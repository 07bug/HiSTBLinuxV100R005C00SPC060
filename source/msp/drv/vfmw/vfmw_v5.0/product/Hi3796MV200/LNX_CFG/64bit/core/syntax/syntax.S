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
	bls	.L21
.L19:
	mov	x0, 0
	b	.L2
	.p2align 3
.L21:
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
	.byte	(.L18 - .Lrtx4) / 4
	.byte	(.L5 - .Lrtx4) / 4
	.byte	(.L6 - .Lrtx4) / 4
	.byte	(.L7 - .Lrtx4) / 4
	.byte	(.L19 - .Lrtx4) / 4
	.byte	(.L8 - .Lrtx4) / 4
	.byte	(.L9 - .Lrtx4) / 4
	.byte	(.L19 - .Lrtx4) / 4
	.byte	(.L10 - .Lrtx4) / 4
	.byte	(.L11 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L13 - .Lrtx4) / 4
	.byte	(.L19 - .Lrtx4) / 4
	.byte	(.L14 - .Lrtx4) / 4
	.byte	(.L15 - .Lrtx4) / 4
	.byte	(.L16 - .Lrtx4) / 4
	.byte	(.L17 - .Lrtx4) / 4
	.byte	(.L19 - .Lrtx4) / 4
	.byte	(.L18 - .Lrtx4) / 4
	.text
	.p2align 3
.L18:
	add	x0, x19, 16
.L2:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5:
	add	x19, x19, 53248
	add	x0, x19, 296
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
.L7:
	add	x19, x19, 86016
	add	x0, x19, 2784
	b	.L2
	.p2align 3
.L8:
	add	x19, x19, 40960
	add	x0, x19, 1672
	b	.L2
	.p2align 3
.L9:
	add	x19, x19, 12288
	add	x0, x19, 3984
	b	.L2
	.p2align 3
.L14:
	add	x0, x19, 920
	b	.L2
	.p2align 3
.L15:
	add	x19, x19, 4096
	add	x0, x19, 2856
	b	.L2
	.p2align 3
.L16:
	add	x19, x19, 274432
	add	x0, x19, 4048
	b	.L2
	.p2align 3
.L17:
	add	x19, x19, 16384
	add	x0, x19, 2296
	b	.L2
	.p2align 3
.L12:
	add	x19, x19, 12288
	add	x0, x19, 480
	b	.L2
	.p2align 3
.L13:
	add	x19, x19, 8192
	add	x0, x19, 48
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
	cbz	x20, .L29
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
	beq	.L27
	ldr	x21, .LC9
	b	.L28
	.p2align 3
.L26:
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
	beq	.L27
.L28:
	and	w0, w0, 7
	cbnz	w0, .L26
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	b	.L26
	.p2align 3
.L27:
	mov	x1, x22
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L29:
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
	cbz	x19, .L36
	ldr	x20, .LC12
	mov	w0, 2
	ldr	x1, [x20, 24]
	blr	x1
	ldrh	w2, [x19, 6]
	ldrh	w3, [x19, 4]
	ldrh	w4, [x19, 8]
	cmp	w2, w3
	beq	.L37
.L34:
	ldr	x1, .LC14
	mov	w0, 1
	bl	dprint_vfmw
.L35:
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
.L37:
	cmp	w2, w4
	bne	.L34
	b	.L35
	.p2align 3
.L36:
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
	beq	.L57
	cmp	w21, 20
	bls	.L58
.L38:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L58:
	ldr	x0, .LC17
	ldrb	w0, [x0,w21,uxtw]
	adr	x1, .Lrtx42
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx42:
	.section	.rodata
	.align	0
	.align	2
.L42:
	.byte	(.L41 - .Lrtx42) / 4
	.byte	(.L43 - .Lrtx42) / 4
	.byte	(.L44 - .Lrtx42) / 4
	.byte	(.L45 - .Lrtx42) / 4
	.byte	(.L38 - .Lrtx42) / 4
	.byte	(.L46 - .Lrtx42) / 4
	.byte	(.L47 - .Lrtx42) / 4
	.byte	(.L38 - .Lrtx42) / 4
	.byte	(.L48 - .Lrtx42) / 4
	.byte	(.L49 - .Lrtx42) / 4
	.byte	(.L50 - .Lrtx42) / 4
	.byte	(.L50 - .Lrtx42) / 4
	.byte	(.L50 - .Lrtx42) / 4
	.byte	(.L51 - .Lrtx42) / 4
	.byte	(.L38 - .Lrtx42) / 4
	.byte	(.L52 - .Lrtx42) / 4
	.byte	(.L53 - .Lrtx42) / 4
	.byte	(.L54 - .Lrtx42) / 4
	.byte	(.L55 - .Lrtx42) / 4
	.byte	(.L38 - .Lrtx42) / 4
	.byte	(.L56 - .Lrtx42) / 4
	.text
	.p2align 3
.L57:
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
.L56:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	USERDEC_RecycleImage
	b	.L38
	.p2align 3
.L41:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	H264DEC_RecycleImage
	b	.L38
	.p2align 3
.L43:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	VC1DEC_RecycleImage
	b	.L38
	.p2align 3
.L44:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	MPEG4DEC_RecycleImage
	b	.L38
	.p2align 3
.L45:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	MPEG2DEC_RecycleImage
	b	.L38
	.p2align 3
.L46:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	DIVX3DEC_RecycleImage
	b	.L38
	.p2align 3
.L47:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	AVSDEC_RecycleImage
	b	.L38
	.p2align 3
.L48:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	REAL8DEC_RecycleImage
	b	.L38
	.p2align 3
.L49:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	REAL9DEC_RecycleImage
	b	.L38
	.p2align 3
.L50:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	VP6DEC_RecycleImage
	b	.L38
	.p2align 3
.L51:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	VP8DEC_RecycleImage
	b	.L38
	.p2align 3
.L52:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	MVC_DEC_RecycleImage
	b	.L38
	.p2align 3
.L53:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	HEVC_DECRecycleImage
	b	.L38
	.p2align 3
.L54:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	VP9DEC_RecycleImage
	b	.L38
	.p2align 3
.L55:
	ldr	w1, [x20, 148]
	mov	x0, x19
	bl	AVS2DEC_RecycleImage
	b	.L38
	.size	ReturnImageToSyntax, .-ReturnImageToSyntax
	.align	3
.LC15:
	.xword	.LANCHOR0
	.align	3
.LC16:
	.xword	.LC2
	.align	3
.LC17:
	.xword	.L42
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
	bhi	.L128
	cmp	x22, xzr
	ccmp	x27, xzr, 4, ne
	beq	.L129
	cbz	x26, .L130
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
	beq	.L68
	ldr	x25, .LC26
	mov	w23, 1000
	b	.L125
	.p2align 3
.L67:
	add	w19, w19, 1
	and	w19, w19, 63
	cmp	w19, w3
	beq	.L68
.L125:
	sxtw	x0, w19
	ldr	w1, [x26, 148]
	add	x0, x0, 2
	ldr	x0, [x27, x0, lsl 3]
	ldr	w2, [x0, 148]
	cmp	w2, w1
	bne	.L67
	mov	x1, x25
	mov	w0, 0
	add	w19, w19, 1
	bl	dprint_vfmw
	str	w23, [x26, 152]
	and	w19, w19, 63
	ldrh	w3, [x27, 8]
	cmp	w19, w3
	bne	.L125
	.p2align 2
.L68:
	ldr	w2, [x26, 152]
	cmp	w2, 100
	bhi	.L131
	ldp	w3, w4, [x26, 68]
	cmp	w3, 31
	bhi	.L132
.L70:
	ldr	x1, .LC28
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x26, 152]
	cmp	w0, 1000
	beq	.L73
	mov	x2, x26
	mov	x1, x22
	mov	w0, w24
	bl	ReturnImageToSyntax
.L73:
	ldr	x1, [x20, 32]
	mov	w0, 2
	blr	x1
	mov	w0, 1
.L61:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L132:
	cmp	w4, 31
	bls	.L70
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
	beq	.L92
	add	x19, x27, 528
	ldr	x0, [x19, 56]
	sub	w24, w24, #8
	sub	x1, x3, x0
	cmp	x1, 5
	ccmn	x0, #1, 4, ls
	beq	.L133
	cmp	w24, 1
	bls	.L76
	mov	x2, x3
	mov	x3, -1
.L74:
	ldr	x1, .LC31
	mov	w0, 29
	ldr	x4, [x26, 592]
	str	x3, [x26, 584]
	bl	dprint_vfmw
	ldr	w0, [x26, 76]
	cbz	w0, .L77
	ldr	w0, [x26, 80]
	cbz	w0, .L77
	ldr	w1, [x26, 68]
.L78:
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
	beq	.L79
	str	w1, [x19, 48]
.L79:
	ldr	w1, [x19, 44]
	ldr	x24, .LC32
	add	w2, w1, 1
	str	w2, [x19, 44]
	str	w1, [x26, 160]
	ldr	w1, [x27, 528]
	cmp	w4, w1
	beq	.L80
	ldr	x6, [x24]
	cbz	x6, .L81
	strb	w1, [x29, 120]
	mov	w3, 2
	strb	w0, [x29, 121]
	add	x2, x29, 120
	mov	w1, 7
	mov	w0, w21
	stp	w5, w4, [x29, 104]
	blr	x6
	ldp	w5, w4, [x29, 104]
.L81:
	str	w4, [x27, 528]
.L80:
	ldr	w0, [x19, 4]
	cmp	w28, w0
	beq	.L82
	ldr	x4, [x24]
	cbz	x4, .L83
	add	x2, x29, 128
	mov	w3, 1
	mov	w1, 4
	mov	w0, w21
	strb	w5, [x2, -8]!
	blr	x4
.L83:
	str	w28, [x19, 4]
.L82:
	ldr	w0, [x19, 16]
	cmp	w22, w0
	beq	.L134
.L84:
	ldr	x4, [x24]
	stp	w22, w23, [x19, 16]
	cbz	x4, .L85
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
.L85:
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
	add	x3, x3, 507904
	ldr	w4, [x3, 1728]
	add	w4, w4, 1
	str	w4, [x3, 1728]
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
	cbz	x4, .L87
	mov	w3, 640
	mov	x2, x26
	mov	w1, 5
	mov	w0, w21
	blr	x4
.L87:
	mov	w0, 8
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L135
.L89:
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
	bls	.L61
	ldr	w0, [x20, 4]
	cbz	w0, .L91
	mov	w3, 10000
	mul	w0, w0, w3
	udiv	w1, w0, w1
	str	w1, [x20, 8]
.L91:
	lsl	x1, x22, 2
	mov	w0, 1
	sub	x1, x1, x22
	lsl	x1, x1, 3
	add	x3, x23, x1
	str	w2, [x23, x1]
	str	wzr, [x3, 4]
	b	.L61
	.p2align 3
.L131:
	ldp	w3, w4, [x26, 68]
	b	.L70
.L133:
	cmp	w24, 1
	mov	x2, x3
	bhi	.L74
	ldrb	w0, [x26, 64]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L74
.L76:
	mov	x2, -1
	str	x2, [x26, 576]
	mov	x3, x2
	b	.L74
.L77:
	ldp	w1, w0, [x26, 68]
	stp	w1, w0, [x26, 76]
	lsr	w2, w1, 1
	lsr	w0, w0, 1
	str	w2, [x26, 84]
	str	w0, [x26, 88]
	b	.L78
.L135:
	ldr	x0, [x20]
	blr	x0
	mov	w4, w0
	ldr	x3, .LC37
	ldr	x1, .LC38
	ldr	w0, [x3, w21, sxtw 2]
	ldr	w1, [x1]
	sub	w0, w4, w0
	cmp	w0, w1
	bls	.L89
	ldr	x0, .LC18
	lsl	w2, w21, 24
	add	w2, w2, 524288
	mov	w1, 515
	add	x0, x0, 80
	str	w4, [x3, w21, sxtw 2]
	bl	DBG_AddTrace
	b	.L89
.L134:
	ldr	w0, [x19, 20]
	cmp	w23, w0
	bne	.L84
	b	.L85
.L92:
	mov	x2, x3
	add	x19, x27, 528
	b	.L74
.L128:
	ldr	x2, .LC18
	mov	w3, 396
	ldr	x1, .LC19
	mov	w0, 1
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -2
	b	.L61
.L129:
	ldr	x2, .LC18
	mov	w3, 397
	ldr	x1, .LC19
	mov	w0, 1
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -2
	b	.L61
.L130:
	ldr	x1, .LC21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L61
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
	beq	.L144
	ldrh	w0, [x19, 6]
	ldrh	w3, [x19, 4]
	cmp	w0, w3
	bcs	.L145
	add	w1, w0, 64
	sub	w3, w1, w3
.L140:
	ldrh	w4, [x19, 8]
	cmp	w0, w4
	bls	.L143
	add	w4, w4, 64
.L143:
	str	w3, [x21]
	sub	w0, w4, w0
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L145:
	sub	w3, w0, w3
	b	.L140
	.p2align 3
.L144:
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
	beq	.L152
	mov	x0, x19
	bl	SYNTAX_GetVoQue
	mov	x19, x0
	cbz	x0, .L153
	ldr	x22, .LC45
	mov	w0, 2
	mov	w21, -3
	ldr	x1, [x22, 24]
	blr	x1
	ldrh	w1, [x19, 6]
	ldrh	w0, [x19, 8]
	cmp	w0, w1
	beq	.L150
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
.L150:
	ldr	x1, [x22, 32]
	mov	w0, 2
	blr	x1
	mov	w0, w21
.L148:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L152:
	ldr	x2, .LC41
	mov	w3, 671
	ldr	x1, .LC42
	mov	w0, 1
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -2
	b	.L148
.L153:
	ldr	x2, .LC41
	mov	w0, 1
	ldr	x1, .LC44
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -2
	b	.L148
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
	beq	.L205
	mov	x0, x21
	bl	SYNTAX_GetVoQue
	mov	x25, x0
	cbz	x0, .L206
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
	beq	.L189
	ldr	x23, .LC56
	b	.L203
	.p2align 3
.L162:
	add	w20, w20, 1
	and	w20, w20, 63
	cmp	w20, w1
	beq	.L189
.L203:
	sxtw	x19, w20
	add	x0, x19, 2
	ldr	x0, [x25, x0, lsl 3]
	cbz	x0, .L160
	ldr	w0, [x0, 148]
	cmp	w26, w0
	bne	.L162
	mov	w5, 1
.L161:
	ldrh	w4, [x25, 4]
	b	.L164
	.p2align 3
.L193:
	mov	w20, w1
.L164:
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
	bne	.L193
	ldr	w0, [x24, 148]
	cmp	w5, 1
	ldr	w1, [x25, 600]
	sub	w0, w0, w1
	str	w0, [x24, 148]
	ldrh	w2, [x25, 4]
	add	w2, w2, 1
	and	w2, w2, 63
	strh	w2, [x25, 4]
	beq	.L202
	ldrh	w1, [x25, 6]
	add	w20, w20, 1
	and	w20, w20, 63
	cmp	w20, w1
	bne	.L203
.L189:
	ldr	x1, .LC54
	mov	w2, w26
	mov	w0, 1
	mov	w19, -2
	bl	dprint_vfmw
.L159:
	ldr	x1, [x22, 32]
	mov	w0, 2
	blr	x1
	mov	w0, w19
.L156:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L160:
	mov	w2, w20
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	mov	w5, 2
	b	.L161
.L202:
	ldr	x1, .LC58
	mov	w0, 12
	ldrh	w4, [x25, 8]
	ldrh	w3, [x25, 6]
	ldr	w5, [x24, 148]
	bl	dprint_vfmw
	ldr	w1, [x21]
	cmp	w1, 20
	bls	.L207
.L195:
	mov	w0, -2
.L165:
	cmp	w1, 17
	bls	.L208
.L182:
	cmn	w0, #2
	beq	.L199
	mov	w19, -20
	cmp	w0, 1
	csinc	w19, w19, wzr, ne
	b	.L159
.L207:
	ldr	x0, .LC59
	ldrb	w0, [x0,w1,uxtw]
	adr	x2, .Lrtx167
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx167:
	.section	.rodata
	.align	0
	.align	2
.L167:
	.byte	(.L166 - .Lrtx167) / 4
	.byte	(.L168 - .Lrtx167) / 4
	.byte	(.L169 - .Lrtx167) / 4
	.byte	(.L170 - .Lrtx167) / 4
	.byte	(.L195 - .Lrtx167) / 4
	.byte	(.L171 - .Lrtx167) / 4
	.byte	(.L172 - .Lrtx167) / 4
	.byte	(.L195 - .Lrtx167) / 4
	.byte	(.L173 - .Lrtx167) / 4
	.byte	(.L174 - .Lrtx167) / 4
	.byte	(.L175 - .Lrtx167) / 4
	.byte	(.L175 - .Lrtx167) / 4
	.byte	(.L175 - .Lrtx167) / 4
	.byte	(.L176 - .Lrtx167) / 4
	.byte	(.L195 - .Lrtx167) / 4
	.byte	(.L177 - .Lrtx167) / 4
	.byte	(.L178 - .Lrtx167) / 4
	.byte	(.L179 - .Lrtx167) / 4
	.byte	(.L180 - .Lrtx167) / 4
	.byte	(.L195 - .Lrtx167) / 4
	.byte	(.L181 - .Lrtx167) / 4
	.text
.L181:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	USERDEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L180:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	AVS2DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L179:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	VP9DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L178:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	HEVC_DECRecycleImage
	ldr	w1, [x21]
	b	.L165
.L177:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	MVC_DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L176:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	VP8DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L175:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	VP6DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L174:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	REAL9DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L173:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	REAL8DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L172:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	AVSDEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L171:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	DIVX3DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L170:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	MPEG2DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L169:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	MPEG4DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L168:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	VC1DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L166:
	ldr	w1, [x24, 148]
	add	x0, x21, 8
	bl	H264DEC_RecycleImage
	ldr	w1, [x21]
	b	.L165
.L208:
	ldr	x2, .LC60
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx184
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx184:
	.section	.rodata
	.align	0
	.align	2
.L184:
	.byte	(.L183 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L182 - .Lrtx184) / 4
	.byte	(.L187 - .Lrtx184) / 4
	.byte	(.L187 - .Lrtx184) / 4
	.byte	(.L187 - .Lrtx184) / 4
	.text
.L187:
	mov	w19, -20
	cmp	w0, wzr
	csinc	w19, w19, wzr, ne
	b	.L159
.L183:
	mov	w19, -20
	cmp	w0, wzr
	csinc	w19, w19, wzr, ne
	b	.L159
.L205:
	ldr	x1, .LC49
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L156
.L206:
	ldr	x2, .LC50
	mov	w0, 1
	ldr	x1, .LC51
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, -2
	b	.L156
.L199:
	mov	w19, w0
	b	.L159
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
	.xword	.L167
	.align	3
.LC60:
	.xword	.L184
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
	cbz	x19, .L230
	ldr	w0, [x19]
	cmp	w0, 20
	bls	.L231
.L229:
	mov	w0, -2
	b	.L211
	.p2align 3
.L231:
	ldr	x1, .LC63
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx213
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx213:
	.section	.rodata
	.align	0
	.align	2
.L213:
	.byte	(.L227 - .Lrtx213) / 4
	.byte	(.L214 - .Lrtx213) / 4
	.byte	(.L215 - .Lrtx213) / 4
	.byte	(.L216 - .Lrtx213) / 4
	.byte	(.L229 - .Lrtx213) / 4
	.byte	(.L217 - .Lrtx213) / 4
	.byte	(.L218 - .Lrtx213) / 4
	.byte	(.L229 - .Lrtx213) / 4
	.byte	(.L219 - .Lrtx213) / 4
	.byte	(.L220 - .Lrtx213) / 4
	.byte	(.L221 - .Lrtx213) / 4
	.byte	(.L221 - .Lrtx213) / 4
	.byte	(.L221 - .Lrtx213) / 4
	.byte	(.L222 - .Lrtx213) / 4
	.byte	(.L229 - .Lrtx213) / 4
	.byte	(.L223 - .Lrtx213) / 4
	.byte	(.L224 - .Lrtx213) / 4
	.byte	(.L225 - .Lrtx213) / 4
	.byte	(.L226 - .Lrtx213) / 4
	.byte	(.L229 - .Lrtx213) / 4
	.byte	(.L227 - .Lrtx213) / 4
	.text
	.p2align 3
.L227:
	add	x19, x19, 16
	.p2align 2
.L228:
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
.L211:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L225:
	add	x19, x19, 274432
	add	x19, x19, 4048
	b	.L228
	.p2align 3
.L224:
	add	x19, x19, 4096
	add	x19, x19, 2856
	b	.L228
	.p2align 3
.L223:
	add	x19, x19, 920
	b	.L228
	.p2align 3
.L222:
	add	x19, x19, 8192
	add	x19, x19, 48
	b	.L228
	.p2align 3
.L221:
	add	x19, x19, 12288
	add	x19, x19, 480
	b	.L228
	.p2align 3
.L220:
	add	x19, x19, 53248
	add	x19, x19, 1704
	b	.L228
	.p2align 3
.L226:
	add	x19, x19, 16384
	add	x19, x19, 2296
	b	.L228
	.p2align 3
.L215:
	add	x19, x19, 20480
	add	x19, x19, 2248
	b	.L228
	.p2align 3
.L214:
	add	x19, x19, 53248
	add	x19, x19, 296
	b	.L228
	.p2align 3
.L219:
	add	x19, x19, 53248
	add	x19, x19, 1728
	b	.L228
	.p2align 3
.L218:
	add	x19, x19, 12288
	add	x19, x19, 3984
	b	.L228
	.p2align 3
.L217:
	add	x19, x19, 40960
	add	x19, x19, 1672
	b	.L228
	.p2align 3
.L216:
	add	x19, x19, 86016
	add	x19, x19, 2784
	b	.L228
.L230:
	ldr	x2, .LC61
	mov	w3, 948
	ldr	x1, .LC62
	mov	w0, 1
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w0, -2
	b	.L211
	.size	SYNTAX_ReturnImage, .-SYNTAX_ReturnImage
	.align	3
.LC61:
	.xword	.LANCHOR0
	.align	3
.LC62:
	.xword	.LC2
	.align	3
.LC63:
	.xword	.L213
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
	beq	.L238
	ldr	x2, [x19, 8]
	add	x1, x29, 40
	ldr	x3, [x19, 40]
	mov	x0, x20
	ldrb	w5, [x19, 18]
	ldp	w7, w6, [x19, 24]
	ldr	w4, [x19, 32]
	str	x2, [x29, 48]
	str	x3, [x29, 72]
	ldrsb	w2, [x19, 17]
	ldrb	w3, [x19, 21]
	strb	w5, [x29, 40]
	stp	w7, w6, [x29, 56]
	str	w4, [x29, 64]
	strb	w3, [x29, 41]
	str	w2, [x29, 68]
	bl	H264DEC_DecodePacket
	cmn	w0, #2
	add	x0, x20, 65536
	beq	.L239
	strb	wzr, [x19, 1]
	ldr	x1, .LC67
	ldrsw	x2, [x0, 1980]
	ldr	x1, [x1, x2, lsl 3]
	strb	wzr, [x1, 1624]
.L236:
	ldr	x1, [x20, 616]
	cbz	x1, .L240
.L232:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L238:
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
.L239:
	mov	w1, 1
	strb	w1, [x19, 1]
	ldr	x2, .LC67
	ldrsw	x3, [x0, 1980]
	ldr	x2, [x2, x3, lsl 3]
	strb	w1, [x2, 1624]
	b	.L236
	.p2align 3
.L240:
	add	x20, x20, 12288
	ldrb	w1, [x20, 2640]
	cmp	w1, 1
	bne	.L232
	ldr	w0, [x0, 1980]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 2640]
	b	.L232
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
	beq	.L251
	ldp	w6, w5, [x19, 24]
	ldrb	w4, [x19, 18]
	add	x1, x29, 32
	ldrsb	w2, [x19, 17]
	mov	x0, x20
	ldr	w3, [x19, 32]
	ldr	x7, [x19, 8]
	strb	w4, [x29, 32]
	str	x7, [x29, 40]
	stp	w6, w2, [x29, 48]
	stp	w5, w3, [x29, 56]
	bl	HEVCDEC_DecodePacket
	cmn	w0, #2
	beq	.L244
	ldrb	w0, [x20, 9]
	cbnz	w0, .L244
	strb	wzr, [x19, 1]
	ldr	x0, .LC70
	ldrsw	x1, [x20, 276]
	ldr	x0, [x0, x1, lsl 3]
	strb	wzr, [x0, 1624]
.L246:
	ldr	x0, [x20, 3056]
	cbz	x0, .L252
.L241:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L244:
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x1, .LC70
	ldrsw	x2, [x20, 276]
	ldr	x1, [x1, x2, lsl 3]
	strb	w0, [x1, 1624]
	b	.L246
	.p2align 3
.L251:
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
.L252:
	ldrb	w0, [x20, 11]
	cmp	w0, 1
	bne	.L241
	ldr	w0, [x20, 276]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 11]
	b	.L241
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
	beq	.L269
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L270
	ldr	x23, .LC73
	add	x22, x19, 96
	mov	x2, 88
	add	x1, x19, 8
	mov	x0, x22
	add	x21, x20, 311296
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
	ldr	w0, [x21, 3172]
	cbz	w0, .L257
	ldr	w0, [x21, 3208]
	ldr	w1, [x21, 3212]
	cmp	w1, w0
	beq	.L257
.L258:
	mov	w0, 1
	strb	w0, [x19, 1]
.L253:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L257:
	ldr	w0, [x21, 3168]
	cbnz	w0, .L258
	strb	wzr, [x19, 1]
	ldr	x0, [x20, 8]
	cbnz	x0, .L253
	add	x20, x20, 262144
	ldrb	w0, [x20, 1044]
	cbnz	w0, .L253
	ldr	x3, [x23, 96]
	mov	x2, 176
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	w1, [x19, 32]
	ldr	w0, [x21, 3272]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC74
	ldr	x4, [x0]
	cbz	x4, .L253
	ldr	w0, [x21, 3272]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L253
	.p2align 3
.L269:
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
.L270:
	add	x20, x20, 311296
	ldr	w0, [x20, 3272]
	bl	VCTRL_OutputLastFrame
	ldr	w1, [x19, 32]
	ldr	w0, [x20, 3272]
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
	beq	.L277
	ldrb	w3, [x19, 18]
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
	beq	.L278
	strb	wzr, [x19, 1]
.L275:
	ldr	x0, [x20, 232]
	cbz	x0, .L279
.L271:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L277:
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
.L278:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L275
	.p2align 3
.L279:
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	bne	.L271
	ldr	w0, [x20, 120]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x20, 1]
	b	.L271
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
	beq	.L294
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L295
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
	bhi	.L284
	ldr	x1, .LC81
.L293:
	mov	w0, 0
	add	x20, x20, 53248
	bl	dprint_vfmw
	ldr	w1, [x19, 120]
	ldr	w0, [x20, 896]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC82
	ldr	x4, [x0]
	cbz	x4, .L280
	ldr	w0, [x20, 896]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L280:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L284:
	add	x2, x20, 16384
	ldr	x0, [x19, 96]
	add	x2, x2, 1528
	mov	w1, 16
	bl	Vc1SMPSeqHdr
	cbz	w0, .L296
	ldr	x1, .LC84
	b	.L293
	.p2align 3
.L294:
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
.L296:
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
.L295:
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
	beq	.L308
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L309
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
	beq	.L310
	strb	wzr, [x19, 1]
.L302:
	ldr	x0, [x20, 8]
	cbz	x0, .L311
.L297:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L308:
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
.L310:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L302
	.p2align 3
.L309:
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
.L311:
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
	cbz	x4, .L297
	ldr	w0, [x20, 2328]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L297
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
	beq	.L323
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L324
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
	beq	.L325
	strb	wzr, [x19, 1]
.L317:
	ldr	x0, [x20, 8]
	cbz	x0, .L326
.L312:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L323:
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
.L325:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L317
	.p2align 3
.L324:
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
.L326:
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
	cbz	x4, .L312
	ldr	w0, [x20, 2304]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L312
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
	beq	.L338
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L339
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
	beq	.L340
	strb	wzr, [x19, 1]
.L332:
	ldr	x0, [x20, 8]
	cbz	x0, .L341
.L327:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L338:
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
.L340:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L332
	.p2align 3
.L339:
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
.L341:
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
	cbz	x4, .L327
	ldr	w0, [x20, 2272]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L327
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
	beq	.L353
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L354
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
	beq	.L355
	strb	wzr, [x19, 1]
.L347:
	ldr	x0, [x20, 8]
	cbz	x0, .L356
.L342:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L353:
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
.L355:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L347
	.p2align 3
.L354:
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
.L356:
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
	cbz	x4, .L342
	ldr	w0, [x20, 8840]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L342
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
	beq	.L368
	ldrb	w0, [x19, 19]
	cmp	w0, 1
	beq	.L369
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
	beq	.L370
	strb	wzr, [x19, 1]
.L362:
	ldr	x0, [x20, 8]
	cbz	x0, .L371
.L357:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L368:
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
.L370:
	mov	w0, 1
	strb	w0, [x19, 1]
	b	.L362
	.p2align 3
.L369:
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
.L371:
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
	cbz	x4, .L357
	ldr	w0, [x20, 13368]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L357
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
	bhi	.L394
	cbz	x19, .L375
	ldr	x0, [x19, 8]
	cbz	x0, .L375
	ldr	x1, .LC109
	ldr	x1, [x1, w20, sxtw 3]
	ldr	w2, [x1, 1552]
	cmp	w2, 1
	beq	.L395
.L377:
	ldrb	w1, [x19, 18]
	strb	wzr, [x19, 448]
	cmp	w1, 1
	beq	.L396
	cbnz	w1, .L393
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
	bls	.L393
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
	cbz	x4, .L381
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	mov	w0, w20
	blr	x4
.L381:
	strb	wzr, [x19, 2]
.L393:
	mov	w0, -1
.L392:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L395:
	ldr	w1, [x1, 1600]
	cmp	w1, 1
	bne	.L377
	ldrb	w1, [x19, 448]
	cmp	w1, 1
	bne	.L377
	mov	x2, 176
	add	x1, x19, 272
	add	x0, x19, 96
	bl	memcpy
	strb	wzr, [x19, 448]
	mov	w0, 0
	b	.L392
	.p2align 3
.L396:
	ldrb	w21, [x19, 2]
	cbz	w21, .L397
	cmp	w21, 1
	bne	.L393
	ldr	w2, [x19, 116]
	cmp	w2, 1023
	bhi	.L383
	ldr	x22, .LC110
	uxtw	x2, w2
	ldr	x1, [x19, 96]
	sub	x0, x0, x2
	ldr	x3, [x22, 104]
	blr	x3
	strb	w21, [x19, 106]
	ldp	w0, w1, [x19, 116]
	ldp	w2, w4, [x19, 24]
	ldr	x3, [x19, 8]
	sub	w2, w2, w0
	sub	x3, x3, x0, uxtw
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
.L384:
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
.L383:
	ldr	x3, .LC110
	mov	x2, 88
	add	x1, x19, 8
	add	x0, x19, 184
	ldr	x3, [x3, 104]
	blr	x3
	b	.L384
	.p2align 3
.L397:
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
	b	.L392
	.p2align 3
.L394:
	ldr	x2, .LC105
	mov	w3, 1768
	ldr	x1, .LC106
	mov	w0, 1
	add	x2, x2, 432
	bl	dprint_vfmw
	mov	w0, -1
	b	.L392
	.p2align 3
.L375:
	ldr	x1, .LC108
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L392
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
	beq	.L404
	add	x21, x19, 53248
	mov	x0, x19
	ldr	w22, [x21, 896]
	bl	VC1_GetPacketState
	cmp	w0, 2
	beq	.L405
.L401:
	ldr	w0, [x21, 896]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L406
.L403:
	ldr	x0, [x19, 8]
	cbz	x0, .L407
.L398:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L404:
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
.L406:
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
	cbnz	x0, .L398
	b	.L407
	.p2align 3
.L405:
	ldr	x0, .LC116
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	bne	.L402
	ldr	w0, [x0, 1600]
	cbnz	w0, .L401
.L402:
	add	x1, x19, 12288
	mov	x0, x19
	add	x1, x1, 2344
	bl	VC1DEC_Decode
	ldr	w0, [x21, 896]
	mov	x1, x20
	bl	SegMan
	cbnz	w0, .L403
	b	.L406
	.p2align 3
.L407:
	add	x19, x19, 12288
	ldrb	w0, [x19, 2527]
	cmp	w0, 1
	bne	.L398
	ldr	w0, [x21, 896]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19, 2527]
	b	.L398
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
	beq	.L414
	ldrb	w2, [x19, 18]
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
	bhi	.L415
	ldr	w2, [x1, 608]
	cmp	w2, 8
	bgt	.L416
	add	x2, x20, 16384
	sxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x2, 1528]
	ldr	w0, [x1, 608]
	mov	x1, x20
	strb	w0, [x2, 1530]
	mov	x0, x19
	beq	.L417
	bl	DecodeStream_VC1_Smp
.L408:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L415:
	ldr	x1, .LC127
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L414:
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
.L416:
	ldr	x1, .LC129
	mov	w0, 0
	bl	dprint_vfmw
	b	.L408
	.p2align 3
.L417:
	bl	DecodeStream_VC1_Adv
	b	.L408
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
	beq	.L425
	add	x21, x19, 86016
	mov	x0, x19
	ldr	w22, [x21, 3384]
	bl	MP2_GetPacketState
	cmp	w0, 2
	beq	.L426
.L421:
	ldr	w0, [x21, 3384]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L427
.L423:
	ldr	x0, [x19, 8]
	cbz	x0, .L428
.L418:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L425:
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
.L427:
	add	x1, x20, 96
	mov	x0, x19
	bl	MPEG2DEC_Decode
	ldrb	w0, [x21, 3401]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	strb	w0, [x20, 1]
	ldr	x0, [x19, 8]
	cbnz	x0, .L418
	b	.L428
	.p2align 3
.L426:
	ldr	x0, .LC132
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	bne	.L422
	ldr	w0, [x0, 1600]
	cbnz	w0, .L421
.L422:
	add	x1, x21, 2192
	mov	x0, x19
	bl	MPEG2DEC_Decode
	ldr	w0, [x21, 3384]
	mov	x1, x20
	bl	SegMan
	cbnz	w0, .L423
	b	.L427
	.p2align 3
.L428:
	ldrb	w0, [x21, 3402]
	cmp	w0, 1
	bne	.L418
	ldr	w0, [x21, 3384]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x21, 3402]
	b	.L418
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
	beq	.L435
	add	x21, x19, 20480
	mov	x0, x19
	ldr	w22, [x21, 2848]
	bl	MP4_GetPacketState
	cmp	w0, 3
	beq	.L436
.L432:
	ldr	w0, [x21, 2848]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L437
.L434:
	ldr	x0, [x19, 1040]
	cbz	x0, .L438
.L429:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L435:
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
.L437:
	add	x1, x20, 96
	mov	x0, x19
	bl	MPEG4DEC_Decode
	ldr	x0, [x19, 1040]
	cbnz	x0, .L429
	b	.L438
	.p2align 3
.L436:
	ldr	x0, .LC135
	ldr	x0, [x0, w22, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	bne	.L433
	ldr	w0, [x0, 1600]
	cbnz	w0, .L432
.L433:
	add	x1, x19, 12288
	mov	x0, x19
	add	x1, x1, 3440
	bl	MPEG4DEC_Decode
	ldr	w0, [x21, 2848]
	mov	x1, x20
	bl	SegMan
	cbnz	w0, .L434
	b	.L437
	.p2align 3
.L438:
	ldrb	w0, [x21, 2884]
	cmp	w0, 1
	bne	.L429
	ldr	w0, [x21, 2848]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x21, 2884]
	b	.L429
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
	beq	.L445
	mov	x0, x19
	ldr	w21, [x19, 4]
	bl	AVS_GetPacketState
	cbnz	w0, .L442
	ldr	x0, .LC138
	ldr	x0, [x0, w21, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	beq	.L446
.L443:
	add	x1, x19, 16384
	mov	x0, x19
	add	x1, x1, 496
	bl	AVSDEC_Decode
.L442:
	ldr	w0, [x19, 4]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L447
	ldr	x0, [x19, 24]
	cbz	x0, .L448
.L439:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L445:
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
.L447:
	add	x1, x20, 96
	mov	x0, x19
	bl	AVSDEC_Decode
	ldr	x0, [x19, 24]
	cbnz	x0, .L439
	b	.L448
	.p2align 3
.L446:
	ldr	w0, [x0, 1600]
	cbnz	w0, .L442
	b	.L443
	.p2align 3
.L448:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L439
	ldr	w0, [x19, 4]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19]
	b	.L439
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
	.global	DecodeStream_AVS2
	.type	DecodeStream_AVS2, %function
DecodeStream_AVS2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L455
	ldr	w0, [x19, 4]
	mov	x1, x20
	bl	SegMan
	cbz	w0, .L456
	ldr	w0, [x19, 8]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	strb	w0, [x20, 1]
	ldr	x0, [x19, 48]
	cbz	x0, .L457
.L449:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L455:
	ldr	x2, .LC139
	mov	w3, 1442
	ldr	x1, .LC140
	mov	w0, 1
	add	x2, x2, 560
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L456:
	add	x1, x20, 96
	mov	x0, x19
	bl	AVS2DEC_Decode
	ldr	w0, [x19, 8]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	strb	w0, [x20, 1]
	ldr	x0, [x19, 48]
	cbnz	x0, .L449
.L457:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L449
	ldr	w0, [x19, 4]
	bl	VCTRL_OutputLastFrame
	strb	wzr, [x19]
	b	.L449
	.size	DecodeStream_AVS2, .-DecodeStream_AVS2
	.align	3
.LC139:
	.xword	.LANCHOR0
	.align	3
.LC140:
	.xword	.LC2
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
	beq	.L478
	mov	w0, 6
	bl	VCTRL_RecordPosTime
	cmp	w21, 18
	bls	.L479
.L461:
	ldr	x2, .LC141
	mov	w3, 1756
	ldr	x1, .LC145
	mov	w0, 32
	add	x2, x2, 584
	bl	dprint_vfmw
.L477:
	mov	w0, 7
	bl	VCTRL_RecordPosTime
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L479:
	ldr	x0, .LC143
	ldrb	w0, [x0,w21,uxtw]
	adr	x1, .Lrtx463
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx463:
	.section	.rodata
	.align	0
	.align	2
.L463:
	.byte	(.L462 - .Lrtx463) / 4
	.byte	(.L464 - .Lrtx463) / 4
	.byte	(.L465 - .Lrtx463) / 4
	.byte	(.L466 - .Lrtx463) / 4
	.byte	(.L461 - .Lrtx463) / 4
	.byte	(.L467 - .Lrtx463) / 4
	.byte	(.L468 - .Lrtx463) / 4
	.byte	(.L461 - .Lrtx463) / 4
	.byte	(.L469 - .Lrtx463) / 4
	.byte	(.L470 - .Lrtx463) / 4
	.byte	(.L471 - .Lrtx463) / 4
	.byte	(.L471 - .Lrtx463) / 4
	.byte	(.L471 - .Lrtx463) / 4
	.byte	(.L472 - .Lrtx463) / 4
	.byte	(.L461 - .Lrtx463) / 4
	.byte	(.L473 - .Lrtx463) / 4
	.byte	(.L474 - .Lrtx463) / 4
	.byte	(.L475 - .Lrtx463) / 4
	.byte	(.L476 - .Lrtx463) / 4
	.text
	.p2align 3
.L478:
	ldr	x2, .LC141
	mov	w3, 1676
	ldr	x1, .LC142
	mov	w0, 1
	add	x2, x2, 584
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L462:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_H264
	b	.L477
	.p2align 3
.L464:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_VC1
	b	.L477
	.p2align 3
.L465:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_MPEG4
	b	.L477
	.p2align 3
.L466:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_MPEG2
	b	.L477
	.p2align 3
.L467:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_DIVX3
	b	.L477
	.p2align 3
.L468:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_AVS
	b	.L477
	.p2align 3
.L469:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_REAL8
	b	.L477
	.p2align 3
.L470:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_REAL9
	b	.L477
	.p2align 3
.L471:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_VP6x
	b	.L477
	.p2align 3
.L472:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_VP8
	b	.L477
	.p2align 3
.L473:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_MVC
	b	.L477
	.p2align 3
.L474:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_HEVC
	b	.L477
	.p2align 3
.L475:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_VP9
	b	.L477
	.p2align 3
.L476:
	mov	x1, x20
	mov	x0, x19
	bl	DecodeStream_AVS2
	b	.L477
	.size	DecodeStream, .-DecodeStream
	.align	3
.LC141:
	.xword	.LANCHOR0
	.align	3
.LC142:
	.xword	.LC2
	.align	3
.LC143:
	.xword	.L463
	.align	3
.LC145:
	.xword	.LC144
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
	cbz	x19, .L506
	sub	w0, w20, #5
	cmp	w0, 12
	bls	.L507
.L483:
	ldr	x1, .LC157
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
.L480:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L507:
	ldr	x1, .LC148
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx485
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx485:
	.section	.rodata
	.align	0
	.align	2
.L485:
	.byte	(.L484 - .Lrtx485) / 4
	.byte	(.L483 - .Lrtx485) / 4
	.byte	(.L483 - .Lrtx485) / 4
	.byte	(.L486 - .Lrtx485) / 4
	.byte	(.L487 - .Lrtx485) / 4
	.byte	(.L488 - .Lrtx485) / 4
	.byte	(.L488 - .Lrtx485) / 4
	.byte	(.L488 - .Lrtx485) / 4
	.byte	(.L489 - .Lrtx485) / 4
	.byte	(.L483 - .Lrtx485) / 4
	.byte	(.L483 - .Lrtx485) / 4
	.byte	(.L483 - .Lrtx485) / 4
	.byte	(.L490 - .Lrtx485) / 4
	.text
	.p2align 3
.L490:
	ldr	x20, [x19]
	add	x19, x19, 311296
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 3272]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 250]
	cmp	w0, 1
	beq	.L496
	ldr	x1, .LC155
	mov	w0, 1
	bl	dprint_vfmw
.L496:
	ldr	x3, .LC149
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
.L489:
	ldr	x20, [x19]
	ldr	w0, [x19, 8840]
	ldr	w1, [x20, 264]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 250]
	cmp	w0, 1
	beq	.L496
	ldr	x1, .LC151
	mov	w0, 1
	bl	dprint_vfmw
	b	.L496
	.p2align 3
.L488:
	ldr	x20, [x19]
	ldr	w0, [x19, 13368]
	ldr	w1, [x20, 264]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x20, 250]
	cmp	w0, 1
	beq	.L496
	ldr	x1, .LC153
	mov	w0, 1
	bl	dprint_vfmw
	b	.L496
	.p2align 3
.L487:
	ldr	x20, [x19]
	ldrb	w1, [x20, 250]
	cmp	w1, 1
	bne	.L496
	add	x19, x19, 53248
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2304]
	bl	SM_ReleaseStreamSeg
	b	.L496
	.p2align 3
.L486:
	ldr	x20, [x19]
	ldrb	w1, [x20, 250]
	cmp	w1, 1
	bne	.L496
	add	x19, x19, 53248
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2328]
	bl	SM_ReleaseStreamSeg
	b	.L496
	.p2align 3
.L484:
	ldr	x20, [x19]
	ldrb	w1, [x20, 250]
	cmp	w1, 1
	bne	.L496
	add	x19, x19, 40960
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2272]
	bl	SM_ReleaseStreamSeg
	b	.L496
	.p2align 3
.L506:
	ldr	x2, .LC146
	mov	w3, 1855
	ldr	x1, .LC147
	mov	w0, 1
	add	x2, x2, 600
	bl	dprint_vfmw
	b	.L480
	.size	ReleasePacket, .-ReleasePacket
	.align	3
.LC146:
	.xword	.LANCHOR0
	.align	3
.LC147:
	.xword	.LC2
	.align	3
.LC148:
	.xword	.L485
	.align	3
.LC149:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC151:
	.xword	.LC150
	.align	3
.LC153:
	.xword	.LC152
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC157:
	.xword	.LC156
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
	cbz	x20, .L527
	sub	w0, w19, #10
	cmp	w0, 7
	bls	.L528
.L508:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L528:
	ldr	x1, .LC160
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx512
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx512:
	.section	.rodata
	.align	0
	.align	2
.L512:
	.byte	(.L511 - .Lrtx512) / 4
	.byte	(.L511 - .Lrtx512) / 4
	.byte	(.L511 - .Lrtx512) / 4
	.byte	(.L513 - .Lrtx512) / 4
	.byte	(.L508 - .Lrtx512) / 4
	.byte	(.L508 - .Lrtx512) / 4
	.byte	(.L508 - .Lrtx512) / 4
	.byte	(.L514 - .Lrtx512) / 4
	.text
	.p2align 3
.L514:
	ldr	x19, [x20]
	add	x20, x20, 311296
	ldr	w1, [x19, 264]
	ldr	w0, [x20, 3272]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 250]
	cmp	w0, 1
	beq	.L517
	ldr	x1, .LC161
	mov	w0, 1
	bl	dprint_vfmw
.L517:
	ldr	x3, .LC162
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 240
	ldr	x3, [x3, 96]
	blr	x3
.L529:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L513:
	ldr	x19, [x20]
	ldr	w0, [x20, 8840]
	ldr	w1, [x19, 264]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 250]
	cmp	w0, 1
	beq	.L517
	ldr	x1, .LC163
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x3, .LC162
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 240
	ldr	x3, [x3, 96]
	blr	x3
	b	.L529
	.p2align 3
.L511:
	ldr	x19, [x20]
	ldr	w0, [x20, 13368]
	ldr	w1, [x19, 264]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 250]
	cmp	w0, 1
	beq	.L517
	ldr	x1, .LC164
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x3, .LC162
	mov	x2, 176
	mov	w1, 0
	add	x0, x19, 240
	ldr	x3, [x3, 96]
	blr	x3
	b	.L529
	.p2align 3
.L527:
	ldr	x2, .LC158
	mov	w3, 1965
	ldr	x1, .LC159
	mov	w0, 1
	add	x2, x2, 616
	bl	dprint_vfmw
	b	.L508
	.size	ReleaseCurPic_VPx, .-ReleaseCurPic_VPx
	.align	3
.LC158:
	.xword	.LANCHOR0
	.align	3
.LC159:
	.xword	.LC2
	.align	3
.LC160:
	.xword	.L512
	.align	3
.LC161:
	.xword	.LC154
	.align	3
.LC162:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC163:
	.xword	.LC150
	.align	3
.LC164:
	.xword	.LC152
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
	cbz	x19, .L537
	cmp	w20, 8
	beq	.L533
	cmp	w20, 9
	bne	.L530
	ldr	x20, [x19]
	ldrb	w1, [x20, 250]
	cmp	w1, 1
	beq	.L538
.L536:
	ldr	x3, .LC167
	mov	x2, 176
	mov	w1, 0
	add	x0, x20, 240
	ldr	x3, [x3, 96]
	blr	x3
.L530:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L533:
	ldr	x20, [x19]
	ldrb	w1, [x20, 250]
	cmp	w1, 1
	bne	.L536
	add	x19, x19, 53248
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2328]
	bl	SM_ReleaseStreamSeg
	b	.L536
	.p2align 3
.L537:
	ldr	x2, .LC165
	mov	w3, 2022
	ldr	x1, .LC166
	mov	w0, 1
	add	x2, x2, 640
	bl	dprint_vfmw
	b	.L530
	.p2align 3
.L538:
	add	x19, x19, 53248
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2304]
	bl	SM_ReleaseStreamSeg
	b	.L536
	.size	ReleaseCurPic_Realx, .-ReleaseCurPic_Realx
	.align	3
.LC165:
	.xword	.LANCHOR0
	.align	3
.LC166:
	.xword	.LC2
	.align	3
.LC167:
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
	cbz	x19, .L543
	ldr	x20, [x19]
	ldrb	w1, [x20, 250]
	cmp	w1, 1
	beq	.L544
.L542:
	ldr	x3, .LC170
	mov	x2, 176
	mov	w1, 0
	add	x0, x20, 240
	ldr	x3, [x3, 96]
	blr	x3
.L539:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L544:
	add	x19, x19, 40960
	ldr	w1, [x20, 264]
	ldr	w0, [x19, 2272]
	bl	SM_ReleaseStreamSeg
	b	.L542
	.p2align 3
.L543:
	ldr	x2, .LC168
	mov	w3, 2064
	ldr	x1, .LC169
	mov	w0, 1
	add	x2, x2, 664
	bl	dprint_vfmw
	b	.L539
	.size	ReleaseCurPic_DIVX3, .-ReleaseCurPic_DIVX3
	.align	3
.LC168:
	.xword	.LANCHOR0
	.align	3
.LC169:
	.xword	.LC2
	.align	3
.LC170:
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
	cbz	x19, .L564
	cmp	w20, 18
	bls	.L565
.L548:
	ldr	x1, .LC174
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
.L545:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L565:
	ldr	x0, .LC173
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx550
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx550:
	.section	.rodata
	.align	0
	.align	2
.L550:
	.byte	(.L549 - .Lrtx550) / 4
	.byte	(.L551 - .Lrtx550) / 4
	.byte	(.L552 - .Lrtx550) / 4
	.byte	(.L553 - .Lrtx550) / 4
	.byte	(.L548 - .Lrtx550) / 4
	.byte	(.L554 - .Lrtx550) / 4
	.byte	(.L555 - .Lrtx550) / 4
	.byte	(.L548 - .Lrtx550) / 4
	.byte	(.L556 - .Lrtx550) / 4
	.byte	(.L557 - .Lrtx550) / 4
	.byte	(.L558 - .Lrtx550) / 4
	.byte	(.L558 - .Lrtx550) / 4
	.byte	(.L558 - .Lrtx550) / 4
	.byte	(.L559 - .Lrtx550) / 4
	.byte	(.L548 - .Lrtx550) / 4
	.byte	(.L560 - .Lrtx550) / 4
	.byte	(.L561 - .Lrtx550) / 4
	.byte	(.L562 - .Lrtx550) / 4
	.byte	(.L563 - .Lrtx550) / 4
	.text
	.p2align 3
.L563:
	mov	x0, x19
	bl	AVS2DEC_ClearCurPic
	b	.L545
	.p2align 3
.L562:
	mov	x1, x19
	mov	w0, 17
	bl	ReleaseCurPic_VPx
	b	.L545
	.p2align 3
.L561:
	mov	x0, x19
	bl	HEVC_ClearCurrPic
	b	.L545
	.p2align 3
.L560:
	mov	x0, x19
	bl	MVC_ClearCurrPic
	b	.L545
	.p2align 3
.L559:
	mov	x1, x19
	mov	w0, 13
	bl	ReleaseCurPic_VPx
	b	.L545
	.p2align 3
.L558:
	mov	x1, x19
	mov	w0, w20
	bl	ReleaseCurPic_VPx
	b	.L545
	.p2align 3
.L557:
	mov	x1, x19
	mov	w0, 9
	bl	ReleaseCurPic_Realx
	b	.L545
	.p2align 3
.L556:
	mov	x1, x19
	mov	w0, 8
	bl	ReleaseCurPic_Realx
	b	.L545
	.p2align 3
.L555:
	mov	x0, x19
	bl	AVS_ClearCurPic
	b	.L545
	.p2align 3
.L554:
	mov	x1, x19
	mov	w0, 5
	bl	ReleaseCurPic_DIVX3
	b	.L545
	.p2align 3
.L553:
	mov	x0, x19
	bl	MP2_ClearCurPic
	b	.L545
	.p2align 3
.L552:
	mov	x0, x19
	bl	MP4_ClearCurPic
	mov	x0, x19
	bl	MP4_Clean_HeadPacket
	b	.L545
	.p2align 3
.L551:
	add	x1, x19, 53248
	add	x0, x19, 12288
	add	x0, x0, 2520
	ldr	w1, [x1, 896]
	bl	VC1_ClearCurPic
	b	.L545
	.p2align 3
.L549:
	mov	x0, x19
	bl	H264_ClearCurrPic
	b	.L545
	.p2align 3
.L564:
	ldr	x2, .LC171
	mov	w3, 2080
	ldr	x1, .LC172
	mov	w0, 1
	add	x2, x2, 688
	bl	dprint_vfmw
	b	.L545
	.size	ReleaseCurPic, .-ReleaseCurPic
	.align	3
.LC171:
	.xword	.LANCHOR0
	.align	3
.LC172:
	.xword	.LC2
	.align	3
.LC173:
	.xword	.L550
	.align	3
.LC174:
	.xword	.LC156
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
	mov	x19, x1
	mov	x20, x3
	mov	w21, w2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L625
	cmp	w21, 2
	mov	w0, 0
	ldr	x1, [x20]
	beq	.L626
.L569:
	ldrb	w2, [x1]
	ldrb	w3, [x1, 1]
	ldrb	w4, [x1, 2]
	cbnz	w2, .L572
	cbnz	w3, .L572
	cmp	w4, 1
	bne	.L572
	cmp	w21, 18
	bls	.L627
.L592:
	mov	w0, -1
.L568:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L627:
	ldr	x2, .LC179
	ldrb	w2, [x2,w21,uxtw]
	adr	x3, .Lrtx576
	add	x2, x3, w2, sxtb #2
	br	x2
.Lrtx576:
	.section	.rodata
	.align	0
	.align	2
.L576:
	.byte	(.L575 - .Lrtx576) / 4
	.byte	(.L577 - .Lrtx576) / 4
	.byte	(.L570 - .Lrtx576) / 4
	.byte	(.L578 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L579 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L580 - .Lrtx576) / 4
	.byte	(.L581 - .Lrtx576) / 4
	.byte	(.L592 - .Lrtx576) / 4
	.byte	(.L582 - .Lrtx576) / 4
	.text
	.p2align 3
.L626:
	ldrb	w2, [x20, 80]
	and	w0, w2, 1
	tbz	x2, 0, .L569
.L570:
	ldrb	w2, [x1, 3]
	mov	w5, 176
	mov	w3, 47
	cmp	w2, 179
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
	cbz	w3, .L585
	ldr	w3, [x19]
	cbnz	w3, .L585
.L586:
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x1, 3]
.L587:
	cmp	w2, 182
	bne	.L568
.L618:
	str	wzr, [x19]
.L629:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L578:
	ldrb	w2, [x1, 3]
	mov	w3, 179
	add	w0, w2, 73
	cmp	w2, wzr
	ccmp	w2, w3, 4, ne
	uxtb	w0, w0
	ccmp	w0, 1, 0, ne
	bls	.L628
	ldr	x3, .LC180
	mov	w0, -1
	ldr	x4, [x3, w22, sxtw 3]
	ldr	x3, [x4, 712]
	cmn	x3, #1
	bne	.L584
	ldr	w3, [x19]
	cbnz	w3, .L584
	add	w3, w2, w0
	uxtb	w3, w3
	cmp	w3, 174
	bhi	.L584
	ldr	x2, [x20, 32]
	str	x2, [x4, 712]
	ldrb	w2, [x1, 3]
.L584:
	cbnz	w2, .L568
.L623:
	str	wzr, [x19]
	b	.L629
	.p2align 3
.L582:
	ldrb	w2, [x1, 3]
	add	w3, w2, 80
	add	w0, w2, 74
	cmp	w2, 179
	uxtb	w3, w3
	cset	w4, eq
	uxtb	w0, w0
	cmp	w3, 1
	ccmp	w0, 1, 0, hi
	cset	w0, ls
	orr	w0, w4, w0
	cbz	w0, .L604
.L622:
	ldr	w0, [x19]
	cbnz	w0, .L604
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	cmp	w2, 179
	cset	w4, eq
.L589:
	cmp	w2, 182
	cset	w1, eq
	orr	w1, w4, w1
	cbz	w1, .L568
	str	wzr, [x19]
	b	.L629
	.p2align 3
.L580:
	mov	x0, x19
	bl	MVC_IsNewPicNal
	b	.L568
	.p2align 3
.L579:
	ldrb	w2, [x1, 3]
	add	w3, w2, 74
	cmp	w2, 179
	cset	w4, eq
	cmp	w2, 176
	uxtb	w3, w3
	cset	w0, eq
	cmp	w3, 1
	orr	w0, w4, w0
	cset	w3, ls
	orr	w0, w3, w0
	cbnz	w0, .L622
.L604:
	mov	w0, -1
	b	.L589
	.p2align 3
.L577:
	ldrb	w2, [x1, 3]
	mov	w0, -1
	sub	w3, w2, #12
	uxtb	w3, w3
	cmp	w3, 3
	ccmp	w2, 10, 4, hi
	cset	w3, eq
	cbnz	w3, .L630
.L590:
	cmp	w2, 13
	bne	.L568
	b	.L618
	.p2align 3
.L575:
	mov	x0, x19
	bl	H264_IsNewPicNal
	b	.L568
	.p2align 3
.L581:
	mov	x0, x19
	bl	HEVC_IsNewPicNal
	b	.L568
	.p2align 3
.L585:
	cbnz	w0, .L586
	mov	w0, -1
	b	.L587
	.p2align 3
.L572:
	ldr	x1, .LC178
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L630:
	ldr	w3, [x19]
	cbnz	w3, .L590
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	b	.L590
	.p2align 3
.L628:
	ldr	w3, [x19]
	mov	w0, -1
	cbnz	w3, .L584
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldrb	w2, [x1, 3]
	cbz	w2, .L623
	b	.L568
	.p2align 3
.L625:
	ldr	x2, .LC175
	mov	w3, 2356
	ldr	x1, .LC176
	mov	w0, 1
	add	x2, x2, 704
	bl	dprint_vfmw
	mov	w0, -1
	b	.L568
	.size	IsNewpicSeg, .-IsNewpicSeg
	.align	3
.LC175:
	.xword	.LANCHOR0
	.align	3
.LC176:
	.xword	.LC2
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC179:
	.xword	.L576
	.align	3
.LC180:
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
	bhi	.L637
	ldr	x19, .LC183
	add	x19, x19, 128
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L631
	ldr	x1, .LC184
	ldr	x1, [x1, 440]
	blr	x1
	str	xzr, [x19, w20, sxtw 3]
.L631:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L637:
	ldr	x2, .LC181
	mov	w3, 2414
	ldr	x1, .LC182
	mov	w0, 1
	add	x2, x2, 720
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CloseUsdPool, .-CloseUsdPool
	.align	3
.LC181:
	.xword	.LANCHOR0
	.align	3
.LC182:
	.xword	.LC2
	.align	3
.LC183:
	.xword	.LANCHOR1
	.align	3
.LC184:
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
	bhi	.L644
	ldr	x0, .LC188
	add	x0, x0, 128
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L638
	str	xzr, [x0, w19, sxtw 3]
.L638:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L644:
	ldr	x2, .LC186
	mov	w3, 2446
	ldr	x1, .LC187
	mov	w0, 1
	add	x2, x2, 736
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CloseUsdPool_WithMem, .-CloseUsdPool_WithMem
	.align	3
.LC186:
	.xword	.LANCHOR0
	.align	3
.LC187:
	.xword	.LC2
	.align	3
.LC188:
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
	bhi	.L651
	ldr	x0, .LC194
	add	x0, x0, 128
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L649
	add	x1, x0, 204800
	str	wzr, [x0]
	add	x1, x1, 536
	add	x0, x0, 1048
	.p2align 2
.L648:
	stp	wzr, wzr, [x0, -4]
	add	x0, x0, 1064
	cmp	x0, x1
	bne	.L648
	mov	w0, 0
.L647:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L651:
	ldr	x2, .LC192
	mov	w3, 2464
	ldr	x1, .LC193
	mov	w0, 1
	add	x2, x2, 760
	bl	dprint_vfmw
	mov	w0, -1
	b	.L647
.L649:
	mov	w0, -1
	b	.L647
	.size	InitUsdPool, .-InitUsdPool
	.align	3
.LC192:
	.xword	.LANCHOR0
	.align	3
.LC193:
	.xword	.LC2
	.align	3
.LC194:
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
	bhi	.L656
	ldr	x20, .LC198
	add	x20, x20, 128
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L657
.L655:
	mov	w0, w19
	bl	InitUsdPool
.L654:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L657:
	ldr	x1, .LC199
	mov	w0, 7688
	movk	w0, 0x3, lsl 16
	ldr	x1, [x1, 432]
	blr	x1
	str	x0, [x20, w19, sxtw 3]
	b	.L655
	.p2align 3
.L656:
	ldr	x2, .LC196
	mov	w3, 2399
	ldr	x1, .LC197
	mov	w0, 1
	add	x2, x2, 776
	bl	dprint_vfmw
	mov	w0, -1
	b	.L654
	.size	OpenUsdPool, .-OpenUsdPool
	.align	3
.LC196:
	.xword	.LANCHOR0
	.align	3
.LC197:
	.xword	.LC2
	.align	3
.LC198:
	.xword	.LANCHOR1
	.align	3
.LC199:
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
	bhi	.L663
	cbz	x20, .L664
	ldr	x0, .LC203
	add	x0, x0, 128
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L665
.L662:
	mov	w0, w19
	bl	InitUsdPool
.L660:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L665:
	str	x20, [x0, w19, sxtw 3]
	b	.L662
	.p2align 3
.L663:
	ldr	x2, .LC201
	mov	w3, 2431
	ldr	x1, .LC202
	mov	w0, 1
	add	x2, x2, 792
	bl	dprint_vfmw
	mov	w0, -1
	b	.L660
.L664:
	ldr	x2, .LC201
	mov	w3, 2432
	ldr	x1, .LC202
	mov	w0, 1
	add	x2, x2, 792
	bl	dprint_vfmw
	mov	w0, -1
	b	.L660
	.size	OpenUsdPool_WithMem, .-OpenUsdPool_WithMem
	.align	3
.LC201:
	.xword	.LANCHOR0
	.align	3
.LC202:
	.xword	.LC2
	.align	3
.LC203:
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
	bhi	.L673
	ldr	x0, .LC207
	add	x0, x0, 128
	ldr	x3, [x0, w19, sxtw 3]
	cbz	x3, .L671
	add	x0, x3, 1048
	mov	w1, 0
	b	.L670
	.p2align 3
.L669:
	add	w1, w1, 1
	add	x0, x0, 1064
	cmp	w1, 192
	beq	.L671
.L670:
	ldr	w2, [x0]
	cbnz	w2, .L669
	ldr	w2, [x0, -4]
	cbnz	w2, .L669
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
.L668:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L671:
	mov	x0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L673:
	ldr	x2, .LC205
	mov	w3, 2494
	ldr	x1, .LC206
	mov	w0, 1
	add	x2, x2, 816
	bl	dprint_vfmw
	mov	x0, 0
	b	.L668
	.size	GetUsd, .-GetUsd
	.align	3
.LC205:
	.xword	.LANCHOR0
	.align	3
.LC206:
	.xword	.LC2
	.align	3
.LC207:
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
	cbz	x19, .L677
	str	wzr, [x19, 1040]
.L674:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L677:
	ldr	x2, .LC209
	mov	w3, 2525
	ldr	x1, .LC210
	mov	w0, 1
	add	x2, x2, 824
	bl	dprint_vfmw
	b	.L674
	.size	FreeUsdByDec, .-FreeUsdByDec
	.align	3
.LC209:
	.xword	.LANCHOR0
	.align	3
.LC210:
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
	cbz	x19, .L681
	mov	w0, 1
	str	w0, [x19, 1036]
.L678:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L681:
	ldr	x2, .LC211
	mov	w3, 2536
	ldr	x1, .LC212
	mov	w0, 1
	add	x2, x2, 840
	bl	dprint_vfmw
	b	.L678
	.size	MarkUsdByDnr, .-MarkUsdByDnr
	.align	3
.LC211:
	.xword	.LANCHOR0
	.align	3
.LC212:
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
	cbz	x19, .L685
	str	wzr, [x19, 1036]
.L682:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L685:
	ldr	x2, .LC213
	mov	w3, 2546
	ldr	x1, .LC214
	mov	w0, 1
	add	x2, x2, 856
	bl	dprint_vfmw
	b	.L682
	.size	UnMarkUsdByDnr, .-UnMarkUsdByDnr
	.align	3
.LC213:
	.xword	.LANCHOR0
	.align	3
.LC214:
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
	cbz	x19, .L699
	cbz	x20, .L700
	ldrh	w0, [x19, 4]
	ldrh	w4, [x19, 8]
	and	w0, w0, 63
	.p2align 2
.L698:
	cmp	w0, w4
	beq	.L692
	sxtw	x2, w0
	add	w0, w0, 1
	add	x2, x2, 2
	and	w0, w0, 63
	ldr	x2, [x19, x2, lsl 3]
	cbz	x2, .L698
	ldr	w3, [x2, 148]
	ldr	w2, [x20, 148]
	cmp	w3, w2
	bne	.L698
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L692:
	mov	w0, -1
.L688:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L700:
	ldr	x1, .LC217
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L688
.L699:
	ldr	x2, .LC215
	mov	w3, 2558
	ldr	x1, .LC216
	mov	w0, 1
	add	x2, x2, 872
	bl	dprint_vfmw
	mov	w0, -1
	b	.L688
	.size	IsImageInVoQueue, .-IsImageInVoQueue
	.align	3
.LC215:
	.xword	.LANCHOR0
	.align	3
.LC216:
	.xword	.LC2
	.align	3
.LC217:
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
	cbz	x19, .L705
	ldrh	w2, [x19, 6]
	mov	w0, 0
	ldrh	w1, [x19, 8]
	cmp	w1, w2
	beq	.L706
.L703:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L706:
	ldrh	w0, [x19, 4]
	ldr	x19, [sp, 16]
	cmp	w0, w1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L705:
	ldr	x2, .LC218
	mov	w0, 0
	ldr	x1, .LC220
	add	x2, x2, 896
	bl	dprint_vfmw
	mov	w0, 0
	b	.L703
	.size	IsVoQueueEmpty, .-IsVoQueueEmpty
	.align	3
.LC218:
	.xword	.LANCHOR0
	.align	3
.LC220:
	.xword	.LC219
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
	cbz	x19, .L718
	cmp	w20, 5
	bls	.L719
	ldr	x1, .LC225
	mov	w0, 1
	mov	w2, w20
	stp	wzr, w0, [x19, 100]
	bl	dprint_vfmw
.L707:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L719:
	ldr	x0, .LC223
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx712
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx712:
	.section	.rodata
	.align	0
	.align	2
.L712:
	.byte	(.L711 - .Lrtx712) / 4
	.byte	(.L713 - .Lrtx712) / 4
	.byte	(.L714 - .Lrtx712) / 4
	.byte	(.L715 - .Lrtx712) / 4
	.byte	(.L716 - .Lrtx712) / 4
	.byte	(.L717 - .Lrtx712) / 4
	.text
	.p2align 3
.L716:
	mov	w1, 235
	mov	w0, 100
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L715:
	mov	w1, 221
	mov	w0, 100
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L714:
	mov	w1, 16
	mov	w0, 9
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L713:
	mov	w1, 4
	mov	w0, 3
	stp	w1, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L711:
	mov	w0, 1
	stp	wzr, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L717:
	mov	w0, 2
	stp	wzr, w0, [x19, 100]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L718:
	ldr	x2, .LC221
	mov	w3, 2606
	ldr	x1, .LC222
	mov	w0, 1
	add	x2, x2, 912
	bl	dprint_vfmw
	b	.L707
	.size	SetAspectRatio, .-SetAspectRatio
	.align	3
.LC221:
	.xword	.LANCHOR0
	.align	3
.LC222:
	.xword	.LC2
	.align	3
.LC223:
	.xword	.L712
	.align	3
.LC225:
	.xword	.LC224
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
	cbz	x19, .L724
	ldr	w0, [x19, 552]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	csinv	w0, w0, wzr, hi
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L724:
	ldr	x2, .LC226
	mov	w3, 2654
	ldr	x1, .LC227
	mov	w0, 1
	add	x2, x2, 928
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.size	GetVoLastImageID, .-GetVoLastImageID
	.align	3
.LC226:
	.xword	.LANCHOR0
	.align	3
.LC227:
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
	cbz	x19, .L734
	ldr	w1, [x19, 332]
	cmp	w1, 1
	beq	.L729
	ldr	w2, [x19, 336]
	mov	w0, 0
	cmp	w2, 1
	beq	.L732
	cmp	w1, 2
	ldr	w1, [x19, 340]
	beq	.L731
	cmp	w1, 1
	cset	w0, eq
.L728:
	cmp	w1, 1
	cset	w1, eq
	orr	w0, w1, w0
.L732:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L729:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L731:
	mov	w0, 1
	b	.L728
	.p2align 3
.L734:
	ldr	x2, .LC228
	mov	w3, 2669
	ldr	x1, .LC229
	mov	w0, 1
	add	x2, x2, 952
	bl	dprint_vfmw
	mov	w0, 0
	b	.L732
	.size	IsMain10Profile, .-IsMain10Profile
	.align	3
.LC228:
	.xword	.LANCHOR0
	.align	3
.LC229:
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
	bhi	.L739
	ldr	x0, .LC232
	sub	x19, x19, x21
	ldr	x0, [x0, w20, sxtw 3]
	ldr	w0, [x0, 128]
	cbnz	w0, .L740
	cmp	x19, 1000
	ldr	x21, [sp, 32]
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L740:
	mov	x0, 16960
	ldr	x21, [sp, 32]
	movk	x0, 0xf, lsl 16
	cmp	x19, x0
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L739:
	ldr	x2, .LC230
	mov	w3, 2694
	ldr	x1, .LC231
	mov	w0, 1
	add	x2, x2, 968
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	IsPtsRewind, .-IsPtsRewind
	.align	3
.LC230:
	.xword	.LANCHOR0
	.align	3
.LC231:
	.xword	.LC2
	.align	3
.LC232:
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
	.type	__func__.12113, %object
	.size	__func__.12113, 13
__func__.12113:
	.string	"PrintVoQueue"
	.zero	3
	.type	__func__.12119, %object
	.size	__func__.12119, 13
__func__.12119:
	.string	"ResetVoQueue"
	.zero	3
	.type	__func__.12125, %object
	.size	__func__.12125, 20
__func__.12125:
	.string	"ReturnImageToSyntax"
	.zero	4
	.type	__func__.12190, %object
	.size	__func__.12190, 19
__func__.12190:
	.string	"InsertImgToVoQueue"
	.zero	5
	.type	__FUNCTION__.12193, %object
	.size	__FUNCTION__.12193, 19
__FUNCTION__.12193:
	.string	"InsertImgToVoQueue"
	.zero	5
	.type	__func__.12201, %object
	.size	__func__.12201, 15
__func__.12201:
	.string	"GetQueueImgNum"
	.zero	1
	.type	__func__.12231, %object
	.size	__func__.12231, 20
__func__.12231:
	.string	"SYNTAX_ReceiveImage"
	.zero	4
	.type	__func__.12278, %object
	.size	__func__.12278, 20
__func__.12278:
	.string	"SYNTAX_ReleaseImage"
	.zero	4
	.type	__func__.12287, %object
	.size	__func__.12287, 19
__func__.12287:
	.string	"SYNTAX_ReturnImage"
	.zero	5
	.type	__func__.12313, %object
	.size	__func__.12313, 18
__func__.12313:
	.string	"DecodeStream_H264"
	.zero	6
	.type	__func__.12320, %object
	.size	__func__.12320, 18
__func__.12320:
	.string	"DecodeStream_HEVC"
	.zero	6
	.type	__func__.12325, %object
	.size	__func__.12325, 17
__func__.12325:
	.string	"DecodeStream_VP9"
	.zero	7
	.type	__func__.12332, %object
	.size	__func__.12332, 17
__func__.12332:
	.string	"DecodeStream_MVC"
	.zero	7
	.type	__func__.12345, %object
	.size	__func__.12345, 21
__func__.12345:
	.string	"DecodeStream_VC1_Smp"
	.zero	3
	.type	__func__.12384, %object
	.size	__func__.12384, 19
__func__.12384:
	.string	"DecodeStream_REAL8"
	.zero	5
	.type	__func__.12390, %object
	.size	__func__.12390, 19
__func__.12390:
	.string	"DecodeStream_REAL9"
	.zero	5
	.type	__func__.12396, %object
	.size	__func__.12396, 19
__func__.12396:
	.string	"DecodeStream_DIVX3"
	.zero	5
	.type	__func__.12402, %object
	.size	__func__.12402, 17
__func__.12402:
	.string	"DecodeStream_VP8"
	.zero	7
	.type	__func__.12408, %object
	.size	__func__.12408, 18
__func__.12408:
	.string	"DecodeStream_VP6x"
	.zero	6
	.type	__func__.12438, %object
	.size	__func__.12438, 7
__func__.12438:
	.string	"SegMan"
	.zero	1
	.type	__func__.12339, %object
	.size	__func__.12339, 21
__func__.12339:
	.string	"DecodeStream_VC1_Adv"
	.zero	3
	.type	__func__.12350, %object
	.size	__func__.12350, 17
__func__.12350:
	.string	"DecodeStream_VC1"
	.zero	7
	.type	__func__.12357, %object
	.size	__func__.12357, 19
__func__.12357:
	.string	"DecodeStream_MPEG2"
	.zero	5
	.type	__func__.12364, %object
	.size	__func__.12364, 19
__func__.12364:
	.string	"DecodeStream_MPEG4"
	.zero	5
	.type	__func__.12371, %object
	.size	__func__.12371, 17
__func__.12371:
	.string	"DecodeStream_AVS"
	.zero	7
	.type	__func__.12378, %object
	.size	__func__.12378, 18
__func__.12378:
	.string	"DecodeStream_AVS2"
	.zero	6
	.type	__func__.12414, %object
	.size	__func__.12414, 13
__func__.12414:
	.string	"DecodeStream"
	.zero	3
	.type	__func__.12444, %object
	.size	__func__.12444, 14
__func__.12444:
	.string	"ReleasePacket"
	.zero	2
	.type	__func__.12460, %object
	.size	__func__.12460, 18
__func__.12460:
	.string	"ReleaseCurPic_VPx"
	.zero	6
	.type	__func__.12473, %object
	.size	__func__.12473, 20
__func__.12473:
	.string	"ReleaseCurPic_Realx"
	.zero	4
	.type	__func__.12483, %object
	.size	__func__.12483, 20
__func__.12483:
	.string	"ReleaseCurPic_DIVX3"
	.zero	4
	.type	__func__.12488, %object
	.size	__func__.12488, 14
__func__.12488:
	.string	"ReleaseCurPic"
	.zero	2
	.type	__func__.12568, %object
	.size	__func__.12568, 12
__func__.12568:
	.string	"IsNewpicSeg"
	.zero	4
	.type	__func__.12578, %object
	.size	__func__.12578, 13
__func__.12578:
	.string	"CloseUsdPool"
	.zero	3
	.type	__func__.12588, %object
	.size	__func__.12588, 21
__func__.12588:
	.string	"CloseUsdPool_WithMem"
	.zero	3
	.type	__func__.12594, %object
	.size	__func__.12594, 12
__func__.12594:
	.string	"InitUsdPool"
	.zero	4
	.type	__func__.12574, %object
	.size	__func__.12574, 12
__func__.12574:
	.string	"OpenUsdPool"
	.zero	4
	.type	__func__.12584, %object
	.size	__func__.12584, 20
__func__.12584:
	.string	"OpenUsdPool_WithMem"
	.zero	4
	.type	__func__.12604, %object
	.size	__func__.12604, 7
__func__.12604:
	.string	"GetUsd"
	.zero	1
	.type	__func__.12612, %object
	.size	__func__.12612, 13
__func__.12612:
	.string	"FreeUsdByDec"
	.zero	3
	.type	__func__.12617, %object
	.size	__func__.12617, 13
__func__.12617:
	.string	"MarkUsdByDnr"
	.zero	3
	.type	__func__.12622, %object
	.size	__func__.12622, 15
__func__.12622:
	.string	"UnMarkUsdByDnr"
	.zero	1
	.type	__func__.12628, %object
	.size	__func__.12628, 17
__func__.12628:
	.string	"IsImageInVoQueue"
	.zero	7
	.type	__func__.12634, %object
	.size	__func__.12634, 15
__func__.12634:
	.string	"IsVoQueueEmpty"
	.zero	1
	.type	__func__.12639, %object
	.size	__func__.12639, 15
__func__.12639:
	.string	"SetAspectRatio"
	.zero	1
	.type	__func__.12652, %object
	.size	__func__.12652, 17
__func__.12652:
	.string	"GetVoLastImageID"
	.zero	7
	.type	__func__.12657, %object
	.size	__func__.12657, 16
__func__.12657:
	.string	"IsMain10Profile"
	.type	__func__.12664, %object
	.size	__func__.12664, 12
__func__.12664:
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
.LC144:
	ASCII(.string	"Func: %s, Line: %d\n" )
	.zero	4
.LC150:
	ASCII(.string	"ERROR: VFMW_VP8 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC152:
	ASCII(.string	"ERROR: VFMW_VP6 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC154:
	ASCII(.string	"ERROR: VFMW_VP9 one packet stream, but IsLastSeg == 0\n" )
	.zero	1
.LC156:
	ASCII(.string	"VidStd=%d Error!\n" )
	.zero	6
.LC177:
	ASCII(.string	"pu8[0] = %x,pu8[1] = %x, pu8[2] = %x\n" )
	.zero	2
.LC219:
	ASCII(.string	"%s pstVoQue NULL\n" )
	.zero	6
.LC224:
	ASCII(.string	"WARNNING: aspect ration (%d) is not expected!\n" )
	.bss
	.align	3
.LANCHOR1 = . + 0
	.type	last_rec_pos_time.12189, %object
	.size	last_rec_pos_time.12189, 128
last_rec_pos_time.12189:
	.zero	128
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 256
pstVdecUsdPool:
	.zero	256
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
