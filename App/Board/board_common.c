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


/* Initialization routine common to all boards.
*/
void board_init()
{
    /* STM32 HAL driver layer init */
    HAL_Init();

    /* Project-independent init */
    board_specific_init();
    
    /* Project-specific and board-specific init 
     * project-board.c 
     */
    board_project_init();
}



/*----------------------------------------------------------*/
/* Please note:
 * - With GCC small printf (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar() directly. 
 *   Otherwise we must setup the _write syscall intermediary to call __io_putchar.
 */

extern UART_HandleTypeDef           UartHandle;

int _write(int file, char* ptr, int len)
{
    HAL_UART_Transmit(&UartHandle, (uint8_t*)ptr, len, 0xFFFF);
    return len;
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval ch
  */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&UartHandle, (uint8_t*)&ch, 1U, 0xFFFFU);
    return ch;
}


/**
  * @brief Transmit Data.
  * @param uDataLength: Data pointer to the Data to transmit.
  * @param uTimeout: Timeout duration.
  * @retval Status of the Transmit operation.
  */
int Board_COM_Transmit(uint8_t* Data, uint16_t uDataLength, uint32_t uTimeout)
{
    return HAL_UART_Transmit(&UartHandle, (uint8_t*)Data, uDataLength, uTimeout);
}

/**
  * @brief Receive Data.
  * @param uDataLength: Data pointer to the Data to receive.
  * @param uTimeout: Timeout duration.
  * @retval Status of the Receive operation.
  */
int Board_COM_Receive(uint8_t* Data, uint16_t uDataLength, uint32_t uTimeout)
{
    return HAL_UART_Receive(&UartHandle, (uint8_t*)Data, uDataLength, uTimeout);
}

/**
  * @brief  Flush COM Input.
  * @param None.
  * @retval HAL_Status.
  */
int Board_COM_Flush(void)
{
    /* Clean the input path */
    __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
    return HAL_OK;
}

/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                          */
/******************************************************************************/
/* These are generally common across all STM32 MCUs. */

/**
  * @brief  NMI Handler present for handling Double ECC NMI interrupt
  * @param  None.
  * @retvat void
  */
void NMI_Handler(void)
{
    while (1)
    {
    }
}

void HardFault_Handler(void)
{
    while (1)
    {
    }
}

void MemManage_Handler(void)
{
    while (1)
    {
    }
}

void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}


/******************************************************************************/
/*                 STM32F7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f7xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles Flash operation error interrupt request.
  * @param  None
  * @retval None
  */
void FLASH_IRQHandler(void)
{
    HAL_FLASH_IRQHandler();
}





#ifdef USE_FULL_ASSERT

/**
  * @brief Reports the name of the source file and the source line number
  * where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
      /* USER CODE END 6 */

}

#endif



