#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VDMHAL_UpateDecParam.constprop.10, %function
VDMHAL_UpateDecParam.constprop.10:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 17
	bhi	.L1
	ldr	x0, .LC0
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx4
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx4:
	.section	.rodata
	.align	0
	.align	2
.L4:
	.byte	(.L14 - .Lrtx4) / 4
	.byte	(.L5 - .Lrtx4) / 4
	.byte	(.L6 - .Lrtx4) / 4
	.byte	(.L7 - .Lrtx4) / 4
	.byte	(.L1 - .Lrtx4) / 4
	.byte	(.L8 - .Lrtx4) / 4
	.byte	(.L9 - .Lrtx4) / 4
	.byte	(.L1 - .Lrtx4) / 4
	.byte	(.L10 - .Lrtx4) / 4
	.byte	(.L11 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L13 - .Lrtx4) / 4
	.byte	(.L1 - .Lrtx4) / 4
	.byte	(.L14 - .Lrtx4) / 4
	.byte	(.L15 - .Lrtx4) / 4
	.byte	(.L16 - .Lrtx4) / 4
	.text
	.p2align 3
.L14:
	mov	w0, 1
	strb	wzr, [x19, 4]
	strb	w0, [x19, 17]
.L1:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L15:
	mov	w0, 1
	strb	wzr, [x19]
	strb	w0, [x19, 5]
	b	.L1
	.p2align 3
.L16:
	add	x19, x19, 270336
	mov	w0, 1
	str	wzr, [x19, 2468]
	strb	w0, [x19, 2081]
	b	.L1
	.p2align 3
.L5:
	mov	w0, 1
	str	wzr, [x19, 14600]
	strb	w0, [x19, 75]
	b	.L1
	.p2align 3
.L6:
	mov	w0, 1
	str	wzr, [x19, 14672]
	strb	w0, [x19, 167]
	b	.L1
	.p2align 3
.L7:
	add	x1, x19, 45056
	mov	w0, 1
	str	wzr, [x1, 240]
	strb	w0, [x19, 144]
	b	.L1
	.p2align 3
.L8:
	mov	w0, 1
	str	wzr, [x19, 160]
	strb	w0, [x19]
	b	.L1
	.p2align 3
.L9:
	mov	w0, 1
	str	wzr, [x19, 14904]
	strb	w0, [x19, 48]
	b	.L1
	.p2align 3
.L10:
	mov	w0, 1
	str	wzr, [x19, 76]
	strb	w0, [x19]
	b	.L1
	.p2align 3
.L11:
	mov	w0, 1
	str	wzr, [x19, 72]
	strb	w0, [x19, 1]
	b	.L1
	.p2align 3
.L12:
	mov	w0, 1
	str	wzr, [x19, 264]
	strb	w0, [x19, 104]
	b	.L1
	.p2align 3
.L13:
	mov	w0, 1
	str	wzr, [x19, 3144]
	strb	w0, [x19, 2778]
	b	.L1
	.size	VDMHAL_UpateDecParam.constprop.10, .-VDMHAL_UpateDecParam.constprop.10
	.align	3
.LC0:
	.xword	.L4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetHalMemSize
	.type	VDMHAL_V5R2C1_GetHalMemSize, %function
VDMHAL_V5R2C1_GetHalMemSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 6291456
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_GetHalMemSize, .-VDMHAL_V5R2C1_GetHalMemSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_OpenHAL
	.type	VDMHAL_V5R2C1_OpenHAL, %function
VDMHAL_V5R2C1_OpenHAL:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L31
	ldp	w23, w22, [x19]
	ldr	w19, [x19, 8]
	cbz	w23, .L32
	mov	w0, 6291455
	cmp	w22, w0
	ble	.L33
	cmp	w19, wzr
	bgt	.L34
	sxtw	x20, w19
	ldr	x25, .LC15
	ldr	x21, .LC16
	mov	x2, 268
	add	x0, x20, x20, lsl 4
	mov	w1, 0
	lsl	x0, x0, 2
	ldr	x3, [x25, 96]
	sub	x0, x0, x20
	add	x0, x21, x0, lsl 2
	blr	x3
	ldr	x24, .LC1
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
	ldr	x1, .LC18
	str	x0, [x24, x25]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 53248
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_Phy2Vir
	mov	x2, x0
	ldr	x1, .LC20
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
.L25:
	str	w1, [x0], 4
	add	w1, w1, 1280
	cmp	x0, x2
	bne	.L25
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
	bcc	.L26
	mov	x0, x21
	bl	H264HAL_V5R2C1_InitHal
	cmp	w0, wzr
	mov	x0, x21
	csetm	w19, ne
	bl	HEVCHAL_V5R2C1_InitHal
	cmp	w0, wzr
	csinv	w19, w19, wzr, eq
.L21:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L34:
	ldr	x1, .LC14
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
.L26:
	ldr	x1, .LC22
	mov	w3, w22
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L21
.L32:
	ldr	x3, .LC10
.L30:
	ldr	x2, .LC6
	mov	w0, 0
	ldr	x1, .LC8
	mov	w19, -1
	bl	dprint_vfmw
	b	.L21
.L33:
	ldr	x3, .LC12
	b	.L30
.L31:
	ldr	x3, .LC5
	b	.L30
	.size	VDMHAL_V5R2C1_OpenHAL, .-VDMHAL_V5R2C1_OpenHAL
	.align	3
.LC1:
	.xword	g_HwMem
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC6:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC15:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC16:
	.xword	g_VdmExtParam
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CloseHAL
	.type	VDMHAL_V5R2C1_CloseHAL, %function
VDMHAL_V5R2C1_CloseHAL:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_CloseHAL, .-VDMHAL_V5R2C1_CloseHAL
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CalcFsSize
	.type	VDMHAL_V5R2C1_CalcFsSize, %function
VDMHAL_V5R2C1_CalcFsSize:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w25, w0
	mov	x0, x30
	mov	w26, w1
	mov	w20, w2
	mov	w23, w3
	mov	w24, w4
	mov	x22, x5
	bl	_mcount
	sub	w1, w26, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L37
	sub	w1, w20, #32
	mov	w6, w20
	cmp	w1, w0
	bhi	.L37
	ldr	x1, .LC27
	add	w0, w26, 15
	asr	w0, w0, 4
	add	w3, w20, 15
	asr	w3, w3, 4
	cmp	w0, 45
	ldrb	w2, [x1]
	mov	w1, 36
	ccmp	w3, w1, 0, le
	mov	w19, 32
	cset	w4, le
	mov	w1, 64
	cmp	w4, wzr
	lsl	w21, w0, 4
	csel	w19, w19, w1, eq
	cmp	w2, 1
	csel	w19, w19, w1, ne
	cmp	w24, 16
	beq	.L42
	cmp	w24, 17
	beq	.L69
	mul	w19, w0, w19
	ldr	x27, .LC29
	add	w21, w21, 255
	add	w6, w20, 31
	and	w21, w21, -256
	mul	w19, w19, w3
	ldr	x5, [x27, w25, sxtw 3]
	and	w6, w6, -32
	add	w19, w19, 143
	mov	w28, 0
	and	w19, w19, -128
	mov	w7, 0
.L45:
	ldr	w0, [x5, 1280]
	cmp	w0, 1
	beq	.L70
.L67:
	asr	w4, w19, 1
	mov	w9, 0
	mov	w8, 0
	mov	w26, 0
.L48:
	cmp	w23, 1
	mul	w23, w6, w21
	beq	.L71
	mul	w2, w28, w7
	lsl	w1, w26, 2
	lsl	w0, w2, 2
	sub	w1, w1, w26
	sub	w2, w0, w2
	lsl	w0, w23, 2
	sub	w0, w0, w23
	lsr	w0, w0, 1
	add	w0, w0, w2, lsr 1
	add	w20, w0, w1, lsr 1
.L51:
	add	x2, x5, 503808
	ldr	w0, [x2, 1624]
	cbz	w0, .L72
	add	x0, x5, 507904
	cmp	w24, 17
	lsl	w21, w21, 4
	str	w20, [x0, 1096]
	str	w8, [x2, 3972]
	str	w9, [x2, 3976]
	str	w4, [x2, 4012]
	beq	.L53
.L73:
	ldr	w0, [x2, 1632]
	mov	w1, 32
	sub	w24, w24, #16
	str	w21, [x2, 3964]
	cmp	w0, 32
	lsr	w21, w21, 1
	csel	w0, w0, w1, le
	str	w21, [x2, 3968]
	str	w0, [x2, 4016]
	cmp	w24, 1
	add	w0, w26, w23
	str	w0, [x2, 3996]
	bls	.L54
.L55:
	ldr	x0, [x27, w25, sxtw 3]
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
	cbz	x22, .L63
	str	w1, [x22, 4]
	mov	w0, 0
	ldr	x3, [x27, w25, sxtw 3]
	add	x3, x3, 503808
	ldr	w3, [x3, 1632]
	stp	w3, w19, [x22, 8]
	ldr	x3, [x27, w25, sxtw 3]
	add	x3, x3, 503808
	ldr	w3, [x3, 4016]
	stp	w3, w4, [x22, 16]
	str	w2, [x22]
	ldr	x2, [x27, w25, sxtw 3]
	add	x2, x2, 507904
	str	w1, [x2, 1104]
.L65:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L72:
	ldr	x1, .LC28
	add	x0, x2, 3960
	mov	x2, 1248
	lsl	w21, w21, 4
	stp	w7, w9, [x29, 96]
	ldr	x3, [x1, 96]
	mov	w1, 0
	stp	w4, w8, [x29, 104]
	blr	x3
	ldr	x5, [x27, w25, sxtw 3]
	cmp	w24, 17
	ldp	w4, w8, [x29, 104]
	add	x0, x5, 507904
	add	x2, x5, 503808
	ldp	w7, w9, [x29, 96]
	str	w20, [x0, 1096]
	str	w8, [x2, 3972]
	str	w9, [x2, 3976]
	str	w4, [x2, 4012]
	bne	.L73
.L53:
	mov	w0, 1
	str	w21, [x2, 3964]
	str	w0, [x2, 4016]
	lsr	w21, w21, 1
	add	w0, w26, w23
	str	w21, [x2, 3968]
	str	w0, [x2, 3996]
.L54:
	ldr	w0, [x5, 1612]
	cmp	w0, 8
	ble	.L55
	lsl	w6, w23, 2
	ldr	x1, .LC31
	sub	w6, w6, w23
	lsl	w23, w26, 2
	sub	w26, w23, w26
	mov	w0, 31
	mul	w28, w28, w7
	lsr	w23, w26, 1
	lsl	w7, w7, 4
	add	w6, w23, w6, lsr 1
	str	w7, [x2, 3980]
	str	w6, [x2, 3988]
	str	w28, [x2, 3992]
	bl	dprint_vfmw
	b	.L55
	.p2align 3
.L71:
	lsl	w1, w3, 6
	sub	w1, w1, w3, lsl 4
	mul	w20, w1, w21
	b	.L51
	.p2align 3
.L42:
	ldr	x27, .LC29
	mul	w19, w3, w21
	add	w21, w26, 255
	ldr	x5, [x27, w25, sxtw 3]
	add	w19, w19, 143
	and	w21, w21, -256
	and	w19, w19, -128
	ldr	w0, [x5, 1612]
	cmp	w0, 8
	ble	.L74
	ldr	w0, [x5, 1280]
	add	w28, w20, 31
	and	w28, w28, -32
	lsr	w7, w21, 2
	cmp	w0, 1
	bne	.L67
	.p2align 2
.L70:
	cmp	w20, 2159
	mov	w0, 3839
	ccmp	w24, 17, 4, le
	ccmp	w26, w0, 0, ne
	ble	.L67
	add	w2, w20, 63
	asr	w4, w19, 1
.L60:
	adds	w8, w26, 2047
	add	w26, w26, 4094
	csel	w26, w26, w8, mi
	and	w26, w26, -2048
	cmp	w26, wzr
	add	w8, w26, 127
	csel	w8, w8, w26, lt
	add	w26, w2, 63
	cmp	w2, wzr
	asr	w8, w8, 7
	csel	w2, w26, w2, lt
	lsl	w26, w8, 5
	asr	w2, w2, 6
	mul	w26, w2, w26
	mov	w9, w26
	b	.L48
	.p2align 3
.L69:
	ldr	x27, .LC29
	add	w21, w26, 255
	add	w2, w20, 63
	and	w21, w21, -256
	and	w6, w2, -64
	ldr	x5, [x27, w25, sxtw 3]
	ldr	w0, [x5, 1612]
	cmp	w0, 8
	bgt	.L58
	mov	w28, 0
	mov	w7, 0
.L46:
	ldr	w0, [x5, 1280]
	mov	w4, 64
	movk	w4, 0x12, lsl 16
	cmp	w0, 1
	beq	.L64
	mov	w19, 128
	mov	w9, 0
	mov	w8, 0
	movk	w19, 0x24, lsl 16
	mov	w26, 0
	b	.L48
	.p2align 3
.L74:
	mov	w28, 0
	mov	w7, 0
	b	.L45
	.p2align 3
.L63:
	mov	w0, 0
	b	.L65
	.p2align 3
.L58:
	add	w28, w6, 63
	lsr	w7, w21, 2
	and	w28, w28, -64
	b	.L46
	.p2align 3
.L37:
	ldr	x2, .LC25
	mov	w0, 0
	ldr	x3, .LC24
	ldr	x1, .LC26
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L65
	.p2align 3
.L64:
	mov	w19, 128
	movk	w19, 0x24, lsl 16
	b	.L60
	.size	VDMHAL_V5R2C1_CalcFsSize, .-VDMHAL_V5R2C1_CalcFsSize
	.align	3
.LC24:
	.xword	.LC23
	.align	3
.LC25:
	.xword	.LANCHOR0
	.align	3
.LC26:
	.xword	.LC7
	.align	3
.LC27:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC28:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC29:
	.xword	s_pstVfmwChan
	.align	3
.LC31:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetRpuSize
	.type	VDMHAL_V5R2C1_GetRpuSize, %function
VDMHAL_V5R2C1_GetRpuSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1024
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_GetRpuSize, .-VDMHAL_V5R2C1_GetRpuSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CalcFsNum
	.type	VDMHAL_V5R2C1_CalcFsNum, %function
VDMHAL_V5R2C1_CalcFsNum:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x19, x3
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L81
	cmp	w21, 17
	ldr	x2, .LC35
	beq	.L82
	ldr	x3, [x2, w20, sxtw 3]
	mov	w4, 32
	add	x1, x3, 503808
	ldr	w0, [x1, 1632]
	cmp	w0, w4
	csel	w0, w0, w4, le
	str	w0, [x1, 4016]
	ldr	w0, [x3, 664]
	cmp	w0, 2
	beq	.L83
.L80:
	ldr	x1, [x2, w20, sxtw 3]
	mov	w0, 0
	add	x1, x1, 503808
	ldr	w1, [x1, 1632]
	str	w1, [x19, 8]
	ldr	x1, [x2, w20, sxtw 3]
	add	x1, x1, 503808
	ldr	w1, [x1, 4016]
	str	w1, [x19, 16]
.L78:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L82:
	ldr	x0, [x2, w20, sxtw 3]
	mov	w1, 1
	add	x0, x0, 503808
	str	w1, [x0, 4016]
	b	.L80
	.p2align 3
.L83:
	ldr	w0, [x1, 1636]
	str	w0, [x1, 4016]
	b	.L80
.L81:
	ldr	x2, .LC32
	mov	w0, 1
	ldr	x1, .LC34
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -1
	b	.L78
	.size	VDMHAL_V5R2C1_CalcFsNum, .-VDMHAL_V5R2C1_CalcFsNum
	.align	3
.LC32:
	.xword	.LANCHOR0
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC35:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_DynamicAllocFrame
	.type	VDMHAL_V5R2C1_DynamicAllocFrame, %function
VDMHAL_V5R2C1_DynamicAllocFrame:
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
	ldr	x21, .LC36
	mov	w0, w19
	ldr	x1, [x21, w19, sxtw 3]
	add	x1, x1, 503808
	add	x1, x1, 1656
	bl	DelAllFrameMemRecord
	cbnz	w0, .L104
.L85:
	ldr	x1, [x21, w19, sxtw 3]
	mov	w2, 255
	add	x1, x1, 503808
	add	x0, x1, 1656
	add	x1, x1, 3960
	.p2align 2
.L86:
	str	w2, [x0], 72
	cmp	x1, x0
	bne	.L86
	mov	w0, 1088
	cmp	w23, 1920
	ccmp	w22, w0, 0, le
	ble	.L87
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x20, 8]
.L88:
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
	beq	.L91
	add	x1, x1, 503808
	ldr	w0, [x1, 1636]
	str	w0, [x20, 16]
	ldr	x1, [x21, w19, sxtw 3]
.L91:
	add	x0, x1, 507904
	add	x1, x1, 475136
	mov	w4, 1
	mov	w3, w22
	mov	w2, w23
	str	wzr, [x0, 1136]
	str	w4, [x1, 2280]
	str	w4, [x0, 1676]
	mov	w0, 31
	ldr	x1, .LC40
	ldr	w4, [x20, 8]
	ldr	w5, [x20, 16]
	bl	dprint_vfmw
	ldr	x0, .LC41
	ldr	x4, [x0]
	cbz	x4, .L92
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
.L92:
	ldr	x3, .LC42
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
	.p2align 3
.L87:
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x0, 36]
	cmp	w1, 24
	beq	.L103
	add	x1, x0, 507904
	ldr	w1, [x1, 1732]
	cbnz	w1, .L103
	ldr	w1, [x20, 8]
	add	w1, w1, 4
	str	w1, [x20, 8]
	ldr	x0, [x21, w19, sxtw 3]
	b	.L88
.L103:
	ldr	w1, [x20, 8]
	b	.L88
.L104:
	ldr	x1, .LC38
	mov	w0, 0
	bl	dprint_vfmw
	b	.L85
	.size	VDMHAL_V5R2C1_DynamicAllocFrame, .-VDMHAL_V5R2C1_DynamicAllocFrame
	.align	3
.LC36:
	.xword	s_pstVfmwChan
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC41:
	.xword	g_event_report
	.align	3
.LC42:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_DynamicAllocFrame_Only
	.type	VDMHAL_V5R2C1_DynamicAllocFrame_Only, %function
VDMHAL_V5R2C1_DynamicAllocFrame_Only:
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
	ldr	x4, .LC43
	mov	w3, w21
	ldr	w5, [x19, 8]
	mov	w2, w22
	ldr	x1, .LC45
	mov	w0, 31
	ldr	x4, [x4, w20, sxtw 3]
	add	x4, x4, 503808
	str	w5, [x4, 1636]
	ldr	w4, [x19, 8]
	ldr	w5, [x19, 16]
	bl	dprint_vfmw
	ldr	x0, .LC46
	ldr	x4, [x0]
	cbz	x4, .L105
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
.L105:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDMHAL_V5R2C1_DynamicAllocFrame_Only, .-VDMHAL_V5R2C1_DynamicAllocFrame_Only
	.align	3
.LC43:
	.xword	s_pstVfmwChan
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC46:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ArrangeMem_Normal
	.type	VDMHAL_V5R2C1_ArrangeMem_Normal, %function
VDMHAL_V5R2C1_ArrangeMem_Normal:
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
	bhi	.L146
	ldr	x21, .LC51
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 503808
	ldr	w26, [x1, 1628]
	ldr	w1, [x0, 100]
	cmp	w1, 2
	beq	.L147
	and	w1, w20, -17
	cmp	w1, wzr
	ccmp	w20, 18, 4, ne
	beq	.L148
.L115:
	cmp	w20, 17
	cset	w2, eq
	mov	w1, w2
.L116:
	ldr	x4, .LC52
	sbfiz	x3, x19, 4, 32
	ldr	w5, [x0, 1292]
	str	w2, [x0, 1280]
	str	w1, [x4, x3]
	ldr	w3, [x0, 1284]
	ldr	w4, [x0, 1288]
	mov	w0, 1
	ldr	x1, .LC54
	bl	dprint_vfmw
.L114:
	mov	w2, w25
	add	x3, x29, 104
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R2C1_CalcFsNum
	mov	w25, w0
	add	x5, x29, 104
	mov	w4, w20
	mov	w3, w27
	mov	w2, w24
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R2C1_CalcFsSize
	orr	w0, w25, w0
	cbnz	w0, .L149
	ldr	x27, [x21, w19, sxtw 3]
	ldr	w20, [x29, 104]
	add	x0, x27, 503808
	cmp	w26, w20
	ldr	w25, [x0, 1632]
	ldr	w5, [x0, 1648]
	beq	.L150
.L119:
	ldr	x2, .LC49
	mov	w3, w20
	ldr	x1, .LC58
	mov	w4, w25
	add	x2, x2, 112
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x21, w19, sxtw 3]
	add	x3, x29, 104
	mov	w2, w24
	add	x0, x0, 503808
	ldr	w1, [x0, 1624]
	str	w20, [x0, 1628]
	cbz	w1, .L151
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R2C1_DynamicAllocFrame_Only
.L122:
	ldr	x4, [x21, w19, sxtw 3]
	mov	w3, w25
	ldr	x1, .LC60
	mov	w2, w20
	add	x4, x4, 503808
	mov	w0, 31
	ldr	w4, [x4, 1648]
	bl	dprint_vfmw
	ldr	x19, [x21, w19, sxtw 3]
	ldr	x0, .LC61
	add	x19, x19, 507904
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 1112]
	mov	w1, 2
.L112:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, w1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L151:
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R2C1_DynamicAllocFrame
	b	.L122
	.p2align 3
.L148:
	cmp	w23, 3839
	mov	w1, 2159
	ccmp	w24, w1, 0, le
	ble	.L115
	mov	w1, 1
	mov	w2, w1
	b	.L116
	.p2align 3
.L150:
	cmp	w5, 1
	beq	.L119
	ldr	w1, [x0, 1624]
	cmp	w1, 1
	beq	.L119
	cbz	x22, .L152
	add	x26, x27, 507904
	add	x20, x0, 3960
	mov	x0, x27
	ldr	w23, [x26, 1096]
	cbz	w25, .L153
.L124:
	add	x0, x0, 503808
	ldr	w2, [x0, 1636]
	cmp	w2, 30
	bgt	.L154
.L125:
	ldr	x24, .LC61
	mov	w0, 8
	str	w2, [x26, -88]
	ldr	x1, [x24, 24]
	blr	x1
	ldr	x7, [x21, w19, sxtw 3]
	add	x9, x7, 507904
	ldr	w0, [x9, 1136]
	cbz	w0, .L130
	ldp	w10, w6, [x26, -80]
	sub	x4, x26, #136
	mov	w5, 0
	mov	w8, 1
	.p2align 2
.L129:
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
	beq	.L127
	ldr	w1, [x4, 68]
	ldr	w3, [x11, 1704]
	add	w2, w1, 1
	uxtw	x1, w1
	lsl	x0, x1, 2
	sub	x0, x0, x1
	add	x0, x4, x0, lsl 2
	str	w3, [x0, 848]
	str	w2, [x4, 68]
.L127:
	ldr	w0, [x4, 64]
	cmp	w0, w10
	bcs	.L128
	ldr	w2, [x11, 1664]
	add	x1, x27, x0, uxtw 3
	add	x1, x1, 507904
	add	w0, w0, 1
	cmp	w2, 255
	beq	.L128
	ldr	w2, [x11, 1720]
	str	w2, [x1, 72]
	strb	w8, [x1, 76]
	str	w0, [x4, 64]
.L128:
	ldr	w0, [x9, 1136]
	cmp	w5, w0
	bcc	.L129
.L130:
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
	b	.L112
	.p2align 3
.L147:
	add	x2, x0, 1280
	mov	w1, -1
	stp	wzr, wzr, [x2]
	stp	w1, w1, [x2, 8]
	b	.L114
	.p2align 3
.L154:
	ldr	x1, .LC67
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 30
	mov	w2, w1
	add	x0, x0, 503808
	str	w1, [x0, 1636]
	b	.L125
	.p2align 3
.L153:
	ldr	x1, .LC65
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x21, w19, sxtw 3]
	b	.L124
	.p2align 3
.L146:
	ldr	x2, .LC49
	mov	w0, 0
	ldr	x1, .LC50
	ldr	x3, .LC48
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w1, -1
	b	.L112
	.p2align 3
.L149:
	ldr	x1, .LC56
	mov	w0, 31
	bl	dprint_vfmw
	mov	w1, -1
	b	.L112
.L152:
	ldr	x2, .LC49
	mov	w0, 0
	ldr	x1, .LC50
	ldr	x3, .LC63
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w1, -1
	b	.L112
	.size	VDMHAL_V5R2C1_ArrangeMem_Normal, .-VDMHAL_V5R2C1_ArrangeMem_Normal
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC49:
	.xword	.LANCHOR0
	.align	3
.LC50:
	.xword	.LC7
	.align	3
.LC51:
	.xword	s_pstVfmwChan
	.align	3
.LC52:
	.xword	g_VfmwCompressPara
	.align	3
.LC54:
	.xword	.LC53
	.align	3
.LC56:
	.xword	.LC55
	.align	3
.LC58:
	.xword	.LC57
	.align	3
.LC60:
	.xword	.LC59
	.align	3
.LC61:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC67:
	.xword	.LC66
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ArrangeMem_Specific
	.type	VDMHAL_V5R2C1_ArrangeMem_Specific, %function
VDMHAL_V5R2C1_ArrangeMem_Specific:
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
	cbz	w22, .L246
	sub	w1, w21, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L158
	sub	w1, w24, #32
	cmp	w1, w0
	bhi	.L158
	cbz	x19, .L247
	ldr	x0, .LC75
	cmp	w20, 20
	mov	x2, 1232
	mov	w1, 0
	mov	w6, 20
	ldr	x3, [x0, 96]
	mov	x0, x19
	csel	w26, w20, w6, le
	mov	w20, 32
	blr	x3
	ldr	x1, .LC76
	add	w0, w21, 15
	asr	w0, w0, 4
	add	w3, w24, 15
	cmp	w0, 45
	asr	w3, w3, 4
	ldrb	w2, [x1]
	mov	w1, 36
	ccmp	w3, w1, 0, le
	mov	w1, 64
	cset	w4, le
	cmp	w4, wzr
	csel	w20, w20, w1, eq
	cmp	w2, 1
	csel	w20, w20, w1, ne
	cmp	w25, 16
	lsl	w2, w0, 4
	beq	.L248
	cmp	w25, 17
	beq	.L166
	mul	w20, w0, w20
	mul	w20, w20, w3
	add	w20, w20, 143
	and	w20, w20, -128
	mul	w1, w26, w20
	cmp	w28, w1
	ble	.L164
	add	w2, w2, 255
	sub	w1, w28, w1
	and	w28, w2, -256
	add	w7, w22, 1023
	lsl	w0, w28, 4
	str	w0, [x19, 4]
	asr	w0, w0, 1
	and	w7, w7, -1024
	str	w0, [x19, 8]
	asr	w0, w20, 1
	str	w26, [x19, 56]
	sub	w6, w7, w22
	str	w0, [x19, 52]
	add	w2, w24, 31
	sub	w1, w1, w6
	and	w2, w2, -32
	tbnz	w23, #31, .L242
	ldr	x4, .LC79
	mov	w8, 0
	mov	w26, 0
	ldr	x0, [x4, w23, sxtw 3]
	ldr	w0, [x0, 1280]
	cmp	w0, 1
	beq	.L249
.L210:
	mov	w5, 0
	mov	w0, 0
	mov	w24, 0
.L169:
	stp	w0, w5, [x19, 12]
	ldr	w0, [x29, 144]
	cmp	w0, 1
	beq	.L250
	mul	w3, w2, w28
	mul	w5, w26, w8
	lsl	w0, w3, 2
	lsl	w21, w24, 2
	sub	w3, w0, w3
	lsl	w0, w5, 2
	sub	w0, w0, w5
	sub	w21, w21, w24
	asr	w0, w0, 1
	add	w0, w0, w3, asr 1
	add	w21, w0, w21, lsr 1
.L171:
	ldr	w0, [x29, 152]
	tbnz	w0, #31, .L172
	stp	w2, w8, [x29, 104]
	stp	w1, w6, [x29, 112]
	str	w7, [x29, 120]
	bl	VCTRL_GetChanWidth
	mov	w23, w0
	ldr	w0, [x29, 152]
	bl	VCTRL_GetChanHeight
	cmn	w23, #1
	ldr	w7, [x29, 120]
	ccmn	w0, #1, 4, ne
	ldp	w2, w8, [x29, 104]
	ldp	w1, w6, [x29, 112]
	beq	.L251
	ldr	w3, [x29, 144]
	add	w23, w23, 15
	and	w23, w23, -16
	add	w0, w0, 15
	cmp	w3, 1
	add	w3, w23, 255
	and	w0, w0, -16
	and	w11, w3, -256
	beq	.L252
	ldr	x3, .LC79
	ldr	w4, [x29, 152]
	ldr	x3, [x3, w4, sxtw 3]
	ldr	w3, [x3, 1280]
	cmp	w3, 1
	beq	.L176
	add	w3, w0, 126
	adds	w0, w0, 63
	csel	w3, w3, w0, mi
	mov	w10, 0
	asr	w3, w3, 6
.L177:
	mul	w3, w11, w3
	mul	w11, w26, w8
	lsl	w5, w3, 2
	sub	w3, w5, w3
	lsl	w0, w11, 2
	lsl	w3, w3, 6
	sub	w0, w0, w11
	asr	w0, w0, 1
	add	w0, w0, w3, asr 1
	add	w0, w0, w10
.L175:
	cmp	w21, w0
	ldr	w23, [x29, 152]
	bgt	.L253
.L172:
	mul	w28, w2, w28
	sub	w0, w25, #16
	cmp	w0, 1
	add	w0, w28, w24
	str	w0, [x19, 36]
	bls	.L254
	cbz	w27, .L181
	cmp	w25, wzr
	ccmp	w25, 3, 4, ne
	beq	.L179
	sdiv	w1, w1, w21
	cmp	w27, 32
	mov	w0, 32
	csel	w27, w27, w0, le
	cmp	w1, w27
	csel	w3, w1, w27, le
	str	w3, [x19, 48]
.L182:
	cbz	w3, .L180
	sub	w0, w3, #1
	mov	x1, 476
	mov	w2, 12
	ldr	w4, [x19, 60]
	umaddl	x2, w0, w2, x1
	add	x1, x19, 464
	mov	w0, w7
	add	x2, x19, x2
	.p2align 2
.L185:
	str	w0, [x1], 12
	add	w0, w0, w21
	cmp	x2, x1
	bne	.L185
	ldr	w0, [x29, 144]
	add	w4, w3, w4
	str	w4, [x19, 60]
	cmp	w0, 1
	beq	.L255
	madd	w6, w21, w3, w6
	add	w0, w6, w22
.L197:
	add	x2, x19, 80
	mov	w1, 0
	.p2align 2
.L189:
	add	w1, w1, 1
	str	w0, [x2], 4
	cmp	w1, w3
	add	w0, w0, 32
	bcc	.L189
.L188:
	ldr	w4, [x19, 56]
	add	w6, w6, w3, lsl 5
	add	w22, w6, w22
	cbz	w4, .L194
	sub	w2, w4, #1
	ldr	w5, [x19, 64]
	add	x2, x2, 27
	add	x1, x19, 208
	mov	w0, w22
	add	x2, x19, x2, lsl 3
	.p2align 2
.L193:
	str	w0, [x1], 8
	add	w0, w0, w20
	cmp	x2, x1
	bne	.L193
	add	w0, w4, w5
	str	w0, [x19, 64]
.L194:
	madd	w20, w4, w20, w6
	str	w20, [x19]
	tbnz	w23, #31, .L192
	ldr	x0, .LC79
	ldr	x0, [x0, w23, sxtw 3]
	cbz	x0, .L192
	add	w0, w20, w22
	cbz	w3, .L192
	sub	w4, w3, #1
	mov	w5, 12
	mov	x2, 860
	add	x1, x19, 848
	umaddl	x2, w4, w5, x2
	add	x2, x19, x2
	.p2align 2
.L195:
	str	w0, [x1], 12
	add	w0, w0, 1024
	cmp	x2, x1
	bne	.L195
.L192:
	add	w20, w20, w3, lsl 10
	mov	w0, 0
	str	w20, [x19]
.L237:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L254:
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
	cbnz	w27, .L179
.L181:
	str	wzr, [x19, 48]
.L180:
	ldr	x2, .LC70
	ldr	x3, .LC85
.L243:
	ldr	x1, .LC71
	add	x2, x2, 184
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
.L179:
	cmp	w27, 32
	mov	w0, 32
	sdiv	w1, w1, w21
	csel	w27, w27, w0, le
	cmp	w27, w1
	csel	w3, w27, w1, le
	str	w3, [x19, 48]
	b	.L182
	.p2align 3
.L248:
	mul	w20, w3, w2
	add	w20, w20, 143
	and	w20, w20, -128
	mul	w1, w26, w20
	cmp	w28, w1
	ble	.L164
	add	w7, w22, 1023
	asr	w0, w20, 1
	and	w7, w7, -1024
	sub	w1, w28, w1
	stp	w0, w26, [x19, 52]
	sub	w6, w7, w22
	add	w28, w21, 255
	sub	w1, w1, w6
	and	w28, w28, -256
	mov	w2, w24
	tbnz	w23, #31, .L202
	ldr	x4, .LC79
	stp	w1, w6, [x29, 104]
	stp	w7, w3, [x29, 112]
	ldr	x0, [x4, w23, sxtw 3]
	str	x4, [x29, 120]
	add	x0, x0, 507904
	add	x0, x0, 1752
	bl	IsMain10Profile
	ldp	w1, w6, [x29, 104]
	ldp	w7, w3, [x29, 112]
	ldr	x4, [x29, 120]
	cbz	w0, .L207
	cmp	w28, wzr
	add	w8, w28, 3
	csel	w8, w8, w28, lt
	add	w9, w24, 31
	asr	w8, w8, 2
	and	w26, w9, -32
	mov	w2, w24
	b	.L168
	.p2align 3
.L250:
	lsl	w0, w3, 4
	mul	w0, w0, w28
	lsl	w21, w0, 2
	sub	w21, w21, w0
	b	.L171
.L256:
	mov	w20, 128
	movk	w20, 0x24, lsl 16
.L202:
	lsl	w0, w28, 4
	str	w0, [x19, 4]
	asr	w0, w0, 1
	str	w0, [x19, 8]
.L242:
	mov	w5, 0
	mov	w0, 0
	mov	w8, 0
	mov	w26, 0
	mov	w24, 0
	b	.L169
	.p2align 3
.L255:
	ldr	x0, .LC86
	ldr	x4, [x0]
	cbz	x4, .L187
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
.L187:
	madd	w6, w21, w3, w6
	add	w0, w6, w22
	cbnz	w3, .L197
	b	.L188
	.p2align 3
.L166:
	lsl	w0, w26, 14
	add	w0, w0, w26, lsl 11
	add	w0, w0, w26
	lsl	w0, w0, 7
	cmp	w28, w0
	ble	.L164
	add	w7, w22, 1023
	mov	w1, 64
	movk	w1, 0x12, lsl 16
	and	w7, w7, -1024
	stp	w1, w26, [x19, 52]
	sub	w0, w28, w0
	sub	w6, w7, w22
	add	w28, w21, 255
	add	w2, w24, 63
	and	w28, w28, -256
	and	w2, w2, -64
	sub	w1, w0, w6
	tbnz	w23, #31, .L256
	ldr	x4, .LC79
	ldr	x0, [x4, w23, sxtw 3]
	ldr	w0, [x0, 1612]
	cmp	w0, 8
	ble	.L208
	cmp	w28, wzr
	add	w8, w28, 3
	csel	w8, w8, w28, lt
	add	w9, w2, 63
	mov	w20, 128
	asr	w8, w8, 2
	and	w26, w9, -64
	movk	w20, 0x24, lsl 16
.L168:
	lsl	w0, w28, 4
	str	w0, [x19, 4]
	asr	w0, w0, 1
	str	w0, [x19, 8]
	ldr	x0, [x4, w23, sxtw 3]
	ldr	w0, [x0, 1280]
	cmp	w0, 1
	bne	.L210
.L249:
	cmp	w25, 17
	mov	w0, 1920
	ccmp	w21, w0, 0, ne
	ble	.L210
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
	b	.L169
	.p2align 3
.L252:
	mul	w0, w0, w11
	lsl	w3, w0, 2
	sub	w0, w3, w0
	b	.L175
	.p2align 3
.L176:
	adds	w5, w0, 63
	add	w3, w0, 126
	csel	w3, w3, w5, mi
	adds	w5, w23, 2047
	add	w23, w23, 4094
	asr	w3, w3, 6
	csel	w5, w23, w5, mi
	and	w5, w5, -2048
	add	w10, w5, 127
	cmp	w5, wzr
	csel	w5, w10, w5, lt
	lsl	w10, w3, 2
	sub	w10, w10, w3
	asr	w5, w5, 7
	lsl	w10, w10, 5
	mul	w10, w5, w10
	lsr	w10, w10, 1
	b	.L177
.L207:
	mov	w2, w24
	mov	w26, 0
	mov	w8, 0
	b	.L168
.L208:
	mov	w20, 128
	mov	w26, 0
	movk	w20, 0x24, lsl 16
	mov	w8, 0
	b	.L168
.L158:
	ldr	x2, .LC70
	ldr	x3, .LC72
	b	.L243
.L164:
	ldr	x2, .LC70
	ldr	x3, .LC78
	b	.L243
.L246:
	ldr	x2, .LC70
	ldr	x3, .LC69
	b	.L243
.L251:
	ldr	x1, .LC81
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L237
.L253:
	ldr	x2, .LC70
	ldr	x3, .LC83
	b	.L243
.L247:
	ldr	x2, .LC70
	ldr	x3, .LC74
	b	.L243
	.size	VDMHAL_V5R2C1_ArrangeMem_Specific, .-VDMHAL_V5R2C1_ArrangeMem_Specific
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC70:
	.xword	.LANCHOR0
	.align	3
.LC71:
	.xword	.LC7
	.align	3
.LC72:
	.xword	.LC23
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC75:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC76:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC78:
	.xword	.LC77
	.align	3
.LC79:
	.xword	s_pstVfmwChan
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.align	3
.LC85:
	.xword	.LC84
	.align	3
.LC86:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ArrangeMem
	.type	VDMHAL_V5R2C1_ArrangeMem, %function
VDMHAL_V5R2C1_ArrangeMem:
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
	beq	.L261
	tbnz	w19, #31, .L262
	mov	w0, w19
	bl	VCTRL_GetVidStd
	mov	w1, w0
	ldr	x0, .LC87
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 1552]
	cmp	w0, 1
	beq	.L264
.L259:
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
	bl	VDMHAL_V5R2C1_ArrangeMem_Specific
.L263:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L262:
	mov	w1, 22
	b	.L259
	.p2align 3
.L261:
	mov	w1, 16
	b	.L259
	.p2align 3
.L264:
	ldr	x6, [x29, 80]
	mov	w5, w23
	mov	w4, w22
	mov	w3, w21
	mov	w2, w20
	mov	w0, w19
	bl	VDMHAL_V5R2C1_ArrangeMem_Normal
	b	.L263
	.size	VDMHAL_V5R2C1_ArrangeMem, .-VDMHAL_V5R2C1_ArrangeMem
	.align	3
.LC87:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ResetVdm
	.type	VDMHAL_V5R2C1_ResetVdm, %function
VDMHAL_V5R2C1_ResetVdm:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, wzr
	ble	.L266
	ldr	x2, .LC88
	mov	w4, 0
	ldr	x1, .LC90
	mov	w3, w21
	add	x2, x2, 224
	mov	w0, 0
	bl	dprint_vfmw
.L265:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L266:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L278
	sxtw	x22, w21
	ldr	x24, .LC93
	lsl	x0, x22, 6
	ldr	x20, .LC94
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	ldr	x2, [x20]
	add	x0, x0, x1, lsl 2
	ldr	x0, [x24, x0]
	ldr	w25, [x0, 36]
	ldr	w23, [x2, 120]
	tbz	x23, 0, .L265
	ldr	x26, .LC95
	mov	w0, 2
	bfi	w23, w0, 8, 2
	str	w23, [x2, 120]
	mov	w19, 0
	orr	w23, w23, 64
	ldr	x0, [x26, 224]
	blr	x0
	ldr	x0, [x20]
	str	w23, [x0, 120]
	b	.L270
	.p2align 3
.L279:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L271
.L270:
	ldr	x1, [x26, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20]
	ldr	w0, [x0, 372]
	tbz	x0, 2, .L279
	cmp	w19, 999
	bgt	.L271
	ldr	x2, .LC88
	mov	w3, w21
	ldr	x1, .LC99
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
.L273:
	ldr	x0, [x20]
	and	w23, w23, -65
	str	w23, [x0, 120]
	and	w23, w23, -769
	ldr	x0, [x26, 224]
	blr	x0
	lsl	x0, x22, 6
	ldr	x1, [x20]
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x22, x0, x22
	str	w23, [x1, 120]
	add	x22, x0, x22, lsl 2
	ldr	x0, [x24, x22]
	str	w25, [x0, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L271:
	ldr	x2, .LC88
	mov	w3, w21
	ldr	x1, .LC97
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
	b	.L273
.L278:
	ldr	x1, .LC92
	mov	x2, 0
	bl	dprint_vfmw
	b	.L265
	.size	VDMHAL_V5R2C1_ResetVdm, .-VDMHAL_V5R2C1_ResetVdm
	.align	3
.LC88:
	.xword	.LANCHOR0
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC93:
	.xword	g_HwMem
	.align	3
.LC94:
	.xword	g_pstRegCrg
	.align	3
.LC95:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC99:
	.xword	.LC98
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.type	VDMHAL_V5R2C1_SetSmmuPageTableAddr, %function
VDMHAL_V5R2C1_SetSmmuPageTableAddr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC100
	ldr	x3, [x0, 392]
	cbz	x3, .L280
	add	x2, x29, 60
	add	x1, x29, 56
	add	x0, x29, 52
	blr	x3
	cbnz	w19, .L282
	ldr	x0, .LC101
	ldp	w3, w2, [x29, 52]
	ldr	w1, [x29, 60]
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w3, [x0, 524]
	str	w2, [x0, 772]
	str	w1, [x0, 776]
.L280:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L282:
	ldr	x20, .LC102
	mov	w3, w19
	ldr	x21, .LC104
	mov	w4, 1
	add	x20, x20, 248
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
	.size	VDMHAL_V5R2C1_SetSmmuPageTableAddr, .-VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.align	3
.LC100:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC101:
	.xword	g_HwMem
	.align	3
.LC102:
	.xword	.LANCHOR0
	.align	3
.LC104:
	.xword	.LC103
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_EnableSmmu
	.type	VDMHAL_V5R2C1_EnableSmmu, %function
VDMHAL_V5R2C1_EnableSmmu:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC106
	mov	w1, 8
	movk	w1, 0x3, lsl 16
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_EnableSmmu, .-VDMHAL_V5R2C1_EnableSmmu
	.align	3
.LC106:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GlbResetX
	.type	VDMHAL_V5R2C1_GlbResetX, %function
VDMHAL_V5R2C1_GlbResetX:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w23, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	ldr	x20, .LC107
	ldr	x0, [x20]
	ldr	w22, [x0, 120]
	tbnz	x22, 0, .L298
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L298:
	ldr	x21, .LC108
	mov	w1, 2
	bfi	w22, w1, 8, 2
	str	w22, [x0, 120]
	mov	w19, 0
	orr	w22, w22, 16
	ldr	x0, [x21, 224]
	blr	x0
	ldr	x0, [x20]
	str	w22, [x0, 120]
	b	.L290
	.p2align 3
.L299:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L291
.L290:
	ldr	x1, [x21, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20]
	ldr	w0, [x0, 372]
	tbz	x0, 0, .L299
	cmp	w19, 999
	bgt	.L291
	ldr	x2, .LC109
	mov	w3, w23
	ldr	x1, .LC113
	mov	w0, 0
	add	x2, x2, 288
	bl	dprint_vfmw
.L293:
	ldr	x0, [x20]
	and	w22, w22, -17
	str	w22, [x0, 120]
	and	w22, w22, -769
	ldr	x0, [x21, 224]
	blr	x0
	ldr	x0, [x20]
	str	w22, [x0, 120]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L291:
	ldr	x2, .LC109
	mov	w3, w23
	ldr	x1, .LC111
	mov	w0, 0
	add	x2, x2, 288
	bl	dprint_vfmw
	b	.L293
	.size	VDMHAL_V5R2C1_GlbResetX, .-VDMHAL_V5R2C1_GlbResetX
	.align	3
.LC107:
	.xword	g_pstRegCrg
	.align	3
.LC108:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC109:
	.xword	.LANCHOR0
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GlbReset
	.type	VDMHAL_V5R2C1_GlbReset, %function
VDMHAL_V5R2C1_GlbReset:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L303
	mov	w0, 0
	bl	VDMHAL_V5R2C1_GlbResetX
.L300:
	ldp	x29, x30, [sp], 16
	ret
.L303:
	ldr	x2, .LC114
	mov	w3, -121438208
	ldr	x1, .LC116
	add	x2, x2, 312
	bl	dprint_vfmw
	b	.L300
	.size	VDMHAL_V5R2C1_GlbReset, .-VDMHAL_V5R2C1_GlbReset
	.align	3
.LC114:
	.xword	.LANCHOR0
	.align	3
.LC116:
	.xword	.LC115
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ClearIntState
	.type	VDMHAL_V5R2C1_ClearIntState, %function
VDMHAL_V5R2C1_ClearIntState:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x19, w0
	mov	x0, x30
	mov	x20, x19
	bl	_mcount
	ldr	x21, .LC118
	ldr	x0, .LC117
	add	x1, x21, x19, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x0, [x0, x1, lsl 3]
	cbz	x0, .L314
	ldr	w22, [x0, 1312]
.L305:
	cmp	w20, wzr
	bgt	.L316
	lsl	x0, x19, 6
	ldr	x23, .LC121
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x23, x20]
	cbz	x0, .L317
.L308:
	cmp	w22, 1
	bne	.L315
	add	x19, x21, x19, lsl 6
	ldr	w1, [x19, 44]
	cmp	w1, 1
	beq	.L315
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L318
	cmp	w1, 3
	bne	.L304
	mov	w1, -15
	str	w1, [x0, 32]
	b	.L304
	.p2align 3
.L316:
	ldr	x2, .LC119
	mov	w4, 0
	ldr	x1, .LC120
	mov	w3, w20
	add	x2, x2, 336
	mov	w0, 0
	bl	dprint_vfmw
.L304:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L315:
	mov	w1, -1
	str	w1, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L314:
	mov	w22, 0
	b	.L305
	.p2align 3
.L317:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L309
	str	x0, [x23, x20]
	b	.L308
	.p2align 3
.L318:
	mov	w1, -12
	str	w1, [x0, 32]
	b	.L304
.L309:
	ldr	x1, .LC123
	mov	w0, 0
	bl	dprint_vfmw
	b	.L304
	.size	VDMHAL_V5R2C1_ClearIntState, .-VDMHAL_V5R2C1_ClearIntState
	.align	3
.LC117:
	.xword	s_pstVfmwChan
	.align	3
.LC118:
	.xword	g_VdmDrvParam
	.align	3
.LC119:
	.xword	.LANCHOR0
	.align	3
.LC120:
	.xword	.LC89
	.align	3
.LC121:
	.xword	g_HwMem
	.align	3
.LC123:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ClearMMUIntState
	.type	VDMHAL_V5R2C1_ClearMMUIntState, %function
VDMHAL_V5R2C1_ClearMMUIntState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L324
	lsl	x3, x19, 6
	ldr	x20, .LC126
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L325
.L322:
	add	x0, x0, 61440
	mov	w1, 7
	str	w1, [x0, 44]
.L319:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L324:
	ldr	x2, .LC124
	mov	w3, w19
	ldr	x1, .LC125
	mov	w4, 0
	add	x2, x2, 368
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L325:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L323
	str	x0, [x20, x19]
	b	.L322
.L323:
	ldr	x1, .LC127
	mov	w0, 0
	bl	dprint_vfmw
	b	.L319
	.size	VDMHAL_V5R2C1_ClearMMUIntState, .-VDMHAL_V5R2C1_ClearMMUIntState
	.align	3
.LC124:
	.xword	.LANCHOR0
	.align	3
.LC125:
	.xword	.LC89
	.align	3
.LC126:
	.xword	g_HwMem
	.align	3
.LC127:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_MaskInt
	.type	VDMHAL_V5R2C1_MaskInt, %function
VDMHAL_V5R2C1_MaskInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L331
	lsl	x3, x19, 6
	ldr	x20, .LC130
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L332
.L329:
	mov	w1, -1
	str	w1, [x0, 36]
.L326:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L331:
	ldr	x2, .LC128
	mov	w3, w19
	ldr	x1, .LC129
	mov	w4, 0
	add	x2, x2, 400
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L332:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L330
	str	x0, [x20, x19]
	b	.L329
.L330:
	ldr	x1, .LC131
	mov	w0, 0
	bl	dprint_vfmw
	b	.L326
	.size	VDMHAL_V5R2C1_MaskInt, .-VDMHAL_V5R2C1_MaskInt
	.align	3
.LC128:
	.xword	.LANCHOR0
	.align	3
.LC129:
	.xword	.LC89
	.align	3
.LC130:
	.xword	g_HwMem
	.align	3
.LC131:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetIntMaskCfg
	.type	VDMHAL_V5R2C1_GetIntMaskCfg, %function
VDMHAL_V5R2C1_GetIntMaskCfg:
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
	.size	VDMHAL_V5R2C1_GetIntMaskCfg, .-VDMHAL_V5R2C1_GetIntMaskCfg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_EnableInt
	.type	VDMHAL_V5R2C1_EnableInt, %function
VDMHAL_V5R2C1_EnableInt:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC133
	sxtw	x0, w19
	ldr	x2, .LC132
	add	x1, x1, x0, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x1, [x2, x1, lsl 3]
	cbz	x1, .L344
	ldr	w20, [x1, 1312]
.L337:
	cmp	w19, wzr
	bgt	.L345
	lsl	x19, x0, 6
	ldr	x21, .LC136
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	ldr	x0, [x21, x19]
	cbz	x0, .L346
.L340:
	mov	w1, -6
	mov	w2, -2
	cmp	w20, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 36]
.L336:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L345:
	ldr	x2, .LC134
	mov	w3, w19
	ldr	x1, .LC135
	mov	w4, 0
	add	x2, x2, 424
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L344:
	mov	w20, 0
	b	.L337
	.p2align 3
.L346:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L341
	str	x0, [x21, x19]
	b	.L340
.L341:
	ldr	x1, .LC137
	mov	w0, 0
	bl	dprint_vfmw
	b	.L336
	.size	VDMHAL_V5R2C1_EnableInt, .-VDMHAL_V5R2C1_EnableInt
	.align	3
.LC132:
	.xword	s_pstVfmwChan
	.align	3
.LC133:
	.xword	g_VdmDrvParam
	.align	3
.LC134:
	.xword	.LANCHOR0
	.align	3
.LC135:
	.xword	.LC89
	.align	3
.LC136:
	.xword	g_HwMem
	.align	3
.LC137:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CheckReg
	.type	VDMHAL_V5R2C1_CheckReg, %function
VDMHAL_V5R2C1_CheckReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	bgt	.L364
	lsl	x0, x19, 6
	ldr	x21, .LC141
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x21, x20]
	cbz	x0, .L365
.L350:
	sub	w0, w22, #1
	cmp	w0, 6
	bls	.L366
	ldr	x2, .LC138
	mov	w3, w22
	ldr	x1, .LC145
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
.L363:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L366:
	ldr	x1, .LC146
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx357
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx357:
	.section	.rodata
	.align	0
	.align	2
.L357:
	.byte	(.L361 - .Lrtx357) / 4
	.byte	(.L358 - .Lrtx357) / 4
	.byte	(.L359 - .Lrtx357) / 4
	.byte	(.L360 - .Lrtx357) / 4
	.byte	(.L362 - .Lrtx357) / 4
	.byte	(.L352 - .Lrtx357) / 4
	.byte	(.L354 - .Lrtx357) / 4
	.text
	.p2align 3
.L362:
	mov	x1, 61480
.L356:
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
.L361:
	mov	x1, 28
	b	.L356
	.p2align 3
.L360:
	mov	x1, 40
	b	.L356
	.p2align 3
.L359:
	mov	x1, 36
	b	.L356
	.p2align 3
.L358:
	mov	x1, 32
	b	.L356
	.p2align 3
.L354:
	mov	x1, 62272
	b	.L356
	.p2align 3
.L352:
	mov	x1, 62304
	b	.L356
	.p2align 3
.L365:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L351
	str	x0, [x21, x20]
	b	.L350
	.p2align 3
.L364:
	ldr	x2, .LC138
	mov	w3, w19
	ldr	x1, .LC140
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L363
.L351:
	ldr	x2, .LC138
	mov	w0, 0
	ldr	x1, .LC143
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
	b	.L363
	.size	VDMHAL_V5R2C1_CheckReg, .-VDMHAL_V5R2C1_CheckReg
	.align	3
.LC138:
	.xword	.LANCHOR0
	.align	3
.LC140:
	.xword	.LC139
	.align	3
.LC141:
	.xword	g_HwMem
	.align	3
.LC143:
	.xword	.LC142
	.align	3
.LC145:
	.xword	.LC144
	.align	3
.LC146:
	.xword	.L357
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ReadMMUMask
	.type	VDMHAL_V5R2C1_ReadMMUMask, %function
VDMHAL_V5R2C1_ReadMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	ble	.L370
	ldr	x2, .LC148
	mov	w3, w19
	ldr	x1, .LC150
	mov	w4, 1
	add	x2, x2, 472
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L370:
	lsl	x0, x19, 6
	ldr	x1, .LC147
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
	.size	VDMHAL_V5R2C1_ReadMMUMask, .-VDMHAL_V5R2C1_ReadMMUMask
	.align	3
.LC147:
	.xword	g_HwMem
	.align	3
.LC148:
	.xword	.LANCHOR0
	.align	3
.LC150:
	.xword	.LC149
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_WriteMMUMask
	.type	VDMHAL_V5R2C1_WriteMMUMask, %function
VDMHAL_V5R2C1_WriteMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	ble	.L374
	ldr	x2, .LC152
	mov	w3, w19
	ldr	x1, .LC153
	mov	w4, 1
	add	x2, x2, 504
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L374:
	lsl	x0, x19, 6
	ldr	x1, .LC151
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
	.size	VDMHAL_V5R2C1_WriteMMUMask, .-VDMHAL_V5R2C1_WriteMMUMask
	.align	3
.LC151:
	.xword	g_HwMem
	.align	3
.LC152:
	.xword	.LANCHOR0
	.align	3
.LC153:
	.xword	.LC103
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_PrepareDec
	.type	VDMHAL_V5R2C1_PrepareDec, %function
VDMHAL_V5R2C1_PrepareDec:
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
	cbz	x22, .L394
	cmp	w21, wzr
	bgt	.L395
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
	cmp	w20, 17
	bls	.L396
.L393:
	mov	w0, -1
	b	.L377
	.p2align 3
.L396:
	ldr	x0, .LC158
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx380
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx380:
	.section	.rodata
	.align	0
	.align	2
.L380:
	.byte	(.L390 - .Lrtx380) / 4
	.byte	(.L381 - .Lrtx380) / 4
	.byte	(.L382 - .Lrtx380) / 4
	.byte	(.L383 - .Lrtx380) / 4
	.byte	(.L393 - .Lrtx380) / 4
	.byte	(.L384 - .Lrtx380) / 4
	.byte	(.L385 - .Lrtx380) / 4
	.byte	(.L393 - .Lrtx380) / 4
	.byte	(.L386 - .Lrtx380) / 4
	.byte	(.L387 - .Lrtx380) / 4
	.byte	(.L388 - .Lrtx380) / 4
	.byte	(.L388 - .Lrtx380) / 4
	.byte	(.L388 - .Lrtx380) / 4
	.byte	(.L389 - .Lrtx380) / 4
	.byte	(.L393 - .Lrtx380) / 4
	.byte	(.L390 - .Lrtx380) / 4
	.byte	(.L391 - .Lrtx380) / 4
	.byte	(.L392 - .Lrtx380) / 4
	.text
	.p2align 3
.L390:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	H264HAL_V5R2C1_StartDec
.L377:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L391:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	HEVCHAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L389:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP8HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L388:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP6HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L387:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV9HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L386:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV8HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L385:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	AVSHAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L384:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	DIVX3HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L383:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP2HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L382:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP4HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L381:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VC1HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L392:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP9HAL_V5R2C1_StartDec
	b	.L377
	.p2align 3
.L395:
	ldr	x2, .LC154
	mov	w3, w21
	ldr	x1, .LC157
	mov	w4, 0
	add	x2, x2, 536
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L394:
	ldr	x2, .LC154
	mov	x3, 0
	ldr	x1, .LC156
	mov	w0, 0
	add	x2, x2, 536
	bl	dprint_vfmw
	mov	w0, -1
	b	.L377
	.size	VDMHAL_V5R2C1_PrepareDec, .-VDMHAL_V5R2C1_PrepareDec
	.align	3
.LC154:
	.xword	.LANCHOR0
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC157:
	.xword	.LC89
	.align	3
.LC158:
	.xword	.L380
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_IsVdmReady
	.type	VDMHAL_V5R2C1_IsVdmReady, %function
VDMHAL_V5R2C1_IsVdmReady:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC159
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L402
	cmp	w19, wzr
	ble	.L403
	ldr	x2, .LC162
	mov	w4, 1
	ldr	x1, .LC164
	mov	w3, w19
	add	x2, x2, 568
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 0
.L399:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L403:
	ldr	w0, [x0, 28]
	ldr	x19, [sp, 16]
	ubfx	x0, x0, 17, 1
	ldp	x29, x30, [sp], 32
	ret
.L402:
	ldr	x2, .LC162
	ldr	x3, .LC161
	ldr	x1, .LC163
	add	x2, x2, 568
	bl	dprint_vfmw
	mov	w0, -1
	b	.L399
	.size	VDMHAL_V5R2C1_IsVdmReady, .-VDMHAL_V5R2C1_IsVdmReady
	.align	3
.LC159:
	.xword	g_HwMem
	.align	3
.LC161:
	.xword	.LC160
	.align	3
.LC162:
	.xword	.LANCHOR0
	.align	3
.LC163:
	.xword	.LC7
	.align	3
.LC164:
	.xword	.LC149
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_IsVdmRun
	.type	VDMHAL_V5R2C1_IsVdmRun, %function
VDMHAL_V5R2C1_IsVdmRun:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC165
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L409
	cmp	w19, wzr
	ble	.L410
	ldr	x2, .LC168
	mov	w4, 1
	ldr	x1, .LC169
	mov	w3, w19
	add	x2, x2, 600
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
.L406:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L410:
	ldr	w0, [x0, 40]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L409:
	ldr	x1, .LC167
	bl	dprint_vfmw
	mov	w0, 0
	b	.L406
	.size	VDMHAL_V5R2C1_IsVdmRun, .-VDMHAL_V5R2C1_IsVdmRun
	.align	3
.LC165:
	.xword	g_HwMem
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC168:
	.xword	.LANCHOR0
	.align	3
.LC169:
	.xword	.LC149
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_IsVdhDecOver
	.type	VDMHAL_V5R2C1_IsVdhDecOver, %function
VDMHAL_V5R2C1_IsVdhDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC170
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L419
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R2C1_CheckReg
	cmp	w19, 2
	beq	.L416
	cmp	w19, 3
	beq	.L416
	cmp	w19, 1
	ubfx	x0, x0, 17, 1
	beq	.L413
	ldr	x2, .LC172
	mov	w3, w19
	ldr	x1, .LC174
	mov	w0, 0
	add	x2, x2, 624
	bl	dprint_vfmw
	mov	w0, 0
.L413:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L416:
	and	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L419:
	ldr	x2, .LC172
	ldr	x3, .LC171
	ldr	x1, .LC173
	add	x2, x2, 624
	bl	dprint_vfmw
	mov	w0, -1
	b	.L413
	.size	VDMHAL_V5R2C1_IsVdhDecOver, .-VDMHAL_V5R2C1_IsVdhDecOver
	.align	3
.LC170:
	.xword	g_HwMem
	.align	3
.LC171:
	.xword	.LC160
	.align	3
.LC172:
	.xword	.LANCHOR0
	.align	3
.LC173:
	.xword	.LC7
	.align	3
.LC174:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_IsVdhPartDecOver
	.type	VDMHAL_V5R2C1_IsVdhPartDecOver, %function
VDMHAL_V5R2C1_IsVdhPartDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC175
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L428
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R2C1_CheckReg
	cmp	w19, 1
	beq	.L424
	cmp	w19, 2
	ubfx	x0, x0, 2, 1
	bne	.L429
.L422:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L429:
	ldr	x2, .LC177
	mov	w3, w19
	ldr	x1, .LC179
	mov	w0, 0
	add	x2, x2, 656
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L424:
	ubfx	x0, x0, 19, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L428:
	ldr	x2, .LC177
	ldr	x3, .LC176
	ldr	x1, .LC178
	add	x2, x2, 656
	bl	dprint_vfmw
	mov	w0, -1
	b	.L422
	.size	VDMHAL_V5R2C1_IsVdhPartDecOver, .-VDMHAL_V5R2C1_IsVdhPartDecOver
	.align	3
.LC175:
	.xword	g_HwMem
	.align	3
.LC176:
	.xword	.LC160
	.align	3
.LC177:
	.xword	.LANCHOR0
	.align	3
.LC178:
	.xword	.LC7
	.align	3
.LC179:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_UpdateHardwareInfo
	.type	VDMHAL_V5R2C1_UpdateHardwareInfo, %function
VDMHAL_V5R2C1_UpdateHardwareInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	bl	_mcount
	cmp	w22, wzr
	bgt	.L431
	ldr	x4, .LC180
	add	x0, x4, 4
	add	x4, x4, 128
	ldr	w1, [x4, -128]
	cmp	w1, 1
	bne	.L435
	b	.L446
	.p2align 3
.L456:
	cmp	x0, x4
	beq	.L455
.L435:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L456
.L446:
	mov	w19, w1
.L432:
	sxtw	x20, w22
	ldr	x24, .LC185
	lsl	x0, x20, 6
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x21, x0, x20
	add	x21, x0, x21, lsl 2
	ldr	x1, [x24, x21]
	cbz	x1, .L457
.L436:
	lsl	x0, x20, 2
	ldr	x21, .LC187
	sub	x4, x0, x20
	ldr	x2, .LC191
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
	beq	.L458
	cmp	w19, 1
	beq	.L459
	ldr	w5, [x1, 4096]
	ldr	w3, [x1, 4108]
	ldr	w2, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w2, w0, [x4, 8]
	stp	w5, w3, [x4, 16]
	cbz	w19, .L460
.L441:
	mov	w0, 180
	add	x4, x1, 32768
	add	x1, x4, 256
	smull	x2, w22, w0
	add	x0, x2, 52
	add	x2, x2, 180
	add	x0, x21, x0
	add	x3, x21, x2
	.p2align 2
.L442:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L442
	mov	w0, 0
	cbnz	w19, .L449
	lsl	x1, x20, 2
	ldr	w3, [x4, 384]
	sub	x20, x1, x20
	ldr	w2, [x4, 388]
	lsl	x1, x20, 4
	sub	x1, x1, x20
	add	x21, x21, x1, lsl 2
	stp	w2, w3, [x21, 44]
.L449:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L460:
	ldr	w5, [x1, 176]
	ldr	w0, [x1, 180]
	stp	w5, w0, [x4, 24]
	ldr	w3, [x1, 184]
	ldr	w2, [x1, 188]
	ldr	w0, [x1, 192]
	stp	w3, w2, [x4, 32]
	str	w0, [x4, 40]
	b	.L441
	.p2align 3
.L455:
	mov	w19, 0
	b	.L432
.L458:
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
.L459:
	sub	x0, x5, x20
	and	w23, w3, 131071
	lsl	x0, x0, 2
	sub	x1, x0, x20
	add	x0, x0, x1, lsl 2
	add	x0, x24, x0
	ldr	w0, [x0, 56]
	bl	MEM_Phy2Vir
	cbz	x0, .L461
	sub	w1, w23, #1
	cmp	w1, 199
	bhi	.L447
	lsl	w1, w23, 2
	sub	w1, w1, #4
	lsl	x1, x1, 2
	add	x3, x1, 8
.L440:
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
	b	.L441
.L457:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L437
	str	x0, [x24, x21]
	mov	x1, x0
	b	.L436
.L447:
	mov	x3, 8
	mov	x1, 0
	b	.L440
.L431:
	ldr	x2, .LC181
	mov	w4, 0
	ldr	x1, .LC182
	mov	w3, w22
	add	x2, x2, 688
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L449
.L461:
	ldr	x2, .LC181
	ldr	x3, .LC189
	ldr	x1, .LC190
	add	x2, x2, 688
	bl	dprint_vfmw
	mov	w0, -1
	b	.L449
.L437:
	ldr	x1, .LC186
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L449
	.size	VDMHAL_V5R2C1_UpdateHardwareInfo, .-VDMHAL_V5R2C1_UpdateHardwareInfo
	.align	3
.LC180:
	.xword	g_DSPState
	.align	3
.LC181:
	.xword	.LANCHOR0
	.align	3
.LC182:
	.xword	.LC89
	.align	3
.LC185:
	.xword	g_HwMem
	.align	3
.LC186:
	.xword	.LC122
	.align	3
.LC187:
	.xword	g_BackUp
	.align	3
.LC189:
	.xword	.LC188
	.align	3
.LC190:
	.xword	.LC7
	.align	3
.LC191:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ReadMsgSlot
	.type	VDMHAL_V5R2C1_ReadMsgSlot, %function
VDMHAL_V5R2C1_ReadMsgSlot:
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
	beq	.L466
	cmp	w19, 800
	bhi	.L467
	ldr	x3, .LC196
	ubfiz	x2, x19, 2, 30
	mov	x1, x21
	mov	x0, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L464:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L467:
	ldr	x1, .LC195
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L464
	.p2align 3
.L466:
	ldr	x1, .LC193
	mov	x3, x21
	mov	x2, x20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L464
	.size	VDMHAL_V5R2C1_ReadMsgSlot, .-VDMHAL_V5R2C1_ReadMsgSlot
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC195:
	.xword	.LC194
	.align	3
.LC196:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_WriteMsgSlot
	.type	VDMHAL_V5R2C1_WriteMsgSlot, %function
VDMHAL_V5R2C1_WriteMsgSlot:
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
	beq	.L469
	sub	w0, w21, #1
	cmp	w0, 255
	bhi	.L469
	ldr	x3, .LC199
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
.L469:
	ldr	x1, .LC198
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMHAL_V5R2C1_WriteMsgSlot, .-VDMHAL_V5R2C1_WriteMsgSlot
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC199:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CfgRpMsg
	.type	VDMHAL_V5R2C1_CfgRpMsg, %function
VDMHAL_V5R2C1_CfgRpMsg:
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
	cbz	x0, .L514
	ldr	w2, [x19, 44]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L515
	ldr	w3, [x19, 64]
	mov	w4, 0
	ldp	w2, w0, [x19, 28]
	ldrb	w5, [x19]
	lsl	w2, w2, w3
	lsl	w0, w0, w3
	add	w1, w2, 255
	cmp	w5, 1
	and	w1, w1, -256
	lsl	w3, w1, 4
	beq	.L516
	ldr	w2, [x19, 4]
	cmp	w2, 16
	beq	.L477
.L525:
	add	w0, w0, 31
	mov	w23, 8
	and	w0, w0, -32
	madd	w0, w0, w1, w4
.L500:
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
	cbnz	w0, .L517
.L479:
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
	bls	.L518
.L481:
	ldr	w0, [x19, 56]
	mov	w11, 0
	cbz	w0, .L519
.L482:
	cmp	w0, 1
	beq	.L498
.L524:
	sub	w11, w11, #1
	uxth	w11, w11
.L499:
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
.L512:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L517:
	add	w0, w3, 15
	cmp	w3, wzr
	csel	w1, w0, w3, lt
	asr	w1, w1, 4
	b	.L479
	.p2align 3
.L519:
	ldr	w0, [x19, 64]
	cmp	w0, 6
	beq	.L503
	cmp	w0, 5
	beq	.L504
	cmp	w0, 4
	mov	w2, 8
	beq	.L483
	ldr	x1, .LC207
	mov	w0, 1
	bl	dprint_vfmw
	mov	w2, 1
.L483:
	ldr	w8, [x19, 44]
	cmp	w8, wzr
	ble	.L513
	mul	w12, w22, w21
	mov	w4, 0
	mov	w6, 0
	sub	w13, w12, #1
	mov	w11, 0
	sub	w9, w2, #1
	b	.L486
	.p2align 3
.L522:
	ldrsh	w6, [x10, 74]
	sub	w6, w6, #1
	add	w6, w6, w2
	udiv	w6, w6, w2
	mul	w6, w6, w2
	cmp	w0, w6
	bgt	.L489
.L488:
	add	w4, w4, 1
	cmp	w4, w8
	bge	.L520
.L497:
	cmp	w4, 199
	bgt	.L521
.L486:
	add	x10, x19, x4, sxtw 2
	cmp	w4, wzr
	ldrsh	w1, [x10, 78]
	sub	w0, w1, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	bgt	.L522
	ccmp	w0, w6, 0, ne
	ble	.L488
.L491:
	ldrsh	w1, [x10, 76]
	cmp	w12, w0
	csel	w0, w0, w13, hi
	add	w5, w11, 1
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w5, 250
	bgt	.L523
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
	blt	.L497
.L520:
	ldr	w0, [x19, 56]
	cmp	w0, 1
	bne	.L524
	.p2align 2
.L498:
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
	b	.L499
	.p2align 3
.L516:
	adds	w4, w2, 2047
	add	w2, w2, 4094
	csel	w2, w2, w4, mi
	add	w5, w0, 126
	and	w2, w2, -2048
	cmp	w2, wzr
	add	w4, w2, 127
	csel	w2, w4, w2, lt
	adds	w6, w0, 63
	csel	w4, w5, w6, mi
	asr	w2, w2, 7
	asr	w4, w4, 6
	lsl	w4, w4, 5
	mul	w4, w2, w4
	ldr	w2, [x19, 4]
	cmp	w2, 16
	bne	.L525
.L477:
	madd	w0, w0, w1, w4
	mov	w23, 10
	b	.L500
	.p2align 3
.L518:
	add	w22, w22, w22, lsr 31
	asr	w22, w22, 1
	b	.L481
	.p2align 3
.L492:
	udiv	w0, w0, w2
	ldrsh	w1, [x5, 80]
	udiv	w1, w1, w2
	mul	w0, w0, w2
	mul	w1, w1, w2
	cmp	w0, w1
	add	w14, w1, 1
	bhi	.L493
	sub	w1, w4, #1
	cmp	w0, w14
	add	x1, x19, x1, sxtw 2
	beq	.L493
	ldrsh	w1, [x1, 78]
	sub	w1, w1, #1
	add	w1, w1, w2
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w0, w1
	bhi	.L491
.L493:
	cmp	w7, 199
	mov	w4, w3
	bgt	.L526
	ldrsh	w1, [x5, 82]
.L489:
	add	w3, w4, 1
	add	x5, x19, x4, sxtw 2
	cmp	w8, w3
	add	w0, w9, w1
	add	w7, w3, 1
	bgt	.L492
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L491
.L504:
	mov	w2, 4
	b	.L483
	.p2align 3
.L526:
	add	x0, x19, x3, sxtw 2
	ldrsh	w0, [x0, 78]
	sub	w0, w0, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L491
.L521:
	ldr	x2, .LC202
	mov	w3, 2128
	ldr	x1, .LC209
	mov	w0, 0
	add	x2, x2, 752
	bl	dprint_vfmw
.L513:
	mov	w11, 0
	ldr	w0, [x19, 56]
	b	.L482
.L503:
	mov	w2, 2
	b	.L483
.L523:
	mov	w0, 1
	str	w0, [x19, 56]
	b	.L498
.L515:
	ldr	x1, .LC205
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L512
.L514:
	ldr	x2, .LC202
	mov	w0, 0
	ldr	x3, .LC201
	ldr	x1, .LC203
	add	x2, x2, 728
	bl	dprint_vfmw
	mov	w0, -1
	b	.L512
	.size	VDMHAL_V5R2C1_CfgRpMsg, .-VDMHAL_V5R2C1_CfgRpMsg
	.align	3
.LC201:
	.xword	.LC200
	.align	3
.LC202:
	.xword	.LANCHOR0
	.align	3
.LC203:
	.xword	.LC7
	.align	3
.LC205:
	.xword	.LC204
	.align	3
.LC207:
	.xword	.LC206
	.align	3
.LC209:
	.xword	.LC208
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CfgRpReg
	.type	VDMHAL_V5R2C1_CfgRpReg, %function
VDMHAL_V5R2C1_CfgRpReg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x0, x30
	mov	w21, w3
	mov	x22, x1
	mov	x20, x4
	bl	_mcount
	str	wzr, [x29, 60]
	cmp	w21, wzr
	bgt	.L553
	ldr	x0, [x22]
	cbz	x0, .L554
.L530:
	ldr	x19, .LC213
	ldr	w3, [x22, 64]
	ldrb	w0, [x19]
	and	w3, w3, -16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L555
	mov	x0, x20
	mov	w2, 16
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	mov	w3, 53763
	movk	w3, 0x2000, lsl 16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L556
	mov	x0, x20
	mov	w2, 12
	mov	w1, 2
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	VDH_Record_RegData
	str	w22, [x29, 60]
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L557
	mov	x0, x20
	mov	w3, w22
	mov	w2, 60
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L558
	mov	x0, x20
	mov	w3, w22
	mov	w2, 64
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L559
	mov	x0, x20
	mov	w3, w22
	mov	w2, 68
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L560
	mov	x0, x20
	mov	w3, w22
	mov	w2, 72
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L561
	mov	x0, x20
	mov	w3, w22
	mov	w2, 76
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L562
	mov	x0, x20
	mov	w3, w22
	mov	w2, 80
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L563
	mov	x0, x20
	mov	w3, w22
	mov	w2, 84
	mov	w1, 2
	bl	VDH_Record_RegData
	mov	w0, 0
.L550:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L555:
	sxtw	x1, w21
	ldr	x2, .LC214
	lsl	x0, x1, 6
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x4, x0, x1
	add	x0, x0, x4, lsl 2
	ldr	x0, [x2, x0]
	str	w3, [x0, 16]
.L533:
	lsl	x0, x1, 6
	mov	w4, 53763
	sub	x0, x0, x1
	movk	w4, 0x2000, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 12]
.L535:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 60]
.L537:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 64]
.L539:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 68]
.L541:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 72]
.L543:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 76]
.L545:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 80]
.L547:
	lsl	x3, x1, 6
	mov	w4, 3075
	sub	x3, x3, x1
	movk	w4, 0x30, lsl 16
	lsl	x3, x3, 2
	mov	w0, 0
	sub	x1, x3, x1
	add	x1, x3, x1, lsl 2
	ldr	x1, [x2, x1]
	str	w4, [x1, 84]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L554:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L531
	str	x0, [x22]
	b	.L530
	.p2align 3
.L553:
	ldr	x2, .LC210
	mov	w4, 0
	ldr	x1, .LC211
	mov	w3, w21
	add	x2, x2, 776
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L550
.L531:
	ldr	x1, .LC212
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L550
.L560:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L541
.L559:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L539
.L558:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L537
.L557:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L535
.L562:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L545
.L561:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L543
.L563:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L547
.L556:
	ldr	x2, .LC214
	sxtw	x1, w21
	b	.L533
	.size	VDMHAL_V5R2C1_CfgRpReg, .-VDMHAL_V5R2C1_CfgRpReg
	.align	3
.LC210:
	.xword	.LANCHOR0
	.align	3
.LC211:
	.xword	.LC89
	.align	3
.LC212:
	.xword	.LC122
	.align	3
.LC213:
	.xword	g_HalDisable
	.align	3
.LC214:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_MakeDecReport
	.type	VDMHAL_V5R2C1_MakeDecReport, %function
VDMHAL_V5R2C1_MakeDecReport:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L594
	ldr	x23, [x19, 8]
	ldr	w21, [x19]
	ldr	w22, [x19, 16]
	cbz	x23, .L595
	sxtw	x22, w22
	ldr	x20, .LC223
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x0, [x20, x0]
	cbz	x0, .L568
	ldr	x2, .LC224
	add	x0, x2, 4
	add	x2, x2, 128
	ldr	w1, [x2, -128]
	cmp	w1, 1
	bne	.L571
	b	.L583
	.p2align 3
.L597:
	cmp	x0, x2
	beq	.L596
.L571:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L597
.L583:
	mov	w19, w1
.L569:
	ldr	x3, .LC228
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
	ldr	x4, .LC229
	add	x2, x0, x3, lsl 2
	add	x2, x20, x2
	add	x1, x4, x1, lsl 2
	ldr	w0, [x2, 40]
	str	w0, [x23, 4]
	ldr	w1, [x1, 4]
	ubfx	x0, x1, 17, 2
	cmp	w0, 1
	beq	.L584
	and	w1, w1, 131072
	cmp	w1, wzr
	ccmp	w21, 3, 0, ne
	cset	w1, ne
.L572:
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
	beq	.L598
.L573:
	cmp	w2, 200
	bhi	.L599
.L575:
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	add	x20, x20, x0
	ldr	w21, [x20, 56]
	mov	w0, w21
	bl	MEM_Phy2Vir
	cbz	x0, .L600
	lsl	x3, x22, 2
	ldr	x19, .LC234
	sub	x3, x3, x22
	ldr	w2, [x23, 12]
	mov	x1, x0
	add	x20, x22, x3, lsl 3
	lsl	w2, w2, 2
	lsl	x24, x20, 7
	add	x0, x19, x24
	bl	VDMHAL_V5R2C1_ReadMsgSlot
	ldr	w1, [x19, x24]
	ldr	w0, [x23, 12]
	lsr	w1, w1, 31
	str	w1, [x23, 16]
	cbz	w0, .L580
	sub	w2, w0, #1
	mov	x5, 26
	add	x1, x23, 22
	mov	w0, 2
	add	x5, x5, x2, uxtw 2
	lsl	x3, x20, 5
	add	x5, x23, x5
	.p2align 2
.L579:
	sub	w2, w0, #1
	add	x4, x3, x0, uxtw
	add	x2, x3, x2
	add	w0, w0, 4
	ldr	w2, [x19, x2, lsl 2]
	strh	w2, [x1, -2]
	ldr	w2, [x19, x4, lsl 2]
	strh	w2, [x1], 4
	cmp	x5, x1
	bne	.L579
.L580:
	mov	w0, 6
	bl	IsDprintTypeEnable
	cbnz	w0, .L601
.L566:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L598:
	cmp	w19, 1
	beq	.L602
	ldr	x1, .LC230
	ldrb	w1, [x1]
	cbnz	w1, .L573
	ldrb	w0, [x0, 19]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L573
	mov	w0, 1
	strh	wzr, [x23, 20]
	str	w0, [x23, 12]
	mov	w0, 0
	strh	wzr, [x23, 22]
	b	.L566
	.p2align 3
.L596:
	mov	w19, 0
	b	.L569
	.p2align 3
.L601:
	ldr	x1, .LC236
	mov	w0, 6
	ldr	w2, [x23, 12]
	mov	w20, 0
	bl	dprint_vfmw
	mov	w2, w21
	ldr	x1, .LC238
	lsl	x21, x22, 2
	mov	w0, 6
	sub	x21, x21, x22
	bl	dprint_vfmw
	ldr	x24, .LC240
	add	x21, x22, x21, lsl 3
	lsl	x21, x21, 5
	.p2align 2
.L581:
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
	bhi	.L581
	ldr	x1, .LC242
	mov	w0, 6
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L584:
	mov	w1, 0
	b	.L572
	.p2align 3
.L599:
	ldr	x1, .LC232
	mov	w3, 200
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 12]
	b	.L575
	.p2align 3
.L602:
	ldr	w0, [x0, 16]
	ubfx	x0, x0, 21, 2
	cmp	w0, 2
	bne	.L573
	strh	wzr, [x23, 20]
	mov	w0, 0
	strh	wzr, [x23, 22]
	str	w19, [x23, 12]
	b	.L566
.L600:
	ldr	x2, .LC219
	ldr	x3, .LC233
	ldr	x1, .LC220
	add	x2, x2, 800
	bl	dprint_vfmw
	mov	w0, -1
	b	.L566
.L568:
	ldr	x2, .LC219
	ldr	x3, .LC225
.L592:
	ldr	x1, .LC220
	mov	w0, 0
	add	x2, x2, 800
	bl	dprint_vfmw
	mov	w0, -1
	b	.L566
.L595:
	ldr	x2, .LC219
	ldr	x3, .LC222
	b	.L592
.L594:
	ldr	x2, .LC219
	ldr	x3, .LC218
	b	.L592
	.size	VDMHAL_V5R2C1_MakeDecReport, .-VDMHAL_V5R2C1_MakeDecReport
	.align	3
.LC218:
	.xword	.LC217
	.align	3
.LC219:
	.xword	.LANCHOR0
	.align	3
.LC220:
	.xword	.LC7
	.align	3
.LC222:
	.xword	.LC221
	.align	3
.LC223:
	.xword	g_HwMem
	.align	3
.LC224:
	.xword	g_DSPState
	.align	3
.LC225:
	.xword	.LC160
	.align	3
.LC228:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC229:
	.xword	g_BackUp
	.align	3
.LC230:
	.xword	g_not_allow_H264FullPictureRepair_flag
	.align	3
.LC232:
	.xword	.LC231
	.align	3
.LC233:
	.xword	.LC188
	.align	3
.LC234:
	.xword	g_UpMsg
	.align	3
.LC236:
	.xword	.LC235
	.align	3
.LC238:
	.xword	.LC237
	.align	3
.LC240:
	.xword	.LC239
	.align	3
.LC242:
	.xword	.LC241
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_PrepareRepair
	.type	VDMHAL_V5R2C1_PrepareRepair, %function
VDMHAL_V5R2C1_PrepareRepair:
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
	mov	x23, x1
	mov	w27, w2
	mov	x24, x4
	bl	_mcount
	ldr	x25, .LC243
	lsl	x0, x19, 6
	cmp	w19, wzr
	sub	x0, x0, x19
	mov	x21, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	add	x26, x20, x25
	bgt	.L622
	ldr	x0, [x20, x25]
	cbz	x0, .L623
	cbz	w27, .L624
.L608:
	cmp	w27, 1
	mov	w0, 0
	beq	.L625
.L605:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L623:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L607
	str	x0, [x20, x25]
	cbnz	w27, .L608
	.p2align 2
.L624:
	lsl	x0, x19, 3
	ldr	x20, .LC248
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 3
	ldr	w1, [x0, 44]
	cmp	w1, wzr
	ble	.L609
	cmp	w22, 6
	beq	.L626
.L610:
	lsl	x2, x19, 3
	sub	x2, x2, x19
	lsl	x2, x2, 3
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x2, x2, x19
	lsl	x2, x2, 3
	add	x1, x20, x2
	ldr	w0, [x1, 28]
	ldr	w3, [x1, 64]
	lsl	w0, w0, w3
	cmp	w0, 1920
	bgt	.L612
	ldr	w0, [x1, 4]
	cmp	w0, 17
	beq	.L612
	mov	w0, 1
	strb	wzr, [x20, x2]
	strb	w0, [x1, 1]
	mov	x1, x23
	mov	w0, w22
	bl	VDMHAL_UpateDecParam.constprop.10
.L612:
	mov	x4, x24
	mov	w3, w21
	mov	x2, x23
	mov	x1, x26
	mov	w0, w22
	bl	VDMHAL_V5R2C1_CfgRpReg
	lsl	x0, x19, 3
	mov	w2, w21
	sub	x0, x0, x19
	mov	x1, x26
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 3
	bl	VDMHAL_V5R2C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L625:
	cmp	w22, 6
	bne	.L613
	ldrb	w0, [x23, 17]
	cmp	w0, 1
	bne	.L613
	lsl	x0, x19, 3
	ldr	x2, .LC248
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	lsl	x19, x19, 3
	add	x1, x2, x19
	ldr	w0, [x1, 920]
	cmp	w0, wzr
	ble	.L613
	ldr	w0, [x1, 28]
	add	x20, x19, 876
	ldr	w3, [x1, 64]
	add	x20, x20, x2
	lsl	w0, w0, w3
	cmp	w0, 1920
	mov	w0, 2
	str	w0, [x1, 928]
	bgt	.L614
	ldr	w0, [x1, 4]
	cmp	w0, 17
	beq	.L614
	strb	w27, [x1, 1]
	mov	w0, w22
	mov	x1, x23
	strb	wzr, [x2, x19]
	bl	VDMHAL_UpateDecParam.constprop.10
.L614:
	mov	x4, x24
	mov	w3, w21
	mov	x2, x23
	mov	x1, x26
	mov	w0, 6
	bl	VDMHAL_V5R2C1_CfgRpReg
	mov	w2, w21
	mov	x1, x26
	mov	x0, x20
	bl	VDMHAL_V5R2C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L626:
	ldrb	w1, [x23, 17]
	mov	w2, 0
	cmp	w1, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 928]
	b	.L610
	.p2align 3
.L622:
	ldr	x2, .LC244
	mov	w4, 0
	ldr	x1, .LC245
	mov	w3, w19
	add	x2, x2, 832
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L605
	.p2align 3
.L613:
	ldr	x1, .LC252
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L605
.L609:
	ldr	x1, .LC250
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L605
.L607:
	ldr	x1, .LC247
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L605
	.size	VDMHAL_V5R2C1_PrepareRepair, .-VDMHAL_V5R2C1_PrepareRepair
	.align	3
.LC243:
	.xword	g_HwMem
	.align	3
.LC244:
	.xword	.LANCHOR0
	.align	3
.LC245:
	.xword	.LC89
	.align	3
.LC247:
	.xword	.LC246
	.align	3
.LC248:
	.xword	g_RepairParam
	.align	3
.LC250:
	.xword	.LC249
	.align	3
.LC252:
	.xword	.LC251
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_StartHwRepair
	.type	VDMHAL_V5R2C1_StartHwRepair, %function
VDMHAL_V5R2C1_StartHwRepair:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC253
	ldrb	w4, [x21]
	cmp	w4, 1
	bne	.L651
	cmp	w20, wzr
	ble	.L652
	ldr	x22, .LC255
	mov	w3, w20
	ldr	x23, .LC256
	mov	w0, 32
	add	x2, x22, 864
	mov	x1, x23
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L635
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L648
.L630:
	cbz	x19, .L653
.L644:
	ldr	x1, .LC259
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
.L627:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L652:
	sxtw	x0, w20
	ldr	x3, .LC254
	lsl	x1, x0, 6
	mov	w4, 67108864
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x2, x1, x0
	add	x1, x1, x2, lsl 2
	ldr	x1, [x3, x1]
	str	w4, [x1, 8]
.L633:
	lsl	x1, x0, 6
	mov	w2, -2
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x3, x0]
	str	w2, [x0, 36]
.L631:
	ldr	x0, .LC260
	ldr	x0, [x0, 224]
	blr	x0
	cmp	w20, wzr
	ble	.L647
	ldr	x22, .LC255
	ldr	x23, .LC256
.L640:
	add	x22, x22, 880
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
	b	.L627
	.p2align 3
.L629:
	cmp	w20, wzr
	ble	.L645
	ldr	x22, .LC255
	ldr	x23, .LC256
.L635:
	mov	w4, 1
	mov	w3, w20
	add	x2, x22, 864
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	bne	.L630
.L648:
	ldr	x0, .LC260
	ldr	x0, [x0, 224]
	blr	x0
	b	.L640
	.p2align 3
.L651:
	mov	x0, x19
	mov	w3, 67108864
	mov	w2, 8
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L629
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L631
	cbnz	x19, .L644
.L653:
	ldr	x2, .LC255
	mov	x3, 0
	ldr	x1, .LC258
	mov	w0, 0
	add	x2, x2, 880
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L647:
	lsl	x0, x20, 6
	ldr	x1, .LC254
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
	b	.L627
.L645:
	ldr	x3, .LC254
	sxtw	x0, w20
	b	.L633
	.size	VDMHAL_V5R2C1_StartHwRepair, .-VDMHAL_V5R2C1_StartHwRepair
	.align	3
.LC253:
	.xword	g_HalDisable
	.align	3
.LC254:
	.xword	g_HwMem
	.align	3
.LC255:
	.xword	.LANCHOR0
	.align	3
.LC256:
	.xword	.LC103
	.align	3
.LC258:
	.xword	.LC257
	.align	3
.LC259:
	.xword	g_VdmDrvParam
	.align	3
.LC260:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CalVdhClkSkip
	.type	VDMHAL_V5R2C1_CalVdhClkSkip, %function
VDMHAL_V5R2C1_CalVdhClkSkip:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	bl	_mcount
	ldr	x24, .LC262
	ldr	w28, [x24, 128]
	tbnz	w28, #31, .L686
	ldr	x25, .LC265
	add	x20, x24, 132
	ldr	x27, .LC268
	add	x24, x24, 256
	ldr	x26, .LC267
	mov	w23, 30
	mov	w22, 0
	mov	w21, 0
	add	x25, x25, 912
	mov	w19, 0
	b	.L657
	.p2align 3
.L689:
	mov	w3, w28
	mov	x2, x25
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
.L659:
	cmp	x24, x20
	beq	.L687
.L676:
	ldr	w28, [x20], 4
	tbnz	w28, #31, .L688
.L657:
	mov	w0, w28
	bl	VCTRL_IsChanActive
	cbnz	w0, .L689
	mov	w0, w28
	bl	FSP_GetInst
	cbz	x0, .L660
	ldp	w1, w0, [x0, 40]
	adds	w19, w1, 15
	add	w1, w1, 30
	add	w21, w0, 30
	csel	w19, w1, w19, mi
	adds	w0, w0, 15
	asr	w19, w19, 4
	csel	w0, w21, w0, mi
	asr	w21, w0, 4
.L660:
	ldr	x1, [x27, w28, sxtw 3]
	mov	w0, w28
	ldr	w1, [x1, 1640]
	cmp	w1, 31
	csel	w23, w23, w1, lt
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	bls	.L690
.L679:
	cmp	x24, x20
	mov	w22, 0
	bne	.L676
.L687:
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
.L690:
	ldr	x1, .LC269
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx663
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx663:
	.section	.rodata
	.align	0
	.align	2
.L663:
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L679 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L679 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L679 - .Lrtx663) / 4
	.byte	(.L673 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.byte	(.L672 - .Lrtx663) / 4
	.text
	.p2align 3
.L672:
	mul	w22, w19, w21
	mul	w22, w22, w23
	b	.L659
	.p2align 3
.L688:
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
.L655:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L673:
	mul	w22, w19, w21
	mul	w22, w22, w23
	lsl	w22, w22, 1
	b	.L659
.L686:
	mov	w0, 25
	b	.L655
	.size	VDMHAL_V5R2C1_CalVdhClkSkip, .-VDMHAL_V5R2C1_CalVdhClkSkip
	.align	3
.LC262:
	.xword	g_ChanCtx
	.align	3
.LC265:
	.xword	.LANCHOR0
	.align	3
.LC267:
	.xword	.LC266
	.align	3
.LC268:
	.xword	s_pstVfmwChan
	.align	3
.LC269:
	.xword	.L663
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetVdmClk
	.type	VDMHAL_V5R2C1_GetVdmClk, %function
VDMHAL_V5R2C1_GetVdmClk:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 3
	bls	.L699
.L692:
	ldr	x0, .LC272
	sbfiz	x19, x19, 6, 32
	mov	w1, 500
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L699:
	ldr	x0, .LC271
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx694
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx694:
	.section	.rodata
	.align	0
	.align	2
.L694:
	.byte	(.L692 - .Lrtx694) / 4
	.byte	(.L695 - .Lrtx694) / 4
	.byte	(.L696 - .Lrtx694) / 4
	.byte	(.L697 - .Lrtx694) / 4
	.text
	.p2align 3
.L696:
	ldr	x0, .LC272
	sbfiz	x19, x19, 6, 32
	mov	w1, 100
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L695:
	ldr	x0, .LC272
	sbfiz	x19, x19, 6, 32
	mov	w1, 540
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L697:
	ldr	x0, .LC272
	sbfiz	x19, x19, 6, 32
	mov	w1, 600
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R2C1_GetVdmClk, .-VDMHAL_V5R2C1_GetVdmClk
	.align	3
.LC271:
	.xword	.L694
	.align	3
.LC272:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_StartHwDecode
	.type	VDMHAL_V5R2C1_StartHwDecode, %function
VDMHAL_V5R2C1_StartHwDecode:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, wzr
	bgt	.L749
	ldr	x25, .LC275
	sxtw	x21, w20
	ldr	x24, .LC276
	mov	w26, 0
	add	x0, x25, x21, lsl 6
	ldr	w23, [x0, 8]
	ldr	x0, [x24, w23, sxtw 3]
	ldr	w1, [x0, 1628]
	cmp	w1, 1
	beq	.L750
.L703:
	ldr	x22, .LC280
	ldrb	w0, [x22]
	cmp	w0, 1
	bne	.L751
	ldr	x1, .LC281
	ldr	x2, [x1]
	ldr	w1, [x2, 120]
	ubfx	x3, x1, 8, 2
	cmp	w26, w3
	beq	.L742
	bfi	w1, w26, 8, 2
	str	w1, [x2, 120]
.L742:
	ldr	x1, .LC282
	ldrh	w1, [x1,w26,uxtw #1]
	adr	x2, .Lrtx711
	add	x1, x2, w1, sxth #2
	br	x1
.Lrtx711:
	.section	.rodata
	.align	0
	.align	2
.L711:
	.2byte	(.L710 - .Lrtx711) / 4
	.2byte	(.L712 - .Lrtx711) / 4
	.2byte	(.L713 - .Lrtx711) / 4
	.2byte	(.L714 - .Lrtx711) / 4
	.text
	.p2align 3
.L751:
	mov	x0, x19
	mov	w3, w26
	mov	w2, 0
	mov	w1, 0
	bl	VDH_Record_RegData
	ldrb	w0, [x22]
	b	.L742
	.p2align 3
.L749:
	ldr	x2, .LC273
	mov	w4, 0
	ldr	x1, .LC274
	mov	w3, w20
	add	x2, x2, 944
	mov	w0, 0
	bl	dprint_vfmw
.L700:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L750:
	ldr	w0, [x0, 632]
	cmp	w0, 17
	bne	.L703
	ldr	x0, .LC277
	ldr	x0, [x0, w23, sxtw 3]
	ldr	w1, [x0, 40]
	cmp	w1, 3839
	bgt	.L704
	ldr	w0, [x0, 44]
	cmp	w0, 2159
	ble	.L703
.L704:
	ldr	x2, .LC278
	mov	w0, 12320
	mov	w1, 65536
	movk	w0, 0xf8a2, lsl 16
	ldr	x2, [x2, 304]
	blr	x2
	ldr	x1, .LC279
	ldr	x1, [x1]
	ldr	w1, [x1, 196]
	lsr	w1, w1, 24
	cmp	w1, 3
	beq	.L735
	cmp	w1, 2
	beq	.L736
	mov	w2, 221
	mov	w3, 221
	movk	w2, 0x71, lsl 16
	movk	w3, 0x89, lsl 16
	cmp	w1, 1
	csel	w1, w2, w3, ne
.L705:
	mov	w26, 2
	str	w1, [x0]
	b	.L703
	.p2align 3
.L713:
	add	x1, x25, x21, lsl 6
	mov	w2, 100
	str	w2, [x1, 16]
.L715:
	ldr	x1, [x24, w23, sxtw 3]
	cmp	w0, 1
	ldr	w24, [x1, 1312]
	bne	.L752
.L716:
	ldr	x0, .LC281
	mov	x3, x19
	mov	w2, w20
	ldr	x0, [x0]
	ldr	w1, [x0, 120]
	and	w1, w1, -258049
	str	w1, [x0, 120]
	ldr	w1, [x0, 120]
	orr	w1, w1, 131072
	str	w1, [x0, 120]
	mov	w0, 12
	mov	w1, 3
	bl	SCD_ConfigReg
	ldrb	w0, [x22]
	cmp	w0, 1
	beq	.L753
.L728:
	mov	w1, 2
	mov	x0, x19
	mov	w3, -1431655766
	mov	w2, 156
	bl	VDH_Record_RegData
	ldr	x1, .LC283
	ldrb	w0, [x22]
	ldr	w1, [x1]
	cmp	w1, 1
	beq	.L754
.L719:
	mov	w3, 0
.L718:
	cmp	w0, 1
	beq	.L755
	mov	x0, x19
	mov	w2, 61472
	mov	w1, 2
	bl	VDH_Record_RegData
	cmp	w24, 1
	ldrb	w0, [x22]
	beq	.L756
.L722:
	mov	w3, -2
.L721:
	cmp	w0, 1
	beq	.L757
	mov	x0, x19
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x22]
	cmp	w0, 1
	beq	.L758
	cbz	x19, .L759
	mov	w0, 1
	strb	w20, [x19]
	stp	w0, w23, [x19, 4]
	mov	x0, x19
	bl	VDH_PostTask
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L756:
	mov	w3, -6
	b	.L721
	.p2align 3
.L754:
	mov	w3, 15
	b	.L718
	.p2align 3
.L712:
	add	x1, x25, x21, lsl 6
	mov	w2, 540
	cmp	w0, 1
	str	w2, [x1, 16]
	ldr	x1, [x24, w23, sxtw 3]
	ldr	w24, [x1, 1312]
	beq	.L716
.L752:
	mov	w3, 0
	mov	w2, 1
	mov	w1, 0
	mov	x0, x19
	bl	VDH_Record_RegData
	mov	w0, 12
	mov	x3, x19
	mov	w2, w20
	mov	w1, 3
	bl	SCD_ConfigReg
	ldrb	w0, [x22]
	cmp	w0, 1
	bne	.L728
.L753:
	ldr	x2, .LC283
	lsl	x1, x21, 6
	sub	x1, x1, x21
	ldr	x26, .LC284
	lsl	x1, x1, 2
	ldr	w2, [x2]
	cmp	w2, 1
	sub	x2, x1, x21
	add	x1, x1, x2, lsl 2
	mov	w2, -1431655766
	ldr	x1, [x26, x1]
	str	w2, [x1, 156]
	bne	.L719
	mov	w3, 15
	b	.L720
	.p2align 3
.L710:
	add	x1, x25, x21, lsl 6
	mov	w2, 500
	str	w2, [x1, 16]
	b	.L715
	.p2align 3
.L714:
	add	x1, x25, x21, lsl 6
	mov	w2, 600
	str	w2, [x1, 16]
	b	.L715
	.p2align 3
.L755:
	ldr	x26, .LC284
.L720:
	lsl	x0, x21, 6
	cmp	w24, 1
	sub	x0, x0, x21
	lsl	x0, x0, 2
	sub	x1, x0, x21
	add	x0, x0, x1, lsl 2
	ldr	x0, [x26, x0]
	add	x0, x0, 61440
	str	w3, [x0, 32]
	beq	.L741
	mov	w0, 1
	b	.L722
	.p2align 3
.L757:
	ldr	x26, .LC284
.L723:
	lsl	x1, x21, 6
	ldr	x19, .LC278
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
.L726:
	lsl	x0, x21, 6
	mov	w2, 1
	sub	x1, x0, x21
	add	x25, x25, x0
	lsl	x0, x1, 2
	ldr	x3, .LC286
	sub	x21, x0, x21
	mov	w1, 4
	add	x21, x0, x21, lsl 2
	ldr	x0, [x26, x21]
	str	wzr, [x0]
	ldr	x0, [x26, x21]
	str	w2, [x0]
	ldr	x0, [x26, x21]
	str	wzr, [x0]
	ldr	w2, [x25, 8]
	mov	w0, w2
	ldr	w2, [x3, w2, sxtw 2]
	bl	VDEC_Lowdelay_Event_Time
	b	.L700
	.p2align 3
.L759:
	ldr	x2, .LC273
	mov	x3, 0
	ldr	x1, .LC285
	mov	w0, 0
	add	x2, x2, 944
	bl	dprint_vfmw
	b	.L700
	.p2align 3
.L741:
	mov	w3, -6
	b	.L723
.L735:
	mov	w1, 221
	movk	w1, 0x71, lsl 16
	b	.L705
.L736:
	mov	w1, 221
	movk	w1, 0x7d, lsl 16
	b	.L705
.L758:
	ldr	x19, .LC278
	mov	x0, 30
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
	ldr	x26, .LC284
	b	.L726
	.size	VDMHAL_V5R2C1_StartHwDecode, .-VDMHAL_V5R2C1_StartHwDecode
	.align	3
.LC273:
	.xword	.LANCHOR0
	.align	3
.LC274:
	.xword	.LC89
	.align	3
.LC275:
	.xword	g_VdmDrvParam
	.align	3
.LC276:
	.xword	s_pstVfmwChan
	.align	3
.LC277:
	.xword	s_pFspInst
	.align	3
.LC278:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC279:
	.xword	g_pstRegSysCtrl
	.align	3
.LC280:
	.xword	g_HalDisable
	.align	3
.LC281:
	.xword	g_pstRegCrg
	.align	3
.LC282:
	.xword	.L711
	.align	3
.LC283:
	.xword	mask_mmu_err_int
	.align	3
.LC284:
	.xword	g_HwMem
	.align	3
.LC285:
	.xword	.LC257
	.align	3
.LC286:
	.xword	g_LowDelaySeqIndex
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetCharacter
	.type	VDMHAL_V5R2C1_GetCharacter, %function
VDMHAL_V5R2C1_GetCharacter:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC287
	mov	w3, 15
	ldr	x0, .LC288
	mov	w1, 4
	str	w3, [x2]
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_GetCharacter, .-VDMHAL_V5R2C1_GetCharacter
	.align	3
.LC287:
	.xword	g_VdmCharacter
	.align	3
.LC288:
	.xword	g_eVdmVersion
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_WriteBigTitle1DYuv
	.type	VDMHAL_V5R2C1_WriteBigTitle1DYuv, %function
VDMHAL_V5R2C1_WriteBigTitle1DYuv:
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
	beq	.L805
	mov	w20, 2
	cmp	w0, w20
	csinc	w20, w20, wzr, ne
.L762:
	ldr	x0, [x29, 112]
	cbz	x0, .L761
	ldr	x0, .LC290
	mov	w4, 0
	add	x3, x29, 144
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L765
	ldr	x0, .LC294
	mov	w4, 0
	add	x3, x29, 176
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L765
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
	bne	.L766
	lsr	w1, w3, 1
	lsr	w0, w19, 1
	str	w1, [x29, 120]
	add	x1, x25, 2097152
	str	w0, [x29, 104]
	str	x1, [x29, 136]
	ldr	x28, .LC295
	ldr	x20, [x29, 152]
	cbz	w3, .L768
	mov	w27, 0
	str	wzr, [x29, 132]
	.p2align 2
.L767:
	cbz	w19, .L770
	ldr	w0, [x29, 124]
	lsr	w23, w27, 4
	ldr	w24, [x29, 132]
	mov	w26, 0
	mul	w0, w23, w0
	ubfiz	x23, x27, 8, 4
	add	x23, x0, x23
	.p2align 2
.L769:
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
	bhi	.L769
.L770:
	ldr	w0, [x29, 132]
	add	w27, w27, 1
	add	w0, w0, w19
	str	w0, [x29, 132]
	ldr	w0, [x29, 128]
	cmp	w0, w27
	bne	.L767
.L768:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	blr	x3
	ldr	w0, [x29, 120]
	cbz	w0, .L860
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 132]
	.p2align 2
.L774:
	cbz	w19, .L776
	ldr	w0, [x29, 132]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L773:
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
	bhi	.L773
.L776:
	ldr	w0, [x29, 120]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L774
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L861
.L802:
	ldr	w0, [x29, 108]
	cbnz	w0, .L779
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
.L779:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 120]
.L855:
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
.L761:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L765:
	ldr	x1, .LC292
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
.L805:
	mov	w20, 0
	b	.L762
.L766:
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
	ldr	x28, .LC295
	ldr	x20, [x29, 152]
	bls	.L784
	ldr	w27, [x29, 120]
	.p2align 2
.L786:
	cbz	w19, .L787
	ldr	w0, [x29, 124]
	lsr	w24, w27, 4
	lsr	w23, w27, 1
	mov	w26, 0
	mul	w0, w24, w0
	mul	w23, w23, w19
	ubfiz	x24, x27, 8, 4
	add	x24, x0, x24
	.p2align 2
.L785:
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
	bhi	.L785
.L787:
	ldr	w0, [x29, 128]
	add	w27, w27, 2
	cmp	w0, w27
	bhi	.L786
.L784:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	lsr	w1, w1, 1
	blr	x3
	ldr	w0, [x29, 132]
	cbz	w0, .L862
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 128]
	.p2align 2
.L791:
	cbz	w19, .L793
	ldr	w0, [x29, 128]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L790:
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
	bhi	.L790
.L793:
	ldr	w0, [x29, 132]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L791
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L863
	ldr	w0, [x29, 108]
	cbnz	w0, .L796
	ldr	w1, [x29, 120]
	ldr	w0, [x29, 132]
	cmp	w0, w1
	bls	.L799
	.p2align 2
.L800:
	ldr	w0, [x29, 120]
	ldr	w1, [x29, 132]
	add	w0, w0, 2
	str	w0, [x29, 120]
	cmp	w1, w0
	bhi	.L800
.L799:
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
.L796:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 132]
	b	.L855
.L861:
	mov	w0, 0
	mov	w6, 0
	.p2align 2
.L778:
	ldr	w1, [x29, 104]
	mov	w5, w0
	cbz	w1, .L780
	ldr	w1, [x29, 104]
	add	w5, w1, w0
	mov	w1, 1
	.p2align 2
.L777:
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
	bne	.L777
.L780:
	ldr	w0, [x29, 120]
	add	w6, w6, 1
	add	x20, x20, x19
	cmp	w0, w6
	mov	w0, w5
	bne	.L778
	b	.L779
.L863:
	ldr	w0, [x29, 120]
	mov	w7, 0
	mul	w1, w19, w0
	lsl	w0, w19, 1
	add	x20, x20, x1
	.p2align 2
.L795:
	ldr	w3, [x29, 104]
	cbz	w3, .L797
	lsr	w1, w7, 1
	mov	w2, 1
	mul	w1, w1, w3
	add	w6, w3, w1
	.p2align 2
.L794:
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
	bne	.L794
.L797:
	ldr	w1, [x29, 132]
	add	w7, w7, 2
	add	x20, x20, x0
	cmp	w1, w7
	bhi	.L795
	b	.L796
.L862:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L796
	ldr	w0, [x29, 108]
	cbz	w0, .L799
	b	.L796
.L860:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	bne	.L802
	b	.L779
	.size	VDMHAL_V5R2C1_WriteBigTitle1DYuv, .-VDMHAL_V5R2C1_WriteBigTitle1DYuv
	.align	3
.LC290:
	.xword	.LC289
	.align	3
.LC292:
	.xword	.LC291
	.align	3
.LC294:
	.xword	.LC293
	.align	3
.LC295:
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
	ldr	x0, .LC296
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L871
	cbnz	w19, .L867
	ldr	x0, .LC297
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	ubfx	x2, x0, 8, 2
	cmp	w20, w2
	beq	.L864
	bfi	w0, w20, 8, 2
	str	w0, [x1, 120]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L867:
	cmp	w19, 1
	beq	.L872
.L864:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L871:
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
.L872:
	ldr	x0, .LC297
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	bfi	w0, w20, 12, 5
	and	w0, w0, -131073
	str	w0, [x1, 120]
	ldr	w0, [x1, 120]
	orr	w0, w0, 131072
	str	w0, [x1, 120]
	b	.L864
	.size	CRG_ConfigReg, .-CRG_ConfigReg
	.align	3
.LC296:
	.xword	g_HalDisable
	.align	3
.LC297:
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
	ldr	x0, .LC298
	ldrb	w4, [x0]
	cmp	w4, 1
	bne	.L877
	cmp	w19, wzr
	ble	.L878
	ldr	x2, .LC300
	mov	w3, w19
	ldr	x1, .LC301
	mov	w0, 32
	add	x2, x2, 864
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L878:
	lsl	x0, x19, 6
	ldr	x1, .LC299
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
.L877:
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
.LC298:
	.xword	g_HalDisable
	.align	3
.LC299:
	.xword	g_HwMem
	.align	3
.LC300:
	.xword	.LANCHOR0
	.align	3
.LC301:
	.xword	.LC103
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.52379, %object
	.size	__func__.52379, 22
__func__.52379:
	.string	"VDMHAL_V5R2C1_OpenHAL"
	.zero	2
	.type	__func__.52453, %object
	.size	__func__.52453, 25
__func__.52453:
	.string	"VDMHAL_V5R2C1_CalcFsSize"
	.zero	7
	.type	__func__.52479, %object
	.size	__func__.52479, 24
__func__.52479:
	.string	"VDMHAL_V5R2C1_CalcFsNum"
	.type	__func__.52522, %object
	.size	__func__.52522, 32
__func__.52522:
	.string	"VDMHAL_V5R2C1_ArrangeMem_Normal"
	.type	__FUNCTION__.52523, %object
	.size	__FUNCTION__.52523, 32
__FUNCTION__.52523:
	.string	"VDMHAL_V5R2C1_ArrangeMem_Normal"
	.type	__func__.52465, %object
	.size	__func__.52465, 33
__func__.52465:
	.string	"VDMHAL_V5R2C1_FillMemArrangeInfo"
	.zero	7
	.type	__func__.52605, %object
	.size	__func__.52605, 34
__func__.52605:
	.string	"VDMHAL_V5R2C1_ArrangeMem_Specific"
	.zero	6
	.type	__func__.52629, %object
	.size	__func__.52629, 23
__func__.52629:
	.string	"VDMHAL_V5R2C1_ResetVdm"
	.zero	1
	.type	__func__.52639, %object
	.size	__func__.52639, 35
__func__.52639:
	.string	"VDMHAL_V5R2C1_SetSmmuPageTableAddr"
	.zero	5
	.type	__func__.52663, %object
	.size	__func__.52663, 24
__func__.52663:
	.string	"VDMHAL_V5R2C1_GlbResetX"
	.type	__func__.52649, %object
	.size	__func__.52649, 23
__func__.52649:
	.string	"VDMHAL_V5R2C1_GlbReset"
	.zero	1
	.type	__func__.52672, %object
	.size	__func__.52672, 28
__func__.52672:
	.string	"VDMHAL_V5R2C1_ClearIntState"
	.zero	4
	.type	__func__.52678, %object
	.size	__func__.52678, 31
__func__.52678:
	.string	"VDMHAL_V5R2C1_ClearMMUIntState"
	.zero	1
	.type	__func__.52684, %object
	.size	__func__.52684, 22
__func__.52684:
	.string	"VDMHAL_V5R2C1_MaskInt"
	.zero	2
	.type	__func__.52697, %object
	.size	__func__.52697, 24
__func__.52697:
	.string	"VDMHAL_V5R2C1_EnableInt"
	.type	__func__.52706, %object
	.size	__func__.52706, 23
__func__.52706:
	.string	"VDMHAL_V5R2C1_CheckReg"
	.zero	1
	.type	__func__.52720, %object
	.size	__func__.52720, 26
__func__.52720:
	.string	"VDMHAL_V5R2C1_ReadMMUMask"
	.zero	6
	.type	__func__.52725, %object
	.size	__func__.52725, 27
__func__.52725:
	.string	"VDMHAL_V5R2C1_WriteMMUMask"
	.zero	5
	.type	__func__.52756, %object
	.size	__func__.52756, 25
__func__.52756:
	.string	"VDMHAL_V5R2C1_PrepareDec"
	.zero	7
	.type	__func__.52761, %object
	.size	__func__.52761, 25
__func__.52761:
	.string	"VDMHAL_V5R2C1_IsVdmReady"
	.zero	7
	.type	__func__.52766, %object
	.size	__func__.52766, 23
__func__.52766:
	.string	"VDMHAL_V5R2C1_IsVdmRun"
	.zero	1
	.type	__func__.52772, %object
	.size	__func__.52772, 27
__func__.52772:
	.string	"VDMHAL_V5R2C1_IsVdhDecOver"
	.zero	5
	.type	__func__.52782, %object
	.size	__func__.52782, 31
__func__.52782:
	.string	"VDMHAL_V5R2C1_IsVdhPartDecOver"
	.zero	1
	.type	__func__.52797, %object
	.size	__func__.52797, 33
__func__.52797:
	.string	"VDMHAL_V5R2C1_UpdateHardwareInfo"
	.zero	7
	.type	__func__.52870, %object
	.size	__func__.52870, 23
__func__.52870:
	.string	"VDMHAL_V5R2C1_CfgRpMsg"
	.zero	1
	.type	__func__.52847, %object
	.size	__func__.52847, 24
__func__.52847:
	.string	"VDMHAL_CfgNotFullRepair"
	.type	__func__.52881, %object
	.size	__func__.52881, 23
__func__.52881:
	.string	"VDMHAL_V5R2C1_CfgRpReg"
	.zero	1
	.type	__func__.52894, %object
	.size	__func__.52894, 28
__func__.52894:
	.string	"VDMHAL_V5R2C1_MakeDecReport"
	.zero	4
	.type	__func__.52963, %object
	.size	__func__.52963, 28
__func__.52963:
	.string	"VDMHAL_V5R2C1_PrepareRepair"
	.zero	4
	.type	__func__.53153, %object
	.size	__func__.53153, 15
__func__.53153:
	.string	"MFDE_ConfigReg"
	.zero	1
	.type	__func__.52970, %object
	.size	__func__.52970, 28
__func__.52970:
	.string	"VDMHAL_V5R2C1_StartHwRepair"
	.zero	4
	.type	__func__.53009, %object
	.size	__func__.53009, 28
__func__.53009:
	.string	"VDMHAL_V5R2C1_CalVdhClkSkip"
	.zero	4
	.type	__func__.53035, %object
	.size	__func__.53035, 28
__func__.53035:
	.string	"VDMHAL_V5R2C1_StartHwDecode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC4:
	ASCII(.string	"pOpenParam = NULL error!" )
	.zero	7
.LC7:
	ASCII(.string	"%s: %s\n" )
.LC9:
	ASCII(.string	"MemBaseAddr = 0 error!" )
	.zero	1
.LC11:
	ASCII(.string	"VDMHAL_V5R2C1_OpenHAL: Size error!" )
	.zero	5
.LC13:
	ASCII(.string	"VdhId is wrong!!!\n" )
	.zero	5
.LC17:
	ASCII(.string	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\n" )
	.zero	7
.LC19:
	ASCII(.string	"BPDRegVirAddr %p\n" )
	.zero	6
.LC21:
	ASCII(.string	"!!!!!! HAL memory not enouph! need %d, have %d\n" )
.LC23:
	ASCII(.string	"image size out of range" )
.LC30:
	ASCII(.string	"VDMHAL ArrangeMem HEVC/VP9 10 bit\n" )
	.zero	5
.LC33:
	ASCII(.string	"%s pstVfmwFrameSizeInfo = NULL\n" )
.LC37:
	ASCII(.string	"DelAllFrameMemRecord err in VDMHAL_V5R2C1_ArrangeMem!\n" )
	.zero	1
.LC39:
	ASCII(.string	"Report arrange frame buffer: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	3
.LC44:
	ASCII(.string	"Report arrange frame buffer only: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	6
.LC47:
	ASCII(.string	"VidStd Invalid" )
	.zero	1
.LC53:
	ASCII(.string	"Set CompressEn %d, LossCompressEn %d, YCompRatio %d, UVCompRatio %d\n" )
	.zero	3
.LC55:
	ASCII(.string	"VDMHAL_V5R2C1_CalcFsSize err!\n" )
	.zero	1
.LC57:
	ASCII(.string	"%s, need arrange, Size: %#x, Num: %#x, RefChanged: %#x\n" )
.LC59:
	ASCII(.string	"DFS, report event. Size: 0x%x, Num: %d, RefChanged: %d\n" )
.LC62:
	ASCII(.string	"pVdmMemArrange is NULL" )
	.zero	1
.LC64:
	ASCII(.string	"DFS, no ref frame!\n" )
	.zero	4
.LC66:
	ASCII(.string	"DFS, Frame number = %d > 30, Then, Frame num = 30, \n" )
	.zero	3
.LC68:
	ASCII(.string	"VDMHAL_V5R2C1_ArrangeMem Mem addr is NULL" )
	.zero	6
.LC73:
	ASCII(.string	"'pVdmMemArrange' is NULL" )
	.zero	7
.LC77:
	ASCII(.string	"MemSize not enough for pmv slot" )
.LC80:
	ASCII(.string	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight failed!\n" )
	.zero	3
.LC82:
	ASCII(.string	"ImgSlotLen > ChanSlotLen" )
	.zero	7
.LC84:
	ASCII(.string	"cann't allocate img slot" )
	.zero	7
.LC89:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC91:
	ASCII(.string	"VDMHAL_V5R2C1_ResetVdm: map vdm register fail, vir(reg) = (%p)\n" )
.LC96:
	ASCII(.string	"%s module id %d failed!\n" )
	.zero	7
.LC98:
	ASCII(.string	"%s module id %d success!\n" )
	.zero	6
.LC103:
	ASCII(.string	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC110:
	ASCII(.string	"%s VdhId %d failed!\n" )
	.zero	3
.LC112:
	ASCII(.string	"%s VdhId %d success!\n" )
	.zero	2
.LC115:
	ASCII(.string	"%s: map vdm register 0x%x failed!\n" )
	.zero	5
.LC122:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC139:
	ASCII(.string	"%s: VdhId(%d) Invalid!\n" )
.LC142:
	ASCII(.string	"%s: vdm register virtual address not mapped, reset failed!\n" )
	.zero	4
.LC144:
	ASCII(.string	"%s: unkown reg_id = %d\n" )
.LC149:
	ASCII(.string	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC155:
	ASCII(.string	"%s: pDecParam(%p) = NULL\n" )
	.zero	6
.LC160:
	ASCII(.string	"VDM register not mapped yet!" )
	.zero	3
.LC166:
	ASCII(.string	"VDM register not mapped yet!\n" )
	.zero	2
.LC188:
	ASCII(.string	"can NOT map vir addr for up-msg" )
.LC192:
	ASCII(.string	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\n" )
	.zero	1
.LC194:
	ASCII(.string	"ReadUpMsgSlot error! upmsg_size(%d) > 512\n" )
	.zero	5
.LC197:
	ASCII(.string	"WriteMsgSlot error!\n" )
	.zero	3
.LC200:
	ASCII(.string	"can not map repair msg virtual address!" )
.LC204:
	ASCII(.string	"ValidGroupNum=%d out of range!\n" )
.LC206:
	ASCII(.string	"align_mb error\n" )
.LC208:
	ASCII(.string	"[%s][%d]sclie_num is wrong! %d \n" )
	.zero	7
.LC217:
	ASCII(.string	"'pMakeDecReport' is NULL" )
	.zero	7
.LC221:
	ASCII(.string	"'pDecReport' is NULL" )
	.zero	3
.LC231:
	ASCII(.string	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full repair.\n" )
	.zero	3
.LC235:
	ASCII(.string	"\n***** UpMsg DecSliceNum=%d\n" )
	.zero	3
.LC237:
	ASCII(.string	"\n***** Up Msg (phy addr: %#8x) *****\n" )
	.zero	2
.LC239:
	ASCII(.string	"\n0x%02x 0x%08x 0x%08x 0x%08x 0x%08x\n" )
	.zero	3
.LC241:
	ASCII(.string	"\n***** Up Msg print finished *****\n" )
	.zero	4
.LC246:
	ASCII(.string	"vdm register virtual address not mapped, VDMHAL_V200R003_PrepareRepair failed!\n" )
.LC249:
	ASCII(.string	"FIRST_REPAIR Parameter Error!\n" )
	.zero	1
.LC251:
	ASCII(.string	"SECOND_REPAIR Parameter Error!\n" )
.LC257:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC266:
	ASCII(.string	"%s The channel %d is not active\n" )
	.zero	7
.LC289:
	ASCII(.string	"BigTile1d_y" )
	.zero	4
.LC291:
	ASCII(.string	"failed mem_allocMemBlock BigTile_yuv save!\n" )
	.zero	4
.LC293:
	ASCII(.string	"BigTile1d_uv" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
