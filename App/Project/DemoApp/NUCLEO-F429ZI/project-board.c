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
#include <stdio.h>

#define USER_APP_NBLINKS            1

/* Externally accessble by the board */
UART_HandleTypeDef           UartHandle; 


void board_project_init(void)
{


    /* USART resources configuration (Clock, GPIO pins and USART registers) ----*/
    /* USART configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    UartHandle.Instance = COM_UART;
    UartHandle.Init.BaudRate = 115200U;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits = UART_STOPBITS_1;
    UartHandle.Init.Parity = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode = UART_MODE_RX | UART_MODE_TX;

    HAL_UART_Init(&UartHandle);

#if defined(__GNUC__)
    setvbuf(stdout, NULL, _IONBF, 0);
#endif

    /* Board BSP  Configuration-------------------------------------------------*/

    /* Button Init */
    BUTTON_INIT();

    /* LED Init */
    BSP_LED_Init(BOARD_LED_STATUS);

    for (int i = 0U; i < USER_APP_NBLINKS; i++)
    {
        BSP_LED_Toggle(BOARD_LED_STATUS);
        HAL_Delay(100U);
        BSP_LED_Toggle(BOARD_LED_STATUS);
        HAL_Delay(100U);
        BSP_LED_Toggle(BOARD_LED_STATUS);
        HAL_Delay(100U);
        BSP_LED_Toggle(BOARD_LED_STATUS);
        HAL_Delay(100U);
    }

}

/**
  * @brief  UART MSP Init.
  * @param  huart: UART handler pointer.
  * @retval None.
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

    GPIO_InitTypeDef GPIO_InitStruct;
    if (huart->Instance == COM_UART)
    {
        /* Peripheral Clock Enable */
        COM_UART_CLK_ENABLE();

        /* GPIO Ports Clock Enable */
        COM_UART_TX_GPIO_CLK_ENABLE();
        COM_UART_RX_GPIO_CLK_ENABLE();

        /*Configure GPIO pins : COM_UART_TX_Pin  */
        GPIO_InitStruct.Pin = COM_UART_TX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = COM_UART_TX_AF;
        HAL_GPIO_Init(COM_UART_TX_GPIO_PORT, &GPIO_InitStruct);

        /*Configure GPIO pins : COM_UART_RX_Pin  */
        GPIO_InitStruct.Pin = COM_UART_RX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = COM_UART_RX_AF;
        HAL_GPIO_Init(COM_UART_RX_GPIO_PORT, &GPIO_InitStruct);
    }
}

/**
  * @brief  UART MSP DeInit.
  * @param  huart: UART handler pointer.
  * @retval None.
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == COM_UART)
    {
        /* Peripheral clock disable */
        COM_UART_CLK_DISABLE();

        HAL_GPIO_DeInit(COM_UART_TX_GPIO_PORT, COM_UART_TX_PIN);
        HAL_GPIO_DeInit(COM_UART_RX_GPIO_PORT, COM_UART_RX_PIN);
    }
}


/**
  * @}
  */

  /** @defgroup  COM_Control_Functions Control Functions
    * @{
    */



