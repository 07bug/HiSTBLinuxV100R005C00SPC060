#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal_h264.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	Write_V5R2C1_CabacTab
	.type	Write_V5R2C1_CabacTab, %function
Write_V5R2C1_CabacTab:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L5
	ldr	x3, .LC2
	mov	x2, 5120
	ldr	x1, .LC3
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L3:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L5:
	ldr	x1, .LC1
	mov	w2, 51
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3
	.size	Write_V5R2C1_CabacTab, .-Write_V5R2C1_CabacTab
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC2:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC3:
	.xword	g_CabacMN
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R2C1_InitHal
	.type	H264HAL_V5R2C1_InitHal, %function
H264HAL_V5R2C1_InitHal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L12
	ldr	w0, [x19, 1104]
	bl	Write_V5R2C1_CabacTab
	cbnz	w0, .L13
.L8:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L13:
	ldr	x1, .LC10
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L8
.L12:
	ldr	x3, .LC5
	mov	w0, 0
	ldr	x2, .LC6
	ldr	x1, .LC8
	bl	dprint_vfmw
	mov	w0, -1
	b	.L8
	.size	H264HAL_V5R2C1_InitHal, .-H264HAL_V5R2C1_InitHal
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC6:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC10:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_V5R2C1_VirAddr
	.type	Get_V5R2C1_VirAddr, %function
Get_V5R2C1_VirAddr:
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
	.size	Get_V5R2C1_VirAddr, .-Get_V5R2C1_VirAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_V5R2C1_PhyAddr
	.type	Get_V5R2C1_PhyAddr, %function
Get_V5R2C1_PhyAddr:
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
	.size	Get_V5R2C1_PhyAddr, .-Get_V5R2C1_PhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R2C1_CutSliceChain
	.type	H264HAL_V5R2C1_CutSliceChain, %function
H264HAL_V5R2C1_CutSliceChain:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L19
	str	wzr, [x0, 252]
	mov	w0, 0
.L18:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L19:
	ldr	x2, .LC13
	ldr	x3, .LC12
	ldr	x1, .LC14
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L18
	.size	H264HAL_V5R2C1_CutSliceChain, .-H264HAL_V5R2C1_CutSliceChain
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC13:
	.xword	.LANCHOR0
	.align	3
.LC14:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Write_V5R2C1_Qmatrix
	.type	Write_V5R2C1_Qmatrix, %function
Write_V5R2C1_Qmatrix:
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
	cbz	w23, .L20
	sub	w23, w23, #1
	ldr	x25, .LC18
	ldr	x24, .LC20
	add	x23, x23, 1
	mov	x19, 0
	.p2align 2
.L22:
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
	bne	.L22
.L20:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	Write_V5R2C1_Qmatrix, .-Write_V5R2C1_Qmatrix
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
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
	ldr	x25, .LC24
	ldr	x26, .LC22
	add	x22, x22, 8
	add	x21, x21, 4
	add	w20, w20, 4
	add	x24, x23, 8
	mov	w19, 0
.L28:
	ldr	w4, [x22]
	add	w6, w19, 1
	str	w6, [x29, 108]
	mov	x1, x26
	mov	w2, w6
	mov	w0, 4
	sub	w3, w20, #4
	cbz	w4, .L26
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
.L27:
	add	w19, w19, 3
	add	x22, x22, 4
	cmp	w19, 6
	add	x21, x21, 12
	add	x23, x23, 12
	add	w20, w20, 12
	add	x24, x24, 12
	bne	.L28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L26:
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
	b	.L27
	.size	H264HAL_SetSliceMsgStreamAddrInfo, .-H264HAL_SetSliceMsgStreamAddrInfo
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC24:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgMvAddrInfo
	.type	H264HAL_SetSliceMsgMvAddrInfo, %function
H264HAL_SetSliceMsgMvAddrInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	mov	x19, x2
	mov	w20, w3
	bl	_mcount
	ldr	x0, .LC25
	ldrb	w1, [x21]
	add	x0, x0, 56
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L38
	mov	w3, 0
	mov	w0, 0
.L31:
	str	w0, [x19, 32]
	add	w2, w20, 32
	str	w3, [x19, 36]
	mov	w0, 4
	ldr	w3, [x19, 32]
	ldr	x1, .LC29
	bl	dprint_vfmw
	ldr	w3, [x19, 36]
	add	w2, w20, 36
	ldr	x1, .LC31
	mov	w0, 4
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L38:
	ldr	x1, .LC27
	mov	w0, 4
	ldr	w2, [x21, 2788]
	bl	dprint_vfmw
	ldrb	w0, [x22]
	cbnz	w0, .L32
	ldrb	w0, [x21, 2778]
	cmp	w0, 3
	ldr	w0, [x21, 2788]
	beq	.L39
.L37:
	add	x22, x22, x0, lsl 2
	mov	w3, 0
	ldr	w0, [x22, 584]
	and	w0, w0, -16
	b	.L31
	.p2align 3
.L32:
	ldr	w0, [x21, 2776]
	and	w0, w0, 16776960
	cmp	w0, 768
	beq	.L40
	ldrb	w0, [x21, 2776]
	cmp	w0, 1
	ldr	w0, [x21, 2788]
	beq	.L37
	ldr	w1, [x22, 716]
	add	x22, x22, x0, lsl 2
	mov	w3, 0
	ldr	w0, [x22, 584]
	add	w0, w0, w1
	and	w0, w0, -16
	b	.L31
	.p2align 3
.L39:
	ldr	w3, [x22, 716]
	add	x22, x22, x0, lsl 2
	ldr	w0, [x22, 584]
	add	w3, w0, w3
	and	w0, w0, -16
	and	w3, w3, -16
	b	.L31
	.p2align 3
.L40:
	ldr	w0, [x21, 2788]
	b	.L37
	.size	H264HAL_SetSliceMsgMvAddrInfo, .-H264HAL_SetSliceMsgMvAddrInfo
	.align	3
.LC25:
	.xword	.LANCHOR0
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC31:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgEndMbInSlice
	.type	H264HAL_SetSliceMsgEndMbInSlice, %function
H264HAL_SetSliceMsgEndMbInSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x1
	mov	x22, x0
	mov	x0, x30
	mov	x21, x2
	mov	w19, w3
	bl	_mcount
	ldr	x0, [x20, 4056]
	cbz	x0, .L42
	mov	w3, w19
.L43:
	str	w3, [x21, 176]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L42:
	ldr	w4, [x22, 740]
	ldrb	w0, [x20, 1]
	cmp	w4, 262144
	ble	.L45
	add	w3, w0, 1
	mov	w1, 262143
	sdiv	w3, w1, w3
	b	.L43
	.p2align 3
.L45:
	sub	w4, w4, #1
	add	w3, w0, 1
	sdiv	w3, w4, w3
	b	.L43
	.size	H264HAL_SetSliceMsgEndMbInSlice, .-H264HAL_SetSliceMsgEndMbInSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgRefPicFrame
	.type	H264HAL_SetSliceMsgRefPicFrame, %function
H264HAL_SetSliceMsgRefPicFrame:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x7, x0
	mov	x0, x30
	mov	w26, w4
	add	w28, w4, 3
	stp	x7, x1, [x29, 104]
	mov	x20, x2
	str	w3, [x29, 124]
	bl	_mcount
	lsl	w28, w28, 2
	uxtw	x0, w26
	ldr	x6, [x29, 112]
	lsl	w26, w26, 3
	add	x21, x6, x0, lsl 2
	add	w26, w26, 20
	ldr	w1, [x21, 52]
	cbz	w1, .L49
	lsl	x27, x0, 10
	mov	w19, 0
	mov	w24, 0
	add	x27, x27, x0, lsl 7
	ldr	x22, .LC33
	mov	w25, 0
	mov	w23, 8
	ldr	x7, [x29, 104]
	b	.L55
	.p2align 3
.L53:
	cmp	w10, 3
	beq	.L62
.L54:
	ldr	w0, [x21, 52]
	cmp	w0, w19
	bls	.L63
.L55:
	uxtw	x0, w19
	ldr	w4, [x7, 48]
	lsl	x1, x0, 5
	add	x12, x22, 72
	add	x0, x1, x0, lsl 2
	and	w10, w19, 3
	add	x0, x0, x27
	and	w3, w19, 7
	add	x0, x6, x0
	lsl	w11, w3, 2
	add	w13, w10, w10, lsl 2
	add	w19, w19, 1
	ldrb	w1, [x0, 1626]
	ldrb	w14, [x0, 1627]
	ldr	w2, [x0, 1644]
	add	x4, x4, x1, lsl 1
	cmp	w14, 1
	csel	w1, w23, wzr, eq
	ubfiz	w2, w2, 1, 4
	cmp	w3, 7
	lsl	w2, w2, w13
	ldr	w0, [x12, x4, lsl 2]
	orr	w24, w24, w2
	and	w0, w0, 3
	orr	w0, w0, w1
	lsl	w0, w0, w11
	orr	w25, w25, w0
	bne	.L53
	str	w25, [x20, w28, uxtw 2]
	mov	w2, w28
	ldr	w0, [x29, 124]
	mov	w25, 0
	ldr	w4, [x20, w28, uxtw 2]
	ldr	x1, .LC35
	add	w3, w0, w28, lsl 2
	mov	w0, 4
	str	w10, [x29, 112]
	stp	x6, x7, [x29, 96]
	bl	dprint_vfmw
	add	w28, w28, 1
	ldr	w10, [x29, 112]
	ldp	x6, x7, [x29, 96]
	cmp	w10, 3
	bne	.L54
	.p2align 2
.L62:
	str	w24, [x20, w26, uxtw 2]
	mov	w2, w26
	ldr	w0, [x29, 124]
	mov	w24, 0
	ldr	w4, [x20, w26, uxtw 2]
	ldr	x1, .LC35
	add	w3, w0, w26, lsl 2
	mov	w0, 4
	add	w26, w26, 1
	stp	x6, x7, [x29, 104]
	bl	dprint_vfmw
	ldr	w0, [x21, 52]
	ldp	x6, x7, [x29, 104]
	cmp	w0, w19
	bhi	.L55
	.p2align 2
.L63:
	and	w0, w0, 7
	cbnz	w0, .L64
.L49:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L64:
	str	w25, [x20, w28, uxtw 2]
	mov	w2, w28
	ldr	w21, [x29, 124]
	mov	w0, 4
	ldr	x19, .LC35
	ldr	w4, [x20, w28, uxtw 2]
	add	w3, w21, w28, lsl 2
	mov	x1, x19
	bl	dprint_vfmw
	str	w24, [x20, w26, uxtw 2]
	add	w3, w21, w26, lsl 2
	mov	w2, w26
	ldr	w4, [x20, w26, uxtw 2]
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
	.size	H264HAL_SetSliceMsgRefPicFrame, .-H264HAL_SetSliceMsgRefPicFrame
	.align	3
.LC33:
	.xword	.LANCHOR0
	.align	3
.LC35:
	.xword	.LC34
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgRefPicField
	.type	H264HAL_SetSliceMsgRefPicField, %function
H264HAL_SetSliceMsgRefPicField:
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
	cbz	w1, .L65
	lsl	x5, x0, 10
	mov	w28, 0
	mov	w26, 0
	ldr	x22, .LC37
	add	x24, x5, x0, lsl 7
	mov	w9, 0
	b	.L85
	.p2align 3
.L68:
	cmp	w2, 2
	beq	.L76
	and	w12, w28, 3
	and	w0, w28, 7
.L75:
	cmp	w0, 7
	beq	.L101
.L83:
	cmp	w12, 3
	beq	.L102
.L84:
	ldr	w0, [x23, 52]
	add	w28, w28, 1
	cmp	w0, w28
	bls	.L103
.L85:
	uxtw	x1, w28
	lsl	x0, x1, 5
	add	x0, x0, x1, lsl 2
	add	x0, x0, x24
	add	x0, x21, x0
	ldrb	w2, [x0, 1624]
	cmp	w2, 1
	bne	.L68
	ldrb	w2, [x0, 1625]
	cmp	w2, 3
	beq	.L69
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
	ldr	w2, [x20, 48]
	add	x3, x3, x2
	ldr	x2, .LC37
	add	x2, x2, 104
	ldr	w2, [x2, x3, lsl 2]
	and	w2, w2, 3
.L99:
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
	bne	.L83
.L101:
	str	w9, [x19, w25, uxtw 2]
	mov	w2, w25
	ldr	w0, [x29, 108]
	ldr	w4, [x19, w25, uxtw 2]
	ldr	x1, .LC38
	add	w3, w0, w25, lsl 2
	mov	w0, 4
	str	w12, [x29, 104]
	add	w25, w25, 1
	bl	dprint_vfmw
	ldr	w12, [x29, 104]
	mov	w9, 0
	cmp	w12, 3
	bne	.L84
	.p2align 2
.L102:
	str	w26, [x19, w27, uxtw 2]
	mov	w2, w27
	ldr	w0, [x29, 108]
	add	w28, w28, 1
	ldr	w4, [x19, w27, uxtw 2]
	mov	w26, 0
	ldr	x1, .LC38
	add	w3, w0, w27, lsl 2
	mov	w0, 4
	str	w9, [x29, 104]
	add	w27, w27, 1
	bl	dprint_vfmw
	ldr	w0, [x23, 52]
	ldr	w9, [x29, 104]
	cmp	w0, w28
	bhi	.L85
	.p2align 2
.L103:
	and	w0, w0, 7
	cbnz	w0, .L104
.L65:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L76:
	ldrb	w2, [x0, 1625]
	cmp	w2, 3
	beq	.L77
	ldrb	w4, [x0, 1630]
	ldrb	w0, [x0, 1631]
	sbfiz	x2, x4, 1, 32
	cmp	w0, 1
	ldr	w0, [x20, 48]
	add	x0, x2, x0
	ldr	x2, .LC37
	add	x2, x2, 104
	ldr	w2, [x2, x0, lsl 2]
.L100:
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
	b	.L75
	.p2align 3
.L69:
	ldrb	w2, [x0, 1626]
	ldr	w3, [x20, 48]
	ldrb	w4, [x0, 1628]
	add	x2, x3, x2, lsl 1
	ldrb	w3, [x0, 1629]
	ldr	x0, .LC37
	cmp	w3, 1
	add	x0, x0, 104
	ldr	w2, [x0, x2, lsl 2]
	mov	w0, 8
	csel	w3, wzr, w0, ne
	cmp	w4, 1
	mov	w0, 4
	and	w2, w2, 3
	csel	w0, wzr, w0, ne
	orr	w0, w3, w0
	b	.L99
	.p2align 3
.L77:
	ldrb	w2, [x0, 1626]
	ldr	w3, [x20, 48]
	ldrb	w4, [x0, 1630]
	add	x2, x3, x2, lsl 1
	ldrb	w3, [x0, 1631]
	add	x0, x22, 104
	cmp	w3, 1
	ldr	w2, [x0, x2, lsl 2]
	b	.L100
	.p2align 3
.L104:
	str	w9, [x19, w25, uxtw 2]
	mov	w2, w25
	ldr	w21, [x29, 108]
	mov	w0, 4
	ldr	x20, .LC38
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
	.size	H264HAL_SetSliceMsgRefPicField, .-H264HAL_SetSliceMsgRefPicField
	.align	3
.LC37:
	.xword	.LANCHOR0
	.align	3
.LC38:
	.xword	.LC34
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgRefPicInfo
	.type	H264HAL_SetSliceMsgRefPicInfo, %function
H264HAL_SetSliceMsgRefPicInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	ldrb	w0, [x19]
	mov	w4, 0
	mov	w3, w22
	mov	x2, x21
	mov	x1, x20
	cbnz	w0, .L106
	mov	x0, x19
	bl	H264HAL_SetSliceMsgRefPicFrame
	ldr	x0, .LC40
	ldrb	w1, [x20]
	add	x0, x0, 56
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L110
.L105:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L106:
	mov	x0, x19
	bl	H264HAL_SetSliceMsgRefPicField
	ldr	x0, .LC40
	ldrb	w1, [x20]
	add	x0, x0, 56
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L105
	mov	w4, 1
	mov	w3, w22
	mov	x2, x21
	mov	x1, x20
	mov	x0, x19
	bl	H264HAL_SetSliceMsgRefPicField
	b	.L105
	.p2align 3
.L110:
	mov	w4, 1
	mov	w3, w22
	mov	x2, x21
	mov	x1, x20
	mov	x0, x19
	bl	H264HAL_SetSliceMsgRefPicFrame
	b	.L105
	.size	H264HAL_SetSliceMsgRefPicInfo, .-H264HAL_SetSliceMsgRefPicInfo
	.align	3
.LC40:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgAPCInfo
	.type	H264HAL_SetSliceMsgAPCInfo, %function
H264HAL_SetSliceMsgAPCInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x1
	mov	x0, x30
	mov	x21, x2
	mov	w23, w3
	bl	_mcount
	ldr	x22, .LC42
	ldr	w2, [x19, 3928]
	add	x20, x19, 3932
	mov	w24, 36
	mov	w19, 0
	and	w2, w2, 31
	.p2align 2
.L112:
	add	w19, w19, 1
	and	w1, w19, 3
	cmp	w19, 32
	add	w3, w1, w1, lsl 2
	beq	.L115
.L114:
	ldr	w0, [x20]
	cmp	w1, 3
	add	x20, x20, 4
	and	w0, w0, 31
	lsl	w0, w0, w3
	orr	w2, w2, w0
	bne	.L112
	str	w2, [x21, w24, uxtw 2]
	add	w3, w23, w24, lsl 2
	mov	w2, w24
	mov	x1, x22
	ldr	w4, [x21, w24, uxtw 2]
	mov	w0, 4
	add	w19, w19, 1
	add	w24, w24, 1
	bl	dprint_vfmw
	and	w1, w19, 3
	cmp	w19, 32
	mov	w2, 0
	add	w3, w1, w1, lsl 2
	bne	.L114
.L115:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	H264HAL_SetSliceMsgAPCInfo, .-H264HAL_SetSliceMsgAPCInfo
	.align	3
.LC42:
	.xword	.LC34
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_SetSliceMsgWPInfo
	.type	H264HAL_SetSliceMsgWPInfo, %function
H264HAL_SetSliceMsgWPInfo:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	x24, x2
	str	w3, [x29, 108]
	bl	_mcount
	ldr	w0, [x20, 300]
	cbz	w0, .L117
	ldr	x28, .LC43
	ldrb	w1, [x19]
	add	x0, x28, 56
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 1
	beq	.L118
.L117:
	ldr	w0, [x20, 304]
	cmp	w0, 1
	beq	.L147
.L116:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L147:
	ldr	x28, .LC43
	ldrb	w1, [x19]
	add	x0, x28, 56
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L116
.L118:
	ldr	w3, [x29, 108]
	mov	w0, 4
	ldr	x1, .LC45
	add	x25, x24, 256
	ldr	w2, [x19, 44]
	add	w22, w3, 256
	add	x26, x24, 512
	mov	w20, 0
	add	x24, x24, 768
	bl	dprint_vfmw
	ldr	x23, .LC46
	.p2align 2
.L121:
	add	x21, x19, x20, uxtw 2
	ldr	w4, [x19, 80]
	mov	w3, w22
	add	w2, w20, 64
	and	w5, w4, 7
	mov	x1, x23
	ldrb	w6, [x21, 856]
	mov	w0, 4
	ldr	w4, [x21, 88]
	ubfiz	w4, w4, 3, 9
	orr	w4, w4, w6, lsl 12
	orr	w4, w4, w5
	str	w4, [x25, w20, uxtw 2]
	ldr	w4, [x25, w20, uxtw 2]
	bl	dprint_vfmw
	ldrb	w1, [x21, 984]
	add	w3, w22, 256
	ldr	w0, [x21, 216]
	add	w2, w20, 128
	ldr	w4, [x19, 84]
	ubfiz	w0, w0, 3, 9
	and	w4, w4, 7
	orr	w0, w0, w1, lsl 12
	orr	w0, w0, w4
	str	w0, [x26, w20, uxtw 2]
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x26, w20, uxtw 2]
	bl	dprint_vfmw
	ldrb	w5, [x21, 1112]
	add	w3, w22, 512
	ldr	w4, [x21, 344]
	add	w2, w20, 192
	mov	w0, 4
	mov	x1, x23
	and	w4, w4, 511
	add	w22, w22, w0
	orr	w4, w4, w5, lsl 9
	str	w4, [x24, w20, uxtw 2]
	ldr	w4, [x24, w20, uxtw 2]
	add	w20, w20, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w20, w0
	bls	.L121
	ldr	x1, .LC48
	mov	w0, 4
	ldr	w2, [x19, 80]
	mov	w20, 0
	bl	dprint_vfmw
	ldr	x22, .LC50
	ldr	x21, .LC52
	.p2align 2
.L122:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 88]
	bl	dprint_vfmw
	ldr	w2, [x27, 856]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w20, w0
	bls	.L122
	add	x0, x28, 56
	ldrb	w1, [x19]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L123
.L126:
	ldr	x1, .LC54
	mov	w0, 4
	ldr	w2, [x19, 84]
	mov	w20, 0
	bl	dprint_vfmw
	ldr	x22, .LC60
	ldr	x21, .LC62
	.p2align 2
.L124:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 216]
	bl	dprint_vfmw
	ldr	w2, [x27, 984]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w20, w0
	bls	.L124
	add	x0, x28, 56
	ldrb	w1, [x19]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	beq	.L127
.L130:
	ldr	x22, .LC68
	mov	w20, 0
	ldr	x21, .LC70
	.p2align 2
.L128:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 344]
	bl	dprint_vfmw
	ldr	w2, [x27, 1112]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w20, w0
	bls	.L128
	add	x0, x28, 56
	ldrb	w1, [x19]
	ldr	w0, [x0, w1, sxtw 2]
	cmp	w0, 2
	bne	.L116
	ldr	x22, .LC72
	mov	w20, 0
	ldr	x27, .LC74
	.p2align 2
.L131:
	add	x21, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x21, 728]
	bl	dprint_vfmw
	ldr	w2, [x21, 1496]
	mov	x1, x27
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w2, [x19, 40]
	cmp	w20, w2
	bls	.L131
	add	x28, x28, 56
	ldrb	w0, [x19]
	ldr	w0, [x28, w0, sxtw 2]
	cmp	w0, 2
	bne	.L116
	ldr	w3, [x29, 108]
	mov	w0, 4
	ldr	x1, .LC76
	mov	w21, 0
	add	w27, w3, 384
	bl	dprint_vfmw
	.p2align 2
.L132:
	uxtw	x20, w21
	mov	w3, w27
	add	x22, x20, 32
	add	x20, x19, x20, lsl 2
	ldrb	w2, [x20, 1240]
	ldr	w0, [x20, 472]
	ubfiz	w0, w0, 3, 9
	orr	w1, w0, w2, lsl 12
	ldr	w0, [x19, 80]
	add	w2, w21, 96
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x25, x22, lsl 2]
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x25, x22, lsl 2]
	bl	dprint_vfmw
	ldrb	w2, [x20, 1368]
	add	w3, w27, 256
	ldr	w0, [x20, 600]
	ubfiz	w0, w0, 3, 9
	orr	w1, w0, w2, lsl 12
	ldr	w0, [x19, 84]
	add	w2, w21, 160
	and	w0, w0, 7
	orr	w0, w1, w0
	str	w0, [x26, x22, lsl 2]
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x26, x22, lsl 2]
	bl	dprint_vfmw
	ldrb	w1, [x20, 1496]
	add	w3, w27, 512
	ldr	w0, [x20, 728]
	add	w2, w21, 224
	add	w21, w21, 1
	add	w27, w27, 4
	and	w0, w0, 511
	orr	w0, w0, w1, lsl 9
	str	w0, [x24, x22, lsl 2]
	mov	x1, x23
	mov	w0, 4
	ldr	w4, [x24, x22, lsl 2]
	bl	dprint_vfmw
	ldr	w0, [x19, 40]
	cmp	w21, w0
	bls	.L132
	b	.L116
	.p2align 3
.L127:
	ldr	x22, .LC64
	mov	w20, 0
	ldr	x21, .LC66
	.p2align 2
.L129:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 600]
	bl	dprint_vfmw
	ldr	w2, [x27, 1368]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 40]
	cmp	w20, w0
	bls	.L129
	b	.L130
	.p2align 3
.L123:
	ldr	x22, .LC56
	mov	w20, 0
	ldr	x21, .LC58
	.p2align 2
.L125:
	add	x27, x19, x20, uxtw 2
	mov	x1, x22
	mov	w0, 4
	add	w20, w20, 1
	ldr	w2, [x27, 472]
	bl	dprint_vfmw
	ldr	w2, [x27, 1240]
	mov	x1, x21
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w0, [x19, 40]
	cmp	w20, w0
	bls	.L125
	b	.L126
	.size	H264HAL_SetSliceMsgWPInfo, .-H264HAL_SetSliceMsgWPInfo
	.align	3
.LC43:
	.xword	.LANCHOR0
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC46:
	.xword	.LC34
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
.LC60:
	.xword	.LC59
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
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
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_CheckParaValid
	.type	H264HAL_CheckParaValid, %function
H264HAL_CheckParaValid:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, wzr
	bgt	.L156
	cbz	x19, .L157
	ldr	w0, [x19, 44]
	cmp	w0, 512
	bhi	.L153
	ldr	w0, [x19, 36]
	cmp	w0, 512
	bhi	.L153
	ldr	x1, [x19, 944]
	mov	w0, 0
	cbz	x1, .L158
.L150:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L156:
	ldr	x2, .LC78
	mov	w4, 0
	ldr	x1, .LC80
	mov	w3, w20
	add	x2, x2, 136
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L150
	.p2align 3
.L153:
	ldr	x2, .LC78
	ldr	x3, .LC85
.L155:
	ldr	x1, .LC83
	mov	w0, 0
	add	x2, x2, 136
	bl	dprint_vfmw
	mov	w0, -1
	b	.L150
.L157:
	ldr	x2, .LC78
	ldr	x3, .LC82
	b	.L155
.L158:
	ldr	x2, .LC78
	ldr	x3, .LC87
	ldr	x1, .LC83
	add	x2, x2, 136
	bl	dprint_vfmw
	mov	w0, -1
	b	.L150
	.size	H264HAL_CheckParaValid, .-H264HAL_CheckParaValid
	.align	3
.LC78:
	.xword	.LANCHOR0
	.align	3
.LC80:
	.xword	.LC79
	.align	3
.LC82:
	.xword	.LC81
	.align	3
.LC83:
	.xword	.LC7
	.align	3
.LC85:
	.xword	.LC84
	.align	3
.LC87:
	.xword	.LC86
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_GetVdmRegVirAddr
	.type	H264HAL_GetVdmRegVirAddr, %function
H264HAL_GetVdmRegVirAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, wzr
	bgt	.L164
	ldr	x0, [x19]
	cbz	x0, .L162
.L163:
	mov	w0, 0
.L161:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L162:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	str	x0, [x19]
	cbnz	x0, .L163
	ldr	x1, .LC91
	bl	dprint_vfmw
	mov	w0, -1
	b	.L161
	.p2align 3
.L164:
	ldr	x1, .LC89
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L161
	.size	H264HAL_GetVdmRegVirAddr, .-H264HAL_GetVdmRegVirAddr
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC91:
	.xword	.LC90
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R2C1_CfgVdmReg
	.type	H264HAL_V5R2C1_CfgVdmReg, %function
H264HAL_V5R2C1_CfgVdmReg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w23, w2
	mov	x22, x3
	mov	x24, x1
	bl	_mcount
	ldr	x1, .LC93
	sbfiz	x0, x23, 6, 32
	ldr	x2, .LC92
	cmp	x22, xzr
	ldrb	w1, [x1]
	add	x0, x2, x0
	ccmp	w1, 1, 4, eq
	ldr	w2, [x0, 8]
	bne	.L189
	ldr	x0, .LC97
	ldr	x0, [x0, w2, sxtw 3]
	cbz	x0, .L177
	ldr	w21, [x0, 1312]
	uxtb	w0, w21
	and	w25, w0, 1
.L168:
	cmp	w1, 1
	beq	.L169
	strb	w0, [x22, 1]
.L169:
	ldr	w2, [x20, 1188]
	mov	w0, 262143
	ldr	w1, [x20, 740]
	cmp	w2, 1
	str	wzr, [x29, 92]
	csetm	w4, eq
	cmp	w1, 262144
	and	w4, w4, 3
	uxtb	w4, w4
	bgt	.L170
	sub	w0, w1, #1
	and	w0, w0, 1048575
.L170:
	ldr	w1, [x29, 92]
	mov	x3, x22
	mov	w2, w23
	bfi	w1, w0, 0, 20
	str	w1, [x29, 92]
	ubfx	x0, x1, 24, 6
	ubfx	x1, x1, 16, 6
	orr	w0, w0, 64
	strb	w1, [x29, 94]
	orr	w0, w0, 1
	and	w0, w0, -3
	bfi	w0, w4, 2, 2
	strb	w0, [x29, 95]
	mov	w0, 8
	ldr	w19, [x29, 92]
	str	w19, [x20, 960]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC99
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	strb	wzr, [x29, 92]
	ldrb	w2, [x20, 16]
	mov	w0, 0
	ldrb	w1, [x20, 2]
	bfi	w0, w2, 4, 1
	mov	w2, 1
	bfi	w0, w1, 6, 1
	strh	w2, [x29, 94]
	mov	w1, 0
	ldrb	w2, [x20, 3]
	orr	w0, w0, -128
	bfi	w1, w25, 4, 1
	strb	w0, [x29, 93]
	strb	w1, [x29, 95]
	cbz	w2, .L171
	ldr	w0, [x20, 44]
	lsl	w0, w0, 4
	cmp	w0, 1920
	bhi	.L172
.L171:
	mov	w0, 1
	strb	wzr, [x20, 4]
	strb	w0, [x20, 17]
	mov	w4, 1
	mov	w0, 0
.L173:
	ldrb	w1, [x29, 95]
	mov	x3, x22
	mov	w2, w23
	bfi	w1, w4, 5, 1
	bfi	w1, w0, 6, 1
	mov	w0, 12
	and	w1, w1, 127
	strb	w1, [x29, 95]
	ldr	w19, [x29, 92]
	str	w19, [x20, 964]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC101
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x24, 72]
	mov	x3, x22
	mov	w0, 16
	and	w19, w19, -16
	mov	w2, w23
	mov	w1, w19
	str	w19, [x20, 968]
	bl	MFDE_ConfigReg
	ldr	x1, .LC103
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x24, 56]
	mov	x3, x22
	mov	w0, 20
	and	w19, w19, -16
	mov	w2, w23
	mov	w1, w19
	str	w19, [x20, 972]
	bl	MFDE_ConfigReg
	ldr	x1, .LC105
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x20, 736]
	mov	x3, x22
	mov	w0, 24
	and	w19, w19, -16
	mov	w2, w23
	mov	w1, w19
	str	w19, [x20, 976]
	str	w19, [x29, 92]
	bl	MFDE_ConfigReg
	ldr	x1, .LC107
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w0, [x20, 44]
	mov	w1, 0
	cmp	w0, 256
	bhi	.L174
	cmp	w0, 119
	mov	w1, 1
	bhi	.L190
.L174:
	mov	x3, x22
	mov	w2, w23
	mov	w0, 4
	mov	w19, 3075
	movk	w19, 0x30, lsl 16
	bl	SCD_ConfigReg
	str	w19, [x29, 92]
	mov	w0, 60
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 64
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 68
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 72
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 76
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 80
	bl	MFDE_ConfigReg
	mov	x3, x22
	mov	w2, w23
	mov	w1, w19
	mov	w0, 84
	bl	MFDE_ConfigReg
	cmp	w21, 1
	beq	.L191
.L175:
	ldr	w1, [x20, 308]
	mov	x3, x22
	mov	w0, 96
	mov	w2, w23
	mov	w21, 0
	add	x1, x20, x1, lsl 2
	ldr	w19, [x1, 324]
	and	w19, w19, -16
	str	w19, [x20, 1012]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC114
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x20, 720]
	mov	x3, x22
	mov	w0, 100
	mov	w1, w19
	mov	w2, w23
	str	w19, [x20, 1016]
	bl	MFDE_ConfigReg
	ldr	x1, .LC116
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x20, 320]
	mov	x3, x22
	mov	w0, 104
	mov	w1, w19
	mov	w2, w23
	str	w19, [x20, 1020]
	bl	MFDE_ConfigReg
	ldr	x1, .LC118
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w19, [x20, 732]
	mov	x3, x22
	mov	w0, 108
	mov	w1, w19
	mov	w2, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC120
	mov	w2, w19
	mov	w0, 3
	mov	w19, 0
	bl	dprint_vfmw
	ldr	w25, [x24, 1180]
	mov	x3, x22
	mov	w0, 128
	and	w25, w25, -16
	mov	w2, w23
	mov	w1, w25
	str	w25, [x20, 1036]
	bl	MFDE_ConfigReg
	ldr	x1, .LC122
	mov	w2, w25
	mov	w0, 3
	bl	dprint_vfmw
	str	wzr, [x29, 92]
	ldr	w0, [x24, 1184]
	mov	x3, x22
	strh	w0, [x29, 92]
	mov	w2, w23
	mov	w0, 132
	ldr	w24, [x29, 92]
	str	w24, [x20, 1040]
	mov	w1, w24
	bl	MFDE_ConfigReg
	ldr	x1, .LC124
	mov	w2, w24
	mov	w0, 3
	bl	dprint_vfmw
	add	x1, x20, 1056
	.p2align 2
.L176:
	ldr	w0, [x1], 4
	and	w0, w0, 3
	lsl	w0, w0, w19
	add	w19, w19, 2
	cmp	w19, 32
	orr	w21, w0, w21
	bne	.L176
	mov	x3, x22
	mov	w1, w21
	mov	w0, 148
	mov	w2, w23
	bl	MFDE_ConfigReg
	ldr	x1, .LC126
	mov	w2, w21
	mov	w0, 3
	bl	dprint_vfmw
	mov	x3, x22
	mov	w2, w23
	mov	w1, 0
	mov	w0, 152
	bl	MFDE_ConfigReg
	ldr	x1, .LC128
	mov	w2, 0
	mov	w0, 3
	bl	dprint_vfmw
	mov	w0, w19
	mov	x3, x22
	mov	w2, w23
	mov	w1, -1
	bl	MFDE_ConfigReg
	mov	w0, 0
.L167:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L190:
	ldr	w0, [x20, 1184]
	cmp	w0, wzr
	cset	w1, eq
	b	.L174
	.p2align 3
.L172:
	ldrb	w0, [x20, 4]
	mov	w4, 0
	strb	wzr, [x20, 17]
	and	w0, w0, 1
	b	.L173
.L177:
	mov	w25, 0
	mov	w0, 0
	mov	w21, 0
	b	.L168
.L191:
	ldr	x1, .LC108
	mov	x3, x22
	mov	w2, w23
	mov	w0, 92
	ldr	w19, [x1]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC110
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	ldr	w1, [x20, 308]
	mov	w2, w23
	mov	w0, 112
	mov	x3, x22
	add	x1, x20, x1, lsl 2
	ldr	w19, [x1, 452]
	mov	w1, w19
	bl	MFDE_ConfigReg
	ldr	x1, .LC112
	mov	w2, w19
	mov	w0, 3
	bl	dprint_vfmw
	b	.L175
.L189:
	ldr	x2, .LC94
	mov	x3, x22
	ldr	x1, .LC96
	mov	w0, 0
	add	x2, x2, 160
	bl	dprint_vfmw
	mov	w0, -1
	b	.L167
	.size	H264HAL_V5R2C1_CfgVdmReg, .-H264HAL_V5R2C1_CfgVdmReg
	.align	3
.LC92:
	.xword	g_VdmDrvParam
	.align	3
.LC93:
	.xword	g_HalDisable
	.align	3
.LC94:
	.xword	.LANCHOR0
	.align	3
.LC96:
	.xword	.LC95
	.align	3
.LC97:
	.xword	s_pstVfmwChan
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC103:
	.xword	.LC102
	.align	3
.LC105:
	.xword	.LC104
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC108:
	.xword	g_TunnelLineNumber
	.align	3
.LC110:
	.xword	.LC109
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC120:
	.xword	.LC119
	.align	3
.LC122:
	.xword	.LC121
	.align	3
.LC124:
	.xword	.LC123
	.align	3
.LC126:
	.xword	.LC125
	.align	3
.LC128:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_FindNextSlicePara
	.type	H264HAL_FindNextSlicePara, %function
H264HAL_FindNextSlicePara:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x22, x3
	mov	x0, x30
	mov	w20, w2
	mov	w21, w1
	bl	_mcount
	ldr	w1, [x19, 48]
	cmp	w20, w21
	str	w20, [x22]
	bge	.L193
	ldr	x19, [x19, 4056]
	cbz	x19, .L196
	ldr	w0, [x19, 48]
	cmp	w1, w0
	bcc	.L193
	add	w2, w20, 1
	b	.L195
	.p2align 3
.L197:
	ldr	x19, [x19, 4056]
	cbz	x19, .L196
	ldr	w0, [x19, 48]
	cmp	w1, w0
	bcc	.L193
.L195:
	cmp	w21, w2
	str	w2, [x22]
	add	w2, w2, 1
	bne	.L197
.L193:
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L196:
	ldr	x1, .LC130
	mov	w2, 813
	mov	w0, 1
	mov	x19, 0
	bl	dprint_vfmw
	mov	x0, x19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	H264HAL_FindNextSlicePara, .-H264HAL_FindNextSlicePara
	.align	3
.LC130:
	.xword	.LC129
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R2C1_SetPicMsg
	.type	H264HAL_V5R2C1_SetPicMsg, %function
H264HAL_V5R2C1_SetPicMsg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w23, w2
	mov	w21, w3
	str	x1, [x29, 96]
	bl	_mcount
	add	w1, w23, 112
	mov	w0, w23
	str	w1, [x29, 108]
	bl	MEM_Phy2Vir
	mov	x19, x0
	cbz	x0, .L233
	ldp	w3, w2, [x20, 52]
	ldr	w0, [x20, 32]
	mov	w1, -2147483648
	lsl	w2, w2, 27
	ldr	w5, [x20, 60]
	cmp	w0, wzr
	csel	w0, w0, w1, eq
	orr	w1, w2, w3, lsl 28
	ldrb	w2, [x20, 1]
	ldr	w3, [x20, 48]
	cmp	w2, 1
	ldrb	w2, [x20]
	add	x3, x3, x2, lsl 1
	ldr	x2, .LC133
	add	x2, x2, 224
	ldr	w4, [x2, x3, lsl 2]
	ldr	w3, [x20, 36]
	sub	w3, w3, #1
	lsl	w3, w3, 16
	orr	w3, w3, w4, lsl 14
	ldr	w4, [x20, 44]
	sub	w4, w4, #1
	orr	w4, w4, w5, lsl 26
	orr	w2, w4, w1
	ldr	x1, .LC136
	orr	w4, w3, w2
	mov	w3, 33554432
	csel	w3, wzr, w3, ne
	mov	w2, w23
	orr	w0, w0, w3
	orr	w0, w4, w0
	str	w0, [x19]
	mov	w0, 4
	ldr	w3, [x19]
	bl	dprint_vfmw
	ldr	w0, [x20, 312]
	add	w2, w23, 4
	ldr	x1, .LC138
	and	w0, w0, -16
	str	w0, [x19, 4]
	mov	w0, 4
	ldr	w3, [x19, 4]
	bl	dprint_vfmw
	ldr	w0, [x20, 64]
	add	w2, w23, 8
	str	w0, [x19, 8]
	mov	w0, 4
	ldr	x1, .LC140
	ldr	w3, [x19, 8]
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	cbnz	w0, .L234
	str	wzr, [x19, 12]
	add	w2, w23, 12
	ldr	x1, .LC142
	mov	w0, 4
	ldr	w3, [x19, 12]
	str	wzr, [x19, 16]
.L231:
	bl	dprint_vfmw
	ldr	x1, .LC144
	add	w2, w23, 16
	ldr	w3, [x19, 16]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	x22, [x29, 96]
	ldr	x1, .LC146
	add	w2, w23, 20
	mov	w0, 4
	ldr	w3, [x22, 1160]
	and	w3, w3, -16
	str	w3, [x19, 20]
	ldr	w3, [x19, 20]
	bl	dprint_vfmw
	ldr	w0, [x22, 1164]
	add	w2, w23, 24
	ldr	x1, .LC148
	and	w0, w0, -16
	str	w0, [x19, 24]
	mov	w0, 4
	ldr	w3, [x19, 24]
	bl	dprint_vfmw
	ldrb	w0, [x20]
	cmp	w0, 2
	beq	.L208
	ldr	w0, [x20, 316]
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 584]
	and	w0, w0, -16
.L209:
	str	w0, [x19, 28]
	add	w2, w23, 28
	ldr	x1, .LC150
	mov	w0, 4
	ldr	w3, [x19, 28]
	and	w21, w21, -16
	bl	dprint_vfmw
	ldr	x0, [x29, 96]
	add	w2, w23, 32
	ldr	x1, .LC152
	ldr	w0, [x0, 1168]
	and	w0, w0, -16
	str	w0, [x19, 32]
	mov	w0, 4
	ldr	w3, [x19, 32]
	bl	dprint_vfmw
	str	w21, [x19, 36]
	ldr	x1, .LC154
	add	w2, w23, 36
	ldr	w3, [x19, 36]
	mov	w0, 4
	bl	dprint_vfmw
	ldr	w21, [x20, 936]
	ldr	x22, .LC156
	cbz	w21, .L210
	add	w27, w23, 40
	mov	w24, 0
	.p2align 2
.L211:
	uxtw	x0, w24
	mov	w3, w27
	add	x5, x0, 10
	add	w2, w24, 10
	add	x4, x20, x0, lsl 2
	mov	x1, x22
	mov	w0, 4
	add	w24, w24, 1
	add	w27, w27, w0
	ldr	w4, [x4, 744]
	add	x4, x20, x4, lsl 2
	ldr	w4, [x4, 324]
	and	w4, w4, -16
	str	w4, [x19, x5, lsl 2]
	ldr	w4, [x19, x5, lsl 2]
	bl	dprint_vfmw
	ldr	w21, [x20, 936]
	cmp	w21, w24
	bhi	.L211
	cmp	w21, 15
	bhi	.L215
.L210:
	add	w2, w21, 10
	add	w24, w23, w2, lsl 2
	.p2align 2
.L214:
	ldr	w5, [x20, 744]
	uxtw	x4, w21
	add	x4, x4, 10
	mov	w3, w24
	mov	w0, 4
	mov	x1, x22
	add	x5, x20, x5, lsl 2
	add	w21, w21, 1
	add	w24, w24, w0
	ldr	w5, [x5, 324]
	and	w5, w5, -16
	str	w5, [x19, x4, lsl 2]
	ldr	w4, [x19, x4, lsl 2]
	bl	dprint_vfmw
	cmp	w21, 15
	add	w2, w21, 10
	bls	.L214
.L215:
	ldr	x0, [x29, 96]
	add	w2, w23, 104
	ldr	x1, .LC158
	ldr	w3, [x0, 1104]
	mov	w0, 4
	and	w3, w3, -16
	str	w3, [x19, 104]
	ldr	w3, [x19, 104]
	bl	dprint_vfmw
	ldr	w21, [x20, 936]
	cbz	w21, .L235
	add	w24, w23, 108
	mov	w28, 27
	mov	w26, w24
	mov	w27, 0
	.p2align 2
.L217:
	add	x25, x20, x27, uxtw 2
	ubfiz	x4, x27, 1, 31
	add	x4, x4, 27
	mov	w3, w26
	lsl	x21, x4, 2
	mov	w2, w28
	ldr	w6, [x25, 808]
	mov	x1, x22
	str	w6, [x19, x4, lsl 2]
	mov	w0, 4
	add	w27, w27, 1
	ldr	w4, [x19, w28, uxtw 2]
	bl	dprint_vfmw
	add	x4, x21, 4
	add	w6, w28, 1
	ldr	w0, [x25, 872]
	add	w3, w26, 4
	mov	w2, w6
	mov	x1, x22
	str	w0, [x19, x4]
	mov	w0, 4
	add	w28, w28, 2
	add	w26, w26, 8
	ldr	w4, [x19, w6, uxtw 2]
	bl	dprint_vfmw
	ldr	w21, [x20, 936]
	cmp	w21, w27
	bhi	.L217
	cmp	w21, 15
	bhi	.L219
.L216:
	lsl	w27, w21, 1
	add	w28, w24, w21, lsl 3
	.p2align 2
.L218:
	uxtw	x4, w27
	add	w6, w27, 27
	add	x4, x4, 27
	mov	w3, w28
	lsl	x26, x4, 2
	mov	w2, w6
	mov	x1, x22
	mov	w0, 4
	str	wzr, [x19, x4, lsl 2]
	add	w21, w21, 1
	ldr	w4, [x19, w6, uxtw 2]
	bl	dprint_vfmw
	add	x5, x26, 4
	add	w4, w27, 28
	ldr	w0, [x29, 108]
	sub	w3, w28, w24
	mov	w2, w4
	mov	x1, x22
	str	wzr, [x19, x5]
	add	w3, w3, w0
	mov	w0, 4
	add	w27, w27, 2
	ldr	w4, [x19, w4, uxtw 2]
	add	w28, w28, 8
	bl	dprint_vfmw
	cmp	w21, 15
	bls	.L218
.L219:
	ldr	x0, [x29, 96]
	add	x3, x19, 256
	add	w2, w23, 256
	mov	w1, 56
	ldr	w4, [x0, 1176]
	add	x0, x20, 76
	and	w4, w4, -16
	str	w4, [x19, 236]
	bl	Write_V5R2C1_Qmatrix
	mov	w0, 0
.L203:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L234:
	ldr	w0, [x20, 68]
	add	w2, w23, 12
	str	w0, [x19, 12]
	mov	w0, 4
	ldr	x1, .LC142
	ldr	w3, [x20, 72]
	str	w3, [x19, 16]
	ldr	w3, [x19, 12]
	b	.L231
	.p2align 3
.L208:
	ldr	w1, [x20, 316]
	ldr	w0, [x20, 716]
	add	x1, x20, x1, lsl 2
	ldr	w1, [x1, 584]
	add	w0, w1, w0
	and	w0, w0, -16
	b	.L209
.L235:
	add	w24, w23, 108
	b	.L216
.L233:
	ldr	x2, .LC133
	mov	w0, 0
	ldr	x3, .LC132
	ldr	x1, .LC134
	add	x2, x2, 192
	bl	dprint_vfmw
	mov	w0, -1
	b	.L203
	.size	H264HAL_V5R2C1_SetPicMsg, .-H264HAL_V5R2C1_SetPicMsg
	.align	3
.LC132:
	.xword	.LC131
	.align	3
.LC133:
	.xword	.LANCHOR0
	.align	3
.LC134:
	.xword	.LC7
	.align	3
.LC136:
	.xword	.LC135
	.align	3
.LC138:
	.xword	.LC137
	.align	3
.LC140:
	.xword	.LC139
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC144:
	.xword	.LC143
	.align	3
.LC146:
	.xword	.LC145
	.align	3
.LC148:
	.xword	.LC147
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC152:
	.xword	.LC151
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC158:
	.xword	.LC157
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R2C1_SetSliceMsg
	.type	H264HAL_V5R2C1_SetSliceMsg, %function
H264HAL_V5R2C1_SetSliceMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w3
	mov	x19, x2
	mov	w24, w5
	mov	w23, w7
	bl	_mcount
	mov	w0, w21
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L250
	mov	x2, x0
	mov	w3, w21
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgStreamAddrInfo
	ldr	w0, [x19, 48]
	add	w2, w21, 24
	ldp	w3, w1, [x19, 32]
	and	w0, w0, 1048575
	ubfiz	w1, w1, 24, 2
	orr	w0, w0, w3, lsl 26
	orr	w0, w0, w1
	str	w0, [x20, 24]
	ldr	x1, .LC164
	mov	w0, 4
	ldr	w3, [x20, 24]
	bl	dprint_vfmw
	ldr	x0, .LC165
	ldrb	w4, [x19, 3]
	ldrb	w0, [x0]
	cbnz	w0, .L240
	cbz	w4, .L251
.L240:
	ldp	w2, w3, [x19, 52]
	ldp	w0, w1, [x19, 40]
	ldr	x25, .LC161
	lsl	w2, w2, 2
	ubfiz	w1, w1, 16, 5
	ubfiz	w0, w0, 21, 5
	orr	w0, w0, w1
	orr	w1, w2, w3, lsl 8
	ldrb	w5, [x19]
	orr	w2, w0, w1
	add	x0, x25, 56
	ldrb	w1, [x19, 2]
	ldr	w0, [x0, w5, sxtw 2]
	orr	w1, w0, w1, lsl 15
	orr	w0, w2, w1
	ldr	x1, .LC167
	orr	w0, w0, w4, lsl 14
	str	w0, [x20, 28]
	add	w2, w21, 28
	mov	w0, 4
	ldr	w3, [x20, 28]
	bl	dprint_vfmw
	mov	w3, w21
	mov	x2, x20
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgMvAddrInfo
	ldrb	w2, [x19, 4]
	ldp	w0, w1, [x19, 60]
	ubfiz	w0, w0, 5, 5
	and	w1, w1, 31
	orr	w0, w0, w2, lsl 16
	add	w2, w21, 40
	orr	w0, w0, w1
	str	w0, [x20, 40]
	ldr	x1, .LC169
	mov	w0, 4
	ldr	w3, [x20, 40]
	bl	dprint_vfmw
	ldp	w0, w1, [x19, 68]
	ldr	w2, [x19, 76]
	ubfiz	w1, w1, 8, 4
	ubfiz	w0, w0, 16, 4
	orr	w0, w0, w1
	ldr	x1, .LC171
	orr	w0, w0, w2
	str	w0, [x20, 44]
	add	w2, w21, 44
	mov	w0, 4
	ldr	w3, [x20, 44]
	bl	dprint_vfmw
	ldr	x0, [x19, 4056]
	cbz	x0, .L252
.L242:
	str	w23, [x20, 176]
	and	w24, w24, -16
	str	w24, [x20, 252]
	add	x25, x25, 56
	mov	w23, 0
	ldrb	w0, [x19]
	ldr	w0, [x25, w0, sxtw 2]
	cbz	w0, .L238
	mov	w3, w21
	mov	x2, x20
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgRefPicInfo
	mov	w3, w21
	mov	x2, x20
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgAPCInfo
	mov	w3, w21
	mov	x2, x20
	mov	x1, x19
	mov	x0, x22
	bl	H264HAL_SetSliceMsgWPInfo
.L238:
	mov	w0, w23
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L251:
	ldp	w1, w0, [x22, 40]
	mul	w0, w0, w1
	cmp	w0, 1620
	bls	.L240
	mov	w23, -1
	b	.L238
	.p2align 3
.L252:
	ldr	w0, [x22, 740]
	ldrb	w23, [x19, 1]
	cmp	w0, 262144
	ble	.L244
	add	w23, w23, 1
	mov	w0, 262143
	sdiv	w23, w0, w23
	b	.L242
	.p2align 3
.L244:
	sub	w0, w0, #1
	add	w23, w23, 1
	sdiv	w23, w0, w23
	b	.L242
.L250:
	ldr	x2, .LC161
	mov	w0, 0
	ldr	x3, .LC160
	mov	w23, -1
	ldr	x1, .LC162
	add	x2, x2, 256
	bl	dprint_vfmw
	b	.L238
	.size	H264HAL_V5R2C1_SetSliceMsg, .-H264HAL_V5R2C1_SetSliceMsg
	.align	3
.LC160:
	.xword	.LC11
	.align	3
.LC161:
	.xword	.LANCHOR0
	.align	3
.LC162:
	.xword	.LC7
	.align	3
.LC164:
	.xword	.LC163
	.align	3
.LC165:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC169:
	.xword	.LC168
	.align	3
.LC171:
	.xword	.LC170
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264HAL_V5R2C1_StartDec
	.type	H264HAL_V5R2C1_StartDec, %function
H264HAL_V5R2C1_StartDec:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	sxtw	x22, w1
	mov	x23, x2
	bl	_mcount
	ldr	x20, .LC173
	lsl	x2, x22, 6
	mov	w1, w22
	sub	x2, x2, x22
	mov	x0, x28
	lsl	x2, x2, 2
	sub	x21, x2, x22
	add	x21, x2, x21, lsl 2
	bl	H264HAL_CheckParaValid
	cmn	w0, #1
	add	x21, x20, x21
	beq	.L284
	mov	w1, w22
	mov	x0, x21
	bl	H264HAL_GetVdmRegVirAddr
	cmn	w0, #1
	beq	.L284
	ldr	x3, .LC174
	mov	w0, 3
	ldr	x1, .LC176
	ldr	w2, [x3]
	add	w2, w2, 1
	str	w2, [x3]
	bl	dprint_vfmw
	mov	x3, x23
	mov	w2, w22
	mov	x1, x21
	mov	x0, x28
	bl	H264HAL_V5R2C1_CfgVdmReg
	cmn	w0, #1
	beq	.L284
	ldp	w2, w3, [x21, 72]
	mov	x1, x21
	mov	x0, x28
	bl	H264HAL_V5R2C1_SetPicMsg
	ldr	x26, [x28, 944]
	ldr	w0, [x28, 1188]
	cmp	w0, 1
	beq	.L285
	ldr	w19, [x26, 48]
	mov	w23, 0
	cbnz	w19, .L286
.L260:
	add	x24, x22, x22, lsl 2
	ldr	w1, [x28, 940]
	lsl	x24, x24, 4
	mov	w27, 0
	sub	x24, x24, x22
	mov	w19, 0
	lsl	x0, x24, 1
	str	x0, [x29, 104]
	.p2align 2
.L262:
	cmp	w19, w1
	bge	.L287
.L267:
	ldr	w6, [x26, 48]
	cmp	w6, w27
	ccmp	w19, wzr, 4, ls
	bgt	.L262
	ldr	x0, [x29, 104]
	add	w4, w23, 4
	add	w5, w23, 5
	add	w4, w4, w19
	sub	x25, x0, x22
	add	w24, w19, w5
	lsl	x25, x25, 1
	add	x3, x29, 140
	add	x4, x25, x4, sxtw
	add	x7, x25, x24, sxtw
	add	w2, w19, 1
	mov	x0, x26
	add	x4, x20, x4, lsl 2
	add	x7, x20, x7, lsl 2
	mov	w27, w6
	stp	w5, w6, [x29, 112]
	ldr	w4, [x4, 56]
	str	w4, [x29, 120]
	ldr	w4, [x7, 56]
	str	w4, [x29, 124]
	bl	H264HAL_FindNextSlicePara
	mov	x9, x0
	mov	w0, 140
	cbz	x9, .L284
	ldr	w19, [x29, 140]
	ldr	w1, [x28, 940]
	ldp	w5, w6, [x29, 112]
	cmp	w1, w19
	ldr	w4, [x29, 120]
	add	w5, w5, w19
	ccmp	w24, w0, 4, ne
	add	x5, x25, x5, sxtw
	beq	.L288
	add	x5, x20, x5, lsl 2
	ldr	w7, [x9, 48]
	ldr	w3, [x29, 124]
	mov	x2, x26
	sub	w7, w7, #1
	mov	x1, x21
	ldr	w5, [x5, 56]
	mov	x0, x28
	mov	x26, x9
	bl	H264HAL_V5R2C1_SetSliceMsg
	cbnz	w0, .L266
.L289:
	ldr	w1, [x28, 940]
	cmp	w19, w1
	blt	.L267
.L287:
	cmp	w1, wzr
	ble	.L268
	add	x0, x22, x22, lsl 2
	add	w1, w1, 4
	lsl	x0, x0, 4
	add	w1, w1, w23
	sub	x0, x0, x22
	lsl	x0, x0, 1
	sub	x0, x0, x22
	lsl	x0, x0, 1
	add	x0, x0, x1, sxtw
	add	x20, x20, x0, lsl 2
	ldr	w0, [x20, 56]
	bl	H264HAL_V5R2C1_CutSliceChain
	mov	w0, 0
.L255:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L288:
	ldr	w0, [x28, 44]
	mov	x2, x26
	ldr	w7, [x28, 36]
	mov	w5, 0
	ldr	w3, [x29, 124]
	mov	x1, x21
	str	xzr, [x26, 4056]
	mov	x26, x9
	mul	w7, w0, w7
	mov	x0, x28
	ldr	w19, [x28, 940]
	sub	w7, w7, #1
	bl	H264HAL_V5R2C1_SetSliceMsg
	cbz	w0, .L289
.L266:
	ldr	x1, .LC178
	mov	w2, 1203
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L268:
	ldr	x1, .LC180
	mov	w0, 1
	bl	dprint_vfmw
.L284:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L285:
	ldr	w1, [x28, 940]
	cmp	w1, 1
	ble	.L258
	.p2align 2
.L259:
	add	w0, w0, 1
	ldr	x26, [x26, 4056]
	cmp	w0, w1
	bne	.L259
.L258:
	lsl	x0, x22, 6
	ldr	w1, [x28, 44]
	sub	x0, x0, x22
	ldr	w7, [x28, 36]
	lsl	x0, x0, 2
	ldr	w6, [x26, 48]
	sub	x22, x0, x22
	mov	w5, 0
	mul	w7, w1, w7
	add	x0, x0, x22, lsl 2
	mov	x2, x26
	add	x20, x20, x0
	mov	w4, 0
	mov	x0, x28
	sub	w7, w7, #1
	mov	x1, x21
	ldr	w3, [x20, 76]
	bl	H264HAL_V5R2C1_SetSliceMsg
	cbz	w0, .L255
	ldr	x1, .LC178
	mov	w2, 1116
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L255
	.p2align 3
.L286:
	ldp	w10, w9, [x26, 8]
	ldp	w8, w27, [x26, 16]
	str	wzr, [x26, 48]
	mov	w23, 1
	stp	wzr, wzr, [x26, 16]
	stp	w23, wzr, [x26, 8]
	ldp	w25, w24, [x26, 24]
	ldr	w0, [x28, 736]
	sub	w7, w19, #1
	stp	w0, wzr, [x26, 24]
	mov	w6, 0
	mov	x2, x26
	ldp	w4, w3, [x21, 72]
	ldr	w5, [x21, 80]
	mov	x1, x21
	mov	x0, x28
	str	w8, [x29, 124]
	stp	w10, w9, [x29, 116]
	bl	H264HAL_V5R2C1_SetSliceMsg
	ldp	w10, w9, [x29, 116]
	ldr	w8, [x29, 124]
	cbnz	w0, .L290
	stp	w10, w9, [x26, 8]
	stp	w8, w27, [x26, 16]
	stp	w25, w24, [x26, 24]
	str	w19, [x26, 48]
	ldr	x26, [x28, 944]
	b	.L260
.L290:
	ldr	x1, .LC178
	mov	w2, 1150
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L255
	.size	H264HAL_V5R2C1_StartDec, .-H264HAL_V5R2C1_StartDec
	.align	3
.LC173:
	.xword	g_HwMem
	.align	3
.LC174:
	.xword	.LANCHOR1
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC180:
	.xword	.LC179
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11323, %object
	.size	__func__.11323, 23
__func__.11323:
	.string	"H264HAL_V5R2C1_InitHal"
	.zero	1
	.type	__func__.11338, %object
	.size	__func__.11338, 29
__func__.11338:
	.string	"H264HAL_V5R2C1_CutSliceChain"
	.zero	3
	.type	g_SliceTypeForPMV, %object
	.size	g_SliceTypeForPMV, 12
g_SliceTypeForPMV:
	.word	1
	.word	2
	.word	0
	.zero	4
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
	.type	__func__.11472, %object
	.size	__func__.11472, 23
__func__.11472:
	.string	"H264HAL_CheckParaValid"
	.zero	1
	.type	__func__.11490, %object
	.size	__func__.11490, 25
__func__.11490:
	.string	"H264HAL_V5R2C1_CfgVdmReg"
	.zero	7
	.type	__func__.11516, %object
	.size	__func__.11516, 25
__func__.11516:
	.string	"H264HAL_V5R2C1_SetPicMsg"
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
	.type	__func__.11546, %object
	.size	__func__.11546, 27
__func__.11546:
	.string	"H264HAL_V5R2C1_SetSliceMsg"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"line: %d, p = NULL is not expected value!\n" )
	.zero	5
.LC4:
	ASCII(.string	"pHwMem is NULL!\n" )
	.zero	7
.LC7:
	ASCII(.string	"%s: %s\n" )
.LC9:
	ASCII(.string	"H264HAL_V5R2C1_InitHal return error.\n" )
	.zero	2
.LC11:
	ASCII(.string	"can not map slice msg virtual address!\n" )
.LC17:
	ASCII(.string	"qmatrix[%d] = 0x%x\n" )
	.zero	4
.LC19:
	ASCII(.string	"picmsg Dxx addr 0x%x = 0x%x\n" )
	.zero	3
.LC21:
	ASCII(.string	"Before slicemsg D[%d] tmp =0x%x,bitsoffset =0x%x,bytespos = 0x%x\n" )
	.zero	6
.LC23:
	ASCII(.string	"slicemsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	7
.LC26:
	ASCII(.string	"slicemsg g_pListX[1][0]->frame_store->pmv_address_idc = %d\n" )
	.zero	4
.LC28:
	ASCII(.string	"slicemsg D[6] addr 0x%x = 0x%x\n" )
.LC30:
	ASCII(.string	"slicemsg D[7] addr 0x%x = 0x%x\n" )
.LC34:
	ASCII(.string	"slicemsg D[%d] address 0x%x = 0x%x\n" )
	.zero	4
.LC44:
	ASCII(.string	"slicemsg burst1 D0~D31, burst2 D0~31, burst3 D0~D31 list0size = %d\n" )
	.zero	4
.LC47:
	ASCII(.string	"luma_lg = %d\n" )
	.zero	2
.LC49:
	ASCII(.string	"wp_weight_l0_y = %d\n" )
	.zero	3
.LC51:
	ASCII(.string	"wp_offset_l0_y = %d\n" )
	.zero	3
.LC53:
	ASCII(.string	"chroma_lg = %d\n" )
.LC55:
	ASCII(.string	"wp_weight_l1_y = %d\n" )
	.zero	3
.LC57:
	ASCII(.string	"wp_offset_l1_y = %d\n" )
	.zero	3
.LC59:
	ASCII(.string	"wp_weight_l0_u = %d\n" )
	.zero	3
.LC61:
	ASCII(.string	"wp_offset_l0_u = %d\n" )
	.zero	3
.LC63:
	ASCII(.string	"wp_weight_l1_u = %d\n" )
	.zero	3
.LC65:
	ASCII(.string	"wp_offset_l1_u = %d\n" )
	.zero	3
.LC67:
	ASCII(.string	"wp_weight_l0_v = %d\n" )
	.zero	3
.LC69:
	ASCII(.string	"wp_offset_l0_v = %d\n" )
	.zero	3
.LC71:
	ASCII(.string	"wp_weight_l1_v = %d\n" )
	.zero	3
.LC73:
	ASCII(.string	"wp_offset_l1_v = %d\n" )
	.zero	3
.LC75:
	ASCII(.string	"slicemsg burst1 D32~D63, burst2 D32~63, burst3 D32~D63 list1size = %d\n" )
	.zero	1
.LC79:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC81:
	ASCII(.string	"point of picture para null\n" )
	.zero	4
.LC84:
	ASCII(.string	"picture width out of range\n" )
	.zero	4
.LC86:
	ASCII(.string	"point of fst slice para null\n" )
	.zero	2
.LC88:
	ASCII(.string	"VdhId is wrong! H264HAL_V200R003_StartDec\n" )
	.zero	5
.LC90:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC95:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC98:
	ASCII(.string	"BASIC_V5R2C1_CFG0 = 0x%x\n" )
	.zero	6
.LC100:
	ASCII(.string	"BASIC_V5R2C1_CFG1 = 0x%x\n" )
	.zero	6
.LC102:
	ASCII(.string	"AVM_V5R2C1_ADDR = 0x%x\n" )
.LC104:
	ASCII(.string	"VAM_V5R2C1_ADDR = 0x%x\n" )
.LC106:
	ASCII(.string	"STREAM_V5R2C1_BASE_ADDR = 0x%x\n" )
.LC109:
	ASCII(.string	"VREG_PART_DEC_OVER_INT_LEVEL=0x%x\n" )
	.zero	5
.LC111:
	ASCII(.string	"VREG_LINE_NUM_STADDR = 0x%x\n" )
	.zero	3
.LC113:
	ASCII(.string	"YSTADDR_V5R2C1_1D = 0x%x\n" )
	.zero	6
.LC115:
	ASCII(.string	"YSTRIDE_V5R2C1_1D = 0x%x\n" )
	.zero	6
.LC117:
	ASCII(.string	"UVOFFSET_V5R2C1_1D = 0x%x\n" )
	.zero	5
.LC119:
	ASCII(.string	"HEAD_INF_OFFSET_V5R2C1_1D = 0x%x\n" )
	.zero	6
.LC121:
	ASCII(.string	"PPFD_V5R2C1_BUF_ADDR = 0x%x\n" )
	.zero	3
.LC123:
	ASCII(.string	"PPFD_V5R2C1_BUF_LEN = 0x%x\n" )
	.zero	4
.LC125:
	ASCII(.string	"REF_V5R2C1_PIC_TYPE = 0x%x\n" )
	.zero	4
.LC127:
	ASCII(.string	"FF_V5R2C1_APT_EN = 0x%x\n" )
	.zero	7
.LC129:
	ASCII(.string	"line %d pSlicePara is NULL!\n" )
	.zero	3
.LC131:
	ASCII(.string	"can not map down msg virtual address!\n" )
	.zero	1
.LC135:
	ASCII(.string	"picmsg D[0] addr 0x%x = 0x%x\n" )
	.zero	2
.LC137:
	ASCII(.string	"picmsg D[1] addr 0x%x = 0x%x\n" )
	.zero	2
.LC139:
	ASCII(.string	"picmsg D[2] addr 0x%x = 0x%x\n" )
	.zero	2
.LC141:
	ASCII(.string	"picmsg D[3] addr 0x%x = 0x%x\n" )
	.zero	2
.LC143:
	ASCII(.string	"picmsg D[4] addr 0x%x = 0x%x\n" )
	.zero	2
.LC145:
	ASCII(.string	"picmsg D[5] addr 0x%x = 0x%x\n" )
	.zero	2
.LC147:
	ASCII(.string	"picmsg D[6] addr 0x%x = 0x%x\n" )
	.zero	2
.LC149:
	ASCII(.string	"picmsg D[7] addr 0x%x = 0x%x\n" )
	.zero	2
.LC151:
	ASCII(.string	"picmsg D[8] addr 0x%x = 0x%x\n" )
	.zero	2
.LC153:
	ASCII(.string	"picmsg D[9] addr 0x%x = 0x%x\n" )
	.zero	2
.LC155:
	ASCII(.string	"picmsg D[%d] addr 0x%x = 0x%x\n" )
	.zero	1
.LC157:
	ASCII(.string	"picmsg D[26] addr 0x%x = 0x%x\n" )
	.zero	1
.LC163:
	ASCII(.string	"slicemsg D[4] addr 0x%x = 0x%x\n" )
.LC166:
	ASCII(.string	"slicemsg D[5] addr 0x%x = 0x%x\n" )
.LC168:
	ASCII(.string	"slicemsg D[8] addr 0x%x = 0x%x\n" )
.LC170:
	ASCII(.string	"slicemsg D[9] addr 0x%x = 0x%x\n" )
.LC175:
	ASCII(.string	"\n\n***********************H264HAL_V200R003_StartDec is Now %d***********************\n" )
	.zero	3
.LC177:
	ASCII(.string	"line %d Set slice msg not wrong!\n" )
	.zero	6
.LC179:
	ASCII(.string	"!!! no slice to dec, add up msg report." )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	StartCnt.11568, %object
	.size	StartCnt.11568, 4
StartCnt.11568:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
