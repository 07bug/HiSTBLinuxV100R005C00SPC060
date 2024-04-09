#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"syntax.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	SYNTAX_GetVoQue, %function
SYNTAX_GetVoQue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	cmp	w0, 20
	bls	.L20
.L18:
	mov	x0, 0
	b	.L2
	.p2align 3
.L20:
	ldr	x1, .LC0
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx4
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx4:
	.section	.rodata
	.align	0
	.align	2
.L4:
	.byte	(.L17 - .Lrtx4) / 4
	.byte	(.L5 - .Lrtx4) / 4
	.byte	(.L6 - .Lrtx4) / 4
	.byte	(.L7 - .Lrtx4) / 4
	.byte	(.L18 - .Lrtx4) / 4
	.byte	(.L8 - .Lrtx4) / 4
	.byte	(.L9 - .Lrtx4) / 4
	.byte	(.L18 - .Lrtx4) / 4
	.byte	(.L10 - .Lrtx4) / 4
	.byte	(.L11 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L13 - .Lrtx4) / 4
	.byte	(.L18 - .Lrtx4) / 4
	.byte	(.L14 - .Lrtx4) / 4
	.byte	(.L15 - .Lrtx4) / 4
	.byte	(.L16 - .Lrtx4) / 4
	.byte	(.L18 - .Lrtx4) / 4
	.byte	(.L18 - .Lrtx4) / 4
	.byte	(.L17 - .Lrtx4) / 4
	.text
	.p2align 3
.L17:
	add	x0, x19, 16
.L2:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L9:
	add	x19, x19, 12288
	add	x0, x19, 3984
	b	.L2
	.p2align 3
.L10:
	add	x19, x19, 53248
	add	x0, x19, 1728
	b	.L2
	.p2align 3
.L11:
	add	x19, x19, 53248
	add	x0, x19, 1704
	b	.L2
	.p2align 3
.L6:
	add	x19, x19, 20480
	add	x0, x19, 2248
	b	.L2
	.p2align 3
.L8:
	add	x19, x19, 40960
	add	x0, x19, 1672
	b	.L2
	.p2align 3
.L15:
	add	x19, x19, 4096
	add	x0, x19, 1944
	b	.L2
	.p2align 3
.L13:
	add	x19, x19, 8192
	add	x0, x19, 48
	b	.L2
	.p2align 3
.L14:
	add	x0, x19, 920
	b	.L2
	.p2align 3
.L7:
	add	x19, x19, 86016
	add	x0, x19, 2784
	b	.L2
	.p2align 3
.L5:
	add	x19, x19, 53248
	add	x0, x19, 296
	b	.L2
	.p2align 3
.L16:
	add	x19, x19, 274432
	add	x0, x19, 1424
	b	.L2
	.p2align 3
.L12:
	add	x19, x19, 12288
	add	x0, x19, 480
	b	.L2
	.size	SYNTAX_GetVoQue, .-SYNTAX_GetVoQue
	.align	3
.LC0:
	.xword	.L4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintVoQueue
	.type	PrintVoQueue, %function
PrintVoQueue:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L28
	ldr	x1, .LC5
	mov	w0, 1
	ldrh	w4, [x20, 8]
	ldrh	w3, [x20, 4]
	ldrh	w2, [x20, 6]
	bl	dprint_vfmw
	ldr	x22, .LC7
	ldrh	w0, [x20, 4]
	ldrh	w1, [x20, 8]
	and	w19, w0, 63
	cmp	w19, w1
	beq	.L26
	ldr	x21, .LC9
	b	.L27
	.p2align 3
.L25:
	uxtw	x2, w19
	mov	x1, x21
	add	x2, x2, 2
	mov	w0, 1
	ldr	x2, [x20, x2, lsl 3]
	ldr	w2, [x2, 148]
	bl	dprint_vfmw
	add	w0, w19, 1
	ldrh	w1, [x20, 8]
	and	w19, w0, 63
	cmp	w19, w1
	beq	.L26
.L27:
	and	w0, w0, 7
	cbnz	w0, .L25
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	b	.L25
	.p2align 3
.L26:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L28:
	ldr	x2, .LC1
	mov	w3, 78
	ldr	x1, .LC3
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PrintVoQueue, .-PrintVoQueue
	.align	3
.LC1:
	.xword	.LANCHOR0
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC9:
	.xword	.LC8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetVoQueue
	.type	ResetVoQueue, %function
ResetVoQueue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L35
	ldr	x20, .LC12
	mov	w0, 2
	ldr	x1, [x20, 24]
	blr	x1
	ldrh	w2, [x19, 6]
	ldrh	w3, [x19, 4]
	ldrh	w4, [x19, 8]
	cmp	w2, w3
	beq	.L36
.L33:
	ldr	x1, .LC14
	mov	w0, 1
	bl	dprint_vfmw
.L34:
	add	x4, x19, 512
	strh	wzr, [x19, 2]
	strh	wzr, [x19, 4]
	mov	w0, 64
	strh	wzr, [x19, 6]
	mov	x3, -1
	strh	w0, [x19]
	mov	w0, -1
	strh	wzr, [x19, 8]
	ldr	w1, [x19, 600]
	ldr	x2, [x20, 32]
	stp	w0, w0, [x4, 16]
	stp	w0, w0, [x4, 24]
	add	w1, w1, 100
	str	w0, [x19, 544]
	str	w0, [x19, 548]
	mov	w0, 2
	str	x3, [x19, 584]
	str	w1, [x19, 600]
	str	wzr, [x19, 572]
	str	wzr, [x19, 580]
	str	xzr, [x19, 592]
	blr	x2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L36:
	cmp	w2, w4
	bne	.L33
	b	.L34
	.p2align 3
.L35:
	ldr	x2, .LC10
	mov	w3, 107
	ldr	x1, .LC11
	mov	w0, 1
	add	x2, x2, 16
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ResetVoQueue, .-ResetVoQueue
	.align	3
.LC10:
	.xword	.LANCHOR0
	.align	3
.LC11:
	.xword	.LC2
	.align	3
.LC12:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC14:
	.xword	.LC13
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReturnImageToSyntax
	.type	ReturnImageToSyntax, %function
ReturnImageToSyntax:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L55
	cmp	w21, 20
	bls	.L56
.L37:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L56:
	ldr	x0, .LC17
	ldrb	w0, [x0,w21,uxtw]
	adr	x1, .Lrtx41
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx41:
	.section	.rodata
	.align	0
	.align	2
.L41:
	.byte	(.L40 - .Lrtx41) / 4
	.byte	(.L42 - .Lrtx41) / 4
	.byte	(.L43 - .Lrtx41) / 4
	.byte	(.L44 - .Lrtx41) / 4
	.byte	(.L37 - .Lrtx41) / 4
	.byte	(.L45 - .Lrtx41) / 4
	.byte	(.L46 - .Lrtx41) / 4
	.byte	(.L37 - .Lrtx41) / 4
	.byte	(.L47 - .Lrtx41) / 4
	.byte	(.L48 - .Lrtx41) / 4
	.byte	(.L49 - .Lrtx41) / 4
	.byte	(.L49 - .Lrtx41) / 4
	.byte	(.L49 - .Lrtx41) / 4
	.byte	(.L50 - .Lrtx41) / 4
	.byte	(.L37 - .Lrtx41) / 4
	.byte	(.L51 - .Lrtx41) / 4
	.byte	(.L52 - .Lrtx41) / 4
	.byte	(.L53 - .Lrtx41) / 4
	.byte	(.L37 - .Lrtx41) / 4
	.byte	(.L37 - .Lrtx41) / 4
	.byte	(.L54 - .Lrtx41) / 4
	.text
	.p2align 3
.L55:
	ldr	x2, .LC15
	mov	w3, 151
	ldr	x1, .LC16
	mov	w0, 1
	add	x2, x2, 32
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L54:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	USERDEC_RecycleImage
	b	.L37
	.p2align 3
.L53:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	VP9DEC_RecycleImage
	b	.L37
	.p2align 3
.L52:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	HEVC_DECRecycleImage
	b	.L37
	.p2align 3
.L51:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	MVC_DEC_RecycleImage
	b	.L37
	.p2align 3
.L50:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	VP8DEC_RecycleImage
	b	.L37
	.p2align 3
.L49:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	VP6DEC_RecycleImage
	b	.L37
	.p2align 3
.L48:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	REAL9DEC_RecycleImage
	b	.L37
	.p2align 3
.L47:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	REAL8DEC_RecycleImage
	b	.L37
	.p2align 3
.L46:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	AVSDEC_RecycleImage
	b	.L37
	.p2align 3
.L45:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	DIVX3DEC_RecycleImage
	b	.L37
	.p2align 3
.L44:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	MPEG2DEC_RecycleImage
	b	.L37
	.p2align 3
.L43:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	MPEG4DEC_RecycleImage
	b	.L37
	.p2align 3
.L42:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	VC1DEC_RecycleImage
	b	.L37
	.p2align 3
.L40:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	H264DEC_RecycleImage
	b	.L37
	.size	ReturnImageToSyntax, .-ReturnImageToSyntax
	.align	3
.LC15:
	.xword	.LANCHOR0
	.align	3
.LC16:
	.xword	.LC2
	.align	3
.LC17:
	.xword	.L41
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertImgToVoQueue
	.type	InsertImgToVoQueue, %function
InsertImgToVoQueue:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w21, w0
	mov	x0, x30
	mov	w24, w1
	mov	x22, x2
	mov	x27, x3
	mov	x26, x4
	bl	_mcount
	cmp	w21, 31
	bhi	.L126
	cmp	x22, xzr
	ccmp	x27, xzr, 4, ne
	beq	.L127
	cbz	x26, .L128
	ldr	x1, .LC23
	mov	w0, 2
	bl	dprint_vfmw
	ldr	x20, .LC24
	mov	w0, 2
	ldr	x1, [x20, 24]
	blr	x1
	ldrh	w19, [x27, 4]
	ldrh	w3, [x27, 8]
	and	w19, w19, 63
	cmp	w19, w3
	beq	.L66
	ldr	x25, .LC26
	mov	w23, 1000
	b	.L123
	.p2align 3
.L65:
	add	w19, w19, 1
	and	w19, w19, 63
	cmp	w19, w3
	beq	.L66
.L123:
	sxtw	x0, w19
	ldr	w1, [x26, 148]
	add	x0, x0, 2
	ldr	x0, [x27, x0, lsl 3]
	ldr	w2, [x0, 148]
	cmp	w2, w1
	bne	.L65
	mov	x1, x25
	mov	w0, 0
	add	w19, w19, 1
	bl	dprint_vfmw
	str	w23, [x26, 152]
	and	w19, w19, 63
	ldrh	w3, [x27, 8]
	cmp	w19, w3
	bne	.L123
	.p2align 2
.L66:
	ldr	w2, [x26, 152]
	cmp	w2, 100
	bhi	.L129
	ldp	w3, w4, [x26, 68]
	cmp	w3, 31
	bhi	.L130
.L68:
	ldr	x1, .LC28
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x26, 152]
	cmp	w0, 1000
	beq	.L71
	mov	x2, x26
	mov	x1, x22
	mov	w0, w24
	bl	ReturnImageToSyntax
.L71:
	ldr	x1, [x20, 32]
	mov	w0, 2
	blr	x1
	mov	w0, 1
.L59:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L130:
	cmp	w4, 31
	bls	.L68
	add	x1, x26, 416
	mov	w0, w21
	str	w24, [x26, 216]
	bl	VCTRL_GetHDRConfigInfo
	ldr	x25, .LC29
	ldrb	w0, [x26, 66]
	ldr	x3, [x26, 584]
	ldr	x1, [x25, w21, sxtw 3]
	ldr	w1, [x1, 128]
	str	x3, [x26, 576]
	cmp	w1, 1
	cset	w1, eq
	cmp	w24, 20
	bfi	w0, w1, 2, 1
	strb	w0, [x26, 66]
	beq	.L90
	add	x19, x27, 528
	ldr	x0, [x19, 56]
	sub	w24, w24, #8
	sub	x1, x3, x0
	cmp	x1, 5
	ccmn	x0, #1, 4, ls
	beq	.L131
	cmp	w24, 1
	bls	.L74
	mov	x2, x3
	mov	x3, -1
.L72:
	ldr	x1, .LC31
	mov	w0, 29
	ldr	x4, [x26, 592]
	str	x3, [x26, 584]
	bl	dprint_vfmw
	ldr	w0, [x26, 76]
	cbz	w0, .L75
	ldr	w0, [x26, 80]
	cbz	w0, .L75
	ldr	w1, [x26, 68]
.L76:
	str	w1, [x19, 28]
	ldr	w2, [x19, 8]
	ldr	w0, [x26, 72]
	str	w0, [x19, 32]
	ldrb	w0, [x26, 64]
	ubfx	x0, x0, 5, 3
	str	w0, [x19, 36]
	ldr	w0, [x26, 64]
	str	w0, [x19, 40]
	ldr	w0, [x26, 148]
	add	w0, w0, 2
	str	w0, [x19, 24]
	ldrh	w1, [x26, 76]
	ldp	w22, w23, [x26, 80]
	ldrb	w5, [x26, 65]
	ldr	w0, [x26, 64]
	orr	w22, w1, w22, lsl 16
	ldr	w1, [x26, 156]
	ubfx	x5, x5, 0, 2
	ubfx	x0, x0, 14, 3
	cmp	w1, w2
	ldrh	w2, [x26, 88]
	uxtb	w28, w5
	uxtb	w4, w0
	orr	w23, w2, w23, lsl 16
	beq	.L77
	str	w1, [x19, 48]
.L77:
	ldr	w1, [x19, 44]
	ldr	x24, .LC32
	add	w2, w1, 1
	str	w2, [x19, 44]
	str	w1, [x26, 160]
	ldr	w1, [x27, 528]
	cmp	w4, w1
	beq	.L78
	ldr	x6, [x24]
	cbz	x6, .L79
	strb	w1, [x29, 120]
	mov	w3, 2
	strb	w0, [x29, 121]
	add	x2, x29, 120
	mov	w1, 7
	mov	w0, w21
	stp	w5, w4, [x29, 104]
	blr	x6
	ldp	w5, w4, [x29, 104]
.L79:
	str	w4, [x27, 528]
.L78:
	ldr	w0, [x19, 4]
	cmp	w28, w0
	beq	.L80
	ldr	x4, [x24]
	cbz	x4, .L81
	add	x2, x29, 128
	mov	w3, 1
	mov	w1, 4
	mov	w0, w21
	strb	w5, [x2, -8]!
	blr	x4
.L81:
	str	w28, [x19, 4]
.L80:
	ldr	w0, [x19, 16]
	cmp	w22, w0
	beq	.L132
.L82:
	ldr	x4, [x24]
	stp	w22, w23, [x19, 16]
	cbz	x4, .L83
	ldp	w2, w0, [x26, 76]
	ldr	w1, [x26, 84]
	mov	w3, 8
	strh	w0, [x29, 122]
	ldr	w0, [x26, 88]
	strh	w2, [x29, 120]
	add	x2, x29, 120
	strh	w1, [x29, 124]
	mov	w1, 1
	strh	w0, [x29, 126]
	mov	w0, w21
	blr	x4
.L83:
	ldp	w3, w2, [x26, 112]
	ldp	w1, w0, [x26, 36]
	stp	w1, w0, [x26, 20]
	add	w1, w3, w1
	add	w0, w2, w0
	stp	w1, w0, [x26, 28]
	ldr	w5, [x26, 148]
	mov	w0, 12
	ldrh	w4, [x27, 8]
	sxtw	x22, w21
	ldrh	w3, [x27, 6]
	ldrh	w2, [x27, 4]
	ldr	x1, .LC34
	bl	dprint_vfmw
	ldr	x23, .LC35
	ldrh	w0, [x27, 8]
	lsl	x2, x22, 2
	sub	x2, x2, x22
	add	w1, w0, 1
	add	x0, x0, 2
	and	w1, w1, 63
	add	x2, x23, x2, lsl 3
	str	x26, [x27, x0, lsl 3]
	mov	w0, w21
	strh	w1, [x27, 8]
	mov	w1, 5
	ldr	x3, [x25, w21, sxtw 3]
	add	x3, x3, 311296
	ldr	w4, [x3, 1600]
	add	w4, w4, 1
	str	w4, [x3, 1600]
	str	wzr, [x26, 264]
	ldr	w3, [x26, 52]
	str	w3, [x2, 20]
	ldr	w2, [x26, 160]
	bl	VDEC_Lowdelay_Event_Time
	ldr	x3, .LC36
	mov	w0, 2
	ldr	w1, [x26, 160]
	ldr	x2, [x20, 32]
	add	w1, w1, 1
	str	w1, [x3, w21, sxtw 2]
	blr	x2
	ldr	x4, [x24]
	cbz	x4, .L85
	mov	w3, 640
	mov	x2, x26
	mov	w1, 5
	mov	w0, w21
	blr	x4
.L85:
	mov	w0, 8
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L133
.L87:
	lsl	x19, x22, 2
	ldr	x1, [x20]
	sub	x19, x19, x22
	lsl	x19, x19, 3
	add	x20, x23, x19
	ldr	w0, [x20, 4]
	add	w0, w0, 1
	str	w0, [x20, 4]
	blr	x1
	mov	w2, w0
	ldr	w1, [x23, x19]
	mov	w0, 1
	sub	w1, w2, w1
	cmp	w1, 299
	bls	.L59
	ldr	w0, [x20, 4]
	cbz	w0, .L89
	mov	w3, 10000
	mul	w0, w0, w3
	udiv	w1, w0, w1
	str	w1, [x20, 8]
.L89:
	lsl	x1, x22, 2
	mov	w0, 1
	sub	x1, x1, x22
	lsl	x1, x1, 3
	add	x3, x23, x1
	str	w2, [x23, x1]
	str	wzr, [x3, 4]
	b	.L59
	.p2align 3
.L129:
	ldp	w3, w4, [x26, 68]
	b	.L68
.L131:
	cmp	w24, 1
	mov	x2, x3
	bhi	.L72
	ldrb	w0, [x26, 64]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L72
.L74:
	mov	x2, -1
	str	x2, [x26, 576]
	mov	x3, x2
	b	.L72
.L75:
	ldp	w1, w0, [x26, 68]
	stp	w1, w0, [x26, 76]
	lsr	w2, w1, 1
	lsr	w0, w0, 1
	str	w2, [x26, 84]
	str	w0, [x26, 88]
	b	.L76
.L133:
	ldr	x0, [x20]
	blr	x0
	mov	w4, w0
	ldr	x3, .LC37
	ldr	x1, .LC38
	ldr	w0, [x3, w21, sxtw 2]
	ldr	w1, [x1]
	sub	w0, w4, w0
	cmp	w0, w1
	bls	.L87
	ldr	x0, .LC18
	lsl	w2, w21, 24
	add	w2, w2, 524288
	mov	w1, 515
	add	x0, x0, 80
	str	w4, [x3, w21, sxtw 2]
	bl	DBG_AddTrace
	b	.L87
.L132:
	ldr	w0, [x19, 20]
	cmp	w23, w0
	bne	.L82
	b	.L83
.L90:
	mov	x2, x3
	add	x19, x27, 528
	b	.L72
.L126:
	ldr	x2, .LC18
	mov	w3, 396
	ldr	x1, .LC19
	mov	w0, 1
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -2
	b	.L59
.L127:
	ldr	x2, .LC18
	mov	w3, 397
	ldr	x1, .LC19
	mov	w0, 1
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -2
	b	.L59
.L128:
	ldr	x1, .LC21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L59
	.size	InsertImgToVoQueue, .-InsertImgToVoQueue
	.align	3
.LC18:
	.xword	.LANCHOR0
	.align	3
.LC19:
	.xword	.LC2
	.align	3
.LC21:
	.xword	.LC20
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC24:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC26:
	.xword	.LC25
	.align	3
.LC28:
	.xword	.LC27
	.align	3
.LC29:
	.xword	s_pstVfmwChan
	.align	3
.LC31:
	.xword	.LC30
	.align	3
.LC32:
	.xword	g_event_report
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC35:
	.xword	g_VfmwChanStat
	.align	3
.LC36:
	.xword	g_LowDelaySeqIndex
	.align	3
.LC37:
	.xword	.LANCHOR1
	.align	3
.LC38:
	.xword	g_TraceFramePeriod
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetQueueImgNum
	.type	GetQueueImgNum, %function
GetQueueImgNum:
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
	beq	.L142
	ldrh	w0, [x19, 6]
	ldrh	w3, [x19, 4]
	cmp	w0, w3
	bcs	.L143
	add	w1, w0, 64
	sub	w3, w1, w3
.L138:
	ldrh	w4, [x19, 8]
	cmp	w0, w4
	bls	.L141
	add	w4, w4, 64
.L141:
	str	w3, [x21]
	sub	w0, w4, w0
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L143:
	sub	w3, w0, w3
	b	.L138
	.p2align 3
.L142:
	ldr	x2, .LC39
	mov	w3, 556
	ldr	x1, .LC40
	mov	w0, 1
	add	x2, x2, 104
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetQueueImgNum, .-GetQueueImgNum
	.align	3
.LC39:
	.xword	.LANCHOR0
	.align	3
.LC40:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_ReceiveImage
	.type	SYNTAX_ReceiveImage, %function
SYNTAX_ReceiveImage:
	stp	x29, x30, [sp, -64]!
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
	beq	.L150
	mov	x0, x19
	bl	SYNTAX_GetVoQue
	mov	x19, x0
	cbz	x0, .L151
	ldr	x22, .LC45
	mov	w0, 2
	mov	w21, -3
	ldr	x1, [x22, 24]
	blr	x1
	ldrh	w1, [x19, 6]
	ldrh	w0, [x19, 8]
	cmp	w0, w1
	beq	.L148
	add	x1, x1, 2
	ldr	x3, [x22, 104]
	mov	x2, 640
	mov	x0, x20
	ldr	x23, [x20, 496]
	mov	w21, 1
	ldr	x1, [x19, x1, lsl 3]
	blr	x3
	str	x23, [x20, 496]
	ldr	x1, .LC47
	mov	w0, 12
	ldr	w5, [x20, 148]
	ldrh	w4, [x19, 8]
	ldrh	w3, [x19, 6]
	ldrh	w2, [x19, 4]
	bl	dprint_vfmw
	ldr	w1, [x20, 148]
	ldr	w0, [x19, 600]
	add	w0, w1, w0
	str	w0, [x20, 148]
	ldrh	w0, [x19, 6]
	add	w0, w0, w21
	and	w0, w0, 63
	strh	w0, [x19, 6]
.L148:
	ldr	x1, [x22, 32]
	mov	w0, 2
	blr	x1
	mov	w0, w21
.L146:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L150:
	ldr	x2, .LC41
	mov	w3, 671
	ldr	x1, .LC42
	mov	w0, 1
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -2
	b	.L146
.L151:
	ldr	x2, .LC41
	mov	w0, 1
	ldr	x1, .LC44
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -2
	b	.L146
	.size	SYNTAX_ReceiveImage, .-SYNTAX_ReceiveImage
	.align	3
.LC41:
	.xword	.LANCHOR0
	.align	3
.LC42:
	.xword	.LC2
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC45:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC47:
	.xword	.LC46
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_ReleaseImage
	.type	SYNTAX_ReleaseImage, %function
SYNTAX_ReleaseImage:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	x24, x1
	bl	_mcount
	cmp	x24, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L202
	mov	x0, x21
	bl	SYNTAX_GetVoQue
	mov	x25, x0
	cbz	x0, .L203
	ldr	x22, .LC52
	mov	w0, 2
	ldr	x1, [x22, 24]
	blr	x1
	ldrh	w20, [x25, 4]
	ldrh	w1, [x25, 6]
	and	w20, w20, 63
	ldr	w26, [x24, 148]
	ldr	w0, [x25, 600]
	cmp	w1, w20
	sub	w26, w26, w0
	beq	.L186
	ldr	x23, .LC56
	b	.L200
	.p2align 3
.L160:
	add	w20, w20, 1
	and	w20, w20, 63
	cmp	w20, w1
	beq	.L186
.L200:
	sxtw	x19, w20
	add	x0, x19, 2
	ldr	x0, [x25, x0, lsl 3]
	cbz	x0, .L158
	ldr	w0, [x0, 148]
	cmp	w26, w0
	bne	.L160
	mov	w5, 1
.L159:
	ldrh	w4, [x25, 4]
	b	.L162
	.p2align 3
.L190:
	mov	w20, w1
.L162:
	cmp	w20, wzr
	sub	w0, w20, #1
	mov	w1, 63
	add	x2, x19, 2
	csel	w1, w0, w1, ne
	cmp	w20, w4
	sxtw	x0, w1
	add	x3, x0, 2
	mov	x19, x0
	ldr	x0, [x25, x3, lsl 3]
	str	x0, [x25, x2, lsl 3]
	bne	.L190
	ldr	w0, [x24, 148]
	cmp	w5, 1
	ldr	w1, [x25, 600]
	sub	w0, w0, w1
	str	w0, [x24, 148]
	ldrh	w2, [x25, 4]
	add	w2, w2, 1
	and	w2, w2, 63
	strh	w2, [x25, 4]
	beq	.L199
	ldrh	w1, [x25, 6]
	add	w20, w20, 1
	and	w20, w20, 63
	cmp	w20, w1
	bne	.L200
.L186:
	ldr	x1, .LC54
	mov	w2, w26
	mov	w0, 1
	mov	w19, -2
	bl	dprint_vfmw
.L157:
	ldr	x1, [x22, 32]
	mov	w0, 2
	blr	x1
	mov	w0, w19
.L154:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L158:
	mov	w2, w20
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	mov	w5, 2
	b	.L159
.L199:
	ldr	x1, .LC58
	mov	w0, 12
	ldrh	w4, [x25, 8]
	ldrh	w3, [x25, 6]
	ldr	w5, [x24, 148]
	bl	dprint_vfmw
	ldr	w1, [x21]
	cmp	w1, 20
	bls	.L204
.L192:
	mov	w0, -2
.L163:
	cmp	w1, 17
	bls	.L205
.L179:
	cmn	w0, #2
	beq	.L196
	mov	w19, -20
	cmp	w0, 1
	csinc	w19, w19, wzr, ne
	b	.L157
.L204:
	ldr	x0, .LC59
	ldrb	w0, [x0,w1,uxtw]
	adr	x2, .Lrtx165
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx165:
	.section	.rodata
	.align	0
	.align	2
.L165:
	.byte	(.L164 - .Lrtx165) / 4
	.byte	(.L166 - .Lrtx165) / 4
	.byte	(.L167 - .Lrtx165) / 4
	.byte	(.L168 - .Lrtx165) / 4
	.byte	(.L192 - .Lrtx165) / 4
	.byte	(.L169 - .Lrtx165) / 4
	.byte	(.L170 - .Lrtx165) / 4
	.byte	(.L192 - .Lrtx165) / 4
	.byte	(.L171 - .Lrtx165) / 4
	.byte	(.L172 - .Lrtx165) / 4
	.byte	(.L173 - .Lrtx165) / 4
	.byte	(.L173 - .Lrtx165) / 4
	.byte	(.L173 - .Lrtx165) / 4
	.byte	(.L174 - .Lrtx165) / 4
	.byte	(.L192 - .Lrtx165) / 4
	.byte	(.L175 - .Lrtx165) / 4
	.byte	(.L176 - .Lrtx165) / 4
	.byte	(.L177 - .Lrtx165) / 4
	.byte	(.L192 - .Lrtx165) / 4
	.byte	(.L192 - .Lrtx165) / 4
	.byte	(.L178 - .Lrtx165) / 4
	.text
.L178:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	USERDEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L177:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	VP9DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L170:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	AVSDEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L169:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	DIVX3DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L168:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	MPEG2DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L167:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	MPEG4DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L166:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	VC1DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L164:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	H264DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L174:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	VP8DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L173:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	VP6DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L172:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	REAL9DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L171:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	REAL8DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L176:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	HEVC_DECRecycleImage
	ldr	w1, [x21]
	b	.L163
.L175:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	MVC_DEC_RecycleImage
	ldr	w1, [x21]
	b	.L163
.L205:
	ldr	x2, .LC60
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx181
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx181:
	.section	.rodata
	.align	0
	.align	2
.L181:
	.byte	(.L180 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L179 - .Lrtx181) / 4
	.byte	(.L184 - .Lrtx181) / 4
	.byte	(.L184 - .Lrtx181) / 4
	.byte	(.L184 - .Lrtx181) / 4
	.text
.L184:
	mov	w19, -20
	cmp	w0, wzr
	csinc	w19, w19, wzr, ne
	b	.L157
.L180:
	mov	w19, -20
	cmp	w0, wzr
	csinc	w19, w19, wzr, ne
	b	.L157
.L202:
	ldr	x1, .LC49
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L154
.L203:
	ldr	x2, .LC50
	mov	w0, 1
	ldr	x1, .LC51
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, -2
	b	.L154
.L196:
	mov	w19, w0
	b	.L157
	.size	SYNTAX_ReleaseImage, .-SYNTAX_ReleaseImage
	.align	3
.LC49:
	.xword	.LC48
	.align	3
.LC50:
	.xword	.LANCHOR0
	.align	3
.LC51:
	.xword	.LC43
	.align	3
.LC52:
	.xword	vfmw_Osal_Func_Ptr_S
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
	.xword	.L165
	.align	3
.LC60:
	.xword	.L181
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SYNTAX_ReturnImage
	.type	SYNTAX_ReturnImage, %function
SYNTAX_ReturnImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L226
	ldr	w0, [x19]
	cmp	w0, 20
	bls	.L227
.L225:
	mov	w0, -2
	b	.L208
	.p2align 3
.L227:
	ldr	x1, .LC63
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx210
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx210:
	.section	.rodata
	.align	0
	.align	2
.L210:
	.byte	(.L223 - .Lrtx210) / 4
	.byte	(.L211 - .Lrtx210) / 4
	.byte	(.L212 - .Lrtx210) / 4
	.byte	(.L213 - .Lrtx210) / 4
	.byte	(.L225 - .Lrtx210) / 4
	.byte	(.L214 - .Lrtx210) / 4
	.byte	(.L215 - .Lrtx210) / 4
	.byte	(.L225 - .Lrtx210) / 4
	.byte	(.L216 - .Lrtx210) / 4
	.byte	(.L217 - .Lrtx210) / 4
	.byte	(.L218 - .Lrtx210) / 4
	.byte	(.L218 - .Lrtx210) / 4
	.byte	(.L218 - .Lrtx210) / 4
	.byte	(.L219 - .Lrtx210) / 4
	.byte	(.L225 - .Lrtx210) / 4
	.byte	(.L220 - .Lrtx210) / 4
	.byte	(.L221 - .Lrtx210) / 4
	.byte	(.L222 - .Lrtx210) / 4
	.byte	(.L225 - .Lrtx210) / 4
	.byte	(.L225 - .Lrtx210) / 4
	.byte	(.L223 - .Lrtx210) / 4
	.text
	.p2align 3
.L223:
	add	x19, x19, 16
	.p2align 2
.L224:
	ldr	x20, .LC64
	mov	w0, 2
	ldr	x1, [x20, 24]
	blr	x1
	ldrh	w1, [x19, 6]
	mov	w0, 2
	sub	w1, w1, #1
	and	w1, w1, 63
	strh	w1, [x19, 6]
	ldr	x1, [x20, 32]
	blr	x1
	mov	w0, 1
.L208:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L220:
	add	x19, x19, 920
	b	.L224
	.p2align 3
.L219:
	add	x19, x19, 8192
	add	x19, x19, 48
	b	.L224
	.p2align 3
.L218:
	add	x19, x19, 12288
	add	x19, x19, 480
	b	.L224
	.p2align 3
.L217:
	add	x19, x19, 53248
	add	x19, x19, 1704
	b	.L224
	.p2align 3
.L222:
	add	x19, x19, 274432
	add	x19, x19, 1424
	b	.L224
	.p2align 3
.L221:
	add	x19, x19, 4096
	add	x19, x19, 1944
	b	.L224
	.p2align 3
.L212:
	add	x19, x19, 20480
	add	x19, x19, 2248
	b	.L224
	.p2align 3
.L211:
	add	x19, x19, 53248
	add	x19, x19, 296
	b	.L224
	.p2align 3
.L216:
	add	x19, x19, 53248
	add	x19, x19, 1728
	b	.L224
	.p2align 3
.L215:
	add	x19, x19, 12288
	add	x19, x19, 3984
	b	.L224
	.p2align 3
.L214:
	add	x19, x19, 40960
	add	x19, x19, 1672
	b	.L224
	.p2align 3
.L213:
	add	x19, x19, 86016
	add	x19, x19, 2784
	b	.L224
.L226:
	ldr	x2, .LC61
	mov	w3, 948
	ldr	x1, .LC62
	mov	w0, 1
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w0, -2
	b	.L208
	.size	SYNTAX_ReturnImage, .-SYNTAX_ReturnImage
	.align	3
.LC61:
	.xword	.LANCHOR0
	.align	3
.LC62:
	.xword	.LC2
	.align	3
.LC63:
	.xword	.L210
	.align	3
.LC64:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_H264
	.type	DecodeStream_H264, %function
DecodeStream_H264:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L234
	ldr	x2, [x19, 8]
	add	x1, x29, 40
	ldrb	w4, [x19, 17]
	mov	x0, x20
	ldp	w6, w5, [x19, 24]
	ldr	w3, [x19, 32]
	ldr	x7, [x19, 40]
	str	x2, [x29, 48]
	ldrb	w2, [x19, 20]
	strb	w4, [x29, 40]
	stp	w6, w5, [x29, 56]
	str	w3, [x29, 64]
	str	x7, [x29, 72]
	strb	w2, [x29, 41]
	bl	H264DEC_DecodePacket
	cmn	w0, #2
	add	x0, x20, 65536
	beq	.L235
	strb	wzr, [x19, 1]
	ldr	x1, .LC67
	ldrsw	x2, [x0, 1980]
	ldr	x1, [x1, x2, lsl 3]
	strb	wzr, [x1, 1624]
.L232:
	ldr	x1, [x20, 616]
	cbz	x1, .L236
.L228:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L234:
	ldr	x2, .LC65
	mov	w3, 1051
	ldr	x1, .LC66
	mov	w0, 1
	add	x2, x2, 192
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L235:
	mov	w1, 1
	strb	w1, [x19, 1]
	ldr	x2, .LC67
	ldrsw	x3, [x0, 1980]
	ldr	x2, [x2, x3, lsl 3]
	strb	w1, [x2, 1624]
	b	.L232
	.p2align 3
.L236:
	add	x20, x20, 12288
	ldrb	w1, [x20, 2640]
	cmp	w1, 1
	bne	.L228
	ldr	w0, [x0, 1980]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 2640]
	b	.L228
	.size	DecodeStream_H264, .-DecodeStream_H264
	.align	3
.LC65:
	.xword	.LANCHOR0
	.align	3
.LC66:
	.xword	.LC2
	.align	3
.LC67:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_HEVC
	.type	DecodeStream_HEVC, %function
DecodeStream_HEVC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L247
	ldp	w5, w4, [x19, 24]
	ldrb	w3, [x19, 17]
	add	x1, x29, 32
	ldr	w2, [x19, 32]
	mov	x0, x20
	ldr	x6, [x19, 8]
	strb	w3, [x29, 32]
	str	x6, [x29, 40]
	str	w5, [x29, 48]
	stp	w4, w2, [x29, 56]
	bl	HEVCDEC_DecodePacket
	cmn	w0, #2
	beq	.L240
	ldrb	w0, [x20, 7]
	cbnz	w0, .L240
	strb	wzr, [x19, 1]
	ldr	x0, .LC70
	ldrsw	x1, [x20, 252]
	ldr	x0, [x0, x1, lsl 3]
	strb	wzr, [x0, 1624]
.L242:
	ldr	x0, [x20, 2448]
	cbz	x0, .L248
.L237:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L240:
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x1, .LC70
	ldrsw	x2, [x20, 252]
	ldr	x1, [x1, x2, lsl 3]
	strb	w0, [x1, 1624]
	b	.L242
	.p2align 3
.L247:
	ldr	x2, .LC68
	mov	w3, 1091
	ldr	x1, .LC69
	mov	w0, 1
	add	x2, x2, 216
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L248:
	ldrb	w0, [x20, 9]
	cmp	w0, 1
	bne	.L237
	ldr	w0, [x20, 252]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 9]
	b	.L237
	.size	DecodeStream_HEVC, .-DecodeStream_HEVC
	.align	3
.LC68:
	.xword	.LANCHOR0
	.align	3
.LC69:
	.xword	.LC2
	.align	3
.LC70:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VP9
	.type	DecodeStream_VP9, %function
DecodeStream_VP9:
	stp	x29, x30, [sp, -64]!
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
	beq	.L265
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L266
	ldr	x23, .LC73
	add	x22, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x22
	add	x21, x20, 294912
	ldr	x3, [x23, 104]
	blr	x3
	ldr	x3, [x23, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x22
	mov	x0, x20
	bl	VP9DEC_DecodePacket
	ldr	w0, [x21, 3828]
	cbz	w0, .L253
	ldr	w0, [x21, 3864]
	ldr	w1, [x21, 3868]
	cmp	w1, w0
	beq	.L253
.L254:
	mov	w0, 1
	strb	w0, [x19, 1]
.L249:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L253:
	ldr	w0, [x21, 3824]
	cbnz	w0, .L254
	strb	wzr, [x19, 1]
	ldr	x0, [x20, 8]
	cbnz	x0, .L249
	add	x20, x20, 262144
	ldrb	w0, [x20, 1044]
	cbnz	w0, .L249
	ldr	x3, [x23, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x21, 3928]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC74
	ldr	x4, [x0]
	cbz	x4, .L249
	ldr	w0, [x21, 3928]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L249
	.p2align 3
.L265:
	ldr	x2, .LC71
	mov	w3, 1127
	ldr	x1, .LC72
	mov	w0, 1
	add	x2, x2, 240
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L266:
	add	x20, x20, 294912
	ldr	w0, [x20, 3928]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 3928]
	bl	SM_ReleaseStreamSeg
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	DecodeStream_VP9, .-DecodeStream_VP9
	.align	3
.LC71:
	.xword	.LANCHOR0
	.align	3
.LC72:
	.xword	.LC2
	.align	3
.LC73:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC74:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_MVC
	.type	DecodeStream_MVC, %function
DecodeStream_MVC:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L273
	ldrb	w3, [x19, 17]
	add	x1, x29, 40
	ldp	w5, w4, [x19, 24]
	ldr	w2, [x19, 32]
	mov	x0, x20
	ldr	x6, [x19, 8]
	ldr	x7, [x19, 40]
	strb	w3, [x29, 40]
	str	x6, [x29, 48]
	stp	w5, w4, [x29, 56]
	str	w2, [x29, 64]
	str	x7, [x29, 72]
	bl	MVC_DEC_DecodePacket
	cmn	w0, #2
	beq	.L274
	strb	wzr, [x19, 1]
.L271:
	ldr	x0, [x20, 232]
	cbz	x0, .L275
.L267:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L273:
	ldr	x2, .LC75
	mov	w3, 1169
	ldr	x1, .LC76
	mov	w0, 1
	add	x2, x2, 264
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L274:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L271
	.p2align 3
.L275:
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	bne	.L267
	ldr	w0, [x20, 120]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 1]
	b	.L267
	.size	DecodeStream_MVC, .-DecodeStream_MVC
	.align	3
.LC75:
	.xword	.LANCHOR0
	.align	3
.LC76:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VC1_Smp
	.type	DecodeStream_VC1_Smp, %function
DecodeStream_VC1_Smp:
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
	beq	.L290
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L291
	ldr	x21, .LC79
	add	x22, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x22
	ldr	x3, [x21, 104]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	ldr	w0, [x19, 116]
	cmp	w0, 15
	bgt	.L280
	ldr	x1, .LC81
.L289:
	mov	w0, 0
	add	x20, x20, 53248
	bl	dprint_vfmw
	ldr	w1, [x19, 120]
	ldr	w0, [x20, 896]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC82
	ldr	x4, [x0]
	cbz	x4, .L276
	ldr	w0, [x20, 896]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L276:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L280:
	add	x2, x20, 16384
	ldr	x0, [x19, 96]
	add	x2, x2, 1528
	mov	w1, 16
	bl	Vc1SMPSeqHdr
	cbz	w0, .L292
	ldr	x1, .LC84
	b	.L289
	.p2align 3
.L290:
	ldr	x2, .LC77
	mov	w3, 1235
	ldr	x1, .LC78
	mov	w0, 1
	add	x2, x2, 288
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L292:
	ldp	w0, w3, [x19, 112]
	ldr	x2, [x19, 96]
	mov	x1, x22
	add	w0, w0, 16
	sub	w3, w3, #16
	add	x2, x2, 16
	str	x2, [x19, 96]
	stp	w0, w3, [x19, 112]
	mov	x0, x20
	bl	VC1DEC_Decode
	ldr	x3, [x21, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L291:
	add	x20, x20, 53248
	ldr	w0, [x20, 896]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 896]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	DecodeStream_VC1_Smp, .-DecodeStream_VC1_Smp
	.align	3
.LC77:
	.xword	.LANCHOR0
	.align	3
.LC78:
	.xword	.LC2
	.align	3
.LC79:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC82:
	.xword	g_event_report
	.align	3
.LC84:
	.xword	.LC83
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_REAL8
	.type	DecodeStream_REAL8, %function
DecodeStream_REAL8:
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
	beq	.L304
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L305
	ldr	x22, .LC87
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	REAL8DEC_Decode
	cmn	w0, #2
	beq	.L306
	strb	wzr, [x19, 1]
.L298:
	ldr	x0, [x20, 8]
	cbz	x0, .L307
.L293:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L304:
	ldr	x2, .LC85
	mov	w3, 1474
	ldr	x1, .LC86
	mov	w0, 1
	add	x2, x2, 312
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L306:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L298
	.p2align 3
.L305:
	add	x20, x20, 53248
	ldr	w0, [x20, 2328]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 2328]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L307:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 53248
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 2328]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC88
	ldr	x4, [x0]
	cbz	x4, .L293
	ldr	w0, [x20, 2328]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L293
	.size	DecodeStream_REAL8, .-DecodeStream_REAL8
	.align	3
.LC85:
	.xword	.LANCHOR0
	.align	3
.LC86:
	.xword	.LC2
	.align	3
.LC87:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC88:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_REAL9
	.type	DecodeStream_REAL9, %function
DecodeStream_REAL9:
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
	beq	.L319
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L320
	ldr	x22, .LC91
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	REAL9DEC_Decode
	cmn	w0, #2
	beq	.L321
	strb	wzr, [x19, 1]
.L313:
	ldr	x0, [x20, 8]
	cbz	x0, .L322
.L308:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L319:
	ldr	x2, .LC89
	mov	w3, 1511
	ldr	x1, .LC90
	mov	w0, 1
	add	x2, x2, 336
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L321:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L313
	.p2align 3
.L320:
	add	x20, x20, 53248
	ldr	w0, [x20, 2304]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 2304]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L322:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 53248
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 2304]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC92
	ldr	x4, [x0]
	cbz	x4, .L308
	ldr	w0, [x20, 2304]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L308
	.size	DecodeStream_REAL9, .-DecodeStream_REAL9
	.align	3
.LC89:
	.xword	.LANCHOR0
	.align	3
.LC90:
	.xword	.LC2
	.align	3
.LC91:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC92:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_DIVX3
	.type	DecodeStream_DIVX3, %function
DecodeStream_DIVX3:
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
	beq	.L334
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L335
	ldr	x22, .LC95
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	DIVX3DEC_Decode
	cmn	w0, #2
	beq	.L336
	strb	wzr, [x19, 1]
.L328:
	ldr	x0, [x20, 8]
	cbz	x0, .L337
.L323:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L334:
	ldr	x2, .LC93
	mov	w3, 1553
	ldr	x1, .LC94
	mov	w0, 1
	add	x2, x2, 360
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L336:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L328
	.p2align 3
.L335:
	add	x20, x20, 40960
	ldr	w0, [x20, 2272]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 2272]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L337:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	add	x20, x20, 40960
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 2272]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC96
	ldr	x4, [x0]
	cbz	x4, .L323
	ldr	w0, [x20, 2272]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L323
	.size	DecodeStream_DIVX3, .-DecodeStream_DIVX3
	.align	3
.LC93:
	.xword	.LANCHOR0
	.align	3
.LC94:
	.xword	.LC2
	.align	3
.LC95:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC96:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VP8
	.type	DecodeStream_VP8, %function
DecodeStream_VP8:
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
	beq	.L349
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L350
	ldr	x22, .LC99
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	VP8DEC_Decode
	cmn	w0, #2
	beq	.L351
	strb	wzr, [x19, 1]
.L343:
	ldr	x0, [x20, 8]
	cbz	x0, .L352
.L338:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L349:
	ldr	x2, .LC97
	mov	w3, 1595
	ldr	x1, .LC98
	mov	w0, 1
	add	x2, x2, 384
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L351:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L343
	.p2align 3
.L350:
	ldr	w0, [x20, 8840]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 8840]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L352:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 8840]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC100
	ldr	x4, [x0]
	cbz	x4, .L338
	ldr	w0, [x20, 8840]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L338
	.size	DecodeStream_VP8, .-DecodeStream_VP8
	.align	3
.LC97:
	.xword	.LANCHOR0
	.align	3
.LC98:
	.xword	.LC2
	.align	3
.LC99:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC100:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VP6x
	.type	DecodeStream_VP6x, %function
DecodeStream_VP6x:
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
	beq	.L364
	ldrb	w0, [x19, 18]
	cmp	w0, 1
	beq	.L365
	ldr	x22, .LC103
	add	x21, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x21
	ldr	x3, [x22, 104]
	blr	x3
	ldr	x3, [x22, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	mov	x1, x21
	mov	x0, x20
	bl	VP6DEC_Decode
	cmn	w0, #2
	beq	.L366
	strb	wzr, [x19, 1]
.L358:
	ldr	x0, [x20, 8]
	cbz	x0, .L367
.L353:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L364:
	ldr	x2, .LC101
	mov	w3, 1636
	ldr	x1, .LC102
	mov	w0, 1
	add	x2, x2, 408
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L366:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L358
	.p2align 3
.L365:
	ldr	w0, [x20, 13368]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 13368]
	bl	SM_ReleaseStreamSeg
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L367:
	ldr	x3, [x22, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x21
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 13368]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC104
	ldr	x4, [x0]
	cbz	x4, .L353
	ldr	w0, [x20, 13368]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L353
	.size	DecodeStream_VP6x, .-DecodeStream_VP6x
	.align	3
.LC101:
	.xword	.LANCHOR0
	.align	3
.LC102:
	.xword	.LC2
	.align	3
.LC103:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC104:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SegMan
	.type	SegMan, %function
SegMan:
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
	bhi	.L390
	cbz	x19, .L371
	ldr	x0, [x19, 8]
	cbz	x0, .L371
	ldr	x1, .LC109
	ldr	x1, [x1, w20, sxtw 3]
	ldr	w2, [x1, 1552]
	cmp	w2, 1
	beq	.L391
.L373:
	ldrb	w1, [x19, 17]
	strb	wzr, [x19, 448]
	cmp	w1, 1
	beq	.L392
	cbnz	w1, .L389
	ldr	x21, .LC110
	add	x23, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x23
	add	x22, x19, 184
	ldr	x3, [x21, 104]
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldrb	w0, [x19, 2]
	add	w0, w0, 1
	uxtb	w0, w0
	strb	w0, [x19, 2]
	cmp	w0, 1
	bls	.L389
	ldr	w1, [x19, 120]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	w1, [x19, 208]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	x3, [x21, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x23
	blr	x3
	ldr	x3, [x21, 96]
	mov	x2, 88
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	x1, .LC112
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC113
	ldr	x4, [x0]
	cbz	x4, .L377
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	mov	w0, w20
	blr	x4
.L377:
	strb	wzr, [x19, 2]
.L389:
	mov	w0, -1
.L388:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L391:
	ldr	w1, [x1, 1600]
	cmp	w1, 1
	bne	.L373
	ldrb	w1, [x19, 448]
	cmp	w1, 1
	bne	.L373
	mov	x2, 176
	add	x1, x19, 272
	add	x0, x19, 96
	bl	memcpy
	strb	wzr, [x19, 448]
	mov	w0, 0
	b	.L388
	.p2align 3
.L392:
	ldrb	w21, [x19, 2]
	cbz	w21, .L393
	cmp	w21, 1
	bne	.L389
	ldr	w2, [x19, 116]
	cmp	w2, 1023
	bgt	.L379
	ldr	x22, .LC110
	sxtw	x2, w2
	ldr	x1, [x19, 96]
	sub	x0, x0, x2
	ldr	x3, [x22, 104]
	blr	x3
	strb	w21, [x19, 105]
	ldp	w0, w1, [x19, 116]
	ldp	w2, w4, [x19, 24]
	ldr	x3, [x19, 8]
	sub	w2, w2, w0
	sub	x3, x3, x0, sxtw
	add	w0, w4, w0
	str	x3, [x19, 96]
	stp	w2, w0, [x19, 112]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x19, 32]
	mov	x2, 88
	ldr	x3, [x22, 96]
	mov	w1, 0
	str	w0, [x19, 120]
	add	x0, x19, 184
	blr	x3
.L380:
	mov	w0, 1
	add	x1, x19, 96
	strb	w0, [x19, 448]
	mov	x2, 176
	strb	wzr, [x19, 2]
	add	x0, x19, 272
	bl	memcpy
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L379:
	ldr	x3, .LC110
	mov	x2, 88
	add	x1, x19, 8
	add	x0, x19, 184
	ldr	x3, [x3, 104]
	blr	x3
	b	.L380
	.p2align 3
.L393:
	ldr	x20, .LC110
	mov	x2, 88
	add	x1, x19, 8
	add	x0, x19, 96
	ldr	x3, [x20, 104]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 88
	mov	w1, 0
	add	x0, x19, 184
	blr	x3
	strb	wzr, [x19, 2]
	mov	w0, 0
	b	.L388
	.p2align 3
.L390:
	ldr	x2, .LC105
	mov	w3, 1768
	ldr	x1, .LC106
	mov	w0, 1
	add	x2, x2, 432
	bl	dprint_vfmw
	mov	w0, -1
	b	.L388
	.p2align 3
.L371:
	ldr	x1, .LC108
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L388
	.size	SegMan, .-SegMan
	.align	3
.LC105:
	.xword	.LANCHOR0
	.align	3
.LC106:
	.xword	.LC2
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC109:
	.xword	s_pstVfmwChan
	.align	3
.LC110:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC113:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VC1_Adv
	.type	DecodeStream_VC1_Adv, %function
DecodeStream_VC1_Adv:
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
	beq	.L400
	add	x21, x19, 53248
	mov	x0, x19
	ldr	w22, [x21, 896]
	bl	VC1_GetPacketState
	cmp	w0, 2
	beq	.L401
.L397:
	ldr	w0, [x21, 896]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L402
.L399:
	ldr	x0, [x19, 8]
	cbz	x0, .L403
.L394:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L400:
	ldr	x2, .LC114
	mov	w3, 1202
	ldr	x1, .LC115
	mov	w0, 1
	add	x2, x2, 440
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L402:
	add	x20, x20, 96
	mov	x0, x19
	mov	x1, x20
	bl	VC1DEC_Decode
	ldr	x3, .LC117
	mov	x2, 176
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 8]
	cbnz	x0, .L394
	b	.L403
	.p2align 3
.L401:
	ldr	x0, .LC116
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	bne	.L398
	ldr	w0, [x0, 1600]
	cbnz	w0, .L397
.L398:
	add	x1, x19, 12288
	mov	x0, x19
	add	x1, x1, 2344
	bl	VC1DEC_Decode
	ldr	w0, [x21, 896]
	mov	x1, x20
	bl	SegMan
	cbnz	w0, .L399
	b	.L402
	.p2align 3
.L403:
	add	x19, x19, 12288
	ldrb	w0, [x19, 2527]
	cmp	w0, 1
	bne	.L394
	ldr	w0, [x21, 896]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19, 2527]
	b	.L394
	.size	DecodeStream_VC1_Adv, .-DecodeStream_VC1_Adv
	.align	3
.LC114:
	.xword	.LANCHOR0
	.align	3
.LC115:
	.xword	.LC2
	.align	3
.LC116:
	.xword	s_pstVfmwChan
	.align	3
.LC117:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_VC1
	.type	DecodeStream_VC1, %function
DecodeStream_VC1:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L410
	ldrb	w2, [x19, 17]
	mov	w0, 22
	ldr	x1, .LC121
	bl	dprint_vfmw
	ldr	x1, .LC123
	mov	w0, 22
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	x1, .LC125
	mov	w0, 22
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	x1, [x20]
	ldr	w0, [x1, 604]
	cmp	w0, 1
	bhi	.L411
	ldr	w2, [x1, 608]
	cmp	w2, 8
	bgt	.L412
	add	x2, x20, 16384
	sxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x2, 1528]
	ldr	w0, [x1, 608]
	mov	x1, x20
	strb	w0, [x2, 1530]
	mov	x0, x19
	beq	.L413
	bl	DecodeStream_VC1_Smp
.L404:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L411:
	ldr	x1, .LC127
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L410:
	ldr	x2, .LC118
	mov	w3, 1286
	ldr	x1, .LC119
	mov	w0, 1
	add	x2, x2, 464
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L412:
	ldr	x1, .LC129
	mov	w0, 0
	bl	dprint_vfmw
	b	.L404
	.p2align 3
.L413:
	bl	DecodeStream_VC1_Adv
	b	.L404
	.size	DecodeStream_VC1, .-DecodeStream_VC1
	.align	3
.LC118:
	.xword	.LANCHOR0
	.align	3
.LC119:
	.xword	.LC2
	.align	3
.LC121:
	.xword	.LC120
	.align	3
.LC123:
	.xword	.LC122
	.align	3
.LC125:
	.xword	.LC124
	.align	3
.LC127:
	.xword	.LC126
	.align	3
.LC129:
	.xword	.LC128
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_MPEG2
	.type	DecodeStream_MPEG2, %function
DecodeStream_MPEG2:
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
	beq	.L421
	add	x21, x19, 86016
	mov	x0, x19
	ldr	w22, [x21, 3384]
	bl	MP2_GetPacketState
	cmp	w0, 2
	beq	.L422
.L417:
	ldr	w0, [x21, 3384]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L423
.L419:
	ldr	x0, [x19, 8]
	cbz	x0, .L424
.L414:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L421:
	ldr	x2, .LC130
	mov	w3, 1326
	ldr	x1, .LC131
	mov	w0, 1
	add	x2, x2, 488
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L423:
	add	x1, x20, 96
	mov	x0, x19
	bl	MPEG2DEC_Decode
	ldrb	w0, [x21, 3401]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	strb	w0, [x20, 1]
	ldr	x0, [x19, 8]
	cbnz	x0, .L414
	b	.L424
	.p2align 3
.L422:
	ldr	x0, .LC132
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	bne	.L418
	ldr	w0, [x0, 1600]
	cbnz	w0, .L417
.L418:
	add	x1, x21, 2192
	mov	x0, x19
	bl	MPEG2DEC_Decode
	ldr	w0, [x21, 3384]
	mov	x1, x20
	bl	SegMan
	cbnz	w0, .L419
	b	.L423
	.p2align 3
.L424:
	ldrb	w0, [x21, 3402]
	cmp	w0, 1
	bne	.L414
	ldr	w0, [x21, 3384]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x21, 3402]
	b	.L414
	.size	DecodeStream_MPEG2, .-DecodeStream_MPEG2
	.align	3
.LC130:
	.xword	.LANCHOR0
	.align	3
.LC131:
	.xword	.LC2
	.align	3
.LC132:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_MPEG4
	.type	DecodeStream_MPEG4, %function
DecodeStream_MPEG4:
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
	beq	.L431
	add	x21, x19, 20480
	mov	x0, x19
	ldr	w22, [x21, 2848]
	bl	MP4_GetPacketState
	cmp	w0, 3
	beq	.L432
.L428:
	ldr	w0, [x21, 2848]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L433
.L430:
	ldr	x0, [x19, 1040]
	cbz	x0, .L434
.L425:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L431:
	ldr	x2, .LC133
	mov	w3, 1371
	ldr	x1, .LC134
	mov	w0, 1
	add	x2, x2, 512
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L433:
	add	x1, x20, 96
	mov	x0, x19
	bl	MPEG4DEC_Decode
	ldr	x0, [x19, 1040]
	cbnz	x0, .L425
	b	.L434
	.p2align 3
.L432:
	ldr	x0, .LC135
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	bne	.L429
	ldr	w0, [x0, 1600]
	cbnz	w0, .L428
.L429:
	add	x1, x19, 12288
	mov	x0, x19
	add	x1, x1, 3440
	bl	MPEG4DEC_Decode
	ldr	w0, [x21, 2848]
	mov	x1, x20
	bl	SegMan
	cbnz	w0, .L430
	b	.L433
	.p2align 3
.L434:
	ldrb	w0, [x21, 2884]
	cmp	w0, 1
	bne	.L425
	ldr	w0, [x21, 2848]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x21, 2884]
	b	.L425
	.size	DecodeStream_MPEG4, .-DecodeStream_MPEG4
	.align	3
.LC133:
	.xword	.LANCHOR0
	.align	3
.LC134:
	.xword	.LC2
	.align	3
.LC135:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream_AVS
	.type	DecodeStream_AVS, %function
DecodeStream_AVS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L441
	mov	x0, x19
	ldr	w21, [x19, 4]
	bl	AVS_GetPacketState
	cbnz	w0, .L438
	ldr	x0, .LC138
	ldr	x0, [x0, w21, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	beq	.L442
.L439:
	add	x1, x19, 16384
	mov	x0, x19
	add	x1, x1, 496
	bl	AVSDEC_Decode
.L438:
	ldr	w0, [x19, 4]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L443
	ldr	x0, [x19, 24]
	cbz	x0, .L444
.L435:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L441:
	ldr	x2, .LC136
	mov	w3, 1407
	ldr	x1, .LC137
	mov	w0, 1
	add	x2, x2, 536
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L443:
	add	x1, x20, 96
	mov	x0, x19
	bl	AVSDEC_Decode
	ldr	x0, [x19, 24]
	cbnz	x0, .L435
	b	.L444
	.p2align 3
.L442:
	ldr	w0, [x0, 1600]
	cbnz	w0, .L438
	b	.L439
	.p2align 3
.L444:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L435
	ldr	w0, [x19, 4]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19]
	b	.L435
	.size	DecodeStream_AVS, .-DecodeStream_AVS
	.align	3
.LC136:
	.xword	.LANCHOR0
	.align	3
.LC137:
	.xword	.LC2
	.align	3
.LC138:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecodeStream
	.type	DecodeStream, %function
DecodeStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	w21, w1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L464
	mov	w0, 6
	bl	VCTRL_RecordPosTime
	cmp	w21, 17
	bls	.L465
.L448:
	ldr	x2, .LC139
	mov	w3, 1756
	ldr	x1, .LC143
	mov	w0, 32
	add	x2, x2, 560
	bl	dprint_vfmw
.L463:
	mov	w0, 7
	bl	VCTRL_RecordPosTime
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L465:
	ldr	x0, .LC141
	ldrb	w0, [x0,w21,uxtw]
	adr	x1, .Lrtx450
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx450:
	.section	.rodata
	.align	0
	.align	2
.L450:
	.byte	(.L449 - .Lrtx450) / 4
	.byte	(.L451 - .Lrtx450) / 4
	.byte	(.L452 - .Lrtx450) / 4
	.byte	(.L453 - .Lrtx450) / 4
	.byte	(.L448 - .Lrtx450) / 4
	.byte	(.L454 - .Lrtx450) / 4
	.byte	(.L455 - .Lrtx450) / 4
	.byte	(.L448 - .Lrtx450) / 4
	.byte	(.L456 - .Lrtx450) / 4
	.byte	(.L457 - .Lrtx450) / 4
	.byte	(.L458 - .Lrtx450) / 4
	.byte	(.L458 - .Lrtx450) / 4
	.byte	(.L458 - .Lrtx450) / 4
	.byte	(.L459 - .Lrtx450) / 4
	.byte	(.L448 - .Lrtx450) / 4
	.byte	(.L460 - .Lrtx450) / 4
	.byte	(.L461 - .Lrtx450) / 4
	.byte	(.L462 - .Lrtx450) / 4
	.text
	.p2align 3
.L464:
	ldr	x2, .LC139
	mov	w3, 1676
	ldr	x1, .LC140
	mov	w0, 1
	add	x2, x2, 560
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L449:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_H264
	b	.L463
	.p2align 3
.L451:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_VC1
	b	.L463
	.p2align 3
.L452:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_MPEG4
	b	.L463
	.p2align 3
.L453:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_MPEG2
	b	.L463
	.p2align 3
.L454:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_DIVX3
	b	.L463
	.p2align 3
.L455:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_AVS
	b	.L463
	.p2align 3
.L456:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_REAL8
	b	.L463
	.p2align 3
.L457:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_REAL9
	b	.L463
	.p2align 3
.L458:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_VP6x
	b	.L463
	.p2align 3
.L459:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_VP8
	b	.L463
	.p2align 3
.L460:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_MVC
	b	.L463
	.p2align 3
.L461:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_HEVC
	b	.L463
	.p2align 3
.L462:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_VP9
	b	.L463
	.size	DecodeStream, .-DecodeStream
	.align	3
.LC139:
	.xword	.LANCHOR0
	.align	3
.LC140:
	.xword	.LC2
	.align	3
.LC141:
	.xword	.L450
	.align	3
.LC143:
	.xword	.LC142
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleasePacket
	.type	ReleasePacket, %function
ReleasePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L492
	sub	w0, w20, #5
	cmp	w0, 12
	bls	.L493
.L469:
	ldr	x1, .LC155
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
.L466:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L493:
	ldr	x1, .LC146
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx471
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx471:
	.section	.rodata
	.align	0
	.align	2
.L471:
	.byte	(.L470 - .Lrtx471) / 4
	.byte	(.L469 - .Lrtx471) / 4
	.byte	(.L469 - .Lrtx471) / 4
	.byte	(.L472 - .Lrtx471) / 4
	.byte	(.L473 - .Lrtx471) / 4
	.byte	(.L474 - .Lrtx471) / 4
	.byte	(.L474 - .Lrtx471) / 4
	.byte	(.L474 - .Lrtx471) / 4
	.byte	(.L475 - .Lrtx471) / 4
	.byte	(.L469 - .Lrtx471) / 4
	.byte	(.L469 - .Lrtx471) / 4
	.byte	(.L469 - .Lrtx471) / 4
	.byte	(.L476 - .Lrtx471) / 4
	.text
	.p2align 3
.L476:
	ldr	x20, [x19]
	add	x19, x19, 294912
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 3928]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 249]
	cmp	w0, 1
	beq	.L482
	ldr	x1, .LC153
	mov	w0, 1
	bl	dprint_vfmw
.L482:
	ldr	x3, .LC147
	mov	x2, 176
	mov	w1, 0
	add	x0, x20, 240
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L475:
	ldr	x20, [x19]
	ldr	w0, [x19, 8840]
	ldr	w1, [x20, 264]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 249]
	cmp	w0, 1
	beq	.L482
	ldr	x1, .LC149
	mov	w0, 1
	bl	dprint_vfmw
	b	.L482
	.p2align 3
.L474:
	ldr	x20, [x19]
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 264]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 249]
	cmp	w0, 1
	beq	.L482
	ldr	x1, .LC151
	mov	w0, 1
	bl	dprint_vfmw
	b	.L482
	.p2align 3
.L473:
	ldr	x20, [x19]
	ldrb	w1, [x20, 249]
	cmp	w1, 1
	bne	.L482
	add	x19, x19, 53248
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2304]
	bl	SM_ReleaseStreamSeg
	b	.L482
	.p2align 3
.L472:
	ldr	x20, [x19]
	ldrb	w1, [x20, 249]
	cmp	w1, 1
	bne	.L482
	add	x19, x19, 53248
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2328]
	bl	SM_ReleaseStreamSeg
	b	.L482
	.p2align 3
.L470:
	ldr	x20, [x19]
	ldrb	w1, [x20, 249]
	cmp	w1, 1
	bne	.L482
	add	x19, x19, 40960
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2272]
	bl	SM_ReleaseStreamSeg
	b	.L482
	.p2align 3
.L492:
	ldr	x2, .LC144
	mov	w3, 1855
	ldr	x1, .LC145
	mov	w0, 1
	add	x2, x2, 576
	bl	dprint_vfmw
	b	.L466
	.size	ReleasePacket, .-ReleasePacket
	.align	3
.LC144:
	.xword	.LANCHOR0
	.align	3
.LC145:
	.xword	.LC2
	.align	3
.LC146:
	.xword	.L471
	.align	3
.LC147:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC149:
	.xword	.LC148
	.align	3
.LC151:
	.xword	.LC150
	.align	3
.LC153:
	.xword	.LC152
	.align	3
.LC155:
	.xword	.LC154
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseCurPic_VPx
	.type	ReleaseCurPic_VPx, %function
ReleaseCurPic_VPx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L513
	sub	w0, w19, #10
	cmp	w0, 7
	bls	.L514
.L494:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L514:
	ldr	x1, .LC158
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx498
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx498:
	.section	.rodata
	.align	0
	.align	2
.L498:
	.byte	(.L497 - .Lrtx498) / 4
	.byte	(.L497 - .Lrtx498) / 4
	.byte	(.L497 - .Lrtx498) / 4
	.byte	(.L499 - .Lrtx498) / 4
	.byte	(.L494 - .Lrtx498) / 4
	.byte	(.L494 - .Lrtx498) / 4
	.byte	(.L494 - .Lrtx498) / 4
	.byte	(.L500 - .Lrtx498) / 4
	.text
	.p2align 3
.L500:
	ldr	x19, [x20]
	add	x20, x20, 294912
	ldr	w1, [x19, 264]
	ldr	w0, [x20, 3928]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 249]
	cmp	w0, 1
	beq	.L503
	ldr	x1, .LC159
	mov	w0, 1
	bl	dprint_vfmw
.L503:
	ldr	x3, .LC160
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 240
	ldr	x3, [x3, 96]
	blr	x3
.L515:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L499:
	ldr	x19, [x20]
	ldr	w0, [x20, 8840]
	ldr	w1, [x19, 264]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 249]
	cmp	w0, 1
	beq	.L503
	ldr	x1, .LC161
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x3, .LC160
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 240
	ldr	x3, [x3, 96]
	blr	x3
	b	.L515
	.p2align 3
.L497:
	ldr	x19, [x20]
	ldr	w0, [x20, 13368]
	ldr	w1, [x19, 264]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 249]
	cmp	w0, 1
	beq	.L503
	ldr	x1, .LC162
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x3, .LC160
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 240
	ldr	x3, [x3, 96]
	blr	x3
	b	.L515
	.p2align 3
.L513:
	ldr	x2, .LC156
	mov	w3, 1965
	ldr	x1, .LC157
	mov	w0, 1
	add	x2, x2, 592
	bl	dprint_vfmw
	b	.L494
	.size	ReleaseCurPic_VPx, .-ReleaseCurPic_VPx
	.align	3
.LC156:
	.xword	.LANCHOR0
	.align	3
.LC157:
	.xword	.LC2
	.align	3
.LC158:
	.xword	.L498
	.align	3
.LC159:
	.xword	.LC152
	.align	3
.LC160:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC161:
	.xword	.LC148
	.align	3
.LC162:
	.xword	.LC150
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseCurPic_Realx
	.type	ReleaseCurPic_Realx, %function
ReleaseCurPic_Realx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L523
	cmp	w20, 8
	beq	.L519
	cmp	w20, 9
	bne	.L516
	ldr	x20, [x19]
	ldrb	w1, [x20, 249]
	cmp	w1, 1
	beq	.L524
.L522:
	ldr	x3, .LC165
	mov	x2, 176
	mov	w1, 0
	add	x0, x20, 240
	ldr	x3, [x3, 96]
	blr	x3
.L516:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L519:
	ldr	x20, [x19]
	ldrb	w1, [x20, 249]
	cmp	w1, 1
	bne	.L522
	add	x19, x19, 53248
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2328]
	bl	SM_ReleaseStreamSeg
	b	.L522
	.p2align 3
.L523:
	ldr	x2, .LC163
	mov	w3, 2022
	ldr	x1, .LC164
	mov	w0, 1
	add	x2, x2, 616
	bl	dprint_vfmw
	b	.L516
	.p2align 3
.L524:
	add	x19, x19, 53248
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2304]
	bl	SM_ReleaseStreamSeg
	b	.L522
	.size	ReleaseCurPic_Realx, .-ReleaseCurPic_Realx
	.align	3
.LC163:
	.xword	.LANCHOR0
	.align	3
.LC164:
	.xword	.LC2
	.align	3
.LC165:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseCurPic_DIVX3
	.type	ReleaseCurPic_DIVX3, %function
ReleaseCurPic_DIVX3:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L529
	ldr	x20, [x19]
	ldrb	w1, [x20, 249]
	cmp	w1, 1
	beq	.L530
.L528:
	ldr	x3, .LC168
	mov	x2, 176
	mov	w1, 0
	add	x0, x20, 240
	ldr	x3, [x3, 96]
	blr	x3
.L525:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L530:
	add	x19, x19, 40960
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2272]
	bl	SM_ReleaseStreamSeg
	b	.L528
	.p2align 3
.L529:
	ldr	x2, .LC166
	mov	w3, 2064
	ldr	x1, .LC167
	mov	w0, 1
	add	x2, x2, 640
	bl	dprint_vfmw
	b	.L525
	.size	ReleaseCurPic_DIVX3, .-ReleaseCurPic_DIVX3
	.align	3
.LC166:
	.xword	.LANCHOR0
	.align	3
.LC167:
	.xword	.LC2
	.align	3
.LC168:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseCurPic
	.type	ReleaseCurPic, %function
ReleaseCurPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L549
	cmp	w20, 17
	bls	.L550
.L534:
	ldr	x1, .LC172
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
.L531:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L550:
	ldr	x0, .LC171
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx536
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx536:
	.section	.rodata
	.align	0
	.align	2
.L536:
	.byte	(.L535 - .Lrtx536) / 4
	.byte	(.L537 - .Lrtx536) / 4
	.byte	(.L538 - .Lrtx536) / 4
	.byte	(.L539 - .Lrtx536) / 4
	.byte	(.L534 - .Lrtx536) / 4
	.byte	(.L540 - .Lrtx536) / 4
	.byte	(.L541 - .Lrtx536) / 4
	.byte	(.L534 - .Lrtx536) / 4
	.byte	(.L542 - .Lrtx536) / 4
	.byte	(.L543 - .Lrtx536) / 4
	.byte	(.L544 - .Lrtx536) / 4
	.byte	(.L544 - .Lrtx536) / 4
	.byte	(.L544 - .Lrtx536) / 4
	.byte	(.L545 - .Lrtx536) / 4
	.byte	(.L534 - .Lrtx536) / 4
	.byte	(.L546 - .Lrtx536) / 4
	.byte	(.L547 - .Lrtx536) / 4
	.byte	(.L548 - .Lrtx536) / 4
	.text
	.p2align 3
.L548:
	mov	x1, x19
	mov	w0, 17
	bl	ReleaseCurPic_VPx
	b	.L531
	.p2align 3
.L547:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	b	.L531
	.p2align 3
.L546:
	mov	x0, x19
	bl	MVC_ClearCurrPic
	b	.L531
	.p2align 3
.L545:
	mov	x1, x19
	mov	w0, 13
	bl	ReleaseCurPic_VPx
	b	.L531
	.p2align 3
.L544:
	mov	x1, x19
	mov	w0, w20
	bl	ReleaseCurPic_VPx
	b	.L531
	.p2align 3
.L543:
	mov	x1, x19
	mov	w0, 9
	bl	ReleaseCurPic_Realx
	b	.L531
	.p2align 3
.L542:
	mov	x1, x19
	mov	w0, 8
	bl	ReleaseCurPic_Realx
	b	.L531
	.p2align 3
.L541:
	mov	x0, x19
	bl	AVS_ClearCurPic
	b	.L531
	.p2align 3
.L540:
	mov	x1, x19
	mov	w0, 5
	bl	ReleaseCurPic_DIVX3
	b	.L531
	.p2align 3
.L539:
	mov	x0, x19
	bl	MP2_ClearCurPic
	b	.L531
	.p2align 3
.L538:
	mov	x0, x19
	bl	MP4_ClearCurPic
	mov	x0, x19
	bl	MP4_Clean_HeadPacket
	b	.L531
	.p2align 3
.L537:
	add	x1, x19, 53248
	add	x0, x19, 12288
	add	x0, x0, 2520
	ldr	w1, [x1, 896]
	bl	VC1_ClearCurPic
	b	.L531
	.p2align 3
.L535:
	mov	x0, x19
	bl	H264_ClearCurrPic
	b	.L531
	.p2align 3
.L549:
	ldr	x2, .LC169
	mov	w3, 2080
	ldr	x1, .LC170
	mov	w0, 1
	add	x2, x2, 664
	bl	dprint_vfmw
	b	.L531
	.size	ReleaseCurPic, .-ReleaseCurPic
	.align	3
.LC169:
	.xword	.LANCHOR0
	.align	3
.LC170:
	.xword	.LC2
	.align	3
.LC171:
	.xword	.L536
	.align	3
.LC172:
	.xword	.LC154
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsNewpicSeg
	.type	IsNewpicSeg, %function
IsNewpicSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	x20, x1
	mov	x19, x3
	mov	w21, w2
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L600
	cmp	w21, 2
	mov	w0, 0
	ldr	x1, [x19]
	beq	.L601
.L554:
	ldrb	w2, [x1]
	ldrb	w3, [x1, 1]
	ldrb	w4, [x1, 2]
	cbnz	w2, .L557
	cbnz	w3, .L557
	cmp	w4, 1
	bne	.L557
	cmp	w21, 16
	bls	.L602
.L575:
	mov	w0, -1
.L553:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L602:
	ldr	x2, .LC177
	ldrb	w2, [x2,w21,uxtw]
	adr	x3, .Lrtx561
	add	x2, x3, w2, sxtb #2
	br	x2
.Lrtx561:
	.section	.rodata
	.align	0
	.align	2
.L561:
	.byte	(.L560 - .Lrtx561) / 4
	.byte	(.L562 - .Lrtx561) / 4
	.byte	(.L555 - .Lrtx561) / 4
	.byte	(.L563 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L564 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L575 - .Lrtx561) / 4
	.byte	(.L565 - .Lrtx561) / 4
	.byte	(.L566 - .Lrtx561) / 4
	.text
	.p2align 3
.L601:
	ldrb	w2, [x19, 80]
	and	w0, w2, 1
	tbz	x2, 0, .L554
.L555:
	ldrb	w2, [x1, 3]
	mov	w5, 179
	mov	w3, 47
	cmp	w2, 176
	add	w4, w2, 75
	ccmp	w2, w5, 4, ne
	cset	w5, eq
	cmp	w2, 254
	ccmp	w2, w3, 0, ne
	uxtb	w4, w4
	cset	w3, ls
	cmp	w4, 1
	orr	w3, w5, w3
	cset	w4, ls
	orr	w3, w4, w3
	cbnz	w3, .L603
.L569:
	cbz	w0, .L581
.L570:
	mov	w0, 1
	str	w0, [x20]
	mov	w0, 0
	ldrb	w2, [x1, 3]
.L571:
	cmp	w2, 182
	bne	.L553
.L597:
	str	wzr, [x20]
.L605:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L566:
	mov	x0, x20
	bl	HEVC_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L563:
	ldrb	w2, [x1, 3]
	mov	w3, 179
	add	w0, w2, 73
	cmp	w2, wzr
	ccmp	w2, w3, 4, ne
	uxtb	w0, w0
	ccmp	w0, 1, 0, ne
	bls	.L604
	ldr	x3, .LC178
	mov	w0, -1
	ldr	x4, [x3, w22, sxtw 3]
	ldr	x3, [x4, 712]
	cmn	x3, #1
	bne	.L568
	ldr	w3, [x20]
	cbnz	w3, .L568
	add	w3, w2, w0
	uxtb	w3, w3
	cmp	w3, 174
	bhi	.L568
	ldr	x2, [x19, 32]
	str	x2, [x4, 712]
	ldrb	w2, [x1, 3]
.L568:
	cbnz	w2, .L553
.L598:
	str	wzr, [x20]
	b	.L605
	.p2align 3
.L562:
	ldrb	w2, [x1, 3]
	mov	w0, -1
	sub	w3, w2, #12
	uxtb	w3, w3
	cmp	w3, 3
	ccmp	w2, 10, 4, hi
	cset	w3, eq
	cbnz	w3, .L606
.L573:
	cmp	w2, 13
	bne	.L553
	b	.L597
	.p2align 3
.L565:
	mov	x0, x20
	bl	MVC_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L564:
	ldrb	w2, [x1, 3]
	add	w0, w2, 74
	cmp	w2, 179
	cset	w3, eq
	uxtb	w0, w0
	cmp	w0, 1
	cset	w4, ls
	cmp	w2, 176
	cset	w0, eq
	orr	w0, w3, w0
	orr	w0, w4, w0
	cbz	w0, .L584
	ldr	w0, [x20]
	cbnz	w0, .L584
	mov	w0, 1
	str	w0, [x20]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	cmp	w2, 179
	cset	w3, eq
.L572:
	cmp	w2, 182
	cset	w1, eq
	orr	w1, w3, w1
	cbz	w1, .L553
	str	wzr, [x20]
	b	.L605
	.p2align 3
.L560:
	mov	x0, x20
	bl	H264_IsNewPicNal
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L603:
	ldr	w3, [x20]
	cbz	w3, .L570
	b	.L569
	.p2align 3
.L557:
	ldr	x1, .LC176
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L606:
	ldr	w3, [x20]
	cbnz	w3, .L573
	mov	w0, 1
	str	w0, [x20]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	b	.L573
	.p2align 3
.L604:
	ldr	w3, [x20]
	mov	w0, -1
	cbnz	w3, .L568
	mov	w0, 1
	str	w0, [x20]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	cbz	w2, .L598
	b	.L553
	.p2align 3
.L600:
	ldr	x2, .LC173
	mov	w3, 2356
	ldr	x1, .LC174
	mov	w0, 1
	add	x2, x2, 680
	bl	dprint_vfmw
	mov	w0, -1
	b	.L553
	.p2align 3
.L584:
	mov	w0, -1
	b	.L572
.L581:
	mov	w0, -1
	b	.L571
	.size	IsNewpicSeg, .-IsNewpicSeg
	.align	3
.LC173:
	.xword	.LANCHOR0
	.align	3
.LC174:
	.xword	.LC2
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC177:
	.xword	.L561
	.align	3
.LC178:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CloseUsdPool
	.type	CloseUsdPool, %function
CloseUsdPool:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	cmp	w20, 31
	bhi	.L613
	ldr	x19, .LC181
	add	x19, x19, 128
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L607
	ldr	x1, .LC182
	ldr	x1, [x1, 440]
	blr	x1
	str	xzr, [x19, w20, sxtw 3]
.L607:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L613:
	ldr	x2, .LC179
	mov	w3, 2414
	ldr	x1, .LC180
	mov	w0, 1
	add	x2, x2, 696
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CloseUsdPool, .-CloseUsdPool
	.align	3
.LC179:
	.xword	.LANCHOR0
	.align	3
.LC180:
	.xword	.LC2
	.align	3
.LC181:
	.xword	.LANCHOR1
	.align	3
.LC182:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CloseUsdPool_WithMem
	.type	CloseUsdPool_WithMem, %function
CloseUsdPool_WithMem:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L620
	ldr	x0, .LC186
	add	x0, x0, 128
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L614
	str	xzr, [x0, w19, sxtw 3]
.L614:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L620:
	ldr	x2, .LC184
	mov	w3, 2446
	ldr	x1, .LC185
	mov	w0, 1
	add	x2, x2, 712
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CloseUsdPool_WithMem, .-CloseUsdPool_WithMem
	.align	3
.LC184:
	.xword	.LANCHOR0
	.align	3
.LC185:
	.xword	.LC2
	.align	3
.LC186:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitUsdPool
	.type	InitUsdPool, %function
InitUsdPool:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L627
	ldr	x0, .LC192
	add	x0, x0, 128
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L625
	add	x1, x0, 204800
	str	wzr, [x0]
	add	x1, x1, 536
	add	x0, x0, 1048
	.p2align 2
.L624:
	stp	wzr, wzr, [x0, -4]
	add	x0, x0, 1064
	cmp	x0, x1
	bne	.L624
	mov	w0, 0
.L623:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L627:
	ldr	x2, .LC190
	mov	w3, 2464
	ldr	x1, .LC191
	mov	w0, 1
	add	x2, x2, 736
	bl	dprint_vfmw
	mov	w0, -1
	b	.L623
.L625:
	mov	w0, -1
	b	.L623
	.size	InitUsdPool, .-InitUsdPool
	.align	3
.LC190:
	.xword	.LANCHOR0
	.align	3
.LC191:
	.xword	.LC2
	.align	3
.LC192:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OpenUsdPool
	.type	OpenUsdPool, %function
OpenUsdPool:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L632
	ldr	x20, .LC196
	add	x20, x20, 128
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L633
.L631:
	mov	w0, w19
	bl	InitUsdPool
.L630:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L633:
	ldr	x1, .LC197
	mov	w0, 7688
	movk	w0, 0x3, lsl 16
	ldr	x1, [x1, 432]
	blr	x1
	str	x0, [x20, w19, sxtw 3]
	b	.L631
	.p2align 3
.L632:
	ldr	x2, .LC194
	mov	w3, 2399
	ldr	x1, .LC195
	mov	w0, 1
	add	x2, x2, 752
	bl	dprint_vfmw
	mov	w0, -1
	b	.L630
	.size	OpenUsdPool, .-OpenUsdPool
	.align	3
.LC194:
	.xword	.LANCHOR0
	.align	3
.LC195:
	.xword	.LC2
	.align	3
.LC196:
	.xword	.LANCHOR1
	.align	3
.LC197:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OpenUsdPool_WithMem
	.type	OpenUsdPool_WithMem, %function
OpenUsdPool_WithMem:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L639
	cbz	x20, .L640
	ldr	x0, .LC201
	add	x0, x0, 128
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L641
.L638:
	mov	w0, w19
	bl	InitUsdPool
.L636:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L641:
	str	x20, [x0, w19, sxtw 3]
	b	.L638
	.p2align 3
.L639:
	ldr	x2, .LC199
	mov	w3, 2431
	ldr	x1, .LC200
	mov	w0, 1
	add	x2, x2, 768
	bl	dprint_vfmw
	mov	w0, -1
	b	.L636
.L640:
	ldr	x2, .LC199
	mov	w3, 2432
	ldr	x1, .LC200
	mov	w0, 1
	add	x2, x2, 768
	bl	dprint_vfmw
	mov	w0, -1
	b	.L636
	.size	OpenUsdPool_WithMem, .-OpenUsdPool_WithMem
	.align	3
.LC199:
	.xword	.LANCHOR0
	.align	3
.LC200:
	.xword	.LC2
	.align	3
.LC201:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetUsd
	.type	GetUsd, %function
GetUsd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L649
	ldr	x0, .LC205
	add	x0, x0, 128
	ldr	x3, [x0, w19, sxtw 3]
	cbz	x3, .L647
	add	x0, x3, 1048
	mov	w1, 0
	b	.L646
	.p2align 3
.L645:
	add	w1, w1, 1
	add	x0, x0, 1064
	cmp	w1, 192
	beq	.L647
.L646:
	ldr	w2, [x0]
	cbnz	w2, .L645
	ldr	w2, [x0, -4]
	cbnz	w2, .L645
	sxtw	x0, w1
	lsl	x1, x0, 7
	add	x1, x1, x0, lsl 2
	add	x0, x1, x0
	add	x1, x3, x0, lsl 3
	add	x0, x1, 8
	strb	wzr, [x1, 1034]
	strb	wzr, [x1, 1035]
	strb	wzr, [x1, 1036]
	strh	wzr, [x1, 1038]
	str	wzr, [x1, 1044]
	str	wzr, [x1, 1052]
	str	wzr, [x1, 1056]
	str	wzr, [x1, 1060]
	str	xzr, [x1, 1064]
.L644:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L647:
	mov	x0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L649:
	ldr	x2, .LC203
	mov	w3, 2494
	ldr	x1, .LC204
	mov	w0, 1
	add	x2, x2, 792
	bl	dprint_vfmw
	mov	x0, 0
	b	.L644
	.size	GetUsd, .-GetUsd
	.align	3
.LC203:
	.xword	.LANCHOR0
	.align	3
.LC204:
	.xword	.LC2
	.align	3
.LC205:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FreeUsdByDec
	.type	FreeUsdByDec, %function
FreeUsdByDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L653
	str	wzr, [x19, 1040]
.L650:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L653:
	ldr	x2, .LC207
	mov	w3, 2525
	ldr	x1, .LC208
	mov	w0, 1
	add	x2, x2, 800
	bl	dprint_vfmw
	b	.L650
	.size	FreeUsdByDec, .-FreeUsdByDec
	.align	3
.LC207:
	.xword	.LANCHOR0
	.align	3
.LC208:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MarkUsdByDnr
	.type	MarkUsdByDnr, %function
MarkUsdByDnr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L657
	mov	w0, 1
	str	w0, [x19, 1036]
.L654:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L657:
	ldr	x2, .LC209
	mov	w3, 2536
	ldr	x1, .LC210
	mov	w0, 1
	add	x2, x2, 816
	bl	dprint_vfmw
	b	.L654
	.size	MarkUsdByDnr, .-MarkUsdByDnr
	.align	3
.LC209:
	.xword	.LANCHOR0
	.align	3
.LC210:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkUsdByDnr
	.type	UnMarkUsdByDnr, %function
UnMarkUsdByDnr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L661
	str	wzr, [x19, 1036]
.L658:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L661:
	ldr	x2, .LC211
	mov	w3, 2546
	ldr	x1, .LC212
	mov	w0, 1
	add	x2, x2, 832
	bl	dprint_vfmw
	b	.L658
	.size	UnMarkUsdByDnr, .-UnMarkUsdByDnr
	.align	3
.LC211:
	.xword	.LANCHOR0
	.align	3
.LC212:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsImageInVoQueue
	.type	IsImageInVoQueue, %function
IsImageInVoQueue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L675
	cbz	x20, .L676
	ldrh	w0, [x19, 4]
	ldrh	w4, [x19, 8]
	and	w0, w0, 63
	.p2align 2
.L674:
	cmp	w0, w4
	beq	.L668
	sxtw	x2, w0
	add	w0, w0, 1
	add	x2, x2, 2
	and	w0, w0, 63
	ldr	x2, [x19, x2, lsl 3]
	cbz	x2, .L674
	ldr	w3, [x2, 148]
	ldr	w2, [x20, 148]
	cmp	w3, w2
	bne	.L674
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L668:
	mov	w0, -1
.L664:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L676:
	ldr	x1, .LC215
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L664
.L675:
	ldr	x2, .LC213
	mov	w3, 2558
	ldr	x1, .LC214
	mov	w0, 1
	add	x2, x2, 848
	bl	dprint_vfmw
	mov	w0, -1
	b	.L664
	.size	IsImageInVoQueue, .-IsImageInVoQueue
	.align	3
.LC213:
	.xword	.LANCHOR0
	.align	3
.LC214:
	.xword	.LC2
	.align	3
.LC215:
	.xword	.LC20
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsVoQueueEmpty
	.type	IsVoQueueEmpty, %function
IsVoQueueEmpty:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L681
	ldrh	w2, [x19, 6]
	mov	w0, 0
	ldrh	w1, [x19, 8]
	cmp	w1, w2
	beq	.L682
.L679:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L682:
	ldrh	w0, [x19, 4]
	ldr	x19, [sp, 16]
	cmp	w0, w1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L681:
	ldr	x2, .LC216
	mov	w0, 0
	ldr	x1, .LC218
	add	x2, x2, 872
	bl	dprint_vfmw
	mov	w0, 0
	b	.L679
	.size	IsVoQueueEmpty, .-IsVoQueueEmpty
	.align	3
.LC216:
	.xword	.LANCHOR0
	.align	3
.LC218:
	.xword	.LC217
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetAspectRatio
	.type	SetAspectRatio, %function
SetAspectRatio:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L694
	cmp	w20, 5
	bls	.L695
	ldr	x1, .LC223
	mov	w0, 1
	mov	w2, w20
	stp	wzr, w0, [x19, 100]
	bl	dprint_vfmw
.L683:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L695:
	ldr	x0, .LC221
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx688
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx688:
	.section	.rodata
	.align	0
	.align	2
.L688:
	.byte	(.L687 - .Lrtx688) / 4
	.byte	(.L689 - .Lrtx688) / 4
	.byte	(.L690 - .Lrtx688) / 4
	.byte	(.L691 - .Lrtx688) / 4
	.byte	(.L692 - .Lrtx688) / 4
	.byte	(.L693 - .Lrtx688) / 4
	.text
	.p2align 3
.L692:
	mov	w1, 235
	mov	w0, 100
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L691:
	mov	w1, 221
	mov	w0, 100
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L690:
	mov	w1, 16
	mov	w0, 9
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L689:
	mov	w1, 4
	mov	w0, 3
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L687:
	mov	w0, 1
	stp	wzr, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L693:
	mov	w0, 2
	stp	wzr, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L694:
	ldr	x2, .LC219
	mov	w3, 2606
	ldr	x1, .LC220
	mov	w0, 1
	add	x2, x2, 888
	bl	dprint_vfmw
	b	.L683
	.size	SetAspectRatio, .-SetAspectRatio
	.align	3
.LC219:
	.xword	.LANCHOR0
	.align	3
.LC220:
	.xword	.LC2
	.align	3
.LC221:
	.xword	.L688
	.align	3
.LC223:
	.xword	.LC222
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetVoLastImageID
	.type	GetVoLastImageID, %function
GetVoLastImageID:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L700
	ldr	w0, [x19, 552]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	csinv	w0, w0, wzr, hi
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L700:
	ldr	x2, .LC224
	mov	w3, 2654
	ldr	x1, .LC225
	mov	w0, 1
	add	x2, x2, 904
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.size	GetVoLastImageID, .-GetVoLastImageID
	.align	3
.LC224:
	.xword	.LANCHOR0
	.align	3
.LC225:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsMain10Profile
	.type	IsMain10Profile, %function
IsMain10Profile:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L710
	ldr	w1, [x19, 308]
	cmp	w1, 1
	beq	.L705
	ldr	w2, [x19, 312]
	mov	w0, 0
	cmp	w2, 1
	beq	.L708
	cmp	w1, 2
	ldr	w1, [x19, 316]
	beq	.L707
	cmp	w1, 1
	cset	w0, eq
.L704:
	cmp	w1, 1
	cset	w1, eq
	orr	w0, w1, w0
.L708:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L705:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L707:
	mov	w0, 1
	b	.L704
	.p2align 3
.L710:
	ldr	x2, .LC226
	mov	w3, 2669
	ldr	x1, .LC227
	mov	w0, 1
	add	x2, x2, 928
	bl	dprint_vfmw
	mov	w0, 0
	b	.L708
	.size	IsMain10Profile, .-IsMain10Profile
	.align	3
.LC226:
	.xword	.LANCHOR0
	.align	3
.LC227:
	.xword	.LC2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsPtsRewind
	.type	IsPtsRewind, %function
IsPtsRewind:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	mov	x21, x2
	bl	_mcount
	cmp	w20, 31
	bhi	.L715
	ldr	x0, .LC230
	sub	x19, x19, x21
	ldr	x0, [x0, w20, sxtw 3]
	ldr	w0, [x0, 128]
	cbnz	w0, .L716
	cmp	x19, 1000
	ldr	x21, [sp, 32]
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L716:
	mov	x0, 16960
	ldr	x21, [sp, 32]
	movk	x0, 0xf, lsl 16
	cmp	x19, x0
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L715:
	ldr	x2, .LC228
	mov	w3, 2694
	ldr	x1, .LC229
	mov	w0, 1
	add	x2, x2, 944
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	IsPtsRewind, .-IsPtsRewind
	.align	3
.LC228:
	.xword	.LANCHOR0
	.align	3
.LC229:
	.xword	.LC2
	.align	3
.LC230:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MetadataMapToSec
	.type	MetadataMapToSec, %function
MetadataMapToSec:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MetadataMapToSec, .-MetadataMapToSec
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MetadataUnMapToSec
	.type	MetadataUnMapToSec, %function
MetadataUnMapToSec:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MetadataUnMapToSec, .-MetadataUnMapToSec
	.global	pstVdecUsdPool
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11557, %object
	.size	__func__.11557, 13
__func__.11557:
	.string	"PrintVoQueue"
	.zero	3
	.type	__func__.11563, %object
	.size	__func__.11563, 13
__func__.11563:
	.string	"ResetVoQueue"
	.zero	3
	.type	__func__.11569, %object
	.size	__func__.11569, 20
__func__.11569:
	.string	"ReturnImageToSyntax"
	.zero	4
	.type	__func__.11633, %object
	.size	__func__.11633, 19
__func__.11633:
	.string	"InsertImgToVoQueue"
	.zero	5
	.type	__FUNCTION__.11636, %object
	.size	__FUNCTION__.11636, 19
__FUNCTION__.11636:
	.string	"InsertImgToVoQueue"
	.zero	5
	.type	__func__.11644, %object
	.size	__func__.11644, 15
__func__.11644:
	.string	"GetQueueImgNum"
	.zero	1
	.type	__func__.11673, %object
	.size	__func__.11673, 20
__func__.11673:
	.string	"SYNTAX_ReceiveImage"
	.zero	4
	.type	__func__.11719, %object
	.size	__func__.11719, 20
__func__.11719:
	.string	"SYNTAX_ReleaseImage"
	.zero	4
	.type	__func__.11728, %object
	.size	__func__.11728, 19
__func__.11728:
	.string	"SYNTAX_ReturnImage"
	.zero	5
	.type	__func__.11753, %object
	.size	__func__.11753, 18
__func__.11753:
	.string	"DecodeStream_H264"
	.zero	6
	.type	__func__.11760, %object
	.size	__func__.11760, 18
__func__.11760:
	.string	"DecodeStream_HEVC"
	.zero	6
	.type	__func__.11765, %object
	.size	__func__.11765, 17
__func__.11765:
	.string	"DecodeStream_VP9"
	.zero	7
	.type	__func__.11772, %object
	.size	__func__.11772, 17
__func__.11772:
	.string	"DecodeStream_MVC"
	.zero	7
	.type	__func__.11785, %object
	.size	__func__.11785, 21
__func__.11785:
	.string	"DecodeStream_VC1_Smp"
	.zero	3
	.type	__func__.11817, %object
	.size	__func__.11817, 19
__func__.11817:
	.string	"DecodeStream_REAL8"
	.zero	5
	.type	__func__.11823, %object
	.size	__func__.11823, 19
__func__.11823:
	.string	"DecodeStream_REAL9"
	.zero	5
	.type	__func__.11829, %object
	.size	__func__.11829, 19
__func__.11829:
	.string	"DecodeStream_DIVX3"
	.zero	5
	.type	__func__.11835, %object
	.size	__func__.11835, 17
__func__.11835:
	.string	"DecodeStream_VP8"
	.zero	7
	.type	__func__.11841, %object
	.size	__func__.11841, 18
__func__.11841:
	.string	"DecodeStream_VP6x"
	.zero	6
	.type	__func__.11870, %object
	.size	__func__.11870, 7
__func__.11870:
	.string	"SegMan"
	.zero	1
	.type	__func__.11779, %object
	.size	__func__.11779, 21
__func__.11779:
	.string	"DecodeStream_VC1_Adv"
	.zero	3
	.type	__func__.11790, %object
	.size	__func__.11790, 17
__func__.11790:
	.string	"DecodeStream_VC1"
	.zero	7
	.type	__func__.11797, %object
	.size	__func__.11797, 19
__func__.11797:
	.string	"DecodeStream_MPEG2"
	.zero	5
	.type	__func__.11804, %object
	.size	__func__.11804, 19
__func__.11804:
	.string	"DecodeStream_MPEG4"
	.zero	5
	.type	__func__.11811, %object
	.size	__func__.11811, 17
__func__.11811:
	.string	"DecodeStream_AVS"
	.zero	7
	.type	__func__.11847, %object
	.size	__func__.11847, 13
__func__.11847:
	.string	"DecodeStream"
	.zero	3
	.type	__func__.11876, %object
	.size	__func__.11876, 14
__func__.11876:
	.string	"ReleasePacket"
	.zero	2
	.type	__func__.11892, %object
	.size	__func__.11892, 18
__func__.11892:
	.string	"ReleaseCurPic_VPx"
	.zero	6
	.type	__func__.11905, %object
	.size	__func__.11905, 20
__func__.11905:
	.string	"ReleaseCurPic_Realx"
	.zero	4
	.type	__func__.11915, %object
	.size	__func__.11915, 20
__func__.11915:
	.string	"ReleaseCurPic_DIVX3"
	.zero	4
	.type	__func__.11920, %object
	.size	__func__.11920, 14
__func__.11920:
	.string	"ReleaseCurPic"
	.zero	2
	.type	__func__.11992, %object
	.size	__func__.11992, 12
__func__.11992:
	.string	"IsNewpicSeg"
	.zero	4
	.type	__func__.12002, %object
	.size	__func__.12002, 13
__func__.12002:
	.string	"CloseUsdPool"
	.zero	3
	.type	__func__.12012, %object
	.size	__func__.12012, 21
__func__.12012:
	.string	"CloseUsdPool_WithMem"
	.zero	3
	.type	__func__.12018, %object
	.size	__func__.12018, 12
__func__.12018:
	.string	"InitUsdPool"
	.zero	4
	.type	__func__.11998, %object
	.size	__func__.11998, 12
__func__.11998:
	.string	"OpenUsdPool"
	.zero	4
	.type	__func__.12008, %object
	.size	__func__.12008, 20
__func__.12008:
	.string	"OpenUsdPool_WithMem"
	.zero	4
	.type	__func__.12028, %object
	.size	__func__.12028, 7
__func__.12028:
	.string	"GetUsd"
	.zero	1
	.type	__func__.12036, %object
	.size	__func__.12036, 13
__func__.12036:
	.string	"FreeUsdByDec"
	.zero	3
	.type	__func__.12041, %object
	.size	__func__.12041, 13
__func__.12041:
	.string	"MarkUsdByDnr"
	.zero	3
	.type	__func__.12046, %object
	.size	__func__.12046, 15
__func__.12046:
	.string	"UnMarkUsdByDnr"
	.zero	1
	.type	__func__.12052, %object
	.size	__func__.12052, 17
__func__.12052:
	.string	"IsImageInVoQueue"
	.zero	7
	.type	__func__.12058, %object
	.size	__func__.12058, 15
__func__.12058:
	.string	"IsVoQueueEmpty"
	.zero	1
	.type	__func__.12063, %object
	.size	__func__.12063, 15
__func__.12063:
	.string	"SetAspectRatio"
	.zero	1
	.type	__func__.12076, %object
	.size	__func__.12076, 17
__func__.12076:
	.string	"GetVoLastImageID"
	.zero	7
	.type	__func__.12081, %object
	.size	__func__.12081, 16
__func__.12081:
	.string	"IsMain10Profile"
	.type	__func__.12088, %object
	.size	__func__.12088, 12
__func__.12088:
	.string	"IsPtsRewind"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC2:
	ASCII(.string	"[%s %d]assert warning\n" )
	.zero	1
.LC4:
	ASCII(.string	"VoQueue state: head(%d) history(%d) tail(%d)" )
	.zero	3
.LC6:
	ASCII(.string	"\n" )
	.zero	6
.LC8:
	ASCII(.string	"%d " )
	.zero	4
.LC13:
	ASCII(.string	"ResetVoQueue but queue not empty: head(%d) history(%d) tail(%d)\n" )
	.zero	7
.LC20:
	ASCII(.string	"image point NULL\n" )
	.zero	6
.LC22:
	ASCII(.string	"call InsertVOQueue\n" )
	.zero	4
.LC25:
	ASCII(.string	"FATAL: p_image(id=%d) has already in the VoQueue!\n" )
	.zero	5
.LC27:
	ASCII(.string	"error=%d,W=%d,H=%d,not acceptable!\n" )
	.zero	4
.LC30:
	ASCII(.string	"out_pts: %lld -> %lld Usertag %lld\n" )
	.zero	4
.LC33:
	ASCII(.string	"Queue=(%02d,%02d,%02d) + F%d\n" )
	.zero	2
.LC43:
	ASCII(.string	"%s, pstVoQue is NULL!!!\n" )
	.zero	7
.LC46:
	ASCII(.string	"Queue=(%02d,%02d,%02d) - F%d\n" )
	.zero	2
.LC48:
	ASCII(.string	"SYNTAX_ReleaseImage p_image is null\n" )
	.zero	3
.LC53:
	ASCII(.string	"Image %d not found in vo queue.\n" )
	.zero	7
.LC55:
	ASCII(.string	"image[%d] null\n" )
.LC57:
	ASCII(.string	"Queue=(%02d,%02d,%02d) x F%d\n" )
	.zero	2
.LC80:
	ASCII(.string	"LENTH ERROR: VC1 S/MP BS is wrong!\n" )
	.zero	4
.LC83:
	ASCII(.string	"SYNTAX ERROR: VC1 S/MP BS is wrong!\n" )
	.zero	3
.LC107:
	ASCII(.string	"pSegMan error!\n" )
.LC111:
	ASCII(.string	"More than two packet!!!ERROR!!!\n" )
	.zero	7
.LC120:
	ASCII(.string	"pSegMan->CurrSeg.IsLastSeg=%d\n" )
	.zero	1
.LC122:
	ASCII(.string	"pSegMan->CurrSeg.PhyAddr=%#x\n" )
	.zero	2
.LC124:
	ASCII(.string	"pSegMan->CurrSeg.LenInByte=%#x\n" )
.LC126:
	ASCII(.string	"ERROR: Wrong PreParseInfo about Vc1 IsAdvProfile!\n" )
	.zero	5
.LC128:
	ASCII(.string	"ERROR: Wrong PreParseInfo about Vc1 CodecVersion!\n" )
	.zero	5
.LC142:
	ASCII(.string	"Func: %s, Line: %d\n" )
	.zero	4
.LC148:
	ASCII(.string	"ERROR: VFMW_VP8 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC150:
	ASCII(.string	"ERROR: VFMW_VP6 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC152:
	ASCII(.string	"ERROR: VFMW_VP9 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC154:
	ASCII(.string	"VidStd=%d Error!\n" )
	.zero	6
.LC175:
	ASCII(.string	"pu8[0] = %x,pu8[1] = %x, pu8[2] = %x\n" )
	.zero	2
.LC217:
	ASCII(.string	"%s pstVoQue NULL\n" )
	.zero	6
.LC222:
	ASCII(.string	"WARNNING: aspect ration (%d) is not expected!\n" )
	.bss
	.align	3
.LANCHOR1 = . + 0
	.type	last_rec_pos_time.11632, %object
	.size	last_rec_pos_time.11632, 128
last_rec_pos_time.11632:
	.zero	128
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 256
pstVdecUsdPool:
	.zero	256
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
