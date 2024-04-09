#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vp8.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VP8_init_frame.part.0, %function
VP8_init_frame.part.0:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC0
	ldr	x21, .LC1
	mov	x2, 38
	add	x0, x19, 2382
	ldr	x3, [x20, 104]
	mov	x1, x21
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 40
	mov	x2, 1056
	add	x0, x19, 1326
	blr	x3
	ldr	x21, .LC2
	ldr	x3, [x20, 104]
	mov	x2, 4
	mov	x1, x21
	add	x0, x19, 1318
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x21, 8
	mov	x2, 3
	add	x0, x19, 1322
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 8
	mov	w1, 0
	add	x0, x19, 22
	blr	x3
	strb	wzr, [x19, 17]
	mov	x2, 4
	mov	w1, 0
	ldr	x3, [x20, 96]
	add	x0, x19, 40
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 4
	mov	w1, 0
	add	x0, x19, 44
	blr	x3
	strb	wzr, [x19, 51]
	strb	wzr, [x19, 52]
	mov	w0, 1
	strb	wzr, [x19, 56]
	strb	w0, [x19, 49]
	strb	w0, [x19, 50]
	strb	wzr, [x19, 57]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP8_init_frame.part.0, .-VP8_init_frame.part.0
	.align	3
.LC0:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp8_Vfmw_StartBoolDecode
	.type	Vp8_Vfmw_StartBoolDecode, %function
Vp8_Vfmw_StartBoolDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	w1, 255
	mov	w0, 16
	str	w1, [x19]
	mov	w1, 24
	str	w0, [x19, 8]
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Vp8_Vfmw_StartBoolDecode, .-Vp8_Vfmw_StartBoolDecode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp8_Vfmw_DecodeBool
	.type	Vp8_Vfmw_DecodeBool, %function
Vp8_Vfmw_DecodeBool:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	uxtb	w19, w2
	mov	x23, x1
	bl	_mcount
	mov	w24, 0
	ldp	w3, w0, [x22]
	ldr	w25, [x22, 8]
	sub	w1, w3, #1
	mul	w1, w1, w19
	lsr	w1, w1, 8
	add	w1, w1, 1
	lsl	w2, w1, 16
	cmp	w0, w2
	bcc	.L4
	sub	w1, w3, w1
	sub	w0, w0, w2
	mov	w24, 1
.L4:
	ldr	x2, .LC3
	add	x2, x2, 1096
	ldrb	w20, [x2, w1, uxtw]
	subs	w25, w25, w20
	lsl	w21, w1, w20
	lsl	w20, w0, w20
	bmi	.L10
.L5:
	stp	w21, w20, [x22]
	str	w25, [x22, 8]
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L10:
	mov	w0, 8
	subs	w26, w0, w25
	bmi	.L5
	mov	w19, w26
	.p2align 2
.L6:
	mov	w1, 8
	mov	x0, x23
	bl	BsGet
	lsl	w0, w0, w19
	subs	w19, w19, #8
	orr	w20, w20, w0
	bpl	.L6
	add	w25, w25, 8
	and	w0, w26, -8
	add	w25, w0, w25
	b	.L5
	.size	Vp8_Vfmw_DecodeBool, .-Vp8_Vfmw_DecodeBool
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vp8_Vfmw_DecodeValue
	.type	Vp8_Vfmw_DecodeValue, %function
Vp8_Vfmw_DecodeValue:
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
	bmi	.L12
	.p2align 2
.L13:
	mov	w2, -128
	mov	x1, x22
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w20, w0, w20
	cmn	w19, #1
	bne	.L13
.L12:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Vp8_Vfmw_DecodeValue, .-Vp8_Vfmw_DecodeValue
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_SetImgFormat
	.type	VP8_SetImgFormat, %function
VP8_SetImgFormat:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 3248
	bl	_mcount
	ldr	w1, [x20, 8216]
	ldr	w0, [x20, 8840]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L16
	ldr	w2, [x20, 8224]
	mov	w4, 1
	ldrb	w3, [x0, 64]
	mov	w5, 5
	ldrb	w1, [x0, 65]
	bfi	w3, w2, 0, 2
	and	w2, w2, 3
	and	w1, w1, -4
	and	w3, w3, -29
	orr	w1, w1, 12
	bfi	w3, w5, 5, 3
	bfi	w1, w4, 4, 2
	strb	w3, [x0, 64]
	strb	w1, [x0, 65]
	mov	w3, 8
	mov	w5, 13
	ldr	w1, [x0, 64]
	and	w1, w1, -114689
	str	w1, [x0, 64]
	lsr	w1, w1, 16
	ldrb	w6, [x21, 2500]
	bfi	w1, w6, 1, 1
	strb	w1, [x0, 66]
	mov	w1, 0
	ldr	w6, [x20, 5752]
	stp	w2, w2, [x0, 56]
	add	x2, x0, 256
	strb	wzr, [x0, 284]
	strb	w4, [x0, 291]
	strb	w4, [x0, 289]
	str	w6, [x0, 120]
	stp	w5, w3, [x2, 40]
	stp	w3, w3, [x2, 48]
	bl	SetAspectRatio
	ldr	w1, [x20, 5828]
	str	w1, [x19, 68]
	ldr	w0, [x20, 5832]
	str	w0, [x19, 72]
	ldr	x2, [x20]
	ldr	w2, [x2, 28]
	cmp	w2, 25
	beq	.L22
.L18:
	lsr	w3, w1, 1
	lsr	w2, w0, 1
	stp	w1, w0, [x19, 76]
	stp	w3, w2, [x19, 84]
.L16:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L22:
	ldr	w5, [x19, 112]
	add	w2, w0, 15
	lsr	w3, w2, 4
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
	b	.L18
	.size	VP8_SetImgFormat, .-VP8_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8DEC_VDMPostProc
	.type	VP8DEC_VDMPostProc, %function
VP8DEC_VDMPostProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x20, .L93
	ldr	x3, [x20, 8]
	add	x2, x20, 4096
	mov	x1, x20
	mov	w0, 13
	add	x19, x20, 3248
	ldrb	w4, [x3, 2778]
	strb	w4, [x2, 1652]
	ldr	w3, [x3, 3144]
	str	w3, [x20, 5752]
	bl	ReleasePacket
	ldr	w1, [x19, 4968]
	ldr	w0, [x20, 8840]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L94
	tbnz	w21, #31, .L27
	cmp	w21, 100
	mov	w2, 100
	csel	w2, w21, w2, le
	str	w2, [x0, 152]
	ldr	x0, [x20]
	ldr	w3, [x0]
	cmp	w2, w3
	bhi	.L95
	mov	x0, x20
	bl	VP8_SetImgFormat
	ldr	w0, [x19, 4932]
	cmp	w0, 2
	beq	.L96
.L29:
	ldr	w0, [x20, 3324]
	cbnz	w0, .L31
.L30:
	mov	w0, -1
	str	w0, [x19, 4972]
	ldr	w1, [x19, 4968]
	mov	w2, 0
	ldr	w0, [x20, 8840]
	bl	FSP_SetDisplay
	ldr	w1, [x19, 4972]
.L32:
	cmn	w1, #1
	beq	.L33
	ldr	w0, [x20, 8840]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L97
	ldr	w1, [x19, 4972]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_SetDisplay
	add	x3, x20, 8192
	ldr	w0, [x20, 8840]
	mov	x4, x22
	add	x3, x3, 40
	mov	x2, x20
	mov	w1, 13
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w21, w0
	bne	.L98
.L33:
	ldr	w0, [x19, 4936]
	add	x21, x20, 3256
	ldr	w1, [x19, 4976]
	add	w0, w0, 1
	str	w0, [x19, 4936]
	ldr	w22, [x19, 4964]
	cbz	w1, .L35
	ldrb	w0, [x21, 48]
	mov	w23, 0
	cbnz	w0, .L35
	ldrb	w0, [x21, 52]
	cmp	w0, 1
	beq	.L99
.L40:
	cmp	w0, 2
	beq	.L100
.L42:
	ldrb	w0, [x21, 51]
	cmp	w0, 1
	beq	.L101
.L45:
	cmp	w0, 2
	beq	.L102
.L47:
	ldr	w0, [x19, 4976]
	cbz	w0, .L50
	ldrb	w0, [x21, 49]
	cbz	w0, .L51
.L50:
	ldr	w3, [x19, 4956]
	ldr	w0, [x19, 4964]
	cmp	w3, w0
	beq	.L91
	ldr	w0, [x19, 4960]
	cmp	w3, w0
	beq	.L91
	ldr	w1, [x19, 4968]
	cmp	w3, w1
	beq	.L53
	ldr	w0, [x20, 8840]
	mov	w2, 0
	mov	w1, w3
	bl	FSP_SetRef
.L91:
	ldr	w1, [x19, 4968]
.L53:
	str	w1, [x19, 4956]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_SetRef
.L51:
	ldr	w0, [x21, 64]
	cbz	w0, .L55
	ldrb	w0, [x21, 50]
	cbz	w0, .L56
.L55:
	ldr	w3, [x19, 4960]
	ldr	w0, [x19, 4964]
	cmp	w3, w0
	beq	.L92
	ldr	w0, [x19, 4956]
	cmp	w3, w0
	beq	.L92
	ldr	w1, [x19, 4968]
	cmp	w3, w1
	beq	.L58
	ldr	w0, [x20, 8840]
	mov	w2, 0
	mov	w1, w3
	bl	FSP_SetRef
.L92:
	ldr	w1, [x19, 4968]
.L58:
	str	w1, [x19, 4960]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_SetRef
.L56:
	mov	w21, 1
	cbnz	w23, .L103
.L80:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L31:
	ldr	w1, [x19, 4968]
	str	w1, [x19, 4972]
	b	.L32
	.p2align 3
.L35:
	ldr	w0, [x19, 4956]
	cmp	w22, w0
	beq	.L39
	ldr	w0, [x19, 4960]
	cmp	w22, w0
	beq	.L39
	ldr	w1, [x19, 4968]
	cmp	w22, w1
	cset	w23, ne
.L38:
	str	w1, [x19, 4964]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_SetRef
	ldrb	w0, [x21, 52]
	cmp	w0, 1
	bne	.L40
.L99:
	ldr	w1, [x19, 4960]
	ldr	w0, [x19, 4964]
	cmp	w1, w0
	beq	.L41
	ldr	w0, [x19, 4956]
	cmp	w0, w1
	ccmp	w22, w1, 4, ne
	beq	.L41
	ldr	w0, [x20, 8840]
	mov	w2, 0
	bl	FSP_SetRef
.L41:
	str	w22, [x19, 4960]
	mov	w2, 1
	mov	w1, w22
	mov	w23, 0
	ldr	w0, [x20, 8840]
	bl	FSP_SetRef
	ldrb	w0, [x21, 51]
	cmp	w0, 1
	bne	.L45
.L101:
	ldr	w1, [x19, 4956]
	ldr	w0, [x19, 4964]
	cmp	w1, w0
	beq	.L46
	ldr	w0, [x19, 4960]
	cmp	w0, w1
	ccmp	w22, w1, 4, ne
	beq	.L46
	ldr	w0, [x20, 8840]
	mov	w2, 0
	bl	FSP_SetRef
.L46:
	str	w22, [x19, 4956]
	mov	w2, 1
	mov	w1, w22
	mov	w23, 0
	ldr	w0, [x20, 8840]
	bl	FSP_SetRef
	b	.L47
	.p2align 3
.L39:
	mov	w23, 0
	ldr	w1, [x19, 4968]
	b	.L38
	.p2align 3
.L27:
	str	wzr, [x0, 152]
	mov	x0, x20
	bl	VP8_SetImgFormat
	ldr	w0, [x19, 4932]
	cmp	w0, 2
	bne	.L29
.L96:
	ldr	w0, [x19, 4976]
	cbnz	w0, .L30
	b	.L29
	.p2align 3
.L98:
	ldr	w0, [x20, 8840]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x20, 8840]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	mov	w2, 0
	ldr	w1, [x19, 4972]
	ldr	w0, [x20, 8840]
	bl	FSP_SetDisplay
	ldr	x1, .LC14
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L100:
	ldr	w3, [x19, 4960]
	ldr	w0, [x19, 4964]
	ldr	w1, [x19, 4956]
	cmp	w3, w0
	beq	.L44
	cmp	w3, w1
	beq	.L44
	ldr	w0, [x20, 8840]
	mov	w1, w3
	mov	w2, 0
	bl	FSP_SetRef
	ldr	w1, [x19, 4956]
.L44:
	str	w1, [x19, 4960]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_SetRef
	b	.L42
	.p2align 3
.L102:
	ldr	w3, [x19, 4956]
	ldr	w0, [x19, 4964]
	ldr	w1, [x19, 4960]
	cmp	w3, w0
	beq	.L49
	cmp	w3, w1
	beq	.L49
	ldr	w0, [x20, 8840]
	mov	w1, w3
	mov	w2, 0
	bl	FSP_SetRef
	ldr	w1, [x19, 4960]
.L49:
	str	w1, [x19, 4956]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_SetRef
	b	.L47
	.p2align 3
.L103:
	ldr	w0, [x20, 8840]
	mov	w1, w22
	mov	w2, 0
	bl	FSP_SetRef
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L93:
	ldr	x1, .LC6
	mov	w2, 581
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L95:
	ldr	x1, .LC10
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	ldr	w1, [x19, 4956]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_ClearLogicFs
	ldr	w1, [x19, 4960]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_ClearLogicFs
	ldr	w1, [x19, 4964]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_ClearLogicFs
	str	wzr, [x19, 4956]
	str	wzr, [x19, 4960]
	str	wzr, [x19, 4964]
	ldr	w0, [x20, 8840]
	bl	FSP_GetNullLogicFs
	str	wzr, [x19, 4936]
	str	w0, [x19, 4956]
	str	w0, [x19, 4960]
	str	w0, [x19, 4964]
	b	.L80
.L97:
	ldr	x1, .LC12
	mov	w2, 626
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L80
.L94:
	ldr	x1, .LC8
	mov	w21, -1
	bl	dprint_vfmw
	b	.L80
	.size	VP8DEC_VDMPostProc, .-VP8DEC_VDMPostProc
	.align	3
.LC6:
	.xword	.LC5
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC14:
	.xword	.LC13
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8DEC_Init
	.type	VP8DEC_Init, %function
VP8DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L108
	ldr	x3, .LC16
	mov	x2, 8856
	mov	w1, 0
	mov	x0, x19
	ldr	w21, [x19, 8832]
	ldr	x3, [x3, 96]
	blr	x3
	str	w21, [x19, 8832]
	add	x0, x19, 8192
	add	x0, x0, 40
	bl	ResetVoQueue
	str	x20, [x19]
	mov	x0, x19
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 8840]
	beq	.L109
	mov	w2, 1024
	str	w2, [x19, 8176]
	ldr	x2, [x19]
	mov	w3, 3
	str	wzr, [x19, 8188]
	mov	w0, 1
	ldr	w4, [x2, 8]
	str	w4, [x19, 8180]
	str	w3, [x19, 8192]
	str	wzr, [x19, 8196]
	str	w3, [x19, 8228]
	ldr	w2, [x2, 40]
	str	w2, [x19, 8200]
.L106:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L108:
	ldr	x1, .LC15
	mov	w2, 760
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L109:
	ldr	x1, .LC18
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L106
	.size	VP8DEC_Init, .-VP8DEC_Init
	.align	3
.LC15:
	.xword	.LC5
	.align	3
.LC16:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC18:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8DEC_Destroy
	.type	VP8DEC_Destroy, %function
VP8DEC_Destroy:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VP8DEC_Destroy, .-VP8DEC_Destroy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_setup_version
	.type	VP8_setup_version, %function
VP8_setup_version:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 72]
	cmp	w0, 3
	bls	.L121
.L112:
	stp	wzr, wzr, [x19, 84]
	stp	wzr, wzr, [x19, 92]
	str	wzr, [x19, 100]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L121:
	ldr	x1, .LC19
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx114
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx114:
	.section	.rodata
	.align	0
	.align	2
.L114:
	.byte	(.L112 - .Lrtx114) / 4
	.byte	(.L115 - .Lrtx114) / 4
	.byte	(.L116 - .Lrtx114) / 4
	.byte	(.L117 - .Lrtx114) / 4
	.text
	.p2align 3
.L116:
	mov	w0, 1
	stp	w0, wzr, [x19, 84]
	stp	w0, wzr, [x19, 92]
.L119:
	mov	w0, 1
	str	w0, [x19, 100]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L115:
	mov	w0, 1
	stp	wzr, w0, [x19, 84]
	stp	w0, wzr, [x19, 92]
	b	.L119
	.p2align 3
.L117:
	mov	w0, 1
	stp	w0, w0, [x19, 84]
	stp	w0, w0, [x19, 92]
	b	.L119
	.size	VP8_setup_version, .-VP8_setup_version
	.align	3
.LC19:
	.xword	.L114
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	read_mvcontexts
	.type	read_mvcontexts, %function
read_mvcontexts:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	mov	x22, x1
	mov	x28, x2
	bl	_mcount
	ldr	x27, .LC22
	mov	x26, 0
.L127:
	add	x24, x27, x26
	add	x25, x28, x26
	mov	x21, 0
	.p2align 2
.L126:
	ldrb	w2, [x24, x21]
	mov	x1, x22
	mov	x0, x23
	bl	Vp8_Vfmw_DecodeBool
	cbz	w0, .L123
	mov	w20, 0
	mov	w19, 6
	.p2align 2
.L124:
	mov	w2, -128
	mov	x1, x22
	mov	x0, x23
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w20, w0, w20
	cmn	w19, #1
	bne	.L124
	uxtb	w20, w20
	mov	w0, 1
	ubfiz	w1, w20, 1, 7
	cmp	w20, wzr
	csel	w0, w1, w0, ne
	strb	w0, [x25, x21]
.L123:
	add	x21, x21, 1
	cmp	x21, 19
	bne	.L126
	add	x26, x26, 19
	cmp	x26, 38
	bne	.L127
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.size	read_mvcontexts, .-read_mvcontexts
	.align	3
.LC22:
	.xword	.LANCHOR2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_mb_mode_mv_init
	.type	VP8_mb_mode_mv_init, %function
VP8_mb_mode_mv_init:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	bl	_mcount
	ldr	w0, [x23, 64]
	cbz	w0, .L136
	mov	w22, 0
	mov	w21, 7
	.p2align 2
.L138:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x19
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L138
	strb	w22, [x23, 58]
	mov	w21, 7
	mov	w22, 0
	.p2align 2
.L139:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x19
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L139
	strb	w22, [x23, 59]
	mov	w21, 7
	mov	w22, 0
	.p2align 2
.L140:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x19
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L140
	strb	w22, [x23, 60]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x19
	bl	Vp8_Vfmw_DecodeBool
	cmp	w0, 1
	beq	.L141
	mov	w2, -128
	mov	x1, x20
	mov	x0, x19
	bl	Vp8_Vfmw_DecodeBool
	cbz	w0, .L143
.L142:
	add	x24, x23, 1322
	add	x25, x23, 1325
.L148:
	mov	w22, 0
	mov	w21, 7
	.p2align 2
.L147:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x19
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L147
	strb	w22, [x24], 1
	cmp	x25, x24
	bne	.L148
.L143:
	add	x2, x23, 2382
	mov	x1, x20
	mov	x0, x19
	bl	read_mvcontexts
.L136:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L141:
	add	x24, x23, 1318
	add	x25, x23, 1322
.L145:
	mov	w22, 0
	mov	w21, 7
	.p2align 2
.L144:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x19
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w21
	sub	w21, w21, #1
	orr	w22, w0, w22
	cmn	w21, #1
	bne	.L144
	strb	w22, [x24], 1
	cmp	x24, x25
	bne	.L145
	mov	w2, -128
	mov	x1, x20
	mov	x0, x19
	bl	Vp8_Vfmw_DecodeBool
	cbnz	w0, .L142
	b	.L143
	.size	VP8_mb_mode_mv_init, .-VP8_mb_mode_mv_init
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	get_delta_q
	.type	get_delta_q, %function
get_delta_q:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	mov	w23, w2
	mov	x24, x3
	bl	_mcount
	mov	w2, -128
	mov	x1, x22
	mov	x0, x21
	mov	w19, 0
	bl	Vp8_Vfmw_DecodeBool
	cbz	w0, .L160
	mov	w20, 3
.L161:
	mov	w2, -128
	mov	x1, x22
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w20
	sub	w20, w20, #1
	orr	w19, w0, w19
	cmn	w20, #1
	bne	.L161
	mov	w2, -128
	mov	x1, x22
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	cmp	w0, wzr
	csneg	w19, w19, w19, eq
.L160:
	cmp	w19, w23
	beq	.L162
	mov	w0, 1
	str	w0, [x24]
.L162:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	get_delta_q, .-get_delta_q
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_init_frame
	.type	VP8_init_frame, %function
VP8_init_frame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 64]
	cbnz	w0, .L168
	mov	x0, x19
	bl	VP8_init_frame.part.0
.L168:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP8_init_frame, .-VP8_init_frame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_GetPictureHeader
	.type	VP8_GetPictureHeader, %function
VP8_GetPictureHeader:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x27, x1
	mov	w23, w2
	bl	_mcount
	add	x25, x27, 2468
	mov	w2, 7
	mov	w1, 8
	str	w2, [x29, 136]
	mov	x0, x20
	mov	w2, 6
	str	w2, [x29, 140]
	bl	BsGet
	mov	w19, w0
	mov	w1, 8
	mov	x0, x20
	uxtb	w21, w19
	bl	BsGet
	mov	w22, w0
	mov	w1, 8
	mov	x0, x20
	ubfiz	w22, w22, 8, 8
	bl	BsGet
	ubfiz	w0, w0, 16, 8
	and	w1, w19, 1
	orr	w0, w22, w0
	and	w19, w19, 255
	str	w1, [x25, 64]
	orr	w0, w0, w19
	str	w1, [x27, 4976]
	asr	w0, w0, 5
	ubfx	x1, x21, 1, 3
	cmp	w0, w23
	ubfx	x21, x21, 4, 1
	str	w0, [x25, 76]
	stp	w21, w1, [x25, 68]
	bhi	.L270
	mov	x0, x25
	bl	VP8_setup_version
	ldr	w0, [x25, 64]
	cbz	w0, .L271
.L174:
	add	x21, x27, 2616
	mov	w0, 255
	str	w0, [x27, 2616]
	mov	w2, 16
	mov	w1, 24
	mov	x0, x20
	str	w2, [x21, 8]
	bl	BsGet
	str	w0, [x21, 4]
	ldr	w0, [x25, 64]
	cbz	w0, .L272
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	strb	w0, [x25, 14]
	cbnz	w0, .L180
.L188:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	mov	w22, 0
	mov	w19, 5
	bl	Vp8_Vfmw_DecodeBool
	str	w0, [x25, 144]
.L181:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w22, w0, w22
	cmn	w19, #1
	bne	.L181
	strb	w22, [x25, 10]
	mov	w19, 2
	mov	w22, 0
.L192:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w22, w0, w22
	cmn	w19, #1
	bne	.L192
	strb	w22, [x25, 11]
	mov	w2, -128
	strb	wzr, [x25, 1]
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	strb	w0, [x25, 2]
	cbnz	w0, .L193
.L195:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	mov	w22, 0
	mov	w19, 6
	bl	Vp8_Vfmw_DecodeBool
	mov	w23, w0
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	orr	w0, w0, w23, lsl 1
	strb	w0, [x25, 13]
.L194:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w22, w0, w22
	cmn	w19, #1
	bne	.L194
	add	x19, x29, 144
	ldrsb	w2, [x25, 5]
	mov	x1, x20
	strb	w22, [x25, 3]
	mov	x0, x21
	str	wzr, [x19, -12]!
	mov	x3, x19
	bl	get_delta_q
	strb	w0, [x25, 5]
	ldrsb	w2, [x25, 6]
	mov	x3, x19
	mov	x1, x20
	mov	x0, x21
	bl	get_delta_q
	strb	w0, [x25, 6]
	ldrsb	w2, [x25, 7]
	mov	x3, x19
	mov	x1, x20
	mov	x0, x21
	bl	get_delta_q
	strb	w0, [x25, 7]
	ldrsb	w2, [x25, 8]
	mov	x3, x19
	mov	x1, x20
	mov	x0, x21
	bl	get_delta_q
	strb	w0, [x25, 8]
	ldrsb	w2, [x25, 9]
	mov	x1, x20
	mov	x3, x19
	mov	x0, x21
	bl	get_delta_q
	strb	w0, [x25, 9]
	ldr	w1, [x25, 64]
	cbnz	w1, .L273
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	strb	w0, [x25, 53]
	cbz	w0, .L274
.L209:
	ldr	w0, [x25, 64]
	cbnz	w0, .L210
.L276:
	mov	w0, 1
	strb	w0, [x25, 48]
.L211:
	ldr	x28, .LC37
	add	x0, x27, 1056
	mov	w2, 255
	str	x0, [x29, 104]
	str	x27, [x29, 112]
	add	x0, x28, 304
	str	x0, [x29, 120]
.L212:
	ldp	x26, x0, [x29, 112]
	sub	x24, x0, #231
	.p2align 2
.L221:
	sub	x22, x24, #33
	mov	x23, x26
.L219:
	mov	x19, 0
	b	.L217
	.p2align 3
.L213:
	add	x19, x19, 1
	cmp	x19, 11
	beq	.L275
.L215:
	ldrb	w2, [x22, x19]
.L217:
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	cmp	w0, 1
	bne	.L213
	mov	w27, 0
	mov	w28, 7
	.p2align 2
.L214:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w28
	sub	w28, w28, #1
	orr	w27, w0, w27
	cmn	w28, #1
	bne	.L214
	add	x0, x23, x19
	add	x19, x19, 1
	cmp	x19, 11
	strb	w27, [x0, 3794]
	bne	.L215
.L275:
	add	x22, x22, 11
	add	x23, x23, 11
	cmp	x24, x22
	beq	.L216
	ldrb	w2, [x22]
	b	.L219
.L274:
	ldr	x3, .LC36
	mov	x2, 1149
	add	x1, x27, 3777
	add	x0, x27, 2628
	ldr	x3, [x3, 104]
	blr	x3
	ldr	w0, [x25, 64]
	cbz	w0, .L276
	b	.L210
	.p2align 3
.L273:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	strb	w0, [x25, 49]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	strb	wzr, [x25, 51]
	ldrb	w2, [x25, 49]
	uxtb	w1, w0
	strb	w1, [x25, 50]
	cbnz	w2, .L207
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	mov	w19, w0
	mov	x1, x20
	mov	w2, -128
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	orr	w0, w0, w19, lsl 1
	ldrb	w1, [x25, 50]
	strb	w0, [x25, 51]
.L207:
	strb	wzr, [x25, 52]
	cbnz	w1, .L208
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	mov	w19, w0
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	orr	w0, w0, w19, lsl 1
	strb	w0, [x25, 52]
.L208:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	strb	w0, [x25, 56]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	strb	w0, [x25, 57]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	strb	w0, [x25, 53]
	cbnz	w0, .L209
	b	.L274
	.p2align 3
.L193:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	strb	w0, [x25, 1]
	cbz	w0, .L195
	add	x22, x27, 2508
	add	x19, x27, 2512
	b	.L200
.L197:
	add	x22, x22, 1
	cmp	x19, x22
	beq	.L277
.L200:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x25, 30]
	bne	.L197
	mov	w24, 0
	mov	w23, 5
.L198:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w23
	sub	w23, w23, #1
	orr	w24, w0, w24
	cmn	w23, #1
	bne	.L198
	strb	w24, [x22]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x25, 12]
	bne	.L197
	ldrb	w0, [x22]
	add	x22, x22, 1
	neg	w0, w0
	strb	w0, [x22, -1]
	cmp	x19, x22
	bne	.L200
.L277:
	add	x24, x27, 2516
	b	.L205
	.p2align 3
.L202:
	add	x19, x19, 1
	cmp	x24, x19
	beq	.L195
.L205:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x25, 31]
	bne	.L202
	mov	w23, 0
	mov	w22, 5
.L203:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w22
	sub	w22, w22, #1
	orr	w23, w0, w23
	cmn	w22, #1
	bne	.L203
	strb	w23, [x19]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	cbz	w0, .L202
	ldrb	w0, [x19]
	neg	w0, w0
	strb	w0, [x19]
	b	.L202
	.p2align 3
.L180:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	strb	w0, [x25, 15]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	strb	w0, [x25, 16]
	cbnz	w0, .L278
.L182:
	ldrb	w0, [x25, 15]
	cbz	w0, .L188
	ldr	x3, .LC36
	add	x0, x27, 2486
	mov	x2, 3
	mov	w1, 255
	mov	x19, x0
	add	x24, x27, 2489
	ldr	x3, [x3, 96]
	blr	x3
	b	.L191
	.p2align 3
.L189:
	add	x19, x19, 1
	cmp	x24, x19
	beq	.L188
.L191:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x25, 21]
	bne	.L189
	mov	w23, 0
	mov	w22, 7
.L190:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w22
	sub	w22, w22, #1
	orr	w23, w0, w23
	cmn	w22, #1
	bne	.L190
	strb	w23, [x19]
	b	.L189
	.p2align 3
.L272:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	str	w0, [x25, 136]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	str	w0, [x25, 140]
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	strb	w0, [x25, 14]
	cbz	w0, .L188
	b	.L180
	.p2align 3
.L210:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	strb	w0, [x25, 48]
	b	.L211
	.p2align 3
.L216:
	ldr	x0, [x29, 120]
	add	x26, x26, 33
	cmp	x24, x0
	beq	.L218
	ldrb	w2, [x24], 33
	b	.L221
.L218:
	ldp	x1, x0, [x29, 104]
	add	x0, x0, 264
	str	x0, [x29, 112]
	cmp	x1, x0
	beq	.L220
	ldr	x0, [x29, 120]
	ldrb	w2, [x0]
	add	x0, x0, 264
	str	x0, [x29, 120]
	b	.L212
.L220:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	str	w0, [x25, 80]
	cbz	w0, .L222
	mov	w22, 0
	mov	w19, 7
.L223:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w19
	sub	w19, w19, #1
	orr	w22, w0, w22
	cmn	w19, #1
	bne	.L223
	strb	w22, [x25, 61]
.L224:
	mov	x0, x25
	mov	x2, x20
	mov	x1, x21
	bl	VP8_mb_mode_mv_init
	ldr	w0, [x25, 64]
	cbz	w0, .L225
	ldr	w1, [x25, 48]
	mov	w0, 1
	tst	w1, 16776960
	beq	.L172
.L225:
	ldrb	w1, [x25, 3]
	mov	w0, 1
	strb	w1, [x25, 4]
.L172:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L270:
	ldr	x1, .LC27
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L222:
	strb	wzr, [x25, 61]
	b	.L224
.L271:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	mov	w19, w0
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	uxtb	w2, w0
	uxtb	w1, w19
	uxtb	w3, w21
	cmp	w1, 157
	mov	w1, 42
	ccmp	w3, 1, 0, eq
	ccmp	w2, w1, 0, eq
	beq	.L175
	ldr	x1, .LC29
	mov	w4, w2
	mov	w0, 1
	uxtb	w2, w19
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L175:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 8
	mov	x0, x20
	and	w21, w21, 255
	bl	BsGet
	mov	w22, w0
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	mov	w19, w0
	mov	w1, 8
	mov	x0, x20
	and	w19, w19, 255
	bl	BsGet
	ubfiz	w3, w0, 8, 6
	ubfiz	w2, w22, 8, 6
	orr	w3, w3, w19
	orr	w2, w2, w21
	mov	w1, 32
	cmp	w3, w1
	add	w4, w2, 15
	lsr	w4, w4, 4
	ccmp	w2, w1, 0, hi
	ubfx	x0, x0, 6, 2
	add	w1, w3, 15
	lsr	w1, w1, 4
	cset	w5, ls
	ubfx	x22, x22, 6, 2
	cmp	w4, 512
	stp	w22, w0, [x25, 120]
	mov	w0, 512
	ccmp	w1, w0, 2, ls
	mul	w6, w4, w1
	cset	w0, hi
	str	w6, [x25, 128]
	stp	w4, w1, [x25, 104]
	stp	w2, w3, [x25, 112]
	orr	w0, w5, w0
	cbnz	w0, .L279
	ldp	w19, w21, [x27, 120]
	cmp	w2, w19
	ccmp	w3, w21, 0, eq
	beq	.L177
	ldr	x1, .LC33
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, .LC35
	mov	w3, w21
	ldp	w4, w5, [x25, 104]
	mov	w2, w19
	mov	w0, 22
	bl	dprint_vfmw
.L177:
	ldr	w0, [x25, 64]
	cbnz	w0, .L174
	mov	x0, x25
	bl	VP8_init_frame.part.0
	b	.L174
.L279:
	ldr	x1, .LC31
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L278:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	mov	x23, x27
	mov	x24, 0
	bl	Vp8_Vfmw_DecodeBool
	strb	w0, [x25, 17]
	ldr	x3, .LC36
	mov	x2, 8
	mov	w1, 0
	add	x0, x27, 2490
	ldr	x3, [x3, 96]
	blr	x3
.L183:
	add	x26, x23, 4
.L187:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	mov	w28, 0
	bl	Vp8_Vfmw_DecodeBool
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x25]
	beq	.L280
.L184:
	strb	w28, [x23, 2490]
	add	x23, x23, 1
	cmp	x23, x26
	bne	.L187
	add	x24, x24, 4
	cmp	x24, 8
	bne	.L183
	b	.L182
	.p2align 3
.L280:
	add	x0, x29, 136
	mov	w19, 0
	ldr	w22, [x24, x0]
	subs	w22, w22, #1
	bmi	.L185
.L186:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	lsl	w0, w0, w22
	sub	w22, w22, #1
	orr	w19, w0, w19
	cmn	w22, #1
	bne	.L186
	sxtb	w28, w19
.L185:
	mov	w2, -128
	mov	x1, x20
	mov	x0, x21
	bl	Vp8_Vfmw_DecodeBool
	cbz	w0, .L184
	neg	w19, w19
	sxtb	w28, w19
	b	.L184
	.size	VP8_GetPictureHeader, .-VP8_GetPictureHeader
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
.LC33:
	.xword	.LC32
	.align	3
.LC35:
	.xword	.LC34
	.align	3
.LC36:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC37:
	.xword	.LANCHOR2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_ArrangeVHBMem
	.type	VP8_ArrangeVHBMem, %function
VP8_ArrangeVHBMem:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 4096
	add	x0, x0, 1620
	ldp	w2, w3, [x0, 112]
	cmp	w3, 31
	bls	.L283
	mov	w1, 8160
	sub	w4, w2, #32
	mov	w0, 8192
	cmp	w4, w1
	ccmp	w3, w0, 2, ls
	bhi	.L283
	ldr	x1, [x19]
	ldr	w0, [x1, 772]
	cbnz	w0, .L286
	ldr	w0, [x1, 28]
	cmp	w0, 25
	beq	.L314
.L287:
	mov	w20, 4
	mov	w22, w2
	mov	w21, w3
	mov	w24, 5
	mov	w23, w20
.L292:
	ldr	x0, .LC42
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 72
	blr	x3
	ldr	x0, [x19]
	stp	w22, w21, [x29, 76]
	stp	w22, w21, [x29, 84]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L298
	strb	w23, [x29, 73]
	sxtb	w20, w20
	strb	w24, [x29, 74]
.L303:
	ldr	w0, [x19, 8840]
	add	x1, x29, 72
	strb	w20, [x29, 75]
	bl	FSP_ConfigInstance
	cbnz	w0, .L299
	ldr	x1, [x19]
	add	x3, x29, 68
	ldr	w0, [x19, 8840]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L315
	cbnz	w0, .L301
	mov	w0, 1
	str	w0, [x19, 8188]
	b	.L307
	.p2align 3
.L283:
	ldr	x1, .LC39
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
.L307:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L286:
	ldr	w0, [x1, 28]
	cmp	w0, 25
	bne	.L287
	ldr	w4, [x1, 732]
	ldr	w5, [x1, 736]
	cmp	w2, w4
	bhi	.L295
	cmp	w3, w5
	bhi	.L295
	ldr	w4, [x1, 760]
	mov	w22, w2
	ldr	w0, [x1, 756]
	mov	w21, w3
	mov	w20, 1
	add	w23, w0, 2
	cbz	w4, .L297
.L312:
	add	w20, w0, w20
	mov	w0, 17
	cmp	w20, w0
	csel	w20, w20, w0, le
.L297:
	ldrsb	w24, [x1, 780]
	b	.L292
	.p2align 3
.L299:
	ldr	x1, .LC46
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L307
	.p2align 3
.L298:
	mov	w0, 1
	strb	w24, [x29, 74]
	strb	w0, [x29, 73]
	mov	w20, 1
	b	.L303
	.p2align 3
.L314:
	ldr	w22, [x1, 732]
	cmp	w2, w22
	bhi	.L316
	ldr	w21, [x1, 736]
	cmp	w3, w21
	bhi	.L317
	ldr	w0, [x19, 8188]
	cmp	w0, 1
	beq	.L307
	ldr	w2, [x1, 760]
	mov	w20, 1
	ldr	w0, [x1, 756]
	add	w23, w0, 2
	cbnz	w2, .L312
	ldrsb	w24, [x1, 780]
	b	.L292
	.p2align 3
.L295:
	ldr	x1, .LC41
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L307
.L315:
	add	x0, x19, 8192
	add	x0, x0, 40
	bl	ResetVoQueue
.L301:
	ldr	x1, .LC44
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L307
.L317:
	mov	w5, w21
.L289:
	ldr	x1, .LC41
	mov	w4, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L307
.L316:
	ldr	w5, [x1, 736]
	b	.L289
	.size	VP8_ArrangeVHBMem, .-VP8_ArrangeVHBMem
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC42:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC46:
	.xword	.LC45
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_DecodeDecide
	.type	VP8_DecodeDecide, %function
VP8_DecodeDecide:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 3248
	bl	_mcount
	ldr	w0, [x19, 4940]
	cbz	w0, .L346
	ldr	w0, [x19, 4932]
	sub	w0, w0, #2
	cmp	w0, 1
	ldr	x0, [x20]
	ldr	w2, [x0, 8]
	bls	.L347
.L322:
	cmp	w2, 4
	str	w2, [x19, 4932]
	bls	.L348
	ldr	x1, .LC58
	mov	w0, 1
	bl	dprint_vfmw
.L325:
	mov	w0, 0
.L339:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L348:
	ldr	x0, .LC64
	ldrb	w0, [x0,w2,uxtw]
	adr	x1, .Lrtx328
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx328:
	.section	.rodata
	.align	0
	.align	2
.L328:
	.byte	(.L326 - .Lrtx328) / 4
	.byte	(.L326 - .Lrtx328) / 4
	.byte	(.L323 - .Lrtx328) / 4
	.byte	(.L325 - .Lrtx328) / 4
	.byte	(.L326 - .Lrtx328) / 4
	.text
	.p2align 3
.L347:
	cmp	w2, 1
	ccmp	w2, 4, 4, hi
	bne	.L322
	ldr	x1, .LC50
	mov	w0, 2
	bl	dprint_vfmw
	ldr	w1, [x19, 4956]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_ClearLogicFs
	ldr	w1, [x19, 4960]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_ClearLogicFs
	ldr	w1, [x19, 4964]
	mov	w2, 1
	ldr	w0, [x20, 8840]
	bl	FSP_ClearLogicFs
	str	wzr, [x19, 4956]
	str	wzr, [x19, 4960]
	str	wzr, [x19, 4964]
	ldr	w0, [x20, 8840]
	bl	FSP_GetNullLogicFs
	str	wzr, [x19, 4936]
	str	w0, [x19, 4956]
	str	w0, [x19, 4960]
	str	w0, [x19, 4964]
	ldr	x0, [x20]
	ldr	w2, [x0, 8]
	b	.L322
	.p2align 3
.L346:
	ldr	x1, .LC48
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L323:
	ldr	w2, [x19, 4976]
	cbnz	w2, .L349
.L324:
	ldr	w1, [x19, 4964]
	ldr	w0, [x20, 8840]
	bl	FSP_GetFsImagePtr
	mov	x1, x0
	cbz	x0, .L350
	ldr	w2, [x19, 4976]
	mov	w0, 1
	cbz	w2, .L339
	ldr	x3, [x20]
	ldr	w2, [x1, 152]
	ldr	w3, [x3]
	cmp	w2, w3
	bls	.L339
	ldr	x1, .LC63
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L326:
	ldr	w0, [x19, 4976]
	cbz	w0, .L324
	ldr	w0, [x19, 4936]
	cbnz	w0, .L324
	ldr	x2, .LC54
	mov	w3, 0
	ldr	x1, .LC56
	mov	w0, 18
	bl	dprint_vfmw
	b	.L325
	.p2align 3
.L349:
	ldr	x1, .LC52
	mov	w0, 18
	bl	dprint_vfmw
	b	.L325
	.p2align 3
.L350:
	ldr	x2, .LC59
	mov	w3, 1486
	ldr	x1, .LC61
	mov	w0, 22
	add	x2, x2, 1096
	bl	dprint_vfmw
	mov	w0, 0
	b	.L339
	.size	VP8_DecodeDecide, .-VP8_DecodeDecide
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
.LC59:
	.xword	.LANCHOR2
	.align	3
.LC61:
	.xword	.LC60
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC64:
	.xword	.L328
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_GetImageBuffer
	.type	VP8_GetImageBuffer, %function
VP8_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 3248
	bl	_mcount
	ldr	w0, [x19, 8840]
	mov	w1, 1
	bl	FSP_NewLogicFs
	str	w0, [x20, 4968]
	mov	w1, w0
	tbnz	w0, #31, .L357
	ldr	w0, [x19, 8840]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L358
	ldr	x1, .LC70
	mov	w0, 18
	ldr	w2, [x20, 4968]
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L356
	ldr	x1, [x19, 40]
	cbz	x1, .L356
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC72
	bl	dprint_vfmw
	mov	w0, 1
.L353:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L356:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L357:
	ldr	x1, .LC66
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 8840]
	mov	w2, 1
	ldr	w1, [x20, 4956]
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 8840]
	mov	w2, 1
	ldr	w1, [x20, 4960]
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 4964]
	mov	w2, 1
	ldr	w0, [x19, 8840]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 4956]
	str	wzr, [x20, 4960]
	str	wzr, [x20, 4964]
	ldr	w0, [x19, 8840]
	bl	FSP_GetNullLogicFs
	str	wzr, [x20, 4936]
	str	w0, [x20, 4956]
	add	x1, x19, 8192
	str	w0, [x20, 4960]
	add	x1, x1, 40
	str	w0, [x20, 4964]
	ldr	w0, [x19, 8840]
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L358:
	ldr	x1, .LC68
	mov	w2, 1542
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L353
	.size	VP8_GetImageBuffer, .-VP8_GetImageBuffer
	.align	3
.LC66:
	.xword	.LC65
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC70:
	.xword	.LC69
	.align	3
.LC72:
	.xword	.LC71
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_Set_DecParam
	.type	VP8_Set_DecParam, %function
VP8_Set_DecParam:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x24, x0
	mov	x0, x30
	add	x1, x24, 4096
	str	x1, [x29, 104]
	mov	x20, x1
	add	x21, x24, 16
	bl	_mcount
	ldr	x28, .LC73
	ldr	x3, [x24, 3200]
	mov	x2, 3164
	str	x3, [x29, 96]
	mov	w1, 0
	ldr	x3, [x28, 96]
	mov	x0, x21
	add	x19, x24, 3248
	blr	x3
	ldr	w1, [x20, 1684]
	add	x0, x20, 1620
	str	w1, [x21, 2800]
	ldr	w1, [x19, 4980]
	str	w1, [x21, 2804]
	ldr	w1, [x0, 104]
	str	w1, [x21, 2788]
	ldr	w1, [x0, 108]
	str	w1, [x21, 2792]
	ldr	w1, [x0, 92]
	str	w1, [x21, 2808]
	ldr	w1, [x0, 96]
	str	w1, [x21, 2812]
	ldrb	w1, [x0, 61]
	strb	w1, [x21, 2752]
	ldr	w1, [x0, 80]
	strb	w1, [x21, 2753]
	ldrb	w1, [x0, 13]
	strb	w1, [x21, 2754]
	ldrb	w1, [x0, 14]
	strb	w1, [x21, 2755]
	ldrb	w1, [x0, 15]
	strb	w1, [x21, 2756]
	ldrb	w1, [x0, 17]
	strb	w1, [x21, 2757]
	ldrb	w1, [x0, 2]
	strb	w1, [x21, 2758]
	ldr	w1, [x0, 144]
	strb	w1, [x21, 2760]
	ldrb	w1, [x0, 10]
	strb	w1, [x21, 2762]
	ldrb	w1, [x0, 11]
	strb	w1, [x21, 2763]
	ldr	w1, [x19, 4944]
	strb	w1, [x21, 2761]
	ldr	w1, [x19, 4948]
	strb	w1, [x21, 2764]
	ldrb	w1, [x0, 3]
	strb	w1, [x21, 2759]
	ldrsb	x1, [x0, 5]
	lsr	w2, w1, 31
	strb	w2, [x21, 2765]
	eor	x2, x1, x1, asr 63
	sub	x2, x2, x1, asr 63
	strb	w2, [x21, 2766]
	ldrsb	x1, [x0, 6]
	lsr	w2, w1, 31
	strb	w2, [x21, 2767]
	eor	x2, x1, x1, asr 63
	sub	x2, x2, x1, asr 63
	strb	w2, [x21, 2768]
	ldrsb	x1, [x0, 7]
	lsr	w2, w1, 31
	strb	w2, [x21, 2769]
	eor	x2, x1, x1, asr 63
	sub	x2, x2, x1, asr 63
	strb	w2, [x21, 2770]
	ldrsb	x1, [x0, 8]
	lsr	w2, w1, 31
	strb	w2, [x21, 2771]
	eor	x2, x1, x1, asr 63
	sub	x2, x2, x1, asr 63
	strb	w2, [x21, 2772]
	ldrsb	x1, [x0, 9]
	lsr	w2, w1, 31
	strb	w2, [x21, 2773]
	eor	x2, x1, x1, asr 63
	sub	x2, x2, x1, asr 63
	strb	w2, [x21, 2774]
	ldrb	w1, [x0, 58]
	strb	w1, [x21, 2775]
	ldrb	w1, [x0, 59]
	strb	w1, [x21, 2776]
	ldrb	w1, [x0, 60]
	strb	w1, [x21, 2777]
	ldr	w1, [x0, 152]
	str	w1, [x21, 2784]
	ldr	w1, [x0, 148]
	strb	w1, [x21, 2779]
	ldr	w0, [x0, 156]
	strb	w0, [x21, 2780]
	ldr	w0, [x19, 4952]
	str	w0, [x21, 3140]
	ldr	w1, [x19, 4968]
	ldr	w0, [x24, 8840]
	bl	FSP_GetLogicFs
	mov	x20, x0
	ldr	w1, [x19, 4956]
	ldr	w0, [x24, 8840]
	bl	FSP_GetLogicFs
	mov	x22, x0
	ldr	w1, [x19, 4960]
	ldr	w0, [x24, 8840]
	bl	FSP_GetLogicFs
	mov	x23, x0
	ldr	w1, [x19, 4964]
	ldr	w0, [x24, 8840]
	bl	FSP_GetLogicFs
	cmp	x20, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L360
	cmp	x23, xzr
	ccmp	x0, xzr, 4, ne
	beq	.L360
	ldr	x1, [x20, 32]
	cbz	x1, .L399
	ldr	w1, [x1, 8]
	str	w1, [x21, 3120]
	ldr	w1, [x20, 8]
	str	w1, [x21, 3136]
	ldr	x1, [x22, 32]
	cbz	x1, .L400
.L395:
	ldr	w1, [x1, 8]
	str	w1, [x21, 3128]
	ldr	x1, [x23, 32]
	cbz	x1, .L401
.L396:
	ldr	w1, [x1, 8]
	str	w1, [x21, 3124]
	ldr	x0, [x0, 32]
	cbz	x0, .L402
.L397:
	ldr	w0, [x0, 8]
	add	x3, x24, 3072
	str	w0, [x21, 3132]
	ldr	x0, [x29, 104]
	ldr	x2, [x20, 40]
	add	x1, x0, 1642
	add	x0, x24, 3056
	ldr	w2, [x2, 24]
	str	w2, [x19, 4928]
	str	w2, [x21, 2796]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 60]
	str	w2, [x21, 3152]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 44]
	str	w2, [x21, 3156]
	ldr	x2, [x20, 40]
	ldr	w2, [x2, 48]
	str	w2, [x21, 3160]
.L370:
	add	x0, x0, 4
	ldrsb	w2, [x1]
	add	x1, x1, 1
	cmp	x3, x0
	str	w2, [x0, -4]
	ldrsb	w2, [x1, 3]
	str	w2, [x0, 12]
	ldrsb	w2, [x1, 17]
	str	w2, [x0, 28]
	ldrsb	w2, [x1, 21]
	str	w2, [x0, 44]
	ldrb	w2, [x1, 31]
	str	w2, [x0, 60]
	bne	.L370
	ldr	x20, [x29, 104]
	mov	x2, 16
	ldr	x3, [x28, 96]
	mov	w1, 0
	add	x19, x20, 1620
	mov	x0, x21
	mov	w25, 1152
	add	x26, x20, 2946
	blr	x3
	ldrb	w0, [x19, 61]
	mov	x2, 16
	strb	w0, [x24, 16]
	mov	w1, 0
	add	x0, x24, 32
	ldrb	w3, [x19, 18]
	strb	w3, [x24, 17]
	ldrb	w3, [x19, 19]
	strb	w3, [x24, 18]
	ldrb	w3, [x19, 20]
	strb	w3, [x24, 19]
	ldrb	w3, [x19, 58]
	strb	w3, [x24, 20]
	ldrb	w3, [x19, 59]
	strb	w3, [x24, 21]
	ldrb	w3, [x19, 60]
	strb	w3, [x24, 22]
	ldr	x3, [x28, 96]
	blr	x3
	ldrb	w0, [x19, 1318]
	mov	x2, 16
	strb	w0, [x24, 32]
	mov	w1, 0
	add	x0, x24, 48
	ldrb	w3, [x19, 1319]
	strb	w3, [x24, 33]
	ldrb	w3, [x19, 1320]
	strb	w3, [x24, 34]
	ldrb	w3, [x19, 1321]
	strb	w3, [x24, 35]
	ldrb	w3, [x19, 1322]
	strb	w3, [x24, 36]
	ldrb	w3, [x19, 1323]
	strb	w3, [x24, 37]
	ldrb	w3, [x19, 1324]
	strb	w3, [x24, 38]
	ldr	x3, [x28, 96]
	blr	x3
	ldr	x3, [x28, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x24, 64
	blr	x3
	ldr	x3, [x28, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x24, 720
	blr	x3
	ldrb	w0, [x19, 2383]
	mov	x2, 16
	strb	w0, [x24, 720]
	mov	w1, 0
	ldr	x3, [x28, 96]
	ldrb	w0, [x19, 2382]
	strb	w0, [x24, 721]
	ldrb	w0, [x19, 2384]
	strb	w0, [x24, 722]
	ldrb	w0, [x19, 2385]
	strb	w0, [x24, 723]
	ldrb	w0, [x19, 2386]
	strb	w0, [x24, 724]
	ldrb	w0, [x19, 2387]
	strb	w0, [x24, 725]
	ldrb	w0, [x19, 2388]
	strb	w0, [x24, 726]
	ldrb	w0, [x19, 2389]
	strb	w0, [x24, 727]
	ldrb	w0, [x19, 2390]
	strb	w0, [x24, 728]
	add	x0, x24, 736
	blr	x3
	ldrb	w0, [x19, 2383]
	mov	x2, 16
	strb	w0, [x24, 736]
	mov	w1, 0
	ldr	x3, [x28, 96]
	ldrb	w0, [x19, 2391]
	strb	w0, [x24, 737]
	ldrb	w0, [x19, 2392]
	strb	w0, [x24, 738]
	ldrb	w0, [x19, 2393]
	strb	w0, [x24, 739]
	ldrb	w0, [x19, 2394]
	strb	w0, [x24, 740]
	ldrb	w0, [x19, 2395]
	strb	w0, [x24, 741]
	ldrb	w0, [x19, 2396]
	strb	w0, [x24, 742]
	ldrb	w0, [x19, 2397]
	strb	w0, [x24, 743]
	ldrb	w0, [x19, 2398]
	strb	w0, [x24, 744]
	ldrb	w0, [x19, 2399]
	strb	w0, [x24, 745]
	ldrb	w0, [x19, 2400]
	strb	w0, [x24, 746]
	add	x0, x24, 752
	blr	x3
	ldrb	w0, [x19, 2402]
	mov	x2, 16
	strb	w0, [x24, 752]
	mov	w1, 0
	ldr	x3, [x28, 96]
	ldrb	w0, [x19, 2401]
	strb	w0, [x24, 753]
	ldrb	w0, [x19, 2403]
	strb	w0, [x24, 754]
	ldrb	w0, [x19, 2404]
	strb	w0, [x24, 755]
	ldrb	w0, [x19, 2405]
	strb	w0, [x24, 756]
	ldrb	w0, [x19, 2406]
	strb	w0, [x24, 757]
	ldrb	w0, [x19, 2407]
	strb	w0, [x24, 758]
	ldrb	w0, [x19, 2408]
	strb	w0, [x24, 759]
	ldrb	w0, [x19, 2409]
	strb	w0, [x24, 760]
	add	x0, x24, 768
	blr	x3
	ldrb	w0, [x19, 2402]
	strb	w0, [x24, 768]
	ldrb	w0, [x19, 2410]
	strb	w0, [x24, 769]
	ldrb	w0, [x19, 2411]
	strb	w0, [x24, 770]
	ldrb	w0, [x19, 2412]
	strb	w0, [x24, 771]
	ldrb	w0, [x19, 2413]
	strb	w0, [x24, 772]
	ldrb	w0, [x19, 2414]
	strb	w0, [x24, 773]
	ldrb	w0, [x19, 2415]
	strb	w0, [x24, 774]
	ldrb	w0, [x19, 2416]
	strb	w0, [x24, 775]
	ldrb	w0, [x19, 2417]
	strb	w0, [x24, 776]
	ldrb	w0, [x19, 2418]
	strb	w0, [x24, 777]
	ldrb	w0, [x19, 2419]
	strb	w0, [x24, 778]
.L371:
	sub	w19, w25, #384
	mov	x23, x26
	.p2align 2
.L375:
	add	w22, w19, 48
	mov	x20, x23
.L372:
	add	x27, x21, x19, uxtw
	ldr	x5, [x28, 96]
	mov	x2, 16
	mov	w1, 0
	mov	x0, x27
	add	w19, w19, 16
	blr	x5
	ldr	x5, [x28, 104]
	mov	x1, x20
	mov	x2, 11
	mov	x0, x27
	add	x20, x20, x2
	blr	x5
	cmp	w19, w22
	bne	.L372
	cmp	w25, w19
	add	x23, x23, 33
	bne	.L375
	add	w25, w25, 384
	add	x26, x26, 264
	cmp	w25, 2688
	bne	.L371
	ldr	x0, [x29, 104]
	ldr	w0, [x0, 1684]
	cbnz	w0, .L387
	mov	x19, 10
	mov	w20, w19
.L376:
	ldr	x26, [x29, 96]
	add	x25, x24, 3208
	ldr	x0, [x29, 104]
	ldr	w1, [x26, 8]
	add	x27, x0, 1620
	mov	x0, x25
	and	w1, w1, -16
	sub	w1, w1, #16
	str	w1, [x21, 2816]
	ldr	w22, [x27, 76]
	bl	BsPos
	add	w22, w20, w22
	lsl	w22, w22, 3
	sub	w0, w22, w0
	str	w0, [x21, 2820]
	mov	x0, x25
	ldr	w23, [x26, 8]
	bl	BsPos
	mov	w22, w0
	cmp	w22, wzr
	add	w1, w22, 7
	csel	w1, w1, w22, lt
	and	w23, w23, 15
	mov	x0, x25
	add	w22, w23, 16
	add	w22, w22, w1, asr 3
	bl	BsPos
	asr	w2, w0, 31
	lsr	w2, w2, 29
	ubfiz	w3, w22, 3, 4
	add	w1, w0, w2
	and	w22, w22, -16
	and	w1, w1, 7
	sub	w0, w1, w2
	add	x2, x21, 2816
	add	w0, w3, w0
	mov	w1, 1
	stp	w0, w22, [x2, 8]
	stp	wzr, wzr, [x2, 16]
	str	wzr, [x21, 2840]
	ldrb	w2, [x27, 13]
	ldr	w9, [x27, 76]
	lsl	w1, w1, w2
	ldr	w3, [x26, 12]
	and	w7, w1, 255
	ldr	x0, [x26]
	uxtb	w1, w1
	str	w7, [x21, 2844]
	cmp	w1, 1
	add	x19, x19, x9, uxtw
	sub	w3, w3, w20
	add	x0, x0, x19
	bls	.L388
	sub	w5, w7, #1
	lsl	w1, w5, 2
	sub	w5, w1, w5
	add	x5, x0, x5, sxtw
.L377:
	cbz	w7, .L386
	mov	w2, 1
	sub	w8, w7, #1
	sub	w4, w2, w7
	mov	x1, 0
	lsl	w2, w4, 2
	sub	w2, w2, w4
	add	x4, x29, 144
	sub	w2, w2, w9
	add	w10, w2, w3
	.p2align 2
.L381:
	cmp	w8, w1
	ble	.L379
	ldrb	w2, [x0, 1]
	ldrb	w6, [x0]
	ldrb	w3, [x0, 2]
	add	w2, w6, w2, lsl 8
	add	w2, w2, w3, lsl 16
.L380:
	str	w2, [x4, x1, lsl 2]
	add	x1, x1, 1
	cmp	w7, w1
	add	x0, x0, 3
	add	x5, x5, x2, uxtw
	bgt	.L381
	ldr	x0, [x29, 96]
	add	w20, w20, w8, lsl 2
	sub	w8, w20, w8
	mov	x2, x4
	add	x3, x29, 112
	mov	w4, 0
	ldr	w1, [x0, 8]
	add	x0, x24, 2864
	and	w1, w1, 15
	add	w9, w1, w9
	add	w8, w9, w8
	.p2align 2
.L385:
	cbz	w4, .L403
	ldr	w1, [x2, -4]
	ldr	w5, [x3, -4]
	add	w1, w5, w1
	str	w1, [x3]
.L384:
	ldr	w6, [x2], 4
	and	w5, w1, -16
	add	w4, w4, 1
	ubfiz	w1, w1, 3, 4
	lsl	w6, w6, 3
	str	w1, [x0, 32]
	str	w6, [x0]
	add	w1, w5, 16
	str	wzr, [x0, 96]
	cmp	w7, w4
	str	wzr, [x0, 128]
	add	x3, x3, 4
	str	wzr, [x0, 160]
	add	x0, x0, 4
	str	w1, [x0, 60]
	bne	.L385
.L386:
	ldr	x1, [x24]
	mov	w0, 1
	str	x21, [x24, 8]
	ldr	w2, [x1, 640]
	str	w2, [x24, 3160]
	ldr	w1, [x1, 692]
	str	w1, [x24, 3164]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L360:
	ldr	x1, .LC75
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L393:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L387:
	mov	x19, 3
	mov	w20, w19
	b	.L376
.L388:
	mov	x5, x0
	b	.L377
.L402:
	ldr	x0, [x20, 32]
	b	.L397
.L401:
	ldr	x1, [x20, 32]
	b	.L396
.L400:
	ldr	x1, [x20, 32]
	b	.L395
.L399:
	ldr	x1, .LC77
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L393
.L379:
	sub	x2, x0, x5
	add	w2, w10, w2
	b	.L380
.L403:
	str	w8, [x29, 112]
	ldr	w1, [x3]
	b	.L384
	.size	VP8_Set_DecParam, .-VP8_Set_DecParam
	.align	3
.LC73:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC75:
	.xword	.LC74
	.align	3
.LC77:
	.xword	.LC76
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8_Update_PictHeader
	.type	VP8_Update_PictHeader, %function
VP8_Update_PictHeader:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 2468
	add	x22, x19, 8
	bl	_mcount
	ldr	x21, .LC78
	ldrb	w0, [x20, 53]
	cbnz	w0, .L405
	ldr	x3, [x21, 104]
	mov	x2, 1149
	add	x1, x19, 2628
	add	x0, x19, 3777
	blr	x3
.L405:
	ldr	x3, [x21, 104]
	mov	x1, x20
	mov	x2, 2460
	mov	x0, x22
	blr	x3
	ldr	w0, [x20, 64]
	str	w0, [x19, 4980]
	ldr	w0, [x20, 144]
	str	w0, [x19, 4944]
	ldrb	w0, [x20, 11]
	str	w0, [x19, 4948]
	ldrb	w0, [x20, 48]
	strb	w0, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VP8_Update_PictHeader, .-VP8_Update_PictHeader
	.align	3
.LC78:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8DEC_Decode
	.type	VP8DEC_Decode, %function
VP8DEC_Decode:
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
	beq	.L451
	ldr	x1, [x20]
	str	x1, [x19, 3184]
	ldr	w0, [x20, 16]
	str	w0, [x19, 3192]
	ldr	w2, [x20, 20]
	str	w2, [x19, 3196]
	cmp	w2, 2
	ble	.L452
	add	x21, x19, 3208
	add	x20, x19, 3248
	mov	x0, x21
	bl	BsInit
	add	x0, x19, 3184
	ldr	w2, [x19, 3196]
	str	x0, [x19, 3200]
	mov	x1, x20
	mov	x0, x21
	bl	VP8_GetPictureHeader
	cmp	w0, 1
	bne	.L453
	ldr	w0, [x20, 4940]
	cbnz	w0, .L454
.L413:
	ldr	x22, .LC84
	ldr	x4, [x22]
	cbz	x4, .L415
	ldr	w3, [x19, 3364]
	ldr	w2, [x19, 5820]
	ldr	w1, [x19, 5824]
	ldr	w5, [x19, 3360]
	ldr	w0, [x19, 8840]
	strh	w3, [x29, 74]
	mov	w3, 8
	strh	w2, [x29, 76]
	add	x2, x29, 72
	strh	w1, [x29, 78]
	mov	w1, 2
	strh	w5, [x29, 72]
	blr	x4
.L415:
	ldr	w0, [x19, 8840]
	bl	FSP_GetFspType
	cbz	w0, .L455
.L450:
	add	x21, x19, 4096
.L416:
	ldr	w0, [x19, 8840]
	mov	w2, 1
	ldr	w1, [x20, 4956]
	add	x22, x19, 8192
	add	x22, x22, 40
	add	x21, x21, 1620
	bl	FSP_ClearLogicFs
	ldr	w0, [x19, 8840]
	mov	w2, 1
	ldr	w1, [x20, 4960]
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 4964]
	mov	w2, 1
	ldr	w0, [x19, 8840]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 4956]
	str	wzr, [x20, 4960]
	str	wzr, [x20, 4964]
	ldr	w0, [x19, 8840]
	bl	FSP_GetNullLogicFs
	str	wzr, [x20, 4936]
	str	w0, [x20, 4956]
	mov	x1, x22
	str	w0, [x20, 4960]
	str	w0, [x20, 4964]
	ldr	w0, [x19, 8840]
	bl	FSP_ClearNotInVoQueue
	ldp	w2, w3, [x21, 104]
	cmp	w2, 512
	bhi	.L423
	cmp	w3, 512
	bhi	.L423
	ldr	x0, [x19]
	ldr	w1, [x0, 772]
	cbnz	w1, .L425
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L456
.L425:
	mov	x0, x19
	bl	VP8_ArrangeVHBMem
	cmp	w0, 1
	bne	.L457
.L414:
	mov	x0, x19
	bl	VP8_DecodeDecide
	cmp	w0, 1
	mov	w21, w0
	beq	.L426
	ldr	x1, .LC92
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L410
	.p2align 3
.L452:
	ldr	x1, .LC81
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L410:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L451:
	ldr	x1, .LC79
	mov	w2, 1891
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L454:
	ldr	w2, [x19, 3360]
	add	x21, x19, 4096
	ldr	w1, [x19, 5820]
	add	x21, x21, 1620
	cmp	w2, w1
	bne	.L413
	ldr	w1, [x19, 3364]
	ldr	w0, [x21, 108]
	cmp	w1, w0
	bne	.L413
	b	.L414
	.p2align 3
.L455:
	add	x3, x29, 80
	ldr	w0, [x19, 8840]
	add	x2, x29, 68
	add	x1, x29, 64
	stp	wzr, wzr, [x29, 64]
	str	wzr, [x3, -8]!
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19]
	ldr	w2, [x0, 772]
	cmp	w2, 1
	bne	.L450
	ldr	w0, [x29, 72]
	cmp	w0, wzr
	bgt	.L419
	ldr	w0, [x29, 68]
	cmp	w0, 32
	bgt	.L419
	ldr	x0, [x19, 8]
	cbnz	x0, .L419
	ldr	w3, [x19, 3360]
	add	x21, x19, 4096
	cbz	w3, .L416
	ldr	w1, [x19, 8844]
	ldr	w6, [x21, 1728]
	cmp	w6, w1
	beq	.L416
	ldr	w1, [x19, 8848]
	ldr	w5, [x21, 1724]
	cmp	w5, w1
	beq	.L416
	ldr	w4, [x19, 3364]
	mov	w0, w2
	ldr	x1, .LC86
	bl	dprint_vfmw
	ldr	w0, [x21, 1728]
	str	w0, [x19, 8844]
	ldr	x4, [x22]
	ldr	w0, [x21, 1724]
	str	w0, [x19, 8848]
	cbz	x4, .L416
	ldr	w0, [x19, 8840]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L416
	.p2align 3
.L423:
	ldr	x1, .LC88
	mov	w0, 18
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L453:
	ldr	x1, .LC83
	mov	w0, 2
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L457:
	ldr	x1, .LC90
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L410
	.p2align 3
.L456:
	ldr	w0, [x20, 4940]
	cbnz	w0, .L425
	mov	x0, x22
	bl	ResetVoQueue
	b	.L425
	.p2align 3
.L426:
	mov	x0, x19
	bl	VP8_GetImageBuffer
	cmp	w0, 1
	beq	.L427
	ldr	x1, .LC94
	mov	w0, w21
	bl	dprint_vfmw
	mov	w0, 0
	b	.L410
	.p2align 3
.L427:
	ldr	w0, [x19, 8840]
	ldr	w1, [x20, 4968]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L458
	ldr	x3, [x19]
	mov	x4, -1
	ldr	x1, .LC97
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
	ldr	w0, [x20, 4976]
	cbnz	w0, .L429
	ldr	w1, [x20, 4960]
	ldr	w0, [x20, 4968]
	cmp	w1, w0
	beq	.L430
	ldr	w0, [x19, 8840]
	mov	w2, 0
	bl	FSP_SetRef
	ldr	w0, [x20, 4968]
.L430:
	ldr	w1, [x20, 4964]
	cmp	w1, w0
	beq	.L431
	ldr	w0, [x19, 8840]
	mov	w2, 0
	bl	FSP_SetRef
	ldr	w0, [x20, 4968]
.L431:
	ldr	w1, [x20, 4956]
	cmp	w1, w0
	beq	.L432
	ldr	w0, [x19, 8840]
	mov	w2, 0
	bl	FSP_SetRef
.L432:
	str	wzr, [x20, 4936]
.L429:
	mov	x0, x19
	bl	VP8_Set_DecParam
	mov	x0, x20
	bl	VP8_Update_PictHeader
	mov	w0, 0
	b	.L410
	.p2align 3
.L419:
	mov	w0, -2
	b	.L410
.L458:
	ldr	x1, .LC95
	mov	w2, 2013
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L410
	.size	VP8DEC_Decode, .-VP8DEC_Decode
	.align	3
.LC79:
	.xword	.LC5
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.align	3
.LC84:
	.xword	g_event_report
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC94:
	.xword	.LC93
	.align	3
.LC95:
	.xword	.LC67
	.align	3
.LC97:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8DEC_RecycleImage
	.type	VP8DEC_RecycleImage, %function
VP8DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L463
	ldr	w0, [x19, 8840]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x19, 8840]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L462
	ldr	w0, [x19, 8840]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 8840]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L462:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L463:
	ldr	x1, .LC98
	mov	w2, 2064
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP8DEC_RecycleImage, .-VP8DEC_RecycleImage
	.align	3
.LC98:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8DEC_GetRemainImg
	.type	VP8DEC_GetRemainImg, %function
VP8DEC_GetRemainImg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L467
	add	x0, x19, 8192
	add	x0, x0, 40
	bl	GetVoLastImageID
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L467:
	ldr	x1, .LC99
	mov	w2, 2084
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	VP8DEC_GetRemainImg, .-VP8DEC_GetRemainImg
	.align	3
.LC99:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VP8DEC_GetImageBuffer
	.type	VP8DEC_GetImageBuffer, %function
VP8DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L475
	ldr	w0, [x19, 8840]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w20, w0
	beq	.L470
	ldr	w0, [x19, 8840]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L476
.L470:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L476:
	add	x1, x19, 8192
	ldr	w0, [x19, 8840]
	add	x1, x1, 40
	bl	FSP_ClearNotInVoQueue
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L475:
	ldr	x1, .LC100
	mov	w2, 2093
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VP8DEC_GetImageBuffer, .-VP8DEC_GetImageBuffer
	.align	3
.LC100:
	.xword	.LC5
	.global	default_uv_mode_prob
	.global	default_ymode_prob
	.global	VP8_VFMWBITREADER_NORM
	.global	vp8_mv_update_probs
	.global	vp8_default_mv_context
	.global	vp8_coef_update_probs
	.global	default_coef_probs
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	vp8_default_mv_context, %object
	.size	vp8_default_mv_context, 38
vp8_default_mv_context:
	.byte	-94
	.byte	-128
	.byte	-31
	.byte	-110
	.byte	-84
	.byte	-109
	.byte	-42
	.byte	39
	.byte	-100
	.byte	-128
	.byte	-127
	.byte	-124
	.byte	75
	.byte	-111
	.byte	-78
	.byte	-50
	.byte	-17
	.byte	-2
	.byte	-2
	.byte	-92
	.byte	-128
	.byte	-52
	.byte	-86
	.byte	119
	.byte	-21
	.byte	-116
	.byte	-26
	.byte	-28
	.byte	-128
	.byte	-126
	.byte	-126
	.byte	74
	.byte	-108
	.byte	-76
	.byte	-53
	.byte	-20
	.byte	-2
	.byte	-2
	.zero	2
	.type	default_coef_probs, %object
	.size	default_coef_probs, 1056
default_coef_probs:
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-3
	.byte	-120
	.byte	-2
	.byte	-1
	.byte	-28
	.byte	-37
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-67
	.byte	-127
	.byte	-14
	.byte	-1
	.byte	-29
	.byte	-43
	.byte	-1
	.byte	-37
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	106
	.byte	126
	.byte	-29
	.byte	-4
	.byte	-42
	.byte	-47
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	98
	.byte	-8
	.byte	-1
	.byte	-20
	.byte	-30
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-75
	.byte	-123
	.byte	-18
	.byte	-2
	.byte	-35
	.byte	-22
	.byte	-1
	.byte	-102
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	78
	.byte	-122
	.byte	-54
	.byte	-9
	.byte	-58
	.byte	-76
	.byte	-1
	.byte	-37
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-71
	.byte	-7
	.byte	-1
	.byte	-13
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-72
	.byte	-106
	.byte	-9
	.byte	-1
	.byte	-20
	.byte	-32
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	77
	.byte	110
	.byte	-40
	.byte	-1
	.byte	-20
	.byte	-26
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	101
	.byte	-5
	.byte	-1
	.byte	-15
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-86
	.byte	-117
	.byte	-15
	.byte	-4
	.byte	-20
	.byte	-47
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	37
	.byte	116
	.byte	-60
	.byte	-13
	.byte	-28
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-52
	.byte	-2
	.byte	-1
	.byte	-11
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-49
	.byte	-96
	.byte	-6
	.byte	-1
	.byte	-18
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	102
	.byte	103
	.byte	-25
	.byte	-1
	.byte	-45
	.byte	-85
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-104
	.byte	-4
	.byte	-1
	.byte	-16
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-79
	.byte	-121
	.byte	-13
	.byte	-1
	.byte	-22
	.byte	-31
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	80
	.byte	-127
	.byte	-45
	.byte	-1
	.byte	-62
	.byte	-32
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-10
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-58
	.byte	35
	.byte	-19
	.byte	-33
	.byte	-63
	.byte	-69
	.byte	-94
	.byte	-96
	.byte	-111
	.byte	-101
	.byte	62
	.byte	-125
	.byte	45
	.byte	-58
	.byte	-35
	.byte	-84
	.byte	-80
	.byte	-36
	.byte	-99
	.byte	-4
	.byte	-35
	.byte	1
	.byte	68
	.byte	47
	.byte	-110
	.byte	-48
	.byte	-107
	.byte	-89
	.byte	-35
	.byte	-94
	.byte	-1
	.byte	-33
	.byte	-128
	.byte	1
	.byte	-107
	.byte	-15
	.byte	-1
	.byte	-35
	.byte	-32
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-72
	.byte	-115
	.byte	-22
	.byte	-3
	.byte	-34
	.byte	-36
	.byte	-1
	.byte	-57
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	81
	.byte	99
	.byte	-75
	.byte	-14
	.byte	-80
	.byte	-66
	.byte	-7
	.byte	-54
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	-127
	.byte	-24
	.byte	-3
	.byte	-42
	.byte	-59
	.byte	-14
	.byte	-60
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	99
	.byte	121
	.byte	-46
	.byte	-6
	.byte	-55
	.byte	-58
	.byte	-1
	.byte	-54
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	23
	.byte	91
	.byte	-93
	.byte	-14
	.byte	-86
	.byte	-69
	.byte	-9
	.byte	-46
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	-56
	.byte	-10
	.byte	-1
	.byte	-22
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	109
	.byte	-78
	.byte	-15
	.byte	-1
	.byte	-25
	.byte	-11
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	44
	.byte	-126
	.byte	-55
	.byte	-3
	.byte	-51
	.byte	-64
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-124
	.byte	-17
	.byte	-5
	.byte	-37
	.byte	-47
	.byte	-1
	.byte	-91
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	94
	.byte	-120
	.byte	-31
	.byte	-5
	.byte	-38
	.byte	-66
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	22
	.byte	100
	.byte	-82
	.byte	-11
	.byte	-70
	.byte	-95
	.byte	-1
	.byte	-57
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-74
	.byte	-7
	.byte	-1
	.byte	-24
	.byte	-21
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	124
	.byte	-113
	.byte	-15
	.byte	-1
	.byte	-29
	.byte	-22
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	35
	.byte	77
	.byte	-75
	.byte	-5
	.byte	-63
	.byte	-45
	.byte	-1
	.byte	-51
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-99
	.byte	-9
	.byte	-1
	.byte	-20
	.byte	-25
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	121
	.byte	-115
	.byte	-21
	.byte	-1
	.byte	-31
	.byte	-29
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	45
	.byte	99
	.byte	-68
	.byte	-5
	.byte	-61
	.byte	-39
	.byte	-1
	.byte	-32
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	1
	.byte	-5
	.byte	-1
	.byte	-43
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-53
	.byte	1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-119
	.byte	1
	.byte	-79
	.byte	-1
	.byte	-32
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-3
	.byte	9
	.byte	-8
	.byte	-5
	.byte	-49
	.byte	-48
	.byte	-1
	.byte	-64
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-81
	.byte	13
	.byte	-32
	.byte	-13
	.byte	-63
	.byte	-71
	.byte	-7
	.byte	-58
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	73
	.byte	17
	.byte	-85
	.byte	-35
	.byte	-95
	.byte	-77
	.byte	-20
	.byte	-89
	.byte	-1
	.byte	-22
	.byte	-128
	.byte	1
	.byte	95
	.byte	-9
	.byte	-3
	.byte	-44
	.byte	-73
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-17
	.byte	90
	.byte	-12
	.byte	-6
	.byte	-45
	.byte	-47
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-101
	.byte	77
	.byte	-61
	.byte	-8
	.byte	-68
	.byte	-61
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	24
	.byte	-17
	.byte	-5
	.byte	-38
	.byte	-37
	.byte	-1
	.byte	-51
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-55
	.byte	51
	.byte	-37
	.byte	-1
	.byte	-60
	.byte	-70
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	69
	.byte	46
	.byte	-66
	.byte	-17
	.byte	-55
	.byte	-38
	.byte	-1
	.byte	-28
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-65
	.byte	-5
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-33
	.byte	-91
	.byte	-7
	.byte	-1
	.byte	-43
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-115
	.byte	124
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	16
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-66
	.byte	36
	.byte	-26
	.byte	-1
	.byte	-20
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-107
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-30
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-9
	.byte	-64
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-16
	.byte	-128
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-122
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-43
	.byte	62
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	55
	.byte	93
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-54
	.byte	24
	.byte	-43
	.byte	-21
	.byte	-70
	.byte	-65
	.byte	-36
	.byte	-96
	.byte	-16
	.byte	-81
	.byte	-1
	.byte	126
	.byte	38
	.byte	-74
	.byte	-24
	.byte	-87
	.byte	-72
	.byte	-28
	.byte	-82
	.byte	-1
	.byte	-69
	.byte	-128
	.byte	61
	.byte	46
	.byte	-118
	.byte	-37
	.byte	-105
	.byte	-78
	.byte	-16
	.byte	-86
	.byte	-1
	.byte	-40
	.byte	-128
	.byte	1
	.byte	112
	.byte	-26
	.byte	-6
	.byte	-57
	.byte	-65
	.byte	-9
	.byte	-97
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-90
	.byte	109
	.byte	-28
	.byte	-4
	.byte	-45
	.byte	-41
	.byte	-1
	.byte	-82
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	39
	.byte	77
	.byte	-94
	.byte	-24
	.byte	-84
	.byte	-76
	.byte	-11
	.byte	-78
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	52
	.byte	-36
	.byte	-10
	.byte	-58
	.byte	-57
	.byte	-7
	.byte	-36
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	124
	.byte	74
	.byte	-65
	.byte	-13
	.byte	-73
	.byte	-63
	.byte	-6
	.byte	-35
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	24
	.byte	71
	.byte	-126
	.byte	-37
	.byte	-102
	.byte	-86
	.byte	-13
	.byte	-74
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	-74
	.byte	-31
	.byte	-7
	.byte	-37
	.byte	-16
	.byte	-1
	.byte	-32
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-107
	.byte	-106
	.byte	-30
	.byte	-4
	.byte	-40
	.byte	-51
	.byte	-1
	.byte	-85
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	28
	.byte	108
	.byte	-86
	.byte	-14
	.byte	-73
	.byte	-62
	.byte	-2
	.byte	-33
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	81
	.byte	-26
	.byte	-4
	.byte	-52
	.byte	-53
	.byte	-1
	.byte	-64
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	123
	.byte	102
	.byte	-47
	.byte	-9
	.byte	-68
	.byte	-60
	.byte	-1
	.byte	-23
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	20
	.byte	95
	.byte	-103
	.byte	-13
	.byte	-92
	.byte	-83
	.byte	-1
	.byte	-53
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-34
	.byte	-8
	.byte	-1
	.byte	-40
	.byte	-43
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-88
	.byte	-81
	.byte	-10
	.byte	-4
	.byte	-21
	.byte	-51
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	47
	.byte	116
	.byte	-41
	.byte	-1
	.byte	-45
	.byte	-44
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	121
	.byte	-20
	.byte	-3
	.byte	-44
	.byte	-42
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-115
	.byte	84
	.byte	-43
	.byte	-4
	.byte	-55
	.byte	-54
	.byte	-1
	.byte	-37
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	42
	.byte	80
	.byte	-96
	.byte	-16
	.byte	-94
	.byte	-71
	.byte	-1
	.byte	-51
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-12
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-18
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.type	VP8_VFMWBITREADER_NORM, %object
	.size	VP8_VFMWBITREADER_NORM, 256
VP8_VFMWBITREADER_NORM:
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
	.align	3
.LANCHOR2 = . + 0
	.type	vp8_mv_update_probs, %object
	.size	vp8_mv_update_probs, 38
vp8_mv_update_probs:
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
	.byte	-2
	.byte	-2
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
	.byte	-2
	.byte	-2
	.zero	2
	.type	vp8_coef_update_probs, %object
	.size	vp8_coef_update_probs, 1056
vp8_coef_update_probs:
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
	.byte	-80
	.byte	-10
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-33
	.byte	-15
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-3
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
	.byte	-12
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-22
	.byte	-2
	.byte	-2
	.byte	-1
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
	.byte	-10
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-17
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-1
	.byte	-2
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
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-3
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-6
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
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
	.byte	-39
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
	.byte	-4
	.byte	-15
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-22
	.byte	-6
	.byte	-15
	.byte	-6
	.byte	-3
	.byte	-1
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-33
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-18
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-2
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
	.byte	-9
	.byte	-2
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
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-4
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
	.byte	-2
	.byte	-2
	.byte	-1
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
	.byte	-2
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-6
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
	.byte	-2
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
	.byte	-70
	.byte	-5
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-22
	.byte	-5
	.byte	-12
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-5
	.byte	-13
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-20
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-3
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-2
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
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
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
	.byte	-2
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
	.byte	-6
	.byte	-2
	.byte	-4
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-2
	.byte	-7
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-10
	.byte	-3
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-4
	.byte	-2
	.byte	-5
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
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
	.byte	-2
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-11
	.byte	-5
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-4
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
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
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-1
	.byte	-2
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
	.byte	-2
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
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-6
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
	.byte	-2
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
	.type	__FUNCTION__.11638, %object
	.size	__FUNCTION__.11638, 17
__FUNCTION__.11638:
	.string	"VP8_DecodeDecide"
	.data
	.align	3
.LANCHOR1 = . + 0
	.type	default_ymode_prob, %object
	.size	default_ymode_prob, 4
default_ymode_prob:
	.byte	112
	.byte	86
	.byte	-116
	.byte	37
	.zero	4
	.type	default_uv_mode_prob, %object
	.size	default_uv_mode_prob, 3
default_uv_mode_prob:
	.byte	-94
	.byte	101
	.byte	-52
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC5:
	ASCII(.string	"line: %d\n" )
	.zero	6
.LC7:
	ASCII(.string	"pCurImg is null\n" )
	.zero	7
.LC9:
	ASCII(.string	"err_level(%d) over ref_thr(%d)\n" )
.LC11:
	ASCII(.string	"line: %d pToQueImg is null\n" )
	.zero	4
.LC13:
	ASCII(.string	"insert img to Voqueue failed!\n" )
	.zero	1
.LC17:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC26:
	ASCII(.string	"Error!partition 0 length > streamlength!\n" )
	.zero	6
.LC28:
	ASCII(.string	"Invalid frame sync code,data[0-1]:%02x,%02x,%02x\n" )
	.zero	6
.LC30:
	ASCII(.string	"Invalid frame width %d and Height %d!\n" )
	.zero	1
.LC32:
	ASCII(.string	"We have a new size image!\n" )
	.zero	5
.LC34:
	ASCII(.string	"The old size is %d x %d,the new is %d x %d\n" )
	.zero	4
.LC38:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC40:
	ASCII(.string	"vp8 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC43:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC45:
	ASCII(.string	"FSP_ConfigInstance fail!\n" )
	.zero	6
.LC47:
	ASCII(.string	"ERROR: No Img buffer is allocated\n" )
	.zero	5
.LC49:
	ASCII(.string	"----------------- vp8 Imode -> %d ------------------\n" )
	.zero	2
.LC51:
	ASCII(.string	"-----I_MODE, but FrameType is %d-----\n" )
	.zero	1
.LC53:
	ASCII(.string	"P-frm" )
	.zero	2
.LC55:
	ASCII(.string	"-----cur framtype is %s, but refnum=%d-----\n" )
	.zero	3
.LC57:
	ASCII(.string	"error: DecMode illegal\n" )
.LC60:
	ASCII(.string	"%s %d NULL == pFwdImg!!\n" )
	.zero	7
.LC62:
	ASCII(.string	"dec P frame, fwd ref err(%d) > ref_thr(%d)\n" )
	.zero	4
.LC65:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC67:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC69:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC71:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC74:
	ASCII(.string	"VP8_Set_DecParam but logic fs is null!\n" )
.LC76:
	ASCII(.string	"VP8_Set_DecParam but cur logic pstDecodeFs is null!\n" )
	.zero	3
.LC80:
	ASCII(.string	"Error!Truncated packet\n" )
.LC82:
	ASCII(.string	"VP8_CB_GetPictureHeader Error!\n" )
.LC85:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC87:
	ASCII(.string	"pic width/height to large,MbWidth = %d, MbHeight = %d" )
	.zero	2
.LC89:
	ASCII(.string	"VP8_ArrangeVHBMem error\n" )
	.zero	7
.LC91:
	ASCII(.string	"VP8_DecodeDecide err\n" )
	.zero	2
.LC93:
	ASCII(.string	"VP8_GetBufFromQueue err\n" )
	.zero	7
.LC96:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
