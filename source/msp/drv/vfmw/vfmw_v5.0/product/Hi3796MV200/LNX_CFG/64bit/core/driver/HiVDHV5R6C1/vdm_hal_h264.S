#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_h264.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	H264HAL_SetSliceMsgRefPicFrame.isra.2, %function
H264HAL_SetSliceMsgRefPicFrame.isra.2:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x8, x0
	mov	x0, x30
	mov	w27, w4
	mov	x20, x2
	stp	x8, x1, [x29, 104]
	str	w3, [x29, 124]
	bl	_mcount
	uxtw	x0, w27
	ldr	x7, [x29, 112]
	add	w5, w27, 3
	lsl	w27, w27, 3
	add	x6, x7, x0, lsl 2
	lsl	w23, w5, 2
	add	w27, w27, 20
	ldr	w1, [x6, 52]
	cbz	w1, .L1
	lsl	x28, x0, 10
	mov	w25, 0
	mov	w26, 0
	add	x28, x28, x0, lsl 7
	ldr	x21, .LC0
	mov	w19, 0
	mov	w22, 8
	ldr	x8, [x29, 104]
	b	.L7
	.p2align 3
.L5:
	cmp	w24, 3
	beq	.L15
.L6:
	ldr	w0, [x6, 52]
	cmp	w19, w0
	bcs	.L16
.L7:
	uxtw	x0, w19
	ldr	w4, [x8]
	lsl	x1, x0, 5
	and	w24, w19, 3
	add	x0, x1, x0, lsl 2
	and	w3, w19, 7
	add	x0, x0, x28
	lsl	w11, w3, 2
	add	x0, x7, x0
	add	w12, w24, w24, lsl 2
	add	w19, w19, 1
	ldrb	w1, [x0, 1626]
	ldrb	w13, [x0, 1627]
	ldr	w2, [x0, 1644]
	add	x4, x4, x1, lsl 1
	cmp	w13, 1
	csel	w1, w22, wzr, eq
	ubfiz	w2, w2, 1, 4
	cmp	w3, 7
	lsl	w2, w2, w12
	ldr	w0, [x21, x4, lsl 2]
	orr	w25, w25, w2
	and	w0, w0, 3
	orr	w0, w0, w1
	lsl	w0, w0, w11
	orr	w26, w26, w0
	bne	.L5
	str	w26, [x20, w23, uxtw 2]
	mov	w2, w23
	ldr	w0, [x29, 124]
	mov	w26, 0
	ldr	w4, [x20, w23, uxtw 2]
	ldr	x1, .LC2
	add	w3, w0, w23, lsl 2
	mov	w0, 4
	str	x6, [x29, 112]
	stp	x7, x8, [x29, 96]
	bl	dprint_vfmw
	add	w23, w23, 1
	cmp	w24, 3
	ldr	x6, [x29, 112]
	ldp	x7, x8, [x29, 96]
	bne	.L6
	.p2align 2
.L15:
	str	w25, [x20, w27, uxtw 2]
	mov	w2, w27
	ldr	w0, [x29, 124]
	mov	w25, 0
	ldr	w4, [x20, w27, uxtw 2]
	ldr	x1, .LC2
	add	w3, w0, w27, lsl 2
	mov	w0, 4
	str	x6, [x29, 112]
	stp	x7, x8, [x29, 96]
	bl	dprint_vfmw
	add	w27, w27, 1
	ldr	x6, [x29, 112]
	ldp	x7, x8, [x29, 96]
	ldr	w0, [x6, 52]
	cmp	w19, w0
	bcc	.L7
	.p2align 2
.L16:
	and	w0, w0, 7
	cbnz	w0, .L17
.L1:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L17:
	str	w26, [x20, w23, uxtw 2]
	mov	w2, w23
	ldr	w21, [x29, 124]
	mov	w0, 4
	ldr	x19, .LC2
	ldr	w4, [x20, w23, uxtw 2]
	add	w3, w21, w23, lsl 2
	mov	x1, x19
	bl	dprint_vfmw
	str	w25, [x20, w27, uxtw 2]
	add	w3, w21, w27, lsl 2
	mov	w2, w27
	ldr	w4, [x20, w27, uxtw 2]
	mov	x1, x19
	mov	w0, 4
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	H264HAL_SetSliceMsgRefPicFrame.isra.2, .-H264HAL_SetSliceMsgRefPicFrame.isra.2
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	H264HAL_SetSliceMsgRefPicField.isra.3, %function
H264HAL_SetSliceMsgRefPicField.isra.3:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w4
	mov	x21, x1
	mov	x19, x2
	str	w3, [x29, 108]
	bl	_mcount
	uxtw	x0, w22
	add	w10, w22, 3
	lsl	w7, w22, 3
	lsl	w25, w10, 2
	add	x23, x21, x0, lsl 2
	add	w27, w7, 20
	ldr	w1, [x23, 52]
	cbz	w1, .L18
	lsl	x5, x0, 10
	mov	w26, 0
	mov	w9, 0
	ldr	x22, .LC3
	add	x24, x5, x0, lsl 7
	mov	w28, 0
	b	.L38
	.p2align 3
.L21:
	cmp	w2, 2
	beq	.L29
	and	w12, w28, 3
	and	w0, w28, 7
.L28:
	cmp	w0, 7
	beq	.L54
.L36:
	cmp	w12, 3
	beq	.L55
.L37:
	ldr	w0, [x23, 52]
	add	w28, w28, 1
	cmp	w28, w0
	bcs	.L56
.L38:
	uxtw	x1, w28
	lsl	x0, x1, 5
	add	x0, x0, x1, lsl 2
	add	x0, x0, x24
	add	x0, x21, x0
	ldrb	w2, [x0, 1624]
	cmp	w2, 1
	bne	.L21
	ldrb	w2, [x0, 1625]
	cmp	w2, 3
	beq	.L22
	ldrb	w4, [x0, 1629]
	mov	w2, 8
	ldrb	w3, [x0, 1628]
	mov	w0, 4
	cmp	w4, 1
	csel	w2, wzr, w2, ne
	cmp	w3, 1
	csel	w0, wzr, w0, ne
	sbfiz	x3, x3, 1, 32
	orr	w0, w2, w0
	ldr	w2, [x20]
	add	x3, x3, x2
	ldr	x2, .LC3
	add	x2, x2, 32
	ldr	w2, [x2, x3, lsl 2]
	and	w2, w2, 3
.L52:
	orr	w2, w2, w0
	and	w0, w28, 7
	lsl	w3, w0, 2
	and	w12, w28, 3
	lsl	w2, w2, w3
	cmp	w0, 7
	orr	w9, w9, w2
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 2
	add	w2, w12, w12, lsl 2
	add	x1, x1, x24
	add	x1, x21, x1
	ldr	w1, [x1, 1644]
	ubfiz	w1, w1, 1, 4
	lsl	w1, w1, w2
	orr	w26, w26, w1
	bne	.L36
.L54:
	str	w9, [x19, w25, uxtw 2]
	mov	w2, w25
	ldr	w0, [x29, 108]
	ldr	w4, [x19, w25, uxtw 2]
	ldr	x1, .LC4
	add	w3, w0, w25, lsl 2
	mov	w0, 4
	str	w12, [x29, 104]
	add	w25, w25, 1
	bl	dprint_vfmw
	ldr	w12, [x29, 104]
	mov	w9, 0
	cmp	w12, 3
	bne	.L37
	.p2align 2
.L55:
	str	w26, [x19, w27, uxtw 2]
	mov	w2, w27
	ldr	w0, [x29, 108]
	add	w28, w28, 1
	ldr	w4, [x19, w27, uxtw 2]
	mov	w26, 0
	ldr	x1, .LC4
	add	w3, w0, w27, lsl 2
	mov	w0, 4
	str	w9, [x29, 104]
	add	w27, w27, 1
	bl	dprint_vfmw
	ldr	w0, [x23, 52]
	ldr	w9, [x29, 104]
	cmp	w28, w0
	bcc	.L38
	.p2align 2
.L56:
	and	w0, w0, 7
	cbnz	w0, .L57
.L18:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L29:
	ldrb	w2, [x0, 1625]
	cmp	w2, 3
	beq	.L30
	ldrb	w4, [x0, 1630]
	ldrb	w0, [x0, 1631]
	sbfiz	x2, x4, 1, 32
	cmp	w0, 1
	ldr	w0, [x20]
	add	x0, x2, x0
	ldr	x2, .LC3
	add	x2, x2, 32
	ldr	w2, [x2, x0, lsl 2]
.L53:
	mov	w0, 8
	and	w2, w2, 3
	csel	w3, wzr, w0, ne
	cmp	w4, 1
	mov	w0, 4
	and	w12, w28, 3
	csel	w0, wzr, w0, ne
	orr	w0, w3, w0
	orr	w2, w2, w0
	and	w0, w28, 7
	lsl	w3, w0, 2
	lsl	w2, w2, w3
	orr	w9, w9, w2
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 2
	add	w2, w12, w12, lsl 2
	add	x1, x1, x24
	add	x1, x21, x1
	ldr	w1, [x1, 1644]
	ubfiz	w1, w1, 1, 4
	orr	w1, w1, 1
	lsl	w1, w1, w2
	orr	w26, w26, w1
	b	.L28
	.p2align 3
.L22:
	ldrb	w2, [x0, 1626]
	ldr	w3, [x20]
	ldrb	w4, [x0, 1628]
	add	x2, x3, x2, lsl 1
	ldrb	w3, [x0, 1629]
	ldr	x0, .LC3
	cmp	w3, 1
	add	x0, x0, 32
	ldr	w2, [x0, x2, lsl 2]
	mov	w0, 8
	csel	w3, wzr, w0, ne
	cmp	w4, 1
	mov	w0, 4
	and	w2, w2, 3
	csel	w0, wzr, w0, ne
	orr	w0, w3, w0
	b	.L52
	.p2align 3
.L30:
	ldrb	w2, [x0, 1626]
	ldr	w3, [x20]
	ldrb	w4, [x0, 1630]
	add	x2, x3, x2, lsl 1
	ldrb	w3, [x0, 1631]
	add	x0, x22, 32
	cmp	w3, 1
	ldr	w2, [x0, x2, lsl 2]
	b	.L53
	.p2align 3
.L57:
	str	w9, [x19, w25, uxtw 2]
	mov	w2, w25
	ldr	w21, [x29, 108]
	mov	w0, 4
	ldr	x20, .LC4
	ldr	w4, [x19, w25, uxtw 2]
	add	w3, w21, w25, lsl 2
	mov	x1, x20
	bl	dprint_vfmw
	str	w26, [x19, w27, uxtw 2]
	add	w3, w21, w27, lsl 2
	mov	w2, w27
	ldr	w4, [x19, w27, uxtw 2]
	mov	x1, x20
	mov	w0, 4
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	H264HAL_SetSliceMsgRefPicField.isra.3, .-H264HAL_SetSliceMsgRefPicField.isra.3
	.align	3
.LC3:
	.xword	.LANCHOR0
	.align	3
.LC4:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Write_V5R6C1_CabacTab
	.type	Write_V5R6C1_CabacTab, %function
Write_V5R6C1_CabacTab:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L61
	ldr	x3, .LC8
	mov	x2, 5120
	ldr	x1, .LC9
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L60:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L61:
	ldr	x1, .LC7
	mov	w2, 59
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L60
	.size	Write_V5R6C1_CabacTab, .-Write_V5R6C1_CabacTab
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC8:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC9:
	.xword	g_CabacMN
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_InitHal
	.type	H264HAL_V5R6C1_InitHal, %function
H264HAL_V5R6C1_InitHal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 1104]
	bl	Write_V5R6C1_CabacTab
	cbnz	w0, .L67
.L63:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L67:
	ldr	x1, .LC11
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L63
	.size	H264HAL_V5R6C1_InitHal, .-H264HAL_V5R6C1_InitHal
	.align	3
.LC11:
	.xword	.LC10
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_V5R6C1_VirAddr
	.type	Get_V5R6C1_VirAddr, %function
Get_V5R6C1_VirAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x19, x20, uxtw 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_V5R6C1_VirAddr, .-Get_V5R6C1_VirAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_V5R6C1_PhyAddr
	.type	Get_V5R6C1_PhyAddr, %function
Get_V5R6C1_PhyAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	w0, w19, w20, lsl 2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_V5R6C1_PhyAddr, .-Get_V5R6C1_PhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_CutSliceChain
	.type	H264HAL_V5R6C1_CutSliceChain, %function
H264HAL_V5R6C1_CutSliceChain:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L73
	str	wzr, [x0, 252]
	mov	w0, 0
.L72:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L73:
	ldr	x2, .LC14
	ldr	x3, .LC13
	ldr	x1, .LC16
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L72
	.size	H264HAL_V5R6C1_CutSliceChain, .-H264HAL_V5R6C1_CutSliceChain
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC14:
	.xword	.LANCHOR0
	.align	3
.LC16:
	.xword	.LC15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Write_V5R6C1_Qmatrix
	.type	Write_V5R6C1_Qmatrix, %function
Write_V5R6C1_Qmatrix:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	w23, w1
	mov	x0, x30
	mov	w20, w2
	mov	x22, x3
	bl	_mcount
	cbz	w23, .L74
	sub	w23, w23, #1
	ldr	x25, .LC20
	ldr	x24, .LC22
	add	x23, x23, 1
	mov	x19, 0
	.p2align 2
.L76:
	ldr	w0, [x21, x19, lsl 2]
	mov	w2, w19
	str	w0, [x22, x19, lsl 2]
	mov	x1, x25
	mov	w0, 4
	ldr	w3, [x21, x19, lsl 2]
	bl	dprint_vfmw
	ldr	w3, [x22, x19, lsl 2]
	mov	w2, w20
	mov	w0, 4
	mov	x1, x24
	add	x19, x19, 1
	add	w20, w20, w0
	bl	dprint_vfmw
	cmp	x19, x23
	bne	.L76
.L74:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	Write_V5R6C1_Qmatrix, .-Write_V5R6C1_Qmatrix
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgStreamAddrInfo
	.type	H264HAL_SetSliceMsgStreamAddrInfo, %function
H264HAL_SetSliceMsgStreamAddrInfo:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	mov	x21, x2
	mov	x22, x1
	mov	w20, w3
	mov	x23, x2
	bl	_mcount
	ldr	x25, .LC26
	ldr	x26, .LC24
	add	x22, x22, 8
	add	x21, x21, 4
	add	w20, w20, 4
	add	x24, x23, 8
	mov	w19, 0
.L82:
	ldr	w4, [x22]
	add	w6, w19, 1
	str	w6, [x29, 108]
	mov	x1, x26
	mov	w2, w6
	mov	w0, 4
	sub	w3, w20, #4
	cbz	w4, .L80
	ldr	w28, [x22, 16]
	ldr	w4, [x22, 8]
	ldr	w8, [x27, 736]
	mov	w5, w28
	add	w7, w4, w28, lsl 3
	and	w28, w28, -16
	and	w7, w7, 127
	and	w8, w8, -16
	mov	w3, w7
	stp	w8, w7, [x29, 100]
	bl	dprint_vfmw
	ldp	w7, w6, [x29, 104]
	str	w7, [x21]
	mov	w3, w20
	mov	w2, w6
	mov	x1, x25
	ldr	w4, [x21]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x22]
	add	w3, w20, 4
	str	w0, [x24]
	add	w2, w19, 2
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x24]
	bl	dprint_vfmw
	ldr	w8, [x29, 100]
	sub	w3, w20, #4
	mov	w2, w19
	mov	x1, x25
	sub	w28, w28, w8
	str	w28, [x23]
	mov	w0, 4
	ldr	w4, [x23]
	bl	dprint_vfmw
.L81:
	add	w19, w19, 3
	add	x22, x22, 4
	cmp	w19, 6
	add	x21, x21, 12
	add	x23, x23, 12
	add	w20, w20, 12
	add	x24, x24, 12
	bne	.L82
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L80:
	str	wzr, [x23]
	mov	w2, w19
	mov	x1, x25
	mov	w0, 4
	ldr	w4, [x23]
	bl	dprint_vfmw
	str	wzr, [x21]
	mov	w3, w20
	add	w2, w19, 1
	ldr	w4, [x21]
	mov	x1, x25
	mov	w0, 4
	bl	dprint_vfmw
	str	wzr, [x24]
	add	w3, w20, 4
	add	w2, w19, 2
	ldr	w4, [x24]
	mov	x1, x25
	mov	w0, 4
	bl	dprint_vfmw
	b	.L81
	.size	H264HAL_SetSliceMsgStreamAddrInfo, .-H264HAL_SetSliceMsgStreamAddrInfo
	.align	3
.LC24:
	.xword	.LC23
	.align	3
.LC26:
	.xword	.LC25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	H264HAL_V5R6C1_SetSliceMsg.isra.7, %function
H264HAL_V5R6C1_SetSliceMsg.isra.7:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w2
	mov	x20, x1
	mov	w24, w3
	mov	w19, w4
	bl	_mcount
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x26, x0
	cbz	x0, .L141
	mov	x2, x0
	mov	w3, w21
	mov	x1, x20
	mov	x0, x22
	bl	H264HAL_SetSliceMsgStreamAddrInfo
	ldr	w0, [x20, 48]
	add	w2, w21, 24
	ldp	w3, w1, [x20, 32]
	and	w0, w0, 1048575
	ubfiz	w1, w1, 24, 2
	orr	w0, w0, w3, lsl 26
	orr	w0, w0, w1
	str	w0, [x26, 24]
	ldr	x1, .LC31
	mov	w0, 4
	ldr	w3, [x26, 24]
	bl	dprint_vfmw
	ldr	x0, .LC32
	ldrb	w4, [x20, 3]
	ldrb	w0, [x0]
	cbnz	w0, .L88
	cbz	w4, .L142
.L88:
	ldp	w2, w3, [x20, 52]
	ldp	w0, w1, [x20, 40]
	ldr	x23, .LC28
	lsl	w2, w2, 2
	ldrb	w5, [x20]
	ubfiz	w1, w1, 16, 5
	add	x25, x23, 128
	ubfiz	w0, w0, 21, 5
	orr	w0, w0, w1
	orr	w1, w2, w3, lsl 8
	orr	w2, w0, w1
	ldrb	w1, [x20, 2]
	ldr	w0, [x25, w5, sxtw 2]
	orr	w1, w0, w1, lsl 15
	orr	w0, w2, w1
	ldr	x1, .LC34
	orr	w0, w0, w4, lsl 14
	str	w0, [x26, 28]
	add	w2, w21, 28
	mov	w0, 4
	ldr	w3, [x26, 28]
	bl	dprint_vfmw
	ldrb	w0, [x20]
	ldr	w0, [x25, w0, sxtw 2]
	cmp	w0, 2
	beq	.L143
	mov	w3, 0
	mov	w0, 0
.L89:
	str	w0, [x26, 32]
	add	w2, w21, 32
	ldr	x1, .LC38
	mov	w0, 4
	str	w3, [x26, 36]
	ldr	w3, [x26, 32]
	bl	dprint_vfmw
	ldr	x1, .LC40
	add	w2, w21, 36
	ldr	w3, [x26, 36]
	mov	w0, 4
	bl	dprint_vfmw
	ldrb	w2, [x20, 4]
	ldp	w0, w1, [x20, 60]
	ubfiz	w0, w0, 5, 5
	and	w1, w1, 31
	orr	w0, w0, w2, lsl 16
	add	w2, w21, 40
	orr	w0, w0, w1
	str	w0, [x26, 40]
	ldr	x1, .LC42
	mov	w0, 4
	ldr	w3, [x26, 40]
	bl	dprint_vfmw
	ldp	w0, w1, [x20, 68]
	ldr	w2, [x20, 76]
	ubfiz	w1, w1, 8, 4
	ubfiz	w0, w0, 16, 4
	orr	w0, w0, w1
	ldr	x1, .LC44
	orr	w0, w0, w2
	str	w0, [x26, 44]
	add	w2, w21, 44
	mov	w0, 4
	ldr	w3, [x26, 44]
	bl	dprint_vfmw
	ldr	x0, [x20, 4056]
	cbz	x0, .L144
.L95:
	str	w19, [x26, 176]
	and	w24, w24, -16
	str	w24, [x26, 252]
	add	x19, x23, 128
	ldrb	w0, [x20]
	ldr	w0, [x19, w0, sxtw 2]
	cbnz	w0, .L98
.L108:
	mov	w0, 0
.L86:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L98:
	ldrb	w0, [x22]
	add	x24, x22, 48
	mov	w4, 0
	mov	w3, w21
	mov	x2, x26
	mov	x1, x20
	cbz	w0, .L145
	mov	x0, x24
	bl	H264HAL_SetSliceMsgRefPicField.isra.3
	ldrb	w0, [x20]
	ldr	w0, [x19, w0, sxtw 2]
	cmp	w0, 2
	beq	.L146
.L101:
	ldr	w2, [x20, 3928]
	add	x25, x20, 3932
	ldr	x24, .LC45
	mov	w19, 0
	mov	w27, 36
	and	w2, w2, 31
	.p2align 2
.L103:
	add	w19, w19, 1
	and	w1, w19, 3
	cmp	w19, 32
	add	w3, w1, w1, lsl 2
	beq	.L147
.L105:
	ldr	w0, [x25]
	cmp	w1, 3
	add	x25, x25, 4
	and	w0, w0, 31
	lsl	w0, w0, w3
	orr	w2, w2, w0
	bne	.L103
	str	w2, [x26, w27, uxtw 2]
	add	w3, w21, w27, lsl 2
	mov	w2, w27
	mov	x1, x24
	ldr	w4, [x26, w27, uxtw 2]
	mov	w0, 4
	add	w19, w19, 1
	add	w27, w27, 1
	bl	dprint_vfmw
	and	w1, w19, 3
	cmp	w19, 32
	mov	w2, 0
	add	w3, w1, w1, lsl 2
	bne	.L105
	.p2align 2
.L147:
	ldr	w0, [x22, 300]
	cbz	w0, .L106
	add	x0, x23, 128
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 1
	beq	.L107
.L106:
	ldr	w0, [x22, 304]
	cmp	w0, 1
	bne	.L108
	add	x0, x23, 128
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L108
.L107:
	ldr	x1, .LC47
	mov	w0, 4
	ldr	w2, [x20, 44]
	add	x25, x26, 256
	add	x27, x26, 512
	add	w24, w21, 256
	add	x26, x26, 768
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x28, .LC45
	.p2align 2
.L109:
	add	x22, x20, x19, uxtw 2
	ldr	w0, [x20, 80]
	mov	w3, w24
	and	w1, w0, 7
	ldrb	w2, [x22, 856]
	ldr	w0, [x22, 88]
	ubfiz	w0, w0, 3, 9
	orr	w0, w0, w2, lsl 12
	add	w2, w19, 64
	orr	w0, w0, w1
	str	w0, [x25, w19, uxtw 2]
	mov	x1, x28
	mov	w0, 4
	ldr	w4, [x25, w19, uxtw 2]
	bl	dprint_vfmw
	ldrb	w2, [x22, 984]
	add	w3, w24, 256
	ldr	w0, [x22, 216]
	ubfiz	w0, w0, 3, 9
	orr	w1, w0, w2, lsl 12
	ldr	w0, [x20, 84]
	add	w2, w19, 128
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x27, w19, uxtw 2]
	mov	x1, x28
	mov	w0, 4
	ldr	w4, [x27, w19, uxtw 2]
	bl	dprint_vfmw
	ldrb	w1, [x22, 1112]
	add	w3, w24, 512
	ldr	w0, [x22, 344]
	add	w2, w19, 192
	add	w24, w24, 4
	and	w0, w0, 511
	orr	w0, w0, w1, lsl 9
	str	w0, [x26, w19, uxtw 2]
	mov	x1, x28
	mov	w0, 4
	ldr	w4, [x26, w19, uxtw 2]
	add	w19, w19, 1
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	cmp	w19, w0
	bls	.L109
	ldr	x1, .LC49
	mov	w0, 4
	ldr	w2, [x20, 80]
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x24, .LC51
	.p2align 2
.L110:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 88]
	bl	dprint_vfmw
	ldr	x1, .LC53
	mov	w0, 4
	ldr	w2, [x22, 856]
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	cmp	w19, w0
	bls	.L110
	add	x0, x23, 128
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L111
.L114:
	ldr	x1, .LC55
	mov	w0, 4
	ldr	w2, [x20, 84]
	mov	w19, 0
	bl	dprint_vfmw
	ldr	x24, .LC61
	.p2align 2
.L112:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 216]
	bl	dprint_vfmw
	ldr	x1, .LC63
	mov	w0, 4
	ldr	w2, [x22, 984]
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	cmp	w19, w0
	bls	.L112
	add	x0, x23, 128
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L115
.L118:
	ldr	x24, .LC69
	mov	w19, 0
	.p2align 2
.L116:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 344]
	bl	dprint_vfmw
	ldr	x1, .LC71
	mov	w0, 4
	ldr	w2, [x22, 1112]
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	cmp	w19, w0
	bls	.L116
	add	x0, x23, 128
	ldrb	w1, [x20]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L108
	ldr	x24, .LC73
	mov	w19, 0
	.p2align 2
.L119:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 728]
	bl	dprint_vfmw
	ldr	w2, [x22, 1496]
	mov	w0, 4
	ldr	x1, .LC75
	bl	dprint_vfmw
	ldr	w2, [x20, 40]
	cmp	w19, w2
	bls	.L119
	add	x23, x23, 128
	ldrb	w0, [x20]
	ldr	w0, [x23, w0, sxtw 2]
	cmp	w0, 2
	bne	.L108
	ldr	x1, .LC77
	mov	w0, 4
	add	w21, w21, 384
	mov	w22, 0
	bl	dprint_vfmw
	.p2align 2
.L120:
	uxtw	x19, w22
	mov	w3, w21
	add	x23, x19, 32
	add	w2, w22, 96
	add	x19, x20, x19, lsl 2
	ldrb	w0, [x19, 1240]
	ldr	w1, [x19, 472]
	ubfiz	w1, w1, 3, 9
	orr	w1, w1, w0, lsl 12
	ldr	w0, [x20, 80]
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x25, x23, lsl 2]
	mov	x1, x28
	mov	w0, 4
	ldr	w4, [x25, x23, lsl 2]
	bl	dprint_vfmw
	ldrb	w0, [x19, 1368]
	add	w3, w21, 256
	ldr	w1, [x19, 600]
	add	w2, w22, 160
	ubfiz	w1, w1, 3, 9
	orr	w1, w1, w0, lsl 12
	ldr	w0, [x20, 84]
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x27, x23, lsl 2]
	mov	x1, x28
	mov	w0, 4
	ldr	w4, [x27, x23, lsl 2]
	bl	dprint_vfmw
	ldrb	w0, [x19, 1496]
	add	w3, w21, 512
	ldr	w1, [x19, 728]
	add	w2, w22, 224
	add	w22, w22, 1
	add	w21, w21, 4
	and	w1, w1, 511
	orr	w0, w1, w0, lsl 9
	str	w0, [x26, x23, lsl 2]
	mov	x1, x28
	mov	w0, 4
	ldr	w4, [x26, x23, lsl 2]
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	cmp	w22, w0
	bls	.L120
	b	.L108
	.p2align 3
.L142:
	ldp	w1, w0, [x22, 40]
	mul	w0, w0, w1
	cmp	w0, 1620
	bls	.L88
	mov	w0, -1
	b	.L86
	.p2align 3
.L145:
	mov	x0, x24
	bl	H264HAL_SetSliceMsgRefPicFrame.isra.2
	ldrb	w0, [x20]
	ldr	w0, [x19, w0, sxtw 2]
	cmp	w0, 2
	bne	.L101
	mov	w4, 1
	mov	w3, w21
	mov	x2, x26
	mov	x1, x20
	mov	x0, x24
	bl	H264HAL_SetSliceMsgRefPicFrame.isra.2
	b	.L101
	.p2align 3
.L143:
	ldr	x1, .LC36
	mov	w0, 4
	ldr	w2, [x20, 2788]
	bl	dprint_vfmw
	ldrb	w0, [x22]
	cbnz	w0, .L90
	ldrb	w0, [x20, 2778]
	cmp	w0, 3
	ldr	w0, [x20, 2788]
	beq	.L148
.L139:
	add	x0, x22, x0, lsl 2
	mov	w3, 0
	ldr	w0, [x0, 584]
	and	w0, w0, -16
	b	.L89
	.p2align 3
.L144:
	ldr	w0, [x22, 740]
	ldrb	w1, [x20, 1]
	cmp	w0, 262144
	ble	.L97
	add	w19, w1, 1
	mov	w0, 262143
	sdiv	w19, w0, w19
	b	.L95
.L90:
	ldr	w0, [x20, 2776]
	and	w0, w0, 16776960
	cmp	w0, 768
	beq	.L140
	ldrb	w0, [x20, 2776]
	cmp	w0, 1
	beq	.L140
	ldr	w1, [x20, 2788]
	mov	w3, 0
	ldr	w0, [x22, 716]
	add	x1, x22, x1, lsl 2
	ldr	w1, [x1, 584]
	add	w0, w1, w0
	and	w0, w0, -16
	b	.L89
.L97:
	sub	w0, w0, #1
	add	w19, w1, 1
	sdiv	w19, w0, w19
	b	.L95
.L146:
	mov	w4, 1
	mov	w3, w21
	mov	x2, x26
	mov	x1, x20
	mov	x0, x24
	bl	H264HAL_SetSliceMsgRefPicField.isra.3
	b	.L101
.L140:
	ldr	w0, [x20, 2788]
	b	.L139
.L148:
	add	x0, x22, x0, lsl 2
	ldr	w3, [x22, 716]
	ldr	w0, [x0, 584]
	add	w3, w0, w3
	and	w0, w0, -16
	and	w3, w3, -16
	b	.L89
.L115:
	ldr	x24, .LC65
	mov	w19, 0
	.p2align 2
.L117:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 600]
	bl	dprint_vfmw
	ldr	x1, .LC67
	mov	w0, 4
	ldr	w2, [x22, 1368]
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	cmp	w19, w0
	bls	.L117
	b	.L118
.L111:
	ldr	x24, .LC57
	mov	w19, 0
	.p2align 2
.L113:
	add	x22, x20, x19, uxtw 2
	mov	x1, x24
	mov	w0, 4
	add	w19, w19, 1
	ldr	w2, [x22, 472]
	bl	dprint_vfmw
	ldr	x1, .LC59
	mov	w0, 4
	ldr	w2, [x22, 1240]
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	cmp	w19, w0
	bls	.L113
	b	.L114
.L141:
	ldr	x2, .LC28
	mov	w0, 0
	ldr	x3, .LC27
	ldr	x1, .LC29
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L86
	.size	H264HAL_V5R6C1_SetSliceMsg.isra.7, .-H264HAL_V5R6C1_SetSliceMsg.isra.7
	.align	3
.LC27:
	.xword	.LC12
	.align	3
.LC28:
	.xword	.LANCHOR0
	.align	3
.LC29:
	.xword	.LC15
	.align	3
.LC31:
	.xword	.LC30
	.align	3
.LC32:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC34:
	.xword	.LC33
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
	.xword	.LC1
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.align	3
.LC51:
	.xword	.LC50
	.align	3
.LC53:
	.xword	.LC52
	.align	3
.LC55:
	.xword	.LC54
	.align	3
.LC57:
	.xword	.LC56
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
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC71:
	.xword	.LC70
	.align	3
.LC73:
	.xword	.LC72
	.align	3
.LC75:
	.xword	.LC74
	.align	3
.LC77:
	.xword	.LC76
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R6C1_StartDec
	.type	H264HAL_V5R6C1_StartDec, %function
H264HAL_V5R6C1_StartDec:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	w24, w1
	mov	x25, x2
	bl	_mcount
	cmp	w24, wzr
	bgt	.L253
	cbz	x21, .L254
	ldr	w0, [x21, 44]
	cmp	w0, 512
	bhi	.L154
	ldr	w0, [x21, 36]
	cmp	w0, 512
	bhi	.L154
	ldr	x0, [x21, 944]
	cbz	x0, .L255
	cbz	w24, .L157
	cmp	w24, 1
	bne	.L256
	mov	w0, -104529920
.L158:
	sxtw	x22, w24
	ldr	x23, .LC91
	lsl	x1, x22, 6
	sub	x1, x1, x22
	lsl	x1, x1, 2
	sub	x19, x1, x22
	add	x19, x1, x19, lsl 2
	ldr	x1, [x23, x19]
	cbz	x1, .L257
.L159:
	ldr	x3, .LC160
	mov	w0, 3
	ldr	x1, .LC162
	ldr	w2, [x3]
	add	w2, w2, 1
	str	w2, [x3]
	bl	dprint_vfmw
	ldr	x1, .LC164
	ldr	x0, .LC163
	ldrb	w1, [x1]
	add	x0, x0, x22, lsl 6
	cmp	w1, 1
	ccmp	x25, xzr, 0, ne
	ldr	w0, [x0, 8]
	beq	.L258
	ldr	x2, .LC96
	ldr	x0, [x2, w0, sxtw 3]
	cbz	x0, .L210
	ldr	w20, [x0, 1312]
	uxtb	w0, w20
	and	w26, w0, 1
.L161:
	cmp	w1, 1
	beq	.L162
	strb	w0, [x25, 1]
.L162:
	ldr	w2, [x21, 1188]
	mov	w0, 262143
	ldr	w1, [x21, 740]
	cmp	w2, 1
	str	wzr, [x29, 124]
	csetm	w2, eq
	cmp	w1, 262144
	and	w2, w2, 3
	uxtb	w2, w2
	bgt	.L163
	sub	w0, w1, #1
	and	w0, w0, 1048575
.L163:
	ldr	w1, [x29, 124]
	mov	x3, x25
	bfi	w1, w0, 0, 20
	str	w1, [x29, 124]
	ubfx	x0, x1, 24, 6
	ubfx	x1, x1, 16, 6
	orr	w0, w0, 64
	strb	w1, [x29, 126]
	orr	w0, w0, 1
	and	w0, w0, -3
	bfi	w0, w2, 2, 2
	strb	w0, [x29, 127]
	mov	w2, w24
	mov	w0, 8
	ldr	w19, [x29, 124]
	str	w19, [x21, 960]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC98
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	strb	wzr, [x29, 124]
	ldrb	w2, [x21, 16]
	mov	w0, 0
	ldrb	w1, [x21, 2]
	bfi	w0, w2, 4, 1
	mov	w2, 1
	bfi	w0, w1, 6, 1
	strh	w2, [x29, 126]
	mov	w1, 0
	ldrb	w2, [x21, 3]
	orr	w0, w0, -128
	bfi	w1, w26, 4, 1
	strb	w0, [x29, 125]
	strb	w1, [x29, 127]
	cbz	w2, .L164
	ldr	w0, [x21, 44]
	lsl	w0, w0, 4
	cmp	w0, 1920
	bls	.L164
	ldrb	w0, [x21, 4]
	and	w1, w1, -33
	strb	w1, [x29, 127]
	and	w1, w0, 1
.L166:
	ldrb	w0, [x29, 127]
	mov	x3, x25
	strb	wzr, [x21, 17]
	mov	w2, w24
	bfi	w0, w1, 6, 1
	and	w0, w0, 127
	strb	w0, [x29, 127]
	mov	w0, 12
	ldr	w19, [x29, 124]
	str	w19, [x21, 964]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC100
	mov	w2, w19
	mov	w0, 3
	lsl	x19, x22, 6
	sub	x19, x19, x22
	bl	dprint_vfmw
	lsl	x19, x19, 2
	sub	x0, x19, x22
	mov	x3, x25
	mov	w2, w24
	add	x19, x19, x0, lsl 2
	mov	w0, 16
	add	x19, x23, x19
	ldr	w26, [x19, 72]
	and	w26, w26, -16
	str	w26, [x21, 968]
	mov	w1, w26
	bl	MFDE_ConfigReg
	ldr	x1, .LC102
	mov	w2, w26
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x19, 56]
	mov	x3, x25
	mov	w2, w24
	and	w19, w19, -16
	mov	w0, 20
	mov	w1, w19
	str	w19, [x21, 972]
	bl	MFDE_ConfigReg
	ldr	x1, .LC104
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x21, 736]
	mov	x3, x25
	mov	w2, w24
	and	w19, w19, -16
	mov	w0, 24
	mov	w1, w19
	str	w19, [x21, 976]
	str	w19, [x29, 124]
	bl	MFDE_ConfigReg
	ldr	x1, .LC106
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w0, [x21, 44]
	mov	w1, 0
	cmp	w0, 256
	bhi	.L167
	cmp	w0, 119
	mov	w1, 1
	bls	.L167
	ldr	w0, [x21, 1184]
	cmp	w0, wzr
	cset	w1, eq
.L167:
	mov	x3, x25
	mov	w2, w24
	mov	w0, 4
	mov	w19, 3075
	movk	w19, 0x30, lsl 16
	bl	SCD_ConfigReg
	str	w19, [x29, 124]
	mov	x3, x25
	mov	w2, w24
	mov	w1, w19
	mov	w0, 60
	bl	MFDE_ConfigReg
	mov	x3, x25
	mov	w2, w24
	mov	w1, w19
	mov	w0, 64
	bl	MFDE_ConfigReg
	mov	x3, x25
	mov	w2, w24
	mov	w1, w19
	mov	w0, 68
	bl	MFDE_ConfigReg
	mov	x3, x25
	mov	w2, w24
	mov	w1, w19
	mov	w0, 72
	bl	MFDE_ConfigReg
	mov	x3, x25
	mov	w2, w24
	mov	w1, w19
	mov	w0, 76
	bl	MFDE_ConfigReg
	mov	x3, x25
	mov	w2, w24
	mov	w1, w19
	mov	w0, 80
	bl	MFDE_ConfigReg
	mov	x3, x25
	mov	w2, w24
	mov	w1, w19
	mov	w0, 84
	bl	MFDE_ConfigReg
	cmp	w20, 1
	beq	.L259
.L168:
	ldr	w1, [x21, 308]
	mov	x3, x25
	mov	w0, 96
	mov	w2, w24
	add	x1, x21, x1, lsl 2
	ldr	w19, [x1, 324]
	and	w19, w19, -16
	str	w19, [x21, 1012]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC113
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x21, 720]
	mov	x3, x25
	mov	w0, 100
	mov	w1, w19
	mov	w2, w24
	str	w19, [x21, 1016]
	bl	MFDE_ConfigReg
	ldr	x1, .LC115
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x21, 320]
	mov	x3, x25
	mov	w0, 104
	mov	w1, w19
	mov	w2, w24
	str	w19, [x21, 1020]
	bl	MFDE_ConfigReg
	ldr	x1, .LC117
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x21, 732]
	mov	x3, x25
	mov	w0, 108
	mov	w1, w19
	mov	w2, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC119
	mov	w2, w19
	mov	w0, 3
	lsl	x19, x22, 6
	sub	x19, x19, x22
	bl	dprint_vfmw
	lsl	x19, x19, 2
	sub	x1, x19, x22
	mov	x3, x25
	mov	w0, 128
	mov	w2, w24
	add	x19, x19, x1, lsl 2
	add	x19, x23, x19
	ldr	w20, [x19, 1180]
	and	w20, w20, -16
	str	w20, [x21, 1036]
	mov	w1, w20
	bl	MFDE_ConfigReg
	ldr	x1, .LC121
	mov	w2, w20
	mov	w0, 3
	mov	w20, 0
	bl	dprint_vfmw
	str	wzr, [x29, 124]
	ldr	w0, [x19, 1184]
	mov	x3, x25
	strh	w0, [x29, 124]
	mov	w2, w24
	mov	w0, 132
	mov	w19, 0
	ldr	w26, [x29, 124]
	str	w26, [x21, 1040]
	mov	w1, w26
	bl	MFDE_ConfigReg
	ldr	x1, .LC123
	mov	w2, w26
	mov	w0, 3
	bl	dprint_vfmw
	add	x1, x21, 1056
	.p2align 2
.L169:
	ldr	w0, [x1], 4
	and	w0, w0, 3
	lsl	w0, w0, w19
	add	w19, w19, 2
	cmp	w19, 32
	orr	w20, w0, w20
	bne	.L169
	mov	x3, x25
	mov	w1, w20
	mov	w0, 148
	mov	w2, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC125
	mov	w2, w20
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x25
	mov	w2, w24
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC127
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	mov	w0, w19
	mov	x3, x25
	mov	w2, w24
	mov	w1, -1
	bl	MFDE_ConfigReg
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x1, x0, 2
	sub	x0, x1, x22
	add	x0, x1, x0, lsl 2
	add	x0, x23, x0
	ldp	w1, w20, [x0, 72]
	str	w1, [x29, 100]
	mov	w0, w1
	add	w1, w1, 112
	str	w1, [x29, 104]
	bl	MEM_Phy2Vir
	mov	x19, x0
	cbz	x0, .L260
	ldp	w4, w1, [x21, 48]
	ldr	w2, [x21, 56]
	mov	w3, -2147483648
	ldr	w0, [x21, 32]
	lsl	w2, w2, 27
	ldr	w24, [x29, 100]
	orr	w1, w2, w1, lsl 28
	ldrb	w2, [x21]
	cmp	w0, wzr
	csel	w0, w0, w3, eq
	ldr	w3, [x21, 60]
	add	x4, x4, x2, lsl 1
	ldr	x2, .LC79
	add	x2, x2, 232
	ldr	w4, [x2, x4, lsl 2]
	ldr	w2, [x21, 36]
	sub	w2, w2, #1
	lsl	w2, w2, 16
	orr	w2, w2, w4, lsl 14
	ldr	w4, [x21, 44]
	sub	w4, w4, #1
	orr	w4, w4, w3, lsl 26
	ldrb	w3, [x21, 1]
	orr	w1, w4, w1
	cmp	w3, 1
	mov	w3, 33554432
	csel	w3, wzr, w3, ne
	orr	w4, w2, w1
	orr	w0, w0, w3
	ldr	x1, .LC131
	orr	w0, w4, w0
	str	w0, [x19]
	mov	w2, w24
	mov	w0, 4
	ldr	w3, [x19]
	bl	dprint_vfmw
	ldr	w0, [x21, 312]
	add	w2, w24, 4
	ldr	x1, .LC133
	and	w0, w0, -16
	str	w0, [x19, 4]
	mov	w0, 4
	ldr	w3, [x19, 4]
	bl	dprint_vfmw
	ldr	w0, [x21, 64]
	add	w2, w24, 8
	str	w0, [x19, 8]
	mov	w0, 4
	ldr	x1, .LC135
	ldr	w3, [x19, 8]
	bl	dprint_vfmw
	ldr	w0, [x21, 48]
	cbz	w0, .L174
	ldr	w0, [x21, 68]
	add	w2, w24, 12
	str	w0, [x19, 12]
	mov	w0, 4
	ldr	x1, .LC137
	ldr	w3, [x21, 72]
	str	w3, [x19, 16]
	ldr	w3, [x19, 12]
	bl	dprint_vfmw
	ldr	x1, .LC139
	add	w2, w24, 16
	ldr	w3, [x19, 16]
	mov	w0, 4
	bl	dprint_vfmw
.L175:
	lsl	x24, x22, 6
	ldr	w25, [x29, 100]
	sub	x24, x24, x22
	ldr	x1, .LC141
	lsl	x24, x24, 2
	add	w2, w25, 20
	sub	x0, x24, x22
	add	x24, x24, x0, lsl 2
	add	x24, x23, x24
	ldr	w0, [x24, 1160]
	and	w0, w0, -16
	str	w0, [x19, 20]
	mov	w0, 4
	ldr	w3, [x19, 20]
	bl	dprint_vfmw
	ldr	w0, [x24, 1164]
	add	w2, w25, 24
	ldr	x1, .LC143
	and	w0, w0, -16
	str	w0, [x19, 24]
	mov	w0, 4
	ldr	w3, [x19, 24]
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 2
	beq	.L176
	ldr	w0, [x21, 316]
	add	x0, x21, x0, lsl 2
	ldr	w0, [x0, 584]
	and	w0, w0, -16
.L177:
	str	w0, [x19, 28]
	mov	w0, 4
	ldr	w24, [x29, 100]
	and	w20, w20, -16
	ldr	x1, .LC145
	ldr	w3, [x19, 28]
	add	w2, w24, 28
	bl	dprint_vfmw
	lsl	x0, x22, 6
	ldr	x1, .LC147
	sub	x0, x0, x22
	add	w2, w24, 32
	lsl	x0, x0, 2
	sub	x3, x0, x22
	add	x0, x0, x3, lsl 2
	add	x0, x23, x0
	ldr	w0, [x0, 1168]
	and	w0, w0, -16
	str	w0, [x19, 32]
	mov	w0, 4
	ldr	w3, [x19, 32]
	bl	dprint_vfmw
	str	w20, [x19, 36]
	ldr	x1, .LC149
	add	w2, w24, 36
	ldr	w3, [x19, 36]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w20, [x21, 936]
	ldr	x24, .LC151
	cbz	w20, .L178
	ldr	w0, [x29, 100]
	mov	w26, 0
	add	w28, w0, 40
	.p2align 2
.L179:
	uxtw	x0, w26
	mov	w3, w28
	add	x5, x0, 10
	add	w2, w26, 10
	add	x4, x21, x0, lsl 2
	mov	x1, x24
	mov	w0, 4
	add	w26, w26, 1
	add	w28, w28, w0
	ldr	w4, [x4, 744]
	add	x4, x21, x4, lsl 2
	ldr	w4, [x4, 324]
	and	w4, w4, -16
	str	w4, [x19, x5, lsl 2]
	ldr	w4, [x19, x5, lsl 2]
	bl	dprint_vfmw
	ldr	w20, [x21, 936]
	cmp	w26, w20
	bcc	.L179
	cmp	w20, 15
	bhi	.L183
.L178:
	add	w2, w20, 10
	ldr	w0, [x29, 100]
	add	w26, w0, w2, lsl 2
	.p2align 2
.L182:
	ldr	w5, [x21, 744]
	uxtw	x4, w20
	add	x4, x4, 10
	mov	w3, w26
	mov	w0, 4
	mov	x1, x24
	add	x5, x21, x5, lsl 2
	add	w20, w20, 1
	add	w26, w26, w0
	ldr	w5, [x5, 324]
	and	w5, w5, -16
	str	w5, [x19, x4, lsl 2]
	ldr	w4, [x19, x4, lsl 2]
	bl	dprint_vfmw
	cmp	w20, 15
	add	w2, w20, 10
	bls	.L182
.L183:
	lsl	x0, x22, 6
	ldr	w1, [x29, 100]
	sub	x0, x0, x22
	lsl	x0, x0, 2
	add	w2, w1, 104
	sub	x3, x0, x22
	ldr	x1, .LC153
	add	x0, x0, x3, lsl 2
	add	x0, x23, x0
	ldr	w0, [x0, 1104]
	and	w0, w0, -16
	str	w0, [x19, 104]
	mov	w0, 4
	ldr	w3, [x19, 104]
	bl	dprint_vfmw
	ldr	w20, [x21, 936]
	cbz	w20, .L261
	ldr	w0, [x29, 100]
	mov	w26, 27
	mov	w28, 0
	add	w0, w0, 108
	str	w0, [x29, 108]
	mov	w27, w0
	.p2align 2
.L185:
	add	x25, x21, x28, uxtw 2
	ubfiz	x4, x28, 1, 31
	add	x4, x4, 27
	mov	w3, w27
	lsl	x20, x4, 2
	mov	w2, w26
	ldr	w7, [x25, 808]
	mov	x1, x24
	str	w7, [x19, x4, lsl 2]
	mov	w0, 4
	add	w28, w28, 1
	ldr	w4, [x19, w26, uxtw 2]
	bl	dprint_vfmw
	add	x4, x20, 4
	add	w7, w26, 1
	ldr	w0, [x25, 872]
	add	w3, w27, 4
	mov	w2, w7
	mov	x1, x24
	str	w0, [x19, x4]
	mov	w0, 4
	add	w26, w26, 2
	add	w27, w27, 8
	ldr	w4, [x19, w7, uxtw 2]
	bl	dprint_vfmw
	ldr	w20, [x21, 936]
	cmp	w28, w20
	bcc	.L185
	cmp	w20, 15
	bhi	.L187
.L184:
	ldr	w0, [x29, 108]
	lsl	w28, w20, 1
	add	w27, w0, w20, lsl 3
	.p2align 2
.L186:
	uxtw	x4, w28
	add	w7, w28, 27
	add	x4, x4, 27
	mov	w3, w27
	lsl	x26, x4, 2
	mov	w2, w7
	mov	x1, x24
	mov	w0, 4
	str	wzr, [x19, x4, lsl 2]
	add	w20, w20, 1
	ldr	w4, [x19, w7, uxtw 2]
	bl	dprint_vfmw
	add	x6, x26, 4
	add	w4, w28, 28
	ldr	w0, [x29, 108]
	mov	w2, w4
	mov	x1, x24
	add	w28, w28, 2
	str	wzr, [x19, x6]
	sub	w3, w27, w0
	ldr	w0, [x29, 104]
	add	w27, w27, 8
	ldr	w4, [x19, w4, uxtw 2]
	add	w3, w3, w0
	mov	w0, 4
	bl	dprint_vfmw
	cmp	w20, 15
	bls	.L186
.L187:
	lsl	x4, x22, 6
	ldr	w0, [x29, 100]
	sub	x4, x4, x22
	add	x3, x19, 256
	lsl	x4, x4, 2
	add	w2, w0, 256
	sub	x5, x4, x22
	mov	w1, 56
	add	x0, x21, 76
	add	x4, x4, x5, lsl 2
	add	x4, x23, x4
	ldr	w4, [x4, 1176]
	and	w4, w4, -16
	str	w4, [x19, 236]
	bl	Write_V5R6C1_Qmatrix
.L171:
	ldr	w0, [x21, 1188]
	ldr	x26, [x21, 944]
	cmp	w0, 1
	beq	.L262
	ldr	w19, [x26, 48]
	mov	w24, 0
	cbnz	w19, .L263
.L191:
	add	x25, x22, x22, lsl 2
	ldr	w1, [x21, 940]
	lsl	x25, x25, 4
	mov	w27, 0
	sub	x25, x25, x22
	mov	w20, 0
	lsl	x25, x25, 1
	.p2align 2
.L193:
	cmp	w20, w1
	bge	.L264
.L205:
	ldr	w3, [x26, 48]
	cmp	w3, w27
	ccmp	w20, wzr, 4, ls
	bgt	.L193
	add	w4, w24, 5
	sub	x0, x25, x22
	add	w5, w20, w4
	lsl	x0, x0, 1
	add	w20, w20, 1
	mov	w27, w3
	add	x0, x0, x5, sxtw
	cmp	w20, w1
	add	x0, x23, x0, lsl 2
	ldr	w2, [x0, 56]
	bge	.L217
	ldr	x19, [x26, 4056]
	cbz	x19, .L196
	ldr	w0, [x19, 48]
	cmp	w3, w0
	bcs	.L200
	b	.L209
	.p2align 3
.L201:
	ldr	x19, [x19, 4056]
	cbz	x19, .L196
	ldr	w0, [x19, 48]
	cmp	w3, w0
	bcc	.L209
.L200:
	add	w20, w20, 1
	cmp	w20, w1
	blt	.L201
.L195:
	cbz	x19, .L151
.L209:
	cmp	w5, 140
	ccmp	w20, w1, 4, ne
	beq	.L265
	add	w4, w4, w20
	sub	x0, x25, x22
	lsl	x0, x0, 1
	ldr	w1, [x19, 48]
	add	x0, x0, x4, sxtw
	sub	w4, w1, #1
	mov	x1, x26
	add	x0, x23, x0, lsl 2
	ldr	w3, [x0, 56]
	mov	x0, x21
	bl	H264HAL_V5R6C1_SetSliceMsg.isra.7
	cbnz	w0, .L204
.L266:
	ldr	w1, [x21, 940]
	mov	x26, x19
	cmp	w20, w1
	blt	.L205
.L264:
	cmp	w1, wzr
	ble	.L206
	add	x0, x22, x22, lsl 2
	add	w1, w1, 4
	lsl	x0, x0, 4
	add	w1, w1, w24
	sub	x0, x0, x22
	lsl	x0, x0, 1
	sub	x0, x0, x22
	lsl	x0, x0, 1
	add	x0, x0, x1, sxtw
	add	x23, x23, x0, lsl 2
	ldr	w0, [x23, 56]
	bl	H264HAL_V5R6C1_CutSliceChain
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L256:
	ldr	x1, .LC90
	mov	w0, 0
	bl	dprint_vfmw
.L151:
	mov	w0, -1
.L226:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L265:
	ldr	w0, [x21, 44]
	mov	w3, 0
	ldr	w4, [x21, 36]
	mov	x1, x26
	str	xzr, [x26, 4056]
	mul	w4, w0, w4
	mov	x0, x21
	ldr	w20, [x21, 940]
	sub	w4, w4, #1
	bl	H264HAL_V5R6C1_SetSliceMsg.isra.7
	cbz	w0, .L266
.L204:
	ldr	x1, .LC155
	mov	w2, 1217
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L196:
	ldr	x1, .LC157
	mov	w2, 827
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L164:
	ldrb	w0, [x29, 127]
	mov	w1, 0
	strb	wzr, [x21, 4]
	and	w0, w0, -33
	strb	w0, [x29, 127]
	b	.L166
.L174:
	str	wzr, [x19, 12]
	mov	w0, 4
	ldr	w24, [x29, 100]
	ldr	w3, [x19, 12]
	ldr	x1, .LC137
	add	w2, w24, 12
	str	wzr, [x19, 16]
	bl	dprint_vfmw
	ldr	x1, .LC139
	add	w2, w24, 16
	ldr	w3, [x19, 16]
	mov	w0, 4
	bl	dprint_vfmw
	b	.L175
.L157:
	mov	w0, -121438208
	b	.L158
.L262:
	ldr	w1, [x21, 940]
	cmp	w1, 1
	ble	.L189
	.p2align 2
.L190:
	add	w0, w0, 1
	ldr	x26, [x26, 4056]
	cmp	w0, w1
	bne	.L190
.L189:
	lsl	x2, x22, 6
	ldr	w0, [x21, 44]
	sub	x2, x2, x22
	ldr	w4, [x21, 36]
	lsl	x2, x2, 2
	mov	w3, 0
	sub	x22, x2, x22
	mov	x1, x26
	mul	w4, w0, w4
	add	x2, x2, x22, lsl 2
	mov	x0, x21
	add	x23, x23, x2
	sub	w4, w4, #1
	ldr	w2, [x23, 76]
	bl	H264HAL_V5R6C1_SetSliceMsg.isra.7
	cbz	w0, .L226
	ldr	x1, .LC155
	mov	w2, 1130
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L226
	.p2align 3
.L176:
	ldr	w1, [x21, 316]
	ldr	w0, [x21, 716]
	add	x1, x21, x1, lsl 2
	ldr	w1, [x1, 584]
	add	w0, w1, w0
	and	w0, w0, -16
	b	.L177
.L263:
	lsl	x2, x22, 6
	str	wzr, [x26, 48]
	sub	x2, x2, x22
	mov	w24, 1
	lsl	x2, x2, 2
	sub	w4, w19, #1
	sub	x0, x2, x22
	mov	x1, x26
	ldp	w6, w5, [x26, 8]
	ldp	w28, w27, [x26, 16]
	stp	w24, wzr, [x26, 8]
	stp	wzr, wzr, [x26, 16]
	add	x2, x2, x0, lsl 2
	add	x2, x23, x2
	ldr	w0, [x21, 736]
	ldp	w25, w20, [x26, 24]
	stp	w0, wzr, [x26, 24]
	mov	x0, x21
	ldr	w3, [x2, 80]
	ldr	w2, [x2, 76]
	stp	w6, w5, [x29, 104]
	bl	H264HAL_V5R6C1_SetSliceMsg.isra.7
	ldp	w6, w5, [x29, 104]
	cbnz	w0, .L267
	stp	w6, w5, [x26, 8]
	stp	w28, w27, [x26, 16]
	stp	w25, w20, [x26, 24]
	str	w19, [x26, 48]
	ldr	x26, [x21, 944]
	b	.L191
.L217:
	mov	x19, x26
	b	.L195
.L210:
	mov	w26, 0
	mov	w0, 0
	mov	w20, 0
	b	.L161
.L259:
	ldr	x1, .LC107
	mov	x3, x25
	mov	w2, w24
	mov	w0, 92
	ldr	w19, [x1]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC109
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w1, [x21, 308]
	mov	w2, w24
	mov	w0, 112
	mov	x3, x25
	add	x1, x21, x1, lsl 2
	ldr	w19, [x1, 452]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC111
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	b	.L168
.L261:
	ldr	w0, [x29, 100]
	add	w0, w0, 108
	str	w0, [x29, 108]
	b	.L184
.L257:
	bl	MEM_Phy2Vir
	str	x0, [x19, x23]
	cbnz	x0, .L159
	ldr	x1, .LC93
	bl	dprint_vfmw
	b	.L151
	.p2align 3
.L253:
	ldr	x2, .LC79
	mov	w4, 0
	ldr	x1, .LC81
	mov	w3, w24
	add	x2, x2, 144
	mov	w0, 0
	bl	dprint_vfmw
	b	.L151
.L154:
	ldr	x2, .LC79
	mov	w0, 0
	ldr	x3, .LC86
	ldr	x1, .LC84
	add	x2, x2, 144
	bl	dprint_vfmw
	b	.L151
.L267:
	ldr	x1, .LC155
	mov	w2, 1164
	mov	w0, w24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L226
.L206:
	ldr	x1, .LC159
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L226
.L258:
	ldr	x2, .LC79
	mov	x3, x25
	ldr	x1, .LC95
	mov	w0, 0
	add	x2, x2, 168
	bl	dprint_vfmw
	mov	w0, -1
	b	.L226
.L254:
	ldr	x2, .LC79
	mov	w0, 0
	ldr	x3, .LC83
	ldr	x1, .LC84
	add	x2, x2, 144
	bl	dprint_vfmw
	b	.L151
.L255:
	ldr	x2, .LC79
	ldr	x3, .LC88
	ldr	x1, .LC84
	add	x2, x2, 144
	bl	dprint_vfmw
	b	.L151
.L260:
	ldr	x2, .LC79
	mov	w0, 0
	ldr	x3, .LC129
	ldr	x1, .LC84
	add	x2, x2, 200
	bl	dprint_vfmw
	b	.L171
	.size	H264HAL_V5R6C1_StartDec, .-H264HAL_V5R6C1_StartDec
	.align	3
.LC79:
	.xword	.LANCHOR0
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.align	3
.LC84:
	.xword	.LC15
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
.LC91:
	.xword	g_HwMem
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC96:
	.xword	s_pstVfmwChan
	.align	3
.LC98:
	.xword	.LC97
	.align	3
.LC100:
	.xword	.LC99
	.align	3
.LC102:
	.xword	.LC101
	.align	3
.LC104:
	.xword	.LC103
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC107:
	.xword	g_TunnelLineNumber
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.align	3
.LC115:
	.xword	.LC114
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC119:
	.xword	.LC118
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
	.align	3
.LC131:
	.xword	.LC130
	.align	3
.LC133:
	.xword	.LC132
	.align	3
.LC135:
	.xword	.LC134
	.align	3
.LC137:
	.xword	.LC136
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC141:
	.xword	.LC140
	.align	3
.LC143:
	.xword	.LC142
	.align	3
.LC145:
	.xword	.LC144
	.align	3
.LC147:
	.xword	.LC146
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
	.align	3
.LC157:
	.xword	.LC156
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC160:
	.xword	.LANCHOR1
	.align	3
.LC162:
	.xword	.LC161
	.align	3
.LC163:
	.xword	g_VdmDrvParam
	.align	3
.LC164:
	.xword	g_HalDisable
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	g_ListStructFrame, %object
	.size	g_ListStructFrame, 32
g_ListStructFrame:
	.word	0
	.word	1
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.type	g_ListStructField, %object
	.size	g_ListStructField, 32
g_ListStructField:
	.word	0
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.type	__func__.11858, %object
	.size	__func__.11858, 29
__func__.11858:
	.string	"H264HAL_V5R6C1_CutSliceChain"
	.zero	3
	.type	__func__.12069, %object
	.size	__func__.12069, 27
__func__.12069:
	.string	"H264HAL_V5R6C1_SetSliceMsg"
	.zero	5
	.type	g_SliceTypeForPMV, %object
	.size	g_SliceTypeForPMV, 12
g_SliceTypeForPMV:
	.word	1
	.word	2
	.word	0
	.zero	4
	.type	__func__.11991, %object
	.size	__func__.11991, 23
__func__.11991:
	.string	"H264HAL_CheckParaValid"
	.zero	1
	.type	__func__.12013, %object
	.size	__func__.12013, 25
__func__.12013:
	.string	"H264HAL_V5R6C1_CfgVdmReg"
	.zero	7
	.type	__func__.12039, %object
	.size	__func__.12039, 25
__func__.12039:
	.string	"H264HAL_V5R6C1_SetPicMsg"
	.zero	7
	.type	g_StructTrans, %object
	.size	g_StructTrans, 32
g_StructTrans:
	.word	0
	.word	3
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"slicemsg D[%d] address 0x%x = 0x%x\n" )
	.zero	4
.LC6:
	ASCII(.string	"line: %d, p = NULL is not expected value!\n" )
	.zero	5
.LC10:
	ASCII(.string	"H264HAL_V5R6C1_InitHal return error.\n" )
	.zero	2
.LC12:
	ASCII(.string	"can not map slice msg virtual address!\n" )
.LC15:
	ASCII(.string	"%s: %s\n" )
.LC19:
	ASCII(.string	"qmatrix[%d] = 0x%x\n" )
	.zero	4
.LC21:
	ASCII(.string	"picmsg Dxx addr 0x%x = 0x%x\n" )
	.zero	3
.LC23:
	ASCII(.string	"Before slicemsg D[%d] tmp =0x%x,bitsoffset =0x%x,bytespos = 0x%x\n" )
	.zero	6
.LC25:
	ASCII(.string	"slicemsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	7
.LC30:
	ASCII(.string	"slicemsg D[4] addr 0x%x = 0x%x\n" )
.LC33:
	ASCII(.string	"slicemsg D[5] addr 0x%x = 0x%x\n" )
.LC35:
	ASCII(.string	"slicemsg g_pListX[1][0]->frame_store->pmv_address_idc = %d\n" )
	.zero	4
.LC37:
	ASCII(.string	"slicemsg D[6] addr 0x%x = 0x%x\n" )
.LC39:
	ASCII(.string	"slicemsg D[7] addr 0x%x = 0x%x\n" )
.LC41:
	ASCII(.string	"slicemsg D[8] addr 0x%x = 0x%x\n" )
.LC43:
	ASCII(.string	"slicemsg D[9] addr 0x%x = 0x%x\n" )
.LC46:
	ASCII(.string	"slicemsg burst1 D0~D31, burst2 D0~31, burst3 D0~D31 list0size = %d\n" )
	.zero	4
.LC48:
	ASCII(.string	"luma_lg = %d\n" )
	.zero	2
.LC50:
	ASCII(.string	"wp_weight_l0_y = %d\n" )
	.zero	3
.LC52:
	ASCII(.string	"wp_offset_l0_y = %d\n" )
	.zero	3
.LC54:
	ASCII(.string	"chroma_lg = %d\n" )
.LC56:
	ASCII(.string	"wp_weight_l1_y = %d\n" )
	.zero	3
.LC58:
	ASCII(.string	"wp_offset_l1_y = %d\n" )
	.zero	3
.LC60:
	ASCII(.string	"wp_weight_l0_u = %d\n" )
	.zero	3
.LC62:
	ASCII(.string	"wp_offset_l0_u = %d\n" )
	.zero	3
.LC64:
	ASCII(.string	"wp_weight_l1_u = %d\n" )
	.zero	3
.LC66:
	ASCII(.string	"wp_offset_l1_u = %d\n" )
	.zero	3
.LC68:
	ASCII(.string	"wp_weight_l0_v = %d\n" )
	.zero	3
.LC70:
	ASCII(.string	"wp_offset_l0_v = %d\n" )
	.zero	3
.LC72:
	ASCII(.string	"wp_weight_l1_v = %d\n" )
	.zero	3
.LC74:
	ASCII(.string	"wp_offset_l1_v = %d\n" )
	.zero	3
.LC76:
	ASCII(.string	"slicemsg burst1 D32~D63, burst2 D32~63, burst3 D32~D63 list1size = %d\n" )
	.zero	1
.LC80:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC82:
	ASCII(.string	"point of picture para null\n" )
	.zero	4
.LC85:
	ASCII(.string	"picture width out of range\n" )
	.zero	4
.LC87:
	ASCII(.string	"point of fst slice para null\n" )
	.zero	2
.LC89:
	ASCII(.string	"VdhId is wrong! H264HAL_V200R003_StartDec\n" )
	.zero	5
.LC92:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC94:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC97:
	ASCII(.string	"BASIC_V5R6C1_CFG0 = 0x%x\n" )
	.zero	6
.LC99:
	ASCII(.string	"BASIC_V5R6C1_CFG1 = 0x%x\n" )
	.zero	6
.LC101:
	ASCII(.string	"AVM_V5R6C1_ADDR = 0x%x\n" )
.LC103:
	ASCII(.string	"VAM_V5R6C1_ADDR = 0x%x\n" )
.LC105:
	ASCII(.string	"STREAM_V5R6C1_BASE_ADDR = 0x%x\n" )
.LC108:
	ASCII(.string	"VREG_PART_DEC_OVER_INT_LEVEL=0x%x\n" )
	.zero	5
.LC110:
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC112:
	ASCII(.string	"YSTADDR_V5R6C1_1D = 0x%x\n" )
	.zero	6
.LC114:
	ASCII(.string	"YSTRIDE_V5R6C1_1D = 0x%x\n" )
	.zero	6
.LC116:
	ASCII(.string	"UVOFFSET_V5R6C1_1D = 0x%x\n" )
	.zero	5
.LC118:
	ASCII(.string	"HEAD_INF_OFFSET_V5R6C1_1D = 0x%x\n" )
	.zero	6
.LC120:
	ASCII(.string	"PPFD_V5R6C1_BUF_ADDR = 0x%x\n" )
	.zero	3
.LC122:
	ASCII(.string	"PPFD_V5R6C1_BUF_LEN = 0x%x\n" )
	.zero	4
.LC124:
	ASCII(.string	"REF_V5R6C1_PIC_TYPE = 0x%x\n" )
	.zero	4
.LC126:
	ASCII(.string	"FF_V5R6C1_APT_EN = 0x%x\n" )
	.zero	7
.LC128:
	ASCII(.string	"can not map down msg virtual address!\n" )
	.zero	1
.LC130:
	ASCII(.string	"picmsg D[0] addr 0x%x = 0x%x\n" )
	.zero	2
.LC132:
	ASCII(.string	"picmsg D[1] addr 0x%x = 0x%x\n" )
	.zero	2
.LC134:
	ASCII(.string	"picmsg D[2] addr 0x%x = 0x%x\n" )
	.zero	2
.LC136:
	ASCII(.string	"picmsg D[3] addr 0x%x = 0x%x\n" )
	.zero	2
.LC138:
	ASCII(.string	"picmsg D[4] addr 0x%x = 0x%x\n" )
	.zero	2
.LC140:
	ASCII(.string	"picmsg D[5] addr 0x%x = 0x%x\n" )
	.zero	2
.LC142:
	ASCII(.string	"picmsg D[6] addr 0x%x = 0x%x\n" )
	.zero	2
.LC144:
	ASCII(.string	"picmsg D[7] addr 0x%x = 0x%x\n" )
	.zero	2
.LC146:
	ASCII(.string	"picmsg D[8] addr 0x%x = 0x%x\n" )
	.zero	2
.LC148:
	ASCII(.string	"picmsg D[9] addr 0x%x = 0x%x\n" )
	.zero	2
.LC150:
	ASCII(.string	"picmsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	1
.LC152:
	ASCII(.string	"picmsg D[26] addr 0x%x = 0x%x\n" )
	.zero	1
.LC154:
	ASCII(.string	"line %d Set slice msg not wrong!\n" )
	.zero	6
.LC156:
	ASCII(.string	"line %d pSlicePara is NULL!\n" )
	.zero	3
.LC158:
	ASCII(.string	"!!! no slice to dec, add up msg report." )
.LC161:
	ASCII(.string	"\n\n***********************H264HAL_V200R003_StartDec is Now %d***********************\n" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	StartCnt.12091, %object
	.size	StartCnt.12091, 4
StartCnt.12091:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
