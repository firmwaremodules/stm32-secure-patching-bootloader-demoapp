#ifndef __BOARD_H
#define __BOARD_H

#include "stm32f7xx_hal.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_qspi.h" /* For low level flash common */
#include "board-f7.h"
#define BOARD_NAME_STRING     "DISCO-F769I"
/* This board file for DISCO-F769I contains elements common to the 
 * Demonstration projects.
 */






 /* Button --------------------------------------------------------------------*/

#define BUTTON_INIT()         BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
#define BUTTON_PUSHED()      (BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_SET)

/* Trace and YMODEM updater UART ---------------------------------------------*/

/* ST-LINK UART */
#define COM_UART                                USART1
#define COM_UART_CLK_ENABLE()                   __HAL_RCC_USART1_CLK_ENABLE()
#define COM_UART_CLK_DISABLE()                  __HAL_RCC_USART1_CLK_DISABLE()

#define COM_UART_TX_AF                          GPIO_AF7_USART1
#define COM_UART_TX_GPIO_PORT                   GPIOA
#define COM_UART_TX_PIN                         GPIO_PIN_9
#define COM_UART_TX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM_UART_TX_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define COM_UART_RX_AF                          GPIO_AF7_USART1
#define COM_UART_RX_GPIO_PORT                   GPIOA
#define COM_UART_RX_PIN                         GPIO_PIN_10
#define COM_UART_RX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM_UART_RX_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()



/* Uncomment to enable the adaquate Clock Source */
#define RTC_CLOCK_SOURCE_LSI
/*#define RTC_CLOCK_SOURCE_LSE*/

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
