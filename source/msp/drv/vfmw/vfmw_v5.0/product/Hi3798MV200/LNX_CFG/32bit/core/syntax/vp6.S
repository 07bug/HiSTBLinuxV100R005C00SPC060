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
	.file	"vp6.c"
	.text
	.align	2
	.global	Vp6_Vfmw_DecodeBool
	.type	Vp6_Vfmw_DecodeBool, %function
Vp6_Vfmw_DecodeBool:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r7, r1
	ldmib	r1, {r1, r5}
	mov	r6, r0
	ldr	r3, [r7, #12]
	sub	r4, r1, #1
	mul	r2, r4, r2
	mov	r4, r2, lsr #8
	add	r4, r4, #1
	mov	r2, r4, asl #16
	cmp	r5, r2
	rsbcs	r4, r4, r1
	rsbcs	r5, r2, r5
	movcs	r8, #1
	movcc	r8, #0
	cmp	r4, #127
	bls	.L6
	b	.L9
.L5:
	cmp	r4, #127
	bhi	.L11
.L6:
	subs	r3, r3, #1
	mov	r4, r4, asl #1
	mov	r5, r5, asl #1
	bne	.L5
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	cmp	r4, #127
	mov	r3, #8
	orr	r5, r5, r0
	bls	.L6
.L11:
	str	r3, [r7, #12]
.L9:
	stmib	r7, {r4, r5}
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp6_Vfmw_DecodeBool, .-Vp6_Vfmw_DecodeBool
	.align	2
	.global	Vp6_Vfmw_DecodeBool128
	.type	Vp6_Vfmw_DecodeBool128, %function
Vp6_Vfmw_DecodeBool128:
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
	ldr	r5, [r1, #4]
	mov	r4, r1
	ldr	r2, [r1, #8]
	add	r3, r5, #1
	ldr	r1, [r1, #12]
	mov	r3, r3, lsr #1
	mov	r6, r3, asl #16
	cmp	r2, r6
	rsbcs	r3, r3, r5
	rsbcs	r2, r6, r2
	movcs	r7, #1
	movcc	r5, r3, asl #1
	movcs	r5, r3, asl r7
	movcs	r6, r2, asl r7
	movcc	r6, r2, asl #1
	movcc	r7, #0
	subs	r1, r1, #1
	bne	.L15
	mov	r1, #8
	bl	BsGet
	mov	r1, #8
	orr	r6, r6, r0
.L15:
	str	r1, [r4, #12]
	mov	r0, r7
	stmib	r4, {r5, r6}
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp6_Vfmw_DecodeBool128, .-Vp6_Vfmw_DecodeBool128
	.align	2
	.global	Vp6_Vfmw_BoolRead
	.type	Vp6_Vfmw_BoolRead, %function
Vp6_Vfmw_BoolRead:
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
	subs	r4, r2, #1
	mov	r5, #0
	mov	r6, r0
	mov	r7, r1
	bmi	.L17
.L18:
	mov	r1, r7
	mov	r0, r6
	bl	Vp6_Vfmw_DecodeBool128
	orr	r5, r5, r0, asl r4
	subs	r4, r4, #1
	bcs	.L18
.L17:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp6_Vfmw_BoolRead, .-Vp6_Vfmw_BoolRead
	.align	2
	.global	Vp6_Vfmw_StartDecode
	.type	Vp6_Vfmw_StartDecode, %function
Vp6_Vfmw_StartDecode:
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
	mov	r4, r1
	mov	r2, #0
	mov	r3, #255
	stmia	r1, {r2, r3}
	mov	r3, #8
	mov	r1, #24
	str	r3, [r4, #12]
	bl	BsGet
	str	r0, [r4, #8]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp6_Vfmw_StartDecode, .-Vp6_Vfmw_StartDecode
	.align	2
	.global	VP6_ArrangeVHBMem
	.type	VP6_ArrangeVHBMem, %function
VP6_ArrangeVHBMem:
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
	add	r4, r0, #12288
	mov	r5, r0
	ldr	r3, [r4, #244]
	ldr	r2, [r4, #248]
	cmp	r3, #2
	bls	.L24
	sub	r0, r2, #3
	movw	r1, #509
	cmp	r3, #512
	cmpls	r0, r1
	bhi	.L24
	ldr	r1, [r5]
	ldr	r0, [r1, #732]
	cmp	r0, #0
	ldr	r0, [r1, #28]
	bne	.L27
	cmp	r0, #25
	beq	.L51
.L28:
	mov	r7, #3
	mov	r6, r2, asl #4
	mov	r8, r3, asl #4
	mov	r9, r7
	mov	r10, #5
.L33:
	ldr	r3, .L53
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r5]
	str	r6, [fp, #-60]
	str	r8, [fp, #-56]
	ldr	r3, [r3, #28]
	str	r6, [fp, #-52]
	cmp	r3, #24
	str	r8, [fp, #-48]
	beq	.L39
	uxtb	r7, r7
	strb	r9, [fp, #-63]
	strb	r10, [fp, #-62]
.L44:
	sub	r1, fp, #64
	ldr	r0, [r4, #752]
	strb	r7, [fp, #-61]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L40
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r4, #752]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L52
	cmp	r0, #0
	moveq	r0, #1
	streq	r0, [r4, #32]
	beq	.L48
.L42:
	ldr	r1, .L53+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L48
.L24:
	ldr	r1, .L53+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
.L48:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L27:
	cmp	r0, #25
	bne	.L28
	ldr	r0, [r1, #692]
	mov	r2, r2, asl #4
	ldr	ip, [r1, #696]
	mov	r3, r3, asl #4
	cmp	r2, r0
	bhi	.L36
	cmp	r3, ip
	bhi	.L36
	ldr	r0, [r1, #720]
	mov	r6, r2
	ldr	r2, [r1, #716]
	mov	r8, r3
	cmp	r0, #0
	add	r9, r2, #2
	beq	.L46
	add	r7, r2, #1
	cmp	r7, #17
	movge	r7, #17
.L38:
	ldrb	r10, [r1, #740]	@ zero_extendqisi2
	b	.L33
.L40:
	ldr	r1, .L53+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L48
.L39:
	mov	r7, #1
	strb	r10, [fp, #-62]
	strb	r7, [fp, #-63]
	b	.L44
.L51:
	ldr	r6, [r1, #692]
	mov	r2, r2, asl #4
	ldr	r8, [r1, #696]
	mov	r3, r3, asl #4
	cmp	r2, r6
	bhi	.L30
	cmp	r3, r8
	bhi	.L30
	ldr	r0, [r4, #32]
	cmp	r0, #1
	beq	.L48
	ldr	r2, [r1, #720]
	ldr	r3, [r1, #716]
	cmp	r2, #0
	add	r9, r3, #2
	beq	.L46
	add	r7, r3, #1
	cmp	r7, #17
	movge	r7, #17
	b	.L38
.L36:
	stmia	sp, {r0, ip}
	mov	r0, #0
	ldr	r1, .L53+16
	bl	dprint_vfmw
	mov	r0, #0
	b	.L48
.L46:
	mov	r7, #1
	b	.L38
.L30:
	stmia	sp, {r6, r8}
	mov	r0, #0
	ldr	r1, .L53+16
	bl	dprint_vfmw
	mov	r0, #0
	b	.L48
.L52:
	add	r0, r5, #12672
	add	r0, r0, #16
	bl	ResetVoQueue
	b	.L42
.L54:
	.align	2
.L53:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC0
	.word	.LC3
	.word	.LC1
	UNWIND(.fnend)
	.size	VP6_ArrangeVHBMem, .-VP6_ArrangeVHBMem
	.align	2
	.global	VP6_GetImageBuffer
	.type	VP6_GetImageBuffer, %function
VP6_GetImageBuffer:
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
	add	r4, r0, #12288
	mov	r6, r0
	mov	r1, #1
	ldr	r0, [r4, #752]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #44]
	blt	.L61
	mov	r1, r0
	ldr	r0, [r4, #752]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L62
	ldr	r2, [r4, #44]
	mov	r0, #18
	ldr	r1, .L63
	bl	dprint_vfmw
	ldr	r0, [r5, #28]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r5, #32]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r0, #24]
	mov	r0, #18
	ldr	r1, .L63+4
	str	r3, [r4, #60]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #28]
	str	r3, [r4, #64]
	ldr	r3, [r5, #32]
	ldr	r2, [r5, #28]
	ldr	r3, [r3, #8]
	ldr	r2, [r2, #8]
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L61:
	ldr	r1, .L63+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #48]
	ldr	r0, [r4, #752]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #52]
	mov	r5, #0
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #48]
	str	r5, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_GetNullLogicFs
	add	r1, r6, #12672
	str	r5, [r4, #28]
	add	r1, r1, #16
	str	r0, [r4, #52]
	str	r0, [r4, #48]
	ldr	r0, [r4, #752]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L62:
	mov	r2, #636
	ldr	r1, .L63+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L64:
	.align	2
.L63:
	.word	.LC6
	.word	.LC7
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	VP6_GetImageBuffer, .-VP6_GetImageBuffer
	.align	2
	.global	VP6DEC_GetImageBuffer
	.type	VP6DEC_GetImageBuffer, %function
VP6DEC_GetImageBuffer:
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
	subs	r5, r0, #0
	beq	.L72
	add	r4, r5, #12288
	ldr	r0, [r4, #752]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #752]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L73
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L73:
	add	r1, r5, #12672
	ldr	r0, [r4, #752]
	add	r1, r1, #16
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L72:
	movw	r2, #659
	ldr	r1, .L74
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L75:
	.align	2
.L74:
	.word	.LC8
	UNWIND(.fnend)
	.size	VP6DEC_GetImageBuffer, .-VP6DEC_GetImageBuffer
	.align	2
	.global	VP6_BuildScanOrder
	.type	VP6_BuildScanOrder, %function
VP6_BuildScanOrder:
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
	add	r5, r0, #1088
	mov	r4, #1
	mov	lr, #0
	strb	lr, [r0, #960]
.L77:
	mov	r2, r5
	mov	r3, #1
.L79:
	ldrb	ip, [r2, #1]!	@ zero_extendqisi2
	cmp	ip, lr
	addeq	ip, r0, r4
	addeq	r4, r4, #1
	streqb	r3, [ip, #960]
	add	r3, r3, #1
	cmp	r3, #64
	bne	.L79
	add	lr, lr, #1
	cmp	lr, #16
	bne	.L77
	add	r5, r0, #1020
	add	r4, r0, #956
	add	r5, r5, #3
	add	r4, r4, #3
	mov	lr, #0
.L80:
	mov	r3, #0
	mov	ip, r4
	mov	r2, r3
.L81:
	ldrb	r0, [ip, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r3, r0
	movcc	r3, r0
	cmp	r2, lr
	bls	.L81
	uxtb	r3, r3
	strb	r3, [r5, #1]!
	ldr	r2, [r1, #16]
	add	lr, lr, #1
	cmp	r2, #6
	addhi	r3, r3, #1
	strhib	r3, [r5]
	cmp	lr, #64
	bne	.L80
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_BuildScanOrder, .-VP6_BuildScanOrder
	.global	__aeabi_idiv
	.global	__aeabi_uidiv
	.align	2
	.global	VP6_BuildModeTree
	.type	VP6_BuildModeTree, %function
VP6_BuildModeTree:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 96
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #100)
	sub	sp, sp, #100
	mov	r9, #0
	mov	r10, #100
	mov	r7, r9
	add	r2, r0, #404
	add	r3, r0, #464
	str	r0, [fp, #-128]
	str	r0, [fp, #-132]
	str	r2, [fp, #-140]
	str	r3, [fp, #-136]
.L88:
	ldr	r3, [fp, #-128]
	ldr	r8, [fp, #-140]
	ldr	r9, [fp, #-132]
	str	r3, [fp, #-92]
	str	r3, [fp, #-88]
.L94:
	mov	r4, #0
	sub	r1, fp, #84
	mov	r2, r4
	mov	r0, r8
.L91:
	cmp	r7, r2
	add	r2, r2, #1
	add	r1, r1, #4
	add	r0, r0, #1
	ldrneb	r3, [r0, #-1]	@ zero_extendqisi2
	moveq	r3, #0
	smulbbne	r3, r3, r10
	cmp	r2, #10
	add	r4, r4, r3
	str	r3, [r1, #-4]
	bne	.L91
	ldr	r2, [fp, #-88]
	add	r8, r8, #20
	add	r9, r9, #90
	add	r2, r2, #20
	ldrb	r0, [r2, #394]	@ zero_extendqisi2
	ldrb	r3, [r2, #384]	@ zero_extendqisi2
	str	r2, [fp, #-88]
	mvn	r1, r0
	rsb	r0, r0, r0, lsl #8
	rsb	r1, r3, r1
	bl	__aeabi_idiv
	ldr	r3, [fp, #-84]
	ldr	r6, [fp, #-76]
	add	r1, r4, #1
	ldr	r5, [fp, #-92]
	mov	r2, r3
	ldr	r3, [fp, #-72]
	add	r6, r2, r6
	str	r2, [fp, #-96]
	add	r5, r5, #10
	mov	ip, r3
	ldr	r3, [fp, #-68]
	str	ip, [fp, #-100]
	add	lr, ip, r3
	str	lr, [fp, #-108]
	add	r4, lr, r6
	sub	r3, r0, #1
	rsb	r0, r4, r4, lsl #8
	strb	r3, [r5, #-6]
	str	r5, [fp, #-92]
	bl	__aeabi_uidiv
	add	r1, r4, #1
	add	r3, r0, #1
	rsb	r0, r6, r6, lsl #8
	strb	r3, [r9, #-46]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-80]
	ldr	r4, [fp, #-64]
	ldr	r5, [fp, #-56]
	ldr	r1, [fp, #-52]
	add	r5, r3, r5
	ldr	r2, [fp, #-48]
	str	r3, [fp, #-124]
	mov	r3, r4
	ldr	r4, [fp, #-60]
	add	r2, r1, r2
	add	ip, r2, #1
	str	r1, [fp, #-112]
	add	r4, r3, r4
	add	r1, r2, r5
	add	r2, r4, #1
	str	r3, [fp, #-104]
	add	r1, r1, r2
	str	ip, [fp, #-116]
	str	r2, [fp, #-120]
	add	r0, r0, #1
	strb	r0, [r9, #-45]
	rsb	r0, r5, r5, lsl #8
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-96]
	add	r1, r6, #1
	add	ip, r0, #1
	rsb	r0, r2, r2, lsl #8
	strb	ip, [r9, #-44]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-100]
	ldr	lr, [fp, #-108]
	add	r1, lr, #1
	add	ip, r0, #1
	rsb	r0, r3, r3, lsl #8
	strb	ip, [r9, #-43]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-124]
	add	r1, r5, #1
	add	ip, r0, #1
	rsb	r0, r3, r3, lsl #8
	strb	ip, [r9, #-42]
	bl	__aeabi_uidiv
	ldr	r5, [fp, #-116]
	add	r1, r5, r4
	add	r3, r0, #1
	rsb	r0, r4, r4, lsl #8
	strb	r3, [r9, #-41]
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-120]
	ldr	r4, [fp, #-104]
	mov	r1, r2
	add	r3, r0, #1
	rsb	r0, r4, r4, lsl #8
	strb	r3, [r9, #-40]
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-112]
	mov	r1, r5
	add	r3, r0, #1
	rsb	r0, r2, r2, lsl #8
	strb	r3, [r9, #-39]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-136]
	cmp	r8, r3
	add	r0, r0, #1
	strb	r0, [r9, #-38]
	bne	.L94
	ldr	r3, [fp, #-128]
	add	r7, r7, #1
	cmp	r7, #10
	add	r3, r3, #1
	str	r3, [fp, #-128]
	ldr	r3, [fp, #-132]
	add	r3, r3, #9
	str	r3, [fp, #-132]
	bne	.L88
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_BuildModeTree, .-VP6_BuildModeTree
	.align	2
	.global	VP6_ConfigureContexts
	.type	VP6_ConfigureContexts, %function
VP6_ConfigureContexts:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r7, r0, #1184
	add	lr, r0, #516
	add	r7, r7, #5
	add	lr, lr, #2
	add	r0, r0, #540
.L97:
	ldr	r6, .L105
	sub	r5, r7, #33
	add	r4, lr, #6
	sub	r8, lr, #5
.L102:
	sub	ip, r5, #5
	mov	r1, r8
	mov	r2, r6
.L98:
	ldmia	r2, {r3, r9}
	add	r2, r2, #24
	ldrb	r10, [r1, #1]!	@ zero_extendqisi2
	mul	r3, r3, r10
	add	r3, r3, #128
	add	r3, r9, r3, asr #8
	cmp	r3, #255
	movge	r3, #255
	cmp	r3, #1
	movlt	r3, #1
	cmp	r1, lr
	strb	r3, [ip, #1]!
	bne	.L98
	mov	r2, r5
	mov	r3, lr
.L99:
	ldrb	r1, [r3, #1]!	@ zero_extendqisi2
	cmp	r4, r3
	strb	r1, [r2, #1]!
	bne	.L99
	add	r5, r5, #11
	add	r6, r6, #8
	cmp	r7, r5
	bne	.L102
	add	lr, lr, #11
	add	r7, r7, #33
	cmp	lr, r0
	bne	.L97
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L106:
	.align	2
.L105:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VP6_ConfigureContexts, .-VP6_ConfigureContexts
	.align	2
	.global	VP6_ConfigureEntropyDecoder
	.type	VP6_ConfigureEntropyDecoder, %function
VP6_ConfigureEntropyDecoder:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	mov	r5, r2
	str	r2, [fp, #-96]
	add	r7, r5, #76
	ldr	r2, .L157
	mov	r8, r1
	str	r0, [fp, #-76]
	mov	r1, #128
	sub	r0, fp, #56
	str	r3, [fp, #-64]
	ldr	r4, [r2, #48]
	mov	r2, #11
	blx	r4
	mov	r3, #0
	str	r3, [fp, #-68]
.L108:
	ldr	r3, [fp, #-68]
	sub	r4, fp, #56
	add	r5, r3, #512
	sub	r6, r3, #1
	ldr	r3, .L157+4
	add	r5, r5, #2
	add	r6, r3, r6
	ldr	r3, [fp, #-76]
	add	r5, r3, r5
.L112:
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L109
	mov	r10, #0
	mov	r9, #6
.L110:
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r9
	subs	r9, r9, #1
	bcs	.L110
	mov	r3, r10, asl #1
	ands	r3, r3, #255
	moveq	r2, #1
	movne	r2, #0
	add	r3, r3, r2
	uxtb	r3, r3
	strb	r3, [r4]
	strb	r3, [r5]
.L111:
	add	r4, r4, #1
	sub	r3, fp, #45
	cmp	r4, r3
	add	r5, r5, #1
	bne	.L112
	ldr	r3, [fp, #-68]
	add	r3, r3, #11
	str	r3, [fp, #-68]
	cmp	r3, #22
	bne	.L108
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	ldr	r3, [fp, #-76]
	add	r3, r3, #536
	strne	r3, [fp, #-68]
	bne	.L114
	mov	r0, r3
	str	r3, [fp, #-68]
	ldr	r3, .L157
	mov	r2, #28
	ldr	r1, .L157+8
	ldr	r3, [r3, #52]
	blx	r3
.L114:
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	beq	.L118
	ldr	r3, [fp, #-76]
	ldr	r4, .L157+12
	add	r5, r3, #1088
	add	r5, r5, #1
	add	r6, r4, #63
.L117:
	ldrb	r2, [r4, #1]!	@ zero_extendqisi2
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L115
	mov	r10, #0
	mov	r9, #3
.L116:
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r9
	subs	r9, r9, #1
	bcs	.L116
	strb	r10, [r5]
.L115:
	cmp	r4, r6
	add	r5, r5, #1
	bne	.L117
	ldr	r1, [fp, #-96]
	ldr	r0, [fp, #-76]
	bl	VP6_BuildScanOrder
.L118:
	ldr	r4, .L157+16
.L122:
	ldr	r6, [fp, #-68]
	add	r9, r4, #14
.L121:
	ldrb	r2, [r4, #1]!	@ zero_extendqisi2
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L119
	mov	r10, #0
	mov	r5, #6
.L120:
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r5
	subs	r5, r5, #1
	bcs	.L120
	mov	r10, r10, asl #1
	ands	r10, r10, #255
	moveq	r3, #1
	movne	r3, #0
	add	r3, r10, r3
	strb	r3, [r6]
.L119:
	cmp	r4, r9
	add	r6, r6, #1
	bne	.L121
	ldr	r3, .L157+20
	cmp	r3, r4
	ldr	r3, [fp, #-68]
	add	r3, r3, #14
	str	r3, [fp, #-68]
	bne	.L122
	mov	r3, #0
	str	r3, [fp, #-88]
.L131:
	ldr	r2, [fp, #-88]
	ldr	r1, .L157+24
	add	r3, r1, r2, lsl #1
	str	r2, [fp, #-84]
	add	r1, r2, #396
	sub	r3, r3, #1
	str	r1, [fp, #-92]
	str	r3, [fp, #-68]
.L133:
	ldr	r3, [fp, #-68]
	add	r3, r3, #66
	str	r3, [fp, #-80]
	ldr	r3, [fp, #-84]
	str	r3, [fp, #-72]
.L130:
	ldr	r3, [fp, #-72]
	sub	r4, fp, #56
	ldr	r6, [fp, #-68]
	add	r5, r3, #564
	ldr	r3, [fp, #-76]
	add	r5, r3, r5
.L127:
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L124
	mov	r10, #0
	mov	r9, #6
.L125:
	mov	r1, r7
	mov	r0, r8
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r9
	subs	r9, r9, #1
	bcs	.L125
	mov	r3, r10, asl #1
	ands	r3, r3, #255
	moveq	r2, #1
	movne	r2, #0
	add	r3, r3, r2
	uxtb	r3, r3
	strb	r3, [r4]
	strb	r3, [r5]
.L126:
	add	r4, r4, #1
	sub	r3, fp, #45
	cmp	r4, r3
	add	r5, r5, #1
	bne	.L127
	ldr	r2, [fp, #-72]
	ldr	r3, [fp, #-68]
	add	r2, r2, #11
	str	r2, [fp, #-72]
	ldr	r2, [fp, #-80]
	add	r3, r3, #11
	str	r3, [fp, #-68]
	cmp	r2, r3
	bne	.L130
	ldr	r2, [fp, #-80]
	ldr	r3, [fp, #-84]
	str	r2, [fp, #-68]
	add	r3, r3, #198
	ldr	r2, [fp, #-92]
	str	r3, [fp, #-84]
	cmp	r3, r2
	bne	.L133
	ldr	r3, [fp, #-88]
	add	r3, r3, #66
	str	r3, [fp, #-88]
	cmp	r3, #198
	bne	.L131
	ldr	r1, [fp, #-96]
	ldr	r0, [fp, #-76]
	bl	VP6_ConfigureContexts
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L124:
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	ldreqb	r3, [r4]	@ zero_extendqisi2
	streqb	r3, [r5]
	b	.L126
.L109:
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	ldreqb	r3, [r4]	@ zero_extendqisi2
	streqb	r3, [r5]
	b	.L111
.L158:
	.align	2
.L157:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+120
	.word	.LANCHOR0+144
	.word	.LANCHOR0+596
	.word	.LANCHOR0+171
	.word	.LANCHOR0+199
	.word	.LANCHOR0+200
	UNWIND(.fnend)
	.size	VP6_ConfigureEntropyDecoder, .-VP6_ConfigureEntropyDecoder
	.align	2
	.global	VP6_decodeModeDiff
	.type	VP6_decodeModeDiff, %function
VP6_decodeModeDiff:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r1, #76
	mov	r2, #205
	mov	r7, r0
	mov	r1, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	mov	r2, #171
	mov	r1, r5
	mov	r6, r0, asl #1
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool
	rsb	r6, r6, #1
	cmp	r0, #0
	beq	.L169
	mov	r2, #199
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	movne	r8, #0
	movne	r4, #6
	beq	.L170
.L166:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r8, r8, r0, asl r4
	subs	r4, r4, #1
	bcs	.L166
	mul	r0, r8, r6
	mov	r0, r0, asl #2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L170:
	mov	r2, #140
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L163
	mov	r0, r6, asl #4
	sub	r0, r0, r6, asl #2
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L169:
	mov	r1, r5
	mov	r0, r7
	mov	r2, #83
	bl	Vp6_Vfmw_DecodeBool
	rsb	r0, r0, #3
	mov	r0, r6, asl r0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L163:
	mov	r2, #125
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L164
	mov	r0, r6, asl #4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L164:
	mov	r1, r5
	mov	r0, r7
	mov	r2, #104
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	movne	r0, r6, asl #4
	addne	r0, r0, r6, lsl #2
	moveq	r0, r6, asl #5
	subeq	r0, r0, r6, asl #3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_decodeModeDiff, .-VP6_decodeModeDiff
	.align	2
	.global	VP6_DecodeModeProbs
	.type	VP6_DecodeModeProbs, %function
VP6_DecodeModeProbs:
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
	add	r9, r0, #412
	add	r9, r9, #1
	add	r7, r2, #76
	mov	r6, r2
	mov	r5, r1
	mov	r8, #0
	str	r0, [fp, #-48]
.L178:
	mov	r2, #174
	mov	r1, r7
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L172
	mov	r10, #0
	mov	r4, #3
.L173:
	mov	r1, r7
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r4
	subs	r4, r4, #1
	bcs	.L173
	mov	r2, r10, asl #4
	add	r0, r8, #20
	add	r1, r2, r10, lsl #2
	mov	r2, r9
	add	r3, r8, r1
	add	r0, r1, r0
	ldr	r1, .L192
	add	r3, r1, r3
	add	r0, r1, r0
.L174:
	ldrb	r1, [r3]	@ zero_extendqisi2
	add	r3, r3, #2
	strb	r1, [r2, #1]!
	ldrb	r1, [r3, #-1]	@ zero_extendqisi2
	cmp	r3, r0
	strb	r1, [r2, #-10]
	bne	.L174
.L172:
	mov	r2, #254
	mov	r1, r7
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L179
	sub	r10, r9, #412
	mov	r4, #0
	sub	r10, r10, #1
.L177:
	mov	r1, r6
	mov	r0, r5
	bl	VP6_decodeModeDiff
	ldrb	r3, [r10, #414]	@ zero_extendqisi2
	adds	r0, r3, r0
	movmi	r0, #0
	bmi	.L175
	cmp	r0, #255
	movge	r0, #255
	uxtb	r0, r0
.L175:
	strb	r0, [r10, #414]
	mov	r1, r6
	mov	r0, r5
	bl	VP6_decodeModeDiff
	ldrb	r3, [r10, #404]	@ zero_extendqisi2
	adds	r0, r3, r0
	movmi	r0, #0
	bmi	.L176
	cmp	r0, #255
	movge	r0, #255
	uxtb	r0, r0
.L176:
	add	r4, r4, #1
	strb	r0, [r10, #404]
	cmp	r4, #10
	add	r10, r10, #1
	bne	.L177
.L179:
	add	r8, r8, #320
	add	r9, r9, #20
	cmp	r8, #960
	bne	.L178
	mov	r1, r6
	ldr	r0, [fp, #-48]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VP6_BuildModeTree
.L193:
	.align	2
.L192:
	.word	.LANCHOR0+660
	UNWIND(.fnend)
	.size	VP6_DecodeModeProbs, .-VP6_DecodeModeProbs
	.align	2
	.global	VP6_ConfigureMvEntropyDecoder
	.type	VP6_ConfigureMvEntropyDecoder, %function
VP6_ConfigureMvEntropyDecoder:
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
	ldr	r7, .L232
	add	r4, r2, #76
	mov	r5, r1
	add	r8, r7, #34
	mov	r9, r0
	str	r0, [fp, #-52]
.L202:
	ldrb	r2, [r7]	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L198
	mov	r10, #0
	mov	r6, #6
.L196:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r6
	subs	r6, r6, #1
	bcs	.L196
	mov	r10, r10, asl #1
	ands	r10, r10, #255
	strneb	r10, [r9, #2]
	moveq	r3, #1
	streqb	r3, [r9, #2]
.L198:
	ldrb	r2, [r7, #1]	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L201
	mov	r10, #0
	mov	r6, #6
.L199:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r6
	subs	r6, r6, #1
	bcs	.L199
	mov	r10, r10, asl #1
	ands	r10, r10, #255
	strneb	r10, [r9]
	moveq	r3, #1
	streqb	r3, [r9]
.L201:
	add	r7, r7, #17
	add	r9, r9, #1
	cmp	r7, r8
	bne	.L202
	ldr	r3, .L232+4
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	add	r9, r3, #488
	add	r9, r9, #3
.L203:
	ldr	r8, [fp, #-48]
	sub	r7, r9, #7
.L209:
	ldrb	r2, [r8, #1]!	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L205
	mov	r10, #0
	mov	r6, #6
.L206:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r6
	subs	r6, r6, #1
	bcs	.L206
	mov	r10, r10, asl #1
	ands	r10, r10, #255
	strneb	r10, [r7]
	moveq	r3, #1
	streqb	r3, [r7]
.L205:
	add	r7, r7, #1
	cmp	r9, r7
	bne	.L209
	ldr	r3, [fp, #-48]
	add	r9, r9, #7
	ldr	r2, .L232+8
	add	r3, r3, #17
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L203
	sub	r3, r2, #27
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	add	r8, r3, #504
	add	r8, r8, #2
.L210:
	ldr	r9, [fp, #-48]
	sub	r7, r8, #8
.L216:
	ldrb	r2, [r9, #1]!	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L212
	mov	r10, #0
	mov	r6, #6
.L213:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r6
	subs	r6, r6, #1
	bcs	.L213
	mov	r3, r10, asl #1
	ands	r3, r3, #255
	moveq	r3, #1
	strb	r3, [r7]
.L212:
	add	r7, r7, #1
	cmp	r8, r7
	bne	.L216
	ldr	r3, [fp, #-48]
	add	r8, r8, #8
	ldr	r2, .L232+12
	add	r3, r3, #17
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L210
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L233:
	.align	2
.L232:
	.word	.LANCHOR0+1620
	.word	.LANCHOR0+1621
	.word	.LANCHOR0+1655
	.word	.LANCHOR0+1662
	UNWIND(.fnend)
	.size	VP6_ConfigureMvEntropyDecoder, .-VP6_ConfigureMvEntropyDecoder
	.align	2
	.global	VP6_BoolTreeToHuffCodes
	.type	VP6_BoolTreeToHuffCodes, %function
VP6_BoolTreeToHuffCodes:
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
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	smulbb	r3, r2, r3
	mov	r3, r3, lsr #8
	str	r3, [r1, #44]
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	ldrb	r2, [r0]	@ zero_extendqisi2
	rsb	r3, r3, #255
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	str	r3, [r1]
	ldrb	ip, [r0]	@ zero_extendqisi2
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	rsb	ip, ip, #255
	mul	r3, r3, ip
	mov	r3, r3, lsr #8
	str	r3, [r1, #4]
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	ldrb	r2, [r0, #3]	@ zero_extendqisi2
	rsb	r3, r3, #255
	ldrb	lr, [r0, #4]	@ zero_extendqisi2
	mul	r3, ip, r3
	mov	r3, r3, lsr #8
	mul	r2, r2, r3
	mov	ip, r2, lsr #8
	mul	r2, lr, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #8]
	ldrb	r2, [r0, #4]	@ zero_extendqisi2
	ldrb	lr, [r0, #5]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r2, r2, ip
	mov	r2, r2, lsr #8
	mul	ip, lr, r2
	mov	ip, ip, lsr #8
	str	ip, [r1, #12]
	ldrb	ip, [r0, #5]	@ zero_extendqisi2
	rsb	ip, ip, #255
	mul	r2, ip, r2
	mov	r2, r2, lsr #8
	str	r2, [r1, #16]
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	ldrb	r2, [r0, #6]	@ zero_extendqisi2
	rsb	ip, ip, #255
	ldrb	lr, [r0, #7]	@ zero_extendqisi2
	mul	r3, ip, r3
	mov	r3, r3, lsr #8
	mul	r2, r2, r3
	mov	ip, r2, lsr #8
	mul	r2, lr, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #20]
	ldrb	r2, [r0, #7]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r2, r2, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #24]
	ldrb	ip, [r0, #6]	@ zero_extendqisi2
	ldrb	r2, [r0, #8]	@ zero_extendqisi2
	rsb	ip, ip, #255
	ldrb	lr, [r0, #9]	@ zero_extendqisi2
	mul	r3, ip, r3
	mov	r3, r3, lsr #8
	mul	r2, r2, r3
	mov	ip, r2, lsr #8
	mul	r2, lr, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #28]
	ldrb	r2, [r0, #9]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r2, r2, ip
	mov	r2, r2, lsr #8
	str	r2, [r1, #32]
	ldrb	r2, [r0, #8]	@ zero_extendqisi2
	ldrb	ip, [r0, #10]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	mul	r2, ip, r3
	mov	r2, r2, lsr #8
	str	r2, [r1, #36]
	ldrb	r2, [r0, #10]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	str	r3, [r1, #40]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_BoolTreeToHuffCodes, .-VP6_BoolTreeToHuffCodes
	.align	2
	.global	VP6_ZerosBoolTreeToHuffCodes
	.type	VP6_ZerosBoolTreeToHuffCodes, %function
VP6_ZerosBoolTreeToHuffCodes:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	smulbb	r3, ip, r3
	mov	r3, r3, lsr #8
	mul	r2, r2, r3
	mov	r2, r2, lsr #8
	str	r2, [r1]
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r3, r3, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #4]
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	ldrb	ip, [r0]	@ zero_extendqisi2
	rsb	r3, r3, #255
	ldrb	lr, [r0, #3]	@ zero_extendqisi2
	mul	r3, ip, r3
	mov	r2, r3, lsr #8
	mul	r3, lr, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #8]
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	rsb	r3, r3, #255
	mul	r3, r3, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #12]
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	r4, [r0, #4]	@ zero_extendqisi2
	rsb	r3, r3, #255
	ldrb	ip, [r0, #5]	@ zero_extendqisi2
	ldrb	lr, [r0, #6]	@ zero_extendqisi2
	mul	r3, r4, r3
	mov	r3, r3, lsr #8
	mul	r3, ip, r3
	mov	r2, r3, lsr #8
	mul	r3, lr, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #16]
	ldrb	r3, [r0, #6]	@ zero_extendqisi2
	rsb	r3, r3, #255
	mul	r3, r3, r2
	mov	r3, r3, lsr #8
	str	r3, [r1, #20]
	ldrb	r3, [r0]	@ zero_extendqisi2
	ldrb	lr, [r0, #4]	@ zero_extendqisi2
	rsb	r3, r3, #255
	ldrb	r2, [r0, #5]	@ zero_extendqisi2
	ldrb	ip, [r0, #7]	@ zero_extendqisi2
	mul	r3, lr, r3
	rsb	r2, r2, #255
	mov	r3, r3, lsr #8
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	mul	r2, ip, r3
	mov	r2, r2, lsr #8
	str	r2, [r1, #24]
	ldrb	r2, [r0, #7]	@ zero_extendqisi2
	rsb	r2, r2, #255
	mul	r3, r2, r3
	mov	r3, r3, lsr #8
	str	r3, [r1, #28]
	ldrb	r3, [r0, #4]	@ zero_extendqisi2
	ldrb	r2, [r0]	@ zero_extendqisi2
	rsb	r0, r3, #255
	rsb	r3, r2, #255
	mul	r3, r3, r0
	mov	r3, r3, lsr #8
	str	r3, [r1, #32]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_ZerosBoolTreeToHuffCodes, .-VP6_ZerosBoolTreeToHuffCodes
	.align	2
	.global	VP6_InsertSorted
	.type	VP6_InsertSorted, %function
VP6_InsertSorted:
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
	ldr	r5, [r2]
	mov	r7, r1, asl #4
	cmn	r5, #1
	beq	.L237
	mov	r3, r5, asl #4
	sub	r7, r7, r1, asl #2
	sub	r3, r3, r5, asl #2
	add	r7, r0, r7
	add	r3, r0, r3
	ldr	r6, [r7, #8]
	ldr	ip, [r3, #8]
	cmp	r6, ip
	bls	.L238
	mov	r4, r5
	b	.L240
.L248:
	add	r3, r0, r3
	ldr	lr, [r3, #8]
	cmp	lr, r6
	bcs	.L247
	mov	r4, ip
.L240:
	ldr	ip, [r3, #4]
	cmn	ip, #1
	mov	r3, ip, asl #4
	sub	r3, r3, ip, asl #2
	bne	.L248
.L239:
	mov	r3, r4, asl #4
	sub	r4, r3, r4, asl #2
	add	r0, r0, r4
	str	r1, [r0, #4]
	str	ip, [r7, #4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L247:
	cmp	r5, ip
	bne	.L239
.L242:
	str	r1, [r2]
	str	ip, [r7, #4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L237:
	sub	r7, r7, r1, asl #2
	add	r7, r0, r7
.L238:
	mov	ip, r5
	b	.L242
	UNWIND(.fnend)
	.size	VP6_InsertSorted, .-VP6_InsertSorted
	.align	2
	.global	VP6_BuildHuffTree
	.type	VP6_BuildHuffTree, %function
VP6_BuildHuffTree:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 376
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #380)
	sub	sp, sp, #380
	subs	r10, r2, #0
	mov	r9, r0
	mov	r0, #0
	str	r0, [fp, #-408]
	beq	.L254
	sub	r6, fp, #404
	sub	r1, r1, #4
	mov	r5, #1
	mvn	r4, #0
	mov	ip, r6
.L253:
	mov	r2, r0, asl #4
	sub	r3, fp, #44
	sub	r2, r2, r0, asl #2
	ldr	lr, [r1, #4]!
	add	r2, r3, r2
	cmp	lr, #0
	ldrb	r3, [r2, #-360]	@ zero_extendqisi2
	moveq	lr, #1
	streq	r5, [r1]
	orr	r3, r3, #1
	bfi	r3, r0, #1, #4
	add	r0, r0, #1
	cmp	r0, r10
	bfc	r3, #5, #3
	strb	r3, [r2, #-360]
	stmib	ip, {r4, lr}
	add	ip, ip, #12
	bne	.L253
	cmp	r10, #1
	bls	.L254
	sub	r7, fp, #408
	mov	r4, #1
.L255:
	mov	r1, r4
	mov	r2, r7
	mov	r0, r6
	add	r4, r4, #1
	bl	VP6_InsertSorted
	cmp	r4, r10
	bne	.L255
	ldr	r2, [fp, #-408]
.L251:
	mov	r0, r2, asl #2
	mov	r2, r2, asl #4
	rsb	r3, r0, r2
	sub	r1, fp, #44
	add	r3, r1, r3
	ldr	r3, [r3, #-356]
	cmn	r3, #1
	beq	.L249
	mov	r5, r10, asl #4
	sub	r8, r10, #2
	sub	r6, fp, #404
	sub	r5, r5, r10, asl #2
	add	r8, r8, r10
	add	r9, r9, r10, lsl #1
	and	r8, r8, #15
	add	r5, r6, r5
	sub	r7, fp, #408
	mov	r4, r10
	str	r6, [fp, #-416]
.L257:
	mov	r1, r4, asl #4
	rsb	ip, r0, r2
	sub	r1, r1, r4, asl #2
	sub	r2, fp, #44
	add	r1, r2, r1
	mov	lr, r3, asl #4
	sub	r3, lr, r3, asl #2
	add	ip, r2, ip
	ldrb	r10, [r1, #-360]	@ zero_extendqisi2
	add	r3, r2, r3
	rsb	lr, r4, r8
	ldr	r0, [ip, #-352]
	and	r10, r10, #254
	ldrb	ip, [ip, #-360]	@ zero_extendqisi2
	bfi	r10, lr, #1, #4
	ldrb	lr, [r3, #-360]	@ zero_extendqisi2
	strb	r10, [r1, #-360]
	mvn	r6, #0
	ldr	r10, [r3, #-352]
	mov	r1, r4
	str	r6, [r5, #4]
	mov	r2, r7
	add	r0, r10, r0
	str	r0, [r5, #8]
	ldr	r3, [r3, #-356]
	add	r4, r4, #1
	ldr	r0, [fp, #-416]
	add	r5, r5, #12
	strb	lr, [r9, #-3]
	sub	r9, r9, #2
	strb	ip, [r9, #-2]
	str	r3, [fp, #-408]
	bl	VP6_InsertSorted
	ldr	r2, [fp, #-408]
	sub	r1, fp, #44
	mov	r0, r2, asl #2
	mov	r2, r2, asl #4
	rsb	r3, r0, r2
	add	r3, r1, r3
	ldr	r3, [r3, #-356]
	cmp	r3, r6
	bne	.L257
.L249:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L254:
	mov	r2, #0
	b	.L251
	UNWIND(.fnend)
	.size	VP6_BuildHuffTree, .-VP6_BuildHuffTree
	.align	2
	.global	VP6_BuildHuffLookupTable
	.type	VP6_BuildHuffLookupTable, %function
VP6_BuildHuffLookupTable:
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
	mov	r4, #0
.L266:
	mov	r2, #0
	mov	lr, r2
.L265:
	rsb	r3, lr, #5
	add	r5, r0, r2, lsl #1
	mov	r3, r4, asr r3
	add	ip, lr, #1
	tst	r3, #1
	mov	lr, ip
	ldrneb	r3, [r5, #1]	@ zero_extendqisi2
	ldreqb	r3, [r0, r2, asl #1]	@ zero_extendqisi2
	and	r5, r3, #1
	ubfx	r2, r3, #1, #4
	bfi	r3, r5, #0, #1
	bfi	r3, r2, #1, #4
	eor	r3, r3, #1
	cmp	ip, #5
	movhi	r3, #0
	andls	r3, r3, #1
	cmp	r3, #0
	bne	.L265
	ldrb	r3, [r1, r4]	@ zero_extendqisi2
	bfi	r3, r2, #4, #4
	bfi	r3, ip, #1, #3
	bfi	r3, r5, #0, #1
	strb	r3, [r1, r4]
	add	r4, r4, #1
	cmp	r4, #64
	bne	.L266
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6_BuildHuffLookupTable, .-VP6_BuildHuffLookupTable
	.align	2
	.global	VP6_BuildTreeTab
	.type	VP6_BuildTreeTab, %function
VP6_BuildTreeTab:
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
	add	r6, r0, #9088
	add	r7, r0, #9920
	add	r6, r6, #30
	add	r7, r7, #62
	mov	r1, #0
.L270:
	sub	r5, r6, #432
.L279:
	sub	r4, r5, #96
.L277:
	ldrb	lr, [r4, #-2]	@ zero_extendqisi2
	add	r3, r0, r1
	add	ip, r1, #1
	mov	r2, r4
	add	ip, r0, ip
	add	r1, r1, #2
	strb	lr, [r3, #1218]
	mov	r3, #0
	ldrb	lr, [r4, #-1]	@ zero_extendqisi2
	strb	lr, [ip, #1218]
	b	.L275
.L273:
	ldrb	lr, [r2]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #11
	addne	r1, r1, #2
	addeq	r1, r1, #6
	add	r2, r2, #2
	strb	lr, [ip, #1218]
	ldrb	lr, [r2, #-1]	@ zero_extendqisi2
	strb	lr, [ip, #1219]
.L275:
	add	r3, r3, #1
	add	ip, r0, r1
	cmp	r3, #12
	bne	.L273
	add	r4, r4, #24
	cmp	r4, r5
	bne	.L277
	add	r5, r4, #144
	cmp	r6, r5
	bne	.L279
	add	r6, r4, #576
	cmp	r6, r7
	bne	.L270
	add	r4, r0, #9408
	add	r5, r0, #9472
	add	r4, r4, #46
	add	r5, r5, #30
	mov	r1, #768
.L278:
	ldrb	lr, [r4, #-2]	@ zero_extendqisi2
	add	r3, r0, r1
	add	ip, r1, #1
	mov	r2, r4
	add	ip, r0, ip
	add	r1, r1, #2
	strb	lr, [r3, #1218]
	mov	r3, #0
	ldrb	lr, [r4, #-1]	@ zero_extendqisi2
	strb	lr, [ip, #1218]
	b	.L284
.L282:
	ldrb	lr, [r2]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #11
	addne	r1, r1, #2
	addeq	r1, r1, #6
	add	r2, r2, #2
	strb	lr, [ip, #1218]
	ldrb	lr, [r2, #-1]	@ zero_extendqisi2
	strb	lr, [ip, #1219]
.L284:
	add	r3, r3, #1
	add	ip, r0, r1
	cmp	r3, #12
	bne	.L282
	add	r4, r4, #24
	cmp	r4, r5
	bne	.L278
	add	r4, r0, #8512
	add	r5, r0, #8576
	add	r4, r4, #20
	add	r5, r5, #12
	mov	ip, #832
.L283:
	mov	r1, r4
	mov	r3, #0
.L289:
	ldrb	lr, [r1]	@ zero_extendqisi2
	add	r2, r0, ip
	cmp	r3, #5
	cmpne	r3, #11
	addeq	ip, ip, #6
	strb	lr, [r2, #1218]
	ldrb	lr, [r1, #1]	@ zero_extendqisi2
	strb	lr, [r2, #1219]
	beq	.L286
	cmp	r3, #13
	beq	.L294
	add	ip, ip, #2
.L286:
	add	r3, r3, #1
	add	r1, r1, #2
	cmp	r3, #14
	bne	.L289
.L288:
	add	r4, r4, #28
	cmp	r4, r5
	bne	.L283
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L294:
	add	ip, ip, #30
	b	.L288
	UNWIND(.fnend)
	.size	VP6_BuildTreeTab, .-VP6_BuildTreeTab
	.align	2
	.global	VP6_ConvertBoolToHuff
	.type	VP6_ConvertBoolToHuff, %function
VP6_ConvertBoolToHuff:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
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
	add	r6, r0, #6592
	mov	r8, r0
	add	r6, r6, #4
	ldr	r1, .L302
	mov	r0, #22
	add	r5, r8, #9408
	bl	dprint_vfmw
	add	r5, r5, #44
	add	r0, r8, #512
	mov	r1, r6
	add	r0, r0, #2
	bl	VP6_BoolTreeToHuffCodes
	mov	r2, #12
	mov	r1, r6
	mov	r0, r5
	bl	VP6_BuildHuffTree
	add	r4, r8, #6592
	add	r1, r8, #9472
	mov	r0, r5
	add	r4, r4, #52
	add	r1, r1, #28
	add	r6, r8, #9472
	bl	VP6_BuildHuffLookupTable
	add	r6, r6, #4
	add	r0, r8, #524
	mov	r1, r4
	add	r0, r0, #1
	bl	VP6_BoolTreeToHuffCodes
	add	r5, r8, #6656
	mov	r2, #12
	mov	r1, r4
	mov	r0, r6
	add	r5, r5, #36
	bl	VP6_BuildHuffTree
	add	r4, r8, #8512
	add	r1, r8, #9536
	mov	r0, r6
	add	r4, r4, #20
	add	r1, r1, #28
	bl	VP6_BuildHuffLookupTable
	mov	r1, r5
	add	r0, r8, #536
	bl	VP6_ZerosBoolTreeToHuffCodes
	mov	r2, #9
	mov	r1, r5
	mov	r0, r4
	bl	VP6_BuildHuffTree
	add	r5, r8, #6720
	add	r1, r8, #11904
	mov	r0, r4
	add	r5, r5, #28
	add	r1, r1, #28
	add	r4, r8, #8512
	bl	VP6_BuildHuffLookupTable
	add	r4, r4, #48
	add	r0, r8, #548
	mov	r1, r5
	add	r0, r0, #2
	bl	VP6_ZerosBoolTreeToHuffCodes
	mov	r1, r5
	mov	r0, r4
	mov	r2, #9
	bl	VP6_BuildHuffTree
	add	r3, r8, #760
	mov	r0, r4
	add	r1, r8, #11968
	mov	r4, r3
	add	r3, r8, #6784
	add	r1, r1, #28
	mov	r5, r3
	add	r3, r8, #8576
	mov	r6, r3
	add	r3, r8, #9600
	mov	r7, r3
	add	r3, r8, #1152
	mov	r9, r3
	bl	VP6_BuildHuffLookupTable
	add	r3, r4, #2
	str	r8, [fp, #-72]
	str	r3, [fp, #-52]
	add	r3, r5, #20
	str	r3, [fp, #-60]
	add	r3, r6, #12
	str	r3, [fp, #-64]
	add	r3, r7, #28
	str	r3, [fp, #-56]
	add	r3, r9, #6
	str	r3, [fp, #-68]
.L296:
	ldr	r3, [fp, #-52]
	ldr	r10, [fp, #-56]
	sub	r4, r3, #198
	ldr	r9, [fp, #-64]
	ldr	r3, [fp, #-60]
	str	r3, [fp, #-48]
.L300:
	ldr	r8, [fp, #-48]
	add	r7, r4, #66
	mov	r6, r10
	mov	r5, r9
.L297:
	mov	r1, r8
	mov	r0, r4
	bl	VP6_BoolTreeToHuffCodes
	mov	r1, r8
	mov	r0, r5
	mov	r2, #12
	bl	VP6_BuildHuffTree
	add	r4, r4, #11
	mov	r1, r6
	mov	r0, r5
	bl	VP6_BuildHuffLookupTable
	cmp	r4, r7
	add	r8, r8, #48
	add	r6, r6, #64
	add	r5, r5, #24
	bne	.L297
	ldr	r3, [fp, #-52]
	add	r9, r9, #144
	add	r10, r10, #384
	cmp	r3, r4
	ldr	r3, [fp, #-48]
	add	r3, r3, #288
	str	r3, [fp, #-48]
	bne	.L300
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-52]
	add	r2, r2, #864
	str	r2, [fp, #-60]
	ldr	r2, [fp, #-68]
	add	r3, r3, #198
	str	r3, [fp, #-52]
	cmp	r3, r2
	ldr	r3, [fp, #-64]
	add	r3, r3, #432
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-56]
	add	r3, r3, #1152
	str	r3, [fp, #-56]
	bne	.L296
	ldr	r8, [fp, #-72]
	mov	r0, r8
	bl	VP6_BuildTreeTab
	ldr	r1, .L302+4
	mov	r0, #22
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L303:
	.align	2
.L302:
	.word	.LC9
	.word	.LC10
	UNWIND(.fnend)
	.size	VP6_ConvertBoolToHuff, .-VP6_ConvertBoolToHuff
	.align	2
	.global	VP6_IntraFrmHeader
	.type	VP6_IntraFrmHeader, %function
VP6_IntraFrmHeader:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r5, r1
	mov	r4, r0
	ldr	r1, .L343
	mov	r0, #22
	add	r8, r4, #8192
	bl	dprint_vfmw
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	mov	r1, #2
	uxtb	r3, r0
	mov	r0, r5
	str	r3, [r8, #4084]
	bl	BsGet
	ldr	r2, [r8, #4084]
	cmp	r2, #8
	uxtb	r0, r0
	str	r0, [r8, #4088]
	bhi	.L339
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r6, r0
	cmp	r6, #0
	bne	.L340
	ldrb	r3, [r8, #4070]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L308
	mov	r1, #16
	mov	r0, r5
	bl	BsGet
	add	r9, r4, #12288
	mov	r2, #255
	mov	r3, #8
	str	r6, [r9, #48]
	mov	r1, #24
	str	r2, [r9, #52]
	str	r3, [r9, #60]
	str	r0, [r9, #28]
	mov	r0, r5
	bl	BsGet
	str	r0, [r9, #56]
.L309:
	add	r4, r4, #12288
	mov	r10, #0
	add	r4, r4, #48
	mov	r6, #7
.L310:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r10, r10, r0, asl r6
	subs	r6, r6, #1
	bcs	.L310
	mov	r7, #0
	mov	r6, #7
	uxtb	r10, r10
	str	r10, [r9]
.L311:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L311
	ldr	r10, [r9]
	uxtb	r3, r7
	mov	r6, #7
	mov	r7, #0
	str	r3, [r9, #4]
	mov	r3, r3, asl #1
	mov	r10, r10, asl #1
	str	r3, [fp, #-48]
	str	r3, [r9, #12]
	str	r10, [r9, #8]
.L312:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L312
	uxtb	r2, r7
	mov	r6, #7
	mov	r7, #0
	mov	r2, r2, asl #1
	str	r2, [r9, #16]
.L313:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L313
	uxtb	r3, r7
	mov	r1, r4
	mov	r0, r5
	mov	r3, r3, asl #1
	str	r3, [r9, #20]
	bl	Vp6_Vfmw_DecodeBool128
	mov	r1, r4
	mov	r6, r0
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	ldr	r3, [r8, #3872]
	ldr	r2, [r8, #3868]
	cmp	r10, r3
	orr	r0, r0, r6, asl #1
	strb	r0, [r8, #4071]
	bne	.L315
	ldr	r1, [fp, #-48]
	cmp	r1, r2
	beq	.L316
.L315:
	ldr	r1, [fp, #-48]
	mov	r0, #22
	str	r10, [sp, #4]
	str	r1, [sp]
	ldr	r1, .L343+4
	bl	dprint_vfmw
.L316:
	ldr	r3, [r8, #4088]
	ldr	r2, [fp, #-48]
	cmp	r3, #0
	str	r10, [r8, #3872]
	str	r2, [r8, #3868]
	moveq	r2, #14
	streqb	r2, [r8, #4074]
	streq	r3, [r9, #32]
	bne	.L341
.L325:
	ldr	r1, .L343+8
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L339:
	ldr	r1, .L343+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L308:
	add	r9, r4, #12288
	mov	ip, #255
	mov	r2, #8
	mov	r1, #24
	str	r3, [r9, #48]
	mov	r0, r5
	str	ip, [r9, #52]
	str	r2, [r9, #60]
	bl	BsGet
	str	r0, [r9, #56]
	b	.L309
.L340:
	ldr	r1, .L343+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L341:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	beq	.L318
	mov	r7, #0
	mov	r6, #4
	mov	r3, #2
	str	r3, [r9, #32]
.L319:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L319
	ldr	r3, [r8, #4084]
	mov	r9, #0
	mov	r6, #2
	cmp	r3, #7
	movhi	r3, r9
	movls	r3, #5
	mov	r7, r7, asl r3
	strb	r7, [r8, #4072]
.L321:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r9, r9, r0, asl r6
	subs	r6, r6, #1
	bcs	.L321
	strb	r9, [r8, #4073]
.L322:
	ldr	r3, [r8, #4084]
	cmp	r3, #7
	bls	.L342
	mov	r7, #0
	mov	r6, #3
.L324:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	orr	r7, r7, r0, asl r6
	subs	r6, r6, #1
	bcs	.L324
	strb	r7, [r8, #4074]
	b	.L325
.L342:
	mov	r3, #16
	strb	r3, [r8, #4074]
	b	.L325
.L318:
	mov	r1, r4
	mov	r0, r5
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	streq	r0, [r9, #32]
	movne	r3, #1
	strne	r3, [r9, #32]
	b	.L322
.L344:
	.align	2
.L343:
	.word	.LC11
	.word	.LC14
	.word	.LC15
	.word	.LC12
	.word	.LC13
	UNWIND(.fnend)
	.size	VP6_IntraFrmHeader, .-VP6_IntraFrmHeader
	.align	2
	.global	VP6_InterFrmHeader
	.type	VP6_InterFrmHeader, %function
VP6_InterFrmHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #8192
	mov	r5, r0
	mov	r7, r1
	ldr	r2, [r4, #3936]
	cmp	r2, #0
	beq	.L367
	ldrb	r3, [r4, #4070]	@ zero_extendqisi2
	ldr	r1, [r4, #3940]
	cmp	r3, #0
	str	r2, [r4, #4084]
	str	r1, [r4, #4088]
	bne	.L368
	add	r6, r0, #12288
	mov	ip, #255
	mov	r2, #8
	mov	r1, #24
	str	r3, [r6, #48]
	mov	r0, r7
	str	ip, [r6, #52]
	str	r2, [r6, #60]
	bl	BsGet
	str	r0, [r6, #56]
.L349:
	add	r5, r5, #12288
	mov	r0, r7
	add	r5, r5, #48
	mov	r1, r5
	bl	Vp6_Vfmw_DecodeBool128
	str	r0, [r6, #36]
	ldr	r3, [r4, #3940]
	str	r0, [r4, #3892]
	cmp	r3, #0
	bne	.L369
	mov	r2, #14
	mov	r0, #1
	strb	r2, [r4, #4074]
	str	r3, [r6, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L368:
	mov	r1, #16
	mov	r0, r7
	bl	BsGet
	add	r6, r5, #12288
	mov	r3, #0
	mov	r2, #255
	str	r3, [r6, #48]
	mov	r1, #24
	mov	r3, #8
	str	r2, [r6, #52]
	str	r3, [r6, #60]
	str	r0, [r6, #28]
	mov	r0, r7
	bl	BsGet
	str	r0, [r6, #56]
	b	.L349
.L369:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r6, #40]
	bne	.L370
.L351:
	ldr	r3, [r4, #3936]
	cmp	r3, #7
	bhi	.L371
	mov	r3, #16
	mov	r0, #1
	strb	r3, [r4, #4074]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L371:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	bne	.L372
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L370:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r0, r0, r8, asl #1
	str	r0, [r6, #40]
	b	.L351
.L372:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	beq	.L353
	mov	r9, #0
	mov	r8, #4
	mov	r3, #2
	str	r3, [r6, #32]
.L354:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r9, r9, r0, asl r8
	subs	r8, r8, #1
	bcs	.L354
	mov	r8, #0
	mov	r6, #2
	strb	r9, [r4, #4072]
.L355:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r8, r8, r0, asl r6
	subs	r6, r6, #1
	bcs	.L355
	strb	r8, [r4, #4073]
.L356:
	mov	r8, #0
	mov	r6, #3
.L358:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	orr	r8, r8, r0, asl r6
	subs	r6, r6, #1
	bcs	.L358
	strb	r8, [r4, #4074]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L367:
	ldr	r3, [r4, #4084]
	mov	r0, #1
	ldr	r1, .L373
	bl	dprint_vfmw
	mvn	r0, #87
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L353:
	mov	r1, r5
	mov	r0, r7
	bl	Vp6_Vfmw_DecodeBool128
	cmp	r0, #0
	streq	r0, [r6, #32]
	movne	r3, #1
	strne	r3, [r6, #32]
	b	.L356
.L374:
	.align	2
.L373:
	.word	.LC16
	UNWIND(.fnend)
	.size	VP6_InterFrmHeader, .-VP6_InterFrmHeader
	.align	2
	.global	VP6_GetPictureHeader
	.type	VP6_GetPictureHeader, %function
VP6_GetPictureHeader:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r0
	mov	r6, r1
	beq	.L381
	ldr	r1, .L384
	mov	r0, #22
	bl	dprint_vfmw
	mov	r1, #1
	mov	r0, r6
	add	r4, r7, #8192
	bl	BsGet
	mov	r1, #6
	uxtb	r3, r0
	mov	r0, r6
	str	r3, [r4, #4092]
	strb	r3, [r4, #3888]
	bl	BsGet
	ldr	ip, .L384+4
	ldr	r1, .L384+8
	add	r2, r7, #12224
	add	r5, ip, #128
	uxtb	r3, r0
	strb	r0, [r4, #4068]
	add	r1, r1, r3
	mov	r0, r6
	mov	r3, r3, asl #1
	ldrb	lr, [r1, #1656]	@ zero_extendqisi2
	mov	r1, #1
	ldrh	ip, [ip, r3]
	ldrh	r3, [r5, r3]
	strb	lr, [r4, #4069]
	strh	ip, [r2, #48]	@ movhi
	strh	r3, [r2, #50]	@ movhi
	bl	BsGet
	ldr	r3, [r4, #4092]
	mov	r1, r6
	cmp	r3, #0
	strb	r0, [r4, #4070]
	mov	r0, r7
	beq	.L382
	bl	VP6_InterFrmHeader
	mov	r5, r0
	cmp	r5, #1
	beq	.L383
.L380:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L382:
	bl	VP6_IntraFrmHeader
	mov	r5, r0
	cmp	r5, #1
	bne	.L380
.L383:
	add	r1, r7, #12288
	mov	r0, r6
	add	r1, r1, #48
	add	r7, r7, #12288
	bl	Vp6_Vfmw_DecodeBool128
	ldr	r1, .L384+12
	str	r0, [r7, #44]
	mov	r0, #22
	ldrb	r3, [r4, #4068]	@ zero_extendqisi2
	str	r3, [r7, #24]
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L381:
	ldr	r1, .L384+16
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L385:
	.align	2
.L384:
	.word	.LC18
	.word	.LANCHOR0+1720
	.word	.LANCHOR0
	.word	.LC19
	.word	.LC17
	UNWIND(.fnend)
	.size	VP6_GetPictureHeader, .-VP6_GetPictureHeader
	.align	2
	.global	VP6DEC_Init
	.type	VP6DEC_Init, %function
VP6DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	cmpne	r0, #0
	mov	r8, r1
	mov	r4, r0
	moveq	r6, #1
	movne	r6, #0
	beq	.L390
	add	r5, r0, #12288
	ldr	r7, .L392
	mov	r2, #13056
	mov	r1, r6
	ldr	r9, [r5, #744]
	ldr	r3, [r7, #48]
	blx	r3
	add	r0, r4, #12672
	add	r0, r0, #16
	str	r9, [r5, #744]
	bl	ResetVoQueue
	str	r8, [r4]
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r5, #752]
	beq	.L391
	ldr	r3, [r7, #48]
	movw	r2, #12408
	mov	r1, r6
	add	r0, r4, #244
	blx	r3
	str	r6, [r5, #32]
	mov	r3, #1024
	str	r3, [r5, #60]
	ldr	r3, [r4]
	mov	r0, #22
	ldr	r1, .L392+4
	ldr	r3, [r3, #8]
	str	r3, [r5, #24]
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L390:
	movw	r2, #2005
	ldr	r1, .L392+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L391:
	mov	r0, r6
	ldr	r1, .L392+12
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L393:
	.align	2
.L392:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC21
	.word	.LC8
	.word	.LC20
	UNWIND(.fnend)
	.size	VP6DEC_Init, .-VP6DEC_Init
	.align	2
	.global	VP6DEC_Destroy
	.type	VP6DEC_Destroy, %function
VP6DEC_Destroy:
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
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP6DEC_Destroy, .-VP6DEC_Destroy
	.align	2
	.global	VP6_DecodeDecide
	.type	VP6_DecodeDecide, %function
VP6_DecodeDecide:
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
	add	r4, r0, #12288
	mov	r6, r0
	ldr	r5, [r4, #32]
	cmp	r5, #0
	beq	.L421
	ldr	r3, [r4, #24]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r3, [r0]
	ldr	r2, [r3, #8]
	bls	.L422
.L399:
	str	r2, [r4, #24]
	cmp	r2, #4
	ldrls	pc, [pc, r2, asl #2]
	b	.L404
.L405:
	.word	.L403
	.word	.L403
	.word	.L400
	.word	.L402
	.word	.L403
.L423:
	ldr	r1, .L425
	mov	r0, #18
	bl	dprint_vfmw
.L402:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L422:
	cmp	r2, #4
	cmpne	r2, #1
	bhi	.L399
	ldr	r1, .L425+4
	mov	r0, #2
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #48]
	mov	r5, #0
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #48]
	str	r5, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_GetNullLogicFs
	str	r5, [r4, #28]
	str	r0, [r4, #52]
	str	r0, [r4, #48]
	ldr	r3, [r6]
	ldr	r2, [r3, #8]
	b	.L399
.L421:
	ldr	r1, .L425+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L400:
	ldrb	r2, [r4, #36]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L423
.L401:
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L424
	ldrb	r3, [r4, #36]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L410
	ldr	r3, [r6]
	ldr	r2, [r5, #152]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L410
	ldr	r1, .L425+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L403:
	ldrb	r3, [r4, #36]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L401
	ldr	r3, [r4, #28]
	cmp	r3, #0
	bne	.L401
	ldr	r2, .L425+16
	mov	r0, #18
	ldr	r1, .L425+20
	bl	dprint_vfmw
	b	.L402
.L404:
	ldr	r1, .L425+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L410:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L424:
	movw	r3, #2143
	ldr	r2, .L425+28
	ldr	r1, .L425+32
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L426:
	.align	2
.L425:
	.word	.LC24
	.word	.LC23
	.word	.LC22
	.word	.LC29
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LANCHOR0+1976
	.word	.LC28
	UNWIND(.fnend)
	.size	VP6_DecodeDecide, .-VP6_DecodeDecide
	.align	2
	.global	VP6_Set_DecParam
	.type	VP6_Set_DecParam, %function
VP6_Set_DecParam:
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
	add	r5, r0, #12288
	mov	r4, r0
	add	r7, r0, #8
	ldr	r8, [r0, #228]
	ldrb	r3, [r5, #36]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L452
	ldr	r3, .L453
	mov	r2, #220
	mov	r1, #0
	mov	r0, r7
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r5, #240]
	mov	r2, #0
	strb	r2, [r4, #9]
	str	r3, [r4, #72]
	ldrb	r3, [r5, #216]	@ zero_extendqisi2
	str	r3, [r4, #76]
	ldrb	r3, [r5, #218]	@ zero_extendqisi2
	str	r3, [r4, #80]
	ldr	r3, [r5, #288]
	str	r3, [r4, #84]
	ldr	r3, [r5, #276]
	str	r3, [r4, #96]
	ldrb	r3, [r5, #220]	@ zero_extendqisi2
	str	r3, [r4, #100]
	ldrb	r3, [r5, #221]	@ zero_extendqisi2
	str	r3, [r4, #104]
	ldrb	r3, [r5, #222]	@ zero_extendqisi2
	str	r3, [r4, #108]
	ldr	r3, [r5, #284]
	str	r3, [r4, #120]
	ldrb	r3, [r5, #217]	@ zero_extendqisi2
	strb	r3, [r4, #8]
	ldrh	r3, [r5, #228]
	str	r3, [r4, #88]
	ldrh	r3, [r5, #230]
	str	r3, [r4, #92]
	ldr	r3, [r5, #236]
	str	r3, [r4, #116]
	ldr	r3, [r5, #232]
	str	r3, [r4, #112]
	ldr	r3, [r5, #248]
	strh	r3, [r4, #62]	@ movhi
	ldr	r3, [r5, #244]
	strh	r3, [r4, #64]	@ movhi
	ldr	r1, [r5, #44]
	ldr	r0, [r5, #752]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #52]
	mov	r6, r0
	ldr	r0, [r5, #752]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #48]
	mov	r9, r0
	ldr	r0, [r5, #752]
	bl	FSP_GetLogicFs
	cmp	r6, #0
	cmpne	r9, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L436
	ldr	r3, [r6, #28]
	cmp	r3, #0
	beq	.L437
	ldr	r3, [r3, #8]
	str	r3, [r4, #184]
	ldr	r3, [r6, #8]
	str	r3, [r4, #196]
	ldr	r3, [r0, #28]
	cmp	r3, #0
	ldreq	r3, [r6, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #188]
	ldr	r3, [r9, #28]
	add	r9, r4, #12608
	add	r9, r9, #44
	cmp	r3, #0
	mov	r0, r9
	ldreq	r3, [r6, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #192]
	ldr	r3, [r5, #60]
	str	r3, [r4, #200]
	ldr	r3, [r5, #64]
	str	r3, [r4, #204]
	ldr	r3, [r6, #28]
	ldr	r3, [r3, #60]
	str	r3, [r4, #208]
	ldr	r3, [r6, #28]
	ldr	r3, [r3, #44]
	str	r3, [r4, #212]
	ldr	r3, [r6, #28]
	ldr	r3, [r3, #48]
	str	r3, [r4, #216]
	ldr	r3, [r5, #300]
	str	r3, [r4, #172]
	ldr	r3, [r5, #296]
	str	r3, [r4, #176]
	ldr	r3, [r5, #304]
	str	r3, [r4, #180]
	ldr	r6, [r8]
	bl	BsPos
	cmp	r0, #0
	add	r3, r0, #7
	movlt	r0, r3
	add	r6, r6, r0, asr #3
	mov	r0, r6
	bl	MEM_Vir2Phy
	bic	r3, r0, #15
	mov	r0, r6
	sub	r3, r3, #16
	str	r3, [r4, #68]
	bl	MEM_Vir2Phy
	ldrb	r6, [r5, #218]	@ zero_extendqisi2
	cmp	r6, #0
	and	r0, r0, #15
	mov	r0, r0, asl #3
	bne	.L442
	ldr	r3, [r5, #236]
	cmp	r3, #0
	bne	.L443
.L442:
	mov	r3, #16
	str	r0, [r4, #128]
	str	r3, [r4, #132]
	mov	r0, r9
	ldr	r9, [r5, #272]
	bl	BsPos
	mov	r6, #0
	str	r6, [r4, #144]
	str	r6, [r4, #140]
	mov	r9, r9, asl #3
	str	r6, [r4, #136]
	rsb	r0, r0, r9
	str	r0, [r4, #124]
	ldr	r3, [r8]
	ldr	r10, [r5, #272]
	add	r10, r3, r10
	mov	r0, r10
	bl	MEM_Vir2Phy
	mov	r9, r0
	mov	r0, r10
	bl	MEM_Vir2Phy
	and	r9, r9, #15
	ldr	r3, [r4, #68]
	mov	r9, r9, asl #3
	str	r9, [r4, #152]
	bic	r0, r0, #15
	rsb	r0, r3, r0
	str	r0, [r4, #156]
	ldr	r3, [r5, #272]
	ldr	r2, [r8, #8]
	str	r6, [r4, #168]
	mov	r3, r3, asl #3
	str	r6, [r4, #164]
	rsb	r3, r3, r2, lsl #3
	str	r6, [r4, #160]
	str	r3, [r4, #148]
.L444:
	ldr	lr, [r4]
	add	r2, r4, #5120
	add	r3, r4, #4416
	add	ip, r4, #4992
	add	r0, r4, #4288
	add	r1, r4, #3312
	add	r2, r2, #54
	add	r3, r3, #22
	str	r2, [r4, #52]
	add	r2, r4, #3376
	str	r3, [r4, #40]
	add	r3, r4, #3248
	add	ip, ip, #54
	add	r0, r0, #54
	str	ip, [r4, #48]
	add	r1, r1, #6
	str	r0, [r4, #36]
	add	ip, r4, #2544
	str	r1, [r4, #28]
	add	r0, r4, #2480
	add	r2, r2, #6
	add	r1, r4, #3184
	str	r2, [r4, #32]
	add	r3, r3, #6
	add	r2, r4, #6656
	str	r3, [r4, #24]
	add	r3, r4, #4992
	add	ip, ip, #6
	add	r0, r0, #6
	str	ip, [r4, #16]
	str	r0, [r4, #12]
	add	r1, r1, #6
	add	r2, r2, #54
	str	r1, [r4, #20]
	str	r2, [r4, #56]
	add	r3, r3, #22
	str	r3, [r4, #44]
	mov	r0, #1
	ldr	r3, [lr, #600]
	str	r3, [r4, #220]
	ldr	r3, [lr, #652]
	str	r7, [r4, #4]
	str	r3, [r4, #224]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L436:
	ldr	r1, .L453+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L452:
	str	r3, [r0, #72]
	mov	r3, #1
	strb	r3, [r0, #9]
	ldr	r1, [r5, #44]
	ldr	r0, [r5, #752]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #52]
	mov	r6, r0
	ldr	r0, [r5, #752]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #48]
	mov	r8, r0
	ldr	r0, [r5, #752]
	bl	FSP_GetLogicFs
	cmp	r6, #0
	cmpne	r8, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L436
	ldr	r3, [r6, #28]
	cmp	r3, #0
	beq	.L437
	ldr	r3, [r3, #8]
	str	r3, [r4, #184]
	ldr	r3, [r6, #8]
	str	r3, [r4, #196]
	ldr	r3, [r0, #28]
	mov	r0, #1
	cmp	r3, #0
	ldreq	r3, [r6, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #188]
	ldr	r3, [r8, #28]
	cmp	r3, #0
	ldreq	r3, [r6, #28]
	ldr	r3, [r3, #8]
	str	r7, [r4, #4]
	str	r3, [r4, #192]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L443:
	str	r0, [r4, #128]
	mov	r3, #16
	mov	r0, r9
	str	r3, [r4, #132]
	ldr	r5, [r8, #8]
	bl	BsPos
	str	r6, [r4, #144]
	str	r6, [r4, #140]
	mov	r5, r5, asl #3
	str	r6, [r4, #136]
	str	r6, [r4, #156]
	str	r6, [r4, #152]
	str	r6, [r4, #148]
	str	r6, [r4, #168]
	str	r6, [r4, #164]
	str	r6, [r4, #160]
	rsb	r0, r0, r5
	str	r0, [r4, #124]
	b	.L444
.L437:
	ldr	r1, .L453+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L454:
	.align	2
.L453:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC30
	.word	.LC31
	UNWIND(.fnend)
	.size	VP6_Set_DecParam, .-VP6_Set_DecParam
	.align	2
	.global	VP6_CfgTable
	.type	VP6_CfgTable, %function
VP6_CfgTable:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r6, .L480
	add	r4, r0, #2240
	add	r8, r0, #2288
	add	r4, r4, #2
	add	r8, r8, #2
	add	r5, r0, #4
	mov	r7, r0
	mov	r3, #0
	str	r1, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
.L456:
	mov	r1, r5
	mov	r0, r4
	ldr	r3, [r6, #52]
	mov	r2, #10
	add	r4, r4, #16
	blx	r3
	cmp	r4, r8
	add	r5, r5, #10
	bne	.L456
	add	r3, r7, #2944
	add	r4, r7, #2304
	add	r3, r3, #2
	add	r4, r4, #2
	add	r9, r7, #44
	str	r7, [fp, #-68]
	mov	r8, r3
.L457:
	add	r5, r4, #160
	mov	r7, r9
.L458:
	mov	r1, r7
	mov	r0, r4
	ldr	r3, [r6, #52]
	mov	r2, #9
	add	r4, r4, #16
	blx	r3
	cmp	r4, r5
	add	r7, r7, #9
	ldr	r10, .L480
	bne	.L458
	cmp	r4, r8
	add	r9, r9, #90
	bne	.L457
	ldr	r7, [fp, #-68]
	mov	r1, #0
	ldr	r8, [r10, #48]
	mov	r2, #16
	sub	r0, fp, #60
	mov	r5, r1
	blx	r8
	ldrb	ip, [r7]	@ zero_extendqisi2
	ldrb	r2, [r7, #484]	@ zero_extendqisi2
	mov	r0, r4
	ldrb	lr, [r7, #485]	@ zero_extendqisi2
	sub	r1, fp, #60
	strb	ip, [fp, #-60]
	ldrb	ip, [r7, #486]	@ zero_extendqisi2
	ldrb	r8, [r7, #2]	@ zero_extendqisi2
	ldrb	r4, [r7, #487]	@ zero_extendqisi2
	strb	r2, [fp, #-58]
	strb	lr, [fp, #-57]
	ldrb	r2, [r7, #488]	@ zero_extendqisi2
	ldrb	lr, [r7, #489]	@ zero_extendqisi2
	strb	ip, [fp, #-56]
	ldrb	ip, [r7, #490]	@ zero_extendqisi2
	strb	lr, [fp, #-53]
	strb	r8, [fp, #-59]
	strb	ip, [fp, #-52]
	strb	r4, [fp, #-55]
	strb	r2, [fp, #-54]
	mov	r2, #16
	ldr	r4, [r10, #52]
	blx	r4
	mov	r1, r5
	ldr	r4, [r10, #48]
	mov	r2, #16
	sub	r0, fp, #60
	blx	r4
	ldrb	ip, [r7]	@ zero_extendqisi2
	ldrb	r4, [r7, #498]	@ zero_extendqisi2
	add	r0, r7, #2960
	ldrb	r2, [r7, #499]	@ zero_extendqisi2
	sub	r1, fp, #60
	ldrb	lr, [r7, #500]	@ zero_extendqisi2
	add	r0, r0, #2
	strb	ip, [fp, #-60]
	ldrb	ip, [r7, #501]	@ zero_extendqisi2
	strb	r4, [fp, #-59]
	strb	r2, [fp, #-58]
	ldrb	r4, [r7, #502]	@ zero_extendqisi2
	ldrb	r2, [r7, #503]	@ zero_extendqisi2
	strb	lr, [fp, #-57]
	strb	ip, [fp, #-56]
	ldrb	lr, [r7, #504]	@ zero_extendqisi2
	ldrb	ip, [r7, #505]	@ zero_extendqisi2
	strb	r4, [fp, #-55]
	strb	lr, [fp, #-53]
	strb	ip, [fp, #-52]
	strb	r2, [fp, #-54]
	mov	r2, #16
	strb	r5, [fp, #-51]
	strb	r5, [fp, #-50]
	ldr	r4, [r10, #52]
	blx	r4
	mov	r1, r5
	ldr	r4, [r10, #48]
	mov	r2, #16
	sub	r0, fp, #60
	blx	r4
	ldrb	ip, [r7, #1]	@ zero_extendqisi2
	ldrb	r4, [r7, #3]	@ zero_extendqisi2
	add	r0, r7, #2976
	ldrb	r2, [r7, #491]	@ zero_extendqisi2
	sub	r1, fp, #60
	ldrb	lr, [r7, #492]	@ zero_extendqisi2
	add	r0, r0, #2
	strb	ip, [fp, #-60]
	ldrb	ip, [r7, #493]	@ zero_extendqisi2
	strb	r4, [fp, #-59]
	strb	r2, [fp, #-58]
	ldrb	r4, [r7, #494]	@ zero_extendqisi2
	ldrb	r2, [r7, #495]	@ zero_extendqisi2
	strb	lr, [fp, #-57]
	strb	ip, [fp, #-56]
	ldrb	lr, [r7, #496]	@ zero_extendqisi2
	ldrb	ip, [r7, #497]	@ zero_extendqisi2
	strb	r4, [fp, #-55]
	strb	lr, [fp, #-53]
	strb	ip, [fp, #-52]
	strb	r2, [fp, #-54]
	mov	r2, #16
	ldr	r4, [r10, #52]
	blx	r4
	mov	r1, r5
	ldr	r4, [r10, #48]
	mov	r2, #16
	sub	r0, fp, #60
	blx	r4
	ldrb	r4, [r7, #1]	@ zero_extendqisi2
	ldrb	lr, [r7, #506]	@ zero_extendqisi2
	add	r0, r7, #2992
	ldrb	ip, [r7, #507]	@ zero_extendqisi2
	sub	r1, fp, #60
	ldrb	r2, [r7, #509]	@ zero_extendqisi2
	add	r0, r0, #2
	ldrb	r8, [r7, #508]	@ zero_extendqisi2
	strb	r5, [fp, #-51]
	strb	r5, [fp, #-50]
	strb	r4, [fp, #-60]
	ldrb	r5, [r7, #510]	@ zero_extendqisi2
	ldrb	r4, [r7, #511]	@ zero_extendqisi2
	strb	lr, [fp, #-59]
	strb	ip, [fp, #-58]
	ldrb	lr, [r7, #512]	@ zero_extendqisi2
	ldrb	ip, [r7, #513]	@ zero_extendqisi2
	strb	r2, [fp, #-56]
	mov	r2, #16
	strb	r4, [fp, #-54]
	strb	r8, [fp, #-57]
	strb	r5, [fp, #-55]
	strb	lr, [fp, #-53]
	strb	ip, [fp, #-52]
	ldr	r4, [r10, #52]
	blx	r4
	ldr	r3, [fp, #-64]
	ldr	r2, [r3, #72]
	cmp	r2, #0
	bne	.L460
	add	r5, r7, #4096
	add	r8, r7, #1152
	mov	r4, r5
	add	r5, r5, #2
	add	r4, r4, #50
.L461:
	mov	r1, r8
	mov	r0, r5
	ldr	r3, [r6, #52]
	mov	r2, #11
	add	r5, r5, #16
	blx	r3
	cmp	r5, r4
	add	r8, r8, #11
	bne	.L461
	add	r5, r7, #1184
	add	r8, r7, #4160
	add	r5, r5, #1
	add	r8, r8, #34
.L462:
	mov	r1, r5
	mov	r0, r4
	ldr	r3, [r6, #52]
	mov	r2, #11
	add	r4, r4, #16
	blx	r3
	cmp	r4, r8
	add	r5, r5, #11
	ldr	r9, .L480
	bne	.L462
	add	r0, r7, #4736
	ldr	r3, [r9, #52]
	mov	r2, #14
	add	r1, r7, #536
	add	r0, r0, #34
	add	r10, r7, #4480
	blx	r3
	add	ip, r7, #5056
	add	r1, r7, #548
	add	r0, r7, #4736
	ldr	r3, [r9, #52]
	add	r1, r1, #2
	add	r0, r0, #50
	mov	r2, #14
	mov	r4, ip
	blx	r3
	add	r3, r4, #2
	str	r3, [fp, #-64]
	add	r3, r7, #564
	add	r10, r10, #2
	str	r7, [fp, #-68]
	mov	r9, r3
.L469:
	sub	r4, r10, #288
	mov	r8, r9
.L472:
	add	r7, r4, #48
	mov	r5, r8
.L470:
	mov	r1, r5
	mov	r0, r4
	ldr	r3, [r6, #52]
	mov	r2, #11
	add	r4, r4, #16
	blx	r3
	cmp	r7, r4
	add	r5, r5, #66
	bne	.L470
	cmp	r7, r10
	add	r8, r8, #11
	mov	r4, r7
	bne	.L472
	ldr	r3, [fp, #-64]
	add	r10, r10, #288
	add	r9, r9, #198
	cmp	r10, r3
	bne	.L469
	ldr	r7, [fp, #-68]
.L468:
	add	r0, r7, #3008
	ldr	r3, [r6, #52]
	add	r1, r7, #960
	mov	r2, #64
	add	r0, r0, #2
	blx	r3
	add	r0, r7, #3072
	ldr	r3, [r6, #52]
	add	r1, r7, #1024
	mov	r2, #64
	add	r0, r0, #2
	blx	r3
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L460:
	add	r1, r7, #9472
	add	r0, r7, #4800
	ldr	r4, [r10, #52]
	add	r1, r1, #28
	mov	r2, #128
	add	r0, r0, #2
	blx	r4
	add	ip, r7, #9600
	add	r1, r7, #11904
	add	r0, r7, #6464
	ldr	r3, [r10, #52]
	mov	r2, #128
	add	r1, r1, #28
	add	r0, r0, #2
	mov	r4, ip
	add	r10, r7, #5696
	blx	r3
	add	r2, r4, #28
	add	r10, r10, #2
	add	r3, r7, #7232
	mov	r9, r2
	add	r3, r3, #2
	str	r7, [fp, #-68]
	str	r3, [fp, #-64]
.L463:
	sub	r4, r10, #768
	mov	r8, r9
.L467:
	add	r7, r4, #256
	mov	r5, r8
.L464:
	ldr	r3, [r6, #52]
	mov	r2, #64
	mov	r1, r5
	mov	r0, r4
	add	r4, r4, r2
	blx	r3
	cmp	r7, r4
	add	r5, r5, #64
	ldr	r3, .L480
	bne	.L464
	cmp	r7, r10
	add	r8, r8, #384
	mov	r4, r7
	bne	.L467
	ldr	r2, [fp, #-64]
	add	r10, r7, #768
	add	r9, r9, #1152
	cmp	r10, r2
	bne	.L463
	ldr	r7, [fp, #-68]
	mov	r2, #960
	ldr	r3, [r3, #52]
	add	r1, r7, #1216
	add	r0, r7, #3136
	add	r1, r1, #2
	add	r0, r0, #2
	blx	r3
	b	.L468
.L481:
	.align	2
.L480:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP6_CfgTable, .-VP6_CfgTable
	.align	2
	.global	VP6_BuildTables
	.type	VP6_BuildTables, %function
VP6_BuildTables:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r4, r1
	mov	r6, r2
	mov	r5, r0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L487
	ldr	r3, [r1, #24]
	cmp	r3, #0
	bne	.L491
	ldr	r7, .L493
	mov	r2, #80
	ldr	r1, .L493+4
	add	r0, r0, #404
	ldr	r3, [r7, #52]
	blx	r3
	mov	r2, #2
	ldr	r3, [r7, #52]
	add	r0, r5, r2
	ldr	r1, .L493+8
	blx	r3
	ldr	r3, [r7, #52]
	mov	r2, #14
	ldr	r1, .L493+12
	add	r0, r5, #484
	blx	r3
	ldr	r3, [r7, #52]
	mov	r2, #2
	ldr	r1, .L493+16
	mov	r0, r5
	blx	r3
	add	r0, r5, #496
	ldr	r3, [r7, #52]
	mov	r2, #16
	ldr	r1, .L493+20
	add	r0, r0, #2
	blx	r3
	ldr	r1, .L493+24
	ldr	r3, [r7, #52]
	mov	r2, #64
	add	r0, r5, #1088
	blx	r3
	mov	r1, r4
	mov	r0, r5
	bl	VP6_BuildScanOrder
.L485:
	ldr	r3, [r4, #24]
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VP6_ConfigureEntropyDecoder
	ldr	r3, [r4, #72]
	cmp	r3, #0
	bne	.L492
.L486:
	mov	r1, r4
	mov	r0, r5
	bl	VP6_CfgTable
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L491:
	mov	r2, r1
	mov	r1, r6
	bl	VP6_DecodeModeProbs
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	bl	VP6_ConfigureMvEntropyDecoder
	b	.L485
.L492:
	mov	r0, r5
	bl	VP6_ConvertBoolToHuff
	b	.L486
.L487:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L494:
	.align	2
.L493:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1996
	.word	.LANCHOR0+2076
	.word	.LANCHOR0+2080
	.word	.LANCHOR0+2096
	.word	.LANCHOR0+2100
	.word	.LANCHOR0+2116
	UNWIND(.fnend)
	.size	VP6_BuildTables, .-VP6_BuildTables
	.align	2
	.global	IsFrameSizeChanged
	.type	IsFrameSizeChanged, %function
IsFrameSizeChanged:
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
	add	r3, r0, #8192
	add	r0, r0, #12288
	ldr	r1, [r3, #3948]
	ldr	r2, [r0]
	cmp	r1, r2
	beq	.L498
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L498:
	ldr	r3, [r3, #3952]
	ldr	r0, [r0, #4]
	subs	r0, r3, r0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsFrameSizeChanged, .-IsFrameSizeChanged
	.align	2
	.global	VP6DEC_Decode
	.type	VP6DEC_Decode, %function
VP6DEC_Decode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	moveq	r8, #1
	movne	r8, #0
	beq	.L545
	ldr	r3, [r1]
	str	r3, [r0, #232]
	ldr	r2, [r1, #12]
	str	r2, [r0, #236]
	ldr	r2, [r1, #16]
	cmp	r2, #0
	str	r2, [r0, #240]
	bne	.L502
	add	r5, r0, #12288
	mov	r3, #3
	strb	r3, [r5, #36]
.L503:
	mov	r0, r4
	bl	VP6_DecodeDecide
	cmp	r0, #1
	mov	r7, r0
	beq	.L523
	ldr	r1, .L553
	mov	r0, #1
	bl	dprint_vfmw
	mov	r8, #0
.L501:
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L502:
	cmp	r2, #2
	ble	.L546
	add	r5, r0, #12608
	add	r6, r0, #244
	add	r5, r5, #44
	mov	r1, r3
	mov	r0, r5
	bl	BsInit
	add	r3, r4, #232
	mov	r1, r5
	mov	r0, r6
	str	r3, [r4, #228]
	bl	VP6_GetPictureHeader
	cmp	r0, #1
	mov	r7, r0
	beq	.L505
	ldr	r1, .L553+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L545:
	movw	r2, #2597
	ldr	r1, .L553+8
	mov	r0, #0
	mov	r8, r0
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L505:
	add	r1, r4, #12480
	mov	r2, r5
	mov	r0, r6
	add	r1, r1, #24
	bl	VP6_BuildTables
	cmp	r0, #1
	bne	.L547
	add	r5, r4, #12288
	ldr	r3, [r5, #32]
	cmp	r3, #0
	bne	.L548
.L507:
	ldr	r7, .L553+12
	ldr	r6, [r7]
	cmp	r6, #0
	beq	.L509
	ldr	r1, [r5, #96]
	mov	r3, #8
	ldr	r0, [r5, #244]
	sub	r2, fp, #44
	ldr	lr, [r5, #100]
	ldr	ip, [r5, #248]
	strh	r1, [fp, #-42]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-38]	@ movhi
	strh	lr, [fp, #-44]	@ movhi
	strh	ip, [fp, #-40]	@ movhi
	ldr	r0, [r5, #752]
	blx	r6
.L509:
	ldr	r0, [r5, #752]
	bl	FSP_GetFspType
	subs	ip, r0, #0
	bne	.L510
	sub	r3, fp, #36
	sub	r2, fp, #48
	sub	r1, fp, #52
	ldr	r0, [r5, #752]
	str	ip, [r3, #-8]!
	str	ip, [fp, #-52]
	str	ip, [fp, #-48]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4]
	ldr	r2, [r3, #732]
	cmp	r2, #1
	beq	.L549
.L510:
	mov	r2, #1
	ldr	r1, [r5, #48]
	ldr	r0, [r5, #752]
	mov	r7, #0
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #52]
	add	r6, r4, #12672
	ldr	r0, [r5, #752]
	add	r6, r6, #16
	bl	FSP_ClearLogicFs
	str	r7, [r5, #48]
	str	r7, [r5, #52]
	ldr	r0, [r5, #752]
	bl	FSP_GetNullLogicFs
	str	r7, [r5, #28]
	mov	r1, r6
	str	r0, [r5, #52]
	str	r0, [r5, #48]
	ldr	r0, [r5, #752]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [r5, #248]
	ldr	r3, [r5, #244]
	cmp	r2, #512
	bhi	.L517
	cmp	r3, #512
	bhi	.L517
	ldr	r3, [r4]
	ldr	r2, [r3, #732]
	cmp	r2, #0
	bne	.L519
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L550
.L519:
	ldr	r0, [r5, #752]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L544
.L521:
	mov	r0, r4
	bl	VP6_ArrangeVHBMem
	cmp	r0, #1
	beq	.L503
	ldr	r1, .L553+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r8, #0
	b	.L501
.L523:
	mov	r0, r4
	bl	VP6_GetImageBuffer
	cmp	r0, #1
	mov	r6, r0
	beq	.L524
	mov	r0, r7
	ldr	r1, .L553+20
	bl	dprint_vfmw
	mov	r8, #0
	b	.L501
.L546:
	ldr	r1, .L553+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L524:
	mov	r2, r0
	ldr	r1, [r5, #44]
	ldr	r0, [r5, #752]
	bl	FSP_SetRef
	ldr	r1, [r5, #44]
	ldr	r0, [r5, #752]
	bl	FSP_GetFsImagePtr
	subs	lr, r0, #0
	beq	.L551
	ldr	r3, [r4]
	add	ip, lr, #592
	add	r1, lr, #608
	mov	r7, #0
	mov	r0, #29
	ldrd	r2, [r3, #64]
	strd	r2, [ip, #-8]
	ldr	r3, [r4]
	ldrd	r2, [r3, #80]
	strd	r2, [ip]
	ldr	r3, [r4]
	ldrd	r2, [r3, #96]
	strd	r2, [r1, #-8]
	mvn	r2, #0
	ldr	r1, [r4]
	mvn	r3, #0
	ldr	r1, [r1, #112]
	str	r1, [lr]
	ldr	r1, [r4]
	ldr	r1, [r1, #116]
	str	r1, [lr, #4]
	ldr	r1, [r4]
	ldr	r1, [r1, #120]
	str	r1, [lr, #8]
	ldr	r1, [r4]
	ldr	r1, [r1, #136]
	str	r7, [lr, #52]
	str	r1, [lr, #12]
	ldr	lr, [r4]
	ldr	r1, .L553+28
	strd	r2, [lr, #64]
	ldrd	r8, [ip]
	ldrd	r2, [ip, #-8]
	strd	r8, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	VP6_Set_DecParam
	cmp	r0, #1
	mov	r8, r0
	beq	.L526
	mov	r0, r6
	ldr	r1, .L553+32
	mov	r8, r7
	bl	dprint_vfmw
	b	.L501
.L548:
	ldr	r2, [r5, #96]
	ldr	r3, [r5, #244]
	cmp	r2, r3
	bne	.L507
	ldr	r2, [r5, #100]
	ldr	r3, [r5, #248]
	cmp	r2, r3
	beq	.L503
	b	.L507
.L526:
	ldrb	r3, [r5, #36]	@ zero_extendqisi2
	add	r1, r4, #12480
	cmp	r3, #0
	ldr	r3, .L553+36
	beq	.L552
	ldr	r6, [r5, #84]
	add	r0, r4, #12352
	ldr	r4, [r5, #88]
	add	r1, r1, #24
	ldr	r3, [r3, #52]
	add	r0, r0, #4
	mov	r2, #148
	blx	r3
	str	r6, [r5, #84]
	str	r4, [r5, #88]
.L528:
	ldr	r1, .L553+40
	mov	r0, #22
	bl	dprint_vfmw
	b	.L501
.L547:
	mov	r0, r7
	ldr	r1, .L553+44
	bl	dprint_vfmw
	b	.L501
.L517:
	ldr	r1, .L553+48
	mov	r0, #18
	bl	dprint_vfmw
	mov	r8, #0
	b	.L501
.L552:
	add	r0, r4, #12352
	add	r1, r1, #24
	mov	r2, #148
	ldr	r3, [r3, #52]
	add	r0, r0, #4
	blx	r3
	b	.L528
.L551:
	movw	r2, #2738
	ldr	r1, .L553+52
	mov	r0, #22
	mov	r8, lr
	bl	dprint_vfmw
	b	.L501
.L549:
	ldr	r3, [fp, #-44]
	cmp	r3, #0
	bgt	.L513
	ldr	r3, [fp, #-48]
	cmp	r3, #32
	bgt	.L513
	ldr	r6, [r4, #4]
	cmp	r6, #0
	bne	.L513
	ldr	r3, [r5, #100]
	cmp	r3, #0
	beq	.L510
	ldr	r1, [r5, #244]
	ldr	r0, [r5, #756]
	cmp	r1, r0
	beq	.L510
	ldr	r0, [r5, #248]
	ldr	ip, [r5, #760]
	cmp	r0, ip
	beq	.L510
	stmib	sp, {r0, r1}
	mov	r0, r2
	ldr	ip, [r5, #96]
	ldr	r1, .L553+56
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r7, [r7]
	ldr	r2, [r5, #244]
	ldr	r3, [r5, #248]
	cmp	r7, #0
	str	r2, [r5, #756]
	str	r3, [r5, #760]
	beq	.L510
	mov	r3, r6
	mov	r2, r6
	mov	r1, #120
	ldr	r0, [r5, #752]
	blx	r7
	b	.L510
.L550:
	ldr	r3, [r5, #32]
	cmp	r3, #0
	bne	.L521
.L544:
	mov	r0, r6
	bl	ResetVoQueue
	b	.L521
.L513:
	mvn	r8, #1
	b	.L501
.L554:
	.align	2
.L553:
	.word	.LC38
	.word	.LC33
	.word	.LC8
	.word	g_event_report
	.word	.LC37
	.word	.LC39
	.word	.LC32
	.word	.LC40
	.word	.LC41
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC42
	.word	.LC34
	.word	.LC36
	.word	.LC5
	.word	.LC35
	UNWIND(.fnend)
	.size	VP6DEC_Decode, .-VP6DEC_Decode
	.align	2
	.global	VP6_SetImgFormat
	.type	VP6_SetImgFormat, %function
VP6_SetImgFormat:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #12288
	mov	r6, r0
	ldr	r1, [r5, #44]
	ldr	r0, [r5, #752]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldrb	r2, [r5, #36]	@ zero_extendqisi2
	mov	ip, #1
	ldrb	r1, [r4, #64]	@ zero_extendqisi2
	mov	lr, #5
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	bfi	r1, r2, #0, #2
	and	r2, r2, #3
	and	r3, r3, #252
	and	r1, r1, #227
	orr	r3, r3, #12
	bfi	r1, lr, #5, #3
	bfi	r3, ip, #4, #2
	strb	r1, [r4, #64]
	strb	r3, [r4, #65]
	mov	lr, #0
	ldr	r3, [r4, #64]
	mov	r1, lr
	bfc	r3, #14, #3
	str	r3, [r4, #64]
	ldrb	r7, [r5, #223]	@ zero_extendqisi2
	mov	r3, r3, lsr #16
	bfi	r3, r7, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r5, #224]
	str	r2, [r4, #56]
	str	r2, [r4, #60]
	mov	r2, #10
	str	r3, [r4, #120]
	mov	r3, #8
	str	r2, [r4, #296]
	str	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	strb	ip, [r4, #291]
	strb	ip, [r4, #289]
	strb	lr, [r4, #284]
	bl	SetAspectRatio
	ldr	r2, [r5, #248]
	mov	r2, r2, asl #4
	str	r2, [r4, #68]
	ldr	r3, [r5, #244]
	mov	r3, r3, asl #4
	str	r3, [r4, #72]
	ldr	r1, [r6]
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L561
.L557:
	str	r2, [r4, #76]
	mov	r2, r2, lsr #1
	str	r3, [r4, #80]
	mov	r3, r3, lsr #1
	str	r2, [r4, #84]
	str	r3, [r4, #88]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L561:
	ldr	lr, [r4, #112]
	mov	ip, r3, lsr #4
	ldr	r5, [r4, #36]
	add	r7, r4, #512
	mov	r1, lr, asl #4
	add	r8, r5, lr
	mul	ip, ip, r1
	add	r6, ip, r5
	str	r6, [r4, #40]
	ldrd	r0, [r7, #-8]
	add	lr, r6, lr
	adds	r0, r0, ip
	adc	r1, r1, ip, asr #31
	strd	r0, [r7]
	str	r6, [r4, #24]
	str	lr, [r4, #32]
	str	r8, [r4, #28]
	str	r5, [r4, #20]
	b	.L557
	UNWIND(.fnend)
	.size	VP6_SetImgFormat, .-VP6_SetImgFormat
	.align	2
	.global	VP6DEC_VDMPostProc
	.type	VP6DEC_VDMPostProc, %function
VP6DEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r5, r0, #0
	mov	r6, r1
	beq	.L592
	mov	r2, r1
	mov	r0, #22
	ldr	r1, .L600
	add	r4, r5, #12288
	bl	dprint_vfmw
	ldr	r3, [r5, #4]
	mov	r1, r5
	mov	r0, #10
	ldrb	r2, [r3, #52]	@ zero_extendqisi2
	strb	r2, [r4, #223]
	ldr	r3, [r3, #212]
	str	r3, [r4, #224]
	bl	ReleasePacket
	ldr	r1, [r4, #44]
	ldr	r0, [r4, #752]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L593
	cmp	r6, #0
	blt	.L566
	cmp	r6, #100
	movlt	r2, r6
	movge	r2, #100
	str	r2, [r7, #152]
	ldr	r3, [r5]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L594
.L567:
	mov	r0, r5
	bl	VP6_SetImgFormat
	ldr	r3, [r4, #24]
	mov	r2, #1
	str	r2, [r4, #28]
	cmp	r3, #2
	beq	.L595
.L568:
	ldr	r1, [r4, #44]
	str	r1, [r4, #56]
.L569:
	cmn	r1, #1
	beq	.L570
	mov	r2, #1
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	ldr	r1, [r4, #56]
	ldr	r0, [r4, #752]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L596
	add	r3, r5, #12672
	ldr	r0, [r4, #752]
	mov	r2, r5
	str	r6, [sp]
	add	r3, r3, #16
	mov	r1, #10
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r5, r0
	bne	.L597
.L570:
	ldr	r3, [r4, #52]
	ldr	r2, [r4, #48]
	cmp	r3, r2
	beq	.L572
	ldr	r1, [r4, #44]
	cmp	r3, r1
	beq	.L573
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
	ldr	r1, [r4, #44]
.L573:
	str	r1, [r4, #52]
	mov	r2, #1
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
	ldrb	r3, [r4, #36]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L598
	ldr	r3, [r4, #48]
	ldr	r1, [r4, #44]
	cmp	r3, r1
	beq	.L576
.L599:
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
	ldr	r1, [r4, #44]
.L576:
	ldr	r0, [r4, #752]
	mov	r2, #1
	str	r1, [r4, #48]
	bl	FSP_SetRef
	mov	r0, #1
.L590:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L598:
	ldr	r3, [r4, #40]
	cmp	r3, #0
	moveq	r0, #1
	beq	.L590
	ldr	r3, [r4, #48]
	ldr	r1, [r4, #44]
	cmp	r3, r1
	bne	.L599
	b	.L576
.L566:
	mov	r3, #0
	str	r3, [r7, #152]
	b	.L567
.L595:
	ldrb	r3, [r4, #36]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L568
	mvn	r3, #0
	ldr	r1, [r4, #44]
	mov	r2, #0
	str	r3, [r4, #56]
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	ldr	r1, [r4, #56]
	b	.L569
.L597:
	mov	r2, #0
	add	r8, r6, #560
	ldr	r1, [r4, #44]
	add	r9, r6, #544
	ldr	r0, [r4, #752]
	mov	r7, #0
	bl	FSP_SetRef
	ldr	r1, [r6, #544]
	ldr	r0, [r4, #752]
	mov	r6, #0
	bl	FreeUsdByDec
	strd	r6, [r9]
	ldr	r1, [r8, #-8]
	ldr	r0, [r4, #752]
	bl	FreeUsdByDec
	strd	r6, [r8, #-8]
	mov	r2, #0
	ldr	r1, [r4, #56]
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	ldr	r1, .L600+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L592:
	movw	r2, #2873
	ldr	r1, .L600+8
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L572:
	mov	r1, r3
	ldr	r0, [r4, #752]
	bl	FSP_GetRef
	subs	r2, r0, #0
	bne	.L591
	ldr	r3, [r4, #52]
	ldr	r1, [r4, #44]
	cmp	r3, r1
	beq	.L573
	mov	r1, r3
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
.L591:
	ldr	r1, [r4, #44]
	b	.L573
.L594:
	ldr	r1, .L600+12
	mov	r0, #1
	bl	dprint_vfmw
	add	r5, r7, #544
	mov	r2, #0
	add	r8, r7, #560
	ldr	r1, [r4, #44]
	mov	r6, #0
	ldr	r0, [r4, #752]
	bl	FSP_SetRef
	ldr	r1, [r7, #544]
	ldr	r0, [r4, #752]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r5]
	mov	r5, #0
	ldr	r1, [r8, #-8]
	ldr	r0, [r4, #752]
	bl	FreeUsdByDec
	strd	r6, [r8, #-8]
	mov	r2, r5
	ldr	r1, [r4, #44]
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	mov	r2, #1
	ldr	r1, [r4, #48]
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #48]
	str	r5, [r4, #52]
	ldr	r0, [r4, #752]
	bl	FSP_GetNullLogicFs
	str	r5, [r4, #28]
	mov	r3, r0
	mvn	r0, #0
	str	r3, [r4, #52]
	str	r3, [r4, #48]
	b	.L590
.L596:
	mov	r2, r6
	ldr	r1, .L600+16
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L590
.L593:
	ldr	r1, .L600+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L590
.L601:
	.align	2
.L600:
	.word	.LC43
	.word	.LC47
	.word	.LC8
	.word	.LC45
	.word	.LC46
	.word	.LC44
	UNWIND(.fnend)
	.size	VP6DEC_VDMPostProc, .-VP6DEC_VDMPostProc
	.align	2
	.global	VP6DEC_RecycleImage
	.type	VP6DEC_RecycleImage, %function
VP6DEC_RecycleImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L606
	add	r4, r4, #12288
	mov	r2, #0
	ldr	r0, [r4, #752]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #752]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L605
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #752]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #752]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L605:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L606:
	movw	r2, #3003
	ldr	r1, .L607
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L608:
	.align	2
.L607:
	.word	.LC8
	UNWIND(.fnend)
	.size	VP6DEC_RecycleImage, .-VP6DEC_RecycleImage
	.align	2
	.global	VP6DEC_GetRemainImg
	.type	VP6DEC_GetRemainImg, %function
VP6DEC_GetRemainImg:
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
	subs	r4, r0, #0
	beq	.L613
	add	r0, r4, #12672
	add	r0, r0, #16
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	GetVoLastImageID
.L613:
	movw	r2, #3038
	ldr	r1, .L614
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L615:
	.align	2
.L614:
	.word	.LC8
	UNWIND(.fnend)
	.size	VP6DEC_GetRemainImg, .-VP6DEC_GetRemainImg
	.global	DefaultScanBands
	.global	ZrlUpdateProbs
	.global	ScanBandUpdateProbs
	.global	ZeroRunProbDefaults
	.global	VP6_AcUpdateProbs
	.global	VP6_DcUpdateProbs
	.global	DefaultSignProbs
	.global	DefaultIsShortProbs
	.global	DefaultMvLongProbs
	.global	DefaultMvShortProbs
	.global	VP6_MvUpdateProbs
	.global	VP6_BaselineXmittedProbs
	.global	VP6_ModeVq
	.global	VP6_DcNodeEqs
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	VP6_DcNodeEqs, %object
	.size	VP6_DcNodeEqs, 120
VP6_DcNodeEqs:
	.word	122
	.word	133
	.word	133
	.word	51
	.word	142
	.word	-16
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	78
	.word	171
	.word	169
	.word	71
	.word	221
	.word	-30
	.word	139
	.word	117
	.word	214
	.word	44
	.word	246
	.word	-3
	.word	168
	.word	79
	.word	210
	.word	38
	.word	203
	.word	17
	.type	VP6_DcUpdateProbs, %object
	.size	VP6_DcUpdateProbs, 22
VP6_DcUpdateProbs:
	.byte	-110
	.byte	-1
	.byte	-75
	.byte	-49
	.byte	-24
	.byte	-13
	.byte	-18
	.byte	-5
	.byte	-12
	.byte	-6
	.byte	-7
	.byte	-77
	.byte	-1
	.byte	-42
	.byte	-16
	.byte	-6
	.byte	-1
	.byte	-12
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.space	2
	.type	ZeroRunProbDefaults, %object
	.size	ZeroRunProbDefaults, 28
ZeroRunProbDefaults:
	.byte	-58
	.byte	-59
	.byte	-60
	.byte	-110
	.byte	-58
	.byte	-52
	.byte	-87
	.byte	-114
	.byte	-126
	.byte	-120
	.byte	-107
	.byte	-107
	.byte	-65
	.byte	-7
	.byte	-121
	.byte	-55
	.byte	-75
	.byte	-102
	.byte	98
	.byte	117
	.byte	-124
	.byte	126
	.byte	-110
	.byte	-87
	.byte	-72
	.byte	-16
	.byte	-10
	.byte	-2
	.type	ZrlUpdateProbs, %object
	.size	ZrlUpdateProbs, 28
ZrlUpdateProbs:
	.byte	-37
	.byte	-10
	.byte	-18
	.byte	-7
	.byte	-24
	.byte	-17
	.byte	-7
	.byte	-1
	.byte	-8
	.byte	-3
	.byte	-17
	.byte	-12
	.byte	-15
	.byte	-8
	.byte	-58
	.byte	-24
	.byte	-5
	.byte	-3
	.byte	-37
	.byte	-15
	.byte	-3
	.byte	-1
	.byte	-8
	.byte	-7
	.byte	-12
	.byte	-18
	.byte	-5
	.byte	-1
	.type	VP6_AcUpdateProbs, %object
	.size	VP6_AcUpdateProbs, 396
VP6_AcUpdateProbs:
	.byte	-29
	.byte	-10
	.byte	-26
	.byte	-9
	.byte	-12
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-47
	.byte	-25
	.byte	-25
	.byte	-7
	.byte	-7
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-31
	.byte	-14
	.byte	-15
	.byte	-5
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-15
	.byte	-3
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-50
	.byte	-53
	.byte	-29
	.byte	-17
	.byte	-9
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-49
	.byte	-57
	.byte	-36
	.byte	-20
	.byte	-13
	.byte	-4
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-44
	.byte	-37
	.byte	-26
	.byte	-13
	.byte	-12
	.byte	-3
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-20
	.byte	-19
	.byte	-9
	.byte	-4
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-16
	.byte	-16
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-26
	.byte	-23
	.byte	-7
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-18
	.byte	-18
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-5
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-31
	.byte	-17
	.byte	-29
	.byte	-25
	.byte	-12
	.byte	-3
	.byte	-13
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-24
	.byte	-22
	.byte	-32
	.byte	-28
	.byte	-14
	.byte	-7
	.byte	-14
	.byte	-4
	.byte	-5
	.byte	-5
	.byte	-1
	.byte	-21
	.byte	-7
	.byte	-18
	.byte	-16
	.byte	-5
	.byte	-1
	.byte	-7
	.byte	-1
	.byte	-3
	.byte	-3
	.byte	-1
	.byte	-7
	.byte	-3
	.byte	-5
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-6
	.byte	-7
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-13
	.byte	-12
	.byte	-6
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-8
	.byte	-6
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.type	ScanBandUpdateProbs, %object
	.size	ScanBandUpdateProbs, 64
ScanBandUpdateProbs:
	.byte	-1
	.byte	-124
	.byte	-124
	.byte	-97
	.byte	-103
	.byte	-105
	.byte	-95
	.byte	-86
	.byte	-92
	.byte	-94
	.byte	-120
	.byte	110
	.byte	103
	.byte	114
	.byte	-127
	.byte	118
	.byte	124
	.byte	125
	.byte	-124
	.byte	-120
	.byte	114
	.byte	110
	.byte	-114
	.byte	-121
	.byte	-122
	.byte	123
	.byte	-113
	.byte	126
	.byte	-103
	.byte	-73
	.byte	-90
	.byte	-95
	.byte	-85
	.byte	-76
	.byte	-77
	.byte	-92
	.byte	-53
	.byte	-38
	.byte	-31
	.byte	-39
	.byte	-41
	.byte	-50
	.byte	-53
	.byte	-39
	.byte	-27
	.byte	-15
	.byte	-8
	.byte	-13
	.byte	-3
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.type	VP6_ModeVq, %object
	.size	VP6_ModeVq, 960
VP6_ModeVq:
	.byte	9
	.byte	15
	.byte	32
	.byte	25
	.byte	7
	.byte	19
	.byte	9
	.byte	21
	.byte	1
	.byte	12
	.byte	14
	.byte	12
	.byte	3
	.byte	18
	.byte	14
	.byte	23
	.byte	3
	.byte	10
	.byte	0
	.byte	4
	.byte	48
	.byte	39
	.byte	1
	.byte	2
	.byte	11
	.byte	27
	.byte	29
	.byte	44
	.byte	7
	.byte	27
	.byte	1
	.byte	4
	.byte	0
	.byte	3
	.byte	1
	.byte	6
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	21
	.byte	32
	.byte	1
	.byte	2
	.byte	4
	.byte	10
	.byte	32
	.byte	43
	.byte	6
	.byte	23
	.byte	2
	.byte	3
	.byte	1
	.byte	19
	.byte	1
	.byte	6
	.byte	12
	.byte	21
	.byte	0
	.byte	7
	.byte	69
	.byte	83
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	10
	.byte	29
	.byte	3
	.byte	12
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	0
	.byte	0
	.byte	11
	.byte	20
	.byte	1
	.byte	4
	.byte	18
	.byte	36
	.byte	43
	.byte	48
	.byte	13
	.byte	35
	.byte	0
	.byte	2
	.byte	0
	.byte	5
	.byte	3
	.byte	12
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	70
	.byte	44
	.byte	0
	.byte	1
	.byte	2
	.byte	10
	.byte	37
	.byte	46
	.byte	8
	.byte	26
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	8
	.byte	15
	.byte	0
	.byte	1
	.byte	8
	.byte	21
	.byte	74
	.byte	53
	.byte	22
	.byte	42
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	3
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	-115
	.byte	42
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	11
	.byte	24
	.byte	1
	.byte	11
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	19
	.byte	4
	.byte	10
	.byte	24
	.byte	45
	.byte	21
	.byte	37
	.byte	9
	.byte	29
	.byte	0
	.byte	3
	.byte	1
	.byte	7
	.byte	11
	.byte	25
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	46
	.byte	42
	.byte	0
	.byte	1
	.byte	2
	.byte	10
	.byte	54
	.byte	51
	.byte	10
	.byte	30
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	28
	.byte	32
	.byte	0
	.byte	0
	.byte	3
	.byte	10
	.byte	75
	.byte	51
	.byte	14
	.byte	33
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	100
	.byte	46
	.byte	0
	.byte	1
	.byte	3
	.byte	9
	.byte	21
	.byte	37
	.byte	5
	.byte	20
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	1
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	27
	.byte	29
	.byte	0
	.byte	1
	.byte	9
	.byte	25
	.byte	53
	.byte	51
	.byte	12
	.byte	34
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	1
	.byte	5
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	80
	.byte	38
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	69
	.byte	33
	.byte	5
	.byte	16
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	16
	.byte	20
	.byte	0
	.byte	0
	.byte	2
	.byte	8
	.byte	104
	.byte	49
	.byte	15
	.byte	33
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-62
	.byte	16
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	9
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	41
	.byte	22
	.byte	1
	.byte	0
	.byte	1
	.byte	31
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	7
	.byte	0
	.byte	1
	.byte	98
	.byte	25
	.byte	4
	.byte	10
	.byte	123
	.byte	37
	.byte	6
	.byte	4
	.byte	1
	.byte	27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	5
	.byte	8
	.byte	1
	.byte	7
	.byte	0
	.byte	1
	.byte	12
	.byte	10
	.byte	0
	.byte	2
	.byte	26
	.byte	14
	.byte	14
	.byte	12
	.byte	0
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	55
	.byte	17
	.byte	1
	.byte	9
	.byte	0
	.byte	36
	.byte	5
	.byte	7
	.byte	1
	.byte	3
	.byte	-47
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	5
	.byte	4
	.byte	5
	.byte	0
	.byte	121
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	2
	.byte	4
	.byte	1
	.byte	4
	.byte	2
	.byte	2
	.byte	0
	.byte	1
	.byte	-81
	.byte	5
	.byte	0
	.byte	1
	.byte	0
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	83
	.byte	5
	.byte	2
	.byte	3
	.byte	0
	.byte	102
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	3
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-23
	.byte	6
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	34
	.byte	16
	.byte	112
	.byte	21
	.byte	1
	.byte	28
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	8
	.byte	1
	.byte	7
	.byte	0
	.byte	3
	.byte	2
	.byte	5
	.byte	0
	.byte	2
	.byte	-97
	.byte	35
	.byte	2
	.byte	2
	.byte	0
	.byte	25
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	6
	.byte	0
	.byte	5
	.byte	0
	.byte	1
	.byte	4
	.byte	4
	.byte	0
	.byte	1
	.byte	75
	.byte	39
	.byte	5
	.byte	7
	.byte	2
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	11
	.byte	2
	.byte	16
	.byte	1
	.byte	4
	.byte	7
	.byte	10
	.byte	0
	.byte	2
	.byte	-44
	.byte	21
	.byte	0
	.byte	1
	.byte	0
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	2
	.byte	2
	.byte	0
	.byte	0
	.byte	4
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	-84
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	-69
	.byte	22
	.byte	1
	.byte	1
	.byte	0
	.byte	17
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	6
	.byte	0
	.byte	4
	.byte	0
	.byte	1
	.byte	4
	.byte	4
	.byte	0
	.byte	1
	.byte	-123
	.byte	6
	.byte	1
	.byte	2
	.byte	1
	.byte	70
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	4
	.byte	0
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-5
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	3
	.byte	2
	.byte	3
	.byte	0
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	11
	.byte	4
	.byte	1
	.byte	4
	.byte	0
	.byte	2
	.byte	3
	.byte	2
	.byte	0
	.byte	4
	.byte	49
	.byte	46
	.byte	3
	.byte	4
	.byte	7
	.byte	31
	.byte	42
	.byte	41
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	1
	.byte	7
	.byte	1
	.byte	4
	.byte	2
	.byte	4
	.byte	0
	.byte	1
	.byte	26
	.byte	25
	.byte	1
	.byte	1
	.byte	2
	.byte	10
	.byte	67
	.byte	39
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	0
	.byte	14
	.byte	0
	.byte	2
	.byte	31
	.byte	26
	.byte	1
	.byte	6
	.byte	103
	.byte	46
	.byte	1
	.byte	2
	.byte	2
	.byte	10
	.byte	33
	.byte	42
	.byte	0
	.byte	0
	.byte	1
	.byte	4
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	14
	.byte	31
	.byte	9
	.byte	13
	.byte	14
	.byte	54
	.byte	22
	.byte	29
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	4
	.byte	18
	.byte	6
	.byte	13
	.byte	1
	.byte	5
	.byte	0
	.byte	1
	.byte	85
	.byte	39
	.byte	0
	.byte	0
	.byte	1
	.byte	9
	.byte	69
	.byte	40
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	0
	.byte	0
	.byte	31
	.byte	28
	.byte	0
	.byte	0
	.byte	3
	.byte	14
	.byte	-126
	.byte	34
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	3
	.byte	3
	.byte	0
	.byte	1
	.byte	-85
	.byte	25
	.byte	0
	.byte	0
	.byte	1
	.byte	5
	.byte	25
	.byte	21
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	17
	.byte	21
	.byte	68
	.byte	29
	.byte	6
	.byte	15
	.byte	13
	.byte	22
	.byte	0
	.byte	0
	.byte	6
	.byte	12
	.byte	3
	.byte	14
	.byte	4
	.byte	10
	.byte	1
	.byte	7
	.byte	0
	.byte	3
	.byte	51
	.byte	39
	.byte	0
	.byte	1
	.byte	2
	.byte	12
	.byte	91
	.byte	44
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	0
	.byte	1
	.byte	81
	.byte	25
	.byte	0
	.byte	0
	.byte	2
	.byte	9
	.byte	106
	.byte	26
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-116
	.byte	37
	.byte	0
	.byte	1
	.byte	1
	.byte	8
	.byte	24
	.byte	33
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	0
	.byte	2
	.byte	0
	.byte	1
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	14
	.byte	23
	.byte	1
	.byte	3
	.byte	11
	.byte	53
	.byte	90
	.byte	31
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	1
	.byte	5
	.byte	2
	.byte	6
	.byte	1
	.byte	2
	.byte	0
	.byte	0
	.byte	123
	.byte	29
	.byte	0
	.byte	0
	.byte	1
	.byte	7
	.byte	57
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	13
	.byte	14
	.byte	0
	.byte	0
	.byte	4
	.byte	20
	.byte	-81
	.byte	20
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	-54
	.byte	23
	.byte	0
	.byte	0
	.byte	1
	.byte	3
	.byte	2
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	VP6_MvUpdateProbs, %object
	.size	VP6_MvUpdateProbs, 34
VP6_MvUpdateProbs:
	.byte	-19
	.byte	-10
	.byte	-3
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-6
	.byte	-6
	.byte	-4
	.byte	-25
	.byte	-13
	.byte	-11
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-5
	.byte	-5
	.byte	-2
	.space	2
	.type	VP6_LoopFilterLimitValues, %object
	.size	VP6_LoopFilterLimitValues, 64
VP6_LoopFilterLimitValues:
	.byte	14
	.byte	14
	.byte	13
	.byte	13
	.byte	12
	.byte	12
	.byte	10
	.byte	10
	.byte	10
	.byte	10
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.type	DcQuantTab, %object
	.size	DcQuantTab, 128
DcQuantTab:
	.short	188
	.short	188
	.short	188
	.short	188
	.short	180
	.short	172
	.short	172
	.short	172
	.short	172
	.short	172
	.short	168
	.short	164
	.short	164
	.short	160
	.short	160
	.short	160
	.short	160
	.short	140
	.short	140
	.short	140
	.short	140
	.short	132
	.short	132
	.short	132
	.short	132
	.short	128
	.short	128
	.short	128
	.short	108
	.short	108
	.short	104
	.short	104
	.short	100
	.short	100
	.short	96
	.short	96
	.short	92
	.short	92
	.short	76
	.short	76
	.short	76
	.short	76
	.short	72
	.short	72
	.short	68
	.short	64
	.short	64
	.short	64
	.short	64
	.short	64
	.short	60
	.short	44
	.short	44
	.short	44
	.short	40
	.short	40
	.short	36
	.short	32
	.short	28
	.short	20
	.short	12
	.short	12
	.short	8
	.short	8
	.type	AcQuantTab, %object
	.size	AcQuantTab, 128
AcQuantTab:
	.short	376
	.short	368
	.short	360
	.short	352
	.short	344
	.short	328
	.short	312
	.short	296
	.short	280
	.short	264
	.short	248
	.short	232
	.short	216
	.short	212
	.short	208
	.short	204
	.short	200
	.short	196
	.short	192
	.short	188
	.short	184
	.short	180
	.short	176
	.short	172
	.short	168
	.short	160
	.short	156
	.short	148
	.short	144
	.short	140
	.short	136
	.short	132
	.short	128
	.short	124
	.short	120
	.short	116
	.short	112
	.short	108
	.short	104
	.short	100
	.short	96
	.short	92
	.short	88
	.short	84
	.short	80
	.short	76
	.short	72
	.short	68
	.short	64
	.short	60
	.short	56
	.short	52
	.short	48
	.short	44
	.short	40
	.short	36
	.short	32
	.short	28
	.short	24
	.short	20
	.short	16
	.short	12
	.short	8
	.short	4
	.type	__FUNCTION__.13978, %object
	.size	__FUNCTION__.13978, 17
__FUNCTION__.13978:
	.ascii	"VP6_DecodeDecide\000"
	.space	3
	.type	VP6_BaselineXmittedProbs, %object
	.size	VP6_BaselineXmittedProbs, 80
VP6_BaselineXmittedProbs:
	.byte	42
	.byte	2
	.byte	7
	.byte	42
	.byte	22
	.byte	3
	.byte	2
	.byte	5
	.byte	1
	.byte	0
	.byte	69
	.byte	1
	.byte	1
	.byte	44
	.byte	6
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	8
	.byte	1
	.byte	8
	.byte	0
	.byte	0
	.byte	2
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	-27
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	35
	.byte	1
	.byte	6
	.byte	34
	.byte	0
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	122
	.byte	1
	.byte	1
	.byte	46
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	64
	.byte	0
	.byte	64
	.byte	64
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	64
	.byte	0
	.byte	64
	.byte	64
	.byte	64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	DefaultIsShortProbs, %object
	.size	DefaultIsShortProbs, 2
DefaultIsShortProbs:
	.byte	-94
	.byte	-92
	.space	2
	.type	DefaultMvShortProbs, %object
	.size	DefaultMvShortProbs, 14
DefaultMvShortProbs:
	.byte	-31
	.byte	-110
	.byte	-84
	.byte	-109
	.byte	-42
	.byte	39
	.byte	-100
	.byte	-52
	.byte	-86
	.byte	119
	.byte	-21
	.byte	-116
	.byte	-26
	.byte	-28
	.space	2
	.type	DefaultSignProbs, %object
	.size	DefaultSignProbs, 2
DefaultSignProbs:
	.byte	-128
	.byte	-128
	.space	2
	.type	DefaultMvLongProbs, %object
	.size	DefaultMvLongProbs, 16
DefaultMvLongProbs:
	.byte	-9
	.byte	-46
	.byte	-121
	.byte	68
	.byte	-118
	.byte	-36
	.byte	-17
	.byte	-10
	.byte	-12
	.byte	-72
	.byte	-55
	.byte	44
	.byte	-83
	.byte	-35
	.byte	-17
	.byte	-3
	.type	DefaultScanBands, %object
	.size	DefaultScanBands, 64
DefaultScanBands:
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	3
	.byte	3
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	6
	.byte	6
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	7
	.byte	8
	.byte	8
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	9
	.byte	10
	.byte	10
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	11
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	13
	.byte	13
	.byte	13
	.byte	13
	.byte	13
	.byte	14
	.byte	14
	.byte	14
	.byte	14
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.byte	15
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"image_size_in_mb abnormal(%d x %d)\012\000" )
.LC1:
	ASCII(.ascii	"vp6 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC2:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"line: %d\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"enter VP6_ConvertBoolToHuff\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"leave VP6_ConvertBoolToHuff\012\000" )
	.space	3
.LC11:
	ASCII(.ascii	"enter VP6_IntraFrmHeader\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"error: Vp3VersionNo %d > CURRENT_DECODE_VERSION(8)\012" )
	ASCII(.ascii	"\000" )
.LC13:
	ASCII(.ascii	"error: bitstream error!\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"We have a new size image!\012 The old size is %d x " )
	ASCII(.ascii	"%d, and the new is %d x %d\012\000" )
.LC15:
	ASCII(.ascii	"leave VP6_IntraFrmHeader\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"VP6_InterFrmHeader VersionNo fault,old:%d,new:%d\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC17:
	ASCII(.ascii	"[ERR]VP6_GetPictureHeader invalid param!\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"VP6_GetPictureHeader enter!\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"VP6_GetPictureHeader leave!\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC21:
	ASCII(.ascii	"VP6DEC_Init leave\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"ERROR: No Img buffer is allocated\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"----------------- vp6 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"-----I_MODE, but FrameType is %d-----\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"P-frm\000" )
	.space	2
.LC26:
	ASCII(.ascii	"-----cur framtype is %s, but refnum=%d-----\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"error: DecMode illegal\012\000" )
.LC28:
	ASCII(.ascii	"%s %d NULL == pFwdImg!!\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"dec P frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC30:
	ASCII(.ascii	"VP6_Set_DecParam but logic fs is null!\012\000" )
.LC31:
	ASCII(.ascii	"Decord FS is NULL!\012\000" )
.LC32:
	ASCII(.ascii	"Error! Truncated packet\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"[ERR]VP6_GetPictureHeader Error!\012\000" )
	.space	2
.LC34:
	ASCII(.ascii	"[ERR] VP6_DecodeDecide Error!\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\012" )
	ASCII(.ascii	"\000" )
.LC36:
	ASCII(.ascii	"pic width/height to large,MbWidth = %d, MbHeight = " )
	ASCII(.ascii	"%d\000" )
	.space	2
.LC37:
	ASCII(.ascii	"VP6_ArrangeVHBMem err\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"VP6_DecodeDecide err\012\000" )
	.space	2
.LC39:
	ASCII(.ascii	"VP6DEC_GetImageBuffer err\012\000" )
	.space	1
.LC40:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC41:
	ASCII(.ascii	"VP6_PrePare_decode Error!\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"leave VP6DEC_Decode\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC44:
	ASCII(.ascii	"pCurImg is null\012\000" )
	.space	3
.LC45:
	ASCII(.ascii	"err_level(%d) over ref_thr(%d)\012\000" )
.LC46:
	ASCII(.ascii	"line: %d pToQueImg is null!\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"insert img to Voqueue failed!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
