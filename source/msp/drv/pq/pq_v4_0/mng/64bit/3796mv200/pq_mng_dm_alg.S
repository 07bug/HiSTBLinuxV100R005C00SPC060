#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"pq_mng_dm_alg.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	DM_GetDetRatio
	.type	DM_GetDetRatio, %function
DM_GetDetRatio:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 164]
	mov	w0, 15
	ldr	x19, [sp, 16]
	cmp	w1, wzr
	csel	w0, w0, wzr, gt
	ldp	x29, x30, [sp], 32
	ret
	.size	DM_GetDetRatio, .-DM_GetDetRatio
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DM_GetDMParaFlag
	.type	DM_GetDMParaFlag, %function
DM_GetDMParaFlag:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	uxth	w19, w0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	ldrh	w0, [x20]
	cmp	w0, w19
	bhi	.L9
	ldrh	w0, [x20, 2]
	cmp	w0, w19
	bhi	.L10
	ldrh	w0, [x20, 4]
	cmp	w0, w19
	bhi	.L11
	ldrh	w0, [x20, 6]
	cmp	w0, w19
	bhi	.L13
	ldrb	w0, [x21, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L9:
	mov	x0, 0
	ldrb	w0, [x21, x0]
.L14:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L10:
	mov	x0, 1
	ldrb	w0, [x21, x0]
	b	.L14
	.p2align 3
.L11:
	mov	x0, 2
	ldrb	w0, [x21, x0]
	b	.L14
	.p2align 3
.L13:
	mov	x0, 3
	ldrb	w0, [x21, x0]
	b	.L14
	.size	DM_GetDMParaFlag, .-DM_GetDMParaFlag
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_UpdateDMCfg
	.type	PQ_MNG_ALG_UpdateDMCfg, %function
PQ_MNG_ALG_UpdateDMCfg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	add	x21, x20, 184
	bl	_mcount
	strb	wzr, [x29, 68]
	ldr	w0, [x20, 164]
	str	wzr, [x29, 64]
	cmp	w0, 720
	str	xzr, [x29, 72]
	bgt	.L16
	ldrb	w1, [x20, 169]
	cmp	w1, 1
	beq	.L47
.L16:
	ldrb	w0, [x20, 168]
.L29:
	lsl	x1, x0, 2
	sub	x0, x1, x0
	lsl	x0, x0, 4
	add	x20, x21, x0
	ldrh	w0, [x21, x0]
	strh	w0, [x19, 106]
	ldrh	w0, [x20, 2]
	strh	w0, [x19, 108]
	ldrh	w0, [x20, 4]
	strh	w0, [x19, 116]
	ldrh	w0, [x20, 6]
	strh	w0, [x19, 118]
	ldrb	w0, [x20, 8]
	strb	w0, [x19, 306]
	ldrb	w0, [x20, 9]
	strb	w0, [x19, 307]
	ldrsh	w4, [x20, 10]
	strh	w4, [x19, 126]
	ldrsh	w2, [x20, 12]
	strh	w2, [x19, 128]
	ldrsh	w3, [x20, 14]
	strh	w3, [x19, 130]
	ldrsh	w1, [x20, 16]
	strh	w1, [x19, 132]
	ldrb	w0, [x20, 20]
	strb	w0, [x19, 305]
	cmp	w0, 1
	beq	.L48
.L30:
	ldrb	w0, [x20, 19]
	strb	w0, [x19, 304]
	ldrb	w0, [x20, 18]
	strb	w0, [x19, 124]
	ldr	x1, [x20, 40]
	cbz	x1, .L31
	mov	x2, 62
	add	x0, x19, 138
	bl	pq_alg_memcpy
.L31:
	ldrh	w0, [x20, 22]
	strh	w0, [x19, 310]
	ldr	x1, .LC1
	ldrh	w0, [x20, 24]
	strh	w0, [x19, 312]
	ldr	w1, [x1]
	ldrb	w0, [x20, 26]
	strb	w0, [x19, 308]
	ldrb	w0, [x20, 27]
	strb	w0, [x19, 309]
	ldrb	w0, [x20, 28]
	strb	w0, [x19, 110]
	ldrh	w0, [x20, 30]
	strh	w0, [x19, 112]
	ldrh	w0, [x20, 32]
	strh	w0, [x19, 114]
	ldrh	w0, [x20, 34]
	strh	w0, [x19, 120]
	ldrh	w0, [x20, 36]
	strh	w0, [x19, 122]
	mov	w0, 0
	strb	w1, [x19, 104]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L47:
	mov	w2, 15
	cmp	w0, wzr
	csel	w2, wzr, w2, le
	cbz	x20, .L18
	ldr	x5, .LC0
	ldr	w3, [x5]
	cmp	w3, 31
	bhi	.L34
	uxtw	x0, w3
	add	w1, w3, 1
	lsl	x6, x0, 2
.L19:
	add	x3, x20, x0, lsl 2
	add	x4, x20, 12
	add	x0, x4, x6
	str	w1, [x5]
	str	w2, [x3, 12]
	str	x0, [x20, 152]
	ldr	w22, [x20, 140]
	cmp	w22, wzr
	beq	.L20
	mov	w2, 0
	mov	w1, 0
	add	x5, x20, 136
	ble	.L22
	.p2align 2
.L42:
	ldr	w3, [x0], -4
	add	w2, w2, 1
	cmp	x0, x4
	add	w1, w1, w3
	csel	x0, x0, x5, cs
	cmp	w22, w2
	bne	.L42
.L22:
	sdiv	w1, w1, w22
	uxth	w22, w1
.L23:
	mov	x2, 8
	add	x1, x20, 170
	add	x0, x29, 72
	add	x23, x29, 64
	bl	pq_alg_memcpy
	mov	x0, x23
	mov	x2, 5
	add	x1, x20, 178
	bl	pq_alg_memcpy
	ldrh	w0, [x29, 72]
	cmp	w0, w22
	bhi	.L26
.L32:
	ldrh	w0, [x29, 74]
	cmp	w0, w22
	bhi	.L36
	ldrh	w0, [x29, 76]
	cmp	w0, w22
	bhi	.L37
	ldrh	w0, [x29, 78]
	cmp	w0, w22
	bhi	.L49
	ldrb	w0, [x29, 68]
	b	.L29
	.p2align 3
.L48:
	cmp	w4, w3
	ccmp	w2, w1, 4, gt
	bgt	.L30
	strb	wzr, [x19, 305]
	b	.L30
	.p2align 3
.L20:
	ldrh	w22, [x4, x6]
	b	.L23
	.p2align 3
.L34:
	mov	x6, 0
	mov	x0, 0
	b	.L19
.L37:
	mov	x0, 2
	add	x23, x23, x0
.L26:
	ldrb	w0, [x23]
	b	.L29
	.p2align 3
.L18:
	add	x0, x29, 72
	mov	x2, 8
	mov	x1, 170
	add	x23, x29, 64
	mov	w22, 65535
	bl	pq_alg_memcpy
	mov	x2, 5
	mov	x1, 178
	mov	x0, x23
	bl	pq_alg_memcpy
	b	.L32
.L36:
	mov	x0, 1
	add	x23, x23, x0
	b	.L26
.L49:
	mov	x0, 3
	add	x23, x23, x0
	b	.L26
	.size	PQ_MNG_ALG_UpdateDMCfg, .-PQ_MNG_ALG_UpdateDMCfg
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC1:
	.xword	.LANCHOR1
	.global	g_u32DmStr
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	g_u32DmStr, %object
	.size	g_u32DmStr, 4
g_u32DmStr:
	.word	8
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	i.2016, %object
	.size	i.2016, 4
i.2016:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
