#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vp9.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VP9_u_v_x
	.type	VP9_u_v_x, %function
VP9_u_v_x:
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
	.size	VP9_u_v_x, .-VP9_u_v_x
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_s_v
	.type	VP9_s_v, %function
VP9_s_v:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	w1, w20, 1
	mov	x0, x19
	bl	BsGet
	tbnz	x0, 0, .L6
	asr	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L6:
	neg	w0, w0, asr 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_s_v, .-VP9_s_v
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_ReadIsValid
	.type	Vp9_Cabac_ReadIsValid, %function
Vp9_Cabac_ReadIsValid:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	w19, w1
	bl	_mcount
	cmp	x20, xzr
	mov	w0, 0
	ccmp	x21, xzr, 4, ne
	beq	.L8
	add	x1, x20, x19, uxtw
	cmp	x21, x1
	ccmp	x20, x1, 2, cs
	cset	w0, cc
.L8:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_Cabac_ReadIsValid, .-Vp9_Cabac_ReadIsValid
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_ReaderFill
	.type	Vp9_Cabac_ReaderFill, %function
Vp9_Cabac_ReaderFill:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	w19, 24
	mov	w20, 16
	bl	_mcount
	ldp	w22, w23, [x21, 36]
	mov	x0, x21
	sub	w19, w19, w23
	sub	w20, w20, w23
	and	w19, w19, -8
	mov	w1, w19
	sub	w20, w20, w19
	and	w20, w20, 7
	add	w19, w23, w19
	bl	BsGet
	lsl	w0, w0, w20
	orr	w20, w0, w22
	stp	w20, w19, [x21, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_Cabac_ReaderFill, .-Vp9_Cabac_ReaderFill
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_Read
	.type	Vp9_Cabac_Read, %function
Vp9_Cabac_Read:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	ldp	w22, w19, [x20, 40]
	sub	w19, w19, #1
	mul	w19, w19, w21
	lsr	w19, w19, 8
	add	w19, w19, 1
	tbnz	w22, #31, .L12
	ldr	w1, [x20, 36]
.L13:
	lsl	w2, w19, 24
	mov	w0, 0
	cmp	w2, w1
	bhi	.L14
	ldr	w3, [x20, 44]
	sub	w1, w1, w2
	mov	w0, 1
	sub	w19, w3, w19
.L14:
	ldr	x2, .LC0
	ldrb	w2, [x2, w19, uxtw]
	sub	w22, w22, w2
	lsl	w19, w19, w2
	lsl	w1, w1, w2
	str	w19, [x20, 44]
	stp	w1, w22, [x20, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L12:
	mov	w1, 24
	mov	w23, 16
	sub	w1, w1, w22
	sub	w23, w23, w22
	and	w1, w1, -8
	mov	x0, x20
	sub	w23, w23, w1
	ldr	w21, [x20, 36]
	and	w23, w23, 7
	add	w22, w22, w1
	bl	BsGet
	lsl	w0, w0, w23
	orr	w1, w0, w21
	b	.L13
	.size	Vp9_Cabac_Read, .-Vp9_Cabac_Read
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_ReadLiteral
	.type	Vp9_Cabac_ReadLiteral, %function
Vp9_Cabac_ReadLiteral:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w25, w1
	bl	_mcount
	subs	w25, w25, #1
	bmi	.L21
	ldr	x27, .LC1
	mov	w26, 0
	mov	w24, 24
	mov	w23, 1
	ldp	w20, w21, [x22, 36]
	ldr	w19, [x22, 44]
	b	.L20
	.p2align 3
.L18:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L19
	ldr	w2, [x22, 44]
	lsl	w0, w23, w25
	sub	w20, w20, w1
	sub	w19, w2, w19
.L19:
	orr	w26, w26, w0
	ldrb	w0, [x27, w19, uxtw]
	sub	w25, w25, #1
	lsl	w20, w20, w0
	sub	w21, w21, w0
	lsl	w19, w19, w0
	cmn	w25, #1
	stp	w20, w21, [x22, 36]
	str	w19, [x22, 44]
	beq	.L17
.L20:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w21, #31, .L18
	sub	w1, w24, w21
	mov	w0, 16
	sub	w28, w0, w21
	and	w1, w1, -8
	sub	w28, w28, w1
	mov	x0, x22
	and	w28, w28, 7
	add	w21, w1, w21
	bl	BsGet
	lsl	w0, w0, w28
	orr	w20, w0, w20
	b	.L18
.L21:
	mov	w26, 0
.L17:
	mov	w0, w26
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.size	Vp9_Cabac_ReadLiteral, .-Vp9_Cabac_ReadLiteral
	.align	3
.LC1:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Cabac_ReaderInit
	.type	Vp9_Cabac_ReaderInit, %function
Vp9_Cabac_ReaderInit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, -8
	mov	w1, 32
	stp	wzr, w0, [x19, 36]
	mov	w0, 255
	str	w0, [x19, 44]
	mov	x0, x19
	bl	BsGet
	mov	w2, w0
	ldr	w3, [x19, 44]
	sub	w1, w3, #1
	ubfx	x1, x1, 1, 24
	add	w1, w1, 1
	lsl	w0, w1, 24
	cmp	w0, w2
	bhi	.L27
	sub	w2, w2, w0
	sub	w1, w3, w1
	mov	w0, 1
.L26:
	ldr	x4, .LC2
	mov	w3, 24
	ldrb	w4, [x4, w1, uxtw]
	lsl	w2, w2, w4
	sub	w3, w3, w4
	lsl	w1, w1, w4
	str	w1, [x19, 44]
	stp	w2, w3, [x19, 36]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L27:
	mov	w0, 0
	b	.L26
	.size	Vp9_Cabac_ReaderInit, .-Vp9_Cabac_ReaderInit
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadTxMode
	.type	Vp9_ReadTxMode, %function
Vp9_ReadTxMode:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	w23, 1
	mov	w24, 0
	bl	_mcount
	ldr	x25, .LC3
	ldp	w20, w22, [x21, 36]
	ldr	w19, [x21, 44]
	mov	w3, 24
	mov	w28, 16
	mov	w26, w23
.L31:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w22, #31, .L39
.L29:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L30
	ldr	w2, [x21, 44]
	lsl	w0, w26, w23
	sub	w20, w20, w1
	sub	w19, w2, w19
.L30:
	orr	w24, w24, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w23, w23, #1
	lsl	w20, w20, w0
	sub	w22, w22, w0
	lsl	w19, w19, w0
	cmn	w23, #1
	stp	w20, w22, [x21, 36]
	str	w19, [x21, 44]
	bne	.L31
	cmp	w24, 3
	beq	.L40
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L39:
	sub	w1, w3, w22
	sub	w27, w28, w22
	and	w1, w1, -8
	mov	x0, x21
	sub	w27, w27, w1
	str	w3, [x29, 108]
	and	w27, w27, 7
	add	w22, w1, w22
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldr	w3, [x29, 108]
	b	.L29
	.p2align 3
.L40:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w22, #31, .L41
.L33:
	lsl	w0, w19, 24
	cmp	w0, w20
	bhi	.L34
	ldr	w1, [x21, 44]
	sub	w20, w20, w0
	mov	w24, 4
	sub	w19, w1, w19
.L34:
	ldrb	w0, [x25, w19, uxtw]
	lsl	w20, w20, w0
	sub	w22, w22, w0
	lsl	w19, w19, w0
	str	w19, [x21, 44]
	stp	w20, w22, [x21, 36]
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L41:
	mov	w1, 24
	mov	w23, 16
	sub	w1, w1, w22
	sub	w23, w23, w22
	and	w1, w1, -8
	mov	x0, x21
	sub	w23, w23, w1
	add	w22, w22, w1
	and	w23, w23, 7
	bl	BsGet
	lsl	w0, w0, w23
	orr	w20, w0, w20
	b	.L33
	.size	Vp9_ReadTxMode, .-Vp9_ReadTxMode
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReaderHasError
	.type	Vp9_ReaderHasError, %function
Vp9_ReaderHasError:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 40]
	mov	w1, 65502
	movk	w1, 0x3fff, lsl 16
	ldr	x19, [sp, 16]
	sub	w0, w0, #33
	cmp	w0, w1
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_ReaderHasError, .-Vp9_ReaderHasError
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_DiffUpdateProb
	.type	Vp9_DiffUpdateProb, %function
Vp9_DiffUpdateProb:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldp	w24, w19, [x22, 40]
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L44
	ldr	w20, [x22, 36]
.L45:
	lsl	w1, w19, 24
	cmp	w1, w20
	bhi	.L46
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	ldr	x23, .LC4
	sub	w19, w0, w19
	ldrb	w0, [x23, w19, uxtw]
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	tbnz	w24, #31, .L93
.L48:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w0, w19, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L53
	ldr	w19, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w19, w0
	ldrb	w0, [x23, w19, uxtw]
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	tbnz	w24, #31, .L94
.L55:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L59
	ldr	w19, [x22, 44]
	sub	w20, w20, w1
	mov	w26, 0
	mov	w25, 6
	sub	w0, w19, w0
	mov	w2, 24
	mov	w28, 16
	mov	w3, 1
	ldrb	w19, [x23, w0, uxtw]
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	b	.L60
	.p2align 3
.L64:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L65
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w3, w25
.L65:
	orr	w26, w26, w0
	ldrb	w0, [x23, w19, uxtw]
	sub	w25, w25, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w25, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	beq	.L95
.L60:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbz	w24, #31, .L64
	sub	w1, w2, w24
	sub	w27, w28, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w3, w2, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w3, w2, [x29, 104]
	b	.L64
	.p2align 3
.L46:
	uxtw	x0, w19
	ldr	x23, .LC4
	mov	w25, 0
	mov	w26, 3
	mov	w28, 24
	mov	w4, 16
	ldrb	w0, [x23, x0]
	mov	w3, 1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
.L51:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L96
.L49:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L50
	ldr	w2, [x22, 44]
	lsl	w0, w3, w26
	sub	w20, w20, w1
	sub	w19, w2, w19
.L50:
	orr	w25, w25, w0
	ldrb	w0, [x23, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L51
.L52:
	ldrb	w1, [x21]
	add	x23, x23, 256
	sub	w1, w1, #1
	lsl	w3, w1, 1
	ldrb	w2, [x23, w25, sxtw]
	cmp	w3, 255
	bgt	.L69
	add	w0, w2, 1
	cmp	w0, w3
	bgt	.L70
	tbnz	x0, 0, .L97
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L70:
	add	w0, w0, 1
	strb	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L69:
	mov	w0, 254
	add	w3, w2, 1
	sub	w1, w0, w1
	cmp	w3, w1, lsl 1
	ble	.L98
.L73:
	mov	w0, 255
	sub	w0, w0, w3
.L100:
	strb	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L98:
	tbnz	x3, 0, .L99
	add	w0, w3, w3, lsr 31
	add	w3, w1, w0, asr 1
	mov	w0, 255
	sub	w0, w0, w3
	b	.L100
	.p2align 3
.L53:
	uxtw	x1, w0
	mov	w25, 0
	mov	w26, 3
	mov	w28, 24
	mov	w3, 16
	mov	w2, 1
	ldrb	w19, [x23, x1]
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
.L58:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L101
.L56:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L57
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w2, w26
.L57:
	orr	w25, w25, w0
	ldrb	w0, [x23, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L58
	add	w25, w25, 16
	b	.L52
	.p2align 3
.L96:
	sub	w1, w28, w24
	sub	w27, w4, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w3, w4, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w3, w4, [x29, 104]
	b	.L49
	.p2align 3
.L97:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L70
	.p2align 3
.L99:
	add	w2, w2, 2
	sub	w3, w1, w2, lsr 1
	b	.L73
	.p2align 3
.L44:
	mov	w23, 24
	mov	w25, 16
	sub	w23, w23, w24
	sub	w25, w25, w24
	and	w23, w23, -8
	mov	x0, x22
	mov	w1, w23
	sub	w25, w25, w23
	ldr	w20, [x22, 36]
	and	w25, w25, 7
	bl	BsGet
	lsl	w0, w0, w25
	add	w24, w24, w23
	orr	w20, w0, w20
	stp	w20, w24, [x22, 36]
	b	.L45
	.p2align 3
.L101:
	sub	w1, w28, w24
	sub	w27, w3, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w2, w3, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w2, w3, [x29, 104]
	b	.L56
	.p2align 3
.L59:
	uxtw	x1, w0
	mov	w25, 0
	mov	w26, 4
	mov	w2, 24
	mov	w3, 16
	mov	w28, 1
	ldrb	w19, [x23, x1]
	lsl	w20, w20, w19
	sub	w24, w24, w19
	lsl	w19, w0, w19
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	.p2align 2
.L63:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w24, #31, .L102
.L61:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L62
	ldr	w0, [x22, 44]
	sub	w20, w20, w1
	sub	w19, w0, w19
	lsl	w0, w28, w26
.L62:
	orr	w25, w25, w0
	ldrb	w0, [x23, w19, uxtw]
	sub	w26, w26, #1
	lsl	w20, w20, w0
	sub	w24, w24, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w20, w24, [x22, 36]
	str	w19, [x22, 44]
	bne	.L63
	add	w25, w25, 32
	b	.L52
	.p2align 3
.L102:
	sub	w1, w2, w24
	sub	w27, w3, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w27, w27, w1
	add	w24, w1, w24
	and	w27, w27, 7
	stp	w2, w3, [x29, 104]
	bl	BsGet
	lsl	w0, w0, w27
	orr	w20, w0, w20
	ldp	w2, w3, [x29, 104]
	b	.L61
	.p2align 3
.L93:
	mov	w26, 24
	mov	w25, 16
	sub	w26, w26, w24
	sub	w25, w25, w24
	and	w26, w26, -8
	mov	x0, x22
	mov	w1, w26
	sub	w25, w25, w26
	and	w25, w25, 7
	add	w24, w26, w24
	bl	BsGet
	lsl	w0, w0, w25
	orr	w20, w0, w20
	stp	w20, w24, [x22, 36]
	b	.L48
.L95:
	cmp	w26, 64
	mov	w25, w26
	bgt	.L103
	add	w25, w25, 64
	b	.L52
.L103:
	sub	w19, w19, #1
	lsl	w25, w26, 1
	ubfx	x19, x19, 1, 24
	sub	w25, w25, #65
	add	w19, w19, 1
	tbnz	w24, #31, .L104
.L67:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L68
	ldr	w2, [x22, 44]
	sub	w20, w20, w1
	mov	w0, 1
	sub	w19, w2, w19
.L68:
	ldrb	w1, [x23, w19, uxtw]
	add	w25, w25, w0
	add	w25, w25, 64
	lsl	w20, w20, w1
	sub	w24, w24, w1
	lsl	w19, w19, w1
	str	w19, [x22, 44]
	stp	w20, w24, [x22, 36]
	b	.L52
.L94:
	mov	w26, 24
	mov	w25, 16
	sub	w26, w26, w24
	sub	w25, w25, w24
	and	w26, w26, -8
	mov	x0, x22
	mov	w1, w26
	sub	w25, w25, w26
	and	w25, w25, 7
	add	w24, w26, w24
	bl	BsGet
	lsl	w0, w0, w25
	orr	w20, w0, w20
	stp	w20, w24, [x22, 36]
	b	.L55
.L104:
	mov	w1, 24
	mov	w26, 16
	sub	w1, w1, w24
	sub	w26, w26, w24
	and	w1, w1, -8
	mov	x0, x22
	sub	w26, w26, w1
	add	w24, w24, w1
	and	w26, w26, 7
	bl	BsGet
	lsl	w0, w0, w26
	orr	w20, w0, w20
	b	.L67
	.size	Vp9_DiffUpdateProb, .-Vp9_DiffUpdateProb
	.align	3
.LC4:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadTxProbs
	.type	Vp9_ReadTxProbs, %function
Vp9_ReadTxProbs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x1
	mov	x22, x0
	mov	x0, x30
	mov	x28, 0
	mov	w23, 24
	mov	w21, 16
	bl	_mcount
	ldr	x27, .LC8
	ldp	w26, w20, [x19, 36]
	ldr	w1, [x19, 44]
	mov	w24, 1
.L136:
	sub	w1, w1, #1
	lsl	w25, w1, 6
	sub	w1, w25, w1
	ubfx	x1, x1, 6, 24
	add	w25, w1, 1
	tbnz	w20, #31, .L259
.L106:
	lsl	w0, w25, 24
	cmp	w0, w26
	bhi	.L107
	ldr	w1, [x19, 44]
	sub	w26, w26, w0
	sub	w1, w1, w25
	ldrb	w25, [x27, w1, uxtw]
	lsl	w26, w26, w25
	sub	w20, w20, w25
	lsl	w25, w1, w25
	str	w25, [x19, 44]
	stp	w26, w20, [x19, 36]
	tbnz	w20, #31, .L260
.L108:
	sub	w1, w25, #1
	ubfx	x25, x1, 1, 24
	add	w1, w25, 1
	lsl	w0, w1, 24
	cmp	w0, w26
	bhi	.L109
	ldr	w25, [x19, 44]
	sub	w26, w26, w0
	sub	w25, w25, w1
	ldrb	w1, [x27, w25, uxtw]
	lsl	w26, w26, w1
	sub	w20, w20, w1
	lsl	w25, w25, w1
	str	w25, [x19, 44]
	stp	w26, w20, [x19, 36]
	tbnz	w20, #31, .L261
.L111:
	sub	w25, w25, #1
	ubfx	x0, x25, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L116
	sub	w25, w26, w1
	ldr	w1, [x19, 44]
	sub	w0, w1, w0
	ldrb	w1, [x27, w0, uxtw]
	sub	w3, w20, w1
	lsl	w25, w25, w1
	lsl	w20, w0, w1
	str	w20, [x19, 44]
	stp	w25, w3, [x19, 36]
	tbnz	w3, #31, .L262
.L118:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w25
	bhi	.L122
	sub	w25, w25, w1
	ldr	w1, [x19, 44]
	mov	w26, 0
	mov	w4, 6
	sub	w0, w1, w0
	ldrb	w20, [x27, w0, uxtw]
	lsl	w25, w25, w20
	sub	w3, w3, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w25, w3, [x19, 36]
	b	.L123
	.p2align 3
.L127:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w25
	bhi	.L128
	ldr	w0, [x19, 44]
	sub	w25, w25, w1
	sub	w20, w0, w20
	lsl	w0, w24, w4
.L128:
	orr	w26, w26, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w4, w4, #1
	lsl	w25, w25, w0
	sub	w3, w3, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w25, w3, [x19, 36]
	str	w20, [x19, 44]
	beq	.L263
.L123:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w3, #31, .L127
	sub	w1, w23, w3
	sub	w5, w21, w3
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w4, w5, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w3, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w25, w0, w25
	b	.L127
	.p2align 3
.L107:
	uxtw	x0, w25
	ldrb	w1, [x27, x0]
	lsl	w26, w26, w1
	sub	w20, w20, w1
	lsl	w1, w25, w1
	str	w1, [x19, 44]
	stp	w26, w20, [x19, 36]
.L206:
	add	x28, x28, 1
	cmp	x28, 2
	bne	.L136
	add	x28, x22, 3
	add	x23, x22, 7
	mov	w25, 24
	mov	w24, 16
.L141:
	sub	w1, w1, #1
	lsl	w21, w1, 6
	sub	w1, w21, w1
	ubfx	x21, x1, 6, 24
	add	w21, w21, 1
	tbnz	w20, #31, .L264
.L137:
	lsl	w0, w21, 24
	cmp	w0, w26
	bhi	.L138
	ldr	w2, [x19, 44]
	sub	w26, w26, w0
	sub	x1, x28, #1
	mov	x0, x19
	sub	w21, w2, w21
	ldrb	w2, [x27, w21, uxtw]
	lsl	w26, w26, w2
	sub	w20, w20, w2
	lsl	w21, w21, w2
	str	w21, [x19, 44]
	stp	w26, w20, [x19, 36]
	bl	Vp9_DiffUpdateProb
	ldr	w1, [x19, 44]
	ldp	w26, w20, [x19, 36]
	sub	w1, w1, #1
	lsl	w0, w1, 6
	sub	w1, w0, w1
	ubfx	x1, x1, 6, 24
	add	w21, w1, 1
	tbnz	w20, #31, .L265
.L139:
	lsl	w0, w21, 24
	cmp	w0, w26
	bhi	.L140
	ldr	w2, [x19, 44]
	sub	w26, w26, w0
	mov	x1, x28
	mov	x0, x19
	sub	w21, w2, w21
	ldrb	w2, [x27, w21, uxtw]
	lsl	w26, w26, w2
	sub	w20, w20, w2
	lsl	w21, w21, w2
	str	w21, [x19, 44]
	stp	w26, w20, [x19, 36]
	bl	Vp9_DiffUpdateProb
	ldr	w1, [x19, 44]
	ldp	w26, w20, [x19, 36]
.L208:
	add	x28, x28, 2
	cmp	x23, x28
	bne	.L141
	sub	w1, w1, #1
	add	x28, x22, 8
	lsl	w2, w1, 6
	add	x22, x22, 14
	sub	w1, w2, w1
	mov	w24, 24
	ubfx	x1, x1, 6, 24
	mov	w23, 16
	mov	w21, 1
	mov	w25, 254
	add	w2, w1, 1
	tbnz	w20, #31, .L266
.L142:
	lsl	w0, w2, 24
	cmp	w0, w26
	bhi	.L143
	ldr	w1, [x19, 44]
	sub	w26, w26, w0
	sub	w1, w1, w2
	ldrb	w0, [x27, w1, uxtw]
	lsl	w2, w26, w0
	sub	w20, w20, w0
	lsl	w26, w1, w0
	str	w26, [x19, 44]
	stp	w2, w20, [x19, 36]
	tbnz	w20, #31, .L267
.L144:
	sub	w1, w26, #1
	ubfx	x1, x1, 1, 24
	add	w1, w1, 1
	lsl	w0, w1, 24
	cmp	w0, w2
	bhi	.L145
	sub	w26, w2, w0
	ldr	w0, [x19, 44]
	sub	w1, w0, w1
	ldrb	w0, [x27, w1, uxtw]
	sub	w2, w20, w0
	lsl	w26, w26, w0
	lsl	w20, w1, w0
	str	w20, [x19, 44]
	stp	w26, w2, [x19, 36]
	tbnz	w2, #31, .L268
.L147:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L152
	sub	w26, w26, w1
	ldr	w1, [x19, 44]
	sub	w0, w1, w0
	ldrb	w20, [x27, w0, uxtw]
	lsl	w26, w26, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w26, w2, [x19, 36]
	tbnz	w2, #31, .L269
.L154:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L158
	sub	w26, w26, w1
	ldr	w1, [x19, 44]
	mov	w3, 0
	mov	w4, 6
	sub	w0, w1, w0
	ldrb	w20, [x27, w0, uxtw]
	lsl	w26, w26, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w26, w2, [x19, 36]
	b	.L159
	.p2align 3
.L163:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L164
	ldr	w0, [x19, 44]
	sub	w26, w26, w1
	sub	w20, w0, w20
	lsl	w0, w21, w4
.L164:
	orr	w3, w3, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w26, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L270
.L159:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L163
	sub	w1, w24, w2
	sub	w5, w23, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L163
	.p2align 3
.L140:
	uxtw	x0, w21
	ldrb	w1, [x27, x0]
	lsl	w26, w26, w1
	sub	w20, w20, w1
	lsl	w1, w21, w1
	str	w1, [x19, 44]
	stp	w26, w20, [x19, 36]
	b	.L208
	.p2align 3
.L138:
	uxtw	x0, w21
	ldrb	w1, [x27, x0]
	lsl	w26, w26, w1
	sub	w20, w20, w1
	lsl	w1, w21, w1
	str	w1, [x19, 44]
	sub	w1, w1, #1
	lsl	w0, w1, 6
	sub	w1, w0, w1
	stp	w26, w20, [x19, 36]
	ubfx	x1, x1, 6, 24
	add	w21, w1, 1
	tbz	w20, #31, .L139
.L265:
	sub	w3, w25, w20
	sub	w2, w24, w20
	and	w3, w3, -8
	mov	x0, x19
	sub	w2, w2, w3
	mov	w1, w3
	stp	w2, w3, [x29, 104]
	bl	BsGet
	ldp	w2, w3, [x29, 104]
	and	w2, w2, 7
	add	w20, w3, w20
	lsl	w0, w0, w2
	orr	w26, w0, w26
	stp	w26, w20, [x19, 36]
	b	.L139
	.p2align 3
.L143:
	uxtw	x0, w2
	ldrb	w1, [x27, x0]
	lsl	w3, w26, w1
	sub	w26, w20, w1
	lsl	w1, w2, w1
	str	w1, [x19, 44]
	sub	w1, w1, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	stp	w3, w26, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w26, #31, .L271
.L172:
	lsl	w1, w20, 24
	cmp	w1, w3
	bhi	.L173
	ldr	w0, [x19, 44]
	sub	w1, w3, w1
	sub	w0, w0, w20
	ldrb	w2, [x27, w0, uxtw]
	sub	w4, w26, w2
	lsl	w20, w1, w2
	lsl	w26, w0, w2
	str	w26, [x19, 44]
	stp	w20, w4, [x19, 36]
	tbnz	w4, #31, .L272
.L174:
	sub	w0, w26, #1
	ubfx	x26, x0, 1, 24
	add	w0, w26, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L175
	ldr	w26, [x19, 44]
	sub	w20, w20, w1
	sub	w26, w26, w0
	ldrb	w0, [x27, w26, uxtw]
	lsl	w3, w20, w0
	sub	w4, w4, w0
	lsl	w26, w26, w0
	str	w26, [x19, 44]
	stp	w3, w4, [x19, 36]
	tbnz	w4, #31, .L273
.L177:
	sub	w26, w26, #1
	ubfx	x20, x26, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w3
	bhi	.L182
	sub	w26, w3, w1
	ldr	w1, [x19, 44]
	sub	w0, w1, w0
	ldrb	w20, [x27, w0, uxtw]
	lsl	w26, w26, w20
	sub	w4, w4, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w26, w4, [x19, 36]
	tbnz	w4, #31, .L274
.L184:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L188
	ldr	w20, [x19, 44]
	sub	w1, w26, w1
	mov	w3, 0
	mov	w5, 6
	sub	w0, w20, w0
	ldrb	w20, [x27, w0, uxtw]
	lsl	w26, w1, w20
	sub	w2, w4, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w26, w2, [x19, 36]
	b	.L189
	.p2align 3
.L193:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L194
	ldr	w0, [x19, 44]
	sub	w26, w26, w1
	sub	w20, w0, w20
	lsl	w0, w21, w5
.L194:
	orr	w3, w3, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w5, w5, #1
	lsl	w26, w26, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w26, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L275
.L189:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L193
	sub	w1, w24, w2
	sub	w4, w23, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w3, w5, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w3, w5, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w26, w0, w26
	b	.L193
	.p2align 3
.L173:
	uxtw	x0, w20
	ldrb	w0, [x27, x0]
	sub	w4, w26, w0
	lsl	w2, w3, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	stp	w2, w4, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w26, w0, 1
	tbnz	w4, #31, .L276
.L202:
	lsl	w0, w26, 24
	cmp	w0, w2
	bhi	.L203
	ldr	w3, [x19, 44]
	sub	w2, w2, w0
	mov	x1, x28
	mov	x0, x19
	sub	w3, w3, w26
	ldrb	w5, [x27, w3, uxtw]
	lsl	w2, w2, w5
	sub	w4, w4, w5
	lsl	w3, w3, w5
	str	w3, [x19, 44]
	stp	w2, w4, [x19, 36]
	bl	Vp9_DiffUpdateProb
.L211:
	add	x28, x28, 3
	cmp	x22, x28
	beq	.L105
	ldr	w1, [x19, 44]
	ldp	w26, w20, [x19, 36]
	sub	w1, w1, #1
	lsl	w2, w1, 6
	sub	w1, w2, w1
	ubfx	x1, x1, 6, 24
	add	w2, w1, 1
	tbz	w20, #31, .L142
.L266:
	sub	w4, w24, w20
	sub	w3, w23, w20
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w20, w4, w20
	orr	w26, w0, w26
	stp	w26, w20, [x19, 36]
	b	.L142
	.p2align 3
.L105:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L203:
	uxtw	x0, w26
	ldrb	w0, [x27, x0]
	lsl	w2, w2, w0
	sub	w1, w4, w0
	lsl	w0, w26, w0
	str	w0, [x19, 44]
	stp	w2, w1, [x19, 36]
	b	.L211
	.p2align 3
.L145:
	uxtw	x0, w1
	mov	w3, 0
	mov	w5, 3
	ldrb	w0, [x27, x0]
	lsl	w26, w2, w0
	sub	w2, w20, w0
	lsl	w20, w1, w0
	str	w20, [x19, 44]
	stp	w26, w2, [x19, 36]
.L150:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L277
.L148:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L149
	ldr	w0, [x19, 44]
	sub	w26, w26, w1
	sub	w20, w0, w20
	lsl	w0, w21, w5
.L149:
	orr	w3, w3, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w5, w5, #1
	lsl	w26, w26, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w26, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L150
.L151:
	add	x0, x27, 256
	ldrb	w2, [x0, w3, sxtw]
	ldrb	w0, [x28, -2]
	sub	w0, w0, #1
	lsl	w3, w0, 1
	cmp	w3, 255
	bgt	.L166
	add	w1, w2, 1
	cmp	w1, w3
	bgt	.L167
	tbnz	x1, 0, .L278
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L167:
	add	w1, w1, 1
.L169:
	strb	w1, [x28, -2]
	ldr	w1, [x19, 44]
	ldp	w3, w26, [x19, 36]
	sub	w1, w1, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbz	w26, #31, .L172
.L271:
	sub	w4, w24, w26
	sub	w5, w23, w26
	and	w4, w4, -8
	mov	x0, x19
	sub	w5, w5, w4
	mov	w1, w4
	stp	w3, w5, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w3, w5, [x29, 100]
	ldr	w4, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	add	w4, w4, w26
	orr	w2, w0, w3
	mov	w26, w4
	mov	w3, w2
	stp	w2, w4, [x19, 36]
	b	.L172
	.p2align 3
.L109:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w25, [x27, x0]
	lsl	w26, w26, w25
	sub	w20, w20, w25
	lsl	w25, w1, w25
	str	w25, [x19, 44]
	stp	w26, w20, [x19, 36]
.L114:
	sub	w25, w25, #1
	ubfx	x25, x25, 1, 24
	add	w25, w25, 1
	tbnz	w20, #31, .L279
.L112:
	lsl	w1, w25, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L113
	ldr	w0, [x19, 44]
	sub	w26, w26, w1
	sub	w25, w0, w25
	lsl	w0, w24, w4
.L113:
	orr	w3, w3, w0
	ldrb	w0, [x27, w25, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w20, w20, w0
	lsl	w25, w25, w0
	cmn	w4, #1
	stp	w26, w20, [x19, 36]
	str	w25, [x19, 44]
	bne	.L114
.L115:
	add	x0, x27, 256
	ldrb	w3, [x0, w3, sxtw]
	ldrb	w0, [x22, x28]
	sub	w0, w0, #1
	lsl	w4, w0, 1
	cmp	w4, 255
	bgt	.L130
	add	w1, w3, 1
	cmp	w1, w4
	bgt	.L131
	tbnz	x1, 0, .L280
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L131:
	add	w1, w1, 1
.L133:
	strb	w1, [x22, x28]
	ldp	w26, w20, [x19, 36]
	ldr	w1, [x19, 44]
	b	.L206
	.p2align 3
.L175:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w26, [x27, x1]
	lsl	w20, w20, w26
	sub	w2, w4, w26
	lsl	w26, w0, w26
	str	w26, [x19, 44]
	stp	w20, w2, [x19, 36]
.L180:
	sub	w26, w26, #1
	ubfx	x26, x26, 1, 24
	add	w26, w26, 1
	tbnz	w2, #31, .L281
.L178:
	lsl	w1, w26, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L179
	ldr	w0, [x19, 44]
	sub	w20, w20, w1
	sub	w26, w0, w26
	lsl	w0, w21, w5
.L179:
	orr	w3, w3, w0
	ldrb	w0, [x27, w26, uxtw]
	sub	w5, w5, #1
	lsl	w20, w20, w0
	sub	w2, w2, w0
	lsl	w26, w26, w0
	cmn	w5, #1
	stp	w20, w2, [x19, 36]
	str	w26, [x19, 44]
	bne	.L180
.L181:
	add	x0, x27, 256
	ldrb	w2, [x0, w3, sxtw]
	ldrb	w0, [x28, -1]
	sub	w0, w0, #1
	lsl	w3, w0, 1
	cmp	w3, 255
	bgt	.L196
	add	w1, w2, 1
	cmp	w1, w3
	bgt	.L197
	tbnz	x1, 0, .L282
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L197:
	add	w1, w1, 1
.L199:
	strb	w1, [x28, -1]
	ldr	w0, [x19, 44]
	ldp	w2, w4, [x19, 36]
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	ubfx	x0, x0, 6, 24
	add	w26, w0, 1
	tbz	w4, #31, .L202
.L276:
	sub	w3, w24, w4
	mov	x0, x19
	and	w3, w3, -8
	sub	w20, w23, w4
	mov	w1, w3
	sub	w20, w20, w3
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	add	w1, w3, w4
	and	w3, w20, 7
	lsl	w0, w0, w3
	mov	w4, w1
	orr	w2, w0, w2
	stp	w2, w1, [x19, 36]
	b	.L202
	.p2align 3
.L130:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w3, 1
	cmp	w1, w0, lsl 1
	bgt	.L134
	tbnz	x1, 0, .L283
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L134:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L133
	.p2align 3
.L196:
	sub	w0, w25, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L200
	tbnz	x1, 0, .L284
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L200:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L199
	.p2align 3
.L166:
	sub	w0, w25, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L170
	tbnz	x1, 0, .L285
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L170:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L169
	.p2align 3
.L259:
	sub	w4, w23, w20
	sub	w3, w21, w20
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w20, w4, w20
	lsl	w0, w0, w3
	orr	w26, w0, w26
	stp	w26, w20, [x19, 36]
	b	.L106
	.p2align 3
.L264:
	sub	w3, w25, w20
	sub	w2, w24, w20
	and	w3, w3, -8
	mov	x0, x19
	sub	w2, w2, w3
	mov	w1, w3
	stp	w2, w3, [x29, 104]
	bl	BsGet
	ldp	w2, w3, [x29, 104]
	and	w2, w2, 7
	add	w20, w3, w20
	lsl	w0, w0, w2
	orr	w26, w0, w26
	stp	w26, w20, [x19, 36]
	b	.L137
	.p2align 3
.L281:
	sub	w1, w24, w2
	sub	w4, w23, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w20, w0, w20
	b	.L178
	.p2align 3
.L279:
	sub	w1, w23, w20
	sub	w5, w21, w20
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w20, w1, w20
	stp	w4, w3, [x29, 100]
	str	w5, [x29, 108]
	bl	BsGet
	ldr	w5, [x29, 108]
	ldp	w4, w3, [x29, 100]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L112
	.p2align 3
.L277:
	sub	w1, w24, w2
	sub	w4, w23, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w3, w5, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w3, w5, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w26, w0, w26
	b	.L148
	.p2align 3
.L116:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w1, [x27, x1]
	lsl	w25, w26, w1
	sub	w26, w20, w1
	lsl	w20, w0, w1
	str	w20, [x19, 44]
	stp	w25, w26, [x19, 36]
.L121:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w26, #31, .L286
.L119:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w25
	bhi	.L120
	ldr	w0, [x19, 44]
	sub	w25, w25, w1
	sub	w20, w0, w20
	lsl	w0, w24, w4
.L120:
	orr	w3, w3, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w4, w4, #1
	lsl	w25, w25, w0
	sub	w26, w26, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w25, w26, [x19, 36]
	str	w20, [x19, 44]
	bne	.L121
	add	w3, w3, 16
	b	.L115
	.p2align 3
.L182:
	uxtw	x1, w0
	mov	w2, 3
	ldrb	w20, [x27, x1]
	lsl	w26, w3, w20
	sub	w4, w4, w20
	mov	w3, 0
	lsl	w20, w0, w20
	stp	w26, w4, [x19, 36]
	str	w20, [x19, 44]
.L187:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w4, #31, .L287
.L185:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L186
	ldr	w0, [x19, 44]
	sub	w26, w26, w1
	sub	w20, w0, w20
	lsl	w0, w21, w2
.L186:
	orr	w3, w3, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w2, w2, #1
	lsl	w26, w26, w0
	sub	w4, w4, w0
	lsl	w20, w20, w0
	cmn	w2, #1
	stp	w26, w4, [x19, 36]
	str	w20, [x19, 44]
	bne	.L187
	add	w3, w3, 16
	b	.L181
	.p2align 3
.L152:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x27, x1]
	lsl	w26, w26, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w26, w2, [x19, 36]
.L157:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L288
.L155:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L156
	ldr	w0, [x19, 44]
	sub	w26, w26, w1
	sub	w20, w0, w20
	lsl	w0, w21, w4
.L156:
	orr	w3, w3, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w26, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L157
	add	w3, w3, 16
	b	.L151
	.p2align 3
.L267:
	sub	w4, w24, w20
	sub	w3, w23, w20
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w20, w4, w20
	orr	w0, w0, w2
	mov	w2, w0
	stp	w0, w20, [x19, 36]
	b	.L144
	.p2align 3
.L272:
	sub	w2, w24, w4
	sub	w3, w23, w4
	and	w2, w2, -8
	mov	x0, x19
	sub	w3, w3, w2
	mov	w1, w2
	stp	w4, w3, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w4, w3, [x29, 100]
	ldr	w2, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w4, w2, w4
	orr	w20, w0, w20
	stp	w20, w4, [x19, 36]
	b	.L174
	.p2align 3
.L260:
	sub	w4, w23, w20
	sub	w3, w21, w20
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w20, w4, w20
	lsl	w0, w0, w3
	orr	w26, w0, w26
	stp	w26, w20, [x19, 36]
	b	.L108
	.p2align 3
.L278:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L167
	.p2align 3
.L280:
	add	w1, w3, 2
	sub	w1, w0, w1, lsr 1
	b	.L131
	.p2align 3
.L282:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L197
	.p2align 3
.L288:
	sub	w1, w24, w2
	sub	w5, w23, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L155
	.p2align 3
.L287:
	sub	w1, w24, w4
	sub	w5, w23, w4
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w4, w1, w4
	stp	w2, w3, [x29, 96]
	stp	w5, w4, [x29, 104]
	bl	BsGet
	ldp	w5, w4, [x29, 104]
	ldp	w2, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L185
	.p2align 3
.L286:
	sub	w1, w23, w26
	sub	w5, w21, w26
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w26, w1, w26
	stp	w4, w3, [x29, 100]
	str	w5, [x29, 108]
	bl	BsGet
	ldr	w5, [x29, 108]
	ldp	w4, w3, [x29, 100]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w25, w0, w25
	b	.L119
	.p2align 3
.L283:
	add	w3, w3, 2
	sub	w1, w0, w3, lsr 1
	b	.L134
	.p2align 3
.L285:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	b	.L170
	.p2align 3
.L284:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	b	.L200
.L188:
	uxtw	x1, w0
	mov	w3, 0
	ldrb	w20, [x27, x1]
	sub	w2, w4, w20
	lsl	w26, w26, w20
	mov	w4, 4
	lsl	w20, w0, w20
	stp	w26, w2, [x19, 36]
	str	w20, [x19, 44]
	.p2align 2
.L192:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L289
.L190:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L191
	ldr	w0, [x19, 44]
	sub	w26, w26, w1
	sub	w20, w0, w20
	lsl	w0, w21, w4
.L191:
	orr	w3, w3, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w26, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L192
	add	w3, w3, 32
	b	.L181
.L122:
	uxtw	x1, w0
	mov	w26, 0
	mov	w4, 4
	ldrb	w20, [x27, x1]
	lsl	w25, w25, w20
	sub	w3, w3, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w25, w3, [x19, 36]
	.p2align 2
.L126:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w3, #31, .L290
.L124:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w25
	bhi	.L125
	ldr	w0, [x19, 44]
	sub	w25, w25, w1
	sub	w20, w0, w20
	lsl	w0, w24, w4
.L125:
	orr	w26, w26, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w4, w4, #1
	lsl	w25, w25, w0
	sub	w3, w3, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w25, w3, [x19, 36]
	str	w20, [x19, 44]
	bne	.L126
	add	w3, w26, 32
	b	.L115
.L158:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x27, x1]
	lsl	w26, w26, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w26, w2, [x19, 36]
	.p2align 2
.L162:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L291
.L160:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L161
	ldr	w0, [x19, 44]
	sub	w26, w26, w1
	sub	w20, w0, w20
	lsl	w0, w21, w4
.L161:
	orr	w3, w3, w0
	ldrb	w0, [x27, w20, uxtw]
	sub	w4, w4, #1
	lsl	w26, w26, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w26, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L162
	add	w3, w3, 32
	b	.L151
	.p2align 3
.L291:
	sub	w1, w24, w2
	sub	w5, w23, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L160
	.p2align 3
.L290:
	sub	w1, w23, w3
	sub	w5, w21, w3
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w3, w1, w3
	stp	w4, w5, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w4, w5, [x29, 100]
	ldr	w3, [x29, 108]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w25, w0, w25
	b	.L124
	.p2align 3
.L289:
	sub	w1, w24, w2
	sub	w5, w23, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w26, w0, w26
	b	.L190
	.p2align 3
.L268:
	sub	w4, w24, w2
	sub	w3, w23, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w26, w0, w26
	stp	w26, w2, [x19, 36]
	b	.L147
	.p2align 3
.L261:
	sub	w4, w23, w20
	sub	w3, w21, w20
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	ldp	w3, w4, [x29, 104]
	and	w3, w3, 7
	add	w20, w4, w20
	lsl	w0, w0, w3
	orr	w0, w0, w26
	mov	w26, w0
	stp	w0, w20, [x19, 36]
	b	.L111
	.p2align 3
.L273:
	sub	w2, w24, w4
	mov	x0, x19
	and	w2, w2, -8
	sub	w20, w23, w4
	mov	w1, w2
	sub	w20, w20, w2
	stp	w3, w4, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w3, w4, [x29, 100]
	and	w20, w20, 7
	ldr	w2, [x29, 108]
	lsl	w0, w0, w20
	add	w4, w2, w4
	orr	w3, w0, w3
	stp	w3, w4, [x19, 36]
	b	.L177
.L270:
	cmp	w3, 64
	mov	w20, w3
	bgt	.L292
	add	w3, w20, 64
	b	.L151
.L292:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w3, w20, 64
	b	.L151
.L263:
	cmp	w26, 64
	mov	w20, w26
	bgt	.L293
	add	w3, w20, 64
	b	.L115
.L293:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w26, lsl 1
	sub	w20, w0, #65
	add	w3, w20, 64
	b	.L115
.L275:
	cmp	w3, 64
	mov	w20, w3
	bgt	.L294
	add	w3, w20, 64
	b	.L181
.L294:
	mov	w1, 128
	mov	x0, x19
	bl	Vp9_Cabac_Read
	add	w0, w0, w20, lsl 1
	sub	w20, w0, #65
	add	w3, w20, 64
	b	.L181
.L269:
	sub	w4, w24, w2
	sub	w3, w23, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w26, w0, w26
	stp	w26, w2, [x19, 36]
	b	.L154
.L262:
	sub	w4, w23, w3
	mov	x0, x19
	and	w4, w4, -8
	sub	w26, w21, w3
	mov	w1, w4
	sub	w26, w26, w4
	stp	w3, w4, [x29, 104]
	bl	BsGet
	and	w26, w26, 7
	ldp	w3, w4, [x29, 104]
	lsl	w0, w0, w26
	orr	w25, w0, w25
	add	w3, w4, w3
	stp	w25, w3, [x19, 36]
	b	.L118
.L274:
	sub	w2, w24, w4
	sub	w3, w23, w4
	and	w2, w2, -8
	mov	x0, x19
	sub	w3, w3, w2
	mov	w1, w2
	stp	w4, w3, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w4, w3, [x29, 100]
	ldr	w2, [x29, 108]
	and	w3, w3, 7
	add	w2, w2, w4
	lsl	w0, w0, w3
	orr	w26, w0, w26
	mov	w4, w2
	stp	w26, w2, [x19, 36]
	b	.L184
	.size	Vp9_ReadTxProbs, .-Vp9_ReadTxProbs
	.align	3
.LC8:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCoefProbsCommon
	.type	Vp9_ReadCoefProbsCommon, %function
Vp9_ReadCoefProbsCommon:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x1
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldp	w22, w19, [x27, 40]
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w22, #31, .L296
	ldr	w0, [x27, 36]
.L297:
	lsl	w2, w19, 24
	cmp	w2, w0
	bhi	.L298
	ldr	w1, [x27, 44]
	sub	w0, w0, w2
	ldr	x28, .LC10
	mov	w23, 24
	sub	w19, w1, w19
	add	x1, x21, 1024
	str	x1, [x29, 104]
	ldrb	w2, [x28, w19, uxtw]
	sub	w1, w22, w2
	lsl	w0, w0, w2
	lsl	w19, w19, w2
	str	w0, [x27, 36]
	str	w19, [x27, 44]
	mov	w22, 16
	str	w1, [x27, 40]
.L299:
	str	x21, [x29, 112]
	str	wzr, [x29, 124]
.L403:
	ldr	x0, [x29, 112]
	str	x0, [x29, 160]
	ldr	w0, [x29, 124]
	str	wzr, [x29, 172]
	sbfiz	x0, x0, 3, 32
	str	x0, [x29, 128]
	.p2align 2
.L401:
	ldr	w0, [x29, 172]
	mov	w26, 0
	ldr	x1, [x29, 128]
	cmp	w0, wzr
	ldr	x25, [x29, 160]
	add	x19, x1, x0, sxtw
	mov	w0, 3
	mov	w1, 6
	lsl	x19, x19, 3
	csel	w20, w0, w1, eq
	cmp	w26, w20
	bge	.L458
	.p2align 2
.L397:
	ldp	w2, w0, [x27, 40]
	add	x6, x19, x26, sxtw
	sub	w1, w0, #1
	lsl	w0, w1, 6
	add	x24, x21, x6, lsl 2
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L300
	ldr	w4, [x27, 36]
.L301:
	lsl	w1, w10, 24
	cmp	w1, w4
	bhi	.L302
	ldr	w0, [x27, 44]
	sub	w4, w4, w1
	sub	w0, w0, w10
	ldrb	w9, [x28, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L459
.L303:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w1, w0, 1
	lsl	w9, w1, 24
	cmp	w9, w4
	bhi	.L304
	ldr	w0, [x27, 44]
	sub	w4, w4, w9
	sub	w0, w0, w1
	ldrb	w10, [x28, w0, uxtw]
	lsl	w4, w4, w10
	sub	w2, w2, w10
	lsl	w10, w0, w10
	str	w10, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L460
.L306:
	sub	w0, w10, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L311
	ldr	w9, [x27, 44]
	sub	w4, w4, w1
	sub	w0, w9, w0
	ldrb	w9, [x28, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L461
.L313:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L317
	sub	w12, w4, w1
	ldr	w1, [x27, 44]
	mov	w10, 0
	mov	w9, 6
	sub	w0, w1, w0
	mov	w11, 1
	ldrb	w1, [x28, w0, uxtw]
	lsl	w12, w12, w1
	sub	w4, w2, w1
	lsl	w0, w0, w1
	str	w0, [x27, 44]
	stp	w12, w4, [x27, 36]
	b	.L318
	.p2align 3
.L322:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L323
	ldr	w13, [x27, 44]
	lsl	w0, w11, w9
	sub	w12, w12, w1
	sub	w2, w13, w2
.L323:
	orr	w10, w10, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w9, w9, #1
	lsl	w12, w12, w0
	sub	w4, w4, w0
	cmn	w9, #1
	lsl	w0, w2, w0
	stp	w12, w4, [x27, 36]
	str	w0, [x27, 44]
	beq	.L462
.L318:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L322
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w9, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w9, [x29, 144]
	orr	w12, w0, w12
	b	.L322
	.p2align 3
.L302:
	uxtw	x0, w10
	ldrb	w0, [x28, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x27, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w4, w2, [x27, 36]
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L463
.L333:
	lsl	w1, w10, 24
	cmp	w1, w4
	bhi	.L334
	ldr	w0, [x27, 44]
	sub	w1, w4, w1
	sub	w0, w0, w10
	ldrb	w9, [x28, w0, uxtw]
	lsl	w4, w1, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L464
.L335:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w1, w0, 1
	lsl	w9, w1, 24
	cmp	w9, w4
	bhi	.L336
	ldr	w0, [x27, 44]
	sub	w4, w4, w9
	sub	w0, w0, w1
	ldrb	w10, [x28, w0, uxtw]
	lsl	w4, w4, w10
	sub	w2, w2, w10
	lsl	w10, w0, w10
	str	w10, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L465
.L338:
	sub	w0, w10, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L343
	ldr	w9, [x27, 44]
	sub	w4, w4, w1
	sub	w0, w9, w0
	ldrb	w9, [x28, w0, uxtw]
	lsl	w4, w4, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w4, w2, [x27, 36]
	tbnz	w2, #31, .L466
.L345:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w4
	bhi	.L349
	sub	w12, w4, w1
	ldr	w1, [x27, 44]
	mov	w10, 0
	mov	w9, 6
	sub	w0, w1, w0
	mov	w11, 1
	ldrb	w1, [x28, w0, uxtw]
	lsl	w12, w12, w1
	sub	w4, w2, w1
	lsl	w0, w0, w1
	str	w0, [x27, 44]
	stp	w12, w4, [x27, 36]
	b	.L350
	.p2align 3
.L354:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L355
	ldr	w13, [x27, 44]
	lsl	w0, w11, w9
	sub	w12, w12, w1
	sub	w2, w13, w2
.L355:
	orr	w10, w10, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w9, w9, #1
	lsl	w12, w12, w0
	sub	w4, w4, w0
	cmn	w9, #1
	lsl	w0, w2, w0
	stp	w12, w4, [x27, 36]
	str	w0, [x27, 44]
	beq	.L467
.L350:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L354
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w9, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w9, [x29, 144]
	orr	w12, w0, w12
	b	.L354
	.p2align 3
.L334:
	uxtw	x0, w10
	ldrb	w0, [x28, x0]
	lsl	w9, w4, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x27, 44]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	stp	w9, w2, [x27, 36]
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbnz	w2, #31, .L468
.L365:
	lsl	w1, w10, 24
	cmp	w1, w9
	bhi	.L366
	ldr	w0, [x27, 44]
	sub	w1, w9, w1
	sub	w0, w0, w10
	ldrb	w4, [x28, w0, uxtw]
	lsl	w12, w1, w4
	sub	w2, w2, w4
	lsl	w4, w0, w4
	str	w4, [x27, 44]
	stp	w12, w2, [x27, 36]
	tbnz	w2, #31, .L469
.L367:
	sub	w4, w4, #1
	ubfx	x4, x4, 1, 24
	add	w0, w4, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L368
	ldr	w4, [x27, 44]
	sub	w1, w12, w1
	sub	w4, w4, w0
	ldrb	w0, [x28, w4, uxtw]
	lsl	w12, w1, w0
	sub	w2, w2, w0
	lsl	w4, w4, w0
	str	w4, [x27, 44]
	stp	w12, w2, [x27, 36]
	tbnz	w2, #31, .L470
.L370:
	sub	w0, w4, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L375
	ldr	w4, [x27, 44]
	sub	w1, w12, w1
	sub	w0, w4, w0
	ldrb	w9, [x28, w0, uxtw]
	lsl	w12, w1, w9
	sub	w2, w2, w9
	lsl	w9, w0, w9
	str	w9, [x27, 44]
	stp	w12, w2, [x27, 36]
	tbnz	w2, #31, .L471
.L377:
	sub	w0, w9, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w12
	bhi	.L381
	sub	w12, w12, w1
	ldr	w1, [x27, 44]
	mov	w10, 0
	mov	w9, 6
	sub	w0, w1, w0
	mov	w11, 1
	ldrb	w1, [x28, w0, uxtw]
	lsl	w12, w12, w1
	sub	w4, w2, w1
	lsl	w0, w0, w1
	str	w0, [x27, 44]
	stp	w12, w4, [x27, 36]
	b	.L382
	.p2align 3
.L386:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L387
	ldr	w13, [x27, 44]
	lsl	w0, w11, w9
	sub	w12, w12, w1
	sub	w2, w13, w2
.L387:
	orr	w10, w10, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w9, w9, #1
	lsl	w12, w12, w0
	sub	w4, w4, w0
	cmn	w9, #1
	lsl	w0, w2, w0
	stp	w12, w4, [x27, 36]
	str	w0, [x27, 44]
	beq	.L472
.L382:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w4, #31, .L386
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L386
	.p2align 3
.L366:
	uxtw	x0, w10
	ldrb	w0, [x28, x0]
	lsl	w1, w9, w0
	sub	w2, w2, w0
	lsl	w0, w10, w0
	str	w0, [x27, 44]
	stp	w1, w2, [x27, 36]
.L406:
	add	w26, w26, 1
	add	x25, x25, 4
	cmp	w26, w20
	blt	.L397
.L458:
	ldr	w0, [x29, 172]
	ldr	x1, [x29, 160]
	add	w0, w0, 1
	str	w0, [x29, 172]
	add	x1, x1, 32
	cmp	w0, 6
	str	x1, [x29, 160]
	bne	.L401
	ldr	w0, [x29, 124]
	ldr	x1, [x29, 112]
	add	w0, w0, 1
	str	w0, [x29, 124]
	add	x1, x1, 256
	cmp	w0, 2
	str	x1, [x29, 112]
	bne	.L403
	ldr	x0, [x29, 104]
	add	x21, x21, 512
	cmp	x0, x21
	bne	.L299
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L368:
	uxtw	x1, w0
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w4, [x28, x1]
	lsl	w1, w12, w4
	sub	w2, w2, w4
	lsl	w4, w0, w4
	str	w4, [x27, 44]
	stp	w1, w2, [x27, 36]
.L373:
	sub	w4, w4, #1
	mov	w12, w1
	ubfx	x4, x4, 1, 24
	add	w4, w4, 1
	tbnz	w2, #31, .L473
.L371:
	lsl	w1, w4, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L372
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w4, w13, w4
.L372:
	orr	w9, w9, w0
	ldrb	w0, [x28, w4, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w2, w2, w0
	lsl	w4, w4, w0
	cmn	w10, #1
	stp	w1, w2, [x27, 36]
	str	w4, [x27, 44]
	bne	.L373
.L374:
	ldrb	w1, [x24, 2]
	add	x0, x28, 256
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L391
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L392
	tbnz	x0, 0, .L474
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L392:
	add	w0, w0, 1
.L394:
	strb	w0, [x24, 2]
	b	.L406
	.p2align 3
.L336:
	uxtw	x0, w1
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w0, [x28, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w1, w0
	str	w0, [x27, 44]
	stp	w4, w2, [x27, 36]
.L341:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w12, w0, 1
	tbnz	w2, #31, .L475
.L339:
	lsl	w1, w12, 24
	mov	w0, 0
	cmp	w1, w4
	bhi	.L340
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w4, w4, w1
	sub	w12, w13, w12
.L340:
	orr	w9, w9, w0
	ldrb	w0, [x28, w12, uxtw]
	sub	w10, w10, #1
	lsl	w4, w4, w0
	sub	w2, w2, w0
	cmn	w10, #1
	lsl	w0, w12, w0
	stp	w4, w2, [x27, 36]
	str	w0, [x27, 44]
	bne	.L341
.L342:
	ldrb	w1, [x24, 1]
	add	x0, x28, 256
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L359
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L360
	tbnz	x0, 0, .L476
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L360:
	add	w0, w0, 1
.L362:
	strb	w0, [x24, 1]
	ldr	w0, [x27, 44]
	ldp	w9, w2, [x27, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbz	w2, #31, .L365
.L468:
	sub	w11, w23, w2
	sub	w4, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w4, w4, w11
	mov	w1, w11
	stp	w9, w10, [x29, 144]
	stp	w2, w11, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldr	w4, [x29, 168]
	ldp	w9, w10, [x29, 144]
	and	w4, w4, 7
	ldp	w2, w11, [x29, 152]
	lsl	w0, w0, w4
	orr	w1, w0, w9
	add	w2, w11, w2
	mov	w9, w1
	stp	w1, w2, [x27, 36]
	b	.L365
	.p2align 3
.L304:
	uxtw	x0, w1
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w0, [x28, x0]
	lsl	w4, w4, w0
	sub	w2, w2, w0
	lsl	w0, w1, w0
	str	w0, [x27, 44]
	stp	w4, w2, [x27, 36]
.L309:
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w12, w0, 1
	tbnz	w2, #31, .L477
.L307:
	lsl	w1, w12, 24
	mov	w0, 0
	cmp	w1, w4
	bhi	.L308
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w4, w4, w1
	sub	w12, w13, w12
.L308:
	orr	w9, w9, w0
	ldrb	w0, [x28, w12, uxtw]
	sub	w10, w10, #1
	lsl	w4, w4, w0
	sub	w2, w2, w0
	cmn	w10, #1
	lsl	w0, w12, w0
	stp	w4, w2, [x27, 36]
	str	w0, [x27, 44]
	bne	.L309
.L310:
	ldrb	w1, [x25]
	add	x0, x28, 256
	sub	w1, w1, #1
	lsl	w4, w1, 1
	ldrb	w2, [x0, w9, sxtw]
	cmp	w4, 255
	bgt	.L327
	add	w0, w2, 1
	cmp	w0, w4
	bgt	.L328
	tbnz	x0, 0, .L478
	add	w0, w0, w0, lsr 31
	add	w0, w1, w0, asr 1
.L328:
	add	w0, w0, 1
.L330:
	strb	w0, [x25]
	ldr	w0, [x27, 44]
	ldp	w4, w2, [x27, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w10, w0, 1
	tbz	w2, #31, .L333
.L463:
	sub	w11, w23, w2
	sub	w9, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w9, w9, w11
	mov	w1, w11
	stp	w4, w10, [x29, 144]
	stp	w2, w11, [x29, 152]
	str	w9, [x29, 168]
	bl	BsGet
	ldr	w9, [x29, 168]
	ldp	w4, w10, [x29, 144]
	and	w9, w9, 7
	ldp	w2, w11, [x29, 152]
	lsl	w0, w0, w9
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x27, 36]
	b	.L333
	.p2align 3
.L327:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L331
	tbnz	x4, 0, .L479
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L331:
	mov	w0, 255
	sub	w0, w0, w4
	b	.L330
	.p2align 3
.L359:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L363
	tbnz	x4, 0, .L480
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L363:
	mov	w0, 255
	sub	w0, w0, w4
	b	.L362
	.p2align 3
.L391:
	mov	w0, 254
	add	w4, w2, 1
	sub	w1, w0, w1
	cmp	w4, w1, lsl 1
	bgt	.L395
	tbnz	x4, 0, .L481
	add	w0, w4, w4, lsr 31
	add	w4, w1, w0, asr 1
.L395:
	mov	w0, 255
	sub	w0, w0, w4
	strb	w0, [x24, 2]
	b	.L406
	.p2align 3
.L300:
	sub	w11, w23, w2
	sub	w4, w22, w2
	and	w11, w11, -8
	ldr	w9, [x27, 36]
	sub	w4, w4, w11
	mov	w1, w11
	mov	x0, x27
	str	w9, [x29, 168]
	stp	w10, w2, [x29, 144]
	stp	w11, w4, [x29, 152]
	bl	BsGet
	ldp	w11, w4, [x29, 152]
	ldp	w10, w2, [x29, 144]
	and	w4, w4, 7
	ldr	w9, [x29, 168]
	lsl	w0, w0, w4
	add	w2, w2, w11
	orr	w4, w0, w9
	stp	w4, w2, [x27, 36]
	b	.L301
	.p2align 3
.L473:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w11, w12, [x29, 136]
	stp	w4, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w4, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L371
	.p2align 3
.L477:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w11, w4, [x29, 136]
	stp	w12, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w4, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w12, w10, [x29, 144]
	orr	w4, w0, w4
	b	.L307
	.p2align 3
.L475:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w11, w4, [x29, 136]
	stp	w12, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w4, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w12, w10, [x29, 144]
	orr	w4, w0, w4
	b	.L339
	.p2align 3
.L375:
	uxtw	x1, w0
	mov	w9, 0
	mov	w10, 3
	mov	w11, 1
	ldrb	w13, [x28, x1]
	sub	w4, w2, w13
	lsl	w1, w12, w13
	lsl	w2, w0, w13
	str	w2, [x27, 44]
	stp	w1, w4, [x27, 36]
.L380:
	sub	w2, w2, #1
	mov	w12, w1
	ubfx	x2, x2, 1, 24
	add	w2, w2, 1
	tbnz	w4, #31, .L482
.L378:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L379
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w13, w2
.L379:
	orr	w9, w9, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	lsl	w2, w2, w0
	cmn	w10, #1
	stp	w1, w4, [x27, 36]
	str	w2, [x27, 44]
	bne	.L380
	add	w9, w9, 16
	b	.L374
	.p2align 3
.L311:
	uxtw	x1, w0
	mov	w10, 0
	mov	w11, 3
	mov	w12, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w4, w9
	sub	w2, w2, w9
	lsl	w0, w0, w9
	str	w0, [x27, 44]
	stp	w1, w2, [x27, 36]
.L316:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w4, w0, 1
	tbnz	w2, #31, .L483
.L314:
	lsl	w1, w4, 24
	mov	w0, 0
	cmp	w1, w9
	bhi	.L315
	ldr	w13, [x27, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w4, w13, w4
.L315:
	orr	w10, w10, w0
	ldrb	w0, [x28, w4, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w2, w2, w0
	cmn	w11, #1
	lsl	w0, w4, w0
	stp	w1, w2, [x27, 36]
	str	w0, [x27, 44]
	bne	.L316
	add	w9, w10, 16
	b	.L310
	.p2align 3
.L343:
	uxtw	x1, w0
	mov	w10, 0
	mov	w11, 3
	mov	w12, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w4, w9
	sub	w2, w2, w9
	lsl	w0, w0, w9
	str	w0, [x27, 44]
	stp	w1, w2, [x27, 36]
.L348:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w4, w0, 1
	tbnz	w2, #31, .L484
.L346:
	lsl	w1, w4, 24
	mov	w0, 0
	cmp	w1, w9
	bhi	.L347
	ldr	w13, [x27, 44]
	lsl	w0, w12, w11
	sub	w9, w9, w1
	sub	w4, w13, w4
.L347:
	orr	w10, w10, w0
	ldrb	w0, [x28, w4, uxtw]
	sub	w11, w11, #1
	lsl	w1, w9, w0
	sub	w2, w2, w0
	cmn	w11, #1
	lsl	w0, w4, w0
	stp	w1, w2, [x27, 36]
	str	w0, [x27, 44]
	bne	.L348
	add	w9, w10, 16
	b	.L342
	.p2align 3
.L469:
	sub	w10, w23, w2
	sub	w9, w22, w2
	and	w10, w10, -8
	mov	x0, x27
	sub	w9, w9, w10
	mov	w1, w10
	stp	w4, w12, [x29, 144]
	stp	w2, w10, [x29, 152]
	str	w9, [x29, 168]
	bl	BsGet
	ldr	w9, [x29, 168]
	ldp	w4, w12, [x29, 144]
	and	w9, w9, 7
	ldp	w2, w10, [x29, 152]
	lsl	w0, w0, w9
	orr	w1, w0, w12
	add	w2, w10, w2
	mov	w12, w1
	stp	w1, w2, [x27, 36]
	b	.L367
	.p2align 3
.L459:
	sub	w11, w23, w2
	sub	w10, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w10, w10, w11
	mov	w1, w11
	stp	w4, w9, [x29, 144]
	stp	w2, w11, [x29, 152]
	str	w10, [x29, 168]
	bl	BsGet
	ldr	w10, [x29, 168]
	ldp	w4, w9, [x29, 144]
	ldp	w2, w11, [x29, 152]
	and	w10, w10, 7
	lsl	w0, w0, w10
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x27, 36]
	b	.L303
	.p2align 3
.L464:
	sub	w11, w23, w2
	sub	w10, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w10, w10, w11
	mov	w1, w11
	stp	w9, w4, [x29, 144]
	stp	w2, w11, [x29, 152]
	str	w10, [x29, 168]
	bl	BsGet
	ldr	w10, [x29, 168]
	ldp	w9, w4, [x29, 144]
	ldp	w2, w11, [x29, 152]
	and	w10, w10, 7
	lsl	w0, w0, w10
	add	w2, w2, w11
	orr	w4, w0, w4
	stp	w4, w2, [x27, 36]
	b	.L335
	.p2align 3
.L478:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L328
	.p2align 3
.L474:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	add	w0, w0, 1
	b	.L394
	.p2align 3
.L476:
	add	w0, w2, 2
	sub	w0, w1, w0, lsr 1
	b	.L360
	.p2align 3
.L483:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w12, w9, [x29, 136]
	stp	w4, w11, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w12, w9, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w4, w11, [x29, 144]
	orr	w9, w0, w9
	b	.L314
	.p2align 3
.L484:
	sub	w1, w23, w2
	sub	w13, w22, w2
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w2, w1, w2
	stp	w12, w9, [x29, 136]
	stp	w4, w11, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w2, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w12, w9, [x29, 136]
	and	w13, w13, 7
	ldr	w2, [x29, 168]
	lsl	w0, w0, w13
	ldp	w4, w11, [x29, 144]
	orr	w9, w0, w9
	b	.L346
	.p2align 3
.L482:
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L378
	.p2align 3
.L480:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L363
	.p2align 3
.L479:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L331
	.p2align 3
.L481:
	add	w2, w2, 2
	sub	w4, w1, w2, lsr 1
	b	.L395
.L317:
	uxtw	x1, w0
	mov	w10, 4
	mov	w11, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w4, w9
	lsl	w0, w0, w9
	sub	w4, w2, w9
	str	w0, [x27, 44]
	mov	w9, 0
	stp	w1, w4, [x27, 36]
	.p2align 2
.L321:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L485
.L319:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L320
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w13, w2
.L320:
	orr	w9, w9, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x27, 36]
	str	w0, [x27, 44]
	bne	.L321
	add	w9, w9, 32
	b	.L310
.L349:
	uxtw	x1, w0
	mov	w10, 4
	mov	w11, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w4, w9
	lsl	w0, w0, w9
	sub	w4, w2, w9
	str	w0, [x27, 44]
	mov	w9, 0
	stp	w1, w4, [x27, 36]
	.p2align 2
.L353:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L486
.L351:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L352
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w13, w2
.L352:
	orr	w9, w9, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x27, 36]
	str	w0, [x27, 44]
	bne	.L353
	add	w9, w9, 32
	b	.L342
.L381:
	uxtw	x1, w0
	mov	w10, 4
	mov	w11, 1
	ldrb	w9, [x28, x1]
	lsl	w1, w12, w9
	sub	w4, w2, w9
	lsl	w0, w0, w9
	mov	w9, 0
	stp	w1, w4, [x27, 36]
	str	w0, [x27, 44]
	.p2align 2
.L385:
	sub	w0, w0, #1
	mov	w12, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w4, #31, .L487
.L383:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L384
	ldr	w13, [x27, 44]
	lsl	w0, w11, w10
	sub	w12, w12, w1
	sub	w2, w13, w2
.L384:
	orr	w9, w9, w0
	ldrb	w0, [x28, w2, uxtw]
	sub	w10, w10, #1
	lsl	w1, w12, w0
	sub	w4, w4, w0
	cmn	w10, #1
	lsl	w0, w2, w0
	stp	w1, w4, [x27, 36]
	str	w0, [x27, 44]
	bne	.L385
	add	w9, w9, 32
	b	.L374
	.p2align 3
.L487:
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L383
	.p2align 3
.L486:
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w9, [x29, 144]
	stp	w10, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w10, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w9, [x29, 144]
	orr	w12, w0, w12
	b	.L351
	.p2align 3
.L485:
	sub	w1, w23, w4
	sub	w13, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w13, w13, w1
	add	w4, w1, w4
	stp	w11, w12, [x29, 136]
	stp	w2, w10, [x29, 144]
	stp	w9, w13, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w13, [x29, 152]
	ldp	w11, w12, [x29, 136]
	and	w13, w13, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w13
	ldp	w2, w10, [x29, 144]
	orr	w12, w0, w12
	b	.L319
	.p2align 3
.L470:
	sub	w10, w23, w2
	sub	w9, w22, w2
	and	w10, w10, -8
	mov	x0, x27
	sub	w9, w9, w10
	mov	w1, w10
	stp	w4, w12, [x29, 144]
	stp	w2, w9, [x29, 152]
	str	w10, [x29, 168]
	bl	BsGet
	ldp	w2, w9, [x29, 152]
	ldp	w4, w12, [x29, 144]
	and	w9, w9, 7
	ldr	w10, [x29, 168]
	lsl	w0, w0, w9
	orr	w1, w0, w12
	add	w2, w10, w2
	mov	w12, w1
	stp	w1, w2, [x27, 36]
	b	.L370
	.p2align 3
.L465:
	sub	w11, w23, w2
	sub	w9, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w9, w9, w11
	mov	w1, w11
	stp	w10, w4, [x29, 144]
	stp	w2, w9, [x29, 152]
	str	w11, [x29, 168]
	bl	BsGet
	ldp	w2, w9, [x29, 152]
	ldp	w10, w4, [x29, 144]
	ldr	w11, [x29, 168]
	and	w9, w9, 7
	lsl	w0, w0, w9
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x27, 36]
	b	.L338
	.p2align 3
.L460:
	sub	w11, w23, w2
	sub	w9, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w9, w9, w11
	mov	w1, w11
	stp	w4, w10, [x29, 144]
	stp	w2, w9, [x29, 152]
	str	w11, [x29, 168]
	bl	BsGet
	ldp	w2, w9, [x29, 152]
	ldp	w4, w10, [x29, 144]
	ldr	w11, [x29, 168]
	and	w9, w9, 7
	lsl	w0, w0, w9
	add	w2, w11, w2
	orr	w4, w0, w4
	stp	w4, w2, [x27, 36]
	b	.L306
.L462:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L488
	add	w9, w9, 64
	b	.L310
.L472:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L489
	add	w9, w9, 64
	b	.L374
.L467:
	cmp	w10, 64
	mov	w9, w10
	bgt	.L490
	add	w9, w9, 64
	b	.L342
.L490:
	sub	w2, w0, #1
	lsl	w10, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w9, w10, #65
	add	w2, w2, 1
	tbnz	w4, #31, .L491
.L357:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L358
	ldr	w0, [x27, 44]
	sub	w12, w12, w1
	sub	w2, w0, w2
	mov	w0, 1
.L358:
	ldrb	w1, [x28, w2, uxtw]
	add	w9, w9, w0
	add	w9, w9, 64
	lsl	w0, w12, w1
	lsl	w2, w2, w1
	str	w0, [x27, 36]
	sub	w0, w4, w1
	str	w2, [x27, 44]
	str	w0, [x27, 40]
	b	.L342
.L489:
	sub	w2, w0, #1
	lsl	w10, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w9, w10, #65
	add	w2, w2, 1
	tbnz	w4, #31, .L492
.L389:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L390
	ldr	w0, [x27, 44]
	sub	w12, w12, w1
	sub	w2, w0, w2
	mov	w0, 1
.L390:
	ldrb	w1, [x28, w2, uxtw]
	add	w9, w9, w0
	add	w9, w9, 64
	lsl	w0, w12, w1
	lsl	w2, w2, w1
	str	w0, [x27, 36]
	sub	w0, w4, w1
	str	w2, [x27, 44]
	str	w0, [x27, 40]
	b	.L374
.L488:
	sub	w2, w0, #1
	lsl	w9, w10, 1
	ubfx	x2, x2, 1, 24
	sub	w9, w9, #65
	add	w2, w2, 1
	tbnz	w4, #31, .L493
.L325:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w12
	bhi	.L326
	ldr	w0, [x27, 44]
	sub	w12, w12, w1
	sub	w2, w0, w2
	mov	w0, 1
.L326:
	ldrb	w1, [x28, w2, uxtw]
	add	w9, w9, w0
	add	w9, w9, 64
	lsl	w12, w12, w1
	sub	w0, w4, w1
	lsl	w2, w2, w1
	str	w2, [x27, 44]
	stp	w12, w0, [x27, 36]
	b	.L310
.L471:
	sub	w4, w23, w2
	sub	w10, w22, w2
	and	w4, w4, -8
	mov	x0, x27
	sub	w10, w10, w4
	mov	w1, w4
	stp	w9, w12, [x29, 144]
	stp	w2, w10, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w2, w10, [x29, 152]
	ldp	w9, w12, [x29, 144]
	ldr	w4, [x29, 168]
	and	w10, w10, 7
	lsl	w0, w0, w10
	add	w4, w4, w2
	orr	w1, w0, w12
	mov	w2, w4
	mov	w12, w1
	stp	w1, w4, [x27, 36]
	b	.L377
.L466:
	sub	w11, w23, w2
	sub	w10, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w10, w10, w11
	mov	w1, w11
	stp	w9, w4, [x29, 144]
	stp	w2, w10, [x29, 152]
	str	w11, [x29, 168]
	bl	BsGet
	ldp	w2, w10, [x29, 152]
	ldp	w9, w4, [x29, 144]
	and	w10, w10, 7
	ldr	w11, [x29, 168]
	lsl	w0, w0, w10
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x27, 36]
	b	.L345
.L461:
	sub	w11, w23, w2
	sub	w10, w22, w2
	and	w11, w11, -8
	mov	x0, x27
	sub	w10, w10, w11
	mov	w1, w11
	stp	w4, w9, [x29, 144]
	stp	w2, w10, [x29, 152]
	str	w11, [x29, 168]
	bl	BsGet
	ldp	w2, w10, [x29, 152]
	ldp	w4, w9, [x29, 144]
	and	w10, w10, 7
	ldr	w11, [x29, 168]
	lsl	w0, w0, w10
	orr	w1, w0, w4
	add	w2, w11, w2
	mov	w4, w1
	stp	w1, w2, [x27, 36]
	b	.L313
.L298:
	ldr	x2, .LC10
	uxtw	x1, w19
	ldrb	w2, [x2, x1]
	sub	w1, w22, w2
	lsl	w19, w19, w2
	lsl	w0, w0, w2
	str	w19, [x27, 44]
	stp	w0, w1, [x27, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L296:
	mov	w23, 24
	mov	w24, 16
	sub	w23, w23, w22
	sub	w24, w24, w22
	and	w23, w23, -8
	mov	x0, x27
	mov	w1, w23
	sub	w24, w24, w23
	ldr	w20, [x27, 36]
	and	w24, w24, 7
	bl	BsGet
	lsl	w0, w0, w24
	add	w1, w22, w23
	orr	w0, w0, w20
	mov	w22, w1
	stp	w0, w1, [x27, 36]
	b	.L297
.L493:
	sub	w1, w23, w4
	sub	w10, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w10, w10, w1
	add	w4, w4, w1
	stp	w12, w2, [x29, 144]
	stp	w9, w10, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w10, [x29, 152]
	ldp	w12, w2, [x29, 144]
	and	w10, w10, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w10
	orr	w12, w0, w12
	b	.L325
.L492:
	sub	w1, w23, w4
	sub	w10, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w10, w10, w1
	add	w4, w4, w1
	stp	w12, w2, [x29, 144]
	stp	w9, w10, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w10, [x29, 152]
	ldp	w12, w2, [x29, 144]
	and	w10, w10, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w10
	orr	w12, w0, w12
	b	.L389
.L491:
	sub	w1, w23, w4
	sub	w10, w22, w4
	and	w1, w1, -8
	mov	x0, x27
	sub	w10, w10, w1
	add	w4, w4, w1
	stp	w12, w2, [x29, 144]
	stp	w9, w10, [x29, 152]
	str	w4, [x29, 168]
	bl	BsGet
	ldp	w9, w10, [x29, 152]
	ldp	w12, w2, [x29, 144]
	and	w10, w10, 7
	ldr	w4, [x29, 168]
	lsl	w0, w0, w10
	orr	w12, w0, w12
	b	.L357
	.size	Vp9_ReadCoefProbsCommon, .-Vp9_ReadCoefProbsCommon
	.align	3
.LC10:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCoefProbs
	.type	Vp9_ReadCoefProbs, %function
Vp9_ReadCoefProbs:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	bl	_mcount
	mov	x1, x20
	mov	x0, x19
	bl	Vp9_ReadCoefProbsCommon
	cbnz	w21, .L500
.L494:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L500:
	mov	x1, x20
	add	x0, x19, 1024
	bl	Vp9_ReadCoefProbsCommon
	cmp	w21, 1
	bls	.L496
	mov	x1, x20
	add	x0, x19, 2048
	bl	Vp9_ReadCoefProbsCommon
.L496:
	cmp	w21, 2
	bls	.L494
	mov	x1, x20
	add	x0, x19, 3072
	bl	Vp9_ReadCoefProbsCommon
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_ReadCoefProbs, .-Vp9_ReadCoefProbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadInterModeProbs
	.type	Vp9_ReadInterModeProbs, %function
Vp9_ReadInterModeProbs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x21, x21, 4096
	mov	x19, x1
	bl	_mcount
	ldr	x25, .LC12
	add	x26, x21, 345
	mov	w23, 24
	add	x21, x21, 366
	mov	w22, 16
	mov	w27, 1
	mov	w24, 254
	.p2align 2
.L599:
	ldp	w2, w1, [x19, 40]
	sub	w1, w1, #1
	lsl	w0, w1, 6
	sub	w1, w0, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbnz	w2, #31, .L502
	ldr	w28, [x19, 36]
.L503:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L504
	ldr	w1, [x19, 44]
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x25, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L657
.L505:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L506
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x25, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L658
.L508:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L513
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L659
.L515:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L519
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w4, 0
	mov	w3, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L520
	.p2align 3
.L524:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L525
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L525:
	orr	w4, w4, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L660
.L520:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L524
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L524
	.p2align 3
.L504:
	uxtw	x0, w20
	ldrb	w1, [x25, x0]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w1, w20, w1
	str	w1, [x19, 44]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	stp	w28, w2, [x19, 36]
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbnz	w2, #31, .L661
.L535:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L536
	ldr	w1, [x19, 44]
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x25, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L662
.L537:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L538
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x25, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L663
.L540:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L545
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L664
.L547:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L551
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w4, 0
	mov	w3, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L552
	.p2align 3
.L556:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L557
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L557:
	orr	w4, w4, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L665
.L552:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L556
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L556
	.p2align 3
.L536:
	uxtw	x0, w20
	ldrb	w1, [x25, x0]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w1, w20, w1
	str	w1, [x19, 44]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	stp	w28, w2, [x19, 36]
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbnz	w2, #31, .L666
.L567:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L568
	ldr	w1, [x19, 44]
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x25, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L667
.L569:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L570
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x25, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L668
.L572:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L577
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L669
.L579:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L583
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w4, 0
	mov	w3, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L584
	.p2align 3
.L588:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L589
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L589:
	orr	w4, w4, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L670
.L584:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L588
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L588
	.p2align 3
.L568:
	uxtw	x0, w20
	ldrb	w1, [x25, x0]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w1, w20, w1
	str	w1, [x19, 44]
	stp	w28, w2, [x19, 36]
.L602:
	add	x26, x26, 3
	cmp	x26, x21
	bne	.L599
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L570:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L575:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L671
.L573:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L574
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L574:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L575
.L576:
	ldrb	w0, [x26]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L593
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L594
	tbnz	x1, 0, .L672
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L594:
	add	w1, w1, 1
.L596:
	strb	w1, [x26]
	b	.L602
	.p2align 3
.L538:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L543:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L673
.L541:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L542
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L542:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L543
.L544:
	ldrb	w0, [x26, -1]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L561
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L562
	tbnz	x1, 0, .L674
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L562:
	add	w1, w1, 1
.L564:
	strb	w1, [x26, -1]
	ldr	w1, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbz	w2, #31, .L567
.L666:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L567
	.p2align 3
.L506:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L511:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L675
.L509:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L510
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L510:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L511
.L512:
	ldrb	w0, [x26, -2]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L529
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L530
	tbnz	x1, 0, .L676
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L530:
	add	w1, w1, 1
.L532:
	strb	w1, [x26, -2]
	ldr	w1, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w1, w1, #1
	lsl	w20, w1, 6
	sub	w1, w20, w1
	ubfx	x1, x1, 6, 24
	add	w20, w1, 1
	tbz	w2, #31, .L535
.L661:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L535
	.p2align 3
.L593:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L597
	tbnz	x1, 0, .L677
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L597:
	mov	w0, 255
	sub	w1, w0, w1
.L683:
	strb	w1, [x26]
	b	.L602
	.p2align 3
.L529:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L533
	tbnz	x1, 0, .L678
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L533:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L532
	.p2align 3
.L561:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L565
	tbnz	x1, 0, .L679
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L565:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L564
	.p2align 3
.L502:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	ldr	w28, [x19, 36]
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w2, w3
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L503
	.p2align 3
.L671:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L573
	.p2align 3
.L675:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L509
	.p2align 3
.L673:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L541
	.p2align 3
.L672:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L596
	.p2align 3
.L676:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L530
	.p2align 3
.L674:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L562
	.p2align 3
.L577:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L582:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L680
.L580:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L581
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L581:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L582
	add	w3, w3, 16
	b	.L576
	.p2align 3
.L545:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L550:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L681
.L548:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L549
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L549:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L550
	add	w3, w3, 16
	b	.L544
	.p2align 3
.L513:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L518:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L682
.L516:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L517
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L517:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L518
	add	w3, w3, 16
	b	.L512
	.p2align 3
.L662:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w2, w4
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L537
	.p2align 3
.L667:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L569
	.p2align 3
.L657:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L505
	.p2align 3
.L680:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L580
	.p2align 3
.L682:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L516
	.p2align 3
.L681:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L548
	.p2align 3
.L677:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L683
	.p2align 3
.L678:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L532
	.p2align 3
.L679:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L564
.L551:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L555:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L684
.L553:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L554
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L554:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L555
	add	w3, w3, 32
	b	.L544
.L519:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L523:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L685
.L521:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L522
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L522:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L523
	add	w3, w3, 32
	b	.L512
.L583:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L587:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L686
.L585:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L586
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L586:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L587
	add	w3, w3, 32
	b	.L576
	.p2align 3
.L686:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L585
	.p2align 3
.L685:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L521
	.p2align 3
.L684:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L553
	.p2align 3
.L658:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L508
	.p2align 3
.L668:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L572
	.p2align 3
.L663:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w2, w4
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L540
.L660:
	cmp	w4, 64
	mov	w3, w4
	bgt	.L687
	add	w3, w3, 64
	b	.L512
.L665:
	cmp	w4, 64
	mov	w3, w4
	bgt	.L688
	add	w3, w3, 64
	b	.L544
.L670:
	cmp	w4, 64
	mov	w3, w4
	bgt	.L689
	add	w3, w3, 64
	b	.L576
.L689:
	sub	w20, w20, #1
	lsl	w3, w4, 1
	ubfx	x20, x20, 1, 24
	sub	w3, w3, #65
	add	w20, w20, 1
	tbnz	w2, #31, .L690
.L591:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L592
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	mov	w0, 1
.L592:
	add	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	add	w3, w3, 64
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L576
.L688:
	sub	w20, w20, #1
	lsl	w3, w4, 1
	ubfx	x20, x20, 1, 24
	sub	w3, w3, #65
	add	w20, w20, 1
	tbnz	w2, #31, .L691
.L559:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L560
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	mov	w0, 1
.L560:
	add	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	add	w3, w3, 64
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L544
.L687:
	sub	w20, w20, #1
	lsl	w3, w4, 1
	ubfx	x20, x20, 1, 24
	sub	w3, w3, #65
	add	w20, w20, 1
	tbnz	w2, #31, .L692
.L527:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L528
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	mov	w0, 1
.L528:
	add	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	add	w3, w3, 64
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L512
.L659:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L515
.L669:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L579
.L664:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L547
.L690:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w2, w1
	stp	w3, w4, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w3, w4, [x29, 100]
	ldr	w2, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L591
.L692:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w2, w1
	stp	w3, w4, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w3, w4, [x29, 100]
	ldr	w2, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L527
.L691:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w2, w1
	stp	w3, w4, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w3, w4, [x29, 100]
	ldr	w2, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L559
	.size	Vp9_ReadInterModeProbs, .-Vp9_ReadInterModeProbs
	.align	3
.LC12:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadSwitchableInterpProbs
	.type	Vp9_ReadSwitchableInterpProbs, %function
Vp9_ReadSwitchableInterpProbs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x21, x21, 4096
	mov	x19, x1
	bl	_mcount
	ldr	x25, .LC14
	add	x26, x21, 365
	mov	w23, 24
	add	x21, x21, 373
	mov	w22, 16
	mov	w27, 1
	mov	w24, 254
.L759:
	ldp	w2, w0, [x19, 40]
	sub	w20, w0, #1
	lsl	w0, w20, 6
	sub	w0, w0, w20
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w2, #31, .L694
	ldr	w28, [x19, 36]
.L695:
	lsl	w1, w20, 24
	cmp	w1, w28
	bhi	.L696
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w0, w0, w20
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L799
.L697:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L698
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L800
.L700:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L705
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L801
.L707:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L711
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w4, 0
	mov	w3, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L712
	.p2align 3
.L716:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L717
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L717:
	orr	w4, w4, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L802
.L712:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L716
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w3, w4, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w3, w4, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L716
	.p2align 3
.L696:
	uxtw	x0, w20
	ldrb	w0, [x25, x0]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	stp	w28, w2, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w2, #31, .L803
.L727:
	lsl	w0, w20, 24
	cmp	w0, w28
	bhi	.L728
	ldr	w1, [x19, 44]
	sub	w28, w28, w0
	sub	w1, w1, w20
	ldrb	w20, [x25, w1, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L804
.L729:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w1, w20, 1
	lsl	w0, w1, 24
	cmp	w0, w28
	bhi	.L730
	ldr	w20, [x19, 44]
	sub	w28, w28, w0
	sub	w20, w20, w1
	ldrb	w1, [x25, w20, uxtw]
	lsl	w28, w28, w1
	sub	w2, w2, w1
	lsl	w20, w20, w1
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L805
.L732:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w0, w20, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L737
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w20, w0
	ldrb	w0, [x25, w20, uxtw]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	tbnz	w2, #31, .L806
.L739:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L743
	ldr	w20, [x19, 44]
	sub	w28, w28, w1
	mov	w4, 0
	mov	w3, 6
	sub	w0, w20, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L744
	.p2align 3
.L748:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L749
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w3
.L749:
	orr	w4, w4, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w3, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	beq	.L807
.L744:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w2, #31, .L748
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L748
	.p2align 3
.L728:
	uxtw	x0, w20
	ldrb	w0, [x25, x0]
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w28, w2, [x19, 36]
.L761:
	add	x26, x26, 2
	cmp	x26, x21
	bne	.L759
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L730:
	uxtw	x0, w1
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x0]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w1, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L735:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L808
.L733:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L734
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L734:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L735
.L736:
	ldrb	w0, [x26]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L753
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L754
	tbnz	x1, 0, .L809
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L754:
	add	w1, w1, 1
.L756:
	strb	w1, [x26]
	b	.L761
	.p2align 3
.L698:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L703:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L810
.L701:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L702
	ldr	w5, [x19, 44]
	lsl	w0, w27, w4
	sub	w28, w28, w1
	sub	w20, w5, w20
.L702:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L703
.L704:
	ldrb	w0, [x26, -1]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w4, w0, 1
	ldrb	w2, [x1, w3, sxtw]
	cmp	w4, 255
	bgt	.L721
	add	w1, w2, 1
	cmp	w1, w4
	bgt	.L722
	tbnz	x1, 0, .L811
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L722:
	add	w1, w1, 1
.L724:
	strb	w1, [x26, -1]
	ldr	w0, [x19, 44]
	ldp	w28, w2, [x19, 36]
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbz	w2, #31, .L727
.L803:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L727
	.p2align 3
.L721:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	ble	.L812
	mov	w0, 255
	sub	w1, w0, w1
	b	.L724
	.p2align 3
.L753:
	sub	w0, w24, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	ble	.L813
	mov	w0, 255
	sub	w1, w0, w1
.L815:
	strb	w1, [x26]
	b	.L761
	.p2align 3
.L694:
	sub	w3, w23, w2
	sub	w4, w22, w2
	and	w3, w3, -8
	mov	x0, x19
	sub	w4, w4, w3
	mov	w1, w3
	ldr	w28, [x19, 36]
	stp	w2, w4, [x29, 100]
	str	w3, [x29, 108]
	bl	BsGet
	ldp	w2, w4, [x29, 100]
	ldr	w3, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w2, w2, w3
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L695
	.p2align 3
.L813:
	tbnz	x1, 0, .L814
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L815
	.p2align 3
.L812:
	tbnz	x1, 0, .L816
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L724
	.p2align 3
.L737:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L742:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L817
.L740:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L741
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L741:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L742
	add	w3, w3, 16
	b	.L736
	.p2align 3
.L705:
	uxtw	x1, w0
	mov	w3, 0
	mov	w5, 3
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
.L710:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L818
.L708:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L709
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w5
.L709:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w5, w5, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w5, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L710
	add	w3, w3, 16
	b	.L704
	.p2align 3
.L810:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L701
	.p2align 3
.L808:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L733
	.p2align 3
.L816:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L724
	.p2align 3
.L814:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L815
	.p2align 3
.L799:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w2, w4
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L697
	.p2align 3
.L804:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L729
	.p2align 3
.L809:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L756
	.p2align 3
.L811:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	b	.L722
	.p2align 3
.L818:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L708
	.p2align 3
.L817:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w1, w2
	stp	w5, w3, [x29, 96]
	stp	w4, w2, [x29, 104]
	bl	BsGet
	ldp	w4, w2, [x29, 104]
	ldp	w5, w3, [x29, 96]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L740
.L743:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L747:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L819
.L745:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L746
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L746:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L747
	add	w3, w3, 32
	b	.L736
.L711:
	uxtw	x1, w0
	mov	w3, 0
	mov	w4, 4
	ldrb	w20, [x25, x1]
	lsl	w28, w28, w20
	sub	w2, w2, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	.p2align 2
.L715:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w2, #31, .L820
.L713:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L714
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w27, w4
.L714:
	orr	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w4, w4, #1
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	cmn	w4, #1
	stp	w28, w2, [x19, 36]
	str	w20, [x19, 44]
	bne	.L715
	add	w3, w3, 32
	b	.L704
.L806:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L739
.L801:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L707
	.p2align 3
.L819:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L745
	.p2align 3
.L820:
	sub	w1, w23, w2
	sub	w5, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w2, w1, w2
	stp	w4, w3, [x29, 96]
	stp	w5, w2, [x29, 104]
	bl	BsGet
	ldp	w5, w2, [x29, 104]
	ldp	w4, w3, [x29, 96]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L713
	.p2align 3
.L800:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L700
	.p2align 3
.L805:
	sub	w4, w23, w2
	sub	w3, w22, w2
	and	w4, w4, -8
	mov	x0, x19
	sub	w3, w3, w4
	mov	w1, w4
	stp	w2, w3, [x29, 100]
	str	w4, [x29, 108]
	bl	BsGet
	ldp	w2, w3, [x29, 100]
	ldr	w4, [x29, 108]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w2, w4, w2
	orr	w28, w0, w28
	stp	w28, w2, [x19, 36]
	b	.L732
.L807:
	cmp	w4, 64
	mov	w3, w4
	bgt	.L821
	add	w3, w3, 64
	b	.L736
.L821:
	sub	w20, w20, #1
	lsl	w3, w4, 1
	ubfx	x20, x20, 1, 24
	sub	w3, w3, #65
	add	w20, w20, 1
	tbnz	w2, #31, .L822
.L751:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L752
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	mov	w0, 1
.L752:
	add	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	add	w3, w3, 64
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L736
.L802:
	cmp	w4, 64
	mov	w3, w4
	bgt	.L823
	add	w3, w3, 64
	b	.L704
.L823:
	sub	w20, w20, #1
	lsl	w3, w4, 1
	ubfx	x20, x20, 1, 24
	sub	w3, w3, #65
	add	w20, w20, 1
	tbnz	w2, #31, .L824
.L719:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L720
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	mov	w0, 1
.L720:
	add	w3, w3, w0
	ldrb	w0, [x25, w20, uxtw]
	add	w3, w3, 64
	lsl	w28, w28, w0
	sub	w2, w2, w0
	lsl	w20, w20, w0
	str	w20, [x19, 44]
	stp	w28, w2, [x19, 36]
	b	.L704
.L824:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w2, w1
	stp	w3, w4, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w3, w4, [x29, 100]
	ldr	w2, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L719
.L822:
	sub	w1, w23, w2
	sub	w4, w22, w2
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	add	w2, w2, w1
	stp	w3, w4, [x29, 100]
	str	w2, [x29, 108]
	bl	BsGet
	ldp	w3, w4, [x29, 100]
	ldr	w2, [x29, 108]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w28, w0, w28
	b	.L751
	.size	Vp9_ReadSwitchableInterpProbs, .-Vp9_ReadSwitchableInterpProbs
	.align	3
.LC14:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCompPred
	.type	Vp9_ReadCompPred, %function
Vp9_ReadCompPred:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	w19, w2
	mov	x0, x30
	mov	x20, x1
	str	x3, [x29, 112]
	bl	_mcount
	cbnz	w19, .L995
	ldr	x25, .LC16
	add	x21, x21, 4096
	ldp	w26, w19, [x20, 36]
	ldr	w0, [x20, 44]
	str	wzr, [x29, 124]
.L836:
	sub	w0, w0, #1
	add	x23, x21, 334
	lsl	w28, w0, 6
	add	x22, x21, 344
	sub	w0, w28, w0
	mov	w24, 24
	ubfx	x0, x0, 6, 24
	mov	w27, 1
	add	w28, w0, 1
	tbnz	w19, #31, .L996
	.p2align 2
.L838:
	lsl	w1, w28, 24
	cmp	w1, w26
	bhi	.L839
	ldr	w0, [x20, 44]
	sub	w5, w26, w1
	sub	w0, w0, w28
	ldrb	w28, [x25, w0, uxtw]
	lsl	w26, w5, w28
	sub	w19, w19, w28
	lsl	w28, w0, w28
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L997
.L840:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w0, w28, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L841
	ldr	w28, [x20, 44]
	sub	w1, w26, w1
	sub	w28, w28, w0
	ldrb	w0, [x25, w28, uxtw]
	lsl	w26, w1, w0
	sub	w19, w19, w0
	lsl	w28, w28, w0
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L998
.L843:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L848
	ldr	w5, [x20, 44]
	sub	w1, w26, w1
	sub	w0, w5, w0
	ldrb	w5, [x25, w0, uxtw]
	sub	w26, w19, w5
	lsl	w28, w1, w5
	lsl	w19, w0, w5
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L999
.L850:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L854
	sub	w5, w28, w1
	ldr	w1, [x20, 44]
	mov	w7, 0
	mov	w8, 6
	sub	w0, w1, w0
	ldrb	w9, [x25, w0, uxtw]
	lsl	w1, w5, w9
	sub	w26, w26, w9
	lsl	w0, w0, w9
	str	w0, [x20, 44]
	stp	w1, w26, [x20, 36]
	b	.L855
	.p2align 3
.L859:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L860
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	lsl	w0, w27, w8
.L860:
	orr	w7, w7, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w8, w8, #1
	lsl	w1, w28, w0
	sub	w26, w26, w0
	cmn	w8, #1
	lsl	w0, w19, w0
	stp	w1, w26, [x20, 36]
	str	w0, [x20, 44]
	beq	.L1000
.L855:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w19, w0, 1
	tbz	w26, #31, .L859
	sub	w1, w24, w26
	mov	w0, 16
	and	w1, w1, -8
	sub	w6, w0, w26
	sub	w6, w6, w1
	mov	x0, x20
	stp	w8, w7, [x29, 104]
	str	w6, [x29, 120]
	add	w26, w1, w26
	bl	BsGet
	ldr	w6, [x29, 120]
	ldp	w8, w7, [x29, 104]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w28, w0, w28
	b	.L859
	.p2align 3
.L839:
	uxtw	x0, w28
	ldrb	w0, [x25, x0]
	lsl	w26, w26, w0
	sub	w19, w19, w0
	lsl	w0, w28, w0
	str	w0, [x20, 44]
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	stp	w26, w19, [x20, 36]
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbnz	w19, #31, .L1001
.L870:
	lsl	w1, w28, 24
	cmp	w1, w26
	bhi	.L871
	ldr	w0, [x20, 44]
	sub	w1, w26, w1
	sub	w0, w0, w28
	ldrb	w6, [x25, w0, uxtw]
	lsl	w26, w1, w6
	sub	w19, w19, w6
	lsl	w28, w0, w6
	str	w28, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L1002
.L872:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L873
	sub	w28, w26, w1
	ldr	w1, [x20, 44]
	sub	w0, w1, w0
	ldrb	w1, [x25, w0, uxtw]
	sub	w26, w19, w1
	lsl	w28, w28, w1
	lsl	w19, w0, w1
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L1003
.L875:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L880
	ldr	w6, [x20, 44]
	sub	w28, w28, w1
	sub	w0, w6, w0
	ldrb	w19, [x25, w0, uxtw]
	lsl	w28, w28, w19
	sub	w26, w26, w19
	lsl	w19, w0, w19
	str	w19, [x20, 44]
	stp	w28, w26, [x20, 36]
	tbnz	w26, #31, .L1004
.L882:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w28
	bhi	.L886
	sub	w5, w28, w1
	ldr	w1, [x20, 44]
	mov	w19, 0
	mov	w7, 6
	sub	w0, w1, w0
	ldrb	w8, [x25, w0, uxtw]
	lsl	w1, w5, w8
	sub	w26, w26, w8
	lsl	w0, w0, w8
	str	w0, [x20, 44]
	stp	w1, w26, [x20, 36]
	b	.L887
	.p2align 3
.L891:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w5
	bhi	.L892
	ldr	w0, [x20, 44]
	sub	w5, w5, w1
	sub	w28, w0, w28
	lsl	w0, w27, w7
.L892:
	orr	w19, w19, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w7, w7, #1
	lsl	w1, w5, w0
	sub	w26, w26, w0
	cmn	w7, #1
	lsl	w0, w28, w0
	stp	w1, w26, [x20, 36]
	str	w0, [x20, 44]
	beq	.L1005
.L887:
	sub	w0, w0, #1
	mov	w5, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbz	w26, #31, .L891
	sub	w1, w24, w26
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w26
	sub	w8, w8, w1
	mov	x0, x20
	stp	w5, w7, [x29, 104]
	str	w8, [x29, 120]
	add	w26, w1, w26
	bl	BsGet
	ldr	w8, [x29, 120]
	ldp	w5, w7, [x29, 104]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w5, w0, w5
	b	.L891
	.p2align 3
.L871:
	uxtw	x0, w28
	add	x23, x23, 2
	cmp	x23, x22
	ldrb	w0, [x25, x0]
	lsl	w5, w26, w0
	sub	w19, w19, w0
	lsl	w0, w28, w0
	str	w0, [x20, 44]
	stp	w5, w19, [x20, 36]
	beq	.L900
.L1010:
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbz	w19, #31, .L838
.L996:
	sub	w7, w24, w19
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w19
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w7, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L838
	.p2align 3
.L841:
	uxtw	x1, w0
	mov	w6, 0
	ldrb	w28, [x25, x1]
	lsl	w5, w26, w28
	sub	w19, w19, w28
	mov	w26, 3
	lsl	w28, w0, w28
	stp	w5, w19, [x20, 36]
	str	w28, [x20, 44]
.L846:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w28, w28, 1
	tbnz	w19, #31, .L1006
.L844:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w5
	bhi	.L845
	ldr	w8, [x20, 44]
	lsl	w0, w27, w26
	sub	w5, w5, w1
	sub	w28, w8, w28
.L845:
	orr	w6, w6, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w26, w26, #1
	lsl	w5, w5, w0
	sub	w19, w19, w0
	lsl	w28, w28, w0
	cmn	w26, #1
	stp	w5, w19, [x20, 36]
	str	w28, [x20, 44]
	bne	.L846
.L847:
	ldrb	w0, [x23, -1]
	add	x1, x25, 256
	sub	w0, w0, #1
	ldrb	w5, [x1, w6, sxtw]
	lsl	w6, w0, 1
	cmp	w6, 255
	bgt	.L864
	add	w1, w5, 1
	cmp	w1, w6
	bgt	.L865
	tbnz	x1, 0, .L1007
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L865:
	add	w1, w1, 1
.L867:
	strb	w1, [x23, -1]
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbz	w19, #31, .L870
.L1001:
	sub	w7, w24, w19
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w19
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w7, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L870
	.p2align 3
.L873:
	uxtw	x1, w0
	ldrb	w6, [x25, x1]
	lsl	w28, w26, w6
	sub	w5, w19, w6
	mov	w26, 3
	lsl	w19, w0, w6
	stp	w28, w5, [x20, 36]
	mov	w6, 0
	str	w19, [x20, 44]
.L878:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L1008
.L876:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L877
	ldr	w8, [x20, 44]
	lsl	w0, w27, w26
	sub	w28, w28, w1
	sub	w19, w8, w19
.L877:
	orr	w6, w6, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w26, w26, #1
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w28, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L878
.L879:
	ldrb	w0, [x23]
	add	x1, x25, 256
	sub	w0, w0, #1
	ldrb	w5, [x1, w6, sxtw]
	lsl	w6, w0, 1
	cmp	w6, 255
	bgt	.L894
	add	w1, w5, 1
	cmp	w1, w6
	bgt	.L895
	tbnz	x1, 0, .L1009
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L895:
	add	w1, w1, 1
.L897:
	strb	w1, [x23]
.L1013:
	add	x23, x23, 2
	cmp	x23, x22
	bne	.L1010
.L900:
	ldr	w0, [x29, 124]
	cbnz	w0, .L1011
.L902:
	ldr	x0, [x29, 112]
	ldr	w1, [x29, 124]
	str	w1, [x0]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L894:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w5, 1
	cmp	w1, w0, lsl 1
	ble	.L1012
	mov	w0, 255
	sub	w1, w0, w1
.L1022:
	strb	w1, [x23]
	b	.L1013
	.p2align 3
.L864:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w5, 1
	cmp	w1, w0, lsl 1
	ble	.L1014
	mov	w0, 255
	sub	w1, w0, w1
	b	.L867
	.p2align 3
.L1011:
	ldp	w26, w19, [x20, 36]
	ldr	w0, [x20, 44]
.L837:
	sub	w0, w0, #1
	add	x28, x21, 328
	lsl	w1, w0, 6
	add	x21, x21, 333
	sub	w0, w1, w0
	mov	w24, 24
	ubfx	x0, x0, 6, 24
	mov	w23, 16
	mov	w27, 1
	add	w22, w0, 1
	tbnz	w19, #31, .L1015
	.p2align 2
.L903:
	lsl	w1, w22, 24
	cmp	w1, w26
	bhi	.L904
	ldr	w0, [x20, 44]
	sub	w5, w26, w1
	sub	w0, w0, w22
	ldrb	w22, [x25, w0, uxtw]
	lsl	w26, w5, w22
	sub	w19, w19, w22
	lsl	w22, w0, w22
	str	w22, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L1016
.L905:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w0, w22, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L906
	ldr	w22, [x20, 44]
	sub	w1, w26, w1
	sub	w22, w22, w0
	ldrb	w0, [x25, w22, uxtw]
	lsl	w26, w1, w0
	sub	w19, w19, w0
	lsl	w22, w22, w0
	str	w22, [x20, 44]
	stp	w26, w19, [x20, 36]
	tbnz	w19, #31, .L1017
.L908:
	sub	w0, w22, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L913
	ldr	w4, [x20, 44]
	sub	w1, w26, w1
	sub	w0, w4, w0
	ldrb	w4, [x25, w0, uxtw]
	sub	w26, w19, w4
	lsl	w22, w1, w4
	lsl	w19, w0, w4
	str	w19, [x20, 44]
	stp	w22, w26, [x20, 36]
	tbnz	w26, #31, .L1018
.L915:
	sub	w0, w19, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w22
	bhi	.L919
	sub	w6, w22, w1
	ldr	w1, [x20, 44]
	mov	w19, 0
	mov	w7, 6
	sub	w0, w1, w0
	ldrb	w4, [x25, w0, uxtw]
	lsl	w1, w6, w4
	sub	w26, w26, w4
	lsl	w0, w0, w4
	str	w0, [x20, 44]
	stp	w1, w26, [x20, 36]
	b	.L920
	.p2align 3
.L924:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w4
	bhi	.L925
	ldr	w0, [x20, 44]
	sub	w4, w4, w1
	sub	w22, w0, w22
	lsl	w0, w27, w7
.L925:
	orr	w19, w19, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w7, w7, #1
	lsl	w1, w4, w0
	sub	w26, w26, w0
	cmn	w7, #1
	lsl	w0, w22, w0
	stp	w1, w26, [x20, 36]
	str	w0, [x20, 44]
	beq	.L1019
.L920:
	sub	w0, w0, #1
	mov	w4, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbz	w26, #31, .L924
	sub	w1, w24, w26
	sub	w6, w23, w26
	and	w1, w1, -8
	mov	x0, x20
	sub	w6, w6, w1
	add	w26, w1, w26
	stp	w4, w7, [x29, 104]
	str	w6, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 120]
	ldp	w4, w7, [x29, 104]
	and	w6, w6, 7
	lsl	w0, w0, w6
	orr	w4, w0, w4
	b	.L924
	.p2align 3
.L1014:
	tbnz	x1, 0, .L1020
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L867
	.p2align 3
.L1012:
	tbnz	x1, 0, .L1021
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L1022
	.p2align 3
.L848:
	uxtw	x1, w0
	ldrb	w6, [x25, x1]
	lsl	w1, w26, w6
	sub	w5, w19, w6
	lsl	w0, w0, w6
	mov	w26, 3
	mov	w6, 0
	str	w0, [x20, 44]
	stp	w1, w5, [x20, 36]
.L853:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbnz	w5, #31, .L1023
.L851:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w19
	bhi	.L852
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w28, w0, w28
	lsl	w0, w27, w26
.L852:
	orr	w6, w6, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w28, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L853
	add	w6, w6, 16
	b	.L847
	.p2align 3
.L880:
	uxtw	x1, w0
	ldrb	w6, [x25, x1]
	sub	w5, w26, w6
	lsl	w1, w28, w6
	lsl	w0, w0, w6
	mov	w26, 3
	mov	w6, 0
	str	w0, [x20, 44]
	stp	w1, w5, [x20, 36]
.L885:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w28, w0, 1
	tbnz	w5, #31, .L1024
.L883:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w19
	bhi	.L884
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w28, w0, w28
	lsl	w0, w27, w26
.L884:
	orr	w6, w6, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w28, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L885
	add	w6, w6, 16
	b	.L879
	.p2align 3
.L904:
	uxtw	x0, w22
	ldrb	w0, [x25, x0]
	lsl	w5, w26, w0
	sub	w19, w19, w0
	lsl	w0, w22, w0
	str	w0, [x20, 44]
	stp	w5, w19, [x20, 36]
.L937:
	add	x28, x28, 1
	cmp	x28, x21
	beq	.L902
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w22, w0, 1
	tbz	w19, #31, .L903
.L1015:
	sub	w6, w24, w19
	sub	w4, w23, w19
	and	w6, w6, -8
	mov	x0, x20
	sub	w4, w4, w6
	mov	w1, w6
	str	w4, [x29, 108]
	str	w6, [x29, 120]
	bl	BsGet
	ldr	w4, [x29, 108]
	ldr	w6, [x29, 120]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w19, w6, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L903
	.p2align 3
.L906:
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w22, [x25, x1]
	lsl	w5, w26, w22
	sub	w19, w19, w22
	mov	w26, 3
	lsl	w22, w0, w22
	stp	w5, w19, [x20, 36]
	str	w22, [x20, 44]
.L911:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w22, w22, 1
	tbnz	w19, #31, .L1025
.L909:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w5
	bhi	.L910
	ldr	w7, [x20, 44]
	lsl	w0, w27, w26
	sub	w5, w5, w1
	sub	w22, w7, w22
.L910:
	orr	w4, w4, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w26, w26, #1
	lsl	w5, w5, w0
	sub	w19, w19, w0
	lsl	w22, w22, w0
	cmn	w26, #1
	stp	w5, w19, [x20, 36]
	str	w22, [x20, 44]
	bne	.L911
.L912:
	ldrb	w0, [x28]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w5, w0, 1
	ldrb	w4, [x1, w4, sxtw]
	cmp	w5, 255
	bgt	.L927
	add	w1, w4, 1
	cmp	w1, w5
	bgt	.L928
	tbnz	x1, 0, .L1026
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L928:
	add	w1, w1, 1
.L930:
	strb	w1, [x28]
	b	.L937
	.p2align 3
.L927:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w4, 1
	cmp	w1, w0, lsl 1
	bgt	.L931
	tbnz	x1, 0, .L1027
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L931:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x28]
	b	.L937
	.p2align 3
.L1008:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w28, w0, w28
	b	.L876
	.p2align 3
.L1006:
	sub	w1, w24, w19
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w19
	sub	w8, w8, w1
	mov	x0, x20
	stp	w5, w6, [x29, 104]
	str	w8, [x29, 120]
	add	w19, w1, w19
	bl	BsGet
	ldr	w8, [x29, 120]
	ldp	w5, w6, [x29, 104]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w5, w0, w5
	b	.L844
	.p2align 3
.L1025:
	sub	w1, w24, w19
	sub	w7, w23, w19
	and	w1, w1, -8
	mov	x0, x20
	sub	w7, w7, w1
	add	w19, w1, w19
	stp	w5, w4, [x29, 104]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w7, [x29, 120]
	ldp	w5, w4, [x29, 104]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w5, w0, w5
	b	.L909
	.p2align 3
.L995:
	ldp	w19, w0, [x20, 40]
	sub	w0, w0, #1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbnz	w19, #31, .L827
	ldr	w5, [x20, 36]
.L828:
	lsl	w23, w22, 24
	cmp	w23, w5
	bhi	.L829
	ldr	w0, [x20, 44]
	sub	w5, w5, w23
	ldr	x25, .LC16
	sub	w0, w0, w22
	ldrb	w22, [x25, w0, uxtw]
	lsl	w5, w5, w22
	sub	w19, w19, w22
	lsl	w22, w0, w22
	str	w22, [x20, 44]
	stp	w5, w19, [x20, 36]
	mov	w23, w5
	tbnz	w19, #31, .L1028
.L830:
	sub	w0, w22, #1
	mov	w1, 1
	ubfx	x0, x0, 1, 24
	str	w1, [x29, 124]
	add	w0, w0, w1
	lsl	w1, w0, 24
	cmp	w1, w23
	bhi	.L831
	ldr	w3, [x20, 44]
	sub	w23, w23, w1
	mov	w1, 2
	str	w1, [x29, 124]
	sub	w0, w3, w0
.L831:
	ldrb	w1, [x25, w0, uxtw]
	ldr	w2, [x29, 124]
	lsl	w26, w23, w1
	sub	w19, w19, w1
	lsl	w0, w0, w1
	cmp	w2, 2
	stp	w26, w19, [x20, 36]
	str	w0, [x20, 44]
	bne	.L832
	add	x21, x21, 4096
	mov	w24, 24
	add	x28, x21, 323
	add	x22, x21, 328
	mov	w23, 16
	b	.L835
	.p2align 3
.L1030:
	ldr	w3, [x20, 44]
	sub	w27, w3, w27
	ldrb	w3, [x25, w27, uxtw]
	sub	w19, w19, w3
	lsl	w4, w4, w3
	lsl	w27, w27, w3
	str	w27, [x20, 44]
	stp	w4, w19, [x20, 36]
	bl	Vp9_DiffUpdateProb
	ldr	w0, [x20, 44]
	ldp	w26, w19, [x20, 36]
.L934:
	add	x28, x28, 1
	cmp	x22, x28
	beq	.L836
.L835:
	sub	w0, w0, #1
	lsl	w27, w0, 6
	sub	w0, w27, w0
	ubfx	x0, x0, 6, 24
	add	w27, w0, 1
	tbnz	w19, #31, .L1029
.L833:
	lsl	w3, w27, 24
	mov	x1, x28
	cmp	w3, w26
	mov	x0, x20
	sub	w4, w26, w3
	bls	.L1030
	uxtw	x0, w27
	ldrb	w0, [x25, x0]
	lsl	w26, w26, w0
	sub	w19, w19, w0
	lsl	w0, w27, w0
	str	w0, [x20, 44]
	stp	w26, w19, [x20, 36]
	b	.L934
	.p2align 3
.L1007:
	add	w1, w5, 2
	sub	w1, w0, w1, lsr 1
	b	.L865
	.p2align 3
.L1009:
	add	w1, w5, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L897
	.p2align 3
.L829:
	ldr	x25, .LC16
	uxtw	x0, w22
	add	x21, x21, 4096
	str	wzr, [x29, 124]
	ldrb	w0, [x25, x0]
	lsl	w26, w5, w0
	sub	w19, w19, w0
	lsl	w0, w22, w0
	str	w0, [x20, 44]
	stp	w26, w19, [x20, 36]
	b	.L836
	.p2align 3
.L1026:
	add	w1, w4, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L930
	.p2align 3
.L1021:
	add	w5, w5, 2
	sub	w1, w0, w5, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L1022
	.p2align 3
.L1020:
	add	w5, w5, 2
	sub	w1, w0, w5, lsr 1
	mov	w0, 255
	sub	w1, w0, w1
	b	.L867
	.p2align 3
.L913:
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w6, [x25, x1]
	lsl	w1, w26, w6
	sub	w5, w19, w6
	lsl	w0, w0, w6
	mov	w26, 3
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
.L918:
	sub	w0, w0, #1
	mov	w19, w1
	ubfx	x0, x0, 1, 24
	add	w22, w0, 1
	tbnz	w5, #31, .L1031
.L916:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w19
	bhi	.L917
	ldr	w0, [x20, 44]
	sub	w19, w19, w1
	sub	w22, w0, w22
	lsl	w0, w27, w26
.L917:
	orr	w4, w4, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w26, w26, #1
	lsl	w1, w19, w0
	sub	w5, w5, w0
	cmn	w26, #1
	lsl	w0, w22, w0
	stp	w1, w5, [x20, 36]
	str	w0, [x20, 44]
	bne	.L918
	add	w4, w4, 16
	b	.L912
	.p2align 3
.L1027:
	add	w4, w4, 2
	sub	w1, w0, w4, lsr 1
	b	.L931
.L919:
	uxtw	x1, w0
	mov	w4, 0
	ldrb	w19, [x25, x1]
	sub	w5, w26, w19
	lsl	w1, w22, w19
	mov	w26, 4
	lsl	w19, w0, w19
	stp	w1, w5, [x20, 36]
	str	w19, [x20, 44]
	.p2align 2
.L923:
	sub	w19, w19, #1
	mov	w22, w1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L1032
.L921:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L922
	ldr	w0, [x20, 44]
	sub	w22, w22, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L922:
	orr	w4, w4, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w26, w26, #1
	lsl	w1, w22, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w1, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L923
	add	w4, w4, 32
	b	.L912
	.p2align 3
.L1029:
	sub	w4, w24, w19
	sub	w3, w23, w19
	and	w4, w4, -8
	mov	x0, x20
	sub	w3, w3, w4
	mov	w1, w4
	str	w3, [x29, 108]
	str	w4, [x29, 120]
	bl	BsGet
	ldr	w3, [x29, 108]
	ldr	w4, [x29, 120]
	and	w3, w3, 7
	lsl	w0, w0, w3
	add	w19, w4, w19
	orr	w0, w0, w26
	mov	w26, w0
	stp	w0, w19, [x20, 36]
	b	.L833
	.p2align 3
.L1002:
	sub	w5, w24, w19
	mov	w0, 16
	and	w5, w5, -8
	sub	w6, w0, w19
	sub	w6, w6, w5
	mov	w1, w5
	mov	x0, x20
	str	w6, [x29, 108]
	str	w5, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w5, w19
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w19, [x20, 36]
	b	.L872
	.p2align 3
.L997:
	sub	w7, w24, w19
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w19
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w19, w7
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L840
	.p2align 3
.L1016:
	sub	w6, w24, w19
	sub	w4, w23, w19
	and	w6, w6, -8
	mov	x0, x20
	sub	w4, w4, w6
	mov	w1, w6
	str	w4, [x29, 108]
	str	w6, [x29, 120]
	bl	BsGet
	ldr	w4, [x29, 108]
	ldr	w6, [x29, 120]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w19, w6, w19
	orr	w5, w0, w26
	mov	w26, w5
	stp	w5, w19, [x20, 36]
	b	.L905
	.p2align 3
.L1024:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w19, w0, w19
	b	.L883
	.p2align 3
.L1023:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w19, w0, w19
	b	.L851
	.p2align 3
.L1031:
	sub	w1, w24, w5
	sub	w7, w23, w5
	and	w1, w1, -8
	mov	x0, x20
	sub	w7, w7, w1
	add	w5, w1, w5
	stp	w4, w7, [x29, 104]
	str	w5, [x29, 120]
	bl	BsGet
	ldp	w4, w7, [x29, 104]
	ldr	w5, [x29, 120]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w19, w0, w19
	b	.L916
.L886:
	uxtw	x1, w0
	mov	w6, 0
	ldrb	w19, [x25, x1]
	sub	w5, w26, w19
	lsl	w28, w28, w19
	mov	w26, 4
	lsl	w19, w0, w19
	stp	w28, w5, [x20, 36]
	str	w19, [x20, 44]
	.p2align 2
.L890:
	sub	w19, w19, #1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L1033
.L888:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L889
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L889:
	orr	w6, w6, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w26, w26, #1
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w28, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L890
	add	w6, w6, 32
	b	.L879
.L854:
	uxtw	x1, w0
	mov	w6, 0
	ldrb	w19, [x25, x1]
	sub	w5, w26, w19
	lsl	w1, w28, w19
	mov	w26, 4
	lsl	w19, w0, w19
	stp	w1, w5, [x20, 36]
	str	w19, [x20, 44]
	.p2align 2
.L858:
	sub	w19, w19, #1
	mov	w28, w1
	ubfx	x19, x19, 1, 24
	add	w19, w19, 1
	tbnz	w5, #31, .L1034
.L856:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L857
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	lsl	w0, w27, w26
.L857:
	orr	w6, w6, w0
	ldrb	w0, [x25, w19, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w5, w5, w0
	lsl	w19, w19, w0
	cmn	w26, #1
	stp	w1, w5, [x20, 36]
	str	w19, [x20, 44]
	bne	.L858
	add	w6, w6, 32
	b	.L847
.L832:
	ldr	w1, [x29, 124]
	add	x21, x21, 4096
	cmp	w1, 1
	beq	.L837
	b	.L836
	.p2align 3
.L1034:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w28, w0, w28
	b	.L856
	.p2align 3
.L1033:
	sub	w1, w24, w5
	mov	w0, 16
	and	w1, w1, -8
	sub	w8, w0, w5
	sub	w8, w8, w1
	add	w5, w1, w5
	mov	x0, x20
	str	w5, [x29, 120]
	stp	w6, w8, [x29, 104]
	bl	BsGet
	ldp	w6, w8, [x29, 104]
	ldr	w5, [x29, 120]
	and	w8, w8, 7
	lsl	w0, w0, w8
	orr	w28, w0, w28
	b	.L888
	.p2align 3
.L1003:
	sub	w7, w24, w26
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w26
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	add	w5, w7, w26
	lsl	w0, w0, w6
	orr	w28, w0, w28
	mov	w26, w5
	stp	w28, w5, [x20, 36]
	b	.L875
	.p2align 3
.L998:
	sub	w7, w24, w19
	mov	w0, 16
	and	w7, w7, -8
	sub	w6, w0, w19
	sub	w6, w6, w7
	mov	w1, w7
	mov	x0, x20
	str	w6, [x29, 108]
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w7, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w7, w19
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w19, [x20, 36]
	b	.L843
	.p2align 3
.L827:
	mov	w24, 24
	mov	w25, 16
	sub	w24, w24, w19
	sub	w25, w25, w19
	and	w24, w24, -8
	mov	x0, x20
	mov	w1, w24
	sub	w25, w25, w24
	ldr	w23, [x20, 36]
	and	w25, w25, 7
	bl	BsGet
	lsl	w0, w0, w25
	add	w19, w19, w24
	orr	w5, w0, w23
	stp	w5, w19, [x20, 36]
	b	.L828
.L1032:
	sub	w1, w24, w5
	sub	w7, w23, w5
	and	w1, w1, -8
	mov	x0, x20
	sub	w7, w7, w1
	add	w5, w1, w5
	stp	w4, w7, [x29, 104]
	str	w5, [x29, 120]
	bl	BsGet
	ldp	w4, w7, [x29, 104]
	ldr	w5, [x29, 120]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w22, w0, w22
	b	.L921
	.p2align 3
.L1017:
	sub	w5, w24, w19
	sub	w6, w23, w19
	and	w5, w5, -8
	mov	x0, x20
	sub	w6, w6, w5
	mov	w1, w5
	str	w6, [x29, 108]
	str	w5, [x29, 120]
	bl	BsGet
	ldr	w6, [x29, 108]
	ldr	w5, [x29, 120]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w19, w5, w19
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w19, [x20, 36]
	b	.L908
.L1000:
	cmp	w7, 64
	mov	w6, w7
	bgt	.L1035
	add	w6, w6, 64
	b	.L847
.L1035:
	sub	w19, w0, #1
	lsl	w7, w7, 1
	ubfx	x19, x19, 1, 24
	sub	w6, w7, #65
	add	w19, w19, 1
	mov	w28, w1
	tbnz	w26, #31, .L1036
.L862:
	lsl	w1, w19, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L863
	ldr	w0, [x20, 44]
	sub	w28, w28, w1
	sub	w19, w0, w19
	mov	w0, 1
.L863:
	ldrb	w7, [x25, w19, uxtw]
	add	w6, w6, w0
	add	w6, w6, 64
	lsl	w1, w28, w7
	sub	w0, w26, w7
	lsl	w19, w19, w7
	str	w19, [x20, 44]
	stp	w1, w0, [x20, 36]
	b	.L847
.L1005:
	cmp	w19, 64
	bgt	.L1037
	add	w6, w19, 64
	b	.L879
.L1037:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w19, lsl 1
	sub	w19, w0, #65
	add	w6, w19, 64
	b	.L879
.L1019:
	cmp	w19, 64
	bgt	.L1038
	add	w4, w19, 64
	b	.L912
.L1038:
	mov	w1, 128
	mov	x0, x20
	bl	Vp9_Cabac_Read
	add	w0, w0, w19, lsl 1
	sub	w19, w0, #65
	add	w4, w19, 64
	b	.L912
.L1028:
	mov	w1, 24
	mov	w24, 16
	sub	w1, w1, w19
	sub	w24, w24, w19
	and	w1, w1, -8
	mov	x0, x20
	sub	w24, w24, w1
	add	w19, w1, w19
	and	w24, w24, 7
	bl	BsGet
	lsl	w0, w0, w24
	orr	w23, w0, w23
	b	.L830
.L999:
	sub	w5, w24, w26
	mov	w0, 16
	and	w5, w5, -8
	sub	w7, w0, w26
	sub	w7, w7, w5
	mov	w1, w5
	mov	x0, x20
	str	w7, [x29, 108]
	str	w5, [x29, 120]
	bl	BsGet
	ldr	w7, [x29, 108]
	ldr	w5, [x29, 120]
	and	w7, w7, 7
	lsl	w0, w0, w7
	add	w5, w5, w26
	orr	w1, w0, w28
	mov	w26, w5
	mov	w28, w1
	stp	w1, w5, [x20, 36]
	b	.L850
.L1004:
	sub	w5, w24, w26
	mov	w0, 16
	and	w5, w5, -8
	sub	w7, w0, w26
	sub	w7, w7, w5
	mov	w1, w5
	mov	x0, x20
	str	w7, [x29, 108]
	str	w5, [x29, 120]
	bl	BsGet
	ldr	w7, [x29, 108]
	ldr	w5, [x29, 120]
	and	w7, w7, 7
	add	w5, w5, w26
	lsl	w0, w0, w7
	orr	w28, w0, w28
	mov	w26, w5
	stp	w28, w5, [x20, 36]
	b	.L882
.L1018:
	sub	w6, w24, w26
	sub	w4, w23, w26
	and	w6, w6, -8
	mov	x0, x20
	sub	w4, w4, w6
	mov	w1, w6
	str	w4, [x29, 108]
	str	w6, [x29, 120]
	bl	BsGet
	ldr	w4, [x29, 108]
	ldr	w6, [x29, 120]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w5, w6, w26
	orr	w1, w0, w22
	mov	w26, w5
	mov	w22, w1
	stp	w1, w5, [x20, 36]
	b	.L915
.L1036:
	sub	w1, w24, w26
	mov	w0, 16
	and	w1, w1, -8
	sub	w7, w0, w26
	sub	w7, w7, w1
	mov	x0, x20
	str	w6, [x29, 108]
	add	w26, w26, w1
	str	w7, [x29, 120]
	bl	BsGet
	ldr	w7, [x29, 120]
	ldr	w6, [x29, 108]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w28, w0, w28
	b	.L862
	.size	Vp9_ReadCompPred, .-Vp9_ReadCompPred
	.align	3
.LC16:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadMvProbs
	.type	Vp9_ReadMvProbs, %function
Vp9_ReadMvProbs:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	str	x1, [x29, 104]
	str	w2, [x29, 144]
	bl	_mcount
	ldp	w28, w5, [x19, 36]
	ldr	x24, .LC18
	add	x26, x20, 2
	ldr	w0, [x19, 44]
	mov	w27, 1
	add	x20, x20, 5
.L1045:
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w23, w0, 1
	tbnz	w5, #31, .L1145
.L1040:
	lsl	w1, w23, 24
	cmp	w1, w28
	bhi	.L1041
	ldr	w0, [x19, 44]
	sub	w1, w28, w1
	mov	w21, 0
	mov	w28, 6
	sub	w0, w0, w23
	ldrb	w23, [x24, w0, uxtw]
	lsl	w1, w1, w23
	sub	w25, w5, w23
	lsl	w23, w0, w23
	str	w23, [x19, 44]
	stp	w1, w25, [x19, 36]
	b	.L1044
	.p2align 3
.L1042:
	lsl	w1, w23, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L1043
	ldr	w4, [x19, 44]
	lsl	w0, w27, w28
	sub	w22, w22, w1
	sub	w23, w4, w23
.L1043:
	orr	w21, w21, w0
	ldrb	w0, [x24, w23, uxtw]
	sub	w28, w28, #1
	lsl	w1, w22, w0
	sub	w25, w25, w0
	lsl	w23, w23, w0
	cmn	w28, #1
	stp	w1, w25, [x19, 36]
	str	w23, [x19, 44]
	beq	.L1146
.L1044:
	sub	w23, w23, #1
	mov	w22, w1
	ubfx	x23, x23, 1, 24
	add	w23, w23, 1
	tbz	w25, #31, .L1042
	mov	w0, 24
	sub	w1, w0, w25
	mov	w0, 16
	sub	w4, w0, w25
	and	w1, w1, -8
	sub	w4, w4, w1
	mov	x0, x19
	str	w4, [x29, 152]
	add	w25, w1, w25
	bl	BsGet
	ldr	w4, [x29, 152]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w22, w0, w22
	b	.L1042
	.p2align 3
.L1146:
	lsl	w0, w21, 1
	orr	w0, w0, 1
	strb	w0, [x26]
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
.L1102:
	add	x26, x26, 1
	cmp	x20, x26
	bne	.L1045
	ldr	x1, [x29, 104]
	mov	w22, 24
	mov	w21, 16
	mov	w27, 1
	add	x2, x1, 25
	add	x23, x1, 37
	add	x1, x1, 27
	stp	x1, x2, [x29, 112]
.L1071:
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w6, w0, 1
	tbnz	w5, #31, .L1147
.L1046:
	lsl	w0, w6, 24
	cmp	w0, w28
	bhi	.L1047
	sub	w28, w28, w0
	ldr	w0, [x19, 44]
	mov	w25, 0
	mov	w26, 6
	sub	w0, w0, w6
	ldrb	w6, [x24, w0, uxtw]
	lsl	w1, w28, w6
	sub	w4, w5, w6
	lsl	w0, w0, w6
	str	w0, [x19, 44]
	stp	w1, w4, [x19, 36]
	b	.L1050
	.p2align 3
.L1048:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1049
	ldr	w7, [x19, 44]
	lsl	w0, w27, w26
	sub	w28, w28, w1
	sub	w20, w7, w20
.L1049:
	orr	w25, w25, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w4, w4, w0
	cmn	w26, #1
	lsl	w0, w20, w0
	stp	w1, w4, [x19, 36]
	str	w0, [x19, 44]
	beq	.L1148
.L1050:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbz	w4, #31, .L1048
	sub	w1, w22, w4
	sub	w7, w21, w4
	and	w1, w1, -8
	mov	x0, x19
	sub	w7, w7, w1
	add	w4, w1, w4
	stp	w7, w4, [x29, 148]
	bl	BsGet
	ldp	w7, w4, [x29, 148]
	and	w7, w7, 7
	lsl	w0, w0, w7
	orr	w28, w0, w28
	b	.L1048
	.p2align 3
.L1148:
	ldr	x1, [x29, 120]
	lsl	w0, w25, 1
	orr	w0, w0, 1
	strb	w0, [x1, -25]
	ldp	w26, w20, [x19, 36]
	ldr	w0, [x19, 44]
.L1103:
	sub	x1, x23, #22
	sub	x25, x23, #32
	str	x1, [x29, 128]
	.p2align 2
.L1056:
	sub	w0, w0, #1
	lsl	w9, w0, 6
	sub	w0, w9, w0
	ubfx	x0, x0, 6, 24
	add	w9, w0, 1
	tbnz	w20, #31, .L1149
.L1051:
	lsl	w1, w9, 24
	cmp	w1, w26
	bhi	.L1052
	ldr	w0, [x19, 44]
	sub	w4, w26, w1
	mov	w6, 6
	mov	w26, 0
	sub	w0, w0, w9
	ldrb	w1, [x24, w0, uxtw]
	sub	w28, w20, w1
	lsl	w4, w4, w1
	lsl	w20, w0, w1
	str	w20, [x19, 44]
	stp	w4, w28, [x19, 36]
	b	.L1055
	.p2align 3
.L1053:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w4
	bhi	.L1054
	ldr	w9, [x19, 44]
	lsl	w0, w27, w6
	sub	w4, w4, w1
	sub	w20, w9, w20
.L1054:
	orr	w26, w26, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w6, w6, #1
	lsl	w4, w4, w0
	sub	w28, w28, w0
	lsl	w20, w20, w0
	cmn	w6, #1
	stp	w4, w28, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1150
.L1055:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w28, #31, .L1053
	sub	w1, w22, w28
	sub	w9, w21, w28
	and	w1, w1, -8
	mov	x0, x19
	sub	w9, w9, w1
	str	w4, [x29, 136]
	stp	w6, w9, [x29, 148]
	add	w28, w1, w28
	bl	BsGet
	ldp	w6, w9, [x29, 148]
	ldr	w4, [x29, 136]
	and	w9, w9, 7
	lsl	w0, w0, w9
	orr	w4, w0, w4
	b	.L1053
	.p2align 3
.L1150:
	lsl	w8, w26, 1
	orr	w8, w8, 1
	strb	w8, [x25]
	ldp	w26, w20, [x19, 36]
	ldr	w0, [x19, 44]
.L1104:
	ldr	x1, [x29, 128]
	add	x25, x25, 1
	cmp	x1, x25
	bne	.L1056
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w6, w0, 1
	tbnz	w20, #31, .L1151
.L1057:
	lsl	w0, w6, 24
	cmp	w0, w26
	bhi	.L1058
	sub	w4, w26, w0
	ldr	w0, [x19, 44]
	mov	w5, 6
	mov	w26, 0
	sub	w0, w0, w6
	ldrb	w1, [x24, w0, uxtw]
	lsl	w4, w4, w1
	sub	w20, w20, w1
	lsl	w0, w0, w1
	str	w0, [x19, 44]
	stp	w4, w20, [x19, 36]
	b	.L1061
	.p2align 3
.L1060:
	ldr	w8, [x19, 44]
	sub	w1, w1, w0
	sub	w25, w8, w25
.L1063:
	ldrb	w0, [x24, w25, uxtw]
	sub	w5, w5, #1
	orr	w26, w26, w4
	cmn	w5, #1
	lsl	w4, w1, w0
	sub	w20, w20, w0
	lsl	w0, w25, w0
	str	w0, [x19, 44]
	stp	w4, w20, [x19, 36]
	beq	.L1152
.L1061:
	sub	w0, w0, #1
	mov	w1, w4
	ubfx	x0, x0, 1, 24
	add	w25, w0, 1
	tbnz	w20, #31, .L1059
.L1064:
	lsl	w0, w25, 24
	lsl	w4, w27, w5
	cmp	w0, w1
	bls	.L1060
	mov	w4, 0
	b	.L1063
	.p2align 3
.L1052:
	uxtw	x0, w9
	ldrb	w0, [x24, x0]
	lsl	w26, w26, w0
	sub	w20, w20, w0
	lsl	w0, w9, w0
	str	w0, [x19, 44]
	stp	w26, w20, [x19, 36]
	b	.L1104
	.p2align 3
.L1149:
	sub	w6, w22, w20
	sub	w5, w21, w20
	and	w28, w6, -8
	mov	x0, x19
	sub	w5, w5, w28
	mov	w1, w28
	stp	w9, w5, [x29, 148]
	bl	BsGet
	ldp	w9, w5, [x29, 148]
	and	w5, w5, 7
	lsl	w0, w0, w5
	add	w5, w28, w20
	orr	w4, w0, w26
	mov	w20, w5
	mov	w26, w4
	stp	w4, w5, [x19, 36]
	b	.L1051
	.p2align 3
.L1152:
	ldr	x1, [x29, 120]
	lsl	w0, w26, 1
	orr	w0, w0, 1
	strb	w0, [x1]
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
.L1105:
	sub	x26, x23, #10
	.p2align 2
.L1070:
	sub	w0, w0, #1
	lsl	w20, w0, 6
	sub	w0, w20, w0
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w5, #31, .L1153
.L1065:
	lsl	w1, w20, 24
	cmp	w1, w28
	bhi	.L1066
	ldr	w0, [x19, 44]
	sub	w28, w28, w1
	mov	w25, 0
	mov	w7, 6
	sub	w0, w0, w20
	ldrb	w20, [x24, w0, uxtw]
	lsl	w28, w28, w20
	sub	w4, w5, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w28, w4, [x19, 36]
	b	.L1069
	.p2align 3
.L1067:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1068
	ldr	w5, [x19, 44]
	lsl	w0, w27, w7
	sub	w28, w28, w1
	sub	w20, w5, w20
.L1068:
	orr	w25, w25, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w7, w7, #1
	lsl	w28, w28, w0
	sub	w4, w4, w0
	lsl	w20, w20, w0
	cmn	w7, #1
	stp	w28, w4, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1154
.L1069:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w4, #31, .L1067
	sub	w1, w22, w4
	sub	w5, w21, w4
	and	w1, w1, -8
	mov	x0, x19
	sub	w5, w5, w1
	add	w4, w1, w4
	str	w7, [x29, 136]
	stp	w5, w4, [x29, 148]
	bl	BsGet
	ldp	w5, w4, [x29, 148]
	ldr	w7, [x29, 136]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L1067
	.p2align 3
.L1154:
	lsl	w8, w25, 1
	orr	w8, w8, 1
	strb	w8, [x26]
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
.L1106:
	add	x26, x26, 1
	cmp	x23, x26
	bne	.L1070
	ldp	x2, x1, [x29, 112]
	add	x23, x23, 10
	add	x1, x1, 1
	str	x1, [x29, 120]
	cmp	x1, x2
	bne	.L1071
	ldr	x1, [x29, 104]
	mov	w27, 1
	str	x1, [x29, 112]
	add	x2, x1, 12
	str	x1, [x29, 136]
	str	x2, [x29, 96]
.L1072:
	ldr	x20, [x29, 112]
	mov	w1, 2
	str	w1, [x29, 148]
.L1079:
	mov	x26, 0
.L1078:
	sub	w0, w0, #1
	lsl	w11, w0, 6
	sub	w0, w11, w0
	ubfx	x0, x0, 6, 24
	add	w11, w0, 1
	tbnz	w5, #31, .L1155
.L1073:
	lsl	w1, w11, 24
	cmp	w1, w28
	bhi	.L1074
	ldr	w0, [x19, 44]
	sub	w3, w28, w1
	mov	w25, 0
	mov	w22, 6
	sub	w0, w0, w11
	ldrb	w28, [x24, w0, uxtw]
	lsl	w3, w3, w28
	sub	w21, w5, w28
	lsl	w28, w0, w28
	str	w28, [x19, 44]
	stp	w3, w21, [x19, 36]
	b	.L1077
	.p2align 3
.L1075:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w23
	bhi	.L1076
	ldr	w5, [x19, 44]
	lsl	w0, w27, w22
	sub	w23, w23, w1
	sub	w28, w5, w28
.L1076:
	orr	w25, w25, w0
	ldrb	w0, [x24, w28, uxtw]
	sub	w22, w22, #1
	lsl	w3, w23, w0
	sub	w21, w21, w0
	lsl	w28, w28, w0
	cmn	w22, #1
	stp	w3, w21, [x19, 36]
	str	w28, [x19, 44]
	beq	.L1156
.L1077:
	sub	w28, w28, #1
	mov	w23, w3
	ubfx	x28, x28, 1, 24
	add	w28, w28, 1
	tbz	w21, #31, .L1075
	mov	w0, 24
	sub	w1, w0, w21
	mov	w0, 16
	sub	w5, w0, w21
	and	w1, w1, -8
	sub	w5, w5, w1
	mov	x0, x19
	str	w5, [x29, 152]
	add	w21, w1, w21
	bl	BsGet
	ldr	w5, [x29, 152]
	and	w5, w5, 7
	lsl	w0, w0, w5
	orr	w23, w0, w23
	b	.L1075
	.p2align 3
.L1066:
	uxtw	x0, w20
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w28, w5, [x19, 36]
	b	.L1106
	.p2align 3
.L1156:
	add	x0, x20, x26
	lsl	w10, w25, 1
	orr	w10, w10, 1
	strb	w10, [x0, 47]
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
.L1107:
	add	x26, x26, 1
	cmp	x26, 3
	bne	.L1078
	ldr	w1, [x29, 148]
	add	x20, x20, 3
	subs	w1, w1, #1
	str	w1, [x29, 148]
	bne	.L1079
	sub	w0, w0, #1
	mov	x20, 0
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbnz	w5, #31, .L1157
.L1081:
	lsl	w3, w21, 24
	cmp	w3, w28
	bhi	.L1082
.L1159:
	ldr	w0, [x19, 44]
	sub	w28, w28, w3
	mov	w8, 0
	mov	w3, 6
	sub	w0, w0, w21
	ldrb	w21, [x24, w0, uxtw]
	lsl	w28, w28, w21
	sub	w4, w5, w21
	lsl	w21, w0, w21
	str	w21, [x19, 44]
	stp	w28, w4, [x19, 36]
	b	.L1085
	.p2align 3
.L1083:
	lsl	w1, w21, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1084
	ldr	w5, [x19, 44]
	lsl	w0, w27, w3
	sub	w28, w28, w1
	sub	w21, w5, w21
.L1084:
	orr	w8, w8, w0
	ldrb	w0, [x24, w21, uxtw]
	sub	w3, w3, #1
	lsl	w28, w28, w0
	sub	w4, w4, w0
	lsl	w21, w21, w0
	cmn	w3, #1
	stp	w28, w4, [x19, 36]
	str	w21, [x19, 44]
	beq	.L1158
.L1085:
	sub	w21, w21, #1
	ubfx	x21, x21, 1, 24
	add	w21, w21, 1
	tbz	w4, #31, .L1083
	mov	w0, 24
	str	w3, [x29, 120]
	sub	w1, w0, w4
	mov	w0, 16
	sub	w5, w0, w4
	and	w1, w1, -8
	sub	w5, w5, w1
	add	w4, w1, w4
	mov	x0, x19
	str	w8, [x29, 128]
	stp	w5, w4, [x29, 148]
	bl	BsGet
	ldp	w5, w4, [x29, 148]
	ldr	w3, [x29, 120]
	and	w5, w5, 7
	ldr	w8, [x29, 128]
	lsl	w0, w0, w5
	orr	w28, w0, w28
	b	.L1083
	.p2align 3
.L1074:
	uxtw	x0, w11
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w0, w11, w0
	str	w0, [x19, 44]
	stp	w28, w5, [x19, 36]
	b	.L1107
	.p2align 3
.L1158:
	ldr	x0, [x29, 136]
	lsl	w8, w8, 1
	orr	w8, w8, 1
	add	x0, x0, x20
	add	x20, x20, 1
	cmp	x20, 3
	strb	w8, [x0, 59]
	beq	.L1086
.L1160:
	ldr	w0, [x19, 44]
	ldp	w28, w5, [x19, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbz	w5, #31, .L1081
.L1157:
	mov	w0, 24
	str	w5, [x29, 128]
	sub	w4, w0, w5
	mov	w0, 16
	and	w4, w4, -8
	sub	w3, w0, w5
	sub	w3, w3, w4
	mov	w1, w4
	mov	x0, x19
	stp	w3, w4, [x29, 148]
	bl	BsGet
	ldp	w3, w4, [x29, 148]
	ldr	w5, [x29, 128]
	and	w3, w3, 7
	lsl	w0, w0, w3
	lsl	w3, w21, 24
	orr	w28, w0, w28
	add	w4, w4, w5
	cmp	w3, w28
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	bls	.L1159
	.p2align 2
.L1082:
	uxtw	x0, w21
	add	x20, x20, 1
	cmp	x20, 3
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w4, w5, w0
	lsl	w0, w21, w0
	str	w0, [x19, 44]
	stp	w28, w4, [x19, 36]
	bne	.L1160
.L1086:
	ldr	x1, [x29, 136]
	ldr	x0, [x29, 112]
	add	x1, x1, 3
	str	x1, [x29, 136]
	ldr	x1, [x29, 96]
	add	x0, x0, 6
	str	x0, [x29, 112]
	cmp	x0, x1
	beq	.L1087
	ldp	w28, w5, [x19, 36]
	ldr	w0, [x19, 44]
	b	.L1072
	.p2align 3
.L1153:
	sub	w7, w22, w5
	sub	w4, w21, w5
	and	w25, w7, -8
	mov	x0, x19
	sub	w4, w4, w25
	mov	w1, w25
	stp	w5, w4, [x29, 148]
	bl	BsGet
	ldp	w5, w4, [x29, 148]
	and	w4, w4, 7
	lsl	w0, w0, w4
	add	w4, w25, w5
	orr	w28, w0, w28
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	b	.L1065
	.p2align 3
.L1155:
	mov	w0, 24
	str	w11, [x29, 128]
	sub	w4, w0, w5
	mov	w0, 16
	and	w22, w4, -8
	sub	w3, w0, w5
	mov	w1, w22
	mov	x0, x19
	sub	w21, w3, w22
	str	w5, [x29, 152]
	bl	BsGet
	ldr	w5, [x29, 152]
	and	w3, w21, 7
	lsl	w0, w0, w3
	ldr	w11, [x29, 128]
	add	w4, w22, w5
	orr	w28, w0, w28
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	b	.L1073
	.p2align 3
.L1041:
	uxtw	x0, w23
	ldrb	w0, [x24, x0]
	lsl	w28, w28, w0
	sub	w5, w5, w0
	lsl	w0, w23, w0
	str	w0, [x19, 44]
	stp	w28, w5, [x19, 36]
	b	.L1102
	.p2align 3
.L1059:
	sub	w1, w22, w20
	mov	x0, x19
	and	w1, w1, -8
	sub	w28, w21, w20
	sub	w28, w28, w1
	add	w20, w1, w20
	stp	w4, w5, [x29, 148]
	bl	BsGet
	and	w28, w28, 7
	ldp	w4, w5, [x29, 148]
	lsl	w0, w0, w28
	orr	w1, w0, w4
	b	.L1064
.L1087:
	ldr	w0, [x29, 144]
	cbz	w0, .L1039
	ldr	x0, [x29, 104]
	mov	w22, 24
	mov	w21, 16
	mov	w26, 1
	add	x25, x0, 67
	add	x0, x0, 69
	str	x0, [x29, 152]
.L1100:
	ldr	w0, [x19, 44]
	ldp	w23, w27, [x19, 36]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w27, #31, .L1161
.L1090:
	lsl	w0, w20, 24
	cmp	w0, w23
	bhi	.L1091
	sub	w23, w23, w0
	ldr	w0, [x19, 44]
	mov	w4, 0
	mov	w28, 6
	sub	w0, w0, w20
	ldrb	w20, [x24, w0, uxtw]
	lsl	w23, w23, w20
	sub	w5, w27, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w23, w5, [x19, 36]
	b	.L1094
	.p2align 3
.L1092:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w23
	bhi	.L1093
	ldr	w3, [x19, 44]
	lsl	w0, w26, w28
	sub	w23, w23, w1
	sub	w20, w3, w20
.L1093:
	orr	w4, w4, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w28, w28, #1
	lsl	w23, w23, w0
	sub	w5, w5, w0
	lsl	w20, w20, w0
	cmn	w28, #1
	stp	w23, w5, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1162
.L1094:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w5, #31, .L1092
	sub	w1, w22, w5
	sub	w27, w21, w5
	and	w1, w1, -8
	mov	x0, x19
	add	w5, w1, w5
	sub	w27, w27, w1
	and	w27, w27, 7
	str	w4, [x29, 136]
	str	w5, [x29, 148]
	bl	BsGet
	lsl	w0, w0, w27
	ldr	w4, [x29, 136]
	orr	w23, w0, w23
	ldr	w5, [x29, 148]
	b	.L1092
.L1164:
	lsl	w0, w3, 1
	orr	w0, w0, 1
	strb	w0, [x25]
.L1110:
	ldr	x0, [x29, 152]
	add	x25, x25, 1
	cmp	x25, x0
	bne	.L1100
.L1039:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L1047:
	uxtw	x0, w6
	ldrb	w0, [x24, x0]
	lsl	w26, w28, w0
	sub	w20, w5, w0
	lsl	w0, w6, w0
	str	w0, [x19, 44]
	stp	w26, w20, [x19, 36]
	b	.L1103
.L1058:
	uxtw	x0, w6
	ldrb	w0, [x24, x0]
	lsl	w28, w26, w0
	sub	w5, w20, w0
	lsl	w0, w6, w0
	str	w0, [x19, 44]
	stp	w28, w5, [x19, 36]
	b	.L1105
.L1162:
	lsl	w0, w4, 1
	orr	w0, w0, 1
	strb	w0, [x25, -2]
	ldr	w0, [x19, 44]
	ldp	w23, w27, [x19, 36]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbnz	w27, #31, .L1163
.L1095:
	lsl	w0, w20, 24
	cmp	w0, w23
	bhi	.L1096
.L1165:
	sub	w23, w23, w0
	ldr	w0, [x19, 44]
	mov	w3, 0
	mov	w28, 6
	sub	w0, w0, w20
	ldrb	w20, [x24, w0, uxtw]
	lsl	w23, w23, w20
	sub	w27, w27, w20
	lsl	w20, w0, w20
	str	w20, [x19, 44]
	stp	w23, w27, [x19, 36]
	b	.L1099
	.p2align 3
.L1097:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w23
	bhi	.L1098
	ldr	w4, [x19, 44]
	lsl	w0, w26, w28
	sub	w23, w23, w1
	sub	w20, w4, w20
.L1098:
	orr	w3, w3, w0
	ldrb	w0, [x24, w20, uxtw]
	sub	w28, w28, #1
	lsl	w23, w23, w0
	sub	w27, w27, w0
	lsl	w20, w20, w0
	cmn	w28, #1
	stp	w23, w27, [x19, 36]
	str	w20, [x19, 44]
	beq	.L1164
.L1099:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbz	w27, #31, .L1097
	sub	w1, w22, w27
	sub	w4, w21, w27
	and	w1, w1, -8
	mov	x0, x19
	sub	w4, w4, w1
	str	w3, [x29, 136]
	str	w4, [x29, 148]
	add	w27, w1, w27
	bl	BsGet
	ldr	w4, [x29, 148]
	ldr	w3, [x29, 136]
	and	w4, w4, 7
	lsl	w0, w0, w4
	orr	w23, w0, w23
	b	.L1097
.L1091:
	uxtw	x0, w20
	ldrb	w0, [x24, x0]
	lsl	w23, w23, w0
	sub	w27, w27, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	stp	w23, w27, [x19, 36]
	ubfx	x0, x0, 6, 24
	add	w20, w0, 1
	tbz	w27, #31, .L1095
.L1163:
	sub	w3, w22, w27
	sub	w28, w21, w27
	and	w3, w3, -8
	mov	x0, x19
	mov	w1, w3
	sub	w28, w28, w3
	str	w3, [x29, 148]
	and	w28, w28, 7
	bl	BsGet
	lsl	w0, w0, w28
	ldr	w3, [x29, 148]
	orr	w23, w0, w23
	lsl	w0, w20, 24
	add	w27, w3, w27
	cmp	w0, w23
	stp	w23, w27, [x19, 36]
	bls	.L1165
.L1096:
	uxtw	x0, w20
	ldrb	w0, [x24, x0]
	lsl	w23, w23, w0
	sub	w1, w27, w0
	lsl	w0, w20, w0
	str	w0, [x19, 44]
	stp	w23, w1, [x19, 36]
	b	.L1110
.L1145:
	mov	w0, 24
	str	w5, [x29, 152]
	sub	w3, w0, w5
	mov	w0, 16
	and	w21, w3, -8
	sub	w25, w0, w5
	mov	w1, w21
	mov	x0, x19
	sub	w25, w25, w21
	bl	BsGet
	and	w25, w25, 7
	ldr	w5, [x29, 152]
	lsl	w0, w0, w25
	orr	w28, w0, w28
	add	w4, w21, w5
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	b	.L1040
.L1147:
	sub	w4, w22, w5
	mov	x0, x19
	and	w25, w4, -8
	sub	w20, w21, w5
	mov	w1, w25
	sub	w20, w20, w25
	stp	w6, w5, [x29, 148]
	bl	BsGet
	and	w20, w20, 7
	ldp	w6, w5, [x29, 148]
	lsl	w0, w0, w20
	add	w4, w25, w5
	orr	w28, w0, w28
	mov	w5, w4
	stp	w28, w4, [x19, 36]
	b	.L1046
.L1151:
	sub	w5, w22, w20
	mov	x0, x19
	and	w5, w5, -8
	sub	w28, w21, w20
	mov	w1, w5
	sub	w28, w28, w5
	stp	w6, w5, [x29, 148]
	bl	BsGet
	and	w28, w28, 7
	ldp	w6, w5, [x29, 148]
	lsl	w0, w0, w28
	orr	w4, w0, w26
	add	w5, w5, w20
	mov	w26, w4
	mov	w20, w5
	stp	w4, w5, [x19, 36]
	b	.L1057
.L1161:
	sub	w28, w22, w27
	sub	w3, w21, w27
	and	w28, w28, -8
	mov	x0, x19
	sub	w3, w3, w28
	mov	w1, w28
	str	w3, [x29, 148]
	add	w27, w27, w28
	bl	BsGet
	ldr	w3, [x29, 148]
	and	w3, w3, 7
	lsl	w0, w0, w3
	orr	w23, w0, w23
	stp	w23, w27, [x19, 36]
	b	.L1090
	.size	Vp9_ReadMvProbs, .-Vp9_ReadMvProbs
	.align	3
.LC18:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_PrepareReadModeInfo
	.type	Vp9_PrepareReadModeInfo, %function
Vp9_PrepareReadModeInfo:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 4096
	mov	x27, x1
	mov	w23, w2
	mov	w22, w3
	str	w6, [x29, 124]
	add	x24, x19, 304
	str	x7, [x29, 128]
	add	x26, x19, 307
	stp	w5, w4, [x29, 148]
	bl	_mcount
	ldr	x25, .LC19
	mov	w28, 24
	mov	w21, 1
	str	wzr, [x29, 172]
.L1198:
	ldp	w7, w0, [x27, 40]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w9, w0, 1
	tbnz	w7, #31, .L1167
	ldr	w0, [x27, 36]
.L1168:
	lsl	w1, w9, 24
	cmp	w1, w0
	bhi	.L1169
	sub	w1, w0, w1
	ldr	w0, [x27, 44]
	sub	w0, w0, w9
	ldrb	w2, [x25, w0, uxtw]
	lsl	w9, w1, w2
	sub	w7, w7, w2
	lsl	w2, w0, w2
	str	w2, [x27, 44]
	stp	w9, w7, [x27, 36]
	tbnz	w7, #31, .L1336
.L1170:
	sub	w0, w2, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w9
	bhi	.L1171
	ldr	w2, [x27, 44]
	sub	w1, w9, w1
	sub	w0, w2, w0
	ldrb	w2, [x25, w0, uxtw]
	lsl	w9, w1, w2
	sub	w7, w7, w2
	lsl	w2, w0, w2
	str	w2, [x27, 44]
	stp	w9, w7, [x27, 36]
	tbnz	w7, #31, .L1337
.L1173:
	sub	w0, w2, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w9
	bhi	.L1178
	ldr	w2, [x27, 44]
	sub	w1, w9, w1
	sub	w0, w2, w0
	ldrb	w10, [x25, w0, uxtw]
	lsl	w2, w1, w10
	sub	w7, w7, w10
	lsl	w10, w0, w10
	str	w10, [x27, 44]
	stp	w2, w7, [x27, 36]
	tbnz	w7, #31, .L1338
.L1180:
	sub	w0, w10, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w2
	bhi	.L1184
	sub	w2, w2, w1
	ldr	w1, [x27, 44]
	mov	w10, 0
	mov	w9, 6
	sub	w0, w1, w0
	ldrb	w11, [x25, w0, uxtw]
	lsl	w1, w2, w11
	sub	w7, w7, w11
	lsl	w0, w0, w11
	str	w0, [x27, 44]
	stp	w1, w7, [x27, 36]
	b	.L1185
.L1189:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w11
	bhi	.L1190
	ldr	w0, [x27, 44]
	sub	w11, w11, w1
	sub	w2, w0, w2
	lsl	w0, w21, w9
.L1190:
	orr	w10, w10, w0
	ldrb	w0, [x25, w2, uxtw]
	sub	w9, w9, #1
	lsl	w1, w11, w0
	sub	w7, w7, w0
	cmn	w9, #1
	lsl	w0, w2, w0
	stp	w1, w7, [x27, 36]
	str	w0, [x27, 44]
	beq	.L1339
.L1185:
	sub	w0, w0, #1
	mov	w11, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbz	w7, #31, .L1189
	sub	w1, w28, w7
	mov	w0, 16
	and	w1, w1, -8
	sub	w12, w0, w7
	sub	w12, w12, w1
	add	w7, w1, w7
	mov	x0, x27
	str	w10, [x29, 112]
	stp	w11, w2, [x29, 104]
	str	w9, [x29, 120]
	str	w12, [x29, 136]
	str	w7, [x29, 144]
	bl	BsGet
	ldr	w12, [x29, 136]
	ldp	w11, w2, [x29, 104]
	and	w12, w12, 7
	ldr	w10, [x29, 112]
	lsl	w0, w0, w12
	ldr	w9, [x29, 120]
	ldr	w7, [x29, 144]
	orr	w11, w0, w11
	b	.L1189
	.p2align 3
.L1169:
	uxtw	x1, w9
	ldrb	w1, [x25, x1]
	lsl	w0, w0, w1
	sub	w7, w7, w1
	stp	w0, w7, [x27, 36]
	lsl	w0, w9, w1
	str	w0, [x27, 44]
.L1275:
	add	x24, x24, 1
	cmp	x24, x26
	bne	.L1198
	cmp	w23, wzr
	ccmp	w22, wzr, 0, ne
	beq	.L1340
.L1199:
	ldr	x1, [x29, 128]
	ldr	w0, [x29, 172]
	str	w0, [x1]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1171:
	uxtw	x1, w0
	mov	w10, 0
	mov	w11, 3
	ldrb	w2, [x25, x1]
	lsl	w1, w9, w2
	lsl	w0, w0, w2
	sub	w9, w7, w2
	str	w0, [x27, 44]
	stp	w1, w9, [x27, 36]
.L1176:
	sub	w0, w0, #1
	mov	w7, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w9, #31, .L1341
.L1174:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w7
	bhi	.L1175
	ldr	w12, [x27, 44]
	lsl	w0, w21, w11
	sub	w7, w7, w1
	sub	w2, w12, w2
.L1175:
	orr	w10, w10, w0
	ldrb	w0, [x25, w2, uxtw]
	sub	w11, w11, #1
	lsl	w1, w7, w0
	sub	w9, w9, w0
	cmn	w11, #1
	lsl	w0, w2, w0
	stp	w1, w9, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1176
.L1177:
	ldrb	w0, [x24]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w7, w0, 1
	ldrb	w2, [x1, w10, sxtw]
	cmp	w7, 255
	bgt	.L1192
.L1367:
	add	w1, w2, 1
	cmp	w1, w7
	bgt	.L1193
	tbnz	x1, 0, .L1342
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1193:
	add	w1, w1, 1
.L1195:
	strb	w1, [x24]
	b	.L1275
	.p2align 3
.L1192:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w2, 1
	cmp	w1, w0, lsl 1
	bgt	.L1196
	tbnz	x1, 0, .L1343
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1196:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x24]
	b	.L1275
	.p2align 3
.L1167:
	sub	w10, w28, w7
	mov	w0, 16
	and	w10, w10, -8
	sub	w11, w0, w7
	ldr	w2, [x27, 36]
	sub	w11, w11, w10
	mov	w1, w10
	mov	x0, x27
	stp	w9, w11, [x29, 108]
	str	w7, [x29, 120]
	str	w10, [x29, 136]
	str	w2, [x29, 144]
	bl	BsGet
	ldp	w9, w11, [x29, 108]
	ldr	w7, [x29, 120]
	ldr	w10, [x29, 136]
	and	w11, w11, 7
	ldr	w2, [x29, 144]
	lsl	w0, w0, w11
	add	w7, w7, w10
	orr	w0, w0, w2
	stp	w0, w7, [x27, 36]
	b	.L1168
	.p2align 3
.L1340:
	mov	x0, x20
	add	x2, x19, 372
	mov	x1, x27
	str	x2, [x29, 112]
	bl	Vp9_ReadInterModeProbs
	ldr	w0, [x29, 152]
	cmp	w0, 4
	beq	.L1344
.L1200:
	add	x28, x19, 319
	add	x22, x19, 323
	mov	w23, 24
	mov	w24, 16
.L1204:
	ldp	w3, w0, [x27, 40]
	sub	w1, w0, #1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	ubfx	x0, x0, 6, 24
	add	w21, w0, 1
	tbnz	w3, #31, .L1201
	ldr	w2, [x27, 36]
.L1202:
	lsl	w0, w21, 24
	mov	x1, x28
	cmp	w0, w2
	sub	w6, w2, w0
	mov	x0, x27
	bhi	.L1203
	ldr	w2, [x27, 44]
	sub	w2, w2, w21
	ldrb	w5, [x25, w2, uxtw]
	lsl	w6, w6, w5
	sub	w3, w3, w5
	lsl	w2, w2, w5
	str	w2, [x27, 44]
	stp	w6, w3, [x27, 36]
	bl	Vp9_DiffUpdateProb
.L1276:
	add	x28, x28, 1
	cmp	x22, x28
	bne	.L1204
	ldr	w2, [x29, 148]
	mov	x0, x20
	mov	x1, x27
	add	x3, x29, 172
	add	x21, x19, 9
	mov	w24, 24
	bl	Vp9_ReadCompPred
	mov	w23, 1
	ldp	w26, w20, [x27, 36]
	ldr	w0, [x27, 44]
	add	x1, x19, 73
	str	x1, [x29, 136]
.L1205:
	sub	x22, x21, #9
	.p2align 2
.L1238:
	sub	w0, w0, #1
	lsl	w28, w0, 6
	sub	w0, w28, w0
	ubfx	x0, x0, 6, 24
	add	w28, w0, 1
	tbnz	w20, #31, .L1345
.L1206:
	lsl	w1, w28, 24
	cmp	w1, w26
	bhi	.L1207
	ldr	w0, [x27, 44]
	sub	w6, w26, w1
	sub	w0, w0, w28
	ldrb	w28, [x25, w0, uxtw]
	lsl	w6, w6, w28
	sub	w26, w20, w28
	lsl	w28, w0, w28
	str	w28, [x27, 44]
	stp	w6, w26, [x27, 36]
	tbnz	w26, #31, .L1346
.L1208:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w0, w28, 1
	lsl	w1, w0, 24
	cmp	w1, w6
	bhi	.L1209
	ldr	w28, [x27, 44]
	sub	w20, w6, w1
	sub	w28, w28, w0
	ldrb	w0, [x25, w28, uxtw]
	lsl	w20, w20, w0
	sub	w6, w26, w0
	lsl	w28, w28, w0
	str	w28, [x27, 44]
	stp	w20, w6, [x27, 36]
	tbnz	w6, #31, .L1347
.L1211:
	sub	w0, w28, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w20
	bhi	.L1216
	sub	w7, w20, w1
	ldr	w1, [x27, 44]
	sub	w0, w1, w0
	ldrb	w20, [x25, w0, uxtw]
	lsl	w26, w7, w20
	sub	w28, w6, w20
	lsl	w20, w0, w20
	str	w20, [x27, 44]
	stp	w26, w28, [x27, 36]
	tbnz	w28, #31, .L1348
.L1218:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L1222
	sub	w6, w26, w1
	ldr	w1, [x27, 44]
	mov	w9, 0
	mov	w7, 6
	sub	w0, w1, w0
	ldrb	w10, [x25, w0, uxtw]
	lsl	w1, w6, w10
	sub	w26, w28, w10
	lsl	w0, w0, w10
	str	w0, [x27, 44]
	stp	w1, w26, [x27, 36]
	b	.L1223
	.p2align 3
.L1227:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1228
	ldr	w0, [x27, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w23, w7
.L1228:
	orr	w9, w9, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w7, w7, #1
	lsl	w1, w28, w0
	sub	w26, w26, w0
	cmn	w7, #1
	lsl	w0, w20, w0
	stp	w1, w26, [x27, 36]
	str	w0, [x27, 44]
	beq	.L1349
.L1223:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbz	w26, #31, .L1227
	sub	w1, w24, w26
	mov	w0, 16
	and	w1, w1, -8
	sub	w10, w0, w26
	sub	w10, w10, w1
	mov	x0, x27
	stp	w7, w9, [x29, 144]
	str	w10, [x29, 152]
	add	w26, w1, w26
	bl	BsGet
	ldr	w10, [x29, 152]
	ldp	w7, w9, [x29, 144]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w28, w0, w28
	b	.L1227
	.p2align 3
.L1207:
	uxtw	x0, w28
	ldrb	w0, [x25, x0]
	lsl	w26, w26, w0
	sub	w20, w20, w0
	lsl	w0, w28, w0
	str	w0, [x27, 44]
	stp	w26, w20, [x27, 36]
.L1277:
	add	x22, x22, 1
	cmp	x21, x22
	bne	.L1238
	ldr	x1, [x29, 136]
	add	x21, x21, 16
	cmp	x1, x21
	bne	.L1205
	add	x1, x19, 612
	add	x21, x19, 564
	mov	w24, 16
	mov	w23, 1
	str	x1, [x29, 152]
	.p2align 2
.L1239:
	sub	w0, w0, #1
	mov	x19, x21
	lsl	w1, w0, 6
	mov	w28, 3
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w22, w0, 1
	tbnz	w20, #31, .L1350
.L1240:
	lsl	w1, w22, 24
	cmp	w1, w26
	bhi	.L1241
	ldr	w0, [x27, 44]
	sub	w6, w26, w1
	sub	w0, w0, w22
	ldrb	w22, [x25, w0, uxtw]
	lsl	w26, w6, w22
	sub	w20, w20, w22
	lsl	w22, w0, w22
	str	w22, [x27, 44]
	stp	w26, w20, [x27, 36]
	tbnz	w20, #31, .L1351
.L1242:
	sub	w22, w22, #1
	ubfx	x22, x22, 1, 24
	add	w0, w22, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L1243
	ldr	w22, [x27, 44]
	sub	w6, w26, w1
	sub	w22, w22, w0
	ldrb	w0, [x25, w22, uxtw]
	lsl	w26, w6, w0
	sub	w20, w20, w0
	lsl	w22, w22, w0
	str	w22, [x27, 44]
	stp	w26, w20, [x27, 36]
	tbnz	w20, #31, .L1352
.L1245:
	sub	w0, w22, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L1250
	sub	w6, w26, w1
	ldr	w1, [x27, 44]
	sub	w0, w1, w0
	ldrb	w1, [x25, w0, uxtw]
	sub	w22, w20, w1
	lsl	w26, w6, w1
	lsl	w20, w0, w1
	str	w20, [x27, 44]
	stp	w26, w22, [x27, 36]
	tbnz	w22, #31, .L1353
.L1252:
	sub	w0, w20, #1
	ubfx	x0, x0, 1, 24
	add	w0, w0, 1
	lsl	w1, w0, 24
	cmp	w1, w26
	bhi	.L1256
	sub	w6, w26, w1
	ldr	w1, [x27, 44]
	mov	w9, 0
	mov	w7, 6
	sub	w0, w1, w0
	ldrb	w10, [x25, w0, uxtw]
	lsl	w1, w6, w10
	sub	w26, w22, w10
	lsl	w0, w0, w10
	str	w0, [x27, 44]
	stp	w1, w26, [x27, 36]
	b	.L1257
	.p2align 3
.L1261:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L1262
	ldr	w0, [x27, 44]
	sub	w22, w22, w1
	sub	w20, w0, w20
	lsl	w0, w23, w7
.L1262:
	orr	w9, w9, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w7, w7, #1
	lsl	w1, w22, w0
	sub	w26, w26, w0
	cmn	w7, #1
	lsl	w0, w20, w0
	stp	w1, w26, [x27, 36]
	str	w0, [x27, 44]
	beq	.L1354
.L1257:
	sub	w0, w0, #1
	mov	w22, w1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbz	w26, #31, .L1261
	mov	w0, 24
	sub	w10, w24, w26
	sub	w1, w0, w26
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 136]
	sub	w10, w10, w1
	add	w26, w1, w26
	stp	w9, w10, [x29, 144]
	bl	BsGet
	ldp	w9, w10, [x29, 144]
	ldr	w7, [x29, 136]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w22, w0, w22
	b	.L1261
	.p2align 3
.L1241:
	uxtw	x0, w22
	ldrb	w0, [x25, x0]
	lsl	w6, w26, w0
	sub	w20, w20, w0
	lsl	w0, w22, w0
	str	w0, [x27, 44]
	stp	w6, w20, [x27, 36]
.L1278:
	subs	w28, w28, #1
	add	x19, x19, 1
	beq	.L1355
	ldr	w0, [x27, 44]
	ldp	w26, w20, [x27, 36]
	sub	w0, w0, #1
	lsl	w1, w0, 6
	sub	w0, w1, w0
	ubfx	x0, x0, 6, 24
	add	w22, w0, 1
	tbz	w20, #31, .L1240
.L1350:
	mov	w0, 24
	sub	w7, w24, w20
	sub	w9, w0, w20
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w9, w7, [x29, 144]
	bl	BsGet
	ldp	w9, w7, [x29, 144]
	and	w7, w7, 7
	add	w20, w9, w20
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w20, [x27, 36]
	b	.L1240
	.p2align 3
.L1355:
	ldr	x0, [x29, 152]
	add	x21, x21, 3
	cmp	x21, x0
	beq	.L1273
	ldp	w26, w20, [x27, 36]
	ldr	w0, [x27, 44]
	b	.L1239
	.p2align 3
.L1243:
	uxtw	x1, w0
	mov	w7, 0
	mov	w9, 3
	ldrb	w22, [x25, x1]
	lsl	w6, w26, w22
	sub	w20, w20, w22
	lsl	w22, w0, w22
	str	w22, [x27, 44]
	stp	w6, w20, [x27, 36]
.L1248:
	sub	w22, w22, #1
	mov	w26, w6
	ubfx	x22, x22, 1, 24
	add	w22, w22, 1
	tbnz	w20, #31, .L1356
.L1246:
	lsl	w1, w22, 24
	mov	w0, 0
	cmp	w1, w26
	bhi	.L1247
	ldr	w10, [x27, 44]
	lsl	w0, w23, w9
	sub	w26, w26, w1
	sub	w22, w10, w22
.L1247:
	orr	w7, w7, w0
	ldrb	w0, [x25, w22, uxtw]
	sub	w9, w9, #1
	lsl	w6, w26, w0
	sub	w20, w20, w0
	lsl	w22, w22, w0
	cmn	w9, #1
	stp	w6, w20, [x27, 36]
	str	w22, [x27, 44]
	bne	.L1248
.L1249:
	ldrb	w0, [x19]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w9, w0, 1
	ldrb	w6, [x1, w7, sxtw]
	cmp	w9, 255
	bgt	.L1266
	add	w1, w6, 1
	cmp	w1, w9
	bgt	.L1267
	tbnz	x1, 0, .L1357
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1267:
	add	w1, w1, 1
.L1269:
	strb	w1, [x19]
	b	.L1278
	.p2align 3
.L1209:
	uxtw	x1, w0
	mov	w7, 0
	mov	w9, 3
	ldrb	w28, [x25, x1]
	lsl	w20, w6, w28
	sub	w26, w26, w28
	lsl	w28, w0, w28
	str	w28, [x27, 44]
	stp	w20, w26, [x27, 36]
.L1214:
	sub	w28, w28, #1
	ubfx	x28, x28, 1, 24
	add	w28, w28, 1
	tbnz	w26, #31, .L1358
.L1212:
	lsl	w1, w28, 24
	mov	w0, 0
	cmp	w1, w20
	bhi	.L1213
	ldr	w10, [x27, 44]
	lsl	w0, w23, w9
	sub	w20, w20, w1
	sub	w28, w10, w28
.L1213:
	orr	w7, w7, w0
	ldrb	w0, [x25, w28, uxtw]
	sub	w9, w9, #1
	lsl	w20, w20, w0
	sub	w26, w26, w0
	lsl	w28, w28, w0
	cmn	w9, #1
	stp	w20, w26, [x27, 36]
	str	w28, [x27, 44]
	bne	.L1214
.L1215:
	ldrb	w0, [x22]
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w9, w0, 1
	ldrb	w6, [x1, w7, sxtw]
	cmp	w9, 255
	bgt	.L1232
	add	w1, w6, 1
	cmp	w1, w9
	bgt	.L1233
	tbnz	x1, 0, .L1359
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1233:
	add	w1, w1, 1
.L1235:
	strb	w1, [x22]
	ldp	w26, w20, [x27, 36]
	ldr	w0, [x27, 44]
	b	.L1277
	.p2align 3
.L1266:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w6, 1
	cmp	w1, w0, lsl 1
	bgt	.L1270
	tbnz	x1, 0, .L1360
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1270:
	mov	w0, 255
	sub	w1, w0, w1
	strb	w1, [x19]
	b	.L1278
	.p2align 3
.L1232:
	mov	w1, 254
	sub	w0, w1, w0
	add	w1, w6, 1
	cmp	w1, w0, lsl 1
	bgt	.L1236
	tbnz	x1, 0, .L1361
	add	w1, w1, w1, lsr 31
	add	w1, w0, w1, asr 1
.L1236:
	mov	w0, 255
	sub	w1, w0, w1
	b	.L1235
	.p2align 3
.L1356:
	mov	w0, 24
	sub	w10, w24, w20
	sub	w1, w0, w20
	mov	x0, x27
	and	w1, w1, -8
	str	w9, [x29, 136]
	sub	w10, w10, w1
	add	w20, w1, w20
	stp	w7, w10, [x29, 144]
	bl	BsGet
	ldp	w7, w10, [x29, 144]
	ldr	w9, [x29, 136]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w26, w0, w26
	b	.L1246
	.p2align 3
.L1345:
	sub	w9, w24, w20
	mov	w0, 16
	and	w9, w9, -8
	sub	w7, w0, w20
	sub	w7, w7, w9
	mov	w1, w9
	mov	x0, x27
	stp	w9, w7, [x29, 148]
	bl	BsGet
	ldp	w9, w7, [x29, 148]
	and	w7, w7, 7
	add	w20, w9, w20
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w20, [x27, 36]
	b	.L1206
	.p2align 3
.L1358:
	sub	w1, w24, w26
	mov	w0, 16
	sub	w10, w0, w26
	and	w1, w1, -8
	sub	w10, w10, w1
	mov	x0, x27
	stp	w9, w7, [x29, 144]
	str	w10, [x29, 152]
	add	w26, w1, w26
	bl	BsGet
	ldr	w10, [x29, 152]
	ldp	w9, w7, [x29, 144]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w20, w0, w20
	b	.L1212
	.p2align 3
.L1250:
	uxtw	x1, w0
	mov	w7, 0
	ldrb	w1, [x25, x1]
	lsl	w22, w26, w1
	sub	w6, w20, w1
	mov	w26, 3
	lsl	w20, w0, w1
	stp	w22, w6, [x27, 36]
	str	w20, [x27, 44]
.L1255:
	sub	w20, w20, #1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w6, #31, .L1362
.L1253:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L1254
	ldr	w10, [x27, 44]
	lsl	w0, w23, w26
	sub	w22, w22, w1
	sub	w20, w10, w20
.L1254:
	orr	w7, w7, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w26, w26, #1
	lsl	w22, w22, w0
	sub	w6, w6, w0
	lsl	w20, w20, w0
	cmn	w26, #1
	stp	w22, w6, [x27, 36]
	str	w20, [x27, 44]
	bne	.L1255
	add	w7, w7, 16
	b	.L1249
	.p2align 3
.L1216:
	uxtw	x1, w0
	mov	w26, 3
	ldrb	w7, [x25, x1]
	lsl	w1, w20, w7
	sub	w6, w6, w7
	lsl	w20, w0, w7
	mov	w7, 0
	stp	w1, w6, [x27, 36]
	str	w20, [x27, 44]
.L1221:
	sub	w20, w20, #1
	mov	w28, w1
	ubfx	x20, x20, 1, 24
	add	w20, w20, 1
	tbnz	w6, #31, .L1363
.L1219:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1220
	ldr	w10, [x27, 44]
	lsl	w0, w23, w26
	sub	w28, w28, w1
	sub	w20, w10, w20
.L1220:
	orr	w7, w7, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w6, w6, w0
	lsl	w20, w20, w0
	cmn	w26, #1
	stp	w1, w6, [x27, 36]
	str	w20, [x27, 44]
	bne	.L1221
	add	w7, w7, 16
	b	.L1215
	.p2align 3
.L1351:
	mov	w0, 24
	sub	w7, w24, w20
	sub	w9, w0, w20
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w7, w9, [x29, 144]
	bl	BsGet
	ldp	w7, w9, [x29, 144]
	and	w7, w7, 7
	add	w20, w9, w20
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w20, [x27, 36]
	b	.L1242
	.p2align 3
.L1357:
	add	w1, w6, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L1269
	.p2align 3
.L1203:
	uxtw	x0, w21
	ldrb	w1, [x25, x0]
	lsl	w2, w2, w1
	sub	w0, w3, w1
	lsl	w1, w21, w1
	str	w1, [x27, 44]
	stp	w2, w0, [x27, 36]
	b	.L1276
	.p2align 3
.L1362:
	mov	w0, 24
	sub	w10, w24, w6
	sub	w1, w0, w6
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 136]
	sub	w10, w10, w1
	add	w6, w1, w6
	stp	w10, w6, [x29, 144]
	bl	BsGet
	ldp	w10, w6, [x29, 144]
	ldr	w7, [x29, 136]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w22, w0, w22
	b	.L1253
	.p2align 3
.L1346:
	sub	w7, w24, w26
	mov	w0, 16
	and	w7, w7, -8
	sub	w20, w0, w26
	mov	w1, w7
	mov	x0, x27
	sub	w20, w20, w7
	stp	w6, w7, [x29, 148]
	bl	BsGet
	ldp	w6, w7, [x29, 148]
	and	w1, w20, 7
	lsl	w0, w0, w1
	add	w10, w7, w26
	orr	w20, w0, w6
	mov	w26, w10
	mov	w6, w20
	stp	w20, w10, [x27, 36]
	b	.L1208
	.p2align 3
.L1360:
	add	w6, w6, 2
	sub	w1, w0, w6, lsr 1
	b	.L1270
	.p2align 3
.L1359:
	add	w1, w6, 2
	sub	w1, w0, w1, lsr 1
	b	.L1233
	.p2align 3
.L1363:
	sub	w1, w24, w6
	mov	w0, 16
	and	w1, w1, -8
	sub	w10, w0, w6
	sub	w10, w10, w1
	add	w6, w1, w6
	mov	x0, x27
	str	w6, [x29, 152]
	stp	w7, w10, [x29, 144]
	bl	BsGet
	ldp	w7, w10, [x29, 144]
	ldr	w6, [x29, 152]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w28, w0, w28
	b	.L1219
	.p2align 3
.L1361:
	add	w6, w6, 2
	sub	w1, w0, w6, lsr 1
	b	.L1236
	.p2align 3
.L1273:
	ldr	w2, [x29, 124]
	mov	x0, x27
	ldr	x1, [x29, 112]
	bl	Vp9_ReadMvProbs
	b	.L1199
	.p2align 3
.L1341:
	sub	w1, w28, w9
	mov	w0, 16
	and	w1, w1, -8
	sub	w12, w0, w9
	sub	w12, w12, w1
	add	w9, w1, w9
	mov	x0, x27
	str	w10, [x29, 112]
	stp	w7, w2, [x29, 104]
	str	w11, [x29, 120]
	str	w12, [x29, 136]
	str	w9, [x29, 144]
	bl	BsGet
	ldr	w12, [x29, 136]
	ldp	w7, w2, [x29, 104]
	and	w12, w12, 7
	ldr	w10, [x29, 112]
	lsl	w0, w0, w12
	ldr	w11, [x29, 120]
	ldr	w9, [x29, 144]
	orr	w7, w0, w7
	b	.L1174
.L1256:
	uxtw	x1, w0
	ldrb	w7, [x25, x1]
	lsl	w1, w26, w7
	sub	w6, w22, w7
	lsl	w0, w0, w7
	mov	w26, 4
	mov	w7, 0
	str	w0, [x27, 44]
	stp	w1, w6, [x27, 36]
	.p2align 2
.L1260:
	sub	w0, w0, #1
	mov	w22, w1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbnz	w6, #31, .L1364
.L1258:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L1259
	ldr	w0, [x27, 44]
	sub	w22, w22, w1
	sub	w20, w0, w20
	lsl	w0, w23, w26
.L1259:
	orr	w7, w7, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w26, w26, #1
	lsl	w1, w22, w0
	sub	w6, w6, w0
	cmn	w26, #1
	lsl	w0, w20, w0
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1260
	add	w7, w7, 32
	b	.L1249
.L1222:
	uxtw	x1, w0
	mov	w7, 0
	ldrb	w9, [x25, x1]
	lsl	w1, w26, w9
	sub	w6, w28, w9
	lsl	w0, w0, w9
	mov	w26, 4
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	.p2align 2
.L1226:
	sub	w0, w0, #1
	mov	w28, w1
	ubfx	x0, x0, 1, 24
	add	w20, w0, 1
	tbnz	w6, #31, .L1365
.L1224:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1225
	ldr	w0, [x27, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	lsl	w0, w23, w26
.L1225:
	orr	w7, w7, w0
	ldrb	w0, [x25, w20, uxtw]
	sub	w26, w26, #1
	lsl	w1, w28, w0
	sub	w6, w6, w0
	cmn	w26, #1
	lsl	w0, w20, w0
	stp	w1, w6, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1226
	add	w7, w7, 32
	b	.L1215
	.p2align 3
.L1364:
	mov	w0, 24
	sub	w10, w24, w6
	sub	w1, w0, w6
	mov	x0, x27
	and	w1, w1, -8
	str	w7, [x29, 136]
	sub	w10, w10, w1
	add	w6, w1, w6
	stp	w10, w6, [x29, 144]
	bl	BsGet
	ldp	w10, w6, [x29, 144]
	ldr	w7, [x29, 136]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w22, w0, w22
	b	.L1258
	.p2align 3
.L1352:
	mov	w0, 24
	sub	w7, w24, w20
	sub	w9, w0, w20
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w7, w9, [x29, 144]
	bl	BsGet
	ldp	w7, w9, [x29, 144]
	and	w7, w7, 7
	add	w20, w9, w20
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w20, [x27, 36]
	b	.L1245
	.p2align 3
.L1201:
	sub	w2, w23, w3
	sub	w6, w24, w3
	and	w2, w2, -8
	mov	x0, x27
	sub	w6, w6, w2
	mov	w1, w2
	ldr	w26, [x27, 36]
	str	w3, [x29, 136]
	str	w6, [x29, 144]
	str	w2, [x29, 152]
	bl	BsGet
	ldr	w6, [x29, 144]
	ldr	w2, [x29, 152]
	ldr	w3, [x29, 136]
	and	w6, w6, 7
	lsl	w0, w0, w6
	add	w3, w3, w2
	orr	w2, w0, w26
	stp	w2, w3, [x27, 36]
	b	.L1202
.L1342:
	add	w1, w2, 2
	sub	w1, w0, w1, lsr 1
	add	w1, w1, 1
	b	.L1195
.L1178:
	uxtw	x1, w0
	mov	w10, 0
	mov	w11, 3
	ldrb	w2, [x25, x1]
	lsl	w1, w9, w2
	lsl	w0, w0, w2
	sub	w9, w7, w2
	str	w0, [x27, 44]
	stp	w1, w9, [x27, 36]
.L1183:
	sub	w0, w0, #1
	mov	w7, w1
	ubfx	x0, x0, 1, 24
	add	w2, w0, 1
	tbnz	w9, #31, .L1366
.L1181:
	lsl	w1, w2, 24
	mov	w0, 0
	cmp	w1, w7
	bhi	.L1182
	ldr	w0, [x27, 44]
	sub	w7, w7, w1
	sub	w2, w0, w2
	lsl	w0, w21, w11
.L1182:
	orr	w10, w10, w0
	ldrb	w0, [x25, w2, uxtw]
	sub	w11, w11, #1
	lsl	w1, w7, w0
	sub	w9, w9, w0
	cmn	w11, #1
	lsl	w0, w2, w0
	stp	w1, w9, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1183
	ldrb	w0, [x24]
	add	w10, w10, 16
	add	x1, x25, 256
	sub	w0, w0, #1
	lsl	w7, w0, 1
	cmp	w7, 255
	ldrb	w2, [x1, w10, sxtw]
	bgt	.L1192
	b	.L1367
.L1343:
	add	w2, w2, 2
	sub	w1, w0, w2, lsr 1
	b	.L1196
.L1184:
	uxtw	x1, w0
	mov	w10, 0
	ldrb	w9, [x25, x1]
	lsl	w1, w2, w9
	sub	w7, w7, w9
	lsl	w0, w0, w9
	mov	w2, 4
	stp	w1, w7, [x27, 36]
	str	w0, [x27, 44]
	.p2align 2
.L1188:
	sub	w0, w0, #1
	mov	w9, w1
	ubfx	x0, x0, 1, 24
	add	w11, w0, 1
	tbnz	w7, #31, .L1368
.L1186:
	lsl	w1, w11, 24
	mov	w0, 0
	cmp	w1, w9
	bhi	.L1187
	ldr	w0, [x27, 44]
	sub	w9, w9, w1
	sub	w11, w0, w11
	lsl	w0, w21, w2
.L1187:
	orr	w10, w10, w0
	ldrb	w0, [x25, w11, uxtw]
	sub	w2, w2, #1
	lsl	w1, w9, w0
	sub	w7, w7, w0
	cmn	w2, #1
	lsl	w0, w11, w0
	stp	w1, w7, [x27, 36]
	str	w0, [x27, 44]
	bne	.L1188
	add	w10, w10, 32
	b	.L1177
.L1365:
	sub	w1, w24, w6
	mov	w0, 16
	and	w1, w1, -8
	sub	w10, w0, w6
	sub	w10, w10, w1
	add	w6, w1, w6
	mov	x0, x27
	str	w6, [x29, 152]
	stp	w7, w10, [x29, 144]
	bl	BsGet
	ldp	w7, w10, [x29, 144]
	ldr	w6, [x29, 152]
	and	w10, w10, 7
	lsl	w0, w0, w10
	orr	w28, w0, w28
	b	.L1224
	.p2align 3
.L1347:
	sub	w9, w24, w6
	mov	w0, 16
	and	w9, w9, -8
	sub	w7, w0, w6
	mov	w1, w9
	mov	x0, x27
	sub	w26, w7, w9
	stp	w6, w9, [x29, 148]
	bl	BsGet
	and	w7, w26, 7
	ldp	w6, w9, [x29, 148]
	lsl	w0, w0, w7
	orr	w20, w0, w20
	add	w6, w9, w6
	stp	w20, w6, [x27, 36]
	b	.L1211
.L1354:
	cmp	w9, 64
	mov	w7, w9
	bgt	.L1369
	add	w7, w7, 64
	b	.L1249
.L1369:
	sub	w20, w0, #1
	lsl	w9, w9, 1
	ubfx	x20, x20, 1, 24
	sub	w7, w9, #65
	add	w20, w20, 1
	mov	w22, w1
	tbnz	w26, #31, .L1370
.L1264:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w22
	bhi	.L1265
	ldr	w0, [x27, 44]
	sub	w22, w22, w1
	sub	w20, w0, w20
	mov	w0, 1
.L1265:
	ldrb	w9, [x25, w20, uxtw]
	add	w7, w7, w0
	add	w7, w7, 64
	lsl	w1, w22, w9
	sub	w0, w26, w9
	lsl	w20, w20, w9
	str	w20, [x27, 44]
	stp	w1, w0, [x27, 36]
	b	.L1249
	.p2align 3
.L1336:
	sub	w11, w28, w7
	mov	w0, 16
	and	w11, w11, -8
	sub	w10, w0, w7
	sub	w10, w10, w11
	mov	w1, w11
	mov	x0, x27
	str	w2, [x29, 120]
	stp	w9, w7, [x29, 108]
	str	w10, [x29, 136]
	str	w11, [x29, 144]
	bl	BsGet
	ldr	w10, [x29, 136]
	ldp	w9, w7, [x29, 108]
	and	w10, w10, 7
	ldr	w11, [x29, 144]
	lsl	w0, w0, w10
	ldr	w2, [x29, 120]
	orr	w1, w0, w9
	add	w7, w11, w7
	mov	w9, w1
	stp	w1, w7, [x27, 36]
	b	.L1170
.L1349:
	cmp	w9, 64
	mov	w7, w9
	bgt	.L1371
	add	w7, w7, 64
	b	.L1215
.L1366:
	sub	w1, w28, w9
	mov	w0, 16
	and	w1, w1, -8
	sub	w12, w0, w9
	sub	w12, w12, w1
	add	w9, w1, w9
	mov	x0, x27
	str	w10, [x29, 112]
	stp	w7, w2, [x29, 104]
	str	w11, [x29, 120]
	str	w12, [x29, 136]
	str	w9, [x29, 144]
	bl	BsGet
	ldr	w12, [x29, 136]
	ldp	w7, w2, [x29, 104]
	and	w12, w12, 7
	ldr	w10, [x29, 112]
	lsl	w0, w0, w12
	ldr	w11, [x29, 120]
	ldr	w9, [x29, 144]
	orr	w7, w0, w7
	b	.L1181
.L1353:
	mov	w0, 24
	sub	w7, w24, w22
	sub	w9, w0, w22
	mov	x0, x27
	and	w9, w9, -8
	sub	w7, w7, w9
	mov	w1, w9
	stp	w7, w9, [x29, 144]
	bl	BsGet
	ldp	w7, w9, [x29, 144]
	and	w7, w7, 7
	add	w22, w9, w22
	lsl	w0, w0, w7
	orr	w6, w0, w26
	mov	w26, w6
	stp	w6, w22, [x27, 36]
	b	.L1252
.L1344:
	mov	x1, x27
	mov	x0, x20
	bl	Vp9_ReadSwitchableInterpProbs
	b	.L1200
.L1337:
	sub	w11, w28, w7
	mov	w0, 16
	and	w11, w11, -8
	sub	w10, w0, w7
	sub	w10, w10, w11
	mov	w1, w11
	mov	x0, x27
	str	w9, [x29, 120]
	stp	w2, w7, [x29, 108]
	str	w10, [x29, 136]
	str	w11, [x29, 144]
	bl	BsGet
	ldr	w10, [x29, 136]
	ldr	w9, [x29, 120]
	and	w10, w10, 7
	ldr	w11, [x29, 144]
	ldp	w2, w7, [x29, 108]
	lsl	w0, w0, w10
	orr	w1, w0, w9
	add	w7, w11, w7
	mov	w9, w1
	stp	w1, w7, [x27, 36]
	b	.L1173
.L1371:
	sub	w20, w0, #1
	lsl	w9, w9, 1
	ubfx	x20, x20, 1, 24
	sub	w7, w9, #65
	add	w20, w20, 1
	mov	w28, w1
	tbnz	w26, #31, .L1372
.L1230:
	lsl	w1, w20, 24
	mov	w0, 0
	cmp	w1, w28
	bhi	.L1231
	ldr	w0, [x27, 44]
	sub	w28, w28, w1
	sub	w20, w0, w20
	mov	w0, 1
.L1231:
	ldrb	w9, [x25, w20, uxtw]
	add	w7, w7, w0
	add	w7, w7, 64
	lsl	w1, w28, w9
	sub	w0, w26, w9
	lsl	w20, w20, w9
	str	w20, [x27, 44]
	stp	w1, w0, [x27, 36]
	b	.L1215
.L1370:
	mov	w0, 24
	sub	w9, w24, w26
	sub	w1, w0, w26
	mov	x0, x27
	and	w1, w1, -8
	sub	w9, w9, w1
	add	w26, w26, w1
	stp	w7, w9, [x29, 144]
	bl	BsGet
	ldp	w7, w9, [x29, 144]
	and	w9, w9, 7
	lsl	w0, w0, w9
	orr	w22, w0, w22
	b	.L1264
.L1348:
	sub	w6, w24, w28
	mov	w0, 16
	and	w6, w6, -8
	sub	w9, w0, w28
	sub	w9, w9, w6
	mov	w1, w6
	mov	x0, x27
	stp	w9, w6, [x29, 148]
	bl	BsGet
	ldp	w9, w6, [x29, 148]
	and	w9, w9, 7
	add	w6, w6, w28
	lsl	w0, w0, w9
	mov	w28, w6
	orr	w1, w0, w26
	mov	w26, w1
	stp	w1, w6, [x27, 36]
	b	.L1218
.L1368:
	sub	w1, w28, w7
	mov	w0, 16
	and	w1, w1, -8
	sub	w12, w0, w7
	sub	w12, w12, w1
	add	w7, w1, w7
	mov	x0, x27
	str	w10, [x29, 112]
	stp	w9, w11, [x29, 104]
	str	w2, [x29, 120]
	str	w12, [x29, 136]
	str	w7, [x29, 144]
	bl	BsGet
	ldr	w12, [x29, 136]
	ldp	w9, w11, [x29, 104]
	and	w12, w12, 7
	ldr	w10, [x29, 112]
	lsl	w0, w0, w12
	ldr	w2, [x29, 120]
	ldr	w7, [x29, 144]
	orr	w9, w0, w9
	b	.L1186
.L1339:
	cmp	w10, 64
	bgt	.L1373
	add	w10, w10, 64
	b	.L1177
.L1373:
	mov	w1, 128
	mov	x0, x27
	str	w10, [x29, 144]
	bl	Vp9_Cabac_Read
	ldr	w10, [x29, 144]
	add	w0, w0, w10, lsl 1
	sub	w10, w0, #65
	add	w10, w10, 64
	b	.L1177
.L1338:
	sub	w11, w28, w7
	mov	w0, 16
	and	w11, w11, -8
	sub	w9, w0, w7
	sub	w9, w9, w11
	mov	w1, w11
	mov	x0, x27
	str	w2, [x29, 120]
	stp	w10, w7, [x29, 108]
	str	w9, [x29, 136]
	str	w11, [x29, 144]
	bl	BsGet
	ldr	w9, [x29, 136]
	ldr	w2, [x29, 120]
	and	w9, w9, 7
	ldr	w11, [x29, 144]
	ldp	w10, w7, [x29, 108]
	lsl	w0, w0, w9
	orr	w1, w0, w2
	add	w7, w11, w7
	mov	w2, w1
	stp	w1, w7, [x27, 36]
	b	.L1180
.L1372:
	sub	w1, w24, w26
	mov	w0, 16
	and	w1, w1, -8
	sub	w9, w0, w26
	sub	w9, w9, w1
	mov	x0, x27
	stp	w7, w9, [x29, 148]
	add	w26, w26, w1
	bl	BsGet
	ldp	w7, w9, [x29, 148]
	and	w9, w9, 7
	lsl	w0, w0, w9
	orr	w28, w0, w28
	b	.L1230
	.size	Vp9_PrepareReadModeInfo, .-Vp9_PrepareReadModeInfo
	.align	3
.LC19:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_AdaptProbs
	.type	Vp9_AdaptProbs, %function
Vp9_AdaptProbs:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w20, w0
	mov	x22, x1
	mov	x0, x30
	mov	x21, x2
	mov	x23, x3
	mov	x24, x4
	bl	_mcount
	ldrsb	w0, [x22, w20, uxtw]
	cmp	w0, wzr
	ble	.L1383
	mov	x4, x24
	mov	x3, x23
	mov	x2, x21
	mov	x1, x22
	bl	Vp9_AdaptProbs
	mov	w19, w0
	add	w0, w20, 1
	ldrsb	w0, [x22, x0]
	cmp	w0, wzr
	ble	.L1384
.L1377:
	mov	x4, x24
	mov	x3, x23
	mov	x2, x21
	mov	x1, x22
	bl	Vp9_AdaptProbs
.L1378:
	ubfx	x20, x20, 1, 31
	adds	w0, w19, w0
	ldrb	w4, [x23, x20]
	beq	.L1379
	ldr	x6, .LC21
	cmp	w0, 20
	mov	w5, 20
	lsr	w1, w0, 1
	csel	w5, w0, w5, ls
	add	x6, x6, 512
	add	w19, w1, w19, lsl 8
	mov	w3, 256
	mov	w2, 255
	udiv	w1, w19, w0
	ldrb	w5, [x6, x5]
	cmp	w1, wzr
	sub	w3, w3, w5
	csinc	w1, w1, wzr, gt
	mul	w3, w3, w4
	cmp	w1, w2
	csel	w2, w1, w2, le
	add	w1, w3, 128
	and	w2, w2, 255
	madd	w1, w2, w5, w1
	ubfx	x4, x1, 8, 8
.L1379:
	strb	w4, [x21, x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1383:
	neg	w0, w0
	ldr	w19, [x24, w0, sxtw 2]
	add	w0, w20, 1
	ldrsb	w0, [x22, x0]
	cmp	w0, wzr
	bgt	.L1377
.L1384:
	neg	w0, w0
	ldr	w0, [x24, w0, sxtw 2]
	b	.L1378
	.size	Vp9_AdaptProbs, .-Vp9_AdaptProbs
	.align	3
.LC21:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Lf_Init_Lut
	.type	Lf_Init_Lut, %function
Lf_Init_Lut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	strb	wzr, [x19, 64]
	strb	wzr, [x19, 67]
	strb	wzr, [x19, 68]
	strb	wzr, [x19, 69]
	strb	wzr, [x19, 70]
	strb	wzr, [x19, 71]
	strb	wzr, [x19, 72]
	strb	wzr, [x19, 65]
	strb	wzr, [x19, 66]
	strb	wzr, [x19, 73]
	strb	wzr, [x19, 76]
	strb	w0, [x19, 74]
	strb	w0, [x19, 75]
	strb	w0, [x19, 77]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Lf_Init_Lut, .-Lf_Init_Lut
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Loop_Filter_Init
	.type	VP9_Loop_Filter_Init, %function
VP9_Loop_Filter_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	strb	wzr, [x19, 64]
	strb	wzr, [x19, 67]
	strb	wzr, [x19, 68]
	strb	wzr, [x19, 69]
	strb	wzr, [x19, 70]
	strb	wzr, [x19, 71]
	strb	wzr, [x19, 72]
	strb	wzr, [x19, 65]
	strb	wzr, [x19, 66]
	strb	wzr, [x19, 73]
	strb	wzr, [x19, 76]
	strb	w0, [x19, 74]
	strb	w0, [x19, 75]
	strb	w0, [x19, 77]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Loop_Filter_Init, .-VP9_Loop_Filter_Init
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_InitDecPara
	.type	VP9_InitDecPara, %function
VP9_InitDecPara:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 270336
	bl	_mcount
	ldr	x22, .LC23
	add	x20, x19, 2644
	mov	x2, 5488
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x22, 96]
	blr	x3
	add	x0, x21, 274432
	mov	w1, 3
	add	x0, x0, 4040
	str	w1, [x19, 7712]
	bl	ResetVoQueue
	str	wzr, [x19, 2876]
	ldr	x3, [x22, 96]
	mov	w0, 2
	mov	x2, 16
	str	w0, [x19, 2880]
	mov	w1, 0
	add	x0, x19, 2708
	blr	x3
	strb	wzr, [x19, 2964]
	mov	w1, 1
	strb	wzr, [x19, 2967]
	strb	wzr, [x19, 2968]
	strb	wzr, [x19, 2969]
	strb	wzr, [x19, 2970]
	strb	wzr, [x19, 2971]
	strb	wzr, [x19, 2972]
	strb	wzr, [x19, 2965]
	strb	wzr, [x19, 2966]
	strb	wzr, [x19, 2973]
	strb	wzr, [x19, 2976]
	strb	w1, [x19, 2974]
	strb	w1, [x19, 2975]
	strb	w1, [x19, 2977]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9_InitDecPara, .-VP9_InitDecPara
	.align	3
.LC23:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_Init
	.type	VP9DEC_Init, %function
VP9DEC_Init:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x23, x1
	bl	_mcount
	ldr	x1, .LC27
	mov	w0, 2
	bl	dprint_vfmw
	cmp	x20, xzr
	ccmp	x23, xzr, 4, ne
	beq	.L1402
	ldr	w0, [x23, 664]
	add	x19, x20, 278528
	cmp	w0, 1
	ldr	w22, [x19, 544]
	beq	.L1403
	mov	w24, 0
	mov	w25, 0
	add	x21, x20, 311296
.L1391:
	ldr	x26, .LC30
	mov	x2, 52440
	movk	x2, 0x4, lsl 16
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x26, 96]
	blr	x3
	str	w22, [x19, 544]
	add	x0, x20, 274432
	add	x0, x0, 4040
	bl	ResetVoQueue
	str	x23, [x20]
	mov	x0, x20
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x21, 3272]
	beq	.L1404
	ldr	x1, [x20]
	add	x19, x20, 270336
	add	x22, x19, 2576
	ldr	w0, [x1, 8]
	str	w0, [x19, 2576]
	mov	w0, 3
	stp	w0, wzr, [x22, 8]
	str	w0, [x22, 64]
	ldr	w0, [x1, 48]
	str	w0, [x22, 16]
	ldr	w1, [x1, 52]
	str	w1, [x22, 20]
	bl	MEM_Phy2Vir
	str	x0, [x22, 24]
	mov	w1, 2048
	str	w1, [x22, 32]
	str	wzr, [x21, 3140]
	str	wzr, [x21, 3144]
	str	wzr, [x21, 3168]
	str	wzr, [x21, 3172]
	str	wzr, [x21, 3208]
	str	wzr, [x21, 3212]
	ldr	w0, [x23, 664]
	cmp	w0, 1
	beq	.L1405
	str	wzr, [x21, 3128]
	str	wzr, [x22, 4]
.L1394:
	ldr	x3, [x26, 96]
	mov	w1, 0
	mov	x2, 32
	add	x0, x21, 3176
	blr	x3
	mov	x0, x20
	bl	VP9_InitDecPara
	add	x0, x19, 2724
	add	x1, x19, 2760
	.p2align 2
.L1395:
	str	wzr, [x0]
	add	x0, x0, 4
	str	wzr, [x0, 32]
	cmp	x0, x1
	bne	.L1395
	add	x0, x19, 2840
	add	x2, x19, 2876
	mov	w1, -1
	.p2align 2
.L1396:
	str	w1, [x0], 4
	cmp	x0, x2
	bne	.L1396
	add	x0, x19, 2796
	mov	w1, 0
	mov	w2, 1
	.p2align 2
.L1397:
	str	w1, [x0]
	add	w1, w1, 1
	str	w2, [x0, -72]
	cmp	w1, 8
	add	x0, x0, 4
	bne	.L1397
	mov	w0, 0
.L1390:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1403:
	add	x21, x20, 311296
	add	x0, x20, 270336
	ldr	w25, [x21, 3128]
	ldr	w24, [x0, 2580]
	b	.L1391
	.p2align 3
.L1405:
	str	w25, [x21, 3128]
	str	w24, [x22, 4]
	b	.L1394
.L1402:
	ldr	x1, .LC29
	mov	w2, 2013
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L1390
.L1404:
	ldr	x1, .LC32
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L1390
	.size	VP9DEC_Init, .-VP9DEC_Init
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC30:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC32:
	.xword	.LC31
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ParseSuperFrameIndex
	.type	Vp9_ParseSuperFrameIndex, %function
Vp9_ParseSuperFrameIndex:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w1
	mov	x20, x2
	mov	x19, x3
	bl	_mcount
	cmp	w21, wzr
	ble	.L1419
	sxtw	x0, w21
	add	x1, x22, x0
	ldrb	w1, [x1, -1]
	str	wzr, [x19]
	and	w2, w1, 224
	cmp	w2, 192
	beq	.L1420
.L1406:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1420:
	and	w7, w1, 7
	ubfx	x3, x1, 3, 2
	add	w7, w7, 1
	add	w2, w3, 1
	mul	w6, w7, w2
	add	w6, w6, 2
	cmp	w21, w6
	blt	.L1406
	sub	w21, w21, w6
	ldrb	w4, [x22, w21, sxtw]
	cmp	w4, w1
	bne	.L1406
	add	x0, x0, 1
	uxtb	x8, w3
	sub	x0, x0, x6, sxtw
	mov	x3, 0
	add	x6, x22, x0
	add	x8, x8, 1
	cbz	w7, .L1410
	.p2align 2
.L1415:
	mov	x0, 0
	mov	w4, 0
	cbz	w2, .L1421
	.p2align 2
.L1416:
	ldrb	w1, [x6, x0]
	lsl	w5, w0, 3
	add	x0, x0, 1
	cmp	w2, w0
	lsl	w1, w1, w5
	orr	w4, w4, w1
	bhi	.L1416
	add	x6, x6, x8
.L1414:
	str	w4, [x20, x3, lsl 2]
	add	x3, x3, 1
	cmp	w7, w3
	bhi	.L1415
.L1410:
	str	w7, [x19]
	b	.L1406
	.p2align 3
.L1419:
	ldr	x1, .LC34
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1406
.L1421:
	mov	w4, w2
	b	.L1414
	.size	Vp9_ParseSuperFrameIndex, .-Vp9_ParseSuperFrameIndex
	.align	3
.LC34:
	.xword	.LC33
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_GetImageBuffer
	.type	VP9_GetImageBuffer, %function
VP9_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 270336
	add	x21, x19, 311296
	add	x22, x20, 2576
	bl	_mcount
	ldr	w0, [x22, 5156]
	cmp	w0, 1
	beq	.L1441
	ldr	w0, [x21, 3272]
	mov	w1, 1
	bl	FSP_NewLogicFs
	mov	w1, w0
	str	w0, [x22, 52]
.L1424:
	tbnz	w1, #31, .L1442
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L1443
	add	x20, x20, 2576
	ldr	x1, .LC40
	ldr	w2, [x20, 52]
	mov	w0, 18
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L1428
	ldr	x1, [x19, 40]
	cbz	x1, .L1428
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC42
	bl	dprint_vfmw
	ldr	w0, [x20, 5156]
	cmp	w0, 1
	beq	.L1444
	ldr	x1, [x19, 32]
	mov	w0, 0
	str	wzr, [x1, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1428:
	ldr	x1, .LC44
	mov	w2, 2240
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1426:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1442:
	ldr	x1, .LC36
	mov	w0, 0
	bl	dprint_vfmw
	add	x1, x19, 274432
	ldr	w0, [x21, 3272]
	add	x1, x1, 4040
	bl	FSP_ClearNotInVoQueue
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1441:
	ldr	w0, [x21, 3272]
	mov	w1, 0
	bl	FSP_NewLogicFs
	mov	w1, w0
	str	w0, [x22, 52]
	b	.L1424
	.p2align 3
.L1443:
	ldr	x1, .LC38
	mov	w2, 2228
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1444:
	ldr	w3, [x20, 5160]
	cmp	w3, 8
	bls	.L1431
	ldr	x2, .LC45
	mov	w0, 0
	ldr	x1, .LC47
	add	x2, x2, 536
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1426
	.p2align 3
.L1431:
	add	x20, x20, x3, sxtw 2
	ldr	w0, [x21, 3272]
	ldr	w1, [x20, 264]
	bl	FSP_GetLogicFs
	mov	x3, x0
	cbz	x0, .L1445
	ldr	x4, [x3, 32]
	add	x1, x0, 48
	str	x4, [x19, 32]
	mov	x2, 640
	add	x0, x19, 48
	ldr	x3, [x3, 32]
	str	x3, [x19, 40]
	ldr	w3, [x4, 72]
	str	w3, [x19, 20]
	bl	memcpy
	strb	wzr, [x19, 2]
	ldrsb	w0, [x19, 3]
	str	w0, [x19, 196]
	mov	w0, 0
	b	.L1426
.L1445:
	ldr	x3, .LC49
	mov	w2, 2257
	ldr	x1, .LC51
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1426
	.size	VP9_GetImageBuffer, .-VP9_GetImageBuffer
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
.LC45:
	.xword	.LANCHOR0
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
	.global	VP9_FreeCurFb
	.type	VP9_FreeCurFb, %function
VP9_FreeCurFb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x1, x0
	mov	x0, x30
	add	x20, x1, 270336
	add	x19, x1, 311296
	bl	_mcount
	ldr	w1, [x20, 2628]
	tbnz	w1, #31, .L1447
	ldr	w0, [x19, 3272]
	mov	w2, 1
	bl	FSP_ClearLogicFs
.L1447:
	ldr	w0, [x19, 3164]
	cmp	w0, 8
	bhi	.L1446
	add	x0, x20, x0, sxtw 2
	str	wzr, [x0, 2724]
.L1446:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_FreeCurFb, .-VP9_FreeCurFb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_SetImgFormat
	.type	VP9_SetImgFormat, %function
VP9_SetImgFormat:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1450
	add	x21, x20, 270336
	add	x0, x20, 311296
	ldr	w1, [x21, 2628]
	ldr	w0, [x0, 3272]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1450
	ldr	x1, [x20]
	mov	x2, -1
	mov	w5, 5
	mov	w4, 1
	ldr	x1, [x1, 64]
	str	x1, [x0, 584]
	ldr	x1, [x20]
	str	x2, [x1, 64]
	ldr	w3, [x21, 2636]
	ldrb	w1, [x0, 64]
	ldrb	w2, [x0, 65]
	bfi	w1, w3, 0, 2
	and	w3, w3, 3
	orr	w2, w2, 12
	and	w1, w1, -29
	bfi	w1, w5, 5, 3
	bfi	w2, w4, 4, 2
	strb	w1, [x0, 64]
	mov	w1, 0
	strb	w2, [x0, 65]
	ldr	w2, [x0, 64]
	and	w2, w2, -114689
	str	w2, [x0, 64]
	lsr	w4, w2, 8
	lsr	w2, w2, 16
	and	w4, w4, -4
	strb	w4, [x0, 65]
	ldrb	w4, [x21, 2644]
	bfi	w2, w4, 1, 1
	strb	w2, [x0, 66]
	ldr	w2, [x21, 2648]
	str	w2, [x0, 120]
	stp	w3, w3, [x0, 56]
	bl	SetAspectRatio
	ldr	w5, [x21, 2664]
	str	w5, [x19, 68]
	ldr	w4, [x21, 2668]
	str	w4, [x19, 72]
	ldr	x0, [x20]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L1454
	ldr	w0, [x19, 36]
	ldr	x6, [x19, 504]
.L1455:
	ldr	w1, [x21, 2488]
	add	w2, w5, 255
	str	w1, [x19, 124]
	and	w2, w2, -256
	add	w1, w2, 3
	cmp	w2, wzr
	ldr	w3, [x21, 2496]
	csel	w2, w1, w2, lt
	str	w3, [x19, 128]
	asr	w2, w2, 2
	ubfiz	w7, w2, 4, 27
	ldr	w1, [x21, 2500]
	str	w1, [x19, 132]
	ldr	w1, [x21, 2112]
	str	w1, [x19, 112]
	ldr	w1, [x21, 2120]
	str	w1, [x19, 116]
	ldr	x1, [x20]
	ldr	w3, [x21, 2124]
	ldr	w1, [x1, 972]
	str	w1, [x19, 168]
	lsl	w1, w3, 2
	sub	w1, w1, w3
	add	x6, x6, x3, sxtw
	ldr	x8, [x20]
	add	w3, w3, w0
	add	w1, w1, w1, lsr 31
	add	w0, w0, w1, asr 1
	ldr	w1, [x8, 972]
	str	w1, [x19, 172]
	ldr	w1, [x21, 2516]
	str	w1, [x19, 136]
	add	w1, w4, 63
	and	w1, w1, -64
	ldr	w8, [x21, 2520]
	madd	w2, w1, w2, w0
	stp	w3, w0, [x19, 40]
	lsr	w1, w4, 1
	lsr	w3, w5, 1
	str	w2, [x19, 48]
	stp	w5, w4, [x19, 76]
	str	w1, [x19, 88]
	stp	w8, w7, [x19, 140]
	str	x6, [x19, 512]
	str	w3, [x19, 84]
.L1450:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1454:
	ldr	w2, [x19, 112]
	add	w1, w4, 15
	lsr	w1, w1, 4
	ldr	w0, [x19, 36]
	lsl	w3, w2, 4
	ldr	x6, [x19, 504]
	mul	w1, w1, w3
	add	w3, w1, w0
	str	w3, [x19, 40]
	add	x1, x6, x1, sxtw
	str	x1, [x19, 512]
	stp	w0, w3, [x19, 20]
	add	w1, w2, w0
	add	w2, w2, w3
	stp	w1, w2, [x19, 28]
	b	.L1455
	.size	VP9_SetImgFormat, .-VP9_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_VDMPostProc
	.type	VP9DEC_VDMPostProc, %function
VP9DEC_VDMPostProc:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	mov	w24, w2
	mov	w23, w3
	bl	_mcount
	cbz	x21, .L1513
	add	x28, x21, 270336
	ldr	w1, [x28, 7784]
	ldrb	w2, [x28, 2097]
	str	w1, [x29, 108]
	ldr	w1, [x28, 2484]
	strb	w2, [x28, 2644]
	str	w1, [x28, 2648]
	ldr	w26, [x28, 7792]
	cbnz	w24, .L1514
	add	x20, x21, 311296
	ldr	w0, [x20, 3172]
	cbz	w0, .L1465
.L1523:
	ldr	w0, [x20, 3208]
	ldr	w1, [x20, 3212]
	cmp	w1, w0
	beq	.L1465
.L1466:
	ldr	w0, [x20, 3272]
	add	x19, x28, 2760
	ldr	w1, [x28, 2628]
	add	x27, x28, 2796
	bl	FSP_GetFsImagePtr
	mov	x25, x0
	cbnz	x0, .L1501
	b	.L1515
	.p2align 3
.L1468:
	cmp	w2, wzr
	ccmp	w0, wzr, 0, ne
	beq	.L1516
.L1469:
	add	x19, x19, 4
	cmp	x19, x27
	beq	.L1517
.L1501:
	ldr	w2, [x19]
	ldr	w0, [x19, -36]
	cmp	w2, wzr
	ldr	w1, [x19, 80]
	ccmp	w0, wzr, 4, eq
	beq	.L1468
	ldr	w0, [x20, 3272]
	mov	w2, 1
	add	x19, x19, 4
	bl	FSP_SetRef
	cmp	x19, x27
	bne	.L1501
.L1517:
	ldr	x0, .LC57
	mov	x2, 36
	add	x1, x28, 2724
	ldr	x3, [x0, 104]
	add	x0, x28, 2760
	blr	x3
	tbnz	w22, #31, .L1471
	cmp	w22, 100
	mov	w2, 100
	csel	w2, w22, w2, le
	str	w2, [x25, 152]
	ldr	x0, [x21]
	ldr	w3, [x0]
	cmp	w2, w3
	bhi	.L1518
	mov	x0, x21
	bl	VP9_SetImgFormat
	ldr	w0, [x28, 2576]
	cmp	w0, 2
	beq	.L1519
.L1473:
	ldr	w0, [x28, 7728]
	cbnz	w0, .L1475
.L1474:
	mov	w0, -1
	str	w0, [x28, 2632]
	ldr	w1, [x28, 2628]
	mov	w2, 0
	ldr	w0, [x20, 3272]
	bl	FSP_SetDisplay
	ldr	w1, [x28, 2632]
.L1476:
	cmn	w1, #1
	beq	.L1477
	ldr	w0, [x20, 3272]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1520
	ldr	w1, [x28, 2632]
	mov	w2, 1
	ldr	w0, [x20, 3272]
	add	x28, x28, 2576
	bl	FSP_SetDisplay
	add	x3, x21, 274432
	ldr	w0, [x20, 3272]
	mov	x4, x19
	add	x3, x3, 4040
	mov	x2, x21
	mov	w1, 17
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w19, w0
	bne	.L1521
.L1477:
	cbz	w24, .L1479
	ldr	x0, .LC54
	sbfiz	x23, x23, 6, 32
	add	x23, x0, x23
	ldr	w0, [x23, 44]
	cmp	w0, 2
	beq	.L1464
.L1479:
	add	x0, x21, 274432
	ldr	w19, [x0, 3636]
	cbz	w19, .L1522
.L1464:
	mov	w19, 0
.L1510:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1516:
	ldr	w0, [x20, 3272]
	mov	w2, 0
	bl	FSP_SetRef
	b	.L1469
	.p2align 3
.L1514:
	ldr	x1, .LC54
	sbfiz	x0, x23, 6, 32
	add	x0, x1, x0
	ldr	w0, [x0, 44]
	cmp	w0, 3
	beq	.L1479
	add	x20, x21, 311296
	ldr	w0, [x20, 3172]
	cbnz	w0, .L1523
.L1465:
	mov	x1, x21
	mov	w0, 17
	bl	ReleasePacket
	str	wzr, [x20, 3172]
	b	.L1466
	.p2align 3
.L1475:
	ldr	w1, [x28, 2628]
	str	w1, [x28, 2632]
	b	.L1476
	.p2align 3
.L1522:
	add	x23, x21, 16
	add	x0, x23, 270336
	ldr	w0, [x0, 2356]
	bl	MEM_Phy2Vir
	mov	x22, x0
	cbz	x0, .L1524
	add	x20, x21, 311296
	ldr	w0, [x20, 3236]
	cbz	w0, .L1525
.L1485:
	mov	w26, 0
.L1481:
	ldr	x0, [x20, 3256]
	cbz	x0, .L1526
.L1482:
	ldr	w0, [x29, 108]
	cbz	w0, .L1464
	mov	x0, 4708
	uxtw	x26, w26
	mov	x2, x0
	add	x1, x21, 278528
	madd	x0, x26, x0, x21
	add	x1, x1, 592
	add	x0, x0, 282624
	add	x0, x0, 1204
	bl	memcpy
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1471:
	mov	x0, x21
	str	wzr, [x25, 152]
	bl	VP9_SetImgFormat
	ldr	w0, [x28, 2576]
	cmp	w0, 2
	bne	.L1473
.L1519:
	ldr	w0, [x28, 2636]
	cbnz	w0, .L1474
	b	.L1473
	.p2align 3
.L1521:
	ldr	w0, [x20, 3272]
	mov	w2, 0
	ldr	w1, [x28, 56]
	bl	FSP_SetDisplay
	ldr	x1, .LC63
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1525:
	ldr	w0, [x20, 3256]
	cbnz	w0, .L1485
	ldr	w0, [x20, 3240]
	cmp	w0, wzr
	csel	w26, w26, wzr, eq
	b	.L1481
	.p2align 3
.L1526:
	ldr	x24, .LC57
	add	x23, x23, 270336
	mov	x0, x22
	mov	w2, 5120
	ldr	w1, [x23, 2356]
	add	x23, x21, 282624
	ldr	x3, [x24, 280]
	add	x25, x23, 848
	blr	x3
	ldr	x3, [x24, 104]
	add	x0, x21, 278528
	mov	x1, x22
	mov	x2, 4096
	add	x0, x0, 592
	add	x22, x22, 4096
	blr	x3
	ldr	x3, [x24, 104]
	mov	x2, 256
	mov	x1, x22
	add	x0, x23, 592
	blr	x3
	ldr	x3, [x24, 104]
	add	x1, x22, 256
	mov	x2, 256
	mov	x0, x25
	blr	x3
	ldr	w0, [x20, 3240]
	cbz	w0, .L1483
	ldr	x3, [x24, 104]
	mov	x2, 48
	mov	x1, x25
	add	x0, x23, 1108
	blr	x3
	b	.L1482
.L1483:
	ldr	w3, [x20, 3248]
	mov	x2, 48
	ldr	x4, [x24, 104]
	mov	x1, x25
	lsl	x0, x3, 2
	sub	x0, x0, x3
	add	x0, x21, x0, lsl 4
	add	x0, x0, 282624
	add	x0, x0, 1108
	blr	x4
	b	.L1482
.L1518:
	ldr	x1, .LC59
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
	ldr	w0, [x20, 3272]
	mov	w2, 0
	ldr	w1, [x28, 2628]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 3272]
	mov	w2, 0
	ldr	w1, [x28, 2628]
	bl	FSP_SetRef
	b	.L1510
.L1513:
	ldr	x1, .LC53
	mov	w2, 2504
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L1510
.L1520:
	ldr	x1, .LC61
	mov	w2, 2597
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L1510
.L1515:
	ldr	x1, .LC56
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L1510
.L1524:
	ldr	x1, .LC65
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L1510
	.size	VP9DEC_VDMPostProc, .-VP9DEC_VDMPostProc
	.align	3
.LC53:
	.xword	.LC52
	.align	3
.LC54:
	.xword	g_VdmDrvParam
	.align	3
.LC56:
	.xword	.LC55
	.align	3
.LC57:
	.xword	vfmw_Osal_Func_Ptr_S
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_RecycleImage
	.type	VP9DEC_RecycleImage, %function
VP9DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L1530
	add	x19, x19, 311296
	mov	w2, 0
	mov	w1, w20
	ldr	w0, [x19, 3272]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 3272]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	w0, 0
.L1529:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1530:
	ldr	x1, .LC66
	mov	w2, 2698
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1529
	.size	VP9DEC_RecycleImage, .-VP9DEC_RecycleImage
	.align	3
.LC66:
	.xword	.LC52
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_GetRemainImg
	.type	VP9DEC_GetRemainImg, %function
VP9DEC_GetRemainImg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1534
	add	x0, x19, 274432
	add	x0, x0, 4040
	bl	GetVoLastImageID
.L1533:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1534:
	ldr	x1, .LC68
	mov	w2, 2717
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1533
	.size	VP9DEC_GetRemainImg, .-VP9DEC_GetRemainImg
	.align	3
.LC68:
	.xword	.LC67
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_GetImageBuffer
	.type	VP9DEC_GetImageBuffer, %function
VP9DEC_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1542
	add	x21, x20, 311296
	ldr	w0, [x21, 3272]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w19, w0
	beq	.L1537
	ldr	w0, [x21, 3272]
	mov	w19, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L1543
.L1537:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1543:
	add	x1, x20, 274432
	ldr	w0, [x21, 3272]
	add	x1, x1, 4040
	bl	FSP_ClearNotInVoQueue
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1542:
	ldr	x1, .LC69
	mov	w2, 2729
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9DEC_GetImageBuffer, .-VP9DEC_GetImageBuffer
	.align	3
.LC69:
	.xword	.LC67
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Check_Sync_Code
	.type	Check_Sync_Code, %function
Check_Sync_Code:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w0, 73
	beq	.L1545
.L1547:
	ldr	x1, .LC71
	mov	w0, 1
	bl	dprint_vfmw
.L1544:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1545:
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w0, 131
	bne	.L1547
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w0, 66
	bne	.L1547
	b	.L1544
	.size	Check_Sync_Code, .-Check_Sync_Code
	.align	3
.LC71:
	.xword	.LC70
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Read_Frame_Size
	.type	Read_Frame_Size, %function
Read_Frame_Size:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	x21, x1
	bl	_mcount
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	add	w0, w0, 1
	mov	w1, 16
	str	w0, [x21]
	mov	x0, x19
	bl	BsGet
	add	w0, w0, 1
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Read_Frame_Size, .-Read_Frame_Size
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	get_free_fb
	.type	get_free_fb, %function
get_free_fb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 80]
	cbz	w0, .L1553
	add	x2, x19, 84
	mov	w0, 1
	.p2align 2
.L1551:
	ldr	w3, [x2]
	add	x2, x2, 4
	cbz	w3, .L1550
	add	w0, w0, 1
	cmp	w0, 9
	bne	.L1551
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1553:
	mov	w0, 0
.L1550:
	add	x19, x19, x0, sxtw 2
	mov	w1, 1
	str	w1, [x19, 80]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	get_free_fb, .-get_free_fb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Display_Size
	.type	Setup_Display_Size, %function
Setup_Display_Size:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldp	w1, w0, [x19, 52]
	stp	w1, w0, [x19, 60]
	mov	w1, 1
	mov	x0, x20
	stp	wzr, wzr, [x29, 40]
	bl	BsGet
	cbz	w0, .L1559
	add	x2, x29, 44
	add	x1, x29, 40
	mov	x0, x20
	bl	Read_Frame_Size
.L1559:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Setup_Display_Size, .-Setup_Display_Size
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Update_CP_Size
	.type	VP9_Update_CP_Size, %function
VP9_Update_CP_Size:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 5060]
	ldr	w5, [x19, 5112]
	ldr	w4, [x19, 5116]
	add	x0, x19, x0, sxtw 4
	add	w3, w5, 7
	add	w2, w4, 7
	and	w3, w3, -8
	and	w2, w2, -8
	asr	w7, w3, 3
	asr	w6, w2, 3
	str	w7, [x19, 5152]
	str	w6, [x19, 5156]
	str	w3, [x0, 5296]
	str	w2, [x0, 5300]
	str	w5, [x0, 5304]
	str	w4, [x0, 5308]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Update_CP_Size, .-VP9_Update_CP_Size
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Frame_Size
	.type	Setup_Frame_Size, %function
Setup_Frame_Size:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x2, x20, 4096
	mov	x0, x21
	add	x19, x2, 964
	add	x1, x2, 1016
	add	x2, x2, 1020
	ldp	w4, w3, [x19, 52]
	stp	w4, w3, [x19, 72]
	bl	Read_Frame_Size
	ldr	w2, [x20, 5060]
	mov	x1, x19
	ldp	w6, w5, [x19, 52]
	mov	x0, x21
	add	x2, x20, x2, sxtw 4
	add	w4, w6, 7
	add	w3, w5, 7
	and	w4, w4, -8
	and	w3, w3, -8
	asr	w8, w4, 3
	asr	w7, w3, 3
	stp	w8, w7, [x19, 92]
	str	w4, [x2, 5296]
	str	w3, [x2, 5300]
	str	w6, [x2, 5304]
	str	w5, [x2, 5308]
	bl	Setup_Display_Size
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Setup_Frame_Size, .-Setup_Frame_Size
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	setup_frame_size_with_refs
	.type	setup_frame_size_with_refs, %function
setup_frame_size_with_refs:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x20, x1, 4096
	mov	x23, x1
	add	x22, x20, 964
	mov	w19, 0
	bl	_mcount
.L1569:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	cbnz	w0, .L1575
	add	w19, w19, 1
	cmp	w19, 3
	bne	.L1569
	ldr	w4, [x20, 1016]
	add	x2, x20, 1020
	ldr	w3, [x20, 1020]
	add	x1, x20, 1016
	str	w4, [x20, 1036]
	mov	x0, x21
	str	w3, [x20, 1040]
	bl	Read_Frame_Size
	ldr	w5, [x20, 1016]
	ldr	w4, [x20, 1020]
.L1568:
	ldr	w0, [x23, 5060]
	add	w3, w5, 7
	add	w2, w4, 7
	and	w3, w3, -8
	and	w2, w2, -8
	asr	w6, w3, 3
	add	x0, x23, x0, sxtw 4
	str	w6, [x20, 1056]
	asr	w1, w2, 3
	str	w1, [x20, 1060]
	mov	x1, x22
	str	w3, [x0, 5296]
	str	w2, [x0, 5300]
	str	w5, [x0, 5304]
	str	w4, [x0, 5308]
	mov	x0, x21
	bl	Setup_Display_Size
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1575:
	add	x19, x23, x19, sxtw 2
	ldr	w3, [x20, 1016]
	ldr	w2, [x20, 1020]
	ldr	w1, [x19, 184]
	str	w3, [x20, 1036]
	str	w2, [x20, 1040]
	add	x1, x23, x1, sxtw 4
	ldr	w5, [x1, 5304]
	str	w5, [x20, 1016]
	ldr	w4, [x1, 5308]
	str	w4, [x20, 1020]
	b	.L1568
	.size	setup_frame_size_with_refs, .-setup_frame_size_with_refs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Set_Default_Lf_Deltas
	.type	Set_Default_Lf_Deltas, %function
Set_Default_Lf_Deltas:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	mov	w1, -1
	strb	w0, [x19]
	strb	w0, [x19, 1]
	strb	w0, [x19, 2]
	strb	wzr, [x19, 3]
	strb	w1, [x19, 4]
	strb	w1, [x19, 5]
	strb	wzr, [x19, 6]
	strb	wzr, [x19, 7]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Set_Default_Lf_Deltas, .-Set_Default_Lf_Deltas
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Clearall_Segfeatures
	.type	VP9_Clearall_Segfeatures, %function
VP9_Clearall_Segfeatures:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC72
	mov	x2, 64
	mov	w1, 0
	add	x0, x19, 16
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 80
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Clearall_Segfeatures, .-VP9_Clearall_Segfeatures
	.align	3
.LC72:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Setup_Past_Independence
	.type	VP9_Setup_Past_Independence, %function
VP9_Setup_Past_Independence:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC73
	add	x0, x19, 4096
	mov	x2, 32
	add	x21, x0, 1088
	mov	w1, 0
	ldr	x3, [x20, 96]
	add	x0, x0, 1168
	blr	x3
	strb	wzr, [x21, 3]
	mov	w1, 1
	mov	w2, -1
	ldr	x3, [x20, 96]
	add	x0, x19, 64
	strb	w1, [x19, 336]
	strb	w1, [x19, 337]
	strb	w1, [x19, 338]
	mov	w1, 0
	strb	w2, [x19, 340]
	strb	w2, [x19, 341]
	mov	x2, 16
	strb	wzr, [x19, 339]
	strb	wzr, [x19, 342]
	strb	wzr, [x19, 343]
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9_Setup_Past_Independence, .-VP9_Setup_Past_Independence
	.align	3
.LC73:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_LoopFilter
	.type	Setup_LoopFilter, %function
Setup_LoopFilter:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 8]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	wzr, [x19, 1]
	str	w0, [x19, 12]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19]
	cbnz	w0, .L1604
.L1579:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1604:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 1]
	cbz	w0, .L1579
	add	x21, x19, 2
	add	x22, x19, 6
.L1585:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L1605
.L1582:
	add	x21, x21, 1
	cmp	x21, x22
	bne	.L1585
	mov	w1, 1
	mov	x0, x20
	add	x19, x19, 8
	bl	BsGet
	cbnz	w0, .L1606
.L1586:
	add	x22, x22, 1
	cmp	x22, x19
	beq	.L1579
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbz	w0, .L1586
.L1606:
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	asr	w1, w0, 1
	tbz	x0, 0, .L1588
	neg	w1, w1
.L1588:
	strb	w1, [x22]
	b	.L1586
	.p2align 3
.L1605:
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	asr	w1, w0, 1
	tbz	x0, 0, .L1584
	neg	w1, w1
.L1584:
	strb	w1, [x21]
	b	.L1582
	.size	Setup_LoopFilter, .-Setup_LoopFilter
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Read_Delta_Q
	.type	Read_Delta_Q, %function
Read_Delta_Q:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w1, 1
	mov	x0, x20
	ldr	w21, [x19]
	bl	BsGet
	cbnz	w0, .L1614
.L1608:
	str	w0, [x19]
	cmp	w0, w21
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1614:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	mov	w1, w0
	asr	w0, w0, 1
	tbz	x1, 0, .L1608
	neg	w0, w0
	str	w0, [x19]
	cmp	w0, w21
	cset	w0, ne
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Read_Delta_Q, .-Read_Delta_Q
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Quantization
	.type	Setup_Quantization, %function
Setup_Quantization:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 240]
	add	x1, x19, 244
	mov	x0, x20
	bl	Read_Delta_Q
	add	x1, x19, 248
	mov	x0, x20
	bl	Read_Delta_Q
	add	x1, x19, 252
	mov	x0, x20
	bl	Read_Delta_Q
	ldr	w0, [x19, 240]
	cbnz	w0, .L1617
	ldr	w1, [x19, 244]
	cbnz	w1, .L1616
	ldr	w1, [x19, 248]
	cbnz	w1, .L1616
	ldr	w0, [x19, 252]
	cmp	w0, wzr
	cset	w0, eq
.L1616:
	str	w0, [x19, 52]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1617:
	mov	w0, 0
	str	w0, [x19, 52]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Setup_Quantization, .-Setup_Quantization
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Enable_Segfeature
	.type	VP9_Enable_Segfeature, %function
VP9_Enable_Segfeature:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w1
	mov	w20, w2
	bl	_mcount
	add	x1, x21, x19, sxtw 2
	mov	w3, 1
	lsl	w2, w3, w20
	ldr	w0, [x1, 80]
	orr	w2, w0, w2
	str	w2, [x1, 80]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9_Enable_Segfeature, .-VP9_Enable_Segfeature
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Seg_Feature_Data_Max
	.type	VP9_Seg_Feature_Data_Max, %function
VP9_Seg_Feature_Data_Max:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC74
	add	x0, x0, 560
	ldr	w0, [x0, w19, uxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Seg_Feature_Data_Max, .-VP9_Seg_Feature_Data_Max
	.align	3
.LC74:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_Unsigned_Bits
	.type	Get_Unsigned_Bits, %function
Get_Unsigned_Bits:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 1
	mov	w0, 0
	bls	.L1622
	subs	w1, w19, #1
	beq	.L1622
	.p2align 2
.L1623:
	lsr	w1, w1, 1
	add	w0, w0, 1
	cbnz	w1, .L1623
.L1622:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_Unsigned_Bits, .-Get_Unsigned_Bits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Decode_Unsigned_Max
	.type	Decode_Unsigned_Max, %function
Decode_Unsigned_Max:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 1
	mov	w1, 0
	bls	.L1628
	subs	w0, w19, #1
	beq	.L1628
	.p2align 2
.L1629:
	lsr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1629
.L1628:
	mov	x0, x20
	bl	BsGet
	cmp	w19, w0
	csel	w0, w19, w0, le
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Decode_Unsigned_Max, .-Decode_Unsigned_Max
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Is_Segfeature_Signed
	.type	VP9_Is_Segfeature_Signed, %function
VP9_Is_Segfeature_Signed:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC76
	add	x0, x0, 576
	ldr	w0, [x0, w19, uxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_Is_Segfeature_Signed, .-VP9_Is_Segfeature_Signed
	.align	3
.LC76:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Set_Segdata
	.type	VP9_Set_Segdata, %function
VP9_Set_Segdata:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x24, x0
	mov	x0, x30
	mov	w19, w2
	mov	w20, w3
	mov	w21, w1
	bl	_mcount
	ldr	x22, .LC78
	add	x0, x22, 560
	ldr	w23, [x0, w19, uxtw 2]
	cmp	w23, w20
	blt	.L1640
	tbnz	w20, #31, .L1641
.L1637:
	sbfiz	x21, x21, 2, 32
	add	x19, x21, x19, uxtw
	add	x19, x19, 8
	strh	w20, [x24, x19, lsl 1]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1640:
	ldr	x1, .LC80
	mov	w3, 2998
	add	x2, x22, 592
	mov	w0, 0
	bl	dprint_vfmw
	tbz	w20, #31, .L1637
.L1641:
	add	x0, x22, 576
	ldr	w0, [x0, w19, uxtw 2]
	cbz	w0, .L1642
.L1638:
	neg	w0, w20
	cmp	w23, w0
	bge	.L1637
	ldr	x1, .LC80
	mov	w3, 3010
	add	x2, x22, 592
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1637
	.p2align 3
.L1642:
	ldr	x1, .LC80
	mov	w3, 3005
	add	x2, x22, 592
	bl	dprint_vfmw
	b	.L1638
	.size	VP9_Set_Segdata, .-VP9_Set_Segdata
	.align	3
.LC78:
	.xword	.LANCHOR0
	.align	3
.LC80:
	.xword	.LC79
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Mi_Cols_Aligned_To_Sb
	.type	Mi_Cols_Aligned_To_Sb, %function
Mi_Cols_Aligned_To_Sb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	add	w0, w19, 7
	ldr	x19, [sp, 16]
	and	w0, w0, -8
	ldp	x29, x30, [sp], 32
	ret
	.size	Mi_Cols_Aligned_To_Sb, .-Mi_Cols_Aligned_To_Sb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	To_Sbs
	.type	To_Sbs, %function
To_Sbs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	add	w0, w19, 7
	ldr	x19, [sp, 16]
	asr	w0, w0, 3
	ldp	x29, x30, [sp], 32
	ret
	.size	To_Sbs, .-To_Sbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Get_Tile_N_Bits
	.type	VP9_Get_Tile_N_Bits, %function
VP9_Get_Tile_N_Bits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	add	w3, w19, 7
	mov	w4, 0
	asr	w3, w3, 3
	cmp	w3, 3
	bgt	.L1647
	b	.L1646
	.p2align 3
.L1651:
	mov	w4, w0
.L1647:
	add	w0, w4, 1
	asr	w5, w3, w0
	cmp	w5, 3
	bgt	.L1651
	cmp	w4, wzr
	csel	w4, w4, wzr, ge
.L1646:
	cmp	w3, 64
	mov	w0, 0
	ble	.L1648
	mov	w6, 64
	.p2align 2
.L1649:
	add	w0, w0, 1
	lsl	w5, w6, w0
	cmp	w5, w3
	blt	.L1649
.L1648:
	str	w0, [x21]
	str	w4, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP9_Get_Tile_N_Bits, .-VP9_Get_Tile_N_Bits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Tile_Info
	.type	Setup_Tile_Info, %function
Setup_Tile_Info:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x21, 92]
	add	w1, w1, 7
	asr	w1, w1, 3
	cmp	w1, 3
	ble	.L1655
	mov	w19, 0
	b	.L1656
	.p2align 3
.L1667:
	mov	w19, w0
.L1656:
	add	w0, w19, 1
	asr	w2, w1, w0
	cmp	w2, 3
	bgt	.L1667
	cmp	w19, wzr
	csel	w19, w19, wzr, ge
	cmp	w1, 64
	ble	.L1668
.L1665:
	mov	w0, 0
	mov	w3, 64
	.p2align 2
.L1658:
	add	w0, w0, 1
	lsl	w2, w3, w0
	cmp	w1, w2
	bgt	.L1658
.L1657:
	subs	w19, w19, w0
	str	w0, [x21, 100]
	bne	.L1677
	b	.L1660
	.p2align 3
.L1663:
	ldr	w0, [x21, 100]
	subs	w19, w19, #1
	add	w0, w0, 1
	str	w0, [x21, 100]
	beq	.L1660
.L1677:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cbnz	w0, .L1663
.L1660:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x21, 104]
	cbz	w0, .L1654
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	ldr	w1, [x21, 104]
	add	w0, w1, w0
	str	w0, [x21, 104]
.L1654:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1655:
	cmp	w1, 64
	mov	w19, 0
	bgt	.L1665
	str	wzr, [x21, 100]
	b	.L1660
	.p2align 3
.L1668:
	mov	w0, 0
	b	.L1657
	.size	Setup_Tile_Info, .-Setup_Tile_Info
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Setup_Segmentation
	.type	Setup_Segmentation, %function
Setup_Segmentation:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x23, x1
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	strb	wzr, [x23, 1]
	strb	wzr, [x23, 2]
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23]
	cbnz	w0, .L1716
.L1680:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1716:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 1]
	cbz	w0, .L1683
	add	x19, x23, 5
	add	x20, x23, 12
	b	.L1685
	.p2align 3
.L1684:
	strb	w1, [x19], 1
	cmp	x19, x20
	beq	.L1717
.L1685:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	mov	w1, 255
	cbz	w0, .L1684
	mov	w1, 8
	mov	x0, x21
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19], 1
	cmp	x19, x20
	bne	.L1685
.L1717:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 4]
	cbnz	w0, .L1686
	mov	w0, -1
	strb	w0, [x23, 12]
	strb	w0, [x23, 13]
	strb	w0, [x23, 14]
.L1683:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x23, 2]
	cbz	w0, .L1680
	mov	w1, 1
	mov	x0, x21
	add	x19, x23, 80
	mov	w24, 0
	bl	BsGet
	ldr	x20, .LC83
	strb	w0, [x23, 3]
	mov	x2, 64
	mov	w1, 0
	add	x0, x23, 16
	ldr	x3, [x20, 96]
	mov	x25, x19
	mov	w27, 1
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	blr	x3
	ldr	x26, .LC84
	.p2align 2
.L1690:
	mov	x19, 0
.L1693:
	mov	w1, 1
	mov	x0, x21
	mov	w22, w19
	mov	w20, 0
	bl	BsGet
	cbnz	w0, .L1718
.L1692:
	mov	w3, w20
	mov	w2, w22
	mov	w1, w24
	mov	x0, x23
	add	x19, x19, 1
	bl	VP9_Set_Segdata
	cmp	x19, 4
	bne	.L1693
	add	w24, w24, 1
	add	x25, x25, 4
	cmp	w24, 8
	bne	.L1690
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1718:
	ldr	w3, [x25]
	add	x2, x26, 560
	lsl	w1, w27, w19
	mov	x0, x21
	orr	w1, w3, w1
	str	w1, [x25]
	ldr	w1, [x2, x19, lsl 2]
	bl	Decode_Unsigned_Max
	mov	w20, w0
	add	x0, x26, 576
	ldr	w0, [x0, x19, lsl 2]
	cbz	w0, .L1692
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	cmp	w0, wzr
	csneg	w20, w20, w20, eq
	b	.L1692
	.p2align 3
.L1686:
	add	x19, x23, 15
.L1688:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	mov	w1, 255
	cbnz	w0, .L1719
.L1687:
	strb	w1, [x20], 1
	cmp	x20, x19
	bne	.L1688
	b	.L1683
	.p2align 3
.L1719:
	mov	w1, 8
	mov	x0, x21
	bl	BsGet
	uxtb	w1, w0
	b	.L1687
	.size	Setup_Segmentation, .-Setup_Segmentation
	.align	3
.LC83:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC84:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	read_interp_filter_type
	.type	read_interp_filter_type, %function
read_interp_filter_type:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 2
	bl	_mcount
	mov	w2, 1
	mov	w3, 3
	mov	w1, w2
	mov	x0, x19
	stp	w2, wzr, [x29, 32]
	stp	w20, w3, [x29, 40]
	bl	BsGet
	cbz	w0, .L1723
	ldp	x19, x20, [sp, 16]
	mov	w0, 4
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1723:
	mov	w1, w20
	mov	x0, x19
	bl	BsGet
	add	x1, x29, 48
	add	x0, x1, x0, uxtw 2
	ldp	x19, x20, [sp, 16]
	ldr	w0, [x0, -16]
	ldp	x29, x30, [sp], 48
	ret
	.size	read_interp_filter_type, .-read_interp_filter_type
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	setup_inter_inter
	.type	setup_inter_inter, %function
setup_inter_inter:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w0, w2, [x19, 68]
	ldr	w1, [x19, 76]
	cmp	w2, w0
	ccmp	w1, w0, 0, eq
	cset	w0, ne
	str	w0, [x19, 60]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	setup_inter_inter, .-setup_inter_inter
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ref_cnt_fb
	.type	ref_cnt_fb, %function
ref_cnt_fb:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x1
	mov	x19, x0
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	ldr	w1, [x21]
	ldr	w0, [x19, w1, sxtw 2]
	cmp	w0, wzr
	ble	.L1726
	sub	w0, w0, #1
	str	w0, [x19, w1, sxtw 2]
.L1726:
	str	w20, [x21]
	ldr	w0, [x19, w20, sxtw 2]
	add	w0, w0, 1
	str	w0, [x19, w20, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	ref_cnt_fb, .-ref_cnt_fb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_get_fixed_point_scale_factor
	.type	VP9_get_fixed_point_scale_factor, %function
VP9_get_fixed_point_scale_factor:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	w20, w1
	mov	x0, x30
	bl	_mcount
	cbz	w20, .L1730
	lsl	w0, w19, 14
	sdiv	w0, w0, w20
.L1729:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1730:
	ldr	x2, .LC87
	mov	w4, 0
	ldr	x1, .LC89
	mov	w3, 3203
	add	x2, x2, 608
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1729
	.size	VP9_get_fixed_point_scale_factor, .-VP9_get_fixed_point_scale_factor
	.align	3
.LC87:
	.xword	.LANCHOR0
	.align	3
.LC89:
	.xword	.LC88
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	check_scale_factors
	.type	check_scale_factors, %function
check_scale_factors:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w2
	mov	w22, w1
	mov	w21, w3
	bl	_mcount
	cmp	w20, w19, lsl 1
	mov	w0, 0
	bgt	.L1732
	cmp	w22, w21, lsl 1
	mov	w0, 0
	bgt	.L1732
	cmp	w19, w20, lsl 4
	bgt	.L1732
	cmp	w21, w22, lsl 4
	cset	w0, le
.L1732:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	check_scale_factors, .-check_scale_factors
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_scaled_val
	.type	VP9_scaled_val, %function
VP9_scaled_val:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	smull	x0, w19, w20
	ldp	x19, x20, [sp, 16]
	lsr	x0, x0, 14
	ldp	x29, x30, [sp], 32
	ret
	.size	VP9_scaled_val, .-VP9_scaled_val
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	vp9_setup_scale_factors
	.type	vp9_setup_scale_factors, %function
vp9_setup_scale_factors:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w22, w3
	mov	w20, w1
	mov	w21, w2
	mov	w23, w4
	bl	_mcount
	cmp	w20, w22, lsl 1
	bgt	.L1738
	cmp	w21, w23, lsl 1
	ble	.L1748
.L1738:
	mov	w1, -1
	mov	w0, 16
	stp	w1, w1, [x19]
	stp	w0, w0, [x19, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1748:
	cmp	w22, w20, lsl 4
	bgt	.L1738
	cmp	w23, w21, lsl 4
	bgt	.L1738
	cbz	w22, .L1749
	lsl	w20, w20, 14
	sdiv	w3, w20, w22
	str	w3, [x19]
	cbz	w23, .L1750
.L1741:
	lsl	w21, w21, 14
	sdiv	w21, w21, w23
	sbfx	x0, x21, 10, 22
.L1742:
	str	w0, [x19, 12]
	sbfx	x3, x3, 10, 22
	stp	w21, w3, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1749:
	ldr	x2, .LC90
	mov	w3, 3203
	ldr	x1, .LC91
	mov	w4, 0
	add	x2, x2, 608
	mov	w0, 1
	bl	dprint_vfmw
	mov	w3, -1
	str	w3, [x19]
	cbnz	w23, .L1741
.L1750:
	ldr	x2, .LC90
	mov	w3, 3203
	ldr	x1, .LC91
	mov	w4, 0
	add	x2, x2, 608
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldr	w3, [x19]
	mov	w21, w0
	b	.L1742
	.size	vp9_setup_scale_factors, .-vp9_setup_scale_factors
	.align	3
.LC90:
	.xword	.LANCHOR0
	.align	3
.LC91:
	.xword	.LC88
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_ReadProfile
	.type	Vp9_Vfmw_ReadProfile, %function
Vp9_Vfmw_ReadProfile:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	mov	w19, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	orr	w19, w19, w0, lsl 1
	cmp	w19, 2
	ble	.L1752
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	add	w19, w0, w19
.L1752:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_Vfmw_ReadProfile, .-Vp9_Vfmw_ReadProfile
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadBitDepthColorSpaceSampling
	.type	Vp9_ReadBitDepthColorSpaceSampling, %function
Vp9_ReadBitDepthColorSpaceSampling:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	add	x19, x1, 4096
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 976]
	mov	w1, 8
	str	w1, [x19, 1032]
	cmp	w0, 1
	bls	.L1754
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	mov	w1, 12
	mov	w2, 10
	csel	w1, w1, w2, ne
	str	w1, [x19, 1032]
.L1754:
	add	x19, x19, 964
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	cmp	w0, 7
	str	w0, [x19, 16]
	beq	.L1756
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	ldr	w21, [x19, 12]
	str	w0, [x19, 20]
	and	w21, w21, -3
	cmp	w21, 1
	beq	.L1761
	mov	w0, 1
	stp	w0, w0, [x19, 44]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1756:
	ldr	w1, [x19, 12]
	and	w1, w1, -3
	cmp	w1, 1
	beq	.L1762
	ldr	x2, .LC92
	mov	w3, 3306
	ldr	x1, .LC94
	mov	w0, 1
	add	x2, x2, 648
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1761:
	mov	w1, w21
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 44]
	mov	w1, w21
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 48]
	mov	w1, w21
	mov	x0, x20
	bl	BsGet
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1762:
	mov	x0, x20
	stp	wzr, wzr, [x19, 44]
	bl	BsGet
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_ReadBitDepthColorSpaceSampling, .-Vp9_ReadBitDepthColorSpaceSampling
	.align	3
.LC92:
	.xword	.LANCHOR0
	.align	3
.LC94:
	.xword	.LC93
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ReadCompressedHeader
	.type	Vp9_ReadCompressedHeader, %function
Vp9_ReadCompressedHeader:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	w22, w2
	mov	w23, w3
	mov	w24, w4
	mov	w26, w5
	mov	w25, w6
	mov	w27, w7
	bl	_mcount
	str	wzr, [x29, 108]
	mov	w20, 0
	cbz	w27, .L1768
.L1764:
	mov	x2, x19
	mov	w1, w20
	mov	x0, x21
	bl	Vp9_ReadCoefProbs
	mov	x1, x19
	mov	x0, x21
	add	x7, x29, 108
	mov	w6, w26
	mov	w5, w25
	mov	w4, w24
	mov	w3, w23
	mov	w2, w22
	bl	Vp9_PrepareReadModeInfo
	ldr	w0, [x19, 40]
	mov	w1, 65502
	movk	w1, 0x3fff, lsl 16
	sub	w0, w0, #33
	cmp	w0, w1
	bls	.L1767
	ldr	x2, [x29, 112]
	mov	w0, 0
	ldr	w1, [x29, 108]
	str	w1, [x2]
	ldr	x1, [x29, 120]
	str	w20, [x1]
.L1765:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1768:
	mov	x0, x19
	bl	Vp9_ReadTxMode
	cmp	w0, 4
	mov	w20, w0
	bne	.L1764
	add	x0, x21, 4096
	mov	x1, x19
	add	x0, x0, 307
	bl	Vp9_ReadTxProbs
	b	.L1764
	.p2align 3
.L1767:
	mov	w0, -1
	b	.L1765
	.size	Vp9_ReadCompressedHeader, .-Vp9_ReadCompressedHeader
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Read_UnCompressed_Header
	.type	Read_UnCompressed_Header, %function
Read_UnCompressed_Header:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	add	x22, x1, 4096
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w3, [x22, 972]
	mov	w1, 2
	mov	x0, x19
	str	w3, [x22, 968]
	bl	BsGet
	cmp	w0, 2
	beq	.L1770
	ldr	x1, .LC96
	mov	w0, 1
	bl	dprint_vfmw
.L1770:
	mov	x0, x19
	add	x21, x22, 964
	bl	Vp9_Vfmw_ReadProfile
	mov	w1, 1
	str	w0, [x21, 12]
	mov	x0, x19
	bl	BsGet
	mov	w23, w0
	cbnz	w0, .L1800
	mov	w1, 1
	mov	x0, x19
	str	wzr, [x21, 28]
	bl	BsGet
	str	w0, [x21, 8]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 24]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, w0
	ldr	w0, [x21, 8]
	str	w1, [x21, 40]
	cbz	w0, .L1801
	ldr	w0, [x21, 24]
	cbz	w0, .L1775
	str	wzr, [x21, 108]
.L1776:
	cbz	w1, .L1777
	str	wzr, [x22, 1076]
.L1778:
	add	x26, x22, 964
	ldr	w0, [x26, 108]
	cbz	w0, .L1779
	mov	x0, x19
	bl	Check_Sync_Code
	ldr	w0, [x26, 12]
	cmp	w0, 1
	bls	.L1780
	mov	x1, x20
	mov	x0, x19
	bl	Vp9_ReadBitDepthColorSpaceSampling
.L1781:
	mov	w1, 8
	mov	x0, x19
	add	x21, x22, 964
	bl	BsGet
	str	w0, [x22, 1080]
	mov	x1, x20
	mov	x0, x19
	bl	Setup_Frame_Size
	ldr	w0, [x21, 40]
	cbnz	w0, .L1787
.L1803:
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 80]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 84]
	mov	w1, 2
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 1052]
	ldr	w2, [x22, 972]
	cbnz	w2, .L1802
	.p2align 2
.L1789:
	mov	x0, x20
	bl	VP9_Setup_Past_Independence
	ldr	w0, [x22, 972]
	cbz	w0, .L1790
	b	.L1791
	.p2align 3
.L1800:
	mov	w1, 3
	mov	x0, x19
	mov	w23, 0
	bl	BsGet
	add	x0, x20, x0, uxtw 2
	mov	w1, 1
	ldr	w0, [x0, 152]
	stp	w1, w0, [x21, 28]
	str	wzr, [x21, 116]
	str	wzr, [x20, 344]
	str	w1, [x21, 24]
.L1772:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1779:
	mov	w1, 8
	mov	x0, x19
	add	x24, x20, 184
	add	x25, x20, 196
	bl	BsGet
	mov	x21, x24
	str	w0, [x26, 116]
.L1782:
	mov	w1, 3
	mov	x0, x19
	add	x21, x21, 4
	bl	BsGet
	add	x2, x20, x0, sxtw 2
	mov	w1, 1
	mov	x0, x19
	ldr	w2, [x2, 152]
	str	w2, [x21, -4]
	bl	BsGet
	str	w0, [x21, -120]
	cmp	x25, x21
	bne	.L1782
	mov	x0, x19
	mov	x1, x20
	bl	setup_frame_size_with_refs
	ldr	w4, [x20, 5112]
	ldr	w5, [x20, 5116]
	sub	w0, w4, #1
	cmp	w0, 4095
	bhi	.L1784
	sub	w0, w5, #1
	cmp	w0, 4095
	bhi	.L1784
	mov	w1, 1
	mov	x0, x19
	add	x21, x22, 1344
	bl	BsGet
	str	w0, [x20, 56]
	mov	x0, x19
	bl	read_interp_filter_type
	str	w0, [x22, 1084]
.L1786:
	ldrsw	x1, [x24], 4
	mov	x0, x21
	ldr	w3, [x20, 5112]
	add	x21, x21, 16
	add	x1, x1, 331
	ldr	w4, [x20, 5116]
	add	x1, x20, x1, lsl 4
	ldr	w2, [x1, 12]
	ldr	w1, [x1, 8]
	bl	vp9_setup_scale_factors
	cmp	x25, x24
	bne	.L1786
	ldp	w0, w2, [x20, 68]
	ldr	w1, [x20, 76]
	cmp	w2, w0
	ccmp	w1, w0, 0, eq
	cset	w0, ne
	str	w0, [x20, 60]
	b	.L1774
	.p2align 3
.L1801:
	mov	x0, x19
	bl	Check_Sync_Code
	mov	x1, x20
	mov	x0, x19
	bl	Vp9_ReadBitDepthColorSpaceSampling
	mov	w0, 255
	str	w0, [x21, 116]
	mov	x1, x20
	mov	x0, x19
	ldr	w2, [x20, 5060]
	stp	w2, w2, [x20, 184]
	str	w2, [x20, 192]
	bl	Setup_Frame_Size
.L1774:
	add	x21, x22, 964
	ldr	w0, [x21, 40]
	cbz	w0, .L1803
.L1787:
	stp	wzr, wzr, [x21, 80]
	mov	w1, 2
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 1052]
	ldr	w2, [x22, 972]
	cbz	w2, .L1789
.L1802:
	ldr	w0, [x22, 1004]
	cbnz	w0, .L1789
	ldr	w0, [x22, 1072]
	cbnz	w0, .L1789
.L1791:
	ldp	w0, w2, [x20, 68]
	ldr	w1, [x20, 76]
	cmp	w2, w0
	ccmp	w1, w0, 0, eq
	cset	w0, ne
	str	w0, [x20, 60]
.L1790:
	add	x1, x20, 336
	mov	x0, x19
	bl	Setup_LoopFilter
	mov	x1, x20
	mov	x0, x19
	bl	Setup_Quantization
	add	x1, x22, 1088
	mov	x0, x19
	bl	Setup_Segmentation
	add	x1, x22, 964
	mov	x0, x19
	bl	Setup_Tile_Info
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, 8]
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1780:
	mov	w0, 1
	mov	w1, 8
	str	w0, [x26, 16]
	stp	w0, w0, [x26, 44]
	str	w1, [x26, 68]
	b	.L1781
	.p2align 3
.L1777:
	mov	w1, 2
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 1076]
	b	.L1778
	.p2align 3
.L1775:
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 108]
	ldr	w1, [x21, 40]
	b	.L1776
	.p2align 3
.L1784:
	ldr	x2, .LC97
	mov	w3, 3459
	ldr	x1, .LC99
	mov	w0, 1
	add	x2, x2, 688
	mov	w23, -1
	bl	dprint_vfmw
	b	.L1772
	.size	Read_UnCompressed_Header, .-Read_UnCompressed_Header
	.align	3
.LC96:
	.xword	.LC95
	.align	3
.LC97:
	.xword	.LANCHOR0
	.align	3
.LC99:
	.xword	.LC98
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	swap_frame_buffers
	.type	swap_frame_buffers, %function
swap_frame_buffers:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 4096
	mov	w1, 0
	add	x0, x0, 964
	add	x5, x19, 80
	mov	x7, x0
	ldr	w0, [x0, 116]
	cbz	w0, .L1809
	.p2align 2
.L1812:
	add	x4, x19, x1, sxtw 2
	tbz	x0, 0, .L1806
	ldr	w6, [x4, 152]
	ldr	w3, [x7]
	ldr	w2, [x5, w6, sxtw 2]
	cmp	w2, wzr
	sub	w2, w2, #1
	ble	.L1807
	str	w2, [x5, w6, sxtw 2]
.L1807:
	str	w3, [x4, 152]
	ldr	w2, [x5, w3, sxtw 2]
	add	w2, w2, 1
	str	w2, [x5, w3, sxtw 2]
.L1806:
	asr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1812
.L1809:
	ldrsw	x0, [x19, 5060]
	mov	w1, 2147483647
	add	x0, x19, x0, lsl 2
	ldr	w2, [x0, 80]
	sub	w2, w2, #1
	str	w2, [x0, 80]
	stp	w1, w1, [x19, 184]
	str	w1, [x19, 192]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	swap_frame_buffers, .-swap_frame_buffers
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_Set_DecParam
	.type	VP9_Set_DecParam, %function
VP9_Set_DecParam:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	add	x19, x23, 270336
	add	x20, x23, 16
	add	x22, x19, 2644
	bl	_mcount
	add	x2, x19, 2560
	ldr	w21, [x22, 5088]
	cmp	w21, 1
	beq	.L1849
	add	x3, x20, 262144
	add	x1, x19, 2576
	add	x0, x20, 270336
	strb	wzr, [x3, 1028]
	ldr	w3, [x22, 5068]
	str	w3, [x1, 60]
	ldr	w2, [x2, 8]
	str	w3, [x0, 2112]
	and	w2, w2, -16
	str	w2, [x0, 2128]
	ldr	w2, [x1, 64]
	str	w2, [x0, 2116]
	ldr	w2, [x22, 12]
	str	w2, [x0, 2088]
	ldr	w2, [x22, 16]
	str	w2, [x0, 2092]
	ldr	x2, [x23]
	ldr	w4, [x2, 640]
	str	w4, [x0, 2468]
	ldr	w4, [x2, 644]
	str	w4, [x0, 2472]
	ldr	w4, [x2, 648]
	str	w4, [x0, 2480]
	ldr	w4, [x2, 652]
	str	w4, [x0, 2484]
	ldr	w2, [x2, 692]
	str	w2, [x0, 2488]
	ldr	w2, [x1, 16]
	str	w2, [x0, 2460]
	ldr	w2, [x1, 32]
	str	w2, [x0, 2464]
	ldr	w0, [x22, 192]
	cmp	w0, 8
	ble	.L1850
	add	x21, x23, 311296
	ldrsw	x0, [x21, 3164]
	add	x22, x22, x0, lsl 2
	ldr	w0, [x22, 196]
	str	w0, [x1, 44]
	add	x1, x19, 2644
	ldr	w0, [x1, 188]
	cmp	w0, 8
	bgt	.L1825
.L1855:
	add	x0, x1, x0, sxtw 2
	add	x1, x19, 2644
	ldr	w0, [x0, 196]
	str	w0, [x19, 2616]
	ldr	w0, [x1, 184]
	cmp	w0, 8
	bgt	.L1827
.L1856:
	add	x0, x1, x0, sxtw 2
	ldr	w0, [x0, 196]
	str	w0, [x19, 2624]
	cbz	w3, .L1829
.L1857:
	ldr	w0, [x19, 7812]
	cmp	w0, 1
	beq	.L1829
	ldr	w1, [x19, 2628]
.L1830:
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	mov	x22, x0
	ldr	w1, [x19, 2620]
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldr	w1, [x19, 2616]
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	mov	x24, x0
	ldr	w1, [x19, 2624]
	ldr	w0, [x21, 3272]
	bl	FSP_GetLogicFs
	cmp	x22, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L1831
	cmp	x25, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L1831
	ldr	x1, [x22, 32]
	cbz	x1, .L1851
	add	x1, x20, 270336
	ldr	w2, [x22, 8]
	str	w2, [x1, 2456]
	ldr	x2, [x22, 32]
	ldr	w2, [x2, 20]
	str	w2, [x1, 2496]
	ldr	x2, [x22, 32]
	ldr	w2, [x2, 8]
	str	w2, [x1, 2440]
	ldr	x1, [x25, 32]
	cbz	x1, .L1852
.L1846:
	ldr	w2, [x1, 8]
	add	x1, x20, 270336
	str	w2, [x1, 2444]
	ldr	x1, [x24, 32]
	cbz	x1, .L1853
.L1847:
	ldr	w2, [x1, 8]
	add	x1, x20, 270336
	str	w2, [x1, 2448]
	ldr	x0, [x0, 32]
	cbz	x0, .L1854
.L1848:
	add	x1, x20, 270336
	ldr	w3, [x0, 8]
	add	x2, x20, 262144
	mov	w0, 0
	str	w3, [x1, 2452]
	ldr	w1, [x21, 3280]
	str	w1, [x21, 3276]
	str	w1, [x2, 1024]
	str	x20, [x23, 8]
.L1819:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1850:
	add	x22, x22, x0, sxtw 2
	add	x21, x23, 311296
	ldr	w0, [x22, 196]
	str	w0, [x1, 44]
	add	x1, x19, 2644
	ldr	w0, [x1, 188]
	cmp	w0, 8
	ble	.L1855
.L1825:
	ldrsw	x0, [x21, 3164]
	add	x0, x1, x0, lsl 2
	add	x1, x19, 2644
	ldr	w0, [x0, 196]
	str	w0, [x19, 2616]
	ldr	w0, [x1, 184]
	cmp	w0, 8
	ble	.L1856
.L1827:
	ldrsw	x0, [x21, 3164]
	add	x0, x1, x0, lsl 2
	ldr	w0, [x0, 196]
	str	w0, [x19, 2624]
	cbnz	w3, .L1857
.L1829:
	ldr	w1, [x19, 2628]
	str	w1, [x19, 2616]
	str	w1, [x19, 2620]
	str	w1, [x19, 2624]
	b	.L1830
	.p2align 3
.L1849:
	add	x0, x20, 262144
	add	x26, x20, 270336
	add	x24, x23, 311296
	strb	w21, [x0, 1028]
	ldr	x0, [x23]
	ldr	w1, [x0, 640]
	str	w1, [x26, 2468]
	ldr	w0, [x0, 692]
	str	w0, [x26, 2488]
	ldr	w1, [x19, 2628]
	ldr	w0, [x24, 3272]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldrsw	x1, [x22, 5092]
	ldr	w0, [x24, 3272]
	add	x1, x22, x1, lsl 2
	ldr	w1, [x1, 196]
	bl	FSP_GetLogicFs
	mov	x27, x0
	ldrsw	x1, [x22, 5092]
	ldr	w0, [x24, 3272]
	add	x22, x22, x1, lsl 2
	ldr	w1, [x22, 196]
	bl	FSP_GetFsImagePtr
	mov	x1, x0
	cmp	x25, xzr
	ccmp	x27, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L1831
	ldr	x0, [x25, 32]
	cbz	x0, .L1858
	ldr	w0, [x0, 8]
	str	w0, [x26, 2440]
	ldr	x0, [x27, 32]
	cbz	x0, .L1859
.L1845:
	add	x20, x20, 270336
	ldr	w2, [x0, 8]
	mov	w0, 0
	str	w2, [x20, 2448]
	ldr	x2, [x25, 32]
	ldr	w2, [x2, 20]
	str	w2, [x20, 2496]
	ldr	w2, [x1, 68]
	add	w2, w2, 63
	lsr	w2, w2, 6
	str	w2, [x20, 2088]
	ldr	w2, [x1, 72]
	add	w2, w2, 63
	lsr	w2, w2, 6
	str	w2, [x20, 2092]
	str	xzr, [x23, 8]
	ldr	w2, [x1, 68]
	str	w2, [x19, 2664]
	ldr	w1, [x1, 72]
	str	w1, [x19, 2668]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1854:
	ldr	x0, [x22, 32]
	b	.L1848
	.p2align 3
.L1853:
	ldr	x1, [x22, 32]
	b	.L1847
	.p2align 3
.L1852:
	ldr	x1, [x22, 32]
	b	.L1846
	.p2align 3
.L1831:
	ldr	x1, .LC101
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1819
	.p2align 3
.L1859:
	ldr	x0, [x25, 32]
	b	.L1845
.L1851:
	ldr	x1, .LC105
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1819
.L1858:
	ldr	x1, .LC103
	mov	w0, w21
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1819
	.size	VP9_Set_DecParam, .-VP9_Set_DecParam
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC103:
	.xword	.LC102
	.align	3
.LC105:
	.xword	.LC104
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_ArrangeVHBMem
	.type	VP9_ArrangeVHBMem, %function
VP9_ArrangeVHBMem:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 270336
	add	x19, x21, 2644
	bl	_mcount
	ldp	w2, w3, [x19, 20]
	cmp	w3, 31
	bls	.L1862
	mov	w1, 8160
	sub	w4, w2, #32
	mov	w0, 8192
	cmp	w4, w1
	ccmp	w3, w0, 2, ls
	bls	.L1863
.L1862:
	ldr	x1, .LC107
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1864:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1863:
	ldr	x1, .LC109
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x0, [x20]
	ldr	w1, [x0, 772]
	cbnz	w1, .L1865
	ldr	w1, [x0, 28]
	mov	w22, 5
	cmp	w1, 25
	beq	.L1891
.L1866:
	ldr	w0, [x21, 2580]
	cbnz	w0, .L1871
	add	x19, x20, 311296
	ldr	x0, .LC112
	ldr	x4, .LC113
	mov	w1, 0
	mov	x2, 20
	ldrsw	x3, [x19, 3272]
	ldr	x4, [x4, 96]
	ldr	x3, [x0, x3, lsl 3]
	add	x0, x29, 72
	add	x3, x3, 503808
	str	wzr, [x3, 1624]
	blr	x4
	strb	w22, [x29, 74]
	ldr	w4, [x21, 2664]
	mov	w2, 1
	ldr	w3, [x21, 2668]
	add	x1, x29, 72
	ldr	w0, [x19, 3272]
	strb	w2, [x29, 73]
	strb	w2, [x29, 75]
	stp	w4, w3, [x29, 76]
	stp	w4, w3, [x29, 84]
	bl	FSP_ConfigInstance
	cbz	w0, .L1892
.L1872:
	ldr	x1, .LC117
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1864
.L1865:
	ldr	w1, [x0, 28]
	mov	w22, 5
	cmp	w1, 25
	bne	.L1866
	ldr	w4, [x0, 732]
	ldr	w2, [x19, 20]
	cmp	w2, w4
	bhi	.L1890
	ldr	w5, [x0, 736]
	ldr	w1, [x19, 24]
	cmp	w1, w5
	bls	.L1870
.L1869:
	ldr	x1, .LC111
	mov	w0, 0
	ldr	w3, [x21, 2668]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1864
.L1871:
	add	x22, x20, 311296
	ldr	x23, .LC112
	ldr	x3, .LC113
	mov	w2, 1
	mov	w1, 0
	ldrsw	x0, [x22, 3272]
	ldr	x3, [x3, 96]
	ldr	w19, [x22, 3136]
	ldr	x0, [x23, x0, lsl 3]
	add	x0, x0, 503808
	str	w2, [x0, 1624]
	mov	x2, 20
	add	x0, x29, 72
	blr	x3
	strb	wzr, [x29, 74]
	ldr	x2, [x20]
	add	x1, x29, 72
	ldr	w4, [x21, 2664]
	ldr	w3, [x21, 2668]
	ldr	w0, [x2, 28]
	sxtb	w2, w19
	strb	wzr, [x29, 75]
	cmp	w0, 24
	ldr	w0, [x22, 3272]
	csinc	w2, w2, wzr, ne
	strb	w2, [x29, 73]
	stp	w4, w3, [x29, 76]
	stp	w4, w3, [x29, 84]
	bl	FSP_ConfigInstance
	cbnz	w0, .L1872
	ldr	x1, [x20]
	add	x3, x29, 68
	ldr	w0, [x22, 3272]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cbnz	w0, .L1893
.L1875:
	ldrsw	x0, [x22, 3272]
	ldr	x0, [x23, x0, lsl 3]
	str	wzr, [x0, 1600]
.L1873:
	mov	w1, 1
	mov	w0, 0
	str	w1, [x21, 2580]
	b	.L1864
.L1890:
	ldr	w5, [x0, 736]
	b	.L1869
.L1891:
	ldr	w4, [x0, 732]
	ldr	w2, [x19, 20]
	cmp	w2, w4
	bhi	.L1890
	ldr	w5, [x0, 736]
	ldr	w1, [x19, 24]
	cmp	w1, w5
	bhi	.L1869
	ldr	w1, [x21, 2580]
	cmp	w1, 1
	beq	.L1894
.L1870:
	ldr	w22, [x0, 780]
	b	.L1866
.L1894:
	mov	w0, 0
	b	.L1864
	.p2align 3
.L1892:
	ldr	x1, [x20]
	add	x3, x29, 68
	ldr	w0, [x19, 3272]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cbz	w0, .L1873
	ldr	x1, .LC115
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1864
.L1893:
	ldr	x1, .LC119
	mov	w0, 2
	bl	dprint_vfmw
	b	.L1875
	.size	VP9_ArrangeVHBMem, .-VP9_ArrangeVHBMem
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
.LC112:
	.xword	s_pstVfmwChan
	.align	3
.LC113:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC115:
	.xword	.LC114
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC119:
	.xword	.LC118
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9_GetRefNum
	.type	VP9_GetRefNum, %function
VP9_GetRefNum:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 274432
	add	x19, x29, 104
	bl	_mcount
	ldr	x23, .LC120
	add	x21, x21, 270336
	mov	x2, 36
	add	x1, x21, 2724
	mov	x0, x19
	ldr	x3, [x23, 104]
	ldr	w20, [x22, 3608]
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 32
	add	x1, x21, 2796
	add	x0, x29, 72
	blr	x3
	ldr	w0, [x22, 3636]
	cmp	w0, 1
	beq	.L1912
.L1896:
	ldr	w0, [x22, 3724]
	sxtw	x6, w20
	cbz	w0, .L1903
	mov	w1, 0
	add	x5, x19, x6, lsl 2
	.p2align 2
.L1902:
	sxtw	x2, w1
	tbz	x0, 0, .L1900
	add	x3, x29, 144
	add	x3, x3, x2, lsl 2
	mov	x2, x3
	ldr	w4, [x3, -72]
	ldr	w3, [x19, w4, sxtw 2]
	cmp	w3, wzr
	sub	w3, w3, #1
	ble	.L1901
	str	w3, [x19, w4, sxtw 2]
.L1901:
	str	w20, [x2, -72]
	ldr	w2, [x5]
	add	w2, w2, 1
	str	w2, [x5]
.L1900:
	asr	w0, w0, 1
	add	w1, w1, 1
	cbnz	w0, .L1902
.L1903:
	add	x0, x29, 144
	mov	x1, 0
	add	x2, x0, x6, lsl 2
	mov	w0, 0
	ldr	w3, [x2, -40]
	sub	w3, w3, #1
	str	w3, [x2, -40]
	.p2align 2
.L1899:
	ldr	w2, [x19, x1]
	add	x1, x1, 4
	cmp	w2, wzr
	csinc	w0, w0, w0, eq
	cmp	x1, 36
	bne	.L1899
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1912:
	ldr	w0, [x19, w20, sxtw 2]
	ldr	w1, [x22, 3640]
	cmp	w0, wzr
	ble	.L1897
	sub	w0, w0, #1
	str	w0, [x19, w20, sxtw 2]
.L1897:
	ldr	w0, [x19, w1, sxtw 2]
	mov	w20, w1
	add	w0, w0, 1
	str	w0, [x19, w1, sxtw 2]
	b	.L1896
	.size	VP9_GetRefNum, .-VP9_GetRefNum
	.align	3
.LC120:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_DefaultCoefProbs
	.type	Vp9_DefaultCoefProbs, %function
Vp9_DefaultCoefProbs:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC121
	ldr	x20, .LC122
	mov	x2, 1024
	mov	x0, x19
	ldr	x3, [x21, 104]
	mov	x1, x20
	blr	x3
	mov	x2, 1024
	ldr	x3, [x21, 104]
	add	x1, x20, x2
	add	x0, x19, x2
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 2048
	mov	x2, 1024
	add	x0, x19, 2048
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 3072
	mov	x2, 1024
	add	x0, x19, 3072
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_DefaultCoefProbs, .-Vp9_DefaultCoefProbs
	.align	3
.LC121:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC122:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_InitMbmodeProbs
	.type	Vp9_InitMbmodeProbs, %function
Vp9_InitMbmodeProbs:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 4096
	bl	_mcount
	ldr	x21, .LC123
	ldr	x20, .LC124
	mov	x2, 160
	add	x0, x19, 64
	ldr	x3, [x21, 104]
	sub	x1, x20, #256
	blr	x3
	ldr	x3, [x21, 104]
	sub	x1, x20, #96
	mov	x2, 64
	mov	x0, x19
	blr	x3
	ldr	x3, [x21, 104]
	sub	x1, x20, #32
	mov	x2, 8
	add	x0, x19, 364
	blr	x3
	ldr	x3, [x21, 104]
	sub	x1, x20, #24
	mov	x2, 96
	add	x0, x19, 516
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 72
	mov	x2, 4
	add	x0, x19, 319
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 80
	mov	x2, 5
	add	x0, x19, 323
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 88
	mov	x2, 5
	add	x0, x19, 328
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 96
	mov	x2, 10
	add	x0, x19, 333
	blr	x3
	ldr	x3, .LC125
	add	x0, x19, 307
	ldr	x4, [x21, 104]
	add	x1, x20, 112
	mov	x2, 3
	ldr	x5, [x3, 720]
	ldr	w3, [x3, 728]
	str	x5, [x0]
	str	w3, [x0, 8]
	add	x0, x19, 304
	blr	x4
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_InitMbmodeProbs, .-Vp9_InitMbmodeProbs
	.align	3
.LC123:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC124:
	.xword	.LANCHOR2
	.align	3
.LC125:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_InitMvProbs
	.type	Vp9_InitMvProbs, %function
Vp9_InitMvProbs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC126
	add	x0, x19, 4096
	add	x2, x0, 433
	add	x0, x0, 372
	add	x3, x1, 793
	add	x1, x1, 732
	ldp	x6, x7, [x1, 16]
	stp	x6, x7, [x0, 16]
	ldp	x8, x9, [x1]
	ldp	x4, x5, [x1, 32]
	ldp	x6, x7, [x1, 48]
	stp	x8, x9, [x0]
	stp	x4, x5, [x0, 32]
	stp	x6, x7, [x0, 48]
	ldr	x0, [x3]
	str	x0, [x2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_InitMvProbs, .-Vp9_InitMvProbs
	.align	3
.LC126:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_SetupPastIndependence
	.type	Vp9_SetupPastIndependence, %function
Vp9_SetupPastIndependence:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w3
	mov	w24, w4
	mov	w23, w5
	mov	x21, x1
	mov	x22, x2
	bl	_mcount
	mov	x0, x20
	bl	Vp9_DefaultCoefProbs
	mov	x0, x20
	bl	Vp9_InitMbmodeProbs
	ldr	x1, .LC131
	add	x0, x20, 4096
	add	x6, x0, 372
	add	x4, x0, 433
	add	x7, x1, 732
	add	x1, x1, 793
	add	x0, x0, 343
	mov	x2, 21
	ldp	x8, x9, [x7]
	ldr	x5, [x1]
	ldr	x1, .LC132
	stp	x8, x9, [x6]
	ldp	x8, x9, [x7, 16]
	stp	x8, x9, [x6, 16]
	ldp	x8, x9, [x7, 32]
	stp	x8, x9, [x6, 32]
	ldr	x3, [x1, 104]
	ldp	x8, x9, [x7, 48]
	ldr	x1, .LC133
	stp	x8, x9, [x6, 48]
	add	x1, x1, 116
	str	x5, [x4]
	blr	x3
	cmp	w24, wzr
	ccmp	w19, 3, 4, eq
	ccmp	w23, wzr, 4, ne
	beq	.L1922
	cmp	w19, 2
	beq	.L1923
	str	wzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1922:
	mov	x19, 0
	mov	x23, 18832
	.p2align 2
.L1918:
	add	x0, x21, x19
	mov	x2, 4708
	mov	x1, x20
	add	x19, x19, 4096
	add	x19, x19, 612
	bl	memcpy
	cmp	x19, x23
	bne	.L1918
	str	wzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1923:
	ldr	w0, [x22]
	mov	w3, 4708
	mov	x1, x20
	mov	x2, 4708
	umull	x0, w0, w3
	add	x0, x21, x0
	bl	memcpy
	str	wzr, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_SetupPastIndependence, .-Vp9_SetupPastIndependence
	.align	3
.LC131:
	.xword	.LANCHOR0
	.align	3
.LC132:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC133:
	.xword	.LANCHOR2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_SegfeatureActive
	.type	Vp9_Vfmw_SegfeatureActive, %function
Vp9_Vfmw_SegfeatureActive:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	ldrb	w0, [x20]
	cbz	w0, .L1926
	add	x19, x20, x19, sxtw 2
	mov	w0, 1
	lsl	w2, w0, w21
	ldr	x21, [sp, 32]
	ldr	w0, [x19, 80]
	ldp	x19, x20, [sp, 16]
	tst	w2, w0
	cset	w0, ne
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1926:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_Vfmw_SegfeatureActive, .-Vp9_Vfmw_SegfeatureActive
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_GetSegdata
	.type	Vp9_Vfmw_GetSegdata, %function
Vp9_Vfmw_GetSegdata:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w1
	mov	w19, w2
	sbfiz	x20, x20, 2, 32
	mov	x21, x0
	add	x19, x20, x19, uxtw
	mov	x0, x30
	add	x19, x19, 8
	bl	_mcount
	ldrsh	w0, [x21, x19, lsl 1]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_Vfmw_GetSegdata, .-Vp9_Vfmw_GetSegdata
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_Clamp
	.type	Vp9_Vfmw_Clamp, %function
Vp9_Vfmw_Clamp:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w2
	bl	_mcount
	cmp	w19, w21
	csel	w0, w19, w21, ge
	ldr	x21, [sp, 32]
	cmp	w0, w20
	csel	w0, w0, w20, le
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_Vfmw_Clamp, .-Vp9_Vfmw_Clamp
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_LoopFilterFrameInit
	.type	Vp9_Vfmw_LoopFilterFrameInit, %function
Vp9_Vfmw_LoopFilterFrameInit:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	x27, x2
	mov	w26, w3
	mov	x20, x1
	bl	_mcount
	ldr	x3, .LC138
	asr	w19, w26, 5
	add	x23, x27, 80
	add	x24, x27, 18
	add	x28, x27, 112
	mov	w21, 63
	add	x25, x20, 6
	.p2align 2
.L1935:
	ldrb	w0, [x27]
	mov	w1, w26
	cbz	w0, .L1930
	ldr	w0, [x23]
	tbz	x0, 1, .L1930
	ldrsh	w1, [x24]
	ldrb	w2, [x27, 3]
	add	w0, w1, w26
	cmp	w2, 1
	csel	w1, w0, w1, ne
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	cmp	w1, 63
	csel	w1, w1, w21, le
.L1930:
	ldrb	w0, [x20]
	cbz	w0, .L1944
	ldrsb	w2, [x20, 2]
	add	x5, x20, 3
	mov	x0, x22
	lsl	w2, w2, w19
	adds	w2, w2, w1
	csel	w2, w2, wzr, pl
	cmp	w2, 63
	csel	w2, w2, w21, le
	strb	w2, [x22]
.L1934:
	ldrsb	w2, [x5]
	add	x0, x0, 2
	ldrsb	w4, [x20, 6]
	lsl	w2, w2, w19
	lsl	w4, w4, w19
	add	w2, w2, w1
	adds	w2, w2, w4
	csel	w2, w2, wzr, pl
	cmp	w2, 63
	csel	w2, w2, w21, le
	strb	w2, [x0]
	ldrsb	w2, [x5], 1
	ldrsb	w4, [x20, 7]
	lsl	w2, w2, w19
	lsl	w4, w4, w19
	add	w2, w2, w1
	adds	w2, w2, w4
	csel	w2, w2, wzr, pl
	cmp	w2, 63
	csel	w2, w2, w21, le
	cmp	x25, x5
	strb	w2, [x0, 1]
	bne	.L1934
	add	x23, x23, 4
	add	x22, x22, 8
	cmp	x28, x23
	add	x24, x24, 8
	bne	.L1935
.L1945:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1944:
	ldr	x4, [x3, 96]
	mov	x0, x22
	mov	x2, 8
	str	x3, [x29, 104]
	add	x23, x23, 4
	add	x22, x22, 8
	blr	x4
	add	x24, x24, 8
	cmp	x28, x23
	ldr	x3, [x29, 104]
	bne	.L1935
	b	.L1945
	.size	Vp9_Vfmw_LoopFilterFrameInit, .-Vp9_Vfmw_LoopFilterFrameInit
	.align	3
.LC138:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_MiColsAlignedToSb
	.type	Vp9_MiColsAlignedToSb, %function
Vp9_MiColsAlignedToSb:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	add	w0, w19, 7
	ldr	x19, [sp, 16]
	and	w0, w0, -8
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_MiColsAlignedToSb, .-Vp9_MiColsAlignedToSb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ToSbs
	.type	Vp9_ToSbs, %function
Vp9_ToSbs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	add	w0, w19, 7
	ldr	x19, [sp, 16]
	asr	w0, w0, 3
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_ToSbs, .-Vp9_ToSbs
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_GetTileOffsets
	.type	Vp9_GetTileOffsets, %function
Vp9_GetTileOffsets:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w19, w4
	mov	w21, w3
	mov	x22, x1
	mov	w20, w2
	bl	_mcount
	add	w0, w19, 7
	asr	w0, w0, 3
	mul	w5, w20, w0
	asr	w2, w5, w21
	add	w0, w5, w0
	asr	w3, w0, w21
	lsl	w2, w2, 3
	cmp	w2, w19
	lsl	w3, w3, 3
	csel	w2, w2, w19, le
	cmp	w3, w19
	str	w2, [x23]
	csel	w3, w3, w19, le
	str	w3, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_GetTileOffsets, .-Vp9_GetTileOffsets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_GetTileRowOffsets
	.type	Vp9_GetTileRowOffsets, %function
Vp9_GetTileRowOffsets:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	x23, x3
	mov	x22, x4
	bl	_mcount
	add	w0, w20, 7
	asr	w6, w0, 3
	mul	w0, w19, w6
	asr	w5, w0, w21
	add	w0, w6, w0
	asr	w2, w0, w21
	lsl	w5, w5, 3
	cmp	w5, w20
	lsl	w2, w2, 3
	csel	w5, w5, w20, le
	cmp	w2, w20
	str	w5, [x23]
	csel	w2, w2, w20, le
	str	w2, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_GetTileRowOffsets, .-Vp9_GetTileRowOffsets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_Vfmw_GetTileColOffsets
	.type	Vp9_Vfmw_GetTileColOffsets, %function
Vp9_Vfmw_GetTileColOffsets:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	x23, x3
	mov	x22, x4
	bl	_mcount
	add	w0, w20, 7
	asr	w6, w0, 3
	mul	w0, w19, w6
	asr	w5, w0, w21
	add	w0, w6, w0
	asr	w2, w0, w21
	lsl	w5, w5, 3
	cmp	w5, w20
	lsl	w2, w2, 3
	csel	w5, w5, w20, le
	cmp	w2, w20
	str	w5, [x23]
	csel	w2, w2, w20, le
	str	w2, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Vp9_Vfmw_GetTileColOffsets, .-Vp9_Vfmw_GetTileColOffsets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_SetPoolInfoFrame
	.type	Vp9_SetPoolInfoFrame, %function
Vp9_SetPoolInfoFrame:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 16
	mov	x19, x1
	add	x23, x21, 270336
	bl	_mcount
	ldr	w1, [x23, 2480]
	ldr	w0, [x23, 2472]
	bl	GetCompressRatio
	mov	w22, w0
	ldr	w1, [x23, 2484]
	ldr	w0, [x23, 2472]
	bl	GetCompressRatio
	add	x8, x20, 270336
	add	x9, x20, 311296
	mov	w5, 1048576
	ldr	w1, [x8, 2876]
	ldr	w3, [x8, 2880]
	ubfiz	w1, w1, 10, 3
	ldr	w4, [x8, 7708]
	ubfiz	w3, w3, 13, 2
	ldr	w2, [x8, 7812]
	orr	w3, w3, w1
	ldr	w1, [x8, 7712]
	ubfiz	w4, w4, 1, 2
	ubfiz	w2, w2, 7, 1
	and	w1, w1, 1
	orr	w1, w4, w1
	orr	w4, w3, w1
	ldr	w3, [x8, 7772]
	ldr	w1, [x8, 7788]
	ubfiz	w3, w3, 15, 4
	ubfiz	w1, w1, 9, 1
	orr	w1, w3, w1
	orr	w3, w4, w1
	ldr	w4, [x8, 7784]
	ubfiz	w4, w4, 8, 1
	orr	w1, w4, w2
	ldr	w2, [x8, 7748]
	orr	w4, w3, w1
	ldr	w1, [x8, 7752]
	ubfiz	w2, w2, 5, 1
	ubfiz	w1, w1, 6, 1
	orr	w1, w1, w2
	ldr	w2, [x8, 7740]
	orr	w3, w4, w1
	ldr	w1, [x8, 7744]
	ubfiz	w2, w2, 3, 1
	ubfiz	w1, w1, 4, 1
	orr	w1, w1, w2
	orr	w1, w3, w1
	str	w1, [x19]
	ldr	w2, [x8, 7756]
	ldr	w1, [x9, 3156]
	cmp	w2, w1
	beq	.L1988
.L1952:
	add	x4, x8, 2644
	ldr	w1, [x4, 76]
	ldr	w2, [x4, 184]
	mov	w10, 0
	ldr	w0, [x4, 5180]
	ubfiz	w1, w1, 7, 1
	ubfiz	w2, w2, 8, 4
	and	w0, w0, 7
	orr	w2, w2, w1
	orr	w5, w0, w5
	ldp	w1, w0, [x4, 188]
	ubfiz	w0, w0, 16, 4
	ubfiz	w1, w1, 12, 4
	orr	w1, w0, w1
	orr	w0, w2, w1
	ldp	w1, w2, [x4, 68]
	ubfiz	w2, w2, 6, 1
	ubfiz	w1, w1, 5, 1
	orr	w1, w2, w1
	orr	w2, w0, w1
	ldr	w1, [x4, 56]
	ldr	w0, [x4, 64]
	ubfiz	w1, w1, 3, 1
	ubfiz	w0, w0, 4, 1
	orr	w1, w0, w1
	orr	w0, w2, w1
	orr	w0, w0, w5
	str	w0, [x19, 4]
	ldr	w0, [x4, 5116]
	ldr	w2, [x4, 5112]
	add	w0, w0, 7
	asr	w0, w0, 3
	add	w2, w2, 7
	sub	w1, w0, #1
	asr	w2, w2, 3
	sub	w0, w2, #1
	orr	w0, w0, w1, lsl 16
	str	w0, [x19, 8]
	ldr	w1, [x4, 344]
	ldr	w0, [x4, 348]
	ubfiz	w1, w1, 8, 6
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x19, 12]
	.p2align 2
.L1953:
	lsl	w3, w10, 1
	mov	w5, 0
	sbfiz	x11, x10, 2, 32
	add	x3, x19, x3, sxtw 2
.L1954:
	lsl	w0, w5, 1
	add	x3, x3, 4
	add	w1, w0, 1
	add	w5, w5, 1
	add	x0, x11, x0, sxtw
	cmp	w5, 2
	add	x1, x11, x1, sxtw
	add	x6, x4, x0, lsl 1
	add	x7, x4, x1, lsl 1
	mov	x0, x6
	mov	x2, x7
	ldrb	w6, [x6, 257]
	ldrb	w1, [x0, 256]
	ldrb	w7, [x7, 257]
	ubfiz	w0, w6, 8, 6
	ldrb	w2, [x2, 256]
	and	w1, w1, 63
	ubfiz	w6, w7, 24, 6
	orr	w0, w0, w1
	ubfiz	w2, w2, 16, 6
	orr	w2, w6, w2
	orr	w0, w2, w0
	str	w0, [x3, 12]
	bne	.L1954
	add	w10, w10, 1
	cmp	w10, 8
	bne	.L1953
	ldr	w3, [x4, 252]
	mov	w2, 268435456
	ldr	w4, [x8, 2892]
	add	x0, x8, 2644
	cmp	w3, wzr
	add	x0, x0, 4096
	sxtw	x5, w3
	csel	w6, wzr, w2, ge
	cmp	w4, wzr
	mov	w2, 1048576
	eor	x3, x5, x5, asr 63
	csel	w2, wzr, w2, ge
	sub	x3, x3, x5, asr 63
	sxtw	x5, w4
	ubfiz	w4, w3, 24, 4
	orr	w2, w6, w2
	eor	x1, x5, x5, asr 63
	sub	x1, x1, x5, asr 63
	ldrb	w5, [x8, 2884]
	ubfiz	w1, w1, 16, 4
	orr	w3, w1, w4
	ldr	w4, [x8, 2888]
	cmp	w4, wzr
	sxtw	x4, w4
	eor	x1, x4, x4, asr 63
	sub	x1, x1, x4, asr 63
	ubfiz	w1, w1, 8, 4
	orr	w1, w1, w5
	orr	w1, w1, w3
	orr	w1, w1, w2
	mov	w2, 4096
	csel	w2, wzr, w2, ge
	orr	w1, w1, w2
	str	w1, [x19, 80]
	ldrb	w4, [x0, 1089]
	ldrb	w3, [x0, 1092]
	ldrb	w2, [x0, 1091]
	ldrb	w1, [x0, 1088]
	ubfiz	w0, w3, 3, 1
	ubfiz	w2, w2, 2, 1
	ubfiz	w3, w4, 1, 1
	and	w1, w1, 1
	orr	w0, w0, w2
	orr	w1, w3, w1
	add	x4, x20, 274432
	orr	w0, w0, w1
	add	x3, x4, 3812
	mov	w1, 0
	mov	w2, 0
	str	w0, [x19, 84]
	.p2align 2
.L1959:
	ldr	w0, [x3], 4
	and	w0, w0, 15
	lsl	w0, w0, w1
	add	w1, w1, 4
	cmp	w1, 32
	orr	w2, w2, w0
	bne	.L1959
	str	w2, [x19, 88]
	ldrh	w2, [x8, 7860]
	ldrh	w1, [x8, 7852]
	ubfiz	w2, w2, 18, 9
	ubfiz	w1, w1, 9, 9
	orr	w2, w2, w1
	ldrh	w1, [x8, 7844]
	and	w1, w1, 511
	orr	w1, w1, w2
	str	w1, [x19, 92]
	ldrh	w2, [x8, 7884]
	ldrh	w1, [x8, 7876]
	ubfiz	w2, w2, 18, 9
	ubfiz	w1, w1, 9, 9
	orr	w2, w2, w1
	ldrh	w1, [x8, 7868]
	and	w1, w1, 511
	orr	w1, w1, w2
	str	w1, [x19, 96]
	mov	w2, 0
	ldrh	w1, [x8, 7900]
	ldrh	w0, [x8, 7892]
	ubfiz	w1, w1, 9, 9
	and	w0, w0, 511
	orr	w1, w1, w0
	mov	x0, 0
	str	w1, [x19, 100]
.L1960:
	add	x1, x0, 274432
	add	x1, x1, 3750
	ldrb	w1, [x20, x1]
	lsl	w1, w1, w0
	add	x0, x0, 8
	cmp	x0, 32
	orr	w2, w2, w1
	bne	.L1960
	str	w2, [x19, 104]
	mov	x0, 0
	mov	w2, 0
.L1961:
	add	x1, x0, 274432
	add	x1, x1, 3782
	ldrb	w1, [x20, x1]
	lsl	w1, w1, w0
	add	x0, x0, 8
	cmp	x0, 32
	orr	w2, w2, w1
	bne	.L1961
	add	x4, x4, 3752
	mov	w3, 0
	mov	w5, 0
	str	w2, [x19, 108]
	.p2align 2
.L1962:
	ldrh	w2, [x4]
	lsl	w6, w3, 1
	ldrh	w1, [x4, 2]
	add	w0, w3, 16
	and	w2, w2, 3
	add	w3, w3, 1
	and	w1, w1, 1
	lsl	w2, w2, w6
	lsl	w0, w1, w0
	cmp	w3, 8
	orr	w0, w2, w0
	add	x4, x4, 8
	orr	w5, w5, w0
	bne	.L1962
	str	w5, [x19, 112]
	add	x0, x8, 2644
	ldr	w2, [x8, 2592]
	str	w2, [x19, 116]
	ldr	w1, [x8, 2608]
	str	w1, [x19, 120]
	ldr	w1, [x0, 36]
	str	w1, [x19, 128]
	ldr	w1, [x0, 40]
	str	w1, [x19, 132]
	ldr	w1, [x0, 44]
	str	w1, [x19, 136]
	ldr	w1, [x0, 48]
	str	w1, [x19, 140]
	ldr	w1, [x0, 5440]
	ldrh	w2, [x0, 5444]
	orr	w1, w2, w1, lsl 16
	str	w1, [x19, 180]
	ldr	w1, [x0, 5456]
	ldrh	w2, [x0, 5460]
	orr	w1, w2, w1, lsl 16
	str	w1, [x19, 184]
	ldr	w1, [x0, 5472]
	ldrh	w2, [x0, 5476]
	orr	w1, w2, w1, lsl 16
	str	w1, [x19, 188]
	ldr	w2, [x0, 5468]
	ldr	w3, [x0, 5484]
	ldr	w1, [x0, 5452]
	ubfiz	w2, w2, 8, 6
	ubfiz	w3, w3, 16, 6
	orr	w2, w3, w2
	and	w1, w1, 63
	orr	w1, w1, w2
	str	w1, [x19, 192]
	ldr	w2, [x0, 5464]
	ldr	w3, [x0, 5480]
	ldr	w1, [x0, 5448]
	ubfiz	w2, w2, 8, 6
	ubfiz	w3, w3, 16, 6
	orr	w2, w3, w2
	and	w1, w1, 63
	orr	w1, w1, w2
	str	w1, [x19, 196]
	ldr	w0, [x0, 184]
	cmp	w0, 8
	bls	.L1963
	str	wzr, [x19, 200]
.L1964:
	ldr	w0, [x8, 2832]
	cmp	w0, 8
	bls	.L1965
	str	wzr, [x19, 204]
.L1966:
	ldr	w0, [x8, 2836]
	cmp	w0, 8
	bls	.L1967
	str	wzr, [x19, 208]
.L1968:
	ldr	w0, [x9, 3160]
	ldrh	w1, [x9, 3156]
	orr	w0, w1, w0, lsl 16
	str	w0, [x19, 212]
	ldr	w0, [x8, 2828]
	cmp	w0, 8
	bls	.L1969
	stp	wzr, wzr, [x19, 216]
	str	wzr, [x19, 224]
.L1970:
	ldr	w0, [x8, 2832]
	cmp	w0, 8
	bls	.L1972
	stp	wzr, wzr, [x19, 228]
	str	wzr, [x19, 236]
	ldr	w0, [x8, 2836]
	cmp	w0, 8
	bhi	.L1989
.L1975:
	add	x0, x20, x0, sxtw 4
	add	x21, x21, 270336
	add	x0, x0, 274432
	ldr	w1, [x0, 3852]
	add	w1, w1, 255
	and	w1, w1, -256
	lsl	w1, w1, 4
	mul	w1, w1, w22
	cmp	w1, wzr
	add	w2, w1, 7
	csel	w1, w2, w1, lt
	asr	w1, w1, 3
	str	w1, [x19, 240]
	ldr	w3, [x0, 3852]
	ldr	w4, [x0, 3856]
	add	w1, w3, 255
	ldr	w7, [x21, 2468]
	and	w1, w1, -256
	add	w5, w4, 63
	and	w6, w5, -64
	mul	w1, w1, w22
	cmp	w1, wzr
	add	w2, w1, 7
	csel	w1, w2, w1, lt
	cmp	w7, 1
	asr	w1, w1, 3
	mul	w1, w1, w6
	beq	.L1990
.L1977:
	str	w1, [x19, 244]
	ldr	w1, [x0, 3852]
	ldr	w3, [x0, 3856]
	adds	w0, w1, 2047
	add	w1, w1, 4094
	csel	w0, w1, w0, mi
	add	w2, w3, 126
	and	w0, w0, -2048
	cmp	w0, wzr
	add	w1, w0, 127
	csel	w0, w1, w0, lt
	adds	w1, w3, 63
	csel	w1, w2, w1, mi
	asr	w0, w0, 7
	asr	w1, w1, 6
	lsl	w1, w1, 5
	mul	w0, w0, w1
	str	w0, [x19, 248]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1972:
	add	x0, x20, x0, sxtw 4
	add	x5, x21, 270336
	add	x2, x0, 274432
	ldr	w0, [x2, 3852]
	add	w0, w0, 255
	and	w0, w0, -256
	lsl	w0, w0, 4
	mul	w0, w0, w22
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w0, w1, w0, lt
	asr	w0, w0, 3
	str	w0, [x19, 228]
	ldr	w3, [x2, 3852]
	ldr	w4, [x2, 3856]
	add	w0, w3, 255
	and	w0, w0, -256
	add	w6, w4, 63
	mul	w1, w0, w22
	cmp	w1, wzr
	add	w0, w1, 7
	csel	w0, w0, w1, lt
	ldr	w1, [x5, 2468]
	asr	w0, w0, 3
	cmp	w1, 1
	and	w1, w6, -64
	mul	w0, w0, w1
	beq	.L1991
.L1974:
	str	w0, [x19, 232]
	ldr	w0, [x2, 3852]
	ldr	w3, [x2, 3856]
	adds	w1, w0, 2047
	add	w0, w0, 4094
	csel	w0, w0, w1, mi
	add	w2, w3, 126
	and	w0, w0, -2048
	cmp	w0, wzr
	add	w1, w0, 127
	csel	w0, w1, w0, lt
	adds	w1, w3, 63
	csel	w1, w2, w1, mi
	asr	w0, w0, 7
	asr	w1, w1, 6
	lsl	w1, w1, 5
	mul	w0, w0, w1
	str	w0, [x19, 236]
	ldr	w0, [x8, 2836]
	cmp	w0, 8
	bls	.L1975
.L1989:
	stp	wzr, wzr, [x19, 240]
	str	wzr, [x19, 248]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1969:
	add	x0, x20, x0, sxtw 4
	add	x5, x21, 270336
	add	x2, x0, 274432
	ldr	w0, [x2, 3852]
	add	w0, w0, 255
	and	w0, w0, -256
	lsl	w0, w0, 4
	mul	w0, w0, w22
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w0, w1, w0, lt
	asr	w0, w0, 3
	str	w0, [x19, 216]
	ldr	w3, [x2, 3852]
	ldr	w4, [x2, 3856]
	add	w0, w3, 255
	and	w0, w0, -256
	add	w6, w4, 63
	mul	w1, w0, w22
	cmp	w1, wzr
	add	w0, w1, 7
	csel	w0, w0, w1, lt
	ldr	w1, [x5, 2468]
	asr	w0, w0, 3
	cmp	w1, 1
	and	w1, w6, -64
	mul	w0, w0, w1
	beq	.L1992
.L1971:
	str	w0, [x19, 220]
	ldr	w0, [x2, 3852]
	ldr	w3, [x2, 3856]
	adds	w1, w0, 2047
	add	w0, w0, 4094
	csel	w0, w0, w1, mi
	add	w2, w3, 126
	and	w0, w0, -2048
	cmp	w0, wzr
	add	w1, w0, 127
	csel	w0, w1, w0, lt
	adds	w1, w3, 63
	csel	w1, w2, w1, mi
	asr	w0, w0, 7
	asr	w1, w1, 6
	lsl	w1, w1, 5
	mul	w0, w0, w1
	str	w0, [x19, 224]
	b	.L1970
	.p2align 3
.L1967:
	add	x0, x20, x0, sxtw 4
	add	x2, x21, 270336
	add	x0, x0, 274432
	ldr	w1, [x0, 3852]
	str	w1, [x2, 2528]
	and	w1, w1, 65535
	ldr	w0, [x0, 3856]
	str	w0, [x2, 2540]
	orr	w0, w1, w0, lsl 16
	str	w0, [x19, 208]
	b	.L1968
	.p2align 3
.L1965:
	add	x0, x20, x0, sxtw 4
	add	x2, x21, 270336
	add	x0, x0, 274432
	ldr	w1, [x0, 3852]
	str	w1, [x2, 2524]
	and	w1, w1, 65535
	ldr	w0, [x0, 3856]
	str	w0, [x2, 2536]
	orr	w0, w1, w0, lsl 16
	str	w0, [x19, 204]
	b	.L1966
	.p2align 3
.L1963:
	add	x0, x20, x0, sxtw 4
	add	x2, x21, 270336
	add	x0, x0, 274432
	ldr	w1, [x0, 3852]
	str	w1, [x2, 2520]
	and	w1, w1, 65535
	ldr	w0, [x0, 3856]
	str	w0, [x2, 2532]
	orr	w0, w1, w0, lsl 16
	str	w0, [x19, 200]
	b	.L1964
	.p2align 3
.L1988:
	ldr	w1, [x8, 7760]
	ldr	w0, [x9, 3160]
	cmp	w1, w0
	csel	w5, w5, wzr, ne
	b	.L1952
	.p2align 3
.L1990:
	ldr	w2, [x21, 2472]
	cbnz	w2, .L1977
	adds	w2, w3, 2047
	add	w3, w3, 4094
	csel	w2, w3, w2, mi
	add	w4, w4, 126
	and	w2, w2, -2048
	cmp	w2, wzr
	add	w3, w2, 127
	csel	w3, w3, w2, lt
	cmp	w5, wzr
	csel	w2, w4, w5, lt
	asr	w3, w3, 7
	asr	w2, w2, 6
	lsl	w2, w2, 5
	madd	w1, w3, w2, w1
	b	.L1977
.L1991:
	ldr	w1, [x5, 2472]
	cbnz	w1, .L1974
	adds	w1, w3, 2047
	add	w3, w3, 4094
	csel	w1, w3, w1, mi
	add	w4, w4, 126
	and	w1, w1, -2048
	cmp	w1, wzr
	add	w3, w1, 127
	csel	w3, w3, w1, lt
	cmp	w6, wzr
	csel	w1, w4, w6, lt
	asr	w3, w3, 7
	asr	w1, w1, 6
	lsl	w1, w1, 5
	madd	w0, w3, w1, w0
	b	.L1974
.L1992:
	ldr	w1, [x5, 2472]
	cbnz	w1, .L1971
	adds	w1, w3, 2047
	add	w3, w3, 4094
	csel	w1, w3, w1, mi
	add	w4, w4, 126
	and	w1, w1, -2048
	cmp	w1, wzr
	add	w3, w1, 127
	csel	w3, w3, w1, lt
	cmp	w6, wzr
	csel	w1, w4, w6, lt
	asr	w3, w3, 7
	asr	w1, w1, 6
	lsl	w1, w1, 5
	madd	w0, w3, w1, w0
	b	.L1971
	.size	Vp9_SetPoolInfoFrame, .-Vp9_SetPoolInfoFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_SetPoolInfoTile
	.type	Vp9_SetPoolInfoTile, %function
Vp9_SetPoolInfoTile:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x3
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	w0, [x19]
	str	w0, [x20]
	ldrb	w0, [x19, 4]
	and	w0, w0, 127
	str	w0, [x20, 4]
	ldr	w0, [x19, 8]
	add	w0, w0, 128
	str	w0, [x20, 8]
	ldr	w0, [x19, 12]
	str	w0, [x20, 12]
	ldrb	w0, [x19, 16]
	and	w0, w0, 127
	str	w0, [x20, 16]
	ldr	w0, [x19, 20]
	str	w0, [x20, 20]
	ldrh	w2, [x19, 24]
	ldrh	w0, [x19, 26]
	add	w1, w2, 7
	cmp	w2, w0
	ubfx	x1, x1, 3, 7
	lsl	w1, w1, 16
	beq	.L1994
	add	w0, w0, 7
	asr	w0, w0, 3
	sub	w0, w0, #1
	and	w0, w0, 127
	orr	w0, w0, w1
.L1995:
	str	w0, [x20, 24]
	ldrh	w2, [x19, 28]
	ldrh	w0, [x19, 30]
	add	w1, w2, 7
	cmp	w2, w0
	ubfx	x1, x1, 3, 7
	lsl	w1, w1, 16
	orr	w2, w1, 255
	beq	.L1997
	add	w0, w0, 7
	asr	w0, w0, 3
	sub	w0, w0, #1
	and	w0, w0, 127
	orr	w2, w0, w1
.L1997:
	str	w2, [x20, 28]
	ldr	w0, [x19, 32]
	and	w0, w0, 131071
	str	w0, [x20, 32]
	ldr	w0, [x19, 36]
	and	w0, w0, 131071
	str	w0, [x20, 36]
	ldr	w0, [x19, 40]
	and	w0, w0, 131071
	str	w0, [x20, 40]
	ldr	w0, [x19, 44]
	str	wzr, [x20, 252]
	and	w0, w0, 131071
	str	w0, [x20, 44]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1994:
	orr	w0, w1, 255
	b	.L1995
	.size	Vp9_SetPoolInfoTile, .-Vp9_SetPoolInfoTile
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_DecodeTilesCtrl
	.type	Vp9_DecodeTilesCtrl, %function
Vp9_DecodeTilesCtrl:
	stp	x29, x30, [sp, -288]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x26, x1
	add	x19, x20, 270336
	mov	x0, x30
	str	x20, [x29, 136]
	bl	_mcount
	ldrsw	x22, [x26, 24]
	ldr	x27, [x26]
	mov	w1, 1
	ldr	w0, [x19, 7800]
	ldr	w3, [x19, 7808]
	ldr	w2, [x19, 7804]
	stp	w3, w0, [x29, 112]
	add	x0, x27, x22
	str	x0, [x29, 208]
	add	x0, x20, 311296
	lsl	w3, w1, w3
	str	w2, [x29, 172]
	lsl	w1, w1, w2
	mov	x2, x20
	mov	x20, x0
	str	w1, [x29, 204]
	mov	x0, x2
	add	x1, x2, 16
	mov	w21, w3
	ldr	w28, [x19, 7796]
	str	w3, [x29, 108]
	str	x20, [x29, 128]
	bl	Vp9_SetPoolInfoFrame
	str	wzr, [x20, 3280]
	cmp	w21, wzr
	ldr	w0, [x19, 2568]
	ldr	x1, [x19, 2560]
	and	w0, w0, 15
	str	x1, [x29, 152]
	str	w0, [x29, 160]
	ble	.L2009
	ldr	w1, [x29, 116]
	add	w0, w28, 7
	mov	w21, 0
	str	wzr, [x29, 148]
	add	w1, w1, 7
	asr	w2, w1, 3
	asr	w1, w0, 3
	ldr	w0, [x29, 204]
	stp	w1, w2, [x29, 100]
	sub	w0, w0, #1
	stp	w0, w1, [x29, 164]
	ldr	w0, [x29, 108]
	stp	wzr, wzr, [x29, 120]
	sub	w0, w0, #1
	str	w0, [x29, 144]
.L2008:
	ldr	w1, [x29, 104]
	ldr	w0, [x29, 124]
	ldrb	w4, [x29, 112]
	add	w0, w0, w1
	asr	w3, w0, w4
	mov	w2, w0
	ldr	w0, [x29, 120]
	lsl	w23, w3, 3
	stp	w3, w2, [x29, 120]
	lsl	w25, w0, 3
	ldr	w0, [x29, 116]
	ldr	w2, [x29, 204]
	cmp	w25, w0
	csel	w1, w25, w0, le
	cmp	w23, w0
	csel	w0, w23, w0, le
	cmp	w2, wzr
	stp	w0, w1, [x29, 192]
	mov	w2, w0
	sub	w0, w0, w1
	add	w0, w0, 7
	asr	w3, w0, 3
	str	w3, [x29, 200]
	ble	.L2001
	add	w24, w2, 7
	ldr	w2, [x29, 100]
	asr	w24, w24, 3
	mov	w23, 0
	sub	w24, w24, #1
	mov	w25, w23
	mov	w20, 0
	mov	w19, 0
	mul	w0, w24, w2
	str	w0, [x29, 188]
	add	w0, w1, 7
	asr	w0, w0, 3
	mov	w23, w28
	mov	x24, x27
	mul	w0, w0, w2
	str	w0, [x29, 184]
	ldr	x0, [x29, 136]
	ldr	w2, [x26, 24]
	add	x0, x0, 278528
	str	x0, [x29, 176]
	b	.L2007
	.p2align 3
.L2020:
	ldp	w2, w3, [x29, 144]
	cmp	w2, w3
	bgt	.L2002
.L2004:
	ldr	x2, [x29, 152]
	sub	w1, w28, w22
	ldrh	w3, [x29, 196]
	add	w1, w1, 7
	sub	x0, x0, x2
	strh	w3, [x29, 256]
	ldr	w2, [x29, 160]
	asr	w1, w1, 3
	ldr	w3, [x29, 200]
	add	w4, w22, 7
	add	w0, w2, w0
	ldr	w5, [x29, 188]
	and	w2, w0, 15
	and	w0, w0, -16
	mul	w1, w1, w3
	ldrh	w3, [x29, 192]
	ubfiz	w2, w2, 3, 5
	strh	w3, [x29, 258]
	add	w3, w28, 7
	str	w0, [x29, 232]
	add	w11, w1, w21
	ldr	w0, [x29, 184]
	add	w3, w5, w3, asr 3
	sub	w3, w3, #1
	add	x5, x29, 288
	add	w4, w0, w4, asr 3
	sub	w0, w11, #1
	str	w21, [x29, 276]
	add	x24, x24, x27, sxtw
	str	w0, [x29, 268]
	lsl	w0, w27, 3
	strh	w22, [x29, 260]
	mov	w21, w11
	strh	w28, [x29, 262]
	strb	wzr, [x29, 248]
	strb	w2, [x29, 236]
	str	wzr, [x29, 244]
	str	wzr, [x29, 252]
	str	w3, [x29, 264]
	str	x5, [x29, 280]
	str	w4, [x29, 272]
	str	w0, [x29, 240]
	cbnz	w1, .L2017
	ldr	x0, [x29, 176]
	cmp	w27, wzr
	ldr	w5, [x0, 576]
	ccmp	w27, w5, 0, ge
	bgt	.L2018
.L2006:
	ldr	w2, [x26, 24]
	ldr	w0, [x29, 204]
	sub	w2, w2, w27
	str	w2, [x26, 24]
	cmp	w0, w25
	beq	.L2019
.L2007:
	ldr	w0, [x29, 168]
	lsl	w4, w19, 3
	cmp	w4, w23
	add	x5, x24, 4
	add	w20, w20, w0
	ldrb	w0, [x29, 172]
	csel	w22, w4, w23, le
	mov	x1, x24
	asr	w19, w20, w0
	ldr	w0, [x29, 208]
	lsl	w3, w19, 3
	str	x5, [x29, 216]
	cmp	w3, w23
	sub	w27, w0, w24
	mov	x0, x26
	csel	w28, w3, w23, le
	bl	BsInit
	ldr	w2, [x29, 164]
	mov	x0, x24
	mov	w1, 32
	ldr	x5, [x29, 216]
	cmp	w25, w2
	add	w25, w25, 1
	bge	.L2020
.L2002:
	ldr	x0, [x29, 208]
	cmp	x24, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L2011
	cmp	x0, x5
	ccmp	x5, x24, 0, cs
	mov	x24, x5
	bls	.L2011
	mov	x0, x26
	bl	BsGet
	mov	w27, w0
	mov	x0, x24
	b	.L2004
	.p2align 3
.L2017:
	ldp	x22, x4, [x29, 128]
	add	x3, x29, 232
	str	w11, [x29, 216]
	mov	x0, x4
	ldr	w2, [x22, 3280]
	ubfiz	x1, x2, 8, 32
	add	x1, x1, 1040
	add	x1, x4, x1
	bl	Vp9_SetPoolInfoTile
	ldr	w0, [x22, 3280]
	cmp	w27, wzr
	ldr	w11, [x29, 216]
	add	w0, w0, 1
	str	w0, [x22, 3280]
	ldr	x0, [x29, 176]
	ldr	w5, [x0, 576]
	ccmp	w27, w5, 0, ge
	ble	.L2006
.L2018:
	ldr	x2, .LC139
	mov	w4, w27
	ldr	x1, .LC141
	mov	w3, 4556
	add	x2, x2, 808
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 288
	ret
	.p2align 3
.L2011:
	mov	w0, -1
.L2000:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 288
	ret
	.p2align 3
.L2019:
	mov	w28, w23
	mov	x27, x24
	mov	w21, w11
.L2001:
	ldr	w0, [x29, 148]
	ldr	w1, [x29, 108]
	add	w0, w0, 1
	str	w0, [x29, 148]
	cmp	w0, w1
	bne	.L2008
.L2009:
	mov	w0, 0
	b	.L2000
	.size	Vp9_DecodeTilesCtrl, .-Vp9_DecodeTilesCtrl
	.align	3
.LC139:
	.xword	.LANCHOR0
	.align	3
.LC141:
	.xword	.LC140
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_DecodeTiles
	.type	Vp9_DecodeTiles, %function
Vp9_DecodeTiles:
	sub	sp, sp, #192
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	stp	x27, x28, [sp, 96]
	mov	x19, x0
	mov	x0, x30
	add	x23, x19, 270336
	add	x21, x19, 311296
	mov	x26, x1
	mov	w24, w2
	bl	_mcount
	str	wzr, [x29, 124]
	ldr	w22, [x23, 7712]
	mov	w2, w24
	ldr	w0, [x23, 7792]
	mov	x1, x26
	ldr	w3, [x23, 7816]
	cmp	w22, wzr
	ldr	w28, [x23, 2696]
	add	x20, x19, 278528
	ldr	w27, [x23, 2704]
	add	x25, x20, 592
	str	w22, [x21, 3248]
	stp	w0, w3, [x29, 104]
	stp	w0, wzr, [x29, 116]
	cset	w0, eq
	str	w0, [x21, 3236]
	ldr	w0, [x23, 7744]
	str	w0, [x21, 3256]
	add	x0, x29, 128
	ldr	w5, [x23, 7812]
	str	w5, [x21, 3240]
	ldr	w5, [x23, 7788]
	str	w5, [x21, 3260]
	ldr	w5, [x23, 2700]
	str	w5, [x21, 3264]
	ldr	w5, [x23, 7824]
	str	w5, [x21, 3268]
	ldr	w4, [x23, 7708]
	str	w4, [x21, 3252]
	bl	BsInit
	ldr	w0, [x21, 3236]
	ldr	w4, [x21, 3256]
	ldr	w3, [x29, 108]
	cbnz	w0, .L2023
	cbz	w4, .L2038
.L2023:
	add	x1, x19, 282624
	add	x2, x29, 116
	add	x1, x1, 1204
	mov	x0, x25
	mov	w5, w22
	bl	Vp9_SetupPastIndependence
	ldr	x0, .LC142
	mov	x2, 16
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x23, 2708
	blr	x3
.L2024:
	ldr	w1, [x29, 116]
	mov	x2, 4708
	add	x0, x20, 592
	madd	x1, x1, x2, x19
	add	x1, x1, 282624
	add	x1, x1, 1204
	bl	memcpy
	add	x0, x29, 128
	bl	Vp9_Cabac_ReaderInit
	add	x0, x29, 124
	ldr	w3, [x21, 3240]
	ldr	w5, [x21, 3264]
	mov	w7, w28
	ldr	w4, [x21, 3268]
	mov	w6, w27
	str	x0, [sp, 8]
	add	x0, x29, 120
	mov	w2, w22
	str	x0, [sp]
	mov	x1, x25
	add	x0, x29, 128
	bl	Vp9_ReadCompressedHeader
	cbnz	w0, .L2039
	ldr	w0, [x29, 124]
	add	x2, x23, 2644
	str	w0, [x23, 2876]
	str	w0, [x21, 3244]
	ldr	w0, [x29, 120]
	ldr	w3, [x23, 2988]
	str	w0, [x23, 2880]
	cbnz	w3, .L2040
.L2027:
	ldr	w0, [x21, 3240]
	cbnz	w0, .L2041
	uxtw	x1, w22
	ldr	x27, .LC142
	lsl	x0, x1, 2
	mov	x2, 48
	sub	x1, x0, x1
	add	x0, x20, 592
	ldr	x3, [x27, 104]
	add	x1, x0, x1, lsl 4
	add	x0, x0, 4096
	add	x1, x1, 4096
	add	x0, x0, 256
	add	x1, x1, 516
	blr	x3
.L2029:
	add	x20, x20, 592
	add	x28, x23, 2644
	add	x20, x20, 4096
	add	x28, x28, 4096
	ldr	x3, [x27, 104]
	mov	x2, 7
	add	x1, x28, 1093
	add	x0, x20, 448
	blr	x3
	ldr	x3, [x27, 104]
	add	x1, x28, 1100
	mov	x2, 3
	add	x0, x20, 456
	blr	x3
	add	x0, x19, 262144
	ldr	x3, [x27, 104]
	mov	x1, x25
	add	x0, x0, 1045
	mov	x2, 4608
	blr	x3
	ldr	w0, [x21, 3240]
	cbz	w0, .L2030
	ldr	w21, [x29, 104]
	mov	x0, 4708
	ldr	x3, [x27, 104]
	mov	x2, 48
	mul	x0, x21, x0
	add	x0, x0, 286720
	add	x1, x19, x0
	mov	x0, x1
	add	x1, x1, 1720
	add	x0, x0, 1460
	blr	x3
.L2031:
	mov	x1, 4708
	ldr	x3, [x27, 104]
	add	x0, x19, 266240
	mov	x2, 4608
	madd	x21, x21, x1, x19
	add	x0, x0, 1557
	add	x1, x21, 282624
	add	x1, x1, 1204
	blr	x3
	ldr	w2, [x23, 2652]
	add	x1, x29, 128
	mov	x0, x19
	sub	w24, w24, w2
	str	w24, [x29, 152]
	add	x26, x26, x2, uxtw
	str	x26, [x29, 128]
	bl	Vp9_DecodeTilesCtrl
	mov	w0, 0
.L2026:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L2041:
	ldr	x27, .LC142
	add	x0, x20, 592
	add	x0, x0, 4096
	mov	x2, 48
	add	x1, x0, 516
	add	x0, x0, 256
	ldr	x3, [x27, 104]
	blr	x3
	b	.L2029
	.p2align 3
.L2038:
	ldr	w0, [x21, 3240]
	cbz	w0, .L2024
	b	.L2023
	.p2align 3
.L2030:
	ldr	w21, [x29, 104]
	uxtw	x22, w22
	mov	x0, 4708
	lsl	x1, x22, 2
	sub	x1, x1, x22
	ldr	x3, [x27, 104]
	mul	x0, x21, x0
	mov	x2, 48
	add	x1, x0, x1, lsl 4
	add	x0, x0, 286720
	add	x1, x1, 286720
	add	x0, x19, x0
	add	x1, x19, x1
	add	x0, x0, 1460
	add	x1, x1, 1720
	blr	x3
	b	.L2031
	.p2align 3
.L2040:
	add	x2, x2, 4096
	add	x1, x23, 2980
	add	x2, x2, 1088
	add	x0, x23, 2900
	bl	Vp9_Vfmw_LoopFilterFrameInit
	b	.L2027
	.p2align 3
.L2039:
	ldr	x1, .LC144
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2026
	.size	Vp9_DecodeTiles, .-Vp9_DecodeTiles
	.align	3
.LC142:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC144:
	.xword	.LC143
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_DecodeFame
	.type	VP9DEC_DecodeFame, %function
VP9DEC_DecodeFame:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 311296
	mov	x26, x1
	bl	_mcount
	add	x24, x21, 278528
	add	x20, x21, 270336
	add	x23, x24, 552
	ldr	w0, [x19, 3168]
	add	x25, x20, 2644
	add	x22, x21, 274432
	cbz	w0, .L2043
	ldr	w0, [x22, 3608]
	tbnz	w0, #31, .L2043
.L2044:
	str	w0, [x19, 3164]
	mov	x1, x25
	mov	x0, x23
	bl	Read_UnCompressed_Header
	cbnz	w0, .L2088
	ldr	x0, [x21]
	ldr	w1, [x20, 7772]
	str	w1, [x0, 972]
	ldr	w2, [x20, 7772]
	cmp	w2, 10
	bgt	.L2122
.L2050:
	ldr	w0, [x22, 3636]
	cbz	w0, .L2123
.L2052:
	add	x27, x20, 2644
	ldr	w2, [x27, 5112]
	sub	w0, w2, #128
	cmp	w0, 3968
	bhi	.L2053
	ldr	w1, [x27, 5116]
	sub	w0, w1, #80
	cmp	w0, 4016
	bhi	.L2053
	adds	w0, w2, 63
	stp	w2, w1, [x27, 20]
	add	w2, w2, 126
	csel	w0, w2, w0, mi
	asr	w0, w0, 6
	str	w0, [x27, 12]
	adds	w0, w1, 63
	add	w1, w1, 126
	csel	w0, w1, w0, mi
	asr	w0, w0, 6
	str	w0, [x27, 16]
	mov	x0, x21
	bl	VP9_GetRefNum
	str	w0, [x19, 3140]
	ldr	w0, [x19, 3272]
	ldp	w1, w2, [x27, 20]
	bl	VCTRL_GetFsSize
	mov	w1, w0
	str	w0, [x19, 3128]
	ldr	w0, [x19, 3272]
	bl	FSP_GetPhyFsNum
	str	w0, [x19, 3132]
	ldr	x1, .LC154
	ldr	w0, [x19, 3272]
	ldr	x2, [x1, w0, sxtw 3]
	ldr	w1, [x2, 1560]
	str	w1, [x19, 3136]
	ldr	w5, [x27, 20]
	cmp	w5, 1920
	bls	.L2124
.L2057:
	ldr	w3, [x19, 3140]
	ldr	w2, [x19, 3144]
	ldr	x4, .LC155
	cmp	w2, w3
	csel	w2, w2, w3, ge
	ldr	w4, [x4, 140]
	add	w1, w1, w2
	cmp	w4, w1
	csel	w1, w4, w1, cs
	str	w1, [x19, 3136]
	ldr	w1, [x19, 3148]
	cmp	w5, w1
	beq	.L2125
.L2059:
	str	w3, [x19, 3144]
.L2061:
	mov	w1, 0
	bl	FSP_GetPhyFsNum
	mov	w28, w0
	ldr	w0, [x19, 3132]
	cmp	w28, w0
	ble	.L2062
	sub	w1, w28, w0
	cmp	w1, wzr
	ble	.L2062
	mov	w27, 0
	b	.L2064
	.p2align 3
.L2063:
	ldr	w0, [x19, 3132]
	sub	w1, w28, w0
	cmp	w1, w27
	ble	.L2062
.L2064:
	ldr	w1, [x19, 3128]
	add	w27, w27, 1
	ldr	w0, [x19, 3272]
	bl	FSP_RelsePhyFs
	cbz	w0, .L2063
	ldr	w0, [x19, 3132]
.L2062:
	ldr	w1, [x19, 3136]
	cmp	w0, w1
	ble	.L2067
	sub	w0, w0, w1
	cmp	w0, wzr
	ble	.L2067
	mov	w27, 0
	b	.L2068
	.p2align 3
.L2126:
	ldr	w0, [x19, 3132]
	ldr	w1, [x19, 3136]
	sub	w0, w0, w1
	cmp	w0, w27
	ble	.L2067
.L2068:
	ldr	w0, [x19, 3272]
	mov	w1, 0
	add	w27, w27, 1
	bl	FSP_RelsePhyFs
	cbz	w0, .L2126
.L2067:
	ldr	w0, [x19, 3272]
	mov	w1, 0
	bl	FSP_GetPhyFsNum
	mov	w27, w0
	ldr	w0, [x19, 3136]
	add	w0, w0, 4
	cmp	w27, w0
	bgt	.L2127
	ldr	w1, [x19, 3128]
	ldr	w0, [x19, 3272]
	bl	FSP_GetPhyFsNum
	add	w1, w0, 1
	ldr	w6, [x19, 3140]
	mov	w5, w0
	ldr	w2, [x19, 3136]
	mov	w4, w27
	add	w7, w6, 2
	str	w0, [x19, 3132]
	cmp	w1, w7
	csel	w1, w1, w7, le
	sub	w7, w0, w27
	add	w7, w7, w2
	mov	w0, 2
	cmp	w1, w7
	csel	w7, w1, w7, ge
	str	w7, [x19, 3136]
	ldr	x1, .LC157
	ldr	w2, [x20, 2664]
	ldr	w3, [x20, 2668]
	bl	dprint_vfmw
	ldr	w0, [x20, 2580]
	cbz	w0, .L2069
	ldr	w1, [x19, 3148]
	ldr	w0, [x20, 2664]
	cmp	w1, w0
	beq	.L2128
.L2069:
	mov	x0, x21
	bl	VP9_ArrangeVHBMem
	ldr	w0, [x20, 2580]
	cbz	w0, .L2129
.L2070:
	ldr	x0, [x21]
	ldr	w0, [x0, 8]
	str	w0, [x20, 2576]
	ldr	w0, [x22, 3636]
	cbz	w0, .L2130
.L2071:
	ldr	w0, [x19, 3272]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	bne	.L2131
	mov	x0, x23
	bl	BsBitsToNextByte
	cbnz	w0, .L2132
	ldr	w0, [x20, 7732]
	cbz	w0, .L2133
.L2074:
	mov	x0, x21
	bl	VP9_GetImageBuffer
	cbnz	w0, .L2134
	ldrsw	x1, [x19, 3164]
	add	x23, x20, 2644
	ldr	w2, [x20, 2628]
	mov	x0, x21
	add	x1, x23, x1, lsl 2
	str	w2, [x1, 196]
	bl	VP9_Set_DecParam
	cbnz	w0, .L2135
	ldr	w1, [x22, 3636]
	cmp	w1, 1
	beq	.L2136
	ldr	w0, [x23, 20]
	str	w0, [x19, 3156]
	ldr	w0, [x23, 24]
	str	w0, [x19, 3160]
.L2079:
	mov	x0, x25
	bl	swap_frame_buffers
	ldr	x2, [x19, 3216]
	ldr	x3, [x19, 3224]
	cmp	x2, x3
	bcs	.L2080
	ldrb	w0, [x2]
	cbnz	w0, .L2080
	add	x0, x2, 1
	b	.L2081
	.p2align 3
.L2137:
	ldrb	w1, [x0], 1
	cbnz	w1, .L2080
.L2081:
	cmp	x3, x0
	str	x0, [x19, 3216]
	mov	x2, x0
	bne	.L2137
.L2080:
	ldr	w0, [x19, 3172]
	cmp	w0, 1
	beq	.L2138
.L2082:
	str	wzr, [x19, 3168]
	ldr	w0, [x20, 7732]
	cbnz	w0, .L2083
	ldr	w1, [x22, 3632]
	str	w1, [x22, 3644]
.L2118:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2043:
	ldr	w2, [x20, 2724]
	add	x1, x20, 2728
	mov	w0, 1
	cbz	w2, .L2139
	.p2align 2
.L2105:
	ldr	w2, [x1]
	add	x1, x1, 4
	cbz	w2, .L2045
	add	w0, w0, 1
	cmp	w0, 9
	bne	.L2105
	mov	w0, -1
	str	w0, [x22, 3608]
.L2085:
	ldr	x1, .LC146
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2118
	.p2align 3
.L2123:
	ldr	w2, [x20, 2572]
	cmp	w2, 7
	bgt	.L2052
	ldr	x1, .LC151
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2118
	.p2align 3
.L2124:
	ldr	w3, [x27, 24]
	cmp	w3, 1088
	bhi	.L2057
	ldr	w3, [x2, 36]
	cmp	w3, 24
	beq	.L2058
	add	x2, x2, 507904
	ldr	w2, [x2, 1732]
	cmp	w2, wzr
	add	w2, w1, 4
	csel	w1, w2, w1, eq
.L2058:
	ldr	w3, [x19, 3140]
	ldr	w2, [x19, 3144]
	cmp	w2, w3
	csel	w2, w2, w3, ge
	add	w1, w2, w1
	str	w1, [x19, 3136]
	ldr	w1, [x19, 3148]
	cmp	w5, w1
	bne	.L2059
.L2125:
	ldr	w4, [x19, 3152]
	ldr	w1, [x20, 2668]
	cmp	w4, w1
	bne	.L2059
	str	w2, [x19, 3144]
	b	.L2061
	.p2align 3
.L2130:
	ldr	w1, [x20, 2664]
	str	w1, [x19, 3148]
	ldr	w0, [x20, 2668]
	str	w0, [x19, 3152]
	b	.L2071
.L2139:
	mov	w0, 0
	.p2align 2
.L2045:
	add	x1, x20, x0, sxtw 2
	mov	w2, 1
	str	w2, [x1, 2724]
	str	w0, [x22, 3608]
	tbz	w0, #31, .L2044
	b	.L2085
	.p2align 3
.L2122:
	ldr	x1, .LC148
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC149
	ldr	x4, [x0]
	cbz	x4, .L2050
	ldr	w0, [x20, 7772]
	mov	w3, 8
	stp	wzr, w0, [x29, 104]
	ldr	w0, [x19, 3272]
	add	x2, x29, 104
	mov	w1, 119
	blr	x4
	b	.L2050
	.p2align 3
.L2083:
	mov	w3, 0
	mov	w2, 0
	mov	w1, 0
	mov	x0, x21
	bl	VP9DEC_VDMPostProc
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L2132:
	mov	w1, w0
	mov	x0, x23
	bl	BsGet
	ldr	w0, [x20, 7732]
	cbnz	w0, .L2074
.L2133:
	ldr	w0, [x24, 584]
	ldr	w2, [x24, 576]
	add	w0, w0, 7
	lsr	w1, w0, 3
	mov	x0, x21
	sub	w2, w2, w1
	add	x1, x26, x1
	bl	Vp9_DecodeTiles
	b	.L2074
	.p2align 3
.L2136:
	add	x1, x20, 2724
	ldr	w3, [x22, 3608]
	ldr	w2, [x22, 3640]
	ldr	w0, [x1, w3, sxtw 2]
	cmp	w0, wzr
	ble	.L2078
	sub	w0, w0, #1
	str	w0, [x1, w3, sxtw 2]
.L2078:
	str	w2, [x22, 3608]
	ldr	w0, [x1, w2, sxtw 2]
	add	w0, w0, 1
	str	w0, [x1, w2, sxtw 2]
	b	.L2079
	.p2align 3
.L2128:
	ldr	w1, [x19, 3152]
	ldr	w0, [x20, 2668]
	cmp	w1, w0
	bne	.L2069
	ldr	w1, [x19, 3132]
	ldr	w0, [x19, 3136]
	cmp	w1, w0
	bge	.L2070
	b	.L2069
	.p2align 3
.L2138:
	ldr	w0, [x19, 3212]
	add	w1, w0, 1
	sxtw	x0, w0
	add	x0, x0, 77824
	add	x0, x21, x0, lsl 2
	ldrsw	x0, [x0, 3176]
	str	w1, [x19, 3212]
	add	x2, x2, x0
	str	x2, [x19, 3216]
	b	.L2082
	.p2align 3
.L2053:
	ldr	x0, .LC149
	ldr	x4, [x0]
	cbz	x4, .L2055
	ldr	w0, [x19, 3272]
	mov	x2, 0
	mov	w3, 0
	mov	w1, 102
	blr	x4
	ldr	w2, [x20, 7756]
.L2055:
	ldr	w3, [x20, 7760]
	mov	w0, 1
	ldr	x1, .LC153
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
.L2127:
	mov	w0, -2
	b	.L2118
	.p2align 3
.L2131:
	ldr	x2, .LC160
	mov	w3, 4072
	ldr	x1, .LC162
	mov	w0, 23
	add	x2, x2, 832
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2118
.L2088:
	mov	w0, -1
	b	.L2118
.L2134:
	ldr	x1, .LC164
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2118
.L2129:
	ldr	x1, .LC159
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L2118
.L2135:
	ldr	x1, .LC166
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2118
	.size	VP9DEC_DecodeFame, .-VP9DEC_DecodeFame
	.align	3
.LC146:
	.xword	.LC145
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC149:
	.xword	g_event_report
	.align	3
.LC151:
	.xword	.LC150
	.align	3
.LC153:
	.xword	.LC152
	.align	3
.LC154:
	.xword	s_pstVfmwChan
	.align	3
.LC155:
	.xword	.LANCHOR2
	.align	3
.LC157:
	.xword	.LC156
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC160:
	.xword	.LANCHOR0
	.align	3
.LC162:
	.xword	.LC161
	.align	3
.LC164:
	.xword	.LC163
	.align	3
.LC166:
	.xword	.LC165
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP9DEC_DecodePacket
	.type	VP9DEC_DecodePacket, %function
VP9DEC_DecodePacket:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x29, 60]
	cmp	x21, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L2150
	add	x22, x21, 270336
	ldr	x0, [x19]
	add	x20, x21, 311296
	str	x0, [x22, 2560]
	ldr	w1, [x19, 16]
	str	w1, [x22, 2568]
	ldr	w1, [x19, 20]
	str	w1, [x22, 2572]
	ldr	w5, [x20, 3172]
	cbz	w5, .L2142
	ldr	w2, [x20, 3232]
	ldr	x19, [x20, 3216]
.L2145:
	cbz	w2, .L2154
	ldrb	w3, [x19]
	and	w1, w3, 7
	ubfx	x4, x3, 3, 2
	add	w0, w1, 1
	and	w1, w3, 224
	cmp	w1, 192
	madd	w0, w4, w0, w0
	bne	.L2146
	add	w1, w0, 1
	add	w0, w0, 2
	cmp	w0, w2
	bhi	.L2146
	ldrb	w1, [x19, x1]
	cmp	w1, w3
	bne	.L2146
	ldr	x1, [x20, 3224]
	add	x19, x19, x0, uxtb
	sub	w2, w2, w0
	str	x19, [x20, 3216]
	cmp	x19, x1
	str	w2, [x20, 3232]
	bcc	.L2145
.L2146:
	cmp	w5, 1
	beq	.L2160
.L2148:
	add	x0, x21, 278528
	mov	x1, x19
	add	x0, x0, 552
	bl	BsInit
	mov	x1, x19
	mov	x0, x21
	bl	VP9DEC_DecodeFame
	cmn	w0, #2
	mov	w19, w0
	beq	.L2161
	mov	w0, 0
	cbnz	w19, .L2162
.L2141:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2162:
	mov	x0, x21
	bl	VP9_FreeCurFb
	str	wzr, [x20, 3172]
	mov	x1, x21
	mov	w0, 17
	bl	ReleasePacket
	ldr	x1, .LC169
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2142:
	add	x3, x29, 60
	add	x2, x29, 64
	bl	Vp9_ParseSuperFrameIndex
	ldr	w0, [x29, 60]
	cbnz	w0, .L2163
.L2144:
	ldr	x19, [x22, 2560]
	str	x19, [x20, 3216]
	ldr	w5, [x20, 3172]
	ldr	w2, [x22, 2572]
	str	w2, [x20, 3232]
	add	x0, x19, x2, uxtw
	str	x0, [x20, 3224]
	b	.L2145
	.p2align 3
.L2160:
	ldrsw	x0, [x20, 3212]
	add	x0, x0, 77824
	add	x0, x21, x0, lsl 2
	ldr	w2, [x0, 3176]
	b	.L2148
	.p2align 3
.L2163:
	ldr	x1, .LC167
	mov	w2, 1
	str	w0, [x20, 3208]
	add	x0, x20, 3176
	str	w2, [x20, 3172]
	mov	x2, 32
	ldr	x3, [x1, 104]
	add	x1, x29, 64
	str	wzr, [x20, 3212]
	blr	x3
	b	.L2144
	.p2align 3
.L2161:
	mov	w1, 1
	str	w1, [x20, 3168]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2150:
	mov	w0, -1
	b	.L2141
	.p2align 3
.L2154:
	mov	w2, 0
	b	.L2146
	.size	VP9DEC_DecodePacket, .-VP9DEC_DecodePacket
	.align	3
.LC167:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC169:
	.xword	.LC168
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_TxCoefProbConvert2
	.type	Vp9_TxCoefProbConvert2, %function
Vp9_TxCoefProbConvert2:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x21, .LC170
	mov	x1, x20
	mov	x2, 18
	mov	x0, x19
	ldr	x3, [x21, 104]
	blr	x3
	mov	x2, 18
	ldr	x3, [x21, 104]
	add	x1, x20, x2
	add	x0, x19, 32
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 36
	mov	x2, 18
	add	x0, x19, 64
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 54
	mov	x2, 18
	add	x0, x19, 96
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 72
	mov	x2, 18
	add	x0, x19, 128
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 90
	mov	x2, 18
	add	x0, x19, 160
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 108
	mov	x2, 18
	add	x0, x19, 192
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 256
	mov	x2, 18
	add	x0, x19, 256
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 274
	mov	x2, 18
	add	x0, x19, 288
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 292
	mov	x2, 18
	add	x0, x19, 320
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 310
	mov	x2, 18
	add	x0, x19, 352
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 328
	mov	x2, 18
	add	x0, x19, 384
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 346
	mov	x2, 18
	add	x0, x19, 416
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 364
	mov	x2, 18
	add	x0, x19, 448
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_TxCoefProbConvert2, .-Vp9_TxCoefProbConvert2
	.align	3
.LC170:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_ProbBurstConvert
	.type	Vp9_ProbBurstConvert, %function
Vp9_ProbBurstConvert:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x3, .LC171
	mov	x1, x20
	mov	x2, 4608
	mov	x0, x19
	ldr	x3, [x3, 104]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp9_ProbBurstConvert, .-Vp9_ProbBurstConvert
	.align	3
.LC171:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp9_CoefCountRestore
	.type	Vp9_CoefCountRestore, %function
Vp9_CoefCountRestore:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	mov	x1, x21
	mov	w15, 0
	mov	w0, 0
.L2167:
	add	w16, w0, 288
	mov	x14, x1
	mov	w13, w15
.L2173:
	add	w12, w0, 144
	mov	x11, x14
	mov	w2, w13
	.p2align 2
.L2171:
	add	w10, w0, 24
	mov	x3, x11
	mov	w6, w2
	.p2align 2
.L2168:
	ldr	w4, [x19, w0, uxtw 2]
	add	w5, w0, 1
	add	x3, x3, 16
	add	w8, w0, 2
	and	w9, w4, 67108863
	str	w9, [x20, w6, uxtw 2]
	add	w7, w0, 3
	add	w0, w0, 4
	ldr	w5, [x19, w5, uxtw 2]
	cmp	w0, w10
	add	w6, w6, 1
	ubfiz	w9, w5, 6, 20
	orr	w4, w9, w4, lsr 26
	str	w4, [x3, -16]
	ldr	w4, [x19, w8, uxtw 2]
	ubfiz	w8, w4, 12, 14
	orr	w5, w8, w5, lsr 20
	str	w5, [x3, -12]
	ldr	w5, [x19, w7, uxtw 2]
	ubfiz	w7, w5, 18, 8
	lsr	w5, w5, 8
	orr	w4, w7, w4, lsr 14
	stp	w4, w5, [x3, -8]
	bne	.L2168
	cmp	w0, w12
	add	w2, w2, 6
	add	x11, x11, 96
	bne	.L2171
	cmp	w10, w16
	add	w13, w13, 36
	add	x14, x14, 576
	bne	.L2173
	cmp	w10, 576
	add	w15, w15, 72
	add	x1, x1, 1152
	mov	w0, w10
	bne	.L2167
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp9_CoefCountRestore, .-Vp9_CoefCountRestore
	.global	g_CfgVp9FrmNum
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	vp9_cabac_norm, %object
	.size	vp9_cabac_norm, 256
vp9_cabac_norm:
	.byte	0
	.byte	7
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
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
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
	.byte	0
	.byte	0
	.type	vp9_inv_map_table, %object
	.size	vp9_inv_map_table, 254
vp9_inv_map_table:
	.byte	6
	.byte	19
	.byte	32
	.byte	45
	.byte	58
	.byte	71
	.byte	84
	.byte	97
	.byte	110
	.byte	123
	.byte	-120
	.byte	-107
	.byte	-94
	.byte	-81
	.byte	-68
	.byte	-55
	.byte	-42
	.byte	-29
	.byte	-16
	.byte	-3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	5
	.byte	7
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	21
	.byte	22
	.byte	23
	.byte	24
	.byte	25
	.byte	26
	.byte	27
	.byte	28
	.byte	29
	.byte	30
	.byte	31
	.byte	33
	.byte	34
	.byte	35
	.byte	36
	.byte	37
	.byte	38
	.byte	39
	.byte	40
	.byte	41
	.byte	42
	.byte	43
	.byte	44
	.byte	46
	.byte	47
	.byte	48
	.byte	49
	.byte	50
	.byte	51
	.byte	52
	.byte	53
	.byte	54
	.byte	55
	.byte	56
	.byte	57
	.byte	59
	.byte	60
	.byte	61
	.byte	62
	.byte	63
	.byte	64
	.byte	65
	.byte	66
	.byte	67
	.byte	68
	.byte	69
	.byte	70
	.byte	72
	.byte	73
	.byte	74
	.byte	75
	.byte	76
	.byte	77
	.byte	78
	.byte	79
	.byte	80
	.byte	81
	.byte	82
	.byte	83
	.byte	85
	.byte	86
	.byte	87
	.byte	88
	.byte	89
	.byte	90
	.byte	91
	.byte	92
	.byte	93
	.byte	94
	.byte	95
	.byte	96
	.byte	98
	.byte	99
	.byte	100
	.byte	101
	.byte	102
	.byte	103
	.byte	104
	.byte	105
	.byte	106
	.byte	107
	.byte	108
	.byte	109
	.byte	111
	.byte	112
	.byte	113
	.byte	114
	.byte	115
	.byte	116
	.byte	117
	.byte	118
	.byte	119
	.byte	120
	.byte	121
	.byte	122
	.byte	124
	.byte	125
	.byte	126
	.byte	127
	.byte	-128
	.byte	-127
	.byte	-126
	.byte	-125
	.byte	-124
	.byte	-123
	.byte	-122
	.byte	-121
	.byte	-119
	.byte	-118
	.byte	-117
	.byte	-116
	.byte	-115
	.byte	-114
	.byte	-113
	.byte	-112
	.byte	-111
	.byte	-110
	.byte	-109
	.byte	-108
	.byte	-106
	.byte	-105
	.byte	-104
	.byte	-103
	.byte	-102
	.byte	-101
	.byte	-100
	.byte	-99
	.byte	-98
	.byte	-97
	.byte	-96
	.byte	-95
	.byte	-93
	.byte	-92
	.byte	-91
	.byte	-90
	.byte	-89
	.byte	-88
	.byte	-87
	.byte	-86
	.byte	-85
	.byte	-84
	.byte	-83
	.byte	-82
	.byte	-80
	.byte	-79
	.byte	-78
	.byte	-77
	.byte	-76
	.byte	-75
	.byte	-74
	.byte	-73
	.byte	-72
	.byte	-71
	.byte	-70
	.byte	-69
	.byte	-67
	.byte	-66
	.byte	-65
	.byte	-64
	.byte	-63
	.byte	-62
	.byte	-61
	.byte	-60
	.byte	-59
	.byte	-58
	.byte	-57
	.byte	-56
	.byte	-54
	.byte	-53
	.byte	-52
	.byte	-51
	.byte	-50
	.byte	-49
	.byte	-48
	.byte	-47
	.byte	-46
	.byte	-45
	.byte	-44
	.byte	-43
	.byte	-41
	.byte	-40
	.byte	-39
	.byte	-38
	.byte	-37
	.byte	-36
	.byte	-35
	.byte	-34
	.byte	-33
	.byte	-32
	.byte	-31
	.byte	-30
	.byte	-28
	.byte	-27
	.byte	-26
	.byte	-25
	.byte	-24
	.byte	-23
	.byte	-22
	.byte	-21
	.byte	-20
	.byte	-19
	.byte	-18
	.byte	-17
	.byte	-15
	.byte	-14
	.byte	-13
	.byte	-12
	.byte	-11
	.byte	-10
	.byte	-9
	.byte	-8
	.byte	-7
	.byte	-6
	.byte	-5
	.byte	-4
	.zero	2
	.type	count_to_update_factor, %object
	.size	count_to_update_factor, 21
count_to_update_factor:
	.byte	0
	.byte	6
	.byte	12
	.byte	19
	.byte	25
	.byte	32
	.byte	38
	.byte	44
	.byte	51
	.byte	57
	.byte	64
	.byte	70
	.byte	76
	.byte	83
	.byte	89
	.byte	96
	.byte	102
	.byte	108
	.byte	115
	.byte	121
	.byte	-128
	.zero	3
	.type	__func__.11823, %object
	.size	__func__.11823, 19
__func__.11823:
	.string	"VP9_GetImageBuffer"
	.zero	5
	.type	seg_feature_data_max, %object
	.size	seg_feature_data_max, 16
seg_feature_data_max:
	.word	255
	.word	63
	.word	3
	.word	0
	.type	seg_feature_data_signed, %object
	.size	seg_feature_data_signed, 16
seg_feature_data_signed:
	.word	1
	.word	1
	.word	0
	.word	0
	.type	__func__.11999, %object
	.size	__func__.11999, 16
__func__.11999:
	.string	"VP9_Set_Segdata"
	.type	__FUNCTION__.12075, %object
	.size	__FUNCTION__.12075, 33
__FUNCTION__.12075:
	.string	"VP9_get_fixed_point_scale_factor"
	.zero	7
	.type	__FUNCTION__.12104, %object
	.size	__FUNCTION__.12104, 35
__FUNCTION__.12104:
	.string	"Vp9_ReadBitDepthColorSpaceSampling"
	.zero	5
	.type	__FUNCTION__.12134, %object
	.size	__FUNCTION__.12134, 25
__FUNCTION__.12134:
	.string	"Read_UnCompressed_Header"
	.zero	7
	.type	vp9_default_tx_probs, %object
	.size	vp9_default_tx_probs, 12
vp9_default_tx_probs:
	.byte	100
	.byte	66
	.byte	20
	.byte	-104
	.byte	15
	.byte	101
	.byte	3
	.byte	-120
	.byte	37
	.byte	5
	.byte	52
	.byte	13
	.type	vp9_default_nmv_context, %object
	.size	vp9_default_nmv_context, 69
vp9_default_nmv_context:
	.byte	-128
	.byte	-128
	.byte	32
	.byte	64
	.byte	96
	.byte	-32
	.byte	-112
	.byte	-64
	.byte	-88
	.byte	-64
	.byte	-80
	.byte	-64
	.byte	-58
	.byte	-58
	.byte	-11
	.byte	-40
	.byte	-128
	.byte	-80
	.byte	-96
	.byte	-80
	.byte	-80
	.byte	-64
	.byte	-58
	.byte	-58
	.byte	-48
	.byte	-40
	.byte	-48
	.byte	-120
	.byte	-116
	.byte	-108
	.byte	-96
	.byte	-80
	.byte	-64
	.byte	-32
	.byte	-22
	.byte	-22
	.byte	-16
	.byte	-120
	.byte	-116
	.byte	-108
	.byte	-96
	.byte	-80
	.byte	-64
	.byte	-32
	.byte	-22
	.byte	-22
	.byte	-16
	.byte	-128
	.byte	-128
	.byte	64
	.byte	96
	.byte	112
	.byte	64
	.byte	-128
	.byte	-128
	.byte	64
	.byte	96
	.byte	112
	.byte	64
	.byte	64
	.byte	96
	.byte	64
	.byte	64
	.byte	96
	.byte	64
	.byte	-96
	.byte	-96
	.byte	-128
	.byte	-128
	.zero	7
	.type	__func__.12355, %object
	.size	__func__.12355, 20
__func__.12355:
	.string	"Vp9_DecodeTilesCtrl"
	.zero	4
	.type	__func__.12214, %object
	.size	__func__.12214, 18
__func__.12214:
	.string	"VP9DEC_DecodeFame"
	.data
	.align	3
.LANCHOR1 = . + 0
.LANCHOR2 = . + 4352
	.type	vp9_default_coef_probs_4x4, %object
	.size	vp9_default_coef_probs_4x4, 1024
vp9_default_coef_probs_4x4:
	.byte	-61
	.byte	29
	.byte	-73
	.zero	1
	.byte	84
	.byte	49
	.byte	-120
	.zero	1
	.byte	8
	.byte	42
	.byte	71
	.zero	1
	.zero	20
	.byte	31
	.byte	107
	.byte	-87
	.zero	1
	.byte	35
	.byte	99
	.byte	-97
	.zero	1
	.byte	17
	.byte	82
	.byte	-116
	.zero	1
	.byte	8
	.byte	66
	.byte	114
	.zero	1
	.byte	2
	.byte	44
	.byte	76
	.zero	1
	.byte	1
	.byte	19
	.byte	32
	.zero	1
	.zero	8
	.byte	40
	.byte	-124
	.byte	-55
	.zero	1
	.byte	29
	.byte	114
	.byte	-69
	.zero	1
	.byte	13
	.byte	91
	.byte	-99
	.zero	1
	.byte	7
	.byte	75
	.byte	127
	.zero	1
	.byte	3
	.byte	58
	.byte	95
	.zero	1
	.byte	1
	.byte	28
	.byte	47
	.zero	1
	.zero	8
	.byte	69
	.byte	-114
	.byte	-35
	.zero	1
	.byte	42
	.byte	122
	.byte	-55
	.zero	1
	.byte	15
	.byte	91
	.byte	-97
	.zero	1
	.byte	6
	.byte	67
	.byte	121
	.zero	1
	.byte	1
	.byte	42
	.byte	77
	.zero	1
	.byte	1
	.byte	17
	.byte	31
	.zero	1
	.zero	8
	.byte	102
	.byte	-108
	.byte	-28
	.zero	1
	.byte	67
	.byte	117
	.byte	-52
	.zero	1
	.byte	17
	.byte	82
	.byte	-102
	.zero	1
	.byte	6
	.byte	59
	.byte	114
	.zero	1
	.byte	2
	.byte	39
	.byte	75
	.zero	1
	.byte	1
	.byte	15
	.byte	29
	.zero	1
	.zero	8
	.byte	-100
	.byte	57
	.byte	-23
	.zero	1
	.byte	119
	.byte	57
	.byte	-44
	.zero	1
	.byte	58
	.byte	48
	.byte	-93
	.zero	1
	.byte	29
	.byte	40
	.byte	124
	.zero	1
	.byte	12
	.byte	30
	.byte	81
	.zero	1
	.byte	3
	.byte	12
	.byte	31
	.zero	1
	.zero	8
	.zero	64
	.byte	-65
	.byte	107
	.byte	-30
	.zero	1
	.byte	124
	.byte	117
	.byte	-52
	.zero	1
	.byte	25
	.byte	99
	.byte	-101
	.zero	1
	.zero	20
	.byte	29
	.byte	-108
	.byte	-46
	.zero	1
	.byte	37
	.byte	126
	.byte	-62
	.zero	1
	.byte	8
	.byte	93
	.byte	-99
	.zero	1
	.byte	2
	.byte	68
	.byte	118
	.zero	1
	.byte	1
	.byte	39
	.byte	69
	.zero	1
	.byte	1
	.byte	17
	.byte	33
	.zero	1
	.zero	8
	.byte	41
	.byte	-105
	.byte	-43
	.zero	1
	.byte	27
	.byte	123
	.byte	-63
	.zero	1
	.byte	3
	.byte	82
	.byte	-112
	.zero	1
	.byte	1
	.byte	58
	.byte	105
	.zero	1
	.byte	1
	.byte	32
	.byte	60
	.zero	1
	.byte	1
	.byte	13
	.byte	26
	.zero	1
	.zero	8
	.byte	59
	.byte	-97
	.byte	-36
	.zero	1
	.byte	23
	.byte	126
	.byte	-58
	.zero	1
	.byte	4
	.byte	88
	.byte	-105
	.zero	1
	.byte	1
	.byte	66
	.byte	114
	.zero	1
	.byte	1
	.byte	38
	.byte	71
	.zero	1
	.byte	1
	.byte	18
	.byte	34
	.zero	1
	.zero	8
	.byte	114
	.byte	-120
	.byte	-24
	.zero	1
	.byte	51
	.byte	114
	.byte	-49
	.zero	1
	.byte	11
	.byte	83
	.byte	-101
	.zero	1
	.byte	3
	.byte	56
	.byte	105
	.zero	1
	.byte	1
	.byte	33
	.byte	65
	.zero	1
	.byte	1
	.byte	17
	.byte	34
	.zero	1
	.zero	8
	.byte	-107
	.byte	65
	.byte	-22
	.zero	1
	.byte	121
	.byte	57
	.byte	-41
	.zero	1
	.byte	61
	.byte	49
	.byte	-90
	.zero	1
	.byte	28
	.byte	36
	.byte	114
	.zero	1
	.byte	12
	.byte	25
	.byte	76
	.zero	1
	.byte	3
	.byte	16
	.byte	42
	.zero	1
	.zero	8
	.zero	64
	.byte	-42
	.byte	49
	.byte	-36
	.zero	1
	.byte	-124
	.byte	63
	.byte	-68
	.zero	1
	.byte	42
	.byte	65
	.byte	-119
	.zero	1
	.zero	20
	.byte	85
	.byte	-119
	.byte	-35
	.zero	1
	.byte	104
	.byte	-125
	.byte	-40
	.zero	1
	.byte	49
	.byte	111
	.byte	-64
	.zero	1
	.byte	21
	.byte	87
	.byte	-101
	.zero	1
	.byte	2
	.byte	49
	.byte	87
	.zero	1
	.byte	1
	.byte	16
	.byte	28
	.zero	1
	.zero	8
	.byte	89
	.byte	-93
	.byte	-26
	.zero	1
	.byte	90
	.byte	-119
	.byte	-36
	.zero	1
	.byte	29
	.byte	100
	.byte	-73
	.zero	1
	.byte	10
	.byte	70
	.byte	-121
	.zero	1
	.byte	2
	.byte	42
	.byte	81
	.zero	1
	.byte	1
	.byte	17
	.byte	33
	.zero	1
	.zero	8
	.byte	108
	.byte	-89
	.byte	-19
	.zero	1
	.byte	55
	.byte	-123
	.byte	-34
	.zero	1
	.byte	15
	.byte	97
	.byte	-77
	.zero	1
	.byte	4
	.byte	72
	.byte	-121
	.zero	1
	.byte	1
	.byte	45
	.byte	85
	.zero	1
	.byte	1
	.byte	19
	.byte	38
	.zero	1
	.zero	8
	.byte	124
	.byte	-110
	.byte	-16
	.zero	1
	.byte	66
	.byte	124
	.byte	-32
	.zero	1
	.byte	17
	.byte	88
	.byte	-81
	.zero	1
	.byte	4
	.byte	58
	.byte	122
	.zero	1
	.byte	1
	.byte	36
	.byte	75
	.zero	1
	.byte	1
	.byte	18
	.byte	37
	.zero	1
	.zero	8
	.byte	-115
	.byte	79
	.byte	-15
	.zero	1
	.byte	126
	.byte	70
	.byte	-29
	.zero	1
	.byte	66
	.byte	58
	.byte	-74
	.zero	1
	.byte	30
	.byte	44
	.byte	-120
	.zero	1
	.byte	12
	.byte	34
	.byte	96
	.zero	1
	.byte	2
	.byte	20
	.byte	47
	.zero	1
	.zero	8
	.zero	64
	.byte	-27
	.byte	99
	.byte	-7
	.zero	1
	.byte	-113
	.byte	111
	.byte	-21
	.zero	1
	.byte	46
	.byte	109
	.byte	-64
	.zero	1
	.zero	20
	.byte	82
	.byte	-98
	.byte	-20
	.zero	1
	.byte	94
	.byte	-110
	.byte	-32
	.zero	1
	.byte	25
	.byte	117
	.byte	-65
	.zero	1
	.byte	9
	.byte	87
	.byte	-107
	.zero	1
	.byte	3
	.byte	56
	.byte	99
	.zero	1
	.byte	1
	.byte	33
	.byte	57
	.zero	1
	.zero	8
	.byte	83
	.byte	-89
	.byte	-19
	.zero	1
	.byte	68
	.byte	-111
	.byte	-34
	.zero	1
	.byte	10
	.byte	103
	.byte	-79
	.zero	1
	.byte	2
	.byte	72
	.byte	-125
	.zero	1
	.byte	1
	.byte	41
	.byte	79
	.zero	1
	.byte	1
	.byte	20
	.byte	39
	.zero	1
	.zero	8
	.byte	99
	.byte	-89
	.byte	-17
	.zero	1
	.byte	47
	.byte	-115
	.byte	-32
	.zero	1
	.byte	10
	.byte	104
	.byte	-78
	.zero	1
	.byte	2
	.byte	73
	.byte	-123
	.zero	1
	.byte	1
	.byte	44
	.byte	85
	.zero	1
	.byte	1
	.byte	22
	.byte	47
	.zero	1
	.zero	8
	.byte	127
	.byte	-111
	.byte	-13
	.zero	1
	.byte	71
	.byte	-127
	.byte	-28
	.zero	1
	.byte	17
	.byte	93
	.byte	-79
	.zero	1
	.byte	3
	.byte	61
	.byte	124
	.zero	1
	.byte	1
	.byte	41
	.byte	84
	.zero	1
	.byte	1
	.byte	21
	.byte	52
	.zero	1
	.zero	8
	.byte	-99
	.byte	78
	.byte	-12
	.zero	1
	.byte	-116
	.byte	72
	.byte	-25
	.zero	1
	.byte	69
	.byte	58
	.byte	-72
	.zero	1
	.byte	31
	.byte	44
	.byte	-119
	.zero	1
	.byte	14
	.byte	38
	.byte	105
	.zero	1
	.byte	8
	.byte	23
	.byte	61
	.zero	1
	.zero	8
	.zero	64
	.type	vp9_default_coef_probs_8x8, %object
	.size	vp9_default_coef_probs_8x8, 1024
vp9_default_coef_probs_8x8:
	.byte	125
	.byte	34
	.byte	-69
	.zero	1
	.byte	52
	.byte	41
	.byte	-123
	.zero	1
	.byte	6
	.byte	31
	.byte	56
	.zero	1
	.zero	20
	.byte	37
	.byte	109
	.byte	-103
	.zero	1
	.byte	51
	.byte	102
	.byte	-109
	.zero	1
	.byte	23
	.byte	87
	.byte	-128
	.zero	1
	.byte	8
	.byte	67
	.byte	101
	.zero	1
	.byte	1
	.byte	41
	.byte	63
	.zero	1
	.byte	1
	.byte	19
	.byte	29
	.zero	1
	.zero	8
	.byte	31
	.byte	-102
	.byte	-71
	.zero	1
	.byte	17
	.byte	127
	.byte	-81
	.zero	1
	.byte	6
	.byte	96
	.byte	-111
	.zero	1
	.byte	2
	.byte	73
	.byte	114
	.zero	1
	.byte	1
	.byte	51
	.byte	82
	.zero	1
	.byte	1
	.byte	28
	.byte	45
	.zero	1
	.zero	8
	.byte	23
	.byte	-93
	.byte	-56
	.zero	1
	.byte	10
	.byte	-125
	.byte	-71
	.zero	1
	.byte	2
	.byte	93
	.byte	-108
	.zero	1
	.byte	1
	.byte	67
	.byte	111
	.zero	1
	.byte	1
	.byte	41
	.byte	69
	.zero	1
	.byte	1
	.byte	14
	.byte	24
	.zero	1
	.zero	8
	.byte	29
	.byte	-80
	.byte	-39
	.zero	1
	.byte	12
	.byte	-111
	.byte	-55
	.zero	1
	.byte	3
	.byte	101
	.byte	-100
	.zero	1
	.byte	1
	.byte	69
	.byte	111
	.zero	1
	.byte	1
	.byte	39
	.byte	63
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.byte	57
	.byte	-64
	.byte	-23
	.zero	1
	.byte	25
	.byte	-102
	.byte	-41
	.zero	1
	.byte	6
	.byte	109
	.byte	-89
	.zero	1
	.byte	3
	.byte	78
	.byte	118
	.zero	1
	.byte	1
	.byte	48
	.byte	69
	.zero	1
	.byte	1
	.byte	21
	.byte	29
	.zero	1
	.zero	8
	.zero	64
	.byte	-54
	.byte	105
	.byte	-11
	.zero	1
	.byte	108
	.byte	106
	.byte	-40
	.zero	1
	.byte	18
	.byte	90
	.byte	-112
	.zero	1
	.zero	20
	.byte	33
	.byte	-84
	.byte	-37
	.zero	1
	.byte	64
	.byte	-107
	.byte	-50
	.zero	1
	.byte	14
	.byte	117
	.byte	-79
	.zero	1
	.byte	5
	.byte	90
	.byte	-115
	.zero	1
	.byte	2
	.byte	61
	.byte	95
	.zero	1
	.byte	1
	.byte	37
	.byte	57
	.zero	1
	.zero	8
	.byte	33
	.byte	-77
	.byte	-36
	.zero	1
	.byte	11
	.byte	-116
	.byte	-58
	.zero	1
	.byte	1
	.byte	89
	.byte	-108
	.zero	1
	.byte	1
	.byte	60
	.byte	104
	.zero	1
	.byte	1
	.byte	33
	.byte	57
	.zero	1
	.byte	1
	.byte	12
	.byte	21
	.zero	1
	.zero	8
	.byte	30
	.byte	-75
	.byte	-35
	.zero	1
	.byte	8
	.byte	-115
	.byte	-58
	.zero	1
	.byte	1
	.byte	87
	.byte	-111
	.zero	1
	.byte	1
	.byte	58
	.byte	100
	.zero	1
	.byte	1
	.byte	31
	.byte	55
	.zero	1
	.byte	1
	.byte	12
	.byte	20
	.zero	1
	.zero	8
	.byte	32
	.byte	-70
	.byte	-32
	.zero	1
	.byte	7
	.byte	-114
	.byte	-58
	.zero	1
	.byte	1
	.byte	86
	.byte	-113
	.zero	1
	.byte	1
	.byte	58
	.byte	100
	.zero	1
	.byte	1
	.byte	31
	.byte	55
	.zero	1
	.byte	1
	.byte	12
	.byte	22
	.zero	1
	.zero	8
	.byte	57
	.byte	-64
	.byte	-29
	.zero	1
	.byte	20
	.byte	-113
	.byte	-52
	.zero	1
	.byte	3
	.byte	96
	.byte	-102
	.zero	1
	.byte	1
	.byte	68
	.byte	112
	.zero	1
	.byte	1
	.byte	42
	.byte	69
	.zero	1
	.byte	1
	.byte	19
	.byte	32
	.zero	1
	.zero	8
	.zero	64
	.byte	-44
	.byte	35
	.byte	-41
	.zero	1
	.byte	113
	.byte	47
	.byte	-87
	.zero	1
	.byte	29
	.byte	48
	.byte	105
	.zero	1
	.zero	20
	.byte	74
	.byte	-127
	.byte	-53
	.zero	1
	.byte	106
	.byte	120
	.byte	-53
	.zero	1
	.byte	49
	.byte	107
	.byte	-78
	.zero	1
	.byte	19
	.byte	84
	.byte	-112
	.zero	1
	.byte	4
	.byte	50
	.byte	84
	.zero	1
	.byte	1
	.byte	15
	.byte	25
	.zero	1
	.zero	8
	.byte	71
	.byte	-84
	.byte	-39
	.zero	1
	.byte	44
	.byte	-115
	.byte	-47
	.zero	1
	.byte	15
	.byte	102
	.byte	-83
	.zero	1
	.byte	6
	.byte	76
	.byte	-123
	.zero	1
	.byte	2
	.byte	51
	.byte	89
	.zero	1
	.byte	1
	.byte	24
	.byte	42
	.zero	1
	.zero	8
	.byte	64
	.byte	-71
	.byte	-25
	.zero	1
	.byte	31
	.byte	-108
	.byte	-40
	.zero	1
	.byte	8
	.byte	103
	.byte	-81
	.zero	1
	.byte	3
	.byte	74
	.byte	-125
	.zero	1
	.byte	1
	.byte	46
	.byte	81
	.zero	1
	.byte	1
	.byte	18
	.byte	30
	.zero	1
	.zero	8
	.byte	65
	.byte	-60
	.byte	-21
	.zero	1
	.byte	25
	.byte	-99
	.byte	-35
	.zero	1
	.byte	5
	.byte	105
	.byte	-82
	.zero	1
	.byte	1
	.byte	67
	.byte	120
	.zero	1
	.byte	1
	.byte	38
	.byte	69
	.zero	1
	.byte	1
	.byte	15
	.byte	30
	.zero	1
	.zero	8
	.byte	65
	.byte	-52
	.byte	-18
	.zero	1
	.byte	30
	.byte	-100
	.byte	-32
	.zero	1
	.byte	7
	.byte	107
	.byte	-79
	.zero	1
	.byte	2
	.byte	70
	.byte	124
	.zero	1
	.byte	1
	.byte	42
	.byte	73
	.zero	1
	.byte	1
	.byte	18
	.byte	34
	.zero	1
	.zero	8
	.zero	64
	.byte	-31
	.byte	86
	.byte	-5
	.zero	1
	.byte	-112
	.byte	104
	.byte	-21
	.zero	1
	.byte	42
	.byte	99
	.byte	-75
	.zero	1
	.zero	20
	.byte	85
	.byte	-81
	.byte	-17
	.zero	1
	.byte	112
	.byte	-91
	.byte	-27
	.zero	1
	.byte	29
	.byte	-120
	.byte	-56
	.zero	1
	.byte	12
	.byte	103
	.byte	-94
	.zero	1
	.byte	6
	.byte	77
	.byte	123
	.zero	1
	.byte	2
	.byte	53
	.byte	84
	.zero	1
	.zero	8
	.byte	75
	.byte	-73
	.byte	-17
	.zero	1
	.byte	30
	.byte	-101
	.byte	-35
	.zero	1
	.byte	3
	.byte	106
	.byte	-85
	.zero	1
	.byte	1
	.byte	74
	.byte	-128
	.zero	1
	.byte	1
	.byte	44
	.byte	76
	.zero	1
	.byte	1
	.byte	17
	.byte	28
	.zero	1
	.zero	8
	.byte	73
	.byte	-71
	.byte	-16
	.zero	1
	.byte	27
	.byte	-97
	.byte	-34
	.zero	1
	.byte	2
	.byte	107
	.byte	-84
	.zero	1
	.byte	1
	.byte	75
	.byte	127
	.zero	1
	.byte	1
	.byte	42
	.byte	73
	.zero	1
	.byte	1
	.byte	17
	.byte	29
	.zero	1
	.zero	8
	.byte	62
	.byte	-66
	.byte	-18
	.zero	1
	.byte	21
	.byte	-97
	.byte	-34
	.zero	1
	.byte	2
	.byte	107
	.byte	-84
	.zero	1
	.byte	1
	.byte	72
	.byte	122
	.zero	1
	.byte	1
	.byte	40
	.byte	71
	.zero	1
	.byte	1
	.byte	18
	.byte	32
	.zero	1
	.zero	8
	.byte	61
	.byte	-57
	.byte	-16
	.zero	1
	.byte	27
	.byte	-95
	.byte	-30
	.zero	1
	.byte	4
	.byte	113
	.byte	-76
	.zero	1
	.byte	1
	.byte	76
	.byte	-127
	.zero	1
	.byte	1
	.byte	46
	.byte	80
	.zero	1
	.byte	1
	.byte	23
	.byte	41
	.zero	1
	.zero	8
	.zero	64
	.type	vp9_default_coef_probs_16x16, %object
	.size	vp9_default_coef_probs_16x16, 1024
vp9_default_coef_probs_16x16:
	.byte	7
	.byte	27
	.byte	-103
	.zero	1
	.byte	5
	.byte	30
	.byte	95
	.zero	1
	.byte	1
	.byte	16
	.byte	30
	.zero	1
	.zero	20
	.byte	50
	.byte	75
	.byte	127
	.zero	1
	.byte	57
	.byte	75
	.byte	124
	.zero	1
	.byte	27
	.byte	67
	.byte	108
	.zero	1
	.byte	10
	.byte	54
	.byte	86
	.zero	1
	.byte	1
	.byte	33
	.byte	52
	.zero	1
	.byte	1
	.byte	12
	.byte	18
	.zero	1
	.zero	8
	.byte	43
	.byte	125
	.byte	-105
	.zero	1
	.byte	26
	.byte	108
	.byte	-108
	.zero	1
	.byte	7
	.byte	83
	.byte	122
	.zero	1
	.byte	2
	.byte	59
	.byte	89
	.zero	1
	.byte	1
	.byte	38
	.byte	60
	.zero	1
	.byte	1
	.byte	17
	.byte	27
	.zero	1
	.zero	8
	.byte	23
	.byte	-112
	.byte	-93
	.zero	1
	.byte	13
	.byte	112
	.byte	-102
	.zero	1
	.byte	2
	.byte	75
	.byte	117
	.zero	1
	.byte	1
	.byte	50
	.byte	81
	.zero	1
	.byte	1
	.byte	31
	.byte	51
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.byte	18
	.byte	-94
	.byte	-71
	.zero	1
	.byte	6
	.byte	123
	.byte	-85
	.zero	1
	.byte	1
	.byte	78
	.byte	125
	.zero	1
	.byte	1
	.byte	51
	.byte	86
	.zero	1
	.byte	1
	.byte	31
	.byte	54
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.byte	15
	.byte	-57
	.byte	-29
	.zero	1
	.byte	3
	.byte	-106
	.byte	-52
	.zero	1
	.byte	1
	.byte	91
	.byte	-110
	.zero	1
	.byte	1
	.byte	55
	.byte	95
	.zero	1
	.byte	1
	.byte	30
	.byte	53
	.zero	1
	.byte	1
	.byte	11
	.byte	20
	.zero	1
	.zero	8
	.zero	64
	.byte	19
	.byte	55
	.byte	-16
	.zero	1
	.byte	19
	.byte	59
	.byte	-60
	.zero	1
	.byte	3
	.byte	52
	.byte	105
	.zero	1
	.zero	20
	.byte	41
	.byte	-90
	.byte	-49
	.zero	1
	.byte	104
	.byte	-103
	.byte	-57
	.zero	1
	.byte	31
	.byte	123
	.byte	-75
	.zero	1
	.byte	14
	.byte	101
	.byte	-104
	.zero	1
	.byte	5
	.byte	72
	.byte	106
	.zero	1
	.byte	1
	.byte	36
	.byte	52
	.zero	1
	.zero	8
	.byte	35
	.byte	-80
	.byte	-45
	.zero	1
	.byte	12
	.byte	-125
	.byte	-66
	.zero	1
	.byte	2
	.byte	88
	.byte	-112
	.zero	1
	.byte	1
	.byte	60
	.byte	101
	.zero	1
	.byte	1
	.byte	36
	.byte	60
	.zero	1
	.byte	1
	.byte	16
	.byte	28
	.zero	1
	.zero	8
	.byte	28
	.byte	-73
	.byte	-43
	.zero	1
	.byte	8
	.byte	-122
	.byte	-65
	.zero	1
	.byte	1
	.byte	86
	.byte	-114
	.zero	1
	.byte	1
	.byte	56
	.byte	96
	.zero	1
	.byte	1
	.byte	30
	.byte	53
	.zero	1
	.byte	1
	.byte	12
	.byte	20
	.zero	1
	.zero	8
	.byte	20
	.byte	-66
	.byte	-41
	.zero	1
	.byte	4
	.byte	-121
	.byte	-64
	.zero	1
	.byte	1
	.byte	84
	.byte	-117
	.zero	1
	.byte	1
	.byte	53
	.byte	91
	.zero	1
	.byte	1
	.byte	28
	.byte	49
	.zero	1
	.byte	1
	.byte	11
	.byte	20
	.zero	1
	.zero	8
	.byte	13
	.byte	-60
	.byte	-40
	.zero	1
	.byte	2
	.byte	-119
	.byte	-64
	.zero	1
	.byte	1
	.byte	86
	.byte	-113
	.zero	1
	.byte	1
	.byte	57
	.byte	99
	.zero	1
	.byte	1
	.byte	32
	.byte	56
	.zero	1
	.byte	1
	.byte	13
	.byte	24
	.zero	1
	.zero	8
	.zero	64
	.byte	-45
	.byte	29
	.byte	-39
	.zero	1
	.byte	96
	.byte	47
	.byte	-100
	.zero	1
	.byte	22
	.byte	43
	.byte	87
	.zero	1
	.zero	20
	.byte	78
	.byte	120
	.byte	-63
	.zero	1
	.byte	111
	.byte	116
	.byte	-70
	.zero	1
	.byte	46
	.byte	102
	.byte	-92
	.zero	1
	.byte	15
	.byte	80
	.byte	-128
	.zero	1
	.byte	2
	.byte	49
	.byte	76
	.zero	1
	.byte	1
	.byte	18
	.byte	28
	.zero	1
	.zero	8
	.byte	71
	.byte	-95
	.byte	-53
	.zero	1
	.byte	42
	.byte	-124
	.byte	-64
	.zero	1
	.byte	10
	.byte	98
	.byte	-106
	.zero	1
	.byte	3
	.byte	69
	.byte	109
	.zero	1
	.byte	1
	.byte	44
	.byte	70
	.zero	1
	.byte	1
	.byte	18
	.byte	29
	.zero	1
	.zero	8
	.byte	57
	.byte	-70
	.byte	-45
	.zero	1
	.byte	30
	.byte	-116
	.byte	-60
	.zero	1
	.byte	4
	.byte	93
	.byte	-110
	.zero	1
	.byte	1
	.byte	62
	.byte	102
	.zero	1
	.byte	1
	.byte	38
	.byte	65
	.zero	1
	.byte	1
	.byte	16
	.byte	27
	.zero	1
	.zero	8
	.byte	47
	.byte	-57
	.byte	-39
	.zero	1
	.byte	14
	.byte	-111
	.byte	-60
	.zero	1
	.byte	1
	.byte	88
	.byte	-114
	.zero	1
	.byte	1
	.byte	57
	.byte	98
	.zero	1
	.byte	1
	.byte	36
	.byte	62
	.zero	1
	.byte	1
	.byte	15
	.byte	26
	.zero	1
	.zero	8
	.byte	26
	.byte	-37
	.byte	-27
	.zero	1
	.byte	5
	.byte	-101
	.byte	-49
	.zero	1
	.byte	1
	.byte	94
	.byte	-105
	.zero	1
	.byte	1
	.byte	60
	.byte	104
	.zero	1
	.byte	1
	.byte	36
	.byte	62
	.zero	1
	.byte	1
	.byte	16
	.byte	28
	.zero	1
	.zero	8
	.zero	64
	.byte	-23
	.byte	29
	.byte	-8
	.zero	1
	.byte	-110
	.byte	47
	.byte	-36
	.zero	1
	.byte	43
	.byte	52
	.byte	-116
	.zero	1
	.zero	20
	.byte	100
	.byte	-93
	.byte	-24
	.zero	1
	.byte	-77
	.byte	-95
	.byte	-34
	.zero	1
	.byte	63
	.byte	-114
	.byte	-52
	.zero	1
	.byte	37
	.byte	113
	.byte	-82
	.zero	1
	.byte	26
	.byte	89
	.byte	-119
	.zero	1
	.byte	18
	.byte	68
	.byte	97
	.zero	1
	.zero	8
	.byte	85
	.byte	-75
	.byte	-26
	.zero	1
	.byte	32
	.byte	-110
	.byte	-47
	.zero	1
	.byte	7
	.byte	100
	.byte	-92
	.zero	1
	.byte	3
	.byte	71
	.byte	121
	.zero	1
	.byte	1
	.byte	45
	.byte	77
	.zero	1
	.byte	1
	.byte	18
	.byte	30
	.zero	1
	.zero	8
	.byte	65
	.byte	-69
	.byte	-26
	.zero	1
	.byte	20
	.byte	-108
	.byte	-49
	.zero	1
	.byte	2
	.byte	97
	.byte	-97
	.zero	1
	.byte	1
	.byte	68
	.byte	116
	.zero	1
	.byte	1
	.byte	40
	.byte	70
	.zero	1
	.byte	1
	.byte	14
	.byte	29
	.zero	1
	.zero	8
	.byte	40
	.byte	-62
	.byte	-29
	.zero	1
	.byte	8
	.byte	-109
	.byte	-52
	.zero	1
	.byte	1
	.byte	94
	.byte	-101
	.zero	1
	.byte	1
	.byte	65
	.byte	112
	.zero	1
	.byte	1
	.byte	39
	.byte	66
	.zero	1
	.byte	1
	.byte	14
	.byte	26
	.zero	1
	.zero	8
	.byte	16
	.byte	-48
	.byte	-28
	.zero	1
	.byte	3
	.byte	-105
	.byte	-49
	.zero	1
	.byte	1
	.byte	98
	.byte	-96
	.zero	1
	.byte	1
	.byte	67
	.byte	117
	.zero	1
	.byte	1
	.byte	41
	.byte	74
	.zero	1
	.byte	1
	.byte	17
	.byte	31
	.zero	1
	.zero	8
	.zero	64
	.type	vp9_default_coef_probs_32x32, %object
	.size	vp9_default_coef_probs_32x32, 1024
vp9_default_coef_probs_32x32:
	.byte	17
	.byte	38
	.byte	-116
	.zero	1
	.byte	7
	.byte	34
	.byte	80
	.zero	1
	.byte	1
	.byte	17
	.byte	29
	.zero	1
	.zero	20
	.byte	37
	.byte	75
	.byte	-128
	.zero	1
	.byte	41
	.byte	76
	.byte	-128
	.zero	1
	.byte	26
	.byte	66
	.byte	116
	.zero	1
	.byte	12
	.byte	52
	.byte	94
	.zero	1
	.byte	2
	.byte	32
	.byte	55
	.zero	1
	.byte	1
	.byte	10
	.byte	16
	.zero	1
	.zero	8
	.byte	50
	.byte	127
	.byte	-102
	.zero	1
	.byte	37
	.byte	109
	.byte	-104
	.zero	1
	.byte	16
	.byte	82
	.byte	121
	.zero	1
	.byte	5
	.byte	59
	.byte	85
	.zero	1
	.byte	1
	.byte	35
	.byte	54
	.zero	1
	.byte	1
	.byte	13
	.byte	20
	.zero	1
	.zero	8
	.byte	40
	.byte	-114
	.byte	-89
	.zero	1
	.byte	17
	.byte	110
	.byte	-99
	.zero	1
	.byte	2
	.byte	71
	.byte	112
	.zero	1
	.byte	1
	.byte	44
	.byte	72
	.zero	1
	.byte	1
	.byte	27
	.byte	45
	.zero	1
	.byte	1
	.byte	11
	.byte	17
	.zero	1
	.zero	8
	.byte	30
	.byte	-81
	.byte	-68
	.zero	1
	.byte	9
	.byte	124
	.byte	-87
	.zero	1
	.byte	1
	.byte	74
	.byte	116
	.zero	1
	.byte	1
	.byte	48
	.byte	78
	.zero	1
	.byte	1
	.byte	30
	.byte	49
	.zero	1
	.byte	1
	.byte	11
	.byte	18
	.zero	1
	.zero	8
	.byte	10
	.byte	-34
	.byte	-33
	.zero	1
	.byte	2
	.byte	-106
	.byte	-62
	.zero	1
	.byte	1
	.byte	83
	.byte	-128
	.zero	1
	.byte	1
	.byte	48
	.byte	79
	.zero	1
	.byte	1
	.byte	27
	.byte	45
	.zero	1
	.byte	1
	.byte	11
	.byte	17
	.zero	1
	.zero	8
	.zero	64
	.byte	36
	.byte	41
	.byte	-21
	.zero	1
	.byte	29
	.byte	36
	.byte	-63
	.zero	1
	.byte	10
	.byte	27
	.byte	111
	.zero	1
	.zero	20
	.byte	85
	.byte	-91
	.byte	-34
	.zero	1
	.byte	-79
	.byte	-94
	.byte	-41
	.zero	1
	.byte	110
	.byte	-121
	.byte	-61
	.zero	1
	.byte	57
	.byte	113
	.byte	-88
	.zero	1
	.byte	23
	.byte	83
	.byte	120
	.zero	1
	.byte	10
	.byte	49
	.byte	61
	.zero	1
	.zero	8
	.byte	85
	.byte	-66
	.byte	-33
	.zero	1
	.byte	36
	.byte	-117
	.byte	-56
	.zero	1
	.byte	5
	.byte	90
	.byte	-110
	.zero	1
	.byte	1
	.byte	60
	.byte	103
	.zero	1
	.byte	1
	.byte	38
	.byte	65
	.zero	1
	.byte	1
	.byte	18
	.byte	30
	.zero	1
	.zero	8
	.byte	72
	.byte	-54
	.byte	-33
	.zero	1
	.byte	23
	.byte	-115
	.byte	-57
	.zero	1
	.byte	2
	.byte	86
	.byte	-116
	.zero	1
	.byte	1
	.byte	56
	.byte	97
	.zero	1
	.byte	1
	.byte	36
	.byte	61
	.zero	1
	.byte	1
	.byte	16
	.byte	27
	.zero	1
	.zero	8
	.byte	55
	.byte	-38
	.byte	-31
	.zero	1
	.byte	13
	.byte	-111
	.byte	-56
	.zero	1
	.byte	1
	.byte	86
	.byte	-115
	.zero	1
	.byte	1
	.byte	57
	.byte	99
	.zero	1
	.byte	1
	.byte	35
	.byte	61
	.zero	1
	.byte	1
	.byte	13
	.byte	22
	.zero	1
	.zero	8
	.byte	15
	.byte	-21
	.byte	-44
	.zero	1
	.byte	1
	.byte	-124
	.byte	-72
	.zero	1
	.byte	1
	.byte	84
	.byte	-117
	.zero	1
	.byte	1
	.byte	57
	.byte	97
	.zero	1
	.byte	1
	.byte	34
	.byte	56
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.zero	64
	.byte	-75
	.byte	21
	.byte	-55
	.zero	1
	.byte	61
	.byte	37
	.byte	123
	.zero	1
	.byte	10
	.byte	38
	.byte	71
	.zero	1
	.zero	20
	.byte	47
	.byte	106
	.byte	-84
	.zero	1
	.byte	95
	.byte	104
	.byte	-83
	.zero	1
	.byte	42
	.byte	93
	.byte	-97
	.zero	1
	.byte	18
	.byte	77
	.byte	-125
	.zero	1
	.byte	4
	.byte	50
	.byte	81
	.zero	1
	.byte	1
	.byte	17
	.byte	23
	.zero	1
	.zero	8
	.byte	62
	.byte	-109
	.byte	-57
	.zero	1
	.byte	44
	.byte	-126
	.byte	-67
	.zero	1
	.byte	28
	.byte	102
	.byte	-102
	.zero	1
	.byte	18
	.byte	75
	.byte	115
	.zero	1
	.byte	2
	.byte	44
	.byte	65
	.zero	1
	.byte	1
	.byte	12
	.byte	19
	.zero	1
	.zero	8
	.byte	55
	.byte	-103
	.byte	-46
	.zero	1
	.byte	24
	.byte	-126
	.byte	-62
	.zero	1
	.byte	3
	.byte	93
	.byte	-110
	.zero	1
	.byte	1
	.byte	61
	.byte	97
	.zero	1
	.byte	1
	.byte	31
	.byte	50
	.zero	1
	.byte	1
	.byte	10
	.byte	16
	.zero	1
	.zero	8
	.byte	49
	.byte	-70
	.byte	-33
	.zero	1
	.byte	17
	.byte	-108
	.byte	-52
	.zero	1
	.byte	1
	.byte	96
	.byte	-114
	.zero	1
	.byte	1
	.byte	53
	.byte	83
	.zero	1
	.byte	1
	.byte	26
	.byte	44
	.zero	1
	.byte	1
	.byte	11
	.byte	17
	.zero	1
	.zero	8
	.byte	13
	.byte	-39
	.byte	-44
	.zero	1
	.byte	2
	.byte	-120
	.byte	-76
	.zero	1
	.byte	1
	.byte	78
	.byte	124
	.zero	1
	.byte	1
	.byte	50
	.byte	83
	.zero	1
	.byte	1
	.byte	29
	.byte	49
	.zero	1
	.byte	1
	.byte	14
	.byte	23
	.zero	1
	.zero	8
	.zero	64
	.byte	-59
	.byte	13
	.byte	-9
	.zero	1
	.byte	82
	.byte	17
	.byte	-34
	.zero	1
	.byte	25
	.byte	17
	.byte	-94
	.zero	1
	.zero	20
	.byte	126
	.byte	-70
	.byte	-9
	.zero	1
	.byte	-22
	.byte	-65
	.byte	-13
	.zero	1
	.byte	-80
	.byte	-79
	.byte	-22
	.zero	1
	.byte	104
	.byte	-98
	.byte	-36
	.zero	1
	.byte	66
	.byte	-128
	.byte	-70
	.zero	1
	.byte	55
	.byte	90
	.byte	-119
	.zero	1
	.zero	8
	.byte	111
	.byte	-59
	.byte	-14
	.zero	1
	.byte	46
	.byte	-98
	.byte	-37
	.zero	1
	.byte	9
	.byte	104
	.byte	-85
	.zero	1
	.byte	2
	.byte	65
	.byte	125
	.zero	1
	.byte	1
	.byte	44
	.byte	80
	.zero	1
	.byte	1
	.byte	17
	.byte	91
	.zero	1
	.zero	8
	.byte	104
	.byte	-48
	.byte	-11
	.zero	1
	.byte	39
	.byte	-88
	.byte	-32
	.zero	1
	.byte	3
	.byte	109
	.byte	-94
	.zero	1
	.byte	1
	.byte	79
	.byte	124
	.zero	1
	.byte	1
	.byte	50
	.byte	102
	.zero	1
	.byte	1
	.byte	43
	.byte	102
	.zero	1
	.zero	8
	.byte	84
	.byte	-36
	.byte	-10
	.zero	1
	.byte	31
	.byte	-79
	.byte	-25
	.zero	1
	.byte	2
	.byte	115
	.byte	-76
	.zero	1
	.byte	1
	.byte	79
	.byte	-122
	.zero	1
	.byte	1
	.byte	55
	.byte	77
	.zero	1
	.byte	1
	.byte	60
	.byte	79
	.zero	1
	.zero	8
	.byte	43
	.byte	-13
	.byte	-16
	.zero	1
	.byte	8
	.byte	-76
	.byte	-39
	.zero	1
	.byte	1
	.byte	115
	.byte	-90
	.zero	1
	.byte	1
	.byte	84
	.byte	121
	.zero	1
	.byte	1
	.byte	51
	.byte	67
	.zero	1
	.byte	1
	.byte	16
	.byte	6
	.zero	1
	.zero	8
	.zero	64
	.type	vp9_default_if_uv_probs, %object
	.size	vp9_default_if_uv_probs, 160
vp9_default_if_uv_probs:
	.byte	120
	.byte	7
	.byte	76
	.byte	-80
	.byte	-48
	.byte	126
	.byte	28
	.byte	54
	.byte	103
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	48
	.byte	12
	.byte	-102
	.byte	-101
	.byte	-117
	.byte	90
	.byte	34
	.byte	117
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	67
	.byte	6
	.byte	25
	.byte	-52
	.byte	-13
	.byte	-98
	.byte	13
	.byte	21
	.byte	96
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	97
	.byte	5
	.byte	44
	.byte	-125
	.byte	-80
	.byte	-117
	.byte	48
	.byte	68
	.byte	97
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	83
	.byte	5
	.byte	42
	.byte	-100
	.byte	111
	.byte	-104
	.byte	26
	.byte	49
	.byte	-104
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	80
	.byte	5
	.byte	58
	.byte	-78
	.byte	74
	.byte	83
	.byte	33
	.byte	62
	.byte	-111
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	86
	.byte	5
	.byte	32
	.byte	-102
	.byte	-64
	.byte	-88
	.byte	14
	.byte	22
	.byte	-93
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	85
	.byte	5
	.byte	32
	.byte	-100
	.byte	-40
	.byte	-108
	.byte	19
	.byte	29
	.byte	73
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	77
	.byte	7
	.byte	64
	.byte	116
	.byte	-124
	.byte	122
	.byte	37
	.byte	126
	.byte	120
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	101
	.byte	21
	.byte	107
	.byte	-75
	.byte	-64
	.byte	103
	.byte	19
	.byte	67
	.byte	125
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	vp9_default_if_y_probs, %object
	.size	vp9_default_if_y_probs, 64
vp9_default_if_y_probs:
	.byte	65
	.byte	32
	.byte	18
	.byte	-112
	.byte	-94
	.byte	-62
	.byte	41
	.byte	51
	.byte	98
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-124
	.byte	68
	.byte	18
	.byte	-91
	.byte	-39
	.byte	-60
	.byte	45
	.byte	40
	.byte	78
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-83
	.byte	80
	.byte	19
	.byte	-80
	.byte	-16
	.byte	-63
	.byte	64
	.byte	35
	.byte	46
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-35
	.byte	-121
	.byte	38
	.byte	-62
	.byte	-8
	.byte	121
	.byte	96
	.byte	85
	.byte	29
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	vp9_default_switchable_interp_prob, %object
	.size	vp9_default_switchable_interp_prob, 8
vp9_default_switchable_interp_prob:
	.byte	-21
	.byte	-94
	.byte	36
	.byte	-1
	.byte	34
	.byte	3
	.byte	-107
	.byte	-112
	.type	vp9_default_partition_probs, %object
	.size	vp9_default_partition_probs, 96
vp9_default_partition_probs:
	.byte	-98
	.byte	97
	.byte	94
	.byte	93
	.byte	24
	.byte	99
	.byte	85
	.byte	119
	.byte	44
	.byte	62
	.byte	59
	.byte	67
	.byte	-107
	.byte	53
	.byte	53
	.byte	94
	.byte	20
	.byte	48
	.byte	83
	.byte	53
	.byte	24
	.byte	52
	.byte	18
	.byte	18
	.byte	-106
	.byte	40
	.byte	39
	.byte	78
	.byte	12
	.byte	26
	.byte	67
	.byte	33
	.byte	11
	.byte	24
	.byte	7
	.byte	5
	.byte	-82
	.byte	35
	.byte	49
	.byte	68
	.byte	11
	.byte	27
	.byte	57
	.byte	15
	.byte	9
	.byte	12
	.byte	3
	.byte	3
	.byte	-57
	.byte	122
	.byte	-115
	.byte	-109
	.byte	63
	.byte	-97
	.byte	-108
	.byte	-123
	.byte	118
	.byte	121
	.byte	104
	.byte	114
	.byte	-82
	.byte	73
	.byte	87
	.byte	92
	.byte	41
	.byte	83
	.byte	82
	.byte	99
	.byte	50
	.byte	53
	.byte	39
	.byte	39
	.byte	-79
	.byte	58
	.byte	59
	.byte	68
	.byte	26
	.byte	63
	.byte	52
	.byte	79
	.byte	25
	.byte	17
	.byte	14
	.byte	12
	.byte	-34
	.byte	34
	.byte	30
	.byte	72
	.byte	16
	.byte	44
	.byte	58
	.byte	32
	.byte	12
	.byte	10
	.byte	7
	.byte	6
	.type	vp9_default_intra_inter_p, %object
	.size	vp9_default_intra_inter_p, 4
vp9_default_intra_inter_p:
	.byte	9
	.byte	102
	.byte	-69
	.byte	-31
	.zero	4
	.type	vp9_default_comp_inter_p, %object
	.size	vp9_default_comp_inter_p, 5
vp9_default_comp_inter_p:
	.byte	-17
	.byte	-73
	.byte	119
	.byte	96
	.byte	41
	.zero	3
	.type	vp9_default_comp_ref_p, %object
	.size	vp9_default_comp_ref_p, 5
vp9_default_comp_ref_p:
	.byte	50
	.byte	126
	.byte	123
	.byte	-35
	.byte	-30
	.zero	3
	.type	vp9_default_single_ref_p, %object
	.size	vp9_default_single_ref_p, 10
vp9_default_single_ref_p:
	.byte	33
	.byte	16
	.byte	77
	.byte	74
	.byte	-114
	.byte	-114
	.byte	-84
	.byte	-86
	.byte	-18
	.byte	-9
	.zero	6
	.type	vp9_default_mbskip_probs, %object
	.size	vp9_default_mbskip_probs, 3
vp9_default_mbskip_probs:
	.byte	-64
	.byte	-128
	.byte	64
	.zero	1
	.type	vp9_default_inter_mode_probs, %object
	.size	vp9_default_inter_mode_probs, 21
vp9_default_inter_mode_probs:
	.byte	2
	.byte	-83
	.byte	34
	.byte	7
	.byte	-111
	.byte	85
	.byte	7
	.byte	-90
	.byte	63
	.byte	7
	.byte	94
	.byte	66
	.byte	8
	.byte	64
	.byte	46
	.byte	17
	.byte	81
	.byte	31
	.byte	25
	.byte	29
	.byte	30
	.zero	3
	.type	g_CfgVp9FrmNum, %object
	.size	g_CfgVp9FrmNum, 4
g_CfgVp9FrmNum:
	.word	9
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC26:
	ASCII(.string	"IN VP9DEC_Init\n" )
.LC28:
	ASCII(.string	"line: %d,Invalid pointer!\n" )
	.zero	5
.LC31:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC33:
	ASCII(.string	"data_sz == 0\n" )
	.zero	2
.LC35:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC37:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC39:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC41:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC43:
	ASCII(.string	"line: %d, fs is NULL!\n" )
	.zero	1
.LC46:
	ASCII(.string	"%s  idx=%d\n" )
	.zero	4
.LC48:
	ASCII(.string	"FSP_GetLogicFs err" )
	.zero	5
.LC50:
	ASCII(.string	"fsp.c,L%d: %s\n" )
	.zero	1
.LC52:
	ASCII(.string	"line: %d,pCtx is NULL!\n" )
.LC55:
	ASCII(.string	"pCurImg is null\n" )
	.zero	7
.LC58:
	ASCII(.string	"err_level(%d) over ref_thr(%d)\n" )
.LC60:
	ASCII(.string	"line: %d pToQueImg is null\n" )
	.zero	4
.LC62:
	ASCII(.string	"insert img to Voqueue failed!\n" )
	.zero	1
.LC64:
	ASCII(.string	"pu8ProbCntVir == NULL\n" )
	.zero	1
.LC67:
	ASCII(.string	"line: %d, pCtx is NULL!\n" )
	.zero	7
.LC70:
	ASCII(.string	"Invalid frame sync code\n" )
	.zero	7
.LC79:
	ASCII(.string	"%s  %d ERR\n" )
	.zero	4
.LC88:
	ASCII(.string	"%s:%d this_size:%d is invalid!\n" )
.LC93:
	ASCII(.string	"4:4:4 color is not supported in profile 0 or 2 (%s : %d)\n" )
	.zero	6
.LC95:
	ASCII(.string	"Invalid frame marker\n" )
	.zero	2
.LC98:
	ASCII(.string	"%s:%d w&h=%dx%d is invalid!\n" )
	.zero	3
.LC100:
	ASCII(.string	"VP9_Set_DecParam but logic fs is null!\n" )
.LC102:
	ASCII(.string	"Decord FS is NULL!\n" )
	.zero	4
.LC104:
	ASCII(.string	"VP9_Set_DecParam but cur logic pstDecodeFs is null!\n" )
	.zero	3
.LC106:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC108:
	ASCII(.string	"pic_width_in_pix:%d, pic_height_in_pix:%d\n" )
	.zero	5
.LC110:
	ASCII(.string	"vp9 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC114:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC116:
	ASCII(.string	"FSP_ConfigInstance fail!\n" )
	.zero	6
.LC118:
	ASCII(.string	"vp9 alloc frame only\n" )
	.zero	2
.LC140:
	ASCII(.string	"%s:%d size is invalid  size:%d bslen:%d\n" )
	.zero	7
.LC143:
	ASCII(.string	"ERROR:Vp9_ReadCompressedHeader\n" )
.LC145:
	ASCII(.string	"get_free_fb failed!\n" )
	.zero	3
.LC147:
	ASCII(.string	"bit_depth(%d) > 10.\n" )
	.zero	3
.LC150:
	ASCII(.string	"ERROR: pCtx->StreamParam.Length(%d) < 8\n" )
	.zero	7
.LC152:
	ASCII(.string	"widthxheight exceed %d x %d\n" )
	.zero	3
.LC156:
	ASCII(.string	"%dx%d, all=%d,cur=%d,ref=%d,ned=%d\n" )
	.zero	4
.LC158:
	ASCII(.string	"ERROR: No Img buffer is allocated\n" )
	.zero	5
.LC161:
	ASCII(.string	"%s %d, no fsp\n" )
	.zero	1
.LC163:
	ASCII(.string	"VP9_GetImageBuffer From Queue err\n" )
	.zero	5
.LC165:
	ASCII(.string	"ERROR: VP9_Set_DecParam\n" )
	.zero	7
.LC168:
	ASCII(.string	"VP9_DecOneNal ERR\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
