#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"drv_venc_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_ClrInt
	.type	DRV_VENC_HAL_V400R004C02_ClrInt, %function
DRV_VENC_HAL_V400R004C02_ClrInt:
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
	str	w1, [x0, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5:
	ldr	w1, [x0, 12]
	orr	w1, w1, 134217728
	str	w1, [x0, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4:
	ldr	w1, [x0, 12]
	orr	w1, w1, 1
	str	w1, [x0, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3:
	ldr	w1, [x0, 12]
	orr	w1, w1, 1024
	str	w1, [x0, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V400R004C02_ClrInt, .-DRV_VENC_HAL_V400R004C02_ClrInt
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_DisableInt
	.type	DRV_VENC_HAL_V400R004C02_DisableInt, %function
DRV_VENC_HAL_V400R004C02_DisableInt:
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
	str	wzr, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L14:
	ldr	w1, [x0, 4]
	and	w1, w1, -134217729
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L13:
	ldr	w1, [x0, 4]
	and	w1, w1, -2
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L12:
	ldr	w1, [x0, 4]
	and	w1, w1, -1025
	str	w1, [x0, 4]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V400R004C02_DisableInt, .-DRV_VENC_HAL_V400R004C02_DisableInt
	.align	3
.LC1:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu
	.type	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu, %function
DRV_VENC_HAL_V400R004C02_ReadReg_Smmu:
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
	.size	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu, .-DRV_VENC_HAL_V400R004C02_ReadReg_Smmu
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_ReadReg
	.type	DRV_VENC_HAL_V400R004C02_ReadReg, %function
DRV_VENC_HAL_V400R004C02_ReadReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC3
	ldp	x0, x4, [x1]
	cbz	x19, .L23
	ldr	w1, [x0]
	and	w1, w1, 1
	str	w1, [x19, 8]
	ldr	w1, [x0]
	ubfx	x3, x1, 1, 1
	str	w3, [x19, 12]
	ldr	w2, [x0]
	ubfx	x1, x2, 3, 1
	str	w1, [x19, 16]
	orr	w1, w3, w1
	ldr	w2, [x0]
	ubfx	x2, x2, 27, 1
	str	w2, [x19]
	ldr	w2, [x0]
	ubfx	x2, x2, 10, 1
	str	w2, [x19, 4]
	cbnz	w1, .L23
	ldr	w3, [x0, 5740]
	add	x5, x4, 8
	ubfx	x3, x3, 0, 26
	str	w3, [x19, 24]
	ldr	w1, [x4, 8]
	cbz	w1, .L29
	ldr	w1, [x0, 7808]
	lsl	w1, w1, 3
	str	w1, [x19, 20]
	ldr	w2, [x0, 5636]
	ldr	w1, [x0, 5668]
	ubfx	x2, x2, 0, 19
	ubfx	x1, x1, 0, 17
	add	w1, w2, w1
	str	w1, [x19, 28]
	ldp	w4, w2, [x5, 8]
	add	w4, w4, 7
	add	w2, w2, 7
	lsr	w4, w4, 3
	lsr	w2, w2, 3
	mul	w2, w4, w2
	udiv	w3, w3, w2
	str	w3, [x19, 24]
	ldr	w2, [x0, 7816]
	str	w2, [x19, 32]
	ldr	w2, [x0, 7820]
	str	w2, [x19, 36]
.L28:
	lsr	w1, w1, 2
	str	w1, [x19, 28]
	ldr	w1, [x0, 1808]
	ubfx	x1, x1, 0, 25
	str	w1, [x19, 40]
	ldr	w0, [x0, 1812]
	ubfx	x0, x0, 0, 25
	str	w0, [x19, 44]
.L23:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L29:
	ldr	w1, [x0, 8324]
	lsl	w1, w1, 3
	str	w1, [x19, 20]
	ldr	w4, [x0, 5640]
	ldr	w1, [x0, 5644]
	ldr	w2, [x0, 5672]
	ubfx	x4, x4, 0, 19
	ubfx	x1, x1, 0, 19
	ubfx	x2, x2, 0, 19
	add	w1, w4, w1
	add	w1, w1, w2
	str	w1, [x19, 28]
	ldp	w4, w2, [x5, 8]
	add	w4, w4, 15
	add	w2, w2, 15
	lsr	w4, w4, 4
	lsr	w2, w2, 4
	mul	w2, w4, w2
	udiv	w3, w3, w2
	str	w3, [x19, 24]
	ldr	w2, [x0, 8328]
	str	w2, [x19, 32]
	ldr	w2, [x0, 8332]
	str	w2, [x19, 36]
	b	.L28
	.size	DRV_VENC_HAL_V400R004C02_ReadReg, .-DRV_VENC_HAL_V400R004C02_ReadReg
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_CfgReg
	.type	DRV_VENC_HAL_V400R004C02_CfgReg, %function
DRV_VENC_HAL_V400R004C02_CfgReg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L30
	ldr	x0, .LC7
	mov	x2, 696
	ldr	x3, .LC6
	mov	x1, x21
	ldr	x20, [x21, 688]
	mov	x25, 0
	ldr	x27, [x3, 8]
	ldr	x3, [x0, 8]
	ldr	x0, .LC6
	ldr	x23, [x0]
	mov	x0, x27
	blr	x3
	ldr	w0, [x21, 524]
	ldr	w2, [x21, 516]
	cmp	w0, 25
	bls	.L32
	sub	w1, w0, #26
	mov	x25, 1
	cmp	w1, 3
	bls	.L32
	sub	w1, w0, #30
	mov	x25, 2
	cmp	w1, 4
	bls	.L32
	sub	w1, w0, #35
	mov	x25, 3
	mov	x0, 4
	cmp	w1, 6
	csel	x25, x0, x25, hi
.L32:
	cmp	w2, wzr
	lsl	x3, x25, 2
	cset	x0, eq
	sub	x3, x3, x25
	lsl	x26, x0, 5
	lsl	x1, x3, 3
	add	x0, x26, x0, lsl 3
	sub	x3, x1, x3
	lsl	x26, x0, 6
	lsl	x1, x25, 3
	add	x26, x0, x26
	add	x22, x27, 696
	add	x3, x26, x3, lsl 2
	sub	x1, x1, x25
	add	x3, x22, x3
	lsl	x1, x1, 1
	add	x3, x3, 520
	sub	x1, x1, x25
	mov	x2, 404
	add	x0, x27, 780
	add	x4, x25, x1, lsl 5
	sub	x1, x4, x1
	ldp	x4, x5, [x3]
	stp	x4, x5, [x22]
	add	x1, x1, x26
	ldp	x4, x5, [x3, 16]
	stp	x4, x5, [x22, 16]
	add	x1, x22, x1
	ldp	x4, x5, [x3, 32]
	stp	x4, x5, [x22, 32]
	add	x1, x1, 940
	ldp	x4, x5, [x3, 48]
	stp	x4, x5, [x22, 48]
	ldp	x4, x5, [x3, 64]
	stp	x4, x5, [x22, 64]
	ldr	w3, [x3, 80]
	str	w3, [x22, 80]
	bl	memcpy
	add	x0, x25, 76
	add	x1, x27, 1184
	add	x0, x26, x0, lsl 5
	add	x0, x22, x0
	add	x0, x0, 528
	ldp	x2, x3, [x0]
	stp	x2, x3, [x1]
	ldp	x2, x3, [x0, 16]
	stp	x2, x3, [x1, 16]
	ldr	x2, .LC8
	ldr	w0, [x21, 8]
	cbnz	w0, .L113
	add	x0, x27, 864
	mov	w4, 1
	mov	x3, x0
	str	x0, [x29, 96]
	add	x5, x2, 320
	add	x0, x2, 164
	b	.L37
	.p2align 3
.L35:
	ldr	w4, [x0], 4
.L37:
	str	w4, [x3], 4
	cmp	x5, x0
	bne	.L35
	add	x0, x2, 324
	add	x3, x27, 1024
	add	x2, x2, 480
	mov	w4, 1
	b	.L36
	.p2align 3
.L114:
	ldr	w4, [x0], 4
.L36:
	str	w4, [x3], 4
	cmp	x2, x0
	bne	.L114
	mov	w2, 4
	mov	w0, 7
	stp	w2, wzr, [x22, 100]
	mov	w2, 32
	str	w2, [x22, 516]
	mov	w2, 9
	str	w2, [x22, 136]
	mov	w2, 11
	str	w0, [x22, 132]
	stp	w0, w0, [x22, 124]
	str	w2, [x22, 140]
	mov	w0, 255
	mov	w2, 14
	str	w0, [x22, 164]
	stp	w0, w0, [x22, 156]
	str	w2, [x22, 144]
	mov	w0, 25
	mov	w2, 18
	str	w0, [x22, 152]
	stp	wzr, wzr, [x22, 108]
	stp	wzr, wzr, [x22, 116]
	str	w2, [x22, 148]
.L39:
	ldr	w0, [x21, 44]
	cbz	w0, .L43
	ldr	w0, [x21, 16]
	cmp	w0, 1919
	bls	.L44
	mov	w0, 3
	str	w0, [x27, 6416]
.L43:
	ldr	w0, [x21, 8]
	cbnz	w0, .L46
	ldr	w0, [x21, 12]
	cmp	w0, wzr
	cset	w2, eq
	cmp	w0, 3
	str	w2, [x22, 5732]
	cset	w2, ne
	mov	w0, 5
	str	w2, [x22, 5728]
	mov	w2, 7
	csel	w0, w0, w2, ne
	str	w0, [x22, 5724]
.L48:
	ldr	w0, [x21, 16]
	ldr	w2, [x21, 8]
	sub	w0, w0, #128
	cmp	w0, 127
	ccmp	w2, wzr, 0, ls
	bne	.L49
	mov	w2, 28
	str	w2, [x21, 524]
	str	w2, [x21, 528]
	str	w2, [x21, 532]
	str	wzr, [x27, 796]
	str	wzr, [x21, 24]
	str	wzr, [x27, 7560]
	str	wzr, [x27, 7852]
.L49:
	ldr	w0, [x21, 44]
	mov	w2, 11
	mov	w3, 2
	bfi	w2, w0, 10, 1
	mov	w0, 6
	orr	w2, w2, 134217728
	str	w2, [x23, 4]
	add	x2, x27, 4096
	str	x2, [x29, 104]
	ldr	w5, [x21, 8]
	ldr	w4, [x21, 44]
	cmp	w5, w3
	cset	w6, ne
	bfi	w0, w6, 3, 2
	ldr	w6, [x27, 6528]
	bfi	w0, w4, 5, 1
	ldr	w4, [x27, 7900]
	bfi	w0, w4, 6, 1
	ldr	w4, [x27, 7896]
	bfi	w0, w4, 7, 1
	ldr	w4, [x21, 516]
	and	w0, w0, -16777473
	cmp	w4, wzr
	bfi	w0, w6, 9, 1
	cset	w7, eq
	ldr	w6, [x22, 5732]
	bfi	w0, w7, 10, 2
	cmp	w5, w3
	bfi	w0, w6, 12, 1
	csel	w3, wzr, w3, ne
	bfi	w0, w4, 16, 1
	ldr	w4, [x22, 5728]
	orr	w0, w0, 131072
	mov	w5, 0
	bfi	w0, w4, 18, 2
	and	w0, w0, -6291457
	and	w0, w0, -33554433
	bfi	w0, w3, 26, 2
	ldr	w3, [x21, 48]
	bfi	w0, w3, 28, 2
	mov	w3, 0
	and	w0, w0, 1073741823
	str	w0, [x23, 20]
	str	wzr, [x20, 512]
	mov	w0, 458752
	ldr	w4, [x21, 24]
	ldr	w6, [x21, 32]
	ubfiz	w4, w4, 17, 1
	bfi	w4, w6, 0, 16
	str	w4, [x20, 516]
	mov	w6, 0
	mov	w4, 0
	ldr	w7, [x21, 524]
	bfi	w3, w7, 10, 6
	ldr	w7, [x27, 7560]
	bfi	w3, w7, 18, 1
	ldr	w7, [x27, 7544]
	bfi	w3, w7, 19, 1
	str	w3, [x23, 32]
	str	wzr, [x23, 36]
	str	wzr, [x23, 40]
	str	wzr, [x20, 520]
	ldr	w3, [x27, 8004]
	bfi	w0, w3, 19, 2
	ldr	w3, [x27, 8008]
	bfi	w0, w3, 21, 1
	and	w0, w0, -8388609
	str	w0, [x23, 48]
	ldr	w0, [x21, 20]
	sub	w0, w0, #1
	bfi	w5, w0, 16, 13
	ldr	w0, [x21, 16]
	sub	w0, w0, #1
	bfi	w5, w0, 0, 13
	str	w5, [x20]
	str	w6, [x23, 56]
	ldr	w0, [x27, 8012]
	str	w0, [x23, 60]
	ldr	w0, [x27, 7912]
	bfi	w4, w0, 4, 4
	ldr	w0, [x27, 7916]
	bfi	w4, w0, 0, 4
	str	w4, [x23, 64]
	ldr	w0, [x21, 8]
	cmp	w0, 2
	beq	.L115
	cbnz	w0, .L54
	mov	w0, 15
	mov	w24, 0
	bfi	w24, w0, 16, 6
	mov	w0, 31
	bfi	w24, w0, 0, 7
.L54:
	mov	w0, 3
	mov	w3, 3
	stp	w24, w0, [x20, 16]
	mov	w0, 1
	str	w0, [x20, 524]
	mov	w0, 0
	mov	w2, 1
	bfi	w0, w3, 0, 3
	mov	w5, 0
	bfi	w0, w2, 3, 2
	mov	w2, 0
	bfi	w0, w3, 5, 3
	mov	w4, 0
	bfi	w0, w3, 8, 3
	str	w0, [x23, 100]
	ldr	w0, [x21, 176]
	str	w0, [x20, 128]
	mov	w0, 0
	ldr	w6, [x21, 72]
	str	w6, [x20, 132]
	ldr	w6, [x21, 76]
	str	w6, [x20, 136]
	ldr	w6, [x21, 80]
	str	w6, [x20, 140]
	ldr	w6, [x21, 84]
	bfi	w5, w6, 16, 16
	ldr	w6, [x21, 88]
	bfi	w5, w6, 0, 16
	str	w5, [x20, 152]
	ldr	w5, [x21, 148]
	add	x5, x21, x5, lsl 2
	ldr	w5, [x5, 136]
	str	w5, [x20, 156]
	ldr	w5, [x21, 116]
	add	x5, x21, x5, lsl 2
	ldr	w5, [x5, 92]
	str	w5, [x20, 160]
	ldr	w5, [x21, 116]
	add	x5, x21, x5, lsl 2
	ldr	w5, [x5, 100]
	str	w5, [x20, 164]
	ldr	w5, [x21, 108]
	bfi	w2, w5, 0, 16
	ldr	w5, [x21, 112]
	bfi	w2, w5, 16, 16
	str	w2, [x20, 168]
	ldr	w2, [x21, 116]
	cmp	w2, wzr
	cset	x2, eq
	add	x2, x2, 20
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 12]
	str	w2, [x20, 184]
	ldr	w2, [x21, 116]
	cmp	w2, wzr
	cset	x2, eq
	add	x2, x2, 24
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 4]
	str	w2, [x20, 188]
	ldr	w2, [x21, 112]
	bfi	w4, w2, 0, 16
	ldr	w2, [x21, 108]
	bfi	w4, w2, 16, 16
	str	w4, [x20, 192]
	ldr	w2, [x21, 116]
	cmp	w2, wzr
	cset	x2, eq
	add	x2, x2, 32
	ldr	w2, [x21, x2, lsl 2]
	str	w2, [x20, 208]
	ldr	w2, [x21, 116]
	add	x2, x2, 32
	ldr	w2, [x21, x2, lsl 2]
	str	w2, [x20, 212]
	ldr	w2, [x21, 116]
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 120]
	str	w2, [x20, 48]
	ldr	w2, [x21, 116]
	cmp	w2, wzr
	cset	x2, eq
	add	x2, x2, 28
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 8]
	str	w2, [x20, 52]
	ldr	w2, [x21, 180]
	str	w2, [x20, 56]
	ldr	w2, [x21, 312]
	str	w2, [x20, 60]
	ldr	w2, [x21, 308]
	str	w2, [x20, 64]
	ldr	w2, [x21, 64]
	cmp	w2, 2
	beq	.L55
	cmp	w2, 1
	beq	.L96
	and	w0, w0, -961
	and	w0, w0, -16385
	cbnz	w2, .L56
	ldr	w2, [x21, 68]
	cmp	w2, wzr
	cset	w2, eq
.L57:
	bfi	w0, w2, 16, 8
	str	w0, [x20, 4]
	ldr	x0, [x29, 104]
	mov	w2, 0
	ldr	w3, [x22, 5724]
	mov	w12, 16
	add	x0, x0, 2432
	mov	w11, 64
	bfi	w2, w3, 0, 3
	mov	w10, 0
	mov	w8, 0
	mov	w9, 0
	ldr	w3, [x0, 1364]
	mov	w18, 0
	mov	w16, 0
	mov	w15, 0
	bfi	w2, w3, 4, 1
	mov	w3, 5
	and	w2, w2, -33
	mov	w14, 0
	orr	w2, w2, 1792
	mov	w13, 0
	orr	w2, w2, 28672
	str	w2, [x20, 528]
	mov	w2, 0
	mov	w26, 0
	bfi	w2, w3, 24, 8
	mov	w28, 0
	bfi	w2, w3, 16, 8
	mov	w3, 15
	bfi	w2, w3, 8, 8
	mov	w25, 0
	bfi	w2, w3, 0, 8
	str	w2, [x20, 544]
	mov	w2, 3
	str	w2, [x20, 72]
	mov	w2, 24
	str	w2, [x20, 532]
	mov	w2, 500
	mov	w3, 0
	movk	w2, 0x64, lsl 16
	str	w2, [x20, 536]
	mov	w2, 0
	mov	w30, 0
	ldr	w4, [x0, 4]
	bfi	w3, w4, 0, 1
	ldr	w4, [x22, 4]
	bfi	w3, w4, 1, 1
	ldr	w4, [x27, 696]
	bfi	w3, w4, 2, 1
	mov	w4, 0
	orr	w3, w3, 8
	and	w3, w3, -17
	str	w3, [x23, 352]
	mov	w3, -128
	ldr	w5, [x21, 680]
	str	w5, [x23, 392]
	mov	w5, 0
	bfi	w5, w3, 0, 8
	ldr	w6, [x0, 1008]
	bfi	w5, w3, 8, 8
	bfi	w5, w3, 16, 8
	bfi	w2, w6, 0, 1
	ldr	w6, [x0, 1012]
	bfi	w2, w6, 1, 1
	ldr	w6, [x22, 92]
	bfi	w2, w6, 2, 1
	ldr	w6, [x0, 1028]
	bfi	w2, w6, 4, 1
	ldr	w6, [x22, 88]
	bfi	w2, w6, 8, 1
	ldr	w6, [x0, 1004]
	bfi	w2, w6, 9, 1
	ldr	w6, [x0, 1076]
	bfi	w2, w6, 10, 1
	ldr	w6, [x0, 1080]
	bfi	w2, w6, 11, 1
	ldr	w6, [x0, 1084]
	bfi	w2, w6, 12, 1
	ldr	w6, [x0, 1000]
	bfi	w2, w6, 13, 1
	ldr	w6, [x0, 996]
	bfi	w2, w6, 14, 1
	ldr	w6, [x0, 1088]
	bfi	w2, w6, 15, 1
	str	w2, [x23, 440]
	mov	w2, 2
	mov	w6, 128
	ldr	w7, [x22, 96]
	str	w5, [x20, 1760]
	mov	w5, 1
	bfi	w4, w7, 1, 1
	bfi	w4, w2, 16, 8
	bfi	w4, w2, 24, 8
	mov	w2, 0
	bfi	w2, w3, 0, 8
	str	w4, [x20, 540]
	bfi	w2, w3, 8, 8
	str	w2, [x20, 1764]
	mov	w2, 0
	bfi	w2, w6, 0, 10
	bfi	w2, w6, 10, 10
	str	w2, [x20, 1768]
	str	wzr, [x20, 32]
	mov	w2, 43691
	movk	w2, 0xaaaa, lsl 16
	ldr	w3, [x21, 148]
	add	w3, w3, 2
	umull	x6, w3, w2
	lsr	x4, x6, 32
	lsr	w7, w4, 1
	lsl	w6, w7, 2
	sub	w4, w6, w7
	sub	w3, w3, w4
	mov	w4, 0
	add	x3, x21, x3, lsl 2
	ldr	w3, [x3, 136]
	str	w3, [x20, 216]
	ldr	w3, [x21, 148]
	add	w3, w3, w5
	umull	x6, w3, w2
	lsr	x2, x6, 32
	lsr	w7, w2, 1
	lsl	w6, w7, 2
	sub	w2, w6, w7
	mov	w7, 0
	sub	w2, w3, w2
	mov	w6, 0
	add	x2, x21, x2, lsl 2
	ldr	w2, [x2, 136]
	str	w2, [x20, 220]
	str	w5, [x23, 492]
	mov	w5, 0
	str	wzr, [x20, 1024]
	ldr	w2, [x21, 8]
	ldr	w3, [x21, 20]
	cmp	w2, wzr
	ldr	w2, [x21, 16]
	csel	w11, w11, w12, ne
	sub	w3, w3, #1
	sub	w2, w2, #1
	add	w3, w3, w11
	add	w2, w2, w11
	mov	w12, 0
	udiv	w3, w3, w11
	udiv	w2, w2, w11
	mov	w11, 0
	mul	w2, w2, w3
	ldr	w3, [x21, 520]
	udiv	w2, w3, w2
	mov	w3, 0
	bfi	w4, w2, 0, 20
	str	w4, [x23, 588]
	mov	w4, 0
	ldr	w2, [x0, 8]
	bfi	w10, w2, 16, 5
	ldr	w2, [x0, 12]
	bfi	w10, w2, 0, 10
	str	w10, [x20, 1536]
	mov	w2, 0
	ldr	w10, [x22, 8]
	bfi	w8, w10, 16, 5
	ldr	w10, [x0, 16]
	bfi	w8, w10, 0, 8
	str	w8, [x20, 1540]
	mov	w10, 0
	ldr	w8, [x0, 20]
	bfi	w9, w8, 16, 5
	ldr	w8, [x0, 24]
	bfi	w9, w8, 0, 10
	str	w9, [x20, 1544]
	mov	w9, 0
	ldr	w8, [x0, 28]
	bfi	w7, w8, 16, 5
	ldr	w8, [x22, 12]
	bfi	w7, w8, 0, 8
	str	w7, [x20, 1548]
	mov	w8, 0
	ldr	w7, [x0, 32]
	bfi	w6, w7, 16, 5
	ldr	w7, [x0, 36]
	bfi	w6, w7, 0, 10
	str	w6, [x20, 1552]
	mov	w7, 0
	ldr	w6, [x22, 16]
	bfi	w5, w6, 16, 5
	ldr	w6, [x22, 20]
	bfi	w5, w6, 0, 8
	str	w5, [x20, 1556]
	mov	w6, 0
	ldr	w5, [x0, 40]
	bfi	w4, w5, 16, 5
	ldr	w5, [x0, 44]
	bfi	w4, w5, 0, 10
	str	w4, [x20, 1560]
	mov	w5, 0
	ldr	w4, [x22, 24]
	bfi	w3, w4, 16, 5
	ldr	w4, [x22, 28]
	bfi	w3, w4, 0, 8
	str	w3, [x20, 1564]
	mov	w4, 0
	mov	w3, 0
	ldr	w17, [x0, 48]
	bfi	w2, w17, 12, 4
	ldr	w17, [x0, 52]
	bfi	w2, w17, 8, 4
	ldr	w17, [x0, 56]
	bfi	w2, w17, 4, 4
	ldr	w17, [x0, 60]
	bfi	w2, w17, 0, 4
	ldr	w17, [x0, 64]
	bfi	w2, w17, 28, 4
	ldr	w17, [x22, 32]
	bfi	w2, w17, 24, 4
	ldr	w17, [x0, 68]
	bfi	w2, w17, 20, 4
	ldr	w17, [x0, 72]
	bfi	w2, w17, 16, 4
	str	w2, [x20, 1568]
	mov	w2, 0
	mov	w17, 0
	ldr	w24, [x0, 76]
	bfi	w18, w24, 12, 4
	ldr	w24, [x0, 80]
	bfi	w18, w24, 8, 4
	ldr	w24, [x0, 84]
	bfi	w18, w24, 4, 4
	ldr	w24, [x0, 88]
	bfi	w18, w24, 0, 4
	ldr	w24, [x0, 92]
	bfi	w18, w24, 28, 4
	ldr	w24, [x0, 96]
	bfi	w18, w24, 24, 4
	ldr	w24, [x22, 36]
	bfi	w18, w24, 20, 4
	ldr	w24, [x0, 100]
	bfi	w18, w24, 16, 4
	str	w18, [x20, 1572]
	mov	w24, 0
	ldr	w18, [x0, 104]
	bfi	w16, w18, 12, 4
	ldr	w18, [x0, 108]
	bfi	w16, w18, 8, 4
	ldr	w18, [x0, 112]
	bfi	w16, w18, 4, 4
	ldr	w18, [x0, 116]
	bfi	w16, w18, 0, 4
	ldr	w18, [x0, 120]
	bfi	w16, w18, 28, 4
	ldr	w18, [x0, 124]
	bfi	w16, w18, 24, 4
	ldr	w18, [x22, 40]
	bfi	w16, w18, 20, 4
	ldr	w18, [x0, 128]
	bfi	w16, w18, 16, 4
	str	w16, [x20, 1576]
	ldr	w16, [x0, 132]
	bfi	w15, w16, 12, 4
	ldr	w16, [x22, 44]
	bfi	w15, w16, 8, 4
	ldr	w16, [x0, 136]
	bfi	w15, w16, 4, 4
	ldr	w16, [x0, 140]
	bfi	w15, w16, 0, 4
	ldr	w16, [x0, 144]
	bfi	w15, w16, 28, 4
	ldr	w16, [x0, 148]
	bfi	w15, w16, 24, 4
	ldr	w16, [x0, 152]
	bfi	w15, w16, 20, 4
	ldr	w16, [x0, 156]
	bfi	w15, w16, 16, 4
	str	w15, [x20, 1580]
	mov	w16, 0
	ldr	w15, [x0, 160]
	bfi	w14, w15, 12, 4
	ldr	w15, [x0, 164]
	bfi	w14, w15, 8, 4
	ldr	w15, [x22, 48]
	bfi	w14, w15, 4, 4
	ldr	w15, [x0, 168]
	bfi	w14, w15, 0, 4
	ldr	w15, [x0, 172]
	bfi	w14, w15, 28, 4
	ldr	w15, [x0, 176]
	bfi	w14, w15, 24, 4
	ldr	w15, [x0, 180]
	bfi	w14, w15, 20, 4
	ldr	w15, [x0, 184]
	bfi	w14, w15, 16, 4
	str	w14, [x20, 1584]
	mov	w15, 0
	ldr	w14, [x0, 188]
	bfi	w13, w14, 12, 4
	ldr	w14, [x0, 192]
	bfi	w13, w14, 8, 4
	ldr	w14, [x22, 52]
	bfi	w13, w14, 4, 4
	ldr	w14, [x0, 196]
	bfi	w13, w14, 0, 4
	ldr	w14, [x0, 200]
	bfi	w13, w14, 28, 4
	ldr	w14, [x0, 204]
	bfi	w13, w14, 24, 4
	ldr	w14, [x0, 208]
	bfi	w13, w14, 20, 4
	ldr	w14, [x0, 212]
	bfi	w13, w14, 16, 4
	str	w13, [x20, 1588]
	mov	w14, 0
	ldr	w13, [x0, 216]
	bfi	w12, w13, 12, 4
	ldr	w13, [x22, 56]
	bfi	w12, w13, 8, 4
	ldr	w13, [x0, 220]
	bfi	w12, w13, 4, 4
	ldr	w13, [x0, 224]
	bfi	w12, w13, 0, 4
	ldr	w13, [x0, 228]
	bfi	w12, w13, 28, 4
	ldr	w13, [x0, 232]
	bfi	w12, w13, 24, 4
	ldr	w13, [x0, 236]
	bfi	w12, w13, 20, 4
	ldr	w13, [x0, 240]
	bfi	w12, w13, 16, 4
	str	w12, [x20, 1592]
	mov	w13, 0
	ldr	w12, [x0, 244]
	bfi	w11, w12, 12, 4
	ldr	w12, [x0, 248]
	bfi	w11, w12, 8, 4
	ldr	w12, [x0, 252]
	bfi	w11, w12, 4, 4
	ldr	w12, [x0, 256]
	bfi	w11, w12, 0, 4
	ldr	w12, [x0, 260]
	bfi	w11, w12, 28, 4
	ldr	w12, [x0, 264]
	bfi	w11, w12, 24, 4
	ldr	w12, [x0, 268]
	bfi	w11, w12, 20, 4
	ldr	w12, [x0, 272]
	bfi	w11, w12, 16, 4
	str	w11, [x20, 1596]
	mov	w12, 0
	ldr	w11, [x0, 276]
	bfi	w10, w11, 12, 4
	ldr	w11, [x0, 280]
	bfi	w10, w11, 8, 4
	ldr	w11, [x0, 284]
	bfi	w10, w11, 4, 4
	ldr	w11, [x0, 288]
	bfi	w10, w11, 0, 4
	ldr	w11, [x0, 292]
	bfi	w10, w11, 28, 4
	ldr	w11, [x0, 296]
	bfi	w10, w11, 24, 4
	ldr	w11, [x0, 300]
	bfi	w10, w11, 20, 4
	ldr	w11, [x0, 304]
	bfi	w10, w11, 16, 4
	str	w10, [x20, 1600]
	mov	w11, 0
	ldr	w10, [x0, 308]
	bfi	w9, w10, 0, 3
	ldr	w10, [x0, 312]
	bfi	w9, w10, 3, 7
	ldr	w10, [x0, 316]
	bfi	w9, w10, 10, 3
	ldr	w10, [x0, 320]
	bfi	w9, w10, 13, 5
	ldr	w10, [x0, 324]
	bfi	w9, w10, 18, 4
	ldr	w10, [x0, 328]
	bfi	w9, w10, 22, 4
	ldr	w10, [x0, 332]
	bfi	w9, w10, 26, 4
	str	w9, [x20, 1604]
	mov	w10, 0
	mov	w9, 0
	ldr	w18, [x0, 336]
	bfi	w8, w18, 0, 3
	ldr	w18, [x0, 340]
	bfi	w8, w18, 3, 7
	ldr	w18, [x0, 344]
	bfi	w8, w18, 10, 3
	ldr	w18, [x0, 348]
	bfi	w8, w18, 13, 5
	ldr	w18, [x0, 352]
	bfi	w8, w18, 18, 4
	ldr	w18, [x0, 356]
	bfi	w8, w18, 22, 4
	ldr	w18, [x0, 360]
	bfi	w8, w18, 26, 4
	str	w8, [x20, 1608]
	mov	w18, 0
	ldr	w8, [x0, 364]
	bfi	w7, w8, 0, 3
	ldr	w8, [x0, 368]
	bfi	w7, w8, 3, 7
	ldr	w8, [x0, 372]
	bfi	w7, w8, 10, 3
	ldr	w8, [x0, 376]
	bfi	w7, w8, 13, 5
	ldr	w8, [x0, 380]
	bfi	w7, w8, 18, 4
	ldr	w8, [x0, 384]
	bfi	w7, w8, 22, 4
	ldr	w8, [x0, 388]
	bfi	w7, w8, 26, 4
	str	w7, [x20, 1612]
	mov	w8, 0
	ldr	w7, [x0, 656]
	bfi	w6, w7, 0, 3
	ldr	w7, [x0, 660]
	bfi	w6, w7, 3, 7
	ldr	w7, [x0, 664]
	bfi	w6, w7, 10, 3
	ldr	w7, [x0, 668]
	bfi	w6, w7, 13, 5
	ldr	w7, [x0, 672]
	bfi	w6, w7, 18, 4
	ldr	w7, [x0, 676]
	bfi	w6, w7, 22, 4
	ldr	w7, [x0, 680]
	bfi	w6, w7, 26, 4
	str	w6, [x20, 1616]
	ldr	w6, [x0, 684]
	bfi	w5, w6, 0, 3
	ldr	w6, [x0, 688]
	bfi	w5, w6, 3, 7
	ldr	w6, [x0, 692]
	bfi	w5, w6, 10, 3
	ldr	w6, [x0, 696]
	bfi	w5, w6, 13, 5
	ldr	w6, [x0, 700]
	bfi	w5, w6, 18, 4
	ldr	w6, [x0, 704]
	bfi	w5, w6, 22, 4
	ldr	w6, [x0, 708]
	bfi	w5, w6, 26, 4
	str	w5, [x20, 1620]
	mov	w6, 0
	mov	w5, 0
	ldr	w7, [x22, 68]
	bfi	w4, w7, 0, 3
	ldr	w7, [x0, 712]
	bfi	w4, w7, 3, 7
	ldr	w7, [x0, 716]
	bfi	w4, w7, 10, 3
	ldr	w7, [x0, 720]
	bfi	w4, w7, 13, 5
	ldr	w7, [x0, 724]
	bfi	w4, w7, 18, 4
	ldr	w7, [x0, 728]
	bfi	w4, w7, 22, 4
	ldr	w7, [x0, 732]
	bfi	w4, w7, 26, 4
	str	w4, [x20, 1624]
	mov	w4, 0
	ldr	w7, [x0, 736]
	bfi	w3, w7, 0, 3
	ldr	w7, [x0, 740]
	bfi	w3, w7, 3, 7
	ldr	w7, [x0, 744]
	bfi	w3, w7, 10, 3
	ldr	w7, [x0, 748]
	bfi	w3, w7, 13, 5
	ldr	w7, [x0, 752]
	bfi	w3, w7, 18, 4
	ldr	w7, [x0, 756]
	bfi	w3, w7, 22, 4
	ldr	w7, [x0, 760]
	bfi	w3, w7, 26, 4
	str	w3, [x20, 1628]
	mov	w7, 0
	ldr	w3, [x0, 392]
	bfi	w2, w3, 0, 4
	ldr	w3, [x0, 396]
	bfi	w2, w3, 4, 4
	ldr	w3, [x0, 400]
	bfi	w2, w3, 8, 4
	ldr	w3, [x0, 404]
	bfi	w2, w3, 12, 4
	ldr	w3, [x0, 408]
	bfi	w2, w3, 16, 4
	ldr	w3, [x0, 412]
	bfi	w2, w3, 20, 4
	ldr	w3, [x0, 416]
	bfi	w2, w3, 24, 4
	ldr	w3, [x0, 420]
	bfi	w2, w3, 28, 4
	str	w2, [x20, 1632]
	mov	w3, 0
	ldr	w2, [x0, 424]
	bfi	w17, w2, 0, 4
	ldr	w2, [x0, 428]
	bfi	w17, w2, 4, 4
	ldr	w2, [x0, 432]
	bfi	w17, w2, 8, 4
	ldr	w2, [x0, 436]
	bfi	w17, w2, 12, 4
	ldr	w2, [x0, 440]
	bfi	w17, w2, 16, 4
	ldr	w2, [x0, 444]
	bfi	w17, w2, 20, 4
	str	w17, [x20, 1636]
	mov	w2, 0
	ldr	w17, [x0, 448]
	bfi	w18, w17, 0, 10
	ldr	w17, [x0, 452]
	bfi	w18, w17, 16, 5
	str	w18, [x20, 1640]
	ldr	w17, [x22, 60]
	mov	w18, w24
	bfi	w26, w17, 0, 8
	ldr	w17, [x22, 64]
	bfi	w26, w17, 16, 5
	str	w26, [x20, 1644]
	mov	w26, 0
	ldr	w17, [x0, 456]
	bfi	w28, w17, 0, 10
	ldr	w17, [x0, 460]
	bfi	w28, w17, 16, 5
	str	w28, [x20, 1648]
	mov	w17, 0
	mov	w28, 0
	ldr	w24, [x0, 464]
	bfi	w18, w24, 0, 8
	ldr	w24, [x0, 468]
	bfi	w18, w24, 16, 5
	str	w18, [x20, 1652]
	mov	w18, 0
	ldr	w24, [x0, 472]
	bfi	w18, w24, 0, 10
	ldr	w24, [x0, 476]
	bfi	w18, w24, 16, 5
	str	w18, [x20, 1656]
	mov	w18, 0
	ldr	w24, [x0, 480]
	bfi	w18, w24, 0, 8
	ldr	w24, [x0, 484]
	bfi	w18, w24, 16, 5
	str	w18, [x20, 1660]
	mov	w24, 0
	ldr	w18, [x0, 764]
	bfi	w16, w18, 0, 4
	ldr	w18, [x0, 768]
	bfi	w16, w18, 4, 4
	ldr	w18, [x0, 772]
	bfi	w16, w18, 8, 4
	ldr	w18, [x0, 776]
	bfi	w16, w18, 12, 4
	ldr	w18, [x0, 780]
	bfi	w16, w18, 16, 4
	ldr	w18, [x0, 784]
	bfi	w16, w18, 20, 4
	str	w16, [x20, 1664]
	ldr	w16, [x22, 72]
	bfi	w25, w16, 0, 12
	ldr	w16, [x22, 76]
	bfi	w25, w16, 12, 12
	ldr	w16, [x0, 788]
	bfi	w25, w16, 24, 8
	str	w25, [x20, 1668]
	mov	w25, 0
	mov	w16, 0
	ldr	w18, [x0, 792]
	bfi	w24, w18, 0, 12
	ldr	w18, [x0, 796]
	bfi	w24, w18, 12, 12
	ldr	w18, [x0, 800]
	bfi	w24, w18, 24, 8
	str	w24, [x20, 1672]
	mov	w24, 257
	ldr	w18, [x22, 80]
	movk	w24, 0xc8, lsl 16
	bfi	w30, w18, 0, 12
	ldr	w18, [x0, 804]
	bfi	w30, w18, 12, 12
	ldr	w18, [x0, 808]
	bfi	w30, w18, 24, 8
	str	w30, [x20, 1676]
	mov	w18, 0
	ldr	w30, [x0, 812]
	bfi	w18, w30, 0, 8
	ldr	w30, [x0, 816]
	bfi	w18, w30, 8, 8
	ldr	w30, [x0, 820]
	bfi	w18, w30, 16, 8
	str	w18, [x20, 1680]
	ldr	w18, [x0, 488]
	bfi	w15, w18, 0, 1
	ldr	w18, [x0, 492]
	bfi	w15, w18, 1, 3
	ldr	w18, [x0, 496]
	bfi	w15, w18, 4, 6
	ldr	w18, [x0, 500]
	bfi	w15, w18, 10, 5
	ldr	w18, [x0, 504]
	bfi	w15, w18, 15, 6
	ldr	w18, [x0, 508]
	bfi	w15, w18, 21, 5
	str	w15, [x20, 1684]
	ldr	w15, [x0, 512]
	bfi	w14, w15, 0, 1
	ldr	w15, [x0, 516]
	bfi	w14, w15, 1, 3
	ldr	w15, [x0, 520]
	bfi	w14, w15, 4, 6
	ldr	w15, [x0, 524]
	bfi	w14, w15, 10, 5
	ldr	w15, [x0, 528]
	bfi	w14, w15, 15, 6
	ldr	w15, [x0, 532]
	bfi	w14, w15, 21, 5
	str	w14, [x20, 1688]
	ldr	w14, [x0, 536]
	bfi	w13, w14, 0, 1
	ldr	w14, [x0, 540]
	bfi	w13, w14, 1, 3
	ldr	w14, [x0, 544]
	bfi	w13, w14, 4, 6
	ldr	w14, [x0, 548]
	bfi	w13, w14, 10, 5
	ldr	w14, [x0, 552]
	bfi	w13, w14, 15, 6
	ldr	w14, [x0, 556]
	bfi	w13, w14, 21, 5
	str	w13, [x20, 1692]
	ldr	w13, [x0, 560]
	bfi	w12, w13, 0, 1
	ldr	w13, [x0, 564]
	bfi	w12, w13, 1, 3
	ldr	w13, [x0, 568]
	bfi	w12, w13, 4, 6
	ldr	w13, [x0, 572]
	bfi	w12, w13, 10, 5
	ldr	w13, [x0, 576]
	bfi	w12, w13, 15, 6
	ldr	w13, [x0, 580]
	bfi	w12, w13, 21, 5
	str	w12, [x20, 1696]
	ldr	w12, [x0, 584]
	bfi	w11, w12, 0, 1
	ldr	w12, [x0, 588]
	bfi	w11, w12, 1, 3
	ldr	w12, [x0, 592]
	bfi	w11, w12, 4, 6
	ldr	w12, [x0, 596]
	bfi	w11, w12, 10, 5
	ldr	w12, [x0, 600]
	bfi	w11, w12, 15, 6
	ldr	w12, [x0, 604]
	bfi	w11, w12, 21, 5
	str	w11, [x20, 1700]
	ldr	w11, [x0, 608]
	bfi	w10, w11, 0, 1
	ldr	w11, [x0, 612]
	bfi	w10, w11, 1, 3
	ldr	w11, [x0, 616]
	bfi	w10, w11, 4, 6
	ldr	w11, [x0, 620]
	bfi	w10, w11, 10, 5
	ldr	w11, [x0, 624]
	bfi	w10, w11, 15, 6
	ldr	w11, [x0, 628]
	bfi	w10, w11, 21, 5
	str	w10, [x20, 1704]
	mov	w11, -16711936
	ldr	w10, [x0, 632]
	bfi	w9, w10, 0, 1
	ldr	w10, [x0, 636]
	bfi	w9, w10, 1, 3
	ldr	w10, [x0, 640]
	bfi	w9, w10, 4, 6
	ldr	w10, [x0, 644]
	bfi	w9, w10, 10, 5
	ldr	w10, [x0, 648]
	bfi	w9, w10, 15, 6
	ldr	w10, [x0, 652]
	bfi	w9, w10, 21, 5
	str	w9, [x20, 1708]
	mov	w10, 0
	ldr	w9, [x22, 5720]
	bfi	w10, w9, 20, 8
	ldr	w9, [x21, 44]
	bfi	w10, w9, 28, 1
	stp	w10, w11, [x20, 8]
	mov	w10, 0
	ldr	w9, [x0, 1144]
	bfi	w10, w9, 0, 1
	str	w10, [x20, 1824]
	mov	w10, 0
	ldr	w9, [x0, 1148]
	bfi	w10, w9, 0, 16
	str	w10, [x20, 1828]
	mov	w10, 0
	ldr	w9, [x0, 1152]
	bfi	w10, w9, 0, 16
	str	w10, [x20, 1832]
	ldr	w9, [x0, 1156]
	mov	w10, 0
	bfi	w10, w9, 0, 16
	str	w10, [x20, 1836]
	ldr	w9, [x0, 1160]
	bfi	w6, w9, 18, 9
	ldr	w9, [x0, 1164]
	bfi	w6, w9, 9, 9
	ldr	w9, [x0, 1168]
	bfi	w6, w9, 0, 9
	str	w6, [x20, 1844]
	ldr	w6, [x0, 1172]
	bfi	w5, w6, 16, 8
	ldr	w6, [x0, 1176]
	bfi	w5, w6, 8, 8
	ldr	w6, [x0, 1180]
	bfi	w5, w6, 0, 8
	str	w5, [x20, 1848]
	ldr	w5, [x0, 1184]
	bfi	w4, w5, 8, 4
	ldr	w5, [x0, 1188]
	bfi	w4, w5, 4, 4
	ldr	w5, [x0, 1192]
	bfi	w4, w5, 0, 4
	mov	w5, 3
	bfi	w4, w5, 20, 8
	mov	w5, 20
	bfi	w4, w5, 12, 8
	str	w4, [x20, 1852]
	ldrh	w4, [x0, 1292]
	str	w4, [x20, 1856]
	ldr	w4, [x0, 1308]
	bfi	w7, w4, 0, 8
	ldr	w4, [x0, 1304]
	bfi	w7, w4, 8, 8
	ldr	w4, [x0, 1300]
	bfi	w7, w4, 16, 8
	ldr	w4, [x0, 1296]
	bfi	w7, w4, 24, 8
	str	w7, [x20, 1860]
	ldr	w4, [x0, 1196]
	bfi	w8, w4, 24, 8
	ldr	w4, [x0, 1200]
	bfi	w8, w4, 16, 8
	ldr	w4, [x0, 1204]
	bfi	w8, w4, 8, 8
	ldr	w4, [x0, 1208]
	bfi	w8, w4, 0, 8
	str	w8, [x20, 1872]
	ldr	w4, [x0, 1212]
	bfi	w3, w4, 0, 8
	ldr	w4, [x0, 1216]
	bfi	w3, w4, 8, 8
	ldr	w4, [x0, 1220]
	bfi	w3, w4, 16, 1
	ldr	w4, [x0, 1336]
	bfi	w3, w4, 17, 1
	str	w3, [x20, 1876]
	mov	w4, 0
	ldr	w3, [x0, 1224]
	bfi	w4, w3, 0, 16
	ldr	w3, [x0, 1228]
	bfi	w4, w3, 16, 16
	str	w4, [x20, 1880]
	mov	w4, 0
	ldr	w3, [x22, 488]
	bfi	w2, w3, 22, 9
	ldr	w3, [x22, 492]
	bfi	w2, w3, 17, 5
	ldr	w3, [x22, 496]
	bfi	w2, w3, 9, 8
	ldr	w3, [x22, 516]
	bfi	w2, w3, 0, 9
	str	w2, [x20, 1884]
	mov	w3, 0
	ldr	w2, [x22, 512]
	bfi	w3, w2, 8, 14
	ldr	w2, [x0, 1232]
	bfi	w3, w2, 0, 8
	str	w3, [x20, 1792]
	mov	w3, 0
	ldr	w2, [x22, 500]
	bfi	w26, w2, 16, 8
	ldr	w2, [x22, 504]
	bfi	w26, w2, 8, 8
	ldr	w2, [x22, 508]
	bfi	w26, w2, 0, 8
	str	w26, [x20, 1796]
	ldr	w2, [x0, 1240]
	bfi	w17, w2, 17, 1
	ldr	w2, [x0, 1244]
	bfi	w17, w2, 12, 2
	ldr	w2, [x0, 1248]
	bfi	w17, w2, 4, 4
	ldr	w2, [x0, 1252]
	bfi	w17, w2, 0, 4
	str	w17, [x20, 1800]
	ldr	w2, [x0, 1256]
	bfi	w28, w2, 0, 10
	ldr	w2, [x0, 1260]
	bfi	w28, w2, 16, 9
	str	w28, [x20, 1808]
	ldr	w2, [x0, 1264]
	bfi	w3, w2, 0, 10
	ldr	w2, [x0, 1268]
	bfi	w3, w2, 16, 9
	str	w3, [x20, 1812]
	mov	w3, 0
	ldr	w2, [x0, 1272]
	bfi	w3, w2, 0, 10
	ldr	w2, [x0, 1276]
	bfi	w3, w2, 16, 9
	str	w3, [x20, 1816]
	mov	w3, 0
	ldr	w2, [x0, 1280]
	bfi	w3, w2, 0, 10
	ldr	w2, [x0, 1284]
	bfi	w3, w2, 16, 9
	str	w3, [x20, 1820]
	mov	w3, 0
	ldr	w2, [x0, 1288]
	bfi	w4, w2, 0, 16
	str	w4, [x20, 1804]
	ldr	w2, [x0, 1312]
	mov	w4, 0
	bfi	w3, w2, 0, 13
	ldr	w2, [x0, 1316]
	bfi	w3, w2, 13, 1
	str	w3, [x20, 36]
	mov	w3, 0
	ldr	w2, [x0, 1320]
	bfi	w4, w2, 0, 18
	str	w4, [x20, 40]
	mov	w4, 0
	ldr	w2, [x0, 1324]
	bfi	w4, w2, 0, 18
	str	w4, [x20, 44]
	ldr	w2, [x0, 1348]
	bfi	w3, w2, 16, 7
	ldr	w2, [x0, 1352]
	bfi	w3, w2, 23, 7
	str	w3, [x23, 1792]
	ldr	w2, [x0, 1340]
	bfi	w25, w2, 0, 8
	ldr	w2, [x0, 1344]
	bfi	w25, w2, 8, 8
	ldr	w2, [x0, 1328]
	bfi	w25, w2, 16, 8
	str	w25, [x23, 1796]
	ldr	w2, [x0, 1332]
	bfi	w16, w2, 12, 8
	ldr	w2, [x0, 1356]
	ldr	w0, [x0, 1360]
	bfi	w16, w2, 8, 4
	bfi	w16, w0, 0, 8
	str	w16, [x23, 1800]
	str	w24, [x23, 1804]
	ldr	w0, [x21, 8]
	cbnz	w0, .L59
	mov	w2, 23
	mov	w3, 15
	bfi	w0, w2, 0, 5
	bfi	w0, w3, 5, 5
	bfi	w0, w2, 10, 5
	bfi	w0, w3, 15, 5
	and	w0, w0, -1048577
	str	w0, [x20, 24]
.L60:
	mov	w0, 2
	mov	w4, 16
	str	w0, [x20, 548]
	mov	w0, 0
	mov	w2, 10
	bfi	w0, w4, 6, 6
	str	wzr, [x20, 552]
	bfi	w0, w2, 0, 6
	str	w0, [x20, 556]
	mov	w3, 64
	ldr	x0, [x29, 104]
	mov	w6, 0
	ldr	w2, [x21, 532]
	ldr	w5, [x21, 528]
	add	x0, x0, 2432
	ubfiz	w2, w2, 8, 6
	orr	w2, w2, w3
	bfi	w2, w5, 0, 6
	ldr	w5, [x0, 952]
	bfi	w2, w5, 16, 6
	ldr	w5, [x0, 924]
	bfi	w2, w5, 24, 4
	str	w2, [x23, 3076]
	mov	w5, 0
	ldr	w2, [x21, 8]
	cmp	w2, wzr
	csel	w4, w3, w4, ne
	ldp	w2, w3, [x21, 16]
	sub	w2, w2, #1
	sub	w3, w3, #1
	add	w2, w2, w4
	add	w3, w3, w4
	udiv	w2, w2, w4
	udiv	w3, w3, w4
	mov	w4, 0
	mul	w2, w2, w3
	ldr	w3, [x21, 520]
	udiv	w2, w3, w2
	mov	w3, 0
	bfi	w5, w2, 0, 16
	ldr	w2, [x0, 940]
	bfi	w5, w2, 16, 6
	str	w5, [x23, 3080]
	mov	w5, 0
	ldr	w2, [x22, 100]
	bfi	w6, w2, 0, 6
	ldr	w2, [x0, 932]
	bfi	w6, w2, 24, 6
	ldr	w2, [x0, 936]
	bfi	w6, w2, 16, 6
	ldr	w2, [x0, 944]
	bfi	w6, w2, 8, 6
	str	w6, [x23, 3084]
	mov	w2, 0
	ldr	w6, [x22, 116]
	bfi	w5, w6, 24, 8
	ldr	w6, [x22, 112]
	bfi	w5, w6, 16, 8
	ldr	w6, [x22, 108]
	bfi	w5, w6, 8, 8
	ldr	w6, [x22, 104]
	bfi	w5, w6, 0, 8
	str	w5, [x23, 3088]
	mov	w5, 0
	mov	w6, 0
	ldr	w7, [x22, 132]
	bfi	w4, w7, 24, 8
	ldr	w7, [x22, 128]
	bfi	w4, w7, 16, 8
	ldr	w7, [x22, 124]
	bfi	w4, w7, 8, 8
	ldr	w7, [x22, 120]
	bfi	w4, w7, 0, 8
	str	w4, [x23, 3092]
	mov	w4, 0
	ldr	w7, [x22, 148]
	bfi	w3, w7, 24, 8
	ldr	w7, [x22, 144]
	bfi	w3, w7, 16, 8
	ldr	w7, [x22, 140]
	bfi	w3, w7, 8, 8
	ldr	w7, [x22, 136]
	bfi	w3, w7, 0, 8
	str	w3, [x23, 3096]
	ldr	w3, [x22, 164]
	bfi	w2, w3, 24, 8
	ldr	w3, [x22, 160]
	bfi	w2, w3, 16, 8
	ldr	w3, [x22, 156]
	bfi	w2, w3, 8, 8
	ldr	w3, [x22, 152]
	bfi	w2, w3, 0, 8
	str	w2, [x23, 3072]
	ldr	w2, [x0, 968]
	bfi	w5, w2, 0, 4
	ldr	w2, [x0, 972]
	bfi	w5, w2, 4, 4
	str	w5, [x23, 3100]
	ldr	w2, [x0, 916]
	bfi	w6, w2, 0, 4
	str	w6, [x23, 3104]
	ldr	w2, [x0, 912]
	ldr	w0, [x0, 920]
	bfi	w4, w2, 0, 4
	bfi	w4, w0, 4, 4
	str	w4, [x23, 3108]
	ldr	w0, [x21, 8]
	cbnz	w0, .L62
	mov	w2, 2
	bfi	w0, w2, 0, 4
.L63:
	str	w0, [x23, 3112]
	mov	w5, 0
	ldr	x0, [x29, 104]
	ldr	x2, [x29, 96]
	add	x4, x0, 2432
	mov	w0, 0
	ldr	w3, [x4, 844]
	bfi	w0, w3, 0, 2
	ldr	w3, [x4, 848]
	bfi	w0, w3, 2, 2
	ldr	w3, [x4, 852]
	bfi	w0, w3, 4, 2
	ldr	w3, [x4, 856]
	bfi	w0, w3, 6, 2
	ldr	w3, [x4, 860]
	bfi	w0, w3, 8, 2
	ldr	w3, [x4, 864]
	bfi	w0, w3, 10, 2
	ldr	w3, [x4, 868]
	bfi	w0, w3, 12, 2
	ldr	w3, [x4, 872]
	bfi	w0, w3, 14, 2
	ldr	w3, [x4, 876]
	bfi	w0, w3, 16, 2
	ldr	w3, [x4, 880]
	bfi	w0, w3, 18, 2
	ldr	w3, [x4, 884]
	bfi	w0, w3, 20, 2
	ldr	w3, [x4, 888]
	bfi	w0, w3, 22, 2
	ldr	w3, [x4, 892]
	bfi	w0, w3, 24, 2
	ldr	w3, [x4, 896]
	bfi	w0, w3, 26, 2
	ldr	w3, [x4, 900]
	bfi	w0, w3, 28, 2
	ldr	w3, [x4, 904]
	bfi	w0, w3, 30, 2
	str	w0, [x23, 3116]
	mov	w0, 0
	ldr	w3, [x4, 908]
	bfi	w0, w3, 0, 5
	str	w0, [x23, 3120]
	add	x3, x20, 1104
	add	x0, x27, 928
	ldr	w6, [x4, 956]
	bfi	w5, w6, 24, 4
	ldr	w6, [x4, 960]
	bfi	w5, w6, 28, 4
	ldr	w6, [x4, 964]
	bfi	w5, w6, 16, 6
	ldr	w6, [x4, 928]
	ldr	w4, [x4, 948]
	bfi	w5, w6, 8, 4
	bfi	w5, w4, 0, 6
	str	w5, [x23, 3124]
	.p2align 2
.L64:
	ldr	w4, [x2], 4
	bfi	w19, w4, 0, 20
	cmp	x0, x2
	str	w19, [x3], 4
	bne	.L64
	add	x2, x20, 1280
	.p2align 2
.L65:
	ldr	w3, [x0], 4
	bfi	w19, w3, 0, 20
	cmp	x1, x0
	str	w19, [x2], 4
	bne	.L65
	add	x3, x20, 512
	str	wzr, [x23, 3660]
	add	x4, x20, 512
	str	wzr, [x20, 564]
	str	wzr, [x20, 568]
	add	x5, x20, 512
	str	wzr, [x20, 572]
	mov	w2, -1
	ldr	x0, [x29, 104]
	mov	w1, 7
	stp	wzr, wzr, [x3, 68]
	stp	wzr, wzr, [x3, 76]
	stp	w2, w1, [x4, 84]
	stp	w2, w1, [x4, 92]
	stp	w2, w1, [x5, 100]
	stp	w2, w1, [x5, 108]
	mov	w1, 13
	str	w1, [x20, 576]
	mov	w2, 0
	mov	w1, 0
	ldr	w3, [x0, 3812]
	add	x0, x0, 2432
	bfi	w2, w3, 0, 1
	str	w2, [x20, 120]
	ldr	w2, [x21, 152]
	str	w2, [x20, 96]
	ldr	w2, [x21, 156]
	str	w2, [x20, 100]
	ldr	w2, [x21, 160]
	str	w2, [x20, 104]
	ldr	w2, [x21, 164]
	str	w2, [x20, 108]
	ldr	w2, [x21, 168]
	str	w2, [x20, 112]
	ldr	w2, [x21, 172]
	str	w2, [x20, 116]
	ldr	w2, [x0, 824]
	bfi	w1, w2, 0, 16
	ldr	w2, [x0, 828]
	bfi	w1, w2, 16, 16
	str	w1, [x20, 1728]
	mov	w2, 0
	mov	w1, 0
	ldr	w3, [x0, 840]
	bfi	w2, w3, 16, 16
	str	w2, [x20, 1732]
	ldr	w2, [x0, 832]
	ldr	w0, [x0, 836]
	bfi	w1, w2, 0, 16
	bfi	w1, w0, 16, 16
	str	w1, [x20, 1736]
	ldr	w1, [x21, 8]
	ldr	x0, [x21, 688]
	cmp	w1, 2
	beq	.L116
	ldr	w1, [x21, 584]
	mov	w2, 0
	str	w1, [x0, 256]
	ldr	w1, [x21, 588]
	str	w1, [x0, 260]
	ldr	w1, [x21, 592]
	str	w1, [x0, 264]
	ldr	w1, [x21, 596]
	str	w1, [x0, 268]
	ldr	w1, [x21, 600]
	str	w1, [x0, 272]
	ldr	w1, [x21, 604]
	str	w1, [x0, 276]
	ldr	w1, [x21, 608]
	str	w1, [x0, 280]
	ldr	w1, [x21, 612]
	str	w1, [x0, 284]
	ldr	w4, [x21, 616]
	str	wzr, [x0, 292]
	sub	w3, w4, #1
	lsr	w1, w4, 16
	bfi	w2, w3, 16, 7
	lsr	w3, w4, 8
	sub	w3, w3, #1
	sub	w1, w1, #1
	bfi	w2, w3, 8, 6
	bfi	w2, w1, 0, 6
	str	w2, [x0, 288]
.L74:
	ldr	w1, [x21, 8]
	cmp	w1, 2
	beq	.L117
	ldr	w1, [x22, 5756]
	mov	w2, 0
	str	w1, [x0, 296]
	ldr	w1, [x22, 5760]
	str	w1, [x0, 300]
	ldr	w1, [x22, 5764]
	str	w1, [x0, 304]
	ldr	w1, [x22, 5768]
	str	w1, [x0, 308]
	ldr	w1, [x22, 5772]
	str	w1, [x0, 312]
	ldr	w1, [x22, 5776]
	str	w1, [x0, 316]
	ldr	w1, [x22, 5780]
	str	w1, [x0, 320]
	ldr	w1, [x22, 5784]
	str	w1, [x0, 324]
	ldr	w5, [x22, 5752]
	sub	w4, w5, #1
	lsr	w3, w5, 8
	bfi	w2, w4, 16, 7
	sub	w3, w3, #1
	lsr	w1, w5, 16
	bfi	w2, w3, 8, 6
	sub	w1, w1, #1
	bfi	w2, w1, 0, 6
	str	w2, [x0, 328]
.L81:
	ldr	w1, [x21, 244]
	mov	w0, 0
	str	w1, [x20, 68]
	str	w0, [x23, 9232]
	ldr	x0, [x29, 104]
	ldr	w0, [x0, 3920]
	str	w0, [x23, 9236]
	ldr	w0, [x21, 516]
	cmp	w0, wzr
	cset	w0, ne
	str	w0, [x20, 76]
	ldr	w0, [x21, 664]
	str	w0, [x20, 80]
	ldr	w0, [x21, 668]
	str	w0, [x20, 84]
	ldr	w0, [x21, 672]
	str	w0, [x20, 88]
	ldr	w2, [x21, 672]
	cbz	w2, .L84
	ldr	w2, [x21, 676]
.L84:
	ldr	x0, [x29, 104]
	mov	w3, -85
	mov	w1, 0
	str	w2, [x20, 92]
	add	x0, x0, 2432
	bfi	w1, w3, 0, 8
	mov	w3, 85
	bfi	w1, w3, 8, 8
	str	w1, [x20, 28]
	mov	w3, 0
	mov	w1, 0
	ldr	w4, [x0, 976]
	ldr	w2, [x0, 980]
	ldr	w5, [x0, 984]
	bfi	w3, w4, 0, 6
	bfi	w3, w2, 8, 2
	ldr	w2, [x0, 988]
	ldr	w4, [x0, 992]
	bfi	w3, w5, 10, 1
	bfi	w3, w2, 12, 4
	mov	w2, 0
	bfi	w3, w4, 16, 5
	str	w3, [x23, 12240]
	ldr	w3, [x0, 1036]
	str	w3, [x23, 12244]
	ldr	w3, [x0, 1040]
	str	w3, [x23, 12248]
	ldr	w5, [x0, 1044]
	ldr	w3, [x0, 1048]
	ldr	w4, [x0, 1052]
	bfi	w1, w5, 0, 16
	bfi	w1, w3, 16, 2
	ldr	w3, [x0, 1056]
	ldr	w5, [x0, 1060]
	bfi	w1, w4, 18, 2
	bfi	w1, w3, 20, 4
	ldr	w4, [x0, 1068]
	ldr	w3, [x0, 1072]
	bfi	w1, w5, 24, 1
	bfi	w1, w4, 25, 2
	ldr	w4, [x0, 1064]
	bfi	w1, w3, 27, 1
	mov	w3, 0
	bfi	w1, w4, 28, 1
	str	w1, [x23, 12252]
	mov	w1, 0
	ldr	w5, [x0, 1104]
	ldr	w4, [x0, 1100]
	bfi	w2, w5, 0, 1
	ldr	w5, [x0, 1096]
	bfi	w2, w4, 2, 2
	ldr	w4, [x0, 1092]
	bfi	w2, w5, 4, 2
	ldr	w5, [x0, 1112]
	bfi	w2, w4, 6, 1
	ldr	w4, [x0, 1116]
	bfi	w2, w5, 8, 6
	bfi	w2, w4, 24, 6
	str	w2, [x23, 12256]
	ldr	w5, [x0, 1120]
	ldr	w2, [x0, 1124]
	ldr	w4, [x0, 1128]
	bfi	w3, w5, 0, 6
	bfi	w3, w2, 8, 6
	ldr	w2, [x0, 1132]
	bfi	w3, w4, 16, 6
	bfi	w3, w2, 24, 6
	str	w3, [x23, 12260]
	ldr	w3, [x0, 1136]
	ldr	w2, [x21, 8]
	ldr	w0, [x0, 1140]
	bfi	w1, w3, 0, 6
	bfi	w1, w0, 6, 25
	cbz	w2, .L118
	ldr	w2, [x21, 20]
	ldr	w0, [x21, 520]
	lsr	w3, w2, 6
	udiv	w0, w0, w3
	bfi	w1, w0, 6, 25
.L86:
	str	w1, [x23, 12264]
	mov	w1, 0
	ldr	x0, [x29, 104]
	mov	w2, 0
	ldr	w3, [x21, 556]
	add	x0, x0, 2432
	ldr	w6, [x21, 552]
	ldr	w5, [x21, 548]
	bfi	w1, w3, 10, 1
	ldr	w4, [x0, 1424]
	bfi	w1, w6, 9, 1
	bfi	w1, w5, 8, 1
	ldr	w6, [x0, 1428]
	ldr	w5, [x0, 1404]
	bfi	w1, w4, 7, 1
	bfi	w1, w6, 6, 1
	ldr	w4, [x0, 1400]
	ldr	w6, [x0, 1432]
	bfi	w1, w5, 5, 1
	bfi	w1, w4, 4, 1
	ldr	w5, [x0, 1436]
	ldr	w4, [x0, 1440]
	bfi	w1, w6, 3, 1
	bfi	w1, w5, 2, 1
	ldr	w6, [x0, 1444]
	bfi	w1, w4, 1, 1
	ldr	x3, .LC6
	bfi	w1, w6, 0, 1
	str	w1, [x23, 504]
	add	x5, x23, 61440
	mov	w4, 0
	ldr	w8, [x0, 1408]
	mov	w6, 3
	ldr	w7, [x0, 1448]
	ldr	x3, [x3]
	bfi	w2, w8, 7, 1
	bfi	w2, w7, 6, 1
	ldr	w7, [x0, 1452]
	add	x1, x3, 61440
	ldr	w3, [x0, 1456]
	bfi	w2, w7, 5, 1
	ldr	w7, [x0, 1460]
	bfi	w2, w3, 4, 1
	ldr	w3, [x0, 1464]
	bfi	w2, w7, 3, 1
	ldr	w7, [x0, 1468]
	bfi	w2, w3, 2, 1
	ldr	w3, [x0, 1472]
	bfi	w2, w7, 1, 1
	bfi	w2, w3, 0, 1
	str	w2, [x23, 508]
	mov	w2, 1
	ldr	w3, [x0, 1392]
	ldr	w0, [x0, 1396]
	bfi	w4, w3, 0, 1
	bfi	w4, w0, 3, 1
	bfi	w4, w6, 16, 4
	str	w4, [x5]
	str	wzr, [x5, 32]
	ldr	w0, [x21, 560]
	str	w0, [x1, 520]
	ldr	w0, [x21, 560]
	str	w0, [x1, 524]
	ldr	w0, [x21, 568]
	str	w0, [x1, 752]
	ldr	w0, [x21, 564]
	str	w0, [x1, 756]
	ldr	w0, [x21, 568]
	str	w0, [x1, 772]
	ldr	w0, [x21, 564]
	str	w0, [x1, 776]
	str	wzr, [x5, 8]
	str	wzr, [x23, 16]
	str	w2, [x23, 16]
.L30:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L113:
	add	x0, x27, 864
	mov	w4, 18
	mov	x3, x0
	str	x0, [x29, 96]
	add	x5, x2, 160
	add	x0, x2, 4
	b	.L34
	.p2align 3
.L40:
	ldr	w4, [x0], 4
.L34:
	str	w4, [x3], 4
	cmp	x0, x5
	bne	.L40
	add	x0, x2, 484
	add	x3, x27, 1024
	add	x2, x2, 640
	mov	w4, 193
	b	.L41
	.p2align 3
.L119:
	ldr	w4, [x0], 4
.L41:
	str	w4, [x3], 4
	cmp	x2, x0
	bne	.L119
	mov	w2, 3
	mov	w0, 5
	stp	wzr, w2, [x22, 116]
	stp	w2, w0, [x22, 124]
	mov	w2, 10
	str	w0, [x22, 132]
	str	w2, [x22, 136]
	mov	w0, 255
	mov	w2, 15
	mov	w3, 2
	stp	w0, w0, [x22, 148]
	stp	w0, w0, [x22, 156]
	str	w0, [x22, 164]
	mov	w0, 96
	str	w2, [x22, 140]
	mov	w2, 20
	stp	w3, wzr, [x22, 100]
	stp	wzr, wzr, [x22, 108]
	str	w0, [x22, 516]
	str	w2, [x22, 144]
	b	.L39
.L62:
	ldr	w2, [x22, 84]
	mov	w0, 0
	bfi	w0, w2, 0, 4
	b	.L63
.L59:
	mov	w2, 15
	mov	w0, 0
	bfi	w0, w2, 0, 5
	bfi	w0, w2, 5, 5
	bfi	w0, w2, 10, 5
	bfi	w0, w2, 15, 5
	and	w0, w0, -1048577
	str	w0, [x20, 24]
	b	.L60
.L96:
	mov	w3, 6
.L55:
	bfi	w0, w3, 6, 4
	and	w0, w0, -16385
.L56:
	ldrb	w2, [x21, 68]
	b	.L57
.L46:
	mov	w0, 7
	str	wzr, [x22, 5728]
	str	w0, [x22, 5724]
	str	wzr, [x22, 5732]
	b	.L48
.L118:
	ldr	w2, [x21, 20]
	ldr	w0, [x21, 520]
	lsr	w3, w2, 4
	udiv	w0, w0, w3
	bfi	w1, w0, 6, 25
	b	.L86
.L115:
	ldr	w2, [x21, 20]
	mov	w3, 32
	lsr	w0, w2, 2
	sub	w2, w0, #16
	ldr	w0, [x21, 16]
	lsr	w4, w2, 1
	lsr	w2, w0, 2
	cmp	w4, 32
	sub	w0, w2, #16
	csel	w4, w4, w3, ls
	lsr	w5, w0, 1
	and	w2, w4, 2147483644
	cmp	w5, 72
	mov	w4, 72
	csel	w5, w5, w4, ls
	cmp	w2, 7
	and	w0, w5, 2147483644
	mov	w4, 7
	bls	.L52
	cmp	w2, w3
	csel	w2, w2, w3, ls
	sub	w2, w2, #1
	and	w4, w2, 63
.L52:
	cmp	w0, 7
	mov	w3, 7
	bls	.L53
	cmp	w0, 72
	mov	w2, 72
	csel	w0, w0, w2, ls
	sub	w0, w0, #1
	and	w3, w0, 127
.L53:
	mov	w24, 0
	bfi	w24, w4, 16, 6
	bfi	w24, w3, 0, 7
	b	.L54
.L117:
	ldr	w1, [x22, 5828]
	cmp	w1, 31
	bls	.L120
	ldr	w1, [x22, 5788]
	str	w1, [x0, 308]
	ldr	w1, [x22, 5828]
	cmp	w1, 63
	bhi	.L78
.L123:
	ldr	w2, [x22, 5792]
	mov	w3, 64
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 312]
.L79:
	ldr	w1, [x22, 5828]
	cmp	w1, 64
	bls	.L80
	ldr	w2, [x22, 5796]
	mov	w3, 96
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 316]
.L80:
	ldr	w1, [x22, 5800]
	str	w1, [x0, 320]
	ldr	w1, [x22, 5804]
	str	w1, [x0, 324]
	ldr	w1, [x22, 5808]
	str	w1, [x0, 328]
	ldr	w1, [x22, 5812]
	str	w1, [x0, 332]
	ldr	w1, [x22, 5816]
	str	w1, [x0, 336]
	b	.L81
.L116:
	ldr	w1, [x21, 516]
	mov	w4, 9729
	ldr	w3, [x27, 7904]
	mov	w2, 513
	cmp	w1, wzr
	mov	w1, 0
	csel	w2, w2, w4, eq
	bfi	w1, w3, 8, 3
	bfi	w1, w2, 16, 16
	str	w1, [x0, 256]
	mov	w3, 0
	mov	w2, 0
	ldr	w4, [x21, 616]
	mov	w1, 16
	bfi	w3, w4, 0, 5
	ldr	w4, [x21, 620]
	bfi	w3, w4, 16, 16
	str	w3, [x0, 260]
	mov	w4, 0
	ldr	w3, [x22, 5824]
	bfi	w2, w3, 0, 5
	ldr	w3, [x22, 5828]
	bfi	w2, w3, 16, 16
	str	w2, [x0, 300]
	ldr	w2, [x21, 616]
	sub	w3, w1, w2
	ldr	w2, [x21, 656]
	lsl	w2, w2, w3
	mov	w3, 0
	bfi	w4, w2, 0, 16
	str	w4, [x0, 264]
	ldr	w2, [x22, 5824]
	sub	w1, w1, w2
	ldr	w2, [x22, 5820]
	lsl	w1, w2, w1
	bfi	w3, w1, 0, 16
	str	w3, [x0, 304]
	ldr	w1, [x21, 620]
	cmp	w1, 31
	bls	.L121
	ldr	w1, [x21, 624]
	str	w1, [x0, 268]
	ldr	w1, [x21, 620]
	cmp	w1, 63
	bhi	.L71
.L122:
	ldr	w2, [x21, 628]
	mov	w3, 64
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 272]
.L72:
	ldr	w1, [x21, 620]
	cmp	w1, 64
	bls	.L73
	ldr	w2, [x21, 632]
	mov	w3, 96
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 276]
.L73:
	ldr	w1, [x21, 636]
	str	w1, [x0, 280]
	ldr	w1, [x21, 640]
	str	w1, [x0, 284]
	ldr	w1, [x21, 644]
	str	w1, [x0, 288]
	ldr	w1, [x21, 648]
	str	w1, [x0, 292]
	ldr	w1, [x21, 652]
	str	w1, [x0, 296]
	b	.L74
.L44:
	cmp	w0, 719
	bls	.L45
	mov	w0, 2
	str	w0, [x27, 6416]
	b	.L43
.L121:
	ldr	w2, [x21, 624]
	mov	w3, 32
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 268]
	ldr	w1, [x21, 620]
	cmp	w1, 63
	bls	.L122
.L71:
	ldr	w1, [x21, 628]
	str	w1, [x0, 272]
	b	.L72
.L120:
	ldr	w2, [x22, 5788]
	mov	w3, 32
	sub	w1, w3, w1
	lsl	w1, w2, w1
	str	w1, [x0, 308]
	ldr	w1, [x22, 5828]
	cmp	w1, 63
	bls	.L123
.L78:
	ldr	w1, [x22, 5792]
	str	w1, [x0, 312]
	b	.L79
.L45:
	mov	w0, 1
	str	w0, [x27, 6416]
	b	.L43
	.size	DRV_VENC_HAL_V400R004C02_CfgReg, .-DRV_VENC_HAL_V400R004C02_CfgReg
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
	.global	DRV_VENC_HAL_V400R004C02_Init
	.type	DRV_VENC_HAL_V400R004C02_Init, %function
DRV_VENC_HAL_V400R004C02_Init:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC13
	ldr	x21, .LC14
	ldr	x0, [x20]
	cbz	x0, .L125
.L128:
	ldr	x1, [x21, 40]
	mov	w0, 8024
	blr	x1
	str	x0, [x20, 8]
	cbz	x0, .L153
	ldr	x3, [x21]
	mov	x2, 8024
	mov	w1, 0
	blr	x3
	ldr	x19, [x20, 8]
	cbz	x19, .L142
	add	x22, x19, 4096
	ldr	x1, [x20]
	str	x1, [x19]
	add	x0, x22, 2432
	mov	w4, 1280
	mov	w1, 720
	str	w4, [x19, 16]
	mov	w4, 10240
	str	w1, [x19, 20]
	mov	w1, 28
	str	w4, [x19, 32]
	mov	w2, 1
	str	w1, [x19, 524]
	mov	w3, 3
	str	w2, [x19, 60]
	mov	w4, 16
	stp	wzr, w3, [x19, 8]
	stp	w2, w3, [x19, 44]
	str	w4, [x19, 528]
	mov	w1, 48
	str	w1, [x19, 532]
	mov	w5, 128
	str	w2, [x0, 4]
	mov	w1, 32
	str	w2, [x19, 6528]
	mov	w6, 4
	stp	w5, w3, [x0, 24]
	mov	w3, 6
	mov	w4, 8
	mov	w7, 256
	str	w1, [x0, 448]
	stp	w4, w1, [x0, 32]
	stp	w4, w1, [x0, 40]
	str	w3, [x0, 452]
	add	x1, x22, 3276
	stp	w6, w7, [x0, 8]
	stp	w5, w6, [x0, 16]
	str	w2, [x0, 308]
	add	x3, x22, 3340
	str	w2, [x0, 656]
	str	w2, [x0, 684]
	str	w2, [x0, 736]
	.p2align 2
.L132:
	str	w2, [x1], 4
	mov	w0, 1
	cmp	x1, x3
	bne	.L132
	add	x2, x22, 3276
	add	x1, x22, 3576
	mov	w5, 48
	mov	w3, 4
	mov	w4, 8
	mov	w6, 10
	stp	w5, w5, [x2, 88]
	str	w5, [x2, 96]
	mov	w5, 51
	stp	w3, w4, [x2, 112]
	str	w4, [x2, 64]
	mov	w7, 2
	stp	w0, w3, [x2, 140]
	str	w7, [x2, 80]
	mov	w8, 12
	str	w3, [x2, 212]
	mov	w9, 5
	stp	w8, w8, [x2, 124]
	str	w9, [x2, 132]
	mov	w10, 50
	str	w6, [x2, 268]
	add	x11, x19, 768
	str	w6, [x2, 272]
	str	w6, [x2, 280]
	str	w6, [x2, 284]
	str	w6, [x2, 288]
	stp	w5, w5, [x2, 100]
	str	w5, [x2, 120]
	mov	w5, 44
	stp	w0, w0, [x2, 164]
	str	w5, [x2, 108]
	add	x5, x22, 3796
	str	w0, [x2, 172]
	str	w0, [x2, 184]
	mov	w2, 20
	stp	w8, w4, [x1, 16]
	stp	w2, w10, [x1, 4]
	str	w3, [x1, 24]
	mov	w10, 150
	str	w10, [x1, 12]
	stp	w8, w4, [x1, 28]
	str	w9, [x1, 200]
	mov	w9, 24
	stp	w9, w9, [x1, 136]
	mov	w9, 6
	str	w9, [x1, 48]
	mov	w9, 131
	str	w9, [x1, 52]
	mov	w9, 160
	str	w9, [x1, 56]
	mov	w9, 100
	str	w9, [x1, 60]
	mov	w9, 127
	str	w3, [x1, 44]
	stp	w3, w7, [x1, 36]
	stp	w6, w2, [x1, 68]
	str	w7, [x1, 104]
	mov	w6, 16
	stp	w4, w4, [x1, 112]
	stp	w4, w4, [x1, 120]
	stp	w6, w6, [x1, 128]
	str	w9, [x1, 64]
	mov	w8, 3
	str	w0, [x1, 76]
	mov	w2, 767
	str	w8, [x1, 88]
	mov	w9, 60
	str	w2, [x1, 80]
	add	x2, x22, 2432
	str	w9, [x1, 184]
	mov	x1, x5
	str	w0, [x19, 7892]
	mov	w9, 15
	add	x5, x19, 696
	stp	w7, w0, [x1, 12]
	stp	w0, w0, [x1, 4]
	mov	x1, x2
	mov	w2, 11520
	add	x10, x1, 1280
	movk	w2, 0x131, lsl 16
	stp	w9, w9, [x10, 104]
	stp	wzr, w0, [x10, 112]
	str	w2, [x1, 1484]
	mov	w2, 2304
	str	w7, [x1, 1476]
	movk	w2, 0x3d, lsl 16
	str	w0, [x1, 1480]
	mov	w7, 9
	str	w2, [x1, 1488]
	mov	w1, 64
	str	w0, [x5, 4]
	add	x2, x19, 1184
	str	w0, [x19, 696]
	stp	w3, w6, [x5, 16]
	stp	w3, w6, [x5, 24]
	stp	w6, w3, [x5, 60]
	stp	w8, w1, [x5, 8]
	str	w0, [x5, 68]
	mov	x1, x2
	str	w3, [x19, 780]
	mov	w6, 7
	str	w3, [x19, 796]
	mov	w3, 96
	str	w0, [x19, 784]
	mov	w2, 378
	str	w0, [x19, 788]
	stp	w6, w7, [x11, 60]
	stp	w6, w6, [x11, 52]
	mov	w7, 11
	mov	w6, 255
	str	w7, [x19, 836]
	mov	w7, 14
	str	w6, [x19, 852]
	str	w6, [x19, 856]
	str	w6, [x19, 860]
	mov	w6, 25
	str	w7, [x19, 840]
	mov	w7, 18
	str	w6, [x19, 848]
	str	w7, [x19, 844]
	str	w3, [x1, 28]
	str	w0, [x19, 1184]
	ldr	x3, .LC15
	str	w2, [x1, 24]
	mov	w2, 128
	stp	w8, w4, [x1, 16]
	str	w2, [x1, 12]
	add	x4, x3, 320
	stp	w8, w6, [x1, 4]
	add	x2, x19, 864
	add	x1, x3, 164
	b	.L135
	.p2align 3
.L133:
	ldr	w0, [x1], 4
.L135:
	str	w0, [x2], 4
	cmp	x1, x4
	bne	.L133
	add	x0, x3, 324
	add	x1, x19, 1024
	add	x3, x3, 480
	mov	w2, 1
	b	.L134
	.p2align 3
.L154:
	ldr	w2, [x0], 4
.L134:
	str	w2, [x1], 4
	cmp	x0, x3
	bne	.L154
	add	x19, x19, 1216
	mov	w0, 7
	add	x22, x22, 2320
	mov	x25, x19
	mov	w24, 3
	mov	w26, 96
	mov	w20, 4
	mov	w23, 64
	str	w0, [x5, 5724]
	str	wzr, [x5, 5728]
	str	wzr, [x5, 5732]
.L138:
	ldr	x3, [x21]
	mov	x2, 2600
	mov	w1, 0
	mov	x0, x25
	blr	x3
	mov	x2, x25
	mov	x1, x25
	mov	x0, x25
	mov	w4, 5
	mov	w3, 1
	mov	w10, 20
	mov	w9, 8
	mov	w5, 32
	mov	w8, 384
	mov	w7, 2
	mov	w6, 16
	.p2align 2
.L137:
	str	w24, [x0, 8]
	add	x1, x1, 32
	str	w26, [x1, 2436]
	add	x0, x0, 84
	add	x30, x1, 2304
	str	w20, [x2, 420]
	add	x2, x2, 404
	subs	w4, w4, #1
	str	w3, [x0, -80]
	str	w23, [x0, -72]
	str	wzr, [x0, -40]
	str	wzr, [x0, -12]
	stp	w24, w10, [x30, 108]
	stp	w23, w20, [x30, 116]
	str	w9, [x1, 2428]
	stp	w20, w5, [x0, -60]
	str	wzr, [x0, -28]
	str	wzr, [x0, -8]
	stp	w3, wzr, [x2, 24]
	str	w8, [x1, 2432]
	str	w3, [x0, -84]
	str	wzr, [x0, -52]
	stp	w5, w20, [x0, -24]
	str	wzr, [x0, -4]
	str	w7, [x1, 2408]
	stp	w20, w6, [x0, -68]
	str	w3, [x0, -16]
	str	w3, [x2, 20]
	bne	.L137
	add	x25, x25, 2600
	cmp	x25, x22
	bne	.L138
	mov	w6, 1
	mov	w7, 0
	mov	w2, w6
	mov	w5, 128
	mov	w0, 64
	mov	w14, 6
	mov	w13, 5
	mov	w3, 32
	mov	w4, 2
	mov	w12, 15
	mov	w8, 4
	mov	w1, 3
	mov	w11, 256
	mov	w10, 34
	mov	w9, 16
.L139:
	add	x20, x19, 2560
	str	w5, [x19, 28]
	stp	wzr, wzr, [x19]
	stp	w2, w5, [x19, 8]
	str	w5, [x19, 60]
	cmp	w6, 1
	str	w0, [x19, 96]
	str	w0, [x19, 112]
	str	w0, [x19, 144]
	str	w0, [x19, 180]
	str	w0, [x19, 196]
	str	w0, [x19, 228]
	str	w2, [x19, 380]
	str	wzr, [x19, 384]
	str	wzr, [x19, 388]
	str	w3, [x19, 408]
	str	wzr, [x19, 424]
	str	wzr, [x19, 428]
	str	w14, [x19, 824]
	str	wzr, [x19, 832]
	str	w13, [x19, 1228]
	stp	w4, w12, [x20, 12]
	stp	w0, w4, [x20, 20]
	str	w8, [x19, 2588]
	cbz	w7, .L155
	add	x15, x19, 256
	str	w2, [x19, 336]
	add	x16, x19, 256
	stp	w8, w9, [x15, 96]
	stp	w1, w3, [x15, 104]
	str	w1, [x19, 368]
	str	w1, [x19, 372]
	str	w1, [x19, 376]
	stp	w1, w3, [x16, 136]
	stp	w1, w2, [x16, 144]
	str	wzr, [x19, 412]
	str	w10, [x19, 416]
	str	w2, [x19, 2048]
	str	w4, [x19, 2568]
	str	w11, [x19, 2592]
	bhi	.L142
.L141:
	add	w7, w7, 1
	add	x19, x19, 2600
	add	w6, w6, 1
	b	.L139
	.p2align 3
.L142:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L153:
	ldr	x0, [x20]
	cbz	x0, .L150
	ldr	x1, [x21, 32]
	blr	x1
	str	xzr, [x20]
.L150:
	mov	w0, -1
.L156:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L125:
	ldr	x2, [x21, 24]
	mov	x1, 63232
	mov	x0, 4173856768
	blr	x2
	str	x0, [x20]
	cbnz	x0, .L128
	mov	w0, -1
	b	.L156
.L155:
	add	x17, x19, 256
	str	w2, [x19, 336]
	add	x18, x19, 256
	stp	w8, w9, [x17, 96]
	stp	w1, w3, [x17, 104]
	str	w8, [x19, 368]
	str	w1, [x19, 372]
	str	w1, [x19, 376]
	stp	w8, w3, [x18, 136]
	stp	w1, w2, [x18, 144]
	str	wzr, [x19, 412]
	str	w10, [x19, 416]
	str	w2, [x19, 2048]
	str	w4, [x19, 2568]
	str	w11, [x19, 2592]
	b	.L141
	.size	DRV_VENC_HAL_V400R004C02_Init, .-DRV_VENC_HAL_V400R004C02_Init
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC14:
	.xword	venc_Osal_Func_Ptr_S
	.align	3
.LC15:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DRV_VENC_HAL_V400R004C02_Deinit
	.type	DRV_VENC_HAL_V400R004C02_Deinit, %function
DRV_VENC_HAL_V400R004C02_Deinit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC18
	ldr	x0, [x19]
	cbz	x0, .L158
	ldr	x1, .LC19
	ldr	x1, [x1, 32]
	blr	x1
	str	xzr, [x19]
.L158:
	ldr	x0, [x19, 8]
	cbz	x0, .L157
	ldr	x1, .LC19
	ldr	x1, [x1, 48]
	blr	x1
	str	xzr, [x19, 8]
.L157:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DRV_VENC_HAL_V400R004C02_Deinit, .-DRV_VENC_HAL_V400R004C02_Deinit
	.align	3
.LC18:
	.xword	.LANCHOR0
	.align	3
.LC19:
	.xword	venc_Osal_Func_Ptr_S
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	g_h265LambdaSsd, %object
	.size	g_h265LambdaSsd, 160
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
	.size	g_h265LambdaSad, 160
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
