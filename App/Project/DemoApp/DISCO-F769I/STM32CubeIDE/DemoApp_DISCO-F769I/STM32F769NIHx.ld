/*
*****************************************************************************
**
**  File        : STM32F769NIHx.ld
**
**  Abstract    : Linker script for STM32F769NIHx Device with
**                2048 KB FLASH, 512 KB RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed as is, without any warranty
**                of any kind.
**
*****************************************************************************
*/


/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x20080000;    /* end of RAM */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;      /* required amount of heap  */
_Min_Stack_Size = 0x400; /* required amount of stack */

/* Include board and bootloader specific constants */
INCLUDE stm32-secure-patching-bootloader-linker-gcc_DISCO-F769I_v1.0.0.ld

/* Specific ROM/RAM UserApp definition 
 * ISR Vector Table comes after the image header and has to be located at an offset that is aligned to its size,
 * hence the application's actual start address of VECTOR_SIZE+VECTOR_SIZE.
 * | HDR | ...space... | Vect table     |
 *                     VECTOR_SIZE      VECTOR_SIZE+VECTOR_SIZE
 */
APPLI_region_intvec_start__  = STM32_SECURE_PATCHING_BOOTLOADER_SLOT0_START + VECTOR_SIZE;
APPLI_region_ROM_start    = STM32_SECURE_PATCHING_BOOTLOADER_SLOT0_START  + VECTOR_SIZE + VECTOR_SIZE;
APPLI_region_ROM_length   = STM32_SECURE_PATCHING_BOOTLOADER_SLOT0_END - APPLI_region_ROM_start + 1;
APPLI_region_RAM_start    = STM32_SECURE_PATCHING_BOOTLOADER_RAM_START;
APPLI_region_RAM_length    = 0x20080000 - APPLI_region_RAM_start;

/* Specify the memory areas */
MEMORY
{
  ISR_VECTOR (rx)   : ORIGIN = APPLI_region_intvec_start__, LENGTH = VECTOR_SIZE
  APPLI_region_ROM  : ORIGIN = APPLI_region_ROM_start, LENGTH = APPLI_region_ROM_length
  APPLI_region_RAM  : ORIGIN = APPLI_region_RAM_start, LENGTH = APPLI_region_RAM_length
  SE_IF_region_ROM (rx) : ORIGIN = SE_IF_REGION_ROM_START, LENGTH = SE_IF_REGION_ROM_LENGTH
  QSPI (rx)         : ORIGIN = STM32_SECURE_PATCHING_BOOTLOADER_MULTISEG_START, LENGTH = 64M
}

/* Include the common linker script */
INCLUDE stm32-secure-patching-bootloader-app-linker-sections-multiseg_v1.0.0.ld
