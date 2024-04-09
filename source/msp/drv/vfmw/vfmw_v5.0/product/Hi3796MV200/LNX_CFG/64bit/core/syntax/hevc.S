#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"hevc.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	HEVC_ComparePicByPocAsc, %function
HEVC_ComparePicByPocAsc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, -1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 8]
	ldr	w2, [x2, 8]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	HEVC_ComparePicByPocAsc, .-HEVC_ComparePicByPocAsc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_UpdateInterLayerReflist, %function
HEVC_UpdateInterLayerReflist:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w27, [x20, 5600]
	cbz	w27, .L56
	ldr	w10, [x20, 6928]
	ldr	x7, [x20, 3000]
	cmp	w10, wzr
	ble	.L31
	sxtw	x27, w27
	mov	w24, 0
	mov	w25, 0
	mov	w26, 0
	add	x23, x7, 12288
	lsl	x22, x27, 1
	mov	w21, 1
	.p2align 2
.L25:
	add	x1, x20, x26, sxtw 2
	add	x0, x23, 132
	add	x2, x27, 1032
	ldr	w3, [x0, 4128]
	ldrsw	x1, [x1, 6932]
	ldr	w2, [x0, x2, lsl 2]
	add	x1, x22, x1
	add	x1, x1, 1044
	cmp	w2, w3
	ldr	w6, [x0, x1, lsl 2]
	add	x0, x0, x6, sxtw 2
	ble	.L57
	ldr	w0, [x0, 4128]
	cmp	w2, w0
	cset	w28, ge
.L9:
	ldr	w4, [x20, 3380]
	cbz	w4, .L11
	mov	w0, 0
	ldr	w5, [x20, 5580]
	b	.L24
	.p2align 3
.L12:
	cmp	w0, w4
	beq	.L11
.L24:
	sxtw	x2, w0
	add	w0, w0, 1
	add	x1, x20, x2, lsl 3
	ldr	x1, [x1, 3688]
	ldr	w3, [x1, 8]
	cmp	w3, w5
	bne	.L12
	ldr	w3, [x1, 32]
	cmp	w3, w6
	bne	.L12
	add	x19, x20, x2, lsl 3
	mov	w0, 1
	strb	w0, [x1, 1]
	ldr	x0, [x19, 3688]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L58
.L13:
	str	wzr, [x0, 64]
	ldr	x0, [x19, 3688]
	str	w21, [x0, 60]
	ldr	x0, [x19, 3688]
	str	w21, [x0, 72]
	ldr	x4, [x19, 3688]
	cbz	x4, .L59
	ldr	w10, [x20, 5600]
	uxtw	x6, w10
	lsl	x0, x6, 5
	add	x0, x0, x6, lsl 3
	add	x1, x20, x0, lsl 3
	sub	x0, x1, x0
	ldr	w3, [x0, 14188]
	cbz	w3, .L15
	ldr	w0, [x0, 14196]
	cbz	w0, .L60
	mov	w0, 280
	mov	x1, 14200
	mov	w2, 0
	umaddl	x0, w10, w0, x1
	add	x0, x20, x0
	b	.L18
	.p2align 3
.L22:
	ldr	w1, [x0], 4
	cbz	w1, .L16
.L18:
	add	w2, w2, 1
	cmp	w2, w3
	bne	.L22
.L15:
	cbz	w28, .L23
	add	x0, x20, x25, sxtw 3
	add	w25, w25, 1
	str	x4, [x0, 3416]
	ldr	w10, [x20, 6928]
	.p2align 2
.L11:
	add	w26, w26, 1
	cmp	w10, w26
	bgt	.L25
	mov	w2, w25
	mov	w1, w24
.L7:
	ldr	w0, [x20, 3376]
	str	w2, [x20, 3404]
	cmp	w0, w25
	str	w1, [x20, 3408]
	ble	.L29
	.p2align 2
.L41:
	add	x1, x20, x25, sxtw 3
	add	w25, w25, 1
	cmp	w25, w0
	str	xzr, [x1, 3416]
	bne	.L41
.L29:
	cmp	w0, w24
	ble	.L4
	.p2align 2
.L40:
	add	x1, x20, x24, sxtw 3
	add	w24, w24, 1
	cmp	w24, w0
	str	xzr, [x1, 3552]
	bne	.L40
.L4:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L57:
	ldr	w0, [x0, 4128]
	mov	w28, 1
	cmp	w2, w0
	ble	.L9
	cmp	w2, w3
	cset	w28, ge
	b	.L9
.L23:
	add	x0, x20, x24, sxtw 3
	add	w24, w24, 1
	str	x4, [x0, 3552]
	ldr	w10, [x20, 6928]
	b	.L11
.L60:
	mov	w2, 0
.L16:
	ldr	w1, [x4, 28]
	ldr	w0, [x20, 276]
	str	x4, [x29, 120]
	str	x6, [x29, 104]
	stp	w2, w10, [x29, 112]
	bl	FSP_GetLogicFs
	ldr	x4, [x29, 120]
	cbz	x0, .L19
	ldr	x1, [x0, 32]
	ldp	w2, w10, [x29, 112]
	ldr	x6, [x29, 104]
	cbz	x1, .L19
	uxtw	x3, w2
	mov	w1, 70
	lsl	x5, x6, 5
	umaddl	x1, w10, w1, x3
	add	x5, x5, x6, lsl 3
	add	x1, x20, x1, lsl 2
	str	w21, [x1, 14196]
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x1, 14260]
	ldr	w0, [x4, 8]
	str	w0, [x1, 14324]
	add	x0, x20, x5, lsl 3
	sub	x5, x0, x5
	add	x0, x5, x3
	add	x0, x0, 12288
	ldr	w3, [x5, 14192]
	add	w3, w3, 1
	str	w3, [x5, 14192]
	ldr	w3, [x4, 32]
	str	w3, [x1, 14388]
	str	w2, [x4, 36]
	strb	w21, [x0, 2164]
	ldr	x4, [x19, 3688]
	b	.L15
.L56:
	str	wzr, [x20, 3404]
	str	wzr, [x20, 3408]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L58:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	ldr	x0, [x19, 3688]
	b	.L13
.L31:
	mov	w1, 0
	mov	w2, 0
	mov	w24, 0
	mov	w25, 0
	b	.L7
.L19:
	ldr	w3, [x4, 8]
	mov	x5, x0
	ldr	w2, [x4, 28]
	mov	x6, 0
	ldrb	w4, [x4, 1]
	mov	w0, 0
	ldr	x1, .LC7
	bl	dprint_vfmw
	ldr	x4, [x19, 3688]
	b	.L15
.L59:
	ldr	x2, .LC3
	mov	w3, 170
	ldr	x1, .LC5
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x4, [x19, 3688]
	b	.L15
	.size	HEVC_UpdateInterLayerReflist, .-HEVC_UpdateInterLayerReflist
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC7:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_CheckThatAllRefPicsAreAvailable.part.14, %function
HEVC_CheckThatAllRefPicsAreAvailable.part.14:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19, 5604]
	mov	w4, 5036
	ldr	x2, [x19, 2968]
	add	x7, x19, 4096
	add	x15, x7, 2404
	ldr	x1, [x19, 2960]
	mov	w3, 12668
	ldr	w8, [x19, 6500]
	smaddl	x2, w0, w4, x2
	ldr	w4, [x15, 4]
	mov	w0, 1
	ldr	w16, [x15, 8]
	ldr	w2, [x2, 32]
	add	w8, w8, w4
	cmp	w8, w16
	mov	w11, w8
	smaddl	x1, w2, w3, x1
	ldr	w14, [x1, 116]
	lsl	w14, w0, w14
	bcs	.L62
	ldr	w3, [x19, 3380]
	mov	w10, 0
	sub	w14, w14, #1
	mov	w9, 0
	.p2align 2
.L63:
	sxtw	x13, w11
	cbz	w3, .L69
	add	x5, x19, x13, lsl 2
	mov	w12, 0
	mov	w0, 0
	ldr	w2, [x5, 5656]
	b	.L66
	.p2align 3
.L119:
	cbz	w4, .L65
	ldr	w6, [x1, 8]
	ldr	w4, [x5, 6600]
	cmp	w6, w4
	beq	.L117
	.p2align 2
.L65:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L118
.L66:
	add	x1, x19, x0, sxtw 3
	ldr	x1, [x1, 3688]
	ldr	w4, [x1, 60]
	cbnz	w2, .L119
	cbz	w4, .L65
	ldr	w6, [x1, 8]
	ldr	w4, [x5, 6600]
	eor	w4, w6, w4
	tst	w4, w14
	bne	.L65
.L117:
	ldrb	w4, [x1, 1]
	cbz	w4, .L65
	ldr	x4, [x19, 3040]
	ldr	w6, [x1, 16]
	ldr	w1, [x4, 4]
	cmp	w6, w1
	bls	.L81
	ldr	w1, [x4, 684]
	add	w0, w0, 1
	cmp	w1, 1
	csinc	w12, w12, wzr, eq
	cmp	w0, w3
	bne	.L66
	.p2align 2
.L118:
	cbz	w12, .L69
.L67:
	add	w11, w11, 1
	cmp	w16, w11
	bne	.L63
	cbz	w8, .L71
.L70:
	mov	w11, 0
	add	x7, x7, 2404
	.p2align 2
.L75:
	mov	w12, 0
	mov	w0, 0
	sxtw	x5, w11
	cbnz	w3, .L102
	b	.L77
	.p2align 3
.L72:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L120
.L102:
	add	x2, x19, x0, sxtw 3
	add	x1, x5, 8
	ldr	x2, [x2, 3688]
	ldr	w4, [x2, 60]
	cbnz	w4, .L72
	ldr	w4, [x7, x1, lsl 2]
	ldr	w6, [x19, 5580]
	ldr	w1, [x2, 8]
	add	w4, w6, w4
	cmp	w1, w4
	bne	.L72
	ldrb	w1, [x2, 1]
	cbz	w1, .L72
	ldr	x1, [x19, 3040]
	ldr	w4, [x2, 16]
	ldr	w2, [x1, 4]
	cmp	w4, w2
	bls	.L84
	ldr	w1, [x1, 684]
	add	w0, w0, 1
	cmp	w1, 1
	csinc	w12, w12, wzr, eq
	cmp	w0, w3
	bne	.L102
	.p2align 2
.L120:
	cbz	w12, .L77
.L74:
	add	w11, w11, 1
	cmp	w8, w11
	bhi	.L75
.L71:
	mov	w0, 1
	cbz	w9, .L101
	mov	w0, 0
	str	w10, [x20]
.L101:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L77:
	ldr	w1, [x19, 5600]
	sxtw	x2, w11
	add	x0, x2, 8
	ldr	w4, [x19, 5580]
	add	x1, x19, x1, lsl 2
	ldr	w0, [x7, x0, lsl 2]
	ldr	w1, [x1, 244]
	add	w0, w4, w0
	cmp	w0, w1
	blt	.L74
	add	x2, x7, x2
	ldrb	w1, [x2, 12]
	cmp	w1, wzr
	csel	w10, w10, w0, eq
	csinc	w9, w9, wzr, eq
	b	.L74
	.p2align 3
.L69:
	ldr	w1, [x19, 5600]
	add	x2, x13, 8
	ldr	w4, [x19, 5580]
	add	x1, x19, x1, lsl 2
	ldr	w0, [x15, x2, lsl 2]
	add	w0, w4, w0
	ldr	w1, [x1, 244]
	cmp	w0, w1
	blt	.L67
	add	x13, x15, x13
	ldrb	w1, [x13, 12]
	cmp	w1, wzr
	csel	w10, w10, w0, eq
	csinc	w9, w9, wzr, eq
	b	.L67
	.p2align 3
.L81:
	mov	w12, 1
	b	.L65
	.p2align 3
.L84:
	mov	w12, 1
	b	.L72
.L62:
	cbz	w8, .L101
	mov	w10, 0
	mov	w9, 0
	ldr	w3, [x19, 3380]
	b	.L70
	.size	HEVC_CheckThatAllRefPicsAreAvailable.part.14, .-HEVC_CheckThatAllRefPicsAreAvailable.part.14
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_SetFrmRepeatCount.part.15, %function
HEVC_SetFrmRepeatCount.part.15:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w3, [x19, 316]
	ldr	w2, [x19, 3376]
	ldr	w0, [x19, 312]
	add	w2, w3, w2
	add	w3, w2, 1
	cmp	w0, w3
	bcc	.L122
	sub	w0, w0, #1
	sub	w0, w0, w2
	cmp	w0, 1
	bls	.L123
	mov	w0, 2
	str	w0, [x20, 16]
	ldr	w0, [x19, 316]
	add	w0, w0, 2
	str	w0, [x19, 316]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L122:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L123:
	mov	w0, 1
	str	w0, [x20, 16]
	ldr	w0, [x19, 316]
	add	w0, w0, 1
	str	w0, [x19, 316]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_SetFrmRepeatCount.part.15, .-HEVC_SetFrmRepeatCount.part.15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_OutputFrame, %function
HEVC_OutputFrame:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x21, x1
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 276]
	ldr	w1, [x21, 28]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L174
	ldrb	w2, [x19, 1]
	cmp	w2, 1
	beq	.L175
.L128:
	ldr	w0, [x19, 276]
	mov	w2, 1
	ldr	w1, [x21, 28]
	bl	FSP_SetDisplay
	add	x3, x19, 4096
	ldr	w0, [x19, 276]
	mov	x4, x20
	add	x3, x3, 2848
	mov	x2, x19
	mov	w1, 16
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L146
.L135:
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L176
	str	wzr, [x20, 16]
.L145:
	ldr	w1, [x19, 316]
	mov	w0, 0
	ldr	w2, [x19, 324]
	add	w1, w1, 1
	str	w1, [x19, 316]
	add	w2, w2, 1
	str	w2, [x19, 324]
.L170:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L176:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SetFrmRepeatCount.part.15
	b	.L145
	.p2align 3
.L175:
	ldr	w0, [x19, 276]
	ldr	w1, [x21, 28]
	bl	FSP_SetDisplay
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 24]
	cmp	w0, 6
	beq	.L177
	tst	w0, -5
	bne	.L143
	ldr	w0, [x21, 32]
	cbz	w0, .L128
	b	.L144
	.p2align 3
.L143:
	cmp	w0, 5
	bne	.L128
	ldr	w0, [x21, 32]
	cmp	w0, 1
	beq	.L128
.L144:
	ldr	w0, [x19, 276]
	mov	w2, 0
	ldr	w1, [x21, 28]
	bl	FSP_SetDisplay
	b	.L135
	.p2align 3
.L177:
	add	x22, x19, 2416
	cbz	x21, .L130
	ldr	w0, [x21, 32]
	add	x23, x19, 2680
	cmp	w0, wzr
	csel	x23, x22, x23, eq
	ldrh	w0, [x23, 2]
	ldrh	w3, [x23]
	add	w1, w0, 1
	and	w2, w1, 15
	cmp	w2, w3
	beq	.L178
.L133:
	sbfiz	x0, x0, 4, 32
	ldr	w2, [x21, 8]
	add	x0, x23, x0
	and	w1, w1, 15
	str	w2, [x0, 8]
	ldr	w2, [x21, 28]
	str	w2, [x0, 12]
	str	x20, [x0, 16]
	strh	w1, [x23, 2]
.L130:
	ldr	x23, .LC8
	ldrh	w21, [x19, 2416]
	add	x23, x23, 24
	ldr	x26, .LC20
	ldr	x25, .LC18
	mov	x24, x23
.L134:
	ldrh	w0, [x22, 2]
	cmp	w0, w21
	beq	.L135
.L181:
	ldrh	w5, [x19, 2680]
	ldrh	w0, [x19, 2682]
	cmp	w0, w5
	beq	.L135
	ubfiz	x21, x21, 4, 16
	add	x21, x19, x21
	ldr	x4, [x21, 2432]
	cbz	x4, .L135
	ubfiz	x5, x5, 4, 16
	add	x27, x19, x5
	ldr	x0, [x27, 2696]
	cbz	x0, .L135
	ldr	w3, [x21, 2424]
	ldr	w0, [x27, 2688]
	cmp	w3, w0
	bgt	.L179
	blt	.L180
	ldr	w0, [x4, 180]
	cbz	w0, .L139
	str	wzr, [x4, 180]
	mov	w1, 1
	ldr	x0, [x27, 2696]
	str	w1, [x0, 180]
	ldr	x4, [x21, 2432]
.L139:
	add	x28, x19, 4096
	ldr	w0, [x19, 276]
	add	x28, x28, 2848
	mov	x2, x19
	mov	x3, x28
	mov	w1, 16
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L140
	ldr	w3, [x21, 2424]
	mov	x2, x24
	mov	x1, x25
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 276]
	mov	w2, 0
	ldr	w1, [x21, 2428]
	bl	FSP_SetDisplay
.L140:
	ldrh	w0, [x22]
	mov	x3, x28
	mov	x2, x19
	mov	w1, 16
	add	w0, w0, 1
	and	w0, w0, 15
	strh	w0, [x22]
	ldr	w0, [x19, 276]
	ldr	x4, [x27, 2696]
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L141
	ldr	w3, [x27, 2688]
	mov	x2, x23
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
.L172:
	ldr	w0, [x19, 276]
	mov	w2, 0
	ldr	w1, [x27, 2692]
	bl	FSP_SetDisplay
.L141:
	ldrh	w0, [x19, 2680]
	add	w0, w0, 1
	and	w0, w0, 15
	strh	w0, [x19, 2680]
	ldrh	w21, [x22]
	ldrh	w0, [x22, 2]
	cmp	w0, w21
	bne	.L181
	b	.L135
	.p2align 3
.L179:
	ldr	x2, .LC8
	mov	w4, w0
	ldr	x1, .LC14
	mov	w0, 1
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L172
	.p2align 3
.L180:
	ldr	x1, .LC16
	mov	w4, w3
	ldr	x2, .LC23
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x21, 2428]
	mov	w2, 0
	ldr	w0, [x19, 276]
	bl	FSP_SetDisplay
	ldrh	w21, [x22]
	add	w21, w21, 1
	and	w21, w21, 15
	strh	w21, [x22]
	b	.L134
	.p2align 3
.L146:
	ldr	x2, .LC8
	mov	w0, 1
	ldr	x1, .LC22
	bl	dprint_vfmw
	ldr	w0, [x19, 276]
	mov	w2, 0
	ldr	w1, [x21, 28]
	bl	FSP_SetDisplay
	mov	w0, -1
	b	.L170
.L174:
	ldr	x2, .LC8
	mov	w0, 0
	ldr	x1, .LC10
	bl	dprint_vfmw
	mov	w0, -1
	b	.L170
.L178:
	sbfiz	x1, x2, 4, 32
	ldr	w0, [x19, 276]
	add	x1, x23, x1
	mov	w2, 0
	ldr	w24, [x1, 12]
	mov	w1, w24
	bl	FSP_SetDisplay
	ldrh	w2, [x23]
	mov	w3, w24
	ldr	x1, .LC12
	mov	w0, 1
	add	w2, w2, 1
	and	w2, w2, 15
	strh	w2, [x23]
	ldr	w2, [x21, 32]
	bl	dprint_vfmw
	ldrh	w0, [x23, 2]
	add	w1, w0, 1
	b	.L133
	.size	HEVC_OutputFrame, .-HEVC_OutputFrame
	.align	3
.LC8:
	.xword	.LANCHOR0
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
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC23:
	.xword	.LANCHOR0+24
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_Sei_Mastering_Display_Colour_Volume.part.24, %function
HEVC_Sei_Mastering_Display_Colour_Volume.part.24:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	add	x19, x1, 4
	add	x22, x1, 16
	bl	_mcount
.L183:
	add	x19, x19, 4
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	str	w0, [x19, -4]
	mov	w1, 16
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x19, 8]
	cmp	x19, x22
	bne	.L183
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	str	w0, [x21, 28]
	mov	w1, 16
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x21, 32]
	mov	w1, 32
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x21, 36]
	mov	w1, 32
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x21, 40]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_Sei_Mastering_Display_Colour_Volume.part.24, .-HEVC_Sei_Mastering_Display_Colour_Volume.part.24
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckVpsExtOverlap
	.type	HEVC_CheckVpsExtOverlap, %function
HEVC_CheckVpsExtOverlap:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L189
.L186:
	add	x1, x19, 12288
	ldrb	w2, [x19]
	mov	w0, 2
	ldr	x19, [sp, 16]
	cmp	w2, wzr
	ldrb	w2, [x1, 200]
	cset	w1, ne
	ldp	x29, x30, [sp], 32
	cmp	w2, wzr
	csel	w0, w0, wzr, ne
	orr	w0, w0, w1
	ret
	.p2align 3
.L189:
	ldr	x2, .LC24
	mov	w0, 1
	ldr	x1, .LC26
	add	x2, x2, 56
	bl	dprint_vfmw
	b	.L186
	.size	HEVC_CheckVpsExtOverlap, .-HEVC_CheckVpsExtOverlap
	.align	3
.LC24:
	.xword	.LANCHOR0
	.align	3
.LC26:
	.xword	.LC25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckPpsExtOverlap
	.type	HEVC_CheckPpsExtOverlap, %function
HEVC_CheckPpsExtOverlap:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L194
.L191:
	ldrb	w1, [x19]
	mov	w0, 2
	ldrb	w2, [x19, 3144]
	cmp	w1, wzr
	ldr	x19, [sp, 16]
	cset	w1, ne
	cmp	w2, wzr
	csel	w0, w0, wzr, ne
	orr	w0, w0, w1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L194:
	ldr	x2, .LC27
	mov	w0, 1
	ldr	x1, .LC29
	add	x2, x2, 80
	bl	dprint_vfmw
	b	.L191
	.size	HEVC_CheckPpsExtOverlap, .-HEVC_CheckPpsExtOverlap
	.align	3
.LC27:
	.xword	.LANCHOR0
	.align	3
.LC29:
	.xword	.LC28
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckSliceExtOverlap
	.type	HEVC_CheckSliceExtOverlap, %function
HEVC_CheckSliceExtOverlap:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L199
.L196:
	ldrb	w1, [x19]
	mov	w0, 2
	ldrb	w2, [x19, 16]
	cmp	w1, wzr
	ldr	x19, [sp, 16]
	cset	w1, ne
	cmp	w2, wzr
	csel	w0, w0, wzr, ne
	orr	w0, w0, w1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L199:
	ldr	x2, .LC30
	mov	w0, 1
	ldr	x1, .LC32
	add	x2, x2, 104
	bl	dprint_vfmw
	b	.L196
	.size	HEVC_CheckSliceExtOverlap, .-HEVC_CheckSliceExtOverlap
	.align	3
.LC30:
	.xword	.LANCHOR0
	.align	3
.LC32:
	.xword	.LC31
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_ParsePts_Init
	.type	HEVC_Sei_ParsePts_Init, %function
HEVC_Sei_ParsePts_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC33
	add	x0, x19, 12288
	mov	x2, 56
	mov	w1, 0
	add	x0, x0, 464
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x19, 4236]
	str	xzr, [x19, 4256]
	str	xzr, [x19, 4264]
	str	xzr, [x19, 4272]
	str	xzr, [x19, 4280]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_Sei_ParsePts_Init, .-HEVC_Sei_ParsePts_Init
	.align	3
.LC33:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Get_Dpb_Output_Time
	.type	HEVC_Sei_Get_Dpb_Output_Time, %function
HEVC_Sei_Get_Dpb_Output_Time:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w4, [x19, 5604]
	ldr	w5, [x19, 164]
	tbnz	w4, #31, .L203
	cmp	w4, w5
	bge	.L203
	ldr	x0, [x19, 2968]
	mov	w1, 5036
	ldr	w5, [x19, 160]
	smaddl	x4, w4, w1, x0
	ldr	w4, [x4, 32]
	tbnz	w4, #31, .L207
	cmp	w4, w5
	bge	.L207
	add	x3, x19, 12288
	ldr	x2, [x19, 2960]
	add	x1, x3, 464
	ldr	w6, [x20, 36]
	mov	w5, 12668
	ldr	w0, [x1, 4]
	str	w6, [x1, 12]
	smaddl	x4, w4, w5, x2
	cmp	w0, 1
	ldr	w0, [x20, 40]
	str	w0, [x1, 16]
	ldr	w0, [x4, 52]
	add	x4, x4, x0, lsl 2
	ldrb	w5, [x4, 360]
	beq	.L215
	ldrb	w0, [x1, 1]
	add	x4, x19, 4096
	cbz	w0, .L211
	ldrb	w0, [x4, 136]
	cbz	w0, .L212
	ldr	x6, [x4, 168]
	mov	x2, x6
.L213:
	ldr	w7, [x4, 152]
	add	x0, x7, x2
	str	x0, [x4, 160]
	cmp	x0, x6
	str	x0, [x4, 184]
	bge	.L210
	add	x0, x7, x6
	str	x0, [x4, 160]
	str	x0, [x4, 184]
	b	.L210
	.p2align 3
.L207:
	ldr	w3, [x19, 276]
	mov	w2, 2621
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L203:
	ldr	w3, [x19, 276]
	mov	w2, 2611
	ldr	x1, .LC35
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L211:
	ldr	w0, [x19, 4248]
	ldr	x2, [x19, 4256]
	add	x0, x0, x2
	str	x0, [x19, 4280]
.L210:
	add	x4, x4, 144
	add	x2, x3, 464
	str	x0, [x4, 32]
	ldr	x1, [x2, 32]
	strb	wzr, [x2, 1]
	str	x1, [x2, 48]
	ldrb	w1, [x20, 2]
	cbnz	w1, .L216
	ldr	w1, [x4, 12]
	add	x0, x1, x0
	sub	x0, x0, x5, uxtb
	str	x0, [x2, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L216:
	ldr	w1, [x4, 12]
	add	x1, x1, x0
	asr	x1, x1, 1
	sub	x0, x1, x5, uxtb
	str	x0, [x2, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L215:
	add	x4, x19, 4096
	ldrsw	x0, [x19, 4236]
	str	x0, [x4, 160]
	str	x0, [x4, 184]
	b	.L210
	.p2align 3
.L212:
	ldp	x2, x6, [x4, 160]
	b	.L213
	.size	HEVC_Sei_Get_Dpb_Output_Time, .-HEVC_Sei_Get_Dpb_Output_Time
	.align	3
.LC35:
	.xword	.LC34
	.align	3
.LC37:
	.xword	.LC36
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Get_Last_IDR_Frame_Info
	.type	HEVC_Get_Last_IDR_Frame_Info, %function
HEVC_Get_Last_IDR_Frame_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sub	w0, w20, #19
	cmp	w0, 1
	bls	.L224
.L218:
	sub	w20, w20, #6
	cmp	w20, 3
	bls	.L217
	ldr	x0, [x19, 4280]
	str	x0, [x19, 4264]
.L217:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L224:
	ldr	x0, [x19, 3040]
	ldr	x0, [x0, 64]
	cmn	x0, #1
	beq	.L219
	ldr	x1, [x19, 12784]
	str	x0, [x19, 12776]
	str	x1, [x19, 12792]
	str	x1, [x19, 12800]
.L219:
	add	x0, x19, 12288
	mov	w1, 1
	strb	w1, [x0, 464]
	b	.L218
	.size	HEVC_Get_Last_IDR_Frame_Info, .-HEVC_Get_Last_IDR_Frame_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Get_Frame_Pts
	.type	HEVC_Sei_Get_Frame_Pts, %function
HEVC_Sei_Get_Frame_Pts:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w4, [x19, 12764]
	ldr	w5, [x19, 12768]
	ldr	x6, [x19, 12776]
	ldr	x3, [x19, 12784]
	ldr	x7, [x19, 12792]
	cbz	w4, .L228
	mov	w1, w4
	mov	w2, w5
	b	.L227
	.p2align 3
.L229:
	mov	w1, w0
.L227:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L229
.L226:
	udiv	w4, w4, w1
	sub	x0, x3, x7
	lsl	w2, w0, 6
	sub	w2, w2, w0
	lsl	w2, w2, 1
	sub	w0, w2, w0
	lsl	w0, w0, 3
	udiv	w1, w5, w1
	mul	w0, w0, w4
	udiv	w1, w0, w1
	add	x1, x1, x6
	str	x1, [x19, 5512]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L228:
	mov	w1, w5
	b	.L226
	.size	HEVC_Sei_Get_Frame_Pts, .-HEVC_Sei_Get_Frame_Pts
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitSigLastScan
	.type	HEVC_InitSigLastScan, %function
HEVC_InitSigLastScan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w5
	mov	x20, x4
	bl	_mcount
	cmp	w21, 15
	bgt	.L231
	cmp	w21, 8
	mul	w10, w21, w21
	beq	.L266
	mov	x8, x20
	cbz	w10, .L231
.L237:
	mov	w7, 1
	mov	w1, 0
	mov	w9, 0
	sub	w7, w7, w21
.L241:
	cmp	w21, w9
	mov	w0, w9
	mov	w2, 0
	bgt	.L243
	.p2align 2
.L257:
	sub	w0, w0, #1
	add	w2, w2, 1
	cmp	w21, w0
	ble	.L257
.L243:
	cmp	w0, wzr
	ccmp	w21, w2, 4, ge
	ble	.L239
	madd	w3, w21, w0, w2
	sub	w2, w2, w1
	.p2align 2
.L240:
	str	w3, [x8, w1, uxtw 2]
	sub	w0, w0, #1
	add	w1, w1, 1
	cmp	w0, wzr
	add	w6, w2, w1
	add	w3, w3, w7
	ccmp	w21, w6, 4, ge
	bgt	.L240
.L239:
	cmp	w10, w1
	add	w9, w9, 1
	bhi	.L241
.L231:
	cmp	w21, 4
	ble	.L230
	asr	w14, w21, 2
	add	x0, x19, x14, uxtw
	mul	w16, w14, w14
	ldrsb	w15, [x0, 15]
	add	w15, w15, 1
	cbz	w16, .L230
.L235:
	mov	w9, 1
	ldr	x17, .LC38
	add	x13, x19, 376
	mov	w12, 0
	sbfiz	x15, x15, 14, 32
	sub	w9, w9, w21
.L252:
	add	x0, x15, x12, uxtw
	ldr	x1, [x17]
	cmp	w21, 32
	ldr	w3, [x1, x0, lsl 2]
	beq	.L267
.L245:
	udiv	w2, w3, w14
	lsl	w8, w12, 4
	mov	w10, 0
	mov	w0, 0
	mov	w7, 0
	mov	w1, 0
	madd	w3, w2, w21, w3
	msub	w2, w2, w14, w3
	lsl	w11, w2, 2
	.p2align 2
.L246:
	cmp	w1, wzr
	ccmp	w7, 3, 0, ge
	bgt	.L247
	madd	w2, w21, w1, w7
	sub	w7, w7, w0
	add	w2, w2, w11
	.p2align 2
.L248:
	add	w6, w8, w0
	sub	w1, w1, #1
	add	w0, w0, 1
	cmp	w1, wzr
	add	w3, w7, w0
	str	w2, [x20, w6, uxtw 2]
	ccmp	w3, 3, 0, ge
	add	w2, w2, w9
	ble	.L248
.L247:
	cmp	w0, 15
	add	w10, w10, 1
	bhi	.L249
	cmp	w10, 3
	ble	.L268
	sub	w7, w10, #3
	mov	w1, 3
	b	.L246
.L249:
	add	w12, w12, 1
	add	x13, x13, 4
	cmp	w12, w16
	bne	.L252
.L230:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L267:
	ldr	w3, [x13]
	b	.L245
.L266:
	add	x8, x19, 376
	cbnz	w10, .L237
	ldrsb	w15, [x19, 17]
	mov	w14, 2
	mov	w16, 4
	add	w15, w15, 1
	b	.L235
.L268:
	mov	w1, w10
	mov	w7, 0
	b	.L246
	.size	HEVC_InitSigLastScan, .-HEVC_InitSigLastScan
	.align	3
.LC38:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitScalingOrderTable
	.type	HEVC_InitScalingOrderTable, %function
HEVC_InitScalingOrderTable:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x21, 15
	add	x2, x21, 144
	mov	w1, -1
	.p2align 2
.L270:
	strb	w1, [x0], 1
	cmp	x2, x0
	bne	.L270
	ldr	x22, .LC41
	mov	w3, 1
	mov	w2, 2
	mov	w1, 3
	mov	w0, 4
	strb	wzr, [x21, 19]
	strb	w3, [x21, 23]
	mov	w20, 2
	strb	w2, [x21, 31]
	mov	w19, 0
	strb	w1, [x21, 47]
	strb	w0, [x21, 79]
	.p2align 2
.L271:
	ldr	x4, [x22]
	sbfiz	x0, x19, 16, 32
	mov	w7, w19
	mov	w6, w20
	mov	w5, w20
	add	x4, x4, x0
	mov	x3, 0
	mov	x2, 0
	mov	x1, 0
	mov	x0, x21
	add	w19, w19, 1
	lsl	w20, w20, 1
	bl	HEVC_InitSigLastScan
	cmp	w19, 7
	bne	.L271
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_InitScalingOrderTable, .-HEVC_InitScalingOrderTable
	.align	3
.LC41:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetDar
	.type	HEVC_GetDar, %function
HEVC_GetDar:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w24, w2
	mov	w22, w3
	mov	w23, w4
	bl	_mcount
	cmp	w19, wzr
	ble	.L284
	mov	w0, 255
	cmp	w19, 16
	ccmp	w19, w0, 4, gt
	mov	w21, 0
	cset	w1, ne
	cbnz	w1, .L275
	cmp	w20, wzr
	ccmp	w24, wzr, 4, ne
	ccmp	w19, w0, 0, eq
	beq	.L275
	cmp	w19, 1
	beq	.L301
	cmp	w19, 255
	beq	.L277
	ldr	x0, .LC42
	sbfiz	x19, x19, 3, 32
	add	x0, x0, 136
	add	x1, x0, x19
	ldr	w20, [x0, x19]
	ldr	w24, [x1, 4]
.L277:
	lsl	w4, w20, 10
	lsl	w22, w22, 10
	sdiv	w2, w4, w24
	sdiv	w4, w22, w23
	mul	w4, w2, w4
	cmp	w4, wzr
	add	w0, w4, 1023
	csel	w4, w0, w4, lt
	asr	w4, w4, 10
	subs	w1, w4, #2406
	bmi	.L302
.L278:
	subs	w0, w4, #2263
	bmi	.L303
	cmp	w1, w0
	mov	w21, 4
	bge	.L282
.L275:
	ldr	x1, .LC44
	mov	w2, w21
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L303:
	mov	w0, 2263
	mov	w21, 4
	sub	w0, w0, w4
	cmp	w1, w0
	blt	.L275
.L282:
	subs	w1, w4, #1820
	bmi	.L304
	cmp	w0, w1
	mov	w21, 3
	blt	.L275
.L283:
	subs	w0, w4, #1365
	bmi	.L305
.L281:
	mov	w21, 2
	cmp	w1, w0
	csinc	w21, w21, wzr, lt
	b	.L275
	.p2align 3
.L284:
	mov	w21, 0
	b	.L275
	.p2align 3
.L301:
	mov	w1, 7680
	mov	w0, 4320
	cmp	w22, w1
	mov	w21, 2
	ccmp	w23, w0, 0, eq
	cset	w0, eq
	cbnz	w0, .L275
	mov	w0, 2160
	cmp	w22, 3840
	ccmp	w23, w0, 0, eq
	beq	.L275
	sub	w0, w23, #1080
	mov	w1, 1920
	and	w0, w0, -9
	cmp	w0, wzr
	ccmp	w22, w1, 0, eq
	beq	.L275
	mov	w0, 720
	cmp	w22, 1280
	ccmp	w23, w0, 0, eq
	beq	.L275
	mov	w0, 480
	cmp	w22, 640
	ccmp	w23, w0, 0, eq
	mov	w21, 5
	cset	w0, eq
	cmp	w0, wzr
	csinc	w21, w21, wzr, eq
	b	.L275
	.p2align 3
.L302:
	mov	w1, 2406
	sub	w1, w1, w4
	b	.L278
	.p2align 3
.L304:
	mov	w1, 1820
	mov	w21, 3
	sub	w1, w1, w4
	cmp	w0, w1
	blt	.L275
	b	.L283
.L305:
	mov	w0, 1365
	sub	w0, w0, w4
	b	.L281
	.size	HEVC_GetDar, .-HEVC_GetDar
	.align	3
.LC42:
	.xword	.LANCHOR0
	.align	3
.LC44:
	.xword	.LC43
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintNaluArraySlot
	.type	HEVC_PrintNaluArraySlot, %function
HEVC_PrintNaluArraySlot:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x24, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC47
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, .LC49
	ldr	w0, [x24, 168]
	cmn	w0, #1
	beq	.L310
	mov	w20, 52429
	ldr	x22, .LC53
	mov	w19, 0
	mov	w21, 104
	movk	w20, 0xcccc, lsl 16
	b	.L309
	.p2align 3
.L308:
	ldr	w0, [x24, 168]
	add	w0, w0, 1
	cmp	w0, w19
	bls	.L310
.L309:
	umull	x0, w19, w21
	ldr	x4, [x24, 3032]
	mov	w2, w19
	mov	x1, x22
	add	x4, x4, x0
	mov	w0, 1
	mov	x3, x4
	ldr	w4, [x4, 32]
	bl	dprint_vfmw
	umull	x0, w19, w20
	lsr	x0, x0, 32
	lsr	w0, w0, 3
	lsl	w1, w0, 3
	add	w0, w1, w0, lsl 1
	cmp	w19, w0
	add	w19, w19, 1
	bne	.L308
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x24, 168]
	add	w0, w0, 1
	cmp	w0, w19
	bhi	.L309
.L310:
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC51
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	HEVC_PrintNaluArraySlot, .-HEVC_PrintNaluArraySlot
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.align	3
.LC51:
	.xword	.LC50
	.align	3
.LC53:
	.xword	.LC52
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintCurrSlicelistX
	.type	HEVC_PrintCurrSlicelistX, %function
HEVC_PrintCurrSlicelistX:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC55
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC57
	mov	w0, 1
	ldr	w2, [x19, 5636]
	bl	dprint_vfmw
	ldr	w0, [x19, 5636]
	cbz	w0, .L321
	ldr	x24, .LC61
	mov	w20, 0
	ldr	x22, .LC66
	ldr	x23, .LC63
	ldr	x25, .LC65
	.p2align 2
.L320:
	add	x21, x19, x20, uxtw 3
	mov	w2, w20
	mov	x1, x24
	mov	w0, 1
	add	w20, w20, w0
	ldr	x3, [x21, 3064]
	bl	dprint_vfmw
	ldr	x2, [x21, 3064]
	mov	x1, x23
	mov	w0, 1
	cbz	x2, .L318
	ldr	x2, [x2, 24]
	bl	dprint_vfmw
	ldr	x0, [x21, 3064]
	ldr	x0, [x0, 24]
	cbz	x0, .L318
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetLogicFs
	mov	x2, x0
	mov	x1, x25
	mov	w0, 1
	bl	dprint_vfmw
.L318:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 5636]
	cmp	w0, w20
	bhi	.L320
.L321:
	ldr	x1, .LC59
	mov	w0, 1
	ldr	w2, [x19, 5640]
	bl	dprint_vfmw
	ldr	w0, [x19, 5640]
	cbz	w0, .L316
	ldr	x22, .LC66
	mov	w20, 0
	ldr	x24, .LC70
	ldr	x23, .LC63
	ldr	x25, .LC65
	.p2align 2
.L325:
	add	x21, x19, x20, uxtw 3
	mov	w2, w20
	mov	x1, x24
	mov	w0, 1
	add	w20, w20, w0
	ldr	x3, [x21, 3200]
	bl	dprint_vfmw
	ldr	x2, [x21, 3200]
	mov	x1, x23
	mov	w0, 1
	cbz	x2, .L323
	ldr	x2, [x2, 24]
	bl	dprint_vfmw
	ldr	x0, [x21, 3200]
	ldr	x0, [x0, 24]
	cbz	x0, .L323
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetLogicFs
	mov	x2, x0
	mov	x1, x25
	mov	w0, 1
	bl	dprint_vfmw
.L323:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 5640]
	cmp	w0, w20
	bhi	.L325
.L316:
	ldr	x1, .LC68
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_PrintCurrSlicelistX, .-HEVC_PrintCurrSlicelistX
	.align	3
.LC55:
	.xword	.LC54
	.align	3
.LC57:
	.xword	.LC56
	.align	3
.LC59:
	.xword	.LC58
	.align	3
.LC61:
	.xword	.LC60
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC66:
	.xword	.LC48
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC70:
	.xword	.LC69
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintFrameStoreState
	.type	HEVC_PrintFrameStoreState, %function
HEVC_PrintFrameStoreState:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC74
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x22, 180]
	cbz	w0, .L339
	ldr	x27, .LC78
	mov	w21, 0
	ldr	x23, .LC80
	mov	w25, 728
	ldr	x26, .LC81
	mov	x24, 15384
	.p2align 2
.L338:
	uxtw	x5, w21
	mov	w2, w21
	lsl	x4, x5, 3
	mov	x1, x27
	sub	x4, x4, x5
	mov	w0, 1
	lsl	x3, x4, 1
	mov	w19, 0
	sub	x4, x3, x5
	lsl	x3, x4, 3
	sub	x3, x3, x4
	lsl	x3, x3, 3
	add	x4, x22, x3
	add	x3, x3, 12288
	add	x5, x4, 12288
	add	x3, x3, 2464
	umaddl	x20, w21, w25, x24
	ldr	w4, [x4, 14800]
	add	x3, x22, x3
	ldrb	w6, [x5, 2466]
	add	x20, x22, x20
	ldrb	w5, [x5, 2465]
	bl	dprint_vfmw
.L337:
	ldr	x3, [x20], 8
	mov	w2, w19
	mov	w0, 1
	mov	x1, x23
	add	w19, w19, w0
	bl	dprint_vfmw
	cmp	w19, 4
	bne	.L337
	mov	w0, 1
	mov	x1, x26
	add	w21, w21, w0
	bl	dprint_vfmw
	ldr	w0, [x22, 180]
	cmp	w0, w21
	bhi	.L338
.L339:
	ldr	x1, .LC76
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	HEVC_PrintFrameStoreState, .-HEVC_PrintFrameStoreState
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC78:
	.xword	.LC77
	.align	3
.LC80:
	.xword	.LC79
	.align	3
.LC81:
	.xword	.LC48
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintAPCState
	.type	HEVC_PrintAPCState, %function
HEVC_PrintAPCState:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 12288
	mov	w23, 0
	bl	_mcount
	add	x22, x19, 1908
	ldr	x1, .LC83
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x24, .LC85
	ldr	x21, .LC87
.L345:
	ldp	w4, w3, [x22, -8]
	mov	w2, w23
	mov	x1, x24
	mov	w0, 1
	mov	x20, x22
	mov	w19, 0
	bl	dprint_vfmw
	.p2align 2
.L344:
	ldr	w4, [x20, 64]
	mov	w2, w19
	ldr	w5, [x20, 128]
	mov	w0, 1
	ldr	w3, [x20], 4
	mov	x1, x21
	add	w19, w19, w0
	bl	dprint_vfmw
	cmp	w19, 16
	bne	.L344
	add	w23, w23, 1
	add	x22, x22, 280
	cmp	w23, 2
	bne	.L345
	ldr	x1, .LC89
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	HEVC_PrintAPCState, .-HEVC_PrintAPCState
	.align	3
.LC83:
	.xword	.LC82
	.align	3
.LC85:
	.xword	.LC84
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintDPBState
	.type	HEVC_PrintDPBState, %function
HEVC_PrintDPBState:
	sub	sp, sp, #176
	stp	x29, x30, [sp, 64]
	add	x29, sp, 64
	stp	x19, x20, [sp, 80]
	stp	x21, x22, [sp, 96]
	stp	x23, x24, [sp, 112]
	stp	x25, x26, [sp, 128]
	stp	x27, x28, [sp, 144]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x1, .LC91
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC93
	mov	w0, 1
	ldr	w2, [x19, 3376]
	ldr	w3, [x19, 3380]
	ldr	w6, [x19, 3388]
	ldr	w4, [x19, 3392]
	ldr	w5, [x19, 3396]
	bl	dprint_vfmw
	ldr	w0, [x19, 3380]
	cbz	w0, .L353
	.p2align 2
.L352:
	add	x21, x19, x20, uxtw 3
	ldr	w0, [x19, 276]
	ldr	x2, [x21, 3688]
	ldrb	w7, [x2, 1]
	ldp	w1, w28, [x2, 28]
	ldr	w6, [x2, 48]
	ldrb	w25, [x2]
	ldrb	w22, [x2, 2]
	ldr	w23, [x2, 8]
	ldr	w24, [x2, 60]
	stp	w6, w7, [x29, 104]
	bl	FSP_GetLogicFs
	mov	x26, x0
	ldr	x1, [x21, 3688]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetRef
	mov	w27, w0
	ldr	x1, [x21, 3688]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetDisplay
	ldr	x8, [x21, 3688]
	mov	w2, w20
	ldp	w6, w7, [x29, 104]
	mov	x3, x8
	mov	w5, w25
	ldr	w1, [x8, 236]
	mov	w4, w28
	str	w1, [sp, 56]
	add	w20, w20, 1
	ldr	x1, .LC96
	ldr	w8, [x8, 28]
	str	w8, [sp, 48]
	str	w0, [sp, 40]
	mov	w0, 1
	str	w22, [sp]
	str	w23, [sp, 8]
	str	w24, [sp, 16]
	str	x26, [sp, 24]
	str	w27, [sp, 32]
	bl	dprint_vfmw
	ldr	w0, [x19, 3380]
	cmp	w0, w20
	bhi	.L352
.L353:
	ldr	x24, .LC94
	mov	w0, 1
	mov	x1, x24
	bl	dprint_vfmw
	ldr	w0, [x19, 3380]
	cbz	w0, .L351
	ldr	x26, .LC100
	mov	w21, 0
	ldr	x28, .LC102
	ldr	x27, .LC104
	ldr	x25, .LC112
	b	.L360
	.p2align 3
.L364:
	mov	x2, x20
	mov	x1, x28
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x20, 20]
	mov	x1, x27
	mov	w0, 1
	bl	dprint_vfmw
	ldrsb	w2, [x20]
	mov	w0, 1
	ldr	x1, .LC106
	bl	dprint_vfmw
	ldrsb	w2, [x20, 1]
	mov	w0, 1
	ldr	x1, .LC108
	bl	dprint_vfmw
	mov	x2, x23
	mov	x1, x25
	mov	w0, 1
	cbz	x23, .L356
.L365:
	bl	dprint_vfmw
	ldr	w2, [x23, 72]
	mov	w0, 1
	ldr	x1, .LC114
	bl	dprint_vfmw
	mov	x2, x22
	mov	w0, 1
	cbz	x22, .L358
.L366:
	ldr	x1, .LC118
	bl	dprint_vfmw
	ldr	x1, .LC120
	mov	w0, 1
	ldr	w2, [x22, 72]
	bl	dprint_vfmw
	mov	w0, 1
	mov	x1, x24
	add	w21, w21, w0
	bl	dprint_vfmw
	ldr	w0, [x19, 3380]
	cmp	w0, w21
	bls	.L351
.L360:
	add	x22, x19, x21, uxtw 3
	ldr	w0, [x19, 276]
	ldr	x1, [x22, 3688]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	mov	x20, x0
	ldr	x1, [x22, 3688]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetDecPhyFs
	mov	x23, x0
	ldr	x1, [x22, 3688]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetDispPhyFs
	mov	x22, x0
	mov	w2, w21
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
	cbnz	x20, .L364
	ldr	x1, .LC110
	mov	w0, 1
	bl	dprint_vfmw
	mov	x2, x23
	mov	x1, x25
	mov	w0, 1
	cbnz	x23, .L365
	.p2align 2
.L356:
	ldr	x1, .LC116
	mov	w0, 1
	bl	dprint_vfmw
	mov	x2, x22
	mov	w0, 1
	cbnz	x22, .L366
	.p2align 2
.L358:
	ldr	x1, .LC122
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
	mov	x1, x24
	add	w21, w21, w0
	bl	dprint_vfmw
	ldr	w0, [x19, 3380]
	cmp	w0, w21
	bhi	.L360
.L351:
	ldr	x1, .LC98
	mov	w0, 1
	bl	dprint_vfmw
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	HEVC_PrintDPBState, .-HEVC_PrintDPBState
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC94:
	.xword	.LC48
	.align	3
.LC96:
	.xword	.LC95
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsSliceUnit
	.type	HEVC_IsSliceUnit, %function
HEVC_IsSliceUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 9
	mov	w0, 1
	bls	.L368
	sub	w19, w19, #16
	cmp	w19, 5
	cset	w0, ls
.L368:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsSliceUnit, .-HEVC_IsSliceUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsIUnit
	.type	HEVC_IsIUnit, %function
HEVC_IsIUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sub	w19, w19, #16
	bl	_mcount
	cmp	w19, 5
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsIUnit, .-HEVC_IsIUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNonRefPic
	.type	HEVC_IsNonRefPic, %function
HEVC_IsNonRefPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ands	w19, w19, -7
	mov	w0, 1
	beq	.L372
	cmp	w19, 8
	cset	w0, eq
.L372:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsNonRefPic, .-HEVC_IsNonRefPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsFlushUnit
	.type	HEVC_IsFlushUnit, %function
HEVC_IsFlushUnit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	sub	w19, w19, #16
	bl	_mcount
	cmp	w19, 4
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsFlushUnit, .-HEVC_IsFlushUnit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPVRFlushPic
	.type	HEVC_IsPVRFlushPic, %function
HEVC_IsPVRFlushPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4872]
	cbnz	w0, .L377
	ldr	x1, [x19, 3040]
	mov	x2, 4294967296
	ldr	x3, [x1, 696]
	cmp	x3, x2
	beq	.L380
.L376:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L377:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L380:
	ldr	w2, [x1, 704]
	cbnz	w2, .L376
	ldr	w0, [x1, 660]
	add	w0, w0, 1024
	cmp	w0, 2048
	cset	w0, hi
	b	.L376
	.size	HEVC_IsPVRFlushPic, .-HEVC_IsPVRFlushPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsEosNal
	.type	HEVC_IsEosNal, %function
HEVC_IsEosNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2944]
	mov	w1, 32
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2944]
	mov	w1, 32
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w20, w2
	ccmp	w0, w1, 0, eq
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsEosNal, .-HEVC_IsEosNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcTileInfo
	.type	HEVC_CalcTileInfo, %function
HEVC_CalcTileInfo:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	mov	x21, x3
	bl	_mcount
	ldr	x0, [x22, 3016]
	ldr	x1, [x22, 3008]
	ldp	w23, w26, [x0, 68]
	ldr	w25, [x1, 128]
	sub	w0, w23, #1
	cmp	w0, 9
	bhi	.L410
	sub	w0, w26, #1
	cmp	w0, 10
	bhi	.L411
	ldr	x24, .LC128
	mov	x2, 512
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x24, 96]
	blr	x3
	ldr	x3, [x24, 96]
	mov	x2, 80
	mov	w1, 0
	mov	x0, x20
	blr	x3
	ldr	x3, [x24, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x21
	blr	x3
	cmp	w23, wzr
	ble	.L391
	sub	w7, w25, #4
	mov	x2, x20
	mov	w1, 0
	mov	w6, 0
.L390:
	str	w1, [x2]
	lsl	w3, w1, w7
	ldr	x0, [x22, 3016]
	add	x0, x0, x6, sxtw 1
	ldrsh	w5, [x0, 172]
	add	w5, w5, w1
	lsl	w1, w5, w7
	sub	w0, w5, #1
	cmp	w3, w1
	str	w0, [x2, 4]
	bge	.L396
	cmp	w3, 255
	bhi	.L392
	uxtb	w4, w6
	b	.L394
	.p2align 3
.L395:
	cmp	w3, 255
	bhi	.L392
.L394:
	strb	w4, [x19, w3, sxtw]
	add	w3, w3, 1
	cmp	w3, w1
	blt	.L395
.L396:
	add	w6, w6, 1
	add	x2, x2, 8
	cmp	w23, w6
	mov	w1, w5
	bne	.L390
.L391:
	cmp	w26, wzr
	ble	.L388
	sub	w25, w25, #4
	mov	w0, 0
	mov	w5, 0
.L398:
	str	w0, [x21]
	lsl	w3, w0, w25
	ldr	x1, [x22, 3016]
	add	x1, x1, x5, sxtw 1
	ldrsh	w4, [x1, 212]
	add	w4, w4, w0
	lsl	w0, w4, w25
	sub	w1, w4, #1
	cmp	w3, w0
	str	w1, [x21, 4]
	bge	.L403
	cmp	w3, 255
	bhi	.L399
	uxtb	w2, w5
	add	x1, x19, 256
	b	.L401
	.p2align 3
.L402:
	cmp	w3, 255
	bhi	.L399
.L401:
	strb	w2, [x1, w3, sxtw]
	add	w3, w3, 1
	cmp	w3, w0
	blt	.L402
.L403:
	add	w5, w5, 1
	add	x21, x21, 8
	cmp	w26, w5
	mov	w0, w4
	bne	.L398
.L388:
	mov	w0, 0
	b	.L384
	.p2align 3
.L392:
	ldr	x2, .LC123
	mov	w0, 1
	ldr	x1, .LC130
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
.L384:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L399:
	ldr	x2, .LC123
	mov	w0, 1
	ldr	x1, .LC132
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L384
.L411:
	ldr	x2, .LC123
	mov	w4, 11
	ldr	x1, .LC127
	mov	w3, w26
	add	x2, x2, 272
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L384
.L410:
	ldr	x2, .LC123
	mov	w4, 10
	ldr	x1, .LC125
	mov	w3, w23
	add	x2, x2, 272
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L384
	.size	HEVC_CalcTileInfo, .-HEVC_CalcTileInfo
	.align	3
.LC123:
	.xword	.LANCHOR0
	.align	3
.LC125:
	.xword	.LC124
	.align	3
.LC127:
	.xword	.LC126
	.align	3
.LC128:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC132:
	.xword	.LC131
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_More_Data_In_Payload
	.type	HEVC_Sei_More_Data_In_Payload, %function
HEVC_Sei_More_Data_In_Payload:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	lsl	w20, w20, 3
	ldr	x1, [x19, 2944]
	mov	x0, x1
	ldp	w2, w19, [x1, 32]
	sub	w19, w2, w19
	bl	BsIsByteAligned
	cmp	w20, w19
	ccmp	w0, wzr, 4, ne
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_Sei_More_Data_In_Payload, .-HEVC_Sei_More_Data_In_Payload
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Payload_Extension_Present
	.type	HEVC_Sei_Payload_Extension_Present, %function
HEVC_Sei_Payload_Extension_Present:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	lsl	w20, w20, 3
	ldr	x3, .LC133
	mov	x2, 40
	ldr	x1, [x19, 2944]
	add	x0, x29, x2
	ldr	x3, [x3, 104]
	blr	x3
	ldp	w0, w1, [x29, 72]
	sub	w0, w0, w1
	mov	w1, 0
	cmp	w0, w20
	bcc	.L420
.L414:
	ldp	x19, x20, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L420:
	mov	w1, 1
	add	x0, x29, 40
	bl	BsShow
	mov	w1, 1
	cbz	w0, .L414
	add	x0, x29, 40
	bl	BsSkip
	ldp	w0, w19, [x29, 72]
	sub	w19, w0, w19
	b	.L415
	.p2align 3
.L416:
	bl	BsSkip
	ldp	w0, w19, [x29, 72]
	sub	w19, w0, w19
.L415:
	mov	w1, 1
	add	x0, x29, 40
	bl	BsShow
	cmp	w19, w20
	mov	w1, 1
	cset	w2, cc
	cmp	w0, wzr
	cset	w3, eq
	add	x0, x29, 40
	tst	w2, w3
	bne	.L416
	mov	w1, w2
	ldp	x19, x20, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_Sei_Payload_Extension_Present, .-HEVC_Sei_Payload_Extension_Present
	.align	3
.LC133:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Decoded_Picture_Hash
	.type	HEVC_Sei_Decoded_Picture_Hash, %function
HEVC_Sei_Decoded_Picture_Hash:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L429
	ldr	x0, [x20, 2944]
	mov	w1, 8
	mov	w21, 3
	bl	BsGet
	mov	w22, w0
.L428:
	cbnz	w22, .L423
	mov	w19, 16
	.p2align 2
.L424:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	subs	w19, w19, #1
	bne	.L424
.L425:
	subs	w21, w21, #1
	bne	.L428
.L433:
	mov	w0, 0
.L422:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L423:
	cmp	w22, 1
	beq	.L432
	cmp	w22, 2
	bne	.L425
	ldr	x0, [x20, 2944]
	mov	w1, 32
	bl	BsGet
	subs	w21, w21, #1
	bne	.L428
	b	.L433
.L432:
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	subs	w21, w21, #1
	bne	.L428
	b	.L433
.L429:
	mov	w0, -1
	b	.L422
	.size	HEVC_Sei_Decoded_Picture_Hash, .-HEVC_Sei_Decoded_Picture_Hash
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Region_Refresh_Info
	.type	HEVC_Sei_Region_Refresh_Info, %function
HEVC_Sei_Region_Refresh_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L436
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	mov	w0, 0
.L435:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L436:
	mov	w0, -1
	b	.L435
	.size	HEVC_Sei_Region_Refresh_Info, .-HEVC_Sei_Region_Refresh_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Mastering_Display_Colour_Volume
	.type	HEVC_Sei_Mastering_Display_Colour_Volume, %function
HEVC_Sei_Mastering_Display_Colour_Volume:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L439
	mov	w0, 1
	mov	x1, x19
	strb	w0, [x19]
	mov	x0, x20
	bl	HEVC_Sei_Mastering_Display_Colour_Volume.part.24
.L438:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L439:
	mov	w0, -1
	b	.L438
	.size	HEVC_Sei_Mastering_Display_Colour_Volume, .-HEVC_Sei_Mastering_Display_Colour_Volume
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Content_Light_Level_Information
	.type	HEVC_Sei_Content_Light_Level_Information, %function
HEVC_Sei_Content_Light_Level_Information:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L442
	mov	w0, 1
	strb	w0, [x19]
	mov	w1, 16
	ldr	x0, [x20, 2944]
	bl	BsGet
	strh	w0, [x19, 2]
	mov	w1, 16
	ldr	x0, [x20, 2944]
	bl	BsGet
	strh	w0, [x19, 4]
	mov	w1, 0
.L441:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L442:
	mov	w1, -1
	b	.L441
	.size	HEVC_Sei_Content_Light_Level_Information, .-HEVC_Sei_Content_Light_Level_Information
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_HLGHDR_Comapitibility_Info
	.type	HEVC_Sei_HLGHDR_Comapitibility_Info, %function
HEVC_Sei_HLGHDR_Comapitibility_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L445
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x19]
	mov	w1, 0
.L444:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L445:
	mov	w1, -1
	b	.L444
	.size	HEVC_Sei_HLGHDR_Comapitibility_Info, .-HEVC_Sei_HLGHDR_Comapitibility_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.type	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, %function
HEVC_Sei_Temporal_Sub_Layer_Zero_Index:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L448
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L447:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L448:
	mov	w0, -1
	b	.L447
	.size	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, .-HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Display_Orientation
	.type	HEVC_Sei_Display_Orientation, %function
HEVC_Sei_Display_Orientation:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L452
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L453
.L451:
	ldr	x0, [x19, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L450:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L453:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	b	.L451
	.p2align 3
.L452:
	mov	w0, -1
	b	.L450
	.size	HEVC_Sei_Display_Orientation, .-HEVC_Sei_Display_Orientation
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_TSI
	.type	HEVC_Sei_TSI, %function
HEVC_Sei_TSI:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L456
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	strb	w0, [x19, 1]
	mov	w1, 4
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x19]
.L455:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L456:
	mov	w0, -1
	b	.L455
	.size	HEVC_Sei_TSI, .-HEVC_Sei_TSI
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_User_Data_Unregistered
	.type	HEVC_Sei_User_Data_Unregistered, %function
HEVC_Sei_User_Data_Unregistered:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w2
	mov	w19, 16
	bl	_mcount
	cmp	w21, 15
	bls	.L468
	.p2align 2
.L465:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	subs	w19, w19, #1
	bne	.L465
	subs	w21, w21, #16
	mov	w19, 0
	beq	.L462
	.p2align 2
.L464:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w21, w19
	bne	.L464
.L462:
	mov	w0, 0
.L459:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L468:
	ldr	x1, .LC135
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L459
	.size	HEVC_Sei_User_Data_Unregistered, .-HEVC_Sei_User_Data_Unregistered
	.align	3
.LC135:
	.xword	.LC134
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsRefListWrong
	.type	HEVC_IsRefListWrong, %function
HEVC_IsRefListWrong:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 5636]
	cbnz	w3, .L510
.L470:
	mov	w0, 0
.L508:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L510:
	ldr	x0, [x19, 3064]
	cbz	x0, .L492
	ldr	x0, [x0, 24]
	mov	w20, 0
	cbnz	x0, .L476
	b	.L472
	.p2align 3
.L512:
	ldr	x1, [x0, 32]
	cbz	x1, .L477
	ldr	w3, [x19, 5636]
	add	w20, w20, 1
	cmp	w3, w20
	add	x0, x19, x20, sxtw 3
	bls	.L511
	ldr	x0, [x0, 3064]
	cbz	x0, .L471
	ldr	x0, [x0, 24]
	cbz	x0, .L472
.L476:
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetLogicFs
	cbnz	x0, .L512
.L477:
	add	x19, x19, x20, sxtw 3
	ldr	x1, .LC141
	mov	x4, x0
	mov	w2, w20
	mov	w0, 1
	ldr	x3, [x19, 3064]
	ldr	x3, [x3, 24]
	bl	dprint_vfmw
	mov	w0, -1
.L516:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L511:
	cbz	w3, .L470
	ldr	w0, [x19, 5640]
	cbz	w0, .L470
	ldr	x0, [x19, 3200]
	cbz	x0, .L494
	ldr	x0, [x0, 24]
	mov	w20, 0
	cbnz	x0, .L487
	b	.L484
	.p2align 3
.L515:
	ldr	x1, [x0, 32]
	cbz	x1, .L488
	ldr	w0, [x19, 5640]
	add	w20, w20, 1
	cmp	w0, w20
	add	x1, x19, x20, sxtw 3
	bls	.L470
	ldr	x0, [x1, 3200]
	cbz	x0, .L513
	ldr	x0, [x0, 24]
	cbz	x0, .L514
.L487:
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetLogicFs
	cbnz	x0, .L515
.L488:
	ldr	x1, .LC147
	mov	x3, x0
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L508
.L492:
	mov	w20, 0
	.p2align 2
.L471:
	ldr	x1, .LC137
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L516
	.p2align 3
.L472:
	ldr	x1, .LC139
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L516
.L514:
	ldr	w3, [x19, 5636]
.L484:
	ldr	x1, .LC145
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L508
.L513:
	ldr	w3, [x19, 5636]
.L483:
	ldr	x1, .LC143
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L508
.L494:
	mov	w20, 0
	b	.L483
	.size	HEVC_IsRefListWrong, .-HEVC_IsRefListWrong
	.align	3
.LC137:
	.xword	.LC136
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC141:
	.xword	.LC140
	.align	3
.LC143:
	.xword	.LC142
	.align	3
.LC145:
	.xword	.LC144
	.align	3
.LC147:
	.xword	.LC146
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetUnRefPicWithMinPoc
	.type	HEVC_GetUnRefPicWithMinPoc, %function
HEVC_GetUnRefPicWithMinPoc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, -1
	bl	_mcount
	str	w21, [x20]
	ldr	w3, [x19, 3380]
	cmp	w3, 16
	bhi	.L518
	mov	w4, 2147483647
	mov	w0, 0
	cbz	w3, .L523
	.p2align 2
.L526:
	add	x2, x19, x0, uxtw 3
	ldr	x2, [x2, 3688]
	ldr	w5, [x2, 8]
	cmp	w5, w4
	bge	.L521
	ldr	w2, [x2]
	tst	w2, 16776960
	bne	.L521
	str	w0, [x20]
	mov	w4, w5
	ldr	w3, [x19, 3380]
.L521:
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L526
	ldr	w3, [x20]
	cmn	w3, #1
	beq	.L523
	ldr	x2, .LC148
	mov	w0, 1
	ldr	x1, .LC154
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, 0
.L520:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L523:
	ldr	x2, .LC148
	mov	w0, 1
	ldr	x1, .LC150
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, -1
	b	.L520
.L518:
	ldr	x2, .LC148
	mov	w0, 1
	ldr	x1, .LC152
	add	x2, x2, 296
	bl	dprint_vfmw
	mov	w0, w21
	b	.L520
	.size	HEVC_GetUnRefPicWithMinPoc, .-HEVC_GetUnRefPicWithMinPoc
	.align	3
.LC148:
	.xword	.LANCHOR0
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC152:
	.xword	.LC151
	.align	3
.LC154:
	.xword	.LC153
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IncreaseDPBSize
	.type	HEVC_IncreaseDPBSize, %function
HEVC_IncreaseDPBSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x20, 3376]
	cmp	w3, 16
	bhi	.L533
	ldr	w0, [x20, 276]
	bl	FSP_GetTotalValidFsNum
	mov	w19, w0
	ldr	w2, [x20, 276]
	ldr	w0, [x20, 4876]
	ldr	w1, [x20, 4880]
	bl	FSP_GetOccupiedNum
	subs	w0, w19, w0
	csel	w0, w0, wzr, pl
	ldr	x2, .LC155
	cmp	w0, wzr
	ble	.L532
	ldr	w3, [x20, 3376]
	add	w3, w3, 1
	cmp	w3, w0
	bhi	.L532
	ldr	x1, .LC159
	add	x2, x2, 328
	mov	w0, 13
	str	w3, [x20, 3376]
	bl	dprint_vfmw
	mov	w0, 0
.L531:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L532:
	ldr	x1, .LC161
	mov	w3, w0
	add	x2, x2, 328
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L531
	.p2align 3
.L533:
	ldr	x2, .LC155
	mov	w4, 17
	ldr	x1, .LC157
	mov	w0, 1
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w1, 17
	mov	w0, -1
	str	w1, [x20, 3376]
	b	.L531
	.size	HEVC_IncreaseDPBSize, .-HEVC_IncreaseDPBSize
	.align	3
.LC155:
	.xword	.LANCHOR0
	.align	3
.LC157:
	.xword	.LC156
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC161:
	.xword	.LC160
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PicTypeStatistic
	.type	HEVC_PicTypeStatistic, %function
HEVC_PicTypeStatistic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5596]
	sub	w1, w0, #16
	cmp	w1, 5
	bhi	.L535
	str	w0, [x19, 4860]
	str	wzr, [x19, 4872]
.L534:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L535:
	ldr	w0, [x19, 4860]
	sub	w0, w0, #16
	cmp	w0, 5
	bls	.L534
	ldr	w0, [x19, 5588]
	cmp	w0, 1
	beq	.L537
	cmp	w0, 2
	beq	.L538
	cbnz	w0, .L534
	mov	w0, 2
	str	w0, [x19, 4872]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L537:
	ldr	w1, [x19, 4872]
	cmp	w1, 2
	beq	.L534
	str	w0, [x19, 4872]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L538:
	ldr	w0, [x19, 4872]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L534
	str	wzr, [x19, 4872]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_PicTypeStatistic, .-HEVC_PicTypeStatistic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsReferenceNalu
	.type	HEVC_IsReferenceNalu, %function
HEVC_IsReferenceNalu:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 5596]
	cmp	w1, 15
	bhi	.L544
	mov	w0, 1
	tbnz	x1, 0, .L545
.L544:
	sub	w1, w1, #16
	cmp	w1, 7
	cset	w0, ls
.L545:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsReferenceNalu, .-HEVC_IsReferenceNalu
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_4x4
	.type	HEVC_WriteQmatrix_4x4, %function
HEVC_WriteQmatrix_4x4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	ubfiz	x20, x20, 6, 32
	bl	_mcount
	add	x1, x21, x20
	ldrb	w4, [x1, 636]
	ldr	w3, [x1, 644]
	ldr	w2, [x1, 640]
	ldrb	w0, [x1, 632]
	ubfiz	w2, w2, 8, 8
	orr	w2, w2, w4, lsl 16
	orr	w0, w0, w3, lsl 24
	orr	w0, w2, w0
	str	w0, [x19]
	ldrb	w4, [x1, 645]
	ldrb	w2, [x1, 637]
	ldr	w3, [x1, 640]
	ldrb	w0, [x1, 633]
	lsl	w2, w2, 16
	and	w3, w3, 65280
	orr	w2, w2, w4, lsl 24
	orr	w0, w0, w3
	orr	w0, w2, w0
	str	w0, [x19, 4]
	ldrb	w4, [x1, 646]
	ldrb	w2, [x1, 642]
	ldr	w3, [x1, 636]
	ldrb	w0, [x1, 634]
	lsl	w2, w2, 8
	and	w3, w3, 16711680
	orr	w2, w2, w4, lsl 24
	orr	w0, w0, w3
	orr	w0, w2, w0
	str	w0, [x19, 8]
	ldrb	w3, [x1, 639]
	ldrb	w2, [x1, 643]
	ldr	w0, [x1, 644]
	ldrb	w1, [x1, 635]
	lsl	w2, w2, 8
	and	w0, w0, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 12]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_4x4, .-HEVC_WriteQmatrix_4x4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_32x32
	.type	HEVC_WriteQmatrix_32x32, %function
HEVC_WriteQmatrix_32x32:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 18
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1800]
	ldr	w3, [x0, 1808]
	ldr	w4, [x0, 1792]
	ldrb	w2, [x1, 632]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1832]
	ldr	w3, [x0, 1840]
	ldr	w4, [x0, 1824]
	ldrb	w2, [x0, 1816]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1809]
	ldrb	w4, [x0, 1801]
	ldr	w3, [x0, 1792]
	ldrb	w2, [x1, 633]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1841]
	ldrb	w4, [x0, 1833]
	ldr	w3, [x0, 1824]
	ldrb	w2, [x0, 1817]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1810]
	ldrb	w4, [x0, 1794]
	ldr	w3, [x0, 1800]
	ldrb	w2, [x1, 634]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1842]
	ldrb	w4, [x0, 1826]
	ldr	w3, [x0, 1832]
	ldrb	w2, [x0, 1818]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1803]
	ldrb	w3, [x0, 1795]
	ldr	w5, [x0, 1808]
	ldrb	w2, [x1, 635]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1835]
	ldrb	w3, [x0, 1827]
	ldr	w1, [x0, 1840]
	ldrb	w2, [x0, 1819]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1804]
	ldr	w2, [x0, 1812]
	ldr	w3, [x0, 1796]
	ldrb	w1, [x0, 1788]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1836]
	ldr	w2, [x0, 1844]
	ldr	w3, [x0, 1828]
	ldrb	w1, [x0, 1820]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1813]
	ldrb	w3, [x0, 1805]
	ldr	w2, [x0, 1796]
	ldrb	w1, [x0, 1789]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1845]
	ldrb	w3, [x0, 1837]
	ldr	w2, [x0, 1828]
	ldrb	w1, [x0, 1821]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1814]
	ldrb	w3, [x0, 1798]
	ldr	w2, [x0, 1804]
	ldrb	w1, [x0, 1790]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1846]
	ldrb	w3, [x0, 1830]
	ldr	w2, [x0, 1836]
	ldrb	w1, [x0, 1822]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1807]
	ldrb	w3, [x0, 1799]
	ldr	w1, [x0, 1812]
	ldrb	w2, [x0, 1791]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1839]
	ldrb	w2, [x0, 1831]
	ldr	w4, [x0, 1844]
	ldrb	w1, [x0, 1823]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_32x32, .-HEVC_WriteQmatrix_32x32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_8x8
	.type	HEVC_WriteQmatrix_8x8, %function
HEVC_WriteQmatrix_8x8:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 6
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1048]
	ldr	w3, [x0, 1064]
	ldr	w4, [x0, 1032]
	ldrb	w2, [x1, 632]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1056]
	ldr	w3, [x0, 1072]
	ldr	w4, [x0, 1040]
	ldrb	w2, [x0, 1024]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1065]
	ldrb	w4, [x0, 1049]
	ldr	w3, [x0, 1032]
	ldrb	w2, [x1, 633]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1073]
	ldrb	w4, [x0, 1057]
	ldr	w3, [x0, 1040]
	ldrb	w2, [x0, 1025]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1066]
	ldrb	w4, [x0, 1034]
	ldr	w3, [x0, 1048]
	ldrb	w2, [x1, 634]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1074]
	ldrb	w4, [x0, 1042]
	ldr	w3, [x0, 1056]
	ldrb	w2, [x0, 1026]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1051]
	ldrb	w3, [x0, 1035]
	ldr	w5, [x0, 1064]
	ldrb	w2, [x1, 635]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1059]
	ldrb	w3, [x0, 1043]
	ldr	w1, [x0, 1072]
	ldrb	w2, [x0, 1027]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1052]
	ldr	w2, [x0, 1068]
	ldr	w3, [x0, 1036]
	ldrb	w1, [x0, 1020]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1060]
	ldr	w2, [x0, 1076]
	ldr	w3, [x0, 1044]
	ldrb	w1, [x0, 1028]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1069]
	ldrb	w3, [x0, 1053]
	ldr	w2, [x0, 1036]
	ldrb	w1, [x0, 1021]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1077]
	ldrb	w3, [x0, 1061]
	ldr	w2, [x0, 1044]
	ldrb	w1, [x0, 1029]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1070]
	ldrb	w3, [x0, 1038]
	ldr	w2, [x0, 1052]
	ldrb	w1, [x0, 1022]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1078]
	ldrb	w3, [x0, 1046]
	ldr	w2, [x0, 1060]
	ldrb	w1, [x0, 1030]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1055]
	ldrb	w3, [x0, 1039]
	ldr	w1, [x0, 1068]
	ldrb	w2, [x0, 1023]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1063]
	ldrb	w2, [x0, 1047]
	ldr	w4, [x0, 1076]
	ldrb	w1, [x0, 1031]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_8x8, .-HEVC_WriteQmatrix_8x8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteQmatrix_16x16
	.type	HEVC_WriteQmatrix_16x16, %function
HEVC_WriteQmatrix_16x16:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	uxtw	x0, w20
	add	x1, x0, 12
	add	x0, x21, x0, lsl 6
	add	x1, x21, x1, lsl 6
	ldrb	w5, [x0, 1416]
	ldr	w3, [x0, 1424]
	ldr	w4, [x0, 1408]
	ldrb	w2, [x1, 632]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19]
	ldrb	w5, [x0, 1448]
	ldr	w3, [x0, 1456]
	ldr	w4, [x0, 1440]
	ldrb	w2, [x0, 1432]
	ubfiz	w4, w4, 8, 8
	orr	w4, w4, w5, lsl 16
	orr	w2, w2, w3, lsl 24
	orr	w2, w4, w2
	str	w2, [x19, 4]
	ldrb	w5, [x0, 1425]
	ldrb	w4, [x0, 1417]
	ldr	w3, [x0, 1408]
	ldrb	w2, [x1, 633]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 8]
	ldrb	w5, [x0, 1457]
	ldrb	w4, [x0, 1449]
	ldr	w3, [x0, 1440]
	ldrb	w2, [x0, 1433]
	lsl	w4, w4, 16
	and	w3, w3, 65280
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 12]
	ldrb	w5, [x0, 1426]
	ldrb	w4, [x0, 1410]
	ldr	w3, [x0, 1416]
	ldrb	w2, [x1, 634]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 16]
	ldrb	w5, [x0, 1458]
	ldrb	w4, [x0, 1442]
	ldr	w3, [x0, 1448]
	ldrb	w2, [x0, 1434]
	lsl	w4, w4, 8
	and	w3, w3, 16711680
	orr	w4, w4, w5, lsl 24
	orr	w2, w2, w3
	orr	w2, w4, w2
	str	w2, [x19, 20]
	ldrb	w4, [x0, 1419]
	ldrb	w3, [x0, 1411]
	ldr	w5, [x0, 1424]
	ldrb	w2, [x1, 635]
	lsl	w3, w3, 8
	and	w1, w5, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 24]
	ldrb	w4, [x0, 1451]
	ldrb	w3, [x0, 1443]
	ldr	w1, [x0, 1456]
	ldrb	w2, [x0, 1435]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 28]
	ldrb	w4, [x0, 1420]
	ldr	w2, [x0, 1428]
	ldr	w3, [x0, 1412]
	ldrb	w1, [x0, 1404]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 32]
	ldrb	w4, [x0, 1452]
	ldr	w2, [x0, 1460]
	ldr	w3, [x0, 1444]
	ldrb	w1, [x0, 1436]
	ubfiz	w3, w3, 8, 8
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2, lsl 24
	orr	w1, w3, w1
	str	w1, [x19, 36]
	ldrb	w4, [x0, 1429]
	ldrb	w3, [x0, 1421]
	ldr	w2, [x0, 1412]
	ldrb	w1, [x0, 1405]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 40]
	ldrb	w4, [x0, 1461]
	ldrb	w3, [x0, 1453]
	ldr	w2, [x0, 1444]
	ldrb	w1, [x0, 1437]
	lsl	w3, w3, 16
	and	w2, w2, 65280
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 44]
	ldrb	w4, [x0, 1430]
	ldrb	w3, [x0, 1414]
	ldr	w2, [x0, 1420]
	ldrb	w1, [x0, 1406]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 48]
	ldrb	w4, [x0, 1462]
	ldrb	w3, [x0, 1446]
	ldr	w2, [x0, 1452]
	ldrb	w1, [x0, 1438]
	lsl	w3, w3, 8
	and	w2, w2, 16711680
	orr	w3, w3, w4, lsl 24
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 52]
	ldrb	w4, [x0, 1423]
	ldrb	w3, [x0, 1415]
	ldr	w1, [x0, 1428]
	ldrb	w2, [x0, 1407]
	lsl	w3, w3, 8
	and	w1, w1, -16777216
	orr	w3, w3, w4, lsl 16
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19, 56]
	ldrb	w3, [x0, 1455]
	ldrb	w2, [x0, 1447]
	ldr	w4, [x0, 1460]
	ldrb	w1, [x0, 1439]
	lsl	w2, w2, 8
	and	w0, w4, -16777216
	orr	w2, w2, w3, lsl 16
	orr	w0, w0, w1
	orr	w0, w2, w0
	str	w0, [x19, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_WriteQmatrix_16x16, .-HEVC_WriteQmatrix_16x16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CtbRsAddrToTsAddr
	.type	HEVC_CtbRsAddrToTsAddr, %function
HEVC_CtbRsAddrToTsAddr:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x3, [x20, 3016]
	ldrb	w0, [x3, 13]
	cbz	w0, .L585
	ldp	w6, w11, [x3, 68]
	ldr	x0, [x20, 3008]
	mov	w1, 0
	subs	w8, w11, #1
	ldrb	w7, [x3, 15]
	sub	w12, w6, #1
	ldr	w4, [x0, 64]
	ldr	w5, [x0, 128]
	bmi	.L557
	.p2align 2
.L588:
	sxtw	x0, w1
	add	x9, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x9, x0, lsl 2
	cmp	w11, w1
	ldrsh	w2, [x2, 212]
	sub	w2, w2, #1
	str	w2, [x0, -172]
	bne	.L588
.L557:
	mov	w1, 0
	tbnz	w12, #31, .L555
	.p2align 2
.L587:
	sxtw	x0, w1
	add	x9, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x9, x0, lsl 2
	cmp	w6, w1
	ldrsh	w2, [x2, 172]
	sub	w2, w2, #1
	str	w2, [x0, -84]
	bne	.L587
.L555:
	mov	w1, 1
	lsl	w0, w1, w5
	sdiv	w5, w4, w0
	msub	w0, w5, w0, w4
	cmp	w0, wzr
	csinc	w5, w5, w5, eq
	sdiv	w9, w19, w5
	msub	w5, w9, w5, w19
	cbz	w7, .L600
	tbnz	w8, #31, .L597
	mov	w14, 0
	mov	w13, 0
	mov	w4, 0
	mov	w7, 0
	mov	w8, 0
	mov	w0, 0
	.p2align 2
.L569:
	tbnz	w12, #31, .L580
	add	x0, x29, 224
	mov	w7, w4
	add	x0, x0, x13, sxtw 2
	mov	w1, 0
	mov	w2, 0
	ldr	w8, [x0, -172]
	add	w8, w8, 1
	add	w10, w14, w8
	b	.L566
	.p2align 3
.L578:
	mov	w7, w4
.L566:
	add	x0, x29, 224
	add	x0, x0, x2, sxtw 2
	add	w2, w2, 1
	ldr	w0, [x0, -84]
	add	w0, w0, 1
	add	w3, w0, w1
	cmp	w5, w3
	madd	w4, w0, w8, w4
	bge	.L564
	cmp	w9, w10
	blt	.L572
.L564:
	cmp	w6, w2
	mov	w1, w3
	bne	.L578
.L570:
	add	w1, w0, w3
	cmp	w5, w1
	bge	.L579
	cmp	w9, w10
	blt	.L595
.L579:
	add	w13, w13, 1
	mov	w14, w10
	cmp	w11, w13
	bne	.L569
.L596:
	sub	w9, w9, w10
	mov	w1, w3
	mul	w0, w9, w0
	.p2align 2
.L562:
	sub	w19, w5, w1
	add	w0, w19, w0
	add	w19, w0, w7
.L585:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L600:
	tbnz	w8, #31, .L597
	mov	w14, 0
	mov	w13, 0
	mov	w4, 0
	mov	w7, 0
	mov	w8, 0
	mov	w0, 0
	tbnz	w12, #31, .L583
	.p2align 2
.L601:
	add	x0, x29, 224
	mov	w7, w4
	add	x3, x0, x13, sxtw 2
	mov	w1, 0
	mov	w2, 0
	ldr	w8, [x3, -172]
	add	w8, w8, 1
	add	w10, w14, w8
	b	.L573
	.p2align 3
.L581:
	mov	w7, w4
.L573:
	add	x0, x29, 224
	add	x0, x0, x2, sxtw 2
	add	w2, w2, 1
	ldr	w0, [x0, -84]
	add	w0, w0, 1
	add	w3, w0, w1
	cmp	w5, w3
	madd	w4, w0, w8, w4
	bge	.L571
	cmp	w9, w10
	blt	.L572
.L571:
	cmp	w6, w2
	mov	w1, w3
	bne	.L581
.L577:
	add	w1, w0, w3
	cmp	w5, w1
	bge	.L582
	cmp	w9, w10
	blt	.L595
.L582:
	add	w13, w13, 1
	mov	w14, w10
	cmp	w11, w13
	beq	.L596
	tbz	w12, #31, .L601
.L583:
	mov	w3, 0
	add	w10, w14, w8
	b	.L577
	.p2align 3
.L572:
	sub	w9, w9, w14
	mul	w0, w9, w0
	b	.L562
.L580:
	mov	w3, 0
	add	w10, w14, w8
	b	.L570
.L597:
	mov	w0, 0
	mov	w1, 0
	mov	w7, 0
	b	.L562
.L595:
	sub	w9, w9, w14
	mov	w1, w3
	mul	w0, w9, w0
	b	.L562
	.size	HEVC_CtbRsAddrToTsAddr, .-HEVC_CtbRsAddrToTsAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CtbTsAddrToRsAddr
	.type	HEVC_CtbTsAddrToRsAddr, %function
HEVC_CtbTsAddrToRsAddr:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x3, [x20, 3016]
	ldrb	w0, [x3, 13]
	cbz	w0, .L620
	ldp	w8, w4, [x3, 68]
	ldr	x0, [x20, 3008]
	subs	w13, w4, #1
	sub	w12, w8, #1
	ldr	w5, [x0, 64]
	ldr	w6, [x0, 128]
	bmi	.L604
	mov	w1, 0
	.p2align 2
.L605:
	sxtw	x0, w1
	add	x7, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x7, x0, lsl 2
	cmp	w4, w1
	ldrsh	w2, [x2, 212]
	sub	w2, w2, #1
	str	w2, [x0, -172]
	bne	.L605
	tbnz	w12, #31, .L637
.L607:
	mov	w1, 0
	.p2align 2
.L610:
	sxtw	x0, w1
	add	x4, x29, 224
	add	w1, w1, 1
	add	x2, x3, x0, lsl 1
	add	x0, x4, x0, lsl 2
	cmp	w12, w1
	ldrsh	w2, [x2, 172]
	sub	w2, w2, #1
	str	w2, [x0, -84]
	bge	.L610
	mov	w1, 1
	lsl	w0, w1, w6
	sdiv	w1, w5, w0
	msub	w0, w1, w0, w5
	cmp	w0, wzr
	csinc	w0, w1, w1, eq
	tbnz	w13, #31, .L608
.L609:
	ldr	w11, [x29, 140]
	mov	w10, 0
	mov	w9, 0
	mov	w4, 0
	mov	w1, 0
	mov	w7, 0
	mov	w2, 0
	add	w11, w11, 1
	.p2align 2
.L616:
	tbnz	w12, #31, .L622
	add	x1, x29, 224
	add	x1, x1, x9, sxtw 2
	ldr	w7, [x1, -172]
	add	w7, w7, 1
	madd	w5, w11, w7, w4
	cmp	w19, w5
	blt	.L623
	mov	w1, w4
	mov	w2, w11
	mov	w6, 0
	mov	w3, 0
	mov	w4, w5
	b	.L613
	.p2align 3
.L614:
	ldr	w2, [x5, -84]
	mov	w1, w4
	add	w2, w2, 1
	madd	w5, w2, w7, w4
	cmp	w5, w19
	bgt	.L615
	mov	w4, w5
.L613:
	add	w3, w3, 1
	add	x5, x29, 224
	cmp	w8, w3
	add	w6, w6, w2
	add	x5, x5, x3, sxtw 2
	bne	.L614
.L617:
	cmp	w4, w19
	bgt	.L621
	add	w9, w9, 1
	add	w10, w10, w7
	cmp	w13, w9
	bge	.L616
.L621:
	mov	w4, w1
	.p2align 2
.L615:
	cbz	w2, .L608
	sub	w4, w19, w4
	sdiv	w1, w4, w2
	add	w10, w1, w10
	msub	w4, w1, w2, w4
	add	w6, w4, w6
	madd	w0, w10, w0, w6
.L632:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L620:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 224
	ret
.L622:
	mov	w6, 0
	b	.L617
.L623:
	mov	w2, w11
	mov	w6, 0
	b	.L615
.L637:
	mov	w0, 1
	lsl	w0, w0, w6
	sdiv	w1, w5, w0
	msub	w0, w1, w0, w5
	cmp	w0, wzr
	csinc	w0, w1, w1, eq
	b	.L609
.L604:
	tbz	w12, #31, .L607
.L608:
	ldr	x1, .LC163
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L632
	.size	HEVC_CtbTsAddrToRsAddr, .-HEVC_CtbTsAddrToRsAddr
	.align	3
.LC163:
	.xword	.LC162
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcTileMap
	.type	HEVC_CalcTileMap, %function
HEVC_CalcTileMap:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC164
	ldr	x0, [x20]
	cbz	x0, .L660
	ldr	x21, .LC168
	add	x0, x0, 483328
	mov	x2, 16384
	mov	w1, 0
	movk	x2, 0x2, lsl 16
	add	x0, x0, 336
	ldr	x3, [x21, 96]
	blr	x3
	ldr	x0, [x20]
	mov	x2, 36864
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x0, x0, 630784
	add	x0, x0, 336
	blr	x3
	add	x0, x19, 8192
	ldr	x3, [x21, 96]
	mov	x2, 880
	mov	w1, 0
	add	x0, x0, 2068
	blr	x3
	str	wzr, [x19, 10256]
	ldr	x0, [x19, 3016]
	ldr	x2, [x19, 3008]
	ldr	w1, [x0, 72]
	ldr	w11, [x2, 188]
	cbz	w1, .L642
	ldr	x7, [x20]
	mov	w16, 0
	mov	w18, 0
	mov	w4, 0
.L649:
	ldr	w1, [x0, 68]
	uxtw	x17, w16
	cbz	w1, .L650
	add	x10, x17, 104
	ldr	w1, [x19, 10256]
	mul	w15, w18, w11
	mov	w13, 0
	mov	w14, 0
	lsl	x10, x10, 1
.L648:
	uxtw	x2, w1
	add	x3, x0, x10
	uxtw	x12, w13
	add	x5, x19, x2, lsl 3
	str	w4, [x5, 10260]
	ldrsh	w3, [x3, 4]
	cbz	w3, .L644
	add	x5, x12, 80
	add	w9, w14, w15
	mov	w8, 0
	lsl	x5, x5, 1
	.p2align 2
.L646:
	add	x2, x0, x5
	mov	w1, w4
	sub	w6, w9, w4
	ldrsh	w2, [x2, 12]
	cbz	w2, .L647
	.p2align 2
.L654:
	sxtw	x0, w1
	add	w3, w6, w1
	add	x0, x0, 118784
	add	w1, w1, 1
	add	x0, x0, 2132
	sub	w2, w1, w4
	str	w3, [x7, x0, lsl 2]
	ldr	x0, [x19, 3016]
	add	x3, x0, x5
	ldrsh	w3, [x3, 12]
	cmp	w3, w2
	bhi	.L654
	mov	w4, w1
.L647:
	add	x1, x0, x10
	add	w8, w8, 1
	add	w9, w9, w11
	ldrsh	w1, [x1, 4]
	cmp	w1, w8
	bhi	.L646
	ldr	w1, [x19, 10256]
	uxtw	x2, w1
.L644:
	add	x2, x19, x2, lsl 3
	sub	w3, w4, #1
	add	w1, w1, 1
	add	x12, x0, x12, lsl 1
	add	w13, w13, 1
	str	w3, [x2, 10264]
	str	w1, [x19, 10256]
	ldr	w3, [x0, 68]
	ldrsh	w2, [x12, 172]
	cmp	w3, w13
	add	w14, w14, w2
	bhi	.L648
.L650:
	add	x17, x0, x17, lsl 1
	ldr	w1, [x0, 72]
	add	w16, w16, 1
	cmp	w1, w16
	ldrsh	w1, [x17, 212]
	add	w18, w18, w1
	bhi	.L649
.L642:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L660:
	ldr	x2, .LC165
	ldr	x1, .LC167
	add	x2, x2, 352
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_CalcTileMap, .-HEVC_CalcTileMap
	.align	3
.LC164:
	.xword	.LANCHOR1
	.align	3
.LC165:
	.xword	.LANCHOR0
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC168:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WritePicMsg
	.type	HEVC_WritePicMsg, %function
HEVC_WritePicMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 4096
	add	x21, x19, 8192
	bl	_mcount
	ldr	w3, [x19, 4892]
	mov	w0, 2
	ldr	w2, [x19, 5076]
	ldr	x1, .LC170
	bl	dprint_vfmw
	ldr	x1, .LC172
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w22, [x19, 4864]
	ldr	w6, [x19, 5040]
	ldr	w5, [x19, 5044]
	str	w6, [x19, 8848]
	str	w5, [x19, 8852]
	ldr	w4, [x19, 4972]
	ldr	w0, [x19, 4964]
	ldr	w5, [x19, 4892]
	ldr	w6, [x19, 5076]
	ldr	w2, [x19, 4968]
	str	w6, [x19, 8840]
	str	w5, [x19, 8844]
	sub	w2, w2, w0
	ldr	w1, [x19, 4976]
	sub	w0, w4, w0
	ldr	w6, [x19, 5064]
	ldr	w5, [x19, 5068]
	ldr	x3, [x19, 3008]
	str	w6, [x19, 8860]
	str	w5, [x19, 8864]
	ldr	w6, [x19, 5072]
	ldr	x5, [x19, 3048]
	str	w22, [x19, 7584]
	uxtw	x22, w22
	str	w2, [x19, 8856]
	lsl	x24, x22, 3
	str	w0, [x19, 8872]
	sub	w0, w1, w4
	str	w6, [x19, 8868]
	mov	x2, 64
	str	w0, [x19, 8876]
	add	x0, x24, x22, lsl 5
	str	x5, [x19, 10048]
	lsl	x23, x0, 3
	str	wzr, [x19, 204]
	sub	x23, x23, x0
	add	x0, x20, 3584
	ldrb	w1, [x3, 10]
	strb	w1, [x20, 3462]
	ldrb	w1, [x3, 3]
	strb	w1, [x20, 3463]
	ldrb	w1, [x3, 7]
	strb	w1, [x20, 3464]
	ldrb	w1, [x3, 6]
	strb	w1, [x20, 3465]
	ldrb	w1, [x3, 5]
	strb	w1, [x20, 3466]
	ldr	w1, [x3, 60]
	str	w1, [x19, 7564]
	ldr	w1, [x3, 104]
	strb	w1, [x20, 3472]
	ldr	w1, [x3, 192]
	ldr	x4, [x19, 3016]
	sub	w1, w1, #1
	str	w1, [x19, 7572]
	ldr	w6, [x19, 4868]
	add	x1, x23, 12288
	ldr	w5, [x3, 188]
	add	x1, x19, x1
	str	w6, [x19, 7580]
	add	x1, x1, 2036
	sub	w5, w5, #1
	str	w5, [x19, 7576]
	ldr	w5, [x4, 84]
	sub	w5, w5, #2
	str	w5, [x19, 7588]
	ldrb	w5, [x4, 11]
	strb	w5, [x20, 3496]
	ldrb	w4, [x4, 10]
	strb	w4, [x20, 3497]
	ldr	w4, [x3, 164]
	str	w4, [x19, 7596]
	ldr	w4, [x3, 168]
	str	w4, [x19, 7600]
	ldr	w4, [x3, 156]
	str	w4, [x19, 7604]
	ldr	w4, [x3, 160]
	str	w4, [x19, 7608]
	ldr	w4, [x3, 148]
	str	w4, [x19, 7612]
	ldr	w4, [x3, 152]
	str	w4, [x19, 7616]
	ldr	w4, [x3, 172]
	str	w4, [x19, 7620]
	ldr	x4, .LC173
	ldr	w5, [x3, 124]
	str	w5, [x19, 7624]
	ldr	x4, [x4, 104]
	ldr	w5, [x3, 128]
	str	w5, [x19, 7628]
	ldr	w5, [x3, 100]
	str	w5, [x19, 7632]
	ldr	w5, [x3, 92]
	str	w5, [x19, 7636]
	ldr	w5, [x3, 112]
	str	w5, [x19, 7640]
	ldr	w5, [x3, 108]
	str	w5, [x19, 7644]
	ldr	w5, [x3, 96]
	str	w5, [x19, 7648]
	ldr	w3, [x3, 88]
	str	w3, [x19, 7652]
	blr	x4
	ldr	x0, [x19, 3008]
	add	x3, x21, 1692
	add	x2, x21, 1612
	add	x1, x21, 1100
	ldr	w4, [x0, 68]
	str	w4, [x19, 7744]
	ldr	w0, [x0, 64]
	str	w0, [x19, 7748]
	mov	x0, x19
	bl	HEVC_CalcTileInfo
	cbnz	w0, .L681
	ldr	x1, [x19, 3016]
	mov	w0, 0
	ldrb	w2, [x1, 16]
	strb	w2, [x20, 3676]
	ldrb	w2, [x1, 7]
	strb	w2, [x20, 3677]
	ldrb	w2, [x1, 3]
	strb	w2, [x20, 3678]
	ldrb	w2, [x1, 14]
	strb	w2, [x20, 3679]
	ldrb	w2, [x1, 15]
	strb	w2, [x20, 3680]
	ldrb	w2, [x1, 13]
	strb	w2, [x20, 3681]
	ldr	x2, [x19, 3008]
	ldr	w3, [x1, 56]
	ldr	w2, [x2, 128]
	sub	w2, w2, w3
	str	w2, [x19, 7780]
	ldr	w2, [x1, 52]
	str	w2, [x19, 7784]
	ldrb	w2, [x1, 8]
	strb	w2, [x20, 3692]
	ldrb	w2, [x1, 12]
	strb	w2, [x20, 3693]
	ldrb	w2, [x1, 6]
	strb	w2, [x20, 3694]
	ldr	w2, [x1, 60]
	str	w2, [x19, 7792]
	ldr	w2, [x1, 64]
	str	w2, [x19, 7796]
	ldr	w2, [x1, 72]
	sub	w2, w2, #1
	str	w2, [x19, 7800]
	ldr	w2, [x1, 68]
	sub	w2, w2, #1
	str	w2, [x19, 7804]
	ldrb	w2, [x1, 10]
	strb	w2, [x20, 3497]
	ldrb	w1, [x1, 11]
	strb	w1, [x20, 3496]
	str	wzr, [x19, 2384]
	ldr	w1, [x19, 2368]
	cmp	w1, 1
	beq	.L663
	ldr	x1, [x19, 4920]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	mov	x25, x0
	cbz	x0, .L682
	ldp	x2, x3, [x0, 32]
	cbz	x2, .L666
	cbz	x3, .L666
	ldr	w0, [x19, 276]
	add	x3, x21, 972
	add	x2, x21, 704
	add	x1, x21, 832
	add	x23, x19, x23
	bl	FSP_GetDecFsAddrTab
	ldr	x1, [x25, 32]
	add	x2, x21, 836
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 4]
	str	w1, [x19, 8840]
	add	x1, x21, 964
	bl	FSP_GetPmvAddrTab
	ldr	w0, [x19, 4892]
	mov	w1, 0
	str	w0, [x19, 8844]
	ldr	w0, [x25, 12]
	str	w0, [x19, 9160]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 8]
	str	w0, [x19, 10248]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 60]
	str	w0, [x19, 10252]
	ldr	w3, [x23, 14188]
	str	w3, [x19, 10036]
	cbz	w3, .L671
	add	x22, x24, x22, lsl 1
	lsl	x0, x22, 3
	sub	x22, x0, x22
	.p2align 2
.L675:
	sxtw	x0, w1
	add	w1, w1, 1
	add	x2, x22, x0
	cmp	w1, w3
	add	x0, x19, x0, lsl 2
	add	x2, x19, x2, lsl 2
	ldr	w2, [x2, 14260]
	str	w2, [x0, 9972]
	bne	.L675
.L671:
	add	x23, x20, 3716
	mov	w22, 0
.L669:
	mov	x2, x23
	mov	w0, w22
	mov	x1, x19
	add	w22, w22, 1
	add	x23, x23, 64
	bl	HEVC_WriteQmatrix_8x8
	cmp	w22, 4
	bne	.L669
	mov	w0, w22
	add	x2, x20, 3972
	mov	x1, x19
	add	x23, x21, 132
	mov	w22, 2
	bl	HEVC_WriteQmatrix_8x8
	add	x2, x20, 4036
	mov	x1, x19
	mov	w0, 5
	bl	HEVC_WriteQmatrix_8x8
	add	x2, x21, 4
	mov	x1, x19
	mov	w0, 0
	bl	HEVC_WriteQmatrix_16x16
	add	x2, x21, 68
	mov	x1, x19
	mov	w0, 1
	bl	HEVC_WriteQmatrix_16x16
.L672:
	mov	x2, x23
	mov	w0, w22
	mov	x1, x19
	add	w22, w22, 1
	add	x23, x23, 64
	bl	HEVC_WriteQmatrix_16x16
	cmp	w22, 6
	bne	.L672
	add	x2, x21, 388
	mov	x1, x19
	mov	w0, 0
	add	x22, x21, 516
	mov	w20, 0
	bl	HEVC_WriteQmatrix_32x32
	add	x2, x21, 452
	mov	x1, x19
	mov	w0, 1
	bl	HEVC_WriteQmatrix_32x32
	.p2align 2
.L673:
	mov	x2, x22
	mov	w0, w20
	mov	x1, x19
	add	w20, w20, 1
	add	x22, x22, 16
	bl	HEVC_WriteQmatrix_4x4
	cmp	w20, 6
	bne	.L673
	add	x0, x19, 2304
	add	x8, x19, 2304
	ldp	w5, w6, [x0, 16]
	ldp	w3, w4, [x8, 32]
	ldp	w7, w2, [x0, 8]
	ldp	w0, w1, [x8, 24]
	lsl	w3, w3, 16
	lsl	w5, w5, 16
	orr	w3, w3, w4, lsl 24
	orr	w5, w5, w6, lsl 24
	orr	w0, w0, w1, lsl 8
	orr	w2, w7, w2, lsl 8
	orr	w0, w3, w0
	ldr	w4, [x19, 4892]
	orr	w1, w5, w2
	str	w0, [x19, 8808]
	str	w1, [x19, 8804]
	mov	w0, 0
	str	w4, [x19, 8836]
.L663:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L681:
	ldr	x2, .LC174
	mov	w0, 1
	ldr	x1, .LC176
	add	x2, x2, 376
	bl	dprint_vfmw
	mov	w0, -1
	b	.L663
.L666:
	ldr	x1, .LC180
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L663
.L682:
	ldr	x2, [x19, 4920]
	mov	w0, 1
	ldr	x1, .LC178
	ldr	w2, [x2, 28]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L663
	.size	HEVC_WritePicMsg, .-HEVC_WritePicMsg
	.align	3
.LC170:
	.xword	.LC169
	.align	3
.LC172:
	.xword	.LC171
	.align	3
.LC173:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC174:
	.xword	.LANCHOR0
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC180:
	.xword	.LC179
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckListX
	.type	HEVC_CheckListX, %function
HEVC_CheckListX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 4096
	add	x0, x0, 1472
	ldrb	w1, [x0, 1]
	cbz	w1, .L685
	ldrsb	w1, [x19, 14]
	add	x0, x19, 12288
	add	x0, x0, 524
	cbz	w1, .L717
.L685:
	ldp	w4, w5, [x0, 68]
	cmp	w4, 16
	bhi	.L718
	cmp	w5, 16
	bhi	.L689
	cbz	w4, .L690
	ldr	x0, [x19, 3064]
	cbz	x0, .L703
	ldr	x0, [x0, 24]
	cbz	x0, .L719
	add	x0, x19, 3072
	mov	w2, 0
	b	.L695
	.p2align 3
.L696:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L691
	ldr	x1, [x1, 24]
	cbz	x1, .L692
.L695:
	add	w2, w2, 1
	cmp	w4, w2
	bne	.L696
.L690:
	cbz	w5, .L705
	ldr	x0, [x19, 3200]
	cbz	x0, .L706
	ldr	x0, [x0, 24]
	cbz	x0, .L720
	add	x0, x19, 3208
	mov	w2, 0
	b	.L701
	.p2align 3
.L702:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L697
	ldr	x1, [x1, 24]
	cbz	x1, .L698
.L701:
	add	w2, w2, 1
	cmp	w5, w2
	bne	.L702
.L705:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L703:
	mov	w2, 0
	.p2align 2
.L691:
	ldr	x1, .LC189
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L687:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L719:
	mov	w2, 0
.L692:
	ldr	x1, .LC191
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L706:
	mov	w2, 0
.L697:
	ldr	x1, .LC193
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L720:
	mov	w2, 0
.L698:
	ldr	x1, .LC195
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L717:
	ldr	x2, .LC181
	mov	w0, 0
	ldr	x1, .LC183
	add	x2, x2, 400
	bl	dprint_vfmw
	mov	w0, -1
	b	.L687
.L689:
	ldr	x1, .LC187
	mov	w3, 17
	mov	w2, w5
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L687
.L718:
	ldr	x1, .LC185
	mov	w3, 17
	mov	w2, w4
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L687
	.size	HEVC_CheckListX, .-HEVC_CheckListX
	.align	3
.LC181:
	.xword	.LANCHOR0
	.align	3
.LC183:
	.xword	.LC182
	.align	3
.LC185:
	.xword	.LC184
	.align	3
.LC187:
	.xword	.LC186
	.align	3
.LC189:
	.xword	.LC188
	.align	3
.LC191:
	.xword	.LC190
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC195:
	.xword	.LC194
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
	stp	x29, x30, [sp, -240]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	ldr	w24, [x19, 4864]
	bl	HEVC_CheckListX
	mov	w23, w0
	cbnz	w0, .L793
	ldr	w3, [x19, 152]
	ldr	w0, [x19, 204]
	cmp	w0, w3
	bcs	.L871
	mov	w22, 1512
	ldr	x21, .LC198
	ldr	x20, [x19, 3048]
	mov	x2, 1512
	umull	x0, w0, w22
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x20, x20, x0
	mov	x0, x20
	blr	x3
	ldr	x3, [x21, 96]
	mov	w1, 0
	mov	x2, 64
	add	x0, x29, 176
	blr	x3
	ldr	w0, [x19, 204]
	ldr	w1, [x19, 152]
	add	w0, w0, 1
	str	w0, [x19, 204]
	cmp	w0, w1
	bcc	.L872
	str	xzr, [x20, 1504]
.L725:
	ldr	w22, [x19, 176]
	ldr	w0, [x19, 260]
	ldr	w1, [x19, 5604]
	add	w22, w22, 1
	ldr	x3, [x19, 2984]
	add	w0, w0, 1
	str	w22, [x19, 176]
	str	w1, [x19, 208]
	str	w0, [x19, 260]
	ldrb	w1, [x3]
	ldr	w0, [x3, 8]
	cmp	w1, 1
	ccmp	w1, w0, 2, ls
	bcs	.L726
	.p2align 2
.L727:
	uxtw	x0, w1
	lsl	x2, x0, 5
	add	x3, x3, x2
	add	x0, x20, x0, lsl 2
	ldr	w3, [x3, 60]
	str	w3, [x0, 8]
	ldr	x3, [x19, 2984]
	add	x3, x3, x2
	ldr	w3, [x3, 56]
	str	w3, [x20, w1, uxtw 2]
	add	w1, w1, 1
	ldr	x3, [x19, 2984]
	add	x2, x3, x2
	ldr	w2, [x2, 64]
	str	w2, [x0, 16]
	ldr	x3, [x19, 2984]
	ldr	w0, [x3, 8]
	cmp	w0, w1
	ccmp	w1, 1, 2, hi
	bls	.L727
.L726:
	cmp	w0, 1
	bhi	.L732
	.p2align 2
.L843:
	add	x1, x20, x0, uxtw 2
	str	wzr, [x1, 8]
	str	wzr, [x20, w0, uxtw 2]
	add	w0, w0, 1
	cmp	w0, 2
	str	wzr, [x1, 16]
	bne	.L843
.L732:
	add	x25, x19, 4096
	add	x26, x19, 12288
	ldrb	w0, [x25, 1473]
	cbz	w0, .L873
.L730:
	ldr	w0, [x19, 12880]
	cbz	w0, .L733
	mov	w4, 0
	mov	w5, 1
	b	.L737
	.p2align 3
.L875:
	ldr	w1, [x3, 16]
	cbz	w1, .L735
	ldr	w1, [x19, 5600]
	cbz	w1, .L735
	ldr	x1, [x3, 24]
	add	x6, x29, 240
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 36]
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1, lsl 2
	ldr	w2, [x2, 9028]
	str	w2, [x1, -64]
	ldr	x1, [x3, 24]
	ldr	w1, [x1, 36]
	str	w1, [x0, 372]
	ldrb	w1, [x19, 2]
	cbz	w1, .L736
	str	w5, [x0, 116]
.L736:
	ldr	w0, [x19, 12880]
	add	w4, w4, 1
	cmp	w0, w4
	bls	.L874
	.p2align 2
.L737:
	uxtw	x0, w4
	add	x1, x19, x0, lsl 3
	add	x0, x20, x0, lsl 2
	ldr	x2, [x1, 3064]
	ldr	w2, [x2, 4]
	str	w2, [x0, 116]
	ldrb	w2, [x19, 1]
	ldr	x3, [x1, 3064]
	cbnz	w2, .L875
.L735:
	ldr	x1, [x3, 24]
	add	x6, x29, 240
	add	w4, w4, 1
	ldp	w2, w1, [x1, 20]
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1, lsl 2
	ldr	w2, [x2, 9028]
	str	w2, [x1, -64]
	ldr	x1, [x3, 24]
	ldr	w1, [x1, 24]
	str	w1, [x0, 372]
	ldr	w0, [x19, 12880]
	cmp	w0, w4
	bhi	.L737
.L874:
	ldr	w3, [x19, 12884]
	cbz	w3, .L738
.L792:
	mov	w4, 0
	mov	w5, 1
	b	.L742
	.p2align 3
.L877:
	ldr	w1, [x3, 16]
	cbz	w1, .L740
	ldr	w1, [x19, 5600]
	cbz	w1, .L740
	ldr	x1, [x3, 24]
	add	x6, x29, 240
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 36]
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1, lsl 2
	ldr	w2, [x2, 9028]
	str	w2, [x1, -64]
	ldr	x1, [x3, 24]
	ldr	w1, [x1, 36]
	str	w1, [x0, 436]
	ldrb	w1, [x19, 2]
	cbz	w1, .L741
	str	w5, [x0, 180]
.L741:
	ldr	w3, [x19, 12884]
	add	w4, w4, 1
	cmp	w3, w4
	bls	.L876
	.p2align 2
.L742:
	uxtw	x0, w4
	add	x1, x19, x0, lsl 3
	add	x0, x20, x0, lsl 2
	ldr	x2, [x1, 3200]
	ldr	w2, [x2, 4]
	str	w2, [x0, 180]
	ldrb	w2, [x19, 1]
	ldr	x3, [x1, 3200]
	cbnz	w2, .L877
.L740:
	ldr	x1, [x3, 24]
	add	x6, x29, 240
	add	w4, w4, 1
	ldp	w2, w1, [x1, 20]
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1, lsl 2
	ldr	w2, [x2, 9028]
	str	w2, [x1, -64]
	ldr	x1, [x3, 24]
	ldr	w1, [x1, 24]
	str	w1, [x0, 436]
	ldr	w3, [x19, 12884]
	cmp	w3, w4
	bhi	.L742
.L876:
	ldr	w0, [x19, 12880]
.L738:
	cbz	w0, .L743
	uxtw	x1, w24
	ldr	w2, [x20, 372]
	lsl	x4, x1, 3
	ldr	w5, [x19, 4868]
	add	x4, x4, x1, lsl 1
	lsl	x1, x4, 3
	sub	x4, x1, x4
	add	x1, x4, x2
	add	x1, x19, x1, lsl 2
	ldr	w1, [x1, 14324]
	cmp	w5, w1
	blt	.L799
	sub	w0, w0, #1
	mov	x1, x20
	add	x2, x20, x0, lsl 2
	b	.L746
	.p2align 3
.L747:
	ldr	w0, [x1, 376]
	add	x1, x1, 4
	add	x0, x4, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14324]
	cmp	w0, w5
	bgt	.L799
.L746:
	cmp	x1, x2
	bne	.L747
.L743:
	ldr	w0, [x19, 12832]
	cbnz	w0, .L870
	mov	w0, 1
	cbz	w3, .L744
	uxtw	x1, w24
	ldr	w4, [x19, 4868]
	lsl	x0, x1, 3
	add	x1, x0, x1, lsl 1
	ldr	w0, [x20, 436]
	lsl	x2, x1, 3
	sub	x2, x2, x1
	add	x0, x2, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14324]
	cmp	w4, w0
	blt	.L799
	sub	w3, w3, #1
	mov	x1, x20
	add	x3, x20, x3, lsl 2
	b	.L749
	.p2align 3
.L750:
	ldr	w0, [x1, 440]
	add	x1, x1, 4
	add	x0, x2, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14324]
	cmp	w0, w4
	bgt	.L799
.L749:
	cmp	x1, x3
	bne	.L750
.L870:
	mov	w0, 1
.L744:
	strb	w0, [x20, 24]
	ldrb	w0, [x25, 1473]
	strb	w0, [x20, 25]
	ldr	w2, [x19, 12828]
	str	w2, [x20, 28]
	ldrb	w0, [x26, 531]
	strb	w0, [x20, 32]
	ldr	w0, [x19, 12852]
	str	w0, [x20, 36]
	ldr	w0, [x19, 2368]
	cbnz	w0, .L751
	ldr	x3, [x19, 4920]
	ldr	w4, [x19, 204]
	ldr	w0, [x3, 324]
	sub	w1, w4, #1
	madd	w0, w1, w0, w2
	udiv	w0, w0, w4
	str	w0, [x3, 68]
.L751:
	ldr	w0, [x19, 12832]
	cbz	w0, .L878
	cmp	w0, 1
	mov	w24, 0
	beq	.L753
.L754:
	str	w24, [x20, 40]
	ldr	w0, [x19, 12856]
	str	w0, [x20, 48]
	ldrb	w0, [x26, 532]
	strb	w0, [x20, 52]
	ldr	w0, [x19, 12860]
	str	w0, [x20, 44]
	ldr	w0, [x19, 12888]
	cbz	w0, .L755
	sub	w0, w0, #1
	str	w0, [x20, 60]
.L756:
	ldr	w0, [x19, 12892]
	cbz	w0, .L757
	sub	w0, w0, #1
	str	w0, [x20, 56]
.L758:
	ldrb	w0, [x26, 528]
	strb	w0, [x20, 64]
	ldrb	w0, [x26, 530]
	strb	w0, [x20, 65]
	ldr	w0, [x19, 12880]
	str	w0, [x20, 68]
	ldr	w0, [x19, 12884]
	str	w0, [x20, 72]
	ldr	w0, [x19, 12832]
	str	w0, [x20, 76]
	ldr	w0, [x19, 5608]
	str	w0, [x20, 80]
	ldr	x0, [x19, 3008]
	ldr	w3, [x19, 5608]
	ldr	w1, [x0, 188]
	mov	x0, x19
	udiv	w2, w3, w1
	msub	w1, w2, w1, w3
	str	w1, [x20, 84]
	ldr	x1, [x19, 3008]
	ldr	w2, [x1, 188]
	ldr	w1, [x19, 5608]
	udiv	w1, w1, w2
	str	w1, [x20, 88]
	ldr	w1, [x19, 5608]
	bl	HEVC_CtbRsAddrToTsAddr
	str	w0, [x20, 92]
	ldr	w0, [x19, 12864]
	str	w0, [x20, 96]
	ldr	w0, [x19, 12868]
	str	w0, [x20, 100]
	ldr	w0, [x19, 12876]
	str	w0, [x20, 104]
	ldr	w0, [x19, 12872]
	str	w0, [x20, 108]
	ldrb	w0, [x26, 527]
	strb	w0, [x20, 112]
	ldrb	w0, [x26, 526]
	strb	w0, [x20, 113]
	ldrb	w0, [x26, 533]
	strb	w0, [x20, 114]
	ldrb	w0, [x26, 534]
	strb	w0, [x20, 115]
	ldr	x0, [x19, 3016]
	ldrb	w1, [x0, 10]
	cbz	w1, .L759
	ldr	w1, [x19, 12832]
	cmp	w1, 1
	beq	.L760
.L759:
	ldrb	w0, [x0, 11]
	cmp	w0, 1
	beq	.L879
.L762:
	ldrb	w0, [x26, 528]
	cbz	w0, .L764
	add	x0, x29, 240
	add	x24, x0, x24, sxtw 2
	ldr	w0, [x24, -64]
	str	w0, [x20, 564]
.L765:
	ldrb	w0, [x19, 2]
	cbz	w0, .L766
	ldr	w0, [x19, 5600]
	cbz	w0, .L766
	ldr	x8, [x19, 3048]
	add	x26, x20, 1356
	cmp	x20, x8
	beq	.L880
.L769:
	ldr	w4, [x20, 68]
	cbz	w4, .L770
	mov	x1, 0
	mov	w0, 0
	.p2align 2
.L772:
	add	x2, x19, x0, sxtw 3
	add	w0, w0, 1
	ldr	x2, [x2, 3064]
	ldr	x2, [x2, 24]
	add	x3, x2, 88
	ldr	w2, [x2, 32]
	cmp	w2, wzr
	csel	x1, x1, x3, ne
	cmp	w0, w4
	bne	.L772
	cbz	x1, .L770
.L773:
	ldrsw	x0, [x20, 40]
	ldr	w2, [x19, 4876]
	add	x0, x19, x0
	ldr	w12, [x19, 4880]
	add	x0, x0, 12288
	ldrsb	w0, [x0, 2444]
	cbnz	w0, .L776
	mov	w0, 1
	strb	w0, [x26, 1]
.L777:
	cbz	x1, .L778
	add	x24, x8, 1356
	ldr	w0, [x1, 168]
	ldp	w5, w6, [x1, 68]
	str	w2, [x29, 120]
	str	w0, [x24, 112]
	str	w5, [x29, 128]
	ldr	w0, [x1, 172]
	str	w0, [x24, 116]
	ldr	x3, [x21, 488]
	ldr	w0, [x1, 112]
	str	w0, [x24, 120]
	ldp	w4, w0, [x1, 20]
	sub	w0, w0, w4
	str	w0, [x24, 124]
	ldr	w0, [x1, 140]
	str	w0, [x24, 128]
	ldr	w0, [x1, 144]
	str	w0, [x24, 132]
	ldr	w4, [x1, 20]
	ldr	w0, [x1, 44]
	sub	w0, w0, w4
	str	w0, [x24, 136]
	ldr	w0, [x1, 48]
	ldr	w1, [x1, 44]
	sub	w0, w0, w1
	str	w0, [x24, 140]
	ldr	x10, [x19, 3016]
	stp	x8, x10, [x29, 104]
	add	x4, x10, 1888
	ldr	w0, [x10, 1960]
	ldr	w28, [x10, 2472]
	ldr	w1, [x10, 3496]
	sub	w0, w2, w0, lsl 1
	sub	w9, w0, w28, lsl 1
	ldr	w0, [x10, 2984]
	sxtw	x11, w9
	sub	w0, w5, w0, lsl 1
	sub	w7, w0, w1, lsl 1
	ldr	w0, [x10, 2216]
	stp	w12, w7, [x29, 152]
	ldr	w27, [x10, 2728]
	sub	w0, w12, w0, lsl 1
	ldr	w1, [x10, 3240]
	str	w9, [x29, 160]
	sub	w27, w0, w27, lsl 1
	ldr	w0, [x10, 3752]
	sub	w1, w6, w1, lsl 1
	str	x4, [x29, 144]
	str	w6, [x29, 136]
	sub	w28, w1, w0, lsl 1
	sbfiz	x0, x7, 16, 32
	mov	w1, w9
	add	x0, x0, x11, lsr 1
	blr	x3
	mov	x11, x0
	sxtw	x1, w27
	ldr	x3, [x21, 488]
	sbfiz	x0, x28, 16, 32
	str	x11, [x29, 168]
	add	x0, x0, x1, lsr 1
	mov	w1, w27
	blr	x3
	mov	x21, x0
	ldr	w2, [x29, 120]
	ldr	w5, [x29, 128]
	ldr	w6, [x29, 136]
	cmp	w2, w5
	ldr	w9, [x29, 160]
	ldp	w12, w7, [x29, 152]
	ldp	x8, x10, [x29, 104]
	ldr	x4, [x29, 144]
	ldr	x11, [x29, 168]
	bgt	.L779
	cmp	w11, 65536
	cset	w14, le
.L780:
	cmp	w12, w6
	bgt	.L781
	cmp	w21, 65536
	cset	w13, le
.L782:
	mov	w0, 1
	strb	w0, [x8, 1356]
	stp	w5, w6, [x24, 8]
	cbz	w14, .L783
	orr	w13, w14, w13
	str	w13, [x24, 4]
.L783:
	stp	w11, w21, [x24, 24]
	stp	w11, w21, [x24, 32]
	ldrb	w0, [x4, 2]
	cbz	w0, .L784
	ldr	w0, [x4, 2120]
	str	w0, [x24, 72]
	mul	w8, w0, w11
	ldr	w0, [x10, 4264]
	str	w0, [x24, 76]
	add	w8, w8, 8
	mul	w3, w0, w21
	ldr	w0, [x10, 4520]
	neg	w8, w8, asr 4
	add	w3, w3, 8
	sub	w0, w0, #8
	str	w0, [x24, 80]
	neg	w3, w3, asr 4
	mul	w2, w0, w11
	ldr	w1, [x10, 4776]
	asr	w0, w28, 1
	add	w2, w2, 8
	sub	w1, w1, #8
	str	w1, [x24, 84]
	neg	w2, w2, asr 4
.L785:
	mul	w1, w1, w21
	add	w0, w0, w27, lsl 8
	add	w1, w1, 8
	stp	w8, w3, [x24, 88]
	neg	w1, w1, asr 4
	mov	w3, 4095
	stp	w2, w1, [x24, 96]
	asr	w1, w7, 1
	mov	w2, -4096
	sdiv	w0, w0, w28
	add	w1, w1, w9, lsl 8
	sdiv	w1, w1, w7
	cmp	w1, 4095
	csel	w1, w1, w3, le
	cmn	w1, #4096
	csel	w1, w1, w2, ge
	cmp	w0, w3
	csel	w0, w0, w3, le
	cmp	w0, w2
	csel	w0, w0, w2, ge
	stp	w1, w0, [x24, 104]
	mov	w0, 1
	ldr	w1, [x4, 72]
	lsl	w1, w1, 1
	str	w1, [x24, 40]
	asr	w2, w1, 1
	ldr	w1, [x4, 328]
	lsl	w1, w1, 1
	stp	w1, w2, [x24, 44]
	asr	w1, w1, 1
	str	w1, [x24, 52]
	ldr	w1, [x4, 1096]
	lsl	w1, w1, 1
	str	w1, [x24, 56]
	asr	w2, w1, 1
	ldr	w1, [x4, 1352]
	lsl	w1, w1, 1
	stp	w1, w2, [x24, 60]
	asr	w1, w1, 1
	str	w1, [x24, 68]
	ldr	x1, [x19, 3008]
	ldr	w1, [x1, 128]
	lsl	w1, w0, w1
	sub	w2, w1, #1
	neg	w1, w1
	add	w0, w5, w2
	add	w2, w6, w2
	and	w0, w0, w1
	and	w1, w2, w1
	stp	w0, w1, [x24, 16]
.L778:
	str	wzr, [x26, 144]
	mov	w2, 0
	mov	w0, 0
	ldr	w1, [x19, 14468]
	cbz	w1, .L768
	.p2align 2
.L842:
	add	x1, x19, x0, sxtw
	add	x1, x1, 12288
	ldrsb	w1, [x1, 2444]
	lsl	w1, w1, w0
	add	w0, w0, 1
	orr	w2, w2, w1
	str	w2, [x26, 144]
	ldr	w1, [x19, 14468]
	cmp	w1, w0
	bhi	.L842
	b	.L768
	.p2align 3
.L872:
	ldr	x1, [x19, 3048]
	umull	x0, w0, w22
	add	x0, x1, x0
	str	x0, [x20, 1504]
	b	.L725
	.p2align 3
.L799:
	mov	w0, 0
	b	.L744
	.p2align 3
.L766:
	mov	w1, 1
	strb	wzr, [x20, 1356]
	strb	w1, [x20, 1357]
	str	wzr, [x20, 1360]
.L768:
	ldr	w0, [x19, 2368]
	cbnz	w0, .L789
	ldr	x0, [x19, 3024]
	ldr	x1, [x19, 2984]
	str	x1, [x0, w22, uxtw 3]
	str	xzr, [x19, 2984]
.L789:
	ldrb	w0, [x25, 3681]
	cbz	w0, .L824
	ldr	w0, [x19, 260]
	cmp	w0, 1
	beq	.L881
	sub	w1, w0, #2
	ldr	w2, [x20, 92]
	sub	w0, w0, #1
	add	x1, x19, x1, lsl 3
	sub	w2, w2, #1
	add	x3, x19, x0, lsl 3
	str	w2, [x1, 11144]
	ldr	w1, [x20, 92]
	str	w1, [x3, 11140]
.L791:
	ldr	w1, [x19, 7572]
	add	x0, x19, x0, lsl 3
	ldr	w2, [x19, 7576]
	mov	w3, 36863
	madd	w2, w1, w2, w2
	add	w1, w2, w1
	str	w1, [x0, 11144]
	ldr	w1, [x20, 92]
	sub	w1, w1, #1
	cmp	w1, w3
	bhi	.L824
	mov	x0, x19
	bl	HEVC_CtbTsAddrToRsAddr
	str	w0, [x20, 568]
.L824:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L878:
	ldrb	w0, [x26, 532]
	cbnz	w0, .L753
	ldrsw	x0, [x19, 12856]
	add	x0, x20, x0, lsl 2
	ldr	w24, [x0, 436]
	b	.L754
	.p2align 3
.L764:
	ldr	w0, [x19, 9028]
	str	w0, [x20, 564]
	b	.L765
	.p2align 3
.L757:
	str	wzr, [x20, 56]
	b	.L758
	.p2align 3
.L755:
	str	wzr, [x20, 60]
	b	.L756
	.p2align 3
.L753:
	ldrsw	x0, [x19, 12856]
	add	x0, x20, x0, lsl 2
	ldr	w24, [x0, 372]
	b	.L754
	.p2align 3
.L873:
	ldr	x3, [x21, 104]
	mov	x2, 1376
	add	x1, x25, 1472
	add	x0, x26, 524
	blr	x3
	mov	w0, 1
	strb	w0, [x19, 14]
	b	.L730
	.p2align 3
.L879:
	ldr	w0, [x19, 12832]
	cbnz	w0, .L762
.L760:
	ldr	w0, [x19, 12968]
	mov	x2, 64
	str	w0, [x20, 580]
	add	x1, x26, 816
	ldr	x3, [x21, 104]
	ldr	w0, [x19, 13100]
	str	w0, [x20, 584]
	add	x0, x20, 588
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 64
	add	x1, x26, 684
	add	x0, x20, 716
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x26, 880
	add	x0, x20, 844
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x26, 1008
	add	x0, x20, 1100
	blr	x3
	ldr	w0, [x19, 12832]
	cbnz	w0, .L762
	ldr	x3, [x21, 104]
	add	x1, x26, 1136
	mov	x2, 64
	add	x0, x20, 652
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x26, 748
	mov	x2, 64
	add	x0, x20, 780
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x26, 1200
	mov	x2, 128
	add	x0, x20, 972
	blr	x3
	ldr	x3, [x21, 104]
	mov	x2, 128
	add	x1, x26, 1328
	add	x0, x20, 1228
	blr	x3
	b	.L762
	.p2align 3
.L776:
	strb	wzr, [x26, 1]
	b	.L777
	.p2align 3
.L881:
	ldr	w1, [x20, 92]
	mov	x0, 0
	str	w1, [x19, 11140]
	b	.L791
	.p2align 3
.L781:
	lsl	w0, w6, 2
	mov	w13, 1
	sub	w0, w0, w6
	add	w1, w0, w0, lsr 31
	cmp	w12, w1, asr 1
	ble	.L782
	cmp	w12, w6, lsl 1
	mov	w13, 2
	ble	.L782
	cmp	w12, w0
	mov	w13, 3
	ble	.L782
	ldr	x1, .LC202
	mov	w3, w6
	mov	w2, w12
	mov	w0, 1
	str	x4, [x29, 104]
	str	w13, [x29, 112]
	str	w14, [x29, 120]
	str	x11, [x29, 128]
	str	w7, [x29, 136]
	str	x10, [x29, 144]
	stp	w9, w5, [x29, 152]
	str	x8, [x29, 160]
	str	w6, [x29, 168]
	bl	dprint_vfmw
	ldr	w13, [x29, 112]
	ldr	w14, [x29, 120]
	ldr	w7, [x29, 136]
	ldp	w9, w5, [x29, 152]
	ldr	w6, [x29, 168]
	ldr	x4, [x29, 104]
	ldr	x11, [x29, 128]
	ldr	x10, [x29, 144]
	ldr	x8, [x29, 160]
	b	.L782
	.p2align 3
.L779:
	lsl	w0, w5, 2
	mov	w14, 1
	sub	w0, w0, w5
	add	w1, w0, w0, lsr 31
	cmp	w2, w1, asr 1
	ble	.L780
	cmp	w2, w5, lsl 1
	mov	w14, 2
	ble	.L780
	cmp	w2, w0
	mov	w14, 3
	ble	.L780
	ldr	x1, .LC200
	mov	w3, w5
	mov	w0, 1
	str	x4, [x29, 104]
	str	w14, [x29, 112]
	str	x11, [x29, 120]
	str	w9, [x29, 128]
	str	x10, [x29, 136]
	str	w6, [x29, 144]
	stp	w7, w12, [x29, 152]
	str	x8, [x29, 160]
	str	w5, [x29, 168]
	bl	dprint_vfmw
	ldr	w14, [x29, 112]
	ldr	w9, [x29, 128]
	ldr	w6, [x29, 144]
	ldp	w7, w12, [x29, 152]
	ldr	w5, [x29, 168]
	ldr	x4, [x29, 104]
	ldr	x11, [x29, 120]
	ldr	x10, [x29, 136]
	ldr	x8, [x29, 160]
	b	.L780
	.p2align 3
.L784:
	asr	w0, w28, 1
	mov	w2, 0
	add	w1, w0, w27, lsl 2
	mov	w3, 0
	mov	w8, 0
	sdiv	w1, w1, w28
	stp	wzr, wzr, [x24, 72]
	sub	w1, w1, #4
	stp	wzr, w1, [x24, 80]
	b	.L785
.L733:
	ldr	w0, [x19, 12884]
	cbnz	w0, .L792
	mov	w0, 1
	b	.L744
.L770:
	ldr	w4, [x20, 72]
	mov	x1, 0
	cbz	w4, .L773
	mov	w0, 0
	.p2align 2
.L775:
	add	x2, x19, x0, sxtw 3
	add	w0, w0, 1
	ldr	x2, [x2, 3200]
	ldr	x2, [x2, 24]
	add	x3, x2, 88
	ldr	w2, [x2, 32]
	cmp	w2, wzr
	csel	x1, x1, x3, ne
	cmp	w0, w4
	bne	.L775
	b	.L773
.L880:
	str	wzr, [x26, 4]
	strb	wzr, [x20, 1356]
	b	.L769
.L793:
	mov	w23, -1
	b	.L824
.L871:
	ldr	x1, .LC197
	mov	w2, w0
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L824
	.size	HEVC_WriteSliceMsg, .-HEVC_WriteSliceMsg
	.align	3
.LC197:
	.xword	.LC196
	.align	3
.LC198:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC200:
	.xword	.LC199
	.align	3
.LC202:
	.xword	.LC201
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetVirAddr
	.type	HEVC_GetVirAddr, %function
HEVC_GetVirAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x19, x20, uxtw 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetVirAddr, .-HEVC_GetVirAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetPhyAddr
	.type	HEVC_GetPhyAddr, %function
HEVC_GetPhyAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	w0, w19, w20, lsl 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetPhyAddr, .-HEVC_GetPhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CfgVDMReg
	.type	HEVC_CfgVDMReg, %function
HEVC_CfgVDMReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 4884]
	ldr	w0, [x19, 204]
	ldr	w2, [x19, 4888]
	cmp	w1, wzr
	str	w0, [x19, 10040]
	cset	w1, eq
	str	w2, [x19, 8884]
	mov	w0, 0
	str	w1, [x19, 8892]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_CfgVDMReg, .-HEVC_CfgVDMReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsRefForCurrPic
	.type	HEVC_IsRefForCurrPic, %function
HEVC_IsRefForCurrPic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L915
.L886:
	ldr	w3, [x19, 5604]
	ldr	w4, [x19, 164]
	tbnz	w3, #31, .L889
	cmp	w3, w4
	bge	.L889
	ldr	x0, [x19, 2968]
	mov	w1, 5036
	ldr	w4, [x19, 160]
	smaddl	x3, w3, w1, x0
	ldr	w3, [x3, 32]
	tbnz	w3, #31, .L892
	cmp	w3, w4
	bge	.L892
	add	x20, x19, 4096
	ldr	x2, [x19, 2960]
	mov	w4, 12668
	ldr	w5, [x19, 6500]
	ldr	w6, [x20, 2408]
	mov	w0, 1
	smaddl	x3, w3, w4, x2
	ldr	w4, [x20, 2412]
	add	w7, w5, w6
	ldr	w9, [x3, 116]
	cmp	w7, w4
	mov	w3, w7
	lsl	w9, w0, w9
	bcs	.L905
	cmp	w7, 15
	bgt	.L895
	ldr	w8, [x19, 4868]
	sub	w9, w9, #1
	and	w10, w9, w8
	b	.L897
	.p2align 3
.L916:
	cmp	w4, w3
	bls	.L905
	cmp	w3, 16
	beq	.L895
.L897:
	add	x0, x19, x3, sxtw 2
	mov	w1, w8
	add	w3, w3, 1
	ldr	w2, [x0, 5656]
	ldr	w0, [x0, 6600]
	cbnz	w2, .L898
	mov	w1, w10
	and	w0, w0, w9
.L898:
	cmp	w1, w0
	bne	.L916
	mov	w21, 1
.L894:
	cbz	w7, .L908
	ldr	w3, [x19, 5580]
	add	x2, x20, 2440
	ldr	w1, [x20, 2436]
	mov	w4, 0
	ldr	w0, [x19, 4868]
	add	w1, w3, w1
	cmp	w0, w1
	bne	.L903
	b	.L900
	.p2align 3
.L902:
	ldr	w1, [x2], 4
	add	w1, w3, w1
	cmp	w1, w0
	beq	.L900
.L903:
	add	w4, w4, 1
	cmp	w4, w7
	beq	.L908
	cmp	w4, 17
	bne	.L902
	ldr	x1, .LC210
	mov	w3, w4
	mov	w2, 9007
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w21
	b	.L887
	.p2align 3
.L889:
	ldr	x1, .LC204
	mov	w2, 8946
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
.L887:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L915:
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L886
.L900:
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L892:
	ldr	x1, .LC206
	mov	w2, 8958
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L905:
	mov	w21, 0
	b	.L894
	.p2align 3
.L895:
	ldr	x1, .LC208
	mov	w5, w4
	mov	w2, 8978
	mov	w4, 16
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	ldr	w5, [x19, 6500]
	ldr	w6, [x20, 2408]
	add	w7, w6, w5
	b	.L894
	.p2align 3
.L908:
	mov	w0, w21
	b	.L887
	.size	HEVC_IsRefForCurrPic, .-HEVC_IsRefForCurrPic
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC206:
	.xword	.LC205
	.align	3
.LC208:
	.xword	.LC207
	.align	3
.LC210:
	.xword	.LC209
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicVPSRefresh
	.type	HEVC_IsPicVPSRefresh, %function
HEVC_IsPicVPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 3000]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	beq	.L920
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L920:
	ldrb	w0, [x19, 2]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicVPSRefresh, .-HEVC_IsPicVPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicVPS
	.type	HEVC_UpdatePicVPS, %function
HEVC_UpdatePicVPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, 24912
	mov	x20, -24912
	bl	_mcount
	strb	wzr, [x22, 2]
	ldr	x3, .LC211
	mov	x1, x22
	ldr	w0, [x19, 156]
	mov	x2, 24912
	ldr	x4, [x19, 2952]
	ldr	x3, [x3, 104]
	smaddl	x0, w0, w21, x20
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x19, 156]
	ldr	x1, [x19, 2952]
	smaddl	x0, w0, w21, x20
	add	x0, x1, x0
	str	x0, [x19, 3000]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_UpdatePicVPS, .-HEVC_UpdatePicVPS
	.align	3
.LC211:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicSPSRefresh
	.type	HEVC_IsPicSPSRefresh, %function
HEVC_IsPicSPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 3008]
	ldr	w0, [x19, 56]
	ldr	w1, [x1, 56]
	cmp	w1, w0
	beq	.L925
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L925:
	ldrb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicSPSRefresh, .-HEVC_IsPicSPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicSPS
	.type	HEVC_UpdatePicSPS, %function
HEVC_UpdatePicSPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, 12668
	mov	x20, -12668
	bl	_mcount
	strb	wzr, [x22]
	ldr	x3, .LC212
	mov	x1, x22
	ldr	w0, [x19, 160]
	mov	x2, 12668
	ldr	x4, [x19, 2960]
	ldr	x3, [x3, 104]
	smaddl	x0, w0, w21, x20
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x19, 160]
	ldr	x1, [x19, 2960]
	smaddl	x0, w0, w21, x20
	add	x0, x1, x0
	str	x0, [x19, 3008]
	ldr	w1, [x0, 56]
	str	w1, [x19, 288]
	ldr	w1, [x0, 64]
	str	w1, [x19, 292]
	ldr	w1, [x0, 68]
	str	w1, [x19, 296]
	ldr	w1, [x0, 128]
	str	w1, [x19, 300]
	ldr	w1, [x0, 88]
	str	w1, [x19, 304]
	ldr	w0, [x0, 96]
	str	w0, [x19, 308]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_UpdatePicSPS, .-HEVC_UpdatePicSPS
	.align	3
.LC212:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsPicPPSRefresh
	.type	HEVC_IsPicPPSRefresh, %function
HEVC_IsPicPPSRefresh:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x1, [x20, 3016]
	ldr	w0, [x19, 28]
	ldr	w1, [x1, 28]
	cmp	w1, w0
	beq	.L930
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L930:
	ldrb	w0, [x19, 1]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsPicPPSRefresh, .-HEVC_IsPicPPSRefresh
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdatePicPPS
	.type	HEVC_UpdatePicPPS, %function
HEVC_UpdatePicPPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x2
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	strb	wzr, [x19, 1]
	ldrb	w0, [x19, 13]
	cbz	w0, .L932
	ldrb	w0, [x19, 15]
	cbnz	w0, .L952
	ldr	w0, [x19, 68]
	ldr	w2, [x21, 188]
	sub	w3, w0, #1
	add	x1, x19, x0, sxtw 1
	cmp	w3, wzr
	strh	w2, [x1, 170]
	ble	.L944
	sub	w4, w0, #2
	add	x0, x19, 88
	add	x4, x4, 45
	add	x4, x19, x4, lsl 1
	.p2align 2
.L943:
	ldrsh	w3, [x0]
	add	x0, x0, 2
	strh	w3, [x0, 82]
	cmp	x0, x4
	ldrh	w2, [x1, 170]
	sub	w2, w2, w3
	strh	w2, [x1, 170]
	bne	.L943
.L944:
	ldr	w0, [x19, 72]
	ldr	w1, [x21, 192]
	sub	w2, w0, #1
	add	x3, x19, x0, sxtw 1
	cmp	w2, wzr
	strh	w1, [x3, 210]
	ble	.L939
	sub	w4, w0, #2
	add	x0, x19, 128
	add	x4, x4, 65
	add	x4, x19, x4, lsl 1
	.p2align 2
.L945:
	ldrsh	w2, [x0]
	add	x0, x0, 2
	strh	w2, [x0, 82]
	cmp	x4, x0
	ldrh	w1, [x3, 210]
	sub	w1, w1, w2
	strh	w1, [x3, 210]
	bne	.L945
	b	.L939
	.p2align 3
.L932:
	ldr	w0, [x21, 188]
	strh	w0, [x19, 172]
	ldr	w0, [x21, 192]
	strh	w0, [x19, 212]
.L939:
	ldr	w0, [x20, 164]
	mov	w22, 5036
	ldr	x1, .LC215
	mov	x21, -5036
	ldr	x4, [x20, 2968]
	mov	x2, 5036
	smaddl	x0, w0, w22, x21
	ldr	x3, [x1, 104]
	mov	x1, x19
	add	x0, x4, x0
	blr	x3
	ldr	w0, [x20, 164]
	ldr	x1, [x20, 2968]
	smaddl	x0, w0, w22, x21
	add	x0, x1, x0
	str	x0, [x20, 3016]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L952:
	ldr	w4, [x19, 68]
	add	x1, x19, 172
	mov	w3, 0
	cmp	w4, wzr
	ble	.L938
	.p2align 2
.L947:
	add	w3, w3, 1
	ldr	w5, [x21, 188]
	sub	w0, w3, #1
	cmp	w3, w4
	mul	w2, w3, w5
	mul	w0, w0, w5
	udiv	w2, w2, w4
	udiv	w0, w0, w4
	sub	w0, w2, w0
	strh	w0, [x1], 2
	bne	.L947
.L938:
	ldr	w4, [x19, 72]
	add	x1, x19, 212
	mov	w3, 0
	cmp	w4, wzr
	ble	.L939
	.p2align 2
.L946:
	add	w3, w3, 1
	ldr	w5, [x21, 192]
	sub	w0, w3, #1
	cmp	w3, w4
	mul	w2, w3, w5
	mul	w0, w0, w5
	udiv	w2, w2, w4
	udiv	w0, w0, w4
	sub	w0, w2, w0
	strh	w0, [x1], 2
	bne	.L946
	b	.L939
	.size	HEVC_UpdatePicPPS, .-HEVC_UpdatePicPPS
	.align	3
.LC215:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitPicInfo
	.type	HEVC_InitPicInfo, %function
HEVC_InitPicInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x3, x19, 4096
	mov	w2, 1
	mov	w1, -1
	ldr	x0, .LC216
	strb	w2, [x3, 761]
	str	w1, [x19, 4888]
	ldr	w4, [x19, 5596]
	ldr	x1, [x19, 3008]
	ldr	w2, [x19, 5580]
	str	w4, [x19, 4860]
	str	w2, [x19, 4868]
	ldrsw	x4, [x19, 276]
	ldr	w5, [x1, 64]
	str	w5, [x19, 4876]
	ldr	x0, [x0, x4, lsl 3]
	ldr	w4, [x1, 68]
	str	w4, [x19, 4880]
	str	wzr, [x19, 4884]
	ldrsb	w4, [x0, 44]
	cmp	w4, 1
	beq	.L966
.L954:
	ldr	w0, [x19, 2368]
	cbnz	w0, .L957
	ldr	x0, [x19, 3040]
	mov	x1, -1
	ldr	x2, [x0, 64]
	str	x2, [x19, 5512]
	ldr	x2, [x0, 80]
	str	x2, [x19, 5520]
	ldr	x2, [x0, 96]
	str	x2, [x19, 5528]
	ldr	w2, [x0, 112]
	str	w2, [x19, 4928]
	ldr	w2, [x0, 116]
	str	w2, [x19, 4932]
	ldr	w2, [x0, 120]
	str	w2, [x19, 4936]
	ldr	w2, [x0, 136]
	str	w2, [x19, 4940]
	ldrb	w2, [x0, 56]
	strb	w2, [x3, 1464]
	str	x1, [x0, 64]
	ldr	x1, [x19, 3008]
.L957:
	ldr	w0, [x1, 64]
	str	w0, [x19, 4996]
	add	x0, x3, 832
	ldr	w2, [x19, 5600]
	ldr	w4, [x1, 68]
	str	w4, [x19, 5000]
	str	w2, [x19, 4864]
	str	wzr, [x19, 4980]
	str	w2, [x19, 5112]
	ldr	w5, [x1, 60]
	ldr	w4, [x1, 2084]
	ldrb	w2, [x3, 896]
	cmp	w5, 1
	bfi	w2, w4, 5, 3
	cset	w4, ne
	bfi	w2, w4, 2, 3
	strb	w2, [x3, 896]
	ldr	w1, [x1, 2068]
	and	w1, w1, 7
	bl	SetAspectRatio
	ldr	w0, [x19, 2368]
	cmp	w0, 1
	beq	.L953
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5580]
	str	w1, [x0, 8]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 4992]
	str	w1, [x0, 152]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 4980]
	str	w1, [x0, 140]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5032]
	str	w1, [x0, 192]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5028]
	str	w1, [x0, 188]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 4996]
	str	w1, [x0, 156]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5000]
	str	w1, [x0, 160]
	ldr	x1, [x19, 4920]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetDispPhyFs
	cbz	x0, .L959
	ldr	w3, [x19, 4980]
	mov	w1, 0
	ldr	w2, [x0, 4]
	cmp	w3, wzr
	ldr	w0, [x19, 276]
	cset	w3, ne
	bl	FSP_SetStoreType
.L959:
	ldr	x0, [x19, 3008]
	ldr	x4, [x19, 4920]
	ldr	w1, [x0, 72]
	str	w1, [x19, 5148]
	ldr	w3, [x0, 76]
	str	w3, [x19, 5152]
	ldr	w6, [x0, 80]
	str	w6, [x19, 5156]
	ldr	w5, [x0, 84]
	str	w5, [x19, 5160]
	ldr	w2, [x0, 64]
	sub	w1, w2, w1
	sub	w1, w1, w3
	str	w1, [x19, 5004]
	ldr	w3, [x0, 68]
	sub	w2, w3, w6
	sub	w2, w2, w5
	str	w2, [x19, 5008]
	ldr	w2, [x0, 60]
	str	w2, [x19, 5092]
	ldr	w2, [x0, 88]
	str	w2, [x19, 5096]
	ldr	w0, [x0, 96]
	str	w0, [x19, 5100]
	ldr	w0, [x4, 172]
	str	w0, [x19, 5012]
	ldr	w0, [x4, 176]
	str	w0, [x19, 5016]
	str	w1, [x4, 164]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5008]
	str	w1, [x0, 168]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5012]
	str	w1, [x0, 172]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5016]
	str	w1, [x0, 176]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5096]
	str	w1, [x0, 256]
	ldr	x0, [x19, 4920]
	ldr	w1, [x19, 5100]
	str	w1, [x0, 260]
	str	wzr, [x19, 4872]
.L953:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L966:
	ldr	x4, [x0, 160]
	mov	x0, 1
	movk	x0, 0x2, lsl 32
	cmp	x4, x0
	bne	.L954
	add	x0, x19, 12288
	ldrb	w0, [x0, 464]
	cmp	w0, 1
	bne	.L954
	ldr	x4, [x19, 12784]
	ldr	x0, [x19, 12800]
	cmp	x4, x0
	bls	.L955
	sub	x5, x4, x0
	cmp	x5, 16
	bls	.L955
.L956:
	ldr	w4, [x19, 284]
	sub	w2, w2, w4
	add	x0, x0, x2, sxtw
	str	x0, [x19, 12784]
	b	.L954
	.p2align 3
.L955:
	cmp	x4, x0
	bcs	.L954
	sub	x4, x0, x4
	cmp	x4, 16
	bls	.L954
	b	.L956
	.size	HEVC_InitPicInfo, .-HEVC_InitPicInfo
	.align	3
.LC216:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RepairList
	.type	HEVC_RepairList, %function
HEVC_RepairList:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x26, 5588]
	cmp	w3, 1
	beq	.L969
	cmp	w3, 2
	beq	.L985
	cbz	w3, .L984
	ldr	x2, .LC217
	mov	w0, 1
	ldr	x1, .LC219
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L972:
	ldr	x0, [x26, 3040]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L980
	mov	w0, 1
	str	w0, [x28]
	ldr	x0, [x26, 4920]
	add	x0, x0, 56
	str	x0, [x23, -8]
	.p2align 2
.L980:
	add	w27, w27, 1
	add	x28, x28, 4
	cmp	w27, w22
	add	x23, x23, 136
	bcc	.L982
.L985:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 112
	ret
.L984:
	mov	w22, 2
.L971:
	ldr	x21, .LC217
	add	x28, x26, 4096
	add	x28, x28, 1540
	add	x23, x26, 3072
	add	x0, x21, 416
	mov	w27, 0
	str	x0, [x29, 104]
	.p2align 2
.L982:
	ldr	w1, [x28]
	cbz	w1, .L972
	ldr	x2, [x23, -8]
	cbnz	x2, .L986
	mov	x3, x23
	mov	w0, 0
	b	.L974
	.p2align 3
.L976:
	ldr	x24, [x3], 8
	cbnz	x24, .L991
.L974:
	add	w0, w0, 1
	cmp	w1, w0
	bne	.L976
	mov	w20, -1
.L975:
	ldr	x0, [x26, 3040]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L977
	ldr	x24, [x26, 4920]
	add	x24, x24, 56
.L973:
	mov	x0, x2
	uxtw	x25, w27
	mov	w19, 0
	lsl	x21, x25, 4
	cbz	x0, .L992
	.p2align 2
.L978:
	add	w19, w19, 1
	add	x0, x21, x25
	cmp	w1, w19
	add	x0, x0, x19, uxtw
	bls	.L980
	add	x0, x26, x0, lsl 3
	ldr	x0, [x0, 3064]
	cbnz	x0, .L978
.L992:
	ldr	x1, .LC223
	mov	w4, w19
	ldr	x2, [x29, 104]
	mov	w5, w20
	mov	w3, w27
	mov	w0, 1
	bl	dprint_vfmw
	add	x0, x21, x25
	add	x0, x0, x19, uxtw
	add	x0, x26, x0, lsl 3
	str	x24, [x0, 3064]
	ldr	w1, [x28]
	b	.L978
	.p2align 3
.L991:
	sxtb	w20, w0
	cmn	w20, #1
	ccmp	x24, xzr, 4, ne
	bne	.L973
	b	.L975
	.p2align 3
.L986:
	mov	x24, x2
	mov	w20, 0
	b	.L973
.L969:
	mov	w22, w3
	b	.L971
.L977:
	ldr	x2, .LC217
	mov	w3, w27
	ldr	x1, .LC221
	mov	w0, 1
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	HEVC_RepairList, .-HEVC_RepairList
	.align	3
.LC217:
	.xword	.LANCHOR0
	.align	3
.LC219:
	.xword	.LC218
	.align	3
.LC221:
	.xword	.LC220
	.align	3
.LC223:
	.xword	.LC222
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitListX
	.type	HEVC_InitListX, %function
HEVC_InitListX:
	stp	x29, x30, [sp, -320]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1056
	ldr	x20, .LC225
	add	x21, x29, 48
	mov	x2, 272
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x20, 96]
	blr	x3
	ldr	w0, [x19, 3392]
	cbz	w0, .L1057
	sub	w3, w0, #1
	mov	w6, 0
	add	x3, x3, 479
	add	x0, x19, 3824
	add	x3, x19, x3, lsl 3
	b	.L997
	.p2align 3
.L996:
	cmp	x0, x3
	beq	.L995
.L997:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L996
	ldr	w2, [x1, 60]
	cbnz	w2, .L996
	ldr	w2, [x1, 64]
	cmp	w2, 1
	bne	.L996
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x6, uxtw 3
	cmp	x0, x3
	sub	x2, x2, #4096
	add	w6, w6, 1
	str	x1, [x2, 3824]
	bne	.L997
	.p2align 2
.L995:
	ldrb	w8, [x19, 1]
	sub	w7, w6, #1
	cbz	w8, .L998
	ldr	w0, [x19, 3404]
	cbz	w0, .L1058
	sub	w4, w0, #1
	mov	w3, w6
	add	x4, x4, 428
	add	x0, x19, 3416
	add	x4, x19, x4, lsl 3
	b	.L1001
	.p2align 3
.L1000:
	cmp	x4, x0
	beq	.L1088
.L1001:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L1000
	ldr	w2, [x1, 72]
	cmp	w2, 1
	bne	.L1000
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x3, uxtw 3
	cmp	x4, x0
	sub	x2, x2, #4096
	add	w3, w3, 1
	str	x1, [x2, 3824]
	bne	.L1001
	.p2align 2
.L1088:
	sub	w9, w3, w6
.L999:
	ldr	w5, [x19, 3396]
	cbnz	w5, .L1049
	mov	w4, w9
	mov	w11, 0
	b	.L1002
	.p2align 3
.L998:
	ldr	w5, [x19, 3396]
	mov	w3, w6
	mov	w9, 0
	cbz	w5, .L1089
.L1049:
	add	x1, x19, 3960
	mov	w0, 0
	b	.L1004
	.p2align 3
.L1003:
	cmp	w0, w5
	bcs	.L1090
.L1004:
	ldr	x2, [x1]
	add	w0, w0, 1
	add	x1, x1, 8
	ldrb	w4, [x2, 1]
	cmp	w4, 1
	bne	.L1003
	ldr	w4, [x2, 60]
	cbnz	w4, .L1003
	ldr	w4, [x2, 64]
	cmp	w4, 1
	bne	.L1003
	add	x4, x29, 320
	add	x2, x2, 56
	add	x4, x4, x3, uxtw 3
	cmp	w0, w5
	sub	x4, x4, #4096
	add	w3, w3, 1
	str	x2, [x4, 3824]
	bcc	.L1004
	.p2align 2
.L1090:
	cbz	w8, .L1005
	sub	w4, w3, w6
	sub	w11, w4, w9
.L1002:
	ldr	w10, [x19, 3388]
	add	w5, w9, w11
	cbz	w10, .L1007
.L1008:
	add	x1, x19, 4096
	mov	w0, 0
	b	.L1011
	.p2align 3
.L1010:
	cmp	w0, w10
	bcs	.L1091
.L1011:
	ldr	x2, [x1]
	add	w0, w0, 1
	add	x1, x1, 8
	ldrb	w4, [x2, 1]
	cmp	w4, 1
	bne	.L1010
	ldr	w4, [x2, 60]
	cmp	w4, 1
	bne	.L1010
	ldr	w12, [x2, 64]
	add	x4, x29, 320
	add	x4, x4, x3, uxtw 3
	add	x2, x2, 56
	sub	x4, x4, #4096
	cbnz	w12, .L1010
	str	x2, [x4, 3824]
	cmp	w0, w10
	add	w3, w3, 1
	bcc	.L1011
	.p2align 2
.L1091:
	sub	w4, w3, w6
	cbnz	w8, .L1007
	sub	w4, w4, w11
.L1009:
	mov	w0, 0
.L1016:
	cbz	w3, .L1092
.L1017:
	ldr	w10, [x19, 5588]
	cbnz	w10, .L1019
	cbz	w8, .L1093
	add	w12, w6, w9
	cbz	w11, .L1062
	add	x13, x21, 136
	add	w14, w11, w12
	mov	w1, w12
	.p2align 2
.L1024:
	add	x2, x29, 320
	add	x2, x2, x1, uxtw 3
	add	w1, w1, 1
	sub	x2, x2, #4096
	cmp	w14, w1
	ldr	x2, [x2, 3824]
	str	x2, [x13], 8
	bne	.L1024
	mov	w1, w11
.L1023:
	cbz	w0, .L1063
	add	w2, w11, w4
	add	w0, w0, w1
	add	w12, w2, w12
	.p2align 2
.L1026:
	add	x2, x29, 320
	add	x13, x29, 320
	add	x2, x2, x12, uxtw 3
	add	x13, x13, x1, uxtw 3
	sub	x2, x2, #4096
	add	w1, w1, 1
	cmp	w0, w1
	add	w12, w12, 1
	ldr	x2, [x2, 3824]
	str	x2, [x13, -136]
	bne	.L1026
.L1025:
	mov	w1, w0
	cbz	w6, .L1029
.L1051:
	mov	x2, 0
	.p2align 2
.L1028:
	add	x1, x29, 320
	ldr	x13, [x21, x2, lsl 3]
	add	x12, x1, x0, uxtw 3
	add	x2, x2, 1
	cmp	w6, w2
	add	w1, w0, 1
	mov	w0, w1
	str	x13, [x12, -136]
	bhi	.L1028
	cbnz	w8, .L1029
.L1052:
	cbz	w4, .L1031
	add	w7, w11, w7
	add	w4, w4, w1
	mov	w2, w1
	.p2align 2
.L1035:
	add	w5, w2, 1
	add	x0, x29, 320
	add	x6, x0, x2, uxtw 3
	sub	w0, w5, w1
	add	w0, w0, w7
	mov	w2, w5
	cmp	w5, w4
	add	x5, x29, 320
	add	x0, x5, x0, lsl 3
	sub	x0, x0, #4096
	ldr	x0, [x0, 3824]
	str	x0, [x6, -136]
	bne	.L1035
.L1031:
	ldr	w5, [x19, 5644]
	ldr	w7, [x19, 5648]
	str	w5, [x19, 5636]
	str	w7, [x19, 5640]
	cbnz	w5, .L1055
	.p2align 2
.L1053:
	cbz	w7, .L1041
	add	x0, x19, 4096
	add	x4, x19, 3200
	add	x2, x0, 2700
	mov	w1, 0
	ldrb	w6, [x0, 2569]
	.p2align 2
.L1044:
	cbz	w6, .L1042
	ldr	w0, [x2]
.L1043:
	add	x8, x29, 320
	add	w1, w1, 1
	add	x0, x8, x0, uxtw 3
	cmp	w7, w1
	add	x2, x2, 4
	ldr	x0, [x0, -136]
	str	x0, [x4], 8
	bne	.L1044
	mov	w0, w5
.L1040:
	cmp	w0, 16
	bhi	.L1065
	.p2align 2
.L1046:
	add	x1, x19, x0, uxtw 3
	ldr	x2, [x19, 3064]
	add	w0, w0, 1
	cmp	w0, 16
	str	x2, [x1, 3064]
	bls	.L1046
.L1065:
	cmp	w7, 16
	mov	w0, w7
	bhi	.L1047
	.p2align 2
.L1048:
	add	x1, x19, x0, uxtw 3
	ldr	x2, [x19, 3200]
	add	w0, w0, 1
	cmp	w0, 17
	str	x2, [x1, 3200]
	bne	.L1048
.L1047:
	mov	w0, 0
.L1086:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L1007:
	ldr	w0, [x19, 3408]
	sub	w4, w4, w11
	sub	w4, w4, w9
	cbz	w0, .L1009
	sub	w10, w0, #1
	add	x0, x19, 3552
	add	x10, x10, 445
	add	x10, x19, x10, lsl 3
	b	.L1015
	.p2align 3
.L1014:
	cmp	x0, x10
	beq	.L1094
.L1015:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 1
	bne	.L1014
	add	x2, x29, 320
	add	x1, x1, 56
	add	x2, x2, x3, uxtw 3
	cmp	x0, x10
	sub	x2, x2, #4096
	add	w3, w3, 1
	str	x1, [x2, 3824]
	bne	.L1015
.L1094:
	sub	w0, w3, w6
	sub	w0, w0, w11
	sub	w0, w0, w9
	sub	w0, w0, w4
	cbnz	w3, .L1017
.L1092:
	ldr	x3, [x20, 96]
	mov	x2, 272
	mov	w1, 0
	add	x0, x19, 3064
	str	wzr, [x19, 5636]
	str	wzr, [x19, 5640]
	blr	x3
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L1047
	ldr	x1, [x19, 4920]
	mov	w2, 1
	mov	w0, 0
	str	w2, [x19, 5636]
	add	x1, x1, 56
	str	x1, [x19, 3064]
	b	.L1086
	.p2align 3
.L1005:
	sub	w11, w3, w6
	add	w5, w9, w11
.L1050:
	ldr	w10, [x19, 3388]
	cbnz	w10, .L1008
	mov	w4, 0
	mov	w0, 0
	b	.L1016
	.p2align 3
.L1019:
	ldr	w5, [x19, 5644]
	ldr	w7, [x19, 5648]
	str	w5, [x19, 5636]
	str	w7, [x19, 5640]
	cbz	w5, .L1036
.L1055:
	add	x1, x19, 4096
	add	x4, x19, 3064
	add	x2, x1, 2572
	mov	w0, 0
	ldrb	w6, [x1, 2568]
	.p2align 2
.L1039:
	cbz	w6, .L1037
	ldr	w1, [x2]
.L1038:
	add	x8, x29, 320
	add	w0, w0, 1
	add	x1, x8, x1, uxtw 3
	cmp	w0, w5
	sub	x1, x1, #4096
	add	x2, x2, 4
	ldr	x1, [x1, 3824]
	str	x1, [x4], 8
	bne	.L1039
	cbnz	w10, .L1040
	b	.L1053
	.p2align 3
.L1037:
	udiv	w1, w0, w3
	msub	w1, w1, w3, w0
	b	.L1038
	.p2align 3
.L1042:
	udiv	w0, w1, w3
	msub	w0, w0, w3, w1
	b	.L1043
	.p2align 3
.L1093:
	mov	w0, 0
	cbz	w11, .L1022
	add	x2, x21, 136
	add	w12, w11, w6
	mov	w0, w6
	.p2align 2
.L1027:
	add	x1, x29, 320
	add	x1, x1, x0, uxtw 3
	add	w0, w0, 1
	sub	x1, x1, #4096
	cmp	w12, w0
	ldr	x1, [x1, 3824]
	str	x1, [x2], 8
	bne	.L1027
	mov	w0, w11
.L1022:
	mov	w1, w0
	cbnz	w6, .L1051
	b	.L1052
	.p2align 3
.L1029:
	cbz	w4, .L1064
	add	w5, w6, w5
	add	w4, w4, w1
	.p2align 2
.L1033:
	add	x0, x29, 320
	add	x2, x29, 320
	add	x0, x0, x5, uxtw 3
	add	x2, x2, x1, uxtw 3
	sub	x0, x0, #4096
	add	w1, w1, 1
	cmp	w4, w1
	add	w5, w5, 1
	ldr	x0, [x0, 3824]
	str	x0, [x2, -136]
	bne	.L1033
.L1032:
	cbz	w9, .L1031
	add	w9, w4, w9
	mov	w1, w4
	.p2align 2
.L1034:
	add	w2, w1, 1
	add	x0, x29, 320
	add	x5, x0, x1, uxtw 3
	sub	w0, w2, w4
	add	w0, w0, w7
	mov	w1, w2
	cmp	w2, w9
	add	x2, x29, 320
	add	x0, x2, x0, lsl 3
	sub	x0, x0, #4096
	ldr	x0, [x0, 3824]
	str	x0, [x5, -136]
	bne	.L1034
	ldr	w5, [x19, 5644]
	ldr	w7, [x19, 5648]
	str	w5, [x19, 5636]
	str	w7, [x19, 5640]
	cbnz	w5, .L1055
	b	.L1053
.L1041:
	ldr	x3, [x20, 104]
	mov	x2, 136
	add	x1, x19, 3064
	add	x0, x19, 3200
	blr	x3
	ldr	w7, [x19, 5636]
	str	w7, [x19, 5640]
	mov	w0, w7
	b	.L1040
.L1057:
	mov	w6, 0
	b	.L995
.L1089:
	mov	w11, 0
	mov	w9, 0
	b	.L1050
.L1058:
	mov	w3, w6
	mov	w9, 0
	b	.L999
.L1036:
	mov	w0, 0
	b	.L1046
.L1056:
	mov	w0, -1
	b	.L1086
.L1064:
	mov	w4, w1
	b	.L1032
.L1063:
	mov	w0, w1
	b	.L1025
.L1062:
	mov	w1, 0
	b	.L1023
	.size	HEVC_InitListX, .-HEVC_InitListX
	.align	3
.LC225:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecList
	.type	HEVC_DecList, %function
HEVC_DecList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5588]
	cmp	w0, 2
	beq	.L1101
	mov	x0, x19
	bl	HEVC_InitListX
	cbnz	w0, .L1102
	mov	x0, x19
	bl	HEVC_RepairList
	mov	w1, 0
	cbnz	w0, .L1103
.L1097:
	mov	w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1101:
	str	wzr, [x19, 5636]
	mov	w1, 0
	str	wzr, [x19, 5640]
	mov	w0, w1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1102:
	ldr	x1, .LC227
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L1097
.L1103:
	ldr	x1, .LC229
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L1097
	.size	HEVC_DecList, .-HEVC_DecList
	.align	3
.LC227:
	.xword	.LC226
	.align	3
.LC229:
	.xword	.LC228
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ArrangeMem
	.type	HEVC_ArrangeMem, %function
HEVC_ArrangeMem:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 3008]
	mov	w1, 8160
	ldr	w20, [x0, 128]
	ldr	w21, [x0, 192]
	ldr	w0, [x0, 188]
	lsl	w21, w21, w20
	sub	w2, w21, #32
	lsl	w20, w0, w20
	sub	w0, w20, #32
	cmp	w2, w1
	ccmp	w0, w1, 2, ls
	bhi	.L1105
	ldr	x3, .LC230
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 3040]
	stp	w20, w21, [x29, 60]
	stp	w20, w21, [x29, 68]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L1114
	ldrsb	w2, [x19, 3376]
	strb	w2, [x29, 57]
.L1110:
	ldr	w0, [x19, 276]
	add	x1, x29, 56
	strb	w2, [x29, 59]
	bl	FSP_ConfigInstance
	cbnz	w0, .L1115
	ldr	x1, [x19, 3040]
	add	x3, x29, 52
	ldr	w0, [x19, 276]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
.L1112:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1114:
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x29, 57]
	b	.L1110
	.p2align 3
.L1105:
	ldr	x2, .LC231
	mov	w4, w21
	ldr	x1, .LC233
	mov	w3, w20
	add	x2, x2, 432
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	mov	w0, -20
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1115:
	ldr	x2, .LC231
	mov	w0, 1
	ldr	x1, .LC235
	add	x2, x2, 432
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1112
	.size	HEVC_ArrangeMem, .-HEVC_ArrangeMem
	.align	3
.LC230:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC231:
	.xword	.LANCHOR0
	.align	3
.LC233:
	.xword	.LC232
	.align	3
.LC235:
	.xword	.LC234
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveApcStore
	.type	HEVC_RemoveApcStore, %function
HEVC_RemoveApcStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x0, x19, x20, uxtw 3
	ldr	x1, [x0, 3688]
	ldr	w4, [x1, 32]
	cmp	w4, 1
	bhi	.L1119
	ldr	w0, [x1, 24]
	cmp	w0, 15
	bhi	.L1116
	sxtw	x2, w4
	uxtw	x0, w0
	lsl	x3, x2, 5
	mov	w6, 70
	add	x3, x3, x2, lsl 3
	mov	w5, 16
	smaddl	x4, w4, w6, x0
	add	x2, x19, x3, lsl 3
	sub	x2, x2, x3
	add	x4, x19, x4, lsl 2
	add	x0, x2, x0
	add	x0, x0, 12288
	str	wzr, [x4, 14196]
	str	wzr, [x4, 14260]
	str	wzr, [x4, 14324]
	str	wzr, [x4, 14388]
	strb	wzr, [x0, 2164]
	ldr	w0, [x1, 20]
	add	x19, x19, x0, lsl 2
	str	wzr, [x19, 2168]
	str	w5, [x1, 24]
	ldr	w0, [x2, 14192]
	sub	w0, w0, #1
	str	w0, [x2, 14192]
.L1116:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1119:
	ldr	x2, .LC236
	mov	w3, w20
	ldr	x1, .LC238
	mov	w0, 1
	add	x2, x2, 448
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_RemoveApcStore, .-HEVC_RemoveApcStore
	.align	3
.LC236:
	.xword	.LANCHOR0
	.align	3
.LC238:
	.xword	.LC237
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveUnusedApcStore
	.type	HEVC_RemoveUnusedApcStore, %function
HEVC_RemoveUnusedApcStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w1, [x20, 3380]
	cbnz	w1, .L1125
	b	.L1120
	.p2align 3
.L1122:
	add	w19, w19, 1
	cmp	w1, w19
	bls	.L1120
.L1125:
	add	x0, x20, x19, sxtw 3
	ldr	x0, [x0, 3688]
	ldrb	w0, [x0, 1]
	cbnz	w0, .L1122
	mov	w1, w19
	mov	x0, x20
	add	w19, w19, 1
	bl	HEVC_RemoveApcStore
	ldr	w1, [x20, 3380]
	cmp	w1, w19
	bhi	.L1125
.L1120:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_RemoveUnusedApcStore, .-HEVC_RemoveUnusedApcStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ApplyReferencePictureSet
	.type	HEVC_ApplyReferencePictureSet, %function
HEVC_ApplyReferencePictureSet:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	mov	w21, 1
	mov	w25, 0
	bl	_mcount
	ldr	w2, [x23, 5604]
	mov	w5, 5036
	ldr	x1, [x23, 2968]
	mov	w4, 12668
	ldr	x0, [x23, 2960]
	ldr	w3, [x23, 3380]
	smaddl	x1, w2, w5, x1
	ldr	w1, [x1, 32]
	smaddl	x0, w1, w4, x0
	ldr	w0, [x0, 116]
	lsl	w0, w21, w0
	cbz	w3, .L1127
	add	x19, x23, 4096
	mov	w22, w21
	add	x19, x19, 2404
	sub	w26, w0, #1
	b	.L1158
	.p2align 3
.L1130:
	add	w25, w25, 1
	cmp	w3, w25
	bls	.L1127
.L1158:
	add	x24, x23, x25, sxtw 3
	ldr	w0, [x23, 5600]
	ldr	x1, [x24, 3688]
	ldr	w2, [x1, 32]
	cmp	w2, w0
	bne	.L1130
	ldp	w3, w0, [x19]
	ldr	w2, [x19, 8]
	add	w0, w3, w0
	cmp	w0, w2
	mov	w20, w0
	bcs	.L1168
	ldr	w2, [x1, 8]
	mov	w4, 0
	.p2align 2
.L1138:
	add	x0, x23, x20, sxtw 2
	ldr	w3, [x0, 5656]
	cbz	w3, .L1133
	ldr	w3, [x1, 60]
	cbz	w3, .L1134
	ldr	w3, [x0, 6600]
	cmp	w3, w2
	beq	.L1169
.L1134:
	cbnz	w4, .L1166
	ldrb	w3, [x1, 1]
	mov	w4, w2
	ldr	w0, [x0, 6600]
	cmp	w3, wzr
	ccmp	w4, w0, 0, ne
	beq	.L1170
.L1149:
	mov	w3, w2
	mov	w4, 0
.L1137:
	ldr	w0, [x19, 8]
	add	w20, w20, 1
	mov	w2, w3
	cmp	w0, w20
	bhi	.L1138
	ldp	w2, w0, [x19]
	add	w0, w2, w0
.L1132:
	ldr	w5, [x23, 5580]
	cbz	w0, .L1140
	mov	w20, 0
	.p2align 2
.L1142:
	ldr	w0, [x1, 60]
	add	x2, x19, x20, sxtw 2
	add	w20, w20, 1
	cbnz	w0, .L1141
	ldr	w0, [x2, 32]
	add	w0, w5, w0
	cmp	w0, w3
	beq	.L1171
.L1141:
	ldp	w2, w0, [x19]
	add	w0, w2, w0
	cmp	w0, w20
	bhi	.L1142
.L1140:
	cmp	w4, wzr
	ccmp	w3, w5, 4, eq
	beq	.L1167
	strb	wzr, [x1, 1]
	ldr	x0, [x24, 3688]
	str	wzr, [x0, 60]
	ldr	x0, [x24, 3688]
	str	wzr, [x0, 72]
	ldr	x0, [x24, 3688]
	ldr	w1, [x0, 52]
	cmp	w1, 1
	beq	.L1167
	ldr	w1, [x0, 28]
	mov	w2, 0
	ldr	w0, [x23, 276]
	bl	FSP_SetRef
.L1167:
	ldr	w3, [x23, 3380]
	add	w25, w25, 1
	cmp	w3, w25
	bhi	.L1158
.L1127:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1169:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x24, 3688]
	str	wzr, [x0, 72]
	ldr	x0, [x24, 3688]
	str	w21, [x0, 48]
	ldr	x0, [x24, 3688]
	ldr	w1, [x0, 28]
	ldr	w0, [x23, 276]
	bl	FSP_SetRef
.L1135:
	ldr	x1, [x24, 3688]
	mov	w4, 1
	ldr	w3, [x1, 8]
	b	.L1137
	.p2align 3
.L1133:
	ldr	w3, [x1, 60]
	cbz	w3, .L1136
	ldr	w3, [x0, 6600]
	eor	w3, w2, w3
	tst	w3, w26
	beq	.L1172
.L1136:
	cbnz	w4, .L1166
	ldr	w0, [x0, 6600]
	and	w4, w26, w2
	ldrb	w3, [x1, 1]
	and	w0, w26, w0
	cmp	w3, wzr
	ccmp	w4, w0, 0, ne
	bne	.L1149
.L1170:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x24, 3688]
	str	w21, [x0, 60]
	ldr	x0, [x24, 3688]
	str	wzr, [x0, 72]
	ldr	x0, [x24, 3688]
	str	w21, [x0, 48]
	ldr	x0, [x24, 3688]
	ldr	w1, [x0, 28]
	ldr	w0, [x23, 276]
	bl	FSP_SetRef
	ldr	x1, [x24, 3688]
	mov	w4, 1
	ldr	w3, [x1, 8]
	b	.L1137
	.p2align 3
.L1172:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x24, 3688]
	str	wzr, [x0, 72]
	ldr	x0, [x24, 3688]
	str	w21, [x0, 48]
	ldr	x1, [x24, 3688]
	ldr	w0, [x23, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	b	.L1135
	.p2align 3
.L1166:
	mov	w3, w2
	b	.L1137
	.p2align 3
.L1171:
	strb	w22, [x1, 1]
	mov	w2, 1
	ldr	x0, [x24, 3688]
	str	wzr, [x0, 72]
	ldr	x0, [x24, 3688]
	str	w21, [x0, 48]
	ldr	x1, [x24, 3688]
	ldr	w0, [x23, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldr	x1, [x24, 3688]
	mov	w4, 1
	ldr	w5, [x23, 5580]
	ldr	w3, [x1, 8]
	b	.L1141
.L1168:
	mov	w4, 0
	ldr	w3, [x1, 8]
	b	.L1132
	.size	HEVC_ApplyReferencePictureSet, .-HEVC_ApplyReferencePictureSet
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckThatAllRefPicsAreAvailable
	.type	HEVC_CheckThatAllRefPicsAreAvailable, %function
HEVC_CheckThatAllRefPicsAreAvailable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19, 5596]
	sub	w0, w0, #19
	cmp	w0, 2
	bls	.L1175
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.14
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1175:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_CheckThatAllRefPicsAreAvailable, .-HEVC_CheckThatAllRefPicsAreAvailable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetFrmRepeatCount
	.type	HEVC_SetFrmRepeatCount, %function
HEVC_SetFrmRepeatCount:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bls	.L1177
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SetFrmRepeatCount.part.15
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1177:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_SetFrmRepeatCount, .-HEVC_SetFrmRepeatCount
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetFreeFrameStoreNum
	.type	HEVC_GetFreeFrameStoreNum, %function
HEVC_GetFreeFrameStoreNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 12288
	add	x5, x19, 28672
	add	x2, x2, 2464
	add	x5, x5, 640
	mov	w0, 0
	.p2align 2
.L1184:
	ldr	w1, [x2, 48]
	cbnz	w1, .L1180
	cbz	x2, .L1181
	ldr	w4, [x19, 3380]
	cbz	w4, .L1181
	ldr	x1, [x19, 3688]
	cmp	x1, x2
	beq	.L1180
	sub	w4, w4, #1
	mov	x1, x19
	add	x4, x19, x4, lsl 3
	b	.L1182
	.p2align 3
.L1183:
	ldr	x3, [x1, 3688]
	cmp	x3, x2
	beq	.L1180
.L1182:
	cmp	x4, x1
	add	x1, x1, 8
	bne	.L1183
.L1181:
	add	w0, w0, 1
.L1180:
	add	x2, x2, 728
	cmp	x2, x5
	bne	.L1184
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetFreeFrameStoreNum, .-HEVC_GetFreeFrameStoreNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdateReflist
	.type	HEVC_UpdateReflist, %function
HEVC_UpdateReflist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x20, 6500]
	cbz	w1, .L1214
	add	x24, x20, 4096
	mov	w22, 0
	mov	w21, 0
	add	x23, x24, 2404
	mov	w26, 1
	mov	w25, 1
	.p2align 2
.L1200:
	uxtw	x0, w21
	add	x1, x23, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L1196
	add	x0, x0, 8
	ldr	w5, [x20, 3380]
	ldr	w4, [x20, 5580]
	ldr	w0, [x23, x0, lsl 2]
	add	w4, w4, w0
	cbz	w5, .L1196
	add	x1, x20, 3688
	mov	w0, 0
	b	.L1199
	.p2align 3
.L1197:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L1196
.L1199:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	w3, [x2, 8]
	cmp	w4, w3
	bne	.L1197
	ldr	w3, [x2, 32]
	ldr	w6, [x20, 5600]
	cmp	w6, w3
	bne	.L1197
	add	x19, x20, x0, uxtw 3
	strb	w26, [x2, 1]
	ldr	x0, [x19, 3688]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L1242
.L1198:
	str	w25, [x0, 64]
	add	x0, x20, x22, uxtw 3
	add	w22, w22, 1
	ldr	x1, [x19, 3688]
	str	wzr, [x1, 60]
	ldr	x1, [x19, 3688]
	str	x1, [x0, 3824]
	.p2align 2
.L1196:
	ldr	w1, [x23]
	add	w21, w21, 1
	cmp	w1, w21
	bhi	.L1200
.L1195:
	ldr	w0, [x20, 3376]
	str	w22, [x20, 3392]
	cmp	w0, w22
	bls	.L1205
	.p2align 2
.L1229:
	add	x2, x20, x22, uxtw 3
	add	w22, w22, 1
	cmp	w22, w0
	str	xzr, [x2, 3824]
	bne	.L1229
.L1205:
	add	x23, x24, 2404
	mov	w22, 0
	mov	w26, 1
	mov	w25, 1
	ldr	w24, [x23, 4]
	add	w24, w1, w24
	cmp	w24, w21
	bls	.L1203
	.p2align 2
.L1228:
	uxtw	x0, w21
	add	x1, x23, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L1206
	add	x0, x0, 8
	ldr	w5, [x20, 3380]
	ldr	w4, [x20, 5580]
	ldr	w0, [x23, x0, lsl 2]
	add	w4, w4, w0
	cbz	w5, .L1206
	add	x1, x20, 3688
	mov	w0, 0
	b	.L1209
	.p2align 3
.L1207:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L1206
.L1209:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	w3, [x2, 8]
	cmp	w4, w3
	bne	.L1207
	ldr	w3, [x2, 32]
	ldr	w6, [x20, 5600]
	cmp	w6, w3
	bne	.L1207
	add	x19, x20, x0, uxtw 3
	strb	w26, [x2, 1]
	ldr	x0, [x19, 3688]
	ldrb	w1, [x0, 1]
	cbnz	w1, .L1243
.L1208:
	str	w25, [x0, 64]
	add	x0, x20, x22, uxtw 3
	add	w22, w22, 1
	ldr	x1, [x19, 3688]
	str	wzr, [x1, 60]
	ldr	x1, [x19, 3688]
	str	x1, [x0, 3960]
	.p2align 2
.L1206:
	add	w21, w21, 1
	cmp	w24, w21
	bhi	.L1228
	ldr	w0, [x20, 3376]
.L1203:
	cmp	w0, w22
	str	w22, [x20, 3396]
	bls	.L1194
	.p2align 2
.L1227:
	add	x1, x20, x22, uxtw 3
	add	w22, w22, 1
	cmp	w0, w22
	str	xzr, [x1, 3960]
	bne	.L1227
.L1194:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1242:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	ldr	x0, [x19, 3688]
	b	.L1198
.L1243:
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	ldr	x0, [x19, 3688]
	b	.L1208
.L1214:
	mov	w22, 0
	mov	w21, 0
	add	x24, x20, 4096
	b	.L1195
	.size	HEVC_UpdateReflist, .-HEVC_UpdateReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UpdateLTReflist
	.type	HEVC_UpdateLTReflist, %function
HEVC_UpdateLTReflist:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 5604]
	mov	w2, 5036
	ldr	x0, [x19, 2968]
	mov	w5, 12668
	ldr	w6, [x19, 6500]
	add	x1, x19, 4096
	ldr	w9, [x19, 6508]
	add	x1, x1, 2404
	smaddl	x2, w3, w2, x0
	ldr	w0, [x19, 6504]
	sub	w9, w9, #1
	ldr	x4, [x19, 2960]
	mov	w3, 1
	ldr	w2, [x2, 32]
	add	w0, w6, w0
	sub	w0, w0, #1
	cmp	w9, w0
	smaddl	x0, w2, w5, x4
	ldr	w0, [x0, 116]
	lsl	w0, w3, w0
	ble	.L1254
	mov	w10, 0
	mov	x11, x1
	sub	w7, w0, #1
	mov	w13, w3
	mov	w12, w3
	.p2align 2
.L1251:
	sxtw	x0, w9
	add	x1, x11, x0
	ldrb	w1, [x1, 12]
	cbz	w1, .L1246
	add	x0, x19, x0, lsl 2
	ldr	w8, [x19, 3380]
	ldr	w6, [x0, 5656]
	ldr	w5, [x0, 6600]
	uxtb	w6, w6
	and	w0, w5, w7
	cmp	w6, wzr
	csel	w5, w0, w5, eq
	cmp	w8, wzr
	ble	.L1246
	add	x2, x19, 3688
	mov	w1, 0
	b	.L1250
	.p2align 3
.L1249:
	add	w1, w1, 1
	cmp	w1, w8
	beq	.L1246
.L1250:
	ldr	x3, [x2]
	cmp	w6, wzr
	add	x2, x2, 8
	ldr	w0, [x3, 8]
	and	w4, w0, w7
	csel	w0, w4, w0, eq
	cmp	w5, w0
	bne	.L1249
	ldr	w4, [x3, 32]
	ldr	w0, [x19, 5600]
	cmp	w4, w0
	bne	.L1249
	add	x1, x19, x1, sxtw 3
	strb	w13, [x3, 1]
	add	x0, x19, x10, sxtw 3
	add	w10, w10, 1
	ldr	x2, [x1, 3688]
	str	wzr, [x2, 64]
	ldr	x2, [x1, 3688]
	str	w12, [x2, 60]
	ldr	x1, [x1, 3688]
	str	x1, [x0, 4096]
	.p2align 2
.L1246:
	ldp	w1, w0, [x11]
	sub	w9, w9, #1
	add	w0, w1, w0
	sub	w0, w0, #1
	cmp	w0, w9
	blt	.L1251
	mov	w0, w10
.L1245:
	ldr	w1, [x19, 3376]
	str	w0, [x19, 3388]
	cmp	w1, w10
	ble	.L1244
	.p2align 2
.L1257:
	add	x0, x19, x10, sxtw 3
	add	w10, w10, 1
	cmp	w10, w1
	str	xzr, [x0, 4096]
	bne	.L1257
.L1244:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1254:
	mov	w0, 0
	mov	w10, 0
	b	.L1245
	.size	HEVC_UpdateLTReflist, .-HEVC_UpdateLTReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetAPC
	.type	HEVC_GetAPC, %function
HEVC_GetAPC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x23, x1
	mov	x0, x30
	bl	_mcount
	cbz	x23, .L1281
	ldr	w20, [x21, 4864]
	uxtw	x22, w20
	lsl	x0, x22, 5
	add	x0, x0, x22, lsl 3
	add	x1, x21, x0, lsl 3
	sub	x0, x1, x0
	ldr	w2, [x0, 14188]
	cbz	w2, .L1265
	ldr	w0, [x0, 14196]
	cbz	w0, .L1282
	mov	w0, 280
	mov	x1, 14200
	mov	w19, 0
	umaddl	x0, w20, w0, x1
	add	x0, x21, x0
	b	.L1268
	.p2align 3
.L1271:
	ldr	w1, [x0], 4
	cbz	w1, .L1266
.L1268:
	add	w19, w19, 1
	cmp	w19, w2
	bne	.L1271
.L1265:
	ldr	x1, .LC245
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1278:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1282:
	mov	w19, 0
	.p2align 2
.L1266:
	ldr	w0, [x21, 276]
	ldr	w1, [x23, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1269
	ldr	x1, [x0, 32]
	cbz	x1, .L1269
	uxtw	x24, w19
	mov	w3, 70
	mov	w2, 1
	lsl	x1, x22, 5
	umaddl	x20, w20, w3, x24
	add	x22, x1, x22, lsl 3
	mov	w3, w19
	add	x20, x21, x20, lsl 2
	add	x1, x21, x22, lsl 3
	sub	x22, x1, x22
	ldr	x1, .LC242
	add	x24, x22, x24
	str	w2, [x20, 14196]
	add	x24, x24, 12288
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x20, 14260]
	ldr	w0, [x23, 8]
	str	w0, [x20, 14324]
	ldr	w0, [x22, 14192]
	add	w0, w0, w2
	str	w0, [x22, 14192]
	mov	w0, 13
	ldr	w2, [x23, 236]
	bl	dprint_vfmw
	str	w19, [x23, 24]
	ldr	w1, [x23, 32]
	mov	w0, 0
	str	w1, [x20, 14388]
	strb	wzr, [x24, 2164]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1269:
	ldrb	w4, [x23, 1]
	mov	x5, x0
	ldr	x1, .LC243
	mov	x6, 0
	ldr	w3, [x23, 8]
	mov	w0, 0
	ldr	w2, [x23, 28]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1278
.L1281:
	ldr	x2, .LC239
	mov	w3, 11586
	ldr	x1, .LC240
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1278
	.size	HEVC_GetAPC, .-HEVC_GetAPC
	.align	3
.LC239:
	.xword	.LC2
	.align	3
.LC240:
	.xword	.LC4
	.align	3
.LC242:
	.xword	.LC241
	.align	3
.LC243:
	.xword	.LC6
	.align	3
.LC245:
	.xword	.LC244
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckFrameStore
	.type	HEVC_CheckFrameStore, %function
HEVC_CheckFrameStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1293
	ldr	w1, [x19, 28]
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	cbz	x0, .L1285
	ldrsb	w4, [x0, 1]
	cmp	w4, 3
	ccmp	w4, wzr, 4, ne
	beq	.L1305
	ldr	w0, [x19, 52]
	cmp	w0, 1
	beq	.L1290
	ldr	w4, [x19, 48]
	ldrb	w5, [x19]
	cbz	w4, .L1289
	cmp	w5, 1
	mov	w0, 0
	beq	.L1289
.L1299:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1305:
	ldr	x2, .LC246
	mov	w0, 13
	ldr	x1, .LC248
	ldr	w3, [x19, 28]
	add	x2, x2, 472
	bl	dprint_vfmw
.L1287:
	ldr	w0, [x19, 52]
	cmp	w0, 1
	bne	.L1306
.L1290:
	mov	w1, 1
	mov	w0, 2
	strb	w1, [x19, 2]
	str	w0, [x19, 52]
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1285:
	ldr	x1, .LC250
	mov	x2, x19
	ldr	w3, [x19, 8]
	mov	w0, 1
	ldr	w5, [x19, 28]
	ldr	w4, [x19, 52]
	bl	dprint_vfmw
	b	.L1287
.L1306:
	ldr	x2, .LC246
	mov	w0, 1
	ldr	x1, .LC252
	ldr	w3, [x19, 8]
	add	x2, x2, 472
	bl	dprint_vfmw
	mov	w0, -3
	b	.L1299
	.p2align 3
.L1289:
	ldr	x2, .LC246
	mov	x3, x19
	ldr	x1, .LC254
	mov	w0, 1
	add	x2, x2, 472
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1299
	.p2align 3
.L1293:
	mov	w0, -1
	b	.L1299
	.size	HEVC_CheckFrameStore, .-HEVC_CheckFrameStore
	.align	3
.LC246:
	.xword	.LANCHOR0
	.align	3
.LC248:
	.xword	.LC247
	.align	3
.LC250:
	.xword	.LC249
	.align	3
.LC252:
	.xword	.LC251
	.align	3
.LC254:
	.xword	.LC253
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetImagePara
	.type	HEVC_GetImagePara, %function
HEVC_GetImagePara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w23, [x21, 12]
	ldr	x0, [x21, 672]
	cmn	x0, #1
	beq	.L1309
	ldr	w1, [x20, 3380]
	cbz	w1, .L1309
	mov	w25, -1
	mov	x24, -2
	mov	w19, 0
	b	.L1312
	.p2align 3
.L1347:
	ldr	x0, [x22, 3688]
	ldr	w1, [x20, 3380]
	ldr	x0, [x0, 672]
	cmp	x0, x24
	bcs	.L1311
	mov	w25, w19
	mov	x24, x0
.L1311:
	add	w19, w19, 1
	cmp	w1, w19
	bls	.L1349
.L1312:
	add	x22, x20, x19, sxtw 3
	ldr	x0, [x22, 3688]
	cbz	x0, .L1311
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	cbz	x0, .L1348
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	ccmp	w0, wzr, 4, ne
	bne	.L1347
.L1348:
	ldr	w1, [x20, 3380]
	add	w19, w19, 1
	cmp	w1, w19
	bhi	.L1312
.L1349:
	cmn	w25, #1
	beq	.L1309
	ldr	x1, [x21, 672]
	cmp	x1, x24
	bhi	.L1350
.L1309:
	ldrb	w0, [x21, 153]
	ldrb	w1, [x21, 152]
	and	w0, w0, -64
	strb	w0, [x21, 153]
	and	w1, w1, -4
	strb	w1, [x21, 152]
	ldr	w2, [x20, 144]
	str	w2, [x21, 196]
	ldr	x2, [x20, 3000]
	ldrh	w2, [x2, 124]
	cmp	w2, 1
	beq	.L1320
	cmp	w2, 257
	bne	.L1321
	ldr	w2, [x20, 4244]
	cmp	w2, 1
	cset	w4, ne
.L1313:
	ldr	x3, [x20, 3008]
	mov	w2, 3
	ldrb	w3, [x3, 2066]
	cbz	w3, .L1314
	ldr	w3, [x21, 40]
	mov	w2, 1
	cmp	w3, w2
	ccmp	w3, 11, 4, ne
	cset	w4, eq
	cbz	w4, .L1351
.L1315:
	ldr	w3, [x21, 44]
	cmp	w3, wzr
	cset	w4, eq
.L1314:
	mov	w3, 2
	ldrb	w6, [x21, 3]
	bfi	w0, w3, 4, 2
	ldrb	w3, [x21, 154]
	bfi	w0, w2, 2, 2
	ldrb	w5, [x21, 4]
	ldr	w2, [x21, 48]
	bfi	w0, w4, 0, 2
	bfi	w1, w23, 0, 2
	bfi	w3, w6, 1, 1
	strb	w0, [x21, 153]
	strb	w1, [x21, 152]
	strb	w3, [x21, 154]
	str	w5, [x21, 208]
	cbz	w2, .L1316
	ldr	w0, [x21, 16]
	str	w0, [x21, 240]
.L1316:
	ldr	x0, [x20, 3040]
	ldr	w1, [x21, 28]
	ldr	w0, [x0, 644]
	str	w0, [x21, 212]
	ldr	x0, [x20, 3040]
	ldr	w0, [x0, 648]
	str	w0, [x21, 216]
	ldr	x0, [x20, 3040]
	ldr	w0, [x0, 652]
	str	w0, [x21, 220]
	ldr	w0, [x20, 276]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1307
	ldr	x3, .LC257
	mov	x2, 640
	add	x1, x21, 88
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 16
	str	w0, [x19, 296]
	mov	w0, 4
	mov	w1, 1
	ldr	w2, [x21, 56]
	strb	w1, [x19, 291]
	cmp	w2, wzr
	strb	w1, [x19, 289]
	csel	w0, w0, wzr, ne
	strb	w0, [x19, 284]
	ldr	w0, [x21, 68]
	str	w0, [x19, 236]
.L1307:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1350:
	ldr	w0, [x20, 276]
	mov	x2, x24
	bl	IsPtsRewind
	cbnz	w0, .L1309
	ldr	x1, .LC256
	mov	x3, x24
	ldr	x2, [x21, 672]
	mov	w0, 29
	add	x25, x20, x25, sxtw 3
	bl	dprint_vfmw
	ldr	x0, [x25, 3688]
	ldr	x1, [x21, 672]
	str	x1, [x0, 672]
	str	x24, [x21, 672]
	b	.L1309
	.p2align 3
.L1351:
	mov	w4, 2
	and	w3, w3, -9
	mov	w2, 3
	cmp	w3, w4
	csel	w2, w2, w4, ne
	b	.L1315
	.p2align 3
.L1320:
	mov	w4, 0
	b	.L1313
	.p2align 3
.L1321:
	mov	w4, 1
	b	.L1313
	.size	HEVC_GetImagePara, .-HEVC_GetImagePara
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC257:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CheckOutputImage
	.type	HEVC_CheckOutputImage, %function
HEVC_CheckOutputImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 19
	bhi	.L1354
	uxtw	x1, w19
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x1, x0, x1
	lsl	x0, x1, 3
	sub	x1, x0, x1
	add	x1, x20, x1, lsl 3
	add	x1, x1, 12288
	ldrb	w0, [x1, 2465]
	cmp	w0, wzr
	cset	w0, ne
.L1353:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1354:
	mov	w0, -1
	b	.L1353
	.size	HEVC_CheckOutputImage, .-HEVC_CheckOutputImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DECRecycleImage
	.type	HEVC_DECRecycleImage, %function
HEVC_DECRecycleImage:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	ldr	w0, [x21, 276]
	mov	w1, w22
	bl	FSP_GetLogicFs
	cbz	x0, .L1360
	ldrsb	w1, [x0, 1]
	add	x19, x0, 592
	add	x20, x0, 624
	cbz	w1, .L1366
.L1363:
	ldr	x2, [x19]
	mov	x1, x2
	cbz	x2, .L1358
	ldr	w0, [x21, 276]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1358:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L1363
	ldr	w0, [x21, 276]
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, 0
.L1356:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1366:
	ldr	x1, .LC259
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1356
.L1360:
	mov	w0, -1
	b	.L1356
	.size	HEVC_DECRecycleImage, .-HEVC_DECRecycleImage
	.align	3
.LC259:
	.xword	.LC258
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetSLHDR1MasteringDisplayInfo
	.type	HEVC_GetSLHDR1MasteringDisplayInfo, %function
HEVC_GetSLHDR1MasteringDisplayInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x1, x19, 568
	mov	w2, 14999
	ldr	w0, [x1, 4]
	cmp	w0, w2
	bhi	.L1371
	sub	w2, w0, #8192
	mov	w3, 4749
	sub	w2, w2, #308
	cmp	w2, w3
	bhi	.L1370
	mov	w0, 1
	strb	w0, [x20, 3]
	b	.L1369
	.p2align 3
.L1370:
	sub	w0, w0, #12288
	sub	w0, w0, #962
	cmp	w0, 1749
	bls	.L1374
.L1371:
	strb	wzr, [x20, 3]
.L1369:
	ldr	w2, [x1, 36]
	mov	w0, 56963
	movk	w0, 0x431b, lsl 16
	mov	w3, 10000
	add	w2, w2, 249856
	mov	w5, 2063
	add	w2, w2, 144
	movk	w5, 0x5f6, lsl 16
	mov	w4, w3
	umull	x2, w2, w0
	lsr	x2, x2, 32
	lsr	w2, w2, 17
	lsl	w0, w2, 3
	sub	w0, w0, w2
	add	w2, w2, w0, lsl 3
	sub	w0, w2, w0
	cmp	w0, w3
	csel	w0, w0, w3, ls
	strh	w0, [x20, 4]
	ldr	w0, [x1, 40]
	cmp	w0, w5
	bhi	.L1372
	mov	w1, 5977
	movk	w1, 0xd1b7, lsl 16
	umull	x0, w0, w1
	ubfx	x4, x0, 45, 16
.L1372:
	strh	w4, [x20, 6]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1374:
	mov	w0, 2
	strb	w0, [x20, 3]
	b	.L1369
	.size	HEVC_GetSLHDR1MasteringDisplayInfo, .-HEVC_GetSLHDR1MasteringDisplayInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_PrintSLHDR1Info
	.type	HEVC_PrintSLHDR1Info, %function
HEVC_PrintSLHDR1Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w2, [x21]
	mov	w0, 32
	ldr	x1, .LC261
	bl	dprint_vfmw
	ldrb	w2, [x21, 1]
	mov	w0, 32
	ldr	x1, .LC263
	bl	dprint_vfmw
	ldrb	w2, [x21, 2]
	mov	w0, 32
	ldr	x1, .LC265
	bl	dprint_vfmw
	ldrb	w2, [x21, 3]
	mov	w0, 32
	ldr	x1, .LC267
	bl	dprint_vfmw
	ldrh	w2, [x21, 4]
	mov	w0, 32
	ldr	x1, .LC269
	bl	dprint_vfmw
	ldrh	w2, [x21, 6]
	mov	w0, 32
	ldr	x1, .LC271
	bl	dprint_vfmw
	ldrb	w2, [x21, 8]
	mov	w0, 32
	ldr	x1, .LC273
	bl	dprint_vfmw
	ldrb	w2, [x21, 9]
	mov	w0, 32
	ldr	x1, .LC275
	bl	dprint_vfmw
	ldrb	w0, [x21, 1]
	ldrb	w2, [x21, 10]
	cbnz	w0, .L1376
	ldr	x1, .LC277
	add	x19, x21, 10
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w2, [x19, 1]
	mov	w0, 32
	ldr	x1, .LC279
	bl	dprint_vfmw
	ldrb	w2, [x19, 2]
	mov	w0, 32
	ldr	x1, .LC281
	bl	dprint_vfmw
	ldrb	w2, [x19, 3]
	mov	w0, 32
	ldr	x1, .LC283
	bl	dprint_vfmw
	ldrb	w2, [x19, 4]
	mov	w0, 32
	ldr	x1, .LC285
	bl	dprint_vfmw
	ldrb	w2, [x19, 5]
	mov	w0, 32
	ldr	x1, .LC287
	bl	dprint_vfmw
	ldrb	w0, [x19, 5]
	cbz	w0, .L1381
	ldr	x23, .LC291
	mov	w20, 0
	ldr	x22, .LC293
	.p2align 2
.L1380:
	add	x21, x19, x20, uxtw
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	ldrb	w2, [x21, 6]
	bl	dprint_vfmw
	ldrb	w2, [x21, 17]
	mov	w3, w20
	mov	x1, x22
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 5]
	cmp	w0, w20
	bhi	.L1380
.L1381:
	ldrb	w2, [x19, 28]
	mov	w0, 32
	ldr	x1, .LC289
	bl	dprint_vfmw
	ldrb	w0, [x19, 28]
	cbz	w0, .L1382
	ldr	x23, .LC295
	mov	w20, 0
	ldr	x22, .LC297
	.p2align 2
.L1383:
	add	x21, x19, x20, uxtw
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	ldrb	w2, [x21, 29]
	bl	dprint_vfmw
	ldrb	w2, [x21, 36]
	mov	w3, w20
	mov	x1, x22
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 28]
	cmp	w0, w20
	bhi	.L1383
.L1382:
	ldr	x1, .LC315
	mov	x2, 290
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1376:
	ldr	x1, .LC299
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21, 10]
	cbz	w0, .L1394
	ldr	x24, .LC303
	mov	w20, 0
	ldr	x23, .LC305
	add	x19, x21, 10
	.p2align 2
.L1387:
	add	x22, x21, x20, uxtw 1
	mov	w2, w20
	mov	x1, x24
	mov	w0, 32
	ldrh	w3, [x22, 12]
	bl	dprint_vfmw
	ldrh	w3, [x22, 80]
	mov	w2, w20
	mov	x1, x23
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19]
	cmp	w0, w20
	bhi	.L1387
.L1388:
	ldrb	w2, [x19, 138]
	mov	w0, 32
	ldr	x1, .LC301
	bl	dprint_vfmw
	ldrb	w0, [x19, 138]
	cbz	w0, .L1386
	ldr	x24, .LC311
	mov	w20, 0
	ldr	x23, .LC313
	.p2align 2
.L1389:
	add	x22, x21, x20, uxtw 1
	mov	w3, w20
	mov	x1, x24
	mov	w0, 32
	ldrh	w2, [x22, 150]
	bl	dprint_vfmw
	ldrh	w2, [x22, 218]
	mov	w3, w20
	mov	x1, x23
	mov	w0, 32
	add	w20, w20, 1
	bl	dprint_vfmw
	ldrb	w0, [x19, 138]
	cmp	w0, w20
	bhi	.L1389
.L1386:
	ldrh	w2, [x19, 276]
	mov	w0, 32
	ldr	x1, .LC307
	bl	dprint_vfmw
	ldrh	w2, [x19, 278]
	mov	w0, 32
	ldr	x1, .LC309
	bl	dprint_vfmw
	b	.L1382
.L1394:
	add	x19, x21, 10
	b	.L1388
	.size	HEVC_PrintSLHDR1Info, .-HEVC_PrintSLHDR1Info
	.align	3
.LC261:
	.xword	.LC260
	.align	3
.LC263:
	.xword	.LC262
	.align	3
.LC265:
	.xword	.LC264
	.align	3
.LC267:
	.xword	.LC266
	.align	3
.LC269:
	.xword	.LC268
	.align	3
.LC271:
	.xword	.LC270
	.align	3
.LC273:
	.xword	.LC272
	.align	3
.LC275:
	.xword	.LC274
	.align	3
.LC277:
	.xword	.LC276
	.align	3
.LC279:
	.xword	.LC278
	.align	3
.LC281:
	.xword	.LC280
	.align	3
.LC283:
	.xword	.LC282
	.align	3
.LC285:
	.xword	.LC284
	.align	3
.LC287:
	.xword	.LC286
	.align	3
.LC289:
	.xword	.LC288
	.align	3
.LC291:
	.xword	.LC290
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
.LC299:
	.xword	.LC298
	.align	3
.LC301:
	.xword	.LC300
	.align	3
.LC303:
	.xword	.LC302
	.align	3
.LC305:
	.xword	.LC304
	.align	3
.LC307:
	.xword	.LC306
	.align	3
.LC309:
	.xword	.LC308
	.align	3
.LC311:
	.xword	.LC310
	.align	3
.LC313:
	.xword	.LC312
	.align	3
.LC315:
	.xword	.LC314
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetSLHDR1Info
	.type	HEVC_GetSLHDR1Info, %function
HEVC_GetSLHDR1Info:
	stp	x29, x30, [sp, -352]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	mov	x2, 290
	mov	w1, 0
	add	x0, x29, 56
	bl	memset
	ldrb	w3, [x21, 1]
	ldrb	w4, [x19, 56]
	ldrb	w5, [x19, 568]
	cbz	w3, .L1435
	cbnz	w4, .L1438
.L1435:
	ldrb	w6, [x19, 59]
	ldrb	w7, [x19, 128]
.L1397:
	ldr	x2, .LC316
	mov	w0, 22
	ldr	x1, .LC318
	add	x2, x2, 496
	bl	dprint_vfmw
	strb	wzr, [x20, 466]
.L1395:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 352
	ret
	.p2align 3
.L1438:
	cbz	w5, .L1435
	ldrb	w0, [x19, 59]
	cbnz	w0, .L1400
	ldrb	w7, [x19, 128]
	cbz	w7, .L1439
.L1400:
	mov	w0, 1
	strb	w0, [x20, 466]
	ldr	w1, [x21, 24]
	ldrb	w3, [x19, 57]
	ldrb	w2, [x19, 58]
	cmp	w1, 9
	strb	w3, [x29, 56]
	strb	w2, [x29, 57]
	beq	.L1440
.L1402:
	ldrb	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1403
	ldrb	w1, [x19, 129]
	cmp	w1, 1
	beq	.L1403
	cmp	w1, 9
	ccmp	w0, 9, 4, ne
	beq	.L1441
	ldrb	w0, [x29, 64]
	strb	w0, [x29, 58]
.L1403:
	mov	x1, x19
	add	x0, x29, 56
	bl	HEVC_GetSLHDR1MasteringDisplayInfo
	ldrb	w1, [x29, 64]
	ldrb	w0, [x29, 58]
	cmp	w1, w0
	beq	.L1442
	strb	wzr, [x29, 65]
.L1406:
	ldrb	w0, [x29, 57]
	cbnz	w0, .L1407
	add	x5, x19, 59
	ldrb	w6, [x5, 2]
	ldrb	w4, [x5, 3]
	ldrb	w3, [x5, 4]
	ldrb	w2, [x5, 5]
	ldrb	w1, [x5, 6]
	ldrb	w0, [x5, 7]
	strb	w6, [x29, 66]
	strb	w4, [x29, 67]
	strb	w3, [x29, 68]
	strb	w2, [x29, 69]
	strb	w1, [x29, 70]
	strb	w0, [x29, 71]
	cbz	w0, .L1412
	sub	w4, w0, #1
	add	x2, x29, 56
	add	x4, x4, 17
	add	x0, x29, 72
	add	x1, x19, 82
	add	x4, x2, x4
	.p2align 2
.L1411:
	ldrb	w3, [x1, -15]
	add	x0, x0, 1
	ldrb	w2, [x1], 1
	strb	w3, [x0, -1]
	strb	w2, [x0, 10]
	cmp	x0, x4
	bne	.L1411
.L1412:
	ldrb	w0, [x5, 38]
	strb	w0, [x29, 94]
	cbz	w0, .L1410
	sub	w3, w0, #1
	add	x1, x29, 56
	add	x3, x3, 40
	add	x0, x29, 95
	add	x19, x19, 113
	add	x3, x1, x3
	.p2align 2
.L1415:
	ldrb	w2, [x19, -15]
	add	x0, x0, 1
	ldrb	w1, [x19], 1
	strb	w2, [x0, -1]
	strb	w1, [x0, 6]
	cmp	x0, x3
	bne	.L1415
.L1410:
	ldr	w0, [x20, 472]
	cbnz	w0, .L1443
	ldr	x2, .LC316
	mov	w0, 1
	ldr	x1, .LC320
	add	x2, x2, 496
	bl	dprint_vfmw
	b	.L1395
	.p2align 3
.L1407:
	add	x5, x19, 128
	ldrb	w0, [x5, 40]
	add	w0, w0, 1
	ldp	w2, w1, [x5, 8]
	uxtb	w0, w0
	strh	w2, [x29, 342]
	strb	w0, [x29, 66]
	strh	w1, [x29, 344]
	cbz	w0, .L1419
	sub	w2, w0, #1
	add	x1, x29, 68
	add	x2, x2, 87
	add	x0, x19, 172
	add	x2, x19, x2, lsl 1
	.p2align 2
.L1418:
	ldrh	w4, [x0]
	add	x0, x0, 2
	ldrh	w3, [x0, 196]
	cmp	x0, x2
	strh	w4, [x1]
	add	x1, x1, 2
	strh	w3, [x1, 66]
	bne	.L1418
.L1419:
	ldrb	w0, [x5, 41]
	add	w0, w0, 1
	uxtb	w0, w0
	strb	w0, [x29, 204]
	cbz	w0, .L1410
	sub	w2, w0, #1
	add	x1, x29, 206
	add	x2, x2, 120
	add	x0, x19, 238
	add	x19, x19, x2, lsl 1
	.p2align 2
.L1420:
	ldrh	w3, [x0]
	add	x0, x0, 2
	ldrh	w2, [x0, 196]
	cmp	x0, x19
	strh	w3, [x1]
	add	x1, x1, 2
	strh	w2, [x1, 66]
	bne	.L1420
	b	.L1410
	.p2align 3
.L1443:
	ldr	x3, .LC321
	mov	x2, 290
	ldr	x0, [x20, 480]
	add	x1, x29, 56
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 290
	str	w0, [x20, 468]
	b	.L1395
	.p2align 3
.L1439:
	mov	w6, 0
	b	.L1397
	.p2align 3
.L1441:
	mov	w0, 1
	strb	w0, [x29, 58]
	b	.L1403
	.p2align 3
.L1442:
	ldrb	w0, [x29, 59]
	strb	w0, [x29, 65]
	b	.L1406
	.p2align 3
.L1440:
	ldr	w1, [x21, 32]
	cmp	w1, 9
	bne	.L1402
	strb	w0, [x29, 64]
	b	.L1402
	.size	HEVC_GetSLHDR1Info, .-HEVC_GetSLHDR1Info
	.align	3
.LC316:
	.xword	.LANCHOR0
	.align	3
.LC318:
	.xword	.LC317
	.align	3
.LC320:
	.xword	.LC319
	.align	3
.LC321:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ConvertHDRInfo
	.type	HEVC_ConvertHDRInfo, %function
HEVC_ConvertHDRInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	mov	x19, x2
	bl	_mcount
	add	x3, x21, 464
	add	x0, x19, 572
	ldrb	w1, [x20]
	add	x2, x21, 496
	add	x4, x19, 584
	strb	w1, [x3, 24]
	ldr	w1, [x20, 24]
	strb	w1, [x3, 25]
	ldr	w1, [x20, 32]
	strb	w1, [x3, 26]
	ldr	w1, [x20, 28]
	str	w1, [x3, 28]
	ldrb	w1, [x19, 568]
	strb	w1, [x21, 464]
.L1445:
	ldr	w1, [x0]
	add	x0, x0, 4
	strh	w1, [x2]
	add	x2, x2, 2
	cmp	x0, x4
	ldr	w1, [x0, 8]
	strh	w1, [x2, 4]
	bne	.L1445
	ldr	w0, [x19, 596]
	mov	x2, x19
	strh	w0, [x3, 44]
	mov	x1, x20
	mov	x0, x21
	ldr	w4, [x19, 600]
	strh	w4, [x3, 46]
	ldr	w4, [x19, 604]
	str	w4, [x3, 48]
	ldr	w4, [x19, 608]
	str	w4, [x3, 52]
	ldrb	w4, [x19, 612]
	strb	w4, [x3, 1]
	ldrh	w4, [x19, 614]
	str	w4, [x3, 56]
	ldrh	w4, [x19, 616]
	str	w4, [x3, 60]
	ldrb	w4, [x19, 618]
	strb	w4, [x3, 64]
	bl	HEVC_GetSLHDR1Info
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ConvertHDRInfo, .-HEVC_ConvertHDRInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_AllocFrameStore
	.type	HEVC_AllocFrameStore, %function
HEVC_AllocFrameStore:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x23, x20, 4096
	add	x19, x20, 12288
	bl	_mcount
	add	x19, x19, 2464
	ldr	w1, [x20, 5604]
	mov	w5, 5036
	ldr	x0, [x20, 2968]
	mov	w4, 12668
	ldr	x2, [x20, 2960]
	mov	x3, 0
	smaddl	x0, w1, w5, x0
	ldr	w21, [x0, 32]
	strb	wzr, [x23, 761]
	smaddl	x21, w21, w4, x2
	.p2align 2
.L1453:
	ldr	w0, [x19, 48]
	cbnz	w0, .L1448
	cbz	x19, .L1449
	ldr	w2, [x20, 3380]
	cbz	w2, .L1449
	ldr	x0, [x20, 3688]
	cmp	x0, x19
	beq	.L1448
	sub	w2, w2, #1
	mov	x0, x20
	add	x2, x20, x2, lsl 3
	b	.L1451
	.p2align 3
.L1452:
	ldr	x1, [x0, 3688]
	cmp	x1, x19
	beq	.L1448
.L1451:
	cmp	x0, x2
	add	x0, x0, 8
	bne	.L1452
.L1449:
	mov	w1, 101
	lsl	x0, x3, 3
	str	w1, [x20, 4896]
	sub	x0, x0, x3
	mov	w1, 1
	mov	x2, 640
	lsl	x0, x0, x1
	strb	w1, [x23, 761]
	sub	x3, x0, x3
	add	x0, x23, 832
	lsl	x22, x3, 3
	sub	x3, x22, x3
	add	x22, x20, x3, lsl 3
	add	x24, x22, 12288
	add	x1, x24, 2552
	bl	memcpy
	str	x19, [x20, 4920]
	str	wzr, [x20, 5080]
	str	wzr, [x22, 14768]
	strb	wzr, [x24, 2466]
	strb	wzr, [x19]
	ldr	x0, [x20, 4920]
	str	wzr, [x0, 60]
	ldr	x0, [x20, 4920]
	str	wzr, [x0, 64]
	ldr	x0, [x20, 4920]
	str	wzr, [x0, 52]
	ldrb	w1, [x23, 761]
	cmp	w1, 1
	bne	.L1457
	ldr	w0, [x20, 276]
	bl	FSP_NewLogicFs
	mov	w24, w0
	mov	w1, w0
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	mov	x22, x0
	cmp	w24, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L1455
	add	x2, x23, 136
	add	x1, x21, 2064
	add	x19, x0, 48
	bl	HEVC_ConvertHDRInfo
	ldr	x0, [x20, 3040]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L1470
.L1456:
	ldr	x21, .LC324
	mov	x2, 640
	ldr	x0, [x20, 4920]
	mov	x1, x19
	ldr	x3, [x21, 104]
	add	x0, x0, 88
	blr	x3
	ldr	x1, [x20, 4920]
	mov	x2, 640
	ldr	x3, [x21, 104]
	add	x0, x23, 832
	add	x1, x1, 88
	blr	x3
	ldr	x1, [x20, 4920]
	mov	w0, 0
	str	w24, [x1, 28]
	ldrsb	w1, [x22, 4]
	str	w1, [x20, 4892]
.L1468:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1448:
	add	w3, w3, 1
	add	x19, x19, 728
	cmp	w3, 20
	bne	.L1453
.L1457:
	ldr	x1, .LC323
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1470:
	ldr	x2, [x20, 3008]
	ldr	w21, [x19, 112]
	ldr	w1, [x19, 36]
	ldr	w0, [x2, 68]
	ldr	w2, [x2, 64]
	stp	w2, w0, [x19, 68]
	mul	w21, w0, w21
	stp	wzr, wzr, [x19, 240]
	add	w0, w21, w1
	str	wzr, [x19, 256]
	stp	wzr, wzr, [x19, 248]
	str	w0, [x19, 40]
	bl	MEM_Phy2Vir
	str	x0, [x19, 512]
	ldr	w1, [x19, 20]
	ldr	w2, [x19, 116]
	add	w0, w21, w1
	str	w0, [x19, 24]
	add	w0, w2, w0
	str	w0, [x19, 32]
	b	.L1456
.L1455:
	ldr	x1, .LC326
	mov	w0, 0
	strb	wzr, [x23, 761]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1468
	.size	HEVC_AllocFrameStore, .-HEVC_AllocFrameStore
	.align	3
.LC323:
	.xword	.LC322
	.align	3
.LC324:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC326:
	.xword	.LC325
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsVoFinish
	.type	HEVC_IsVoFinish, %function
HEVC_IsVoFinish:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w0, [x20, 276]
	bl	FSP_GetFspType
	cmn	w0, #1
	mov	w21, w0
	bne	.L1477
	b	.L1479
	.p2align 3
.L1474:
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L1476
	cmp	w19, 32
	beq	.L1480
.L1477:
	ldr	w0, [x20, 276]
	mov	w1, w19
	add	w19, w19, 1
	bl	FSP_GetLogicFs
	cbnz	x0, .L1474
	ldr	x1, .LC330
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1479:
	ldr	x1, .LC328
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1476:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1480:
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_IsVoFinish, .-HEVC_IsVoFinish
	.align	3
.LC328:
	.xword	.LC327
	.align	3
.LC330:
	.xword	.LC329
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetBackPicFromVOQueue
	.type	HEVC_GetBackPicFromVOQueue, %function
HEVC_GetBackPicFromVOQueue:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 12288
	add	x23, x22, 28672
	bl	_mcount
	add	x20, x20, 2465
	add	x0, x22, 4096
	add	x23, x23, 641
	add	x0, x0, 2848
	bl	ResetVoQueue
	.p2align 2
.L1484:
	strb	wzr, [x20]
	add	x19, x20, 631
	add	x21, x20, 663
	str	wzr, [x20, 47]
.L1483:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L1482
	ldr	w0, [x22, 276]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1482:
	add	x19, x19, 8
	cmp	x19, x21
	bne	.L1483
	add	x20, x20, 728
	cmp	x20, x23
	bne	.L1484
	ldr	w0, [x22, 184]
	cbz	w0, .L1481
	sub	w1, w0, #1
	add	x0, x22, 2168
	add	x1, x1, 543
	add	x22, x22, x1, lsl 2
	.p2align 2
.L1486:
	str	wzr, [x0], 4
	cmp	x0, x22
	bne	.L1486
.L1481:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	HEVC_GetBackPicFromVOQueue, .-HEVC_GetBackPicFromVOQueue
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveFrameStoreOutDPB
	.type	HEVC_RemoveFrameStoreOutDPB, %function
HEVC_RemoveFrameStoreOutDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	uxtw	x21, w1
	mov	x20, x0
	mov	x0, x30
	mov	x19, x21
	add	x22, x20, x21, lsl 3
	bl	_mcount
	ldr	x0, [x22, 3688]
	str	wzr, [x0, 48]
	ldr	x1, [x22, 3688]
	ldr	w0, [x20, 276]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1495
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L1496
	ldr	x1, [x22, 3688]
	mov	w2, 0
	ldr	w0, [x20, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetDisplay
.L1496:
	ldr	x1, [x22, 3688]
	mov	w2, 0
	ldr	w0, [x20, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
.L1495:
	ldr	w2, [x20, 3380]
	sub	w2, w2, #1
	cmp	w19, w2
	bhi	.L1499
	.p2align 2
.L1505:
	add	w0, w19, 1
	add	x1, x20, x21, lsl 3
	mov	w19, w0
	cmp	w0, w2
	mov	x21, x0
	add	x0, x20, x0, lsl 3
	ldr	x0, [x0, 3688]
	str	x0, [x1, 3688]
	bls	.L1505
.L1499:
	add	x0, x20, x2, uxtw 3
	str	xzr, [x0, 3688]
	str	w2, [x20, 3380]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RemoveFrameStoreOutDPB, .-HEVC_RemoveFrameStoreOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveDummyFrame
	.type	HEVC_RemoveDummyFrame, %function
HEVC_RemoveDummyFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, 0
	mov	w19, 0
	bl	_mcount
	ldr	w2, [x20, 3380]
	cbnz	w2, .L1516
	b	.L1509
	.p2align 3
.L1511:
	add	w19, w19, 1
	cmp	w2, w19
	mov	w21, w19
	bls	.L1509
.L1516:
	add	x0, x20, x19, sxtw 3
	ldr	x0, [x0, 3688]
	ldrb	w1, [x0]
	cbz	w1, .L1511
	mov	w1, w21
	strb	wzr, [x0]
	mov	x0, x20
	sub	w19, w19, #1
	add	w19, w19, 1
	bl	HEVC_RemoveApcStore
	mov	w1, w21
	mov	x0, x20
	mov	w21, w19
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	w2, [x20, 3380]
	cmp	w2, w19
	bhi	.L1516
.L1509:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RemoveDummyFrame, .-HEVC_RemoveDummyFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveUnUsedFrameStore
	.type	HEVC_RemoveUnUsedFrameStore, %function
HEVC_RemoveUnUsedFrameStore:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	w25, 0
	bl	_mcount
	ldr	w22, [x21, 3380]
	cbz	w22, .L1520
	mov	w26, 0
	mov	w20, 0
	mov	w24, -1
	mov	w23, 1
	.p2align 2
.L1527:
	add	x19, x21, x26, uxtw 3
	ldr	w0, [x21, 276]
	ldr	x1, [x19, 3688]
	ldr	w1, [x1, 28]
	bl	FSP_GetLogicFs
	cbz	x0, .L1521
	ldrsb	w1, [x0]
	cbnz	w1, .L1536
	ldrsb	w0, [x0, 1]
	cmp	w0, wzr
	ccmp	w0, 3, 4, ne
	ldr	x0, [x19, 3688]
	bne	.L1523
.L1539:
	ldr	w1, [x0, 52]
	cmp	w1, 1
	beq	.L1523
	str	w24, [x0, 28]
	ldr	x0, [x19, 3688]
	strb	wzr, [x0, 1]
	ldr	x0, [x19, 3688]
	strb	w23, [x0, 2]
.L1536:
	ldr	x0, [x19, 3688]
.L1523:
	ldr	w0, [x0]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L1540
	add	w26, w26, 1
.L1526:
	add	w20, w20, 1
	cmp	w22, w20
	bne	.L1527
.L1520:
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1521:
	ldr	x0, [x19, 3688]
	b	.L1539
	.p2align 3
.L1540:
	mov	w1, w26
	mov	x0, x21
	mov	w25, 1
	bl	HEVC_RemoveFrameStoreOutDPB
	b	.L1526
	.size	HEVC_RemoveUnUsedFrameStore, .-HEVC_RemoveUnUsedFrameStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SimpleSlideDPB
	.type	HEVC_SimpleSlideDPB, %function
HEVC_SimpleSlideDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 14188]
	ldr	w1, [x19, 14192]
	cmp	w1, w0
	bcs	.L1544
	ldr	w0, [x19, 14468]
	ldr	w1, [x19, 14472]
	cmp	w1, w0
	bcs	.L1544
	ldr	w0, [x19, 3376]
	ldr	w1, [x19, 3380]
	cmp	w1, w0
	bcc	.L1541
	cmp	w0, 15
	bls	.L1547
.L1544:
	ldr	x0, [x19, 3688]
	mov	w2, 0
	strb	wzr, [x0, 1]
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_SetRef
	mov	x0, x19
	mov	w1, 0
	bl	HEVC_RemoveApcStore
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
.L1541:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1547:
	mov	x0, x19
	bl	HEVC_IncreaseDPBSize
	cbnz	w0, .L1544
	b	.L1541
	.size	HEVC_SimpleSlideDPB, .-HEVC_SimpleSlideDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetMinPOC
	.type	HEVC_GetMinPOC, %function
HEVC_GetMinPOC:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	str	wzr, [x21]
	mov	w0, 2147483647
	str	w0, [x20]
	ldr	w3, [x19, 3376]
	ldr	w2, [x19, 3380]
	cmp	w2, w3
	bhi	.L1556
.L1549:
	mov	w0, 0
	cbz	w2, .L1548
	.p2align 2
.L1554:
	add	x1, x19, x0, uxtw 3
	ldr	w2, [x20]
	ldr	x1, [x1, 3688]
	ldr	w1, [x1, 8]
	cmp	w2, w1
	ble	.L1551
	str	w1, [x20]
	str	w0, [x21]
.L1551:
	ldr	w1, [x19, 3380]
	add	w0, w0, 1
	cmp	w1, w0
	bhi	.L1554
.L1548:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1556:
	ldr	x1, .LC332
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x19, 3376]
	str	w2, [x19, 3380]
	b	.L1549
	.size	HEVC_GetMinPOC, .-HEVC_GetMinPOC
	.align	3
.LC332:
	.xword	.LC331
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetReRangeFlag
	.type	HEVC_GetReRangeFlag, %function
HEVC_GetReRangeFlag:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w4
	mov	w22, w2
	bl	_mcount
	ldr	w5, [x19, 5604]
	mov	w3, 5036
	ldr	x2, [x19, 2968]
	mov	w1, 12668
	ldr	x0, [x19, 2960]
	smaddl	x3, w5, w3, x2
	ldr	w3, [x3, 32]
	smaddl	x0, w3, w1, x0
	ldr	w1, [x0, 64]
	cmp	w1, w21
	ccmp	w20, wzr, 0, eq
	bne	.L1558
	ldr	w0, [x0, 68]
	cmp	w0, w22
	beq	.L1569
.L1558:
	ldrb	w1, [x19, 1]
	mov	w0, 1
	cmp	w1, w0
	beq	.L1570
.L1559:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1570:
	ldr	x2, [x19, 3040]
	ldr	w2, [x2, 24]
	tst	w2, -5
	beq	.L1559
	ldr	w2, [x19, 2396]
	mov	w0, 0
	cbnz	w2, .L1559
	str	w1, [x19, 2396]
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1569:
	ldr	w0, [x19, 172]
	cbz	w0, .L1558
	ldr	x1, [x19, 3040]
	mov	w0, 0
	ldr	w1, [x1, 976]
	cbnz	w1, .L1558
	b	.L1559
	.size	HEVC_GetReRangeFlag, .-HEVC_GetReRangeFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalcStreamBits
	.type	HEVC_CalcStreamBits, %function
HEVC_CalcStreamBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x5, [x19, 2984]
	ldr	x0, [x19, 2944]
	ldrb	w4, [x5]
	ldr	w6, [x0, 32]
	cbz	w4, .L1582
	sub	w2, w4, #1
	mov	w7, 32
	mov	x3, 80
	add	x0, x5, 48
	mov	w1, 0
	umaddl	x3, w2, w7, x3
	add	x3, x5, x3
	.p2align 2
.L1573:
	ldr	w2, [x0], 32
	cmp	x0, x3
	add	w1, w1, w2
	bne	.L1573
.L1572:
	sbfiz	x4, x4, 5, 32
	and	w0, w6, 7
	add	x4, x5, x4
	str	w0, [x4, 60]
	ldr	x3, [x19, 2984]
	ldr	x0, [x19, 2944]
	ldrb	w2, [x3]
	ldr	w0, [x0, 32]
	add	x4, x3, x2, lsl 5
	ldr	w3, [x4, 52]
	add	w0, w3, w0, lsr 3
	sub	w0, w0, w1
	str	w0, [x4, 64]
	ldr	x3, [x19, 2984]
	ldr	x0, [x19, 2944]
	ldrb	w2, [x3]
	ldr	w0, [x0, 32]
	add	x4, x3, x2, lsl 5
	ldr	w2, [x4, 48]
	add	w1, w1, w2
	lsl	w1, w1, 3
	sub	w0, w1, w0
	str	w0, [x4, 56]
	ldr	x1, [x19, 2984]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldp	w2, w1, [x0, 60]
	ubfiz	w1, w1, 3, 2
	add	w1, w1, w2
	str	w1, [x0, 60]
	ldr	x1, [x19, 2984]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldr	w1, [x0, 64]
	and	w1, w1, -4
	str	w1, [x0, 64]
	ldr	x3, [x19, 2984]
	ldr	w2, [x3, 8]
	sub	w1, w2, #1
	cmp	w1, 1
	bhi	.L1590
	ldrb	w0, [x3]
	add	w4, w0, 1
	cmp	w4, 1
	ccmp	w2, w4, 0, ls
	bls	.L1576
	add	w2, w0, 2
	.p2align 2
.L1577:
	sub	w0, w2, #1
	cmp	w2, 1
	lsl	x1, x0, 5
	add	x0, x0, 1
	add	x3, x3, x1
	lsl	x0, x0, 5
	cset	w5, ls
	str	wzr, [x3, 60]
	ldr	x3, [x19, 2984]
	add	x4, x3, x0
	add	x3, x3, x1
	ldr	w4, [x4, 20]
	str	w4, [x3, 64]
	ldr	x3, [x19, 2984]
	add	x0, x3, x0
	add	x3, x3, x1
	ldr	w0, [x0, 16]
	lsl	w0, w0, 3
	str	w0, [x3, 56]
	ldr	x0, [x19, 2984]
	add	x0, x0, x1
	ldp	w4, w3, [x0, 60]
	ubfiz	w3, w3, 3, 4
	add	w3, w3, w4
	str	w3, [x0, 60]
	ldr	x0, [x19, 2984]
	add	x1, x0, x1
	ldr	w0, [x1, 64]
	and	w0, w0, -16
	str	w0, [x1, 64]
	ldr	x3, [x19, 2984]
	ldr	w0, [x3, 8]
	cmp	w0, w2
	add	w2, w2, 1
	cset	w1, hi
	tst	w5, w1
	bne	.L1577
	sub	w1, w0, #1
.L1576:
	ubfiz	x0, x1, 5, 32
	ldr	w1, [x3, 12]
	add	x3, x3, x0
	ldr	w0, [x3, 56]
	sub	w0, w0, w1
	str	w0, [x3, 56]
	ldr	x3, [x19, 2984]
	ldrb	w0, [x3]
	ldr	w4, [x3, 8]
	cmp	w0, w4
	bcs	.L1571
	.p2align 2
.L1585:
	ubfiz	x1, x0, 5, 32
	ldr	w2, [x19, 4888]
	add	x1, x3, x1
	add	w0, w0, 1
	ldr	w1, [x1, 64]
	cmp	w1, w2
	bcs	.L1579
	str	w1, [x19, 4888]
	ldr	w4, [x3, 8]
.L1579:
	cmp	w4, w0
	bhi	.L1585
.L1571:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1590:
	ldr	x1, .LC334
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1582:
	mov	w1, 0
	b	.L1572
	.size	HEVC_CalcStreamBits, .-HEVC_CalcStreamBits
	.align	3
.LC334:
	.xword	.LC333
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_VpsSpsPpsCheck
	.type	HEVC_VpsSpsPpsCheck, %function
HEVC_VpsSpsPpsCheck:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 164]
	ldr	w2, [x19, 5604]
	cmp	w2, w0
	bge	.L1599
	mov	w0, 5036
	ldr	x1, [x19, 2968]
	smull	x0, w2, w0
	add	x3, x1, x0
	ldrb	w0, [x1, x0]
	cbz	w0, .L1600
	ldr	w2, [x3, 32]
	ldr	w0, [x19, 160]
	cmp	w2, w0
	bge	.L1601
	ldr	x1, [x19, 2960]
	mov	w0, 12668
	smaddl	x0, w2, w0, x1
	ldrb	w1, [x0, 1]
	cbz	w1, .L1602
	ldr	w2, [x0, 48]
	ldr	w0, [x19, 156]
	cmp	w2, w0
	bcs	.L1603
	mov	w1, 24912
	ldr	x3, [x19, 2952]
	mov	w0, 0
	umull	x1, w2, w1
	ldrb	w1, [x3, x1]
	cbz	w1, .L1604
.L1593:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1599:
	ldr	x1, .LC336
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1593
	.p2align 3
.L1600:
	ldr	x1, .LC338
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1593
	.p2align 3
.L1601:
	ldr	x1, .LC340
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1593
	.p2align 3
.L1602:
	ldr	x1, .LC342
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1593
	.p2align 3
.L1603:
	ldr	x1, .LC344
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1593
	.p2align 3
.L1604:
	ldr	x1, .LC346
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1593
	.size	HEVC_VpsSpsPpsCheck, .-HEVC_VpsSpsPpsCheck
	.align	3
.LC336:
	.xword	.LC335
	.align	3
.LC338:
	.xword	.LC337
	.align	3
.LC340:
	.xword	.LC339
	.align	3
.LC342:
	.xword	.LC341
	.align	3
.LC344:
	.xword	.LC343
	.align	3
.LC346:
	.xword	.LC345
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNewPic
	.type	HEVC_IsNewPic, %function
HEVC_IsNewPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 5600]
	mov	w0, 2147483647
	ldr	x3, [x19, 2984]
	add	x8, x19, x2, lsl 2
	ldr	w5, [x8, 244]
	cmp	w5, w0
	beq	.L1640
	ldr	w1, [x3, 16]
	sub	w0, w1, #16
	cmp	w0, 2
	ccmp	w1, 21, 4, hi
	beq	.L1611
.L1621:
	cmp	w1, 1
	bls	.L1641
.L1610:
	sub	w1, w1, #19
	cmp	w1, 1
	bhi	.L1611
	mov	w5, -2147483647
	str	w5, [x8, 244]
	.p2align 2
.L1611:
	ldr	w4, [x19, 5580]
	cmp	w4, w5
	bge	.L1613
.L1646:
	ldr	w6, [x3, 16]
	sub	w0, w6, #8
	cmp	w0, 1
	bls	.L1642
.L1614:
	add	x0, x19, x2
	ldrb	w0, [x0, 12]
	cbz	w0, .L1615
	ldr	w6, [x8, 252]
	cmp	w6, w4
	bgt	.L1643
.L1615:
	add	x0, x19, 4096
	ldrb	w1, [x0, 1473]
	cbnz	w1, .L1616
	ldr	w1, [x3, 16]
	sub	w3, w1, #19
	cmp	w3, 1
	bls	.L1637
	cmp	w1, 21
	beq	.L1637
	sub	w1, w1, #16
	cmp	w1, 2
	bhi	.L1616
	add	x2, x19, x2
	str	w4, [x8, 252]
	mov	w1, 1
	strb	w1, [x2, 12]
	.p2align 2
.L1616:
	ldr	w1, [x19, 260]
	ldrb	w2, [x0, 1472]
	cbnz	w1, .L1619
	ldr	w1, [x19, 5604]
	mov	w0, 1
	ldr	w3, [x19, 328]
	cmp	w3, w1
	beq	.L1644
.L1632:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1640:
	ldr	w1, [x3, 16]
	mov	w4, 0
	sub	w6, w1, #16
	cmp	w6, 5
	cset	w0, ls
	cmp	w1, 1
	bls	.L1645
.L1607:
	orr	w4, w4, w0
	mov	w0, 2
	cbz	w4, .L1632
	cmp	w6, 2
	ccmp	w1, 21, 4, hi
	bne	.L1621
.L1622:
	ldr	w4, [x19, 5580]
	str	w4, [x8, 244]
	ldr	w0, [x3, 16]
	cmp	w0, 1
	bhi	.L1613
	mov	w0, 1
	str	w0, [x19, 356]
	.p2align 2
.L1613:
	add	x0, x19, x2
	ldrb	w5, [x0, 6]
	cbz	w5, .L1614
	ldr	w6, [x3, 16]
	sub	w0, w6, #8
	cmp	w0, 1
	bhi	.L1614
	ldr	x2, .LC347
	mov	w3, 12994
	ldr	x1, .LC351
	mov	w0, 1
	add	x2, x2, 520
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1632
	.p2align 3
.L1619:
	ldr	w0, [x19, 208]
	ldr	w1, [x19, 5604]
	ldr	w3, [x19, 328]
	cmp	w1, w0
	mov	w0, 1
	csinc	w2, w2, wzr, eq
	cmp	w3, w1
	bne	.L1632
.L1644:
	ldr	w0, [x19, 284]
	ldr	x19, [sp, 16]
	cmp	w0, w4
	csinc	w0, w2, wzr, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1643:
	ldr	w7, [x3, 16]
	sub	w1, w7, #8
	cmp	w1, 1
	bhi	.L1615
	ldr	x2, .LC347
	mov	w5, w4
	ldr	x1, .LC353
	mov	w4, w0
	mov	w3, 13003
	add	x2, x2, 520
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1632
	.p2align 3
.L1637:
	add	x2, x19, x2
	str	w4, [x8, 252]
	strb	wzr, [x2, 12]
	b	.L1616
	.p2align 3
.L1641:
	ldr	w0, [x19, 5588]
	cmp	w0, 2
	bne	.L1610
	mov	w0, 2147483647
	cmp	w5, w0
	beq	.L1622
	ldr	w4, [x19, 5580]
	cmp	w4, w5
	blt	.L1646
	b	.L1613
	.p2align 3
.L1642:
	ldr	x2, .LC347
	mov	w3, 12987
	ldr	x1, .LC349
	mov	w0, 1
	add	x2, x2, 520
	bl	dprint_vfmw
	mov	w0, 2
	b	.L1632
	.p2align 3
.L1645:
	ldr	w4, [x19, 5588]
	cmp	w4, 2
	cset	w4, eq
	b	.L1607
	.size	HEVC_IsNewPic, .-HEVC_IsNewPic
	.align	3
.LC347:
	.xword	.LANCHOR0
	.align	3
.LC349:
	.xword	.LC348
	.align	3
.LC351:
	.xword	.LC350
	.align	3
.LC353:
	.xword	.LC352
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReadByteAlignment
	.type	HEVC_ReadByteAlignment, %function
HEVC_ReadByteAlignment:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L1652
	ldr	x0, [x19, 2944]
	mov	w20, 0
	bl	BsBitsToNextByte
	mov	w1, w0
	cbz	w0, .L1649
	ldr	x0, [x19, 2944]
	bl	BsGet
	mov	w2, w0
	ldr	x1, .LC357
	mov	w0, 19
	bl	dprint_vfmw
.L1649:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1652:
	ldr	x1, .LC355
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1649
	.size	HEVC_ReadByteAlignment, .-HEVC_ReadByteAlignment
	.align	3
.LC355:
	.xword	.LC354
	.align	3
.LC357:
	.xword	.LC356
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetRapPicFlag
	.type	HEVC_GetRapPicFlag, %function
HEVC_GetRapPicFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5596]
	ldr	x19, [sp, 16]
	sub	w0, w0, #16
	cmp	w0, 5
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetRapPicFlag, .-HEVC_GetRapPicFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetIdrPicFlag
	.type	HEVC_GetIdrPicFlag, %function
HEVC_GetIdrPicFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5596]
	ldr	x19, [sp, 16]
	sub	w0, w0, #19
	cmp	w0, 1
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetIdrPicFlag, .-HEVC_GetIdrPicFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPTL
	.type	HEVC_DecPTL, %function
HEVC_DecPTL:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w24, w2
	mov	x22, x1
	mov	w23, w3
	bl	_mcount
	ldr	x0, [x20, 2944]
	cbnz	w24, .L1693
.L1691:
	mov	w1, 8
	bl	BsGet
	str	w0, [x22, 4]
	cmp	w23, wzr
	ble	.L1661
	sub	w21, w23, #1
	mov	x19, 0
	add	x21, x21, 1
	add	x25, x29, 88
	add	x22, x29, 80
	.p2align 2
.L1662:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x25, x19]
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22, x19]
	add	x19, x19, 1
	cmp	x19, x21
	bne	.L1662
	cmp	w23, 7
	mov	w19, w23
	ble	.L1680
	b	.L1672
	.p2align 3
.L1665:
	cmp	w19, 8
	beq	.L1672
.L1680:
	ldr	x0, [x20, 2944]
	mov	w1, 2
	add	w19, w19, 1
	bl	BsGet
	cbz	w0, .L1665
	ldr	x1, .LC359
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1672:
	mov	x21, 0
	.p2align 2
.L1670:
	cbz	w24, .L1667
	ldrb	w0, [x25, x21]
	cbnz	w0, .L1694
.L1667:
	ldrb	w0, [x22, x21]
	cbnz	w0, .L1695
.L1669:
	add	x21, x21, 1
	cmp	w23, w21
	bgt	.L1670
.L1661:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1695:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	b	.L1669
	.p2align 3
.L1694:
	ldr	x0, [x20, 2944]
	mov	w1, 2
	mov	w19, 32
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 5
	bl	BsGet
	.p2align 2
.L1668:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	subs	w19, w19, #1
	bne	.L1668
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 12
	bl	BsGet
	b	.L1667
.L1693:
	mov	w1, 2
	add	x19, x29, 96
	add	x21, x29, 128
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 5
	bl	BsGet
	mov	w25, w0
	.p2align 2
.L1657:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19], 1
	cmp	x19, x21
	bne	.L1657
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x22, 1]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	sub	w0, w25, #4
	cmp	w0, 3
	bls	.L1658
	ldrb	w0, [x29, 100]
	cbnz	w0, .L1658
	ldrb	w0, [x29, 101]
	cbnz	w0, .L1658
	ldrb	w0, [x29, 102]
	cbnz	w0, .L1658
	ldrb	w0, [x29, 103]
	cbnz	w0, .L1658
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 11
	bl	BsGet
	b	.L1660
	.p2align 3
.L1658:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 2
	bl	BsGet
.L1660:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	str	w25, [x20, 332]
	ldrb	w2, [x29, 97]
	ldrb	w1, [x29, 98]
	ldr	x0, [x20, 2944]
	str	w2, [x20, 336]
	str	w1, [x20, 340]
	b	.L1691
	.size	HEVC_DecPTL, .-HEVC_DecPTL
	.align	3
.LC359:
	.xword	.LC358
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetDefaultScalingList
	.type	HEVC_SetDefaultScalingList, %function
HEVC_SetDefaultScalingList:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x26, x20, 2248
	mov	w25, 0
	bl	_mcount
	ldr	x21, .LC361
	ldr	x22, .LC360
	mov	w23, 16
	ldr	x24, .LC362
.L1697:
	ldr	w0, [x26]
	cbz	w0, .L1706
	uxtw	x0, w25
	mov	w27, 0
	lsl	x28, x0, 2
	sub	x28, x28, x0
	lsl	x28, x28, 1
	.p2align 2
.L1703:
	uxtw	x19, w27
	add	x1, x21, 536
	add	x0, x19, x28
	cmp	w25, 3
	mov	x2, 64
	cbz	w25, .L1710
	add	x0, x20, x0, lsl 6
	beq	.L1711
	cmp	w27, 3
	ldr	x4, [x24, 104]
	add	x0, x0, 632
	csel	x1, x22, x1, cc
	blr	x4
.L1699:
	add	x19, x28, x19
	add	w27, w27, 1
	add	x19, x20, x19, lsl 2
	str	w23, [x19, 2264]
	ldr	w0, [x26]
	cmp	w0, w27
	bhi	.L1703
.L1706:
	add	w25, w25, 1
	add	x26, x26, 4
	cmp	w25, 4
	bne	.L1697
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1710:
	add	x0, x20, x19, lsl 6
	ldr	x1, .LC363
	ldr	x4, [x24, 104]
	mov	x2, 16
	add	x0, x0, 632
	blr	x4
	b	.L1699
.L1711:
	ldr	x0, .LC361
	uxtw	x19, w27
	cmp	w27, wzr
	ldr	x4, [x24, 104]
	add	x1, x0, 536
	ldr	x0, .LC360
	mov	x2, 64
	csel	x1, x0, x1, eq
	add	x0, x20, x19, lsl 6
	add	x0, x0, 1784
	blr	x4
	b	.L1699
	.size	HEVC_SetDefaultScalingList, .-HEVC_SetDefaultScalingList
	.align	3
.LC360:
	.xword	.LANCHOR2
	.align	3
.LC361:
	.xword	.LANCHOR0
	.align	3
.LC362:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC363:
	.xword	.LANCHOR0+600
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SetScalingList
	.type	HEVC_SetScalingList, %function
HEVC_SetScalingList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 3008]
	ldrb	w1, [x0, 3]
	cbz	w1, .L1744
	ldrb	w1, [x19, 1]
	ldr	x20, [x19, 3016]
	cmp	w1, 1
	beq	.L1760
.L1714:
	ldrb	w1, [x20, 21]
	cbnz	w1, .L1754
	ldrb	w1, [x0, 4]
	cbz	w1, .L1718
.L1755:
	adds	x20, x0, 432
	cset	w0, eq
.L1723:
	cbnz	w0, .L1718
.L1726:
	ldr	x21, .LC364
	mov	x2, 1536
	mov	w1, 0
	add	x0, x19, 632
	ldr	x3, [x21, 96]
	blr	x3
	add	x16, x20, 1
	add	x15, x19, 360
	mov	w12, 0
	mov	w17, 64
	mov	w14, 6
.L1727:
	ldr	w13, [x15, 1888]
	cbz	w13, .L1736
	ldr	w8, [x15]
	mov	x9, x16
	mov	w11, 0
	cmp	w8, 64
	csel	w8, w8, w17, ls
	lsr	w10, w8, 2
.L1734:
	uxtw	x7, w11
	mov	w4, 0
	umaddl	x7, w12, w14, x7
	lsl	x7, x7, 4
	.p2align 2
.L1728:
	cmp	w10, w4
	bls	.L1731
	cbz	w8, .L1728
	add	x0, x7, x4, uxtw
	ldrb	w1, [x9, -1]
	mov	x6, x9
	mov	w3, 0
	add	x0, x19, x0, lsl 2
	ldr	w2, [x0, 632]
	orr	w1, w2, w1
	str	w1, [x0, 632]
	.p2align 2
.L1739:
	add	w3, w3, 1
	add	x0, x7, x4, uxtw
	cmp	w8, w3
	and	w5, w3, 3
	add	x0, x19, x0, lsl 2
	lsl	w1, w5, 3
	beq	.L1728
	ldrb	w2, [x6], 1
	cmp	w5, 3
	ldr	w5, [x0, 632]
	csinc	w4, w4, w4, ne
	lsl	w1, w2, w1
	orr	w1, w5, w1
	str	w1, [x0, 632]
	b	.L1739
.L1731:
	add	w11, w11, 1
	add	x9, x9, 64
	cmp	w11, w13
	bne	.L1734
.L1736:
	add	w12, w12, 1
	add	x16, x16, 384
	cmp	w12, 4
	add	x15, x15, 4
	bne	.L1727
	ldr	x3, [x21, 104]
	mov	x2, 96
	add	x1, x20, 1536
	add	x0, x19, 2264
	blr	x3
.L1744:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1720:
	ldrb	w1, [x20, 21]
	cbz	w1, .L1755
.L1754:
	adds	x20, x20, 256
	cset	w0, eq
	cbz	w0, .L1726
.L1718:
	mov	x0, x19
	bl	HEVC_SetDefaultScalingList
.L1763:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1760:
	ldrb	w1, [x20, 1889]
	cmp	w1, 1
	beq	.L1761
	add	x2, x0, 12288
	ldrb	w2, [x2, 372]
	cmp	w2, 1
	bne	.L1714
	ldrb	w2, [x0, 4]
	cbnz	w2, .L1720
	ldrb	w2, [x20, 21]
	orr	w1, w1, w2
	cbnz	w1, .L1721
	ldrsw	x0, [x0, 12664]
	mov	w20, 12668
	ldr	x1, [x19, 2960]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 228]
	smaddl	x20, w0, w20, x1
	ldrb	w0, [x20, 4]
	cmp	w0, 1
	bne	.L1718
	adds	x20, x20, 432
	cset	w0, eq
	b	.L1723
.L1761:
	ldrsw	x1, [x20, 1956]
	mov	w20, 5036
	ldr	x2, [x19, 2968]
	mov	w4, 12668
	ldr	x0, [x19, 2960]
	add	x1, x19, x1, lsl 2
	ldr	w3, [x1, 236]
	ldr	w1, [x1, 228]
	smaddl	x2, w3, w20, x2
	smaddl	x0, w1, w4, x0
	ldrb	w1, [x2, 21]
	cmp	w1, 1
	beq	.L1762
	ldrb	w1, [x0, 4]
	cmp	w1, 1
	beq	.L1755
	mov	x0, x19
	bl	HEVC_SetDefaultScalingList
	b	.L1763
.L1721:
	cbnz	w2, .L1754
	mov	x0, x19
	bl	HEVC_SetDefaultScalingList
	b	.L1763
.L1762:
	adds	x20, x2, 256
	cset	w0, eq
	b	.L1723
	.size	HEVC_SetScalingList, .-HEVC_SetScalingList
	.align	3
.LC364:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CalScalingList
	.type	HEVC_CalScalingList, %function
HEVC_CalScalingList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	uxtw	x22, w3
	mov	x21, x1
	bl	_mcount
	add	x0, x20, x19, uxtw 2
	mov	w9, 6
	mov	w8, 64
	mov	w5, 0
	umaddl	x9, w19, w9, x22
	ldr	w0, [x0, 360]
	lsl	x9, x9, 4
	cmp	w0, w8
	csel	w8, w0, w8, ls
	lsr	w10, w8, 2
	.p2align 2
.L1765:
	cmp	w5, w10
	bcs	.L1764
	cbz	w8, .L1765
	add	x0, x9, x5, uxtw
	mov	x7, x21
	mov	w4, 0
	add	x0, x20, x0, lsl 2
	ldrb	w2, [x7], 1
	ldr	w3, [x0, 632]
	orr	w2, w3, w2
	str	w2, [x0, 632]
	.p2align 2
.L1771:
	add	w4, w4, 1
	add	x0, x9, x5, uxtw
	cmp	w8, w4
	and	w6, w4, 3
	add	x0, x20, x0, lsl 2
	lsl	w2, w6, 3
	beq	.L1765
	ldrb	w3, [x7], 1
	cmp	w6, 3
	ldr	w6, [x0, 632]
	csinc	w5, w5, w5, ne
	lsl	w2, w3, w2
	orr	w2, w6, w2
	str	w2, [x0, 632]
	b	.L1771
.L1764:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_CalScalingList, .-HEVC_CalScalingList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetScalingListDefaultAddress
	.type	HEVC_GetScalingListDefaultAddress, %function
HEVC_GetScalingListDefaultAddress:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 3
	bls	.L1785
	ldr	x1, .LC368
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1785:
	ldr	x0, .LC366
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1775
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1775:
	.section	.rodata
	.align	0
	.align	2
.L1775:
	.byte	(.L1779 - .Lrtx1775) / 4
	.byte	(.L1777 - .Lrtx1775) / 4
	.byte	(.L1777 - .Lrtx1775) / 4
	.byte	(.L1778 - .Lrtx1775) / 4
	.text
	.p2align 3
.L1777:
	cmp	w20, 2
	ldr	x0, .LC365
	bhi	.L1782
.L1783:
	add	x0, x0, 144
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1778:
	ldr	x0, .LC365
	cbz	w20, .L1783
.L1782:
	add	x0, x0, 80
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1779:
	ldr	x0, .LC365
	ldp	x19, x20, [sp, 16]
	add	x0, x0, 64
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetScalingListDefaultAddress, .-HEVC_GetScalingListDefaultAddress
	.align	3
.LC365:
	.xword	.LANCHOR2
	.align	3
.LC366:
	.xword	.L1775
	.align	3
.LC368:
	.xword	.LC367
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecRefPicListsModification
	.type	HEVC_DecRefPicListsModification, %function
HEVC_DecRefPicListsModification:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	mov	x23, x2
	mov	w20, w3
	bl	_mcount
	cmp	x21, xzr
	ccmp	x23, xzr, 4, ne
	ccmp	x22, xzr, 4, ne
	beq	.L1796
	sub	w0, w20, #1
	mov	w19, 1
	asr	w0, w0, 1
	cbz	w0, .L1788
	.p2align 2
.L1789:
	asr	w0, w0, 1
	add	w19, w19, 1
	cbnz	w0, .L1789
.L1788:
	ldr	x0, [x22, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w20, 1
	strb	w0, [x23]
	cset	w24, hi
	cmp	w0, wzr
	cset	w0, ne
	tst	w24, w0
	beq	.L1793
	ldr	w0, [x21, 76]
	cbz	w0, .L1793
	mov	w20, 0
	.p2align 2
.L1794:
	ldr	x0, [x22, 2944]
	mov	w1, w19
	bl	BsGet
	add	x1, x23, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 4]
	ldr	w0, [x21, 76]
	cmp	w0, w20
	bhi	.L1794
.L1793:
	ldr	w0, [x21, 20]
	cbz	w0, .L1811
.L1792:
	mov	w0, 0
.L1787:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1811:
	ldr	x0, [x22, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, wzr
	strb	w0, [x23, 1]
	cset	w0, ne
	tst	w24, w0
	beq	.L1792
	ldr	w0, [x21, 80]
	cbz	w0, .L1792
	mov	w20, 0
	.p2align 2
.L1795:
	ldr	x0, [x22, 2944]
	mov	w1, w19
	bl	BsGet
	add	x1, x23, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 132]
	ldr	w0, [x21, 80]
	cmp	w0, w20
	bhi	.L1795
	b	.L1792
.L1796:
	mov	w0, -1
	b	.L1787
	.size	HEVC_DecRefPicListsModification, .-HEVC_DecRefPicListsModification
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_MoreRbspData
	.type	HEVC_MoreRbspData, %function
HEVC_MoreRbspData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2944]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L1814
	ldr	x1, [x19, 2984]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w1, [x1, 12]
	add	w1, w1, 3
	cmp	w1, w0
	cset	w0, cc
	ret
	.p2align 3
.L1814:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_MoreRbspData, .-HEVC_MoreRbspData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_More_Rbsp_Data
	.type	HEVC_More_Rbsp_Data, %function
HEVC_More_Rbsp_Data:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2944]
	ldr	w2, [x0, 24]
	ldr	w3, [x0, 32]
	lsl	w2, w2, 3
	cmp	w2, w3
	bls	.L1818
	mov	w1, 8
	bl	BsShow
	cmp	w0, 128
	cset	w0, ne
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1818:
	ldr	x1, .LC370
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_More_Rbsp_Data, .-HEVC_More_Rbsp_Data
	.align	3
.LC370:
	.xword	.LC369
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FindTrailZeros
	.type	HEVC_FindTrailZeros, %function
HEVC_FindTrailZeros:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
.L1832:
	ldr	x1, [x20, 2984]
	mov	w3, 0
	ldr	w5, [x1, 8]
	sub	w5, w5, #1
	add	x2, x1, x5, lsl 5
	ldr	w0, [x2, 48]
	ldr	x2, [x2, 40]
	sub	x0, x0, #1
	add	x0, x2, x0
	.p2align 2
.L1820:
	ldrb	w2, [x0]
	add	x19, x5, 1
	lsl	x19, x19, 5
	add	x4, x1, x19
	cbnz	w2, .L1833
	ldr	x2, [x1, 40]
	add	w3, w3, 1
	cmp	x0, x2
	beq	.L1834
	ldr	x2, [x4, 8]
	cmp	x0, x2
	sub	x0, x0, #1
	bne	.L1820
	add	x1, x1, x5, lsl 5
	ldr	w0, [x20, 276]
	ldr	w1, [x1, 68]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x20, 2984]
	add	x19, x0, x19
	str	xzr, [x19, 8]
	ldr	x1, [x20, 2984]
	ldr	w0, [x1, 8]
	sub	w0, w0, #1
	str	w0, [x1, 8]
	b	.L1832
	.p2align 3
.L1833:
	mov	w0, 1
	mov	w5, w0
	tbnz	x2, 0, .L1827
	.p2align 2
.L1830:
	lsl	w4, w5, w0
	add	w0, w0, 1
	tst	w4, w2
	bne	.L1827
	cmp	w0, 8
	bne	.L1830
	ldr	x1, .LC374
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1834:
	ldr	x1, .LC372
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1827:
	str	wzr, [x1, 4]
	add	w3, w0, w3, lsl 3
	mov	w0, 0
	ldr	x1, [x20, 2984]
	str	w3, [x1, 12]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FindTrailZeros, .-HEVC_FindTrailZeros
	.align	3
.LC372:
	.xword	.LC371
	.align	3
.LC374:
	.xword	.LC373
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FindNaluArraySlot
	.type	HEVC_FindNaluArraySlot, %function
HEVC_FindNaluArraySlot:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19, 168]
	ldr	w0, [x19, 148]
	add	w3, w3, 1
	cmp	w3, wzr
	ble	.L1836
	udiv	w1, w0, w3
	mov	w4, 104
	ldr	x5, [x19, 3032]
	msub	w0, w1, w3, w0
	umull	x1, w0, w4
	add	x1, x5, x1
	ldr	w1, [x1, 32]
	cbz	w1, .L1837
	mov	w1, 0
	b	.L1839
	.p2align 3
.L1840:
	udiv	w0, w2, w3
	msub	w0, w0, w3, w2
	umull	x2, w0, w4
	add	x2, x5, x2
	ldr	w2, [x2, 32]
	cbz	w2, .L1837
.L1839:
	add	w1, w1, 1
	cmp	w3, w1
	add	w2, w1, w0
	bne	.L1840
.L1836:
	str	w0, [x19, 148]
.L1851:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1837:
	cmp	w0, w3
	str	w0, [x19, 148]
	bcs	.L1851
	mov	w1, 104
	mov	w2, 1
	umull	x1, w0, w1
	add	x5, x5, x1
	str	w2, [x5, 32]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FindNaluArraySlot, .-HEVC_FindNaluArraySlot
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReleaseNAL
	.type	HEVC_ReleaseNAL, %function
HEVC_ReleaseNAL:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1861
	ldr	x24, .LC377
	add	x19, x20, 40
	ldr	x23, .LC379
	add	x22, x20, 104
	stp	wzr, wzr, [x20, 32]
.L1856:
	ldr	x1, [x19]
	mov	w0, w21
	cbz	x1, .L1855
	ldr	w1, [x19, 28]
	bl	SM_ReleaseStreamSeg
	ldr	w4, [x19, 8]
	mov	x2, x24
	ldr	x3, [x19]
	mov	x1, x23
	mov	w0, 7
	bl	dprint_vfmw
	str	xzr, [x19]
	str	wzr, [x19, 8]
	str	wzr, [x19, 20]
.L1855:
	add	x19, x19, 32
	cmp	x19, x22
	bne	.L1856
	ldr	x3, .LC380
	mov	x2, 104
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
.L1852:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1861:
	ldr	x2, .LC375
	mov	w3, 14320
	ldr	x1, .LC376
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1852
	.size	HEVC_ReleaseNAL, .-HEVC_ReleaseNAL
	.align	3
.LC375:
	.xword	.LC2
	.align	3
.LC376:
	.xword	.LC4
	.align	3
.LC377:
	.xword	.LANCHOR3
	.align	3
.LC379:
	.xword	.LC378
	.align	3
.LC380:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDecBuffers
	.type	HEVC_InitDecBuffers, %function
HEVC_InitDecBuffers:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	beq	.L1901
.L1863:
	ldr	x0, [x20, 3008]
	ldr	w0, [x0, 184]
	add	w0, w0, 1
	str	w0, [x20, 3376]
.L1864:
	cmp	w0, 17
	bhi	.L1902
.L1865:
	add	x2, x20, 3328
	add	x0, x20, 3416
	add	x1, x20, 3552
	stp	wzr, wzr, [x2, 52]
	stp	wzr, wzr, [x2, 60]
	str	wzr, [x20, 3396]
	str	wzr, [x20, 3404]
	str	wzr, [x20, 3408]
	.p2align 2
.L1866:
	str	xzr, [x0]
	add	x0, x0, 8
	str	xzr, [x0, 128]
	str	xzr, [x0, 264]
	str	xzr, [x0, 400]
	str	xzr, [x0, 536]
	str	xzr, [x0, 672]
	cmp	x0, x1
	bne	.L1866
	add	x26, x20, 12288
	ldr	x22, .LC384
	add	x19, x26, 2464
	mov	w21, 0
	mov	w25, 20
	mov	w24, 16
	.p2align 2
.L1867:
	ldr	x3, [x22, 96]
	add	x0, x19, 88
	mov	x2, 640
	mov	w1, 0
	mov	w23, 16
	blr	x3
	str	w21, [x19, 236]
	add	w21, w21, 1
	strb	wzr, [x19]
	strb	wzr, [x19, 1]
	cmp	w21, 20
	strb	wzr, [x19, 2]
	str	wzr, [x19, 8]
	stp	w25, w24, [x19, 20]
	str	wzr, [x19, 48]
	str	wzr, [x19, 56]
	str	x19, [x19, 80]
	add	x19, x19, 728
	bne	.L1867
	ldr	x3, [x22, 96]
	mov	x2, 280
	mov	w1, 0
	add	x0, x26, 1900
	blr	x3
	str	w23, [x20, 14188]
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 280
	add	x0, x26, 2180
	str	wzr, [x20, 14192]
	blr	x3
	str	w23, [x20, 14468]
	add	x1, x20, 3064
	add	x0, x20, 3200
	str	wzr, [x20, 14472]
	.p2align 2
.L1868:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L1868
	add	x1, x20, 3336
	str	wzr, [x20, 5636]
	.p2align 2
.L1869:
	str	xzr, [x0], 8
	cmp	x1, x0
	bne	.L1869
	ldr	w0, [x20, 184]
	str	wzr, [x20, 5640]
	cbz	w0, .L1874
	sub	w1, w0, #1
	add	x0, x20, 2168
	add	x1, x1, 543
	add	x1, x20, x1, lsl 2
	.p2align 2
.L1873:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L1873
.L1874:
	ldr	w3, [x20, 168]
	mov	w19, 0
	cbz	w3, .L1862
	.p2align 2
.L1891:
	ldr	x0, [x20, 3024]
	uxtw	x21, w19
	ldr	x0, [x0, w19, uxtw 3]
	add	w19, w19, 1
	mov	x1, x0
	cbz	x0, .L1875
	ldr	x2, [x20, 2984]
	cmp	x0, x2
	beq	.L1875
	ldr	w0, [x20, 276]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 3024]
	mov	w2, 2
	str	xzr, [x0, x21, lsl 3]
	ldr	w1, [x20, 204]
	ldr	w0, [x20, 260]
	ldr	w4, [x20, 176]
	cmp	w1, wzr
	cset	w7, ne
	cmp	w0, wzr
	cset	w5, ne
	sub	w6, w4, #1
	cmp	w4, 3
	ldr	w3, [x20, 168]
	sub	w1, w1, w7
	csel	w2, w6, w2, cs
	sub	w0, w0, w5
	str	w2, [x20, 176]
	str	w1, [x20, 204]
	str	w0, [x20, 260]
.L1875:
	cmp	w3, w19
	bhi	.L1891
.L1862:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1902:
	ldr	x2, .LC381
	mov	w4, 17
	ldr	x1, .LC383
	mov	w3, w4
	add	x2, x2, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 17
	str	w0, [x20, 3376]
	b	.L1865
	.p2align 3
.L1901:
	ldr	x0, [x20, 3040]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L1863
	ldr	w0, [x20, 2392]
	cbz	w0, .L1863
	ldr	x1, [x20, 3008]
	ldr	w1, [x1, 184]
	mul	w0, w0, w1
	add	w0, w0, 1
	str	w0, [x20, 3376]
	b	.L1864
	.size	HEVC_InitDecBuffers, .-HEVC_InitDecBuffers
	.align	3
.LC381:
	.xword	.LANCHOR3
	.align	3
.LC383:
	.xword	.LC382
	.align	3
.LC384:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_EmptyFrmFromDPB
	.type	HEVC_EmptyFrmFromDPB, %function
HEVC_EmptyFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1914
	ldr	w3, [x20, 3380]
	mov	w0, 0
	mov	w4, 1
	cbz	w3, .L1909
	.p2align 2
.L1923:
	add	x1, x20, x0, uxtw 3
	add	w0, w0, 1
	ldr	x1, [x1, 3688]
	ldrb	w2, [x1, 2]
	cbnz	w2, .L1907
	strb	w4, [x1, 2]
	ldr	w3, [x20, 3380]
.L1907:
	cmp	w3, w0
	bhi	.L1923
.L1909:
	mov	w0, -2147483647
	add	x19, x20, 3688
	add	x21, x20, 3824
	stp	w0, w0, [x20, 212]
	.p2align 2
.L1906:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L1910
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L1910:
	ldr	x0, [x19, 136]
	mov	w2, 1
	cbz	x0, .L1911
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L1911:
	ldr	x0, [x19, 272]
	mov	w2, 1
	cbz	x0, .L1912
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L1912:
	ldr	x0, [x19, 408]
	mov	w2, 1
	cbz	x0, .L1913
	ldr	w1, [x0, 28]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L1913:
	str	xzr, [x19, 136]
	str	xzr, [x19, 272]
	str	xzr, [x19, 408]
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L1906
	mov	x0, x20
	bl	HEVC_InitDecBuffers
	mov	w0, 0
.L1904:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1914:
	mov	w0, -1
	b	.L1904
	.size	HEVC_EmptyFrmFromDPB, .-HEVC_EmptyFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CombinePacket
	.type	HEVC_CombinePacket, %function
HEVC_CombinePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2984]
	cbz	x0, .L1933
	ldr	w0, [x0, 48]
	cmp	w0, 4095
	bhi	.L1930
	ldr	x1, .LC388
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	ldr	x3, .LC389
	ldr	w2, [x1, 48]
	ldr	x0, [x1, 72]
	ldr	x3, [x3, 104]
	ldr	x1, [x1, 40]
	sub	x0, x0, x2
	blr	x3
	ldr	x0, [x19, 2984]
	mov	w3, 1
	ldr	w2, [x0, 100]
	ldr	w1, [x0, 68]
	str	w2, [x0, 68]
	ldr	x0, [x19, 2984]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 2984]
	ldr	w4, [x0, 48]
	ldr	x2, [x0, 72]
	sub	x2, x2, x4
	str	x2, [x0, 40]
	ldr	x0, [x19, 2984]
	ldr	w4, [x0, 48]
	ldr	w2, [x0, 84]
	sub	w2, w2, w4
	str	w2, [x0, 52]
	ldr	x0, [x19, 2984]
	ldr	w4, [x0, 48]
	ldr	w2, [x0, 80]
	add	w2, w4, w2
	str	w2, [x0, 48]
	ldr	x0, [x19, 2984]
	str	w3, [x0, 8]
	ldr	w0, [x19, 276]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 2984]
	str	xzr, [x0, 72]
	ldr	x0, [x19, 2984]
	str	wzr, [x0, 92]
	ldr	x0, [x19, 2984]
	str	wzr, [x0, 80]
.L1930:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1933:
	ldr	x1, .LC386
	bl	dprint_vfmw
	b	.L1930
	.size	HEVC_CombinePacket, .-HEVC_CombinePacket
	.align	3
.LC386:
	.xword	.LC385
	.align	3
.LC388:
	.xword	.LC387
	.align	3
.LC389:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsOutDPB
	.type	HEVC_IsOutDPB, %function
HEVC_IsOutDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1939
	ldr	w3, [x19, 3380]
	cbz	w3, .L1939
	ldr	x0, [x19, 3688]
	cmp	x20, x0
	beq	.L1941
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1936
	.p2align 3
.L1937:
	ldr	x2, [x0, 3688]
	cmp	x20, x2
	beq	.L1941
.L1936:
	cmp	x0, x3
	add	x0, x0, 8
	bne	.L1937
.L1939:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1941:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsOutDPB, .-HEVC_IsOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsNewPicNal
	.type	HEVC_IsNewPicNal, %function
HEVC_IsNewPicNal:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	HEVC_IsNewPicNal, .-HEVC_IsNewPicNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_u_v
	.type	HEVC_u_v, %function
HEVC_u_v:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_u_v, .-HEVC_u_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_f_v
	.type	HEVC_f_v, %function
HEVC_f_v:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_f_v, .-HEVC_f_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ue_v
	.type	HEVC_ue_v, %function
HEVC_ue_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	bls	.L1948
	mov	w0, -4370
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1948:
	mov	w1, w0
	mov	x0, x19
	add	w21, w1, 1
	bl	BsSkip
	mov	w1, w21
	mov	x0, x19
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w21
	mov	x0, x19
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ue_v, .-HEVC_ue_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Tone_Mapping_Info
	.type	HEVC_Sei_Tone_Mapping_Info, %function
HEVC_Sei_Tone_Mapping_Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC391
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1969
.L1954:
	ldr	x0, [x19, 2944]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 32
	bl	BsGet
	mov	w0, 0
.L1952:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1969:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 8
	mov	w22, w0
	bhi	.L1970
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 4
	mov	w1, w0
	mov	w0, 0
	bhi	.L1952
	ldr	x0, .LC394
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx1953
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1953:
	.section	.rodata
	.align	0
	.align	2
.L1953:
	.byte	(.L1954 - .Lrtx1953) / 4
	.byte	(.L1954 - .Lrtx1953) / 4
	.byte	(.L1955 - .Lrtx1953) / 4
	.byte	(.L1956 - .Lrtx1953) / 4
	.byte	(.L1957 - .Lrtx1953) / 4
	.text
	.p2align 3
.L1955:
	mov	w2, 1
	lsl	w22, w2, w22
	cbz	w22, .L1968
	add	w21, w21, 7
	mov	w20, 0
	and	w21, w21, -8
	.p2align 2
.L1959:
	ldr	x0, [x19, 2944]
	mov	w1, w21
	add	w20, w20, 1
	bl	BsGet
	cmp	w22, w20
	bne	.L1959
.L1968:
	mov	w0, 0
.L1971:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1956:
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	cmp	w0, 256
	mov	w23, w0
	bhi	.L1961
	cbz	w0, .L1968
	add	w21, w21, 7
	add	w22, w22, 7
	and	w21, w21, -8
	and	w22, w22, -8
	mov	w20, 0
	.p2align 2
.L1963:
	ldr	x0, [x19, 2944]
	mov	w1, w21
	add	w20, w20, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, w22
	bl	BsGet
	cmp	w20, w23
	bne	.L1963
	mov	w0, 0
	b	.L1971
	.p2align 3
.L1957:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 255
	beq	.L1972
.L1964:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	mov	w0, 0
	b	.L1971
	.p2align 3
.L1972:
	ldr	x0, [x19, 2944]
	mov	w1, 32
	bl	BsGet
	b	.L1964
.L1970:
	ldr	x1, .LC393
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1952
.L1961:
	ldr	x1, .LC396
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1952
	.size	HEVC_Sei_Tone_Mapping_Info, .-HEVC_Sei_Tone_Mapping_Info
	.align	3
.LC391:
	.xword	.LC390
	.align	3
.LC393:
	.xword	.LC392
	.align	3
.LC394:
	.xword	.L1953
	.align	3
.LC396:
	.xword	.LC395
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Frame_Packing_Arrangement
	.type	HEVC_Sei_Frame_Packing_Arrangement, %function
HEVC_Sei_Frame_Packing_Arrangement:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC398
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1974
	ldr	x0, [x19, 2944]
	mov	w1, 7
	bl	BsGet
	mov	w21, w0
	sub	w0, w0, #3
	cmp	w0, 2
	bhi	.L1981
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w20, w0
	ldr	x0, [x19, 2944]
	mov	w1, 6
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	cmp	w20, wzr
	ccmp	w21, 5, 4, eq
	bne	.L1982
.L1977:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
.L1974:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L1976:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1982:
	ldr	x0, [x19, 2944]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 4
	bl	BsGet
	b	.L1977
	.p2align 3
.L1981:
	ldr	x1, .LC400
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1976
	.size	HEVC_Sei_Frame_Packing_Arrangement, .-HEVC_Sei_Frame_Packing_Arrangement
	.align	3
.LC398:
	.xword	.LC397
	.align	3
.LC400:
	.xword	.LC399
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Dec_Unit_Info
	.type	HEVC_Sei_Dec_Unit_Info, %function
HEVC_Sei_Dec_Unit_Info:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	cmp	x21, xzr
	ccmp	x20, xzr, 4, ne
	ccmp	x19, xzr, 4, ne
	beq	.L1987
	ldr	x1, .LC402
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldrb	w0, [x20, 3]
	cbnz	w0, .L1994
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L1995
.L1986:
	ldr	x0, [x19, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L1984:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1994:
	ldr	w1, [x20, 4]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L1986
.L1995:
	ldr	w1, [x20, 8]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	b	.L1986
	.p2align 3
.L1987:
	mov	w0, -1
	b	.L1984
	.size	HEVC_Sei_Dec_Unit_Info, .-HEVC_Sei_Dec_Unit_Info
	.align	3
.LC402:
	.xword	.LC401
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Active_Param_sets
	.type	HEVC_Sei_Active_Param_sets, %function
HEVC_Sei_Active_Param_sets:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x1, .LC404
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 15
	bgt	.L1997
	tbnz	w0, #31, .L2001
	ldr	x22, .LC408
	add	w21, w0, 1
	mov	w19, 0
	.p2align 2
.L2000:
	ldr	x0, [x20, 2944]
	mov	x1, x22
	add	w19, w19, 1
	bl	HEVC_ue_v
	cmp	w21, w19
	bne	.L2000
.L2001:
	ldr	x0, [x20, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L1999:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1997:
	ldr	x1, .LC406
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1999
	.size	HEVC_Sei_Active_Param_sets, .-HEVC_Sei_Active_Param_sets
	.align	3
.LC404:
	.xword	.LC403
	.align	3
.LC406:
	.xword	.LC405
	.align	3
.LC408:
	.xword	.LC407
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Buf_Period
	.type	HEVC_Sei_Buf_Period, %function
HEVC_Sei_Buf_Period:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x22, x2
	bl	_mcount
	ldr	x1, .LC410
	ldr	x0, [x19, 2944]
	str	wzr, [x19, 12760]
	bl	HEVC_ue_v
	cmp	w0, 15
	bhi	.L2029
	add	x0, x19, 12288
	mov	w1, 1
	mov	w24, 0
	strb	w1, [x0, 465]
	ldrb	w0, [x22, 2]
	cbz	w0, .L2030
.L2006:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	mov	w21, w1
	mov	w20, 0
	bl	BsGet
	strb	w0, [x23]
	ldr	w1, [x22, 16]
	ldr	x0, [x19, 2944]
	add	w1, w1, w21
	bl	BsGet
.L2007:
	cbz	w20, .L2031
	cmp	w20, 1
	beq	.L2032
.L2012:
	cmp	w21, 1
	bhi	.L2011
.L2010:
	add	w20, w20, 1
	add	w21, w21, 1
	b	.L2007
	.p2align 3
.L2011:
	ldr	x0, [x19, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L2027:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2030:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w24, w0
	cbz	w24, .L2006
	ldr	w1, [x22, 16]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 20]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	b	.L2006
.L2029:
	ldr	x1, .LC412
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2027
.L2031:
	ldrb	w0, [x22]
	cbz	w0, .L2012
	ldr	w0, [x22, 24]
	mov	w23, 0
	cmn	w0, #1
	bne	.L2015
	b	.L2010
	.p2align 3
.L2014:
	ldr	w0, [x22, 24]
	add	w0, w0, 1
	cmp	w0, w23
	bls	.L2012
.L2015:
	ldr	w1, [x22, 12]
	add	w23, w23, 1
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	ldrb	w0, [x22, 2]
	orr	w0, w0, w24
	cbz	w0, .L2014
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	ldr	w1, [x22, 12]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	b	.L2014
.L2032:
	ldrb	w0, [x22, 1]
	cbz	w0, .L2011
	ldr	w0, [x22, 24]
	cmn	w0, #1
	beq	.L2011
	mov	w23, 0
	b	.L2015
	.size	HEVC_Sei_Buf_Period, .-HEVC_Sei_Buf_Period
	.align	3
.LC410:
	.xword	.LC409
	.align	3
.LC412:
	.xword	.LC411
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Pic_Timming
	.type	HEVC_Sei_Pic_Timming, %function
HEVC_Sei_Pic_Timming:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	x22, x1
	bl	_mcount
	ldr	w1, [x19, 12756]
	ldr	w0, [x19, 12760]
	add	w1, w1, 1
	str	w1, [x19, 12756]
	add	w0, w0, 1
	str	w0, [x19, 12760]
	ldrb	w0, [x20, 2]
	cbnz	w0, .L2060
.L2034:
	ldrh	w0, [x20, 44]
	add	x21, x20, 44
	cbz	w0, .L2036
	ldr	w1, [x21, 16]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x22, 8]
	ldr	w1, [x21, 20]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	str	w0, [x22, 12]
	ldrb	w0, [x21, 2]
	cbnz	w0, .L2037
.L2040:
	ldrsw	x1, [x19, 276]
	ldr	x0, .LC413
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L2061
.L2036:
	ldr	x0, [x19, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L2043:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2060:
	ldr	x0, [x19, 2944]
	mov	w1, 4
	bl	BsGet
	str	w0, [x22]
	mov	w1, 2
	ldr	x0, [x19, 2944]
	bl	BsGet
	str	w0, [x22, 4]
	mov	w1, 1
	ldr	x0, [x19, 2944]
	bl	BsGet
	b	.L2034
	.p2align 3
.L2061:
	ldr	x1, [x0, 160]
	mov	x0, 1
	movk	x0, 0x2, lsl 32
	cmp	x1, x0
	bne	.L2036
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L2036
	.p2align 3
.L2037:
	ldr	w1, [x21, 8]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	ldrb	w0, [x21, 2]
	cbz	w0, .L2040
	ldrb	w0, [x21, 3]
	cbz	w0, .L2040
	ldr	x1, .LC415
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	mov	w23, w0
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w24, w0
	cbnz	w24, .L2062
.L2041:
	cmp	w23, 255
	bhi	.L2063
	ldr	x25, .LC419
	add	w23, w23, 1
	mov	w22, 0
	b	.L2045
	.p2align 3
.L2044:
	cmp	w22, w23
	beq	.L2040
.L2045:
	ldr	x0, [x19, 2944]
	mov	x1, x25
	add	w22, w22, 1
	bl	HEVC_ue_v
	cbnz	w24, .L2044
	ldr	w1, [x21, 4]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	b	.L2044
	.p2align 3
.L2062:
	ldr	w1, [x21, 4]
	ldr	x0, [x19, 2944]
	add	w1, w1, 1
	bl	BsGet
	b	.L2041
.L2063:
	ldr	x1, .LC417
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2043
	.size	HEVC_Sei_Pic_Timming, .-HEVC_Sei_Pic_Timming
	.align	3
.LC413:
	.xword	s_pstVfmwChan
	.align	3
.LC415:
	.xword	.LC414
	.align	3
.LC417:
	.xword	.LC416
	.align	3
.LC419:
	.xword	.LC418
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Color_Volume_Reconstruction_Info
	.type	HEVC_Sei_Color_Volume_Reconstruction_Info, %function
HEVC_Sei_Color_Volume_Reconstruction_Info:
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
	beq	.L2074
	ldr	x1, .LC421
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2066
.L2070:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x20]
.L2065:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2066:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	beq	.L2079
.L2067:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	mov	w21, 0
	bl	BsGet
	strb	w0, [x20, 2]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	strb	w0, [x20, 3]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	strb	w0, [x20, 4]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	strb	w0, [x20, 5]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	strb	w0, [x20, 6]
	mov	w1, 4
	ldr	x0, [x19, 2944]
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x20, 7]
	cbz	w1, .L2072
	.p2align 2
.L2076:
	add	x22, x20, x21, uxtw
	ldr	x0, [x19, 2944]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	strb	w0, [x22, 8]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	strb	w0, [x22, 23]
	ldrb	w0, [x20, 7]
	cmp	w0, w21
	bhi	.L2076
.L2072:
	ldr	x0, [x19, 2944]
	mov	w1, 4
	mov	w21, 0
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x20, 38]
	cbz	w1, .L2070
	.p2align 2
.L2075:
	add	x22, x20, x21, uxtw
	ldr	x0, [x19, 2944]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	strb	w0, [x22, 39]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	strb	w0, [x22, 54]
	ldrb	w0, [x20, 38]
	cmp	w0, w21
	bhi	.L2075
	b	.L2070
	.p2align 3
.L2074:
	mov	w0, -1
	b	.L2065
	.p2align 3
.L2079:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x20, 1]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	b	.L2067
	.size	HEVC_Sei_Color_Volume_Reconstruction_Info, .-HEVC_Sei_Color_Volume_Reconstruction_Info
	.align	3
.LC421:
	.xword	.LC420
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_User_Data_Registered_Itu_T_T35
	.type	HEVC_Sei_User_Data_Registered_Itu_T_T35, %function
HEVC_Sei_User_Data_Registered_Itu_T_T35:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	w21, w2
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L2087
	cmp	w21, 3
	bls	.L2091
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 2
	beq	.L2092
	cmp	w0, 4
	beq	.L2093
	subs	w21, w21, #4
	mov	w19, 0
	beq	.L2086
	.p2align 2
.L2089:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w21, w19
	bne	.L2089
.L2086:
	mov	w0, 0
.L2081:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2092:
	add	x1, x20, 4096
	mov	x0, x20
	add	x1, x1, 192
	bl	HEVC_Sei_TSI
	cmn	w0, #1
	csetm	w0, eq
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2093:
	add	x1, x20, 4096
	mov	x0, x20
	add	x1, x1, 195
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	w0, #1
	csetm	w0, eq
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2087:
	mov	w0, -1
	b	.L2081
.L2091:
	ldr	x1, .LC423
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2081
	.size	HEVC_Sei_User_Data_Registered_Itu_T_T35, .-HEVC_Sei_User_Data_Registered_Itu_T_T35
	.align	3
.LC423:
	.xword	.LC422
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecShortTermRefPicSet
	.type	HEVC_DecShortTermRefPicSet, %function
HEVC_DecShortTermRefPicSet:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	w20, w3
	mov	x0, x30
	mov	x27, x1
	mov	x19, x2
	bl	_mcount
	cbnz	w20, .L2141
.L2095:
	ldr	x1, .LC437
	ldr	x0, [x22, 2944]
	bl	HEVC_ue_v
	cmp	w0, 16
	str	w0, [x19]
	bhi	.L2142
	ldr	x1, .LC441
	ldr	x0, [x22, 2944]
	bl	HEVC_ue_v
	cmp	w0, 16
	str	w0, [x19, 4]
	bhi	.L2143
	ldr	w1, [x19]
	add	w2, w0, w1
	str	w2, [x19, 8]
	cmp	w2, 16
	bhi	.L2120
	mov	w20, 0
	cbz	w1, .L2122
	ldr	x25, .LC447
	mov	w21, 0
	mov	w23, 0
	mov	w24, 32767
	b	.L2124
	.p2align 3
.L2123:
	str	w23, [x19, x2, lsl 2]
	add	x20, x19, x20
	ldr	x0, [x22, 2944]
	bl	BsGet
	strb	w0, [x20, 12]
	ldr	w20, [x19]
	cmp	w20, w21
	bls	.L2144
.L2124:
	ldr	x0, [x22, 2944]
	mov	x1, x25
	uxtw	x20, w21
	add	w21, w21, 1
	bl	HEVC_ue_v
	cmp	w0, w24
	mvn	w1, w0
	add	x2, x20, 8
	add	w23, w23, w1
	mov	w1, 1
	bls	.L2123
	ldr	x1, .LC449
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2141:
	ldr	x0, [x22, 2944]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2095
	ldr	w0, [x27, 176]
	cmp	w20, w0
	beq	.L2145
	sub	w20, w20, #1
.L2099:
	ldr	x0, [x22, 2944]
	mov	w1, 1
	bl	BsGet
	mov	w25, w0
	ldr	x1, .LC431
	ldr	x0, [x22, 2944]
	bl	HEVC_ue_v
	uxtw	x1, w20
	mov	w4, 1
	lsl	x2, x1, 2
	sub	w25, w4, w25, lsl 1
	sub	x3, x2, x1
	lsl	x2, x3, 3
	sub	x2, x2, x3
	lsl	x24, x2, 1
	sub	x24, x24, x1
	madd	w25, w0, w25, w25
	add	x28, x27, x24, lsl 2
	ldr	w2, [x28, 2172]
	cmp	w2, 16
	bhi	.L2146
	mov	w21, 0
	mov	w26, 0
	mov	w20, 0
	mov	w23, 0
	b	.L2106
	.p2align 3
.L2101:
	sub	w1, w0, #1
	cmp	w1, 1
	bls	.L2147
.L2102:
	ldr	w0, [x28, 2172]
	add	w21, w21, 1
	cmp	w0, w21
	bcc	.L2148
.L2106:
	ldr	x0, [x22, 2944]
	mov	w1, 1
	bl	BsGet
	cbnz	w0, .L2101
	ldr	x0, [x22, 2944]
	mov	w1, 1
	bl	BsGet
	lsl	w0, w0, 1
	sub	w1, w0, #1
	cmp	w1, 1
	bhi	.L2102
.L2147:
	ldr	w5, [x28, 2172]
	add	x1, x24, x21, uxtw
	uxtw	x2, w23
	cmp	w5, w21
	add	x4, x2, 8
	add	x3, x19, x2
	add	x2, x27, x1, lsl 2
	mov	w1, 0
	bls	.L2103
	ldr	w1, [x2, 2196]
.L2103:
	cmp	w0, 1
	add	w0, w1, w25
	str	w0, [x19, x4, lsl 2]
	cset	w1, eq
	strb	w1, [x3, 12]
	tbnz	w0, #31, .L2149
	add	w26, w26, 1
	add	w23, w23, 1
.L2150:
	ldr	w0, [x28, 2172]
	add	w21, w21, 1
	cmp	w0, w21
	bcs	.L2106
.L2148:
	cmp	w23, 16
	str	w23, [x19, 8]
	ccmp	w20, 16, 2, ls
	ccmp	w26, 16, 2, ls
	stp	w20, w26, [x19]
	bhi	.L2107
	cmp	w23, 1
	bls	.L2113
	sub	w10, w23, #2
	add	x9, x19, 36
	add	x10, x10, 1
	mov	x7, 0
	.p2align 2
.L2112:
	add	x0, x19, x7
	mov	w3, w7
	ldr	w5, [x9]
	ldrb	w8, [x0, 13]
	tbnz	w7, #31, .L2116
	.p2align 2
.L2131:
	sxtw	x1, w3
	add	w0, w3, 1
	add	x4, x19, x1
	add	x1, x19, x1, lsl 2
	sxtw	x0, w0
	add	x6, x0, 8
	add	x0, x19, x0
	ldr	w2, [x1, 32]
	cmp	w5, w2
	bge	.L2114
	str	w2, [x19, x6, lsl 2]
	ldrb	w2, [x4, 12]
	strb	w2, [x0, 12]
	str	w5, [x1, 32]
	strb	w8, [x4, 12]
.L2114:
	subs	w3, w3, #1
	bpl	.L2131
.L2116:
	add	x7, x7, 1
	add	x9, x9, 4
	cmp	x10, x7
	bne	.L2112
.L2113:
	lsr	w7, w20, 1
	sub	w20, w20, #1
	cbz	w7, .L2110
	add	x2, x19, 32
	add	x1, x19, 12
	sub	w7, w20, w7
	.p2align 2
.L2117:
	sxtw	x0, w20
	ldrb	w4, [x1]
	add	x3, x19, x0
	ldr	w5, [x2]
	add	x0, x19, x0, lsl 2
	sub	w20, w20, #1
	cmp	w20, w7
	ldr	w6, [x0, 32]
	str	w6, [x2], 4
	ldrb	w6, [x3, 12]
	strb	w6, [x1], 1
	str	w5, [x0, 32]
	strb	w4, [x3, 12]
	bne	.L2117
.L2110:
	mov	w0, 0
.L2140:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2149:
	add	w20, w20, 1
	add	w23, w23, 1
	b	.L2150
.L2144:
	ldr	w2, [x19, 8]
.L2122:
	cmp	w2, w20
	bls	.L2110
	ldr	x24, .LC451
	mov	w23, 0
	.p2align 2
.L2125:
	ldr	x0, [x22, 2944]
	mov	x1, x24
	uxtw	x21, w20
	add	w20, w20, 1
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x2, x21, 8
	add	w23, w23, w0
	add	x21, x19, x21
	mov	w1, 1
	str	w23, [x19, x2, lsl 2]
	ldr	x0, [x22, 2944]
	bl	BsGet
	strb	w0, [x21, 12]
	ldr	w0, [x19, 8]
	cmp	w0, w20
	bhi	.L2125
	b	.L2110
.L2145:
	ldr	x1, .LC425
	ldr	x0, [x22, 2944]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w20, w2
	bcc	.L2151
	sub	w3, w20, #1
	sub	w20, w3, w0
	cmp	w20, w3
	bls	.L2099
	ldr	x1, .LC429
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2140
.L2107:
	ldr	x1, .LC435
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2140
.L2143:
	ldr	x1, .LC443
	mov	w0, 1
	ldr	w2, [x19]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2140
.L2151:
	ldr	x1, .LC427
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2140
.L2146:
	ldr	x1, .LC433
	mov	w0, w4
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2140
.L2142:
	ldr	x1, .LC439
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2140
.L2120:
	ldr	x1, .LC445
	mov	w3, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2140
	.size	HEVC_DecShortTermRefPicSet, .-HEVC_DecShortTermRefPicSet
	.align	3
.LC425:
	.xword	.LC424
	.align	3
.LC427:
	.xword	.LC426
	.align	3
.LC429:
	.xword	.LC428
	.align	3
.LC431:
	.xword	.LC430
	.align	3
.LC433:
	.xword	.LC432
	.align	3
.LC435:
	.xword	.LC434
	.align	3
.LC437:
	.xword	.LC436
	.align	3
.LC439:
	.xword	.LC438
	.align	3
.LC441:
	.xword	.LC440
	.align	3
.LC443:
	.xword	.LC442
	.align	3
.LC445:
	.xword	.LC444
	.align	3
.LC447:
	.xword	.LC446
	.align	3
.LC449:
	.xword	.LC448
	.align	3
.LC451:
	.xword	.LC450
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecHrdParam
	.type	HEVC_DecHrdParam, %function
HEVC_DecHrdParam:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	uxtb	w19, w2
	mov	w23, w3
	bl	_mcount
	cmp	x20, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2175
	cbnz	w19, .L2199
.L2155:
	ldr	x27, .LC455
	mov	w19, 0
	ldr	x25, .LC453
	ldr	x26, .LC457
	ldr	x28, .LC459
	.p2align 2
.L2171:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	uxtw	x21, w19
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2200
	add	x0, x22, x21, lsl 2
	str	wzr, [x0, 24]
.L2174:
	ldr	x0, [x20, 2944]
	mov	x1, x25
	bl	HEVC_ue_v
.L2161:
	ldr	x0, [x20, 2944]
	mov	x1, x27
	bl	HEVC_ue_v
	add	x1, x22, x21, lsl 2
	str	w0, [x1, 24]
.L2162:
	cmp	w0, 31
	bhi	.L2201
	mov	w24, 0
.L2164:
	cbz	w24, .L2202
	cmp	w24, 1
	beq	.L2197
.L2170:
	add	w24, w24, 1
	cmp	w24, 2
	bne	.L2164
.L2169:
	add	w19, w19, 1
	cmp	w23, w19
	bcs	.L2171
	mov	w0, 0
.L2196:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2201:
	mov	w2, w0
	mov	x1, x26
	mov	w0, 1
	mov	w24, 0
	bl	dprint_vfmw
	add	x0, x22, x21, lsl 2
	str	wzr, [x0, 24]
	b	.L2164
	.p2align 3
.L2200:
	add	x24, x22, x21, lsl 2
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	str	wzr, [x24, 24]
	uxtb	w0, w0
	cbnz	w0, .L2174
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2161
	ldr	w0, [x24, 24]
	b	.L2162
	.p2align 3
.L2199:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x22]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x22, 1]
	ldrh	w0, [x22]
	cbz	w0, .L2155
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x22, 2]
	cbnz	w0, .L2203
.L2157:
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	ldrb	w0, [x22, 2]
	cbnz	w0, .L2204
.L2158:
	ldr	x0, [x20, 2944]
	mov	w1, 5
	bl	BsGet
	str	w0, [x22, 12]
	mov	w1, 5
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x22, 16]
	mov	w1, 5
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x22, 20]
	b	.L2155
.L2175:
	mov	w0, -1
	b	.L2196
.L2204:
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	b	.L2158
.L2203:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 5
	bl	BsGet
	str	w0, [x22, 4]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x22, 3]
	mov	w1, 5
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x22, 8]
	b	.L2157
.L2202:
	ldrb	w0, [x22]
	cbnz	w0, .L2177
	mov	w24, 1
.L2197:
	ldrb	w0, [x22, 1]
	cbz	w0, .L2169
.L2177:
	add	x0, x21, 4
	str	wzr, [x29, 108]
	lsl	x0, x0, 2
	str	x0, [x29, 96]
	b	.L2173
.L2172:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x29, 96]
	ldr	w1, [x29, 108]
	add	x0, x22, x0
	ldr	w0, [x0, 8]
	cmp	w0, w1
	bcc	.L2170
.L2173:
	ldr	w2, [x29, 108]
	mov	x1, x28
	ldr	x0, [x20, 2944]
	add	w2, w2, 1
	str	w2, [x29, 108]
	bl	HEVC_ue_v
	ldr	x1, .LC461
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldrb	w0, [x22, 2]
	cbz	w0, .L2172
	ldr	x1, .LC463
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC465
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	b	.L2172
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	3
.LC453:
	.xword	.LC452
	.align	3
.LC455:
	.xword	.LC454
	.align	3
.LC457:
	.xword	.LC456
	.align	3
.LC459:
	.xword	.LC458
	.align	3
.LC461:
	.xword	.LC460
	.align	3
.LC463:
	.xword	.LC462
	.align	3
.LC465:
	.xword	.LC464
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	HEVC_ParseVPSExtension, %function
HEVC_ParseVPSExtension:
	sub	sp, sp, #672
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x28, x19, 12288
	add	x4, x29, 312
	add	x0, x29, 200
	add	x21, x28, 132
	mov	x2, 12492
	mov	w1, 0
	str	xzr, [x29, 184]
	stp	xzr, xzr, [x4]
	add	x4, x29, 328
	stp	xzr, xzr, [x0]
	ldr	x0, .LC466
	stp	xzr, xzr, [x4]
	add	x4, x29, 344
	ldr	x3, [x0, 96]
	mov	x0, x21
	stp	xzr, xzr, [x29, 168]
	stp	xzr, xzr, [x4]
	add	x4, x29, 360
	stp	xzr, xzr, [x4]
	add	x4, x29, 640
	stp	xzr, xzr, [x4]
	add	x4, x29, 656
	stp	xzr, xzr, [x4]
	add	x4, x29, 672
	stp	xzr, xzr, [x4]
	add	x4, x29, 688
	stp	xzr, xzr, [x4]
	add	x4, x29, 704
	stp	xzr, xzr, [x4]
	add	x4, x29, 720
	stp	xzr, xzr, [x4]
	add	x4, x29, 736
	stp	xzr, xzr, [x4]
	add	x4, x29, 752
	stp	xzr, xzr, [x4]
	add	x4, x29, 376
	stp	xzr, xzr, [x4]
	add	x4, x29, 392
	stp	xzr, xzr, [x4]
	add	x4, x29, 408
	stp	xzr, xzr, [x4]
	add	x4, x29, 424
	stp	xzr, xzr, [x4]
	add	x4, x29, 440
	stp	xzr, xzr, [x4]
	add	x4, x29, 456
	stp	xzr, xzr, [x4]
	add	x4, x29, 472
	stp	xzr, xzr, [x4]
	add	x4, x29, 488
	stp	xzr, xzr, [x4]
	add	x4, x29, 504
	stp	xzr, xzr, [x4]
	add	x4, x29, 520
	stp	xzr, xzr, [x4]
	add	x4, x29, 536
	stp	xzr, xzr, [x4]
	add	x4, x29, 552
	stp	xzr, xzr, [x4]
	blr	x3
	ldr	w0, [x19, 8]
	mov	w3, 62
	cmp	w0, w3
	csel	w3, w0, w3, le
	str	w3, [x28, 4248]
	cmp	w3, 1
	bgt	.L2712
	cmp	w3, wzr
	ble	.L2208
	ldrb	w0, [x19, 3]
	cbnz	w0, .L2713
.L2208:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	mov	x21, 0
	mov	w27, 0
	add	x22, x29, 312
	bl	BsGet
	uxtb	w0, w0
	str	w0, [x29, 152]
.L2209:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cmp	w0, wzr
	str	w0, [x22, x21]
	add	x21, x21, 4
	csinc	w27, w27, w27, eq
	cmp	x21, 64
	bne	.L2209
	ldr	w0, [x29, 152]
	mov	x21, 0
	add	x25, x29, 504
	cmp	w0, wzr
	cset	w23, ne
	sub	w24, w27, w23
	cmp	w24, wzr
	ble	.L2214
.L2213:
	ldr	x0, [x20, 2944]
	mov	w1, 3
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x25, x21, lsl 2]
	add	x21, x21, 1
	cmp	w24, w21
	bgt	.L2213
.L2214:
	mov	w3, 0
	mov	w6, 6
	tbnz	w27, #31, .L2212
.L2590:
	cmp	w27, w3
	cset	w0, eq
	tst	w23, w0
	bne	.L2217
	cmp	w3, #1
	bmi	.L2219
	sxtw	x4, w3
	add	x1, x29, 768
	mov	w0, 0
	add	x1, x1, x4, lsl 2
	sub	x1, x1, #4096
	ldr	w2, [x1, 3704]
.L2220:
	add	x1, x29, 768
	add	x1, x1, x0, sxtw 2
	add	w0, w0, 1
	sub	x1, x1, #4096
	cmp	w0, w3
	ldr	w1, [x1, 3832]
	add	w1, w1, 1
	add	w2, w2, w1
	bne	.L2220
	add	x0, x29, 768
	add	x0, x0, x4, lsl 2
	sub	x0, x0, #4096
	str	w2, [x0, 3704]
.L2219:
	add	w3, w3, 1
	cmp	w27, w3
	bge	.L2590
.L2212:
	ldr	w0, [x29, 152]
	cbz	w0, .L2216
	sub	w0, w27, #1
	add	x2, x29, 768
	mov	w1, 5
	add	x0, x2, x0, sxtw 2
	sub	x0, x0, #4096
	ldr	w2, [x0, 3704]
	sub	w1, w1, w2
	str	w1, [x0, 3832]
.L2216:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	add	x26, x28, 132
	mov	w24, 1
	bl	BsGet
	uxtb	w0, w0
	ldr	w1, [x26, 4116]
	str	w0, [x29, 128]
	cmp	w1, wzr
	ble	.L2231
	str	x19, [x29, 112]
	mov	x21, x26
	mov	w23, w24
	mov	w19, w27
.L2589:
	ldr	w0, [x29, 128]
	cbnz	w0, .L2714
	sxtw	x4, w24
	mov	w0, w24
	add	x1, x21, x4, lsl 2
	str	w24, [x1, 4136]
.L2227:
	add	x1, x21, x0, sxtw 2
	cmp	w19, wzr
	str	w24, [x1, 4144]
	ldr	w1, [x29, 152]
	cbz	w1, .L2228
	ble	.L2232
	add	x1, x29, 640
	ldr	w6, [x29, 376]
	add	x4, x1, x4, lsl 6
	mov	w2, 0
.L2234:
	add	w2, w2, 1
	add	x1, x29, 768
	cmp	w19, w2
	add	x3, x1, x2, sxtw 2
	sub	x3, x3, #4096
	ldr	w3, [x3, 3704]
	lsl	w1, w23, w3
	sub	w1, w1, #1
	and	w1, w1, w0
	asr	w1, w1, w6
	str	w1, [x4], 4
	mov	w6, w3
	bne	.L2234
.L2232:
	ldr	w0, [x21, 4116]
	add	w24, w24, 1
	cmp	w0, w24
	bge	.L2589
.L2722:
	ldr	x19, [x29, 112]
.L2231:
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	ldr	w6, [x28, 4248]
	add	x7, x28, 132
	mov	w23, w0
	tbnz	w6, #31, .L2715
	ldr	w8, [x29, 312]
	mov	w21, 1
	mov	w5, 0
	add	x9, x19, 16384
.L2241:
	sxtw	x4, w5
	mov	w3, w8
	mov	x0, 0
	mov	w2, 0
	add	x1, x7, x4, lsl 2
	lsl	x4, x4, 4
	ldrsw	x10, [x1, 4136]
	add	x1, x29, 768
	add	x1, x1, x10, lsl 2
	sub	x1, x1, #4096
	str	w8, [x1, 3496]
	b	.L2237
	.p2align 3
.L2716:
	ldr	w3, [x22, x0]
.L2237:
	add	x1, x4, x2, sxtw
	cbz	w3, .L2235
	add	x3, x29, 768
	add	w2, w2, 1
	add	x1, x3, x1, lsl 2
	add	x3, x29, 440
	ldr	w1, [x1, -128]
	str	w1, [x3, x0]
.L2235:
	add	x0, x0, 4
	cmp	x0, 64
	bne	.L2716
	add	x0, x29, 768
	ldr	w4, [x29, 444]
	add	x0, x0, x10, lsl 2
	cmp	w5, wzr
	sub	x0, x0, #4096
	str	w4, [x0, 3496]
	ble	.L2238
	sub	w3, w5, #1
	add	x1, x9, 172
	add	x3, x3, 4096
	mov	w2, 1
	add	x3, x3, 44
	add	x3, x19, x3, lsl 2
	.p2align 2
.L2240:
	ldrsw	x0, [x1], 4
	add	x10, x29, 768
	add	x0, x10, x0, lsl 2
	sub	x0, x0, #4096
	ldr	w0, [x0, 3496]
	cmp	w4, w0
	csel	w2, w2, wzr, ne
	cmp	x3, x1
	bne	.L2240
	cmp	w2, wzr
	csinc	w21, w21, w21, eq
.L2238:
	add	w5, w5, 1
	cmp	w5, w6
	ble	.L2241
	cmp	w23, wzr
	ble	.L2242
	cmp	w21, wzr
	ble	.L2242
.L2243:
	add	x22, x19, 16384
	mov	w24, 0
	add	x22, x22, 164
.L2247:
	ldr	x0, [x20, 2944]
	mov	w1, w23
	add	w24, w24, 1
	bl	BsGet
	str	w0, [x22], 4
	cmp	w21, w24
	bgt	.L2247
	ldr	w6, [x28, 4248]
.L2242:
	add	x0, x19, 16384
	cmp	w6, wzr
	str	x0, [x29, 152]
	mov	w25, 1
	add	x23, x28, 132
	ble	.L2252
	str	x28, [x29, 128]
.L2588:
	sxtw	x0, w25
	cmp	w25, wzr
	add	x1, x23, x0, lsl 2
	ldr	w22, [x1, 4136]
	ble	.L2493
	lsl	x0, x0, 1
	sub	w1, w25, #1
	add	x0, x0, 12288
	sxtw	x22, w22
	add	x24, x0, 138
	add	x0, x0, 137
	add	x21, x19, x0
	ldr	x0, [x29, 152]
	add	x24, x24, x1
	mov	w28, 0
	add	x24, x19, x24
	lsl	x26, x22, 1
	add	x27, x0, 172
	.p2align 2
.L2250:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	add	x21, x21, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x21, -1]
	add	x1, x26, x28, sxtw
	add	x1, x1, 1044
	cmp	x21, x24
	cbz	w0, .L2249
	ldr	w0, [x27]
	add	w28, w28, 1
	str	w0, [x23, x1, lsl 2]
.L2249:
	add	x27, x27, 4
	bne	.L2250
	add	x22, x22, 1040
	add	w25, w25, 1
	str	w28, [x23, x22, lsl 2]
	ldr	w0, [x23, 4116]
	cmp	w0, w25
	bge	.L2588
.L2732:
	ldr	x28, [x29, 128]
.L2252:
	ldr	x0, .LC466
	mov	x2, 16
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 200
	blr	x3
	ldr	w7, [x28, 4248]
	add	x10, x28, 132
	mov	w11, 0
	tbnz	w7, #31, .L2497
	mov	x13, 16596
	mov	x12, 4150
	mov	w9, 1
.L2587:
	add	x0, x10, x11, sxtw 2
	ldr	w0, [x0, 4136]
	sxtw	x14, w0
	add	x1, x14, 1040
	ldr	w1, [x10, x1, lsl 2]
	cmp	w1, wzr
	ble	.L2261
	add	x8, x12, x0, sxtw 1
	sub	w1, w1, #1
	add	x8, x8, x1
	add	x1, x29, 768
	add	x3, x1, x14, lsl 3
	add	x0, x13, x0, sxtw 3
	add	x2, x19, x0
	add	x8, x19, x8, lsl 2
	lsl	x14, x14, 1
	sub	x3, x3, #4096
	.p2align 2
.L2260:
	ldrsw	x0, [x2]
	add	x15, x29, 768
	add	x4, x29, 768
	mov	w6, 1
	add	x1, x14, x0
	mov	w5, w6
	add	x4, x4, x0, lsl 3
	add	x2, x2, 4
	add	x1, x15, x1, lsl 2
	sub	x4, x4, #4096
	sub	x1, x1, #4096
	mov	x0, x4
	str	w9, [x1, 3528]
	ldr	w1, [x3, 3528]
	cbnz	w1, .L2258
	ldr	w1, [x4, 3528]
	cmp	w1, wzr
	cset	w6, ne
.L2258:
	ldr	w1, [x3, 3532]
	str	w6, [x3, 3528]
	cbnz	w1, .L2259
	ldr	w0, [x0, 3532]
	cmp	w0, wzr
	cset	w5, ne
.L2259:
	cmp	x2, x8
	str	w5, [x3, 3532]
	bne	.L2260
.L2261:
	add	w11, w11, 1
	cmp	w11, w7
	ble	.L2587
	cmp	w7, wzr
	ble	.L2267
	sub	w4, w7, #1
	add	x5, x19, 16384
	add	x4, x4, 4096
	add	x5, x5, 172
	add	x4, x4, 44
	add	x4, x19, x4, lsl 2
.L2265:
	ldr	w3, [x5]
	mov	w2, 0
	add	w1, w3, 1
	cmp	w1, 1
	sxtw	x3, w3
	bgt	.L2262
	.p2align 2
.L2264:
	add	x0, x3, x1, sxtw 1
	add	x6, x29, 768
	add	w1, w1, 1
	add	x0, x6, x0, lsl 2
	sub	x0, x0, #4096
	ldr	w0, [x0, 3528]
	cmp	w0, wzr
	csinc	w2, w2, w2, eq
	cmp	w1, 2
	bne	.L2264
.L2262:
	add	x0, x29, 768
	add	x5, x5, 4
	add	x0, x0, x3, lsl 2
	cmp	x5, x4
	sub	x0, x0, #4096
	str	w2, [x0, 3504]
	bne	.L2265
.L2267:
	mov	w21, 0
	mov	w1, 0
	add	x3, x28, 132
	mov	w4, 1
.L2266:
	add	x0, x3, x1, sxtw 2
	add	x2, x29, 768
	add	x6, x29, 768
	add	x2, x2, x21, sxtw 2
	sub	x2, x2, #4096
	ldrsw	x0, [x0, 4136]
	add	x5, x0, 1040
	add	x0, x6, x0, lsl 2
	sub	x0, x0, #4096
	ldr	w5, [x3, x5, lsl 2]
	cbnz	w5, .L2269
	ldr	w0, [x0, 3504]
	str	w4, [x2, 3512]
	cmp	w0, wzr
	add	w0, w0, 1
	ble	.L2271
	str	w0, [x2, 3512]
.L2271:
	add	w21, w21, 1
.L2269:
	add	w1, w1, 1
	cmp	w1, w7
	ble	.L2266
	cmp	w21, 1
	ble	.L2497
	ldr	x1, .LC471
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 1023
	mov	w22, w0
	bgt	.L2717
	cmp	w0, wzr
	mov	w24, 1
	mov	w23, 0
	ble	.L2268
.L2586:
	cmp	w21, 1
	add	x26, x29, 188
	mov	w25, 1
	ble	.L2279
	.p2align 2
.L2276:
	ldr	w3, [x26]
	mov	w1, 0
	ldr	x0, [x20, 2944]
	add	w3, w3, 1
	cmp	w3, 1
	bls	.L2274
	.p2align 2
.L2275:
	add	w1, w1, 1
	lsl	w2, w24, w1
	cmp	w3, w2
	bhi	.L2275
.L2274:
	add	w25, w25, 1
	bl	BsGet
	cmp	w21, w25
	add	x26, x26, 4
	bne	.L2276
.L2279:
	add	w23, w23, 1
	cmp	w22, w23
	bne	.L2586
.L2268:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2280
	add	x0, x28, 132
	ldr	w2, [x0, 4116]
	tbnz	w2, #31, .L2284
	ldr	w3, [x19, 12]
	mov	w1, 0
.L2286:
	add	x4, x0, x1, sxtw 2
	add	w1, w1, 1
	cmp	w1, w2
	str	w3, [x4, 4168]
	ble	.L2286
.L2284:
	ldr	w8, [x19, 20]
	mov	w7, 0
	add	x3, x28, 132
	tbnz	w8, #31, .L2283
.L2584:
	sxtw	x6, w7
	mov	w2, 0
	lsl	x5, x6, 1
	mov	w0, 0
	add	x6, x19, x6, lsl 2
	ldr	w4, [x6, 8324]
	cbz	w4, .L2290
	.p2align 2
.L2585:
	add	x1, x5, x0, sxtw
	add	w0, w0, 1
	add	x1, x19, x1, lsl 2
	ldrsw	x1, [x1, 132]
	add	x1, x1, 1036
	ldrsw	x1, [x3, x1, lsl 2]
	add	x1, x3, x1, lsl 2
	ldr	w1, [x1, 4168]
	cmp	w2, w1
	csel	w2, w2, w1, ge
	cmp	w0, w4
	bne	.L2585
.L2290:
	add	x6, x6, 20480
	add	w7, w7, 1
	cmp	w7, w8
	str	w2, [x6, 232]
	ble	.L2584
.L2283:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2291
	add	x3, x28, 132
	ldr	w4, [x3, 4116]
	mov	w5, 7
	cmp	w0, w4
	bge	.L2305
.L2304:
	add	w6, w0, 1
	sxtw	x2, w0
	cmp	w6, w4
	mov	w0, w6
	lsl	x2, x2, 1
	bgt	.L2303
.L2583:
	add	x1, x2, x0, sxtw
	add	w0, w0, 1
	cmp	w0, w4
	add	x1, x3, x1, lsl 2
	str	w5, [x1, 12392]
	ble	.L2583
.L2303:
	mov	w0, w6
	cmp	w0, w4
	blt	.L2304
.L2305:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	mov	w21, 2
	bl	BsGet
	strb	w0, [x28, 134]
	ldr	x1, .LC475
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	mov	w1, w0
	ldrb	w0, [x19, 3]
	str	w1, [x29, 144]
	cmp	w0, wzr
	csinc	w21, w21, wzr, ne
	cmp	w1, w21
	blt	.L2310
.L2582:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	add	w21, w21, w1
	bl	BsGet
	uxtb	w2, w0
	ldr	w3, [x19, 12]
	add	x1, x29, 192
	mov	x0, x20
	bl	HEVC_DecPTL
	ldr	w0, [x29, 144]
	cmp	w0, w21
	bge	.L2582
.L2310:
	ldr	w7, [x19, 20]
	add	x21, x28, 132
	add	w7, w22, w7
	add	w7, w7, 1
	str	w7, [x21, 4112]
	cmp	w7, 1
	ble	.L2718
	ldr	x1, .LC477
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	mov	w22, w0
	ldr	x0, [x20, 2944]
	mov	w1, 2
	bl	BsGet
	str	w0, [x29, 104]
	ldr	w7, [x21, 4112]
	add	w4, w22, w7
	str	w4, [x21, 4120]
	cmp	w4, 1025
	bgt	.L2488
	mov	w0, -1
	cmp	w4, 1
	str	w0, [x21, 4192]
	ble	.L2312
	mov	w0, 1
	str	w0, [x29, 152]
	ldr	w1, [x29, 104]
	mov	w26, w0
	mov	w25, w0
	ldr	w0, [x29, 152]
	cmp	w1, 2
	str	wzr, [x29, 128]
	cset	w1, eq
	cmp	w7, w0
	str	w1, [x29, 100]
	ccmp	w7, 2, 4, le
	mov	x23, -12429
	mov	x27, x28
	sub	x23, x23, x19
	ble	.L2313
.L2721:
	sub	w7, w7, #1
	mov	w1, 0
	cmp	w7, 1
	ldr	x0, [x20, 2944]
	bls	.L2314
.L2315:
	add	w1, w1, 1
	lsl	w2, w26, w1
	cmp	w7, w2
	bhi	.L2315
.L2314:
	ldrsw	x28, [x29, 152]
	bl	BsGet
	add	x1, x27, 132
	add	x2, x28, 1048
	str	w0, [x1, x2, lsl 2]
	ldr	w7, [x27, 4244]
.L2316:
	ldr	w0, [x29, 152]
	cmp	w7, w0
	mov	w21, w0
	bgt	.L2317
	add	x0, x27, x28, lsl 2
	ldr	w21, [x0, 4324]
	add	w21, w21, 1
.L2317:
	ldr	w0, [x19, 20]
	ldr	w1, [x29, 152]
	cmp	w0, w1
	ldr	w1, [x29, 100]
	cset	w0, lt
	orr	w0, w1, w0
	cbnz	w0, .L2318
	sxtw	x0, w21
	mov	w2, 0
	mov	x1, x0
	str	x1, [x29, 112]
	mov	w0, 0
	add	x3, x19, x1, lsl 2
	ldr	w16, [x3, 8324]
	cbz	w16, .L2320
	add	x1, x27, 132
	sub	w5, w16, #1
	add	x1, x1, x28, lsl 1
	ldr	w4, [x29, 104]
	b	.L2581
.L2719:
	cmp	w4, 2
	add	x2, x1, x0, sxtw
	beq	.L2324
	cbnz	w4, .L2322
	strb	w25, [x2, 9]
.L2322:
	add	w0, w0, 1
	cmp	w0, w16
	mov	w2, w0
	bcs	.L2491
.L2581:
	cmp	w4, 1
	bne	.L2719
	add	x6, x1, x0, sxtw
	cmp	w5, w2
	add	w0, w0, 1
	cset	w7, eq
	cmp	w0, w16
	mov	w2, w0
	strb	w7, [x6, 9]
	bcc	.L2581
.L2491:
	ldr	w16, [x3, 8324]
.L2320:
	ldr	w0, [x27, 4252]
	cbz	w0, .L2334
	sub	w0, w0, #1
	mov	x18, 12431
	add	x15, x19, 16384
	add	x14, x27, 141
	add	x18, x18, x0, uxtw 1
	add	x15, x15, 228
	add	x18, x19, x18
	mov	x17, x19
	mov	x22, 132
	.p2align 2
.L2333:
	ldr	w0, [x15]
	add	w0, w0, 1
	add	x1, x19, x0, uxtw 2
	ldr	w9, [x1, 8324]
	cbz	w9, .L2337
	add	x11, x23, x14
	add	x0, x22, x0, uxtw 3
	add	x11, x11, 12288
	add	x10, x19, x0
	mov	x8, x17
	mov	x6, x14
	mov	w7, 0
	add	x11, x11, 2192
	.p2align 2
.L2336:
	ldrb	w0, [x6]
	strb	wzr, [x6, 2050]
	cbz	w0, .L2338
	strb	w25, [x6, 2050]
	ldr	w0, [x8, 132]
	cbz	w7, .L2338
	add	x3, x27, 132
	sub	w4, w7, #1
	add	x0, x3, x0, uxtw 2
	add	x4, x11, x4
	add	x1, x14, 2050
	add	x4, x19, x4
	mov	x2, x10
	ldrsw	x5, [x0, 4144]
	add	x5, x3, x5, lsl 1
	.p2align 2
.L2340:
	ldr	w0, [x2]
	add	x2, x2, 4
	add	x0, x0, 1036
	ldrsw	x0, [x3, x0, lsl 2]
	add	x0, x5, x0
	ldrb	w0, [x0, 5]
	cbz	w0, .L2339
	strb	w25, [x1]
.L2339:
	add	x1, x1, 1
	cmp	x1, x4
	bne	.L2340
.L2338:
	add	w7, w7, 1
	add	x6, x6, 1
	cmp	w9, w7
	add	x8, x8, 4
	bne	.L2336
.L2337:
	add	x14, x14, 2
	add	x15, x15, 4
	cmp	x14, x18
	add	x17, x17, 8
	bne	.L2333
.L2334:
	mov	w3, 0
	mov	w1, 0
	cbz	w16, .L2331
	ldr	x0, [x29, 112]
	add	x4, x27, 132
	ldr	w6, [x29, 128]
	add	x4, x4, x28, lsl 1
	lsl	x5, x0, 1
	.p2align 2
.L2580:
	sxtw	x0, w1
	add	w1, w1, 1
	add	x2, x5, x0
	add	x0, x4, x0
	cmp	w1, w16
	add	x2, x19, x2, lsl 2
	ldrb	w0, [x0, 9]
	cbz	w0, .L2341
	ldr	w6, [x2, 132]
	add	w3, w3, 1
.L2341:
	bne	.L2580
	ldr	x1, [x29, 112]
	add	x0, x27, 132
	add	x28, x0, x28, lsl 1
	ldr	w0, [x29, 144]
	add	x21, x1, 2080
	mov	w24, 0
	lsl	x21, x21, 2
	add	w22, w0, 1
	mov	x0, x21
	str	w3, [x29, 112]
	mov	x21, x19
	str	w6, [x29, 128]
	mov	x19, x0
	.p2align 2
.L2346:
	add	x0, x28, x24, sxtw
	ldrb	w0, [x0, 2059]
	cbz	w0, .L2343
	ldr	w0, [x21, 20]
	cmp	w0, wzr
	ble	.L2343
	cmp	w22, 1
	mov	w1, 0
	ldr	x0, [x20, 2944]
	bls	.L2344
	.p2align 2
.L2345:
	add	w1, w1, 1
	lsl	w2, w26, w1
	cmp	w22, w2
	bhi	.L2345
.L2344:
	bl	BsGet
.L2343:
	add	x0, x21, x19
	add	w24, w24, 1
	ldr	w0, [x0, 4]
	cmp	w0, w24
	bhi	.L2346
	ldr	w3, [x29, 112]
	mov	x19, x21
	cmp	w3, 1
	beq	.L2720
.L2331:
	add	x21, x27, 132
	ldr	w1, [x29, 152]
	ldr	w0, [x21, 4120]
	add	w1, w1, 1
	str	w1, [x29, 152]
	cmp	w0, w1
	ble	.L2347
.L2723:
	ldr	w7, [x21, 4112]
	ldr	w0, [x29, 152]
	cmp	w7, w0
	ccmp	w7, 2, 4, le
	bgt	.L2721
.L2313:
	ldrsw	x28, [x29, 152]
	add	x0, x27, x28, lsl 2
	str	wzr, [x0, 4324]
	b	.L2316
.L2228:
	ble	.L2232
	add	x0, x29, 640
	mov	x25, 0
	add	x26, x0, x4, lsl 6
	add	x27, x29, 504
.L2233:
	ldr	w1, [x27, x25, lsl 2]
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x26, x25, lsl 2]
	add	x25, x25, 1
	cmp	w19, w25
	bgt	.L2233
	ldr	w0, [x21, 4116]
	add	w24, w24, 1
	cmp	w0, w24
	bge	.L2589
	b	.L2722
.L2217:
	add	x0, x29, 768
	add	x0, x0, x3, sxtw 2
	sub	x0, x0, #4096
	str	w6, [x0, 3704]
	b	.L2219
.L2714:
	ldr	x0, [x20, 2944]
	mov	w1, 6
	bl	BsGet
	sxtw	x4, w24
	add	x1, x21, x4, lsl 2
	str	w0, [x1, 4136]
	b	.L2227
.L2318:
	sxtw	x0, w21
	str	x0, [x29, 112]
	add	x24, x19, x0, lsl 2
	ldr	w16, [x24, 8324]
	cbz	w16, .L2320
	add	x22, x27, 132
	mov	w21, 0
	add	x22, x22, x28, lsl 1
	.p2align 2
.L2321:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	add	x1, x22, x21, sxtw
	add	w21, w21, 1
	strb	w0, [x1, 9]
	ldr	w16, [x24, 8324]
	cmp	w16, w21
	bhi	.L2321
	b	.L2320
.L2720:
	ldr	x0, [x29, 128]
	add	x0, x27, x0, sxtw 2
	ldr	w0, [x0, 4292]
	cmp	w0, wzr
	ble	.L2331
	ldr	x0, [x20, 2944]
	mov	w1, w3
	add	x21, x27, 132
	bl	BsGet
	ldr	w1, [x29, 152]
	ldr	w0, [x21, 4120]
	add	w1, w1, 1
	str	w1, [x29, 152]
	cmp	w0, w1
	bgt	.L2723
.L2347:
	ldr	x1, .LC481
	mov	x28, x27
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 255
	str	w0, [x21, 4124]
	bhi	.L2486
.L2349:
	ldr	x27, .LC485
	mov	w22, 0
	ldr	x26, .LC487
	ldr	x25, .LC489
	ldr	x24, .LC491
	b	.L2363
.L2350:
	add	x23, x19, 24576
	add	x21, x29, 216
	add	x23, x23, 252
.L2352:
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	str	w0, [x21, 4]
	mov	w1, 16
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x21, 8]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2724
	cbz	x23, .L2357
	ldr	w0, [x23, 12]
	str	w0, [x21, 12]
	ldrb	w0, [x23]
	strb	w0, [x21]
	ldr	w0, [x23, 16]
	str	w0, [x21, 16]
	ldr	w0, [x23, 20]
	str	w0, [x21, 20]
.L2357:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2725
	stp	wzr, wzr, [x21, 24]
	stp	wzr, wzr, [x21, 32]
.L2359:
	ldp	w2, w3, [x21, 16]
	cmp	w2, 8
	bhi	.L2361
	cmp	w3, 8
	bls	.L2362
.L2361:
	ldr	x1, .LC493
	mov	w0, 1
	bl	dprint_vfmw
	stp	wzr, wzr, [x21, 16]
.L2362:
	ldr	w0, [x28, 4256]
	add	w22, w22, 1
	cmp	w0, w22
	bcc	.L2726
.L2363:
	cmp	w22, 1
	bgt	.L2350
	mov	x23, 0
	cbz	w22, .L2351
	sub	w0, w22, #1
	sxtw	x0, w0
	lsl	x23, x0, 5
	add	x23, x23, x0, lsl 3
	add	x23, x23, 24576
	add	x23, x19, x23
	add	x23, x23, 252
.L2351:
	sxtw	x0, w22
	lsl	x21, x0, 5
	add	x21, x21, x0, lsl 3
	add	x21, x21, 24576
	add	x21, x19, x21
	add	x21, x21, 252
	b	.L2352
.L2725:
	ldr	x0, [x20, 2944]
	mov	x1, x27
	bl	HEVC_ue_v
	str	w0, [x21, 24]
	mov	x1, x26
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x21, 28]
	mov	x1, x25
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x21, 32]
	mov	x1, x24
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x21, 36]
	b	.L2359
.L2724:
	ldr	x0, [x20, 2944]
	mov	w1, 2
	bl	BsGet
	cmp	w0, 3
	str	w0, [x21, 12]
	beq	.L2727
	cbz	x23, .L2356
	ldrb	w0, [x23]
	strb	w0, [x21]
.L2355:
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	str	w0, [x21, 16]
	mov	w1, 4
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x21, 20]
	b	.L2357
.L2726:
	cbnz	w0, .L2728
	ldrb	w1, [x19, 3]
	mov	w0, 0
	cbz	w1, .L2367
.L2487:
	add	x2, x19, 16384
	mov	w3, 0
	add	x2, x2, 188
.L2366:
	add	w3, w3, 1
	str	wzr, [x2], 4
	cmp	w3, w1
	blt	.L2366
.L2365:
	cbz	w0, .L2367
	cmp	w1, wzr
	ldr	w0, [x28, 4248]
	cset	w22, ne
	mov	w21, 1
	cmp	w22, w0
	bgt	.L2374
.L2579:
	ldr	w3, [x28, 4256]
	mov	w1, 0
	ldr	x0, [x20, 2944]
	add	w3, w3, 1
	cmp	w3, 1
	bls	.L2371
.L2372:
	add	w1, w1, 1
	lsl	w2, w21, w1
	cmp	w3, w2
	bhi	.L2372
.L2371:
	bl	BsGet
	add	x1, x28, 132
	add	x2, x1, x22, sxtw 2
	add	w22, w22, 1
	str	w0, [x2, 4152]
	ldr	w0, [x28, 4248]
	cmp	w0, w22
	bge	.L2579
.L2374:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	mov	w23, w1
	add	x21, x28, 132
	mov	x22, x21
	bl	BsGet
	strb	w0, [x28, 133]
	mov	w1, w23
	ldr	x0, [x20, 2944]
	bl	BsGet
	ldr	w0, [x28, 4248]
	cmp	w0, wzr
	bgt	.L2578
	b	.L2370
	.p2align 3
.L2378:
	ldr	w0, [x22, 4116]
	cmp	w0, w23
	blt	.L2370
.L2578:
	sxtw	x21, w23
	add	w23, w23, 1
	add	x0, x22, x21, lsl 2
	ldrsw	x0, [x0, 4136]
	add	x0, x0, 1040
	ldr	w0, [x22, x0, lsl 2]
	cbnz	w0, .L2378
	add	x21, x22, x21
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x21, 3]
	ldr	w0, [x22, 4116]
	cmp	w0, w23
	bge	.L2578
.L2370:
	ldr	w0, [x28, 4252]
	mov	w1, 1
	str	w1, [x29, 112]
	cmp	w0, w1
	bls	.L2377
	ldr	x23, .LC501
	str	x28, [x29, 144]
	mov	x28, x19
.L2576:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x1, [x29, 144]
	ldr	w3, [x29, 112]
	add	x1, x1, 132
	ldr	w2, [x1, 4112]
	mov	w25, w3
	cmp	w2, w3
	bhi	.L2382
	add	x1, x1, x3, uxtw 2
	ldr	w25, [x1, 4192]
	add	w25, w25, 1
.L2382:
	cmp	w0, wzr
	ldr	x0, [x29, 144]
	uxtw	x1, w25
	mov	w21, 0
	add	x26, x0, 132
	cset	w0, ne
	str	w0, [x29, 152]
	add	x27, x1, 2072
	ldr	x0, [x29, 112]
	lsl	x27, x27, 2
	str	x1, [x29, 128]
	add	x19, x26, x0, uxtw 1
	.p2align 2
.L2391:
	cmp	w21, wzr
	ldr	w1, [x29, 152]
	cset	w0, ne
	tst	w1, w0
	bne	.L2729
	cmp	w21, wzr
	cset	w0, eq
.L2384:
	cbz	w0, .L2385
	ldr	x0, [x29, 128]
	mov	w25, 0
	lsl	x22, x0, 1
	add	x24, x28, x0, lsl 2
	ldr	w3, [x24, 8324]
	cbz	w3, .L2390
	.p2align 2
.L2577:
	uxtw	x0, w25
	add	w25, w25, 1
	add	x1, x19, x0
	ldrb	w1, [x1, 2059]
	cbz	w1, .L2387
	ldrb	w6, [x28, 3]
	add	x0, x22, x0
	mov	x1, x23
	add	x0, x28, x0, lsl 2
	cbnz	w6, .L2388
	ldr	w0, [x0, 132]
	cbz	w0, .L2387
.L2388:
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	w3, [x24, 8324]
.L2387:
	cmp	w25, w3
	bcc	.L2577
.L2390:
	ldr	x1, .LC497
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC499
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
.L2385:
	add	x0, x26, x27
	add	w21, w21, 1
	ldr	w0, [x0, 4]
	cmp	w21, w0
	bls	.L2391
	ldr	w1, [x29, 112]
	ldr	w0, [x26, 4120]
	add	w1, w1, 1
	str	w1, [x29, 112]
	cmp	w1, w0
	bcc	.L2576
	mov	x19, x28
	ldr	x28, [x29, 144]
.L2377:
	ldr	x1, .LC495
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	mov	w23, w0
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2730
	add	x24, x28, 132
	ldrb	w0, [x19, 3]
	mov	w22, 2
	ldr	w1, [x24, 4116]
	cmp	w0, wzr
	csinc	w22, w22, wzr, eq
	cmp	w22, w1
	bgt	.L2393
	add	w23, w23, 2
.L2396:
	cmp	w0, wzr
	sxtw	x25, w22
	cset	w21, eq
	cmp	w21, w22
	add	x25, x24, x25, lsl 1
	blt	.L2575
	b	.L2401
	.p2align 3
.L2399:
	cmp	w21, w22
	bge	.L2401
.L2575:
	add	x0, x25, x21, sxtw
	add	w21, w21, 1
	ldrb	w0, [x0, 5]
	cbz	w0, .L2399
	ldr	x0, [x20, 2944]
	mov	w1, w23
	bl	BsGet
	cmp	w21, w22
	blt	.L2575
.L2401:
	ldr	w0, [x24, 4116]
	add	w22, w22, 1
	cmp	w0, w22
	blt	.L2393
	ldrb	w0, [x19, 3]
	b	.L2396
.L2729:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	b	.L2384
.L2730:
	ldr	x0, [x20, 2944]
	add	w1, w23, 2
	bl	BsGet
.L2393:
	ldr	x1, .LC503
	mov	w21, 1
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, wzr
	mov	w22, w0
	ble	.L2405
.L2574:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	add	w21, w21, 1
	bl	BsGet
	cmp	w22, w21
	bge	.L2574
.L2405:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2731
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 672
	ret
.L2493:
	sxtw	x22, w22
	mov	w28, 0
	add	x22, x22, 1040
	add	w25, w25, 1
	str	w28, [x23, x22, lsl 2]
	ldr	w0, [x23, 4116]
	cmp	w0, w25
	bge	.L2588
	b	.L2732
	.p2align 3
.L2367:
	add	x2, x28, 132
	cmp	w1, wzr
	ldr	w3, [x2, 4116]
	cset	w0, ne
	cmp	w0, w3
	bgt	.L2374
	ldr	w1, [x2, 4124]
.L2375:
	add	x4, x2, x0, sxtw 2
	cmp	w0, w1
	csel	w5, w0, w1, ls
	add	w0, w0, 1
	cmp	w0, w3
	str	w5, [x4, 4152]
	ble	.L2375
	b	.L2374
.L2728:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	ldrb	w1, [x19, 3]
	cbnz	w1, .L2487
	b	.L2365
	.p2align 3
.L2356:
	strb	wzr, [x21]
	b	.L2355
.L2727:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x21]
	b	.L2355
.L2324:
	add	x1, x27, 132
	add	x1, x1, x28, lsl 1
.L2327:
	ldr	w4, [x29, 152]
	add	x2, x1, x0, sxtw
	orr	w4, w0, w4
	add	w0, w0, 1
	cbnz	w4, .L2326
.L2733:
	strb	w25, [x2, 9]
	cmp	w16, w0
	bls	.L2491
	ldr	w4, [x29, 152]
	add	x2, x1, x0, sxtw
	orr	w4, w0, w4
	add	w0, w0, 1
	cbz	w4, .L2733
.L2326:
	cmp	w0, w16
	bcc	.L2327
	ldr	w16, [x3, 8324]
	b	.L2320
.L2718:
	cmp	w7, 1025
	str	w7, [x21, 4120]
	ble	.L2734
	mov	w4, w7
	mov	w22, 0
.L2488:
	ldr	x2, .LC467
	mov	w6, w22
	ldr	x1, .LC479
	mov	w5, 1025
	mov	w3, 1635
	add	x2, x2, 40
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, -1
	add	sp, sp, 672
	ret
	.p2align 3
.L2291:
	add	x24, x28, 132
	ldr	w0, [x24, 4116]
	mov	x25, 0
	str	x19, [x29, 152]
	cmp	w25, w0
	mov	w27, 7
	mov	x19, x20
	bge	.L2735
.L2298:
	add	w20, w25, 1
	cmp	w0, w20
	blt	.L2294
	mov	w21, w20
	lsl	x26, x25, 1
	b	.L2297
.L2295:
	str	w27, [x1, 12392]
	add	w21, w21, 1
	ldr	w0, [x24, 4116]
	cmp	w0, w21
	blt	.L2294
.L2297:
	sxtw	x23, w21
	add	x1, x26, x23
	add	x0, x24, x23, lsl 1
	add	x0, x0, x25
	add	x1, x24, x1, lsl 2
	ldrb	w0, [x0, 5]
	cbz	w0, .L2295
	ldr	x0, [x19, 2944]
	mov	w1, 3
	add	w21, w21, 1
	bl	BsGet
	add	x1, x26, x23
	add	x1, x24, x1, lsl 2
	str	w0, [x1, 12392]
	ldr	w0, [x24, 4116]
	cmp	w0, w21
	bge	.L2297
.L2294:
	sxtw	x25, w20
	cmp	w25, w0
	blt	.L2298
.L2735:
	mov	x20, x19
	ldr	x19, [x29, 152]
	b	.L2305
.L2280:
	add	x21, x28, 132
	ldr	w0, [x21, 4116]
	tbnz	w0, #31, .L2284
	mov	w23, 0
.L2285:
	ldr	x0, [x20, 2944]
	mov	w1, 3
	bl	BsGet
	add	x1, x21, x23, sxtw 2
	add	w23, w23, 1
	str	w0, [x1, 4168]
	ldr	w0, [x21, 4116]
	cmp	w0, w23
	bge	.L2285
	b	.L2284
.L2497:
	mov	w22, 0
	b	.L2268
.L2731:
	ldr	x0, [x20, 2944]
	bl	BsToNextByte
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2736
.L2407:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	mov	w25, w0
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	mov	w26, w0
	orr	w0, w25, w0
	cbz	w0, .L2409
	ldrb	w1, [x19, 3]
	mov	w24, 0
	ldr	w0, [x19, 20]
	mov	w23, 0
	cmp	w1, wzr
	cset	w22, eq
	cmp	w22, w0
	bhi	.L2409
.L2573:
	mov	w21, 0
.L2415:
	add	w21, w21, 1
	cbnz	w25, .L2737
	cbnz	w26, .L2738
.L2412:
	cbnz	w23, .L2739
.L2413:
	cbnz	w24, .L2740
.L2414:
	ldr	w0, [x19, 12]
	cmp	w21, w0
	bls	.L2415
	ldr	w0, [x19, 20]
	add	w22, w22, 1
	cmp	w22, w0
	bls	.L2573
.L2409:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	mov	w23, w0
	cbnz	w0, .L2741
	ldr	w21, [x28, 4248]
.L2418:
	mov	w22, 0
.L2419:
	ldr	x0, [x20, 2944]
	mov	w1, 3
	add	w22, w22, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	cmp	w22, w21
	bls	.L2419
	cmp	w23, wzr
	ccmp	w21, wzr, 4, ne
	beq	.L2423
	ldrb	w1, [x19, 3]
	ldr	w0, [x28, 4248]
	cmp	w1, wzr
	cset	w21, eq
	cmp	w21, w0
	bhi	.L2423
.L2424:
	ldr	x0, [x20, 2944]
	mov	w1, 4
	add	w21, w21, 1
	bl	BsGet
	ldr	w0, [x28, 4248]
	cmp	w21, w0
	bls	.L2424
.L2423:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cbnz	w0, .L2422
	mov	w21, 0
.L2426:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	sub	x1, x29, #3328
	add	x1, x1, x21, uxtw
	add	w21, w21, 1
	strb	w0, [x1, 3488]
	cbz	w0, .L2425
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
.L2425:
	ldr	w0, [x28, 4248]
	cmp	w21, w0
	bls	.L2426
	mov	w23, 1
	cbz	w0, .L2422
.L2572:
	uxtw	x1, w23
	add	x22, x19, x1, lsl 2
	add	x22, x22, 16384
	ldrsw	x0, [x22, 172]
	add	x2, x28, x0, lsl 2
	ldr	w2, [x2, 4292]
	cbz	w2, .L2431
	sub	x2, x29, #3328
	mov	w21, 0
	add	x1, x2, x1
	ldrb	w24, [x1, 3488]
	b	.L2429
.L2428:
	ldrsw	x0, [x22, 172]
	add	x1, x28, x0, lsl 2
	ldr	w1, [x1, 4292]
	cmp	w21, w1
	bcs	.L2431
.L2429:
	lsl	x0, x0, 1
	add	x1, x28, 132
	add	x0, x0, x21, uxtw
	add	w21, w21, 1
	add	x0, x0, 1044
	cbz	w24, .L2428
	ldrsw	x0, [x1, x0, lsl 2]
	add	x0, x0, 1036
	ldr	w0, [x1, x0, lsl 2]
	sub	x1, x29, #3328
	add	x0, x1, x0
	ldrb	w0, [x0, 3488]
	cbz	w0, .L2428
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldrsw	x0, [x22, 172]
	add	x1, x28, x0, lsl 2
	ldr	w1, [x1, 4292]
	cmp	w21, w1
	bcc	.L2429
.L2431:
	ldr	w0, [x28, 4248]
	add	w23, w23, 1
	cmp	w23, w0
	bls	.L2572
.L2422:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2432
.L2436:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2434
	ldr	w0, [x28, 4248]
	mov	w26, 0
	mov	w22, 1
	cbz	w0, .L2434
	ldr	x23, .LC505
	ldr	x24, .LC507
.L2570:
	add	x21, x19, x22, uxtw 2
	mov	w25, 0
	add	x21, x21, 16384
	ldrsw	x0, [x21, 172]
	add	x1, x28, x0, lsl 2
	ldr	w1, [x1, 4292]
	cbz	w1, .L2446
.L2571:
	lsl	x0, x0, 1
	ldrb	w2, [x19, 3]
	add	x0, x0, x25, uxtw
	mov	x1, x23
	add	w25, w25, 1
	add	x0, x28, x0, lsl 2
	cbnz	w2, .L2438
	ldr	w0, [x0, 4308]
	cmp	w0, wzr
	ble	.L2439
.L2438:
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	mov	w26, w0
.L2439:
	cbnz	w26, .L2742
.L2441:
	ldrsw	x0, [x21, 172]
	add	x1, x28, x0, lsl 2
	ldr	w1, [x1, 4292]
	cmp	w25, w1
	bcc	.L2571
.L2446:
	ldr	w0, [x28, 4248]
	add	w22, w22, 1
	cmp	w22, w0
	bls	.L2570
.L2434:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cbnz	w0, .L2743
.L2447:
	add	x19, x28, 132
	ldr	w0, [x19, 4116]
	mov	w21, 1
	cbnz	w0, .L2569
	b	.L2485
	.p2align 3
.L2483:
	ldr	w0, [x19, 4116]
	cmp	w21, w0
	bhi	.L2485
.L2569:
	add	x0, x19, x21, uxtw 2
	add	w21, w21, 1
	ldrsw	x0, [x0, 4136]
	add	x0, x0, 1040
	ldr	w0, [x19, x0, lsl 2]
	cbnz	w0, .L2483
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	w0, [x19, 4116]
	cmp	w21, w0
	bls	.L2569
.L2485:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, 0
	add	sp, sp, 672
	ret
.L2739:
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	cbz	w24, .L2414
.L2740:
	ldr	x0, [x20, 2944]
	mov	w1, 2
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 2
	bl	BsGet
	b	.L2414
.L2738:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	mov	w24, w0
	cbz	w23, .L2413
	b	.L2739
.L2737:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	mov	w23, w0
	cbz	w26, .L2412
	b	.L2738
.L2742:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2441
	ldr	x0, [x20, 2944]
	mov	x1, x24
	bl	HEVC_ue_v
	b	.L2441
.L2432:
	mov	w21, 0
.L2435:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	add	w21, w21, w1
	bl	BsGet
	ldr	w0, [x28, 4248]
	cmp	w21, w0
	bls	.L2435
	b	.L2436
.L2717:
	ldr	x2, .LC467
	mov	w4, w0
	ldr	x1, .LC473
	mov	w5, 1024
	mov	w3, 1537
	add	x2, x2, 40
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, -1
	add	sp, sp, 672
	ret
.L2715:
	cmp	w0, wzr
	mov	w21, 1
	bgt	.L2243
	b	.L2242
.L2713:
	ldr	w3, [x19, 12]
	mov	w2, 0
	add	x1, x29, 192
	mov	x0, x20
	bl	HEVC_DecPTL
	b	.L2208
.L2712:
	ldr	x2, .LC467
	mov	w4, 1
	ldr	x1, .LC469
	mov	w0, w4
	add	x2, x2, 40
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, -1
	add	sp, sp, 672
	ret
.L2734:
	mov	w0, -1
	str	w0, [x21, 4192]
.L2312:
	ldr	x1, .LC481
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 255
	str	w0, [x28, 4256]
	bls	.L2349
.L2486:
	ldr	x1, .LC483
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	mov	w0, -1
	add	sp, sp, 672
	ret
.L2743:
	ldr	x1, .LC509
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	w21, [x19, 24]
	add	w25, w0, w21
	cmp	w25, 1024
	bhi	.L2448
	cmp	w21, w25
	bcs	.L2455
	ldr	x23, .LC513
	b	.L2454
	.p2align 3
.L2745:
	ldr	x0, [x20, 2944]
	bl	BsGet
	mov	w22, w0
.L2452:
	ldr	x0, [x20, 2944]
	mov	x1, x23
	bl	HEVC_ue_v
	mov	w5, w0
	cmp	w5, 7
	mov	w3, w0
	mov	w2, w22
	add	x1, x29, 256
	mov	x0, x20
	bhi	.L2744
	bl	HEVC_DecHrdParam
	add	w21, w21, 1
	cmp	w25, w21
	bls	.L2455
.L2454:
	mov	w1, 1
	cbnz	w21, .L2745
	mov	w22, 1
	b	.L2452
.L2744:
	ldr	x1, .LC515
	mov	w4, 7
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2447
.L2455:
	cbz	w25, .L2447
	ldr	w0, [x28, 4252]
	cmp	w0, 1
	bls	.L2447
	mov	w21, 1
	ldr	x23, .LC527
	mov	w24, w25
	mov	w22, w21
	mov	x25, x19
.L2481:
	add	x27, x25, x21, uxtw 2
	ldr	w0, [x27, 8324]
	cmp	w0, 2
	bls	.L2457
	sub	w0, w0, #1
	str	w0, [x29, 568]
.L2458:
	ldr	x1, .LC517
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 16
	bhi	.L2459
	add	w0, w0, 1
	str	w0, [x29, 112]
	cmp	w0, 1
	add	x0, x29, 572
	str	x0, [x29, 152]
	mov	w0, 1
	str	w0, [x29, 128]
	bls	.L2470
.L2469:
	ldr	x1, .LC521
	mov	w26, 0
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x29, 144]
	ldr	x1, [x29, 152]
	ldr	w4, [x28, 4244]
	str	w0, [x1]
.L2464:
	mov	w19, 0
	b	.L2468
.L2466:
	ldr	x0, [x20, 2944]
	bl	BsGet
	ldr	w4, [x28, 4244]
.L2468:
	cmp	w4, w21
	add	x5, x27, 16384
	mov	w1, 1
	mov	w0, w21
	bhi	.L2465
	ldr	w0, [x5, 228]
	add	w0, w0, w1
.L2465:
	add	x0, x25, x0, uxtw 2
	ldr	w0, [x0, 8324]
	cmp	w19, w0
	add	w19, w19, 1
	bcc	.L2466
	ldr	w0, [x29, 144]
	add	w26, w26, 1
	cmp	w0, w26
	bcs	.L2464
	ldr	x1, [x29, 152]
	ldr	w0, [x29, 128]
	add	x1, x1, 4
	str	x1, [x29, 152]
	ldr	w1, [x29, 112]
	add	w0, w0, 1
	str	w0, [x29, 128]
	cmp	w1, w0
	bne	.L2469
.L2470:
	ldr	w0, [x29, 112]
	cbz	w0, .L2462
	ldr	w1, [x28, 4244]
	add	x0, x28, 132
	str	xzr, [x29, 128]
	str	x0, [x29, 104]
.L2471:
	ldr	w0, [x29, 128]
	str	w0, [x29, 96]
	str	wzr, [x29, 152]
.L2480:
	cmp	w1, w21
	mov	w0, w21
	bhi	.L2478
	add	x0, x27, 16384
	ldr	w0, [x0, 228]
	add	w0, w0, 1
.L2478:
	ldr	x2, [x29, 104]
	add	x0, x2, x0, uxtw 2
	ldr	w2, [x29, 152]
	ldr	w0, [x0, 8292]
	cmp	w2, w0
	bhi	.L2746
	ldr	x1, .LC523
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 31
	bhi	.L2472
	add	w0, w0, 1
	add	x1, x29, 568
	str	w0, [x29, 100]
	ldr	x0, [x29, 128]
	str	wzr, [x29, 144]
	ldr	w26, [x1, x0, lsl 2]
.L2473:
	mov	w19, 0
.L2476:
	cmp	w24, 1
	mov	w1, 0
	ldr	x0, [x20, 2944]
	bls	.L2474
	.p2align 2
.L2475:
	add	w1, w1, 1
	lsl	w2, w22, w1
	cmp	w24, w2
	bhi	.L2475
.L2474:
	bl	BsGet
	add	w19, w19, 1
	ldr	x0, [x20, 2944]
	mov	x1, x23
	bl	HEVC_ue_v
	cmp	w26, w19
	bcs	.L2476
	ldr	w0, [x29, 144]
	ldr	w1, [x29, 100]
	add	w0, w0, 1
	str	w0, [x29, 144]
	cmp	w0, w1
	bne	.L2473
	ldr	w0, [x29, 152]
	add	w0, w0, 1
	str	w0, [x29, 152]
	ldr	x0, [x29, 104]
	ldr	w1, [x0, 4112]
	b	.L2480
.L2472:
	ldr	x1, .LC525
	mov	w5, w0
	ldr	w3, [x29, 96]
	mov	w2, w21
	ldr	w4, [x29, 152]
	mov	w0, 1
	bl	dprint_vfmw
.L2463:
	ldr	x1, .LC529
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2447
.L2746:
	ldr	x0, [x29, 128]
	ldr	w2, [x29, 112]
	add	x0, x0, 1
	str	x0, [x29, 128]
	cmp	w2, w0
	bhi	.L2471
.L2462:
	ldr	w0, [x28, 4252]
	add	w21, w21, 1
	cmp	w21, w0
	bcc	.L2481
	b	.L2447
.L2459:
	ldr	x1, .LC519
	mov	w3, w0
	mov	w4, 16
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2463
.L2457:
	str	w22, [x29, 568]
	b	.L2458
.L2448:
	ldr	x1, .LC511
	mov	w3, 1024
	mov	w2, w25
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2447
.L2741:
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	mov	w21, w0
	b	.L2418
.L2736:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L2407
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	b	.L2407
	.size	HEVC_ParseVPSExtension, .-HEVC_ParseVPSExtension
	.align	3
.LC466:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC467:
	.xword	.LANCHOR3
	.align	3
.LC469:
	.xword	.LC468
	.align	3
.LC471:
	.xword	.LC470
	.align	3
.LC473:
	.xword	.LC472
	.align	3
.LC475:
	.xword	.LC474
	.align	3
.LC477:
	.xword	.LC476
	.align	3
.LC479:
	.xword	.LC478
	.align	3
.LC481:
	.xword	.LC480
	.align	3
.LC483:
	.xword	.LC482
	.align	3
.LC485:
	.xword	.LC484
	.align	3
.LC487:
	.xword	.LC486
	.align	3
.LC489:
	.xword	.LC488
	.align	3
.LC491:
	.xword	.LC490
	.align	3
.LC493:
	.xword	.LC492
	.align	3
.LC495:
	.xword	.LC494
	.align	3
.LC497:
	.xword	.LC496
	.align	3
.LC499:
	.xword	.LC498
	.align	3
.LC501:
	.xword	.LC500
	.align	3
.LC503:
	.xword	.LC502
	.align	3
.LC505:
	.xword	.LC504
	.align	3
.LC507:
	.xword	.LC506
	.align	3
.LC509:
	.xword	.LC508
	.align	3
.LC511:
	.xword	.LC510
	.align	3
.LC513:
	.xword	.LC512
	.align	3
.LC515:
	.xword	.LC514
	.align	3
.LC517:
	.xword	.LC516
	.align	3
.LC519:
	.xword	.LC518
	.align	3
.LC521:
	.xword	.LC520
	.align	3
.LC523:
	.xword	.LC522
	.align	3
.LC525:
	.xword	.LC524
	.align	3
.LC527:
	.xword	.LC526
	.align	3
.LC529:
	.xword	.LC528
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessVPS
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x21, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x20, 3]
	mov	w1, 1
	ldr	x0, [x21, 2944]
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L2748
	ldr	x1, .LC531
	uxtb	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
.L2748:
	ldr	x0, [x21, 2944]
	mov	w1, 6
	bl	BsGet
	cmp	w0, 63
	str	w0, [x20, 8]
	bhi	.L2808
	ldr	x0, [x21, 2944]
	mov	w1, 3
	bl	BsGet
	cmp	w0, 7
	mov	w25, w0
	bhi	.L2809
	str	w0, [x20, 12]
	mov	w1, 1
	ldr	x0, [x21, 2944]
	bl	BsGet
	strb	w0, [x20, 1]
	mov	w1, 16
	ldr	x0, [x21, 2944]
	bl	BsGet
	mov	w1, 65535
	cmp	w0, w1
	bne	.L2810
	mov	w3, w25
	mov	w2, 1
	add	x1, x20, 124
	mov	x0, x21
	bl	HEVC_DecPTL
	cbnz	w0, .L2811
	ldr	x0, [x21, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w28, w0
	tbnz	w25, #31, .L2758
	ldr	x27, .LC541
	add	w23, w25, 1
	ldr	x26, .LC543
	mov	w19, 0
	ldr	x24, .LC545
	b	.L2760
	.p2align 3
.L2757:
	cmp	w23, w19
	beq	.L2758
.L2760:
	add	x22, x20, x19, sxtw 2
	ldr	x0, [x21, 2944]
	mov	x1, x27
	add	w19, w19, 1
	bl	HEVC_ue_v
	add	w0, w0, 1
	str	w0, [x22, 28]
	mov	x1, x26
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
	str	w0, [x22, 60]
	mov	x1, x24
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
	str	w0, [x22, 92]
	cbnz	w28, .L2757
	cmp	w25, w19
	blt	.L2758
	.p2align 2
.L2794:
	add	x0, x20, x19, sxtw 2
	ldr	w1, [x20, 28]
	add	w19, w19, 1
	cmp	w23, w19
	str	w1, [x0, 28]
	ldr	w1, [x20, 60]
	str	w1, [x0, 60]
	ldr	w1, [x20, 92]
	str	w1, [x0, 92]
	bne	.L2794
.L2758:
	ldr	x0, [x21, 2944]
	mov	w1, 6
	bl	BsGet
	cmp	w0, 1
	str	w0, [x20, 16]
	bhi	.L2812
	ldr	w1, [x20, 8]
	sub	w1, w1, #1
	cmp	w1, 61
	ccmp	w0, wzr, 4, ls
	bne	.L2813
.L2761:
	ldr	x1, .LC551
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
	cmp	w0, 1023
	str	w0, [x20, 20]
	bhi	.L2814
	ldr	x19, .LC554
	mov	x2, 8192
	mov	w1, 0
	add	x0, x20, 132
	mov	w24, 1
	ldr	x3, [x19, 96]
	blr	x3
	add	x0, x20, 8192
	ldr	x3, [x19, 96]
	mov	x2, 4096
	mov	w1, 0
	add	x0, x0, 132
	blr	x3
	ldr	w0, [x20, 20]
	cmp	w0, wzr
	ble	.L2764
	.p2align 2
.L2793:
	sxtw	x23, w24
	mov	w19, 0
	mov	w26, 0
	lsl	x22, x23, 1
	.p2align 2
.L2766:
	ldr	x0, [x21, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	add	x1, x22, x26, uxtw
	add	x1, x20, x1, lsl 2
	cbz	w0, .L2765
	add	w26, w26, 1
	str	w19, [x1, 132]
.L2765:
	ldr	w0, [x20, 16]
	add	w19, w19, 1
	cmp	w19, w0
	bls	.L2766
	add	x23, x20, x23, lsl 2
	add	w24, w24, 1
	str	w26, [x23, 8324]
	ldr	w0, [x20, 20]
	cmp	w24, w0
	ble	.L2793
.L2764:
	ldr	x0, [x21, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2774
	ldr	x0, [x21, 2944]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x21, 2944]
	mov	w1, 32
	bl	BsGet
	ldr	x0, [x21, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2815
.L2771:
	ldr	x1, .LC558
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
	cmp	w0, 1024
	str	w0, [x20, 24]
	bhi	.L2772
	cmp	w0, wzr
	ble	.L2774
	ldr	x22, .LC562
	mov	w19, 0
	ldr	x0, [x21, 2944]
	mov	x1, x22
	bl	HEVC_ue_v
	mov	w2, 1
	.p2align 2
.L2783:
	mov	w3, w25
	add	x1, x29, 104
	mov	x0, x21
	add	w19, w19, 1
	bl	HEVC_DecHrdParam
	cbnz	w0, .L2816
.L2776:
	ldr	w0, [x20, 24]
	mov	x1, x22
	cmp	w0, w19
	ble	.L2774
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
	mov	w2, 1
	cbz	w19, .L2783
	ldr	x0, [x21, 2944]
	mov	w1, w2
	add	w19, w19, 1
	bl	BsGet
	mov	w2, w0
	mov	w3, w25
	add	x1, x29, 104
	mov	x0, x21
	bl	HEVC_DecHrdParam
	cbz	w0, .L2776
.L2816:
	ldr	x1, .LC564
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2774:
	ldr	x0, [x21, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2770
	ldrb	w19, [x21, 1]
	cmp	w19, 1
	bne	.L2779
	b	.L2817
	.p2align 3
.L2818:
	ldr	x0, [x21, 2944]
	bl	BsGet
.L2779:
	ldr	x0, [x21, 2944]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L2770
	ldr	x2, [x21, 2984]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcc	.L2818
.L2770:
	mov	w0, 0
.L2804:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2815:
	ldr	x1, .LC556
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
	b	.L2771
.L2813:
	ldr	x1, .LC549
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
	strb	w0, [x21, 1]
	b	.L2761
.L2810:
	ldr	x1, .LC537
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2804
.L2817:
	ldr	x0, [x21, 2944]
	bl	BsToNextByte
	mov	x1, x20
	mov	x0, x21
	bl	HEVC_ParseVPSExtension
	cbnz	w0, .L2819
	ldr	x0, [x21, 2944]
	mov	w1, w19
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2770
	b	.L2779
	.p2align 3
.L2809:
	ldr	x1, .LC535
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2804
.L2808:
	ldr	x1, .LC533
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2804
.L2812:
	mov	w2, 1
	ldr	x1, .LC547
	mov	w0, w2
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2804
.L2811:
	ldr	x1, .LC539
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2804
.L2814:
	ldr	x1, .LC553
.L2806:
	mov	w2, w0
	mov	w3, 1024
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2804
.L2772:
	ldr	x1, .LC560
	b	.L2806
.L2819:
	ldr	x1, .LC566
	mov	w0, w19
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2804
	.size	HEVC_ProcessVPS, .-HEVC_ProcessVPS
	.align	3
.LC531:
	.xword	.LC530
	.align	3
.LC533:
	.xword	.LC532
	.align	3
.LC535:
	.xword	.LC534
	.align	3
.LC537:
	.xword	.LC536
	.align	3
.LC539:
	.xword	.LC538
	.align	3
.LC541:
	.xword	.LC540
	.align	3
.LC543:
	.xword	.LC542
	.align	3
.LC545:
	.xword	.LC544
	.align	3
.LC547:
	.xword	.LC546
	.align	3
.LC549:
	.xword	.LC548
	.align	3
.LC551:
	.xword	.LC550
	.align	3
.LC553:
	.xword	.LC552
	.align	3
.LC554:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC556:
	.xword	.LC555
	.align	3
.LC558:
	.xword	.LC557
	.align	3
.LC560:
	.xword	.LC559
	.align	3
.LC562:
	.xword	.LC561
	.align	3
.LC564:
	.xword	.LC563
	.align	3
.LC566:
	.xword	.LC565
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVPS
	.type	HEVC_DecVPS, %function
HEVC_DecVPS:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC567
	ldr	x0, [x21]
	cbz	x0, .L2827
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	cmp	w0, 15
	mov	w22, w0
	bhi	.L2828
	mov	w19, 24912
	umull	x19, w0, w19
	ldr	x0, [x20, 2952]
	add	x1, x0, x19
	ldrb	w0, [x0, x19]
	cbnz	w0, .L2829
	str	w22, [x1, 4]
	mov	x0, x20
	ldr	x1, [x20, 2952]
	add	x1, x1, x19
	bl	HEVC_ProcessVPS
	mov	w23, w0
	cbnz	w0, .L2830
	ldr	x0, [x20, 2952]
	mov	w1, 1
	add	x0, x0, x19
	strb	w1, [x0, 2]
	ldr	x0, [x20, 2952]
	strb	w1, [x0, x19]
.L2822:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2829:
	ldr	x24, .LC572
	mov	x2, 24912
	ldr	x21, [x21]
	mov	w1, 0
	add	x21, x21, 458752
	ldr	x3, [x24, 96]
	mov	x0, x21
	blr	x3
	str	w22, [x21, 4]
	mov	x1, x21
	mov	x0, x20
	bl	HEVC_ProcessVPS
	mov	w23, w0
	cbnz	w0, .L2831
	mov	w0, 1
	strb	w0, [x21, 2]
	strb	w0, [x21]
	mov	x1, x21
	ldr	x3, [x24, 112]
	mov	x2, 24912
	ldr	x0, [x20, 2952]
	add	x0, x0, x19
	blr	x3
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2831:
	ldr	x1, .LC574
	mov	w2, w22
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2822
	.p2align 3
.L2828:
	ldr	x1, .LC571
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2822
.L2830:
	ldr	x1, .LC576
	mov	w2, w22
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	ldr	x0, [x20, 2952]
	mov	w1, 1
	add	x0, x0, x19
	strb	w1, [x0, 2]
	ldr	x0, [x20, 2952]
	strb	wzr, [x0, x19]
	b	.L2822
.L2827:
	ldr	x2, .LC568
	mov	w23, -1
	ldr	x1, .LC569
	add	x2, x2, 64
	bl	dprint_vfmw
	b	.L2822
	.size	HEVC_DecVPS, .-HEVC_DecVPS
	.align	3
.LC567:
	.xword	.LANCHOR1
	.align	3
.LC568:
	.xword	.LANCHOR3
	.align	3
.LC569:
	.xword	.LC166
	.align	3
.LC571:
	.xword	.LC570
	.align	3
.LC572:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC574:
	.xword	.LC573
	.align	3
.LC576:
	.xword	.LC575
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVuiParam
	.type	HEVC_DecVuiParam, %function
HEVC_DecVuiParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2877
.L2834:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2878
.L2836:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2879
.L2838:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2880
.L2840:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x20, 3]
	mov	w1, 1
	ldr	x0, [x19, 2944]
	bl	BsGet
	strb	w0, [x20, 2]
	mov	w1, 1
	ldr	x0, [x19, 2944]
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2841
	ldr	x1, .LC582
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	w0, [x21, 60]
	cmp	w0, 3
	bhi	.L2881
	ldr	x1, .LC586
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC588
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC590
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
.L2841:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2844
	ldr	x0, [x19, 2944]
	mov	w1, 32
	bl	BsGet
	str	w0, [x20, 36]
	mov	w1, 32
	ldr	x0, [x19, 2944]
	bl	BsGet
	str	w0, [x20, 40]
	ldr	w1, [x20, 36]
	cbnz	w1, .L2882
.L2845:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2883
.L2846:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L2884
.L2844:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w1, w0
	mov	w0, 0
	cbnz	w1, .L2885
.L2843:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2885:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x1, .LC597
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	cmp	w0, 4095
	bhi	.L2886
.L2847:
	ldr	x1, .LC601
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC603
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC605
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC607
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2880:
	ldr	x1, .LC578
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC580
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	b	.L2840
	.p2align 3
.L2877:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 255
	str	w0, [x20, 8]
	bne	.L2834
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsGet
	str	w0, [x20, 12]
	mov	w1, 16
	ldr	x0, [x19, 2944]
	bl	BsGet
	str	w0, [x20, 16]
	b	.L2834
	.p2align 3
.L2879:
	ldr	x0, [x19, 2944]
	mov	w1, 3
	bl	BsGet
	str	w0, [x20, 20]
	mov	w1, 1
	ldr	x0, [x19, 2944]
	bl	BsGet
	strb	w0, [x20]
	mov	w1, 1
	ldr	x0, [x19, 2944]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x20, 1]
	cbz	w0, .L2838
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	str	w0, [x20, 24]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	str	w0, [x20, 28]
	mov	w1, 8
	ldr	x0, [x19, 2944]
	bl	BsGet
	str	w0, [x20, 32]
	b	.L2838
	.p2align 3
.L2878:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	b	.L2836
	.p2align 3
.L2884:
	ldr	w3, [x21, 52]
	mov	w2, 1
	add	x1, x20, 44
	mov	x0, x19
	bl	HEVC_DecHrdParam
	cbz	w0, .L2844
	ldr	x1, .LC595
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2843
	.p2align 3
.L2883:
	ldr	x1, .LC593
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	b	.L2846
	.p2align 3
.L2882:
	ldr	x2, .LC591
	mov	w3, 10000
	umull	x0, w0, w3
	ldr	x2, [x2, 488]
	blr	x2
	add	w0, w0, 5
	mov	w1, 52429
	movk	w1, 0xcccc, lsl 16
	umull	x0, w0, w1
	lsr	x0, x0, 35
	str	w0, [x19, 144]
	b	.L2845
	.p2align 3
.L2886:
	ldr	x1, .LC599
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2847
	.p2align 3
.L2881:
	ldr	x1, .LC584
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2843
	.size	HEVC_DecVuiParam, .-HEVC_DecVuiParam
	.align	3
.LC578:
	.xword	.LC577
	.align	3
.LC580:
	.xword	.LC579
	.align	3
.LC582:
	.xword	.LC581
	.align	3
.LC584:
	.xword	.LC583
	.align	3
.LC586:
	.xword	.LC585
	.align	3
.LC588:
	.xword	.LC587
	.align	3
.LC590:
	.xword	.LC589
	.align	3
.LC591:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC593:
	.xword	.LC592
	.align	3
.LC595:
	.xword	.LC594
	.align	3
.LC597:
	.xword	.LC596
	.align	3
.LC599:
	.xword	.LC598
	.align	3
.LC601:
	.xword	.LC600
	.align	3
.LC603:
	.xword	.LC602
	.align	3
.LC605:
	.xword	.LC604
	.align	3
.LC607:
	.xword	.LC606
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_se_v
	.type	HEVC_se_v, %function
HEVC_se_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 32
	mov	x0, x20
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	bls	.L2892
	mov	w0, 2147483647
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2892:
	mov	w1, w0
	mov	x0, x20
	add	w21, w1, 1
	bl	BsSkip
	mov	w1, w21
	mov	x0, x20
	bl	BsShow
	sub	w0, w0, #1
	asr	w2, w0, 1
	and	w0, w0, 1
	cmp	w0, wzr
	mov	w1, w21
	mov	x0, x20
	neg	w19, w2
	csinc	w19, w19, w2, eq
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_se_v, .-HEVC_se_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Structure_Of_Pictures_Info
	.type	HEVC_Sei_Structure_Of_Pictures_Info, %function
HEVC_Sei_Structure_Of_Pictures_Info:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC609
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC611
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
	cmp	w0, 1024
	mov	w22, w0
	bhi	.L2894
	mov	w19, 0
	cbz	w0, .L2900
	ldr	x24, .LC615
	ldr	x23, .LC617
	.p2align 2
.L2903:
	ldr	x0, [x21, 2944]
	mov	w1, 6
	bl	BsGet
	sub	w20, w0, #19
	ldr	x0, [x21, 2944]
	mov	w1, 3
	bl	BsGet
	cmp	w20, 1
	mov	x1, x24
	bls	.L2897
	ldr	x0, [x21, 2944]
	bl	HEVC_ue_v
.L2897:
	mov	x1, x23
	cbz	w19, .L2898
	ldr	x0, [x21, 2944]
	bl	HEVC_se_v
.L2898:
	add	w19, w19, 1
	cmp	w22, w19
	bne	.L2903
.L2900:
	ldr	x0, [x21, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L2896:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2894:
	ldr	x1, .LC613
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2896
	.size	HEVC_Sei_Structure_Of_Pictures_Info, .-HEVC_Sei_Structure_Of_Pictures_Info
	.align	3
.LC609:
	.xword	.LC608
	.align	3
.LC611:
	.xword	.LC610
	.align	3
.LC613:
	.xword	.LC612
	.align	3
.LC615:
	.xword	.LC614
	.align	3
.LC617:
	.xword	.LC616
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Recovery_Point
	.type	HEVC_Sei_Recovery_Point, %function
HEVC_Sei_Recovery_Point:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L2908
	ldr	x1, .LC619
	ldr	x0, [x19, 2944]
	bl	HEVC_se_v
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	bl	BsToNextByte
	mov	w0, 0
.L2907:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2908:
	mov	w0, -1
	b	.L2907
	.size	HEVC_Sei_Recovery_Point, .-HEVC_Sei_Recovery_Point
	.align	3
.LC619:
	.xword	.LC618
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Color_Remapping_Info
	.type	HEVC_Sei_Color_Remapping_Info, %function
HEVC_Sei_Color_Remapping_Info:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2928
	ldr	x1, .LC621
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L2911
.L2925:
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x22]
.L2910:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2911:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L2936
.L2912:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	mov	w23, 3
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
.L2914:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	uxtb	w1, w0
	cbz	w1, .L2917
	and	w0, w0, 255
	mov	w19, 0
	add	w21, w0, 1
	.p2align 2
.L2916:
	ldr	x0, [x20, 2944]
	mov	w1, 16
	add	w19, w19, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 16
	bl	BsGet
	cmp	w21, w19
	bne	.L2916
.L2917:
	subs	w23, w23, #1
	bne	.L2914
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	beq	.L2918
.L2922:
	add	x26, x22, 3
	mov	x23, x22
	mov	w25, 33
.L2919:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	sub	w24, w23, w22
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 32
	strb	w1, [x23, 40]
	bhi	.L2937
	cbz	w1, .L2927
	mov	w21, 0
	.p2align 2
.L2926:
	uxtw	x19, w21
	ldr	x0, [x20, 2944]
	mov	w1, 16
	add	w21, w21, 1
	umaddl	x19, w24, w25, x19
	bl	BsGet
	mov	w1, 16
	add	x19, x22, x19, lsl 1
	strh	w0, [x19, 44]
	ldr	x0, [x20, 2944]
	bl	BsGet
	strh	w0, [x19, 242]
	ldrb	w0, [x23, 40]
	add	w0, w0, 1
	cmp	w0, w21
	bhi	.L2926
.L2927:
	add	x23, x23, 1
	cmp	x23, x26
	bne	.L2919
	b	.L2925
	.p2align 3
.L2928:
	mov	w0, -1
	b	.L2910
.L2918:
	ldr	x0, [x20, 2944]
	mov	w1, 4
	add	x19, x22, 4
	add	x24, x22, 40
	bl	BsGet
	ldr	x23, .LC623
.L2920:
	add	x21, x19, 12
.L2921:
	ldr	x0, [x20, 2944]
	mov	x1, x23
	bl	HEVC_se_v
	str	w0, [x19], 4
	cmp	x19, x21
	bne	.L2921
	cmp	x19, x24
	bne	.L2920
	b	.L2922
.L2936:
	ldr	x0, [x20, 2944]
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x22, 1]
	mov	w1, 8
	ldr	x0, [x20, 2944]
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	b	.L2912
.L2937:
	ldr	x1, .LC625
	uxtb	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2910
	.size	HEVC_Sei_Color_Remapping_Info, .-HEVC_Sei_Color_Remapping_Info
	.align	3
.LC621:
	.xword	.LC620
	.align	3
.LC623:
	.xword	.LC622
	.align	3
.LC625:
	.xword	.LC624
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Payload
	.type	HEVC_Sei_Payload, %function
HEVC_Sei_Payload:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x23, x2
	mov	w22, w3
	mov	w21, w4
	bl	_mcount
	cmp	x19, xzr
	cset	w2, eq
	cmp	x20, xzr
	cset	w0, eq
	orr	w0, w2, w0
	cbnz	w0, .L2964
	ldr	x0, [x19, 2984]
	ldr	w0, [x0, 16]
	cmp	w0, 39
	beq	.L2985
	cmp	w22, 5
	beq	.L2968
	cmp	w22, 132
	beq	.L2969
	mov	w20, 0
	cbz	w21, .L2963
	.p2align 2
.L2980:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	add	w20, w20, 1
	bl	BsGet
	cmp	w21, w20
	bne	.L2980
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_More_Data_In_Payload
	cbnz	w0, .L2972
	.p2align 2
.L2976:
	mov	w0, 0
.L2940:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2968:
	mov	w2, w21
	add	x1, x20, 568
	mov	x0, x19
	bl	HEVC_Sei_User_Data_Unregistered
	cbnz	w0, .L2964
.L2963:
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_More_Data_In_Payload
	cbz	w0, .L2976
.L2972:
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_Sei_Payload_Extension_Present
	cbnz	w0, .L2986
	.p2align 2
.L2975:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	bl	BsIsByteAligned
	cbz	w0, .L2975
	b	.L2976
	.p2align 3
.L2985:
	cmp	w22, 147
	bls	.L2987
.L2942:
	mov	w20, 0
	cbz	w21, .L2963
	.p2align 2
.L2979:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	add	w20, w20, 1
	bl	BsGet
	cmp	w21, w20
	bne	.L2979
	b	.L2963
	.p2align 3
.L2969:
	add	x1, x20, 619
	mov	x0, x19
	bl	HEVC_Sei_Decoded_Picture_Hash
	cbz	w0, .L2963
	.p2align 2
.L2964:
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2987:
	ldr	x0, .LC626
	ldrb	w0, [x0,w22,uxtw]
	adr	x1, .Lrtx2944
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2944:
	.section	.rodata
	.align	0
	.align	2
.L2944:
	.byte	(.L2943 - .Lrtx2944) / 4
	.byte	(.L2945 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2946 - .Lrtx2944) / 4
	.byte	(.L2968 - .Lrtx2944) / 4
	.byte	(.L2948 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2949 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2950 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2951 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2952 - .Lrtx2944) / 4
	.byte	(.L2953 - .Lrtx2944) / 4
	.byte	(.L2954 - .Lrtx2944) / 4
	.byte	(.L2955 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2956 - .Lrtx2944) / 4
	.byte	(.L2957 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2958 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2959 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2960 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2942 - .Lrtx2944) / 4
	.byte	(.L2961 - .Lrtx2944) / 4
	.text
	.p2align 3
.L2986:
	ldr	x1, .LC628
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	b	.L2975
.L2961:
	cmn	x20, #618
	cset	w0, eq
	orr	w2, w2, w0
	cbnz	w2, .L2964
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	strb	w0, [x20, 618]
	b	.L2963
.L2960:
	add	x1, x20, 612
	mov	x0, x19
	bl	HEVC_Sei_Content_Light_Level_Information
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2959:
	add	x1, x20, 128
	mov	x0, x19
	bl	HEVC_Sei_Color_Remapping_Info
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2958:
	adds	x1, x20, 568
	cset	w0, eq
	orr	w2, w2, w0
	cbnz	w2, .L2964
	mov	w0, 1
	strb	w0, [x20, 568]
	mov	x0, x19
	bl	HEVC_Sei_Mastering_Display_Colour_Volume.part.24
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2957:
	cmn	x20, #568
	cset	w0, eq
	orr	w2, w2, w0
	cbnz	w2, .L2964
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	b	.L2963
.L2956:
	mov	w3, w21
	mov	x2, x23
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_Sei_Scalable_Nesting
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2955:
	add	x1, x20, 568
	mov	x0, x19
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2954:
	add	x2, x23, 2108
	add	x1, x20, 568
	mov	x0, x19
	bl	HEVC_Sei_Dec_Unit_Info
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2953:
	add	x1, x20, 568
	mov	x0, x19
	bl	HEVC_Sei_Active_Param_sets
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2952:
	mov	w2, w21
	add	x1, x20, 619
	mov	x0, x19
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2951:
	add	x1, x20, 568
	mov	x0, x19
	bl	HEVC_Sei_Display_Orientation
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2950:
	add	x1, x20, 568
	mov	x0, x19
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2949:
	add	x1, x20, 619
	mov	x0, x19
	bl	HEVC_Sei_Tone_Mapping_Info
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2948:
	add	x1, x20, 568
	mov	x0, x19
	bl	HEVC_Sei_Recovery_Point
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2946:
	mov	w2, w21
	add	x1, x20, 56
	mov	x0, x19
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2945:
	add	x2, x23, 2064
	add	x1, x20, 8
	mov	x0, x19
	bl	HEVC_Sei_Pic_Timming
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.p2align 3
.L2943:
	add	x2, x23, 2108
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_Sei_Buf_Period
	cbz	w0, .L2963
	mov	w0, -1
	b	.L2940
	.size	HEVC_Sei_Payload, .-HEVC_Sei_Payload
	.align	3
.LC626:
	.xword	.L2944
	.align	3
.LC628:
	.xword	.LC627
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SeiMessage
	.type	HEVC_SeiMessage, %function
HEVC_SeiMessage:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	mov	x23, x2
	bl	_mcount
	mov	w20, 0
	ldr	x0, [x19, 2944]
	b	.L2989
	.p2align 3
.L2991:
	bl	BsSkip
	add	w20, w20, 255
	ldr	x0, [x19, 2944]
	ldr	w4, [x0, 24]
	ldr	w3, [x0, 32]
	add	w1, w3, 8
	cmp	w1, w4, lsl 3
	bhi	.L2998
.L2989:
	mov	w1, 8
	bl	BsShow
	cmp	w0, 255
	mov	w1, 8
	ldr	x0, [x19, 2944]
	beq	.L2991
	bl	BsGet
	mov	w21, 0
	mov	w24, w0
	ldr	x0, [x19, 2944]
	b	.L2992
	.p2align 3
.L2993:
	bl	BsSkip
	add	w21, w21, 255
	ldr	x0, [x19, 2944]
	ldr	w4, [x0, 24]
	ldr	w3, [x0, 32]
	add	w1, w3, 8
	cmp	w1, w4, lsl 3
	bhi	.L2999
.L2992:
	mov	w1, 8
	bl	BsShow
	cmp	w0, 255
	mov	w1, 8
	ldr	x0, [x19, 2944]
	beq	.L2993
	bl	BsGet
	add	w4, w0, w21
	mov	x1, x22
	add	w3, w24, w20
	mov	x2, x23
	mov	x0, x19
	bl	HEVC_Sei_Payload
	mov	w1, 0
	cbnz	w0, .L3000
.L2990:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2998:
	ldr	x1, .LC630
	mov	w2, 5039
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2999:
	ldr	x1, .LC630
	mov	w2, 5060
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L3000:
	ldr	x1, .LC632
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	b	.L2990
	.size	HEVC_SeiMessage, .-HEVC_SeiMessage
	.align	3
.LC630:
	.xword	.LC629
	.align	3
.LC632:
	.xword	.LC631
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSEI
	.type	HEVC_DecSEI, %function
HEVC_DecSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L3007
	ldr	x21, [x19, 2976]
	add	x20, x19, 4096
	add	x20, x20, 136
	cbnz	x21, .L3010
	b	.L3013
	.p2align 3
.L3005:
	ldr	x0, [x19, 2944]
	bl	BsIsByteAligned
	cbz	w0, .L3014
	mov	x0, x19
	bl	HEVC_More_Rbsp_Data
	cbz	w0, .L3015
.L3010:
	mov	x2, x21
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_SeiMessage
	cbz	w0, .L3005
	ldr	x1, .LC636
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L3003:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3015:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	cmp	w0, 128
	bne	.L3016
.L3007:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3014:
	ldr	x1, .LC638
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L3016:
	ldr	x1, .LC640
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3003
.L3013:
	ldr	x1, .LC634
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3003
	.size	HEVC_DecSEI, .-HEVC_DecSEI
	.align	3
.LC634:
	.xword	.LC633
	.align	3
.LC636:
	.xword	.LC635
	.align	3
.LC638:
	.xword	.LC637
	.align	3
.LC640:
	.xword	.LC639
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_Sei_Scalable_Nesting
	.type	HEVC_Sei_Scalable_Nesting, %function
HEVC_Sei_Scalable_Nesting:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x2
	mov	x21, x1
	bl	_mcount
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3018
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	mov	w20, w0
	ldr	x1, .LC642
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	cmp	w0, 63
	mov	w23, w0
	bhi	.L3033
	and	w20, w20, 255
	cmp	w0, w20
	bcc	.L3024
	ldr	x24, .LC646
	.p2align 2
.L3023:
	ldr	x0, [x19, 2944]
	mov	w1, 3
	add	w20, w20, 1
	bl	BsGet
	ldr	x0, [x19, 2944]
	mov	x1, x24
	bl	HEVC_ue_v
	cmp	w23, w20
	bcs	.L3023
.L3024:
	ldr	x0, [x19, 2944]
	bl	BsToNextByte
.L3022:
	mov	x2, x22
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_SeiMessage
	cbnz	w0, .L3034
	ldr	x0, [x19, 2944]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L3028
	ldr	x1, [x19, 2984]
	ldr	w1, [x1, 12]
	add	w1, w1, 3
	cmp	w1, w0
	bcc	.L3022
.L3028:
	mov	w0, 0
.L3020:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3018:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L3024
	ldr	x0, [x19, 2944]
	mov	w1, 3
	mov	w20, 0
	bl	BsGet
	ldr	x1, .LC648
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	cmp	w0, 63
	add	w23, w0, 1
	bhi	.L3035
	.p2align 2
.L3029:
	ldr	x0, [x19, 2944]
	mov	w1, 6
	add	w20, w20, 1
	bl	BsGet
	cmp	w20, w23
	bne	.L3029
	b	.L3024
	.p2align 3
.L3034:
	ldr	x1, .LC651
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L3033:
	ldr	x1, .LC644
	mov	w2, 64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3020
.L3035:
	ldr	x1, .LC650
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3020
	.size	HEVC_Sei_Scalable_Nesting, .-HEVC_Sei_Scalable_Nesting
	.align	3
.LC642:
	.xword	.LC641
	.align	3
.LC644:
	.xword	.LC643
	.align	3
.LC646:
	.xword	.LC645
	.align	3
.LC648:
	.xword	.LC647
	.align	3
.LC650:
	.xword	.LC649
	.align	3
.LC651:
	.xword	.LC635
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecScalingListData
	.type	HEVC_DecScalingListData, %function
HEVC_DecScalingListData:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	str	x1, [x29, 112]
	bl	_mcount
	ldr	x0, .LC652
	ldr	x0, [x0]
	cbz	x0, .L3071
	ldr	x19, [x29, 112]
	mov	x2, 64
	str	x19, [x29, 128]
	add	x27, x20, 360
	add	x3, x19, 1536
	str	x3, [x29, 120]
	ldr	x3, .LC655
	add	x1, x19, 1216
	add	x0, x19, 1344
	mov	w25, 0
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x23, .LC667
	add	x0, x19, 1632
	str	x0, [x29, 96]
.L3039:
	ldr	w0, [x27, 1888]
	cbz	w0, .L3059
	uxtw	x0, w25
	mov	w24, 0
	ldp	x1, x21, [x29, 120]
	str	x1, [x29, 136]
	lsl	x1, x0, 2
	sub	x0, x1, x0
	lsl	x0, x0, 1
	str	x0, [x29, 104]
.L3058:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	mov	w19, 64
	bl	BsGet
	uxtb	w0, w0
	ldr	w1, [x27]
	cmp	w1, w19
	csel	w19, w1, w19, le
	cbz	w25, .L3072
	add	x22, x20, 376
	cbz	w0, .L3073
	cmp	w25, 1
	bls	.L3064
	ldr	x1, .LC663
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	add	w1, w0, 7
	cmp	w1, 254
	bhi	.L3074
	add	w26, w0, 8
	ldr	x0, [x29, 136]
	str	w26, [x0]
.L3042:
	cmp	w19, wzr
	mov	x28, 0
	bgt	.L3055
	b	.L3051
	.p2align 3
.L3054:
	ldr	w0, [x22, x28, lsl 2]
	add	w1, w1, w2
	and	w1, w1, 255
	add	x28, x28, 1
	sub	w26, w1, w2
	cmp	w19, w28
	strb	w26, [x21, x0]
	ble	.L3051
.L3055:
	ldr	x0, [x20, 2944]
	mov	x1, x23
	bl	HEVC_se_v
	add	w2, w0, w26
	add	w0, w0, 128
	add	w1, w2, 256
	cmp	w0, 255
	asr	w2, w1, 31
	lsr	w2, w2, 24
	bls	.L3054
	ldr	x1, .LC669
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L3069:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L3073:
	ldr	x1, .LC657
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, w24
	bhi	.L3061
	sub	w0, w24, w0
	cmp	w25, 1
	uxtb	w0, w0
	bls	.L3046
	cmp	w0, w24
	beq	.L3063
	ldp	x1, x2, [x29, 104]
	add	x1, x1, x0, uxtb
	add	x1, x1, 384
	ldr	w1, [x2, x1, lsl 2]
.L3047:
	ldr	x2, [x29, 136]
	str	w1, [x2]
.L3046:
	cmp	w0, w24
	beq	.L3075
	ldr	x1, [x29, 104]
	add	x0, x1, x0, uxtb
	ldr	x1, [x29, 112]
	add	x1, x1, x0, lsl 6
.L3049:
	cbz	x1, .L3076
	ldr	x0, .LC655
	sxtw	x2, w19
	ldr	x3, [x0, 104]
	mov	x0, x21
	blr	x3
.L3051:
	add	w24, w24, 1
	cmp	w24, 6
	beq	.L3059
	ldr	x0, [x29, 136]
	add	x21, x21, 64
	add	x0, x0, 4
	str	x0, [x29, 136]
	ldr	w0, [x27, 1888]
	cmp	w24, w0
	bcc	.L3058
	.p2align 2
.L3059:
	ldr	x0, [x29, 120]
	add	w25, w25, 1
	ldr	x1, [x29, 96]
	add	x27, x27, 4
	add	x0, x0, 24
	str	x0, [x29, 120]
	cmp	x0, x1
	ldr	x0, [x29, 128]
	add	x0, x0, 384
	str	x0, [x29, 128]
	bne	.L3039
	mov	w0, 0
	b	.L3069
	.p2align 3
.L3064:
	mov	w26, 8
	b	.L3042
.L3075:
	mov	w1, w24
	mov	w0, w25
	bl	HEVC_GetScalingListDefaultAddress
	mov	x1, x0
	b	.L3049
.L3063:
	mov	w1, 16
	b	.L3047
.L3074:
	ldr	x1, .LC665
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3069
.L3061:
	ldr	x1, .LC659
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3069
.L3076:
	ldr	x1, .LC661
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3069
.L3071:
	ldr	x2, .LC653
	ldr	x1, .LC654
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3069
.L3072:
	ldr	x1, .LC652
	ldr	x22, [x1]
	add	x22, x22, 65536
	cbnz	w0, .L3064
	ldr	x1, .LC657
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, w24
	bhi	.L3061
	sub	w0, w24, w0
	uxtb	w0, w0
	b	.L3046
	.size	HEVC_DecScalingListData, .-HEVC_DecScalingListData
	.align	3
.LC652:
	.xword	.LANCHOR1
	.align	3
.LC653:
	.xword	.LANCHOR3
	.align	3
.LC654:
	.xword	.LC166
	.align	3
.LC655:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC657:
	.xword	.LC656
	.align	3
.LC659:
	.xword	.LC658
	.align	3
.LC661:
	.xword	.LC660
	.align	3
.LC663:
	.xword	.LC662
	.align	3
.LC665:
	.xword	.LC664
	.align	3
.LC667:
	.xword	.LC666
	.align	3
.LC669:
	.xword	.LC668
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessSPS
	.type	HEVC_ProcessSPS, %function
HEVC_ProcessSPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldrb	w1, [x20, 1]
	cmp	w1, 1
	beq	.L3272
.L3078:
	ldr	x1, .LC777
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 1
	str	w0, [x19, 60]
	mov	w21, w0
	beq	.L3273
	cmp	w21, 3
	bhi	.L3274
	ldr	x1, .LC677
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L3257:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3274:
	ldr	x1, .LC675
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3272:
	ldr	x0, [x20, 2984]
	ldr	w0, [x0, 24]
	cbz	w0, .L3078
	ldrb	w0, [x19, 46]
	cmp	w0, 7
	bne	.L3078
	ldr	w2, [x19, 48]
	mov	w21, 24912
	ldr	x3, [x20, 2952]
	ldr	x0, [x20, 2944]
	umull	x2, w2, w21
	add	x21, x3, x2
	bl	BsGet
	cbnz	w0, .L3275
	ldr	x1, [x20, 2984]
	add	x0, x21, 12288
	add	x0, x0, 132
	ldr	w1, [x1, 24]
	add	x1, x1, 1036
	ldrsw	x1, [x0, x1, lsl 2]
	add	x0, x0, x1, lsl 2
	ldr	w0, [x0, 4152]
.L3080:
	cmp	w0, 1
	bhi	.L3276
	uxtw	x0, w0
	add	x21, x21, 12288
	lsl	x1, x0, 5
	add	x21, x21, 132
	add	x0, x1, x0, lsl 3
	add	x0, x21, x0
	add	x1, x0, 12288
	ldr	w2, [x0, 12420]
	str	w2, [x19, 60]
	ldrb	w1, [x1, 120]
	strb	w1, [x19, 47]
	ldr	w1, [x0, 12412]
	str	w1, [x19, 64]
	ldr	w1, [x0, 12416]
	str	w1, [x19, 68]
	ldr	w1, [x0, 12424]
	add	w1, w1, 8
	str	w1, [x19, 88]
	ldr	w2, [x0, 12428]
	add	w2, w2, 8
	str	w2, [x19, 96]
	ldr	w2, [x0, 12432]
	str	w2, [x19, 72]
	ldr	w2, [x0, 12436]
	str	w2, [x19, 76]
	ldr	w2, [x0, 12440]
	str	w2, [x19, 80]
	ldr	w0, [x0, 12444]
	str	w0, [x19, 84]
.L3083:
	str	w1, [x20, 196]
	ldr	x1, .LC711
	ldr	w0, [x19, 96]
	str	w0, [x20, 200]
	ldr	w4, [x19, 88]
	ldr	w3, [x19, 96]
	lsl	w2, w4, 2
	lsl	w0, w3, 2
	sub	w2, w2, w4
	sub	w0, w0, w3
	lsl	w2, w2, 1
	lsl	w0, w0, 1
	sub	w2, w2, #48
	sub	w0, w0, #48
	str	w2, [x19, 92]
	str	w0, [x19, 100]
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 12
	bhi	.L3277
	add	w0, w0, 4
	stp	w0, w0, [x19, 116]
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	beq	.L3278
.L3110:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	mov	w23, 0
	mov	w21, 0
	bl	BsGet
	ldr	x26, .LC715
	mov	w27, w0
	ldr	x25, .LC717
	ldr	x24, .LC719
	b	.L3118
	.p2align 3
.L3114:
	ldr	w0, [x19, 52]
	add	w21, w21, 1
	cmp	w0, w21
	bcc	.L3117
.L3118:
	add	x22, x19, x21, uxtw 2
	ldr	x0, [x20, 2944]
	mov	x1, x26
	bl	HEVC_ue_v
	add	w0, w0, 1
	str	w0, [x22, 328]
	mov	x1, x25
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x22, 360]
	mov	x1, x24
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x22, 392]
	ldr	w1, [x22, 328]
	cmp	w23, w1
	csel	w23, w23, w1, cs
	cbnz	w27, .L3114
	ldr	w2, [x19, 52]
	add	w21, w21, 1
	cmp	w21, w2
	bhi	.L3117
	.p2align 2
.L3225:
	add	x0, x19, x21, uxtw 2
	ldr	w1, [x19, 328]
	add	w21, w21, 1
	cmp	w21, w2
	str	w1, [x0, 328]
	ldr	w1, [x19, 360]
	str	w1, [x0, 360]
	ldr	w1, [x19, 392]
	str	w1, [x0, 392]
	bls	.L3225
.L3117:
	ldr	w0, [x19, 184]
	cmp	w0, w23
	csel	w23, w0, w23, ls
	str	w23, [x19, 184]
.L3113:
	ldr	x1, .LC721
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w22, w0
	bhi	.L3279
	ldr	x1, .LC725
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w21, w0
	bhi	.L3280
	add	w2, w22, 3
	add	w1, w0, w2
	sub	w0, w1, #4
	cmp	w0, 2
	stp	w2, w1, [x19, 124]
	bhi	.L3281
	ldp	w4, w0, [x19, 64]
	mov	w23, 1
	lsl	w1, w23, w1
	lsl	w2, w23, w2
	stp	w2, w1, [x19, 132]
	udiv	w3, w4, w1
	stp	w1, w1, [x19, 140]
	udiv	w2, w0, w1
	msub	w4, w3, w1, w4
	cmp	w4, wzr
	csinc	w3, w3, w3, eq
	str	w3, [x19, 188]
	msub	w0, w2, w1, w0
	ldr	x1, .LC731
	cmp	w0, wzr
	csinc	w2, w2, w2, eq
	str	w2, [x19, 192]
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 3
	mov	w22, w0
	bhi	.L3282
	ldr	x1, .LC735
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 3
	bhi	.L3283
	ldr	w2, [x19, 124]
	add	w1, w22, 2
	str	w1, [x19, 148]
	cmp	w1, w2
	bcs	.L3284
	add	w1, w0, w1
	str	w1, [x19, 152]
	cmp	w1, 5
	bhi	.L3129
	ldr	w0, [x19, 128]
	cmp	w1, w0
	bhi	.L3129
	ldr	x1, .LC743
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x19, 164]
	ldr	w1, [x19, 128]
	ldr	w2, [x19, 148]
	sub	w1, w1, w2
	cmp	w0, w1
	bhi	.L3285
	ldr	x1, .LC747
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x19, 168]
	ldr	w1, [x19, 128]
	ldr	w4, [x19, 148]
	sub	w1, w1, w4
	cmp	w0, w1
	bhi	.L3132
	ldr	w2, [x19, 140]
	mov	w3, 1
	lsl	w0, w3, w4
	mov	w1, 0
	lsr	w2, w2, w21
	cmp	w2, w0
	bls	.L3134
	.p2align 2
.L3224:
	add	w1, w1, 1
	add	w0, w4, w1
	lsl	w0, w3, w0
	cmp	w0, w2
	bcc	.L3224
.L3134:
	add	w1, w21, w1
	str	w1, [x19, 172]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 3]
	cbz	w0, .L3139
	ldrb	w1, [x20, 1]
	cmp	w1, 1
	beq	.L3286
.L3137:
	add	x0, x19, 12288
	strb	wzr, [x0, 372]
.L3169:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 4]
	cbnz	w0, .L3287
.L3139:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 6]
	cbnz	w0, .L3140
	ldr	w2, [x19, 68]
	cmp	w2, 64
	bls	.L3288
.L3140:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	str	w0, [x19, 104]
	cbz	w0, .L3141
	ldr	x0, [x20, 2944]
	mov	w1, 4
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x19, 108]
	mov	w1, 4
	ldr	x0, [x20, 2944]
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x19, 112]
	ldr	x1, .LC755
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 2
	mov	w21, w0
	bhi	.L3289
.L3142:
	ldr	x1, .LC759
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 2
	mov	w22, w0
	bhi	.L3290
.L3143:
	add	w0, w21, 3
	str	w0, [x19, 156]
	add	w0, w22, w0
	str	w0, [x19, 160]
	cmp	w0, 5
	bhi	.L3144
	ldr	w1, [x19, 128]
	cmp	w0, w1
	bhi	.L3144
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 7]
.L3141:
	ldr	x1, .LC765
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 64
	str	w0, [x19, 176]
	bhi	.L3146
	mov	w21, 0
	cbnz	w0, .L3223
	b	.L3152
	.p2align 3
.L3150:
	ldr	w0, [x19, 176]
	cmp	w0, w21
	bls	.L3152
.L3223:
	uxtw	x5, w21
	mov	w3, w21
	lsl	x2, x5, 2
	mov	x1, x19
	sub	x2, x2, x5
	mov	x0, x20
	lsl	x4, x2, 3
	add	w21, w21, 1
	sub	x2, x4, x2
	lsl	x2, x2, 1
	sub	x2, x2, x5
	add	x2, x19, x2, lsl 2
	add	x2, x2, 2164
	bl	HEVC_DecShortTermRefPicSet
	cbz	w0, .L3150
	ldr	x1, .LC769
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
	.p2align 3
.L3273:
	ldr	x1, .LC679
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 8192
	str	w0, [x19, 64]
	bls	.L3085
	ldr	x1, .LC681
.L3264:
	mov	w0, w21
	bl	dprint_vfmw
	ldr	x0, .LC682
	ldr	x4, [x0]
	cbz	x4, .L3261
.L3263:
	ldr	w0, [x20, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3085:
	ldr	x1, .LC684
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 4096
	str	w0, [x19, 68]
	bhi	.L3291
	ldr	w2, [x19, 428]
	ldr	w1, [x19, 64]
	cmp	w2, 120
	mul	w0, w0, w1
	beq	.L3090
	bgt	.L3091
	cmp	w2, 60
	beq	.L3171
	ble	.L3292
	cmp	w2, 90
	beq	.L3095
	cmp	w2, 93
	beq	.L3096
	cmp	w2, 63
	beq	.L3293
.L3089:
	ldr	x1, .LC688
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
	.p2align 3
.L3278:
	ldr	x0, [x20, 2984]
	ldr	w0, [x0, 24]
	cbz	w0, .L3110
	ldrb	w0, [x19, 46]
	cmp	w0, 7
	bne	.L3110
	ldp	w0, w7, [x19, 48]
	mov	w6, 24912
	ldr	x8, [x20, 2952]
	mov	w4, 0
	mov	w2, 0
	umull	x6, w0, w6
	.p2align 2
.L3112:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x0, x6
	add	x0, x19, x0
	add	x1, x8, x1
	ldr	w3, [x1, 28]
	str	w3, [x0, 328]
	cmp	w4, w3
	ldr	w5, [x1, 60]
	csel	w4, w4, w3, cs
	str	w5, [x0, 360]
	cmp	w2, w7
	ldr	w1, [x1, 92]
	str	w1, [x0, 392]
	bls	.L3112
	str	w4, [x19, 184]
	b	.L3113
	.p2align 3
.L3152:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 8]
	cbz	w0, .L3149
	ldr	x1, .LC771
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 32
	str	w0, [x19, 180]
	bhi	.L3155
	mov	w22, 0
	cbz	w0, .L3149
	.p2align 2
.L3222:
	ldr	w1, [x19, 116]
	uxtw	x21, w22
	ldr	x0, [x20, 2944]
	add	w22, w22, 1
	bl	BsGet
	add	x2, x19, x21, lsl 2
	add	x21, x19, x21
	mov	w1, 1
	str	w0, [x2, 196]
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x21, 13]
	ldr	w0, [x19, 180]
	cmp	w0, w22
	bhi	.L3222
.L3149:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 10]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	mov	w1, 2
	strb	w0, [x19, 11]
	str	w1, [x19, 2096]
	cbz	w0, .L3154
	mov	x2, x19
	add	x1, x19, 2064
	mov	x0, x20
	bl	HEVC_DecVuiParam
	cbz	w0, .L3154
	ldr	x1, .LC775
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L3261:
	mov	w0, -1
	b	.L3257
	.p2align 3
.L3154:
	ldrb	w5, [x19, 2067]
	ldp	w3, w4, [x19, 64]
	ldr	w0, [x19, 2072]
	ldr	w1, [x19, 2076]
	ldr	w2, [x19, 2080]
	madd	w4, w5, w4, w4
	bl	HEVC_GetDar
	str	w0, [x19, 2068]
	ldrb	w21, [x20, 1]
	cmp	w21, 1
	beq	.L3294
	mov	w1, 1
	mov	w0, 0
	strb	w1, [x19]
	b	.L3257
	.p2align 3
.L3275:
	ldr	x0, [x20, 2944]
	mov	w1, 8
	bl	BsGet
	b	.L3080
	.p2align 3
.L3091:
	cmp	w2, 156
	beq	.L3098
	bgt	.L3099
	cmp	w2, 150
	beq	.L3098
	cmp	w2, 153
	beq	.L3098
	cmp	w2, 123
	bne	.L3089
.L3090:
	mov	w2, 32768
	mov	w1, 2228224
	movk	w2, 0x8, lsl 16
	.p2align 2
.L3092:
	cmp	w0, w2
	bhi	.L3101
	mov	w0, 16
	str	w0, [x19, 184]
.L3102:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	cbz	w0, .L3105
	ldr	x1, .LC690
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	x21, .LC691
	ldr	w2, [x19, 60]
	add	x22, x21, 104
	ldr	x1, .LC693
	ldr	w2, [x22, x2, lsl 2]
	mul	w0, w2, w0
	str	w0, [x19, 72]
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldp	w2, w1, [x19, 60]
	ldr	w3, [x19, 72]
	ldr	w2, [x22, x2, lsl 2]
	sub	w1, w1, w3
	mul	w0, w0, w2
	str	w0, [x19, 76]
	sub	w1, w1, w0
	tbnz	w1, #31, .L3295
	ldr	x1, .LC697
	add	x21, x21, 120
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	w2, [x19, 60]
	ldr	x1, .LC699
	ldr	w2, [x21, x2, lsl 2]
	mul	w0, w2, w0
	str	w0, [x19, 80]
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	w2, [x19, 60]
	ldr	w1, [x19, 68]
	ldr	w3, [x19, 80]
	ldr	w2, [x21, x2, lsl 2]
	sub	w1, w1, w3
	mul	w0, w0, w2
	str	w0, [x19, 84]
	sub	w1, w1, w0
	tbnz	w1, #31, .L3296
.L3105:
	ldr	x1, .LC703
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	add	w2, w0, 8
	cmp	w0, 2
	str	w2, [x19, 88]
	bhi	.L3297
	ldr	x1, .LC707
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	add	w2, w0, 8
	cmp	w0, 6
	str	w2, [x19, 96]
	bhi	.L3298
	ldr	w1, [x19, 88]
	b	.L3083
	.p2align 3
.L3288:
	ldr	x1, .LC753
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC682
	ldr	x4, [x0]
	cbnz	x4, .L3263
	mov	w0, -1
	b	.L3257
	.p2align 3
.L3286:
	ldr	x0, [x20, 2984]
	ldr	w0, [x0, 24]
	cbz	w0, .L3137
	ldrb	w0, [x19, 46]
	cmp	w0, 7
	bne	.L3137
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	add	x1, x19, 12288
	strb	w0, [x1, 372]
	cbz	w0, .L3169
	ldr	x0, [x20, 2944]
	mov	w1, 6
	bl	BsGet
	strb	wzr, [x19, 4]
	str	w0, [x19, 12664]
	b	.L3139
	.p2align 3
.L3101:
	cmp	w0, w1, lsr 1
	bhi	.L3103
	mov	w0, 12
	str	w0, [x19, 184]
	b	.L3102
	.p2align 3
.L3129:
	ldr	x1, .LC741
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
	.p2align 3
.L3291:
	ldr	x1, .LC686
	b	.L3264
	.p2align 3
.L3290:
	ldr	x1, .LC761
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3143
	.p2align 3
.L3289:
	ldr	x1, .LC757
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3142
	.p2align 3
.L3287:
	add	x1, x19, 432
	mov	x0, x20
	bl	HEVC_DecScalingListData
	cbz	w0, .L3139
	ldr	x1, .LC751
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
	.p2align 3
.L3297:
	ldr	x1, .LC705
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC682
	ldr	x4, [x0]
	cbz	x4, .L3261
	ldr	w1, [x19, 88]
	mov	w3, 8
	ldr	w0, [x20, 276]
	add	x2, x29, 104
	stp	wzr, w1, [x29, 104]
	mov	w1, 119
	blr	x4
	mov	w0, -1
	b	.L3257
.L3103:
	lsl	w2, w1, 2
	sub	w1, w2, w1
	cmp	w0, w1, lsr 2
	bhi	.L3104
	mov	w0, 8
	str	w0, [x19, 184]
	b	.L3102
.L3279:
	ldr	x1, .LC723
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3276:
	mov	w2, 1
	ldr	x1, .LC671
	mov	w0, w2
	bl	dprint_vfmw
	ldr	x1, .LC673
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3282:
	ldr	x1, .LC733
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3099:
	cmp	w2, 183
	beq	.L3100
	cmp	w2, 186
	beq	.L3100
	cmp	w2, 180
	bne	.L3089
.L3100:
	mov	w2, 8912896
	mov	w1, 35651584
	b	.L3092
.L3292:
	cbz	w2, .L3094
	cmp	w2, 30
	bne	.L3089
.L3094:
	mov	w2, 9216
	mov	w1, 36864
	b	.L3092
.L3144:
	ldr	x1, .LC763
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3285:
	ldr	x1, .LC745
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3294:
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L3159
.L3162:
	mov	w0, 0
	b	.L3257
.L3159:
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	uxtb	w19, w0
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	uxtb	w23, w0
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 5
	bl	BsGet
	uxtb	w22, w0
	cbnz	w19, .L3299
	cbnz	w23, .L3300
.L3161:
	cbnz	w22, .L3260
	b	.L3162
	.p2align 3
.L3163:
	ldr	x0, [x20, 2944]
	bl	BsGet
.L3260:
	ldr	x0, [x20, 2944]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L3162
	ldr	x2, [x20, 2984]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcc	.L3163
	mov	w0, 0
	b	.L3257
.L3300:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	b	.L3161
.L3299:
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	cbz	w23, .L3161
	b	.L3300
	.p2align 3
.L3293:
	mov	w2, 61440
	mov	w1, 245760
	b	.L3092
.L3098:
	mov	w2, 2228224
	mov	w1, 8912896
	b	.L3092
.L3171:
	mov	w2, 30720
	mov	w1, 122880
	b	.L3092
.L3096:
	mov	w2, 245760
	mov	w1, 983040
	b	.L3092
.L3095:
	mov	w2, 7168
	mov	w1, 28672
	movk	w2, 0x2, lsl 16
	movk	w1, 0x8, lsl 16
	b	.L3092
.L3104:
	mov	w0, 6
	str	w0, [x19, 184]
	b	.L3102
.L3277:
	ldr	x1, .LC713
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3281:
	ldr	x1, .LC729
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3280:
	ldr	x1, .LC727
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3283:
	ldr	x1, .LC737
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3284:
	ldr	x1, .LC739
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3132:
	ldr	x1, .LC749
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3146:
	ldr	x1, .LC767
	mov	w2, 64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3155:
	ldr	x1, .LC773
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3298:
	ldr	x1, .LC709
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3295:
	ldr	x1, .LC695
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
.L3296:
	ldr	x1, .LC701
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3257
	.size	HEVC_ProcessSPS, .-HEVC_ProcessSPS
	.align	3
.LC671:
	.xword	.LC670
	.align	3
.LC673:
	.xword	.LC672
	.align	3
.LC675:
	.xword	.LC674
	.align	3
.LC677:
	.xword	.LC676
	.align	3
.LC679:
	.xword	.LC678
	.align	3
.LC681:
	.xword	.LC680
	.align	3
.LC682:
	.xword	g_event_report
	.align	3
.LC684:
	.xword	.LC683
	.align	3
.LC686:
	.xword	.LC685
	.align	3
.LC688:
	.xword	.LC687
	.align	3
.LC690:
	.xword	.LC689
	.align	3
.LC691:
	.xword	.LANCHOR3
	.align	3
.LC693:
	.xword	.LC692
	.align	3
.LC695:
	.xword	.LC694
	.align	3
.LC697:
	.xword	.LC696
	.align	3
.LC699:
	.xword	.LC698
	.align	3
.LC701:
	.xword	.LC700
	.align	3
.LC703:
	.xword	.LC702
	.align	3
.LC705:
	.xword	.LC704
	.align	3
.LC707:
	.xword	.LC706
	.align	3
.LC709:
	.xword	.LC708
	.align	3
.LC711:
	.xword	.LC710
	.align	3
.LC713:
	.xword	.LC712
	.align	3
.LC715:
	.xword	.LC714
	.align	3
.LC717:
	.xword	.LC716
	.align	3
.LC719:
	.xword	.LC718
	.align	3
.LC721:
	.xword	.LC720
	.align	3
.LC723:
	.xword	.LC722
	.align	3
.LC725:
	.xword	.LC724
	.align	3
.LC727:
	.xword	.LC726
	.align	3
.LC729:
	.xword	.LC728
	.align	3
.LC731:
	.xword	.LC730
	.align	3
.LC733:
	.xword	.LC732
	.align	3
.LC735:
	.xword	.LC734
	.align	3
.LC737:
	.xword	.LC736
	.align	3
.LC739:
	.xword	.LC738
	.align	3
.LC741:
	.xword	.LC740
	.align	3
.LC743:
	.xword	.LC742
	.align	3
.LC745:
	.xword	.LC744
	.align	3
.LC747:
	.xword	.LC746
	.align	3
.LC749:
	.xword	.LC748
	.align	3
.LC751:
	.xword	.LC750
	.align	3
.LC753:
	.xword	.LC752
	.align	3
.LC755:
	.xword	.LC754
	.align	3
.LC757:
	.xword	.LC756
	.align	3
.LC759:
	.xword	.LC758
	.align	3
.LC761:
	.xword	.LC760
	.align	3
.LC763:
	.xword	.LC762
	.align	3
.LC765:
	.xword	.LC764
	.align	3
.LC767:
	.xword	.LC766
	.align	3
.LC769:
	.xword	.LC768
	.align	3
.LC771:
	.xword	.LC770
	.align	3
.LC773:
	.xword	.LC772
	.align	3
.LC775:
	.xword	.LC774
	.align	3
.LC777:
	.xword	.LC776
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSPS
	.type	HEVC_DecSPS, %function
HEVC_DecSPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC780
	ldr	x0, [x21]
	cbz	x0, .L3324
	ldr	x24, .LC783
	mov	x2, 8
	mov	w1, 0
	add	x0, x29, 96
	ldr	x3, [x24, 96]
	blr	x3
	ldr	x0, [x19, 2944]
	mov	w1, 4
	bl	BsGet
	mov	w25, w0
	ldr	w2, [x19, 156]
	cmp	w2, w0
	bls	.L3325
	ldr	x0, [x19, 2984]
	ldr	w0, [x0, 24]
	cbz	w0, .L3326
	ldr	x0, [x19, 2944]
	mov	w1, 3
	bl	BsGet
	uxtb	w26, w0
	cmp	w26, 7
	beq	.L3307
	and	w22, w0, 255
.L3308:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w27, w0
	mov	w3, w22
	mov	w2, 1
	add	x1, x29, 96
	mov	x0, x19
	bl	HEVC_DecPTL
	cbnz	w0, .L3327
.L3309:
	ldr	x1, .LC791
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	mov	w23, w0
	ldr	w2, [x19, 160]
	cmp	w0, w2
	bcs	.L3328
	mov	w20, 12668
	umull	x20, w0, w20
	ldr	x0, [x19, 2960]
	add	x0, x0, x20
	ldrb	w1, [x0, 1]
	cbz	w1, .L3311
	ldr	x21, [x21]
	mov	x2, 12668
	ldr	x3, [x24, 96]
	mov	w1, 0
	add	x21, x21, 458752
	mov	x0, x21
	blr	x3
	strb	w27, [x21, 2]
	ldr	x3, [x24, 104]
	add	x1, x29, 96
	mov	x2, 8
	strb	w26, [x21, 46]
	stp	w25, w22, [x21, 48]
	add	x0, x21, 424
	blr	x3
	str	w23, [x21, 56]
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_ProcessSPS
	mov	w22, w0
	cbnz	w0, .L3329
	mov	w0, 1
	strb	w0, [x21]
	strb	w0, [x21, 1]
	mov	x2, 12668
	ldr	x3, [x24, 112]
	mov	x1, x21
	ldr	x0, [x19, 2960]
	add	x0, x0, x20
	blr	x3
	ldr	x0, [x19, 2960]
	add	x20, x0, x20
	str	x20, [x19, 2976]
.L3323:
	mov	w0, w22
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3326:
	ldr	x0, [x19, 2944]
	mov	w1, 3
	mov	w26, 0
	bl	BsGet
	cmp	w0, 8
	mov	w22, w0
	bls	.L3308
	ldr	x1, .LC787
	mov	w2, 8
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L3323
	.p2align 3
.L3311:
	str	w25, [x0, 48]
	mov	x2, 8
	add	x1, x29, 96
	ldr	x0, [x19, 2960]
	add	x0, x0, x20
	str	w22, [x0, 52]
	ldr	x0, [x19, 2960]
	add	x0, x0, x20
	strb	w27, [x0, 2]
	ldr	x0, [x19, 2960]
	add	x0, x0, x20
	strb	w26, [x0, 46]
	ldr	x0, [x19, 2960]
	ldr	x3, [x24, 104]
	add	x0, x0, x20
	add	x0, x0, 424
	blr	x3
	ldr	x1, [x19, 2960]
	mov	x0, x19
	add	x1, x1, x20
	str	w23, [x1, 56]
	ldr	x1, [x19, 2960]
	add	x1, x1, x20
	bl	HEVC_ProcessSPS
	mov	w22, w0
	cbnz	w0, .L3330
	ldr	x0, [x19, 2960]
	mov	w1, 1
	strb	w1, [x0, x20]
	ldr	x0, [x19, 2960]
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2960]
	add	x20, x0, x20
	str	x20, [x19, 2976]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3328:
	ldr	x1, .LC793
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 160]
	cmp	w23, w1
	bcc	.L3318
	ldr	x0, .LC794
	ldr	x4, [x0]
	cbz	x4, .L3318
	ldr	w0, [x19, 276]
	add	x2, x29, 104
	stp	w23, w1, [x29, 104]
	mov	w3, 8
	mov	w1, 109
	mov	w22, -1
	blr	x4
	ldr	x27, [sp, 80]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3318:
	mov	w22, -1
	b	.L3323
	.p2align 3
.L3307:
	ldr	x0, [x19, 2984]
	ldr	w0, [x0, 24]
	cbz	w0, .L3315
	mov	w0, 24912
	ldr	x1, [x19, 2952]
	mov	w27, 1
	umull	x0, w25, w0
	add	x0, x1, x0
	ldr	w22, [x0, 12]
	cbz	w22, .L3309
	ldrb	w27, [x0, 1]
	b	.L3309
	.p2align 3
.L3325:
	ldr	x1, .LC785
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L3323
	.p2align 3
.L3329:
	ldr	x3, [x19, 2960]
	mov	w2, w23
	ldr	x1, .LC796
	mov	w0, 1
	add	x20, x3, x20
	str	x20, [x19, 2976]
	mov	w22, -1
	bl	dprint_vfmw
	b	.L3323
	.p2align 3
.L3327:
	ldr	x1, .LC789
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L3323
.L3324:
	ldr	x2, .LC781
	mov	w22, -1
	ldr	x1, .LC782
	add	x2, x2, 136
	bl	dprint_vfmw
	b	.L3323
.L3330:
	ldr	x1, .LC798
	mov	w2, w23
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x0, [x19, 2960]
	mov	w1, 1
	strb	w1, [x0, x20]
	ldr	x0, [x19, 2960]
	add	x20, x0, x20
	strb	wzr, [x20, 1]
	b	.L3323
.L3315:
	mov	w22, 0
	b	.L3308
	.size	HEVC_DecSPS, .-HEVC_DecSPS
	.align	3
.LC780:
	.xword	.LANCHOR1
	.align	3
.LC781:
	.xword	.LANCHOR3
	.align	3
.LC782:
	.xword	.LC166
	.align	3
.LC783:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC785:
	.xword	.LC784
	.align	3
.LC787:
	.xword	.LC786
	.align	3
.LC789:
	.xword	.LC788
	.align	3
.LC791:
	.xword	.LC790
	.align	3
.LC793:
	.xword	.LC792
	.align	3
.LC794:
	.xword	g_event_report
	.align	3
.LC796:
	.xword	.LC795
	.align	3
.LC798:
	.xword	.LC797
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ProcessPPS
	.type	HEVC_ProcessPPS, %function
HEVC_ProcessPPS:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	w22, 1
	bl	_mcount
	mov	w0, 1
	strb	w0, [x19, 16]
	stp	w22, w22, [x19, 68]
	ldr	x1, .LC800
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x19, 32]
	tbnz	w0, #31, .L3332
	ldr	w1, [x20, 160]
	cmp	w0, w1
	bge	.L3332
	ldr	x1, [x20, 2960]
	mov	w21, 12668
	smaddl	x21, w0, w21, x1
	ldrb	w1, [x21, 1]
	cbz	w1, .L3479
	ldr	x0, [x20, 2944]
	mov	w1, w22
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, w22
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 3
	ldr	x0, [x20, 2944]
	bl	BsGet
	str	w0, [x19, 36]
	mov	w1, w22
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 3]
	mov	w1, w22
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 5]
	ldr	x1, .LC806
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	add	w0, w0, 1
	cmp	w0, 15
	str	w0, [x19, 40]
	bhi	.L3480
	ldr	x1, .LC810
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	add	w0, w0, 1
	cmp	w0, 15
	str	w0, [x19, 44]
	bhi	.L3481
	ldr	x1, .LC814
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	add	w2, w0, 26
	str	w2, [x19, 48]
	mov	w0, 51
	ldr	w3, [x21, 92]
	neg	w1, w3
	cmp	w2, w1
	ccmp	w2, w0, 0, ge
	bgt	.L3482
	ldr	x0, [x20, 2944]
	mov	w1, w22
	bl	BsGet
	strb	w0, [x19, 6]
	mov	w1, w22
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 7]
	mov	w1, w22
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 8]
	cbnz	w0, .L3483
	mov	w0, 0
	str	wzr, [x19, 52]
.L3341:
	str	w0, [x19, 56]
	ldr	x1, .LC822
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x19, 60]
	bhi	.L3484
	ldr	x1, .LC826
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x19, 64]
	bhi	.L3485
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 10]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 11]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 12]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 13]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 14]
	ldrb	w1, [x19, 13]
	cbnz	w1, .L3486
	ldr	w0, [x21, 188]
	strh	w0, [x19, 172]
	ldr	w0, [x21, 192]
	strh	w0, [x19, 212]
.L3378:
	ldr	w3, [x19, 68]
	cmp	w3, wzr
	ble	.L3383
.L3377:
	ldr	w4, [x21, 140]
	add	x0, x19, 172
	mov	w1, 0
	.p2align 2
.L3382:
	ldrsh	w2, [x0]
	add	w1, w1, 1
	add	x0, x0, 2
	mul	w2, w2, w4
	cmp	w2, 64
	bhi	.L3381
	ldr	w5, [x21, 64]
	cmp	w5, 64
	bhi	.L3487
.L3381:
	cmp	w1, w3
	blt	.L3382
.L3383:
	ldr	w1, [x19, 72]
	cmp	w1, wzr
	ble	.L3380
	ldrsh	w2, [x19, 212]
	ldr	w3, [x21, 140]
	mul	w2, w2, w3
	cmp	w2, 63
	bls	.L3384
	sub	w1, w1, #1
	mov	x0, x19
	add	x1, x19, x1, lsl 1
	b	.L3386
	.p2align 3
.L3387:
	ldrsh	w2, [x0, 214]
	add	x0, x0, 2
	mul	w2, w2, w3
	cmp	w2, 63
	bls	.L3384
.L3386:
	cmp	x1, x0
	bne	.L3387
.L3380:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 17]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 18]
	cbnz	w0, .L3488
.L3389:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 21]
	cbz	w0, .L3392
	add	x1, x19, 256
	mov	x0, x20
	bl	HEVC_DecScalingListData
	cbnz	w0, .L3489
.L3392:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 22]
	ldr	x1, .LC869
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	add	w2, w0, 2
	cmp	w2, 1
	str	w2, [x19, 84]
	ble	.L3393
	ldr	w0, [x21, 128]
	cmp	w2, w0
	bhi	.L3393
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 23]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 24]
	cbnz	w0, .L3395
.L3418:
	mov	w0, 0
.L3503:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3483:
	ldr	x1, .LC818
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 3
	str	w0, [x19, 52]
	bls	.L3341
	ldr	x1, .LC820
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
	.p2align 3
.L3486:
	ldr	x1, .LC830
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w0, 19
	str	w2, [x19, 68]
	bhi	.L3490
	ldr	x1, .LC834
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	add	w2, w0, 1
	cmp	w0, 21
	str	w2, [x19, 72]
	bhi	.L3491
	ldr	w3, [x19, 68]
	cmp	w3, 10
	bgt	.L3492
	cmp	w2, 11
	ble	.L3349
	ldr	x1, .LC841
	mov	w3, w2
	mov	w2, 11
.L3476:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC839
	ldr	x4, [x0]
	cbz	x4, .L3470
.L3473:
	ldr	w0, [x20, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L3465:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3395:
	ldrb	w21, [x20, 1]
	cmp	w21, 1
	bne	.L3418
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	uxtb	w22, w0
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	uxtb	w25, w0
	ldr	x0, [x20, 2944]
	mov	w1, w21
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 5
	bl	BsGet
	uxtb	w0, w0
	str	w0, [x29, 108]
	cbz	w22, .L3397
	ldrb	w0, [x19, 7]
	cbnz	w0, .L3493
.L3398:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3402
	ldr	x1, .LC879
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC881
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 5
	bgt	.L3400
	tbnz	w0, #31, .L3402
	ldr	x24, .LC885
	add	w22, w0, 1
	ldr	x23, .LC887
	mov	w21, 0
	.p2align 2
.L3404:
	ldr	x0, [x20, 2944]
	mov	x1, x24
	add	w21, w21, 1
	bl	HEVC_se_v
	ldr	x0, [x20, 2944]
	mov	x1, x23
	bl	HEVC_se_v
	cmp	w21, w22
	bne	.L3404
.L3402:
	ldr	x1, .LC875
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	ldr	x1, .LC877
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
.L3397:
	cbz	w25, .L3396
	ldr	x0, [x20, 2944]
	mov	w1, 1
	add	x21, x19, 1888
	bl	BsGet
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x21, 1]
	cbnz	w0, .L3494
	str	wzr, [x21, 68]
.L3406:
	ldr	x1, .LC891
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	cmp	w0, 63
	bhi	.L3495
	str	wzr, [x21, 72]
	mov	w1, 8
	str	wzr, [x21, 328]
	str	wzr, [x21, 584]
	str	wzr, [x21, 840]
	str	wzr, [x21, 1096]
	str	wzr, [x21, 1352]
	str	wzr, [x21, 1608]
	str	wzr, [x21, 1864]
	str	wzr, [x21, 2120]
	str	wzr, [x19, 4264]
	str	w1, [x19, 4520]
	str	w1, [x19, 4776]
	cbz	w0, .L3417
	sub	w23, w0, #1
	ldr	x28, .LC897
	add	x23, x23, 1891
	ldr	x27, .LC899
	ldr	x26, .LC901
	add	x22, x19, 1890
	ldr	x25, .LC903
	add	x23, x19, x23
	b	.L3416
	.p2align 3
.L3410:
	add	x0, x19, x21, lsl 2
	str	wzr, [x0, 1960]
	str	wzr, [x0, 2216]
	str	wzr, [x0, 2472]
	str	wzr, [x0, 2728]
.L3411:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbnz	w0, .L3496
	add	x0, x19, x21, lsl 2
	str	wzr, [x0, 2984]
	str	wzr, [x0, 3240]
	str	wzr, [x0, 3496]
	str	wzr, [x0, 3752]
.L3413:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	add	x21, x19, x21, lsl 2
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x22]
	cbnz	w0, .L3497
	mov	w0, 8
	str	wzr, [x21, 4008]
	str	wzr, [x21, 4264]
	str	w0, [x21, 4520]
	str	w0, [x21, 4776]
.L3415:
	add	x22, x22, 1
	cmp	x23, x22
	beq	.L3417
.L3416:
	ldr	x0, [x20, 2944]
	mov	w1, 6
	bl	BsGet
	sxtw	x21, w0
	cmp	w21, 63
	bgt	.L3498
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3410
	add	x24, x19, x21, lsl 2
	ldr	x0, [x20, 2944]
	mov	x1, x28
	bl	HEVC_se_v
	str	w0, [x24, 1960]
	mov	x1, x27
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	str	w0, [x24, 2216]
	mov	x1, x26
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	str	w0, [x24, 2472]
	mov	x1, x25
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	str	w0, [x24, 2728]
	b	.L3411
	.p2align 3
.L3384:
	ldr	x1, .LC857
.L3475:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC839
	ldr	x4, [x0]
	cbnz	x4, .L3473
.L3470:
	mov	w0, -1
.L3504:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3487:
	ldr	x1, .LC855
	b	.L3475
	.p2align 3
.L3482:
	ldr	x1, .LC816
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3349:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 15]
	cbnz	w0, .L3499
	ldr	w0, [x19, 68]
	sub	w1, w0, #1
	cmp	w1, wzr
	ble	.L3354
	ldr	x23, .LC843
	mov	w22, 0
	b	.L3358
	.p2align 3
.L3501:
	cmp	w3, w4
	bhi	.L3356
	ldr	w0, [x19, 68]
	add	w22, w22, 1
	sub	w1, w0, #1
	cmp	w1, w22
	ble	.L3500
.L3358:
	ldr	x0, [x20, 2944]
	mov	x1, x23
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x1, x19, x22, sxtw 1
	sxth	w3, w0
	strh	w3, [x1, 88]
	ldr	w4, [x21, 188]
	tbz	w3, #31, .L3501
.L3356:
	ldr	x1, .LC845
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3492:
	ldr	x1, .LC838
	mov	w2, 10
	b	.L3476
.L3488:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 19]
	mov	w1, 1
	ldr	x0, [x20, 2944]
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 20]
	cbnz	w0, .L3389
	ldr	x1, .LC859
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 76]
	bhi	.L3502
.L3391:
	ldr	x1, .LC863
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 80]
	bls	.L3389
	ldr	x1, .LC865
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 80]
	b	.L3389
.L3499:
	ldr	w0, [x19, 68]
.L3360:
	cmp	w0, wzr
	add	x5, x19, 172
	mov	w3, 0
	ble	.L3353
	.p2align 2
.L3444:
	add	w3, w3, 1
	ldr	w4, [x21, 188]
	sub	w2, w3, #1
	cmp	w3, w0
	mul	w1, w3, w4
	mul	w2, w2, w4
	udiv	w1, w1, w0
	udiv	w2, w2, w0
	sub	w1, w1, w2
	strh	w1, [x5], 2
	bne	.L3444
.L3353:
	ldr	w4, [x19, 72]
	add	x6, x19, 212
	mov	w3, 0
	cmp	w4, wzr
	ble	.L3368
	.p2align 2
.L3443:
	add	w3, w3, 1
	ldr	w5, [x21, 192]
	sub	w2, w3, #1
	cmp	w3, w4
	mul	w1, w3, w5
	mul	w2, w2, w5
	udiv	w1, w1, w4
	udiv	w2, w2, w4
	sub	w1, w1, w2
	strh	w1, [x6], 2
	bne	.L3443
.L3368:
	cmp	w0, 1
	bne	.L3376
	ldr	w3, [x19, 72]
	cmp	w3, 1
	beq	.L3377
.L3376:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x19, 16]
	b	.L3378
.L3417:
	ldr	x0, [x20, 2944]
	mov	w1, 1
	bl	BsGet
.L3396:
	ldr	w0, [x29, 108]
	cbnz	w0, .L3469
	b	.L3418
	.p2align 3
.L3419:
	ldr	x0, [x20, 2944]
	bl	BsGet
	strb	w0, [x19, 25]
.L3469:
	ldr	x0, [x20, 2944]
	bl	BsResidBits
	cmp	w0, wzr
	ble	.L3418
	ldr	x2, [x20, 2984]
	mov	w1, 1
	ldr	w2, [x2, 12]
	add	w2, w2, 3
	cmp	w2, w0
	bcc	.L3419
	mov	w0, 0
	b	.L3503
.L3497:
	ldr	x1, .LC913
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x21, 4008]
	ldr	x1, .LC915
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x21, 4264]
	ldr	x1, .LC917
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x21, 4520]
	ldr	x1, .LC919
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	str	w0, [x21, 4776]
	b	.L3415
.L3496:
	add	x24, x19, x21, lsl 2
	ldr	x1, .LC905
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	str	w0, [x24, 2984]
	ldr	x1, .LC907
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	str	w0, [x24, 3240]
	ldr	x1, .LC909
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	str	w0, [x24, 3496]
	ldr	x1, .LC911
	ldr	x0, [x20, 2944]
	bl	HEVC_se_v
	str	w0, [x24, 3752]
	b	.L3413
.L3332:
	ldr	x1, .LC802
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3479:
	ldr	x1, .LC804
	mov	w2, w0
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3480:
	ldr	x1, .LC808
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3481:
	ldr	x1, .LC812
	mov	w0, w22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3484:
	ldr	x1, .LC824
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3485:
	ldr	x1, .LC828
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3393:
	ldr	x1, .LC871
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3504
.L3500:
	ldr	w1, [x19, 72]
	sub	w1, w1, #1
	cmp	w1, wzr
	ble	.L3366
.L3359:
	ldr	x23, .LC847
	mov	w22, 0
	b	.L3365
	.p2align 3
.L3506:
	cmp	w3, w4
	bhi	.L3363
	ldr	w0, [x19, 72]
	add	w22, w22, 1
	sub	w0, w0, #1
	cmp	w0, w22
	ble	.L3505
.L3365:
	ldr	x0, [x20, 2944]
	mov	x1, x23
	bl	HEVC_ue_v
	add	w0, w0, 1
	add	x1, x19, x22, sxtw 1
	sxth	w3, w0
	strh	w3, [x1, 128]
	ldr	w4, [x21, 192]
	tbz	w3, #31, .L3506
.L3363:
	ldr	x1, .LC849
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3493:
	ldr	x1, .LC873
	ldr	x0, [x20, 2944]
	bl	HEVC_ue_v
	b	.L3398
.L3498:
	ldr	x1, .LC895
	mov	w3, 64
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
.L3403:
	ldr	x1, .LC921
	mov	w0, 1
	ldr	w2, [x19, 84]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3490:
	ldr	x1, .LC832
	mov	w3, 20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3494:
	ldr	x0, [x20, 2944]
	mov	w1, 6
	bl	BsGet
	cmp	w0, 1
	str	w0, [x21, 68]
	ble	.L3406
	ldr	x1, .LC889
	mov	w2, w0
	mov	w3, 2
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3403
	.p2align 3
.L3502:
	ldr	x1, .LC861
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 76]
	b	.L3391
.L3505:
	ldr	w0, [x19, 68]
.L3366:
	ldrb	w1, [x19, 15]
	cbnz	w1, .L3360
	add	x5, x19, x0, sxtw 1
	sub	w2, w0, #1
	ldrsh	w3, [x21, 188]
	cmp	w2, wzr
	strh	w3, [x5, 170]
	ble	.L3371
	sub	w6, w0, #2
	add	x4, x19, 88
	add	x6, x6, 45
	add	x6, x19, x6, lsl 1
	.p2align 2
.L3372:
	ldrsh	w3, [x4]
	add	x4, x4, 2
	strh	w3, [x4, 82]
	cmp	x4, x6
	ldrh	w1, [x5, 170]
	sub	w3, w1, w3
	sxth	w3, w3
	strh	w3, [x5, 170]
	bne	.L3372
.L3371:
	cmp	w3, wzr
	ble	.L3507
	ldr	w1, [x19, 72]
	ldrsh	w3, [x21, 192]
	sub	w2, w1, #1
	add	x5, x19, x1, sxtw 1
	cmp	w2, wzr
	strh	w3, [x5, 210]
	ble	.L3374
	sub	w6, w1, #2
	add	x4, x19, 128
	add	x6, x6, 65
	add	x6, x19, x6, lsl 1
	.p2align 2
.L3375:
	ldrsh	w3, [x4]
	add	x4, x4, 2
	strh	w3, [x4, 82]
	cmp	x4, x6
	ldrh	w1, [x5, 210]
	sub	w3, w1, w3
	sxth	w3, w3
	strh	w3, [x5, 210]
	bne	.L3375
.L3374:
	cmp	w3, wzr
	bgt	.L3368
	ldr	x1, .LC853
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
	.p2align 3
.L3491:
	ldr	x1, .LC836
	mov	w3, 22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3489:
	ldr	x1, .LC867
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3354:
	ldr	w1, [x19, 72]
	sub	w1, w1, #1
	cmp	w1, wzr
	bgt	.L3359
	add	x1, x19, x0, sxtw 1
	ldrsh	w3, [x21, 188]
	sub	w2, w0, #1
	strh	w3, [x1, 170]
	b	.L3371
.L3495:
	ldr	x1, .LC893
	mov	w2, w0
	mov	w3, 64
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3403
.L3507:
	ldr	x1, .LC851
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3465
.L3400:
	ldr	x1, .LC883
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3403
	.size	HEVC_ProcessPPS, .-HEVC_ProcessPPS
	.align	3
.LC800:
	.xword	.LC799
	.align	3
.LC802:
	.xword	.LC801
	.align	3
.LC804:
	.xword	.LC803
	.align	3
.LC806:
	.xword	.LC805
	.align	3
.LC808:
	.xword	.LC807
	.align	3
.LC810:
	.xword	.LC809
	.align	3
.LC812:
	.xword	.LC811
	.align	3
.LC814:
	.xword	.LC813
	.align	3
.LC816:
	.xword	.LC815
	.align	3
.LC818:
	.xword	.LC817
	.align	3
.LC820:
	.xword	.LC819
	.align	3
.LC822:
	.xword	.LC821
	.align	3
.LC824:
	.xword	.LC823
	.align	3
.LC826:
	.xword	.LC825
	.align	3
.LC828:
	.xword	.LC827
	.align	3
.LC830:
	.xword	.LC829
	.align	3
.LC832:
	.xword	.LC831
	.align	3
.LC834:
	.xword	.LC833
	.align	3
.LC836:
	.xword	.LC835
	.align	3
.LC838:
	.xword	.LC837
	.align	3
.LC839:
	.xword	g_event_report
	.align	3
.LC841:
	.xword	.LC840
	.align	3
.LC843:
	.xword	.LC842
	.align	3
.LC845:
	.xword	.LC844
	.align	3
.LC847:
	.xword	.LC846
	.align	3
.LC849:
	.xword	.LC848
	.align	3
.LC851:
	.xword	.LC850
	.align	3
.LC853:
	.xword	.LC852
	.align	3
.LC855:
	.xword	.LC854
	.align	3
.LC857:
	.xword	.LC856
	.align	3
.LC859:
	.xword	.LC858
	.align	3
.LC861:
	.xword	.LC860
	.align	3
.LC863:
	.xword	.LC862
	.align	3
.LC865:
	.xword	.LC864
	.align	3
.LC867:
	.xword	.LC866
	.align	3
.LC869:
	.xword	.LC868
	.align	3
.LC871:
	.xword	.LC870
	.align	3
.LC873:
	.xword	.LC872
	.align	3
.LC875:
	.xword	.LC874
	.align	3
.LC877:
	.xword	.LC876
	.align	3
.LC879:
	.xword	.LC878
	.align	3
.LC881:
	.xword	.LC880
	.align	3
.LC883:
	.xword	.LC882
	.align	3
.LC885:
	.xword	.LC884
	.align	3
.LC887:
	.xword	.LC886
	.align	3
.LC889:
	.xword	.LC888
	.align	3
.LC891:
	.xword	.LC890
	.align	3
.LC893:
	.xword	.LC892
	.align	3
.LC895:
	.xword	.LC894
	.align	3
.LC897:
	.xword	.LC896
	.align	3
.LC899:
	.xword	.LC898
	.align	3
.LC901:
	.xword	.LC900
	.align	3
.LC903:
	.xword	.LC902
	.align	3
.LC905:
	.xword	.LC904
	.align	3
.LC907:
	.xword	.LC906
	.align	3
.LC909:
	.xword	.LC908
	.align	3
.LC911:
	.xword	.LC910
	.align	3
.LC913:
	.xword	.LC912
	.align	3
.LC915:
	.xword	.LC914
	.align	3
.LC917:
	.xword	.LC916
	.align	3
.LC919:
	.xword	.LC918
	.align	3
.LC921:
	.xword	.LC920
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPPS
	.type	HEVC_DecPPS, %function
HEVC_DecPPS:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC922
	ldr	x0, [x21]
	cbz	x0, .L3515
	ldr	x1, .LC926
	ldr	x0, [x19, 2944]
	bl	HEVC_ue_v
	mov	w22, w0
	ldr	w3, [x19, 164]
	cmp	w0, w3
	bcs	.L3516
	mov	w20, 5036
	umull	x20, w0, w20
	ldr	x0, [x19, 2968]
	add	x1, x0, x20
	ldrb	w0, [x0, x20]
	cbnz	w0, .L3517
	str	w22, [x1, 28]
	mov	x0, x19
	ldr	x1, [x19, 2968]
	add	x1, x1, x20
	bl	HEVC_ProcessPPS
	mov	w23, w0
	cbnz	w0, .L3518
	ldr	x0, [x19, 2968]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2968]
	strb	w1, [x0, x20]
.L3510:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3517:
	ldr	x24, .LC929
	mov	x2, 5036
	ldr	x21, [x21]
	mov	w1, 0
	add	x21, x21, 458752
	ldr	x3, [x24, 96]
	mov	x0, x21
	blr	x3
	str	w22, [x21, 28]
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_ProcessPPS
	mov	w23, w0
	cbnz	w0, .L3519
	mov	w0, 1
	strb	w0, [x21, 1]
	strb	w0, [x21]
	mov	x1, x21
	ldr	x3, [x24, 112]
	mov	x2, 5036
	ldr	x0, [x19, 2968]
	add	x0, x0, x20
	blr	x3
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3519:
	ldr	x1, .LC931
	mov	w2, w22
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L3510
	.p2align 3
.L3516:
	ldr	x1, .LC928
	mov	w2, w0
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L3510
.L3518:
	ldr	x1, .LC931
	mov	w2, w22
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	ldr	x0, [x19, 2968]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 1]
	ldr	x0, [x19, 2968]
	strb	wzr, [x0, x20]
	b	.L3510
.L3515:
	ldr	x2, .LC923
	mov	w23, -1
	ldr	x1, .LC924
	add	x2, x2, 152
	bl	dprint_vfmw
	b	.L3510
	.size	HEVC_DecPPS, .-HEVC_DecPPS
	.align	3
.LC922:
	.xword	.LANCHOR1
	.align	3
.LC923:
	.xword	.LANCHOR3
	.align	3
.LC924:
	.xword	.LC166
	.align	3
.LC926:
	.xword	.LC925
	.align	3
.LC928:
	.xword	.LC927
	.align	3
.LC929:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC931:
	.xword	.LC930
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecPredWeightTable
	.type	HEVC_DecPredWeightTable, %function
HEVC_DecPredWeightTable:
	stp	x29, x30, [sp, -240]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x28, 5588]
	mov	w4, 5036
	ldr	w0, [x28, 5604]
	ldr	x2, [x28, 2968]
	cmp	w1, 1
	smaddl	x2, w0, w4, x2
	beq	.L3594
	cbnz	w1, .L3524
	ldrb	w0, [x2, 11]
	cbz	w0, .L3524
.L3522:
	ldr	x1, .LC933
	ldr	x0, [x28, 2944]
	ldr	w19, [x2, 32]
	add	x2, x28, 4096
	mov	x21, x2
	ldr	x20, [x28, 2960]
	str	x2, [x29, 104]
	bl	HEVC_ue_v
	cmp	w0, 7
	str	w0, [x28, 5724]
	add	x22, x21, 1628
	bhi	.L3595
	mov	w1, 12668
	smaddl	x19, w19, w1, x20
	ldr	w1, [x19, 60]
	cbnz	w1, .L3596
	str	w0, [x22, 132]
.L3566:
	ldr	w0, [x28, 5644]
	mov	w20, 0
	cbz	w0, .L3536
	.p2align 2
.L3579:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 5644]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -128]
	bhi	.L3579
	ldr	w0, [x19, 60]
	cbz	w0, .L3532
	mov	w20, 0
	cbz	w1, .L3536
	.p2align 2
.L3578:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 5644]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -64]
	bhi	.L3578
.L3532:
	mov	w27, 0
	cbz	w1, .L3536
	ldr	x0, [x29, 104]
	ldr	x26, .LC951
	add	x21, x0, 1628
	b	.L3577
	.p2align 3
.L3538:
	add	x20, x28, x20
	ldr	w1, [x21]
	mov	w0, 1
	lsl	w0, w0, w1
	str	wzr, [x20, 5728]
	str	w0, [x20, 5860]
.L3540:
	ldr	w0, [x19, 60]
	cbz	w0, .L3542
	add	x0, x29, 240
	add	x0, x0, x22, lsl 2
	ldr	w0, [x0, -64]
	cbnz	w0, .L3543
	lsl	x22, x22, 3
	ldr	w2, [x21, 132]
	add	x1, x28, x22
	add	x22, x21, x22
	mov	w0, 1
	lsl	w0, w0, w2
	str	wzr, [x1, 6052]
	str	w0, [x1, 5924]
	str	w0, [x22, 204]
	str	wzr, [x22, 332]
.L3542:
	ldr	w0, [x28, 5644]
	add	w27, w27, 1
	cmp	w0, w27
	bls	.L3536
.L3577:
	uxtw	x22, w27
	add	x0, x29, 240
	lsl	x20, x22, 2
	add	x0, x0, x20
	ldr	w0, [x0, -128]
	cbz	w0, .L3538
	ldr	x1, .LC943
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	bhi	.L3597
	ldr	w2, [x21]
	add	x20, x28, x20
	mov	w23, 1
	ldr	x1, .LC947
	lsl	w2, w23, w2
	add	w0, w2, w0
	str	w0, [x20, 5860]
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	str	w0, [x20, 5728]
	bls	.L3540
	ldr	x1, .LC949
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
	.p2align 3
.L3594:
	ldrb	w0, [x2, 10]
	cbnz	w0, .L3522
.L3524:
	mov	w0, 0
.L3592:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L3543:
	ldr	x0, [x28, 2944]
	mov	x1, x26
	add	x20, x22, 1
	add	x25, x28, x22, lsl 3
	mov	w24, 128
	mov	w22, 1
	bl	HEVC_se_v
	add	w6, w0, 128
	cmp	w6, 255
	add	x20, x28, x20, lsl 3
	mov	w23, 127
	ldr	x1, .LC955
	bhi	.L3598
.L3544:
	ldr	w6, [x21, 132]
	lsl	w6, w22, w6
	add	w0, w6, w0
	str	w0, [x25, 5924]
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 512
	cmp	w1, 1023
	mov	w6, -128
	bhi	.L3599
	ldr	w1, [x25, 5924]
	add	x25, x25, 4
	ldr	w7, [x21, 132]
	lsl	w1, w1, 7
	asr	w1, w1, w7
	sub	w1, w24, w1
	add	w0, w1, w0
	cmp	w0, 127
	csel	w0, w0, w23, le
	cmn	w0, #128
	csel	w0, w0, w6, ge
	cmp	x20, x25
	str	w0, [x25, 6048]
	beq	.L3542
	ldr	x0, [x28, 2944]
	mov	x1, x26
	bl	HEVC_se_v
	add	w6, w0, 128
	cmp	w6, 255
	ldr	x1, .LC955
	bls	.L3544
.L3598:
	ldr	x1, .LC953
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L3536:
	ldr	w0, [x28, 5588]
	cbnz	w0, .L3524
	ldr	w0, [x28, 5648]
	cbz	w0, .L3524
	mov	w20, 0
	.p2align 2
.L3550:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 5648]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -128]
	bhi	.L3550
	ldr	w0, [x19, 60]
	cbnz	w0, .L3600
.L3551:
	mov	w25, 0
	cbz	w1, .L3524
	ldr	x0, [x29, 104]
	ldr	x23, .LC967
	add	x21, x0, 1628
	b	.L3575
	.p2align 3
.L3555:
	add	x20, x28, x20
	ldr	w1, [x21]
	mov	w0, 1
	lsl	w0, w0, w1
	str	wzr, [x20, 5792]
	str	w0, [x20, 6180]
.L3557:
	ldr	w0, [x19, 60]
	cbz	w0, .L3559
	add	x0, x29, 240
	add	x0, x0, x26, lsl 2
	ldr	w0, [x0, -64]
	cbnz	w0, .L3560
	lsl	x26, x26, 3
	ldr	w4, [x21, 132]
	add	x1, x28, x26
	add	x26, x21, x26
	mov	w0, 1
	lsl	w0, w0, w4
	str	wzr, [x1, 6372]
	str	w0, [x1, 6244]
	str	w0, [x26, 524]
	str	wzr, [x26, 652]
.L3559:
	ldr	w0, [x28, 5648]
	add	w25, w25, 1
	cmp	w0, w25
	bls	.L3524
.L3575:
	uxtw	x26, w25
	add	x0, x29, 240
	lsl	x20, x26, 2
	add	x0, x0, x20
	ldr	w0, [x0, -128]
	cbz	w0, .L3555
	ldr	x1, .LC959
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 128
	cmp	w1, 255
	bhi	.L3601
	ldr	w1, [x21]
	add	x20, x28, x20
	mov	w27, 1
	lsl	w1, w27, w1
	add	w0, w1, w0
	str	w0, [x20, 6180]
	ldr	x1, .LC963
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	str	w0, [x20, 5792]
	add	w0, w0, 128
	cmp	w0, 255
	bls	.L3557
	ldr	x1, .LC965
	mov	w0, w27
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
	.p2align 3
.L3560:
	add	x22, x28, x26, lsl 3
	add	x26, x26, 1
	mov	w20, 1
	mov	w24, 128
	add	x26, x28, x26, lsl 3
	mov	w27, 127
.L3563:
	ldr	x0, [x28, 2944]
	mov	x1, x23
	bl	HEVC_se_v
	add	w5, w0, 128
	cmp	w5, 255
	ldr	x1, .LC971
	bhi	.L3602
	ldr	w5, [x21, 132]
	lsl	w5, w20, w5
	add	w0, w5, w0
	str	w0, [x22, 6244]
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 512
	cmp	w1, 1023
	mov	w5, -128
	bhi	.L3603
	ldr	w1, [x22, 6244]
	add	x22, x22, 4
	ldr	w6, [x21, 132]
	lsl	w1, w1, 7
	asr	w1, w1, w6
	sub	w1, w24, w1
	add	w0, w1, w0
	cmp	w0, 127
	csel	w0, w0, w27, le
	cmn	w0, #128
	csel	w0, w0, w5, ge
	str	w0, [x22, 6368]
	cmp	x22, x26
	bne	.L3563
	b	.L3559
	.p2align 3
.L3596:
	ldr	x1, .LC937
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 7
	cmp	w1, 14
	bhi	.L3604
	ldr	w1, [x28, 5724]
	add	w0, w0, w1
	str	w0, [x22, 132]
	cmp	w0, 7
	bls	.L3566
	ldr	x1, .LC941
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
	.p2align 3
.L3599:
	ldr	x1, .LC957
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
.L3600:
	mov	w20, 0
	cbz	w1, .L3524
	.p2align 2
.L3576:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	add	x1, x29, 240
	add	x2, x1, x20, uxtw 2
	ldr	w1, [x28, 5648]
	add	w20, w20, 1
	cmp	w1, w20
	str	w0, [x2, -64]
	bhi	.L3576
	b	.L3551
.L3597:
	ldr	x1, .LC945
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
.L3602:
	ldr	x1, .LC969
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
.L3603:
	ldr	x1, .LC973
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
.L3601:
	ldr	x1, .LC961
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
.L3595:
	ldr	x1, .LC935
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
.L3604:
	ldr	x1, .LC939
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3592
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	3
.LC933:
	.xword	.LC932
	.align	3
.LC935:
	.xword	.LC934
	.align	3
.LC937:
	.xword	.LC936
	.align	3
.LC939:
	.xword	.LC938
	.align	3
.LC941:
	.xword	.LC940
	.align	3
.LC943:
	.xword	.LC942
	.align	3
.LC945:
	.xword	.LC944
	.align	3
.LC947:
	.xword	.LC946
	.align	3
.LC949:
	.xword	.LC948
	.align	3
.LC951:
	.xword	.LC950
	.align	3
.LC953:
	.xword	.LC952
	.align	3
.LC955:
	.xword	.LC954
	.align	3
.LC957:
	.xword	.LC956
	.align	3
.LC959:
	.xword	.LC958
	.align	3
.LC961:
	.xword	.LC960
	.align	3
.LC963:
	.xword	.LC962
	.align	3
.LC965:
	.xword	.LC964
	.align	3
.LC967:
	.xword	.LC966
	.align	3
.LC969:
	.xword	.LC968
	.align	3
.LC971:
	.xword	.LC970
	.align	3
.LC973:
	.xword	.LC972
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	add	x24, x28, 4096
	bl	_mcount
	ldr	x2, [x28, 2984]
	mov	w1, 1
	ldr	x0, [x28, 2944]
	ldr	w20, [x2, 24]
	bl	BsGet
	strb	w0, [x24, 1472]
	ldr	w25, [x28, 5596]
	sub	w0, w25, #16
	str	w0, [x29, 132]
	cmp	w0, 5
	bls	.L3923
.L3606:
	ldr	x1, .LC975
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	str	w0, [x28, 5604]
	ldr	w4, [x28, 164]
	tbnz	w0, #31, .L3608
	cmp	w0, w4
	bge	.L3608
	mov	x0, x28
	bl	HEVC_VpsSpsPpsCheck
	cbnz	w0, .L3924
	ldr	x0, [x28, 2968]
	mov	w3, 5036
	ldr	w21, [x28, 5604]
	mov	w2, 12668
	ldr	x1, [x28, 2960]
	ldr	x23, [x28, 2952]
	smaddl	x21, w21, w3, x0
	ldr	w19, [x21, 32]
	ldrb	w0, [x21, 2]
	smaddl	x19, w19, w2, x1
	ldr	w22, [x19, 48]
	cbnz	w0, .L3925
.L3614:
	strb	wzr, [x24, 1473]
.L3615:
	ldp	w2, w3, [x19, 140]
	cbz	w2, .L3617
	cbz	w3, .L3617
	ldp	w0, w1, [x19, 64]
	add	w0, w2, w0
	add	w1, w3, w1
	sub	w1, w1, #1
	sub	w0, w0, #1
	udiv	w0, w0, w2
	udiv	w2, w1, w3
	mov	w3, 1
	mov	w1, 0
	mul	w2, w0, w2
	ldr	w0, [x19, 172]
	cmp	w2, 1
	lsl	w0, w0, 1
	lsl	w26, w3, w0
	ble	.L3619
	.p2align 2
.L3620:
	add	w1, w1, 1
	lsl	w0, w3, w1
	cmp	w2, w0
	bgt	.L3620
.L3619:
	ldrb	w0, [x24, 1472]
	str	wzr, [x29, 136]
	cbz	w0, .L3926
.L3621:
	ldr	w0, [x28, 192]
	str	w0, [x28, 5580]
	ldrb	w0, [x24, 1473]
	cbnz	w0, .L3624
	ldrb	w26, [x28, 1]
	ldr	w0, [x21, 36]
	cmp	w26, 1
	beq	.L3625
	mov	w26, 0
	cbz	w0, .L3629
	.p2align 2
.L3860:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	add	w26, w26, w1
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, w26
	bhi	.L3860
.L3629:
	ldr	x1, .LC986
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	cmp	w0, 2
	str	w0, [x28, 5588]
	bhi	.L3927
	ldrb	w0, [x21, 4]
	cbnz	w0, .L3928
.L3632:
	sub	w0, w25, #19
	str	w0, [x29, 116]
	mov	w0, 24912
	umull	x22, w22, w0
	add	x0, x23, x22
	ldrb	w22, [x28, 1]
	str	x0, [x29, 104]
	cmp	w22, 1
	beq	.L3929
	ldr	w0, [x29, 116]
	str	xzr, [x29, 120]
	str	wzr, [x29, 140]
	cmp	w0, 1
	bls	.L3637
.L3967:
	cbz	w22, .L3930
.L3638:
	ldr	w1, [x19, 116]
	mov	w2, 1
	ldr	w0, [x28, 188]
	lsl	w1, w2, w1
	ldr	w2, [x29, 140]
	mov	w3, w1
	str	w3, [x29, 128]
	udiv	w1, w0, w1
	msub	w1, w1, w3, w0
	cmp	w2, w1
	sub	w0, w0, w1
	bcs	.L3639
	sub	w2, w1, w2
	cmp	w2, w3, lsr 1
	bcc	.L3639
	add	w0, w0, w3
.L3640:
	ldr	w1, [x28, 5596]
	add	x20, x28, x20, uxtw 2
	sub	w1, w1, #16
	cmp	w1, 2
	ldr	w1, [x29, 140]
	csel	w0, w0, wzr, hi
	add	w3, w0, w1
	str	w3, [x28, 5580]
	ldr	w2, [x20, 212]
	cmp	w3, w2
	bge	.L3642
	ldrb	w0, [x24, 1472]
	cmp	w0, 1
	beq	.L3931
.L3642:
	ldr	w0, [x28, 2368]
	cbnz	w0, .L3643
	ldr	w0, [x28, 5580]
	str	w0, [x28, 192]
.L3643:
	ldr	w0, [x28, 5592]
	cbnz	w0, .L3644
	ldr	w0, [x28, 5596]
	cmp	w0, 15
	bhi	.L3645
	mov	w1, 1
	tbz	x0, 0, .L3645
.L3646:
	sub	w0, w0, #7
	tst	w0, -3
	cset	w0, ne
	tst	w1, w0
	beq	.L3644
	ldr	w0, [x28, 5580]
	str	w0, [x28, 188]
	.p2align 2
.L3644:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3647
	ldr	w3, [x19, 176]
	mov	w1, 0
	mov	w2, 1
	mov	w0, 0
	cmp	w3, 1
	bls	.L3649
	.p2align 2
.L3859:
	add	w1, w1, 1
	lsl	w0, w2, w1
	cmp	w0, w3
	bcc	.L3859
	mov	w0, 0
	cbnz	w1, .L3932
.L3652:
	sxtw	x4, w0
	mov	x2, 164
	lsl	x1, x4, 2
	add	x0, x24, 2404
	sub	x1, x1, x4
	lsl	x3, x1, 3
	sub	x1, x3, x1
	lsl	x1, x1, 1
	sub	x1, x1, x4
	add	x1, x19, x1, lsl 2
	add	x1, x1, 2164
	bl	memcpy
	str	x0, [x29, 120]
.L3650:
	ldrb	w0, [x19, 8]
	cbz	w0, .L3654
	ldr	w0, [x19, 180]
	ldr	w1, [x24, 2408]
	ldr	w20, [x28, 6500]
	add	w20, w20, w1
	cbnz	w0, .L3933
	mov	w25, 0
	str	wzr, [x29, 156]
.L3655:
	ldr	x1, .LC1000
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	ldr	w3, [x24, 2408]
	add	x1, x24, 2404
	ldr	w2, [x28, 6500]
	add	w0, w0, w25
	mov	w4, w0
	add	w0, w2, w3
	add	w0, w0, w4
	str	w4, [x29, 152]
	cmp	w0, 16
	bhi	.L3934
	ldr	w2, [x29, 152]
	mov	w23, 0
	mov	w27, 0
	add	w0, w20, w2
	str	w0, [x29, 112]
	sub	w22, w0, #1
	cbz	w2, .L3671
	str	x1, [x29, 144]
	b	.L3858
	.p2align 3
.L3937:
	ldr	w1, [x29, 156]
	cbnz	w1, .L3935
.L3662:
	sxtw	x0, w0
	ldr	x1, [x29, 144]
	add	x4, x19, x0
	add	x1, x1, x26
	add	x0, x19, x0, lsl 2
	ldrb	w4, [x4, 13]
	ldr	w20, [x0, 196]
	strb	w4, [x1, 12]
	mov	w1, 1
	ldr	x0, [x28, 2944]
	bl	BsGet
	uxtb	w0, w0
	cmp	w27, wzr
	add	x1, x28, x26, lsl 2
	ccmp	w27, w25, 4, ne
	cbnz	w0, .L3936
.L3666:
	str	w20, [x1, 6600]
	csel	w23, w23, wzr, ne
	str	wzr, [x1, 5656]
	ldr	w0, [x28, 5580]
	sub	w20, w20, w0
	str	w20, [x1, 6532]
.L3668:
	ldr	w0, [x29, 152]
	add	w27, w27, 1
	sub	w22, w22, #1
	cmp	w0, w27
	beq	.L3671
.L3858:
	cmp	w27, w25
	uxtw	x26, w22
	mov	w0, 0
	bcc	.L3937
	ldr	w1, [x19, 120]
	uxtw	x26, w22
	ldr	x0, [x28, 2944]
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x1, [x29, 144]
	add	x1, x1, x26
	strb	w0, [x1, 12]
	mov	w1, 1
	ldr	x0, [x28, 2944]
	bl	BsGet
	uxtb	w0, w0
	cmp	w27, wzr
	add	x1, x28, x26, lsl 2
	ccmp	w27, w25, 4, ne
	cbz	w0, .L3666
.L3936:
	ldr	x1, .LC1006
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	add	w23, w23, w0
	add	x3, x28, x26, lsl 2
	cmp	w27, wzr
	ccmp	w27, w25, 4, ne
	mov	w1, 1
	str	w1, [x3, 5656]
	cset	w1, eq
	cmp	w1, wzr
	csel	w23, w23, w0, eq
	ldr	w0, [x29, 128]
	ldr	w1, [x28, 5580]
	msub	w20, w23, w0, w20
	ldr	w0, [x29, 140]
	sub	w0, w1, w0
	add	w20, w20, w0
	str	w20, [x3, 6600]
	sub	w20, w20, w1
	str	w20, [x3, 6532]
	b	.L3668
	.p2align 3
.L3671:
	ldr	w0, [x29, 112]
	str	w0, [x24, 2412]
	cmp	w0, 16
	bhi	.L3938
.L3654:
	ldrb	w0, [x19, 9]
	cbnz	w0, .L3939
	strb	wzr, [x24, 1476]
	ldrb	w22, [x28, 1]
.L3673:
	cmp	w22, 1
	beq	.L3940
.L3675:
	ldrb	w0, [x19, 6]
	cbnz	w0, .L3941
.L3776:
	ldr	w0, [x29, 116]
	cmp	w0, 1
	bls	.L3942
.L3705:
	ldr	w0, [x28, 5588]
	cmp	w0, 2
	bne	.L3943
.L3706:
	ldrb	w0, [x24, 1476]
	cbnz	w0, .L3780
.L3729:
	mov	w4, 2
.L3736:
	ldrb	w0, [x21, 11]
	cbz	w0, .L3727
	cbnz	w4, .L3727
.L3739:
	mov	x0, x28
	bl	HEVC_DecPredWeightTable
	cbnz	w0, .L3944
	ldr	w4, [x28, 5588]
.L3727:
	cmp	w4, 2
	beq	.L3740
	ldr	x1, .LC1036
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	mov	w3, 4
	mov	w1, 5
	sub	w3, w3, w0
	sub	w2, w1, w0
	cmp	w3, 4
	str	w2, [x28, 5616]
	bhi	.L3945
.L3740:
	ldr	x1, .LC1040
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	ldr	w2, [x21, 48]
	mov	w1, 51
	add	w0, w0, w2
	str	w0, [x28, 5584]
	ldr	w3, [x19, 92]
	neg	w2, w3
	cmp	w0, w2
	ccmp	w0, w1, 0, ge
	bgt	.L3946
	ldrb	w0, [x21, 9]
	cbnz	w0, .L3947
.L3742:
	ldrb	w0, [x21, 18]
	cbz	w0, .L3914
	ldrb	w0, [x21, 19]
	cbnz	w0, .L3948
.L3748:
	ldrb	w0, [x21, 20]
	strb	w0, [x24, 1481]
	ldr	w1, [x21, 76]
	str	w1, [x28, 5628]
	ldr	w1, [x21, 80]
	str	w1, [x28, 5632]
.L3747:
	ldrb	w2, [x19, 6]
	mov	w1, 0
	cbz	w2, .L3751
	ldrh	w1, [x28, 5570]
	cmp	w1, wzr
	cset	w1, ne
.L3751:
	ldrb	w2, [x21, 17]
	cbz	w2, .L3752
	cmp	w0, wzr
	cset	w0, eq
	orr	w1, w0, w1
	cbnz	w1, .L3949
.L3752:
	strb	w2, [x24, 1482]
.L3624:
	ldr	w0, [x21, 12]
	tst	w0, 16776960
	bne	.L3753
.L3760:
	ldrb	w0, [x21, 23]
	cbnz	w0, .L3950
.L3755:
	ldr	w0, [x29, 136]
	cbnz	w0, .L3951
	ldrb	w0, [x28, 3]
	cbz	w0, .L3769
	ldr	w0, [x29, 132]
	cmp	w0, 5
	bhi	.L3770
	ldr	w0, [x28, 5600]
	mov	w2, 1
	add	x1, x28, x0
	strb	w2, [x1, 6]
.L3771:
	ldr	w1, [x28, 5580]
	cmp	w1, wzr
	ldr	w1, [x29, 132]
	ccmp	w1, 5, 2, ne
	bhi	.L3772
	ldr	w1, [x28, 5596]
	add	x0, x28, x0
	cmp	w1, 21
	beq	.L3952
	.p2align 2
.L3915:
	strb	wzr, [x0, 4]
.L3774:
	mov	x0, x28
	bl	HEVC_IsNewPic
	str	w0, [x28, 5720]
	mov	x0, x28
	bl	HEVC_ReadByteAlignment
	cmp	w0, wzr
	csetm	w0, ne
.L3905:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L3925:
	ldrb	w0, [x24, 1472]
	cbnz	w0, .L3614
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1473]
	b	.L3615
	.p2align 3
.L3951:
	ldr	w0, [x28, 5600]
	add	x1, x28, x0
	ldrb	w1, [x1, 6]
	cbnz	w1, .L3771
.L3772:
	add	x0, x28, x0
	b	.L3915
	.p2align 3
.L3639:
	ldr	w2, [x29, 140]
	cmp	w2, w1
	bls	.L3640
	sub	w1, w2, w1
	ldr	w2, [x29, 128]
	cmp	w1, w2, lsr 1
	sub	w1, w0, w2
	csel	w0, w1, w0, hi
	b	.L3640
	.p2align 3
.L3923:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	b	.L3606
	.p2align 3
.L3926:
	ldr	x0, [x28, 2944]
	bl	BsGet
	str	w0, [x28, 5608]
	ldp	w1, w3, [x19, 188]
	mul	w3, w1, w3
	tbnz	w0, #31, .L3623
	cmp	w3, w0
	bls	.L3623
	mul	w0, w26, w0
	str	w0, [x29, 136]
	b	.L3621
	.p2align 3
.L3753:
	ldr	x1, .LC1064
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	mov	w20, w0
	ldr	w0, [x21, 12]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L3953
	cmp	w0, 256
	ldr	w0, [x21, 68]
	beq	.L3954
	ldr	w1, [x19, 192]
	mul	w0, w0, w1
	sub	w0, w0, #1
.L3757:
	cmp	w0, 255
	mov	w1, 255
	csel	w3, w0, w1, ls
	cmp	w20, w3
	bhi	.L3955
	cbz	w20, .L3760
	ldr	x1, .LC1068
	mov	w19, 0
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	cmp	w0, 31
	add	w22, w0, 1
	bhi	.L3956
	.p2align 2
.L3857:
	ldr	x0, [x28, 2944]
	mov	w1, w22
	add	w19, w19, 1
	bl	BsGet
	cmp	w20, w19
	bne	.L3857
	ldrb	w0, [x21, 23]
	cbz	w0, .L3755
.L3950:
	ldr	x1, .LC1072
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	cmp	w0, 256
	mov	w20, w0
	bhi	.L3957
	ldr	x0, [x28, 2944]
	bl	BsResidBits
	cmp	w20, w0
	bhi	.L3766
	mov	w19, 0
	cbz	w20, .L3755
	.p2align 2
.L3856:
	ldr	x0, [x28, 2944]
	mov	w1, 8
	add	w19, w19, 1
	bl	BsGet
	cmp	w20, w19
	bne	.L3856
	b	.L3755
	.p2align 3
.L3769:
	ldr	w0, [x29, 132]
	cmp	w0, 5
	bhi	.L3770
	ldr	w0, [x28, 5600]
	add	x1, x28, x0
	add	x0, x28, x0
	strb	wzr, [x1, 6]
	b	.L3915
.L3953:
	ldr	w0, [x19, 192]
	sub	w0, w0, #1
	b	.L3757
	.p2align 3
.L3645:
	sub	w1, w0, #16
	cmp	w1, 7
	cset	w1, ls
	b	.L3646
.L3932:
	ldr	x0, [x28, 2944]
	bl	BsGet
	ldr	w3, [x19, 176]
	tbnz	w0, #31, .L3958
.L3649:
	sub	w3, w3, #1
	cmp	w3, w0
	bcs	.L3652
.L3653:
	ldr	x1, .LC994
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
	.p2align 3
.L3935:
	ldr	x0, [x28, 2944]
	bl	BsGet
	ldr	w4, [x19, 180]
	sub	w4, w4, #1
	tbnz	w0, #31, .L3664
	cmp	w4, w0
	bcs	.L3662
.L3664:
	ldr	x1, .LC1004
	mov	w3, w0
	mov	w2, w27
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
	.p2align 3
.L3943:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 1477]
	cbnz	w0, .L3959
	ldr	w0, [x21, 40]
	ldr	w4, [x28, 5588]
	str	w0, [x28, 5644]
	cbnz	w4, .L3714
	ldr	w0, [x21, 44]
	mov	w22, 0
	mov	w20, 0
	str	w0, [x28, 5648]
.L3712:
	ldr	x0, [x29, 120]
	cbz	x0, .L3960
	ldr	x0, [x29, 120]
	ldr	w2, [x0, 8]
	cmp	w2, 16
	bhi	.L3716
	mov	w3, 0
	cbz	w2, .L3718
	ldr	x0, [x29, 120]
	sub	w2, w2, #1
	add	x2, x2, 13
	mov	w3, 0
	add	x2, x0, x2
	add	x0, x0, 12
	.p2align 2
.L3720:
	ldrb	w1, [x0], 1
	cmp	w1, wzr
	csinc	w3, w3, w3, eq
	cmp	x0, x2
	bne	.L3720
.L3718:
	ldrb	w0, [x28, 1]
	cmp	w0, 1
	beq	.L3961
.L3721:
	ldrb	w0, [x21, 22]
	cmp	w0, wzr
	ccmp	w3, 1, 4, ne
	ble	.L3962
	add	x2, x24, 2568
	add	x1, x24, 1472
	mov	x0, x28
	bl	HEVC_DecRefPicListsModification
	cbnz	w0, .L3908
	ldr	w4, [x28, 5588]
	cbnz	w4, .L3722
.L3778:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1478]
	ldr	w4, [x28, 5588]
.L3722:
	cmp	w4, 2
	beq	.L3706
.L3779:
	ldrb	w0, [x21, 5]
	cbnz	w0, .L3963
.L3723:
	ldrb	w0, [x24, 1476]
	cbz	w0, .L3732
	cbz	w4, .L3964
	mov	w0, 1
	cmp	w4, 2
	strb	w0, [x24, 1480]
	beq	.L3729
.L3728:
	ldr	w0, [x28, 5644]
	cmp	w0, 1
	bls	.L3913
.L3731:
	ldr	x1, .LC1030
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	str	w0, [x28, 5612]
	ldrb	w2, [x24, 1480]
	cbnz	w2, .L3965
	sub	w4, w22, #1
	cmp	w22, wzr
	csel	w4, w4, wzr, ne
.L3734:
	cmp	w4, w0
	ccmp	w0, wzr, 1, cs
	bge	.L3913
	ldr	x1, .LC1032
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
	.p2align 3
.L3913:
	ldr	w4, [x28, 5588]
.L3732:
	ldrb	w0, [x21, 10]
	cbz	w0, .L3736
	cmp	w4, 1
	bne	.L3736
	b	.L3739
	.p2align 3
.L3770:
	ldr	w0, [x28, 5600]
	add	x0, x28, x0
	b	.L3915
.L3948:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	cbz	w0, .L3748
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 1481]
	cbnz	w0, .L3747
	ldr	x1, .LC1056
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x28, 5628]
	bhi	.L3966
.L3749:
	ldr	x1, .LC1060
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x28, 5632]
	bls	.L3914
	ldr	x1, .LC1062
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 80]
	str	w0, [x28, 5632]
	.p2align 2
.L3914:
	ldrb	w0, [x24, 1481]
	b	.L3747
	.p2align 3
.L3928:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	b	.L3632
	.p2align 3
.L3962:
	cbnz	w4, .L3779
	b	.L3778
	.p2align 3
.L3929:
	cbz	w20, .L3634
	uxtw	x0, w20
	ldr	x1, [x29, 104]
	add	x0, x0, 4096
	add	x0, x1, x0, lsl 2
	ldr	w0, [x0, 180]
	add	x0, x1, x0
	add	x0, x0, 12288
	ldrb	w0, [x0, 135]
	cbnz	w0, .L3634
.L3635:
	ldr	w1, [x19, 120]
	ldr	x0, [x28, 2944]
	bl	BsGet
	ldrb	w22, [x28, 1]
	str	w0, [x29, 140]
.L3636:
	add	x0, x24, 2404
	str	x0, [x29, 120]
	ldr	w0, [x29, 116]
	cmp	w0, 1
	bhi	.L3967
.L3637:
	ldr	w0, [x28, 2368]
	str	wzr, [x28, 5580]
	cbnz	w0, .L3674
	str	wzr, [x28, 192]
.L3674:
	ldr	w0, [x28, 5592]
	cbnz	w0, .L3673
	str	wzr, [x28, 188]
	b	.L3673
	.p2align 3
.L3634:
	ldr	w0, [x29, 116]
	cmp	w0, 1
	bhi	.L3635
	str	wzr, [x29, 140]
	b	.L3636
	.p2align 3
.L3941:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1474]
	mov	w1, 1
	ldr	x0, [x28, 2944]
	bl	BsGet
	strb	w0, [x24, 1475]
	b	.L3776
	.p2align 3
.L3608:
	ldr	x2, .LC976
	mov	w3, w0
	ldr	x1, .LC978
	mov	w0, 1
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
	.p2align 3
.L3942:
	strb	wzr, [x24, 1476]
	b	.L3705
	.p2align 3
.L3947:
	ldr	x1, .LC1044
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x28, 5620]
	bhi	.L3968
	ldr	w3, [x21, 60]
	add	w1, w0, w3
	add	w1, w1, 12
	cmp	w1, 24
	bhi	.L3969
	ldr	x1, .LC1050
	ldr	x0, [x28, 2944]
	bl	HEVC_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x28, 5624]
	bhi	.L3970
	ldr	w1, [x21, 64]
	add	w2, w0, w1
	add	w0, w2, 12
	cmp	w0, 24
	bls	.L3742
	ldr	x1, .LC1054
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
	.p2align 3
.L3647:
	ldr	w3, [x19, 176]
	add	x2, x24, 2404
	mov	x1, x19
	mov	x0, x28
	str	x2, [x29, 120]
	bl	HEVC_DecShortTermRefPicSet
	cbz	w0, .L3650
	ldr	x1, .LC992
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
	.p2align 3
.L3930:
	ldr	w1, [x19, 120]
	ldr	x0, [x28, 2944]
	bl	BsGet
	str	w0, [x29, 140]
	b	.L3638
.L3963:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1479]
	ldr	w4, [x28, 5588]
	b	.L3723
.L3939:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1476]
	ldrb	w22, [x28, 1]
	b	.L3673
.L3961:
	ldr	w0, [x28, 6928]
	add	w3, w3, w0
	b	.L3721
.L3714:
	mov	w20, 0
	str	wzr, [x28, 5648]
.L3713:
	cmp	w4, 2
	beq	.L3706
	mov	w22, 0
	b	.L3712
.L3625:
	cbz	w0, .L3629
	ldr	x0, [x28, 2944]
	mov	w1, w26
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, 1
	bls	.L3629
	ldr	x0, [x28, 2944]
	mov	w1, w26
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, 2
	bls	.L3629
	ldr	x0, [x28, 2944]
	mov	w1, w26
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, 3
	bls	.L3629
	mov	w26, 3
	.p2align 2
.L3630:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	add	w26, w26, 1
	bl	BsGet
	ldr	w0, [x21, 36]
	cmp	w0, w26
	bhi	.L3630
	b	.L3629
.L3959:
	ldr	x1, .LC1016
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	add	w20, w0, 1
	cmp	w20, 16
	bhi	.L3971
	ldr	w4, [x28, 5588]
	str	w20, [x28, 5644]
	cbz	w4, .L3972
	str	wzr, [x28, 5648]
	b	.L3713
.L3780:
	mov	w0, 1
	mov	w4, 2
	strb	w0, [x24, 1480]
	b	.L3732
.L3949:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	strb	w0, [x24, 1482]
	b	.L3624
.L3965:
	sub	w4, w20, #1
	cmp	w20, wzr
	csel	w4, w4, wzr, ne
	b	.L3734
.L3952:
	mov	w1, 1
	strb	w1, [x0, 4]
	b	.L3774
.L3931:
	ldr	x1, .LC990
	bl	dprint_vfmw
	b	.L3642
.L3972:
	ldr	x1, .LC1020
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	add	w22, w0, 1
	cmp	w22, 16
	bhi	.L3973
	ldr	w4, [x28, 5588]
	str	w22, [x28, 5648]
	cmp	w4, 2
	bne	.L3712
	b	.L3706
	.p2align 3
.L3957:
	ldr	x1, .LC1074
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3938:
	ldr	x1, .LC1008
	mov	w3, 16
	ldr	w2, [x29, 112]
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3958:
	sub	w3, w3, #1
	b	.L3653
	.p2align 3
.L3964:
	ldr	x0, [x28, 2944]
	mov	w1, 1
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x24, 1480]
	ldr	w4, [x28, 5588]
	cmp	w4, 2
	beq	.L3740
	cbnz	w0, .L3728
	ldr	w0, [x28, 5648]
	cmp	w0, 1
	bhi	.L3731
	b	.L3732
.L3617:
	ldr	x1, .LC982
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3940:
	ldr	x3, [x28, 2984]
	ldr	w0, [x3, 24]
	cbz	w0, .L3676
	ldr	x2, [x29, 104]
	add	x23, x2, 12288
	ldrb	w1, [x23, 134]
	cbnz	w1, .L3677
	add	x0, x2, x0, uxtw 2
	add	x20, x0, 16384
	ldr	w0, [x20, 196]
	cmp	w0, wzr
	ble	.L3678
	ldr	x0, [x28, 2944]
	mov	w1, w22
	bl	BsGet
	uxtb	w0, w0
	ldr	w4, [x20, 196]
	cbz	w0, .L3680
	cmp	w4, 1
	ble	.L3680
	ldrb	w0, [x23, 133]
	cbnz	w0, .L3681
	mov	w1, 0
	ldr	x0, [x28, 2944]
	bls	.L3682
.L3683:
	add	w1, w1, 1
	lsl	w2, w22, w1
	cmp	w4, w2
	bhi	.L3683
.L3682:
	bl	BsGet
	add	w2, w0, 1
	str	w2, [x24, 2832]
	ldr	w4, [x20, 196]
	cmp	w2, w4
	bne	.L3974
.L3911:
	mov	w1, 0
.L3685:
	cmp	w4, 2
	bgt	.L3700
.L3687:
	cmp	w4, wzr
	ble	.L3675
.L3694:
	add	x0, x24, 2836
	mov	w2, 0
	b	.L3704
	.p2align 3
.L3976:
	ldr	w3, [x0]
.L3702:
	cmp	w3, 2
	add	x0, x0, 4
	bgt	.L3975
	add	w2, w2, 1
	cmp	w2, w4
	beq	.L3675
.L3704:
	mov	w3, w2
	cbnz	w1, .L3976
	str	w2, [x0]
	b	.L3702
.L3954:
	ldr	w1, [x21, 72]
	mul	w0, w0, w1
	sub	w0, w0, #1
	b	.L3757
.L3933:
	ldr	x1, .LC996
	ldr	x0, [x28, 2944]
	bl	HEVC_ue_v
	mov	w25, w0
	ldr	w3, [x19, 180]
	cmp	w0, w3
	bhi	.L3977
	cmp	w3, 1
	str	wzr, [x29, 156]
	bls	.L3655
	mov	w1, 1
	.p2align 2
.L3657:
	ldr	w0, [x29, 156]
	add	w0, w0, 1
	str	w0, [x29, 156]
	lsl	w0, w1, w0
	cmp	w3, w0
	bhi	.L3657
	b	.L3655
.L3924:
	ldr	w0, [x28, 260]
	cbz	w0, .L3612
	ldr	w0, [x28, 192]
	str	w0, [x28, 5580]
.L3613:
	mov	x0, x28
	bl	HEVC_IsNewPic
	str	w0, [x28, 5720]
	ldr	x1, .LC980
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3676:
	ldr	x1, [x29, 104]
	add	x1, x1, 12288
	ldrb	w1, [x1, 134]
.L3677:
	cmp	w1, 1
	beq	.L3978
.L3678:
	str	wzr, [x24, 2832]
	b	.L3675
.L3978:
	ldr	x1, [x28, 2952]
	add	x8, x1, x0, sxtw 2
	add	x8, x8, 16384
	ldr	w2, [x8, 196]
	cmp	w2, wzr
	ble	.L3796
	mov	x6, 4150
	sub	w2, w2, #1
	add	x6, x6, x0, sxtw 1
	ldr	w7, [x3, 28]
	add	x6, x6, x2
	mov	x2, 16596
	add	x0, x2, x0, sxtw 3
	mov	w4, 0
	add	x6, x1, x6, lsl 2
	add	x0, x1, x0
	add	x1, x1, 12288
	add	x2, x1, 132
	.p2align 2
.L3699:
	ldrsw	x1, [x0]
	add	x0, x0, 4
	add	x1, x1, 1036
	ldrsw	x1, [x2, x1, lsl 2]
	add	x3, x2, x1, lsl 2
	ldr	w3, [x3, 4168]
	cmp	w3, w7
	blt	.L3697
	cbz	w7, .L3698
	ldrsw	x3, [x8, 180]
	add	x1, x3, x1, lsl 1
	add	x1, x2, x1, lsl 2
	ldr	w1, [x1, 12392]
	cbz	w1, .L3697
.L3698:
	add	w4, w4, 1
.L3697:
	cmp	x6, x0
	bne	.L3699
	str	w4, [x24, 2832]
	b	.L3911
.L3975:
	ldr	x1, .LC1014
	mov	w4, 2
	mov	w0, 1
	bl	dprint_vfmw
.L3690:
	ldr	x1, .LC1078
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3612:
	str	wzr, [x28, 5580]
	b	.L3613
.L3946:
	ldr	x1, .LC1042
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3623:
	ldr	x1, .LC984
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3927:
	ldr	x1, .LC988
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3766:
	ldr	x1, .LC1076
	mov	w2, w0
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3955:
	ldr	x1, .LC1066
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3716:
	ldr	x1, .LC1026
	mov	w3, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3945:
	ldr	x1, .LC1038
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3966:
	ldr	x1, .LC1058
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x21, 76]
	str	w0, [x28, 5628]
	b	.L3749
.L3680:
	cmp	w4, 1
	bne	.L3678
	str	w4, [x24, 2832]
.L3912:
	mov	w1, 0
	b	.L3694
.L3969:
	ldr	x1, .LC1048
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3934:
	ldr	x1, .LC1002
	mov	w5, 16
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3944:
	ldr	x1, .LC1034
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3970:
	ldr	x1, .LC1052
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3968:
	ldr	x1, .LC1046
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3681:
	str	w22, [x24, 2832]
	ldr	w4, [x20, 196]
	cmp	w4, 1
	beq	.L3912
.L3686:
	mov	w23, 0
	mov	w22, 1
	add	x25, x24, 2828
.L3693:
	ldr	w3, [x20, 196]
	mov	w1, 0
	ldr	x0, [x28, 2944]
	cmp	w3, 1
	bls	.L3691
	.p2align 2
.L3692:
	add	w1, w1, 1
	lsl	w2, w22, w1
	cmp	w3, w2
	bhi	.L3692
.L3691:
	bl	BsGet
	add	x1, x25, x23, sxtw 2
	add	w23, w23, 1
	str	w0, [x1, 8]
	ldr	w4, [x25, 4]
	cmp	w23, w4
	blt	.L3693
	mov	w1, 1
	b	.L3685
.L3971:
	ldr	x1, .LC1018
	mov	w3, 16
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3956:
	ldr	x1, .LC1070
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3908:
	ldr	x1, .LC1028
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3700:
	ldr	x1, .LC1012
	mov	w3, 2
	mov	w2, w4
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3690
.L3977:
	ldr	x1, .LC998
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3974:
	cmp	w2, 2
	bgt	.L3688
	cmp	w2, wzr
	bgt	.L3686
	mov	w4, w2
	mov	w1, 1
	b	.L3687
	.p2align 3
.L3796:
	mov	w4, 0
	str	w4, [x24, 2832]
	b	.L3911
.L3960:
	ldr	x1, .LC1024
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3973:
	ldr	x1, .LC1022
	mov	w3, 16
	mov	w2, w22
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3905
.L3688:
	ldr	x1, .LC1010
	mov	w3, 2
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3690
	.size	HEVC_DecSliceSegmentHeader, .-HEVC_DecSliceSegmentHeader
	.align	3
.LC975:
	.xword	.LC974
	.align	3
.LC976:
	.xword	.LANCHOR3
	.align	3
.LC978:
	.xword	.LC977
	.align	3
.LC980:
	.xword	.LC979
	.align	3
.LC982:
	.xword	.LC981
	.align	3
.LC984:
	.xword	.LC983
	.align	3
.LC986:
	.xword	.LC985
	.align	3
.LC988:
	.xword	.LC987
	.align	3
.LC990:
	.xword	.LC989
	.align	3
.LC992:
	.xword	.LC991
	.align	3
.LC994:
	.xword	.LC993
	.align	3
.LC996:
	.xword	.LC995
	.align	3
.LC998:
	.xword	.LC997
	.align	3
.LC1000:
	.xword	.LC999
	.align	3
.LC1002:
	.xword	.LC1001
	.align	3
.LC1004:
	.xword	.LC1003
	.align	3
.LC1006:
	.xword	.LC1005
	.align	3
.LC1008:
	.xword	.LC1007
	.align	3
.LC1010:
	.xword	.LC1009
	.align	3
.LC1012:
	.xword	.LC1011
	.align	3
.LC1014:
	.xword	.LC1013
	.align	3
.LC1016:
	.xword	.LC1015
	.align	3
.LC1018:
	.xword	.LC1017
	.align	3
.LC1020:
	.xword	.LC1019
	.align	3
.LC1022:
	.xword	.LC1021
	.align	3
.LC1024:
	.xword	.LC1023
	.align	3
.LC1026:
	.xword	.LC1025
	.align	3
.LC1028:
	.xword	.LC1027
	.align	3
.LC1030:
	.xword	.LC1029
	.align	3
.LC1032:
	.xword	.LC1031
	.align	3
.LC1034:
	.xword	.LC1033
	.align	3
.LC1036:
	.xword	.LC1035
	.align	3
.LC1038:
	.xword	.LC1037
	.align	3
.LC1040:
	.xword	.LC1039
	.align	3
.LC1042:
	.xword	.LC1041
	.align	3
.LC1044:
	.xword	.LC1043
	.align	3
.LC1046:
	.xword	.LC1045
	.align	3
.LC1048:
	.xword	.LC1047
	.align	3
.LC1050:
	.xword	.LC1049
	.align	3
.LC1052:
	.xword	.LC1051
	.align	3
.LC1054:
	.xword	.LC1053
	.align	3
.LC1056:
	.xword	.LC1055
	.align	3
.LC1058:
	.xword	.LC1057
	.align	3
.LC1060:
	.xword	.LC1059
	.align	3
.LC1062:
	.xword	.LC1061
	.align	3
.LC1064:
	.xword	.LC1063
	.align	3
.LC1066:
	.xword	.LC1065
	.align	3
.LC1068:
	.xword	.LC1067
	.align	3
.LC1070:
	.xword	.LC1069
	.align	3
.LC1072:
	.xword	.LC1071
	.align	3
.LC1074:
	.xword	.LC1073
	.align	3
.LC1076:
	.xword	.LC1075
	.align	3
.LC1078:
	.xword	.LC1077
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FrameStoreRefFlg
	.type	HEVC_FrameStoreRefFlg, %function
HEVC_FrameStoreRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FrameStoreRefFlg, .-HEVC_FrameStoreRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrSlice
	.type	HEVC_ClearCurrSlice, %function
HEVC_ClearCurrSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 2984]
	cbz	x1, .L3981
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L3981:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrSlice, .-HEVC_ClearCurrSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrNal
	.type	HEVC_ClearCurrNal, %function
HEVC_ClearCurrNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearCurrSlice
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrNal, .-HEVC_ClearCurrNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAllSlice
	.type	HEVC_ClearAllSlice, %function
HEVC_ClearAllSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	w2, [x20, 168]
	cbz	w2, .L3990
	.p2align 2
.L3993:
	ldr	x0, [x20, 3024]
	ldr	x0, [x0, w19, uxtw 3]
	mov	x1, x0
	cbz	x0, .L3988
	ldr	w0, [x20, 276]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 3024]
	str	xzr, [x0, w19, uxtw 3]
	ldr	w2, [x20, 168]
.L3988:
	add	w19, w19, 1
	cmp	w2, w19
	bhi	.L3993
.L3990:
	strb	wzr, [x20, 14]
	mov	w0, 2
	str	wzr, [x20, 204]
	str	w0, [x20, 176]
	mov	w0, 0
	str	wzr, [x20, 260]
	str	wzr, [x20, 268]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	add	x19, x20, 3552
	bl	_mcount
	add	x22, x20, 3688
	mov	x0, x20
	bl	HEVC_ClearAllSlice
	.p2align 2
.L4004:
	ldr	x0, [x19, 136]
	cbz	x0, .L3998
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L3998:
	ldr	x0, [x19, 272]
	cbz	x0, .L3999
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L3999:
	ldr	x0, [x19, 408]
	cbz	x0, .L4000
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L4000:
	ldr	x0, [x19, 544]
	cbz	x0, .L4001
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L4001:
	ldr	x0, [x19, -136]
	str	xzr, [x19, 136]
	str	xzr, [x19, 272]
	str	xzr, [x19, 408]
	str	xzr, [x19, 544]
	cbz	x0, .L4002
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L4002:
	ldr	x0, [x19]
	cbz	x0, .L4003
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
.L4003:
	str	xzr, [x19, -136]
	add	x19, x19, 8
	str	xzr, [x19, -8]
	cmp	x22, x19
	bne	.L4004
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	beq	.L4077
.L4005:
	ldr	x0, [x20, 3008]
	ldr	w0, [x0, 184]
	add	w0, w0, 1
	str	w0, [x20, 3376]
.L4006:
	cmp	w0, 17
	bhi	.L4078
.L4007:
	add	x4, x20, 3328
	ldr	x22, .LC1081
	add	x19, x20, 12288
	mov	x2, 280
	mov	w1, 0
	add	x0, x19, 1900
	ldr	x3, [x22, 96]
	mov	w23, 16
	stp	wzr, wzr, [x4, 52]
	stp	wzr, wzr, [x4, 60]
	str	wzr, [x20, 3396]
	str	wzr, [x20, 3404]
	str	wzr, [x20, 3408]
	blr	x3
	str	w23, [x20, 14188]
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 280
	add	x0, x19, 2180
	str	wzr, [x20, 14192]
	blr	x3
	str	w23, [x20, 14468]
	add	x1, x20, 3064
	add	x0, x20, 3200
	str	wzr, [x20, 14472]
	.p2align 2
.L4008:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L4008
	add	x1, x20, 3336
	str	wzr, [x20, 5636]
	.p2align 2
.L4009:
	str	xzr, [x0], 8
	cmp	x0, x1
	bne	.L4009
	str	wzr, [x20, 5640]
	cbnz	w21, .L4010
	ldr	x0, [x20, 3040]
	ldr	w0, [x0, 960]
	cmp	w0, 1
	beq	.L4010
	ldr	w0, [x20, 184]
	cbz	w0, .L4030
.L4026:
	sub	w1, w0, #1
	add	x0, x20, 2168
	add	x1, x1, 543
	add	x1, x20, x1, lsl 2
	.p2align 2
.L4029:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L4029
.L4030:
	ldr	w2, [x20, 168]
	mov	w19, 0
	cbz	w2, .L4028
	.p2align 2
.L4056:
	ldr	x0, [x20, 3024]
	uxtw	x21, w19
	ldr	x0, [x0, w19, uxtw 3]
	add	w19, w19, 1
	mov	x1, x0
	cbz	x0, .L4031
	ldr	x3, [x20, 2984]
	cmp	x0, x3
	beq	.L4031
	ldr	w0, [x20, 276]
	bl	HEVC_ReleaseNAL
	ldr	x0, [x20, 3024]
	str	xzr, [x0, x21, lsl 3]
	ldr	w2, [x20, 168]
.L4031:
	cmp	w2, w19
	bhi	.L4056
.L4028:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4010:
	ldrb	w1, [x20, 1]
	mov	w0, 20
	stp	w0, w0, [x20, 180]
	cmp	w1, 1
	beq	.L4079
.L4012:
	mov	x0, x20
	bl	HEVC_ArrangeMem
.L4021:
	cbz	w0, .L4022
	cmp	w0, 2
	beq	.L4074
	ldr	x22, .LC1079
.L4023:
	ldr	x1, .LC1088
	add	x2, x22, 200
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4078:
	ldr	x22, .LC1079
	mov	w4, 17
	ldr	x1, .LC1080
	mov	w3, w4
	add	x2, x22, 200
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 17
	str	w0, [x20, 3376]
	b	.L4007
	.p2align 3
.L4077:
	ldr	x0, [x20, 3040]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L4005
	ldr	w0, [x20, 2392]
	cbz	w0, .L4005
	ldr	x1, [x20, 3008]
	ldr	w1, [x1, 184]
	mul	w0, w0, w1
	add	w0, w0, 1
	str	w0, [x20, 3376]
	b	.L4006
	.p2align 3
.L4079:
	ldr	x0, [x20, 3040]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L4012
	ldr	w9, [x20, 2392]
	ldr	x13, [x20, 3008]
	cbz	w9, .L4080
	ldp	w8, w7, [x13, 140]
	mov	w19, 0
	mov	w21, 0
	neg	w11, w8
	neg	w10, w7
	mov	w1, 0
	mov	w3, 0
	mov	w2, 8160
	sub	w8, w8, #1
	sub	w7, w7, #1
	ldr	w12, [x20, 5600]
	b	.L4017
	.p2align 3
.L4015:
	cmp	w21, w1
	csel	w21, w21, w1, cs
	cmp	w19, w0
	csel	w19, w19, w0, cs
	sub	w1, w21, #32
	sub	w0, w19, #32
	cmp	w1, w2
	ccmp	w0, w2, 2, ls
	bhi	.L4016
	uxtb	w3, w4
	cmp	w9, w3
	mov	w1, w3
	bls	.L4081
.L4017:
	add	x0, x20, x3, uxtb 2
	cmp	w12, w1
	add	w4, w3, 1
	ldr	w1, [x0, 2400]
	ldr	w0, [x0, 2408]
	add	w1, w8, w1
	add	w0, w7, w0
	and	w1, w1, w11
	and	w0, w0, w10
	bne	.L4015
	ldr	w14, [x13, 128]
	ldp	w6, w5, [x13, 188]
	lsl	w6, w6, w14
	lsl	w5, w5, w14
	cmp	w1, w6
	csel	w1, w1, w6, cs
	cmp	w0, w5
	csel	w0, w0, w5, cs
	b	.L4015
.L4016:
	ldr	x22, .LC1079
	mov	w5, w19
	ldr	x1, .LC1085
	mov	w4, w21
	add	x2, x22, 216
	mov	w0, 0
	bl	dprint_vfmw
	b	.L4023
	.p2align 3
.L4022:
	ldr	w0, [x20, 276]
	bl	FSP_GetTotalValidFsNum
	cmp	w0, 20
	mov	w0, 20
	ble	.L4082
	str	w0, [x20, 180]
.L4083:
	ldr	w0, [x20, 184]
	cbnz	w0, .L4026
	b	.L4030
.L4082:
	ldr	w0, [x20, 276]
	bl	FSP_GetTotalValidFsNum
	str	w0, [x20, 180]
	b	.L4083
.L4074:
	add	x0, x20, 4096
	add	x0, x0, 2848
	bl	ResetVoQueue
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -2
	ldp	x29, x30, [sp], 96
	ret
.L4081:
	ldr	x3, [x22, 96]
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 72
	ldr	w22, [x20, 3376]
	blr	x3
	ldr	x0, [x20, 3040]
	stp	w21, w19, [x29, 76]
	stp	w21, w19, [x29, 84]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L4019
	sxtb	w2, w22
	strb	w2, [x29, 73]
.L4033:
	ldr	w0, [x20, 276]
	add	x1, x29, 72
	strb	w2, [x29, 75]
	bl	FSP_ConfigInstance
	cbnz	w0, .L4084
	ldr	x1, [x20, 3040]
	add	x3, x29, 68
	ldr	w0, [x20, 276]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	b	.L4021
.L4019:
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x29, 73]
	b	.L4033
.L4080:
	ldr	x22, .LC1079
	mov	w3, 0
	ldr	x1, .LC1083
	mov	w0, 0
	add	x2, x22, 216
	bl	dprint_vfmw
	b	.L4023
.L4084:
	ldr	x22, .LC1079
	mov	w0, 1
	ldr	x1, .LC1086
	add	x2, x22, 216
	bl	dprint_vfmw
	b	.L4023
	.size	HEVC_InitDPB, .-HEVC_InitDPB
	.align	3
.LC1079:
	.xword	.LANCHOR3
	.align	3
.LC1080:
	.xword	.LC382
	.align	3
.LC1081:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1083:
	.xword	.LC1082
	.align	3
.LC1085:
	.xword	.LC1084
	.align	3
.LC1086:
	.xword	.LC234
	.align	3
.LC1088:
	.xword	.LC1087
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAllNal
	.type	HEVC_ClearAllNal, %function
HEVC_ClearAllNal:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	mov	w21, 104
	bl	_mcount
	ldr	w2, [x20, 168]
	cmn	w2, #1
	bne	.L4090
	b	.L4089
	.p2align 3
.L4087:
	add	w0, w2, 1
	cmp	w0, w19
	bls	.L4089
.L4090:
	umull	x1, w19, w21
	ldr	x0, [x20, 3032]
	add	w19, w19, 1
	add	x1, x0, x1
	ldr	w0, [x1, 32]
	cmp	w0, 1
	bne	.L4087
	ldr	w0, [x20, 276]
	bl	HEVC_ReleaseNAL
	ldr	w2, [x20, 168]
	add	w0, w2, 1
	cmp	w0, w19
	bhi	.L4090
.L4089:
	strb	wzr, [x20, 9]
	mov	w0, 0
	str	wzr, [x20, 148]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_ClearAllNal, .-HEVC_ClearAllNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitDecPara
	.type	HEVC_InitDecPara, %function
HEVC_InitDecPara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	add	x23, x21, 4096
	add	x25, x21, 12288
	bl	_mcount
	add	x19, x25, 2464
	ldr	x1, .LC1090
	mov	w0, 22
	mov	w20, 0
	mov	w26, 20
	mov	w24, 16
	bl	dprint_vfmw
	strb	wzr, [x21, 4]
	mov	w0, -2147483647
	mov	w2, 1
	mov	w1, 2147483647
	strb	w2, [x21, 6]
	strb	w2, [x21, 7]
	stp	w0, w0, [x21, 212]
	stp	w1, w1, [x21, 244]
	stp	w0, w0, [x21, 252]
	strb	wzr, [x21, 12]
	mov	x0, x21
	strb	wzr, [x21, 5]
	strb	wzr, [x21, 13]
	bl	HEVC_ClearAllNal
	add	x0, x23, 2848
	bl	ResetVoQueue
	ldr	x22, .LC1091
	.p2align 2
.L4094:
	strb	wzr, [x19]
	add	x0, x19, 88
	strb	wzr, [x19, 1]
	mov	x2, 640
	strb	wzr, [x19, 2]
	mov	w1, 0
	str	wzr, [x19, 8]
	stp	w26, w24, [x19, 20]
	str	wzr, [x19, 48]
	ldr	x3, [x22, 96]
	blr	x3
	str	w20, [x19, 236]
	add	w20, w20, 1
	str	wzr, [x19, 56]
	str	x19, [x19, 80]
	cmp	w20, 20
	add	x19, x19, 728
	bne	.L4094
	add	x0, x21, 2168
	add	x1, x21, 2248
	.p2align 2
.L4095:
	str	wzr, [x0], 4
	cmp	x1, x0
	bne	.L4095
	ldr	w1, [x21, 168]
	mov	w0, 0
	cbz	w1, .L4099
	.p2align 2
.L4101:
	ldr	x1, [x21, 3024]
	str	xzr, [x1, w0, uxtw 3]
	add	w0, w0, 1
	ldr	w1, [x21, 168]
	cmp	w1, w0
	bhi	.L4101
.L4099:
	ldr	x3, [x22, 96]
	mov	x2, 280
	mov	w1, 0
	add	x0, x25, 1900
	mov	w19, 16
	blr	x3
	str	w19, [x21, 14188]
	ldr	x3, [x22, 96]
	mov	w1, 0
	mov	x2, 280
	add	x0, x25, 2180
	blr	x3
	str	w19, [x21, 14468]
	add	x0, x21, 3824
	add	x1, x21, 3960
	.p2align 2
.L4097:
	str	xzr, [x0, -136]
	add	x0, x0, 8
	str	xzr, [x0, -8]
	str	xzr, [x0, 128]
	str	xzr, [x0, 264]
	cmp	x1, x0
	bne	.L4097
	add	x2, x21, 3328
	mov	w0, 17
	add	x19, x21, 3336
	stp	w0, wzr, [x2, 48]
	stp	wzr, wzr, [x2, 56]
	str	wzr, [x21, 3392]
	add	x0, x21, 3200
	str	wzr, [x21, 3396]
	.p2align 2
.L4100:
	str	xzr, [x0, -136]
	add	x0, x0, 8
	str	xzr, [x0, -8]
	cmp	x19, x0
	bne	.L4100
	ldr	x3, [x22, 96]
	mov	w20, 2
	mov	x2, 1376
	str	w20, [x21, 176]
	mov	w1, 0
	add	x0, x23, 1472
	str	wzr, [x21, 204]
	str	wzr, [x21, 260]
	str	wzr, [x21, 268]
	str	xzr, [x21, 2984]
	blr	x3
	strb	wzr, [x21, 8]
	mov	w1, 8
	mov	w3, 1
	stp	w1, w1, [x21, 196]
	add	x1, x21, 2048
	strb	w3, [x21, 3]
	str	wzr, [x21, 172]
	mov	w2, 20
	stp	w2, w2, [x21, 180]
	ldr	x4, [x22, 96]
	mov	w0, 6
	mov	w2, 16
	stp	w0, w20, [x1, 208]
	stp	w0, w0, [x1, 200]
	mov	w1, 64
	str	w2, [x21, 360]
	str	w1, [x21, 364]
	mov	w2, 256
	mov	w1, 1025
	str	w20, [x21, 5588]
	str	w3, [x21, 5720]
	mov	x0, x19
	str	w2, [x21, 368]
	mov	x2, 40
	str	w1, [x21, 372]
	mov	w1, 0
	blr	x4
	str	x19, [x21, 2944]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	HEVC_InitDecPara, .-HEVC_InitDecPara
	.align	3
.LC1090:
	.xword	.LC1089
	.align	3
.LC1091:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearCurrPic
	.type	HEVC_ClearCurrPic, %function
HEVC_ClearCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	ldr	x0, [x19, 4920]
	cbz	x0, .L4108
	ldr	w1, [x0, 28]
	mov	w2, 1
	ldr	w0, [x19, 276]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 4920]
	str	wzr, [x0, 48]
	str	xzr, [x19, 4920]
.L4108:
	add	x19, x19, 4096
	mov	w0, 0
	strb	wzr, [x19, 761]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearCurrPic, .-HEVC_ClearCurrPic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearAll
	.type	HEVC_ClearAll, %function
HEVC_ClearAll:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_InitDPB
	cbnz	w20, .L4115
	add	x0, x19, 4096
	add	x0, x0, 2848
	bl	ResetVoQueue
	ldr	w0, [x19, 276]
	bl	FSP_EmptyInstance
	mov	x0, x19
	bl	HEVC_InitDecPara
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4115:
	add	x1, x19, 4096
	ldr	w0, [x19, 276]
	add	x1, x1, 2848
	bl	FSP_ClearNotInVoQueue
	mov	x0, x19
	bl	HEVC_InitDecPara
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x28, 5604]
	tbnz	w1, #31, .L4146
	ldr	w2, [x28, 164]
	mov	w0, 0
	cmp	w1, w2
	bge	.L4160
	ldr	x3, [x28, 2968]
	mov	w21, 5036
	mov	w0, 12668
	ldr	x25, [x28, 2960]
	ldr	w2, [x28, 5600]
	mov	w5, 1
	smaddl	x21, w1, w21, x3
	ldr	w4, [x28, 292]
	ldr	w3, [x28, 300]
	add	x2, x28, x2, lsl 2
	ldr	w23, [x21, 32]
	mov	w6, w4
	str	w5, [x29, 120]
	mov	w7, w3
	mov	w4, 24912
	ldr	w3, [x28, 288]
	smull	x23, w23, w0
	str	w3, [x29, 112]
	add	x0, x25, x23
	str	x0, [x29, 128]
	mov	x5, x0
	ldr	w3, [x28, 296]
	ldr	w19, [x28, 304]
	ldr	w0, [x0, 48]
	ldr	w20, [x28, 308]
	str	w3, [x29, 108]
	umull	x0, w0, w4
	ldr	x3, [x28, 2952]
	str	w1, [x2, 236]
	add	x1, x3, x0
	ldr	w0, [x21, 32]
	str	w0, [x2, 228]
	stp	w7, w6, [x29, 100]
	ldr	w0, [x5, 48]
	str	w0, [x2, 220]
	ldr	w0, [x28, 172]
	ldr	w2, [x5, 128]
	cmp	w0, wzr
	ldr	w0, [x5, 64]
	cset	w3, eq
	cmp	w2, w7
	cset	w22, ne
	str	w3, [x29, 124]
	cmp	w6, w0
	beq	.L4174
.L4118:
	ldr	w0, [x29, 124]
	ldr	w2, [x1, 4]
	orr	w22, w0, w22
	ldr	w0, [x29, 120]
	orr	w22, w22, w0
	ldr	x0, [x28, 3000]
	ldr	w0, [x0, 4]
	cmp	w2, w0
	beq	.L4175
.L4119:
	ldr	x0, .LC1092
	mov	w27, 24912
	strb	wzr, [x1, 2]
	mov	x26, -24912
	ldr	x5, [x0, 104]
	ldr	w0, [x28, 156]
	ldr	x2, [x28, 2952]
	smaddl	x0, w0, w27, x26
	add	x0, x2, x0
	mov	x2, 24912
	blr	x5
	ldr	w0, [x28, 156]
	ldr	x1, [x28, 2952]
	smaddl	x0, w0, w27, x26
	add	x0, x1, x0
	str	x0, [x28, 3000]
.L4120:
	ldr	x0, [x28, 3008]
	mov	w26, w22
	ldr	x1, [x29, 128]
	ldr	w2, [x0, 56]
	ldr	w1, [x1, 56]
	cmp	w2, w1
	beq	.L4176
.L4145:
	ldr	x2, [x29, 128]
	ldr	w0, [x0, 184]
	ldr	w1, [x2, 184]
	cmp	w1, w0
	mov	x1, x2
	mov	x0, x28
	cset	w2, ne
	str	w2, [x29, 116]
	bl	HEVC_UpdatePicSPS
	ldr	x0, [x28, 3016]
	ldr	w1, [x0, 28]
	ldr	w0, [x21, 28]
	cmp	w1, w0
	beq	.L4177
.L4123:
	ldr	x1, [x29, 128]
	mov	x0, x28
	mov	x2, x21
	bl	HEVC_UpdatePicPPS
	ldr	w0, [x28, 304]
	cmp	w19, w0
	mov	w0, 1
	beq	.L4178
.L4125:
	ldr	w1, [x29, 116]
	ldr	x2, [x28, 3040]
	orr	w0, w1, w0
	str	w0, [x29, 96]
	ldr	x0, [x28, 3008]
	ldr	w1, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w1
	csel	w0, w0, w1, cs
	str	w0, [x2, 972]
	ldr	x23, [x28, 3000]
	add	x23, x23, 12288
	add	x23, x23, 132
	ldr	w13, [x23, 4124]
	cbz	w13, .L4139
	add	w27, w13, 1
	mov	w0, 2
	cmp	w27, 2
	mov	w26, 0
	csel	w27, w27, w0, ls
	str	x23, [x29, 136]
	str	w27, [x28, 2392]
	mov	w23, w27
	mov	w27, w26
	mov	w21, 1
	cmp	w23, w27
	ldr	x20, .LC1094
	bls	.L4139
	.p2align 2
.L4138:
	add	w22, w27, 1
	sxtw	x19, w27
	cmp	w23, w22
	ldr	x26, [x28, 3000]
	bls	.L4136
	add	x26, x26, 12288
	lsl	x25, x19, 5
	add	x26, x26, 132
	add	x25, x25, x19, lsl 3
	mov	w24, w22
	add	x25, x26, x25
	b	.L4135
	.p2align 3
.L4133:
	ldrb	w4, [x28, 2]
	cmp	w4, 1
	beq	.L4134
	strb	w21, [x28, 2]
	ldr	w6, [x3, 12412]
	ldr	w7, [x3, 12416]
	ldr	w4, [x25, 12416]
	ldr	w3, [x25, 12412]
	bl	dprint_vfmw
.L4134:
	cmp	w24, w23
	bcs	.L4136
.L4135:
	sxtw	x0, w24
	ldr	w7, [x25, 12412]
	lsl	x4, x0, 5
	mov	w5, w24
	add	x4, x4, x0, lsl 3
	add	w24, w24, 1
	add	x4, x26, x4
	mov	w2, w27
	mov	x3, x4
	mov	x1, x20
	mov	w0, 32
	ldr	w6, [x4, 12412]
	cmp	w7, w6
	bne	.L4133
	ldr	w4, [x4, 12416]
	ldr	w6, [x25, 12416]
	cmp	w6, w4
	bne	.L4133
	cmp	w24, w23
	bcc	.L4135
	.p2align 2
.L4136:
	ldr	x1, [x29, 136]
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 3
	add	x5, x28, x19, lsl 2
	add	x0, x1, x0
	ldr	w1, [x5, 2400]
	ldr	w3, [x0, 12412]
	cmp	w1, w3
	bne	.L4131
	ldr	w0, [x0, 12416]
	ldr	w1, [x5, 2408]
	cmp	w1, w0
	beq	.L4137
.L4131:
	lsl	x0, x19, 5
	str	w3, [x5, 2400]
	add	x19, x0, x19, lsl 3
	ldr	x0, [x29, 136]
	ldr	x1, .LC1096
	mov	w2, w27
	add	x19, x0, x19
	mov	w0, 32
	ldr	w4, [x19, 12416]
	str	w4, [x5, 2408]
	bl	dprint_vfmw
	str	wzr, [x28, 2396]
.L4137:
	ldr	w23, [x28, 2392]
	mov	w27, w22
	cmp	w23, w27
	bhi	.L4138
.L4139:
	ldr	x0, [x29, 128]
	ldr	w1, [x29, 112]
	ldr	w0, [x0, 56]
	cmp	w0, w1
	beq	.L4179
.L4127:
	ldp	w3, w1, [x29, 100]
	ldr	w2, [x29, 108]
	mov	x0, x28
	ldr	w4, [x29, 116]
	bl	HEVC_GetReRangeFlag
	cbnz	w0, .L4141
	ldr	x0, [x28, 3040]
	ldr	w1, [x0, 960]
	cmp	w1, 1
	beq	.L4141
.L4142:
	str	wzr, [x0, 976]
.L4140:
	ldr	w0, [x28, 2368]
	cbnz	w0, .L4144
	mov	x0, x28
	bl	HEVC_AllocFrameStore
	mov	w19, w0
	cbnz	w0, .L4180
.L4144:
	mov	x0, x28
	bl	HEVC_InitPicInfo
	mov	w0, 0
.L4160:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L4141:
	mov	w1, 1
	mov	x0, x28
	bl	HEVC_InitDPB
	cmn	w0, #2
	beq	.L4160
	cbnz	w0, .L4143
	ldr	x0, [x28, 3040]
	b	.L4142
.L4146:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 144
	ret
.L4174:
	ldr	w0, [x5, 68]
	ldr	w2, [x29, 108]
	cmp	w0, w2
	cset	w0, ne
	str	w0, [x29, 120]
	b	.L4118
.L4176:
	ldrb	w1, [x25, x23]
	str	wzr, [x29, 116]
	cmp	w1, wzr
	cset	w1, ne
	orr	w1, w22, w1
	cbnz	w1, .L4145
	ldr	x0, [x28, 3016]
	ldr	w1, [x0, 28]
	ldr	w0, [x21, 28]
	cmp	w1, w0
	bne	.L4123
.L4177:
	ldrb	w0, [x21, 1]
	cmp	w0, wzr
	cset	w0, ne
	orr	w3, w26, w0
	cbnz	w3, .L4123
	ldr	w0, [x28, 304]
	cmp	w19, w0
	mov	w0, 1
	bne	.L4125
.L4178:
	ldr	w0, [x28, 308]
	cmp	w0, w20
	cset	w0, ne
	b	.L4125
.L4175:
	ldrb	w0, [x1, 2]
	ldr	w2, [x29, 124]
	cmp	w0, wzr
	cset	w0, ne
	orr	w0, w2, w0
	cbz	w0, .L4120
	b	.L4119
	.p2align 3
.L4179:
	ldp	w1, w0, [x29, 120]
	orr	w26, w0, w1
	ldr	w0, [x29, 96]
	orr	w26, w26, w0
	cbnz	w26, .L4127
	ldr	x0, [x28, 3040]
	ldr	w0, [x0, 960]
	cmp	w0, 1
	bne	.L4140
	b	.L4127
	.p2align 3
.L4180:
	ldr	x1, .LC1100
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L4160
.L4143:
	ldr	x1, .LC1098
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x28
	bl	HEVC_ClearAll
	mov	w0, -1
	b	.L4160
	.size	HEVC_InitPic, .-HEVC_InitPic
	.align	3
.LC1092:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1094:
	.xword	.LC1093
	.align	3
.LC1096:
	.xword	.LC1095
	.align	3
.LC1098:
	.xword	.LC1097
	.align	3
.LC1100:
	.xword	.LC1099
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputCurrPic
	.type	HEVC_OutputCurrPic, %function
HEVC_OutputCurrPic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 4096
	bl	_mcount
	ldr	x20, [x19, 4920]
	mov	x2, 640
	ldr	w3, [x19, 4896]
	add	x1, x21, 832
	add	x0, x20, 88
	str	w3, [x20, 16]
	bl	memcpy
	mov	x0, x19
	mov	x1, x20
	bl	HEVC_GetImagePara
	ldrb	w0, [x21, 760]
	cbnz	w0, .L4189
.L4182:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_OutputFrame
	mov	w1, 0
	cbnz	w0, .L4190
.L4183:
	mov	w0, w1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4189:
	ldr	w0, [x19, 276]
	mov	w2, 1
	ldr	w1, [x20, 28]
	bl	FSP_SetRef
	b	.L4182
	.p2align 3
.L4190:
	ldr	x2, .LC1101
	mov	w0, 0
	ldr	x1, .LC1103
	add	x2, x2, 240
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w1, -1
	b	.L4183
	.size	HEVC_OutputCurrPic, .-HEVC_OutputCurrPic
	.align	3
.LC1101:
	.xword	.LANCHOR3
	.align	3
.LC1103:
	.xword	.LC1102
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FirstFrameFastOut
	.type	HEVC_FirstFrameFastOut, %function
HEVC_FirstFrameFastOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	mov	w20, w0
	cbnz	w0, .L4194
	ldr	x0, [x19, 4920]
	mov	w2, 2
	mov	w1, 1
	str	w2, [x0, 52]
	str	w1, [x19, 12808]
	ldr	w0, [x19, 4864]
	ldr	w2, [x19, 4868]
	add	x0, x19, x0, lsl 2
	str	w2, [x0, 212]
	ldr	x0, [x19, 4920]
	strb	w1, [x0, 2]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4194:
	ldr	x2, .LC1104
	mov	w0, 1
	ldr	x1, .LC1106
	add	x2, x2, 264
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_FirstFrameFastOut, .-HEVC_FirstFrameFastOut
	.align	3
.LC1104:
	.xword	.LANCHOR3
	.align	3
.LC1106:
	.xword	.LC1105
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputFrmToVO
	.type	HEVC_OutputFrmToVO, %function
HEVC_OutputFrmToVO:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L4200
	mov	x1, x19
	mov	x0, x20
	bl	HEVC_GetImagePara
	mov	x1, x19
	mov	x0, x20
	bl	HEVC_CheckFrameStore
	cbz	w0, .L4204
	cmn	w0, #3
	bne	.L4205
.L4199:
	mov	w0, 0
.L4196:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4204:
	mov	x1, x19
	mov	x0, x20
	bl	HEVC_OutputFrame
	cbz	w0, .L4199
	ldr	x2, .LC1107
	mov	w0, 0
	ldr	x1, .LC1108
	add	x2, x2, 288
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x20
	bl	HEVC_ClearAll
	mov	w0, -1
	b	.L4196
	.p2align 3
.L4205:
	ldr	x1, .LC1110
	mov	w3, w0
	mov	w2, 11897
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 236]
	mov	x0, x20
	bl	HEVC_DECRecycleImage
	mov	w0, -1
	b	.L4196
	.p2align 3
.L4200:
	mov	w0, -1
	b	.L4196
	.size	HEVC_OutputFrmToVO, .-HEVC_OutputFrmToVO
	.align	3
.LC1107:
	.xword	.LANCHOR3
	.align	3
.LC1108:
	.xword	.LC1102
	.align	3
.LC1110:
	.xword	.LC1109
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DirectOutput
	.type	HEVC_DirectOutput, %function
HEVC_DirectOutput:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 4096
	bl	_mcount
	ldr	x19, [x20, 4920]
	mov	w4, 2
	mov	w3, 1
	add	x1, x21, 832
	mov	x2, 640
	add	x0, x19, 88
	str	w4, [x19, 48]
	strb	wzr, [x19, 1]
	strb	w3, [x19, 2]
	ldr	w3, [x20, 4872]
	str	w3, [x19, 12]
	ldr	w3, [x20, 4896]
	str	w3, [x19, 16]
	bl	memcpy
	str	wzr, [x19, 56]
	ldr	w1, [x19, 28]
	mov	w2, 0
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	mov	x1, x19
	mov	x0, x20
	bl	HEVC_OutputFrmToVO
	str	wzr, [x19, 48]
	ldr	x3, .LC1111
	mov	w20, w0
	mov	x2, 712
	mov	w1, 0
	add	x0, x21, 760
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_DirectOutput, .-HEVC_DirectOutput
	.align	3
.LC1111:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IModeProcess
	.type	HEVC_IModeProcess, %function
HEVC_IModeProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_DirectOutput
	ldr	w2, [x19, 184]
	ldr	w1, [x19, 4892]
	cmp	w1, w2
	beq	.L4208
	add	x1, x19, x1, uxtw 2
	str	wzr, [x1, 2168]
	str	w2, [x19, 4892]
.L4208:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IModeProcess, .-HEVC_IModeProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RemoveFrmFullDPB
	.type	HEVC_RemoveFrmFullDPB, %function
HEVC_RemoveFrmFullDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w4, [x19, 3380]
	cbz	w4, .L4209
	mov	w3, 2147483647
	mov	w20, -1
	mov	w0, 0
	.p2align 2
.L4212:
	add	x1, x19, x0, sxtw 3
	ldr	x1, [x1, 3688]
	ldr	w2, [x1, 8]
	cmp	w2, w3
	bge	.L4211
	ldr	w1, [x1]
	ands	w1, w1, 16776960
	csel	w3, w3, w2, ne
	cmp	w1, wzr
	csel	w20, w20, w0, ne
.L4211:
	add	w0, w0, 1
	cmp	w0, w4
	bne	.L4212
	cmn	w20, #1
	beq	.L4209
	add	x1, x19, x20, sxtw 3
	mov	w3, 1
	mov	x0, x19
	ldr	x2, [x1, 3688]
	strb	w3, [x2, 2]
	ldr	x1, [x1, 3688]
	bl	HEVC_OutputFrmToVO
	mov	w1, w20
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
.L4209:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_RemoveFrmFullDPB, .-HEVC_RemoveFrmFullDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputFrmFromDPB
	.type	HEVC_OutputFrmFromDPB, %function
HEVC_OutputFrmFromDPB:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 3380]
	ldr	w28, [x19, 4864]
	cbz	w2, .L4221
	ldr	x0, .LC1112
	uxtw	x22, w28
	ldr	x25, .LC1114
	mov	w23, 0
	mov	w20, 0
	add	x22, x22, 52
	add	x24, x0, 312
	b	.L4224
	.p2align 3
.L4222:
	add	w20, w20, 1
	cmp	w2, w20
	bls	.L4255
.L4224:
	add	x21, x19, x20, uxtw 3
	ldr	x0, [x21, 3688]
	ldrb	w1, [x0, 2]
	cbnz	w1, .L4222
	ldr	w1, [x0, 32]
	cmp	w28, w1
	bne	.L4222
	add	x1, x19, x22, lsl 2
	ldr	w3, [x0, 8]
	ldr	w4, [x1, 4]
	cmp	w3, w4
	blt	.L4223
	add	w20, w20, 1
	add	w23, w23, 1
	cmp	w2, w20
	bhi	.L4224
	.p2align 2
.L4255:
	ldr	w0, [x19, 2376]
	cmp	w0, 1
	beq	.L4239
.L4225:
	ldr	w0, [x19, 5592]
	ldr	x1, [x19, 3008]
	add	x0, x1, x0, lsl 2
	ldr	w21, [x0, 360]
.L4227:
	cbz	w2, .L4240
	ldr	x26, .LC1112
	uxtw	x22, w28
	add	x7, x22, 52
	ldr	x25, .LC1116
	add	x0, x26, 312
	mov	w20, 0
	lsl	x26, x7, 2
	mov	x24, x0
	str	x0, [x29, 112]
	str	wzr, [x29, 124]
	.p2align 2
.L4238:
	add	x27, x19, x20, uxtw 3
	ldr	x0, [x27, 3688]
	ldrb	w1, [x0, 2]
	cbnz	w1, .L4229
	ldr	w3, [x0, 32]
	cmp	w28, w3
	beq	.L4256
.L4229:
	add	x3, x19, x26
	ldr	w3, [x3, 4]
.L4231:
	cbz	w3, .L4234
	ldr	w4, [x19, 356]
	cmp	w4, 1
	beq	.L4234
.L4235:
	cbnz	w1, .L4233
	ldr	w1, [x19, 5580]
	ldr	w3, [x0, 8]
	add	w1, w1, 100
	cmp	w3, w1
	ble	.L4233
	add	x3, x19, x22, lsl 2
	mov	w1, -2147483647
	ldr	w4, [x3, 244]
	cmp	w4, w1
	beq	.L4233
	ldr	w1, [x19, 356]
	cmp	w1, 1
	beq	.L4257
	.p2align 2
.L4233:
	add	w20, w20, 1
	cmp	w2, w20
	bhi	.L4238
.L4254:
	ldr	w0, [x29, 124]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L4234:
	ldr	w4, [x0, 8]
	cmp	w3, w4
	ble	.L4235
	cbz	w1, .L4258
.L4236:
	mov	x2, x24
	mov	x1, x25
	mov	w0, 31
	bl	dprint_vfmw
	ldr	w2, [x19, 3380]
	b	.L4233
	.p2align 3
.L4256:
	add	x9, x19, x22, lsl 2
	ldr	w4, [x0, 8]
	ldr	w3, [x9, 212]
	cmp	w4, w3
	ble	.L4231
	ldr	w10, [x19, 5592]
	add	x8, x19, 4096
	add	x8, x8, 1472
	cmp	w10, 7
	ccmp	w21, w23, 2, ls
	bcs	.L4231
	ldr	w8, [x8, 12]
	cmp	w4, w8
	blt	.L4232
	add	x4, x19, x22
	ldrb	w4, [x4, 4]
	cbz	w4, .L4231
.L4232:
	mov	w1, 1
	strb	w1, [x0, 2]
	mov	x0, x19
	str	x9, [x29, 104]
	ldr	x1, [x27, 3688]
	sub	w23, w23, #1
	bl	HEVC_OutputFrmToVO
	str	w0, [x29, 124]
	ldr	x0, [x27, 3688]
	ldr	x9, [x29, 104]
	ldr	w0, [x0, 8]
	str	w0, [x9, 212]
	ldr	w2, [x19, 3380]
	b	.L4233
	.p2align 3
.L4258:
	ldr	w1, [x0, 28]
	mov	w2, 0
	ldr	w0, [x19, 276]
	bl	FSP_SetDisplay
	ldr	x0, [x27, 3688]
	ldr	w4, [x0, 8]
	add	x0, x19, x26
	ldr	w3, [x0, 4]
	b	.L4236
	.p2align 3
.L4223:
	mov	x2, x24
	mov	x1, x25
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x21, 3688]
	mov	w2, 0
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_SetDisplay
	ldr	w2, [x19, 3380]
	b	.L4222
.L4221:
	ldr	w0, [x19, 2376]
	mov	w23, 0
	cmp	w0, 1
	bne	.L4225
	.p2align 2
.L4239:
	ldr	x3, [x19, 3008]
	mov	w21, 0
	add	x0, x3, 360
	add	x3, x3, 392
	.p2align 2
.L4226:
	ldr	w1, [x0], 4
	cmp	w21, w1
	csel	w21, w21, w1, cs
	cmp	x3, x0
	bne	.L4226
	b	.L4227
	.p2align 3
.L4257:
	strb	w1, [x0, 2]
	mov	x0, x19
	str	x3, [x29, 104]
	sub	w23, w23, #1
	ldr	x1, [x27, 3688]
	bl	HEVC_OutputFrmToVO
	str	w0, [x29, 124]
	ldr	x3, [x29, 104]
	ldr	w4, [x19, 5580]
	ldr	w0, [x3, 212]
	cmp	w4, w0
	bge	.L4237
	sub	w0, w4, #1
	str	w0, [x3, 212]
.L4237:
	ldr	x0, [x27, 3688]
	ldr	x2, [x29, 112]
	ldr	x1, .LC1118
	ldr	w3, [x0, 8]
	mov	w0, 31
	bl	dprint_vfmw
	ldr	w2, [x19, 3380]
	b	.L4233
.L4240:
	str	wzr, [x29, 124]
	b	.L4254
	.size	HEVC_OutputFrmFromDPB, .-HEVC_OutputFrmFromDPB
	.align	3
.LC1112:
	.xword	.LANCHOR3
	.align	3
.LC1114:
	.xword	.LC1113
	.align	3
.LC1116:
	.xword	.LC1115
	.align	3
.LC1118:
	.xword	.LC1117
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputOneFrmFromDPB
	.type	HEVC_OutputOneFrmFromDPB, %function
HEVC_OutputOneFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w1
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, x21, uxtw 3
	bl	_mcount
	mov	w2, 1
	mov	x0, x19
	ldr	x1, [x20, 3688]
	strb	w2, [x1, 2]
	ldr	x1, [x20, 3688]
	bl	HEVC_OutputFrmToVO
	mov	w22, w0
	ldr	x0, [x20, 3688]
	ldr	w1, [x0, 32]
	ldr	w2, [x0, 8]
	add	x1, x19, x1, lsl 2
	str	w2, [x1, 212]
	ldrb	w0, [x0, 1]
	cbnz	w0, .L4260
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_RemoveApcStore
	mov	w1, w21
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
.L4260:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_OutputOneFrmFromDPB, .-HEVC_OutputOneFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_OutputUnRefPicWithMinPoc
	.type	HEVC_OutputUnRefPicWithMinPoc, %function
HEVC_OutputUnRefPicWithMinPoc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x29, 44
	mov	x0, x19
	bl	HEVC_GetUnRefPicWithMinPoc
	cbnz	w0, .L4266
	ldr	w1, [x29, 44]
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	mov	w1, 0
	cbnz	w0, .L4267
.L4263:
	ldr	x19, [sp, 16]
	mov	w0, w1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4266:
	ldr	x2, .LC1120
	mov	w0, 1
	ldr	x1, .LC1122
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w1, -1
	b	.L4263
	.p2align 3
.L4267:
	ldr	x2, .LC1120
	mov	w0, 1
	ldr	x1, .LC1124
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w1, -1
	b	.L4263
	.size	HEVC_OutputUnRefPicWithMinPoc, .-HEVC_OutputUnRefPicWithMinPoc
	.align	3
.LC1120:
	.xword	.LANCHOR3
	.align	3
.LC1122:
	.xword	.LC1121
	.align	3
.LC1124:
	.xword	.LC1123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FlushOutputFrmFromDPB
	.type	HEVC_FlushOutputFrmFromDPB, %function
HEVC_FlushOutputFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L4277
	ldr	w0, [x19, 3380]
	mov	w20, 0
	mov	w22, 1
	cbnz	w0, .L4280
	b	.L4276
	.p2align 3
.L4284:
	strb	w22, [x1, 2]
	ldr	x1, [x21, 3688]
	bl	HEVC_OutputFrmToVO
	cmn	w0, #1
	mov	w21, w0
	beq	.L4283
.L4273:
	ldr	w0, [x19, 3380]
	cmp	w0, w20
	bls	.L4276
.L4280:
	add	x21, x19, x20, uxtw 3
	ldr	w0, [x19, 276]
	mov	w2, 0
	add	w20, w20, 1
	ldr	x1, [x21, 3688]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldr	x1, [x21, 3688]
	mov	x0, x19
	ldrb	w2, [x1, 2]
	cbz	w2, .L4284
	ldr	w1, [x1, 28]
	ldr	w0, [x19, 276]
	bl	FSP_GetDisplay
	cmp	w0, 3
	mov	w2, 0
	beq	.L4273
	ldr	x1, [x21, 3688]
	ldr	w0, [x19, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 3380]
	cmp	w0, w20
	bhi	.L4280
.L4276:
	mov	w1, -2147483647
	mov	x0, x19
	stp	w1, w1, [x19, 212]
	mov	w21, 0
	bl	HEVC_InitDecBuffers
.L4269:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4283:
	ldr	x2, .LC1125
	mov	w0, 0
	ldr	x1, .LC1127
	add	x2, x2, 368
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L4277:
	mov	w21, -1
	b	.L4269
	.size	HEVC_FlushOutputFrmFromDPB, .-HEVC_FlushOutputFrmFromDPB
	.align	3
.LC1125:
	.xword	.LANCHOR3
	.align	3
.LC1127:
	.xword	.LC1126
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ReceivePacket
	.type	HEVC_ReceivePacket, %function
HEVC_ReceivePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19, 2984]
	str	wzr, [x19, 352]
	cbz	x0, .L4315
	ldrb	w1, [x20]
	str	w1, [x0, 36]
	ldr	x0, [x19, 3040]
	ldr	w1, [x0, 912]
	cmp	w1, 1
	beq	.L4316
.L4292:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L4293
	ldr	x1, [x19, 2984]
	ldr	w0, [x1, 8]
	cmp	w0, 1
	bls	.L4294
	ldr	w2, [x1, 36]
	cmp	w2, 1
	beq	.L4293
.L4294:
	ldr	w2, [x20, 24]
	cmp	w2, wzr
	ble	.L4295
	ldr	x2, [x20, 8]
	cbz	x2, .L4295
	ldr	w3, [x20, 16]
	cbnz	w3, .L4317
.L4295:
	mov	w0, 1
	str	w0, [x1, 36]
	ldr	w0, [x19, 276]
	ldr	w1, [x20, 28]
	bl	SM_ReleaseStreamSeg
.L4291:
	ldr	x0, [x19, 2984]
	ldr	w0, [x0, 36]
	cmp	w0, wzr
	csetm	w0, eq
.L4289:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4317:
	uxtw	x0, w0
	add	x0, x1, x0, lsl 5
	str	x2, [x0, 40]
	ldr	x1, [x19, 2984]
	ldr	w2, [x20, 24]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 48]
	ldr	x1, [x19, 2984]
	ldr	w2, [x20, 16]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 52]
	ldr	x1, [x19, 2984]
	ldr	w2, [x20, 28]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 68]
	ldr	x1, [x19, 2984]
	ldr	w0, [x1, 8]
	add	x0, x1, x0, lsl 5
	str	wzr, [x0, 60]
	ldr	x1, [x19, 2984]
	ldr	w0, [x1, 8]
	add	w0, w0, 1
	str	w0, [x1, 8]
	ldr	x0, [x19, 3040]
	ldrb	w0, [x0, 984]
	cmp	w0, 1
	beq	.L4296
	ldr	w0, [x19, 4908]
	ldr	w1, [x20, 24]
	ldr	w2, [x19, 4912]
	add	w1, w0, w1
	str	w1, [x19, 4908]
	ldr	w0, [x20, 24]
	add	w0, w2, w0
	str	w0, [x19, 4912]
.L4296:
	mov	x0, x19
	bl	HEVC_CombinePacket
	mov	w0, 1
	str	w0, [x19, 352]
	b	.L4291
	.p2align 3
.L4316:
	ldr	w0, [x0, 960]
	cbnz	w0, .L4291
	b	.L4292
	.p2align 3
.L4315:
	ldr	w0, [x20, 24]
	cmp	w0, wzr
	ble	.L4287
	ldr	x0, [x20, 8]
	cbz	x0, .L4287
	ldr	w0, [x20, 16]
	cbz	w0, .L4287
	mov	x0, x19
	bl	HEVC_FindNaluArraySlot
	cmn	w0, #1
	mov	w21, w0
	beq	.L4318
	ldr	x0, [x19, 3032]
	mov	w2, 104
	mov	w1, 1
	smaddl	x0, w21, w2, x0
	str	x0, [x19, 2984]
	ldr	x2, [x20, 8]
	str	x2, [x0, 40]
	ldr	x0, [x19, 2984]
	ldr	w2, [x20, 24]
	str	w2, [x0, 48]
	ldr	x0, [x19, 2984]
	ldr	w2, [x20, 28]
	str	w2, [x0, 68]
	ldr	x0, [x19, 2984]
	ldr	w2, [x20, 16]
	str	w2, [x0, 52]
	ldr	x0, [x19, 2984]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 2984]
	str	w1, [x0, 8]
	ldr	x0, [x19, 2984]
	strb	wzr, [x0]
	ldr	x0, [x19, 2984]
	ldrb	w1, [x20]
	str	w1, [x0, 36]
	ldr	x0, [x19, 3040]
	ldrb	w0, [x0, 984]
	cmp	w0, 1
	beq	.L4290
	ldr	w0, [x19, 4908]
	ldr	w1, [x20, 24]
	ldr	w2, [x19, 4912]
	add	w1, w0, w1
	str	w1, [x19, 4908]
	ldr	w0, [x20, 24]
	add	w0, w2, w0
	str	w0, [x19, 4912]
.L4290:
	ldr	w0, [x20, 20]
	str	w0, [x19, 2364]
	b	.L4291
	.p2align 3
.L4293:
	ldr	x1, .LC1133
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4289
	.p2align 3
.L4287:
	ldr	x1, .LC1131
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4289
.L4318:
	ldr	x1, .LC1129
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, w21
	b	.L4289
	.size	HEVC_ReceivePacket, .-HEVC_ReceivePacket
	.align	3
.LC1129:
	.xword	.LC1128
	.align	3
.LC1131:
	.xword	.LC1130
	.align	3
.LC1133:
	.xword	.LC1132
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_FlushDPB
	.type	HEVC_FlushDPB, %function
HEVC_FlushDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	w2, [x19, 3380]
	cbnz	w2, .L4331
	b	.L4321
	.p2align 3
.L4322:
	cmp	w2, w20
	bls	.L4321
.L4331:
	add	x0, x19, x20, uxtw 3
	add	w20, w20, 1
	ldr	x0, [x0, 3688]
	ldrb	w1, [x0, 1]
	cbz	w1, .L4322
	strb	wzr, [x0, 1]
	mov	w2, 0
	ldr	w1, [x0, 28]
	ldr	w0, [x19, 276]
	bl	FSP_SetRef
	ldr	w2, [x19, 3380]
	cmp	w2, w20
	bhi	.L4331
	.p2align 2
.L4321:
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbz	w0, .L4325
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbnz	w0, .L4321
	b	.L4325
	.p2align 3
.L4327:
	bl	HEVC_GetMinPOC
	ldr	w1, [x29, 40]
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	cmn	w0, #1
	beq	.L4326
.L4325:
	ldr	w3, [x19, 3380]
	add	x2, x29, 40
	add	x1, x29, 44
	mov	x0, x19
	cbnz	w3, .L4327
	mov	w0, 0
.L4326:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_FlushDPB, .-HEVC_FlushDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_ClearDPB
	.type	HEVC_ClearDPB, %function
HEVC_ClearDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_FlushDPB
	cbz	w0, .L4337
	ldr	x2, .LC1134
	mov	w3, w0
	ldr	x1, .LC1136
	mov	w0, 0
	add	x2, x2, 400
	bl	dprint_vfmw
.L4337:
	mov	w1, 0
	mov	x0, x19
	bl	HEVC_InitDPB
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_ClearDPB, .-HEVC_ClearDPB
	.align	3
.LC1134:
	.xword	.LANCHOR3
	.align	3
.LC1136:
	.xword	.LC1135
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RecoverDPBProcess
	.type	HEVC_RecoverDPBProcess, %function
HEVC_RecoverDPBProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC1137
	ldr	x22, .LC1139
	add	x21, x20, 416
	b	.L4342
	.p2align 3
.L4344:
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_IncreaseDPBSize
	cbnz	w0, .L4352
.L4342:
	ldr	w5, [x19, 3376]
	mov	x2, x21
	ldr	w6, [x19, 3380]
	mov	x1, x22
	mov	w0, 13
	mov	w4, w5
	cmp	w6, w5
	mov	w3, w6
	bcs	.L4344
.L4341:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4352:
	ldr	x1, .LC1141
	mov	x2, x21
	mov	w0, 1
	add	x20, x20, 416
	bl	dprint_vfmw
	ldr	x21, .LC1143
	.p2align 2
.L4343:
	ldr	w5, [x19, 3376]
	mov	x2, x20
	ldr	w6, [x19, 3380]
	mov	x1, x21
	mov	w0, 1
	mov	w4, w5
	cmp	w6, w5
	mov	w3, w6
	bcc	.L4341
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_OutputUnRefPicWithMinPoc
	cbz	w0, .L4343
	ldr	x1, .LC1144
	mov	x2, x20
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_PrintDPBState
	mov	x0, x19
	bl	HEVC_ClearDPB
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVC_RecoverDPBProcess, .-HEVC_RecoverDPBProcess
	.align	3
.LC1137:
	.xword	.LANCHOR3
	.align	3
.LC1139:
	.xword	.LC1138
	.align	3
.LC1141:
	.xword	.LC1140
	.align	3
.LC1143:
	.xword	.LC1142
	.align	3
.LC1144:
	.xword	.LC1123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InsertFrmInDPB
	.type	HEVC_InsertFrmInDPB, %function
HEVC_InsertFrmInDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	mov	x19, x2
	bl	_mcount
	cmp	w22, 16
	bhi	.L4357
	add	x20, x21, x22, uxtw 3
	ldr	x0, [x19, 64]
	mov	w1, 1
	mov	w2, w1
	str	x0, [x20, 3688]
	str	w1, [x0, 48]
	ldr	x1, [x20, 3688]
	ldr	w0, [x21, 276]
	ldr	w1, [x1, 28]
	bl	FSP_SetRef
	ldrb	w1, [x19]
	mov	x2, 640
	ldr	x0, [x20, 3688]
	cmp	w1, wzr
	add	x1, x19, 72
	cset	w3, ne
	strb	w3, [x0, 1]
	ldr	x0, [x20, 3688]
	ldr	w3, [x19, 36]
	str	w3, [x0, 20]
	ldr	x0, [x20, 3688]
	add	x0, x0, 88
	bl	memcpy
	ldr	x0, [x20, 3688]
	add	w1, w22, 1
	ldr	w4, [x19, 40]
	mov	w2, 8
	ldr	x3, .LC1149
	str	w4, [x0, 16]
	add	x0, x21, 3688
	ldr	x4, [x20, 3688]
	ldr	x5, [x19, 64]
	str	x5, [x4, 80]
	ldr	x4, [x20, 3688]
	ldr	w5, [x19, 16]
	str	w5, [x4, 12]
	ldr	x4, [x20, 3688]
	ldr	w5, [x19, 12]
	str	w5, [x4, 8]
	ldr	x4, [x20, 3688]
	ldr	w5, [x19, 8]
	str	w5, [x4, 32]
	ldr	x4, [x20, 3688]
	str	wzr, [x4, 72]
	bl	qsort
	ldr	w1, [x21, 3380]
	mov	x0, x21
	add	w1, w1, 1
	str	w1, [x21, 3380]
	ldr	x1, [x19, 64]
	bl	HEVC_GetAPC
	cbnz	w0, .L4358
	strb	wzr, [x19, 1]
	mov	w0, 0
.L4355:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4357:
	ldr	x2, .LC1146
	mov	w3, w22
	ldr	x1, .LC1148
	mov	w0, 0
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	x0, x21
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L4355
	.p2align 3
.L4358:
	ldr	x2, .LC1146
	mov	w3, w0
	ldr	x1, .LC1151
	mov	w0, 0
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	x0, x21
	bl	HEVC_PrintDPBState
	mov	x0, x21
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L4355
	.size	HEVC_InsertFrmInDPB, .-HEVC_InsertFrmInDPB
	.align	3
.LC1146:
	.xword	.LANCHOR3
	.align	3
.LC1148:
	.xword	.LC1147
	.align	3
.LC1149:
	.xword	HEVC_ComparePicByPocAsc
	.align	3
.LC1151:
	.xword	.LC1150
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_SimpleDPBProcess
	.type	HEVC_SimpleDPBProcess, %function
HEVC_SimpleDPBProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 4096
	bl	_mcount
	ldrb	w0, [x20, 760]
	cbnz	w0, .L4372
	ldr	x0, [x19, 4920]
	mov	w1, 2
	str	w1, [x0, 48]
.L4361:
	ldr	x1, [x19, 4920]
	mov	w2, 1
	mov	x0, x19
	strb	w2, [x1, 2]
	ldr	x1, [x19, 4920]
	bl	HEVC_CheckFrameStore
	cmn	w0, #1
	mov	w20, w0
	beq	.L4373
	cmn	w0, #3
	beq	.L4365
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	cbnz	w0, .L4374
.L4365:
	mov	w0, 0
.L4362:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4372:
	mov	x0, x19
	bl	HEVC_SimpleSlideDPB
	ldr	w1, [x19, 3380]
	add	x2, x20, 760
	mov	x0, x19
	bl	HEVC_InsertFrmInDPB
	cbz	w0, .L4361
	ldr	x2, .LC1152
	mov	w4, w0
	ldr	x1, .LC1154
	mov	w3, 10993
	add	x2, x2, 464
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4362
	.p2align 3
.L4374:
	ldr	x2, .LC1152
	mov	w0, 0
	ldr	x1, .LC1157
	add	x2, x2, 464
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4362
.L4373:
	ldr	x2, .LC1152
	mov	w0, 0
	ldr	x1, .LC1156
	add	x2, x2, 464
	bl	dprint_vfmw
	mov	w0, w20
	b	.L4362
	.size	HEVC_SimpleDPBProcess, .-HEVC_SimpleDPBProcess
	.align	3
.LC1152:
	.xword	.LANCHOR3
	.align	3
.LC1154:
	.xword	.LC1153
	.align	3
.LC1156:
	.xword	.LC1155
	.align	3
.LC1157:
	.xword	.LC1105
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecOrderProcess
	.type	HEVC_DecOrderProcess, %function
HEVC_DecOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 3376]
	ldr	w1, [x19, 3380]
	cmp	w1, w0
	bcs	.L4387
.L4376:
	add	x2, x19, 4096
	mov	x0, x19
	add	x2, x2, 760
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L4388
	ldr	x1, [x19, 4920]
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cmn	w0, #1
	mov	w20, w0
	beq	.L4389
	cmn	w0, #3
	beq	.L4382
	mov	x0, x19
	bl	HEVC_OutputCurrPic
	cbnz	w0, .L4390
.L4382:
	mov	w0, 0
.L4379:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4387:
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	w0, 1
	beq	.L4386
	ldr	x2, .LC1158
	mov	w0, 0
	ldr	x1, .LC1160
	add	x2, x2, 488
	bl	dprint_vfmw
.L4386:
	ldr	w1, [x19, 3380]
	b	.L4376
.L4390:
	ldr	x2, .LC1158
	mov	w0, 0
	ldr	x1, .LC1164
	add	x2, x2, 488
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4379
	.p2align 3
.L4388:
	ldr	x2, .LC1158
	mov	w0, 0
	ldr	x1, .LC1162
	add	x2, x2, 488
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4379
.L4389:
	ldr	x2, .LC1158
	mov	w0, 0
	ldr	x1, .LC1163
	add	x2, x2, 488
	bl	dprint_vfmw
	mov	w0, w20
	b	.L4379
	.size	HEVC_DecOrderProcess, .-HEVC_DecOrderProcess
	.align	3
.LC1158:
	.xword	.LANCHOR3
	.align	3
.LC1160:
	.xword	.LC1159
	.align	3
.LC1162:
	.xword	.LC1161
	.align	3
.LC1163:
	.xword	.LC1155
	.align	3
.LC1164:
	.xword	.LC1105
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DispOrderProcess
	.type	HEVC_DispOrderProcess, %function
HEVC_DispOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12808]
	cmp	w0, 1
	beq	.L4392
	mov	x0, x19
	bl	HEVC_FirstFrameFastOut
	cbnz	w0, .L4415
.L4392:
	ldr	w0, [x19, 3376]
	ldr	w1, [x19, 3380]
	cmp	w1, w0
	bcs	.L4416
.L4394:
	add	x20, x19, 4096
	mov	x0, x19
	add	x2, x20, 760
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L4417
	ldr	w0, [x19, 3380]
	cbnz	w0, .L4418
.L4397:
	ldr	w1, [x19, 3376]
	cmp	w1, w0
	bls	.L4419
.L4414:
	mov	w0, 0
.L4393:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4419:
	ldr	w0, [x19, 276]
	add	x1, x20, 2848
	bl	FSP_IfCanGetDecFs
	cbz	w0, .L4414
	mov	x0, x19
	bl	HEVC_RemoveFrmFullDPB
	b	.L4414
	.p2align 3
.L4416:
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	w0, 1
	beq	.L4413
	ldr	x1, .LC1169
	mov	w0, 0
	bl	dprint_vfmw
.L4413:
	ldr	w1, [x19, 3380]
	b	.L4394
	.p2align 3
.L4418:
	mov	x0, x19
	bl	HEVC_OutputFrmFromDPB
	cbnz	w0, .L4398
	ldr	w0, [x19, 3380]
	b	.L4397
	.p2align 3
.L4417:
	ldr	x1, .LC1171
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4393
.L4415:
	ldr	x2, .LC1165
	mov	w0, 0
	ldr	x1, .LC1167
	add	x2, x2, 512
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4393
.L4398:
	ldr	x2, .LC1165
	mov	w0, 1
	ldr	x1, .LC1173
	add	x2, x2, 512
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4393
	.size	HEVC_DispOrderProcess, .-HEVC_DispOrderProcess
	.align	3
.LC1165:
	.xword	.LANCHOR3
	.align	3
.LC1167:
	.xword	.LC1166
	.align	3
.LC1169:
	.xword	.LC1168
	.align	3
.LC1171:
	.xword	.LC1170
	.align	3
.LC1173:
	.xword	.LC1172
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_StorePicInDPB
	.type	HEVC_StorePicInDPB, %function
HEVC_StorePicInDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrsw	x1, [x19, 276]
	ldr	x0, .LC1174
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L4475
.L4421:
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L4476
.L4424:
	add	x21, x19, 4096
	ldrb	w0, [x21, 761]
	cbz	w0, .L4477
	ldr	w0, [x19, 4896]
	cbz	w0, .L4429
	ldr	w1, [x19, 4872]
	cbz	w1, .L4478
.L4430:
	ldr	x1, [x19, 3040]
	ldr	w2, [x1, 4]
	cmp	w2, w0
	bcs	.L4429
	ldr	w20, [x1, 684]
	cbz	w20, .L4479
.L4429:
	ldr	x1, [x19, 3056]
	ldr	x0, [x19, 4920]
	ldr	w1, [x1, 5192]
	str	w1, [x0, 40]
	ldr	x1, [x19, 3056]
	ldr	x0, [x19, 4920]
	ldr	w1, [x1, 5196]
	str	w1, [x0, 44]
	ldr	w0, [x19, 280]
	cmp	w0, 2
	beq	.L4480
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	beq	.L4481
	cmp	w0, 1
	beq	.L4482
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L4442
.L4440:
	mov	x0, x19
	bl	HEVC_DispOrderProcess
	mov	w20, w0
	cbnz	w0, .L4483
	.p2align 2
.L4441:
	strb	wzr, [x21, 761]
.L4473:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4476:
	ldr	w5, [x19, 4864]
	cbz	w5, .L4424
	uxtw	x6, w5
	lsl	x0, x6, 5
	add	x0, x0, x6, lsl 3
	add	x1, x19, x0, lsl 3
	sub	x0, x1, x0
	ldr	w4, [x0, 14188]
	cbz	w4, .L4424
	mov	w2, 280
	mov	x1, 0
	umull	x2, w5, w2
	add	x2, x2, 12288
	add	x0, x2, 1908
	add	x2, x2, 2164
	add	x0, x19, x0
	add	x2, x19, x2
	b	.L4426
	.p2align 3
.L4425:
	add	w1, w1, 1
	add	x2, x2, 1
	cmp	w1, w4
	beq	.L4424
.L4426:
	ldr	w3, [x0]
	add	x0, x0, 4
	cbz	w3, .L4425
	ldrsb	w3, [x2]
	cbz	w3, .L4425
	mov	w2, 70
	lsl	x0, x6, 5
	add	x6, x0, x6, lsl 3
	umaddl	x2, w5, w2, x1
	add	x0, x19, x6, lsl 3
	sub	x6, x0, x6
	add	x2, x19, x2, lsl 2
	add	x1, x6, x1
	add	x0, x1, 12288
	str	wzr, [x2, 14196]
	str	wzr, [x2, 14260]
	str	wzr, [x2, 14324]
	ldr	w1, [x6, 14192]
	sub	w1, w1, #1
	str	w1, [x6, 14192]
	strb	wzr, [x0, 2164]
	str	wzr, [x2, 14388]
	b	.L4424
	.p2align 3
.L4475:
	ldr	x1, [x0, 160]
	mov	x0, 1
	movk	x0, 0x2, lsl 32
	cmp	x1, x0
	bne	.L4421
	add	x0, x19, 12288
	ldrb	w0, [x0, 464]
	cmp	w0, 1
	bne	.L4421
	ldr	w4, [x19, 12764]
	ldr	w5, [x19, 12768]
	ldr	x6, [x19, 12776]
	ldr	x3, [x19, 12784]
	ldr	x7, [x19, 12792]
	cbz	w4, .L4443
	mov	w1, w4
	mov	w2, w5
	b	.L4423
	.p2align 3
.L4444:
	mov	w1, w0
.L4423:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L4444
.L4422:
	udiv	w0, w4, w1
	sub	x3, x3, x7
	lsl	w2, w3, 6
	sub	w2, w2, w3
	lsl	w2, w2, 1
	sub	w2, w2, w3
	lsl	w2, w2, 3
	udiv	w1, w5, w1
	mul	w0, w2, w0
	udiv	w0, w0, w1
	add	x0, x0, x6
	str	x0, [x19, 5512]
	b	.L4421
	.p2align 3
.L4477:
	ldr	x2, .LC1175
	mov	w0, 1
	ldr	x1, .LC1177
	mov	w20, 0
	add	x2, x2, 536
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4479:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x3, [x19, 3040]
	mov	w0, 1
	ldr	x1, .LC1182
	ldr	w2, [x19, 4896]
	ldr	w3, [x3, 4]
	bl	dprint_vfmw
	b	.L4473
	.p2align 3
.L4482:
	mov	x0, x19
	bl	HEVC_DecOrderProcess
	mov	w20, w0
	cbnz	w0, .L4439
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L4441
	b	.L4440
	.p2align 3
.L4478:
	ldr	x2, .LC1175
	mov	w0, 1
	ldr	x1, .LC1179
	add	x2, x2, 536
	bl	dprint_vfmw
	ldr	x0, .LC1180
	ldr	x4, [x0]
	cbz	x4, .L4474
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 111
	blr	x4
.L4474:
	ldr	w0, [x19, 4896]
	b	.L4430
	.p2align 3
.L4480:
	mov	x0, x19
	bl	HEVC_DirectOutput
	mov	w20, w0
	ldr	w1, [x19, 184]
	ldr	w0, [x19, 4892]
	cmp	w0, w1
	beq	.L4433
	add	x0, x19, x0, uxtw 2
	str	wzr, [x0, 2168]
	str	w1, [x19, 4892]
.L4433:
	cbnz	w20, .L4484
.L4434:
	ldr	x1, .LC1186
	mov	w3, 11295
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
.L4435:
	cmn	w20, #1
	bne	.L4441
	.p2align 2
.L4442:
	mov	x0, x19
	mov	w20, -1
	bl	HEVC_ClearCurrPic
	ldr	x2, .LC1175
	mov	w0, 1
	ldr	x1, .LC1194
	add	x2, x2, 536
	bl	dprint_vfmw
	b	.L4441
	.p2align 3
.L4481:
	mov	x0, x19
	bl	HEVC_SimpleDPBProcess
	mov	w20, w0
	cbnz	w0, .L4485
.L4437:
	ldr	x1, .LC1186
	mov	w3, 11310
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L4435
	.p2align 3
.L4483:
	ldr	x2, .LC1175
	mov	w0, 0
	ldr	x1, .LC1192
	add	x2, x2, 536
	bl	dprint_vfmw
	b	.L4435
	.p2align 3
.L4484:
	ldr	x2, .LC1175
	mov	w0, 0
	ldr	x1, .LC1184
	add	x2, x2, 536
	bl	dprint_vfmw
	b	.L4434
	.p2align 3
.L4485:
	ldr	x2, .LC1175
	mov	w0, 0
	ldr	x1, .LC1188
	add	x2, x2, 536
	bl	dprint_vfmw
	b	.L4437
	.p2align 3
.L4439:
	ldr	x2, .LC1175
	mov	w0, 0
	ldr	x1, .LC1190
	add	x2, x2, 536
	bl	dprint_vfmw
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L4435
	b	.L4440
	.p2align 3
.L4443:
	mov	w1, w5
	b	.L4422
	.size	HEVC_StorePicInDPB, .-HEVC_StorePicInDPB
	.align	3
.LC1174:
	.xword	s_pstVfmwChan
	.align	3
.LC1175:
	.xword	.LANCHOR3
	.align	3
.LC1177:
	.xword	.LC1176
	.align	3
.LC1179:
	.xword	.LC1178
	.align	3
.LC1180:
	.xword	g_event_report
	.align	3
.LC1182:
	.xword	.LC1181
	.align	3
.LC1184:
	.xword	.LC1183
	.align	3
.LC1186:
	.xword	.LC1185
	.align	3
.LC1188:
	.xword	.LC1187
	.align	3
.LC1190:
	.xword	.LC1189
	.align	3
.LC1192:
	.xword	.LC1191
	.align	3
.LC1194:
	.xword	.LC1193
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CreateLostPicture
	.type	HEVC_CreateLostPicture, %function
HEVC_CreateLostPicture:
	sub	sp, sp, #720
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	add	x19, x20, 12288
	bl	_mcount
	mov	w21, 0
	ldr	x3, .LC1195
	mov	x2, 712
	mov	w1, 0
	add	x0, x29, 88
	add	x19, x19, 2464
	ldr	x3, [x3, 96]
	blr	x3
	.p2align 2
.L4492:
	ldr	w0, [x19, 48]
	cbnz	w0, .L4487
	cbz	x19, .L4488
	ldr	w2, [x20, 3380]
	cbz	w2, .L4488
	ldr	x0, [x20, 3688]
	cmp	x19, x0
	beq	.L4487
	sub	w2, w2, #1
	mov	x0, x20
	add	x2, x20, x2, lsl 3
	b	.L4490
	.p2align 3
.L4491:
	ldr	x1, [x0, 3688]
	cmp	x19, x1
	beq	.L4487
.L4490:
	cmp	x2, x0
	add	x0, x0, 8
	bne	.L4491
.L4488:
	sxtw	x3, w21
	mov	w24, 1
	lsl	x1, x3, 3
	mov	w4, 101
	sub	x1, x1, x3
	mov	x2, 640
	lsl	x1, x1, x24
	add	x0, x29, 160
	sub	x1, x1, x3
	strb	w24, [x29, 89]
	lsl	x23, x1, 3
	strb	w24, [x29, 88]
	sub	x1, x23, x1
	str	w22, [x29, 100]
	str	w4, [x29, 128]
	add	x23, x20, x1, lsl 3
	add	x25, x23, 12288
	add	x1, x25, 2552
	bl	memcpy
	strb	w24, [x25, 2466]
	str	wzr, [x23, 14804]
	cmp	w21, 19
	strb	w24, [x25, 2464]
	str	x19, [x29, 152]
	str	wzr, [x29, 312]
	bgt	.L4493
	ldr	w5, [x20, 3380]
	cbz	w5, .L4495
	mov	w6, 0
	mov	w3, 2147483647
	mov	w1, 0
	.p2align 2
.L4498:
	add	x0, x20, x1, sxtw 3
	add	w1, w1, 1
	ldr	x4, [x0, 3688]
	ldr	w0, [x4, 8]
	sub	w0, w0, w22
	sxtw	x0, w0
	eor	x2, x0, x0, asr 63
	sub	x2, x2, x0, asr 63
	cmp	w2, w3
	bge	.L4497
	ldrb	w0, [x4, 1]
	cmp	w0, wzr
	csel	w3, w3, w2, eq
	csinc	w6, w6, wzr, eq
.L4497:
	cmp	w1, w5
	bne	.L4498
	cbz	w6, .L4495
	mov	w1, 0
	b	.L4499
	.p2align 3
.L4500:
	cmp	w5, w1
	beq	.L4501
.L4499:
	sxtw	x19, w1
	add	w1, w1, 1
	add	x19, x19, 460
	add	x19, x20, x19, lsl 3
	ldr	x2, [x19, 8]
	ldr	w0, [x2, 8]
	sub	w0, w0, w22
	sxtw	x0, w0
	eor	x4, x0, x0, asr 63
	sub	x4, x4, x0, asr 63
	cmp	w3, w4
	bne	.L4500
	ldrb	w0, [x2, 1]
	cbz	w0, .L4500
	ldp	w1, w23, [x2, 28]
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	mov	x21, x0
	ldr	x2, [x19, 8]
	mov	w3, w22
	ldr	x1, .LC1203
	mov	w0, 1
	ldr	w2, [x2, 8]
	bl	dprint_vfmw
	cbz	x21, .L4501
	ldr	x0, [x21, 32]
	cbz	x0, .L4534
	ldr	w0, [x20, 276]
	mov	w1, 0
	bl	FSP_NewLogicFs
	mov	w1, w0
	mov	w19, w0
	ldr	w0, [x20, 276]
	bl	FSP_GetLogicFs
	mov	x1, x0
	cmp	w19, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L4504
	ldr	x3, [x29, 152]
	add	x2, x29, 88
	mov	x0, x20
	str	w19, [x3, 28]
	ldr	x3, [x21, 32]
	str	x3, [x1, 32]
	ldr	x3, [x21, 40]
	str	x3, [x1, 40]
	ldrsb	w3, [x21, 4]
	ldr	w1, [x20, 3380]
	str	w23, [x29, 96]
	str	w3, [x29, 124]
	bl	HEVC_InsertFrmInDPB
	cbnz	w0, .L4535
	ldr	w0, [x20, 276]
	mov	w2, 0
	mov	w1, w19
	bl	FSP_SetDisplay
	ldr	w1, [x20, 5600]
	mov	w2, 2147483647
	mov	w0, 0
	add	x20, x20, x1, lsl 2
	ldr	w1, [x20, 244]
	cmp	w1, w2
	bne	.L4520
	str	w22, [x20, 244]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	add	sp, sp, 720
	ret
	.p2align 3
.L4487:
	add	w21, w21, 1
	add	x19, x19, 728
	cmp	w21, 20
	bne	.L4492
.L4493:
	ldr	x1, .LC1197
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L4520:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	add	sp, sp, 720
	ret
	.p2align 3
.L4501:
	ldr	x1, .LC1199
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	mov	w0, -1
	add	sp, sp, 720
	ret
.L4504:
	ldr	x2, [x29, 152]
	mov	w0, 0
	ldr	x1, .LC1207
	strb	wzr, [x2]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4520
.L4535:
	ldr	x0, [x29, 152]
	mov	w2, 1
	mov	w1, w19
	strb	wzr, [x0]
	ldr	w0, [x20, 276]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC1209
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4520
.L4495:
	ldr	x1, .LC1201
	mov	w0, 0
	strb	wzr, [x19]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4520
.L4534:
	ldr	x1, .LC1205
	bl	dprint_vfmw
	mov	x0, x20
	bl	HEVC_ClearDPB
	mov	w0, -1
	b	.L4520
	.size	HEVC_CreateLostPicture, .-HEVC_CreateLostPicture
	.align	3
.LC1195:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1197:
	.xword	.LC1196
	.align	3
.LC1199:
	.xword	.LC1198
	.align	3
.LC1201:
	.xword	.LC1200
	.align	3
.LC1203:
	.xword	.LC1202
	.align	3
.LC1205:
	.xword	.LC1204
	.align	3
.LC1207:
	.xword	.LC1206
	.align	3
.LC1209:
	.xword	.LC1208
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_RefPicProcess
	.type	HEVC_RefPicProcess, %function
HEVC_RefPicProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	ldrb	w3, [x19, 1]
	cmp	w3, 1
	beq	.L4537
.L4541:
	mov	x0, x19
	bl	HEVC_ApplyReferencePictureSet
	mov	x0, x19
	bl	HEVC_RemoveUnusedApcStore
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	ldr	x20, .LC1211
	b	.L4538
	.p2align 3
.L4547:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.14
	cbnz	w0, .L4551
	ldr	w2, [x29, 44]
	mov	x1, x20
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 3040]
	mov	x0, x19
	ldr	w1, [x1, 4]
	cbz	w1, .L4545
	ldr	w1, [x29, 44]
	bl	HEVC_CreateLostPicture
	cbnz	w0, .L4559
.L4538:
	ldr	w2, [x19, 5596]
	add	x1, x29, 44
	mov	x0, x19
	sub	w2, w2, #19
	cmp	w2, 2
	bhi	.L4547
.L4551:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L4560
.L4549:
	mov	x0, x19
	bl	HEVC_UpdateReflist
	mov	x0, x19
	bl	HEVC_UpdateLTReflist
	mov	x0, x19
	bl	HEVC_RecoverDPBProcess
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4545:
	ldr	w3, [x19, 5580]
	mov	w2, 0
	ldr	w4, [x29, 44]
	mov	w0, 1
	ldr	x1, .LC1213
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4559:
	mov	x0, x19
	bl	HEVC_RemoveDummyFrame
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4537:
	ldr	w1, [x19, 3404]
	mov	w0, 0
	cbz	w1, .L4543
	.p2align 2
.L4554:
	add	x1, x19, x0, uxtw 3
	add	w0, w0, 1
	ldr	x2, [x1, 3416]
	str	wzr, [x2, 60]
	ldr	x1, [x1, 3416]
	str	w3, [x1, 64]
	ldr	w1, [x19, 3404]
	cmp	w0, w1
	bcc	.L4554
.L4543:
	ldr	w1, [x19, 3408]
	mov	w0, 0
	mov	w3, 1
	cbz	w1, .L4541
	.p2align 2
.L4553:
	add	x1, x19, x0, uxtw 3
	add	w0, w0, 1
	ldr	x2, [x1, 3552]
	str	wzr, [x2, 60]
	ldr	x1, [x1, 3552]
	str	w3, [x1, 64]
	ldr	w1, [x19, 3408]
	cmp	w0, w1
	bcc	.L4553
	b	.L4541
	.p2align 3
.L4560:
	mov	x0, x19
	bl	HEVC_UpdateInterLayerReflist
	b	.L4549
	.size	HEVC_RefPicProcess, .-HEVC_RefPicProcess
	.align	3
.LC1211:
	.xword	.LC1210
	.align	3
.LC1213:
	.xword	.LC1212
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecVDM
	.type	HEVC_DecVDM, %function
HEVC_DecVDM:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 176]
	cmp	w0, 2
	bls	.L4620
	ldr	w0, [x19, 320]
	add	x21, x19, 4096
	ldr	w1, [x19, 324]
	mov	w2, 1
	add	w0, w0, 1
	ldr	x3, [x19, 3040]
	cmp	w0, w1
	csel	w0, w0, w1, ge
	str	w0, [x19, 320]
	sub	w0, w0, w1
	str	w0, [x3, 624]
	strb	w2, [x21, 760]
	ldr	w20, [x19, 272]
	ldr	w2, [x19, 280]
	ubfx	x20, x20, 16, 3
	cmp	w20, w2
	beq	.L4566
	sub	w0, w2, #2
	cmp	w0, 1
	ccmp	w20, 2, 4, ls
	beq	.L4566
	cmp	w20, 1
	ccmp	w20, 4, 4, hi
	beq	.L4621
.L4566:
	cmp	w20, 2
	str	w20, [x19, 280]
	beq	.L4568
	cmp	w20, 3
	bne	.L4617
.L4619:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	x0, x19
	bl	HEVC_ClearDPB
	mov	w0, -1
.L4616:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4617:
	ldr	w0, [x19, 260]
	cbz	w0, .L4587
	cmp	w20, 4
	ldr	w0, [x19, 4872]
	bne	.L4574
	cbnz	w0, .L4574
	mov	w0, 2
	strb	w0, [x19, 8]
	.p2align 2
.L4578:
	ldr	w2, [x19, 264]
	mov	w0, 2
	ldr	x1, .LC1223
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	w2, [x19, 204]
	cbz	w2, .L4622
	ldr	w1, [x19, 4884]
	ldr	x0, [x19, 3040]
	ldr	w3, [x19, 4888]
	cmp	w1, wzr
	str	w2, [x19, 10040]
	cset	w2, eq
	str	w3, [x19, 8884]
	str	w2, [x19, 8892]
	ldr	w2, [x0, 640]
	strb	w2, [x21, 3456]
	ldr	w2, [x0, 644]
	strb	w2, [x21, 3457]
	ldr	w2, [x0, 648]
	strb	w2, [x21, 3459]
	ldr	w2, [x0, 652]
	strb	w2, [x21, 3460]
	ldr	w2, [x0, 692]
	ldr	w0, [x19, 264]
	str	w2, [x19, 8880]
	cbz	w0, .L4583
	add	x21, x21, 3456
	ldr	w0, [x19, 4900]
	str	x21, [x19, 3056]
	add	w1, w1, 1
	str	w0, [x21, 5192]
	ldr	w0, [x19, 4904]
	str	w0, [x21, 5196]
	str	w1, [x19, 4884]
	str	wzr, [x21, 5188]
	ldr	w0, [x19, 4872]
	cbnz	w0, .L4583
	ldr	x1, [x19, 10048]
	mov	w4, 0
	cbz	x1, .L4585
	.p2align 2
.L4586:
	ldp	w2, w0, [x1]
	ldr	x1, [x1, 1504]
	add	w0, w2, w0
	add	w0, w0, 7
	add	w4, w4, w0, lsr 3
	cbnz	x1, .L4586
.L4585:
	ldr	x0, .LC1214
	ldr	x5, [x0]
	cbz	x5, .L4583
	add	x2, x29, 64
	ldr	w0, [x19, 276]
	mov	w3, 4
	mov	w1, 20
	str	w4, [x2, -8]!
	blr	x5
.L4583:
	ldr	w4, [x19, 4912]
	mov	w0, 0
	ldr	x3, [x19, 4920]
	ldr	w1, [x19, 4908]
	str	w4, [x19, 4908]
	sub	w1, w1, w4
	ldr	w2, [x3, 328]
	add	w2, w2, w1
	str	w2, [x3, 328]
	ldr	w2, [x19, 5168]
	add	w1, w2, w1
	str	w1, [x19, 5168]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4568:
	ldr	w0, [x19, 4872]
	cbnz	w0, .L4572
	ldr	w1, [x19, 260]
	cbz	w1, .L4587
.L4574:
	cmp	w0, 2
	beq	.L4623
	cmp	w0, 1
	bne	.L4578
	strb	w0, [x19, 8]
	b	.L4578
	.p2align 3
.L4623:
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	bne	.L4578
	ldr	x0, .LC1221
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L4578
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 24]
	sub	w1, w0, #4
	cmp	w1, 2
	ccmp	w0, wzr, 4, hi
	bne	.L4578
	mov	w3, 1
	ldr	x1, .LC1228
	ldr	w2, [x19, 4868]
	mov	w0, w3
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x0, .LC1214
	ldr	x4, [x0]
	cbz	x4, .L4624
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
	mov	w0, -1
	b	.L4616
	.p2align 3
.L4587:
	ldr	x0, .LC1214
	ldr	x4, [x0]
	cbz	x4, .L4572
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L4572:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, -1
	b	.L4616
.L4621:
	ldr	x1, .LC1220
	mov	w3, w20
	mov	w0, 1
	bl	dprint_vfmw
	str	w20, [x19, 280]
	b	.L4619
	.p2align 3
.L4624:
	mov	w0, -1
	b	.L4616
	.p2align 3
.L4622:
	ldr	x0, .LC1214
	ldr	x4, [x0]
	cbz	x4, .L4581
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L4581:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x2, .LC1224
	mov	w0, 0
	ldr	x1, .LC1226
	add	x2, x2, 560
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4616
	.p2align 3
.L4620:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	ldr	x0, .LC1214
	ldr	x4, [x0]
	cbz	x4, .L4563
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L4563:
	ldr	w0, [x19, 268]
	cmp	w0, 524288
	bls	.L4564
	ldr	x1, .LC1216
	mov	w0, 0
	bl	dprint_vfmw
.L4564:
	ldr	x1, .LC1218
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4616
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	3
.LC1214:
	.xword	g_event_report
	.align	3
.LC1216:
	.xword	.LC1215
	.align	3
.LC1218:
	.xword	.LC1217
	.align	3
.LC1220:
	.xword	.LC1219
	.align	3
.LC1221:
	.xword	g_allow_B_before_P
	.align	3
.LC1223:
	.xword	.LC1222
	.align	3
.LC1224:
	.xword	.LANCHOR3
	.align	3
.LC1226:
	.xword	.LC1225
	.align	3
.LC1228:
	.xword	.LC1227
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_VES_Splitter
	.type	HEVC_VES_Splitter, %function
HEVC_VES_Splitter:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	w23, w2
	mov	w25, w3
	mov	w20, w1
	bl	_mcount
	ldr	x0, [x19, 2944]
	mov	w1, 16
	str	xzr, [x29, 88]
	add	x22, x19, 4096
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	and	w24, w0, 31
	ldr	x0, [x19, 2944]
	mov	w1, 24
	bl	BsBack
	str	wzr, [x22, 1252]
	ldr	x1, [x22, 1264]
	str	x1, [x29, 88]
	cbz	w20, .L4627
	cmp	w20, 1
	bne	.L4785
	cmp	w23, 1
	mov	w0, 31745
	beq	.L4786
	cmp	w21, w0
	ccmp	w24, 25, 0, eq
	bne	.L4656
	ldr	x20, .LC1229
	ldr	x4, [x20]
	cbz	x4, .L4657
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4657:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2984]
	cbnz	w0, .L4780
	ldr	w0, [x1, 48]
	add	x21, x22, 1248
	sub	w0, w0, #6
	add	x2, x0, 5
	str	w0, [x21, 4]
	cmp	x2, 1024
	bhi	.L4787
	ldr	w2, [x1, 80]
	ldr	w3, [x1, 48]
	ldr	w0, [x19, 276]
	add	w3, w3, w2
	ldr	w1, [x21, 8]
	add	x2, x29, 88
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L4788
	ldr	x23, .LC1235
	mov	x2, 5
	ldr	x1, .LC1236
	ldr	x0, [x29, 88]
	ldr	x3, [x23, 104]
	add	x1, x1, 208
	blr	x3
	ldr	x1, [x19, 2984]
	ldr	x0, [x29, 88]
	ldr	w2, [x21, 4]
	ldr	x1, [x1, 40]
	add	x0, x0, 5
	ldr	x3, [x23, 104]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x21, 4]
	add	w0, w0, 5
	str	w0, [x21, 4]
	ldr	x1, [x19, 2984]
	ldr	w2, [x1, 80]
	cbz	w2, .L4663
	add	w3, w0, w2
	cmp	w3, 1024
	bls	.L4664
	uxtw	x2, w0
	ldr	x1, .LC1231
	mov	w3, 2507
	add	x2, x2, 5
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	cbz	x1, .L4665
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4665:
	ldr	x4, [x20]
	cbz	x4, .L4666
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4666:
	ldr	w0, [x19, 276]
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L4760
	ldr	x2, .LC1232
	mov	w3, 2514
	ldr	x1, .LC1238
	mov	w0, 0
	add	x2, x2, 576
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4635
	.p2align 3
.L4785:
	ldr	x1, .LC1245
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
.L4635:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4627:
	cmp	w23, 1
	beq	.L4789
	mov	w0, 31745
	and	w21, w21, -513
	cmp	w21, w0
	mov	w0, 1
	bne	.L4635
	ldr	x2, .LC1232
	mov	w3, 2404
	ldr	x1, .LC1241
.L4764:
	mov	w0, 0
	add	x2, x2, 576
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	cbz	x1, .L4760
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
	mov	w0, -1
	b	.L4635
	.p2align 3
.L4656:
	mov	w1, 32257
	mov	w0, w20
	cmp	w21, w1
	bne	.L4635
	ldr	x2, .LC1232
	mov	w3, 2549
	ldr	x1, .LC1243
	b	.L4764
	.p2align 3
.L4789:
	mov	w0, 31745
	cmp	w21, w0
	ccmp	w24, 25, 0, eq
	bne	.L4630
	ldr	x20, .LC1229
	ldr	x4, [x20]
	cbz	x4, .L4631
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4631:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2984]
	cbnz	w0, .L4780
	ldr	w0, [x1, 48]
	add	x21, x22, 1248
	sub	w0, w0, #6
	add	x2, x0, 5
	str	w0, [x21, 4]
	cmp	x2, 1024
	bls	.L4636
	ldr	x1, .LC1231
	mov	w3, 2318
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	.p2align 2
.L4780:
	cbz	x1, .L4661
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4661:
	ldr	x4, [x20]
	cbz	x4, .L4760
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4760:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4786:
	cmp	w21, w0
	ccmp	w25, 2, 0, eq
	ccmp	w24, 25, 0, eq
	beq	.L4790
	mov	w1, 32257
	cmp	w21, w1
	beq	.L4791
	cmp	w21, w0
	bne	.L4792
.L4668:
	ldr	x1, [x19, 2984]
.L4771:
	cbz	x1, .L4761
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4761:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4630:
	mov	w1, 32257
	mov	w0, w23
	cmp	w21, w1
	bne	.L4635
	b	.L4668
	.p2align 3
.L4787:
	ldr	x1, .LC1231
	mov	w3, 2483
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	b	.L4780
	.p2align 3
.L4792:
	ldr	x0, [x19, 2944]
	mov	w1, 8
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2944]
	mov	w1, 8
	ubfx	x20, x20, 1, 6
	bl	BsSkip
	cmp	w20, 49
	bne	.L4668
	mov	x0, x19
	bl	HEVC_IsEosNal
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L4668
	ldr	x1, [x19, 2984]
	ldr	x0, [x19, 2944]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2944]
	mov	w1, 24
	bl	BsSkip
	mov	w0, 2
	b	.L4635
	.p2align 3
.L4664:
	ldr	x4, [x29, 88]
	uxtw	x2, w2
	ldr	x1, [x1, 72]
	ldr	x3, [x23, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x19, 2984]
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 80]
	add	w0, w1, w0
	str	w0, [x21, 4]
.L4663:
	ldr	x20, .LC1239
	ldr	w0, [x19, 276]
	ldr	x1, [x20, w0, sxtw 3]
	cbz	x1, .L4667
	ldr	x1, [x23, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x19, 276]
	ldr	w1, [x22, 1252]
	ldr	x3, [x23, 88]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x29, 88]
	blr	x3
	ldr	x1, [x23, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x19, 276]
.L4667:
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L4668
	ldr	x2, .LC1232
	mov	w3, 2537
	ldr	x1, .LC1238
	mov	w0, 0
	add	x2, x2, 576
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4635
	.p2align 3
.L4790:
	ldr	x20, .LC1229
	ldr	x4, [x20]
	cbz	x4, .L4650
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4650:
	mov	x0, x19
	bl	HEVC_DecVDM
	ldr	x1, [x19, 2984]
	cbz	w0, .L4771
	b	.L4780
	.p2align 3
.L4636:
	ldr	w2, [x1, 80]
	ldr	w3, [x1, 48]
	ldr	w0, [x19, 276]
	add	w3, w3, w2
	ldr	w1, [x21, 8]
	add	x2, x29, 88
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L4793
	ldr	x23, .LC1235
	mov	x2, 5
	ldr	x1, .LC1236
	ldr	x0, [x29, 88]
	ldr	x3, [x23, 104]
	add	x1, x1, 208
	blr	x3
	ldr	x1, [x19, 2984]
	ldr	x0, [x29, 88]
	ldr	w2, [x21, 4]
	ldr	x1, [x1, 40]
	add	x0, x0, 5
	ldr	x3, [x23, 104]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x21, 4]
	add	w0, w0, 5
	str	w0, [x21, 4]
	ldr	x1, [x19, 2984]
	ldr	w2, [x1, 80]
	cbz	w2, .L4640
	add	w3, w0, w2
	cmp	w3, 1024
	bls	.L4641
	uxtw	x2, w0
	ldr	x1, .LC1231
	mov	w3, 2342
	add	x2, x2, 5
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	cbz	x1, .L4642
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4642:
	ldr	x4, [x20]
	cbz	x4, .L4643
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4643:
	ldr	w0, [x19, 276]
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L4760
	ldr	x2, .LC1232
	mov	w3, 2349
	ldr	x1, .LC1238
	mov	w0, 0
	add	x2, x2, 576
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4635
.L4641:
	ldr	x4, [x29, 88]
	uxtw	x2, w2
	ldr	x1, [x1, 72]
	ldr	x3, [x23, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x19, 2984]
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 80]
	add	w0, w1, w0
	str	w0, [x21, 4]
.L4640:
	ldr	x20, .LC1239
	ldr	w0, [x19, 276]
	ldr	x1, [x20, w0, sxtw 3]
	cbz	x1, .L4644
	ldr	x1, [x23, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x19, 276]
	ldr	w1, [x22, 1252]
	ldr	x3, [x23, 88]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x29, 88]
	blr	x3
	ldr	x1, [x23, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x19, 276]
.L4644:
	ldr	x1, [x29, 88]
	bl	MetadataUnMapToSec
	cbz	w0, .L4668
	ldr	x2, .LC1232
	mov	w3, 2377
	ldr	x1, .LC1238
	mov	w0, 0
	add	x2, x2, 576
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4635
	.p2align 3
.L4791:
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsSkip
	mov	w0, w23
	b	.L4635
.L4788:
	ldr	x2, .LC1232
	mov	w3, 2495
	ldr	x1, .LC1234
	mov	w0, 0
	add	x2, x2, 576
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4635
.L4793:
	ldr	x2, .LC1232
	mov	w3, 2330
	ldr	x1, .LC1234
	mov	w0, 0
	add	x2, x2, 576
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4635
	.size	HEVC_VES_Splitter, .-HEVC_VES_Splitter
	.align	3
.LC1229:
	.xword	g_event_report
	.align	3
.LC1231:
	.xword	.LC1230
	.align	3
.LC1232:
	.xword	.LANCHOR3
	.align	3
.LC1234:
	.xword	.LC1233
	.align	3
.LC1235:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1236:
	.xword	.LANCHOR2
	.align	3
.LC1238:
	.xword	.LC1237
	.align	3
.LC1239:
	.xword	vfmw_save_metadata_file
	.align	3
.LC1241:
	.xword	.LC1240
	.align	3
.LC1243:
	.xword	.LC1242
	.align	3
.LC1245:
	.xword	.LC1244
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_CRAOutputFrame
	.type	HEVC_CRAOutputFrame, %function
HEVC_CRAOutputFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 3380]
	cbz	w0, .L4806
	sub	w2, w0, #1
	mov	w20, 0
	add	x2, x2, 462
	add	x0, x19, 3688
	add	x2, x19, x2, lsl 3
	.p2align 2
.L4797:
	ldr	x1, [x0], 8
	ldrb	w1, [x1, 2]
	cmp	w1, wzr
	csinc	w20, w20, w20, ne
	cmp	x0, x2
	bne	.L4797
	.p2align 2
.L4798:
	mov	x0, x19
	bl	HEVC_RemoveUnUsedFrameStore
	cbnz	w0, .L4798
	cmp	w20, wzr
	ble	.L4800
	.p2align 2
.L4813:
	ldr	w1, [x19, 3380]
	cbz	w1, .L4801
	ldr	x0, [x19, 3688]
	ldrb	w0, [x0, 2]
	cbz	w0, .L4808
	add	x2, x19, 3696
	mov	w0, 0
	b	.L4805
	.p2align 3
.L4802:
	ldr	x3, [x2], 8
	ldrb	w3, [x3, 2]
	cbz	w3, .L4807
.L4805:
	add	w0, w0, 1
	cmp	w0, w1
	bne	.L4802
.L4801:
	mov	x0, x19
	bl	HEVC_OutputOneFrmFromDPB
	cmn	w0, #1
	beq	.L4803
	subs	w20, w20, #1
	bne	.L4813
.L4800:
	mov	w0, 0
.L4803:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4807:
	mov	w1, w0
	b	.L4801
.L4808:
	mov	w1, 0
	b	.L4801
.L4806:
	mov	w20, 0
	b	.L4798
	.size	HEVC_CRAOutputFrame, .-HEVC_CRAOutputFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecSlice
	.type	HEVC_DecSlice, %function
HEVC_DecSlice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 2984]
	ldrsw	x3, [x19, 276]
	ldr	x2, .LC1246
	ldr	w1, [x0, 16]
	str	w1, [x19, 5596]
	ldr	w4, [x0, 28]
	str	w4, [x19, 5592]
	ldr	w20, [x0, 24]
	strb	wzr, [x19, 3]
	str	w20, [x19, 5600]
	ldr	x2, [x2, x3, lsl 3]
	ldrsb	w3, [x2, 44]
	cmp	w3, 1
	beq	.L4883
.L4821:
	ldr	w0, [x19, 5720]
	cmp	w0, 1
	beq	.L4884
.L4825:
	ldr	w0, [x19, 152]
	ldr	w2, [x19, 204]
	cmp	w2, w0
	bcs	.L4885
	add	x20, x19, 4096
	ldrb	w0, [x20, 761]
	cbz	w0, .L4886
	mov	x0, x19
	bl	HEVC_PicTypeStatistic
	mov	x0, x19
	bl	HEVC_CalcStreamBits
	ldr	w0, [x19, 5720]
	cmp	w0, 2
	beq	.L4843
	ldr	w0, [x19, 2368]
	cbnz	w0, .L4844
	ldrb	w0, [x20, 1473]
	cbz	w0, .L4887
.L4844:
	mov	x0, x19
	bl	HEVC_WriteSliceMsg
	cbnz	w0, .L4888
.L4847:
	ldr	w0, [x19, 2368]
	cbz	w0, .L4889
.L4849:
	ldr	w0, [x19, 4244]
	ldr	w1, [x19, 4240]
	str	w0, [x19, 4904]
	mov	w0, 0
	str	w1, [x19, 4900]
.L4830:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4889:
	ldr	w1, [x19, 5580]
	mov	w0, 1
	ldr	w2, [x19, 5604]
	str	w0, [x19, 172]
	str	w1, [x19, 284]
	str	w2, [x19, 328]
	b	.L4849
	.p2align 3
.L4884:
	ldr	w0, [x19, 2368]
	cbnz	w0, .L4827
	cmp	w20, wzr
	sub	w1, w1, #16
	cset	w21, eq
	cmp	w1, 4
	cset	w0, ls
	tst	w21, w0
	beq	.L4890
.L4828:
	mov	x0, x19
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L4891
.L4829:
	add	x0, x19, x20, uxtw
	ldrb	w0, [x0, 4]
	cmp	w0, 1
	cset	w0, eq
	tst	w21, w0
	beq	.L4831
	ldr	w0, [x19, 3380]
	cbnz	w0, .L4892
	.p2align 2
.L4831:
	ldr	x1, [x19, 3040]
	ldr	w0, [x1, 12]
	cbnz	w0, .L4832
	ldr	w0, [x19, 2376]
	cmp	w0, 1
	beq	.L4893
	ldr	w0, [x19, 5592]
	ldr	x2, [x19, 3008]
	add	x0, x2, x0, lsl 2
	ldr	w0, [x0, 360]
	cbnz	w20, .L4832
.L4898:
	ldr	w3, [x19, 212]
	mov	w20, -2147483647
	cmp	w3, w20
	beq	.L4832
	ldr	w2, [x19, 5580]
	add	w0, w3, w0
	cmp	w2, w0
	bge	.L4832
	ldr	w0, [x19, 5596]
	cmp	w0, 21
	bne	.L4832
	ldr	x1, .LC1253
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_CRAOutputFrame
	str	w20, [x19, 212]
	ldr	x1, [x19, 3040]
	.p2align 2
.L4832:
	ldr	w0, [x1, 8]
	cmp	w0, 2
	beq	.L4827
	ldr	w0, [x1, 24]
	cmp	w0, 2
	bne	.L4837
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L4894
.L4838:
	mov	x0, x19
	bl	HEVC_UpdateReflist
	mov	x0, x19
	bl	HEVC_UpdateLTReflist
.L4827:
	mov	x0, x19
	bl	HEVC_InitPic
	cmn	w0, #2
	beq	.L4830
	cbnz	w0, .L4895
	ldr	w1, [x19, 264]
	mov	x0, x19
	add	w1, w1, 1
	str	w1, [x19, 264]
	bl	HEVC_SetScalingList
	mov	x0, x19
	bl	HEVC_WritePicMsg
	cbz	w0, .L4825
	ldr	x1, .LC1257
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4830
	.p2align 3
.L4883:
	ldr	x3, [x2, 160]
	mov	x2, 1
	movk	x2, 0x2, lsl 32
	cmp	x3, x2
	bne	.L4821
	ldr	w0, [x0, 16]
	sub	w2, w0, #19
	cmp	w2, 1
	bls	.L4896
.L4823:
	sub	w0, w0, #6
	cmp	w0, 3
	bls	.L4821
	ldr	x2, [x19, 4280]
	str	x2, [x19, 4264]
	b	.L4821
	.p2align 3
.L4843:
	ldr	x1, [x19, 2984]
	cbz	x1, .L4847
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
	b	.L4847
	.p2align 3
.L4887:
	mov	x0, x19
	bl	HEVC_DecList
	cbnz	w0, .L4897
	mov	x0, x19
	bl	HEVC_IsRefListWrong
	cbz	w0, .L4844
	mov	x0, x19
	bl	HEVC_PrintDPBState
	ldr	x1, .LC1268
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4830
	.p2align 3
.L4890:
	ldr	w0, [x19, 4872]
	cbnz	w0, .L4829
	ldr	x0, [x19, 3040]
	mov	x1, 4294967296
	ldr	x2, [x0, 696]
	cmp	x2, x1
	bne	.L4829
	ldr	w1, [x0, 704]
	cbnz	w1, .L4829
	ldr	w0, [x0, 660]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L4829
	b	.L4828
	.p2align 3
.L4837:
	mov	x0, x19
	bl	HEVC_RefPicProcess
	cbz	w0, .L4827
	mov	w0, -1
	b	.L4830
.L4892:
	mov	x0, x19
	bl	HEVC_EmptyFrmFromDPB
	cbz	w0, .L4831
	ldr	x2, .LC1247
	mov	w0, 1
	ldr	x1, .LC1251
	add	x2, x2, 600
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4830
	.p2align 3
.L4886:
	ldr	x1, .LC1264
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4830
	.p2align 3
.L4893:
	ldr	x4, [x19, 3008]
	mov	w0, 0
	add	x2, x4, 360
	add	x4, x4, 392
	.p2align 2
.L4834:
	ldr	w3, [x2], 4
	cmp	w0, w3
	csel	w0, w0, w3, cs
	cmp	x2, x4
	bne	.L4834
	cbnz	w20, .L4832
	b	.L4898
	.p2align 3
.L4896:
	ldr	x2, [x19, 3040]
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L4824
	ldr	x3, [x19, 12784]
	str	x2, [x19, 12776]
	str	x3, [x19, 12792]
	str	x3, [x19, 12800]
.L4824:
	add	x2, x19, 12288
	mov	w3, 1
	strb	w3, [x2, 464]
	b	.L4823
	.p2align 3
.L4885:
	ldr	x1, .LC1259
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x19, 152]
	ldr	w2, [x19, 204]
	cmp	w2, w1
	bcc	.L4841
	ldr	x0, .LC1260
	ldr	x4, [x0]
	cbz	x4, .L4841
	ldr	w0, [x19, 276]
	mov	w3, 8
	stp	w2, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 108
	blr	x4
.L4841:
	ldr	x1, .LC1262
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, -1
	b	.L4830
	.p2align 3
.L4888:
	ldr	x1, .LC1270
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4830
	.p2align 3
.L4895:
	ldr	x1, .LC1255
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4830
.L4894:
	mov	x0, x19
	bl	HEVC_UpdateInterLayerReflist
	b	.L4838
.L4897:
	ldr	x1, .LC1266
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4830
.L4891:
	ldr	x2, .LC1247
	mov	w0, 1
	ldr	x1, .LC1249
	add	x2, x2, 600
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4830
	.size	HEVC_DecSlice, .-HEVC_DecSlice
	.align	3
.LC1246:
	.xword	s_pstVfmwChan
	.align	3
.LC1247:
	.xword	.LANCHOR3
	.align	3
.LC1249:
	.xword	.LC1248
	.align	3
.LC1251:
	.xword	.LC1250
	.align	3
.LC1253:
	.xword	.LC1252
	.align	3
.LC1255:
	.xword	.LC1254
	.align	3
.LC1257:
	.xword	.LC1256
	.align	3
.LC1259:
	.xword	.LC1258
	.align	3
.LC1260:
	.xword	g_event_report
	.align	3
.LC1262:
	.xword	.LC1261
	.align	3
.LC1264:
	.xword	.LC1263
	.align	3
.LC1266:
	.xword	.LC1265
	.align	3
.LC1268:
	.xword	.LC1267
	.align	3
.LC1270:
	.xword	.LC1269
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_DecOneNal
	.type	HEVC_DecOneNal, %function
HEVC_DecOneNal:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, [x19, 2984]
	ldr	w0, [x3, 8]
	cbz	w0, .L4904
	ldr	w2, [x19, 268]
	mov	w0, 0
	.p2align 2
.L4903:
	uxtw	x1, w0
	add	w0, w0, 1
	add	x1, x3, x1, lsl 5
	ldr	w1, [x1, 48]
	add	w2, w2, w1
	str	w2, [x19, 268]
	ldr	w1, [x3, 8]
	cmp	w1, w0
	bhi	.L4903
.L4904:
	strb	wzr, [x3]
	ldr	x0, [x19, 2984]
	ldr	w1, [x0, 16]
	sub	w1, w1, #36
	cmp	w1, 1
	bls	.L5047
.L4902:
	ldr	w1, [x0, 4]
	add	w1, w1, 16
	str	w1, [x0, 4]
	ldr	x1, [x19, 2984]
	ldr	w2, [x1, 16]
	cmp	w2, 49
	bls	.L5048
.L4905:
	ldr	x1, .LC1282
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	ldr	w0, [x1, 16]
	cmp	w0, 63
	bhi	.L4932
	cbnz	x1, .L5034
	.p2align 2
.L5032:
	mov	w0, 0
.L5051:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L5048:
	ldr	x0, .LC1271
	ldrb	w0, [x0,w2,uxtw]
	adr	x3, .Lrtx4907
	add	x0, x3, w0, sxtb #2
	br	x0
.Lrtx4907:
	.section	.rodata
	.align	0
	.align	2
.L4907:
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4906 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4908 - .Lrtx4907) / 4
	.byte	(.L4909 - .Lrtx4907) / 4
	.byte	(.L4910 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4911 - .Lrtx4907) / 4
	.byte	(.L4911 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4905 - .Lrtx4907) / 4
	.byte	(.L4912 - .Lrtx4907) / 4
	.byte	(.L4913 - .Lrtx4907) / 4
	.text
	.p2align 3
.L5047:
	mov	w1, 1
	strb	w1, [x19, 3]
	b	.L4902
.L4913:
	mov	x0, x19
	bl	HEVC_IsEosNal
	uxtb	w1, w0
	cmp	w1, 1
	beq	.L5049
.L4929:
	ldr	x1, [x19, 2984]
	cbz	x1, .L5032
.L5034:
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
	mov	w0, 0
.L5031:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L4906:
	mov	x0, x19
	bl	HEVC_DecSlice
	cmn	w0, #2
	beq	.L5031
	cbz	w0, .L5032
	ldr	x1, [x19, 2984]
	cbz	x1, .L5045
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L5045:
	ldr	x0, .LC1274
	ldr	x4, [x0]
	cbz	x4, .L5033
.L5035:
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L5033:
	mov	w0, -1
.L5050:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L4909:
	mov	x0, x19
	bl	HEVC_DecSPS
	mov	w20, w0
	ldr	x1, [x19, 2984]
	cbz	x1, .L4919
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4919:
	cbz	w20, .L5032
	ldr	x1, .LC1276
	b	.L5042
.L4910:
	mov	x0, x19
	bl	HEVC_DecPPS
	mov	w20, w0
	ldr	x1, [x19, 2984]
	cbz	x1, .L4921
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4921:
	cbz	w20, .L5032
	ldr	x1, .LC1278
	b	.L5042
.L4908:
	mov	x0, x19
	bl	HEVC_DecVPS
	mov	w20, w0
	ldr	x1, [x19, 2984]
	cbz	x1, .L4914
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4914:
	cbz	w20, .L5032
	ldr	x1, .LC1273
.L5042:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, .LC1274
	ldr	x4, [x21]
	cbz	x4, .L5033
	add	x2, x29, 64
	ldr	w0, [x19, 276]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x4, [x21]
	cbz	x4, .L5033
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
.L4911:
	mov	x0, x19
	bl	HEVC_DecSEI
	mov	w20, w0
	ldr	x1, [x19, 2984]
	cbz	x1, .L4922
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4922:
	cbz	w20, .L5032
	ldr	x1, .LC1280
	mov	w0, 1
	bl	dprint_vfmw
	b	.L5045
.L4912:
	ldrb	w0, [x19, 10]
	cmp	w0, 1
	beq	.L4927
	cbz	x1, .L4926
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4926:
	add	x0, x19, 4096
	ldrb	w0, [x0, 761]
	cbz	w0, .L5032
.L4927:
	add	x20, x19, 3336
	mov	w1, 32
	strb	wzr, [x19, 10]
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w21, w2
	ccmp	w0, w1, 0, eq
	bne	.L5032
	ldr	x20, .LC1274
	ldr	x4, [x20]
	cbz	x4, .L4928
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4928:
	add	x0, x19, 4096
	ldrb	w0, [x0, 761]
	cbz	w0, .L5032
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L5032
.L4931:
	ldr	x4, [x20]
	cbnz	x4, .L5035
	mov	w0, -1
	b	.L5050
	.p2align 3
.L4932:
	ldr	x20, .LC1274
	ldr	x4, [x20]
	cbz	x4, .L4933
	ldr	w0, [x19, 276]
	mov	w1, 102
	mov	w3, 0
	mov	x2, 0
	blr	x4
	ldr	x1, [x19, 2984]
	cbz	x1, .L4934
.L4935:
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L4934:
	ldr	x4, [x20]
	cbz	x4, .L5032
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, 0
	b	.L5051
.L4933:
	cbnz	x1, .L4935
	mov	w0, 0
	b	.L5051
.L5049:
	ldr	x20, .LC1274
	strb	w0, [x19, 11]
	ldr	x4, [x20]
	cbz	x4, .L4930
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4930:
	add	x0, x19, 4096
	ldrb	w0, [x0, 761]
	cbz	w0, .L4929
	mov	x0, x19
	bl	HEVC_DecVDM
	cbz	w0, .L4929
	ldr	x1, [x19, 2984]
	cbz	x1, .L4931
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
	b	.L4931
	.size	HEVC_DecOneNal, .-HEVC_DecOneNal
	.align	3
.LC1271:
	.xword	.L4907
	.align	3
.LC1273:
	.xword	.LC1272
	.align	3
.LC1274:
	.xword	g_event_report
	.align	3
.LC1276:
	.xword	.LC1275
	.align	3
.LC1278:
	.xword	.LC1277
	.align	3
.LC1280:
	.xword	.LC1279
	.align	3
.LC1282:
	.xword	.LC1281
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_UnMarkFrameStoreRef
	.type	HEVC_UnMarkFrameStoreRef, %function
HEVC_UnMarkFrameStoreRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	strb	wzr, [x19, 1]
	ldr	w1, [x19, 28]
	mov	w2, 0
	ldr	w0, [x20, 276]
	bl	FSP_SetRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_UnMarkFrameStoreRef, .-HEVC_UnMarkFrameStoreRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_InquireSliceProperty
	.type	HEVC_InquireSliceProperty, %function
HEVC_InquireSliceProperty:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x21, x2
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	str	wzr, [x21]
	ldr	x3, .LC1283
	add	x0, x19, 4096
	str	wzr, [x22]
	mov	x2, 1376
	mov	w1, 0
	add	x0, x0, 1472
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x1, [x19, 2984]
	mov	x0, x19
	ldr	w2, [x1, 16]
	str	w2, [x19, 5596]
	ldr	w2, [x1, 28]
	str	w2, [x19, 5592]
	ldr	w1, [x1, 24]
	str	w1, [x19, 5600]
	bl	HEVC_DecSliceSegmentHeader
	cbnz	w0, .L5074
	ldr	w1, [x19, 5604]
	mov	w3, 5036
	ldr	x0, [x19, 2968]
	mov	w20, 12668
	ldr	w23, [x19, 2368]
	ldr	x2, [x19, 2960]
	smaddl	x0, w1, w3, x0
	cmp	w23, 1
	ldr	w0, [x0, 32]
	smaddl	x20, w0, w20, x2
	beq	.L5075
	ldr	w0, [x19, 5720]
	cmp	w0, 1
	cset	w0, eq
	str	w0, [x22]
	ldr	x0, [x19, 3008]
	ldr	x1, [x19, 3040]
	ldr	w2, [x20, 184]
	ldp	w5, w3, [x0, 64]
	ldr	w0, [x0, 184]
	ldp	w6, w4, [x20, 64]
	cmp	w2, w0
	ldr	w0, [x1, 912]
	cset	w2, ne
	cmp	w0, 1
	beq	.L5076
.L5059:
	cmp	w6, w5
	cset	w0, ne
	cmp	w4, w3
	orr	w0, w2, w0
	cset	w1, ne
	orr	w0, w1, w0
	cbz	w0, .L5062
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	beq	.L5077
.L5063:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x21]
.L5055:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L5075:
	ldr	x0, [x19, 2944]
	bl	BsResidBits
	cmp	w0, wzr
	ldp	w2, w1, [x20, 188]
	ldr	w3, [x19, 204]
	mul	w1, w1, w2
	add	w3, w3, 1
	udiv	w3, w1, w3
	ccmp	w0, w3, 1, ge
	blt	.L5057
.L5062:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L5074:
	ldr	x1, .LC1285
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1286
	ldr	x4, [x0]
	cbz	x4, .L5064
	add	x2, x29, 80
	ldr	w0, [x19, 276]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L5076:
	ldr	w7, [x20, 96]
	ldr	w0, [x20, 88]
	cmp	w0, w7
	csel	w0, w0, w7, cs
	str	w0, [x1, 972]
	ldr	x0, [x19, 3008]
	ldr	x7, [x19, 3040]
	ldr	w1, [x0, 96]
	ldr	w0, [x0, 88]
	cmp	w0, w1
	csel	w0, w0, w1, cs
	ldr	w1, [x7, 972]
	cmp	w0, 8
	ccmp	w1, 8, 0, hi
	bne	.L5078
.L5060:
	mov	w0, 1
	str	w0, [x7, 976]
	str	w0, [x21]
	b	.L5059
	.p2align 3
.L5077:
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 24]
	tst	w0, -5
	beq	.L5063
	ldr	w1, [x19, 2396]
	mov	w0, 0
	cmp	w1, wzr
	cset	w1, eq
	str	w1, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L5064:
	mov	w0, -1
	b	.L5055
	.p2align 3
.L5078:
	cmp	w0, 8
	ccmp	w1, 8, 4, eq
	ble	.L5059
	b	.L5060
.L5057:
	ldr	x1, .LC1288
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L5055
	.size	HEVC_InquireSliceProperty, .-HEVC_InquireSliceProperty
	.align	3
.LC1283:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1285:
	.xword	.LC1284
	.align	3
.LC1286:
	.xword	g_event_report
	.align	3
.LC1288:
	.xword	.LC1287
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_HaveSliceToDec
	.type	HEVC_HaveSliceToDec, %function
HEVC_HaveSliceToDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	w0, [x19, 204]
	cbnz	w0, .L5080
	add	x0, x19, 4096
	mov	w20, -1
	ldrb	w0, [x0, 761]
	cbnz	w0, .L5084
.L5080:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5084:
	ldr	x2, .LC1289
	mov	w0, 0
	ldr	x1, .LC1291
	add	x2, x2, 616
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_HaveSliceToDec, .-HEVC_HaveSliceToDec
	.align	3
.LC1289:
	.xword	.LANCHOR3
	.align	3
.LC1291:
	.xword	.LC1290
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_GetPicStreamSize
	.type	HEVC_GetPicStreamSize, %function
HEVC_GetPicStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, [x19, 10048]
	mov	w0, 0
	cbz	x2, .L5086
	.p2align 2
.L5087:
	ldp	w3, w1, [x2]
	ldr	x2, [x2, 1504]
	add	w1, w3, w1
	add	w1, w1, 7
	add	w0, w0, w1, lsr 3
	cbnz	x2, .L5087
.L5086:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_GetPicStreamSize, .-HEVC_GetPicStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVC_IsFrameEndNal
	.type	HEVC_IsFrameEndNal, %function
HEVC_IsFrameEndNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sub	w0, w19, #32
	sub	w19, w19, #48
	cmp	w0, 2
	ccmp	w19, 1, 0, hi
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVC_IsFrameEndNal, .-HEVC_IsFrameEndNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_CheckSedOnly
	.type	HEVCDEC_CheckSedOnly, %function
HEVCDEC_CheckSedOnly:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 2364]
	str	wzr, [x19, 2368]
	cmp	w0, 2
	str	wzr, [x19, 2376]
	beq	.L5121
	cmp	w0, 1
	mov	w0, 0
	beq	.L5122
.L5113:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5122:
	ldr	w1, [x19, 2372]
	cmp	w1, 1
	bne	.L5113
	str	wzr, [x19, 2372]
	.p2align 2
.L5119:
	mov	w0, -1
	b	.L5113
	.p2align 3
.L5121:
	ldr	w0, [x19, 2360]
	cbz	w0, .L5119
	ldr	w1, [x19, 2372]
	mov	w0, 0
	cmp	w1, 1
	beq	.L5113
	ldr	w0, [x19, 276]
	bl	VCTRL_CheckFreshSeg
	cbz	w0, .L5119
	ldr	w0, [x19, 276]
	bl	VCTRL_CheckFreshRaw
	cbz	w0, .L5119
	ldr	x1, [x19, 2984]
	ldr	x0, [x19, 2944]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2944]
	mov	w1, 24
	bl	BsSkip
	ldr	x0, [x19, 2944]
	bl	BsResidBits
	cmp	w0, 15
	ble	.L5119
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsSkip
	ldr	x0, [x19, 2944]
	mov	w1, 6
	bl	BsGet
	mov	w20, w0
	ldr	x0, [x19, 2944]
	mov	w1, 9
	bl	BsSkip
	mov	w0, w20
	bl	HEVC_IsSliceUnit
	sxtb	w21, w0
	cmp	w21, 1
	beq	.L5123
	ldr	w0, [x19, 204]
	cbz	w0, .L5119
	sub	w0, w20, #32
	sub	w20, w20, #48
	cmp	w0, 2
	ccmp	w20, 1, 0, hi
	bhi	.L5119
.L5100:
	mov	x0, x19
	bl	HEVC_DecVDM
	cbnz	w0, .L5119
	add	x2, x19, 4096
	mov	w1, 1
	str	w1, [x19, 2376]
	mov	w0, -1
	strb	w1, [x2, 760]
	b	.L5113
	.p2align 3
.L5123:
	ldr	x0, [x19, 2944]
	bl	BsResidBits
	cmp	w0, wzr
	mov	w0, 0
	ble	.L5097
	ldr	x0, [x19, 2944]
	mov	w1, w21
	bl	BsGet
.L5097:
	ldr	w1, [x19, 204]
	cbnz	w1, .L5124
.L5098:
	add	x1, x19, 4096
	mov	w0, 1
	str	wzr, [x19, 2372]
	str	w0, [x19, 2368]
	mov	w0, 0
	ldrb	w1, [x1, 761]
	str	w1, [x19, 2380]
	b	.L5113
.L5124:
	sub	w1, w20, #32
	sub	w20, w20, #48
	cmp	w1, 2
	ccmp	w20, 1, 0, hi
	ccmp	w0, wzr, 0, hi
	beq	.L5098
	b	.L5100
	.size	HEVCDEC_CheckSedOnly, .-HEVCDEC_CheckSedOnly
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_IsNeedSedOnly
	.type	HEVCDEC_IsNeedSedOnly, %function
HEVCDEC_IsNeedSedOnly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 204]
	cbz	w0, .L5128
	ldr	x1, [x19, 3056]
	cbz	x1, .L5133
.L5128:
	mov	w0, 0
.L5127:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5133:
	ldr	w1, [x19, 7576]
	cmp	w1, 1
	bls	.L5128
	ldr	w1, [x19, 2384]
	cmp	w0, w1
	beq	.L5128
	ldr	w0, [x19, 2368]
	cmp	w0, 1
	beq	.L5134
	cbnz	w0, .L5128
	ldr	w0, [x19, 276]
	bl	VCTRL_CheckFreshRaw
	cbz	w0, .L5128
	ldr	w0, [x19, 276]
	bl	VCTRL_CheckFreshSeg
	cmp	w0, wzr
	cset	w0, ne
	b	.L5127
	.p2align 3
.L5134:
	ldr	x0, [x19, 2984]
	cmp	x0, xzr
	cset	w0, ne
	b	.L5127
	.size	HEVCDEC_IsNeedSedOnly, .-HEVCDEC_IsNeedSedOnly
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_SetDecParam
	.type	HEVCDEC_SetDecParam, %function
HEVCDEC_SetDecParam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w20, [x19, 2372]
	cmp	w20, 1
	beq	.L5151
.L5136:
	mov	x0, x19
	bl	HEVCDEC_IsNeedSedOnly
	cmp	w0, 1
	beq	.L5152
	ldr	w0, [x19, 2368]
	cmp	w0, 1
	beq	.L5153
.L5135:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5153:
	ldr	w2, [x19, 176]
	add	x0, x19, 4096
	ldr	w3, [x19, 204]
	ldr	w1, [x19, 260]
	sub	w2, w2, #1
	sub	w3, w3, #1
	str	w2, [x19, 176]
	sub	w1, w1, #1
	str	w3, [x19, 204]
	str	w1, [x19, 260]
	ldr	w2, [x19, 2380]
	strb	w2, [x0, 761]
.L5150:
	ldr	x1, [x19, 2984]
	cbz	x1, .L5135
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5151:
	ldr	w0, [x19, 204]
	cbz	w0, .L5136
	ldr	x0, [x19, 3056]
	cbnz	x0, .L5136
	mov	x0, x19
	bl	HEVC_DecVDM
	cbnz	w0, .L5150
	add	x0, x19, 4096
	str	w20, [x19, 2376]
	strb	w20, [x0, 760]
	b	.L5135
	.p2align 3
.L5152:
	ldr	w1, [x19, 204]
	ldr	x2, [x19, 3040]
	str	w0, [x19, 12740]
	add	x0, x19, 4096
	str	w1, [x19, 2384]
	add	x0, x0, 3456
	str	w1, [x19, 10040]
	ldr	w1, [x2, 692]
	str	w1, [x19, 8880]
	str	wzr, [x19, 2372]
	str	x0, [x19, 3056]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVCDEC_SetDecParam, .-HEVCDEC_SetDecParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_VDMProcSedOnly
	.type	HEVCDEC_VDMProcSedOnly, %function
HEVCDEC_VDMProcSedOnly:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x3, w20
	ldr	x1, [x19, 3056]
	lsl	x0, x3, 2
	ldr	x20, .LC1293
	sub	x3, x0, x3
	ldr	x4, .LC1292
	lsl	x0, x3, 4
	ldrsw	x5, [x19, 276]
	ldp	w21, w2, [x1, 20]
	sub	x3, x0, x3
	ldr	x1, .LC1295
	mov	w0, 22
	ldr	x22, [x4, x5, lsl 3]
	add	x20, x20, x3, lsl 2
	madd	w21, w2, w21, w21
	ldr	w3, [x20, 20]
	add	w21, w21, w2
	mov	w2, w21
	bl	dprint_vfmw
	ldr	w0, [x20, 20]
	cmp	w21, w0
	ldr	w0, [x19, 2368]
	beq	.L5164
	cmp	w0, 1
	beq	.L5165
.L5159:
	str	xzr, [x19, 3056]
.L5157:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5165:
	ldr	w2, [x19, 176]
	add	x0, x19, 4096
	ldr	w3, [x19, 204]
	ldr	w1, [x19, 260]
	sub	w2, w2, #1
	sub	w3, w3, #1
	str	w2, [x19, 176]
	sub	w1, w1, #1
	str	w3, [x19, 204]
	str	w1, [x19, 260]
	str	wzr, [x19, 2372]
	ldr	w2, [x19, 2380]
	strb	w2, [x0, 761]
	ldr	x1, [x19, 2984]
	cbz	x1, .L5159
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
	b	.L5159
	.p2align 3
.L5164:
	cmp	w0, 1
	beq	.L5156
	mov	x0, x19
	bl	HEVC_DecVDM
	cbnz	w0, .L5157
	add	x1, x19, 4096
	mov	w0, 1
	str	w0, [x19, 2376]
	strb	w0, [x1, 760]
	b	.L5157
	.p2align 3
.L5156:
	ldr	w2, [x19, 176]
	add	x4, x19, 4096
	ldr	w3, [x19, 204]
	ldr	w1, [x19, 260]
	sub	w2, w2, #1
	str	w0, [x19, 2372]
	sub	w3, w3, #1
	str	w2, [x19, 176]
	sub	w1, w1, #1
	str	w3, [x19, 204]
	str	w1, [x19, 260]
	ldr	w5, [x19, 2380]
	strb	w5, [x4, 761]
	strb	w0, [x22, 785]
	strb	w0, [x19, 9]
	mov	w0, 0
	str	xzr, [x19, 3056]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	HEVCDEC_VDMProcSedOnly, .-HEVCDEC_VDMProcSedOnly
	.align	3
.LC1292:
	.xword	s_pstVfmwChan
	.align	3
.LC1293:
	.xword	g_BackUp
	.align	3
.LC1295:
	.xword	.LC1294
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_AllocHevcGlbMem
	.type	HEVCDEC_AllocHevcGlbMem, %function
HEVCDEC_AllocHevcGlbMem:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x19, .LC1296
	ldr	x0, [x19]
	cbz	x0, .L5170
.L5167:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5170:
	ldr	x21, .LC1297
	mov	w0, 12624
	movk	w0, 0xa, lsl 16
	ldr	x1, [x21, 432]
	blr	x1
	str	x0, [x19]
	cbz	x0, .L5171
	ldr	x3, [x21, 96]
	mov	x2, 12624
	movk	x2, 0xa, lsl 16
	mov	w1, 0
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L5171:
	ldr	x1, .LC1299
	mov	w2, 15227
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L5167
	.size	HEVCDEC_AllocHevcGlbMem, .-HEVCDEC_AllocHevcGlbMem
	.align	3
.LC1296:
	.xword	.LANCHOR1
	.align	3
.LC1297:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1299:
	.xword	.LC1298
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_ReleaseHevcGlbMem
	.type	HEVCDEC_ReleaseHevcGlbMem, %function
HEVCDEC_ReleaseHevcGlbMem:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC1300
	ldr	x0, [x19]
	cbz	x0, .L5172
	ldr	x1, .LC1301
	ldr	x1, [x1, 440]
	blr	x1
	str	xzr, [x19]
.L5172:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	HEVCDEC_ReleaseHevcGlbMem, .-HEVCDEC_ReleaseHevcGlbMem
	.align	3
.LC1300:
	.xword	.LANCHOR1
	.align	3
.LC1301:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x0, .LC1302
	ldr	x0, [x0]
	cbz	x0, .L5188
	ldr	x20, .LC1305
	mov	x2, 29312
	mov	w1, 0
	mov	x0, x19
	ldr	w22, [x19, 7544]
	ldr	x3, [x20, 96]
	blr	x3
	str	x21, [x19, 3040]
	str	xzr, [x19, 3056]
	str	w22, [x19, 7544]
	ldr	w0, [x21, 28]
	cmp	w0, 25
	beq	.L5189
	mov	w0, 17
	mov	w3, 65
	mov	w2, 200
	mov	w1, 210
	stp	w2, w0, [x19, 152]
	stp	w0, w3, [x19, 160]
	str	w1, [x19, 168]
.L5181:
	ldr	w0, [x21, 632]
	bl	MEM_Phy2Vir
	mov	x5, x0
	cbz	x0, .L5190
	ldr	x11, [x19, 3040]
	mov	w2, 24912
	ldr	w12, [x19, 156]
	mov	w22, 12668
	ldpsw	x7, x6, [x19, 160]
	ldr	w8, [x11, 628]
	mov	w23, 5036
	ldrsw	x9, [x19, 152]
	ldr	w3, [x19, 168]
	madd	w1, w12, w2, w8
	lsl	w4, w9, 2
	add	x8, x0, x8, uxtw
	sub	w10, w4, w9
	str	x8, [x19, 2952]
	madd	w7, w22, w7, w1
	add	x1, x0, x1, uxtw
	str	x1, [x19, 2960]
	add	w1, w3, 1
	lsl	w4, w1, 3
	sub	w4, w4, w1
	lsl	w4, w4, 1
	sub	w1, w4, w1
	lsl	w4, w10, 6
	madd	w6, w23, w6, w7
	sub	w4, w4, w10
	add	x7, x0, x7, uxtw
	str	x7, [x19, 2968]
	add	w4, w6, w4, lsl 3
	add	x0, x0, x6, uxtw
	add	w1, w4, w1, lsl 3
	str	x0, [x19, 3048]
	add	x4, x5, x4, uxtw
	str	x4, [x19, 3032]
	add	x5, x5, x1, uxtw
	str	x5, [x19, 3024]
	add	w3, w1, w3, lsl 3
	ldr	w4, [x11, 636]
	cmp	w3, w4
	bhi	.L5191
	ldr	w1, [x21, 664]
	cbz	w1, .L5192
.L5184:
	lsl	x2, x9, 2
	ldr	x3, [x20, 96]
	sub	x9, x2, x9
	mov	w1, 0
	lsl	x2, x9, 6
	sub	x2, x2, x9
	lsl	x2, x2, 3
	blr	x3
	ldr	w2, [x19, 168]
	mov	w4, 104
	ldr	x3, [x20, 96]
	mov	w1, 0
	add	w2, w2, 1
	ldr	x0, [x19, 3032]
	smull	x2, w2, w4
	blr	x3
	ldrsw	x2, [x19, 168]
	mov	w1, 0
	ldr	x3, [x20, 96]
	ldr	x0, [x19, 3024]
	lsl	x2, x2, 3
	blr	x3
	ldp	w5, w4, [x19, 156]
	mov	x1, -24912
	mov	w0, 24912
	ldr	w2, [x19, 164]
	mov	w8, 5036
	ldr	x9, [x19, 2952]
	mov	x7, -5036
	smaddl	x0, w5, w0, x1
	mov	w3, 12668
	mov	x1, -12668
	ldr	x6, [x19, 2968]
	smaddl	x3, w4, w3, x1
	ldr	x4, [x19, 2960]
	add	x1, x9, x0
	smaddl	x0, w2, w8, x7
	str	x1, [x19, 3000]
	add	x2, x4, x3
	add	x0, x6, x0
	str	x2, [x19, 3008]
	str	x0, [x19, 3016]
	mov	x0, x19
	str	w5, [x1, 4]
	ldr	x1, [x19, 3016]
	ldr	w2, [x19, 160]
	str	w2, [x1, 28]
	ldr	x1, [x19, 3008]
	ldr	w2, [x19, 164]
	str	w2, [x1, 56]
	bl	HEVC_InitScalingOrderTable
	mov	x0, x19
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 276]
	beq	.L5185
	mov	w1, -2147483647
	mov	x0, x19
	stp	w1, w1, [x19, 212]
	bl	HEVC_InitDecPara
	str	wzr, [x19, 12808]
	ldr	w0, [x19, 164]
	mov	w2, 9999
	ldr	x1, [x19, 3040]
	str	w0, [x19, 328]
	mov	w0, 1
	str	w2, [x19, 284]
	strb	w0, [x19]
	ldr	w0, [x1, 12]
	cbnz	w0, .L5186
.L5187:
	str	wzr, [x19, 2388]
	mov	w0, 0
	ldr	w1, [x1, 680]
	str	w1, [x19, 2360]
.L5179:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L5186:
	mov	w0, 6
	str	w0, [x1, 24]
	ldr	x1, [x19, 3040]
	b	.L5187
	.p2align 3
.L5192:
	smull	x2, w12, w2
	ldr	x3, [x20, 96]
	mov	x0, x8
	blr	x3
	ldr	w2, [x19, 160]
	mov	w1, 0
	ldr	x3, [x20, 96]
	ldr	x0, [x19, 2960]
	smull	x2, w2, w22
	blr	x3
	ldr	w2, [x19, 164]
	mov	w1, 0
	ldr	x0, [x19, 2968]
	ldr	x3, [x20, 96]
	smull	x2, w2, w23
	blr	x3
	ldrsw	x9, [x19, 152]
	ldr	x0, [x19, 3048]
	b	.L5184
	.p2align 3
.L5189:
	ldr	w0, [x21, 744]
	str	w0, [x19, 156]
	ldr	w0, [x21, 748]
	str	w0, [x19, 160]
	ldr	w0, [x21, 752]
	str	w0, [x19, 164]
	ldr	w0, [x21, 740]
	str	w0, [x19, 152]
	add	w0, w0, 5
	str	w0, [x19, 168]
	b	.L5181
	.p2align 3
.L5191:
	ldr	x2, .LC1303
	mov	w0, 0
	ldr	x1, .LC1309
	add	x2, x2, 640
	bl	dprint_vfmw
	mov	w0, -20
	b	.L5179
.L5188:
	ldr	x2, .LC1303
	ldr	x1, .LC1304
	add	x2, x2, 640
	bl	dprint_vfmw
	mov	w0, -20
	b	.L5179
.L5185:
	ldr	x2, .LC1303
	mov	w0, 0
	ldr	x1, .LC1311
	add	x2, x2, 640
	bl	dprint_vfmw
	mov	w0, -20
	b	.L5179
.L5190:
	ldr	x2, .LC1303
	mov	w0, 0
	ldr	x1, .LC1307
	add	x2, x2, 640
	bl	dprint_vfmw
	mov	w0, -20
	b	.L5179
	.size	HEVCDEC_Init, .-HEVCDEC_Init
	.align	3
.LC1302:
	.xword	.LANCHOR1
	.align	3
.LC1303:
	.xword	.LANCHOR3
	.align	3
.LC1304:
	.xword	.LC166
	.align	3
.LC1305:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1307:
	.xword	.LC1306
	.align	3
.LC1309:
	.xword	.LC1308
	.align	3
.LC1311:
	.xword	.LC1310
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageBuffer
	.type	HEVCDEC_GetImageBuffer, %function
HEVCDEC_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 180]
	cbz	w0, .L5196
	add	x20, x19, 4096
	ldrb	w0, [x20, 761]
	cmp	w0, 1
	beq	.L5196
	add	x1, x19, 12288
	add	x4, x19, 28672
	add	x1, x1, 2464
	add	x4, x4, 640
	.p2align 2
.L5202:
	ldr	w0, [x1, 48]
	cbnz	w0, .L5197
	cbz	x1, .L5198
	ldr	w3, [x19, 3380]
	cbz	w3, .L5198
	ldr	x0, [x19, 3688]
	cmp	x0, x1
	beq	.L5197
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L5199
	.p2align 3
.L5200:
	ldr	x2, [x0, 3688]
	cmp	x2, x1
	beq	.L5197
.L5199:
	cmp	x3, x0
	add	x0, x0, 8
	bne	.L5200
.L5198:
	ldr	w0, [x19, 276]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L5196
	cmn	w0, #1
	beq	.L5221
.L5220:
	mov	w0, 0
.L5222:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5196:
	ldp	x19, x20, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5197:
	add	x1, x1, 728
	cmp	x1, x4
	bne	.L5202
	add	x2, x29, 44
	add	x1, x29, 40
	add	x0, x20, 2848
	bl	GetQueueImgNum
	mov	x0, x19
	bl	HEVC_PrintFrameStoreState
	ldr	x1, .LC1315
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_PrintDPBState
	ldr	w0, [x19, 180]
	ldr	w2, [x19, 3380]
	ldp	w3, w4, [x29, 40]
	sub	w0, w0, #2
	sub	w0, w0, w2
	add	w1, w3, w4
	cmp	w1, w0
	bge	.L5220
	ldr	x2, .LC1316
	mov	w0, 0
	ldr	x1, .LC1318
	add	x2, x2, 656
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L5221:
	ldr	x1, .LC1313
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 276]
	add	x1, x20, 2848
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	b	.L5222
	.size	HEVCDEC_GetImageBuffer, .-HEVCDEC_GetImageBuffer
	.align	3
.LC1313:
	.xword	.LC1312
	.align	3
.LC1315:
	.xword	.LC1314
	.align	3
.LC1316:
	.xword	.LANCHOR3
	.align	3
.LC1318:
	.xword	.LC1317
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_DecodePacket
	.type	HEVCDEC_DecodePacket, %function
HEVCDEC_DecodePacket:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	str	wzr, [x29, 100]
	stp	wzr, wzr, [x29, 92]
	cbz	x20, .L5311
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L5312
	ldr	x2, [x19, 3040]
	ldrb	w0, [x19, 9]
	cmp	w0, 1
	ldr	w0, [x2, 8]
	ubfiz	w0, w0, 16, 3
	str	w0, [x19, 272]
	beq	.L5227
	ldr	w0, [x2, 912]
	cmp	w0, 1
	beq	.L5313
.L5228:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_ReceivePacket
	mov	w20, w0
	ldr	x0, [x19, 2984]
	str	x0, [x19, 2992]
.L5229:
	strb	wzr, [x19, 9]
	cbz	w20, .L5314
.L5308:
	mov	w0, 0
.L5291:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L5314:
	mov	x0, x19
	bl	HEVCDEC_CheckSedOnly
	cbz	w0, .L5231
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 960]
	cmp	w0, 1
	bne	.L5315
.L5231:
	ldr	x0, [x19, 2984]
	str	wzr, [x0, 4]
	ldr	x1, [x19, 2984]
	ldr	x0, [x19, 2944]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2944]
	mov	w1, 24
	bl	BsSkip
	ldr	x21, .LC1325
	ldrsw	x0, [x19, 276]
	ldr	x0, [x21, x0, lsl 3]
	ldrsb	w20, [x0, 44]
	cmp	w20, 1
	beq	.L5316
	mov	w22, 3
	mov	w23, 2
.L5307:
	mov	w20, 0
.L5233:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x24, [x19, 2984]
	ldr	x0, [x19, 2944]
	mov	w1, 6
	bl	BsGet
	str	w0, [x24, 16]
	mov	w1, 6
	ldr	x24, [x19, 2984]
	ldr	x0, [x19, 2944]
	bl	BsGet
	str	w0, [x24, 24]
	ldr	x24, [x19, 2984]
	ldr	w2, [x24, 24]
	cmp	w2, 1
	bls	.L5234
	mov	w3, 1
	ldr	x1, .LC1327
	mov	w0, w3
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	cbz	x1, .L5309
.L5235:
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L5309:
	mov	w0, -1
.L5324:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L5313:
	ldr	w0, [x2, 960]
	cmp	w0, 1
	bne	.L5228
	ldr	w0, [x19, 352]
	cmp	w0, 1
	bne	.L5228
	ldr	x0, [x19, 2992]
	str	x0, [x19, 2984]
	mov	w0, 0
	strb	wzr, [x19, 9]
	str	wzr, [x19, 352]
	b	.L5291
	.p2align 3
.L5227:
	ldr	x0, [x19, 2984]
	cmp	x0, xzr
	csetm	w20, eq
	cbz	w20, .L5229
	ldr	x1, .LC1324
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w20
	b	.L5291
	.p2align 3
.L5234:
	ldr	x0, [x19, 3040]
	ldr	w3, [x0, 24]
	and	w0, w3, -5
	cmp	w0, wzr
	ccmp	w2, wzr, 4, eq
	bne	.L5317
	ldr	x0, [x19, 2944]
	mov	w1, 3
	bl	BsGet
	str	w0, [x24, 28]
	ldr	x24, [x19, 2984]
	ldr	w0, [x24, 28]
	cbz	w0, .L5238
	sub	w0, w0, #1
	str	w0, [x24, 28]
	ldr	x24, [x19, 2984]
.L5238:
	ldr	w0, [x24, 16]
	bl	HEVC_IsSliceUnit
	sxtb	w25, w0
	cmp	w25, 1
	beq	.L5318
	str	wzr, [x24, 4]
	add	x0, x19, 3336
	ldr	x1, [x19, 2984]
	ldr	w2, [x1, 48]
	ldr	x1, [x1, 40]
	bl	BsInit
	ldr	x0, [x19, 2944]
	mov	w1, 24
	bl	BsSkip
	cmp	w23, 1
	ccmp	w22, 1, 0, eq
	ccmp	w20, 1, 4, eq
	beq	.L5253
	ldr	x0, [x19, 2944]
	mov	w1, 16
	bl	BsSkip
.L5253:
	ldr	x0, [x19, 2944]
	mov	w1, 1
	bl	BsGet
	ldr	x20, [x19, 2984]
	ldr	x0, [x19, 2944]
	mov	w1, 6
	bl	BsGet
	str	w0, [x20, 16]
	mov	w1, 6
	ldr	x20, [x19, 2984]
	ldr	x0, [x19, 2944]
	bl	BsGet
	str	w0, [x20, 24]
	mov	w1, 3
	ldr	x20, [x19, 2984]
	ldr	x0, [x19, 2944]
	bl	BsGet
	str	w0, [x20, 28]
	ldr	x1, [x19, 2984]
	ldr	w0, [x1, 28]
	cbnz	w0, .L5319
.L5243:
	mov	x0, x19
	bl	HEVC_DecOneNal
	cmn	w0, #2
	beq	.L5291
	cbnz	w0, .L5320
	ldr	w0, [x19, 2360]
	str	wzr, [x19, 4912]
	cmp	w0, 1
	bne	.L5308
	mov	x0, x19
	bl	HEVCDEC_SetDecParam
	b	.L5308
	.p2align 3
.L5316:
	ldp	w23, w22, [x0, 156]
	ldr	w3, [x0, 164]
	mov	x0, x19
	mov	w2, w22
	mov	w1, w23
	bl	HEVC_VES_Splitter
	cmp	w0, 2
	beq	.L5233
	cmp	w0, 1
	bne	.L5291
	b	.L5307
	.p2align 3
.L5319:
	sub	w0, w0, #1
	str	w0, [x1, 28]
	b	.L5243
	.p2align 3
.L5312:
	ldr	x1, .LC1322
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L5291
	.p2align 3
.L5318:
	add	x2, x29, 108
	add	x1, x29, 104
	mov	x0, x19
	bl	HEVC_InquireSliceProperty
	cbnz	w0, .L5240
	ldr	w20, [x29, 104]
	cmp	w20, 1
	beq	.L5321
.L5241:
	ldr	w20, [x29, 108]
	cmp	w20, 1
	bne	.L5243
	ldr	x0, [x19, 2984]
	ldr	w0, [x0, 24]
	add	x0, x19, x0
	ldrb	w22, [x0, 4]
	mov	x0, x19
	cmp	w22, 1
	beq	.L5322
	bl	HEVC_FlushOutputFrmFromDPB
	cbnz	w0, .L5323
.L5246:
	ldr	w0, [x19, 276]
	bl	FSP_GetFspType
	cbnz	w0, .L5243
	ldr	w0, [x19, 276]
	add	x3, x29, 100
	add	x2, x29, 96
	add	x1, x29, 92
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 3040]
	ldr	w0, [x0, 772]
	cmp	w0, 1
	bne	.L5243
	ldr	w1, [x29, 100]
	cmp	w1, wzr
	bgt	.L5249
	ldr	w2, [x29, 96]
	cmp	w2, 32
	bgt	.L5249
	ldr	x2, [x19, 3056]
	cbnz	x2, .L5249
	ldr	w2, [x29, 108]
	cbz	w2, .L5243
	ldr	w3, [x19, 264]
	cbz	w3, .L5243
	ldr	x3, [x19, 3008]
	ldr	w4, [x19, 344]
	ldr	w6, [x3, 68]
	cmp	w6, w4
	beq	.L5243
	ldr	w5, [x3, 64]
	cmp	w1, wzr
	ldr	w3, [x19, 348]
	ccmp	w5, w3, 4, eq
	beq	.L5243
	ldr	x1, .LC1335
	bl	dprint_vfmw
	ldr	x0, [x19, 3008]
	ldr	x1, .LC1336
	ldr	w2, [x0, 68]
	str	w2, [x19, 344]
	ldr	x4, [x1]
	ldr	w0, [x0, 64]
	str	w0, [x19, 348]
	cbz	x4, .L5243
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L5243
	.p2align 3
.L5317:
	ldr	x1, .LC1329
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	cbnz	x1, .L5235
	mov	w0, -1
	b	.L5324
	.p2align 3
.L5315:
	ldr	x1, [x19, 2984]
	cbz	x1, .L5232
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L5232:
	mov	x0, x19
	bl	HEVCDEC_SetDecParam
	mov	w0, -1
	b	.L5291
.L5240:
	ldr	x1, .LC1338
	mov	w0, w25
	bl	dprint_vfmw
	ldr	x1, [x19, 2984]
	cbz	x1, .L5251
	ldr	w0, [x19, 276]
	bl	HEVC_ReleaseNAL
	str	xzr, [x19, 2984]
.L5251:
	ldr	x0, .LC1336
	ldr	x4, [x0]
	cbz	x4, .L5252
	ldr	w0, [x19, 276]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L5252:
	ldrsw	x0, [x19, 276]
	ldr	x0, [x21, x0, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	bne	.L5309
	ldr	x1, [x0, 160]
	mov	x0, 1
	movk	x0, 0x2, lsl 32
	cmp	x1, x0
	bne	.L5309
	add	x0, x19, 12288
	ldrb	w1, [x0, 464]
	cbnz	w1, .L5309
	ldr	x3, .LC1339
	mov	x2, 56
	add	x0, x0, 464
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x19, 4236]
	mov	w0, -1
	str	xzr, [x19, 4256]
	str	xzr, [x19, 4264]
	str	xzr, [x19, 4272]
	str	xzr, [x19, 4280]
	b	.L5291
.L5321:
	ldr	w1, [x19, 204]
	cbnz	w1, .L5242
	add	x1, x19, 4096
	ldrb	w1, [x1, 761]
	cbz	w1, .L5241
	ldr	x2, .LC1330
	ldr	x1, .LC1331
	add	x2, x2, 616
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	b	.L5241
.L5311:
	ldr	x1, .LC1320
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L5291
.L5242:
	ldr	x3, [x19, 2984]
	mov	w2, 21
	ldr	x1, .LC1330
	add	x0, x19, 3336
	str	wzr, [x3, 4]
	add	x1, x1, 704
	bl	BsInit
	ldr	x0, [x19, 2944]
	mov	w1, 40
	bl	BsSkip
	ldr	x1, [x19, 2984]
	mov	w2, 48
	mov	x0, x19
	str	w2, [x1, 16]
	strb	w20, [x19, 10]
	bl	HEVC_DecOneNal
	strb	w20, [x19, 9]
	ldr	w1, [x19, 312]
	mov	w0, -2
	add	w1, w1, 1
	str	w1, [x19, 312]
	b	.L5291
.L5322:
	bl	HEVC_EmptyFrmFromDPB
	cbz	w0, .L5246
	ldr	x2, .LC1330
	mov	w0, w22
	ldr	x1, .LC1332
	add	x2, x2, 680
	bl	dprint_vfmw
	b	.L5246
.L5320:
	ldr	x1, .LC1341
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L5291
.L5323:
	ldr	x2, .LC1330
	mov	w0, w20
	ldr	x1, .LC1333
	add	x2, x2, 680
	bl	dprint_vfmw
	b	.L5246
.L5249:
	ldrsw	x2, [x19, 276]
	mov	w1, 1
	mov	w0, -2
	ldr	x2, [x21, x2, lsl 3]
	str	w1, [x2, 1632]
	strb	w1, [x19, 9]
	b	.L5291
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	3
.LC1320:
	.xword	.LC1319
	.align	3
.LC1322:
	.xword	.LC1321
	.align	3
.LC1324:
	.xword	.LC1323
	.align	3
.LC1325:
	.xword	s_pstVfmwChan
	.align	3
.LC1327:
	.xword	.LC1326
	.align	3
.LC1329:
	.xword	.LC1328
	.align	3
.LC1330:
	.xword	.LANCHOR3
	.align	3
.LC1331:
	.xword	.LC1290
	.align	3
.LC1332:
	.xword	.LC1250
	.align	3
.LC1333:
	.xword	.LC1248
	.align	3
.LC1335:
	.xword	.LC1334
	.align	3
.LC1336:
	.xword	g_event_report
	.align	3
.LC1338:
	.xword	.LC1337
	.align	3
.LC1339:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1341:
	.xword	.LC1340
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_VDMPostProc
	.type	HEVCDEC_VDMPostProc, %function
HEVCDEC_VDMPostProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w23, w1
	mov	x21, x3
	mov	w22, w4
	mov	w20, w5
	bl	_mcount
	ldr	x0, [x19, 3040]
	ldr	x2, [x19, 4920]
	ldr	w24, [x0, 684]
	str	w23, [x19, 4896]
	cbz	x2, .L5326
	add	x0, x19, 4096
	ldrb	w1, [x0, 3461]
	strb	w1, [x2, 3]
	ldrb	w0, [x0, 3456]
	strb	w0, [x2, 4]
	ldr	x0, [x19, 3040]
.L5326:
	ldr	w1, [x19, 2388]
	cmp	w1, 1
	bls	.L5327
.L5330:
	ldr	w1, [x19, 4876]
	cmp	w1, 1920
	bls	.L5328
	ldr	w1, [x0, 8]
	cmp	w1, 2
	beq	.L5328
	str	wzr, [x19, 2360]
	cbz	w22, .L5333
.L5362:
	ldr	x5, .LC1342
	sbfiz	x20, x20, 6, 32
	add	x20, x5, x20
	ldr	w0, [x20, 44]
	cmp	w0, 3
	beq	.L5359
	cmp	w0, 1
	beq	.L5333
	cmp	w24, 1
	beq	.L5360
.L5337:
	mov	x1, x21
	mov	x0, x19
	bl	HEVC_StorePicInDPB
	cbnz	w0, .L5361
.L5347:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x19, 172]
.L5335:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L5327:
	add	w1, w1, 1
	str	w1, [x19, 2388]
	cmp	w1, 1
	bhi	.L5330
.L5328:
	ldr	w0, [x0, 680]
	str	w0, [x19, 2360]
	cbnz	w22, .L5362
.L5333:
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	cmp	w24, 1
	bne	.L5337
.L5360:
	ldr	x20, [x19, 3056]
	ldr	w0, [x20, 1292]
	add	x0, x20, x0, lsl 2
	ldr	w23, [x0, 1476]
	mov	w0, w23
	bl	MEM_Phy2Vir
	mov	x22, x0
	ldp	w7, w2, [x20, 192]
	ldr	x3, .LC1343
	mov	w1, w23
	add	w2, w2, 15
	add	w7, w7, 15
	and	w2, w2, -16
	and	w7, w7, -16
	ldr	x3, [x3, 280]
	mul	w7, w2, w7
	lsr	w20, w7, 8
	lsl	w2, w20, 4
	blr	x3
	cbz	w20, .L5348
	mov	w7, 0
	mov	w6, 0
	mov	w4, 2147483647
	mov	w5, 0
	mov	w2, 0
	.p2align 2
.L5344:
	ubfiz	x1, x2, 4, 28
	add	x1, x22, x1
	ldrsh	w3, [x1, 4]
	neg	w0, w3
	and	w8, w3, 32767
	tbz	x3, 15, .L5340
	and	w8, w0, 32767
.L5340:
	ldrsh	w1, [x1, 6]
	neg	w3, w1
	and	w0, w1, 32767
	tbz	x1, 15, .L5342
	and	w0, w3, 32767
.L5342:
	add	w0, w8, w0
	add	w2, w2, 1
	cmp	w4, w0
	add	w7, w7, w0
	csel	w4, w4, w0, le
	cmp	w5, w0
	csel	w5, w5, w0, ge
	cmp	w0, wzr
	csinc	w6, w6, w6, ne
	cmp	w20, w2
	bne	.L5344
	lsl	w0, w6, 2
	sub	w0, w0, w6
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w6, w0, w6
.L5338:
	udiv	w6, w6, w20
	ldr	x0, [x19, 4920]
	cmp	w6, 100
	csel	w4, w4, wzr, ne
	udiv	w7, w7, w20
	cbz	x0, .L5346
	str	w5, [x0, 332]
	mov	x1, x21
	ldr	x0, [x19, 4920]
	str	w4, [x0, 336]
	ldr	x0, [x19, 4920]
	str	w7, [x0, 340]
	ldr	x0, [x19, 4920]
	str	w6, [x0, 344]
	mov	x0, x19
	str	w5, [x19, 5172]
	str	w4, [x19, 5176]
	str	w7, [x19, 5180]
	str	w6, [x19, 5184]
	bl	HEVC_StorePicInDPB
	cbz	w0, .L5347
.L5361:
	ldr	x1, .LC1347
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	mov	x0, x19
	bl	HEVC_ClearDPB
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L5359:
	mov	x0, x19
	bl	HEVC_ClearAllSlice
	mov	w0, 0
	b	.L5335
.L5348:
	mov	w6, 0
	mov	w7, 0
	mov	w4, 2147483647
	mov	w5, 0
	b	.L5338
.L5346:
	ldr	x1, .LC1345
	mov	w0, 0
	bl	dprint_vfmw
	b	.L5337
	.size	HEVCDEC_VDMPostProc, .-HEVCDEC_VDMPostProc
	.align	3
.LC1342:
	.xword	g_VdmDrvParam
	.align	3
.LC1343:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1345:
	.xword	.LC1344
	.align	3
.LC1347:
	.xword	.LC1346
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageWidth
	.type	HEVCDEC_GetImageWidth, %function
HEVCDEC_GetImageWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L5365
	ldr	x0, [x19, 3008]
	ldr	w1, [x0, 132]
	ldr	w0, [x0, 64]
	add	w0, w1, w0
	neg	w1, w1
	sub	w0, w0, #1
	and	w0, w0, w1
.L5364:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L5365:
	mov	w0, -1
	b	.L5364
	.size	HEVCDEC_GetImageWidth, .-HEVCDEC_GetImageWidth
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetImageHeight
	.type	HEVCDEC_GetImageHeight, %function
HEVCDEC_GetImageHeight:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L5368
	ldr	x0, [x19, 3008]
	ldr	w1, [x0, 132]
	ldr	w0, [x0, 68]
	add	w0, w1, w0
	neg	w1, w1
	sub	w0, w0, #1
	and	w0, w0, w1
.L5367:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L5368:
	mov	w0, -1
	b	.L5367
	.size	HEVCDEC_GetImageHeight, .-HEVCDEC_GetImageHeight
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HEVCDEC_GetRemainImg
	.type	HEVCDEC_GetRemainImg, %function
HEVCDEC_GetRemainImg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 3380]
	cbz	w0, .L5374
	ldr	x0, .LC1348
	mov	w21, 1
	ldr	x23, .LC1349
	add	x22, x0, 728
	.p2align 2
.L5370:
	add	x2, x29, 72
	add	x1, x29, 76
	mov	x0, x19
	bl	HEVC_GetMinPOC
	ldr	w2, [x29, 72]
	mov	x0, x19
	add	x1, x19, x2, uxtw 3
	ldr	x20, [x1, 3688]
	mov	x1, x20
	cbz	x20, .L5371
	ldrb	w3, [x20, 2]
	cmp	w3, 1
	beq	.L5371
	strb	w21, [x20, 2]
	bl	HEVC_GetImagePara
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_CheckFrameStore
	cbz	w0, .L5385
.L5384:
	ldr	w2, [x29, 72]
.L5371:
	mov	w1, w2
	mov	x0, x19
	bl	HEVC_RemoveApcStore
	ldr	w1, [x29, 72]
	mov	x0, x19
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	w0, [x19, 3380]
	cbnz	w0, .L5370
.L5374:
	add	x0, x19, 4096
	add	x0, x0, 2848
	bl	GetVoLastImageID
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L5385:
	mov	x1, x20
	mov	x0, x19
	bl	HEVC_OutputFrame
	cbz	w0, .L5384
	mov	x1, x23
	mov	x2, x22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x19
	bl	HEVC_ClearAll
	b	.L5384
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.align	3
.LC1348:
	.xword	.LANCHOR3
	.align	3
.LC1349:
	.xword	.LC1102
	.global	g_pGlbVar
	.global	g_RpuStartCode
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.13581, %object
	.size	__func__.13581, 17
__func__.13581:
	.string	"HEVC_OutputFrame"
	.zero	7
	.type	__func__.12039, %object
	.size	__func__.12039, 26
__func__.12039:
	.string	"HEVC_OutputImgToViewQueue"
	.zero	6
	.type	__func__.11468, %object
	.size	__func__.11468, 24
__func__.11468:
	.string	"HEVC_CheckVpsExtOverlap"
	.type	__func__.11473, %object
	.size	__func__.11473, 24
__func__.11473:
	.string	"HEVC_CheckPpsExtOverlap"
	.type	__func__.11478, %object
	.size	__func__.11478, 26
__func__.11478:
	.string	"HEVC_CheckSliceExtOverlap"
	.zero	6
	.type	SarTable.12233, %object
	.size	SarTable.12233, 136
SarTable.12233:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	12
	.word	11
	.word	10
	.word	11
	.word	16
	.word	11
	.word	40
	.word	33
	.word	24
	.word	11
	.word	20
	.word	11
	.word	32
	.word	11
	.word	80
	.word	33
	.word	18
	.word	11
	.word	15
	.word	11
	.word	64
	.word	33
	.word	160
	.word	99
	.word	4
	.word	3
	.word	3
	.word	2
	.word	2
	.word	1
	.type	__func__.12391, %object
	.size	__func__.12391, 18
__func__.12391:
	.string	"HEVC_CalcTileInfo"
	.zero	6
	.type	__func__.12864, %object
	.size	__func__.12864, 27
__func__.12864:
	.string	"HEVC_GetUnRefPicWithMinPoc"
	.zero	5
	.type	__func__.12873, %object
	.size	__func__.12873, 21
__func__.12873:
	.string	"HEVC_IncreaseDPBSize"
	.zero	3
	.type	__func__.13106, %object
	.size	__func__.13106, 17
__func__.13106:
	.string	"HEVC_CalcTileMap"
	.zero	7
	.type	__func__.13126, %object
	.size	__func__.13126, 17
__func__.13126:
	.string	"HEVC_WritePicMsg"
	.zero	7
	.type	__func__.13155, %object
	.size	__func__.13155, 16
__func__.13155:
	.string	"HEVC_CheckListX"
	.type	__func__.13322, %object
	.size	__func__.13322, 16
__func__.13322:
	.string	"HEVC_RepairList"
	.type	__func__.13409, %object
	.size	__func__.13409, 16
__func__.13409:
	.string	"HEVC_ArrangeMem"
	.type	__func__.13482, %object
	.size	__func__.13482, 20
__func__.13482:
	.string	"HEVC_RemoveApcStore"
	.zero	4
	.type	__func__.13760, %object
	.size	__func__.13760, 21
__func__.13760:
	.string	"HEVC_CheckFrameStore"
	.zero	3
	.type	__func__.13828, %object
	.size	__func__.13828, 19
__func__.13828:
	.string	"HEVC_GetSLHDR1Info"
	.zero	5
	.type	__func__.13955, %object
	.size	__func__.13955, 14
__func__.13955:
	.string	"HEVC_IsNewPic"
	.zero	2
	.type	g_Quant8InterDefault, %object
	.size	g_Quant8InterDefault, 64
g_Quant8InterDefault:
	.word	269488144
	.word	403968529
	.word	286265360
	.word	421008402
	.word	303108112
	.word	471406612
	.word	336728336
	.word	555489560
	.word	403968529
	.word	690035737
	.word	421008402
	.word	908665116
	.word	471406612
	.word	1194731809
	.word	555489560
	.word	1531393577
	.type	g_QuantTsDefault, %object
	.size	g_QuantTsDefault, 16
g_QuantTsDefault:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.align	3
.LANCHOR3 = . + 0
	.type	__func__.14271, %object
	.size	__func__.14271, 16
__func__.14271:
	.string	"HEVC_ReleaseNAL"
	.type	__func__.13441, %object
	.size	__func__.13441, 20
__func__.13441:
	.string	"HEVC_InitDecBuffers"
	.zero	4
	.type	__func__.11887, %object
	.size	__func__.11887, 23
__func__.11887:
	.string	"HEVC_ParseVPSExtension"
	.zero	1
	.type	__func__.12436, %object
	.size	__func__.12436, 12
__func__.12436:
	.string	"HEVC_DecVPS"
	.zero	4
	.type	__func__.14013, %object
	.size	__func__.14013, 24
__func__.14013:
	.string	"HEVC_DecScalingListData"
	.type	g_CropUnitX, %object
	.size	g_CropUnitX, 16
g_CropUnitX:
	.word	1
	.word	2
	.word	2
	.word	1
	.type	g_CropUnitY, %object
	.size	g_CropUnitY, 16
g_CropUnitY:
	.word	1
	.word	2
	.word	1
	.word	1
	.type	__func__.12502, %object
	.size	__func__.12502, 12
__func__.12502:
	.string	"HEVC_DecSPS"
	.zero	4
	.type	__func__.12540, %object
	.size	__func__.12540, 12
__func__.12540:
	.string	"HEVC_DecPPS"
	.zero	4
	.type	__func__.12978, %object
	.size	__func__.12978, 27
__func__.12978:
	.string	"HEVC_DecSliceSegmentHeader"
	.zero	5
	.type	__func__.13420, %object
	.size	__func__.13420, 13
__func__.13420:
	.string	"HEVC_InitDPB"
	.zero	3
	.type	__func__.12096, %object
	.size	__func__.12096, 20
__func__.12096:
	.string	"HEVC_ArrangeShvcMem"
	.zero	4
	.type	__func__.13588, %object
	.size	__func__.13588, 19
__func__.13588:
	.string	"HEVC_OutputCurrPic"
	.zero	5
	.type	__func__.13593, %object
	.size	__func__.13593, 23
__func__.13593:
	.string	"HEVC_FirstFrameFastOut"
	.zero	1
	.type	__func__.13752, %object
	.size	__func__.13752, 19
__func__.13752:
	.string	"HEVC_OutputFrmToVO"
	.zero	5
	.type	__func__.13708, %object
	.size	__func__.13708, 22
__func__.13708:
	.string	"HEVC_OutputFrmFromDPB"
	.zero	2
	.type	__func__.12879, %object
	.size	__func__.12879, 30
__func__.12879:
	.string	"HEVC_OutputUnRefPicWithMinPoc"
	.zero	2
	.type	__func__.13727, %object
	.size	__func__.13727, 27
__func__.13727:
	.string	"HEVC_FlushOutputFrmFromDPB"
	.zero	5
	.type	__func__.14334, %object
	.size	__func__.14334, 14
__func__.14334:
	.string	"HEVC_ClearDPB"
	.zero	2
	.type	__func__.12884, %object
	.size	__func__.12884, 23
__func__.12884:
	.string	"HEVC_RecoverDPBProcess"
	.zero	1
	.type	__func__.13688, %object
	.size	__func__.13688, 20
__func__.13688:
	.string	"HEVC_InsertFrmInDPB"
	.zero	4
	.type	__func__.13598, %object
	.size	__func__.13598, 22
__func__.13598:
	.string	"HEVC_SimpleDPBProcess"
	.zero	2
	.type	__func__.13603, %object
	.size	__func__.13603, 21
__func__.13603:
	.string	"HEVC_DecOrderProcess"
	.zero	3
	.type	__func__.13617, %object
	.size	__func__.13617, 22
__func__.13617:
	.string	"HEVC_DispOrderProcess"
	.zero	2
	.type	__func__.13631, %object
	.size	__func__.13631, 19
__func__.13631:
	.string	"HEVC_StorePicInDPB"
	.zero	5
	.type	__func__.13241, %object
	.size	__func__.13241, 12
__func__.13241:
	.string	"HEVC_DecVDM"
	.zero	4
	.type	__func__.12122, %object
	.size	__func__.12122, 18
__func__.12122:
	.string	"HEVC_VES_Splitter"
	.zero	6
	.type	__func__.12915, %object
	.size	__func__.12915, 14
__func__.12915:
	.string	"HEVC_DecSlice"
	.zero	2
	.type	__func__.14416, %object
	.size	__func__.14416, 20
__func__.14416:
	.string	"HEVC_HaveSliceToDec"
	.zero	4
	.type	__func__.14468, %object
	.size	__func__.14468, 13
__func__.14468:
	.string	"HEVCDEC_Init"
	.zero	3
	.type	__func__.14482, %object
	.size	__func__.14482, 23
__func__.14482:
	.string	"HEVCDEC_GetImageBuffer"
	.zero	1
	.type	__func__.14497, %object
	.size	__func__.14497, 21
__func__.14497:
	.string	"HEVCDEC_DecodePacket"
	.zero	3
	.type	g_HevcNalTypeEOP, %object
	.size	g_HevcNalTypeEOP, 21
g_HevcNalTypeEOP:
	.byte	0
	.byte	0
	.byte	1
	.byte	96
	.byte	0
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.zero	3
	.type	__func__.14546, %object
	.size	__func__.14546, 21
__func__.14546:
	.string	"HEVCDEC_GetRemainImg"
	.data
	.align	3
.LANCHOR2 = . + 0
	.type	g_Quant8IntraDefault, %object
	.size	g_Quant8IntraDefault, 64
g_Quant8IntraDefault:
	.word	269488144
	.word	404034065
	.word	269488144
	.word	420877073
	.word	303108112
	.word	488183316
	.word	353505296
	.word	606018328
	.word	403968273
	.word	791225118
	.word	454431506
	.word	1094069283
	.word	521737749
	.word	1480996393
	.word	605886744
	.word	1935163695
	.type	g_QuantTSDefault4x4, %object
	.size	g_QuantTSDefault4x4, 16
g_QuantTSDefault4x4:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.type	g_QuantInterDefault8x8, %object
	.size	g_QuantInterDefault8x8, 64
g_QuantInterDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	91
	.type	g_QuantIntraDefault8x8, %object
	.size	g_QuantIntraDefault8x8, 64
g_QuantIntraDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	21
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	19
	.byte	22
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	22
	.byte	25
	.byte	29
	.byte	16
	.byte	16
	.byte	18
	.byte	21
	.byte	24
	.byte	27
	.byte	31
	.byte	36
	.byte	17
	.byte	17
	.byte	20
	.byte	24
	.byte	30
	.byte	35
	.byte	41
	.byte	47
	.byte	18
	.byte	19
	.byte	22
	.byte	27
	.byte	35
	.byte	44
	.byte	54
	.byte	65
	.byte	21
	.byte	22
	.byte	25
	.byte	31
	.byte	41
	.byte	54
	.byte	70
	.byte	88
	.byte	24
	.byte	25
	.byte	29
	.byte	36
	.byte	47
	.byte	65
	.byte	88
	.byte	115
	.type	g_RpuStartCode, %object
	.size	g_RpuStartCode, 5
g_RpuStartCode:
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	25
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC2:
	ASCII(.string	"../../core/syntax/hevc.c" )
	.zero	7
.LC4:
	ASCII(.string	"NULL pointer: %s, L%d\n" )
	.zero	1
.LC6:
	ASCII(.string	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%d, logic_fs=%p, dec_fs=%p)\n" )
	.zero	1
.LC9:
	ASCII(.string	"%s: pImg is NULL!\n" )
	.zero	5
.LC11:
	ASCII(.string	"View %d image queue is full, discard head image %d.\n" )
	.zero	3
.LC13:
	ASCII(.string	"%s: view0 frame poc(%d) > view1 frame poc(%d)\n" )
	.zero	1
.LC15:
	ASCII(.string	"%s: view1 frame poc(%d) > view0 frame poc(%d)\n" )
	.zero	1
.LC17:
	ASCII(.string	"%s: Image(view=0, poc=%d) output failed!\n" )
	.zero	6
.LC19:
	ASCII(.string	"%s: Image(view=1, poc=%d) output failed!\n" )
	.zero	6
.LC21:
	ASCII(.string	"%s: InsertImgToVoQueue failed!\n" )
.LC25:
	ASCII(.string	"%s pVPSExt = NULL\n" )
	.zero	5
.LC28:
	ASCII(.string	"%s pPPSExt = NULL\n" )
	.zero	5
.LC31:
	ASCII(.string	"%s pSlcExt = NULL\n" )
	.zero	5
.LC34:
	ASCII(.string	"line:%d ChanID(%d), pic_parameter_set_id(%d) out of range(0,%d).\n" )
	.zero	6
.LC36:
	ASCII(.string	"line:%d ChanID(%d), seq_parameter_set_id(%d) out of range[0,%d].\n" )
	.zero	6
.LC43:
	ASCII(.string	"dar=%d\n" )
.LC46:
	ASCII(.string	"--------------- PrintNaluArraySlot START ---------------\n" )
	.zero	6
.LC48:
	ASCII(.string	"\n" )
	.zero	6
.LC50:
	ASCII(.string	"--------------- PrintNaluArraySlot END ---------------\n" )
.LC52:
	ASCII(.string	"NalArray[%d]=%p,is_valid=%d   " )
	.zero	1
.LC54:
	ASCII(.string	"--------------- PrintCurrSlicelistX START ---------------\n" )
	.zero	5
.LC56:
	ASCII(.string	"List0, size: %d\n" )
	.zero	7
.LC58:
	ASCII(.string	"List1, size: %d\n" )
	.zero	7
.LC60:
	ASCII(.string	"pListX[0][%d]:%p " )
	.zero	6
.LC62:
	ASCII(.string	"pFrameStore:%p " )
.LC64:
	ASCII(.string	"pLogicFs:%p " )
	.zero	3
.LC67:
	ASCII(.string	"--------------- PrintCurrSlicelistX END ---------------\n" )
	.zero	7
.LC69:
	ASCII(.string	"pListX[1][%d]: %p" )
	.zero	6
.LC73:
	ASCII(.string	"--------------- PrintFrameStoreState START ---------------\n" )
	.zero	4
.LC75:
	ASCII(.string	"--------------- PrintFrameStoreState END ---------------\n" )
	.zero	6
.LC77:
	ASCII(.string	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displayed=%d " )
	.zero	5
.LC79:
	ASCII(.string	"p_usrdat[%d]=%p " )
	.zero	7
.LC82:
	ASCII(.string	"--------------- PrintAPCState START ---------------\n" )
	.zero	3
.LC84:
	ASCII(.string	"Layer %d: APC.used_size:%d, APC.size:%d\n" )
	.zero	7
.LC86:
	ASCII(.string	"%d: is_used=%d, idc=%d, poc=%d\n" )
.LC88:
	ASCII(.string	"--------------- PrintAPCState END ---------------\n" )
	.zero	5
.LC90:
	ASCII(.string	"--------------- PrintDPBState START ---------------\n" )
	.zero	3
.LC92:
	ASCII(.string	"DPB: size:%d, used_size:%d, negative:%d, positive:%d, longterm:%d\n" )
	.zero	5
.LC95:
	ASCII(.string	"fs[%d]:%p view %d non_existing:%d state:%d is_ref:%d displayed:%d poc:%d long_term:%d LogicFs:%p, fsp_ref:%d fsp_disp:%d logic_id:%d img_id:%d\n" )
.LC97:
	ASCII(.string	"--------------- PrintDPBState END ---------------\n" )
	.zero	5
.LC99:
	ASCII(.string	"fs[%d]\t" )
.LC101:
	ASCII(.string	"LogicFs:%p\t" )
	.zero	4
.LC103:
	ASCII(.string	"LogicTick:%d\t" )
	.zero	2
.LC105:
	ASCII(.string	"IsRef:%d\t" )
	.zero	6
.LC107:
	ASCII(.string	"DispState:%d\t" )
	.zero	2
.LC109:
	ASCII(.string	"LogicFs:Null\t" )
	.zero	2
.LC111:
	ASCII(.string	"DecFs:%p\t" )
	.zero	6
.LC113:
	ASCII(.string	"DecTick:%d\t" )
	.zero	4
.LC115:
	ASCII(.string	"DecFs:Null\t" )
	.zero	4
.LC117:
	ASCII(.string	"DispFs:%p\t" )
	.zero	5
.LC119:
	ASCII(.string	"DispTick:%d\t" )
	.zero	3
.LC121:
	ASCII(.string	"DispFs:Null\t" )
	.zero	3
.LC124:
	ASCII(.string	"%s num_tile_columns(%d) out of range(0, %d].\n" )
	.zero	2
.LC126:
	ASCII(.string	"%s num_tile_rows(%d) out of range(0, %d].\n" )
	.zero	5
.LC129:
	ASCII(.string	"%s 0 idx(%d) out of range(0, 512).\n" )
	.zero	4
.LC131:
	ASCII(.string	"%s 1 idx(%d) out of range(0, 512).\n" )
	.zero	4
.LC134:
	ASCII(.string	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\n" )
	.zero	6
.LC136:
	ASCII(.string	"pListX[0][%d] = NULL, listXsize[0] = %d\n" )
	.zero	7
.LC138:
	ASCII(.string	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %d\n" )
	.zero	2
.LC140:
	ASCII(.string	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) invalid\n" )
	.zero	1
.LC142:
	ASCII(.string	"pListX[1][%d] = NULL, listXsize[1] = %d\n" )
	.zero	7
.LC144:
	ASCII(.string	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %d\n" )
	.zero	2
.LC146:
	ASCII(.string	"pListX[i][%d] pstLogicFs(%p) invalid\n" )
	.zero	2
.LC149:
	ASCII(.string	"%s can't find such pic.\n" )
	.zero	7
.LC151:
	ASCII(.string	"%s DPB.used_size(%d) >= 17.\n" )
	.zero	3
.LC153:
	ASCII(.string	"%s find pos=%d, poc=%d.\n" )
	.zero	7
.LC156:
	ASCII(.string	"%s DPB.size(%d) already reached max(%d).\n" )
	.zero	6
.LC158:
	ASCII(.string	"%s increase DPB size to %d\n" )
	.zero	4
.LC160:
	ASCII(.string	"%s no enough fs(total_fs_num=%d) to increase DPB size.\n" )
.LC162:
	ASCII(.string	"TileWidthInCtb is 0\n" )
	.zero	3
.LC166:
	ASCII(.string	"%s: g_pGlbVar is NULL!\n" )
.LC169:
	ASCII(.string	"image_id=%d, pmv_idc=%d\n" )
	.zero	7
.LC171:
	ASCII(.string	"pic msg burst0:\n" )
	.zero	7
.LC175:
	ASCII(.string	"%s call HEVC_CalcTileInfo failed.\n" )
	.zero	5
.LC177:
	ASCII(.string	"logic frame id(=%d): get LogicFs error!\n" )
	.zero	7
.LC179:
	ASCII(.string	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p\n" )
	.zero	3
.LC182:
	ASCII(.string	"%s ERROR: bHaveIndependentSlice = 0\n\n" )
	.zero	2
.LC184:
	ASCII(.string	"ListX ERROR: list0size >= %d\n" )
	.zero	2
.LC186:
	ASCII(.string	"ListX ERROR: list1size >= %d\n" )
	.zero	2
.LC188:
	ASCII(.string	"pListX[0][%d] = NULL\n" )
	.zero	2
.LC190:
	ASCII(.string	"pListX[0][%d]->frame_store = NULL\n" )
	.zero	5
.LC192:
	ASCII(.string	"pListX[1][%d] = NULL\n" )
	.zero	2
.LC194:
	ASCII(.string	"pListX[1][%d]->frame_store = NULL\n" )
	.zero	5
.LC196:
	ASCII(.string	"NumSlicePara(%d) >= MaxSliceNum(%d)\n" )
	.zero	3
.LC199:
	ASCII(.string	"width is larger than 3! (%d, %d)\n" )
	.zero	6
.LC201:
	ASCII(.string	"height is larger than 3! (%d, %d)\n" )
	.zero	5
.LC203:
	ASCII(.string	"line:%d pic_parameter_set_id(%d) out of range(0,%d).\n" )
	.zero	2
.LC205:
	ASCII(.string	"line:%d seq_parameter_set_id(%d) out of range[0,%d].\n" )
	.zero	2
.LC207:
	ASCII(.string	"line:%d, i(%d) > Max(%d) num_of_pics %d\n" )
	.zero	7
.LC209:
	ASCII(.string	"line:%d, i(%d) > Max(%d)(neg%d + pos%d)\n" )
	.zero	7
.LC218:
	ASCII(.string	"%s unkown slice type(%d).\n" )
	.zero	5
.LC220:
	ASCII(.string	"%s pListX[%d] no available pic to repair.\n" )
	.zero	5
.LC222:
	ASCII(.string	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\n" )
	.zero	4
.LC226:
	ASCII(.string	"HEVC_InitListX error.\n" )
	.zero	1
.LC228:
	ASCII(.string	"HEVC_RepairList error.\n" )
.LC232:
	ASCII(.string	"%s image size abnormal(%dx%d)\n" )
	.zero	1
.LC234:
	ASCII(.string	"%s HEVC FSP_ConfigInstance failed!\n" )
	.zero	4
.LC237:
	ASCII(.string	"%s fs[%d]->view_id = %d invalid.\n" )
	.zero	6
.LC241:
	ASCII(.string	"framestore %d allocate apc %d\n" )
	.zero	1
.LC244:
	ASCII(.string	"Cant find free apc slot.\n" )
	.zero	6
.LC247:
	ASCII(.string	"%s frame logic_fs_id=%d, state=%d\n" )
	.zero	5
.LC249:
	ASCII(.string	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null, logic_fs_id = %d\n" )
	.zero	2
.LC251:
	ASCII(.string	"%s frame poc=%d, is already output\n" )
	.zero	4
.LC253:
	ASCII(.string	"%s frame(%p) invalid, state:%d, non_existing:%d\n" )
	.zero	7
.LC255:
	ASCII(.string	"exg_pts: %lld <-> %lld\n" )
.LC258:
	ASCII(.string	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STATE_NOT_USED\n" )
.LC260:
	ASCII(.string	"%-5d   specVersion\n" )
	.zero	4
.LC262:
	ASCII(.string	"%-5d   payloadMode\n" )
	.zero	4
.LC264:
	ASCII(.string	"%-5d   hdrPicColourSpace\n" )
	.zero	6
.LC266:
	ASCII(.string	"%-5d   hdrMasterDisplayColourSpace\n" )
	.zero	4
.LC268:
	ASCII(.string	"%-5d   hdrMasterDisplayMaxLuminance\n" )
	.zero	3
.LC270:
	ASCII(.string	"%-5d   hdrMasterDisplayMinLuminance\n" )
	.zero	3
.LC272:
	ASCII(.string	"%-5d   sdrPicColourSpace\n" )
	.zero	6
.LC274:
	ASCII(.string	"%-5d   sdrMasterDisplayColourSpace\n" )
	.zero	4
.LC276:
	ASCII(.string	"%-5d   tmInputSignalBlackLevelOffset\n" )
	.zero	2
.LC278:
	ASCII(.string	"%-5d   tmInputSignalWhiteLevelOffset\n" )
	.zero	2
.LC280:
	ASCII(.string	"%-5d   shadowGain\n" )
	.zero	5
.LC282:
	ASCII(.string	"%-5d   highlightGain\n" )
	.zero	2
.LC284:
	ASCII(.string	"%-5d   midToneWidthAdjFactor\n" )
	.zero	2
.LC286:
	ASCII(.string	"%-5d   tmOutputFineTuningNumVal\n" )
	.zero	7
.LC288:
	ASCII(.string	"%-5d   saturationGainNumVal\n" )
	.zero	3
.LC290:
	ASCII(.string	"%-5d   tmOutputFineTuningX[%d]\n" )
.LC292:
	ASCII(.string	"%-5d   tmOutputFineTuningY[%d]\n" )
.LC294:
	ASCII(.string	"%-5d   saturationGainX[%d]\n" )
	.zero	4
.LC296:
	ASCII(.string	"%-5d   saturationGainY[%d]\n" )
	.zero	4
.LC298:
	ASCII(.string	"%-5d   luminanceMappingNumVal\n" )
	.zero	1
.LC300:
	ASCII(.string	"%-5d   colourCorrectionNumVal\n" )
	.zero	1
.LC302:
	ASCII(.string	"%-5d   luminanceMappingX[%d]\n" )
	.zero	2
.LC304:
	ASCII(.string	"%-5d   luminanceMappingY[%d]\n" )
	.zero	2
.LC306:
	ASCII(.string	"%-5d   chromaToLumaInjectionMuA\n" )
	.zero	7
.LC308:
	ASCII(.string	"%-5d   chromaToLumaInjectionMuB\n" )
	.zero	7
.LC310:
	ASCII(.string	"%-5d   colourCorrectionX[%d]\n" )
	.zero	2
.LC312:
	ASCII(.string	"%-5d   colourCorrectionY[%d]\n" )
	.zero	2
.LC314:
	ASCII(.string	"======SL_HDR1_METADATA= %d=======\n" )
	.zero	5
.LC317:
	ASCII(.string	"%s, [%d %d %d %d %d]\n" )
	.zero	2
.LC319:
	ASCII(.string	"%s HDR_Metadata_phy_addr is invalid!!\n" )
	.zero	1
.LC322:
	ASCII(.string	"FS_ALLOC_ERR, ClearAll\n" )
.LC325:
	ASCII(.string	"Can not new logic fs! ClearAll\n" )
.LC327:
	ASCII(.string	"FSP_GetFspType -1\n" )
	.zero	5
.LC329:
	ASCII(.string	"FSP_GetLogicFs return NULL\n" )
	.zero	4
.LC331:
	ASCII(.string	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), error resilence.\n" )
	.zero	6
.LC333:
	ASCII(.string	"nal_segment = %d is not expected value\n" )
.LC335:
	ASCII(.string	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of range\n" )
	.zero	5
.LC337:
	ASCII(.string	"pps with this pic_parameter_set_id = %d havn't be decoded\n" )
	.zero	5
.LC339:
	ASCII(.string	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of range\n" )
	.zero	5
.LC341:
	ASCII(.string	"sps with this seq_parameter_set_id = %d havn't be decoded\n" )
	.zero	5
.LC343:
	ASCII(.string	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of range\n" )
	.zero	7
.LC345:
	ASCII(.string	"vps with this video_parameter_set_id = %d havn't be decoded\n" )
	.zero	3
.LC348:
	ASCII(.string	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, nal_unit_type = %d, should skip this frame\n" )
	.zero	2
.LC350:
	ASCII(.string	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d, nal_unit_type = %d, should skip this frame\n" )
.LC352:
	ASCII(.string	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocCRA = %d, nal_unit_type = %d, should skip this frame\n" )
.LC354:
	ASCII(.string	"HEVC_ReadByteAlignment: code should not be zero.\n" )
	.zero	6
.LC356:
	ASCII(.string	"HEVC_ReadByteAlignment: code:%d\n" )
	.zero	7
.LC358:
	ASCII(.string	"reserved_zero_2bits not equal 0.\n" )
	.zero	6
.LC367:
	ASCII(.string	"HEVC_GetScalingListDefaultAddress NULL.\n" )
	.zero	7
.LC369:
	ASCII(.string	"Error, BsLen: 0x%x, TotalPos: 0x%x\n" )
	.zero	4
.LC371:
	ASCII(.string	"Panic: All zero data sequence in RBSP \n" )
.LC373:
	ASCII(.string	"nal_trail_zero_bit_num err\n" )
	.zero	4
.LC378:
	ASCII(.string	"%s release streambuff=%p, bitstream_length=%d\n" )
	.zero	1
.LC382:
	ASCII(.string	"%s DPB size exceed %d, force to %d\n" )
	.zero	4
.LC385:
	ASCII(.string	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\n" )
	.zero	6
.LC387:
	ASCII(.string	"END of the bit buffer, copy the first packet!\n" )
	.zero	1
.LC390:
	ASCII(.string	"tone_map_id" )
	.zero	4
.LC392:
	ASCII(.string	"Unsupport: target_bit_depth(%d) > 8\n" )
	.zero	3
.LC395:
	ASCII(.string	"pTon->num_pivots > 256\n" )
.LC397:
	ASCII(.string	"frame_packing_arrangement_id" )
	.zero	3
.LC399:
	ASCII(.string	"frame_packing_arrangement_type(%d) out of range\n" )
	.zero	7
.LC401:
	ASCII(.string	"decoding_unit_idx" )
	.zero	6
.LC403:
	ASCII(.string	"num_sps_ids_minus1" )
	.zero	5
.LC405:
	ASCII(.string	"pAct->num_sps_ids_minus1 > 15\n" )
	.zero	1
.LC407:
	ASCII(.string	"active_seq_parameter_set_id" )
	.zero	4
.LC409:
	ASCII(.string	"bp_seq_parameter_set_id" )
.LC411:
	ASCII(.string	"Wrong bp_seq_parameter_set_id = %d, should be 0 to 15!\n" )
.LC414:
	ASCII(.string	"num_decoding_units_minus1" )
	.zero	6
.LC416:
	ASCII(.string	"pPic->num_decoding_units_minus1 > 255\n" )
	.zero	1
.LC418:
	ASCII(.string	"num_nalus_in_du_minus1" )
	.zero	1
.LC420:
	ASCII(.string	"cv_rec_id" )
	.zero	6
.LC422:
	ASCII(.string	"HEVC_Sei_User_Data_Registered_Itu_T_T35 payloadSize < 4!!\n" )
	.zero	5
.LC424:
	ASCII(.string	"delta_idx_minus1" )
	.zero	7
.LC426:
	ASCII(.string	"delta_idx(%d) > idx(%d).\n" )
	.zero	6
.LC428:
	ASCII(.string	"rIdx(%d) > (idx-1)(%d) or < 0).\n" )
	.zero	7
.LC430:
	ASCII(.string	"abs_delta_rps_minus1" )
	.zero	3
.LC432:
	ASCII(.string	"pTempRPset->num_of_pics(%d) out of range(0,15).\n" )
	.zero	7
.LC434:
	ASCII(.string	"num_of_pics out of range(0,15).\n" )
	.zero	7
.LC436:
	ASCII(.string	"num_negative_pics" )
	.zero	6
.LC438:
	ASCII(.string	"pTempRPset->num_negative_pics(%d) out of range(0,15).\n" )
	.zero	1
.LC440:
	ASCII(.string	"num_positive_pics" )
	.zero	6
.LC442:
	ASCII(.string	"pTempRPset->num_positive_pics(%d) out of range(0,15).\n" )
	.zero	1
.LC444:
	ASCII(.string	"pShortTermRpset->num_of_pics(%d) out of range[0,%d].\n" )
	.zero	2
.LC446:
	ASCII(.string	"delta_poc_s0_minus1" )
	.zero	4
.LC448:
	ASCII(.string	"delta_poc_s0_minus1(%d) out of range.\n" )
	.zero	1
.LC450:
	ASCII(.string	"delta_poc_s1_minus1" )
	.zero	4
.LC452:
	ASCII(.string	"elemental_duration_in_tc_minus1" )
.LC454:
	ASCII(.string	"cpb_cnt_minus1" )
	.zero	1
.LC456:
	ASCII(.string	"cpb_cnt_minus1(%d) out of range(0,31).\n" )
.LC458:
	ASCII(.string	"bit_rate_value_minus1" )
	.zero	2
.LC460:
	ASCII(.string	"cpb_size_value_minus1" )
	.zero	2
.LC462:
	ASCII(.string	"cpb_size_du_value_minus1" )
	.zero	7
.LC464:
	ASCII(.string	"bit_rate_du_value_minus1" )
	.zero	7
.LC468:
	ASCII(.string	"%s: vps_max_layers_minus1 %d out of range[0,%d].\n" )
	.zero	6
.LC470:
	ASCII(.string	"num_add_layer_sets" )
	.zero	5
.LC472:
	ASCII(.string	"%s %d: num_add_layer_sets %d >= HEVC_MAX_VPS_OP_SETS_PLUS1 %d\n" )
	.zero	1
.LC474:
	ASCII(.string	"vps_num_profile_tier_level_minus1" )
	.zero	6
.LC476:
	ASCII(.string	"num_add_olss" )
	.zero	3
.LC478:
	ASCII(.string	"%s %d: num_output_layer_sets %d >= HEVC_MAX_VPS_OP_SETS_PLUS1 %d, num_add_olss %d, num_layer_sets %d\n" )
	.zero	2
.LC480:
	ASCII(.string	"vps_num_rep_formats_minus1" )
	.zero	5
.LC482:
	ASCII(.string	"vps_num_rep_formats_minus1 > 255.\n" )
	.zero	5
.LC484:
	ASCII(.string	"conf_win_vps_left_offset" )
	.zero	7
.LC486:
	ASCII(.string	"conf_win_vps_right_offset" )
	.zero	6
.LC488:
	ASCII(.string	"conf_win_vps_top_offset" )
.LC490:
	ASCII(.string	"conf_win_vps_bottom_offset" )
	.zero	5
.LC492:
	ASCII(.string	"bit_depth_vps_luma_minus8(%d) or bit_depth_vps_chroma_minus8(%d) out of range [0,8]\n" )
	.zero	3
.LC494:
	ASCII(.string	"direct_dep_type_len_minus2" )
	.zero	5
.LC496:
	ASCII(.string	"max_vps_num_reorder_pics" )
	.zero	7
.LC498:
	ASCII(.string	"max_vps_latency_increase_plus1" )
	.zero	1
.LC500:
	ASCII(.string	"max_vps_dec_pic_buffering_minus1" )
	.zero	7
.LC502:
	ASCII(.string	"vps_non_vui_extension_length" )
	.zero	3
.LC504:
	ASCII(.string	"min_spatial_segment_offset_plus1" )
	.zero	7
.LC506:
	ASCII(.string	"min_horizontal_ctu_offset_plus1" )
.LC508:
	ASCII(.string	"vps_num_add_hrd_params" )
	.zero	1
.LC510:
	ASCII(.string	"vps_num_hrd_params %d out of range [0,%d]\n" )
	.zero	5
.LC512:
	ASCII(.string	"num_sub_layer_hrd_minus1" )
	.zero	7
.LC514:
	ASCII(.string	"hrd %d num_sub_layer_hrd_minus1 %d out of range [0,%d]\n" )
.LC516:
	ASCII(.string	"num_signalled_partitioning_schemes" )
	.zero	5
.LC518:
	ASCII(.string	"OPL %d num_signalled_partitioning_schemes %d out of range [0,%d]\n" )
	.zero	6
.LC520:
	ASCII(.string	"num_partitions_in_scheme_minus1" )
.LC522:
	ASCII(.string	"num_bsp_schedules_minus1" )
	.zero	7
.LC524:
	ASCII(.string	"OPL %d Partition %d Tid %dnum_bsp_schedules_minus1 %d out of range [0,31]\n" )
	.zero	5
.LC526:
	ASCII(.string	"bsp_sched_idx" )
	.zero	2
.LC528:
	ASCII(.string	"HEVCC_ParseBspPartitonParameters failed.\n" )
	.zero	6
.LC530:
	ASCII(.string	"vps_base_layer_available_flag(%d) not equal 0x1.\n" )
	.zero	6
.LC532:
	ASCII(.string	"vps_max_layers_minus1 %d out of range[0,63].\n" )
	.zero	2
.LC534:
	ASCII(.string	"vps_max_sub_layers_minus1=%d\n" )
	.zero	2
.LC536:
	ASCII(.string	"vps_reserved_0xffff_16bits not equal 0xffff.\n" )
	.zero	2
.LC538:
	ASCII(.string	"VPS HEVC_DecPTL error.\n" )
.LC540:
	ASCII(.string	"vps_max_dec_pic_buffering_minus1[i]" )
	.zero	4
.LC542:
	ASCII(.string	"vps_num_reorder_pics[i]" )
.LC544:
	ASCII(.string	"vps_max_latency_increase_plus1[i]" )
	.zero	6
.LC546:
	ASCII(.string	"vps_max_layer_id out of range[0,%d].\n" )
	.zero	2
.LC548:
	ASCII(.string	"This is MV_HEVC!\n" )
	.zero	6
.LC550:
	ASCII(.string	"vps_num_layer_sets_minus1" )
	.zero	6
.LC552:
	ASCII(.string	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\n" )
	.zero	5
.LC555:
	ASCII(.string	"vps_num_ticks_poc_diff_one_minus1" )
	.zero	6
.LC557:
	ASCII(.string	"vps_num_hrd_parameters" )
	.zero	1
.LC559:
	ASCII(.string	"vps_num_hrd_parameters(%d) out of range[0,%d].\n" )
.LC561:
	ASCII(.string	"hrd_layer_set_idx" )
	.zero	6
.LC563:
	ASCII(.string	"VPS HEVC_DecHrdParam error.\n" )
	.zero	3
.LC565:
	ASCII(.string	"HEVC VPSExtension error.\n" )
	.zero	6
.LC570:
	ASCII(.string	"pVPS->vps_video_parameter_set_id out of range(0,15).\n" )
	.zero	2
.LC573:
	ASCII(.string	"VPS[%d] decode error0.\n" )
.LC575:
	ASCII(.string	"VPS[%d] decode error1.\n" )
.LC577:
	ASCII(.string	"chroma_sample_loc_type_top_field" )
	.zero	7
.LC579:
	ASCII(.string	"chroma_sample_loc_type_bottom_field" )
	.zero	4
.LC581:
	ASCII(.string	"def_disp_win_left_offset" )
	.zero	7
.LC583:
	ASCII(.string	"VUI pSps->chroma_format_idc out of range(0,3).\n" )
.LC585:
	ASCII(.string	"def_disp_win_right_offset" )
	.zero	6
.LC587:
	ASCII(.string	"def_disp_win_top_offset" )
.LC589:
	ASCII(.string	"def_disp_win_bottom_offset" )
	.zero	5
.LC592:
	ASCII(.string	"vui_num_ticks_poc_diff_one_minus1" )
	.zero	6
.LC594:
	ASCII(.string	"VUI HEVC_DecHrdParam error.\n" )
	.zero	3
.LC596:
	ASCII(.string	"min_spatial_segmentation_idc" )
	.zero	3
.LC598:
	ASCII(.string	"VUI min_spatial_segmentation_idc out of range(0,4095).\n" )
.LC600:
	ASCII(.string	"max_bytes_per_pic_denom" )
.LC602:
	ASCII(.string	"max_bits_per_min_cu_denom" )
	.zero	6
.LC604:
	ASCII(.string	"log2_max_mv_length_horizontal" )
	.zero	2
.LC606:
	ASCII(.string	"log2_max_mv_length_vertical" )
	.zero	4
.LC608:
	ASCII(.string	"sop_seq_parameter_set_id" )
	.zero	7
.LC610:
	ASCII(.string	"num_entries_in_sop_minus1" )
	.zero	6
.LC612:
	ASCII(.string	"num_entries_in_sop_minus1 out of range(0,1024)\n" )
.LC614:
	ASCII(.string	"sop_short_term_rps_idx" )
	.zero	1
.LC616:
	ASCII(.string	"sop_poc_delta" )
	.zero	2
.LC618:
	ASCII(.string	"recovery_poc_cnt" )
	.zero	7
.LC620:
	ASCII(.string	"colour_remap_id" )
.LC622:
	ASCII(.string	"colour_remap_coeffs" )
	.zero	4
.LC624:
	ASCII(.string	"ERROR: post_lut_num_val_minus1 %d out of range[0, 32]\n" )
	.zero	1
.LC627:
	ASCII(.string	"reserved_payload_extension_data" )
.LC629:
	ASCII(.string	"line:%d Cosume TotalPos(%d > %d)!!!\n" )
	.zero	3
.LC631:
	ASCII(.string	"HEVC_SeiMessage HEVC_Sei_Payload error.\n" )
	.zero	7
.LC633:
	ASCII(.string	"SEI pSEISPS = NULL.\n" )
	.zero	3
.LC635:
	ASCII(.string	"SEI HEVC_SeiMessage error.\n" )
	.zero	4
.LC637:
	ASCII(.string	"SEI BsIsByteAligned error.\n" )
	.zero	4
.LC639:
	ASCII(.string	"SEI rbsp_trailing_bits(%d) not equal 0x80.\n" )
	.zero	4
.LC641:
	ASCII(.string	"nesting_num_ops_minus1" )
	.zero	1
.LC643:
	ASCII(.string	"nesting_num_ops_minus1 out of range(0,%d)\n" )
	.zero	5
.LC645:
	ASCII(.string	"nesting_op_idx" )
	.zero	1
.LC647:
	ASCII(.string	"nesting_num_layers_minus1" )
	.zero	6
.LC649:
	ASCII(.string	"nesting_num_layers_minus1 out of range(0,63)\n" )
	.zero	2
.LC656:
	ASCII(.string	"scaling_list_pred_matrix_id_delta" )
	.zero	6
.LC658:
	ASCII(.string	"scaling_list_pred_matrix_id_delta out of range(0,matrixId).\n" )
	.zero	3
.LC660:
	ASCII(.string	"HEVC_DecScalingListData pMatrixAddress NULL.\n" )
	.zero	2
.LC662:
	ASCII(.string	"scaling_list_dc_coef_minus8" )
	.zero	4
.LC664:
	ASCII(.string	"scaling_list_dc_coef_minus8 out of range(-7,247).\n" )
	.zero	5
.LC666:
	ASCII(.string	"scaling_list_delta_coef" )
.LC668:
	ASCII(.string	"scaling_list_dc_coef_minus8 out of range(-128,127).\n" )
	.zero	3
.LC670:
	ASCII(.string	"sps_rep_format_idx %d > HEVC_MAX_NUM_LAYERS %d\n" )
.LC672:
	ASCII(.string	"HEVC_DeriveSPSRepFormat failed.\n" )
	.zero	7
.LC674:
	ASCII(.string	"pSPS->chroma_format_idc out of range(0,3).\n" )
	.zero	4
.LC676:
	ASCII(.string	"pSPS->chroma_format_idc not equal(%d) 1.\n" )
	.zero	6
.LC678:
	ASCII(.string	"pic_width_in_luma_samples" )
	.zero	6
.LC680:
	ASCII(.string	"pic_width_in_luma_samples out of range(0,8192).\n" )
	.zero	7
.LC683:
	ASCII(.string	"pic_height_in_luma_samples" )
	.zero	5
.LC685:
	ASCII(.string	"pic_height_in_luma_samples out of range(0,4096).\n" )
	.zero	6
.LC687:
	ASCII(.string	"ERROR Unkown level: %d\n" )
.LC689:
	ASCII(.string	"conf_win_left_offset" )
	.zero	3
.LC692:
	ASCII(.string	"conf_win_right_offset" )
	.zero	2
.LC694:
	ASCII(.string	"conf_win_left_offset+conf_win_right_offset out of range.\n" )
	.zero	6
.LC696:
	ASCII(.string	"conf_win_top_offset" )
	.zero	4
.LC698:
	ASCII(.string	"conf_win_bottom_offset" )
	.zero	1
.LC700:
	ASCII(.string	"conf_win_top_offset+conf_win_bottom_offset out of range.\n" )
	.zero	6
.LC702:
	ASCII(.string	"bit_depth_luma_minus8" )
	.zero	2
.LC704:
	ASCII(.string	"bit_depth_luma(%d) out of range(8,10).\n" )
.LC706:
	ASCII(.string	"bit_depth_chroma_minus8" )
.LC708:
	ASCII(.string	"bit_depth_chroma(%d) out of range[8,14].\n" )
	.zero	6
.LC710:
	ASCII(.string	"log2_max_pic_order_cnt_lsb_minus4" )
	.zero	6
.LC712:
	ASCII(.string	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12].\n" )
	.zero	1
.LC714:
	ASCII(.string	"sps_max_dec_pic_buffering_minus1" )
	.zero	7
.LC716:
	ASCII(.string	"sps_num_reorder_pics" )
	.zero	3
.LC718:
	ASCII(.string	"sps_max_latency_increase_plus1" )
	.zero	1
.LC720:
	ASCII(.string	"log2_min_coding_block_size_minus3" )
	.zero	6
.LC722:
	ASCII(.string	"log2_min_luma_coding_block_size_minus3 out of range(0,3).\n" )
	.zero	5
.LC724:
	ASCII(.string	"log2_diff_max_min_coding_block_size" )
	.zero	4
.LC726:
	ASCII(.string	"log2_diff_max_min_luma_coding_block_size out of range(0,3).\n" )
	.zero	3
.LC728:
	ASCII(.string	"log2_ctb_sizeY out of range(4,6).\n" )
	.zero	5
.LC730:
	ASCII(.string	"log2_min_transform_block_size_minus2" )
	.zero	3
.LC732:
	ASCII(.string	"log2_min_transform_block_size_minus2 out of range(0,3).\n" )
	.zero	7
.LC734:
	ASCII(.string	"log2_diff_max_min_transform_block_size" )
	.zero	1
.LC736:
	ASCII(.string	"log2_diff_max_min_transform_block_size out of range(0,3).\n" )
	.zero	5
.LC738:
	ASCII(.string	"quadtree_tu_log2_min_size not less than log2_min_cb_sizeY.\n" )
	.zero	4
.LC740:
	ASCII(.string	"quadtree_tu_log2_max_size greater than Min( CtbLog2SizeY, 5 ).\n" )
.LC742:
	ASCII(.string	"max_transform_hierarchy_depth_inter" )
	.zero	4
.LC744:
	ASCII(.string	"max_transform_hierarchy_depth_inter out of range(0,CtbLog2SizeY-Log2MinTrafoSize).\n" )
	.zero	4
.LC746:
	ASCII(.string	"max_transform_hierarchy_depth_intra" )
	.zero	4
.LC748:
	ASCII(.string	"max_transform_hierarchy_depth_intra out of range(0,CtbLog2SizeY-Log2MinTrafoSize).\n" )
	.zero	4
.LC750:
	ASCII(.string	"SPS HEVC_DecScalingListData error.\n" )
	.zero	4
.LC752:
	ASCII(.string	"SPS sao is off and pic height(%d) is too small.(Logic Unsupported).\n" )
	.zero	3
.LC754:
	ASCII(.string	"log2_min_pcm_luma_coding_block_size_minus3" )
	.zero	5
.LC756:
	ASCII(.string	"log2_min_pcm_coding_block_size_minus3(%d) out of range[0,2].\n" )
	.zero	2
.LC758:
	ASCII(.string	"log2_diff_max_min_pcm_luma_coding_block_size" )
	.zero	3
.LC760:
	ASCII(.string	"log2_diff_max_min_pcm_coding_block_size(%d) out of range[0,2].\n" )
.LC762:
	ASCII(.string	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5 ).\n" )
.LC764:
	ASCII(.string	"num_short_term_ref_pic_sets" )
	.zero	4
.LC766:
	ASCII(.string	"num_short_term_ref_pic_sets out of range[0,%d].\n" )
	.zero	7
.LC768:
	ASCII(.string	"SPS HEVC_DecShortTermRefPicSet error.\n" )
	.zero	1
.LC770:
	ASCII(.string	"num_long_term_ref_pic_sps" )
	.zero	6
.LC772:
	ASCII(.string	"num_long_term_ref_pic_sps out of range[0,32].\n" )
	.zero	1
.LC774:
	ASCII(.string	"SPS HEVC_DecVuiParam error.\n" )
	.zero	3
.LC776:
	ASCII(.string	"chroma_format_idc" )
	.zero	6
.LC784:
	ASCII(.string	"sps_video_parameter_set_id out of range(0,%d).\n" )
.LC786:
	ASCII(.string	"sps_max_sub_layers_minus1 out of range(0,%d).\n" )
	.zero	1
.LC788:
	ASCII(.string	"SPS HEVC_DecPTL error.\n" )
.LC790:
	ASCII(.string	"sps_seq_parameter_set_id" )
	.zero	7
.LC792:
	ASCII(.string	"sps_seq_parameter_set_id out of range(0,%d).\n" )
	.zero	2
.LC795:
	ASCII(.string	"SPS[%d] decode error0.\n" )
.LC797:
	ASCII(.string	"SPS[%d] decode error.\n" )
	.zero	1
.LC799:
	ASCII(.string	"pps_seq_parameter_set_id" )
	.zero	7
.LC801:
	ASCII(.string	"pic_parameter_set_id(%d) out of range[0,15].\n" )
	.zero	2
.LC803:
	ASCII(.string	"SPS(%d) haven't decode.\n" )
	.zero	7
.LC805:
	ASCII(.string	"num_ref_idx_l0_default_active_minus1" )
	.zero	3
.LC807:
	ASCII(.string	"num_ref_idx_l0_default_active out of range[0,15].\n" )
	.zero	5
.LC809:
	ASCII(.string	"num_ref_idx_l1_default_active_minus1" )
	.zero	3
.LC811:
	ASCII(.string	"num_ref_idx_l1_default_active out of range[0,15].\n" )
	.zero	5
.LC813:
	ASCII(.string	"init_qp_minus26" )
.LC815:
	ASCII(.string	"pic_init_qp(%d) out of range[-%d,51].\n" )
	.zero	1
.LC817:
	ASCII(.string	"diff_cu_qp_delta_depth" )
	.zero	1
.LC819:
	ASCII(.string	"diff_cu_qp_delta_depth out of range[0,3].\n" )
	.zero	5
.LC821:
	ASCII(.string	"pps_cb_qp_offset" )
	.zero	7
.LC823:
	ASCII(.string	"pic_cb_qp_offset out of range[-12,12].\n" )
.LC825:
	ASCII(.string	"pps_cr_qp_offset" )
	.zero	7
.LC827:
	ASCII(.string	"pic_cr_qp_offset out of range[-12,12].\n" )
.LC829:
	ASCII(.string	"num_tile_columns_minus1" )
.LC831:
	ASCII(.string	"num_tile_columns(%d) out of range(0,%d).\n" )
	.zero	6
.LC833:
	ASCII(.string	"num_tile_rows_minus1" )
	.zero	3
.LC835:
	ASCII(.string	"num_tile_rows out(%d) of range(0,%d).\n" )
	.zero	1
.LC837:
	ASCII(.string	"Logic limit(%d), num_tile_columns(%d) exceed.\n" )
	.zero	1
.LC840:
	ASCII(.string	"Logic limit(%d), num_tile_rows(%d) exceed.\n" )
	.zero	4
.LC842:
	ASCII(.string	"column_width_minus1" )
	.zero	4
.LC844:
	ASCII(.string	"column_width[%d](%d) out of range (0 %d)\n" )
	.zero	6
.LC846:
	ASCII(.string	"row_height_minus1" )
	.zero	6
.LC848:
	ASCII(.string	"row_height[%d](%d) out of range (0 %d)\n" )
.LC850:
	ASCII(.string	"column_bd[%d](%d) <= 0, invalid!\n" )
	.zero	6
.LC852:
	ASCII(.string	"row_bd[%d](%d) <= 0, invalid!\n" )
	.zero	1
.LC854:
	ASCII(.string	"PPS tile width(%d) is too small.(Logic Unsupport)\n" )
	.zero	5
.LC856:
	ASCII(.string	"PPS tile height(%d) is too small.(Logic Unsupport)\n" )
	.zero	4
.LC858:
	ASCII(.string	"pps_beta_offset_div2" )
	.zero	3
.LC860:
	ASCII(.string	"pps_beta_offset_div2(%d) out of range(-6,6).\n" )
	.zero	2
.LC862:
	ASCII(.string	"pps_tc_offset_div2" )
	.zero	5
.LC864:
	ASCII(.string	"pps_tc_offset_div2(%d) out of range(-6,6).\n" )
	.zero	4
.LC866:
	ASCII(.string	"PPS HEVC_DecScalingListData error.\n" )
	.zero	4
.LC868:
	ASCII(.string	"log2_parallel_merge_level_minus2" )
	.zero	7
.LC870:
	ASCII(.string	"log2_parallel_merge_level(%d) out of range(2,log2_ctb_sizeY).\n" )
	.zero	1
.LC872:
	ASCII(.string	"log2_max_transform_skip_block_size_minus2" )
	.zero	6
.LC874:
	ASCII(.string	"log2_sao_offset_scale_luma" )
	.zero	5
.LC876:
	ASCII(.string	"log2_sao_offset_scale_chroma" )
	.zero	3
.LC878:
	ASCII(.string	"diff_cu_chroma_qp_offset_depth" )
	.zero	1
.LC880:
	ASCII(.string	"chroma_qp_offset_list_len_minus1" )
	.zero	7
.LC882:
	ASCII(.string	"chroma_qp_offset_list_len_minus1 %d > 5\n" )
	.zero	7
.LC884:
	ASCII(.string	"cb_qp_offset_list" )
	.zero	6
.LC886:
	ASCII(.string	"cr_qp_offset_list" )
	.zero	6
.LC888:
	ASCII(.string	"pps_scaling_list_ref_layer_id %d > HEVC_MAX_NUM_LAYERS %d\n" )
	.zero	5
.LC890:
	ASCII(.string	"num_ref_loc_offsets" )
	.zero	4
.LC892:
	ASCII(.string	"num_ref_loc_offsets %d > HEVC_EXT_MAX_REF_LOC_OFFSET %d\n" )
	.zero	7
.LC894:
	ASCII(.string	"ref_loc_offset_layer_id %d > HEVC_EXT_MAX_REF_LOC_OFFSET %d\n" )
	.zero	3
.LC896:
	ASCII(.string	"scaled_ref_layer_left_offset" )
	.zero	3
.LC898:
	ASCII(.string	"scaled_ref_layer_top_offset" )
	.zero	4
.LC900:
	ASCII(.string	"scaled_ref_layer_right_offset" )
	.zero	2
.LC902:
	ASCII(.string	"scaled_ref_layer_bottom_offset" )
	.zero	1
.LC904:
	ASCII(.string	"ref_region_left_offset" )
	.zero	1
.LC906:
	ASCII(.string	"ref_region_top_offset" )
	.zero	2
.LC908:
	ASCII(.string	"ref_region_right_offset" )
.LC910:
	ASCII(.string	"ref_region_bottom_offset" )
	.zero	7
.LC912:
	ASCII(.string	"phase_hor_luma" )
	.zero	1
.LC914:
	ASCII(.string	"phase_ver_luma" )
	.zero	1
.LC916:
	ASCII(.string	"phase_hor_chroma_plus8" )
	.zero	1
.LC918:
	ASCII(.string	"phase_ver_chroma_plus8" )
	.zero	1
.LC920:
	ASCII(.string	"HEVC_ParsePPSExtension failed.\n" )
.LC925:
	ASCII(.string	"pps_pic_parameter_set_id" )
	.zero	7
.LC927:
	ASCII(.string	"pic_parameter_set_id(%d) out of range(0,%d).\n" )
	.zero	2
.LC930:
	ASCII(.string	"PPS[%d] decode error.\n" )
	.zero	1
.LC932:
	ASCII(.string	"luma_log2_weight_denom" )
	.zero	1
.LC934:
	ASCII(.string	"luma_log2_weight_denom out of range(0,7).\n" )
	.zero	5
.LC936:
	ASCII(.string	"delta_chroma_log2_weight_denom" )
	.zero	1
.LC938:
	ASCII(.string	"delta_chroma_log2_weight_denom out of range(-7,7).\n" )
	.zero	4
.LC940:
	ASCII(.string	"chroma_log2_weight_denom out of range(0,7).\n" )
	.zero	3
.LC942:
	ASCII(.string	"delta_luma_weight_l0" )
	.zero	3
.LC944:
	ASCII(.string	"delta_luma_weight_l0(%d) out of range(-128,127).\n" )
	.zero	6
.LC946:
	ASCII(.string	"luma_offset_l0" )
	.zero	1
.LC948:
	ASCII(.string	"luma_offset_l0(%d) out of range(-128,127).\n" )
	.zero	4
.LC950:
	ASCII(.string	"delta_chroma_weight_l0" )
	.zero	1
.LC952:
	ASCII(.string	"delta_chroma_weight_l0 out of range(-128,127).\n" )
.LC954:
	ASCII(.string	"delta_chroma_offset_l0" )
	.zero	1
.LC956:
	ASCII(.string	"delta_chroma_offset_l0 out of range(-512,511).\n" )
.LC958:
	ASCII(.string	"delta_luma_weight_l1" )
	.zero	3
.LC960:
	ASCII(.string	"delta_luma_weight_l1 out of range(-128,127).\n" )
	.zero	2
.LC962:
	ASCII(.string	"luma_offset_l1" )
	.zero	1
.LC964:
	ASCII(.string	"luma_offset_l1 out of range(-128,127).\n" )
.LC966:
	ASCII(.string	"delta_chroma_weight_l1" )
	.zero	1
.LC968:
	ASCII(.string	"delta_chroma_weight_l1 out of range(-128,127).\n" )
.LC970:
	ASCII(.string	"delta_chroma_offset_l1" )
	.zero	1
.LC972:
	ASCII(.string	"delta_chroma_offset_l1 out of range(-512,511).\n" )
.LC974:
	ASCII(.string	"slice_pic_parameter_set_id" )
	.zero	5
.LC977:
	ASCII(.string	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\n" )
	.zero	6
.LC979:
	ASCII(.string	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\n" )
.LC981:
	ASCII(.string	"max_cu_width(%d)/max_cu_height(%d) = 0\n" )
.LC983:
	ASCII(.string	"slice_segment_address(%d) out of range(0,%d).\n" )
	.zero	1
.LC985:
	ASCII(.string	"slice_type" )
	.zero	5
.LC987:
	ASCII(.string	"slice_type(%d) out of range(0,2].\n" )
	.zero	5
.LC989:
	ASCII(.string	"HEVC_ClearDPB,LastDisplayPoc:%d poc:%d \n" )
	.zero	7
.LC991:
	ASCII(.string	"SH HEVC_DecShortTermRefPicSet error.\n" )
	.zero	2
.LC993:
	ASCII(.string	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\n" )
	.zero	4
.LC995:
	ASCII(.string	"num_long_term_sps" )
	.zero	6
.LC997:
	ASCII(.string	"num_long_term_sps(%d) out of range[0,%d].\n" )
	.zero	5
.LC999:
	ASCII(.string	"num_long_term_pics" )
	.zero	5
.LC1001:
	ASCII(.string	"SH ERROR: (num_negative_pics(%d) + num_positive_pics(%d) + num_of_longterm_pics(%d)) > %d\n" )
	.zero	5
.LC1003:
	ASCII(.string	"lt_idx_sps[%d] = %d, but out of range[0,%d].\n" )
	.zero	2
.LC1005:
	ASCII(.string	"delta_poc_msb_cycle_lt" )
	.zero	1
.LC1007:
	ASCII(.string	"ERROR: pRPS->num_of_pics(%d) > %d.\n" )
	.zero	4
.LC1009:
	ASCII(.string	"Error0: Parse num_active_ref_layer_pics %d > HEVC_MAX_NUM_LAYERS %d, not support\n" )
	.zero	6
.LC1011:
	ASCII(.string	"Error1: Parse num_active_ref_layer_pics %d > HEVC_MAX_NUM_LAYERS %d, not support\n" )
	.zero	6
.LC1013:
	ASCII(.string	"Parse inter_layer_pred_layer_idc[%d] %d > HEVC_MAX_NUM_LAYERS %d, not support" )
	.zero	2
.LC1015:
	ASCII(.string	"num_ref_idx_l0_active_minus1" )
	.zero	3
.LC1017:
	ASCII(.string	"num_ref_idx_l0_active(%d) out of range(0,%d).\n" )
	.zero	1
.LC1019:
	ASCII(.string	"num_ref_idx_l1_active_minus1" )
	.zero	3
.LC1021:
	ASCII(.string	"num_ref_idx_l1_active(%d) out of range(0,%d).\n" )
	.zero	1
.LC1023:
	ASCII(.string	"pRPS is null.\n" )
	.zero	1
.LC1025:
	ASCII(.string	"pRPS->num_of_pics out(%d) of range(0,%d).\n" )
	.zero	5
.LC1027:
	ASCII(.string	"SH HEVC_DecRefPicListsModification error.\n" )
	.zero	5
.LC1029:
	ASCII(.string	"collocated_ref_idx" )
	.zero	5
.LC1031:
	ASCII(.string	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) out of range(0,%d).\n" )
.LC1033:
	ASCII(.string	"SH HEVC_DecPredWeightTable error.\n" )
	.zero	5
.LC1035:
	ASCII(.string	"five_minus_max_num_merge_cand" )
	.zero	2
.LC1037:
	ASCII(.string	"SH max_num_merge_cand(%d) out of range(1,5).\n" )
	.zero	2
.LC1039:
	ASCII(.string	"slice_qp_delta" )
	.zero	1
.LC1041:
	ASCII(.string	"SH slice_qp(%d) out of range [-%d,51].\n" )
.LC1043:
	ASCII(.string	"slice_cb_qp_offset" )
	.zero	5
.LC1045:
	ASCII(.string	"SH slice_cb_qp_offset(%d) out of range[-12,12].\n" )
	.zero	7
.LC1047:
	ASCII(.string	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out of range[-12,12].\n" )
	.zero	2
.LC1049:
	ASCII(.string	"slice_cr_qp_offset" )
	.zero	5
.LC1051:
	ASCII(.string	"SH slice_cr_qp_offset(%d) out of range[-12,12].\n" )
	.zero	7
.LC1053:
	ASCII(.string	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) out of range[-12,12].\n" )
.LC1055:
	ASCII(.string	"slice_beta_offset_div2" )
	.zero	1
.LC1057:
	ASCII(.string	"SH slice_beta_offset_div2(%d) out of range(-6,6).\n" )
	.zero	5
.LC1059:
	ASCII(.string	"slice_tc_offset_div2" )
	.zero	3
.LC1061:
	ASCII(.string	"SH slice_tc_offset_div2(%d) out of range(-6,6).\n" )
	.zero	7
.LC1063:
	ASCII(.string	"num_entry_point_offsets" )
.LC1065:
	ASCII(.string	"CurrSlice.num_entry_point_offsets(%d) out of range[0,%d].\n" )
	.zero	5
.LC1067:
	ASCII(.string	"offset_len_minus1" )
	.zero	6
.LC1069:
	ASCII(.string	"CurrSlice.offset_len(%d) out of range[1,32].\n" )
	.zero	2
.LC1071:
	ASCII(.string	"slice_segment_header_extension_length" )
	.zero	2
.LC1073:
	ASCII(.string	"slice_segment_header_extension_length(%d) out of range [0,256]\n" )
.LC1075:
	ASCII(.string	"bitsLeft(%d) < slice_segment_header_extension_length(%d)\n" )
	.zero	6
.LC1077:
	ASCII(.string	"HEVC_ParseSliceExtension failed\n" )
	.zero	7
.LC1082:
	ASCII(.string	"%s layer num %d invalid!\n" )
	.zero	6
.LC1084:
	ASCII(.string	"%s layer %d image size abnormal(%dx%d)\n" )
.LC1087:
	ASCII(.string	"%s arrange mem failed.\n" )
.LC1089:
	ASCII(.string	"Init dec para\n" )
	.zero	1
.LC1093:
	ASCII(.string	"Is SHVC: layer%d %dx%d, layer%d %dx%d.\n" )
.LC1095:
	ASCII(.string	"Layer %d: %d x %d\n" )
	.zero	5
.LC1097:
	ASCII(.string	"HEVC_InitDPB error, return %d\n" )
	.zero	1
.LC1099:
	ASCII(.string	"HEVC_AllocFrameStore error\n" )
	.zero	4
.LC1102:
	ASCII(.string	"%s: HEVC_OutputFrame failed!\n" )
	.zero	2
.LC1105:
	ASCII(.string	"%s output current picture failed\n" )
	.zero	6
.LC1109:
	ASCII(.string	"HEVC.c line %d: frame para err(ret=%d), recycle image self\n" )
	.zero	4
.LC1113:
	ASCII(.string	"%s: BlockFsPoc:%d, LastPoc:%d!\n" )
.LC1115:
	ASCII(.string	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\n" )
.LC1117:
	ASCII(.string	"%s: poc:%d, CurPos: %d !\n" )
	.zero	6
.LC1121:
	ASCII(.string	"%s call HEVC_GetUnRefPicWithMinPoc failed\n" )
	.zero	5
.LC1123:
	ASCII(.string	"%s call HEVC_OutputOneFrmFromDPB failed\n" )
	.zero	7
.LC1126:
	ASCII(.string	"%s: HEVC_OutputFrmToVO err!\n" )
	.zero	3
.LC1128:
	ASCII(.string	"cann't find slot for current nal\n" )
	.zero	6
.LC1130:
	ASCII(.string	"receive a zero packet\n" )
	.zero	1
.LC1132:
	ASCII(.string	"nal_release_err\n" )
	.zero	7
.LC1135:
	ASCII(.string	"%s: flush dpb failed, return %d\n" )
	.zero	7
.LC1138:
	ASCII(.string	"%s: DPB.used_size(%d) >= DPB.size(%d), need to increase DPB size.\n" )
	.zero	5
.LC1140:
	ASCII(.string	"%s call HEVC_IncreaseDPBSize failed\n" )
	.zero	3
.LC1142:
	ASCII(.string	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpoc frame.\n" )
	.zero	3
.LC1147:
	ASCII(.string	"%s with invalid pos(%d)\n" )
	.zero	7
.LC1150:
	ASCII(.string	"%s get APC error, ret %d\n" )
	.zero	6
.LC1153:
	ASCII(.string	"%s %d: InsertFrmInDPB failed, return %d\n" )
	.zero	7
.LC1155:
	ASCII(.string	"%s call HEVC_CheckFrameStore failed!\n" )
	.zero	2
.LC1159:
	ASCII(.string	"%s call HEVC_RemoveUnUsedFrameStore Failed.\n" )
	.zero	3
.LC1161:
	ASCII(.string	"%s call HEVC_InsertFrmInDPB Failed.\n" )
	.zero	3
.LC1166:
	ASCII(.string	"%s call HEVC_FirstFrameFastOut Failed\n" )
	.zero	1
.LC1168:
	ASCII(.string	"DPB.used_size may bigger than DPB.size\n" )
.LC1170:
	ASCII(.string	"HEVC_InsertFrmInDPB Failed, ret = %d\n" )
	.zero	2
.LC1172:
	ASCII(.string	"%s call HEVC_OutputFrmFromDPB failed\n" )
	.zero	2
.LC1176:
	ASCII(.string	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_NORMAL\n" )
	.zero	5
.LC1178:
	ASCII(.string	"%s, REPORT_IFRAME_ERR\n" )
	.zero	1
.LC1181:
	ASCII(.string	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\n" )
	.zero	1
.LC1183:
	ASCII(.string	"%s call HEVC_IModeProcess Failed\n" )
	.zero	6
.LC1185:
	ASCII(.string	"HEVC_StorePicInDpb return(%d) from L%d\n" )
.LC1187:
	ASCII(.string	"%s call HEVC_SimpleDPBProcess Failed\n" )
	.zero	2
.LC1189:
	ASCII(.string	"%s call HEVC_DecOrderProcess Failed\n" )
	.zero	3
.LC1191:
	ASCII(.string	"%s call HEVC_DispOrderProcess Failed\n" )
	.zero	2
.LC1193:
	ASCII(.string	"%s return HEVC_DEC_ERR\n" )
.LC1196:
	ASCII(.string	"No frame store for lost pic.\n" )
	.zero	2
.LC1198:
	ASCII(.string	"DPB ERROR: Can not get ref_fs!\n" )
.LC1200:
	ASCII(.string	"DPB no suited fs for lost pic.\n" )
.LC1202:
	ASCII(.string	"Take poc(%d) to creat lost poc(%d).\n" )
	.zero	3
.LC1204:
	ASCII(.string	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\n" )
	.zero	5
.LC1206:
	ASCII(.string	"ERROR: Can not new logic fs!\n" )
	.zero	2
.LC1208:
	ASCII(.string	"Lost pic insert in DPB Failed!\n" )
.LC1210:
	ASCII(.string	"Ref frame(poc %d) lost.\n" )
	.zero	7
.LC1212:
	ASCII(.string	"s32OutErrThr = %d,drop poc %d because lost ref frame(pod %d)\n" )
	.zero	2
.LC1215:
	ASCII(.string	"DecVDM MaxBytesReceived exceed threshold!\n" )
	.zero	5
.LC1217:
	ASCII(.string	"DecVDM no slice and needn't start VDM\n" )
	.zero	1
.LC1219:
	ASCII(.string	"IPBDecMode Changed (%d -> %d)\n" )
	.zero	1
.LC1222:
	ASCII(.string	"VDM start, TotalPicNum=%d.\n" )
	.zero	4
.LC1225:
	ASCII(.string	"%s no correct slice in the pic\n" )
.LC1227:
	ASCII(.string	"Discard this B(poc=%d) before P, is_ref_idc=%d.\n" )
	.zero	7
.LC1230:
	ASCII(.string	"metadatasize is too large:%d at line:%d\n" )
	.zero	7
.LC1233:
	ASCII(.string	"%s:%d Metadata map failed\n" )
	.zero	5
.LC1237:
	ASCII(.string	"%s:%d Metadata unmap failed\n" )
	.zero	3
.LC1240:
	ASCII(.string	"*****[%s][%d],BL Codec can only dec BL stream!!*****\n" )
	.zero	2
.LC1242:
	ASCII(.string	"*****[%s][%d],EL Codec can only dec EL stream in DV_DUAL_VES_IMP stream!!*****\n" )
.LC1244:
	ASCII(.string	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****\n" )
	.zero	3
.LC1248:
	ASCII(.string	"%s call HEVC_FlushOutputFrmFromDPB failed\n" )
	.zero	5
.LC1250:
	ASCII(.string	"%s call HEVC_EmptyFrmFromDPB failed\n" )
	.zero	3
.LC1252:
	ASCII(.string	"Meet CRA frame, force output remain frame, CurPoc %d, LastPoc %d\n" )
	.zero	6
.LC1254:
	ASCII(.string	"Init pic err, exit\n" )
	.zero	4
.LC1256:
	ASCII(.string	"HEVC_WritePicMsg failed!\n" )
	.zero	6
.LC1258:
	ASCII(.string	"Start Reason: SliceParaNum= %d\n" )
.LC1261:
	ASCII(.string	"Too many slice , err!\n" )
	.zero	1
.LC1263:
	ASCII(.string	"Cur pic not init yet, discard this slice!\n" )
	.zero	5
.LC1265:
	ASCII(.string	"Dec List error, ret=%d\n" )
.LC1267:
	ASCII(.string	"Ref List is Wrong!\n" )
	.zero	4
.LC1269:
	ASCII(.string	"HEVC_WriteSliceMsg err.\n" )
	.zero	7
.LC1272:
	ASCII(.string	"VPS decode error.\n" )
	.zero	5
.LC1275:
	ASCII(.string	"SPS decode error.\n" )
	.zero	5
.LC1277:
	ASCII(.string	"PPS decode error.\n" )
	.zero	5
.LC1279:
	ASCII(.string	"SEI decode error.\n" )
	.zero	5
.LC1281:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d\n" )
.LC1284:
	ASCII(.string	"HEVC_DecSliceSegmentHeader dec err\n" )
	.zero	4
.LC1287:
	ASCII(.string	"CurBitsLen = %d, MinBitsLen = %d\n" )
	.zero	6
.LC1290:
	ASCII(.string	"%s last frame fs unrelease, fix it!\n" )
	.zero	3
.LC1294:
	ASCII(.string	"CtbNumOneFrame=%d, SedEnd0=%d\n" )
	.zero	1
.LC1298:
	ASCII(.string	"OSAL_FP_alloc_virmem g_pGlbVar fail %d\n" )
.LC1306:
	ASCII(.string	"%s: Get context addr failed!\n" )
	.zero	2
.LC1308:
	ASCII(.string	"%s FATAL: MemOffset %d > ContextMemSize %d.\n" )
	.zero	3
.LC1310:
	ASCII(.string	"%s: VCTRL_GetChanIDByCtx() return -1!\n" )
	.zero	1
.LC1312:
	ASCII(.string	"Fs leak, clear dpb fs not in vo queue.\n" )
.LC1314:
	ASCII(.string	"No frame store available!\n" )
	.zero	5
.LC1317:
	ASCII(.string	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak, ClearAll!\n" )
.LC1319:
	ASCII(.string	"HEVCDEC_DecodePacket NULL == pPacket!\n" )
	.zero	1
.LC1321:
	ASCII(.string	"HevcCtx not init!\n" )
	.zero	5
.LC1323:
	ASCII(.string	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\n" )
	.zero	6
.LC1326:
	ASCII(.string	"nal_layer_id out %d of range[0,1].\n" )
	.zero	4
.LC1328:
	ASCII(.string	"Not need nal of layer %d in output order %d.\n" )
	.zero	2
.LC1334:
	ASCII(.string	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	4
.LC1337:
	ASCII(.string	"HEVC_InquireSliceProperty error.\n" )
	.zero	6
.LC1340:
	ASCII(.string	"HEVC_DecOneNal ERR\n" )
	.zero	4
.LC1344:
	ASCII(.string	"pHevcCtx->CurrPic.frame_store is null pointer\n" )
	.zero	1
.LC1346:
	ASCII(.string	"HEVC_StorePicInDPB failed, ret = %d\n" )
	.bss
	.align	3
.LANCHOR1 = . + 0
	.type	g_pGlbVar, %object
	.size	g_pGlbVar, 8
g_pGlbVar:
	.zero	8
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
