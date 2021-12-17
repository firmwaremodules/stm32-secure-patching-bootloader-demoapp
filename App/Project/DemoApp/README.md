```
------------------- Main Menu ----------------------------

  Download a new firmware image or patch via YMODEM ----- 1

  Get active firmware info ------------------------------ 2

---------------- YMODEM Firmware Patch Updater -------------------------

  -- Send Firmware

  -- -- File> Transfer> YMODEM> Send ...........................................................................................................................

  -- -- Slot 1 download completed: (1)

  -- -- Bytes: 1488

  -- Image correctly downloaded (status=0) - reboot


[  0.001] Bootloader starting up.
STM32 Secure Patching Bootloader. github.com/firmwaremodules/stm32-secure-patching-bootloader
Build: v1.0.0
Registered to: unregistered
Target: NUCLEO-L073RZ
UID: 333934375d359114
Clock:HSI,32 Crypto:SW UART:2,115200,N81
SLOT0:0800E000 SLOT1:0801F000 SIZE:11000
APP RAMSTART:20001500 VTOR:0800E200
[  0.029] Target check: CPUID:410CC601 IDCODE:20086447 FLASHSZ:00C0 .. OK.
[  0.036] Verify bootloader.
[  0.252] SHA256: c4385f90d6b5852899059c8e7f05222265c6725862c7cc2536702ca420006bae Valid
[  0.261] UART loader check trigger.
[  0.264] Verify slot 1 header.
[  2.713] Slot 1 has firmware header.
[  5.162] Slot 1 is ready.
[  5.165] Check for update.
[  5.167] Verify slot 0.
[  5.169] Verify slot 0 header.
[  7.662] Verify slot 0 signature.
[  7.730] Verify slot 0 ready.
[  7.733] Verify slot 0 fw ver.
[ 10.226] Slot 0 has valid active firmware version 1.0.0
[ 10.231] Slot 1 firmware 1.1.0 is newer.
[ 10.235] Prepare for update.
[ 10.238] Verify slot 1 signature.
[ 10.371] Erase slot 0.
[................                ] 50%
[ 12.157] Copy slot 1 to slot 0.
[................                ] 51%
[.................               ] 52%
[.................               ] 53%
[.................               ] 54%
[..................              ] 55%
[..................              ] 56%
[..................              ] 57%
[...................             ] 58%
[...................             ] 59%
[...................             ] 60%
[....................            ] 61%
[....................            ] 62%
[....................            ] 63%
[....................            ] 64%
[.....................           ] 65%
[.....................           ] 66%
[.....................           ] 67%
[......................          ] 68%
[......................          ] 69%
[......................          ] 70%
[.......................         ] 71%
[.......................         ] 72%
[.......................         ] 73%
[........................        ] 74%
[........................        ] 75%
[........................        ] 76%
[.........................       ] 77%
[.........................       ] 78%
[.........................       ] 79%
[..........................      ] 80%
[..........................      ] 81%
[..........................      ] 82%
[...........................     ] 83%
[...........................     ] 84%
[...........................     ] 85%
[............................    ] 86%
[............................    ] 87%
[............................    ] 88%
[............................    ] 89%
[.............................   ] 90%
[.............................   ] 91%
[.............................   ] 92%
[..............................  ] 93%
[..............................  ] 94%
[..............................  ] 95%
[............................... ] 96%
[............................... ] 97%
[............................... ] 98%
[................................] 99%
[................................] 100%
[ 13.237] Slot 0 validated.
[ 13.240] Verify slot 0.
[ 13.242] Verify slot 0 header.
[ 15.691] Verify slot 0 signature.
[ 15.759] Slot 0 has valid firmware.
[ 15.762] Preparing to launch application in slot 0.

DemoApp starting...

----------------------------------------------------------------------
      stm32-secure-patching-bootloader Demo Application

      https://github.com/stm32-secure-patching-bootloader-demoapp
----------------------------------------------------------------------
Board: L073RZ-NUCLEO
FW Build: v1.0.0-dirty
Firmware Info:
  FW Version: 1.1.0
  ActiveFwSize: 15232 bytes
  ActiveFwTag: e92e9add509848bb9f7f0640dbc4266ef8c48d652ebfc967ae89b57465ed31df
Version 2



------------------- Main Menu ----------------------------

  Download a new firmware image or patch via YMODEM ----- 1

  Get active firmware info ------------------------------ 2

```
