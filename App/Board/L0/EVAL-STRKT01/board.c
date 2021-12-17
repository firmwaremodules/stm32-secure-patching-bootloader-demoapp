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

/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/


/**
* @brief  System Clock Configuration
*         The system Clock is configured as follow :
*            System Clock source            = PLL (HSI)
*            SYSCLK(Hz)                     = 32000000
*            HCLK(Hz)                       = 32000000
*            AHB Prescaler                  = 1
*            APB1 Prescaler                 = 1
*            APB2 Prescaler                 = 1
*            Flash Latency(WS)              = 1
*            Main regulator output voltage  = Scale1 mode
* @retval None
*/
void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is
    clocked below the maximum system frequency, to update the voltage scaling value
    regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* Enable HSI Oscillator */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
    RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        /* Initialization Error */
        while (1);
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
    clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        /* Initialization Error */
        while (1);
    }
}




void board_specific_init(void)
{
    SystemClock_Config();
}



void board_led_toggle(void)
{
    BSP_LED_Toggle(BOARD_LED_STATUS);
}

void board_led_on(void)
{
    BSP_LED_On(BOARD_LED_STATUS);
}

void board_led_off(void)
{
    BSP_LED_Off(BOARD_LED_STATUS);
}


