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
#ifndef APP_UPDATE_PATCH_H
#define APP_UPDATE_PATCH_H

/* 
 * File: app_update_patch.h
 *
 * YMODEM wrappers for the stm32-secure-patching-bootloader patch engine APIs
 * provided in the file Include/stm32_secure_patching_bootloader_interface_XXXX.h
 * 
 * This is a demonstration on how to use bootloader's patch engine APIs from an
 * application-level protocol.
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/**
 * Initialize the firmware download to flash state machine.  Call this first, 
 * optionally specifying the download file size, if known.  Set to 0 if not known.
 * pStatus, if provided, may return additional implementation-dependent status information.
 * Returns HAL_OK (0) if success, HAL_ERROR (1) otherwise.
 */
uint32_t APP_UPDATE_Init(int* pStatus, uint32_t uFileSize);

/**
 * Submit data to the firmware download to flash state machine. 
 * Must be initialized with APP_UPDATE_Init() first, otherwise HAL_ERROR returned.
 * Data is accepted and written until user calls APP_UPDATE_Finish().
 * User must know when all expected bytes have been submitted.
 * Data must be submitted in multiples of 4 bytes (update images are encrypted and
 * will always be multiple of 16).
 * pStatus, if provided, may return additional implementation-dependent status information.
 * Returns HAL_OK if data written or HAL_ERROR if size contraint or any write error occurs.
 */
uint32_t APP_UPDATE_Data(int* pStatus, uint8_t *pData, uint32_t uSize);

/**
 * Finish the firmware download to flash state machine: after returning, upon
 * next boot the bootloader will attempt to install the new firmware.
 * Calling Finish without Init returns HAL_ERROR.
 * After successfully calling Finish, no further Data or Finish calls can be made.
 * pStatus, if provided, may return additional implementation-dependent status information.
 */
uint32_t APP_UPDATE_Finish(int* pStatus);

/**
 * Poll for the status of the update.
 *
 * Return an implementation-dependent status code.
 * The patching implementation will return a code from SE_PATCH_StatusCode.
 */
int APP_UPDATE_Poll_Status(void);


#endif /* APP_UPDATE_PATCH_H */

