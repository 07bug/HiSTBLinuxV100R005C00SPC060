#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_h264.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	H264HAL_SetSliceMsgRefPicFrame.isra.2, %function
H264HAL_SetSliceMsgRefPicFrame.isra.2:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x8, x0
	mov	x0, x30
	mov	w27, w4
	mov	x20, x2
	stp	x8, x1, [x29, 104]
	str	w3, [x29, 124]
	bl	_mcount
	uxtw	x0, w27
	ldr	x7, [x29, 112]
	add	w5, w27, 3
	lsl	w27, w27, 3
	add	x6, x7, x0, lsl 2
	lsl	w23, w5, 2
	add	w27, w27, 20
	ldr	w1, [x6, 52]
	cbz	w1, .L1
	lsl	x28, x0, 10
	mov	w25, 0
	mov	w26, 0
	add	x28, x28, x0, lsl 7
	ldr	x21, .LC0
	mov	w19, 0
	mov	w22, 8
	ldr	x8, [x29, 104]
	b	.L7
	.p2align 3
.L5:
	cmp	w24, 3
	beq	.L15
.L6:
	ldr	w0, [x6, 52]
	cmp	w19, w0
	bcs	.L16
.L7:
	uxtw	x0, w19
	ldr	w4, [x8]
	lsl	x1, x0, 5
	and	w24, w19, 3
	add	x0, x1, x0, lsl 2
	and	w3, w19, 7
	add	x0, x0, x28
	lsl	w11, w3, 2
	add	x0, x7, x0
	add	w12, w24, w24, lsl 2
	add	w19, w19, 1
	ldrb	w1, [x0, 1626]
	ldrb	w13, [x0, 1627]
	ldr	w2, [x0, 1644]
	add	x4, x4, x1, lsl 1
	cmp	w13, 1
	csel	w1, w22, wzr, eq
	ubfiz	w2, w2, 1, 4
	cmp	w3, 7
	lsl	w2, w2, w12
	ldr	w0, [x21, x4, lsl 2]
	orr	w25, w25, w2
	and	w0, w0, 3
	orr	w0, w0, w1
	lsl	w0, w0, w11
	orr	w26, w26, w0
	bne	.L5
	str	w26, [x20, w23, uxtw 2]
	mov	w2, w23
	ldr	w0, [x29, 124]
	mov	w26, 0
	ldr	w4, [x20, w23, uxtw 2]
	ldr	x1, .LC2
	add	w3, w0, w23, lsl 2
	mov	w0, 4
	str	x6, [x29, 112]
	stp	x7, x8, [x29, 96]
	bl	dprint_vfmw
	add	w23, w23, 1
	cmp	w24, 3
	ldr	x6, [x29, 112]
	ldp	x7, x8, [x29, 96]
	bne	.L6
	.p2align 2
.L15:
	str	w25, [x20, w27, uxtw 2]
	mov	w2, w27
	ldr	w0, [x29, 124]
	mov	w25, 0
	ldr	w4, [x20, w27, uxtw 2]
	ldr	x1, .LC2
	add	w3, w0, w27, lsl 2
	mov	w0, 4
	str	x6, [x29, 112]
	stp	x7, x8, [x29, 96]
	bl	dprint_vfmw
	add	w27, w27, 1
	ldr	x6, [x29, 112]
	ldp	x7, x8, [x29, 96]
	ldr	w0, [x6, 52]
	cmp	w19, w0
	bcc	.L7
	.p2align 2
.L16:
	and	w0, w0, 7
	cbnz	w0, .L17
.L1:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L17:
	str	w26, [x20, w23, uxtw 2]
	mov	w2, w23
	ldr	w21, [x29, 124]
	mov	w0, 4
	ldr	x19, .LC2
	ldr	w4, [x20, w23, uxtw 2]
	add	w3, w21, w23, lsl 2
	mov	x1, x19
	bl	dprint_vfmw
	str	w25, [x20, w27, uxtw 2]
	add	w3, w21, w27, lsl 2
	mov	w2, w27
	ldr	w4, [x20, w27, uxtw 2]
	mov	x1, x19
	mov	w0, 4
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	H264HAL_SetSliceMsgRefPicFrame.isra.2, .-H264HAL_SetSliceMsgRefPicFrame.isra.2
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	H264HAL_SetSliceMsgRefPicField.isra.3, %function
H264HAL_SetSliceMsgRefPicField.isra.3:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w4
	mov	x21, x1
	mov	x19, x2
	str	w3, [x29, 108]
	bl	_mcount
	uxtw	x0, w22
	add	w10, w22, 3
	lsl	w7, w22, 3
	lsl	w25, w10, 2
	add	x23, x21, x0, lsl 2
	add	w27, w7, 20
	ldr	w1, [x23, 52]
	cbz	w1, .L18
	lsl	x5, x0, 10
	mov	w26, 0
	mov	w9, 0
	ldr	x22, .LC3
	add	x24, x5, x0, lsl 7
	mov	w28, 0
	b	.L38
	.p2align 3
.L21:
	cmp	w2, 2
	beq	.L29
	and	w12, w28, 3
	and	w0, w28, 7
.L28:
	cmp	w0, 7
	beq	.L54
.L36:
	cmp	w12, 3
	beq	.L55
.L37:
	ldr	w0, [x23, 52]
	add	w28, w28, 1
	cmp	w28, w0
	bcs	.L56
.L38:
	uxtw	x1, w28
	lsl	x0, x1, 5
	add	x0, x0, x1, lsl 2
	add	x0, x0, x24
	add	x0, x21, x0
	ldrb	w2, [x0, 1624]
	cmp	w2, 1
	bne	.L21
	ldrb	w2, [x0, 1625]
	cmp	w2, 3
	beq	.L22
	ldrb	w4, [x0, 1629]
	mov	w2, 8
	ldrb	w3, [x0, 1628]
	mov	w0, 4
	cmp	w4, 1
	csel	w2, wzr, w2, ne
	cmp	w3, 1
	csel	w0, wzr, w0, ne
	sbfiz	x3, x3, 1, 32
	orr	w0, w2, w0
	ldr	w2, [x20]
	add	x3, x3, x2
	ldr	x2, .LC3
	add	x2, x2, 32
	ldr	w2, [x2, x3, lsl 2]
	and	w2, w2, 3
.L52:
	orr	w2, w2, w0
	and	w0, w28, 7
	lsl	w3, w0, 2
	and	w12, w28, 3
	lsl	w2, w2, w3
	cmp	w0, 7
	orr	w9, w9, w2
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 2
	add	w2, w12, w12, lsl 2
	add	x1, x1, x24
	add	x1, x21, x1
	ldr	w1, [x1, 1644]
	ubfiz	w1, w1, 1, 4
	lsl	w1, w1, w2
	orr	w26, w26, w1
	bne	.L36
.L54:
	str	w9, [x19, w25, uxtw 2]
	mov	w2, w25
	ldr	w0, [x29, 108]
	ldr	w4, [x19, w25, uxtw 2]
	ldr	x1, .LC4
	add	w3, w0, w25, lsl 2
	mov	w0, 4
	str	w12, [x29, 104]
	add	w25, w25, 1
	bl	dprint_vfmw
	ldr	w12, [x29, 104]
	mov	w9, 0
	cmp	w12, 3
	bne	.L37
	.p2align 2
.L55:
	str	w26, [x19, w27, uxtw 2]
	mov	w2, w27
	ldr	w0, [x29, 108]
	add	w28, w28, 1
	ldr	w4, [x19, w27, uxtw 2]
	mov	w26, 0
	ldr	x1, .LC4
	add	w3, w0, w27, lsl 2
	mov	w0, 4
	str	w9, [x29, 104]
	add	w27, w27, 1
	bl	dprint_vfmw
	ldr	w0, [x23, 52]
	ldr	w9, [x29, 104]
	cmp	w28, w0
	bcc	.L38
	.p2align 2
.L56:
	and	w0, w0, 7
	cbnz	w0, .L57
.L18:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L29:
	ldrb	w2, [x0, 1625]
	cmp	w2, 3
	beq	.L30
	ldrb	w4, [x0, 1630]
	ldrb	w0, [x0, 1631]
	sbfiz	x2, x4, 1, 32
	cmp	w0, 1
	ldr	w0, [x20]
	add	x0, x2, x0
	ldr	x2, .LC3
	add	x2, x2, 32
	ldr	w2, [x2, x0, lsl 2]
.L53:
	mov	w0, 8
	and	w2, w2, 3
	csel	w3, wzr, w0, ne
	cmp	w4, 1
	mov	w0, 4
	and	w12, w28, 3
	csel	w0, wzr, w0, ne
	orr	w0, w3, w0
	orr	w2, w2, w0
	and	w0, w28, 7
	lsl	w3, w0, 2
	lsl	w2, w2, w3
	orr	w9, w9, w2
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 2
	add	w2, w12, w12, lsl 2
	add	x1, x1, x24
	add	x1, x21, x1
	ldr	w1, [x1, 1644]
	ubfiz	w1, w1, 1, 4
	orr	w1, w1, 1
	lsl	w1, w1, w2
	orr	w26, w26, w1
	b	.L28
	.p2align 3
.L22:
	ldrb	w2, [x0, 1626]
	ldr	w3, [x20]
	ldrb	w4, [x0, 1628]
	add	x2, x3, x2, lsl 1
	ldrb	w3, [x0, 1629]
	ldr	x0, .LC3
	cmp	w3, 1
	add	x0, x0, 32
	ldr	w2, [x0, x2, lsl 2]
	mov	w0, 8
	csel	w3, wzr, w0, ne
	cmp	w4, 1
	mov	w0, 4
	and	w2, w2, 3
	csel	w0, wzr, w0, ne
	orr	w0, w3, w0
	b	.L52
	.p2align 3
.L30:
	ldrb	w2, [x0, 1626]
	ldr	w3, [x20]
	ldrb	w4, [x0, 1630]
	add	x2, x3, x2, lsl 1
	ldrb	w3, [x0, 1631]
	add	x0, x22, 32
	cmp	w3, 1
	ldr	w2, [x0, x2, lsl 2]
	b	.L53
	.p2align 3
.L57:
	str	w9, [x19, w25, uxtw 2]
	mov	w2, w25
	ldr	w21, [x29, 108]
	mov	w0, 4
	ldr	x20, .LC4
	ldr	w4, [x19, w25, uxtw 2]
	add	w3, w21, w25, lsl 2
	mov	x1, x20
	bl	dprint_vfmw
	str	w26, [x19, w27, uxtw 2]
	add	w3, w21, w27, lsl 2
	mov	w2, w27
	ldr	w4, [x19, w27, uxtw 2]
	mov	x1, x20
	mov	w0, 4
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	H264HAL_SetSliceMsgRefPicField.isra.3, .-H264HAL_SetSliceMsgRefPicField.isra.3
	.align	3
.LC3:
	.xword	.LANCHOR0
	.align	3
.LC4:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	H264HAL_V4R3C1_SetSliceMsg.isra.7, %function
H264HAL_V4R3C1_SetSliceMsg.isra.7:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w2
	mov	x20, x1
	stp	w4, w3, [x29, 108]
	bl	_mcount
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x26, x0
	cbz	x0, .L119
	ldr	x24, .LC16
	add	x6, x20, 8
	add	x28, x0, 4
	mov	x27, x0
	add	w23, w21, 4
	add	x25, x0, 8
	mov	w19, 0
.L63:
	ldr	w4, [x6]
	add	w11, w19, 1
	str	w11, [x29, 136]
	mov	w2, w11
	ldr	x1, .LC14
	mov	w0, 4
	sub	w3, w23, #4
	cbz	w4, .L61
	ldr	w10, [x22, 736]
	ldr	w4, [x6, 8]
	and	w13, w10, -16
	ldr	w10, [x6, 16]
	str	w13, [x29, 116]
	mov	w5, w10
	str	x6, [x29, 120]
	add	w12, w4, w10, lsl 3
	and	w12, w12, 127
	mov	w3, w12
	stp	w10, w12, [x29, 128]
	bl	dprint_vfmw
	ldp	w12, w11, [x29, 132]
	str	w12, [x28]
	mov	w3, w23
	mov	w2, w11
	mov	x1, x24
	ldr	w4, [x28]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	x6, [x29, 120]
	add	w3, w23, 4
	add	w2, w19, 2
	mov	x1, x24
	str	x6, [x29, 136]
	ldr	w0, [x6]
	str	w0, [x25]
	mov	w0, 4
	ldr	w4, [x25]
	bl	dprint_vfmw
	ldr	w10, [x29, 128]
	sub	w3, w23, #4
	ldr	w13, [x29, 116]
	mov	w2, w19
	and	w10, w10, -16
	mov	x1, x24
	sub	w10, w10, w13
	str	w10, [x27]
	mov	w0, 4
	ldr	w4, [x27]
	bl	dprint_vfmw
	ldr	x6, [x29, 136]
.L62:
	add	w19, w19, 3
	add	x6, x6, 4
	cmp	w19, 6
	add	x28, x28, 12
	add	x27, x27, 12
	add	w23, w23, 12
	add	x25, x25, 12
	bne	.L63
	ldr	w1, [x20, 48]
	add	w2, w21, 24
	ldp	w3, w0, [x20, 32]
	and	w1, w1, 1048575
	orr	w1, w1, w3, lsl 26
	ubfiz	w0, w0, 24, 2
	orr	w0, w1, w0
	str	w0, [x26, 24]
	ldr	x1, .LC18
	mov	w0, 4
	ldr	w3, [x26, 24]
	bl	dprint_vfmw
	ldr	x0, .LC19
	ldrb	w4, [x20, 3]
	ldrb	w0, [x0]
	cbnz	w0, .L65
	cbz	w4, .L120
.L65:
	ldp	w2, w3, [x20, 52]
	ldp	w0, w1, [x20, 40]
	ldr	x23, .LC10
	lsl	w2, w2, 2
	ldrb	w5, [x20]
	ubfiz	w1, w1, 16, 5
	add	x19, x23, 96
	ubfiz	w0, w0, 21, 5
	orr	w0, w0, w1
	orr	w1, w2, w3, lsl 8
	orr	w2, w0, w1
	ldrb	w1, [x20, 2]
	ldr	w0, [x19, w5, sxtw 2]
	orr	w1, w0, w1, lsl 15
	orr	w0, w2, w1
	ldr	x1, .LC21
	orr	w0, w0, w4, lsl 14
	str	w0, [x26, 28]
	add	w2, w21, 28
	mov	w0, 4
	ldr	w3, [x26, 28]
	bl	dprint_vfmw
	ldrb	w0, [x20]
	ldr	w0, [x19, w0, sxtw 2]
	cmp	w0, 2
	beq	.L121
	mov	w3, 0
	mov	w0, 0
.L66:
	str	w0, [x26, 32]
	add	w2, w21, 32
	ldr	x1, .LC25
	mov	w0, 4
	str	w3, [x26, 36]
	ldr	w3, [x26, 32]
	bl	dprint_vfmw
	ldr	x1, .LC27
	add	w2, w21, 36
	ldr	w3, [x26, 36]
	mov	w0, 4
	bl	dprint_vfmw
	ldrb	w2, [x20, 4]
	ldp	w0, w1, [x20, 60]
	ubfiz	w0, w0, 5, 5
	and	w1, w1, 31
	orr	w0, w0, w2, lsl 16
	add	w2, w21, 40
	orr	w0, w0, w1
	str	w0, [x26, 40]
	ldr	x1, .LC29
	mov	w0, 4
	ldr	w3, [x26, 40]
	bl	dprint_vfmw
	ldp	w0, w1, [x20, 68]
	ldr	w2, [x20, 76]
	ubfiz	w1, w1, 8, 4
	ubfiz	w0, w0, 16, 4
	orr	w0, w0, w1
	ldr	x1, .LC31
	orr	w0, w0, w2
	str	w0, [x26, 44]
	add	w2, w21, 44
	mov	w0, 4
	ldr	w3, [x26, 44]
	bl	dprint_vfmw
	ldr	x0, [x20, 4056]
	cbz	x0, .L71
	ldr	w25, [x29, 108]
.L72:
	ldr	w0, [x29, 112]
	add	x19, x23, 96
	str	w25, [x26, 176]
	and	w27, w0, -16
	str	w27, [x26, 252]
	ldrb	w0, [x20]
	ldr	w0, [x19, w0, sxtw 2]
	cbnz	w0, .L75
.L85:
	mov	w0, 0
.L60:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L61:
	str	wzr, [x27]
	mov	w2, w19
	mov	x1, x24
	mov	w0, 4
	ldr	w4, [x27]
	str	x6, [x29, 136]
	bl	dprint_vfmw
	str	wzr, [x28]
	mov	w3, w23
	add	w2, w19, 1
	ldr	w4, [x28]
	mov	x1, x24
	mov	w0, 4
	bl	dprint_vfmw
	str	wzr, [x25]
	add	w3, w23, 4
	add	w2, w19, 2
	ldr	w4, [x25]
	mov	x1, x24
	mov	w0, 4
	bl	dprint_vfmw
	ldr	x6, [x29, 136]
	b	.L62
	.p2align 3
.L75:
	ldrb	w0, [x22]
	add	x24, x22, 48
	mov	w4, 0
	mov	w3, w21
	mov	x2, x26
	mov	x1, x20
	cbz	w0, .L122
	mov	x0, x24
	bl	H264HAL_SetSliceMsgRefPicField.isra.3
	ldrb	w0, [x20]
	ldr	w0, [x19, w0, sxtw 2]
	cmp	w0, 2
	beq	.L123
.L78:
	ldr	w2, [x20, 3928]
	add	x25, x20, 3932
	ldr	x24, .LC32
	mov	w19, 0
	mov	w27, 36
	and	w2, w2, 31
	.p2align 2
.L80:
	add	w19, w19, 1
	and	w1, w19, 3
	cmp	w19, 32
	add	w3, w1, w1, lsl 2
	beq	.L124
.L82:
	ldr	w0, [x25]
	cmp	w1, 3
	add	x25, x25, 4
	and	w0, w0, 31
	lsl	w0, w0, w3
	orr	w2, w2, w0
	bne	.L80
	str	w2, [x26, w27, uxtw 2]
	add	w3, w21, w27, lsl 2
	mov	w2, w27
	mov	x1, x24
	ldr	w4, [x26, w27, uxtw 2]
	mov	w0, 4
	add	w19, w19, 1
	add	w27, w27, 1
	bl	dprint_vfmw
	and	w1, w19, 3
	cmp	w19, 32
	mov	w2, 0
	add	w3, w1, w1, lsl 2
	bne	.L82
	.p2align 2
.L124:
	ldr	w0, [x22, 300]
	cbz	w0, .L83
	add	x0, x23, 96
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 1
	beq	.L84
.L83:
	ldr	w0, [x22, 304]
	cmp	w0, 1
	bne	.L85
	add	x0, x23, 96
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L85
.L84:
	ldr	x1, .LC34
	mov	w0, 4
	ldr	w2, [x20, 44]
	add	x27, x26, 256
	add	x28, x26, 512
	add	w24, w21, 256
	add	x26, x26, 768
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x25, .LC32
	.p2align 2
.L86:
	add	x22, x20, x19, uxtw 2
	ldr	w0, [x20, 80]
	mov	w3, w24
	and	w1, w0, 7
	ldrb	w2, [x22, 856]
	ldr	w0, [x22, 88]
	ubfiz	w0, w0, 3, 9
	orr	w0, w0, w2, lsl 12
	add	w2, w19, 64
	orr	w0, w0, w1
	str	w0, [x27, w19, uxtw 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x27, w19, uxtw 2]
	bl	dprint_vfmw
	ldrb	w2, [x22, 984]
	add	w3, w24, 256
	ldr	w0, [x22, 216]
	ubfiz	w0, w0, 3, 9
	orr	w1, w0, w2, lsl 12
	ldr	w0, [x20, 84]
	add	w2, w19, 128
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x28, w19, uxtw 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x28, w19, uxtw 2]
	bl	dprint_vfmw
	ldrb	w1, [x22, 1112]
	add	w3, w24, 512
	ldr	w0, [x22, 344]
	add	w2, w19, 192
	add	w24, w24, 4
	and	w0, w0, 511
	orr	w0, w0, w1, lsl 9
	str	w0, [x26, w19, uxtw 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x26, w19, uxtw 2]
	add	w19, w19, 1
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	cmp	w19, w0
	bls	.L86
	ldr	x1, .LC36
	mov	w0, 4
	ldr	w2, [x20, 80]
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x24, .LC38
	.p2align 2
.L87:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 88]
	bl	dprint_vfmw
	ldr	x1, .LC40
	mov	w0, 4
	ldr	w2, [x22, 856]
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	cmp	w19, w0
	bls	.L87
	add	x0, x23, 96
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L88
.L91:
	ldr	x1, .LC42
	mov	w0, 4
	ldr	w2, [x20, 84]
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x24, .LC48
	.p2align 2
.L89:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 216]
	bl	dprint_vfmw
	ldr	x1, .LC50
	mov	w0, 4
	ldr	w2, [x22, 984]
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	cmp	w19, w0
	bls	.L89
	add	x0, x23, 96
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L92
.L95:
	ldr	x24, .LC56
	mov	w19, 0
	.p2align 2
.L93:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 344]
	bl	dprint_vfmw
	ldr	x1, .LC58
	mov	w0, 4
	ldr	w2, [x22, 1112]
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	cmp	w19, w0
	bls	.L93
	add	x0, x23, 96
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L85
	ldr	x24, .LC60
	mov	w19, 0
	.p2align 2
.L96:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 728]
	bl	dprint_vfmw
	ldr	w2, [x22, 1496]
	mov	w0, 4
	ldr	x1, .LC62
	bl	dprint_vfmw
	ldr	w2, [x20, 40]
	cmp	w19, w2
	bls	.L96
	add	x23, x23, 96
	ldrb	w0, [x20]
	ldr	w0, [x23, w0, sxtw 2]
	cmp	w0, 2
	bne	.L85
	ldr	x1, .LC64
	mov	w0, 4
	add	w21, w21, 384
	mov	w22, 0
	bl	dprint_vfmw
	.p2align 2
.L97:
	uxtw	x19, w22
	mov	w3, w21
	add	x23, x19, 32
	add	w2, w22, 96
	add	x19, x20, x19, lsl 2
	ldrb	w0, [x19, 1240]
	ldr	w1, [x19, 472]
	ubfiz	w1, w1, 3, 9
	orr	w1, w1, w0, lsl 12
	ldr	w0, [x20, 80]
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x27, x23, lsl 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x27, x23, lsl 2]
	bl	dprint_vfmw
	ldrb	w0, [x19, 1368]
	add	w3, w21, 256
	ldr	w1, [x19, 600]
	add	w2, w22, 160
	ubfiz	w1, w1, 3, 9
	orr	w1, w1, w0, lsl 12
	ldr	w0, [x20, 84]
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x28, x23, lsl 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x28, x23, lsl 2]
	bl	dprint_vfmw
	ldrb	w0, [x19, 1496]
	add	w3, w21, 512
	ldr	w1, [x19, 728]
	add	w2, w22, 224
	add	w22, w22, 1
	add	w21, w21, 4
	and	w1, w1, 511
	orr	w0, w1, w0, lsl 9
	str	w0, [x26, x23, lsl 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x26, x23, lsl 2]
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	cmp	w22, w0
	bls	.L97
	b	.L85
	.p2align 3
.L120:
	ldp	w1, w0, [x22, 40]
	mul	w0, w0, w1
	cmp	w0, 1620
	bls	.L65
	mov	w0, -1
	b	.L60
	.p2align 3
.L122:
	mov	x0, x24
	bl	H264HAL_SetSliceMsgRefPicFrame.isra.2
	ldrb	w0, [x20]
	ldr	w0, [x19, w0, sxtw 2]
	cmp	w0, 2
	bne	.L78
	mov	w4, 1
	mov	w3, w21
	mov	x2, x26
	mov	x1, x20
	mov	x0, x24
	bl	H264HAL_SetSliceMsgRefPicFrame.isra.2
	b	.L78
	.p2align 3
.L121:
	ldr	x1, .LC23
	mov	w0, 4
	ldr	w2, [x20, 2788]
	bl	dprint_vfmw
	ldrb	w0, [x22]
	cbnz	w0, .L67
	ldrb	w0, [x20, 2778]
	cmp	w0, 3
	ldr	w0, [x20, 2788]
	beq	.L125
.L117:
	add	x0, x22, x0, lsl 2
	mov	w3, 0
	ldr	w0, [x0, 584]
	and	w0, w0, -16
	b	.L66
	.p2align 3
.L71:
	ldr	w0, [x22, 740]
	ldrb	w1, [x20, 1]
	cmp	w0, 262144
	ble	.L74
	add	w25, w1, 1
	mov	w0, 262143
	sdiv	w25, w0, w25
	b	.L72
.L67:
	ldr	w0, [x20, 2776]
	and	w0, w0, 16776960
	cmp	w0, 768
	beq	.L118
	ldrb	w0, [x20, 2776]
	cmp	w0, 1
	beq	.L118
	ldr	w1, [x20, 2788]
	mov	w3, 0
	ldr	w0, [x22, 716]
	add	x1, x22, x1, lsl 2
	ldr	w1, [x1, 584]
	add	w0, w1, w0
	and	w0, w0, -16
	b	.L66
.L74:
	sub	w0, w0, #1
	add	w25, w1, 1
	sdiv	w25, w0, w25
	b	.L72
.L123:
	mov	w4, 1
	mov	w3, w21
	mov	x2, x26
	mov	x1, x20
	mov	x0, x24
	bl	H264HAL_SetSliceMsgRefPicField.isra.3
	b	.L78
.L118:
	ldr	w0, [x20, 2788]
	b	.L117
.L125:
	add	x0, x22, x0, lsl 2
	ldr	w3, [x22, 716]
	ldr	w0, [x0, 584]
	add	w3, w0, w3
	and	w0, w0, -16
	and	w3, w3, -16
	b	.L66
.L92:
	ldr	x24, .LC52
	mov	w19, 0
	.p2align 2
.L94:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 600]
	bl	dprint_vfmw
	ldr	x1, .LC54
	mov	w0, 4
	ldr	w2, [x22, 1368]
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	cmp	w19, w0
	bls	.L94
	b	.L95
.L88:
	ldr	x24, .LC44
	mov	w19, 0
	.p2align 2
.L90:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 472]
	bl	dprint_vfmw
	ldr	x1, .LC46
	mov	w0, 4
	ldr	w2, [x22, 1240]
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	cmp	w19, w0
	bls	.L90
	b	.L91
.L119:
	ldr	x2, .LC10
	mov	w0, 0
	ldr	x3, .LC9
	ldr	x1, .LC12
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L60
	.size	H264HAL_V4R3C1_SetSliceMsg.isra.7, .-H264HAL_V4R3C1_SetSliceMsg.isra.7
	.align	3
.LC9:
	.xword	.LC8
	.align	3
.LC10:
	.xword	.LANCHOR0
	.align	3
.LC12:
	.xword	.LC11
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
.LC19:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC21:
	.xword	.LC20
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC31:
	.xword	.LC30
	.align	3
.LC32:
	.xword	.LC1
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC36:
	.xword	.LC35
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC46:
	.xword	.LC45
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC50:
	.xword	.LC49
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
.LC60:
	.xword	.LC59
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V4R3C1_InitHal
	.type	H264HAL_V4R3C1_InitHal, %function
H264HAL_V4R3C1_InitHal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 1104]
	bl	MEM_Phy2Vir
	cbz	x0, .L129
	ldr	x3, .LC70
	mov	x2, 5120
	ldr	x1, .LC71
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L128:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L129:
	ldr	x1, .LC67
	mov	w2, 58
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, .LC69
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L128
	.size	H264HAL_V4R3C1_InitHal, .-H264HAL_V4R3C1_InitHal
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC70:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC71:
	.xword	g_CabacMN
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V4R3C1_StartDec
	.type	H264HAL_V4R3C1_StartDec, %function
H264HAL_V4R3C1_StartDec:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w1
	mov	x20, x2
	bl	_mcount
	cmp	w19, wzr
	bgt	.L227
	cbz	x21, .L228
	ldr	w0, [x21, 44]
	cmp	w0, 512
	bhi	.L135
	ldr	w0, [x21, 36]
	cmp	w0, 512
	bhi	.L135
	ldr	x0, [x21, 944]
	cbz	x0, .L229
	cbz	w19, .L138
	cmp	w19, 1
	bne	.L230
	mov	w0, -104529920
.L139:
	sxtw	x22, w19
	ldr	x23, .LC84
	lsl	x1, x22, 6
	sub	x1, x1, x22
	lsl	x1, x1, 2
	sub	x24, x1, x22
	add	x24, x1, x24, lsl 2
	ldr	x1, [x23, x24]
	cbz	x1, .L231
.L140:
	ldr	x3, .LC160
	mov	w0, 3
	ldr	x1, .LC162
	ldr	w2, [x3]
	add	w2, w2, 1
	str	w2, [x3]
	bl	dprint_vfmw
	ldr	x1, .LC164
	cmp	x20, xzr
	ldr	x0, .LC163
	ldrb	w1, [x1]
	add	x0, x0, x22, lsl 6
	ccmp	w1, 1, 4, eq
	ldr	w0, [x0, 8]
	bne	.L232
	ldr	x2, .LC89
	ldr	x0, [x2, w0, sxtw 3]
	cbz	x0, .L189
	ldr	w25, [x0, 1312]
	uxtb	w0, w25
	and	w24, w0, 1
.L142:
	cmp	w1, 1
	beq	.L143
	strb	w0, [x20, 1]
.L143:
	ldr	w1, [x21, 740]
	mov	w0, 262143
	str	wzr, [x29, 124]
	cmp	w1, 262144
	bgt	.L144
	sub	w0, w1, #1
	and	w0, w0, 1048575
.L144:
	ldr	w1, [x29, 124]
	mov	x3, x20
	mov	w2, w19
	mov	w27, 1
	bfi	w1, w0, 0, 20
	str	w1, [x29, 124]
	ubfx	x0, x1, 24, 6
	ubfx	x1, x1, 16, 6
	orr	w0, w0, 64
	strb	w1, [x29, 126]
	orr	w0, w0, 1
	and	w0, w0, -3
	strb	w0, [x29, 127]
	mov	w0, 8
	ldr	w26, [x29, 124]
	str	w26, [x21, 960]
	mov	w1, w26
	bl	MFDE_ConfigReg
	ldr	x1, .LC91
	mov	w2, w26
	mov	w0, 3
	bl	dprint_vfmw
	strh	w27, [x29, 126]
	ldrb	w2, [x21, 16]
	mov	w1, 0
	mov	w0, 0
	ldrb	w3, [x21, 2]
	bfi	w1, w2, 4, 1
	bfi	w0, w24, 4, 1
	ldrb	w2, [x21, 4]
	and	w0, w0, -33
	bfi	w1, w3, 6, 1
	strb	wzr, [x29, 124]
	bfi	w0, w2, 6, 1
	orr	w1, w1, -128
	and	w0, w0, 127
	strb	w1, [x29, 125]
	strb	w0, [x29, 127]
	mov	x3, x20
	mov	w2, w19
	mov	w0, 12
	ldr	w24, [x29, 124]
	str	w24, [x21, 964]
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC93
	mov	w2, w24
	mov	w0, 3
	lsl	x24, x22, 6
	sub	x24, x24, x22
	bl	dprint_vfmw
	lsl	x24, x24, 2
	sub	x0, x24, x22
	mov	x3, x20
	mov	w2, w19
	add	x24, x24, x0, lsl 2
	mov	w0, 16
	add	x24, x23, x24
	ldr	w26, [x24, 72]
	and	w26, w26, -16
	str	w26, [x21, 968]
	mov	w1, w26
	bl	MFDE_ConfigReg
	ldr	x1, .LC95
	mov	w2, w26
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w24, [x24, 56]
	mov	x3, x20
	mov	w2, w19
	and	w24, w24, -16
	mov	w0, 20
	mov	w1, w24
	str	w24, [x21, 972]
	bl	MFDE_ConfigReg
	ldr	x1, .LC97
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w24, [x21, 736]
	mov	x3, x20
	mov	w2, w19
	and	w24, w24, -16
	mov	w0, 24
	mov	w1, w24
	str	w24, [x21, 976]
	str	w24, [x29, 124]
	bl	MFDE_ConfigReg
	ldr	x1, .LC99
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w0, [x21, 44]
	mov	w1, 0
	cmp	w0, 256
	bhi	.L145
	cmp	w0, 119
	mov	w1, w27
	bls	.L145
	ldr	w0, [x21, 1184]
	cmp	w0, wzr
	cset	w1, eq
.L145:
	mov	x3, x20
	mov	w2, w19
	mov	w0, 4
	mov	w24, 3075
	movk	w24, 0x30, lsl 16
	bl	SCD_ConfigReg
	str	w24, [x29, 124]
	mov	x3, x20
	mov	w2, w19
	mov	w1, w24
	mov	w0, 60
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w19
	mov	w1, w24
	mov	w0, 64
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w19
	mov	w1, w24
	mov	w0, 68
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w19
	mov	w1, w24
	mov	w0, 72
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w19
	mov	w1, w24
	mov	w0, 76
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w19
	mov	w1, w24
	mov	w0, 80
	bl	MFDE_ConfigReg
	mov	x3, x20
	mov	w2, w19
	mov	w1, w24
	mov	w0, 84
	bl	MFDE_ConfigReg
	cmp	w25, 1
	beq	.L233
.L146:
	ldr	w1, [x21, 308]
	mov	x3, x20
	mov	w0, 96
	mov	w2, w19
	add	x1, x21, x1, lsl 2
	ldr	w24, [x1, 324]
	and	w24, w24, -16
	str	w24, [x21, 1012]
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC106
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w24, [x21, 720]
	mov	x3, x20
	mov	w0, 100
	mov	w1, w24
	mov	w2, w19
	str	w24, [x21, 1016]
	bl	MFDE_ConfigReg
	ldr	x1, .LC108
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w24, [x21, 320]
	mov	x3, x20
	mov	w0, 104
	mov	w1, w24
	mov	w2, w19
	str	w24, [x21, 1020]
	bl	MFDE_ConfigReg
	ldr	x1, .LC110
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w24, [x21, 732]
	mov	x3, x20
	mov	w0, 108
	mov	w1, w24
	mov	w2, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC112
	mov	w2, w24
	mov	w0, 3
	lsl	x24, x22, 6
	sub	x24, x24, x22
	bl	dprint_vfmw
	lsl	x24, x24, 2
	sub	x1, x24, x22
	mov	x3, x20
	mov	w0, 128
	mov	w2, w19
	add	x24, x24, x1, lsl 2
	add	x24, x23, x24
	ldr	w25, [x24, 1180]
	and	w25, w25, -16
	str	w25, [x21, 1036]
	mov	w1, w25
	bl	MFDE_ConfigReg
	ldr	x1, .LC114
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	str	wzr, [x29, 124]
	ldr	w0, [x24, 1184]
	mov	x3, x20
	strh	w0, [x29, 124]
	mov	w2, w19
	mov	w0, 132
	mov	w24, 0
	ldr	w25, [x29, 124]
	str	w25, [x21, 1040]
	mov	w1, w25
	bl	MFDE_ConfigReg
	ldr	x1, .LC116
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	add	x2, x21, 1056
	mov	w1, 0
	.p2align 2
.L147:
	ldr	w0, [x2], 4
	and	w0, w0, 3
	lsl	w0, w0, w1
	add	w1, w1, 2
	cmp	w1, 32
	orr	w24, w0, w24
	bne	.L147
	mov	x3, x20
	mov	w1, w24
	mov	w0, 148
	mov	w2, w19
	str	w24, [x29, 124]
	bl	MFDE_ConfigReg
	ldr	x1, .LC118
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	ldrb	w0, [x21]
	ldr	x1, .LC72
	ldr	w2, [x21, 48]
	add	x1, x1, 168
	add	x0, x2, x0, lsl 1
	ldr	w0, [x1, x0, lsl 2]
	cbz	w0, .L194
	mov	w1, 0
	mov	w25, 0
.L148:
	mov	x3, x20
	mov	w2, w19
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC120
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x20
	mov	w2, w19
	mov	w1, -1
	mov	w0, 32
	bl	MFDE_ConfigReg
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x1, x0, 2
	sub	x0, x1, x22
	add	x0, x1, x0, lsl 2
	add	x0, x23, x0
	ldp	w1, w20, [x0, 72]
	str	w1, [x29, 100]
	mov	w0, w1
	add	w1, w1, 112
	str	w1, [x29, 104]
	bl	MEM_Phy2Vir
	mov	x19, x0
	cbz	x0, .L234
	ldrb	w2, [x21]
	mov	w1, -2147483648
	ldr	w3, [x21, 48]
	ldr	w0, [x21, 32]
	add	x2, x3, x2, lsl 1
	ldr	x3, .LC72
	cmp	w0, wzr
	ldr	w4, [x21, 60]
	add	x3, x3, 168
	csel	w0, w0, w1, eq
	ldr	w24, [x29, 100]
	ldr	w3, [x3, x2, lsl 2]
	ldp	w1, w2, [x21, 52]
	lsl	w2, w2, 27
	orr	w1, w2, w1, lsl 28
	ldr	w2, [x21, 36]
	sub	w2, w2, #1
	lsl	w2, w2, 16
	orr	w2, w2, w3, lsl 14
	ldr	w3, [x21, 44]
	sub	w3, w3, #1
	orr	w3, w3, w4, lsl 26
	orr	w1, w3, w1
	orr	w2, w2, w1
	ldrb	w1, [x21, 1]
	cmp	w1, 1
	mov	w1, 33554432
	csel	w1, wzr, w1, ne
	orr	w0, w0, w1
	ldr	x1, .LC124
	orr	w0, w2, w0
	str	w0, [x19]
	mov	w2, w24
	mov	w0, 4
	ldr	w3, [x19]
	bl	dprint_vfmw
	ldr	w0, [x21, 312]
	add	w2, w24, 4
	ldr	x1, .LC126
	and	w0, w0, -16
	str	w0, [x19, 4]
	mov	w0, 4
	ldr	w3, [x19, 4]
	bl	dprint_vfmw
	ldr	w0, [x21, 64]
	add	w2, w24, 8
	str	w0, [x19, 8]
	mov	w0, 4
	ldr	x1, .LC128
	ldr	w3, [x19, 8]
	bl	dprint_vfmw
	ldr	w0, [x21, 48]
	cbz	w0, .L153
	ldr	w0, [x21, 68]
	add	w2, w24, 12
	str	w0, [x19, 12]
	ldr	x1, .LC130
	ldr	w0, [x21, 72]
	ldr	w3, [x19, 12]
	str	w0, [x19, 16]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	x1, .LC132
	add	w2, w24, 16
	ldr	w3, [x19, 16]
	mov	w0, 4
	bl	dprint_vfmw
.L154:
	lsl	x26, x22, 6
	ldr	w24, [x29, 100]
	sub	x26, x26, x22
	ldr	x1, .LC134
	lsl	x26, x26, 2
	add	w2, w24, 20
	sub	x0, x26, x22
	add	x26, x26, x0, lsl 2
	add	x26, x23, x26
	ldr	w0, [x26, 1160]
	and	w0, w0, -16
	str	w0, [x19, 20]
	mov	w0, 4
	ldr	w3, [x19, 20]
	bl	dprint_vfmw
	ldr	w0, [x26, 1164]
	add	w2, w24, 24
	ldr	x1, .LC136
	and	w0, w0, -16
	str	w0, [x19, 24]
	mov	w0, 4
	ldr	w3, [x19, 24]
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 2
	beq	.L155
	ldr	w0, [x21, 316]
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 584]
	and	w0, w0, -16
.L156:
	str	w0, [x19, 28]
	mov	w0, 4
	ldr	w24, [x29, 100]
	and	w20, w20, -16
	ldr	x1, .LC138
	ldr	w3, [x19, 28]
	add	w2, w24, 28
	bl	dprint_vfmw
	lsl	x0, x22, 6
	add	w2, w24, 32
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x1, .LC140
	add	x0, x23, x0
	ldr	w0, [x0, 1168]
	and	w0, w0, -16
	str	w0, [x19, 32]
	mov	w0, 4
	ldr	w3, [x19, 32]
	bl	dprint_vfmw
	str	w20, [x19, 36]
	ldr	x1, .LC142
	add	w2, w24, 36
	ldr	w3, [x19, 36]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w26, [x21, 936]
	ldr	x20, .LC144
	cbz	w26, .L157
	ldr	w0, [x29, 100]
	mov	w28, 0
	add	w24, w0, 40
	.p2align 2
.L158:
	uxtw	x0, w28
	mov	w3, w24
	add	x6, x0, 10
	add	w2, w28, 10
	add	x4, x21, x0, lsl 2
	mov	x1, x20
	mov	w0, 4
	add	w28, w28, 1
	add	w24, w24, w0
	ldr	w4, [x4, 744]
	add	x4, x21, x4, lsl 2
	ldr	w4, [x4, 324]
	and	w4, w4, -16
	str	w4, [x19, x6, lsl 2]
	ldr	w4, [x19, x6, lsl 2]
	bl	dprint_vfmw
	ldr	w26, [x21, 936]
	cmp	w28, w26
	bcc	.L158
	cmp	w26, 15
	bhi	.L162
.L157:
	add	w2, w26, 10
	ldr	w0, [x29, 100]
	add	w28, w0, w2, lsl 2
	.p2align 2
.L161:
	ldr	w5, [x21, 744]
	uxtw	x4, w26
	add	x4, x4, 10
	mov	w3, w28
	mov	w0, 4
	mov	x1, x20
	add	x5, x21, x5, lsl 2
	add	w26, w26, 1
	add	w28, w28, w0
	ldr	w5, [x5, 324]
	and	w5, w5, -16
	str	w5, [x19, x4, lsl 2]
	ldr	w4, [x19, x4, lsl 2]
	bl	dprint_vfmw
	cmp	w26, 15
	add	w2, w26, 10
	bls	.L161
.L162:
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	w1, [x29, 100]
	add	x0, x23, x0
	add	w2, w1, 104
	ldr	x1, .LC146
	ldr	w0, [x0, 1104]
	and	w0, w0, -16
	str	w0, [x19, 104]
	mov	w0, 4
	ldr	w3, [x19, 104]
	bl	dprint_vfmw
	ldr	w28, [x21, 936]
	cbz	w28, .L235
	ldr	w0, [x29, 100]
	mov	w27, 27
	mov	w24, 0
	add	w0, w0, 108
	str	w0, [x29, 108]
	mov	w26, w0
	.p2align 2
.L164:
	add	x25, x21, x24, uxtw 2
	ubfiz	x4, x24, 1, 31
	add	x4, x4, 27
	mov	w3, w26
	lsl	x28, x4, 2
	mov	w2, w27
	ldr	w8, [x25, 808]
	mov	x1, x20
	str	w8, [x19, x4, lsl 2]
	mov	w0, 4
	add	w24, w24, 1
	ldr	w4, [x19, w27, uxtw 2]
	bl	dprint_vfmw
	add	x4, x28, 4
	add	w8, w27, 1
	ldr	w0, [x25, 872]
	add	w3, w26, 4
	mov	w2, w8
	mov	x1, x20
	str	w0, [x19, x4]
	mov	w0, 4
	add	w27, w27, 2
	add	w26, w26, 8
	ldr	w4, [x19, w8, uxtw 2]
	bl	dprint_vfmw
	ldr	w28, [x21, 936]
	cmp	w24, w28
	bcc	.L164
	cmp	w28, 15
	bhi	.L167
.L163:
	ldr	w0, [x29, 108]
	lsl	w27, w28, 1
	add	w24, w0, w28, lsl 3
	.p2align 2
.L166:
	uxtw	x4, w27
	add	w8, w27, 27
	add	x4, x4, 27
	mov	w3, w24
	lsl	x26, x4, 2
	mov	w2, w8
	mov	x1, x20
	mov	w0, 4
	str	wzr, [x19, x4, lsl 2]
	add	w28, w28, 1
	ldr	w4, [x19, w8, uxtw 2]
	bl	dprint_vfmw
	add	x7, x26, 4
	add	w4, w27, 28
	ldr	w0, [x29, 108]
	mov	w2, w4
	mov	x1, x20
	add	w27, w27, 2
	str	wzr, [x19, x7]
	sub	w3, w24, w0
	ldr	w0, [x29, 104]
	add	w24, w24, 8
	ldr	w4, [x19, w4, uxtw 2]
	add	w3, w3, w0
	mov	w0, 4
	bl	dprint_vfmw
	cmp	w28, 15
	bls	.L166
.L167:
	lsl	x0, x22, 6
	ldr	w1, [x29, 100]
	sub	x0, x0, x22
	add	x26, x19, 256
	lsl	x0, x0, 2
	add	w25, w1, 256
	sub	x1, x0, x22
	ldr	x28, .LC148
	add	x27, x21, 76
	mov	w20, 0
	add	x0, x0, x1, lsl 2
	add	x0, x23, x0
	ldr	w0, [x0, 1176]
	and	w0, w0, -16
	str	w0, [x19, 236]
	ldr	x19, .LC150
	.p2align 2
.L165:
	ldr	w0, [x27]
	mov	w2, w20
	str	w0, [x26]
	mov	x1, x28
	mov	w0, 4
	add	w20, w20, 1
	ldr	w3, [x27], 4
	bl	dprint_vfmw
	ldr	w3, [x26], 4
	mov	w2, w25
	mov	w0, 4
	mov	x1, x19
	add	w25, w25, w0
	bl	dprint_vfmw
	cmp	w20, 56
	bne	.L165
.L150:
	ldr	x27, [x21, 944]
	cbz	x27, .L236
	ldr	w19, [x27, 48]
	mov	w25, 0
	cbnz	w19, .L237
.L169:
	add	x26, x22, x22, lsl 2
	ldr	w1, [x21, 940]
	lsl	x26, x26, 4
	mov	w28, 0
	sub	x26, x26, x22
	mov	w20, 0
	lsl	x26, x26, 1
	.p2align 2
.L171:
	cmp	w20, w1
	bge	.L238
.L183:
	ldr	w3, [x27, 48]
	cmp	w20, wzr
	ccmp	w3, w28, 2, gt
	bls	.L171
	add	w4, w25, 5
	sub	x0, x26, x22
	add	w5, w20, w4
	lsl	x0, x0, 1
	add	w20, w20, 1
	mov	w28, w3
	add	x0, x0, x5, sxtw
	cmp	w20, w1
	add	x0, x23, x0, lsl 2
	ldr	w2, [x0, 56]
	bge	.L197
	ldr	x19, [x27, 4056]
	cbz	x19, .L174
	ldr	w0, [x19, 48]
	cmp	w3, w0
	bcs	.L178
	b	.L188
	.p2align 3
.L179:
	ldr	x19, [x19, 4056]
	cbz	x19, .L174
	ldr	w0, [x19, 48]
	cmp	w3, w0
	bcc	.L188
.L178:
	add	w20, w20, 1
	cmp	w20, w1
	blt	.L179
.L173:
	cbz	x19, .L132
.L188:
	mov	w0, 140
	cmp	w20, w1
	ccmp	w5, w0, 4, ne
	beq	.L239
	add	w4, w4, w20
	sub	x0, x26, x22
	lsl	x0, x0, 1
	ldr	w1, [x19, 48]
	add	x0, x0, x4, sxtw
	sub	w4, w1, #1
	mov	x1, x27
	add	x0, x23, x0, lsl 2
	ldr	w3, [x0, 56]
	mov	x0, x21
	bl	H264HAL_V4R3C1_SetSliceMsg.isra.7
	cbnz	w0, .L182
.L241:
	ldr	w1, [x21, 940]
	mov	x27, x19
	cmp	w20, w1
	blt	.L183
.L238:
	cmp	w1, wzr
	ble	.L184
	add	x0, x22, x22, lsl 2
	add	w1, w1, 4
	lsl	x0, x0, 4
	add	w1, w1, w25
	sub	x0, x0, x22
	lsl	x0, x0, 1
	sub	x0, x0, x22
	lsl	x0, x0, 1
	add	x0, x0, x1, sxtw
	add	x23, x23, x0, lsl 2
	ldr	w0, [x23, 56]
	bl	MEM_Phy2Vir
	cbz	x0, .L240
	str	wzr, [x0, 252]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L230:
	ldr	x1, .LC83
	mov	w0, 0
	bl	dprint_vfmw
.L132:
	mov	w0, -1
.L219:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L239:
	ldr	w0, [x21, 44]
	mov	w3, 0
	ldr	w4, [x21, 36]
	mov	x1, x27
	str	xzr, [x27, 4056]
	mul	w4, w0, w4
	mov	x0, x21
	ldr	w20, [x21, 940]
	sub	w4, w4, #1
	bl	H264HAL_V4R3C1_SetSliceMsg.isra.7
	cbz	w0, .L241
.L182:
	ldr	x1, .LC154
	mov	w2, 1185
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L174:
	ldr	x1, .LC156
	mov	w2, 814
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L194:
	mov	w1, 2
	mov	w25, w1
	b	.L148
.L153:
	str	wzr, [x19, 12]
	mov	w0, 4
	ldr	w24, [x29, 100]
	ldr	w3, [x19, 12]
	ldr	x1, .LC130
	add	w2, w24, 12
	str	wzr, [x19, 16]
	bl	dprint_vfmw
	ldr	x1, .LC132
	add	w2, w24, 16
	ldr	w3, [x19, 16]
	mov	w0, 4
	bl	dprint_vfmw
	b	.L154
.L138:
	mov	w0, -121438208
	b	.L139
.L237:
	lsl	x0, x22, 6
	str	wzr, [x27, 48]
	sub	x0, x0, x22
	mov	w25, 1
	lsl	x1, x0, 2
	sub	w4, w19, #1
	sub	x0, x1, x22
	ldp	w7, w6, [x27, 8]
	ldp	w5, w28, [x27, 16]
	stp	w25, wzr, [x27, 8]
	stp	wzr, wzr, [x27, 16]
	add	x0, x1, x0, lsl 2
	str	w5, [x29, 108]
	ldr	w1, [x21, 736]
	add	x0, x23, x0
	ldp	w26, w20, [x27, 24]
	stp	w1, wzr, [x27, 24]
	mov	x1, x27
	ldp	w2, w3, [x0, 76]
	mov	x0, x21
	stp	w7, w6, [x29, 100]
	bl	H264HAL_V4R3C1_SetSliceMsg.isra.7
	ldp	w7, w6, [x29, 100]
	ldr	w5, [x29, 108]
	cbnz	w0, .L242
	stp	w7, w6, [x27, 8]
	stp	w5, w28, [x27, 16]
	stp	w26, w20, [x27, 24]
	str	w19, [x27, 48]
	ldr	x27, [x21, 944]
	b	.L169
.L155:
	ldr	w1, [x21, 316]
	ldr	w0, [x21, 716]
	add	x1, x21, x1, lsl 2
	ldr	w1, [x1, 584]
	add	w0, w1, w0
	and	w0, w0, -16
	b	.L156
.L197:
	mov	x19, x27
	b	.L173
.L189:
	mov	w24, 0
	mov	w0, 0
	mov	w25, 0
	b	.L142
.L233:
	ldr	x1, .LC100
	mov	x3, x20
	mov	w2, w19
	mov	w0, 92
	ldr	w24, [x1]
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC102
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w1, [x21, 308]
	mov	w2, w19
	mov	w0, 112
	mov	x3, x20
	add	x1, x21, x1, lsl 2
	ldr	w24, [x1, 452]
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC104
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	b	.L146
.L235:
	ldr	w0, [x29, 100]
	add	w0, w0, 108
	str	w0, [x29, 108]
	b	.L163
.L231:
	bl	MEM_Phy2Vir
	str	x0, [x24, x23]
	cbnz	x0, .L140
	ldr	x1, .LC86
	bl	dprint_vfmw
	b	.L132
	.p2align 3
.L227:
	ldr	x2, .LC72
	mov	w4, 0
	ldr	x1, .LC74
	mov	w3, w19
	add	x2, x2, 112
	mov	w0, 0
	bl	dprint_vfmw
	b	.L132
.L135:
	ldr	x2, .LC72
	mov	w0, 0
	ldr	x3, .LC79
	ldr	x1, .LC77
	add	x2, x2, 112
	bl	dprint_vfmw
	b	.L132
.L242:
	ldr	x1, .LC154
	mov	w2, 1132
	mov	w0, w25
	bl	dprint_vfmw
	mov	w0, -1
	b	.L219
.L184:
	ldr	x1, .LC159
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L219
.L236:
	ldr	x1, .LC152
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L219
.L234:
	ldr	x0, .LC72
	ldr	x3, .LC122
	ldr	x1, .LC77
	add	x2, x0, 200
	mov	w0, 0
	bl	dprint_vfmw
	b	.L150
.L232:
	ldr	x2, .LC72
	mov	x3, x20
	ldr	x1, .LC88
	mov	w0, 0
	add	x2, x2, 136
	bl	dprint_vfmw
	mov	w0, -1
	b	.L219
.L240:
	ldr	x0, .LC72
	ldr	x3, .LC157
	ldr	x1, .LC77
	add	x2, x0, 232
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L219
.L228:
	ldr	x2, .LC72
	mov	w0, 0
	ldr	x3, .LC76
	ldr	x1, .LC77
	add	x2, x2, 112
	bl	dprint_vfmw
	b	.L132
.L229:
	ldr	x2, .LC72
	ldr	x3, .LC81
	ldr	x1, .LC77
	add	x2, x2, 112
	bl	dprint_vfmw
	b	.L132
	.size	H264HAL_V4R3C1_StartDec, .-H264HAL_V4R3C1_StartDec
	.align	3
.LC72:
	.xword	.LANCHOR0
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC77:
	.xword	.LC11
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.align	3
.LC84:
	.xword	g_HwMem
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC89:
	.xword	s_pstVfmwChan
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC100:
	.xword	g_TunnelLineNumber
	.align	3
.LC102:
	.xword	.LC101
	.align	3
.LC104:
	.xword	.LC103
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC110:
	.xword	.LC109
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC120:
	.xword	.LC119
	.align	3
.LC122:
	.xword	.LC121
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
	.align	3
.LC134:
	.xword	.LC133
	.align	3
.LC136:
	.xword	.LC135
	.align	3
.LC138:
	.xword	.LC137
	.align	3
.LC140:
	.xword	.LC139
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC144:
	.xword	.LC143
	.align	3
.LC146:
	.xword	.LC145
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC152:
	.xword	.LC151
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC157:
	.xword	.LC8
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC160:
	.xword	.LANCHOR1
	.align	3
.LC162:
	.xword	.LC161
	.align	3
.LC163:
	.xword	g_VdmDrvParam
	.align	3
.LC164:
	.xword	g_HalDisable
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	g_ListStructFrame, %object
	.size	g_ListStructFrame, 32
g_ListStructFrame:
	.word	0
	.word	1
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.type	g_ListStructField, %object
	.size	g_ListStructField, 32
g_ListStructField:
	.word	0
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.type	__func__.11488, %object
	.size	__func__.11488, 27
__func__.11488:
	.string	"H264HAL_V4R3C1_SetSliceMsg"
	.zero	5
	.type	g_SliceTypeForPMV, %object
	.size	g_SliceTypeForPMV, 12
g_SliceTypeForPMV:
	.word	1
	.word	2
	.word	0
	.zero	4
	.type	__func__.11411, %object
	.size	__func__.11411, 23
__func__.11411:
	.string	"H264HAL_CheckParaValid"
	.zero	1
	.type	__func__.11432, %object
	.size	__func__.11432, 25
__func__.11432:
	.string	"H264HAL_V4R3C1_CfgVdmReg"
	.zero	7
	.type	g_StructTrans, %object
	.size	g_StructTrans, 32
g_StructTrans:
	.word	0
	.word	3
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.type	__func__.11458, %object
	.size	__func__.11458, 25
__func__.11458:
	.string	"H264HAL_V4R3C1_SetPicMsg"
	.zero	7
	.type	__func__.11277, %object
	.size	__func__.11277, 29
__func__.11277:
	.string	"H264HAL_V4R3C1_CutSliceChain"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"slicemsg D[%d] address 0x%x = 0x%x\n" )
	.zero	4
.LC8:
	ASCII(.string	"can not map slice msg virtual address!\n" )
.LC11:
	ASCII(.string	"%s: %s\n" )
.LC13:
	ASCII(.string	"Before slicemsg D[%d] tmp =0x%x,bitsoffset =0x%x,bytespos = 0x%x\n" )
	.zero	6
.LC15:
	ASCII(.string	"slicemsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	7
.LC17:
	ASCII(.string	"slicemsg D[4] addr 0x%x = 0x%x\n" )
.LC20:
	ASCII(.string	"slicemsg D[5] addr 0x%x = 0x%x\n" )
.LC22:
	ASCII(.string	"slicemsg g_pListX[1][0]->frame_store->pmv_address_idc = %d\n" )
	.zero	4
.LC24:
	ASCII(.string	"slicemsg D[6] addr 0x%x = 0x%x\n" )
.LC26:
	ASCII(.string	"slicemsg D[7] addr 0x%x = 0x%x\n" )
.LC28:
	ASCII(.string	"slicemsg D[8] addr 0x%x = 0x%x\n" )
.LC30:
	ASCII(.string	"slicemsg D[9] addr 0x%x = 0x%x\n" )
.LC33:
	ASCII(.string	"slicemsg burst1 D0~D31, burst2 D0~31, burst3 D0~D31 list0size = %d\n" )
	.zero	4
.LC35:
	ASCII(.string	"luma_lg = %d\n" )
	.zero	2
.LC37:
	ASCII(.string	"wp_weight_l0_y = %d\n" )
	.zero	3
.LC39:
	ASCII(.string	"wp_offset_l0_y = %d\n" )
	.zero	3
.LC41:
	ASCII(.string	"chroma_lg = %d\n" )
.LC43:
	ASCII(.string	"wp_weight_l1_y = %d\n" )
	.zero	3
.LC45:
	ASCII(.string	"wp_offset_l1_y = %d\n" )
	.zero	3
.LC47:
	ASCII(.string	"wp_weight_l0_u = %d\n" )
	.zero	3
.LC49:
	ASCII(.string	"wp_offset_l0_u = %d\n" )
	.zero	3
.LC51:
	ASCII(.string	"wp_weight_l1_u = %d\n" )
	.zero	3
.LC53:
	ASCII(.string	"wp_offset_l1_u = %d\n" )
	.zero	3
.LC55:
	ASCII(.string	"wp_weight_l0_v = %d\n" )
	.zero	3
.LC57:
	ASCII(.string	"wp_offset_l0_v = %d\n" )
	.zero	3
.LC59:
	ASCII(.string	"wp_weight_l1_v = %d\n" )
	.zero	3
.LC61:
	ASCII(.string	"wp_offset_l1_v = %d\n" )
	.zero	3
.LC63:
	ASCII(.string	"slicemsg burst1 D32~D63, burst2 D32~63, burst3 D32~D63 list1size = %d\n" )
	.zero	1
.LC66:
	ASCII(.string	"line: %d, p = NULL is not expected value!\n" )
	.zero	5
.LC68:
	ASCII(.string	"H264HAL_V4R3C1_InitHal return error.\n" )
	.zero	2
.LC73:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC75:
	ASCII(.string	"point of picture para null\n" )
	.zero	4
.LC78:
	ASCII(.string	"picture width out of range\n" )
	.zero	4
.LC80:
	ASCII(.string	"point of fst slice para null\n" )
	.zero	2
.LC82:
	ASCII(.string	"VdhId is wrong! H264HAL_StartDec\n" )
	.zero	6
.LC85:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC87:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC90:
	ASCII(.string	"BASIC_V4R3C1_CFG0 = 0x%x\n" )
	.zero	6
.LC92:
	ASCII(.string	"BASIC_V4R3C1_CFG1 = 0x%x\n" )
	.zero	6
.LC94:
	ASCII(.string	"AVM_V4R3C1_ADDR = 0x%x\n" )
.LC96:
	ASCII(.string	"VAM_V4R3C1_ADDR = 0x%x\n" )
.LC98:
	ASCII(.string	"STREAM_V4R3C1_BASE_ADDR = 0x%x\n" )
.LC101:
	ASCII(.string	"VREG_PART_DEC_OVER_INT_LEVEL=0x%x\n" )
	.zero	5
.LC103:
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC105:
	ASCII(.string	"YSTADDR_V4R3C1_1D = 0x%x\n" )
	.zero	6
.LC107:
	ASCII(.string	"YSTRIDE_V4R3C1_1D = 0x%x\n" )
	.zero	6
.LC109:
	ASCII(.string	"UVOFFSET_V4R3C1_1D = 0x%x\n" )
	.zero	5
.LC111:
	ASCII(.string	"HEAD_INF_OFFSET_V4R3C1_1D = 0x%x\n" )
	.zero	6
.LC113:
	ASCII(.string	"PPFD_V4R3C1_BUF_ADDR = 0x%x\n" )
	.zero	3
.LC115:
	ASCII(.string	"PPFD_V4R3C1_BUF_LEN = 0x%x\n" )
	.zero	4
.LC117:
	ASCII(.string	"REF_V4R3C1_PIC_TYPE = 0x%x\n" )
	.zero	4
.LC119:
	ASCII(.string	"FF_V4R3C1_APT_EN = 0x%x\n" )
	.zero	7
.LC121:
	ASCII(.string	"can not map down msg virtual address!\n" )
	.zero	1
.LC123:
	ASCII(.string	"picmsg D[0] addr 0x%x = 0x%x\n" )
	.zero	2
.LC125:
	ASCII(.string	"picmsg D[1] addr 0x%x = 0x%x\n" )
	.zero	2
.LC127:
	ASCII(.string	"picmsg D[2] addr 0x%x = 0x%x\n" )
	.zero	2
.LC129:
	ASCII(.string	"picmsg D[3] addr 0x%x = 0x%x\n" )
	.zero	2
.LC131:
	ASCII(.string	"picmsg D[4] addr 0x%x = 0x%x\n" )
	.zero	2
.LC133:
	ASCII(.string	"picmsg D[5] addr 0x%x = 0x%x\n" )
	.zero	2
.LC135:
	ASCII(.string	"picmsg D[6] addr 0x%x = 0x%x\n" )
	.zero	2
.LC137:
	ASCII(.string	"picmsg D[7] addr 0x%x = 0x%x\n" )
	.zero	2
.LC139:
	ASCII(.string	"picmsg D[8] addr 0x%x = 0x%x\n" )
	.zero	2
.LC141:
	ASCII(.string	"picmsg D[9] addr 0x%x = 0x%x\n" )
	.zero	2
.LC143:
	ASCII(.string	"picmsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	1
.LC145:
	ASCII(.string	"picmsg D[26] addr 0x%x = 0x%x\n" )
	.zero	1
.LC147:
	ASCII(.string	"qmatrix[%d] = 0x%x\n" )
	.zero	4
.LC149:
	ASCII(.string	"picmsg Dxx addr 0x%x = 0x%x\n" )
	.zero	3
.LC151:
	ASCII(.string	"pSlicePara = NULL!\n" )
	.zero	4
.LC153:
	ASCII(.string	"line %d Set slice msg not wrong!\n" )
	.zero	6
.LC155:
	ASCII(.string	"line %d pSlicePara is NULL!\n" )
	.zero	3
.LC158:
	ASCII(.string	"!!! no slice to dec, add up msg report." )
.LC161:
	ASCII(.string	"\n\n***********************H264HAL_StartDec is Now %d***********************\n" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	StartCnt.11510, %object
	.size	StartCnt.11510, 4
StartCnt.11510:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
