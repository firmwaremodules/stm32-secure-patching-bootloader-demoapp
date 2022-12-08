## STM32 Secure Patching Bootloader Demo App

STM32 Secure Patching Bootloader and Firmware Update System Demonstration Application.

*Please note that this repository has been deprecated in favor of the reference designs integrated with selected STM32Cube projects in the repositories found here:*

* https://github.com/firmwaremodules/STM32CubeL4
* https://github.com/firmwaremodules/STM32CubeF4

<hr>

### Setup

This repository uses submodules - references to other repositories - including to the [bootloader](https://github.com/firmwaremodules/stm32-secure-patching-bootloader) and to various STM32 HAL and BSP [components](https://github.com/STMicroelectronics/STM32Cube_MCU_Overall_Offer).

* Clone the repository with `--recursive` : `git clone --recursive https://github.com/firmwaremodules/stm32-secure-patching-bootloader-demoapp`
* Or, if you've already cloned it without `--recursive`, use : `git submodule update --init`

Open STM32CubeIDE and create a new workspace (anywhere, any name, doesn't matter).  Then import projects directly : 

1. File -> Import Projects from File System... 
2. Select Directory... button to navigate to the project dir, for example to `App\Project\DemoApp\DISCO-F769I\STM32CubeIDE\DemoApp_DISCO-F769I`.  
3. Click `Select Folder` on the project directory `DemoApp_DISCO-F769I`.
4. Leave other options at defaults.  All we're doing is importing this ready-to-go project into the workspace.

### Building

Right-click the project, for example `DemoApp_DISCO-F769I` and select `Build Project` from drop-down menu.

It will build the sources then run the postbuild script to generate the artifacts in the `App\Project\Binary` directory.  The STM32CubeIDE build console will contain outputs like this:

```
Finished building target: DemoApp_DISCO-F769I.elf
 
arm-none-eabi-size   DemoApp_DISCO-F769I.elf 
arm-none-eabi-objdump -h -S  DemoApp_DISCO-F769I.elf  > "DemoApp_DISCO-F769I.list"
   text	   data	    bss	    dec	    hex	filename
2636744	    168	   2872	2639784	 2847a8	DemoApp_DISCO-F769I.elf
Finished building: default.size.stdout
 
Finished building: DemoApp_DISCO-F769I.list
 
"../../../../../../../Bootloader/Scripts/STM32CubeIDE/postbuild.sh" "DemoApp_DISCO-F769I" "../../Keys" "../../../../../Binary" "1.0.0" "1.0.0" "DISCO-F769I" "v1.0.0" 1024 0x90000000
Running postbuild
Using:
- C:/fm/github/stm32-secure-patching-bootloader-demoapp/Bootloader/Scripts/STM32CubeIDE
- C:/fm/github/stm32-secure-patching-bootloader-demoapp/Bootloader/Tools
- C:/fm/github/stm32-secure-patching-bootloader-demoapp/Bootloader/Libs
- C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/DemoApp/DISCO-F769I/STM32CubeIDE/DemoApp_DISCO-F769I/Debug
- C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/DemoApp/DISCO-F769I/STM32CubeIDE/Keys
- C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/Binary
- C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/DemoApp/DISCO-F769I/STM32CubeIDE/DemoApp_DISCO-F769I/Debug/output.txt
- DemoApp_DISCO-F769I
- 1.0.0
- 1.0.0
- DISCO-F769I
- v1.0.0
- 1024
- 0x90000000
Using version=1.0.0 from 1.0.0
machine type is V7M
Using stm32-secure-patching-bootloader_DISCO-F769I_v1.0.0.bin
Made C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/Binary/DemoApp_DISCO-F769I_1.0.0.sfb
Made C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/Binary/BOOT_DemoApp_DISCO-F769I_1.0.0.hex
Postbuild finished.
```

### Running

You must use a dedicated flash programmer like [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) to program the target board.

You will be programming the resultant `.hex` or `.bin` file, beginning with `BOOT_`. Both are equivalent.  `.bin` is not produced if a *multisegment* stm32-secure-patching-bootloader is used.

If the DemoApp is targeting a board with external flash and the multisegment feature is enabled (as shown by 0x90000000 in the postbuild.sh script arguments), make sure that you select the appropriate external flash loader in STM32CubeProgrammer.

After programming, press the reset button on the board.  Observe the output on the STLINK UART @ 115200 N81 (most boards).

This example is for the *DemoApp_DISCO-F769I* project:

```
[  0.000] Bootloader starting up.
STM32 Secure Patching Bootloader. github.com/firmwaremodules/stm32-secure-patching-bootloader
Build: v1.0.0
Registered to: unregistered
Target: DISCO-F769I
UID: 0651383269396431
Clock:HSE,25,216 Crypto:SW UART:1,115200,N81
SLOT0:08040000 SLOT1:90400000 SIZE:5C0000
APP RAMSTART:20022700 VTOR:08040400
[  0.029] Target check: CPUID:411FC270 IDCODE:10016451 FLASHSZ:0800 .. OK.
[  1.370] Verify bootloader.
[  1.427] SHA256: 5b766ae8eb673e36b47d047cacf9b342dcafc72057d49753d013eab9781dba7c Valid
[  1.435] UART loader check trigger.
[  1.438] Check USB flash media.
[  2.441] No valid firmware found on flash media, status=1
[  2.447] Verify slot 1 header.
[  2.666] Slot 1 is empty.
[  2.668] Verify slot 0.
[  2.671] Verify slot 0 header.
[  2.903] Verify slot 0 signature.
[  5.493] Verify slot 0 ready.
[  5.496] Verify slot 0 fw ver.
[  5.729] Slot 0 has valid active firmware version 1.0.0
[  5.734] Preparing to launch application in slot 0.

DemoApp starting...

-----------------------------------------------------------------------------------
      stm32-secure-patching-bootloader Demo Application

      https://github.com/firmwaremodules/stm32-secure-patching-bootloader-demoapp
------------------------------------------------------------------------------------
Board: DISCO-F769I
FW Build: v1.0.0
Firmware Info:
  FW Version (from header): 1.0.0
  ActiveFwSize: 2637120 bytes
  ActiveFwTag: 481aded4d0aa596a4f5f6e16e7dd2834e892dcf06f9fe4b25816c7f7a9aebb4f
QSPI string: Version 1



------------------- Main Menu ----------------------------

  Download a new firmware image or patch via YMODEM ----- 1

  Get active firmware info ------------------------------ 2
```

### Updating

To perform an update on a target, you have three options depending on target board support:

1. **YMODEM over UART from bootloader** - press and hold 'user button' while booting on board to trigger [all boards]
2. **YMODEM over UART from application** - use menu [all boards]  
3. **USB Flash Drive** [boards with USB host support]

In all cases, you have to supply an **.sfb** or **.sfbp** file that was produced from a build.  You cannot update from v1.0.0 to v1.0.0, so you have to build a new, higher,xxxxxxxxxxxx version.  This is easily accomplished in the DemoApps by performing two steps:

1. In `project.h` change `#define FW_UPDATE_VERSION                       2`.  _This is neccessary is create a binary difference between the images for a patch to be generated_.  With no binary difference, no patch is generated, but the full image is still made and can still be used to update to.
2. Change the `to` version in the Postbuild Steps command line argument (STM32CubeIDE -> RightClick Project -> Properties -> C/C++ Build -> Settings -> Build Steps) : `.... "../../../../../Binary" "1.1.0" "1.0.0" "DISCO-F769I" ....` Here we have selected to build a new version **"1.1.0"** with version **"1.0.0"** as the patch reference.

Rebuild the project.  Ensure you see the following artifacts made in the build console:

```
Made C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/Binary/DemoApp_DISCO-F769I_1.1.0.sfb
Made C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/Binary/BOOT_DemoApp_DISCO-F769I_1.1.0.hex
Made C:/fm/github/stm32-secure-patching-bootloader-demoapp/App/Project/Binary/DemoApp_DISCO-F769I_1.0.0_1.1.0.sfbp
```

Place the `DemoApp_DISCO-F769I_1.1.0.sfb` or `DemoApp_DISCO-F769I_1.0.0_1.1.0.sfbp` onto the root directory of a flash drive (best to have the flash drive empty but usually not necessary) and insert it into the USB host port (A USB OTG cable adapter is usually needed).  Reboot the board and observe the update and installation occur all in one go!

This example below uses the patch file `DemoApp_DISCO-F769I_1.0.0_1.1.0.sfbp`:

```
[  0.000] Bootloader starting up.
STM32 Secure Patching Bootloader. github.com/firmwaremodules/stm32-secure-patching-bootloader
Build: v1.0.0
Registered to: unregistered
Target: DISCO-F769I
UID: 0651383269396431
Clock:HSE,25,216 Crypto:SW UART:1,115200,N81
SLOT0:08040000 SLOT1:90400000 SIZE:5C0000
APP RAMSTART:20022700 VTOR:08040400
[  0.029] Target check: CPUID:411FC270 IDCODE:10016451 FLASHSZ:0800 .. OK.
[  1.370] Verify bootloader.
[  1.427] SHA256: 5b766ae8eb673e36b47d047cacf9b342dcafc72057d49753d013eab9781dba7c Valid
[  1.435] UART loader check trigger.
[  1.438] Check USB flash media.
[  2.982] Open update file [DemoApp_NUCLEO-F429ZI_1.0.0_2.0.0.sfbp] 304 bytes
[  3.211] Update file rejected @ 272/272 status:3
[  3.448] Open update file [DemoApp_DISCO-F769I_1.0.0_1.1.0.sfbp] 304 bytes
[................                ] 50%
[ 28.930] Firmware patched from flash media and ready to install, status=1
[ 28.937] Verify slot 1 header.
[ 29.157] Slot 1 has firmware header.
[ 29.378] Slot 1 is ready.
[ 29.381] Check for update.
[ 29.383] Verify slot 0.
[ 29.385] Verify slot 0 header.
[ 29.618] Verify slot 0 signature.
[ 32.234] Verify slot 0 ready.
[ 32.236] Verify slot 0 fw ver.
[ 32.469] Slot 0 has valid active firmware version 1.0.0
[ 32.474] Slot 1 firmware 1.1.0 is newer.
[ 32.478] Prepare for update.
[ 32.480] Verify slot 1 signature.
[ 37.837] Erase slot 0.
[................                ] 50%
[ 45.588] Copy slot 1 to slot 0.
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
[ 60.522] Slot 0 validated.
[ 60.525] Verify slot 0.
[ 60.527] Verify slot 0 header.
[ 60.747] Verify slot 0 signature.
[ 63.363] Slot 0 has valid firmware.
[ 63.366] Preparing to launch application in slot 0.

DemoApp starting...

-----------------------------------------------------------------------------------
      stm32-secure-patching-bootloader Demo Application

      https://github.com/firmwaremodules/stm32-secure-patching-bootloader-demoapp
------------------------------------------------------------------------------------
Board: DISCO-F769I
FW Build: v1.0.0-dirty
Firmware Info:
  FW Version (from header): 1.1.0
  ActiveFwSize: 2637120 bytes
  ActiveFwTag: 5b0421b44e23f3bfab1b9fd2f4f6d3410f1bf817f1e8cde2c09dc7c265058be7
QSPI string: Version 2



------------------- Main Menu ----------------------------

  Download a new firmware image or patch via YMODEM ----- 1

  Get active firmware info ------------------------------ 2
```

To use the YMODEM over UART update method, it has been tested with [TeraTerm](https://ttssh2.osdn.jp/index.html.en) : select File->Transfer->YMODEM->Send when prompted.

### Changing Keys

To generate new random keys for a project, use the `make_keys.bat` script that comes with the the bootloader repository like this:

```
c:\fm\github\stm32-secure-patching-bootloader-demoapp\Bootloader\Scripts>make_keys.bat ..\..\App\Project\DemoApp\DISCO-L496G\STM32CubeIDE\Keys
make_keys.bat : Generate new secure keys for stm32-secure-patching-bootloader
Making ..\..\App\Project\DemoApp\DISCO-L496G\STM32CubeIDE\Keys/Cipher_Key_AES_CBC.bin
Making ..\..\App\Project\DemoApp\DISCO-L496G\STM32CubeIDE\Keys/Signing_PrivKey_ECC.txt
```


