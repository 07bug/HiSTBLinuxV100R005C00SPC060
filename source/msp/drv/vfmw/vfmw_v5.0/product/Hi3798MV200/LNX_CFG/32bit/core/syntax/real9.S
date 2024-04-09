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
	.file	"real9.c"
	.text
	.align	2
	.global	Real9_CB_GetBits
	.type	Real9_CB_GetBits, %function
Real9_CB_GetBits:
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
	mov	r5, r0
	mov	r6, r1
	bl	BsShow
	mov	r1, r6
	mov	r4, r0
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_GetBits, .-Real9_CB_GetBits
	.align	2
	.global	Real9_CB_Get1Bit
	.type	Real9_CB_Get1Bit, %function
Real9_CB_Get1Bit:
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
	mov	r1, #1
	mov	r5, r0
	bl	BsShow
	mov	r1, #1
	mov	r4, r0
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_Get1Bit, .-Real9_CB_Get1Bit
	.align	2
	.global	Real9_CB_GetVLCBits
	.type	Real9_CB_GetVLCBits, %function
Real9_CB_GetVLCBits:
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
	ldr	r7, .L8
	mov	r4, #0
	mov	r6, r0
	mov	r8, r1
	mov	r5, r4
.L4:
	mov	r1, #8
	mov	r0, r6
	bl	BsShow
	ldrb	r3, [r7, r0]	@ zero_extendqisi2
	mov	r0, r6
	and	r2, r3, #15
	mov	r1, r3, lsr #4
	mov	r3, r3, lsr #5
	add	r4, r4, r1
	orr	r5, r2, r5, asl r3
	bl	BsSkip
	tst	r4, #1
	beq	.L4
	str	r5, [r8]
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L9:
	.align	2
.L8:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real9_CB_GetVLCBits, .-Real9_CB_GetVLCBits
	.align	2
	.global	Real9_GetImageBuffer
	.type	Real9_GetImageBuffer, %function
Real9_GetImageBuffer:
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
	add	r4, r0, #53248
	mov	r6, r0
	mov	r1, #1
	add	r7, r0, #8192
	ldr	r0, [r4, #1952]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #1552]
	blt	.L16
	mov	r1, r0
	ldr	r0, [r4, #1952]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L17
	ldr	r2, [r4, #1552]
	mov	r0, #18
	ldr	r1, .L18
	bl	dprint_vfmw
	ldr	r2, [r5, #28]
	cmp	r2, #0
	beq	.L15
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L15
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L18+4
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L15:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L16:
	ldr	r1, .L18+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #1548]
	ldr	r0, [r4, #1952]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1544]
	mov	r5, #0
	ldr	r0, [r4, #1952]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #1544]
	str	r5, [r4, #1548]
	ldr	r0, [r4, #1952]
	bl	FSP_GetNullLogicFs
	add	r1, r6, #54784
	add	r1, r1, #64
	str	r0, [r4, #1548]
	str	r0, [r4, #1544]
	strb	r5, [r7, #3189]
	ldr	r0, [r4, #1952]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L17:
	mov	r2, #464
	ldr	r1, .L18+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L19:
	.align	2
.L18:
	.word	.LC5
	.word	.LC6
	.word	.LC3
	.word	.LC4
	UNWIND(.fnend)
	.size	Real9_GetImageBuffer, .-Real9_GetImageBuffer
	.align	2
	.global	Real9_ArrangeVHBMem
	.type	Real9_ArrangeVHBMem, %function
Real9_ArrangeVHBMem:
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
	mov	r4, r2
	ldr	r2, [r2, #32]
	mov	r5, r1
	ldr	r3, [r4, #28]
	cmp	r2, #1
	bls	.L22
	sub	r0, r3, #2
	movw	r1, #510
	cmp	r2, #512
	cmpls	r0, r1
	bhi	.L22
	ldr	r1, [r5]
	ldr	r3, [r1, #732]
	cmp	r3, #0
	ldr	r3, [r1, #28]
	bne	.L25
	cmp	r3, #25
	beq	.L48
.L26:
	ldr	r7, [r4, #24]
	mov	r10, #5
	ldr	r8, [r4, #20]
	mov	r6, #2
	mov	r9, #4
.L32:
	ldr	r3, .L50
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, [r5]
	ldr	r2, [r4, #24]
	ldr	r3, [r4, #20]
	ldr	r1, [r1, #28]
	str	r7, [fp, #-60]
	cmp	r1, #24
	str	r8, [fp, #-56]
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	beq	.L38
	uxtb	r6, r6
	strb	r9, [fp, #-63]
	strb	r10, [fp, #-62]
.L42:
	add	r4, r5, #53248
	sub	r1, fp, #64
	strb	r6, [fp, #-61]
	ldr	r0, [r4, #1952]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	movne	r0, #0
	bne	.L47
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r4, #1952]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L49
	cmp	r0, #0
	addeq	r5, r5, #8192
	moveq	r3, #1
	moveq	r0, r3
	streqb	r3, [r5, #3192]
	beq	.L47
.L40:
	ldr	r1, .L50+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L47
.L22:
	ldr	r1, .L50+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
.L47:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L25:
	cmp	r3, #25
	bne	.L26
	ldr	r2, [r4, #24]
	ldr	r0, [r1, #692]
	ldr	r3, [r4, #20]
	cmp	r2, r0
	ldr	ip, [r1, #696]
	bhi	.L35
	cmp	r3, ip
	bhi	.L35
	ldr	r0, [r1, #720]
	mov	r7, r2
	ldr	r6, [r1, #716]
	mov	r8, r3
	cmp	r0, #0
	add	r9, r6, #2
	beq	.L45
	add	r6, r6, #1
	cmp	r6, #17
	movge	r6, #17
.L37:
	ldrb	r10, [r1, #740]	@ zero_extendqisi2
	b	.L32
.L38:
	mov	r6, #1
	strb	r10, [fp, #-62]
	strb	r6, [fp, #-63]
	b	.L42
.L35:
	stmia	sp, {r0, ip}
	mov	r0, #0
	ldr	r1, .L50+12
	bl	dprint_vfmw
	mov	r0, #0
	b	.L47
.L48:
	ldr	r2, [r4, #24]
	ldr	r7, [r1, #692]
	ldr	r3, [r4, #20]
	cmp	r2, r7
	ldr	r8, [r1, #696]
	bhi	.L28
	cmp	r3, r8
	bhi	.L28
	add	r3, r5, #8192
	ldrb	r0, [r3, #3192]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L47
	ldr	r2, [r1, #720]
	ldr	r3, [r1, #716]
	cmp	r2, #0
	add	r9, r3, #2
	beq	.L45
	add	r6, r3, #1
	cmp	r6, #17
	movge	r6, #17
	b	.L37
.L45:
	mov	r6, #1
	b	.L37
.L28:
	stmia	sp, {r7, r8}
	mov	r0, #0
	ldr	r1, .L50+12
	bl	dprint_vfmw
	mov	r0, #0
	b	.L47
.L49:
	add	r0, r5, #54784
	add	r0, r0, #64
	bl	ResetVoQueue
	b	.L40
.L51:
	.align	2
.L50:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC9
	.word	.LC7
	.word	.LC8
	UNWIND(.fnend)
	.size	Real9_ArrangeVHBMem, .-Real9_ArrangeVHBMem
	.align	2
	.global	Real9_CB_GetCPFMT
	.type	Real9_CB_GetCPFMT, %function
Real9_CB_GetCPFMT:
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
	mov	r1, #4
	mov	r5, r0
	bl	BsShow
	mov	r1, #4
	mov	r4, r0
	mov	r0, r5
	bl	BsSkip
	strb	r4, [r6, #8]
	mov	r1, #9
	mov	r0, r5
	bl	BsShow
	mov	r1, #9
	mov	r4, r0
	add	r4, r4, #1
	mov	r0, r5
	bl	BsSkip
	mov	r4, r4, asl #2
	mov	r0, r5
	str	r4, [r6, #24]
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	mov	r4, r0
	beq	.L55
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L55:
	mov	r1, #9
	mov	r0, r5
	bl	BsShow
	mov	r1, #9
	mov	r7, r0
	mov	r0, r5
	bl	BsSkip
	mov	r7, r7, asl #2
	mov	r0, r4
	str	r7, [r6, #20]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_GetCPFMT, .-Real9_CB_GetCPFMT
	.align	2
	.global	Real9_CB_SetDimensions
	.type	Real9_CB_SetDimensions, %function
Real9_CB_SetDimensions:
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
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #20]
	cmp	r3, #128
	beq	.L73
	cmp	r3, #176
	beq	.L74
	cmp	r3, #352
	beq	.L75
	cmp	r3, #704
	beq	.L76
	cmp	r3, #1408
	beq	.L77
.L58:
	add	r3, r3, #15
	add	r2, r2, #15
	mov	r3, r3, lsr #4
	mov	r2, r2, lsr #4
	str	r3, [r0, #84]
	mul	r3, r3, r2
	str	r2, [r0, #80]
	sub	r3, r3, #1
	cmp	r3, #47
	movls	r2, #0
	bls	.L59
	cmp	r3, #98
	bls	.L68
	cmp	r3, #396
	bcc	.L69
	cmp	r3, #1584
	bcc	.L70
	cmp	r3, #6336
	movcs	r2, #5
	bcc	.L72
.L59:
	ldr	r3, .L78
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #256]
	str	r3, [r0, #88]
	ldmfd	sp, {fp, sp, pc}
.L77:
	cmp	r2, #1152
	bne	.L58
	mov	r2, #88
	mov	r3, #72
	str	r2, [r0, #84]
	str	r3, [r0, #80]
.L72:
	mov	r2, #4
	b	.L59
.L73:
	cmp	r2, #96
	bne	.L58
	mov	r2, #8
	mov	r3, #6
	str	r2, [r0, #84]
	mov	r2, #0
	str	r3, [r0, #80]
	b	.L59
.L74:
	cmp	r2, #144
	bne	.L58
	mov	r2, #11
	mov	r3, #9
	str	r2, [r0, #84]
	str	r3, [r0, #80]
.L68:
	mov	r2, #1
	b	.L59
.L75:
	cmp	r2, #288
	bne	.L58
	mov	r2, #22
	mov	r3, #18
	str	r2, [r0, #84]
	str	r3, [r0, #80]
.L69:
	mov	r2, #2
	b	.L59
.L76:
	cmp	r2, #576
	bne	.L58
	mov	r2, #44
	mov	r3, #36
	str	r2, [r0, #84]
	str	r3, [r0, #80]
.L70:
	mov	r2, #3
	b	.L59
.L79:
	.align	2
.L78:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real9_CB_SetDimensions, .-Real9_CB_SetDimensions
	.align	2
	.global	Real9_CB_GetPicSize
	.type	Real9_CB_GetPicSize, %function
Real9_CB_GetPicSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #84)
	sub	sp, sp, #84
	ldr	ip, .L96
	mov	r6, r1
	mov	r4, r0
	mov	r8, r2
	mov	r7, r3
	ldmia	ip!, {r0, r1, r2, r3}
	sub	r9, fp, #108
	sub	lr, fp, #76
	sub	r10, fp, #124
	add	r5, ip, #16
	stmia	r9!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	add	ip, ip, #48
	stmia	r9, {r0, r1, r2, r3}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r5, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	ldr	ip, [r6, #20]
	sub	ip, ip, #2
	cmp	ip, #1
	stmia	r10, {r0, r1, r2, r3}
	bls	.L94
.L81:
	mov	r1, #3
	mov	r0, r4
	bl	BsShow
	mov	r1, #3
	mov	r5, r0
	mov	r0, r4
	bl	BsSkip
	sub	r3, fp, #44
	add	r5, r3, r5, lsl #2
	ldr	r6, [r5, #-64]
	cmp	r6, #0
	beq	.L84
.L83:
	mov	r1, #3
	mov	r0, r4
	bl	BsShow
	mov	r1, #3
	mov	r9, r0
	mov	r0, r4
	bl	BsSkip
	sub	r3, fp, #44
	add	r3, r3, r9, lsl #2
	ldr	r5, [r3, #-32]
	cmp	r5, #0
	beq	.L95
.L85:
	str	r6, [r8]
	str	r5, [r7]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L84:
	mov	r1, #8
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	mov	r5, r0
	mov	r0, r4
	bl	BsSkip
	cmp	r5, #255
	add	r6, r6, r5, lsl #2
	beq	.L84
	b	.L83
.L94:
	mov	r0, r4
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	beq	.L81
	ldr	r3, [r6, #52]
	str	r3, [r8]
	ldr	r3, [r6, #56]
	str	r3, [r7]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L95:
	mov	r0, r4
	mov	r9, r9, asl #1
	bl	Real9_CB_Get1Bit
	sub	r2, fp, #44
	orr	r0, r0, r9
	and	r3, r0, #3
	add	r3, r2, r3, lsl #2
	ldr	r5, [r3, #-80]
	cmp	r5, #0
	bne	.L85
.L86:
	mov	r1, #8
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	mov	r9, r0
	mov	r0, r4
	bl	BsSkip
	cmp	r9, #255
	add	r5, r5, r9, lsl #2
	beq	.L86
	b	.L85
.L97:
	.align	2
.L96:
	.word	.LANCHOR0+280
	UNWIND(.fnend)
	.size	Real9_CB_GetPicSize, .-Real9_CB_GetPicSize
	.align	2
	.global	Real9_CB_FindNextSliceStartCode
	.type	Real9_CB_FindNextSliceStartCode, %function
Real9_CB_FindNextSliceStartCode:
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
	mov	r5, r0
	bl	BsToNextByte
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #2
	subgt	r6, r6, #2
	movwgt	r7, #7184
	movgt	r4, #0
	movtgt	r7, 29
	bgt	.L101
	b	.L102
.L105:
	bl	BsSkip
	cmp	r4, r6
	beq	.L102
.L101:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, r7
	mov	r0, r5
	bne	.L105
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L102:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_FindNextSliceStartCode, .-Real9_CB_FindNextSliceStartCode
	.align	2
	.global	Real9_CB_SearchBits_IgnoreOnly0
	.type	Real9_CB_SearchBits_IgnoreOnly0, %function
Real9_CB_SearchBits_IgnoreOnly0:
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
	mov	r5, #1
	sub	ip, r1, #1
	mov	r6, r2
	mov	r8, r3
	mov	r9, r1
	mov	r7, r0
	mov	r5, r5, asl ip
	bl	BsShow
	mov	r1, r9
	mov	r4, r0
	mov	r0, r7
	bl	BsSkip
	cmp	r6, r4
	cmpne	r8, #0
	beq	.L107
	ands	r10, r4, r5
	bne	.L107
	ldr	r3, .L113
	add	r9, r3, r9, lsl #2
	ldr	r9, [r9, #360]
	b	.L108
.L109:
	tst	r4, r5
	bne	.L107
.L108:
	mov	r0, r7
	and	r4, r9, r4, asl #1
	bl	Real9_CB_Get1Bit
	add	r10, r10, #1
	orr	r4, r0, r4
	cmp	r6, r4
	cmpne	r8, r10
	bhi	.L109
.L107:
	rsb	r0, r6, r4
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L114:
	.align	2
.L113:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real9_CB_SearchBits_IgnoreOnly0, .-Real9_CB_SearchBits_IgnoreOnly0
	.align	2
	.global	Real9_CB_GetSSC
	.type	Real9_CB_GetSSC, %function
Real9_CB_GetSSC:
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
	ldr	r3, [r1, #12]
	cmp	r3, #1
	beq	.L117
	bl	Real9_CB_FindNextSliceStartCode
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L117:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_GetSSC, .-Real9_CB_GetSSC
	.align	2
	.global	Real9_CB_GetSliceHeader
	.type	Real9_CB_GetSliceHeader, %function
Real9_CB_GetSliceHeader:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 8
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
	ldr	r4, [fp, #8]
	mov	r5, r1
	mov	r7, r2
	mov	r8, r3
	mov	r9, r0
	ldr	r6, [r4, #12]
	cmp	r6, #1
	beq	.L154
	cmp	r1, #0
	beq	.L155
	mov	r2, #0
	str	r2, [r7]
	ldr	r2, [fp, #4]
	mov	r0, #1
	mvn	r3, #0
	str	r3, [r2]
.L143:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L154:
	cmp	r1, #0
	bne	.L120
	ldr	r3, [r4, #96]
	cmn	r3, #1
	beq	.L156
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	bne	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r1, #2
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	ldr	r3, [r4, #92]
	cmp	r3, r6
	beq	.L123
.L133:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L155:
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	bne	.L133
	ldr	r5, [r4, #88]
	mov	r0, r9
	mov	r1, r5
	bl	BsShow
	mov	r1, r5
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	str	r6, [r7]
	ldr	r3, [r4, #88]
	cmp	r3, #11
	bls	.L138
	mov	r0, r9
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	bne	.L133
.L138:
	mov	r1, #5
	mov	r0, r9
	bl	BsShow
	mov	r1, #5
	mov	r5, r0
	mov	r0, r9
	bl	BsSkip
	ldr	r3, [fp, #4]
	cmp	r5, #31
	str	r5, [r3]
	bgt	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r1, #2
	mov	r5, r0
	mov	r0, r9
	bl	BsSkip
	str	r5, [r4, #60]
	mov	r0, r9
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	mov	r4, r0
	bne	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r1, #2
	mov	r5, r0
	mov	r0, r9
	bl	BsSkip
	str	r5, [r8]
	mov	r0, r4
	b	.L143
.L156:
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	bne	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r5, r6
	mov	r1, #2
	mov	r10, r0
	mov	r0, r9
	bl	BsSkip
	str	r10, [r4, #92]
.L123:
	mov	r1, #5
	mov	r0, r9
	bl	BsShow
	mov	r1, #5
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	uxtb	r0, r6
	cmp	r0, #31
	strb	r0, [r4, #74]
	bhi	.L133
	mov	r0, r9
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	bne	.L133
	mov	r0, r9
	bl	Real9_CB_Get1Bit
	subs	r10, r0, #0
	bne	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r1, #2
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	str	r6, [r4, #60]
	mov	r1, #1
	mov	r0, r9
	bl	BsShow
	mov	r1, #1
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	adds	r6, r6, #0
	mov	r1, #13
	mov	r0, r9
	movne	r6, #1
	cmp	r5, #0
	strb	r6, [r4, #73]
	add	r5, r4, #72
	beq	.L126
	bl	BsShow
	mov	r1, #13
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	ldr	r3, [r4, #92]
	str	r6, [r4, #100]
	cmp	r3, #1
	bls	.L128
	cmp	r3, #2
	ldreq	r2, [r4, #116]
	ldreq	r3, [r4, #120]
	streq	r2, [r4, #124]
	streq	r3, [r4, #128]
.L144:
	mov	r1, r5
	sub	r3, fp, #48
	sub	r2, fp, #52
	mov	r0, r9
	bl	Real9_CB_GetPicSize
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	movw	r1, #8144
	sub	r0, r2, #48
	cmp	r0, r1
	str	r2, [r4, #116]
	str	r2, [r4, #24]
	str	r3, [r4, #120]
	str	r3, [r4, #20]
	bhi	.L133
	sub	r3, r3, #48
	cmp	r3, r1
	bhi	.L133
	mov	r0, r4
	bl	Real9_CB_SetDimensions
.L134:
	ldr	r5, [r4, #88]
	mov	r0, r9
	mov	r1, r5
	bl	BsShow
	mov	r1, r5
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	str	r6, [r4, #96]
.L120:
	ldr	r2, [r4, #96]
	mov	r3, #0
	ldr	r1, [fp, #4]
	mov	r0, #1
	str	r2, [r7]
	ldrb	r2, [r4, #74]	@ zero_extendqisi2
	str	r2, [r1]
	str	r3, [r8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L126:
	bl	BsShow
	mov	r1, #13
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	ldr	r3, [r4, #100]
	cmp	r3, r6
	bne	.L133
	sub	r3, fp, #48
	sub	r2, fp, #52
	mov	r1, r5
	mov	r0, r9
	bl	Real9_CB_GetPicSize
	ldr	r2, [r4, #116]
	ldr	r3, [fp, #-52]
	cmp	r2, r3
	bne	.L133
	ldr	r2, [r4, #120]
	ldr	r3, [fp, #-48]
	cmp	r2, r3
	bne	.L133
	b	.L134
.L128:
	str	r10, [r4, #124]
	str	r10, [r4, #128]
	b	.L144
	UNWIND(.fnend)
	.size	Real9_CB_GetSliceHeader, .-Real9_CB_GetSliceHeader
	.align	2
	.global	Real9_CB_GetPictureHeader
	.type	Real9_CB_GetPictureHeader, %function
Real9_CB_GetPictureHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	ldr	r3, [r1, #12]
	mov	r4, r1
	mov	r5, r0
	cmp	r3, #1
	beq	.L181
	ldr	r3, .L184
	mov	r2, #136
	mov	r1, #0
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	mov	r1, #16
	mov	r0, r5
	bl	BsShow
	mov	r1, #16
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	movw	r3, #21845
	cmp	r6, r3
	bne	.L177
	mov	r1, #16
	mov	r0, r5
	bl	BsShow
	mov	r1, #16
	mov	r7, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r7, r6
	bne	.L177
	mov	r0, r5
	sub	r1, fp, #32
	bl	Real9_CB_GetVLCBits
	cmp	r0, #30
	bls	.L177
	ldr	r3, [fp, #-32]
	ands	r2, r3, #1
	bne	.L177
	tst	r3, #2
	mov	r0, r5
	strne	r2, [r4, #24]
	moveq	r1, #176
	moveq	r2, #144
	streq	r1, [r4, #24]
	sub	r1, fp, #32
	str	r2, [r4, #20]
	ubfx	r2, r3, #2, #5
	ubfx	r3, r3, #7, #8
	str	r2, [r4, #56]
	str	r3, [r4, #44]
	bl	Real9_CB_GetVLCBits
	cmp	r0, #1
	streq	r0, [r4, #16]
	beq	.L171
	cmp	r0, #3
	beq	.L182
	cmp	r0, #5
	bne	.L177
	ldr	r3, [fp, #-32]
	cmp	r3, #0
	bne	.L177
	mov	r3, #2
	str	r3, [r4, #16]
.L171:
	ldr	r3, [r4, #24]
	cmp	r3, #0
	beq	.L183
.L173:
	sub	r3, r3, #48
	movw	r2, #8144
	cmp	r3, r2
	bhi	.L177
	ldr	r3, [r4, #20]
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L177
	mov	r0, r4
	mov	r6, #1
	bl	Real9_CB_SetDimensions
	mov	r1, #2
	mov	r0, r5
	bl	BsShow
	mov	r1, #2
	mov	r7, r0
	mov	r0, r5
	bl	BsSkip
	str	r7, [r4, #60]
.L159:
	ldr	r3, [r4, #24]
	mov	r0, r6
	ldr	r2, [r4, #20]
	add	r3, r3, #15
	add	r2, r2, #15
	mov	r3, r3, lsr #4
	str	r3, [r4, #32]
	mov	r2, r2, lsr #4
	str	r2, [r4, #28]
	mul	r3, r3, r2
	str	r3, [r4, #36]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L182:
	ldr	r3, [fp, #-32]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [r4, #16]
	beq	.L171
.L177:
	mvn	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L181:
	str	r1, [sp, #4]
	mvn	r2, #0
	sub	r3, fp, #32
	str	r2, [r1, #96]
	str	r3, [sp]
	sub	r2, fp, #36
	sub	r3, fp, #40
	mov	r1, #0
	bl	Real9_CB_GetSliceHeader
	cmp	r0, #1
	mvnne	r6, #1
	bne	.L159
	ldr	r3, [r4, #92]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L175
.L162:
	.word	.L161
	.word	.L163
	.word	.L164
	.word	.L165
.L183:
	mov	r1, r4
	mov	r0, r5
	bl	Real9_CB_GetCPFMT
	cmp	r0, #0
	beq	.L177
	ldr	r3, [r4, #24]
	b	.L173
.L165:
	mov	r6, #1
	mov	r3, #2
	str	r3, [r4, #16]
.L160:
	ldr	r3, [r4, #24]
	movw	r2, #8144
	ldrb	lr, [r4, #73]	@ zero_extendqisi2
	sub	r3, r3, #48
	ldrb	ip, [r4, #74]	@ zero_extendqisi2
	ldr	r0, [r4, #100]
	cmp	r3, r2
	ldr	r1, [r4, #104]
	ldr	r3, [r4, #108]
	str	lr, [r4, #52]
	str	ip, [r4, #56]
	str	r0, [r4, #44]
	str	r1, [r4, #64]
	str	r3, [r4, #68]
	bhi	.L177
	ldr	r3, [r4, #20]
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L177
	mov	r0, r4
	bl	Real9_CB_SetDimensions
	b	.L159
.L164:
	mov	r0, #1
	str	r0, [r4, #16]
	mov	r6, r0
	b	.L160
.L163:
	mov	r3, #0
	mov	r6, #1
	str	r3, [r4, #16]
	str	r3, [r4, #76]
	b	.L160
.L161:
	mov	r0, #1
	mov	r3, #0
	str	r0, [r4, #76]
	mov	r6, r0
	str	r3, [r4, #16]
	b	.L160
.L175:
	mvn	r6, #1
	b	.L160
.L185:
	.align	2
.L184:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Real9_CB_GetPictureHeader, .-Real9_CB_GetPictureHeader
	.align	2
	.global	Real9_SetImgFormat
	.type	Real9_SetImgFormat, %function
Real9_SetImgFormat:
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
	add	r5, r0, #53248
	mov	r6, r0
	ldr	r1, [r5, #1552]
	ldr	r0, [r5, #1952]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, [r5, #208]
	mov	lr, #5
	ldrb	r1, [r4, #64]	@ zero_extendqisi2
	mov	ip, #1
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
	mov	ip, #0
	ldr	r3, [r4, #64]
	mov	r1, ip
	bfc	r3, #14, #3
	str	r3, [r4, #64]
	ldrb	lr, [r5, #192]	@ zero_extendqisi2
	mov	r3, r3, lsr #16
	bfi	r3, lr, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r5, #196]
	str	r2, [r4, #56]
	str	r2, [r4, #60]
	str	r3, [r4, #120]
	str	ip, [r4, #52]
	ldr	r3, [r5, #216]
	str	r3, [r4, #68]
	ldr	r3, [r5, #212]
	str	r3, [r4, #72]
	bl	SetAspectRatio
	ldr	r3, [r6]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L192
.L188:
	mov	r2, #9
	mov	r3, #0
	str	r2, [r4, #296]
	mov	r2, #1
	strb	r3, [r4, #284]
	mov	r3, #8
	strb	r2, [r4, #291]
	strb	r2, [r4, #289]
	str	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L192:
	ldr	r3, [r4, #72]
	add	lr, r4, #512
	ldr	r2, [r4, #112]
	add	r3, r3, #15
	ldr	ip, [r4, #36]
	mov	r1, r2, asl #4
	mov	r3, r3, lsr #4
	add	r6, ip, r2
	mul	r3, r3, r1
	add	r5, r3, ip
	str	r5, [r4, #40]
	ldrd	r0, [lr, #-8]
	add	r2, r5, r2
	adds	r0, r0, r3
	adc	r1, r1, r3, asr #31
	strd	r0, [lr]
	str	r5, [r4, #24]
	str	r2, [r4, #32]
	str	r6, [r4, #28]
	str	ip, [r4, #20]
	b	.L188
	UNWIND(.fnend)
	.size	Real9_SetImgFormat, .-Real9_SetImgFormat
	.align	2
	.global	RV9_RecordVFMWState
	.type	RV9_RecordVFMWState, %function
RV9_RecordVFMWState:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	RV9_RecordVFMWState, .-RV9_RecordVFMWState
	.align	2
	.global	Real9_WriteSliceMsg
	.type	Real9_WriteSliceMsg, %function
Real9_WriteSliceMsg:
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
	mov	r2, #44
	add	r3, r0, #53248
	mla	r2, r2, r1, r0
	ldr	r4, [r3, #356]
	add	r1, r1, #1
	add	ip, r2, #120
	add	lr, r2, #128
	str	r4, [r2, #100]
	ldr	r4, [r3, #348]
	str	r4, [r2, #108]
	ldr	r4, [r3, #352]
	str	r4, [r2, #116]
	ldr	r4, [r3, #368]
	str	r4, [r2, #104]
	ldr	r4, [r3, #360]
	str	r4, [r2, #112]
	ldr	r4, [r3, #364]
	str	r4, [r2, #120]
	ldr	r2, [r3, #336]
	str	r2, [ip, #4]
	ldr	r2, [r3, #332]
	str	r2, [ip, #8]
	ldr	r2, [r3, #328]
	str	r2, [lr, #4]
	ldr	r3, [r3, #340]
	str	r3, [lr, #8]
	str	r1, [r0, #40]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_WriteSliceMsg, .-Real9_WriteSliceMsg
	.align	2
	.global	Real9_WritePicMsg
	.type	Real9_WritePicMsg, %function
Real9_WritePicMsg:
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
	add	r3, r0, #53248
	ldr	r2, [r3, #208]
	cmp	r2, #2
	strb	r2, [r0, #8]
	ldr	r2, [r3, #224]
	str	r2, [r0, #12]
	ldr	r2, [r3, #220]
	str	r2, [r0, #16]
	ldr	r2, [r3, #1468]
	str	r2, [r0, #20]
	ldr	r2, [r3, #1472]
	str	r2, [r0, #24]
	ldr	r2, [r3, #248]
	str	r2, [r0, #28]
	ldr	r1, [r3, #372]
	str	r1, [r0, #32]
	ldr	r1, [r3, #376]
	str	r1, [r0, #36]
	strne	r2, [r3, #372]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_WritePicMsg, .-Real9_WritePicMsg
	.align	2
	.global	Real9_WriteReg
	.type	Real9_WriteReg, %function
Real9_WriteReg:
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
	str	r1, [r0, #44]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_WriteReg, .-Real9_WriteReg
	.align	2
	.global	Real9_ModifySliceMsg
	.type	Real9_ModifySliceMsg, %function
Real9_ModifySliceMsg:
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
	ldr	r2, [r0, #136]
	ldr	r3, [r0, #12]
	cmp	r2, #0
	ldr	ip, [r0, #16]
	bne	.L205
	mul	ip, r3, ip
	ldr	r5, [r0, #40]
	cmp	r5, #2
	sub	ip, ip, #1
	bls	.L204
	ldr	r3, [r0, #180]
	sub	lr, r5, #1
	cmp	r3, #0
	cmpgt	ip, r3
	ble	.L205
	mov	r2, r0
	mov	r3, #1
	b	.L206
.L207:
	ldr	r1, [r2, #224]
	add	r2, r2, #44
	cmp	ip, r1
	cmpgt	r1, #0
	ble	.L205
.L206:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L207
.L204:
	cmp	r5, #1
	bls	.L208
	sub	r4, r5, #1
	mov	r3, r0
	mov	r2, #0
	b	.L209
.L210:
	ldr	lr, [r3, #136]
	add	r3, r3, #44
	add	r2, r2, #1
	ldr	r1, [r3, #136]
	cmp	lr, r1
	bge	.L205
.L209:
	cmp	r2, r4
	bne	.L210
	mov	r3, #44
	mla	r2, r3, r2, r0
	ldr	r3, [r2, #136]
	cmp	ip, r3
	cmpge	r3, #0
	ble	.L205
.L208:
	cmp	r5, #0
	beq	.L211
	sub	r7, r5, #1
	mov	r6, r0
	mov	lr, r0
	mov	r4, #0
	b	.L214
.L229:
	cmp	r4, r5
	beq	.L228
.L214:
	cmp	r4, r7
	streq	ip, [lr, #140]
	add	r4, r4, #1
	add	lr, lr, #44
	ldrne	r3, [lr, #136]
	moveq	r1, ip
	subne	r1, r3, #1
	ldr	r3, [lr, #92]
	strne	r1, [lr, #96]
	mov	r2, r3, lsr #31
	cmp	ip, r3
	orrlt	r2, r2, #1
	cmp	r3, r1
	movle	r3, r2
	orrgt	r3, r2, #1
	orr	r3, r3, r1, lsr #31
	cmp	ip, r1
	orrlt	r3, r3, #1
	cmp	r3, #0
	beq	.L229
.L205:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L228:
	ldr	r2, [r0, #100]
	mov	r1, r2
	b	.L217
.L230:
	ldr	r1, [r6, #100]
.L217:
	cmp	r2, r1
	ldr	ip, [r6, #104]
	add	r3, r3, #1
	movcs	r2, r1
	cmp	ip, r2
	bcs	.L215
	ldr	r1, [r6, #120]
	cmp	r1, #0
	movne	r2, ip
.L215:
	cmp	r5, r3
	add	r6, r6, #44
	bne	.L230
	bic	r2, r2, #15
	ldr	lr, [r0, #40]
	str	r2, [r0, #48]
	mov	r3, r0
	mov	ip, #0
	b	.L221
.L231:
	ldr	r4, [r3, #108]
	rsb	r2, r2, r1
	and	r1, r4, #7
	add	r2, r2, r4, lsr #3
	and	r4, r2, #15
	bic	r2, r2, #15
	str	r2, [r3, #100]
	add	r2, r1, r4, lsl #3
	str	r2, [r3, #108]
.L219:
	add	ip, ip, #1
	add	r3, r3, #44
	cmp	lr, ip
	bls	.L220
	ldr	r2, [r0, #48]
.L221:
	ldr	r4, [r3, #104]
	ldr	r1, [r3, #100]
	cmp	r4, #0
	rsb	r6, r2, r4
	beq	.L231
	ldr	r7, [r3, #108]
	rsb	r2, r2, r1
	ldr	r4, [r3, #112]
	and	r5, r7, #7
	add	r2, r2, r7, lsr #3
	add	r1, r6, r4, lsr #3
	and	r7, r2, #15
	and	r6, r1, #15
	and	r4, r4, #7
	add	r5, r5, r7, lsl #3
	bic	r2, r2, #15
	add	r4, r4, r6, lsl #3
	bic	r1, r1, #15
	str	r5, [r3, #108]
	str	r2, [r3, #100]
	str	r4, [r3, #112]
	str	r1, [r3, #104]
	b	.L219
.L211:
	ldr	r3, [r0, #100]
	bic	r3, r3, #15
	str	r3, [r0, #48]
.L220:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_ModifySliceMsg, .-Real9_ModifySliceMsg
	.align	2
	.global	REAL9DEC_Init
	.type	REAL9DEC_Init, %function
REAL9DEC_Init:
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
	mov	r7, r1
	mov	r6, r0
	moveq	r5, #1
	movne	r5, #0
	beq	.L236
	ldr	r3, .L238
	movw	r2, #55216
	mov	r1, r5
	add	r4, r0, #53248
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r6, #54784
	add	r0, r0, #64
	bl	ResetVoQueue
	str	r7, [r6]
	mov	r3, #15
	str	r3, [r4, #372]
	str	r3, [r4, #376]
	add	r2, r6, #8192
	ldr	ip, [r7, #8]
	mov	r3, #1
	strb	r5, [r2, #3192]
	mov	r1, #8192
	mov	r0, r6
	strb	ip, [r2, #3188]
	str	r1, [r4, #232]
	str	r3, [r4, #204]
	strb	r3, [r4, #200]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #1952]
	mov	r0, r5
	beq	.L237
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L236:
	ldr	r1, .L238+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L237:
	ldr	r1, .L238+8
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L239:
	.align	2
.L238:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	.word	.LC11
	UNWIND(.fnend)
	.size	REAL9DEC_Init, .-REAL9DEC_Init
	.align	2
	.global	REAL9DEC_Destroy
	.type	REAL9DEC_Destroy, %function
REAL9DEC_Destroy:
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
	add	r3, r0, #53248
	ldr	r1, .L241
	mov	r0, #2
	ldr	r2, [r3, #1444]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L242:
	.align	2
.L241:
	.word	.LC12
	UNWIND(.fnend)
	.size	REAL9DEC_Destroy, .-REAL9DEC_Destroy
	.global	__aeabi_idiv
	.align	2
	.global	REAL9DEC_Decode
	.type	REAL9DEC_Decode, %function
REAL9DEC_Decode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #220)
	sub	sp, sp, #220
	mov	r2, #136
	mov	r7, r0
	mov	r5, r1
	sub	r0, fp, #180
	mov	r1, #0
	bl	memset
	cmp	r7, #0
	beq	.L390
	add	r4, r7, #53248
	add	r3, r7, #8
	str	r3, [fp, #-200]
	cmp	r5, #0
	ldr	r2, [r4, #308]
	mov	r0, #1
	ldr	r3, [r4, #312]
	mov	r1, #8192
	str	r0, [r4, #204]
	str	r2, [r4, #316]
	str	r2, [fp, #-56]
	str	r2, [fp, #-64]
	str	r3, [r4, #320]
	str	r3, [fp, #-52]
	str	r3, [fp, #-60]
	str	r0, [fp, #-168]
	str	r1, [r4, #232]
	str	r1, [fp, #-140]
	beq	.L391
	ldr	r3, .L411
	mov	r1, #0
	movw	r2, #11356
	ldr	r0, [fp, #-200]
	mov	r6, r1
	ldr	r3, [r3, #48]
	blx	r3
	str	r6, [r4, #1408]
	ldr	r3, [r5, #16]
	add	r1, r7, #8192
	str	r1, [fp, #-204]
	str	r3, [r4, #1428]
	ldr	r3, [r5, #12]
	str	r3, [r4, #1412]
	ldr	r3, [r5]
	str	r3, [r1, #3176]
	ldr	r2, [r5, #16]
	str	r2, [r4, #1416]
	ldrb	r3, [r5, #6]	@ zero_extendqisi2
	strb	r3, [r1, #3180]
	ldrb	r3, [r5, #6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L247
	ldr	r3, [r5, #92]
	str	r3, [r4, #1420]
	ldr	r3, [r5, #80]
	str	r3, [r1, #3184]
	ldr	r3, [r5, #96]
	str	r3, [r4, #1424]
	ldrb	r3, [r5, #86]	@ zero_extendqisi2
	strb	r3, [r1, #3181]
	ldrb	r3, [r5, #86]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L392
.L248:
	movw	r3, #65525
	sub	r1, r2, #10
	movt	r3, 47
	cmp	r1, r3
	bhi	.L384
	ldr	r8, [fp, #-204]
	ldr	r1, [r8, #3176]
	cmp	r1, #0
	beq	.L384
	add	r5, r7, #54784
	add	r5, r5, #32
	mov	r0, r5
	bl	BsInit
	mov	r1, #8
	mov	r0, r5
	bl	BsShow
	mov	r1, #8
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r6, #255
	add	r0, r6, #1
	str	r0, [r4, #380]
	bhi	.L384
	cmp	r0, #0
	beq	.L251
	add	r9, r7, #53504
	movw	r10, #65535
	add	r9, r9, #124
	str	r7, [fp, #-204]
	movt	r10, 47
	mov	r6, #0
	mov	r7, r9
	b	.L252
.L394:
	ldr	r0, [r4, #380]
	cmp	r0, r6
	bls	.L393
.L252:
	mov	r1, #32
	mov	r0, r5
	bl	BsSkip
	mov	r1, #32
	mov	r0, r5
	add	r6, r6, #1
	bl	BsShow
	mov	r1, #32
	mov	r9, r0
	mov	r0, r5
	bl	BsSkip
	rev	r0, r9
	cmp	r0, r10
	str	r0, [r7, #4]!
	ble	.L394
.L384:
	mov	r6, #0
.L372:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L392:
	ldr	r1, [r5, #20]
	ldr	r0, [r4, #1952]
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r5, #100]
	ldr	r0, [r4, #1952]
	bl	SM_ReleaseStreamSeg
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L247:
	ldr	r3, [fp, #-204]
	str	r6, [r4, #1420]
	str	r6, [r3, #3184]
	str	r6, [r4, #1424]
	strb	r6, [r3, #3181]
	b	.L248
.L391:
	ldr	r2, [r4, #1444]
	mov	r6, r5
	ldr	r1, .L411+4
	bl	dprint_vfmw
	b	.L372
.L393:
	ldr	r7, [fp, #-204]
	str	r8, [fp, #-204]
.L251:
	add	r3, r7, #53504
	sub	lr, r0, #1
	add	r3, r3, #128
	mov	r2, #0
	ldr	r8, [fp, #-204]
	b	.L253
.L254:
	ldr	ip, [r3, #4]!
	ldr	r1, [r3, #-4]
	cmp	ip, r1
	ble	.L384
.L253:
	cmp	r2, lr
	add	r2, r2, #1
	bne	.L254
	ldr	r2, [r4, #384]
	mov	r0, r0, asl #3
	add	r1, r0, #1
	movw	r3, #65534
	add	r0, r1, r2
	cmp	r1, #3145728
	sub	r10, r0, #1
	movt	r3, 47
	movlt	r2, #0
	movge	r2, #1
	cmp	r10, r3
	movls	r10, r2
	orrhi	r10, r2, #1
	str	r8, [fp, #-204]
	cmp	r10, #0
	str	r1, [fp, #-208]
	str	r0, [fp, #-212]
	bne	.L384
	ldr	r2, [r4, #1416]
	mov	r3, r0
	rsb	r2, r0, r2
	cmp	r2, #0
	ble	.L384
	ldr	r1, [r8, #3176]
	mov	r0, r5
	add	r1, r1, r3
	bl	BsInit
	sub	r1, fp, #180
	mov	r0, r5
	bl	Real9_CB_GetPictureHeader
	cmp	r0, #1
	mov	r6, r0
	bne	.L395
	ldr	r3, [fp, #-204]
	ldrb	r3, [r3, #3192]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L256
	ldr	r2, [fp, #-148]
	ldr	r3, [r4, #224]
	cmp	r2, r3
	beq	.L396
.L256:
	ldr	r3, .L411+8
	ldr	r10, [r3]
	cmp	r10, #0
	beq	.L258
	ldr	r1, [r4, #220]
	mov	r3, #8
	ldr	r0, [fp, #-152]
	sub	r2, fp, #188
	ldr	lr, [r4, #224]
	ldr	ip, [fp, #-148]
	strh	r1, [fp, #-186]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-182]	@ movhi
	strh	lr, [fp, #-188]	@ movhi
	strh	ip, [fp, #-184]	@ movhi
	ldr	r0, [r4, #1952]
	blx	r10
.L258:
	ldr	r0, [r4, #1952]
	bl	FSP_GetFspType
	subs	ip, r0, #0
	bne	.L259
	sub	r3, fp, #44
	sub	r2, fp, #192
	sub	r1, fp, #196
	ldr	r0, [r4, #1952]
	str	ip, [r3, #-144]!
	str	ip, [fp, #-196]
	str	ip, [fp, #-192]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r7]
	ldr	r2, [r3, #732]
	cmp	r2, #1
	beq	.L397
.L259:
	mov	r2, #1
	ldr	r1, [r4, #1548]
	ldr	r0, [r4, #1952]
	add	r10, r7, #54784
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1544]
	add	r10, r10, #64
	ldr	r0, [r4, #1952]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #1952]
	str	r3, [r4, #1544]
	str	r3, [r4, #1548]
	str	r3, [fp, #-216]
	bl	FSP_GetNullLogicFs
	ldr	r3, [fp, #-216]
	mov	r1, r10
	ldr	r2, [fp, #-204]
	str	r0, [r4, #1548]
	str	r0, [r4, #1544]
	strb	r3, [r2, #3189]
	ldr	r0, [r4, #1952]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [fp, #-148]
	cmp	r2, #512
	ldrhi	r3, [fp, #-152]
	bhi	.L266
	ldr	r1, [fp, #-152]
	cmp	r1, #512
	mov	r3, r1
	bhi	.L266
	ldr	r3, [r7]
	ldr	r0, [r3, #732]
	cmp	r0, #0
	bne	.L268
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L398
.L268:
	ldr	r0, [r4, #1952]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L373
.L379:
	ldr	r2, [fp, #-148]
	ldr	r1, [fp, #-152]
.L270:
	mov	r3, r1
	mov	r0, #1
	ldr	r1, .L411+12
	bl	dprint_vfmw
	sub	r2, fp, #180
	mov	r1, r7
	mov	r0, #6
	bl	Real9_ArrangeVHBMem
	subs	r3, r0, #0
	beq	.L399
.L257:
	add	r3, r7, #53248
	sub	r1, fp, #180
	mov	r2, r3
	ldr	r3, .L411
	add	r2, r2, #192
	str	r2, [fp, #-216]
	ldr	r3, [r3, #52]
	mov	r0, r2
	mov	r2, #136
	blx	r3
	ldr	r3, [r7]
	ldr	r2, [fp, #-204]
	mov	r0, r7
	ldr	r3, [r3, #8]
	strb	r3, [r2, #3188]
	bl	Real9_GetImageBuffer
	subs	r3, r0, #0
	beq	.L400
	ldr	r1, [r4, #1552]
	ldr	r0, [r4, #1952]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L385
	ldr	r0, [r7]
	add	r2, r3, #592
	add	ip, r3, #608
	ldr	r1, .L411+16
	ldrd	r8, [r0, #64]
	mov	r0, #29
	strd	r8, [r2, #-8]
	ldr	lr, [r7]
	ldrd	r8, [lr, #80]
	strd	r8, [r2]
	ldr	lr, [r7]
	ldrd	r8, [lr, #96]
	strd	r8, [ip, #-8]
	mvn	r8, #0
	ldr	ip, [r7]
	mvn	r9, #0
	ldr	ip, [ip, #112]
	str	ip, [r3]
	ldr	ip, [r7]
	ldr	ip, [ip, #116]
	str	ip, [r3, #4]
	ldr	ip, [r7]
	ldr	ip, [ip, #120]
	str	ip, [r3, #8]
	ldr	ip, [r7]
	ldr	ip, [ip, #136]
	str	ip, [r3, #12]
	ldr	r3, [r7]
	strd	r8, [r3, #64]
	ldrd	r8, [r2]
	ldrd	r2, [r2, #-8]
	strd	r8, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #208]
	cmp	r3, #2
	beq	.L387
	cmp	r3, #1
	ldr	r3, [fp, #-204]
	ldrb	r3, [r3, #3189]	@ zero_extendqisi2
	beq	.L401
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #1
.L277:
	ldr	r2, [fp, #-204]
	strb	r3, [r2, #3189]
	ldr	r2, [r4, #1544]
	ldr	r3, [r4, #1548]
	cmp	r2, r3
	beq	.L278
	ldr	r1, .L411+20
	mov	r0, #13
	bl	dprint_vfmw
	mov	r2, #0
	ldr	r1, [r4, #1544]
	ldr	r0, [r4, #1952]
	bl	FSP_SetRef
.L278:
	ldr	r3, [r4, #1548]
	mov	r2, #1
	ldr	r1, [r4, #1552]
	ldr	r0, [r4, #1952]
	str	r3, [r4, #1544]
	str	r1, [r4, #1548]
	bl	FSP_SetRef
	ldr	r1, [r4, #1544]
	ldr	r0, [r4, #1952]
	bl	FSP_RemovePmv
	ldr	r2, [r4, #1552]
	ldr	r1, .L411+24
	mov	r0, #13
	bl	dprint_vfmw
	ldr	r3, [fp, #-204]
	ldrb	r3, [r3, #3188]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L280
	ldr	r3, [r4, #208]
	cmp	r3, #0
	beq	.L380
	cmp	r3, #2
	beq	.L321
	cmp	r3, #1
	beq	.L380
.L280:
	ldr	r1, [r4, #1552]
	ldr	r0, [r4, #1952]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #1544]
	mov	r9, r0
	ldr	r0, [r4, #1952]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #1548]
	mov	r10, r0
	ldr	r0, [r4, #1952]
	bl	FSP_GetLogicFs
	cmp	r9, #0
	cmpne	r10, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	str	r0, [fp, #-220]
	cmp	r3, #0
	bne	.L402
	ldr	r3, [r9, #28]
	cmp	r3, #0
	beq	.L286
	ldr	r2, [r9, #32]
	cmp	r2, #0
	beq	.L286
	ldr	r2, [fp, #-220]
	mov	r0, #13
	ldr	r1, .L411+28
	ldr	r2, [r2, #28]
	cmp	r2, #0
	ldrne	lr, [r2, #8]
	ldreq	lr, [r3, #8]
	str	lr, [r7, #52]
	ldr	r3, [r10, #28]
	cmp	r3, #0
	ldreq	r3, [r9, #28]
	ldr	ip, [r3, #8]
	str	ip, [r7, #56]
	ldr	r3, [r9, #28]
	ldr	r2, [r3, #8]
	str	r2, [r7, #60]
	ldr	r3, [r9, #8]
	str	r3, [r7, #72]
	mov	r8, r3
	ldr	r3, [fp, #-220]
	ldr	r3, [r3, #8]
	str	r3, [r7, #76]
	str	r3, [fp, #-224]
	ldr	r3, [r9, #32]
	ldr	r3, [r3, #8]
	str	r8, [sp, #8]
	ldr	r8, [fp, #-224]
	str	r8, [sp, #12]
	str	r3, [r7, #64]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, [r9, #32]
	ldr	r3, [r3, #24]
	str	r3, [r7, #68]
	ldr	r3, [r9, #32]
	ldr	r3, [r3, #24]
	str	r3, [r4, #1516]
	ldr	r3, [r9, #32]
	ldr	r3, [r3, #60]
	str	r3, [r7, #88]
	ldr	r3, [r9, #32]
	ldr	r3, [r3, #44]
	str	r3, [r7, #92]
	ldr	r3, [r9, #32]
	ldr	r3, [r3, #48]
	str	r3, [r7, #96]
	ldr	r3, [r4, #208]
	cmp	r3, #2
	beq	.L403
.L292:
	ldr	r3, [r4, #236]
	mov	r0, r5
	str	r3, [r9, #16]
	ldr	r3, [r4, #208]
	ldr	r2, [r4, #248]
	cmp	r3, #2
	strb	r3, [r7, #8]
	ldr	r3, [r4, #224]
	str	r2, [fp, #-224]
	str	r3, [r7, #12]
	ldr	r3, [r4, #220]
	str	r3, [r7, #16]
	ldr	r3, [r4, #1468]
	str	r3, [r7, #20]
	ldr	r3, [r4, #1472]
	str	r2, [r7, #28]
	str	r3, [r7, #24]
	ldr	r3, [r4, #372]
	str	r3, [r7, #32]
	ldr	r3, [r4, #376]
	str	r3, [r7, #36]
	strne	r2, [r4, #372]
	bl	BsPos
	ldr	r1, [r4, #380]
	cmp	r1, #1
	ldreq	r9, [r4, #384]
	ldrne	r9, [r4, #384]
	mov	r3, r0, asr #31
	mov	r2, r3, lsr #29
	add	r3, r0, r2
	moveq	r0, r5
	and	r3, r3, #7
	movne	r0, r5
	rsb	r3, r2, r3
	ldreq	r2, [fp, #-208]
	str	r3, [r4, #348]
	ldreq	r3, [r4, #1416]
	ldrne	r3, [r4, #388]
	rsbeq	r3, r2, r3
	rsb	r9, r9, r3
	bl	BsPos
	ldr	r3, [fp, #-212]
	mov	r9, r9, asl #3
	rsb	r0, r0, r9
	ldr	r9, [r4, #1412]
	str	r0, [r4, #352]
	mov	r0, r5
	add	r9, r3, r9
	bl	BsPos
	ldr	r2, [r4, #252]
	mov	r1, #1
	ldr	ip, [r4, #244]
	ldr	lr, [fp, #-224]
	str	r2, [r4, #332]
	str	ip, [r4, #336]
	str	lr, [r4, #328]
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	mov	r3, #0
	add	r0, r9, r0, asr #3
	str	r3, [r4, #360]
	str	r0, [r4, #356]
	str	r3, [r4, #364]
	str	r3, [r4, #368]
	str	r3, [r4, #340]
	str	r0, [r7, #100]
	ldr	r0, [r4, #348]
	str	r0, [r7, #108]
	ldr	r0, [r4, #352]
	str	ip, [r7, #124]
	str	r3, [r7, #104]
	str	r0, [r7, #116]
	str	r3, [r7, #112]
	str	r3, [r7, #120]
	str	r2, [r7, #128]
	str	r3, [r7, #136]
	str	lr, [r7, #132]
	str	r1, [r7, #40]
	ldr	r2, [r4, #380]
	cmp	r2, r1
	bls	.L317
	ldr	r10, [r4, #388]
	movw	r0, #65535
	ldr	r2, [fp, #-208]
	movt	r0, 47
	add	r10, r2, r10
	cmp	r10, r0
	bgt	.L386
	cmp	r10, #0
	ble	.L386
	ldr	r2, [r4, #1416]
	rsb	r2, r10, r2
	cmp	r2, #0
	ble	.L386
	add	ip, r7, #53504
	mov	r9, r1
	add	r1, ip, #132
	str	r6, [fp, #-236]
	sub	ip, fp, #188
	str	r3, [fp, #-232]
	str	ip, [fp, #-212]
	mov	r6, r1
	str	r0, [fp, #-220]
	str	r9, [fp, #-228]
	ldr	r8, [fp, #-204]
	b	.L308
.L309:
	ldr	r3, [r4, #380]
	add	r9, r9, #1
	cmp	r3, r9
	bls	.L404
	ldr	r3, [fp, #-208]
	ldr	r10, [r6, #4]!
	add	r10, r3, r10
	ldr	r3, [fp, #-220]
	cmp	r10, r3
	bgt	.L386
	cmp	r10, #0
	ble	.L386
	ldr	r2, [r4, #1416]
	rsb	r2, r10, r2
	cmp	r2, #0
	ble	.L386
.L308:
	ldr	r1, [r8, #3176]
	mov	r0, r5
	add	r1, r1, r10
	bl	BsInit
	ldr	r3, [fp, #-216]
	sub	r2, fp, #196
	mov	r1, #0
	mov	r0, r5
	str	r3, [sp, #4]
	ldr	r3, [fp, #-212]
	str	r3, [sp]
	sub	r3, fp, #192
	bl	Real9_CB_GetSliceHeader
	cmp	r0, #1
	bne	.L309
	ldr	r3, [r4, #224]
	ldr	r2, [fp, #-196]
	cmp	r3, #0
	str	r2, [fp, #-204]
	beq	.L405
	ldr	r3, [fp, #-188]
	mov	r0, r5
	ldr	r2, [fp, #-224]
	cmp	r3, #0
	movge	r2, r3
	str	r2, [fp, #-224]
	bl	BsPos
	ldr	r1, [r4, #380]
	sub	r1, r1, #1
	cmp	r1, r9
	mov	r3, r0, asr #31
	mov	r2, r3, lsr #29
	add	r3, r0, r2
	and	r3, r3, #7
	rsb	r3, r2, r3
	str	r3, [r4, #348]
	beq	.L406
	cmp	r9, #254
	bhi	.L407
	ldr	r3, [r6, #4]
	mov	r0, r5
	ldr	r2, [r6]
.L383:
	rsb	r3, r2, r3
	mov	r3, r3, asl #3
	str	r3, [fp, #-240]
	bl	BsPos
	ldr	r3, [fp, #-240]
	rsb	r0, r0, r3
	ldr	r3, [r4, #1412]
	str	r0, [r4, #352]
	mov	r0, r5
	add	r10, r10, r3
	bl	BsPos
	ldr	ip, [fp, #-232]
	mov	r3, #44
	ldr	lr, [fp, #-228]
	ldr	r1, [r4, #252]
	str	ip, [r4, #360]
	mla	r3, r3, lr, r7
	str	ip, [r4, #364]
	str	ip, [r4, #368]
	add	lr, lr, #1
	ldr	ip, [fp, #-224]
	str	r1, [r4, #332]
	add	r1, r3, #120
	str	lr, [fp, #-228]
	str	ip, [r4, #328]
	ldr	ip, [fp, #-204]
	str	ip, [r4, #340]
	add	r2, r0, #7
	cmp	r0, #0
	movlt	r0, r2
	ldr	r2, [r4, #244]
	add	r0, r10, r0, asr #3
	str	r0, [r4, #356]
	cmp	lr, #131
	str	r2, [r4, #336]
	add	r2, r3, #128
	str	r0, [r3, #100]
	ldr	r0, [r4, #348]
	str	r0, [r3, #108]
	ldr	r0, [r4, #352]
	str	r0, [r3, #116]
	ldr	r0, [r4, #368]
	str	r0, [r3, #104]
	ldr	r0, [r4, #360]
	str	r0, [r3, #112]
	ldr	r0, [r4, #364]
	str	r0, [r3, #120]
	ldr	r3, [r4, #336]
	str	r3, [r1, #4]
	ldr	r3, [r4, #332]
	str	r3, [r1, #8]
	ldr	r3, [r4, #328]
	str	r3, [r2, #4]
	ldr	r3, [r4, #340]
	str	r3, [r2, #8]
	str	lr, [r7, #40]
	ble	.L309
	mov	r0, r7
	bl	Real9_ModifySliceMsg
	cmp	r0, #1
	bne	.L386
	ldr	r3, [fp, #-200]
	str	r3, [r7, #4]
	b	.L309
.L390:
	ldr	r1, .L411+32
	mov	r0, #1
	mov	r6, r7
	bl	dprint_vfmw
	b	.L372
.L395:
	ldr	r1, .L411+36
	mov	r0, #1
	mov	r6, r10
	bl	dprint_vfmw
	b	.L372
.L266:
	ldr	r1, .L411+40
	mov	r0, #18
	bl	dprint_vfmw
	b	.L384
.L400:
	ldr	r2, [r4, #1444]
	mov	r6, r3
	ldr	r1, .L411+44
	bl	dprint_vfmw
	b	.L372
.L397:
	ldr	r3, [fp, #-188]
	cmp	r3, #0
	bgt	.L262
	ldr	r3, [fp, #-192]
	cmp	r3, #32
	bgt	.L262
	ldr	r3, [r7, #4]
	cmp	r3, #0
	bne	.L262
	ldr	r3, [r4, #1440]
	cmp	r3, #0
	beq	.L259
	ldr	r1, [r4, #224]
	cmp	r1, #0
	beq	.L259
	ldr	lr, [fp, #-152]
	ldr	r0, [r4, #1956]
	cmp	lr, r0
	beq	.L259
	ldr	r0, [fp, #-148]
	ldr	ip, [r4, #1960]
	cmp	r0, ip
	beq	.L259
	ldr	ip, [r4, #220]
	str	r0, [sp, #8]
	mov	r0, r2
	str	lr, [sp, #12]
	stmia	sp, {r1, ip}
	ldr	r1, .L411+48
	bl	dprint_vfmw
	ldr	r3, .L411+8
	ldr	r2, [fp, #-152]
	ldr	r10, [r3]
	ldr	r3, [fp, #-148]
	cmp	r10, #0
	str	r2, [r4, #1956]
	str	r3, [r4, #1960]
	beq	.L259
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #1952]
	blx	r10
	b	.L259
.L396:
	ldr	r2, [fp, #-152]
	ldr	r3, [r4, #220]
	cmp	r2, r3
	bne	.L256
	b	.L257
.L398:
	ldr	r3, [fp, #-204]
	ldrb	r3, [r3, #3192]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L270
.L373:
	mov	r0, r10
	bl	ResetVoQueue
	b	.L379
.L399:
	ldr	r1, .L411+52
	mov	r0, #1
	mov	r6, r3
	bl	dprint_vfmw
	b	.L372
.L387:
	ldr	r3, [fp, #-204]
	ldrb	r3, [r3, #3189]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L386
	ldr	r3, [fp, #-204]
	ldrb	r3, [r3, #3188]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L280
.L321:
	ldr	r3, [r4, #1560]
	cmp	r3, #0
	bne	.L280
.L385:
	mov	r2, #1
	ldr	r1, [r4, #1552]
	ldr	r0, [r4, #1952]
	mov	r6, r3
	bl	FSP_ClearLogicFs
	b	.L372
.L386:
	mov	r2, #1
	ldr	r1, [r4, #1552]
	ldr	r0, [r4, #1952]
	mov	r6, #0
	bl	FSP_ClearLogicFs
	b	.L372
.L380:
	str	r3, [r4, #1560]
	b	.L280
.L401:
	cmp	r3, #0
	movne	r3, #2
	bne	.L277
	b	.L384
.L406:
	ldr	r3, [r4, #1416]
	mov	r0, r5
	ldr	r1, [fp, #-208]
	ldr	r2, [r6]
	rsb	r3, r1, r3
	b	.L383
.L262:
	mvn	r6, #1
	b	.L372
.L402:
	movw	r3, #1896
	ldr	r2, .L411+56
	ldr	r1, .L411+60
	mov	r0, #0
	bl	dprint_vfmw
	mov	r6, #0
	b	.L372
.L404:
	ldr	r6, [fp, #-236]
.L317:
	ldr	r5, [r7, #4]
	mov	r8, #1
	str	r8, [r7, #44]
	cmp	r5, #0
	beq	.L408
	ldr	r3, [r7]
	ldr	r2, [r3, #912]
	cmp	r2, #1
	beq	.L322
.L319:
	cmp	r2, #2
	beq	.L409
.L320:
	ldr	r2, [r3, #600]
	str	r2, [r7, #80]
	ldr	r3, [r3, #652]
	str	r3, [r7, #84]
	b	.L372
.L403:
	ldr	r1, [fp, #-220]
	ldr	r2, [r10, #16]
	ldr	r3, [r4, #236]
	ldr	r10, [r1, #16]
	subs	r3, r3, r2
	rsb	r10, r2, r10
	ldrmi	r2, [r4, #232]
	addmi	r3, r3, r2
	cmp	r10, #0
	ldrlt	r2, [r4, #232]
	addlt	r10, r10, r2
	cmp	r3, r10
	movgt	r3, #0
	cmp	r10, #0
	ble	.L324
	mov	r1, r10
	mov	r0, r3, asl #14
	str	r3, [fp, #-220]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-220]
	mov	r1, r10
	str	r0, [fp, #-224]
	rsb	r0, r3, r10
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
	ldr	r3, [fp, #-220]
	ldr	r2, [fp, #-224]
.L296:
	str	r3, [r4, #1460]
	str	r10, [r4, #1464]
	str	r2, [r4, #1468]
	str	r0, [r4, #1472]
	b	.L292
.L286:
	ldr	r1, [r4, #1552]
	mov	r2, #1
	ldr	r0, [r4, #1952]
	mov	r6, #0
	bl	FSP_ClearLogicFs
	ldr	r1, .L411+64
	mov	r0, r6
	bl	dprint_vfmw
	b	.L372
.L405:
	mov	r2, r0
	ldr	r1, [r4, #1552]
	ldr	r0, [r4, #1952]
	mov	r6, r3
	bl	FSP_ClearLogicFs
	b	.L372
.L324:
	mov	r0, #0
	mov	r2, r0
	b	.L296
.L407:
	movw	r2, #2122
	ldr	r1, .L411+68
	mov	r0, #22
	mov	r6, #0
	bl	dprint_vfmw
	b	.L372
.L409:
	ldr	r2, [r3, #916]
	cmp	r2, #0
	ble	.L320
	ldr	r2, [r7, #4]
	cmp	r2, #0
	beq	.L320
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L320
	mov	r2, #0
	str	r2, [r7, #4]
	ldr	r1, [r4, #1552]
	mov	r6, r2
	ldr	r0, [r4, #1952]
	bl	FSP_SetDisplay
	ldr	r2, [r7]
	mov	r1, r7
	mov	r0, #9
	ldr	r3, [r2, #916]
	sub	r3, r3, #1
	str	r3, [r2, #916]
	bl	ReleasePacket
	b	.L372
.L408:
	mov	r0, r7
	bl	Real9_ModifySliceMsg
	cmp	r0, #1
	bne	.L410
	ldr	r2, [fp, #-200]
	ldr	r3, [r7]
	str	r2, [r7, #4]
	ldr	r2, [r3, #912]
	cmp	r2, #1
	bne	.L319
	ldr	r2, [fp, #-200]
	cmp	r2, #0
	beq	.L320
	mov	r5, r2
.L322:
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L320
	mov	r2, #0
	str	r2, [r7, #4]
	ldr	r1, [r4, #1552]
	mov	r6, r2
	ldr	r0, [r4, #1952]
	bl	FSP_SetDisplay
	mov	r1, r7
	mov	r0, #9
	bl	ReleasePacket
	b	.L372
.L410:
	mov	r2, r8
	ldr	r1, [r4, #1552]
	ldr	r0, [r4, #1952]
	mov	r6, r5
	bl	FSP_ClearLogicFs
	b	.L372
.L412:
	.align	2
.L411:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	g_event_report
	.word	.LC18
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC26
	.word	.LC13
	.word	.LC15
	.word	.LC17
	.word	.LC20
	.word	.LC16
	.word	.LC19
	.word	.LANCHOR0+460
	.word	.LC24
	.word	.LC25
	.word	.LC27
	UNWIND(.fnend)
	.size	REAL9DEC_Decode, .-REAL9DEC_Decode
	.align	2
	.global	REAL9DEC_RecycleImage
	.type	REAL9DEC_RecycleImage, %function
REAL9DEC_RecycleImage:
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
	cmp	r0, #0
	mov	r5, r1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r4, r0, #53248
	mov	r2, #0
	ldr	r0, [r4, #1952]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #1952]
	bl	FSP_GetFsImagePtr
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL9DEC_RecycleImage, .-REAL9DEC_RecycleImage
	.align	2
	.global	REAL9DEC_GetRemainImg
	.type	REAL9DEC_GetRemainImg, %function
REAL9DEC_GetRemainImg:
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
	subs	r4, r0, #0
	beq	.L434
	ldr	r3, [r4]
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L433
	add	r6, r4, #53248
	ldr	r1, [r6, #1548]
	ldr	r0, [r6, #1952]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L433
	ldr	r1, [r6, #1548]
	ldr	r0, [r6, #1952]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L432
.L433:
	add	r5, r4, #54784
	add	r5, r5, #64
.L422:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	GetVoLastImageID
.L432:
	mov	r0, r4
	add	r5, r4, #54784
	bl	Real9_SetImgFormat
	add	r5, r5, #64
	mov	r3, #1
	str	r3, [r7, #180]
	mov	r2, r3
	ldr	r1, [r6, #1548]
	ldr	r0, [r6, #1952]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #1952]
	mov	r2, r4
	mov	r3, r5
	str	r7, [sp]
	mov	r1, #9
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L420
	mov	r2, #0
	ldr	r1, [r6, #1548]
	ldr	r0, [r6, #1952]
	bl	FSP_SetDisplay
	b	.L422
.L420:
	ldr	r3, [r7, #152]
	cmp	r3, #100
	bhi	.L422
	ldr	r3, [r7, #68]
	cmp	r3, #31
	bls	.L422
	ldr	r3, [r7, #72]
	cmp	r3, #31
	movhi	r0, #0
	bls	.L422
.L429:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L434:
	ldr	r1, .L435
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L429
.L436:
	.align	2
.L435:
	.word	.LC13
	UNWIND(.fnend)
	.size	REAL9DEC_GetRemainImg, .-REAL9DEC_GetRemainImg
	.align	2
	.global	REAL9DEC_VDMPostProc
	.type	REAL9DEC_VDMPostProc, %function
REAL9DEC_VDMPostProc:
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
	subs	r5, r0, #0
	mov	r6, r1
	mov	r7, r2
	beq	.L462
	mov	r2, r1
	mov	r0, #22
	ldr	r1, .L465
	add	r4, r5, #53248
	bl	dprint_vfmw
	ldr	r3, [r5, #4]
	mov	r1, r5
	mov	r0, #9
	add	r8, r5, #8192
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	strb	r2, [r4, #192]
	ldr	r3, [r3, #72]
	str	r3, [r4, #196]
	bl	ReleasePacket
	ldr	r1, [r4, #1552]
	ldr	r0, [r4, #1952]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L439
	ldr	r3, [r4, #208]
	cmp	r3, #2
	andne	r7, r7, #31
	strb	r3, [r8, #3190]
	strne	r7, [r4, #376]
	cmp	r6, #0
	movlt	r6, #0
	blt	.L441
	cmp	r6, #100
	movge	r6, #100
.L441:
	str	r6, [r0, #152]
	mov	r0, #22
	ldr	r1, .L465+4
	bl	dprint_vfmw
	mov	r0, r5
	bl	Real9_SetImgFormat
	ldrb	r3, [r8, #3188]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L444
	ldr	r3, [r5]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	bne	.L444
	ldr	r3, [r4, #208]
	cmp	r3, #2
	beq	.L444
	ldrb	r3, [r8, #3189]	@ zero_extendqisi2
	cmp	r3, #1
	ldrhi	r1, [r4, #1544]
	mvnls	r1, #0
	cmn	r1, #1
	str	r1, [r4, #1556]
	beq	.L446
.L464:
	ldr	r0, [r4, #1952]
	bl	FSP_GetFsImagePtr
	ldr	r6, [r4, #1556]
	mov	r1, r6
	mov	r7, r0
	ldr	r0, [r4, #1952]
	bl	FSP_GetRef
	mov	r2, r6
	ldr	r1, .L465+8
	mov	r3, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #1556]
	ldr	r0, [r4, #1952]
	bl	FSP_SetDisplay
	add	r3, r5, #54784
	ldr	r0, [r4, #1952]
	add	r3, r3, #64
	str	r7, [sp]
	mov	r2, r5
	mov	r1, #9
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L463
.L446:
	ldr	r3, [r4, #1444]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r4, #1444]
.L439:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L444:
	ldr	r1, [r4, #1552]
	cmn	r1, #1
	str	r1, [r4, #1556]
	bne	.L464
	b	.L446
.L463:
	ldr	r0, [r4, #1952]
	mov	r2, #0
	ldr	r1, [r4, #1556]
	bl	FSP_SetDisplay
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L462:
	ldr	r1, .L465+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L466:
	.align	2
.L465:
	.word	.LC28
	.word	.LC29
	.word	.LC30
	.word	.LC13
	UNWIND(.fnend)
	.size	REAL9DEC_VDMPostProc, .-REAL9DEC_VDMPostProc
	.align	2
	.global	REAL9DEC_GetImageBuffer
	.type	REAL9DEC_GetImageBuffer, %function
REAL9DEC_GetImageBuffer:
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
	beq	.L474
	add	r4, r5, #53248
	ldr	r0, [r4, #1952]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #1952]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L475
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L475:
	add	r1, r5, #54784
	ldr	r0, [r4, #1952]
	add	r1, r1, #64
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L474:
	ldr	r1, .L476
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L477:
	.align	2
.L476:
	.word	.LC13
	UNWIND(.fnend)
	.size	REAL9DEC_GetImageBuffer, .-REAL9DEC_GetImageBuffer
	.align	2
	.global	REAL9DEC_Support
	.type	REAL9DEC_Support, %function
REAL9DEC_Support:
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
	cmp	r0, #0
	movne	r3, #1
	strne	r3, [r0]
	ldmnefd	sp, {fp, sp, pc}
	ldr	r1, .L480
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L481:
	.align	2
.L480:
	.word	.LC31
	UNWIND(.fnend)
	.size	REAL9DEC_Support, .-REAL9DEC_Support
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	gs_VLCDecodeTable, %object
	.size	gs_VLCDecodeTable, 256
gs_VLCDecodeTable:
	.byte	-128
	.byte	-127
	.byte	112
	.byte	112
	.byte	-126
	.byte	-125
	.byte	113
	.byte	113
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	-124
	.byte	-123
	.byte	114
	.byte	114
	.byte	-122
	.byte	-121
	.byte	115
	.byte	115
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	-120
	.byte	-119
	.byte	116
	.byte	116
	.byte	-118
	.byte	-117
	.byte	117
	.byte	117
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	-116
	.byte	-115
	.byte	118
	.byte	118
	.byte	-114
	.byte	-113
	.byte	119
	.byte	119
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.type	MBA_FieldWidth, %object
	.size	MBA_FieldWidth, 24
MBA_FieldWidth:
	.word	6
	.word	7
	.word	9
	.word	11
	.word	13
	.word	14
.LC0:
	.word	160
	.word	176
	.word	240
	.word	320
	.word	352
	.word	640
	.word	704
	.word	0
.LC1:
	.word	120
	.word	132
	.word	144
	.word	240
	.word	288
	.word	480
	.word	0
	.word	0
.LC2:
	.word	180
	.word	360
	.word	576
	.word	0
	.type	GetBitsMask, %object
	.size	GetBitsMask, 100
GetBitsMask:
	.word	0
	.word	1
	.word	3
	.word	7
	.word	15
	.word	31
	.word	63
	.word	127
	.word	255
	.word	511
	.word	1023
	.word	2047
	.word	4095
	.word	8191
	.word	16383
	.word	32767
	.word	65535
	.word	131071
	.word	262143
	.word	524287
	.word	1048575
	.word	2097151
	.word	4194303
	.word	8388607
	.word	16777215
	.type	__FUNCTION__.13869, %object
	.size	__FUNCTION__.13869, 16
__FUNCTION__.13869:
	.ascii	"REAL9DEC_Decode\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC3:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"image size abnormal (%dx%d) in MB\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"real9 actual frame size(%dx%d) exeed max config(%dx" )
	ASCII(.ascii	"%d)\012\000" )
.LC9:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"ERROR: Invalid packet pointer!\012\000" )
.LC11:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC12:
	ASCII(.ascii	"Decoding quits at frm %d\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"pCtx is NULL!\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
.LC15:
	ASCII(.ascii	"Real9_CB_GetPictureHeader Error!\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"pic width/height to large,MbWidth = %d, MbHeight = " )
	ASCII(.ascii	"%d\000" )
	.space	2
.LC18:
	ASCII(.ascii	"new seq size %d * %d\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"Real9_ArrangeVHBMem err\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"Fatal Error: frm%d, get image buffer failed\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"++++++++++ ref %d\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"CurFsID abnormal!,%s %d (NULL == pCur) || (NULL == " )
	ASCII(.ascii	"pFwd) || (NULL == pBwd)!!\012\000" )
	.space	2
.LC25:
	ASCII(.ascii	"CurFsID abnormal!\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p," )
	ASCII(.ascii	"%p,%p,%p,%p\012\000" )
.LC27:
	ASCII(.ascii	"line:%d! i > (RV9_MAX_SLC_PARAM_NUM - 2)\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"DEBUG: DEC over\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"flag is NULL!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
