#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"drv_venc_ratecontrol.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VEDU_DRV_RCModifyQPDeltaOfIP, %function
VEDU_DRV_RCModifyQPDeltaOfIP:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x4, [x19, 120]
	mov	x1, 4294967295
	ldr	w0, [x19, 28]
	cmp	x4, x1
	ldr	w5, [x19, 68]
	bls	.L2
	ldr	w1, [x19, 128]
	lsl	w2, w1, 4
	add	w3, w2, w1, lsl 2
.L3:
	cmp	w3, 16711680
	mov	w1, 33423360
	csel	w3, w3, w1, ls
	ldr	w5, [x19, 4564]
	cmp	w3, w0
	bcc	.L6
	cmp	w5, wzr
	ble	.L1
.L6:
	sub	w2, w0, w3
	mov	w1, -256
	lsl	w2, w2, 8
	ldr	w4, [x19, 4448]
	mov	w6, 3264
	mov	w0, 256
	udiv	w2, w2, w3
	ldr	x3, .LC0
	cmp	w2, w1
	csel	w1, w2, w1, ge
	cmp	w4, w6
	csel	w4, w4, w6, ls
	cmp	w1, w0
	csel	w1, w1, w0, le
	lsr	w4, w4, 6
	add	w0, w5, w1, asr 6
	cmp	w0, wzr
	ldr	w1, [x3, w4, uxtw 2]
	csel	w0, w0, wzr, ge
	cmp	w1, w0
	csel	w0, w1, w0, le
	str	w0, [x19, 4564]
.L1:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2:
	lsl	w3, w4, 4
	add	w5, w5, 19
	add	w4, w3, w4, lsl 2
	udiv	w3, w4, w5
	b	.L3
	.size	VEDU_DRV_RCModifyQPDeltaOfIP, .-VEDU_DRV_RCModifyQPDeltaOfIP
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VEDU_DRV_RCGetTimeOfP, %function
VEDU_DRV_RCGetTimeOfP:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4576]
	cbz	w0, .L11
	ldr	w0, [x19, 4608]
	add	w0, w0, 1
	cmp	w0, 1
	bls	.L29
	mov	w0, 0
	str	wzr, [x19, 4608]
.L13:
	add	x0, x19, x0, uxtw 2
	ldr	w1, [x19, 28]
	str	w1, [x0, 4580]
.L14:
	ldr	w0, [x19, 4584]
	add	x3, x19, 4096
	ldr	w2, [x19, 4580]
	mov	w1, 0
	add	w2, w2, w0
	add	x0, x3, 492
	add	x3, x3, 512
	.p2align 2
.L17:
	ldr	w4, [x0], 4
	cmp	x3, x0
	add	w1, w1, w4
	bne	.L17
	cmp	w1, wzr
	ccmp	w2, wzr, 4, ne
	beq	.L23
	add	w2, w2, w2, lsl 2
	lsl	w1, w1, 1
	mov	w0, 3
	sdiv	w1, w2, w1
	str	w1, [x19, 4556]
	cmp	w1, 2
	ble	.L22
	mov	w0, 50
	cmp	w1, w0
	csel	w0, w1, w0, le
.L22:
	ldr	w1, [x19, 68]
	str	w0, [x19, 4556]
	mov	w0, 1
	cmp	w1, 1
	str	w0, [x19, 4560]
	mov	w0, 0
	bne	.L18
	str	w1, [x19, 4556]
.L18:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L11:
	ldr	w1, [x19, 4612]
	add	w1, w1, 1
	cmp	w1, 4
	bhi	.L15
	mov	w0, w1
	str	w1, [x19, 4612]
.L16:
	add	x0, x19, x0, uxtw 2
	ldr	w1, [x19, 28]
	str	w1, [x0, 4588]
	b	.L14
	.p2align 3
.L15:
	str	wzr, [x19, 4612]
	b	.L16
	.p2align 3
.L29:
	str	w0, [x19, 4608]
	b	.L13
.L23:
	mov	w0, -1
	b	.L18
	.size	VEDU_DRV_RCGetTimeOfP, .-VEDU_DRV_RCGetTimeOfP
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VEDU_DRV_RcModifyQPForLargeFrmBits.isra.1, %function
VEDU_DRV_RcModifyQPForLargeFrmBits.isra.1:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	VEDU_DRV_RcModifyQPForLargeFrmBits.isra.1, .-VEDU_DRV_RcModifyQPForLargeFrmBits.isra.1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VEDU_DRV_RCGetTargetFrameBits, %function
VEDU_DRV_RCGetTargetFrameBits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 64]
	ldr	w1, [x19, 4908]
	cmp	w1, w0
	beq	.L49
	ldr	w2, [x19, 56]
	str	w0, [x19, 4908]
	udiv	w2, w0, w2
	str	w2, [x19, 128]
.L39:
	ldp	w3, w4, [x19, 68]
	umull	x5, w3, w2
	str	x5, [x19, 120]
	cbnz	w4, .L50
	ldr	w0, [x19, 4560]
.L42:
	cmp	w3, 999
	bls	.L51
	mul	w0, w0, w2
	cmp	w4, wzr
	str	w0, [x19, 4524]
	cset	w0, ne
	str	w0, [x19, 4576]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L51:
	uxtw	x0, w0
.L43:
	ldr	w1, [x19, 4904]
	cmp	w3, w1
	beq	.L45
	str	w3, [x19, 4904]
.L45:
	mul	x0, x5, x0
	mov	x1, 4294967295
	cmp	x0, x1
	bls	.L47
	ldr	x1, .LC3
	ldr	x0, .LC5
	ldr	x1, [x1, 16]
	blr	x1
	ldp	w3, w4, [x19, 68]
	mov	w0, -1
.L47:
	ldr	w1, [x19, 4556]
	sub	w3, w3, #1
	cmp	w4, wzr
	add	w3, w3, w1
	udiv	w0, w0, w3
	str	w0, [x19, 4524]
	cset	w0, ne
	str	w0, [x19, 4576]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L50:
	cmp	w3, 1
	beq	.L41
	ldr	w0, [x19, 4556]
	ldr	w6, [x19, 4536]
	ldr	w1, [x19, 4540]
	cmp	w0, w6
	csel	w0, w0, w6, ge
	cmp	w1, w0
	csel	w0, w1, w0, le
	str	w0, [x19, 4556]
	b	.L42
	.p2align 3
.L49:
	ldr	w2, [x19, 128]
	b	.L39
	.p2align 3
.L41:
	mov	x0, 1
	str	w3, [x19, 4556]
	b	.L43
	.size	VEDU_DRV_RCGetTargetFrameBits, .-VEDU_DRV_RCGetTargetFrameBits
	.align	3
.LC3:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC5:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RC_DRV_NewModeMovingDecision
	.type	RC_DRV_NewModeMovingDecision, %function
RC_DRV_NewModeMovingDecision:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w12, [x19, 4528]
	add	x4, x19, 216
	ldr	x9, .LC6
	add	x8, x19, 224
	ldr	w1, [x19, 52]
	mov	x2, x4
	mov	w5, 0
	mov	w10, 15
	mov	w6, w12
.L54:
	ldr	w3, [x2]
	add	x7, x9, 208
	cmn	w3, #1
	add	w0, w3, 8
	beq	.L63
	subs	w0, w0, w6
	csel	w0, w0, wzr, pl
	cmp	w0, 15
	csel	w0, w0, w10, le
	ldr	w6, [x7, w0, sxtw 2]
	mov	w3, w6
.L53:
	ldr	w0, [x2, -64]
	add	x2, x2, 4
	cmp	x8, x2
	mul	w3, w3, w0
	add	w5, w5, w3, lsr 5
	bne	.L54
	add	x0, x19, 184
	mov	w2, 0
	.p2align 2
.L55:
	ldr	w3, [x0], 4
	cmp	x4, x0
	add	w2, w2, w3
	bne	.L55
	cmp	w5, wzr
	mov	w0, 255
	ccmp	w2, wzr, 4, ne
	cset	w3, eq
	cbz	w3, .L69
.L56:
	add	w11, w1, 16773120
	mov	w9, 100
	add	w11, w11, 4066
	sub	w9, w9, w1
	lsl	w11, w11, 8
	mov	w10, 41195
	movk	w10, 0xea0e, lsl 16
	ldr	w3, [x19, 248]
	madd	w0, w9, w0, w11
	ldr	w4, [x19, 280]
	add	x2, x19, 252
	lsr	w0, w0, 1
	add	x13, x19, 280
	mov	w8, 0
	mov	w7, 0
	umull	x10, w0, w10
	mov	w1, w4
	mov	w0, w3
	lsr	x10, x10, 32
	mov	w5, w3
	lsr	w10, w10, 5
	mov	w6, w4
	b	.L59
	.p2align 3
.L70:
	ldr	w0, [x2]
	add	x2, x2, 4
	ldr	w1, [x2, 28]
.L59:
	cmp	w4, w1
	add	w7, w7, w0
	csel	w4, w4, w1, cs
	cmp	w6, w1
	csel	w6, w6, w1, ls
	cmp	w3, w0
	csel	w3, w3, w0, cs
	cmp	w5, w0
	csel	w5, w5, w0, ls
	cmp	x13, x2
	add	w8, w8, w1
	bne	.L70
	sub	w3, w7, w3
	subs	w3, w3, w5
	bne	.L60
	mov	w0, 100
	mov	w1, 256
	str	w0, [x19, 312]
.L61:
	add	w11, w11, 4096
	mov	w2, 8969
	add	w11, w11, 2304
	movk	w2, 0x58ed, lsl 16
	add	w3, w10, 1
	str	w10, [x19, 436]
	madd	w1, w9, w1, w11
	umull	x2, w1, w2
	lsr	x2, x2, 32
	sub	w1, w1, w2
	add	w1, w2, w1, lsr 1
	lsr	w0, w1, 6
	str	w0, [x19, 440]
	add	w0, w3, w0
	lsr	w0, w0, 1
	str	w0, [x19, 444]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L63:
	mov	w6, 32
	mov	w3, w6
	b	.L53
	.p2align 3
.L69:
	lsl	w5, w5, 6
	sdiv	w2, w5, w2
	asr	w2, w2, 4
	cmp	w2, wzr
	ble	.L65
	mov	w4, 99
	ldr	x0, .LC6
	cmp	w2, w4
	mov	w3, 34079
	csel	w2, w2, w4, le
	add	x0, x0, 272
	movk	w3, 0x51eb, lsl 16
	ldr	w0, [x0, w2, sxtw 2]
	lsl	w0, w0, 8
	smull	x2, w0, w3
	asr	x2, x2, 37
	sub	w0, w2, w0, asr 31
	b	.L56
	.p2align 3
.L60:
	lsr	w12, w12, 6
	mov	w2, 15
	subs	w12, w12, #22
	ldr	x1, .LC6
	csel	w0, w12, wzr, pl
	sub	w4, w8, w4
	cmp	w0, w2
	sub	w6, w4, w6
	csel	w0, w0, w2, le
	add	x2, x1, 672
	ldr	w0, [x2, w0, sxtw 2]
	mul	w0, w6, w0
	sdiv	w0, w0, w3
	cmp	w0, wzr
	ble	.L66
	mov	w4, 16
	add	x2, x1, 736
	cmp	w0, w4
	mov	w1, 34079
	csel	w0, w0, w4, le
	movk	w1, 0x51eb, lsl 16
	ldr	w0, [x2, w0, sxtw 2]
	lsl	w0, w0, 8
	smull	x1, w0, w1
	asr	x1, x1, 37
	sub	w1, w1, w0, asr 31
.L62:
	lsl	w0, w6, 2
	sub	w0, w0, w6
	lsl	w2, w0, 5
	add	w0, w0, w2
	add	w6, w0, w6
	sdiv	w3, w6, w3
	str	w3, [x19, 312]
	b	.L61
	.p2align 3
.L65:
	mov	w0, 253
	b	.L56
	.p2align 3
.L66:
	mov	w1, 12
	b	.L62
	.size	RC_DRV_NewModeMovingDecision, .-RC_DRV_NewModeMovingDecision
	.align	3
.LC6:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_EflRCCalcTargetFrameBits
	.type	VEDU_DRV_EflRCCalcTargetFrameBits, %function
VEDU_DRV_EflRCCalcTargetFrameBits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	bl	_mcount
	ldr	w3, [x20, 68]
	ldr	w0, [x20, 4904]
	cmp	w0, w3
	beq	.L72
	ldr	w0, [x20, 128]
	str	w3, [x20, 4904]
	umull	x0, w0, w3
	str	x0, [x20, 120]
.L72:
	uxtw	x0, w19
	mov	x4, 4294967295
	mul	x0, x0, x21
	cmp	x0, x4
	bls	.L74
	ldr	x1, .LC11
	ldr	x0, .LC12
	ldr	x1, [x1, 16]
	blr	x1
	ldr	w3, [x20, 68]
	mov	w0, -1
.L74:
	ldr	w1, [x20, 4556]
	ldr	x21, [sp, 32]
	sub	w1, w1, #1
	add	w3, w1, w3
	ldp	x19, x20, [sp, 16]
	udiv	w0, w0, w3
	ldp	x29, x30, [sp], 48
	ret
	.size	VEDU_DRV_EflRCCalcTargetFrameBits, .-VEDU_DRV_EflRCCalcTargetFrameBits
	.align	3
.LC11:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC12:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCCalculateCurQP_AVBR
	.type	VEDU_DRV_RCCalculateCurQP_AVBR, %function
VEDU_DRV_RCCalculateCurQP_AVBR:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w21, [x19, 4576]
	ldr	w20, [x19, 4888]
	ldr	w23, [x19, 4896]
	cbnz	w21, .L98
.L76:
	ldr	w22, [x19, 28]
	ldr	w25, [x19, 4456]
	ldr	w3, [x19, 4936]
	mov	w0, w22
	ldr	w1, [x19, 56]
	mov	w2, w25
	ldr	w24, [x19, 4556]
	bl	VEDU_DRV_RcModifyQPForLargeFrmBits.isra.1
	cmp	w22, w25
	asr	w3, w24, 4
	bcc	.L77
	sub	w2, w22, w25
	ldr	w1, [x19, 316]
	lsl	w2, w2, 6
	udiv	w2, w2, w25
	mul	w1, w2, w1
	asr	w1, w1, 8
.L78:
	add	w0, w1, w0
	mov	w1, -54
	cmp	w0, w1
	mov	w4, 256
	csel	w1, w0, w1, ge
	mov	w2, 10
	cmp	w1, w4
	csel	w1, w1, w4, le
	cmp	w3, 9
	ble	.L79
	mov	w0, 200
	cmp	w3, w0
	csel	w2, w3, w0, le
.L79:
	lsl	w0, w1, 3
	cmp	w24, 640
	add	w1, w0, w1, lsl 1
	sdiv	w0, w1, w2
	ble	.L80
	cmn	w0, #16
	mov	w1, -16
	csel	w0, w0, w1, ge
	mov	w1, 32
	cmp	w0, w1
	csel	w0, w0, w1, le
.L80:
	ldr	w4, [x19, 64]
	lsl	w1, w23, 5
	lsl	w2, w20, 5
	mov	w3, 63
	ldr	w6, [x19, 136]
	udiv	w1, w1, w4
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	udiv	w2, w2, w4
	cmp	w2, wzr
	csel	w2, w2, wzr, ge
	cmp	w2, 63
	csel	w2, w2, w3, le
	cmp	w1, w3
	csel	w1, w1, w3, le
	ldr	x3, .LC13
	cmp	w20, w23
	add	x3, x3, 808
	ldr	w1, [x3, w1, sxtw 2]
	ldr	w2, [x3, w2, sxtw 2]
	sub	w2, w2, w1
	lsr	w1, w6, 4
	bls	.L81
	sub	w3, w6, w1
	cmp	w20, w3
	bls	.L81
	lsl	w1, w2, 2
	mov	w5, -128
	sub	w2, w1, w2
	mov	w1, 256
	sbfx	x2, x2, 1, 30
	cmp	w2, w5
	csel	w2, w2, w5, ge
	cmp	w2, w1
	csel	w5, w2, w1, le
.L82:
	cmp	w24, 640
	ble	.L83
	cmn	w5, #16
	mov	w1, -16
	csel	w5, w5, w1, ge
	mov	w1, 32
	cmp	w5, w1
	csel	w5, w5, w1, le
.L83:
	ldp	x3, x1, [x19, 392]
	ldr	w6, [x19, 144]
	lsr	x3, x3, 10
	lsr	x1, x1, 10
	sub	w3, w3, w6
	sub	w1, w1, w6
	lsl	w2, w3, 2
	sub	w3, w2, w3
	lsl	w2, w1, 2
	lsl	w3, w3, 3
	sub	w1, w2, w1
	lsl	w1, w1, 4
	udiv	w3, w3, w6
	cmp	w3, wzr
	csinv	w3, w3, wzr, ge
	cmp	w3, wzr
	csinc	w3, w3, wzr, le
	udiv	w1, w1, w6
	cmp	w1, wzr
	csinv	w1, w1, wzr, ge
	cmp	w1, wzr
	csinc	w1, w1, wzr, le
	cmp	w20, w4
	bls	.L84
	add	w4, w0, w5
	ldr	w6, [x19, 4520]
	add	w4, w4, w3
	mov	w7, 0
	add	w2, w4, w1
.L85:
	add	x4, x19, 256
	add	w2, w7, w2
	add	w2, w2, w6
	stp	w0, w5, [x4, 160]
	stp	w3, w1, [x4, 168]
	str	w7, [x19, 432]
	str	w2, [x19, 4520]
	cbz	w21, .L87
	ldr	w0, [x19, 4452]
	cmp	w2, w0
	bcs	.L87
	ldr	w1, [x19, 68]
	cmp	w1, 1
	bls	.L87
	add	w2, w2, w0
	lsr	w2, w2, 1
.L87:
	ldp	w1, w0, [x19, 4]
	lsl	w1, w1, 6
	lsl	w3, w0, 6
	cmp	w1, w2
	csel	w0, w1, w2, cs
	cmp	w0, w3
	csel	w0, w0, w3, ls
	str	w0, [x19, 4520]
	lsr	w0, w0, 6
	str	w0, [x19, 4528]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L81:
	cmp	w20, w23
	mov	w5, 0
	bcs	.L82
	add	w6, w6, w1
	cmp	w23, w6
	bcs	.L82
	lsl	w1, w2, 2
	mov	w5, -128
	sub	w2, w1, w2
	mov	w1, 256
	asr	w2, w2, 2
	cmp	w2, w5
	csel	w2, w2, w5, ge
	cmp	w2, w1
	csel	w5, w2, w1, le
	b	.L82
	.p2align 3
.L84:
	add	w2, w0, w5
	add	w2, w2, w3
	add	w2, w2, w1
	cmp	w2, wzr
	ble	.L99
	ldr	w4, [x19, 148]
	mov	w7, 0
	ldr	w6, [x19, 4520]
	cmp	w6, w4, lsl 6
	bcc	.L85
	add	w4, w5, w3
	mov	w7, -6
	add	w2, w4, w1
	mov	w0, 0
	b	.L85
	.p2align 3
.L77:
	sub	w22, w25, w22
	lsl	w1, w22, 3
	sub	w1, w1, w22
	lsl	w1, w1, 3
	udiv	w1, w1, w25
	neg	w1, w1
	b	.L78
	.p2align 3
.L98:
	mov	x0, x19
	bl	VEDU_DRV_RCModifyQPDeltaOfIP
	ldr	w21, [x19, 4576]
	b	.L76
	.p2align 3
.L99:
	mov	w7, 0
	ldr	w6, [x19, 4520]
	b	.L85
	.size	VEDU_DRV_RCCalculateCurQP_AVBR, .-VEDU_DRV_RCCalculateCurQP_AVBR
	.align	3
.LC13:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCGetTargetFrameBits_AVBR
	.type	VEDU_DRV_RCGetTargetFrameBits_AVBR, %function
VEDU_DRV_RCGetTargetFrameBits_AVBR:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 64]
	ldr	w1, [x19, 4908]
	cmp	w1, w0
	beq	.L119
	ldr	w1, [x19, 56]
	str	w0, [x19, 4908]
	udiv	w1, w0, w1
	str	w1, [x19, 128]
.L102:
	ldr	w2, [x19, 68]
	mov	x0, x19
	umull	x1, w2, w1
	str	x1, [x19, 120]
	bl	RC_DRV_NewModeMovingDecision
	ldr	w1, [x19, 316]
	ldr	w4, [x19, 148]
	sub	w2, w1, #2
	ldr	w3, [x19, 4520]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	cmp	w3, w4, lsl 6
	bcc	.L103
	cmp	w1, w0
	bhi	.L120
.L103:
	str	w0, [x19, 316]
.L105:
	ldr	w2, [x19, 64]
	uxtw	x1, w0
	ldr	x3, [x19, 120]
	mul	w0, w0, w2
	mul	x1, x1, x3
	lsr	w0, w0, 8
	lsr	x1, x1, 8
	stp	w0, w1, [x19, 136]
	lsr	w0, w1, 10
	cbnz	w0, .L118
	mov	w0, 1
.L118:
	ldr	w4, [x19, 72]
	str	w0, [x19, 144]
	cbnz	w4, .L121
	ldr	w3, [x19, 68]
	ldr	w0, [x19, 4560]
.L110:
	cmp	w3, 999
	bls	.L122
	ldr	w1, [x19, 128]
	cmp	w4, wzr
	mul	w0, w0, w1
	str	w0, [x19, 4524]
	cset	w0, ne
	str	w0, [x19, 4576]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L120:
	add	w1, w1, 1
	cmp	w1, 254
	ble	.L117
	mov	w1, 255
.L117:
	str	w1, [x19, 316]
	b	.L105
	.p2align 3
.L122:
	uxtw	x0, w0
.L111:
	ldr	w2, [x19, 4904]
	and	x1, x1, 4294967295
	cmp	w2, w3
	beq	.L113
	ldr	w2, [x19, 128]
	str	w3, [x19, 4904]
	umull	x2, w2, w3
	str	x2, [x19, 120]
.L113:
	mul	x0, x1, x0
	mov	x1, 4294967295
	cmp	x0, x1
	bls	.L115
	ldr	x1, .LC15
	ldr	x0, .LC16
	ldr	x1, [x1, 16]
	blr	x1
	ldp	w3, w4, [x19, 68]
	mov	w0, -1
.L115:
	ldr	w1, [x19, 4556]
	sub	w3, w3, #1
	cmp	w4, wzr
	add	w3, w3, w1
	udiv	w0, w0, w3
	str	w0, [x19, 4524]
	cset	w0, ne
	str	w0, [x19, 4576]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L121:
	ldr	w0, [x19, 4556]
	ldr	w5, [x19, 4536]
	ldr	w2, [x19, 4540]
	cmp	w0, w5
	ldr	w3, [x19, 68]
	csel	w0, w0, w5, ge
	cmp	w2, w0
	csel	w0, w2, w0, le
	cmp	w3, 1
	str	w0, [x19, 4556]
	bne	.L110
	mov	x0, 1
	str	w3, [x19, 4556]
	b	.L111
	.p2align 3
.L119:
	ldr	w1, [x19, 128]
	b	.L102
	.size	VEDU_DRV_RCGetTargetFrameBits_AVBR, .-VEDU_DRV_RCGetTargetFrameBits_AVBR
	.align	3
.LC15:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC16:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VENC_DRV_RcOpenOneFrm
	.type	VENC_DRV_RcOpenOneFrm, %function
VENC_DRV_RcOpenOneFrm:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L144
	ldr	w0, [x19, 4616]
	cbnz	w0, .L193
	ldr	w0, [x19, 20]
	cbnz	w0, .L194
	ldr	w0, [x19, 132]
	ldr	w1, [x19, 56]
	cbz	w0, .L143
	mov	x0, x19
	str	w1, [x19, 4884]
	bl	VEDU_DRV_RCCalculateCurQP_AVBR
	mov	x0, x19
	bl	VEDU_DRV_RCGetTimeOfP
	cmn	w0, #1
	beq	.L144
	mov	x0, x19
	bl	VEDU_DRV_RCGetTargetFrameBits_AVBR
.L140:
	ldr	w0, [x19, 104]
	cbz	w0, .L157
	ldr	w0, [x19, 4528]
	mov	w1, 23
	add	w0, w0, 1
	cmp	w0, 22
	bhi	.L195
.L158:
	str	wzr, [x19, 104]
	str	w1, [x19, 4528]
.L157:
	ldr	w1, [x19, 100]
	mov	w0, 0
	cbz	w1, .L125
	ldr	w1, [x19, 4528]
	add	w1, w1, 1
	str	w1, [x19, 4528]
.L125:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L193:
	ldr	w1, [x19, 4620]
	mov	w0, 0
	str	w1, [x19, 4520]
	lsr	w2, w1, 6
	add	w1, w1, 128
	str	w2, [x19, 4528]
	str	w1, [x19, 4452]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L143:
	ldr	w20, [x19, 4576]
	str	w1, [x19, 4884]
	cbnz	w20, .L196
.L145:
	ldr	w21, [x19, 28]
	ldr	w22, [x19, 4456]
	ldr	w3, [x19, 4936]
	mov	w0, w21
	mov	w2, w22
	bl	VEDU_DRV_RcModifyQPForLargeFrmBits.isra.1
	cmp	w21, w22
	bcs	.L197
	sub	w21, w22, w21
	lsl	w1, w21, 3
	sub	w1, w1, w21
	lsl	w1, w1, 3
	udiv	w1, w1, w22
	neg	w2, w1
.L147:
	ldr	w7, [x19, 4896]
	add	w2, w0, w2
	ldr	w6, [x19, 64]
	cmn	w2, #128
	ldr	w1, [x19, 4888]
	lsl	w4, w7, 5
	mov	w9, -128
	mov	w8, 256
	lsl	w5, w1, 5
	csel	w2, w2, w9, ge
	udiv	w4, w4, w6
	cmp	w2, w8
	csel	w2, w2, w8, le
	mov	w0, 63
	cmp	w4, wzr
	csel	w4, w4, wzr, ge
	udiv	w5, w5, w6
	cmp	w5, wzr
	csel	w5, w5, wzr, ge
	cmp	w5, 63
	csel	w5, w5, w0, le
	cmp	w4, w0
	csel	w4, w4, w0, le
	ldr	x0, .LC18
	cmp	w1, w7
	add	x0, x0, 808
	ldr	w5, [x0, w5, sxtw 2]
	ldr	w3, [x0, w4, sxtw 2]
	lsr	w0, w6, 4
	sub	w5, w5, w3
	bls	.L148
	sub	w3, w6, w0
	cmp	w7, w3
	bls	.L148
	lsl	w4, w5, 2
	sub	w3, w4, w5
	lsl	w3, w3, 1
	cmp	w3, w9
	csel	w3, w3, w9, ge
	cmp	w3, w8
	csel	w3, w3, w8, le
.L149:
	cmp	w6, w1
	add	w3, w2, w3
	bcs	.L150
	sub	w1, w1, w6
	lsl	w2, w1, 2
	sub	w2, w2, w1
	lsl	w2, w2, 5
	udiv	w0, w2, w6
.L151:
	cmn	w0, #64
	mov	w1, -64
	csel	w0, w0, w1, ge
	ldr	w2, [x19, 4572]
	ldr	w1, [x19, 4568]
	cmp	w0, 64
	mov	w4, 64
	csel	w0, w0, w4, le
	cmp	w1, w2
	add	w0, w0, w3
	bcs	.L152
	mov	w3, 60293
	sub	w2, w2, w1
	movk	w3, 0x51, lsl 16
	cmp	w2, w3
	bls	.L153
	mov	w2, 2147483647
	udiv	w1, w2, w1
.L155:
	cmn	w1, #32
	mov	w2, -32
	csel	w1, w1, w2, ge
	mov	w3, 32
	cmp	w1, w3
	ldr	w2, [x19, 4520]
	csel	w1, w1, w3, le
	add	w1, w1, w0
	add	w1, w1, w2
	str	w1, [x19, 4520]
	cbz	w20, .L156
	ldr	w0, [x19, 4452]
	cmp	w1, w0
	bcs	.L156
	ldr	w2, [x19, 68]
	cmp	w2, 1
	bls	.L156
	add	w1, w1, w0
	lsr	w1, w1, 1
	.p2align 2
.L156:
	ldp	w2, w3, [x19, 4]
	mov	x0, x19
	lsl	w2, w2, 6
	lsl	w3, w3, 6
	cmp	w2, w1
	csel	w1, w2, w1, cs
	cmp	w1, w3
	csel	w1, w1, w3, ls
	str	w1, [x19, 4520]
	lsr	w1, w1, 6
	str	w1, [x19, 4528]
	bl	VEDU_DRV_RCGetTimeOfP
	cmn	w0, #1
	beq	.L144
	mov	x0, x19
	bl	VEDU_DRV_RCGetTargetFrameBits
	b	.L140
	.p2align 3
.L194:
	ldr	w2, [x19, 4536]
	mov	w1, 8
	ldr	w3, [x19, 4540]
	mov	w0, 1
	cmp	w2, w1
	ldr	w4, [x19, 68]
	csel	w1, w2, w1, ge
	str	w0, [x19, 4560]
	cmp	w3, w1
	str	wzr, [x19, 4564]
	csel	w1, w3, w1, le
	cmp	w4, w0
	str	w1, [x19, 4556]
	beq	.L198
.L128:
	ldr	w2, [x19, 64]
	mov	w0, 1
	ldr	w3, [x19, 56]
	str	w0, [x19, 4576]
	lsl	w1, w2, 3
	add	w1, w1, w2, lsl 1
	ldr	w5, [x19, 104]
	udiv	w0, w2, w3
	lsr	w1, w1, 3
	str	w0, [x19, 128]
	str	w1, [x19, 4568]
	str	w1, [x19, 4572]
	str	w3, [x19, 4900]
	str	w4, [x19, 4904]
	str	w2, [x19, 4908]
	umull	x0, w0, w4
	str	x0, [x19, 120]
	lsr	x0, x0, 10
	str	w0, [x19, 144]
	cbz	w5, .L129
	str	wzr, [x19, 112]
.L129:
	ldr	x0, .LC17
	add	x20, x19, 4096
	str	w3, [x19, 4884]
	mov	w1, 0
	mov	x2, 260
	str	wzr, [x19, 4888]
	ldr	x3, [x0]
	add	x0, x20, 528
	str	wzr, [x19, 4892]
	str	wzr, [x19, 4896]
	blr	x3
	ldr	x0, [x19, 120]
	mov	x1, 4294967295
	cmp	x0, x1
	bls	.L130
	ldr	w1, [x19, 128]
	ldr	w3, [x19, 4556]
.L131:
	mul	w3, w1, w3
	ldr	w0, [x19, 4888]
	ldr	w2, [x19, 4884]
	str	w3, [x19, 4624]
	add	w3, w3, w0
	cmp	w2, 1
	str	w3, [x19, 4888]
	bls	.L132
	sub	w2, w2, #2
	add	x0, x20, 532
	mov	x4, x2
	add	x2, x2, 1158
	add	x2, x19, x2, lsl 2
	.p2align 2
.L133:
	str	w1, [x0], 4
	cmp	x2, x0
	bne	.L133
	madd	w1, w1, w4, w1
	add	w3, w3, w1
	str	w3, [x19, 4888]
.L132:
	mov	x0, x19
	str	w3, [x19, 4896]
	bl	VEDU_DRV_RCGetTargetFrameBits
	ldr	w0, [x19, 4524]
	mov	w3, 23592
	ldr	w1, [x19, 4556]
	movk	w3, 0x28f, lsl 16
	mov	w2, -1
	cmp	w0, w3
	str	w0, [x19, 4580]
	udiv	w1, w0, w1
	str	w0, [x19, 4584]
	str	w1, [x19, 4588]
	str	w1, [x19, 4592]
	str	w1, [x19, 4596]
	str	w1, [x19, 4600]
	str	w1, [x19, 4604]
	str	w2, [x19, 4608]
	str	w2, [x19, 4612]
	bls	.L199
	mov	w0, -96
	str	w3, [x19, 4524]
.L135:
	ldp	w1, w2, [x19, 12]
	mul	w2, w1, w2
	lsl	w1, w2, 2
	sub	w1, w1, w2
	lsr	w1, w1, 1
	udiv	w0, w0, w1
	cmp	w0, 170
	bhi	.L159
	sub	w1, w0, #121
	cmp	w1, 49
	bls	.L160
	sub	w1, w0, #81
	cmp	w1, 39
	bls	.L161
	sub	w1, w0, #41
	cmp	w1, 39
	bls	.L162
	sub	w1, w0, #16
	cmp	w1, 24
	bls	.L163
	sub	w1, w0, #6
	cmp	w1, 9
	bls	.L164
	sub	w0, w0, #3
	mov	w1, 2880
	cmp	w0, 2
	mov	w5, 2688
	csel	w5, w1, w5, hi
	mov	w6, 2560
	mov	w1, 2752
	mov	w2, 40
	csel	w6, w1, w6, hi
	mov	w1, 43
	csel	w0, w1, w2, hi
	b	.L136
	.p2align 3
.L195:
	mov	w1, 35
	cmp	w0, w1
	csel	w1, w0, w1, ls
	b	.L158
	.p2align 3
.L197:
	sub	w21, w21, w22
	lsl	w21, w21, 6
	udiv	w2, w21, w22
	b	.L147
	.p2align 3
.L196:
	mov	x0, x19
	bl	VEDU_DRV_RCModifyQPDeltaOfIP
	ldr	w20, [x19, 4576]
	ldr	w1, [x19, 56]
	b	.L145
	.p2align 3
.L148:
	cmp	w1, w7
	mov	w3, 0
	bcs	.L149
	add	w0, w6, w0
	cmp	w7, w0
	bcs	.L149
	lsl	w3, w5, 2
	mov	w4, -128
	cmp	w3, w4
	mov	w0, 256
	csel	w3, w3, w4, ge
	cmp	w3, w0
	csel	w3, w3, w0, le
	b	.L149
	.p2align 3
.L150:
	sub	w1, w6, w1
	lsl	w0, w1, 6
	add	w1, w0, w1, lsl 3
	udiv	w0, w1, w6
	neg	w0, w0
	b	.L151
	.p2align 3
.L152:
	sub	w2, w1, w2
	mov	w3, 400
	mul	w2, w2, w3
	udiv	w1, w2, w1
	neg	w1, w1
	b	.L155
	.p2align 3
.L130:
	ldr	w1, [x19, 68]
	ldr	w3, [x19, 4556]
	sub	w1, w1, #1
	add	w1, w1, w3
	udiv	w1, w0, w1
	b	.L131
	.p2align 3
.L159:
	mov	w5, 576
	mov	w6, 448
	mov	w0, 7
.L136:
	ldr	w2, [x19, 4564]
	ldr	w4, [x19, 4624]
	sub	w0, w0, w2
	ldr	w1, [x19, 68]
	mov	w2, -1
	ldr	w3, [x19, 4628]
	stp	w2, w2, [x19, 216]
	str	w0, [x19, 4528]
	add	x2, x19, 216
	str	w0, [x19, 4532]
	add	x0, x19, 184
	stp	w4, w4, [x19, 152]
	str	w5, [x19, 4452]
	str	w6, [x19, 4520]
	.p2align 2
.L137:
	str	w3, [x0], 4
	cmp	x2, x0
	bne	.L137
	add	x0, x19, 248
	add	x2, x19, 280
	.p2align 2
.L138:
	str	wzr, [x0]
	add	x0, x0, 4
	str	wzr, [x0, 28]
	str	wzr, [x0, 68]
	str	wzr, [x0, 100]
	cmp	x0, x2
	bne	.L138
	cmp	w1, 1000
	mov	w0, 1000
	csel	w0, w1, w0, ls
	ldr	x2, [x19, 120]
	mov	w1, 100
	cmp	w0, wzr
	str	w1, [x19, 312]
	str	w1, [x19, 316]
	str	wzr, [x19, 384]
	str	w0, [x19, 388]
	stp	x2, x2, [x19, 392]
	ble	.L140
	sub	w1, w0, #1
	add	x0, x19, 448
	add	x1, x1, 113
	add	x1, x19, x1, lsl 2
	.p2align 2
.L141:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L141
	b	.L140
	.p2align 3
.L199:
	lsl	w1, w0, 2
	sub	w1, w1, w0
	lsl	w2, w1, 5
	add	w1, w1, w2
	add	w0, w1, w0
	b	.L135
	.p2align 3
.L153:
	mov	w3, 400
	mul	w2, w2, w3
	udiv	w1, w2, w1
	b	.L155
	.p2align 3
.L161:
	mov	w5, 1408
	mov	w6, 1280
	mov	w0, 20
	b	.L136
	.p2align 3
.L198:
	str	w4, [x19, 4556]
	b	.L128
	.p2align 3
.L160:
	mov	w5, 1088
	mov	w6, 960
	mov	w0, 15
	b	.L136
	.p2align 3
.L144:
	mov	w0, -1
	b	.L125
.L162:
	mov	w5, 1728
	mov	w6, 1600
	mov	w0, 25
	b	.L136
.L163:
	mov	w5, 2048
	mov	w6, 1920
	mov	w0, 30
	b	.L136
.L164:
	mov	w5, 2560
	mov	w6, 2432
	mov	w0, 38
	b	.L136
	.size	VENC_DRV_RcOpenOneFrm, .-VENC_DRV_RcOpenOneFrm
	.align	3
.LC17:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC18:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VENC_DRV_EflRcAverage
	.type	VENC_DRV_EflRcAverage, %function
VENC_DRV_EflRcAverage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cbz	x20, .L205
	cmp	w19, wzr
	mov	w3, w19
	ble	.L206
	mov	x0, 0
	mov	w4, 0
	.p2align 2
.L204:
	ldr	w2, [x20, x0, lsl 2]
	add	x0, x0, 1
	cmp	w2, wzr
	add	w4, w4, w2
	cset	w2, eq
	cmp	w19, w0
	sub	w3, w3, w2
	bgt	.L204
.L202:
	mov	w0, 0
	cbz	w3, .L201
	sdiv	w0, w4, w3
.L201:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L205:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L206:
	mov	w4, 0
	b	.L202
	.size	VENC_DRV_EflRcAverage, .-VENC_DRV_EflRcAverage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VENC_DRV_RcCloseOneFrm
	.type	VENC_DRV_RcCloseOneFrm, %function
VENC_DRV_RcCloseOneFrm:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	mov	x22, x3
	bl	_mcount
	cmp	x20, xzr
	cset	w1, eq
	cmp	x19, xzr
	cset	w0, eq
	orr	w0, w1, w0
	cbnz	w0, .L243
	cmp	x21, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L243
	ldr	x0, [x19, 88]
	cbnz	x0, .L267
	str	wzr, [x19, 20]
	mov	w1, 0
	ldr	w2, [x19, 60]
	ldr	w0, [x21]
	sub	w0, w0, w2
	str	w0, [x21]
	ldr	w0, [x19, 72]
	cbz	w0, .L268
.L219:
	str	w1, [x22]
	ldr	w6, [x19, 28]
	cbz	x20, .L220
	ldr	x1, [x20]
	cbz	x1, .L220
	ldp	w0, w2, [x20, 16]
	cmp	w0, w2
	ldr	w2, [x20, 12]
	bhi	.L269
	mov	w0, 0
	add	x1, x1, x2, lsl 2
.L222:
	add	w0, w6, w0
	str	w0, [x20, 16]
	str	w6, [x1]
	ldp	w1, w0, [x20, 8]
	add	w0, w0, 1
	str	w0, [x20, 12]
	cmp	w0, w1
	bcc	.L266
	sub	w0, w0, w1
	str	w0, [x20, 12]
.L266:
	ldr	w6, [x19, 28]
.L220:
	ldr	w0, [x19, 108]
	cmp	w0, 1
	beq	.L224
	ldr	w1, [x19, 4464]
.L225:
	ldr	w0, [x19, 4468]
	add	x5, x19, 4096
	ldr	w2, [x19, 4472]
	ldr	w3, [x19, 4476]
	ldr	w4, [x19, 4480]
	ldr	w7, [x19, 4484]
	str	w0, [x19, 4472]
	adds	x0, x5, 372
	str	w1, [x19, 4468]
	str	w2, [x19, 4476]
	str	w3, [x19, 4480]
	str	w4, [x19, 4484]
	str	w7, [x19, 4488]
	beq	.L246
	add	x5, x5, 396
	mov	w3, 0
	mov	w2, 6
	b	.L229
	.p2align 3
.L270:
	ldr	w1, [x0]
.L229:
	cmp	w1, wzr
	add	x0, x0, 4
	cset	w4, eq
	cmp	x0, x5
	add	w3, w3, w1
	sub	w2, w2, w4
	bne	.L270
	mov	w0, 0
	cbz	w2, .L226
	sdiv	w0, w3, w2
.L226:
	ldr	w1, [x19, 132]
	str	w0, [x19, 4492]
	cbnz	w1, .L271
.L230:
	ldr	w0, [x19, 72]
	cbnz	w0, .L272
	ldr	w0, [x19, 4520]
	str	w0, [x19, 4452]
.L241:
	ldr	w0, [x19, 4524]
	str	w0, [x19, 4456]
	mov	w0, 0
	str	w6, [x19, 4460]
.L211:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L272:
	ldr	w0, [x19, 4520]
	str	w0, [x19, 4448]
	b	.L241
	.p2align 3
.L268:
	ldr	w1, [x22]
	add	w1, w1, 1
	b	.L219
	.p2align 3
.L269:
	ldr	w3, [x1, w2, uxtw 2]
	add	x1, x1, x2, uxtw 2
	sub	w0, w0, w3
	b	.L222
	.p2align 3
.L271:
	ldr	w0, [x19, 72]
	cbz	w0, .L231
	ldr	w0, [x19, 4528]
	add	x3, x19, 216
	ldr	w2, [x19, 156]
	ldr	w1, [x19, 220]
	stp	w1, w0, [x19, 216]
	stp	w2, w6, [x19, 152]
	mov	w0, w6
.L232:
	add	w4, w2, w0
	mov	w1, 0
	add	x0, x19, 184
	.p2align 2
.L235:
	ldr	w2, [x0], 4
	cmp	x3, x0
	add	w1, w1, w2
	bne	.L235
	ldr	w5, [x19, 384]
	ubfx	x2, x4, 1, 31
	ldr	w7, [x19, 388]
	ubfx	x1, x1, 3, 29
	add	w3, w5, 1
	add	x5, x19, x5, sxtw 2
	sub	w0, w7, #1
	cmp	w7, w3
	csel	w3, w3, wzr, gt
	sxtw	x4, w0
	str	w6, [x5, 448]
	cmp	w7, wzr
	str	w3, [x19, 384]
	madd	x4, x4, x1, x2
	ble	.L248
	uxtw	x3, w0
	mov	x1, 0
	add	x3, x3, 113
	add	x0, x19, 448
	add	x3, x19, x3, lsl 2
	.p2align 2
.L239:
	ldr	w2, [x0], 4
	cmp	x3, x0
	add	x1, x1, x2
	bne	.L239
	stp	x1, x4, [x19, 392]
	b	.L230
	.p2align 3
.L224:
	ldr	w1, [x19, 4492]
	str	w1, [x19, 4464]
	b	.L225
	.p2align 3
.L231:
	add	x0, x19, 188
	add	x3, x19, 216
	.p2align 2
.L233:
	ldr	w4, [x0]
	add	x0, x0, 4
	ldr	w2, [x0, 60]
	ldr	w1, [x0, 92]
	str	w4, [x0, -8]
	str	w2, [x0, 56]
	str	w1, [x0, 88]
	cmp	x0, x3
	bne	.L233
	ldp	w1, w0, [x19, 36]
	str	w0, [x19, 308]
	add	x4, x19, 352
	str	w6, [x19, 212]
	add	x0, x19, 324
	str	w1, [x19, 276]
	.p2align 2
.L234:
	ldr	w2, [x0]
	add	x0, x0, 4
	ldr	w1, [x0, 28]
	str	w2, [x0, -8]
	str	w1, [x0, 24]
	cmp	x4, x0
	bne	.L234
	ldp	w1, w4, [x19, 44]
	ldr	w6, [x19, 28]
	ldp	w2, w0, [x19, 152]
	str	w4, [x19, 348]
	str	w1, [x19, 380]
	b	.L232
	.p2align 3
.L246:
	mov	w0, 0
	b	.L226
	.p2align 3
.L243:
	mov	w0, -1
	b	.L211
.L267:
	ldp	w2, w0, [x19, 76]
	ldr	w5, [x19, 20]
	mov	w3, 2
	cmp	w2, wzr
	sub	w6, w0, #1
	cset	w4, eq
	cmp	w0, wzr
	csel	w3, w6, w3, ne
	ldr	w2, [x19, 84]
	cmp	w5, wzr
	cset	w0, ne
	sub	w2, w2, #1
	orr	w1, w1, w0
	str	w2, [x19, 84]
	stp	w4, w3, [x19, 76]
	cbnz	w1, .L215
	ldr	x0, [x20]
	cbz	x0, .L215
	ldp	w1, w2, [x20, 16]
	cmp	w1, w2
	bls	.L217
	ldr	w2, [x20, 12]
	ldr	w3, [x0, w2, uxtw 2]
	add	x0, x0, x2, uxtw 2
	sub	w1, w1, w3
	str	w1, [x20, 16]
.L218:
	str	wzr, [x0]
	ldp	w1, w0, [x20, 8]
	add	w0, w0, 1
	str	w0, [x20, 12]
	cmp	w0, w1
	bcc	.L215
	sub	w0, w0, w1
	str	w0, [x20, 12]
.L215:
	ldr	w1, [x19, 4460]
	mov	w0, -1
	str	w1, [x19, 28]
	b	.L211
.L248:
	mov	x1, 0
	stp	x1, x4, [x19, 392]
	b	.L230
.L217:
	ldr	w1, [x20, 12]
	str	wzr, [x20, 16]
	add	x0, x0, x1, lsl 2
	b	.L218
	.size	VENC_DRV_RcCloseOneFrm, .-VENC_DRV_RcCloseOneFrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCUpdateInfo
	.type	VEDU_DRV_RCUpdateInfo, %function
VEDU_DRV_RCUpdateInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L273
	ldr	w5, [x19, 4616]
	cbz	w5, .L276
	ldr	w0, [x19, 4892]
	cbnz	w0, .L277
	ldr	w0, [x19, 4884]
	sub	w0, w0, #1
	str	w0, [x19, 4892]
.L278:
	ldr	w0, [x19, 72]
	cbz	w0, .L281
	ldr	w1, [x19, 56]
	ldr	w0, [x19, 68]
	cmp	w0, w1, lsl 1
	bhi	.L290
.L281:
	ldr	w1, [x19, 4892]
	ldr	w0, [x19, 4524]
	ldr	w7, [x19, 4572]
	uxtw	x2, w1
	ldr	w3, [x19, 4900]
	add	x8, x2, 1156
	ldr	w4, [x19, 28]
	ldr	w6, [x19, 4884]
	add	w7, w0, w7
	cmp	w6, w3
	sub	w3, w4, w0
	ldr	w0, [x19, x8, lsl 2]
	sub	w7, w7, w0
	add	w3, w7, w3
	str	w3, [x19, 4572]
	bne	.L284
	ldr	w3, [x19, 4888]
	add	w1, w1, 1
.L285:
	add	x2, x2, 1156
	add	w3, w4, w3
	sub	w0, w3, w0
	str	w0, [x19, 4888]
	cmp	w6, w1
	str	w4, [x19, x2, lsl 2]
	csel	w1, w1, wzr, hi
	str	w1, [x19, 4892]
.L273:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L276:
	ldr	w0, [x19, 72]
	cbz	w0, .L279
	ldr	w1, [x19, 56]
	ldr	w0, [x19, 68]
	cmp	w0, w1, lsl 1
	bls	.L279
.L290:
	ldr	w0, [x19, 132]
	cbz	w0, .L273
	cbnz	w5, .L281
.L279:
	ldr	w0, [x19, 4572]
	ldr	w4, [x19, 28]
	ldr	w2, [x19, 4524]
	ldr	w6, [x19, 4884]
	add	w0, w4, w0
	ldr	w1, [x19, 4900]
	sub	w0, w0, w2
	str	w0, [x19, 4572]
	cmp	w6, w1
	beq	.L304
.L284:
	ldr	w2, [x19, 56]
	add	x1, x19, 4096
	ldr	w3, [x19, 64]
	add	x0, x1, 528
	add	x1, x1, 788
	udiv	w2, w3, w2
	.p2align 2
.L286:
	str	w2, [x0], 4
	cmp	x1, x0
	bne	.L286
	str	w3, [x19, 4888]
	mov	w1, 1
	str	wzr, [x19, 4892]
	str	w6, [x19, 4900]
	cbnz	w5, .L305
.L287:
	uxtw	x2, w5
	str	w3, [x19, 4896]
	add	x0, x2, 1156
	ldr	w0, [x19, x0, lsl 2]
	b	.L285
.L277:
	sub	w0, w0, #1
	str	w0, [x19, 4892]
	b	.L278
.L305:
	mov	x2, 0
	ldr	w0, [x19, 4624]
	b	.L285
.L304:
	ldr	w5, [x19, 4892]
	ldr	w3, [x19, 4888]
	add	w1, w5, 1
	b	.L287
	.size	VEDU_DRV_RCUpdateInfo, .-VEDU_DRV_RCUpdateInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCIsNeedRecoding
	.type	VEDU_DRV_RCIsNeedRecoding, %function
VEDU_DRV_RCIsNeedRecoding:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L314
	ldr	w0, [x19, 96]
	cbnz	w0, .L310
	ldr	x0, [x19, 88]
	ldr	w1, [x19, 4616]
	cbnz	x0, .L309
	cbnz	w1, .L310
	ldr	w0, [x19, 132]
	cbnz	w0, .L310
	ldr	w0, [x19, 72]
	ldr	w2, [x19, 4524]
	cbz	w0, .L311
	lsl	w0, w2, 2
	ldr	w3, [x19, 28]
	sub	w0, w0, w2
	cmp	w3, w0, lsr 1
	cset	w2, hi
.L312:
	mov	w0, -1
	cbnz	w2, .L309
.L307:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L309:
	add	w1, w1, 1
	str	w1, [x19, 4616]
	cmp	w1, wzr
	csetm	w0, eq
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L311:
	ldr	w0, [x19, 28]
	cmp	w0, w2, lsl 1
	cset	w2, hi
	b	.L312
	.p2align 3
.L310:
	mov	w0, -1
	str	wzr, [x19, 4616]
	b	.L307
.L314:
	mov	w0, -1
	b	.L307
	.size	VEDU_DRV_RCIsNeedRecoding, .-VEDU_DRV_RCIsNeedRecoding
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VEDU_DRV_RCStartQPChange
	.type	VEDU_DRV_RCStartQPChange, %function
VEDU_DRV_RCStartQPChange:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L324
	ldr	x1, [x19, 88]
	ldr	w0, [x19, 4524]
	cbnz	x1, .L327
	ldr	w3, [x19, 28]
.L321:
	cmp	w3, w0
	mov	w2, 0
	bcc	.L322
	.p2align 2
.L323:
	lsl	w1, w0, 2
	add	w2, w2, 1
	sub	w1, w1, w0
	lsl	w1, w1, 2
	sub	w0, w1, w0
	ubfx	x0, x0, 3, 26
	cmp	w3, w0
	bcs	.L323
	lsl	w2, w2, 6
.L322:
	ldp	w0, w1, [x19, 4]
	ldr	w3, [x19, 4520]
	lsl	w0, w0, 6
	lsl	w1, w1, 6
	add	w2, w3, w2
	cmp	w2, w0
	csel	w0, w2, w0, cs
	cmp	w1, w0
	csel	w0, w1, w0, ls
	str	w0, [x19, 4620]
	cmp	w3, w0
	csetm	w0, eq
.L319:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L327:
	ldr	w1, [x19, 24]
	ldr	w3, [x19, 4616]
	mul	w3, w1, w3
	b	.L321
.L324:
	mov	w0, -1
	b	.L319
	.size	VEDU_DRV_RCStartQPChange, .-VEDU_DRV_RCStartQPChange
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VENC_DRV_CalRCRatio
	.type	VENC_DRV_CalRCRatio, %function
VENC_DRV_CalRCRatio:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, w20
	bhi	.L331
	sub	w19, w20, w19
	lsl	w0, w19, 2
	sub	w0, w0, w19
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w0, w0, w19
	udiv	w0, w0, w20
	ldp	x19, x20, [sp, 16]
	neg	w0, w0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L331:
	sub	w19, w19, w20
	lsl	w0, w19, 2
	sub	w0, w0, w19
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w0, w0, w19
	udiv	w0, w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VENC_DRV_CalRCRatio, .-VENC_DRV_CalRCRatio
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	MaxIPropDeltaQP, %object
	.size	MaxIPropDeltaQP, 208
MaxIPropDeltaQP:
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	9
	.word	9
	.word	8
	.word	8
	.word	7
	.word	7
	.word	6
	.word	6
	.word	5
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	s32QPOffsetTab3.1870, %object
	.size	s32QPOffsetTab3.1870, 64
s32QPOffsetTab3.1870:
	.word	14
	.word	15
	.word	16
	.word	18
	.word	20
	.word	22
	.word	25
	.word	28
	.word	32
	.word	36
	.word	40
	.word	44
	.word	50
	.word	56
	.word	64
	.word	72
	.type	s32PercentTab0.1869, %object
	.size	s32PercentTab0.1869, 400
s32PercentTab0.1869:
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	95
	.word	90
	.word	85
	.word	80
	.word	75
	.word	72
	.word	69
	.word	66
	.word	64
	.word	62
	.word	60
	.word	58
	.word	57
	.word	56
	.word	55
	.word	54
	.word	53
	.word	52
	.word	51
	.word	50
	.word	49
	.word	48
	.word	47
	.word	47
	.word	46
	.word	46
	.word	45
	.word	45
	.word	44
	.word	44
	.word	43
	.word	43
	.word	43
	.word	42
	.word	42
	.word	42
	.word	41
	.word	41
	.word	41
	.word	40
	.word	40
	.word	40
	.word	39
	.word	39
	.word	39
	.word	38
	.word	38
	.word	38
	.word	37
	.word	37
	.word	37
	.word	37
	.word	37
	.word	37
	.word	37
	.word	36
	.word	36
	.word	36
	.word	36
	.word	36
	.word	36
	.word	36
	.word	35
	.word	35
	.word	35
	.word	34
	.word	34
	.word	34
	.word	34
	.word	34
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.type	s32QPOffsetTab2.1891, %object
	.size	s32QPOffsetTab2.1891, 64
s32QPOffsetTab2.1891:
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	13
	.word	14
	.word	16
	.word	18
	.word	20
	.word	22
	.word	25
	.word	28
	.word	32
	.word	36
	.type	s32PercentTab1.1890, %object
	.size	s32PercentTab1.1890, 68
s32PercentTab1.1890:
	.word	5
	.word	5
	.word	28
	.word	40
	.word	50
	.word	57
	.word	64
	.word	70
	.word	76
	.word	81
	.word	85
	.word	89
	.word	92
	.word	95
	.word	97
	.word	99
	.word	100
	.zero	4
	.type	TabLnx, %object
	.size	TabLnx, 256
TabLnx:
	.word	0
	.word	-1216
	.word	-972
	.word	-830
	.word	-729
	.word	-651
	.word	-587
	.word	-533
	.word	-486
	.word	-445
	.word	-408
	.word	-374
	.word	-344
	.word	-316
	.word	-290
	.word	-265
	.word	-243
	.word	-221
	.word	-201
	.word	-182
	.word	-164
	.word	-147
	.word	-131
	.word	-115
	.word	-100
	.word	-86
	.word	-72
	.word	-59
	.word	-46
	.word	-34
	.word	-22
	.word	-11
	.word	0
	.word	10
	.word	21
	.word	31
	.word	41
	.word	50
	.word	60
	.word	69
	.word	78
	.word	86
	.word	95
	.word	103
	.word	111
	.word	119
	.word	127
	.word	134
	.word	142
	.word	149
	.word	156
	.word	163
	.word	170
	.word	177
	.word	183
	.word	190
	.word	196
	.word	202
	.word	208
	.word	214
	.word	220
	.word	226
	.word	232
	.word	237
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC4:
	ASCII(.string	"u32BitsPerGop > 0xffffffff!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
