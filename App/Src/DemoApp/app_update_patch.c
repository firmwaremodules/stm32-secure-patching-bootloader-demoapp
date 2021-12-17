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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_update_patch.h"
#include "stm32_secure_patching_bootloader_interface_v1.0.0.h"


/* Debug output ONLY works if the update channel is not the same
 * as the debug channel! 
 * E.g. if using YMODEM on the debug UART, any printf messages will
 * delay or corrupt the transfer.
 */
#define DEBUG 0

#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/**
 * Initialize the patch engine.
 *
 * @param uFileSize - if known, specify the filesize to check for capacity up front
 *                    before performing any operations.  Set to 0 if not known.
 */
uint32_t APP_UPDATE_Init(int* pStatus, uint32_t uFileSize)
{
    uint32_t ret = HAL_ERROR;
    SE_PATCH_Status patch_status;

    SE_PATCH_StartInfo start_info = {
        SE_PATCH_ImageType_APP,
        SE_PATCH_RebootDelay_COMMAND, /* The application is responsible for marking the update as "ready to install". 
                                       with SE_PATCH_InstallAtNextReset 
                                       */
        uFileSize
    };

    SE_PATCH_InitStatus(&patch_status);

    if (SE_PATCH_Init(&patch_status, &start_info) == SE_SUCCESS) {
        ret = HAL_OK;
    }
    else {
        /* Cannot print from YMODEM SE_PATCH_PrintStatus(&patch_status); */
    }
    if (pStatus) {
        *pStatus = patch_status.code;
    }
    return ret;
}


uint32_t APP_UPDATE_Data(int* pStatus, uint8_t *pData, uint32_t uSize)
{
    uint32_t ret = HAL_ERROR;
    SE_PATCH_Status patch_status;
    SE_PATCH_InitStatus(&patch_status);
    if (SE_PATCH_Data(&patch_status, pData, uSize) == SE_SUCCESS) {
        ret = HAL_OK;
    }
    else {
        /* Cannot print from YMODEM SE_PATCH_PrintStatus(&patch_status); */
    }
    if (pStatus) {
        *pStatus = patch_status.code;
    }
    return ret;
}


uint32_t APP_UPDATE_Finish(int* pStatus)
{
    uint32_t ret = HAL_ERROR;
    SE_PATCH_Status patch_status;
    SE_PATCH_InitStatus(&patch_status);

    /* Mark the update as ready to install */
    /* Note that using SE_PATCH_RebootDelay_NEXT at initialization would do this for us.
     */
    if (SE_PATCH_InstallAtNextReset(&patch_status) == SE_SUCCESS) {
        ret = HAL_OK;
    }
    else {
        /* Cannot print from YMODEM SE_PATCH_PrintStatus(&patch_status); */
    }
    if (pStatus) {
        *pStatus = patch_status.code;
    }
    return ret;
}

int APP_UPDATE_Poll_Status(void)
{
    SE_PATCH_StatusCode code = SE_PATCH_StatusCode_NONE;
    SE_PATCH_Status patch_status;
    SE_PATCH_InitStatus(&patch_status);

    if (SE_PATCH_Poll(&patch_status) == SE_SUCCESS) {
        code = patch_status.code;
    }
    return code;
}



