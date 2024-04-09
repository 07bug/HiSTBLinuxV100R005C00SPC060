#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"pq_mng_dm_alg.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	PQ_MNG_ALG_UpdateDMCfg
	.type	PQ_MNG_ALG_UpdateDMCfg, %function
PQ_MNG_ALG_UpdateDMCfg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	w0, [x20, 164]
	add	x2, x20, 184
	cmp	w0, 720
	bgt	.L2
	ldrb	w1, [x20, 169]
	cmp	w1, 1
	beq	.L30
.L2:
	ldrb	w0, [x20, 168]
.L12:
	lsl	x1, x0, 2
	sub	x0, x1, x0
	lsl	x0, x0, 4
	add	x20, x2, x0
	ldrh	w0, [x2, x0]
	strh	w0, [x19, 106]
	ldrh	w0, [x20, 2]
	strh	w0, [x19, 108]
	ldrh	w0, [x20, 4]
	strh	w0, [x19, 116]
	ldrh	w0, [x20, 6]
	strh	w0, [x19, 118]
	ldrb	w0, [x20, 8]
	strb	w0, [x19, 134]
	ldrb	w0, [x20, 9]
	strb	w0, [x19, 135]
	ldrsh	w4, [x20, 10]
	strh	w4, [x19, 124]
	ldrsh	w2, [x20, 12]
	strh	w2, [x19, 126]
	ldrsh	w3, [x20, 14]
	strh	w3, [x19, 128]
	ldrsh	w1, [x20, 16]
	strh	w1, [x19, 130]
	ldrb	w0, [x20, 20]
	strb	w0, [x19, 132]
	cmp	w0, 1
	beq	.L31
.L16:
	ldrb	w0, [x20, 19]
	strb	w0, [x19, 133]
	ldrb	w0, [x20, 18]
	strb	w0, [x19, 138]
	ldr	x1, [x20, 40]
	cbz	x1, .L17
	mov	x2, 62
	add	x0, x19, 140
	bl	pq_alg_memcpy
.L17:
	ldrh	w0, [x20, 22]
	strh	w0, [x19, 100]
	mov	w0, 0
	ldr	x2, .LC1
	ldrh	w1, [x20, 24]
	strh	w1, [x19, 102]
	ldr	w2, [x2]
	ldrb	w1, [x20, 26]
	strb	w1, [x19, 136]
	ldrb	w1, [x20, 27]
	strb	w1, [x19, 137]
	ldrb	w1, [x20, 28]
	strb	w1, [x19, 110]
	ldrh	w1, [x20, 30]
	strh	w1, [x19, 112]
	ldrh	w1, [x20, 32]
	strh	w1, [x19, 114]
	ldrh	w1, [x20, 34]
	strh	w1, [x19, 120]
	ldrh	w1, [x20, 36]
	strh	w1, [x19, 122]
	strb	w2, [x19, 99]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L30:
	mov	w3, 15
	cmp	w0, wzr
	csel	w3, wzr, w3, le
	cbz	x20, .L19
	ldr	x5, .LC0
	ldr	w4, [x5]
	cmp	w4, 31
	bhi	.L20
	uxtw	x0, w4
	add	w1, w4, 1
	lsl	x7, x0, 2
.L5:
	add	x4, x20, x0, lsl 2
	str	w1, [x5]
	add	x6, x20, 12
	add	x0, x6, x7
	str	w3, [x4, 12]
	str	x0, [x20, 152]
	ldr	w5, [x20, 140]
	cmp	w5, wzr
	beq	.L6
	mov	w1, 0
	mov	w3, 0
	add	x7, x20, 136
	ble	.L8
	.p2align 2
.L25:
	ldr	w4, [x0], -4
	add	w1, w1, 1
	cmp	x0, x6
	add	w3, w3, w4
	csel	x0, x0, x7, cs
	cmp	w5, w1
	bne	.L25
.L8:
	sdiv	w3, w3, w5
	uxth	w3, w3
.L9:
	ldrh	w0, [x20, 170]
	cmp	w0, w3
	bls	.L4
	ldrb	w0, [x20, 178]
	b	.L12
	.p2align 3
.L31:
	cmp	w4, w3
	ccmp	w2, w1, 4, gt
	bgt	.L16
	strb	wzr, [x19, 132]
	b	.L16
	.p2align 3
.L19:
	mov	w3, 65535
.L4:
	ldrh	w0, [x20, 172]
	cmp	w0, w3
	bhi	.L32
	ldrh	w0, [x20, 174]
	cmp	w0, w3
	bls	.L14
	ldrb	w0, [x20, 180]
	b	.L12
	.p2align 3
.L6:
	ldrh	w3, [x6, x7]
	b	.L9
	.p2align 3
.L20:
	mov	x7, 0
	mov	x0, 0
	b	.L5
	.p2align 3
.L32:
	ldrb	w0, [x20, 179]
	b	.L12
	.p2align 3
.L14:
	ldrh	w0, [x20, 176]
	cmp	w0, w3
	bls	.L15
	ldrb	w0, [x20, 181]
	b	.L12
.L15:
	ldrb	w0, [x20, 182]
	b	.L12
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
	.type	i.1997, %object
	.size	i.1997, 4
i.1997:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
