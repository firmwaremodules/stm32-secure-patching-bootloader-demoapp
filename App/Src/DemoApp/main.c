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
 /* This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at : www.st.com/SLA0044
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fw_update_ymodem.h"
#include "stm32_secure_patching_bootloader_interface_v1.0.0.h"
#include <string.h>
#include <stdio.h>

/* For projects and boards configured for external flash. */
#if QSPI_MEMORY_MAPPED_MODE
#if FW_UPDATE_VERSION == 1
const char qspi_string[] LOCATION_EXTFLASH_ATTRIBUTE = "This is a version 1 message from QSPI!";
#else
const char qspi_string[] LOCATION_EXTFLASH_ATTRIBUTE = "This is a version 2 message from QSPI!";
#endif

/* These structures allows for build-time control of application size. */
const uint8_t LARGE_APPLICATION_BLOB_QSPI[LARGE_APPLICATION_BLOB_QSPI_SIZE] LOCATION_EXTFLASH_ATTRIBUTE = { 0x55 };
const uint8_t LARGE_APPLICATION_BLOB[LARGE_APPLICATION_BLOB_SIZE] = { 0xAA };
#endif

static HAL_StatusTypeDef GetActiveFirmwareInfo(void);

/**
  * @brief  Display the TEST Main Menu choices on HyperTerminal
  * @param  None.
  * @retval None.
  */
static void PrintMainMenu(void)
{
    printf("\n------------------- Main Menu ----------------------------\n\n");
    printf("  Download a new firmware image or patch via YMODEM ----- 1\n\n");
    printf("  Get active firmware info ------------------------------ 2\n\n");
}

/**
  * @brief  Display the Main Menu choices on HyperTerminal
  * @param  None.
  * @retval Does not return.
  */
static void Run(void)
{
    uint8_t key = 0U;

    /* Print Main Menu message*/
    PrintMainMenu();

    while (1U)
    {
        /* Clean the input path */
        Board_COM_Flush();

        /* Receive input from UART.  Note that this timeout defines the
         * loop period and the LED blink rate.
         */
        if (Board_COM_Receive(&key, 1U, RX_TIMEOUT) == BOARD_STATUS_OK)
        {
            switch (key)
            {
            case '1' :
                FW_UPDATE_YMODEM_Run();
                break;
            case '2' :
                GetActiveFirmwareInfo();
            break;
            default:
                printf("Invalid option\n");
            break;
            }   

            /*Print Main Menu message*/
            PrintMainMenu();
        }

        board_led_toggle();
    }
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize board/platform first */
    board_init();

    printf("\nDemoApp starting...\n");

    /* Get the firmware version embedded in the active slot header using the 
     * bootloader services.
     */
    SE_StatusTypeDef se_Status = SE_KO;
    SE_APP_ActiveFwInfo FwInfo;
    memset(&FwInfo, 0x0, sizeof(SE_APP_ActiveFwInfo));
    SE_APP_GetActiveFwInfo(&se_Status, &FwInfo);

    printf("\n-----------------------------------------------------------------------------------\n");
    printf("      stm32-secure-patching-bootloader Demo Application                             \n");
    printf("                                                                                    \n");
    printf("      https://github.com/firmwaremodules/stm32-secure-patching-bootloader-demoapp   \n");
    printf("------------------------------------------------------------------------------------\n");
    /* Note that build TIME and DATE must *not* be present to allow for binary-exact reproducible builds
     * at any point in time - useful if a patch must be created from a version whose binary is not available but
     * the repository tag is.
     */
    /* Note that FW version below comes from the embedded image header and is the extracted 3 digits. */
    /* BUILD_VERSION_STR comes from the "git describe" output to capture the full version info.    
     */
    printf("Board: " BOARD_NAME_STRING "\n");
    printf("FW Build: " BUILD_VERSION_STR "\n"); /* note: injected through preprocessor */
    GetActiveFirmwareInfo();

#if QSPI_MEMORY_MAPPED_MODE
    printf("QSPI string: %s", qspi_string);
#endif

    /* This version define allows for building two distinct applications
     * with this one difference to allow the patch generator to make a patch.
     *    * Set FW_UPDATE_VERSION set to 1 in project.h and change the IDE's postbuild command
     *      to' argument version to 1.0.0 or similar.  Do a build.
     *    * Set FW_UPDATE_VERSION set to 2 in project.h and change the IDE's postbuild command
     *      to' argument version to anything higher than 1.0.0 such as 1.1.0.
     * 
     * "../../../../../../../Bootloader/Scripts/STM32CubeIDE/postbuild.sh" "${BuildArtifactFileBaseName}" "../../Keys" "../../../../../Binary" "1.1.0" "1.0.0" "NUCLEO-L073RZ" "v1.0.0" 512 0
     */
#if FW_UPDATE_VERSION == 1
    printf("Version 1\n");
#else
    printf("Version 2\n");
#endif

    printf("\n\n");

    /* Does not return */
    Run();
}


/**
  * @brief  Execute some Secure Engine API function calls.
  * @param  None
  * @retval HAL Status.
  */
HAL_StatusTypeDef GetActiveFirmwareInfo(void)
{
    HAL_StatusTypeDef ret = HAL_ERROR;
    SE_ErrorStatus se_retCode = SE_ERROR;
    SE_StatusTypeDef se_Status = SE_KO;
    SE_APP_ActiveFwInfo FwInfo;

    memset(&FwInfo, 0x0, sizeof(SE_APP_ActiveFwInfo));

    /* Get FW info */
    se_retCode = SE_APP_GetActiveFwInfo(&se_Status, &FwInfo);

    if ((SE_SUCCESS == se_retCode) &&
        (SE_OK == se_Status))
    {
        /* Return success */
        ret = HAL_OK;

        /* Print the result */
        printf("Firmware Info:\n");
        printf("  FW Version (from header): %d.%d.%d\n",
            FW_VERSION_MAJOR(FwInfo.ActiveFwVersion),
            FW_VERSION_MINOR(FwInfo.ActiveFwVersion),
            FW_VERSION_PATCH(FwInfo.ActiveFwVersion));
        printf("  ActiveFwSize: %d bytes\n", FwInfo.ActiveFwSize);
        printf("  ActiveFwTag: ");
        for (int i = 0; i < SE_TAG_LEN; i++) {
            printf("%02x", FwInfo.ActiveFwTag[i]);
        }
        printf("\n");
    }
    else
    {
        /* Failure */
        printf("  ERROR: bootloader interface access failed.  Is the bootloader present?\n");
    }

    return ret;
}


