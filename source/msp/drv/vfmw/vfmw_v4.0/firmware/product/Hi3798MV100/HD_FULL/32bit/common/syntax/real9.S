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
	ldr	r3, [r0, #16]
	ldr	r2, [r0, #12]
	cmp	r3, #128
	beq	.L19
	cmp	r3, #176
	beq	.L20
	cmp	r3, #352
	beq	.L21
	cmp	r3, #704
	beq	.L22
	cmp	r3, #1408
	beq	.L23
.L3:
	add	r3, r3, #15
	add	r2, r2, #15
	mov	r3, r3, lsr #4
	mov	r2, r2, lsr #4
	str	r3, [r0, #76]
	mul	r3, r3, r2
	str	r2, [r0, #72]
	sub	r3, r3, #1
	cmp	r3, #47
	movls	r3, #0
	bls	.L4
	cmp	r3, #98
	bls	.L13
	cmp	r3, #396
	bcc	.L14
	cmp	r3, #1584
	bcc	.L15
	cmp	r3, #6336
	movcs	r3, #5
	bcc	.L17
.L4:
	ldr	r2, .L24
	ldr	r3, [r2, r3, asl #2]
	str	r3, [r0, #80]
	ldmfd	sp, {fp, sp, pc}
.L23:
	cmp	r2, #1152
	bne	.L3
	mov	r2, #88
	mov	r3, #72
	str	r2, [r0, #76]
	str	r3, [r0, #72]
.L17:
	mov	r3, #4
	b	.L4
.L19:
	cmp	r2, #96
	bne	.L3
	mov	r3, #8
	mov	r2, #6
	str	r3, [r0, #76]
	mov	r3, #0
	str	r2, [r0, #72]
	b	.L4
.L20:
	cmp	r2, #144
	bne	.L3
	mov	r2, #11
	mov	r3, #9
	str	r2, [r0, #76]
	str	r3, [r0, #72]
.L13:
	mov	r3, #1
	b	.L4
.L21:
	cmp	r2, #288
	bne	.L3
	mov	r2, #22
	mov	r3, #18
	str	r2, [r0, #76]
	str	r3, [r0, #72]
.L14:
	mov	r3, #2
	b	.L4
.L22:
	cmp	r2, #576
	bne	.L3
	mov	r2, #44
	mov	r3, #36
	str	r2, [r0, #76]
	str	r3, [r0, #72]
.L15:
	mov	r3, #3
	b	.L4
.L25:
	.align	2
.L24:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real9_CB_SetDimensions, .-Real9_CB_SetDimensions
	.align	2
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
	ldr	r7, .L31
	mov	r4, #0
	mov	r6, r0
	mov	r8, r1
	mov	r5, r4
.L28:
	mov	r1, #8
	mov	r0, r6
	bl	BsShow
	add	r3, r7, r0
	mov	r0, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	and	r2, r3, #15
	mov	r1, r3, lsr #4
	mov	r3, r3, lsr #5
	add	r4, r4, r1
	orr	r5, r2, r5, asl r3
	bl	BsSkip
	tst	r4, #1
	beq	.L28
	str	r5, [r8]
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L32:
	.align	2
.L31:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real9_CB_GetVLCBits, .-Real9_CB_GetVLCBits
	.align	2
	.type	RV9_RecordVFMWState.part.1, %function
RV9_RecordVFMWState.part.1:
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
	ldr	ip, .L34
	movw	r3, #1411
	ldr	r2, .L34+4
	mov	r0, #1
	ldr	r1, .L34+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L35:
	.align	2
.L34:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+280
	.word	.LC3
	UNWIND(.fnend)
	.size	RV9_RecordVFMWState.part.1, .-RV9_RecordVFMWState.part.1
	.align	2
	.type	Real9_WriteReg.part.4, %function
Real9_WriteReg.part.4:
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
	ldr	ip, .L37
	movw	r3, #1491
	ldr	r2, .L37+4
	mov	r0, #1
	ldr	r1, .L37+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L38:
	.align	2
.L37:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+300
	.word	.LC3
	UNWIND(.fnend)
	.size	Real9_WriteReg.part.4, .-Real9_WriteReg.part.4
	.align	2
	.type	Real9_CB_GetSliceHeader.constprop.5, %function
Real9_CB_GetSliceHeader.constprop.5:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 88
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	ldr	r4, [fp, #4]
	mov	r7, r3
	mov	r6, r1
	mov	r8, r2
	mov	r5, r0
	ldr	r3, [r4, #4]
	cmp	r3, #1
	beq	.L71
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	beq	.L72
.L45:
	mov	r0, #0
.L42:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L71:
	ldr	r9, [r4, #88]
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	bne	.L45
	cmn	r9, #1
	mov	r1, #2
	mov	r0, r5
	movne	r9, #0
	moveq	r9, #1
	cmp	r9, #0
	beq	.L43
	bl	BsShow
	mov	r1, #2
	mov	r10, r0
	mov	r0, r5
	bl	BsSkip
	str	r10, [r4, #84]
.L44:
	mov	r1, #5
	mov	r0, r5
	bl	BsShow
	mov	r1, #5
	mov	r10, r0
	mov	r0, r5
	bl	BsSkip
	uxtb	r0, r10
	cmp	r0, #31
	strb	r0, [r4, #66]
	bhi	.L45
	mov	r0, r5
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	bne	.L45
	mov	r0, r5
	bl	Real9_CB_Get1Bit
	subs	r10, r0, #0
	bne	.L45
	mov	r1, #2
	mov	r0, r5
	bl	BsShow
	mov	r1, #2
	str	r0, [fp, #-128]
	mov	r0, r5
	bl	BsSkip
	ldr	r3, [fp, #-128]
	mov	r1, #1
	mov	r0, r5
	str	r3, [r4, #52]
	bl	BsShow
	mov	r1, #1
	str	r0, [fp, #-128]
	mov	r0, r5
	bl	BsSkip
	ldr	r3, [fp, #-128]
	mov	r1, #13
	mov	r0, r5
	adds	r3, r3, #0
	movne	r3, #1
	cmp	r9, #0
	strb	r3, [r4, #65]
	beq	.L46
	bl	BsShow
	mov	r1, #13
	str	r0, [fp, #-128]
	mov	r0, r5
	bl	BsSkip
	ldr	r3, [r4, #84]
	ldr	r2, [fp, #-128]
	cmp	r3, #1
	str	r2, [r4, #92]
	bls	.L48
	cmp	r3, #2
	bne	.L47
	ldr	ip, .L74
	sub	r3, fp, #76
	str	r3, [fp, #-128]
	sub	r10, fp, #108
	ldr	lr, [r4, #108]
	ldmia	ip!, {r0, r1, r2, r3}
	str	lr, [r4, #116]
	add	lr, ip, #16
	stmia	r10!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	add	ip, ip, #48
	str	ip, [fp, #-132]
	ldr	ip, [r4, #112]
	stmia	r10, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	r10, [fp, #-128]
	str	ip, [r4, #120]
	sub	ip, fp, #124
	stmia	r10!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	r10, {r0, r1, r2, r3}
	ldr	r3, [fp, #-132]
	ldmia	r3, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
.L50:
	mov	r0, r5
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	ldrne	r10, [r4, #116]
	ldrne	r3, [r4, #120]
	bne	.L52
.L51:
	mov	r1, #3
	mov	r0, r5
	bl	BsShow
	mov	r1, #3
	mov	r10, r0
	mov	r0, r5
	bl	BsSkip
	sub	r3, fp, #44
	add	r10, r3, r10, lsl #2
	ldr	r10, [r10, #-64]
	cmp	r10, #0
	bne	.L53
	str	r6, [fp, #-128]
	mov	r6, r10
	mov	r10, r4
.L54:
	mov	r1, #8
	mov	r0, r5
	bl	BsShow
	mov	r1, #8
	mov	r4, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r4, #255
	add	r6, r6, r4, lsl #2
	beq	.L54
	mov	r4, r10
	mov	r10, r6
	ldr	r6, [fp, #-128]
.L53:
	mov	r1, #3
	mov	r0, r5
	bl	BsShow
	mov	r1, #3
	str	r0, [fp, #-128]
	mov	r0, r5
	bl	BsSkip
	ldr	r2, [fp, #-128]
	sub	r3, fp, #44
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #-32]
	cmp	r3, #0
	beq	.L73
.L52:
	cmp	r9, #0
	beq	.L57
	sub	r1, r10, #48
	movw	r2, #8144
	cmp	r1, r2
	str	r10, [r4, #108]
	str	r3, [r4, #112]
	str	r10, [r4, #16]
	str	r3, [r4, #12]
	bhi	.L45
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L45
	mov	r0, r4
	bl	Real9_CB_SetDimensions
.L58:
	ldr	r10, [r4, #80]
	mov	r0, r5
	mov	r1, r10
	bl	BsShow
	mov	r1, r10
	mov	r9, r0
	mov	r0, r5
	bl	BsSkip
	str	r9, [r4, #88]
	str	r9, [r6]
	mov	r3, #0
	ldrb	r2, [r4, #66]	@ zero_extendqisi2
	mov	r0, #1
	str	r2, [r7]
	str	r3, [r8]
	b	.L42
.L72:
	ldr	r9, [r4, #80]
	mov	r0, r5
	mov	r1, r9
	bl	BsShow
	mov	r1, r9
	mov	r10, r0
	mov	r0, r5
	bl	BsSkip
	str	r10, [r6]
	ldr	r3, [r4, #80]
	cmp	r3, #11
	bls	.L61
	mov	r0, r5
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	bne	.L45
.L61:
	mov	r1, #5
	mov	r0, r5
	bl	BsShow
	mov	r1, #5
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r6, #31
	str	r6, [r7]
	bgt	.L45
	mov	r1, #2
	mov	r0, r5
	bl	BsShow
	mov	r1, #2
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	str	r6, [r4, #52]
	mov	r0, r5
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	mov	r4, r0
	bne	.L45
	mov	r1, #2
	mov	r0, r5
	bl	BsShow
	mov	r1, #2
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	str	r6, [r8]
	b	.L42
.L43:
	bl	BsShow
	mov	r1, #2
	mov	r10, r0
	mov	r0, r5
	bl	BsSkip
	ldr	r3, [r4, #84]
	cmp	r10, r3
	bne	.L45
	b	.L44
.L48:
	str	r10, [r4, #116]
	str	r10, [r4, #120]
.L47:
	ldr	ip, .L74
	sub	r3, r3, #2
	sub	r2, fp, #76
	cmp	r3, #1
	str	r2, [fp, #-128]
	sub	r10, fp, #108
	ldmia	ip!, {r0, r1, r2, r3}
	add	lr, ip, #16
	stmia	r10!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	add	ip, ip, #48
	stmia	r10, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	r10, [fp, #-128]
	stmia	r10!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	r10, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	sub	ip, fp, #124
	stmia	ip, {r0, r1, r2, r3}
	bhi	.L51
	b	.L50
.L46:
	bl	BsShow
	mov	r1, #13
	mov	r10, r0
	mov	r0, r5
	bl	BsSkip
	ldr	r3, [r4, #92]
	cmp	r10, r3
	ldreq	r3, [r4, #84]
	bne	.L45
	b	.L47
.L57:
	ldr	r2, [r4, #108]
	cmp	r2, r10
	bne	.L45
	ldr	r2, [r4, #112]
	cmp	r2, r3
	bne	.L45
	b	.L58
.L73:
	mov	r0, r5
	mov	r2, r2, asl #1
	str	r2, [fp, #-128]
	bl	Real9_CB_Get1Bit
	ldr	r2, [fp, #-128]
	orr	r0, r0, r2
	sub	r2, fp, #44
	and	r3, r0, #3
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-80]
	cmp	r3, #0
	bne	.L52
	str	r4, [fp, #4]
	mov	r4, r3
	str	r6, [fp, #-128]
.L56:
	mov	r1, #8
	mov	r0, r5
	bl	BsShow
	mov	r1, #8
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r6, #255
	add	r4, r4, r6, lsl #2
	beq	.L56
	mov	r3, r4
	ldr	r6, [fp, #-128]
	ldr	r4, [fp, #4]
	b	.L52
.L75:
	.align	2
.L74:
	.word	.LANCHOR0+316
	UNWIND(.fnend)
	.size	Real9_CB_GetSliceHeader.constprop.5, .-Real9_CB_GetSliceHeader.constprop.5
	.align	2
	.global	Real9_GetImageBuffer
	.type	Real9_GetImageBuffer, %function
Real9_GetImageBuffer:
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
	beq	.L84
	add	r7, r5, #77824
	mov	r1, #1
	add	r6, r5, #45056
	add	r8, r5, #8192
	ldr	r0, [r7, #2456]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r6, #1016]
	blt	.L85
	mov	r1, r0
	ldr	r0, [r7, #2456]
	bl	FSP_GetLogicFs
	subs	r4, r0, #0
	beq	.L86
	ldr	r5, .L87
	mov	r0, #18
	ldr	r2, [r6, #1016]
	ldr	r1, .L87+4
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r2, [r4, #520]
	cmp	r2, #0
	beq	.L83
	ldr	r3, [r4, #524]
	cmp	r3, #0
	beq	.L83
	ldr	r1, [r4, #528]
	cmp	r1, #0
	beq	.L83
	ldr	ip, [r1, #12]
	mov	r0, #18
	ldr	r3, [r3, #12]
	ldr	r2, [r2, #12]
	ldr	r4, [r5, #68]
	ldr	r1, .L87+8
	str	ip, [sp]
	blx	r4
	mov	r0, #1
.L78:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L83:
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L85:
	ldr	r3, .L87
	mov	r0, #0
	ldr	r1, .L87+12
	mov	r4, r0
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r6, #1012]
	ldr	r0, [r7, #2456]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r6, #1008]
	ldr	r0, [r7, #2456]
	bl	FSP_ClearLogicFs
	str	r4, [r6, #1008]
	str	r4, [r6, #1012]
	ldr	r0, [r7, #2456]
	bl	FSP_GetNullLogicFs
	add	r1, r5, #46080
	add	r1, r1, #40
	str	r0, [r6, #1012]
	str	r0, [r6, #1008]
	strb	r4, [r8, #3173]
	ldr	r0, [r7, #2456]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L84:
	ldr	ip, .L87
	mov	r3, #504
	ldr	r2, .L87+16
	mov	r0, #1
	ldr	r1, .L87+20
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L86:
	ldr	r3, .L87
	movw	r2, #533
	ldr	r1, .L87+24
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	b	.L78
.L88:
	.align	2
.L87:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC7
	.word	.LC4
	.word	.LANCHOR0+396
	.word	.LC3
	.word	.LC5
	UNWIND(.fnend)
	.size	Real9_GetImageBuffer, .-Real9_GetImageBuffer
	.align	2
	.global	Real9_ArrangeVHBMem
	.type	Real9_ArrangeVHBMem, %function
Real9_ArrangeVHBMem:
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
	UNWIND(.pad #60)
	sub	sp, sp, #60
	cmp	r2, #0
	cmpne	r1, #0
	mov	r5, r1
	mov	r4, r2
	beq	.L119
	ldr	r2, [r2, #24]
	ldr	r3, [r4, #20]
	cmp	r2, #1
	bls	.L93
	cmp	r3, #1
	bls	.L93
	ldr	r1, [r1]
	ldr	r3, [r1, #776]
	cmp	r3, #0
	ldr	r3, [r1, #28]
	bne	.L95
	cmp	r3, #25
	beq	.L120
.L96:
	ldr	r7, [r4, #16]
	mov	r9, #5
	ldr	r6, [r4, #12]
	mov	r10, #4
	mov	r3, #2
	str	r3, [fp, #-88]
.L102:
	ldr	r8, .L124
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #76
	ldr	r3, [r8, #48]
	blx	r3
	ldr	r0, [r4, #12]
	ldr	r1, [r5]
	mov	r3, #0
	ldr	r2, [r4, #16]
	str	r0, [fp, #-48]
	ldr	r1, [r1, #28]
	str	r7, [fp, #-68]
	cmp	r1, #24
	str	r6, [fp, #-64]
	str	r2, [fp, #-52]
	strb	r3, [fp, #-75]
	beq	.L108
	ldrb	r3, [fp, #-88]	@ zero_extendqisi2
	strb	r10, [fp, #-72]
	strb	r9, [fp, #-70]
.L110:
	add	r6, r5, #77824
	sub	r1, fp, #76
	strb	r3, [fp, #-69]
	mov	r4, #0
	ldr	r0, [r6, #2456]
	strb	r4, [fp, #-73]
	bl	FSP_ConfigInstance
	subs	r7, r0, #0
	beq	.L121
.L118:
	mov	r0, #0
.L115:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L95:
	cmp	r3, #25
	bne	.L96
	ldr	r2, [r4, #16]
	ldr	r0, [r1, #736]
	ldr	r3, [r4, #12]
	cmp	r2, r0
	ldr	ip, [r1, #740]
	bhi	.L105
	cmp	r3, ip
	bhi	.L105
	ldr	r0, [r1, #764]
	mov	r7, r2
	ldr	r2, [r1, #760]
	mov	r6, r3
	cmp	r0, #0
	add	r10, r2, #2
	bne	.L122
.L113:
	mov	r3, #1
	str	r3, [fp, #-88]
.L107:
	ldrb	r9, [r1, #784]	@ zero_extendqisi2
	b	.L102
.L93:
	ldr	ip, .L124
	mov	r0, #0
	ldr	r1, .L124+4
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L119:
	ldr	ip, .L124
	mov	r3, #568
	ldr	r2, .L124+8
	mov	r0, #1
	ldr	r1, .L124+12
	ldr	r4, [ip, #68]
	blx	r4
	b	.L118
.L121:
	ldr	r1, [r5]
	sub	r3, fp, #80
	ldr	r0, [r6, #2456]
	ldr	r2, [r1, #24]
	ldr	r1, [r1, #20]
	bl	FSP_PartitionFsMemory
	cmp	r0, r4
	bne	.L123
	add	r5, r5, #8192
	mov	r3, #1
	mov	r0, r3
	strb	r3, [r5, #3176]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L108:
	mov	r3, #1
	strb	r9, [fp, #-70]
	strb	r3, [fp, #-72]
	b	.L110
.L120:
	ldr	r2, [r4, #16]
	ldr	r7, [r1, #736]
	ldr	r3, [r4, #12]
	cmp	r2, r7
	ldr	r6, [r1, #740]
	bhi	.L98
	cmp	r3, r6
	bhi	.L98
	add	r3, r5, #8192
	ldrb	r0, [r3, #3176]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L115
	ldr	r2, [r1, #764]
	ldr	r3, [r1, #760]
	cmp	r2, #0
	add	r10, r3, #2
	beq	.L113
	add	r3, r3, #1
	cmp	r3, #17
	movge	r3, #17
	str	r3, [fp, #-88]
	b	.L107
.L105:
	ldr	r1, .L124
	stmia	sp, {r0, ip}
.L117:
	ldr	r4, [r1, #68]
	mov	r0, #0
	ldr	r1, .L124+16
	blx	r4
	b	.L118
.L122:
	add	r2, r2, #1
	cmp	r2, #17
	movlt	r3, r2
	movge	r3, #17
	str	r3, [fp, #-88]
	b	.L107
.L98:
	ldr	r1, .L124
	str	r6, [sp, #4]
	str	r7, [sp]
	b	.L117
.L123:
	ldr	r3, [r8, #68]
	mov	r0, r7
	ldr	r1, .L124+20
	blx	r3
	mov	r0, r7
	b	.L115
.L125:
	.align	2
.L124:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	.LANCHOR0+420
	.word	.LC3
	.word	.LC9
	.word	.LC10
	UNWIND(.fnend)
	.size	Real9_ArrangeVHBMem, .-Real9_ArrangeVHBMem
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
	subs	r7, r0, #0
	mov	r6, r2
	mov	r8, r3
	mov	r9, r1
	beq	.L135
	sub	r3, r1, #1
	mov	r5, #1
	mov	r5, r5, asl r3
	bl	BsShow
	mov	r1, r9
	mov	r4, r0
	mov	r0, r7
	bl	BsSkip
	cmp	r6, r4
	cmpne	r8, #0
	beq	.L129
	ands	r10, r4, r5
	bne	.L129
	ldr	r3, .L136
	add	r9, r3, r9, lsl #2
	ldr	r9, [r9, #472]
	b	.L130
.L131:
	tst	r4, r5
	bne	.L129
.L130:
	mov	r0, r7
	and	r4, r9, r4, asl #1
	bl	Real9_CB_Get1Bit
	add	r10, r10, #1
	orr	r4, r0, r4
	cmp	r6, r4
	cmpne	r8, r10
	bhi	.L131
.L129:
	rsb	r0, r6, r4
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L135:
	ldr	ip, .L136+4
	movw	r3, #898
	ldr	r2, .L136+8
	mov	r0, #1
	ldr	r1, .L136+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r7
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L137:
	.align	2
.L136:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+440
	.word	.LC3
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L149
	ldr	r3, [r1, #4]
	cmp	r3, #1
	beq	.L148
	bl	BsToNextByte
	mov	r0, r7
	bl	BsResidBits
	cmp	r0, #0
	add	r5, r0, #7
	movge	r5, r0
	mov	r5, r5, asr #3
	cmp	r5, #2
	subgt	r5, r5, #2
	movwgt	r6, #7184
	movtgt	r6, 29
	bgt	.L143
	b	.L148
.L150:
	bl	BsSkip
	cmp	r4, r5
	beq	.L148
.L143:
	mov	r1, #24
	mov	r0, r7
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, r6
	mov	r0, r7
	bne	.L150
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L149:
	ldr	ip, .L151
	movw	r3, #926
	ldr	r2, .L151+4
	mov	r0, #1
	ldr	r1, .L151+8
	ldr	r4, [ip, #68]
	blx	r4
.L148:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L152:
	.align	2
.L151:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+572
	.word	.LC3
	UNWIND(.fnend)
	.size	Real9_CB_GetSSC, .-Real9_CB_GetSSC
	.align	2
	.global	Real9_SetImgFormat
	.type	Real9_SetImgFormat, %function
Real9_SetImgFormat:
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
	beq	.L160
	add	r2, r5, #45056
	add	r3, r5, #77824
	ldr	r1, [r2, #1016]
	ldr	r0, [r3, #2456]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r2, r5, #40960
	mov	ip, #0
	mov	r1, ip
	ldr	r3, [r2, #3768]
	str	ip, [r4, #148]
	and	r3, r3, #3
	str	r3, [r4, #152]
	orr	ip, r3, #7168
	str	r3, [r4, #156]
	orr	ip, ip, #32
	str	ip, [r4, #160]
	ldr	r3, [r2, #3776]
	str	r3, [r4, #164]
	ldr	r3, [r2, #3772]
	str	r3, [r4, #168]
	bl	SetAspectRatio
	ldr	r3, [r5]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L161
.L156:
	mov	r2, #9
	mov	r3, #0
	str	r2, [r4, #384]
	mov	r2, #1
	strb	r3, [r4, #372]
	mov	r3, #8
	strb	r2, [r4, #379]
	strb	r2, [r4, #377]
	str	r3, [r4, #388]
	str	r3, [r4, #396]
	str	r3, [r4, #392]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L160:
	ldr	ip, .L162
	movw	r3, #1339
	ldr	r2, .L162+4
	mov	r0, #1
	ldr	r1, .L162+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L161:
	ldr	r3, [r4, #168]
	ldr	r1, [r4, #192]
	add	r3, r3, #15
	ldr	r0, [r4, #104]
	ldr	ip, [r4, #32]
	mov	r2, r3, lsr #4
	mov	r3, r1, asl #4
	add	lr, r0, r1
	str	r0, [r4, #88]
	mul	r3, r2, r3
	str	r0, [r4, #120]
	str	lr, [r4, #96]
	str	ip, [r4, #48]
	add	r0, r3, r0
	add	r3, ip, r3
	add	r1, r0, r1
	str	r3, [r4, #36]
	str	r0, [r4, #108]
	str	r0, [r4, #92]
	str	r1, [r4, #100]
	bl	MEM_Phy2Vir
	ldr	r3, [r4, #92]
	str	r3, [r4, #124]
	str	r0, [r4, #52]
	b	.L156
.L163:
	.align	2
.L162:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+588
	.word	.LC3
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
	cmp	r0, #0
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RV9_RecordVFMWState.part.1
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
	cmp	r0, #0
	beq	.L168
	mov	r2, #44
	add	r3, r0, #40960
	mla	r2, r2, r1, r0
	ldr	r4, [r3, #3916]
	add	r1, r1, #1
	add	lr, r2, #104
	add	ip, r2, #112
	str	r4, [r2, #84]
	ldr	r4, [r3, #3908]
	str	r4, [r2, #92]
	ldr	r4, [r3, #3912]
	str	r4, [r2, #100]
	ldr	r4, [r3, #3928]
	str	r4, [r2, #88]
	ldr	r4, [r3, #3920]
	str	r4, [r2, #96]
	ldr	r4, [r3, #3924]
	str	r4, [r2, #104]
	ldr	r2, [r3, #3896]
	str	r2, [lr, #4]
	ldr	r2, [r3, #3892]
	str	r2, [lr, #8]
	ldr	r2, [r3, #3888]
	str	r2, [ip, #4]
	ldr	r3, [r3, #3900]
	str	r3, [ip, #8]
	str	r1, [r0, #40]
	ldmfd	sp, {r4, fp, sp, pc}
.L168:
	ldr	ip, .L169
	movw	r3, #1427
	ldr	r2, .L169+4
	mov	r0, #1
	ldr	r1, .L169+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	ip
.L170:
	.align	2
.L169:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+608
	.word	.LC3
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
	cmp	r0, #0
	beq	.L177
	add	r3, r0, #40960
	add	r2, r0, #45056
	ldr	r1, [r3, #3768]
	cmp	r1, #2
	strb	r1, [r0, #9]
	ldr	r1, [r3, #3784]
	str	r1, [r0, #12]
	ldr	r1, [r3, #3780]
	str	r1, [r0, #16]
	ldr	r1, [r2, #932]
	str	r1, [r0, #20]
	ldr	r2, [r2, #936]
	str	r2, [r0, #24]
	ldr	r2, [r3, #3808]
	str	r2, [r0, #28]
	ldr	r1, [r3, #3932]
	str	r1, [r0, #32]
	ldr	r1, [r3, #3936]
	str	r1, [r0, #36]
	strne	r2, [r3, #3932]
	ldmfd	sp, {fp, sp, pc}
.L177:
	ldr	ip, .L178
	movw	r3, #1462
	ldr	r2, .L178+4
	mov	r0, #1
	ldr	r1, .L178+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L179:
	.align	2
.L178:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+628
	.word	.LC3
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
	cmp	r0, #0
	strne	r1, [r0, #44]
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	Real9_WriteReg.part.4
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
	subs	r4, r0, #0
	beq	.L210
	ldr	r2, [r4, #120]
	ldr	r3, [r4, #12]
	cmp	r2, #0
	ldr	r0, [r4, #16]
	bne	.L187
	mul	r0, r3, r0
	ldr	r5, [r4, #40]
	cmp	r5, #2
	sub	r0, r0, #1
	bls	.L186
	ldr	r3, [r4, #164]
	sub	ip, r5, #1
	cmp	r3, #0
	cmpgt	r0, r3
	ble	.L187
	mov	r2, r4
	mov	r3, #1
	b	.L188
.L189:
	ldr	r1, [r2, #208]
	add	r2, r2, #44
	cmp	r0, r1
	cmpgt	r1, #0
	ble	.L187
.L188:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L189
.L186:
	cmp	r5, #1
	bls	.L190
	sub	lr, r5, #1
	mov	r3, r4
	mov	r2, #0
	b	.L191
.L192:
	ldr	ip, [r3, #120]
	add	r3, r3, #44
	add	r2, r2, #1
	ldr	r1, [r3, #120]
	cmp	ip, r1
	bge	.L187
.L191:
	cmp	r2, lr
	bne	.L192
	mov	r3, #44
	mla	r2, r3, r2, r4
	ldr	r3, [r2, #120]
	cmp	r0, r3
	cmpge	r3, #0
	ble	.L187
.L190:
	cmp	r5, #0
	beq	.L193
	sub	r7, r5, #1
	mov	r6, r4
	mov	ip, r4
	mov	lr, #0
	b	.L196
.L212:
	cmp	lr, r5
	beq	.L211
.L196:
	cmp	lr, r7
	streq	r0, [ip, #124]
	add	lr, lr, #1
	add	ip, ip, #44
	ldrne	r3, [ip, #120]
	moveq	r1, r0
	subne	r1, r3, #1
	ldr	r3, [ip, #76]
	strne	r1, [ip, #80]
	mov	r2, r3, lsr #31
	cmp	r0, r3
	orrlt	r2, r2, #1
	cmp	r3, r1
	movle	r3, r2
	orrgt	r3, r2, #1
	orr	r3, r3, r1, lsr #31
	cmp	r0, r1
	orrlt	r3, r3, #1
	cmp	r3, #0
	beq	.L212
.L187:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L210:
	ldr	ip, .L215
	movw	r3, #1507
	ldr	r2, .L215+4
	mov	r0, #1
	ldr	r1, .L215+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L211:
	ldr	r2, [r4, #84]
	mov	r1, r2
	b	.L199
.L213:
	ldr	r1, [r6, #84]
.L199:
	cmp	r2, r1
	ldr	r0, [r6, #88]
	add	r3, r3, #1
	movcs	r2, r1
	cmp	r0, r2
	bcs	.L197
	ldr	r1, [r6, #104]
	cmp	r1, #0
	movne	r2, r0
.L197:
	cmp	r5, r3
	add	r6, r6, #44
	bne	.L213
	bic	r2, r2, #15
	ldr	ip, [r4, #40]
	str	r2, [r4, #48]
	mov	r3, r4
	mov	r0, #0
	b	.L203
.L214:
	ldr	lr, [r3, #92]
	rsb	r2, r2, r1
	and	r1, lr, #7
	add	r2, r2, lr, lsr #3
	and	lr, r2, #15
	bic	r2, r2, #15
	str	r2, [r3, #84]
	add	r2, r1, lr, lsl #3
	str	r2, [r3, #92]
.L201:
	add	r0, r0, #1
	add	r3, r3, #44
	cmp	ip, r0
	bls	.L202
	ldr	r2, [r4, #48]
.L203:
	ldr	lr, [r3, #88]
	ldr	r1, [r3, #84]
	cmp	lr, #0
	rsb	r6, r2, lr
	beq	.L214
	ldr	r7, [r3, #92]
	rsb	r2, r2, r1
	ldr	lr, [r3, #96]
	and	r5, r7, #7
	add	r2, r2, r7, lsr #3
	add	r1, r6, lr, lsr #3
	and	r7, r2, #15
	and	r6, r1, #15
	and	lr, lr, #7
	add	r5, r5, r7, lsl #3
	bic	r2, r2, #15
	add	lr, lr, r6, lsl #3
	bic	r1, r1, #15
	str	r5, [r3, #92]
	str	r2, [r3, #84]
	str	lr, [r3, #96]
	str	r1, [r3, #88]
	b	.L201
.L193:
	ldr	r3, [r4, #84]
	bic	r3, r3, #15
	str	r3, [r4, #48]
.L202:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L216:
	.align	2
.L215:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+648
	.word	.LC3
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
	subs	r4, r0, #0
	mov	r6, r1
	beq	.L221
	ldr	r7, .L223
	movw	r2, #14752
	mov	r1, #0
	movt	r2, 1
	mov	r5, r1
	ldr	r3, [r7, #48]
	blx	r3
	add	r0, r4, #46080
	add	r0, r0, #40
	bl	ResetVoQueue
	add	r3, r4, #40960
	str	r6, [r4]
	mov	r2, #15
	str	r2, [r3, #3932]
	add	r1, r4, #8192
	str	r2, [r3, #3936]
	mov	ip, #8192
	ldr	lr, [r6, #8]
	mov	r2, #1
	strb	r5, [r1, #3176]
	mov	r0, r4
	add	r4, r4, #77824
	strb	lr, [r1, #3172]
	str	ip, [r3, #3792]
	str	r2, [r3, #3764]
	strb	r2, [r3, #3760]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #2456]
	beq	.L222
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L221:
	ldr	ip, .L223
	movw	r3, #1622
	ldr	r2, .L223+4
	mov	r0, #1
	ldr	r1, .L223+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L222:
	ldr	r3, [r7, #68]
	mov	r0, r5
	ldr	r1, .L223+12
	blx	r3
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L224:
	.align	2
.L223:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+672
	.word	.LC3
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
	cmp	r0, #0
	ldr	ip, .L228
	beq	.L227
	add	r3, r0, #45056
	ldr	r1, .L228+4
	mov	r0, #2
	ldr	r2, [r3, #908]
	ldr	r3, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L227:
	movw	r3, #1670
	ldr	r2, .L228+8
	mov	r0, #1
	ldr	r1, .L228+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L229:
	.align	2
.L228:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC12
	.word	.LANCHOR0+688
	.word	.LC3
	UNWIND(.fnend)
	.size	REAL9DEC_Destroy, .-REAL9DEC_Destroy
	.global	__aeabi_idiv
	.align	2
	.global	REAL9DEC_Decode
	.type	REAL9DEC_Decode, %function
REAL9DEC_Decode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 192
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #212)
	sub	sp, sp, #212
	mov	r2, #128
	mov	r6, r0
	mov	r5, r1
	sub	r0, fp, #172
	mov	r1, #0
	bl	memset
	cmp	r6, #0
	beq	.L376
	add	r4, r6, #40960
	add	r3, r6, #8
	str	r3, [fp, #-192]
	cmp	r5, #0
	ldr	r2, [r4, #3868]
	mov	r0, #1
	ldr	r3, [r4, #3872]
	mov	r1, #8192
	str	r0, [r4, #3764]
	str	r2, [r4, #3876]
	str	r2, [fp, #-56]
	str	r2, [fp, #-64]
	str	r3, [r4, #3880]
	str	r3, [fp, #-52]
	str	r3, [fp, #-60]
	str	r0, [fp, #-168]
	str	r1, [r4, #3792]
	str	r1, [fp, #-140]
	beq	.L377
	ldr	r3, .L399
	add	r7, r6, #45056
	mov	r1, #0
	movw	r2, #11344
	ldr	r0, [fp, #-192]
	mov	r8, r1
	ldr	r3, [r3, #48]
	blx	r3
	str	r8, [r7, #872]
	ldr	r3, [r5, #12]
	add	r1, r6, #8192
	str	r1, [fp, #-196]
	str	r3, [r7, #892]
	ldr	r3, [r5, #8]
	str	r3, [r7, #876]
	ldr	r3, [r5]
	str	r3, [r1, #3160]
	ldr	r2, [r5, #12]
	str	r2, [r7, #880]
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	strb	r3, [r1, #3164]
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L234
	ldr	r3, [r5, #88]
	str	r3, [r7, #884]
	ldr	r3, [r5, #80]
	str	r3, [r1, #3168]
	ldr	r3, [r5, #92]
	str	r3, [r7, #888]
	ldrb	r3, [r5, #85]	@ zero_extendqisi2
	strb	r3, [r1, #3165]
	ldrb	r3, [r5, #85]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L378
.L235:
	movw	r3, #65525
	sub	r1, r2, #10
	movt	r3, 47
	cmp	r1, r3
	bhi	.L370
	ldr	r9, [fp, #-196]
	ldr	r1, [r9, #3160]
	cmp	r1, #0
	beq	.L370
	add	r5, r6, #46080
	add	r5, r5, #8
	mov	r0, r5
	bl	BsInit
	mov	r1, #8
	mov	r0, r5
	bl	BsShow
	mov	r1, #8
	mov	r8, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r8, #255
	add	r0, r8, #1
	str	r0, [r4, #3940]
	bhi	.L370
	cmp	r0, #0
	beq	.L238
	add	r10, r6, #44800
	movw	r3, #65535
	add	r10, r10, #100
	movt	r3, 47
	str	r6, [fp, #-196]
	mov	r8, #0
	mov	r6, r10
	str	r7, [fp, #-200]
	mov	r10, r3
	b	.L239
.L380:
	ldr	r0, [r4, #3940]
	cmp	r0, r8
	bls	.L379
.L239:
	mov	r1, #32
	mov	r0, r5
	bl	BsSkip
	mov	r1, #32
	mov	r0, r5
	add	r8, r8, #1
	bl	BsShow
	mov	r1, #32
	mov	r7, r0
	mov	r0, r5
	bl	BsSkip
	rev	r0, r7
	cmp	r0, r10
	str	r0, [r6, #4]!
	ble	.L380
.L370:
	mov	r0, #0
.L358:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L378:
	add	r6, r6, #77824
	ldr	r1, [r5, #16]
	ldr	r0, [r6, #2456]
	bl	SM_ReleaseStreamSeg
	ldr	r0, [r6, #2456]
	ldr	r1, [r5, #96]
	bl	SM_ReleaseStreamSeg
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L234:
	ldr	r3, [fp, #-196]
	str	r8, [r7, #884]
	str	r8, [r3, #3168]
	str	r8, [r7, #888]
	strb	r8, [r3, #3165]
	b	.L235
.L377:
	ldr	r3, .L399
	add	r6, r6, #45056
	ldr	r1, .L399+4
	ldr	r2, [r6, #908]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	b	.L358
.L379:
	ldr	r7, [fp, #-200]
	ldr	r6, [fp, #-196]
	str	r9, [fp, #-196]
.L238:
	add	r3, r6, #44800
	sub	lr, r0, #1
	add	r3, r3, #104
	mov	r2, #0
	ldr	r9, [fp, #-196]
	b	.L240
.L241:
	ldr	ip, [r3, #4]!
	ldr	r1, [r3, #-4]
	cmp	ip, r1
	ble	.L370
.L240:
	cmp	r2, lr
	add	r2, r2, #1
	bne	.L241
	mov	r0, r0, asl #3
	ldr	r10, [r4, #3944]
	add	r2, r0, #1
	movw	r3, #65534
	cmp	r2, #3145728
	add	r10, r2, r10
	sub	r8, r10, #1
	str	r2, [fp, #-200]
	movt	r3, 47
	movlt	r2, #0
	movge	r2, #1
	cmp	r8, r3
	movls	r8, r2
	orrhi	r8, r2, #1
	cmp	r8, #0
	str	r9, [fp, #-196]
	bne	.L370
	ldr	r2, [r7, #880]
	rsb	r2, r10, r2
	cmp	r2, #0
	ble	.L370
	ldr	r1, [r9, #3160]
	mov	r0, r5
	add	r1, r1, r10
	bl	BsInit
	ldr	r3, [fp, #-168]
	cmp	r3, #1
	beq	.L381
	ldr	r3, .L399
	mov	r1, r8
	mov	r2, #128
	sub	r0, fp, #172
	ldr	r3, [r3, #48]
	blx	r3
	mov	r1, #16
	mov	r0, r5
	bl	BsShow
	mov	r1, #16
	mov	r8, r0
	mov	r0, r5
	bl	BsSkip
	movw	r3, #21845
	cmp	r8, r3
	bne	.L251
	mov	r1, #16
	mov	r0, r5
	bl	BsShow
	mov	r1, #16
	str	r0, [fp, #-204]
	mov	r0, r5
	bl	BsSkip
	ldr	r3, [fp, #-204]
	cmp	r3, r8
	bne	.L251
	sub	r1, fp, #180
	mov	r0, r5
	str	r1, [fp, #-208]
	bl	Real9_CB_GetVLCBits
	cmp	r0, #30
	bls	.L251
	ldr	r3, [fp, #-180]
	ands	r2, r3, #1
	bne	.L251
	tst	r3, #2
	ldr	r1, [fp, #-208]
	mov	r0, r5
	strne	r2, [fp, #-156]
	moveq	r2, #176
	streq	r2, [fp, #-156]
	moveq	r2, #144
	str	r2, [fp, #-160]
	ubfx	r2, r3, #2, #5
	ubfx	r3, r3, #7, #8
	str	r2, [fp, #-124]
	str	r3, [fp, #-136]
	bl	Real9_CB_GetVLCBits
	cmp	r0, #1
	streq	r0, [fp, #-164]
	beq	.L257
	cmp	r0, #3
	beq	.L382
	cmp	r0, #5
	bne	.L251
	ldr	r3, [fp, #-180]
	cmp	r3, #0
	bne	.L251
	mov	r3, #2
	str	r3, [fp, #-164]
.L257:
	ldr	r3, [fp, #-156]
	cmp	r3, #0
	beq	.L383
.L259:
	sub	r3, r3, #48
	movw	r2, #8144
	cmp	r3, r2
	bhi	.L251
	ldr	r3, [fp, #-160]
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L251
	sub	r0, fp, #172
	bl	Real9_CB_SetDimensions
	mov	r1, #2
	mov	r0, r5
	bl	BsShow
	mov	r1, #2
	mov	r8, r0
	mov	r0, r5
	bl	BsSkip
	ldr	r2, [fp, #-156]
	ldr	r1, [fp, #-160]
	add	r2, r2, #15
	str	r8, [fp, #-120]
	add	r1, r1, #15
	mov	r2, r2, lsr #4
	str	r2, [fp, #-148]
	mov	r1, r1, lsr #4
	str	r1, [fp, #-152]
	mul	r3, r2, r1
	str	r3, [fp, #-144]
.L252:
	ldr	r3, [fp, #-196]
	ldrb	r3, [r3, #3176]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L260
	ldr	r3, [r4, #3784]
	cmp	r3, r2
	beq	.L384
.L260:
	ldr	r3, .L399+8
	ldr	r8, [r3]
	cmp	r8, #0
	addeq	r3, r6, #77824
	streq	r3, [fp, #-204]
	beq	.L262
	add	r3, r6, #77824
	ldr	r0, [r4, #3780]
	ldr	ip, [r4, #3784]
	mov	lr, r3
	str	r3, [fp, #-204]
	strh	r2, [fp, #-176]	@ movhi
	mov	r3, #8
	strh	r1, [fp, #-174]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-178]	@ movhi
	ldr	r2, [fp, #-208]
	strh	ip, [fp, #-180]	@ movhi
	ldr	r0, [lr, #2456]
	blx	r8
.L262:
	ldr	r9, [fp, #-204]
	mov	r2, #1
	ldr	r1, [r7, #1012]
	add	r8, r6, #46080
	add	r8, r8, #40
	ldr	r0, [r9, #2456]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r7, #1008]
	ldr	r0, [r9, #2456]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	str	r3, [r7, #1008]
	str	r3, [r7, #1012]
	ldr	r0, [r9, #2456]
	str	r3, [fp, #-212]
	bl	FSP_GetNullLogicFs
	ldr	r2, [fp, #-196]
	mov	r1, r8
	ldr	r3, [fp, #-212]
	str	r0, [r7, #1012]
	str	r0, [r7, #1008]
	strb	r3, [r2, #3173]
	ldr	r0, [r9, #2456]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [fp, #-148]
	cmp	r2, #512
	ldrhi	r1, [fp, #-152]
	bhi	.L264
	ldr	r3, [fp, #-152]
	cmp	r3, #512
	mov	r1, r3
	bhi	.L264
	ldr	r1, [r6]
	ldr	r0, [r1, #776]
	cmp	r0, #0
	bne	.L266
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L385
.L266:
	ldr	r3, [fp, #-204]
	ldr	r0, [r3, #2456]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L360
.L365:
	ldr	r2, [fp, #-148]
	ldr	r3, [fp, #-152]
.L268:
	ldr	r1, .L399
	mov	r0, #1
	ldr	r8, [r1, #68]
	ldr	r1, .L399+12
	blx	r8
	sub	r2, fp, #172
	mov	r1, r6
	mov	r0, #6
	bl	Real9_ArrangeVHBMem
	ldr	r8, .L399
	subs	r3, r0, #0
	beq	.L386
.L261:
	add	r3, r6, #44544
	sub	r1, fp, #172
	add	r3, r3, #176
	str	r3, [fp, #-216]
	mov	r2, #128
	mov	r0, r3
	ldr	r3, .L399
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r6]
	ldr	r2, [fp, #-196]
	mov	r0, r6
	ldr	r3, [r3, #8]
	strb	r3, [r2, #3172]
	bl	Real9_GetImageBuffer
	subs	r3, r0, #0
	beq	.L387
	add	r3, r6, #77824
	ldr	r1, [r7, #1016]
	str	r3, [fp, #-204]
	ldr	r0, [r3, #2456]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L271
	ldr	r2, [r6]
	mov	r0, #29
	ldr	ip, .L399
	ldr	r1, .L399+16
	ldrd	r8, [r2, #48]
	strd	r8, [r3, #8]
	ldr	r2, [r6]
	ldrd	r8, [r2, #64]
	strd	r8, [r3, #16]
	ldr	r2, [r6]
	ldrd	r8, [r2, #80]
	strd	r8, [r3, #24]
	mvn	r8, #0
	ldr	r2, [r6]
	mvn	r9, #0
	ldr	r2, [r2, #96]
	str	r2, [r3, #68]
	ldr	r2, [r6]
	ldr	r2, [r2, #100]
	str	r2, [r3, #72]
	ldr	r2, [r6]
	ldr	r2, [r2, #104]
	str	r2, [r3, #76]
	ldr	r2, [r6]
	ldr	r2, [r2, #120]
	str	r2, [r3, #80]
	ldr	r2, [r6]
	strd	r8, [r2, #48]
	ldrd	r8, [r3, #16]
	ldr	ip, [ip, #68]
	ldrd	r2, [r3, #8]
	strd	r8, [sp]
	blx	ip
	ldr	r3, [r4, #3768]
	cmp	r3, #2
	beq	.L388
	cmp	r3, #1
	ldr	r3, [fp, #-196]
	ldrb	r3, [r3, #3173]	@ zero_extendqisi2
	beq	.L389
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #1
.L275:
	ldr	r2, [fp, #-196]
	strb	r3, [r2, #3173]
	ldr	r2, [r7, #1008]
	ldr	r3, [r7, #1012]
	cmp	r2, r3
	beq	.L276
	ldr	r3, .L399
	mov	r0, #13
	ldr	r1, .L399+20
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [fp, #-204]
	mov	r2, #0
	ldr	r1, [r7, #1008]
	ldr	r0, [r3, #2456]
	bl	FSP_SetRef
.L276:
	ldr	r3, [r7, #1012]
	mov	r2, #1
	ldr	r1, [r7, #1016]
	ldr	r8, [fp, #-204]
	str	r3, [r7, #1008]
	str	r1, [r7, #1012]
	ldr	r0, [r8, #2456]
	bl	FSP_SetRef
	ldr	r1, [r7, #1008]
	ldr	r0, [r8, #2456]
	bl	FSP_RemovePmv
	ldr	r3, .L399
	ldr	r2, [r7, #1016]
	mov	r0, #13
	ldr	r1, .L399+24
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [fp, #-196]
	ldrb	r3, [r3, #3172]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L278
	ldr	r3, [r4, #3768]
	cmp	r3, #0
	beq	.L366
	cmp	r3, #2
	beq	.L315
	cmp	r3, #1
	beq	.L366
.L278:
	ldr	r9, [fp, #-204]
	ldr	r1, [r7, #1016]
	ldr	r0, [r9, #2456]
	bl	FSP_GetLogicFs
	ldr	r1, [r7, #1008]
	mov	r8, r0
	ldr	r0, [r9, #2456]
	bl	FSP_GetLogicFs
	ldr	r1, [r7, #1012]
	str	r0, [fp, #-212]
	ldr	r0, [r9, #2456]
	bl	FSP_GetLogicFs
	ldr	r3, [fp, #-212]
	cmp	r8, #0
	cmpne	r3, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	str	r0, [fp, #-220]
	cmp	r3, #0
	bne	.L390
	ldr	r3, [r8, #520]
	cmp	r3, #0
	beq	.L284
	ldr	r2, [r8, #528]
	cmp	r2, #0
	beq	.L284
	ldr	r2, [r8, #524]
	cmp	r2, #0
	beq	.L284
	ldr	r2, [fp, #-220]
	mov	r0, #13
	ldr	r1, .L399+28
	ldr	r2, [r2, #520]
	cmp	r2, #0
	ldrne	lr, [r2, #12]
	ldreq	lr, [r3, #12]
	ldr	r3, [fp, #-212]
	str	lr, [r6, #52]
	ldr	r3, [r3, #520]
	cmp	r3, #0
	ldreq	r3, [r8, #520]
	ldr	ip, [r3, #12]
	str	ip, [r6, #56]
	ldr	r3, [r8, #520]
	ldr	r2, [r3, #12]
	str	r2, [r6, #60]
	ldr	r3, [r8, #532]
	str	r3, [r6, #76]
	mov	r9, r3
	ldr	r3, [fp, #-220]
	ldr	r3, [r3, #532]
	str	r3, [r6, #80]
	str	r3, [fp, #-224]
	ldr	r3, [r8, #524]
	ldr	r3, [r3, #12]
	str	r9, [sp, #8]
	ldr	r9, [fp, #-224]
	str	r9, [sp, #12]
	str	r3, [r6, #64]
	stmia	sp, {ip, lr}
	ldr	ip, .L399
	ldr	ip, [ip, #68]
	blx	ip
	ldr	r3, [r8, #524]
	ldr	r3, [r3, #20]
	str	r3, [r6, #68]
	ldr	r3, [r8, #524]
	ldr	r3, [r3, #20]
	str	r3, [r7, #980]
	ldr	r3, [r4, #3768]
	cmp	r3, #2
	beq	.L391
.L290:
	ldr	r3, [r4, #3796]
	mov	r0, r6
	str	r3, [r8, #540]
	ldr	r3, [r4, #3808]
	str	r3, [fp, #-212]
	bl	Real9_WritePicMsg
	mov	r0, r5
	bl	BsPos
	ldr	r1, [r4, #3940]
	cmp	r1, #1
	ldreq	r8, [r4, #3944]
	ldrne	r8, [r4, #3944]
	mov	r3, r0, asr #31
	mov	r2, r3, lsr #29
	add	r3, r0, r2
	moveq	r0, r5
	and	r3, r3, #7
	movne	r0, r5
	rsb	r3, r2, r3
	ldreq	r2, [fp, #-200]
	str	r3, [r4, #3908]
	ldreq	r3, [r7, #880]
	ldrne	r3, [r4, #3948]
	rsbeq	r3, r2, r3
	rsb	r8, r8, r3
	bl	BsPos
	mov	r8, r8, asl #3
	rsb	r0, r0, r8
	str	r0, [r4, #3912]
	ldr	r3, [r7, #876]
	mov	r0, r5
	add	r10, r10, r3
	bl	BsPos
	ldr	r1, [fp, #-212]
	ldr	r2, [r4, #3812]
	str	r1, [r4, #3888]
	mov	r1, #0
	str	r2, [r4, #3892]
	str	r1, [r4, #3920]
	str	r1, [r4, #3924]
	str	r1, [r4, #3928]
	str	r1, [r4, #3900]
	cmp	r0, #0
	add	r3, r0, #7
	movlt	r0, r3
	ldr	r3, [r4, #3804]
	add	r0, r10, r0, asr #3
	str	r0, [r4, #3916]
	mov	r0, r6
	str	r3, [r4, #3896]
	bl	Real9_WriteSliceMsg
	ldr	r3, [r4, #3940]
	cmp	r3, #1
	bls	.L297
	ldr	r10, [r4, #3948]
	movw	r3, #65535
	ldr	r2, [fp, #-200]
	movt	r3, 47
	add	r10, r2, r10
	cmp	r10, r3
	bgt	.L373
	cmp	r10, #0
	ble	.L373
	ldr	r2, [r7, #880]
	rsb	r2, r10, r2
	cmp	r2, #0
	ble	.L373
	add	r8, r6, #44800
	mov	r1, #1
	mov	r0, #0
	str	r6, [fp, #-224]
	add	r8, r8, #108
	str	r0, [fp, #-232]
	str	r3, [fp, #-220]
	mov	r6, r1
	str	r1, [fp, #-228]
	ldr	r9, [fp, #-196]
	b	.L303
.L304:
	ldr	r3, [r4, #3940]
	add	r6, r6, #1
	cmp	r3, r6
	bls	.L392
	ldr	r3, [fp, #-200]
	ldr	r10, [r8, #4]!
	add	r10, r3, r10
	ldr	r3, [fp, #-220]
	cmp	r10, r3
	bgt	.L373
	cmp	r10, #0
	ble	.L373
	ldr	r2, [r7, #880]
	rsb	r2, r10, r2
	cmp	r2, #0
	ble	.L373
.L303:
	ldr	r1, [r9, #3160]
	mov	r0, r5
	add	r1, r1, r10
	bl	BsInit
	ldr	r3, [fp, #-216]
	sub	r2, fp, #184
	sub	r1, fp, #188
	mov	r0, r5
	str	r3, [sp]
	ldr	r3, [fp, #-208]
	bl	Real9_CB_GetSliceHeader.constprop.5
	cmp	r0, #1
	bne	.L304
	ldr	r3, [r4, #3784]
	ldr	r2, [fp, #-188]
	cmp	r3, #0
	str	r2, [fp, #-196]
	beq	.L393
	ldr	r3, [fp, #-180]
	mov	r0, r5
	ldr	r2, [fp, #-212]
	cmp	r3, #0
	movge	r2, r3
	str	r2, [fp, #-212]
	bl	BsPos
	ldr	r1, [r4, #3940]
	sub	r1, r1, #1
	cmp	r1, r6
	mov	r3, r0, asr #31
	mov	r2, r3, lsr #29
	add	r3, r0, r2
	and	r3, r3, #7
	rsb	r3, r2, r3
	str	r3, [r4, #3908]
	beq	.L394
	cmp	r6, #254
	bhi	.L395
	ldr	r3, [r8, #4]
	mov	r0, r5
	ldr	r2, [r8]
.L369:
	rsb	r3, r2, r3
	mov	r3, r3, asl #3
	str	r3, [fp, #-236]
	bl	BsPos
	ldr	r3, [fp, #-236]
	rsb	r0, r0, r3
	str	r0, [r4, #3912]
	ldr	r3, [r7, #876]
	mov	r0, r5
	add	r10, r10, r3
	bl	BsPos
	ldr	r1, [fp, #-232]
	ldr	ip, [fp, #-228]
	ldr	r2, [r4, #3812]
	str	r1, [r4, #3920]
	str	r1, [r4, #3924]
	str	r1, [r4, #3928]
	ldr	r1, [fp, #-212]
	str	r2, [r4, #3892]
	str	r1, [r4, #3888]
	ldr	r1, [fp, #-196]
	str	r1, [r4, #3900]
	mov	r1, ip
	cmp	r0, #0
	add	r3, r0, #7
	movlt	r0, r3
	ldr	r3, [r4, #3804]
	add	r0, r10, r0, asr #3
	str	r0, [r4, #3916]
	add	r0, ip, #1
	str	r0, [fp, #-228]
	str	r3, [r4, #3896]
	mov	r10, r0
	ldr	r0, [fp, #-224]
	bl	Real9_WriteSliceMsg
	cmp	r10, #131
	ble	.L304
	ldr	r0, [fp, #-224]
	bl	Real9_ModifySliceMsg
	cmp	r0, #1
	bne	.L373
	ldr	r3, [fp, #-224]
	ldr	r2, [fp, #-192]
	str	r2, [r3, #4]
	b	.L304
.L376:
	ldr	ip, .L399
	movw	r3, #1704
	ldr	r2, .L399+32
	mov	r0, #1
	ldr	r1, .L399+36
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r6
	b	.L358
.L381:
	sub	r3, fp, #180
	sub	r2, fp, #172
	sub	r1, fp, #184
	str	r2, [sp]
	mov	r0, r5
	sub	r2, fp, #188
	mvn	ip, #0
	str	r3, [fp, #-208]
	str	ip, [fp, #-84]
	bl	Real9_CB_GetSliceHeader.constprop.5
	cmp	r0, #1
	beq	.L396
	ldr	r3, [fp, #-156]
	ldr	r2, [fp, #-160]
	add	r3, r3, #15
	add	r2, r2, #15
	mov	r3, r3, lsr #4
	str	r3, [fp, #-148]
	mov	r2, r2, lsr #4
	str	r2, [fp, #-152]
	mul	r3, r3, r2
	str	r3, [fp, #-144]
.L251:
	ldr	r3, .L399
	mov	r0, #1
	ldr	r1, .L399+40
	ldr	r3, [r3, #68]
	blx	r3
	b	.L370
.L264:
	ldr	r3, .L399
	mov	r0, #18
	ldr	r4, [r3, #68]
	mov	r3, r1
	ldr	r1, .L399+44
	blx	r4
	mov	r0, #0
	b	.L358
.L383:
	mov	r1, #4
	mov	r0, r5
	bl	BsShow
	mov	r1, #4
	mov	r8, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, #9
	mov	r0, r5
	strb	r8, [fp, #-172]
	bl	BsShow
	mov	r1, #9
	mov	r8, r0
	mov	r0, r5
	bl	BsSkip
	add	r3, r8, #1
	mov	r0, r5
	mov	r3, r3, asl #2
	str	r3, [fp, #-156]
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	bne	.L251
	mov	r1, #9
	mov	r0, r5
	bl	BsShow
	mov	r1, #9
	mov	r8, r0
	mov	r0, r5
	bl	BsSkip
	mov	r8, r8, asl #2
	ldr	r3, [fp, #-156]
	str	r8, [fp, #-160]
	b	.L259
.L387:
	str	r3, [fp, #-192]
	ldr	r3, .L399
	ldr	r2, [r7, #908]
	ldr	r1, .L399+48
	ldr	r4, [r3, #68]
	blx	r4
	ldr	r3, [fp, #-192]
	mov	r0, r3
	b	.L358
.L385:
	ldr	r1, [fp, #-196]
	ldrb	r1, [r1, #3176]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L268
.L360:
	mov	r0, r8
	bl	ResetVoQueue
	b	.L365
.L382:
	ldr	r3, [fp, #-180]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [fp, #-164]
	bne	.L251
	b	.L257
.L384:
	ldr	r3, [r4, #3780]
	cmp	r3, r1
	bne	.L260
	b	.L261
.L396:
	ldr	r3, [fp, #-88]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L318
.L246:
	.word	.L245
	.word	.L247
	.word	.L248
	.word	.L249
.L249:
	mov	r8, #1
	mov	r3, #2
	str	r3, [fp, #-164]
.L244:
	ldrb	r0, [fp, #-107]	@ zero_extendqisi2
	movw	r2, #8144
	ldr	r3, [fp, #-156]
	ldrb	ip, [fp, #-106]	@ zero_extendqisi2
	sub	r3, r3, #48
	ldr	r1, [fp, #-80]
	cmp	r3, r2
	str	r0, [fp, #-128]
	ldr	r3, [fp, #-72]
	ldr	r0, [fp, #-76]
	str	ip, [fp, #-124]
	str	r1, [fp, #-136]
	str	r0, [fp, #-116]
	str	r3, [fp, #-112]
	bhi	.L251
	ldr	r3, [fp, #-160]
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L251
	sub	r0, fp, #172
	bl	Real9_CB_SetDimensions
	ldr	r2, [fp, #-156]
	ldr	r1, [fp, #-160]
	cmp	r8, #1
	add	r2, r2, #15
	add	r1, r1, #15
	mov	r2, r2, lsr #4
	str	r2, [fp, #-148]
	mov	r1, r1, lsr #4
	str	r1, [fp, #-152]
	mul	r3, r2, r1
	str	r3, [fp, #-144]
	beq	.L252
	b	.L251
.L248:
	mov	r8, #1
	str	r8, [fp, #-164]
	b	.L244
.L247:
	mov	r3, #0
	mov	r8, #1
	str	r3, [fp, #-164]
	str	r3, [fp, #-104]
	b	.L244
.L245:
	mov	r8, #1
	mov	r3, #0
	str	r8, [fp, #-104]
	str	r3, [fp, #-164]
	b	.L244
.L386:
	ldr	r2, [r8, #68]
	mov	r0, #1
	ldr	r1, .L399+52
	str	r3, [fp, #-192]
	blx	r2
	ldr	r3, [fp, #-192]
	mov	r0, r3
	b	.L358
.L388:
	ldr	r3, [fp, #-196]
	ldrb	r3, [r3, #3173]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L373
	ldr	r3, [fp, #-196]
	ldrb	r3, [r3, #3172]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L278
.L315:
	ldr	r8, [r7, #1024]
	cmp	r8, #0
	bne	.L278
.L373:
	ldr	r3, [fp, #-204]
	mov	r2, #1
	ldr	r1, [r7, #1016]
	ldr	r0, [r3, #2456]
	bl	FSP_ClearLogicFs
	mov	r0, #0
	b	.L358
.L366:
	str	r3, [r7, #1024]
	b	.L278
.L389:
	cmp	r3, #0
	movne	r3, #2
	bne	.L275
	b	.L370
.L394:
	ldr	r3, [r7, #880]
	mov	r0, r5
	ldr	r1, [fp, #-200]
	ldr	r2, [r8]
	rsb	r3, r1, r3
	b	.L369
.L390:
	ldr	r3, .L399
	mov	r0, #0
	ldr	r2, .L399+56
	ldr	r1, .L399+60
	ldr	r4, [r3, #68]
	movw	r3, #1981
	blx	r4
	mov	r0, #0
	b	.L358
.L392:
	ldr	r6, [fp, #-224]
	str	r9, [fp, #-196]
.L297:
	ldr	r5, [r6, #4]
	mov	r4, #1
	str	r4, [r6, #44]
	cmp	r5, #0
	beq	.L316
	ldr	r3, [r6]
	ldr	r2, [r3, #900]
	cmp	r2, r4
	beq	.L317
.L313:
	cmp	r2, #2
	beq	.L397
.L314:
	ldr	r3, [r3, #676]
	mov	r0, #1
	ldr	r2, [fp, #-196]
	str	r3, [r2, #3156]
	b	.L358
.L391:
	ldr	r3, [fp, #-212]
	ldr	r1, [fp, #-220]
	ldr	r2, [r3, #540]
	ldr	r3, [r4, #3796]
	ldr	r1, [r1, #540]
	subs	r3, r3, r2
	rsb	r2, r2, r1
	ldrmi	r1, [r4, #3792]
	addmi	r3, r3, r1
	cmp	r2, #0
	ldrlt	r1, [r4, #3792]
	addlt	r2, r2, r1
	cmp	r3, r2
	movgt	r3, #0
	cmp	r2, #0
	ble	.L320
	mov	r1, r2
	mov	r0, r3, asl #14
	str	r2, [fp, #-220]
	str	r3, [fp, #-212]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-220]
	ldr	r3, [fp, #-212]
	mov	r1, r2
	str	r2, [fp, #-212]
	str	r3, [fp, #-220]
	mov	r9, r0
	rsb	r0, r3, r2
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
	ldr	r2, [fp, #-212]
	ldr	r3, [fp, #-220]
.L294:
	str	r3, [r7, #924]
	str	r2, [r7, #928]
	str	r9, [r7, #932]
	str	r0, [r7, #936]
	b	.L290
.L284:
	ldr	r3, [fp, #-204]
	mov	r2, #1
	ldr	r1, [r7, #1016]
	ldr	r0, [r3, #2456]
	bl	FSP_ClearLogicFs
	ldr	r3, .L399
	ldr	r1, .L399+64
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	b	.L358
.L271:
	ldr	r1, [r7, #1016]
	mov	r2, #1
	str	r3, [fp, #-192]
.L371:
	ldr	r3, [fp, #-204]
	ldr	r0, [r3, #2456]
	bl	FSP_ClearLogicFs
	ldr	r3, [fp, #-192]
	mov	r0, r3
	b	.L358
.L318:
	mvn	r8, #1
	b	.L244
.L393:
	str	r3, [fp, #-192]
	mov	r2, r0
	ldr	r1, [r7, #1016]
	b	.L371
.L395:
	ldr	r3, .L399
	movw	r2, #2210
	ldr	r1, .L399+68
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	b	.L358
.L400:
	.align	2
.L399:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	g_event_report
	.word	.LC16
	.word	.LC19
	.word	.LC20
	.word	.LC21
	.word	.LC24
	.word	.LANCHOR0+708
	.word	.LC3
	.word	.LC14
	.word	.LC15
	.word	.LC18
	.word	.LC17
	.word	.LANCHOR0+724
	.word	.LC22
	.word	.LC23
	.word	.LC25
.L316:
	mov	r0, r6
	bl	Real9_ModifySliceMsg
	cmp	r0, #1
	bne	.L398
	ldr	r2, [fp, #-192]
	ldr	r3, [r6]
	str	r2, [r6, #4]
	ldr	r2, [r3, #900]
	cmp	r2, #1
	bne	.L313
	ldr	r2, [fp, #-192]
	cmp	r2, #0
	beq	.L314
	mov	r5, r2
.L317:
	ldrb	r2, [r5, #1]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L314
	ldr	r3, [fp, #-204]
	mov	r5, #0
	mov	r2, r5
	str	r5, [r6, #4]
	ldr	r1, [r7, #1016]
	ldr	r0, [r3, #2456]
	bl	FSP_SetDisplay
	mov	r0, #9
	mov	r1, r6
	bl	ReleasePacket
	mov	r0, r5
	b	.L358
.L397:
	ldr	r2, [r3, #904]
	cmp	r2, #0
	ble	.L314
	ldr	r2, [r6, #4]
	cmp	r2, #0
	beq	.L314
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L314
	ldr	r3, [fp, #-204]
	mov	r5, #0
	mov	r2, r5
	str	r5, [r6, #4]
	ldr	r1, [r7, #1016]
	ldr	r0, [r3, #2456]
	bl	FSP_SetDisplay
	ldr	r2, [r6]
	mov	r0, #9
	mov	r1, r6
	ldr	r3, [r2, #904]
	sub	r3, r3, #1
	str	r3, [r2, #904]
	bl	ReleasePacket
	mov	r0, r5
	b	.L358
.L320:
	mov	r0, #0
	mov	r9, r0
	b	.L294
.L398:
	ldr	r3, [fp, #-204]
	mov	r2, r4
	ldr	r1, [r7, #1016]
	ldr	r0, [r3, #2456]
	bl	FSP_ClearLogicFs
	mov	r0, r5
	b	.L358
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
	add	r4, r0, #77824
	mov	r2, #0
	ldr	r0, [r4, #2456]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #2456]
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r4, r0, #0
	beq	.L422
	ldr	r3, [r4]
	ldr	r3, [r3, #12]
	cmp	r3, #1
	beq	.L421
	add	r7, r4, #45056
	add	r6, r4, #77824
	ldr	r1, [r7, #1012]
	ldr	r0, [r6, #2456]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L421
	ldr	r1, [r7, #1012]
	ldr	r0, [r6, #2456]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L420
.L421:
	add	r5, r4, #46080
	add	r5, r5, #40
.L410:
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	GetVoLastImageID
.L420:
	mov	r0, r4
	add	r5, r4, #46080
	bl	Real9_SetImgFormat
	add	r5, r5, #40
	mov	r3, #1
	str	r3, [r8, #244]
	mov	r2, r3
	ldr	r1, [r7, #1012]
	ldr	r0, [r6, #2456]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #2456]
	mov	r2, r4
	mov	r3, r5
	str	r8, [sp]
	mov	r1, #9
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L408
	ldr	r1, [r7, #1012]
	mov	r2, #0
	ldr	r0, [r6, #2456]
	bl	FSP_SetDisplay
	b	.L410
.L408:
	ldr	r3, [r8, #200]
	cmp	r3, #100
	bhi	.L410
	ldr	r3, [r8, #164]
	cmp	r3, #31
	bls	.L410
	ldr	r3, [r8, #168]
	cmp	r3, #31
	movhi	r0, #0
	bls	.L410
.L417:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L422:
	ldr	ip, .L423
	movw	r3, #2326
	ldr	r2, .L423+4
	mov	r0, #1
	ldr	r1, .L423+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L417
.L424:
	.align	2
.L423:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+740
	.word	.LC3
	UNWIND(.fnend)
	.size	REAL9DEC_GetRemainImg, .-REAL9DEC_GetRemainImg
	.align	2
	.global	REAL9DEC_VDMPostProc
	.type	REAL9DEC_VDMPostProc, %function
REAL9DEC_VDMPostProc:
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
	subs	r4, r0, #0
	mov	r6, r1
	mov	r10, r2
	beq	.L453
	ldr	r8, .L456
	mov	r2, r1
	mov	r0, #22
	ldr	r1, .L456+4
	add	r5, r4, #45056
	add	r7, r4, #77824
	ldr	r3, [r8, #68]
	add	r9, r4, #8192
	blx	r3
	mov	r1, r4
	mov	r0, #9
	bl	ReleasePacket
	ldr	r1, [r5, #1016]
	ldr	r0, [r7, #2456]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L427
	add	r3, r4, #40960
	ldr	r2, [r3, #3768]
	cmp	r2, #2
	andne	r10, r10, #31
	strb	r2, [r9, #3174]
	strne	r10, [r3, #3936]
	cmp	r6, #0
	movlt	r6, #0
	blt	.L429
	cmp	r6, #100
	movge	r6, #100
.L429:
	ldr	r2, [r8, #68]
	str	r6, [r0, #200]
	mov	r0, #22
	ldr	r1, .L456+8
	str	r3, [fp, #-48]
	blx	r2
	mov	r0, r4
	bl	Real9_SetImgFormat
	ldrb	r2, [r9, #3172]	@ zero_extendqisi2
	ldr	r3, [fp, #-48]
	cmp	r2, #2
	beq	.L432
	ldr	r2, [r4]
	ldr	r2, [r2, #12]
	cmp	r2, #1
	beq	.L432
	ldr	r3, [r3, #3768]
	cmp	r3, #2
	beq	.L432
	ldrb	r3, [r9, #3173]	@ zero_extendqisi2
	cmp	r3, #1
	ldrhi	r1, [r5, #1008]
	mvnls	r1, #0
	cmn	r1, #1
	str	r1, [r5, #1020]
	beq	.L434
.L455:
	ldr	r0, [r7, #2456]
	bl	FSP_GetFsImagePtr
	ldr	r6, [r5, #1020]
	ldr	r8, [r8, #68]
	mov	r1, r6
	mov	r9, r0
	ldr	r0, [r7, #2456]
	bl	FSP_GetRef
	mov	r2, r6
	ldr	r1, .L456+12
	mov	r3, r0
	mov	r0, #12
	blx	r8
	mov	r2, #1
	ldr	r1, [r5, #1020]
	ldr	r0, [r7, #2456]
	bl	FSP_SetDisplay
	add	r3, r4, #46080
	ldr	r0, [r7, #2456]
	add	r3, r3, #40
	str	r9, [sp]
	mov	r2, r4
	mov	r1, #9
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L454
.L434:
	ldr	r3, [r5, #908]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r5, #908]
.L427:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L432:
	ldr	r1, [r5, #1016]
	cmn	r1, #1
	str	r1, [r5, #1020]
	bne	.L455
	b	.L434
.L454:
	ldr	r0, [r7, #2456]
	mov	r2, #0
	ldr	r1, [r5, #1020]
	bl	FSP_SetDisplay
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L453:
	ldr	ip, .L456
	movw	r3, #2390
	ldr	r2, .L456+16
	mov	r0, #1
	ldr	r1, .L456+20
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L457:
	.align	2
.L456:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LANCHOR0+764
	.word	.LC3
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
	beq	.L465
	add	r4, r5, #77824
	ldr	r0, [r4, #2456]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #2456]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L466
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L466:
	add	r1, r5, #46080
	ldr	r0, [r4, #2456]
	add	r1, r1, #40
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L465:
	ldr	ip, .L467
	movw	r3, #2472
	ldr	r2, .L467+4
	mov	r0, #1
	ldr	r1, .L467+8
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L468:
	.align	2
.L467:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+788
	.word	.LC3
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
	ldr	ip, .L471
	movw	r3, #2492
	ldr	r2, .L471+4
	mov	r0, #1
	ldr	r1, .L471+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L472:
	.align	2
.L471:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+812
	.word	.LC3
	UNWIND(.fnend)
	.size	REAL9DEC_Support, .-REAL9DEC_Support
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	MBA_FieldWidth, %object
	.size	MBA_FieldWidth, 24
MBA_FieldWidth:
	.word	6
	.word	7
	.word	9
	.word	11
	.word	13
	.word	14
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
	.type	__func__.13376, %object
	.size	__func__.13376, 20
__func__.13376:
	.ascii	"RV9_RecordVFMWState\000"
	.type	__func__.13399, %object
	.size	__func__.13399, 15
__func__.13399:
	.ascii	"Real9_WriteReg\000"
	.space	1
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
	.type	__func__.13245, %object
	.size	__func__.13245, 21
__func__.13245:
	.ascii	"Real9_GetImageBuffer\000"
	.space	3
	.type	__func__.13259, %object
	.size	__func__.13259, 20
__func__.13259:
	.ascii	"Real9_ArrangeVHBMem\000"
	.type	__func__.13312, %object
	.size	__func__.13312, 32
__func__.13312:
	.ascii	"Real9_CB_SearchBits_IgnoreOnly0\000"
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
	.type	__func__.13320, %object
	.size	__func__.13320, 16
__func__.13320:
	.ascii	"Real9_CB_GetSSC\000"
	.type	__func__.13369, %object
	.size	__func__.13369, 19
__func__.13369:
	.ascii	"Real9_SetImgFormat\000"
	.space	1
	.type	__func__.13386, %object
	.size	__func__.13386, 20
__func__.13386:
	.ascii	"Real9_WriteSliceMsg\000"
	.type	__func__.13393, %object
	.size	__func__.13393, 18
__func__.13393:
	.ascii	"Real9_WritePicMsg\000"
	.space	2
	.type	__func__.13409, %object
	.size	__func__.13409, 21
__func__.13409:
	.ascii	"Real9_ModifySliceMsg\000"
	.space	3
	.type	__func__.13432, %object
	.size	__func__.13432, 14
__func__.13432:
	.ascii	"REAL9DEC_Init\000"
	.space	2
	.type	__func__.13437, %object
	.size	__func__.13437, 17
__func__.13437:
	.ascii	"REAL9DEC_Destroy\000"
	.space	3
	.type	__func__.13472, %object
	.size	__func__.13472, 16
__func__.13472:
	.ascii	"REAL9DEC_Decode\000"
	.type	__FUNCTION__.13480, %object
	.size	__FUNCTION__.13480, 16
__FUNCTION__.13480:
	.ascii	"REAL9DEC_Decode\000"
	.type	__func__.13498, %object
	.size	__func__.13498, 22
__func__.13498:
	.ascii	"REAL9DEC_GetRemainImg\000"
	.space	2
	.type	__func__.13507, %object
	.size	__func__.13507, 21
__func__.13507:
	.ascii	"REAL9DEC_VDMPostProc\000"
	.space	3
	.type	__func__.13513, %object
	.size	__func__.13513, 24
__func__.13513:
	.ascii	"REAL9DEC_GetImageBuffer\000"
	.type	__func__.13517, %object
	.size	__func__.13517, 17
__func__.13517:
	.ascii	"REAL9DEC_Support\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC3:
	ASCII(.ascii	"[%s %d]assert warning\012\000" )
	.space	1
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
	ASCII(.ascii	"real9 actual frame size(%dx%d) exeed max config(%dx" )
	ASCII(.ascii	"%d)\012\000" )
.LC10:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC12:
	ASCII(.ascii	"Decoding quits at frm %d\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
.LC14:
	ASCII(.ascii	"Real9_CB_GetPictureHeader Error!\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"pic width/height to large,MbWidth = %d, MbHeight = " )
	ASCII(.ascii	"%d\000" )
	.space	2
.LC16:
	ASCII(.ascii	"new seq size %d * %d\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"Real9_ArrangeVHBMem err\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"Fatal Error: frm%d, get image buffer failed\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"++++++++++ ref %d\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"CurFsID abnormal!,%s %d (NULL == pCur) || (NULL == " )
	ASCII(.ascii	"pFwd) || (NULL == pBwd)!!\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"CurFsID abnormal!\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p," )
	ASCII(.ascii	"%p,%p,%p,%p\012\000" )
.LC25:
	ASCII(.ascii	"line:%d! i > (RV9_MAX_SLC_PARAM_NUM - 2)\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"DEBUG: DEC over\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
