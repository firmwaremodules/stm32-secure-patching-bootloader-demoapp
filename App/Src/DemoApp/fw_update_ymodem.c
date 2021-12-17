/**
  ******************************************************************************
  * @file    fw_update_app.c
  * @author  MCD Application Team
  * @brief   Firmware Update module.
  *          This file provides set of firmware functions to manage Firmware
  *          Update functionalities.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/*
 * Copyright (c) 2021 Firmware Modules Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ymodem.h"
#include "app_update_patch.h"
#include <string.h>
#include <stdio.h>


static uint32_t m_uFileSizeYmodem = 0U;  /* !< Ymodem File size*/
static uint32_t m_uNbrBlocksYmodem = 0U; /* !< Ymodem Number of blocks*/
static uint32_t m_uPacketsReceived = 0U; /* !< Ymodem packets received*/


/**
  * @brief  Display the FW_UPDATE Main Menu choices on HyperTerminal
  * @param  None.
  * @retval None.
  */
static void PrintWelcome(void)
{
    printf("---------------- YMODEM Firmware Patch Updater -------------------------\n\n");
}

/**
  * @brief Download a new Firmware from the host.
  * @retval HAL status
  * 
  * See Project/DemoApp/README.md for details on expected operation.
  */
static HAL_StatusTypeDef DownloadNewFirmware()
{
    HAL_StatusTypeDef ret = HAL_ERROR;
    COM_StatusTypeDef e_result;
    uint32_t u_fw_size;

    printf("  -- Send Firmware \n\n");

    /* Refresh Watchdog */
    board_watchdog_service();

    /* Download is initialized when the user sends a file */
    /* Download binary */
    printf("  -- -- File> Transfer> YMODEM> Send ");

    /*Init of Ymodem*/
    Ymodem_Init();

    /*Receive through Ymodem*/
    e_result = Ymodem_Receive(&u_fw_size);
    printf("\n\n");

    int e_update_status = APP_UPDATE_Poll_Status();
    if ((e_result == COM_OK))
    {
        printf("  -- -- Slot 1 download completed: (%d)\n\n", e_update_status);
        printf("  -- -- Bytes: %d\n\n", u_fw_size);
        ret = HAL_OK;
    }
    else if (e_result == COM_ABORT)
    {
        printf("  -- -- Aborted by user: (%d)\n\n", e_update_status);
        ret = HAL_ERROR;
    }
    else
    {
        printf("  -- -- Error during file download: (%d)\n\n", e_update_status);
        ret = HAL_ERROR;
    }
    return ret;
}



/**
  * @brief  Run FW Update process.
  * @param  None
  * @retval HAL Status.
  */
HAL_StatusTypeDef FW_UPDATE_YMODEM_Run(void)
{
    HAL_StatusTypeDef ret = HAL_ERROR;

    /* Print Firmware Update welcome message */
    PrintWelcome();

    /* Download new firmware image*/
    ret = DownloadNewFirmware();

    if (HAL_OK == ret)
    {
        int update_status = 0;
        /* 'Finalize the image to mark it as ready for update. 
        * Without calling this API, the bootloader will not take action to perform the update on 
        * next boot.  This is useful to schedule updates.
        */
        if (APP_UPDATE_Finish(&update_status) == HAL_OK)
        {
            /* System Reboot*/
            printf("  -- Image correctly downloaded (status=%d) - reboot\n\n", update_status);
            HAL_Delay(1000U);
            HAL_NVIC_SystemReset();
        } 
        else
        {
            printf(" --- Image download finalization failed.\n\n");
        }
    }

    if (ret != HAL_OK)
    {
        printf("  -- Operation failed\n\n");
    }
    return ret;
}

/*----- Callbacks -------------------------------------------------------------*/

/**
  * @brief  Ymodem Header Packet Transfer completed callback.
  * @param  uFileSize Dimension of the file that will be received (Bytes).
  * @retval None
  */
HAL_StatusTypeDef Ymodem_HeaderPktRxCpltCallback(uint32_t uFileSize)
{
  HAL_StatusTypeDef ret = HAL_ERROR;

  /*Reset of the ymodem variables */
  m_uFileSizeYmodem = 0U;
  m_uPacketsReceived = 0U;
  m_uNbrBlocksYmodem = 0U;
 
  if (APP_UPDATE_Init(NULL, uFileSize) == HAL_OK)
  {
    ret = HAL_OK;

    /*Filesize information is stored*/
    m_uFileSizeYmodem = uFileSize;

    /* compute the number of 1K blocks */
    m_uNbrBlocksYmodem = (m_uFileSizeYmodem + (PACKET_1K_SIZE - 1U)) / PACKET_1K_SIZE;
  } 

  /* NOTE : delay inserted for Ymodem protocol*/
  HAL_Delay(1000U);

  return ret;
}

/**
  * @brief  Ymodem Data Packet Transfer completed callback.
  * @param  pData Pointer to the buffer.
  * @param  uSize Packet dimension (Bytes).
  * @retval None
  */
HAL_StatusTypeDef Ymodem_DataPktRxCpltCallback(uint8_t *pData, uint32_t uSize)
{
  HAL_StatusTypeDef e_ret_status = HAL_ERROR;

  m_uPacketsReceived++;

  /*Increase the number of received packets*/
  if (m_uPacketsReceived == m_uNbrBlocksYmodem) /*Last Packet*/
  {
    /*Extracting actual payload from last packet*/
    if (0 == (m_uFileSizeYmodem % PACKET_1K_SIZE))
    {
      /* The last packet must be fully considered */
      uSize = PACKET_1K_SIZE;
    }
    else
    {
      /* The last packet is not full, drop the extra bytes */
      uSize = m_uFileSizeYmodem - ((uint32_t)(m_uFileSizeYmodem / PACKET_1K_SIZE) * PACKET_1K_SIZE);
    }

    m_uPacketsReceived = 0U;
  }

  /* Submit data to the update handler implementation */
  if (APP_UPDATE_Data(NULL, pData, uSize) == HAL_OK)
  {
      e_ret_status = HAL_OK;
  }
  else
  {
      e_ret_status = HAL_ERROR;
  }

  if (e_ret_status == HAL_ERROR)
  {

    /*Reset of the ymodem variables */
    m_uFileSizeYmodem = 0U;
    m_uPacketsReceived = 0U;
    m_uNbrBlocksYmodem = 0U;
  }
  return e_ret_status;
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
