	.section .SE_Key_Data,"a",%progbits
 .syntax unified 
 .thumb 

      	.global SE_ReadKey
SE_ReadKey:
	PUSH {R1-R5}
	MOVW R1, #0x6754
	MOVT R1, #0xc2d5
	MOVW R2, #0xc937
	MOVT R2, #0x70cb
	MOVW R3, #0x55b0
	MOVT R3, #0x799a
	MOVW R4, #0xb831
	MOVT R4, #0x497b
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR

	.global SE_ReadKey_Pub
SE_ReadKey_Pub:
	PUSH {R1-R5}
	MOVW R1, #0x96db
	MOVT R1, #0x76b3
	MOVW R2, #0xdf3
	MOVT R2, #0x2261
	MOVW R3, #0xe2ba
	MOVT R3, #0x9dd2
	MOVW R4, #0xa602
	MOVT R4, #0xc48a
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x5161
	MOVT R1, #0x3608
	MOVW R2, #0xe01b
	MOVT R2, #0x22ee
	MOVW R3, #0x611b
	MOVT R3, #0xd950
	MOVW R4, #0xdd27
	MOVT R4, #0xf6a
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x78ad
	MOVT R1, #0xa47d
	MOVW R2, #0xae3
	MOVT R2, #0x951f
	MOVW R3, #0x642
	MOVT R3, #0x6857
	MOVW R4, #0x1687
	MOVT R4, #0xcea6
	STM R0, {R1-R4}
	ADD R0, R0,#16
	MOVW R1, #0x1474
	MOVT R1, #0xc796
	MOVW R2, #0x38e5
	MOVT R2, #0x2c50
	MOVW R3, #0x3812
	MOVT R3, #0xe583
	MOVW R4, #0xa387
	MOVT R4, #0x405e
	STM R0, {R1-R4}
	POP {R1-R5}
	BX LR
	.end
