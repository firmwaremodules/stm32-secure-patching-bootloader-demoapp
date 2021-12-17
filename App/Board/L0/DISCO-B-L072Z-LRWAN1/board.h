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

#include "stm32l0xx_hal.h"
#include "b-l072z-lrwan1.h"
#include "board-l0.h"


#define BOARD_NAME_STRING     "B-L072Z-LRWAN1"


/* This board file for B-L072Z-LRWAN1 contains elements common to the 
 * Demonstration projects.
 * 
 * This board has 4 user LEDs and 1 button, and offers access to these through
 * a common BSP API.
 */

/* Button --------------------------------------------------------------------*/

#define BUTTON_INIT()         BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
#define BUTTON_PUSHED()      (BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_RESET)



#define BOARD_UART1_CLK_ENABLE()                __HAL_RCC_USART1_CLK_ENABLE()
#define BOARD_UART1_CLK_DISABLE()               __HAL_RCC_USART1_CLK_DISABLE()
#define BOARD_UART1_TX_AF                       GPIO_AF4_USART1
#define BOARD_UART1_TX_PIN                      GPIO_PIN_9
#define BOARD_UART1_TX_GPIO_PORT                GPIOA
#define BOARD_UART1_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define BOARD_UART1_TX_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOA_CLK_DISABLE()


/* Trace and YMODEM updater UART ---------------------------------------------*/


/* ST-LINK UART */
#define COM_UART                                USART2
#define COM_UART_CLK_ENABLE()                   __HAL_RCC_USART2_CLK_ENABLE()
#define COM_UART_CLK_DISABLE()                  __HAL_RCC_USART2_CLK_DISABLE()

#define COM_UART_TX_AF                          GPIO_AF4_USART2
#define COM_UART_TX_GPIO_PORT                   GPIOA
#define COM_UART_TX_PIN                         GPIO_PIN_2
#define COM_UART_TX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM_UART_TX_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define COM_UART_RX_AF                          GPIO_AF4_USART2
#define COM_UART_RX_GPIO_PORT                   GPIOA
#define COM_UART_RX_PIN                         GPIO_PIN_3
#define COM_UART_RX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM_UART_RX_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()


/* Uncomment to enable the adaquate Clock Source */
#define RTC_CLOCK_SOURCE_LSI
/*#define RTC_CLOCK_SOURCE_LSE*/

#ifdef RTC_CLOCK_SOURCE_LSI
#define RTC_ASYNCH_PREDIV    0x7C
#define RTC_SYNCH_PREDIV     0x0127
#endif

#ifdef RTC_CLOCK_SOURCE_LSE
#define RTC_ASYNCH_PREDIV  0x7FU
#define RTC_SYNCH_PREDIV   0x00FFU
#endif


/* LEDs ----------------------------------------------------------------------*/

#define BOARD_LED_STATUS                        LED_GREEN


#endif
