## Key Management

The bootloader and secure firmware update security system consists of two private keys: 

* AES-CBC key (encryption - confidentiality) 
* ECDSA key (signing - authentication)

The `prepareimage.py` tool is used for generating both keys.

These keys must be unique to each project to prevent loading wrong firmware.

**These keys are the means by which the the bootloader accepts or rejects firmware for a given product** 

Do not use the same keys for multiple projects/products or the bootloader in one product could
update to firmware meant for another product.

Use the `make_keys.bat` convenience script located in the bootloader `Scripts` directory to generate the keys
automatically in the specified project `Keys` directory, or follow these manual steps:

Open a console window to `Tools` and run these commands:

1. `python prepareimage.py keygen -k Cipher_Key_AES_CBC.bin -t aes-cbc`
2. `python prepareimage.py keygen -k Signing_PrivKey_ECC.txt -t ecdsa-p256`
5. Add and/or commit changes to these 2 files into the project's `Keys` directory.

`machine.txt` must exist, and must contain either `V7M` for a non-Cortex-M0 target,
or `V6M` for a Cortex-M0 target.


