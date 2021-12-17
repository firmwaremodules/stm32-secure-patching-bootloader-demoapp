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

#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include "board-f4.h"
/* This board file for F769I-DISCO contains elements common to the 
 * Demonstration projects.
 */

#define BOARD_NAME_STRING     "F429ZI-NUCLEO"

 /* Button --------------------------------------------------------------------*/

#define BUTTON_INIT()         BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
#define BUTTON_PUSHED()      (BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_SET)

/* Trace and YMODEM updater UART ---------------------------------------------*/

/*
* 
*  UART2 - PD5
       CN11                                                       CN12

        1  2              CN8                    CN7                -  1 2
        3  4                                                           3 4
        5  6              1  2                   1  2                  5 6
        7  8              3  4                   3  4                  7 8
        9 10              5  6                   5  6                  9 10
       11 12              7  8                   7  8                 11 12       
       13 14              9 10                   9 10                 13 14
       15 16             11 12                  11 12                 15 16
       17 18             13 14                  13 14                 17 18
       19 20             15 16                  15 16                 19 20
       21 22                                    17 18                 21 22
       23 24                                    19 20                 23 24
       25 26                                                          25 26
       27 28              CN9                    CN10                 27 28
       29 30                                                          29 30
                          1  2                   1  2                 31 32
                          3  4                   3  4               - 33 34
                          5  6 - PD5 USART2 TX   5  6                 35 36
                          7  8                   7  8
                          9 10                   9 10
                         11 12                  11 12
                         13 14                  13 14
                         15 16                  15 16
                         17 18                  17 18
                         19 20                  19 20
                         21 22                  21 22
                         23 24                  25 26
                         27 28                  27 28
                         29 30                  29 30
                                                31 32
                                                33 34 

*/

/* ST-LINK UART */
#define COM_UART                                USART3
#define COM_UART_CLK_ENABLE()                   __HAL_RCC_USART3_CLK_ENABLE()
#define COM_UART_CLK_DISABLE()                  __HAL_RCC_USART3_CLK_DISABLE()

#define COM_UART_TX_AF                          GPIO_AF7_USART3
#define COM_UART_TX_GPIO_PORT                   GPIOD
#define COM_UART_TX_PIN                         GPIO_PIN_8
#define COM_UART_TX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOD_CLK_ENABLE()
#define COM_UART_TX_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOD_CLK_DISABLE()

#define COM_UART_RX_AF                          GPIO_AF7_USART3
#define COM_UART_RX_GPIO_PORT                   GPIOD
#define COM_UART_RX_PIN                         GPIO_PIN_9
#define COM_UART_RX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOD_CLK_ENABLE()
#define COM_UART_RX_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOD_CLK_DISABLE()


/**
* @}
*/

  /* Uncomment to enable the adaquate Clock Source */
//#define RTC_CLOCK_SOURCE_LSI
#define RTC_CLOCK_SOURCE_LSE /* F429ZI-NUCLEO LSE available by default */

#ifdef RTC_CLOCK_SOURCE_LSI
#define RTC_ASYNCH_PREDIV    0x7FU
#define RTC_SYNCH_PREDIV     0x0130U
#endif

#ifdef RTC_CLOCK_SOURCE_LSE
#define RTC_ASYNCH_PREDIV  0x7FU
#define RTC_SYNCH_PREDIV   0x00FFU
#endif


/* LEDs ----------------------------------------------------------------------*/

#define BOARD_LED_STATUS                        LED_GREEN


#endif
