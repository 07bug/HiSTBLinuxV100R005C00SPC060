#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"postprocess.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	PostPro_BubbleSort
	.type	PostPro_BubbleSort, %function
PostPro_BubbleSort:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w9, [x19, 12]
	mov	w8, 1
	add	x10, x19, 20
	cmp	w9, w8
	bls	.L1
	.p2align 2
.L10:
	mov	w1, 0
	sub	w5, w9, w8
	cmp	w1, w5
	add	w1, w1, 1
	mov	x0, x10
	mov	w7, 0
	add	x2, x19, x1, uxtw 2
	beq	.L14
	.p2align 2
.L5:
	ldrh	w3, [x0]
	ldrh	w4, [x2, 20]
	cmp	w3, w4
	bls	.L4
	strh	w4, [x0]
	mov	w7, 1
	ldrh	w4, [x0, 2]
	ldrh	w6, [x2, 22]
	strh	w6, [x0, 2]
	strh	w3, [x2, 20]
	strh	w4, [x2, 22]
.L4:
	cmp	w1, w5
	add	w1, w1, 1
	add	x0, x0, 4
	add	x2, x19, x1, uxtw 2
	bne	.L5
.L14:
	cbz	w7, .L1
	add	w8, w8, 1
	cmp	w9, w8
	ccmp	w7, 1, 0, hi
	beq	.L10
.L1:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PostPro_BubbleSort, .-PostPro_BubbleSort
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetH264MbOfMBAFF
	.type	PostPro_GetH264MbOfMBAFF, %function
PostPro_GetH264MbOfMBAFF:
	sub	sp, sp, #800
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	ldp	w9, w10, [x20, 28]
	lsl	w1, w9, 1
	cbz	w0, .L30
	sub	w0, w0, #1
	mov	x8, 6
	add	x3, x29, 32
	add	x2, x19, 20
	add	x8, x8, x0, uxtw 2
	add	x0, x29, 34
	add	x8, x3, x8
	.p2align 2
.L17:
	ldrh	w4, [x2]
	add	x2, x2, 4
	ldrh	w3, [x2, -2]
	strh	w4, [x0, -2]
	strh	w3, [x0], 4
	cmp	x0, x8
	bne	.L17
	ldrh	w0, [x29, 34]
	ldrh	w3, [x29, 32]
	orr	w0, w0, 1
	and	w3, w3, 65534
	strh	w3, [x29, 32]
	uxth	w0, w0
	strh	w0, [x29, 34]
	cbz	w1, .L30
	add	x6, x29, 38
	mov	w7, 0
	sub	w11, w1, #2
	uxth	w12, w1
	b	.L26
	.p2align 3
.L36:
	cmp	w4, w13
	lsr	w2, w2, 1
	lsr	w15, w3, 1
	beq	.L21
	mul	w4, w12, w4
	uxtw	x14, w7
	add	w3, w7, 1
	cmp	w3, 199
	add	x0, x19, x14, lsl 2
	uxth	w4, w4
	add	w2, w4, w2
	mov	x14, x0
	uxth	w2, w2
	strh	w2, [x0, 20]
	ldr	w0, [x20, 28]
	sub	w0, w0, #1
	add	w4, w4, w0
	strh	w4, [x14, 22]
	bhi	.L22
	mul	w0, w12, w13
	ldr	w4, [x20, 28]
	add	x13, x19, x3, lsl 2
	uxth	w15, w15
	add	w2, w2, w4
	uxth	w0, w0
	add	w4, w7, 2
	add	w5, w0, w15
	strh	w2, [x13, 20]
	cmp	w4, 199
	strh	w5, [x13, 22]
	bhi	.L22
	ldr	w2, [x20, 28]
	add	x3, x19, x4, lsl 2
	add	w7, w7, 3
	add	w2, w0, w2
	cmp	w7, 199
	uxth	w0, w2
	strh	w0, [x3, 20]
	add	w0, w15, w0
	strh	w0, [x3, 22]
	bhi	.L22
.L23:
	cmp	x6, x8
	beq	.L25
.L27:
	ldrh	w0, [x6]
	ldrh	w3, [x6, -2]
	orr	w0, w0, 1
	and	w3, w3, 65534
	strh	w3, [x6, -2]
	uxth	w0, w0
	strh	w0, [x6], 4
.L26:
	udiv	w4, w3, w1
	mul	w5, w4, w1
	sub	w2, w3, w5
	cmp	w2, 1
	bls	.L19
	udiv	w13, w0, w1
	msub	w3, w13, w1, w0
	cmp	w11, w3
	bhi	.L36
	uxtw	x4, w7
	uxth	w5, w5
	add	w2, w5, w2, lsr 1
	add	w3, w7, 1
	add	x13, x19, x4, lsl 2
	cmp	w3, 199
	uxth	w2, w2
	mov	x4, x13
	strh	w2, [x13, 20]
	ldr	w13, [x20, 28]
	sub	w13, w13, #1
	add	w5, w5, w13
	strh	w5, [x4, 22]
	bhi	.L22
	add	x5, x19, x3, lsl 2
	ldr	w4, [x20, 28]
	add	w7, w7, 2
	add	w2, w2, w4
	cmp	w7, 199
	strh	w2, [x5, 20]
	strh	w0, [x5, 22]
	bls	.L23
.L22:
	mul	w9, w9, w10
	mov	w0, 1
	strh	wzr, [x19, 20]
	sub	w9, w9, #1
	str	w0, [x19, 12]
	strh	w9, [x19, 22]
	mov	x0, x19
	bl	PostPro_BubbleSort
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	add	sp, sp, 800
	ret
	.p2align 3
.L19:
	udiv	w2, w0, w1
	mul	w2, w2, w1
	sub	w4, w0, w2
	cmp	w11, w4
	bls	.L24
	uxtw	x5, w7
	uxth	w2, w2
	ubfx	x4, x4, 1, 16
	add	w0, w7, 1
	add	x14, x19, x5, lsl 2
	add	w13, w2, w4
	cmp	w0, 199
	strh	w3, [x14, 20]
	strh	w13, [x14, 22]
	bhi	.L22
	uxtw	x3, w0
	ldr	w0, [x20, 28]
	add	w7, w7, 2
	add	x5, x19, x3, lsl 2
	add	w2, w2, w0
	cmp	w7, 199
	uxth	w2, w2
	strh	w2, [x5, 20]
	add	w2, w4, w2
	strh	w2, [x5, 22]
	bhi	.L22
	cmp	x6, x8
	bne	.L27
	.p2align 2
.L25:
	str	w7, [x19, 12]
.L37:
	mov	x0, x19
	bl	PostPro_BubbleSort
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	add	sp, sp, 800
	ret
	.p2align 3
.L24:
	uxtw	x2, w7
	add	w7, w7, 1
	cmp	w7, 199
	add	x4, x19, x2, lsl 2
	strh	w3, [x4, 20]
	strh	w0, [x4, 22]
	bls	.L23
	b	.L22
	.p2align 3
.L21:
	uxtw	x0, w7
	uxth	w5, w5
	add	w2, w5, w2
	add	w5, w5, w15
	add	x3, x19, x0, lsl 2
	add	w0, w7, 1
	uxth	w2, w2
	uxth	w5, w5
	cmp	w0, 199
	strh	w2, [x3, 20]
	strh	w5, [x3, 22]
	bhi	.L22
	add	x4, x19, x0, lsl 2
	ldr	w3, [x20, 28]
	add	w7, w7, 2
	add	w2, w2, w3
	cmp	w7, 199
	strh	w2, [x4, 20]
	ldr	w2, [x20, 28]
	add	w5, w5, w2
	strh	w5, [x4, 22]
	bls	.L23
	b	.L22
.L30:
	mov	w7, 0
	str	w7, [x19, 12]
	b	.L37
	.size	PostPro_GetH264MbOfMBAFF, .-PostPro_GetH264MbOfMBAFF
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetH264MbGroup
	.type	PostPro_GetH264MbGroup, %function
PostPro_GetH264MbGroup:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x21, x0
	mov	x0, x30
	mov	w22, w2
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w1, w2, #1
	cmp	w1, 199
	bhi	.L57
	ldp	w20, w0, [x21, 28]
	mul	w20, w20, w0
	cbnz	w22, .L58
.L41:
	str	wzr, [x21, 44]
	mov	w5, -1
	str	wzr, [x21, 56]
	uxth	w9, w20
	mov	w0, 0
	mov	w6, w5
	ldr	w1, [x19, 12]
	add	w10, w20, w5
	add	x2, x19, x1, lsl 2
	strh	w9, [x2, 22]
	strh	w9, [x2, 20]
	b	.L49
	.p2align 3
.L62:
	cmp	w1, w5
	csel	w5, w5, w6, ge
	add	w4, w5, 1
	cmp	w1, w4
	ble	.L44
	ldr	w4, [x21, 44]
	cmp	w4, 199
	bgt	.L59
	add	x8, x21, x4, sxtw 2
	add	w6, w6, w6, lsr 31
	sub	w5, w5, #100
	sub	w7, w1, #1
	sxth	w6, w6
	strh	w7, [x8, 78]
	cmp	w5, w6
	strh	w6, [x8, 76]
	ble	.L46
	strh	w5, [x8, 76]
.L46:
	add	w4, w4, 1
	str	w4, [x21, 44]
.L44:
	ldr	w4, [x19, 12]
	sub	w5, w4, #1
	cmp	w5, w0
	beq	.L60
.L52:
	add	w0, w0, 1
	mov	w5, w2
	cmp	w0, w4
	mov	w6, w1
	bhi	.L61
.L49:
	uxtw	x3, w0
	add	x1, x19, x3, lsl 2
	mov	x2, x1
	ldrh	w1, [x1, 20]
	ldrh	w2, [x2, 22]
	cmp	w20, w1
	ccmp	w20, w2, 1, ge
	ccmp	w1, w2, 0, ge
	ble	.L62
	ldr	w4, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w4
	bls	.L49
.L61:
	mov	w0, 0
.L40:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L60:
	add	x3, x19, x3, lsl 2
	ldrh	w3, [x3, 22]
	cmp	w3, w10
	bge	.L52
	ldr	w0, [x21, 44]
	cmp	w0, 199
	bgt	.L63
	add	x2, x21, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w3, [x2, 76]
	strh	w9, [x2, 78]
	str	w1, [x21, 44]
	b	.L40
	.p2align 3
.L58:
	mov	x1, x19
	mov	x0, x21
	bl	PostPro_GetH264MbOfMBAFF
	b	.L41
.L57:
	ldr	x1, .LC3
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L59:
	ldr	x1, .LC5
	mov	w2, 270
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L40
.L63:
	ldr	x1, .LC5
	mov	w2, 295
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L40
	.size	PostPro_GetH264MbGroup, .-PostPro_GetH264MbGroup
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC5:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetH264RepairParam
	.type	PostPro_GetH264RepairParam, %function
PostPro_GetH264RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x19, 308]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 324]
	str	w0, [x20, 8]
	ldr	x0, [x19, 944]
	ldr	w4, [x0, 1640]
	add	x0, x19, x4, uxtw 2
	ldr	w0, [x0, 324]
	str	w0, [x20, 20]
	ldr	w0, [x19, 316]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 584]
	str	w0, [x20, 24]
	ldr	w0, [x19, 44]
	str	w0, [x20, 28]
	ldr	w0, [x19, 36]
	str	w0, [x20, 32]
	ldrb	w0, [x19]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 36]
	ldrb	w0, [x19, 1]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 40]
	ldr	w5, [x19, 936]
	cbz	w5, .L65
	ldr	w0, [x19, 1120]
	cmp	w4, w0
	beq	.L102
	mov	w0, 0
	b	.L68
	.p2align 3
.L69:
	ldr	w3, [x19, x3, lsl 2]
	cmp	w4, w3
	beq	.L66
.L68:
	add	w0, w0, 1
	cmp	w0, w5
	sxtw	x2, w0
	add	x3, x2, 280
	bne	.L69
.L65:
	ldr	w2, [x19, 48]
	cbz	w2, .L70
	ldrb	w0, [x19]
	cmp	w0, wzr
	cset	w2, eq
.L70:
	ldrsb	w0, [x19, 2]
	cbnz	w0, .L103
	str	wzr, [x21, 12]
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	beq	.L104
.L73:
	ldrb	w0, [x19]
	cbz	w0, .L82
	cmp	w0, 1
	beq	.L100
	cmp	w0, 2
	beq	.L100
	cmp	w0, 3
	bne	.L79
.L82:
	str	wzr, [x20, 52]
.L79:
	ldrb	w1, [x19, 4]
	mov	w0, 4
	strb	w1, [x20]
	str	w0, [x20, 64]
	ldr	w0, [x19, 720]
	str	w0, [x20, 12]
	ldr	w0, [x19, 724]
	str	w0, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L100:
	str	w0, [x20, 52]
	b	.L79
.L102:
	mov	x2, 0
	.p2align 2
.L66:
	add	x2, x2, 264
	ldr	w0, [x19, x2, lsl 2]
	str	w0, [x20, 48]
	b	.L65
	.p2align 3
.L103:
	mov	x1, x21
	mov	x0, x20
	bl	PostPro_GetH264MbGroup
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	bne	.L73
.L104:
	ldr	w3, [x19, 580]
	cbz	w3, .L73
	ldr	w1, [x19, 324]
	mov	w0, 0
	cmp	w2, w1
	bne	.L74
	.p2align 2
.L76:
	add	w0, w0, 1
	cmp	w3, w0
	add	x1, x19, x0, sxtw 2
	beq	.L73
	ldr	w1, [x1, 324]
	cmp	w2, w1
	beq	.L76
.L74:
	str	w1, [x20, 20]
	b	.L73
	.size	PostPro_GetH264RepairParam, .-PostPro_GetH264RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetMVCRepairParam
	.type	PostPro_GetMVCRepairParam, %function
PostPro_GetMVCRepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x19, 308]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 324]
	str	w0, [x20, 8]
	ldr	x0, [x19, 944]
	ldr	w4, [x0, 1640]
	add	x0, x19, x4, uxtw 2
	ldr	w0, [x0, 324]
	str	w0, [x20, 20]
	ldr	w0, [x19, 316]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 584]
	str	w0, [x20, 24]
	ldr	w0, [x19, 44]
	str	w0, [x20, 28]
	ldr	w0, [x19, 36]
	str	w0, [x20, 32]
	ldrb	w0, [x19]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 36]
	ldrb	w0, [x19, 1]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 40]
	ldr	w5, [x19, 936]
	cbz	w5, .L106
	ldr	w0, [x19, 1120]
	cmp	w4, w0
	beq	.L143
	mov	w0, 0
	b	.L109
	.p2align 3
.L110:
	ldr	w3, [x19, x3, lsl 2]
	cmp	w4, w3
	beq	.L107
.L109:
	add	w0, w0, 1
	cmp	w0, w5
	sxtw	x2, w0
	add	x3, x2, 280
	bne	.L110
.L106:
	ldr	w2, [x19, 48]
	cbz	w2, .L111
	ldrb	w0, [x19]
	cmp	w0, wzr
	cset	w2, eq
.L111:
	ldrsb	w0, [x19, 2]
	cbnz	w0, .L144
	str	wzr, [x21, 12]
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	beq	.L145
.L114:
	ldrb	w0, [x19]
	cbz	w0, .L123
	cmp	w0, 1
	beq	.L141
	cmp	w0, 2
	beq	.L141
	cmp	w0, 3
	bne	.L120
.L123:
	str	wzr, [x20, 52]
.L120:
	ldrb	w1, [x19, 4]
	mov	w0, 4
	strb	w1, [x20]
	str	w0, [x20, 64]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L141:
	str	w0, [x20, 52]
	mov	w0, 4
	ldrb	w1, [x19, 4]
	strb	w1, [x20]
	str	w0, [x20, 64]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L143:
	mov	x2, 0
	.p2align 2
.L107:
	add	x2, x2, 264
	ldr	w0, [x19, x2, lsl 2]
	str	w0, [x20, 48]
	b	.L106
	.p2align 3
.L144:
	mov	x1, x21
	mov	x0, x20
	bl	PostPro_GetH264MbGroup
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	bne	.L114
.L145:
	ldr	w3, [x19, 580]
	cbz	w3, .L114
	ldr	w1, [x19, 324]
	mov	w0, 0
	cmp	w2, w1
	bne	.L115
	.p2align 2
.L117:
	add	w0, w0, 1
	cmp	w3, w0
	add	x1, x19, x0, sxtw 2
	beq	.L114
	ldr	w1, [x1, 324]
	cmp	w2, w1
	beq	.L117
.L115:
	str	w1, [x20, 20]
	b	.L114
	.size	PostPro_GetMVCRepairParam, .-PostPro_GetMVCRepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetHevcMbGroupOfTile
	.type	PostPro_GetHevcMbGroupOfTile, %function
PostPro_GetHevcMbGroupOfTile:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x21, x2
	mov	w20, w3
	bl	_mcount
	ldr	x22, .LC6
	ldr	x0, [x22]
	cbz	x0, .L196
	ldr	x0, .LC11
	sbfiz	x20, x20, 6, 32
	str	wzr, [x19, 44]
	add	x0, x0, x20
	str	wzr, [x19, 56]
	ldr	x1, .LC10
	ldp	w20, w2, [x19, 28]
	ldrsw	x0, [x0, 8]
	mul	w20, w20, w2
	ldr	x0, [x1, x0, lsl 3]
	add	x0, x0, 507904
	add	x0, x0, 1752
	bl	HEVC_CalcTileMap
	ldr	w1, [x23, 12]
	cbz	w1, .L155
	ldr	x7, [x22]
	mov	w8, 0
	mov	w9, 1
	.p2align 2
.L154:
	add	x5, x23, x8, uxtw 2
	ldrh	w3, [x5, 20]
	ldrh	w4, [x5, 22]
	mov	w0, w3
	cmp	w3, w4
	bhi	.L152
	mov	x6, x5
	b	.L153
	.p2align 3
.L191:
	ldrh	w3, [x5, 20]
.L153:
	cmp	w20, w3
	blt	.L156
	cmp	w20, w4
	uxtw	x3, w0
	add	x3, x3, 114688
	blt	.L156
	add	x3, x7, x3, lsl 2
	ldr	w2, [x3, 12660]
	add	x2, x7, x2
	add	x2, x2, 618496
	strb	w9, [x2, 372]
.L156:
	ldrh	w4, [x6, 22]
	add	w0, w0, 1
	cmp	w4, w0
	bcs	.L191
	ldr	w1, [x23, 12]
.L152:
	add	w8, w8, 1
	cmp	w1, w8
	bhi	.L154
.L155:
	ldr	w9, [x21, 2488]
	cmp	w9, 199
	bhi	.L197
	cbz	w9, .L157
	ldr	w3, [x21, 3592]
	mov	w8, 36863
	cmp	w3, w8
	bhi	.L198
	ldr	x4, [x22]
	mov	w2, 0
	mov	x7, 0
	.p2align 2
.L160:
	add	x0, x21, x7, lsl 3
	ldr	w6, [x0, 3588]
	cmp	w6, w3
	bhi	.L166
	uxtw	x0, w6
	add	x0, x0, 114688
	add	x0, x4, x0, lsl 2
	ldr	w5, [x0, 12660]
	add	x0, x4, x5
	add	x0, x0, 618496
	ldrb	w0, [x0, 372]
	cbz	w0, .L163
	mov	w1, w6
	b	.L165
	.p2align 3
.L168:
	add	x0, x4, x0, lsl 2
	ldr	w0, [x0, 12660]
	add	x0, x4, x0
	add	x0, x0, 618496
	ldrb	w0, [x0, 372]
	cbz	w0, .L163
.L165:
	add	w0, w1, 1
	cmp	w0, w3
	mov	x1, x0
	add	x0, x0, 114688
	bls	.L168
.L166:
	add	w2, w2, 1
	cmp	w9, w2
	bls	.L157
.L162:
	uxtw	x7, w2
	add	x0, x21, x7, lsl 3
	ldr	w3, [x0, 3592]
	cmp	w3, w8
	bls	.L160
.L158:
	ldr	x1, .LC15
	mov	w4, 36864
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L163:
	add	x1, x21, x7, lsl 3
	ldr	w0, [x1, 3592]
	cmp	w6, w0
	bls	.L167
	b	.L166
	.p2align 3
.L193:
	ldr	w5, [x0, 12660]
.L167:
	add	x5, x4, x5
	add	w0, w6, 1
	add	x5, x5, 618496
	mov	x6, x0
	add	x0, x0, 114688
	strb	wzr, [x5, 372]
	add	x0, x4, x0, lsl 2
	ldr	w3, [x1, 3592]
	cmp	w3, w6
	bcs	.L193
	ldr	w9, [x21, 2488]
	add	w2, w2, 1
	cmp	w9, w2
	bhi	.L162
.L157:
	ldr	x3, [x22]
	mov	w4, 0
	.p2align 2
.L173:
	cmp	w4, w20
	bcs	.L199
	add	x0, x3, x4, uxtw
	mov	w2, w4
	add	x0, x0, 618496
	ldrb	w0, [x0, 372]
	cmp	w0, 1
	bne	.L187
	b	.L200
	.p2align 3
.L201:
	ldrb	w1, [x1, 372]
	cbnz	w1, .L171
	mov	w2, w0
.L187:
	add	w0, w2, 1
	cmp	w0, w20
	add	x1, x3, x0, uxtw
	add	x1, x1, 618496
	bcc	.L201
.L171:
	ldr	w1, [x19, 44]
	add	w5, w1, 1
	add	x1, x19, x1, sxtw 2
	strh	w4, [x1, 76]
	mov	w4, w0
	strh	w2, [x1, 78]
	str	w5, [x19, 44]
.L170:
	cmp	w5, 199
	ble	.L173
	ldr	x1, .LC17
	mov	w0, 1
	sub	w20, w20, #1
	bl	dprint_vfmw
	strh	wzr, [x19, 76]
	strh	w20, [x19, 78]
	mov	w0, 1
	str	w0, [x19, 44]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L200:
	add	w4, w4, 1
	ldr	w5, [x19, 44]
	b	.L170
.L199:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L197:
	ldr	x1, .LC13
	mov	w3, 200
	mov	w2, w9
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L196:
	ldr	x2, .LC7
	ldr	x1, .LC9
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L198:
	mov	w2, 0
	b	.L158
	.size	PostPro_GetHevcMbGroupOfTile, .-PostPro_GetHevcMbGroupOfTile
	.align	3
.LC6:
	.xword	g_pGlbVar
	.align	3
.LC7:
	.xword	.LANCHOR0
	.align	3
.LC9:
	.xword	.LC8
	.align	3
.LC10:
	.xword	s_pstVfmwChan
	.align	3
.LC11:
	.xword	g_VdmDrvParam
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC17:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetHevcMbGroupOfNoTile
	.type	PostPro_GetHevcMbGroupOfNoTile, %function
PostPro_GetHevcMbGroupOfNoTile:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w20, w3
	mov	x19, x1
	bl	_mcount
	sbfiz	x20, x20, 6, 32
	ldr	x0, .LC19
	str	wzr, [x21, 44]
	add	x0, x0, x20
	str	wzr, [x21, 56]
	ldr	x1, .LC18
	ldp	w20, w2, [x21, 28]
	ldrsw	x0, [x0, 8]
	mul	w20, w20, w2
	ldr	x0, [x1, x0, lsl 3]
	add	x0, x0, 507904
	add	x0, x0, 1752
	bl	HEVC_CalcTileMap
	cbnz	w0, .L217
	ldr	w1, [x19, 12]
	mov	w6, -1
	uxth	w9, w20
	mov	w0, 0
	mov	w7, w6
	add	w10, w20, w6
	add	x2, x19, x1, lsl 2
	strh	w9, [x2, 22]
	strh	w9, [x2, 20]
	b	.L212
	.p2align 3
.L221:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w1, w6, 1
	cmp	w2, w1
	ble	.L207
	ldr	w3, [x21, 44]
	cmp	w3, 199
	bgt	.L218
	add	x8, x21, x3, sxtw 2
	add	w7, w7, w7, lsr 31
	sub	w6, w6, #100
	sub	w1, w2, #1
	sxth	w7, w7
	strh	w1, [x8, 78]
	cmp	w6, w7
	strh	w7, [x8, 76]
	ble	.L209
	strh	w6, [x8, 76]
.L209:
	add	w3, w3, 1
	str	w3, [x21, 44]
.L207:
	ldr	w1, [x19, 12]
	sub	w3, w1, #1
	cmp	w3, w0
	beq	.L219
.L215:
	add	w0, w0, 1
	mov	w6, w4
	cmp	w0, w1
	mov	w7, w2
	bhi	.L220
.L212:
	sxtw	x5, w0
	add	x2, x19, x5, lsl 2
	mov	x1, x2
	ldrh	w2, [x2, 20]
	ldrh	w4, [x1, 22]
	cmp	w20, w2
	ccmp	w20, w4, 1, ge
	ccmp	w2, w4, 0, ge
	ble	.L221
	ldr	w1, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w1
	bls	.L212
.L220:
	mov	w0, 0
.L204:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L219:
	add	x5, x19, x5, lsl 2
	ldrh	w5, [x5, 22]
	cmp	w5, w10
	bge	.L215
	ldr	w3, [x21, 44]
	cmp	w3, 199
	bgt	.L222
	add	x1, x21, x3, sxtw 2
	sub	w9, w9, #1
	add	w3, w3, 1
	mov	w0, 0
	strh	w5, [x1, 76]
	strh	w9, [x1, 78]
	str	w3, [x21, 44]
	b	.L204
.L217:
	ldr	x2, .LC20
	mov	w0, 1
	ldr	x1, .LC22
	add	x2, x2, 32
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L218:
	ldr	x2, .LC20
	mov	w0, 1
	ldr	x1, .LC24
	add	x2, x2, 32
	bl	dprint_vfmw
	mov	w0, 1
	b	.L204
.L222:
	ldr	x2, .LC20
	mov	w0, 1
	ldr	x1, .LC26
	add	x2, x2, 32
	bl	dprint_vfmw
	mov	w0, 1
	b	.L204
	.size	PostPro_GetHevcMbGroupOfNoTile, .-PostPro_GetHevcMbGroupOfNoTile
	.align	3
.LC18:
	.xword	s_pstVfmwChan
	.align	3
.LC19:
	.xword	g_VdmDrvParam
	.align	3
.LC20:
	.xword	.LANCHOR0
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC24:
	.xword	.LC23
	.align	3
.LC26:
	.xword	.LC25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetHevcMbGroup
	.type	PostPro_GetHevcMbGroup, %function
PostPro_GetHevcMbGroup:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w1, w2, #1
	cmp	w1, 199
	bhi	.L227
	ldr	w0, [x20, 68]
	mov	w3, w22
	mov	x2, x21
	mov	x1, x19
	cbnz	w0, .L228
	mov	x0, x20
	bl	PostPro_GetHevcMbGroupOfNoTile
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L228:
	mov	x0, x20
	bl	PostPro_GetHevcMbGroupOfTile
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L227:
	ldr	x1, .LC27
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetHevcMbGroup, .-PostPro_GetHevcMbGroup
	.align	3
.LC27:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetHEVCRepairParam
	.type	PostPro_GetHEVCRepairParam, %function
PostPro_GetHEVCRepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	mov	x22, x2
	mov	w21, w3
	bl	_mcount
	ldr	w0, [x19, 1288]
	mov	w4, 1
	add	x0, x0, 336
	ldr	w0, [x19, x0, lsl 2]
	str	w0, [x20, 8]
	ldr	x0, [x19, 2496]
	ldr	w0, [x0, 372]
	add	x0, x0, 336
	ldr	w0, [x19, x0, lsl 2]
	str	w0, [x20, 20]
	ldr	w0, [x19, 1292]
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 1476]
	str	w0, [x20, 24]
	ldr	w3, [x19, 76]
	str	w3, [x20, 64]
	lsl	w2, w4, w3
	ldrb	w0, [x19]
	strb	w0, [x20]
	ldr	w0, [x19, 196]
	sub	w0, w0, #1
	add	w0, w0, w2
	lsr	w0, w0, w3
	str	w0, [x20, 28]
	ldr	w0, [x19, 192]
	sub	w0, w0, #1
	add	w2, w0, w2
	lsr	w2, w2, w3
	str	w2, [x20, 32]
	ldrb	w0, [x19, 225]
	str	w0, [x20, 68]
	str	w4, [x20, 36]
	ldr	w0, [x19, 12]
	cmp	w0, wzr
	cset	w0, eq
	str	w0, [x20, 40]
	ldr	w0, [x19, 1340]
	cbnz	w0, .L242
	str	wzr, [x22, 12]
.L231:
	ldr	w2, [x20, 8]
	ldr	w0, [x20, 20]
	cmp	w2, w0
	beq	.L243
.L232:
	str	wzr, [x20, 52]
	ldr	w0, [x19, 1296]
	str	w0, [x20, 12]
	ldr	w0, [x19, 1300]
	str	w0, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L243:
	ldr	w3, [x19, 1472]
	cbz	w3, .L232
	ldr	w1, [x19, 1344]
	mov	w0, 0
	cmp	w2, w1
	bne	.L233
	.p2align 2
.L235:
	add	w0, w0, 1
	cmp	w3, w0
	add	x1, x19, x0, sxtw 2
	beq	.L232
	ldr	w1, [x1, 1344]
	cmp	w2, w1
	beq	.L235
.L233:
	str	w1, [x20, 20]
	b	.L232
	.p2align 3
.L242:
	mov	w3, w21
	mov	x2, x19
	mov	x1, x22
	mov	x0, x20
	bl	PostPro_GetHevcMbGroup
	b	.L231
	.size	PostPro_GetHEVCRepairParam, .-PostPro_GetHEVCRepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuv_Vp9
	.type	PostPro_CopyYuv_Vp9, %function
PostPro_CopyYuv_Vp9:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x26, x0
	mov	x0, x30
	mov	w22, w1
	mov	x23, x2
	bl	_mcount
	ldr	x25, .LC28
	sxtw	x0, w22
	add	x21, x26, 270336
	lsl	x20, x0, 3
	mov	w24, 1
	sub	x20, x20, x0
	lsl	x20, x20, 3
	ldr	w1, [x21, 2448]
	sub	x20, x20, x0
	ldr	w2, [x21, 2088]
	lsl	x20, x20, 2
	ldr	w3, [x21, 2092]
	sub	x20, x20, x0
	ldr	w0, [x21, 2456]
	lsl	x20, x20, 3
	ldr	w4, [x21, 2440]
	add	x19, x25, x20
	stp	w1, w0, [x19, 20]
	ldr	x1, .LC30
	mov	w0, 22
	stp	w2, w3, [x19, 28]
	str	w4, [x19, 8]
	stp	w24, wzr, [x19, 36]
	bl	dprint_vfmw
	strh	wzr, [x19, 76]
	ldp	w0, w1, [x19, 28]
	ldr	x2, .LC31
	stp	w24, wzr, [x19, 44]
	mul	w0, w0, w1
	ldr	w1, [x21, 2468]
	strb	w1, [x25, x20]
	sub	w0, w0, #1
	ldrb	w1, [x21, 2081]
	ldr	x5, [x2, 272]
	mov	w2, 6
	strh	w0, [x19, 78]
	strb	w1, [x19, 1]
	stp	wzr, w24, [x19, 52]
	str	w2, [x19, 64]
	cbz	x5, .L246
	mov	x4, x23
	mov	w3, w22
	mov	x1, x26
	mov	w2, 0
	mov	w0, 17
	blr	x5
	cmp	w0, wzr
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L246:
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	PostPro_CopyYuv_Vp9, .-PostPro_CopyYuv_Vp9
	.align	3
.LC28:
	.xword	g_RepairParam
	.align	3
.LC30:
	.xword	.LC29
	.align	3
.LC31:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVp9MbGroup
	.type	PostPro_GetVp9MbGroup, %function
PostPro_GetVp9MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	sub	w0, w0, #1
	cmp	w0, 199
	bhi	.L261
	str	wzr, [x20, 44]
	mov	w6, -1
	str	wzr, [x20, 56]
	mov	w0, 0
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 22]
	strh	w9, [x3, 20]
	b	.L256
	.p2align 3
.L265:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L252
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L252
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L262
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 76]
	strh	w6, [x8, 78]
	str	w5, [x20, 44]
.L252:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L263
.L259:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L264
.L256:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 20]
	ldrh	w3, [x3, 22]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L265
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L256
.L264:
	mov	w0, 0
.L249:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L263:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 22]
	cmp	w4, w10
	bge	.L259
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L266
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 76]
	strh	w9, [x2, 78]
	str	w1, [x20, 44]
	b	.L249
.L261:
	ldr	x1, .LC33
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L262:
	ldr	x1, .LC34
	mov	w2, 794
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L249
.L266:
	ldr	x1, .LC34
	mov	w2, 808
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L249
	.size	PostPro_GetVp9MbGroup, .-PostPro_GetVp9MbGroup
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC34:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVP9RepairParam
	.type	PostPro_GetVP9RepairParam, %function
PostPro_GetVP9RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	add	x3, x20, 270336
	mov	w5, 1
	mov	w4, 6
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x3, 2440]
	str	w2, [x19, 8]
	ldr	w2, [x3, 2448]
	str	w2, [x19, 20]
	ldr	w2, [x3, 2456]
	str	w2, [x19, 24]
	ldr	w2, [x3, 2088]
	str	w2, [x19, 28]
	ldr	w2, [x3, 2092]
	stp	w2, w5, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x3, 2468]
	strb	w2, [x19]
	str	w4, [x19, 64]
	bl	PostPro_GetVp9MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetVP9RepairParam, .-PostPro_GetVP9RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetMp24MbGroup
	.type	PostPro_GetMp24MbGroup, %function
PostPro_GetMp24MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L288
	str	wzr, [x20, 44]
	str	wzr, [x20, 56]
	ldp	w5, w1, [x20, 28]
	ldr	w0, [x19, 12]
	mul	w5, w5, w1
	uxtw	x1, w0
	add	x2, x19, x1, lsl 2
	uxth	w10, w5
	strh	w10, [x2, 22]
	strh	w10, [x2, 20]
	cbnz	w0, .L289
.L271:
	mov	w7, -1
	mov	w0, 0
	mov	w6, w7
	add	w11, w5, w7
	b	.L280
	.p2align 3
.L293:
	cmp	w2, w3
	ccmp	w2, w6, 1, le
	blt	.L272
	cmp	w2, w7
	csel	w7, w7, w6, ge
	add	w4, w7, 1
	cmp	w2, w4
	beq	.L276
	add	w6, w6, w6, lsr 31
	sub	w8, w2, #1
	cmp	w6, w8
	bge	.L276
	ldr	w4, [x20, 44]
	cmp	w4, 199
	bgt	.L290
	add	x9, x20, x4, sxtw 2
	sxth	w6, w6
	cmp	w7, w6
	strh	w6, [x9, 76]
	strh	w8, [x9, 78]
	ble	.L278
	strh	w7, [x9, 76]
.L278:
	add	w4, w4, 1
	str	w4, [x20, 44]
.L276:
	ldr	w4, [x19, 12]
	sub	w6, w4, #1
	cmp	w6, w0
	beq	.L291
.L283:
	add	w0, w0, 1
	mov	w7, w3
	cmp	w0, w4
	mov	w6, w2
	bhi	.L292
.L280:
	uxtw	x1, w0
	add	x2, x19, x1, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 20]
	ldrh	w3, [x3, 22]
	cmp	w5, w2
	ccmp	w5, w3, 1, ge
	bge	.L293
.L272:
	ldr	w4, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w4
	bls	.L280
.L292:
	mov	w0, 0
.L270:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L291:
	add	x1, x19, x1, lsl 2
	ldrh	w1, [x1, 22]
	cmp	w1, w11
	bge	.L283
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L294
	add	x3, x20, x0, sxtw 2
	sub	w10, w10, #1
	add	w2, w0, 1
	mov	w0, 0
	strh	w1, [x3, 76]
	strh	w10, [x3, 78]
	str	w2, [x20, 44]
	b	.L270
	.p2align 3
.L289:
	sub	w0, w0, #1
	sub	w1, w5, #10
	add	x0, x19, x0, lsl 2
	ldrh	w2, [x0, 22]
	cmp	w2, w1
	blt	.L271
	sub	w1, w10, #1
	strh	w1, [x0, 22]
	b	.L271
.L288:
	ldr	x1, .LC35
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L290:
	ldr	x1, .LC36
	mov	w2, 900
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L270
.L294:
	ldr	x1, .LC36
	mov	w2, 926
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L270
	.size	PostPro_GetMp24MbGroup, .-PostPro_GetMp24MbGroup
	.align	3
.LC35:
	.xword	.LC2
	.align	3
.LC36:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetMPEG2RepairParam
	.type	PostPro_GetMPEG2RepairParam, %function
PostPro_GetMPEG2RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 188]
	str	w0, [x19, 8]
	ldr	w0, [x20, 184]
	str	w0, [x19, 20]
	ldr	w0, [x20, 224]
	str	w0, [x19, 24]
	ldrh	w0, [x20, 150]
	str	w0, [x19, 28]
	ldrh	w0, [x20, 146]
	str	w0, [x19, 32]
	ldrb	w0, [x20, 3]
	cmp	w0, 3
	cset	w0, eq
	stp	w0, wzr, [x19, 36]
	ldrb	w0, [x20, 3]
	cmp	w0, 1
	beq	.L299
	cmp	w0, 2
	beq	.L299
	cmp	w0, 3
	beq	.L300
.L297:
	add	x20, x20, 45056
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 240]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetMp24MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L300:
	str	wzr, [x19, 52]
	b	.L297
	.p2align 3
.L299:
	str	w0, [x19, 52]
	b	.L297
	.size	PostPro_GetMPEG2RepairParam, .-PostPro_GetMPEG2RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuv_Mpeg4
	.type	PostPro_CopyYuv_Mpeg4, %function
PostPro_CopyYuv_Mpeg4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	cbz	x19, .L306
	cbnz	w20, .L307
	ldrh	w5, [x19, 176]
	ldrh	w4, [x19, 178]
	ldr	x1, .LC42
	ldr	x6, .LC43
	mul	w3, w5, w4
	ldr	w2, [x19, 240]
	sub	w3, w3, #1
	ldr	w8, [x19, 14672]
	ldr	w7, [x19, 232]
	ldr	w0, [x19, 14588]
	strh	w3, [x1, 78]
	strb	w8, [x1]
	ldr	w3, [x19, 14604]
	ldr	w8, [x19, 14600]
	stp	w2, w5, [x1, 24]
	ldr	x6, [x6, 272]
	ldrb	w2, [x19, 167]
	stp	w0, w8, [x1, 8]
	stp	w3, w7, [x1, 16]
	mov	w0, 1
	mov	w7, 4
	strh	wzr, [x1, 76]
	str	w4, [x1, 32]
	str	wzr, [x1, 40]
	str	wzr, [x1, 52]
	strb	w2, [x1, 1]
	str	w0, [x1, 36]
	str	w0, [x1, 44]
	str	w0, [x1, 56]
	str	w7, [x1, 64]
	cbz	x6, .L303
	mov	x4, x21
	mov	w3, 0
	mov	w2, 0
	mov	x1, x19
	mov	w0, 2
	blr	x6
	cmp	w0, wzr
	cset	w0, ne
.L303:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L307:
	ldr	x2, .LC37
	mov	w3, w20
	ldr	x1, .LC41
	mov	w0, 0
	add	x2, x2, 64
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L306:
	ldr	x2, .LC37
	mov	w0, 0
	ldr	x1, .LC39
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, 1
	b	.L303
	.size	PostPro_CopyYuv_Mpeg4, .-PostPro_CopyYuv_Mpeg4
	.align	3
.LC37:
	.xword	.LANCHOR0
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC42:
	.xword	g_RepairParam
	.align	3
.LC43:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetMPEG4RepairParam
	.type	PostPro_GetMPEG4RepairParam, %function
PostPro_GetMPEG4RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 224]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 232]
	str	w2, [x19, 20]
	ldr	w2, [x20, 240]
	str	w2, [x19, 24]
	ldrh	w2, [x20, 176]
	str	w2, [x19, 28]
	ldrh	w2, [x20, 178]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 14672]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetMp24MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetMPEG4RepairParam, .-PostPro_GetMPEG4RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetAvsMbGroup
	.type	PostPro_GetAvsMbGroup, %function
PostPro_GetAvsMbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L321
	ldp	w3, w1, [x20, 28]
	str	wzr, [x20, 56]
	mov	w6, -1
	mov	x10, x20
	mov	w0, 0
	ldr	w2, [x19, 12]
	mov	w11, 0
	mul	w1, w3, w1
	mov	w9, w6
	add	x16, x20, 876
	add	x3, x19, x2, lsl 2
	add	w15, w1, w6
	add	w12, w1, w1, lsr 31
	uxth	w14, w1
	asr	w12, w12, 1
	add	w13, w12, w6
	strh	w14, [x3, 22]
	strh	w14, [x3, 20]
	b	.L316
	.p2align 3
.L324:
	cmp	w2, w6
	uxth	w5, w11
	csel	w6, w6, w9, ge
	lsr	w7, w9, 31
	add	w6, w6, 1
	mov	w8, w5
	cmp	w2, w6
	sub	w7, w7, w5
	sub	w5, w2, #1
	add	w7, w7, w9
	sub	w5, w5, w8
	mov	w9, w2
	mov	w6, w3
	ble	.L314
	ldr	w8, [x10, 44]
	cmp	w2, w13
	add	w17, w8, 1
	add	x8, x10, x8, sxtw 2
	strh	w7, [x8, 76]
	strh	w5, [x8, 78]
	str	w17, [x10, 44]
	ldr	w5, [x10, 36]
	cbnz	w5, .L314
	csel	x10, x10, x16, lt
	csel	w11, w11, w12, lt
.L314:
	ldr	w5, [x19, 12]
	sub	w7, w5, #1
	cmp	w7, w0
	beq	.L322
.L315:
	add	w0, w0, 1
	cmp	w0, w5
	bhi	.L323
.L316:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 20]
	ldrh	w3, [x3, 22]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L324
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L316
.L323:
	mov	w0, 0
.L311:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L322:
	add	x4, x19, x4, lsl 2
	mov	w9, w2
	mov	w6, w3
	ldrh	w2, [x4, 22]
	cmp	w2, w15
	bge	.L315
	ldr	w1, [x20, 44]
	sub	w14, w14, #1
	mov	w0, 0
	add	w3, w1, 1
	add	x1, x20, x1, sxtw 2
	strh	w2, [x1, 76]
	strh	w14, [x1, 78]
	str	w3, [x20, 44]
	b	.L311
	.p2align 3
.L321:
	ldr	x1, .LC44
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PostPro_GetAvsMbGroup, .-PostPro_GetAvsMbGroup
	.align	3
.LC44:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetAVSRepairParam
	.type	PostPro_GetAVSRepairParam, %function
PostPro_GetAVSRepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w4, [x20, 14464]
	add	x0, x19, 768
	str	w4, [x19, 8]
	ldr	w7, [x20, 14456]
	str	w7, [x19, 20]
	ldr	w2, [x20, 14468]
	str	w2, [x19, 24]
	ldrh	w6, [x20, 72]
	str	w6, [x19, 28]
	ldrh	w1, [x20, 74]
	str	w1, [x19, 32]
	lsr	w8, w1, 1
	ldrb	w3, [x20, 17]
	cmp	w3, 3
	cset	w5, eq
	stp	w5, wzr, [x19, 36]
	ldr	w3, [x21, 4]
	str	w7, [x19, 896]
	add	w4, w3, w4
	str	w4, [x19, 884]
	ldr	w3, [x21, 4]
	stp	w1, w5, [x0, 140]
	add	w3, w3, w3, lsl 3
	madd	w3, w3, w8, w2
	stp	w3, w6, [x0, 132]
	str	wzr, [x19, 916]
	ldrb	w0, [x20, 17]
	cmp	w0, 3
	beq	.L328
	cmp	w0, 1
	beq	.L329
.L327:
	ldr	w1, [x20, 14904]
	mov	w0, 4
	strb	w1, [x19]
	mov	x1, x21
	str	w0, [x19, 64]
	mov	x0, x19
	bl	PostPro_GetAvsMbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L329:
	str	w0, [x19, 52]
	b	.L327
	.p2align 3
.L328:
	str	wzr, [x19, 52]
	b	.L327
	.size	PostPro_GetAVSRepairParam, .-PostPro_GetAVSRepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuv_Vc1
	.type	PostPro_CopyYuv_Vc1, %function
PostPro_CopyYuv_Vc1:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	bl	_mcount
	cbz	x19, .L340
	cbnz	w21, .L341
	ldrh	w1, [x19, 78]
	mov	w2, 16
	sub	w0, w1, #1
	uxth	w0, w0
	cmp	w0, 2047
	bhi	.L342
.L334:
	ldr	w4, [x19, 14608]
	ldr	w3, [x19, 14612]
	ldr	x1, .LC49
	ldr	x5, .LC50
	mul	w0, w4, w3
	strh	wzr, [x1, 76]
	sub	w0, w0, #1
	strh	w0, [x1, 78]
	ldr	w7, [x19, 14440]
	mov	w0, 1
	ldr	w6, [x19, 14448]
	ldr	w8, [x19, 14568]
	stp	w7, w6, [x1, 20]
	stp	w4, w3, [x1, 28]
	str	w8, [x1, 8]
	mov	w7, 4
	ldrb	w3, [x19, 75]
	ldr	w8, [x19, 14516]
	ldr	w4, [x19, 14520]
	ldr	w6, [x19, 14600]
	ldr	x5, [x5, 272]
	stp	w0, wzr, [x1, 36]
	stp	w0, wzr, [x1, 44]
	stp	wzr, w0, [x1, 52]
	str	w2, [x1, 60]
	strb	w3, [x1, 1]
	strb	w6, [x1]
	stp	w8, w4, [x1, 12]
	str	w7, [x1, 64]
	cbz	x5, .L332
	mov	x4, x20
	mov	w3, 0
	mov	w2, 0
	mov	x1, x19
	blr	x5
	cmp	w0, wzr
	cset	w0, ne
.L332:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L342:
	sub	w0, w1, #2049
	mov	w2, 32
	uxth	w0, w0
	cmp	w0, 2047
	bls	.L334
	sub	w1, w1, #4096
	mov	w2, 48
	sub	w0, w1, #1
	uxth	w0, w0
	cmp	w0, 2047
	bls	.L334
	sub	w1, w1, #2049
	mov	w0, 16
	mov	w2, 64
	uxth	w1, w1
	cmp	w1, 2047
	csel	w2, w0, w2, hi
	b	.L334
	.p2align 3
.L341:
	ldr	x2, .LC45
	mov	w3, w21
	ldr	x1, .LC48
	mov	w0, 0
	add	x2, x2, 88
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L340:
	ldr	x2, .LC45
	mov	w0, 0
	ldr	x1, .LC47
	add	x2, x2, 88
	bl	dprint_vfmw
	mov	w0, 1
	b	.L332
	.size	PostPro_CopyYuv_Vc1, .-PostPro_CopyYuv_Vc1
	.align	3
.LC45:
	.xword	.LANCHOR0
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC48:
	.xword	.LC40
	.align	3
.LC49:
	.xword	g_RepairParam
	.align	3
.LC50:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVc1MbGroup
	.type	PostPro_GetVc1MbGroup, %function
PostPro_GetVc1MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	sub	w0, w0, #1
	cmp	w0, 199
	bhi	.L357
	str	wzr, [x20, 44]
	mov	w6, -1
	str	wzr, [x20, 56]
	mov	w0, 0
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 22]
	strh	w9, [x3, 20]
	b	.L352
	.p2align 3
.L361:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L348
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L348
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L358
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 76]
	strh	w6, [x8, 78]
	str	w5, [x20, 44]
.L348:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L359
.L355:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L360
.L352:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 20]
	ldrh	w3, [x3, 22]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L361
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L352
.L360:
	mov	w0, 0
.L345:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L359:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 22]
	cmp	w4, w10
	bge	.L355
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L362
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 76]
	strh	w9, [x2, 78]
	str	w1, [x20, 44]
	b	.L345
.L357:
	ldr	x1, .LC51
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L358:
	ldr	x1, .LC52
	mov	w2, 1363
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L345
.L362:
	ldr	x1, .LC52
	mov	w2, 1379
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L345
	.size	PostPro_GetVc1MbGroup, .-PostPro_GetVc1MbGroup
	.align	3
.LC51:
	.xword	.LC32
	.align	3
.LC52:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVC1RepairParam
	.type	PostPro_GetVC1RepairParam, %function
PostPro_GetVC1RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 14568]
	mov	x1, x21
	str	w0, [x19, 8]
	mov	x0, x19
	ldr	w2, [x20, 14440]
	str	w2, [x19, 20]
	ldr	w2, [x20, 14448]
	str	w2, [x19, 24]
	ldrh	w2, [x20, 82]
	add	w2, w2, 1
	str	w2, [x19, 28]
	ldrh	w2, [x20, 84]
	add	w2, w2, 1
	str	w2, [x19, 32]
	ldrb	w2, [x20, 5]
	and	w2, w2, -3
	uxtb	w2, w2
	cmp	w2, wzr
	cset	w2, eq
	stp	w2, wzr, [x19, 36]
	bl	PostPro_GetVc1MbGroup
	ldrb	w0, [x20, 72]
	ldr	w1, [x19, 36]
	and	w0, w0, 3
	str	w0, [x19, 48]
	cmp	w1, 1
	beq	.L367
	ldrb	w0, [x20, 5]
	cmp	w0, 3
	beq	.L368
.L365:
	mov	w0, 4
	str	w0, [x19, 64]
	ldr	w0, [x20, 14600]
	strb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L368:
	ldrb	w0, [x20, 8]
	cbz	w0, .L369
	cmp	w0, 1
	bne	.L365
	mov	w0, 2
	str	w0, [x19, 52]
	mov	w0, 4
	str	w0, [x19, 64]
	ldr	w0, [x20, 14600]
	strb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L369:
	mov	w0, 1
	str	w0, [x19, 52]
	b	.L365
	.p2align 3
.L367:
	str	wzr, [x19, 52]
	mov	w0, 4
	str	w0, [x19, 64]
	ldr	w0, [x20, 14600]
	strb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetVC1RepairParam, .-PostPro_GetVC1RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetREAL8RepairParam
	.type	PostPro_GetREAL8RepairParam, %function
PostPro_GetREAL8RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 56]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 52]
	str	w2, [x19, 20]
	ldr	w2, [x20, 68]
	str	w2, [x19, 24]
	ldr	w2, [x20, 4]
	str	w2, [x19, 28]
	ldr	w2, [x20, 8]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 76]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetMp24MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetREAL8RepairParam, .-PostPro_GetREAL8RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetREAL9RepairParam
	.type	PostPro_GetREAL9RepairParam, %function
PostPro_GetREAL9RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 52]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 48]
	str	w2, [x19, 20]
	ldr	w2, [x20, 64]
	str	w2, [x19, 24]
	ldr	w2, [x20, 4]
	str	w2, [x19, 28]
	ldr	w2, [x20, 8]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 72]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetMp24MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetREAL9RepairParam, .-PostPro_GetREAL9RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetDivx3MbGroup
	.type	PostPro_GetDivx3MbGroup, %function
PostPro_GetDivx3MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 12]
	sub	w0, w2, #1
	cmp	w0, 3
	bhi	.L384
	ldp	w3, w1, [x20, 28]
	str	wzr, [x20, 56]
	mov	w6, -1
	mov	x10, x20
	mov	w0, 0
	ldr	w2, [x19, 12]
	mov	w11, 0
	mul	w1, w3, w1
	mov	w9, w6
	add	x16, x20, 876
	add	x3, x19, x2, lsl 2
	add	w15, w1, w6
	add	w12, w1, w1, lsr 31
	uxth	w14, w1
	asr	w12, w12, 1
	add	w13, w12, w6
	strh	w14, [x3, 22]
	strh	w14, [x3, 20]
	b	.L379
	.p2align 3
.L387:
	cmp	w2, w6
	uxth	w5, w11
	csel	w6, w6, w9, ge
	lsr	w7, w9, 31
	add	w6, w6, 1
	mov	w8, w5
	cmp	w2, w6
	sub	w7, w7, w5
	sub	w5, w2, #1
	add	w7, w7, w9
	sub	w5, w5, w8
	mov	w9, w2
	mov	w6, w3
	ble	.L377
	ldr	w8, [x10, 44]
	cmp	w2, w13
	add	w17, w8, 1
	add	x8, x10, x8, sxtw 2
	strh	w7, [x8, 76]
	strh	w5, [x8, 78]
	str	w17, [x10, 44]
	ldr	w5, [x10, 36]
	cbnz	w5, .L377
	csel	x10, x10, x16, lt
	csel	w11, w11, w12, lt
.L377:
	ldr	w5, [x19, 12]
	sub	w7, w5, #1
	cmp	w7, w0
	beq	.L385
.L378:
	add	w0, w0, 1
	cmp	w0, w5
	bhi	.L386
.L379:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 20]
	ldrh	w3, [x3, 22]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L387
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L379
.L386:
	mov	w0, 0
.L374:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L385:
	add	x4, x19, x4, lsl 2
	mov	w9, w2
	mov	w6, w3
	ldrh	w2, [x4, 22]
	cmp	w2, w15
	bge	.L378
	ldr	w1, [x20, 44]
	sub	w14, w14, #1
	mov	w0, 0
	add	w3, w1, 1
	add	x1, x20, x1, sxtw 2
	strh	w2, [x1, 76]
	strh	w14, [x1, 78]
	str	w3, [x20, 44]
	b	.L374
	.p2align 3
.L384:
	ldr	x1, .LC53
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PostPro_GetDivx3MbGroup, .-PostPro_GetDivx3MbGroup
	.align	3
.LC53:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetDIVX3RepairParam
	.type	PostPro_GetDIVX3RepairParam, %function
PostPro_GetDIVX3RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 128]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 124]
	str	w2, [x19, 20]
	ldr	w2, [x20, 152]
	str	w2, [x19, 24]
	ldr	w2, [x20, 8]
	str	w2, [x19, 28]
	ldr	w2, [x20, 12]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 160]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetDivx3MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetDIVX3RepairParam, .-PostPro_GetDIVX3RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_CopyYuv_Vp6
	.type	PostPro_CopyYuv_Vp6, %function
PostPro_CopyYuv_Vp6:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	cbz	x19, .L394
	cbnz	w20, .L395
	ldrh	w5, [x19, 106]
	ldrh	w4, [x19, 108]
	ldr	x1, .LC58
	ldr	x6, .LC59
	mul	w3, w5, w4
	ldp	w7, w2, [x19, 236]
	sub	w3, w3, #1
	ldr	w8, [x19, 264]
	ldr	w0, [x19, 228]
	strh	w3, [x1, 78]
	strb	w8, [x1]
	ldr	w3, [x19, 248]
	ldr	w8, [x19, 244]
	stp	w2, w5, [x1, 24]
	ldr	x6, [x6, 272]
	ldrb	w2, [x19, 104]
	stp	w0, w8, [x1, 8]
	stp	w3, w7, [x1, 16]
	mov	w0, 1
	mov	w7, 4
	strh	wzr, [x1, 76]
	str	w4, [x1, 32]
	str	wzr, [x1, 40]
	stp	wzr, wzr, [x1, 48]
	strb	w2, [x1, 1]
	str	w0, [x1, 36]
	str	w0, [x1, 44]
	str	w0, [x1, 56]
	str	w7, [x1, 64]
	cbz	x6, .L391
	mov	x4, x21
	mov	w3, 0
	mov	w2, 0
	mov	x1, x19
	mov	w0, 10
	blr	x6
	cmp	w0, wzr
	cset	w0, ne
.L391:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L395:
	ldr	x2, .LC54
	mov	w3, w20
	ldr	x1, .LC57
	mov	w0, 0
	add	x2, x2, 112
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L394:
	ldr	x2, .LC54
	mov	w0, 0
	ldr	x1, .LC56
	add	x2, x2, 112
	bl	dprint_vfmw
	mov	w0, 1
	b	.L391
	.size	PostPro_CopyYuv_Vp6, .-PostPro_CopyYuv_Vp6
	.align	3
.LC54:
	.xword	.LANCHOR0
	.align	3
.LC56:
	.xword	.LC55
	.align	3
.LC57:
	.xword	.LC40
	.align	3
.LC58:
	.xword	g_RepairParam
	.align	3
.LC59:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVp6MbGroup
	.type	PostPro_GetVp6MbGroup, %function
PostPro_GetVp6MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	sub	w0, w0, #1
	cmp	w0, 199
	bhi	.L410
	str	wzr, [x20, 44]
	mov	w6, -1
	str	wzr, [x20, 56]
	mov	w0, 0
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 22]
	strh	w9, [x3, 20]
	b	.L405
	.p2align 3
.L414:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L401
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L401
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L411
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 76]
	strh	w6, [x8, 78]
	str	w5, [x20, 44]
.L401:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L412
.L408:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L413
.L405:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 20]
	ldrh	w3, [x3, 22]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L414
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L405
.L413:
	mov	w0, 0
.L398:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L412:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 22]
	cmp	w4, w10
	bge	.L408
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L415
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 76]
	strh	w9, [x2, 78]
	str	w1, [x20, 44]
	b	.L398
.L410:
	ldr	x1, .LC60
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L411:
	ldr	x1, .LC61
	mov	w2, 1656
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L398
.L415:
	ldr	x1, .LC61
	mov	w2, 1672
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L398
	.size	PostPro_GetVp6MbGroup, .-PostPro_GetVp6MbGroup
	.align	3
.LC60:
	.xword	.LC32
	.align	3
.LC61:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVP6RepairParam
	.type	PostPro_GetVP6RepairParam, %function
PostPro_GetVP6RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 228]
	mov	w3, 1
	str	w0, [x19, 8]
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 236]
	str	w2, [x19, 20]
	ldr	w2, [x20, 240]
	str	w2, [x19, 24]
	ldrh	w2, [x20, 106]
	str	w2, [x19, 28]
	ldrh	w2, [x20, 108]
	stp	w2, w3, [x19, 32]
	str	wzr, [x19, 40]
	bl	PostPro_GetVp6MbGroup
	stp	wzr, wzr, [x19, 48]
	mov	w1, 4
	ldr	w0, [x20, 264]
	strb	w0, [x19]
	str	w1, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetVP6RepairParam, .-PostPro_GetVP6RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVp8MbGroup
	.type	PostPro_GetVp8MbGroup, %function
PostPro_GetVp8MbGroup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	sub	w0, w0, #1
	cmp	w0, 199
	bhi	.L431
	str	wzr, [x20, 44]
	mov	w6, -1
	str	wzr, [x20, 56]
	mov	w0, 0
	ldp	w1, w3, [x20, 28]
	ldr	w2, [x19, 12]
	mov	w7, w6
	mul	w1, w1, w3
	add	x3, x19, x2, lsl 2
	add	w10, w1, w6
	uxth	w9, w1
	strh	w9, [x3, 22]
	strh	w9, [x3, 20]
	b	.L426
	.p2align 3
.L435:
	cmp	w2, w6
	csel	w6, w6, w7, ge
	add	w6, w6, 1
	cmp	w2, w6
	beq	.L422
	add	w7, w7, w7, lsr 31
	sub	w6, w2, #1
	cmp	w7, w6
	bge	.L422
	ldr	w5, [x20, 44]
	cmp	w5, 199
	bgt	.L432
	add	x8, x20, x5, sxtw 2
	add	w5, w5, 1
	strh	w7, [x8, 76]
	strh	w6, [x8, 78]
	str	w5, [x20, 44]
.L422:
	ldr	w5, [x19, 12]
	sub	w6, w5, #1
	cmp	w6, w0
	beq	.L433
.L429:
	add	w0, w0, 1
	mov	w6, w3
	cmp	w0, w5
	mov	w7, w2
	bhi	.L434
.L426:
	uxtw	x4, w0
	add	x2, x19, x4, lsl 2
	mov	x3, x2
	ldrh	w2, [x2, 20]
	ldrh	w3, [x3, 22]
	cmp	w1, w2
	ccmp	w1, w3, 1, ge
	ccmp	w2, w3, 0, ge
	ble	.L435
	ldr	w5, [x19, 12]
	add	w0, w0, 1
	cmp	w0, w5
	bls	.L426
.L434:
	mov	w0, 0
.L419:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L433:
	add	x4, x19, x4, lsl 2
	ldrh	w4, [x4, 22]
	cmp	w4, w10
	bge	.L429
	ldr	w0, [x20, 44]
	cmp	w0, 199
	bgt	.L436
	add	x2, x20, x0, sxtw 2
	sub	w9, w9, #1
	add	w1, w0, 1
	mov	w0, 0
	strh	w4, [x2, 76]
	strh	w9, [x2, 78]
	str	w1, [x20, 44]
	b	.L419
.L431:
	ldr	x1, .LC62
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L432:
	ldr	x1, .LC63
	mov	w2, 1756
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L419
.L436:
	ldr	x1, .LC63
	mov	w2, 1772
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
	b	.L419
	.size	PostPro_GetVp8MbGroup, .-PostPro_GetVp8MbGroup
	.align	3
.LC62:
	.xword	.LC32
	.align	3
.LC63:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetVP8RepairParam
	.type	PostPro_GetVP8RepairParam, %function
PostPro_GetVP8RepairParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldr	w0, [x20, 3120]
	mov	w4, 1
	str	w0, [x19, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x19
	ldr	w2, [x20, 3132]
	str	w2, [x19, 20]
	ldr	w2, [x20, 3136]
	str	w2, [x19, 24]
	ldr	w2, [x20, 2788]
	str	w2, [x19, 28]
	ldr	w2, [x20, 2792]
	stp	w2, w4, [x19, 32]
	str	wzr, [x19, 40]
	str	wzr, [x19, 52]
	ldr	w2, [x20, 3144]
	strb	w2, [x19]
	str	w3, [x19, 64]
	bl	PostPro_GetVp8MbGroup
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_GetVP8RepairParam, .-PostPro_GetVP8RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_SetDecReport
	.type	PostPro_SetDecReport, %function
PostPro_SetDecReport:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x2
	mov	x21, x1
	bl	_mcount
	ldr	x3, .LC64
	mov	x2, 824
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	cmp	w20, 17
	bls	.L456
.L439:
	ldr	x2, .LC66
	mov	w3, 1976
	ldr	x1, .LC68
	mov	w0, 0
	add	x2, x2, 136
	bl	dprint_vfmw
.L454:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L456:
	ldr	x0, .LC65
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx441
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx441:
	.section	.rodata
	.align	0
	.align	2
.L441:
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L439 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L446 - .Lrtx441) / 4
	.byte	(.L439 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L439 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.byte	(.L450 - .Lrtx441) / 4
	.text
	.p2align 3
.L446:
	ldrb	w0, [x21, 17]
	cmp	w0, 1
	beq	.L457
.L450:
	strh	wzr, [x19, 20]
	mov	w0, 1
	strh	wzr, [x19, 22]
	str	w0, [x19, 12]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L457:
	strh	wzr, [x19, 20]
	mov	w0, 2
	strh	wzr, [x19, 22]
	str	w0, [x19, 12]
	ldrh	w1, [x21, 74]
	ldrh	w0, [x21, 72]
	mul	w0, w0, w1
	add	w0, w0, w0, lsr 31
	asr	w0, w0, 1
	strh	w0, [x19, 24]
	ldrh	w0, [x21, 72]
	ldrh	w1, [x21, 74]
	mul	w0, w0, w1
	add	w0, w0, w0, lsr 31
	asr	w0, w0, 1
	strh	w0, [x19, 26]
	b	.L454
	.size	PostPro_SetDecReport, .-PostPro_SetDecReport
	.align	3
.LC64:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC65:
	.xword	.L441
	.align	3
.LC66:
	.xword	.LANCHOR0
	.align	3
.LC68:
	.xword	.LC67
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetRepairParam
	.type	PostPro_GetRepairParam, %function
PostPro_GetRepairParam:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x26, x1
	mov	w20, w0
	add	x25, x1, 876
	mov	x0, x30
	mov	x19, x2
	mov	x21, x3
	mov	w22, w4
	bl	_mcount
	str	w20, [x26, 4]
	cmp	w20, 17
	str	wzr, [x26, 44]
	str	wzr, [x25, 44]
	bls	.L490
.L459:
	ldr	x2, .LC70
	mov	w3, 2068
	ldr	x1, .LC71
	mov	w0, 0
	bl	dprint_vfmw
	.p2align 2
.L474:
	ldp	w20, w1, [x26, 28]
	ldr	w0, [x26, 44]
	mul	w20, w20, w1
	cbz	w0, .L481
	ldr	x24, .LC73
	mov	w22, 0
	mov	w23, 0
	.p2align 2
.L476:
	add	x19, x26, x23, uxtw 2
	mov	x1, x24
	mov	w0, 22
	add	w23, w23, 1
	ldrsh	w2, [x19, 78]
	ldrsh	w3, [x19, 76]
	bl	dprint_vfmw
	ldrsh	w0, [x19, 78]
	ldrsh	w2, [x19, 76]
	ldr	w1, [x26, 44]
	sub	w0, w0, w2
	cmp	w1, w23
	add	w0, w0, 1
	add	w22, w22, w0
	bhi	.L476
.L475:
	ldr	w0, [x25, 44]
	cbz	w0, .L477
	sub	w0, w0, #1
	mov	x3, 958
	add	x1, x26, 954
	add	x3, x3, x0, uxtw 2
	add	x3, x26, x3
	.p2align 2
.L478:
	ldrsh	w0, [x1]
	add	x1, x1, 4
	ldrsh	w2, [x1, -6]
	cmp	x3, x1
	sub	w0, w0, w2
	add	w0, w0, 1
	add	w22, w22, w0
	bne	.L478
.L477:
	cbz	w20, .L479
	lsl	w19, w22, 2
	mov	w1, 100
	sub	w19, w19, w22
	lsl	w0, w19, 5
	add	w19, w19, w0
	add	w19, w19, w22
	udiv	w19, w19, w20
	cmp	w19, w1
	csel	w19, w19, w1, ls
	cbz	w19, .L479
.L480:
	str	wzr, [x21, 12]
	mov	w3, w22
	ldr	x1, .LC75
	mov	w2, w20
	ldr	w4, [x26, 72]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L479:
	ldr	w0, [x26, 72]
	cmp	w0, 1
	cset	w19, eq
	b	.L480
	.p2align 3
.L490:
	ldr	x0, .LC69
	ldrh	w0, [x0,w20,uxtw #1]
	adr	x1, .Lrtx461
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx461:
	.section	.rodata
	.align	0
	.align	2
.L461:
	.2byte	(.L460 - .Lrtx461) / 4
	.2byte	(.L462 - .Lrtx461) / 4
	.2byte	(.L463 - .Lrtx461) / 4
	.2byte	(.L464 - .Lrtx461) / 4
	.2byte	(.L459 - .Lrtx461) / 4
	.2byte	(.L465 - .Lrtx461) / 4
	.2byte	(.L466 - .Lrtx461) / 4
	.2byte	(.L459 - .Lrtx461) / 4
	.2byte	(.L467 - .Lrtx461) / 4
	.2byte	(.L468 - .Lrtx461) / 4
	.2byte	(.L469 - .Lrtx461) / 4
	.2byte	(.L469 - .Lrtx461) / 4
	.2byte	(.L469 - .Lrtx461) / 4
	.2byte	(.L470 - .Lrtx461) / 4
	.2byte	(.L459 - .Lrtx461) / 4
	.2byte	(.L471 - .Lrtx461) / 4
	.2byte	(.L472 - .Lrtx461) / 4
	.2byte	(.L473 - .Lrtx461) / 4
	.text
.L473:
	add	x19, x19, 270336
	mov	w4, 1
	mov	w3, 6
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 2440]
	str	w2, [x26, 8]
	ldr	w2, [x19, 2448]
	str	w2, [x26, 20]
	ldr	w2, [x19, 2456]
	str	w2, [x26, 24]
	ldr	w2, [x19, 2088]
	str	w2, [x26, 28]
	ldr	w2, [x19, 2092]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 2468]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetVp9MbGroup
	b	.L474
.L460:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetH264RepairParam
	b	.L474
.L462:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetVC1RepairParam
	b	.L474
.L463:
	ldr	w0, [x19, 224]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 232]
	str	w2, [x26, 20]
	ldr	w2, [x19, 240]
	str	w2, [x26, 24]
	ldrh	w2, [x19, 176]
	str	w2, [x26, 28]
	ldrh	w2, [x19, 178]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 14672]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetMp24MbGroup
	b	.L474
.L464:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetMPEG2RepairParam
	b	.L474
.L465:
	ldr	w0, [x19, 128]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 124]
	str	w2, [x26, 20]
	ldr	w2, [x19, 152]
	str	w2, [x26, 24]
	ldr	w2, [x19, 8]
	str	w2, [x26, 28]
	ldr	w2, [x19, 12]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 160]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetDivx3MbGroup
	b	.L474
.L466:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetAVSRepairParam
	b	.L474
.L467:
	ldr	w0, [x19, 56]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 52]
	str	w2, [x26, 20]
	ldr	w2, [x19, 68]
	str	w2, [x26, 24]
	ldr	w2, [x19, 4]
	str	w2, [x26, 28]
	ldr	w2, [x19, 8]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 76]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetMp24MbGroup
	b	.L474
.L468:
	ldr	w0, [x19, 52]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 48]
	str	w2, [x26, 20]
	ldr	w2, [x19, 64]
	str	w2, [x26, 24]
	ldr	w2, [x19, 4]
	str	w2, [x26, 28]
	ldr	w2, [x19, 8]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 72]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetMp24MbGroup
	b	.L474
.L469:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetVP6RepairParam
	b	.L474
.L470:
	ldr	w0, [x19, 3120]
	mov	w4, 1
	str	w0, [x26, 8]
	mov	w3, 4
	mov	x1, x21
	mov	x0, x26
	ldr	w2, [x19, 3132]
	str	w2, [x26, 20]
	ldr	w2, [x19, 3136]
	str	w2, [x26, 24]
	ldr	w2, [x19, 2788]
	str	w2, [x26, 28]
	ldr	w2, [x19, 2792]
	stp	w2, w4, [x26, 32]
	str	wzr, [x26, 40]
	str	wzr, [x26, 52]
	ldr	w2, [x19, 3144]
	strb	w2, [x26]
	str	w3, [x26, 64]
	bl	PostPro_GetVp8MbGroup
	b	.L474
.L471:
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetMVCRepairParam
	b	.L474
.L472:
	mov	w3, w22
	mov	x2, x21
	mov	x1, x19
	mov	x0, x26
	bl	PostPro_GetHEVCRepairParam
	b	.L474
.L481:
	mov	w22, 0
	b	.L475
	.size	PostPro_GetRepairParam, .-PostPro_GetRepairParam
	.align	3
.LC69:
	.xword	.L461
	.align	3
.LC70:
	.xword	.LANCHOR1
	.align	3
.LC71:
	.xword	.LC67
	.align	3
.LC73:
	.xword	.LC72
	.align	3
.LC75:
	.xword	.LC74
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetErrRatio
	.type	PostPro_GetErrRatio, %function
PostPro_GetErrRatio:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L496
	ldr	x3, .LC78
	mov	x2, 24
	ldp	w23, w21, [x19]
	mov	w1, 0
	add	x0, x29, 72
	ldr	x3, [x3, 96]
	ldr	x22, [x19, 8]
	sxtw	x19, w23
	blr	x3
	ldr	x20, .LC80
	lsl	x1, x19, 3
	ldr	x2, .LC81
	sub	x0, x1, x19
	str	w21, [x29, 72]
	lsl	x1, x0, 1
	lsl	x0, x0, 3
	sub	x1, x1, x19
	sub	x0, x0, x19
	lsl	x1, x1, 3
	lsl	x0, x0, 2
	sub	x1, x1, x19
	ldr	x2, [x2, 280]
	sub	x0, x0, x19
	str	w23, [x29, 88]
	ldr	x19, .LC79
	add	x20, x20, x1, lsl 3
	str	x20, [x29, 80]
	add	x19, x19, x0, lsl 3
	cbz	x2, .L494
	add	x0, x29, 72
	blr	x2
.L495:
	mov	w4, w23
	mov	x3, x20
	mov	x2, x22
	mov	x1, x19
	mov	w0, w21
	bl	PostPro_GetRepairParam
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L494:
	ldr	x1, .LC83
	mov	w2, 2140
	mov	w0, 0
	bl	dprint_vfmw
	b	.L495
	.p2align 3
.L496:
	ldr	x1, .LC77
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, 1
	ldp	x29, x30, [sp], 96
	ret
	.size	PostPro_GetErrRatio, .-PostPro_GetErrRatio
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC78:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC79:
	.xword	g_RepairParam
	.align	3
.LC80:
	.xword	g_DecReport
	.align	3
.LC81:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC83:
	.xword	.LC82
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_SetFullRepair
	.type	PostPro_SetFullRepair, %function
PostPro_SetFullRepair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	cbz	x19, .L501
	cbnz	w20, .L502
	ldr	x5, .LC88
	mov	x2, x19
	ldr	x20, .LC89
	mov	w19, 1
	mov	w4, 0
	mov	x3, x5
	mov	x1, x20
	mov	w0, w21
	str	w19, [x5]
	str	wzr, [x5, 12]
	bl	PostPro_GetRepairParam
	str	w19, [x20, 44]
	mov	w0, 100
	str	w19, [x20, 56]
.L499:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L502:
	ldr	x2, .LC84
	mov	w3, w20
	ldr	x1, .LC87
	mov	w0, 0
	add	x2, x2, 24
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L501:
	ldr	x2, .LC84
	mov	w0, 0
	ldr	x1, .LC86
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, 0
	b	.L499
	.size	PostPro_SetFullRepair, .-PostPro_SetFullRepair
	.align	3
.LC84:
	.xword	.LANCHOR1
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC87:
	.xword	.LC40
	.align	3
.LC88:
	.xword	g_DecReport
	.align	3
.LC89:
	.xword	g_RepairParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PostPro_GetRepairStratage
	.type	PostPro_GetRepairStratage, %function
PostPro_GetRepairStratage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L511
	cbnz	w20, .L506
.L507:
	ldrb	w0, [x19, 3]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L506:
	cmp	w20, 15
	beq	.L507
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L511:
	ldr	x2, .LC90
	mov	w0, 0
	ldr	x1, .LC91
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PostPro_GetRepairStratage, .-PostPro_GetRepairStratage
	.align	3
.LC90:
	.xword	.LANCHOR1
	.align	3
.LC91:
	.xword	.LC85
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11036, %object
	.size	__func__.11036, 29
__func__.11036:
	.string	"PostPro_GetHevcMbGroupOfTile"
	.zero	3
	.type	__func__.11072, %object
	.size	__func__.11072, 31
__func__.11072:
	.string	"PostPro_GetHevcMbGroupOfNoTile"
	.zero	1
	.type	__func__.11148, %object
	.size	__func__.11148, 22
__func__.11148:
	.string	"PostPro_CopyYuv_Mpeg4"
	.zero	2
	.type	__func__.11184, %object
	.size	__func__.11184, 20
__func__.11184:
	.string	"PostPro_CopyYuv_Vc1"
	.zero	4
	.type	__func__.11245, %object
	.size	__func__.11245, 20
__func__.11245:
	.string	"PostPro_CopyYuv_Vp6"
	.zero	4
	.type	__func__.11321, %object
	.size	__func__.11321, 21
__func__.11321:
	.string	"PostPro_SetDecReport"
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.11350, %object
	.size	__func__.11350, 23
__func__.11350:
	.string	"PostPro_GetRepairParam"
	.zero	1
	.type	__func__.11375, %object
	.size	__func__.11375, 22
__func__.11375:
	.string	"PostPro_SetFullRepair"
	.zero	2
	.type	__func__.11380, %object
	.size	__func__.11380, 26
__func__.11380:
	.string	"PostPro_GetRepairStratage"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC2:
	ASCII(.string	"DecSliceNum(=%d) out of range!\n" )
.LC4:
	ASCII(.string	"line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_SLICE_NUM - 1)\n" )
	.zero	5
.LC8:
	ASCII(.string	"%s: g_pGlbVar is NULL!\n" )
.LC12:
	ASCII(.string	"NumSlicePara %d out of range[0 %d).\n" )
	.zero	3
.LC14:
	ASCII(.string	"SliceGroup[%d][1] %d out of range[0 %d).\n" )
	.zero	6
.LC16:
	ASCII(.string	"pRepairParam->ValidGroupNum >(MAX_UP_MSG_SLICE_NUM - 1)\n" )
	.zero	7
.LC21:
	ASCII(.string	"%s:call HEVC_CalcTileMap fail!\n" )
.LC23:
	ASCII(.string	"%s:0 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_SLICE_NUM - 1)\n" )
	.zero	5
.LC25:
	ASCII(.string	"%s:1 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_SLICE_NUM - 1)\n" )
	.zero	5
.LC29:
	ASCII(.string	"pRepairParam->ImageWidth=%d,pRepairParam->ImageHeight=%d\n" )
	.zero	6
.LC32:
	ASCII(.string	"DecSliceNum out of range!\n" )
	.zero	5
.LC38:
	ASCII(.string	"%s pMp4DecParam is null\n" )
	.zero	7
.LC40:
	ASCII(.string	"%s VdhId %d invalid!\n" )
	.zero	2
.LC46:
	ASCII(.string	"%s pVc1DecParam is null\n" )
	.zero	7
.LC55:
	ASCII(.string	"%s pVp6DecParam is null\n" )
	.zero	7
.LC67:
	ASCII(.string	"%s %d VidStd Err!\n" )
	.zero	5
.LC72:
	ASCII(.string	"pRepairParam[0].MbGroup[i].EndMbn=%d,pRepairParam[0].MbGroup[i].StartMbn=%d\n" )
	.zero	3
.LC74:
	ASCII(.string	"total_mbs=%d,err_mbs=%d, ErrFrame_Flag: %d\n" )
	.zero	4
.LC76:
	ASCII(.string	"PostPro_GetErrRatio: pParam = NULL\n" )
	.zero	4
.LC82:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC85:
	ASCII(.string	"%s pDecParam is null\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
