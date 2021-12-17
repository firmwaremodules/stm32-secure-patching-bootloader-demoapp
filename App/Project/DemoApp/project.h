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
#ifndef __PROJECT_H
#define __PROJECT_H

/* 'main.h' for project DemoApp */

#include "project-conf.h"
#include "project-board.h"


/* Select from 1 or 2 to change the application. 
* A difference is required in the binary image to generate a patch and this define
* does it.
*/
#define FW_UPDATE_VERSION                       1

/* Maximum Timeout values for flags waiting loops. */
#define COM_UART_TIMEOUT_MAX                    1000U

/* Constants used by Serial Command Line Mode */
#define TX_TIMEOUT                              ((uint32_t)100U)
#define RX_TIMEOUT                              ((uint32_t)1000U)

/* Configuration for external flash multi-segment mode available on select boards only. */

/* This define allows for build-time control of application size for demonstration purposes.
 * These bytes are placed into the QSPI section and require QSPI_MEMORY_MAPPED_MODE to be set to 1.
 */
#ifdef LARGE_APPLICATION_TEST_CONF
#define LARGE_APPLICATION_TEST                      LARGE_APPLICATION_TEST_CONF
#else
#define LARGE_APPLICATION_TEST                      0
#endif


#if LARGE_APPLICATION_TEST
 /* Defined in 256K blocks */
 /* Note: strictly speaking we cannot fill every single byte of a slot
  * because of the header placed into a 512 byte section at the start
  * of each slot.
  */
#define LARGE_APPLICATION_BLOB_QSPI_SIZE            (10 * 0x40000)
#define LARGE_APPLICATION_BLOB_SIZE                 (2 * 0x40000)
#else
#define LARGE_APPLICATION_BLOB_QSPI_SIZE            4
#define LARGE_APPLICATION_BLOB_SIZE                 4
#endif

 /* Set to test QSPI: locate a string in the QSPI (ExtFlashSection) segment,
  * and print a string located there to confirm correct operation.
  */
#ifdef QSPI_MEMORY_MAPPED_MODE_CONF
#define QSPI_MEMORY_MAPPED_MODE                     QSPI_MEMORY_MAPPED_MODE_CONF
#else
#define QSPI_MEMORY_MAPPED_MODE                     0
#endif

  /* Use after variable allocation to have linker allocate to the QSPI flash segment.
   * This requires cooperation with the linker script (having defined and
   * assigned the ExtFlashSection section to QSPI region).
   *
   * E.g.
   *   const uint8_t image[] LOCATION_EXTFLASH_ATTRIBUTE = { 0xAA, 0xBB, ... image data ... };
  */
#define LOCATION_EXTFLASH_ATTRIBUTE __attribute__ ((section ("ExtFlashSection"))) __attribute__ ((aligned(4))) 



#endif /* _PROJECT_H */
