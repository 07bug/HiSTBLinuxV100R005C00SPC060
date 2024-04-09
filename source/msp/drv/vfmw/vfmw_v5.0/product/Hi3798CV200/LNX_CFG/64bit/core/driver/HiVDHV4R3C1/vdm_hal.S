#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetHalMemSize
	.type	VDMHAL_V4R3C1_GetHalMemSize, %function
VDMHAL_V4R3C1_GetHalMemSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 6291456
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_GetHalMemSize, .-VDMHAL_V4R3C1_GetHalMemSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_OpenHAL
	.type	VDMHAL_V4R3C1_OpenHAL, %function
VDMHAL_V4R3C1_OpenHAL:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L15
	ldp	w23, w22, [x19]
	ldr	w19, [x19, 8]
	cbz	w23, .L16
	mov	w0, 6291455
	cmp	w22, w0
	ble	.L17
	cmp	w19, wzr
	bgt	.L18
	sxtw	x20, w19
	ldr	x25, .LC14
	ldr	x21, .LC15
	mov	x2, 268
	add	x0, x20, x20, lsl 4
	mov	w1, 0
	lsl	x0, x0, 2
	ldr	x3, [x25, 96]
	sub	x0, x0, x20
	add	x0, x21, x0, lsl 2
	blr	x3
	ldr	x24, .LC0
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
	ldr	x1, .LC17
	str	x0, [x24, x25]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 53248
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_Phy2Vir
	mov	x2, x0
	ldr	x1, .LC19
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
.L8:
	str	w1, [x0], 4
	add	w1, w1, 1280
	cmp	x0, x2
	bne	.L8
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
	bcc	.L9
	mov	x0, x21
	bl	H264HAL_V4R3C1_InitHal
	cmp	w0, wzr
	mov	x0, x21
	csetm	w19, ne
	bl	HEVCHAL_V4R3C1_InitHal
	cmp	w0, wzr
	csinv	w19, w19, wzr, eq
.L4:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L18:
	ldr	x1, .LC13
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
.L9:
	ldr	x1, .LC21
	mov	w3, w22
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L4
.L16:
	ldr	x3, .LC9
.L13:
	ldr	x2, .LC5
	mov	w0, 0
	ldr	x1, .LC7
	mov	w19, -1
	bl	dprint_vfmw
	b	.L4
.L17:
	ldr	x3, .LC11
	b	.L13
.L15:
	ldr	x3, .LC4
	b	.L13
	.size	VDMHAL_V4R3C1_OpenHAL, .-VDMHAL_V4R3C1_OpenHAL
	.align	3
.LC0:
	.xword	g_HwMem
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC5:
	.xword	.LANCHOR0
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC9:
	.xword	.LC8
	.align	3
.LC11:
	.xword	.LC10
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC14:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC15:
	.xword	g_VdmExtParam
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
	.align	3
.LC21:
	.xword	.LC20
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CloseHAL
	.type	VDMHAL_V4R3C1_CloseHAL, %function
VDMHAL_V4R3C1_CloseHAL:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_CloseHAL, .-VDMHAL_V4R3C1_CloseHAL
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CalcFsSize
	.type	VDMHAL_V4R3C1_CalcFsSize, %function
VDMHAL_V4R3C1_CalcFsSize:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w23, w0
	mov	x0, x30
	mov	w27, w1
	mov	w28, w2
	mov	w24, w3
	mov	w25, w4
	mov	x22, x5
	bl	_mcount
	sub	w1, w27, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L21
	sub	w1, w28, #32
	mov	w21, w28
	cmp	w1, w0
	bhi	.L21
	add	w0, w27, 15
	add	w20, w28, 15
	asr	w0, w0, 4
	ldr	x1, .LC26
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
	cmp	w25, 16
	beq	.L26
	cmp	w25, 17
	beq	.L47
	mul	w19, w0, w19
	ldr	x4, .LC28
	add	w3, w3, 255
	add	w21, w28, 31
	and	w26, w3, -256
	mul	w19, w19, w20
	ldr	x5, [x4, w23, sxtw 3]
	and	w21, w21, -32
	add	w19, w19, 143
	mov	w6, 0
	and	w19, w19, -128
	mov	w7, 0
	asr	w3, w19, 1
.L37:
	ldr	w0, [x5, 1280]
	cmp	w0, 1
	beq	.L48
.L41:
	cmp	w24, 1
	mov	w28, 0
	mov	w8, 0
	mov	w27, 0
	mul	w21, w21, w26
	beq	.L49
.L30:
	mul	w2, w6, w7
	lsl	w1, w27, 2
	lsl	w0, w2, 2
	sub	w1, w1, w27
	sub	w2, w0, w2
	lsl	w0, w21, 2
	sub	w0, w0, w21
	lsr	w0, w0, 1
	add	w0, w0, w2, lsr 1
	add	w20, w0, w1, lsr 1
.L31:
	add	x2, x5, 307200
	ldr	w0, [x2, 1496]
	cbz	w0, .L50
	add	x0, x5, 311296
	cmp	w25, 17
	str	w20, [x0, 968]
	str	w3, [x2, 3884]
	lsl	w3, w26, 4
	str	w8, [x2, 3844]
	str	w28, [x2, 3848]
	beq	.L33
.L52:
	ldr	w0, [x2, 1504]
	mov	w1, 32
	str	w3, [x2, 3836]
	lsr	w3, w3, 1
	cmp	w0, 32
	str	w3, [x2, 3840]
	csel	w0, w0, w1, le
	cmp	w25, 16
	str	w0, [x2, 3888]
	add	w0, w21, w27
	str	w0, [x2, 3868]
	beq	.L51
.L35:
	ldr	x0, [x4, w23, sxtw 3]
	mov	w5, 1024
	add	w1, w20, 1056
	add	x3, x0, 311296
	add	w2, w1, w19
	add	w6, w2, w5
	str	w19, [x3, 972]
	str	w5, [x3, 980]
	ldrsb	w0, [x0, 44]
	cmp	w0, 1
	csel	w2, w6, w2, eq
	cbz	x22, .L42
	str	w1, [x22, 4]
	mov	w0, 0
	ldr	x3, [x4, w23, sxtw 3]
	add	x3, x3, 307200
	ldr	w3, [x3, 1504]
	stp	w3, w19, [x22, 8]
	ldr	x3, [x4, w23, sxtw 3]
	add	x3, x3, 307200
	ldr	w3, [x3, 3888]
	stp	w3, w5, [x22, 16]
	str	w2, [x22]
	ldr	x2, [x4, w23, sxtw 3]
	add	x2, x2, 311296
	str	w1, [x2, 976]
.L43:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L51:
	ldr	w0, [x5, 1612]
	cmp	w0, 8
	ble	.L35
	lsl	w0, w21, 2
	ldr	x1, .LC30
	sub	w21, w0, w21
	lsl	w0, w27, 2
	sub	w27, w0, w27
	mov	w0, 31
	mul	w6, w6, w7
	lsr	w27, w27, 1
	lsl	w7, w7, 5
	add	w21, w27, w21, lsr 1
	str	w7, [x2, 3852]
	str	w21, [x2, 3860]
	str	w6, [x2, 3864]
	str	x4, [x29, 120]
	bl	dprint_vfmw
	ldr	x4, [x29, 120]
	b	.L35
	.p2align 3
.L50:
	ldr	x1, .LC27
	add	x0, x2, 3832
	mov	x2, 1248
	str	x4, [x29, 96]
	stp	w8, w7, [x29, 108]
	ldr	x5, [x1, 96]
	mov	w1, 0
	stp	w6, w3, [x29, 116]
	blr	x5
	ldr	x4, [x29, 96]
	cmp	w25, 17
	ldp	w6, w3, [x29, 116]
	ldp	w8, w7, [x29, 108]
	ldr	x5, [x4, w23, sxtw 3]
	add	x0, x5, 311296
	add	x2, x5, 307200
	str	w20, [x0, 968]
	str	w3, [x2, 3884]
	lsl	w3, w26, 4
	str	w8, [x2, 3844]
	str	w28, [x2, 3848]
	bne	.L52
.L33:
	mov	w0, 1
	add	w21, w21, w27
	str	w0, [x2, 3888]
	lsr	w0, w3, 1
	str	w3, [x2, 3836]
	str	w21, [x2, 3868]
	str	w0, [x2, 3840]
	b	.L35
	.p2align 3
.L26:
	ldr	x4, .LC28
	mul	w19, w20, w3
	add	w3, w27, 255
	ldr	x5, [x4, w23, sxtw 3]
	add	w19, w19, 143
	and	w26, w3, -256
	and	w19, w19, -128
	ldr	w0, [x5, 1612]
	cmp	w0, 8
	ble	.L53
	ldr	w0, [x5, 1280]
	add	w6, w28, 31
	and	w6, w6, -32
	lsr	w7, w26, 2
	cmp	w0, 1
	asr	w3, w19, 1
	bne	.L41
	.p2align 2
.L48:
	adds	w1, w27, 511
	add	w27, w27, 1022
	csel	w27, w27, w1, mi
	add	w0, w28, 126
	and	w27, w27, -512
	cmp	w27, wzr
	add	w8, w27, 63
	csel	w8, w8, w27, lt
	adds	w27, w28, 63
	csel	w27, w0, w27, mi
	asr	w8, w8, 6
	asr	w27, w27, 6
	lsl	w8, w8, 1
	lsl	w27, w27, 5
	cmp	w24, 1
	mul	w21, w21, w26
	mul	w27, w27, w8
	mov	w28, w27
	bne	.L30
.L49:
	lsl	w1, w20, 6
	sub	w20, w1, w20, lsl 4
	mul	w20, w20, w26
	b	.L31
	.p2align 3
.L47:
	ldr	x4, .LC28
	add	w3, w27, 255
	add	w21, w28, 63
	and	w26, w3, -256
	mov	w19, 128
	mov	w3, 64
	and	w21, w21, -64
	movk	w3, 0x12, lsl 16
	ldr	x5, [x4, w23, sxtw 3]
	movk	w19, 0x24, lsl 16
	mov	w6, 0
	mov	w7, 0
	b	.L37
	.p2align 3
.L53:
	asr	w3, w19, 1
	mov	w6, 0
	mov	w7, 0
	b	.L37
	.p2align 3
.L42:
	mov	w0, 0
	b	.L43
	.p2align 3
.L21:
	ldr	x2, .LC24
	mov	w0, 0
	ldr	x3, .LC23
	ldr	x1, .LC25
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L43
	.size	VDMHAL_V4R3C1_CalcFsSize, .-VDMHAL_V4R3C1_CalcFsSize
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC24:
	.xword	.LANCHOR0
	.align	3
.LC25:
	.xword	.LC6
	.align	3
.LC26:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC27:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC28:
	.xword	s_pstVfmwChan
	.align	3
.LC30:
	.xword	.LC29
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetRpuSize
	.type	VDMHAL_V4R3C1_GetRpuSize, %function
VDMHAL_V4R3C1_GetRpuSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1024
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_GetRpuSize, .-VDMHAL_V4R3C1_GetRpuSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CalcFsNum
	.type	VDMHAL_V4R3C1_CalcFsNum, %function
VDMHAL_V4R3C1_CalcFsNum:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x19, x3
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L60
	cmp	w21, 17
	ldr	x2, .LC34
	beq	.L61
	ldr	x3, [x2, w20, sxtw 3]
	mov	w4, 32
	add	x1, x3, 307200
	ldr	w0, [x1, 1504]
	cmp	w0, w4
	csel	w0, w0, w4, le
	str	w0, [x1, 3888]
	ldr	w0, [x3, 664]
	cmp	w0, 2
	beq	.L62
.L59:
	ldr	x1, [x2, w20, sxtw 3]
	mov	w0, 0
	add	x1, x1, 307200
	ldr	w1, [x1, 1504]
	str	w1, [x19, 8]
	ldr	x1, [x2, w20, sxtw 3]
	add	x1, x1, 307200
	ldr	w1, [x1, 3888]
	str	w1, [x19, 16]
.L57:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L61:
	ldr	x0, [x2, w20, sxtw 3]
	mov	w1, 1
	add	x0, x0, 307200
	str	w1, [x0, 3888]
	b	.L59
	.p2align 3
.L62:
	ldr	w0, [x1, 1508]
	str	w0, [x1, 3888]
	b	.L59
.L60:
	ldr	x2, .LC31
	mov	w0, 1
	ldr	x1, .LC33
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -1
	b	.L57
	.size	VDMHAL_V4R3C1_CalcFsNum, .-VDMHAL_V4R3C1_CalcFsNum
	.align	3
.LC31:
	.xword	.LANCHOR0
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC34:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_DynamicAllocFrame
	.type	VDMHAL_V4R3C1_DynamicAllocFrame, %function
VDMHAL_V4R3C1_DynamicAllocFrame:
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
	ldr	x21, .LC35
	mov	w0, w19
	ldr	x1, [x21, w19, sxtw 3]
	add	x1, x1, 307200
	add	x1, x1, 1528
	bl	DelAllFrameMemRecord
	cbnz	w0, .L83
.L64:
	ldr	x1, [x21, w19, sxtw 3]
	mov	w2, 255
	add	x1, x1, 307200
	add	x0, x1, 1528
	add	x1, x1, 3832
	.p2align 2
.L65:
	str	w2, [x0], 72
	cmp	x1, x0
	bne	.L65
	mov	w0, 1088
	cmp	w23, 1920
	ccmp	w22, w0, 0, le
	ble	.L66
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x20, 8]
.L67:
	add	x2, x0, 307200
	ldr	w3, [x0, 1560]
	mov	w0, w19
	add	w1, w3, w1
	str	w1, [x2, 1508]
	bl	VCTRL_GetVidStd
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w2, [x1, 664]
	cmp	w2, 2
	ccmp	w0, 17, 4, eq
	beq	.L70
	add	x1, x1, 307200
	ldr	w0, [x1, 1508]
	str	w0, [x20, 16]
	ldr	x1, [x21, w19, sxtw 3]
.L70:
	add	x0, x1, 311296
	add	x1, x1, 278528
	mov	w4, 1
	mov	w3, w22
	mov	w2, w23
	str	wzr, [x0, 1008]
	str	w4, [x1, 2152]
	str	w4, [x0, 1548]
	mov	w0, 31
	ldr	x1, .LC39
	ldr	w4, [x20, 8]
	ldr	w5, [x20, 16]
	bl	dprint_vfmw
	ldr	x0, .LC40
	ldr	x4, [x0]
	cbz	x4, .L71
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
.L71:
	ldr	x3, .LC41
	mov	x2, 528
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 0
	ldr	x3, [x3, 96]
	add	x0, x0, 311296
	add	x0, x0, 1016
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 311296
	str	wzr, [x1, 1544]
	bl	FSP_ClearContextAll
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L66:
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x0, 36]
	cmp	w1, 24
	beq	.L82
	add	x1, x0, 311296
	ldr	w1, [x1, 1604]
	cbnz	w1, .L82
	ldr	w1, [x20, 8]
	add	w1, w1, 4
	str	w1, [x20, 8]
	ldr	x0, [x21, w19, sxtw 3]
	b	.L67
.L82:
	ldr	w1, [x20, 8]
	b	.L67
.L83:
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	b	.L64
	.size	VDMHAL_V4R3C1_DynamicAllocFrame, .-VDMHAL_V4R3C1_DynamicAllocFrame
	.align	3
.LC35:
	.xword	s_pstVfmwChan
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC40:
	.xword	g_event_report
	.align	3
.LC41:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_DynamicAllocFrame_Only
	.type	VDMHAL_V4R3C1_DynamicAllocFrame_Only, %function
VDMHAL_V4R3C1_DynamicAllocFrame_Only:
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
	ldr	x4, .LC42
	mov	w3, w21
	ldr	w5, [x19, 8]
	mov	w2, w22
	ldr	x1, .LC44
	mov	w0, 31
	ldr	x4, [x4, w20, sxtw 3]
	add	x4, x4, 307200
	str	w5, [x4, 1508]
	ldr	w4, [x19, 8]
	ldr	w5, [x19, 16]
	bl	dprint_vfmw
	ldr	x0, .LC45
	ldr	x4, [x0]
	cbz	x4, .L84
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
.L84:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDMHAL_V4R3C1_DynamicAllocFrame_Only, .-VDMHAL_V4R3C1_DynamicAllocFrame_Only
	.align	3
.LC42:
	.xword	s_pstVfmwChan
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC45:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ArrangeMem_Normal
	.type	VDMHAL_V4R3C1_ArrangeMem_Normal, %function
VDMHAL_V4R3C1_ArrangeMem_Normal:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	mov	w22, w1
	mov	w23, w2
	mov	w24, w3
	mov	w25, w4
	mov	w27, w5
	mov	x21, x6
	bl	_mcount
	str	xzr, [x29, 120]
	add	x0, x29, 104
	cmp	w22, 21
	stp	xzr, xzr, [x0]
	bhi	.L119
	ldr	x20, .LC50
	ldr	x0, [x20, w19, sxtw 3]
	add	x1, x0, 307200
	ldr	w26, [x1, 1500]
	ldr	w1, [x0, 100]
	cmp	w1, 2
	beq	.L120
	mov	w2, 1
	ldr	w3, [x0, 1284]
	ldr	w4, [x0, 1288]
	ldr	w5, [x0, 1292]
	ldr	x1, .LC52
	str	w2, [x0, 1280]
	mov	w0, w2
	bl	dprint_vfmw
.L93:
	mov	w2, w25
	add	x3, x29, 104
	mov	w1, w22
	mov	w0, w19
	bl	VDMHAL_V4R3C1_CalcFsNum
	mov	w25, w0
	add	x5, x29, 104
	mov	w4, w22
	mov	w3, w27
	mov	w2, w24
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V4R3C1_CalcFsSize
	orr	w0, w25, w0
	cbnz	w0, .L121
	ldr	x27, [x20, w19, sxtw 3]
	ldr	w22, [x29, 104]
	cmp	w26, w22
	add	x26, x27, 307200
	ldr	w25, [x26, 1504]
	ldr	w5, [x26, 1520]
	beq	.L122
.L96:
	ldr	x2, .LC48
	mov	w3, w22
	ldr	x1, .LC56
	mov	w4, w25
	add	x2, x2, 112
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	add	x3, x29, 104
	mov	w2, w24
	add	x0, x0, 307200
	ldr	w1, [x0, 1496]
	str	w22, [x0, 1500]
	cbz	w1, .L123
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V4R3C1_DynamicAllocFrame_Only
.L99:
	ldr	x4, [x20, w19, sxtw 3]
	mov	w3, w25
	ldr	x1, .LC58
	mov	w2, w22
	add	x4, x4, 307200
	mov	w0, 31
	ldr	w4, [x4, 1520]
	bl	dprint_vfmw
	ldr	x19, [x20, w19, sxtw 3]
	ldr	x0, .LC59
	add	x19, x19, 311296
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 984]
	mov	w1, 2
.L91:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, w1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L123:
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V4R3C1_DynamicAllocFrame
	b	.L99
	.p2align 3
.L120:
	add	x2, x0, 1280
	mov	w1, -1
	stp	wzr, wzr, [x2]
	stp	w1, w1, [x2, 8]
	b	.L93
	.p2align 3
.L122:
	cmp	w5, 1
	beq	.L96
	ldr	w0, [x26, 1496]
	cmp	w0, 1
	beq	.L96
	cbz	x21, .L124
	add	x1, x27, 311296
	add	x22, x26, 3832
	mov	x0, x27
	ldr	w23, [x1, 968]
	cbz	w25, .L125
.L101:
	add	x0, x0, 307200
	ldr	w2, [x0, 1508]
	cmp	w2, 30
	bgt	.L126
.L102:
	ldr	x24, .LC59
	add	x26, x26, 3832
	mov	w0, 8
	str	w2, [x26, 48]
	ldr	x1, [x24, 24]
	blr	x1
	ldr	x7, [x20, w19, sxtw 3]
	add	x9, x7, 311296
	ldr	w0, [x9, 1008]
	cbz	w0, .L107
	ldp	w10, w6, [x26, 56]
	mov	x1, x26
	mov	w5, 0
	mov	w8, 1
	.p2align 2
.L106:
	uxtw	x0, w5
	add	w5, w5, 1
	lsl	x2, x0, 6
	add	x2, x2, x0, lsl 3
	add	x2, x7, x2
	add	x11, x2, 307200
	uxtw	x2, w6
	lsl	x3, x2, 2
	add	x4, x2, 20
	sub	x3, x3, x2
	add	w6, w6, 1
	ldr	w2, [x11, 1560]
	add	x3, x1, x3, lsl 2
	ldr	w12, [x11, 1540]
	add	w2, w2, 1023
	and	w2, w2, -1024
	strb	w8, [x3, 472]
	str	w2, [x3, 464]
	add	w2, w23, w2
	str	w12, [x3, 468]
	str	w2, [x1, x4, lsl 2]
	str	w6, [x1, 60]
	ldr	w2, [x11, 1532]
	cmp	w2, 255
	beq	.L104
	ldr	w2, [x1, 68]
	ldr	w4, [x11, 1576]
	add	w3, w2, 1
	uxtw	x2, w2
	lsl	x0, x2, 2
	sub	x0, x0, x2
	add	x0, x1, x0, lsl 2
	str	w4, [x0, 848]
	str	w3, [x1, 68]
.L104:
	ldr	w0, [x1, 64]
	cmp	w0, w10
	bcs	.L105
	ldr	w3, [x11, 1536]
	add	x2, x27, x0, uxtw 3
	add	x2, x2, 307200
	add	w0, w0, 1
	cmp	w3, 255
	beq	.L105
	ldr	w3, [x11, 1592]
	str	w3, [x2, 4040]
	strb	w8, [x2, 4044]
	str	w0, [x1, 64]
.L105:
	ldr	w0, [x9, 1008]
	cmp	w5, w0
	bcc	.L106
.L107:
	ldr	x3, [x24, 104]
	mov	x2, 1232
	mov	x1, x22
	mov	x0, x21
	blr	x3
	ldr	x1, [x20, w19, sxtw 3]
	mov	w3, 1
	ldr	x2, [x24, 32]
	mov	w0, 8
	add	x1, x1, 311296
	str	w3, [x1, 1012]
	blr	x2
	mov	w1, 0
	b	.L91
	.p2align 3
.L126:
	ldr	x1, .LC65
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	mov	w1, 30
	mov	w2, w1
	add	x0, x0, 307200
	str	w1, [x0, 1508]
	b	.L102
	.p2align 3
.L125:
	ldr	x1, .LC63
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	b	.L101
	.p2align 3
.L119:
	ldr	x2, .LC48
	mov	w0, 0
	ldr	x1, .LC49
	ldr	x3, .LC47
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w1, -1
	b	.L91
	.p2align 3
.L121:
	ldr	x1, .LC54
	mov	w0, 31
	bl	dprint_vfmw
	mov	w1, -1
	b	.L91
.L124:
	ldr	x2, .LC48
	mov	w0, 0
	ldr	x1, .LC49
	ldr	x3, .LC61
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w1, -1
	b	.L91
	.size	VDMHAL_V4R3C1_ArrangeMem_Normal, .-VDMHAL_V4R3C1_ArrangeMem_Normal
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC48:
	.xword	.LANCHOR0
	.align	3
.LC49:
	.xword	.LC6
	.align	3
.LC50:
	.xword	s_pstVfmwChan
	.align	3
.LC52:
	.xword	.LC51
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
.LC59:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC61:
	.xword	.LC60
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ArrangeMem_Specific
	.type	VDMHAL_V4R3C1_ArrangeMem_Specific, %function
VDMHAL_V4R3C1_ArrangeMem_Specific:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w21, w0
	mov	w23, w2
	mov	x0, x30
	mov	w24, w1
	mov	w28, w3
	mov	w22, w4
	mov	w26, w5
	mov	w20, w6
	mov	w27, w7
	ldr	x19, [x29, 160]
	bl	_mcount
	cbz	w23, .L209
	sub	w1, w22, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L130
	sub	w1, w26, #32
	cmp	w1, w0
	bhi	.L130
	cbz	x19, .L210
	ldr	x0, .LC73
	cmp	w20, 20
	mov	w6, 20
	mov	x2, 1232
	csel	w6, w20, w6, le
	mov	w1, 0
	ldr	x3, [x0, 96]
	mov	x0, x19
	str	w6, [x29, 124]
	mov	w20, 32
	blr	x3
	ldr	x1, .LC74
	add	w0, w22, 15
	asr	w0, w0, 4
	add	w8, w26, 15
	cmp	w0, 45
	asr	w8, w8, 4
	ldrb	w2, [x1]
	mov	w1, 36
	ccmp	w8, w1, 0, le
	mov	w1, 64
	cset	w3, le
	ldr	w6, [x29, 124]
	cmp	w3, wzr
	csel	w20, w20, w1, eq
	cmp	w2, 1
	csel	w20, w20, w1, ne
	cmp	w24, 16
	lsl	w1, w0, 4
	beq	.L211
	cmp	w24, 17
	beq	.L138
	mul	w20, w0, w20
	mul	w20, w20, w8
	add	w20, w20, 143
	and	w20, w20, -128
	mul	w25, w6, w20
	cmp	w28, w25
	ble	.L136
	add	w7, w23, 1023
	add	w1, w1, 255
	and	w7, w7, -1024
	add	w9, w26, 31
	asr	w0, w20, 1
	and	w1, w1, -256
	stp	w0, w6, [x19, 52]
	and	w9, w9, -32
	add	w4, w26, 63
	mov	w11, 0
	mov	w10, 0
	sub	w6, w7, w23
.L140:
	adds	w0, w22, 511
	add	w22, w22, 1022
	csel	w0, w22, w0, mi
	ldr	w3, [x29, 144]
	and	w2, w0, -512
	cmp	w2, wzr
	add	w0, w2, 63
	csel	w0, w0, w2, lt
	cmp	w4, wzr
	add	w2, w4, 63
	asr	w0, w0, 6
	csel	w2, w2, w4, lt
	lsl	w4, w0, 6
	asr	w2, w2, 6
	lsl	w0, w0, 1
	cmp	w3, 1
	mul	w2, w4, w2
	stp	w0, w2, [x19, 12]
	lsl	w0, w1, 4
	str	w0, [x19, 4]
	asr	w0, w0, 1
	str	w0, [x19, 8]
	beq	.L212
	mul	w4, w9, w1
	mul	w5, w11, w10
	lsl	w0, w4, 2
	lsl	w22, w2, 2
	sub	w4, w0, w4
	lsl	w0, w5, 2
	sub	w0, w0, w5
	sub	w22, w22, w2
	asr	w0, w0, 1
	add	w0, w0, w4, asr 1
	add	w22, w0, w22, lsr 1
.L143:
	ldr	w0, [x29, 152]
	tbnz	w0, #31, .L144
	stp	w7, w1, [x29, 100]
	stp	w9, w10, [x29, 108]
	stp	w11, w6, [x29, 116]
	str	w2, [x29, 124]
	bl	VCTRL_GetChanWidth
	mov	w21, w0
	ldr	w0, [x29, 152]
	bl	VCTRL_GetChanHeight
	cmn	w21, #1
	ldr	w2, [x29, 124]
	ccmn	w0, #1, 4, ne
	ldp	w7, w1, [x29, 100]
	ldp	w9, w10, [x29, 108]
	ldp	w11, w6, [x29, 116]
	beq	.L213
	ldr	w3, [x29, 144]
	add	w4, w21, 15
	and	w4, w4, -16
	add	w0, w0, 15
	cmp	w3, 1
	add	w8, w4, 255
	and	w0, w0, -16
	and	w8, w8, -256
	beq	.L214
	adds	w5, w0, 63
	add	w0, w0, 126
	csel	w0, w0, w5, mi
	adds	w5, w4, 511
	add	w4, w4, 1022
	asr	w0, w0, 6
	csel	w4, w4, w5, mi
	and	w4, w4, -512
	add	w5, w4, 63
	cmp	w4, wzr
	csel	w4, w5, w4, lt
	asr	w4, w4, 6
	lsl	w5, w4, 1
	lsl	w4, w0, 2
	mul	w8, w8, w0
	sub	w0, w4, w0
	lsl	w0, w0, 5
	mul	w4, w5, w0
	mul	w5, w11, w10
	lsl	w0, w8, 2
	sub	w8, w0, w8
	lsl	w0, w5, 2
	lsl	w8, w8, 6
	sub	w0, w0, w5
	asr	w0, w0, 1
	add	w0, w0, w8, asr 1
	add	w0, w0, w4, lsr 1
.L147:
	cmp	w22, w0
	ldr	w21, [x29, 152]
	bgt	.L215
.L144:
	mul	w26, w9, w1
	cmp	w21, wzr
	str	w2, [x29, 124]
	add	w0, w26, w2
	ccmp	w24, 16, 0, ge
	str	w0, [x19, 36]
	stp	w10, w11, [x29, 116]
	bne	.L149
	ldr	x0, .LC77
	stp	w7, w6, [x29, 108]
	ldr	x0, [x0, w21, sxtw 3]
	add	x0, x0, 311296
	add	x0, x0, 1624
	bl	IsMain10Profile
	ldp	w7, w6, [x29, 108]
	ldp	w10, w11, [x29, 116]
	ldr	w2, [x29, 124]
	cbnz	w0, .L216
	.p2align 2
.L149:
	cbnz	w27, .L151
	str	wzr, [x19, 48]
.L152:
	ldr	x2, .LC68
	ldr	x3, .LC84
.L206:
	ldr	x1, .LC69
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
.L151:
	sub	w3, w28, w25
	cmp	w27, 32
	sub	w3, w3, w6
	mov	w0, 32
	csel	w27, w27, w0, le
	sdiv	w3, w3, w22
	cmp	w3, w27
	csel	w3, w3, w27, le
	str	w3, [x19, 48]
	cbz	w3, .L152
	sub	w0, w3, #1
	mov	x1, 476
	mov	w2, 12
	ldr	w4, [x19, 60]
	umaddl	x2, w0, w2, x1
	add	x1, x19, 464
	mov	w0, w7
	add	x2, x19, x2
	.p2align 2
.L157:
	str	w0, [x1], 12
	add	w0, w0, w22
	cmp	x2, x1
	bne	.L157
	ldr	w0, [x29, 144]
	add	w4, w3, w4
	str	w4, [x19, 60]
	cmp	w0, 1
	beq	.L217
	madd	w6, w22, w3, w6
	add	w0, w6, w23
.L168:
	add	x2, x19, 80
	mov	w1, 0
	.p2align 2
.L161:
	add	w1, w1, 1
	str	w0, [x2], 4
	cmp	w1, w3
	add	w0, w0, 32
	bcc	.L161
.L160:
	ldr	w4, [x19, 56]
	add	w6, w6, w3, lsl 5
	add	w23, w6, w23
	cbz	w4, .L166
	sub	w2, w4, #1
	ldr	w5, [x19, 64]
	add	x2, x2, 27
	add	x1, x19, 208
	mov	w0, w23
	add	x2, x19, x2, lsl 3
	.p2align 2
.L165:
	str	w0, [x1], 8
	add	w0, w0, w20
	cmp	x2, x1
	bne	.L165
	add	w0, w4, w5
	str	w0, [x19, 64]
.L166:
	madd	w20, w20, w4, w6
	str	w20, [x19]
	tbnz	w21, #31, .L164
	ldr	x0, .LC77
	ldr	x0, [x0, w21, sxtw 3]
	cbz	x0, .L164
	add	w0, w20, w23
	cbz	w3, .L164
	sub	w4, w3, #1
	mov	w5, 12
	mov	x2, 860
	add	x1, x19, 848
	umaddl	x2, w4, w5, x2
	add	x2, x19, x2
	.p2align 2
.L167:
	str	w0, [x1], 12
	add	w0, w0, 1024
	cmp	x2, x1
	bne	.L167
.L164:
	add	w20, w20, w3, lsl 10
	mov	w0, 0
	str	w20, [x19]
.L199:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L211:
	mul	w20, w8, w1
	add	w20, w20, 143
	and	w20, w20, -128
	mul	w25, w6, w20
	cmp	w28, w25
	ble	.L136
	asr	w0, w20, 1
	add	w7, w23, 1023
	stp	w0, w6, [x19, 52]
	and	w7, w7, -1024
	add	w1, w22, 255
	and	w1, w1, -256
	sub	w6, w7, w23
	tbnz	w21, #31, .L205
	ldr	x0, .LC77
	stp	w7, w1, [x29, 112]
	stp	w6, w8, [x29, 120]
	ldr	x0, [x0, w21, sxtw 3]
	add	x0, x0, 311296
	add	x0, x0, 1624
	bl	IsMain10Profile
	ldp	w7, w1, [x29, 112]
	ldp	w6, w8, [x29, 120]
	cbz	w0, .L205
	cmp	w1, wzr
	add	w10, w1, 3
	csel	w10, w10, w1, lt
	add	w11, w26, 31
	asr	w10, w10, 2
	and	w11, w11, -32
	add	w4, w26, 63
	mov	w9, w26
	b	.L140
	.p2align 3
.L212:
	lsl	w0, w8, 4
	mul	w0, w0, w1
	lsl	w22, w0, 2
	sub	w22, w22, w0
	b	.L143
	.p2align 3
.L217:
	ldr	x0, .LC85
	ldr	x4, [x0]
	cbz	x4, .L159
	stp	w6, w7, [x29, 124]
	stp	w22, w3, [x29, 132]
	add	x2, x29, 128
	mov	w3, 12
	mov	w1, 128
	mov	w0, w21
	blr	x4
	ldr	w3, [x19, 48]
	ldr	w6, [x29, 124]
.L159:
	madd	w6, w22, w3, w6
	add	w0, w6, w23
	cbnz	w3, .L168
	b	.L160
	.p2align 3
.L138:
	lsl	w3, w6, 14
	add	w3, w3, w6, lsl 11
	add	w3, w3, w6
	lsl	w25, w3, 7
	cmp	w28, w25
	ble	.L136
	add	w7, w23, 1023
	add	w4, w26, 63
	and	w7, w7, -1024
	add	w1, w22, 255
	mov	w0, 64
	mov	w20, 128
	movk	w0, 0x12, lsl 16
	and	w1, w1, -256
	stp	w0, w6, [x19, 52]
	and	w9, w4, -64
	movk	w20, 0x24, lsl 16
	mov	w11, 0
	mov	w10, 0
	sub	w6, w7, w23
	b	.L140
	.p2align 3
.L205:
	add	w4, w26, 63
	mov	w9, w26
	mov	w11, 0
	mov	w10, 0
	b	.L140
	.p2align 3
.L214:
	mul	w0, w0, w8
	lsl	w4, w0, 2
	sub	w0, w4, w0
	b	.L147
.L130:
	ldr	x2, .LC68
	ldr	x3, .LC70
	b	.L206
.L216:
	lsl	w0, w26, 2
	sub	w1, w0, w26
	lsl	w0, w2, 2
	sub	w0, w0, w2
	lsr	w2, w2, 1
	lsr	w0, w0, 1
	madd	w11, w11, w10, w2
	add	w0, w0, w1, asr 1
	ldr	x1, .LC82
	lsl	w10, w10, 5
	str	w10, [x19, 20]
	stp	w0, w11, [x19, 28]
	mov	w0, 0
	stp	w7, w6, [x29, 120]
	bl	dprint_vfmw
	ldp	w7, w6, [x29, 120]
	b	.L149
.L136:
	ldr	x2, .LC68
	ldr	x3, .LC76
	b	.L206
.L209:
	ldr	x2, .LC68
	ldr	x3, .LC67
	b	.L206
.L213:
	ldr	x1, .LC79
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L199
.L215:
	ldr	x2, .LC68
	ldr	x3, .LC81
	b	.L206
.L210:
	ldr	x2, .LC68
	ldr	x3, .LC72
	b	.L206
	.size	VDMHAL_V4R3C1_ArrangeMem_Specific, .-VDMHAL_V4R3C1_ArrangeMem_Specific
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC68:
	.xword	.LANCHOR0
	.align	3
.LC69:
	.xword	.LC6
	.align	3
.LC70:
	.xword	.LC22
	.align	3
.LC72:
	.xword	.LC71
	.align	3
.LC73:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC74:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC77:
	.xword	s_pstVfmwChan
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC82:
	.xword	.LC29
	.align	3
.LC84:
	.xword	.LC83
	.align	3
.LC85:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ArrangeMem
	.type	VDMHAL_V4R3C1_ArrangeMem, %function
VDMHAL_V4R3C1_ArrangeMem:
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
	beq	.L222
	tbnz	w19, #31, .L223
	mov	w0, w19
	bl	VCTRL_GetVidStd
	mov	w1, w0
	ldr	x0, .LC86
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 1552]
	cmp	w0, 1
	beq	.L225
.L220:
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
	bl	VDMHAL_V4R3C1_ArrangeMem_Specific
.L224:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L223:
	mov	w1, 22
	b	.L220
	.p2align 3
.L222:
	mov	w1, 16
	b	.L220
	.p2align 3
.L225:
	ldr	x6, [x29, 80]
	mov	w5, w23
	mov	w4, w22
	mov	w3, w21
	mov	w2, w20
	mov	w0, w19
	bl	VDMHAL_V4R3C1_ArrangeMem_Normal
	b	.L224
	.size	VDMHAL_V4R3C1_ArrangeMem, .-VDMHAL_V4R3C1_ArrangeMem
	.align	3
.LC86:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ResetVdm
	.type	VDMHAL_V4R3C1_ResetVdm, %function
VDMHAL_V4R3C1_ResetVdm:
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
	ble	.L227
	ldr	x2, .LC87
	mov	w4, 0
	ldr	x1, .LC89
	mov	w3, w21
	add	x2, x2, 224
	mov	w0, 0
	bl	dprint_vfmw
.L226:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L227:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L239
	sxtw	x22, w21
	ldr	x24, .LC92
	lsl	x0, x22, 6
	ldr	x20, .LC93
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	ldr	x2, [x20]
	add	x0, x0, x1, lsl 2
	ldr	x0, [x24, x0]
	ldr	w25, [x0, 36]
	ldr	w23, [x2, 120]
	tbz	x23, 0, .L226
	ldr	x26, .LC94
	mov	w0, 2
	bfi	w23, w0, 8, 2
	str	w23, [x2, 120]
	mov	w19, 0
	orr	w23, w23, 64
	ldr	x0, [x26, 224]
	blr	x0
	ldr	x0, [x20]
	str	w23, [x0, 120]
	b	.L231
	.p2align 3
.L240:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L232
.L231:
	ldr	x1, [x26, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20]
	ldr	w0, [x0, 372]
	tbz	x0, 2, .L240
	cmp	w19, 999
	bgt	.L232
	ldr	x2, .LC87
	mov	w3, w21
	ldr	x1, .LC98
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
.L234:
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
.L232:
	ldr	x2, .LC87
	mov	w3, w21
	ldr	x1, .LC96
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
	b	.L234
.L239:
	ldr	x1, .LC91
	mov	x2, 0
	bl	dprint_vfmw
	b	.L226
	.size	VDMHAL_V4R3C1_ResetVdm, .-VDMHAL_V4R3C1_ResetVdm
	.align	3
.LC87:
	.xword	.LANCHOR0
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC92:
	.xword	g_HwMem
	.align	3
.LC93:
	.xword	g_pstRegCrg
	.align	3
.LC94:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC96:
	.xword	.LC95
	.align	3
.LC98:
	.xword	.LC97
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.type	VDMHAL_V4R3C1_SetSmmuPageTableAddr, %function
VDMHAL_V4R3C1_SetSmmuPageTableAddr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC99
	ldr	x3, [x0, 392]
	cbz	x3, .L241
	add	x2, x29, 60
	add	x1, x29, 56
	add	x0, x29, 52
	blr	x3
	cbnz	w19, .L243
	ldr	x0, .LC100
	ldp	w3, w2, [x29, 52]
	ldr	w1, [x29, 60]
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w3, [x0, 524]
	str	w2, [x0, 772]
	str	w1, [x0, 776]
.L241:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L243:
	ldr	x20, .LC101
	mov	w3, w19
	ldr	x21, .LC103
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
	.size	VDMHAL_V4R3C1_SetSmmuPageTableAddr, .-VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.align	3
.LC99:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC100:
	.xword	g_HwMem
	.align	3
.LC101:
	.xword	.LANCHOR0
	.align	3
.LC103:
	.xword	.LC102
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_EnableSmmu
	.type	VDMHAL_V4R3C1_EnableSmmu, %function
VDMHAL_V4R3C1_EnableSmmu:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC105
	mov	w1, 8
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_EnableSmmu, .-VDMHAL_V4R3C1_EnableSmmu
	.align	3
.LC105:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GlbResetX
	.type	VDMHAL_V4R3C1_GlbResetX, %function
VDMHAL_V4R3C1_GlbResetX:
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
	cbz	x0, .L260
	ldr	x20, .LC109
	ldr	x0, [x20]
	ldr	w22, [x0, 120]
	tbnz	x22, 0, .L261
.L248:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L261:
	ldr	x21, .LC110
	mov	w1, 2
	bfi	w22, w1, 8, 2
	str	w22, [x0, 120]
	mov	w19, 0
	orr	w22, w22, 16
	ldr	x0, [x21, 224]
	blr	x0
	ldr	x0, [x20]
	str	w22, [x0, 120]
	b	.L252
	.p2align 3
.L262:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L253
.L252:
	ldr	x1, [x21, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20]
	ldr	w0, [x0, 372]
	tbz	x0, 0, .L262
	cmp	w19, 999
	bgt	.L253
	ldr	x2, .LC106
	mov	w3, w23
	ldr	x1, .LC114
	mov	w0, 0
	add	x2, x2, 288
	bl	dprint_vfmw
.L255:
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
.L253:
	ldr	x2, .LC106
	mov	w3, w23
	ldr	x1, .LC112
	mov	w0, 0
	add	x2, x2, 288
	bl	dprint_vfmw
	b	.L255
.L260:
	ldr	x2, .LC106
	mov	w3, -121438208
	ldr	x1, .LC108
	add	x2, x2, 288
	bl	dprint_vfmw
	b	.L248
	.size	VDMHAL_V4R3C1_GlbResetX, .-VDMHAL_V4R3C1_GlbResetX
	.align	3
.LC106:
	.xword	.LANCHOR0
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC109:
	.xword	g_pstRegCrg
	.align	3
.LC110:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC114:
	.xword	.LC113
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GlbReset
	.type	VDMHAL_V4R3C1_GlbReset, %function
VDMHAL_V4R3C1_GlbReset:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L266
	mov	w0, 0
	bl	VDMHAL_V4R3C1_GlbResetX
.L263:
	ldp	x29, x30, [sp], 16
	ret
.L266:
	ldr	x2, .LC115
	mov	w3, -121438208
	ldr	x1, .LC116
	add	x2, x2, 312
	bl	dprint_vfmw
	b	.L263
	.size	VDMHAL_V4R3C1_GlbReset, .-VDMHAL_V4R3C1_GlbReset
	.align	3
.LC115:
	.xword	.LANCHOR0
	.align	3
.LC116:
	.xword	.LC107
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ClearIntState
	.type	VDMHAL_V4R3C1_ClearIntState, %function
VDMHAL_V4R3C1_ClearIntState:
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
	cbz	x0, .L277
	ldr	w22, [x0, 1312]
.L268:
	cmp	w20, wzr
	bgt	.L279
	lsl	x0, x19, 6
	ldr	x23, .LC121
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x23, x20]
	cbz	x0, .L280
.L271:
	cmp	w22, 1
	bne	.L278
	add	x19, x21, x19, lsl 6
	ldr	w1, [x19, 44]
	cmp	w1, 1
	beq	.L278
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L281
	cmp	w1, 3
	bne	.L267
	mov	w1, -15
	str	w1, [x0, 32]
	b	.L267
	.p2align 3
.L279:
	ldr	x2, .LC119
	mov	w4, 0
	ldr	x1, .LC120
	mov	w3, w20
	add	x2, x2, 336
	mov	w0, 0
	bl	dprint_vfmw
.L267:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L278:
	mov	w1, -1
	str	w1, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L277:
	mov	w22, 0
	b	.L268
	.p2align 3
.L280:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L272
	str	x0, [x23, x20]
	b	.L271
	.p2align 3
.L281:
	mov	w1, -12
	str	w1, [x0, 32]
	b	.L267
.L272:
	ldr	x1, .LC123
	mov	w0, 0
	bl	dprint_vfmw
	b	.L267
	.size	VDMHAL_V4R3C1_ClearIntState, .-VDMHAL_V4R3C1_ClearIntState
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
	.xword	.LC88
	.align	3
.LC121:
	.xword	g_HwMem
	.align	3
.LC123:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ClearMMUIntState
	.type	VDMHAL_V4R3C1_ClearMMUIntState, %function
VDMHAL_V4R3C1_ClearMMUIntState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L287
	lsl	x3, x19, 6
	ldr	x20, .LC126
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L288
.L285:
	add	x0, x0, 61440
	mov	w1, 7
	str	w1, [x0, 44]
.L282:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L287:
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
.L288:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L286
	str	x0, [x20, x19]
	b	.L285
.L286:
	ldr	x1, .LC127
	mov	w0, 0
	bl	dprint_vfmw
	b	.L282
	.size	VDMHAL_V4R3C1_ClearMMUIntState, .-VDMHAL_V4R3C1_ClearMMUIntState
	.align	3
.LC124:
	.xword	.LANCHOR0
	.align	3
.LC125:
	.xword	.LC88
	.align	3
.LC126:
	.xword	g_HwMem
	.align	3
.LC127:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_MaskInt
	.type	VDMHAL_V4R3C1_MaskInt, %function
VDMHAL_V4R3C1_MaskInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L294
	lsl	x3, x19, 6
	ldr	x20, .LC130
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L295
.L292:
	mov	w1, -1
	str	w1, [x0, 36]
.L289:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L294:
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
.L295:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L293
	str	x0, [x20, x19]
	b	.L292
.L293:
	ldr	x1, .LC131
	mov	w0, 0
	bl	dprint_vfmw
	b	.L289
	.size	VDMHAL_V4R3C1_MaskInt, .-VDMHAL_V4R3C1_MaskInt
	.align	3
.LC128:
	.xword	.LANCHOR0
	.align	3
.LC129:
	.xword	.LC88
	.align	3
.LC130:
	.xword	g_HwMem
	.align	3
.LC131:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetIntMaskCfg
	.type	VDMHAL_V4R3C1_GetIntMaskCfg, %function
VDMHAL_V4R3C1_GetIntMaskCfg:
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
	.size	VDMHAL_V4R3C1_GetIntMaskCfg, .-VDMHAL_V4R3C1_GetIntMaskCfg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_EnableInt
	.type	VDMHAL_V4R3C1_EnableInt, %function
VDMHAL_V4R3C1_EnableInt:
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
	cbz	x1, .L307
	ldr	w20, [x1, 1312]
.L300:
	cmp	w19, wzr
	bgt	.L308
	lsl	x19, x0, 6
	ldr	x21, .LC136
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	ldr	x0, [x21, x19]
	cbz	x0, .L309
.L303:
	mov	w1, -6
	mov	w2, -2
	cmp	w20, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 36]
.L299:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L308:
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
.L307:
	mov	w20, 0
	b	.L300
	.p2align 3
.L309:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L304
	str	x0, [x21, x19]
	b	.L303
.L304:
	ldr	x1, .LC137
	mov	w0, 0
	bl	dprint_vfmw
	b	.L299
	.size	VDMHAL_V4R3C1_EnableInt, .-VDMHAL_V4R3C1_EnableInt
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
	.xword	.LC88
	.align	3
.LC136:
	.xword	g_HwMem
	.align	3
.LC137:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CheckReg
	.type	VDMHAL_V4R3C1_CheckReg, %function
VDMHAL_V4R3C1_CheckReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	bgt	.L327
	lsl	x0, x19, 6
	ldr	x21, .LC141
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x21, x20]
	cbz	x0, .L328
.L313:
	sub	w0, w22, #1
	cmp	w0, 6
	bls	.L329
	ldr	x2, .LC138
	mov	w3, w22
	ldr	x1, .LC145
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
.L326:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L329:
	ldr	x1, .LC146
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx320
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx320:
	.section	.rodata
	.align	0
	.align	2
.L320:
	.byte	(.L324 - .Lrtx320) / 4
	.byte	(.L321 - .Lrtx320) / 4
	.byte	(.L322 - .Lrtx320) / 4
	.byte	(.L323 - .Lrtx320) / 4
	.byte	(.L325 - .Lrtx320) / 4
	.byte	(.L315 - .Lrtx320) / 4
	.byte	(.L317 - .Lrtx320) / 4
	.text
	.p2align 3
.L325:
	mov	x1, 61480
.L319:
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
.L324:
	mov	x1, 28
	b	.L319
	.p2align 3
.L323:
	mov	x1, 40
	b	.L319
	.p2align 3
.L322:
	mov	x1, 36
	b	.L319
	.p2align 3
.L321:
	mov	x1, 32
	b	.L319
	.p2align 3
.L317:
	mov	x1, 62272
	b	.L319
	.p2align 3
.L315:
	mov	x1, 62304
	b	.L319
	.p2align 3
.L328:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L314
	str	x0, [x21, x20]
	b	.L313
	.p2align 3
.L327:
	ldr	x2, .LC138
	mov	w3, w19
	ldr	x1, .LC140
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L326
.L314:
	ldr	x2, .LC138
	mov	w0, 0
	ldr	x1, .LC143
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
	b	.L326
	.size	VDMHAL_V4R3C1_CheckReg, .-VDMHAL_V4R3C1_CheckReg
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
	.xword	.L320
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ReadMMUMask
	.type	VDMHAL_V4R3C1_ReadMMUMask, %function
VDMHAL_V4R3C1_ReadMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	ble	.L333
	ldr	x2, .LC148
	mov	w3, w19
	ldr	x1, .LC150
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L333:
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
	.size	VDMHAL_V4R3C1_ReadMMUMask, .-VDMHAL_V4R3C1_ReadMMUMask
	.align	3
.LC147:
	.xword	g_HwMem
	.align	3
.LC148:
	.xword	.LANCHOR1
	.align	3
.LC150:
	.xword	.LC149
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_WriteMMUMask
	.type	VDMHAL_V4R3C1_WriteMMUMask, %function
VDMHAL_V4R3C1_WriteMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	ble	.L337
	ldr	x2, .LC152
	mov	w3, w19
	ldr	x1, .LC153
	mov	w4, 1
	add	x2, x2, 32
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L337:
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
	.size	VDMHAL_V4R3C1_WriteMMUMask, .-VDMHAL_V4R3C1_WriteMMUMask
	.align	3
.LC151:
	.xword	g_HwMem
	.align	3
.LC152:
	.xword	.LANCHOR1
	.align	3
.LC153:
	.xword	.LC102
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_PrepareDec
	.type	VDMHAL_V4R3C1_PrepareDec, %function
VDMHAL_V4R3C1_PrepareDec:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x21, x1
	mov	x0, x30
	mov	w22, w2
	mov	x19, x3
	bl	_mcount
	cbz	x21, .L357
	cbnz	w22, .L358
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
	bls	.L359
.L356:
	mov	w0, -1
	b	.L340
	.p2align 3
.L359:
	ldr	x0, .LC159
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx343
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx343:
	.section	.rodata
	.align	0
	.align	2
.L343:
	.byte	(.L353 - .Lrtx343) / 4
	.byte	(.L344 - .Lrtx343) / 4
	.byte	(.L345 - .Lrtx343) / 4
	.byte	(.L346 - .Lrtx343) / 4
	.byte	(.L356 - .Lrtx343) / 4
	.byte	(.L347 - .Lrtx343) / 4
	.byte	(.L348 - .Lrtx343) / 4
	.byte	(.L356 - .Lrtx343) / 4
	.byte	(.L349 - .Lrtx343) / 4
	.byte	(.L350 - .Lrtx343) / 4
	.byte	(.L351 - .Lrtx343) / 4
	.byte	(.L351 - .Lrtx343) / 4
	.byte	(.L351 - .Lrtx343) / 4
	.byte	(.L352 - .Lrtx343) / 4
	.byte	(.L356 - .Lrtx343) / 4
	.byte	(.L353 - .Lrtx343) / 4
	.byte	(.L354 - .Lrtx343) / 4
	.byte	(.L355 - .Lrtx343) / 4
	.text
	.p2align 3
.L353:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	H264HAL_V4R3C1_StartDec
.L340:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L354:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	HEVCHAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L352:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	VP8HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L351:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	VP6HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L350:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	RV9HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L349:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	RV8HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L348:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	AVSHAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L347:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	DIVX3HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L346:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	MP2HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L345:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	MP4HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L344:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	VC1HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L355:
	mov	x2, x19
	mov	w1, 0
	mov	x0, x21
	bl	VP9HAL_V4R3C1_StartDec
	b	.L340
	.p2align 3
.L358:
	ldr	x2, .LC154
	mov	w3, w22
	ldr	x1, .LC158
	mov	w0, 0
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L340
.L357:
	ldr	x2, .LC154
	mov	x3, 0
	ldr	x1, .LC156
	mov	w0, 0
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L340
	.size	VDMHAL_V4R3C1_PrepareDec, .-VDMHAL_V4R3C1_PrepareDec
	.align	3
.LC154:
	.xword	.LANCHOR1
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC158:
	.xword	.LC157
	.align	3
.LC159:
	.xword	.L343
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_IsVdmReady
	.type	VDMHAL_V4R3C1_IsVdmReady, %function
VDMHAL_V4R3C1_IsVdmReady:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC160
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L365
	cmp	w19, wzr
	ble	.L366
	ldr	x2, .LC163
	mov	w4, 1
	ldr	x1, .LC165
	mov	w3, w19
	add	x2, x2, 96
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 0
.L362:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L366:
	ldr	w0, [x0, 28]
	ldr	x19, [sp, 16]
	ubfx	x0, x0, 17, 1
	ldp	x29, x30, [sp], 32
	ret
.L365:
	ldr	x2, .LC163
	ldr	x3, .LC162
	ldr	x1, .LC164
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L362
	.size	VDMHAL_V4R3C1_IsVdmReady, .-VDMHAL_V4R3C1_IsVdmReady
	.align	3
.LC160:
	.xword	g_HwMem
	.align	3
.LC162:
	.xword	.LC161
	.align	3
.LC163:
	.xword	.LANCHOR1
	.align	3
.LC164:
	.xword	.LC6
	.align	3
.LC165:
	.xword	.LC149
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_IsVdmRun
	.type	VDMHAL_V4R3C1_IsVdmRun, %function
VDMHAL_V4R3C1_IsVdmRun:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC166
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L372
	cmp	w19, wzr
	ble	.L373
	ldr	x2, .LC169
	mov	w4, 1
	ldr	x1, .LC170
	mov	w3, w19
	add	x2, x2, 128
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
.L369:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L373:
	ldr	w0, [x0, 40]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L372:
	ldr	x1, .LC168
	bl	dprint_vfmw
	mov	w0, 0
	b	.L369
	.size	VDMHAL_V4R3C1_IsVdmRun, .-VDMHAL_V4R3C1_IsVdmRun
	.align	3
.LC166:
	.xword	g_HwMem
	.align	3
.LC168:
	.xword	.LC167
	.align	3
.LC169:
	.xword	.LANCHOR1
	.align	3
.LC170:
	.xword	.LC149
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_IsVdhDecOver
	.type	VDMHAL_V4R3C1_IsVdhDecOver, %function
VDMHAL_V4R3C1_IsVdhDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC171
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L382
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V4R3C1_CheckReg
	cmp	w19, 2
	beq	.L379
	cmp	w19, 3
	beq	.L379
	cmp	w19, 1
	ubfx	x0, x0, 17, 1
	beq	.L376
	ldr	x2, .LC173
	mov	w3, w19
	ldr	x1, .LC175
	mov	w0, 0
	add	x2, x2, 152
	bl	dprint_vfmw
	mov	w0, 0
.L376:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L379:
	and	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L382:
	ldr	x2, .LC173
	ldr	x3, .LC172
	ldr	x1, .LC174
	add	x2, x2, 152
	bl	dprint_vfmw
	mov	w0, -1
	b	.L376
	.size	VDMHAL_V4R3C1_IsVdhDecOver, .-VDMHAL_V4R3C1_IsVdhDecOver
	.align	3
.LC171:
	.xword	g_HwMem
	.align	3
.LC172:
	.xword	.LC161
	.align	3
.LC173:
	.xword	.LANCHOR1
	.align	3
.LC174:
	.xword	.LC6
	.align	3
.LC175:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_IsVdhPartDecOver
	.type	VDMHAL_V4R3C1_IsVdhPartDecOver, %function
VDMHAL_V4R3C1_IsVdhPartDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC176
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L391
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V4R3C1_CheckReg
	cmp	w19, 1
	beq	.L387
	cmp	w19, 2
	ubfx	x0, x0, 2, 1
	bne	.L392
.L385:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L392:
	ldr	x2, .LC178
	mov	w3, w19
	ldr	x1, .LC180
	mov	w0, 0
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L387:
	ubfx	x0, x0, 19, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L391:
	ldr	x2, .LC178
	ldr	x3, .LC177
	ldr	x1, .LC179
	add	x2, x2, 184
	bl	dprint_vfmw
	mov	w0, -1
	b	.L385
	.size	VDMHAL_V4R3C1_IsVdhPartDecOver, .-VDMHAL_V4R3C1_IsVdhPartDecOver
	.align	3
.LC176:
	.xword	g_HwMem
	.align	3
.LC177:
	.xword	.LC161
	.align	3
.LC178:
	.xword	.LANCHOR1
	.align	3
.LC179:
	.xword	.LC6
	.align	3
.LC180:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_UpdateHardwareInfo
	.type	VDMHAL_V4R3C1_UpdateHardwareInfo, %function
VDMHAL_V4R3C1_UpdateHardwareInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, wzr
	bgt	.L394
	ldr	x4, .LC181
	ldr	w0, [x4]
	cmp	w0, 1
	beq	.L395
	add	x0, x4, 4
	add	x4, x4, 128
	b	.L398
	.p2align 3
.L434:
	cmp	x0, x4
	beq	.L433
.L398:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L434
.L395:
	sxtw	x19, w21
	ldr	x24, .LC186
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x1, x0, x19
	add	x0, x0, x1, lsl 2
	ldr	x2, [x24, x0]
	cbz	x2, .L435
	lsl	x0, x19, 2
	ldr	x20, .LC187
	sub	x1, x0, x19
	ldr	w3, [x2, 12]
	lsl	x0, x1, 4
	mov	w22, 1
	sub	x0, x0, x1
	lsl	x0, x0, 2
	add	x1, x20, x0
	str	w3, [x20, x0]
	ldr	w2, [x2, 28]
	str	w2, [x1, 4]
.L401:
	lsl	x0, x19, 6
	and	w23, w2, 131071
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x1, x0, x19
	add	x0, x0, x1, lsl 2
	add	x0, x24, x0
	ldr	w0, [x0, 56]
	bl	MEM_Phy2Vir
	cbz	x0, .L436
	sub	w1, w23, #1
	cmp	w1, 199
	bhi	.L410
	lsl	w1, w23, 2
	sub	w1, w1, #4
	lsl	x1, x1, 2
	add	x3, x1, 8
.L404:
	lsl	x2, x19, 2
	ldr	w4, [x0, x1]
	sub	x2, x2, x19
	lsl	x1, x2, 4
	sub	x2, x1, x2
	lsl	x1, x19, 6
	sub	x1, x1, x19
	add	x2, x20, x2, lsl 2
	lsl	x1, x1, 2
	str	w4, [x2, 16]
	ldr	w3, [x0, x3]
	sub	x0, x1, x19
	str	w3, [x2, 20]
	add	x1, x1, x0, lsl 2
	ldr	x1, [x24, x1]
	ldr	w3, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w3, w0, [x2, 8]
	b	.L405
	.p2align 3
.L433:
	sxtw	x19, w21
	ldr	x24, .LC186
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x1, x0, x19
	add	x0, x0, x1, lsl 2
	ldr	x1, [x24, x0]
	cbz	x1, .L437
	lsl	x0, x19, 2
	ldr	x20, .LC187
	sub	x2, x0, x19
	ldr	w3, [x1, 12]
	lsl	x0, x2, 4
	mov	w22, 0
	sub	x0, x0, x2
	lsl	x0, x0, 2
	add	x2, x20, x0
	str	w3, [x20, x0]
	ldr	w0, [x1, 28]
	str	w0, [x2, 4]
.L402:
	lsl	x0, x19, 2
	ldr	w2, [x1, 4096]
	sub	x4, x0, x19
	ldr	w5, [x1, 4116]
	lsl	x0, x4, 4
	ldr	w3, [x1, 208]
	sub	x0, x0, x4
	add	x0, x20, x0, lsl 2
	stp	w2, w5, [x0, 16]
	ldr	w2, [x1, 212]
	str	w3, [x0, 8]
	str	w2, [x0, 12]
	cbnz	w22, .L405
	ldr	w5, [x1, 176]
	ldr	w2, [x1, 180]
	stp	w5, w2, [x0, 24]
	ldr	w4, [x1, 184]
	ldr	w3, [x1, 188]
	ldr	w2, [x1, 192]
	stp	w4, w3, [x0, 32]
	str	w2, [x0, 40]
.L405:
	mov	w0, 180
	add	x4, x1, 32768
	add	x1, x4, 256
	smull	x2, w21, w0
	add	x0, x2, 52
	add	x2, x2, 180
	add	x0, x20, x0
	add	x3, x20, x2
	.p2align 2
.L406:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L406
	mov	w0, 0
	cbnz	w22, .L420
	lsl	x1, x19, 2
	ldr	w3, [x4, 384]
	sub	x19, x1, x19
	ldr	w2, [x4, 388]
	lsl	x1, x19, 4
	sub	x1, x1, x19
	add	x20, x20, x1, lsl 2
	stp	w2, w3, [x20, 44]
.L420:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L410:
	mov	x3, 8
	mov	x1, 0
	b	.L404
.L394:
	ldr	x2, .LC182
	mov	w4, 0
	ldr	x1, .LC183
	mov	w3, w21
	add	x2, x2, 216
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L420
.L437:
	mov	w22, 0
.L407:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L400
	lsl	x2, x19, 6
	lsl	x3, x19, 2
	sub	x2, x2, x19
	sub	x4, x3, x19
	lsl	x2, x2, 2
	lsl	x3, x4, 4
	sub	x1, x2, x19
	sub	x3, x3, x4
	ldr	x20, .LC187
	lsl	x3, x3, 2
	add	x2, x2, x1, lsl 2
	add	x1, x20, x3
	str	x0, [x24, x2]
	ldr	w2, [x0, 12]
	str	w2, [x20, x3]
	ldr	w2, [x0, 28]
	str	w2, [x1, 4]
	cbnz	w22, .L401
	mov	x1, x0
	b	.L402
.L435:
	mov	w22, 1
	b	.L407
.L436:
	ldr	x2, .LC182
	ldr	x3, .LC190
	ldr	x1, .LC191
	add	x2, x2, 216
	bl	dprint_vfmw
	mov	w0, -1
	b	.L420
.L400:
	ldr	x1, .LC188
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L420
	.size	VDMHAL_V4R3C1_UpdateHardwareInfo, .-VDMHAL_V4R3C1_UpdateHardwareInfo
	.align	3
.LC181:
	.xword	g_DSPState
	.align	3
.LC182:
	.xword	.LANCHOR1
	.align	3
.LC183:
	.xword	.LC88
	.align	3
.LC186:
	.xword	g_HwMem
	.align	3
.LC187:
	.xword	g_BackUp
	.align	3
.LC188:
	.xword	.LC122
	.align	3
.LC190:
	.xword	.LC189
	.align	3
.LC191:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_ReadMsgSlot
	.type	VDMHAL_V4R3C1_ReadMsgSlot, %function
VDMHAL_V4R3C1_ReadMsgSlot:
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
	beq	.L442
	cmp	w19, 800
	bhi	.L443
	ldr	x3, .LC196
	ubfiz	x2, x19, 2, 30
	mov	x1, x21
	mov	x0, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L440:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L443:
	ldr	x1, .LC195
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L440
	.p2align 3
.L442:
	ldr	x1, .LC193
	mov	x3, x21
	mov	x2, x20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L440
	.size	VDMHAL_V4R3C1_ReadMsgSlot, .-VDMHAL_V4R3C1_ReadMsgSlot
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
	.global	VDMHAL_V4R3C1_WriteMsgSlot
	.type	VDMHAL_V4R3C1_WriteMsgSlot, %function
VDMHAL_V4R3C1_WriteMsgSlot:
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
	beq	.L445
	sub	w0, w21, #1
	cmp	w0, 255
	bhi	.L445
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
.L445:
	ldr	x1, .LC198
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMHAL_V4R3C1_WriteMsgSlot, .-VDMHAL_V4R3C1_WriteMsgSlot
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC199:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CfgRpMsg
	.type	VDMHAL_V4R3C1_CfgRpMsg, %function
VDMHAL_V4R3C1_CfgRpMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L488
	ldr	w0, [x20, 64]
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L489
	ldr	w2, [x19, 44]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L490
	ldp	w2, w0, [x19, 28]
	ldr	w4, [x19, 64]
	mov	w3, 0
	ldrb	w5, [x19]
	lsl	w2, w2, w4
	lsl	w0, w0, w4
	cmp	w5, 1
	add	w1, w2, 255
	and	w1, w1, -256
	lsl	w5, w1, 4
	beq	.L491
.L453:
	ldr	w2, [x19, 4]
	cmp	w2, 16
	beq	.L454
	add	w0, w0, 31
	mov	w23, 8
	and	w0, w0, -32
	madd	w0, w0, w1, w3
.L475:
	ldr	w1, [x19, 20]
	mov	w4, 0
	str	w1, [x20]
	mov	w2, 0
	ldr	w1, [x19, 20]
	add	w1, w0, w1
	str	w1, [x20, 4]
	ldr	w1, [x19, 8]
	str	w1, [x20, 8]
	ldr	w1, [x19, 8]
	add	w0, w0, w1
	str	w0, [x20, 12]
	str	w5, [x20, 16]
	str	w3, [x20, 20]
	ldp	w1, w0, [x19, 28]
	sub	w0, w0, #1
	sub	w1, w1, #1
	bfi	w2, w0, 0, 9
	bfi	w4, w1, 0, 9
	strh	w2, [x29, 74]
	strh	w4, [x29, 72]
	ldr	w0, [x29, 72]
	str	w0, [x20, 24]
	ldr	w0, [x19, 52]
	ldp	w21, w22, [x19, 28]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L492
.L456:
	ldr	w0, [x19, 56]
	mov	w11, 0
	cbz	w0, .L493
.L457:
	cmp	w0, 1
	beq	.L473
.L498:
	sub	w11, w11, #1
	uxth	w11, w11
.L474:
	ldrb	w4, [x19]
	ldr	w2, [x19, 52]
	ldr	w3, [x19, 64]
	ldrb	w0, [x29, 74]
	and	w2, w2, 3
	ldrb	w1, [x29, 75]
	sub	w3, w3, #4
	bfi	w0, w4, 0, 1
	strh	w11, [x29, 72]
	bfi	w0, w2, 4, 2
	bfi	w1, w3, 0, 2
	bfi	w0, w2, 6, 2
	bfi	w1, w23, 2, 4
	strb	w0, [x29, 74]
	mov	w0, 0
	strb	w1, [x29, 75]
	ldr	w1, [x29, 72]
	str	w1, [x20, 28]
.L486:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L493:
	ldr	w0, [x19, 64]
	cmp	w0, 6
	beq	.L478
	cmp	w0, 5
	beq	.L479
	cmp	w0, 4
	mov	w2, 8
	beq	.L458
	ldr	x1, .LC209
	mov	w0, 1
	bl	dprint_vfmw
	mov	w2, 1
.L458:
	ldr	w8, [x19, 44]
	cmp	w8, wzr
	ble	.L487
	mul	w12, w22, w21
	mov	w4, 0
	mov	w6, 0
	sub	w13, w12, #1
	mov	w11, 0
	sub	w9, w2, #1
	b	.L461
	.p2align 3
.L496:
	ldrsh	w6, [x10, 74]
	sub	w6, w6, #1
	add	w6, w6, w2
	udiv	w6, w6, w2
	mul	w6, w6, w2
	cmp	w0, w6
	bgt	.L464
.L463:
	add	w4, w4, 1
	cmp	w4, w8
	bge	.L494
.L472:
	cmp	w4, 199
	bgt	.L495
.L461:
	add	x10, x19, x4, sxtw 2
	cmp	w4, wzr
	ldrsh	w1, [x10, 78]
	sub	w0, w1, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	bgt	.L496
	ccmp	w0, w6, 0, ne
	ble	.L463
.L466:
	ldrsh	w1, [x10, 76]
	cmp	w12, w0
	csel	w0, w0, w13, hi
	add	w5, w11, 1
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w5, 250
	bgt	.L497
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
	blt	.L472
.L494:
	ldr	w0, [x19, 56]
	cmp	w0, 1
	bne	.L498
	.p2align 2
.L473:
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
	b	.L474
	.p2align 3
.L454:
	madd	w0, w0, w1, w3
	mov	w23, 10
	b	.L475
	.p2align 3
.L491:
	adds	w3, w2, 511
	add	w2, w2, 1022
	csel	w2, w2, w3, mi
	add	w4, w0, 126
	and	w2, w2, -512
	cmp	w2, wzr
	add	w3, w2, 63
	csel	w2, w3, w2, lt
	adds	w6, w0, 63
	csel	w3, w4, w6, mi
	asr	w2, w2, 6
	asr	w3, w3, 6
	lsl	w2, w2, 1
	lsl	w3, w3, 5
	mul	w3, w2, w3
	b	.L453
	.p2align 3
.L492:
	add	w22, w22, w22, lsr 31
	asr	w22, w22, 1
	b	.L456
	.p2align 3
.L467:
	udiv	w0, w0, w2
	ldrsh	w1, [x5, 80]
	udiv	w1, w1, w2
	mul	w0, w0, w2
	mul	w1, w1, w2
	cmp	w0, w1
	add	w14, w1, 1
	bhi	.L468
	sub	w1, w4, #1
	cmp	w0, w14
	add	x1, x19, x1, sxtw 2
	beq	.L468
	ldrsh	w1, [x1, 78]
	sub	w1, w1, #1
	add	w1, w1, w2
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w0, w1
	bhi	.L466
.L468:
	cmp	w7, 199
	mov	w4, w3
	bgt	.L499
	ldrsh	w1, [x5, 82]
.L464:
	add	w3, w4, 1
	add	x5, x19, x4, sxtw 2
	cmp	w8, w3
	add	w0, w9, w1
	add	w7, w3, 1
	bgt	.L467
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L466
.L478:
	mov	w2, 2
	b	.L458
	.p2align 3
.L499:
	add	x0, x19, x3, sxtw 2
	ldrsh	w0, [x0, 78]
	sub	w0, w0, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L466
.L495:
	ldr	x2, .LC204
	mov	w3, 2111
	ldr	x1, .LC211
	mov	w0, 0
	add	x2, x2, 280
	bl	dprint_vfmw
.L487:
	mov	w11, 0
	ldr	w0, [x19, 56]
	b	.L457
.L479:
	mov	w2, 4
	b	.L458
.L488:
	ldr	x1, .LC201
	mov	x3, x20
	mov	x2, x19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L486
.L497:
	mov	w0, 1
	str	w0, [x19, 56]
	b	.L473
.L490:
	ldr	x1, .LC207
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L486
.L489:
	ldr	x2, .LC204
	mov	w0, 0
	ldr	x3, .LC203
	ldr	x1, .LC205
	add	x2, x2, 256
	bl	dprint_vfmw
	mov	w0, -1
	b	.L486
	.size	VDMHAL_V4R3C1_CfgRpMsg, .-VDMHAL_V4R3C1_CfgRpMsg
	.align	3
.LC201:
	.xword	.LC200
	.align	3
.LC203:
	.xword	.LC202
	.align	3
.LC204:
	.xword	.LANCHOR1
	.align	3
.LC205:
	.xword	.LC6
	.align	3
.LC207:
	.xword	.LC206
	.align	3
.LC209:
	.xword	.LC208
	.align	3
.LC211:
	.xword	.LC210
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CfgRpReg
	.type	VDMHAL_V4R3C1_CfgRpReg, %function
VDMHAL_V4R3C1_CfgRpReg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x0, x30
	mov	x22, x1
	mov	x19, x2
	mov	w21, w3
	mov	x20, x4
	bl	_mcount
	cmp	x19, xzr
	str	wzr, [x29, 60]
	ccmp	x22, xzr, 4, ne
	beq	.L527
	cmp	w21, wzr
	bgt	.L528
	ldr	x0, [x22]
	cbz	x0, .L529
.L504:
	ldr	x19, .LC217
	ldr	w3, [x22, 64]
	ldrb	w0, [x19]
	and	w3, w3, -16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L530
	mov	w2, 16
	mov	w1, 2
	mov	x0, x20
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	mov	w3, 53763
	movk	w3, 0x2000, lsl 16
	str	w3, [x29, 60]
	cmp	w0, 1
	ldr	x2, .LC218
	sxtw	x1, w21
	beq	.L507
	mov	w2, 12
	mov	w1, 2
	mov	x0, x20
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	VDH_Record_RegData
	str	w22, [x29, 60]
	ldrb	w0, [x19]
	sxtw	x1, w21
	ldr	x2, .LC218
	cmp	w0, 1
	beq	.L509
	mov	x0, x20
	mov	w3, w22
	mov	w2, 60
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L531
	mov	x0, x20
	mov	w3, w22
	mov	w2, 64
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L532
	mov	x0, x20
	mov	w3, w22
	mov	w2, 68
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L533
	mov	x0, x20
	mov	w3, w22
	mov	w2, 72
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L534
	mov	x0, x20
	mov	w3, w22
	mov	w2, 76
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L535
	mov	x0, x20
	mov	w3, w22
	mov	w2, 80
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L536
	mov	x0, x20
	mov	w3, w22
	mov	w2, 84
	mov	w1, 2
	bl	VDH_Record_RegData
	mov	w0, 0
.L524:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L530:
	sxtw	x1, w21
	ldr	x2, .LC218
	lsl	x0, x1, 6
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x4, x0, x1
	add	x0, x0, x4, lsl 2
	ldr	x0, [x2, x0]
	str	w3, [x0, 16]
.L507:
	lsl	x0, x1, 6
	mov	w4, 53763
	sub	x0, x0, x1
	movk	w4, 0x2000, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 12]
.L509:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 60]
.L511:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 64]
.L513:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 68]
.L515:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 72]
.L517:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 76]
.L519:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 80]
.L521:
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
.L529:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L505
	str	x0, [x22]
	b	.L504
	.p2align 3
.L528:
	ldr	x2, .LC214
	mov	w4, 0
	ldr	x1, .LC215
	mov	w3, w21
	add	x2, x2, 304
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L524
	.p2align 3
.L527:
	ldr	x1, .LC213
	mov	x3, x22
	mov	x2, x19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L524
.L505:
	ldr	x1, .LC216
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L524
.L533:
	ldr	x2, .LC218
	sxtw	x1, w21
	b	.L515
.L532:
	ldr	x2, .LC218
	sxtw	x1, w21
	b	.L513
.L531:
	ldr	x2, .LC218
	sxtw	x1, w21
	b	.L511
.L536:
	ldr	x2, .LC218
	sxtw	x1, w21
	b	.L521
.L535:
	ldr	x2, .LC218
	sxtw	x1, w21
	b	.L519
.L534:
	ldr	x2, .LC218
	sxtw	x1, w21
	b	.L517
	.size	VDMHAL_V4R3C1_CfgRpReg, .-VDMHAL_V4R3C1_CfgRpReg
	.align	3
.LC213:
	.xword	.LC212
	.align	3
.LC214:
	.xword	.LANCHOR1
	.align	3
.LC215:
	.xword	.LC88
	.align	3
.LC216:
	.xword	.LC122
	.align	3
.LC217:
	.xword	g_HalDisable
	.align	3
.LC218:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_MakeDecReport
	.type	VDMHAL_V4R3C1_MakeDecReport, %function
VDMHAL_V4R3C1_MakeDecReport:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L567
	ldr	x23, [x19, 8]
	ldr	w21, [x19]
	ldr	w22, [x19, 16]
	cbz	x23, .L568
	sxtw	x22, w22
	ldr	x20, .LC227
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x0, [x20, x0]
	cbz	x0, .L541
	ldr	x2, .LC228
	add	x0, x2, 4
	add	x2, x2, 128
	ldr	w1, [x2, -128]
	cmp	w1, 1
	bne	.L544
	b	.L556
	.p2align 3
.L570:
	cmp	x0, x2
	beq	.L569
.L544:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L570
.L556:
	mov	w19, w1
.L542:
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
	beq	.L557
	and	w1, w1, 131072
	cmp	w1, wzr
	ccmp	w21, 3, 0, ne
	cset	w1, ne
.L545:
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
	beq	.L571
.L546:
	cmp	w2, 200
	bhi	.L572
.L548:
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	add	x20, x20, x0
	ldr	w21, [x20, 56]
	mov	w0, w21
	bl	MEM_Phy2Vir
	cbz	x0, .L573
	lsl	x3, x22, 2
	ldr	x19, .LC238
	sub	x3, x3, x22
	ldr	w2, [x23, 12]
	mov	x1, x0
	add	x20, x22, x3, lsl 3
	lsl	w2, w2, 2
	add	x0, x19, x20, lsl 7
	bl	VDMHAL_V4R3C1_ReadMsgSlot
	ldr	w0, [x23, 12]
	cbz	w0, .L553
	sub	w2, w0, #1
	mov	x5, 26
	add	x1, x23, 22
	mov	w0, 2
	add	x5, x5, x2, uxtw 2
	lsl	x3, x20, 5
	add	x5, x23, x5
	.p2align 2
.L552:
	sub	w2, w0, #1
	add	x4, x3, x0, uxtw
	add	x2, x3, x2
	add	w0, w0, 4
	ldr	w2, [x19, x2, lsl 2]
	strh	w2, [x1, -2]
	ldr	w2, [x19, x4, lsl 2]
	strh	w2, [x1], 4
	cmp	x5, x1
	bne	.L552
.L553:
	mov	w0, 6
	bl	IsDprintTypeEnable
	cbnz	w0, .L574
.L539:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L571:
	cmp	w19, 1
	beq	.L575
	ldr	x1, .LC234
	ldrb	w1, [x1]
	cbnz	w1, .L546
	ldrb	w0, [x0, 19]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L546
	mov	w0, 1
	strh	wzr, [x23, 20]
	str	w0, [x23, 12]
	mov	w0, 0
	strh	wzr, [x23, 22]
	b	.L539
	.p2align 3
.L569:
	mov	w19, 0
	b	.L542
	.p2align 3
.L574:
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
.L554:
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
	bhi	.L554
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
.L557:
	mov	w1, 0
	b	.L545
	.p2align 3
.L572:
	ldr	x1, .LC236
	mov	w3, 200
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 12]
	b	.L548
	.p2align 3
.L575:
	ldr	w0, [x0, 16]
	ubfx	x0, x0, 21, 2
	cmp	w0, 2
	bne	.L546
	strh	wzr, [x23, 20]
	mov	w0, 0
	strh	wzr, [x23, 22]
	str	w19, [x23, 12]
	b	.L539
.L573:
	ldr	x2, .LC223
	ldr	x3, .LC237
	ldr	x1, .LC224
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, -1
	b	.L539
.L541:
	ldr	x2, .LC223
	ldr	x3, .LC229
.L565:
	ldr	x1, .LC224
	mov	w0, 0
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, -1
	b	.L539
.L568:
	ldr	x2, .LC223
	ldr	x3, .LC226
	b	.L565
.L567:
	ldr	x2, .LC223
	ldr	x3, .LC222
	b	.L565
	.size	VDMHAL_V4R3C1_MakeDecReport, .-VDMHAL_V4R3C1_MakeDecReport
	.align	3
.LC222:
	.xword	.LC221
	.align	3
.LC223:
	.xword	.LANCHOR1
	.align	3
.LC224:
	.xword	.LC6
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
	.xword	.LC161
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
	.xword	.LC189
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
	.global	VDMHAL_V4R3C1_PrepareRepair
	.type	VDMHAL_V4R3C1_PrepareRepair, %function
VDMHAL_V4R3C1_PrepareRepair:
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
	mov	x26, x1
	mov	w25, w2
	mov	x23, x4
	bl	_mcount
	ldr	x24, .LC247
	lsl	x0, x19, 6
	mov	x21, x19
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	add	x27, x20, x24
	cbz	x26, .L588
	cmp	w19, wzr
	bgt	.L589
	ldr	x0, [x20, x24]
	cbz	x0, .L590
	cbz	w25, .L591
.L582:
	cmp	w25, 1
	mov	w20, 0
	beq	.L592
.L578:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L590:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L581
	str	x0, [x20, x24]
	cbnz	w25, .L582
	.p2align 2
.L591:
	lsl	x0, x19, 3
	ldr	x24, .LC254
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x24, x0, lsl 3
	ldr	w1, [x0, 44]
	cmp	w1, wzr
	ble	.L583
	cmp	w22, 6
	bne	.L584
	ldrb	w1, [x26, 17]
	mov	w2, 0
	cmp	w1, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 928]
.L584:
	mov	x4, x23
	mov	w3, w21
	mov	x2, x26
	mov	x1, x27
	mov	w0, w22
	mov	w20, 0
	bl	VDMHAL_V4R3C1_CfgRpReg
	lsl	x0, x19, 3
	mov	w2, w21
	sub	x0, x0, x19
	mov	x1, x27
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x24, x0, lsl 3
	bl	VDMHAL_V4R3C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L592:
	cmp	w22, 6
	bne	.L586
	ldrb	w0, [x26, 17]
	cmp	w0, 1
	bne	.L586
	lsl	x0, x19, 3
	ldr	x24, .LC254
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	lsl	x19, x19, 3
	add	x0, x24, x19
	ldr	w1, [x0, 920]
	cmp	w1, wzr
	ble	.L586
	mov	w1, 2
	mov	x4, x23
	mov	w3, w21
	mov	x2, x26
	str	w1, [x0, 928]
	mov	x1, x27
	mov	w0, w22
	bl	VDMHAL_V4R3C1_CfgRpReg
	add	x0, x19, 876
	mov	w2, w21
	mov	x1, x27
	add	x0, x24, x0
	bl	VDMHAL_V4R3C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L589:
	ldr	x2, .LC250
	mov	w4, 0
	ldr	x1, .LC251
	mov	w3, w19
	add	x2, x2, 360
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L578
	.p2align 3
.L586:
	ldr	x1, .LC258
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	b	.L578
.L588:
	ldr	x1, .LC249
	mov	x2, 0
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L578
.L583:
	ldr	x1, .LC256
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	b	.L578
.L581:
	ldr	x1, .LC253
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L578
	.size	VDMHAL_V4R3C1_PrepareRepair, .-VDMHAL_V4R3C1_PrepareRepair
	.align	3
.LC247:
	.xword	g_HwMem
	.align	3
.LC249:
	.xword	.LC248
	.align	3
.LC250:
	.xword	.LANCHOR1
	.align	3
.LC251:
	.xword	.LC88
	.align	3
.LC253:
	.xword	.LC252
	.align	3
.LC254:
	.xword	g_RepairParam
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC258:
	.xword	.LC257
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_StartHwRepair
	.type	VDMHAL_V4R3C1_StartHwRepair, %function
VDMHAL_V4R3C1_StartHwRepair:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC259
	ldrb	w4, [x21]
	cmp	w4, 1
	bne	.L617
	cmp	w20, wzr
	ble	.L618
	ldr	x22, .LC261
	mov	w3, w20
	ldr	x23, .LC262
	mov	w0, 32
	add	x2, x22, 392
	mov	x1, x23
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L601
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L614
.L596:
	cbz	x19, .L619
.L610:
	ldr	x1, .LC265
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
.L593:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L618:
	sxtw	x0, w20
	ldr	x3, .LC260
	lsl	x1, x0, 6
	mov	w4, 67108864
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x2, x1, x0
	add	x1, x1, x2, lsl 2
	ldr	x1, [x3, x1]
	str	w4, [x1, 8]
.L599:
	lsl	x1, x0, 6
	mov	w2, -2
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x3, x0]
	str	w2, [x0, 36]
.L597:
	ldr	x0, .LC266
	ldr	x0, [x0, 224]
	blr	x0
	cmp	w20, wzr
	ble	.L613
	ldr	x22, .LC261
	ldr	x23, .LC262
.L606:
	add	x22, x22, 408
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
	b	.L593
	.p2align 3
.L595:
	cmp	w20, wzr
	ble	.L611
	ldr	x22, .LC261
	ldr	x23, .LC262
.L601:
	mov	w4, 1
	mov	w3, w20
	add	x2, x22, 392
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	bne	.L596
.L614:
	ldr	x0, .LC266
	ldr	x0, [x0, 224]
	blr	x0
	b	.L606
	.p2align 3
.L617:
	mov	x0, x19
	mov	w3, 67108864
	mov	w2, 8
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L595
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L597
	cbnz	x19, .L610
.L619:
	ldr	x2, .LC261
	mov	x3, 0
	ldr	x1, .LC264
	mov	w0, 0
	add	x2, x2, 408
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L613:
	lsl	x0, x20, 6
	ldr	x1, .LC260
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
	b	.L593
.L611:
	ldr	x3, .LC260
	sxtw	x0, w20
	b	.L599
	.size	VDMHAL_V4R3C1_StartHwRepair, .-VDMHAL_V4R3C1_StartHwRepair
	.align	3
.LC259:
	.xword	g_HalDisable
	.align	3
.LC260:
	.xword	g_HwMem
	.align	3
.LC261:
	.xword	.LANCHOR1
	.align	3
.LC262:
	.xword	.LC102
	.align	3
.LC264:
	.xword	.LC263
	.align	3
.LC265:
	.xword	g_VdmDrvParam
	.align	3
.LC266:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_CalVdhClkSkip
	.type	VDMHAL_V4R3C1_CalVdhClkSkip, %function
VDMHAL_V4R3C1_CalVdhClkSkip:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	bl	_mcount
	ldr	x24, .LC268
	ldr	w28, [x24, 128]
	tbnz	w28, #31, .L652
	ldr	x25, .LC271
	add	x20, x24, 132
	ldr	x27, .LC274
	add	x24, x24, 256
	ldr	x26, .LC273
	mov	w23, 30
	mov	w22, 0
	mov	w21, 0
	add	x25, x25, 440
	mov	w19, 0
	b	.L623
	.p2align 3
.L655:
	mov	w3, w28
	mov	x2, x25
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
.L625:
	cmp	x24, x20
	beq	.L653
.L642:
	ldr	w28, [x20], 4
	tbnz	w28, #31, .L654
.L623:
	mov	w0, w28
	bl	VCTRL_IsChanActive
	cbnz	w0, .L655
	mov	w0, w28
	bl	FSP_GetInst
	cbz	x0, .L626
	ldp	w1, w0, [x0, 40]
	adds	w19, w1, 15
	add	w1, w1, 30
	add	w21, w0, 30
	csel	w19, w1, w19, mi
	adds	w0, w0, 15
	asr	w19, w19, 4
	csel	w0, w21, w0, mi
	asr	w21, w0, 4
.L626:
	ldr	x1, [x27, w28, sxtw 3]
	mov	w0, w28
	ldr	w1, [x1, 1640]
	cmp	w1, 31
	csel	w23, w23, w1, lt
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	bls	.L656
.L645:
	cmp	x24, x20
	mov	w22, 0
	bne	.L642
.L653:
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
.L656:
	ldr	x1, .LC275
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx629
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx629:
	.section	.rodata
	.align	0
	.align	2
.L629:
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L645 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L645 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L645 - .Lrtx629) / 4
	.byte	(.L639 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.byte	(.L638 - .Lrtx629) / 4
	.text
	.p2align 3
.L638:
	mul	w22, w19, w21
	mul	w22, w22, w23
	b	.L625
	.p2align 3
.L654:
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
.L621:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L639:
	mul	w22, w19, w21
	mul	w22, w22, w23
	lsl	w22, w22, 1
	b	.L625
.L652:
	mov	w0, 25
	b	.L621
	.size	VDMHAL_V4R3C1_CalVdhClkSkip, .-VDMHAL_V4R3C1_CalVdhClkSkip
	.align	3
.LC268:
	.xword	g_ChanCtx
	.align	3
.LC271:
	.xword	.LANCHOR1
	.align	3
.LC273:
	.xword	.LC272
	.align	3
.LC274:
	.xword	s_pstVfmwChan
	.align	3
.LC275:
	.xword	.L629
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetVdmClk
	.type	VDMHAL_V4R3C1_GetVdmClk, %function
VDMHAL_V4R3C1_GetVdmClk:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 3
	bls	.L665
.L658:
	ldr	x0, .LC278
	sbfiz	x19, x19, 6, 32
	mov	w1, 500
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L665:
	ldr	x0, .LC277
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx660
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx660:
	.section	.rodata
	.align	0
	.align	2
.L660:
	.byte	(.L658 - .Lrtx660) / 4
	.byte	(.L661 - .Lrtx660) / 4
	.byte	(.L662 - .Lrtx660) / 4
	.byte	(.L663 - .Lrtx660) / 4
	.text
	.p2align 3
.L662:
	ldr	x0, .LC278
	sbfiz	x19, x19, 6, 32
	mov	w1, 100
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L661:
	ldr	x0, .LC278
	sbfiz	x19, x19, 6, 32
	mov	w1, 540
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L663:
	ldr	x0, .LC278
	sbfiz	x19, x19, 6, 32
	mov	w1, 600
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V4R3C1_GetVdmClk, .-VDMHAL_V4R3C1_GetVdmClk
	.align	3
.LC277:
	.xword	.L660
	.align	3
.LC278:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_StartHwDecode
	.type	VDMHAL_V4R3C1_StartHwDecode, %function
VDMHAL_V4R3C1_StartHwDecode:
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
	ble	.L667
	ldr	x2, .LC279
	mov	w4, 0
	ldr	x1, .LC280
	mov	w3, w20
	add	x2, x2, 472
	mov	w0, 0
	bl	dprint_vfmw
.L666:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L667:
	ldr	x21, .LC281
	ldrb	w0, [x21]
	cmp	w0, 1
	bne	.L701
	ldr	x1, .LC284
	ldr	x2, [x1]
	ldr	w0, [x2, 120]
	ubfx	x3, x0, 8, 2
	cbz	w3, .L672
	and	w0, w0, -769
	str	w0, [x2, 120]
.L672:
	ldr	x24, .LC282
	sxtw	x22, w20
	ldr	x2, .LC283
	mov	w3, 500
	add	x0, x24, x22, lsl 6
	ldr	w23, [x0, 8]
	str	w3, [x0, 16]
	ldr	x0, [x2, w23, sxtw 3]
	ldr	w25, [x0, 1312]
.L671:
	ldr	x0, [x1]
	ldr	w1, [x0, 120]
	and	w1, w1, -258049
	str	w1, [x0, 120]
	ldr	w1, [x0, 120]
	orr	w1, w1, 131072
	str	w1, [x0, 120]
.L673:
	mov	w0, 12
	mov	x3, x19
	mov	w2, w20
	mov	w1, 3
	bl	SCD_ConfigReg
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L702
	mov	w1, 2
	mov	x0, x19
	mov	w3, -1431655766
	mov	w2, 156
	bl	VDH_Record_RegData
	ldr	x1, .LC285
	ldrb	w0, [x21]
	ldr	w1, [x1]
	cmp	w1, 1
	beq	.L703
.L675:
	mov	w3, 0
.L674:
	cmp	w0, 1
	beq	.L704
	mov	x0, x19
	mov	w2, 61472
	mov	w1, 2
	bl	VDH_Record_RegData
	cmp	w25, 1
	ldrb	w0, [x21]
	beq	.L705
.L678:
	mov	w3, -2
.L677:
	cmp	w0, 1
	beq	.L706
	mov	x0, x19
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L707
	cbz	x19, .L708
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
.L705:
	mov	w3, -6
	b	.L677
	.p2align 3
.L703:
	mov	w3, 7
	b	.L674
	.p2align 3
.L701:
	mov	w3, 0
	mov	w2, 0
	mov	w1, 0
	mov	x0, x19
	sxtw	x22, w20
	bl	VDH_Record_RegData
	ldr	x24, .LC282
	ldr	x1, .LC283
	mov	w2, 500
	add	x0, x24, x22, lsl 6
	ldrb	w3, [x21]
	cmp	w3, 1
	ldr	w23, [x0, 8]
	str	w2, [x0, 16]
	ldr	x0, [x1, w23, sxtw 3]
	ldr	w25, [x0, 1312]
	beq	.L709
	mov	w3, 0
	mov	w2, 1
	mov	w1, 0
	mov	x0, x19
	bl	VDH_Record_RegData
	b	.L673
	.p2align 3
.L702:
	ldr	x2, .LC285
	lsl	x1, x22, 6
	sub	x1, x1, x22
	ldr	x26, .LC286
	lsl	x1, x1, 2
	ldr	w2, [x2]
	cmp	w2, 1
	sub	x2, x1, x22
	add	x1, x1, x2, lsl 2
	mov	w2, -1431655766
	ldr	x1, [x26, x1]
	str	w2, [x1, 156]
	bne	.L675
	mov	w3, 7
	b	.L676
	.p2align 3
.L704:
	ldr	x26, .LC286
.L676:
	lsl	x0, x22, 6
	cmp	w25, 1
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x0, [x26, x0]
	add	x0, x0, 61440
	str	w3, [x0, 32]
	beq	.L691
	mov	w0, 1
	b	.L678
	.p2align 3
.L706:
	ldr	x26, .LC286
.L679:
	lsl	x1, x22, 6
	ldr	x19, .LC287
	sub	x1, x1, x22
	mov	x0, 30
	lsl	x1, x1, 2
	sub	x2, x1, x22
	add	x1, x1, x2, lsl 2
	ldr	x1, [x26, x1]
	str	w3, [x1, 36]
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
.L682:
	lsl	x0, x22, 6
	mov	w2, 1
	sub	x1, x0, x22
	add	x24, x24, x0
	lsl	x0, x1, 2
	ldr	x3, .LC289
	sub	x22, x0, x22
	mov	w1, 4
	add	x22, x0, x22, lsl 2
	ldr	x0, [x26, x22]
	str	wzr, [x0]
	ldr	x0, [x26, x22]
	str	w2, [x0]
	ldr	x0, [x26, x22]
	str	wzr, [x0]
	ldr	w2, [x24, 8]
	mov	w0, w2
	ldr	w2, [x3, w2, sxtw 2]
	bl	VDEC_Lowdelay_Event_Time
	b	.L666
	.p2align 3
.L708:
	ldr	x2, .LC279
	mov	x3, 0
	ldr	x1, .LC288
	mov	w0, 0
	add	x2, x2, 472
	bl	dprint_vfmw
	b	.L666
	.p2align 3
.L691:
	mov	w3, -6
	b	.L679
.L709:
	ldr	x1, .LC284
	b	.L671
.L707:
	ldr	x19, .LC287
	mov	x0, 30
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
	ldr	x26, .LC286
	b	.L682
	.size	VDMHAL_V4R3C1_StartHwDecode, .-VDMHAL_V4R3C1_StartHwDecode
	.align	3
.LC279:
	.xword	.LANCHOR1
	.align	3
.LC280:
	.xword	.LC88
	.align	3
.LC281:
	.xword	g_HalDisable
	.align	3
.LC282:
	.xword	g_VdmDrvParam
	.align	3
.LC283:
	.xword	s_pstVfmwChan
	.align	3
.LC284:
	.xword	g_pstRegCrg
	.align	3
.LC285:
	.xword	mask_mmu_err_int
	.align	3
.LC286:
	.xword	g_HwMem
	.align	3
.LC287:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC288:
	.xword	.LC263
	.align	3
.LC289:
	.xword	g_LowDelaySeqIndex
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_GetCharacter
	.type	VDMHAL_V4R3C1_GetCharacter, %function
VDMHAL_V4R3C1_GetCharacter:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC290
	mov	w3, 15
	ldr	x0, .LC291
	mov	w1, 4
	str	w3, [x2]
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V4R3C1_GetCharacter, .-VDMHAL_V4R3C1_GetCharacter
	.align	3
.LC290:
	.xword	g_VdmCharacter
	.align	3
.LC291:
	.xword	g_eVdmVersion
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V4R3C1_WriteBigTitle1DYuv
	.type	VDMHAL_V4R3C1_WriteBigTitle1DYuv, %function
VDMHAL_V4R3C1_WriteBigTitle1DYuv:
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
	beq	.L755
	mov	w20, 2
	cmp	w0, w20
	csinc	w20, w20, wzr, ne
.L712:
	ldr	x0, [x29, 112]
	cbz	x0, .L711
	ldr	x0, .LC293
	mov	w4, 0
	add	x3, x29, 144
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L715
	ldr	x0, .LC297
	mov	w4, 0
	add	x3, x29, 176
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L715
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
	bne	.L716
	lsr	w1, w3, 1
	lsr	w0, w19, 1
	str	w1, [x29, 120]
	add	x1, x25, 2097152
	str	w0, [x29, 104]
	str	x1, [x29, 136]
	ldr	x28, .LC298
	ldr	x20, [x29, 152]
	cbz	w3, .L718
	mov	w27, 0
	str	wzr, [x29, 132]
	.p2align 2
.L717:
	cbz	w19, .L720
	ldr	w0, [x29, 124]
	lsr	w23, w27, 4
	ldr	w24, [x29, 132]
	mov	w26, 0
	mul	w0, w23, w0
	ubfiz	x23, x27, 8, 4
	add	x23, x0, x23
	.p2align 2
.L719:
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
	bhi	.L719
.L720:
	ldr	w0, [x29, 132]
	add	w27, w27, 1
	add	w0, w0, w19
	str	w0, [x29, 132]
	ldr	w0, [x29, 128]
	cmp	w0, w27
	bne	.L717
.L718:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	blr	x3
	ldr	w0, [x29, 120]
	cbz	w0, .L810
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 132]
	.p2align 2
.L724:
	cbz	w19, .L726
	ldr	w0, [x29, 132]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L723:
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
	bhi	.L723
.L726:
	ldr	w0, [x29, 120]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L724
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L811
.L752:
	ldr	w0, [x29, 108]
	cbnz	w0, .L729
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
.L729:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 120]
.L805:
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
.L711:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L715:
	ldr	x1, .LC295
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
.L755:
	mov	w20, 0
	b	.L712
.L716:
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
	ldr	x28, .LC298
	ldr	x20, [x29, 152]
	bls	.L734
	ldr	w27, [x29, 120]
	.p2align 2
.L736:
	cbz	w19, .L737
	ldr	w0, [x29, 124]
	lsr	w24, w27, 4
	lsr	w23, w27, 1
	mov	w26, 0
	mul	w0, w24, w0
	mul	w23, w23, w19
	ubfiz	x24, x27, 8, 4
	add	x24, x0, x24
	.p2align 2
.L735:
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
	bhi	.L735
.L737:
	ldr	w0, [x29, 128]
	add	w27, w27, 2
	cmp	w0, w27
	bhi	.L736
.L734:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	lsr	w1, w1, 1
	blr	x3
	ldr	w0, [x29, 132]
	cbz	w0, .L812
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 128]
	.p2align 2
.L741:
	cbz	w19, .L743
	ldr	w0, [x29, 128]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L740:
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
	bhi	.L740
.L743:
	ldr	w0, [x29, 132]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L741
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L813
	ldr	w0, [x29, 108]
	cbnz	w0, .L746
	ldr	w1, [x29, 120]
	ldr	w0, [x29, 132]
	cmp	w0, w1
	bls	.L749
	.p2align 2
.L750:
	ldr	w0, [x29, 120]
	ldr	w1, [x29, 132]
	add	w0, w0, 2
	str	w0, [x29, 120]
	cmp	w1, w0
	bhi	.L750
.L749:
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
.L746:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 132]
	b	.L805
.L811:
	mov	w0, 0
	mov	w6, 0
	.p2align 2
.L728:
	ldr	w1, [x29, 104]
	mov	w5, w0
	cbz	w1, .L730
	ldr	w1, [x29, 104]
	add	w5, w1, w0
	mov	w1, 1
	.p2align 2
.L727:
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
	bne	.L727
.L730:
	ldr	w0, [x29, 120]
	add	w6, w6, 1
	add	x20, x20, x19
	cmp	w0, w6
	mov	w0, w5
	bne	.L728
	b	.L729
.L813:
	ldr	w0, [x29, 120]
	mov	w7, 0
	mul	w1, w19, w0
	lsl	w0, w19, 1
	add	x20, x20, x1
	.p2align 2
.L745:
	ldr	w3, [x29, 104]
	cbz	w3, .L747
	lsr	w1, w7, 1
	mov	w2, 1
	mul	w1, w1, w3
	add	w6, w3, w1
	.p2align 2
.L744:
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
	bne	.L744
.L747:
	ldr	w1, [x29, 132]
	add	w7, w7, 2
	add	x20, x20, x0
	cmp	w1, w7
	bhi	.L745
	b	.L746
.L812:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L746
	ldr	w0, [x29, 108]
	cbz	w0, .L749
	b	.L746
.L810:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	bne	.L752
	b	.L729
	.size	VDMHAL_V4R3C1_WriteBigTitle1DYuv, .-VDMHAL_V4R3C1_WriteBigTitle1DYuv
	.align	3
.LC293:
	.xword	.LC292
	.align	3
.LC295:
	.xword	.LC294
	.align	3
.LC297:
	.xword	.LC296
	.align	3
.LC298:
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
	ldr	x0, .LC299
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L821
	cbnz	w19, .L817
	ldr	x0, .LC300
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	ubfx	x2, x0, 8, 2
	cmp	w20, w2
	beq	.L814
	bfi	w0, w20, 8, 2
	str	w0, [x1, 120]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L817:
	cmp	w19, 1
	beq	.L822
.L814:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L821:
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
.L822:
	ldr	x0, .LC300
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	bfi	w0, w20, 12, 5
	and	w0, w0, -131073
	str	w0, [x1, 120]
	ldr	w0, [x1, 120]
	orr	w0, w0, 131072
	str	w0, [x1, 120]
	b	.L814
	.size	CRG_ConfigReg, .-CRG_ConfigReg
	.align	3
.LC299:
	.xword	g_HalDisable
	.align	3
.LC300:
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
	ldr	x0, .LC301
	ldrb	w4, [x0]
	cmp	w4, 1
	bne	.L827
	cmp	w19, wzr
	ble	.L828
	ldr	x2, .LC303
	mov	w3, w19
	ldr	x1, .LC304
	mov	w0, 32
	add	x2, x2, 392
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L828:
	lsl	x0, x19, 6
	ldr	x1, .LC302
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
.L827:
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
.LC301:
	.xword	g_HalDisable
	.align	3
.LC302:
	.xword	g_HwMem
	.align	3
.LC303:
	.xword	.LANCHOR1
	.align	3
.LC304:
	.xword	.LC102
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.53700, %object
	.size	__func__.53700, 22
__func__.53700:
	.string	"VDMHAL_V4R3C1_OpenHAL"
	.zero	2
	.type	__func__.53774, %object
	.size	__func__.53774, 25
__func__.53774:
	.string	"VDMHAL_V4R3C1_CalcFsSize"
	.zero	7
	.type	__func__.53800, %object
	.size	__func__.53800, 24
__func__.53800:
	.string	"VDMHAL_V4R3C1_CalcFsNum"
	.type	__func__.53842, %object
	.size	__func__.53842, 32
__func__.53842:
	.string	"VDMHAL_V4R3C1_ArrangeMem_Normal"
	.type	__FUNCTION__.53843, %object
	.size	__FUNCTION__.53843, 32
__FUNCTION__.53843:
	.string	"VDMHAL_V4R3C1_ArrangeMem_Normal"
	.type	__func__.53786, %object
	.size	__func__.53786, 33
__func__.53786:
	.string	"VDMHAL_V4R3C1_FillMemArrangeInfo"
	.zero	7
	.type	__func__.53923, %object
	.size	__func__.53923, 34
__func__.53923:
	.string	"VDMHAL_V4R3C1_ArrangeMem_Specific"
	.zero	6
	.type	__func__.53947, %object
	.size	__func__.53947, 23
__func__.53947:
	.string	"VDMHAL_V4R3C1_ResetVdm"
	.zero	1
	.type	__func__.53957, %object
	.size	__func__.53957, 35
__func__.53957:
	.string	"VDMHAL_V4R3C1_SetSmmuPageTableAddr"
	.zero	5
	.type	__func__.53978, %object
	.size	__func__.53978, 24
__func__.53978:
	.string	"VDMHAL_V4R3C1_GlbResetX"
	.type	__func__.53967, %object
	.size	__func__.53967, 23
__func__.53967:
	.string	"VDMHAL_V4R3C1_GlbReset"
	.zero	1
	.type	__func__.53990, %object
	.size	__func__.53990, 28
__func__.53990:
	.string	"VDMHAL_V4R3C1_ClearIntState"
	.zero	4
	.type	__func__.53996, %object
	.size	__func__.53996, 31
__func__.53996:
	.string	"VDMHAL_V4R3C1_ClearMMUIntState"
	.zero	1
	.type	__func__.54002, %object
	.size	__func__.54002, 22
__func__.54002:
	.string	"VDMHAL_V4R3C1_MaskInt"
	.zero	2
	.type	__func__.54015, %object
	.size	__func__.54015, 24
__func__.54015:
	.string	"VDMHAL_V4R3C1_EnableInt"
	.type	__func__.54024, %object
	.size	__func__.54024, 23
__func__.54024:
	.string	"VDMHAL_V4R3C1_CheckReg"
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.54038, %object
	.size	__func__.54038, 26
__func__.54038:
	.string	"VDMHAL_V4R3C1_ReadMMUMask"
	.zero	6
	.type	__func__.54043, %object
	.size	__func__.54043, 27
__func__.54043:
	.string	"VDMHAL_V4R3C1_WriteMMUMask"
	.zero	5
	.type	__func__.54074, %object
	.size	__func__.54074, 25
__func__.54074:
	.string	"VDMHAL_V4R3C1_PrepareDec"
	.zero	7
	.type	__func__.54079, %object
	.size	__func__.54079, 25
__func__.54079:
	.string	"VDMHAL_V4R3C1_IsVdmReady"
	.zero	7
	.type	__func__.54084, %object
	.size	__func__.54084, 23
__func__.54084:
	.string	"VDMHAL_V4R3C1_IsVdmRun"
	.zero	1
	.type	__func__.54090, %object
	.size	__func__.54090, 27
__func__.54090:
	.string	"VDMHAL_V4R3C1_IsVdhDecOver"
	.zero	5
	.type	__func__.54100, %object
	.size	__func__.54100, 31
__func__.54100:
	.string	"VDMHAL_V4R3C1_IsVdhPartDecOver"
	.zero	1
	.type	__func__.54115, %object
	.size	__func__.54115, 33
__func__.54115:
	.string	"VDMHAL_V4R3C1_UpdateHardwareInfo"
	.zero	7
	.type	__func__.54188, %object
	.size	__func__.54188, 23
__func__.54188:
	.string	"VDMHAL_V4R3C1_CfgRpMsg"
	.zero	1
	.type	__func__.54165, %object
	.size	__func__.54165, 24
__func__.54165:
	.string	"VDMHAL_CfgNotFullRepair"
	.type	__func__.54199, %object
	.size	__func__.54199, 23
__func__.54199:
	.string	"VDMHAL_V4R3C1_CfgRpReg"
	.zero	1
	.type	__func__.54212, %object
	.size	__func__.54212, 28
__func__.54212:
	.string	"VDMHAL_V4R3C1_MakeDecReport"
	.zero	4
	.type	__func__.54251, %object
	.size	__func__.54251, 28
__func__.54251:
	.string	"VDMHAL_V4R3C1_PrepareRepair"
	.zero	4
	.type	__func__.54438, %object
	.size	__func__.54438, 15
__func__.54438:
	.string	"MFDE_ConfigReg"
	.zero	1
	.type	__func__.54258, %object
	.size	__func__.54258, 28
__func__.54258:
	.string	"VDMHAL_V4R3C1_StartHwRepair"
	.zero	4
	.type	__func__.54297, %object
	.size	__func__.54297, 28
__func__.54297:
	.string	"VDMHAL_V4R3C1_CalVdhClkSkip"
	.zero	4
	.type	__func__.54320, %object
	.size	__func__.54320, 28
__func__.54320:
	.string	"VDMHAL_V4R3C1_StartHwDecode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC3:
	ASCII(.string	"pOpenParam = NULL error!" )
	.zero	7
.LC6:
	ASCII(.string	"%s: %s\n" )
.LC8:
	ASCII(.string	"MemBaseAddr = 0 error!" )
	.zero	1
.LC10:
	ASCII(.string	"VDMHAL_V4R3C1_OpenHAL: Size error!" )
	.zero	5
.LC12:
	ASCII(.string	"VdhId is wrong!!!\n" )
	.zero	5
.LC16:
	ASCII(.string	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\n" )
	.zero	7
.LC18:
	ASCII(.string	"BPDRegVirAddr %p\n" )
	.zero	6
.LC20:
	ASCII(.string	"!!!!!! HAL memory not enouph! need %d, have %d\n" )
.LC22:
	ASCII(.string	"image size out of range" )
.LC29:
	ASCII(.string	"VDMHAL ArrangeMem HEVC 10 bit\n" )
	.zero	1
.LC32:
	ASCII(.string	"%s pstVfmwFrameSizeInfo = NULL\n" )
.LC36:
	ASCII(.string	"DelAllFrameMemRecord err in VDMHAL_V4R3C1_ArrangeMem!\n" )
	.zero	1
.LC38:
	ASCII(.string	"Report arrange frame buffer: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	3
.LC43:
	ASCII(.string	"Report arrange frame buffer only: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	6
.LC46:
	ASCII(.string	"VidStd Invalid" )
	.zero	1
.LC51:
	ASCII(.string	"Set CompressEn %d, LossCompressEn %d, YCompRatio %d, UVCompRatio %d\n" )
	.zero	3
.LC53:
	ASCII(.string	"VDMHAL_V4R3C1_CalcFsSize err!\n" )
	.zero	1
.LC55:
	ASCII(.string	"%s, need arrange, Size: %#x, Num: %#x, RefChanged: %#x\n" )
.LC57:
	ASCII(.string	"DFS, report event. Size: 0x%x, Num: %d, RefChanged: %d\n" )
.LC60:
	ASCII(.string	"pVdmMemArrange is NULL" )
	.zero	1
.LC62:
	ASCII(.string	"DFS, no ref frame!\n" )
	.zero	4
.LC64:
	ASCII(.string	"DFS, Frame number = %d > 30, Then, Frame num = 30, \n" )
	.zero	3
.LC66:
	ASCII(.string	"VDMHAL_V4R3C1_ArrangeMem Mem addr is NULL" )
	.zero	6
.LC71:
	ASCII(.string	"'pVdmMemArrange' is NULL" )
	.zero	7
.LC75:
	ASCII(.string	"MemSize not enough for pmv slot" )
.LC78:
	ASCII(.string	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight failed!\n" )
	.zero	3
.LC80:
	ASCII(.string	"ImgSlotLen > ChanSlotLen" )
	.zero	7
.LC83:
	ASCII(.string	"cann't allocate img slot" )
	.zero	7
.LC88:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC90:
	ASCII(.string	"VDMHAL_V4R3C1_ResetVdm: map vdm register fail, vir(reg) = (%p)\n" )
.LC95:
	ASCII(.string	"%s module id %d failed!\n" )
	.zero	7
.LC97:
	ASCII(.string	"%s module id %d success!\n" )
	.zero	6
.LC102:
	ASCII(.string	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC107:
	ASCII(.string	"%s: map vdm register 0x%x failed!\n" )
	.zero	5
.LC111:
	ASCII(.string	"%s VdhId %d failed!\n" )
	.zero	3
.LC113:
	ASCII(.string	"%s VdhId %d success!\n" )
	.zero	2
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
.LC157:
	ASCII(.string	"%s: VdhId(%d)overgrown its limits\n" )
	.zero	5
.LC161:
	ASCII(.string	"VDM register not mapped yet!" )
	.zero	3
.LC167:
	ASCII(.string	"VDM register not mapped yet!\n" )
	.zero	2
.LC189:
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
	ASCII(.string	"VDMHAL_V4R3C1_CfgRpMsg error! pRepairParam=%p, pHwMem=%p\n" )
	.zero	6
.LC202:
	ASCII(.string	"can not map repair msg virtual address!" )
.LC206:
	ASCII(.string	"ValidGroupNum=%d out of range!\n" )
.LC208:
	ASCII(.string	"align_mb error\n" )
.LC210:
	ASCII(.string	"[%s][%d]sclie_num is wrong! %d \n" )
	.zero	7
.LC212:
	ASCII(.string	"VDMHAL_V4R3C1_CfgRpReg error! pDecParam=%p, pHwMem=%p\n" )
	.zero	1
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
.LC248:
	ASCII(.string	"VDMHAL_V4R3C1_PrepareRepair error! pDecParam=%p\n" )
	.zero	7
.LC252:
	ASCII(.string	"vdm register virtual address not mapped, VDMHAL_V200R003_PrepareRepair failed!\n" )
.LC255:
	ASCII(.string	"FIRST_REPAIR Parameter Error!\n" )
	.zero	1
.LC257:
	ASCII(.string	"SECOND_REPAIR Parameter Error!\n" )
.LC263:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC272:
	ASCII(.string	"%s The channel %d is not active\n" )
	.zero	7
.LC292:
	ASCII(.string	"BigTile1d_y" )
	.zero	4
.LC294:
	ASCII(.string	"failed mem_allocMemBlock BigTile_yuv save!\n" )
	.zero	4
.LC296:
	ASCII(.string	"BigTile1d_uv" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
