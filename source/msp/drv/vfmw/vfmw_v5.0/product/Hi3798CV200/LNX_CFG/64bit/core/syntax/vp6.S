#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vp6.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	Vp6_Vfmw_DecodeBool
	.type	Vp6_Vfmw_DecodeBool, %function
Vp6_Vfmw_DecodeBool:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x1
	mov	x22, x0
	mov	x0, x30
	uxtb	w19, w2
	mov	w23, 0
	bl	_mcount
	ldp	w1, w20, [x21, 4]
	sub	w0, w1, #1
	mul	w19, w0, w19
	lsr	w19, w19, 8
	add	w19, w19, 1
	lsl	w0, w19, 16
	cmp	w20, w0
	bcc	.L2
	sub	w19, w1, w19
	sub	w20, w20, w0
	mov	w23, 1
.L2:
	cmp	w19, 127
	bhi	.L9
	ldr	w1, [x21, 12]
	b	.L6
	.p2align 3
.L5:
	cmp	w19, 127
	bhi	.L11
.L6:
	subs	w1, w1, #1
	lsl	w19, w19, 1
	lsl	w20, w20, 1
	bne	.L5
	mov	w1, 8
	mov	x0, x22
	bl	BsGet
	orr	w20, w20, w0
	cmp	w19, 127
	mov	w1, 8
	bls	.L6
.L11:
	str	w1, [x21, 12]
.L9:
	stp	w19, w20, [x21, 4]
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp6_Vfmw_DecodeBool, .-Vp6_Vfmw_DecodeBool
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp6_Vfmw_DecodeBool128
	.type	Vp6_Vfmw_DecodeBool128, %function
Vp6_Vfmw_DecodeBool128:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x1
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldp	w20, w1, [x19, 4]
	ldr	w2, [x19, 12]
	add	w0, w20, 1
	lsr	w0, w0, 1
	lsl	w21, w0, 16
	cmp	w1, w21
	bcc	.L13
	sub	w0, w20, w0
	sub	w1, w1, w21
	lsl	w20, w0, 1
	lsl	w21, w1, 1
	mov	w23, 1
.L14:
	subs	w2, w2, #1
	bne	.L15
	mov	w1, 8
	mov	x0, x22
	bl	BsGet
	orr	w21, w21, w0
	mov	w2, 8
.L15:
	stp	w20, w21, [x19, 4]
	str	w2, [x19, 12]
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L13:
	lsl	w20, w0, 1
	lsl	w21, w1, 1
	mov	w23, 0
	b	.L14
	.size	Vp6_Vfmw_DecodeBool128, .-Vp6_Vfmw_DecodeBool128
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp6_Vfmw_BoolRead
	.type	Vp6_Vfmw_BoolRead, %function
Vp6_Vfmw_BoolRead:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	x22, x1
	bl	_mcount
	mov	w20, 0
	subs	w19, w19, #1
	bmi	.L17
	.p2align 2
.L18:
	mov	x1, x22
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w20, w0, w20
	cmn	w19, #1
	bne	.L18
.L17:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp6_Vfmw_BoolRead, .-Vp6_Vfmw_BoolRead
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp6_Vfmw_StartDecode
	.type	Vp6_Vfmw_StartDecode, %function
Vp6_Vfmw_StartDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w1, 255
	mov	w0, 8
	stp	wzr, w1, [x19]
	str	w0, [x19, 12]
	mov	w1, 24
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp6_Vfmw_StartDecode, .-Vp6_Vfmw_StartDecode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_ArrangeVHBMem
	.type	VP6_ArrangeVHBMem, %function
VP6_ArrangeVHBMem:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 12288
	bl	_mcount
	add	x0, x20, 284
	ldp	w3, w2, [x0, 28]
	cmp	w3, 2
	bls	.L24
	sub	w1, w2, #3
	mov	w0, 512
	cmp	w1, 509
	ccmp	w3, w0, 2, ls
	bhi	.L24
	ldr	x1, [x19]
	ldr	w0, [x1, 772]
	cbnz	w0, .L27
	ldr	w0, [x1, 28]
	cmp	w0, 25
	beq	.L55
.L28:
	mov	w21, 3
	lsl	w23, w2, 4
	lsl	w22, w3, 4
	mov	w25, 5
	mov	w24, w21
.L33:
	ldr	x0, .LC4
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x19]
	stp	w23, w22, [x29, 92]
	stp	w23, w22, [x29, 100]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L39
	strb	w24, [x29, 89]
	sxtb	w21, w21
	strb	w25, [x29, 90]
.L44:
	ldr	w0, [x19, 13368]
	add	x1, x29, 88
	strb	w21, [x29, 91]
	bl	FSP_ConfigInstance
	cbnz	w0, .L40
	ldr	x1, [x19]
	add	x3, x29, 84
	ldr	w0, [x19, 13368]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L56
	cbnz	w0, .L42
	mov	w0, 1
	str	w0, [x19, 12388]
	b	.L48
	.p2align 3
.L24:
	ldr	x1, .LC1
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
.L48:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L27:
	ldr	w0, [x1, 28]
	cmp	w0, 25
	bne	.L28
	ldr	w4, [x1, 732]
	lsl	w2, w2, 4
	cmp	w2, w4
	bhi	.L57
	ldr	w5, [x1, 736]
	lsl	w3, w3, 4
	cmp	w3, w5
	bhi	.L36
	ldr	w4, [x1, 760]
	mov	w23, w2
	ldr	w0, [x1, 756]
	mov	w22, w3
	mov	w21, 1
	add	w24, w0, 2
	cbz	w4, .L38
.L53:
	add	w21, w0, w21
	mov	w0, 17
	cmp	w21, w0
	csel	w21, w21, w0, le
.L38:
	ldrsb	w25, [x1, 780]
	b	.L33
	.p2align 3
.L40:
	ldr	x1, .LC8
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L48
	.p2align 3
.L39:
	mov	w0, 1
	strb	w25, [x29, 90]
	strb	w0, [x29, 89]
	mov	w21, 1
	b	.L44
	.p2align 3
.L55:
	ldr	w23, [x1, 732]
	lsl	w2, w2, 4
	cmp	w2, w23
	bhi	.L58
	ldr	w22, [x1, 736]
	lsl	w3, w3, 4
	cmp	w3, w22
	bhi	.L59
	ldr	w0, [x19, 12388]
	cmp	w0, 1
	beq	.L48
	ldr	w2, [x1, 760]
	mov	w21, 1
	ldr	w0, [x1, 756]
	add	w24, w0, 2
	cbnz	w2, .L53
	ldrsb	w25, [x1, 780]
	b	.L33
.L57:
	ldr	w5, [x1, 736]
	lsl	w3, w3, 4
.L36:
	ldr	x1, .LC3
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L48
.L56:
	add	x0, x20, 472
	bl	ResetVoQueue
.L42:
	ldr	x1, .LC6
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L48
.L59:
	mov	w5, w22
.L30:
	ldr	x1, .LC3
	mov	w4, w23
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L48
.L58:
	lsl	w3, w3, 4
	ldr	w5, [x1, 736]
	b	.L30
	.size	VP6_ArrangeVHBMem, .-VP6_ArrangeVHBMem
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC6:
	.xword	.LC5
	.align	3
.LC8:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_GetImageBuffer
	.type	VP6_GetImageBuffer, %function
VP6_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 312
	bl	_mcount
	ldr	w0, [x20, 13368]
	mov	w1, 1
	bl	FSP_NewLogicFs
	str	w0, [x19, 12088]
	mov	w1, w0
	tbnz	w0, #31, .L66
	ldr	w0, [x20, 13368]
	bl	FSP_GetLogicFs
	mov	x20, x0
	cbz	x0, .L67
	ldr	x1, .LC14
	mov	w0, 18
	ldr	w2, [x19, 12088]
	bl	dprint_vfmw
	ldr	x0, [x20, 32]
	cbz	x0, .L65
	ldr	x0, [x20, 40]
	cbz	x0, .L65
	ldr	w0, [x0, 24]
	str	w0, [x19, 12104]
	mov	w0, 18
	ldr	x1, .LC16
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 28]
	str	w2, [x19, 12108]
	ldp	x2, x3, [x20, 32]
	ldr	w2, [x2, 8]
	ldr	w3, [x3, 8]
	bl	dprint_vfmw
	mov	w0, 1
.L62:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L65:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L66:
	ldr	x1, .LC10
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x19, 12092]
	mov	w2, 1
	ldr	w0, [x20, 13368]
	bl	FSP_ClearLogicFs
	ldr	w1, [x19, 12096]
	mov	w2, 1
	ldr	w0, [x20, 13368]
	bl	FSP_ClearLogicFs
	str	wzr, [x19, 12092]
	str	wzr, [x19, 12096]
	ldr	w0, [x20, 13368]
	bl	FSP_GetNullLogicFs
	str	wzr, [x19, 12072]
	str	w0, [x19, 12092]
	add	x1, x20, 12288
	str	w0, [x19, 12096]
	add	x1, x1, 472
	ldr	w0, [x20, 13368]
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L67:
	ldr	x1, .LC12
	mov	w2, 636
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L62
	.size	VP6_GetImageBuffer, .-VP6_GetImageBuffer
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
.LC16:
	.xword	.LC15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6DEC_GetImageBuffer
	.type	VP6DEC_GetImageBuffer, %function
VP6DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L75
	ldr	w0, [x19, 13368]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w20, w0
	beq	.L70
	ldr	w0, [x19, 13368]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L76
.L70:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L76:
	add	x1, x19, 12288
	ldr	w0, [x19, 13368]
	add	x1, x1, 472
	bl	FSP_ClearNotInVoQueue
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L75:
	ldr	x1, .LC18
	mov	w2, 659
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP6DEC_GetImageBuffer, .-VP6DEC_GetImageBuffer
	.align	3
.LC18:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_BuildScanOrder
	.type	VP6_BuildScanOrder, %function
VP6_BuildScanOrder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	w5, 1
	strb	wzr, [x19, 960]
	mov	w4, 0
	add	x6, x19, 1089
	.p2align 2
.L78:
	mov	x2, x6
	mov	w0, 1
	b	.L80
	.p2align 3
.L79:
	add	w0, w0, 1
	cmp	w0, 64
	beq	.L88
.L80:
	ldrb	w3, [x2]
	add	x2, x2, 1
	cmp	w3, w4
	bne	.L79
	add	x3, x19, x5, uxtw
	add	w5, w5, 1
	strb	w0, [x3, 960]
	add	w0, w0, 1
	cmp	w0, 64
	bne	.L80
.L88:
	add	w4, w4, 1
	cmp	w4, 16
	bne	.L78
	add	x8, x19, 64
	mov	x7, x19
	.p2align 2
.L81:
	mov	w6, w19
	sub	w5, w7, w19
	mov	x0, x19
	mov	w2, 0
	.p2align 2
.L82:
	ldrb	w3, [x0, 960]
	add	x0, x0, 1
	sub	w4, w0, w6
	cmp	w2, w3
	csel	w2, w2, w3, cs
	cmp	w4, w5
	bls	.L82
	uxtb	w2, w2
	strb	w2, [x7, 1024]
	ldr	w0, [x20, 16]
	cmp	w0, 6
	bls	.L83
	add	w2, w2, 1
	strb	w2, [x7, 1024]
.L83:
	add	x7, x7, 1
	cmp	x8, x7
	bne	.L81
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP6_BuildScanOrder, .-VP6_BuildScanOrder
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_BuildModeTree
	.type	VP6_BuildModeTree, %function
VP6_BuildModeTree:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x15, x19, 44
	add	x16, x19, 10
	mov	x13, x19
	add	x8, x29, 104
	add	x14, x19, 60
	.p2align 2
.L90:
	sub	w7, w13, w19
	mov	x5, x19
	mov	x6, x15
	mov	x12, x13
	mov	x11, x13
.L96:
	mov	x1, 0
	mov	w4, 0
	.p2align 2
.L93:
	cmp	w7, w1
	add	x0, x5, x1
	beq	.L98
	ldrb	w0, [x0, 404]
	lsl	w2, w0, 2
	sub	w2, w2, w0
	lsl	w3, w2, 5
	add	w2, w2, w3
	add	w0, w2, w0
	str	w0, [x8, x1, lsl 2]
.L92:
	add	x1, x1, 1
	add	w4, w4, w0
	cmp	x1, 10
	bne	.L93
	ldrb	w23, [x11, 414]
	add	w4, w4, 1
	ldp	w22, w2, [x29, 104]
	ldp	w1, w21, [x29, 112]
	ldp	w10, w20, [x29, 120]
	ldrb	w24, [x11, 404]
	add	w1, w22, w1
	add	w10, w21, w10
	lsl	w26, w23, 8
	add	w3, w23, 1
	add	w0, w1, w10
	sub	w26, w26, w23
	add	w3, w3, w24
	ldp	w17, w18, [x29, 128]
	lsl	w23, w0, 8
	lsl	w27, w1, 8
	ldp	w30, w9, [x29, 136]
	sub	w23, w23, w0
	sub	w27, w27, w1
	sdiv	w3, w26, w3
	add	w0, w0, 1
	lsl	w26, w22, 8
	add	w17, w20, w17
	add	w18, w2, w18
	sub	w22, w26, w22
	lsl	w26, w2, 8
	add	w9, w30, w9
	lsl	w28, w18, 8
	sub	w26, w26, w2
	lsl	w2, w17, 8
	add	w25, w18, 1
	add	w24, w17, 1
	sub	w18, w28, w18
	lsl	w28, w21, 8
	add	w1, w1, 1
	sub	w21, w28, w21
	add	w10, w10, 1
	udiv	w27, w27, w0
	lsl	w0, w20, 8
	sub	w20, w0, w20
	add	w28, w9, w24
	mvn	w3, w3
	add	x5, x5, 20
	strb	w3, [x12, 4]
	add	w27, w27, 1
	cmp	x14, x5
	strb	w27, [x6, 1]
	add	x11, x11, 20
	add	x12, x12, 10
	add	x6, x6, 90
	udiv	w4, w23, w4
	add	w23, w9, w17
	sub	w17, w2, w17
	lsl	w2, w30, 8
	add	w23, w23, w25
	add	w9, w9, 1
	sub	w2, w2, w30
	add	w4, w4, 1
	strb	w4, [x6, -90]
	udiv	w24, w20, w24
	add	w0, w24, 1
	strb	w0, [x6, -83]
	udiv	w18, w18, w23
	add	w18, w18, 1
	strb	w18, [x6, -88]
	udiv	w1, w22, w1
	add	w1, w1, 1
	strb	w1, [x6, -87]
	udiv	w10, w21, w10
	add	w10, w10, 1
	strb	w10, [x6, -86]
	udiv	w25, w26, w25
	add	w25, w25, 1
	strb	w25, [x6, -85]
	udiv	w17, w17, w28
	add	w17, w17, 1
	strb	w17, [x6, -84]
	udiv	w2, w2, w9
	add	w0, w2, 1
	strb	w0, [x6, -82]
	bne	.L96
	add	x13, x13, 1
	add	x15, x15, 9
	cmp	x16, x13
	bne	.L90
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L98:
	str	wzr, [x8, x1, lsl 2]
	mov	w0, 0
	b	.L92
	.size	VP6_BuildModeTree, .-VP6_BuildModeTree
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_ConfigureContexts
	.type	VP6_ConfigureContexts, %function
VP6_ConfigureContexts:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x16, .LC23
	add	x4, x19, 1152
	mov	w11, 0
	mov	w9, 255
.L100:
	lsl	w12, w11, 2
	mov	x10, x16
	sub	w12, w12, w11
	lsl	w13, w11, 1
	add	w14, w12, 5
	neg	w15, w11, lsl 1
	mov	w7, 0
	mov	w5, 133
	mov	w0, 122
	add	w12, w12, 11
	add	w8, w11, 5
.L106:
	add	x3, x10, 28
	add	w17, w7, w13
	mov	w2, w11
	b	.L104
	.p2align 3
.L101:
	ldr	w0, [x3, -4]
	ldr	w5, [x3], 24
.L104:
	add	x1, x19, x2, uxtw
	add	w6, w17, w2
	add	w2, w2, 1
	ldrb	w1, [x1, 514]
	mul	w0, w1, w0
	add	w0, w0, 128
	add	w0, w5, w0, asr 8
	cmp	w0, 255
	csel	w0, w0, w9, le
	cmp	w0, wzr
	csinc	w0, w0, wzr, gt
	cmp	w8, w2
	strb	w0, [x4, x6]
	bne	.L101
	add	w0, w14, w7
	add	w3, w12, w7
	sub	w2, w15, w7
	.p2align 2
.L102:
	add	w1, w2, w0
	add	x1, x19, x1
	ldrb	w1, [x1, 514]
	strb	w1, [x4, w0, uxtw]
	add	w0, w0, 1
	cmp	w3, w0
	bne	.L102
	add	w7, w7, 11
	add	x10, x10, 8
	cmp	w7, 33
	beq	.L103
	ldp	w0, w5, [x10]
	b	.L106
	.p2align 3
.L103:
	add	w11, w11, 11
	cmp	w11, 22
	bne	.L100
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP6_ConfigureContexts, .-VP6_ConfigureContexts
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_ConfigureEntropyDecoder
	.type	VP6_ConfigureEntropyDecoder, %function
VP6_ConfigureEntropyDecoder:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	mov	w26, w3
	str	x2, [x29, 96]
	bl	_mcount
	add	x25, x29, 144
	ldr	x3, .LC30
	mov	x2, 11
	mov	w1, 128
	mov	x0, x25
	mov	x22, 0
	add	x20, x19, 76
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, .LC31
	mov	w2, 146
	add	x24, x0, 120
.L109:
	mov	x1, x20
	mov	x0, x21
	mov	x19, 0
	str	w22, [x29, 136]
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L110
.L153:
	mov	w28, 0
	mov	w27, 6
	.p2align 2
.L111:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w27
	sub	w27, w27, #1
	orr	w28, w0, w28
	cmn	w27, #1
	bne	.L111
	ldr	w0, [x29, 136]
	ubfiz	w3, w28, 1, 7
	cmp	w3, wzr
	add	w1, w0, w19
	csinc	w3, w3, w3, ne
	add	x1, x23, x1
	uxtb	w0, w3
	strb	w0, [x25, x19]
	strb	w0, [x1, 514]
.L112:
	add	x19, x19, 1
	cmp	x19, 11
	beq	.L152
.L113:
	add	x0, x24, x22
	mov	x1, x20
	ldrb	w2, [x0, x19]
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbnz	w0, .L153
.L110:
	cbnz	w26, .L112
	ldr	w0, [x29, 136]
	ldrb	w1, [x25, x19]
	add	w0, w0, w19
	add	x19, x19, 1
	add	x0, x23, x0
	cmp	x19, 11
	strb	w1, [x0, 514]
	bne	.L113
.L152:
	add	x22, x22, 11
	cmp	x22, 22
	beq	.L114
	ldrb	w2, [x22, x24]
	b	.L109
.L114:
	cbnz	w26, .L116
	ldr	x0, .LC30
	mov	x2, 28
	ldr	x3, [x0, 104]
	ldr	x0, .LC31
	add	x1, x0, 144
	add	x0, x23, 536
	blr	x3
.L116:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	cbz	w0, .L117
	ldr	x0, .LC31
	add	x22, x23, 1089
	mov	w2, 132
	add	x19, x0, 178
	add	x24, x0, 240
	.p2align 2
.L121:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L118
	mov	w28, 0
	mov	w27, 3
.L119:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w27
	sub	w27, w27, #1
	orr	w28, w0, w28
	cmn	w27, #1
	bne	.L119
	strb	w28, [x22]
.L118:
	cmp	x24, x19
	add	x22, x22, 1
	beq	.L120
	ldrb	w2, [x19], 1
	b	.L121
.L120:
	ldr	x1, [x29, 96]
	mov	x0, x23
	bl	VP6_BuildScanOrder
.L117:
	ldr	x0, .LC31
	mov	x22, 0
	mov	w2, 219
	add	x24, x0, 240
.L122:
	mov	x19, 0
	.p2align 2
.L128:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L123
	mov	w28, 0
	mov	w27, 6
	.p2align 2
.L124:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w27
	sub	w27, w27, #1
	orr	w28, w0, w28
	cmn	w27, #1
	bne	.L124
	add	x0, x19, x22
	ubfiz	w2, w28, 1, 7
	add	x0, x23, x0
	cmp	w2, wzr
	csinc	w2, w2, w2, ne
	strb	w2, [x0, 536]
.L123:
	add	x19, x19, 1
	cmp	x19, 14
	beq	.L154
	add	x0, x24, x22
	ldrb	w2, [x0, x19]
	b	.L128
.L154:
	add	x22, x22, 14
	cmp	x22, 28
	beq	.L155
	ldrb	w2, [x22, x24]
	b	.L122
.L155:
	ldr	x0, .LC31
	mov	w2, 227
	str	wzr, [x29, 128]
	add	x0, x0, 272
	str	x0, [x29, 112]
.L127:
	ldr	w0, [x29, 128]
	str	w0, [x29, 132]
	add	w1, w0, 198
	ldr	x0, [x29, 112]
	str	w1, [x29, 108]
	str	x0, [x29, 120]
.L138:
	ldr	x22, [x29, 120]
	str	xzr, [x29, 136]
	.p2align 2
.L136:
	ldp	w0, w1, [x29, 132]
	mov	x19, 0
	add	w24, w0, w1
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L129
	.p2align 2
.L157:
	mov	w28, 0
	mov	w27, 6
	.p2align 2
.L130:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w27
	sub	w27, w27, #1
	orr	w28, w0, w28
	cmn	w27, #1
	bne	.L130
	ubfiz	w3, w28, 1, 7
	add	w1, w24, w19
	cmp	w3, wzr
	add	x1, x23, x1
	csinc	w3, w3, w3, ne
	uxtb	w0, w3
	strb	w0, [x25, x19]
	strb	w0, [x1, 564]
.L131:
	add	x19, x19, 1
	cmp	x19, 11
	beq	.L156
.L132:
	ldrb	w2, [x22, x19]
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbnz	w0, .L157
.L129:
	cbnz	w26, .L131
	add	w0, w24, w19
	ldrb	w1, [x25, x19]
	add	x0, x23, x0
	add	x19, x19, 1
	cmp	x19, 11
	strb	w1, [x0, 564]
	bne	.L132
.L156:
	ldr	x0, [x29, 136]
	add	x22, x22, 11
	add	x0, x0, 11
	str	x0, [x29, 136]
	cmp	x0, 66
	beq	.L133
	ldrb	w2, [x22]
	b	.L136
.L133:
	ldr	x0, [x29, 120]
	ldr	w2, [x29, 108]
	ldr	w1, [x29, 132]
	add	x0, x0, 66
	str	x0, [x29, 120]
	cmp	w1, w2
	beq	.L135
	ldrb	w2, [x0]
	add	w0, w1, 198
	str	w0, [x29, 132]
	b	.L138
.L135:
	ldr	w0, [x29, 128]
	ldr	x1, [x29, 112]
	add	w0, w0, 66
	str	w0, [x29, 128]
	add	x1, x1, 132
	cmp	w0, 198
	str	x1, [x29, 112]
	beq	.L137
	ldrb	w2, [x1]
	b	.L127
.L137:
	ldr	x1, [x29, 96]
	mov	x0, x23
	bl	VP6_ConfigureContexts
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.size	VP6_ConfigureEntropyDecoder, .-VP6_ConfigureEntropyDecoder
	.align	3
.LC30:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC31:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_decodeModeDiff
	.type	VP6_decodeModeDiff, %function
VP6_decodeModeDiff:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x19, x1, 76
	bl	_mcount
	mov	w2, -51
	mov	x1, x19
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbnz	w0, .L168
	mov	w0, 0
.L159:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L168:
	mov	x1, x19
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	neg	w22, w0, lsl 1
	mov	w2, -85
	mov	x1, x19
	mov	x0, x21
	add	w22, w22, 1
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L169
	mov	w2, -57
	mov	x1, x19
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L170
	mov	w23, 0
	mov	w20, 6
	.p2align 2
.L165:
	mov	x1, x19
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w20
	sub	w20, w20, #1
	orr	w23, w0, w23
	cmn	w20, #1
	bne	.L165
	mul	w0, w22, w23
	ldp	x19, x20, [sp, 16]
	lsl	w0, w0, 2
	ldr	x23, [sp, 48]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L170:
	mov	w2, -116
	mov	x1, x19
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L162
	lsl	w0, w22, 2
	sub	w0, w0, w22
	lsl	w0, w0, 2
	b	.L159
	.p2align 3
.L169:
	mov	x1, x19
	mov	w2, 83
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	ldr	x23, [sp, 48]
	mov	w1, 3
	sub	w0, w1, w0
	lsl	w0, w22, w0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L162:
	mov	w2, 125
	mov	x1, x19
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L163
	lsl	w0, w22, 4
	b	.L159
.L163:
	mov	w2, 104
	mov	x1, x19
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L164
	lsl	w0, w22, 4
	add	w0, w0, w22, lsl 2
	b	.L159
.L164:
	lsl	w0, w22, 2
	sub	w0, w0, w22
	lsl	w0, w0, 3
	b	.L159
	.size	VP6_decodeModeDiff, .-VP6_decodeModeDiff
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_DecodeModeProbs
	.type	VP6_DecodeModeProbs, %function
VP6_DecodeModeProbs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	mov	x21, x2
	mov	x19, x1
	bl	_mcount
	ldr	x26, .LC34
	add	x23, x21, 76
	add	x20, x27, 424
	add	x0, x26, 672
	add	x25, x27, 414
	mov	x24, 0
	mov	w28, 20
	str	x0, [x29, 104]
.L178:
	mov	w2, -82
	mov	x1, x23
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L177
	mov	w22, 0
	mov	w26, 3
.L175:
	mov	x1, x23
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w26
	sub	w26, w26, #1
	orr	w22, w0, w22
	cmn	w26, #1
	bne	.L175
	smaddl	x0, w22, w28, x24
	ldr	x2, [x29, 104]
	mov	x1, x25
	add	x0, x2, x0
	.p2align 2
.L176:
	add	x1, x1, 1
	ldrb	w2, [x0]
	add	x0, x0, 2
	cmp	x20, x1
	strb	w2, [x1, -1]
	ldrb	w2, [x0, -1]
	strb	w2, [x1, -11]
	bne	.L176
.L177:
	mov	w2, -2
	mov	x1, x23
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L174
	mov	x26, x25
	mov	w22, 255
	b	.L173
	.p2align 3
.L191:
	cmp	w0, 255
	mov	x1, x21
	csel	w0, w0, w22, le
	uxtb	w0, w0
	strb	w0, [x26]
	mov	x0, x19
	bl	VP6_decodeModeDiff
	ldrb	w1, [x26, -10]
	adds	w0, w1, w0
	bmi	.L184
.L192:
	cmp	w0, 255
	add	x26, x26, 1
	csel	w0, w0, w22, le
	uxtb	w0, w0
	strb	w0, [x26, -11]
	cmp	x26, x20
	beq	.L174
.L173:
	mov	x1, x21
	mov	x0, x19
	bl	VP6_decodeModeDiff
	ldrb	w1, [x26]
	adds	w0, w1, w0
	bpl	.L191
	mov	w0, 0
	mov	x1, x21
	strb	w0, [x26]
	mov	x0, x19
	bl	VP6_decodeModeDiff
	ldrb	w1, [x26, -10]
	adds	w0, w1, w0
	bpl	.L192
.L184:
	mov	w0, 0
	add	x26, x26, 1
	strb	w0, [x26, -11]
	cmp	x26, x20
	bne	.L173
	.p2align 2
.L174:
	add	x24, x24, 320
	add	x20, x20, 20
	cmp	x24, 960
	add	x25, x25, 20
	bne	.L178
	mov	x1, x21
	mov	x0, x27
	bl	VP6_BuildModeTree
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	VP6_DecodeModeProbs, .-VP6_DecodeModeProbs
	.align	3
.LC34:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_ConfigureMvEntropyDecoder
	.type	VP6_ConfigureMvEntropyDecoder, %function
VP6_ConfigureMvEntropyDecoder:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x25, x0
	mov	x0, x30
	mov	x20, x2
	mov	x21, x1
	bl	_mcount
	add	x20, x20, 76
	ldr	x0, .LC37
	mov	x22, x25
	add	x26, x25, 2
	mov	w28, 246
	add	x23, x0, 1649
	mov	w2, 237
	mov	w27, 1
.L206:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L195
	mov	w24, 0
	mov	w19, 6
	.p2align 2
.L196:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w24, w0, w24
	cmn	w19, #1
	bne	.L196
	ubfiz	w2, w24, 1, 7
	tst	w2, 254
	beq	.L197
	strb	w2, [x22, 2]
.L195:
	mov	w2, w28
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L200
	mov	w28, 0
	mov	w19, 6
	.p2align 2
.L201:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w28, w0, w28
	cmn	w19, #1
	bne	.L201
	ubfiz	w28, w28, 1, 7
	tst	w28, 254
	beq	.L202
	strb	w28, [x22]
.L200:
	add	x22, x22, 1
	cmp	x22, x26
	beq	.L228
	ldrb	w2, [x23]
	add	x23, x23, 17
	ldrb	w28, [x23, -16]
	b	.L206
	.p2align 3
.L228:
	ldr	x0, .LC37
	add	x23, x25, 7
	mov	w2, 253
	mov	w27, 1
	add	x26, x0, 1635
	add	x0, x25, 21
	str	x0, [x29, 104]
.L205:
	sub	x19, x23, #7
	mov	x22, x26
	.p2align 2
.L215:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L208
	mov	w28, 0
	mov	w24, 6
	.p2align 2
.L209:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w24
	sub	w24, w24, #1
	orr	w28, w0, w28
	cmn	w24, #1
	bne	.L209
	ubfiz	w3, w28, 1, 7
	tst	w3, 254
	beq	.L210
	strb	w3, [x19, 484]
.L208:
	add	x19, x19, 1
	cmp	x19, x23
	beq	.L229
.L212:
	ldrb	w2, [x22], 1
	b	.L215
	.p2align 3
.L210:
	strb	w27, [x19, 484]
	add	x19, x19, 1
	cmp	x19, x23
	bne	.L212
.L229:
	ldr	x0, [x29, 104]
	add	x23, x19, 7
	add	x26, x26, 17
	cmp	x23, x0
	beq	.L230
	ldrb	w2, [x26, -1]
	b	.L205
	.p2align 3
.L230:
	ldr	x0, .LC37
	add	x27, x25, 8
	mov	w2, 254
	add	x25, x25, 24
	add	x24, x0, 1642
	mov	w28, 1
.L214:
	sub	x23, x27, #8
	mov	x26, x24
	.p2align 2
.L223:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool
	cbz	w0, .L217
	mov	w22, 0
	mov	w19, 6
	.p2align 2
.L218:
	mov	x1, x20
	mov	x0, x21
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w22, w0, w22
	cmn	w19, #1
	bne	.L218
	ubfiz	w22, w22, 1, 7
	tst	w22, 254
	beq	.L219
	strb	w22, [x23, 498]
.L217:
	add	x23, x23, 1
	cmp	x23, x27
	beq	.L231
.L221:
	ldrb	w2, [x26], 1
	b	.L223
	.p2align 3
.L219:
	strb	w28, [x23, 498]
	add	x23, x23, 1
	cmp	x23, x27
	bne	.L221
.L231:
	add	x27, x27, 8
	add	x24, x24, 17
	cmp	x25, x27
	beq	.L193
	ldrb	w2, [x24, -1]
	b	.L214
	.p2align 3
.L193:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L197:
	strb	w27, [x22, 2]
	b	.L195
.L202:
	strb	w27, [x22]
	b	.L200
	.size	VP6_ConfigureMvEntropyDecoder, .-VP6_ConfigureMvEntropyDecoder
	.align	3
.LC37:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_BoolTreeToHuffCodes
	.type	VP6_BoolTreeToHuffCodes, %function
VP6_BoolTreeToHuffCodes:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w2, [x19, 1]
	mov	w0, 255
	ldrb	w1, [x19]
	mul	w1, w1, w2
	lsr	w1, w1, 8
	str	w1, [x20, 44]
	ldrb	w1, [x19, 1]
	ldrb	w2, [x19]
	sub	w1, w0, w1
	mul	w1, w1, w2
	lsr	w1, w1, 8
	str	w1, [x20]
	ldrb	w2, [x19]
	ldrb	w3, [x19, 2]
	sub	w2, w0, w2
	mul	w3, w3, w2
	lsr	w3, w3, 8
	str	w3, [x20, 4]
	ldrb	w1, [x19, 2]
	ldrb	w3, [x19, 3]
	sub	w1, w0, w1
	ldrb	w4, [x19, 4]
	mul	w2, w1, w2
	lsr	w2, w2, 8
	mul	w1, w3, w2
	lsr	w3, w1, 8
	mul	w1, w4, w3
	lsr	w1, w1, 8
	str	w1, [x20, 8]
	ldrb	w1, [x19, 4]
	ldrb	w4, [x19, 5]
	sub	w1, w0, w1
	mul	w1, w1, w3
	lsr	w1, w1, 8
	mul	w3, w4, w1
	lsr	w3, w3, 8
	str	w3, [x20, 12]
	ldrb	w3, [x19, 5]
	sub	w3, w0, w3
	mul	w1, w3, w1
	lsr	w1, w1, 8
	str	w1, [x20, 16]
	ldrb	w1, [x19, 3]
	ldrb	w3, [x19, 6]
	sub	w1, w0, w1
	ldrb	w4, [x19, 7]
	mul	w2, w1, w2
	lsr	w2, w2, 8
	mul	w1, w3, w2
	lsr	w3, w1, 8
	mul	w1, w4, w3
	lsr	w1, w1, 8
	str	w1, [x20, 20]
	ldrb	w1, [x19, 7]
	sub	w1, w0, w1
	mul	w1, w1, w3
	lsr	w1, w1, 8
	str	w1, [x20, 24]
	ldrb	w1, [x19, 6]
	ldrb	w3, [x19, 8]
	sub	w1, w0, w1
	ldrb	w4, [x19, 9]
	mul	w1, w1, w2
	lsr	w2, w1, 8
	mul	w1, w3, w2
	lsr	w3, w1, 8
	mul	w1, w4, w3
	lsr	w1, w1, 8
	str	w1, [x20, 28]
	ldrb	w1, [x19, 9]
	sub	w1, w0, w1
	mul	w1, w1, w3
	lsr	w1, w1, 8
	str	w1, [x20, 32]
	ldrb	w1, [x19, 8]
	ldrb	w3, [x19, 10]
	sub	w1, w0, w1
	mul	w1, w1, w2
	lsr	w1, w1, 8
	mul	w2, w3, w1
	lsr	w2, w2, 8
	str	w2, [x20, 36]
	ldrb	w2, [x19, 10]
	sub	w0, w0, w2
	mul	w0, w0, w1
	lsr	w0, w0, 8
	str	w0, [x20, 40]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP6_BoolTreeToHuffCodes, .-VP6_BoolTreeToHuffCodes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_ZerosBoolTreeToHuffCodes
	.type	VP6_ZerosBoolTreeToHuffCodes, %function
VP6_ZerosBoolTreeToHuffCodes:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrb	w2, [x19, 1]
	mov	w0, 255
	ldrb	w1, [x19]
	ldrb	w3, [x19, 2]
	mul	w1, w1, w2
	lsr	w2, w1, 8
	mul	w1, w3, w2
	lsr	w1, w1, 8
	str	w1, [x20]
	ldrb	w1, [x19, 2]
	sub	w1, w0, w1
	mul	w1, w1, w2
	lsr	w1, w1, 8
	str	w1, [x20, 4]
	ldrb	w1, [x19, 1]
	ldrb	w3, [x19]
	sub	w1, w0, w1
	ldrb	w2, [x19, 3]
	mul	w1, w1, w3
	lsr	w1, w1, 8
	mul	w2, w2, w1
	lsr	w2, w2, 8
	str	w2, [x20, 8]
	ldrb	w2, [x19, 3]
	sub	w2, w0, w2
	mul	w1, w2, w1
	lsr	w1, w1, 8
	str	w1, [x20, 12]
	ldrb	w3, [x19]
	ldrb	w2, [x19, 4]
	sub	w3, w0, w3
	ldrb	w4, [x19, 5]
	ldrb	w1, [x19, 6]
	mul	w2, w3, w2
	lsr	w2, w2, 8
	mul	w2, w2, w4
	lsr	w2, w2, 8
	mul	w1, w1, w2
	lsr	w1, w1, 8
	str	w1, [x20, 16]
	ldrb	w1, [x19, 6]
	sub	w1, w0, w1
	mul	w2, w1, w2
	lsr	w2, w2, 8
	str	w2, [x20, 20]
	ldrb	w3, [x19]
	ldrb	w2, [x19, 4]
	sub	w3, w0, w3
	ldrb	w4, [x19, 5]
	ldrb	w1, [x19, 7]
	mul	w2, w3, w2
	sub	w4, w0, w4
	lsr	w2, w2, 8
	mul	w2, w2, w4
	lsr	w2, w2, 8
	mul	w1, w1, w2
	lsr	w1, w1, 8
	str	w1, [x20, 24]
	ldrb	w1, [x19, 7]
	sub	w1, w0, w1
	mul	w2, w1, w2
	lsr	w2, w2, 8
	str	w2, [x20, 28]
	ldrb	w2, [x19, 4]
	ldrb	w1, [x19]
	sub	w1, w0, w1
	sub	w0, w0, w2
	mul	w0, w1, w0
	lsr	w0, w0, 8
	str	w0, [x20, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP6_ZerosBoolTreeToHuffCodes, .-VP6_ZerosBoolTreeToHuffCodes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_InsertSorted
	.type	VP6_InsertSorted, %function
VP6_InsertSorted:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	w8, [x21]
	uxtw	x7, w20
	cmn	w8, #1
	beq	.L235
	uxtw	x1, w8
	lsl	x3, x7, 2
	lsl	x0, x1, 2
	sub	x7, x3, x7
	sub	x0, x0, x1
	add	x7, x19, x7, lsl 2
	add	x0, x19, x0, lsl 2
	ldr	w6, [x7, 8]
	ldr	w1, [x0, 8]
	cmp	w6, w1
	bls	.L236
	uxtw	x5, w8
	b	.L238
	.p2align 3
.L246:
	sub	x0, x0, x4
	add	x0, x19, x0, lsl 2
	ldr	w4, [x0, 8]
	cmp	w4, w6
	bcs	.L245
	uxtw	x5, w3
.L238:
	ldr	w3, [x0, 4]
	cmn	w3, #1
	uxtw	x4, w3
	lsl	x0, x4, 2
	bne	.L246
.L237:
	lsl	x0, x5, 2
	sub	x5, x0, x5
	add	x19, x19, x5, lsl 2
	str	w20, [x19, 4]
	str	w3, [x7, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L245:
	cmp	w8, w3
	bne	.L237
.L240:
	str	w20, [x21]
	str	w3, [x7, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L235:
	lsl	x0, x7, 2
	sub	x7, x0, x7
	add	x7, x19, x7, lsl 2
.L236:
	mov	w3, w8
	b	.L240
	.size	VP6_InsertSorted, .-VP6_InsertSorted
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_BuildHuffTree
	.type	VP6_BuildHuffTree, %function
VP6_BuildHuffTree:
	stp	x29, x30, [sp, -448]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	w24, w2
	mov	x21, x1
	bl	_mcount
	str	wzr, [x29, 84]
	sub	w19, w24, #1
	cbz	w24, .L252
	add	x20, x29, 88
	mov	x3, 0
	add	x4, x20, 8
	mov	w6, 1
	mov	w1, -1
	.p2align 2
.L251:
	uxtw	x2, w3
	ldr	w5, [x21, x3, lsl 2]
	lsl	x0, x2, 2
	sub	x0, x0, x2
	add	x2, x29, 448
	add	x0, x2, x0, lsl 2
	sub	x0, x0, #512
	ldrb	w2, [x0, 152]
	orr	w2, w2, 1
	bfi	w2, w3, 1, 4
	and	w2, w2, 31
	strb	w2, [x0, 152]
	cbnz	w5, .L250
	str	w6, [x21, x3, lsl 2]
	mov	w5, 1
.L250:
	add	x3, x3, 1
	stp	w1, w5, [x4, -4]
	cmp	w24, w3
	add	x4, x4, 12
	bhi	.L251
	cmp	w24, 1
	bls	.L252
	mov	w23, 1
	add	x21, x29, 84
	.p2align 2
.L253:
	mov	w1, w23
	mov	x2, x21
	mov	x0, x20
	add	w23, w23, 1
	bl	VP6_InsertSorted
	cmp	w24, w23
	bne	.L253
	ldr	w2, [x29, 84]
.L249:
	uxtw	x2, w2
	add	x1, x29, 448
	lsl	x0, x2, 2
	sub	x0, x0, x2
	add	x0, x1, x0, lsl 2
	sub	x0, x0, #4096
	ldr	w4, [x0, 3740]
	cmn	w4, #1
	beq	.L247
	sub	w25, w24, #2
	add	x20, x29, 88
	and	w25, w25, 15
	add	x21, x29, 84
	mov	w23, -1
	.p2align 2
.L255:
	uxtw	x3, w24
	lsl	x0, x2, 2
	sub	x2, x0, x2
	uxtw	x4, w4
	lsl	x0, x3, 2
	lsl	x1, x4, 2
	sub	x3, x0, x3
	sub	x4, x1, x4
	add	x0, x29, 448
	add	x1, x29, 448
	add	x3, x1, x3, lsl 2
	add	x0, x0, x2, lsl 2
	sub	x7, x3, #512
	sub	x0, x0, #4096
	sub	x3, x3, #4096
	add	x4, x1, x4, lsl 2
	sub	w19, w19, #1
	sub	x4, x4, #4096
	ubfiz	x1, x19, 1, 32
	ldrb	w6, [x0, 3736]
	add	x2, x22, x1
	ldrb	w5, [x7, 152]
	str	w23, [x3, 3740]
	ldrb	w8, [x4, 3736]
	and	w5, w5, 254
	strb	w6, [x22, x1]
	bfi	w5, w25, 1, 4
	ldr	w9, [x0, 3744]
	mov	w1, w24
	ldr	w6, [x4, 3744]
	mov	x0, x20
	strb	w8, [x2, 1]
	mov	x2, x21
	ldr	w8, [x4, 3740]
	add	w4, w9, w6
	strb	w5, [x7, 152]
	add	w25, w25, 15
	str	w4, [x3, 3744]
	add	w24, w24, 1
	str	w8, [x29, 84]
	and	w25, w25, 15
	bl	VP6_InsertSorted
	ldr	w2, [x29, 84]
	add	x0, x29, 448
	lsl	x1, x2, 2
	sub	x1, x1, x2
	add	x1, x0, x1, lsl 2
	sub	x1, x1, #4096
	ldr	w4, [x1, 3740]
	cmn	w4, #1
	bne	.L255
.L247:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 448
	ret
.L252:
	mov	w2, 0
	b	.L249
	.size	VP6_BuildHuffTree, .-VP6_BuildHuffTree
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_BuildHuffLookupTable
	.type	VP6_BuildHuffLookupTable, %function
VP6_BuildHuffLookupTable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	x5, 0
	mov	w7, 6
	.p2align 2
.L264:
	mov	w6, w5
	mov	w0, 0
	mov	w2, 0
	b	.L263
	.p2align 3
.L268:
	ldrb	w3, [x0, 1]
	and	w4, w3, 1
	ubfx	x0, x3, 1, 4
	cmp	w4, wzr
	ccmp	w2, 5, 2, eq
	bhi	.L267
.L263:
	add	w2, w2, 1
	ubfiz	x4, x0, 1, 4
	sub	w3, w7, w2
	add	x0, x19, x4
	asr	w3, w6, w3
	tbnz	x3, 0, .L268
	ldrb	w3, [x19, x4]
	and	w4, w3, 1
	ubfx	x0, x3, 1, 4
	cmp	w4, wzr
	ccmp	w2, 5, 2, eq
	bls	.L263
.L267:
	ldrb	w3, [x20, x5]
	bfi	w3, w0, 4, 4
	mov	w0, w3
	bfi	w0, w2, 1, 3
	bfi	w0, w4, 0, 1
	strb	w0, [x20, x5]
	add	x5, x5, 1
	cmp	x5, 64
	bne	.L264
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP6_BuildHuffLookupTable, .-VP6_BuildHuffLookupTable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_BuildTreeTab
	.type	VP6_BuildTreeTab, %function
VP6_BuildTreeTab:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x8, x19, 8192
	mov	w0, 0
	add	x10, x8, 926
	add	x11, x8, 1790
.L270:
	sub	x9, x10, #432
.L279:
	sub	x7, x9, #96
.L277:
	add	x1, x19, x0, uxtw
	add	w2, w0, 1
	ldrb	w4, [x7, -2]
	mov	x3, x7
	add	x2, x19, x2, uxtw
	add	w0, w0, 2
	strb	w4, [x1, 1218]
	mov	w1, 0
	ldrb	w4, [x7, -1]
	strb	w4, [x2, 1218]
	b	.L275
	.p2align 3
.L273:
	ldrb	w0, [x3]
	cmp	w1, 5
	add	x3, x3, 2
	strb	w0, [x6, 1218]
	ccmp	w1, 11, 4, ne
	cset	w6, eq
	ldrb	w0, [x3, -1]
	cmp	w6, wzr
	strb	w0, [x2, 1218]
	csel	w0, w4, w5, ne
.L275:
	add	w1, w1, 1
	add	w2, w0, 1
	cmp	w1, 12
	add	x6, x19, x0, uxtw
	add	x2, x19, x2
	add	w5, w0, 2
	add	w4, w0, 6
	bne	.L273
	add	x7, x7, 24
	cmp	x7, x9
	bne	.L277
	add	x9, x7, 144
	cmp	x10, x9
	bne	.L279
	add	x10, x7, 576
	cmp	x10, x11
	bne	.L270
	add	x7, x8, 1262
	add	x9, x8, 1310
	mov	w0, 768
.L278:
	add	x1, x19, x0, uxtw
	add	w2, w0, 1
	ldrb	w4, [x7, -2]
	mov	x3, x7
	add	x2, x19, x2, uxtw
	add	w0, w0, 2
	strb	w4, [x1, 1218]
	mov	w1, 0
	ldrb	w4, [x7, -1]
	strb	w4, [x2, 1218]
	b	.L284
	.p2align 3
.L282:
	ldrb	w0, [x3]
	cmp	w1, 5
	add	x3, x3, 2
	strb	w0, [x6, 1218]
	ccmp	w1, 11, 4, ne
	cset	w6, eq
	ldrb	w0, [x3, -1]
	cmp	w6, wzr
	strb	w0, [x2, 1218]
	csel	w0, w4, w5, ne
.L284:
	add	w1, w1, 1
	add	w2, w0, 1
	cmp	w1, 12
	add	x6, x19, x0, uxtw
	add	x2, x19, x2
	add	w5, w0, 2
	add	w4, w0, 6
	bne	.L282
	add	x7, x7, 24
	cmp	x9, x7
	bne	.L278
	add	x6, x8, 340
	mov	w3, 832
	add	x8, x8, 396
.L283:
	mov	x2, x6
	mov	w1, 0
	b	.L289
	.p2align 3
.L294:
	add	w1, w1, 1
	add	w3, w3, 6
	cmp	w1, 14
	add	x2, x2, 2
	beq	.L288
.L289:
	add	x4, x19, x3, uxtw
	ldrb	w5, [x2]
	add	w0, w3, 1
	cmp	w1, 5
	add	x0, x19, x0
	ccmp	w1, 11, 4, ne
	strb	w5, [x4, 1218]
	ldrb	w4, [x2, 1]
	strb	w4, [x0, 1218]
	beq	.L294
	cmp	w1, 13
	beq	.L295
	add	w1, w1, 1
	add	w3, w3, 2
	cmp	w1, 14
	add	x2, x2, 2
	bne	.L289
.L288:
	add	x6, x6, 28
	cmp	x8, x6
	bne	.L283
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L295:
	add	w3, w3, 30
	b	.L288
	.size	VP6_BuildTreeTab, .-VP6_BuildTreeTab
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_ConvertBoolToHuff
	.type	VP6_ConvertBoolToHuff, %function
VP6_ConvertBoolToHuff:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x27, x21, 4096
	add	x19, x21, 8192
	bl	_mcount
	add	x23, x27, 2500
	ldr	x1, .LC39
	mov	w0, 22
	add	x22, x19, 1260
	add	x20, x27, 2548
	add	x25, x19, 1284
	add	x24, x27, 2596
	bl	dprint_vfmw
	mov	w26, 198
	mov	x1, x23
	add	x0, x21, 514
	bl	VP6_BoolTreeToHuffCodes
	mov	w2, 12
	mov	x1, x23
	mov	x0, x22
	add	x23, x19, 340
	bl	VP6_BuildHuffTree
	mov	x0, x22
	add	x1, x19, 1308
	add	x22, x27, 2652
	bl	VP6_BuildHuffLookupTable
	mov	x1, x20
	add	x0, x21, 525
	bl	VP6_BoolTreeToHuffCodes
	add	x3, x27, 2708
	mov	w2, 12
	mov	x1, x20
	mov	x0, x25
	str	x3, [x29, 104]
	add	x20, x19, 368
	bl	VP6_BuildHuffTree
	add	x1, x19, 1372
	mov	x0, x25
	bl	VP6_BuildHuffLookupTable
	mov	x1, x24
	add	x0, x21, 536
	bl	VP6_ZerosBoolTreeToHuffCodes
	add	x0, x19, 396
	mov	w2, 9
	mov	x1, x24
	str	x0, [x29, 120]
	mov	x0, x23
	bl	VP6_BuildHuffTree
	add	x0, x19, 1436
	add	x1, x19, 3740
	str	x0, [x29, 112]
	mov	x0, x23
	bl	VP6_BuildHuffLookupTable
	mov	x1, x22
	add	x0, x21, 550
	bl	VP6_ZerosBoolTreeToHuffCodes
	mov	x1, x22
	mov	x0, x20
	mov	w2, 9
	bl	VP6_BuildHuffTree
	add	x1, x19, 3804
	mov	x0, x20
	bl	VP6_BuildHuffLookupTable
.L297:
	ldp	x23, x25, [x29, 104]
	ldr	x24, [x29, 120]
	sub	w27, w26, #198
.L301:
	add	w22, w27, 66
	mov	x20, x25
	mov	x19, x24
	mov	x28, x23
	.p2align 2
.L298:
	add	x0, x21, x27, uxtw
	mov	x1, x28
	add	x0, x0, 564
	add	w27, w27, 11
	bl	VP6_BoolTreeToHuffCodes
	mov	x1, x28
	mov	x0, x19
	mov	w2, 12
	add	x28, x28, 48
	bl	VP6_BuildHuffTree
	mov	x1, x20
	mov	x0, x19
	add	x20, x20, 64
	add	x19, x19, 24
	bl	VP6_BuildHuffLookupTable
	cmp	w27, w22
	bne	.L298
	cmp	w26, w27
	add	x23, x23, 288
	add	x24, x24, 144
	add	x25, x25, 384
	bne	.L301
	ldr	x0, [x29, 104]
	add	w26, w26, 198
	cmp	w26, 594
	add	x0, x0, 864
	str	x0, [x29, 104]
	ldr	x0, [x29, 120]
	add	x0, x0, 432
	str	x0, [x29, 120]
	ldr	x0, [x29, 112]
	add	x0, x0, 1152
	str	x0, [x29, 112]
	bne	.L297
	mov	x0, x21
	bl	VP6_BuildTreeTab
	ldr	x1, .LC41
	mov	w0, 22
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	VP6_ConvertBoolToHuff, .-VP6_ConvertBoolToHuff
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_IntraFrmHeader
	.type	VP6_IntraFrmHeader, %function
VP6_IntraFrmHeader:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x24, x0
	mov	x0, x30
	mov	x19, x1
	add	x23, x24, 12288
	bl	_mcount
	sub	x20, x23, #28
	ldr	x1, .LC43
	mov	w0, 22
	bl	dprint_vfmw
	mov	w1, 5
	mov	x0, x19
	bl	BsGet
	uxtb	w0, w0
	mov	w1, 2
	str	w0, [x23, -12]
	mov	x0, x19
	bl	BsGet
	uxtb	w0, w0
	ldr	w2, [x23, -12]
	str	w0, [x23, -8]
	cmp	w2, 8
	bhi	.L334
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L335
	ldrb	w0, [x23, -26]
	cbz	w0, .L307
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, 56]
.L307:
	mov	w1, 255
	mov	w0, 8
	str	w1, [x24, 12340]
	mov	w1, 24
	str	w0, [x24, 12348]
	mov	x0, x19
	str	wzr, [x24, 12336]
	mov	x20, 12336
	mov	w22, 0
	add	x20, x24, x20
	bl	BsGet
	mov	w21, 7
	str	w0, [x24, 12344]
	.p2align 2
.L309:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L309
	and	w0, w22, 255
	mov	w21, 7
	mov	w22, 0
	str	w0, [x23]
	.p2align 2
.L310:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L310
	ldr	w25, [x23]
	and	w22, w22, 255
	lsl	w26, w22, 1
	mov	w27, 0
	lsl	w25, w25, 1
	mov	w21, 7
	stp	w22, w25, [x23, 4]
	str	w26, [x23, 12]
	.p2align 2
.L311:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w27, w0, w27
	cmn	w21, #1
	bne	.L311
	ubfiz	w27, w27, 1, 8
	mov	w22, 0
	mov	w21, 7
	str	w27, [x23, 16]
	.p2align 2
.L312:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L312
	mov	x1, x20
	ubfiz	w22, w22, 1, 8
	mov	x0, x19
	str	w22, [x23, 20]
	bl	Vp6_Vfmw_DecodeBool128
	mov	w21, w0
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	orr	w0, w0, w21, lsl 1
	strb	w0, [x23, -25]
	ldr	w3, [x24, 12064]
	ldr	w2, [x24, 12060]
	cmp	w25, w3
	bne	.L314
	cmp	w26, w2
	beq	.L315
.L314:
	ldr	x1, .LC49
	mov	w5, w25
	mov	w4, w26
	mov	w0, 22
	bl	dprint_vfmw
.L315:
	str	w26, [x24, 12060]
	sub	x21, x23, #28
	str	w25, [x24, 12064]
	ldr	w0, [x23, -8]
	cbnz	w0, .L336
	mov	w0, 14
	strb	w0, [x23, -22]
	str	wzr, [x21, 60]
.L325:
	ldr	x1, .LC51
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L334:
	ldr	x1, .LC45
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L335:
	ldr	x1, .LC47
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L336:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	cbz	w0, .L317
	mov	w0, 2
	mov	w22, 0
	str	w0, [x21, 60]
	mov	w21, 4
	.p2align 2
.L318:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L318
	ldr	w1, [x23, -12]
	mov	w0, 5
	and	w22, w22, 255
	mov	w24, 0
	cmp	w1, 7
	mov	w21, 2
	csel	w0, wzr, w0, hi
	lsl	w0, w22, w0
	strb	w0, [x23, -24]
.L320:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w24, w0, w24
	cmn	w21, #1
	bne	.L320
	strb	w24, [x23, -23]
.L321:
	ldr	w0, [x23, -12]
	cmp	w0, 7
	bls	.L323
	mov	w22, 0
	mov	w21, 3
.L324:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L324
	strb	w22, [x23, -22]
	b	.L325
	.p2align 3
.L323:
	mov	w0, 16
	strb	w0, [x23, -22]
	b	.L325
	.p2align 3
.L317:
	mov	x1, x20
	mov	x0, x19
	bl	Vp6_Vfmw_DecodeBool128
	cbz	w0, .L322
	mov	w0, 1
	str	w0, [x21, 60]
	b	.L321
.L322:
	str	wzr, [x21, 60]
	b	.L321
	.size	VP6_IntraFrmHeader, .-VP6_IntraFrmHeader
	.align	3
.LC43:
	.xword	.LC42
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.align	3
.LC51:
	.xword	.LC50
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_InterFrmHeader
	.type	VP6_InterFrmHeader, %function
VP6_InterFrmHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	ldr	w0, [x19, 12128]
	cbz	w0, .L359
	add	x20, x19, 12288
	str	w0, [x20, -12]
	ldr	w1, [x19, 12132]
	ldrb	w0, [x20, -26]
	str	w1, [x20, -8]
	cbnz	w0, .L360
.L340:
	mov	w1, 255
	mov	w0, 8
	str	w1, [x19, 12340]
	mov	w1, 24
	str	w0, [x19, 12348]
	mov	x0, x22
	str	wzr, [x19, 12336]
	mov	x21, 12336
	sub	x23, x20, #28
	add	x21, x19, x21
	bl	BsGet
	str	w0, [x19, 12344]
	mov	x1, x21
	mov	x0, x22
	bl	Vp6_Vfmw_DecodeBool128
	str	w0, [x23, 64]
	str	w0, [x19, 12084]
	ldr	w0, [x19, 12132]
	cbnz	w0, .L361
	mov	w0, 14
	strb	w0, [x20, -22]
	mov	w19, 1
	str	wzr, [x23, 60]
.L339:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L360:
	mov	w1, 16
	mov	x0, x22
	bl	BsGet
	str	w0, [x20, 28]
	b	.L340
	.p2align 3
.L361:
	mov	x1, x21
	mov	x0, x22
	bl	Vp6_Vfmw_DecodeBool128
	str	w0, [x23, 68]
	mov	w24, w0
	cbnz	w0, .L362
.L343:
	ldr	w0, [x19, 12128]
	cmp	w0, 7
	bhi	.L363
	mov	w0, 16
	strb	w0, [x20, -22]
	mov	w19, 1
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L363:
	mov	x1, x21
	mov	x0, x22
	mov	w19, 1
	bl	Vp6_Vfmw_DecodeBool128
	cbz	w0, .L339
	mov	x1, x21
	mov	x0, x22
	bl	Vp6_Vfmw_DecodeBool128
	cbz	w0, .L345
	mov	w0, 2
	mov	w23, 0
	mov	w19, 4
	str	w0, [x20, 32]
	.p2align 2
.L346:
	mov	x1, x21
	mov	x0, x22
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w23, w0, w23
	cmn	w19, #1
	bne	.L346
	strb	w23, [x20, -24]
	mov	w19, 2
	mov	w23, 0
.L347:
	mov	x1, x21
	mov	x0, x22
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w23, w0, w23
	cmn	w19, #1
	bne	.L347
	strb	w23, [x20, -23]
.L350:
	mov	w23, 0
	mov	w19, 3
.L348:
	mov	x1, x21
	mov	x0, x22
	bl	Vp6_Vfmw_DecodeBool128
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w23, w0, w23
	cmn	w19, #1
	bne	.L348
	strb	w23, [x20, -22]
	mov	w19, 1
	b	.L339
	.p2align 3
.L362:
	mov	x1, x21
	mov	x0, x22
	bl	Vp6_Vfmw_DecodeBool128
	orr	w0, w0, w24, lsl 1
	str	w0, [x23, 68]
	b	.L343
	.p2align 3
.L359:
	ldr	w3, [x19, 12276]
	mov	w2, 0
	ldr	x1, .LC53
	mov	w0, 1
	mov	w19, -88
	bl	dprint_vfmw
	b	.L339
	.p2align 3
.L345:
	mov	x1, x21
	mov	x0, x22
	bl	Vp6_Vfmw_DecodeBool128
	cmp	w0, wzr
	mov	w1, 0
	csel	w19, w19, w1, ne
	str	w19, [x20, 32]
	b	.L350
	.size	VP6_InterFrmHeader, .-VP6_InterFrmHeader
	.align	3
.LC53:
	.xword	.LC52
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_GetPictureHeader
	.type	VP6_GetPictureHeader, %function
VP6_GetPictureHeader:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x21, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L370
	ldr	x1, .LC57
	mov	w0, 22
	add	x19, x21, 12288
	add	x22, x21, 8192
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	and	w1, w0, 255
	str	w1, [x19, -4]
	mov	w1, 6
	strb	w0, [x22, 3888]
	mov	x0, x20
	bl	BsGet
	and	w3, w0, 255
	ldr	x2, .LC58
	mov	w1, 1
	strb	w0, [x19, -28]
	mov	x0, x20
	add	x5, x2, 1672
	add	x4, x2, 1736
	add	x2, x2, 1864
	ldrb	w5, [x5, w3, sxtw]
	ldrh	w4, [x4, w3, sxtw 1]
	ldrh	w2, [x2, w3, sxtw 1]
	strb	w5, [x19, -27]
	strh	w4, [x19, -16]
	strh	w2, [x19, -14]
	bl	BsGet
	strb	w0, [x19, -26]
	ldr	w1, [x19, -4]
	cbz	w1, .L371
	mov	x0, x21
	mov	x1, x20
	bl	VP6_InterFrmHeader
	cmp	w0, 1
	mov	w21, w0
	beq	.L372
.L366:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L371:
	mov	x0, x21
	mov	x1, x20
	bl	VP6_IntraFrmHeader
	cmp	w0, 1
	mov	w21, w0
	bne	.L366
.L372:
	add	x1, x22, 4068
	mov	x0, x20
	add	x1, x1, 76
	bl	Vp6_Vfmw_DecodeBool128
	str	w0, [x19, 44]
	ldrb	w3, [x19, -28]
	mov	w0, 22
	ldr	x1, .LC60
	str	w3, [x19, 24]
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L370:
	ldr	x1, .LC55
	mov	w0, 22
	mov	w21, 0
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP6_GetPictureHeader, .-VP6_GetPictureHeader
	.align	3
.LC55:
	.xword	.LC54
	.align	3
.LC57:
	.xword	.LC56
	.align	3
.LC58:
	.xword	.LANCHOR0
	.align	3
.LC60:
	.xword	.LC59
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6DEC_Init
	.type	VP6DEC_Init, %function
VP6DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L377
	ldr	x21, .LC65
	mov	x2, 13384
	mov	w1, 0
	mov	x0, x19
	ldr	w22, [x19, 13360]
	ldr	x3, [x21, 96]
	blr	x3
	str	w22, [x19, 13360]
	add	x0, x19, 12288
	add	x0, x0, 472
	bl	ResetVoQueue
	str	x20, [x19]
	mov	x0, x19
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 13368]
	beq	.L378
	ldr	x3, [x21, 96]
	add	x20, x19, 312
	mov	x2, 12408
	mov	w1, 0
	mov	x0, x20
	blr	x3
	str	wzr, [x19, 12388]
	ldr	x2, [x19]
	mov	w0, 1024
	str	w0, [x19, 12416]
	mov	w0, 22
	ldr	x1, .LC69
	ldr	w2, [x2, 8]
	str	w2, [x19, 12380]
	bl	dprint_vfmw
	mov	w0, 1
.L375:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L377:
	ldr	x1, .LC64
	mov	w2, 2005
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L378:
	ldr	x1, .LC67
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L375
	.size	VP6DEC_Init, .-VP6DEC_Init
	.align	3
.LC64:
	.xword	.LC17
	.align	3
.LC65:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC69:
	.xword	.LC68
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6DEC_Destroy
	.type	VP6DEC_Destroy, %function
VP6DEC_Destroy:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VP6DEC_Destroy, .-VP6DEC_Destroy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_DecodeDecide
	.type	VP6_DecodeDecide, %function
VP6_DecodeDecide:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 312
	bl	_mcount
	ldr	w0, [x19, 12076]
	cbz	w0, .L408
	ldr	w0, [x19, 12068]
	sub	w0, w0, #2
	cmp	w0, 1
	ldr	x0, [x20]
	ldr	w2, [x0, 8]
	bls	.L409
.L384:
	cmp	w2, 4
	str	w2, [x19, 12068]
	bls	.L410
	ldr	x1, .LC81
	mov	w0, 1
	bl	dprint_vfmw
.L387:
	mov	w0, 0
.L401:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L410:
	ldr	x0, .LC87
	ldrb	w0, [x0,w2,uxtw]
	adr	x1, .Lrtx390
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx390:
	.section	.rodata
	.align	0
	.align	2
.L390:
	.byte	(.L388 - .Lrtx390) / 4
	.byte	(.L388 - .Lrtx390) / 4
	.byte	(.L385 - .Lrtx390) / 4
	.byte	(.L387 - .Lrtx390) / 4
	.byte	(.L388 - .Lrtx390) / 4
	.text
	.p2align 3
.L409:
	cmp	w2, 1
	ccmp	w2, 4, 4, hi
	bne	.L384
	ldr	x1, .LC73
	mov	w0, 2
	bl	dprint_vfmw
	ldr	w1, [x19, 12092]
	mov	w2, 1
	ldr	w0, [x20, 13368]
	bl	FSP_ClearLogicFs
	ldr	w1, [x19, 12096]
	mov	w2, 1
	ldr	w0, [x20, 13368]
	bl	FSP_ClearLogicFs
	str	wzr, [x19, 12092]
	str	wzr, [x19, 12096]
	ldr	w0, [x20, 13368]
	bl	FSP_GetNullLogicFs
	str	wzr, [x19, 12072]
	str	w0, [x19, 12092]
	str	w0, [x19, 12096]
	ldr	x0, [x20]
	ldr	w2, [x0, 8]
	b	.L384
	.p2align 3
.L408:
	ldr	x1, .LC71
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L385:
	add	x0, x19, 8192
	ldrb	w2, [x0, 3888]
	cbnz	w2, .L411
.L386:
	ldr	w1, [x19, 12096]
	ldr	w0, [x20, 13368]
	bl	FSP_GetFsImagePtr
	mov	x1, x0
	cbz	x0, .L412
	add	x19, x19, 8192
	mov	w0, 1
	ldrb	w2, [x19, 3888]
	cbz	w2, .L401
	ldr	x3, [x20]
	ldr	w2, [x1, 152]
	ldr	w3, [x3]
	cmp	w2, w3
	bls	.L401
	ldr	x1, .LC86
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L388:
	add	x0, x19, 8192
	ldrb	w0, [x0, 3888]
	cbz	w0, .L386
	ldr	w0, [x19, 12072]
	cbnz	w0, .L386
	ldr	x2, .LC77
	mov	w3, 0
	ldr	x1, .LC79
	mov	w0, 18
	bl	dprint_vfmw
	b	.L387
	.p2align 3
.L411:
	ldr	x1, .LC75
	mov	w0, 18
	bl	dprint_vfmw
	b	.L387
	.p2align 3
.L412:
	ldr	x2, .LC82
	mov	w3, 2143
	ldr	x1, .LC84
	mov	w0, 22
	add	x2, x2, 1992
	bl	dprint_vfmw
	mov	w0, 0
	b	.L401
	.size	VP6_DecodeDecide, .-VP6_DecodeDecide
	.align	3
.LC71:
	.xword	.LC70
	.align	3
.LC73:
	.xword	.LC72
	.align	3
.LC75:
	.xword	.LC74
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC82:
	.xword	.LANCHOR0
	.align	3
.LC84:
	.xword	.LC83
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC87:
	.xword	.L390
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_Set_DecParam
	.type	VP6_Set_DecParam, %function
VP6_Set_DecParam:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 312
	add	x19, x20, 16
	bl	_mcount
	add	x0, x21, 8192
	ldrb	w0, [x0, 3888]
	cmp	w0, 3
	beq	.L438
	ldr	x3, .LC92
	add	x22, x20, 12288
	mov	x2, 272
	mov	w1, 0
	mov	x0, x19
	ldr	x24, [x20, 288]
	ldr	x3, [x3, 96]
	blr	x3
	ldr	w1, [x22, 308]
	str	w1, [x19, 116]
	strb	wzr, [x19, 1]
	ldrb	w1, [x22, 284]
	str	w1, [x19, 120]
	ldrb	w1, [x22, 286]
	str	w1, [x19, 124]
	ldr	w1, [x22, 356]
	str	w1, [x19, 128]
	ldr	w1, [x22, 344]
	str	w1, [x19, 140]
	ldrb	w1, [x22, 288]
	str	w1, [x19, 144]
	ldrb	w1, [x22, 289]
	str	w1, [x19, 148]
	ldrb	w1, [x22, 290]
	str	w1, [x19, 152]
	ldr	w1, [x22, 352]
	str	w1, [x19, 164]
	ldrb	w1, [x22, 285]
	strb	w1, [x20, 16]
	ldrh	w1, [x22, 296]
	str	w1, [x19, 132]
	ldrh	w1, [x22, 298]
	str	w1, [x19, 136]
	ldr	w1, [x22, 304]
	str	w1, [x19, 160]
	ldr	w1, [x22, 300]
	str	w1, [x19, 156]
	ldr	w1, [x22, 316]
	strh	w1, [x19, 106]
	ldr	w0, [x22, 312]
	strh	w0, [x19, 108]
	ldr	w1, [x21, 12088]
	ldr	w0, [x20, 13368]
	bl	FSP_GetLogicFs
	mov	x23, x0
	ldr	w1, [x21, 12096]
	ldr	w0, [x20, 13368]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldr	w1, [x21, 12092]
	ldr	w0, [x20, 13368]
	bl	FSP_GetLogicFs
	cmp	x23, xzr
	ccmp	x25, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L422
	ldr	x1, [x23, 32]
	cbz	x1, .L423
	ldr	w1, [x1, 8]
	str	w1, [x19, 228]
	ldr	w1, [x23, 8]
	str	w1, [x19, 240]
	ldr	x0, [x0, 32]
	cbz	x0, .L439
.L436:
	ldr	w0, [x0, 8]
	str	w0, [x19, 232]
	ldr	x0, [x25, 32]
	cbz	x0, .L440
.L437:
	ldr	w0, [x0, 8]
	add	x26, x22, 432
	str	w0, [x19, 236]
	mov	x0, x26
	ldr	w1, [x21, 12104]
	str	w1, [x19, 244]
	ldr	w1, [x21, 12108]
	str	w1, [x19, 248]
	ldr	x1, [x23, 32]
	ldr	w1, [x1, 60]
	str	w1, [x19, 252]
	ldr	x1, [x23, 32]
	ldr	w1, [x1, 44]
	str	w1, [x19, 256]
	ldr	x1, [x23, 32]
	ldr	w1, [x1, 48]
	str	w1, [x19, 260]
	ldr	w1, [x22, 368]
	str	w1, [x19, 216]
	ldr	w1, [x22, 364]
	str	w1, [x19, 220]
	ldr	w1, [x22, 372]
	str	w1, [x19, 224]
	ldr	x23, [x24]
	bl	BsPos
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w0, w1, w0, lt
	asr	w0, w0, 3
	add	x23, x23, x0, sxtw
	mov	x0, x23
	bl	MEM_Vir2Phy
	and	w0, w0, -16
	sub	w1, w0, #16
	mov	x0, x23
	str	w1, [x19, 112]
	bl	MEM_Vir2Phy
	and	w0, w0, 15
	ldrb	w1, [x22, 286]
	lsl	w0, w0, 3
	cbnz	w1, .L428
	ldr	w1, [x22, 304]
	cbnz	w1, .L429
.L428:
	mov	w1, 16
	stp	w0, w1, [x19, 172]
	mov	x0, x26
	ldr	w23, [x22, 340]
	bl	BsPos
	str	wzr, [x19, 188]
	lsl	w23, w23, 3
	sub	w0, w23, w0
	str	w0, [x19, 168]
	stp	wzr, wzr, [x19, 180]
	ldr	w0, [x22, 340]
	ldr	x23, [x24]
	add	x23, x23, x0
	mov	x0, x23
	bl	MEM_Vir2Phy
	mov	w25, w0
	mov	x0, x23
	ubfiz	w25, w25, 3, 4
	bl	MEM_Vir2Phy
	and	w0, w0, -16
	ldr	w1, [x19, 112]
	sub	w0, w0, w1
	stp	w25, w0, [x19, 196]
	ldr	w1, [x22, 340]
	ldr	w0, [x24, 12]
	stp	wzr, wzr, [x19, 204]
	lsl	w0, w0, 3
	str	wzr, [x19, 212]
	sub	w0, w0, w1, lsl 3
	str	w0, [x19, 192]
.L430:
	add	x21, x21, 4096
	add	x1, x20, 3386
	add	x0, x21, 834
	str	x0, [x19, 88]
	add	x0, x21, 706
	str	x1, [x19, 40]
	str	x0, [x19, 80]
	add	x1, x21, 98
	add	x0, x20, 3450
	str	x1, [x19, 64]
	add	x1, x21, 2
	stp	x0, x1, [x19, 48]
	add	x0, x20, 2618
	add	x1, x20, 3322
	str	x0, [x19, 16]
	add	x0, x20, 3258
	str	x1, [x19, 32]
	add	x1, x20, 2554
	str	x0, [x19, 24]
	add	x0, x21, 2370
	str	x1, [x19, 8]
	add	x21, x21, 674
	str	x0, [x19, 96]
	mov	w0, 1
	str	x21, [x19, 72]
	ldr	x1, [x20]
	ldr	w2, [x1, 640]
	str	w2, [x19, 264]
	ldr	w1, [x1, 692]
	str	w1, [x19, 268]
	str	x19, [x20, 8]
.L416:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L422:
	ldr	x1, .LC89
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L438:
	str	w0, [x19, 116]
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	w1, [x21, 12088]
	ldr	w0, [x20, 13368]
	bl	FSP_GetLogicFs
	mov	x22, x0
	ldr	w1, [x21, 12096]
	ldr	w0, [x20, 13368]
	bl	FSP_GetLogicFs
	mov	x23, x0
	ldr	w1, [x21, 12092]
	ldr	w0, [x20, 13368]
	bl	FSP_GetLogicFs
	cmp	x22, xzr
	ccmp	x23, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L422
	ldr	x1, [x22, 32]
	cbz	x1, .L423
	ldr	w1, [x1, 8]
	str	w1, [x19, 228]
	ldr	w1, [x22, 8]
	str	w1, [x19, 240]
	ldr	x0, [x0, 32]
	cbz	x0, .L441
.L434:
	ldr	w0, [x0, 8]
	str	w0, [x19, 232]
	ldr	x0, [x23, 32]
	cbz	x0, .L442
.L435:
	ldr	w0, [x0, 8]
	str	w0, [x19, 236]
	mov	w0, 1
	str	x19, [x20, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L429:
	mov	w1, 16
	stp	w0, w1, [x19, 172]
	mov	x0, x26
	ldr	w22, [x24, 12]
	bl	BsPos
	str	wzr, [x19, 212]
	lsl	w22, w22, 3
	sub	w0, w22, w0
	str	w0, [x19, 168]
	stp	wzr, wzr, [x19, 180]
	stp	wzr, wzr, [x19, 188]
	stp	wzr, wzr, [x19, 196]
	stp	wzr, wzr, [x19, 204]
	b	.L430
	.p2align 3
.L440:
	ldr	x0, [x23, 32]
	b	.L437
	.p2align 3
.L439:
	ldr	x0, [x23, 32]
	b	.L436
	.p2align 3
.L423:
	ldr	x1, .LC91
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L416
	.p2align 3
.L442:
	ldr	x0, [x22, 32]
	b	.L435
	.p2align 3
.L441:
	ldr	x0, [x22, 32]
	b	.L434
	.size	VP6_Set_DecParam, .-VP6_Set_DecParam
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC92:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_CfgTable
	.type	VP6_CfgTable, %function
VP6_CfgTable:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	x25, x1
	add	x20, x22, 2242
	bl	_mcount
	ldr	x21, .LC93
	stp	xzr, xzr, [x29, 96]
	add	x19, x22, 4
	add	x23, x22, 34
.L444:
	ldr	x3, [x21, 104]
	mov	x1, x19
	mov	x0, x20
	mov	x2, 10
	add	x19, x19, x2
	add	x20, x20, 16
	blr	x3
	cmp	x19, x23
	bne	.L444
	add	x24, x22, 2306
	add	x19, x22, 44
	add	x26, x22, 404
	.p2align 2
.L445:
	add	x23, x19, 90
	mov	x20, x24
	.p2align 2
.L446:
	ldr	x3, [x21, 104]
	mov	x1, x19
	mov	x0, x20
	mov	x2, 9
	add	x19, x19, x2
	add	x20, x20, 16
	blr	x3
	cmp	x23, x19
	bne	.L446
	cmp	x23, x26
	add	x24, x24, 160
	mov	x19, x23
	bne	.L445
	ldr	x3, [x21, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x29, 96
	blr	x3
	ldrb	w5, [x22]
	ldrb	w4, [x22, 2]
	ldrb	w3, [x22, 484]
	ldrb	w0, [x22, 485]
	ldrb	w2, [x22, 486]
	ldrb	w1, [x22, 487]
	strb	w5, [x29, 96]
	strb	w4, [x29, 97]
	ldrb	w5, [x22, 488]
	ldrb	w4, [x22, 489]
	strb	w3, [x29, 98]
	strb	w0, [x29, 99]
	ldr	x3, [x21, 104]
	ldrb	w0, [x22, 490]
	strb	w5, [x29, 102]
	strb	w4, [x29, 103]
	strb	w2, [x29, 100]
	mov	x2, 16
	strb	w1, [x29, 101]
	add	x1, x29, 96
	strb	w0, [x29, 104]
	add	x0, x22, 2946
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x29, 96
	blr	x3
	strb	wzr, [x29, 105]
	ldrb	w5, [x22]
	ldrb	w4, [x22, 498]
	ldrb	w3, [x22, 499]
	ldrb	w0, [x22, 500]
	ldrb	w2, [x22, 501]
	ldrb	w1, [x22, 502]
	strb	w5, [x29, 96]
	strb	w4, [x29, 97]
	ldrb	w5, [x22, 503]
	ldrb	w4, [x22, 504]
	strb	w3, [x29, 98]
	strb	w0, [x29, 99]
	ldr	x3, [x21, 104]
	ldrb	w0, [x22, 505]
	strb	w5, [x29, 102]
	strb	w4, [x29, 103]
	strb	w2, [x29, 100]
	mov	x2, 16
	strb	w1, [x29, 101]
	add	x1, x29, 96
	strb	w0, [x29, 104]
	add	x0, x22, 2962
	strb	wzr, [x29, 106]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x29, 96
	blr	x3
	ldrb	w5, [x22, 1]
	ldrb	w4, [x22, 3]
	ldrb	w3, [x22, 491]
	ldrb	w0, [x22, 492]
	ldrb	w2, [x22, 493]
	ldrb	w1, [x22, 494]
	strb	w5, [x29, 96]
	strb	w4, [x29, 97]
	ldrb	w5, [x22, 495]
	ldrb	w4, [x22, 496]
	strb	w3, [x29, 98]
	strb	w0, [x29, 99]
	ldr	x3, [x21, 104]
	ldrb	w0, [x22, 497]
	strb	w5, [x29, 102]
	strb	w4, [x29, 103]
	strb	w2, [x29, 100]
	mov	x2, 16
	strb	w1, [x29, 101]
	add	x1, x29, 96
	strb	w0, [x29, 104]
	add	x0, x22, 2978
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x29, 96
	blr	x3
	strb	wzr, [x29, 105]
	ldrb	w2, [x22, 1]
	ldrb	w1, [x22, 506]
	ldrb	w3, [x22, 507]
	ldrb	w0, [x22, 508]
	ldrb	w5, [x22, 509]
	ldrb	w4, [x22, 510]
	strb	w2, [x29, 96]
	strb	w1, [x29, 97]
	ldrb	w2, [x22, 511]
	ldrb	w1, [x22, 512]
	strb	w3, [x29, 98]
	strb	w0, [x29, 99]
	ldr	x3, [x21, 104]
	ldrb	w0, [x22, 513]
	strb	w2, [x29, 102]
	mov	x2, 16
	strb	w1, [x29, 103]
	add	x1, x29, 96
	strb	w0, [x29, 104]
	add	x0, x22, 2994
	strb	w5, [x29, 100]
	strb	w4, [x29, 101]
	strb	wzr, [x29, 106]
	blr	x3
	ldr	w0, [x25, 72]
	cbnz	w0, .L448
	add	x20, x22, 4096
	mov	w25, 0
	add	x19, x20, 2
.L449:
	sxtw	x1, w25
	ldr	x3, [x21, 104]
	add	x1, x1, 1152
	mov	x0, x19
	mov	x2, 11
	add	x1, x22, x1
	add	w25, w25, 11
	add	x19, x19, 16
	blr	x3
	cmp	w25, 33
	bne	.L449
	add	x19, x20, 50
.L450:
	sxtw	x1, w25
	ldr	x3, [x21, 104]
	add	x1, x1, 1152
	mov	x0, x19
	mov	x2, 11
	add	x1, x22, x1
	add	w25, w25, 11
	add	x19, x19, 16
	blr	x3
	cmp	w25, 66
	bne	.L450
	ldr	x3, [x21, 104]
	mov	x2, 14
	add	x1, x22, 536
	add	x0, x20, 674
	add	x27, x20, 98
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 14
	add	x1, x22, 550
	add	x0, x20, 690
	blr	x3
.L457:
	sub	w23, w25, #66
	mov	x26, x27
	.p2align 2
.L460:
	add	w24, w23, 198
	mov	x20, x26
	mov	w19, w23
.L458:
	add	x1, x22, x19, sxtw
	ldr	x3, [x21, 104]
	mov	x0, x20
	mov	x2, 11
	add	x1, x1, 564
	add	w19, w19, 66
	add	x20, x20, 16
	blr	x3
	cmp	w24, w19
	bne	.L458
	add	w23, w23, 11
	add	x26, x26, 48
	cmp	w25, w23
	bne	.L460
	add	w25, w25, 198
	add	x27, x27, 288
	cmp	w25, 462
	bne	.L457
.L456:
	ldr	x3, [x21, 104]
	add	x1, x22, 960
	mov	x2, 64
	add	x0, x22, 3010
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x22, 1024
	mov	x2, 64
	add	x0, x22, 3074
	blr	x3
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 112
	ret
.L448:
	add	x19, x22, 4096
	add	x20, x22, 8192
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x20, 1308
	add	x0, x19, 706
	add	x25, x19, 1602
	add	x26, x20, 1436
	blr	x3
	add	x27, x19, 3138
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x20, 3740
	add	x0, x19, 2370
	blr	x3
.L451:
	sub	x19, x25, #768
	mov	x24, x26
.L455:
	add	x23, x19, 256
	mov	x20, x24
.L452:
	ldr	x3, [x21, 104]
	mov	x2, 64
	mov	x1, x20
	mov	x0, x19
	add	x20, x20, x2
	add	x19, x19, x2
	blr	x3
	cmp	x19, x23
	bne	.L452
	cmp	x25, x19
	add	x24, x24, 384
	bne	.L455
	add	x25, x25, 768
	add	x26, x26, 1152
	cmp	x27, x25
	bne	.L451
	ldr	x3, [x21, 104]
	mov	x2, 960
	add	x1, x22, 1218
	add	x0, x22, 3138
	blr	x3
	b	.L456
	.size	VP6_CfgTable, .-VP6_CfgTable
	.align	3
.LC93:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VP6_BuildTables.part.2, %function
VP6_BuildTables.part.2:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	x23, x2
	bl	_mcount
	ldr	w0, [x20, 24]
	cbz	w0, .L471
	mov	x2, x20
	mov	x1, x23
	mov	x0, x19
	bl	VP6_DecodeModeProbs
	mov	x2, x20
	mov	x1, x23
	mov	x0, x19
	bl	VP6_ConfigureMvEntropyDecoder
	ldr	w3, [x20, 24]
	mov	x0, x19
	mov	x2, x20
	mov	x1, x23
	bl	VP6_ConfigureEntropyDecoder
	ldr	w0, [x20, 72]
	cbnz	w0, .L477
.L473:
	mov	x1, x20
	mov	x0, x19
	bl	VP6_CfgTable
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L471:
	ldr	x22, .LC94
	mov	x2, 80
	ldr	x21, .LC95
	add	x0, x19, 404
	ldr	x3, [x22, 104]
	mov	x1, x21
	blr	x3
	mov	x2, 2
	ldr	x3, [x22, 104]
	add	x1, x21, 80
	add	x0, x19, x2
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 14
	add	x1, x21, 88
	add	x0, x19, 484
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 2
	add	x1, x21, 104
	mov	x0, x19
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 16
	add	x1, x21, 112
	add	x0, x19, 498
	blr	x3
	ldr	x3, [x22, 104]
	mov	x2, 64
	add	x1, x21, 128
	add	x0, x19, 1088
	blr	x3
	mov	x1, x20
	mov	x0, x19
	bl	VP6_BuildScanOrder
	ldr	w3, [x20, 24]
	mov	x0, x19
	mov	x2, x20
	mov	x1, x23
	bl	VP6_ConfigureEntropyDecoder
	ldr	w0, [x20, 72]
	cbz	w0, .L473
.L477:
	mov	x0, x19
	bl	VP6_ConvertBoolToHuff
	b	.L473
	.size	VP6_BuildTables.part.2, .-VP6_BuildTables.part.2
	.align	3
.LC94:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC95:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_BuildTables
	.type	VP6_BuildTables, %function
VP6_BuildTables:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	cmp	x20, xzr
	ccmp	x21, xzr, 4, ne
	ccmp	x19, xzr, 4, ne
	beq	.L480
	mov	x2, x21
	mov	x1, x20
	mov	x0, x19
	bl	VP6_BuildTables.part.2
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L480:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP6_BuildTables, .-VP6_BuildTables
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsFrameSizeChanged
	.type	IsFrameSizeChanged, %function
IsFrameSizeChanged:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 12140]
	ldr	w0, [x19, 12288]
	cmp	w1, w0
	beq	.L484
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L484:
	ldr	w0, [x19, 12292]
	ldr	w1, [x19, 12144]
	ldr	x19, [sp, 16]
	cmp	w1, w0
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	IsFrameSizeChanged, .-IsFrameSizeChanged
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6DEC_Decode
	.type	VP6DEC_Decode, %function
VP6DEC_Decode:
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
	beq	.L532
	ldr	x1, [x20]
	add	x21, x19, 296
	str	x1, [x19, 296]
	ldr	w0, [x20, 16]
	str	w0, [x21, 8]
	ldr	w2, [x20, 20]
	str	w2, [x21, 12]
	cbnz	w2, .L488
	add	x20, x19, 312
	mov	w1, 3
	add	x0, x20, 8192
	strb	w1, [x0, 3888]
.L489:
	mov	x0, x19
	bl	VP6_DecodeDecide
	cmp	w0, 1
	mov	w21, w0
	beq	.L510
	ldr	x1, .LC111
	mov	w0, 1
	mov	w19, 0
	bl	dprint_vfmw
.L487:
	mov	w0, w19
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L488:
	cmp	w2, 2
	ble	.L533
	add	x23, x19, 12288
	add	x20, x19, 312
	add	x22, x23, 432
	mov	x0, x22
	bl	BsInit
	str	x21, [x19, 288]
	mov	x1, x22
	mov	x0, x20
	bl	VP6_GetPictureHeader
	cmp	w0, 1
	bne	.L534
	add	x1, x20, 8192
	cmp	x20, xzr
	add	x1, x1, 4068
	ccmp	x1, xzr, 4, ne
	ccmp	x22, xzr, 4, ne
	beq	.L493
	mov	x2, x22
	mov	x0, x20
	bl	VP6_BuildTables.part.2
	cmp	w0, 1
	bne	.L493
	ldr	w0, [x20, 12076]
	cbz	w0, .L494
	ldr	w0, [x19, 12600]
	ldr	w1, [x20, 12140]
	cmp	w1, w0
	bne	.L494
	ldr	w1, [x20, 12144]
	ldr	w0, [x20, 12292]
	cmp	w1, w0
	beq	.L489
	.p2align 2
.L494:
	ldr	x21, .LC103
	ldr	x4, [x21]
	cbz	x4, .L496
	ldr	w0, [x20, 12140]
	ldr	w1, [x19, 12600]
	ldr	w3, [x20, 12144]
	ldr	w2, [x20, 12292]
	strh	w0, [x29, 74]
	ldr	w0, [x19, 13368]
	strh	w1, [x29, 78]
	mov	w1, 2
	strh	w3, [x29, 72]
	mov	w3, 8
	strh	w2, [x29, 76]
	add	x2, x29, 72
	blr	x4
.L496:
	ldr	w0, [x19, 13368]
	bl	FSP_GetFspType
	cbnz	w0, .L497
	add	x3, x29, 80
	ldr	w0, [x19, 13368]
	add	x2, x29, 68
	add	x1, x29, 64
	stp	wzr, wzr, [x29, 64]
	str	wzr, [x3, -8]!
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19]
	ldr	w2, [x0, 772]
	cmp	w2, 1
	bne	.L497
	ldr	w0, [x29, 72]
	cmp	w0, wzr
	bgt	.L500
	ldr	w0, [x29, 68]
	cmp	w0, 32
	bgt	.L500
	ldr	x0, [x19, 8]
	cbnz	x0, .L500
	ldr	w3, [x20, 12144]
	cbz	w3, .L497
	ldr	w6, [x19, 12600]
	ldr	w0, [x19, 13372]
	cmp	w6, w0
	beq	.L497
	ldr	w0, [x19, 13376]
	ldr	w5, [x20, 12292]
	cmp	w5, w0
	beq	.L497
	ldr	w4, [x20, 12140]
	mov	w0, w2
	ldr	x1, .LC105
	bl	dprint_vfmw
	ldr	w0, [x19, 12600]
	str	w0, [x19, 13372]
	ldr	x4, [x21]
	ldr	w0, [x20, 12292]
	str	w0, [x19, 13376]
	cbz	x4, .L497
	ldr	w0, [x19, 13368]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	.p2align 2
.L497:
	ldr	w0, [x19, 13368]
	mov	w2, 1
	ldr	w1, [x20, 12092]
	add	x23, x23, 472
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 12096]
	mov	w2, 1
	ldr	w0, [x19, 13368]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 12092]
	str	wzr, [x20, 12096]
	ldr	w0, [x19, 13368]
	bl	FSP_GetNullLogicFs
	str	wzr, [x20, 12072]
	str	w0, [x20, 12092]
	mov	x1, x23
	str	w0, [x20, 12096]
	ldr	w0, [x19, 13368]
	bl	FSP_ClearNotInVoQueue
	ldr	w2, [x20, 12292]
	ldr	w3, [x19, 12600]
	cmp	w2, 512
	bhi	.L504
	cmp	w3, 512
	bhi	.L504
	ldr	x0, [x19]
	ldr	w1, [x0, 772]
	cbnz	w1, .L506
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L535
.L506:
	ldr	w0, [x19, 13368]
	bl	FSP_GetFspType
	cbz	w0, .L531
.L508:
	mov	x0, x19
	bl	VP6_ArrangeVHBMem
	cmp	w0, 1
	beq	.L489
	ldr	x1, .LC109
	mov	w0, 1
	mov	w19, 0
	bl	dprint_vfmw
	b	.L487
	.p2align 3
.L532:
	ldr	x1, .LC96
	mov	w2, 2597
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L534:
	ldr	x1, .LC100
	mov	w0, 1
	mov	w19, 0
	bl	dprint_vfmw
	b	.L487
	.p2align 3
.L510:
	mov	x0, x19
	bl	VP6_GetImageBuffer
	cmp	w0, 1
	mov	w22, w0
	beq	.L511
	ldr	x1, .LC113
	mov	w0, w21
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L533:
	ldr	x1, .LC98
	mov	w0, 1
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L511:
	mov	w2, w0
	ldr	w1, [x20, 12088]
	ldr	w0, [x19, 13368]
	bl	FSP_SetRef
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 12088]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L536
	ldr	x3, [x19]
	mov	x4, -1
	ldr	x1, .LC116
	mov	w0, 29
	ldr	x3, [x3, 64]
	str	x3, [x2, 584]
	ldr	x3, [x19]
	ldr	x3, [x3, 80]
	str	x3, [x2, 592]
	ldr	x3, [x19]
	ldr	x3, [x3, 96]
	str	x3, [x2, 600]
	ldr	x3, [x19]
	ldr	w3, [x3, 112]
	str	w3, [x2]
	ldr	x3, [x19]
	ldr	w3, [x3, 116]
	str	w3, [x2, 4]
	ldr	x3, [x19]
	ldr	w3, [x3, 120]
	str	w3, [x2, 8]
	ldr	x3, [x19]
	ldr	w3, [x3, 136]
	str	w3, [x2, 12]
	str	wzr, [x2, 52]
	ldr	x3, [x19]
	str	x4, [x3, 64]
	ldr	x3, [x2, 592]
	ldr	x2, [x2, 584]
	bl	dprint_vfmw
	mov	x0, x19
	bl	VP6_Set_DecParam
	cmp	w0, 1
	mov	w19, w0
	beq	.L513
	ldr	x1, .LC118
	mov	w0, w22
	mov	w19, 0
	bl	dprint_vfmw
	b	.L487
	.p2align 3
.L493:
	ldr	x1, .LC102
	mov	w0, 1
	mov	w19, 0
	bl	dprint_vfmw
	b	.L487
	.p2align 3
.L513:
	add	x0, x20, 8192
	ldr	x3, .LC119
	mov	x2, 148
	ldrb	w1, [x0, 3888]
	cbz	w1, .L537
	ldr	x3, [x3, 104]
	add	x1, x0, 4068
	add	x0, x0, 3920
	ldr	w22, [x20, 12128]
	ldr	w21, [x20, 12132]
	blr	x3
	str	w22, [x20, 12128]
	str	w21, [x20, 12132]
.L515:
	ldr	x1, .LC121
	mov	w0, 22
	bl	dprint_vfmw
	b	.L487
	.p2align 3
.L504:
	ldr	x1, .LC107
	mov	w0, 18
	mov	w19, 0
	bl	dprint_vfmw
	b	.L487
.L535:
	ldr	w0, [x20, 12076]
	cbnz	w0, .L508
.L531:
	mov	x0, x23
	bl	ResetVoQueue
	b	.L508
.L537:
	ldr	x3, [x3, 104]
	add	x1, x0, 4068
	add	x0, x0, 3920
	blr	x3
	b	.L515
.L536:
	ldr	x1, .LC114
	mov	w2, 2738
	mov	w0, 22
	mov	w19, 0
	bl	dprint_vfmw
	b	.L487
.L500:
	mov	w19, -2
	b	.L487
	.size	VP6DEC_Decode, .-VP6DEC_Decode
	.align	3
.LC96:
	.xword	.LC17
	.align	3
.LC98:
	.xword	.LC97
	.align	3
.LC100:
	.xword	.LC99
	.align	3
.LC102:
	.xword	.LC101
	.align	3
.LC103:
	.xword	g_event_report
	.align	3
.LC105:
	.xword	.LC104
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.align	3
.LC114:
	.xword	.LC11
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC119:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC121:
	.xword	.LC120
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6_SetImgFormat
	.type	VP6_SetImgFormat, %function
VP6_SetImgFormat:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 312
	bl	_mcount
	ldr	w1, [x20, 12400]
	ldr	w0, [x20, 13368]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L538
	add	x5, x21, 8192
	ldrb	w3, [x0, 64]
	ldrb	w1, [x0, 65]
	mov	w4, 1
	mov	w6, 5
	ldrb	w2, [x5, 3888]
	and	w1, w1, -4
	orr	w1, w1, 12
	bfi	w3, w2, 0, 2
	bfi	w1, w4, 4, 2
	and	w3, w3, -29
	strb	w1, [x0, 65]
	bfi	w3, w6, 5, 3
	strb	w3, [x0, 64]
	and	w2, w2, 3
	mov	w3, 8
	ldr	w1, [x0, 64]
	and	w1, w1, -114689
	str	w1, [x0, 64]
	lsr	w1, w1, 16
	ldrb	w5, [x5, 4075]
	bfi	w1, w5, 1, 1
	strb	w1, [x0, 66]
	mov	w5, 10
	mov	w1, 0
	ldr	w6, [x20, 12580]
	stp	w2, w2, [x0, 56]
	add	x2, x0, 256
	strb	wzr, [x0, 284]
	strb	w4, [x0, 291]
	strb	w4, [x0, 289]
	str	w6, [x0, 120]
	stp	w5, w3, [x2, 40]
	stp	w3, w3, [x2, 48]
	bl	SetAspectRatio
	ldr	w1, [x20, 12604]
	lsl	w1, w1, 4
	str	w1, [x19, 68]
	ldr	w0, [x20, 12600]
	lsl	w0, w0, 4
	str	w0, [x19, 72]
	ldr	x2, [x20]
	ldr	w2, [x2, 28]
	cmp	w2, 25
	beq	.L544
.L540:
	lsr	w3, w1, 1
	lsr	w2, w0, 1
	stp	w1, w0, [x19, 76]
	stp	w3, w2, [x19, 84]
.L538:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L544:
	ldr	w5, [x19, 112]
	lsr	w3, w0, 4
	ldr	w4, [x19, 36]
	lsl	w2, w5, 4
	ldr	x6, [x19, 504]
	add	w7, w5, w4
	mul	w2, w3, w2
	add	w3, w2, w4
	str	w3, [x19, 40]
	add	w5, w5, w3
	add	x2, x6, x2, sxtw
	stp	w4, w3, [x19, 20]
	stp	w7, w5, [x19, 28]
	str	x2, [x19, 512]
	b	.L540
	.size	VP6_SetImgFormat, .-VP6_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6DEC_VDMPostProc
	.type	VP6DEC_VDMPostProc, %function
VP6DEC_VDMPostProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L579
	ldr	x1, .LC124
	mov	w2, w21
	mov	w0, 22
	add	x23, x19, 12288
	add	x20, x19, 312
	bl	dprint_vfmw
	ldr	x3, [x19, 8]
	mov	x1, x19
	mov	w0, 10
	ldrb	w4, [x3, 104]
	strb	w4, [x23, 291]
	ldr	w3, [x3, 264]
	str	w3, [x23, 292]
	bl	ReleasePacket
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 12088]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L580
	tbnz	w21, #31, .L549
	cmp	w21, 100
	mov	w2, 100
	csel	w2, w21, w2, le
	str	w2, [x0, 152]
	ldr	x0, [x19]
	ldr	w3, [x0]
	cmp	w2, w3
	bhi	.L581
	mov	x0, x19
	bl	VP6_SetImgFormat
	ldr	w0, [x20, 12068]
	mov	w1, 1
	str	w1, [x20, 12072]
	cmp	w0, 2
	beq	.L582
.L551:
	ldr	w1, [x20, 12088]
	str	w1, [x20, 12100]
.L552:
	cmn	w1, #1
	beq	.L553
	ldr	w0, [x19, 13368]
	mov	w2, 1
	bl	FSP_SetDisplay
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 12100]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L583
	mov	x4, x0
	ldr	w0, [x19, 13368]
	add	x3, x23, 472
	mov	x2, x19
	mov	w1, 10
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w21, w0
	bne	.L584
.L553:
	ldr	w0, [x20, 12092]
	ldr	w3, [x20, 12096]
	cmp	w3, w0
	beq	.L585
.L578:
	ldr	w1, [x20, 12088]
	cmp	w3, w1
	beq	.L556
	ldr	w0, [x19, 13368]
	mov	w2, 0
	mov	w1, w3
	bl	FSP_SetRef
.L576:
	ldr	w1, [x20, 12088]
.L556:
	str	w1, [x20, 12096]
	mov	w2, 1
	ldr	w0, [x19, 13368]
	bl	FSP_SetRef
	add	x0, x20, 8192
	ldrb	w0, [x0, 3888]
	cbnz	w0, .L586
	ldr	w1, [x20, 12088]
	ldr	w3, [x20, 12092]
	cmp	w3, w1
	beq	.L559
.L587:
	ldr	w0, [x19, 13368]
	mov	w1, w3
	mov	w2, 0
	bl	FSP_SetRef
	ldr	w1, [x20, 12088]
.L559:
	str	w1, [x20, 12092]
	mov	w2, 1
	ldr	w0, [x19, 13368]
	bl	FSP_SetRef
	mov	w0, 1
.L569:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L586:
	ldr	w1, [x20, 12084]
	mov	w0, 1
	cbz	w1, .L569
	ldr	w1, [x20, 12088]
	ldr	w3, [x20, 12092]
	cmp	w3, w1
	bne	.L587
	b	.L559
	.p2align 3
.L549:
	str	wzr, [x0, 152]
	mov	x0, x19
	bl	VP6_SetImgFormat
	ldr	w0, [x20, 12068]
	mov	w1, 1
	str	w1, [x20, 12072]
	cmp	w0, 2
	bne	.L551
.L582:
	add	x0, x20, 8192
	ldrb	w0, [x0, 3888]
	cbz	w0, .L551
	mov	w0, -1
	str	w0, [x20, 12100]
	ldr	w1, [x20, 12088]
	mov	w2, 0
	ldr	w0, [x19, 13368]
	bl	FSP_SetDisplay
	ldr	w1, [x20, 12100]
	b	.L552
	.p2align 3
.L584:
	ldr	w0, [x19, 13368]
	mov	w2, 0
	ldr	w1, [x20, 12088]
	bl	FSP_SetRef
	ldr	w0, [x19, 13368]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x19, 13368]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	mov	w2, 0
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 12100]
	bl	FSP_SetDisplay
	ldr	x1, .LC132
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L579:
	ldr	x1, .LC122
	mov	w2, 2873
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L585:
	ldr	w0, [x19, 13368]
	mov	w1, w3
	bl	FSP_GetRef
	cbnz	w0, .L576
	ldr	w3, [x20, 12096]
	b	.L578
	.p2align 3
.L581:
	ldr	x1, .LC128
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 13368]
	mov	w2, 0
	ldr	w1, [x20, 12088]
	bl	FSP_SetRef
	ldr	w0, [x19, 13368]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x19, 13368]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	mov	w2, 0
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 12088]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 13368]
	mov	w2, 1
	ldr	w1, [x20, 12092]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 13368]
	mov	w2, 1
	ldr	w1, [x20, 12096]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 12092]
	str	wzr, [x20, 12096]
	ldr	w0, [x19, 13368]
	bl	FSP_GetNullLogicFs
	str	wzr, [x20, 12072]
	str	w0, [x20, 12092]
	str	w0, [x20, 12096]
	mov	w0, -1
	b	.L569
.L583:
	ldr	x1, .LC130
	mov	x2, 0
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L569
.L580:
	ldr	x1, .LC126
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L569
	.size	VP6DEC_VDMPostProc, .-VP6DEC_VDMPostProc
	.align	3
.LC122:
	.xword	.LC17
	.align	3
.LC124:
	.xword	.LC123
	.align	3
.LC126:
	.xword	.LC125
	.align	3
.LC128:
	.xword	.LC127
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC132:
	.xword	.LC131
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6DEC_RecycleImage
	.type	VP6DEC_RecycleImage, %function
VP6DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L592
	ldr	w0, [x19, 13368]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x19, 13368]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L591
	ldr	w0, [x19, 13368]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 13368]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L591:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L592:
	ldr	x1, .LC133
	mov	w2, 3003
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP6DEC_RecycleImage, .-VP6DEC_RecycleImage
	.align	3
.LC133:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP6DEC_GetRemainImg
	.type	VP6DEC_GetRemainImg, %function
VP6DEC_GetRemainImg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L596
	add	x0, x19, 12288
	add	x0, x0, 472
	bl	GetVoLastImageID
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L596:
	ldr	x1, .LC134
	mov	w2, 3038
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	VP6DEC_GetRemainImg, .-VP6DEC_GetRemainImg
	.align	3
.LC134:
	.xword	.LC17
	.global	DefaultScanBands
	.global	ZrlUpdateProbs
	.global	ScanBandUpdateProbs
	.global	ZeroRunProbDefaults
	.global	VP6_AcUpdateProbs
	.global	VP6_DcUpdateProbs
	.global	DefaultSignProbs
	.global	DefaultIsShortProbs
	.global	DefaultMvLongProbs
	.global	DefaultMvShortProbs
	.global	VP6_MvUpdateProbs
	.global	VP6_BaselineXmittedProbs
	.global	VP6_ModeVq
	.global	VP6_DcNodeEqs
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	VP6_DcNodeEqs, %object
	.size	VP6_DcNodeEqs, 120
VP6_DcNodeEqs:
	.word	122
	.word	133
	.word	133
	.word	51
	.word	142
	.word	-16
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	78
	.word	171
	.word	169
	.word	71
	.word	221
	.word	-30
	.word	139
	.word	117
	.word	214
	.word	44
	.word	246
	.word	-3
	.word	168
	.word	79
	.word	210
	.word	38
	.word	203
	.word	17
	.type	VP6_DcUpdateProbs, %object
	.size	VP6_DcUpdateProbs, 22
VP6_DcUpdateProbs:
	.byte	-110
	.byte	-1
	.byte	-75
	.byte	-49
	.byte	-24
	.byte	-13
	.byte	-18
	.byte	-5
	.byte	-12
	.byte	-6
	.byte	-7
	.byte	-77
	.byte	-1
	.byte	-42
	.byte	-16
	.byte	-6
	.byte	-1
	.byte	-12
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.zero	2
	.type	ZeroRunProbDefaults, %object
	.size	ZeroRunProbDefaults, 28
ZeroRunProbDefaults:
	.byte	-58
	.byte	-59
	.byte	-60
	.byte	-110
	.byte	-58
	.byte	-52
	.byte	-87
	.byte	-114
	.byte	-126
	.byte	-120
	.byte	-107
	.byte	-107
	.byte	-65
	.byte	-7
	.byte	-121
	.byte	-55
	.byte	-75
	.byte	-102
	.byte	98
	.byte	117
	.byte	-124
	.byte	126
	.byte	-110
	.byte	-87
	.byte	-72
	.byte	-16
	.byte	-10
	.byte	-2
	.zero	4
	.type	ScanBandUpdateProbs, %object
	.size	ScanBandUpdateProbs, 64
ScanBandUpdateProbs:
	.byte	-1
	.byte	-124
	.byte	-124
	.byte	-97
	.byte	-103
	.byte	-105
	.byte	-95
	.byte	-86
	.byte	-92
	.byte	-94
	.byte	-120
	.byte	110
	.byte	103
	.byte	114
	.byte	-127
	.byte	118
	.byte	124
	.byte	125
	.byte	-124
	.byte	-120
	.byte	114
	.byte	110
	.byte	-114
	.byte	-121
	.byte	-122
	.byte	123
	.byte	-113
	.byte	126
	.byte	-103
	.byte	-73
	.byte	-90
	.byte	-95
	.byte	-85
	.byte	-76
	.byte	-77
	.byte	-92
	.byte	-53
	.byte	-38
	.byte	-31
	.byte	-39
	.byte	-41
	.byte	-50
	.byte	-53
	.byte	-39
	.byte	-27
	.byte	-15
	.byte	-8
	.byte	-13
	.byte	-3
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.type	ZrlUpdateProbs, %object
	.size	ZrlUpdateProbs, 28
ZrlUpdateProbs:
	.byte	-37
	.byte	-10
	.byte	-18
	.byte	-7
	.byte	-24
	.byte	-17
	.byte	-7
	.byte	-1
	.byte	-8
	.byte	-3
	.byte	-17
	.byte	-12
	.byte	-15
	.byte	-8
	.byte	-58
	.byte	-24
	.byte	-5
	.byte	-3
	.byte	-37
	.byte	-15
	.byte	-3
	.byte	-1
	.byte	-8
	.byte	-7
	.byte	-12
	.byte	-18
	.byte	-5
	.byte	-1
	.zero	4
	.type	VP6_AcUpdateProbs, %object
	.size	VP6_AcUpdateProbs, 396
VP6_AcUpdateProbs:
	.byte	-29
	.byte	-10
	.byte	-26
	.byte	-9
	.byte	-12
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-47
	.byte	-25
	.byte	-25
	.byte	-7
	.byte	-7
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-31
	.byte	-14
	.byte	-15
	.byte	-5
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-15
	.byte	-3
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-50
	.byte	-53
	.byte	-29
	.byte	-17
	.byte	-9
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-49
	.byte	-57
	.byte	-36
	.byte	-20
	.byte	-13
	.byte	-4
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-44
	.byte	-37
	.byte	-26
	.byte	-13
	.byte	-12
	.byte	-3
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-20
	.byte	-19
	.byte	-9
	.byte	-4
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-16
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-26
	.byte	-23
	.byte	-7
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-18
	.byte	-18
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-5
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-31
	.byte	-17
	.byte	-29
	.byte	-25
	.byte	-12
	.byte	-3
	.byte	-13
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-24
	.byte	-22
	.byte	-32
	.byte	-28
	.byte	-14
	.byte	-7
	.byte	-14
	.byte	-4
	.byte	-5
	.byte	-5
	.byte	-1
	.byte	-21
	.byte	-7
	.byte	-18
	.byte	-16
	.byte	-5
	.byte	-1
	.byte	-7
	.byte	-1
	.byte	-3
	.byte	-3
	.byte	-1
	.byte	-7
	.byte	-3
	.byte	-5
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-6
	.byte	-7
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-13
	.byte	-12
	.byte	-6
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-8
	.byte	-6
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.zero	4
	.type	VP6_ModeVq, %object
	.size	VP6_ModeVq, 960
VP6_ModeVq:
	.byte	9
	.byte	15
	.byte	32
	.byte	25
	.byte	7
	.byte	19
	.byte	9
	.byte	21
	.byte	1
	.byte	12
	.byte	14
	.byte	12
	.byte	3
	.byte	18
	.byte	14
	.byte	23
	.byte	3
	.byte	10
	.byte	0
	.byte	4
	.byte	48
	.byte	39
	.byte	1
	.byte	2
	.byte	11
	.byte	27
	.byte	29
	.byte	44
	.byte	7
	.byte	27
	.byte	1
	.byte	4
	.byte	0
	.byte	3
	.byte	1
	.byte	6
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	21
	.byte	32
	.byte	1
	.byte	2
	.byte	4
	.byte	10
	.byte	32
	.byte	43
	.byte	6
	.byte	23
	.byte	2
	.byte	3
	.byte	1
	.byte	19
	.byte	1
	.byte	6
	.byte	12
	.byte	21
	.byte	0
	.byte	7
	.byte	69
	.byte	83
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	10
	.byte	29
	.byte	3
	.byte	12
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	0
	.byte	0
	.byte	11
	.byte	20
	.byte	1
	.byte	4
	.byte	18
	.byte	36
	.byte	43
	.byte	48
	.byte	13
	.byte	35
	.byte	0
	.byte	2
	.byte	0
	.byte	5
	.byte	3
	.byte	12
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	70
	.byte	44
	.byte	0
	.byte	1
	.byte	2
	.byte	10
	.byte	37
	.byte	46
	.byte	8
	.byte	26
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	8
	.byte	15
	.byte	0
	.byte	1
	.byte	8
	.byte	21
	.byte	74
	.byte	53
	.byte	22
	.byte	42
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	3
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	-115
	.byte	42
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	11
	.byte	24
	.byte	1
	.byte	11
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	19
	.byte	4
	.byte	10
	.byte	24
	.byte	45
	.byte	21
	.byte	37
	.byte	9
	.byte	29
	.byte	0
	.byte	3
	.byte	1
	.byte	7
	.byte	11
	.byte	25
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	46
	.byte	42
	.byte	0
	.byte	1
	.byte	2
	.byte	10
	.byte	54
	.byte	51
	.byte	10
	.byte	30
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	28
	.byte	32
	.byte	0
	.byte	0
	.byte	3
	.byte	10
	.byte	75
	.byte	51
	.byte	14
	.byte	33
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	100
	.byte	46
	.byte	0
	.byte	1
	.byte	3
	.byte	9
	.byte	21
	.byte	37
	.byte	5
	.byte	20
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	1
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	27
	.byte	29
	.byte	0
	.byte	1
	.byte	9
	.byte	25
	.byte	53
	.byte	51
	.byte	12
	.byte	34
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	1
	.byte	5
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	80
	.byte	38
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	69
	.byte	33
	.byte	5
	.byte	16
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	16
	.byte	20
	.byte	0
	.byte	0
	.byte	2
	.byte	8
	.byte	104
	.byte	49
	.byte	15
	.byte	33
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-62
	.byte	16
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	9
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	41
	.byte	22
	.byte	1
	.byte	0
	.byte	1
	.byte	31
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	7
	.byte	0
	.byte	1
	.byte	98
	.byte	25
	.byte	4
	.byte	10
	.byte	123
	.byte	37
	.byte	6
	.byte	4
	.byte	1
	.byte	27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	5
	.byte	8
	.byte	1
	.byte	7
	.byte	0
	.byte	1
	.byte	12
	.byte	10
	.byte	0
	.byte	2
	.byte	26
	.byte	14
	.byte	14
	.byte	12
	.byte	0
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	55
	.byte	17
	.byte	1
	.byte	9
	.byte	0
	.byte	36
	.byte	5
	.byte	7
	.byte	1
	.byte	3
	.byte	-47
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	5
	.byte	4
	.byte	5
	.byte	0
	.byte	121
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	2
	.byte	4
	.byte	1
	.byte	4
	.byte	2
	.byte	2
	.byte	0
	.byte	1
	.byte	-81
	.byte	5
	.byte	0
	.byte	1
	.byte	0
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	83
	.byte	5
	.byte	2
	.byte	3
	.byte	0
	.byte	102
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	3
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-23
	.byte	6
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	34
	.byte	16
	.byte	112
	.byte	21
	.byte	1
	.byte	28
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	8
	.byte	1
	.byte	7
	.byte	0
	.byte	3
	.byte	2
	.byte	5
	.byte	0
	.byte	2
	.byte	-97
	.byte	35
	.byte	2
	.byte	2
	.byte	0
	.byte	25
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	6
	.byte	0
	.byte	5
	.byte	0
	.byte	1
	.byte	4
	.byte	4
	.byte	0
	.byte	1
	.byte	75
	.byte	39
	.byte	5
	.byte	7
	.byte	2
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	11
	.byte	2
	.byte	16
	.byte	1
	.byte	4
	.byte	7
	.byte	10
	.byte	0
	.byte	2
	.byte	-44
	.byte	21
	.byte	0
	.byte	1
	.byte	0
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	2
	.byte	2
	.byte	0
	.byte	0
	.byte	4
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	-84
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	-69
	.byte	22
	.byte	1
	.byte	1
	.byte	0
	.byte	17
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	6
	.byte	0
	.byte	4
	.byte	0
	.byte	1
	.byte	4
	.byte	4
	.byte	0
	.byte	1
	.byte	-123
	.byte	6
	.byte	1
	.byte	2
	.byte	1
	.byte	70
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	4
	.byte	0
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-5
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	3
	.byte	2
	.byte	3
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	11
	.byte	4
	.byte	1
	.byte	4
	.byte	0
	.byte	2
	.byte	3
	.byte	2
	.byte	0
	.byte	4
	.byte	49
	.byte	46
	.byte	3
	.byte	4
	.byte	7
	.byte	31
	.byte	42
	.byte	41
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	1
	.byte	7
	.byte	1
	.byte	4
	.byte	2
	.byte	4
	.byte	0
	.byte	1
	.byte	26
	.byte	25
	.byte	1
	.byte	1
	.byte	2
	.byte	10
	.byte	67
	.byte	39
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	0
	.byte	14
	.byte	0
	.byte	2
	.byte	31
	.byte	26
	.byte	1
	.byte	6
	.byte	103
	.byte	46
	.byte	1
	.byte	2
	.byte	2
	.byte	10
	.byte	33
	.byte	42
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	14
	.byte	31
	.byte	9
	.byte	13
	.byte	14
	.byte	54
	.byte	22
	.byte	29
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	4
	.byte	18
	.byte	6
	.byte	13
	.byte	1
	.byte	5
	.byte	0
	.byte	1
	.byte	85
	.byte	39
	.byte	0
	.byte	0
	.byte	1
	.byte	9
	.byte	69
	.byte	40
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	0
	.byte	0
	.byte	31
	.byte	28
	.byte	0
	.byte	0
	.byte	3
	.byte	14
	.byte	-126
	.byte	34
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	3
	.byte	3
	.byte	0
	.byte	1
	.byte	-85
	.byte	25
	.byte	0
	.byte	0
	.byte	1
	.byte	5
	.byte	25
	.byte	21
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	17
	.byte	21
	.byte	68
	.byte	29
	.byte	6
	.byte	15
	.byte	13
	.byte	22
	.byte	0
	.byte	0
	.byte	6
	.byte	12
	.byte	3
	.byte	14
	.byte	4
	.byte	10
	.byte	1
	.byte	7
	.byte	0
	.byte	3
	.byte	51
	.byte	39
	.byte	0
	.byte	1
	.byte	2
	.byte	12
	.byte	91
	.byte	44
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	0
	.byte	1
	.byte	81
	.byte	25
	.byte	0
	.byte	0
	.byte	2
	.byte	9
	.byte	106
	.byte	26
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-116
	.byte	37
	.byte	0
	.byte	1
	.byte	1
	.byte	8
	.byte	24
	.byte	33
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	14
	.byte	23
	.byte	1
	.byte	3
	.byte	11
	.byte	53
	.byte	90
	.byte	31
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	1
	.byte	5
	.byte	2
	.byte	6
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	123
	.byte	29
	.byte	0
	.byte	0
	.byte	1
	.byte	7
	.byte	57
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	13
	.byte	14
	.byte	0
	.byte	0
	.byte	4
	.byte	20
	.byte	-81
	.byte	20
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-54
	.byte	23
	.byte	0
	.byte	0
	.byte	1
	.byte	3
	.byte	2
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	VP6_MvUpdateProbs, %object
	.size	VP6_MvUpdateProbs, 34
VP6_MvUpdateProbs:
	.byte	-19
	.byte	-10
	.byte	-3
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-6
	.byte	-6
	.byte	-4
	.byte	-25
	.byte	-13
	.byte	-11
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-5
	.byte	-5
	.byte	-2
	.zero	6
	.type	VP6_LoopFilterLimitValues, %object
	.size	VP6_LoopFilterLimitValues, 64
VP6_LoopFilterLimitValues:
	.byte	14
	.byte	14
	.byte	13
	.byte	13
	.byte	12
	.byte	12
	.byte	10
	.byte	10
	.byte	10
	.byte	10
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.type	DcQuantTab, %object
	.size	DcQuantTab, 128
DcQuantTab:
	.hword	188
	.hword	188
	.hword	188
	.hword	188
	.hword	180
	.hword	172
	.hword	172
	.hword	172
	.hword	172
	.hword	172
	.hword	168
	.hword	164
	.hword	164
	.hword	160
	.hword	160
	.hword	160
	.hword	160
	.hword	140
	.hword	140
	.hword	140
	.hword	140
	.hword	132
	.hword	132
	.hword	132
	.hword	132
	.hword	128
	.hword	128
	.hword	128
	.hword	108
	.hword	108
	.hword	104
	.hword	104
	.hword	100
	.hword	100
	.hword	96
	.hword	96
	.hword	92
	.hword	92
	.hword	76
	.hword	76
	.hword	76
	.hword	76
	.hword	72
	.hword	72
	.hword	68
	.hword	64
	.hword	64
	.hword	64
	.hword	64
	.hword	64
	.hword	60
	.hword	44
	.hword	44
	.hword	44
	.hword	40
	.hword	40
	.hword	36
	.hword	32
	.hword	28
	.hword	20
	.hword	12
	.hword	12
	.hword	8
	.hword	8
	.type	AcQuantTab, %object
	.size	AcQuantTab, 128
AcQuantTab:
	.hword	376
	.hword	368
	.hword	360
	.hword	352
	.hword	344
	.hword	328
	.hword	312
	.hword	296
	.hword	280
	.hword	264
	.hword	248
	.hword	232
	.hword	216
	.hword	212
	.hword	208
	.hword	204
	.hword	200
	.hword	196
	.hword	192
	.hword	188
	.hword	184
	.hword	180
	.hword	176
	.hword	172
	.hword	168
	.hword	160
	.hword	156
	.hword	148
	.hword	144
	.hword	140
	.hword	136
	.hword	132
	.hword	128
	.hword	124
	.hword	120
	.hword	116
	.hword	112
	.hword	108
	.hword	104
	.hword	100
	.hword	96
	.hword	92
	.hword	88
	.hword	84
	.hword	80
	.hword	76
	.hword	72
	.hword	68
	.hword	64
	.hword	60
	.hword	56
	.hword	52
	.hword	48
	.hword	44
	.hword	40
	.hword	36
	.hword	32
	.hword	28
	.hword	24
	.hword	20
	.hword	16
	.hword	12
	.hword	8
	.hword	4
	.type	__FUNCTION__.11262, %object
	.size	__FUNCTION__.11262, 17
__FUNCTION__.11262:
	.string	"VP6_DecodeDecide"
	.align	3
.LANCHOR1 = . + 0
	.type	VP6_BaselineXmittedProbs, %object
	.size	VP6_BaselineXmittedProbs, 80
VP6_BaselineXmittedProbs:
	.byte	42
	.byte	2
	.byte	7
	.byte	42
	.byte	22
	.byte	3
	.byte	2
	.byte	5
	.byte	1
	.byte	0
	.byte	69
	.byte	1
	.byte	1
	.byte	44
	.byte	6
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	8
	.byte	1
	.byte	8
	.byte	0
	.byte	0
	.byte	2
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	-27
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	35
	.byte	1
	.byte	6
	.byte	34
	.byte	0
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	122
	.byte	1
	.byte	1
	.byte	46
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	64
	.byte	0
	.byte	64
	.byte	64
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	64
	.byte	0
	.byte	64
	.byte	64
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	DefaultIsShortProbs, %object
	.size	DefaultIsShortProbs, 2
DefaultIsShortProbs:
	.byte	-94
	.byte	-92
	.zero	6
	.type	DefaultMvShortProbs, %object
	.size	DefaultMvShortProbs, 14
DefaultMvShortProbs:
	.byte	-31
	.byte	-110
	.byte	-84
	.byte	-109
	.byte	-42
	.byte	39
	.byte	-100
	.byte	-52
	.byte	-86
	.byte	119
	.byte	-21
	.byte	-116
	.byte	-26
	.byte	-28
	.zero	2
	.type	DefaultSignProbs, %object
	.size	DefaultSignProbs, 2
DefaultSignProbs:
	.byte	-128
	.byte	-128
	.zero	6
	.type	DefaultMvLongProbs, %object
	.size	DefaultMvLongProbs, 16
DefaultMvLongProbs:
	.byte	-9
	.byte	-46
	.byte	-121
	.byte	68
	.byte	-118
	.byte	-36
	.byte	-17
	.byte	-10
	.byte	-12
	.byte	-72
	.byte	-55
	.byte	44
	.byte	-83
	.byte	-35
	.byte	-17
	.byte	-3
	.type	DefaultScanBands, %object
	.size	DefaultScanBands, 64
DefaultScanBands:
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	3
	.byte	3
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	6
	.byte	6
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	8
	.byte	8
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	10
	.byte	10
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	13
	.byte	13
	.byte	13
	.byte	13
	.byte	13
	.byte	14
	.byte	14
	.byte	14
	.byte	14
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"image_size_in_mb abnormal(%d x %d)\n" )
	.zero	4
.LC2:
	ASCII(.string	"vp6 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC5:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC7:
	ASCII(.string	"FSP_ConfigInstance fail!\n" )
	.zero	6
.LC9:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC11:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC13:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC15:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC17:
	ASCII(.string	"line: %d\n" )
	.zero	6
.LC38:
	ASCII(.string	"enter VP6_ConvertBoolToHuff\n" )
	.zero	3
.LC40:
	ASCII(.string	"leave VP6_ConvertBoolToHuff\n" )
	.zero	3
.LC42:
	ASCII(.string	"enter VP6_IntraFrmHeader\n" )
	.zero	6
.LC44:
	ASCII(.string	"error: Vp3VersionNo %d > CURRENT_DECODE_VERSION(8)\n" )
	.zero	4
.LC46:
	ASCII(.string	"error: bitstream error!\n" )
	.zero	7
.LC48:
	ASCII(.string	"We have a new size image!\n The old size is %d x %d, and the new is %d x %d\n" )
	.zero	4
.LC50:
	ASCII(.string	"leave VP6_IntraFrmHeader\n" )
	.zero	6
.LC52:
	ASCII(.string	"VP6_InterFrmHeader VersionNo fault,old:%d,new:%d\n" )
	.zero	6
.LC54:
	ASCII(.string	"[ERR]VP6_GetPictureHeader invalid param!\n" )
	.zero	6
.LC56:
	ASCII(.string	"VP6_GetPictureHeader enter!\n" )
	.zero	3
.LC59:
	ASCII(.string	"VP6_GetPictureHeader leave!\n" )
	.zero	3
.LC66:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC68:
	ASCII(.string	"VP6DEC_Init leave\n" )
	.zero	5
.LC70:
	ASCII(.string	"ERROR: No Img buffer is allocated\n" )
	.zero	5
.LC72:
	ASCII(.string	"----------------- vp6 Imode -> %d ------------------\n" )
	.zero	2
.LC74:
	ASCII(.string	"-----I_MODE, but FrameType is %d-----\n" )
	.zero	1
.LC76:
	ASCII(.string	"P-frm" )
	.zero	2
.LC78:
	ASCII(.string	"-----cur framtype is %s, but refnum=%d-----\n" )
	.zero	3
.LC80:
	ASCII(.string	"error: DecMode illegal\n" )
.LC83:
	ASCII(.string	"%s %d NULL == pFwdImg!!\n" )
	.zero	7
.LC85:
	ASCII(.string	"dec P frame, fwd ref err(%d) > ref_thr(%d)\n" )
	.zero	4
.LC88:
	ASCII(.string	"VP6_Set_DecParam but logic fs is null!\n" )
.LC90:
	ASCII(.string	"Decord FS is NULL!\n" )
	.zero	4
.LC97:
	ASCII(.string	"Error! Truncated packet\n" )
	.zero	7
.LC99:
	ASCII(.string	"[ERR]VP6_GetPictureHeader Error!\n" )
	.zero	6
.LC101:
	ASCII(.string	"[ERR] VP6_DecodeDecide Error!\n" )
	.zero	1
.LC104:
	ASCII(.string	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	4
.LC106:
	ASCII(.string	"pic width/height to large,MbWidth = %d, MbHeight = %d" )
	.zero	2
.LC108:
	ASCII(.string	"VP6_ArrangeVHBMem err\n" )
	.zero	1
.LC110:
	ASCII(.string	"VP6_DecodeDecide err\n" )
	.zero	2
.LC112:
	ASCII(.string	"VP6DEC_GetImageBuffer err\n" )
	.zero	5
.LC115:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.zero	2
.LC117:
	ASCII(.string	"VP6_PrePare_decode Error!\n" )
	.zero	5
.LC120:
	ASCII(.string	"leave VP6DEC_Decode\n" )
	.zero	3
.LC123:
	ASCII(.string	"ErrRatio = %d\n" )
	.zero	1
.LC125:
	ASCII(.string	"pCurImg is null\n" )
	.zero	7
.LC127:
	ASCII(.string	"err_level(%d) over ref_thr(%d)\n" )
.LC129:
	ASCII(.string	"line: %d pToQueImg is null!\n" )
	.zero	3
.LC131:
	ASCII(.string	"insert img to Voqueue failed!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
