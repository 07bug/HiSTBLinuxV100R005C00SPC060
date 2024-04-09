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
	.type	H264HAL_SetSliceMsgRefPicFrame.isra.2, %function
H264HAL_SetSliceMsgRefPicFrame.isra.2:
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
	beq	.L1
	mov	r4, ip, asl #10
	mov	r7, #0
	add	ip, r4, ip, lsl #7
	mov	r8, r7
	add	r4, r1, ip
	mov	r5, r7
	b	.L7
.L5:
	cmp	r6, #3
	beq	.L15
.L6:
	ldr	r3, [r9, #52]
	cmp	r5, r3
	bcs	.L16
.L7:
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	and	r3, r5, #7
	ldr	r2, [r10]
	and	r6, r5, #3
	ldr	ip, .L18
	add	r4, r4, #36
	add	r1, r2, r1, lsl #1
	ldrb	r0, [r4, #1591]	@ zero_extendqisi2
	ldr	r2, [r4, #1608]
	add	r5, r5, #1
	ldr	r1, [ip, r1, asl #2]
	cmp	r0, #1
	and	r1, r1, #3
	mov	r2, r2, asl #1
	moveq	r0, #8
	movne	r0, #0
	and	r2, r2, #31
	orr	r1, r0, r1
	cmp	r3, #7
	add	r0, r6, r6, lsl #2
	mov	r3, r3, asl #2
	orr	r7, r7, r2, asl r0
	orr	r8, r8, r1, asl r3
	bne	.L5
	ldr	lr, [fp, #-48]
	ldr	r1, [fp, #-56]
	ldr	r0, [fp, #-60]
	mov	r2, lr
	str	r8, [r1, lr, asl #2]
	add	r3, r0, lr, lsl #2
	ldr	ip, [r1, lr, asl #2]
	mov	r0, #4
	ldr	r1, .L18+4
	add	lr, lr, #1
	str	lr, [fp, #-48]
	mov	r8, #0
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r6, #3
	bne	.L6
.L15:
	ldr	lr, [fp, #-52]
	ldr	r1, [fp, #-56]
	ldr	r0, [fp, #-60]
	mov	r2, lr
	str	r7, [r1, lr, asl #2]
	add	r3, r0, lr, lsl #2
	ldr	ip, [r1, lr, asl #2]
	mov	r0, #4
	ldr	r1, .L18+4
	add	lr, lr, #1
	str	lr, [fp, #-52]
	mov	r7, #0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r9, #52]
	cmp	r5, r3
	bcc	.L7
.L16:
	tst	r3, #7
	bne	.L17
.L1:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L17:
	ldr	r4, [fp, #-56]
	mov	r0, #4
	ldr	r2, [fp, #-48]
	ldr	r5, [fp, #-60]
	ldr	r1, .L18+4
	str	r8, [r4, r2, asl #2]
	add	r3, r5, r2, lsl #2
	ldr	ip, [r4, r2, asl #2]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [fp, #-52]
	ldr	r1, .L18+4
	mov	r0, #4
	str	r7, [r4, r2, asl #2]
	add	r3, r5, r2, lsl #2
	ldr	ip, [r4, r2, asl #2]
	str	ip, [fp, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L19:
	.align	2
.L18:
	.word	.LANCHOR0
	.word	.LC0
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgRefPicFrame.isra.2, .-H264HAL_SetSliceMsgRefPicFrame.isra.2
	.align	2
	.type	H264HAL_SetSliceMsgRefPicField.isra.3, %function
H264HAL_SetSliceMsgRefPicField.isra.3:
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
	beq	.L20
	mov	r4, ip, asl #10
	mov	r7, #0
	add	ip, r4, ip, lsl #7
	mov	r8, r7
	add	r4, r1, ip
	mov	r5, r7
	b	.L40
.L23:
	cmp	r3, #2
	beq	.L31
	and	r6, r5, #3
	and	r3, r5, #7
.L30:
	cmp	r3, #7
	beq	.L56
.L38:
	cmp	r6, #3
	beq	.L57
.L39:
	ldr	r3, [r10, #52]
	add	r5, r5, #1
	add	r4, r4, #36
	cmp	r5, r3
	bcs	.L58
.L40:
	ldrb	r3, [r4, #1624]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L23
	ldrb	r3, [r4, #1625]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L24
	ldr	r1, [fp, #-48]
	and	r3, r5, #7
	ldrb	r2, [r4, #1628]	@ zero_extendqisi2
	ldrb	r0, [r4, #1629]	@ zero_extendqisi2
	ldr	r1, [r1]
	add	r1, r1, r2, lsl #1
.L54:
	cmp	r0, #1
	ldr	r0, .L60
	and	r6, r5, #3
	add	r1, r0, r1, lsl #2
	moveq	r0, #8
	movne	r0, #0
	cmp	r2, #1
	ldr	r2, [r1, #32]
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
	bne	.L38
.L56:
	ldr	lr, [fp, #-52]
	ldr	r1, [fp, #-56]
	ldr	r0, [fp, #-60]
	mov	r2, lr
	str	r8, [r1, lr, asl #2]
	add	r3, r0, lr, lsl #2
	ldr	ip, [r1, lr, asl #2]
	mov	r0, #4
	ldr	r1, .L60+4
	add	lr, lr, #1
	str	lr, [fp, #-52]
	mov	r8, #0
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r6, #3
	bne	.L39
.L57:
	ldr	r2, [fp, #-56]
	mov	r0, #4
	ldr	r3, [fp, #-60]
	ldr	r1, .L60+4
	str	r7, [r2, r9, asl #2]
	add	r3, r3, r9, lsl #2
	ldr	ip, [r2, r9, asl #2]
	mov	r2, r9
	mov	r7, #0
	add	r9, r9, #1
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L39
.L31:
	ldrb	r3, [r4, #1625]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L32
	ldr	r1, [fp, #-48]
	and	r3, r5, #7
	ldrb	r2, [r4, #1630]	@ zero_extendqisi2
	ldrb	r0, [r4, #1631]	@ zero_extendqisi2
	ldr	r1, [r1]
	add	r1, r1, r2, lsl #1
.L55:
	cmp	r0, #1
	ldr	r0, .L60
	and	r6, r5, #3
	add	r1, r0, r1, lsl #2
	moveq	r0, #8
	movne	r0, #0
	cmp	r2, #1
	ldr	r2, [r1, #32]
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
	b	.L30
.L58:
	tst	r3, #7
	bne	.L59
.L20:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L24:
	ldr	r2, [fp, #-48]
	and	r3, r5, #7
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	ldrb	r0, [r4, #1629]	@ zero_extendqisi2
	ldr	r2, [r2]
	add	r1, r2, r1, lsl #1
	ldrb	r2, [r4, #1628]	@ zero_extendqisi2
	b	.L54
.L32:
	ldr	r2, [fp, #-48]
	and	r3, r5, #7
	ldrb	r1, [r4, #1626]	@ zero_extendqisi2
	ldrb	r0, [r4, #1631]	@ zero_extendqisi2
	ldr	r2, [r2]
	add	r1, r2, r1, lsl #1
	ldrb	r2, [r4, #1630]	@ zero_extendqisi2
	b	.L55
.L59:
	ldr	r4, [fp, #-56]
	mov	r0, #4
	ldr	r2, [fp, #-52]
	ldr	r5, [fp, #-60]
	ldr	r1, .L60+4
	str	r8, [r4, r2, asl #2]
	add	r3, r5, r2, lsl #2
	ldr	ip, [r4, r2, asl #2]
	str	ip, [sp]
	bl	dprint_vfmw
	str	r7, [r4, r9, asl #2]
	ldr	ip, [r4, r9, asl #2]
	add	r3, r5, r9, lsl #2
	mov	r2, r9
	ldr	r1, .L60+4
	mov	r0, #4
	str	ip, [fp, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L61:
	.align	2
.L60:
	.word	.LANCHOR0
	.word	.LC0
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgRefPicField.isra.3, .-H264HAL_SetSliceMsgRefPicField.isra.3
	.align	2
	.global	Write_V5R6C1_CabacTab
	.type	Write_V5R6C1_CabacTab, %function
Write_V5R6C1_CabacTab:
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
	beq	.L65
	ldr	r3, .L66
	mov	r2, #5120
	ldr	r1, .L66+4
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L65:
	mov	r2, #59
	ldr	r1, .L66+8
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L67:
	.align	2
.L66:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_CabacMN
	.word	.LC1
	UNWIND(.fnend)
	.size	Write_V5R6C1_CabacTab, .-Write_V5R6C1_CabacTab
	.align	2
	.global	H264HAL_V5R6C1_InitHal
	.type	H264HAL_V5R6C1_InitHal, %function
H264HAL_V5R6C1_InitHal:
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
	ldr	r0, [r0, #1088]
	bl	Write_V5R6C1_CabacTab
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r1, .L73
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L74:
	.align	2
.L73:
	.word	.LC2
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_InitHal, .-H264HAL_V5R6C1_InitHal
	.align	2
	.global	Get_V5R6C1_VirAddr
	.type	Get_V5R6C1_VirAddr, %function
Get_V5R6C1_VirAddr:
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
	.size	Get_V5R6C1_VirAddr, .-Get_V5R6C1_VirAddr
	.align	2
	.global	Get_V5R6C1_PhyAddr
	.type	Get_V5R6C1_PhyAddr, %function
Get_V5R6C1_PhyAddr:
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
	.size	Get_V5R6C1_PhyAddr, .-Get_V5R6C1_PhyAddr
	.align	2
	.global	H264HAL_V5R6C1_CutSliceChain
	.type	H264HAL_V5R6C1_CutSliceChain, %function
H264HAL_V5R6C1_CutSliceChain:
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
	beq	.L80
	mov	r0, #0
	str	r0, [r3, #252]
	ldmfd	sp, {fp, sp, pc}
.L80:
	ldr	r3, .L81
	ldr	r2, .L81+4
	ldr	r1, .L81+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L82:
	.align	2
.L81:
	.word	.LC3
	.word	.LANCHOR0+64
	.word	.LC4
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_CutSliceChain, .-H264HAL_V5R6C1_CutSliceChain
	.align	2
	.global	Write_V5R6C1_Qmatrix
	.type	Write_V5R6C1_Qmatrix, %function
Write_V5R6C1_Qmatrix:
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
.L85:
	ldr	r3, [r7, #4]!
	mov	r2, r4
	ldr	r1, .L88
	mov	r0, #4
	add	r4, r4, #1
	mov	r5, r7
	str	r3, [r6, #4]!
	ldr	r3, [r5], r10
	bl	dprint_vfmw
	ldr	r3, [r6]
	rsb	r2, r8, r5
	ldr	r1, .L88+4
	mov	r0, #4
	bl	dprint_vfmw
	cmp	r4, r9
	bne	.L85
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L89:
	.align	2
.L88:
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	Write_V5R6C1_Qmatrix, .-Write_V5R6C1_Qmatrix
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
.L93:
	ldr	r8, [r10, #4]!
	sub	r3, r7, #4
	mov	r2, r4
	ldr	r1, .L95
	cmp	r8, #0
	mov	r0, #4
	add	r9, r4, #1
	beq	.L91
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
	ldr	r1, .L95+4
	mov	r3, r8
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	str	r8, [r5]
	mov	r2, r9
	ldr	ip, [r6, #4]
	mov	r3, r7
	ldr	r1, .L95
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r10]
	add	r3, r7, #4
	add	r2, r4, #2
	ldr	r1, .L95
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
	ldr	r1, .L95
	str	ip, [sp]
	bl	dprint_vfmw
.L92:
	add	r4, r4, #3
	add	r5, r5, #12
	cmp	r4, #6
	add	r6, r6, #12
	add	r7, r7, #12
	bne	.L93
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L91:
	str	r8, [r6]
	ldr	ip, [r5, #-4]
	str	ip, [sp]
	bl	dprint_vfmw
	str	r8, [r5]
	ldr	ip, [r6, #4]
	mov	r3, r7
	add	r2, r4, #1
	ldr	r1, .L95
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	str	r8, [r5, #4]
	ldr	ip, [r5, #4]
	add	r3, r7, #4
	add	r2, r4, #2
	ldr	r1, .L95
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L92
.L96:
	.align	2
.L95:
	.word	.LC8
	.word	.LC7
	UNWIND(.fnend)
	.size	H264HAL_SetSliceMsgStreamAddrInfo, .-H264HAL_SetSliceMsgStreamAddrInfo
	.global	__aeabi_idiv
	.align	2
	.type	H264HAL_V5R6C1_SetSliceMsg.isra.7, %function
H264HAL_V5R6C1_SetSliceMsg.isra.7:
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
	mov	r10, r0
	mov	r0, r2
	mov	r8, r2
	mov	r5, r1
	mov	r4, r3
	bl	MEM_Phy2Vir
	subs	r7, r0, #0
	beq	.L158
	mov	r3, r8
	mov	r2, r7
	mov	r1, r5
	mov	r0, r10
	bl	H264HAL_SetSliceMsgStreamAddrInfo
	ldr	r0, [r5, #48]
	ldr	r3, [r5, #32]
	add	r2, r8, #24
	ldr	ip, [r5, #36]
	ubfx	r0, r0, #0, #20
	ldr	r1, .L166
	and	ip, ip, #3
	orr	r3, r0, r3, asl #26
	mov	r0, #4
	orr	r3, r3, ip, asl #24
	str	r3, [r7, #24]
	ldr	r3, [r7, #24]
	bl	dprint_vfmw
	ldr	r3, .L166+4
	ldrb	lr, [r5, #3]	@ zero_extendqisi2
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L101
	cmp	lr, #0
	beq	.L159
.L101:
	ldr	r1, [r5, #56]
	add	r2, r8, #28
	ldr	ip, [r5, #52]
	mov	r0, #4
	ldrb	r6, [r5]	@ zero_extendqisi2
	mov	r9, r1, asl #8
	ldr	r3, [r5, #40]
	orr	r1, r9, ip, asl #2
	ldr	ip, .L166+8
	and	r3, r3, #31
	add	r6, ip, r6, lsl #2
	ldr	ip, [r5, #44]
	orr	r1, r1, r3, asl #21
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	and	ip, ip, #31
	ldr	r6, [r6, #124]
	orr	r1, r1, ip, asl #16
	orr	ip, r1, r6
	ldr	r1, .L166+12
	orr	r3, ip, r3, asl #15
	orr	r3, r3, lr, asl #14
	str	r3, [r7, #28]
	ldr	r3, [r7, #28]
	bl	dprint_vfmw
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r2, .L166+8
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #124]
	cmp	r3, #2
	movne	r3, #0
	movne	r2, r3
	beq	.L160
.L102:
	str	r2, [r7, #32]
	mov	r0, #4
	add	r2, r8, #32
	str	r3, [r7, #36]
	ldr	r1, .L166+16
	ldr	r3, [r7, #32]
	bl	dprint_vfmw
	ldr	r3, [r7, #36]
	add	r2, r8, #36
	ldr	r1, .L166+20
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r0, [r5, #60]
	ldrb	lr, [r5, #4]	@ zero_extendqisi2
	add	r2, r8, #40
	and	r0, r0, #31
	ldr	r3, [r5, #64]
	ldr	r1, .L166+24
	mov	r0, r0, asl #5
	and	ip, r3, #31
	orr	r3, r0, lr, asl #16
	mov	r0, #4
	orr	r3, r3, ip
	str	r3, [r7, #40]
	ldr	r3, [r7, #40]
	bl	dprint_vfmw
	ldr	r0, [r5, #68]
	ldr	r3, [r5, #72]
	add	r2, r8, #44
	and	r0, r0, #15
	ldr	ip, [r5, #76]
	and	r3, r3, #15
	ldr	r1, .L166+28
	mov	r0, r0, asl #16
	orr	r3, r0, r3, asl #8
	mov	r0, #4
	orr	r3, r3, ip
	str	r3, [r7, #44]
	ldr	r3, [r7, #44]
	bl	dprint_vfmw
	ldr	r3, [r5, #4056]
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L152
	ldr	r0, [fp, #4]
.L108:
	str	r0, [r7, #176]
	bic	r4, r4, #15
	str	r4, [r7, #252]
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r4, .L166+8
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #124]
	cmp	r3, #0
	bne	.L111
.L121:
	mov	r0, #0
.L153:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L159:
	ldr	r1, [r10, #40]
	movw	r2, #1620
	ldr	r3, [r10, #44]
	mul	r3, r3, r1
	cmp	r3, r2
	mvnhi	r0, #0
	bls	.L101
	b	.L153
.L111:
	ldrb	r3, [r10]	@ zero_extendqisi2
	add	r6, r10, #48
	cmp	r3, #0
	beq	.L161
	mov	r2, #0
	mov	r3, r8
	str	r2, [sp]
	mov	r0, r6
	mov	r2, r7
	mov	r1, r5
	bl	H264HAL_SetSliceMsgRefPicField.isra.3
	ldrb	r3, [r5]	@ zero_extendqisi2
	add	r4, r4, r3, lsl #2
	ldr	r3, [r4, #124]
	cmp	r3, #2
	beq	.L162
.L114:
	mov	r6, r5
	mov	r4, #0
	ldr	r1, [r6, #3928]!
	mov	r9, #36
	and	r1, r1, #31
.L116:
	add	r4, r4, #1
	and	r3, r4, #3
	cmp	r4, #32
	add	r0, r3, r3, lsl #2
	beq	.L163
	ldr	r2, [r6, #4]!
	cmp	r3, #3
	and	r3, r2, #31
	orr	r1, r1, r3, asl r0
	bne	.L116
	str	r1, [r7, r9, asl #2]
	add	r3, r8, r9, lsl #2
	ldr	ip, [r7, r9, asl #2]
	mov	r2, r9
	ldr	r1, .L166+32
	mov	r0, #4
	add	r9, r9, #1
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r1, #0
	b	.L116
.L161:
	str	r3, [sp]
	mov	r2, r7
	mov	r3, r8
	mov	r0, r6
	mov	r1, r5
	bl	H264HAL_SetSliceMsgRefPicFrame.isra.2
	ldrb	r3, [r5]	@ zero_extendqisi2
	add	r4, r4, r3, lsl #2
	ldr	r3, [r4, #124]
	cmp	r3, #2
	bne	.L114
	mov	r2, #1
	mov	r0, r6
	str	r2, [sp]
	mov	r3, r8
	mov	r2, r7
	mov	r1, r5
	bl	H264HAL_SetSliceMsgRefPicFrame.isra.2
	b	.L114
.L163:
	ldr	r3, [r10, #300]
	cmp	r3, #0
	beq	.L119
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r2, .L166+8
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #124]
	cmp	r3, #1
	beq	.L120
.L119:
	ldr	r3, [r10, #304]
	cmp	r3, #1
	bne	.L121
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r2, .L166+8
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #124]
	cmp	r3, #2
	bne	.L121
.L120:
	ldr	r2, [r5, #44]
	mov	r0, #4
	ldr	r1, .L166+36
	add	r10, r7, #256
	bl	dprint_vfmw
	add	r2, r7, #768
	add	r3, r7, #512
	mov	r9, r8
	str	r7, [fp, #-48]
	mov	r4, r5
	str	r8, [fp, #-52]
	mov	r6, #0
	mov	r7, r3
	mov	r8, r2
	str	r5, [fp, #-56]
.L122:
	ldr	r0, [r4, #88]
	add	r3, r9, #256
	ldrb	r1, [r4, #856]	@ zero_extendqisi2
	add	r2, r6, #64
	ubfx	lr, r0, #0, #9
	ldr	r0, [r5, #80]
	add	r4, r4, #4
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L166+32
	orr	r0, r0, ip
	str	r0, [r10]
	ldr	ip, [r10], #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r0, [r4, #212]
	ldrb	r1, [r4, #980]	@ zero_extendqisi2
	add	r3, r9, #512
	ubfx	lr, r0, #0, #9
	ldr	r0, [r5, #84]
	add	r2, r6, #128
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L166+32
	orr	r0, r0, ip
	str	r0, [r7]
	ldr	ip, [r7], #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldrb	r0, [r4, #1108]	@ zero_extendqisi2
	ldr	r1, [r4, #340]
	add	r3, r9, #768
	add	r2, r6, #192
	add	r6, r6, #1
	ubfx	r1, r1, #0, #9
	orr	r1, r1, r0, asl #9
	str	r1, [r8]
	ldr	ip, [r8], #4
	mov	r0, #4
	ldr	r1, .L166+32
	add	r9, r9, r0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #44]
	cmp	r6, r3
	bls	.L122
	ldr	r2, [r5, #80]
	mov	r0, #4
	ldr	r1, .L166+40
	add	r6, r5, #84
	ldr	r7, [fp, #-48]
	add	r4, r5, #852
	ldr	r8, [fp, #-52]
	bl	dprint_vfmw
	mov	r9, #0
.L123:
	ldr	r2, [r6, #4]!
	mov	r0, #4
	ldr	r1, .L166+44
	add	r9, r9, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #4]!
	ldr	r1, .L166+48
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r5, #44]
	cmp	r9, r3
	bls	.L123
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r2, .L166+8
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #124]
	cmp	r3, #2
	beq	.L124
.L127:
	ldr	r2, [r5, #84]
	mov	r0, #4
	ldr	r1, .L166+52
	add	r6, r5, #212
	bl	dprint_vfmw
	add	r4, r5, #980
	mov	r9, #0
.L125:
	ldr	r2, [r6, #4]!
	mov	r0, #4
	ldr	r1, .L166+56
	add	r9, r9, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #4]!
	ldr	r1, .L166+60
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r5, #44]
	cmp	r9, r3
	bls	.L125
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r2, .L166+8
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #124]
	cmp	r3, #2
	beq	.L164
.L128:
	add	r6, r5, #1104
	add	r9, r5, #340
	add	r6, r6, #4
	mov	r4, #0
.L130:
	ldr	r2, [r9, #4]!
	mov	r0, #4
	ldr	r1, .L166+64
	add	r4, r4, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L166+68
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r5, #44]
	cmp	r4, r3
	bls	.L130
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r2, .L166+8
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #124]
	cmp	r3, #2
	bne	.L121
	add	r6, r5, #1488
	add	r9, r5, #724
	add	r6, r6, #4
	mov	r4, #0
.L132:
	ldr	r2, [r9, #4]!
	mov	r0, #4
	ldr	r1, .L166+72
	add	r4, r4, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L166+76
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r2, [r5, #40]
	cmp	r4, r2
	bls	.L132
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r1, .L166+8
	add	r3, r1, r3, lsl #2
	ldr	r3, [r3, #124]
	cmp	r3, #2
	bne	.L121
	ldr	r1, .L166+80
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r10, [fp, #-56]
	add	r9, r7, #384
	add	r6, r7, #640
	add	r7, r7, #896
	mov	r4, #0
.L133:
	ldr	r0, [r10, #472]
	add	r3, r8, #384
	ldrb	r1, [r10, #1240]	@ zero_extendqisi2
	add	r2, r4, #96
	ubfx	lr, r0, #0, #9
	ldr	r0, [r5, #80]
	add	r10, r10, #4
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L166+32
	orr	r0, r0, ip
	str	r0, [r9]
	ldr	ip, [r9], #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r0, [r10, #596]
	ldrb	r1, [r10, #1364]	@ zero_extendqisi2
	add	r3, r8, #640
	ubfx	lr, r0, #0, #9
	ldr	r0, [r5, #84]
	add	r2, r4, #160
	mov	r1, r1, asl #12
	and	ip, r0, #7
	orr	r0, r1, lr, asl #3
	ldr	r1, .L166+32
	orr	r0, r0, ip
	str	r0, [r6]
	ldr	ip, [r6], #4
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	ldrb	r0, [r10, #1492]	@ zero_extendqisi2
	ldr	r1, [r10, #724]
	add	r3, r8, #896
	add	r2, r4, #224
	add	r4, r4, #1
	ubfx	r1, r1, #0, #9
	orr	r1, r1, r0, asl #9
	str	r1, [r7]
	ldr	ip, [r7], #4
	mov	r0, #4
	ldr	r1, .L166+32
	add	r8, r8, r0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #40]
	cmp	r4, r3
	bls	.L133
	b	.L121
.L160:
	ldr	r2, [r5, #2788]
	mov	r0, #4
	ldr	r1, .L166+84
	bl	dprint_vfmw
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L103
	ldrb	r2, [r5, #2778]	@ zero_extendqisi2
	cmp	r2, #3
	ldr	r2, [r5, #2788]
	beq	.L165
.L155:
	add	r2, r2, #146
	ldr	r2, [r10, r2, asl #2]
	bic	r2, r2, #15
	b	.L102
.L152:
	ldr	r0, [r10, #740]
	cmp	r0, #262144
	addgt	r1, r1, #1
	addle	r1, r1, #1
	movwgt	r0, #65535
	suble	r0, r0, #1
	movtgt	r0, 3
	bl	__aeabi_idiv
	b	.L108
.L103:
	ldr	r3, [r5, #2776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #768
	beq	.L156
	ldrb	r3, [r5, #2776]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L156
	ldr	r1, [r5, #2788]
	mov	r3, #0
	ldr	r0, [r10, #716]
	add	r1, r1, #146
	ldr	r2, [r10, r1, asl #2]
	add	r2, r2, r0
	bic	r2, r2, #15
	b	.L102
.L162:
	mov	r2, #1
	mov	r0, r6
	str	r2, [sp]
	mov	r3, r8
	mov	r2, r7
	mov	r1, r5
	bl	H264HAL_SetSliceMsgRefPicField.isra.3
	b	.L114
.L156:
	ldr	r2, [r5, #2788]
	mov	r3, #0
	b	.L155
.L165:
	add	r2, r2, #146
	ldr	r3, [r10, #716]
	ldr	r2, [r10, r2, asl #2]
	add	r3, r2, r3
	bic	r2, r2, #15
	bic	r3, r3, #15
	b	.L102
.L164:
	add	r6, r5, #1360
	add	r9, r5, #596
	add	r6, r6, #4
	mov	r4, #0
.L129:
	ldr	r2, [r9, #4]!
	mov	r0, #4
	ldr	r1, .L166+88
	add	r4, r4, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L166+92
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r5, #40]
	cmp	r4, r3
	bls	.L129
	b	.L128
.L124:
	add	r6, r5, #1232
	add	r9, r5, #468
	add	r6, r6, #4
	mov	r4, #0
.L126:
	ldr	r2, [r9, #4]!
	mov	r0, #4
	ldr	r1, .L166+96
	add	r4, r4, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #4]!
	ldr	r1, .L166+100
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r3, [r5, #40]
	cmp	r4, r3
	bls	.L126
	b	.L127
.L158:
	ldr	r3, .L166+104
	ldr	r2, .L166+108
	ldr	r1, .L166+112
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L153
.L167:
	.align	2
.L166:
	.word	.LC9
	.word	g_not_direct_8x8_inference_flag
	.word	.LANCHOR0
	.word	.LC10
	.word	.LC12
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC0
	.word	.LC16
	.word	.LC17
	.word	.LC18
	.word	.LC19
	.word	.LC20
	.word	.LC23
	.word	.LC24
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC30
	.word	.LC31
	.word	.LC11
	.word	.LC25
	.word	.LC26
	.word	.LC21
	.word	.LC22
	.word	.LC3
	.word	.LANCHOR0+96
	.word	.LC4
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_SetSliceMsg.isra.7, .-H264HAL_V5R6C1_SetSliceMsg.isra.7
	.align	2
	.global	H264HAL_V5R6C1_StartDec
	.type	H264HAL_V5R6C1_StartDec, %function
H264HAL_V5R6C1_StartDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	subs	r3, r1, #0
	mov	r7, r2
	str	r3, [fp, #-56]
	mov	r4, r0
	bgt	.L276
	cmp	r0, #0
	beq	.L277
	ldr	r3, [r0, #44]
	cmp	r3, #512
	bhi	.L173
	ldr	r3, [r0, #36]
	cmp	r3, #512
	bhi	.L173
	ldr	r0, [r0, #944]
	cmp	r0, #0
	beq	.L278
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	beq	.L240
	cmp	r3, #1
	moveq	r0, #0
	movteq	r0, 63941
	beq	.L176
	ldr	r1, .L292
	mov	r0, #0
	bl	dprint_vfmw
.L170:
	mvn	r0, #0
.L247:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L240:
	mov	r0, #0
	movt	r0, 63683
.L176:
	ldr	r3, [fp, #-56]
	movw	r5, #1228
	mul	r5, r5, r3
	ldr	r3, .L292+4
	ldr	r3, [r3, r5]
	cmp	r3, #0
	beq	.L279
.L177:
	ldr	r3, .L292+8
	mov	r0, #3
	ldr	r1, .L292+12
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
	bl	dprint_vfmw
	ldr	r0, [fp, #-56]
	ldr	r2, .L292+16
	ldr	r1, .L292+20
	mov	r3, r0, asl #6
	ldrb	r2, [r2]	@ zero_extendqisi2
	sub	r3, r3, r0, asl #3
	add	r3, r1, r3
	subs	r2, r2, #1
	ldr	r1, [r3, #8]
	movne	r2, #1
	cmp	r7, #0
	movne	r3, #0
	andeq	r3, r2, #1
	cmp	r3, #0
	bne	.L280
	ldr	r3, .L292+24
	mov	r0, #8
	ldr	r5, [r3, r1, asl #2]
	cmp	r5, #0
	ldrne	r9, [r5, #1208]
	moveq	r3, r5
	moveq	r9, r5
	uxtbne	r3, r9
	andne	r5, r3, #1
	cmp	r2, #0
	strneb	r3, [r7, #1]
	mov	r3, #0
	ldr	lr, [r4, #1184]
	ldr	ip, [r4, #740]
	cmp	lr, #1
	str	r3, [fp, #-48]
	ldr	r1, [fp, #-48]
	movne	lr, r3
	moveq	lr, #3
	cmp	ip, #262144
	mov	r3, r7
	suble	ip, ip, #1
	ldr	r2, [fp, #-56]
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
	ldr	r6, [fp, #-48]
	mov	r1, r6
	str	r6, [r4, #956]
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+28
	mov	r0, #3
	bl	dprint_vfmw
	ldrb	r2, [r4, #16]	@ zero_extendqisi2
	ldrb	ip, [r4, #2]	@ zero_extendqisi2
	mov	r3, #0
	ldrb	r0, [r4, #3]	@ zero_extendqisi2
	bfi	r3, r2, #4, #1
	bfi	r3, ip, #6, #1
	mov	r1, #0
	cmp	r0, r1
	mov	r2, #0
	mvn	r3, r3, asl #25
	bfi	r2, r1, #0, #4
	mvn	r3, r3, lsr #25
	strb	r2, [fp, #-48]
	strb	r3, [fp, #-47]
	mov	r2, #1
	mov	r3, #0
	strh	r2, [fp, #-46]	@ movhi
	bfi	r3, r5, #4, #1
	strb	r3, [fp, #-45]
	bne	.L281
.L182:
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2
	mov	r3, #0
	mov	r2, r3
	strb	r3, [r4, #4]
	bfc	r1, #5, #1
	strb	r1, [fp, #-45]
.L184:
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2
	mov	r5, #0
	strb	r5, [r4, #17]
	mov	r3, r7
	bfi	r1, r2, #6, #1
	ldr	r10, [fp, #-56]
	bfi	r1, r5, #7, #1
	strb	r1, [fp, #-45]
	ldr	r6, [fp, #-48]
	mov	r0, #12
	mov	r2, r10
	movw	r8, #1228
	mov	r1, r6
	str	r6, [r4, #960]
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+32
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r2, .L292+4
	mov	r3, r7
	mov	r0, #16
	mla	r8, r8, r10, r2
	mov	r2, r10
	ldr	r6, [r8, #56]
	bic	r6, r6, #15
	str	r6, [r4, #964]
	mov	r1, r6
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+36
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r6, [r8, #40]
	mov	r3, r7
	mov	r2, r10
	bic	r6, r6, #15
	mov	r0, #20
	str	r6, [r4, #968]
	mov	r1, r6
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+40
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r6, [r4, #736]
	mov	r3, r7
	mov	r2, r10
	bic	r6, r6, #15
	mov	r0, #24
	str	r6, [r4, #972]
	mov	r1, r6
	str	r6, [fp, #-48]
	bl	MFDE_ConfigReg
	ldr	r1, .L292+44
	mov	r2, r6
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r3, [r4, #44]
	cmp	r3, #256
	movhi	r1, r5
	bls	.L282
.L185:
	ldr	r5, [fp, #-56]
	movw	r6, #3075
	movt	r6, 48
	mov	r3, r7
	mov	r0, #4
	mov	r2, r5
	bl	SCD_ConfigReg
	mov	r1, r6
	mov	r3, r7
	mov	r2, r5
	mov	r0, #60
	str	r6, [fp, #-48]
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r5
	mov	r1, r6
	mov	r0, #64
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r5
	mov	r1, r6
	mov	r0, #68
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r5
	mov	r1, r6
	mov	r0, #72
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r5
	mov	r1, r6
	mov	r0, #76
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r5
	mov	r1, r6
	mov	r0, #80
	bl	MFDE_ConfigReg
	mov	r3, r7
	mov	r2, r5
	mov	r1, r6
	mov	r0, #84
	bl	MFDE_ConfigReg
	cmp	r9, #1
	beq	.L283
.L186:
	ldr	r1, [r4, #308]
	mov	r3, r7
	ldr	r8, [fp, #-56]
	mov	r0, #96
	movw	r9, #1228
	mov	r10, #0
	add	r1, r4, r1, lsl #2
	mov	r5, r10
	mov	r2, r8
	ldr	r6, [r1, #324]
	bic	r6, r6, #15
	str	r6, [r4, #1008]
	mov	r1, r6
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+48
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r6, [r4, #720]
	mov	r3, r7
	mov	r2, r8
	mov	r0, #100
	mov	r1, r6
	str	r6, [r4, #1012]
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+52
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r6, [r4, #320]
	mov	r3, r7
	mov	r2, r8
	mov	r0, #104
	mov	r1, r6
	str	r6, [r4, #1016]
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+56
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r6, [r4, #732]
	mov	r3, r7
	mov	r2, r8
	mov	r0, #108
	mov	r1, r6
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+60
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, .L292+4
	mov	r2, r8
	str	r8, [fp, #-56]
	mov	r3, r7
	mov	r0, #128
	mla	r9, r9, r8, r1
	mov	r6, r10
	ldr	r8, [r9, #1164]
	bic	r8, r8, #15
	str	r8, [r4, #1032]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L292+64
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r9, #1168]
	str	r10, [fp, #-48]
	mov	r3, r7
	ldr	r2, [fp, #-56]
	mov	r0, #132
	strh	r1, [fp, #-48]	@ movhi
	ldr	r8, [fp, #-48]
	mov	r1, r8
	str	r8, [r4, #1036]
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L292+68
	mov	r0, #3
	bl	dprint_vfmw
	add	r2, r4, #1040
	add	r2, r2, #8
.L187:
	ldr	r3, [r2, #4]!
	and	r3, r3, #3
	orr	r6, r6, r3, asl r5
	add	r5, r5, #2
	cmp	r5, #32
	bne	.L187
	ldr	r8, [fp, #-56]
	mov	r3, r7
	mov	r1, r6
	mov	r0, #148
	mov	r2, r8
	bl	MFDE_ConfigReg
	mov	r2, r6
	ldr	r1, .L292+72
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r7
	mov	r2, r8
	mov	r1, #0
	mov	r0, #152
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L292+76
	mov	r0, #3
	bl	dprint_vfmw
	mov	r0, r5
	mov	r3, r7
	mov	r2, r8
	mvn	r1, #0
	bl	MFDE_ConfigReg
	ldr	r1, .L292+4
	movw	r3, #1228
	mla	r3, r3, r8, r1
	ldr	r2, [r3, #56]
	ldr	r5, [r3, #60]
	mov	r0, r2
	str	r2, [fp, #-64]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-60]
	beq	.L284
	ldrb	ip, [r4]	@ zero_extendqisi2
	ldr	r3, [r4, #52]
	ldr	r0, [r4, #48]
	ldr	r1, [r4, #56]
	add	ip, r0, ip, lsl #1
	mov	r3, r3, asl #28
	ldr	r0, [r4, #60]
	orr	r3, r3, r1, asl #27
	ldr	lr, .L292+80
	ldr	r1, [r4, #44]
	orr	r0, r3, r0, asl #26
	add	ip, lr, ip, lsl #2
	ldr	r3, [r4, #36]
	sub	r1, r1, #1
	orr	r1, r0, r1
	ldr	r0, [r4, #32]
	ldr	ip, [ip, #216]
	sub	r3, r3, #1
	ldrb	lr, [r4, #1]	@ zero_extendqisi2
	cmp	r0, #0
	ldr	r6, [fp, #-60]
	orr	r3, r1, r3, asl #16
	ldr	r7, [fp, #-64]
	orr	r3, r3, ip, asl #14
	movne	r0, #-2147483648
	cmp	lr, #1
	orr	r3, r3, r0
	ldr	r1, .L292+84
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
	ldr	r1, .L292+88
	bic	r3, r3, #15
	mov	r0, #4
	str	r3, [r6, #4]
	ldr	r3, [r6, #4]
	bl	dprint_vfmw
	ldr	r3, [r4, #64]
	add	r2, r7, #8
	ldr	r1, .L292+92
	mov	r0, #4
	str	r3, [r6, #8]
	ldr	r3, [r6, #8]
	bl	dprint_vfmw
	ldr	r3, [r4, #48]
	cmp	r3, #0
	bne	.L285
	ldr	r6, [fp, #-60]
	mov	r0, #4
	ldr	r7, [fp, #-64]
	ldr	r1, .L292+96
	str	r3, [r6, #12]
	add	r2, r7, #12
	str	r3, [r6, #16]
	ldr	r3, [r6, #12]
	bl	dprint_vfmw
	ldr	r3, [r6, #16]
.L271:
	add	r2, r7, #16
	ldr	r1, .L292+100
	mov	r0, #4
	bic	r5, r5, #15
	bl	dprint_vfmw
	ldr	r1, [fp, #-56]
	ldr	r0, .L292+4
	movw	r3, #1228
	ldr	r7, [fp, #-60]
	ldr	r8, [fp, #-64]
	mla	r3, r3, r1, r0
	add	r2, r8, #20
	ldr	r1, .L292+104
	mov	r0, #4
	add	r6, r3, #1136
	ldr	r3, [r3, #1144]
	bic	r3, r3, #15
	str	r3, [r7, #20]
	ldr	r3, [r7, #20]
	bl	dprint_vfmw
	ldr	r3, [r6, #12]
	add	r2, r8, #24
	ldr	r1, .L292+108
	bic	r3, r3, #15
	mov	r0, #4
	str	r3, [r7, #24]
	ldr	r3, [r7, #24]
	bl	dprint_vfmw
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r6, [fp, #-60]
	mov	r0, #4
	cmp	r3, #2
	ldr	r7, [fp, #-64]
	ldreq	r2, [r4, #316]
	ldrne	r3, [r4, #316]
	ldreq	r1, [r4, #716]
	addne	r3, r3, #146
	ldrne	r3, [r4, r3, asl #2]
	addeq	r2, r2, #146
	ldreq	r3, [r4, r2, asl #2]
	add	r2, r7, #28
	addeq	r3, r3, r1
	ldr	r1, .L292+112
	bic	r3, r3, #15
	str	r3, [r6, #28]
	ldr	r3, [r6, #28]
	bl	dprint_vfmw
	ldr	r2, [fp, #-56]
	ldr	r1, .L292+4
	movw	r3, #1228
	mov	r0, #4
	mla	r3, r3, r2, r1
	add	r2, r7, #32
	ldr	r1, .L292+116
	ldr	r3, [r3, #1152]
	bic	r3, r3, #15
	str	r3, [r6, #32]
	ldr	r3, [r6, #32]
	bl	dprint_vfmw
	str	r5, [r6, #36]
	add	r2, r7, #36
	ldr	r1, .L292+120
	mov	r0, #4
	ldr	r3, [r6, #36]
	bl	dprint_vfmw
	ldr	r5, [r4, #936]
	cmp	r5, #0
	beq	.L286
	ldr	r3, [fp, #-60]
	add	r8, r4, #740
	ldr	r2, [fp, #-64]
	mov	r6, #0
	add	r7, r3, #40
	rsb	r10, r3, r2
.L197:
	ldr	r0, [r8, #4]!
	mov	r3, r7
	add	r2, r6, #10
	ldr	r1, .L292+124
	add	r6, r6, #1
	add	r0, r4, r0, lsl #2
	ldr	lr, [r0, #324]
	mov	r0, #4
	bic	lr, lr, #15
	str	lr, [r3], r10
	ldr	ip, [r7]
	add	r7, r7, r0
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r5, [r4, #936]
	cmp	r6, r5
	bcc	.L197
	cmp	r5, #15
	bhi	.L201
.L196:
	add	r2, r5, #10
	ldr	r3, [fp, #-60]
	add	r6, r3, r2, lsl #2
.L200:
	ldr	lr, [r4, #744]
	mov	r3, r6
	add	r5, r5, #1
	mov	r0, #4
	ldr	r1, .L292+124
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
	bls	.L200
.L201:
	ldr	r1, [fp, #-56]
	movw	r3, #1228
	ldr	r0, .L292+4
	ldr	ip, [fp, #-60]
	ldr	r2, [fp, #-64]
	mla	r3, r3, r1, r0
	add	r2, r2, #104
	ldr	r1, .L292+128
	mov	r0, #4
	ldr	r3, [r3, #1088]
	bic	r3, r3, #15
	str	r3, [ip, #104]
	ldr	r3, [ip, #104]
	bl	dprint_vfmw
	ldr	r6, [r4, #936]
	cmp	r6, #0
	beq	.L287
	ldr	r3, [fp, #-64]
	add	r9, r4, #804
	mov	r5, #0
	add	r3, r3, #108
	str	r3, [fp, #-68]
	ldr	r3, [fp, #-60]
	add	r8, r3, #108
	add	r7, r3, #112
.L203:
	ldr	r0, [r9, #4]!
	mov	r3, r8
	mov	r6, r5, asl #1
	ldr	r1, .L292+124
	add	r2, r6, #27
	add	r5, r5, #1
	str	r0, [r3], r10
	mov	r0, #4
	ldr	ip, [r7, #-4]
	add	r8, r8, #8
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r9, #64]
	mov	r3, r7
	add	r2, r6, #28
	ldr	r1, .L292+124
	mov	r0, #4
	str	ip, [r3], r10
	add	r7, r7, #8
	ldr	ip, [r8, #-4]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r6, [r4, #936]
	cmp	r5, r6
	bcc	.L203
	cmp	r6, #15
	bhi	.L205
.L202:
	ldr	r2, [fp, #-68]
	mov	r7, r6, asl #1
	ldr	r3, [fp, #-60]
	add	r7, r7, #27
	str	r4, [fp, #-68]
	mov	r8, #0
	rsb	r9, r3, r2
	ldr	r2, [fp, #-64]
	add	r5, r3, r6, lsl #3
	mov	r4, r3
	add	r10, r2, #112
.L204:
	str	r8, [r5, #108]
	add	r3, r9, r5
	ldr	ip, [r5, #108]
	mov	r2, r7
	ldr	r1, .L292+124
	mov	r0, #4
	add	r6, r6, #1
	str	ip, [sp]
	bl	dprint_vfmw
	str	r8, [r5, #112]
	ldr	ip, [r5, #112]
	rsb	r3, r4, r10
	add	r3, r3, r5
	add	r2, r7, #1
	ldr	r1, .L292+124
	mov	r0, #4
	str	ip, [sp]
	add	r5, r5, #8
	bl	dprint_vfmw
	cmp	r6, #15
	add	r7, r7, #2
	bls	.L204
	ldr	r4, [fp, #-68]
.L205:
	ldr	r3, [fp, #-64]
	movw	ip, #1228
	ldr	r1, .L292+4
	add	r0, r4, #76
	add	r2, r3, #256
	ldr	r3, [fp, #-56]
	ldr	lr, [fp, #-60]
	mla	ip, ip, r3, r1
	add	r3, lr, #256
	mov	r1, #56
	ldr	ip, [ip, #1160]
	bic	ip, ip, #15
	str	ip, [lr, #236]
	bl	Write_V5R6C1_Qmatrix
.L189:
	ldr	r3, [r4, #1184]
	ldr	r7, [r4, #944]
	cmp	r3, #1
	beq	.L288
	ldr	r10, [r7, #48]
	cmp	r10, #0
	bne	.L289
.L209:
	ldr	r3, [fp, #-56]
	movw	r9, #307
	ldr	r1, [r4, #940]
	mov	r8, #0
	mov	r6, r8
	mul	r9, r9, r3
.L211:
	cmp	r6, r1
	bge	.L290
.L224:
	ldr	r0, [r7, #48]
	add	ip, r10, #5
	add	lr, ip, r6
	cmp	r0, r8
	add	r3, r9, lr
	add	r3, r3, #10
	movhi	r2, #0
	movls	r2, #1
	cmp	r6, #0
	movle	r2, #0
	cmp	r2, #0
	ldr	r2, .L292+4
	ldr	r2, [r2, r3, asl #2]
	bne	.L211
	add	r6, r6, #1
	mov	r8, r0
	cmp	r6, r1
	bge	.L213
	ldr	r5, [r7, #4056]
	cmp	r5, #0
	beq	.L214
	ldr	r3, [r5, #48]
	cmp	r0, r3
	bcs	.L218
	b	.L229
.L219:
	ldr	r5, [r5, #4056]
	cmp	r5, #0
	beq	.L214
	ldr	r3, [r5, #48]
	cmp	r0, r3
	bcc	.L229
.L218:
	add	r6, r6, #1
	cmp	r6, r1
	bne	.L219
	cmp	r5, #0
	beq	.L170
.L230:
	ldr	ip, [r4, #36]
	mov	r0, #0
	ldr	r1, [r4, #44]
	mov	r3, r0
	str	r0, [r7, #4056]
	ldr	r6, [r4, #940]
	mul	r1, r1, ip
	sub	r1, r1, #1
.L222:
	str	r1, [sp]
	mov	r0, r4
	mov	r1, r7
	bl	H264HAL_V5R6C1_SetSliceMsg.isra.7
	cmp	r0, #0
	bne	.L223
	ldr	r1, [r4, #940]
	mov	r7, r5
	cmp	r6, r1
	blt	.L224
.L290:
	cmp	r1, #0
	ble	.L225
	ldr	r2, [fp, #-56]
	movw	r3, #307
	mla	r3, r3, r2, r10
	ldr	r2, .L292+4
	add	r3, r3, r1
	add	r3, r3, #14
	ldr	r0, [r2, r3, asl #2]
	bl	H264HAL_V5R6C1_CutSliceChain
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L282:
	cmp	r3, #119
	ldrhi	r1, [r4, #1180]
	movls	r1, #1
	clzhi	r1, r1
	movhi	r1, r1, lsr #5
	b	.L185
.L281:
	ldr	r3, [r4, #44]
	mov	r3, r3, asl #4
	cmp	r3, #1920
	bls	.L182
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	ldrb	r0, [fp, #-45]	@ zero_extendqisi2
	and	r2, r3, #1
	bfi	r0, r1, #5, #1
	strb	r0, [fp, #-45]
	b	.L184
.L285:
	ldr	r6, [fp, #-60]
	mov	r0, #4
	ldr	r3, [r4, #68]
	ldr	r7, [fp, #-64]
	ldr	r1, .L292+96
	str	r3, [r6, #12]
	add	r2, r7, #12
	ldr	ip, [r4, #72]
	ldr	r3, [r6, #12]
	str	ip, [r6, #16]
	bl	dprint_vfmw
	ldr	r3, [r6, #16]
	b	.L271
.L213:
	cmp	r7, #0
	beq	.L170
	mov	r5, r7
.L229:
	cmp	lr, #140
	cmpne	r6, r1
	beq	.L230
	add	r3, r9, ip
	ldr	r0, .L292+4
	add	r3, r3, r6
	ldr	r1, [r5, #48]
	add	r3, r3, #10
	sub	r1, r1, #1
	ldr	r3, [r0, r3, asl #2]
	b	.L222
.L214:
	movw	r2, #827
	ldr	r1, .L292+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L288:
	ldr	r2, [r4, #940]
	cmp	r2, #1
	ble	.L207
.L208:
	add	r3, r3, #1
	ldr	r7, [r7, #4056]
	cmp	r3, r2
	bne	.L208
.L207:
	ldr	r3, [fp, #-56]
	movw	lr, #1228
	ldr	r2, .L292+4
	mov	r1, r7
	ldr	ip, [r4, #36]
	mov	r0, r4
	mla	lr, lr, r3, r2
	ldr	r2, [r4, #44]
	mov	r3, #0
	mul	ip, r2, ip
	ldr	r2, [lr, #60]
	sub	ip, ip, #1
	str	ip, [sp]
	bl	H264HAL_V5R6C1_SetSliceMsg.isra.7
	cmp	r0, #0
	beq	.L247
	movw	r2, #1130
	ldr	r1, .L292+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L247
.L289:
	ldr	r3, [fp, #-56]
	movw	r2, #1228
	ldr	r1, .L292+4
	mov	r6, #1
	ldr	r9, [r7, #8]
	sub	ip, r10, #1
	str	r6, [r7, #8]
	mov	r0, r4
	mla	r2, r2, r3, r1
	ldr	r3, [r7, #12]
	ldr	r1, [r7, #20]
	ldr	r8, [r7, #28]
	str	r3, [fp, #-60]
	ldr	r3, [r7, #16]
	ldr	r5, [r7, #24]
	str	r1, [fp, #-68]
	mov	r1, r7
	str	r3, [fp, #-64]
	mov	r3, #0
	str	r3, [r7, #48]
	str	r3, [r7, #12]
	str	r3, [r7, #16]
	str	r3, [r7, #20]
	ldr	lr, [r4, #736]
	str	r3, [r7, #28]
	str	lr, [r7, #24]
	ldr	r3, [r2, #64]
	ldr	r2, [r2, #60]
	str	ip, [sp]
	bl	H264HAL_V5R6C1_SetSliceMsg.isra.7
	cmp	r0, #0
	bne	.L291
	ldr	r3, [fp, #-60]
	str	r10, [r7, #48]
	mov	r10, r6
	str	r9, [r7, #8]
	str	r3, [r7, #12]
	ldr	r3, [fp, #-64]
	str	r5, [r7, #24]
	str	r8, [r7, #28]
	str	r3, [r7, #16]
	ldr	r3, [fp, #-68]
	str	r3, [r7, #20]
	ldr	r7, [r4, #944]
	b	.L209
.L223:
	movw	r2, #1217
	ldr	r1, .L292+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L247
.L283:
	ldr	r1, .L292+140
	mov	r3, r7
	ldr	r6, [fp, #-56]
	mov	r0, #92
	ldr	r5, [r1]
	mov	r2, r6
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L292+144
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r4, #308]
	mov	r2, r6
	mov	r3, r7
	mov	r0, #112
	add	r1, r4, r1, lsl #2
	ldr	r5, [r1, #452]
	mov	r1, r5
	bl	MFDE_ConfigReg
	mov	r2, r5
	ldr	r1, .L292+148
	mov	r0, #3
	bl	dprint_vfmw
	b	.L186
.L287:
	ldr	r3, [fp, #-64]
	add	r3, r3, #108
	str	r3, [fp, #-68]
	b	.L202
.L286:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-60]
	rsb	r10, r2, r3
	b	.L196
.L279:
	bl	MEM_Phy2Vir
	ldr	r2, .L292+4
	cmp	r0, #0
	str	r0, [r5, r2]
	bne	.L177
	ldr	r1, .L292+152
	bl	dprint_vfmw
	b	.L170
.L276:
	mov	r0, #0
	ldr	r2, .L292+156
	str	r0, [sp]
	ldr	r1, .L292+160
	bl	dprint_vfmw
	b	.L170
.L173:
	ldr	r3, .L292+164
	mov	r0, #0
	ldr	r2, .L292+156
	ldr	r1, .L292+168
	bl	dprint_vfmw
	b	.L170
.L291:
	mov	r0, r6
	movw	r2, #1164
	ldr	r1, .L292+136
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L247
.L225:
	ldr	r1, .L292+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L247
.L280:
	mov	r3, r7
	ldr	r2, .L292+176
	ldr	r1, .L292+180
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L247
.L277:
	ldr	r3, .L292+184
	ldr	r2, .L292+156
	ldr	r1, .L292+168
	bl	dprint_vfmw
	b	.L170
.L278:
	ldr	r3, .L292+188
	ldr	r2, .L292+156
	ldr	r1, .L292+168
	bl	dprint_vfmw
	b	.L170
.L284:
	ldr	r3, .L292+192
	ldr	r2, .L292+196
	ldr	r1, .L292+168
	bl	dprint_vfmw
	b	.L189
.L293:
	.align	2
.L292:
	.word	.LC36
	.word	g_HwMem
	.word	.LANCHOR1
	.word	.LC70
	.word	g_HalDisable
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC39
	.word	.LC40
	.word	.LC41
	.word	.LC42
	.word	.LC43
	.word	.LC46
	.word	.LC47
	.word	.LC48
	.word	.LC49
	.word	.LC50
	.word	.LC51
	.word	.LC52
	.word	.LC53
	.word	.LANCHOR0
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
	.word	.LC65
	.word	.LC66
	.word	.LC68
	.word	.LC67
	.word	g_TunnelLineNumber
	.word	.LC44
	.word	.LC45
	.word	.LC37
	.word	.LANCHOR0+136
	.word	.LC32
	.word	.LC34
	.word	.LC4
	.word	.LC69
	.word	.LANCHOR0+160
	.word	.LC38
	.word	.LC33
	.word	.LC35
	.word	.LC54
	.word	.LANCHOR0+188
	UNWIND(.fnend)
	.size	H264HAL_V5R6C1_StartDec, .-H264HAL_V5R6C1_StartDec
	.section	.rodata
	.align	2
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
	.type	__func__.14527, %object
	.size	__func__.14527, 29
__func__.14527:
	.ascii	"H264HAL_V5R6C1_CutSliceChain\000"
	.space	3
	.type	__func__.14738, %object
	.size	__func__.14738, 27
__func__.14738:
	.ascii	"H264HAL_V5R6C1_SetSliceMsg\000"
	.space	1
	.type	g_SliceTypeForPMV, %object
	.size	g_SliceTypeForPMV, 12
g_SliceTypeForPMV:
	.word	1
	.word	2
	.word	0
	.type	__func__.14660, %object
	.size	__func__.14660, 23
__func__.14660:
	.ascii	"H264HAL_CheckParaValid\000"
	.space	1
	.type	__func__.14682, %object
	.size	__func__.14682, 25
__func__.14682:
	.ascii	"H264HAL_V5R6C1_CfgVdmReg\000"
	.space	3
	.type	__func__.14708, %object
	.size	__func__.14708, 25
__func__.14708:
	.ascii	"H264HAL_V5R6C1_SetPicMsg\000"
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"slicemsg D[%d] address 0x%x = 0x%x\012\000" )
.LC1:
	ASCII(.ascii	"line: %d, p = NULL is not expected value!\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"H264HAL_V5R6C1_InitHal return error.\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"can not map slice msg virtual address!\012\000" )
.LC4:
	ASCII(.ascii	"%s: %s\012\000" )
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
	ASCII(.ascii	"slicemsg D[4] addr 0x%x = 0x%x\012\000" )
.LC10:
	ASCII(.ascii	"slicemsg D[5] addr 0x%x = 0x%x\012\000" )
.LC11:
	ASCII(.ascii	"slicemsg g_pListX[1][0]->frame_store->pmv_address_i" )
	ASCII(.ascii	"dc = %d\012\000" )
.LC12:
	ASCII(.ascii	"slicemsg D[6] addr 0x%x = 0x%x\012\000" )
.LC13:
	ASCII(.ascii	"slicemsg D[7] addr 0x%x = 0x%x\012\000" )
.LC14:
	ASCII(.ascii	"slicemsg D[8] addr 0x%x = 0x%x\012\000" )
.LC15:
	ASCII(.ascii	"slicemsg D[9] addr 0x%x = 0x%x\012\000" )
.LC16:
	ASCII(.ascii	"slicemsg burst1 D0~D31, burst2 D0~31, burst3 D0~D31" )
	ASCII(.ascii	" list0size = %d\012\000" )
.LC17:
	ASCII(.ascii	"luma_lg = %d\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"wp_weight_l0_y = %d\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"wp_offset_l0_y = %d\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"chroma_lg = %d\012\000" )
.LC21:
	ASCII(.ascii	"wp_weight_l1_y = %d\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"wp_offset_l1_y = %d\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"wp_weight_l0_u = %d\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"wp_offset_l0_u = %d\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"wp_weight_l1_u = %d\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"wp_offset_l1_u = %d\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"wp_weight_l0_v = %d\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"wp_offset_l0_v = %d\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"wp_weight_l1_v = %d\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"wp_offset_l1_v = %d\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"slicemsg burst1 D32~D63, burst2 D32~63, burst3 D32~" )
	ASCII(.ascii	"D63 list1size = %d\012\000" )
	.space	1
.LC32:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC33:
	ASCII(.ascii	"point of picture para null\012\000" )
.LC34:
	ASCII(.ascii	"picture width out of range\012\000" )
.LC35:
	ASCII(.ascii	"point of fst slice para null\012\000" )
	.space	2
.LC36:
	ASCII(.ascii	"VdhId is wrong! H264HAL_V200R003_StartDec\012\000" )
	.space	1
.LC37:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC38:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC39:
	ASCII(.ascii	"BASIC_V5R6C1_CFG0 = 0x%x\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"BASIC_V5R6C1_CFG1 = 0x%x\012\000" )
	.space	2
.LC41:
	ASCII(.ascii	"AVM_V5R6C1_ADDR = 0x%x\012\000" )
.LC42:
	ASCII(.ascii	"VAM_V5R6C1_ADDR = 0x%x\012\000" )
.LC43:
	ASCII(.ascii	"STREAM_V5R6C1_BASE_ADDR = 0x%x\012\000" )
.LC44:
	ASCII(.ascii	"VREG_PART_DEC_OVER_INT_LEVEL=0x%x\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"YSTADDR_V5R6C1_1D = 0x%x\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"YSTRIDE_V5R6C1_1D = 0x%x\012\000" )
	.space	2
.LC48:
	ASCII(.ascii	"UVOFFSET_V5R6C1_1D = 0x%x\012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"HEAD_INF_OFFSET_V5R6C1_1D = 0x%x\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"PPFD_V5R6C1_BUF_ADDR = 0x%x\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"PPFD_V5R6C1_BUF_LEN = 0x%x\012\000" )
.LC52:
	ASCII(.ascii	"REF_V5R6C1_PIC_TYPE = 0x%x\012\000" )
.LC53:
	ASCII(.ascii	"FF_V5R6C1_APT_EN = 0x%x\012\000" )
	.space	3
.LC54:
	ASCII(.ascii	"can not map down msg virtual address!\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"picmsg D[0] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"picmsg D[1] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	"picmsg D[2] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC58:
	ASCII(.ascii	"picmsg D[3] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"picmsg D[4] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"picmsg D[5] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"picmsg D[6] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC62:
	ASCII(.ascii	"picmsg D[7] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"picmsg D[8] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC64:
	ASCII(.ascii	"picmsg D[9] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC65:
	ASCII(.ascii	"picmsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	1
.LC66:
	ASCII(.ascii	"picmsg D[26] addr 0x%x = 0x%x\012\000" )
	.space	1
.LC67:
	ASCII(.ascii	"line %d Set slice msg not wrong!\012\000" )
	.space	2
.LC68:
	ASCII(.ascii	"line %d pSlicePara is NULL!\012\000" )
	.space	3
.LC69:
	ASCII(.ascii	"!!! no slice to dec, add up msg report.\000" )
.LC70:
	ASCII(.ascii	"\012\012***********************H264HAL_V200R003_Sta" )
	ASCII(.ascii	"rtDec is Now %d***********************\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	StartCnt.14760, %object
	.size	StartCnt.14760, 4
StartCnt.14760:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
