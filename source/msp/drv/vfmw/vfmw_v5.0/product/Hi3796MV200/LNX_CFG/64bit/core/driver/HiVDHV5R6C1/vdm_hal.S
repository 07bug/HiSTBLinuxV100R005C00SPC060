#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VDMHAL_V5R6C1_CfgRpReg.isra.9, %function
VDMHAL_V5R6C1_CfgRpReg.isra.9:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	mov	x22, x1
	mov	x20, x3
	bl	_mcount
	cmp	w21, wzr
	str	wzr, [x29, 60]
	bgt	.L28
	ldr	x0, [x19]
	cbz	x0, .L29
.L4:
	ldr	x19, .LC5
	ldr	w3, [x22]
	ldrb	w0, [x19]
	and	w3, w3, -16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L30
	mov	x0, x20
	mov	w2, 16
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	mov	w3, 53763
	movk	w3, 0x2000, lsl 16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L31
	mov	x0, x20
	mov	w2, 12
	mov	w1, 2
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	VDH_Record_RegData
	str	w22, [x29, 60]
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L32
	mov	x0, x20
	mov	w3, w22
	mov	w2, 60
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L33
	mov	x0, x20
	mov	w3, w22
	mov	w2, 64
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L34
	mov	x0, x20
	mov	w3, w22
	mov	w2, 68
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L35
	mov	x0, x20
	mov	w3, w22
	mov	w2, 72
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L36
	mov	x0, x20
	mov	w3, w22
	mov	w2, 76
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L37
	mov	x0, x20
	mov	w3, w22
	mov	w2, 80
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L38
	mov	x0, x20
	mov	w3, w22
	mov	w2, 84
	mov	w1, 2
	bl	VDH_Record_RegData
	mov	w0, 0
.L24:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L30:
	sxtw	x2, w21
	ldr	x1, .LC6
	lsl	x0, x2, 6
	sub	x0, x0, x2
	lsl	x0, x0, 2
	sub	x4, x0, x2
	add	x0, x0, x4, lsl 2
	ldr	x0, [x1, x0]
	str	w3, [x0, 16]
.L7:
	lsl	x0, x2, 6
	mov	w4, 53763
	sub	x0, x0, x2
	movk	w4, 0x2000, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x2
	add	x0, x0, x3, lsl 2
	ldr	x0, [x1, x0]
	str	w4, [x0, 12]
.L9:
	lsl	x0, x2, 6
	mov	w4, 3075
	sub	x0, x0, x2
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x2
	add	x0, x0, x3, lsl 2
	ldr	x0, [x1, x0]
	str	w4, [x0, 60]
.L11:
	lsl	x0, x2, 6
	mov	w4, 3075
	sub	x0, x0, x2
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x2
	add	x0, x0, x3, lsl 2
	ldr	x0, [x1, x0]
	str	w4, [x0, 64]
.L13:
	lsl	x0, x2, 6
	mov	w4, 3075
	sub	x0, x0, x2
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x2
	add	x0, x0, x3, lsl 2
	ldr	x0, [x1, x0]
	str	w4, [x0, 68]
.L15:
	lsl	x0, x2, 6
	mov	w4, 3075
	sub	x0, x0, x2
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x2
	add	x0, x0, x3, lsl 2
	ldr	x0, [x1, x0]
	str	w4, [x0, 72]
.L17:
	lsl	x0, x2, 6
	mov	w4, 3075
	sub	x0, x0, x2
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x2
	add	x0, x0, x3, lsl 2
	ldr	x0, [x1, x0]
	str	w4, [x0, 76]
.L19:
	lsl	x0, x2, 6
	mov	w4, 3075
	sub	x0, x0, x2
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x2
	add	x0, x0, x3, lsl 2
	ldr	x0, [x1, x0]
	str	w4, [x0, 80]
.L21:
	lsl	x3, x2, 6
	mov	w4, 3075
	sub	x3, x3, x2
	movk	w4, 0x30, lsl 16
	lsl	x3, x3, 2
	mov	w0, 0
	sub	x2, x3, x2
	add	x2, x3, x2, lsl 2
	ldr	x1, [x1, x2]
	str	w4, [x1, 84]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L29:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L5
	str	x0, [x19]
	b	.L4
	.p2align 3
.L28:
	ldr	x2, .LC0
	mov	w4, 0
	ldr	x1, .LC2
	mov	w3, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L24
.L5:
	ldr	x1, .LC4
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L24
.L35:
	ldr	x1, .LC6
	sxtw	x2, w21
	b	.L15
.L34:
	ldr	x1, .LC6
	sxtw	x2, w21
	b	.L13
.L33:
	ldr	x1, .LC6
	sxtw	x2, w21
	b	.L11
.L32:
	ldr	x1, .LC6
	sxtw	x2, w21
	b	.L9
.L37:
	ldr	x1, .LC6
	sxtw	x2, w21
	b	.L19
.L36:
	ldr	x1, .LC6
	sxtw	x2, w21
	b	.L17
.L38:
	ldr	x1, .LC6
	sxtw	x2, w21
	b	.L21
.L31:
	ldr	x1, .LC6
	sxtw	x2, w21
	b	.L7
	.size	VDMHAL_V5R6C1_CfgRpReg.isra.9, .-VDMHAL_V5R6C1_CfgRpReg.isra.9
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LC1
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC5:
	.xword	g_HalDisable
	.align	3
.LC6:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetHalMemSize
	.type	VDMHAL_V5R6C1_GetHalMemSize, %function
VDMHAL_V5R6C1_GetHalMemSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 6291456
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_GetHalMemSize, .-VDMHAL_V5R6C1_GetHalMemSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_OpenHAL
	.type	VDMHAL_V5R6C1_OpenHAL, %function
VDMHAL_V5R6C1_OpenHAL:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L52
	ldp	w23, w22, [x19]
	ldr	w19, [x19, 8]
	cbz	w23, .L53
	mov	w0, 6291455
	cmp	w22, w0
	ble	.L54
	cmp	w19, wzr
	bgt	.L55
	sxtw	x20, w19
	ldr	x25, .LC21
	ldr	x21, .LC22
	mov	x2, 268
	add	x0, x20, x20, lsl 4
	mov	w1, 0
	lsl	x0, x0, 2
	ldr	x3, [x25, 96]
	sub	x0, x0, x20
	add	x0, x21, x0, lsl 2
	blr	x3
	ldr	x24, .LC7
	lsl	x0, x20, 6
	ldr	x3, [x25, 96]
	sub	x0, x0, x20
	mov	w1, 4
	lsl	x0, x0, 2
	str	w1, [x21]
	sub	x25, x0, x20
	mov	x2, 1256
	mov	w1, 0
	add	x25, x0, x25, lsl 2
	add	x21, x24, x25
	mov	x0, x21
	blr	x3
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	mov	x2, x0
	ldr	x1, .LC24
	str	x0, [x24, x25]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 53248
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_Phy2Vir
	mov	x2, x0
	ldr	x1, .LC26
	str	x0, [x21, 16]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1256
	add	w4, w23, 1023
	and	w4, w4, -1024
	add	w1, w23, w22
	smull	x19, w19, w0
	sub	w1, w1, w4
	mov	w2, 1024
	add	x0, x19, 56
	add	x19, x19, 896
	stp	w4, w1, [x21, 32]
	str	w2, [x21, 40]
	add	x0, x24, x0
	add	x2, x24, x19
	mov	w1, w4
	.p2align 2
.L46:
	str	w1, [x0], 4
	add	w1, w1, 1280
	cmp	x0, x2
	bne	.L46
	lsl	x0, x20, 6
	add	w2, w4, 266240
	sub	x0, x0, x20
	add	w2, w2, 3072
	lsl	x0, x0, 2
	add	w3, w2, 4096
	sub	x20, x0, x20
	mov	w7, 210
	add	w3, w3, 1024
	add	x0, x0, x20, lsl 2
	add	w1, w3, 32768
	add	x0, x24, x0
	add	w1, w1, 1023
	and	w1, w1, -32768
	add	w4, w1, 4427776
	add	w5, w1, 4370432
	str	w7, [x0, 1080]
	add	x7, x0, 1024
	add	w4, w4, 1024
	add	w5, w5, 2048
	add	w6, w1, 589824
	add	w8, w1, 45056
	stp	w2, w1, [x7, 80]
	stp	w1, w1, [x7, 88]
	str	w3, [x0, 1124]
	add	w3, w1, 1773568
	add	w3, w3, 1152
	add	w7, w1, 1093632
	add	w2, w1, 4390912
	cmp	w4, w3
	add	w2, w2, 1024
	str	w7, [x0, 1164]
	add	w7, w1, 4423680
	str	w5, [x0, 1192]
	str	w3, [x0, 1152]
	add	w5, w1, 4374528
	str	w2, [x0, 1204]
	add	w5, w5, 1024
	str	w2, [x0, 1220]
	csel	w2, w4, w3, cs
	add	w3, w7, 1024
	str	w3, [x0, 1200]
	add	w3, w1, 1769472
	add	w4, w6, 2048
	add	w3, w3, 2048
	str	w5, [x0, 1196]
	sub	w2, w2, w23
	add	w5, w1, 1179648
	add	w5, w5, 2048
	str	w1, [x0, 1172]
	str	w4, [x0, 1132]
	cmp	w22, w2
	add	w4, w1, 2142208
	str	w3, [x0, 1144]
	str	w3, [x0, 1148]
	add	w3, w1, 3190784
	str	w6, [x0, 1120]
	add	w1, w1, 4239360
	str	w6, [x0, 1128]
	str	wzr, [x0, 1156]
	str	w8, [x0, 1160]
	str	wzr, [x0, 1184]
	str	w5, [x0, 1136]
	str	w5, [x0, 1140]
	str	w4, [x0, 1168]
	str	w3, [x0, 1176]
	str	w1, [x0, 1208]
	bcc	.L47
	mov	x0, x21
	bl	H264HAL_V5R6C1_InitHal
	cmp	w0, wzr
	mov	x0, x21
	csetm	w19, ne
	bl	HEVCHAL_V5R6C1_InitHal
	cmp	w0, wzr
	csinv	w19, w19, wzr, eq
.L42:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L55:
	ldr	x1, .LC20
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L47:
	ldr	x1, .LC28
	mov	w3, w22
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L42
.L53:
	ldr	x2, .LC12
	ldr	x3, .LC16
.L51:
	ldr	x1, .LC14
	add	x2, x2, 24
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L42
.L54:
	ldr	x2, .LC12
	ldr	x3, .LC18
	b	.L51
.L52:
	ldr	x2, .LC12
	ldr	x3, .LC11
	b	.L51
	.size	VDMHAL_V5R6C1_OpenHAL, .-VDMHAL_V5R6C1_OpenHAL
	.align	3
.LC7:
	.xword	g_HwMem
	.align	3
.LC11:
	.xword	.LC10
	.align	3
.LC12:
	.xword	.LANCHOR0
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC16:
	.xword	.LC15
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC21:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC22:
	.xword	g_VdmExtParam
	.align	3
.LC24:
	.xword	.LC23
	.align	3
.LC26:
	.xword	.LC25
	.align	3
.LC28:
	.xword	.LC27
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CloseHAL
	.type	VDMHAL_V5R6C1_CloseHAL, %function
VDMHAL_V5R6C1_CloseHAL:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_CloseHAL, .-VDMHAL_V5R6C1_CloseHAL
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CalcFsSize
	.type	VDMHAL_V5R6C1_CalcFsSize, %function
VDMHAL_V5R6C1_CalcFsSize:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	mov	w25, w1
	mov	w26, w2
	mov	w23, w3
	mov	w24, w4
	mov	x21, x5
	bl	_mcount
	sub	w1, w25, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L58
	sub	w1, w26, #32
	mov	w8, w26
	cmp	w1, w0
	bhi	.L58
	add	w0, w25, 15
	add	w20, w26, 15
	asr	w0, w0, 4
	ldr	x1, .LC33
	mov	w2, 36
	asr	w20, w20, 4
	cmp	w0, 45
	mov	w19, 32
	ccmp	w20, w2, 0, le
	ldrb	w1, [x1]
	cset	w4, le
	mov	w2, 64
	cmp	w4, wzr
	lsl	w3, w0, 4
	csel	w19, w19, w2, eq
	cmp	w1, 1
	csel	w19, w19, w2, ne
	cmp	w24, 16
	beq	.L63
	cmp	w24, 17
	beq	.L89
	mul	w19, w0, w19
	sub	w0, w24, #17
	cmp	w0, 1
	mul	w19, w19, w20
	add	w19, w19, 143
	and	w19, w19, -128
	asr	w4, w19, 1
	bls	.L64
	ldr	x27, .LC34
	add	w3, w3, 255
	add	w8, w26, 31
	and	w28, w3, -256
	and	w8, w8, -32
	mov	w5, 0
	ldr	x7, [x27, w22, sxtw 3]
	mov	w6, 0
.L66:
	ldr	w0, [x7, 1280]
	cmp	w0, 1
	beq	.L90
	mov	w26, 0
	mov	w3, 0
	mov	w25, 0
.L67:
	cmp	w23, 1
	mul	w23, w8, w28
	beq	.L91
	mul	w2, w5, w6
	lsl	w1, w25, 2
	lsl	w0, w2, 2
	sub	w1, w1, w25
	sub	w2, w0, w2
	lsl	w0, w23, 2
	sub	w0, w0, w23
	lsr	w0, w0, 1
	add	w0, w0, w2, lsr 1
	add	w20, w0, w1, lsr 1
.L69:
	add	x2, x7, 503808
	ldr	w0, [x2, 1624]
	cbz	w0, .L92
.L70:
	add	x0, x7, 507904
	cmp	w24, 17
	str	w20, [x0, 1096]
	str	w3, [x2, 3972]
	str	w26, [x2, 3976]
	str	w4, [x2, 4012]
	beq	.L71
	ldr	w1, [x2, 1632]
	mov	w0, 32
	cmp	w1, 32
	csel	w0, w1, w0, le
	str	w0, [x2, 4016]
	ldr	w0, [x7, 664]
	cmp	w0, 2
	beq	.L93
.L72:
	lsl	w3, w28, 4
	sub	w24, w24, #16
	add	w0, w25, w23
	str	w3, [x2, 3964]
	cmp	w24, 2
	lsr	w3, w3, 1
	str	w0, [x2, 3996]
	str	w3, [x2, 3968]
	bls	.L73
.L74:
	ldr	x0, [x27, w22, sxtw 3]
	mov	w4, 1024
	add	w1, w20, 1056
	add	x3, x0, 507904
	add	w2, w1, w19
	add	w5, w2, w4
	str	w19, [x3, 1100]
	str	w4, [x3, 1108]
	ldrsb	w0, [x0, 44]
	cmp	w0, 1
	csel	w2, w5, w2, eq
	cbz	x21, .L84
	str	w1, [x21, 4]
	mov	w0, 0
	ldr	x3, [x27, w22, sxtw 3]
	add	x3, x3, 503808
	ldr	w3, [x3, 1632]
	stp	w3, w19, [x21, 8]
	ldr	x3, [x27, w22, sxtw 3]
	add	x3, x3, 503808
	ldr	w3, [x3, 4016]
	stp	w3, w4, [x21, 16]
	str	w2, [x21]
	ldr	x2, [x27, w22, sxtw 3]
	add	x2, x2, 507904
	str	w1, [x2, 1104]
.L85:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L71:
	lsl	w3, w28, 4
	mov	w0, 1
	str	w3, [x2, 3964]
	lsr	w3, w3, 1
	str	w0, [x2, 4016]
	add	w0, w25, w23
	str	w3, [x2, 3968]
	str	w0, [x2, 3996]
.L73:
	ldr	w0, [x7, 1612]
	cmp	w0, 8
	ble	.L74
	lsl	w0, w23, 2
	ldr	x1, .LC37
	sub	w23, w0, w23
	lsl	w0, w25, 2
	sub	w25, w0, w25
	mov	w0, 31
	mul	w5, w5, w6
	lsr	w25, w25, 1
	lsl	w6, w6, 5
	add	w23, w25, w23, lsr 1
	str	w6, [x2, 3980]
	str	w23, [x2, 3988]
	str	w5, [x2, 3992]
	bl	dprint_vfmw
	b	.L74
	.p2align 3
.L92:
	ldr	x1, .LC35
	add	x0, x2, 3960
	mov	x2, 1248
	stp	w4, w3, [x29, 96]
	ldr	x7, [x1, 96]
	mov	w1, 0
	stp	w6, w5, [x29, 104]
	blr	x7
	ldr	x7, [x27, w22, sxtw 3]
	ldp	w4, w3, [x29, 96]
	add	x2, x7, 503808
	ldp	w6, w5, [x29, 104]
	b	.L70
	.p2align 3
.L91:
	lsl	w1, w20, 6
	sub	w20, w1, w20, lsl 4
	mul	w20, w20, w28
	b	.L69
	.p2align 3
.L90:
	adds	w3, w25, 2047
	add	w25, w25, 4094
	csel	w25, w25, w3, mi
	add	w0, w26, 126
	and	w25, w25, -2048
	cmp	w25, wzr
	add	w3, w25, 127
	csel	w3, w3, w25, lt
	adds	w25, w26, 63
	csel	w25, w0, w25, mi
	asr	w3, w3, 7
	asr	w25, w25, 6
	lsl	w25, w25, 5
	mul	w25, w25, w3
	mov	w26, w25
	b	.L67
	.p2align 3
.L63:
	ldr	x27, .LC34
	mul	w19, w20, w3
	add	w3, w25, 255
	ldr	x7, [x27, w22, sxtw 3]
	add	w19, w19, 143
	and	w28, w3, -256
	and	w19, w19, -128
	ldr	w0, [x7, 1612]
	cmp	w0, 8
	ble	.L94
	add	w5, w26, 31
	lsr	w6, w28, 2
	and	w5, w5, -32
	asr	w4, w19, 1
	b	.L66
	.p2align 3
.L89:
	mov	w4, 64
	mov	w19, 128
	movk	w4, 0x12, lsl 16
	movk	w19, 0x24, lsl 16
.L64:
	ldr	x27, .LC34
	add	w3, w25, 255
	add	w8, w26, 63
	and	w28, w3, -256
	and	w8, w8, -64
	ldr	x7, [x27, w22, sxtw 3]
	ldr	w0, [x7, 1612]
	cmp	w0, 8
	ble	.L82
	lsr	w6, w28, 2
	mov	w5, w8
	b	.L66
	.p2align 3
.L94:
	asr	w4, w19, 1
	mov	w5, 0
	mov	w6, 0
	b	.L66
	.p2align 3
.L93:
	add	w1, w1, 1
	str	w1, [x2, 4016]
	b	.L72
	.p2align 3
.L84:
	mov	w0, 0
	b	.L85
	.p2align 3
.L82:
	mov	w5, 0
	mov	w6, 0
	b	.L66
	.p2align 3
.L58:
	ldr	x2, .LC31
	mov	w0, 0
	ldr	x3, .LC30
	ldr	x1, .LC32
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L85
	.size	VDMHAL_V5R6C1_CalcFsSize, .-VDMHAL_V5R6C1_CalcFsSize
	.align	3
.LC30:
	.xword	.LC29
	.align	3
.LC31:
	.xword	.LANCHOR0
	.align	3
.LC32:
	.xword	.LC13
	.align	3
.LC33:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC34:
	.xword	s_pstVfmwChan
	.align	3
.LC35:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC37:
	.xword	.LC36
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetRpuSize
	.type	VDMHAL_V5R6C1_GetRpuSize, %function
VDMHAL_V5R6C1_GetRpuSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1024
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_GetRpuSize, .-VDMHAL_V5R6C1_GetRpuSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CalcFsNum
	.type	VDMHAL_V5R6C1_CalcFsNum, %function
VDMHAL_V5R6C1_CalcFsNum:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x19, x3
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L101
	cmp	w21, 17
	ldr	x1, .LC41
	beq	.L102
	ldr	x4, [x1, w20, sxtw 3]
	mov	w2, 32
	add	x3, x4, 503808
	ldr	w0, [x3, 1632]
	cmp	w0, w2
	csel	w2, w0, w2, le
	str	w2, [x3, 4016]
	ldr	w2, [x4, 664]
	cmp	w2, 2
	beq	.L103
.L100:
	str	w0, [x19, 8]
	mov	w0, 0
	ldr	x1, [x1, w20, sxtw 3]
	add	x1, x1, 503808
	ldr	w1, [x1, 4016]
	str	w1, [x19, 16]
.L98:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L102:
	ldr	x0, [x1, w20, sxtw 3]
	mov	w2, 1
	add	x0, x0, 503808
	str	w2, [x0, 4016]
	ldr	w0, [x0, 1632]
	b	.L100
	.p2align 3
.L103:
	add	w2, w0, 1
	str	w2, [x3, 4016]
	b	.L100
.L101:
	ldr	x2, .LC38
	mov	w0, 1
	ldr	x1, .LC40
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -1
	b	.L98
	.size	VDMHAL_V5R6C1_CalcFsNum, .-VDMHAL_V5R6C1_CalcFsNum
	.align	3
.LC38:
	.xword	.LANCHOR0
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC41:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_DynamicAllocFrame
	.type	VDMHAL_V5R6C1_DynamicAllocFrame, %function
VDMHAL_V5R6C1_DynamicAllocFrame:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w23, w1
	mov	w22, w2
	mov	x20, x3
	bl	_mcount
	ldr	x21, .LC42
	mov	w0, w19
	ldr	x1, [x21, w19, sxtw 3]
	add	x1, x1, 503808
	add	x1, x1, 1656
	bl	DelAllFrameMemRecord
	cbnz	w0, .L126
.L105:
	ldr	x1, [x21, w19, sxtw 3]
	mov	w2, 255
	add	x1, x1, 503808
	add	x0, x1, 1656
	add	x1, x1, 3960
	.p2align 2
.L106:
	str	w2, [x0], 72
	cmp	x1, x0
	bne	.L106
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 507904
	ldr	w2, [x1, 1736]
	cbnz	w2, .L125
	mov	w2, 1088
	cmp	w23, 1920
	ccmp	w22, w2, 0, le
	ble	.L127
.L125:
	ldr	w1, [x20, 8]
.L108:
	add	x2, x0, 503808
	ldr	w3, [x0, 1560]
	mov	w0, w19
	add	w1, w3, w1
	str	w1, [x2, 1636]
	bl	VCTRL_GetVidStd
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w2, [x1, 664]
	cmp	w2, 2
	ccmp	w0, 17, 4, eq
	beq	.L112
	add	x1, x1, 503808
	ldr	w0, [x1, 1636]
	str	w0, [x20, 16]
	ldr	x1, [x21, w19, sxtw 3]
.L112:
	add	x0, x1, 507904
	add	x1, x1, 475136
	mov	w4, 1
	mov	w3, w22
	mov	w2, w23
	str	wzr, [x0, 1136]
	str	w4, [x1, 2280]
	str	w4, [x0, 1676]
	mov	w0, 31
	ldr	x1, .LC46
	ldr	w4, [x20, 8]
	ldr	w5, [x20, 16]
	bl	dprint_vfmw
	ldr	x0, .LC47
	ldr	x4, [x0]
	cbz	x4, .L113
	ldp	w1, w2, [x20, 12]
	ldp	w3, w5, [x20, 4]
	ldr	w0, [x20, 20]
	stp	w2, w1, [x29, 72]
	stp	w5, w3, [x29, 64]
	stp	w0, w23, [x29, 80]
	str	w22, [x29, 88]
	mov	w3, 28
	add	x2, x29, 64
	mov	w1, 121
	mov	w0, w19
	blr	x4
.L113:
	ldr	x3, .LC48
	mov	x2, 528
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 0
	ldr	x3, [x3, 96]
	add	x0, x0, 507904
	add	x0, x0, 1144
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 507904
	str	wzr, [x1, 1672]
	bl	FSP_ClearContextAll
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
.L127:
	ldr	w2, [x0, 36]
	cmp	w2, 24
	beq	.L125
	ldr	w1, [x1, 1732]
	cbnz	w1, .L125
	ldr	w1, [x20, 8]
	add	w1, w1, 4
	str	w1, [x20, 8]
	ldr	x0, [x21, w19, sxtw 3]
	b	.L108
.L126:
	ldr	x1, .LC44
	mov	w0, 0
	bl	dprint_vfmw
	b	.L105
	.size	VDMHAL_V5R6C1_DynamicAllocFrame, .-VDMHAL_V5R6C1_DynamicAllocFrame
	.align	3
.LC42:
	.xword	s_pstVfmwChan
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC46:
	.xword	.LC45
	.align	3
.LC47:
	.xword	g_event_report
	.align	3
.LC48:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_DynamicAllocFrame_Only
	.type	VDMHAL_V5R6C1_DynamicAllocFrame_Only, %function
VDMHAL_V5R6C1_DynamicAllocFrame_Only:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x3
	mov	w22, w1
	mov	w21, w2
	bl	_mcount
	ldr	x4, .LC49
	mov	w3, w21
	ldr	w5, [x19, 8]
	mov	w2, w22
	ldr	x1, .LC51
	mov	w0, 31
	ldr	x4, [x4, w20, sxtw 3]
	add	x4, x4, 503808
	str	w5, [x4, 1636]
	ldr	w4, [x19, 8]
	ldr	w5, [x19, 16]
	bl	dprint_vfmw
	ldr	x0, .LC52
	ldr	x4, [x0]
	cbz	x4, .L128
	ldp	w1, w2, [x19, 12]
	ldp	w3, w5, [x19, 4]
	ldr	w0, [x19, 20]
	stp	w2, w1, [x29, 56]
	stp	w5, w3, [x29, 48]
	stp	w0, w22, [x29, 64]
	str	w21, [x29, 72]
	mov	w3, 28
	add	x2, x29, 48
	mov	w1, 122
	mov	w0, w20
	blr	x4
.L128:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDMHAL_V5R6C1_DynamicAllocFrame_Only, .-VDMHAL_V5R6C1_DynamicAllocFrame_Only
	.align	3
.LC49:
	.xword	s_pstVfmwChan
	.align	3
.LC51:
	.xword	.LC50
	.align	3
.LC52:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ArrangeMem_Normal
	.type	VDMHAL_V5R6C1_ArrangeMem_Normal, %function
VDMHAL_V5R6C1_ArrangeMem_Normal:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w23, w2
	mov	w24, w3
	mov	w25, w4
	mov	w27, w5
	mov	x22, x6
	bl	_mcount
	str	xzr, [x29, 120]
	add	x0, x29, 104
	cmp	w20, 21
	stp	xzr, xzr, [x0]
	bhi	.L173
	bl	PDT_Is3716MV450
	cbz	w0, .L136
	mul	w1, w23, w24
	mov	w0, 36863
	movk	w0, 0x7e, lsl 16
	cmp	w1, w0
	bgt	.L174
.L136:
	ldr	x21, .LC59
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 503808
	ldr	w26, [x1, 1628]
	ldr	w1, [x0, 100]
	cmp	w1, 2
	beq	.L175
	and	w1, w20, -17
	cmp	w1, wzr
	ccmp	w20, 18, 4, ne
	beq	.L176
.L139:
	cmp	w20, 17
	cset	w2, eq
	mov	w1, w2
.L140:
	ldr	x4, .LC60
	sbfiz	x3, x19, 4, 32
	ldr	w5, [x0, 1292]
	str	w2, [x0, 1280]
	str	w1, [x4, x3]
	ldr	w3, [x0, 1284]
	ldr	w4, [x0, 1288]
	mov	w0, 1
	ldr	x1, .LC62
	bl	dprint_vfmw
.L138:
	mov	w2, w25
	add	x3, x29, 104
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R6C1_CalcFsNum
	mov	w25, w0
	add	x5, x29, 104
	mov	w4, w20
	mov	w3, w27
	mov	w2, w24
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R6C1_CalcFsSize
	orr	w0, w25, w0
	cbnz	w0, .L177
	ldr	x27, [x21, w19, sxtw 3]
	ldr	w20, [x29, 104]
	add	x0, x27, 503808
	cmp	w26, w20
	ldr	w25, [x0, 1632]
	ldr	w5, [x0, 1648]
	beq	.L178
.L143:
	ldr	x2, .LC55
	mov	w3, w20
	ldr	x1, .LC66
	mov	w4, w25
	add	x2, x2, 136
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x21, w19, sxtw 3]
	add	x3, x29, 104
	mov	w2, w24
	add	x0, x0, 503808
	ldr	w1, [x0, 1624]
	str	w20, [x0, 1628]
	cbz	w1, .L179
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R6C1_DynamicAllocFrame_Only
.L146:
	ldr	x4, [x21, w19, sxtw 3]
	mov	w3, w25
	ldr	x1, .LC68
	mov	w2, w20
	add	x4, x4, 503808
	mov	w0, 31
	ldr	w4, [x4, 1648]
	bl	dprint_vfmw
	ldr	x19, [x21, w19, sxtw 3]
	ldr	x0, .LC69
	add	x19, x19, 507904
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 1112]
	mov	w1, 2
.L135:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, w1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L179:
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R6C1_DynamicAllocFrame
	b	.L146
	.p2align 3
.L176:
	cmp	w23, 3839
	mov	w1, 2159
	ccmp	w24, w1, 0, le
	ble	.L139
	mov	w1, 1
	mov	w2, w1
	b	.L140
	.p2align 3
.L178:
	cmp	w5, 1
	beq	.L143
	ldr	w1, [x0, 1624]
	cmp	w1, 1
	beq	.L143
	cbz	x22, .L180
	add	x26, x27, 507904
	add	x20, x0, 3960
	mov	x0, x27
	ldr	w23, [x26, 1096]
	cbz	w25, .L181
.L148:
	add	x0, x0, 503808
	ldr	w2, [x0, 1636]
	cmp	w2, 30
	bgt	.L182
.L149:
	ldr	x24, .LC69
	mov	w0, 8
	str	w2, [x26, -88]
	ldr	x1, [x24, 24]
	blr	x1
	ldr	x7, [x21, w19, sxtw 3]
	add	x9, x7, 507904
	ldr	w0, [x9, 1136]
	cbz	w0, .L154
	ldp	w10, w6, [x26, -80]
	sub	x4, x26, #136
	mov	w5, 0
	mov	w8, 1
	.p2align 2
.L153:
	uxtw	x0, w5
	add	w5, w5, 1
	lsl	x1, x0, 6
	add	x1, x1, x0, lsl 3
	add	x1, x7, x1
	add	x11, x1, 503808
	uxtw	x1, w6
	lsl	x2, x1, 2
	add	x3, x1, 20
	sub	x2, x2, x1
	add	w6, w6, 1
	ldr	w1, [x11, 1688]
	add	x2, x4, x2, lsl 2
	ldr	w12, [x11, 1668]
	add	w1, w1, 1023
	and	w1, w1, -1024
	strb	w8, [x2, 472]
	str	w1, [x2, 464]
	add	w1, w23, w1
	str	w12, [x2, 468]
	str	w1, [x4, x3, lsl 2]
	str	w6, [x4, 60]
	ldr	w1, [x11, 1660]
	cmp	w1, 255
	beq	.L151
	ldr	w1, [x4, 68]
	ldr	w3, [x11, 1704]
	add	w2, w1, 1
	uxtw	x1, w1
	lsl	x0, x1, 2
	sub	x0, x0, x1
	add	x0, x4, x0, lsl 2
	str	w3, [x0, 848]
	str	w2, [x4, 68]
.L151:
	ldr	w0, [x4, 64]
	cmp	w0, w10
	bcs	.L152
	ldr	w2, [x11, 1664]
	add	x1, x27, x0, uxtw 3
	add	x1, x1, 507904
	add	w0, w0, 1
	cmp	w2, 255
	beq	.L152
	ldr	w2, [x11, 1720]
	str	w2, [x1, 72]
	strb	w8, [x1, 76]
	str	w0, [x4, 64]
.L152:
	ldr	w0, [x9, 1136]
	cmp	w5, w0
	bcc	.L153
.L154:
	ldr	x3, [x24, 104]
	mov	x2, 1232
	mov	x1, x20
	mov	x0, x22
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	w3, 1
	ldr	x2, [x24, 32]
	mov	w0, 8
	add	x1, x1, 507904
	str	w3, [x1, 1140]
	blr	x2
	mov	w1, 0
	b	.L135
	.p2align 3
.L175:
	add	x2, x0, 1280
	mov	w1, -1
	stp	wzr, wzr, [x2]
	stp	w1, w1, [x2, 8]
	b	.L138
	.p2align 3
.L182:
	ldr	x1, .LC75
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 30
	mov	w2, w1
	add	x0, x0, 503808
	str	w1, [x0, 1636]
	b	.L149
	.p2align 3
.L181:
	ldr	x1, .LC73
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x21, w19, sxtw 3]
	b	.L148
	.p2align 3
.L173:
	ldr	x2, .LC55
	mov	w0, 0
	ldr	x1, .LC56
	ldr	x3, .LC54
	add	x2, x2, 104
	bl	dprint_vfmw
	mov	w1, -1
	b	.L135
	.p2align 3
.L177:
	ldr	x1, .LC64
	mov	w0, 31
	bl	dprint_vfmw
	mov	w1, -1
	b	.L135
	.p2align 3
.L174:
	bl	PDT_Is3716MV450
	mov	w2, w0
	ldr	x1, .LC58
	mov	w0, 31
	bl	dprint_vfmw
	mov	w1, -1
	b	.L135
.L180:
	ldr	x2, .LC55
	mov	w0, 0
	ldr	x1, .LC56
	ldr	x3, .LC71
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w1, -1
	b	.L135
	.size	VDMHAL_V5R6C1_ArrangeMem_Normal, .-VDMHAL_V5R6C1_ArrangeMem_Normal
	.align	3
.LC54:
	.xword	.LC53
	.align	3
.LC55:
	.xword	.LANCHOR0
	.align	3
.LC56:
	.xword	.LC13
	.align	3
.LC58:
	.xword	.LC57
	.align	3
.LC59:
	.xword	s_pstVfmwChan
	.align	3
.LC60:
	.xword	g_VfmwCompressPara
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
	.align	3
.LC66:
	.xword	.LC65
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC69:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC71:
	.xword	.LC70
	.align	3
.LC73:
	.xword	.LC72
	.align	3
.LC75:
	.xword	.LC74
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ArrangeMem_Specific
	.type	VDMHAL_V5R6C1_ArrangeMem_Specific, %function
VDMHAL_V5R6C1_ArrangeMem_Specific:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w23, w0
	mov	w22, w2
	mov	x0, x30
	mov	w25, w1
	mov	w28, w3
	mov	w21, w4
	mov	w24, w5
	mov	w20, w6
	mov	w27, w7
	ldr	x19, [x29, 160]
	bl	_mcount
	cbz	w22, .L277
	sub	w1, w21, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L186
	sub	w1, w24, #32
	cmp	w1, w0
	bhi	.L186
	cbz	x19, .L278
	ldr	x0, .LC83
	cmp	w20, 20
	mov	x2, 1232
	mov	w1, 0
	mov	w6, 20
	ldr	x3, [x0, 96]
	mov	x0, x19
	csel	w26, w20, w6, le
	mov	w20, 32
	blr	x3
	ldr	x1, .LC84
	add	w0, w21, 15
	asr	w0, w0, 4
	add	w2, w24, 15
	cmp	w0, 45
	asr	w2, w2, 4
	ldrb	w3, [x1]
	mov	w1, 36
	ccmp	w2, w1, 0, le
	mov	w1, 64
	cset	w4, le
	cmp	w4, wzr
	csel	w20, w20, w1, eq
	cmp	w3, 1
	csel	w20, w20, w1, ne
	cmp	w25, 16
	lsl	w1, w0, 4
	beq	.L279
	cmp	w25, 17
	beq	.L235
	mul	w20, w0, w20
	mul	w20, w20, w2
	add	w20, w20, 143
	and	w20, w20, -128
.L194:
	mul	w3, w26, w20
	cmp	w28, w3
	ble	.L192
	sub	w0, w25, #17
	add	w7, w22, 1023
	and	w7, w7, -1024
	cmp	w0, 1
	asr	w0, w20, 1
	sub	w3, w28, w3
	stp	w0, w26, [x19, 52]
	sub	w6, w7, w22
	sub	w3, w3, w6
	bls	.L280
	add	w28, w1, 255
	add	w1, w24, 31
	and	w28, w28, -256
	and	w1, w1, -32
	lsl	w0, w28, 4
	str	w0, [x19, 4]
	asr	w0, w0, 1
	str	w0, [x19, 8]
	tbnz	w23, #31, .L272
	ldr	x4, .LC87
	mov	w8, 0
	mov	w26, 0
	ldr	x0, [x4, w23, sxtw 3]
	ldr	w0, [x0, 1280]
	cmp	w0, 1
	beq	.L281
.L240:
	mov	w5, 0
	mov	w0, 0
	mov	w24, 0
.L197:
	stp	w0, w5, [x19, 12]
	ldr	w0, [x29, 144]
	cmp	w0, 1
	beq	.L282
	mul	w2, w1, w28
	mul	w5, w26, w8
	lsl	w0, w2, 2
	lsl	w21, w24, 2
	sub	w2, w0, w2
	lsl	w0, w5, 2
	sub	w0, w0, w5
	sub	w21, w21, w24
	asr	w0, w0, 1
	add	w0, w0, w2, asr 1
	add	w21, w0, w21, lsr 1
.L199:
	ldr	w0, [x29, 152]
	tbnz	w0, #31, .L200
	stp	w7, w1, [x29, 104]
	stp	w8, w6, [x29, 112]
	str	w3, [x29, 120]
	bl	VCTRL_GetChanWidth
	mov	w23, w0
	ldr	w0, [x29, 152]
	bl	VCTRL_GetChanHeight
	cmn	w23, #1
	ldr	w3, [x29, 120]
	ccmn	w0, #1, 4, ne
	ldp	w7, w1, [x29, 104]
	ldp	w8, w6, [x29, 112]
	beq	.L283
	ldr	w2, [x29, 144]
	add	w23, w23, 15
	and	w23, w23, -16
	add	w0, w0, 15
	cmp	w2, 1
	add	w2, w23, 255
	and	w0, w0, -16
	and	w11, w2, -256
	beq	.L284
	ldr	x2, .LC87
	ldr	w4, [x29, 152]
	ldr	x2, [x2, w4, sxtw 3]
	ldr	w2, [x2, 1280]
	cmp	w2, 1
	beq	.L204
	add	w2, w0, 126
	adds	w0, w0, 63
	csel	w2, w2, w0, mi
	mov	w10, 0
	asr	w2, w2, 6
.L205:
	mul	w2, w11, w2
	mul	w11, w26, w8
	lsl	w5, w2, 2
	sub	w2, w5, w2
	lsl	w0, w11, 2
	lsl	w2, w2, 6
	sub	w0, w0, w11
	asr	w0, w0, 1
	add	w0, w0, w2, asr 1
	add	w0, w0, w10
.L203:
	cmp	w21, w0
	ldr	w23, [x29, 152]
	bgt	.L285
.L200:
	mul	w28, w1, w28
	sub	w0, w25, #16
	cmp	w0, 1
	add	w0, w28, w24
	str	w0, [x19, 36]
	bls	.L286
	cbz	w27, .L209
	cmp	w25, wzr
	ccmp	w25, 3, 4, ne
	beq	.L207
	sdiv	w3, w3, w21
	cmp	w27, 32
	mov	w0, 32
	csel	w27, w27, w0, le
	cmp	w3, w27
	csel	w3, w3, w27, le
	str	w3, [x19, 48]
.L210:
	cbz	w3, .L208
	sub	w0, w3, #1
	mov	x1, 476
	mov	w2, 12
	ldr	w4, [x19, 60]
	umaddl	x2, w0, w2, x1
	add	x1, x19, 464
	mov	w0, w7
	add	x2, x19, x2
	.p2align 2
.L213:
	str	w0, [x1], 12
	add	w0, w0, w21
	cmp	x2, x1
	bne	.L213
	ldr	w0, [x29, 144]
	add	w4, w3, w4
	str	w4, [x19, 60]
	cmp	w0, 1
	beq	.L287
	madd	w6, w21, w3, w6
	add	w0, w6, w22
.L225:
	add	x2, x19, 80
	mov	w1, 0
	.p2align 2
.L217:
	add	w1, w1, 1
	str	w0, [x2], 4
	cmp	w1, w3
	add	w0, w0, 32
	bcc	.L217
.L216:
	ldr	w4, [x19, 56]
	add	w6, w6, w3, lsl 5
	add	w22, w6, w22
	cbz	w4, .L222
	sub	w2, w4, #1
	ldr	w5, [x19, 64]
	add	x2, x2, 27
	add	x1, x19, 208
	mov	w0, w22
	add	x2, x19, x2, lsl 3
	.p2align 2
.L221:
	str	w0, [x1], 8
	add	w0, w0, w20
	cmp	x2, x1
	bne	.L221
	add	w0, w4, w5
	str	w0, [x19, 64]
.L222:
	madd	w20, w20, w4, w6
	str	w20, [x19]
	tbnz	w23, #31, .L220
	ldr	x0, .LC87
	ldr	x0, [x0, w23, sxtw 3]
	cbz	x0, .L220
	add	w0, w20, w22
	cbz	w3, .L220
	sub	w4, w3, #1
	mov	w5, 12
	mov	x2, 860
	add	x1, x19, 848
	umaddl	x2, w4, w5, x2
	add	x2, x19, x2
	.p2align 2
.L223:
	str	w0, [x1], 12
	add	w0, w0, 1024
	cmp	x2, x1
	bne	.L223
.L220:
	add	w20, w20, w3, lsl 10
	mov	w0, 0
	str	w20, [x19]
.L266:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L286:
	lsl	w0, w28, 2
	lsr	w4, w24, 1
	sub	w28, w0, w28
	lsl	w0, w24, 2
	sub	w0, w0, w24
	madd	w9, w26, w8, w4
	lsr	w0, w0, 1
	lsl	w8, w8, 4
	add	w0, w0, w28, asr 1
	str	w8, [x19, 20]
	stp	w0, w9, [x19, 28]
	cbnz	w27, .L207
.L209:
	str	wzr, [x19, 48]
.L208:
	ldr	x2, .LC78
	ldr	x3, .LC93
.L273:
	ldr	x1, .LC79
	add	x2, x2, 208
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L207:
	cmp	w27, 32
	mov	w0, 32
	sdiv	w3, w3, w21
	csel	w27, w27, w0, le
	cmp	w27, w3
	csel	w3, w27, w3, le
	str	w3, [x19, 48]
	b	.L210
	.p2align 3
.L279:
	mul	w20, w2, w1
	add	w20, w20, 143
	and	w20, w20, -128
	mul	w3, w26, w20
	cmp	w28, w3
	ble	.L192
	add	w7, w22, 1023
	asr	w0, w20, 1
	and	w7, w7, -1024
	sub	w3, w28, w3
	stp	w0, w26, [x19, 52]
	sub	w6, w7, w22
	add	w28, w21, 255
	sub	w3, w3, w6
	and	w28, w28, -256
	mov	w1, w24
	tbnz	w23, #31, .L196
	ldr	x4, .LC87
	stp	w7, w6, [x29, 104]
	stp	w3, w2, [x29, 112]
	ldr	x0, [x4, w23, sxtw 3]
	str	x4, [x29, 120]
	add	x0, x0, 507904
	add	x0, x0, 1752
	bl	IsMain10Profile
	ldp	w7, w6, [x29, 104]
	ldp	w3, w2, [x29, 112]
	ldr	x4, [x29, 120]
	cbz	w0, .L236
	cmp	w28, wzr
	add	w8, w28, 3
	csel	w8, w8, w28, lt
	add	w9, w24, 31
	asr	w8, w8, 2
	and	w26, w9, -32
	mov	w1, w24
.L195:
	lsl	w0, w28, 4
	str	w0, [x19, 4]
	asr	w0, w0, 1
	str	w0, [x19, 8]
	ldr	x0, [x4, w23, sxtw 3]
	ldr	w0, [x0, 1280]
	cmp	w0, 1
	bne	.L240
.L281:
	cmp	w25, 17
	mov	w0, 1920
	ccmp	w21, w0, 0, ne
	ble	.L240
	adds	w0, w21, 2047
	add	w21, w21, 4094
	csel	w0, w21, w0, mi
	and	w4, w0, -2048
	cmp	w4, wzr
	add	w0, w4, 127
	csel	w0, w0, w4, lt
	adds	w5, w24, 63
	add	w4, w24, 126
	asr	w0, w0, 7
	csel	w4, w4, w5, mi
	asr	w4, w4, 6
	lsl	w4, w4, 5
	mul	w24, w4, w0
	mov	w5, w24
	b	.L197
	.p2align 3
.L282:
	lsl	w0, w2, 4
	mul	w0, w0, w28
	lsl	w21, w0, 2
	sub	w21, w21, w0
	b	.L199
	.p2align 3
.L196:
	lsl	w0, w28, 4
	str	w0, [x19, 4]
	asr	w0, w0, 1
	str	w0, [x19, 8]
.L272:
	mov	w5, 0
	mov	w0, 0
	mov	w8, 0
	mov	w26, 0
	mov	w24, 0
	b	.L197
	.p2align 3
.L287:
	ldr	x0, .LC94
	ldr	x4, [x0]
	cbz	x4, .L215
	str	w3, [x29, 136]
	add	x2, x29, 128
	mov	w3, 12
	mov	w1, 128
	mov	w0, w23
	str	w6, [x29, 120]
	stp	w7, w21, [x29, 128]
	blr	x4
	ldr	w3, [x19, 48]
	ldr	w6, [x29, 120]
.L215:
	madd	w6, w21, w3, w6
	add	w0, w6, w22
	cbnz	w3, .L225
	b	.L216
	.p2align 3
.L235:
	mov	w20, 128
	movk	w20, 0x24, lsl 16
	b	.L194
	.p2align 3
.L280:
	add	w28, w21, 255
	add	w1, w24, 63
	and	w28, w28, -256
	and	w1, w1, -64
	tbnz	w23, #31, .L196
	ldr	x4, .LC87
	ldr	x0, [x4, w23, sxtw 3]
	ldr	w0, [x0, 1612]
	cmp	w0, 8
	ble	.L237
	cmp	w28, wzr
	add	w8, w28, 3
	csel	w8, w8, w28, lt
	mov	w26, w1
	asr	w8, w8, 2
	b	.L195
	.p2align 3
.L284:
	mul	w0, w0, w11
	lsl	w2, w0, 2
	sub	w0, w2, w0
	b	.L203
	.p2align 3
.L204:
	adds	w5, w0, 63
	add	w2, w0, 126
	csel	w2, w2, w5, mi
	adds	w5, w23, 2047
	add	w23, w23, 4094
	asr	w2, w2, 6
	csel	w5, w23, w5, mi
	and	w5, w5, -2048
	add	w10, w5, 127
	cmp	w5, wzr
	csel	w5, w10, w5, lt
	lsl	w10, w2, 2
	sub	w10, w10, w2
	asr	w5, w5, 7
	lsl	w10, w10, 5
	mul	w10, w5, w10
	lsr	w10, w10, 1
	b	.L205
.L236:
	mov	w1, w24
	mov	w26, 0
	mov	w8, 0
	b	.L195
.L237:
	mov	w26, 0
	mov	w8, 0
	b	.L195
.L186:
	ldr	x2, .LC78
	ldr	x3, .LC80
	b	.L273
.L192:
	ldr	x2, .LC78
	ldr	x3, .LC86
	b	.L273
.L277:
	ldr	x2, .LC78
	ldr	x3, .LC77
	b	.L273
.L283:
	ldr	x1, .LC89
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L266
.L285:
	ldr	x2, .LC78
	ldr	x3, .LC91
	b	.L273
.L278:
	ldr	x2, .LC78
	ldr	x3, .LC82
	b	.L273
	.size	VDMHAL_V5R6C1_ArrangeMem_Specific, .-VDMHAL_V5R6C1_ArrangeMem_Specific
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC78:
	.xword	.LANCHOR0
	.align	3
.LC79:
	.xword	.LC13
	.align	3
.LC80:
	.xword	.LC29
	.align	3
.LC82:
	.xword	.LC81
	.align	3
.LC83:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC84:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC87:
	.xword	s_pstVfmwChan
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC94:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ArrangeMem
	.type	VDMHAL_V5R6C1_ArrangeMem, %function
VDMHAL_V5R6C1_ArrangeMem:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	stp	x19, x20, [sp, 48]
	stp	x21, x22, [sp, 64]
	stp	x23, x24, [sp, 80]
	stp	x25, x26, [sp, 96]
	mov	w24, w0
	mov	x0, x30
	mov	w19, w7
	mov	w25, w1
	mov	w20, w2
	mov	w21, w3
	mov	w22, w4
	mov	w26, w5
	mov	w23, w6
	bl	_mcount
	cmn	w19, #2
	beq	.L292
	tbnz	w19, #31, .L293
	mov	w0, w19
	bl	VCTRL_GetVidStd
	mov	w1, w0
	ldr	x0, .LC95
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 1552]
	cmp	w0, 1
	beq	.L295
.L290:
	ldr	x0, [x29, 80]
	mov	w7, w26
	str	x0, [sp, 16]
	mov	w6, w22
	mov	w5, w21
	mov	w4, w20
	mov	w3, w25
	mov	w2, w24
	str	w23, [sp]
	mov	w0, w19
	str	w19, [sp, 8]
	bl	VDMHAL_V5R6C1_ArrangeMem_Specific
.L294:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L293:
	mov	w1, 22
	b	.L290
	.p2align 3
.L292:
	mov	w1, 16
	b	.L290
	.p2align 3
.L295:
	ldr	x6, [x29, 80]
	mov	w5, w23
	mov	w4, w22
	mov	w3, w21
	mov	w2, w20
	mov	w0, w19
	bl	VDMHAL_V5R6C1_ArrangeMem_Normal
	b	.L294
	.size	VDMHAL_V5R6C1_ArrangeMem, .-VDMHAL_V5R6C1_ArrangeMem
	.align	3
.LC95:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ResetVdm
	.type	VDMHAL_V5R6C1_ResetVdm, %function
VDMHAL_V5R6C1_ResetVdm:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, wzr
	ble	.L297
	ldr	x2, .LC96
	mov	w4, 0
	ldr	x1, .LC97
	mov	w3, w21
	add	x2, x2, 248
	mov	w0, 0
	bl	dprint_vfmw
.L296:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L297:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L312
	sxtw	x23, w21
	ldr	x20, .LC100
	lsl	x0, x23, 6
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x26, x0, x23
	add	x26, x0, x26, lsl 2
	ldr	x0, [x20, x26]
	add	x1, x0, 61440
	ldr	w24, [x0, 36]
	ldr	w1, [x1, 2052]
	str	w1, [x29, 92]
	and	w1, w1, 3
	cbz	w1, .L296
	ldr	x25, .LC101
	mov	w19, 0
	mov	x22, x26
	ldr	x0, [x25, 224]
	blr	x0
	ldr	x0, [x20, x26]
	add	x0, x0, 61440
	ldr	w1, [x0, 2060]
	str	w1, [x29, 92]
	orr	w1, w1, 2
	strb	w1, [x29, 92]
	ldr	w1, [x29, 92]
	str	w1, [x0, 2060]
	b	.L302
	.p2align 3
.L313:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L303
.L302:
	ldr	x1, [x25, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20, x22]
	add	x0, x0, 61440
	ldr	w0, [x0, 2064]
	str	w0, [x29, 92]
	tbz	x0, 1, .L313
	cmp	w19, 999
	bgt	.L303
	ldr	x2, .LC96
	mov	w3, w21
	ldr	x1, .LC105
	mov	w0, 0
	add	x2, x2, 248
	bl	dprint_vfmw
.L305:
	lsl	x0, x23, 6
	ldr	x2, [x25, 224]
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x23, x0, x23
	add	x23, x0, x23, lsl 2
	ldr	x0, [x20, x23]
	add	x0, x0, 61440
	ldr	w1, [x0, 2060]
	str	w1, [x29, 92]
	and	w1, w1, -3
	strb	w1, [x29, 92]
	ldr	w1, [x29, 92]
	str	w1, [x0, 2060]
	blr	x2
	ldr	x0, [x20, x23]
	str	w24, [x0, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L303:
	ldr	x2, .LC96
	mov	w3, w21
	ldr	x1, .LC103
	mov	w0, 0
	add	x2, x2, 248
	bl	dprint_vfmw
	b	.L305
.L312:
	ldr	x1, .LC99
	mov	x2, 0
	bl	dprint_vfmw
	b	.L296
	.size	VDMHAL_V5R6C1_ResetVdm, .-VDMHAL_V5R6C1_ResetVdm
	.align	3
.LC96:
	.xword	.LANCHOR0
	.align	3
.LC97:
	.xword	.LC1
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC100:
	.xword	g_HwMem
	.align	3
.LC101:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC103:
	.xword	.LC102
	.align	3
.LC105:
	.xword	.LC104
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.type	VDMHAL_V5R6C1_SetSmmuPageTableAddr, %function
VDMHAL_V5R6C1_SetSmmuPageTableAddr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC106
	ldr	x3, [x0, 392]
	cbz	x3, .L314
	add	x2, x29, 60
	add	x1, x29, 56
	add	x0, x29, 52
	blr	x3
	cbnz	w19, .L316
	ldr	x0, .LC107
	ldp	w3, w2, [x29, 52]
	ldr	w1, [x29, 60]
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w3, [x0, 524]
	str	w2, [x0, 772]
	str	w1, [x0, 776]
.L314:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L316:
	ldr	x20, .LC108
	mov	w3, w19
	ldr	x21, .LC110
	mov	w4, 1
	add	x20, x20, 272
	mov	w0, 32
	mov	x1, x21
	mov	x2, x20
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x20
	mov	x1, x21
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x20
	mov	x1, x21
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.size	VDMHAL_V5R6C1_SetSmmuPageTableAddr, .-VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.align	3
.LC106:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC107:
	.xword	g_HwMem
	.align	3
.LC108:
	.xword	.LANCHOR0
	.align	3
.LC110:
	.xword	.LC109
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_EnableSmmu
	.type	VDMHAL_V5R6C1_EnableSmmu, %function
VDMHAL_V5R6C1_EnableSmmu:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC112
	mov	w1, 8
	movk	w1, 0x3, lsl 16
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_EnableSmmu, .-VDMHAL_V5R6C1_EnableSmmu
	.align	3
.LC112:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GlbResetX
	.type	VDMHAL_V5R6C1_GlbResetX, %function
VDMHAL_V5R6C1_GlbResetX:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L340
	cmp	w19, wzr
	ble	.L341
	ldr	x22, .LC113
	mov	w4, 1
	ldr	x23, .LC118
	mov	w3, w19
	add	x21, x22, 312
	mov	w0, 32
	mov	x1, x23
	mov	x2, x21
	bl	dprint_vfmw
	ldrb	w20, [x29, 92]
	and	w20, w20, 3
	cmp	w20, 1
	beq	.L342
.L321:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L341:
	sxtw	x0, w19
	ldr	x21, .LC116
	lsl	x20, x0, 6
	sub	x20, x20, x0
	lsl	x20, x20, 2
	sub	x0, x20, x0
	add	x20, x20, x0, lsl 2
	ldr	x0, [x21, x20]
	add	x0, x0, 61440
	ldr	w0, [x0, 2052]
	str	w0, [x29, 92]
	and	w0, w0, 3
	cmp	w0, 1
	bne	.L321
	ldr	x24, .LC119
	ldr	x0, [x24, 224]
	blr	x0
	ldr	x22, .LC113
	ldr	x0, [x21, x20]
	add	x0, x0, 61440
	ldr	w1, [x0, 2060]
	str	w1, [x29, 92]
	orr	w1, w1, 1
	strb	w1, [x29, 92]
	ldr	w1, [x29, 92]
	str	w1, [x0, 2060]
	b	.L336
	.p2align 3
.L342:
	ldr	x24, .LC119
	ldr	x0, [x24, 224]
	blr	x0
	mov	w4, w20
	mov	w3, w19
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w5, [x29, 92]
	mov	w4, w20
	ldr	x1, .LC124
	mov	w3, w19
	orr	w5, w5, 1
	mov	x2, x21
	mov	w0, 32
	strb	w5, [x29, 92]
	bl	dprint_vfmw
.L336:
	sxtw	x23, w19
	ldr	x25, .LC118
	lsl	x21, x23, 6
	ldr	x26, .LC116
	sub	x21, x21, x23
	mov	w20, 0
	lsl	x21, x21, 2
	sub	x21, x21, x23
	b	.L331
	.p2align 3
.L328:
	bl	dprint_vfmw
	ldrb	w0, [x29, 92]
	tbnz	x0, 0, .L330
.L343:
	add	w20, w20, 1
	cmp	w20, 1000
	beq	.L332
.L331:
	ldr	x1, [x24, 232]
	mov	x0, 30
	blr	x1
	cmp	w19, wzr
	add	x0, x21, x21, lsl 2
	add	x5, x0, x23
	mov	w4, 1
	mov	w3, w19
	add	x2, x22, 312
	mov	x1, x25
	mov	w0, 32
	bgt	.L328
	ldr	x0, [x26, x5]
	add	x0, x0, 61440
	ldr	w0, [x0, 2064]
	str	w0, [x29, 92]
	ldrb	w0, [x29, 92]
	tbz	x0, 0, .L343
.L330:
	cmp	w20, 999
	bgt	.L332
	ldr	x1, .LC123
	mov	w3, w19
	add	x2, x22, 312
	mov	w0, 0
	bl	dprint_vfmw
.L334:
	cmp	w19, wzr
	ble	.L344
	add	x22, x22, 312
	ldr	x1, .LC118
	mov	w3, w19
	mov	x2, x22
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC124
	mov	w3, w19
	mov	x2, x22
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L332:
	ldr	x1, .LC121
	mov	w3, w19
	add	x2, x22, 312
	mov	w0, 0
	bl	dprint_vfmw
	b	.L334
	.p2align 3
.L344:
	lsl	x0, x19, 6
	ldr	x1, .LC116
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x0, x0, x19, lsl 2
	ldr	x0, [x1, x0]
	add	x0, x0, 61440
	ldr	w1, [x0, 2060]
	str	w1, [x29, 92]
	and	w1, w1, -2
	strb	w1, [x29, 92]
	ldr	w1, [x29, 92]
	str	w1, [x0, 2060]
	b	.L321
	.p2align 3
.L340:
	ldr	x2, .LC113
	mov	w3, -121438208
	ldr	x1, .LC115
	add	x2, x2, 312
	bl	dprint_vfmw
	b	.L321
	.size	VDMHAL_V5R6C1_GlbResetX, .-VDMHAL_V5R6C1_GlbResetX
	.align	3
.LC113:
	.xword	.LANCHOR0
	.align	3
.LC115:
	.xword	.LC114
	.align	3
.LC116:
	.xword	g_HwMem
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC119:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC121:
	.xword	.LC120
	.align	3
.LC123:
	.xword	.LC122
	.align	3
.LC124:
	.xword	.LC109
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GlbReset
	.type	VDMHAL_V5R6C1_GlbReset, %function
VDMHAL_V5R6C1_GlbReset:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L348
	mov	w0, 0
	bl	VDMHAL_V5R6C1_GlbResetX
.L345:
	ldp	x29, x30, [sp], 16
	ret
.L348:
	ldr	x2, .LC126
	mov	w3, -121438208
	ldr	x1, .LC127
	add	x2, x2, 336
	bl	dprint_vfmw
	b	.L345
	.size	VDMHAL_V5R6C1_GlbReset, .-VDMHAL_V5R6C1_GlbReset
	.align	3
.LC126:
	.xword	.LANCHOR0
	.align	3
.LC127:
	.xword	.LC114
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ClearIntState
	.type	VDMHAL_V5R6C1_ClearIntState, %function
VDMHAL_V5R6C1_ClearIntState:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x19, w0
	mov	x0, x30
	mov	x20, x19
	bl	_mcount
	ldr	x21, .LC129
	ldr	x0, .LC128
	add	x1, x21, x19, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x0, [x0, x1, lsl 3]
	cbz	x0, .L359
	ldr	w22, [x0, 1312]
.L350:
	cmp	w20, wzr
	bgt	.L361
	lsl	x0, x19, 6
	ldr	x23, .LC132
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x23, x20]
	cbz	x0, .L362
.L353:
	cmp	w22, 1
	bne	.L360
	add	x19, x21, x19, lsl 6
	ldr	w1, [x19, 44]
	cmp	w1, 1
	beq	.L360
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L363
	cmp	w1, 3
	bne	.L349
	mov	w1, -15
	str	w1, [x0, 32]
	b	.L349
	.p2align 3
.L361:
	ldr	x2, .LC130
	mov	w4, 0
	ldr	x1, .LC131
	mov	w3, w20
	add	x2, x2, 360
	mov	w0, 0
	bl	dprint_vfmw
.L349:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L360:
	mov	w1, -1
	str	w1, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L359:
	mov	w22, 0
	b	.L350
	.p2align 3
.L362:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L354
	str	x0, [x23, x20]
	b	.L353
	.p2align 3
.L363:
	mov	w1, -12
	str	w1, [x0, 32]
	b	.L349
.L354:
	ldr	x1, .LC133
	mov	w0, 0
	bl	dprint_vfmw
	b	.L349
	.size	VDMHAL_V5R6C1_ClearIntState, .-VDMHAL_V5R6C1_ClearIntState
	.align	3
.LC128:
	.xword	s_pstVfmwChan
	.align	3
.LC129:
	.xword	g_VdmDrvParam
	.align	3
.LC130:
	.xword	.LANCHOR0
	.align	3
.LC131:
	.xword	.LC1
	.align	3
.LC132:
	.xword	g_HwMem
	.align	3
.LC133:
	.xword	.LC3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ClearMMUIntState
	.type	VDMHAL_V5R6C1_ClearMMUIntState, %function
VDMHAL_V5R6C1_ClearMMUIntState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L369
	lsl	x3, x19, 6
	ldr	x20, .LC136
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L370
.L367:
	add	x0, x0, 61440
	mov	w1, 7
	str	w1, [x0, 44]
.L364:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L369:
	ldr	x2, .LC134
	mov	w3, w19
	ldr	x1, .LC135
	mov	w4, 0
	add	x2, x2, 392
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L370:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L368
	str	x0, [x20, x19]
	b	.L367
.L368:
	ldr	x1, .LC137
	mov	w0, 0
	bl	dprint_vfmw
	b	.L364
	.size	VDMHAL_V5R6C1_ClearMMUIntState, .-VDMHAL_V5R6C1_ClearMMUIntState
	.align	3
.LC134:
	.xword	.LANCHOR0
	.align	3
.LC135:
	.xword	.LC1
	.align	3
.LC136:
	.xword	g_HwMem
	.align	3
.LC137:
	.xword	.LC3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_MaskInt
	.type	VDMHAL_V5R6C1_MaskInt, %function
VDMHAL_V5R6C1_MaskInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L376
	lsl	x3, x19, 6
	ldr	x20, .LC140
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L377
.L374:
	mov	w1, -1
	str	w1, [x0, 36]
.L371:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L376:
	ldr	x2, .LC138
	mov	w3, w19
	ldr	x1, .LC139
	mov	w4, 0
	add	x2, x2, 424
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L377:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L375
	str	x0, [x20, x19]
	b	.L374
.L375:
	ldr	x1, .LC141
	mov	w0, 0
	bl	dprint_vfmw
	b	.L371
	.size	VDMHAL_V5R6C1_MaskInt, .-VDMHAL_V5R6C1_MaskInt
	.align	3
.LC138:
	.xword	.LANCHOR0
	.align	3
.LC139:
	.xword	.LC1
	.align	3
.LC140:
	.xword	g_HwMem
	.align	3
.LC141:
	.xword	.LC3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetIntMaskCfg
	.type	VDMHAL_V5R6C1_GetIntMaskCfg, %function
VDMHAL_V5R6C1_GetIntMaskCfg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 1
	mov	w1, -6
	mov	w0, -2
	ldr	x19, [sp, 16]
	csel	w0, w1, w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R6C1_GetIntMaskCfg, .-VDMHAL_V5R6C1_GetIntMaskCfg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_EnableInt
	.type	VDMHAL_V5R6C1_EnableInt, %function
VDMHAL_V5R6C1_EnableInt:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC143
	sxtw	x0, w19
	ldr	x2, .LC142
	add	x1, x1, x0, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x1, [x2, x1, lsl 3]
	cbz	x1, .L389
	ldr	w20, [x1, 1312]
.L382:
	cmp	w19, wzr
	bgt	.L390
	lsl	x19, x0, 6
	ldr	x21, .LC146
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	ldr	x0, [x21, x19]
	cbz	x0, .L391
.L385:
	mov	w1, -6
	mov	w2, -2
	cmp	w20, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 36]
.L381:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L390:
	ldr	x2, .LC144
	mov	w3, w19
	ldr	x1, .LC145
	mov	w4, 0
	add	x2, x2, 448
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L389:
	mov	w20, 0
	b	.L382
	.p2align 3
.L391:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L386
	str	x0, [x21, x19]
	b	.L385
.L386:
	ldr	x1, .LC147
	mov	w0, 0
	bl	dprint_vfmw
	b	.L381
	.size	VDMHAL_V5R6C1_EnableInt, .-VDMHAL_V5R6C1_EnableInt
	.align	3
.LC142:
	.xword	s_pstVfmwChan
	.align	3
.LC143:
	.xword	g_VdmDrvParam
	.align	3
.LC144:
	.xword	.LANCHOR0
	.align	3
.LC145:
	.xword	.LC1
	.align	3
.LC146:
	.xword	g_HwMem
	.align	3
.LC147:
	.xword	.LC3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CheckReg
	.type	VDMHAL_V5R6C1_CheckReg, %function
VDMHAL_V5R6C1_CheckReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	bgt	.L409
	lsl	x0, x19, 6
	ldr	x21, .LC151
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x21, x20]
	cbz	x0, .L410
.L395:
	sub	w0, w22, #1
	cmp	w0, 6
	bls	.L411
	ldr	x2, .LC148
	mov	w3, w22
	ldr	x1, .LC155
	mov	w0, 0
	add	x2, x2, 472
	bl	dprint_vfmw
	mov	w0, 0
.L408:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L411:
	ldr	x1, .LC156
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx402
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx402:
	.section	.rodata
	.align	0
	.align	2
.L402:
	.byte	(.L406 - .Lrtx402) / 4
	.byte	(.L403 - .Lrtx402) / 4
	.byte	(.L404 - .Lrtx402) / 4
	.byte	(.L405 - .Lrtx402) / 4
	.byte	(.L407 - .Lrtx402) / 4
	.byte	(.L397 - .Lrtx402) / 4
	.byte	(.L399 - .Lrtx402) / 4
	.text
	.p2align 3
.L407:
	mov	x1, 61480
.L401:
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x21, x19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	w0, [x0, x1]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L406:
	mov	x1, 28
	b	.L401
	.p2align 3
.L405:
	mov	x1, 40
	b	.L401
	.p2align 3
.L404:
	mov	x1, 36
	b	.L401
	.p2align 3
.L403:
	mov	x1, 32
	b	.L401
	.p2align 3
.L399:
	mov	x1, 62272
	b	.L401
	.p2align 3
.L397:
	mov	x1, 62304
	b	.L401
	.p2align 3
.L410:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L396
	str	x0, [x21, x20]
	b	.L395
	.p2align 3
.L409:
	ldr	x2, .LC148
	mov	w3, w19
	ldr	x1, .LC150
	mov	w0, 0
	add	x2, x2, 472
	bl	dprint_vfmw
	mov	w0, -1
	b	.L408
.L396:
	ldr	x2, .LC148
	mov	w0, 0
	ldr	x1, .LC153
	add	x2, x2, 472
	bl	dprint_vfmw
	mov	w0, 0
	b	.L408
	.size	VDMHAL_V5R6C1_CheckReg, .-VDMHAL_V5R6C1_CheckReg
	.align	3
.LC148:
	.xword	.LANCHOR0
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC151:
	.xword	g_HwMem
	.align	3
.LC153:
	.xword	.LC152
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC156:
	.xword	.L402
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ReadMMUMask
	.type	VDMHAL_V5R6C1_ReadMMUMask, %function
VDMHAL_V5R6C1_ReadMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	ble	.L415
	ldr	x2, .LC158
	mov	w3, w19
	ldr	x1, .LC159
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L415:
	lsl	x0, x19, 6
	ldr	x1, .LC157
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	ldr	x19, [sp, 16]
	add	x0, x0, 61440
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 32]
	ret
	.size	VDMHAL_V5R6C1_ReadMMUMask, .-VDMHAL_V5R6C1_ReadMMUMask
	.align	3
.LC157:
	.xword	g_HwMem
	.align	3
.LC158:
	.xword	.LANCHOR1
	.align	3
.LC159:
	.xword	.LC117
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_WriteMMUMask
	.type	VDMHAL_V5R6C1_WriteMMUMask, %function
VDMHAL_V5R6C1_WriteMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	ble	.L419
	ldr	x2, .LC161
	mov	w3, w19
	ldr	x1, .LC162
	mov	w4, 1
	add	x2, x2, 32
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L419:
	lsl	x0, x19, 6
	ldr	x1, .LC160
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	add	x0, x0, 61440
	str	w20, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R6C1_WriteMMUMask, .-VDMHAL_V5R6C1_WriteMMUMask
	.align	3
.LC160:
	.xword	g_HwMem
	.align	3
.LC161:
	.xword	.LANCHOR1
	.align	3
.LC162:
	.xword	.LC109
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_PrepareDec
	.type	VDMHAL_V5R6C1_PrepareDec, %function
VDMHAL_V5R6C1_PrepareDec:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x22, x1
	mov	x0, x30
	mov	w21, w2
	mov	x19, x3
	bl	_mcount
	cbz	x22, .L440
	cmp	w21, wzr
	bgt	.L441
	cmp	w20, 6
	mov	w2, 0
	cset	w1, eq
	mov	w0, 0
	mov	x3, x19
	bl	SCD_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, 1
	mov	w0, 8
	bl	SCD_ConfigReg
	cmp	w20, 18
	bls	.L442
.L439:
	mov	w0, -1
	b	.L422
	.p2align 3
.L442:
	ldr	x0, .LC167
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx425
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx425:
	.section	.rodata
	.align	0
	.align	2
.L425:
	.byte	(.L435 - .Lrtx425) / 4
	.byte	(.L426 - .Lrtx425) / 4
	.byte	(.L427 - .Lrtx425) / 4
	.byte	(.L428 - .Lrtx425) / 4
	.byte	(.L439 - .Lrtx425) / 4
	.byte	(.L429 - .Lrtx425) / 4
	.byte	(.L430 - .Lrtx425) / 4
	.byte	(.L439 - .Lrtx425) / 4
	.byte	(.L431 - .Lrtx425) / 4
	.byte	(.L432 - .Lrtx425) / 4
	.byte	(.L433 - .Lrtx425) / 4
	.byte	(.L433 - .Lrtx425) / 4
	.byte	(.L433 - .Lrtx425) / 4
	.byte	(.L434 - .Lrtx425) / 4
	.byte	(.L439 - .Lrtx425) / 4
	.byte	(.L435 - .Lrtx425) / 4
	.byte	(.L436 - .Lrtx425) / 4
	.byte	(.L437 - .Lrtx425) / 4
	.byte	(.L438 - .Lrtx425) / 4
	.text
	.p2align 3
.L435:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	H264HAL_V5R6C1_StartDec
.L422:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L437:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP9HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L436:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	HEVCHAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L434:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP8HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L433:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP6HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L432:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV9HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L431:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV8HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L430:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	AVSHAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L429:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	DIVX3HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L428:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP2HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L427:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP4HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L426:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VC1HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L438:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	AVS2HAL_V5R6C1_StartDec
	b	.L422
	.p2align 3
.L441:
	ldr	x2, .LC163
	mov	w3, w21
	ldr	x1, .LC166
	mov	w4, 0
	add	x2, x2, 64
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L440:
	ldr	x2, .LC163
	mov	x3, 0
	ldr	x1, .LC165
	mov	w0, 0
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L422
	.size	VDMHAL_V5R6C1_PrepareDec, .-VDMHAL_V5R6C1_PrepareDec
	.align	3
.LC163:
	.xword	.LANCHOR1
	.align	3
.LC165:
	.xword	.LC164
	.align	3
.LC166:
	.xword	.LC1
	.align	3
.LC167:
	.xword	.L425
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_IsVdmReady
	.type	VDMHAL_V5R6C1_IsVdmReady, %function
VDMHAL_V5R6C1_IsVdmReady:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC168
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L448
	cmp	w19, wzr
	ble	.L449
	ldr	x2, .LC171
	mov	w4, 1
	ldr	x1, .LC173
	mov	w3, w19
	add	x2, x2, 96
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 0
.L445:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L449:
	ldr	w0, [x0, 28]
	ldr	x19, [sp, 16]
	ubfx	x0, x0, 17, 1
	ldp	x29, x30, [sp], 32
	ret
.L448:
	ldr	x2, .LC171
	ldr	x3, .LC170
	ldr	x1, .LC172
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L445
	.size	VDMHAL_V5R6C1_IsVdmReady, .-VDMHAL_V5R6C1_IsVdmReady
	.align	3
.LC168:
	.xword	g_HwMem
	.align	3
.LC170:
	.xword	.LC169
	.align	3
.LC171:
	.xword	.LANCHOR1
	.align	3
.LC172:
	.xword	.LC13
	.align	3
.LC173:
	.xword	.LC117
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_IsVdmRun
	.type	VDMHAL_V5R6C1_IsVdmRun, %function
VDMHAL_V5R6C1_IsVdmRun:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC174
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L455
	cmp	w19, wzr
	ble	.L456
	ldr	x2, .LC177
	mov	w4, 1
	ldr	x1, .LC178
	mov	w3, w19
	add	x2, x2, 128
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
.L452:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L456:
	ldr	w0, [x0, 40]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L455:
	ldr	x1, .LC176
	bl	dprint_vfmw
	mov	w0, 0
	b	.L452
	.size	VDMHAL_V5R6C1_IsVdmRun, .-VDMHAL_V5R6C1_IsVdmRun
	.align	3
.LC174:
	.xword	g_HwMem
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC177:
	.xword	.LANCHOR1
	.align	3
.LC178:
	.xword	.LC117
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_IsVdhDecOver
	.type	VDMHAL_V5R6C1_IsVdhDecOver, %function
VDMHAL_V5R6C1_IsVdhDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC179
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L465
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R6C1_CheckReg
	cmp	w19, 2
	beq	.L462
	cmp	w19, 3
	beq	.L462
	cmp	w19, 1
	ubfx	x0, x0, 17, 1
	beq	.L459
	ldr	x2, .LC181
	mov	w3, w19
	ldr	x1, .LC183
	mov	w0, 0
	add	x2, x2, 152
	bl	dprint_vfmw
	mov	w0, 0
.L459:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L462:
	and	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L465:
	ldr	x2, .LC181
	ldr	x3, .LC180
	ldr	x1, .LC182
	add	x2, x2, 152
	bl	dprint_vfmw
	mov	w0, -1
	b	.L459
	.size	VDMHAL_V5R6C1_IsVdhDecOver, .-VDMHAL_V5R6C1_IsVdhDecOver
	.align	3
.LC179:
	.xword	g_HwMem
	.align	3
.LC180:
	.xword	.LC169
	.align	3
.LC181:
	.xword	.LANCHOR1
	.align	3
.LC182:
	.xword	.LC13
	.align	3
.LC183:
	.xword	.LC154
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_IsVdhPartDecOver
	.type	VDMHAL_V5R6C1_IsVdhPartDecOver, %function
VDMHAL_V5R6C1_IsVdhPartDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC184
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L474
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R6C1_CheckReg
	cmp	w19, 1
	beq	.L470
	cmp	w19, 2
	ubfx	x0, x0, 2, 1
	bne	.L475
.L468:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L475:
	ldr	x2, .LC186
	mov	w3, w19
	ldr	x1, .LC188
	mov	w0, 0
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L470:
	ubfx	x0, x0, 19, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L474:
	ldr	x2, .LC186
	ldr	x3, .LC185
	ldr	x1, .LC187
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, -1
	b	.L468
	.size	VDMHAL_V5R6C1_IsVdhPartDecOver, .-VDMHAL_V5R6C1_IsVdhPartDecOver
	.align	3
.LC184:
	.xword	g_HwMem
	.align	3
.LC185:
	.xword	.LC169
	.align	3
.LC186:
	.xword	.LANCHOR1
	.align	3
.LC187:
	.xword	.LC13
	.align	3
.LC188:
	.xword	.LC154
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_UpdateHardwareInfo
	.type	VDMHAL_V5R6C1_UpdateHardwareInfo, %function
VDMHAL_V5R6C1_UpdateHardwareInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	bl	_mcount
	cmp	w22, wzr
	bgt	.L477
	ldr	x4, .LC189
	add	x0, x4, 4
	add	x4, x4, 128
	ldr	w1, [x4, -128]
	cmp	w1, 1
	bne	.L481
	b	.L492
	.p2align 3
.L502:
	cmp	x0, x4
	beq	.L501
.L481:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L502
.L492:
	mov	w19, w1
.L478:
	sxtw	x20, w22
	ldr	x24, .LC194
	lsl	x0, x20, 6
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x21, x0, x20
	add	x21, x0, x21, lsl 2
	ldr	x1, [x24, x21]
	cbz	x1, .L503
.L482:
	lsl	x0, x20, 2
	ldr	x21, .LC196
	sub	x4, x0, x20
	ldr	x2, .LC200
	lsl	x0, x4, 4
	ldr	w3, [x1, 12]
	sub	x0, x0, x4
	lsl	x5, x20, 6
	lsl	x0, x0, 2
	add	x4, x21, x0
	str	w3, [x21, x0]
	add	x0, x2, x5
	ldr	w3, [x1, 28]
	ldr	w0, [x0, 56]
	str	w3, [x4, 4]
	cmp	w0, 1
	beq	.L504
	cmp	w19, 1
	beq	.L505
	ldr	w5, [x1, 4096]
	ldr	w3, [x1, 4108]
	ldr	w2, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w2, w0, [x4, 8]
	stp	w5, w3, [x4, 16]
	cbz	w19, .L506
.L487:
	mov	w0, 180
	add	x4, x1, 32768
	add	x1, x4, 256
	smull	x2, w22, w0
	add	x0, x2, 52
	add	x2, x2, 180
	add	x0, x21, x0
	add	x3, x21, x2
	.p2align 2
.L488:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L488
	mov	w0, 0
	cbnz	w19, .L495
	lsl	x1, x20, 2
	ldr	w3, [x4, 384]
	sub	x20, x1, x20
	ldr	w2, [x4, 388]
	lsl	x1, x20, 4
	sub	x1, x1, x20
	add	x21, x21, x1, lsl 2
	stp	w2, w3, [x21, 44]
.L495:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L506:
	ldr	w5, [x1, 176]
	ldr	w0, [x1, 180]
	stp	w5, w0, [x4, 24]
	ldr	w3, [x1, 184]
	ldr	w2, [x1, 188]
	ldr	w0, [x1, 192]
	stp	w3, w2, [x4, 32]
	str	w0, [x4, 40]
	b	.L487
	.p2align 3
.L501:
	mov	w19, 0
	b	.L478
.L504:
	ldr	w2, [x1, 4108]
	mov	w0, 0
	str	w2, [x4, 20]
	and	w2, w2, 1048575
	ldr	w1, [x1, 176]
	stp	w2, w1, [x4, 20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L505:
	sub	x0, x5, x20
	and	w23, w3, 131071
	lsl	x0, x0, 2
	sub	x1, x0, x20
	add	x0, x0, x1, lsl 2
	add	x0, x24, x0
	ldr	w0, [x0, 56]
	bl	MEM_Phy2Vir
	cbz	x0, .L507
	sub	w1, w23, #1
	cmp	w1, 199
	bhi	.L493
	lsl	w1, w23, 2
	sub	w1, w1, #4
	lsl	x1, x1, 2
	add	x3, x1, 8
.L486:
	lsl	x2, x20, 2
	ldr	w4, [x0, x1]
	sub	x2, x2, x20
	lsl	x1, x2, 4
	sub	x2, x1, x2
	lsl	x1, x20, 6
	sub	x1, x1, x20
	add	x2, x21, x2, lsl 2
	lsl	x1, x1, 2
	str	w4, [x2, 16]
	ldr	w3, [x0, x3]
	sub	x0, x1, x20
	str	w3, [x2, 20]
	add	x1, x1, x0, lsl 2
	ldr	x1, [x24, x1]
	ldr	w3, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w3, w0, [x2, 8]
	b	.L487
.L503:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L483
	str	x0, [x24, x21]
	mov	x1, x0
	b	.L482
.L493:
	mov	x3, 8
	mov	x1, 0
	b	.L486
.L477:
	ldr	x2, .LC190
	mov	w4, 0
	ldr	x1, .LC191
	mov	w3, w22
	add	x2, x2, 216
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L495
.L507:
	ldr	x2, .LC190
	ldr	x3, .LC198
	ldr	x1, .LC199
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w0, -1
	b	.L495
.L483:
	ldr	x1, .LC195
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L495
	.size	VDMHAL_V5R6C1_UpdateHardwareInfo, .-VDMHAL_V5R6C1_UpdateHardwareInfo
	.align	3
.LC189:
	.xword	g_DSPState
	.align	3
.LC190:
	.xword	.LANCHOR1
	.align	3
.LC191:
	.xword	.LC1
	.align	3
.LC194:
	.xword	g_HwMem
	.align	3
.LC195:
	.xword	.LC3
	.align	3
.LC196:
	.xword	g_BackUp
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC199:
	.xword	.LC13
	.align	3
.LC200:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_ReadMsgSlot
	.type	VDMHAL_V5R6C1_ReadMsgSlot, %function
VDMHAL_V5R6C1_ReadMsgSlot:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	mov	w19, w2
	bl	_mcount
	cmp	x20, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L512
	cmp	w19, 800
	bhi	.L513
	ldr	x3, .LC205
	ubfiz	x2, x19, 2, 30
	mov	x1, x21
	mov	x0, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L510:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L513:
	ldr	x1, .LC204
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L510
	.p2align 3
.L512:
	ldr	x1, .LC202
	mov	x3, x21
	mov	x2, x20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L510
	.size	VDMHAL_V5R6C1_ReadMsgSlot, .-VDMHAL_V5R6C1_ReadMsgSlot
	.align	3
.LC202:
	.xword	.LC201
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC205:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_WriteMsgSlot
	.type	VDMHAL_V5R6C1_WriteMsgSlot, %function
VDMHAL_V5R6C1_WriteMsgSlot:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L515
	sub	w0, w21, #1
	cmp	w0, 255
	bhi	.L515
	ldr	x3, .LC208
	ubfiz	x2, x21, 2, 30
	mov	x1, x20
	mov	x0, x19
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L515:
	ldr	x1, .LC207
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMHAL_V5R6C1_WriteMsgSlot, .-VDMHAL_V5R6C1_WriteMsgSlot
	.align	3
.LC207:
	.xword	.LC206
	.align	3
.LC208:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CfgRpMsg
	.type	VDMHAL_V5R6C1_CfgRpMsg, %function
VDMHAL_V5R6C1_CfgRpMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 64]
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L565
	ldr	w2, [x19, 44]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L566
	ldr	w3, [x19, 64]
	ldp	w0, w2, [x19, 28]
	ldr	w6, [x19, 4]
	lsl	w0, w0, w3
	lsl	w2, w2, w3
	add	w1, w0, 255
	cmp	w0, 1920
	and	w1, w1, -256
	lsl	w3, w1, 4
	bgt	.L562
	cmp	w6, 17
	beq	.L562
	strb	wzr, [x19]
	mov	w4, 0
	strb	wzr, [x19, 1]
.L525:
	cmp	w6, 16
	beq	.L526
.L570:
	add	w0, w2, 31
	mov	w23, 8
	and	w0, w0, -32
	madd	w0, w0, w1, w4
.L549:
	ldr	w2, [x19, 20]
	mov	w1, w3
	str	w2, [x20]
	ldr	w2, [x19, 20]
	add	w2, w0, w2
	str	w2, [x20, 4]
	ldr	w2, [x19, 8]
	str	w2, [x20, 8]
	ldr	w2, [x19, 8]
	add	w0, w0, w2
	str	w0, [x20, 12]
	ldrb	w0, [x19, 1]
	cbnz	w0, .L567
.L528:
	str	w1, [x20, 16]
	mov	w3, 0
	str	w4, [x20, 20]
	mov	w2, 0
	ldp	w1, w0, [x19, 28]
	sub	w0, w0, #1
	sub	w1, w1, #1
	bfi	w2, w0, 0, 9
	bfi	w3, w1, 0, 9
	strh	w2, [x29, 74]
	strh	w3, [x29, 72]
	ldr	w0, [x29, 72]
	str	w0, [x20, 24]
	ldr	w0, [x19, 52]
	ldp	w21, w22, [x19, 28]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L568
.L530:
	ldr	w0, [x19, 56]
	mov	w11, 0
	cbz	w0, .L569
.L531:
	cmp	w0, 1
	beq	.L547
.L575:
	sub	w11, w11, #1
	uxth	w11, w11
.L548:
	ldr	w3, [x19, 64]
	ldrb	w4, [x19]
	ldr	w2, [x19, 52]
	sub	w3, w3, #4
	ldrb	w1, [x29, 74]
	ldrb	w0, [x29, 75]
	and	w2, w2, 3
	bfi	w1, w4, 0, 1
	strh	w11, [x29, 72]
	bfi	w0, w3, 0, 2
	ldrb	w3, [x19, 1]
	bfi	w1, w2, 4, 2
	bfi	w0, w23, 2, 4
	bfi	w1, w2, 6, 2
	bfi	w0, w3, 6, 1
	strb	w1, [x29, 74]
	strb	w0, [x29, 75]
	mov	w0, 0
	ldr	w1, [x29, 72]
	str	w1, [x20, 28]
.L561:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L562:
	ldrb	w4, [x19]
	strb	wzr, [x19, 1]
	cmp	w4, 1
	mov	w4, 0
	bne	.L525
	adds	w4, w0, 2047
	add	w0, w0, 4094
	csel	w0, w0, w4, mi
	add	w5, w2, 126
	and	w0, w0, -2048
	cmp	w0, wzr
	add	w4, w0, 127
	csel	w0, w4, w0, lt
	adds	w7, w2, 63
	csel	w4, w5, w7, mi
	asr	w0, w0, 7
	asr	w4, w4, 6
	cmp	w6, 16
	lsl	w4, w4, 5
	mul	w4, w0, w4
	bne	.L570
.L526:
	madd	w0, w2, w1, w4
	mov	w23, 10
	b	.L549
	.p2align 3
.L567:
	add	w0, w3, 15
	cmp	w3, wzr
	csel	w1, w0, w3, lt
	asr	w1, w1, 4
	b	.L528
	.p2align 3
.L569:
	ldr	w0, [x19, 64]
	cmp	w0, 6
	beq	.L552
	cmp	w0, 5
	beq	.L553
	cmp	w0, 4
	mov	w2, 8
	beq	.L532
	ldr	x1, .LC216
	mov	w0, 1
	bl	dprint_vfmw
	mov	w2, 1
.L532:
	ldr	w8, [x19, 44]
	cmp	w8, wzr
	ble	.L563
	mul	w12, w22, w21
	mov	w4, 0
	mov	w6, 0
	sub	w13, w12, #1
	mov	w11, 0
	sub	w9, w2, #1
	b	.L535
	.p2align 3
.L573:
	ldrsh	w6, [x10, 74]
	sub	w6, w6, #1
	add	w6, w6, w2
	udiv	w6, w6, w2
	mul	w6, w6, w2
	cmp	w0, w6
	bgt	.L538
.L537:
	add	w4, w4, 1
	cmp	w4, w8
	bge	.L571
.L546:
	cmp	w4, 199
	bgt	.L572
.L535:
	add	x10, x19, x4, sxtw 2
	cmp	w4, wzr
	ldrsh	w1, [x10, 78]
	sub	w0, w1, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	bgt	.L573
	ccmp	w0, w6, 0, ne
	ble	.L537
.L540:
	ldrsh	w1, [x10, 76]
	cmp	w12, w0
	csel	w0, w0, w13, hi
	add	w5, w11, 1
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w5, 250
	bgt	.L574
	udiv	w7, w1, w21
	sxtw	x3, w11
	mov	w11, w5
	mov	w8, 0
	add	x3, x3, 6
	add	w4, w4, 1
	lsl	x3, x3, 3
	udiv	w5, w0, w21
	msub	w1, w7, w21, w1
	bfi	w8, w1, 0, 9
	mov	w1, 0
	bfi	w1, w7, 0, 9
	strh	w8, [x29, 76]
	strh	w1, [x29, 78]
	mov	w1, 0
	msub	w0, w5, w21, w0
	bfi	w1, w0, 0, 9
	mov	w0, 0
	bfi	w0, w5, 0, 9
	ldr	w5, [x29, 76]
	str	w5, [x20, x3]
	add	x3, x3, 4
	strh	w1, [x29, 76]
	strh	w0, [x29, 78]
	ldr	w0, [x29, 76]
	str	w0, [x20, x3]
	ldr	w8, [x19, 44]
	cmp	w4, w8
	blt	.L546
.L571:
	ldr	w0, [x19, 56]
	cmp	w0, 1
	bne	.L575
	.p2align 2
.L547:
	strh	wzr, [x29, 72]
	sub	w21, w21, #1
	strh	wzr, [x29, 74]
	mov	w2, 0
	sub	w22, w22, #1
	mov	w1, 0
	ldr	w3, [x29, 72]
	bfi	w2, w21, 0, 9
	bfi	w1, w22, 0, 9
	strh	w2, [x29, 72]
	strh	w1, [x29, 74]
	mov	w11, 0
	str	w0, [x19, 44]
	str	w3, [x20, 48]
	ldr	w0, [x29, 72]
	str	w0, [x20, 52]
	b	.L548
	.p2align 3
.L568:
	add	w22, w22, w22, lsr 31
	asr	w22, w22, 1
	b	.L530
	.p2align 3
.L541:
	udiv	w0, w0, w2
	ldrsh	w1, [x5, 80]
	udiv	w1, w1, w2
	mul	w0, w0, w2
	mul	w1, w1, w2
	cmp	w0, w1
	add	w14, w1, 1
	bhi	.L542
	sub	w1, w4, #1
	cmp	w0, w14
	add	x1, x19, x1, sxtw 2
	beq	.L542
	ldrsh	w1, [x1, 78]
	sub	w1, w1, #1
	add	w1, w1, w2
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w0, w1
	bhi	.L540
.L542:
	cmp	w7, 199
	mov	w4, w3
	bgt	.L576
	ldrsh	w1, [x5, 82]
.L538:
	add	w3, w4, 1
	add	x5, x19, x4, sxtw 2
	cmp	w8, w3
	add	w0, w9, w1
	add	w7, w3, 1
	bgt	.L541
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L540
.L553:
	mov	w2, 4
	b	.L532
	.p2align 3
.L576:
	add	x0, x19, x3, sxtw 2
	ldrsh	w0, [x0, 78]
	sub	w0, w0, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L540
.L572:
	ldr	x2, .LC211
	mov	w3, 2152
	ldr	x1, .LC218
	mov	w0, 0
	add	x2, x2, 280
	bl	dprint_vfmw
.L563:
	mov	w11, 0
	ldr	w0, [x19, 56]
	b	.L531
.L552:
	mov	w2, 2
	b	.L532
.L574:
	mov	w0, 1
	str	w0, [x19, 56]
	b	.L547
.L566:
	ldr	x1, .LC214
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L561
.L565:
	ldr	x2, .LC211
	mov	w0, 0
	ldr	x3, .LC210
	ldr	x1, .LC212
	add	x2, x2, 256
	bl	dprint_vfmw
	mov	w0, -1
	b	.L561
	.size	VDMHAL_V5R6C1_CfgRpMsg, .-VDMHAL_V5R6C1_CfgRpMsg
	.align	3
.LC210:
	.xword	.LC209
	.align	3
.LC211:
	.xword	.LANCHOR1
	.align	3
.LC212:
	.xword	.LC13
	.align	3
.LC214:
	.xword	.LC213
	.align	3
.LC216:
	.xword	.LC215
	.align	3
.LC218:
	.xword	.LC217
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_MakeDecReport
	.type	VDMHAL_V5R6C1_MakeDecReport, %function
VDMHAL_V5R6C1_MakeDecReport:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L607
	ldr	x23, [x19, 8]
	ldr	w21, [x19]
	ldr	w22, [x19, 16]
	cbz	x23, .L608
	sxtw	x22, w22
	ldr	x20, .LC227
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x0, [x20, x0]
	cbz	x0, .L581
	ldr	x2, .LC228
	add	x0, x2, 4
	add	x2, x2, 128
	ldr	w1, [x2, -128]
	cmp	w1, 1
	bne	.L584
	b	.L596
	.p2align 3
.L610:
	cmp	x0, x2
	beq	.L609
.L584:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L610
.L596:
	mov	w19, w1
.L582:
	ldr	x3, .LC232
	mov	x2, 824
	mov	w1, 0
	mov	x0, x23
	ldr	x3, [x3, 96]
	blr	x3
	lsl	x0, x22, 6
	lsl	x1, x22, 2
	sub	x0, x0, x22
	sub	x1, x1, x22
	lsl	x0, x0, 2
	lsl	x2, x1, 4
	sub	x3, x0, x22
	sub	x1, x2, x1
	ldr	x4, .LC233
	add	x2, x0, x3, lsl 2
	add	x2, x20, x2
	add	x1, x4, x1, lsl 2
	ldr	w0, [x2, 40]
	str	w0, [x23, 4]
	ldr	w1, [x1, 4]
	ubfx	x0, x1, 17, 2
	cmp	w0, 1
	beq	.L597
	and	w1, w1, 131072
	cmp	w1, wzr
	ccmp	w21, 3, 0, ne
	cset	w1, ne
.L585:
	lsl	x0, x22, 2
	str	w1, [x23]
	sub	x0, x0, x22
	cmp	w21, wzr
	lsl	x1, x0, 4
	ccmp	w21, 15, 4, ne
	sub	x0, x1, x0
	add	x0, x4, x0, lsl 2
	ldr	w2, [x0, 4]
	and	w2, w2, 131071
	str	w2, [x23, 12]
	beq	.L611
.L586:
	cmp	w2, 200
	bhi	.L612
.L588:
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	add	x20, x20, x0
	ldr	w21, [x20, 56]
	mov	w0, w21
	bl	MEM_Phy2Vir
	cbz	x0, .L613
	lsl	x3, x22, 2
	ldr	x19, .LC238
	sub	x3, x3, x22
	ldr	w2, [x23, 12]
	mov	x1, x0
	add	x20, x22, x3, lsl 3
	lsl	w2, w2, 2
	lsl	x24, x20, 7
	add	x0, x19, x24
	bl	VDMHAL_V5R6C1_ReadMsgSlot
	ldr	w1, [x19, x24]
	ldr	w0, [x23, 12]
	lsr	w1, w1, 31
	str	w1, [x23, 16]
	cbz	w0, .L593
	sub	w2, w0, #1
	mov	x5, 26
	add	x1, x23, 22
	mov	w0, 2
	add	x5, x5, x2, uxtw 2
	lsl	x3, x20, 5
	add	x5, x23, x5
	.p2align 2
.L592:
	sub	w2, w0, #1
	add	x4, x3, x0, uxtw
	add	x2, x3, x2
	add	w0, w0, 4
	ldr	w2, [x19, x2, lsl 2]
	strh	w2, [x1, -2]
	ldr	w2, [x19, x4, lsl 2]
	strh	w2, [x1], 4
	cmp	x5, x1
	bne	.L592
.L593:
	mov	w0, 6
	bl	IsDprintTypeEnable
	cbnz	w0, .L614
.L579:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L611:
	cmp	w19, 1
	beq	.L615
	ldr	x1, .LC234
	ldrb	w1, [x1]
	cbnz	w1, .L586
	ldrb	w0, [x0, 19]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L586
	mov	w0, 1
	strh	wzr, [x23, 20]
	str	w0, [x23, 12]
	mov	w0, 0
	strh	wzr, [x23, 22]
	b	.L579
	.p2align 3
.L609:
	mov	w19, 0
	b	.L582
	.p2align 3
.L614:
	ldr	x1, .LC240
	mov	w0, 6
	ldr	w2, [x23, 12]
	mov	w20, 0
	bl	dprint_vfmw
	mov	w2, w21
	ldr	x1, .LC242
	lsl	x21, x22, 2
	mov	w0, 6
	sub	x21, x21, x22
	bl	dprint_vfmw
	ldr	x24, .LC244
	add	x21, x22, x21, lsl 3
	lsl	x21, x21, 5
	.p2align 2
.L594:
	add	w1, w20, 3
	add	w3, w20, 2
	add	w0, w20, 1
	add	x7, x21, x20, uxtw
	add	x1, x21, x1
	add	x3, x21, x3
	add	x0, x21, x0
	mov	w2, w20
	add	w20, w20, 4
	ldr	w6, [x19, x1, lsl 2]
	mov	x1, x24
	ldr	w5, [x19, x3, lsl 2]
	ldr	w4, [x19, x0, lsl 2]
	mov	w0, 6
	ldr	w3, [x19, x7, lsl 2]
	bl	dprint_vfmw
	ldr	w0, [x23, 12]
	lsl	w0, w0, 2
	sub	w0, w0, #3
	cmp	w0, w20
	bhi	.L594
	ldr	x1, .LC246
	mov	w0, 6
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L597:
	mov	w1, 0
	b	.L585
	.p2align 3
.L612:
	ldr	x1, .LC236
	mov	w3, 200
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 12]
	b	.L588
	.p2align 3
.L615:
	ldr	w0, [x0, 16]
	ubfx	x0, x0, 21, 2
	cmp	w0, 2
	bne	.L586
	strh	wzr, [x23, 20]
	mov	w0, 0
	strh	wzr, [x23, 22]
	str	w19, [x23, 12]
	b	.L579
.L613:
	ldr	x2, .LC223
	ldr	x3, .LC237
	ldr	x1, .LC224
	add	x2, x2, 304
	bl	dprint_vfmw
	mov	w0, -1
	b	.L579
.L581:
	ldr	x2, .LC223
	ldr	x3, .LC229
.L605:
	ldr	x1, .LC224
	mov	w0, 0
	add	x2, x2, 304
	bl	dprint_vfmw
	mov	w0, -1
	b	.L579
.L608:
	ldr	x2, .LC223
	ldr	x3, .LC226
	b	.L605
.L607:
	ldr	x2, .LC223
	ldr	x3, .LC222
	b	.L605
	.size	VDMHAL_V5R6C1_MakeDecReport, .-VDMHAL_V5R6C1_MakeDecReport
	.align	3
.LC222:
	.xword	.LC221
	.align	3
.LC223:
	.xword	.LANCHOR1
	.align	3
.LC224:
	.xword	.LC13
	.align	3
.LC226:
	.xword	.LC225
	.align	3
.LC227:
	.xword	g_HwMem
	.align	3
.LC228:
	.xword	g_DSPState
	.align	3
.LC229:
	.xword	.LC169
	.align	3
.LC232:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC233:
	.xword	g_BackUp
	.align	3
.LC234:
	.xword	g_not_allow_H264FullPictureRepair_flag
	.align	3
.LC236:
	.xword	.LC235
	.align	3
.LC237:
	.xword	.LC197
	.align	3
.LC238:
	.xword	g_UpMsg
	.align	3
.LC240:
	.xword	.LC239
	.align	3
.LC242:
	.xword	.LC241
	.align	3
.LC244:
	.xword	.LC243
	.align	3
.LC246:
	.xword	.LC245
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_PrepareRepair
	.type	VDMHAL_V5R6C1_PrepareRepair, %function
VDMHAL_V5R6C1_PrepareRepair:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w3
	mov	x24, x1
	mov	w26, w2
	mov	x23, x4
	bl	_mcount
	ldr	x25, .LC247
	lsl	x0, x19, 6
	cmp	w19, wzr
	sub	x0, x0, x19
	mov	x21, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	add	x27, x20, x25
	bgt	.L627
	ldr	x0, [x20, x25]
	cbz	x0, .L628
	cbz	w26, .L629
.L621:
	cmp	w26, 1
	mov	w20, 0
	beq	.L630
.L618:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L628:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L620
	str	x0, [x20, x25]
	cbnz	w26, .L621
	.p2align 2
.L629:
	lsl	x0, x19, 3
	ldr	x25, .LC252
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x25, x0, lsl 3
	ldr	w1, [x0, 44]
	cmp	w1, wzr
	ble	.L622
	cmp	w22, 6
	bne	.L623
	ldrb	w1, [x24, 17]
	mov	w2, 0
	cmp	w1, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 928]
.L623:
	mov	x3, x23
	mov	w2, w21
	add	x1, x27, 64
	mov	x0, x27
	mov	w20, 0
	bl	VDMHAL_V5R6C1_CfgRpReg.isra.9
	lsl	x0, x19, 3
	mov	w2, w21
	sub	x0, x0, x19
	mov	x1, x27
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x25, x0, lsl 3
	bl	VDMHAL_V5R6C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L630:
	cmp	w22, 6
	bne	.L625
	ldrb	w0, [x24, 17]
	cmp	w0, 1
	bne	.L625
	lsl	x0, x19, 3
	ldr	x22, .LC252
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	lsl	x19, x19, 3
	add	x0, x22, x19
	ldr	w1, [x0, 920]
	cmp	w1, wzr
	ble	.L625
	mov	w4, 2
	mov	x3, x23
	str	w4, [x0, 928]
	mov	w2, w21
	add	x1, x27, 64
	mov	x0, x27
	bl	VDMHAL_V5R6C1_CfgRpReg.isra.9
	add	x0, x19, 876
	mov	w2, w21
	mov	x1, x27
	add	x0, x22, x0
	bl	VDMHAL_V5R6C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L627:
	ldr	x2, .LC248
	mov	w4, 0
	ldr	x1, .LC249
	mov	w3, w19
	add	x2, x2, 336
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L618
	.p2align 3
.L625:
	ldr	x1, .LC256
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	b	.L618
.L622:
	ldr	x1, .LC254
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	b	.L618
.L620:
	ldr	x1, .LC251
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L618
	.size	VDMHAL_V5R6C1_PrepareRepair, .-VDMHAL_V5R6C1_PrepareRepair
	.align	3
.LC247:
	.xword	g_HwMem
	.align	3
.LC248:
	.xword	.LANCHOR1
	.align	3
.LC249:
	.xword	.LC1
	.align	3
.LC251:
	.xword	.LC250
	.align	3
.LC252:
	.xword	g_RepairParam
	.align	3
.LC254:
	.xword	.LC253
	.align	3
.LC256:
	.xword	.LC255
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_StartHwRepair
	.type	VDMHAL_V5R6C1_StartHwRepair, %function
VDMHAL_V5R6C1_StartHwRepair:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC257
	ldrb	w4, [x21]
	cmp	w4, 1
	bne	.L655
	cmp	w20, wzr
	ble	.L656
	ldr	x22, .LC259
	mov	w3, w20
	ldr	x23, .LC260
	mov	w0, 32
	add	x2, x22, 368
	mov	x1, x23
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L639
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L652
.L634:
	cbz	x19, .L657
.L648:
	ldr	x1, .LC263
	sbfiz	x0, x20, 6, 32
	mov	w2, 1
	str	w2, [x19, 4]
	add	x1, x1, x0
	mov	x0, x19
	ldr	w1, [x1, 8]
	str	w1, [x19, 8]
	strb	w20, [x19]
	strb	w2, [x19, 2]
	bl	VDH_PostTask
.L631:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L656:
	sxtw	x0, w20
	ldr	x3, .LC258
	lsl	x1, x0, 6
	mov	w4, 67108864
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x2, x1, x0
	add	x1, x1, x2, lsl 2
	ldr	x1, [x3, x1]
	str	w4, [x1, 8]
.L637:
	lsl	x1, x0, 6
	mov	w2, -2
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x3, x0]
	str	w2, [x0, 36]
.L635:
	ldr	x0, .LC264
	ldr	x0, [x0, 224]
	blr	x0
	cmp	w20, wzr
	ble	.L651
	ldr	x22, .LC259
	ldr	x23, .LC260
.L644:
	add	x22, x22, 384
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	b	.L631
	.p2align 3
.L633:
	cmp	w20, wzr
	ble	.L649
	ldr	x22, .LC259
	ldr	x23, .LC260
.L639:
	mov	w4, 1
	mov	w3, w20
	add	x2, x22, 368
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	bne	.L634
.L652:
	ldr	x0, .LC264
	ldr	x0, [x0, 224]
	blr	x0
	b	.L644
	.p2align 3
.L655:
	mov	x0, x19
	mov	w3, 67108864
	mov	w2, 8
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L633
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L635
	cbnz	x19, .L648
.L657:
	ldr	x2, .LC259
	mov	x3, 0
	ldr	x1, .LC262
	mov	w0, 0
	add	x2, x2, 384
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L651:
	lsl	x0, x20, 6
	ldr	x1, .LC258
	sub	x0, x0, x20
	mov	w3, 1
	lsl	x0, x0, 2
	sub	x20, x0, x20
	add	x0, x0, x20, lsl 2
	ldr	x2, [x1, x0]
	str	wzr, [x2]
	ldr	x2, [x1, x0]
	str	w3, [x2]
	ldr	x0, [x1, x0]
	str	wzr, [x0]
	b	.L631
.L649:
	ldr	x3, .LC258
	sxtw	x0, w20
	b	.L637
	.size	VDMHAL_V5R6C1_StartHwRepair, .-VDMHAL_V5R6C1_StartHwRepair
	.align	3
.LC257:
	.xword	g_HalDisable
	.align	3
.LC258:
	.xword	g_HwMem
	.align	3
.LC259:
	.xword	.LANCHOR1
	.align	3
.LC260:
	.xword	.LC109
	.align	3
.LC262:
	.xword	.LC261
	.align	3
.LC263:
	.xword	g_VdmDrvParam
	.align	3
.LC264:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_CalVdhClkSkip
	.type	VDMHAL_V5R6C1_CalVdhClkSkip, %function
VDMHAL_V5R6C1_CalVdhClkSkip:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	bl	_mcount
	ldr	x24, .LC266
	ldr	w28, [x24, 128]
	tbnz	w28, #31, .L690
	ldr	x25, .LC269
	add	x20, x24, 132
	ldr	x27, .LC272
	add	x24, x24, 256
	ldr	x26, .LC271
	mov	w23, 30
	mov	w22, 0
	mov	w21, 0
	add	x25, x25, 416
	mov	w19, 0
	b	.L661
	.p2align 3
.L693:
	mov	w3, w28
	mov	x2, x25
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
.L663:
	cmp	x24, x20
	beq	.L691
.L680:
	ldr	w28, [x20], 4
	tbnz	w28, #31, .L692
.L661:
	mov	w0, w28
	bl	VCTRL_IsChanActive
	cbnz	w0, .L693
	mov	w0, w28
	bl	FSP_GetInst
	cbz	x0, .L664
	ldp	w1, w0, [x0, 40]
	adds	w19, w1, 15
	add	w1, w1, 30
	add	w21, w0, 30
	csel	w19, w1, w19, mi
	adds	w0, w0, 15
	asr	w19, w19, 4
	csel	w0, w21, w0, mi
	asr	w21, w0, 4
.L664:
	ldr	x1, [x27, w28, sxtw 3]
	mov	w0, w28
	ldr	w1, [x1, 1640]
	cmp	w1, 31
	csel	w23, w23, w1, lt
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	bls	.L694
.L683:
	cmp	x24, x20
	mov	w22, 0
	bne	.L680
.L691:
	lsl	w0, w22, 2
	mov	w3, 23813
	sub	w22, w0, w22
	movk	w3, 0xdb4f, lsl 16
	lsl	w1, w22, 6
	mov	w0, 32
	mov	w2, 25
	umull	x1, w1, w3
	ldp	x19, x20, [sp, 16]
	lsr	x1, x1, 53
	sub	w0, w0, w1
	cmp	w0, w2
	csel	w0, w0, w2, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L694:
	ldr	x1, .LC273
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx667
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx667:
	.section	.rodata
	.align	0
	.align	2
.L667:
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L683 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L683 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L683 - .Lrtx667) / 4
	.byte	(.L677 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.byte	(.L676 - .Lrtx667) / 4
	.text
	.p2align 3
.L676:
	mul	w22, w19, w21
	mul	w22, w22, w23
	b	.L663
	.p2align 3
.L692:
	lsl	w1, w22, 2
	mov	w0, 23813
	sub	w22, w1, w22
	movk	w0, 0xdb4f, lsl 16
	lsl	w22, w22, 6
	mov	w1, 32
	mov	w2, 25
	umull	x0, w22, w0
	lsr	x0, x0, 53
	sub	w0, w1, w0
	cmp	w0, w2
	csel	w0, w0, w2, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
.L659:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L677:
	mul	w22, w19, w21
	mul	w22, w22, w23
	lsl	w22, w22, 1
	b	.L663
.L690:
	mov	w0, 25
	b	.L659
	.size	VDMHAL_V5R6C1_CalVdhClkSkip, .-VDMHAL_V5R6C1_CalVdhClkSkip
	.align	3
.LC266:
	.xword	g_ChanCtx
	.align	3
.LC269:
	.xword	.LANCHOR1
	.align	3
.LC271:
	.xword	.LC270
	.align	3
.LC272:
	.xword	s_pstVfmwChan
	.align	3
.LC273:
	.xword	.L667
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetVdmClk
	.type	VDMHAL_V5R6C1_GetVdmClk, %function
VDMHAL_V5R6C1_GetVdmClk:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 3
	bls	.L703
.L696:
	ldr	x0, .LC276
	sbfiz	x19, x19, 6, 32
	mov	w1, 500
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L703:
	ldr	x0, .LC275
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx698
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx698:
	.section	.rodata
	.align	0
	.align	2
.L698:
	.byte	(.L696 - .Lrtx698) / 4
	.byte	(.L699 - .Lrtx698) / 4
	.byte	(.L700 - .Lrtx698) / 4
	.byte	(.L701 - .Lrtx698) / 4
	.text
	.p2align 3
.L700:
	ldr	x0, .LC276
	sbfiz	x19, x19, 6, 32
	mov	w1, 100
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L699:
	ldr	x0, .LC276
	sbfiz	x19, x19, 6, 32
	mov	w1, 540
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L701:
	ldr	x0, .LC276
	sbfiz	x19, x19, 6, 32
	mov	w1, 600
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R6C1_GetVdmClk, .-VDMHAL_V5R6C1_GetVdmClk
	.align	3
.LC275:
	.xword	.L698
	.align	3
.LC276:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_StartHwDecode
	.type	VDMHAL_V5R6C1_StartHwDecode, %function
VDMHAL_V5R6C1_StartHwDecode:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w0, 8
	cmp	w20, wzr
	str	w0, [x29, 92]
	ble	.L705
	ldr	x2, .LC277
	mov	w4, 0
	ldr	x1, .LC278
	mov	w3, w20
	add	x2, x2, 448
	mov	w0, 0
	bl	dprint_vfmw
.L704:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L705:
	add	x0, x29, 92
	bl	HI_DRV_SYS_GetChipPackageType
	ldr	x22, .LC279
	ldr	w0, [x29, 92]
	ldrb	w1, [x22]
	cmp	w0, wzr
	cset	w21, ne
	cmp	w1, 1
	bne	.L744
	ldr	x0, .LC280
	ldr	x2, [x0]
	ldr	w0, [x2, 120]
	ubfx	x3, x0, 8, 2
	cmp	w3, w21
	beq	.L737
	bfi	w0, w21, 8, 2
	str	w0, [x2, 120]
.L737:
	ldr	x0, .LC281
	ldr	x23, .LC282
	ldrb	w0, [x0,w21,uxtw]
	adr	x2, .Lrtx712
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx712:
	.section	.rodata
	.align	0
	.align	2
.L712:
	.byte	(.L711 - .Lrtx712) / 4
	.byte	(.L713 - .Lrtx712) / 4
	.byte	(.L714 - .Lrtx712) / 4
	.byte	(.L715 - .Lrtx712) / 4
	.text
	.p2align 3
.L714:
	sxtw	x21, w20
	mov	w2, 100
	add	x0, x23, x21, lsl 6
	str	w2, [x0, 16]
.L716:
	add	x0, x23, x21, lsl 6
	ldr	x2, .LC283
	cmp	w1, 1
	ldr	w24, [x0, 8]
	ldr	x0, [x2, w24, sxtw 3]
	ldr	w25, [x0, 1312]
	bne	.L745
	ldr	x0, .LC280
	ldr	x0, [x0]
	ldr	w1, [x0, 120]
	and	w1, w1, -258049
	str	w1, [x0, 120]
	ldr	w1, [x0, 120]
	orr	w1, w1, 131072
	str	w1, [x0, 120]
.L718:
	mov	w0, 12
	mov	x3, x19
	mov	w2, w20
	mov	w1, 3
	bl	SCD_ConfigReg
	ldrb	w0, [x22]
	cmp	w0, 1
	beq	.L746
	mov	w1, 2
	mov	x0, x19
	mov	w3, -1431655766
	mov	w2, 156
	bl	VDH_Record_RegData
	ldr	x1, .LC284
	ldrb	w0, [x22]
	ldr	w1, [x1]
	cmp	w1, 1
	beq	.L747
.L720:
	mov	w3, 0
.L719:
	cmp	w0, 1
	beq	.L748
	mov	x0, x19
	mov	w2, 61472
	mov	w1, 2
	bl	VDH_Record_RegData
	cmp	w25, 1
	ldrb	w0, [x22]
	beq	.L749
.L723:
	mov	w3, -2
.L722:
	cmp	w0, 1
	beq	.L750
	mov	x0, x19
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x22]
	cmp	w0, 1
	beq	.L751
	cbz	x19, .L752
	mov	w0, 1
	strb	w20, [x19]
	stp	w0, w24, [x19, 4]
	mov	x0, x19
	bl	VDH_PostTask
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L749:
	mov	w3, -6
	b	.L722
	.p2align 3
.L747:
	mov	w3, 15
	b	.L719
	.p2align 3
.L713:
	sxtw	x21, w20
	mov	w2, 540
	add	x0, x23, x21, lsl 6
	str	w2, [x0, 16]
	b	.L716
	.p2align 3
.L711:
	sxtw	x21, w20
	mov	w2, 500
	add	x0, x23, x21, lsl 6
	str	w2, [x0, 16]
	b	.L716
	.p2align 3
.L715:
	sxtw	x21, w20
	mov	w2, 600
	add	x0, x23, x21, lsl 6
	str	w2, [x0, 16]
	b	.L716
	.p2align 3
.L744:
	mov	w1, 0
	mov	w3, w21
	mov	w2, 0
	mov	x0, x19
	bl	VDH_Record_RegData
	ldrb	w1, [x22]
	b	.L737
	.p2align 3
.L745:
	mov	w3, 0
	mov	w2, 1
	mov	w1, 0
	mov	x0, x19
	bl	VDH_Record_RegData
	b	.L718
	.p2align 3
.L746:
	ldr	x2, .LC284
	lsl	x1, x21, 6
	sub	x1, x1, x21
	ldr	x26, .LC285
	lsl	x1, x1, 2
	ldr	w2, [x2]
	cmp	w2, 1
	sub	x2, x1, x21
	add	x1, x1, x2, lsl 2
	mov	w2, -1431655766
	ldr	x1, [x26, x1]
	str	w2, [x1, 156]
	bne	.L720
	mov	w3, 15
	b	.L721
	.p2align 3
.L750:
	ldr	x26, .LC285
.L724:
	lsl	x1, x21, 6
	ldr	x19, .LC286
	sub	x1, x1, x21
	mov	x0, 30
	lsl	x1, x1, 2
	sub	x2, x1, x21
	add	x1, x1, x2, lsl 2
	ldr	x1, [x26, x1]
	str	w3, [x1, 36]
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
.L727:
	lsl	x0, x21, 6
	mov	w2, 1
	sub	x1, x0, x21
	add	x23, x23, x0
	lsl	x0, x1, 2
	ldr	x3, .LC288
	sub	x21, x0, x21
	mov	w1, 4
	add	x21, x0, x21, lsl 2
	ldr	x0, [x26, x21]
	str	wzr, [x0]
	ldr	x0, [x26, x21]
	str	w2, [x0]
	ldr	x0, [x26, x21]
	str	wzr, [x0]
	ldr	w2, [x23, 8]
	mov	w0, w2
	ldr	w2, [x3, w2, sxtw 2]
	bl	VDEC_Lowdelay_Event_Time
	b	.L704
	.p2align 3
.L748:
	ldr	x26, .LC285
.L721:
	lsl	x0, x21, 6
	cmp	w25, 1
	sub	x0, x0, x21
	lsl	x0, x0, 2
	sub	x1, x0, x21
	add	x0, x0, x1, lsl 2
	ldr	x0, [x26, x0]
	add	x0, x0, 61440
	str	w3, [x0, 32]
	beq	.L736
	mov	w0, 1
	b	.L723
	.p2align 3
.L752:
	ldr	x2, .LC277
	mov	x3, 0
	ldr	x1, .LC287
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	b	.L704
	.p2align 3
.L736:
	mov	w3, -6
	b	.L724
.L751:
	ldr	x19, .LC286
	mov	x0, 30
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
	ldr	x26, .LC285
	b	.L727
	.size	VDMHAL_V5R6C1_StartHwDecode, .-VDMHAL_V5R6C1_StartHwDecode
	.align	3
.LC277:
	.xword	.LANCHOR1
	.align	3
.LC278:
	.xword	.LC1
	.align	3
.LC279:
	.xword	g_HalDisable
	.align	3
.LC280:
	.xword	g_pstRegCrg
	.align	3
.LC281:
	.xword	.L712
	.align	3
.LC282:
	.xword	g_VdmDrvParam
	.align	3
.LC283:
	.xword	s_pstVfmwChan
	.align	3
.LC284:
	.xword	mask_mmu_err_int
	.align	3
.LC285:
	.xword	g_HwMem
	.align	3
.LC286:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC287:
	.xword	.LC261
	.align	3
.LC288:
	.xword	g_LowDelaySeqIndex
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_GetCharacter
	.type	VDMHAL_V5R6C1_GetCharacter, %function
VDMHAL_V5R6C1_GetCharacter:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC289
	mov	w3, 15
	ldr	x0, .LC290
	mov	w1, 4
	str	w3, [x2]
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R6C1_GetCharacter, .-VDMHAL_V5R6C1_GetCharacter
	.align	3
.LC289:
	.xword	g_VdmCharacter
	.align	3
.LC290:
	.xword	g_eVdmVersion
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.type	VDMHAL_V5R6C1_WriteBigTitle1DYuv, %function
VDMHAL_V5R6C1_WriteBigTitle1DYuv:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 112]
	mov	x0, x30
	mov	w21, w3
	mov	x22, x1
	mov	w19, w2
	str	w4, [x29, 108]
	bl	_mcount
	ubfx	x0, x21, 29, 2
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	cmp	w0, 1
	beq	.L798
	mov	w20, 2
	cmp	w0, w20
	csinc	w20, w20, wzr, ne
.L755:
	ldr	x0, [x29, 112]
	cbz	x0, .L754
	ldr	x0, .LC292
	mov	w4, 0
	add	x3, x29, 144
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L758
	ldr	x0, .LC296
	mov	w4, 0
	add	x3, x29, 176
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L758
	add	w19, w19, 15
	add	w21, w21, 15
	and	w19, w19, -16
	and	w0, w21, -16
	add	w1, w19, 255
	mov	w3, w0
	and	w1, w1, -256
	add	w0, w0, 62
	lsl	w1, w1, 4
	ldr	x25, [x29, 184]
	mov	w2, w1
	adds	w1, w3, 31
	csel	w0, w0, w1, mi
	add	w21, w2, 15
	cmp	w2, wzr
	asr	w0, w0, 5
	csel	w21, w21, w2, lt
	cmp	w20, wzr
	asr	w21, w21, 4
	ccmp	w20, 3, 4, ne
	stp	w2, w3, [x29, 124]
	mul	w21, w0, w21
	add	x21, x22, x21, sxtw
	bne	.L759
	lsr	w1, w3, 1
	lsr	w0, w19, 1
	str	w1, [x29, 120]
	add	x1, x25, 2097152
	str	w0, [x29, 104]
	str	x1, [x29, 136]
	ldr	x28, .LC297
	ldr	x20, [x29, 152]
	cbz	w3, .L761
	mov	w27, 0
	str	wzr, [x29, 132]
	.p2align 2
.L760:
	cbz	w19, .L763
	ldr	w0, [x29, 124]
	lsr	w23, w27, 4
	ldr	w24, [x29, 132]
	mov	w26, 0
	mul	w0, w23, w0
	ubfiz	x23, x27, 8, 4
	add	x23, x0, x23
	.p2align 2
.L762:
	lsr	w1, w26, 8
	add	x0, x24, x26, uxtw
	ubfiz	x1, x1, 12, 20
	ldr	x5, [x28, 104]
	add	x1, x1, x23
	mov	x2, 256
	add	x1, x22, x1
	add	x0, x20, x0
	add	w26, w26, 256
	blr	x5
	cmp	w19, w26
	bhi	.L762
.L763:
	ldr	w0, [x29, 132]
	add	w27, w27, 1
	add	w0, w0, w19
	str	w0, [x29, 132]
	ldr	w0, [x29, 128]
	cmp	w0, w27
	bne	.L760
.L761:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	blr	x3
	ldr	w0, [x29, 120]
	cbz	w0, .L853
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 132]
	.p2align 2
.L767:
	cbz	w19, .L769
	ldr	w0, [x29, 132]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L766:
	lsr	w1, w27, 8
	add	x0, x23, x27, uxtw
	ubfiz	x1, x1, 11, 21
	ldr	x5, [x28, 104]
	add	x1, x1, x22
	mov	x2, 256
	add	x1, x21, x1
	add	x0, x20, x0
	add	w27, w27, 256
	blr	x5
	cmp	w19, w27
	bhi	.L766
.L769:
	ldr	w0, [x29, 120]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L767
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L854
.L795:
	ldr	w0, [x29, 108]
	cbnz	w0, .L772
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	ldr	x0, [x29, 136]
	mov	w1, 128
	blr	x3
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	mov	w1, 128
	mov	x0, x25
	blr	x3
.L772:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 120]
.L848:
	mul	w19, w0, w1
	ldr	x20, [x29, 112]
	mov	x0, x25
	ldr	x3, [x28, 88]
	mov	w1, w19
	mov	x2, x20
	blr	x3
	ldr	x3, [x28, 88]
	mov	x2, x20
	ldr	x0, [x29, 136]
	mov	w1, w19
	blr	x3
	ldr	w0, [x29, 160]
	ldr	x1, [x29, 152]
	bl	MEM_ReleaseMemBlock
	ldr	x3, [x28, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 144
	blr	x3
	ldr	w0, [x29, 192]
	ldr	x1, [x29, 184]
	bl	MEM_ReleaseMemBlock
	ldr	x3, [x28, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 176
	blr	x3
.L754:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L758:
	ldr	x1, .LC294
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L798:
	mov	w20, 0
	b	.L755
.L759:
	cmp	w20, 1
	ldr	w1, [x29, 128]
	cset	w0, ne
	str	w0, [x29, 120]
	cmp	w1, w0
	lsr	w0, w19, 1
	str	w0, [x29, 104]
	lsr	w0, w1, 1
	str	w0, [x29, 132]
	add	x0, x25, 2097152
	str	x0, [x29, 136]
	ldr	x28, .LC297
	ldr	x20, [x29, 152]
	bls	.L777
	ldr	w27, [x29, 120]
	.p2align 2
.L779:
	cbz	w19, .L780
	ldr	w0, [x29, 124]
	lsr	w24, w27, 4
	lsr	w23, w27, 1
	mov	w26, 0
	mul	w0, w24, w0
	mul	w23, w23, w19
	ubfiz	x24, x27, 8, 4
	add	x24, x0, x24
	.p2align 2
.L778:
	lsr	w1, w26, 8
	add	x0, x23, x26, uxtw
	ubfiz	x1, x1, 12, 20
	ldr	x5, [x28, 104]
	add	x1, x1, x24
	mov	x2, 256
	add	x1, x22, x1
	add	x0, x20, x0
	add	w26, w26, 256
	blr	x5
	cmp	w19, w26
	bhi	.L778
.L780:
	ldr	w0, [x29, 128]
	add	w27, w27, 2
	cmp	w0, w27
	bhi	.L779
.L777:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	lsr	w1, w1, 1
	blr	x3
	ldr	w0, [x29, 132]
	cbz	w0, .L855
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 128]
	.p2align 2
.L784:
	cbz	w19, .L786
	ldr	w0, [x29, 128]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L783:
	lsr	w1, w27, 8
	add	x0, x23, x27, uxtw
	ubfiz	x1, x1, 11, 21
	ldr	x5, [x28, 104]
	add	x1, x1, x22
	mov	x2, 256
	add	x1, x21, x1
	add	x0, x20, x0
	add	w27, w27, 256
	blr	x5
	cmp	w19, w27
	bhi	.L783
.L786:
	ldr	w0, [x29, 132]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L784
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L856
	ldr	w0, [x29, 108]
	cbnz	w0, .L789
	ldr	w1, [x29, 120]
	ldr	w0, [x29, 132]
	cmp	w0, w1
	bls	.L792
	.p2align 2
.L793:
	ldr	w0, [x29, 120]
	ldr	w1, [x29, 132]
	add	w0, w0, 2
	str	w0, [x29, 120]
	cmp	w1, w0
	bhi	.L793
.L792:
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	ldr	x0, [x29, 136]
	mov	w1, 128
	blr	x3
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	mov	w1, 128
	mov	x0, x25
	blr	x3
.L789:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 132]
	b	.L848
.L854:
	mov	w0, 0
	mov	w6, 0
	.p2align 2
.L771:
	ldr	w1, [x29, 104]
	mov	w5, w0
	cbz	w1, .L773
	ldr	w1, [x29, 104]
	add	w5, w1, w0
	mov	w1, 1
	.p2align 2
.L770:
	sub	w3, w1, #1
	uxtw	x2, w0
	ldr	x4, [x29, 136]
	add	w0, w0, 1
	cmp	w0, w5
	ldrb	w3, [x20, x3]
	strb	w3, [x4, x2]
	ldrb	w3, [x20, w1, uxtw]
	add	w1, w1, 2
	strb	w3, [x25, x2]
	bne	.L770
.L773:
	ldr	w0, [x29, 120]
	add	w6, w6, 1
	add	x20, x20, x19
	cmp	w0, w6
	mov	w0, w5
	bne	.L771
	b	.L772
.L856:
	ldr	w0, [x29, 120]
	mov	w7, 0
	mul	w1, w19, w0
	lsl	w0, w19, 1
	add	x20, x20, x1
	.p2align 2
.L788:
	ldr	w3, [x29, 104]
	cbz	w3, .L790
	lsr	w1, w7, 1
	mov	w2, 1
	mul	w1, w1, w3
	add	w6, w3, w1
	.p2align 2
.L787:
	sub	w5, w2, #1
	uxtw	x3, w1
	ldr	x4, [x29, 136]
	add	w1, w1, 1
	cmp	w6, w1
	ldrb	w5, [x20, x5]
	strb	w5, [x4, x3]
	ldrb	w5, [x20, w2, uxtw]
	add	w2, w2, 2
	strb	w5, [x25, x3]
	bne	.L787
.L790:
	ldr	w1, [x29, 132]
	add	w7, w7, 2
	add	x20, x20, x0
	cmp	w1, w7
	bhi	.L788
	b	.L789
.L855:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L789
	ldr	w0, [x29, 108]
	cbz	w0, .L792
	b	.L789
.L853:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	bne	.L795
	b	.L772
	.size	VDMHAL_V5R6C1_WriteBigTitle1DYuv, .-VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.align	3
.LC292:
	.xword	.LC291
	.align	3
.LC294:
	.xword	.LC293
	.align	3
.LC296:
	.xword	.LC295
	.align	3
.LC297:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CRG_ConfigReg
	.type	CRG_ConfigReg, %function
CRG_ConfigReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	ldr	x0, .LC298
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L864
	cbnz	w19, .L860
	ldr	x0, .LC299
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	ubfx	x2, x0, 8, 2
	cmp	w20, w2
	beq	.L857
	bfi	w0, w20, 8, 2
	str	w0, [x1, 120]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L860:
	cmp	w19, 1
	beq	.L865
.L857:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L864:
	mov	w3, w20
	mov	w2, w19
	mov	x0, x21
	mov	w1, 0
	bl	VDH_Record_RegData
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L865:
	ldr	x0, .LC299
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	bfi	w0, w20, 12, 5
	and	w0, w0, -131073
	str	w0, [x1, 120]
	ldr	w0, [x1, 120]
	orr	w0, w0, 131072
	str	w0, [x1, 120]
	b	.L857
	.size	CRG_ConfigReg, .-CRG_ConfigReg
	.align	3
.LC298:
	.xword	g_HalDisable
	.align	3
.LC299:
	.xword	g_pstRegCrg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MFDE_ConfigReg
	.type	MFDE_ConfigReg, %function
MFDE_ConfigReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	uxtw	x20, w0
	mov	x0, x30
	mov	w21, w1
	sxtw	x19, w2
	mov	x22, x3
	bl	_mcount
	ldr	x0, .LC300
	ldrb	w4, [x0]
	cmp	w4, 1
	bne	.L870
	cmp	w19, wzr
	ble	.L871
	ldr	x2, .LC302
	mov	w3, w19
	ldr	x1, .LC303
	mov	w0, 32
	add	x2, x2, 368
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L871:
	lsl	x0, x19, 6
	ldr	x1, .LC301
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	str	w21, [x0, x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L870:
	mov	w3, w21
	mov	w2, w20
	mov	x0, x22
	mov	w1, 2
	bl	VDH_Record_RegData
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.align	3
.LC300:
	.xword	g_HalDisable
	.align	3
.LC301:
	.xword	g_HwMem
	.align	3
.LC302:
	.xword	.LANCHOR1
	.align	3
.LC303:
	.xword	.LC109
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.56347, %object
	.size	__func__.56347, 23
__func__.56347:
	.string	"VDMHAL_V5R6C1_CfgRpReg"
	.zero	1
	.type	__func__.55847, %object
	.size	__func__.55847, 22
__func__.55847:
	.string	"VDMHAL_V5R6C1_OpenHAL"
	.zero	2
	.type	__func__.55920, %object
	.size	__func__.55920, 25
__func__.55920:
	.string	"VDMHAL_V5R6C1_CalcFsSize"
	.zero	7
	.type	__func__.55946, %object
	.size	__func__.55946, 24
__func__.55946:
	.string	"VDMHAL_V5R6C1_CalcFsNum"
	.type	__func__.55989, %object
	.size	__func__.55989, 32
__func__.55989:
	.string	"VDMHAL_V5R6C1_ArrangeMem_Normal"
	.type	__FUNCTION__.55990, %object
	.size	__FUNCTION__.55990, 32
__FUNCTION__.55990:
	.string	"VDMHAL_V5R6C1_ArrangeMem_Normal"
	.type	__func__.55932, %object
	.size	__func__.55932, 33
__func__.55932:
	.string	"VDMHAL_V5R6C1_FillMemArrangeInfo"
	.zero	7
	.type	__func__.56072, %object
	.size	__func__.56072, 34
__func__.56072:
	.string	"VDMHAL_V5R6C1_ArrangeMem_Specific"
	.zero	6
	.type	__func__.56095, %object
	.size	__func__.56095, 23
__func__.56095:
	.string	"VDMHAL_V5R6C1_ResetVdm"
	.zero	1
	.type	__func__.56105, %object
	.size	__func__.56105, 35
__func__.56105:
	.string	"VDMHAL_V5R6C1_SetSmmuPageTableAddr"
	.zero	5
	.type	__func__.56125, %object
	.size	__func__.56125, 24
__func__.56125:
	.string	"VDMHAL_V5R6C1_GlbResetX"
	.type	__func__.56115, %object
	.size	__func__.56115, 23
__func__.56115:
	.string	"VDMHAL_V5R6C1_GlbReset"
	.zero	1
	.type	__func__.56137, %object
	.size	__func__.56137, 28
__func__.56137:
	.string	"VDMHAL_V5R6C1_ClearIntState"
	.zero	4
	.type	__func__.56143, %object
	.size	__func__.56143, 31
__func__.56143:
	.string	"VDMHAL_V5R6C1_ClearMMUIntState"
	.zero	1
	.type	__func__.56149, %object
	.size	__func__.56149, 22
__func__.56149:
	.string	"VDMHAL_V5R6C1_MaskInt"
	.zero	2
	.type	__func__.56162, %object
	.size	__func__.56162, 24
__func__.56162:
	.string	"VDMHAL_V5R6C1_EnableInt"
	.type	__func__.56171, %object
	.size	__func__.56171, 23
__func__.56171:
	.string	"VDMHAL_V5R6C1_CheckReg"
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.56185, %object
	.size	__func__.56185, 26
__func__.56185:
	.string	"VDMHAL_V5R6C1_ReadMMUMask"
	.zero	6
	.type	__func__.56190, %object
	.size	__func__.56190, 27
__func__.56190:
	.string	"VDMHAL_V5R6C1_WriteMMUMask"
	.zero	5
	.type	__func__.56222, %object
	.size	__func__.56222, 25
__func__.56222:
	.string	"VDMHAL_V5R6C1_PrepareDec"
	.zero	7
	.type	__func__.56227, %object
	.size	__func__.56227, 25
__func__.56227:
	.string	"VDMHAL_V5R6C1_IsVdmReady"
	.zero	7
	.type	__func__.56232, %object
	.size	__func__.56232, 23
__func__.56232:
	.string	"VDMHAL_V5R6C1_IsVdmRun"
	.zero	1
	.type	__func__.56238, %object
	.size	__func__.56238, 27
__func__.56238:
	.string	"VDMHAL_V5R6C1_IsVdhDecOver"
	.zero	5
	.type	__func__.56248, %object
	.size	__func__.56248, 31
__func__.56248:
	.string	"VDMHAL_V5R6C1_IsVdhPartDecOver"
	.zero	1
	.type	__func__.56263, %object
	.size	__func__.56263, 33
__func__.56263:
	.string	"VDMHAL_V5R6C1_UpdateHardwareInfo"
	.zero	7
	.type	__func__.56336, %object
	.size	__func__.56336, 23
__func__.56336:
	.string	"VDMHAL_V5R6C1_CfgRpMsg"
	.zero	1
	.type	__func__.56313, %object
	.size	__func__.56313, 24
__func__.56313:
	.string	"VDMHAL_CfgNotFullRepair"
	.type	__func__.56360, %object
	.size	__func__.56360, 28
__func__.56360:
	.string	"VDMHAL_V5R6C1_MakeDecReport"
	.zero	4
	.type	__func__.56399, %object
	.size	__func__.56399, 28
__func__.56399:
	.string	"VDMHAL_V5R6C1_PrepareRepair"
	.zero	4
	.type	__func__.56587, %object
	.size	__func__.56587, 15
__func__.56587:
	.string	"MFDE_ConfigReg"
	.zero	1
	.type	__func__.56406, %object
	.size	__func__.56406, 28
__func__.56406:
	.string	"VDMHAL_V5R6C1_StartHwRepair"
	.zero	4
	.type	__func__.56445, %object
	.size	__func__.56445, 28
__func__.56445:
	.string	"VDMHAL_V5R6C1_CalVdhClkSkip"
	.zero	4
	.type	__func__.56469, %object
	.size	__func__.56469, 28
__func__.56469:
	.string	"VDMHAL_V5R6C1_StartHwDecode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC3:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC10:
	ASCII(.string	"pOpenParam = NULL error!" )
	.zero	7
.LC13:
	ASCII(.string	"%s: %s\n" )
.LC15:
	ASCII(.string	"MemBaseAddr = 0 error!" )
	.zero	1
.LC17:
	ASCII(.string	"VDMHAL_V5R6C1_OpenHAL: Size error!" )
	.zero	5
.LC19:
	ASCII(.string	"VdhId is wrong!!!\n" )
	.zero	5
.LC23:
	ASCII(.string	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\n" )
	.zero	7
.LC25:
	ASCII(.string	"BPDRegVirAddr %p\n" )
	.zero	6
.LC27:
	ASCII(.string	"!!!!!! HAL memory not enouph! need %d, have %d\n" )
.LC29:
	ASCII(.string	"image size out of range" )
.LC36:
	ASCII(.string	"VDMHAL ArrangeMem HEVC/VP9/AVS2 10 bit\n" )
.LC39:
	ASCII(.string	"%s pstVfmwFrameSizeInfo = NULL\n" )
.LC43:
	ASCII(.string	"DelAllFrameMemRecord err in VDMHAL_V5R6C1_ArrangeMem!\n" )
	.zero	1
.LC45:
	ASCII(.string	"Report arrange frame buffer: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	3
.LC50:
	ASCII(.string	"Report arrange frame buffer only: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	6
.LC53:
	ASCII(.string	"VidStd Invalid" )
	.zero	1
.LC57:
	ASCII(.string	"decoder not support, ISMV450 = %d\n" )
	.zero	5
.LC61:
	ASCII(.string	"Set CompressEn %d, LossCompressEn %d, YCompRatio %d, UVCompRatio %d\n" )
	.zero	3
.LC63:
	ASCII(.string	"VDMHAL_V5R6C1_CalcFsSize err!\n" )
	.zero	1
.LC65:
	ASCII(.string	"%s, need arrange, Size: %#x, Num: %#x, RefChanged: %#x\n" )
.LC67:
	ASCII(.string	"DFS, report event. Size: 0x%x, Num: %d, RefChanged: %d\n" )
.LC70:
	ASCII(.string	"pVdmMemArrange is NULL" )
	.zero	1
.LC72:
	ASCII(.string	"DFS, no ref frame!\n" )
	.zero	4
.LC74:
	ASCII(.string	"DFS, Frame number = %d > 30, Then, Frame num = 30, \n" )
	.zero	3
.LC76:
	ASCII(.string	"VDMHAL_V5R6C1_ArrangeMem Mem addr is NULL" )
	.zero	6
.LC81:
	ASCII(.string	"'pVdmMemArrange' is NULL" )
	.zero	7
.LC85:
	ASCII(.string	"MemSize not enough for pmv slot" )
.LC88:
	ASCII(.string	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight failed!\n" )
	.zero	3
.LC90:
	ASCII(.string	"ImgSlotLen > ChanSlotLen" )
	.zero	7
.LC92:
	ASCII(.string	"cann't allocate img slot" )
	.zero	7
.LC98:
	ASCII(.string	"VDMHAL_V5R6C1_ResetVdm: map vdm register fail, vir(reg) = (%p)\n" )
.LC102:
	ASCII(.string	"%s module id %d failed!\n" )
	.zero	7
.LC104:
	ASCII(.string	"%s module id %d success!\n" )
	.zero	6
.LC109:
	ASCII(.string	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC114:
	ASCII(.string	"%s: map vdm register 0x%x failed!\n" )
	.zero	5
.LC117:
	ASCII(.string	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC120:
	ASCII(.string	"%s VdhId %d failed!\n" )
	.zero	3
.LC122:
	ASCII(.string	"%s VdhId %d success!\n" )
	.zero	2
.LC149:
	ASCII(.string	"%s: VdhId(%d) Invalid!\n" )
.LC152:
	ASCII(.string	"%s: vdm register virtual address not mapped, reset failed!\n" )
	.zero	4
.LC154:
	ASCII(.string	"%s: unkown reg_id = %d\n" )
.LC164:
	ASCII(.string	"%s: pDecParam(%p) = NULL\n" )
	.zero	6
.LC169:
	ASCII(.string	"VDM register not mapped yet!" )
	.zero	3
.LC175:
	ASCII(.string	"VDM register not mapped yet!\n" )
	.zero	2
.LC197:
	ASCII(.string	"can NOT map vir addr for up-msg" )
.LC201:
	ASCII(.string	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\n" )
	.zero	1
.LC203:
	ASCII(.string	"ReadUpMsgSlot error! upmsg_size(%d) > 512\n" )
	.zero	5
.LC206:
	ASCII(.string	"WriteMsgSlot error!\n" )
	.zero	3
.LC209:
	ASCII(.string	"can not map repair msg virtual address!" )
.LC213:
	ASCII(.string	"ValidGroupNum=%d out of range!\n" )
.LC215:
	ASCII(.string	"align_mb error\n" )
.LC217:
	ASCII(.string	"[%s][%d]sclie_num is wrong! %d \n" )
	.zero	7
.LC221:
	ASCII(.string	"'pMakeDecReport' is NULL" )
	.zero	7
.LC225:
	ASCII(.string	"'pDecReport' is NULL" )
	.zero	3
.LC235:
	ASCII(.string	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full repair.\n" )
	.zero	3
.LC239:
	ASCII(.string	"\n***** UpMsg DecSliceNum=%d\n" )
	.zero	3
.LC241:
	ASCII(.string	"\n***** Up Msg (phy addr: %#8x) *****\n" )
	.zero	2
.LC243:
	ASCII(.string	"\n0x%02x 0x%08x 0x%08x 0x%08x 0x%08x\n" )
	.zero	3
.LC245:
	ASCII(.string	"\n***** Up Msg print finished *****\n" )
	.zero	4
.LC250:
	ASCII(.string	"vdm register virtual address not mapped, VDMHAL_V200R003_PrepareRepair failed!\n" )
.LC253:
	ASCII(.string	"FIRST_REPAIR Parameter Error!\n" )
	.zero	1
.LC255:
	ASCII(.string	"SECOND_REPAIR Parameter Error!\n" )
.LC261:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC270:
	ASCII(.string	"%s The channel %d is not active\n" )
	.zero	7
.LC291:
	ASCII(.string	"BigTile1d_y" )
	.zero	4
.LC293:
	ASCII(.string	"failed mem_allocMemBlock BigTile_yuv save!\n" )
	.zero	4
.LC295:
	ASCII(.string	"BigTile1d_uv" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
