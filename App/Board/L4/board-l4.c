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
#include <stdint.h>


void board_watchdog_service(void)
{
    WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD);
}


/******************************************************************************/
/*            CRC                                                            */
/******************************************************************************/

static CRC_HandleTypeDef    CrcHandle;

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

int board_crc_config(BOARD_CRC_ConfigTypeDef eCRCConfg)
{
    int status = BOARD_STATUS_OK;

    /* Switch to the selected configuration */
    CrcHandle.Instance = CRC;

    /* The input data are not inverted */
    CrcHandle.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;

    /* The output data are not inverted */
    CrcHandle.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;

    switch (eCRCConfg)
    {
    case BOARD_CRC_CONFIG_32BIT:
        /* The Default polynomial is used */
        CrcHandle.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
        /* The default init value is used */
        CrcHandle.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
        /* The input data are 32-bit long words */
        CrcHandle.InputDataFormat = CRC_INPUTDATA_FORMAT_WORDS;
        /* Valid parameter*/
        break;

    case BOARD_CRC_CONFIG_16BIT:
        /* The CRC-16-CCIT polynomial is used */
        CrcHandle.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_DISABLE;
        CrcHandle.Init.GeneratingPolynomial = 0x1021U;
        CrcHandle.Init.CRCLength = CRC_POLYLENGTH_16B;
        /* The zero init value is used */
        CrcHandle.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_DISABLE;
        CrcHandle.Init.InitValue = 0U;
        /* The input data are 8-bit long */
        CrcHandle.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
        /* Valid parameter*/
        break;

    default:
        /* Invalid parameter */
        status = BOARD_STATUS_ERROR;
        break;
    }

    if (status == BOARD_STATUS_OK)
    {
        if (HAL_CRC_Init(&CrcHandle) != HAL_OK)
        {
            status = BOARD_STATUS_ERROR;
        }
    }
    return status;
}

uint32_t board_crc_calculate(uint32_t pBuffer[], uint32_t BufferLength)
{
    return HAL_CRC_Calculate(&CrcHandle, pBuffer, BufferLength);
}




