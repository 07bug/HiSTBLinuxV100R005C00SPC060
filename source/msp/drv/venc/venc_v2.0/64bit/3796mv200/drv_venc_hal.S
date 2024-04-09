#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"drv_venc_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_ClrInt
	.type	DRV_VENC_HAL_V500R001_ClrInt, %function
DRV_VENC_HAL_V500R001_ClrInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC0
	cmp	w19, 1
	ldr	x0, [x0]
	beq	.L3
	cbz	w19, .L4
	cmp	w19, 2
	beq	.L5
	mov	w1, -1
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5:
	ldr	w1, [x0, 4]
	orr	w1, w1, 64
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4:
	ldr	w1, [x0, 4]
	orr	w1, w1, 1
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3:
	ldr	w1, [x0, 4]
	orr	w1, w1, 2
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V500R001_ClrInt, .-DRV_VENC_HAL_V500R001_ClrInt
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_DisableInt
	.type	DRV_VENC_HAL_V500R001_DisableInt, %function
DRV_VENC_HAL_V500R001_DisableInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC1
	cmp	w19, 1
	ldr	x0, [x0]
	beq	.L12
	cbz	w19, .L13
	cmp	w19, 2
	beq	.L14
	str	wzr, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L14:
	ldr	w1, [x0]
	and	w1, w1, -65
	str	w1, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L13:
	ldr	w1, [x0]
	and	w1, w1, -2
	str	w1, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L12:
	ldr	w1, [x0]
	and	w1, w1, -3
	str	w1, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V500R001_DisableInt, .-DRV_VENC_HAL_V500R001_DisableInt
	.align	3
.LC1:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_ReadReg_Smmu
	.type	DRV_VENC_HAL_V500R001_ReadReg_Smmu, %function
DRV_VENC_HAL_V500R001_ReadReg_Smmu:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC2
	ldr	x0, [x0]
	cbz	x19, .L18
	add	x0, x0, 61440
	mov	w2, -1
	ldr	w1, [x0, 40]
	and	w1, w1, 1
	str	w1, [x19]
	ldr	w1, [x0, 40]
	ubfx	x1, x1, 1, 1
	str	w1, [x19, 4]
	ldr	w1, [x0, 40]
	ubfx	x1, x1, 2, 1
	str	w1, [x19, 8]
	ldr	w1, [x0, 40]
	ubfx	x1, x1, 3, 1
	str	w1, [x19, 12]
	ldr	w1, [x0, 24]
	and	w1, w1, 1
	str	w1, [x19, 16]
	ldr	w1, [x0, 24]
	ubfx	x1, x1, 1, 1
	str	w1, [x19, 20]
	ldr	w1, [x0, 24]
	ubfx	x1, x1, 2, 1
	str	w1, [x19, 24]
	ldr	w1, [x0, 24]
	ubfx	x1, x1, 3, 1
	str	w1, [x19, 28]
	ldr	w1, [x0, 864]
	str	w1, [x19, 32]
	ldr	w1, [x0, 848]
	str	w1, [x19, 40]
	ldr	w1, [x0, 832]
	str	w1, [x19, 36]
	ldr	w1, [x0, 816]
	str	w1, [x19, 44]
	str	w2, [x0, 28]
.L18:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V500R001_ReadReg_Smmu, .-DRV_VENC_HAL_V500R001_ReadReg_Smmu
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_ReadReg
	.type	DRV_VENC_HAL_V500R001_ReadReg, %function
DRV_VENC_HAL_V500R001_ReadReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC3
	ldp	x0, x4, [x1]
	cbz	x19, .L23
	ldr	w1, [x0, 12292]
	and	w1, w1, 1
	str	w1, [x19, 8]
	ldr	w1, [x0, 12292]
	ubfx	x3, x1, 2, 1
	str	w3, [x19, 12]
	ldr	w1, [x0, 12292]
	ubfx	x1, x1, 6, 1
	str	w1, [x19]
	ldr	w1, [x0, 12292]
	ubfx	x1, x1, 1, 1
	str	w1, [x19, 4]
	ldr	w2, [x0, 12292]
	ubfx	x1, x2, 3, 1
	str	w1, [x19, 16]
	orr	w1, w3, w1
	cbz	w1, .L31
.L25:
	ldr	w2, [x0, 14404]
	ldr	w1, [x0, 14408]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 48]
	ldr	w2, [x0, 14412]
	ldr	w1, [x0, 14416]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 52]
	ldr	w2, [x0, 14420]
	ldr	w1, [x0, 14424]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 56]
	ldr	w2, [x0, 14428]
	ldr	w1, [x0, 14432]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 60]
	ldr	w2, [x0, 14436]
	ldr	w1, [x0, 14440]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 64]
	ldr	w2, [x0, 14444]
	ldr	w1, [x0, 14448]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 68]
	ldr	w2, [x0, 14452]
	ldr	w1, [x0, 14456]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 72]
	ldr	w2, [x0, 14460]
	ldr	w1, [x0, 14464]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 76]
	ldr	w2, [x0, 14468]
	ldr	w1, [x0, 14472]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 80]
	ldr	w2, [x0, 14476]
	ldr	w1, [x0, 14480]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 84]
	ldr	w2, [x0, 14484]
	ldr	w1, [x0, 14488]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 88]
	ldr	w2, [x0, 14492]
	ldr	w1, [x0, 14496]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 92]
	ldr	w2, [x0, 14500]
	ldr	w1, [x0, 14504]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 96]
	ldr	w2, [x0, 14508]
	ldr	w1, [x0, 14512]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 100]
	ldr	w2, [x0, 14516]
	ldr	w1, [x0, 14520]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 104]
	ldr	w2, [x0, 14524]
	ldr	w1, [x0, 14528]
	ubfx	x2, x2, 0, 29
	and	w1, w1, 127
	sub	w1, w2, w1
	str	w1, [x19, 108]
	ldr	w1, [x0, 14408]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 112]
	ldr	w1, [x0, 14416]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 116]
	ldr	w1, [x0, 14424]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 120]
	ldr	w1, [x0, 14432]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 124]
	ldr	w1, [x0, 14440]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 128]
	ldr	w1, [x0, 14448]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 132]
	ldr	w1, [x0, 14456]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 136]
	ldr	w1, [x0, 14464]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 140]
	ldr	w1, [x0, 14472]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 144]
	ldr	w1, [x0, 14480]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 148]
	ldr	w1, [x0, 14488]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 152]
	ldr	w1, [x0, 14496]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 156]
	ldr	w1, [x0, 14504]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 160]
	ldr	w1, [x0, 14512]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 164]
	ldr	w1, [x0, 14520]
	ubfx	x1, x1, 31, 1
	str	w1, [x19, 168]
	ldr	w0, [x0, 14528]
	ubfx	x0, x0, 31, 1
	str	w0, [x19, 172]
.L23:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L31:
	ldr	w1, [x4, 8]
	cbz	w1, .L32
	ldr	w1, [x0, 14272]
	lsl	w1, w1, 3
	str	w1, [x19, 20]
	ldr	w2, [x0, 15044]
	ldr	w1, [x0, 15076]
	ubfx	x2, x2, 0, 19
	ubfx	x1, x1, 0, 17
	add	w1, w2, w1
.L27:
	lsr	w1, w1, 2
	str	w1, [x19, 28]
	ldr	w1, [x0, 14280]
	str	w1, [x19, 32]
	ldr	w1, [x0, 14284]
	str	w1, [x19, 36]
	ldr	w1, [x0, 12736]
	ubfx	x1, x1, 0, 25
	str	w1, [x19, 40]
	ldr	w1, [x0, 12740]
	ubfx	x1, x1, 0, 25
	str	w1, [x19, 44]
	b	.L25
	.p2align 3
.L32:
	ldr	w1, [x0, 14400]
	lsl	w1, w1, 3
	str	w1, [x19, 20]
	ldr	w1, [x0, 15048]
	ldr	w3, [x0, 15052]
	ldr	w2, [x0, 15080]
	ubfx	x4, x1, 0, 19
	ubfx	x1, x3, 0, 19
	ubfx	x2, x2, 0, 19
	add	w1, w4, w1
	add	w1, w1, w2
	b	.L27
	.size	DRV_VENC_HAL_V500R001_ReadReg, .-DRV_VENC_HAL_V500R001_ReadReg
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_CfgReg
	.type	DRV_VENC_HAL_V500R001_CfgReg, %function
DRV_VENC_HAL_V500R001_CfgReg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L33
	ldr	x24, .LC6
	mov	x2, 696
	ldr	x0, .LC7
	mov	x1, x21
	ldr	x19, [x21, 688]
	ldp	x23, x22, [x24]
	ldr	x3, [x0, 8]
	mov	x0, x22
	blr	x3
	ldr	w0, [x21, 8]
	add	x1, x22, 868
	ldr	x5, .LC8
	mov	x2, x1
	cbnz	w0, .L128
	add	x0, x5, 204
	add	x4, x5, 360
	mov	w3, 1
	b	.L39
	.p2align 3
.L37:
	ldr	w3, [x0], 4
.L39:
	str	w3, [x2], 4
	cmp	x4, x0
	bne	.L37
	add	x2, x22, 1028
	add	x0, x5, 364
	add	x4, x5, 520
	mov	w3, 1
	b	.L38
	.p2align 3
.L129:
	ldr	w3, [x0], 4
.L38:
	str	w3, [x2], 4
	cmp	x4, x0
	bne	.L129
	add	x4, x22, 696
	mov	w2, 4
	mov	w0, 7
	str	w2, [x4, 100]
	mov	w2, 32
	str	w2, [x4, 520]
	mov	w2, 9
	str	w2, [x4, 140]
	mov	w2, 11
	stp	wzr, w0, [x4, 124]
	stp	w0, w0, [x4, 132]
	str	w2, [x4, 144]
	mov	w0, 255
	mov	w2, 14
	str	w0, [x4, 168]
	stp	w0, w0, [x4, 160]
	str	w2, [x4, 148]
	mov	w0, 25
	mov	w2, 18
	str	w0, [x4, 156]
	stp	wzr, wzr, [x4, 108]
	stp	wzr, wzr, [x4, 116]
	str	w2, [x4, 152]
.L41:
	ldr	w0, [x21, 44]
	cbz	w0, .L45
	ldr	w0, [x21, 16]
	cmp	w0, 1919
	bls	.L46
	mov	w0, 3
	str	w0, [x22, 1220]
.L45:
	ldr	w0, [x21, 8]
	cbnz	w0, .L48
	ldr	w0, [x21, 12]
	cmp	w0, wzr
	cset	w2, eq
	cmp	w0, 3
	str	w2, [x4, 536]
	cset	w2, ne
	mov	w0, 5
	str	w2, [x4, 532]
	mov	w2, 7
	csel	w0, w0, w2, ne
	str	w0, [x4, 528]
.L50:
	ldr	w0, [x21, 16]
	ldr	w2, [x21, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	add	x0, x22, 1332
	ccmp	w2, wzr, 0, ls
	cset	w2, eq
	cbz	w2, .L51
	mov	w3, 28
	str	w3, [x21, 524]
	str	w3, [x21, 528]
	str	w3, [x21, 532]
	str	wzr, [x22, 796]
	str	wzr, [x21, 24]
	str	wzr, [x22, 4312]
	str	wzr, [x0, 1144]
	str	wzr, [x0, 2056]
	str	wzr, [x0, 2308]
	str	wzr, [x0, 2560]
	str	wzr, [x0, 2564]
	str	wzr, [x22, 4284]
.L51:
	ldr	w2, [x21, 680]
	mov	w8, 1
	str	w2, [x23, 280]
	mov	w2, 207
	str	w2, [x23]
	ldr	w2, [x0, 2192]
	str	w2, [x23, 16]
	mov	w2, 0
	ldr	w7, [x0, 2152]
	ldr	w6, [x0, 2156]
	ldr	w3, [x0, 2200]
	bfi	w2, w7, 31, 1
	bfi	w2, w6, 30, 1
	sub	w3, w3, #1
	bfi	w2, w3, 16, 9
	ldr	w3, [x0, 2204]
	sub	w3, w3, #1
	bfi	w2, w3, 0, 9
	str	w2, [x23, 20]
	ldr	w2, [x22, 4468]
	str	w2, [x23, 24]
	mov	w2, 0
	ldr	w6, [x22, 4464]
	ldr	w3, [x22, 4460]
	bfi	w2, w6, 21, 1
	mov	w6, 3
	bfi	w2, w3, 19, 2
	ldr	w3, [x22, 4312]
	orr	w2, w2, 458752
	bfi	w2, w3, 2, 1
	ldr	w3, [x22, 4340]
	bfi	w2, w3, 23, 1
	ldr	w3, [x22, 4316]
	bfi	w2, w3, 3, 1
	ldr	w3, [x22, 4320]
	bfi	w2, w3, 1, 1
	ldr	w3, [x22, 4324]
	bfi	w2, w3, 0, 1
	mov	w3, 4
	str	w2, [x23, 52]
	mov	w2, 0
	bfi	w2, w3, 13, 3
	bfi	w2, w3, 10, 3
	ldr	w7, [x22, 4368]
	bfi	w2, w6, 7, 3
	ldr	w6, [x22, 4372]
	bfi	w2, w8, 5, 2
	bfi	w2, w3, 2, 3
	mov	w3, 0
	bfi	w3, w7, 4, 4
	bfi	w2, w8, 0, 2
	bfi	w3, w6, 0, 4
	str	w3, [x23, 56]
	str	w2, [x23, 68]
	mov	w3, 16
	mov	w2, 32
	mov	w7, 0
	ldr	w6, [x21, 8]
	cmp	w6, wzr
	csel	w6, w2, w3, ne
	ldp	w2, w3, [x21, 16]
	sub	w2, w2, #1
	sub	w3, w3, #1
	add	w2, w2, w6
	add	w3, w3, w6
	udiv	w2, w2, w6
	udiv	w3, w3, w6
	mul	w2, w2, w3
	ldr	w3, [x21, 520]
	udiv	w2, w3, w2
	bfi	w7, w2, 0, 20
	str	w7, [x23, 588]
	ldr	w3, [x0, 2612]
	mov	w2, 0
	bfi	w2, w3, 0, 4
	str	w2, [x23, 592]
	ldr	w3, [x21, 8]
	ldr	w10, [x21, 44]
	cmp	w3, 2
	ldr	w2, [x0, 2656]
	ldr	w9, [x21, 60]
	ldr	w6, [x21, 516]
	lsl	w2, w2, 31
	ldr	w12, [x22, 1228]
	ldr	w11, [x22, 1232]
	ldr	x7, [x24]
	beq	.L130
	and	w8, w2, -201326593
	cmp	w3, wzr
	orr	w2, w2, 201326592
	csel	w2, w2, w8, ne
.L54:
	ldr	w8, [x0, 2360]
	cmp	w6, wzr
	bfi	w2, w8, 30, 1
	ldr	w8, [x0, 2344]
	bfi	w2, w12, 18, 2
	bfi	w2, w8, 21, 1
	ldr	w8, [x0, 2348]
	bfi	w2, w8, 17, 1
	cset	w8, eq
	bfi	w2, w6, 16, 1
	ldr	w6, [x22, 1332]
	bfi	w2, w11, 12, 1
	cmp	w3, 2
	bfi	w2, w8, 10, 2
	ldr	w3, [x0, 2328]
	bfi	w2, w6, 9, 1
	mov	w8, 0
	bfi	w2, w3, 8, 1
	ldr	w3, [x0, 2380]
	bfi	w2, w3, 7, 1
	ldr	w3, [x0, 2384]
	bfi	w2, w3, 6, 1
	cset	w3, ne
	bfi	w2, w10, 5, 1
	cmp	w9, wzr
	bfi	w2, w3, 2, 2
	cset	w3, ne
	and	w2, w2, -32769
	bfi	w2, w3, 4, 1
	ldr	w3, [x0, 2180]
	orr	w2, w2, 2
	bfi	w2, w3, 0, 1
	str	w2, [x7, 28]
	mov	w3, 0
	mov	w2, 0
	ldr	w6, [x0, 2552]
	bfi	w3, w6, 16, 9
	ldr	w6, [x0, 2556]
	bfi	w3, w6, 0, 9
	str	w3, [x19]
	mov	w6, 0
	ldr	w3, [x21, 24]
	ldr	w9, [x21, 32]
	ubfiz	w3, w3, 17, 1
	orr	w3, w3, 65536
	bfi	w3, w9, 0, 16
	str	w3, [x19, 8]
	ldr	w3, [x21, 524]
	bfi	w2, w3, 10, 6
	ldr	w3, [x0, 2208]
	bfi	w2, w3, 5, 5
	ldr	w3, [x0, 2212]
	bfi	w2, w3, 0, 5
	ldr	w3, [x0, 1144]
	bfi	w2, w3, 18, 1
	ldr	w3, [x0, 1128]
	bfi	w2, w3, 19, 1
	str	w2, [x19, 12]
	ldr	w2, [x0, 2368]
	bfi	w6, w2, 8, 2
	ldr	w2, [x0, 2372]
	bfi	w6, w2, 4, 4
	ldr	w2, [x0, 2376]
	bfi	w6, w2, 0, 4
	str	w6, [x19, 16]
	ldr	w2, [x21, 20]
	sub	w2, w2, #1
	bfi	w8, w2, 16, 13
	ldr	w2, [x21, 16]
	sub	w2, w2, #1
	bfi	w8, w2, 0, 13
	str	w8, [x19, 4]
	ldr	w2, [x0, 2764]
	cmp	w2, 1
	beq	.L131
	ldr	w3, [x0, 2388]
	mov	w2, 0
	bfi	w2, w3, 0, 2
.L57:
	str	w2, [x19, 20]
	mov	w2, 0
	mov	w6, 0
	mov	w3, 0
	ldr	w8, [x0, 2396]
	mov	w12, 0
	mov	w9, 0
	mov	w10, 0
	and	w8, w8, 1
	str	w8, [x19, 24]
	mov	w14, 2
	mov	w11, 0
	ldr	w8, [x0, 2300]
	mov	w13, 0
	bfi	w2, w8, 12, 4
	ldr	w8, [x0, 2304]
	bfi	w2, w8, 8, 4
	ldr	w8, [x0, 2316]
	bfi	w2, w8, 4, 1
	ldr	w8, [x4, 528]
	bfi	w2, w8, 0, 3
	ldr	w8, [x0, 2320]
	bfi	w2, w8, 5, 1
	str	w2, [x19, 28]
	mov	w8, 0
	ldr	w2, [x0, 2268]
	bfi	w6, w2, 12, 1
	ldr	w2, [x0, 2276]
	bfi	w6, w2, 4, 2
	mov	w2, 0
	orr	w6, w6, 3
	str	w6, [x19, 32]
	ldr	w6, [x0, 2592]
	bfi	w3, w6, 4, 1
	ldr	w6, [x0, 2308]
	bfi	w3, w6, 2, 1
	ldr	w6, [x0, 2312]
	bfi	w3, w6, 3, 1
	ldr	w6, [x0, 2560]
	bfi	w3, w6, 1, 1
	ldr	w6, [x0, 2564]
	bfi	w3, w6, 0, 1
	str	w3, [x19, 36]
	mov	w6, 0
	ldr	w3, [x0, 2568]
	bfi	w12, w3, 16, 16
	ldr	w3, [x0, 2572]
	bfi	w12, w3, 0, 16
	str	w12, [x19, 40]
	mov	w3, 0
	ldr	w12, [x0, 2576]
	bfi	w9, w12, 24, 8
	ldr	w12, [x0, 2580]
	bfi	w9, w12, 16, 8
	ldr	w12, [x0, 2584]
	bfi	w9, w12, 8, 8
	ldr	w12, [x0, 2588]
	bfi	w9, w12, 0, 8
	str	w9, [x19, 44]
	ldr	w9, [x4, 96]
	bfi	w10, w9, 1, 1
	ldr	w9, [x22, 4300]
	bfi	w10, w9, 16, 8
	ldr	w9, [x22, 4296]
	bfi	w10, w9, 24, 8
	str	w10, [x19, 48]
	ldr	w9, [x22, 696]
	bfi	w8, w9, 2, 1
	ldr	w9, [x4, 4]
	bfi	w8, w9, 1, 1
	ldr	w9, [x0, 4]
	bfi	w8, w9, 0, 1
	ldr	w9, [x0, 2596]
	bfi	w8, w9, 3, 1
	ldr	w9, [x0, 2600]
	bfi	w8, w9, 4, 1
	stp	w8, w14, [x19, 52]
	ldr	w8, [x0, 1112]
	bfi	w2, w8, 0, 1
	ldr	w8, [x0, 1116]
	bfi	w2, w8, 1, 1
	ldr	w8, [x4, 92]
	bfi	w2, w8, 2, 1
	ldr	w8, [x0, 1140]
	bfi	w2, w8, 4, 1
	ldr	w8, [x0, 1108]
	bfi	w2, w8, 9, 1
	ldr	w8, [x4, 88]
	bfi	w2, w8, 8, 1
	ldr	w8, [x0, 1160]
	bfi	w2, w8, 3, 1
	ldr	w8, [x0, 1216]
	bfi	w2, w8, 15, 1
	ldr	w8, [x0, 1100]
	bfi	w2, w8, 14, 1
	ldr	w8, [x0, 1104]
	bfi	w2, w8, 13, 1
	ldr	w8, [x0, 1212]
	bfi	w2, w8, 12, 1
	ldr	w8, [x0, 1208]
	bfi	w2, w8, 11, 1
	ldr	w8, [x0, 1204]
	bfi	w2, w8, 10, 1
	ldr	w8, [x0, 1148]
	bfi	w2, w8, 18, 1
	str	w2, [x19, 60]
	ldr	w2, [x22, 4284]
	bfi	w11, w2, 8, 1
	ldr	w2, [x22, 4288]
	bfi	w11, w2, 0, 8
	str	w11, [x19, 64]
	ldr	w2, [x22, 4292]
	bfi	w13, w2, 0, 1
	str	w13, [x19, 68]
	ldr	w2, [x22, 4456]
	bfi	w6, w2, 0, 1
	ldr	w2, [x22, 4452]
	bfi	w6, w2, 1, 1
	ldr	w2, [x22, 4448]
	bfi	w6, w2, 2, 1
	ldr	w2, [x22, 4444]
	bfi	w6, w2, 3, 1
	ldr	w2, [x22, 4440]
	bfi	w6, w2, 4, 1
	ldr	w2, [x22, 4436]
	bfi	w6, w2, 5, 1
	ldr	w2, [x22, 4432]
	bfi	w6, w2, 6, 1
	ldr	w2, [x22, 4392]
	bfi	w6, w2, 7, 1
	str	w6, [x19, 72]
	ldr	w2, [x22, 4428]
	bfi	w3, w2, 0, 1
	ldr	w2, [x22, 4424]
	bfi	w3, w2, 1, 1
	ldr	w2, [x22, 4420]
	bfi	w3, w2, 2, 1
	ldr	w2, [x22, 4416]
	bfi	w3, w2, 3, 1
	ldr	w2, [x22, 4384]
	bfi	w3, w2, 4, 1
	ldr	w2, [x22, 4388]
	bfi	w3, w2, 5, 1
	ldr	w2, [x22, 4412]
	bfi	w3, w2, 6, 1
	ldr	w2, [x22, 4408]
	bfi	w3, w2, 7, 1
	ldr	w2, [x22, 4396]
	bfi	w3, w2, 8, 1
	ldr	w2, [x22, 4404]
	bfi	w3, w2, 9, 1
	ldr	w2, [x22, 4400]
	bfi	w3, w2, 10, 1
	str	w3, [x19, 76]
	ldr	w2, [x21, 8]
	ldr	w3, [x21, 60]
	cmp	w2, w14
	ldr	x6, [x21, 688]
	beq	.L132
	cbnz	w2, .L59
	mov	w2, 15
	mov	w28, 0
	bfi	w28, w2, 16, 6
	mov	w2, 31
	bfi	w28, w2, 0, 7
.L59:
	cbz	w3, .L60
	str	w28, [x6, 80]
.L61:
	mov	w3, 1
	mov	w2, 0
	bfi	w2, w3, 16, 6
	mov	w10, 0
	bfi	w2, w3, 0, 7
	str	w2, [x23, 128]
	mov	w2, 43691
	mov	w9, 0
	ldr	w3, [x21, 148]
	movk	w2, 0xaaaa, lsl 16
	mov	w8, 0
	mov	w6, 0
	add	x3, x21, x3, lsl 2
	ldr	w3, [x3, 136]
	str	w3, [x19, 88]
	ldr	w3, [x21, 148]
	add	w3, w3, 2
	umull	x11, w3, w2
	lsr	x11, x11, 32
	lsr	w11, w11, 1
	lsl	w12, w11, 2
	sub	w11, w12, w11
	sub	w3, w3, w11
	add	x3, x21, x3, lsl 2
	ldr	w3, [x3, 136]
	str	w3, [x19, 92]
	ldr	w3, [x21, 148]
	add	w3, w3, 1
	umull	x2, w3, w2
	lsr	x2, x2, 32
	lsr	w2, w2, 1
	lsl	w11, w2, 2
	sub	w2, w11, w2
	sub	w2, w3, w2
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 136]
	str	w2, [x19, 96]
	ldr	w2, [x21, 176]
	str	w2, [x19, 100]
	ldr	w2, [x21, 72]
	str	w2, [x19, 104]
	ldr	w2, [x21, 76]
	str	w2, [x19, 108]
	ldr	w2, [x21, 80]
	str	w2, [x19, 112]
	ldr	w2, [x21, 84]
	bfi	w10, w2, 16, 16
	ldr	w2, [x21, 88]
	bfi	w10, w2, 0, 16
	str	w10, [x19, 124]
	ldr	w2, [x21, 116]
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 92]
	str	w2, [x19, 128]
	ldr	w2, [x21, 116]
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 100]
	str	w2, [x19, 132]
	ldr	w2, [x21, 108]
	bfi	w9, w2, 0, 16
	ldr	w2, [x21, 112]
	bfi	w9, w2, 16, 16
	str	w9, [x19, 136]
	ldr	w2, [x21, 116]
	cmp	w2, wzr
	cset	x2, eq
	add	x2, x2, 20
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 12]
	str	w2, [x19, 152]
	ldr	w2, [x21, 116]
	cmp	w2, wzr
	cset	x2, eq
	add	x2, x2, 24
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 4]
	str	w2, [x19, 156]
	ldr	w2, [x21, 108]
	bfi	w8, w2, 16, 16
	ldr	w2, [x21, 112]
	bfi	w8, w2, 0, 16
	str	w8, [x19, 160]
	ldr	w2, [x21, 116]
	cmp	w2, wzr
	cset	x2, eq
	add	x2, x2, 32
	ldr	w2, [x21, x2, lsl 2]
	str	w2, [x19, 176]
	ldr	w2, [x21, 116]
	add	x2, x2, 32
	ldr	w2, [x21, x2, lsl 2]
	str	w2, [x19, 208]
	ldr	w2, [x21, 116]
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 120]
	str	w2, [x19, 216]
	ldr	w2, [x21, 116]
	cmp	w2, wzr
	cset	x2, eq
	add	x2, x2, 28
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 8]
	str	w2, [x19, 220]
	ldr	w2, [x21, 180]
	str	w2, [x19, 224]
	ldr	w2, [x21, 312]
	str	w2, [x19, 228]
	ldr	w2, [x21, 308]
	str	w2, [x19, 232]
	ldr	w2, [x21, 64]
	ldr	w3, [x22, 4120]
	ldr	x8, [x21, 688]
	bfi	w6, w3, 14, 1
	cbnz	w2, .L62
	ldr	w2, [x21, 68]
	mov	w3, 0
	cmp	w2, wzr
	cset	w2, eq
	bfi	w6, w2, 16, 8
.L63:
	ldr	w2, [x21, 60]
	bfi	w6, w3, 6, 4
	and	w6, w6, -64
	cbnz	w2, .L133
.L64:
	str	w6, [x7, 284]
.L65:
	str	wzr, [x19, 256]
	mov	w2, 0
	ldr	w6, [x4, 8]
	ldr	w3, [x0, 16]
	bfi	w2, w6, 16, 5
	bfi	w2, w3, 0, 8
	ldr	w3, [x0, 392]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 332]
	mov	w2, 0
	ldr	w6, [x0, 656]
	ldr	w3, [x0, 660]
	bfi	w2, w6, 0, 3
	bfi	w2, w3, 3, 7
	ldr	w3, [x0, 664]
	bfi	w2, w3, 10, 3
	ldr	w3, [x0, 672]
	bfi	w2, w3, 18, 4
	ldr	w3, [x0, 680]
	bfi	w2, w3, 26, 4
	str	w2, [x19, 336]
	mov	w2, 0
	ldr	w6, [x0, 488]
	ldr	w3, [x0, 492]
	bfi	w2, w6, 0, 1
	bfi	w2, w3, 1, 3
	ldr	w3, [x0, 504]
	bfi	w2, w3, 15, 6
	ldr	w3, [x0, 508]
	bfi	w2, w3, 21, 5
	str	w2, [x19, 340]
	mov	w2, 0
	ldr	w6, [x0, 28]
	ldr	w3, [x4, 12]
	bfi	w2, w6, 16, 5
	bfi	w2, w3, 0, 8
	ldr	w3, [x0, 400]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 344]
	mov	w2, 0
	ldr	w6, [x0, 684]
	ldr	w3, [x0, 688]
	bfi	w2, w6, 0, 3
	bfi	w2, w3, 3, 7
	ldr	w3, [x0, 692]
	bfi	w2, w3, 10, 3
	ldr	w3, [x0, 700]
	bfi	w2, w3, 18, 4
	ldr	w3, [x0, 708]
	bfi	w2, w3, 26, 4
	str	w2, [x19, 348]
	mov	w2, 0
	ldr	w6, [x0, 512]
	ldr	w3, [x0, 516]
	bfi	w2, w6, 0, 1
	bfi	w2, w3, 1, 3
	ldr	w3, [x0, 528]
	bfi	w2, w3, 15, 6
	ldr	w3, [x0, 532]
	bfi	w2, w3, 21, 5
	str	w2, [x19, 352]
	mov	w2, 0
	ldr	w3, [x4, 24]
	bfi	w2, w3, 16, 5
	ldr	w3, [x4, 28]
	bfi	w2, w3, 0, 8
	ldr	w3, [x0, 416]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 356]
	mov	w2, 0
	ldr	w6, [x0, 736]
	ldr	w3, [x0, 740]
	bfi	w2, w6, 0, 3
	bfi	w2, w3, 3, 7
	ldr	w3, [x0, 744]
	bfi	w2, w3, 10, 3
	ldr	w3, [x0, 752]
	bfi	w2, w3, 18, 4
	ldr	w3, [x0, 760]
	bfi	w2, w3, 26, 4
	str	w2, [x19, 360]
	mov	w2, 0
	ldr	w6, [x0, 560]
	ldr	w3, [x0, 564]
	bfi	w2, w6, 0, 1
	bfi	w2, w3, 1, 3
	ldr	w3, [x0, 576]
	bfi	w2, w3, 15, 6
	ldr	w3, [x0, 580]
	bfi	w2, w3, 21, 5
	str	w2, [x19, 364]
	mov	w2, 0
	ldp	w6, w3, [x4, 60]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 16, 5
	ldr	w3, [x0, 424]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 368]
	mov	w2, 0
	ldr	w6, [x0, 308]
	ldr	w3, [x0, 312]
	bfi	w2, w6, 0, 3
	bfi	w2, w3, 3, 7
	ldr	w3, [x0, 316]
	bfi	w2, w3, 10, 3
	ldr	w3, [x0, 324]
	bfi	w2, w3, 18, 4
	ldr	w3, [x0, 332]
	bfi	w2, w3, 26, 4
	str	w2, [x19, 372]
	mov	w2, 0
	ldr	w6, [x0, 584]
	ldr	w3, [x0, 588]
	bfi	w2, w6, 0, 1
	bfi	w2, w3, 1, 3
	ldr	w3, [x0, 600]
	bfi	w2, w3, 15, 6
	ldr	w3, [x0, 604]
	bfi	w2, w3, 21, 5
	str	w2, [x19, 376]
	mov	w2, 0
	ldp	w6, w3, [x4, 16]
	bfi	w2, w6, 16, 5
	bfi	w2, w3, 0, 8
	ldr	w3, [x0, 408]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 380]
	ldr	w6, [x4, 68]
	mov	w2, 0
	ldr	w3, [x0, 712]
	bfi	w2, w6, 0, 3
	bfi	w2, w3, 3, 7
	ldr	w3, [x0, 716]
	bfi	w2, w3, 10, 3
	ldr	w3, [x0, 724]
	bfi	w2, w3, 18, 4
	ldr	w3, [x0, 732]
	bfi	w2, w3, 26, 4
	str	w2, [x19, 384]
	mov	w2, 0
	ldr	w6, [x0, 536]
	ldr	w3, [x0, 540]
	bfi	w2, w6, 0, 1
	bfi	w2, w3, 1, 3
	ldr	w3, [x0, 552]
	bfi	w2, w3, 15, 6
	ldr	w3, [x0, 556]
	bfi	w2, w3, 21, 5
	str	w2, [x19, 388]
	mov	w2, 0
	ldr	w6, [x0, 464]
	ldr	w3, [x0, 468]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 16, 5
	ldr	w3, [x0, 432]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 392]
	mov	w2, 0
	ldr	w6, [x0, 336]
	ldr	w3, [x0, 340]
	bfi	w2, w6, 0, 3
	bfi	w2, w3, 3, 7
	ldr	w3, [x0, 344]
	bfi	w2, w3, 10, 3
	ldr	w3, [x0, 352]
	bfi	w2, w3, 18, 4
	ldr	w3, [x0, 360]
	bfi	w2, w3, 26, 4
	str	w2, [x19, 396]
	mov	w2, 0
	ldr	w6, [x0, 608]
	ldr	w3, [x0, 612]
	bfi	w2, w6, 0, 1
	bfi	w2, w3, 1, 3
	ldr	w3, [x0, 624]
	bfi	w2, w3, 15, 6
	ldr	w3, [x0, 628]
	bfi	w2, w3, 21, 5
	str	w2, [x19, 400]
	mov	w2, 0
	ldr	w6, [x0, 480]
	ldr	w3, [x0, 484]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 16, 5
	ldr	w3, [x0, 440]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 404]
	mov	w2, 0
	ldr	w6, [x0, 364]
	ldr	w3, [x0, 368]
	bfi	w2, w6, 0, 3
	bfi	w2, w3, 3, 7
	ldr	w3, [x0, 372]
	bfi	w2, w3, 10, 3
	ldr	w3, [x0, 380]
	bfi	w2, w3, 18, 4
	ldr	w3, [x0, 388]
	bfi	w2, w3, 26, 4
	str	w2, [x19, 408]
	mov	w2, 0
	ldr	w6, [x0, 632]
	ldr	w3, [x0, 636]
	bfi	w2, w6, 0, 1
	bfi	w2, w3, 1, 3
	ldr	w3, [x0, 648]
	bfi	w2, w3, 15, 6
	ldr	w3, [x0, 652]
	bfi	w2, w3, 21, 5
	str	w2, [x19, 412]
	mov	w2, 0
	ldp	w3, w6, [x0, 56]
	bfi	w2, w6, 0, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 52]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 72]
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 68]
	bfi	w2, w3, 20, 4
	ldr	w3, [x4, 32]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 416]
	mov	w2, 0
	ldp	w3, w6, [x0, 136]
	bfi	w2, w6, 0, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x4, 44]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 156]
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 152]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 148]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 420]
	mov	w2, 0
	ldp	w3, w6, [x0, 220]
	bfi	w2, w6, 0, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x4, 56]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 240]
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 236]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 232]
	bfi	w2, w3, 24, 4
	str	w2, [x19, 424]
	mov	w2, 0
	ldp	w6, w3, [x0, 80]
	bfi	w2, w6, 8, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 88]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 96]
	bfi	w2, w3, 24, 4
	ldr	w3, [x4, 36]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 100]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 428]
	mov	w2, 0
	ldr	w6, [x0, 164]
	ldr	w3, [x4, 48]
	bfi	w2, w6, 8, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 168]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 176]
	bfi	w2, w3, 24, 4
	ldr	w3, [x0, 180]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 184]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 432]
	mov	w2, 0
	ldp	w6, w3, [x0, 248]
	bfi	w2, w6, 8, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 256]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 264]
	bfi	w2, w3, 24, 4
	ldr	w3, [x0, 268]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 272]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 436]
	mov	w2, 0
	ldp	w6, w3, [x0, 108]
	bfi	w2, w6, 8, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 116]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 124]
	bfi	w2, w3, 24, 4
	ldr	w3, [x4, 40]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 128]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 440]
	mov	w2, 0
	ldr	w6, [x0, 192]
	ldr	w3, [x4, 52]
	bfi	w2, w6, 8, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 196]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 204]
	bfi	w2, w3, 24, 4
	ldr	w3, [x0, 208]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 212]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 444]
	ldr	w6, [x0, 280]
	mov	w2, 0
	ldr	w3, [x0, 284]
	bfi	w2, w6, 8, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 288]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 296]
	bfi	w2, w3, 24, 4
	ldr	w3, [x0, 300]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 304]
	bfi	w2, w3, 16, 4
	str	w2, [x19, 448]
	mov	w2, 0
	ldr	w6, [x0, 764]
	ldr	w3, [x0, 768]
	bfi	w2, w6, 0, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 772]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 776]
	bfi	w2, w3, 12, 4
	ldr	w3, [x0, 780]
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 784]
	bfi	w2, w3, 20, 4
	str	w2, [x19, 452]
	mov	w2, 0
	ldp	w6, w3, [x4, 72]
	bfi	w2, w6, 0, 12
	bfi	w2, w3, 12, 12
	ldr	w3, [x0, 788]
	bfi	w2, w3, 24, 8
	str	w2, [x19, 456]
	mov	w2, 0
	ldr	w6, [x0, 792]
	ldr	w3, [x0, 796]
	bfi	w2, w6, 0, 12
	bfi	w2, w3, 12, 12
	ldr	w3, [x0, 800]
	bfi	w2, w3, 24, 8
	str	w2, [x19, 460]
	mov	w2, 0
	ldr	w6, [x4, 80]
	ldr	w3, [x0, 804]
	bfi	w2, w6, 0, 12
	bfi	w2, w3, 12, 12
	ldr	w3, [x0, 808]
	bfi	w2, w3, 24, 8
	str	w2, [x19, 464]
	mov	w2, 0
	ldr	w6, [x0, 812]
	ldr	w3, [x0, 816]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 820]
	bfi	w2, w3, 16, 8
	str	w2, [x19, 468]
	mov	w2, 0
	ldr	w6, [x22, 4164]
	ldr	w3, [x22, 4168]
	bfi	w2, w6, 14, 1
	bfi	w2, w3, 15, 1
	ldr	w3, [x21, 44]
	bfi	w2, w3, 28, 1
	ldr	w3, [x4, 524]
	bfi	w2, w3, 20, 8
	str	w2, [x19, 480]
	mov	w2, 0
	ldr	w6, [x22, 4184]
	ldr	w3, [x22, 4180]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 8, 8
	ldr	w3, [x22, 4176]
	bfi	w2, w3, 16, 8
	ldr	w3, [x22, 4172]
	bfi	w2, w3, 24, 8
	str	w2, [x19, 484]
	mov	w2, 0
	ldr	w3, [x0, 1280]
	bfi	w2, w3, 0, 1
	str	w2, [x19, 488]
	mov	w2, 0
	ldr	w3, [x0, 1284]
	bfi	w2, w3, 0, 16
	str	w2, [x19, 492]
	mov	w2, 0
	ldr	w3, [x0, 1288]
	bfi	w2, w3, 0, 16
	str	w2, [x19, 496]
	mov	w2, 0
	ldr	w3, [x0, 1292]
	bfi	w2, w3, 0, 16
	str	w2, [x19, 500]
	mov	w2, 0
	ldr	w6, [x0, 1340]
	ldr	w3, [x0, 1344]
	bfi	w2, w6, 16, 1
	bfi	w2, w3, 0, 16
	str	w2, [x19, 504]
	mov	w2, 0
	ldr	w6, [x0, 1296]
	ldr	w3, [x0, 1300]
	bfi	w2, w6, 18, 9
	bfi	w2, w3, 9, 9
	ldr	w3, [x0, 1304]
	bfi	w2, w3, 0, 9
	str	w2, [x19, 508]
	mov	w2, 0
	ldr	w6, [x0, 1308]
	ldr	w3, [x0, 1312]
	bfi	w2, w6, 16, 8
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 1316]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 512]
	mov	w2, 0
	ldr	w6, [x0, 1320]
	ldr	w3, [x0, 1324]
	bfi	w2, w6, 8, 4
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 1328]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 1336]
	bfi	w2, w3, 12, 8
	ldr	w3, [x0, 1332]
	bfi	w2, w3, 20, 8
	str	w2, [x19, 516]
	ldr	w6, [x0, 2040]
	mov	w2, 0
	ldr	w3, [x0, 2036]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 2032]
	bfi	w2, w3, 16, 8
	ldr	w3, [x0, 2028]
	bfi	w2, w3, 24, 8
	str	w2, [x19, 524]
	mov	w2, 0
	ldr	w6, [x0, 1348]
	ldr	w3, [x0, 1352]
	bfi	w2, w6, 24, 8
	bfi	w2, w3, 16, 8
	ldr	w3, [x0, 1356]
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 1360]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 528]
	mov	w2, 0
	ldr	w6, [x0, 1412]
	ldr	w3, [x0, 2068]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 17, 1
	str	w2, [x19, 532]
	mov	w2, 0
	ldr	w6, [x0, 1424]
	ldr	w3, [x0, 1428]
	bfi	w2, w6, 0, 16
	bfi	w2, w3, 16, 16
	str	w2, [x19, 536]
	mov	w2, 0
	ldr	w6, [x4, 492]
	ldr	w3, [x4, 496]
	bfi	w2, w6, 22, 9
	bfi	w2, w3, 17, 5
	ldr	w3, [x4, 500]
	bfi	w2, w3, 9, 8
	ldr	w3, [x4, 520]
	bfi	w2, w3, 0, 9
	str	w2, [x19, 540]
	mov	w2, 0
	ldr	w6, [x4, 516]
	ldr	w3, [x0, 1952]
	bfi	w2, w6, 8, 14
	bfi	w2, w3, 0, 8
	str	w2, [x19, 544]
	mov	w2, 0
	ldr	w6, [x4, 504]
	ldr	w3, [x4, 508]
	bfi	w2, w6, 16, 8
	bfi	w2, w3, 8, 8
	ldr	w3, [x4, 512]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 548]
	mov	w2, 0
	ldr	w6, [x0, 1960]
	ldr	w3, [x0, 1964]
	bfi	w2, w6, 18, 1
	bfi	w2, w3, 12, 2
	ldr	w3, [x0, 1972]
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 1976]
	bfi	w2, w3, 0, 4
	str	w2, [x19, 552]
	ldr	w6, [x0, 1980]
	mov	w2, 0
	ldr	w3, [x0, 1984]
	bfi	w2, w6, 0, 10
	bfi	w2, w3, 16, 9
	str	w2, [x19, 556]
	mov	w2, 0
	ldr	w6, [x0, 1988]
	ldr	w3, [x0, 1992]
	bfi	w2, w6, 0, 10
	bfi	w2, w3, 16, 9
	str	w2, [x19, 560]
	mov	w2, 0
	ldr	w6, [x0, 1996]
	ldr	w3, [x0, 2000]
	bfi	w2, w6, 0, 10
	bfi	w2, w3, 16, 9
	str	w2, [x19, 564]
	mov	w2, 0
	ldr	w6, [x0, 2004]
	ldr	w3, [x0, 2008]
	bfi	w2, w6, 0, 10
	bfi	w2, w3, 16, 9
	str	w2, [x19, 568]
	mov	w2, 0
	ldr	w3, [x0, 2012]
	bfi	w2, w3, 0, 16
	str	w2, [x19, 572]
	mov	w2, 0
	ldr	w6, [x0, 2044]
	ldr	w3, [x0, 2048]
	bfi	w2, w6, 0, 13
	bfi	w2, w3, 13, 1
	str	w2, [x19, 576]
	mov	w2, 0
	ldr	w3, [x0, 2052]
	bfi	w2, w3, 0, 18
	str	w2, [x19, 580]
	mov	w2, 0
	ldr	w3, [x0, 2056]
	bfi	w2, w3, 0, 18
	str	w2, [x19, 584]
	mov	w2, 0
	ldr	w6, [x0, 2080]
	ldr	w3, [x0, 2084]
	bfi	w2, w6, 16, 7
	bfi	w2, w3, 23, 7
	str	w2, [x19, 588]
	mov	w2, 0
	ldr	w6, [x0, 2064]
	ldr	w3, [x0, 2088]
	bfi	w2, w6, 12, 8
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 2092]
	bfi	w2, w3, 0, 8
	ldr	w3, [x0, 2096]
	bfi	w2, w3, 20, 8
	ldr	w3, [x0, 2100]
	bfi	w2, w3, 28, 4
	str	w2, [x19, 592]
	mov	w2, 0
	ldr	w6, [x0, 2072]
	ldr	w3, [x0, 2076]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 2060]
	bfi	w2, w3, 16, 8
	str	w2, [x19, 596]
	mov	w2, 0
	ldr	w6, [x0, 2104]
	ldr	w3, [x0, 2108]
	bfi	w2, w6, 0, 8
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 2112]
	bfi	w2, w3, 16, 16
	str	w2, [x19, 600]
	mov	w2, 0
	ldr	w6, [x0, 1364]
	ldr	w3, [x0, 1368]
	bfi	w2, w6, 24, 8
	bfi	w2, w3, 16, 8
	ldr	w3, [x0, 1372]
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 1376]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 604]
	mov	w2, 0
	ldr	w6, [x0, 1380]
	ldr	w3, [x0, 1384]
	bfi	w2, w6, 24, 8
	bfi	w2, w3, 16, 8
	ldr	w3, [x0, 1388]
	bfi	w2, w3, 8, 8
	ldr	w3, [x0, 1392]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 608]
	mov	w2, 0
	ldr	w6, [x0, 1396]
	ldr	w3, [x0, 1400]
	bfi	w2, w6, 28, 4
	bfi	w2, w3, 23, 5
	ldr	w3, [x0, 1404]
	bfi	w2, w3, 14, 9
	ldr	w3, [x0, 1408]
	bfi	w2, w3, 0, 14
	str	w2, [x19, 612]
	mov	w2, 0
	ldr	w6, [x21, 532]
	ldr	w3, [x0, 2216]
	bfi	w2, w6, 8, 6
	bfi	w2, w3, 16, 1
	ldr	w3, [x21, 528]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 624]
	ldr	w2, [x21, 8]
	ldr	w3, [x21, 20]
	cbnz	w2, .L66
	ldr	w2, [x21, 520]
	lsr	w3, w3, 4
	udiv	w3, w2, w3
	mov	w2, 0
	bfi	w2, w3, 6, 25
.L67:
	mov	w3, 2
	bfi	w2, w3, 0, 6
	str	w2, [x19, 628]
	mov	w2, 0
	ldr	w3, [x0, 988]
	bfi	w2, w3, 0, 16
	str	w2, [x19, 632]
	mov	w2, 0
	ldr	w6, [x0, 960]
	ldr	w3, [x0, 936]
	bfi	w2, w6, 8, 6
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 964]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 636]
	mov	w2, 0
	ldr	w6, [x0, 948]
	ldr	w3, [x0, 928]
	bfi	w2, w6, 8, 6
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 1264]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 640]
	mov	w2, 0
	ldr	w6, [x0, 948]
	ldr	w3, [x0, 932]
	bfi	w2, w6, 8, 6
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 1252]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 644]
	mov	w2, 0
	ldr	w6, [x0, 944]
	ldr	w3, [x0, 924]
	bfi	w2, w6, 8, 6
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 1260]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 648]
	mov	w2, 0
	ldr	w6, [x4, 104]
	ldr	w3, [x4, 84]
	bfi	w2, w6, 8, 6
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 1248]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 652]
	mov	w2, 0
	ldr	w6, [x0, 940]
	ldr	w3, [x0, 956]
	bfi	w2, w6, 16, 4
	bfi	w2, w3, 8, 6
	ldr	w3, [x0, 1256]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 656]
	mov	w2, 0
	ldr	w6, [x0, 968]
	ldr	w3, [x0, 972]
	bfi	w2, w6, 16, 4
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 976]
	bfi	w2, w3, 8, 6
	ldr	w3, [x0, 1268]
	bfi	w2, w3, 0, 6
	str	w2, [x19, 660]
	mov	w2, 0
	ldr	w3, [x4, 120]
	bfi	w2, w3, 24, 8
	ldr	w3, [x4, 116]
	bfi	w2, w3, 16, 8
	ldr	w3, [x4, 112]
	bfi	w2, w3, 8, 8
	ldr	w3, [x4, 108]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 664]
	mov	w2, 0
	ldp	w3, w6, [x4, 132]
	bfi	w2, w6, 24, 8
	bfi	w2, w3, 16, 8
	ldr	w3, [x4, 128]
	bfi	w2, w3, 8, 8
	ldr	w3, [x4, 124]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 668]
	mov	w2, 0
	ldp	w3, w6, [x4, 148]
	bfi	w2, w6, 24, 8
	bfi	w2, w3, 16, 8
	ldr	w3, [x4, 144]
	bfi	w2, w3, 8, 8
	ldr	w3, [x4, 140]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 672]
	mov	w2, 0
	ldp	w3, w6, [x4, 164]
	bfi	w2, w6, 24, 8
	bfi	w2, w3, 16, 8
	ldr	w3, [x4, 160]
	bfi	w2, w3, 8, 8
	ldr	w3, [x4, 156]
	bfi	w2, w3, 0, 8
	str	w2, [x19, 676]
	mov	w2, 0
	ldr	w6, [x0, 848]
	ldr	w3, [x0, 852]
	bfi	w2, w6, 0, 2
	bfi	w2, w3, 2, 2
	ldr	w3, [x0, 856]
	bfi	w2, w3, 4, 2
	ldr	w3, [x0, 860]
	bfi	w2, w3, 6, 2
	ldr	w3, [x0, 864]
	bfi	w2, w3, 8, 2
	ldr	w3, [x0, 868]
	bfi	w2, w3, 10, 2
	ldr	w3, [x0, 872]
	bfi	w2, w3, 12, 2
	ldr	w3, [x0, 876]
	bfi	w2, w3, 14, 2
	ldr	w3, [x0, 880]
	bfi	w2, w3, 16, 2
	ldr	w3, [x0, 884]
	bfi	w2, w3, 18, 2
	ldr	w3, [x0, 888]
	bfi	w2, w3, 20, 2
	ldr	w3, [x0, 892]
	bfi	w2, w3, 22, 2
	ldr	w3, [x0, 896]
	bfi	w2, w3, 24, 2
	ldr	w3, [x0, 900]
	bfi	w2, w3, 26, 2
	ldr	w3, [x0, 904]
	bfi	w2, w3, 28, 2
	ldr	w3, [x0, 908]
	bfi	w2, w3, 30, 2
	str	w2, [x19, 680]
	mov	w2, 0
	ldr	w3, [x0, 912]
	bfi	w2, w3, 0, 5
	str	w2, [x19, 684]
	mov	w2, 0
	ldr	w6, [x0, 980]
	ldr	w3, [x0, 984]
	bfi	w2, w6, 0, 4
	bfi	w2, w3, 4, 4
	str	w2, [x19, 688]
	ldr	w2, [x21, 8]
	cmp	w2, 2
	beq	.L134
	add	x2, x19, 692
	add	x5, x22, 1188
	.p2align 2
.L78:
	ldr	w3, [x1], 4
	bfi	w20, w3, 0, 20
	cmp	x1, x5
	str	w20, [x2], 4
	bne	.L78
.L77:
	ldr	w2, [x0, 1196]
	mov	w1, 0
	ldr	w3, [x0, 1200]
	bfi	w1, w2, 8, 2
	ldr	w2, [x0, 1008]
	bfi	w1, w3, 12, 1
	bfi	w1, w2, 0, 5
	str	w1, [x19, 1012]
	mov	w1, 0
	mov	w2, 0
	ldr	w3, [x0, 1004]
	bfi	w1, w3, 16, 4
	ldr	w3, [x0, 1184]
	bfi	w1, w3, 12, 4
	ldr	w3, [x0, 996]
	bfi	w1, w3, 9, 2
	ldr	w3, [x0, 1000]
	bfi	w1, w3, 8, 1
	ldr	w3, [x0, 992]
	bfi	w1, w3, 0, 6
	str	w1, [x19, 1016]
	ldr	w1, [x0, 1164]
	str	w1, [x19, 1020]
	ldr	w1, [x0, 1168]
	str	w1, [x19, 1024]
	ldr	w3, [x0, 1192]
	ldrh	w1, [x0, 1172]
	bfi	w1, w3, 21, 1
	ldr	w3, [x0, 1180]
	bfi	w1, w3, 18, 2
	ldr	w3, [x0, 1176]
	bfi	w1, w3, 16, 2
	str	w1, [x19, 1028]
	mov	w1, 0
	mov	w3, 0
	ldr	w5, [x22, 4308]
	bfi	w2, w5, 4, 2
	ldr	w5, [x0, 2324]
	bfi	w2, w5, 1, 1
	ldr	w5, [x22, 4328]
	bfi	w2, w5, 2, 1
	str	w2, [x19, 1040]
	ldr	w2, [x0, 2676]
	bfi	w1, w2, 16, 16
	ldr	w2, [x0, 2680]
	bfi	w1, w2, 0, 16
	str	w1, [x19, 1044]
	mov	w2, 0
	mov	w1, 0
	ldr	w5, [x22, 4332]
	bfi	w3, w5, 6, 6
	ldr	w5, [x22, 4336]
	bfi	w3, w5, 0, 6
	str	w3, [x19, 1048]
	ldr	w3, [x0, 2660]
	bfi	w2, w3, 31, 1
	ldr	w3, [x0, 2664]
	bfi	w2, w3, 0, 17
	str	w2, [x19, 1052]
	ldr	w3, [x0, 2668]
	ldr	w2, [x0, 2672]
	bfi	w1, w3, 16, 11
	bfi	w1, w2, 0, 10
	str	w1, [x19, 1056]
	ldr	w1, [x21, 544]
	cbz	w1, .L75
	ldr	w1, [x21, 516]
	cbnz	w1, .L75
	mov	w1, 15
.L79:
	str	w1, [x19, 1060]
	ldr	w1, [x21, 544]
	cbz	w1, .L80
	ldr	w1, [x21, 516]
	cbnz	w1, .L80
	mov	w1, 16
.L81:
	str	w1, [x19, 1064]
	mov	w3, 0
	mov	w1, 0
	mov	w2, 0
	ldr	w5, [x0, 2428]
	bfi	w3, w5, 0, 1
	str	w3, [x19, 1068]
	ldr	w3, [x0, 2436]
	bfi	w1, w3, 15, 1
	ldr	w3, [x0, 2440]
	bfi	w1, w3, 14, 1
	ldr	w3, [x0, 2444]
	bfi	w1, w3, 13, 1
	ldr	w3, [x0, 2448]
	bfi	w1, w3, 12, 1
	ldr	w3, [x0, 2452]
	bfi	w1, w3, 8, 4
	ldr	w3, [x0, 2456]
	bfi	w1, w3, 4, 4
	ldr	w3, [x0, 2460]
	bfi	w1, w3, 0, 4
	str	w1, [x19, 1072]
	mov	w1, 0
	mov	w3, 0
	ldr	w5, [x0, 2464]
	bfi	w2, w5, 0, 4
	str	w2, [x19, 1076]
	ldr	w2, [x0, 2476]
	bfi	w1, w2, 0, 8
	ldr	w2, [x0, 2472]
	bfi	w1, w2, 8, 8
	ldr	w2, [x0, 2468]
	bfi	w1, w2, 16, 8
	str	w1, [x19, 1080]
	mov	w2, 7
	mov	w1, -1
	ldr	w5, [x0, 2484]
	bfi	w3, w5, 0, 16
	add	x5, x19, 1024
	stp	w3, w1, [x5, 60]
	stp	w1, w2, [x5, 68]
	str	w1, [x19, 1100]
	mov	w1, 0
	str	w2, [x19, 1104]
	mov	w3, 0
	mov	w2, 0
	ldr	w5, [x0, 2548]
	bfi	w1, w5, 3, 1
	ldr	w5, [x0, 2544]
	bfi	w1, w5, 2, 1
	ldr	w5, [x0, 2540]
	bfi	w1, w5, 1, 1
	orr	w1, w1, 1
	str	w1, [x19, 1108]
	ldr	w1, [x22, 4124]
	str	w1, [x19, 1112]
	ldr	w1, [x22, 4128]
	str	w1, [x19, 1116]
	ldr	w1, [x22, 4132]
	str	w1, [x19, 1120]
	ldr	w1, [x22, 4136]
	str	w1, [x19, 1124]
	ldr	w1, [x22, 4140]
	str	w1, [x19, 1128]
	ldr	w1, [x22, 4144]
	str	w1, [x19, 1132]
	ldr	w1, [x0, 2764]
	bfi	w3, w1, 0, 1
	str	w3, [x19, 1136]
	mov	w1, 0
	mov	w3, 0
	ldr	w5, [x22, 4360]
	bfi	w2, w5, 0, 8
	ldr	w5, [x22, 4364]
	bfi	w2, w5, 8, 8
	str	w2, [x19, 1140]
	ldr	w2, [x0, 824]
	bfi	w1, w2, 0, 16
	ldr	w2, [x0, 828]
	bfi	w1, w2, 16, 16
	str	w1, [x19, 1144]
	mov	w1, 0
	mov	w2, 0
	ldr	w5, [x0, 840]
	bfi	w3, w5, 16, 16
	str	w3, [x19, 1148]
	ldr	w3, [x0, 832]
	bfi	w1, w3, 0, 16
	ldr	w3, [x0, 836]
	bfi	w1, w3, 16, 16
	str	w1, [x19, 1152]
	mov	w1, 0
	mov	w3, 513
	ldr	w5, [x0, 844]
	bfi	w2, w5, 0, 3
	str	w2, [x19, 1156]
	mov	w5, 9729
	ldr	w2, [x0, 2732]
	bfi	w1, w2, 8, 3
	ldr	w2, [x21, 516]
	cmp	w2, wzr
	mov	w2, 0
	csel	w3, w3, w5, eq
	mov	w5, 0
	bfi	w1, w3, 16, 16
	str	w1, [x19, 1172]
	mov	w1, 16
	ldr	w3, [x21, 616]
	bfi	w2, w3, 0, 5
	ldr	w3, [x21, 620]
	bfi	w2, w3, 16, 16
	str	w2, [x19, 1176]
	ldr	w2, [x21, 616]
	sub	w3, w1, w2
	ldr	w2, [x21, 656]
	lsl	w2, w2, w3
	bfi	w5, w2, 0, 16
	str	w5, [x19, 1180]
	mov	w2, 0
	ldr	w3, [x4, 628]
	bfi	w2, w3, 0, 5
	ldr	w3, [x4, 632]
	bfi	w2, w3, 16, 16
	str	w2, [x19, 1216]
	mov	w3, 0
	ldr	w2, [x4, 628]
	sub	w1, w1, w2
	ldr	w2, [x4, 624]
	lsl	w1, w2, w1
	bfi	w3, w1, 0, 16
	str	w3, [x19, 1220]
	ldr	w1, [x21, 8]
	cmp	w1, 2
	beq	.L135
.L84:
	cbnz	w1, .L90
	ldr	w1, [x21, 616]
	mov	w2, 0
	sub	w3, w1, #1
	bfi	w2, w3, 16, 7
	lsr	w3, w1, 8
	sub	w3, w3, #1
	lsr	w1, w1, 16
	sub	w1, w1, #1
	bfi	w2, w3, 8, 6
	bfi	w2, w1, 0, 6
	str	w2, [x19, 1288]
	ldr	w1, [x21, 584]
	str	w1, [x19, 1256]
	ldr	w1, [x21, 588]
	str	w1, [x19, 1260]
	ldr	w1, [x21, 592]
	str	w1, [x19, 1264]
	ldr	w1, [x21, 596]
	str	w1, [x19, 1268]
	ldr	w1, [x21, 600]
	str	w1, [x19, 1272]
	ldr	w1, [x21, 604]
	str	w1, [x19, 1276]
	ldr	w1, [x21, 608]
	str	w1, [x19, 1280]
	ldr	w1, [x21, 612]
	str	w1, [x19, 1284]
.L90:
	ldr	w0, [x0, 2760]
	ubfiz	w0, w0, 1, 24
	str	w0, [x19, 1292]
	ldr	w0, [x21, 8]
	cmp	w0, 2
	beq	.L136
.L91:
	cbnz	w0, .L97
	ldr	w0, [x4, 556]
	mov	w1, 0
	sub	w3, w0, #1
	lsr	w2, w0, 8
	bfi	w1, w3, 16, 7
	sub	w2, w2, #1
	lsr	w0, w0, 16
	bfi	w1, w2, 8, 6
	sub	w0, w0, #1
	bfi	w1, w0, 0, 6
	str	w1, [x19, 1328]
	ldr	w0, [x4, 560]
	str	w0, [x19, 1296]
	ldr	w0, [x4, 564]
	str	w0, [x19, 1300]
	ldr	w0, [x4, 568]
	str	w0, [x19, 1304]
	ldr	w0, [x4, 572]
	str	w0, [x19, 1308]
	ldr	w0, [x4, 576]
	str	w0, [x19, 1312]
	ldr	w0, [x4, 580]
	str	w0, [x19, 1316]
	ldr	w0, [x4, 584]
	str	w0, [x19, 1320]
	ldr	w0, [x4, 588]
	str	w0, [x19, 1324]
.L97:
	ldr	w1, [x21, 52]
	mov	w0, 0
	mov	w4, 0
	bfi	w0, w1, 0, 1
	str	w0, [x19, 1332]
	orr	w4, w4, 65536
	ldr	w0, [x22, 4472]
	str	w0, [x19, 1336]
	ldr	w0, [x21, 56]
	cmp	w0, wzr
	csel	w4, wzr, w4, eq
	orr	w4, w4, 256
	tbz	x4, 16, .L103
	ldr	w2, [x21, 320]
	add	x0, x21, 324
	add	x1, x19, 1476
	add	x3, x21, 516
	bfi	w4, w2, 0, 8
	.p2align 2
.L102:
	ldr	w2, [x0], 4
	str	w2, [x1], 4
	cmp	x3, x0
	bne	.L102
.L103:
	add	x0, x21, 180
	add	x1, x19, 1404
	add	x3, x21, 244
	str	w4, [x19, 1472]
	.p2align 2
.L101:
	ldr	w2, [x0]
	add	x0, x0, 4
	str	w2, [x1]
	add	x1, x1, 4
	cmp	x3, x0
	ldr	w2, [x0, 60]
	str	w2, [x1, -68]
	bne	.L101
	ldr	w0, [x21, 316]
	add	x2, x23, 61440
	str	w0, [x19, 1468]
	mov	w0, 0
	mov	w5, 3
	mov	w6, 9
	ldr	w7, [x22, 4376]
	mov	w3, 0
	ldr	w4, [x22, 4380]
	bfi	w3, w6, 24, 8
	bfi	w0, w7, 0, 1
	ldr	x1, [x24]
	bfi	w0, w4, 3, 1
	mov	w4, 7
	bfi	w0, w5, 16, 4
	str	w0, [x2]
	str	wzr, [x2, 8]
	bfi	w3, w4, 16, 8
	str	wzr, [x2, 16]
	mov	w4, 1
	str	wzr, [x2, 28]
	and	w3, w3, -65281
	str	wzr, [x2, 32]
	bfi	w3, w4, 0, 8
	str	wzr, [x2, 44]
	add	x1, x1, 61440
	str	w3, [x2, 1328]
	str	wzr, [x23, 4]
	ldr	w2, [x21, 560]
	str	w2, [x1, 520]
	ldr	w2, [x21, 560]
	str	w2, [x1, 524]
	ldr	w2, [x21, 568]
	str	w2, [x1, 752]
	ldr	w2, [x21, 564]
	str	w2, [x1, 756]
	ldr	w2, [x21, 568]
	str	w2, [x1, 772]
	ldr	w0, [x21, 564]
	str	w0, [x1, 776]
	str	w4, [x23, 8]
.L33:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L128:
	add	x0, x5, 4
	add	x4, x5, 160
	mov	w3, 18
	b	.L36
	.p2align 3
.L42:
	ldr	w3, [x0], 4
.L36:
	str	w3, [x2], 4
	cmp	x0, x4
	bne	.L42
	add	x2, x22, 1028
	add	x0, x5, 524
	add	x4, x5, 680
	mov	w3, 193
	b	.L43
	.p2align 3
.L137:
	ldr	w3, [x0], 4
.L43:
	str	w3, [x2], 4
	cmp	x0, x4
	bne	.L137
	add	x4, x22, 696
	mov	w2, 3
	mov	w0, 5
	mov	w3, 2
	stp	w2, w2, [x4, 124]
	mov	w2, 10
	str	w2, [x4, 140]
	stp	w0, w0, [x4, 132]
	mov	w2, 15
	mov	w0, 255
	str	w2, [x4, 144]
	mov	w2, 20
	stp	w0, w0, [x4, 152]
	stp	w0, w0, [x4, 160]
	str	w0, [x4, 168]
	mov	w0, 96
	str	w3, [x4, 100]
	stp	wzr, wzr, [x4, 108]
	stp	wzr, wzr, [x4, 116]
	str	w0, [x4, 520]
	str	w2, [x4, 148]
	b	.L41
.L136:
	ldr	w1, [x4, 632]
	ldr	x0, [x21, 688]
	cmp	w1, 31
	bls	.L138
	ldr	w1, [x4, 592]
	str	w1, [x0, 1224]
	ldr	w1, [x4, 632]
	cmp	w1, 63
	bhi	.L94
.L141:
	ldr	w2, [x4, 596]
	mov	w3, 64
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1228]
.L95:
	ldr	w1, [x4, 632]
	cmp	w1, 64
	bls	.L96
	ldr	w2, [x4, 600]
	mov	w3, 96
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1232]
.L96:
	ldr	w1, [x4, 604]
	str	w1, [x0, 1236]
	ldr	w1, [x4, 608]
	str	w1, [x0, 1240]
	ldr	w1, [x4, 612]
	str	w1, [x0, 1244]
	ldr	w1, [x4, 616]
	str	w1, [x0, 1248]
	ldr	w1, [x4, 620]
	str	w1, [x0, 1252]
	ldr	w0, [x21, 8]
	b	.L91
.L135:
	ldr	w2, [x21, 620]
	ldr	x1, [x21, 688]
	cmp	w2, 31
	bls	.L139
	ldr	w2, [x21, 624]
	str	w2, [x1, 1184]
	ldr	w2, [x21, 620]
	cmp	w2, 63
	bhi	.L87
.L140:
	mov	w3, 64
	sub	w2, w3, w2
	ldr	w3, [x21, 628]
	lsl	w2, w3, w2
	str	w2, [x1, 1188]
.L88:
	ldr	w2, [x21, 620]
	cmp	w2, 64
	bls	.L89
	mov	w3, 96
	sub	w2, w3, w2
	ldr	w3, [x21, 632]
	lsl	w2, w3, w2
	str	w2, [x1, 1192]
.L89:
	ldr	w2, [x21, 636]
	str	w2, [x1, 1196]
	ldr	w2, [x21, 640]
	str	w2, [x1, 1200]
	ldr	w2, [x21, 644]
	str	w2, [x1, 1204]
	ldr	w2, [x21, 648]
	str	w2, [x1, 1208]
	ldr	w2, [x21, 652]
	str	w2, [x1, 1212]
	ldr	w1, [x21, 8]
	b	.L84
	.p2align 3
.L80:
	ldr	w2, [x22, 4116]
	mov	w1, 0
	bfi	w1, w2, 4, 1
	b	.L81
	.p2align 3
.L75:
	ldr	w3, [x22, 4104]
	mov	w1, 0
	ldr	w2, [x22, 4108]
	bfi	w1, w3, 3, 1
	ldr	w3, [x22, 4112]
	bfi	w1, w2, 2, 1
	ldr	w2, [x22, 4100]
	bfi	w1, w3, 1, 1
	bfi	w1, w2, 0, 1
	b	.L79
.L62:
	ldr	w3, [x21, 68]
	cmp	w2, 2
	bfi	w6, w3, 16, 8
	mov	w3, 3
	beq	.L63
	cmp	w2, 1
	mov	w3, 6
	ldr	w2, [x21, 60]
	csel	w3, wzr, w3, ne
	bfi	w6, w3, 6, 4
	and	w6, w6, -64
	cbz	w2, .L64
.L133:
	str	w6, [x8, 236]
	b	.L65
.L60:
	str	w28, [x7, 124]
	b	.L61
.L66:
	ldr	w2, [x21, 520]
	lsr	w3, w3, 5
	udiv	w3, w2, w3
	mov	w2, 0
	bfi	w2, w3, 6, 25
	b	.L67
.L48:
	mov	w0, 7
	str	wzr, [x4, 532]
	str	w0, [x4, 528]
	str	wzr, [x4, 536]
	b	.L50
.L134:
	ldr	w2, [x21, 544]
	cbz	w2, .L69
	ldr	w2, [x21, 516]
	cbnz	w2, .L69
	add	x6, x5, 16
	mov	w3, 36
	mov	w1, 0
	b	.L72
	.p2align 3
.L70:
	ldr	w3, [x6], 4
.L72:
	sxtw	x2, w1
	add	w1, w1, 1
	add	x2, x2, 592
	bfi	w27, w3, 0, 20
	cmp	w1, 40
	add	x2, x23, x2, lsl 2
	str	w27, [x2, 4]
	bne	.L70
	add	x3, x5, 536
	mov	w6, 273
	add	x5, x5, 692
	b	.L71
	.p2align 3
.L73:
	ldr	w6, [x3], 4
.L71:
	sxtw	x2, w1
	bfi	w26, w6, 0, 20
	add	x2, x2, 592
	cmp	x5, x3
	add	w1, w1, 1
	add	x2, x23, x2, lsl 2
	str	w26, [x2, 4]
	bne	.L73
	b	.L77
.L132:
	mov	w2, 19
	mov	w28, 0
	bfi	w28, w2, 16, 6
	mov	w2, 27
	bfi	w28, w2, 0, 7
	b	.L59
.L131:
	mov	w2, 3
	b	.L57
.L46:
	cmp	w0, 719
	bls	.L47
	mov	w0, 2
	str	w0, [x22, 1220]
	b	.L45
.L139:
	mov	w3, 32
	sub	w2, w3, w2
	ldr	w3, [x21, 624]
	lsl	w2, w3, w2
	str	w2, [x1, 1184]
	ldr	w2, [x21, 620]
	cmp	w2, 63
	bls	.L140
.L87:
	ldr	w2, [x21, 628]
	str	w2, [x1, 1188]
	b	.L88
.L138:
	ldr	w2, [x4, 592]
	mov	w3, 32
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 1224]
	ldr	w1, [x4, 632]
	cmp	w1, 63
	bls	.L141
.L94:
	ldr	w1, [x4, 596]
	str	w1, [x0, 1228]
	b	.L95
.L69:
	add	x2, x19, 692
	add	x5, x22, 1188
	.p2align 2
.L76:
	ldr	w3, [x1], 4
	bfi	w25, w3, 0, 20
	cmp	x5, x1
	str	w25, [x2], 4
	bne	.L76
	b	.L77
.L47:
	mov	w0, 1
	str	w0, [x22, 1220]
	b	.L45
.L130:
	bfi	w2, w8, 26, 2
	b	.L54
	.size	DRV_VENC_HAL_V500R001_CfgReg, .-DRV_VENC_HAL_V500R001_CfgReg
	.align	3
.LC6:
	.xword	.LANCHOR0
	.align	3
.LC7:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC8:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_Init
	.type	DRV_VENC_HAL_V500R001_Init, %function
DRV_VENC_HAL_V500R001_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC14
	ldr	x20, .LC15
	ldr	x0, [x19]
	cbz	x0, .L143
.L146:
	ldr	x1, [x20, 40]
	mov	w0, 4480
	blr	x1
	str	x0, [x19, 8]
	cbz	x0, .L163
	ldr	x3, [x20]
	mov	w1, 0
	mov	x2, 4480
	blr	x3
	ldr	x1, [x19, 8]
	cbz	x1, .L154
	add	x13, x1, 1280
	ldr	x2, [x19]
	add	x14, x1, 1280
	mov	w4, 1
	str	x2, [x1]
	mov	w5, 3
	str	w4, [x1, 60]
	mov	w3, 1280
	stp	wzr, w5, [x1, 8]
	str	w3, [x1, 16]
	mov	w8, 4
	stp	w4, w5, [x1, 44]
	stp	w4, w8, [x13, 56]
	mov	w7, 128
	mov	w9, 256
	stp	w9, w7, [x13, 64]
	stp	w8, w7, [x14, 72]
	mov	w6, 8
	mov	w2, 720
	stp	w5, w6, [x14, 80]
	mov	w3, 10240
	str	w2, [x1, 20]
	mov	w2, 28
	str	w3, [x1, 32]
	str	w2, [x1, 524]
	mov	w3, 16
	mov	w2, 48
	str	w3, [x1, 528]
	str	w2, [x1, 532]
	mov	w3, 32
	add	x2, x1, 2180
	mov	w9, 6
	str	w3, [x1, 1368]
	add	x5, x1, 2244
	str	w3, [x1, 1376]
	str	w3, [x1, 1780]
	mov	x3, x2
	str	w6, [x1, 1372]
	str	w4, [x1, 1640]
	str	w4, [x1, 2016]
	str	w4, [x1, 2068]
	str	w9, [x1, 1784]
	.p2align 2
.L149:
	str	w4, [x3], 4
	mov	w0, 1
	cmp	x3, x5
	bne	.L149
	mov	w3, 48
	str	wzr, [x2, 260]
	stp	wzr, w3, [x2, 92]
	stp	w3, w3, [x2, 100]
	add	x3, x2, 256
	str	wzr, [x2, 292]
	stp	wzr, wzr, [x2, 80]
	stp	wzr, wzr, [x2, 132]
	str	wzr, [x2, 296]
	mov	w4, 4
	str	wzr, [x2, 304]
	mov	w5, 8
	str	w4, [x2, 164]
	mov	w8, 2
	str	wzr, [x2, 308]
	mov	w7, 3
	stp	w5, w8, [x2, 64]
	stp	w7, wzr, [x2, 72]
	str	wzr, [x2, 356]
	mov	w10, 10
	mov	w13, 51
	str	w13, [x2, 108]
	stp	w10, w4, [x2, 116]
	stp	w5, w13, [x2, 124]
	stp	w10, w10, [x3, 144]
	stp	wzr, w10, [x3, 152]
	mov	w3, 44
	str	w10, [x2, 416]
	str	w3, [x2, 112]
	mov	w14, 70
	str	wzr, [x2, 424]
	mov	w3, 2592
	str	w3, [x2, 140]
	mov	w11, 50
	stp	w4, w4, [x2, 168]
	str	w14, [x2, 196]
	mov	w12, 60
	str	w14, [x2, 228]
	add	x14, x2, 256
	stp	w11, w12, [x2, 188]
	stp	w11, w12, [x2, 220]
	str	w4, [x2, 176]
	mov	w9, 160
	str	w9, [x2, 212]
	mov	w3, 21845
	str	w9, [x2, 244]
	mov	w6, 5
	stp	w0, w0, [x14, 8]
	stp	wzr, w0, [x14, 16]
	mov	w14, 80
	str	w14, [x2, 200]
	str	w14, [x2, 232]
	mov	w14, 120
	stp	w3, w3, [x2, 180]
	str	w14, [x2, 204]
	add	x3, x1, 2608
	str	w14, [x2, 236]
	mov	w14, 140
	str	w4, [x2, 336]
	mov	w16, 150
	stp	wzr, w4, [x2, 152]
	stp	w6, wzr, [x2, 144]
	str	w14, [x2, 208]
	add	x17, x3, 512
	str	w14, [x2, 240]
	mov	w14, 180
	str	wzr, [x2, 280]
	mov	w15, 6
	str	w14, [x2, 216]
	str	w14, [x2, 248]
	mov	w14, 12
	str	wzr, [x2, 372]
	str	wzr, [x2, 376]
	str	wzr, [x2, 312]
	str	wzr, [x2, 300]
	str	wzr, [x2, 256]
	str	wzr, [x2, 252]
	str	wzr, [x2, 360]
	str	wzr, [x2, 364]
	str	wzr, [x2, 368]
	add	x2, x1, 3448
	stp	w11, w16, [x3, 12]
	mov	w16, 30
	str	w16, [x3, 60]
	mov	w16, 511
	str	w16, [x3, 748]
	add	x16, x3, 512
	mov	w11, 20
	stp	w14, w5, [x3, 20]
	stp	w4, w14, [x3, 28]
	mov	w14, 131
	str	w9, [x3, 76]
	stp	w5, w4, [x3, 36]
	mov	w9, 15
	str	w6, [x3, 760]
	stp	w8, w4, [x3, 44]
	stp	w15, w4, [x3, 52]
	str	w6, [x3, 764]
	add	x18, x2, 256
	str	w11, [x3, 8]
	add	x19, x2, 256
	str	w14, [x3, 72]
	add	x20, x2, 256
	str	w14, [x3, 84]
	mov	w14, 100
	str	w9, [x3, 752]
	add	x30, x2, 256
	str	w9, [x3, 756]
	str	w14, [x3, 80]
	str	w0, [x3, 4]
	str	w7, [x3, 676]
	str	w0, [x3, 688]
	stp	w8, w15, [x16, 184]
	stp	w5, w5, [x16, 192]
	stp	w10, w11, [x3, 136]
	str	w5, [x3, 712]
	mov	w10, 24
	str	w5, [x3, 716]
	str	w12, [x3, 784]
	mov	w12, 16
	str	w6, [x3, 800]
	str	w5, [x3, 820]
	str	w5, [x3, 824]
	str	w11, [x3, 836]
	mov	w11, 255
	stp	w12, w12, [x17, 208]
	stp	w10, w10, [x17, 216]
	mov	w10, 767
	str	w10, [x3, 148]
	stp	w0, w0, [x2, 44]
	mov	w3, 7
	str	w0, [x2, 88]
	stp	w3, w3, [x2, 184]
	stp	w0, w0, [x2, 80]
	str	w0, [x2, 208]
	mov	w10, -1
	str	w0, [x2, 232]
	str	w0, [x2, 248]
	str	w7, [x2, 272]
	str	w0, [x2, 280]
	stp	w10, w3, [x18, 132]
	stp	w10, w3, [x18, 140]
	stp	w10, w3, [x19, 148]
	stp	w10, w3, [x19, 156]
	stp	w0, w0, [x20, 164]
	stp	w0, w0, [x20, 172]
	str	w14, [x2, 452]
	mov	w14, 9
	str	w0, [x2, 444]
	mov	w10, 64
	str	w0, [x2, 448]
	stp	w6, w6, [x30, 204]
	stp	w9, w9, [x30, 212]
	str	w0, [x2, 476]
	mov	w6, 500
	str	w6, [x2, 456]
	add	x6, x1, 696
	str	w8, [x1, 4296]
	str	w8, [x1, 4300]
	str	w9, [x2, 560]
	str	w9, [x2, 564]
	str	w8, [x2, 592]
	str	w0, [x2, 480]
	str	w7, [x2, 496]
	str	w0, [x2, 524]
	str	w7, [x2, 600]
	str	w7, [x2, 604]
	str	w11, [x1, 4172]
	str	w11, [x1, 4180]
	str	w0, [x2, 100]
	str	w0, [x2, 200]
	str	w0, [x2, 264]
	str	w0, [x2, 268]
	str	w8, [x2, 616]
	str	w0, [x2, 648]
	mov	w2, 171
	str	w2, [x1, 4360]
	mov	w2, 85
	str	w2, [x1, 4364]
	mov	w2, 23040
	movk	w2, 0x262, lsl 16
	str	w2, [x1, 4468]
	mov	w2, 2304
	str	w9, [x1, 4332]
	str	w3, [x1, 4368]
	movk	w2, 0x3d, lsl 16
	str	w9, [x1, 4372]
	mov	w9, 256
	str	w8, [x1, 4460]
	str	w2, [x1, 4472]
	str	w0, [x1, 4312]
	str	w0, [x1, 4320]
	str	w14, [x1, 4336]
	str	wzr, [x1, 4376]
	str	w0, [x1, 4380]
	str	w0, [x1, 4464]
	str	w0, [x6, 4]
	str	w0, [x1, 696]
	stp	w4, w12, [x6, 16]
	stp	w4, w12, [x6, 24]
	stp	w12, w4, [x6, 60]
	stp	w0, w9, [x6, 68]
	stp	w7, w10, [x6, 8]
	str	w4, [x1, 796]
	add	x4, x1, 768
	add	x12, x1, 768
	mov	w9, 25
	stp	w3, w3, [x4, 56]
	stp	w3, w14, [x4, 64]
	add	x3, x1, 1188
	mov	w4, 11
	stp	w9, w11, [x12, 84]
	stp	w11, w11, [x12, 92]
	mov	x2, x3
	str	w4, [x1, 840]
	mov	w4, 14
	str	w8, [x1, 780]
	str	w4, [x1, 844]
	mov	w4, 18
	str	w13, [x1, 800]
	mov	w3, 128
	str	w4, [x1, 848]
	mov	w8, 378
	ldr	x4, .LC16
	str	w10, [x2, 28]
	str	wzr, [x1, 1188]
	stp	w3, w7, [x2, 12]
	stp	w5, w8, [x2, 20]
	stp	w7, w9, [x2, 4]
	add	x3, x1, 868
	add	x2, x4, 204
	add	x5, x4, 360
	b	.L152
	.p2align 3
.L150:
	ldr	w0, [x2], 4
.L152:
	str	w0, [x3], 4
	cmp	x2, x5
	bne	.L150
	add	x1, x1, 1028
	add	x0, x4, 364
	add	x3, x4, 520
	mov	w2, 1
	b	.L151
	.p2align 3
.L164:
	ldr	w2, [x0], 4
.L151:
	str	w2, [x1], 4
	cmp	x0, x3
	bne	.L164
	str	wzr, [x6, 532]
	mov	w0, 7
	str	wzr, [x6, 536]
	str	w0, [x6, 528]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L163:
	ldr	x0, [x19]
	cbz	x0, .L160
	ldr	x1, [x20, 32]
	blr	x1
	str	xzr, [x19]
.L160:
	mov	w0, -1
.L165:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L154:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L143:
	ldr	x2, [x20, 24]
	mov	x1, 63232
	mov	x0, 4173856768
	blr	x2
	str	x0, [x19]
	cbnz	x0, .L146
	mov	w0, -1
	b	.L165
	.size	DRV_VENC_HAL_V500R001_Init, .-DRV_VENC_HAL_V500R001_Init
	.align	3
.LC14:
	.xword	.LANCHOR0
	.align	3
.LC15:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC16:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V500R001_Deinit
	.type	DRV_VENC_HAL_V500R001_Deinit, %function
DRV_VENC_HAL_V500R001_Deinit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC19
	ldr	x0, [x19]
	cbz	x0, .L167
	ldr	x1, .LC20
	ldr	x1, [x1, 32]
	blr	x1
	str	xzr, [x19]
.L167:
	ldr	x0, [x19, 8]
	cbz	x0, .L166
	ldr	x1, .LC20
	ldr	x1, [x1, 48]
	blr	x1
	str	xzr, [x19, 8]
.L166:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V500R001_Deinit, .-DRV_VENC_HAL_V500R001_Deinit
	.align	3
.LC19:
	.xword	.LANCHOR0
	.align	3
.LC20:
	.xword	venc_Osal_Func_Ptr_S
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	g_h265LambdaSsd, %object
	.size	g_h265LambdaSsd, 200
g_h265LambdaSsd:
	.word	18
	.word	22
	.word	28
	.word	36
	.word	45
	.word	57
	.word	72
	.word	91
	.word	115
	.word	145
	.word	183
	.word	231
	.word	291
	.word	367
	.word	463
	.word	583
	.word	735
	.word	926
	.word	1167
	.word	1470
	.word	1853
	.word	2334
	.word	2941
	.word	3706
	.word	4669
	.word	5883
	.word	7412
	.word	9338
	.word	11766
	.word	14824
	.word	18677
	.word	23532
	.word	29649
	.word	37355
	.word	47065
	.word	59298
	.word	74711
	.word	94130
	.word	118596
	.word	131071
	.word	188260
	.word	237192
	.word	262142
	.zero	28
	.type	g_h264LambdaSsd, %object
	.size	g_h264LambdaSsd, 160
g_h264LambdaSsd:
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	4
	.word	5
	.word	7
	.word	9
	.word	11
	.word	14
	.word	17
	.word	22
	.word	27
	.word	34
	.word	43
	.word	54
	.word	69
	.word	86
	.word	109
	.word	137
	.word	173
	.word	218
	.word	274
	.word	345
	.word	435
	.word	548
	.word	691
	.word	870
	.word	1097
	.word	1382
	.word	1741
	.word	2193
	.word	2763
	.word	3482
	.word	4095
	.word	4095
	.word	4095
	.type	g_h264LambdaSad, %object
	.size	g_h264LambdaSad, 160
g_h264LambdaSad:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	4
	.word	4
	.word	4
	.word	5
	.word	6
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
	.word	23
	.word	25
	.word	29
	.word	32
	.word	36
	.word	40
	.word	45
	.word	51
	.word	57
	.word	64
	.word	72
	.word	81
	.word	91
	.type	g_h265LambdaSad, %object
	.size	g_h265LambdaSad, 200
g_h265LambdaSad:
	.word	193
	.word	216
	.word	243
	.word	273
	.word	306
	.word	344
	.word	386
	.word	433
	.word	487
	.word	546
	.word	613
	.word	688
	.word	773
	.word	867
	.word	974
	.word	1093
	.word	1227
	.word	1377
	.word	1546
	.word	1735
	.word	1948
	.word	2186
	.word	2454
	.word	2755
	.word	3092
	.word	3471
	.word	3896
	.word	4373
	.word	4908
	.word	5510
	.word	6184
	.word	6942
	.word	7792
	.word	8746
	.word	9817
	.word	11020
	.word	12369
	.word	13884
	.word	15584
	.word	17493
	.word	19636
	.word	22040
	.word	23170
	.zero	28
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_pRegBase, %object
	.size	g_pRegBase, 8
g_pRegBase:
	.zero	8
	.type	g_pHalRegInfo, %object
	.size	g_pHalRegInfo, 8
g_pHalRegInfo:
	.zero	8
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
