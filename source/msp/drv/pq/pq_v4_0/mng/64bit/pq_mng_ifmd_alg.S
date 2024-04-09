#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"pq_mng_ifmd_alg.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	SearchPhase, %function
SearchPhase:
	stp	x29, x30, [sp, -272]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 120]
	mov	x0, x30
	mov	x19, x3
	mov	x23, x1
	mov	x28, x4
	add	x26, x29, 168
	stp	x2, x3, [x29, 104]
	bl	_mcount
	mov	w24, 0
	add	x0, x19, 428
	ldr	x19, .LC4
	add	x27, x29, 136
	mov	x25, x0
	str	x0, [x29, 96]
	.p2align 2
.L13:
	ldp	x8, x9, [x28]
	ldp	x6, x7, [x28, 16]
	mov	x2, 100
	mov	x1, x19
	add	x0, x29, 168
	ldr	w22, [x28, 28]
	ldp	w21, w20, [x28, 20]
	stp	x8, x9, [x27]
	stp	x6, x7, [x27, 16]
	bl	memcpy
	cmp	w20, w21, lsl 1
	blt	.L7
	mov	x0, 0
	mov	w1, 0
	b	.L5
	.p2align 3
.L21:
	ldr	w2, [x27, x0]
	add	x0, x0, 4
	cmp	w2, w21
	csinc	w1, w1, w1, ne
	cmp	x0, 20
	beq	.L20
.L5:
	ldr	w2, [x26, x0]
	cbz	w2, .L21
	ldr	w2, [x27, x0]
	add	x0, x0, 4
	cmp	w22, w2, lsl 5
	csinc	w1, w1, w1, ge
	cmp	x0, 20
	bne	.L5
.L20:
	cmp	w1, 4
	ble	.L7
	ldr	x0, [x29, 120]
	str	w24, [x0]
	ldr	x0, [x29, 112]
	ldrsb	w0, [x0, 109]
	add	w1, w0, 1
	cmp	w1, w24
	beq	.L8
	add	w1, w24, 4
	cmp	w1, w0
	beq	.L8
.L7:
	ldr	w0, [x23]
	add	w0, w0, 1
	str	w0, [x23]
.L10:
	add	w24, w24, 1
	add	x26, x26, 20
	cmp	w24, 5
	add	x25, x25, 4
	bne	.L13
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 272
	ret
	.p2align 3
.L8:
	ldr	x0, [x29, 104]
	mov	w1, 5
	str	w24, [x0]
	ldr	w0, [x25]
	add	w0, w0, 1
	cmp	w0, 5
	csel	w0, w0, w1, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	str	w0, [x25]
	cmp	w0, 3
	ble	.L10
	ldr	x1, [x29, 96]
	mov	w0, 0
	.p2align 2
.L9:
	cmp	w0, w24
	add	w0, w0, 1
	beq	.L11
	mov	w2, 3
	str	w2, [x1]
.L11:
	cmp	w0, 5
	add	x1, x1, 4
	bne	.L9
	b	.L10
	.size	SearchPhase, .-SearchPhase
	.align	3
.LC4:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	DetectSceneChange.isra.4, %function
DetectSceneChange.isra.4:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w2
	mov	w22, w1
	mov	w19, w3
	bl	_mcount
	add	w3, w22, w21, lsl 1
	ldr	w4, [x20]
	add	w3, w3, w19, lsl 2
	mov	x1, x20
	lsl	w3, w3, 1
	mov	w6, 0
	mov	w2, 0
	mov	w5, w4
	b	.L25
	.p2align 3
.L28:
	ldr	w0, [x1, 4]
	add	w2, w2, 1
	str	w0, [x1]
	cmp	w2, 6
	add	x1, x1, 4
	beq	.L27
.L25:
	ldr	w0, [x1]
	cmp	w4, w0
	add	w6, w6, w0
	csel	w4, w4, w0, le
	cmp	w5, w0
	csel	w5, w5, w0, ge
	cmp	w2, 4
	ble	.L28
	add	w2, w2, 1
	str	w3, [x20, 20]
	cmp	w2, 6
	add	x1, x1, 4
	bne	.L25
.L27:
	sub	w4, w6, w4
	mov	w0, 3392
	sub	w5, w4, w5
	movk	w0, 0x3, lsl 16
	cmp	w5, wzr
	add	w6, w5, 3
	csel	w5, w6, w5, lt
	asr	w5, w5, 2
	lsl	w5, w5, 1
	cmp	w3, w5
	ccmp	w3, w0, 4, gt
	cset	w0, gt
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	DetectSceneChange.isra.4, .-DetectSceneChange.isra.4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	Calc22PLD_4FLD, %function
Calc22PLD_4FLD:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w23, w1
	mov	w24, w4
	mov	w21, w5
	mov	x19, x2
	mov	w22, w3
	bl	_mcount
	cmp	w23, wzr
	ldr	w12, [x20, 28]
	cset	w10, eq
	ldp	w9, w8, [x20, 4]
	ldp	w14, w15, [x20, 12]
	ldp	w0, w4, [x20, 40]
	ldp	w1, w6, [x20, 120]
	ldp	w5, w13, [x20, 128]
	cbnz	w23, .L30
	ldp	w11, w3, [x19, 40]
	mov	w2, w0
	mov	w7, w12
	mov	w0, w4
.L31:
	cmp	w11, w3
	add	w6, w1, w6, lsl 1
	csel	w1, w11, w3, le
	cmp	w3, 80
	lsl	w16, w1, 1
	mov	w1, 80
	ccmp	w7, w1, 0, le
	add	w6, w6, w5, lsl 2
	add	w6, w6, w13, lsl 3
	ble	.L32
	lsl	w15, w7, 2
	lsl	w14, w3, 1
	sub	w4, w15, w7
	cmp	w4, w14
	bgt	.L101
	add	w1, w3, w3, lsl 2
	add	w1, w1, w1, lsr 31
	cmp	w11, w1, asr 1
	bgt	.L35
	cmp	w11, 1000
	ble	.L37
	lsl	w4, w3, 3
	add	w1, w11, w11, lsl 2
	sub	w4, w4, w3
	cmp	w1, w4
	bge	.L35
.L37:
	cmp	w7, 99
	bgt	.L102
	lsl	w5, w7, 3
	cmp	w3, w5
	blt	.L40
	cmp	w7, 10
	mov	w1, 10
	csel	w1, w7, w1, ge
	lsl	w4, w11, 1
	cmp	w4, w1, lsl 3
	bge	.L41
.L40:
	sub	w1, w3, w11
	cmp	w16, 150
	mov	w4, 150
	sxtw	x1, w1
	eor	x17, x1, x1, asr 63
	sub	x17, x17, x1, asr 63
	csel	w1, w16, w4, ge
	add	w1, w1, 50
	cmp	w1, w17
	bge	.L41
	ldr	w1, [x19, 32]
	cmp	w1, 10
	bgt	.L103
.L41:
	cmp	w5, w14
	bge	.L42
	cmp	w5, w11, lsl 1
	bge	.L104
.L43:
	add	w13, w13, 100
	uxtw	x1, w10
	cmp	w15, w13
	add	x1, x19, x1
	ble	.L44
	ldrb	w4, [x1, 88]
	mov	w5, 1
	sub	w4, w4, #15
	strb	w4, [x1, 88]
	b	.L34
	.p2align 3
.L30:
	ldr	w11, [x20, 32]
	mov	w2, w4
	ldr	w7, [x20, 24]
	mov	w3, w12
	stp	w11, w12, [x19, 40]
	b	.L31
	.p2align 3
.L35:
	uxtw	x1, w10
	mov	w5, 1
	add	x1, x19, x1
	ldrb	w4, [x1, 88]
	sub	w4, w4, #1
	strb	w4, [x1, 88]
.L34:
	mul	w21, w24, w21
	asr	w4, w21, 16
	mul	w2, w2, w4
	mul	w0, w0, w4
	asr	w2, w2, 2
	cmp	w2, 400
	asr	w0, w0, 2
	ccmp	w0, 29, 0, gt
	ble	.L63
.L79:
	lsl	w0, w0, 4
	uxtw	x1, w10
	cmp	w0, 127
	ble	.L63
.L84:
	add	x1, x19, x1
	ldrb	w0, [x1, 88]
	sub	w0, w0, #5
	strb	w0, [x1, 88]
.L63:
	cmp	w5, 1
	beq	.L83
.L64:
	mov	w2, 0
.L59:
	ldrsb	w0, [x19, 88]
	mov	w4, 32
	str	w2, [x19, 36]
	cmp	w0, 32
	ldrb	w0, [x19, 88]
	ldrsb	w2, [x19, 89]
	csel	w0, w0, w4, le
	ldrb	w1, [x19, 89]
	sxtb	w5, w0
	cmp	w5, wzr
	csel	w0, w0, wzr, ge
	cmp	w2, 32
	csel	w1, w1, w4, le
	strb	w0, [x19, 88]
	sxtb	w0, w0
	sxtb	w2, w1
	cmp	w2, wzr
	csel	w1, w1, wzr, ge
	cmp	w0, 24
	strb	w1, [x19, 89]
	sxtb	w1, w1
	ccmp	w1, 24, 4, gt
	ble	.L65
	mov	w5, 1
	str	w5, [x19, 92]
.L66:
	ldp	w4, w0, [x19, 8]
	ldr	w2, [x20]
	add	w1, w0, w4
	stp	w4, w0, [x19, 12]
	ldr	w0, [x19, 4]
	str	w0, [x19, 8]
	add	w4, w1, w0
	ldr	w1, [x19]
	stp	w2, w1, [x19]
	mov	w0, 26215
	add	w1, w4, w1
	add	w1, w1, w2
	movk	w0, 0x6666, lsl 16
	ldr	w2, [x19, 28]
	smull	x0, w1, w0
	asr	x0, x0, 33
	sub	w0, w0, w1, asr 31
	add	w1, w0, w2
	ldr	w2, [x19, 20]
	sub	w1, w1, w2
	cmn	w1, #2999
	stp	w0, w1, [x19, 24]
	blt	.L68
	mov	w2, 3000
	str	w0, [x19, 20]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x19, 28]
	cbz	w5, .L81
	cmp	w1, 999
	ble	.L70
	strb	wzr, [x19, 88]
	strb	wzr, [x19, 89]
	str	wzr, [x19, 92]
.L70:
	ldrsb	w1, [x19, 100]
	mov	w2, 100
	ldrb	w0, [x19, 100]
	sub	w8, w8, w9
	cmp	w1, 100
	mov	w1, 34464
	csel	w0, w0, w2, le
	movk	w1, 0x1, lsl 16
	sxtb	w2, w0
	cmp	w2, wzr
	csel	w0, w0, wzr, ge
	cmp	w8, w1
	strb	w0, [x19, 100]
	ble	.L72
	add	w0, w0, 10
	sxtb	w0, w0
	strb	w0, [x19, 100]
.L73:
	cmp	w0, 59
	bgt	.L105
.L75:
	str	w6, [x19, 32]
	mov	w0, 1
	str	w0, [x19, 96]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L32:
	mov	w5, 5499
	cmp	w9, w5
	bgt	.L48
	cmp	w8, wzr
	mov	w4, 20
	csel	w4, w8, w4, ne
	cmp	w9, w4
	bgt	.L48
	cmp	w14, w5
	bgt	.L49
	add	w1, w15, 150
	cmp	w14, w1
	ble	.L50
.L49:
	cbnz	w22, .L50
	.p2align 2
.L48:
	uxtw	x1, w10
	add	x1, x19, x1
	strb	wzr, [x1, 88]
.L52:
	mul	w21, w24, w21
	mov	w5, 1
	asr	w21, w21, 16
	mul	w2, w2, w21
	mul	w0, w0, w21
	asr	w2, w2, 2
	asr	w0, w0, 2
	cmp	w2, 400
	ccmp	w0, 29, 0, gt
	bgt	.L79
.L83:
	ldr	w2, [x19, 36]
	mov	w0, 50
	add	w2, w2, 1
	cmp	w2, w0
	csel	w2, w2, w0, le
	cmp	w2, wzr
	csel	w2, w2, wzr, ge
	b	.L59
	.p2align 3
.L68:
	mov	w1, -3000
	str	w0, [x19, 20]
	str	w1, [x19, 28]
	cbnz	w5, .L70
.L81:
	str	wzr, [x19, 28]
	b	.L70
	.p2align 3
.L72:
	sub	w3, w3, w7
	mov	w1, 20000
	cmp	w3, 1000
	ccmp	w8, w1, 4, gt
	ble	.L74
	add	w0, w0, 6
	sxtb	w0, w0
	strb	w0, [x19, 100]
	cmp	w0, 59
	ble	.L75
.L105:
	str	wzr, [x19, 96]
	str	w6, [x19, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L101:
	uxtw	x1, w10
	mov	w5, 1
	add	x1, x19, x1
	strb	wzr, [x1, 88]
	b	.L34
	.p2align 3
.L65:
	cmp	w1, 19
	ccmp	w0, 19, 4, gt
	bgt	.L106
	mov	w5, 0
	str	wzr, [x19, 92]
	b	.L66
	.p2align 3
.L74:
	sub	w0, w0, #5
	sxtb	w0, w0
	strb	w0, [x19, 100]
	b	.L73
	.p2align 3
.L106:
	ldr	w5, [x19, 92]
	b	.L66
	.p2align 3
.L102:
	uxtw	x1, w10
	cmp	w7, 499
	add	x4, x19, x1
	ldrb	w5, [x4, 88]
	mov	w4, 5
	bgt	.L39
	mov	w4, 34079
	movk	w4, 0x51eb, lsl 16
	smull	x4, w7, w4
	asr	x4, x4, 37
	sub	w4, w4, w7, asr 31
	uxtb	w4, w4
.L39:
	add	x1, x19, x1
	sub	w4, w5, w4
	mov	w5, 1
	strb	w4, [x1, 88]
	b	.L34
	.p2align 3
.L50:
	cmp	w7, 39
	ble	.L51
	cmp	w7, w3, lsl 1
	bge	.L48
.L51:
	cmp	w11, 80
	bgt	.L107
.L53:
	cmp	w8, 1000
	ble	.L55
	lsl	w1, w9, 3
	cmp	w1, w8, lsl 1
	bge	.L56
	cbnz	w22, .L57
	cmp	w15, w14, lsl 1
	ble	.L56
.L57:
	mov	w1, 9000
	cmp	w8, w1
	ble	.L52
	mul	w21, w24, w21
	uxtw	x1, w10
	asr	w4, w21, 16
	mul	w2, w2, w4
	mul	w0, w0, w4
	add	x4, x19, x1
	asr	w2, w2, 2
	cmp	w2, 400
	asr	w0, w0, 2
	ccmp	w0, 29, 0, gt
	ldrb	w2, [x4, 88]
	add	w2, w2, 1
	strb	w2, [x4, 88]
	ble	.L64
	lsl	w0, w0, 4
	cmp	w0, 127
	ble	.L64
	mov	w5, 0
	b	.L84
	.p2align 3
.L104:
	ldr	w1, [x19, 32]
	cmp	w1, 9
	ble	.L43
.L42:
	add	w1, w3, 150
	cmp	w7, w1
	ble	.L108
.L45:
	ldr	w1, [x19, 92]
	cmp	w1, 1
	beq	.L109
	uxtw	x1, w10
	mov	w5, 1
	add	x1, x19, x1
	ldrb	w4, [x1, 88]
	sub	w4, w4, #3
	strb	w4, [x1, 88]
	b	.L34
	.p2align 3
.L108:
	add	w12, w12, 150
	mov	w5, 1
	cmp	w7, w12
	bgt	.L45
	b	.L34
	.p2align 3
.L107:
	sub	w4, w3, w11
	add	w1, w16, 50
	sxtw	x4, w4
	eor	x5, x4, x4, asr 63
	sub	x5, x5, x4, asr 63
	cmp	w1, w5
	bge	.L53
	ldr	w1, [x19, 32]
	cmp	w1, 10
	ble	.L53
	ldr	w4, [x19, 92]
	cmp	w4, 1
	beq	.L61
	mov	w4, 5000
	cmp	w1, w4
	ble	.L52
.L61:
	uxtw	x1, w10
	ldr	w4, [x19, 36]
	add	x1, x19, x1
	mvn	w5, w4
	ldrb	w4, [x1, 88]
	add	w4, w5, w4
	strb	w4, [x1, 88]
	b	.L52
	.p2align 3
.L103:
	uxtw	x1, w10
	mov	w5, 1
	add	x1, x19, x1
	ldrb	w4, [x1, 88]
	sub	w4, w4, #5
	strb	w4, [x1, 88]
	b	.L34
	.p2align 3
.L55:
	uxtw	x1, w10
	add	x1, x19, x1
	ldrb	w4, [x1, 88]
	sub	w4, w4, #1
	strb	w4, [x1, 88]
	b	.L52
	.p2align 3
.L44:
	ldrb	w4, [x1, 88]
	mov	w5, 0
	add	w4, w4, 1
	strb	w4, [x1, 88]
	b	.L34
	.p2align 3
.L109:
	mov	w5, w1
	uxtw	x1, w10
	add	x1, x19, x1
	ldrb	w4, [x1, 88]
	sub	w4, w4, #1
	strb	w4, [x1, 88]
	b	.L34
.L56:
	ldr	w4, [x19, 92]
	cmp	w4, 1
	bne	.L55
	cmp	w1, w8, lsl 2
	ble	.L61
	cbnz	w22, .L62
	lsl	w14, w14, 3
	cmp	w14, w15, lsl 1
	ble	.L61
.L62:
	uxtw	x1, w10
	ldr	w4, [x19, 36]
	add	x1, x19, x1
	mvn	w4, w4
	ldrb	w5, [x1, 88]
	add	w4, w5, w4, lsl 1
	strb	w4, [x1, 88]
	b	.L52
	.size	Calc22PLD_4FLD, .-Calc22PLD_4FLD
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	calc_MCorMA
	.type	calc_MCorMA, %function
calc_MCorMA:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x4
	mov	w22, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	w23, w3
	bl	_mcount
	ldrsb	w1, [x19, 100]
	mov	w0, 100
	ldrb	w5, [x19, 100]
	cmp	w1, 100
	sub	w1, w20, w22
	csel	w5, w5, w0, le
	mov	w0, 34464
	movk	w0, 0x1, lsl 16
	sxtb	w2, w5
	cmp	w2, wzr
	csel	w5, w5, wzr, ge
	cmp	w1, w0
	strb	w5, [x19, 100]
	ble	.L111
	add	w5, w5, 10
	sxtb	w5, w5
	strb	w5, [x19, 100]
.L112:
	cmp	w5, 59
	bgt	.L116
.L114:
	mov	w0, 1
	str	w0, [x19, 96]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L111:
	sub	w21, w21, w23
	mov	w0, 20000
	cmp	w21, 1000
	ccmp	w1, w0, 4, gt
	ble	.L113
	add	w5, w5, 6
	sxtb	w5, w5
	strb	w5, [x19, 100]
	cmp	w5, 59
	ble	.L114
.L116:
	str	wzr, [x19, 96]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L113:
	sub	w5, w5, #5
	sxtb	w5, w5
	strb	w5, [x19, 100]
	b	.L112
	.size	calc_MCorMA, .-calc_MCorMA
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_FmdSet
	.type	PQ_MNG_ALG_FmdSet, %function
PQ_MNG_ALG_FmdSet:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	x25, x2
	bl	_mcount
	ldr	w0, [x20]
	cbz	w0, .L366
	mov	x0, x25
	mov	x2, 28
	mov	w1, 0
	bl	pq_alg_memset
	ldr	w0, [x19, 68]
	cmp	w0, 1
	beq	.L367
	ldrb	w0, [x20, 7]
	add	x27, x20, 7
	cmp	w0, 255
	beq	.L121
	ldrb	w0, [x27, 1]
	cmp	w0, 255
	beq	.L121
	ldrb	w0, [x27, 2]
	cmp	w0, 255
	beq	.L121
	ldrb	w0, [x20, 4]
	add	x26, x20, 4
	cmp	w0, 255
	beq	.L123
.L379:
	ldrb	w0, [x26, 1]
	cmp	w0, 255
	beq	.L123
	ldrb	w0, [x26, 2]
	cmp	w0, 255
	beq	.L123
	ldr	w0, [x19, 48]
	cbz	w0, .L131
.L381:
	add	x21, x20, 16
	ldrb	w0, [x27, 2]
	str	w0, [x21, 8]
	ldr	w0, [x19, 48]
	cbz	w0, .L133
.L382:
	ldrb	w0, [x26, 2]
	str	w0, [x21, 12]
	mov	w0, 2
	ldr	w1, [x19, 48]
	cmp	w1, wzr
	csinc	w0, w0, wzr, eq
	str	w0, [x21, 16]
	ldr	w0, [x19, 48]
	cbz	w0, .L136
.L383:
	ldp	w3, w2, [x19, 60]
.L137:
	ldr	x0, [x21, 8]
	mov	x1, 4294967297
	cmp	x0, xzr
	ccmp	x0, x1, 4, ne
	orr	w0, w3, w2
	cset	w4, ne
	mov	w1, 0
	cbz	w0, .L138
	cmp	w3, 1
	ccmp	w2, 1, 0, eq
	cset	w1, ne
.L138:
	str	w4, [x20, 16]
	add	x0, x20, 162
	str	w1, [x21, 4]
	add	x4, x20, 258
	ldr	w2, [x21, 452]
	ldr	w1, [x21, 456]
	str	w1, [x21, 452]
	str	w2, [x21, 448]
	ldr	w1, [x21, 468]
	ldr	w2, [x19, 52]
	ldr	w3, [x21, 464]
	str	w2, [x21, 456]
	str	w3, [x21, 460]
	str	w1, [x21, 464]
	ldr	w1, [x19, 56]
	str	w1, [x21, 468]
	ldp	w2, w1, [x19, 40]
	mul	w1, w1, w2
	asr	w1, w1, 11
	str	w1, [x20, 488]
	.p2align 2
.L139:
	ldrh	w3, [x0]
	ldrh	w2, [x0, -2]
	strh	w3, [x0, 2]
	strh	w2, [x0], 6
	cmp	x4, x0
	bne	.L139
	add	x2, x19, 236
	add	x0, x20, 160
	add	x4, x20, 256
	mov	w5, 0
	.p2align 2
.L141:
	ldrh	w3, [x0, 4]
	cmp	w1, w3
	ble	.L140
	ldrh	w3, [x0]
	cmp	w1, w3
	ble	.L140
	ldrh	w3, [x0, 2]
	cmp	w1, w3
	csinc	w5, w5, w5, le
.L140:
	ldr	w3, [x2], 4
	strh	w3, [x0], 6
	cmp	x0, x4
	bne	.L141
	ldr	w0, [x19, 20]
	str	w5, [x19, 232]
	cmp	w0, 1
	beq	.L368
	cmp	w0, 2
	beq	.L369
	cmp	w0, 3
	beq	.L370
.L143:
	ldr	w28, [x20, 16]
	mov	w22, 2
.L189:
	add	x5, x20, 136
	ldr	w3, [x19, 216]
	ldp	w1, w2, [x19, 208]
	mov	x0, x5
	str	x5, [x29, 104]
	uxtw	x24, w28
	bl	DetectSceneChange.isra.4
	add	x1, x21, x24
	ldr	x5, [x29, 104]
	strb	w0, [x1, 107]
	cbz	w28, .L281
	ldrsb	w0, [x21, 107]
	cbnz	w0, .L371
.L281:
	mov	w23, 0
	str	wzr, [x29, 104]
.L191:
	ldp	w1, w2, [x19, 208]
	ldr	w3, [x19, 216]
	mov	x0, x5
	bl	DetectSceneChange.isra.4
	add	x4, x21, x24
	strb	w0, [x4, 107]
	ldr	w0, [x19, 24]
	cbz	w0, .L282
	ldr	x0, .LC7
	ldr	w2, [x19, 76]
	ldr	w0, [x0, 16]
	cmp	w0, 1
	add	x0, x19, 84
	beq	.L372
	cmp	w2, 1
	beq	.L373
.L200:
	ldr	w5, [x19, 40]
	cmp	w5, 288
	bgt	.L201
	ldr	w1, [x19, 72]
	cmp	w1, 1
	beq	.L286
.L201:
	ldr	w1, [x21, 448]
	cbz	w1, .L374
.L197:
	ldr	w0, [x19, 28]
	ldr	w28, [x21, 248]
	cbnz	w0, .L375
	ldrsb	w0, [x20, 120]
	ldrsb	w1, [x20, 121]
	cmp	w0, 1
	beq	.L233
	cmp	w0, 2
	bne	.L376
	mov	w2, 0
	mov	w4, 0
.L232:
	cmp	w28, 1
	beq	.L361
	cmp	w2, 1
	mov	w1, 2
	cset	w0, eq
.L234:
	ldr	x5, .LC9
	add	x9, x29, 168
	strb	w1, [x20, 121]
	cmp	w0, 1
	add	x1, x5, 104
	strb	w0, [x20, 120]
	ldr	x2, [x5, 136]
	str	x2, [x29, 200]
	ldp	x2, x3, [x1]
	stp	x2, x3, [x9]
	ldp	x2, x3, [x1, 16]
	add	x1, x29, 184
	ldr	w8, [x19, 8]
	ldr	w7, [x20, 20]
	ldr	w6, [x21, 16]
	stp	x2, x3, [x1]
	beq	.L241
	cmp	w0, 2
	beq	.L242
	cbz	w0, .L243
	stp	wzr, wzr, [x25, 4]
	tbz	x6, 0, .L252
	cmp	w7, wzr
	cset	w1, eq
	str	w1, [x25]
.L253:
	cmp	w0, 2
	str	w22, [x25, 20]
	stp	wzr, w23, [x25, 12]
	beq	.L297
	cmp	w0, 1
	csetm	w1, ne
	mov	w0, w1
.L258:
	cmp	w1, 1
	bls	.L377
.L255:
	str	w0, [x25, 24]
	ldrb	w0, [x27, 1]
	strb	w0, [x20, 7]
	ldrb	w0, [x27, 2]
	strb	w0, [x27, 1]
	ldr	w0, [x19, 20]
	cmp	w0, 1
	beq	.L378
.L256:
	mov	x1, x25
	add	x0, x20, 492
	mov	x2, 28
	bl	pq_alg_memcpy
	ldrb	w0, [x26, 1]
	strb	w0, [x20, 4]
	ldrb	w0, [x26, 2]
	strb	w0, [x26, 1]
	ldr	w0, [x19, 64]
	strb	w0, [x26, 2]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L121:
	ldr	w0, [x19, 60]
	add	x26, x20, 4
	strb	w0, [x20, 7]
	ldr	w0, [x19, 60]
	strb	w0, [x27, 1]
	ldr	w0, [x19, 60]
	strb	w0, [x27, 2]
	ldrb	w0, [x20, 4]
	cmp	w0, 255
	bne	.L379
.L123:
	ldr	w0, [x19, 48]
	cbnz	w0, .L380
	ldrb	w0, [x19, 60]
	strb	w0, [x20, 4]
	ldr	w0, [x19, 48]
	cbz	w0, .L127
.L385:
	ldrb	w0, [x19, 60]
	strb	w0, [x26, 1]
	ldr	w0, [x19, 48]
	cbz	w0, .L129
.L386:
	ldr	w0, [x19, 60]
	cmp	w0, wzr
	cset	w0, eq
	strb	w0, [x26, 2]
.L387:
	ldr	w0, [x19, 48]
	cbnz	w0, .L381
.L131:
	add	x21, x20, 16
	ldrb	w0, [x27, 1]
	str	w0, [x21, 8]
	ldr	w0, [x19, 48]
	cbnz	w0, .L382
.L133:
	ldrb	w0, [x26, 1]
	str	w0, [x21, 12]
	mov	w0, 2
	ldr	w1, [x19, 48]
	cmp	w1, wzr
	csinc	w0, w0, wzr, eq
	str	w0, [x21, 16]
	ldr	w0, [x19, 48]
	cbnz	w0, .L383
.L136:
	ldrb	w2, [x26, 2]
	ldrb	w3, [x27, 2]
	b	.L137
	.p2align 3
.L366:
	stp	wzr, wzr, [x25]
	stp	wzr, wzr, [x25, 8]
	mov	x2, 28
	mov	x1, x25
	ldr	w3, [x19, 60]
	add	x0, x20, 492
	str	w3, [x25, 20]
	ldr	w3, [x20]
	add	w3, w3, 1
	str	w3, [x20]
	bl	pq_alg_memcpy
.L350:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L282:
	mov	w28, 0
.L192:
	ldr	w0, [x19, 28]
	mov	w4, 0
	cbnz	w0, .L384
.L202:
	ldrsb	w0, [x20, 120]
	ldrsb	w1, [x20, 121]
	cmp	w0, 1
	beq	.L233
	cmp	w0, 2
	mov	w2, 0
	beq	.L232
.L239:
	cmp	w28, 1
	beq	.L296
.L361:
	sxtb	w1, w1
	b	.L234
	.p2align 3
.L380:
	ldr	w0, [x19, 60]
	cmp	w0, wzr
	cset	w0, eq
	strb	w0, [x20, 4]
	ldr	w0, [x19, 48]
	cbnz	w0, .L385
.L127:
	ldr	w0, [x19, 60]
	cmp	w0, wzr
	cset	w0, eq
	strb	w0, [x26, 1]
	ldr	w0, [x19, 48]
	cbnz	w0, .L386
.L129:
	ldrb	w0, [x19, 60]
	strb	w0, [x26, 2]
	b	.L387
	.p2align 3
.L371:
	ldrsb	w0, [x21, 108]
	cbz	w0, .L281
	mov	w23, 1
	str	w23, [x29, 104]
	b	.L191
.L373:
	ldr	x3, .LC8
	ldr	w1, [x19, 80]
	ldr	w4, [x3]
	cmp	w1, w4
	bcc	.L200
	ldr	w3, [x3, 4]
	cmp	w1, w3
	bcs	.L200
	mov	w28, w2
	b	.L192
	.p2align 3
.L378:
	ldr	w0, [x25, 20]
	cmp	w0, 2
	beq	.L256
	strb	w0, [x27, 2]
	b	.L256
	.p2align 3
.L368:
	ldr	w0, [x21, 448]
	cbnz	w0, .L143
	ldr	w22, [x19, 8]
	cmp	w22, 2
	beq	.L388
	cmp	w22, 1
	beq	.L389
.L146:
	ldr	w28, [x20, 16]
	cbz	w28, .L358
	ldr	w2, [x20, 24]
	add	x1, x19, 220
	ldr	w4, [x19, 220]
	cmp	w2, 1
	ldr	w3, [x1, 4]
	beq	.L390
	ldr	w6, [x1, 8]
.L151:
	ldp	w1, w2, [x19, 40]
	ldr	x8, .LC7
	mul	w1, w1, w2
	ldr	w7, [x8]
	asr	w2, w1, 9
	str	w7, [x8, 12]
	cmp	w2, wzr
	add	w1, w2, 31
	csel	w1, w1, w2, lt
	mov	w2, 16
	sub	w5, w2, w5
	asr	w1, w1, 5
	stp	w7, w7, [x8, 4]
	mul	w1, w1, w5
	mov	w5, 6
	cmp	w1, wzr
	add	w2, w1, 15
	csel	w1, w2, w1, lt
	asr	w2, w1, 4
	lsl	w1, w2, 2
	sub	w1, w1, w2
	add	w1, w1, w1, lsr 31
	asr	w1, w1, 1
	cmp	w1, 5
	csel	w1, w1, w5, gt
	sub	w5, w4, w3
	cmp	w3, w4
	sdiv	w5, w5, w1
	csel	w9, w3, w4, le
	csel	w10, w3, w4, ge
	cmp	w5, wzr
	ble	.L153
	cmp	w3, 254
	mov	w2, 50
	ble	.L154
	mov	w2, 26215
	movk	w2, 0x6666, lsl 16
	smull	x2, w3, w2
	asr	x2, x2, 33
	sub	w2, w2, w3, asr 31
.L154:
	add	w2, w2, w3
	cmp	w2, w4
	bge	.L155
	mov	w2, 1
	str	w2, [x8]
.L156:
	cmp	w10, 100
	ble	.L357
	sub	w8, w10, w9
	mov	w1, 0
	lsl	w11, w8, 2
	sub	w11, w11, w8
	lsl	w12, w11, 5
	add	w11, w11, w12
	add	w8, w11, w8
	sdiv	w8, w8, w10
	cmp	w8, 19
	ble	.L159
.L357:
	cmn	w5, #500
	mov	w1, -500
	csel	w1, w5, w1, ge
	mov	w5, 500
	cmp	w1, 500
	csel	w1, w1, w5, le
.L159:
	cmp	w7, w2
	add	x2, x29, 168
	csel	w1, w1, wzr, eq
	cmp	w6, w3
	csel	w5, w6, w3, ge
	str	xzr, [x29, 184]
	stp	xzr, xzr, [x2]
	cmp	w5, 254
	mov	w2, 50
	ble	.L162
	mov	w7, 26215
	movk	w7, 0x6666, lsl 16
	smull	x7, w5, w7
	asr	x7, x7, 33
	sub	w2, w7, w5, asr 31
.L162:
	add	w2, w5, w2
	cmp	w2, w4
	mov	w2, 0
	bge	.L163
	mov	w2, 1
	str	w2, [x29, 168]
.L163:
	cmp	w6, w4
	mov	w7, 50
	csel	w5, w6, w4, ge
	cmp	w5, 254
	ble	.L164
	mov	w8, 26215
	movk	w8, 0x6666, lsl 16
	smull	x8, w5, w8
	asr	x8, x8, 33
	sub	w7, w8, w5, asr 31
.L164:
	add	w7, w5, w7
	cmp	w7, w3
	bge	.L165
	mov	w5, 1
	str	w5, [x29, 172]
.L165:
	cmp	w10, 254
	mov	w5, 50
	ble	.L166
	mov	w7, 26215
	movk	w7, 0x6666, lsl 16
	smull	x7, w10, w7
	asr	x7, x7, 33
	sub	w5, w7, w10, asr 31
.L166:
	add	w5, w10, w5
	cmp	w5, w6
	bge	.L167
	mov	w5, 1
	str	w5, [x29, 176]
.L167:
	cmp	w6, w3
	mov	w5, 50
	csel	w7, w6, w3, le
	cmp	w7, 254
	ble	.L168
	mov	w5, 26215
	movk	w5, 0x6666, lsl 16
	smull	x5, w7, w5
	asr	x5, x5, 33
	sub	w5, w5, w7, asr 31
.L168:
	sub	w5, w7, w5
	cmp	w5, w4
	ble	.L169
	mov	w5, 1
	str	w5, [x29, 180]
.L169:
	cmp	w6, w4
	mov	w5, 50
	csel	w7, w6, w4, le
	cmp	w7, 254
	ble	.L170
	mov	w5, 26215
	movk	w5, 0x6666, lsl 16
	smull	x5, w7, w5
	asr	x5, x5, 33
	sub	w5, w5, w7, asr 31
.L170:
	sub	w5, w7, w5
	cmp	w5, w3
	ble	.L171
	mov	w5, 1
	str	w5, [x29, 184]
.L171:
	cmp	w9, 254
	mov	w5, 50
	ble	.L172
	mov	w5, 26215
	movk	w5, 0x6666, lsl 16
	smull	x5, w9, w5
	asr	x5, x5, 33
	sub	w5, w5, w9, asr 31
.L172:
	sub	w5, w9, w5
	cmp	w5, w6
	ble	.L173
	mov	w0, 1
	str	w0, [x29, 188]
.L173:
	cbz	w2, .L174
	ldr	w5, [x29, 184]
	cbnz	w5, .L174
	sxtw	x7, w1
	eor	x5, x7, x7, asr 63
	sub	x5, x5, x7, asr 63
	cmp	w5, 20
	ble	.L175
	cmp	w1, 50
	mov	w5, 50
	csel	w1, w1, w5, ge
.L175:
	cbnz	w0, .L176
	ldr	w0, [x29, 176]
	cbnz	w0, .L275
	ldr	w5, [x29, 184]
	cmp	w5, wzr
	ccmp	w2, wzr, 4, ne
	bne	.L176
	ldr	w0, [x29, 180]
	cbnz	w0, .L391
.L177:
	cmp	w4, wzr
	ccmp	w3, wzr, 4, ne
	beq	.L176
	orr	w0, w5, w0
	cmp	w0, wzr
	csel	w1, w1, wzr, eq
.L176:
	mov	x0, 0
	mov	w3, 0
	b	.L179
.L392:
	add	x2, x29, 168
	ldr	w2, [x2, x0]
.L179:
	add	x0, x0, 4
	add	w3, w3, w2
	cmp	x0, 24
	bne	.L392
	cbnz	w3, .L180
	cmp	w1, 50
	mov	w0, 50
	csel	w1, w1, w0, le
	mov	w0, -50
	cmp	w1, w0
	csel	w1, w1, w0, ge
.L180:
	add	w0, w1, 49
	cmp	w0, 98
	bls	.L277
	cmp	w1, 99
	cset	w0, le
.L181:
	cmp	w6, 1
	cset	w2, le
	tst	w0, w2
	ldr	w0, [x20, 128]
	csel	w1, w1, wzr, eq
	add	w1, w1, w0
	str	w1, [x20, 128]
	cmp	w1, 1000
	ble	.L183
	mov	w0, 1000
	str	w0, [x20, 128]
.L184:
	mov	w22, 0
	str	wzr, [x20, 132]
	b	.L189
.L293:
	cmp	w2, 1
	beq	.L361
	.p2align 2
.L233:
	cmp	w28, 1
	beq	.L235
	strb	wzr, [x20, 120]
	mov	w0, 1
	strb	w0, [x20, 121]
	ldr	w7, [x20, 20]
	ldr	w6, [x21, 16]
.L243:
	stp	wzr, wzr, [x25, 4]
	tbz	x6, 0, .L244
	cmp	w7, wzr
	cset	w0, eq
	str	w0, [x25]
.L245:
	mov	w1, -1
	str	wzr, [x25, 12]
	mov	w0, w1
	stp	w23, w22, [x25, 16]
	b	.L258
.L296:
	mov	w28, 0
.L235:
	mov	w0, 2
	strb	w28, [x20, 121]
	strb	w0, [x20, 120]
	ldr	x5, .LC9
	ldr	w7, [x20, 20]
	ldr	w6, [x21, 16]
.L242:
	mov	w0, 1
	stp	w0, w0, [x25, 4]
	tbz	x6, 0, .L249
	cmp	w7, wzr
	cset	w0, eq
	str	w0, [x25]
.L250:
	mov	w0, 1
	str	w22, [x25, 20]
	stp	w0, w23, [x25, 12]
.L251:
	add	x0, x5, x0, sxtw 2
	ldr	w0, [x0, 144]
	b	.L255
.L384:
	ldr	w8, [x21, 448]
	ldr	w5, [x21, 16]
	cbnz	w8, .L203
	ldr	w0, [x21, 460]
	cmp	w0, 1
	bgt	.L393
	ldr	x2, [x21, 96]
	mov	w1, -1
	stp	wzr, w1, [x29, 156]
	str	w1, [x29, 164]
	ldr	w3, [x19, 208]
	ldr	w0, [x19, 216]
	ldr	w1, [x19, 212]
	cbz	x2, .L209
	add	w1, w3, w1, lsl 1
	add	x11, x20, 100
	add	w0, w1, w0, lsl 2
	add	x10, x20, 40
	lsl	w0, w0, 1
	str	w0, [x2]
	ldr	x0, [x21, 96]
	ldr	w13, [x21, 20]
	add	x0, x0, 4
	cmp	x0, x11
	add	w1, w13, 1
	csel	x0, x0, x10, ls
	str	w1, [x21, 20]
	str	x0, [x21, 96]
	cbz	x0, .L209
	cmp	w1, 4
	bgt	.L394
.L209:
	ldr	w0, [x21, 404]
	mov	w2, 0
	strb	wzr, [x21, 364]
	mov	w8, 0
	strb	wzr, [x21, 365]
	cmp	w0, 1
	str	wzr, [x21, 356]
	mov	w0, -1
	strb	w0, [x21, 109]
	mov	w0, 0
	ldrsb	w4, [x20, 382]
	ldr	w6, [x20, 376]
	beq	.L206
.L207:
	add	x3, x20, 396
	ldr	x9, [x20, 408]
	add	x1, x20, 420
	ldr	x10, [x3]
	str	x10, [x20, 384]
	ldr	w10, [x20, 404]
	str	w10, [x20, 392]
	str	x9, [x3]
	ldr	w9, [x20, 416]
	str	w9, [x20, 404]
	ldr	x3, [x1]
	str	x3, [x20, 408]
	ldr	w3, [x20, 428]
	str	w3, [x20, 416]
	ldr	x3, [x20, 432]
	str	x3, [x1]
	str	w8, [x20, 432]
	ldr	w3, [x20, 440]
	str	w3, [x20, 428]
	strb	w0, [x20, 440]
	strb	w2, [x20, 441]
	strb	w4, [x20, 442]
	str	w6, [x20, 436]
.L203:
	ldr	w0, [x21, 456]
	cbz	w0, .L226
	ldr	w0, [x21, 452]
	cbz	w0, .L227
	sub	w0, w5, #2
	sxtw	x1, w0
	lsl	x0, x1, 2
	sub	x0, x0, x1
.L360:
	lsl	x0, x0, 2
	add	x0, x0, 368
	add	x1, x21, x0
	ldr	w2, [x21, x0]
	ldrsb	w0, [x20, 120]
	ldrsb	w4, [x1, 10]
	cmp	w0, 1
	ldrsb	w1, [x20, 121]
	beq	.L293
	cmp	w0, 2
	beq	.L232
	cmp	w2, 1
	bne	.L239
	ldr	x5, .LC9
	strb	w2, [x20, 120]
	add	x0, x5, 104
	strb	wzr, [x20, 121]
	ldr	x1, [x5, 136]
	str	x1, [x29, 200]
	add	x1, x29, 168
	ldp	x2, x3, [x0]
	ldr	w8, [x19, 8]
	stp	x2, x3, [x1]
	add	x2, x29, 184
	ldp	x0, x1, [x0, 16]
	stp	x0, x1, [x2]
.L241:
	mov	w0, 1
	stp	w0, wzr, [x25, 4]
	cbnz	w8, .L247
	add	w4, w4, w0
.L362:
	mov	w0, 26215
	movk	w0, 0x6666, lsl 16
	smull	x0, w4, w0
	asr	x0, x0, 34
	sub	w0, w0, w4, asr 31
	lsl	w1, w0, 3
	add	w0, w1, w0, lsl 1
	add	x1, x29, 208
	sub	w0, w4, w0
	add	x0, x1, x0, sxtw 2
	ldr	w0, [x0, -40]
	str	w0, [x25]
.L248:
	mov	w1, 0
	mov	w0, 0
	str	wzr, [x25, 12]
	stp	w23, w22, [x25, 16]
	b	.L258
.L369:
	mov	w22, 0
	ldr	w28, [x20, 16]
	b	.L189
.L372:
	cmp	w2, 1
	ldr	w1, [x19, 72]
	beq	.L395
.L195:
	cmp	w1, 1
	beq	.L286
.L196:
	ldr	w1, [x21, 448]
	cbnz	w1, .L197
	ldr	w3, [x19, 8]
	mov	w1, w28
	ldp	w5, w4, [x19, 40]
.L359:
	ldr	w2, [x20, 260]
	add	x28, x20, 268
	str	w2, [x20, 256]
	ldr	w2, [x20, 264]
	str	w2, [x20, 260]
	mov	x2, x28
	bl	Calc22PLD_4FLD
	ldr	w28, [x20, 360]
	str	w28, [x20, 264]
	b	.L192
.L249:
	str	w7, [x25]
	b	.L250
.L247:
	cmp	w8, 1
	bne	.L248
	add	w4, w4, 2
	b	.L362
.L244:
	str	w7, [x25]
	b	.L245
.L252:
	str	w7, [x25]
	b	.L253
.L367:
	mov	x2, 28
	add	x1, x20, 492
	mov	x0, x25
	bl	pq_alg_memcpy
	b	.L350
.L370:
	mov	w22, 1
	ldr	w28, [x20, 16]
	b	.L189
.L226:
	ldr	w0, [x21, 452]
	cbnz	w0, .L227
	sxtw	x5, w5
	lsl	x0, x5, 2
	sub	x0, x0, x5
	b	.L360
.L393:
	mov	x2, 60
	add	x0, x20, 384
	mov	w1, 0
	bl	pq_alg_memset
	ldrsb	w4, [x20, 394]
	mov	x2, 20
	mov	w1, 0
	add	x0, x20, 444
	str	w4, [x29, 104]
	bl	pq_alg_memset
	ldr	w4, [x29, 104]
	b	.L202
.L286:
	mov	w28, w1
	b	.L192
.L377:
	ldr	x5, .LC9
	b	.L251
.L374:
	mov	w1, w28
	ldr	w3, [x19, 8]
	ldr	w4, [x19, 44]
	b	.L359
.L227:
	sub	w0, w5, #1
	sxtw	x1, w0
	lsl	x0, x1, 2
	sub	x0, x0, x1
	b	.L360
.L375:
	ldr	w5, [x21, 16]
	b	.L203
.L395:
	cbnz	w1, .L195
	ldr	x3, .LC8
	ldr	w1, [x19, 80]
	ldr	w4, [x3]
	cmp	w1, w4
	bcc	.L196
	ldr	w3, [x3, 4]
	cmp	w1, w3
	bcs	.L196
	mov	w28, w2
	b	.L192
.L297:
	mov	w0, 22
	b	.L255
.L376:
	mov	w4, 0
	b	.L239
.L174:
	ldr	w5, [x29, 172]
	cbz	w5, .L175
	ldr	w5, [x29, 180]
	cbnz	w5, .L175
	sxtw	x7, w1
	eor	x5, x7, x7, asr 63
	sub	x5, x5, x7, asr 63
	cmp	w5, 20
	ble	.L175
	cmn	w1, #50
	mov	w5, -50
	csel	w1, w1, w5, le
	b	.L175
.L155:
	mov	w2, 0
	str	wzr, [x8]
	b	.L156
.L277:
	mov	w0, 1
	mov	w1, 0
	b	.L181
.L394:
	ldr	x6, [x21, 88]
	add	x9, x29, 208
	mov	w3, 0
	mov	w12, 0
	mov	x0, x6
	ldr	w7, [x6]
	str	w7, [x9, -40]!
	mov	w2, w7
	mov	w1, w7
	add	x4, x9, 4
.L210:
	cmp	w2, w1
	add	x0, x0, 4
	csel	w2, w2, w1, ge
	add	w3, w3, 1
	cmp	x11, x0
	csel	x0, x0, x10, cs
	cmp	w3, 5
	beq	.L396
.L213:
	ldr	w1, [x0]
	add	x4, x4, 4
	str	w1, [x4, -4]
	cmp	w1, w7
	bge	.L210
	cmp	w2, w1
	add	x0, x0, 4
	mov	w12, w3
	csel	w2, w2, w1, ge
	add	w3, w3, 1
	cmp	x11, x0
	csel	x0, x0, x10, cs
	cmp	w3, 5
	mov	w7, w1
	bne	.L213
.L396:
	mov	w3, w2
	mov	x1, 0
.L215:
	ldr	w0, [x9, x1, lsl 2]
	cmp	w1, w12
	add	x1, x1, 1
	ccmp	w0, w3, 0, ne
	csel	w0, w0, w3, lt
	cmp	x1, 5
	mov	w3, w0
	bne	.L215
	stp	w8, w5, [x29, 96]
	add	x5, x29, 168
	str	w2, [x29, 196]
	stp	w7, w0, [x29, 188]
	add	x0, x6, 4
	add	x1, x20, 40
	cmp	x11, x0
	str	w13, [x21, 20]
	csel	x0, x0, x1, cs
	str	x0, [x21, 88]
	ldp	x6, x7, [x5]
	add	x5, x29, 184
	add	x2, x29, 160
	stp	x6, x7, [x29, 112]
	add	x1, x29, 156
	add	x4, x29, 112
	ldp	x6, x7, [x5]
	mov	x3, x21
	add	x0, x29, 164
	stp	x6, x7, [x29, 128]
	bl	SearchPhase
	ldp	w0, w1, [x19, 124]
	ldp	w5, w2, [x29, 100]
	cmp	w0, w1
	csel	w0, w0, w1, le
	ldr	w1, [x29, 156]
	cmp	w0, 64
	cset	w6, gt
	cmp	w1, 4
	cset	w1, gt
	str	w6, [x21, 360]
	orr	w1, w6, w1
	orr	w24, w2, w1
	cbnz	w24, .L397
	ldr	w1, [x29, 160]
	cmp	w1, 4
	bhi	.L398
	add	x0, x21, x1, sxtw 2
	and	w2, w1, 1
	ldr	w0, [x0, 428]
	cmp	w0, 3
	cset	w3, gt
	sxtb	w0, w0
	str	w3, [x21, 356]
	strb	w0, [x21, 364]
	ldr	w4, [x20, 16]
	cmp	w4, w2
	beq	.L399
	add	w4, w1, 5
	sxtb	w4, w4
.L224:
	cmp	w1, wzr
	strb	w4, [x21, 366]
	cset	w2, eq
.L222:
	strb	w2, [x21, 365]
	tbnz	w1, #31, .L219
	sxtb	w1, w1
	mov	w8, w3
.L225:
	strb	w1, [x21, 109]
	ldr	w1, [x21, 404]
	cmp	w1, 1
	bne	.L207
	cbnz	w3, .L207
.L206:
	mov	w1, 2
	str	wzr, [x21, 380]
	strb	w1, [x21, 424]
	strb	w1, [x21, 412]
	strb	w1, [x21, 400]
	strb	w1, [x21, 388]
	str	wzr, [x21, 392]
	str	wzr, [x21, 404]
	str	wzr, [x21, 416]
	b	.L207
.L183:
	cmn	w1, #1000
	bge	.L185
	mov	w0, -1000
	str	w0, [x20, 128]
.L186:
	mov	w22, 1
	str	w22, [x20, 132]
	b	.L189
.L388:
	str	w22, [x21, 116]
	ldr	w28, [x20, 16]
	b	.L189
.L397:
	cmp	w0, 64
	mov	w0, -1
	str	w0, [x29, 160]
	ble	.L218
	ldr	w8, [x29, 96]
	mov	w0, 0
	strb	wzr, [x21, 364]
.L220:
	add	x1, x20, 256
	str	w8, [x21, 428]
	mov	w3, 0
	mov	w4, 0
	mov	w2, 0
	stp	w8, w8, [x1, 192]
	stp	w8, w8, [x1, 200]
	strb	wzr, [x21, 366]
	strb	wzr, [x21, 365]
	str	wzr, [x21, 356]
.L219:
	ldrsb	w1, [x29, 164]
	mov	w8, w3
	b	.L225
.L389:
	ldr	x1, [x21, 8]
	mov	x2, 4294967297
	cmp	x1, x2
	ccmp	x1, xzr, 4, ne
	bne	.L146
	ldr	w22, [x21, 116]
	ldr	w28, [x20, 16]
	b	.L189
.L185:
	cmp	w1, 200
	bgt	.L184
	cmn	w1, #200
	blt	.L186
.L358:
	ldr	w22, [x21, 116]
	b	.L189
.L153:
	bge	.L155
	cmp	w4, 254
	mov	w2, 50
	ble	.L157
	mov	w2, 26215
	movk	w2, 0x6666, lsl 16
	smull	x2, w4, w2
	asr	x2, x2, 33
	sub	w2, w2, w4, asr 31
.L157:
	add	w2, w2, w4
	cmp	w2, w3
	bge	.L155
	mov	w2, 2
	str	w2, [x8]
	b	.L156
.L390:
	mov	w2, w4
	ldr	w6, [x1, 8]
	mov	w4, w3
	mov	w3, w2
	b	.L151
.L275:
	mov	w1, 0
	b	.L176
.L218:
	ldrb	w0, [x21, 364]
	mov	w1, 4
	sub	w0, w0, #1
	sxtb	w2, w0
	cmp	w2, 4
	csel	w0, w0, w1, le
	sxtb	w1, w0
	cmp	w1, wzr
	csel	w0, w0, wzr, ge
	strb	w0, [x21, 364]
	sxtb	w0, w0
	mov	w8, w0
	b	.L220
.L391:
	ldr	w7, [x29, 172]
	cbnz	w7, .L176
	b	.L177
.L398:
	cmp	w1, wzr
	ldrsb	w0, [x21, 364]
	ldrsb	w4, [x20, 382]
	cset	w2, eq
	ldr	w3, [x20, 372]
	b	.L222
.L399:
	sxtb	w4, w1
	b	.L224
	.size	PQ_MNG_ALG_FmdSet, .-PQ_MNG_ALG_FmdSet
	.align	3
.LC7:
	.xword	.LANCHOR1
	.align	3
.LC8:
	.xword	.LANCHOR2
	.align	3
.LC9:
	.xword	.LANCHOR0
	.global	g_u32FrmRateThr_H
	.global	g_u32FrmRateThr_L
	.global	g_u32IPDetect
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
.LC0:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	1
	.zero	4
.LC1:
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.type	g_u32PDTypeNum, %object
	.size	g_u32PDTypeNum, 8
g_u32PDTypeNum:
	.word	32
	.word	22
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	g_u32FrmRateThr_L, %object
	.size	g_u32FrmRateThr_L, 4
g_u32FrmRateThr_L:
	.word	23800
	.type	g_u32FrmRateThr_H, %object
	.size	g_u32FrmRateThr_H, 4
g_u32FrmRateThr_H:
	.word	24200
	.bss
	.align	3
.LANCHOR1 = . + 0
	.type	stastlasi1432big.1819, %object
	.size	stastlasi1432big.1819, 16
stastlasi1432big.1819:
	.zero	16
	.type	g_u32IPDetect, %object
	.size	g_u32IPDetect, 4
g_u32IPDetect:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
