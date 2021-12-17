/**
  ******************************************************************************
  * @file    ymodem.c
  * @author  MCD Application Team
  * @brief   Ymodem module.
  *          This file provides set of firmware functions to manage Ymodem
  *          functionalities.
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

/** @addtogroup USER_APP User App Example
  * @{
  */

/** @addtogroup  FW_UPDATE Firmware Update Example
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ymodem.h"
#include <string.h>
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IS_CAP_LETTER(c)    (((c) >= 'A') && ((c) <= 'F'))
#define IS_LC_LETTER(c)     (((c) >= 'a') && ((c) <= 'f'))
#define IS_09(c)            (((c) >= '0') && ((c) <= '9'))
#define ISVALIDHEX(c)       (IS_CAP_LETTER(c) || IS_LC_LETTER(c) || IS_09(c))
#define ISVALIDDEC(c)       IS_09(c)
#define CONVERTDEC(c)       (c - '0')

#define CONVERTHEX_ALPHA(c) (IS_CAP_LETTER(c) ? ((c) - 'A'+10) : ((c) - 'a'+10))
#define CONVERTHEX(c)       (IS_09(c) ? ((c) - '0') : CONVERTHEX_ALPHA(c))
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* @note ATTENTION - please keep this variable 32bit alligned */
static uint8_t m_aPacketData[PACKET_1K_SIZE + PACKET_DATA_INDEX + PACKET_TRAILER_SIZE]; /*!<Array used to store Packet Data*/
static uint8_t m_aFileName[FILE_NAME_LENGTH + 1U]; /*!< Array used to store File Name data */

/* Private function prototypes -----------------------------------------------*/
static HAL_StatusTypeDef ReceivePacket(uint8_t *pData, uint32_t *puLength, uint32_t uTimeout);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Convert a string to an integer
  * @param  pInputStr: The string to be converted
  * @param  pIntNum: The integer value
  * @retval 1: Correct
  *         0: Error
  */
static uint32_t Str2Int(uint8_t* pInputStr, uint32_t* pIntNum)
{
    uint32_t i = 0U, res = 0U;
    uint32_t val = 0U;

    if ((pInputStr[0U] == '0') && ((pInputStr[1U] == 'x') || (pInputStr[1U] == 'X')))
    {
        i = 2U;
        while ((i < 11U) && (pInputStr[i] != '\0'))
        {
            if (ISVALIDHEX(pInputStr[i]))
            {
                val = (val << 4U) + CONVERTHEX(pInputStr[i]);
            }
            else
            {
                /* Return 0, Invalid input */
                res = 0U;
                break;
            }
            i++;
        }

        /* valid result */
        if (pInputStr[i] == '\0')
        {
            *pIntNum = val;
            res = 1U;
        }
    }
    else /* max 10-digit decimal input */
    {
        while ((i < 11U) && (res != 1U))
        {
            if (pInputStr[i] == '\0')
            {
                *pIntNum = val;
                /* return 1 */
                res = 1U;
            }
            else if (((pInputStr[i] == 'k') || (pInputStr[i] == 'K')) && (i > 0U))
            {
                val = val << 10U;
                *pIntNum = val;
                res = 1U;
            }
            else if (((pInputStr[i] == 'm') || (pInputStr[i] == 'M')) && (i > 0U))
            {
                val = val << 20U;
                *pIntNum = val;
                res = 1U;
            }
            else if (ISVALIDDEC(pInputStr[i]))
            {
                val = val * 10U + CONVERTDEC(pInputStr[i]);
            }
            else
            {
                /* return 0, Invalid input */
                res = 0U;
                break;
            }
            i++;
        }
    }

    return res;
}


/**
  * @brief  Transmit a byte to the HyperTerminal
  * @param  param The byte to be sent
  * @retval HAL_StatusTypeDef HAL_OK if OK
  */
static HAL_StatusTypeDef Serial_PutByte(uint8_t uParam)
{
    return Board_COM_Transmit(&uParam, 1U, TX_TIMEOUT);
}

/**
  * @brief  Receive a packet from sender
  * @param  pData
  * @param  puLength
  *     0: end of transmission
  *     2: abort by sender
  *    >0: packet length
  * @param  uTimeout
  * @retval HAL_OK: normally return
  *         HAL_BUSY: abort by user
  */
static HAL_StatusTypeDef ReceivePacket(uint8_t *pData, uint32_t *puLength, uint32_t uTimeout)
{
  uint32_t crc;
  uint32_t packet_size = 0U;
  HAL_StatusTypeDef status;
  uint8_t char1;

  *puLength = 0U;

  /* If the SecureBoot configured the IWDG, UserApp must reload IWDG counter with value defined in the reload register */
  WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD);

  status = (HAL_StatusTypeDef)Board_COM_Receive(&char1, 1, uTimeout);

  if (status == HAL_OK)
  {
    switch (char1)
    {
      case SOH:
        packet_size = PACKET_SIZE;
        break;
      case STX:
        packet_size = PACKET_1K_SIZE;
        break;
      case EOT:
        break;
      case CA:
        if ((Board_COM_Receive(&char1, 1U, uTimeout) == HAL_OK) && (char1 == CA))
        {
          packet_size = 2U;
        }
        else
        {
          status = HAL_ERROR;
        }
        break;
      case ABORT1:
      case ABORT2:
        status = HAL_BUSY;
        break;
      case RB:
        Board_COM_Receive(&char1, 1U, uTimeout);                /* Ymodem starup sequence : rb ==> 0x72 + 0x62 + 0x0D */
        Board_COM_Receive(&char1, 1U, uTimeout);
        packet_size = 3U;
        break;
      default:
        status = HAL_ERROR;
        break;
    }
    *pData = char1;

    if (packet_size >= PACKET_SIZE)
    {
      status = Board_COM_Receive(&pData[PACKET_NUMBER_INDEX], packet_size + PACKET_OVERHEAD_SIZE, uTimeout);

      /* Simple packet sanity check */
      if (status == HAL_OK)
      {
        if (pData[PACKET_NUMBER_INDEX] != ((pData[PACKET_CNUMBER_INDEX]) ^ NEGATIVE_BYTE))
        {
          packet_size = 0U;
          status = HAL_ERROR;
        }
        else
        {
          /* Check packet CRC */
          /* CRC may be used by secure engine services and so must be configured
           * here each time it is required (as is done by the secure engine services).
           */
          crc = pData[packet_size + PACKET_DATA_INDEX] << 8U;
          crc += pData[packet_size + PACKET_DATA_INDEX + 1U];
          if (board_crc_config(BOARD_CRC_CONFIG_16BIT) != BOARD_STATUS_OK ||
              board_crc_calculate((uint32_t *)&pData[PACKET_DATA_INDEX], packet_size) != crc) {
                packet_size = 0U;
                status = HAL_ERROR;
          }
        }
      }
      else
      {
        packet_size = 0U;
      }
    }
  }
  *puLength = packet_size;
  return status;
}

/**
  * @brief  Init of Ymodem module.
  * @param None.
  * @retval None.
  */
void Ymodem_Init(void)
{
    board_crc_init();
}

/* Public functions ---------------------------------------------------------*/
/**
  * @brief  Receive a file using the ymodem protocol with CRC16.
  * @param  puSize The uSize of the file.
  * @retval COM_StatusTypeDef result of reception/programming
  */
COM_StatusTypeDef Ymodem_Receive(uint32_t *puSize)
{
  uint32_t i, packet_length, session_done = 0U, file_done, errors = 0U, session_begin = 0U;
  uint32_t ramsource, filesize = 0U;
  uint8_t *file_ptr;
  uint8_t file_size[FILE_SIZE_LENGTH + 1U];
  uint32_t packets_received;
  COM_StatusTypeDef e_result = COM_OK;

  while ((session_done == 0U) && (e_result == COM_OK))
  {
    packets_received = 0U;
    file_done = 0U;
    while ((file_done == 0U) && (e_result == COM_OK))
    {
      switch (ReceivePacket(m_aPacketData, &packet_length, DOWNLOAD_TIMEOUT))
      {
        case HAL_OK:
          errors = 0U;
          switch (packet_length)
          {
            case 3U:
              /* Startup sequence */
              break;
            case 2U:
              /* Abort by sender */
              Serial_PutByte(ACK);
              e_result = COM_ABORT;
              break;
            case 0U:
              /* End of transmission */
              Serial_PutByte(ACK);
              *puSize = filesize;
              file_done = 1U;
              break;
            default:
              /* Normal packet */
              if (m_aPacketData[PACKET_NUMBER_INDEX] != (packets_received & 0xff))
              {
                //             Serial_PutByte(NAK);
              }
              else
              {
                if (packets_received == 0U)
                {
                  /* File name packet */
                  if (m_aPacketData[PACKET_DATA_INDEX] != 0U)
                  {
                    /* File name extraction */
                    i = 0U;
                    file_ptr = m_aPacketData + PACKET_DATA_INDEX;
                    while ((*file_ptr != 0U) && (i < FILE_NAME_LENGTH))
                    {
                      m_aFileName[i++] = *file_ptr++;
                    }

                    /* File size extraction */
                    m_aFileName[i++] = '\0';
                    i = 0U;
                    file_ptr ++;
                    while ((*file_ptr != ' ') && (i < FILE_SIZE_LENGTH))
                    {
                      file_size[i++] = *file_ptr++;
                    }
                    file_size[i++] = '\0';
                    Str2Int(file_size, &filesize);

                    /* Header packet received callback call*/
                    if (Ymodem_HeaderPktRxCpltCallback((uint32_t) filesize) == HAL_OK)
                    {
                      Serial_PutByte(ACK);
                      Board_COM_Flush();
                      Serial_PutByte(CRC16);
                    }
                    else
                    {
                      /* End session */
                      Serial_PutByte(CA);
                      Serial_PutByte(CA);
                      e_result = COM_ABORT;
                      break;
                    }

                  }
                  /* File header packet is empty, end session */
                  else
                  {
                    Serial_PutByte(ACK);
                    file_done = 1;
                    session_done = 1;
                    break;
                  }
                }
                else /* Data packet */
                {
                  ramsource = (uint32_t) & m_aPacketData[PACKET_DATA_INDEX];

                  /* Data packet received callback call*/
                  if (Ymodem_DataPktRxCpltCallback((uint8_t *)ramsource, (uint32_t)packet_length) == HAL_OK)
                  {
                    Serial_PutByte(ACK);
                  }
                  else /* An error occurred while writing to Flash memory */
                  {
                    /* End session */
                    Serial_PutByte(CA);
                    Serial_PutByte(CA);
                    e_result = COM_ABORT;
                  }
                }
                packets_received ++;
                session_begin = 1U;
              }
              break;
          }
          break;
        case HAL_BUSY: /* Abort actually */
          Serial_PutByte(CA);
          Serial_PutByte(CA);
          e_result = COM_ABORT;
          break;
        default: /* HAL_ERROR or HAL_TIMEOUT */
          if (session_begin > 0U)
          {
            errors ++;
          }
          if (errors > MAX_ERRORS)
          {
            /* If we've started a transfer but start timing out on the receive,
             * then we will catch this after MAX_ERRORS receive timeouts and abort.
             */
            /* Abort communication */
            Serial_PutByte(CA);
            Serial_PutByte(CA);
            e_result = COM_ABORT;
          }
          else
          {
            Serial_PutByte(CRC16); /* Ask for a packet */
            printf("\b.");         /* Replace C char by . on display console */
          }
          break;
      }
    }
  }
  return e_result;
}

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
