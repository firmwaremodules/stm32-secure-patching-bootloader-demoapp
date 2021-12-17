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
#ifndef __BOARD_H
#define __BOARD_H

#include "stm32l4xx_hal.h"
#include "stm32l496g_discovery.h"
// There is a QSPI flash on here
#include "stm32l496g_discovery_qspi.h" /* For low level flash common */
#include "board-l4.h"


#define BOARD_NAME_STRING     "DISCO-L496G"


/* This board file for DISCO-L496G contains elements common to the 
 * Demonstration projects.
 */

/* Button --------------------------------------------------------------------*/

#define BUTTON_INIT()         BSP_JOY_Init(JOY_MODE_GPIO);
#define BUTTON_PUSHED()      (BSP_JOY_GetState() == JOY_SEL)

#define BOARD_UART1_CLK_ENABLE()                __HAL_RCC_USART1_CLK_ENABLE()
#define BOARD_UART1_CLK_DISABLE()               __HAL_RCC_USART1_CLK_DISABLE()
#define BOARD_UART1_TX_AF                       GPIO_AF7_USART1
#define BOARD_UART1_TX_PIN                      GPIO_PIN_6
#define BOARD_UART1_TX_GPIO_PORT                GPIOB
#define BOARD_UART1_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define BOARD_UART1_TX_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOB_CLK_DISABLE()


/* Trace and YMODEM updater UART ---------------------------------------------*/


/* ST-LINK UART */
#define COM_UART                                USART2
#define COM_UART_CLK_ENABLE()                   __HAL_RCC_USART2_CLK_ENABLE()
#define COM_UART_CLK_DISABLE()                  __HAL_RCC_USART2_CLK_DISABLE()

#define COM_UART_TX_AF                          GPIO_AF7_USART2
#define COM_UART_TX_GPIO_PORT                   GPIOA
#define COM_UART_TX_PIN                         GPIO_PIN_2
#define COM_UART_TX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM_UART_TX_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define COM_UART_RX_AF                          GPIO_AF7_USART2
#define COM_UART_RX_GPIO_PORT                   GPIOD
#define COM_UART_RX_PIN                         GPIO_PIN_6
#define COM_UART_RX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOD_CLK_ENABLE()
#define COM_UART_RX_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOD_CLK_DISABLE()



/* Uncomment to enable the adaquate Clock Source */
#define RTC_CLOCK_SOURCE_LSI
/*#define RTC_CLOCK_SOURCE_LSE*/

#ifdef RTC_CLOCK_SOURCE_LSI
#define RTC_ASYNCH_PREDIV    0x7FU
#define RTC_SYNCH_PREDIV     0xF9
#endif

#ifdef RTC_CLOCK_SOURCE_LSE
#define RTC_ASYNCH_PREDIV  0x7FU
#define RTC_SYNCH_PREDIV   0x00FFU
#endif


/* LEDs ----------------------------------------------------------------------*/

#define BOARD_LED_STATUS                        LED_GREEN


#endif
