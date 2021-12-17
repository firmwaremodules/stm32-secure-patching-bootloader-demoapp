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
#include "main.h"
#include <string.h>

void board_watchdog_service(void)
{
    WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD);
}


/******************************************************************************/
/*            CRC                                                            */
/******************************************************************************/

static CRC_HandleTypeDef    CrcHandle;

/**
  * @brief  Software CRC16 calculation.
  * @retval uint16_t CRC intermediate value
  */
static uint16_t CRCSW_Update(uint16_t crc_in, uint8_t incr)
{
    uint16_t xor = crc_in >> 15;
    uint16_t out = crc_in << 1;

    if (incr)
    {
        out++;
    }
    if (xor)
    {
        out ^= 0x1021;
    }
    return out;
}

/**
  * @brief  Software CRC16 calculation.
  * @param  pdata: pointer to data buffer.
  * @param  size: buffer length in bytes.
  * @retval uint16_t CRC
  */
static uint16_t CRCSW_Calculate(const uint8_t* pdata, uint16_t size)
{
    uint16_t crc;
    uint8_t i;

    for (crc = 0; size > 0; size--, pdata++)
    {
        for (i = 0x80; i; i >>= 1)
        {
            crc = CRCSW_Update(crc, *pdata & i);
        }
    }
    for (i = 0; i < 16; i++)
    {
        crc = CRCSW_Update(crc, 0);
    }
    return crc;
} 

int board_crc_init(void)
{
    /* Configure the peripheral clock */
    __HAL_RCC_CRC_CLK_ENABLE();

    /* Configure CRC with default polynomial - standard configuration */
    return board_crc_config(BOARD_CRC_CONFIG_32BIT);
}

int board_crc_deinit(void)
{
    /* Disable the peripheral clock */
    __HAL_RCC_CRC_CLK_DISABLE();
    return BOARD_STATUS_OK;
}

/* F4 platforms have one CRC configuration. */
int board_crc_config(BOARD_CRC_ConfigTypeDef eCRCConfg)
{
    int status = BOARD_STATUS_OK;

    CrcHandle.Instance = CRC;

    if (HAL_CRC_Init(&CrcHandle) != HAL_OK)
    {
        status = BOARD_STATUS_ERROR;
    }
    return status;
}

/* Only called by bootloader apps by ymodem loader for 16-bit CRC
 * F4 does not have hardware support for this 16-bit CRC.
 */
uint32_t board_crc_calculate(uint32_t pBuffer[], uint32_t BufferLength)
{
    return ((uint32_t)CRCSW_Calculate((uint8_t*)pBuffer, (uint16_t)BufferLength));
}



