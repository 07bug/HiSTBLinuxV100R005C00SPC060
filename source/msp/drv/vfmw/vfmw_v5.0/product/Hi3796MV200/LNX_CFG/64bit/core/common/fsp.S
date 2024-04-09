#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"fsp.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	FSP_ClearContext, %function
FSP_ClearContext:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L5
	ldr	x20, .LC4
	mov	w0, 8
	add	x21, x19, 24576
	ldr	x1, [x20, 24]
	blr	x1
	strb	wzr, [x19, 2]
	strb	wzr, [x19, 4]
	mov	x2, 20
	strb	wzr, [x19, 5]
	mov	w1, 0
	strb	wzr, [x19, 3]
	add	x0, x19, 36
	stp	wzr, wzr, [x19, 8]
	stp	wzr, wzr, [x19, 16]
	str	wzr, [x19, 24]
	str	wzr, [x19, 32]
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 56
	blr	x3
	ldr	x3, [x20, 96]
	add	x0, x19, 20480
	mov	x2, 2816
	mov	w1, 0
	add	x0, x0, 1680
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 2816
	mov	w1, 0
	add	x0, x21, 400
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 256
	mov	w1, 0
	add	x0, x21, 3216
	blr	x3
	ldr	x1, [x20, 32]
	mov	w0, 8
	blr	x1
	mov	w0, 0
.L3:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L5:
	ldr	x3, .LC1
	mov	w2, 132
	ldr	x1, .LC3
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3
	.size	FSP_ClearContext, .-FSP_ClearContext
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_Init
	.type	FSP_Init, %function
FSP_Init:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC5
	mov	x2, 256
	ldr	x0, .LC6
	mov	w1, 0
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x29, x30, [sp], 16
	ret
	.size	FSP_Init, .-FSP_Init
	.align	3
.LC5:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC6:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ConfigAttribute
	.type	FSP_ConfigAttribute, %function
FSP_ConfigAttribute:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L11
	ldr	x0, .LC10
	ldr	x2, [x0, w19, sxtw 3]
	ldr	w0, [x2, 28]
	cmp	w0, 1
	bne	.L12
	ldrsb	w1, [x20]
	mov	w0, 0
	strb	w1, [x2, 1]
.L9:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L12:
	ldr	x3, .LC12
	mov	w2, 349
	ldr	x1, .LC9
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L9
	.p2align 3
.L11:
	ldr	x3, .LC8
	mov	w2, 348
	ldr	x1, .LC9
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L9
	.size	FSP_ConfigAttribute, .-FSP_ConfigAttribute
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC9:
	.xword	.LC2
	.align	3
.LC10:
	.xword	.LANCHOR0
	.align	3
.LC12:
	.xword	.LC11
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ClearContextAll
	.type	FSP_ClearContextAll, %function
FSP_ClearContextAll:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L17
	ldr	x0, .LC15
	ldr	x19, [x0, w19, sxtw 3]
	cbz	x19, .L18
	ldr	x3, .LC18
	mov	x2, 28048
	mov	w1, 0
	mov	x0, x19
	ldrsb	w22, [x19, 3]
	ldr	x3, [x3, 96]
	ldrsb	w21, [x19, 5]
	ldrsb	w25, [x19]
	ldrsb	w24, [x19, 1]
	ldp	w23, w20, [x19, 28]
	blr	x3
	strb	w25, [x19]
	strb	w24, [x19, 1]
	mov	w0, 0
	strb	w22, [x19, 3]
	strb	w21, [x19, 5]
	stp	w23, w20, [x19, 28]
.L15:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L17:
	ldr	x3, .LC13
	mov	w2, 369
	ldr	x1, .LC14
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L15
.L18:
	ldr	x3, .LC17
	mov	w2, 370
	ldr	x1, .LC14
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L15
	.size	FSP_ClearContextAll, .-FSP_ClearContextAll
	.align	3
.LC13:
	.xword	.LC7
	.align	3
.LC14:
	.xword	.LC2
	.align	3
.LC15:
	.xword	.LANCHOR0
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC18:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_EnableInstance
	.type	FSP_EnableInstance, %function
FSP_EnableInstance:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L23
	ldr	x21, .LC21
	ldr	x0, [x21, w20, sxtw 3]
	cbnz	x0, .L24
	ldr	x3, .LC24
	mov	x2, 28048
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	strb	w20, [x19]
	mov	w0, 1
	stp	w0, wzr, [x19, 28]
	str	x19, [x21, w20, sxtw 3]
	mov	w0, 0
.L21:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L24:
	ldr	x3, .LC23
	mov	w2, 396
	ldr	x1, .LC20
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L23:
	ldr	x3, .LC19
	mov	w2, 395
	ldr	x1, .LC20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L21
	.size	FSP_EnableInstance, .-FSP_EnableInstance
	.align	3
.LC19:
	.xword	.LC7
	.align	3
.LC20:
	.xword	.LC2
	.align	3
.LC21:
	.xword	.LANCHOR0
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC24:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_DisableInstance
	.type	FSP_DisableInstance, %function
FSP_DisableInstance:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L30
	ldr	x1, .LC27
	ldr	x0, [x1, w19, sxtw 3]
	cbz	x0, .L31
	ldr	w2, [x0, 28]
	cmp	w2, 1
	beq	.L32
.L29:
	str	xzr, [x1, w19, sxtw 3]
.L25:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L32:
	str	wzr, [x0, 28]
	b	.L29
	.p2align 3
.L30:
	ldr	x3, .LC25
	mov	w2, 412
	ldr	x1, .LC26
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L31:
	ldr	x3, .LC28
	mov	w2, 413
	ldr	x1, .LC26
	bl	dprint_vfmw
	b	.L25
	.size	FSP_DisableInstance, .-FSP_DisableInstance
	.align	3
.LC25:
	.xword	.LC7
	.align	3
.LC26:
	.xword	.LC2
	.align	3
.LC27:
	.xword	.LANCHOR0
	.align	3
.LC28:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_Exit
	.type	FSP_Exit, %function
FSP_Exit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	mov	x19, 0
	bl	_mcount
	ldr	x20, .LC31
	b	.L35
	.p2align 3
.L34:
	add	x19, x19, 1
	cmp	x19, 32
	beq	.L43
.L35:
	ldr	x0, [x20, x19, lsl 3]
	cbz	x0, .L34
	ldr	w0, [x0, 28]
	cbz	w0, .L34
	mov	w0, w19
	add	x19, x19, 1
	bl	FSP_DisableInstance
	cmp	x19, 32
	bne	.L35
.L43:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_Exit, .-FSP_Exit
	.align	3
.LC31:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ResetInstance
	.type	FSP_ResetInstance, %function
FSP_ResetInstance:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L48
	ldr	x0, .LC34
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L49
	bl	FSP_ClearContext
	mov	w0, 0
.L46:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L48:
	ldr	x3, .LC32
	mov	w2, 431
	ldr	x1, .LC33
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L46
.L49:
	ldr	x3, .LC35
	mov	w2, 432
	ldr	x1, .LC33
	bl	dprint_vfmw
	mov	w0, -1
	b	.L46
	.size	FSP_ResetInstance, .-FSP_ResetInstance
	.align	3
.LC32:
	.xword	.LC7
	.align	3
.LC33:
	.xword	.LC2
	.align	3
.LC34:
	.xword	.LANCHOR0
	.align	3
.LC35:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ConfigInstance
	.type	FSP_ConfigInstance, %function
FSP_ConfigInstance:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L60
	cbz	x21, .L61
	ldr	x0, .LC40
	ldr	x19, [x0, w20, sxtw 3]
	cbz	x19, .L54
	ldr	w0, [x19, 28]
	cmp	w0, 1
	bne	.L54
	ldr	x0, .LC43
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 503808
	ldr	w0, [x0, 1624]
	cbz	w0, .L62
.L56:
	ldr	x3, .LC44
	mov	x2, 20
	mov	x1, x21
	add	x0, x19, 36
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L52:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L62:
	mov	x0, x19
	bl	FSP_ClearContext
	b	.L56
	.p2align 3
.L54:
	ldr	x3, .LC42
	mov	w2, 570
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L52
	.p2align 3
.L60:
	ldr	x3, .LC36
	mov	w2, 567
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L52
.L61:
	ldr	x3, .LC39
	mov	w2, 568
	ldr	x1, .LC37
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L52
	.size	FSP_ConfigInstance, .-FSP_ConfigInstance
	.align	3
.LC36:
	.xword	.LC7
	.align	3
.LC37:
	.xword	.LC2
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC40:
	.xword	.LANCHOR0
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC43:
	.xword	s_pstVfmwChan
	.align	3
.LC44:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ConfigFrameBuf
	.type	FSP_ConfigFrameBuf, %function
FSP_ConfigFrameBuf:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	stp	x27, x28, [sp, 96]
	mov	w27, w0
	mov	x0, x30
	mov	w25, w1
	mov	w26, w2
	mov	x20, x3
	bl	_mcount
	ldr	x19, .LC45
	mov	x2, 1232
	ldr	x22, .LC46
	mov	w1, 0
	ldr	x3, [x19, 96]
	add	x0, x22, 256
	blr	x3
	cmp	w27, 31
	bhi	.L105
	ldr	x21, [x22, w27, sxtw 3]
	cbz	x21, .L106
	ldr	x24, .LC50
	add	x23, x21, 36
	ldr	x0, [x24, w27, sxtw 3]
	ldp	w4, w5, [x23, 4]
	ldp	w2, w3, [x0, 148]
	mul	w6, w4, w5
	mul	w1, w2, w3
	cmp	w6, w1
	bgt	.L107
	ldr	w1, [x0, 1552]
	ldrsb	w28, [x23, 1]
	cmp	w1, 1
	beq	.L108
.L68:
	add	x0, x0, 503808
	ldr	w1, [x0, 1632]
	cmp	w28, w1
	beq	.L70
	mov	w1, 1
	str	w1, [x0, 1648]
	ldr	x1, .LC54
	ldr	x8, [x1, 128]
	ldrsb	w1, [x23, 1]
	str	w1, [x0, 1632]
	cbz	x8, .L72
.L113:
	ldrsb	w6, [x21, 36]
	mov	w1, w26
	ldrsb	w4, [x23, 3]
	mov	w0, w25
	ldp	w2, w3, [x23, 4]
	add	x25, x22, 256
	mov	w7, w27
	mov	w5, 32
	str	x25, [sp]
	mov	w26, 32
	blr	x8
	ldr	x1, [x24, w27, sxtw 3]
	add	x1, x1, 503808
	ldr	w1, [x1, 4016]
	cmp	w1, 32
	csel	w1, w1, w26, le
	cmp	w0, 2
	strb	w1, [x21, 5]
	beq	.L109
	cbnz	w0, .L75
	ldr	w0, [x25, 48]
	strb	w0, [x21, 2]
	mov	w0, 31
	ldr	x1, .LC58
	ldr	x2, [x24, w27, sxtw 3]
	strb	wzr, [x2, 1624]
	str	wzr, [x2, 1600]
	bl	dprint_vfmw
	ldr	w4, [x25, 48]
	cmp	w28, w4
	bgt	.L110
	strb	wzr, [x21, 4]
	ldr	w0, [x25, 48]
	cmp	w0, 32
	csel	w0, w0, w26, le
	strb	w0, [x21, 3]
	mov	w0, 8
	ldr	x1, [x19, 24]
	blr	x1
	ldr	w0, [x25, 60]
	cbz	w0, .L111
	ldr	w13, [x21, 16]
	sxtw	x4, w27
	ldp	w5, w6, [x23, 4]
	ldp	w11, w10, [x25, 4]
	ldr	w9, [x25, 12]
	mov	x2, x25
	mov	w3, 0
	mov	w7, 4
	mov	w8, 1
	.p2align 2
.L83:
	uxtw	x12, w13
	uxtw	x0, w3
	lsl	x1, x12, 2
	lsl	x15, x0, 2
	sub	x1, x1, x12
	sub	x15, x15, x0
	lsl	x1, x1, 2
	add	x0, x0, 20
	sub	x1, x1, x12
	add	x15, x2, x15, lsl 2
	ldr	w17, [x2, 20]
	add	x1, x21, x1, lsl 3
	ldr	w18, [x2, x0, lsl 2]
	add	x0, x1, 20480
	ldr	w1, [x15, 468]
	ldr	w16, [x15, 464]
	ldr	x14, [x24, x4, lsl 3]
	str	w1, [x0, 1692]
	add	x1, x0, 1536
	str	w16, [x0, 1688]
	strb	wzr, [x0, 1681]
	strb	wzr, [x0, 1682]
	str	w13, [x0, 1684]
	ldr	w15, [x2, 32]
	stp	w18, w11, [x1, 164]
	stp	w10, w17, [x1, 172]
	str	w15, [x0, 1720]
	add	x15, x14, 507904
	ldr	w1, [x2, 16]
	ldr	w16, [x2, 28]
	str	w16, [x0, 1716]
	str	w1, [x0, 1728]
	ldr	w17, [x2, 36]
	ldp	w16, w1, [x2, 40]
	str	w9, [x0, 1724]
	str	w5, [x0, 1732]
	str	w6, [x0, 1736]
	str	w17, [x0, 1740]
	str	w16, [x0, 1744]
	str	w1, [x0, 1748]
	ldr	w0, [x15, 1676]
	cbnz	w0, .L80
	ldr	w0, [x15, 1672]
	cbz	w0, .L80
	ldr	x5, [x22, x4, lsl 3]
	mov	w1, 0
	ldr	w6, [x5, 16]
	lsl	x0, x6, 2
	sub	x0, x0, x6
	lsl	x0, x0, 2
	sub	x0, x0, x6
	add	x5, x5, x0, lsl 3
	add	x0, x5, 20480
	ldr	w6, [x0, 1688]
	b	.L82
	.p2align 3
.L81:
	ldr	w0, [x15, 1672]
	cmp	w1, w0
	bcs	.L112
.L82:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 28672
	add	x0, x0, 3143
	add	x0, x14, x0, lsl 4
	ldr	w0, [x0, 12]
	cmp	w6, w0
	bne	.L81
	add	x0, x5, 20480
	strb	w7, [x0, 1682]
	ldr	w0, [x15, 1672]
	cmp	w1, w0
	bcc	.L82
.L112:
	ldr	w13, [x21, 16]
	ldp	w5, w6, [x23, 4]
	uxtw	x12, w13
.L80:
	lsl	x0, x12, 2
	add	w13, w13, 1
	sub	x0, x0, x12
	add	w3, w3, 1
	lsl	x0, x0, 2
	sub	x0, x0, x12
	add	x0, x21, x0, lsl 3
	add	x0, x0, 20480
	str	w8, [x0, 1764]
	str	w13, [x21, 16]
	ldr	w0, [x2, 60]
	cmp	w0, w3
	bhi	.L83
.L79:
	add	x8, x22, 256
	ldr	w0, [x8, 68]
	cbz	w0, .L88
	ldr	w3, [x21, 24]
	mov	w2, 0
	.p2align 2
.L87:
	uxtw	x4, w3
	uxtw	x7, w2
	lsl	x0, x4, 2
	lsl	x1, x7, 2
	sub	x0, x0, x4
	sub	x1, x1, x7
	lsl	x0, x0, 2
	add	w3, w3, 1
	sub	x0, x0, x4
	add	x1, x8, x1, lsl 2
	add	w2, w2, 1
	add	x0, x21, x0, lsl 3
	add	x0, x0, 20480
	ldr	w1, [x1, 848]
	str	w1, [x0, 1696]
	str	w3, [x21, 24]
	ldr	w0, [x8, 68]
	cmp	w0, w2
	bhi	.L87
.L88:
	add	x3, x22, 256
	ldr	w0, [x3, 56]
	mov	w1, 32
	cmp	w0, w1
	csel	w0, w0, w1, le
	strb	w0, [x21, 5]
	ldr	w0, [x3, 64]
	cbz	w0, .L86
	ldr	w2, [x21, 20]
	mov	w1, 0
	mov	w7, 1
	.p2align 2
.L89:
	add	x0, x21, x2, uxtw 3
	add	x4, x3, x1, uxtw 3
	add	x0, x0, 24576
	add	w2, w2, 1
	add	w1, w1, 1
	ldr	w4, [x4, 208]
	strb	wzr, [x0, 3221]
	strb	w7, [x0, 3220]
	str	w4, [x0, 3216]
	str	w2, [x21, 20]
	ldr	w0, [x3, 64]
	cmp	w0, w1
	bhi	.L89
.L86:
	ldr	w1, [x22, 308]
	add	x4, x21, 20480
	str	w1, [x21, 8]
	mov	w2, 1
	str	wzr, [x21, 60]
	ldr	w3, [x22, 260]
	ldr	w7, [x4, 1688]
	ldr	w4, [x22, 264]
	stp	w3, w4, [x21, 80]
	stp	w5, w6, [x21, 108]
	ldr	w3, [x22, 284]
	ldr	w5, [x22, 276]
	ldr	w0, [x22, 300]
	stp	w5, w3, [x21, 88]
	ldr	w4, [x22, 292]
	ldr	w5, [x22, 288]
	ldr	w3, [x22, 296]
	ldr	w1, [x22, 256]
	str	w0, [x21, 124]
	mov	w0, 8
	strb	wzr, [x21, 57]
	strb	wzr, [x21, 58]
	str	w7, [x21, 64]
	str	w2, [x21, 140]
	str	w4, [x21, 116]
	str	w5, [x21, 96]
	str	w3, [x21, 120]
	str	w1, [x20]
	ldr	x1, [x19, 32]
	blr	x1
	mov	w0, 0
.L94:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L107:
	ldr	x1, .LC52
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, .LC53
	ldr	x4, [x0]
	cbz	x4, .L90
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w0, w27
	blr	x4
	add	sp, x29, 0
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L109:
	ldr	w1, [x25, 48]
	add	sp, x29, 0
	strb	w1, [x21, 2]
	mov	w2, 1
	ldr	x1, [x24, w27, sxtw 3]
	strb	w2, [x1, 1624]
	str	w2, [x1, 1600]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L70:
	ldr	x1, .LC54
	str	wzr, [x0, 1648]
	ldr	x8, [x1, 128]
	ldrsb	w1, [x23, 1]
	str	w1, [x0, 1632]
	cbnz	x8, .L113
.L72:
	ldr	w1, [x0, 4016]
	mov	w2, 32
	mov	w0, -1
	cmp	w1, w2
	csel	w1, w1, w2, le
	strb	w1, [x21, 5]
.L75:
	strb	wzr, [x21, 2]
	mov	w2, w0
	ldr	x1, .LC60
	mov	w0, 0
	ldr	x3, [x24, w27, sxtw 3]
	strb	wzr, [x3, 1624]
	str	wzr, [x3, 1600]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L94
.L90:
	mov	w0, -1
	b	.L94
	.p2align 3
.L108:
	add	x1, x0, 475136
	ldr	w1, [x1, 2280]
	tst	w1, -3
	beq	.L68
	cmp	w1, 1
	mov	w0, 0
	beq	.L94
	strb	wzr, [x21, 2]
	mov	w0, 31
	ldr	x1, .LC56
	ldr	x2, [x24, w27, sxtw 3]
	add	x2, x2, 475136
	ldr	w2, [x2, 2280]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L94
.L111:
	ldp	w5, w6, [x23, 4]
	b	.L79
.L105:
	ldr	x3, .LC47
	mov	w2, 599
	ldr	x1, .LC48
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L94
.L110:
	ldr	x1, .LC62
	mov	w3, w28
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L94
.L106:
	ldr	x3, .LC49
	mov	w2, 600
	ldr	x1, .LC48
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L94
	.size	FSP_ConfigFrameBuf, .-FSP_ConfigFrameBuf
	.align	3
.LC45:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC46:
	.xword	.LANCHOR0
	.align	3
.LC47:
	.xword	.LC7
	.align	3
.LC48:
	.xword	.LC2
	.align	3
.LC49:
	.xword	.LC16
	.align	3
.LC50:
	.xword	s_pstVfmwChan
	.align	3
.LC52:
	.xword	.LC51
	.align	3
.LC53:
	.xword	g_event_report
	.align	3
.LC54:
	.xword	g_vdm_hal_fun_ptr
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetOccupiedNum
	.type	FSP_GetOccupiedNum, %function
FSP_GetOccupiedNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	cmp	w19, 31
	bhi	.L120
	cmp	w20, 1088
	mov	w0, 1
	bgt	.L116
	ldr	x1, .LC66
	mov	w0, 4
	ldr	x1, [x1, w19, sxtw 3]
	add	x1, x1, 507904
	ldr	w1, [x1, 1732]
	cmp	w1, wzr
	csinc	w0, w0, wzr, eq
.L116:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L120:
	ldr	x3, .LC64
	mov	w2, 765
	ldr	x1, .LC65
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L116
	.size	FSP_GetOccupiedNum, .-FSP_GetOccupiedNum
	.align	3
.LC64:
	.xword	.LC7
	.align	3
.LC65:
	.xword	.LC2
	.align	3
.LC66:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IsPmvAvailable
	.type	FSP_IsPmvAvailable, %function
FSP_IsPmvAvailable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrh	w0, [x19, 4]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_IsPmvAvailable, .-FSP_IsPmvAvailable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetPhyFsNum
	.type	FSP_GetPhyFsNum, %function
FSP_GetPhyFsNum:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w21, 31
	bhi	.L131
	ldr	x23, .LC71
	ldr	x0, [x23, w21, sxtw 3]
	cbz	x0, .L132
	ldr	x22, .LC73
	mov	w0, 3
	mov	w19, 0
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x3, [x23, w21, sxtw 3]
	add	x2, x3, 20480
	add	x3, x3, 24576
	add	x2, x2, 1764
	add	x4, x3, 484
	b	.L127
	.p2align 3
.L126:
	add	x2, x2, 88
	cmp	x2, x4
	beq	.L133
.L127:
	ldr	w3, [x2]
	cmp	w3, 1
	bne	.L126
	ldr	w0, [x2, -72]
	add	x2, x2, 88
	cmp	w0, w20
	ccmp	w20, wzr, 4, ne
	csinc	w19, w19, w19, ne
	cmp	x2, x4
	bne	.L127
.L133:
	ldr	x1, [x22, 32]
	mov	w0, 3
	blr	x1
	mov	w0, w19
.L124:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L131:
	ldr	x3, .LC69
	mov	w2, 1042
	ldr	x1, .LC70
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L124
.L132:
	ldr	x3, .LC72
	mov	w2, 1043
	ldr	x1, .LC70
	bl	dprint_vfmw
	mov	w0, -1
	b	.L124
	.size	FSP_GetPhyFsNum, .-FSP_GetPhyFsNum
	.align	3
.LC69:
	.xword	.LC7
	.align	3
.LC70:
	.xword	.LC2
	.align	3
.LC71:
	.xword	.LANCHOR0
	.align	3
.LC72:
	.xword	.LC16
	.align	3
.LC73:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_RelsePhyFs
	.type	FSP_RelsePhyFs, %function
FSP_RelsePhyFs:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L167
	ldr	x22, .LC78
	ldr	x0, [x22, w20, sxtw 3]
	cbz	x0, .L168
	ldr	x23, .LC80
	mov	w0, 3
	mov	w19, 0
	ldr	x1, [x23, 24]
	blr	x1
	ldr	x2, [x22, w20, sxtw 3]
	add	x0, x2, 20480
	add	x0, x0, 1764
	b	.L141
	.p2align 3
.L138:
	add	w19, w19, 1
	add	x0, x0, 88
	cmp	w19, 32
	beq	.L165
.L141:
	ldr	w1, [x0]
	cmp	w1, 1
	bne	.L138
	ldrsb	w1, [x0, -83]
	cbnz	w1, .L138
	ldrsb	w1, [x0, -82]
	cbnz	w1, .L138
	ldr	w1, [x0, -72]
	cmp	w1, w21
	beq	.L138
	sxtw	x24, w19
	lsl	x0, x24, 2
	sub	x0, x0, x24
	lsl	x0, x0, 2
	sub	x24, x0, x24
	add	x2, x2, x24, lsl 3
	add	x24, x2, 20480
	ldr	w25, [x24, 1688]
	mov	w0, w25
	bl	MEM_Phy2Vir
	ldr	w21, [x24, 1692]
	cmp	w19, 31
	mov	x22, x0
	bgt	.L165
	mov	x1, x0
	str	wzr, [x24, 1764]
	mov	w2, w21
	mov	w0, w25
	uxtw	x19, w19
	bl	MEM_DelMemRecord
	ldr	x24, .LC81
	lsl	x1, x19, 6
	add	x19, x1, x19, lsl 3
	ldr	x0, [x24, w20, sxtw 3]
	add	x0, x0, x19
	add	x0, x0, 503808
	ldr	w1, [x0, 1664]
	cmp	w1, 255
	beq	.L143
	ldr	w26, [x0, 1720]
	mov	w0, w26
	bl	MEM_Phy2Vir
	mov	x1, x0
	ldr	x2, [x24, w20, sxtw 3]
	mov	w0, w26
	add	x19, x2, x19
	add	x2, x19, 503808
	ldr	w2, [x2, 1676]
	bl	MEM_DelMemRecord
.L143:
	ldr	x1, [x23, 32]
	mov	w0, 3
	blr	x1
	ldr	x1, [x23, 24]
	mov	w0, 8
	blr	x1
	ldr	x3, [x24, w20, sxtw 3]
	mov	w1, 0
	add	x4, x3, 507904
	add	x0, x4, 336
	b	.L146
	.p2align 3
.L144:
	add	w1, w1, 1
	add	x0, x0, 12
	cmp	w1, 32
	beq	.L147
.L146:
	ldrb	w2, [x0]
	cmp	w2, 1
	bne	.L144
	ldr	w2, [x0, -8]
	cmp	w25, w2
	bne	.L144
	cmp	w1, 31
	bgt	.L147
	sxtw	x1, w1
	lsl	x0, x1, 2
	sub	x1, x0, x1
	add	x0, x4, x1, lsl 2
	strb	wzr, [x0, 336]
.L147:
	add	x0, x3, 503808
	mov	w19, 0
	add	x0, x0, 1656
	b	.L150
	.p2align 3
.L148:
	add	w19, w19, 1
	add	x0, x0, 72
	cmp	w19, 32
	beq	.L151
.L150:
	ldr	w1, [x0]
	cmp	w1, 255
	beq	.L148
	ldr	w1, [x0, 32]
	cmp	w25, w1
	bne	.L148
	cmp	w19, 31
	bgt	.L151
	sxtw	x0, w19
	ldr	x2, .LC82
	lsl	x1, x0, 6
	add	x0, x1, x0, lsl 3
	mov	w1, 255
	add	x0, x3, x0
	ldr	x4, [x2]
	add	x0, x0, 503808
	str	w1, [x0, 1656]
	cbz	x4, .L151
	uxtw	x25, w25
	uxtw	x21, w21
	mov	w3, 24
	add	x2, x29, 88
	mov	w1, 123
	mov	w0, w20
	stp	x25, x22, [x29, 88]
	str	x21, [x29, 104]
	blr	x4
.L151:
	ldr	x1, [x23, 32]
	mov	w0, 8
	blr	x1
	cmp	w19, 31
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	csetm	w0, gt
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L165:
	ldr	x1, [x23, 32]
	mov	w0, 3
	blr	x1
	mov	w0, -1
.L164:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
.L167:
	ldr	x3, .LC76
	mov	w2, 1069
	ldr	x1, .LC77
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L164
.L168:
	ldr	x3, .LC79
	mov	w2, 1070
	ldr	x1, .LC77
	bl	dprint_vfmw
	mov	w0, -1
	b	.L164
	.size	FSP_RelsePhyFs, .-FSP_RelsePhyFs
	.align	3
.LC76:
	.xword	.LC7
	.align	3
.LC77:
	.xword	.LC2
	.align	3
.LC78:
	.xword	.LANCHOR0
	.align	3
.LC79:
	.xword	.LC16
	.align	3
.LC80:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC81:
	.xword	s_pstVfmwChan
	.align	3
.LC82:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_RemovePmv
	.type	FSP_RemovePmv, %function
FSP_RemovePmv:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L175
	cmp	w19, 31
	bhi	.L176
	ldr	x0, .LC87
	ldr	x2, [x0, w20, sxtw 3]
	cbz	x2, .L177
	sxtw	x1, w19
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x2, x0, lsl 4
	ldr	w3, [x0, 168]
	cmp	w3, 2
	beq	.L178
.L169:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L178:
	ldrsb	w0, [x0, 148]
	uxtb	w3, w0
	cmp	w3, 31
	bhi	.L174
	sxtw	x0, w0
	add	x0, x0, 3474
	add	x0, x2, x0, lsl 3
	strb	wzr, [x0, 5]
.L174:
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x1, x0, x1
	add	x1, x2, x1, lsl 4
	str	wzr, [x1, 168]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L175:
	ldr	x3, .LC83
	mov	w2, 1152
	ldr	x1, .LC84
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L176:
	ldr	x3, .LC86
	mov	w2, 1153
	ldr	x1, .LC84
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L177:
	ldr	x3, .LC88
	mov	w2, 1154
	ldr	x1, .LC84
	mov	w0, 0
	bl	dprint_vfmw
	b	.L169
	.size	FSP_RemovePmv, .-FSP_RemovePmv
	.align	3
.LC83:
	.xword	.LC7
	.align	3
.LC84:
	.xword	.LC2
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC87:
	.xword	.LANCHOR0
	.align	3
.LC88:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_SetRef
	.type	FSP_SetRef, %function
FSP_SetRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	mov	w21, w2
	bl	_mcount
	cmp	w20, 31
	bhi	.L208
	cmp	w19, 31
	bhi	.L209
	ldr	x0, .LC92
	ldr	x20, [x0, w20, sxtw 3]
	cbz	x20, .L210
	lsl	x0, x19, 2
	sxtb	w1, w21
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 4
	ldrsb	w2, [x0, 146]
	strb	w1, [x0, 144]
	cbnz	w2, .L179
	ldr	x2, [x0, 176]
	cbz	x2, .L185
	ldr	w0, [x0, 164]
	ldr	w3, [x2, 72]
	cmp	w3, w0
	beq	.L211
.L185:
	lsl	x0, x19, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 4
	ldrsb	w3, [x0, 148]
	uxtb	w1, w3
	cmp	w1, 31
	bhi	.L186
	cmp	w21, 1
	beq	.L212
	cbnz	w21, .L189
	ldr	w1, [x0, 168]
	cmp	w1, 2
	beq	.L213
.L190:
	lsl	x0, x19, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 4
	ldr	x0, [x0, 184]
	cbz	x0, .L199
	ldrsb	w1, [x0, 2]
	cmp	w1, 1
	beq	.L214
.L199:
	lsl	x1, x19, 2
	sub	x1, x1, x19
	lsl	x1, x1, 2
	sub	x1, x1, x19
	lsl	x1, x1, 2
	sub	x19, x1, x19
	add	x19, x20, x19, lsl 4
	str	xzr, [x19, 176]
.L179:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L208:
	ldr	x3, .LC89
	mov	w2, 1177
	ldr	x1, .LC90
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L212:
	ldr	w1, [x0, 168]
	cmp	w1, 1
	beq	.L215
.L188:
	lsl	x0, x19, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 4
	ldr	x1, [x0, 184]
	cbz	x1, .L179
.L194:
	lsl	x0, x19, 2
	ldr	w3, [x1, 72]
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 4
	ldr	w2, [x0, 164]
	cmp	w3, w2
	ccmp	w21, 1, 0, eq
	beq	.L216
.L191:
	cbz	w21, .L199
.L207:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L209:
	ldr	x3, .LC91
	mov	w2, 1178
	ldr	x1, .LC90
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L186:
	ldr	x1, .LC95
	mov	w2, 1226
	mov	w0, 0
	bl	dprint_vfmw
	cbz	w21, .L190
	b	.L188
	.p2align 3
.L211:
	strb	w1, [x2, 1]
	b	.L185
	.p2align 3
.L215:
	sxtw	x1, w3
	mov	w2, 2
	add	x1, x1, 3474
	add	x1, x20, x1, lsl 3
	strb	w21, [x1, 5]
	str	w2, [x0, 168]
.L189:
	lsl	x0, x19, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 4
	ldr	x1, [x0, 184]
	cbnz	x1, .L194
	cbz	w21, .L199
	b	.L207
	.p2align 3
.L216:
	ldrsb	w2, [x1, 2]
	cmp	w2, 1
	bne	.L191
	mov	w2, 2
	strb	w2, [x1, 2]
	strb	w2, [x0, 145]
	cbz	w21, .L199
	b	.L207
	.p2align 3
.L214:
	strb	wzr, [x0, 2]
	b	.L199
	.p2align 3
.L213:
	sxtw	x1, w3
	add	x1, x1, 3474
	add	x1, x20, x1, lsl 3
	strb	wzr, [x1, 5]
	str	wzr, [x0, 152]
	str	wzr, [x0, 168]
	b	.L190
	.p2align 3
.L210:
	ldr	x3, .LC93
	mov	w2, 1179
	ldr	x1, .LC90
	mov	w0, 0
	bl	dprint_vfmw
	b	.L179
	.size	FSP_SetRef, .-FSP_SetRef
	.align	3
.LC89:
	.xword	.LC7
	.align	3
.LC90:
	.xword	.LC2
	.align	3
.LC91:
	.xword	.LC85
	.align	3
.LC92:
	.xword	.LANCHOR0
	.align	3
.LC93:
	.xword	.LC16
	.align	3
.LC95:
	.xword	.LC94
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetRef
	.type	FSP_GetRef, %function
FSP_GetRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L222
	cmp	w19, 31
	bhi	.L223
	ldr	x0, .LC101
	ldr	x2, [x0, w20, sxtw 3]
	cbz	x2, .L224
	sxtw	x1, w19
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x1, x0, x1
	add	x1, x2, x1, lsl 4
	ldrsb	w0, [x1, 144]
.L219:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L222:
	ldr	x3, .LC97
	mov	w2, 1258
	ldr	x1, .LC98
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L219
	.p2align 3
.L223:
	ldr	x3, .LC100
	mov	w2, 1259
	ldr	x1, .LC98
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L219
.L224:
	ldr	x3, .LC102
	mov	w2, 1260
	ldr	x1, .LC98
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L219
	.size	FSP_GetRef, .-FSP_GetRef
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC98:
	.xword	.LC2
	.align	3
.LC100:
	.xword	.LC99
	.align	3
.LC101:
	.xword	.LANCHOR0
	.align	3
.LC102:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_SetDisplay
	.type	FSP_SetDisplay, %function
FSP_SetDisplay:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	sxtw	x20, w1
	mov	w22, w2
	bl	_mcount
	cmp	w21, 31
	bhi	.L252
	cmp	w20, 31
	bhi	.L253
	ldr	x24, .LC106
	ldr	x0, [x24, w21, sxtw 3]
	cbz	x0, .L254
	ldr	x25, .LC108
	lsl	x19, x20, 2
	sub	x19, x19, x20
	mov	w0, 3
	lsl	x19, x19, 2
	mov	w23, w0
	ldr	x1, [x25, 24]
	sub	x19, x19, x20
	lsl	x19, x19, 2
	sub	x19, x19, x20
	blr	x1
	ldr	x26, [x24, w21, sxtw 3]
	cmp	w22, wzr
	add	x24, x26, x19, lsl 4
	csel	w1, wzr, w23, eq
	ldrsb	w0, [x24, 146]
	strb	w1, [x24, 145]
	cbnz	w0, .L238
	ldr	x1, [x24, 184]
	cbz	x1, .L238
	ldr	w3, [x1, 72]
	ldr	w2, [x24, 164]
	cmp	w3, w2
	bne	.L255
	cbnz	w22, .L234
	strb	wzr, [x24, 145]
	mov	w0, w21
	strb	wzr, [x1, 2]
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L256
.L236:
	lsl	x1, x20, 2
	sub	x1, x1, x20
	lsl	x1, x1, 2
	sub	x1, x1, x20
	lsl	x1, x1, 2
	sub	x1, x1, x20
	add	x20, x26, x1, lsl 4
	str	xzr, [x20, 184]
.L238:
	ldr	x1, [x25, 32]
	mov	w0, 3
	blr	x1
.L225:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L252:
	ldr	x3, .LC103
	mov	w2, 1273
	ldr	x1, .LC104
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L234:
	mov	w0, w21
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L257
.L237:
	lsl	x0, x20, 2
	mov	w1, 3
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x20, x0, x20
	add	x20, x26, x20, lsl 4
	ldr	x0, [x20, 184]
	strb	w1, [x20, 145]
	strb	w1, [x0, 2]
	b	.L238
	.p2align 3
.L253:
	ldr	x3, .LC105
	mov	w2, 1274
	ldr	x1, .LC104
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L255:
	ldr	x1, .LC110
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x25, 32]
	mov	w0, w23
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L254:
	ldr	x3, .LC107
	mov	w2, 1275
	ldr	x1, .LC104
	bl	dprint_vfmw
	b	.L225
	.p2align 3
.L257:
	ldr	x0, [x24, 184]
	cbz	x0, .L237
	ldr	w1, [x0, 80]
	add	w1, w1, 1
	str	w1, [x0, 80]
	b	.L237
	.p2align 3
.L256:
	ldr	x0, [x24, 184]
	cbz	x0, .L236
	ldr	w1, [x0, 80]
	cbz	w1, .L236
	add	x19, x26, x19, lsl 4
	sub	w1, w1, #1
	str	w1, [x0, 80]
	ldr	x0, [x19, 184]
	ldr	w1, [x0, 80]
	cbz	w1, .L236
	mov	w1, 3
	strb	w1, [x0, 2]
	b	.L236
	.size	FSP_SetDisplay, .-FSP_SetDisplay
	.align	3
.LC103:
	.xword	.LC7
	.align	3
.LC104:
	.xword	.LC2
	.align	3
.LC105:
	.xword	.LC85
	.align	3
.LC106:
	.xword	.LANCHOR0
	.align	3
.LC107:
	.xword	.LC16
	.align	3
.LC108:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC110:
	.xword	.LC109
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ClearNotInVoQueue
	.type	FSP_ClearNotInVoQueue, %function
FSP_ClearNotInVoQueue:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L269
	cbz	x22, .L270
	ldr	x0, .LC115
	ldr	x19, [x0, w20, sxtw 3]
	cbz	x19, .L271
	add	x21, x19, 20480
	add	x19, x19, 192
	add	x21, x21, 1728
	b	.L264
	.p2align 3
.L263:
	add	x19, x19, 688
	cmp	x19, x21
	beq	.L272
.L264:
	ldr	w1, [x19, 148]
	mov	w0, w20
	mov	w2, 0
	bl	FSP_SetRef
	mov	x1, x19
	mov	x0, x22
	bl	IsImageInVoQueue
	cbz	w0, .L263
	ldr	w1, [x19, 148]
	mov	w2, 0
	mov	w0, w20
	add	x19, x19, 688
	bl	FSP_SetDisplay
	cmp	x19, x21
	bne	.L264
.L272:
	mov	w0, 0
.L260:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L269:
	ldr	x3, .LC111
	mov	w2, 501
	ldr	x1, .LC112
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L260
.L271:
	ldr	x3, .LC116
	mov	w2, 503
	ldr	x1, .LC112
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L260
.L270:
	ldr	x3, .LC114
	mov	w2, 502
	ldr	x1, .LC112
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L260
	.size	FSP_ClearNotInVoQueue, .-FSP_ClearNotInVoQueue
	.align	3
.LC111:
	.xword	.LC7
	.align	3
.LC112:
	.xword	.LC2
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC115:
	.xword	.LANCHOR0
	.align	3
.LC116:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetDisplay
	.type	FSP_GetDisplay, %function
FSP_GetDisplay:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L278
	ldr	x0, .LC119
	ldr	x2, [x0, w20, sxtw 3]
	cbz	x2, .L279
	cmp	w19, 31
	bhi	.L280
	sxtw	x1, w19
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x1, x0, x1
	add	x1, x2, x1, lsl 4
	ldrsb	w0, [x1, 145]
.L275:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L278:
	ldr	x3, .LC117
	mov	w2, 1348
	ldr	x1, .LC118
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L275
	.p2align 3
.L280:
	ldr	x3, .LC121
	mov	w2, 1350
	ldr	x1, .LC118
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L275
.L279:
	ldr	x3, .LC120
	mov	w2, 1349
	ldr	x1, .LC118
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L275
	.size	FSP_GetDisplay, .-FSP_GetDisplay
	.align	3
.LC117:
	.xword	.LC7
	.align	3
.LC118:
	.xword	.LC2
	.align	3
.LC119:
	.xword	.LANCHOR0
	.align	3
.LC120:
	.xword	.LC16
	.align	3
.LC121:
	.xword	.LC85
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_SetStoreType
	.type	FSP_SetStoreType, %function
FSP_SetStoreType:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w22, w1
	sxtw	x19, w2
	mov	w20, w3
	bl	_mcount
	cmp	w21, 31
	bhi	.L290
	ldr	x0, .LC124
	ldr	x3, [x0, w21, sxtw 3]
	cbz	x3, .L291
	cmp	w19, 31
	bhi	.L292
	cbz	w22, .L293
	cmp	w22, 1
	bne	.L289
	ldrsb	w0, [x3, 4]
	cmp	w19, w0
	bge	.L289
	lsl	x2, x19, 2
	mov	w0, 0
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x2, x2, x19
	add	x19, x3, x2, lsl 3
	add	x19, x19, 24576
	str	w20, [x19, 476]
.L283:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L293:
	ldrsb	w0, [x3, 3]
	cmp	w19, w0
	bge	.L289
	lsl	x2, x19, 2
	mov	w0, 0
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x19, x2, x19
	add	x19, x3, x19, lsl 3
	add	x19, x19, 20480
	str	w20, [x19, 1756]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L289:
	mov	w0, -1
	b	.L283
	.p2align 3
.L290:
	ldr	x3, .LC122
	mov	w2, 1363
	ldr	x1, .LC123
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L283
	.p2align 3
.L292:
	ldr	x3, .LC127
	mov	w2, 1365
	ldr	x1, .LC123
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L283
.L291:
	ldr	x3, .LC125
	mov	w2, 1364
	ldr	x1, .LC123
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L283
	.size	FSP_SetStoreType, .-FSP_SetStoreType
	.align	3
.LC122:
	.xword	.LC7
	.align	3
.LC123:
	.xword	.LC2
	.align	3
.LC124:
	.xword	.LANCHOR0
	.align	3
.LC125:
	.xword	.LC16
	.align	3
.LC127:
	.xword	.LC126
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetStoreType
	.type	FSP_GetStoreType, %function
FSP_GetStoreType:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	sxtw	x20, w2
	bl	_mcount
	cmp	w19, 31
	bhi	.L303
	ldr	x0, .LC130
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L304
	cmp	w20, 31
	bhi	.L305
	cbnz	w21, .L299
	ldrsb	w2, [x1, 3]
	mov	w0, 2
	cmp	w20, w2
	bge	.L296
	lsl	x0, x20, 2
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x20, x0, x20
	add	x1, x1, x20, lsl 3
	add	x1, x1, 20480
	ldr	w0, [x1, 1756]
	b	.L296
	.p2align 3
.L303:
	ldr	x3, .LC128
	mov	w2, 1394
	ldr	x1, .LC129
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L296:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L305:
	ldr	x3, .LC132
	mov	w2, 1396
	ldr	x1, .LC129
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L299:
	cmp	w21, 1
	mov	w0, 2
	bne	.L296
	ldrsb	w2, [x1, 4]
	cmp	w20, w2
	bge	.L296
	lsl	x0, x20, 2
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x0, x0, x20
	add	x0, x1, x0, lsl 3
	add	x0, x0, 24576
	ldr	w0, [x0, 476]
	b	.L296
	.p2align 3
.L304:
	ldr	x3, .LC131
	mov	w2, 1395
	ldr	x1, .LC129
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L296
	.size	FSP_GetStoreType, .-FSP_GetStoreType
	.align	3
.LC128:
	.xword	.LC7
	.align	3
.LC129:
	.xword	.LC2
	.align	3
.LC130:
	.xword	.LANCHOR0
	.align	3
.LC131:
	.xword	.LC16
	.align	3
.LC132:
	.xword	.LC126
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_ClearLogicFs
	.type	FSP_ClearLogicFs, %function
FSP_ClearLogicFs:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	ccmp	w20, 31, 2, ls
	bhi	.L306
	ldr	x21, .LC133
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L306
	mov	w2, 0
	mov	w1, w20
	mov	w0, w19
	bl	FSP_SetRef
	sxtw	x0, w20
	ldr	x2, [x21, w19, sxtw 3]
	lsl	x1, x0, 2
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x2, x0, lsl 4
	ldrsb	w0, [x0, 145]
	cmp	w0, 3
	beq	.L306
	mov	w2, 0
	mov	w1, w20
	mov	w0, w19
	bl	FSP_SetDisplay
.L306:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	FSP_ClearLogicFs, .-FSP_ClearLogicFs
	.align	3
.LC133:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetLogicFs
	.type	FSP_GetLogicFs, %function
FSP_GetLogicFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L319
	ldr	x0, .LC134
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L319
	sxtw	x1, w19
	lsl	x2, x1, 2
	sub	x2, x2, x1
	lsl	x2, x2, 2
	sub	x2, x2, x1
	lsl	x2, x2, 2
	sub	x1, x2, x1
	ldp	x19, x20, [sp, 16]
	add	x0, x0, x1, lsl 4
	add	x0, x0, 144
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L319:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetLogicFs, .-FSP_GetLogicFs
	.align	3
.LC134:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetFsImagePtr
	.type	FSP_GetFsImagePtr, %function
FSP_GetFsImagePtr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L323
	ldr	x0, .LC135
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L323
	sxtw	x1, w19
	lsl	x2, x1, 2
	sub	x2, x2, x1
	lsl	x2, x2, 2
	sub	x2, x2, x1
	lsl	x2, x2, 2
	sub	x1, x2, x1
	ldp	x19, x20, [sp, 16]
	add	x0, x0, x1, lsl 4
	add	x0, x0, 192
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L323:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetFsImagePtr, .-FSP_GetFsImagePtr
	.align	3
.LC135:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetDecPhyFs
	.type	FSP_GetDecPhyFs, %function
FSP_GetDecPhyFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L327
	ldr	x0, .LC136
	ldr	x2, [x0, w20, sxtw 3]
	cbz	x2, .L327
	sxtw	x1, w19
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x1, x0, x1
	ldp	x19, x20, [sp, 16]
	add	x1, x2, x1, lsl 4
	ldp	x29, x30, [sp], 32
	ldr	x0, [x1, 176]
	ret
	.p2align 3
.L327:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetDecPhyFs, .-FSP_GetDecPhyFs
	.align	3
.LC136:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetDispPhyFs
	.type	FSP_GetDispPhyFs, %function
FSP_GetDispPhyFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L331
	ldr	x0, .LC137
	ldr	x2, [x0, w20, sxtw 3]
	cbz	x2, .L331
	sxtw	x1, w19
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x1, x0, x1
	ldp	x19, x20, [sp, 16]
	add	x1, x2, x1, lsl 4
	ldp	x29, x30, [sp], 32
	ldr	x0, [x1, 184]
	ret
	.p2align 3
.L331:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetDispPhyFs, .-FSP_GetDispPhyFs
	.align	3
.LC137:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetPmvAddr
	.type	FSP_GetPmvAddr, %function
FSP_GetPmvAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	ccmp	w19, 31, 2, ls
	bhi	.L335
	ldr	x0, .LC138
	ldr	x2, [x0, w20, sxtw 3]
	cbz	x2, .L335
	sxtw	x1, w19
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x1, x0, x1
	ldp	x19, x20, [sp, 16]
	add	x1, x2, x1, lsl 4
	ldp	x29, x30, [sp], 32
	ldr	w0, [x1, 152]
	ret
	.p2align 3
.L335:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_GetPmvAddr, .-FSP_GetPmvAddr
	.align	3
.LC138:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetDecFsAddrTab
	.type	FSP_GetDecFsAddrTab, %function
FSP_GetDecFsAddrTab:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	mov	x21, x3
	bl	_mcount
	cmp	w22, 31
	bhi	.L347
	ldr	x2, .LC141
	ldr	x0, [x2, w22, sxtw 3]
	cbz	x0, .L348
	cbz	x20, .L349
	cbz	x19, .L350
	ldrsb	w3, [x0, 3]
	mov	w1, 88
	str	w3, [x19]
	mov	w0, 0
	cmp	w3, wzr
	ldr	x6, [x2, w22, sxtw 3]
	add	x6, x6, 20480
	add	x6, x6, 1680
	ble	.L336
	.p2align 2
.L345:
	smaddl	x4, w0, w1, x6
	ldr	w5, [x4, 8]
	str	w5, [x20, w0, sxtw 2]
	ldr	w4, [x4, 20]
	str	w4, [x21, w0, sxtw 2]
	add	w0, w0, 1
	ldr	w4, [x19]
	cmp	w4, w0
	bgt	.L345
.L336:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L347:
	ldr	x3, .LC139
	mov	w2, 1513
	ldr	x1, .LC140
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L348:
	ldr	x3, .LC142
	mov	w2, 1514
	ldr	x1, .LC140
	bl	dprint_vfmw
	b	.L336
.L349:
	ldr	x3, .LC144
	mov	w2, 1515
	ldr	x1, .LC140
	mov	w0, 0
	bl	dprint_vfmw
	b	.L336
.L350:
	ldr	x3, .LC146
	mov	w2, 1516
	ldr	x1, .LC140
	mov	w0, 0
	bl	dprint_vfmw
	b	.L336
	.size	FSP_GetDecFsAddrTab, .-FSP_GetDecFsAddrTab
	.align	3
.LC139:
	.xword	.LC7
	.align	3
.LC140:
	.xword	.LC2
	.align	3
.LC141:
	.xword	.LANCHOR0
	.align	3
.LC142:
	.xword	.LC16
	.align	3
.LC144:
	.xword	.LC143
	.align	3
.LC146:
	.xword	.LC145
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetPmvAddrTab
	.type	FSP_GetPmvAddrTab, %function
FSP_GetPmvAddrTab:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	mov	x19, x2
	bl	_mcount
	cmp	w20, 31
	bhi	.L362
	ldr	x0, .LC149
	ldr	x4, [x0, w20, sxtw 3]
	cbz	x4, .L363
	cbz	x19, .L364
	cbz	x21, .L365
	ldrsb	w0, [x4, 5]
	mov	w3, 0
	str	w0, [x21]
	ldrsb	w0, [x4, 5]
	cmp	w0, wzr
	ble	.L351
	.p2align 2
.L360:
	sxtw	x0, w3
	add	x0, x0, 3474
	lsl	x0, x0, 3
	ldr	w0, [x4, x0]
	str	w0, [x19, w3, sxtw 2]
	add	w3, w3, 1
	ldrsb	w0, [x4, 5]
	cmp	w0, w3
	bgt	.L360
.L351:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L362:
	ldr	x3, .LC147
	mov	w2, 1537
	ldr	x1, .LC148
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L363:
	ldr	x3, .LC150
	mov	w2, 1538
	ldr	x1, .LC148
	mov	w0, 0
	bl	dprint_vfmw
	b	.L351
.L364:
	ldr	x3, .LC152
	mov	w2, 1539
	ldr	x1, .LC148
	mov	w0, 0
	bl	dprint_vfmw
	b	.L351
.L365:
	ldr	x3, .LC154
	mov	w2, 1540
	ldr	x1, .LC148
	mov	w0, 0
	bl	dprint_vfmw
	b	.L351
	.size	FSP_GetPmvAddrTab, .-FSP_GetPmvAddrTab
	.align	3
.LC147:
	.xword	.LC7
	.align	3
.LC148:
	.xword	.LC2
	.align	3
.LC149:
	.xword	.LANCHOR0
	.align	3
.LC150:
	.xword	.LC16
	.align	3
.LC152:
	.xword	.LC151
	.align	3
.LC154:
	.xword	.LC153
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetInstInfo
	.type	FSP_GetInstInfo, %function
FSP_GetInstInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L370
	ldr	x0, .LC157
	ldr	x3, [x0, w20, sxtw 3]
	cbz	x3, .L371
	ldrsb	w1, [x3, 3]
	add	x0, x3, 20480
	strb	w1, [x19, 2]
	mov	x2, 2816
	ldr	x5, .LC159
	add	x1, x0, 1680
	ldr	w6, [x0, 1688]
	ldr	w4, [x0, 1776]
	add	x0, x19, 8
	sub	w4, w4, w6
	str	w4, [x19, 4]
	ldrsb	w4, [x3, 4]
	strb	w4, [x19, 3]
	ldrsb	w4, [x3]
	strb	w4, [x19]
	ldrsb	w3, [x3, 5]
	strb	w3, [x19, 1]
	ldr	x3, [x5, 104]
	blr	x3
.L366:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L370:
	ldr	x3, .LC155
	mov	w2, 1557
	ldr	x1, .LC156
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L371:
	ldr	x3, .LC158
	mov	w2, 1558
	ldr	x1, .LC156
	mov	w0, 0
	bl	dprint_vfmw
	b	.L366
	.size	FSP_GetInstInfo, .-FSP_GetInstInfo
	.align	3
.LC155:
	.xword	.LC7
	.align	3
.LC156:
	.xword	.LC2
	.align	3
.LC157:
	.xword	.LANCHOR0
	.align	3
.LC158:
	.xword	.LC16
	.align	3
.LC159:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetLogicIdByPhyAddr
	.type	FSP_GetLogicIdByPhyAddr, %function
FSP_GetLogicIdByPhyAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L384
	ldr	x1, .LC162
	mov	w0, 0
	ldr	x1, [x1, w20, sxtw 3]
	add	x2, x1, 176
	cbnz	x1, .L381
	b	.L385
	.p2align 3
.L376:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L386
.L381:
	ldr	x3, [x2]
	add	x2, x2, 688
	cbz	x3, .L376
	ldr	w3, [x3, 8]
	cmp	w3, w19
	bne	.L376
.L374:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L386:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L384:
	ldr	x3, .LC160
	mov	w2, 1579
	ldr	x1, .LC161
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L374
.L385:
	ldr	x3, .LC163
	mov	w2, 1580
	ldr	x1, .LC161
	bl	dprint_vfmw
	mov	w0, -1
	b	.L374
	.size	FSP_GetLogicIdByPhyAddr, .-FSP_GetLogicIdByPhyAddr
	.align	3
.LC160:
	.xword	.LC7
	.align	3
.LC161:
	.xword	.LC2
	.align	3
.LC162:
	.xword	.LANCHOR0
	.align	3
.LC163:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetNullLogicFs
	.type	FSP_GetNullLogicFs, %function
FSP_GetNullLogicFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L401
	ldr	x0, .LC166
	ldr	x3, [x0, w19, sxtw 3]
	cbz	x3, .L390
	add	x1, x3, 20480
	ldrsb	w0, [x1, 993]
	cbz	w0, .L402
	add	x1, x1, 305
	mov	w0, 30
	b	.L393
	.p2align 3
.L404:
	sub	w0, w0, #1
	cmn	w0, #1
	beq	.L403
.L393:
	ldrsb	w2, [x1]
	sub	x1, x1, #688
	cbnz	w2, .L404
.L391:
	sxtw	x1, w0
	lsl	x2, x1, 2
	sub	x2, x2, x1
	lsl	x2, x2, 2
	sub	x2, x2, x1
	lsl	x2, x2, 2
	sub	x1, x2, x1
	add	x1, x3, x1, lsl 4
	stp	xzr, xzr, [x1, 176]
.L389:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L403:
	mov	w0, 0
	b	.L391
.L402:
	mov	w0, 31
	b	.L391
.L401:
	ldr	x3, .LC164
	mov	w2, 1606
	ldr	x1, .LC165
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L389
.L390:
	ldr	x3, .LC167
	mov	w2, 1607
	ldr	x1, .LC165
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L389
	.size	FSP_GetNullLogicFs, .-FSP_GetNullLogicFs
	.align	3
.LC164:
	.xword	.LC7
	.align	3
.LC165:
	.xword	.LC2
	.align	3
.LC166:
	.xword	.LANCHOR0
	.align	3
.LC167:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetFspType
	.type	FSP_GetFspType, %function
FSP_GetFspType:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L409
	ldr	x0, .LC170
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L410
	ldr	w0, [x0, 28]
	cmp	w0, 1
	csetm	w0, ne
.L407:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L409:
	ldr	x3, .LC168
	mov	w2, 1628
	ldr	x1, .LC169
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L407
.L410:
	ldr	x3, .LC171
	mov	w2, 1629
	ldr	x1, .LC169
	bl	dprint_vfmw
	mov	w0, -1
	b	.L407
	.size	FSP_GetFspType, .-FSP_GetFspType
	.align	3
.LC168:
	.xword	.LC7
	.align	3
.LC169:
	.xword	.LC2
	.align	3
.LC170:
	.xword	.LANCHOR0
	.align	3
.LC171:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetTotalValidFsNum
	.type	FSP_GetTotalValidFsNum, %function
FSP_GetTotalValidFsNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L415
	ldr	x0, .LC174
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L416
	ldrsb	w0, [x0, 2]
.L413:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L415:
	ldr	x3, .LC172
	mov	w2, 1643
	ldr	x1, .LC173
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L413
.L416:
	ldr	x3, .LC175
	mov	w2, 1644
	ldr	x1, .LC173
	bl	dprint_vfmw
	mov	w0, -1
	b	.L413
	.size	FSP_GetTotalValidFsNum, .-FSP_GetTotalValidFsNum
	.align	3
.LC172:
	.xword	.LC7
	.align	3
.LC173:
	.xword	.LC2
	.align	3
.LC174:
	.xword	.LANCHOR0
	.align	3
.LC175:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IsSpecialFrm
	.type	FSP_IsSpecialFrm, %function
FSP_IsSpecialFrm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	bhi	.L427
	ldr	x0, .LC178
	ldr	x3, [x0, w20, sxtw 3]
	cbz	x3, .L422
	sub	w1, w19, #1
	mov	w0, 0
	cmn	w1, #3
	bhi	.L419
	add	x2, x3, 507904
	ldr	w1, [x2, 1672]
	cbz	w1, .L419
	ldr	w0, [x2, 1148]
	cmp	w19, w0
	beq	.L426
	mov	w2, 0
	b	.L420
	.p2align 3
.L421:
	add	x0, x0, 3143
	add	x0, x3, x0, lsl 4
	ldr	w0, [x0, 12]
	cmp	w19, w0
	beq	.L426
.L420:
	add	w2, w2, 1
	cmp	w2, w1
	sxtw	x0, w2
	add	x0, x0, 28672
	bne	.L421
.L422:
	mov	w0, 0
.L419:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L426:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L427:
	ldr	x3, .LC176
	mov	w2, 1654
	ldr	x1, .LC177
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L419
	.size	FSP_IsSpecialFrm, .-FSP_IsSpecialFrm
	.align	3
.LC176:
	.xword	.LC7
	.align	3
.LC177:
	.xword	.LC2
	.align	3
.LC178:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_EmptyInstance
	.type	FSP_EmptyInstance, %function
FSP_EmptyInstance:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L450
	ldr	x0, .LC181
	ldr	x22, [x0, w19, sxtw 3]
	cbz	x22, .L451
	ldr	x3, .LC183
	mov	x2, 22016
	mov	w1, 0
	add	x0, x22, 144
	mov	w24, 0
	mov	w21, 4
	ldr	x3, [x3, 96]
	blr	x3
	ldrsb	w0, [x22, 3]
	cmp	w0, wzr
	ble	.L438
	.p2align 2
.L446:
	sxtw	x23, w24
	mov	w0, w19
	lsl	x20, x23, 2
	add	w24, w24, 1
	sub	x20, x20, x23
	lsl	x20, x20, 2
	sub	x20, x20, x23
	add	x20, x22, x20, lsl 3
	add	x20, x20, 20480
	ldr	w1, [x20, 1688]
	bl	FSP_IsSpecialFrm
	cmp	w0, 1
	mov	w1, 0
	strb	wzr, [x20, 1681]
	csel	w1, w21, w1, eq
	strb	wzr, [x20, 1680]
	strb	w1, [x20, 1682]
	str	wzr, [x20, 1752]
	ldrsb	w0, [x22, 3]
	cmp	w0, w24
	bgt	.L446
.L438:
	ldrsb	w0, [x22, 4]
	mov	w24, 0
	mov	w21, 4
	cmp	w0, wzr
	ble	.L434
	.p2align 2
.L445:
	sxtw	x23, w24
	mov	w0, w19
	lsl	x20, x23, 2
	add	w24, w24, 1
	sub	x20, x20, x23
	lsl	x20, x20, 2
	sub	x20, x20, x23
	add	x20, x22, x20, lsl 3
	add	x20, x20, 24576
	ldr	w1, [x20, 408]
	bl	FSP_IsSpecialFrm
	cmp	w0, 1
	mov	w1, 0
	strb	wzr, [x20, 401]
	csel	w1, w21, w1, eq
	strb	wzr, [x20, 400]
	strb	w1, [x20, 402]
	str	wzr, [x20, 472]
	ldrsb	w0, [x22, 4]
	cmp	w0, w24
	bgt	.L445
.L434:
	ldrsb	w0, [x22, 5]
	cmp	w0, wzr
	ble	.L440
	sub	w1, w0, #1
	mov	x3, 27804
	add	x0, x22, 24576
	mov	w2, 1
	add	x1, x3, x1, uxtw 3
	add	x0, x0, 3220
	add	x1, x22, x1
	.p2align 2
.L444:
	strb	w2, [x0]
	add	x0, x0, 8
	strb	wzr, [x0, -7]
	cmp	x1, x0
	bne	.L444
.L440:
	mov	w0, 0
	str	wzr, [x22, 12]
.L430:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L450:
	ldr	x3, .LC179
	mov	w2, 446
	ldr	x1, .LC180
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L430
.L451:
	ldr	x3, .LC182
	mov	w2, 447
	ldr	x1, .LC180
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L430
	.size	FSP_EmptyInstance, .-FSP_EmptyInstance
	.align	3
.LC179:
	.xword	.LC7
	.align	3
.LC180:
	.xword	.LC2
	.align	3
.LC181:
	.xword	.LANCHOR0
	.align	3
.LC182:
	.xword	.LC16
	.align	3
.LC183:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IsDecFsAvailable
	.type	FSP_IsDecFsAvailable, %function
FSP_IsDecFsAvailable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L457
	ldr	w1, [x20, 84]
	mov	w0, 0
	cmp	w1, 1
	beq	.L458
.L454:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L458:
	ldr	w1, [x20]
	tst	w1, 16776960
	bne	.L454
	ldr	w1, [x20, 8]
	mov	w0, w19
	bl	FSP_IsSpecialFrm
	cmp	w0, wzr
	cset	w0, eq
	b	.L454
	.p2align 3
.L457:
	ldr	x3, .LC184
	mov	w2, 781
	ldr	x1, .LC185
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 255
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FSP_IsDecFsAvailable, .-FSP_IsDecFsAvailable
	.align	3
.LC184:
	.xword	.LC7
	.align	3
.LC185:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IfCanGetDecFs
	.type	FSP_IfCanGetDecFs, %function
FSP_IfCanGetDecFs:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L477
	cbz	x19, .L478
	ldr	x0, .LC189
	ldr	x21, [x0, w20, sxtw 3]
	cbz	x21, .L479
	add	x22, x21, 20480
	add	x23, x21, 24576
	add	x19, x22, 1680
	add	x23, x23, 400
	b	.L464
	.p2align 3
.L481:
	cmp	x19, x23
	beq	.L480
.L464:
	mov	x1, x19
	mov	w0, w20
	add	x19, x19, 88
	bl	FSP_IsDecFsAvailable
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L481
	mov	w0, 0
.L474:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L480:
	add	x2, x22, 1764
	mov	w4, 0
	mov	w1, 0
	b	.L466
	.p2align 3
.L465:
	add	w1, w1, 1
	cmp	w1, 32
	beq	.L482
.L466:
	ldr	w0, [x2]
	add	x2, x2, 88
	cmp	w0, 1
	bne	.L465
	sxtw	x3, w1
	add	w1, w1, 1
	lsl	x0, x3, 2
	sub	x0, x0, x3
	lsl	x0, x0, 2
	sub	x0, x0, x3
	add	x0, x21, x0, lsl 3
	add	x0, x0, 20480
	ldr	w0, [x0, 1680]
	and	w0, w0, 16776960
	cmp	w0, 196608
	csinc	w4, w4, w4, ne
	cmp	w1, 32
	bne	.L466
.L482:
	ldr	w0, [x21, 40]
	cmp	w0, 1088
	bgt	.L483
	ldr	x1, .LC191
	mov	w0, 4
	ldr	x1, [x1, w20, sxtw 3]
	add	x1, x1, 507904
	ldr	w1, [x1, 1732]
	cmp	w1, wzr
	csinc	w0, w0, wzr, eq
	cmp	w4, w0
	csetm	w0, le
.L484:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L483:
	mov	w0, 1
	cmp	w4, w0
	csetm	w0, le
	b	.L484
.L477:
	ldr	x3, .LC186
	mov	w2, 529
	ldr	x1, .LC187
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L474
.L479:
	ldr	x3, .LC190
	mov	w2, 531
	ldr	x1, .LC187
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L474
.L478:
	ldr	x3, .LC188
	mov	w2, 530
	ldr	x1, .LC187
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L474
	.size	FSP_IfCanGetDecFs, .-FSP_IfCanGetDecFs
	.align	3
.LC186:
	.xword	.LC7
	.align	3
.LC187:
	.xword	.LC2
	.align	3
.LC188:
	.xword	.LC113
	.align	3
.LC189:
	.xword	.LANCHOR0
	.align	3
.LC190:
	.xword	.LC16
	.align	3
.LC191:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_IsNewFsAvalible
	.type	FSP_IsNewFsAvalible, %function
FSP_IsNewFsAvalible:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	cmp	w20, 31
	bhi	.L523
	ldr	x21, .LC194
	ldr	x19, [x21, w20, sxtw 3]
	cbz	x19, .L524
	ldrsb	w0, [x19, 3]
	cbnz	w0, .L489
.L496:
	mov	w0, 1
.L521:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L489:
	mov	w0, w20
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L490
	ldrsb	w0, [x19, 3]
	cmp	w0, wzr
	ble	.L494
	mov	w22, 0
	b	.L493
	.p2align 3
.L525:
	add	w22, w22, 1
	cmp	w0, w22
	ble	.L494
.L493:
	sxtw	x2, w22
	mov	w0, w20
	lsl	x1, x2, 2
	sub	x1, x1, x2
	lsl	x1, x1, 2
	sub	x1, x1, x2
	lsl	x1, x1, 3
	add	x1, x1, 20480
	add	x1, x1, 1680
	add	x1, x19, x1
	bl	FSP_IsDecFsAvailable
	uxtb	w0, w0
	cmp	w0, 1
	ldrsb	w0, [x19, 3]
	bne	.L525
	cmp	w0, w22
	ble	.L494
.L500:
	mov	w0, w20
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L496
	ldrsb	w2, [x19, 5]
	cmp	w2, wzr
	ble	.L501
	add	x0, x19, 24576
	ldrh	w0, [x0, 3220]
	cmp	w0, 1
	beq	.L496
	mov	w1, 0
	b	.L502
	.p2align 3
.L503:
	add	x0, x19, x0, lsl 3
	ldrh	w0, [x0, 4]
	cmp	w0, 1
	beq	.L496
.L502:
	add	w1, w1, 1
	cmp	w1, w2
	sxtw	x0, w1
	add	x0, x0, 3474
	bne	.L503
.L506:
	mov	w0, w20
	bl	VCTRL_GetVidStd
	cbz	w0, .L496
	mov	w0, w20
	bl	VCTRL_GetVidStd
	cmp	w0, 16
	beq	.L496
	mov	w0, w20
	bl	VCTRL_GetVidStd
	cmp	w0, 15
	beq	.L496
	.p2align 2
.L494:
	ldr	x0, [x21, w20, sxtw 3]
	cbz	x0, .L526
	mov	w0, 0
.L527:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L490:
	ldr	x0, .LC196
	add	x22, x19, 20480
	add	x22, x22, 1680
	mov	w23, 0
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 823296
	ldr	w24, [x0, 784]
	b	.L499
	.p2align 3
.L497:
	add	w23, w23, 1
	add	x22, x22, 88
	cmp	w23, 32
	beq	.L494
.L499:
	mov	x1, x22
	mov	w0, w20
	bl	FSP_IsDecFsAvailable
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L497
	ldr	w0, [x22, 12]
	cmp	w24, w0
	bne	.L497
	cmp	w23, 31
	ble	.L500
	b	.L494
	.p2align 3
.L526:
	ldr	x1, .LC198
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L527
.L501:
	bne	.L494
	b	.L506
	.p2align 3
.L523:
	ldr	x3, .LC192
	mov	w2, 813
	ldr	x1, .LC193
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L521
.L524:
	ldr	x3, .LC195
	mov	w2, 814
	ldr	x1, .LC193
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L521
	.size	FSP_IsNewFsAvalible, .-FSP_IsNewFsAvalible
	.align	3
.LC192:
	.xword	.LC7
	.align	3
.LC193:
	.xword	.LC2
	.align	3
.LC194:
	.xword	.LANCHOR0
	.align	3
.LC195:
	.xword	.LC16
	.align	3
.LC196:
	.xword	s_pstVfmwChan
	.align	3
.LC198:
	.xword	.LC197
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_NewLogicFs
	.type	FSP_NewLogicFs, %function
FSP_NewLogicFs:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w21, 31
	bhi	.L567
	ldr	x24, .LC201
	ldr	x0, [x24, w21, sxtw 3]
	cbz	x0, .L568
	ldr	x22, .LC203
	mov	w0, 3
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x25, [x24, w21, sxtw 3]
	mov	w1, 0
	add	x0, x25, 144
	.p2align 2
.L534:
	ldrsb	w2, [x0]
	cbnz	w2, .L532
	ldrsb	w2, [x0, 1]
	cbz	w2, .L569
.L532:
	add	w1, w1, 1
	add	x0, x0, 688
	cmp	w1, 32
	bne	.L534
.L535:
	ldr	x1, .LC205
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x22, 32]
	mov	w0, 3
	blr	x1
	mov	w0, -1
.L564:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L569:
	sxtw	x23, w1
	lsl	x19, x23, 2
	sub	x19, x19, x23
	lsl	x19, x19, 2
	sub	x19, x19, x23
	lsl	x19, x19, 2
	sub	x19, x19, x23
	lsl	x19, x19, 4
	add	x0, x25, x19
	add	x19, x19, 144
	adds	x19, x25, x19
	strb	w1, [x0, 147]
	strb	wzr, [x0, 146]
	beq	.L535
	str	wzr, [x0, 152]
	stp	xzr, xzr, [x0, 176]
	cbnz	w20, .L536
	add	x1, x25, 24576
	add	x2, x25, 56
	stp	x2, x2, [x0, 176]
	mov	w2, 1
	ldr	w1, [x1, 3216]
	str	w1, [x0, 152]
	ldrb	w1, [x25, 5]
	strb	w2, [x0, 146]
	sub	w1, w1, #1
	strb	w1, [x0, 148]
.L537:
	lsl	x0, x23, 2
	mov	w1, 1
	sub	x0, x0, x23
	mov	w2, 1
	lsl	x0, x0, 2
	add	x19, x19, 48
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x0, x0, x23
	lsl	x0, x0, 4
	add	x21, x25, x0
	add	x0, x0, 192
	add	x0, x25, x0
	ldr	x3, [x21, 184]
	strb	w1, [x21, 145]
	strb	w1, [x3, 2]
	str	w2, [x21, 168]
	mov	x2, 640
	ldr	x3, [x21, 176]
	ldr	w1, [x25, 12]
	str	w1, [x21, 164]
	str	w1, [x3, 72]
	ldr	x1, [x21, 184]
	ldr	w3, [x21, 164]
	str	w3, [x1, 72]
	ldr	w1, [x25, 12]
	add	w1, w1, 1
	str	w1, [x25, 12]
	mov	w1, 0
	ldr	x3, [x22, 96]
	ldp	x20, x23, [x21, 176]
	blr	x3
	ldrsb	w0, [x21, 147]
	str	w0, [x19, 148]
	ldr	w0, [x20, 52]
	str	w0, [x19, 68]
	ldr	w0, [x20, 56]
	str	w0, [x19, 72]
	ldr	w0, [x23, 24]
	str	w0, [x19, 112]
	ldr	w0, [x23, 28]
	str	w0, [x19, 116]
	ldr	w0, [x23, 44]
	str	w0, [x19, 136]
	ldr	w0, [x23, 48]
	str	w0, [x19, 140]
	ldr	w0, [x20, 8]
	str	w0, [x19, 36]
	bl	MEM_Phy2Vir
	str	x0, [x19, 504]
	ldr	w1, [x19, 36]
	ldr	w0, [x20, 60]
	add	w0, w1, w0
	str	w0, [x19, 40]
	bl	MEM_Phy2Vir
	str	x0, [x19, 512]
	ldr	w3, [x19, 36]
	ldr	w1, [x23, 8]
	str	w1, [x19, 20]
	ldr	x2, [x19, 504]
	ldr	w0, [x23, 60]
	add	w0, w1, w0
	str	w0, [x19, 24]
	ldr	w4, [x23, 24]
	add	w1, w4, w1
	str	w1, [x19, 28]
	ldr	w1, [x23, 28]
	add	w0, w1, w0
	str	w0, [x19, 32]
	ldr	w0, [x20, 32]
	str	w0, [x19, 144]
	ldr	w0, [x20, 36]
	add	w0, w0, w3
	str	w0, [x19, 44]
	ldrsw	x0, [x20, 36]
	add	x0, x0, x2
	str	x0, [x19, 528]
	ldp	w1, w0, [x20, 36]
	add	w0, w1, w0
	add	w3, w0, w3
	str	w3, [x19, 48]
	ldpsw	x1, x0, [x20, 36]
	add	x0, x1, x0
	add	x2, x0, x2
	str	x2, [x19, 536]
	ldr	w0, [x20, 20]
	str	w0, [x19, 212]
	ldr	w0, [x20, 20]
	bl	MEM_Phy2Vir
	str	x0, [x19, 520]
	ldr	w0, [x20, 16]
	str	w0, [x19, 424]
	bl	MEM_Phy2Vir
	str	x0, [x19, 432]
	ldr	x1, [x22, 32]
	mov	w0, 3
	blr	x1
	ldrsb	w0, [x21, 147]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L536:
	mov	w0, w21
	ldr	x24, [x24, w21, sxtw 3]
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L538
	ldrsb	w0, [x24, 3]
	mov	w26, 0
	cmp	w0, wzr
	bgt	.L558
	.p2align 2
.L540:
	lsl	x20, x23, 2
	sub	x20, x20, x23
	lsl	x20, x20, 2
	sub	x20, x20, x23
	lsl	x20, x20, 2
	sub	x20, x20, x23
	add	x20, x25, x20, lsl 4
	ldr	x1, [x20, 176]
	cbz	x1, .L570
	ldrsb	w0, [x25, 5]
	cmp	w0, wzr
	ble	.L547
	mov	w0, w21
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	beq	.L548
	ldrsb	w2, [x25, 5]
	add	x4, x25, 24576
	cmp	w2, wzr
	ble	.L549
	ldrh	w0, [x4, 3220]
	cmp	w0, 1
	beq	.L550
	mov	w1, 0
	b	.L551
	.p2align 3
.L553:
	add	x0, x25, x0, lsl 3
	ldrh	w3, [x0, 4]
	cmp	w3, 1
	beq	.L571
.L551:
	add	w1, w1, 1
	cmp	w1, w2
	sxtw	x0, w1
	add	x0, x0, 3474
	bne	.L553
.L549:
	cmp	w2, wzr
	ldr	w5, [x25, 8]
	ble	.L555
.L552:
	sub	w2, w2, #1
	mov	x0, 27805
	add	x1, x4, 3221
	add	x0, x0, x2, uxtw 3
	add	x0, x25, x0
	.p2align 2
.L554:
	strb	wzr, [x1], 8
	cmp	x0, x1
	bne	.L554
.L555:
	lsl	x20, x23, 2
	ldr	x1, .LC211
	sub	x20, x20, x23
	mov	w0, 0
	lsl	x20, x20, 2
	sub	x20, x20, x23
	lsl	x20, x20, 2
	sub	x20, x20, x23
	add	x20, x25, x20, lsl 4
	strb	wzr, [x20, 148]
	ldr	w2, [x4, 3216]
	stp	w2, w5, [x20, 152]
	bl	dprint_vfmw
	ldr	x1, [x20, 176]
	.p2align 2
.L547:
	lsl	x0, x23, 2
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x0, x0, x23
	add	x0, x25, x0, lsl 4
	str	x1, [x0, 184]
	b	.L537
	.p2align 3
.L572:
	ldrsb	w0, [x24, 3]
	cmp	w26, w0
	bge	.L540
.L558:
	sxtw	x20, w26
	mov	w0, w21
	lsl	x1, x20, 2
	add	w26, w26, 1
	sub	x1, x1, x20
	lsl	x1, x1, 2
	sub	x20, x1, x20
	lsl	x20, x20, 3
	add	x20, x20, 20480
	add	x20, x20, 1680
	add	x20, x24, x20
	mov	x1, x20
	bl	FSP_IsDecFsAvailable
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L572
	str	x20, [x19, 32]
	b	.L540
.L538:
	ldr	x0, .LC206
	add	x20, x24, 20480
	add	x24, x24, 24576
	add	x20, x20, 1680
	add	x24, x24, 400
	ldr	x0, [x0, w21, sxtw 3]
	add	x0, x0, 823296
	ldr	w26, [x0, 784]
	b	.L545
	.p2align 3
.L544:
	add	x20, x20, 88
	cmp	x20, x24
	beq	.L540
.L545:
	mov	x1, x20
	mov	w0, w21
	bl	FSP_IsDecFsAvailable
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L544
	ldr	w0, [x20, 12]
	cmp	w26, w0
	bne	.L544
	str	x20, [x19, 32]
	b	.L540
.L571:
	lsl	x3, x23, 2
	cmp	w1, w2
	sub	x3, x3, x23
	lsl	x3, x3, 2
	sub	x3, x3, x23
	lsl	x3, x3, 2
	sub	x3, x3, x23
	add	x3, x25, x3, lsl 4
	strb	w1, [x3, 148]
	ldr	w0, [x0]
	str	w0, [x3, 152]
	ldr	w5, [x25, 8]
	str	w5, [x3, 156]
	bge	.L552
.L556:
	lsl	x0, x23, 2
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x0, x0, x23
	add	x0, x25, x0, lsl 4
	ldr	x1, [x0, 176]
	b	.L547
.L548:
	add	x0, x25, 24576
	strb	wzr, [x20, 148]
	ldr	x1, [x20, 176]
	ldr	w0, [x0, 3216]
	str	w0, [x20, 152]
	ldr	w0, [x25, 8]
	str	w0, [x20, 156]
	b	.L547
.L567:
	ldr	x3, .LC199
	mov	w2, 908
	ldr	x1, .LC200
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L564
.L568:
	ldr	x3, .LC202
	mov	w2, 909
	ldr	x1, .LC200
	bl	dprint_vfmw
	mov	w0, -1
	b	.L564
.L550:
	strb	wzr, [x20, 148]
	ldr	w0, [x4, 3216]
	str	w0, [x20, 152]
	ldr	w0, [x25, 8]
	str	w0, [x20, 156]
	b	.L556
.L570:
	ldr	x2, .LC207
	mov	w0, 0
	ldr	x1, .LC209
	bl	dprint_vfmw
	ldr	x1, [x22, 32]
	mov	w0, 3
	blr	x1
	mov	w0, -1
	b	.L564
	.size	FSP_NewLogicFs, .-FSP_NewLogicFs
	.align	3
.LC199:
	.xword	.LC7
	.align	3
.LC200:
	.xword	.LC2
	.align	3
.LC201:
	.xword	.LANCHOR0
	.align	3
.LC202:
	.xword	.LC16
	.align	3
.LC203:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC205:
	.xword	.LC204
	.align	3
.LC206:
	.xword	s_pstVfmwChan
	.align	3
.LC207:
	.xword	.LANCHOR1
	.align	3
.LC209:
	.xword	.LC208
	.align	3
.LC211:
	.xword	.LC210
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_SetSingleFrameBuf
	.type	FSP_SetSingleFrameBuf, %function
FSP_SetSingleFrameBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L620
	ldr	x0, .LC214
	mov	w7, 32
	ldr	x8, [x0, w20, sxtw 3]
	add	x0, x8, 503808
	add	x4, x8, 507904
	ldr	w1, [x0, 1636]
	ldr	w0, [x4, 1096]
	cmp	w1, w7
	csel	w7, w1, w7, le
	str	w7, [x4, -88]
	ldr	w1, [x19]
	cmp	w1, 255
	beq	.L593
	ldrb	w1, [x4, 336]
	cbz	w1, .L594
	add	x2, x4, 348
	mov	x3, 1
	b	.L578
	.p2align 3
.L622:
	add	w3, w3, 1
	cmp	w3, 32
	beq	.L621
.L578:
	ldrb	w5, [x2]
	add	x2, x2, 12
	cbnz	w5, .L622
.L577:
	uxtw	x5, w3
	sub	x6, x4, #136
	lsl	x1, x5, 2
	ldr	w2, [x19, 32]
	sub	x1, x1, x5
	mov	w9, 1
	add	w2, w2, 1023
	add	x5, x5, 20
	add	x1, x6, x1, lsl 2
	and	w2, w2, -1024
	add	w0, w0, w2
	str	w2, [x1, 464]
	ldr	w2, [x19, 12]
	str	w2, [x1, 468]
	strb	w9, [x1, 472]
	ldr	w2, [x4, -76]
	add	w2, w2, 1
	str	w2, [x4, -76]
	str	w0, [x6, x5, lsl 2]
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L576
	ldr	w0, [x19, 48]
	str	w0, [x1, 848]
	strb	w9, [x1, 856]
	ldr	w0, [x4, -68]
	add	w0, w0, 1
	str	w0, [x4, -68]
.L576:
	ldr	w0, [x19, 8]
	cmp	w0, 255
	beq	.L591
	ldrb	w0, [x4, 76]
	cbz	w0, .L623
	add	x2, x4, 84
	mov	w0, 1
	b	.L581
	.p2align 3
.L624:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L591
.L581:
	ldrb	w5, [x2]
	add	x2, x2, 8
	cbnz	w5, .L624
.L580:
	add	x0, x8, x0, uxtw 3
	ldr	w2, [x19, 64]
	add	x0, x0, 507904
	mov	w1, 1
	str	w2, [x0, 72]
	strb	w1, [x0, 76]
	ldr	w0, [x4, -72]
	add	w0, w0, 1
	str	w0, [x4, -72]
.L591:
	ldr	x0, .LC215
	ldr	x6, [x0, w20, sxtw 3]
	add	x8, x6, 20480
	strb	w7, [x6, 3]
	strb	wzr, [x6, 4]
	ldrsb	w7, [x4, -80]
	strb	w7, [x6, 5]
	ldr	w0, [x8, 1764]
	cbz	w0, .L595
	add	x2, x8, 1852
	mov	x0, 1
	b	.L584
	.p2align 3
.L583:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L625
.L584:
	ldr	w5, [x2]
	add	x2, x2, 88
	cbnz	w5, .L583
	mov	w9, w0
.L582:
	lsl	x2, x0, 2
	ldr	w5, [x6, 16]
	sub	x2, x2, x0
	lsl	x1, x3, 2
	lsl	x2, x2, 2
	sub	x1, x1, x3
	sub	x0, x2, x0
	add	w2, w5, 1
	sub	x5, x4, #136
	str	w2, [x6, 16]
	add	x0, x6, x0, lsl 3
	add	x1, x5, x1, lsl 2
	add	x0, x0, 20480
	add	x3, x3, 20
	add	x2, x6, 36
	str	w9, [x0, 1684]
	mov	w9, 1
	ldr	w10, [x1, 464]
	str	w10, [x0, 1688]
	ldr	w1, [x1, 468]
	str	w1, [x0, 1692]
	ldr	w1, [x5, x3, lsl 2]
	str	w1, [x0, 1700]
	ldr	w1, [x4, -132]
	str	w1, [x0, 1704]
	ldr	w1, [x4, -128]
	str	w1, [x0, 1708]
	ldr	w1, [x4, -116]
	str	w1, [x0, 1712]
	ldr	w1, [x4, -108]
	str	w1, [x0, 1716]
	ldr	w1, [x4, -104]
	str	w1, [x0, 1720]
	ldr	w1, [x4, -124]
	str	w1, [x0, 1724]
	ldr	w1, [x4, -120]
	str	w1, [x0, 1728]
	mov	x1, x2
	ldr	w2, [x2, 4]
	str	w2, [x0, 1732]
	ldr	w3, [x1, 8]
	str	w3, [x0, 1736]
	ldr	w1, [x4, -100]
	str	w1, [x0, 1740]
	ldr	w1, [x4, -96]
	str	w1, [x0, 1744]
	ldr	w1, [x4, -92]
	str	w1, [x0, 1748]
	str	w9, [x0, 1764]
	strb	wzr, [x0, 1681]
	strb	wzr, [x0, 1682]
	ldr	w0, [x6, 20]
	cmp	w0, w7
	bcs	.L586
	ldr	w1, [x19, 8]
	cmp	w1, 255
	beq	.L586
	uxtw	x1, w0
	add	w0, w0, 1
	add	x5, x5, x1, lsl 3
	add	x1, x6, x1, lsl 3
	add	x1, x1, 24576
	ldr	w5, [x5, 208]
	str	w5, [x1, 3216]
	strb	wzr, [x1, 3221]
	strb	w9, [x1, 3220]
	str	w0, [x6, 20]
.L586:
	ldr	w0, [x4, -88]
	sub	x10, x4, #136
	ldr	w1, [x6, 24]
	cmp	w1, w0
	bcc	.L626
.L587:
	ldr	w0, [x4, -84]
	ldr	w1, [x6, 140]
	str	w0, [x6, 8]
	mov	w0, 0
	cbnz	w1, .L606
	str	wzr, [x6, 60]
	mov	w1, 1
	ldr	w5, [x8, 1688]
	str	w5, [x6, 64]
	ldr	w5, [x4, -132]
	str	w5, [x6, 80]
	ldr	w5, [x4, -128]
	str	w5, [x6, 84]
	stp	w2, w3, [x6, 108]
	ldr	w2, [x4, -100]
	str	w2, [x6, 116]
	ldr	w2, [x4, -96]
	str	w2, [x6, 120]
	ldr	w2, [x4, -92]
	str	w2, [x6, 124]
	strb	wzr, [x6, 57]
	strb	wzr, [x6, 58]
	str	w1, [x6, 140]
.L606:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L626:
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L587
	uxtw	x9, w1
	ldr	w5, [x4, -68]
	lsl	x0, x9, 2
	add	w1, w1, 1
	sub	w5, w5, #1
	sub	x0, x0, x9
	lsl	x0, x0, 2
	lsl	x7, x5, 2
	sub	x0, x0, x9
	sub	x5, x7, x5
	add	x0, x6, x0, lsl 3
	add	x5, x10, x5, lsl 2
	add	x0, x0, 20480
	ldr	w5, [x5, 848]
	str	w5, [x0, 1696]
	str	w1, [x6, 24]
	b	.L587
	.p2align 3
.L625:
	ldr	x2, .LC216
	mov	w0, 1
	ldr	x1, .LC220
	add	x2, x2, 16
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L593:
	mov	x3, 0
	b	.L576
	.p2align 3
.L621:
	ldr	x2, .LC216
	mov	w0, 1
	ldr	x1, .LC218
	add	x2, x2, 16
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L595:
	mov	w9, 0
	mov	x0, 0
	b	.L582
.L594:
	mov	x3, 0
	b	.L577
.L623:
	mov	w0, 0
	b	.L580
.L620:
	ldr	x3, .LC212
	mov	w2, 1688
	ldr	x1, .LC213
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L606
	.size	FSP_SetSingleFrameBuf, .-FSP_SetSingleFrameBuf
	.align	3
.LC212:
	.xword	.LC7
	.align	3
.LC213:
	.xword	.LC2
	.align	3
.LC214:
	.xword	s_pstVfmwChan
	.align	3
.LC215:
	.xword	.LANCHOR0
	.align	3
.LC216:
	.xword	.LANCHOR1
	.align	3
.LC218:
	.xword	.LC217
	.align	3
.LC220:
	.xword	.LC219
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FSP_GetInst
	.type	FSP_GetInst, %function
FSP_GetInst:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L630
	ldr	x0, .LC224
	ldr	x0, [x0, w19, sxtw 3]
.L629:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L630:
	ldr	x2, .LC221
	mov	w3, w19
	ldr	x1, .LC223
	mov	w0, 1
	add	x2, x2, 40
	bl	dprint_vfmw
	mov	x0, 0
	b	.L629
	.size	FSP_GetInst, .-FSP_GetInst
	.align	3
.LC221:
	.xword	.LANCHOR1
	.align	3
.LC223:
	.xword	.LC222
	.align	3
.LC224:
	.xword	.LANCHOR0
	.global	s_pFspInst
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.11603, %object
	.size	__func__.11603, 15
__func__.11603:
	.string	"FSP_NewLogicFs"
	.zero	1
	.type	__func__.11795, %object
	.size	__func__.11795, 22
__func__.11795:
	.string	"FSP_SetSingleFrameBuf"
	.zero	2
	.type	__func__.11805, %object
	.size	__func__.11805, 12
__func__.11805:
	.string	"FSP_GetInst"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"pFspInst = NULL" )
.LC2:
	ASCII(.string	"fsp.c,L%d: %s\n" )
	.zero	1
.LC7:
	ASCII(.string	"InstID out of range" )
	.zero	4
.LC11:
	ASCII(.string	"fsp instance not in used" )
	.zero	7
.LC16:
	ASCII(.string	"fsp is not inited" )
	.zero	6
.LC22:
	ASCII(.string	"fsp is already inited" )
	.zero	2
.LC38:
	ASCII(.string	"pstFspInstCfg = NULL" )
	.zero	3
.LC41:
	ASCII(.string	"This inst is not active" )
.LC51:
	ASCII(.string	"user set decode channel max resolution is (w=%d,h=%d), this stream (w=%d,h=%d) can NOT be decoded!\n" )
	.zero	4
.LC55:
	ASCII(.string	"DFS, Wrong Partition State. State: 0x%x\n" )
	.zero	7
.LC57:
	ASCII(.string	"DFS, Mem Element Fill Successed! Ready to Decode!\n" )
	.zero	5
.LC59:
	ASCII(.string	"Fsp arrange failed, return %d\n" )
	.zero	1
.LC61:
	ASCII(.string	"arrange ret %d, min = %d, actual = %d\n" )
	.zero	1
.LC85:
	ASCII(.string	"LogicFrameID out of range" )
	.zero	6
.LC94:
	ASCII(.string	"fsp.c, line %d: pstLogicFs->PmvIdc out of range(=%d)\n" )
	.zero	2
.LC96:
	ASCII(.string	"FSP_GetRef: InstID out of range" )
.LC99:
	ASCII(.string	"FSP_GetRef: LogicFrameID out of range" )
	.zero	2
.LC109:
	ASCII(.string	"FSP_SetDisplay: LogicTick=%d, DispTick=%d!\n" )
	.zero	4
.LC113:
	ASCII(.string	"pstVoQue is NULL" )
	.zero	7
.LC126:
	ASCII(.string	"PhyFsID out of range" )
	.zero	3
.LC143:
	ASCII(.string	"DecFsAddrTab is NULL\n" )
	.zero	2
.LC145:
	ASCII(.string	"DecFsNum is NULL\n" )
	.zero	6
.LC151:
	ASCII(.string	"PmvAddrTab is NULL\n" )
	.zero	4
.LC153:
	ASCII(.string	"PmvNum is NULL\n" )
.LC197:
	ASCII(.string	"FSP_IsFsLeak: fsp is not inited \n" )
	.zero	6
.LC204:
	ASCII(.string	"no logic frame store!!!\n" )
	.zero	7
.LC208:
	ASCII(.string	"%s no decode phy fs\n" )
	.zero	3
.LC210:
	ASCII(.string	"no pmv memory\n" )
	.zero	1
.LC217:
	ASCII(.string	"%s no free frame record position.\n" )
	.zero	5
.LC219:
	ASCII(.string	"%s no free dec fs record position.\n" )
	.zero	4
.LC222:
	ASCII(.string	"%s InstID %d out of range\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	s_pFspInst, %object
	.size	s_pFspInst, 256
s_pFspInst:
	.zero	256
	.type	MemArrange.11553, %object
	.size	MemArrange.11553, 1232
MemArrange.11553:
	.zero	1232
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
