#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"pq_mng_db_alg.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	FillBorder_Size8, %function
FillBorder_Size8:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x3
	mov	x21, x0
	mov	x0, x30
	mov	w22, w2
	sxtb	w23, w1
	bl	_mcount
	str	wzr, [x20]
	stp	xzr, xzr, [x29, 64]
	stp	xzr, xzr, [x29, 80]
	cmp	w22, 4096
	bhi	.L1
	sub	w2, w22, #3
	cmp	w2, 4
	bls	.L12
	mov	w0, 4
	b	.L5
	.p2align 3
.L4:
	add	w0, w0, 1
	cmp	w0, w2
	beq	.L19
.L5:
	ldrb	w1, [x21, w0, sxtw]
	cmp	w1, 1
	bne	.L4
	ubfiz	x1, x0, 2, 3
	add	x3, x29, 96
	add	x1, x3, x1
	add	w0, w0, 1
	cmp	w0, w2
	ldr	w3, [x1, -32]
	add	w3, w3, 1
	str	w3, [x1, -32]
	bne	.L5
.L19:
	ldr	w1, [x29, 64]
.L3:
	mov	x0, 0
	mov	w19, 0
	mov	w2, 0
	b	.L11
	.p2align 3
.L7:
	add	x1, x29, 64
	ldr	w1, [x1, x0, lsl 2]
.L11:
	cmp	w2, w1
	bcs	.L6
	mov	w19, w0
	mov	w2, w1
.L6:
	add	x0, x0, 1
	cmp	x0, 8
	bne	.L7
	uxtw	x2, w22
	mov	w1, 0
	mov	x0, x21
	bl	pq_alg_memset
	cbnz	w19, .L20
.L8:
	sub	w0, w23, #1
	add	w0, w0, w19
	cmp	w22, w0
	bls	.L1
	mov	w2, 1
	.p2align 2
.L10:
	strb	w2, [x21, w0, sxtw]
	add	w0, w0, w23
	cmp	w22, w0
	ldr	w1, [x20]
	add	w1, w1, 1
	str	w1, [x20]
	bhi	.L10
.L1:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L20:
	sub	w0, w19, #1
	mov	w1, 1
	strb	w1, [x21, x0]
	ldr	w0, [x20]
	add	w0, w0, 1
	str	w0, [x20]
	b	.L8
.L12:
	mov	w1, 0
	b	.L3
	.size	FillBorder_Size8, .-FillBorder_Size8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	CheckStartEndBorder.part.0, %function
CheckStartEndBorder.part.0:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	sxtb	w21, w1
	mov	x20, x2
	mov	x22, x3
	bl	_mcount
	cmp	w19, wzr
	ble	.L22
	add	w1, w21, w21, lsr 31
	mov	x4, x20
	asr	w1, w1, 1
	mov	w0, 0
	b	.L24
	.p2align 3
.L23:
	add	w0, w0, 1
	add	x4, x4, 1
	cmp	w0, w19
	beq	.L22
.L24:
	ldrb	w2, [x4]
	cmp	w2, 1
	bne	.L23
	cmp	w1, w0
	blt	.L23
	strb	wzr, [x4]
	ldr	w0, [x22]
	sub	w0, w0, #1
	str	w0, [x22]
.L22:
	cmp	w19, 1
	ble	.L21
	add	w21, w21, w21, lsr 31
	mov	w4, 1
	asr	w2, w21, 1
	b	.L27
	.p2align 3
.L26:
	add	w4, w4, 1
	cmp	w19, w4
	beq	.L21
.L27:
	sub	w0, w19, w4
	sxtw	x0, w0
	add	x1, x20, x0
	ldrb	w0, [x20, x0]
	cmp	w0, 1
	bne	.L26
	cmp	w2, w4
	blt	.L26
	strb	wzr, [x1]
	ldr	w0, [x22]
	sub	w0, w0, #1
	str	w0, [x22]
.L21:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	CheckStartEndBorder.part.0, .-CheckStartEndBorder.part.0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	FillBorderHchrVy.constprop.16, %function
FillBorderHchrVy.constprop.16:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w22, w1
	uxtb	w20, w2
	bl	_mcount
	cmp	w22, 4096
	bhi	.L30
	ldr	x0, .LC4
	cmp	w20, 1
	ldr	x3, [x19, 4120]
	add	x1, x0, 16384
	ldr	x23, [x19, 4128]
	ldr	x20, [x0, 20504]
	ldr	x2, [x0, 20512]
	add	x0, x19, 8192
	ldrsb	w21, [x1, 13]
	ldr	x7, [x19, 8648]
	ldr	x4, [x19, 8656]
	add	x19, x0, 488
	ldrsb	w1, [x1, 14]
	beq	.L91
	cmp	w21, 8
	bne	.L92
.L64:
	mov	x3, x19
	mov	w2, w22
	mov	w1, w21
	mov	x0, x20
	bl	FillBorder_Size8
.L34:
	cmp	w22, 4096
	ble	.L93
.L62:
	uxtw	x2, w22
	mov	x1, x20
	mov	x0, x23
	bl	pq_alg_memcpy
.L30:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L92:
	sub	w4, w22, #3
	ldrb	w6, [x0, 476]
	cmp	w4, 4
	str	wzr, [x19]
	bls	.L86
	ldrb	w0, [x20, 4]
	cmp	w0, 1
	beq	.L86
	mov	w2, w4
	mov	w0, 4
	b	.L37
	.p2align 3
.L38:
	ldrb	w1, [x20, w0, sxtw]
	cmp	w1, 1
	beq	.L94
.L37:
	add	w0, w0, 1
	cmp	w0, w4
	bne	.L38
	mov	w10, w4
.L35:
	sub	w0, w10, w21
	mov	w3, 1
	cmp	w0, 4
	ble	.L43
	.p2align 2
.L76:
	strb	w3, [x20, w0, sxtw]
	sub	w0, w0, w21
	cmp	w0, 4
	ldr	w1, [x19]
	add	w1, w1, 1
	str	w1, [x19]
	bgt	.L76
.L43:
	cmp	w4, wzr
	mov	w0, w4
	ble	.L41
	ldrb	w1, [x20, w4, sxtw]
	cmp	w1, 1
	bne	.L45
	b	.L41
	.p2align 3
.L46:
	ldrb	w1, [x20, w0, sxtw]
	cmp	w1, 1
	beq	.L41
.L45:
	subs	w0, w0, #1
	bne	.L46
.L41:
	add	w1, w21, w0
	mov	w5, 1
	cmp	w1, w4
	bcs	.L51
	.p2align 2
.L75:
	strb	w5, [x20, w1, sxtw]
	add	w1, w1, w21
	cmp	w1, w4
	ldr	w3, [x19]
	add	w3, w3, 1
	str	w3, [x19]
	bcc	.L75
.L51:
	cmp	w0, w10
	mov	w5, w10
	mov	w4, 0
	mov	w9, 1
	bcs	.L74
	b	.L49
	.p2align 3
.L54:
	add	w2, w2, 1
	cmp	w0, w2
	mov	w5, w2
	bcc	.L49
.L74:
	ldrb	w1, [x20, w2, sxtw]
	cmp	w1, 1
	bne	.L54
	ldr	w3, [x19]
	cmp	w10, w5
	ccmp	w21, wzr, 4, ne
	add	w3, w3, 1
	str	w3, [x19]
	beq	.L69
	sub	w8, w5, w4
	udiv	w8, w8, w21
	cmp	w8, 1
	bls	.L69
	.p2align 2
.L55:
	add	w4, w4, w21
	add	w1, w1, 1
	cmp	w8, w1
	strb	w9, [x20, w4, uxtw]
	ldr	w3, [x19]
	add	w3, w3, 1
	str	w3, [x19]
	bne	.L55
.L69:
	add	w2, w2, 1
	mov	w4, w5
	cmp	w0, w2
	mov	w5, w2
	bcs	.L74
.L49:
	cmp	w22, 4
	bls	.L34
	add	x1, x20, 4
	sub	w3, w22, #5
	add	x2, x3, 4
	add	x0, x7, 3
	add	x3, x7, x2
	ldrb	w2, [x1]
	cmp	w2, 1
	beq	.L95
	.p2align 2
.L57:
	ldrsb	w2, [x0]
	cmp	w2, wzr
	sub	w2, w2, #1
	ble	.L60
.L87:
	strb	w2, [x0]
.L59:
	add	x0, x0, 1
	add	x1, x1, 1
	cmp	x3, x0
	beq	.L34
	ldrb	w2, [x1]
	cmp	w2, 1
	bne	.L57
.L95:
	strb	wzr, [x1]
	strb	w2, [x1, -1]
	ldrsb	w2, [x0]
	cmp	w2, w6
	add	w2, w2, 1
	blt	.L87
	strb	w6, [x0]
	b	.L59
	.p2align 3
.L91:
	mov	w21, w1
	mov	x7, x4
	cmp	w21, 8
	add	x19, x0, 484
	mov	x23, x3
	mov	x20, x2
	beq	.L64
	b	.L92
	.p2align 3
.L60:
	strb	wzr, [x0]
	b	.L59
	.p2align 3
.L93:
	mov	x3, x19
	mov	x2, x20
	mov	w1, w21
	mov	w0, w22
	bl	CheckStartEndBorder.part.0
	b	.L62
	.p2align 3
.L94:
	mov	w2, w0
	mov	w10, w0
	b	.L35
.L86:
	mov	w10, 4
	mov	w2, w10
	b	.L35
	.size	FillBorderHchrVy.constprop.16, .-FillBorderHchrVy.constprop.16
	.align	3
.LC4:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_GetDbDetInfo
	.type	PQ_MNG_ALG_GetDbDetInfo, %function
PQ_MNG_ALG_GetDbDetInfo:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x2
	mov	x23, x1
	bl	_mcount
	ldr	x20, .LC6
	mov	x2, 20520
	mov	w1, 0
	mov	x0, x20
	bl	pq_alg_memset
	mov	x2, 8808
	mov	x1, x22
	mov	x0, x19
	bl	pq_alg_memcpy
	add	x0, x20, 16384
	ldr	w1, [x22, 48]
	strb	w1, [x0, 12]
	add	w1, w1, 1
	ldr	w2, [x22, 64]
	uxtb	w1, w1
	strb	w2, [x0, 13]
	cmp	w1, 64
	ldr	w1, [x22, 56]
	strb	w1, [x0, 14]
	ldr	w3, [x22, 44]
	str	w3, [x0]
	ldr	w3, [x22, 60]
	str	w3, [x0, 4]
	ldr	w3, [x22, 52]
	str	w3, [x0, 8]
	bls	.L97
	mov	w3, -1
	strb	w3, [x0, 12]
.L97:
	add	w0, w2, 1
	uxtb	w0, w0
	cmp	w0, 64
	bls	.L98
	add	x0, x20, 16384
	mov	w2, -1
	strb	w2, [x0, 13]
.L98:
	add	w0, w1, 1
	uxtb	w0, w0
	cmp	w0, 64
	bls	.L99
	add	x0, x20, 16384
	mov	w1, -1
	strb	w1, [x0, 14]
.L99:
	mov	x2, 16384
	mov	x0, x20
	mov	w1, 0
	bl	pq_alg_memset
	add	x4, x20, 12288
	add	x2, x22, 580
	mov	x0, x20
	add	x4, x4, 3072
	.p2align 2
.L100:
	add	x0, x0, 8
	ldr	w1, [x2], 4
	cmp	x4, x0
	and	w3, w1, 2047
	ubfx	x1, x1, 16, 11
	stp	w3, w1, [x0, -8]
	bne	.L100
	add	x0, x20, 16384
	mov	w1, 0
	mov	x2, 2048
	add	x0, x0, 15
	add	x21, x22, 68
	bl	pq_alg_memset
	ldr	w1, [x22, 68]
	mov	x4, x21
	mov	x5, 0
	.p2align 2
.L101:
	add	x0, x5, 16384
	and	w1, w1, 1
	add	x0, x0, 15
	add	w2, w5, 1
	mov	w3, 1
	strb	w1, [x20, x0]
	b	.L104
	.p2align 3
.L102:
	lsr	w1, w1, w3
	add	w3, w3, 1
	and	w1, w1, 1
	cmp	w3, 32
	strb	w1, [x0, 15]
	add	w2, w2, 1
	beq	.L293
.L104:
	cmp	w2, 2047
	add	x0, x20, x2, uxtw
	add	x0, x0, 16384
	ldr	w1, [x4]
	bls	.L102
.L103:
	add	x0, x20, 16384
	mov	w3, 4096
	add	x2, x0, 15
	add	x1, x0, 1935
	str	x2, [x20, 20496]
	add	x0, x0, 2895
	str	x1, [x20, 20504]
	mov	w2, 2160
	str	x0, [x20, 20512]
	ldp	w21, w1, [x22]
	ldr	w0, [x22, 8]
	cmp	w21, w3
	ccmp	w0, w3, 0, le
	ccmp	w1, w2, 0, le
	bgt	.L106
	sub	w2, w21, #4
	cmp	w2, 3836
	bls	.L294
.L107:
	str	wzr, [x22, 28]
.L108:
	mov	w2, 1080
	cmp	w21, 1920
	ccmp	w1, w2, 0, le
	ble	.L109
	stp	wzr, wzr, [x22, 36]
.L109:
	cmp	w0, 960
	ble	.L110
	str	wzr, [x22, 36]
.L110:
	ldr	w1, [x22, 32]
	cmp	w1, 1
	beq	.L295
.L111:
	mov	w0, -1
	strb	w0, [x23]
.L126:
	ldr	w0, [x22, 36]
	cmp	w0, 1
	beq	.L296
.L174:
	mov	w0, -1
	strb	w0, [x23, 1]
.L189:
	ldr	w0, [x22, 40]
	cmp	w0, 1
	beq	.L297
.L201:
	mov	w0, -1
	strb	w0, [x23, 2]
.L106:
	ldr	w0, [x23, 4]
	str	w0, [x19, 44]
	ldrsb	w0, [x23]
	str	w0, [x19, 48]
	ldr	w0, [x23, 8]
	str	w0, [x19, 52]
	ldrsb	w0, [x23, 2]
	str	w0, [x19, 56]
	ldr	w0, [x23, 12]
	str	w0, [x19, 60]
	ldrsb	w0, [x23, 1]
	str	w0, [x19, 64]
	ldr	w0, [x23, 8672]
	str	w0, [x19, 16]
	ldr	w0, [x23, 8676]
	str	w0, [x19, 20]
	ldr	w0, [x23, 8680]
	str	w0, [x19, 24]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L293:
	add	x5, x5, 32
	ldr	w1, [x4, 4]!
	cmp	x5, 2048
	bne	.L101
	b	.L103
.L294:
	sub	w2, w1, #1
	cmp	w2, 2159
	bls	.L108
	b	.L107
.L295:
	ldr	w1, [x22, 28]
	cmp	w1, 1
	bne	.L111
	cmp	w21, 4096
	ble	.L298
	ldr	w1, [x22, 36]
	cmp	w1, 1
	bne	.L174
	mov	w21, w0
	b	.L228
	.p2align 3
.L297:
	ldr	w0, [x22, 28]
	cmp	w0, 1
	bne	.L201
	b	.L229
	.p2align 3
.L296:
	ldr	w0, [x22, 28]
	cmp	w0, 1
	bne	.L174
	ldr	w21, [x22, 8]
.L228:
	cmp	w21, 4096
	ble	.L299
	ldr	w0, [x22, 40]
	cmp	w0, 1
	bne	.L201
.L229:
	ldr	w21, [x22, 4]
	cmp	w21, 2160
	bgt	.L106
	add	x1, x20, 16384
	add	x0, x23, 4096
	ldr	w3, [x1, 8]
	ldrb	w2, [x0, 44]
	cmp	w3, w2
	bcs	.L203
	mov	w2, -1
	strb	w2, [x1, 14]
.L204:
	add	x1, x20, 16384
	mov	w2, 100
	str	w2, [x1, 8]
.L205:
	ldrb	w4, [x0, 40]
	add	x2, x0, 192
	sub	w1, w4, #1
	sxtb	w1, w1
	cmp	w1, wzr
	ble	.L206
.L207:
	sbfiz	x3, x1, 3, 32
	sub	w1, w1, #1
	sub	x4, x3, #8
	add	x5, x2, x3
	add	x6, x2, x4
	sxtb	w1, w1
	ldrsb	w4, [x2, x4]
	strb	w4, [x2, x3]
	ldr	w3, [x6, 4]
	str	w3, [x5, 4]
	cbnz	w1, .L207
	ldrb	w4, [x0, 40]
.L206:
	add	x3, x20, 16384
	ldrsb	w1, [x3, 14]
	strb	w1, [x0, 192]
	ldr	w1, [x23, 4152]
	ldr	w3, [x3, 8]
	cmp	w1, w4
	str	w3, [x23, 4292]
	bcs	.L208
	add	w1, w1, 1
	str	w1, [x23, 4152]
.L208:
	cmp	w4, w1
	add	x1, x20, 16384
	beq	.L209
	ldrsb	w0, [x23, 2]
	ldrsb	w1, [x1, 14]
.L210:
	cmp	w0, w1
	bne	.L300
	add	w0, w0, 1
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L301
	mov	x0, x23
	mov	w2, 1
	mov	w1, w21
	bl	FillBorderHchrVy.constprop.16
	ldrsb	w0, [x23, 2]
	cmp	w0, 8
	beq	.L218
	add	x25, x23, 8192
	ldrb	w0, [x25, 474]
	ldrb	w1, [x25, 475]
	cmp	w1, w0
	bhi	.L302
	sub	w0, w21, #5
	cmp	w0, 4091
	bhi	.L218
	mov	x0, 5
	mov	w9, 1
.L226:
	sub	x2, x0, #1
	ldr	x4, [x23, 4120]
	ldrb	w8, [x4, x2]
	cmp	w8, 1
	beq	.L303
.L290:
	mov	w1, w0
.L222:
	cmp	w21, w1
	add	x0, x0, 1
	bhi	.L226
	b	.L218
.L299:
	add	x1, x20, 16384
	add	x0, x23, 4096
	ldr	w3, [x1, 4]
	ldrb	w2, [x0, 43]
	cmp	w3, w2
	bcs	.L176
	mov	w2, -1
	strb	w2, [x1, 13]
.L177:
	add	x1, x20, 16384
	mov	w2, 100
	str	w2, [x1, 4]
.L178:
	ldrb	w4, [x0, 40]
	add	x2, x0, 320
	sub	w1, w4, #1
	sxtb	w1, w1
	cmp	w1, wzr
	ble	.L179
.L180:
	sbfiz	x3, x1, 3, 32
	sub	w1, w1, #1
	sub	x4, x3, #8
	add	x5, x2, x3
	add	x6, x2, x4
	sxtb	w1, w1
	ldrsb	w4, [x2, x4]
	strb	w4, [x2, x3]
	ldr	w3, [x6, 4]
	str	w3, [x5, 4]
	cbnz	w1, .L180
	ldrb	w4, [x0, 40]
.L179:
	add	x3, x20, 16384
	ldrsb	w1, [x3, 13]
	strb	w1, [x0, 320]
	ldr	w1, [x23, 4148]
	ldr	w3, [x3, 4]
	cmp	w1, w4
	str	w3, [x23, 4420]
	bcs	.L181
	add	w1, w1, 1
	str	w1, [x23, 4148]
.L181:
	cmp	w4, w1
	add	x1, x20, 16384
	beq	.L182
	ldrsb	w0, [x23, 1]
	ldrsb	w1, [x1, 13]
.L183:
	cmp	w0, w1
	bne	.L304
	add	w0, w0, 1
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L305
	mov	x0, x23
	mov	w2, 2
	mov	w1, w21
	bl	FillBorderHchrVy.constprop.16
	ldrsb	w0, [x23, 1]
	cmp	w0, 8
	beq	.L192
	add	x25, x23, 8192
	ldrb	w0, [x25, 473]
	ldrb	w1, [x25, 475]
	cmp	w1, w0
	bhi	.L306
	sub	w0, w21, #5
	cmp	w0, 4091
	bhi	.L192
	mov	x0, 5
	mov	w9, 1
.L200:
	sub	x2, x0, #1
	ldr	x4, [x23, 4128]
	ldrb	w8, [x4, x2]
	cmp	w8, 1
	beq	.L307
.L289:
	mov	w1, w0
.L196:
	cmp	w21, w1
	add	x0, x0, 1
	bhi	.L200
.L192:
	add	x0, x20, 16384
	ldr	w0, [x0, 4]
	str	w0, [x23, 12]
	b	.L189
.L298:
	add	x1, x20, 16384
	add	x0, x23, 4096
	ldr	w3, [x1]
	ldrb	w2, [x0, 42]
	cmp	w3, w2
	bcs	.L113
	mov	w2, -1
	strb	w2, [x1, 12]
.L114:
	add	x1, x20, 16384
	mov	w2, 100
	str	w2, [x1]
.L115:
	ldrb	w4, [x0, 40]
	add	x2, x0, 64
	sub	w1, w4, #1
	sxtb	w1, w1
	cmp	w1, wzr
	ble	.L116
.L117:
	sbfiz	x3, x1, 3, 32
	sub	w1, w1, #1
	sub	x4, x3, #8
	add	x5, x2, x3
	add	x6, x2, x4
	sxtb	w1, w1
	ldrsb	w4, [x2, x4]
	strb	w4, [x2, x3]
	ldr	w3, [x6, 4]
	str	w3, [x5, 4]
	cbnz	w1, .L117
	ldrb	w4, [x0, 40]
.L116:
	add	x3, x20, 16384
	ldrsb	w1, [x3, 12]
	strb	w1, [x0, 64]
	ldr	w1, [x23, 4144]
	ldr	w3, [x3]
	cmp	w1, w4
	str	w3, [x23, 4164]
	bcs	.L118
	add	w1, w1, 1
	str	w1, [x23, 4144]
.L118:
	cmp	w4, w1
	beq	.L119
	add	x0, x20, 16384
	ldrsb	w24, [x23]
	ldrsb	w1, [x0, 12]
.L120:
	cmp	w24, w1
	bne	.L308
	add	w0, w24, 1
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L309
	add	x25, x23, 8192
	ldr	x26, [x20, 20496]
	cmp	w21, 4096
	add	x27, x25, 480
	ldrb	w9, [x25, 476]
	str	wzr, [x23, 8672]
	bhi	.L128
	cmp	w24, 8
	beq	.L310
	sub	w3, w21, #3
	ldr	x1, [x23, 8640]
	cmp	w3, 4
	bls	.L232
	ldrb	w0, [x26, 4]
	cmp	w0, 1
	beq	.L232
	mov	w0, 4
	b	.L133
	.p2align 3
.L134:
	ldrb	w2, [x26, w0, sxtw]
	cmp	w2, 1
	beq	.L233
.L133:
	add	w0, w0, 1
	cmp	w0, w3
	bne	.L134
.L233:
	mov	w2, w0
.L131:
	sub	w4, w2, w24
	mov	x12, -4
	cmp	w4, 4
	mov	w11, 1
	ble	.L141
.L255:
	add	x6, x12, x4, sxtw 2
	mov	w5, 0
	add	x6, x20, x6
	mov	w8, 0
	mov	w7, 0
.L139:
	ldr	w10, [x6]
	add	x6, x6, 4
	cmp	w10, w8
	bls	.L138
	mov	w5, w7
	mov	w8, w10
.L138:
	add	w7, w7, 1
	cmp	w7, 3
	bne	.L139
	sub	w4, w4, #1
	add	w4, w4, w5
	strb	w11, [x26, w4, sxtw]
	sub	w4, w4, w24
	cmp	w4, 4
	ldr	w5, [x23, 8672]
	add	w5, w5, 1
	str	w5, [x23, 8672]
	bgt	.L255
.L141:
	cmp	w3, wzr
	mov	w5, w3
	ble	.L137
	ldrb	w4, [x26, w3, sxtw]
	cmp	w4, 1
	bne	.L143
	b	.L137
	.p2align 3
.L144:
	ldrb	w4, [x26, w5, sxtw]
	cmp	w4, 1
	beq	.L137
.L143:
	subs	w5, w5, #1
	bne	.L144
.L137:
	add	w4, w5, w24
	mov	x13, -4
	cmp	w4, w3
	mov	w12, 1
	bcs	.L151
.L254:
	add	x7, x13, x4, sxtw 2
	mov	w6, 0
	add	x7, x20, x7
	mov	w10, 0
	mov	w8, 0
.L149:
	ldr	w11, [x7]
	add	x7, x7, 4
	cmp	w11, w10
	bls	.L148
	mov	w6, w8
	mov	w10, w11
.L148:
	add	w8, w8, 1
	cmp	w8, 3
	bne	.L149
	sub	w4, w4, #1
	add	w4, w4, w6
	strb	w12, [x26, w4, sxtw]
	add	w4, w4, w24
	cmp	w4, w3
	ldr	w6, [x23, 8672]
	add	w6, w6, 1
	str	w6, [x23, 8672]
	bcc	.L254
.L151:
	cmp	w5, w2
	mov	w7, w2
	mov	w3, 0
	mov	x13, -4
	mov	w12, 1
	bcs	.L282
	b	.L147
	.p2align 3
.L234:
	mov	w7, w3
.L154:
	add	w0, w0, 1
	cmp	w0, w5
	bhi	.L147
	mov	w3, w7
	mov	w7, w0
.L282:
	ldrb	w6, [x26, w0, sxtw]
	cmp	w6, 1
	bne	.L234
	ldr	w4, [x23, 8672]
	cmp	w24, wzr
	ccmp	w7, w2, 4, ne
	add	w4, w4, 1
	str	w4, [x23, 8672]
	beq	.L154
	sub	w10, w7, w3
	udiv	w10, w10, w24
	cmp	w10, 1
	bls	.L154
.L157:
	add	w3, w24, w3
	mov	w4, 0
	mov	w14, 0
	mov	w11, 0
	add	x8, x13, x3, uxtw 2
	add	x8, x20, x8
.L156:
	ldr	w15, [x8]
	add	x8, x8, 4
	cmp	w15, w14
	bls	.L155
	mov	w4, w11
	mov	w14, w15
.L155:
	add	w11, w11, 1
	cmp	w11, 3
	bne	.L156
	sub	w3, w3, #1
	add	w6, w6, 1
	add	w3, w3, w4
	cmp	w10, w6
	strb	w12, [x26, w3, uxtw]
	ldr	w4, [x23, 8672]
	add	w4, w4, 1
	str	w4, [x23, 8672]
	bne	.L157
	b	.L154
.L303:
	ldr	x1, [x23, 8656]
	ldrb	w5, [x25, 475]
	ldrsb	w3, [x1, x2]
	cmp	w3, w5
	bge	.L290
	sub	x7, x0, #2
	ldrsb	w3, [x1, x0]
	ldrsb	w6, [x1, x7]
	cmp	w5, w6
	bgt	.L224
	cmp	w6, w3
	mov	w1, w0
	blt	.L225
	strb	w8, [x4, x7]
	ldr	x3, [x23, 4120]
	strb	wzr, [x3, x2]
	b	.L222
.L302:
	add	w0, w0, 1
	strb	w0, [x25, 474]
.L218:
	add	x20, x20, 16384
	ldr	w0, [x20, 8]
	str	w0, [x23, 8]
	b	.L106
.L113:
	ldrb	w1, [x1, 12]
	add	w1, w1, 1
	uxtb	w1, w1
	cmp	w1, 1
	bhi	.L115
	b	.L114
.L232:
	mov	w2, 4
	mov	w0, w2
	b	.L131
.L301:
	sxtw	x21, w21
	ldr	x0, [x23, 4120]
	mov	x2, x21
	mov	w1, 0
	bl	pq_alg_memset
	str	wzr, [x23, 8]
	mov	w1, -1
	ldr	x0, [x23, 8656]
	strb	w1, [x23, 2]
	mov	x2, x21
	mov	w1, 0
	bl	pq_alg_memset
	add	x0, x23, 8192
	strb	wzr, [x0, 474]
	str	wzr, [x23, 8676]
	b	.L106
.L300:
	ldr	x0, [x23, 8656]
	sxtw	x2, w21
	mov	w1, 0
	bl	pq_alg_memset
	add	x0, x23, 8192
	strb	wzr, [x0, 474]
	b	.L106
.L209:
	cmp	w4, 1
	ldrsb	w1, [x1, 14]
	ble	.L238
	mov	w3, 1
	mov	w5, w3
	b	.L213
	.p2align 3
.L212:
	cmp	w4, w3
	ble	.L211
.L213:
	ldrsb	w6, [x2, 8]!
	add	w3, w3, 1
	cmp	w6, w1
	sxtb	w3, w3
	bne	.L212
	ldrb	w7, [x0, 63]
	add	w6, w5, 1
	ldr	w8, [x2, 4]
	cmp	w8, w7
	bcc	.L212
	uxtb	w5, w6
	b	.L212
.L203:
	ldrb	w1, [x1, 14]
	add	w1, w1, 1
	uxtb	w1, w1
	cmp	w1, 1
	bhi	.L205
	b	.L204
.L306:
	add	w0, w0, 1
	strb	w0, [x25, 473]
	b	.L192
.L307:
	ldr	x1, [x23, 8648]
	ldrb	w6, [x25, 475]
	ldrsb	w3, [x1, x2]
	cmp	w3, w6
	bge	.L289
	sub	x7, x0, #2
	ldrsb	w3, [x1, x0]
	ldrsb	w5, [x1, x7]
	cmp	w6, w5
	bgt	.L198
	cmp	w5, w3
	mov	w1, w0
	blt	.L199
	strb	w8, [x4, x7]
	ldr	x3, [x23, 4128]
	strb	wzr, [x3, x2]
	b	.L196
.L305:
	sxtw	x21, w21
	ldr	x0, [x23, 4128]
	mov	x2, x21
	mov	w1, 0
	bl	pq_alg_memset
	str	wzr, [x23, 12]
	mov	w1, -1
	ldr	x0, [x23, 8648]
	strb	w1, [x23, 1]
	mov	x2, x21
	mov	w1, 0
	bl	pq_alg_memset
	add	x0, x23, 8192
	strb	wzr, [x0, 473]
	str	wzr, [x23, 8680]
	b	.L189
.L304:
	ldr	x0, [x23, 8648]
	sxtw	x2, w21
	mov	w1, 0
	bl	pq_alg_memset
	add	x0, x23, 8192
	strb	wzr, [x0, 473]
	b	.L189
.L308:
	ldr	x0, [x23, 8640]
	sxtw	x2, w21
	mov	w1, 0
	bl	pq_alg_memset
	add	x0, x23, 8192
	strb	wzr, [x0, 472]
	b	.L126
.L119:
	add	x1, x20, 16384
	cmp	w4, 1
	ldrsb	w1, [x1, 12]
	ble	.L230
	mov	w3, 1
	mov	w5, w3
	b	.L123
	.p2align 3
.L122:
	cmp	w3, w4
	bge	.L121
.L123:
	ldrsb	w6, [x2, 8]!
	add	w3, w3, 1
	cmp	w6, w1
	sxtb	w3, w3
	bne	.L122
	ldrb	w7, [x0, 61]
	add	w6, w5, 1
	ldr	w8, [x2, 4]
	cmp	w8, w7
	bcc	.L122
	uxtb	w5, w6
	b	.L122
.L224:
	mov	w1, w0
.L225:
	cmp	w6, w3
	ccmp	w5, w3, 0, lt
	bgt	.L222
	strb	w9, [x4, x0]
	ldr	x3, [x23, 4120]
	strb	wzr, [x3, x2]
	b	.L222
.L230:
	mov	w5, 1
.L121:
	ldrb	w0, [x0, 60]
	cmp	w0, w5
	bhi	.L311
	add	x0, x20, 16384
	strb	w1, [x23]
	mov	w24, w1
	ldrsb	w1, [x0, 12]
	b	.L120
.L311:
	ldrsb	w24, [x23]
	b	.L120
.L310:
	mov	x3, x27
	mov	w2, w21
	mov	w1, w24
	mov	x0, x26
	bl	FillBorder_Size8
.L130:
	mov	w1, w24
	mov	x3, x27
	mov	x2, x26
	mov	w0, w21
	bl	CheckStartEndBorder.part.0
	ldr	x1, [x20, 20496]
	uxtw	x2, w21
	ldr	x0, [x23, 4112]
	bl	pq_alg_memcpy
	ldrsb	w24, [x23]
.L128:
	cmp	w24, 8
	beq	.L165
	ldrb	w0, [x25, 472]
	ldrb	w1, [x25, 475]
	cmp	w1, w0
	bhi	.L312
	sub	w0, w21, #5
	cmp	w0, 4091
	bhi	.L165
	mov	x0, 5
	mov	w9, 1
.L173:
	sub	x2, x0, #1
	ldr	x4, [x23, 4112]
	ldrb	w8, [x4, x2]
	cmp	w8, 1
	beq	.L313
.L288:
	mov	w1, w0
.L169:
	cmp	w21, w1
	add	x0, x0, 1
	bhi	.L173
.L165:
	add	x0, x20, 16384
	ldr	w0, [x0]
	str	w0, [x23, 4]
	b	.L126
.L309:
	sxtw	x21, w21
	ldr	x0, [x23, 4112]
	mov	x2, x21
	mov	w1, 0
	bl	pq_alg_memset
	str	wzr, [x23, 4]
	mov	w1, -1
	ldr	x0, [x23, 8640]
	strb	w1, [x23]
	mov	x2, x21
	mov	w1, 0
	bl	pq_alg_memset
	add	x0, x23, 8192
	strb	wzr, [x0, 472]
	str	wzr, [x23, 8672]
	b	.L126
.L313:
	ldr	x1, [x23, 8640]
	ldrb	w6, [x25, 475]
	ldrsb	w3, [x1, x2]
	cmp	w3, w6
	bge	.L288
	sub	x7, x0, #2
	ldrsb	w3, [x1, x0]
	ldrsb	w5, [x1, x7]
	cmp	w6, w5
	bgt	.L171
	cmp	w5, w3
	mov	w1, w0
	blt	.L172
	strb	w8, [x4, x7]
	ldr	x3, [x23, 4112]
	strb	wzr, [x3, x2]
	b	.L169
.L312:
	add	w0, w0, 1
	strb	w0, [x25, 472]
	b	.L165
.L171:
	mov	w1, w0
.L172:
	cmp	w6, w3
	ccmp	w5, w3, 0, le
	bge	.L169
	strb	w9, [x4, x0]
	ldr	x3, [x23, 4112]
	strb	wzr, [x3, x2]
	b	.L169
.L238:
	mov	w5, 1
.L211:
	ldrb	w0, [x0, 60]
	cmp	w0, w5
	bhi	.L314
	add	x2, x20, 16384
	strb	w1, [x23, 2]
	mov	w0, w1
	ldrsb	w1, [x2, 14]
	b	.L210
.L182:
	cmp	w4, 1
	ldrsb	w1, [x1, 13]
	ble	.L237
	mov	w3, 1
	mov	w5, w3
	b	.L186
	.p2align 3
.L185:
	cmp	w3, w4
	bge	.L184
.L186:
	ldrsb	w6, [x2, 8]!
	add	w3, w3, 1
	cmp	w6, w1
	sxtb	w3, w3
	bne	.L185
	ldrb	w7, [x0, 62]
	add	w6, w5, 1
	ldr	w8, [x2, 4]
	cmp	w8, w7
	bcc	.L185
	uxtb	w5, w6
	b	.L185
.L147:
	cmp	w21, 4
	bls	.L130
	sub	w2, w21, #5
	add	x0, x1, 3
	add	x2, x2, 4
	add	x2, x1, x2
	add	x1, x26, 4
	b	.L163
	.p2align 3
.L159:
	ldrsb	w3, [x0]
	cmp	w3, wzr
	sub	w3, w3, #1
	ble	.L162
.L287:
	strb	w3, [x0]
.L161:
	add	x0, x0, 1
	add	x1, x1, 1
	cmp	x0, x2
	beq	.L130
.L163:
	ldrb	w3, [x1]
	cmp	w3, 1
	bne	.L159
	strb	wzr, [x1]
	strb	w3, [x1, -1]
	ldrsb	w3, [x0]
	cmp	w3, w9
	add	w3, w3, 1
	blt	.L287
	strb	w9, [x0]
	b	.L161
.L198:
	mov	w1, w0
.L199:
	cmp	w6, w3
	ccmp	w5, w3, 0, le
	bge	.L196
	strb	w9, [x4, x0]
	ldr	x3, [x23, 4128]
	strb	wzr, [x3, x2]
	b	.L196
.L237:
	mov	w5, 1
.L184:
	ldrb	w0, [x0, 60]
	cmp	w0, w5
	bhi	.L315
	add	x2, x20, 16384
	strb	w1, [x23, 1]
	mov	w0, w1
	ldrsb	w1, [x2, 13]
	b	.L183
.L315:
	ldrsb	w0, [x23, 1]
	b	.L183
.L176:
	ldrb	w1, [x1, 13]
	add	w1, w1, 1
	uxtb	w1, w1
	cmp	w1, 1
	bhi	.L178
	b	.L177
.L314:
	ldrsb	w0, [x23, 2]
	b	.L210
.L162:
	strb	wzr, [x0]
	b	.L161
	.size	PQ_MNG_ALG_GetDbDetInfo, .-PQ_MNG_ALG_GetDbDetInfo
	.align	3
.LC6:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_DBCfgDetector
	.type	PQ_MNG_ALG_DBCfgDetector, %function
PQ_MNG_ALG_DBCfgDetector:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x21, x0
	mov	x0, x30
	mov	x20, x2
	bl	_mcount
	ldp	w0, w3, [x19]
	mov	w1, 2160
	cmp	w0, 4096
	ccmp	w3, w1, 0, le
	bgt	.L341
	str	w0, [x21, 636]
	mov	w6, 4096
	ldr	w2, [x19, 4]
	str	w2, [x21, 640]
	ldp	w5, w2, [x19]
	ldr	w4, [x19, 8]
	cmp	w5, w6
	ccmp	w4, w6, 0, le
	ccmp	w2, w1, 0, le
	bgt	.L319
	ldr	w1, [x19, 48]
	cmp	w1, 8
	beq	.L347
	mov	w1, 90
	strh	w1, [x21, 24]
	ldr	w1, [x19, 64]
	cmp	w1, 8
	beq	.L348
.L322:
	mov	w1, 60
	strh	w1, [x21, 26]
.L323:
	ldr	w1, [x19, 56]
	add	w4, w1, 1
	cmp	w4, 1
	bls	.L319
	cmp	w2, wzr
	add	w5, w2, 7
	sdiv	w1, w2, w1
	csel	w5, w5, w2, lt
	asr	w5, w5, 3
	add	w4, w2, 63
	and	w1, w1, 65535
	cmp	w1, w5
	csel	w1, w1, w5, le
	cmp	w2, wzr
	csel	w2, w4, w2, lt
	asr	w2, w2, 6
	cmp	w1, w2
	csel	w1, w1, w2, ge
	strh	w1, [x21, 28]
.L319:
	cmp	w0, 1920
	mov	w1, 1080
	mov	w0, 1
	strh	wzr, [x21, 20]
	strh	w0, [x21, 16]
	ccmp	w3, w1, 0, le
	strh	w0, [x21, 18]
	strh	w0, [x21, 22]
	bgt	.L325
	mov	w0, 6
	strh	w0, [x21, 30]
.L326:
	ldp	w2, w1, [x19]
	mov	w4, 4096
	ldr	w0, [x19, 8]
	cmp	w2, w4
	mov	w3, 2160
	ccmp	w0, w4, 0, le
	ccmp	w1, w3, 0, le
	bgt	.L327
	cmp	w2, 720
	ble	.L349
	cmp	w2, 1920
	bgt	.L330
	mov	w2, 42
	strh	w2, [x21, 32]
.L329:
	cmp	w1, 576
	bgt	.L331
.L353:
	mov	w1, 16
	strh	w1, [x21, 36]
.L332:
	cmp	w0, 360
	ble	.L350
	cmp	w0, 960
	ble	.L351
	mov	w0, 63
	strh	w0, [x21, 34]
.L327:
	add	x19, x21, 40
	mov	x2, 512
	mov	x0, x19
	mov	w1, 0
	add	x20, x20, 16
	bl	pq_alg_memset
	ldr	w0, [x21, 40]
	mov	x4, x19
	mov	x5, 0
	.p2align 2
.L336:
	ldrb	w3, [x20, x5]
	mov	w2, 1
	add	w1, w5, 1
	and	w3, w3, w2
	orr	w3, w3, w0
	str	w3, [x4]
	b	.L339
	.p2align 3
.L337:
	ldrb	w0, [x20, w1, uxtw]
	add	w1, w1, 1
	and	w0, w0, 1
	lsl	w0, w0, w2
	add	w2, w2, 1
	orr	w3, w3, w0
	cmp	w2, 32
	str	w3, [x4]
	beq	.L352
.L339:
	cmp	w1, 2047
	bls	.L337
.L338:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L325:
	mov	w0, 8
	strh	wzr, [x21, 22]
	strh	w0, [x21, 30]
	b	.L326
	.p2align 3
.L352:
	add	x5, x5, 32
	ldr	w0, [x4, 4]!
	cmp	x5, 2048
	bne	.L336
	b	.L338
.L349:
	mov	w2, 16
	cmp	w1, 576
	strh	w2, [x21, 32]
	ble	.L353
.L331:
	cmp	w1, 1080
	bgt	.L333
	mov	w1, 36
	strh	w1, [x21, 36]
	b	.L332
.L347:
	cmp	w5, wzr
	add	w1, w5, 7
	csel	w1, w1, w5, lt
	asr	w1, w1, 3
	strh	w1, [x21, 24]
	ldr	w1, [x19, 64]
	cmp	w1, 8
	bne	.L322
.L348:
	add	w1, w4, 7
	cmp	w4, wzr
	csel	w1, w1, w4, lt
	asr	w1, w1, 3
	strh	w1, [x21, 26]
	b	.L323
.L350:
	mov	w0, 16
	strh	w0, [x21, 34]
	b	.L327
.L341:
	mov	w0, -1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L330:
	mov	w2, 63
	strh	w2, [x21, 32]
	b	.L329
.L351:
	mov	w0, 42
	strh	w0, [x21, 34]
	b	.L327
.L333:
	mov	w1, 63
	strh	w1, [x21, 36]
	b	.L332
	.size	PQ_MNG_ALG_DBCfgDetector, .-PQ_MNG_ALG_DBCfgDetector
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	stDetStaticInfo, %object
	.size	stDetStaticInfo, 20520
stDetStaticInfo:
	.zero	20520
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
