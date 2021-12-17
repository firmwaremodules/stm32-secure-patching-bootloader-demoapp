## STM32L0 Board

* Flash page (128 bytes) is the granularity of the erase operation.
* Flash sector (4096) is the granularity of the write protection.

### Supported Board Variants

* NUCLEO-L073RZ
* DISCO-L072CZ-LRWAN1
* EVAL-STRKT01

All boards support a 192 KB flash L0 part.
The LRWAN1 and STRTK01 boards use a CMWX1ZZABZ-091 module from Murata housing an STM32L072RZ.
All boards have an ST-supplied BSP that defines the status LED and push button.

The resources we use are COM UART, push button for user trigger of Ymodem flash loader in bootloader.

| Board | COM Uart | Button | LED | 
|---|---|---|---|
| NUCLEO-L073RZ | USART2/STLINK | USART1 | PB1/PC13 | LD2/PA5 | 
| DISCO-B-L072Z-LRWAN1 | USART2/STLINK | | PB1/PB2 | LD1/PB5 |
| EVAL-STRKT01 | USART2_TX (PA2) | USER_BUTTON/SW500/PB13 | LED1/PB2 |


