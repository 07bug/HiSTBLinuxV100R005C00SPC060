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
	.file	"real8.c"
	.text
	.align	2
	.global	Real8_CB_GetBits
	.type	Real8_CB_GetBits, %function
Real8_CB_GetBits:
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
	.size	Real8_CB_GetBits, .-Real8_CB_GetBits
	.align	2
	.global	Real8_CB_Get1Bit
	.type	Real8_CB_Get1Bit, %function
Real8_CB_Get1Bit:
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
	.size	Real8_CB_Get1Bit, .-Real8_CB_Get1Bit
	.align	2
	.global	Real8_CB_GetVLCBits
	.type	Real8_CB_GetVLCBits, %function
Real8_CB_GetVLCBits:
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
	.size	Real8_CB_GetVLCBits, .-Real8_CB_GetVLCBits
	.align	2
	.global	Real8_GetImageBuffer
	.type	Real8_GetImageBuffer, %function
Real8_GetImageBuffer:
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
	ldr	r0, [r4, #1960]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #1564]
	blt	.L16
	mov	r1, r0
	ldr	r0, [r4, #1960]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L17
	ldr	r2, [r4, #1564]
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
	ldr	r1, [r4, #1560]
	ldr	r0, [r4, #1960]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1556]
	mov	r5, #0
	ldr	r0, [r4, #1960]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #1556]
	str	r5, [r4, #1560]
	ldr	r0, [r4, #1960]
	bl	FSP_GetNullLogicFs
	add	r1, r6, #54784
	add	r1, r1, #72
	str	r0, [r4, #1560]
	str	r0, [r4, #1556]
	strb	r5, [r7, #3191]
	ldr	r0, [r4, #1960]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L17:
	mov	r2, #516
	ldr	r1, .L18+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L19:
	.align	2
.L18:
	.word	.LC6
	.word	.LC7
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	Real8_GetImageBuffer, .-Real8_GetImageBuffer
	.align	2
	.global	Real8_ArrangeVHBMem
	.type	Real8_ArrangeVHBMem, %function
Real8_ArrangeVHBMem:
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
	ldr	r2, [r2, #104]
	mov	r5, r1
	ldr	r3, [r4, #100]
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
	ldr	r7, [r4, #96]
	mov	r10, #5
	ldr	r8, [r4, #92]
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
	ldr	r2, [r4, #96]
	ldr	r3, [r4, #92]
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
	ldr	r0, [r4, #1960]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	movne	r0, #0
	bne	.L47
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r4, #1960]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L49
	cmp	r0, #0
	addeq	r5, r5, #8192
	moveq	r3, #1
	moveq	r0, r3
	streqb	r3, [r5, #3188]
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
	ldr	r2, [r4, #96]
	ldr	r0, [r1, #692]
	ldr	r3, [r4, #92]
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
	ldr	r2, [r4, #96]
	ldr	r7, [r1, #692]
	ldr	r3, [r4, #92]
	cmp	r2, r7
	ldr	r8, [r1, #696]
	bhi	.L28
	cmp	r3, r8
	bhi	.L28
	add	r3, r5, #8192
	ldrb	r0, [r3, #3188]	@ zero_extendqisi2
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
	add	r0, r0, #72
	bl	ResetVoQueue
	b	.L40
.L51:
	.align	2
.L50:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	Real8_ArrangeVHBMem, .-Real8_ArrangeVHBMem
	.align	2
	.global	Real8_CB_GetCPFMT
	.type	Real8_CB_GetCPFMT, %function
Real8_CB_GetCPFMT:
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
	str	r4, [r6, #96]
	bl	Real8_CB_Get1Bit
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
	str	r7, [r6, #92]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_CB_GetCPFMT, .-Real8_CB_GetCPFMT
	.align	2
	.global	Real8_CB_SetDimensions
	.type	Real8_CB_SetDimensions, %function
Real8_CB_SetDimensions:
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
	ldr	r3, [r0, #96]
	ldr	r2, [r0, #92]
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
	str	r3, [r0, #36]
	mul	r3, r3, r2
	str	r2, [r0, #32]
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
	str	r3, [r0, #40]
	ldmfd	sp, {fp, sp, pc}
.L77:
	cmp	r2, #1152
	bne	.L58
	mov	r2, #88
	mov	r3, #72
	str	r2, [r0, #36]
	str	r3, [r0, #32]
.L72:
	mov	r2, #4
	b	.L59
.L73:
	cmp	r2, #96
	bne	.L58
	mov	r2, #8
	mov	r3, #6
	str	r2, [r0, #36]
	mov	r2, #0
	str	r3, [r0, #32]
	b	.L59
.L74:
	cmp	r2, #144
	bne	.L58
	mov	r2, #11
	mov	r3, #9
	str	r2, [r0, #36]
	str	r3, [r0, #32]
.L68:
	mov	r2, #1
	b	.L59
.L75:
	cmp	r2, #288
	bne	.L58
	mov	r2, #22
	mov	r3, #18
	str	r2, [r0, #36]
	str	r3, [r0, #32]
.L69:
	mov	r2, #2
	b	.L59
.L76:
	cmp	r2, #576
	bne	.L58
	mov	r2, #44
	mov	r3, #36
	str	r2, [r0, #36]
	str	r3, [r0, #32]
.L70:
	mov	r2, #3
	b	.L59
.L79:
	.align	2
.L78:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real8_CB_SetDimensions, .-Real8_CB_SetDimensions
	.align	2
	.global	Real8_CB_GetPicSize
	.type	Real8_CB_GetPicSize, %function
Real8_CB_GetPicSize:
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
	ldr	ip, [r6, #32]
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
	bl	Real8_CB_Get1Bit
	cmp	r0, #0
	beq	.L81
	ldr	r3, [r6, #64]
	str	r3, [r8]
	ldr	r3, [r6, #68]
	str	r3, [r7]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L95:
	mov	r0, r4
	mov	r9, r9, asl #1
	bl	Real8_CB_Get1Bit
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
	.size	Real8_CB_GetPicSize, .-Real8_CB_GetPicSize
	.align	2
	.global	Real8_CB_FindNextSliceStartCode
	.type	Real8_CB_FindNextSliceStartCode, %function
Real8_CB_FindNextSliceStartCode:
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
	movgt	r4, #0
	bgt	.L101
	b	.L102
.L107:
	bl	BsSkip
	cmp	r4, r6
	beq	.L102
.L101:
	mov	r1, #17
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L107
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L102:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_CB_FindNextSliceStartCode, .-Real8_CB_FindNextSliceStartCode
	.align	2
	.global	Real8_CB_SearchBits_IgnoreOnly0
	.type	Real8_CB_SearchBits_IgnoreOnly0, %function
Real8_CB_SearchBits_IgnoreOnly0:
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
	beq	.L109
	ands	r10, r4, r5
	bne	.L109
	ldr	r3, .L115
	add	r9, r3, r9, lsl #2
	ldr	r9, [r9, #360]
	b	.L110
.L111:
	tst	r4, r5
	bne	.L109
.L110:
	mov	r0, r7
	and	r4, r9, r4, asl #1
	bl	Real8_CB_Get1Bit
	add	r10, r10, #1
	orr	r4, r0, r4
	cmp	r6, r4
	cmpne	r8, r10
	bhi	.L111
.L109:
	rsb	r0, r6, r4
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L116:
	.align	2
.L115:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real8_CB_SearchBits_IgnoreOnly0, .-Real8_CB_SearchBits_IgnoreOnly0
	.align	2
	.global	Real8_CB_SetRPRSizes
	.type	Real8_CB_SetRPRSizes, %function
Real8_CB_SetRPRSizes:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	ldr	lr, .L118
	sub	r3, fp, #28
	mov	r4, r0
	mov	r5, r1
	mov	r7, r2
	add	r6, r3, r1, lsl #2
	sub	ip, fp, #64
	ldmia	lr!, {r0, r1, r2, r3}
	str	r5, [r4, #24]
	str	r7, [r4, #20]
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	lr, [lr]
	stmia	ip!, {r0, r1, r2, r3}
	str	lr, [ip]
	ldr	r3, [r6, #-36]
	str	r3, [r4, #16]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L119:
	.align	2
.L118:
	.word	.LANCHOR0+460
	UNWIND(.fnend)
	.size	Real8_CB_SetRPRSizes, .-Real8_CB_SetRPRSizes
	.align	2
	.global	Real8_CB_GetSSC
	.type	Real8_CB_GetSSC, %function
Real8_CB_GetSSC:
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
	bl	Real8_CB_FindNextSliceStartCode
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_CB_GetSSC, .-Real8_CB_GetSSC
	.align	2
	.global	Real8_CB_GetSliceHeader
	.type	Real8_CB_GetSliceHeader, %function
Real8_CB_GetSliceHeader:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [fp, #8]
	mov	r5, r2
	mov	r7, r3
	mov	r6, r0
	ldr	ip, [r4, #84]
	cmp	ip, #1
	beq	.L155
	cmp	r1, #0
	beq	.L156
	mov	r2, #0
	str	r2, [r5]
	ldr	r2, [fp, #4]
	mvn	r3, #0
	mov	r0, #1
	str	r3, [r2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L155:
	cmp	r1, #0
	bne	.L124
	mov	r1, #3
	ldr	r9, [r4, #48]
	bl	BsShow
	mov	r1, #3
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	cmp	r8, #7
	bhi	.L127
	ldr	r3, .L159
	add	r8, r3, r8, lsl #2
	ldr	r3, [r8, #496]
	cmp	r3, #2
	bhi	.L127
	cmn	r9, #1
	mov	r1, #2
	mov	r0, r6
	movne	r9, #0
	moveq	r9, #1
	cmp	r9, #0
	bne	.L157
	bl	BsShow
	mov	r1, #2
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [r4, #44]
	cmp	r3, r8
	bne	.L127
.L129:
	mov	r0, r6
	bl	Real8_CB_Get1Bit
	cmp	r0, #0
	bne	.L127
	mov	r1, #5
	mov	r0, r6
	bl	BsShow
	mov	r1, #5
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	uxtb	r0, r8
	cmp	r0, #31
	strb	r0, [r4, #14]
	bhi	.L127
	mov	r1, #1
	mov	r0, r6
	bl	BsShow
	mov	r1, #1
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	adds	r8, r8, #0
	mov	r1, #13
	mov	r0, r6
	movne	r8, #1
	cmp	r9, #0
	strb	r8, [r4, #13]
	beq	.L130
	bl	BsShow
	mov	r1, #13
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r8, [r4, #16]
	str	r9, [r4, #52]
	cmp	r8, #0
	beq	.L148
	mov	r1, r8
	mov	r0, r6
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [r4, #20]
	str	r9, [r4, #64]
	cmp	r3, #0
	beq	.L127
	add	r1, r3, r9, lsl #3
	ldr	r2, [r3, r9, asl #3]
	mov	r0, r4
	ldr	r3, [r1, #4]
	str	r2, [r4, #68]
	str	r2, [r4, #96]
	str	r3, [r4, #72]
	str	r3, [r4, #92]
	bl	Real8_CB_SetDimensions
.L148:
	ldr	r8, [r4, #40]
	mov	r0, r6
	mov	r1, r8
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	mov	r1, #1
	str	r9, [r4, #48]
	mov	r0, r6
	bl	BsShow
	mov	r1, #1
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	strb	r8, [r4, #12]
.L124:
	ldr	r2, [r4, #48]
	mov	r3, #0
	ldr	r1, [fp, #4]
	mov	r0, #1
	str	r2, [r5]
	ldrb	r2, [r4, #14]	@ zero_extendqisi2
	str	r2, [r1]
	str	r3, [r7]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L156:
	bl	Real8_CB_Get1Bit
	cmp	r0, #1
	beq	.L158
.L127:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L158:
	ldr	r8, [r4, #40]
	mov	r0, r6
	mov	r1, r8
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	str	r9, [r5]
	ldr	r3, [r4, #40]
	cmp	r3, #11
	bls	.L140
	mov	r0, r6
	bl	Real8_CB_Get1Bit
	cmp	r0, #1
	bne	.L127
.L140:
	mov	r1, #5
	mov	r0, r6
	bl	BsShow
	mov	r1, #5
	mov	r4, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [fp, #4]
	cmp	r4, #31
	str	r4, [r3]
	bgt	.L127
	mov	r0, r6
	bl	Real8_CB_Get1Bit
	cmp	r0, #1
	mov	r4, r0
	bne	.L127
	mov	r1, #2
	mov	r0, r6
	bl	BsShow
	mov	r1, #2
	mov	r5, r0
	mov	r0, r6
	bl	BsSkip
	str	r5, [r7]
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L157:
	bl	BsShow
	mov	r1, #2
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	str	r8, [r4, #44]
	b	.L129
.L130:
	bl	BsShow
	mov	r1, #13
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [r4, #52]
	cmp	r3, r8
	bne	.L127
	ldr	r8, [r4, #16]
	cmp	r8, #0
	beq	.L152
	mov	r1, r8
	mov	r0, r6
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [r4, #64]
	cmp	r3, r9
	bne	.L127
.L152:
	ldr	r8, [r4, #40]
	mov	r0, r6
	mov	r1, r8
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	mov	r1, #1
	str	r9, [r4, #48]
	mov	r0, r6
	bl	BsShow
	mov	r1, #1
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	ldrb	r3, [r4, #12]	@ zero_extendqisi2
	cmp	r3, r8
	bne	.L127
	b	.L124
.L160:
	.align	2
.L159:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real8_CB_GetSliceHeader, .-Real8_CB_GetSliceHeader
	.align	2
	.global	Real8_CB_GetPictureHeader
	.type	Real8_CB_GetPictureHeader, %function
Real8_CB_GetPictureHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, [r1, #84]
	mov	r4, r1
	mov	r5, r0
	cmp	r3, #1
	beq	.L187
	ldr	r3, .L190
	mov	r2, #148
	mov	r1, #0
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	mov	r1, #24
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r6, #1
	bne	.L180
	mov	r0, r5
	sub	r1, fp, #32
	bl	Real8_CB_GetVLCBits
	cmp	r0, #30
	bls	.L180
	ldr	r3, [fp, #-32]
	ands	r2, r3, #1
	bne	.L180
	tst	r3, #2
	mov	r0, r5
	strne	r2, [r4, #96]
	moveq	r1, #176
	moveq	r2, #144
	streq	r1, [r4, #96]
	sub	r1, fp, #32
	str	r2, [r4, #92]
	ubfx	r2, r3, #2, #5
	ubfx	r3, r3, #7, #8
	str	r2, [r4, #128]
	str	r3, [r4, #116]
	bl	Real8_CB_GetVLCBits
	cmp	r0, #1
	streq	r0, [r4, #88]
	beq	.L175
	cmp	r0, #3
	beq	.L188
	cmp	r0, #5
	bne	.L180
	ldr	r3, [fp, #-32]
	cmp	r3, #0
	bne	.L180
	mov	r3, #2
	str	r3, [r4, #88]
.L175:
	ldr	r3, [r4, #96]
	cmp	r3, #0
	beq	.L189
.L177:
	sub	r3, r3, #48
	movw	r2, #8144
	cmp	r3, r2
	bhi	.L180
.L186:
	ldr	r3, [r4, #92]
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L180
	mov	r0, r4
	bl	Real8_CB_SetDimensions
	mov	r0, #1
.L163:
	ldr	r3, [r4, #96]
	ldr	r2, [r4, #92]
	add	r3, r3, #15
	add	r2, r2, #15
	mov	r3, r3, lsr #4
	str	r3, [r4, #104]
	mov	r2, r2, lsr #4
	str	r2, [r4, #100]
	mul	r3, r3, r2
	str	r3, [r4, #108]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L188:
	ldr	r3, [fp, #-32]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [r4, #88]
	beq	.L175
.L180:
	mvn	r0, #1
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L187:
	str	r1, [sp, #4]
	mvn	r2, #0
	sub	r3, fp, #32
	str	r2, [r1, #48]
	str	r3, [sp]
	sub	r2, fp, #36
	sub	r3, fp, #40
	mov	r1, #0
	bl	Real8_CB_GetSliceHeader
	cmp	r0, #1
	mvnne	r0, #1
	bne	.L163
	ldr	r3, [r4, #44]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L164
.L166:
	.word	.L165
	.word	.L167
	.word	.L168
	.word	.L169
.L189:
	mov	r0, r5
	mov	r1, r4
	bl	Real8_CB_GetCPFMT
	cmp	r0, #0
	beq	.L180
	ldr	r3, [r4, #96]
	b	.L177
.L167:
	mov	r3, #0
	str	r3, [r4, #88]
	str	r3, [r4, #28]
.L164:
	ldr	r3, [r4, #96]
	add	r0, r4, #52
	movw	r2, #8144
	ldrb	r5, [r4, #12]	@ zero_extendqisi2
	sub	r3, r3, #48
	ldrb	lr, [r4, #13]	@ zero_extendqisi2
	cmp	r3, r2
	ldrb	ip, [r4, #14]	@ zero_extendqisi2
	ldmia	r0, {r0, r1, r3}
	str	r5, [r4, #120]
	str	lr, [r4, #124]
	str	ip, [r4, #128]
	str	r0, [r4, #116]
	str	r1, [r4, #136]
	str	r3, [r4, #140]
	bls	.L186
	b	.L180
.L169:
	mov	r3, #2
	str	r3, [r4, #88]
	b	.L164
.L168:
	mov	r3, #1
	str	r3, [r4, #88]
	b	.L164
.L165:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r4, #88]
	str	r3, [r4, #28]
	b	.L164
.L191:
	.align	2
.L190:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Real8_CB_GetPictureHeader, .-Real8_CB_GetPictureHeader
	.align	2
	.global	Real8_SetImgFormat
	.type	Real8_SetImgFormat, %function
Real8_SetImgFormat:
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
	ldr	r1, [r5, #1564]
	ldr	r0, [r5, #1960]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, [r5, #280]
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
	ldr	r3, [r5, #288]
	str	r3, [r4, #68]
	ldr	r3, [r5, #284]
	str	r3, [r4, #72]
	bl	SetAspectRatio
	ldr	r3, [r6]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L198
.L194:
	mov	r3, #8
	mov	r2, #1
	mov	r1, #0
	str	r3, [r4, #296]
	str	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	strb	r1, [r4, #284]
	strb	r2, [r4, #291]
	strb	r2, [r4, #289]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L198:
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
	b	.L194
	UNWIND(.fnend)
	.size	Real8_SetImgFormat, .-Real8_SetImgFormat
	.align	2
	.global	RV8_RecordVFMWState
	.type	RV8_RecordVFMWState, %function
RV8_RecordVFMWState:
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
	.size	RV8_RecordVFMWState, .-RV8_RecordVFMWState
	.align	2
	.global	Real8_WriteSliceMsg
	.type	Real8_WriteSliceMsg, %function
Real8_WriteSliceMsg:
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
	mov	r3, #44
	add	r2, r0, #53248
	mla	r3, r3, r1, r0
	ldr	ip, [r2, #368]
	add	r1, r1, #1
	str	ip, [r3, #104]
	ldr	ip, [r2, #360]
	str	ip, [r3, #112]
	ldr	ip, [r2, #364]
	str	ip, [r3, #120]
	ldr	ip, [r2, #380]
	str	ip, [r3, #108]
	ldr	ip, [r2, #372]
	str	ip, [r3, #116]
	ldr	ip, [r2, #376]
	str	ip, [r3, #124]
	ldr	ip, [r2, #348]
	str	ip, [r3, #128]
	ldr	ip, [r2, #344]
	str	ip, [r3, #132]
	ldr	ip, [r2, #340]
	str	ip, [r3, #136]
	ldr	r2, [r2, #352]
	str	r2, [r3, #140]
	str	r1, [r0, #44]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_WriteSliceMsg, .-Real8_WriteSliceMsg
	.align	2
	.global	Real8_WritePicMsg
	.type	Real8_WritePicMsg, %function
Real8_WritePicMsg:
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
	ldr	r2, [r3, #280]
	cmp	r2, #2
	strb	r2, [r0, #20]
	ldr	r2, [r3, #296]
	str	r2, [r0, #12]
	ldr	r2, [r3, #292]
	str	r2, [r0, #16]
	ldr	r2, [r3, #1480]
	str	r2, [r0, #24]
	ldr	r2, [r3, #1484]
	str	r2, [r0, #28]
	ldr	r2, [r3, #320]
	str	r2, [r0, #32]
	ldr	r1, [r3, #384]
	str	r1, [r0, #36]
	ldr	r1, [r3, #388]
	str	r1, [r0, #40]
	strne	r2, [r3, #384]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_WritePicMsg, .-Real8_WritePicMsg
	.align	2
	.global	Real8_WriteReg
	.type	Real8_WriteReg, %function
Real8_WriteReg:
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
	str	r1, [r0, #48]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_WriteReg, .-Real8_WriteReg
	.align	2
	.global	Real8_ModifySliceMsg
	.type	Real8_ModifySliceMsg, %function
Real8_ModifySliceMsg:
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
	ldr	r2, [r0, #140]
	ldr	r3, [r0, #12]
	cmp	r2, #0
	ldr	ip, [r0, #16]
	bne	.L211
	mul	ip, r3, ip
	ldr	r5, [r0, #44]
	cmp	r5, #2
	sub	ip, ip, #1
	bls	.L210
	ldr	r3, [r0, #184]
	sub	lr, r5, #1
	cmp	r3, #0
	cmpgt	ip, r3
	ble	.L211
	mov	r2, r0
	mov	r3, #1
	b	.L212
.L213:
	ldr	r1, [r2, #228]
	add	r2, r2, #44
	cmp	ip, r1
	cmpgt	r1, #0
	ble	.L211
.L212:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L213
.L210:
	cmp	r5, #1
	bls	.L214
	sub	r4, r5, #1
	mov	r3, r0
	mov	r2, #0
	b	.L215
.L216:
	ldr	lr, [r3, #140]
	add	r3, r3, #44
	add	r2, r2, #1
	ldr	r1, [r3, #140]
	cmp	lr, r1
	bge	.L211
.L215:
	cmp	r2, r4
	bne	.L216
	mov	r3, #44
	mla	r2, r3, r2, r0
	ldr	r3, [r2, #140]
	cmp	ip, r3
	cmpge	r3, #0
	ble	.L211
.L214:
	cmp	r5, #0
	beq	.L217
	sub	r7, r5, #1
	mov	r6, r0
	mov	lr, r0
	mov	r4, #0
	b	.L220
.L235:
	cmp	r4, r5
	beq	.L234
.L220:
	cmp	r4, r7
	streq	ip, [lr, #144]
	add	r4, r4, #1
	add	lr, lr, #44
	ldrne	r3, [lr, #140]
	moveq	r1, ip
	subne	r1, r3, #1
	ldr	r3, [lr, #96]
	strne	r1, [lr, #100]
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
	beq	.L235
.L211:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L234:
	ldr	r2, [r0, #104]
	mov	r1, r2
	b	.L223
.L236:
	ldr	r1, [r6, #104]
.L223:
	cmp	r2, r1
	ldr	ip, [r6, #108]
	add	r3, r3, #1
	movcs	r2, r1
	cmp	ip, r2
	bcs	.L221
	ldr	r1, [r6, #124]
	cmp	r1, #0
	movne	r2, ip
.L221:
	cmp	r5, r3
	add	r6, r6, #44
	bne	.L236
	bic	r2, r2, #15
	ldr	lr, [r0, #44]
	str	r2, [r0, #52]
	mov	r3, r0
	mov	ip, #0
	b	.L227
.L237:
	ldr	r4, [r3, #112]
	rsb	r2, r2, r1
	and	r1, r4, #7
	add	r2, r2, r4, lsr #3
	and	r4, r2, #15
	bic	r2, r2, #15
	str	r2, [r3, #104]
	add	r2, r1, r4, lsl #3
	str	r2, [r3, #112]
.L225:
	add	ip, ip, #1
	add	r3, r3, #44
	cmp	lr, ip
	bls	.L226
	ldr	r2, [r0, #52]
.L227:
	ldr	r4, [r3, #108]
	ldr	r1, [r3, #104]
	cmp	r4, #0
	rsb	r6, r2, r4
	beq	.L237
	ldr	r7, [r3, #112]
	rsb	r2, r2, r1
	ldr	r4, [r3, #116]
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
	str	r5, [r3, #112]
	str	r2, [r3, #104]
	str	r4, [r3, #116]
	str	r1, [r3, #108]
	b	.L225
.L217:
	ldr	r3, [r0, #104]
	bic	r3, r3, #15
	str	r3, [r0, #52]
.L226:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_ModifySliceMsg, .-Real8_ModifySliceMsg
	.align	2
	.global	REAL8DEC_Init
	.type	REAL8DEC_Init, %function
REAL8DEC_Init:
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
	mov	r7, r1
	mov	r6, r0
	moveq	r5, #1
	movne	r5, #0
	beq	.L242
	add	r4, r0, #53248
	ldr	r3, .L244
	movw	r2, #55224
	mov	r1, r5
	ldr	r8, [r4, #1952]
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r6, #54784
	add	r0, r0, #72
	str	r8, [r4, #1952]
	bl	ResetVoQueue
	str	r7, [r6]
	mov	r3, #15
	str	r3, [r4, #384]
	str	r3, [r4, #388]
	add	r2, r6, #8192
	ldr	ip, [r7, #8]
	mov	r3, #1
	strb	r5, [r2, #3188]
	mov	r1, #8192
	mov	r0, r6
	strb	ip, [r2, #3186]
	str	r1, [r4, #304]
	str	r3, [r4, #276]
	strb	r3, [r4, #200]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #1960]
	mov	r0, r5
	beq	.L243
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L242:
	movw	r2, #1524
	ldr	r1, .L244+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L243:
	ldr	r1, .L244+8
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L245:
	.align	2
.L244:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	.word	.LC12
	UNWIND(.fnend)
	.size	REAL8DEC_Init, .-REAL8DEC_Init
	.align	2
	.global	REAL8DEC_Destroy
	.type	REAL8DEC_Destroy, %function
REAL8DEC_Destroy:
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
	beq	.L248
	add	r3, r3, #53248
	ldr	r1, .L249
	mov	r0, #2
	ldr	r2, [r3, #1456]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L248:
	movw	r2, #1575
	ldr	r1, .L249+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L250:
	.align	2
.L249:
	.word	.LC13
	.word	.LC11
	UNWIND(.fnend)
	.size	REAL8DEC_Destroy, .-REAL8DEC_Destroy
	.global	__aeabi_idiv
	.align	2
	.global	REAL8DEC_Decode
	.type	REAL8DEC_Decode, %function
REAL8DEC_Decode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 296
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #316)
	sub	sp, sp, #316
	clz	r9, r1
	mov	r6, r0
	mov	r2, #148
	mov	r5, r1
	sub	r0, fp, #192
	mov	r1, #0
	mov	r9, r9, lsr #5
	bl	memset
	cmp	r6, #0
	movne	r7, r9
	orreq	r7, r9, #1
	sub	r0, fp, #256
	mov	r2, #64
	mov	r1, #0
	bl	memset
	cmp	r7, #0
	bne	.L385
	add	r4, r6, #53248
	cmp	r9, #0
	mov	r0, #1
	mov	r1, #8192
	ldr	r3, [r4, #264]
	ldr	r2, [r4, #260]
	str	r0, [fp, #-108]
	str	r3, [r4, #272]
	str	r3, [fp, #-112]
	str	r3, [fp, #-120]
	add	r3, r6, #8
	str	r0, [r4, #276]
	str	r2, [r4, #268]
	str	r2, [fp, #-116]
	str	r2, [fp, #-124]
	str	r3, [fp, #-308]
	str	r1, [r4, #304]
	str	r1, [fp, #-80]
	bne	.L386
	ldr	r3, .L406
	movw	r2, #11360
	mov	r1, r9
	ldr	r0, [fp, #-308]
	add	r10, r6, #8192
	ldr	r3, [r3, #48]
	blx	r3
	str	r9, [r4, #1420]
	ldr	r3, [r5, #16]
	str	r3, [r4, #1440]
	ldr	r3, [r5, #12]
	str	r3, [r4, #1424]
	ldr	r3, [r5]
	str	r3, [r10, #3176]
	ldr	r2, [r5, #16]
	str	r2, [r4, #1428]
	ldrb	r3, [r5, #6]	@ zero_extendqisi2
	strb	r3, [r10, #3184]
	ldrb	r3, [r5, #6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L255
	ldr	r3, [r5, #92]
	str	r3, [r4, #1432]
	ldr	r3, [r5, #80]
	str	r3, [r10, #3180]
	ldr	r3, [r5, #96]
	str	r3, [r4, #1436]
	ldrb	r3, [r5, #86]	@ zero_extendqisi2
	strb	r3, [r10, #3185]
	ldrb	r3, [r5, #86]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L387
.L256:
	movw	r3, #65460
	sub	r1, r2, #75
	movt	r3, 47
	cmp	r1, r3
	bhi	.L380
	ldr	r1, [r10, #3176]
	cmp	r1, #0
	beq	.L380
	add	r5, r6, #54784
	add	r5, r5, #40
	mov	r0, r5
	bl	BsInit
	mov	r1, #8
	mov	r0, r5
	bl	BsShow
	mov	r1, #8
	mov	r7, r0
	str	r0, [fp, #-304]
	mov	r0, r5
	bl	BsSkip
	cmp	r7, #8
	bhi	.L380
	sub	r8, fp, #260
	sub	r7, fp, #196
.L259:
	mov	r1, #32
	mov	r0, r5
	bl	BsShow
	mov	r1, #32
	mov	r9, r0
	mov	r0, r5
	bl	BsSkip
	rev	r9, r9
	str	r9, [r8, #4]!
	cmp	r8, r7
	bne	.L259
	mov	r1, #8
	mov	r0, r5
	bl	BsShow
	mov	r1, #8
	mov	r7, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r7, #255
	add	r0, r7, #1
	str	r0, [r4, #392]
	bhi	.L380
	cmp	r0, #0
	beq	.L260
	add	r9, r6, #53504
	movw	r8, #65535
	add	r9, r9, #136
	str	r6, [fp, #-312]
	movt	r8, 47
	mov	r7, #0
	mov	r6, r9
	b	.L261
.L389:
	ldr	r0, [r4, #392]
	cmp	r0, r7
	bls	.L388
.L261:
	mov	r1, #32
	mov	r0, r5
	bl	BsSkip
	mov	r1, #32
	mov	r0, r5
	add	r7, r7, #1
	bl	BsShow
	mov	r1, #32
	mov	r9, r0
	mov	r0, r5
	bl	BsSkip
	rev	r0, r9
	cmp	r0, r8
	str	r0, [r6, #4]!
	ble	.L389
.L380:
	mov	r3, #0
	str	r3, [fp, #-304]
	ldr	r0, [fp, #-304]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L387:
	ldr	r1, [r5, #20]
	ldr	r0, [r4, #1960]
	str	r9, [fp, #-304]
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r5, #100]
	ldr	r0, [r4, #1960]
	bl	SM_ReleaseStreamSeg
.L368:
	ldr	r0, [fp, #-304]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L385:
	movw	r2, #1613
	ldr	r1, .L406+4
	mov	r0, #0
	str	r0, [fp, #-304]
	bl	dprint_vfmw
	ldr	r0, [fp, #-304]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L255:
	str	r9, [r4, #1432]
	str	r9, [r10, #3180]
	str	r9, [r4, #1436]
	strb	r9, [r10, #3185]
	b	.L256
.L386:
	ldr	r2, [r4, #1456]
	ldr	r1, .L406+8
	str	r7, [fp, #-304]
	bl	dprint_vfmw
	b	.L368
.L388:
	ldr	r6, [fp, #-312]
.L260:
	add	r3, r6, #53504
	sub	lr, r0, #1
	add	r3, r3, #140
	mov	r2, #0
	b	.L262
.L263:
	ldr	ip, [r3, #4]!
	ldr	r1, [r3, #-4]
	cmp	ip, r1
	ble	.L380
.L262:
	cmp	r2, lr
	add	r2, r2, #1
	bne	.L263
	ldr	r2, [r4, #396]
	mov	r0, r0, asl #3
	add	r1, r0, #66
	movw	r3, #65461
	add	r0, r1, r2
	cmp	r1, #3145728
	sub	r7, r0, #74
	movt	r3, 47
	movlt	r2, #0
	movge	r2, #1
	cmp	r7, r3
	movls	r7, r2
	orrhi	r7, r2, #1
	str	r1, [fp, #-312]
	cmp	r7, #0
	str	r0, [fp, #-316]
	bne	.L380
	ldr	r2, [r4, #1428]
	mov	r3, r0
	rsb	r2, r0, r2
	cmp	r2, #0
	ble	.L380
	ldr	r1, [r10, #3176]
	mov	r0, r5
	sub	r8, fp, #256
	add	r1, r1, r3
	bl	BsInit
	ldr	r3, [fp, #-304]
	ldr	lr, .L406+12
	sub	r2, fp, #44
	sub	ip, fp, #292
	str	r8, [fp, #-172]
	add	r9, r2, r3, lsl #2
	str	r3, [fp, #-168]
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	lr, [lr]
	stmia	ip!, {r0, r1, r2, r3}
	sub	r1, fp, #192
	str	lr, [ip]
	mov	r0, r5
	ldr	r3, [r9, #-248]
	str	r3, [fp, #-176]
	bl	Real8_CB_GetPictureHeader
	cmp	r0, #1
	str	r0, [fp, #-304]
	bne	.L390
	ldrb	r3, [r10, #3188]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L265
	ldr	r8, .L406+16
	ldr	r7, [r8]
	cmp	r7, #0
	beq	.L266
	ldr	lr, [r4, #296]
	sub	r2, fp, #292
	ldr	r1, [r4, #292]
	mov	r3, #8
	ldr	ip, [fp, #-88]
	strh	lr, [r2]	@ movhi
	sub	lr, fp, #288
	sub	lr, lr, #2
	ldr	r0, [fp, #-92]
	strh	r1, [lr]	@ movhi
	sub	lr, fp, #288
	mov	r1, #2
	strh	ip, [lr]	@ movhi
	sub	ip, fp, #284
	sub	ip, ip, #2
	strh	r0, [ip]	@ movhi
	ldr	r0, [r4, #1960]
	blx	r7
.L266:
	ldr	r0, [r4, #1960]
	bl	FSP_GetFspType
	subs	ip, r0, #0
	bne	.L267
	sub	r3, fp, #292
	sub	r2, fp, #296
	sub	r1, fp, #300
	ldr	r0, [r4, #1960]
	str	ip, [fp, #-300]
	str	ip, [fp, #-296]
	str	ip, [fp, #-292]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r6]
	ldr	r2, [r3, #732]
	cmp	r2, #1
	beq	.L391
.L267:
	mov	r2, #1
	ldr	r1, [r4, #1560]
	ldr	r0, [r4, #1960]
	mov	r8, #0
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1556]
	add	r7, r6, #54784
	ldr	r0, [r4, #1960]
	add	r7, r7, #72
	bl	FSP_ClearLogicFs
	ldr	r0, [r4, #1960]
	str	r8, [r4, #1556]
	str	r8, [r4, #1560]
	bl	FSP_GetNullLogicFs
	mov	r1, r7
	str	r0, [r4, #1560]
	str	r0, [r4, #1556]
	strb	r8, [r10, #3191]
	ldr	r0, [r4, #1960]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [fp, #-88]
	cmp	r2, #512
	ldrhi	r1, [fp, #-92]
	bhi	.L274
	ldr	r3, [fp, #-92]
	cmp	r3, #512
	mov	r1, r3
	bhi	.L274
	ldr	r1, [r6]
	ldr	r0, [r1, #732]
	cmp	r0, #0
	bne	.L276
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L392
.L276:
	ldr	r0, [r4, #1960]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L369
.L375:
	ldr	r2, [fp, #-88]
	ldr	r3, [fp, #-92]
.L278:
	ldr	r1, .L406+20
	mov	r0, #1
	bl	dprint_vfmw
	sub	r2, fp, #192
	mov	r1, r6
	mov	r0, #6
	bl	Real8_ArrangeVHBMem
	subs	r3, r0, #0
	beq	.L393
.L265:
	add	r3, r6, #53248
	sub	r1, fp, #192
	mov	r2, r3
	ldr	r3, .L406
	add	r2, r2, #192
	str	r2, [fp, #-324]
	ldr	r3, [r3, #52]
	mov	r0, r2
	mov	r2, #148
	blx	r3
	ldr	r3, [r6]
	mov	r0, r6
	ldr	r3, [r3, #8]
	strb	r3, [r10, #3186]
	bl	Real8_GetImageBuffer
	subs	r3, r0, #0
	beq	.L394
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L381
	ldr	r0, [r6]
	add	r2, r3, #592
	add	ip, r3, #608
	ldr	r1, .L406+24
	ldrd	r8, [r0, #64]
	mov	r0, #29
	strd	r8, [r2, #-8]
	ldr	lr, [r6]
	ldrd	r8, [lr, #80]
	strd	r8, [r2]
	ldr	lr, [r6]
	ldrd	r8, [lr, #96]
	strd	r8, [ip, #-8]
	mvn	r8, #0
	ldr	ip, [r6]
	mvn	r9, #0
	ldr	ip, [ip, #112]
	str	ip, [r3]
	ldr	ip, [r6]
	ldr	ip, [ip, #116]
	str	ip, [r3, #4]
	ldr	ip, [r6]
	ldr	ip, [ip, #120]
	str	ip, [r3, #8]
	ldr	ip, [r6]
	ldr	ip, [ip, #136]
	str	ip, [r3, #12]
	ldr	r3, [r6]
	strd	r8, [r3, #64]
	ldrd	r8, [r2]
	ldrd	r2, [r2, #-8]
	strd	r8, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #280]
	cmp	r3, #2
	beq	.L382
	cmp	r3, #1
	ldrb	r3, [r10, #3191]	@ zero_extendqisi2
	beq	.L395
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #1
.L285:
	strb	r3, [r10, #3191]
	ldr	r2, [r4, #1556]
	ldr	r3, [r4, #1560]
	cmp	r2, r3
	beq	.L286
	ldr	r1, .L406+28
	mov	r0, #13
	bl	dprint_vfmw
	mov	r2, #0
	ldr	r1, [r4, #1556]
	ldr	r0, [r4, #1960]
	bl	FSP_SetRef
.L286:
	ldr	r3, [r4, #1560]
	mov	r2, #1
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	str	r3, [r4, #1556]
	str	r1, [r4, #1560]
	bl	FSP_SetRef
	ldr	r1, [r4, #1556]
	ldr	r0, [r4, #1960]
	bl	FSP_RemovePmv
	ldr	r2, [r4, #1564]
	ldr	r1, .L406+32
	mov	r0, #13
	bl	dprint_vfmw
	ldrb	r3, [r10, #3186]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L288
	ldr	r3, [r4, #280]
	cmp	r3, #0
	bne	.L396
.L376:
	str	r3, [r4, #1572]
.L288:
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #1556]
	mov	r7, r0
	ldr	r0, [r4, #1960]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #1560]
	mov	r8, r0
	ldr	r0, [r4, #1960]
	bl	FSP_GetLogicFs
	cmp	r7, #0
	cmpne	r8, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	str	r0, [fp, #-320]
	cmp	r3, #0
	bne	.L397
	ldr	r3, [r7, #28]
	cmp	r3, #0
	beq	.L295
	ldr	r2, [r7, #32]
	cmp	r2, #0
	beq	.L295
	ldr	r2, [fp, #-320]
	mov	r0, #13
	ldr	r1, .L406+36
	ldr	r2, [r2, #28]
	cmp	r2, #0
	ldrne	lr, [r2, #8]
	ldreq	lr, [r3, #8]
	str	lr, [r6, #56]
	ldr	r3, [r8, #28]
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	ip, [r3, #8]
	str	ip, [r6, #60]
	ldr	r3, [r7, #28]
	ldr	r2, [r3, #8]
	str	r2, [r6, #64]
	ldr	r3, [r7, #8]
	str	r3, [r6, #76]
	mov	r9, r3
	ldr	r3, [fp, #-320]
	ldr	r3, [r3, #8]
	str	r3, [r6, #80]
	str	r3, [fp, #-328]
	ldr	r3, [r7, #32]
	ldr	r3, [r3, #8]
	str	r9, [sp, #8]
	ldr	r9, [fp, #-328]
	str	r9, [sp, #12]
	str	r3, [r6, #68]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, [r7, #32]
	ldr	r3, [r3, #24]
	str	r3, [r6, #72]
	ldr	r3, [r7, #32]
	ldr	r3, [r3, #60]
	str	r3, [r6, #92]
	ldr	r3, [r7, #32]
	ldr	r3, [r3, #44]
	str	r3, [r6, #96]
	ldr	r3, [r7, #32]
	ldr	r3, [r3, #48]
	str	r3, [r6, #100]
	ldr	r3, [r4, #280]
	cmp	r3, #2
	beq	.L398
.L301:
	ldr	r3, [r4, #308]
	mov	r0, r5
	str	r3, [r7, #16]
	ldr	r3, [r4, #280]
	ldr	r2, [r4, #320]
	cmp	r3, #2
	strb	r3, [r6, #20]
	ldr	r3, [r4, #296]
	str	r2, [fp, #-320]
	str	r3, [r6, #12]
	ldr	r3, [r4, #292]
	str	r3, [r6, #16]
	ldr	r3, [r4, #1480]
	str	r3, [r6, #24]
	ldr	r3, [r4, #1484]
	str	r2, [r6, #32]
	str	r3, [r6, #28]
	ldr	r3, [r4, #384]
	str	r3, [r6, #36]
	ldr	r3, [r4, #388]
	str	r3, [r6, #40]
	strne	r2, [r4, #384]
	bl	BsPos
	ldr	r3, [r4, #392]
	ands	r0, r0, #-2147483641
	submi	r0, r0, #1
	mvnmi	r0, r0, asl #29
	mvnmi	r0, r0, lsr #29
	addmi	r0, r0, #1
	cmp	r3, #1
	str	r0, [r4, #360]
	ldreq	r3, [r4, #1428]
	moveq	r0, r5
	ldreq	r2, [fp, #-312]
	movne	r0, r5
	ldrne	r3, [r4, #400]
	ldreq	r7, [r4, #396]
	rsbeq	r3, r2, r3
	ldrne	r7, [r4, #396]
	rsb	r7, r7, r3
	bl	BsPos
	ldr	r3, [fp, #-316]
	mov	r7, r7, asl #3
	rsb	r0, r0, r7
	ldr	r7, [r4, #1424]
	str	r0, [r4, #364]
	mov	r0, r5
	add	r7, r3, r7
	bl	BsPos
	ldr	r2, [r4, #324]
	mov	r1, #1
	ldr	ip, [r4, #316]
	ldr	lr, [fp, #-320]
	str	r2, [r4, #344]
	str	ip, [r4, #348]
	str	lr, [r4, #340]
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	mov	r3, #0
	add	r0, r7, r0, asr #3
	str	r3, [r4, #372]
	str	r0, [r4, #368]
	str	r3, [r4, #376]
	str	r3, [r4, #380]
	str	r3, [r4, #352]
	str	r0, [r6, #104]
	ldr	r0, [r4, #360]
	str	r0, [r6, #112]
	ldr	r0, [r4, #364]
	str	ip, [r6, #128]
	str	r3, [r6, #108]
	str	r0, [r6, #120]
	str	r3, [r6, #116]
	str	r3, [r6, #124]
	str	r2, [r6, #132]
	str	r3, [r6, #140]
	str	lr, [r6, #136]
	str	r1, [r6, #44]
	ldr	r2, [r4, #392]
	cmp	r2, r1
	bls	.L329
	ldr	r8, [r4, #400]
	movw	r0, #65535
	ldr	r2, [fp, #-312]
	movt	r0, 47
	add	r8, r2, r8
	cmp	r8, r0
	bgt	.L315
	cmp	r8, #73
	ble	.L315
	ldr	r2, [r4, #1428]
	rsb	r2, r8, r2
	cmp	r2, #0
	ble	.L315
	add	r7, r6, #53504
	str	r3, [fp, #-336]
	add	r7, r7, #144
	str	r0, [fp, #-328]
	str	r1, [fp, #-316]
	mov	r9, r1
	b	.L318
.L319:
	ldr	r3, [r4, #392]
	add	r9, r9, #1
	cmp	r3, r9
	bls	.L329
	ldr	r3, [fp, #-312]
	ldr	r8, [r7, #4]!
	add	r8, r3, r8
	ldr	r3, [fp, #-328]
	cmp	r8, r3
	bgt	.L315
	cmp	r8, #73
	ble	.L315
	ldr	r2, [r4, #1428]
	rsb	r2, r8, r2
	cmp	r2, #0
	ble	.L315
.L318:
	ldr	r1, [r10, #3176]
	mov	r0, r5
	add	r1, r1, r8
	bl	BsInit
	ldr	r3, [fp, #-324]
	sub	r2, fp, #300
	mov	r1, #0
	mov	r0, r5
	str	r3, [sp, #4]
	sub	r3, fp, #292
	str	r3, [sp]
	sub	r3, fp, #296
	bl	Real8_CB_GetSliceHeader
	cmp	r0, #1
	bne	.L319
	ldr	r3, [r4, #296]
	ldr	r2, [fp, #-300]
	cmp	r3, #0
	str	r2, [fp, #-332]
	beq	.L399
	ldr	r3, [fp, #-292]
	mov	r0, r5
	ldr	r2, [fp, #-320]
	cmp	r3, #0
	movge	r2, r3
	str	r2, [fp, #-320]
	bl	BsPos
	ldr	r1, [r4, #392]
	sub	r1, r1, #1
	cmp	r1, r9
	mov	r3, r0, asr #31
	mov	r2, r3, lsr #29
	add	r3, r0, r2
	and	r3, r3, #7
	rsb	r3, r2, r3
	str	r3, [r4, #360]
	beq	.L400
	cmp	r9, #254
	bhi	.L401
	ldr	r3, [r7, #4]
	mov	r0, r5
	ldr	r2, [r7]
.L379:
	rsb	r3, r2, r3
	mov	r3, r3, asl #3
	str	r3, [fp, #-340]
	bl	BsPos
	ldr	r3, [fp, #-340]
	rsb	r0, r0, r3
	ldr	r3, [r4, #1424]
	str	r0, [r4, #364]
	mov	r0, r5
	add	r8, r8, r3
	bl	BsPos
	ldr	ip, [fp, #-336]
	mov	r3, #44
	ldr	lr, [fp, #-316]
	ldr	r1, [r4, #324]
	str	ip, [r4, #372]
	str	ip, [r4, #376]
	str	ip, [r4, #380]
	mla	r3, r3, lr, r6
	ldr	ip, [fp, #-320]
	str	r1, [r4, #344]
	add	lr, lr, #1
	str	lr, [fp, #-316]
	str	ip, [r4, #340]
	ldr	ip, [fp, #-332]
	str	ip, [r4, #352]
	add	r2, r0, #7
	cmp	r0, #0
	movlt	r0, r2
	ldr	r2, [r4, #316]
	add	r0, r8, r0, asr #3
	str	r0, [r4, #368]
	cmp	lr, #131
	mov	r8, #0
	str	r2, [r4, #348]
	str	r0, [r3, #104]
	ldr	r2, [r4, #360]
	str	r2, [r3, #112]
	ldr	r2, [r4, #364]
	str	r2, [r3, #120]
	ldr	r2, [r4, #380]
	str	r2, [r3, #108]
	ldr	r2, [r4, #372]
	str	r2, [r3, #116]
	ldr	r2, [r4, #376]
	str	r2, [r3, #124]
	ldr	r2, [r4, #348]
	str	r2, [r3, #128]
	ldr	r2, [r4, #344]
	str	r2, [r3, #132]
	ldr	r2, [r4, #340]
	str	r2, [r3, #136]
	ldr	r2, [r4, #352]
	str	r2, [r3, #140]
	str	lr, [r6, #44]
	ble	.L319
	mov	r0, r6
	bl	Real8_ModifySliceMsg
	cmp	r0, #1
	bne	.L402
	ldr	r3, [fp, #-308]
	cmp	r3, #0
	str	r3, [r6, #4]
	beq	.L403
	ldr	r3, [r6]
	ldr	r2, [r3, #912]
	cmp	r2, #1
	beq	.L404
	cmp	r2, #2
	bne	.L319
	ldr	r3, [r3, #916]
	cmp	r3, #0
	ble	.L319
	ldrb	r3, [r6, #20]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L319
	str	r8, [r6, #4]
	mov	r2, r8
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	str	r8, [fp, #-304]
	bl	FSP_SetDisplay
	ldr	r2, [r6]
	mov	r1, r6
	mov	r0, #8
	ldr	r3, [r2, #916]
	sub	r3, r3, #1
	str	r3, [r2, #916]
	bl	ReleasePacket
	b	.L368
.L390:
	ldr	r1, .L406+40
	mov	r0, #1
	str	r7, [fp, #-304]
	bl	dprint_vfmw
	b	.L368
.L274:
	mov	r3, r1
	mov	r0, #18
	ldr	r1, .L406+44
	bl	dprint_vfmw
	b	.L380
.L394:
	ldr	r2, [r4, #1456]
	ldr	r1, .L406+48
	str	r3, [fp, #-304]
	bl	dprint_vfmw
	b	.L368
.L396:
	cmp	r3, #2
	beq	.L331
	cmp	r3, #1
	beq	.L376
	b	.L288
.L392:
	ldrb	r1, [r10, #3188]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L278
.L369:
	mov	r0, r7
	bl	ResetVoQueue
	b	.L375
.L391:
	ldr	r3, [fp, #-292]
	cmp	r3, #0
	bgt	.L270
	ldr	r3, [fp, #-296]
	cmp	r3, #32
	bgt	.L270
	ldr	r3, [r6, #4]
	cmp	r3, #0
	bne	.L270
	ldr	r3, [r4, #1452]
	cmp	r3, #0
	beq	.L267
	ldr	r1, [r4, #296]
	cmp	r1, #0
	beq	.L267
	ldr	lr, [fp, #-92]
	ldr	r0, [r4, #1964]
	cmp	lr, r0
	beq	.L267
	ldr	r0, [fp, #-88]
	ldr	ip, [r4, #1968]
	cmp	r0, ip
	beq	.L267
	ldr	ip, [r4, #292]
	str	r0, [sp, #8]
	mov	r0, r2
	str	lr, [sp, #12]
	stmia	sp, {r1, ip}
	ldr	r1, .L406+52
	bl	dprint_vfmw
	ldr	r7, [r8]
	ldr	r2, [fp, #-92]
	ldr	r3, [fp, #-88]
	cmp	r7, #0
	str	r2, [r4, #1964]
	str	r3, [r4, #1968]
	beq	.L267
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #1960]
	blx	r7
	b	.L267
.L382:
	ldrb	r3, [r10, #3191]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L315
	ldrb	r3, [r10, #3186]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L288
.L331:
	ldr	r3, [r4, #1572]
	cmp	r3, #0
	bne	.L288
.L381:
	mov	r2, #1
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	str	r3, [fp, #-304]
	bl	FSP_ClearLogicFs
	b	.L368
.L393:
	ldr	r1, .L406+56
	mov	r0, #1
	str	r3, [fp, #-304]
	bl	dprint_vfmw
	b	.L368
.L395:
	cmp	r3, #0
	movne	r3, #2
	bne	.L285
.L315:
	mov	r2, #1
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	mov	r3, #0
	str	r3, [fp, #-304]
	bl	FSP_ClearLogicFs
	b	.L368
.L398:
	ldr	r1, [fp, #-320]
	ldr	r3, [r8, #16]
	ldr	r2, [r4, #308]
	ldr	r8, [r1, #16]
	subs	r2, r2, r3
	rsb	r8, r3, r8
	ldrmi	r3, [r4, #304]
	addmi	r2, r2, r3
	cmp	r8, #0
	ldrlt	r3, [r4, #304]
	addlt	r8, r8, r3
	cmp	r2, r8
	movgt	r2, #0
	cmp	r8, #0
	ble	.L334
	mov	r1, r8
	mov	r0, r2, asl #14
	str	r2, [fp, #-320]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-320]
	mov	r1, r8
	str	r0, [fp, #-328]
	rsb	r0, r2, r8
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
	ldr	r2, [fp, #-320]
	ldr	r3, [fp, #-328]
.L305:
	str	r2, [r4, #1472]
	str	r8, [r4, #1476]
	str	r3, [r4, #1480]
	str	r0, [r4, #1484]
	b	.L301
.L397:
	movw	r3, #1929
	ldr	r2, .L406+60
	ldr	r1, .L406+64
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [fp, #-304]
	b	.L368
.L400:
	ldr	r3, [r4, #1428]
	mov	r0, r5
	ldr	r1, [fp, #-312]
	ldr	r2, [r7]
	rsb	r3, r1, r3
	b	.L379
.L399:
	mov	r2, r0
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	str	r3, [fp, #-304]
	bl	FSP_ClearLogicFs
	b	.L368
.L404:
	ldrb	r3, [r6, #20]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L319
	str	r8, [r6, #4]
	mov	r2, r8
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	str	r8, [fp, #-304]
	bl	FSP_SetDisplay
	mov	r1, r6
	mov	r0, #8
	bl	ReleasePacket
	b	.L368
.L403:
	ldr	ip, [fp, #-308]
	movw	r3, #2125
	ldr	r2, .L406+60
	mov	r0, #22
	ldr	r1, .L406+68
	str	ip, [fp, #-304]
	bl	dprint_vfmw
	b	.L368
.L402:
	mov	r2, #1
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	str	r8, [fp, #-304]
	bl	FSP_ClearLogicFs
	b	.L368
.L401:
	movw	r2, #2092
	ldr	r1, .L406+72
	mov	r0, #22
	mov	r3, #0
	str	r3, [fp, #-304]
	bl	dprint_vfmw
	b	.L368
.L270:
	mvn	r3, #1
	str	r3, [fp, #-304]
	b	.L368
.L329:
	ldr	r5, [r6, #4]
	mov	r7, #1
	str	r7, [r6, #48]
	cmp	r5, #0
	beq	.L405
.L312:
	ldr	r3, [r6]
	ldr	r2, [r3, #600]
	str	r2, [r6, #84]
	ldr	r3, [r3, #652]
	str	r3, [r6, #88]
	b	.L368
.L295:
	ldr	r1, [r4, #1564]
	mov	r2, #1
	ldr	r0, [r4, #1960]
	mov	r3, #0
	str	r3, [fp, #-304]
	bl	FSP_ClearLogicFs
	ldr	r1, .L406+76
	mov	r0, #0
	bl	dprint_vfmw
	b	.L368
.L334:
	mov	r0, #0
	mov	r3, r0
	b	.L305
.L405:
	mov	r0, r6
	bl	Real8_ModifySliceMsg
	cmp	r0, #1
	ldreq	r3, [fp, #-308]
	streq	r3, [r6, #4]
	beq	.L312
	mov	r2, r7
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	str	r5, [fp, #-304]
	bl	FSP_ClearLogicFs
	b	.L368
.L407:
	.align	2
.L406:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	.word	.LC14
	.word	.LANCHOR0+460
	.word	g_event_report
	.word	.LC18
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC26
	.word	.LC15
	.word	.LC17
	.word	.LC20
	.word	.LC16
	.word	.LC19
	.word	.LANCHOR0+528
	.word	.LC24
	.word	.LC28
	.word	.LC27
	.word	.LC25
	UNWIND(.fnend)
	.size	REAL8DEC_Decode, .-REAL8DEC_Decode
	.align	2
	.global	REAL8DEC_RecycleImage
	.type	REAL8DEC_RecycleImage, %function
REAL8DEC_RecycleImage:
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
	ldmeqfd	sp, {fp, sp, pc}
	add	r0, r0, #53248
	mov	r2, #0
	ldr	r0, [r0, #1960]
	bl	FSP_SetDisplay
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL8DEC_RecycleImage, .-REAL8DEC_RecycleImage
	.align	2
	.global	REAL8DEC_GetRemainImg
	.type	REAL8DEC_GetRemainImg, %function
REAL8DEC_GetRemainImg:
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
	beq	.L429
	ldr	r3, [r4]
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L428
	add	r6, r4, #53248
	ldr	r1, [r6, #1560]
	ldr	r0, [r6, #1960]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L428
	ldr	r1, [r6, #1560]
	ldr	r0, [r6, #1960]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L427
.L428:
	add	r5, r4, #54784
	add	r5, r5, #72
.L417:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	GetVoLastImageID
.L427:
	mov	r0, r4
	add	r5, r4, #54784
	bl	Real8_SetImgFormat
	add	r5, r5, #72
	mov	r3, #1
	str	r3, [r7, #180]
	mov	r2, r3
	ldr	r1, [r6, #1560]
	ldr	r0, [r6, #1960]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #1960]
	mov	r2, r4
	mov	r3, r5
	str	r7, [sp]
	mov	r1, #8
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L415
	mov	r2, #0
	ldr	r1, [r6, #1560]
	ldr	r0, [r6, #1960]
	bl	FSP_SetDisplay
	b	.L417
.L429:
	movw	r2, #2201
	ldr	r1, .L430
	bl	dprint_vfmw
.L424:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L415:
	ldr	r3, [r7, #152]
	cmp	r3, #100
	bhi	.L417
	ldr	r3, [r7, #68]
	cmp	r3, #31
	bls	.L417
	ldr	r3, [r7, #72]
	cmp	r3, #31
	bhi	.L424
	b	.L417
.L431:
	.align	2
.L430:
	.word	.LC11
	UNWIND(.fnend)
	.size	REAL8DEC_GetRemainImg, .-REAL8DEC_GetRemainImg
	.align	2
	.global	REAL8DEC_VDMPostProc
	.type	REAL8DEC_VDMPostProc, %function
REAL8DEC_VDMPostProc:
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
	beq	.L457
	mov	r2, r1
	mov	r0, #22
	ldr	r1, .L460
	add	r4, r5, #53248
	bl	dprint_vfmw
	ldr	r3, [r5, #4]
	mov	r1, r5
	mov	r0, #8
	add	r8, r5, #8192
	ldrb	r2, [r3]	@ zero_extendqisi2
	strb	r2, [r4, #192]
	ldr	r3, [r3, #76]
	str	r3, [r4, #196]
	bl	ReleasePacket
	ldr	r1, [r4, #1564]
	ldr	r0, [r4, #1960]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L434
	ldr	r3, [r4, #280]
	cmp	r3, #2
	andne	r7, r7, #31
	strb	r3, [r8, #3189]
	strne	r7, [r4, #388]
	cmp	r6, #0
	movlt	r6, #0
	blt	.L436
	cmp	r6, #100
	movge	r6, #100
.L436:
	str	r6, [r0, #152]
	mov	r0, #22
	ldr	r1, .L460+4
	bl	dprint_vfmw
	mov	r0, r5
	bl	Real8_SetImgFormat
	ldrb	r3, [r8, #3186]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L439
	ldr	r3, [r5]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	bne	.L439
	ldr	r3, [r4, #280]
	cmp	r3, #2
	beq	.L439
	ldrb	r3, [r8, #3191]	@ zero_extendqisi2
	cmp	r3, #1
	ldrhi	r1, [r4, #1556]
	mvnls	r1, #0
	cmn	r1, #1
	str	r1, [r4, #1568]
	beq	.L441
.L459:
	ldr	r0, [r4, #1960]
	bl	FSP_GetFsImagePtr
	ldr	r6, [r4, #1568]
	mov	r1, r6
	mov	r7, r0
	ldr	r0, [r4, #1960]
	bl	FSP_GetRef
	mov	r2, r6
	ldr	r1, .L460+8
	mov	r3, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #1568]
	ldr	r0, [r4, #1960]
	bl	FSP_SetDisplay
	add	r3, r5, #54784
	ldr	r0, [r4, #1960]
	add	r3, r3, #72
	str	r7, [sp]
	mov	r2, r5
	mov	r1, #8
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L458
.L441:
	ldr	r3, [r4, #1456]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r4, #1456]
.L434:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L439:
	ldr	r1, [r4, #1564]
	cmn	r1, #1
	str	r1, [r4, #1568]
	bne	.L459
	b	.L441
.L458:
	ldr	r0, [r4, #1960]
	mov	r2, #0
	ldr	r1, [r4, #1568]
	bl	FSP_SetDisplay
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L457:
	movw	r2, #2259
	ldr	r1, .L460+12
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L461:
	.align	2
.L460:
	.word	.LC29
	.word	.LC30
	.word	.LC31
	.word	.LC11
	UNWIND(.fnend)
	.size	REAL8DEC_VDMPostProc, .-REAL8DEC_VDMPostProc
	.align	2
	.global	REAL8DEC_GetImageBuffer
	.type	REAL8DEC_GetImageBuffer, %function
REAL8DEC_GetImageBuffer:
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
	beq	.L469
	add	r4, r5, #53248
	ldr	r0, [r4, #1960]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #1960]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L470
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L470:
	add	r1, r5, #54784
	ldr	r0, [r4, #1960]
	add	r1, r1, #72
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L469:
	movw	r2, #2340
	ldr	r1, .L471
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L472:
	.align	2
.L471:
	.word	.LC11
	UNWIND(.fnend)
	.size	REAL8DEC_GetImageBuffer, .-REAL8DEC_GetImageBuffer
	.align	2
	.global	REAL8DEC_Support
	.type	REAL8DEC_Support, %function
REAL8DEC_Support:
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
	movne	r2, #1
	strne	r2, [r3]
	ldmnefd	sp, {fp, sp, pc}
	movw	r2, #2362
	ldr	r1, .L475
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L476:
	.align	2
.L475:
	.word	.LC11
	UNWIND(.fnend)
	.size	REAL8DEC_Support, .-REAL8DEC_Support
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
.LC3:
	.word	0
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	3
	.type	s_RVVersionEncodingToMinorVersion, %object
	.size	s_RVVersionEncodingToMinorVersion, 32
s_RVVersionEncodingToMinorVersion:
	.word	2
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.type	__FUNCTION__.13911, %object
	.size	__FUNCTION__.13911, 16
__FUNCTION__.13911:
	.ascii	"REAL8DEC_Decode\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
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
	ASCII(.ascii	"image size abnormal (%dx%d) in MB\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"real8 actual frame size(%dx%d) exeed max config(%dx" )
	ASCII(.ascii	"%d)\012\000" )
.LC10:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"line: %d\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC13:
	ASCII(.ascii	"Decoding quits at frm %d\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
.LC15:
	ASCII(.ascii	"Real8_CB_GetPictureHeader Error!\012\000" )
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
	ASCII(.ascii	"Real8_ArrangeVHBMem err\012\000" )
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
	ASCII(.ascii	"%s %d unknow error!!\012\000" )
	.space	2
.LC25:
	ASCII(.ascii	"CurFsID abnormal!\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p," )
	ASCII(.ascii	"%p,%p,%p,%p\012\000" )
.LC27:
	ASCII(.ascii	"line:%d! i > (RV8_MAX_SLC_PARAM_NUM - 2)\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"%s %d NULL == pCtx->pRv8DecParam!!\012\000" )
.LC29:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"DEBUG: DEC over\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
