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
#include "stm32l0xx_nucleo.h"
#include "board-l0.h"


#define BOARD_NAME_STRING     "NUCLEO-L073RZ"


/* This board file for NUCLEO-L073RZ contains elements common to the 
 * Demonstration projects.
 */

/* Button --------------------------------------------------------------------*/

#define BUTTON_INIT()         BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
#define BUTTON_PUSHED()      (BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_RESET)


/*
* 

PA9 - USART1 TX

         CN7                  CN5   CN10

         1  2                       1  2
         3  4                  10---3  4
         5  6 - E5V     PB9  -  9---5  6
         7  8 - GND             8---7  8
         9 10                   7---9 10
        11 12                   6--11 12
        13 14           PA6  -  5--13 14
        15 16           PA7  -  4--15 16
 PA15 - 17 18                   3--17 18 - PB11
        19 20                   2--19 20
        21 22        D8 PA9  -  1--21 22

 PC13 - 23 24                      23 24 - PB1
        25 26           PB10 -     25 26 - PB15 
        27 28 - PA0     PB4  -     27 28 - PB14
        29 30 - PA1                29 30 - PB13
        31 32 - PA4                31 32
        33 34 - PB0     PA10 -     33 34
        35 36                      35 36
        37 38                      37 38

*/
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


/**
* @}
*/

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
