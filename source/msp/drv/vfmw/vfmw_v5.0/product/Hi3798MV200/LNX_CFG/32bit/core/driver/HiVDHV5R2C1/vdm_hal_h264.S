#include "hi_asm_define.h"
	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"vdm_hal_h264.c"
	.text
	.align	2
	.global	Write_V5R2C1_CabacTab
	.type	Write_V5R2C1_CabacTab, %function
Write_V5R2C1_CabacTab:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L5
	ldr	r3, .L6
	mov	r2, #5120
	ldr	r1, .L6+4
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L5:
	mov	r2, #51
	ldr	r1, .L6+8
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L7:
	.align	2
.L6:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_CabacMN
	.word	.LC0
	UNWIND(.fnend)
	.size	Write_V5R2C1_CabacTab, .-Write_V5R2C1_CabacTab
	.align	2
	.global	H264HAL_V5R2C1_InitHal
	.type	H264HAL_V5R2C1_InitHal, %function
H264HAL_V5R2C1_InitHal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r3, r0, #0
	beq	.L14
	ldr	r0, [r3, #1088]
	bl	Write_V5R2C1_CabacTab
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r1, .L15
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L14:
	ldr	r3, .L15+4
	ldr	r2, .L15+8
	ldr	r1, .L15+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L16:
	.align	2
.L15:
	.word	.LC3
	.word	.LC1
	.word	.LANCHOR0
	.word	.LC2
	UNWIND(.fnend)
	.size	H264HAL_V5R2C1_InitHal, .-H264HAL_V5R2C1_InitHal
	.align	2
	.global	Get_V5R2C1_VirAddr
	.type	Get_V5R2C1_VirAddr, %function
Get_V5R2C1_VirAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r1, r0, lsl #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Get_V5R2C1_VirAddr, .-Get_V5R2C1_VirAddr
	.align	2
	.global	Get_V5R2C1_PhyAddr
	.type	Get_V5R2C1_PhyAddr, %function
Get_V5R2C1_PhyAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r1, r0, lsl #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Get_V5R2C1_PhyAddr, .-Get_V5R2C1_PhyAddr
	.align	2
	.global	H264HAL_V5R2C1_CutSliceChain
	.type	H264HAL_V5R2C1_CutSliceChain, %function
H264HAL_V5R2C1_CutSliceChain:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L22
	mov	r0, #0
	str	r0, [r3, #252]
	ldmfd	sp, {fp, sp, pc}
.L22:
	ldr	r3, .L23
	ldr	r2, .L23+4
	ldr	r1, .L23+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L24:
	.align	2
.L23:
	.word	.LC4
	.word	.LANCHOR0+24
	.word	.LC2
	UNWIND(.fnend)
	.size	H264HAL_V5R2C1_CutSliceChain, .-H264HAL_V5R2C1_CutSliceChain
	.align	2
	.global	Write_V5R2C1_Qmatrix
	.type	Write_V5R2C1_Qmatrix, %function
Write_V5R2C1_Qmatrix:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r9, r1, #0
	mov	r8, r0
	mov	r10, r2
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	sub	r6, r3, #4
	sub	r7, r0, #4
	mov	r4, #0
.L27:
	ldr	r3, [r7, #4]!
	mov	r2, r4
	ldr	r1, .L30
	mov	r0, #4
	add	r4, r4, #1
	mov	r5, r7
	str	r3, [r6, #4]!
	ldr	r3, [r5], r10
	bl	dprint_vfmw
	ldr	r3, [r6]
	rsb	r2, r8, r5
	ldr	r1, .L30+4
	mov	r0, #4
	bl	dprint_vfmw
	cmp	r4, r9
	bne	.L27
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L31:
	.align	2
.L30:
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	Write_V5R2C1_Qmatrix, .-Write_V5R2C1_Qmatrix
	.align	2
	.global	H264HAL_SetSliceMsgStreamAddrInfo
	.type	H264HAL_SetSliceMsgStreamAddrInfo, %function
H264HAL_SetSliceMsgStreamAddrInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	add	r10, r1, #4
	add	r7, r3, #4
	add	r5, r2, #4
	mov	r6, r2
	mov	r4, #0
	str	r0, [fp, #-56]
.L35:
	ldr	r8, [r10, #4]!
	sub	r3, r7, #4
	mov	r2, r4
	ldr	r1, .L37
	cmp	r8, #0
	mov	r0, #4
	add	r9, r4, #1
	beq	.L33
	ldr	r3, [r10, #16]
	mov	r2, r9
	ldr	ip, [fp, #-56]
	mov	r1, r3
	ldr	r3, [r10, #8]
	ldr	ip, [ip, #736]
	add	r8, r3, r1, lsl #3
	str	r1, [fp, #-52]
	and	r8, r8, #127
	str	r1, [sp, #4]
	str	r3, [sp]
	bic	ip, ip, #15
	ldr	r1, .L37+4
	mov	r3, r8
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	str	r8, [r5]
	mov	r2, r9
	ldr	ip, [r6, #4]
	mov	r3, r7
	ldr	r1, .L37
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r10]
	add	r3, r7, #4
	add	r2, r4, #2
	ldr	r1, .L37
	mov	r0, #4
	str	ip, [r5, #4]
	ldr	ip, [r5, #4]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r1, [fp, #-52]
	ldr	ip, [fp, #-48]
	mov	r2, r4
	bic	r3, r1, #15
	mov	r0, #4
	rsb	r3, ip, r3
	str	r3, [r6]
	ldr	ip, [r5, #-4]
	sub	r3, r7, #4
	ldr	r1, .L37
	str	ip, [sp]
	bl	dprint_vfmw
.L34:
	add	r4, r4, #3
	add	r5, r5, #12
	cmp	r4, #6
	add	r6, r6, #12
	add	r7, r7, #12
	bne	.L35
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L33:
	str	r8, [r6]
	ldr	ip, [r5, #-4]
	str	ip, [sp]
	bl	dprint_vfmw
	str	r8, [r5]
	ldr	ip, [r6, #4]
	mov	r3, r7
	add	r2, r4, #1
	ldr	r1, .L37
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	str	r8, [r5, #4]
	ldr	ip, [r5, #4]
	add	r3, r7, #4
	add	r2, r4, #2
	ldr	r1, .L37
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L34
.L38:
	.align	2
.L37:
	.word	.LC8
	.word	.LC7
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgStreamAddrInfo, .-H264HAL_SetSliceMsgStreamAddrInfo
	.align	2
	.global	H264HAL_SetSliceMsgMvAddrInfo
	.type	H264HAL_SetSliceMsgMvAddrInfo, %function
H264HAL_SetSliceMsgMvAddrInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r6, r1
	ldr	r1, .L50
	ldrb	ip, [r6]	@ zero_extendqisi2
	mov	r5, r3
	mov	r4, r2
	mov	r7, r0
	add	r1, r1, ip, lsl #2
	ldr	r3, [r1, #56]
	cmp	r3, #2
	movne	r3, #0
	movne	r2, r3
	beq	.L48
.L40:
	str	r2, [r4, #32]
	mov	r0, #4
	add	r2, r5, #32
	str	r3, [r4, #36]
	ldr	r1, .L50+4
	ldr	r3, [r4, #32]
	bl	dprint_vfmw
	ldr	r3, [r4, #36]
	add	r2, r5, #36
	ldr	r1, .L50+8
	mov	r0, #4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L48:
	ldr	r2, [r6, #2788]
	mov	r0, #4
	ldr	r1, .L50+12
	bl	dprint_vfmw
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L41
	ldrb	r2, [r6, #2778]	@ zero_extendqisi2
	cmp	r2, #3
	ldr	r2, [r6, #2788]
	beq	.L49
.L47:
	add	r2, r2, #146
	ldr	r2, [r7, r2, asl #2]
	bic	r2, r2, #15
	b	.L40
.L41:
	ldr	r3, [r6, #2776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #768
	beq	.L46
	ldrb	r3, [r6, #2776]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L46
	ldr	r1, [r6, #2788]
	mov	r3, #0
	ldr	r0, [r7, #716]
	add	r1, r1, #146
	ldr	r2, [r7, r1, asl #2]
	add	r2, r2, r0
	bic	r2, r2, #15
	b	.L40
.L46:
	ldr	r2, [r6, #2788]
	mov	r3, #0
	b	.L47
.L49:
	add	r2, r2, #146
	ldr	r3, [r7, #716]
	ldr	r2, [r7, r2, asl #2]
	add	r3, r2, r3
	bic	r2, r2, #15
	bic	r3, r3, #15
	b	.L40
.L51:
	.align	2
.L50:
	.word	.LANCHOR0
	.word	.LC10
	.word	.LC11
	.word	.LC9
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgMvAddrInfo, .-H264HAL_SetSliceMsgMvAddrInfo
	.global	__aeabi_idiv
	.align	2
	.global	H264HAL_SetSliceMsgEndMbInSlice
	.type	H264HAL_SetSliceMsgEndMbInSlice, %function
H264HAL_SetSliceMsgEndMbInSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	ip, [r1, #4056]
	cmp	ip, #0
	movne	r0, r3
	beq	.L60
.L54:
	mov	r1, #0
	str	r0, [r2, #176]
	mov	r0, r1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L60:
	ldr	r0, [r0, #740]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r0, #262144
	str	r2, [fp, #-16]
	addgt	r1, r1, #1
	addle	r1, r1, #1
	movwgt	r0, #65535
	suble	r0, r0, #1
	movtgt	r0, 3
	bl	__aeabi_idiv
	ldr	r2, [fp, #-16]
	b	.L54
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgEndMbInSlice, .-H264HAL_SetSliceMsgEndMbInSlice
	.align	2
	.global	H264HAL_SetSliceMsgRefPicFrame
	.type	H264HAL_SetSliceMsgRefPicFrame, %function
H264HAL_SetSliceMsgRefPicFrame:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	ip, [fp, #4]
	str	r3, [fp, #-60]
	mov	r10, r0
	str	r2, [fp, #-56]
	add	r2, ip, #3
	add	r9, r1, ip, lsl #2
	mov	r3, ip, asl #3
	add	r3, r3, #20
	str	r3, [fp, #-52]
	ldr	r3, [r9, #52]
	mov	r2, r2, asl #2
	str	r2, [fp, #-48]
	cmp	r3, #0
	beq	.L61
	mov	r4, ip, asl #10
	mov	r5, #0
	add	ip, r4, ip, lsl #7
	mov	r7, r5
	add	r4, r1, ip
	mov	r8, r5
	b	.L67
.L65:
	cmp	r6, #3
	beq	.L74
.L66:
	ldr	r3, [r9, #52]
	cmp	r3, r5
	bls	.L75
.L67:
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	and	r3, r5, #7
	ldr	r2, [r10, #48]
	and	r6, r5, #3
	ldr	r0, .L77
	add	r4, r4, #36
	add	r1, r2, r1, lsl #1
	ldrb	r2, [r4, #1591]	@ zero_extendqisi2
	add	r5, r5, #1
	add	r1, r0, r1, lsl #2
	cmp	r2, #1
	ldr	r2, [r4, #1608]
	ldr	r1, [r1, #68]
	moveq	r0, #8
	movne	r0, #0
	cmp	r3, #7
	and	r1, r1, #3
	mov	r2, r2, asl #1
	orr	r1, r0, r1
	and	r2, r2, #31
	mov	r3, r3, asl #2
	add	r0, r6, r6, lsl #2
	orr	r8, r8, r1, asl r3
	orr	r7, r7, r2, asl r0
	bne	.L65
	ldr	lr, [fp, #-48]
	ldr	r1, [fp, #-56]
	ldr	r0, [fp, #-60]
	mov	r2, lr
	str	r8, [r1, lr, asl #2]
	add	r3, r0, lr, lsl #2
	ldr	ip, [r1, lr, asl #2]
	mov	r0, #4
	ldr	r1, .L77+4
	add	lr, lr, #1
	str	lr, [fp, #-48]
	mov	r8, #0
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r6, #3
	bne	.L66
.L74:
	ldr	lr, [fp, #-52]
	ldr	r1, [fp, #-56]
	ldr	r0, [fp, #-60]
	mov	r2, lr
	str	r7, [r1, lr, asl #2]
	add	r3, r0, lr, lsl #2
	ldr	ip, [r1, lr, asl #2]
	mov	r0, #4
	ldr	r1, .L77+4
	add	lr, lr, #1
	str	lr, [fp, #-52]
	mov	r7, #0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r9, #52]
	cmp	r3, r5
	bhi	.L67
.L75:
	tst	r3, #7
	bne	.L76
.L61:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L76:
	ldr	r4, [fp, #-56]
	mov	r0, #4
	ldr	r2, [fp, #-48]
	ldr	r5, [fp, #-60]
	ldr	r1, .L77+4
	str	r8, [r4, r2, asl #2]
	add	r3, r5, r2, lsl #2
	ldr	ip, [r4, r2, asl #2]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [fp, #-52]
	ldr	r1, .L77+4
	mov	r0, #4
	str	r7, [r4, r2, asl #2]
	add	r3, r5, r2, lsl #2
	ldr	ip, [r4, r2, asl #2]
	str	ip, [fp, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L78:
	.align	2
.L77:
	.word	.LANCHOR0
	.word	.LC12
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgRefPicFrame, .-H264HAL_SetSliceMsgRefPicFrame
	.align	2
	.global	H264HAL_SetSliceMsgRefPicField
	.type	H264HAL_SetSliceMsgRefPicField, %function
H264HAL_SetSliceMsgRefPicField:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	ip, [fp, #4]
	str	r2, [fp, #-56]
	add	r2, ip, #3
	str	r3, [fp, #-60]
	add	r10, r1, ip, lsl #2
	mov	r9, ip, asl #3
	mov	r3, r2, asl #2
	str	r3, [fp, #-52]
	ldr	r3, [r10, #52]
	add	r9, r9, #20
	str	r0, [fp, #-48]
	cmp	r3, #0
	beq	.L79
	mov	r4, ip, asl #10
	mov	r5, #0
	add	ip, r4, ip, lsl #7
	mov	r7, r5
	add	r4, r1, ip
	mov	r8, r5
	b	.L99
.L82:
	cmp	r3, #2
	beq	.L90
	and	r6, r5, #3
	and	r3, r5, #7
.L89:
	cmp	r3, #7
	beq	.L115
.L97:
	cmp	r6, #3
	beq	.L116
.L98:
	ldr	r3, [r10, #52]
	add	r5, r5, #1
	add	r4, r4, #36
	cmp	r3, r5
	bls	.L117
.L99:
	ldrb	r3, [r4, #1624]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L82
	ldrb	r3, [r4, #1625]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L83
	ldr	r1, [fp, #-48]
	and	r3, r5, #7
	ldrb	r2, [r4, #1628]	@ zero_extendqisi2
	ldrb	r0, [r4, #1629]	@ zero_extendqisi2
	ldr	r1, [r1, #48]
	add	r1, r1, r2, lsl #1
.L113:
	cmp	r0, #1
	ldr	r0, .L119
	and	r6, r5, #3
	add	r1, r0, r1, lsl #2
	moveq	r0, #8
	movne	r0, #0
	cmp	r2, #1
	ldr	r2, [r1, #100]
	moveq	r1, #4
	movne	r1, #0
	and	r2, r2, #3
	orr	r1, r1, r0
	orr	r2, r1, r2
	mov	r0, r3, asl #2
	cmp	r3, #7
	add	r1, r6, r6, lsl #2
	orr	r8, r8, r2, asl r0
	ldr	r2, [r4, #1644]
	mov	r2, r2, asl #1
	and	r2, r2, #31
	orr	r7, r7, r2, asl r1
	bne	.L97
.L115:
	ldr	lr, [fp, #-52]
	ldr	r1, [fp, #-56]
	ldr	r0, [fp, #-60]
	mov	r2, lr
	str	r8, [r1, lr, asl #2]
	add	r3, r0, lr, lsl #2
	ldr	ip, [r1, lr, asl #2]
	mov	r0, #4
	ldr	r1, .L119+4
	add	lr, lr, #1
	str	lr, [fp, #-52]
	mov	r8, #0
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r6, #3
	bne	.L98
.L116:
	ldr	r2, [fp, #-56]
	mov	r0, #4
	ldr	r3, [fp, #-60]
	ldr	r1, .L119+4
	str	r7, [r2, r9, asl #2]
	add	r3, r3, r9, lsl #2
	ldr	ip, [r2, r9, asl #2]
	mov	r2, r9
	mov	r7, #0
	add	r9, r9, #1
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L98
.L90:
	ldrb	r3, [r4, #1625]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L91
	ldr	r1, [fp, #-48]
	and	r3, r5, #7
	ldrb	r2, [r4, #1630]	@ zero_extendqisi2
	ldrb	r0, [r4, #1631]	@ zero_extendqisi2
	ldr	r1, [r1, #48]
	add	r1, r1, r2, lsl #1
.L114:
	cmp	r0, #1
	ldr	r0, .L119
	and	r6, r5, #3
	add	r1, r0, r1, lsl #2
	moveq	r0, #8
	movne	r0, #0
	cmp	r2, #1
	ldr	r2, [r1, #100]
	moveq	r1, #4
	movne	r1, #0
	and	r2, r2, #3
	orr	r1, r1, r0
	orr	r2, r1, r2
	mov	r0, r3, asl #2
	add	r1, r6, r6, lsl #2
	orr	r8, r8, r2, asl r0
	ldr	r2, [r4, #1644]
	mov	r2, r2, asl #1
	and	r2, r2, #30
	orr	r2, r2, #1
	orr	r7, r7, r2, asl r1
	b	.L89
.L117:
	tst	r3, #7
	bne	.L118
.L79:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L83:
	ldr	r2, [fp, #-48]
	and	r3, r5, #7
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	ldrb	r0, [r4, #1629]	@ zero_extendqisi2
	ldr	r2, [r2, #48]
	add	r1, r2, r1, lsl #1
	ldrb	r2, [r4, #1628]	@ zero_extendqisi2
	b	.L113
.L91:
	ldr	r2, [fp, #-48]
	and	r3, r5, #7
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	ldrb	r0, [r4, #1631]	@ zero_extendqisi2
	ldr	r2, [r2, #48]
	add	r1, r2, r1, lsl #1
	ldrb	r2, [r4, #1630]	@ zero_extendqisi2
	b	.L114
.L118:
	ldr	r4, [fp, #-56]
	mov	r0, #4
	ldr	r2, [fp, #-52]
	ldr	r5, [fp, #-60]
	ldr	r1, .L119+4
	str	r8, [r4, r2, asl #2]
	add	r3, r5, r2, lsl #2
	ldr	ip, [r4, r2, asl #2]
	str	ip, [sp]
	bl	dprint_vfmw
	str	r7, [r4, r9, asl #2]
	ldr	ip, [r4, r9, asl #2]
	add	r3, r5, r9, lsl #2
	mov	r2, r9
	ldr	r1, .L119+4
	mov	r0, #4
	str	ip, [fp, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L120:
	.align	2
.L119:
	.word	.LANCHOR0
	.word	.LC12
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgRefPicField, .-H264HAL_SetSliceMsgRefPicField
	.align	2
	.global	H264HAL_SetSliceMsgRefPicInfo
	.type	H264HAL_SetSliceMsgRefPicInfo, %function
H264HAL_SetSliceMsgRefPicInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldrb	ip, [r0]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	ip, #0
	mov	r6, r2
	mov	r7, r3
	bne	.L122
	str	ip, [sp]
	bl	H264HAL_SetSliceMsgRefPicFrame
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r3, .L127
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #56]
	cmp	r3, #2
	beq	.L126
.L121:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L122:
	mov	ip, #0
	str	ip, [sp]
	bl	H264HAL_SetSliceMsgRefPicField
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r3, .L127
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #56]
	cmp	r3, #2
	bne	.L121
	mov	ip, #1
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	str	ip, [sp]
	bl	H264HAL_SetSliceMsgRefPicField
	b	.L121
.L126:
	mov	ip, #1
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	str	ip, [sp]
	bl	H264HAL_SetSliceMsgRefPicFrame
	b	.L121
.L128:
	.align	2
.L127:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgRefPicInfo, .-H264HAL_SetSliceMsgRefPicInfo
	.align	2
	.global	H264HAL_SetSliceMsgAPCInfo
	.type	H264HAL_SetSliceMsgAPCInfo, %function
H264HAL_SetSliceMsgAPCInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r5, r1
	ldr	r1, [r5, #3928]!
	mov	r7, r2
	mov	r8, r3
	mov	r4, #0
	and	r1, r1, #31
	mov	r6, #36
.L130:
	add	r4, r4, #1
	and	r3, r4, #3
	cmp	r4, #32
	add	r0, r3, r3, lsl #2
	beq	.L133
	ldr	r2, [r5, #4]!
	cmp	r3, #3
	and	r3, r2, #31
	orr	r1, r1, r3, asl r0
	bne	.L130
	str	r1, [r7, r6, asl #2]
	add	r3, r8, r6, lsl #2
	ldr	ip, [r7, r6, asl #2]
	mov	r2, r6
	ldr	r1, .L134
	mov	r0, #4
	add	r6, r6, #1
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r1, #0
	b	.L130
.L133:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L135:
	.align	2
.L134:
	.word	.LC12
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgAPCInfo, .-H264HAL_SetSliceMsgAPCInfo
	.align	2
	.global	H264HAL_SetSliceMsgWPInfo
	.type	H264HAL_SetSliceMsgWPInfo, %function
H264HAL_SetSliceMsgWPInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	mov	r4, r1
	ldr	r1, [r0, #300]
	str	r2, [fp, #-52]
	cmp	r1, #0
	str	r3, [fp, #-56]
	beq	.L137
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, .L171
	add	r3, r2, r3, lsl #2
	str	r2, [fp, #-48]
	ldr	r3, [r3, #56]
	cmp	r3, #1
	beq	.L138
.L137:
	ldr	r3, [r0, #304]
	cmp	r3, #1
	beq	.L169
.L136:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L169:
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, .L171
	add	r3, r2, r3, lsl #2
	str	r2, [fp, #-48]
	ldr	r3, [r3, #56]
	cmp	r3, #2
	bne	.L136
.L138:
	ldr	r2, [r4, #44]
	mov	r0, #4
	ldr	r1, .L171+4
	mov	r6, #0
	ldr	r5, [fp, #-52]
	bl	dprint_vfmw
	ldr	r7, [fp, #-56]
	add	r10, r5, #256
	add	r9, r5, #512
	add	r8, r5, #768
	mov	r5, r4
	str	r4, [fp, #-60]
.L141:
	ldr	r0, [r5, #88]
	add	r3, r7, #256
	ldrb	r1, [r5, #856]	@ zero_extendqisi2
	add	r2, r6, #64
	ubfx	lr, r0, #0, #9
	ldr	r0, [r4, #80]
	add	r5, r5, #4
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L171+8
	orr	r0, r0, ip
	str	r0, [r10]
	ldr	ip, [r10], #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r0, [r5, #212]
	ldrb	r1, [r5, #980]	@ zero_extendqisi2
	add	r3, r7, #512
	ubfx	lr, r0, #0, #9
	ldr	r0, [r4, #84]
	add	r2, r6, #128
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L171+8
	orr	r0, r0, ip
	str	r0, [r9]
	ldr	ip, [r9], #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldrb	r0, [r5, #1108]	@ zero_extendqisi2
	ldr	r1, [r5, #340]
	add	r3, r7, #768
	add	r2, r6, #192
	add	r6, r6, #1
	ubfx	r1, r1, #0, #9
	orr	r1, r1, r0, asl #9
	str	r1, [r8]
	ldr	ip, [r8], #4
	mov	r0, #4
	ldr	r1, .L171+8
	add	r7, r7, r0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r6, r3
	bls	.L141
	ldr	r2, [r4, #80]
	mov	r0, #4
	ldr	r1, .L171+12
	add	r6, r4, #84
	bl	dprint_vfmw
	add	r5, r4, #852
	mov	r7, #0
.L142:
	ldr	r2, [r6, #4]!
	mov	r0, #4
	ldr	r1, .L171+16
	add	r7, r7, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #4]!
	ldr	r1, .L171+20
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r7, r3
	bls	.L142
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, [fp, #-48]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #56]
	cmp	r3, #2
	beq	.L143
.L146:
	ldr	r2, [r4, #84]
	mov	r0, #4
	ldr	r1, .L171+24
	add	r6, r4, #212
	bl	dprint_vfmw
	add	r5, r4, #980
	mov	r7, #0
.L144:
	ldr	r2, [r6, #4]!
	mov	r0, #4
	ldr	r1, .L171+28
	add	r7, r7, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #4]!
	ldr	r1, .L171+32
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r7, r3
	bls	.L144
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, [fp, #-48]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #56]
	cmp	r3, #2
	beq	.L170
.L147:
	add	r6, r4, #1104
	add	r7, r4, #340
	add	r6, r6, #4
	mov	r5, #0
.L149:
	ldr	r2, [r7, #4]!
	mov	r0, #4
	ldr	r1, .L171+36
	add	r5, r5, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L171+40
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r5, r3
	bls	.L149
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r2, [fp, #-48]
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #56]
	cmp	r3, #2
	bne	.L136
	add	r6, r4, #1488
	add	r7, r4, #724
	add	r6, r6, #4
	mov	r5, #0
.L151:
	ldr	r2, [r7, #4]!
	mov	r0, #4
	ldr	r1, .L171+44
	add	r5, r5, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L171+48
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r2, [r4, #40]
	cmp	r5, r2
	bls	.L151
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r1, [fp, #-48]
	add	r3, r1, r3, lsl #2
	ldr	r3, [r3, #56]
	cmp	r3, #2
	bne	.L136
	ldr	r1, .L171+52
	mov	r0, #4
	ldr	r6, [fp, #-56]
	bl	dprint_vfmw
	ldr	r3, [fp, #-52]
	mov	r5, #0
	ldr	r10, [fp, #-60]
	add	r8, r3, #384
	add	r7, r3, #640
	add	r9, r3, #896
.L152:
	ldr	r0, [r10, #472]
	add	r3, r6, #384
	ldrb	r1, [r10, #1240]	@ zero_extendqisi2
	add	r2, r5, #96
	ubfx	lr, r0, #0, #9
	ldr	r0, [r4, #80]
	add	r10, r10, #4
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L171+8
	orr	r0, r0, ip
	str	r0, [r8]
	ldr	ip, [r8], #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r0, [r10, #596]
	ldrb	r1, [r10, #1364]	@ zero_extendqisi2
	add	r3, r6, #640
	ubfx	lr, r0, #0, #9
	ldr	r0, [r4, #84]
	add	r2, r5, #160
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L171+8
	orr	r0, r0, ip
	str	r0, [r7]
	ldr	ip, [r7], #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldrb	r0, [r10, #1492]	@ zero_extendqisi2
	ldr	r1, [r10, #724]
	add	r3, r6, #896
	add	r2, r5, #224
	add	r5, r5, #1
	ubfx	r1, r1, #0, #9
	orr	r1, r1, r0, asl #9
	str	r1, [r9]
	ldr	ip, [r9], #4
	mov	r0, #4
	ldr	r1, .L171+8
	add	r6, r6, r0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #40]
	cmp	r5, r3
	bls	.L152
	b	.L136
.L170:
	add	r6, r4, #1360
	add	r7, r4, #596
	add	r6, r6, #4
	mov	r5, #0
.L148:
	ldr	r2, [r7, #4]!
	mov	r0, #4
	ldr	r1, .L171+56
	add	r5, r5, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L171+60
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #40]
	cmp	r5, r3
	bls	.L148
	b	.L147
.L143:
	add	r6, r4, #1232
	add	r7, r4, #468
	add	r6, r6, #4
	mov	r5, #0
.L145:
	ldr	r2, [r7, #4]!
	mov	r0, #4
	ldr	r1, .L171+64
	add	r5, r5, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L171+68
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r4, #40]
	cmp	r5, r3
	bls	.L145
	b	.L146
.L172:
	.align	2
.L171:
	.word	.LANCHOR0
	.word	.LC13
	.word	.LC12
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	.LC20
	.word	.LC21
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC22
	.word	.LC23
	.word	.LC18
	.word	.LC19
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgWPInfo, .-H264HAL_SetSliceMsgWPInfo
	.align	2
	.global	H264HAL_CheckParaValid
	.type	H264HAL_CheckParaValid, %function
H264HAL_CheckParaValid:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r1, #0
	bgt	.L180
	cmp	r0, #0
	beq	.L181
	ldr	r3, [r0, #44]
	cmp	r3, #512
	bhi	.L178
	ldr	r3, [r0, #36]
	cmp	r3, #512
	bhi	.L178
	ldr	r0, [r0, #944]
	cmp	r0, #0
	movne	r0, #0
	beq	.L182
.L175:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L180:
	mov	r0, #0
	mov	r3, r1
	str	r0, [sp]
	ldr	r2, .L183
	ldr	r1, .L183+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L175
.L178:
	ldr	r3, .L183+8
	mov	r0, #0
	ldr	r2, .L183
	ldr	r1, .L183+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L175
.L181:
	ldr	r3, .L183+16
	ldr	r2, .L183
	ldr	r1, .L183+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L175
.L182:
	ldr	r3, .L183+20
	ldr	r2, .L183
	ldr	r1, .L183+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L175
.L184:
	.align	2
.L183:
	.word	.LANCHOR0+132
	.word	.LC29
	.word	.LC31
	.word	.LC2
	.word	.LC30
	.word	.LC32
	UNWIND(.fnend)
	.size	H264HAL_CheckParaValid, .-H264HAL_CheckParaValid
	.align	2
	.global	H264HAL_GetVdmRegVirAddr
	.type	H264HAL_GetVdmRegVirAddr, %function
H264HAL_GetVdmRegVirAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	mov	r4, r0
	bgt	.L190
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L188
.L189:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L188:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4]
	bne	.L189
	ldr	r1, .L191
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L190:
	ldr	r1, .L191+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L192:
	.align	2
.L191:
	.word	.LC34
	.word	.LC33
	UNWIND(.fnend)
	.size	H264HAL_GetVdmRegVirAddr, .-H264HAL_GetVdmRegVirAddr
	.align	2
	.global	H264HAL_V5R2C1_CfgVdmReg
	.type	H264HAL_V5R2C1_CfgVdmReg, %function
H264HAL_V5R2C1_CfgVdmReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r4, .L219
	mov	lr, r2, asl #6
	mov	r6, r2
	sub	lr, lr, r2, asl #3
	ldr	ip, .L219+4
	ldrb	r2, [r4]	@ zero_extendqisi2
	mov	r8, r0
	add	ip, ip, lr
	mov	r5, r1
	subs	r2, r2, #1
	mov	r7, r3
	ldr	r1, [ip, #8]
	movne	r2, #1
	cmp	r3, #0
	movne	r0, #0
	andeq	r0, r2, #1
	cmp	r0, #0
	bne	.L217
	ldr	r3, .L219+8
	mov	r0, #8
	ldr	r4, [r3, r1, asl #2]
	cmp	r4, #0
	ldrne	r9, [r4, #1208]
	moveq	r3, r4
	moveq	r9, r4
	uxtbne	r3, r9
	andne	r4, r3, #1
	cmp	r2, #0
	strneb	r3, [r7, #1]
	mov	r3, #0
	ldr	lr, [r8, #1184]
	mov	r2, r6
	ldr	ip, [r8, #740]
	cmp	lr, #1
	str	r3, [fp, #-48]
	ldr	r1, [fp, #-48]
	movne	lr, r3
	moveq	lr, #3
	cmp	ip, #262144
	mov	r3, r7
	suble	ip, ip, #1
	movwgt	ip, #65535
	ubfxle	ip, ip, #0, #20
	movtgt	ip, 3
	bfi	r1, ip, #0, #20
	str	r1, [fp, #-48]
	mov	ip, r1, lsr #24
	mov	r1, r1, lsr #16
	and	ip, ip, #62
	and	r1, r1, #191
	orr	ip, ip, #65
	bfc	r1, #7, #1
	and	ip, ip, #253
	strb	r1, [fp, #-46]
	bfi	ip, lr, #2, #2
	strb	ip, [fp, #-45]
	ldr	r10, [fp, #-48]
	mov	r1, r10
	str	r10, [r8, #956]
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L219+12
	mov	r0, #3
	bl	dprint_vfmw
	ldrb	r2, [r8, #16]	@ zero_extendqisi2
	ldrb	ip, [r8, #2]	@ zero_extendqisi2
	mov	r3, #0
	ldrb	r0, [r8, #3]	@ zero_extendqisi2
	bfi	r3, r2, #4, #1
	bfi	r3, ip, #6, #1
	mov	r2, #0
	cmp	r0, r2
	mov	r1, #0
	mvn	r3, r3, asl #25
	bfi	r1, r2, #0, #4
	mvn	r3, r3, lsr #25
	strb	r1, [fp, #-48]
	strb	r3, [fp, #-47]
	mov	r1, #1
	mov	r3, #0
	strh	r1, [fp, #-46]	@ movhi
	bfi	r3, r4, #4, #1
	strb	r3, [fp, #-45]
	beq	.L199
	ldr	r3, [r8, #44]
	mov	r3, r3, asl #4
	cmp	r3, #1920
	bhi	.L200
.L199:
	mov	r3, #0
	mov	lr, #1
	mov	ip, r3
	strb	lr, [r8, #17]
	strb	r3, [r8, #4]
.L201:
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2
	mov	r3, r7
	mov	r2, r6
	mov	r0, #12
	bfi	r1, lr, #5, #1
	bfi	r1, ip, #6, #1
	bfc	r1, #7, #1
	strb	r1, [fp, #-45]
	ldr	r4, [fp, #-48]
	mov	r1, r4
	str	r4, [r8, #960]
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L219+16
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r4, [r5, #56]
	mov	r3, r7
	mov	r2, r6
	bic	r4, r4, #15
	mov	r0, #16
	str	r4, [r8, #964]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L219+20
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r4, [r5, #40]
	mov	r3, r7
	mov	r2, r6
	bic	r4, r4, #15
	mov	r0, #20
	str	r4, [r8, #968]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L219+24
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r4, [r8, #736]
	mov	r3, r7
	mov	r2, r6
	bic	r4, r4, #15
	mov	r0, #24
	str	r4, [r8, #972]
	mov	r1, r4
	str	r4, [fp, #-48]
	bl	MFDE_ConfigReg
	ldr	r1, .L219+28
	mov	r2, r4
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r3, [r8, #44]
	cmp	r3, #256
	movhi	r1, #0
	bhi	.L202
	cmp	r3, #119
	ldrhi	r1, [r8, #1180]
	movls	r1, #1
	clzhi	r1, r1
	movhi	r1, r1, lsr #5
.L202:
	movw	r4, #3075
	mov	r3, r7
	movt	r4, 48
	mov	r2, r6
	mov	r0, #4
	bl	SCD_ConfigReg
	mov	r1, r4
	mov	r3, r7
	mov	r2, r6
	mov	r0, #60
	str	r4, [fp, #-48]
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #64
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #68
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #72
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #76
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #80
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r6
	mov	r1, r4
	mov	r0, #84
	bl	MFDE_ConfigReg
	cmp	r9, #1
	beq	.L218
.L203:
	ldr	r1, [r8, #308]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #96
	mov	r10, #0
	add	r1, r8, r1, lsl #2
	mov	r4, r10
	ldr	r9, [r1, #324]
	bic	r9, r9, #15
	str	r9, [r8, #1008]
	mov	r1, r9
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L219+32
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r9, [r8, #720]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #100
	mov	r1, r9
	str	r9, [r8, #1012]
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L219+36
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r9, [r8, #320]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #104
	mov	r1, r9
	str	r9, [r8, #1016]
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L219+40
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r9, [r8, #732]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #108
	mov	r1, r9
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L219+44
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r9, [r5, #1164]
	mov	r3, r7
	mov	r2, r6
	bic	r9, r9, #15
	mov	r0, #128
	str	r9, [r8, #1032]
	mov	r1, r9
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L219+48
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r5, #1168]
	str	r10, [fp, #-48]
	mov	r3, r7
	mov	r2, r6
	mov	r0, #132
	strh	r1, [fp, #-48]	@ movhi
	mov	r5, r10
	ldr	r9, [fp, #-48]
	mov	r1, r9
	str	r9, [r8, #1036]
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L219+52
	mov	r0, #3
	bl	dprint_vfmw
	add	r2, r8, #1040
	add	r2, r2, #8
.L204:
	ldr	r3, [r2, #4]!
	and	r3, r3, #3
	orr	r5, r5, r3, asl r4
	add	r4, r4, #2
	cmp	r4, #32
	bne	.L204
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, #148
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L219+56
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r7
	mov	r2, r6
	mov	r1, #0
	mov	r0, #152
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L219+60
	mov	r0, #3
	bl	dprint_vfmw
	mov	r0, r4
	mov	r3, r7
	mov	r2, r6
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, #0
.L195:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L200:
	ldrb	r3, [r8, #4]	@ zero_extendqisi2
	mov	lr, r2
	strb	r2, [r8, #17]
	and	ip, r3, #1
	b	.L201
.L218:
	ldr	r1, .L219+64
	mov	r3, r7
	mov	r2, r6
	mov	r0, #92
	ldr	r4, [r1]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L219+68
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r8, #308]
	mov	r2, r6
	mov	r3, r7
	mov	r0, #112
	add	r1, r8, r1, lsl #2
	ldr	r4, [r1, #452]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L219+72
	mov	r0, #3
	bl	dprint_vfmw
	b	.L203
.L217:
	ldr	r2, .L219+76
	mov	r0, #0
	ldr	r1, .L219+80
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L195
.L220:
	.align	2
.L219:
	.word	g_HalDisable
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC36
	.word	.LC37
	.word	.LC38
	.word	.LC39
	.word	.LC40
	.word	.LC43
	.word	.LC44
	.word	.LC45
	.word	.LC46
	.word	.LC47
	.word	.LC48
	.word	.LC49
	.word	.LC50
	.word	g_TunnelLineNumber
	.word	.LC41
	.word	.LC42
	.word	.LANCHOR0+156
	.word	.LC35
	UNWIND(.fnend)
	.size	H264HAL_V5R2C1_CfgVdmReg, .-H264HAL_V5R2C1_CfgVdmReg
	.align	2
	.global	H264HAL_FindNextSlicePara
	.type	H264HAL_FindNextSlicePara, %function
H264HAL_FindNextSlicePara:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r2, r1
	ldr	lr, [r0, #48]
	str	r2, [r3]
	ldmgefd	sp, {fp, sp, pc}
	ldr	r0, [r0, #4056]
	cmp	r0, #0
	beq	.L225
	ldr	ip, [r0, #48]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
	add	r2, r2, #1
	b	.L224
.L226:
	ldr	r0, [r0, #4056]
	cmp	r0, #0
	beq	.L225
	ldr	ip, [r0, #48]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
.L224:
	cmp	r2, r1
	str	r2, [r3]
	add	r2, r2, #1
	bne	.L226
	ldmfd	sp, {fp, sp, pc}
.L225:
	movw	r2, #813
	ldr	r1, .L230
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L231:
	.align	2
.L230:
	.word	.LC51
	UNWIND(.fnend)
	.size	H264HAL_FindNextSlicePara, .-H264HAL_FindNextSlicePara
	.align	2
	.global	H264HAL_V5R2C1_SetPicMsg
	.type	H264HAL_V5R2C1_SetPicMsg, %function
H264HAL_V5R2C1_SetPicMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	mov	r4, r0
	mov	r0, r2
	mov	r5, r3
	str	r2, [fp, #-52]
	str	r1, [fp, #-56]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-48]
	beq	.L264
	ldrb	r1, [r4]	@ zero_extendqisi2
	ldr	r0, [r4, #52]
	ldr	ip, [r4, #48]
	ldr	r3, [r4, #56]
	add	ip, ip, r1, lsl #1
	mov	r0, r0, asl #28
	ldr	r1, [r4, #60]
	orr	r3, r0, r3, asl #27
	ldr	lr, .L268
	ldr	r0, [r4, #44]
	add	ip, lr, ip, lsl #2
	orr	r1, r3, r1, asl #26
	sub	r0, r0, #1
	ldr	r3, [r4, #36]
	orr	r1, r1, r0
	ldr	r0, [r4, #32]
	ldr	ip, [ip, #212]
	sub	r3, r3, #1
	ldrb	lr, [r4, #1]	@ zero_extendqisi2
	cmp	r0, #0
	ldr	r6, [fp, #-48]
	orr	r1, r1, r3, asl #16
	ldr	r7, [fp, #-52]
	orr	r3, r1, ip, asl #14
	movne	r0, #-2147483648
	cmp	lr, #1
	orr	r3, r3, r0
	ldr	r1, .L268+4
	moveq	ip, #33554432
	movne	ip, #0
	mov	r2, r7
	orr	r3, r3, ip
	mov	r0, #4
	str	r3, [r6]
	ldr	r3, [r6]
	bl	dprint_vfmw
	ldr	r3, [r4, #312]
	add	r2, r7, #4
	ldr	r1, .L268+8
	bic	r3, r3, #15
	mov	r0, #4
	str	r3, [r6, #4]
	ldr	r3, [r6, #4]
	bl	dprint_vfmw
	ldr	r3, [r4, #64]
	add	r2, r7, #8
	ldr	r1, .L268+12
	mov	r0, #4
	str	r3, [r6, #8]
	ldr	r3, [r6, #8]
	bl	dprint_vfmw
	ldr	r3, [r4, #48]
	cmp	r3, #0
	bne	.L265
	ldr	r6, [fp, #-48]
	mov	r0, #4
	ldr	r7, [fp, #-52]
	ldr	r1, .L268+16
	str	r3, [r6, #12]
	add	r2, r7, #12
	str	r3, [r6, #16]
	ldr	r3, [r6, #12]
	bl	dprint_vfmw
	ldr	r3, [r6, #16]
.L262:
	add	r2, r7, #16
	ldr	r1, .L268+20
	mov	r0, #4
	bic	r5, r5, #15
	bl	dprint_vfmw
	ldr	r7, [fp, #-56]
	ldr	r6, [fp, #-48]
	mov	r0, #4
	ldr	r8, [fp, #-52]
	ldr	r3, [r7, #1144]
	add	r2, r8, #20
	ldr	r1, .L268+24
	bic	r3, r3, #15
	str	r3, [r6, #20]
	ldr	r3, [r6, #20]
	bl	dprint_vfmw
	ldr	r3, [r7, #1148]
	add	r2, r8, #24
	ldr	r1, .L268+28
	bic	r3, r3, #15
	mov	r0, #4
	str	r3, [r6, #24]
	ldr	r3, [r6, #24]
	bl	dprint_vfmw
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r6, [fp, #-48]
	mov	r0, #4
	cmp	r3, #2
	ldr	r7, [fp, #-52]
	ldreq	r2, [r4, #316]
	ldrne	r3, [r4, #316]
	ldreq	r1, [r4, #716]
	addne	r3, r3, #146
	ldrne	r3, [r4, r3, asl #2]
	addeq	r2, r2, #146
	ldreq	r3, [r4, r2, asl #2]
	add	r2, r7, #28
	addeq	r3, r3, r1
	ldr	r1, .L268+32
	bic	r3, r3, #15
	str	r3, [r6, #28]
	ldr	r3, [r6, #28]
	bl	dprint_vfmw
	ldr	r3, [fp, #-56]
	add	r2, r7, #32
	ldr	r1, .L268+36
	mov	r0, #4
	ldr	r3, [r3, #1152]
	bic	r3, r3, #15
	str	r3, [r6, #32]
	ldr	r3, [r6, #32]
	bl	dprint_vfmw
	str	r5, [r6, #36]
	add	r2, r7, #36
	ldr	r1, .L268+40
	mov	r0, #4
	ldr	r3, [r6, #36]
	bl	dprint_vfmw
	ldr	r5, [r4, #936]
	cmp	r5, #0
	beq	.L266
	ldr	r3, [fp, #-48]
	add	r8, r4, #740
	ldr	r2, [fp, #-52]
	mov	r6, #0
	add	r7, r3, #40
	rsb	r10, r3, r2
.L242:
	ldr	lr, [r8, #4]!
	mov	r3, r7
	add	r2, r6, #10
	mov	r0, #4
	ldr	r1, .L268+44
	add	r6, r6, #1
	add	lr, r4, lr, lsl #2
	ldr	lr, [lr, #324]
	bic	lr, lr, #15
	str	lr, [r3], r10
	ldr	ip, [r7]
	add	r7, r7, r0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r5, [r4, #936]
	cmp	r5, r6
	bhi	.L242
	cmp	r5, #15
	bhi	.L246
.L241:
	add	r2, r5, #10
	ldr	r3, [fp, #-48]
	add	r6, r3, r2, lsl #2
.L245:
	ldr	lr, [r4, #744]
	mov	r3, r6
	add	r5, r5, #1
	mov	r0, #4
	ldr	r1, .L268+44
	add	lr, r4, lr, lsl #2
	ldr	lr, [lr, #324]
	bic	lr, lr, #15
	str	lr, [r3], r10
	ldr	ip, [r6]
	add	r6, r6, r0
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r5, #15
	add	r2, r5, #10
	bls	.L245
.L246:
	ldr	r3, [fp, #-56]
	mov	r0, #4
	ldr	ip, [fp, #-48]
	ldr	r2, [fp, #-52]
	ldr	r3, [r3, #1088]
	add	r2, r2, #104
	ldr	r1, .L268+48
	bic	r3, r3, #15
	str	r3, [ip, #104]
	ldr	r3, [ip, #104]
	bl	dprint_vfmw
	ldr	r5, [r4, #936]
	cmp	r5, #0
	beq	.L267
	ldr	r3, [fp, #-52]
	add	r9, r4, #804
	mov	r6, #0
	add	r3, r3, #108
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-48]
	add	r8, r3, #108
	add	r7, r3, #112
.L248:
	ldr	r0, [r9, #4]!
	mov	r3, r8
	mov	r5, r6, asl #1
	ldr	r1, .L268+44
	add	r2, r5, #27
	add	r6, r6, #1
	str	r0, [r3], r10
	mov	r0, #4
	ldr	ip, [r7, #-4]
	add	r8, r8, #8
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r9, #64]
	mov	r3, r7
	add	r2, r5, #28
	ldr	r1, .L268+44
	mov	r0, #4
	str	ip, [r3], r10
	add	r7, r7, #8
	ldr	ip, [r8, #-4]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r5, [r4, #936]
	cmp	r5, r6
	bhi	.L248
	cmp	r5, #15
	bhi	.L250
.L247:
	ldr	r2, [fp, #-60]
	mov	r7, r5, asl #1
	ldr	r3, [fp, #-48]
	add	r7, r7, #27
	str	r4, [fp, #-60]
	mov	r8, #0
	rsb	r9, r3, r2
	ldr	r2, [fp, #-52]
	add	r6, r3, r5, lsl #3
	mov	r4, r3
	add	r10, r2, #112
.L249:
	str	r8, [r6, #108]
	add	r3, r9, r6
	ldr	ip, [r6, #108]
	mov	r2, r7
	ldr	r1, .L268+44
	mov	r0, #4
	add	r5, r5, #1
	str	ip, [sp]
	bl	dprint_vfmw
	str	r8, [r6, #112]
	ldr	ip, [r6, #112]
	rsb	r3, r4, r10
	add	r3, r3, r6
	add	r2, r7, #1
	ldr	r1, .L268+44
	mov	r0, #4
	str	ip, [sp]
	add	r6, r6, #8
	bl	dprint_vfmw
	cmp	r5, #15
	add	r7, r7, #2
	bls	.L249
	ldr	r4, [fp, #-60]
.L250:
	ldr	r3, [fp, #-56]
	add	r0, r4, #76
	ldr	lr, [fp, #-48]
	mov	r1, #56
	ldr	r2, [fp, #-52]
	ldr	ip, [r3, #1160]
	add	r3, lr, #256
	add	r2, r2, #256
	bic	ip, ip, #15
	str	ip, [lr, #236]
	bl	Write_V5R2C1_Qmatrix
	mov	r0, #0
.L234:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L265:
	ldr	r6, [fp, #-48]
	mov	r0, #4
	ldr	r3, [r4, #68]
	ldr	r7, [fp, #-52]
	ldr	r1, .L268+16
	str	r3, [r6, #12]
	add	r2, r7, #12
	ldr	ip, [r4, #72]
	ldr	r3, [r6, #12]
	str	ip, [r6, #16]
	bl	dprint_vfmw
	ldr	r3, [r6, #16]
	b	.L262
.L266:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-48]
	rsb	r10, r2, r3
	b	.L241
.L267:
	ldr	r3, [fp, #-52]
	add	r3, r3, #108
	str	r3, [fp, #-60]
	b	.L247
.L264:
	ldr	r3, .L268+52
	ldr	r2, .L268+56
	ldr	r1, .L268+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L234
.L269:
	.align	2
.L268:
	.word	.LANCHOR0
	.word	.LC53
	.word	.LC54
	.word	.LC55
	.word	.LC56
	.word	.LC57
	.word	.LC58
	.word	.LC59
	.word	.LC60
	.word	.LC61
	.word	.LC62
	.word	.LC63
	.word	.LC64
	.word	.LC52
	.word	.LANCHOR0+184
	.word	.LC2
	UNWIND(.fnend)
	.size	H264HAL_V5R2C1_SetPicMsg, .-H264HAL_V5R2C1_SetPicMsg
	.align	2
	.global	H264HAL_V5R2C1_SetSliceMsg
	.type	H264HAL_V5R2C1_SetSliceMsg, %function
H264HAL_V5R2C1_SetSliceMsg:
	UNWIND(.fnstart)
	@ args = 16, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r7, r0
	mov	r0, r3
	mov	r6, r3
	mov	r4, r2
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L283
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	H264HAL_SetSliceMsgStreamAddrInfo
	ldr	r0, [r4, #48]
	ldr	r3, [r4, #32]
	add	r2, r6, #24
	ldr	ip, [r4, #36]
	ubfx	r0, r0, #0, #20
	ldr	r1, .L285
	and	ip, ip, #3
	orr	r3, r0, r3, asl #26
	mov	r0, #4
	orr	r3, r3, ip, asl #24
	str	r3, [r5, #24]
	ldr	r3, [r5, #24]
	bl	dprint_vfmw
	ldr	r3, .L285+4
	ldrb	lr, [r4, #3]	@ zero_extendqisi2
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L274
	cmp	lr, #0
	beq	.L284
.L274:
	ldr	ip, [r4, #56]
	add	r2, r6, #28
	ldrb	r10, [r4]	@ zero_extendqisi2
	mov	r0, #4
	ldr	r1, [r4, #52]
	ldr	r9, [r4, #40]
	mov	ip, ip, asl #8
	ldr	r8, .L285+8
	ldr	r3, [r4, #44]
	and	r9, r9, #31
	orr	r1, ip, r1, asl #2
	add	ip, r8, r10, lsl #2
	and	r3, r3, #31
	orr	r1, r1, r9, asl #21
	ldr	ip, [ip, #56]
	ldrb	r9, [r4, #2]	@ zero_extendqisi2
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip
	ldr	r1, .L285+12
	orr	r3, r3, r9, asl #15
	orr	lr, r3, lr, asl #14
	str	lr, [r5, #28]
	ldr	r3, [r5, #28]
	bl	dprint_vfmw
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	H264HAL_SetSliceMsgMvAddrInfo
	ldr	r0, [r4, #60]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	add	r2, r6, #40
	and	r0, r0, #31
	ldr	ip, [r4, #64]
	ldr	r1, .L285+16
	mov	r0, r0, asl #5
	and	ip, ip, #31
	orr	r3, r0, r3, asl #16
	mov	r0, #4
	orr	r3, r3, ip
	str	r3, [r5, #40]
	ldr	r3, [r5, #40]
	bl	dprint_vfmw
	ldr	r0, [r4, #68]
	ldr	r3, [r4, #72]
	add	r2, r6, #44
	and	r0, r0, #15
	ldr	ip, [r4, #76]
	and	r3, r3, #15
	ldr	r1, .L285+20
	mov	r0, r0, asl #16
	orr	r3, r0, r3, asl #8
	mov	r0, #4
	orr	r3, r3, ip
	str	r3, [r5, #44]
	ldr	r3, [r5, #44]
	bl	dprint_vfmw
	ldr	r3, [r4, #4056]
	cmp	r3, #0
	beq	.L275
	ldr	r0, [fp, #16]
.L276:
	ldr	r3, [fp, #8]
	str	r0, [r5, #176]
	bic	r3, r3, #15
	str	r3, [r5, #252]
	ldrb	r3, [r4]	@ zero_extendqisi2
	add	r8, r8, r3, lsl #2
	ldr	r0, [r8, #56]
	cmp	r0, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	H264HAL_SetSliceMsgRefPicInfo
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	H264HAL_SetSliceMsgAPCInfo
	mov	r0, r7
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	bl	H264HAL_SetSliceMsgWPInfo
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L284:
	ldr	r1, [r7, #40]
	movw	r2, #1620
	ldr	r3, [r7, #44]
	mul	r3, r3, r1
	cmp	r3, r2
	bls	.L274
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L275:
	ldr	r0, [r7, #740]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	cmp	r0, #262144
	addgt	r1, r1, #1
	addle	r1, r1, #1
	movwgt	r0, #65535
	suble	r0, r0, #1
	movtgt	r0, 3
	bl	__aeabi_idiv
	b	.L276
.L283:
	ldr	r3, .L285+24
	ldr	r2, .L285+28
	ldr	r1, .L285+32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L286:
	.align	2
.L285:
	.word	.LC65
	.word	g_not_direct_8x8_inference_flag
	.word	.LANCHOR0
	.word	.LC66
	.word	.LC67
	.word	.LC68
	.word	.LC4
	.word	.LANCHOR0+244
	.word	.LC2
	UNWIND(.fnend)
	.size	H264HAL_V5R2C1_SetSliceMsg, .-H264HAL_V5R2C1_SetSliceMsg
	.align	2
	.global	H264HAL_V5R2C1_StartDec
	.type	H264HAL_V5R2C1_StartDec, %function
H264HAL_V5R2C1_StartDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldr	r10, .L323
	movw	r3, #1228
	str	r1, [fp, #-88]
	mov	r4, r2
	mov	r9, r0
	mla	r3, r3, r1, r10
	str	r3, [fp, #-84]
	bl	H264HAL_CheckParaValid
	cmn	r0, #1
	beq	.L317
	ldr	r6, [fp, #-88]
	ldr	r5, [fp, #-84]
	mov	r1, r6
	mov	r0, r5
	bl	H264HAL_GetVdmRegVirAddr
	cmn	r0, #1
	beq	.L317
	ldr	r3, .L323+4
	mov	r0, #3
	ldr	r1, .L323+8
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
	bl	dprint_vfmw
	mov	r3, r4
	mov	r2, r6
	mov	r1, r5
	mov	r0, r9
	bl	H264HAL_V5R2C1_CfgVdmReg
	cmn	r0, #1
	beq	.L317
	ldr	r3, [r5, #60]
	mov	r1, r5
	ldr	r2, [r5, #56]
	mov	r0, r9
	bl	H264HAL_V5R2C1_SetPicMsg
	ldr	r3, [r9, #1184]
	ldr	r8, [r9, #944]
	cmp	r3, #1
	beq	.L318
	ldr	r5, [r8, #48]
	cmp	r5, #0
	streq	r5, [fp, #-92]
	bne	.L319
.L294:
	ldr	r1, [fp, #-88]
	movw	r3, #307
	mov	r2, #0
	str	r2, [fp, #-64]
	mov	r4, r2
	ldr	r2, [fp, #-92]
	mul	r3, r3, r1
	ldr	r1, [r9, #940]
	add	r0, r2, #5
	str	r0, [fp, #-60]
	str	r3, [fp, #-56]
	add	r3, r3, r2
	str	r3, [fp, #-80]
.L296:
	ldr	r3, [fp, #-60]
	cmp	r4, r1
	ldr	r2, [fp, #-56]
	add	r7, r3, r4
	ldr	r3, [fp, #-80]
	add	r2, r2, r7
	add	r3, r3, r4
	add	r2, r2, #10
	add	r3, r3, #14
	bge	.L320
	ldr	r3, [r10, r3, asl #2]
	cmp	r4, #0
	ldr	r6, [r8, #48]
	movgt	r5, #1
	movle	r5, #0
	str	r3, [fp, #-68]
	ldr	r3, [fp, #-64]
	cmp	r6, r3
	movhi	r5, #0
	andls	r5, r5, #1
	ldr	r3, [r10, r2, asl #2]
	cmp	r5, #0
	str	r3, [fp, #-72]
	bne	.L296
	sub	r3, fp, #48
	add	r2, r4, #1
	mov	r0, r8
	bl	H264HAL_FindNextSlicePara
	str	r6, [fp, #-64]
	subs	r3, r0, #0
	str	r3, [fp, #-76]
	beq	.L317
	ldr	r4, [fp, #-48]
	ldr	r2, [r9, #940]
	ldr	r3, [fp, #-56]
	ldr	r1, [fp, #-60]
	cmp	r2, r4
	cmpne	r7, #140
	add	r3, r3, r4
	add	r3, r3, r1
	add	r3, r3, #10
	beq	.L321
	ldr	r2, [fp, #-76]
	ldr	r1, .L323
	ldr	r2, [r2, #48]
	ldr	r1, [r1, r3, asl #2]
	sub	r3, r2, #1
.L299:
	ldr	r0, [fp, #-68]
	mov	r2, r8
	str	r3, [sp, #12]
	str	r1, [sp, #4]
	str	r0, [sp]
	mov	r0, r9
	ldr	r3, [fp, #-72]
	str	r6, [sp, #8]
	ldr	r1, [fp, #-84]
	bl	H264HAL_V5R2C1_SetSliceMsg
	ldr	r8, [fp, #-76]
	cmp	r0, #0
	bne	.L300
	ldr	r1, [r9, #940]
	b	.L296
.L321:
	ldr	r2, [r9, #36]
	mov	r1, r5
	ldr	r3, [r9, #44]
	str	r5, [r8, #4056]
	ldr	r4, [r9, #940]
	mul	r3, r3, r2
	sub	r3, r3, #1
	b	.L299
.L320:
	cmp	r1, #0
	ble	.L302
	ldr	r0, [fp, #-92]
	movw	r3, #307
	ldr	r2, [fp, #-88]
	mla	r3, r3, r2, r0
	add	r1, r3, r1
	add	r1, r1, #14
	ldr	r0, [r10, r1, asl #2]
	bl	H264HAL_V5R2C1_CutSliceChain
	mov	r0, #0
.L289:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L302:
	ldr	r1, .L323+12
	mov	r0, #1
	bl	dprint_vfmw
.L317:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L318:
	ldr	r2, [r9, #940]
	cmp	r2, #1
	ble	.L292
.L293:
	add	r3, r3, #1
	ldr	r8, [r8, #4056]
	cmp	r3, r2
	bne	.L293
.L292:
	ldr	r2, [fp, #-88]
	movw	lr, #1228
	ldr	r3, [r9, #44]
	mov	r4, #0
	ldr	ip, [r9, #36]
	mov	r0, r9
	mla	lr, lr, r2, r10
	ldr	r1, [fp, #-84]
	mul	ip, r3, ip
	mov	r2, r8
	ldr	r3, [lr, #60]
	sub	ip, ip, #1
	str	ip, [sp, #12]
	ldr	ip, [r8, #48]
	str	r4, [sp, #4]
	str	r4, [sp]
	str	ip, [sp, #8]
	bl	H264HAL_V5R2C1_SetSliceMsg
	cmp	r0, #0
	beq	.L289
	movw	r2, #1116
	ldr	r1, .L323+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L289
.L319:
	ldr	r3, [r8, #8]
	mov	ip, #0
	ldr	lr, [fp, #-84]
	mov	r6, #1
	str	ip, [r8, #48]
	sub	r0, r5, #1
	str	r3, [fp, #-56]
	mov	r2, r8
	ldr	r3, [r8, #12]
	mov	r1, lr
	str	ip, [r8, #12]
	str	r6, [r8, #8]
	str	r3, [fp, #-60]
	ldr	r3, [r8, #16]
	str	ip, [r8, #16]
	ldr	r7, [r8, #24]
	str	r3, [fp, #-64]
	ldr	r3, [r8, #20]
	str	ip, [r8, #20]
	ldr	r4, [r8, #28]
	str	r3, [fp, #-68]
	ldr	r3, [r9, #736]
	str	ip, [r8, #28]
	str	r3, [r8, #24]
	ldr	r3, [lr, #60]
	ldr	lr, [lr, #64]
	str	ip, [sp, #8]
	ldr	ip, [r1, #56]
	str	r0, [sp, #12]
	mov	r0, r9
	str	lr, [sp, #4]
	str	ip, [sp]
	bl	H264HAL_V5R2C1_SetSliceMsg
	cmp	r0, #0
	bne	.L322
	ldr	r3, [fp, #-56]
	str	r5, [r8, #48]
	str	r7, [r8, #24]
	str	r3, [r8, #8]
	ldr	r3, [fp, #-60]
	str	r4, [r8, #28]
	str	r6, [fp, #-92]
	str	r3, [r8, #12]
	ldr	r3, [fp, #-64]
	str	r3, [r8, #16]
	ldr	r3, [fp, #-68]
	str	r3, [r8, #20]
	ldr	r8, [r9, #944]
	b	.L294
.L300:
	movw	r2, #1203
	ldr	r1, .L323+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L322:
	mov	r0, r6
	movw	r2, #1150
	ldr	r1, .L323+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L289
.L324:
	.align	2
.L323:
	.word	g_HwMem
	.word	.LANCHOR1
	.word	.LC69
	.word	.LC71
	.word	.LC70
	UNWIND(.fnend)
	.size	H264HAL_V5R2C1_StartDec, .-H264HAL_V5R2C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13992, %object
	.size	__func__.13992, 23
__func__.13992:
	.ascii	"H264HAL_V5R2C1_InitHal\000"
	.space	1
	.type	__func__.14007, %object
	.size	__func__.14007, 29
__func__.14007:
	.ascii	"H264HAL_V5R2C1_CutSliceChain\000"
	.space	3
	.type	g_SliceTypeForPMV, %object
	.size	g_SliceTypeForPMV, 12
g_SliceTypeForPMV:
	.word	1
	.word	2
	.word	0
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
	.type	__func__.14141, %object
	.size	__func__.14141, 23
__func__.14141:
	.ascii	"H264HAL_CheckParaValid\000"
	.space	1
	.type	__func__.14159, %object
	.size	__func__.14159, 25
__func__.14159:
	.ascii	"H264HAL_V5R2C1_CfgVdmReg\000"
	.space	3
	.type	__func__.14185, %object
	.size	__func__.14185, 25
__func__.14185:
	.ascii	"H264HAL_V5R2C1_SetPicMsg\000"
	.space	3
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
	.type	__func__.14215, %object
	.size	__func__.14215, 27
__func__.14215:
	.ascii	"H264HAL_V5R2C1_SetSliceMsg\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"line: %d, p = NULL is not expected value!\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"pHwMem is NULL!\012\000" )
	.space	3
.LC2:
	ASCII(.ascii	"%s: %s\012\000" )
.LC3:
	ASCII(.ascii	"H264HAL_V5R2C1_InitHal return error.\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"can not map slice msg virtual address!\012\000" )
.LC5:
	ASCII(.ascii	"qmatrix[%d] = 0x%x\012\000" )
.LC6:
	ASCII(.ascii	"picmsg Dxx addr 0x%x = 0x%x\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"Before slicemsg D[%d] tmp =0x%x,bitsoffset =0x%x,by" )
	ASCII(.ascii	"tespos = 0x%x\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"slicemsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"slicemsg g_pListX[1][0]->frame_store->pmv_address_i" )
	ASCII(.ascii	"dc = %d\012\000" )
.LC10:
	ASCII(.ascii	"slicemsg D[6] addr 0x%x = 0x%x\012\000" )
.LC11:
	ASCII(.ascii	"slicemsg D[7] addr 0x%x = 0x%x\012\000" )
.LC12:
	ASCII(.ascii	"slicemsg D[%d] address 0x%x = 0x%x\012\000" )
.LC13:
	ASCII(.ascii	"slicemsg burst1 D0~D31, burst2 D0~31, burst3 D0~D31" )
	ASCII(.ascii	" list0size = %d\012\000" )
.LC14:
	ASCII(.ascii	"luma_lg = %d\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"wp_weight_l0_y = %d\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"wp_offset_l0_y = %d\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"chroma_lg = %d\012\000" )
.LC18:
	ASCII(.ascii	"wp_weight_l1_y = %d\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"wp_offset_l1_y = %d\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"wp_weight_l0_u = %d\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"wp_offset_l0_u = %d\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"wp_weight_l1_u = %d\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"wp_offset_l1_u = %d\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"wp_weight_l0_v = %d\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"wp_offset_l0_v = %d\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"wp_weight_l1_v = %d\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"wp_offset_l1_v = %d\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"slicemsg burst1 D32~D63, burst2 D32~63, burst3 D32~" )
	ASCII(.ascii	"D63 list1size = %d\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC30:
	ASCII(.ascii	"point of picture para null\012\000" )
.LC31:
	ASCII(.ascii	"picture width out of range\012\000" )
.LC32:
	ASCII(.ascii	"point of fst slice para null\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"VdhId is wrong! H264HAL_V200R003_StartDec\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC35:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC36:
	ASCII(.ascii	"BASIC_V5R2C1_CFG0 = 0x%x\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"BASIC_V5R2C1_CFG1 = 0x%x\012\000" )
	.space	2
.LC38:
	ASCII(.ascii	"AVM_V5R2C1_ADDR = 0x%x\012\000" )
.LC39:
	ASCII(.ascii	"VAM_V5R2C1_ADDR = 0x%x\012\000" )
.LC40:
	ASCII(.ascii	"STREAM_V5R2C1_BASE_ADDR = 0x%x\012\000" )
.LC41:
	ASCII(.ascii	"VREG_PART_DEC_OVER_INT_LEVEL=0x%x\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"YSTADDR_V5R2C1_1D = 0x%x\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"YSTRIDE_V5R2C1_1D = 0x%x\012\000" )
	.space	2
.LC45:
	ASCII(.ascii	"UVOFFSET_V5R2C1_1D = 0x%x\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"HEAD_INF_OFFSET_V5R2C1_1D = 0x%x\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"PPFD_V5R2C1_BUF_ADDR = 0x%x\012\000" )
	.space	3
.LC48:
	ASCII(.ascii	"PPFD_V5R2C1_BUF_LEN = 0x%x\012\000" )
.LC49:
	ASCII(.ascii	"REF_V5R2C1_PIC_TYPE = 0x%x\012\000" )
.LC50:
	ASCII(.ascii	"FF_V5R2C1_APT_EN = 0x%x\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"line %d pSlicePara is NULL!\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"can not map down msg virtual address!\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"picmsg D[0] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC54:
	ASCII(.ascii	"picmsg D[1] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"picmsg D[2] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"picmsg D[3] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	"picmsg D[4] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC58:
	ASCII(.ascii	"picmsg D[5] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"picmsg D[6] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"picmsg D[7] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"picmsg D[8] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC62:
	ASCII(.ascii	"picmsg D[9] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"picmsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	1
.LC64:
	ASCII(.ascii	"picmsg D[26] addr 0x%x = 0x%x\012\000" )
	.space	1
.LC65:
	ASCII(.ascii	"slicemsg D[4] addr 0x%x = 0x%x\012\000" )
.LC66:
	ASCII(.ascii	"slicemsg D[5] addr 0x%x = 0x%x\012\000" )
.LC67:
	ASCII(.ascii	"slicemsg D[8] addr 0x%x = 0x%x\012\000" )
.LC68:
	ASCII(.ascii	"slicemsg D[9] addr 0x%x = 0x%x\012\000" )
.LC69:
	ASCII(.ascii	"\012\012***********************H264HAL_V200R003_Sta" )
	ASCII(.ascii	"rtDec is Now %d***********************\012\000" )
	.space	3
.LC70:
	ASCII(.ascii	"line %d Set slice msg not wrong!\012\000" )
	.space	2
.LC71:
	ASCII(.ascii	"!!! no slice to dec, add up msg report.\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	StartCnt.14237, %object
	.size	StartCnt.14237, 4
StartCnt.14237:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
