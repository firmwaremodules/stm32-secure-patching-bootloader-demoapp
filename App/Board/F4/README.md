## STM32F4 Board

* Vector offset is 512 bytes.

Really bizarre:
* Flash program type is WORD (x32).  DOUBLE WORD (x64) only works with external Vpp voltage applied!

"Any program or erase operation started with inconsistent program parallelism/voltage range
settings may lead to unpredicted results. Even if a subsequent read operation indicates that
the logical value was effectively written to the memory, this value may not be retained.
To use VPP, an external high-voltage supply (between 8 and 9 V) must be applied to the VPP
pad. The external supply must be able to sustain this voltage range even if the DC
consumption exceeds 10 mA. It is advised to limit the use of VPP to initial programming on
the factory line. The VPP supply must not be applied for more than an hour, otherwise the
Flash memory might be damaged."

