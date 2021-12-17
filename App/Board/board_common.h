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
#ifndef __BOARD_COMMON_H
#define __BOARD_COMMON_H

#include "board.h"
#include <stdbool.h>
#include <stdint.h>

#define BOARD_STATUS_OK                         0
#define BOARD_STATUS_ERROR                      -1


void board_init(void);

/* Service watchdog */
void board_watchdog_service(void);

/* Indicators */
void board_led_toggle(void);
void board_led_on(void);
void board_led_off(void);

/* CRC 
 * Hardware or SW (depending on device support) used for ymodem 16-bit CRC.
 * Hardware must always be powered up on Init.
 */
typedef enum
{
    BOARD_CRC_CONFIG_NONE = 0U,   /*!< None */
    BOARD_CRC_CONFIG_32BIT,       /*!< Default configuration */
    BOARD_CRC_CONFIG_16BIT        /*!< 16 bit configuration */
} BOARD_CRC_ConfigTypeDef;
/* APIs return 0 on success, < 0 on error. */
int board_crc_init(void);
int board_crc_deinit(void);
int board_crc_config(BOARD_CRC_ConfigTypeDef eCRCConfg);
uint32_t board_crc_calculate(uint32_t pBuffer[], uint32_t BufferLength);

/* UART APIs */
int Board_COM_Transmit(uint8_t* Data, uint16_t uDataLength, uint32_t uTimeout);
int Board_COM_Receive(uint8_t* Data, uint16_t uDataLength, uint32_t uTimeout);
int Board_COM_Flush(void);

/*---------------------------------------------------------*/
/* Private */

void board_specific_init(void);
void board_project_init(void);

#endif
