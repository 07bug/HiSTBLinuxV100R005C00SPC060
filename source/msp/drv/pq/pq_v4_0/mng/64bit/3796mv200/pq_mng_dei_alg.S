#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"pq_mng_dei_alg.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	PQ_MNG_CopyU32ByBitWithSignal.part.0, %function
PQ_MNG_CopyU32ByBitWithSignal.part.0:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w3
	mov	w21, w1
	mov	x22, x2
	bl	_mcount
	mov	w0, 32
	sub	w3, w20, #1
	sub	w0, w0, w20
	sub	w1, w0, w21
	lsl	w19, w19, w1
	lsr	w1, w19, w0
	lsr	w0, w1, w3
	tbnz	x0, 0, .L5
	mov	w3, 1
	lsl	w20, w3, w20
	sub	w20, w20, #1
	and	w1, w20, w1
	str	w1, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5:
	mov	w3, -1
	lsl	w20, w3, w20
	eor	w1, w20, w1
	str	w1, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PQ_MNG_CopyU32ByBitWithSignal.part.0, .-PQ_MNG_CopyU32ByBitWithSignal.part.0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_CopyU32ByBitWithSignal
	.type	PQ_MNG_CopyU32ByBitWithSignal, %function
PQ_MNG_CopyU32ByBitWithSignal:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	w21, w1
	mov	w19, w4
	mov	x23, x2
	mov	w20, w3
	bl	_mcount
	add	w0, w21, w19
	cmp	w0, 32
	bhi	.L6
	add	w20, w19, w20
	cmp	w20, 32
	bhi	.L6
	mov	w3, w19
	mov	x2, x23
	mov	w1, w21
	mov	w0, w22
	bl	PQ_MNG_CopyU32ByBitWithSignal.part.0
.L6:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	PQ_MNG_CopyU32ByBitWithSignal, .-PQ_MNG_CopyU32ByBitWithSignal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_CopyU32ByBitWithoutSignal
	.type	PQ_MNG_CopyU32ByBitWithoutSignal, %function
PQ_MNG_CopyU32ByBitWithoutSignal:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w4
	mov	x23, x2
	mov	w22, w3
	bl	_mcount
	add	w0, w21, w20
	cmp	w0, 32
	bhi	.L8
	add	w22, w20, w22
	cmp	w22, 32
	bhi	.L8
	mov	w0, 32
	mov	w4, 1
	sub	w0, w0, w20
	lsl	w20, w4, w20
	sub	w1, w0, w21
	sub	w20, w20, #1
	lsl	w1, w19, w1
	lsr	w19, w1, w0
	and	w19, w20, w19
	str	w19, [x23]
.L8:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	PQ_MNG_CopyU32ByBitWithoutSignal, .-PQ_MNG_CopyU32ByBitWithoutSignal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_API_GMD
	.type	PQ_MNG_ALG_API_GMD, %function
PQ_MNG_ALG_API_GMD:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	x19, x3
	bl	_mcount
	cmp	w21, wzr
	ccmp	w20, wzr, 4, ne
	beq	.L18
	ldr	x4, .LC2
	add	w5, w21, w21, lsr 31
	add	w0, w20, w20, lsr 31
	asr	w5, w5, 1
	asr	w0, w0, 1
	add	w5, w5, 1048576
	ldr	w1, [x4, 4]
	add	w0, w0, 1048576
	sdiv	w2, w5, w21
	cmp	w1, wzr
	sdiv	w1, w0, w20
	ble	.L12
	ldr	w0, [x4]
	tbz	w0, #31, .L12
	ldr	w0, [x4, 8]
	cmp	w0, wzr
	ble	.L12
	ldr	w0, [x4, 48]
	mov	w3, 15
	add	w0, w0, 1
	b	.L20
	.p2align 3
.L12:
	ldr	w0, [x4, 48]
	cmp	w0, 3
	ble	.L21
	sub	w0, w0, #4
	mov	w3, 15
.L20:
	cmp	w0, w3
	csel	w0, w0, w3, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	str	w0, [x4, 48]
.L13:
	str	w0, [x19]
	sxtw	x1, w1
	ldp	w5, w3, [x4, 56]
	ldr	w8, [x4, 64]
	ldr	w0, [x4, 52]
	ldp	w7, w6, [x22]
	stp	w0, w5, [x29, 48]
	stp	w3, w8, [x29, 56]
	ldp	w5, w3, [x22, 8]
	stp	w5, w3, [x4, 60]
	stp	w7, w6, [x4, 52]
	mov	x3, 0
	add	x7, x29, 64
	mov	w5, 65535
.L16:
	smull	x0, w0, w2
	mov	w6, 65535
	asr	x0, x0, 12
	mul	x0, x0, x1
	asr	x0, x0, 11
	add	x0, x0, 1
	asr	x0, x0, 1
	cmp	w0, w5
	csel	w0, w0, w5, le
	str	w0, [x7, x3]
	add	x3, x3, 4
	cmp	x3, 16
	beq	.L15
	add	x0, x29, 48
	ldr	w0, [x0, x3]
	b	.L16
	.p2align 3
.L21:
	mov	w0, 0
	str	wzr, [x4, 48]
	b	.L13
	.p2align 3
.L15:
	ldp	w1, w3, [x4, 76]
	ldr	w2, [x4, 84]
	mov	w0, 255
	lsr	w1, w1, 2
	add	w1, w1, w3, lsr 1
	add	w1, w1, w2
	subs	w1, w1, #1024
	csel	w1, w1, wzr, pl
	lsl	w1, w1, 5
	cmp	w1, w6
	bgt	.L17
	add	w0, w1, w0
	cmp	w1, wzr
	csel	w1, w0, w1, lt
	asr	w0, w1, 8
.L17:
	ldp	w6, w5, [x29, 64]
	ldp	w3, w2, [x29, 72]
	stp	w6, w5, [x4, 72]
	stp	w3, w2, [x4, 80]
.L11:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L18:
	mov	w0, -1
	b	.L11
	.size	PQ_MNG_ALG_API_GMD, .-PQ_MNG_ALG_API_GMD
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_API_GMD_P
	.type	PQ_MNG_ALG_API_GMD_P, %function
PQ_MNG_ALG_API_GMD_P:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	x19, x3
	bl	_mcount
	cmp	w21, wzr
	ccmp	w20, wzr, 4, ne
	beq	.L30
	ldr	x6, .LC4
	add	w0, w20, w20, lsr 31
	asr	w0, w0, 1
	add	w5, w21, w21, lsr 31
	add	x3, x6, 88
	add	w0, w0, 1048576
	ldr	w4, [x6, 88]
	asr	w5, w5, 1
	sdiv	w1, w0, w20
	add	w5, w5, 1048576
	ldp	w9, w7, [x3, 4]
	sub	w4, w4, w7
	sxtw	x0, w4
	eor	x4, x0, x0, asr 63
	sub	x4, x4, x0, asr 63
	sdiv	w2, w5, w21
	ldr	w5, [x6, 16]
	cmp	w5, w4
	bgt	.L32
.L25:
	mov	w0, 0
	str	wzr, [x6, 100]
.L26:
	str	w0, [x19]
	sxtw	x1, w1
	mov	x3, 0
	add	x8, x29, 64
	ldp	w0, w4, [x22]
	ldr	w5, [x22, 8]
	stp	w0, w4, [x29, 48]
	ldr	w4, [x22, 12]
	str	w4, [x29, 60]
	mov	w4, 65535
	str	w5, [x29, 56]
.L28:
	smull	x0, w0, w2
	mov	w5, 65535
	asr	x0, x0, 12
	mul	x0, x0, x1
	asr	x0, x0, 11
	add	x0, x0, 1
	asr	x0, x0, 1
	cmp	w0, w4
	csel	w0, w0, w4, le
	str	w0, [x8, x3]
	add	x3, x3, 4
	cmp	x3, 16
	beq	.L27
	add	x0, x29, 48
	ldr	w0, [x0, x3]
	b	.L28
	.p2align 3
.L27:
	ldp	w1, w3, [x29, 68]
	ldr	w2, [x29, 76]
	mov	w0, 255
	lsr	w1, w1, 2
	add	w1, w1, w3, lsr 1
	add	w1, w1, w2
	subs	w1, w1, #1024
	csel	w1, w1, wzr, pl
	lsl	w1, w1, 5
	cmp	w1, w5
	ble	.L33
.L29:
	stp	w9, w7, [x6, 88]
	str	w0, [x6, 96]
.L23:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L33:
	add	w0, w1, w0
	cmp	w1, wzr
	csel	w1, w0, w1, lt
	asr	w0, w1, 8
	b	.L29
	.p2align 3
.L32:
	sub	w0, w9, w7
	ldr	w4, [x6, 12]
	sxtw	x0, w0
	eor	x3, x0, x0, asr 63
	sub	x3, x3, x0, asr 63
	cmp	w4, w3
	bge	.L25
	ldr	w0, [x6, 100]
	mov	w3, 15
	add	w0, w0, 1
	cmp	w0, w3
	csel	w0, w0, w3, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	str	w0, [x6, 100]
	b	.L26
	.p2align 3
.L30:
	mov	w0, -1
	b	.L23
	.size	PQ_MNG_ALG_API_GMD_P, .-PQ_MNG_ALG_API_GMD_P
	.align	3
.LC4:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_RGMV_HVCHK
	.type	PQ_MNG_ALG_RGMV_HVCHK, %function
PQ_MNG_ALG_RGMV_HVCHK:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x2
	mov	w22, w3
	stp	x1, x0, [x29, 104]
	mov	x0, x30
	mov	w19, w4
	mov	w21, w6
	str	w5, [x29, 120]
	bl	_mcount
	cbz	x26, .L34
	cmp	w19, wzr
	str	wzr, [x29, 168]
	ccmp	w22, wzr, 4, ne
	stp	wzr, wzr, [x29, 144]
	stp	wzr, wzr, [x29, 152]
	stp	wzr, wzr, [x29, 160]
	beq	.L34
	mov	w27, 43691
	add	w0, w22, 383
	movk	w27, 0x2aaa, lsl 16
	mov	w23, 192
	smull	x27, w0, w27
	asr	x27, x27, 38
	sub	w27, w27, w0, asr 31
	cmp	w27, 3
	csel	w23, wzr, w23, cc
	cmp	w27, 1
	bls	.L60
	lsl	w0, w27, 24
	cmp	w21, 5
	sub	w0, w0, w27
	add	w19, w19, w19, lsr 31
	lsl	w0, w0, 1
	sub	w0, w0, w27
	add	w27, w22, 545
	add	w27, w27, w0, lsl 7
	lsr	w27, w27, 6
	lsl	w27, w27, 4
	add	w27, w27, 63
	and	w0, w27, 2147483584
	str	w0, [x29, 128]
	asr	w0, w19, 1
	beq	.L75
.L40:
	add	w25, w0, 24
	adds	w0, w0, 9
	csel	w0, w25, w0, mi
	asr	w1, w0, 4
	str	w1, [x29, 132]
.L41:
	cmp	w22, 960
	ble	.L42
	add	w0, w22, w22, lsr 31
	asr	w0, w0, 1
	add	w20, w0, 96
	adds	w0, w0, 33
	csel	w0, w20, w0, mi
	cmp	w21, 5
	asr	w20, w0, 6
	beq	.L76
.L44:
	ldr	w0, [x29, 132]
	cbz	w0, .L34
	mov	w27, 0
	mov	w28, 0
	add	x22, x29, 160
	str	wzr, [x29, 124]
	str	wzr, [x29, 140]
	.p2align 2
.L55:
	ldr	w1, [x29, 124]
	mov	x25, 0
	lsr	w0, w1, 2
	str	w0, [x29, 136]
	cbnz	w20, .L54
	b	.L58
	.p2align 3
.L77:
	cmp	w25, 5
	ble	.L61
	ldr	w0, [x29, 128]
	cmp	w25, 24
	mov	x10, 8
	csel	w9, w23, w0, lt
.L47:
	mov	w0, 43691
	cmp	w3, 5
	movk	w0, 0x2aaa, lsl 16
	smull	x2, w3, w0
	cset	w0, gt
	cmp	w3, 11
	lsr	x2, x2, 32
	lsl	w4, w0, 7
	sub	w2, w2, w3, asr 31
	lsl	w1, w2, 2
	mov	w0, w2
	sub	w2, w1, w2
	sub	w2, w3, w2, lsl 1
	ble	.L62
	sub	w1, w0, #1
	mul	w0, w1, w23
.L50:
	ldr	w1, [x29, 140]
	add	w0, w4, w0
	mov	w3, 9
	mul	w4, w9, w1
	lsl	w1, w2, 2
	ldr	w2, [x29, 132]
	add	w4, w1, w4, lsr 2
	mov	w1, 0
	mul	w0, w0, w2
	add	x4, x4, x10
	add	x2, x29, 144
	lsr	w0, w0, 2
	add	x24, x4, x0
	lsl	x19, x24, 2
	add	x19, x19, 4
	ldr	w0, [x26, x24, lsl 2]
	bl	PQ_MNG_CopyU32ByBitWithSignal.part.0
	ldr	w4, [x26, x24, lsl 2]
.L73:
	ldr	w0, [x26, x19]
	ubfx	x9, x4, 9, 10
	mov	w3, 8
	ubfx	x4, x4, 19, 10
	mov	x2, x22
	mov	w1, 7
	stp	w9, w4, [x29, 148]
	bl	PQ_MNG_CopyU32ByBitWithSignal.part.0
	add	x25, x25, 1
	ldr	w1, [x26, x19]
	ldrsw	x4, [x29, 160]
	ubfx	x0, x1, 15, 10
	ubfx	x1, x1, 25, 4
	ldrsw	x3, [x29, 144]
	stp	w0, w1, [x29, 164]
	ldr	w1, [x29, 152]
	eor	x9, x4, x4, asr 63
	sub	x9, x9, x4, asr 63
	eor	x10, x3, x3, asr 63
	cmp	w1, 127
	ubfx	x1, x1, 4, 26
	cset	w4, hi
	cmp	w9, 3
	sub	x10, x10, x3, asr 63
	cset	w3, gt
	subs	w0, w0, w1
	ldr	w2, [x29, 148]
	csel	w0, w0, wzr, pl
	and	w3, w4, w3
	cmp	w0, 255
	cset	w9, ls
	cmp	w10, 3
	cset	w0, gt
	subs	w1, w2, w1
	csel	w1, w1, wzr, pl
	and	w0, w4, w0
	cmp	w1, 255
	and	w1, w9, w3
	cset	w2, ls
	cmp	w20, w25
	and	w0, w2, w0
	add	w28, w28, w1
	add	w27, w27, w0
	bls	.L58
.L54:
	cmp	w21, 5
	mov	w3, w25
	beq	.L77
	ldr	w0, [x29, 136]
	mov	w3, 9
	add	x2, x29, 144
	mov	w1, 0
	add	w4, w0, w25, lsl 2
	mov	w24, w4
	ubfiz	x19, x24, 2, 32
	add	x19, x19, 4
	ldr	w0, [x26, w24, uxtw 2]
	bl	PQ_MNG_CopyU32ByBitWithSignal.part.0
	ldr	w4, [x26, w24, uxtw 2]
	b	.L73
	.p2align 3
.L58:
	ldp	w2, w1, [x29, 120]
	ldr	w0, [x29, 140]
	add	w1, w1, w2
	str	w1, [x29, 124]
	ldr	w1, [x29, 132]
	add	w0, w0, 1
	str	w0, [x29, 140]
	cmp	w1, w0
	bne	.L55
	cbz	w20, .L34
	ldr	w0, [x29, 132]
	lsl	w1, w28, 7
	mov	w2, 511
	ldr	x3, [x29, 112]
	lsl	w6, w27, 7
	mul	w20, w20, w0
	udiv	w1, w1, w20
	cmp	w1, w2
	csel	w1, w1, w2, ls
	str	w1, [x3]
	ldr	x1, [x29, 104]
	udiv	w0, w6, w20
	cmp	w0, w2
	csel	w0, w0, w2, ls
	str	w0, [x1]
.L34:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L42:
	adds	w20, w22, 33
	add	w0, w22, 96
	csel	w20, w0, w20, mi
	cmp	w21, 5
	asr	w20, w20, 6
	bne	.L44
.L76:
	add	w20, w22, 96
	adds	w22, w22, 33
	csel	w22, w20, w22, mi
	asr	w20, w22, 6
	b	.L44
.L60:
	str	wzr, [x29, 128]
	cmp	w21, 5
	add	w19, w19, w19, lsr 31
	asr	w0, w19, 1
	bne	.L40
.L75:
	add	w25, w0, 12
	adds	w0, w0, 5
	csel	w0, w25, w0, mi
	asr	w1, w0, 3
	str	w1, [x29, 132]
	b	.L41
.L62:
	mov	w0, 0
	b	.L50
.L61:
	mov	x10, 0
	mov	w9, 128
	b	.L47
	.size	PQ_MNG_ALG_RGMV_HVCHK, .-PQ_MNG_ALG_RGMV_HVCHK
	.global	g_pstDeiSwAlgPara
	.global	g_bMcDiEn
	.data
	.align	2
	.type	g_bMcDiEn, %object
	.size	g_bMcDiEn, 4
g_bMcDiEn:
	.word	1
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_pstDeiSwAlgPara, %object
	.size	g_pstDeiSwAlgPara, 48
g_pstDeiSwAlgPara:
	.zero	48
	.type	nAdjK_STAT.1635, %object
	.size	nAdjK_STAT.1635, 4
nAdjK_STAT.1635:
	.zero	4
	.type	g_mtnsum0, %object
	.size	g_mtnsum0, 4
g_mtnsum0:
	.zero	4
	.type	g_mtnsum1, %object
	.size	g_mtnsum1, 4
g_mtnsum1:
	.zero	4
	.type	g_mtnsum2, %object
	.size	g_mtnsum2, 4
g_mtnsum2:
	.zero	4
	.type	g_mtnsum3, %object
	.size	g_mtnsum3, 4
g_mtnsum3:
	.zero	4
	.zero	4
	.type	g_MTSum_GMD, %object
	.size	g_MTSum_GMD, 16
g_MTSum_GMD:
	.zero	16
	.type	nAdjK_status.1657, %object
	.size	nAdjK_status.1657, 12
nAdjK_status.1657:
	.zero	12
	.type	nAdjK_STAT_p.1656, %object
	.size	nAdjK_STAT_p.1656, 4
nAdjK_STAT_p.1656:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
