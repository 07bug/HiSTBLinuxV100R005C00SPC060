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
	.file	"vp9.c"
	.text
	.align	2
	.global	VP9_u_v_x
	.type	VP9_u_v_x, %function
VP9_u_v_x:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	VP9_u_v_x, .-VP9_u_v_x
	.align	2
	.global	VP9_s_v
	.type	VP9_s_v, %function
VP9_s_v:
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
	add	r1, r1, #1
	bl	BsGet
	tst	r0, #1
	mov	r0, r0, asr #1
	rsbne	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_s_v, .-VP9_s_v
	.align	2
	.global	Vp9_Cabac_ReadIsValid
	.type	Vp9_Cabac_ReadIsValid, %function
Vp9_Cabac_ReadIsValid:
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
	cmp	r2, #0
	cmpne	r0, #0
	moveq	r3, #1
	movne	r3, #0
	beq	.L7
	cmp	r1, #0
	ble	.L8
	add	r0, r0, r1
	cmp	r2, r0
	movcc	r0, #0
	movcs	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L7:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L8:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Cabac_ReadIsValid, .-Vp9_Cabac_ReadIsValid
	.align	2
	.global	Vp9_Cabac_ReaderFill
	.type	Vp9_Cabac_ReaderFill, %function
Vp9_Cabac_ReaderFill:
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
	ldr	r5, [r0, #32]
	mov	r7, r0
	ldr	r8, [r0, #28]
	rsb	r6, r5, #24
	rsb	r4, r5, #16
	bic	r6, r6, #7
	rsb	r4, r6, r4
	add	r5, r5, r6
	mov	r1, r6
	and	r4, r4, #7
	bl	BsGet
	str	r5, [r7, #32]
	orr	r0, r8, r0, asl r4
	str	r0, [r7, #28]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Cabac_ReaderFill, .-Vp9_Cabac_ReaderFill
	.align	2
	.global	Vp9_Cabac_Read
	.type	Vp9_Cabac_Read, %function
Vp9_Cabac_Read:
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
	ldr	r4, [r0, #36]
	mov	r5, r0
	ldr	r6, [r0, #32]
	sub	r4, r4, #1
	cmp	r6, #0
	mul	r1, r4, r1
	mov	r4, r1, lsr #8
	add	r4, r4, #1
	blt	.L12
	ldr	r3, [r0, #28]
.L13:
	mov	r2, r4, asl #24
	cmp	r2, r3
	rsbls	r3, r2, r3
	ldr	r2, .L16
	ldrls	r1, [r5, #36]
	movls	r0, #1
	movhi	r0, #0
	rsbls	r4, r4, r1
	ldrb	r1, [r2, r4]	@ zero_extendqisi2
	mov	r3, r3, asl r1
	rsb	r6, r1, r6
	mov	r4, r4, asl r1
	str	r3, [r5, #28]
	str	r6, [r5, #32]
	str	r4, [r5, #36]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L12:
	rsb	r1, r6, #24
	rsb	r8, r6, #16
	bic	r1, r1, #7
	ldr	r7, [r0, #28]
	rsb	r8, r1, r8
	add	r6, r6, r1
	bl	BsGet
	and	r3, r8, #7
	orr	r3, r7, r0, asl r3
	b	.L13
.L17:
	.align	2
.L16:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_Cabac_Read, .-Vp9_Cabac_Read
	.align	2
	.global	Vp9_Cabac_ReadLiteral
	.type	Vp9_Cabac_ReadLiteral, %function
Vp9_Cabac_ReadLiteral:
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
	subs	r7, r1, #1
	mov	r6, r0
	bmi	.L23
	ldr	r8, [r0, #28]
	mov	r9, #0
	ldr	r4, [r0, #36]
	mov	r3, #1
	ldr	r5, [r0, #32]
	ldr	r10, .L27
	b	.L22
.L20:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r10, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L19
.L22:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L20
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	r3, [fp, #-52]
	str	r2, [fp, #-48]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-52]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L20
.L23:
	mov	r9, #0
.L19:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L28:
	.align	2
.L27:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_Cabac_ReadLiteral, .-Vp9_Cabac_ReadLiteral
	.align	2
	.global	Vp9_Cabac_ReaderInit
	.type	Vp9_Cabac_ReaderInit, %function
Vp9_Cabac_ReaderInit:
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
	mvn	r2, #7
	mov	r3, #255
	mov	r5, #0
	str	r2, [r0, #32]
	str	r3, [r0, #36]
	mov	r1, #32
	str	r5, [r0, #28]
	mov	r4, r0
	bl	BsGet
	mov	r2, r0
	ldr	r0, [r4, #36]
	sub	r3, r0, #1
	ubfx	r3, r3, #1, #24
	add	r3, r3, #1
	mov	r1, r3, asl #24
	cmp	r2, r1
	rsbcs	r2, r1, r2
	ldr	r1, .L32
	rsbcs	r3, r3, r0
	movcc	r0, r5
	movcs	r0, #1
	ldrb	r1, [r1, r3]	@ zero_extendqisi2
	mov	r2, r2, asl r1
	mov	r3, r3, asl r1
	str	r2, [r4, #28]
	rsb	r1, r1, #24
	str	r3, [r4, #36]
	str	r1, [r4, #32]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L33:
	.align	2
.L32:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_Cabac_ReaderInit, .-Vp9_Cabac_ReaderInit
	.align	2
	.global	Vp9_ReadTxMode
	.type	Vp9_ReadTxMode, %function
Vp9_ReadTxMode:
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
	mov	r7, #1
	mov	r6, r0
	ldr	r10, .L48
	ldr	r4, [r0, #36]
	mov	r3, r7
	ldr	r5, [r0, #32]
	mov	r9, #0
	ldr	r8, [r0, #28]
	b	.L37
.L35:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r10, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L45
.L37:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L35
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	r3, [fp, #-52]
	str	r2, [fp, #-48]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-52]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L35
.L45:
	cmp	r9, #3
	beq	.L46
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L46:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	add	r4, r4, #1
	movge	r0, r8
	blt	.L47
.L39:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r9, #4
	rsbls	r4, r4, r2
	ldrb	r3, [r10, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	mov	r0, r9
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L47:
	rsb	r1, r5, #24
	rsb	r7, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r7, r1, r7
	add	r5, r1, r5
	bl	BsGet
	and	r7, r7, #7
	orr	r0, r8, r0, asl r7
	b	.L39
.L49:
	.align	2
.L48:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ReadTxMode, .-Vp9_ReadTxMode
	.align	2
	.global	Vp9_ReadTxProbs
	.type	Vp9_ReadTxProbs, %function
Vp9_ReadTxProbs:
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
	ldr	r6, .L399
	ldr	r4, [r1, #28]
	mov	r5, r1
	ldr	r8, [r1, #36]
	add	r2, r0, #2
	ldr	r7, [r1, #32]
	str	r0, [fp, #-60]
	str	r2, [fp, #-56]
	str	r0, [fp, #-48]
	str	r0, [fp, #-52]
.L83:
	sub	r9, r8, #1
	cmp	r7, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L345
.L51:
	mov	r8, r9, asl #24
	cmp	r8, r4
	bhi	.L52
	ldr	r3, [r5, #36]
	rsb	r8, r8, r4
	rsb	r9, r9, r3
	ldrb	r0, [r6, r9]	@ zero_extendqisi2
	mov	r9, r9, asl r0
	rsb	r7, r0, r7
	sub	r10, r9, #1
	cmp	r7, #0
	ubfx	r10, r10, #1, #24
	mov	r8, r8, asl r0
	str	r9, [r5, #36]
	add	r10, r10, #1
	str	r7, [r5, #32]
	str	r8, [r5, #28]
	blt	.L346
.L53:
	mov	r2, r10, asl #24
	cmp	r2, r8
	bhi	.L54
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r10, r10, r3
	ldrb	r0, [r6, r10]	@ zero_extendqisi2
	mov	r3, r10, asl r0
	rsb	r4, r0, r7
	sub	r10, r3, #1
	cmp	r4, #0
	ubfx	r10, r10, #1, #24
	mov	r8, r8, asl r0
	str	r3, [r5, #36]
	add	r10, r10, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L347
.L56:
	mov	r2, r10, asl #24
	cmp	r2, r8
	bhi	.L61
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r3, r10, r3
	ldrb	r0, [r6, r3]	@ zero_extendqisi2
	mov	r3, r3, asl r0
	rsb	r4, r0, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L348
.L63:
	mov	r10, r7, asl #24
	cmp	r10, r8
	bhi	.L67
	ldr	r1, [r5, #36]
	rsb	r8, r10, r8
	mov	r3, #6
	mov	r9, #0
	rsb	r7, r7, r1
	mov	r2, #1
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L68
.L72:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r8, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L349
.L68:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r10
	add	r7, r7, #1
	bge	.L72
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	b	.L72
.L52:
	ldrb	r8, [r6, r9]	@ zero_extendqisi2
	mov	r4, r4, asl r8
	rsb	r7, r8, r7
	str	r4, [r5, #28]
	mov	r8, r9, asl r8
	str	r7, [r5, #32]
	str	r8, [r5, #36]
.L241:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, r2
	bne	.L83
	ldr	r3, [fp, #-60]
	mov	r10, r4
	add	r2, r3, #4
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
.L144:
	sub	r9, r8, #1
	cmp	r7, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L350
.L84:
	mov	r8, r9, asl #24
	cmp	r8, r10
	bhi	.L85
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r9, r9, r3
	ldrb	r0, [r6, r9]	@ zero_extendqisi2
	mov	r9, r9, asl r0
	rsb	r4, r0, r7
	sub	r10, r9, #1
	cmp	r4, #0
	ubfx	r10, r10, #1, #24
	mov	r8, r8, asl r0
	str	r9, [r5, #36]
	add	r10, r10, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L351
.L86:
	mov	r2, r10, asl #24
	cmp	r2, r8
	bhi	.L87
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r3, r10, r3
	ldrb	r10, [r6, r3]	@ zero_extendqisi2
	mov	r3, r3, asl r10
	rsb	r4, r10, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L352
.L89:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L94
	ldr	r2, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r2
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r2, r7, asl r3
	rsb	r8, r3, r4
	sub	r7, r2, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r3
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r10, [r5, #28]
	blt	.L353
.L96:
	mov	r3, r7, asl #24
	cmp	r3, r10
	bhi	.L100
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r4
	mov	r2, #1
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	b	.L101
.L105:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L354
.L101:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L105
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L105
.L85:
	ldrb	r3, [r6, r9]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r7
	mov	r9, r9, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r9, [r5, #36]
.L242:
	sub	r9, r9, #1
	cmp	r4, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L355
.L114:
	mov	r8, r9, asl #24
	cmp	r8, r10
	bhi	.L115
	ldr	r3, [r5, #36]
	rsb	r10, r8, r10
	rsb	r9, r9, r3
	ldrb	r8, [r6, r9]	@ zero_extendqisi2
	mov	r9, r9, asl r8
	rsb	r4, r8, r4
	sub	r7, r9, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r8
	str	r9, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L356
.L116:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L117
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r7, r7, r3
	ldrb	r10, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r10
	rsb	r4, r10, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L357
.L119:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L124
	ldr	r2, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r2
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r2, r7, asl r3
	rsb	r8, r3, r4
	sub	r7, r2, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r3
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r10, [r5, #28]
	blt	.L358
.L126:
	mov	r3, r7, asl #24
	cmp	r3, r10
	bhi	.L130
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r4
	mov	r2, #1
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	b	.L131
.L135:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L359
.L131:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L135
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L135
.L115:
	ldrb	r8, [r6, r9]	@ zero_extendqisi2
	mov	r10, r10, asl r8
	rsb	r7, r8, r4
	str	r10, [r5, #28]
	mov	r8, r9, asl r8
	str	r7, [r5, #32]
	str	r8, [r5, #36]
.L243:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r3, r3, #2
	str	r3, [fp, #-52]
	cmp	r3, r2
	bne	.L144
	ldr	r3, [fp, #-60]
	mov	r9, r8
	add	r3, r3, #6
	str	r3, [fp, #-52]
.L240:
	sub	r9, r9, #1
	cmp	r7, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L360
.L145:
	mov	r8, r9, asl #24
	cmp	r8, r10
	bhi	.L146
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r9, r9, r3
	ldrb	r0, [r6, r9]	@ zero_extendqisi2
	mov	r9, r9, asl r0
	rsb	r4, r0, r7
	sub	r10, r9, #1
	cmp	r4, #0
	ubfx	r10, r10, #1, #24
	mov	r8, r8, asl r0
	str	r9, [r5, #36]
	add	r10, r10, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L361
.L147:
	mov	r3, r10, asl #24
	cmp	r3, r8
	bhi	.L148
	ldr	r7, [r5, #36]
	rsb	r8, r3, r8
	rsb	r10, r10, r7
	ldrb	r0, [r6, r10]	@ zero_extendqisi2
	mov	r10, r10, asl r0
	rsb	r4, r0, r4
	sub	r7, r10, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	r10, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L362
.L150:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L155
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r0
	rsb	r4, r0, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L363
.L157:
	mov	r10, r7, asl #24
	cmp	r10, r8
	bhi	.L161
	ldr	r1, [r5, #36]
	rsb	r8, r10, r8
	mov	r3, #6
	mov	r9, #0
	rsb	r7, r7, r1
	mov	r2, #1
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L162
.L166:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r8, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L364
.L162:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r10
	add	r7, r7, #1
	bge	.L166
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	b	.L166
.L146:
	ldrb	r3, [r6, r9]	@ zero_extendqisi2
	mov	r8, r10, asl r3
	rsb	r4, r3, r7
	mov	r9, r9, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r9, [r5, #36]
.L244:
	sub	r9, r9, #1
	cmp	r4, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L365
.L177:
	mov	r0, r9, asl #24
	cmp	r0, r8
	bhi	.L178
	ldr	r3, [r5, #36]
	rsb	r8, r0, r8
	rsb	r9, r9, r3
	ldrb	r0, [r6, r9]	@ zero_extendqisi2
	mov	r9, r9, asl r0
	rsb	r4, r0, r4
	sub	r7, r9, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	r9, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L366
.L179:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L180
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r0
	rsb	r4, r0, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L367
.L182:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L187
	ldr	r2, [r5, #36]
	rsb	r8, r3, r8
	rsb	r7, r7, r2
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r2, r7, asl r3
	rsb	r4, r3, r4
	sub	r7, r2, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r3
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L368
.L189:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L193
	ldr	r1, [r5, #36]
	rsb	r8, r3, r8
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r1
	mov	r2, #1
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L194
.L198:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L369
.L194:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L198
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L198
.L178:
	ldrb	r7, [r6, r9]	@ zero_extendqisi2
	mov	r8, r8, asl r7
	rsb	r4, r7, r4
	mov	r9, r9, asl r7
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r9, [r5, #36]
.L245:
	sub	r9, r9, #1
	cmp	r4, #0
	mov	r7, r9, asl #8
	sub	r7, r7, r9, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L370
.L207:
	mov	r0, r7, asl #24
	cmp	r0, r8
	bhi	.L208
	ldr	r3, [r5, #36]
	rsb	r8, r0, r8
	rsb	r7, r7, r3
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r0
	rsb	r4, r0, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L371
.L209:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L210
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r0
	rsb	r4, r0, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L372
.L212:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L217
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	ldrb	r0, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r0
	rsb	r4, r0, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r8, r8, asl r0
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r8, [r5, #28]
	blt	.L373
.L219:
	mov	r10, r7, asl #24
	cmp	r10, r8
	bhi	.L223
	ldr	r1, [r5, #36]
	rsb	r8, r10, r8
	mov	r3, #6
	mov	r9, #0
	rsb	r7, r7, r1
	mov	r2, #1
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r10, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L224
.L228:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r8, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L374
.L224:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r10
	add	r7, r7, #1
	bge	.L228
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	b	.L228
.L208:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L246:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #3
	str	r3, [fp, #-48]
	cmp	r3, r2
	ldrne	r10, [r5, #28]
	ldrne	r9, [r5, #36]
	ldrne	r7, [r5, #32]
	bne	.L240
.L50:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L180:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L185
.L183:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L186
.L185:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L183
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L183
.L148:
	ldrb	r7, [r6, r10]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r10, r10, asl r7
	mov	r8, r8, asl r7
	rsb	r4, r7, r4
	str	r10, [r5, #36]
	mov	r7, r10
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	b	.L153
.L151:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L154
.L153:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L151
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L151
.L117:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L122
.L120:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L123
.L122:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L120
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L120
.L87:
	ldrb	r7, [r6, r10]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r10, r10, asl r7
	mov	r8, r8, asl r7
	rsb	r4, r7, r4
	str	r10, [r5, #36]
	mov	r7, r10
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	b	.L92
.L90:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L93
.L92:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L90
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L90
.L54:
	ldrb	r4, [r6, r10]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r10, r10, asl r4
	mov	r8, r8, asl r4
	rsb	r7, r4, r7
	str	r10, [r5, #36]
	mov	r4, r10
	str	r8, [r5, #28]
	str	r7, [r5, #32]
	mov	r10, r3
	b	.L59
.L400:
	.align	2
.L399:
	.word	.LANCHOR0
.L57:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r8, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L60
.L59:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L57
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r7, r1, r7
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L57
.L210:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L215
.L213:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L216
.L215:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L213
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L213
.L369:
	cmp	r9, #64
	ble	.L200
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L200:
	add	r9, r9, #64
.L186:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L201
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L202
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L202:
	add	r3, r3, #1
.L204:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #7]
	ldr	r8, [r5, #28]
	ldr	r9, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L245
.L364:
	cmp	r9, #64
	bgt	.L375
.L168:
	add	r9, r9, #64
.L154:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L171
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L172
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L172:
	add	r3, r3, #1
.L174:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #6]
	ldr	r8, [r5, #28]
	ldr	r9, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L244
.L374:
	cmp	r9, #64
	bgt	.L376
.L230:
	add	r9, r9, #64
.L216:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L233
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L234
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L234:
	add	r3, r3, #1
.L236:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #8]
	b	.L246
.L354:
	cmp	r9, #64
	ble	.L107
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L107:
	add	r9, r9, #64
.L93:
	ldr	r3, [fp, #-52]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L108
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L109
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L109:
	add	r3, r3, #1
.L111:
	ldr	r2, [fp, #-52]
	strb	r3, [r2, #2]
	ldr	r10, [r5, #28]
	ldr	r9, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L242
.L349:
	cmp	r9, #64
	bgt	.L377
.L74:
	add	r9, r9, #64
.L60:
	ldr	r3, [fp, #-52]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L77
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L78
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L78:
	add	r3, r3, #1
.L80:
	ldr	r2, [fp, #-52]
	add	r4, r5, #28
	strb	r3, [r2]
	ldmia	r4, {r4, r7, r8}
	b	.L241
.L359:
	cmp	r9, #64
	ble	.L137
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L137:
	add	r9, r9, #64
.L123:
	ldr	r3, [fp, #-52]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L138
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L139
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L139:
	add	r3, r3, #1
.L141:
	ldr	r2, [fp, #-52]
	strb	r3, [r2, #3]
	ldr	r10, [r5, #28]
	ldr	r8, [r5, #36]
	ldr	r7, [r5, #32]
	b	.L243
.L138:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L378
	rsb	r3, r3, #255
	b	.L141
.L77:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L379
	rsb	r3, r3, #255
	b	.L80
.L108:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L380
	rsb	r3, r3, #255
	b	.L111
.L233:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L381
	rsb	r3, r3, #255
	b	.L236
.L171:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L382
	rsb	r3, r3, #255
	b	.L174
.L201:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L383
	rsb	r3, r3, #255
	b	.L204
.L355:
	rsb	r7, r4, #24
	mov	r0, r5
	bic	r7, r7, #7
	rsb	r8, r4, #16
	rsb	r8, r7, r8
	add	r4, r7, r4
	mov	r1, r7
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L114
.L345:
	rsb	r10, r7, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r8, r7, #16
	rsb	r8, r10, r8
	add	r7, r10, r7
	mov	r1, r10
	and	r8, r8, #7
	bl	BsGet
	str	r7, [r5, #32]
	orr	r0, r4, r0, asl r8
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L51
.L365:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r7, r4, #16
	rsb	r7, r10, r7
	add	r4, r10, r4
	mov	r1, r10
	and	r7, r7, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r7
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L177
.L370:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r10, r4
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L207
.L360:
	rsb	r4, r7, #24
	mov	r0, r5
	bic	r4, r4, #7
	rsb	r8, r7, #16
	rsb	r8, r4, r8
	mov	r1, r4
	and	r8, r8, #7
	bl	BsGet
	add	r4, r4, r7
	str	r4, [r5, #32]
	mov	r7, r4
	orr	r0, r10, r0, asl r8
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L145
.L350:
	rsb	r4, r7, #24
	mov	r0, r5
	bic	r4, r4, #7
	rsb	r8, r7, #16
	rsb	r8, r4, r8
	mov	r1, r4
	and	r8, r8, #7
	bl	BsGet
	add	r4, r4, r7
	str	r4, [r5, #32]
	mov	r7, r4
	orr	r0, r10, r0, asl r8
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L84
.L383:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L204
.L382:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L174
.L381:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L236
.L380:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L111
.L379:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L80
.L378:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L141
.L161:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L165
.L163:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L384
.L165:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L163
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L163
.L193:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L197
.L195:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L385
.L197:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L195
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L195
.L130:
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	mov	r7, r7, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r7, [r5, #36]
	mov	r4, r7
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	mov	r7, r2
	b	.L134
.L132:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L386
.L134:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L132
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	r3, [fp, #-68]
	str	r2, [fp, #-64]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L132
.L67:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L71
.L69:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L387
.L71:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L69
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L69
.L100:
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	mov	r7, r7, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r7, [r5, #36]
	mov	r4, r7
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	mov	r7, r2
	b	.L104
.L102:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L388
.L104:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L102
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	r3, [fp, #-68]
	str	r2, [fp, #-64]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L102
.L223:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L227
.L225:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L389
.L227:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L225
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L225
.L94:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L99
.L97:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L390
.L99:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L97
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L97
.L187:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L192
.L190:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L391
.L192:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L190
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L190
.L155:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L160
.L158:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L392
.L160:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L158
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L158
.L217:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L222
.L220:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L393
.L222:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L220
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L220
.L124:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L129
.L127:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L394
.L129:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L127
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L127
.L61:
	ldrb	r7, [r6, r10]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r10, r10, asl r7
	mov	r8, r8, asl r7
	rsb	r4, r7, r4
	str	r10, [r5, #36]
	mov	r7, r10
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	b	.L66
.L64:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L395
.L66:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L64
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L64
.L395:
	add	r9, r9, #16
	b	.L60
.L391:
	add	r9, r9, #16
	b	.L186
.L390:
	add	r9, r9, #16
	b	.L93
.L394:
	add	r9, r9, #16
	b	.L123
.L393:
	add	r9, r9, #16
	b	.L216
.L392:
	add	r9, r9, #16
	b	.L154
.L386:
	add	r9, r9, #32
	b	.L123
.L385:
	add	r9, r9, #32
	b	.L186
.L384:
	add	r9, r9, #32
	b	.L154
.L388:
	add	r9, r9, #32
	b	.L93
.L387:
	add	r9, r9, #32
	b	.L60
.L389:
	add	r9, r9, #32
	b	.L216
.L346:
	rsb	r9, r7, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r4, r7, #16
	rsb	r4, r9, r4
	add	r7, r7, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r7, [r5, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L53
.L351:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r7, r4, #16
	rsb	r7, r9, r7
	add	r4, r4, r9
	mov	r1, r9
	and	r7, r7, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r7
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L86
.L356:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L116
.L361:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r7, r4, #16
	rsb	r7, r9, r7
	add	r4, r4, r9
	mov	r1, r9
	and	r7, r7, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r7
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L147
.L366:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L179
.L371:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L209
.L375:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r9, r9, asl #1
	add	r7, r7, #1
	sub	r9, r9, #65
	movge	r0, r10
	blt	.L396
.L169:
	mov	r3, r7, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r5, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r9, r9, r2
	rsbls	r7, r7, r1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L168
.L377:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r9, r9, asl #1
	add	r7, r7, #1
	sub	r9, r9, #65
	movge	r0, r10
	blt	.L397
.L75:
	mov	r3, r7, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r5, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r9, r9, r2
	rsbls	r7, r7, r1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L74
.L376:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r9, r9, asl #1
	add	r7, r7, #1
	sub	r9, r9, #65
	movge	r0, r10
	blt	.L398
.L231:
	mov	r3, r7, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r5, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r9, r9, r2
	rsbls	r7, r7, r1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L230
.L373:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L219
.L368:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L189
.L363:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L157
.L353:
	rsb	r9, r8, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L96
.L358:
	rsb	r9, r8, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L126
.L348:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L63
.L396:
	rsb	r1, r4, #24
	rsb	r8, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r8, r1, r8
	add	r4, r1, r4
	bl	BsGet
	and	r8, r8, #7
	orr	r0, r10, r0, asl r8
	b	.L169
.L398:
	rsb	r1, r4, #24
	rsb	r8, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r8, r1, r8
	add	r4, r1, r4
	bl	BsGet
	and	r8, r8, #7
	orr	r0, r10, r0, asl r8
	b	.L231
.L397:
	rsb	r1, r4, #24
	rsb	r8, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r8, r1, r8
	add	r4, r1, r4
	bl	BsGet
	and	r8, r8, #7
	orr	r0, r10, r0, asl r8
	b	.L75
.L352:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L89
.L367:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L182
.L362:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L150
.L372:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r4, #16
	rsb	r9, r10, r9
	add	r4, r4, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r9
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L212
.L357:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L119
.L347:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r7, r4, #16
	rsb	r7, r9, r7
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r7, #7
	str	r4, [r5, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L56
	UNWIND(.fnend)
	.size	Vp9_ReadTxProbs, .-Vp9_ReadTxProbs
	.align	2
	.global	Vp9_ReaderHasError
	.type	Vp9_ReaderHasError, %function
Vp9_ReaderHasError:
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
	ldr	r0, [r0, #32]
	sub	r0, r0, #33
	cmn	r0, #-1073741790
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_ReaderHasError, .-Vp9_ReaderHasError
	.align	2
	.global	Vp9_DiffUpdateProb
	.type	Vp9_DiffUpdateProb, %function
Vp9_DiffUpdateProb:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r4, [r0, #36]
	ldr	r5, [r0, #32]
	mov	r6, r0
	sub	r4, r4, #1
	str	r1, [fp, #-48]
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	add	r10, r4, #1
	blt	.L403
	ldr	r7, [r0, #28]
.L404:
	mov	r0, r10, asl #24
	cmp	r0, r7
	bhi	.L405
	ldr	r4, [r6, #36]
	rsb	r7, r0, r7
	ldr	r8, .L458
	rsb	r4, r10, r4
	ldrb	r0, [r8, r4]	@ zero_extendqisi2
	mov	r3, r4, asl r0
	rsb	r5, r0, r5
	sub	r4, r3, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r7, r7, asl r0
	str	r3, [r6, #36]
	add	r4, r4, #1
	str	r5, [r6, #32]
	str	r7, [r6, #28]
	blt	.L452
.L407:
	mov	r10, r4, asl #24
	cmp	r10, r7
	bhi	.L412
	ldr	r1, [r6, #36]
	rsb	r7, r10, r7
	rsb	r4, r4, r1
	ldrb	r10, [r8, r4]	@ zero_extendqisi2
	mov	r1, r4, asl r10
	rsb	r5, r10, r5
	sub	r4, r1, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r7, asl r10
	str	r1, [r6, #36]
	add	r4, r4, #1
	str	r5, [r6, #32]
	str	r10, [r6, #28]
	blt	.L453
.L414:
	mov	r3, r4, asl #24
	cmp	r3, r10
	bhi	.L418
	ldr	r1, [r6, #36]
	rsb	r10, r3, r10
	mov	r3, #6
	mov	r9, #0
	rsb	r4, r4, r1
	mov	r2, #1
	ldrb	r1, [r8, r4]	@ zero_extendqisi2
	rsb	r7, r1, r5
	mov	r10, r10, asl r1
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r7, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L419
.L423:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r3, [r8, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r10, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
	beq	.L454
.L419:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L423
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r7, r1, r7
	bl	BsGet
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	b	.L423
.L412:
	ldrb	r1, [r8, r4]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r7, r7, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	mov	r10, r3
	str	r4, [r6, #36]
	b	.L417
.L415:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L455
.L417:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L415
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L415
.L405:
	ldr	r8, .L458
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r4, [r8, r10]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r7, [r6, #28]
	mov	r4, r10, asl r4
	str	r5, [r6, #32]
	mov	r10, r3
	str	r4, [r6, #36]
	b	.L410
.L408:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r8, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L411
.L410:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L408
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-56]
	str	r3, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-56]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L408
.L454:
	cmp	r9, #64
	ble	.L425
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl #1
	add	r4, r4, #1
	sub	r9, r9, #65
	movge	r0, r10
	blt	.L456
.L426:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r9, r9, r2
	rsbls	r4, r4, r1
	ldrb	r3, [r8, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r10, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
.L425:
	add	r9, r9, #64
.L411:
	ldr	r3, [fp, #-48]
	add	r8, r8, r9
	ldrb	r1, [r8, #256]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L428
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L429
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L429:
	ldr	r2, [fp, #-48]
	add	r3, r3, #1
	strb	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L428:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L432
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L432:
	ldr	r2, [fp, #-48]
	rsb	r3, r3, #255
	strb	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L455:
	add	r9, r9, #16
	b	.L411
.L418:
	ldrb	r1, [r8, r4]	@ zero_extendqisi2
	mov	r9, #0
	mov	r7, #4
	mov	r3, #1
	mov	r10, r10, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L422
.L420:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r8, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L457
.L422:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L420
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	r3, [fp, #-56]
	str	r2, [fp, #-52]
	add	r5, r1, r5
	bl	BsGet
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-56]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L420
.L457:
	add	r9, r9, #32
	b	.L411
.L403:
	rsb	r8, r5, #24
	ldr	r4, [r0, #28]
	bic	r8, r8, #7
	rsb	r7, r5, #16
	rsb	r7, r8, r7
	add	r5, r5, r8
	mov	r1, r8
	and	r7, r7, #7
	bl	BsGet
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r7
	str	r0, [r6, #28]
	mov	r7, r0
	b	.L404
.L452:
	rsb	r10, r5, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r9, r5, #16
	rsb	r9, r10, r9
	add	r5, r5, r10
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r5, [r6, #32]
	orr	r0, r7, r0, asl r9
	str	r0, [r6, #28]
	mov	r7, r0
	b	.L407
.L453:
	rsb	r9, r5, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r7, r5, #16
	rsb	r7, r9, r7
	add	r5, r5, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r7, #7
	str	r5, [r6, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L414
.L456:
	rsb	r1, r7, #24
	rsb	r5, r7, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r5, r1, r5
	add	r7, r1, r7
	bl	BsGet
	and	r5, r5, #7
	orr	r0, r10, r0, asl r5
	b	.L426
.L459:
	.align	2
.L458:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_DiffUpdateProb, .-Vp9_DiffUpdateProb
	.align	2
	.global	Vp9_ReadCoefProbsCommon
	.type	Vp9_ReadCoefProbsCommon, %function
Vp9_ReadCoefProbsCommon:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldr	r4, [r1, #36]
	ldr	r5, [r1, #32]
	mov	r10, r1
	sub	r4, r4, #1
	mov	r6, r0
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	add	r4, r4, #1
	blt	.L461
	ldr	r3, [r1, #28]
.L462:
	mov	r1, r4, asl #24
	cmp	r1, r3
	bhi	.L463
	ldr	r2, [r10, #36]
	rsb	r3, r1, r3
	ldr	r9, .L652
	add	r1, r6, #512
	rsb	r4, r4, r2
	add	r2, r6, #1536
	add	r2, r2, #2
	str	r2, [fp, #-80]
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	add	r1, r1, #2
	str	r1, [fp, #-76]
	rsb	r5, r2, r5
	str	r5, [r10, #32]
	mov	r5, r10
	mov	r3, r3, asl r2
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r4, [r10, #36]
.L464:
	ldr	r3, [fp, #-76]
	mov	r10, r5
	sub	r3, r3, #512
	str	r3, [fp, #-72]
.L569:
	ldr	r3, [fp, #-72]
	str	r3, [fp, #-60]
	mov	r3, #0
	str	r3, [fp, #-56]
.L567:
	ldr	r3, [fp, #-60]
	str	r3, [fp, #-48]
	mov	r3, #0
	str	r3, [fp, #-52]
.L565:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-52]
	cmp	r3, #0
	moveq	r3, #3
	movne	r3, #6
	cmp	r2, r3
	bge	.L625
	ldr	r5, [r10, #36]
	ldr	r4, [r10, #32]
	sub	r5, r5, #1
	cmp	r4, #0
	mov	r3, r5, asl #8
	sub	r5, r3, r5, asl #2
	mov	r5, r5, lsr #8
	add	r5, r5, #1
	blt	.L465
	ldr	r8, [r10, #28]
.L466:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L467
	ldr	r3, [r10, #36]
	rsb	r8, r6, r8
	rsb	r5, r5, r3
	ldrb	r6, [r9, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r6
	rsb	r4, r6, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r6
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r8, [r10, #28]
	blt	.L626
.L468:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L469
	ldr	r3, [r10, #36]
	rsb	r6, r6, r8
	rsb	r5, r5, r3
	ldrb	r8, [r9, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r8
	rsb	r4, r8, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r6, asl r8
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r8, [r10, #28]
	blt	.L627
.L471:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L476
	ldr	r2, [r10, #36]
	rsb	r8, r6, r8
	rsb	r5, r5, r2
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r2, r5, asl r3
	rsb	r6, r3, r4
	sub	r5, r2, #1
	cmp	r6, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r3
	str	r2, [r10, #36]
	add	r5, r5, #1
	str	r6, [r10, #32]
	str	r8, [r10, #28]
	blt	.L628
.L478:
	mov	r3, r5, asl #24
	cmp	r3, r8
	bhi	.L482
	ldr	r4, [r10, #36]
	rsb	r3, r3, r8
	mov	r7, #0
	mov	r8, #6
	rsb	r5, r5, r4
	mov	r2, #1
	ldrb	r4, [r9, r5]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r6, r4, r6
	str	r3, [r10, #28]
	mov	r4, r5, asl r4
	str	r6, [r10, #32]
	mov	r5, r3
	str	r4, [r10, #36]
	b	.L483
.L487:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r6, r3, r6
	mov	r4, r4, asl r3
	str	r5, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L629
.L483:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L487
	rsb	r1, r6, #24
	rsb	r3, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r6, r1, r6
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r5, r0, asl r3
	b	.L487
.L467:
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
.L570:
	sub	r5, r5, #1
	cmp	r4, #0
	mov	r3, r5, asl #8
	sub	r5, r3, r5, asl #2
	mov	r5, r5, lsr #8
	add	r5, r5, #1
	blt	.L630
.L498:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L499
	ldr	r3, [r10, #36]
	rsb	r8, r6, r8
	rsb	r5, r5, r3
	ldrb	r6, [r9, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r6
	rsb	r4, r6, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r6
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r8, [r10, #28]
	blt	.L631
.L500:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L501
	ldr	r3, [r10, #36]
	rsb	r6, r6, r8
	rsb	r5, r5, r3
	ldrb	r8, [r9, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r8
	rsb	r4, r8, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r6, asl r8
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r8, [r10, #28]
	blt	.L632
.L503:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L508
	ldr	r2, [r10, #36]
	rsb	r8, r6, r8
	rsb	r5, r5, r2
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r2, r5, asl r3
	rsb	r6, r3, r4
	sub	r5, r2, #1
	cmp	r6, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r3
	str	r2, [r10, #36]
	add	r5, r5, #1
	str	r6, [r10, #32]
	str	r8, [r10, #28]
	blt	.L633
.L510:
	mov	r3, r5, asl #24
	cmp	r3, r8
	bhi	.L514
	ldr	r4, [r10, #36]
	rsb	r3, r3, r8
	mov	r7, #0
	mov	r8, #6
	rsb	r5, r5, r4
	mov	r2, #1
	ldrb	r4, [r9, r5]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r6, r4, r6
	str	r3, [r10, #28]
	mov	r4, r5, asl r4
	str	r6, [r10, #32]
	mov	r5, r3
	str	r4, [r10, #36]
	b	.L515
.L519:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r6, r3, r6
	mov	r4, r4, asl r3
	str	r5, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L634
.L515:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L519
	rsb	r1, r6, #24
	rsb	r3, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r6, r1, r6
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r5, r0, asl r3
	b	.L519
.L499:
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
.L571:
	sub	r5, r5, #1
	cmp	r4, #0
	mov	r3, r5, asl #8
	sub	r5, r3, r5, asl #2
	mov	r5, r5, lsr #8
	add	r5, r5, #1
	blt	.L635
.L530:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L531
	ldr	r3, [r10, #36]
	rsb	r8, r6, r8
	rsb	r5, r5, r3
	ldrb	r6, [r9, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r6
	rsb	r4, r6, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r6
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r8, [r10, #28]
	blt	.L636
.L532:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L533
	ldr	r3, [r10, #36]
	rsb	r6, r6, r8
	rsb	r5, r5, r3
	ldrb	r8, [r9, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r8
	rsb	r4, r8, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r6, asl r8
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r8, [r10, #28]
	blt	.L637
.L535:
	mov	r6, r5, asl #24
	cmp	r6, r8
	bhi	.L540
	ldr	r2, [r10, #36]
	rsb	r8, r6, r8
	rsb	r5, r5, r2
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r2, r5, asl r3
	rsb	r6, r3, r4
	sub	r5, r2, #1
	cmp	r6, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r3
	str	r2, [r10, #36]
	add	r5, r5, #1
	str	r6, [r10, #32]
	str	r8, [r10, #28]
	blt	.L638
.L542:
	mov	r3, r5, asl #24
	cmp	r3, r8
	bhi	.L546
	ldr	r4, [r10, #36]
	rsb	r3, r3, r8
	mov	r7, #0
	mov	r8, #6
	rsb	r5, r5, r4
	mov	r2, #1
	ldrb	r4, [r9, r5]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r6, r4, r6
	str	r3, [r10, #28]
	mov	r4, r5, asl r4
	str	r6, [r10, #32]
	mov	r5, r3
	str	r4, [r10, #36]
	b	.L547
.L551:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r6, r3, r6
	mov	r4, r4, asl r3
	str	r5, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L639
.L547:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L551
	rsb	r1, r6, #24
	rsb	r3, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r6, r1, r6
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r5, r0, asl r3
	b	.L551
.L531:
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
.L572:
	ldr	r3, [fp, #-52]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r3, r3, #4
	str	r3, [fp, #-48]
	b	.L565
.L635:
	rsb	r7, r4, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r6, r4, #16
	rsb	r6, r7, r6
	add	r4, r7, r4
	mov	r1, r7
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L530
.L630:
	rsb	r7, r4, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r6, r4, #16
	rsb	r6, r7, r6
	add	r4, r7, r4
	mov	r1, r7
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L498
.L465:
	rsb	r6, r4, #24
	mov	r0, r10
	bic	r6, r6, #7
	ldr	r7, [r10, #28]
	rsb	r8, r4, #16
	add	r4, r4, r6
	mov	r1, r6
	rsb	r8, r6, r8
	bl	BsGet
	and	r8, r8, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r8
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L466
.L533:
	ldrb	r1, [r9, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r7, #0
	mov	r2, #1
	mov	r6, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r8, r3
	str	r5, [r10, #36]
	b	.L538
.L536:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L539
.L538:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L536
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L536
.L639:
	cmp	r7, #64
	mov	r3, r5
	bgt	.L640
.L553:
	add	r7, r7, #64
.L539:
	ldr	r3, [fp, #-48]
	add	r7, r9, r7
	ldrb	r1, [r7, #256]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L556
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L557
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L557:
	add	r3, r3, #1
.L559:
	ldr	r2, [fp, #-48]
	strb	r3, [r2]
	b	.L572
.L556:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L560
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L560:
	rsb	r3, r3, #255
	b	.L559
.L501:
	ldrb	r1, [r9, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r7, #0
	mov	r2, #1
	mov	r6, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r8, r3
	str	r5, [r10, #36]
	b	.L506
.L504:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L507
.L506:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L504
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L504
.L634:
	cmp	r7, #64
	mov	r3, r5
	bgt	.L641
.L521:
	add	r7, r7, #64
.L507:
	ldr	r3, [fp, #-48]
	add	r7, r9, r7
	ldrb	r1, [r7, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L524
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L525
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L525:
	add	r3, r3, #1
.L527:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #-1]
	ldr	r5, [r10, #36]
	ldr	r4, [r10, #32]
	ldr	r8, [r10, #28]
	b	.L571
.L524:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L528
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L528:
	rsb	r3, r3, #255
	b	.L527
.L469:
	ldrb	r1, [r9, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r7, #0
	mov	r2, #1
	mov	r6, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r8, r3
	str	r5, [r10, #36]
	b	.L474
.L472:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L475
.L474:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L472
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L472
.L629:
	cmp	r7, #64
	mov	r3, r5
	bgt	.L642
.L489:
	add	r7, r7, #64
.L475:
	ldr	r3, [fp, #-48]
	add	r7, r9, r7
	ldrb	r1, [r7, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L492
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L493
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L493:
	add	r3, r3, #1
.L495:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #-2]
	ldr	r5, [r10, #36]
	ldr	r4, [r10, #32]
	ldr	r8, [r10, #28]
	b	.L570
.L492:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L496
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L496:
	rsb	r3, r3, #255
	b	.L495
.L625:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r3, #6
	add	r2, r2, #32
	str	r2, [fp, #-60]
	bne	.L567
	ldr	r3, [fp, #-72]
	ldr	r2, [fp, #-76]
	add	r3, r3, #256
	str	r3, [fp, #-72]
	cmp	r3, r2
	bne	.L569
	ldr	r3, [fp, #-76]
	mov	r5, r10
	ldr	r2, [fp, #-80]
	add	r3, r3, #512
	str	r3, [fp, #-76]
	cmp	r3, r2
	bne	.L464
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L476:
	ldrb	r1, [r9, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r7, #0
	mov	r2, #1
	mov	r6, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r8, r3
	str	r5, [r10, #36]
	b	.L481
.L479:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L643
.L481:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L479
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L479
.L540:
	ldrb	r1, [r9, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r7, #0
	mov	r2, #1
	mov	r6, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r8, r3
	str	r5, [r10, #36]
	b	.L545
.L543:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L644
.L545:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L543
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L543
.L508:
	ldrb	r1, [r9, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r7, #0
	mov	r2, #1
	mov	r6, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r8, r3
	str	r5, [r10, #36]
	b	.L513
.L511:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L645
.L513:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L511
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r6, r0, asl r3
	b	.L511
.L645:
	add	r7, r7, #16
	b	.L507
.L644:
	add	r7, r7, #16
	b	.L539
.L643:
	add	r7, r7, #16
	b	.L475
.L546:
	ldrb	r4, [r9, r5]	@ zero_extendqisi2
	mov	r2, #4
	mov	r7, #0
	mov	r3, #1
	mov	r5, r5, asl r4
	mov	r8, r8, asl r4
	rsb	r6, r4, r6
	str	r5, [r10, #36]
	mov	r4, r5
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	mov	r5, r2
	b	.L550
.L548:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L646
.L550:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L548
	rsb	r1, r6, #24
	rsb	r2, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r2, r1, r2
	str	r3, [fp, #-68]
	str	r2, [fp, #-64]
	add	r6, r1, r6
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L548
.L482:
	ldrb	r4, [r9, r5]	@ zero_extendqisi2
	mov	r2, #4
	mov	r7, #0
	mov	r3, #1
	mov	r5, r5, asl r4
	mov	r8, r8, asl r4
	rsb	r6, r4, r6
	str	r5, [r10, #36]
	mov	r4, r5
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	mov	r5, r2
	b	.L486
.L484:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L647
.L486:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L484
	rsb	r1, r6, #24
	rsb	r2, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r2, r1, r2
	str	r3, [fp, #-68]
	str	r2, [fp, #-64]
	add	r6, r1, r6
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L484
.L514:
	ldrb	r4, [r9, r5]	@ zero_extendqisi2
	mov	r2, #4
	mov	r7, #0
	mov	r3, #1
	mov	r5, r5, asl r4
	mov	r8, r8, asl r4
	rsb	r6, r4, r6
	str	r5, [r10, #36]
	mov	r4, r5
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	mov	r5, r2
	b	.L518
.L653:
	.align	2
.L652:
	.word	.LANCHOR0
.L516:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L648
.L518:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L516
	rsb	r1, r6, #24
	rsb	r2, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r2, r1, r2
	str	r3, [fp, #-68]
	str	r2, [fp, #-64]
	add	r6, r1, r6
	bl	BsGet
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-68]
	and	r2, r2, #7
	orr	r0, r8, r0, asl r2
	b	.L516
.L648:
	add	r7, r7, #32
	b	.L507
.L646:
	add	r7, r7, #32
	b	.L539
.L647:
	add	r7, r7, #32
	b	.L475
.L626:
	rsb	r7, r4, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r6, r4, #16
	rsb	r6, r7, r6
	add	r4, r4, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L468
.L636:
	rsb	r7, r4, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r6, r4, #16
	rsb	r6, r7, r6
	add	r4, r4, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L532
.L631:
	rsb	r7, r4, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r6, r4, #16
	rsb	r6, r7, r6
	add	r4, r4, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L500
.L641:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r7, r7, asl #1
	add	r4, r4, #1
	sub	r7, r7, #65
	movge	r0, r5
	blt	.L649
.L522:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r10, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r7, r7, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L521
.L642:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r7, r7, asl #1
	add	r4, r4, #1
	sub	r7, r7, #65
	movge	r0, r5
	blt	.L650
.L490:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r10, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r7, r7, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L489
.L640:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r7, r7, asl #1
	add	r4, r4, #1
	sub	r7, r7, #65
	movge	r0, r5
	blt	.L651
.L554:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r10, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r7, r7, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L553
.L627:
	rsb	r7, r4, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r6, r4, #16
	rsb	r6, r7, r6
	add	r4, r4, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L471
.L632:
	rsb	r7, r4, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r6, r4, #16
	rsb	r6, r7, r6
	add	r4, r4, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L503
.L637:
	rsb	r7, r4, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r6, r4, #16
	rsb	r6, r7, r6
	add	r4, r4, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L535
.L638:
	rsb	r7, r6, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r4, r6, #16
	rsb	r4, r7, r4
	add	r6, r6, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r4, #7
	str	r6, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L542
.L628:
	rsb	r7, r6, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r4, r6, #16
	rsb	r4, r7, r4
	add	r6, r6, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r4, #7
	str	r6, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L478
.L633:
	rsb	r7, r6, #24
	mov	r0, r10
	bic	r7, r7, #7
	rsb	r4, r6, #16
	rsb	r4, r7, r4
	add	r6, r6, r7
	mov	r1, r7
	bl	BsGet
	and	r3, r4, #7
	str	r6, [r10, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r10, #28]
	mov	r8, r0
	b	.L510
.L651:
	rsb	r1, r6, #24
	str	r5, [fp, #-64]
	bic	r1, r1, #7
	rsb	r5, r6, #16
	mov	r0, r10
	rsb	r5, r1, r5
	add	r6, r1, r6
	bl	BsGet
	ldr	r3, [fp, #-64]
	and	r5, r5, #7
	orr	r0, r3, r0, asl r5
	b	.L554
.L649:
	rsb	r1, r6, #24
	str	r5, [fp, #-64]
	bic	r1, r1, #7
	rsb	r5, r6, #16
	mov	r0, r10
	rsb	r5, r1, r5
	add	r6, r1, r6
	bl	BsGet
	ldr	r3, [fp, #-64]
	and	r5, r5, #7
	orr	r0, r3, r0, asl r5
	b	.L522
.L650:
	rsb	r1, r6, #24
	str	r5, [fp, #-64]
	bic	r1, r1, #7
	rsb	r5, r6, #16
	mov	r0, r10
	rsb	r5, r1, r5
	add	r6, r1, r6
	bl	BsGet
	ldr	r3, [fp, #-64]
	and	r5, r5, #7
	orr	r0, r3, r0, asl r5
	b	.L490
.L463:
	ldr	r2, .L652
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L461:
	rsb	r8, r5, #24
	ldr	r7, [r1, #28]
	bic	r8, r8, #7
	mov	r0, r1
	rsb	r9, r5, #16
	add	r5, r5, r8
	mov	r1, r8
	rsb	r9, r8, r9
	bl	BsGet
	and	r3, r9, #7
	str	r5, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r3, r0
	b	.L462
	UNWIND(.fnend)
	.size	Vp9_ReadCoefProbsCommon, .-Vp9_ReadCoefProbsCommon
	.align	2
	.global	Vp9_ReadCoefProbs
	.type	Vp9_ReadCoefProbs, %function
Vp9_ReadCoefProbs:
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
	mov	r4, r1
	mov	r1, r2
	mov	r5, r2
	mov	r6, r0
	bl	Vp9_ReadCoefProbsCommon
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	add	r0, r6, #1024
	bl	Vp9_ReadCoefProbsCommon
	cmp	r4, #1
	bls	.L656
	mov	r1, r5
	add	r0, r6, #2048
	bl	Vp9_ReadCoefProbsCommon
.L656:
	cmp	r4, #2
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	add	r0, r6, #3072
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	Vp9_ReadCoefProbsCommon
	UNWIND(.fnend)
	.size	Vp9_ReadCoefProbs, .-Vp9_ReadCoefProbs
	.align	2
	.global	Vp9_ReadInterModeProbs
	.type	Vp9_ReadInterModeProbs, %function
Vp9_ReadInterModeProbs:
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
	ldr	r6, .L841
	add	r3, r0, #4416
	mov	r5, r1
	mov	r2, r3
	add	r3, r3, #25
	str	r3, [fp, #-48]
	add	r3, r2, #24
	str	r3, [fp, #-52]
	add	r3, r2, #46
	str	r3, [fp, #-56]
.L757:
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L660
	ldr	r10, [r5, #28]
.L661:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L662
	ldr	r3, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r3
	ldrb	r8, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r8
	rsb	r4, r8, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r8
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L815
.L663:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L664
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r7, r7, r3
	ldrb	r10, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r10
	rsb	r4, r10, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L816
.L666:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L671
	ldr	r2, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r2
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r2, r7, asl r3
	rsb	r8, r3, r4
	sub	r7, r2, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r3
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r10, [r5, #28]
	blt	.L817
.L673:
	mov	r3, r7, asl #24
	cmp	r3, r10
	bhi	.L677
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r4
	mov	r2, #1
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	b	.L678
.L682:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L818
.L678:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L682
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L682
.L662:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L758:
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L819
.L693:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L694
	ldr	r3, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r3
	ldrb	r8, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r8
	rsb	r4, r8, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r8
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L820
.L695:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L696
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r7, r7, r3
	ldrb	r10, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r10
	rsb	r4, r10, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L821
.L698:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L703
	ldr	r2, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r2
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r2, r7, asl r3
	rsb	r8, r3, r4
	sub	r7, r2, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r3
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r10, [r5, #28]
	blt	.L822
.L705:
	mov	r3, r7, asl #24
	cmp	r3, r10
	bhi	.L709
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r4
	mov	r2, #1
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	b	.L710
.L714:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L823
.L710:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L714
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L714
.L694:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L759:
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L824
.L725:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L726
	ldr	r3, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r3
	ldrb	r8, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r8
	rsb	r4, r8, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r8
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L825
.L727:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L728
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r7, r7, r3
	ldrb	r10, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r10
	rsb	r4, r10, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L826
.L730:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L735
	ldr	r2, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r2
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r2, r7, asl r3
	rsb	r8, r3, r4
	sub	r7, r2, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r3
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r10, [r5, #28]
	blt	.L827
.L737:
	mov	r3, r7, asl #24
	cmp	r3, r10
	bhi	.L741
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r4
	mov	r2, #1
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	b	.L742
.L746:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L828
.L742:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L746
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L746
.L726:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L760:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r2, #3
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r3, r3, #3
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L757
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L824:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r9, r4
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L725
.L819:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r9, r4
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L693
.L660:
	rsb	r8, r4, #24
	mov	r0, r5
	bic	r8, r8, #7
	ldr	r9, [r5, #28]
	rsb	r10, r4, #16
	add	r4, r4, r8
	mov	r1, r8
	rsb	r10, r8, r10
	bl	BsGet
	and	r10, r10, #7
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L661
.L664:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L669
.L667:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L670
.L669:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L667
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L667
.L818:
	cmp	r9, #64
	mov	r3, r7
	bgt	.L829
.L684:
	add	r9, r9, #64
.L670:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L687
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L688
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L688:
	add	r3, r3, #1
.L690:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #-2]
	ldr	r10, [r5, #28]
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L758
.L687:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L691
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L691:
	rsb	r3, r3, #255
	b	.L690
.L728:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L733
.L731:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L734
.L733:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L731
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L731
.L828:
	cmp	r9, #64
	mov	r3, r7
	bgt	.L830
.L748:
	add	r9, r9, #64
.L734:
	ldr	r3, [fp, #-52]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L751
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L752
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L752:
	add	r3, r3, #1
.L754:
	ldr	r2, [fp, #-52]
	strb	r3, [r2, #1]
	b	.L760
.L751:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L755
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L755:
	rsb	r3, r3, #255
	b	.L754
.L696:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L701
.L699:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L702
.L701:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L699
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L699
.L823:
	cmp	r9, #64
	mov	r3, r7
	bgt	.L831
.L716:
	add	r9, r9, #64
.L702:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L719
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L720
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L720:
	add	r3, r3, #1
.L722:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #-1]
	ldr	r10, [r5, #28]
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L759
.L719:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L723
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L723:
	rsb	r3, r3, #255
	b	.L722
.L677:
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	mov	r7, r7, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r7, [r5, #36]
	mov	r4, r7
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	mov	r7, r2
	b	.L681
.L679:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L832
.L681:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L679
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L679
.L741:
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	mov	r7, r7, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r7, [r5, #36]
	mov	r4, r7
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	mov	r7, r2
	b	.L745
.L743:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L833
.L745:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L743
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L743
.L709:
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	mov	r7, r7, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r7, [r5, #36]
	mov	r4, r7
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	mov	r7, r2
	b	.L713
.L711:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L834
.L713:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L711
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L711
.L735:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L740
.L738:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L835
.L740:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L738
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L738
.L703:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L708
.L706:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L836
.L708:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L706
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L706
.L671:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L676
.L674:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L837
.L676:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L674
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L674
.L837:
	add	r9, r9, #16
	b	.L670
.L836:
	add	r9, r9, #16
	b	.L702
.L835:
	add	r9, r9, #16
	b	.L734
.L834:
	add	r9, r9, #32
	b	.L702
.L833:
	add	r9, r9, #32
	b	.L734
.L832:
	add	r9, r9, #32
	b	.L670
.L842:
	.align	2
.L841:
	.word	.LANCHOR0
.L820:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L695
.L825:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L727
.L815:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L663
.L830:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl #1
	add	r4, r4, #1
	sub	r9, r9, #65
	movge	r0, r7
	blt	.L838
.L749:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r9, r9, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	b	.L748
.L831:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl #1
	add	r4, r4, #1
	sub	r9, r9, #65
	movge	r0, r7
	blt	.L839
.L717:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r9, r9, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	b	.L716
.L829:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl #1
	add	r4, r4, #1
	sub	r9, r9, #65
	movge	r0, r7
	blt	.L840
.L685:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r9, r9, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	b	.L684
.L821:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L698
.L816:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L666
.L826:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L730
.L827:
	rsb	r9, r8, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L737
.L822:
	rsb	r9, r8, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L705
.L817:
	rsb	r9, r8, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L673
.L838:
	rsb	r1, r8, #24
	str	r7, [fp, #-60]
	bic	r1, r1, #7
	rsb	r7, r8, #16
	mov	r0, r5
	rsb	r7, r1, r7
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	and	r7, r7, #7
	orr	r0, r3, r0, asl r7
	b	.L749
.L840:
	rsb	r1, r8, #24
	str	r7, [fp, #-60]
	bic	r1, r1, #7
	rsb	r7, r8, #16
	mov	r0, r5
	rsb	r7, r1, r7
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	and	r7, r7, #7
	orr	r0, r3, r0, asl r7
	b	.L685
.L839:
	rsb	r1, r8, #24
	str	r7, [fp, #-60]
	bic	r1, r1, #7
	rsb	r7, r8, #16
	mov	r0, r5
	rsb	r7, r1, r7
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	and	r7, r7, #7
	orr	r0, r3, r0, asl r7
	b	.L717
	UNWIND(.fnend)
	.size	Vp9_ReadInterModeProbs, .-Vp9_ReadInterModeProbs
	.align	2
	.global	Vp9_ReadSwitchableInterpProbs
	.type	Vp9_ReadSwitchableInterpProbs, %function
Vp9_ReadSwitchableInterpProbs:
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
	ldr	r6, .L964
	add	r3, r0, #4416
	mov	r5, r1
	mov	r2, r3
	add	r3, r3, #45
	str	r3, [fp, #-48]
	add	r3, r2, #44
	str	r3, [fp, #-52]
	add	r3, r2, #53
	str	r3, [fp, #-56]
.L909:
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L844
	ldr	r10, [r5, #28]
.L845:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L846
	ldr	r3, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r3
	ldrb	r8, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r8
	rsb	r4, r8, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r8
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L949
.L847:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L848
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r7, r7, r3
	ldrb	r10, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r10
	rsb	r4, r10, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L950
.L850:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L855
	ldr	r2, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r2
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r2, r7, asl r3
	rsb	r8, r3, r4
	sub	r7, r2, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r3
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r10, [r5, #28]
	blt	.L951
.L857:
	mov	r3, r7, asl #24
	cmp	r3, r10
	bhi	.L861
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r4
	mov	r2, #1
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	b	.L862
.L866:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L952
.L862:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L866
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L866
.L846:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L910:
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L953
.L877:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L878
	ldr	r3, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r3
	ldrb	r8, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r8
	rsb	r4, r8, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r8
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L954
.L879:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L880
	ldr	r3, [r5, #36]
	rsb	r8, r8, r10
	rsb	r7, r7, r3
	ldrb	r10, [r6, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r10
	rsb	r4, r10, r4
	sub	r7, r3, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r5, #36]
	add	r7, r7, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L955
.L882:
	mov	r8, r7, asl #24
	cmp	r8, r10
	bhi	.L887
	ldr	r2, [r5, #36]
	rsb	r10, r8, r10
	rsb	r7, r7, r2
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r2, r7, asl r3
	rsb	r8, r3, r4
	sub	r7, r2, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r10, r10, asl r3
	str	r2, [r5, #36]
	add	r7, r7, #1
	str	r8, [r5, #32]
	str	r10, [r5, #28]
	blt	.L956
.L889:
	mov	r3, r7, asl #24
	cmp	r3, r10
	bhi	.L893
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r4
	mov	r2, #1
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r5, #28]
	mov	r4, r7, asl r4
	str	r8, [r5, #32]
	mov	r7, r3
	str	r4, [r5, #36]
	b	.L894
.L898:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r6, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L957
.L894:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L898
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L898
.L878:
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L911:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r2, #2
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-56]
	add	r3, r3, #2
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L909
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L953:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r9, r4
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L877
.L844:
	rsb	r8, r4, #24
	mov	r0, r5
	bic	r8, r8, #7
	ldr	r9, [r5, #28]
	rsb	r10, r4, #16
	add	r4, r4, r8
	mov	r1, r8
	rsb	r10, r8, r10
	bl	BsGet
	and	r10, r10, #7
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r10
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L845
.L855:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L860
.L858:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L958
.L860:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L858
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L858
.L887:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L892
.L890:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L959
.L892:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L890
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L890
.L848:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L853
.L851:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L854
.L853:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L851
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L851
.L952:
	cmp	r9, #64
	mov	r3, r7
	ble	.L868
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl #1
	add	r4, r4, #1
	sub	r9, r9, #65
	movge	r0, r7
	blt	.L960
.L869:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r9, r9, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
.L868:
	add	r9, r9, #64
.L854:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L871
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L872
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L872:
	add	r3, r3, #1
.L874:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #-1]
	ldr	r10, [r5, #28]
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L910
.L871:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L875
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L875:
	rsb	r3, r3, #255
	b	.L874
.L880:
	ldrb	r1, [r6, r7]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r7, [r5, #36]
	b	.L885
.L883:
	mov	r3, r7, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r7, r7, ip
	cmn	r10, #1
	ldrb	r3, [r6, r7]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L886
.L885:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L883
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r3, r1, r3
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L883
.L957:
	cmp	r9, #64
	mov	r3, r7
	ble	.L900
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl #1
	add	r4, r4, #1
	sub	r9, r9, #65
	movge	r0, r7
	blt	.L961
.L901:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r9, r9, r1
	rsbls	r4, r4, r3
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r3, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
.L900:
	add	r9, r9, #64
.L886:
	ldr	r3, [fp, #-52]
	add	r9, r6, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L903
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L904
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L904:
	add	r3, r3, #1
.L906:
	ldr	r2, [fp, #-52]
	strb	r3, [r2, #1]
	b	.L911
.L903:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L907
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L907:
	rsb	r3, r3, #255
	b	.L906
.L959:
	add	r9, r9, #16
	b	.L886
.L958:
	add	r9, r9, #16
	b	.L854
.L861:
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	mov	r7, r7, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r7, [r5, #36]
	mov	r4, r7
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	mov	r7, r2
	b	.L865
.L863:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L962
.L865:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L863
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L863
.L893:
	ldrb	r4, [r6, r7]	@ zero_extendqisi2
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	mov	r7, r7, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r7, [r5, #36]
	mov	r4, r7
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	mov	r7, r2
	b	.L897
.L895:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r7
	cmp	r2, r0
	sub	r7, r7, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r8, [r5, #32]
	str	r4, [r5, #36]
	beq	.L963
.L897:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L895
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r5
	rsb	r2, r1, r2
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-64]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L895
.L962:
	add	r9, r9, #32
	b	.L854
.L963:
	add	r9, r9, #32
	b	.L886
.L954:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L879
.L949:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L847
.L950:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L850
.L955:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L882
.L951:
	rsb	r9, r8, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L857
.L956:
	rsb	r9, r8, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r5, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L889
.L961:
	rsb	r1, r8, #24
	str	r7, [fp, #-60]
	bic	r1, r1, #7
	rsb	r7, r8, #16
	mov	r0, r5
	rsb	r7, r1, r7
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	and	r7, r7, #7
	orr	r0, r3, r0, asl r7
	b	.L901
.L960:
	rsb	r1, r8, #24
	str	r7, [fp, #-60]
	bic	r1, r1, #7
	rsb	r7, r8, #16
	mov	r0, r5
	rsb	r7, r1, r7
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-60]
	and	r7, r7, #7
	orr	r0, r3, r0, asl r7
	b	.L869
.L965:
	.align	2
.L964:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ReadSwitchableInterpProbs, .-Vp9_ReadSwitchableInterpProbs
	.align	2
	.global	Vp9_ReadCompPred
	.type	Vp9_ReadCompPred, %function
Vp9_ReadCompPred:
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
	cmp	r2, #0
	str	r0, [fp, #-60]
	mov	r6, r1
	str	r3, [fp, #-64]
	bne	.L1184
	add	r4, r1, #28
	str	r2, [fp, #-56]
	ldr	r2, .L1217
	ldmia	r4, {r4, r5, r8}
.L1007:
	mov	r10, r4
	ldr	r3, [fp, #-60]
	mov	r9, r8
	mov	r7, r2
	add	r1, r3, #4416
	mov	r3, r1
	add	r1, r1, #14
	add	r3, r3, #24
	str	r1, [fp, #-48]
	str	r3, [fp, #-52]
.L1072:
	sub	r9, r9, #1
	cmp	r5, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L1185
.L1009:
	mov	r8, r9, asl #24
	cmp	r8, r10
	bhi	.L1010
	ldr	r3, [r6, #36]
	rsb	r8, r8, r10
	rsb	r9, r9, r3
	ldrb	r0, [r7, r9]	@ zero_extendqisi2
	mov	r9, r9, asl r0
	rsb	r4, r0, r5
	sub	r10, r9, #1
	cmp	r4, #0
	ubfx	r10, r10, #1, #24
	mov	r8, r8, asl r0
	str	r9, [r6, #36]
	add	r10, r10, #1
	str	r4, [r6, #32]
	str	r8, [r6, #28]
	blt	.L1186
.L1011:
	mov	r2, r10, asl #24
	cmp	r2, r8
	bhi	.L1012
	ldr	r3, [r6, #36]
	rsb	r8, r2, r8
	rsb	r3, r10, r3
	ldrb	r10, [r7, r3]	@ zero_extendqisi2
	mov	r3, r3, asl r10
	rsb	r4, r10, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r10, [r6, #28]
	blt	.L1187
.L1014:
	mov	r8, r5, asl #24
	cmp	r8, r10
	bhi	.L1019
	ldr	r3, [r6, #36]
	rsb	r10, r8, r10
	rsb	r5, r5, r3
	ldrb	r0, [r7, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r0
	rsb	r8, r0, r4
	sub	r5, r3, #1
	cmp	r8, #0
	ubfx	r5, r5, #1, #24
	mov	r10, r10, asl r0
	str	r3, [r6, #36]
	add	r5, r5, #1
	str	r8, [r6, #32]
	str	r10, [r6, #28]
	blt	.L1188
.L1021:
	mov	r3, r5, asl #24
	cmp	r3, r10
	bhi	.L1025
	ldr	r4, [r6, #36]
	rsb	r10, r3, r10
	mov	r3, #6
	mov	r9, #0
	rsb	r5, r5, r4
	mov	r2, #1
	ldrb	r4, [r7, r5]	@ zero_extendqisi2
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r10, [r6, #28]
	mov	r4, r5, asl r4
	str	r8, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L1026
.L1030:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r3, [r7, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1189
.L1026:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L1030
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	b	.L1030
.L1010:
	ldrb	r3, [r7, r9]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r5
	mov	r9, r9, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r9, [r6, #36]
.L1107:
	sub	r9, r9, #1
	cmp	r4, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L1190
.L1041:
	mov	r8, r9, asl #24
	cmp	r8, r10
	bhi	.L1042
	ldr	r3, [r6, #36]
	rsb	r10, r8, r10
	rsb	r9, r9, r3
	ldrb	r8, [r7, r9]	@ zero_extendqisi2
	mov	r9, r9, asl r8
	rsb	r4, r8, r4
	sub	r5, r9, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r10, r10, asl r8
	str	r9, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r10, [r6, #28]
	blt	.L1191
.L1043:
	mov	r8, r5, asl #24
	cmp	r8, r10
	bhi	.L1044
	ldr	r3, [r6, #36]
	rsb	r8, r8, r10
	rsb	r5, r5, r3
	ldrb	r10, [r7, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r10
	rsb	r4, r10, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r10, r8, asl r10
	str	r3, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r10, [r6, #28]
	blt	.L1192
.L1046:
	mov	r8, r5, asl #24
	cmp	r8, r10
	bhi	.L1051
	ldr	r2, [r6, #36]
	rsb	r10, r8, r10
	rsb	r5, r5, r2
	ldrb	r3, [r7, r5]	@ zero_extendqisi2
	mov	r2, r5, asl r3
	rsb	r8, r3, r4
	sub	r5, r2, #1
	cmp	r8, #0
	ubfx	r5, r5, #1, #24
	mov	r10, r10, asl r3
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r8, [r6, #32]
	str	r10, [r6, #28]
	blt	.L1193
.L1053:
	mov	r3, r5, asl #24
	cmp	r3, r10
	bhi	.L1057
	ldr	r4, [r6, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r5, r5, r4
	mov	r2, #1
	ldrb	r4, [r7, r5]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r6, #28]
	mov	r4, r5, asl r4
	str	r8, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L1058
.L1062:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r7, r4]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r5, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1194
.L1058:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L1062
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r5, r0, asl r3
	b	.L1062
.L1042:
	ldrb	r3, [r7, r9]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r9, r9, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r9, [r6, #36]
.L1108:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #2
	str	r3, [fp, #-48]
	cmp	r3, r2
	ldrne	r10, [r6, #28]
	ldrne	r9, [r6, #36]
	ldrne	r5, [r6, #32]
	bne	.L1072
.L1071:
	ldr	r3, [fp, #-56]
	mov	r2, r7
	cmp	r3, #0
	bne	.L1195
.L1103:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-56]
	str	r2, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1195:
	add	r4, r6, #28
	ldmia	r4, {r4, r5, r8}
.L1008:
	mov	r10, r2
	ldr	r3, [fp, #-60]
	add	r7, r3, #4416
	mov	r3, r7
	add	r7, r7, #8
	add	r3, r3, #13
	str	r7, [fp, #-48]
	str	r3, [fp, #-52]
.L1104:
	sub	r8, r8, #1
	cmp	r5, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L1196
.L1073:
	mov	r7, r8, asl #24
	cmp	r7, r4
	bhi	.L1074
	ldr	r3, [r6, #36]
	rsb	r7, r7, r4
	rsb	r8, r8, r3
	ldrb	r0, [r10, r8]	@ zero_extendqisi2
	mov	r8, r8, asl r0
	rsb	r5, r0, r5
	sub	r9, r8, #1
	cmp	r5, #0
	ubfx	r9, r9, #1, #24
	mov	r7, r7, asl r0
	str	r8, [r6, #36]
	add	r9, r9, #1
	str	r5, [r6, #32]
	str	r7, [r6, #28]
	blt	.L1197
.L1075:
	mov	r2, r9, asl #24
	cmp	r2, r7
	bhi	.L1076
	ldr	r3, [r6, #36]
	rsb	r7, r2, r7
	rsb	r9, r9, r3
	ldrb	r0, [r10, r9]	@ zero_extendqisi2
	mov	r3, r9, asl r0
	rsb	r4, r0, r5
	sub	r9, r3, #1
	cmp	r4, #0
	ubfx	r9, r9, #1, #24
	mov	r7, r7, asl r0
	str	r3, [r6, #36]
	add	r9, r9, #1
	str	r4, [r6, #32]
	str	r7, [r6, #28]
	blt	.L1198
.L1078:
	mov	r3, r9, asl #24
	cmp	r3, r7
	bhi	.L1083
	ldr	r5, [r6, #36]
	rsb	r7, r3, r7
	rsb	r9, r9, r5
	ldrb	r3, [r10, r9]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	sub	r5, r9, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r7, asl r3
	str	r9, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r7, [r6, #28]
	blt	.L1199
.L1085:
	mov	r3, r5, asl #24
	cmp	r3, r7
	bhi	.L1089
	ldr	r1, [r6, #36]
	rsb	r7, r3, r7
	mov	r8, #0
	mov	r9, #6
	rsb	r5, r5, r1
	mov	r2, #1
	ldrb	r1, [r10, r5]	@ zero_extendqisi2
	mov	r3, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r3, [r6, #28]
	str	r4, [r6, #32]
	mov	r7, r3
	str	r5, [r6, #36]
	b	.L1090
.L1094:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r9, #1
	ldrb	r3, [r10, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1200
.L1090:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1094
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L1094
.L1051:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r3
	str	r5, [r6, #36]
	b	.L1056
.L1054:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r5, r5, ip
	cmn	r10, #1
	ldrb	r3, [r7, r5]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1201
.L1056:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L1054
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L1054
.L1019:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r3
	str	r5, [r6, #36]
	b	.L1024
.L1022:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r5, r5, ip
	cmn	r10, #1
	ldrb	r3, [r7, r5]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1202
.L1024:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L1022
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L1022
.L1074:
	ldrb	r3, [r10, r8]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	mov	r8, r8, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r8, [r6, #36]
.L1109:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	beq	.L1103
	add	r4, r6, #28
	ldmia	r4, {r4, r5, r8}
	b	.L1104
.L1190:
	rsb	r8, r4, #24
	mov	r0, r6
	bic	r8, r8, #7
	rsb	r5, r4, #16
	rsb	r5, r8, r5
	add	r4, r8, r4
	mov	r1, r8
	and	r5, r5, #7
	bl	BsGet
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r5
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L1041
.L1185:
	rsb	r4, r5, #24
	mov	r0, r6
	bic	r4, r4, #7
	rsb	r8, r5, #16
	rsb	r8, r4, r8
	mov	r1, r4
	add	r4, r4, r5
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r6, #32]
	mov	r5, r4
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L1009
.L1044:
	ldrb	r1, [r7, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r3
	str	r5, [r6, #36]
	b	.L1049
.L1047:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r5, r5, ip
	cmn	r10, #1
	ldrb	r3, [r7, r5]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1050
.L1049:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L1047
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L1047
.L1194:
	cmp	r9, #64
	ble	.L1064
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L1064:
	add	r9, r9, #64
.L1050:
	ldr	r3, [fp, #-48]
	add	r9, r7, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1065
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1066
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1066:
	add	r3, r3, #1
.L1068:
	ldr	r2, [fp, #-48]
	strb	r3, [r2]
	b	.L1108
.L1065:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1069
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1069:
	rsb	r3, r3, #255
	b	.L1068
.L1012:
	ldrb	r5, [r7, r10]	@ zero_extendqisi2
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	mov	r10, r10, asl r5
	mov	r8, r8, asl r5
	rsb	r4, r5, r4
	str	r10, [r6, #36]
	mov	r5, r10
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r3
	b	.L1017
.L1015:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r5, r5, ip
	cmn	r10, #1
	ldrb	r3, [r7, r5]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1018
.L1017:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L1015
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L1015
.L1189:
	cmp	r9, #64
	ble	.L1032
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl #1
	add	r4, r4, #1
	sub	r9, r9, #65
	movge	r0, r10
	blt	.L1203
.L1033:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r9, r9, r2
	rsbls	r4, r4, r1
	ldrb	r3, [r7, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
.L1032:
	add	r9, r9, #64
.L1018:
	ldr	r3, [fp, #-48]
	add	r9, r7, r9
	ldrb	r1, [r9, #256]	@ zero_extendqisi2
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1035
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1036
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1036:
	add	r3, r3, #1
.L1038:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #-1]
	ldr	r10, [r6, #28]
	ldr	r9, [r6, #36]
	ldr	r4, [r6, #32]
	b	.L1107
.L1035:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1039
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1039:
	rsb	r3, r3, #255
	b	.L1038
.L1196:
	rsb	r9, r5, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r7, r5, #16
	rsb	r7, r9, r7
	add	r5, r9, r5
	mov	r1, r9
	and	r7, r7, #7
	bl	BsGet
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r7
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1073
.L1076:
	ldrb	r4, [r10, r9]	@ zero_extendqisi2
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	mov	r9, r9, asl r4
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r9, [r6, #36]
	mov	r4, r9
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	mov	r9, r3
	b	.L1081
.L1079:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	ldrb	r3, [r10, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1082
.L1081:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1079
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-60]
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L1079
.L1200:
	cmp	r8, #64
	ble	.L1096
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r8, lsl #1
	sub	r8, r0, #65
.L1096:
	add	r8, r8, #64
.L1082:
	ldr	r3, [fp, #-48]
	add	r8, r10, r8
	ldrb	r1, [r8, #256]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L1097
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1098
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1098:
	add	r3, r3, #1
.L1100:
	ldr	r2, [fp, #-48]
	strb	r3, [r2]
	b	.L1109
.L1097:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1101
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1101:
	rsb	r3, r3, #255
	b	.L1100
.L1184:
	ldr	r7, [r1, #36]
	ldr	r5, [r1, #32]
	sub	r7, r7, #1
	cmp	r5, #0
	ubfx	r7, r7, #1, #24
	add	r7, r7, #1
	blt	.L968
	ldr	r0, [r1, #28]
.L969:
	mov	r4, r7, asl #24
	cmp	r4, r0
	bhi	.L970
	ldr	r3, [r6, #36]
	rsb	r0, r4, r0
	ldr	r2, .L1217
	rsb	r7, r7, r3
	ldrb	r1, [r2, r7]	@ zero_extendqisi2
	mov	r3, r7, asl r1
	rsb	r5, r1, r5
	mov	r4, r0, asl r1
	cmp	r5, #0
	sub	r7, r3, #1
	str	r3, [r6, #36]
	ubfx	r7, r7, #1, #24
	str	r5, [r6, #32]
	add	r7, r7, #1
	str	r4, [r6, #28]
	movge	r0, r4
	blt	.L1204
.L971:
	mov	r3, r7, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r3, #1
	movhi	r3, #0
	add	r3, r3, #1
	rsbls	r7, r7, r1
	cmp	r3, #2
	str	r3, [fp, #-56]
	ldrb	r8, [r2, r7]	@ zero_extendqisi2
	mov	r4, r0, asl r8
	rsb	r5, r8, r5
	str	r4, [r6, #28]
	mov	r8, r7, asl r8
	str	r5, [r6, #32]
	str	r8, [r6, #36]
	bne	.L973
	ldr	r3, [fp, #-60]
	mov	r9, r2
	add	r1, r3, #4416
	mov	r3, r1
	add	r1, r1, #3
	add	r3, r3, #8
	str	r1, [fp, #-48]
	str	r3, [fp, #-52]
.L1006:
	sub	r8, r8, #1
	cmp	r5, #0
	mov	r3, r8, asl #8
	sub	r8, r3, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L1205
.L974:
	mov	r7, r8, asl #24
	cmp	r7, r4
	bhi	.L975
	ldr	r3, [r6, #36]
	rsb	r7, r7, r4
	rsb	r8, r8, r3
	ldrb	r0, [r9, r8]	@ zero_extendqisi2
	mov	r8, r8, asl r0
	rsb	r5, r0, r5
	sub	r10, r8, #1
	cmp	r5, #0
	ubfx	r10, r10, #1, #24
	mov	r7, r7, asl r0
	str	r8, [r6, #36]
	add	r10, r10, #1
	str	r5, [r6, #32]
	str	r7, [r6, #28]
	blt	.L1206
.L976:
	mov	r2, r10, asl #24
	cmp	r2, r7
	bhi	.L977
	ldr	r3, [r6, #36]
	rsb	r7, r2, r7
	rsb	r10, r10, r3
	ldrb	r0, [r9, r10]	@ zero_extendqisi2
	mov	r3, r10, asl r0
	rsb	r4, r0, r5
	sub	r10, r3, #1
	cmp	r4, #0
	ubfx	r10, r10, #1, #24
	mov	r7, r7, asl r0
	str	r3, [r6, #36]
	add	r10, r10, #1
	str	r4, [r6, #32]
	str	r7, [r6, #28]
	blt	.L1207
.L979:
	mov	r8, r10, asl #24
	cmp	r8, r7
	bhi	.L984
	ldr	r3, [r6, #36]
	rsb	r7, r8, r7
	rsb	r3, r10, r3
	ldrb	r8, [r9, r3]	@ zero_extendqisi2
	mov	r3, r3, asl r8
	rsb	r4, r8, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r7, asl r8
	str	r3, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r8, [r6, #28]
	blt	.L1208
.L986:
	mov	r10, r5, asl #24
	cmp	r10, r8
	bhi	.L990
	ldr	r1, [r6, #36]
	rsb	r10, r10, r8
	mov	r3, #6
	mov	r8, #0
	rsb	r5, r5, r1
	mov	r2, #1
	mov	r7, r3
	ldrb	r1, [r9, r5]	@ zero_extendqisi2
	mov	r10, r10, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	b	.L991
.L1218:
	.align	2
.L1217:
	.word	.LANCHOR0
.L995:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r7, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1209
.L991:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r10
	add	r5, r5, #1
	bge	.L995
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	b	.L995
.L1201:
	add	r9, r9, #16
	b	.L1050
.L1202:
	add	r9, r9, #16
	b	.L1018
.L1083:
	ldrb	r5, [r10, r9]	@ zero_extendqisi2
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	mov	r9, r9, asl r5
	mov	r7, r7, asl r5
	rsb	r4, r5, r4
	str	r9, [r6, #36]
	mov	r5, r9
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	mov	r9, r3
	b	.L1088
.L1086:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r9, #1
	ldrb	r3, [r10, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1210
.L1088:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1086
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L1086
.L970:
	ldr	r2, .L1217
	mov	r3, #0
	str	r3, [fp, #-56]
	ldrb	r8, [r2, r7]	@ zero_extendqisi2
	mov	r4, r0, asl r8
	rsb	r5, r8, r5
	str	r4, [r6, #28]
	mov	r8, r7, asl r8
	str	r5, [r6, #32]
	str	r8, [r6, #36]
	b	.L1007
.L975:
	ldrb	r3, [r9, r8]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	mov	r8, r8, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r8, [r6, #36]
.L1106:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L1006
	mov	r2, r9
	b	.L1007
.L1210:
	add	r8, r8, #16
	b	.L1082
.L1205:
	rsb	r10, r5, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r7, r5, #16
	rsb	r7, r10, r7
	add	r5, r10, r5
	mov	r1, r10
	and	r7, r7, #7
	bl	BsGet
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r7
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L974
.L977:
	ldrb	r4, [r9, r10]	@ zero_extendqisi2
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	mov	r10, r10, asl r4
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r10, [r6, #36]
	mov	r4, r10
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	mov	r10, r3
	b	.L982
.L980:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	ldrb	r3, [r9, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L983
.L982:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L980
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r5, r1, r5
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L980
.L1209:
	cmp	r8, #64
	ble	.L997
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl #1
	add	r5, r5, #1
	sub	r7, r8, #65
	movge	r0, r10
	blt	.L1211
.L998:
	mov	r3, r5, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r8, #1
	movhi	r8, #0
	add	r8, r7, r8
	rsbls	r5, r5, r2
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
.L997:
	add	r8, r8, #64
.L983:
	ldr	r3, [fp, #-48]
	add	r8, r9, r8
	ldrb	r1, [r8, #256]	@ zero_extendqisi2
	ldrb	r3, [r3]	@ zero_extendqisi2
	sub	r0, r3, #1
	mov	r2, r0, asl #1
	cmp	r2, #255
	bgt	.L1000
	add	r3, r1, #1
	cmp	r3, r2
	bgt	.L1001
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r0, r3, asr #1
	addeq	r3, r0, r3, asr #1
.L1001:
	add	r3, r3, #1
.L1003:
	ldr	r2, [fp, #-48]
	add	r4, r6, #28
	strb	r3, [r2]
	ldmia	r4, {r4, r5, r8}
	b	.L1106
.L1000:
	rsb	r2, r3, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1004
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1004:
	rsb	r3, r3, #255
	b	.L1003
.L1025:
	ldrb	r4, [r7, r5]	@ zero_extendqisi2
	mov	r3, #4
	mov	r9, #0
	mov	r2, #1
	mov	r5, r5, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r5, [r6, #36]
	mov	r4, r5
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	mov	r5, r3
	b	.L1029
.L1027:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r3, [r7, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1212
.L1029:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L1027
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r8, r1, r8
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r10, r0, asl r3
	b	.L1027
.L1057:
	ldrb	r4, [r7, r5]	@ zero_extendqisi2
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	mov	r5, r5, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r5, [r6, #36]
	mov	r4, r5
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	mov	r5, r2
	b	.L1061
.L1059:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r2, [r7, r4]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1213
.L1061:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L1059
	rsb	r1, r8, #24
	rsb	r2, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r2, r1, r2
	str	r3, [fp, #-72]
	str	r2, [fp, #-68]
	add	r8, r1, r8
	bl	BsGet
	ldr	r2, [fp, #-68]
	ldr	r3, [fp, #-72]
	and	r2, r2, #7
	orr	r0, r10, r0, asl r2
	b	.L1059
.L1213:
	add	r9, r9, #32
	b	.L1050
.L1212:
	add	r9, r9, #32
	b	.L1018
.L1186:
	rsb	r9, r4, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r5, r4, #16
	rsb	r5, r9, r5
	add	r4, r4, r9
	mov	r1, r9
	and	r5, r5, #7
	bl	BsGet
	str	r4, [r6, #32]
	orr	r0, r8, r0, asl r5
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L1011
.L1191:
	rsb	r9, r4, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L1043
.L1089:
	ldrb	r1, [r10, r5]	@ zero_extendqisi2
	mov	r8, #0
	mov	r9, #4
	mov	r2, #1
	mov	r7, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	b	.L1093
.L1091:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r9, #1
	ldrb	r3, [r10, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1214
.L1093:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1091
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-68]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L1091
.L1214:
	add	r8, r8, #32
	b	.L1082
.L1197:
	rsb	r8, r5, #24
	mov	r0, r6
	bic	r8, r8, #7
	rsb	r4, r5, #16
	rsb	r4, r8, r4
	add	r5, r5, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r4, #7
	str	r5, [r6, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r6, #28]
	mov	r7, r0
	b	.L1075
.L984:
	ldrb	r5, [r9, r10]	@ zero_extendqisi2
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	mov	r7, r7, asl r5
	rsb	r4, r5, r4
	str	r7, [r6, #28]
	mov	r5, r10, asl r5
	str	r4, [r6, #32]
	mov	r10, r3
	str	r5, [r6, #36]
	b	.L989
.L987:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r10, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1215
.L989:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L987
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L987
.L1215:
	add	r8, r8, #16
	b	.L983
.L1187:
	rsb	r9, r4, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L1014
.L1192:
	rsb	r9, r4, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r6, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L1046
.L1198:
	rsb	r8, r4, #24
	mov	r0, r6
	bic	r8, r8, #7
	rsb	r5, r4, #16
	rsb	r5, r8, r5
	add	r4, r4, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r5, #7
	str	r4, [r6, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r6, #28]
	mov	r7, r0
	b	.L1078
.L990:
	ldrb	r1, [r9, r5]	@ zero_extendqisi2
	mov	r7, #0
	mov	r10, #4
	mov	r2, #1
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	b	.L994
.L992:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r5, r5, ip
	cmn	r10, #1
	ldrb	r3, [r9, r5]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1216
.L994:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L992
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r3, r1, r3
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-72]
	and	r3, r3, #7
	orr	r0, r8, r0, asl r3
	b	.L992
.L1216:
	add	r8, r7, #32
	b	.L983
.L1206:
	rsb	r8, r5, #24
	mov	r0, r6
	bic	r8, r8, #7
	rsb	r4, r5, #16
	rsb	r4, r8, r4
	add	r5, r5, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r4, #7
	str	r5, [r6, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r6, #28]
	mov	r7, r0
	b	.L976
.L1188:
	rsb	r9, r8, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r6, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L1021
.L1193:
	rsb	r9, r8, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r4, r8, #16
	rsb	r4, r9, r4
	add	r8, r8, r9
	mov	r1, r9
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r6, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r10, r0
	b	.L1053
.L1199:
	rsb	r9, r4, #24
	mov	r0, r6
	bic	r9, r9, #7
	rsb	r8, r4, #16
	rsb	r8, r9, r8
	add	r4, r4, r9
	mov	r1, r9
	and	r8, r8, #7
	bl	BsGet
	str	r4, [r6, #32]
	orr	r0, r7, r0, asl r8
	str	r0, [r6, #28]
	mov	r7, r0
	b	.L1085
.L968:
	rsb	r8, r5, #24
	ldr	r4, [r1, #28]
	bic	r8, r8, #7
	mov	r0, r1
	rsb	r9, r5, #16
	add	r5, r5, r8
	mov	r1, r8
	rsb	r9, r8, r9
	bl	BsGet
	and	r9, r9, #7
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r6, #28]
	b	.L969
.L1207:
	rsb	r8, r4, #24
	mov	r0, r6
	bic	r8, r8, #7
	rsb	r5, r4, #16
	rsb	r5, r8, r5
	add	r4, r4, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r5, #7
	str	r4, [r6, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r6, #28]
	mov	r7, r0
	b	.L979
.L1208:
	rsb	r10, r4, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r7, r4, #16
	rsb	r7, r10, r7
	add	r4, r4, r10
	mov	r1, r10
	and	r7, r7, #7
	bl	BsGet
	str	r4, [r6, #32]
	orr	r0, r8, r0, asl r7
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L986
.L1204:
	rsb	r1, r5, #24
	rsb	r8, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-48]
	rsb	r8, r1, r8
	add	r5, r5, r1
	bl	BsGet
	and	r8, r8, #7
	ldr	r2, [fp, #-48]
	orr	r0, r4, r0, asl r8
	b	.L971
.L1203:
	rsb	r1, r8, #24
	rsb	r5, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r5, r1, r5
	add	r8, r1, r8
	bl	BsGet
	and	r5, r5, #7
	orr	r0, r10, r0, asl r5
	b	.L1033
.L973:
	ldr	r3, [fp, #-56]
	cmp	r3, #1
	beq	.L1008
	b	.L1007
.L1211:
	rsb	r1, r4, #24
	rsb	r8, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r8, r1, r8
	add	r4, r1, r4
	bl	BsGet
	and	r8, r8, #7
	orr	r0, r10, r0, asl r8
	b	.L998
	UNWIND(.fnend)
	.size	Vp9_ReadCompPred, .-Vp9_ReadCompPred
	.align	2
	.global	Vp9_ReadMvProbs
	.type	Vp9_ReadMvProbs, %function
Vp9_ReadMvProbs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	mov	r3, r1
	str	r1, [fp, #-76]
	add	r1, r1, #2
	ldr	r4, [r0, #36]
	mov	r10, r0
	ldr	r6, [r0, #32]
	add	r3, r3, #5
	ldr	r5, [r0, #28]
	str	r2, [fp, #-80]
	mov	r2, r1
	str	r3, [fp, #-48]
.L1225:
	sub	r1, r4, #1
	cmp	r6, #0
	mov	r4, r1, asl #8
	sub	r1, r4, r1, asl #2
	mov	r1, r1, lsr #8
	add	r4, r1, #1
	blt	.L1327
.L1220:
	mov	r7, r4, asl #24
	cmp	r7, r5
	bhi	.L1221
	ldr	r1, [r10, #36]
	rsb	r7, r7, r5
	ldr	r0, .L1345
	mov	r9, #0
	rsb	r1, r4, r1
	mov	r8, #6
	mov	r3, #1
	str	r2, [fp, #-56]
	ldrb	r4, [r0, r1]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r6
	str	r7, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1224
.L1222:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldr	r2, .L1345
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1328
.L1224:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1222
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r10
	str	r3, [fp, #-52]
	rsb	r6, r1, r2
	add	r5, r1, r5
	bl	BsGet
	and	r2, r6, #7
	ldr	r3, [fp, #-52]
	orr	r0, r7, r0, asl r2
	b	.L1222
.L1221:
	ldr	r3, .L1345
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r5, r5, asl r1
	rsb	r6, r1, r6
	mov	r4, r4, asl r1
	str	r5, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
.L1282:
	ldr	r3, [fp, #-48]
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L1225
	ldr	r3, [fp, #-76]
	mov	r7, r5
	add	r2, r3, #37
	str	r2, [fp, #-48]
	add	r2, r3, #25
	add	r3, r3, #57
	str	r2, [fp, #-64]
	str	r3, [fp, #-68]
.L1252:
	sub	r4, r4, #1
	cmp	r6, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1329
.L1226:
	mov	r2, r4, asl #24
	cmp	r2, r7
	bhi	.L1227
	ldr	r3, [r10, #36]
	rsb	r7, r2, r7
	ldr	r2, .L1345
	mov	r5, #0
	rsb	r4, r4, r3
	mov	r9, #6
	mov	r3, #1
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r8, r7, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L1230
.L1228:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldr	r2, .L1345
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r5, r5, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1330
.L1230:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1228
	rsb	r1, r6, #24
	rsb	r7, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	str	r3, [fp, #-52]
	rsb	r7, r1, r7
	add	r6, r1, r6
	bl	BsGet
	and	r7, r7, #7
	ldr	r3, [fp, #-52]
	orr	r0, r8, r0, asl r7
	b	.L1228
.L1328:
	ldr	r2, [fp, #-56]
	mov	r3, r9, asl #1
	orr	r3, r3, #1
	strb	r3, [r2]
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r5, [r10, #28]
	b	.L1282
.L1227:
	ldr	r3, .L1345
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r5, r3, r6
	mov	r4, r4, asl r3
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
.L1283:
	ldr	r3, [fp, #-48]
	sub	r2, r3, #32
	sub	r3, r3, #22
	str	r3, [fp, #-52]
.L1236:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r1, r4, asl #8
	sub	r4, r1, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1331
.L1231:
	mov	r3, r4, asl #24
	cmp	r3, r7
	bhi	.L1232
	ldr	r1, [r10, #36]
	rsb	r7, r3, r7
	ldr	r0, .L1345
	mov	r9, #0
	rsb	r1, r4, r1
	mov	r8, #6
	mov	r3, #1
	str	r2, [fp, #-60]
	ldrb	r4, [r0, r1]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r7, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1235
.L1233:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldr	r2, .L1345
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1332
.L1235:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1233
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r10
	str	r3, [fp, #-56]
	rsb	r6, r1, r2
	add	r5, r1, r5
	bl	BsGet
	and	r2, r6, #7
	ldr	r3, [fp, #-56]
	orr	r0, r7, r0, asl r2
	b	.L1233
.L1232:
	ldr	r3, .L1345
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r7, r7, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
.L1284:
	ldr	r3, [fp, #-52]
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L1236
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1333
.L1237:
	mov	r2, r4, asl #24
	cmp	r2, r7
	bhi	.L1238
	ldr	r3, [r10, #36]
	rsb	r7, r2, r7
	ldr	r2, .L1345
	mov	r8, #6
	rsb	r4, r4, r3
	mov	r9, #0
	mov	r3, #1
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r7, r7, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1241
.L1240:
	ldr	ip, [r10, #36]
	rsb	r0, r2, r0
	rsb	r4, r4, ip
.L1243:
	ldr	r2, .L1345
	sub	r8, r8, #1
	cmn	r8, #1
	orr	r9, r9, r1
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1334
.L1241:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	blt	.L1239
.L1244:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r8
	cmp	r2, r0
	bls	.L1240
	mov	r1, #0
	b	.L1243
.L1332:
	ldr	r2, [fp, #-60]
	mov	r9, r9, asl #1
	orr	r9, r9, #1
	strb	r9, [r2]
	ldr	r5, [r10, #32]
	ldr	r4, [r10, #36]
	ldr	r7, [r10, #28]
	b	.L1284
.L1331:
	rsb	r8, r5, #24
	mov	r0, r10
	bic	r8, r8, #7
	str	r2, [fp, #-56]
	rsb	r6, r5, #16
	add	r5, r8, r5
	mov	r1, r8
	rsb	r6, r8, r6
	bl	BsGet
	and	r6, r6, #7
	str	r5, [r10, #32]
	ldr	r2, [fp, #-56]
	orr	r0, r7, r0, asl r6
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L1231
.L1239:
	rsb	r1, r5, #24
	rsb	r6, r5, #16
	bic	r1, r1, #7
	mov	r0, r10
	str	r3, [fp, #-52]
	rsb	r6, r1, r6
	add	r5, r1, r5
	bl	BsGet
	and	r6, r6, #7
	ldr	r3, [fp, #-52]
	orr	r0, r7, r0, asl r6
	b	.L1244
.L1238:
	ldr	r3, .L1345
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r6, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
.L1245:
	ldr	r3, [fp, #-48]
	sub	r2, r3, #10
.L1251:
	sub	r4, r4, #1
	cmp	r6, #0
	mov	r1, r4, asl #8
	sub	r4, r1, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1335
.L1246:
	mov	r3, r4, asl #24
	cmp	r3, r7
	bhi	.L1247
	ldr	r1, [r10, #36]
	rsb	r7, r3, r7
	ldr	r0, .L1345
	mov	r9, #0
	rsb	r1, r4, r1
	mov	r8, #6
	mov	r3, #1
	str	r2, [fp, #-56]
	ldrb	r4, [r0, r1]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r6
	str	r7, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1250
.L1248:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldr	r2, .L1345
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1336
.L1250:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1248
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r10
	str	r3, [fp, #-52]
	rsb	r6, r1, r2
	add	r5, r1, r5
	bl	BsGet
	and	r2, r6, #7
	ldr	r3, [fp, #-52]
	orr	r0, r7, r0, asl r2
	b	.L1248
.L1247:
	ldr	r3, .L1345
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r7, r7, asl r1
	rsb	r6, r1, r6
	mov	r4, r4, asl r1
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
.L1285:
	ldr	r3, [fp, #-48]
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L1251
	add	r3, r2, #10
	ldr	r2, [fp, #-64]
	str	r3, [fp, #-48]
	add	r2, r2, #1
	str	r2, [fp, #-64]
	ldr	r2, [fp, #-68]
	cmp	r3, r2
	bne	.L1252
	ldr	r2, [fp, #-76]
	add	r3, r2, #59
	add	r2, r2, #47
	str	r3, [fp, #-72]
	str	r2, [fp, #-64]
	str	r3, [fp, #-68]
.L1253:
	ldr	r3, [fp, #-64]
	str	r3, [fp, #-48]
	mov	r3, #2
	str	r3, [fp, #-60]
.L1268:
	ldr	r2, [fp, #-48]
	mov	r3, #0
	mov	r5, r6
	mov	r6, r3
.L1259:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1337
.L1254:
	mov	r3, r4, asl #24
	cmp	r3, r7
	bhi	.L1255
	ldr	r1, [r10, #36]
	rsb	r7, r3, r7
	mov	r9, #0
	str	r6, [fp, #-52]
	rsb	r3, r4, r1
	ldr	r1, .L1345
	mov	r8, #6
	mov	r6, r9
	str	r2, [fp, #-56]
	ldrb	r4, [r1, r3]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r7, [r10, #28]
	mov	r4, r3, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1258
.L1256:
	mov	r2, r4, asl #24
	mov	r3, #1
	cmp	r2, r0
	mov	r1, r3, asl r8
	ldr	r3, .L1345
	sub	r8, r8, #1
	ldrls	ip, [r10, #36]
	rsbls	r0, r2, r0
	movhi	r1, #0
	orr	r6, r6, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	ldrb	r2, [r3, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1338
.L1258:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1256
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r9, r1, r2
	add	r5, r1, r5
	bl	BsGet
	and	r2, r9, #7
	orr	r0, r7, r0, asl r2
	b	.L1256
.L1336:
	ldr	r2, [fp, #-56]
	mov	r9, r9, asl #1
	orr	r9, r9, #1
	strb	r9, [r2]
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1285
.L1255:
	ldr	r3, .L1345
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
.L1286:
	add	r6, r6, #1
	add	r2, r2, #1
	cmp	r6, #3
	bne	.L1259
	ldr	r3, [fp, #-60]
	mov	r6, r5
	subs	r3, r3, #1
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-48]
	add	r3, r3, #3
	str	r3, [fp, #-48]
	bne	.L1268
	ldr	r5, [fp, #-60]
	ldr	r3, [fp, #-68]
.L1260:
	sub	r4, r4, #1
	cmp	r6, #0
	mov	r2, r4, asl #8
	sub	r4, r2, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1339
.L1261:
	mov	r1, r4, asl #24
	cmp	r1, r7
	bhi	.L1262
	ldr	r2, [r10, #36]
	rsb	r7, r1, r7
	ldr	r1, .L1345
	mov	r9, #0
	rsb	r2, r4, r2
	str	r5, [fp, #-48]
	mov	r8, #6
	mov	r5, r9
	ldrb	r4, [r1, r2]	@ zero_extendqisi2
	str	r3, [fp, #-52]
	mov	r7, r7, asl r4
	rsb	r6, r4, r6
	str	r7, [r10, #28]
	mov	r4, r2, asl r4
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L1265
.L1263:
	mov	r2, r4, asl #24
	mov	r3, #1
	cmp	r2, r0
	mov	r1, r3, asl r8
	ldr	r3, .L1345
	sub	r8, r8, #1
	ldrls	ip, [r10, #36]
	rsbls	r0, r2, r0
	movhi	r1, #0
	orr	r5, r5, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	ldrb	r2, [r3, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1340
.L1265:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1263
	rsb	r1, r6, #24
	rsb	r2, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r9, r1, r2
	add	r6, r1, r6
	bl	BsGet
	and	r2, r9, #7
	orr	r0, r7, r0, asl r2
	b	.L1263
.L1338:
	ldr	r2, [fp, #-56]
	mov	r9, r6
	mov	r9, r9, asl #1
	ldr	r6, [fp, #-52]
	orr	r9, r9, #1
	strb	r9, [r2]
	ldr	r4, [r10, #36]
	ldr	r5, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1286
.L1335:
	rsb	r5, r6, #24
	mov	r0, r10
	bic	r5, r5, #7
	str	r2, [fp, #-52]
	rsb	r8, r6, #16
	mov	r1, r5
	rsb	r8, r5, r8
	bl	BsGet
	and	r8, r8, #7
	add	r5, r5, r6
	ldr	r2, [fp, #-52]
	str	r5, [r10, #32]
	mov	r6, r5
	orr	r0, r7, r0, asl r8
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L1246
.L1262:
	ldr	r2, .L1345
	add	r5, r5, #1
	cmp	r5, #3
	add	r3, r3, #1
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r7, r7, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1266
.L1341:
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1260
.L1340:
	mov	r9, r5
	ldr	r5, [fp, #-48]
	ldr	r3, [fp, #-52]
	mov	r9, r9, asl #1
	add	r5, r5, #1
	orr	r9, r9, #1
	cmp	r5, #3
	add	r3, r3, #1
	strb	r9, [r3, #-1]
	bne	.L1341
.L1266:
	ldr	r2, [fp, #-68]
	ldr	r3, [fp, #-64]
	add	r2, r2, #3
	str	r2, [fp, #-68]
	ldr	r2, [fp, #-72]
	add	r3, r3, #6
	str	r3, [fp, #-64]
	cmp	r2, r3
	beq	.L1267
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1253
.L1337:
	rsb	r9, r5, #24
	mov	r0, r10
	bic	r9, r9, #7
	str	r2, [fp, #-52]
	rsb	r8, r5, #16
	add	r5, r9, r5
	mov	r1, r9
	rsb	r8, r9, r8
	bl	BsGet
	and	r8, r8, #7
	str	r5, [r10, #32]
	ldr	r2, [fp, #-52]
	orr	r0, r7, r0, asl r8
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L1254
.L1339:
	rsb	r9, r6, #24
	mov	r0, r10
	bic	r9, r9, #7
	str	r3, [fp, #-48]
	rsb	r8, r6, #16
	add	r6, r9, r6
	mov	r1, r9
	rsb	r8, r9, r8
	bl	BsGet
	and	r8, r8, #7
	str	r6, [r10, #32]
	ldr	r3, [fp, #-48]
	orr	r0, r7, r0, asl r8
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L1261
.L1330:
	ldr	r2, [fp, #-64]
	mov	r3, r5, asl #1
	orr	r3, r3, #1
	strb	r3, [r2, #-25]
	ldr	r4, [r10, #36]
	ldr	r5, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1283
.L1334:
	ldr	r2, [fp, #-64]
	mov	r3, r9, asl #1
	orr	r3, r3, #1
	strb	r3, [r2]
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1245
.L1267:
	ldr	r3, [fp, #-80]
	cmp	r3, #0
	beq	.L1219
	ldr	r3, [fp, #-76]
	add	r8, r3, #67
	add	r3, r3, #69
	str	r3, [fp, #-48]
.L1280:
	ldr	r1, [r10, #36]
	ldr	r5, [r10, #32]
	sub	r1, r1, #1
	cmp	r5, #0
	mov	r3, r1, asl #8
	sub	r1, r3, r1, asl #2
	mov	r1, r1, lsr #8
	add	r4, r1, #1
	blt	.L1269
	ldr	r6, [r10, #28]
.L1270:
	mov	r3, r4, asl #24
	cmp	r3, r6
	bhi	.L1271
	ldr	r1, [r10, #36]
	rsb	r6, r3, r6
	ldr	r0, .L1345
	mov	r3, #0
	rsb	r1, r4, r1
	mov	r9, #6
	mov	r2, #1
	mov	r7, r3
	ldrb	r4, [r0, r1]	@ zero_extendqisi2
	str	r8, [fp, #-56]
	mov	r6, r6, asl r4
	rsb	r5, r4, r5
	str	r6, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1274
.L1272:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1345
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1342
.L1274:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L1272
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r10
	str	r2, [fp, #-52]
	rsb	r8, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	orr	r0, r6, r0, asl r3
	b	.L1272
.L1276:
	ldr	r3, .L1345
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	str	r6, [r10, #28]
	mov	r1, r4, asl r1
	str	r5, [r10, #32]
	str	r1, [r10, #36]
.L1289:
	ldr	r3, [fp, #-48]
	add	r8, r8, #1
	cmp	r8, r3
	bne	.L1280
.L1219:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1271:
	ldr	r3, .L1345
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	str	r6, [r10, #28]
	mov	r3, r4, asl r3
	str	r5, [r10, #32]
	str	r3, [r10, #36]
.L1288:
	sub	r3, r3, #1
	cmp	r5, #0
	mov	r1, r3, asl #8
	sub	r3, r1, r3, asl #2
	mov	r1, r3, lsr #8
	add	r4, r1, #1
	blt	.L1343
.L1275:
	mov	r3, r4, asl #24
	cmp	r3, r6
	bhi	.L1276
	ldr	r1, [r10, #36]
	rsb	r6, r3, r6
	ldr	r0, .L1345
	mov	r3, #0
	rsb	r1, r4, r1
	mov	r9, #6
	mov	r2, #1
	str	r8, [fp, #-56]
	ldrb	r4, [r0, r1]	@ zero_extendqisi2
	mov	r7, r6, asl r4
	rsb	r5, r4, r5
	str	r7, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	mov	r6, r3
	str	r4, [r10, #36]
	b	.L1279
.L1277:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1345
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r6, r6, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1344
.L1279:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1277
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r10
	str	r2, [fp, #-52]
	rsb	r8, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	orr	r0, r7, r0, asl r3
	b	.L1277
.L1344:
	ldr	r8, [fp, #-56]
	mov	r3, r6, asl #1
	orr	r3, r3, #1
	strb	r3, [r8]
	b	.L1289
.L1342:
	ldr	r8, [fp, #-56]
	mov	r3, r7, asl #1
	orr	r3, r3, #1
	strb	r3, [r8, #-2]
	ldr	r3, [r10, #36]
	ldr	r5, [r10, #32]
	ldr	r6, [r10, #28]
	b	.L1288
.L1327:
	rsb	r8, r6, #24
	mov	r0, r10
	bic	r8, r8, #7
	str	r2, [fp, #-52]
	rsb	r7, r6, #16
	add	r6, r8, r6
	mov	r1, r8
	rsb	r7, r8, r7
	bl	BsGet
	and	r7, r7, #7
	str	r6, [r10, #32]
	ldr	r2, [fp, #-52]
	orr	r0, r5, r0, asl r7
	str	r0, [r10, #28]
	mov	r5, r0
	b	.L1220
.L1333:
	rsb	r8, r5, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r5, #16
	rsb	r6, r8, r6
	add	r5, r8, r5
	mov	r1, r8
	and	r6, r6, #7
	bl	BsGet
	str	r5, [r10, #32]
	orr	r0, r7, r0, asl r6
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L1237
.L1329:
	rsb	r8, r6, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r5, r6, #16
	rsb	r5, r8, r5
	mov	r1, r8
	bl	BsGet
	and	r3, r5, #7
	add	r5, r8, r6
	str	r5, [r10, #32]
	mov	r6, r5
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L1226
.L1269:
	rsb	r7, r5, #24
	mov	r0, r10
	bic	r7, r7, #7
	ldr	r6, [r10, #28]
	rsb	r9, r5, #16
	add	r5, r5, r7
	mov	r1, r7
	rsb	r9, r7, r9
	bl	BsGet
	and	r9, r9, #7
	str	r5, [r10, #32]
	orr	r0, r6, r0, asl r9
	str	r0, [r10, #28]
	mov	r6, r0
	b	.L1270
.L1343:
	rsb	r9, r5, #24
	mov	r0, r10
	bic	r9, r9, #7
	rsb	r7, r5, #16
	rsb	r7, r9, r7
	add	r5, r9, r5
	mov	r1, r9
	and	r7, r7, #7
	bl	BsGet
	str	r5, [r10, #32]
	orr	r0, r6, r0, asl r7
	str	r0, [r10, #28]
	mov	r6, r0
	b	.L1275
.L1346:
	.align	2
.L1345:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ReadMvProbs, .-Vp9_ReadMvProbs
	.align	2
	.global	Vp9_PrepareReadModeInfo
	.type	Vp9_PrepareReadModeInfo, %function
Vp9_PrepareReadModeInfo:
	UNWIND(.fnstart)
	@ args = 16, pretend = 0, frame = 32
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
	add	r7, r0, #4352
	mov	r6, r1
	str	r3, [fp, #-60]
	mov	r8, r7
	add	r7, r7, #48
	add	r8, r8, #51
	mov	r3, #0
	str	r0, [fp, #-68]
	str	r2, [fp, #-56]
	str	r3, [fp, #-48]
.L1351:
	ldr	r4, [r6, #36]
	ldr	r5, [r6, #32]
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1348
	ldr	r3, [r6, #28]
.L1349:
	mov	r2, r4, asl #24
	mov	r1, r7
	cmp	r2, r3
	mov	r0, r6
	rsb	ip, r2, r3
	bhi	.L1350
	ldr	r3, [r6, #36]
	rsb	r4, r4, r3
	ldr	r3, .L1497
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	ip, ip, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	ip, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	bl	Vp9_DiffUpdateProb
.L1428:
	add	r7, r7, #1
	cmp	r7, r8
	bne	.L1351
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	adds	r3, r3, #0
	movne	r3, #1
	cmp	r2, #0
	movne	r3, #0
	cmp	r3, #0
	bne	.L1474
.L1352:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #16]
	str	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1350:
	ldr	r2, .L1497
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L1428
.L1348:
	rsb	r10, r5, #24
	rsb	r3, r5, #16
	bic	r10, r10, #7
	mov	r0, r6
	rsb	r3, r10, r3
	ldr	r9, [r6, #28]
	mov	r1, r10
	str	r3, [fp, #-64]
	bl	BsGet
	ldr	r3, [fp, #-64]
	add	r5, r5, r10
	str	r5, [r6, #32]
	and	r3, r3, #7
	orr	r0, r9, r0, asl r3
	str	r0, [r6, #28]
	mov	r3, r0
	b	.L1349
.L1474:
	ldr	r4, [fp, #-68]
	mov	r1, r6
	mov	r0, r4
	bl	Vp9_ReadInterModeProbs
	ldr	r3, [fp, #4]
	cmp	r3, #4
	add	r3, r4, #4416
	add	r3, r3, #52
	str	r3, [fp, #-76]
	beq	.L1475
.L1353:
	ldr	r3, [fp, #-68]
	add	r9, r3, #4352
	add	r10, r3, #4416
	add	r9, r9, #63
	add	r10, r10, #3
.L1357:
	ldr	r4, [r6, #36]
	ldr	r5, [r6, #32]
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1354
	ldr	r3, [r6, #28]
.L1355:
	mov	r2, r4, asl #24
	mov	r1, r9
	cmp	r2, r3
	mov	r0, r6
	rsb	ip, r2, r3
	bhi	.L1356
	ldr	r3, [r6, #36]
	rsb	r4, r4, r3
	ldr	r3, .L1497
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	ip, ip, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	ip, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	bl	Vp9_DiffUpdateProb
.L1429:
	add	r9, r9, #1
	cmp	r9, r10
	bne	.L1357
	ldr	ip, [fp, #-68]
	sub	r3, fp, #48
	ldr	r2, [fp, #8]
	mov	r1, r6
	add	lr, ip, #4096
	mov	r0, ip
	add	ip, ip, #4160
	mov	r4, lr
	mov	r5, ip
	bl	Vp9_ReadCompPred
	add	r3, r4, #9
	add	r4, r6, #28
	str	r3, [fp, #-56]
	mov	ip, r5
	add	r3, r5, #9
	str	r3, [fp, #-72]
	ldmia	r4, {r4, r5, r8}
	mov	r7, r5
.L1358:
	ldr	r3, [fp, #-56]
	mov	r10, r8
	sub	r9, r3, #9
.L1391:
	sub	r10, r10, #1
	cmp	r7, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1476
.L1359:
	mov	r8, r10, asl #24
	cmp	r8, r4
	bhi	.L1360
	ldr	r3, [r6, #36]
	rsb	r8, r8, r4
	rsb	r10, r10, r3
	ldr	r3, .L1497
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r7, r3, r7
	sub	r4, r10, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r8, r8, asl r3
	str	r10, [r6, #36]
	add	r4, r4, #1
	str	r7, [r6, #32]
	str	r8, [r6, #28]
	blt	.L1477
.L1361:
	mov	r3, r4, asl #24
	cmp	r3, r8
	bhi	.L1362
	ldr	r2, [r6, #36]
	rsb	r8, r3, r8
	ldr	r3, .L1497
	rsb	r4, r4, r2
	ldrb	r0, [r3, r4]	@ zero_extendqisi2
	mov	r2, r4, asl r0
	rsb	r4, r0, r7
	sub	r5, r2, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r0
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r8, [r6, #28]
	blt	.L1478
.L1364:
	mov	r2, r5, asl #24
	cmp	r2, r8
	bhi	.L1369
	ldr	r3, [r6, #36]
	rsb	r8, r2, r8
	rsb	r5, r5, r3
	ldr	r3, .L1497
	ldrb	r0, [r3, r5]	@ zero_extendqisi2
	mov	r3, r5, asl r0
	rsb	r7, r0, r4
	sub	r5, r3, #1
	cmp	r7, #0
	ubfx	r5, r5, #1, #24
	mov	r8, r8, asl r0
	str	r3, [r6, #36]
	add	r5, r5, #1
	str	r7, [r6, #32]
	str	r8, [r6, #28]
	blt	.L1479
.L1371:
	mov	r3, r5, asl #24
	cmp	r3, r8
	bhi	.L1375
	ldr	r4, [r6, #36]
	rsb	r8, r3, r8
	ldr	r1, .L1497
	mov	r3, #6
	rsb	r5, r5, r4
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-64]
	ldrb	r4, [r1, r5]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r7, r4, r7
	str	r8, [r6, #28]
	mov	r4, r5, asl r4
	str	r7, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L1376
.L1380:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1480
.L1376:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1380
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-60]
	rsb	r9, r1, r3
	add	r7, r1, r7
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-60]
	orr	r0, r8, r0, asl r3
	b	.L1380
.L1360:
	ldr	r3, .L1497
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r7, r3, r7
	mov	r10, r10, asl r3
	str	r4, [r6, #28]
	str	r7, [r6, #32]
	str	r10, [r6, #36]
.L1430:
	ldr	r3, [fp, #-56]
	add	r9, r9, #1
	cmp	r9, r3
	bne	.L1391
	ldr	r2, [fp, #-72]
	add	r3, r9, #16
	mov	r8, r10
	str	r3, [fp, #-56]
	cmp	r3, r2
	bne	.L1358
	ldr	r3, [fp, #-68]
	add	r2, r3, #4608
	add	r3, r3, #4672
	add	r3, r3, #36
	str	r3, [fp, #-64]
	mov	r3, r10
	add	r2, r2, #52
	str	r2, [fp, #-60]
.L1392:
	ldr	r2, [fp, #-60]
	mov	r9, #0
	mov	r10, r3
	str	r2, [fp, #-56]
.L1427:
	sub	r10, r10, #1
	cmp	r7, #0
	mov	r2, r10, asl #8
	sub	r10, r2, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1481
.L1393:
	mov	r8, r10, asl #24
	cmp	r8, r4
	bhi	.L1394
	ldr	r3, [r6, #36]
	rsb	r8, r8, r4
	rsb	r10, r10, r3
	ldr	r3, .L1497
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r5, r3, r7
	sub	r4, r10, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r8, r8, asl r3
	str	r10, [r6, #36]
	add	r4, r4, #1
	str	r5, [r6, #32]
	str	r8, [r6, #28]
	blt	.L1482
.L1395:
	mov	r7, r4, asl #24
	cmp	r7, r8
	bhi	.L1396
	ldr	r2, [r6, #36]
	rsb	r8, r7, r8
	ldr	r3, .L1497
	rsb	r4, r4, r2
	ldrb	r7, [r3, r4]	@ zero_extendqisi2
	mov	r2, r4, asl r7
	rsb	r4, r7, r5
	cmp	r4, #0
	sub	r5, r2, #1
	ubfx	r5, r5, #1, #24
	mov	r7, r8, asl r7
	str	r2, [r6, #36]
	add	r5, r5, #1
	str	r4, [r6, #32]
	str	r7, [r6, #28]
	blt	.L1483
.L1398:
	mov	r8, r5, asl #24
	cmp	r8, r7
	bhi	.L1403
	ldr	r1, [r6, #36]
	rsb	r0, r8, r7
	ldr	r3, .L1497
	rsb	r1, r5, r1
	ldrb	r5, [r3, r1]	@ zero_extendqisi2
	mov	r1, r1, asl r5
	rsb	r8, r5, r4
	sub	r7, r1, #1
	cmp	r8, #0
	ubfx	r7, r7, #1, #24
	mov	r5, r0, asl r5
	str	r1, [r6, #36]
	add	r7, r7, #1
	str	r8, [r6, #32]
	str	r5, [r6, #28]
	blt	.L1484
.L1405:
	mov	r3, r7, asl #24
	cmp	r3, r5
	bhi	.L1409
	ldr	r4, [r6, #36]
	rsb	r5, r3, r5
	ldr	r1, .L1497
	mov	r3, #6
	rsb	r4, r7, r4
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-72]
	ldrb	r1, [r1, r4]	@ zero_extendqisi2
	mov	r7, r5, asl r1
	rsb	r8, r1, r8
	mov	r4, r4, asl r1
	str	r7, [r6, #28]
	str	r8, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L1410
.L1414:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1485
.L1410:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1414
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-68]
	rsb	r9, r1, r3
	add	r8, r1, r8
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-68]
	orr	r0, r7, r0, asl r3
	b	.L1414
.L1394:
	ldr	r3, .L1497
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r7
	mov	r10, r10, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r10, [r6, #36]
.L1431:
	add	r9, r9, #1
	ldr	r3, [fp, #-56]
	cmp	r9, #3
	add	r3, r3, #1
	str	r3, [fp, #-56]
	addne	r4, r6, #28
	ldmneia	r4, {r4, r7, r10}
	bne	.L1427
.L1486:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	add	r3, r3, #3
	str	r3, [fp, #-60]
	cmp	r3, r2
	beq	.L1426
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r7, [r6, #32]
	b	.L1392
.L1481:
	rsb	r5, r7, #24
	mov	r0, r6
	bic	r5, r5, #7
	rsb	r8, r7, #16
	rsb	r8, r5, r8
	mov	r1, r5
	add	r5, r5, r7
	bl	BsGet
	and	r3, r8, #7
	str	r5, [r6, #32]
	mov	r7, r5
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1393
.L1396:
	ldr	r3, .L1497
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-72]
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r3, #3
	mov	r7, r3
	mov	r8, r8, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L1401
.L1399:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1487
.L1401:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1399
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-68]
	rsb	r9, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-68]
	orr	r0, r8, r0, asl r3
	b	.L1399
.L1487:
	ldr	r9, [fp, #-72]
.L1402:
	ldr	r3, [fp, #-56]
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L1497
	sub	ip, r2, #1
	add	r10, r3, r10
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	bgt	.L1419
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1420
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1420:
	add	r3, r3, #1
.L1422:
	ldr	r2, [fp, #-56]
	strb	r3, [r2]
	b	.L1431
.L1419:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1423
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1423:
	rsb	r3, r3, #255
	b	.L1422
.L1476:
	rsb	r8, r7, #24
	mov	r0, r6
	bic	r8, r8, #7
	rsb	r5, r7, #16
	rsb	r5, r8, r5
	add	r7, r8, r7
	mov	r1, r8
	bl	BsGet
	and	r3, r5, #7
	str	r7, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L1359
.L1362:
	ldr	r3, .L1497
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-64]
	ldrb	r1, [r3, r4]	@ zero_extendqisi2
	mov	r3, #3
	rsb	r5, r1, r7
	mov	r8, r8, asl r1
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	mov	r7, r3
	str	r4, [r6, #36]
	b	.L1367
.L1365:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1488
.L1367:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1365
	rsb	r1, r5, #24
	rsb	r3, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-60]
	rsb	r9, r1, r3
	add	r5, r1, r5
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-60]
	orr	r0, r8, r0, asl r3
	b	.L1365
.L1488:
	ldr	r9, [fp, #-64]
.L1368:
	ldrb	r2, [r9]	@ zero_extendqisi2
	ldr	r3, .L1497
	sub	ip, r2, #1
	add	r10, r3, r10
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r10, #256]	@ zero_extendqisi2
	bgt	.L1385
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1386
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1386:
	add	r3, r3, #1
.L1388:
	add	r4, r6, #28
	strb	r3, [r9]
	ldmia	r4, {r4, r7, r10}
	b	.L1430
.L1385:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1389
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1389:
	rsb	r3, r3, #255
	b	.L1388
.L1403:
	ldr	r3, .L1497
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-72]
	ldrb	r1, [r3, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r8, r3
	mov	r7, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	b	.L1408
.L1406:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	ldrb	r3, [r3, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1489
.L1408:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1406
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-68]
	rsb	r9, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-68]
	orr	r0, r7, r0, asl r3
	b	.L1406
.L1489:
	ldr	r9, [fp, #-72]
	add	r10, r10, #16
	b	.L1402
.L1485:
	cmp	r10, #64
	ldr	r9, [fp, #-72]
	bgt	.L1490
.L1416:
	add	r10, r10, #64
	b	.L1402
.L1369:
	ldr	r3, .L1497
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-64]
	ldrb	r1, [r3, r5]	@ zero_extendqisi2
	mov	r3, #3
	mov	r7, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	mov	r8, r3
	str	r5, [r6, #36]
	b	.L1374
.L1372:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	ldrb	r3, [r3, r5]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1491
.L1374:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1372
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-60]
	rsb	r9, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-60]
	orr	r0, r7, r0, asl r3
	b	.L1372
.L1491:
	ldr	r9, [fp, #-64]
	add	r10, r10, #16
	b	.L1368
.L1480:
	cmp	r10, #64
	ldr	r9, [fp, #-64]
	bgt	.L1492
.L1382:
	add	r10, r10, #64
	b	.L1368
.L1409:
	ldr	r3, .L1497
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-72]
	ldrb	r4, [r3, r7]	@ zero_extendqisi2
	mov	r3, #4
	mov	r7, r7, asl r4
	mov	r5, r5, asl r4
	rsb	r8, r4, r8
	str	r7, [r6, #36]
	mov	r4, r7
	str	r5, [r6, #28]
	str	r8, [r6, #32]
	mov	r7, r3
	b	.L1413
.L1411:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r5, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1493
.L1413:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L1411
	rsb	r1, r8, #24
	rsb	r3, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-68]
	rsb	r9, r1, r3
	add	r8, r1, r8
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-68]
	orr	r0, r5, r0, asl r3
	b	.L1411
.L1493:
	ldr	r9, [fp, #-72]
	add	r10, r10, #32
	b	.L1402
.L1482:
	rsb	r10, r5, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r7, r5, #16
	rsb	r7, r10, r7
	add	r5, r5, r10
	mov	r1, r10
	and	r7, r7, #7
	bl	BsGet
	str	r5, [r6, #32]
	orr	r0, r8, r0, asl r7
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L1395
.L1356:
	ldr	r2, .L1497
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L1429
.L1375:
	ldr	r3, .L1497
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-64]
	ldrb	r4, [r3, r5]	@ zero_extendqisi2
	mov	r3, #4
	mov	r8, r8, asl r4
	rsb	r7, r4, r7
	str	r8, [r6, #28]
	mov	r4, r5, asl r4
	str	r7, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L1379
.L1377:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1494
.L1379:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1377
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r6
	str	r2, [fp, #-60]
	rsb	r9, r1, r3
	add	r7, r1, r7
	bl	BsGet
	and	r3, r9, #7
	ldr	r2, [fp, #-60]
	orr	r0, r8, r0, asl r3
	b	.L1377
.L1494:
	ldr	r9, [fp, #-64]
	add	r10, r10, #32
	b	.L1368
.L1477:
	rsb	r10, r7, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r5, r7, #16
	rsb	r5, r10, r5
	add	r7, r7, r10
	mov	r1, r10
	bl	BsGet
	and	r3, r5, #7
	str	r7, [r6, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L1361
.L1490:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r7
	blt	.L1495
.L1417:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	r1, [r6, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r10, r10, r2
	rsbls	r4, r4, r1
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	b	.L1416
.L1483:
	rsb	r10, r4, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r8, r4, #16
	rsb	r8, r10, r8
	add	r4, r4, r10
	mov	r1, r10
	bl	BsGet
	and	r3, r8, #7
	str	r4, [r6, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r6, #28]
	mov	r7, r0
	b	.L1398
.L1426:
	ldr	r1, [fp, #-76]
	mov	r0, r6
	ldr	r2, [fp, #12]
	bl	Vp9_ReadMvProbs
	b	.L1352
.L1492:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r5, r10, #65
	movge	r0, r8
	blt	.L1496
.L1383:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldr	r3, .L1497
	ldrls	r2, [r6, #36]
	movls	r10, #1
	movhi	r10, #0
	add	r10, r5, r10
	rsbls	r4, r4, r2
	ldrb	r3, [r3, r4]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
	b	.L1382
.L1478:
	rsb	r10, r4, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r7, r4, #16
	rsb	r7, r10, r7
	mov	r1, r10
	bl	BsGet
	and	r3, r7, #7
	add	r7, r4, r10
	str	r7, [r6, #32]
	mov	r4, r7
	orr	r0, r8, r0, asl r3
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L1364
.L1484:
	rsb	r10, r8, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r4, r8, #16
	rsb	r4, r10, r4
	add	r8, r8, r10
	mov	r1, r10
	bl	BsGet
	and	r3, r4, #7
	str	r8, [r6, #32]
	orr	r0, r5, r0, asl r3
	str	r0, [r6, #28]
	mov	r5, r0
	b	.L1405
.L1354:
	rsb	r8, r5, #24
	rsb	r3, r5, #16
	bic	r8, r8, #7
	mov	r0, r6
	rsb	r3, r8, r3
	ldr	r7, [r6, #28]
	mov	r1, r8
	str	r3, [fp, #-56]
	bl	BsGet
	ldr	r3, [fp, #-56]
	add	r5, r5, r8
	str	r5, [r6, #32]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	str	r0, [r6, #28]
	mov	r3, r0
	b	.L1355
.L1479:
	rsb	r10, r7, #24
	mov	r0, r6
	bic	r10, r10, #7
	rsb	r4, r7, #16
	rsb	r4, r10, r4
	add	r7, r7, r10
	mov	r1, r10
	bl	BsGet
	and	r3, r4, #7
	str	r7, [r6, #32]
	orr	r0, r8, r0, asl r3
	str	r0, [r6, #28]
	mov	r8, r0
	b	.L1371
.L1495:
	rsb	r1, r8, #24
	rsb	r5, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r5, r1, r5
	add	r8, r1, r8
	bl	BsGet
	and	r5, r5, #7
	orr	r0, r7, r0, asl r5
	b	.L1417
.L1475:
	mov	r1, r6
	ldr	r0, [fp, #-68]
	bl	Vp9_ReadSwitchableInterpProbs
	b	.L1353
.L1498:
	.align	2
.L1497:
	.word	.LANCHOR0
.L1496:
	rsb	r1, r7, #24
	rsb	r10, r7, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r10, r1, r10
	add	r7, r1, r7
	bl	BsGet
	and	r10, r10, #7
	orr	r0, r8, r0, asl r10
	b	.L1383
	UNWIND(.fnend)
	.size	Vp9_PrepareReadModeInfo, .-Vp9_PrepareReadModeInfo
	.global	__aeabi_uidiv
	.align	2
	.global	Vp9_AdaptProbs
	.type	Vp9_AdaptProbs, %function
Vp9_AdaptProbs:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
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
	mov	r5, r0
	ldrsb	r0, [r1, r0]
	mov	r4, r1
	mov	r6, r2
	mov	r9, r3
	cmp	r0, #0
	ldr	r7, [fp, #4]
	ble	.L1508
	str	r7, [sp]
	bl	Vp9_AdaptProbs
	add	r3, r4, r5
	mov	r8, r0
	ldrsb	r0, [r3, #1]
	cmp	r0, #0
	ble	.L1509
.L1502:
	str	r7, [sp]
	mov	r1, r4
	mov	r3, r9
	mov	r2, r6
	bl	Vp9_AdaptProbs
.L1503:
	adds	r7, r0, r8
	ldrb	r4, [r9, r5, lsr #1]	@ zero_extendqisi2
	beq	.L1504
	ldr	r3, .L1510
	mov	r0, r8, asl #8
	add	r0, r0, r7, lsr #1
	mov	r1, r7
	cmp	r7, #20
	addls	r3, r3, r7
	addhi	r3, r3, #20
	ldrb	r8, [r3, #512]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	rsb	r3, r8, #256
	mul	r4, r4, r3
	add	r4, r4, #128
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r0, r0
	mla	r4, r8, r0, r4
	ubfx	r4, r4, #8, #8
.L1504:
	mov	r0, r7
	strb	r4, [r6, r5, lsr #1]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1508:
	mov	r0, r0, asl #2
	add	r3, r4, r5
	rsb	r0, r0, #0
	ldr	r8, [r7, r0]
	ldrsb	r0, [r3, #1]
	cmp	r0, #0
	bgt	.L1502
.L1509:
	mov	r0, r0, asl #2
	rsb	r0, r0, #0
	ldr	r0, [r7, r0]
	b	.L1503
.L1511:
	.align	2
.L1510:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_AdaptProbs, .-Vp9_AdaptProbs
	.align	2
	.global	Lf_Init_Lut
	.type	Lf_Init_Lut, %function
Lf_Init_Lut:
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
	mov	r3, #0
	mov	r2, #1
	strb	r3, [r0, #64]
	strb	r3, [r0, #67]
	strb	r3, [r0, #68]
	strb	r3, [r0, #69]
	strb	r3, [r0, #70]
	strb	r3, [r0, #71]
	strb	r3, [r0, #72]
	strb	r3, [r0, #65]
	strb	r3, [r0, #66]
	strb	r3, [r0, #73]
	strb	r3, [r0, #76]
	strb	r2, [r0, #74]
	strb	r2, [r0, #75]
	strb	r2, [r0, #77]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Lf_Init_Lut, .-Lf_Init_Lut
	.align	2
	.global	VP9_Loop_Filter_Init
	.type	VP9_Loop_Filter_Init, %function
VP9_Loop_Filter_Init:
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
	mov	r3, #0
	mov	r2, #1
	strb	r3, [r1, #64]
	strb	r3, [r1, #67]
	strb	r3, [r1, #68]
	strb	r3, [r1, #69]
	strb	r3, [r1, #70]
	strb	r3, [r1, #71]
	strb	r3, [r1, #72]
	strb	r3, [r1, #65]
	strb	r3, [r1, #66]
	strb	r3, [r1, #73]
	strb	r3, [r1, #76]
	strb	r2, [r1, #74]
	strb	r2, [r1, #75]
	strb	r2, [r1, #77]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_Loop_Filter_Init, .-VP9_Loop_Filter_Init
	.align	2
	.global	VP9_InitDecPara
	.type	VP9_InitDecPara, %function
VP9_InitDecPara:
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
	ldr	r7, .L1515
	movw	r6, #10820
	movt	r6, 4
	add	r6, r0, r6
	mov	r5, r0
	mov	r1, #0
	movw	r2, #5488
	ldr	r3, [r7, #48]
	mov	r0, r6
	add	r4, r5, #270336
	blx	r3
	add	r3, r5, #274432
	movw	r0, #16312
	mov	r2, #3
	movt	r0, 4
	str	r2, [r3, #3600]
	add	r0, r5, r0
	mov	r5, #0
	bl	ResetVoQueue
	ldr	r3, [r7, #48]
	mov	r2, #2
	add	r0, r6, #64
	str	r2, [r4, #2864]
	mov	r1, r5
	str	r5, [r4, #2860]
	mov	r2, #16
	blx	r3
	mov	r3, #1
	strb	r5, [r4, #2948]
	strb	r5, [r4, #2951]
	strb	r5, [r4, #2952]
	strb	r5, [r4, #2953]
	strb	r5, [r4, #2954]
	strb	r5, [r4, #2955]
	strb	r5, [r4, #2956]
	strb	r5, [r4, #2949]
	strb	r5, [r4, #2950]
	strb	r5, [r4, #2957]
	strb	r5, [r4, #2960]
	strb	r3, [r4, #2958]
	strb	r3, [r4, #2959]
	strb	r3, [r4, #2961]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1516:
	.align	2
.L1515:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9_InitDecPara, .-VP9_InitDecPara
	.align	2
	.global	VP9DEC_Init
	.type	VP9DEC_Init, %function
VP9DEC_Init:
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
	mov	r4, r0
	mov	r6, r1
	mov	r0, #2
	ldr	r1, .L1533
	bl	dprint_vfmw
	cmp	r6, #0
	cmpne	r4, #0
	moveq	r7, #1
	movne	r7, #0
	beq	.L1531
	ldr	r3, [r6, #624]
	add	r5, r4, #311296
	add	r8, r4, #278528
	ldr	r9, .L1533+4
	cmp	r3, #1
	mov	r1, #0
	addeq	r3, r4, #270336
	ldr	r10, [r8, #272]
	ldreq	r2, [r5, #2724]
	mov	r0, r4
	ldreq	r7, [r3, #2568]
	ldr	r3, [r9, #48]
	streq	r2, [fp, #-48]
	movw	r2, #52024
	movt	r2, 4
	strne	r7, [fp, #-48]
	blx	r3
	movw	r0, #16312
	str	r10, [r8, #272]
	movt	r0, 4
	add	r0, r4, r0
	bl	ResetVoQueue
	str	r6, [r4]
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r5, #2860]
	beq	.L1532
	ldr	r3, [r4]
	add	r8, r4, #270336
	mov	r10, #0
	mov	r2, #3
	ldr	r1, [r3, #8]
	str	r2, [r8, #2624]
	str	r2, [r8, #2572]
	str	r1, [r8, #2564]
	str	r10, [r8, #2576]
	ldr	r0, [r3, #48]
	str	r0, [r8, #2580]
	ldr	r3, [r3, #52]
	str	r3, [r8, #2584]
	bl	MEM_Phy2Vir
	mov	r3, #2048
	str	r3, [r8, #2592]
	mov	r2, #32
	mov	r1, #0
	str	r0, [r8, #2588]
	movw	r0, #51924
	str	r10, [r5, #2736]
	movt	r0, 4
	str	r10, [r5, #2740]
	add	r0, r4, r0
	str	r10, [r5, #2764]
	str	r10, [r5, #2768]
	str	r10, [r5, #2804]
	str	r10, [r5, #2808]
	ldr	r3, [r6, #624]
	cmp	r3, #1
	strne	r10, [r5, #2724]
	strne	r10, [r8, #2568]
	ldreq	r3, [fp, #-48]
	streq	r3, [r5, #2724]
	ldr	r3, [r9, #48]
	streq	r7, [r8, #2568]
	blx	r3
	mov	r0, r4
	bl	VP9_InitDecPara
	movw	ip, #10932
	add	r2, r8, #2704
	movt	ip, 4
	add	ip, r4, ip
	mov	r0, #0
	mov	r3, r2
	mov	r1, ip
.L1524:
	str	r0, [r3, #4]!
	cmp	r3, ip
	str	r0, [r1, #4]!
	bne	.L1524
	movw	r3, #11012
	movw	r1, #11048
	movt	r3, 4
	movt	r1, 4
	add	r3, r4, r3
	add	r1, r4, r1
	mvn	r0, #0
.L1525:
	str	r0, [r3, #4]!
	cmp	r3, r1
	bne	.L1525
	movw	r1, #10968
	mov	r3, #0
	movt	r1, 4
	add	r1, r4, r1
	mov	r0, #1
.L1526:
	str	r3, [r1, #4]!
	add	r3, r3, #1
	cmp	r3, #8
	str	r0, [r2, #4]!
	bne	.L1526
	mov	r0, #0
.L1519:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1531:
	movw	r2, #2013
	ldr	r1, .L1533+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L1519
.L1532:
	ldr	r1, .L1533+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L1519
.L1534:
	.align	2
.L1533:
	.word	.LC1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC3
	UNWIND(.fnend)
	.size	VP9DEC_Init, .-VP9DEC_Init
	.align	2
	.global	Vp9_ParseSuperFrameIndex
	.type	Vp9_ParseSuperFrameIndex, %function
Vp9_ParseSuperFrameIndex:
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
	ble	.L1547
	add	ip, r0, r1
	mov	r5, #0
	ldrb	ip, [ip, #-1]	@ zero_extendqisi2
	str	r5, [r3]
	and	lr, ip, #224
	cmp	lr, #192
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	and	r6, ip, #7
	ubfx	r8, ip, #3, #2
	add	r6, r6, #1
	add	r7, r8, #1
	mul	r4, r6, r7
	add	r4, r4, #2
	cmp	r1, r4
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	rsb	lr, r4, r1
	ldrb	lr, [r0, lr]	@ zero_extendqisi2
	cmp	lr, ip
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r1, r1, #1
	cmp	r6, r5
	rsb	r1, r4, r1
	add	r4, r0, r1
	beq	.L1538
	sub	r9, r2, #4
.L1539:
	cmp	r7, #0
	beq	.L1542
	mov	r2, #0
	sub	r1, r4, #1
	add	lr, r4, r8
	mov	r0, r2
.L1540:
	ldrb	ip, [r1, #1]!	@ zero_extendqisi2
	cmp	r1, lr
	orr	r0, r0, ip, asl r2
	add	r2, r2, #8
	bne	.L1540
	add	r4, r4, r7
.L1541:
	add	r5, r5, #1
	str	r0, [r9, #4]!
	cmp	r6, r5
	bhi	.L1539
.L1538:
	str	r6, [r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1547:
	ldr	r1, .L1548
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1542:
	mov	r0, r7
	b	.L1541
.L1549:
	.align	2
.L1548:
	.word	.LC4
	UNWIND(.fnend)
	.size	Vp9_ParseSuperFrameIndex, .-Vp9_ParseSuperFrameIndex
	.align	2
	.global	VP9_GetImageBuffer
	.type	VP9_GetImageBuffer, %function
VP9_GetImageBuffer:
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
	add	r7, r0, #274432
	add	r5, r0, #311296
	add	r6, r0, #270336
	mov	r4, r0
	ldr	r3, [r7, #3620]
	ldr	r0, [r5, #2860]
	cmp	r3, #1
	moveq	r1, #0
	movne	r1, #1
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r6, #2612]
	blt	.L1569
	mov	r1, r0
	ldr	r0, [r5, #2860]
	bl	FSP_GetLogicFs
	subs	r4, r0, #0
	beq	.L1570
	ldr	r2, [r6, #2612]
	mov	r0, #18
	ldr	r1, .L1573
	bl	dprint_vfmw
	ldr	r2, [r4, #28]
	cmp	r2, #0
	beq	.L1556
	ldr	r3, [r4, #32]
	cmp	r3, #0
	beq	.L1556
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L1573+4
	bl	dprint_vfmw
	ldr	r3, [r7, #3620]
	cmp	r3, #1
	beq	.L1571
	ldr	r2, [r4, #28]
	mov	r3, #0
	mov	r0, r3
	str	r3, [r2, #80]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1556:
	mov	r2, #2240
	ldr	r1, .L1573+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1569:
	ldr	r1, .L1573+12
	mov	r0, #0
	bl	dprint_vfmw
	movw	r1, #16312
	ldr	r0, [r5, #2860]
	movt	r1, 4
	add	r1, r4, r1
	bl	FSP_ClearNotInVoQueue
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1570:
	movw	r2, #2228
	ldr	r1, .L1573+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1571:
	ldr	r3, [r7, #3624]
	cmp	r3, #8
	bls	.L1559
	ldr	r2, .L1573+20
	mov	r0, #0
	ldr	r1, .L1573+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1559:
	add	r6, r6, r3, lsl #2
	ldr	r0, [r5, #2860]
	ldr	r1, [r6, #2824]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1572
	ldr	ip, [r3, #28]
	add	r1, r3, #40
	mov	r2, #640
	add	r0, r4, #40
	str	ip, [r4, #28]
	ldr	r3, [r3, #28]
	str	r3, [r4, #32]
	ldr	r3, [ip, #72]
	str	r3, [r4, #20]
	bl	memcpy
	ldrsb	r3, [r4, #3]
	mov	r0, #0
	strb	r0, [r4, #2]
	str	r3, [r4, #188]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1572:
	ldr	r3, .L1573+28
	movw	r2, #2257
	ldr	r1, .L1573+32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1574:
	.align	2
.L1573:
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC5
	.word	.LC6
	.word	.LANCHOR0+536
	.word	.LC10
	.word	.LC11
	.word	.LC12
	UNWIND(.fnend)
	.size	VP9_GetImageBuffer, .-VP9_GetImageBuffer
	.align	2
	.global	VP9_FreeCurFb
	.type	VP9_FreeCurFb, %function
VP9_FreeCurFb:
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
	add	r5, r0, #270336
	add	r4, r0, #311296
	ldr	r1, [r5, #2612]
	cmp	r1, #0
	blt	.L1576
	mov	r2, #1
	ldr	r0, [r4, #2860]
	bl	FSP_ClearLogicFs
.L1576:
	ldr	r3, [r4, #2760]
	cmp	r3, #8
	addls	r3, r3, #20
	movls	r2, #0
	addls	r5, r5, r3, lsl #2
	strls	r2, [r5, #2628]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_FreeCurFb, .-VP9_FreeCurFb
	.align	2
	.global	VP9_SetImgFormat
	.type	VP9_SetImgFormat, %function
VP9_SetImgFormat:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r6, r0, #0
	beq	.L1580
	add	r3, r6, #311296
	add	r5, r6, #270336
	ldr	r0, [r3, #2860]
	ldr	r1, [r5, #2612]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1580
	ldr	r3, [r6]
	add	r7, r4, #592
	mov	lr, #5
	mov	ip, #1
	mov	r1, #0
	ldrd	r2, [r3, #64]
	strd	r2, [r7, #-8]
	mvn	r2, #0
	ldr	r7, [r6]
	mvn	r3, #0
	strd	r2, [r7, #64]
	ldr	r2, [r5, #2620]
	ldrb	r3, [r4, #64]	@ zero_extendqisi2
	ldrb	r7, [r4, #65]	@ zero_extendqisi2
	bfi	r3, r2, #0, #2
	and	r2, r2, #3
	and	r3, r3, #227
	orr	r7, r7, #12
	bfi	r3, lr, #5, #3
	bfi	r7, ip, #4, #2
	strb	r3, [r4, #64]
	strb	r7, [r4, #65]
	ldr	r3, [r4, #64]
	bfc	r3, #14, #3
	str	r3, [r4, #64]
	mov	ip, r3, lsr #8
	mov	r3, r3, lsr #16
	bfc	ip, #0, #2
	strb	ip, [r4, #65]
	ldrb	ip, [r5, #2628]	@ zero_extendqisi2
	bfi	r3, ip, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r5, #2632]
	str	r2, [r4, #56]
	str	r2, [r4, #60]
	str	r3, [r4, #120]
	bl	SetAspectRatio
	ldr	ip, [r5, #2648]
	str	ip, [r4, #68]
	ldr	r0, [r5, #2652]
	str	r0, [r4, #72]
	ldr	r3, [r6]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1584
	add	r7, r4, #512
	ldr	lr, [r4, #36]
	ldrd	r2, [r7, #-8]
	strd	r2, [fp, #-52]
.L1585:
	ldr	r2, [r5, #2480]
	add	r3, ip, #255
	bic	r3, r3, #255
	add	r1, r0, #63
	add	r8, r3, #3
	cmp	r3, #0
	str	r2, [r4, #124]
	bic	r1, r1, #63
	ldr	r2, [r5, #2488]
	movlt	r3, r8
	mov	r8, ip, lsr #1
	str	r8, [fp, #-56]
	mov	r3, r3, asr #2
	str	r2, [r4, #128]
	ldr	r2, [r5, #2492]
	str	r2, [r4, #132]
	ldr	r2, [r5, #2104]
	str	r2, [r4, #112]
	ldr	r2, [r5, #2112]
	str	r2, [r4, #116]
	ldr	r9, [r6]
	ldr	r2, [r5, #2116]
	ldr	r10, [r9, #932]
	ldrd	r8, [fp, #-52]
	adds	r8, r8, r2
	str	r10, [r4, #168]
	adc	r9, r9, r2, asr #31
	strd	r8, [fp, #-52]
	ldr	r9, [r6]
	add	r6, r2, r2, lsl #1
	add	r2, lr, r2
	add	r6, r6, r6, lsr #31
	ldr	r9, [r9, #932]
	add	r6, lr, r6, asr #1
	str	r9, [r4, #172]
	ldr	lr, [r5, #2508]
	mla	r1, r3, r1, r6
	ldrd	r8, [fp, #-52]
	str	lr, [r4, #136]
	mov	r3, r3, asl #5
	ldr	lr, [r5, #2512]
	str	r2, [r4, #40]
	mov	r2, r0, lsr #1
	mov	r3, r3, lsr #1
	str	lr, [r4, #140]
	strd	r8, [r7]
	str	r0, [r4, #80]
	ldr	r0, [fp, #-56]
	str	r6, [r4, #44]
	str	ip, [r4, #76]
	str	r0, [r4, #84]
	str	r1, [r4, #48]
	str	r3, [r4, #144]
	str	r2, [r4, #88]
.L1580:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1584:
	ldr	r8, [r4, #112]
	add	r1, r0, #15
	ldr	lr, [r4, #36]
	add	r7, r4, #512
	mov	r3, r1, lsr #4
	mov	r1, r8, asl #4
	add	r10, lr, r8
	mul	r1, r3, r1
	add	r9, r1, lr
	str	r9, [r4, #40]
	ldrd	r2, [r7, #-8]
	add	r8, r9, r8
	strd	r2, [fp, #-52]
	adds	r2, r2, r1
	adc	r3, r3, r1, asr #31
	strd	r2, [r7]
	str	r9, [r4, #24]
	str	r8, [r4, #32]
	str	r10, [r4, #28]
	str	lr, [r4, #20]
	b	.L1585
	UNWIND(.fnend)
	.size	VP9_SetImgFormat, .-VP9_SetImgFormat
	.align	2
	.global	VP9DEC_VDMPostProc
	.type	VP9DEC_VDMPostProc, %function
VP9DEC_VDMPostProc:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	subs	r8, r0, #0
	str	r1, [fp, #-56]
	str	r2, [fp, #-48]
	str	r3, [fp, #-60]
	beq	.L1643
	ldr	r3, [fp, #-48]
	add	r9, r8, #270336
	cmp	r3, #0
	add	r3, r8, #274432
	ldrb	r2, [r9, #2089]	@ zero_extendqisi2
	mov	r1, r3
	str	r3, [fp, #-52]
	ldr	r0, [r1, #3680]
	ldr	r3, [r9, #2476]
	ldr	r1, [r1, #3672]
	str	r0, [fp, #-68]
	strb	r2, [r9, #2628]
	str	r1, [fp, #-72]
	str	r3, [r9, #2632]
	bne	.L1644
	add	r7, r8, #311296
	ldr	r3, [r7, #2768]
	cmp	r3, #0
	beq	.L1595
.L1652:
	ldr	r2, [r7, #2808]
	ldr	r3, [r7, #2804]
	cmp	r2, r3
	beq	.L1595
.L1596:
	ldr	r1, [r9, #2612]
	ldr	r0, [r7, #2860]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	str	r3, [fp, #-64]
	beq	.L1614
	movw	r4, #10932
	movw	r5, #11012
	movw	r10, #10968
	movt	r4, 4
	movt	r5, 4
	movt	r10, 4
	add	r4, r8, r4
	add	r5, r8, r5
	add	r6, r9, #2704
	add	r10, r8, r10
	b	.L1599
.L1597:
	clz	r3, r3
	cmp	r0, #0
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L1645
.L1598:
	cmp	r4, r10
	beq	.L1646
.L1599:
	ldr	r3, [r6, #4]!
	ldr	r0, [r4, #4]!
	adds	r2, r3, #0
	ldr	r1, [r5, #4]!
	movne	r2, #1
	cmp	r0, #0
	movne	r2, #0
	cmp	r2, #0
	beq	.L1597
	mov	r2, #1
	ldr	r0, [r7, #2860]
	bl	FSP_SetRef
	cmp	r4, r10
	bne	.L1599
.L1646:
	ldr	r3, .L1656
	movw	r0, #10820
	movt	r0, 4
	add	r0, r8, r0
	add	r1, r0, #80
	mov	r2, #36
	ldr	r3, [r3, #52]
	add	r0, r0, #116
	blx	r3
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	blt	.L1600
	cmp	r3, #100
	movlt	r2, r3
	ldr	r3, [fp, #-64]
	movge	r2, #100
	str	r2, [r3, #152]
	ldr	r3, [r8]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L1647
.L1601:
	mov	r0, r8
	bl	VP9_SetImgFormat
	ldr	r3, [r9, #2564]
	cmp	r3, #2
	beq	.L1648
.L1602:
	ldr	r3, [fp, #-52]
	ldr	r3, [r3, #3616]
	cmp	r3, #0
	bne	.L1604
.L1603:
	mvn	r3, #0
	ldr	r1, [r9, #2612]
	str	r3, [r9, #2616]
	mov	r2, #0
	ldr	r0, [r7, #2860]
	bl	FSP_SetDisplay
	ldr	r1, [r9, #2616]
.L1605:
	cmn	r1, #1
	beq	.L1606
	ldr	r0, [r7, #2860]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1649
	mov	r2, #1
	ldr	r1, [r9, #2616]
	ldr	r0, [r7, #2860]
	bl	FSP_SetDisplay
	movw	r3, #16312
	ldr	r0, [r7, #2860]
	movt	r3, 4
	str	r4, [sp]
	mov	r2, r8
	add	r3, r8, r3
	mov	r1, #17
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r4, r0
	bne	.L1650
.L1606:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1608
	ldr	r1, [fp, #-60]
	ldr	r2, .L1656+4
	mov	r3, r1, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #2
	beq	.L1594
.L1608:
	ldr	r3, [fp, #-52]
	ldr	r4, [r3, #3620]
	cmp	r4, #0
	beq	.L1651
.L1594:
	mov	r4, #0
.L1640:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1645:
	ldr	r0, [r7, #2860]
	bl	FSP_SetRef
	b	.L1598
.L1644:
	ldr	r1, [fp, #-60]
	ldr	r2, .L1656+4
	mov	r3, r1, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L1608
	add	r7, r8, #311296
	ldr	r3, [r7, #2768]
	cmp	r3, #0
	bne	.L1652
.L1595:
	mov	r1, r8
	mov	r0, #17
	bl	ReleasePacket
	mov	r3, #0
	str	r3, [r7, #2768]
	b	.L1596
.L1604:
	ldr	r1, [r9, #2612]
	str	r1, [r9, #2616]
	b	.L1605
.L1651:
	ldr	r0, [r9, #2364]
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L1653
	add	r7, r8, #311296
	ldr	r3, [r7, #2824]
	cmp	r3, #0
	ldr	r3, [r7, #2844]
	bne	.L1654
	cmp	r3, #0
	strne	r4, [fp, #-68]
	bne	.L1612
	ldr	r3, [r7, #2828]
	cmp	r3, #0
	ldr	r3, [fp, #-68]
	movne	r3, #0
	str	r3, [fp, #-68]
.L1611:
	ldr	r3, [r7, #2848]
	cmp	r3, #0
	beq	.L1655
.L1612:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	beq	.L1594
	ldr	r3, [fp, #-68]
	movw	r2, #4708
	add	r1, r8, #278528
	add	r1, r1, #312
	mla	r0, r2, r3, r8
	add	r0, r0, #282624
	add	r0, r0, #924
	bl	memcpy
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1600:
	ldr	r2, [fp, #-64]
	mov	r3, #0
	str	r3, [r2, #152]
	b	.L1601
.L1648:
	ldr	r3, [r9, #2620]
	cmp	r3, #0
	bne	.L1603
	b	.L1602
.L1654:
	cmp	r3, #0
	str	r4, [fp, #-68]
	beq	.L1611
	b	.L1612
.L1650:
	ldr	r1, [r9, #2616]
	mov	r2, #0
	ldr	r0, [r7, #2860]
	bl	FSP_SetDisplay
	ldr	r1, .L1656+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1655:
	ldr	r6, .L1656
	mov	r2, #5120
	ldr	r1, [r9, #2364]
	mov	r0, r5
	add	r9, r8, #282624
	ldr	r3, [r6, #140]
	add	r10, r9, #568
	blx	r3
	add	r0, r8, #278528
	ldr	r3, [r6, #52]
	mov	r2, #4096
	mov	r1, r5
	add	r0, r0, #312
	blx	r3
	ldr	r3, [r6, #52]
	mov	r2, #256
	add	r1, r5, #4096
	add	r0, r9, #312
	blx	r3
	ldr	r3, [r6, #52]
	add	r1, r5, #4352
	mov	r0, r10
	mov	r2, #256
	blx	r3
	ldr	r3, [r7, #2828]
	cmp	r3, #0
	beq	.L1613
	ldr	r3, [r6, #52]
	mov	r1, r10
	add	r0, r9, #828
	mov	r2, #48
	blx	r3
	b	.L1612
.L1647:
	ldr	r1, .L1656+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r9, #2612]
	ldr	r0, [r7, #2860]
	mov	r2, #0
	bl	FSP_SetDisplay
	ldr	r1, [r9, #2612]
	ldr	r0, [r7, #2860]
	mov	r2, #0
	mvn	r4, #0
	bl	FSP_SetRef
	b	.L1640
.L1613:
	ldr	r0, [r7, #2836]
	mov	r1, r10
	ldr	r5, [r6, #52]
	mov	r2, #48
	mov	r3, r0, asl #6
	sub	r0, r3, r0, asl #4
	add	r0, r8, r0
	add	r0, r0, #282624
	add	r0, r0, #828
	blx	r5
	b	.L1612
.L1643:
	movw	r2, #2504
	ldr	r1, .L1656+16
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L1640
.L1649:
	movw	r2, #2597
	ldr	r1, .L1656+20
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L1640
.L1614:
	ldr	r1, .L1656+24
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L1640
.L1653:
	ldr	r1, .L1656+28
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L1640
.L1657:
	.align	2
.L1656:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VdmDrvParam+40
	.word	.LC17
	.word	.LC15
	.word	.LC13
	.word	.LC16
	.word	.LC14
	.word	.LC18
	UNWIND(.fnend)
	.size	VP9DEC_VDMPostProc, .-VP9DEC_VDMPostProc
	.align	2
	.global	VP9DEC_RecycleImage
	.type	VP9DEC_RecycleImage, %function
VP9DEC_RecycleImage:
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
	mov	r5, r1
	beq	.L1661
	add	r4, r4, #311296
	mov	r2, #0
	ldr	r0, [r4, #2860]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #2860]
	bl	FSP_GetFsImagePtr
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1661:
	movw	r2, #2698
	ldr	r1, .L1662
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1663:
	.align	2
.L1662:
	.word	.LC13
	UNWIND(.fnend)
	.size	VP9DEC_RecycleImage, .-VP9DEC_RecycleImage
	.align	2
	.global	VP9DEC_GetRemainImg
	.type	VP9DEC_GetRemainImg, %function
VP9DEC_GetRemainImg:
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
	beq	.L1668
	movw	r0, #16312
	movt	r0, 4
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetVoLastImageID
.L1668:
	movw	r2, #2717
	ldr	r1, .L1669
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1670:
	.align	2
.L1669:
	.word	.LC19
	UNWIND(.fnend)
	.size	VP9DEC_GetRemainImg, .-VP9DEC_GetRemainImg
	.align	2
	.global	VP9DEC_GetImageBuffer
	.type	VP9DEC_GetImageBuffer, %function
VP9DEC_GetImageBuffer:
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
	beq	.L1678
	add	r4, r5, #311296
	ldr	r0, [r4, #2860]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #2860]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L1679
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1679:
	movw	r1, #16312
	ldr	r0, [r4, #2860]
	movt	r1, 4
	add	r1, r5, r1
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1678:
	movw	r2, #2729
	ldr	r1, .L1680
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1681:
	.align	2
.L1680:
	.word	.LC19
	UNWIND(.fnend)
	.size	VP9DEC_GetImageBuffer, .-VP9DEC_GetImageBuffer
	.align	2
	.global	Check_Sync_Code
	.type	Check_Sync_Code, %function
Check_Sync_Code:
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
	mov	r1, #8
	mov	r4, r0
	bl	BsGet
	cmp	r0, #73
	beq	.L1683
.L1684:
	ldr	r1, .L1685
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1683:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	cmp	r0, #131
	bne	.L1684
	mov	r0, r4
	mov	r1, #8
	bl	BsGet
	cmp	r0, #66
	bne	.L1684
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1686:
	.align	2
.L1685:
	.word	.LC20
	UNWIND(.fnend)
	.size	Check_Sync_Code, .-Check_Sync_Code
	.align	2
	.global	Read_Frame_Size
	.type	Read_Frame_Size, %function
Read_Frame_Size:
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
	mov	r5, r1
	mov	r1, #16
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	mov	r1, #16
	add	r3, r0, #1
	mov	r0, r6
	str	r3, [r5]
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Read_Frame_Size, .-Read_Frame_Size
	.align	2
	.global	get_free_fb
	.type	get_free_fb, %function
get_free_fb:
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
	ldr	r0, [r1, #80]
	cmp	r0, #0
	beq	.L1689
	add	r3, r1, #80
	mov	r0, #1
.L1690:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1689
	add	r0, r0, #1
	cmp	r0, #9
	bne	.L1690
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1689:
	add	r3, r0, #20
	mov	r2, #1
	str	r2, [r1, r3, asl #2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	get_free_fb, .-get_free_fb
	.align	2
	.global	Setup_Display_Size
	.type	Setup_Display_Size, %function
Setup_Display_Size:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r3, r1
	ldr	lr, [r3, #52]
	mov	r1, #1
	ldr	ip, [r3, #56]
	mov	r2, #0
	mov	r4, r0
	str	r2, [fp, #-28]
	str	lr, [r3, #60]
	str	ip, [r3, #64]
	str	r2, [fp, #-24]
	bl	BsGet
	cmp	r0, #0
	beq	.L1698
	mov	r0, r4
	sub	r2, fp, #24
	sub	r1, fp, #28
	bl	Read_Frame_Size
.L1698:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	Setup_Display_Size, .-Setup_Display_Size
	.align	2
	.global	VP9_Update_CP_Size
	.type	VP9_Update_CP_Size, %function
VP9_Update_CP_Size:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #4096
	movw	lr, #5304
	ldr	r4, [r3, #1016]
	ldr	ip, [r3, #1020]
	ldr	r5, [r3, #964]
	add	r1, r4, #7
	add	r2, ip, #7
	bic	r1, r1, #7
	bic	r2, r2, #7
	add	r0, r0, r5, lsl #4
	mov	r5, r1, asr #3
	mov	r6, r2, asr #3
	str	r5, [r3, #1056]
	str	r6, [r3, #1060]
	add	r5, r0, lr
	add	r3, r0, #4096
	str	r4, [r0, lr]
	str	ip, [r5, #4]
	str	r1, [r3, #1200]
	str	r2, [r3, #1204]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_Update_CP_Size, .-VP9_Update_CP_Size
	.align	2
	.global	Setup_Frame_Size
	.type	Setup_Frame_Size, %function
Setup_Frame_Size:
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
	add	r4, r1, #4096
	add	r5, r1, #5056
	add	r2, r5, #60
	mov	r6, r1
	ldr	ip, [r4, #1016]
	add	r1, r5, #56
	ldr	r3, [r4, #1020]
	mov	r8, r0
	add	r5, r5, #4
	str	ip, [r4, #1036]
	str	r3, [r4, #1040]
	bl	Read_Frame_Size
	ldr	r3, [r4, #964]
	ldr	lr, [r4, #1020]
	mov	r1, r5
	ldr	r7, [r4, #1016]
	movw	r5, #5304
	add	r6, r6, r3, lsl #4
	add	r3, lr, #7
	add	r2, r7, #7
	bic	r3, r3, #7
	bic	r2, r2, #7
	add	ip, r6, #4096
	mov	r0, r8
	mov	r8, r2, asr #3
	str	r8, [r4, #1056]
	mov	r8, r3, asr #3
	str	r8, [r4, #1060]
	add	r4, r6, r5
	str	r7, [r6, r5]
	str	lr, [r4, #4]
	str	r2, [ip, #1200]
	str	r3, [ip, #1204]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	Setup_Display_Size
	UNWIND(.fnend)
	.size	Setup_Frame_Size, .-Setup_Frame_Size
	.align	2
	.global	setup_frame_size_with_refs
	.type	setup_frame_size_with_refs, %function
setup_frame_size_with_refs:
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
	add	r7, r1, #5056
	mov	r8, r1
	add	r7, r7, #4
	mov	r6, r0
	mov	r4, #0
.L1708:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	bne	.L1713
	add	r4, r4, #1
	cmp	r4, #3
	bne	.L1708
	add	r5, r8, #4096
	add	r2, r7, #56
	add	r1, r7, #52
	mov	r0, r6
	ldr	ip, [r5, #1016]
	ldr	r3, [r5, #1020]
	str	ip, [r5, #1036]
	str	r3, [r5, #1040]
	bl	Read_Frame_Size
	ldr	r10, [r5, #1016]
	ldr	r9, [r5, #1020]
.L1707:
	ldr	r3, [r5, #964]
	add	ip, r10, #7
	add	r2, r9, #7
	bic	ip, ip, #7
	bic	r2, r2, #7
	mov	r1, r7
	add	r3, r8, r3, lsl #4
	mov	r4, ip, asr #3
	add	lr, r3, #5248
	str	r4, [r5, #1056]
	mov	r4, r2, asr #3
	str	r4, [r5, #1060]
	add	r4, r3, #4096
	movw	r7, #5304
	str	r10, [r3, r7]
	mov	r0, r6
	str	r9, [lr, #60]
	str	ip, [r4, #1200]
	str	r2, [r4, #1204]
	sub	sp, fp, #44
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	Setup_Display_Size
.L1713:
	add	r4, r4, #46
	add	r5, r8, #4096
	movw	r1, #5304
	ldr	r3, [r8, r4, asl #2]
	ldr	ip, [r5, #1016]
	ldr	r0, [r5, #1020]
	add	r3, r8, r3, lsl #4
	str	ip, [r5, #1036]
	add	r2, r3, #5248
	str	r0, [r5, #1040]
	ldr	r10, [r3, r1]
	str	r10, [r5, #1016]
	ldr	r9, [r2, #60]
	str	r9, [r5, #1020]
	b	.L1707
	UNWIND(.fnend)
	.size	setup_frame_size_with_refs, .-setup_frame_size_with_refs
	.align	2
	.global	Set_Default_Lf_Deltas
	.type	Set_Default_Lf_Deltas, %function
Set_Default_Lf_Deltas:
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
	mov	r2, #1
	mov	r3, #0
	mvn	r1, #0
	strb	r2, [r0]
	strb	r2, [r0, #1]
	strb	r2, [r0, #2]
	strb	r3, [r0, #3]
	strb	r3, [r0, #6]
	strb	r3, [r0, #7]
	strb	r1, [r0, #4]
	strb	r1, [r0, #5]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Set_Default_Lf_Deltas, .-Set_Default_Lf_Deltas
	.align	2
	.global	VP9_Clearall_Segfeatures
	.type	VP9_Clearall_Segfeatures, %function
VP9_Clearall_Segfeatures:
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
	ldr	r5, .L1716
	mov	r4, r0
	mov	r2, #64
	mov	r1, #0
	add	r0, r0, #16
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r3, [r5, #48]
	add	r0, r4, #80
	mov	r2, #32
	mov	r1, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L1717:
	.align	2
.L1716:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9_Clearall_Segfeatures, .-VP9_Clearall_Segfeatures
	.align	2
	.global	VP9_Setup_Past_Independence
	.type	VP9_Setup_Past_Independence, %function
VP9_Setup_Past_Independence:
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
	ldr	r5, .L1719
	mov	r4, r0
	add	r0, r0, #5248
	mov	r2, #32
	mov	r1, #0
	add	r0, r0, #16
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r5, [r5, #48]
	add	r2, r4, #4096
	mov	r3, #0
	mov	ip, #1
	mvn	lr, #0
	strb	r3, [r2, #1091]
	mov	r1, r3
	strb	r3, [r4, #339]
	add	r0, r4, #64
	strb	r3, [r4, #342]
	mov	r2, #16
	strb	r3, [r4, #343]
	mov	r3, r5
	strb	ip, [r4, #336]
	strb	ip, [r4, #337]
	strb	ip, [r4, #338]
	strb	lr, [r4, #340]
	strb	lr, [r4, #341]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L1720:
	.align	2
.L1719:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9_Setup_Past_Independence, .-VP9_Setup_Past_Independence
	.align	2
	.global	Setup_LoopFilter
	.type	Setup_LoopFilter, %function
Setup_LoopFilter:
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
	mov	r4, r1
	mov	r1, #6
	mov	r5, r0
	bl	BsGet
	mov	r1, #3
	str	r0, [r4, #8]
	mov	r0, r5
	bl	BsGet
	mov	r3, #0
	mov	r1, #1
	strb	r3, [r4, #1]
	str	r0, [r4, #12]
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #1]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r6, r4, #2
	add	r7, r4, #6
.L1725:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1739
.L1724:
	add	r6, r6, #1
	cmp	r6, r7
	bne	.L1725
	add	r4, r4, #8
.L1727:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1740
.L1726:
	add	r7, r7, #1
	cmp	r7, r4
	bne	.L1727
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1739:
	ldr	r2, .L1741
	mov	r1, #6
	mov	r0, r5
	bl	VP9_s_v
	strb	r0, [r6]
	b	.L1724
.L1740:
	ldr	r2, .L1741+4
	mov	r1, #6
	mov	r0, r5
	bl	VP9_s_v
	strb	r0, [r7]
	b	.L1726
.L1742:
	.align	2
.L1741:
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	Setup_LoopFilter, .-Setup_LoopFilter
	.align	2
	.global	Read_Delta_Q
	.type	Read_Delta_Q, %function
Read_Delta_Q:
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
	mov	r4, r1
	mov	r1, #1
	ldr	r5, [r4]
	mov	r6, r0
	bl	BsGet
	cmp	r0, #0
	beq	.L1744
	mov	r0, r6
	ldr	r2, .L1748
	mov	r1, #4
	bl	VP9_s_v
.L1744:
	str	r0, [r4]
	subs	r0, r0, r5
	movne	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1749:
	.align	2
.L1748:
	.word	.LC23
	UNWIND(.fnend)
	.size	Read_Delta_Q, .-Read_Delta_Q
	.align	2
	.global	Setup_Quantization
	.type	Setup_Quantization, %function
Setup_Quantization:
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
	mov	r1, #8
	mov	r5, r0
	bl	BsGet
	add	r1, r4, #244
	str	r0, [r4, #240]
	mov	r0, r5
	bl	Read_Delta_Q
	add	r1, r4, #248
	mov	r0, r5
	bl	Read_Delta_Q
	mov	r0, r5
	add	r1, r4, #252
	bl	Read_Delta_Q
	ldr	r3, [r4, #240]
	cmp	r3, #0
	movne	r3, #0
	bne	.L1751
	ldr	r2, [r4, #244]
	cmp	r2, #0
	bne	.L1751
	ldr	r2, [r4, #248]
	cmp	r2, #0
	ldreq	r3, [r4, #252]
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
.L1751:
	str	r3, [r4, #52]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Setup_Quantization, .-Setup_Quantization
	.align	2
	.global	VP9_Enable_Segfeature
	.type	VP9_Enable_Segfeature, %function
VP9_Enable_Segfeature:
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
	add	r1, r0, r1, lsl #2
	mov	r0, #1
	ldr	r3, [r1, #80]
	orr	r2, r3, r0, asl r2
	str	r2, [r1, #80]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_Enable_Segfeature, .-VP9_Enable_Segfeature
	.align	2
	.global	VP9_Seg_Feature_Data_Max
	.type	VP9_Seg_Feature_Data_Max, %function
VP9_Seg_Feature_Data_Max:
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
	ldr	r3, .L1756
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #556]
	ldmfd	sp, {fp, sp, pc}
.L1757:
	.align	2
.L1756:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VP9_Seg_Feature_Data_Max, .-VP9_Seg_Feature_Data_Max
	.align	2
	.global	Get_Unsigned_Bits
	.type	Get_Unsigned_Bits, %function
Get_Unsigned_Bits:
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
	cmp	r0, #1
	bls	.L1762
	subs	r3, r0, #1
	beq	.L1763
	mov	r0, #0
.L1761:
	movs	r3, r3, lsr #1
	add	r0, r0, #1
	bne	.L1761
	ldmfd	sp, {fp, sp, pc}
.L1762:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1763:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Get_Unsigned_Bits, .-Get_Unsigned_Bits
	.align	2
	.global	Decode_Unsigned_Max
	.type	Decode_Unsigned_Max, %function
Decode_Unsigned_Max:
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
	cmp	r1, #1
	mov	r4, r1
	movls	r1, #0
	bls	.L1766
	subs	r3, r4, #1
	beq	.L1770
	mov	r1, #0
.L1768:
	movs	r3, r3, lsr #1
	add	r1, r1, #1
	bne	.L1768
.L1766:
	bl	BsGet
	cmp	r0, r4
	movge	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1770:
	mov	r1, r3
	b	.L1766
	UNWIND(.fnend)
	.size	Decode_Unsigned_Max, .-Decode_Unsigned_Max
	.align	2
	.global	VP9_Is_Segfeature_Signed
	.type	VP9_Is_Segfeature_Signed, %function
VP9_Is_Segfeature_Signed:
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
	ldr	r3, .L1773
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #572]
	ldmfd	sp, {fp, sp, pc}
.L1774:
	.align	2
.L1773:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VP9_Is_Segfeature_Signed, .-VP9_Is_Segfeature_Signed
	.align	2
	.global	VP9_Set_Segdata
	.type	VP9_Set_Segdata, %function
VP9_Set_Segdata:
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
	ldr	r7, .L1784
	mov	r10, r2, asl #2
	mov	r5, r3
	mov	r4, r2
	add	r3, r7, r10
	mov	r6, r0
	mov	r9, r1
	ldr	r8, [r3, #556]
	cmp	r8, r5
	blt	.L1781
.L1776:
	cmp	r5, #0
	blt	.L1782
.L1778:
	add	r4, r4, r9, lsl #2
	add	r4, r6, r4, lsl #1
	strh	r5, [r4, #16]	@ movhi
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1782:
	add	r7, r7, r10
	ldr	r0, [r7, #572]
	cmp	r0, #0
	beq	.L1783
.L1779:
	rsb	r3, r5, #0
	cmp	r8, r3
	bge	.L1778
	movw	r3, #3010
	ldr	r2, .L1784+4
	ldr	r1, .L1784+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1778
.L1781:
	movw	r3, #2998
	add	r2, r7, #588
	ldr	r1, .L1784+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1776
.L1783:
	movw	r3, #3005
	ldr	r2, .L1784+4
	ldr	r1, .L1784+8
	bl	dprint_vfmw
	b	.L1779
.L1785:
	.align	2
.L1784:
	.word	.LANCHOR0
	.word	.LANCHOR0+588
	.word	.LC24
	UNWIND(.fnend)
	.size	VP9_Set_Segdata, .-VP9_Set_Segdata
	.align	2
	.global	Mi_Cols_Aligned_To_Sb
	.type	Mi_Cols_Aligned_To_Sb, %function
Mi_Cols_Aligned_To_Sb:
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
	add	r0, r0, #7
	bic	r0, r0, #7
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mi_Cols_Aligned_To_Sb, .-Mi_Cols_Aligned_To_Sb
	.align	2
	.global	To_Sbs
	.type	To_Sbs, %function
To_Sbs:
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
	add	r0, r0, #7
	mov	r0, r0, asr #3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	To_Sbs, .-To_Sbs
	.align	2
	.global	VP9_Get_Tile_N_Bits
	.type	VP9_Get_Tile_N_Bits, %function
VP9_Get_Tile_N_Bits:
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
	add	r0, r0, #7
	mov	r3, #0
	mov	r0, r0, asr #3
	cmp	r0, #3
	ble	.L1789
.L1790:
	add	r3, r3, #1
	mov	ip, r0, asr r3
	cmp	ip, #3
	bgt	.L1790
	sub	r3, r3, #1
	bic	r3, r3, r3, asr #31
.L1789:
	cmp	r0, #64
	mov	ip, #0
	ble	.L1791
	mov	lr, #64
.L1792:
	add	ip, ip, #1
	cmp	r0, lr, asl ip
	bgt	.L1792
.L1791:
	str	ip, [r1]
	str	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_Get_Tile_N_Bits, .-VP9_Get_Tile_N_Bits
	.align	2
	.global	Setup_Tile_Info
	.type	Setup_Tile_Info, %function
Setup_Tile_Info:
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
	ldr	r2, [r1, #92]
	mov	r6, r1
	mov	r5, r0
	add	r2, r2, #7
	mov	r2, r2, asr #3
	cmp	r2, #3
	ble	.L1798
	mov	r4, #0
	b	.L1799
.L1810:
	mov	r4, r3
.L1799:
	add	r3, r4, #1
	mov	r1, r2, asr r3
	cmp	r1, #3
	bgt	.L1810
	cmp	r2, #64
	bic	r4, r4, r4, asr #31
	ble	.L1821
.L1808:
	mov	r3, #0
	mov	r1, #64
.L1801:
	add	r3, r3, #1
	cmp	r2, r1, asl r3
	bgt	.L1801
.L1800:
	subs	r4, r4, r3
	str	r3, [r6, #100]
	bne	.L1804
	b	.L1803
.L1806:
	ldr	r3, [r6, #100]
	subs	r4, r4, #1
	add	r3, r3, #1
	str	r3, [r6, #100]
	beq	.L1803
.L1804:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1806
.L1803:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r6, #104]
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r5
	mov	r1, #1
	bl	BsGet
	ldr	r3, [r6, #104]
	add	r0, r3, r0
	str	r0, [r6, #104]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1798:
	cmp	r2, #64
	movgt	r4, #0
	bgt	.L1808
	mov	r3, #0
	str	r3, [r6, #100]
	b	.L1803
.L1821:
	mov	r3, #0
	b	.L1800
	UNWIND(.fnend)
	.size	Setup_Tile_Info, .-Setup_Tile_Info
	.align	2
	.global	Setup_Segmentation
	.type	Setup_Segmentation, %function
Setup_Segmentation:
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
	mov	r5, r1
	mov	r3, #0
	mov	r1, #1
	strb	r3, [r5, #1]
	mov	r6, r0
	strb	r3, [r5, #2]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	bne	.L1859
.L1823:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1859:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L1826
	add	r4, r5, #4
	add	r7, r5, #11
	b	.L1828
.L1827:
	strb	r3, [r4, #1]!
	cmp	r4, r7
	beq	.L1860
.L1828:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #255
	cmp	r0, #0
	beq	.L1827
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #1]!
	cmp	r4, r7
	bne	.L1828
.L1860:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #4]
	cmp	r0, #0
	addne	r4, r5, #14
	bne	.L1831
	mvn	r3, #0
	strb	r3, [r5, #12]
	strb	r3, [r5, #13]
	strb	r3, [r5, #14]
.L1826:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #2]
	cmp	r0, #0
	beq	.L1823
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	add	r8, r5, #80
	mov	r7, #0
	ldr	r10, .L1863
	strb	r0, [r5, #3]
	mov	r0, r5
	bl	VP9_Clearall_Segfeatures
.L1833:
	mov	r4, #0
	mov	r9, #1
.L1836:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	moveq	r3, r0
	bne	.L1861
.L1835:
	mov	r2, r4
	mov	r1, r7
	add	r4, r4, #1
	mov	r0, r5
	bl	VP9_Set_Segdata
	cmp	r4, #4
	bne	.L1836
	add	r7, r7, #1
	add	r8, r8, #4
	cmp	r7, #8
	bne	.L1833
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1861:
	ldr	r3, [r8]
	mov	r0, r6
	ldr	r1, [r10, r4, asl #2]
	orr	r3, r3, r9, asl r4
	str	r3, [r8]
	bl	Decode_Unsigned_Max
	ldr	r2, .L1863+4
	ldr	r2, [r2, r4, asl #2]
	cmp	r2, #0
	mov	r3, r0
	beq	.L1835
	str	r0, [fp, #-48]
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldr	r3, [fp, #-48]
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r2, r0, #0
	eor	r3, r3, r2
	add	r3, r3, r0
	b	.L1835
.L1831:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #255
	cmp	r0, #0
	bne	.L1862
.L1830:
	strb	r3, [r7, #1]!
	cmp	r7, r4
	bne	.L1831
	b	.L1826
.L1862:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	uxtb	r3, r0
	b	.L1830
.L1864:
	.align	2
.L1863:
	.word	.LANCHOR0+556
	.word	.LANCHOR0+572
	UNWIND(.fnend)
	.size	Setup_Segmentation, .-Setup_Segmentation
	.align	2
	.global	read_interp_filter_type
	.type	read_interp_filter_type, %function
read_interp_filter_type:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r3, .L1869
	mov	r4, r0
	sub	ip, fp, #20
	ldmia	r3, {r0, r1, r2, r3}
	stmdb	ip, {r0, r1, r2, r3}
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	cmp	r0, #0
	movne	r0, #4
	beq	.L1868
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1868:
	mov	r0, r4
	mov	r1, #2
	bl	BsGet
	sub	r3, fp, #20
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #-16]
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1870:
	.align	2
.L1869:
	.word	.LANCHOR0+604
	UNWIND(.fnend)
	.size	read_interp_filter_type, .-read_interp_filter_type
	.align	2
	.global	setup_inter_inter
	.type	setup_inter_inter, %function
setup_inter_inter:
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
	ldr	r3, [r0, #68]
	ldr	r1, [r0, #76]
	ldr	r2, [r0, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r0, #60]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	setup_inter_inter, .-setup_inter_inter
	.align	2
	.global	ref_cnt_fb
	.type	ref_cnt_fb, %function
ref_cnt_fb:
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
	ldr	ip, [r1]
	ldr	r3, [r0, ip, asl #2]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r0, ip, asl #2]
	str	r2, [r1]
	ldr	r3, [r0, r2, asl #2]
	add	r3, r3, #1
	str	r3, [r0, r2, asl #2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	ref_cnt_fb, .-ref_cnt_fb
	.global	__aeabi_idiv
	.align	2
	.global	VP9_get_fixed_point_scale_factor
	.type	VP9_get_fixed_point_scale_factor, %function
VP9_get_fixed_point_scale_factor:
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
	subs	r3, r1, #0
	beq	.L1877
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
.L1876:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1877:
	str	r3, [sp]
	mov	r0, #1
	movw	r3, #3203
	ldr	r2, .L1878
	ldr	r1, .L1878+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1876
.L1879:
	.align	2
.L1878:
	.word	.LANCHOR0+620
	.word	.LC25
	UNWIND(.fnend)
	.size	VP9_get_fixed_point_scale_factor, .-VP9_get_fixed_point_scale_factor
	.align	2
	.global	check_scale_factors
	.type	check_scale_factors, %function
check_scale_factors:
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
	cmp	r0, r2, asl #1
	bgt	.L1884
	cmp	r1, r3, asl #1
	bgt	.L1884
	cmp	r2, r0, asl #4
	bgt	.L1884
	cmp	r3, r1, asl #4
	movle	r0, #1
	movgt	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1884:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	check_scale_factors, .-check_scale_factors
	.align	2
	.global	VP9_scaled_val
	.type	VP9_scaled_val, %function
VP9_scaled_val:
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
	smull	r2, r3, r0, r1
	mov	r0, r2, lsr #14
	orr	r0, r0, r3, asl #18
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VP9_scaled_val, .-VP9_scaled_val
	.align	2
	.global	vp9_setup_scale_factors
	.type	vp9_setup_scale_factors, %function
vp9_setup_scale_factors:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
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
	cmp	r1, r3, asl #1
	mov	ip, r1
	mov	r4, r0
	mov	r7, r2
	ldr	r6, [fp, #4]
	bgt	.L1887
	cmp	r2, r6, asl #1
	ble	.L1897
.L1887:
	mvn	r2, #0
	mov	r3, #16
	str	r2, [r4]
	stmib	r4, {r2, r3}
	str	r3, [r4, #12]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1897:
	cmp	r3, r1, asl #4
	bgt	.L1887
	cmp	r6, r2, asl #4
	bgt	.L1887
	cmp	r3, #0
	beq	.L1898
	mov	r1, r3
	mov	r0, ip, asl #14
	bl	__aeabi_idiv
	cmp	r6, #0
	mov	r5, r0
	str	r5, [r4]
	beq	.L1899
.L1890:
	mov	r1, r6
	mov	r0, r7, asl #14
	bl	__aeabi_idiv
	mov	r7, r0, asr #31
	ubfx	r3, r0, #10, #18
	mov	r1, r7, asl #4
	orr	r1, r1, r0, lsr #28
	orr	r1, r3, r1, asl #18
.L1891:
	mov	r7, r5, asr #31
	ubfx	r3, r5, #10, #18
	str	r0, [r4, #4]
	mov	r2, r7, asl #4
	str	r1, [r4, #12]
	orr	r2, r2, r5, lsr #28
	orr	r3, r3, r2, asl #18
	str	r3, [r4, #8]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1898:
	str	r3, [sp]
	mov	r0, #1
	movw	r3, #3203
	ldr	r2, .L1900
	ldr	r1, .L1900+4
	mvn	r5, #0
	bl	dprint_vfmw
	cmp	r6, #0
	str	r5, [r4]
	bne	.L1890
.L1899:
	ldr	r1, .L1900+4
	movw	r3, #3203
	str	r6, [sp]
	mov	r0, #1
	ldr	r2, .L1900
	bl	dprint_vfmw
	mvn	r1, #0
	mov	r0, r1
	ldr	r5, [r4]
	b	.L1891
.L1901:
	.align	2
.L1900:
	.word	.LANCHOR0+620
	.word	.LC25
	UNWIND(.fnend)
	.size	vp9_setup_scale_factors, .-vp9_setup_scale_factors
	.align	2
	.global	Vp9_Vfmw_ReadProfile
	.type	Vp9_Vfmw_ReadProfile, %function
Vp9_Vfmw_ReadProfile:
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
	bl	BsGet
	mov	r1, #1
	mov	r4, r0
	mov	r0, r5
	bl	BsGet
	orr	r4, r4, r0, asl #1
	cmp	r4, #2
	ble	.L1903
	mov	r0, r5
	mov	r1, #1
	bl	BsGet
	add	r4, r0, r4
.L1903:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_ReadProfile, .-Vp9_Vfmw_ReadProfile
	.align	2
	.global	Vp9_ReadBitDepthColorSpaceSampling
	.type	Vp9_ReadBitDepthColorSpaceSampling, %function
Vp9_ReadBitDepthColorSpaceSampling:
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
	add	r4, r1, #4096
	mov	r2, #8
	mov	r5, r0
	ldr	r3, [r4, #976]
	str	r2, [r4, #1032]
	cmp	r3, #1
	bls	.L1905
	mov	r1, #1
	bl	BsGet
	cmp	r0, #0
	movne	r3, #12
	moveq	r3, #10
	str	r3, [r4, #1032]
.L1905:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	cmp	r0, #7
	str	r0, [r4, #980]
	beq	.L1907
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldr	r6, [r4, #976]
	bic	r6, r6, #2
	cmp	r6, #1
	movne	r3, #1
	str	r0, [r4, #984]
	strne	r3, [r4, #1012]
	strne	r3, [r4, #1008]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #1008]
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #1012]
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
.L1907:
	ldr	r1, [r4, #976]
	bic	r1, r1, #2
	cmp	r1, #1
	beq	.L1913
	movw	r3, #3306
	ldr	r2, .L1914
	ldr	r1, .L1914+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1913:
	mov	r3, #0
	mov	r0, r5
	str	r3, [r4, #1012]
	str	r3, [r4, #1008]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
.L1915:
	.align	2
.L1914:
	.word	.LANCHOR0+656
	.word	.LC26
	UNWIND(.fnend)
	.size	Vp9_ReadBitDepthColorSpaceSampling, .-Vp9_ReadBitDepthColorSpaceSampling
	.align	2
	.global	Vp9_ReadCompressedHeader
	.type	Vp9_ReadCompressedHeader, %function
Vp9_ReadCompressedHeader:
	UNWIND(.fnstart)
	@ args = 24, pretend = 0, frame = 8
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
	ldr	ip, [fp, #16]
	mov	r4, #0
	mov	r6, r1
	cmp	ip, #0
	mov	r7, r2
	mov	r8, r3
	mov	r5, r0
	str	r4, [fp, #-48]
	ldr	r10, [fp, #8]
	ldr	r9, [fp, #12]
	beq	.L1921
.L1917:
	mov	r2, r5
	mov	r1, r4
	mov	r0, r6
	bl	Vp9_ReadCoefProbs
	ldr	r2, [fp, #4]
	mov	r0, r6
	mov	r3, r8
	sub	ip, fp, #48
	stmib	sp, {r9, r10}
	str	r2, [sp]
	mov	r1, r5
	mov	r2, r7
	str	ip, [sp, #12]
	bl	Vp9_PrepareReadModeInfo
	ldr	r3, [r5, #32]
	sub	r3, r3, #33
	cmn	r3, #-1073741790
	ldrhi	r3, [fp, #-48]
	movhi	r0, #0
	ldrhi	r2, [fp, #20]
	mvnls	r0, #0
	strhi	r3, [r2]
	ldrhi	r3, [fp, #24]
	strhi	r4, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1921:
	bl	Vp9_ReadTxMode
	cmp	r0, #4
	mov	r4, r0
	bne	.L1917
	add	r0, r6, #4352
	mov	r1, r5
	add	r0, r0, #51
	bl	Vp9_ReadTxProbs
	b	.L1917
	UNWIND(.fnend)
	.size	Vp9_ReadCompressedHeader, .-Vp9_ReadCompressedHeader
	.align	2
	.global	Read_UnCompressed_Header
	.type	Read_UnCompressed_Header, %function
Read_UnCompressed_Header:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r4, r1, #4096
	mov	r6, r1
	mov	r1, #2
	ldr	r3, [r4, #972]
	mov	r5, r0
	str	r3, [r4, #968]
	bl	BsGet
	cmp	r0, #2
	beq	.L1923
	ldr	r1, .L1957
	mov	r0, #1
	bl	dprint_vfmw
.L1923:
	mov	r0, r5
	bl	Vp9_Vfmw_ReadProfile
	mov	r1, #1
	str	r0, [r4, #976]
	mov	r0, r5
	bl	BsGet
	subs	r7, r0, #0
	bne	.L1953
	mov	r1, #1
	str	r7, [r4, #992]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #972]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #988]
	mov	r0, r5
	bl	BsGet
	ldr	r2, [r4, #972]
	cmp	r2, #0
	mov	r3, r0
	str	r0, [r4, #1004]
	beq	.L1954
	ldr	r2, [r4, #988]
	cmp	r2, #0
	strne	r7, [r4, #1072]
	beq	.L1955
.L1929:
	cmp	r3, #0
	beq	.L1930
	mov	r3, #0
	str	r3, [r4, #1076]
.L1931:
	ldr	r3, [r4, #1072]
	cmp	r3, #0
	beq	.L1932
	mov	r0, r5
	bl	Check_Sync_Code
	ldr	r3, [r4, #976]
	cmp	r3, #1
	bls	.L1933
	mov	r1, r6
	mov	r0, r5
	bl	Vp9_ReadBitDepthColorSpaceSampling
.L1934:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #1080]
	mov	r0, r5
	bl	Setup_Frame_Size
	b	.L1927
.L1953:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r3, #0
	mov	r7, r3
	mov	r2, #1
	add	r0, r0, #38
	ldr	r1, [r6, r0, asl #2]
	str	r3, [r4, #1080]
	str	r2, [r4, #992]
	str	r1, [r4, #996]
	str	r3, [r6, #344]
	str	r2, [r4, #988]
.L1925:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1932:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	add	r8, r6, #180
	add	r10, r6, #192
	mov	r9, r8
	str	r0, [r4, #1080]
.L1935:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	add	r3, r0, #38
	mov	r0, r5
	ldr	r3, [r6, r3, asl #2]
	str	r3, [r9, #4]!
	bl	BsGet
	cmp	r9, r10
	str	r0, [r9, #-116]
	bne	.L1935
	mov	r1, r6
	mov	r0, r5
	bl	setup_frame_size_with_refs
	ldr	r2, [r4, #1016]
	sub	r3, r2, #1
	cmp	r3, #4096
	ldr	r3, [r4, #1020]
	bcs	.L1937
	sub	r1, r3, #1
	cmp	r1, #4096
	bcs	.L1937
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	add	r9, r6, #5440
	str	r0, [r6, #56]
	mov	r0, r5
	bl	read_interp_filter_type
	str	r0, [r4, #1084]
.L1939:
	ldr	r2, [r8, #4]!
	mov	r0, r9
	ldr	ip, [r4, #1020]
	add	r9, r9, #16
	add	r2, r2, #328
	ldr	r3, [r4, #1016]
	add	r2, r2, #3
	str	ip, [sp]
	add	r1, r6, r2, lsl #4
	ldr	r2, [r1, #12]
	ldr	r1, [r1, #8]
	bl	vp9_setup_scale_factors
	cmp	r10, r8
	bne	.L1939
	ldr	r3, [r6, #68]
	ldr	r1, [r6, #76]
	ldr	r2, [r6, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r6, #60]
	b	.L1927
.L1954:
	mov	r0, r5
	bl	Check_Sync_Code
	mov	r1, r6
	mov	r0, r5
	bl	Vp9_ReadBitDepthColorSpaceSampling
	ldr	r3, [r4, #964]
	mov	r2, #255
	mov	r1, r6
	str	r2, [r4, #1080]
	mov	r0, r5
	str	r3, [r6, #184]
	str	r3, [r6, #188]
	str	r3, [r6, #192]
	bl	Setup_Frame_Size
.L1927:
	ldr	r3, [r4, #1004]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r4, #1044]
	strne	r3, [r4, #1048]
	beq	.L1956
.L1941:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #972]
	cmp	r3, #0
	str	r0, [r4, #1052]
	beq	.L1942
	ldr	r3, [r4, #1004]
	cmp	r3, #0
	bne	.L1942
	ldr	r3, [r4, #1072]
	cmp	r3, #0
	bne	.L1942
.L1944:
	ldr	r3, [r6, #68]
	ldr	r1, [r6, #76]
	ldr	r2, [r6, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r6, #60]
.L1943:
	add	r1, r6, #336
	mov	r0, r5
	bl	Setup_LoopFilter
	mov	r1, r6
	mov	r0, r5
	bl	Setup_Quantization
	add	r1, r6, #5184
	mov	r0, r5
	bl	Setup_Segmentation
	add	r1, r6, #5056
	mov	r0, r5
	add	r1, r1, #4
	bl	Setup_Tile_Info
	mov	r0, r5
	mov	r1, #16
	bl	BsGet
	str	r0, [r6, #8]
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1933:
	mov	r3, #1
	mov	r2, #8
	str	r3, [r4, #1008]
	str	r2, [r4, #1032]
	str	r3, [r4, #1012]
	str	r3, [r4, #980]
	b	.L1934
.L1942:
	mov	r0, r6
	bl	VP9_Setup_Past_Independence
	ldr	r3, [r4, #972]
	cmp	r3, #0
	beq	.L1943
	b	.L1944
.L1956:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #1044]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1048]
	b	.L1941
.L1930:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1076]
	b	.L1931
.L1955:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #1004]
	str	r0, [r4, #1072]
	b	.L1929
.L1937:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	movw	r3, #3459
	ldr	r2, .L1957+4
	mvn	r7, #0
	ldr	r1, .L1957+8
	bl	dprint_vfmw
	b	.L1925
.L1958:
	.align	2
.L1957:
	.word	.LC27
	.word	.LANCHOR0+692
	.word	.LC28
	UNWIND(.fnend)
	.size	Read_UnCompressed_Header, .-Read_UnCompressed_Header
	.align	2
	.global	swap_frame_buffers
	.type	swap_frame_buffers, %function
swap_frame_buffers:
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
	add	r5, r0, #4096
	ldr	r3, [r5, #1080]
	cmp	r3, #0
	addne	r2, r0, #152
	addne	lr, r0, #80
	beq	.L1964
.L1963:
	tst	r3, #1
	beq	.L1961
	ldr	r4, [r2]
	ldr	ip, [r5, #964]
	ldr	r1, [lr, r4, asl #2]
	cmp	r1, #0
	sub	r1, r1, #1
	strgt	r1, [lr, r4, asl #2]
	str	ip, [r2]
	ldr	r1, [lr, ip, asl #2]
	add	r1, r1, #1
	str	r1, [lr, ip, asl #2]
.L1961:
	movs	r3, r3, asr #1
	add	r2, r2, #4
	bne	.L1963
.L1964:
	ldr	r3, [r5, #964]
	mvn	r2, #-2147483648
	add	r3, r0, r3, lsl #2
	ldr	r1, [r3, #80]
	sub	r1, r1, #1
	str	r1, [r3, #80]
	str	r2, [r0, #184]
	str	r2, [r0, #188]
	str	r2, [r0, #192]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	swap_frame_buffers, .-swap_frame_buffers
	.align	2
	.global	VP9_Set_DecParam
	.type	VP9_Set_DecParam, %function
VP9_Set_DecParam:
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
	add	r7, r0, #274432
	mov	r5, r0
	add	r4, r0, #270336
	ldr	r6, [r7, #3620]
	cmp	r6, #1
	beq	.L2005
	add	r8, r0, #262144
	mov	r3, #0
	strb	r3, [r8, #1036]
	ldr	r2, [r7, #3600]
	ldr	ip, [r4, #2624]
	ldr	r0, [r4, #2640]
	ldr	r1, [r4, #2644]
	ldr	r3, [r4, #2556]
	str	ip, [r4, #2124]
	str	r1, [r4, #2100]
	bic	r3, r3, #15
	str	r2, [r4, #2620]
	str	r3, [r4, #2136]
	str	r2, [r4, #2120]
	str	r0, [r4, #2096]
	ldr	r3, [r5]
	ldr	r1, [r4, #2820]
	ldr	ip, [r4, #2580]
	ldr	r0, [r3, #600]
	cmp	r1, #8
	addgt	r6, r5, #311296
	addle	r1, r4, r1, lsl #2
	addle	r6, r5, #311296
	str	r0, [r4, #2476]
	ldr	r0, [r3, #604]
	str	r0, [r4, #2480]
	ldr	r0, [r3, #608]
	str	r0, [r4, #2488]
	ldr	lr, [r3, #612]
	ldr	r0, [r4, #2592]
	str	lr, [r4, #2492]
	ldr	r3, [r3, #652]
	str	ip, [r4, #2468]
	str	r0, [r4, #2472]
	str	r3, [r4, #2496]
	ldrgt	r3, [r6, #2760]
	ldrle	r3, [r1, #2824]
	addgt	r3, r4, r3, lsl #2
	ldrgt	r3, [r3, #2824]
	str	r3, [r4, #2604]
	ldr	r3, [r4, #2816]
	cmp	r3, #8
	ldrgt	r3, [r6, #2760]
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #2824]
	str	r3, [r4, #2600]
	ldr	r3, [r4, #2812]
	cmp	r3, #8
	ldrgt	r3, [r6, #2760]
	cmp	r2, #0
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #2824]
	str	r3, [r4, #2608]
	bne	.L2006
.L1983:
	ldr	r1, [r4, #2612]
	str	r1, [r4, #2604]
	str	r1, [r4, #2600]
	str	r1, [r4, #2608]
.L1984:
	ldr	r0, [r6, #2860]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2604]
	mov	r7, r0
	ldr	r0, [r6, #2860]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2600]
	mov	r10, r0
	ldr	r0, [r6, #2860]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2608]
	mov	r9, r0
	ldr	r0, [r6, #2860]
	bl	FSP_GetLogicFs
	cmp	r9, #0
	cmpne	r7, #0
	beq	.L1985
	cmp	r0, #0
	cmpne	r10, #0
	beq	.L1985
	ldr	r3, [r7, #28]
	cmp	r3, #0
	beq	.L2007
	ldr	r3, [r7, #8]
	add	r2, r5, #8
	str	r3, [r4, #2464]
	ldr	r3, [r7, #28]
	ldr	r3, [r3, #20]
	str	r3, [r4, #2504]
	ldr	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #2448]
	ldr	r3, [r10, #28]
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #2452]
	ldr	r3, [r9, #28]
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #2456]
	ldr	r3, [r0, #28]
	mov	r0, #0
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #2460]
	ldr	r3, [r6, #2868]
	str	r3, [r6, #2864]
	str	r3, [r8, #1032]
	str	r2, [r5, #4]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2006:
	ldr	r3, [r7, #3700]
	cmp	r3, #1
	beq	.L1983
	ldr	r1, [r4, #2612]
	b	.L1984
.L2005:
	add	r3, r0, #262144
	add	r8, r0, #311296
	strb	r6, [r3, #1036]
	ldr	r3, [r0]
	ldr	r1, [r4, #2612]
	ldr	r2, [r3, #600]
	str	r2, [r4, #2476]
	ldr	r3, [r3, #652]
	str	r3, [r4, #2496]
	ldr	r0, [r8, #2860]
	bl	FSP_GetLogicFs
	ldr	r3, [r7, #3624]
	add	r3, r4, r3, lsl #2
	ldr	r1, [r3, #2824]
	mov	r9, r0
	ldr	r0, [r8, #2860]
	bl	FSP_GetLogicFs
	ldr	r3, [r7, #3624]
	add	r3, r4, r3, lsl #2
	ldr	r1, [r3, #2824]
	mov	r10, r0
	ldr	r0, [r8, #2860]
	bl	FSP_GetFsImagePtr
	cmp	r9, #0
	cmpne	r10, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r2, r0
	cmp	r3, #0
	bne	.L1985
	ldr	r3, [r9, #28]
	cmp	r3, #0
	beq	.L2008
	ldr	r3, [r3, #8]
	mov	r1, #0
	mov	r0, r1
	str	r3, [r4, #2448]
	ldr	r3, [r10, #28]
	cmp	r3, #0
	ldreq	r3, [r9, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #2456]
	ldr	r3, [r9, #28]
	ldr	r3, [r3, #20]
	str	r3, [r4, #2504]
	ldr	r3, [r2, #68]
	add	r3, r3, #63
	mov	r3, r3, lsr #6
	str	r3, [r4, #2096]
	ldr	r3, [r2, #72]
	add	r3, r3, #63
	mov	r3, r3, lsr #6
	str	r3, [r4, #2100]
	str	r1, [r5, #4]
	ldr	r3, [r2, #68]
	str	r3, [r4, #2648]
	ldr	r3, [r2, #72]
	str	r3, [r4, #2652]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1985:
	ldr	r1, .L2009
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2007:
	ldr	r1, .L2009+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2008:
	mov	r0, r6
	ldr	r1, .L2009+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2010:
	.align	2
.L2009:
	.word	.LC29
	.word	.LC31
	.word	.LC30
	UNWIND(.fnend)
	.size	VP9_Set_DecParam, .-VP9_Set_DecParam
	.align	2
	.global	VP9_ArrangeVHBMem
	.type	VP9_ArrangeVHBMem, %function
VP9_ArrangeVHBMem:
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
	add	r4, r0, #270336
	mov	r5, r0
	ldr	r3, [r4, #2652]
	ldr	r2, [r4, #2648]
	cmp	r3, #31
	bls	.L2013
	sub	r0, r2, #32
	movw	r1, #8160
	cmp	r3, #8192
	cmpls	r0, r1
	bls	.L2014
.L2013:
	ldr	r1, .L2045
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L2015:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2014:
	ldr	r1, .L2045+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r0, [r3, #732]
	ldr	r2, [r3, #28]
	cmp	r0, #0
	bne	.L2016
	cmp	r2, #25
	beq	.L2042
.L2029:
	mov	r7, #5
.L2017:
	ldr	r3, [r4, #2568]
	add	r6, r5, #311296
	cmp	r3, #0
	bne	.L2022
	ldr	r0, [r6, #2860]
	mov	r1, r3
	ldr	r2, .L2045+8
	ldr	ip, .L2045+12
	ldr	r8, [ip, #48]
	ldr	ip, [r2, r0, asl #2]
	mov	r2, #20
	sub	r0, fp, #64
	add	ip, ip, #471040
	str	r3, [ip, #1224]
	blx	r8
	ldr	ip, [r4, #2648]
	ldr	r2, [r4, #2652]
	sub	r1, fp, #64
	ldr	r0, [r6, #2860]
	mov	r3, #1
	strb	r7, [fp, #-62]
	str	ip, [fp, #-60]
	str	ip, [fp, #-52]
	str	r2, [fp, #-56]
	str	r2, [fp, #-48]
	strb	r3, [fp, #-63]
	strb	r3, [fp, #-61]
	bl	FSP_ConfigInstance
	subs	r7, r0, #0
	beq	.L2043
.L2023:
	ldr	r1, .L2045+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2015
.L2016:
	cmp	r2, #25
	bne	.L2029
	ldr	r2, [r4, #2648]
	ldr	ip, [r3, #692]
	cmp	r2, ip
	bhi	.L2041
	ldr	r0, [r4, #2652]
	ldr	r1, [r3, #696]
	cmp	r0, r1
	bls	.L2021
.L2020:
	ldr	r3, [r4, #2652]
	mov	r0, #0
	str	r1, [sp, #4]
	str	ip, [sp]
	ldr	r1, .L2045+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2015
.L2022:
	ldr	r3, [r6, #2860]
	mov	r7, #1
	ldr	r8, .L2045+8
	mov	r1, #0
	ldr	r2, .L2045+12
	sub	r0, fp, #64
	ldr	r9, [r6, #2732]
	ldr	r3, [r8, r3, asl #2]
	ldr	r10, [r2, #48]
	mov	r2, #20
	add	r3, r3, #471040
	str	r7, [r3, #1224]
	blx	r10
	ldr	r1, [r5]
	ldr	r3, [r4, #2652]
	ldr	r2, [r4, #2648]
	ldr	r1, [r1, #28]
	ldr	r0, [r6, #2860]
	cmp	r1, #24
	sub	r1, fp, #64
	uxtbne	r7, r9
	str	r3, [fp, #-56]
	str	r3, [fp, #-48]
	mov	r3, #0
	str	r2, [fp, #-60]
	str	r2, [fp, #-52]
	strb	r7, [fp, #-63]
	strb	r3, [fp, #-62]
	strb	r3, [fp, #-61]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L2023
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r6, #2860]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	bne	.L2044
.L2026:
	ldr	r3, [r6, #2860]
	mov	r2, #0
	ldr	r3, [r8, r3, asl #2]
	str	r2, [r3, #1496]
.L2024:
	mov	r3, #1
	mov	r0, #0
	str	r3, [r4, #2568]
	b	.L2015
.L2041:
	ldr	r1, [r3, #696]
	b	.L2020
.L2042:
	ldr	r2, [r4, #2648]
	ldr	ip, [r3, #692]
	cmp	r2, ip
	bhi	.L2041
	ldr	lr, [r4, #2652]
	ldr	r1, [r3, #696]
	cmp	lr, r1
	bhi	.L2020
	ldr	r2, [r4, #2568]
	cmp	r2, #1
	beq	.L2015
.L2021:
	ldr	r7, [r3, #740]
	b	.L2017
.L2043:
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r6, #2860]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	beq	.L2024
	mov	r0, r7
	ldr	r1, .L2045+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2015
.L2044:
	ldr	r1, .L2045+28
	mov	r0, #2
	bl	dprint_vfmw
	b	.L2026
.L2046:
	.align	2
.L2045:
	.word	.LC32
	.word	.LC33
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC36
	.word	.LC34
	.word	.LC35
	.word	.LC37
	UNWIND(.fnend)
	.size	VP9_ArrangeVHBMem, .-VP9_ArrangeVHBMem
	.align	2
	.global	VP9_GetRefNum
	.type	VP9_GetRefNum, %function
VP9_GetRefNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r8, .L2066
	movw	r6, #10820
	sub	r4, fp, #72
	add	r7, r0, #274432
	movt	r6, 4
	add	r6, r0, r6
	ldr	r3, [r8, #52]
	add	r1, r6, #80
	mov	r2, #36
	mov	r0, r4
	ldr	r5, [r7, #3592]
	blx	r3
	ldr	r3, [r8, #52]
	add	r1, r6, #152
	sub	r0, fp, #104
	mov	r2, #32
	blx	r3
	ldr	r3, [r7, #3620]
	cmp	r3, #1
	beq	.L2065
.L2048:
	ldr	r3, [r7, #3708]
	mov	lr, r5, asl #2
	cmp	r3, #0
	subne	r2, fp, #104
	addne	ip, r4, lr
	beq	.L2055
.L2054:
	tst	r3, #1
	beq	.L2052
	ldr	r0, [r2]
	str	r5, [r2]
	ldr	r1, [r4, r0, asl #2]
	cmp	r1, #0
	sub	r1, r1, #1
	strgt	r1, [r4, r0, asl #2]
	ldr	r1, [ip]
	add	r1, r1, #1
	str	r1, [ip]
.L2052:
	movs	r3, r3, asr #1
	add	r2, r2, #4
	bne	.L2054
.L2055:
	sub	r3, fp, #36
	sub	r1, fp, #40
	add	r2, r3, lr
	sub	r3, fp, #76
	mov	r0, #0
	ldr	ip, [r2, #-36]
	sub	ip, ip, #1
	str	ip, [r2, #-36]
.L2051:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	addne	r0, r0, #1
	cmp	r3, r1
	bne	.L2051
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2065:
	ldr	r3, [r4, r5, asl #2]
	ldr	r2, [r7, #3624]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r4, r5, asl #2]
	ldr	r3, [r4, r2, asl #2]
	mov	r5, r2
	add	r3, r3, #1
	str	r3, [r4, r2, asl #2]
	b	.L2048
.L2067:
	.align	2
.L2066:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9_GetRefNum, .-VP9_GetRefNum
	.align	2
	.global	Vp9_DefaultCoefProbs
	.type	Vp9_DefaultCoefProbs, %function
Vp9_DefaultCoefProbs:
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
	ldr	r4, .L2069
	mov	r2, #1024
	ldr	r5, .L2069+4
	mov	r6, r0
	mov	r1, r4
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #1024
	add	r0, r6, #1024
	mov	r2, #1024
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #2048
	add	r0, r6, #2048
	mov	r2, #1024
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #3072
	add	r0, r6, #3072
	mov	r2, #1024
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L2070:
	.align	2
.L2069:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Vp9_DefaultCoefProbs, .-Vp9_DefaultCoefProbs
	.align	2
	.global	Vp9_InitMbmodeProbs
	.type	Vp9_InitMbmodeProbs, %function
Vp9_InitMbmodeProbs:
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
	ldr	r4, .L2072
	mov	r6, r0
	ldr	r5, .L2072+4
	add	r7, r6, #4096
	mov	r2, #160
	add	r0, r0, #4160
	sub	r1, r5, #4080
	ldr	r3, [r4, #52]
	sub	r1, r1, #8
	sub	r8, r5, #3856
	blx	r3
	sub	r1, r5, #3920
	ldr	r3, [r4, #52]
	mov	r0, r7
	sub	r1, r1, #8
	mov	r2, #64
	blx	r3
	add	r0, r6, #4416
	sub	r1, r8, #8
	ldr	r3, [r4, #52]
	mov	r2, #8
	add	r0, r0, #44
	blx	r3
	add	r0, r6, #4608
	mov	r1, r8
	ldr	r3, [r4, #52]
	mov	r2, #96
	add	r0, r0, #4
	blx	r3
	add	r0, r6, #4352
	ldr	r3, [r4, #52]
	sub	r1, r5, #3760
	mov	r2, #4
	add	r0, r0, #63
	blx	r3
	sub	r8, r5, #3744
	add	r0, r6, #4416
	sub	r1, r8, #12
	ldr	r3, [r4, #52]
	mov	r2, #5
	add	r0, r0, #3
	sub	r5, r5, #3728
	blx	r3
	add	r0, r6, #4416
	sub	r1, r8, #4
	ldr	r3, [r4, #52]
	mov	r2, #5
	add	r0, r0, #8
	blx	r3
	add	r0, r6, #4416
	ldr	r3, [r4, #52]
	sub	r1, r5, #12
	mov	r2, #10
	add	r0, r0, #13
	blx	r3
	add	r0, r7, #304
	mov	r2, #12
	ldr	r1, .L2072+8
	add	r0, r0, #3
	bl	memcpy
	add	r0, r6, #4352
	mov	r1, r5
	add	r0, r0, #48
	ldr	r3, [r4, #52]
	mov	r2, #3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L2073:
	.align	2
.L2072:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2
	.word	.LANCHOR0+720
	UNWIND(.fnend)
	.size	Vp9_InitMbmodeProbs, .-Vp9_InitMbmodeProbs
	.align	2
	.global	Vp9_InitMvProbs
	.type	Vp9_InitMvProbs, %function
Vp9_InitMvProbs:
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
	add	r0, r0, #4416
	mov	r2, #69
	ldr	r1, .L2075
	add	r0, r0, #52
	bl	memcpy
	ldmfd	sp, {fp, sp, pc}
.L2076:
	.align	2
.L2075:
	.word	.LANCHOR0+732
	UNWIND(.fnend)
	.size	Vp9_InitMvProbs, .-Vp9_InitMvProbs
	.align	2
	.global	Vp9_SetupPastIndependence
	.type	Vp9_SetupPastIndependence, %function
Vp9_SetupPastIndependence:
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
	mov	r5, r0
	mov	r4, r3
	mov	r6, r1
	mov	r7, r2
	ldr	r9, [fp, #4]
	ldr	r8, [fp, #8]
	bl	Vp9_DefaultCoefProbs
	mov	r0, r5
	bl	Vp9_InitMbmodeProbs
	add	r0, r5, #4416
	mov	r2, #69
	ldr	r1, .L2085
	add	r0, r0, #52
	bl	memcpy
	ldr	r3, .L2085+4
	add	r0, r5, #4416
	mov	r2, #21
	add	r0, r0, #23
	ldr	r1, .L2085+8
	ldr	r3, [r3, #52]
	blx	r3
	sub	r2, r4, #3
	clz	r2, r2
	mov	r2, r2, lsr #5
	cmp	r9, #0
	orrne	r2, r2, #1
	cmp	r8, #0
	orreq	r2, r2, #1
	cmp	r2, #0
	bne	.L2083
	cmp	r4, #2
	beq	.L2084
.L2080:
	mov	r3, #0
	str	r3, [r7]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2083:
	mov	r4, #0
	movw	r8, #18832
.L2079:
	add	r0, r6, r4
	add	r4, r4, #4672
	add	r4, r4, #36
	movw	r2, #4708
	mov	r1, r5
	bl	memcpy
	cmp	r4, r8
	bne	.L2079
	b	.L2080
.L2084:
	ldr	r0, [r7]
	movw	r2, #4708
	mov	r1, r5
	mla	r0, r2, r0, r6
	bl	memcpy
	b	.L2080
.L2086:
	.align	2
.L2085:
	.word	.LANCHOR0+732
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2-3724
	UNWIND(.fnend)
	.size	Vp9_SetupPastIndependence, .-Vp9_SetupPastIndependence
	.align	2
	.global	Vp9_Vfmw_SegfeatureActive
	.type	Vp9_Vfmw_SegfeatureActive, %function
Vp9_Vfmw_SegfeatureActive:
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
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2089
	add	r1, r1, #20
	mov	ip, #1
	ldr	r3, [r0, r1, asl #2]
	ands	r3, r3, ip, asl r2
	movne	r0, ip
	moveq	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L2089:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_SegfeatureActive, .-Vp9_Vfmw_SegfeatureActive
	.align	2
	.global	Vp9_Vfmw_GetSegdata
	.type	Vp9_Vfmw_GetSegdata, %function
Vp9_Vfmw_GetSegdata:
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
	add	r2, r2, r1, lsl #2
	add	r0, r0, r2, lsl #1
	ldrsh	r0, [r0, #16]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_GetSegdata, .-Vp9_Vfmw_GetSegdata
	.align	2
	.global	Vp9_Vfmw_Clamp
	.type	Vp9_Vfmw_Clamp, %function
Vp9_Vfmw_Clamp:
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
	cmp	r0, r1
	movlt	r0, r1
	cmp	r0, r2
	movge	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_Clamp, .-Vp9_Vfmw_Clamp
	.align	2
	.global	Vp9_Vfmw_LoopFilterFrameInit
	.type	Vp9_Vfmw_LoopFilterFrameInit, %function
Vp9_Vfmw_LoopFilterFrameInit:
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
	add	r7, r2, #80
	mov	r9, r2
	mov	r5, r1
	mov	r6, r0
	mov	r8, r2
	mov	r10, r3
	mov	r4, r3, asr #5
	add	r3, r2, #112
	str	r3, [fp, #-48]
.L2098:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2101
	ldr	r3, [r7]
	tst	r3, #2
	beq	.L2101
	ldrb	r3, [r9, #3]	@ zero_extendqisi2
	ldrsh	r1, [r8, #18]
	cmp	r3, #1
	ldrb	r3, [r5]	@ zero_extendqisi2
	addne	r1, r1, r10
	cmp	r3, #0
	usat	r1, #6, r1
	beq	.L2106
.L2095:
	mov	r0, r5
	add	lr, r5, #5
	ldrsb	r3, [r0, #2]!
	mov	ip, r6
	add	r3, r1, r3, asl r4
	usat	r3, #6, r3
	strb	r3, [r6]
.L2097:
	ldrsb	r3, [r0, #1]!
	add	ip, ip, #2
	ldrsb	r2, [r5, #6]
	cmp	r0, lr
	add	r3, r1, r3, asl r4
	add	r3, r3, r2, asl r4
	usat	r3, #6, r3
	strb	r3, [ip]
	ldrsb	r3, [r0]
	ldrsb	r2, [r5, #7]
	add	r3, r1, r3, asl r4
	add	r3, r3, r2, asl r4
	usat	r3, #6, r3
	strb	r3, [ip, #1]
	bne	.L2097
.L2096:
	ldr	r3, [fp, #-48]
	add	r7, r7, #4
	add	r6, r6, #8
	add	r8, r8, #8
	cmp	r7, r3
	bne	.L2098
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2101:
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r1, r10
	cmp	r3, #0
	bne	.L2095
.L2106:
	ldr	r3, .L2107
	mov	r2, #8
	mov	r0, r6
	ldr	r3, [r3, #48]
	blx	r3
	b	.L2096
.L2108:
	.align	2
.L2107:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Vp9_Vfmw_LoopFilterFrameInit, .-Vp9_Vfmw_LoopFilterFrameInit
	.align	2
	.global	Vp9_MiColsAlignedToSb
	.type	Vp9_MiColsAlignedToSb, %function
Vp9_MiColsAlignedToSb:
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
	add	r0, r0, #7
	bic	r0, r0, #7
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_MiColsAlignedToSb, .-Vp9_MiColsAlignedToSb
	.align	2
	.global	Vp9_ToSbs
	.type	Vp9_ToSbs, %function
Vp9_ToSbs:
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
	add	r0, r0, #7
	mov	r0, r0, asr #3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_ToSbs, .-Vp9_ToSbs
	.align	2
	.global	Vp9_GetTileOffsets
	.type	Vp9_GetTileOffsets, %function
Vp9_GetTileOffsets:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	lr, [fp, #4]
	add	ip, lr, #7
	mov	ip, ip, asr #3
	mul	r2, ip, r2
	add	ip, r2, ip
	mov	r2, r2, asr r3
	mov	r3, ip, asr r3
	mov	r2, r2, asl #3
	mov	r3, r3, asl #3
	cmp	r2, lr
	movge	r2, lr
	cmp	r3, lr
	str	r2, [r0]
	movge	r3, lr
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_GetTileOffsets, .-Vp9_GetTileOffsets
	.align	2
	.global	Vp9_GetTileRowOffsets
	.type	Vp9_GetTileRowOffsets, %function
Vp9_GetTileRowOffsets:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	ip, r1, #7
	ldr	lr, [fp, #4]
	mov	ip, ip, asr #3
	mul	r0, ip, r0
	add	ip, r0, ip
	mov	r0, r0, asr r2
	mov	r2, ip, asr r2
	mov	r0, r0, asl #3
	mov	r2, r2, asl #3
	cmp	r0, r1
	movge	r0, r1
	cmp	r2, r1
	str	r0, [r3]
	movge	r2, r1
	str	r2, [lr]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_GetTileRowOffsets, .-Vp9_GetTileRowOffsets
	.align	2
	.global	Vp9_Vfmw_GetTileColOffsets
	.type	Vp9_Vfmw_GetTileColOffsets, %function
Vp9_Vfmw_GetTileColOffsets:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	ip, r1, #7
	ldr	lr, [fp, #4]
	mov	ip, ip, asr #3
	mul	r0, ip, r0
	add	ip, r0, ip
	mov	r0, r0, asr r2
	mov	r2, ip, asr r2
	mov	r0, r0, asl #3
	mov	r2, r2, asl #3
	cmp	r0, r1
	movge	r0, r1
	cmp	r2, r1
	str	r0, [r3]
	movge	r2, r1
	str	r2, [lr]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_Vfmw_GetTileColOffsets, .-Vp9_Vfmw_GetTileColOffsets
	.align	2
	.global	Vp9_SetPoolInfoFrame
	.type	Vp9_SetPoolInfoFrame, %function
Vp9_SetPoolInfoFrame:
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
	add	r4, r0, #270336
	mov	r6, r0
	mov	r5, r1
	ldr	r0, [r4, #2480]
	add	r9, r6, #274432
	ldr	r1, [r4, #2488]
	add	r10, r6, #311296
	bl	GetCompressRatio
	ldr	r1, [r4, #2492]
	str	r0, [fp, #-48]
	ldr	r0, [r4, #2480]
	bl	GetCompressRatio
	ldr	r0, [r4, #2860]
	ldr	r2, [r4, #2864]
	and	r0, r0, #7
	ldr	r1, [r9, #3600]
	ldr	r3, [r9, #3596]
	and	r2, r2, #3
	mov	r0, r0, asl #10
	and	r1, r1, #1
	orr	r2, r0, r2, asl #13
	and	r3, r3, #3
	ldr	r0, [r9, #3660]
	orr	r2, r2, r1
	orr	r2, r2, r3, asl #1
	ldr	ip, [r9, #3676]
	and	r3, r0, #15
	ldr	r0, [r9, #3700]
	ldr	r1, [r9, #3672]
	and	ip, ip, #1
	orr	r3, r2, r3, asl #15
	ldr	r2, [r9, #3640]
	and	r1, r1, #1
	mov	r0, r0, asl #7
	orr	r3, r3, ip, asl #9
	orr	r1, r3, r1, asl #8
	uxtb	r0, r0
	and	r3, r2, #1
	orr	r1, r1, r0
	ldr	r2, [r9, #3636]
	orr	r1, r1, r3, asl #6
	ldr	r3, [r9, #3632]
	ldr	r0, [r9, #3628]
	and	r2, r2, #1
	and	r3, r3, #1
	orr	r2, r1, r2, asl #5
	and	r1, r0, #1
	orr	r3, r2, r3, asl #4
	orr	r3, r3, r1, asl #3
	str	r3, [r5]
	ldr	r2, [r9, #3644]
	ldr	r3, [r10, #2752]
	cmp	r2, r3
	movne	r0, #1048576
	beq	.L2151
.L2115:
	ldr	r3, [r4, #2816]
	mov	r7, #0
	ldr	r2, [r4, #2820]
	ldr	lr, [r9, #3712]
	mov	r3, r3, asl #12
	and	r2, r2, #15
	ldr	ip, [r4, #2704]
	and	r1, lr, #7
	uxth	r3, r3
	ldr	r8, [r4, #2700]
	orr	r2, r3, r2, asl #16
	orr	r2, r2, r1
	ldr	r1, [r4, #2812]
	mov	ip, ip, asl #7
	and	r1, r1, #15
	uxtb	ip, ip
	orr	r1, r2, r1, asl #8
	and	r2, r8, #1
	orr	r3, r1, ip
	ldr	ip, [r4, #2696]
	orr	r1, r3, r2, asl #6
	ldr	r3, [r4, #2692]
	and	r2, ip, #1
	ldr	ip, [r4, #2684]
	and	r3, r3, #1
	orr	r2, r1, r2, asl #5
	and	r1, ip, #1
	orr	r2, r2, r3, asl #4
	orr	r3, r2, r1, asl #3
	orr	r3, r3, r0
	str	r3, [r5, #4]
	ldr	r2, [r9, #3648]
	ldr	r3, [r9, #3644]
	add	r2, r2, #7
	add	r3, r3, #7
	mov	r2, r2, asr #3
	sub	r2, r2, #1
	mov	r3, r3, asr #3
	sub	r3, r3, #1
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #8]
	ldr	r2, [r4, #2972]
	ldr	r3, [r4, #2976]
	and	r2, r2, #63
	and	r3, r3, #7
	orr	r3, r3, r2, asl #8
	str	r3, [r5, #12]
.L2116:
	add	r0, r5, r7, lsl #3
	mov	lr, r7, asl #2
	add	r0, r0, #12
	mov	ip, #0
.L2117:
	mov	r2, ip, asl #1
	add	ip, ip, #1
	add	r1, r2, #1
	add	r2, lr, r2
	add	r1, lr, r1
	cmp	ip, #2
	add	r8, r4, r2, lsl #1
	add	r3, r4, r1, lsl #1
	mov	r2, r8
	ldrb	r8, [r8, #2884]	@ zero_extendqisi2
	mov	r1, r3
	ldrb	r3, [r3, #2884]	@ zero_extendqisi2
	ldrb	r1, [r1, #2885]	@ zero_extendqisi2
	and	r8, r8, #63
	and	r3, r3, #63
	ldrb	r2, [r2, #2885]	@ zero_extendqisi2
	and	r1, r1, #63
	mov	r3, r3, asl #16
	and	r2, r2, #63
	orr	r3, r3, r1, asl #24
	orr	r8, r3, r8
	orr	r3, r8, r2, asl #8
	str	r3, [r0, #4]!
	bne	.L2117
	add	r7, r7, #1
	cmp	r7, #8
	bne	.L2116
	ldr	ip, [r4, #2880]
	mov	r3, #0
	ldr	r2, [r4, #2876]
	cmp	ip, r3
	ldr	r1, [r4, #2872]
	ldrb	r0, [r4, #2868]	@ zero_extendqisi2
	movlt	r7, #268435456
	movge	r7, r3
	cmp	ip, #0
	rsblt	ip, ip, #0
	cmp	r2, r3
	and	ip, ip, #15
	movlt	lr, #1048576
	movge	lr, r3
	cmp	r2, #0
	rsblt	r2, r2, #0
	cmp	r1, r3
	and	r2, r2, #15
	mov	r2, r2, asl #16
	orr	r2, r2, ip, asl #24
	movlt	ip, #4096
	movge	ip, r3
	cmp	r1, #0
	rsblt	r1, r1, #0
	orr	r2, r2, r0
	and	r1, r1, #15
	add	r0, r9, #3792
	orr	r2, r2, r1, asl #8
	mov	r1, r3
	orr	r7, r2, r7
	orr	lr, r7, lr
	orr	ip, lr, ip
	str	ip, [r5, #80]
	ldrb	lr, [r9, #3719]	@ zero_extendqisi2
	ldrb	r8, [r9, #3720]	@ zero_extendqisi2
	and	lr, lr, #1
	ldrb	r7, [r9, #3716]	@ zero_extendqisi2
	ldrb	ip, [r9, #3717]	@ zero_extendqisi2
	and	r8, r8, #1
	mov	lr, lr, asl #2
	and	r7, r7, #1
	orr	lr, lr, r8, asl #3
	and	ip, ip, #1
	orr	r2, lr, r7
	orr	r2, r2, ip, asl #1
	str	r2, [r5, #84]
.L2122:
	ldr	r2, [r0, #4]!
	and	r2, r2, #15
	orr	r1, r1, r2, asl r3
	add	r3, r3, #4
	cmp	r3, #32
	bne	.L2122
	add	r0, r4, #2624
	str	r1, [r5, #88]
	add	r0, r0, #4
	movw	ip, #1112
	add	r1, r0, #4096
	add	r0, r0, #5248
	add	r3, r1, #1120
	add	r2, r1, #1104
	ldrh	ip, [r1, ip]
	add	lr, r1, #1136
	ldrh	r3, [r3]
	ubfx	ip, ip, #0, #9
	ldrh	r2, [r2]
	ubfx	r3, r3, #0, #9
	mov	ip, ip, asl #9
	ubfx	r2, r2, #0, #9
	orr	r3, ip, r3, asl #18
	movw	ip, #1128
	orr	r3, r3, r2
	str	r3, [r5, #92]
	movw	r3, #1144
	ldrh	r2, [lr]
	ldrh	r3, [r1, r3]
	ubfx	r2, r2, #0, #9
	ldrh	ip, [r1, ip]
	ubfx	r3, r3, #0, #9
	mov	r2, r2, asl #9
	ubfx	ip, ip, #0, #9
	orr	r3, r2, r3, asl #18
	movw	r2, #1160
	orr	r3, r3, ip
	str	r3, [r5, #96]
	ldrh	ip, [r1, r2]
	mov	r3, #0
	ldrh	r2, [r0]
	mov	r1, r3
	ubfx	r0, ip, #0, #9
	ubfx	r2, r2, #0, #9
	orr	r2, r2, r0, asl #9
	str	r2, [r5, #100]
.L2123:
	movw	r2, #16022
	movt	r2, 4
	add	r2, r3, r2
	ldrb	r2, [r6, r2]	@ zero_extendqisi2
	orr	r1, r1, r2, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	bne	.L2123
	mov	r3, #0
	str	r1, [r5, #104]
	mov	r1, r3
.L2124:
	movw	r2, #16054
	movt	r2, 4
	add	r2, r3, r2
	ldrb	r2, [r6, r2]	@ zero_extendqisi2
	orr	r1, r1, r2, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	bne	.L2124
	movw	r7, #16024
	mov	lr, #0
	movt	r7, 4
	add	r7, r6, r7
	mov	r6, lr
	str	r1, [r5, #108]
.L2125:
	ldrh	r1, [r7, #2]
	mov	r3, lr, asl #1
	ldrh	r2, [r7], #8
	add	r0, lr, #16
	and	r1, r1, #1
	add	lr, lr, #1
	and	r2, r2, #3
	cmp	lr, #8
	mov	r2, r2, asl r3
	orr	r3, r2, r1, asl r0
	orr	r6, r6, r3
	bne	.L2125
	str	r6, [r5, #112]
	ldr	r3, [r4, #2580]
	str	r3, [r5, #116]
	ldr	r3, [r4, #2592]
	str	r3, [r5, #120]
	ldr	r3, [r4, #2664]
	str	r3, [r5, #128]
	ldr	r3, [r4, #2668]
	str	r3, [r5, #132]
	ldr	r3, [r4, #2672]
	str	r3, [r5, #136]
	ldr	r3, [r4, #2676]
	str	r3, [r5, #140]
	ldr	r3, [r9, #3976]
	ldr	r2, [r9, #3972]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #180]
	ldr	r3, [r9, #3992]
	ldr	r2, [r9, #3988]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #184]
	ldr	r3, [r9, #4008]
	ldr	r2, [r9, #4004]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #188]
	ldr	r2, [r9, #4000]
	ldr	r3, [r9, #4016]
	and	r2, r2, #63
	ldr	r1, [r9, #3984]
	and	r3, r3, #63
	mov	r2, r2, asl #8
	and	r1, r1, #63
	orr	r3, r2, r3, asl #16
	orr	r3, r3, r1
	str	r3, [r5, #192]
	ldr	r2, [r9, #3996]
	ldr	r3, [r9, #4012]
	and	r2, r2, #63
	ldr	r1, [r9, #3980]
	and	r3, r3, #63
	mov	r2, r2, asl #8
	and	r1, r1, #63
	orr	r3, r2, r3, asl #16
	orr	r3, r3, r1
	str	r3, [r5, #196]
	ldr	r3, [r4, #2812]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #200]
	bls	.L2152
.L2127:
	ldr	r3, [r4, #2816]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #204]
	bhi	.L2129
	add	r3, r4, r3, lsl #4
	movw	r1, #7932
	add	r2, r3, #7872
	ldr	r3, [r3, r1]
	add	r2, r2, #60
	str	r3, [r4, #2532]
	uxth	r3, r3
	ldr	r2, [r2, #4]
	str	r2, [r4, #2544]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #204]
.L2129:
	ldr	r3, [r4, #2820]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #208]
	bhi	.L2131
	add	r3, r4, r3, lsl #4
	movw	r1, #7932
	add	r2, r3, #7872
	ldr	r3, [r3, r1]
	add	r2, r2, #60
	str	r3, [r4, #2536]
	uxth	r3, r3
	ldr	r2, [r2, #4]
	str	r2, [r4, #2548]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #208]
.L2131:
	ldr	r3, [r10, #2752]
	ldr	r2, [r10, #2756]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #212]
	ldr	r2, [r4, #2812]
	cmp	r2, #8
	bls	.L2132
	mov	r3, #0
	str	r3, [r5, #216]
	str	r3, [r5, #220]
	str	r3, [r5, #224]
.L2133:
	ldr	r2, [r4, #2816]
	cmp	r2, #8
	bls	.L2135
	mov	r3, #0
	str	r3, [r5, #228]
	str	r3, [r5, #232]
	str	r3, [r5, #236]
	ldr	r2, [r4, #2820]
	cmp	r2, #8
	bhi	.L2153
.L2138:
	mov	r2, r2, asl #4
	movw	ip, #7932
	add	r0, r4, r2
	ldr	r7, [fp, #-48]
	add	r1, r0, #7872
	ldr	r3, [r0, ip]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r7, r3
	add	lr, r3, #7
	cmp	r3, #0
	movlt	r3, lr
	mov	r3, r3, asr #3
	str	r3, [r5, #240]
	ldr	r0, [r0, ip]
	ldr	ip, [r1, #64]
	add	r3, r0, #255
	ldr	r6, [r4, #2476]
	bic	r3, r3, #255
	add	r1, ip, #63
	bic	lr, r1, #63
	mul	r3, r7, r3
	cmp	r3, #0
	add	r7, r3, #7
	movlt	r3, r7
	cmp	r6, #1
	mov	r3, r3, asr #3
	mul	r3, lr, r3
	beq	.L2154
.L2140:
	add	r4, r4, r2
	movw	r1, #7932
	add	r2, r4, #7872
	str	r3, [r5, #244]
	ldr	r1, [r4, r1]
	ldr	r0, [r2, #64]
	add	r3, r1, #2032
	add	r1, r1, #4080
	adds	r2, r0, #63
	add	r3, r3, #15
	addmi	r2, r0, #126
	add	r1, r1, #14
	cmp	r3, #0
	mov	r2, r2, asr #6
	movlt	r3, r1
	mov	r3, r3, asr #11
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #248]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2152:
	add	r3, r4, r3, lsl #4
	movw	r1, #7932
	add	r2, r3, #7872
	ldr	r3, [r3, r1]
	add	r2, r2, #60
	str	r3, [r4, #2528]
	uxth	r3, r3
	ldr	r2, [r2, #4]
	str	r2, [r4, #2540]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #200]
	b	.L2127
.L2135:
	mov	r2, r2, asl #4
	movw	ip, #7932
	add	r0, r4, r2
	ldr	r7, [fp, #-48]
	add	r1, r0, #7872
	ldr	r3, [r0, ip]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r7, r3
	add	lr, r3, #7
	cmp	r3, #0
	movlt	r3, lr
	mov	r3, r3, asr #3
	str	r3, [r5, #228]
	ldr	r0, [r0, ip]
	ldr	ip, [r1, #64]
	add	r3, r0, #255
	ldr	r6, [r4, #2476]
	bic	r3, r3, #255
	add	r1, ip, #63
	bic	lr, r1, #63
	mul	r3, r7, r3
	cmp	r3, #0
	add	r7, r3, #7
	movlt	r3, r7
	cmp	r6, #1
	mov	r3, r3, asr #3
	mul	r3, lr, r3
	beq	.L2155
.L2137:
	add	r2, r4, r2
	movw	r1, #7932
	add	r0, r2, #7872
	str	r3, [r5, #232]
	add	r0, r0, #60
	ldr	r1, [r2, r1]
	ldr	r0, [r0, #4]
	add	r3, r1, #2032
	add	r3, r3, #15
	add	r1, r1, #4080
	adds	r2, r0, #63
	add	r1, r1, #14
	addmi	r2, r0, #126
	cmp	r3, #0
	movlt	r3, r1
	mov	r2, r2, asr #6
	mov	r3, r3, asr #11
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #236]
	ldr	r2, [r4, #2820]
	cmp	r2, #8
	bls	.L2138
.L2153:
	mov	r3, #0
	str	r3, [r5, #240]
	str	r3, [r5, #244]
	str	r3, [r5, #248]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2132:
	mov	r2, r2, asl #4
	movw	ip, #7932
	add	r0, r4, r2
	ldr	r7, [fp, #-48]
	add	r1, r0, #7872
	ldr	r3, [r0, ip]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, r7, r3
	add	lr, r3, #7
	cmp	r3, #0
	movlt	r3, lr
	mov	r3, r3, asr #3
	str	r3, [r5, #216]
	ldr	r0, [r0, ip]
	ldr	ip, [r1, #64]
	add	r3, r0, #255
	ldr	r6, [r4, #2476]
	bic	r3, r3, #255
	add	r1, ip, #63
	bic	lr, r1, #63
	mul	r3, r7, r3
	cmp	r3, #0
	add	r7, r3, #7
	movlt	r3, r7
	cmp	r6, #1
	mov	r3, r3, asr #3
	mul	r3, lr, r3
	beq	.L2156
.L2134:
	add	r2, r4, r2
	movw	r1, #7932
	add	r0, r2, #7872
	str	r3, [r5, #220]
	add	r0, r0, #60
	ldr	r1, [r2, r1]
	ldr	r0, [r0, #4]
	add	r3, r1, #2032
	add	r3, r3, #15
	add	r1, r1, #4080
	adds	r2, r0, #63
	add	r1, r1, #14
	addmi	r2, r0, #126
	cmp	r3, #0
	movlt	r3, r1
	mov	r2, r2, asr #6
	mov	r3, r3, asr #11
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #224]
	b	.L2133
.L2151:
	ldr	r0, [r9, #3648]
	ldr	r3, [r10, #2756]
	cmp	r0, r3
	movne	r0, #1048576
	moveq	r0, #0
	b	.L2115
.L2154:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L2140
	add	lr, r0, #2032
	cmp	r1, #0
	add	lr, lr, #15
	addlt	r1, ip, #126
	add	r0, r0, #4080
	cmp	lr, #0
	add	r0, r0, #14
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #11
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2140
.L2155:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L2137
	add	lr, r0, #2032
	cmp	r1, #0
	add	lr, lr, #15
	addlt	r1, ip, #126
	add	r0, r0, #4080
	cmp	lr, #0
	add	r0, r0, #14
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #11
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2137
.L2156:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L2134
	add	lr, r0, #2032
	cmp	r1, #0
	add	lr, lr, #15
	addlt	r1, ip, #126
	add	r0, r0, #4080
	cmp	lr, #0
	add	r0, r0, #14
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #11
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2134
	UNWIND(.fnend)
	.size	Vp9_SetPoolInfoFrame, .-Vp9_SetPoolInfoFrame
	.align	2
	.global	Vp9_SetPoolInfoTile
	.type	Vp9_SetPoolInfoTile, %function
Vp9_SetPoolInfoTile:
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
	ldr	r2, [r3]
	str	r2, [r1]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	and	r2, r2, #127
	str	r2, [r1, #4]
	ldr	r2, [r3, #8]
	add	r2, r2, #128
	str	r2, [r1, #8]
	ldr	r2, [r3, #12]
	str	r2, [r1, #12]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	and	r2, r2, #127
	str	r2, [r1, #16]
	ldr	r2, [r3, #20]
	str	r2, [r1, #20]
	ldrh	r2, [r3, #26]
	ldrh	ip, [r3, #24]
	cmp	ip, r2
	add	r0, ip, #7
	addne	r2, r2, #7
	ubfx	r0, r0, #3, #7
	movne	r2, r2, asr #3
	mov	r0, r0, asl #16
	subne	r2, r2, #1
	orreq	r2, r0, #255
	andne	r2, r2, #127
	orrne	r2, r2, r0
	str	r2, [r1, #24]
	ldrh	r0, [r3, #30]
	ldrh	ip, [r3, #28]
	cmp	ip, r0
	add	r2, ip, #7
	addne	r0, r0, #7
	ubfx	r2, r2, #3, #7
	movne	r0, r0, asr #3
	mov	r2, r2, asl #16
	subne	r0, r0, #1
	orreq	r2, r2, #255
	andne	r0, r0, #127
	orrne	r2, r0, r2
	str	r2, [r1, #28]
	ldr	r2, [r3, #32]
	mov	r0, #0
	ubfx	r2, r2, #0, #17
	str	r2, [r1, #32]
	ldr	r2, [r3, #36]
	ubfx	r2, r2, #0, #17
	str	r2, [r1, #36]
	ldr	r2, [r3, #40]
	ubfx	r2, r2, #0, #17
	str	r2, [r1, #40]
	ldr	r3, [r3, #44]
	str	r0, [r1, #252]
	ubfx	r3, r3, #0, #17
	str	r3, [r1, #44]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_SetPoolInfoTile, .-Vp9_SetPoolInfoTile
	.align	2
	.global	Vp9_DecodeTilesCtrl
	.type	Vp9_DecodeTilesCtrl, %function
Vp9_DecodeTilesCtrl:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 160
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #172)
	sub	sp, sp, #172
	add	r3, r0, #274432
	add	ip, r0, #311296
	mov	r7, r1
	str	ip, [fp, #-168]
	mov	r2, #1
	ldr	r1, [r3, #3696]
	mov	r5, ip
	ldr	ip, [r3, #3692]
	add	r4, r0, #270336
	ldr	r8, [r3, #3684]
	mov	lr, r1
	ldr	r3, [r3, #3688]
	mov	r6, ip
	str	ip, [fp, #-152]
	mov	ip, r2, asl lr
	ldr	r9, [r7]
	str	ip, [fp, #-192]
	mov	r2, r2, asl r6
	mov	r10, ip
	ldr	ip, [r7, #16]
	str	r1, [fp, #-196]
	add	r1, r0, #8
	str	r2, [fp, #-124]
	str	r3, [fp, #-188]
	add	r3, r9, ip
	str	r0, [fp, #-116]
	str	r3, [fp, #-120]
	bl	Vp9_SetPoolInfoFrame
	mov	r1, #0
	str	r1, [r5, #2868]
	ldr	r2, [r4, #2552]
	cmp	r10, #0
	ldr	r3, [r4, #2556]
	str	r2, [fp, #-164]
	and	r3, r3, #15
	str	r3, [fp, #-160]
	ble	.L2173
	ldr	r2, [fp, #-188]
	add	r3, r8, #7
	str	r1, [fp, #-180]
	add	r2, r2, #7
	mov	r0, r3, asr #3
	str	r1, [fp, #-172]
	mov	r3, r2, asr #3
	str	r0, [fp, #-156]
	str	r0, [fp, #-204]
	str	r3, [fp, #-200]
	str	r1, [fp, #-112]
	str	r1, [fp, #-184]
.L2172:
	ldr	r3, [fp, #-180]
	ldr	r2, [fp, #-200]
	ldr	r0, [fp, #-196]
	add	r3, r3, r2
	str	r3, [fp, #-180]
	ldr	r2, [fp, #-188]
	mov	r1, r3
	ldr	r3, [fp, #-184]
	mov	r1, r1, asr r0
	str	r1, [fp, #-184]
	ldr	ip, [fp, #-124]
	mov	r3, r3, asl #3
	mov	r0, r1
	cmp	r3, r2
	movge	r3, r2
	str	r3, [fp, #-136]
	mov	r1, r3
	mov	r3, r0, asl #3
	cmp	r3, r2
	movge	r3, r2
	str	r3, [fp, #-140]
	mov	r0, r3
	rsb	r3, r1, r0
	add	r3, r3, #7
	cmp	ip, #0
	mov	r2, r1
	mov	r3, r3, asr #3
	str	r3, [fp, #-132]
	ble	.L2165
	add	r3, r0, #7
	ldr	r0, [fp, #-204]
	add	r1, r2, #7
	mov	r6, #0
	mov	r3, r3, asr #3
	ldr	r2, [r7, #16]
	sub	r3, r3, #1
	mov	r1, r1, asr #3
	mov	r5, r6
	str	r6, [fp, #-104]
	mul	r3, r0, r3
	mul	r1, r0, r1
	str	r3, [fp, #-144]
	sub	r3, ip, #1
	str	r3, [fp, #-128]
	ldr	r3, [fp, #-192]
	str	r1, [fp, #-148]
	sub	r3, r3, #1
	str	r3, [fp, #-176]
	b	.L2171
.L2183:
	ldr	r2, [fp, #-176]
	ldr	r1, [fp, #-172]
	cmp	r2, r1
	ldrle	r2, [fp, #-120]
	rsble	r10, r9, r2
	bgt	.L2166
.L2168:
	ldrh	r2, [fp, #-136]
	rsb	r1, r3, r4
	add	r1, r1, #7
	mov	r0, #0
	str	r0, [fp, #-84]
	strh	r2, [fp, #-72]	@ movhi
	mov	r1, r1, asr #3
	ldrh	r2, [fp, #-140]
	ldr	r0, [fp, #-132]
	strh	r4, [fp, #-66]	@ movhi
	strh	r2, [fp, #-70]	@ movhi
	add	r2, r4, #7
	mul	r4, r0, r1
	ldr	r1, [fp, #-164]
	ldr	r0, [fp, #-160]
	ldr	ip, [fp, #-112]
	rsb	r1, r1, r9
	add	r1, r1, r0
	ldr	r0, [fp, #-144]
	strh	r3, [fp, #-68]	@ movhi
	cmp	r4, #0
	add	r2, r0, r2, asr #3
	add	r4, ip, r4
	mov	r0, #0
	add	r3, r3, #7
	strb	r0, [fp, #-80]
	sub	r0, fp, #44
	str	ip, [fp, #-52]
	sub	r2, r2, #1
	str	r0, [fp, #-48]
	mov	r0, #0
	ldr	ip, [fp, #-148]
	str	r0, [fp, #-76]
	and	r0, r1, #15
	add	r3, ip, r3, asr #3
	str	r2, [fp, #-64]
	str	r3, [fp, #-56]
	sub	r2, r4, #1
	mov	r3, r0, asl #3
	bic	r1, r1, #15
	strb	r3, [fp, #-92]
	mov	r3, r10, asl #3
	str	r2, [fp, #-60]
	str	r1, [fp, #-96]
	str	r3, [fp, #-88]
	bne	.L2181
.L2169:
	ldr	r3, [fp, #-116]
	add	r3, r3, #278528
	ldr	r3, [r3, #296]
	cmp	r10, r3
	movle	r2, #0
	movgt	r2, #1
	orrs	r2, r2, r10, lsr #31
	bne	.L2182
	ldr	r3, [fp, #-124]
	add	r5, r5, #1
	ldr	r2, [r7, #16]
	add	r9, r9, r10
	cmp	r5, r3
	str	r4, [fp, #-112]
	rsb	r2, r10, r2
	str	r2, [r7, #16]
	beq	.L2165
.L2171:
	ldr	r3, [fp, #-156]
	mov	r0, r7
	ldr	r1, [fp, #-152]
	add	r6, r6, r3
	ldr	r3, [fp, #-104]
	mov	r1, r6, asr r1
	str	r1, [fp, #-104]
	mov	r3, r3, asl #3
	cmp	r3, r8
	mov	ip, r1
	mov	r4, ip, asl #3
	mov	r1, r9
	movge	r3, r8
	cmp	r4, r8
	str	r3, [fp, #-108]
	movge	r4, r8
	bl	BsInit
	ldr	r3, [fp, #-128]
	cmp	r5, r3
	ldr	r3, [fp, #-108]
	bge	.L2183
.L2166:
	ldr	r2, [fp, #-120]
	cmp	r2, #0
	cmpne	r9, #0
	beq	.L2175
	add	r9, r9, #4
	str	r3, [fp, #-108]
	cmp	r2, r9
	bcc	.L2175
	mov	r1, #32
	mov	r0, r7
	bl	BsGet
	ldr	r3, [fp, #-108]
	mov	r10, r0
	b	.L2168
.L2181:
	ldr	r3, [fp, #-168]
	sub	r1, fp, #96
	ldr	r2, [r3, #2868]
	mov	r3, r1
	ldr	r1, [fp, #-116]
	mov	r0, r1
	add	r1, r1, r2, lsl #8
	add	r1, r1, #1024
	add	r1, r1, #8
	bl	Vp9_SetPoolInfoTile
	ldr	r2, [fp, #-168]
	ldr	r3, [r2, #2868]
	add	r3, r3, #1
	str	r3, [r2, #2868]
	b	.L2169
.L2175:
	mvn	r0, #0
.L2164:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2182:
	str	r3, [sp, #4]
	mov	r0, #0
	movw	r3, #4556
	str	r10, [sp]
	ldr	r2, .L2184
	ldr	r1, .L2184+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2165:
	ldr	r3, [fp, #-172]
	ldr	r2, [fp, #-192]
	add	r3, r3, #1
	str	r3, [fp, #-172]
	cmp	r3, r2
	bne	.L2172
.L2173:
	mov	r0, #0
	b	.L2164
.L2185:
	.align	2
.L2184:
	.word	.LANCHOR0+804
	.word	.LC38
	UNWIND(.fnend)
	.size	Vp9_DecodeTilesCtrl, .-Vp9_DecodeTilesCtrl
	.align	2
	.global	Vp9_DecodeTiles
	.type	Vp9_DecodeTiles, %function
Vp9_DecodeTiles:
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
	UNWIND(.pad #108)
	sub	sp, sp, #108
	add	r3, r0, #274432
	add	r4, r0, #311296
	add	r6, r0, #270336
	ldr	r10, [r3, #3600]
	mov	r5, r0
	ldr	r0, [r3, #3680]
	mov	lr, #0
	clz	ip, r10
	ldr	r9, [r6, #2688]
	ldr	r7, [r6, #2680]
	mov	r8, r0
	str	r0, [fp, #-108]
	mov	ip, ip, lsr #5
	ldr	r0, [r3, #3704]
	str	ip, [r4, #2824]
	str	r10, [r4, #2836]
	ldr	ip, [r3, #3632]
	str	r0, [fp, #-120]
	sub	r0, fp, #84
	str	lr, [fp, #-92]
	str	ip, [r4, #2844]
	ldr	ip, [r3, #3700]
	str	lr, [fp, #-88]
	add	lr, r5, #278528
	str	r8, [fp, #-96]
	add	r8, lr, #312
	str	ip, [r4, #2828]
	ldr	ip, [r3, #3676]
	str	r1, [fp, #-112]
	str	r2, [fp, #-116]
	str	ip, [r4, #2848]
	ldr	ip, [r6, #2684]
	str	lr, [fp, #-104]
	str	ip, [r4, #2852]
	ldr	ip, [r3, #3712]
	str	ip, [r4, #2856]
	ldr	r3, [r3, #3596]
	str	r3, [r4, #2840]
	bl	BsInit
	ldr	r3, [r4, #2824]
	cmp	r3, #0
	ldr	r3, [r4, #2844]
	bne	.L2188
	cmp	r3, #0
	beq	.L2203
.L2188:
	add	r1, r5, #282624
	stmia	sp, {r3, r10}
	add	r1, r1, #924
	ldr	r3, [fp, #-120]
	sub	r2, fp, #96
	mov	r0, r8
	bl	Vp9_SetupPastIndependence
	ldr	r3, .L2207
	movw	r0, #10884
	mov	r2, #16
	movt	r0, 4
	mov	r1, #0
	add	r0, r5, r0
	ldr	r3, [r3, #48]
	blx	r3
.L2189:
	ldr	r3, [fp, #-96]
	movw	r1, #4708
	mov	r2, r1
	ldr	r0, [fp, #-104]
	mla	r1, r1, r3, r5
	add	r0, r0, #312
	add	r1, r1, #282624
	add	r1, r1, #924
	bl	memcpy
	sub	r0, fp, #84
	bl	Vp9_Cabac_ReaderInit
	ldr	r2, [r4, #2852]
	ldr	r1, [r4, #2856]
	sub	r0, fp, #88
	ldr	r3, [r4, #2828]
	sub	ip, fp, #92
	str	r2, [sp, #4]
	mov	r2, r10
	str	r1, [sp]
	mov	r1, r8
	str	r0, [sp, #20]
	sub	r0, fp, #84
	str	r7, [sp, #12]
	str	r9, [sp, #8]
	str	ip, [sp, #16]
	bl	Vp9_ReadCompressedHeader
	cmp	r0, #0
	bne	.L2204
	ldr	r3, [fp, #-88]
	movw	r7, #10820
	ldr	r2, [fp, #-92]
	movt	r7, 4
	add	r7, r5, r7
	str	r3, [r6, #2860]
	str	r3, [r4, #2832]
	ldr	r3, [r6, #2972]
	str	r2, [r6, #2864]
	cmp	r3, #0
	bne	.L2205
.L2192:
	ldr	r3, [r4, #2828]
	cmp	r3, #0
	bne	.L2206
	mov	r1, r10, asl #6
	ldr	r9, .L2207
	sub	r1, r1, r10, asl #4
	mov	r2, #48
	add	r1, r8, r1
	add	r0, r8, #4352
	add	r1, r1, #4608
	ldr	r3, [r9, #52]
	add	r1, r1, #4
	blx	r3
.L2194:
	add	r1, r7, #5184
	ldr	r3, [r9, #52]
	add	r1, r1, #5
	mov	r2, #7
	add	r0, r8, #4544
	blx	r3
	ldr	r3, [fp, #-104]
	add	r1, r7, #5184
	mov	r2, #3
	add	r1, r1, #12
	add	r0, r3, #4864
	ldr	r3, [r9, #52]
	blx	r3
	movw	r0, #1037
	ldr	r3, [r9, #52]
	mov	r1, r8
	movt	r0, 4
	mov	r2, #4608
	add	r0, r5, r0
	blx	r3
	ldr	r3, [r4, #2828]
	cmp	r3, #0
	beq	.L2195
	ldr	r2, [fp, #-108]
	movw	r3, #4708
	movw	r0, #25756
	movt	r0, 4
	mul	r3, r3, r2
	ldr	r2, .L2207
	add	r1, r5, r3
	ldr	r4, [r2, #52]
	mov	r2, #48
	mov	r3, r1
	add	r1, r1, #286720
	add	r0, r3, r0
	add	r1, r1, #1440
	blx	r4
.L2196:
	ldr	r3, [fp, #-108]
	movw	r1, #4708
	movw	r0, #5645
	mov	r2, #4608
	movt	r0, 4
	add	r0, r5, r0
	mla	r1, r1, r3, r5
	ldr	r3, [r9, #52]
	add	r1, r1, #282624
	add	r1, r1, #924
	blx	r3
	ldr	r3, [r6, #2636]
	ldr	r2, [fp, #-112]
	sub	r1, fp, #84
	ldr	ip, [fp, #-116]
	mov	r0, r5
	add	r2, r2, r3
	str	r2, [fp, #-84]
	rsb	r3, r3, ip
	str	r3, [fp, #-68]
	bl	Vp9_DecodeTilesCtrl
	mov	r0, #0
.L2191:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2206:
	ldr	r9, .L2207
	add	r1, r8, #4608
	add	r1, r1, #4
	mov	r2, #48
	add	r0, r8, #4352
	ldr	r3, [r9, #52]
	blx	r3
	b	.L2194
.L2203:
	ldr	r2, [r4, #2828]
	cmp	r2, #0
	beq	.L2189
	b	.L2188
.L2195:
	ldr	r3, [fp, #-108]
	movw	ip, #4708
	mov	r1, r10, asl #6
	movw	r0, #25756
	sub	r1, r1, r10, asl #4
	movt	r0, 4
	mul	ip, ip, r3
	ldr	r3, .L2207
	mov	r2, #48
	add	r1, r1, ip
	add	ip, r5, ip
	add	r1, r5, r1
	ldr	r3, [r3, #52]
	add	r1, r1, #286720
	add	r0, ip, r0
	add	r1, r1, #1440
	blx	r3
	b	.L2196
.L2205:
	add	r2, r7, #5184
	add	r1, r7, #336
	add	r0, r7, #256
	bl	Vp9_Vfmw_LoopFilterFrameInit
	b	.L2192
.L2204:
	ldr	r1, .L2207+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2191
.L2208:
	.align	2
.L2207:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC39
	UNWIND(.fnend)
	.size	Vp9_DecodeTiles, .-Vp9_DecodeTiles
	.align	2
	.global	VP9DEC_DecodeFame
	.type	VP9DEC_DecodeFame, %function
VP9DEC_DecodeFame:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r3, r0, #278528
	add	r4, r0, #311296
	str	r3, [fp, #-64]
	mov	r2, r3
	movw	r9, #10820
	ldr	r3, [r4, #2764]
	add	r2, r2, #280
	movt	r9, 4
	mov	r6, r0
	cmp	r3, #0
	str	r1, [fp, #-60]
	str	r2, [fp, #-56]
	add	r7, r0, #274432
	add	r9, r0, r9
	beq	.L2210
	ldr	r3, [r7, #3592]
	cmp	r3, #0
	blt	.L2210
.L2211:
	str	r3, [r4, #2760]
	mov	r1, r9
	ldr	r0, [fp, #-56]
	bl	Read_UnCompressed_Header
	subs	r5, r0, #0
	bne	.L2256
	ldr	r2, [r7, #3660]
	ldr	r3, [r6]
	str	r2, [r3, #932]
	ldr	r2, [r7, #3660]
	cmp	r2, #10
	bgt	.L2296
.L2217:
	ldr	r3, [r7, #3620]
	add	r5, r6, #270336
	cmp	r3, #0
	beq	.L2297
.L2219:
	ldr	r2, [r7, #3644]
	sub	r3, r2, #128
	cmp	r3, #3968
	bhi	.L2220
	ldr	r1, [r7, #3648]
	sub	r3, r1, #80
	cmp	r3, #4016
	bhi	.L2220
	adds	r3, r2, #63
	str	r2, [r5, #2648]
	addmi	r2, r2, #126
	movpl	r2, r3
	adds	r3, r1, #63
	addmi	r3, r1, #126
	str	r1, [r5, #2652]
	mov	r2, r2, asr #6
	mov	r0, r6
	mov	r3, r3, asr #6
	str	r2, [r5, #2640]
	str	r3, [r5, #2644]
	bl	VP9_GetRefNum
	str	r0, [r4, #2736]
	ldr	r0, [r4, #2860]
	ldr	r2, [r5, #2652]
	ldr	r1, [r5, #2648]
	bl	VCTRL_GetFsSize
	mov	r1, r0
	str	r0, [r4, #2724]
	ldr	r0, [r4, #2860]
	bl	FSP_GetPhyFsNum
	ldr	r3, .L2313
	ldr	r1, [r4, #2860]
	ldr	r2, [r3, r1, asl #2]
	str	r0, [r4, #2728]
	ldr	r3, [r2, #1456]
	str	r3, [r4, #2732]
	ldr	r0, [r5, #2648]
	cmp	r0, #1920
	bls	.L2298
.L2224:
	ldr	ip, [r4, #2740]
	ldr	r2, [r4, #2736]
	ldr	lr, .L2313+4
	cmp	r2, ip
	ldr	lr, [lr, #-3700]
	movge	ip, r2
	add	r3, r3, ip
	cmp	r3, lr
	movcc	r3, lr
	str	r3, [r4, #2732]
	ldr	r3, [r4, #2744]
	cmp	r0, r3
	beq	.L2299
.L2226:
	str	r2, [r4, #2740]
.L2228:
	mov	r0, r1
	mov	r1, #0
	bl	FSP_GetPhyFsNum
	ldr	r2, [r4, #2728]
	cmp	r0, r2
	mov	r8, r0
	ble	.L2229
	rsb	r3, r2, r0
	cmp	r3, #0
	ble	.L2229
	mov	r10, #0
	b	.L2231
.L2300:
	rsb	r3, r2, r8
	cmp	r3, r10
	ble	.L2229
.L2231:
	ldr	r1, [r4, #2724]
	add	r10, r10, #1
	ldr	r0, [r4, #2860]
	bl	FSP_RelsePhyFs
	ldr	r2, [r4, #2728]
	cmp	r0, #0
	beq	.L2300
.L2229:
	ldr	r3, [r4, #2732]
	cmp	r3, r2
	bge	.L2234
	rsb	r2, r3, r2
	cmp	r2, #0
	ble	.L2234
	mov	r8, #0
	b	.L2235
.L2301:
	ldr	r3, [r4, #2728]
	ldr	r2, [r4, #2732]
	rsb	r3, r2, r3
	cmp	r3, r8
	ble	.L2234
.L2235:
	mov	r1, #0
	ldr	r0, [r4, #2860]
	bl	FSP_RelsePhyFs
	add	r8, r8, #1
	cmp	r0, #0
	beq	.L2301
.L2234:
	mov	r1, #0
	ldr	r0, [r4, #2860]
	bl	FSP_GetPhyFsNum
	ldr	r3, [r4, #2732]
	add	r3, r3, #4
	cmp	r0, r3
	mov	r8, r0
	bgt	.L2302
	ldr	r1, [r4, #2724]
	ldr	r0, [r4, #2860]
	bl	FSP_GetPhyFsNum
	ldr	r2, [r4, #2736]
	ldr	r1, [r4, #2732]
	add	r3, r2, #1
	cmp	r0, r3
	rsb	r3, r8, r0
	addgt	ip, r2, #2
	addle	ip, r0, #1
	add	r3, r3, r1
	str	r0, [r4, #2728]
	cmp	ip, r3
	str	r0, [sp, #4]
	str	r2, [sp, #8]
	mov	r0, #2
	movlt	ip, r3
	str	r8, [sp]
	ldr	r1, .L2313+8
	str	ip, [r4, #2732]
	ldr	r3, [r5, #2652]
	ldr	r2, [r5, #2648]
	str	ip, [sp, #12]
	bl	dprint_vfmw
	ldr	r3, [r5, #2568]
	cmp	r3, #0
	beq	.L2238
	ldr	r2, [r4, #2744]
	ldr	r3, [r5, #2648]
	cmp	r2, r3
	beq	.L2303
.L2238:
	mov	r0, r6
	bl	VP9_ArrangeVHBMem
	ldr	r3, [r5, #2568]
	cmp	r3, #0
	beq	.L2304
.L2239:
	ldr	r3, [r6]
	ldr	r3, [r3, #8]
	str	r3, [r5, #2564]
	ldr	r3, [r7, #3620]
	ldr	r0, [r4, #2860]
	cmp	r3, #0
	ldreq	r3, [r5, #2648]
	streq	r3, [r4, #2744]
	ldreq	r3, [r5, #2652]
	streq	r3, [r4, #2748]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	bne	.L2305
	ldr	r0, [fp, #-56]
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	bne	.L2306
	ldr	r3, [r7, #3620]
	cmp	r3, #0
	beq	.L2307
.L2243:
	mov	r0, r6
	bl	VP9_GetImageBuffer
	cmp	r0, #0
	bne	.L2308
	ldr	r3, [r4, #2760]
	mov	r0, r6
	ldr	r2, [r5, #2612]
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #2824]
	bl	VP9_Set_DecParam
	cmp	r0, #0
	bne	.L2309
	ldr	r3, [r7, #3620]
	cmp	r3, #1
	beq	.L2310
	ldr	r3, [r5, #2648]
	str	r3, [r4, #2752]
	ldr	r3, [r5, #2652]
	str	r3, [r4, #2756]
.L2248:
	mov	r0, r9
	bl	swap_frame_buffers
	ldr	r2, [r4, #2812]
	ldr	r0, [r4, #2816]
	cmp	r2, r0
	bcs	.L2249
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2249
	add	r3, r2, #1
	b	.L2250
.L2311:
	ldrb	r1, [r2]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2249
.L2250:
	cmp	r3, r0
	str	r3, [r4, #2812]
	mov	r2, r3
	add	r3, r3, #1
	bne	.L2311
.L2249:
	ldr	r3, [r4, #2768]
	cmp	r3, #1
	beq	.L2312
.L2251:
	mov	r5, #0
	str	r5, [r4, #2764]
	ldr	r0, [r7, #3620]
	cmp	r0, r5
	bne	.L2252
	ldr	r3, [r7, #3616]
	str	r3, [r7, #3628]
.L2288:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2210:
	add	r5, r6, #270336
	ldr	r3, [r5, #2708]
	cmp	r3, #0
	beq	.L2212
	movw	r2, #10900
	mov	r3, #1
	movt	r2, 4
	add	r2, r6, r2
.L2213:
	ldr	r1, [r2, #4]!
	cmp	r1, #0
	beq	.L2212
	add	r3, r3, #1
	cmp	r3, #9
	bne	.L2213
	mvn	r3, #0
	str	r3, [r7, #3592]
.L2253:
	ldr	r1, .L2313+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2288
.L2297:
	ldr	r2, [r5, #2560]
	cmp	r2, #7
	bgt	.L2219
	ldr	r1, .L2313+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2288
.L2298:
	ldr	ip, [r5, #2652]
	cmp	ip, #1088
	bhi	.L2224
	ldr	ip, [r2, #36]
	cmp	ip, #24
	beq	.L2225
	add	r2, r2, #475136
	ldr	r2, [r2, #1332]
	cmp	r2, #0
	addeq	r3, r3, #4
.L2225:
	ldr	ip, [r4, #2740]
	ldr	r2, [r4, #2736]
	cmp	r2, ip
	movge	ip, r2
	add	r3, ip, r3
	str	r3, [r4, #2732]
	ldr	r3, [r4, #2744]
	cmp	r0, r3
	bne	.L2226
.L2299:
	ldr	r3, [r5, #2652]
	ldr	r0, [r4, #2748]
	cmp	r0, r3
	streq	ip, [r4, #2740]
	bne	.L2226
	b	.L2228
.L2296:
	ldr	r1, .L2313+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2313+24
	ldr	r8, [r3]
	cmp	r8, #0
	beq	.L2217
	ldr	ip, [r7, #3660]
	mov	r3, #8
	str	r5, [fp, #-52]
	sub	r2, fp, #52
	mov	r1, #119
	ldr	r0, [r4, #2860]
	str	ip, [fp, #-48]
	blx	r8
	b	.L2217
.L2306:
	ldr	r0, [fp, #-56]
	bl	BsGet
	ldr	r3, [r7, #3620]
	cmp	r3, #0
	bne	.L2243
.L2307:
	ldr	r2, [fp, #-64]
	mov	r0, r6
	ldr	r1, [fp, #-60]
	ldr	r3, [r2, #304]
	ldr	r2, [r2, #296]
	add	r3, r3, #7
	mov	r3, r3, lsr #3
	add	r1, r1, r3
	rsb	r2, r3, r2
	bl	Vp9_DecodeTiles
	b	.L2243
.L2310:
	ldr	r0, [r7, #3592]
	movw	r3, #10900
	movt	r3, 4
	add	r3, r6, r3
	ldr	r1, [r7, #3624]
	ldr	r2, [r3, r0, asl #2]
	cmp	r2, #0
	subgt	r2, r2, #1
	strgt	r2, [r3, r0, asl #2]
	str	r1, [r7, #3592]
	ldr	r2, [r3, r1, asl #2]
	add	r2, r2, #1
	str	r2, [r3, r1, asl #2]
	b	.L2248
.L2303:
	ldr	r2, [r4, #2748]
	ldr	r3, [r5, #2652]
	cmp	r2, r3
	bne	.L2238
	ldr	r2, [r4, #2728]
	ldr	r3, [r4, #2732]
	cmp	r2, r3
	bge	.L2239
	b	.L2238
.L2212:
	add	r5, r5, r3, lsl #2
	cmp	r3, #0
	mov	r2, #1
	str	r2, [r5, #2708]
	str	r3, [r7, #3592]
	bge	.L2211
	b	.L2253
.L2252:
	mov	r0, r6
	mov	r3, r5
	mov	r2, r5
	mov	r1, r5
	bl	VP9DEC_VDMPostProc
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2312:
	ldr	r1, [r4, #2808]
	add	r3, r1, #77824
	add	r1, r1, #1
	add	r3, r3, #692
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r1, [r4, #2808]
	add	r2, r2, r3
	str	r2, [r4, #2812]
	b	.L2251
.L2220:
	ldr	r3, .L2313+24
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2222
	mov	r3, #0
	ldr	r0, [r4, #2860]
	mov	r2, r3
	mov	r1, #102
	blx	r5
	ldr	r2, [r7, #3644]
.L2222:
	ldr	r3, [r7, #3648]
	mov	r0, #1
	ldr	r1, .L2313+28
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2302:
	mvn	r0, #1
	b	.L2288
.L2305:
	movw	r3, #4072
	ldr	r2, .L2313+32
	ldr	r1, .L2313+36
	mov	r0, #23
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2288
.L2256:
	mvn	r0, #0
	b	.L2288
.L2308:
	ldr	r1, .L2313+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2288
.L2304:
	ldr	r1, .L2313+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2288
.L2309:
	ldr	r1, .L2313+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2288
.L2314:
	.align	2
.L2313:
	.word	s_pstVfmwChan
	.word	.LANCHOR2
	.word	.LC44
	.word	.LC40
	.word	.LC42
	.word	.LC41
	.word	g_event_report
	.word	.LC43
	.word	.LANCHOR0+824
	.word	.LC46
	.word	.LC47
	.word	.LC45
	.word	.LC48
	UNWIND(.fnend)
	.size	VP9DEC_DecodeFame, .-VP9DEC_DecodeFame
	.align	2
	.global	VP9DEC_DecodePacket
	.type	VP9DEC_DecodePacket, %function
VP9DEC_DecodePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r1, #0
	cmpne	r0, #0
	mov	r3, #0
	mov	r5, r0
	str	r3, [fp, #-72]
	beq	.L2325
	ldr	r0, [r1]
	add	r8, r5, #270336
	add	r4, r5, #311296
	str	r0, [r8, #2552]
	ldr	r3, [r1, #12]
	str	r3, [r8, #2556]
	ldr	r1, [r1, #16]
	str	r1, [r8, #2560]
	ldr	r6, [r4, #2768]
	cmp	r6, #0
	beq	.L2334
	ldr	r2, [r4, #2820]
	ldr	r7, [r4, #2812]
.L2321:
	cmp	r2, #0
	beq	.L2320
	ldrb	r0, [r7]	@ zero_extendqisi2
	and	r1, r0, #7
	ubfx	ip, r0, #3, #2
	add	r3, r1, #1
	and	r1, r0, #224
	cmp	r1, #192
	mla	r3, ip, r3, r3
	bne	.L2320
	add	r1, r7, r3
	add	r3, r3, #2
	cmp	r3, r2
	bhi	.L2320
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, r0
	bne	.L2320
	ldr	r1, [r4, #2816]
	add	r7, r7, r3
	rsb	r2, r3, r2
	str	r7, [r4, #2812]
	cmp	r7, r1
	str	r2, [r4, #2820]
	bcc	.L2321
.L2320:
	cmp	r6, #1
	add	r0, r5, #278528
	add	r0, r0, #280
	mov	r1, r7
	ldreq	r3, [r4, #2808]
	addeq	r3, r3, #77824
	addeq	r3, r3, #692
	addeq	r3, r5, r3, lsl #2
	ldreq	r2, [r3, #4]
	bl	BsInit
	mov	r1, r7
	mov	r0, r5
	bl	VP9DEC_DecodeFame
	cmn	r0, #2
	mov	r6, r0
	moveq	r3, #1
	streq	r3, [r4, #2764]
	beq	.L2316
	cmp	r6, #0
	moveq	r0, r6
	bne	.L2335
.L2316:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2335:
	mov	r0, r5
	bl	VP9_FreeCurFb
	mov	r3, #0
	mov	r1, r5
	str	r3, [r4, #2768]
	mov	r0, #17
	bl	ReleasePacket
	ldr	r1, .L2337
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2334:
	sub	r3, fp, #72
	sub	r2, fp, #68
	bl	Vp9_ParseSuperFrameIndex
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	bne	.L2336
.L2318:
	ldr	r7, [r8, #2552]
	ldr	r6, [r4, #2768]
	str	r7, [r4, #2812]
	ldr	r2, [r8, #2560]
	add	r3, r7, r2
	str	r3, [r4, #2816]
	str	r2, [r4, #2820]
	b	.L2321
.L2336:
	ldr	r2, .L2337+4
	movw	r0, #51924
	str	r3, [r4, #2804]
	sub	r1, fp, #68
	str	r6, [r4, #2808]
	movt	r0, 4
	ldr	r3, [r2, #52]
	add	r0, r5, r0
	mov	r2, #1
	str	r2, [r4, #2768]
	mov	r2, #32
	blx	r3
	b	.L2318
.L2325:
	mvn	r0, #0
	b	.L2316
.L2338:
	.align	2
.L2337:
	.word	.LC49
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9DEC_DecodePacket, .-VP9DEC_DecodePacket
	.align	2
	.global	Vp9_TxCoefProbConvert2
	.type	Vp9_TxCoefProbConvert2, %function
Vp9_TxCoefProbConvert2:
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
	ldr	r4, .L2340
	mov	r2, #18
	mov	r5, r0
	mov	r6, r1
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #18
	add	r0, r5, #32
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #36
	add	r0, r5, #64
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #54
	add	r0, r5, #96
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #72
	add	r0, r5, #128
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #90
	add	r0, r5, #160
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #108
	add	r0, r5, #192
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #256
	add	r0, r5, #256
	mov	r2, #18
	blx	r3
	add	r1, r6, #272
	ldr	r3, [r4, #52]
	add	r1, r1, #2
	add	r0, r5, #288
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #292
	add	r0, r5, #320
	mov	r2, #18
	blx	r3
	add	r1, r6, #308
	ldr	r3, [r4, #52]
	add	r1, r1, #2
	add	r0, r5, #352
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #328
	add	r0, r5, #384
	mov	r2, #18
	blx	r3
	add	r1, r6, #344
	ldr	r3, [r4, #52]
	add	r1, r1, #2
	add	r0, r5, #416
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #364
	add	r0, r5, #448
	mov	r2, #18
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L2341:
	.align	2
.L2340:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Vp9_TxCoefProbConvert2, .-Vp9_TxCoefProbConvert2
	.align	2
	.global	Vp9_ProbBurstConvert
	.type	Vp9_ProbBurstConvert, %function
Vp9_ProbBurstConvert:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2343
	mov	r2, #4608
	ldr	r3, [r3, #52]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L2344:
	.align	2
.L2343:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Vp9_ProbBurstConvert, .-Vp9_ProbBurstConvert
	.align	2
	.global	Vp9_CoefCountRestore
	.type	Vp9_CoefCountRestore, %function
Vp9_CoefCountRestore:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r7, r1, #1152
	add	r7, r7, #4
	add	r3, r1, #3456
	add	r3, r3, #4
	str	r0, [fp, #-52]
	str	r2, [fp, #-48]
	str	r3, [fp, #-56]
.L2346:
	ldr	r9, [fp, #-48]
	sub	r8, r7, #1152
	ldr	r4, [fp, #-52]
.L2352:
	add	r6, r4, #576
	mov	r5, r8
	mov	ip, r9
.L2350:
	add	lr, ip, #24
	mov	r0, r5
	mov	r1, r4
.L2347:
	ldr	r3, [r1]
	add	r0, r0, #16
	add	r1, r1, #16
	bic	r2, r3, #-67108864
	str	r2, [ip], #4
	ldr	r2, [r1, #-12]
	mov	r3, r3, lsr #26
	cmp	lr, ip
	ubfx	r10, r2, #0, #20
	mov	r2, r2, lsr #20
	orr	r3, r3, r10, asl #6
	str	r3, [r0, #-20]
	ldr	r3, [r1, #-8]
	ubfx	r10, r3, #0, #14
	mov	r3, r3, lsr #14
	orr	r2, r2, r10, asl #12
	str	r2, [r0, #-16]
	ldr	r2, [r1, #-4]
	uxtb	r10, r2
	mov	r2, r2, lsr #8
	str	r2, [r0, #-8]
	orr	r3, r3, r10, asl #18
	str	r3, [r0, #-12]
	bne	.L2347
	add	r4, r4, #96
	add	r5, r5, #96
	cmp	r6, r4
	mov	ip, lr
	bne	.L2350
	add	r8, r8, #576
	add	r9, r9, #144
	cmp	r7, r8
	mov	r4, r6
	bne	.L2352
	ldr	r3, [fp, #-52]
	add	r7, r7, #1152
	add	r3, r3, #1152
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-56]
	cmp	r7, r3
	ldr	r3, [fp, #-48]
	add	r3, r3, #288
	str	r3, [fp, #-48]
	bne	.L2346
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_CoefCountRestore, .-Vp9_CoefCountRestore
	.global	g_CfgVp9FrmNum
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	vp9_cabac_norm, %object
	.size	vp9_cabac_norm, 256
vp9_cabac_norm:
	.byte	0
	.byte	7
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
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
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
	.byte	0
	.byte	0
	.type	vp9_inv_map_table, %object
	.size	vp9_inv_map_table, 254
vp9_inv_map_table:
	.byte	6
	.byte	19
	.byte	32
	.byte	45
	.byte	58
	.byte	71
	.byte	84
	.byte	97
	.byte	110
	.byte	123
	.byte	-120
	.byte	-107
	.byte	-94
	.byte	-81
	.byte	-68
	.byte	-55
	.byte	-42
	.byte	-29
	.byte	-16
	.byte	-3
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	5
	.byte	7
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	21
	.byte	22
	.byte	23
	.byte	24
	.byte	25
	.byte	26
	.byte	27
	.byte	28
	.byte	29
	.byte	30
	.byte	31
	.byte	33
	.byte	34
	.byte	35
	.byte	36
	.byte	37
	.byte	38
	.byte	39
	.byte	40
	.byte	41
	.byte	42
	.byte	43
	.byte	44
	.byte	46
	.byte	47
	.byte	48
	.byte	49
	.byte	50
	.byte	51
	.byte	52
	.byte	53
	.byte	54
	.byte	55
	.byte	56
	.byte	57
	.byte	59
	.byte	60
	.byte	61
	.byte	62
	.byte	63
	.byte	64
	.byte	65
	.byte	66
	.byte	67
	.byte	68
	.byte	69
	.byte	70
	.byte	72
	.byte	73
	.byte	74
	.byte	75
	.byte	76
	.byte	77
	.byte	78
	.byte	79
	.byte	80
	.byte	81
	.byte	82
	.byte	83
	.byte	85
	.byte	86
	.byte	87
	.byte	88
	.byte	89
	.byte	90
	.byte	91
	.byte	92
	.byte	93
	.byte	94
	.byte	95
	.byte	96
	.byte	98
	.byte	99
	.byte	100
	.byte	101
	.byte	102
	.byte	103
	.byte	104
	.byte	105
	.byte	106
	.byte	107
	.byte	108
	.byte	109
	.byte	111
	.byte	112
	.byte	113
	.byte	114
	.byte	115
	.byte	116
	.byte	117
	.byte	118
	.byte	119
	.byte	120
	.byte	121
	.byte	122
	.byte	124
	.byte	125
	.byte	126
	.byte	127
	.byte	-128
	.byte	-127
	.byte	-126
	.byte	-125
	.byte	-124
	.byte	-123
	.byte	-122
	.byte	-121
	.byte	-119
	.byte	-118
	.byte	-117
	.byte	-116
	.byte	-115
	.byte	-114
	.byte	-113
	.byte	-112
	.byte	-111
	.byte	-110
	.byte	-109
	.byte	-108
	.byte	-106
	.byte	-105
	.byte	-104
	.byte	-103
	.byte	-102
	.byte	-101
	.byte	-100
	.byte	-99
	.byte	-98
	.byte	-97
	.byte	-96
	.byte	-95
	.byte	-93
	.byte	-92
	.byte	-91
	.byte	-90
	.byte	-89
	.byte	-88
	.byte	-87
	.byte	-86
	.byte	-85
	.byte	-84
	.byte	-83
	.byte	-82
	.byte	-80
	.byte	-79
	.byte	-78
	.byte	-77
	.byte	-76
	.byte	-75
	.byte	-74
	.byte	-73
	.byte	-72
	.byte	-71
	.byte	-70
	.byte	-69
	.byte	-67
	.byte	-66
	.byte	-65
	.byte	-64
	.byte	-63
	.byte	-62
	.byte	-61
	.byte	-60
	.byte	-59
	.byte	-58
	.byte	-57
	.byte	-56
	.byte	-54
	.byte	-53
	.byte	-52
	.byte	-51
	.byte	-50
	.byte	-49
	.byte	-48
	.byte	-47
	.byte	-46
	.byte	-45
	.byte	-44
	.byte	-43
	.byte	-41
	.byte	-40
	.byte	-39
	.byte	-38
	.byte	-37
	.byte	-36
	.byte	-35
	.byte	-34
	.byte	-33
	.byte	-32
	.byte	-31
	.byte	-30
	.byte	-28
	.byte	-27
	.byte	-26
	.byte	-25
	.byte	-24
	.byte	-23
	.byte	-22
	.byte	-21
	.byte	-20
	.byte	-19
	.byte	-18
	.byte	-17
	.byte	-15
	.byte	-14
	.byte	-13
	.byte	-12
	.byte	-11
	.byte	-10
	.byte	-9
	.byte	-8
	.byte	-7
	.byte	-6
	.byte	-5
	.byte	-4
	.space	2
	.type	count_to_update_factor, %object
	.size	count_to_update_factor, 21
count_to_update_factor:
	.byte	0
	.byte	6
	.byte	12
	.byte	19
	.byte	25
	.byte	32
	.byte	38
	.byte	44
	.byte	51
	.byte	57
	.byte	64
	.byte	70
	.byte	76
	.byte	83
	.byte	89
	.byte	96
	.byte	102
	.byte	108
	.byte	115
	.byte	121
	.byte	-128
	.space	3
	.type	__func__.14492, %object
	.size	__func__.14492, 19
__func__.14492:
	.ascii	"VP9_GetImageBuffer\000"
	.space	1
	.type	seg_feature_data_max, %object
	.size	seg_feature_data_max, 16
seg_feature_data_max:
	.word	255
	.word	63
	.word	3
	.word	0
	.type	seg_feature_data_signed, %object
	.size	seg_feature_data_signed, 16
seg_feature_data_signed:
	.word	1
	.word	1
	.word	0
	.word	0
	.type	__func__.14668, %object
	.size	__func__.14668, 16
__func__.14668:
	.ascii	"VP9_Set_Segdata\000"
.LC0:
	.word	1
	.word	0
	.word	2
	.word	3
	.type	__FUNCTION__.14744, %object
	.size	__FUNCTION__.14744, 33
__FUNCTION__.14744:
	.ascii	"VP9_get_fixed_point_scale_factor\000"
	.space	3
	.type	__FUNCTION__.14773, %object
	.size	__FUNCTION__.14773, 35
__FUNCTION__.14773:
	.ascii	"Vp9_ReadBitDepthColorSpaceSampling\000"
	.space	1
	.type	__FUNCTION__.14803, %object
	.size	__FUNCTION__.14803, 25
__FUNCTION__.14803:
	.ascii	"Read_UnCompressed_Header\000"
	.space	3
	.type	vp9_default_tx_probs, %object
	.size	vp9_default_tx_probs, 12
vp9_default_tx_probs:
	.byte	100
	.byte	66
	.byte	20
	.byte	-104
	.byte	15
	.byte	101
	.byte	3
	.byte	-120
	.byte	37
	.byte	5
	.byte	52
	.byte	13
	.type	vp9_default_nmv_context, %object
	.size	vp9_default_nmv_context, 69
vp9_default_nmv_context:
	.byte	-128
	.byte	-128
	.byte	32
	.byte	64
	.byte	96
	.byte	-32
	.byte	-112
	.byte	-64
	.byte	-88
	.byte	-64
	.byte	-80
	.byte	-64
	.byte	-58
	.byte	-58
	.byte	-11
	.byte	-40
	.byte	-128
	.byte	-80
	.byte	-96
	.byte	-80
	.byte	-80
	.byte	-64
	.byte	-58
	.byte	-58
	.byte	-48
	.byte	-40
	.byte	-48
	.byte	-120
	.byte	-116
	.byte	-108
	.byte	-96
	.byte	-80
	.byte	-64
	.byte	-32
	.byte	-22
	.byte	-22
	.byte	-16
	.byte	-120
	.byte	-116
	.byte	-108
	.byte	-96
	.byte	-80
	.byte	-64
	.byte	-32
	.byte	-22
	.byte	-22
	.byte	-16
	.byte	-128
	.byte	-128
	.byte	64
	.byte	96
	.byte	112
	.byte	64
	.byte	-128
	.byte	-128
	.byte	64
	.byte	96
	.byte	112
	.byte	64
	.byte	64
	.byte	96
	.byte	64
	.byte	64
	.byte	96
	.byte	64
	.byte	-96
	.byte	-96
	.byte	-128
	.byte	-128
	.space	3
	.type	__func__.15024, %object
	.size	__func__.15024, 20
__func__.15024:
	.ascii	"Vp9_DecodeTilesCtrl\000"
	.type	__func__.14883, %object
	.size	__func__.14883, 18
__func__.14883:
	.ascii	"VP9DEC_DecodeFame\000"
	.data
	.align	2
.LANCHOR1 = . + 0
.LANCHOR2 = . + 8184
	.type	vp9_default_coef_probs_4x4, %object
	.size	vp9_default_coef_probs_4x4, 1024
vp9_default_coef_probs_4x4:
	.byte	-61
	.byte	29
	.byte	-73
	.space	1
	.byte	84
	.byte	49
	.byte	-120
	.space	1
	.byte	8
	.byte	42
	.byte	71
	.space	1
	.space	20
	.byte	31
	.byte	107
	.byte	-87
	.space	1
	.byte	35
	.byte	99
	.byte	-97
	.space	1
	.byte	17
	.byte	82
	.byte	-116
	.space	1
	.byte	8
	.byte	66
	.byte	114
	.space	1
	.byte	2
	.byte	44
	.byte	76
	.space	1
	.byte	1
	.byte	19
	.byte	32
	.space	1
	.space	8
	.byte	40
	.byte	-124
	.byte	-55
	.space	1
	.byte	29
	.byte	114
	.byte	-69
	.space	1
	.byte	13
	.byte	91
	.byte	-99
	.space	1
	.byte	7
	.byte	75
	.byte	127
	.space	1
	.byte	3
	.byte	58
	.byte	95
	.space	1
	.byte	1
	.byte	28
	.byte	47
	.space	1
	.space	8
	.byte	69
	.byte	-114
	.byte	-35
	.space	1
	.byte	42
	.byte	122
	.byte	-55
	.space	1
	.byte	15
	.byte	91
	.byte	-97
	.space	1
	.byte	6
	.byte	67
	.byte	121
	.space	1
	.byte	1
	.byte	42
	.byte	77
	.space	1
	.byte	1
	.byte	17
	.byte	31
	.space	1
	.space	8
	.byte	102
	.byte	-108
	.byte	-28
	.space	1
	.byte	67
	.byte	117
	.byte	-52
	.space	1
	.byte	17
	.byte	82
	.byte	-102
	.space	1
	.byte	6
	.byte	59
	.byte	114
	.space	1
	.byte	2
	.byte	39
	.byte	75
	.space	1
	.byte	1
	.byte	15
	.byte	29
	.space	1
	.space	8
	.byte	-100
	.byte	57
	.byte	-23
	.space	1
	.byte	119
	.byte	57
	.byte	-44
	.space	1
	.byte	58
	.byte	48
	.byte	-93
	.space	1
	.byte	29
	.byte	40
	.byte	124
	.space	1
	.byte	12
	.byte	30
	.byte	81
	.space	1
	.byte	3
	.byte	12
	.byte	31
	.space	1
	.space	8
	.space	64
	.byte	-65
	.byte	107
	.byte	-30
	.space	1
	.byte	124
	.byte	117
	.byte	-52
	.space	1
	.byte	25
	.byte	99
	.byte	-101
	.space	1
	.space	20
	.byte	29
	.byte	-108
	.byte	-46
	.space	1
	.byte	37
	.byte	126
	.byte	-62
	.space	1
	.byte	8
	.byte	93
	.byte	-99
	.space	1
	.byte	2
	.byte	68
	.byte	118
	.space	1
	.byte	1
	.byte	39
	.byte	69
	.space	1
	.byte	1
	.byte	17
	.byte	33
	.space	1
	.space	8
	.byte	41
	.byte	-105
	.byte	-43
	.space	1
	.byte	27
	.byte	123
	.byte	-63
	.space	1
	.byte	3
	.byte	82
	.byte	-112
	.space	1
	.byte	1
	.byte	58
	.byte	105
	.space	1
	.byte	1
	.byte	32
	.byte	60
	.space	1
	.byte	1
	.byte	13
	.byte	26
	.space	1
	.space	8
	.byte	59
	.byte	-97
	.byte	-36
	.space	1
	.byte	23
	.byte	126
	.byte	-58
	.space	1
	.byte	4
	.byte	88
	.byte	-105
	.space	1
	.byte	1
	.byte	66
	.byte	114
	.space	1
	.byte	1
	.byte	38
	.byte	71
	.space	1
	.byte	1
	.byte	18
	.byte	34
	.space	1
	.space	8
	.byte	114
	.byte	-120
	.byte	-24
	.space	1
	.byte	51
	.byte	114
	.byte	-49
	.space	1
	.byte	11
	.byte	83
	.byte	-101
	.space	1
	.byte	3
	.byte	56
	.byte	105
	.space	1
	.byte	1
	.byte	33
	.byte	65
	.space	1
	.byte	1
	.byte	17
	.byte	34
	.space	1
	.space	8
	.byte	-107
	.byte	65
	.byte	-22
	.space	1
	.byte	121
	.byte	57
	.byte	-41
	.space	1
	.byte	61
	.byte	49
	.byte	-90
	.space	1
	.byte	28
	.byte	36
	.byte	114
	.space	1
	.byte	12
	.byte	25
	.byte	76
	.space	1
	.byte	3
	.byte	16
	.byte	42
	.space	1
	.space	8
	.space	64
	.byte	-42
	.byte	49
	.byte	-36
	.space	1
	.byte	-124
	.byte	63
	.byte	-68
	.space	1
	.byte	42
	.byte	65
	.byte	-119
	.space	1
	.space	20
	.byte	85
	.byte	-119
	.byte	-35
	.space	1
	.byte	104
	.byte	-125
	.byte	-40
	.space	1
	.byte	49
	.byte	111
	.byte	-64
	.space	1
	.byte	21
	.byte	87
	.byte	-101
	.space	1
	.byte	2
	.byte	49
	.byte	87
	.space	1
	.byte	1
	.byte	16
	.byte	28
	.space	1
	.space	8
	.byte	89
	.byte	-93
	.byte	-26
	.space	1
	.byte	90
	.byte	-119
	.byte	-36
	.space	1
	.byte	29
	.byte	100
	.byte	-73
	.space	1
	.byte	10
	.byte	70
	.byte	-121
	.space	1
	.byte	2
	.byte	42
	.byte	81
	.space	1
	.byte	1
	.byte	17
	.byte	33
	.space	1
	.space	8
	.byte	108
	.byte	-89
	.byte	-19
	.space	1
	.byte	55
	.byte	-123
	.byte	-34
	.space	1
	.byte	15
	.byte	97
	.byte	-77
	.space	1
	.byte	4
	.byte	72
	.byte	-121
	.space	1
	.byte	1
	.byte	45
	.byte	85
	.space	1
	.byte	1
	.byte	19
	.byte	38
	.space	1
	.space	8
	.byte	124
	.byte	-110
	.byte	-16
	.space	1
	.byte	66
	.byte	124
	.byte	-32
	.space	1
	.byte	17
	.byte	88
	.byte	-81
	.space	1
	.byte	4
	.byte	58
	.byte	122
	.space	1
	.byte	1
	.byte	36
	.byte	75
	.space	1
	.byte	1
	.byte	18
	.byte	37
	.space	1
	.space	8
	.byte	-115
	.byte	79
	.byte	-15
	.space	1
	.byte	126
	.byte	70
	.byte	-29
	.space	1
	.byte	66
	.byte	58
	.byte	-74
	.space	1
	.byte	30
	.byte	44
	.byte	-120
	.space	1
	.byte	12
	.byte	34
	.byte	96
	.space	1
	.byte	2
	.byte	20
	.byte	47
	.space	1
	.space	8
	.space	64
	.byte	-27
	.byte	99
	.byte	-7
	.space	1
	.byte	-113
	.byte	111
	.byte	-21
	.space	1
	.byte	46
	.byte	109
	.byte	-64
	.space	1
	.space	20
	.byte	82
	.byte	-98
	.byte	-20
	.space	1
	.byte	94
	.byte	-110
	.byte	-32
	.space	1
	.byte	25
	.byte	117
	.byte	-65
	.space	1
	.byte	9
	.byte	87
	.byte	-107
	.space	1
	.byte	3
	.byte	56
	.byte	99
	.space	1
	.byte	1
	.byte	33
	.byte	57
	.space	1
	.space	8
	.byte	83
	.byte	-89
	.byte	-19
	.space	1
	.byte	68
	.byte	-111
	.byte	-34
	.space	1
	.byte	10
	.byte	103
	.byte	-79
	.space	1
	.byte	2
	.byte	72
	.byte	-125
	.space	1
	.byte	1
	.byte	41
	.byte	79
	.space	1
	.byte	1
	.byte	20
	.byte	39
	.space	1
	.space	8
	.byte	99
	.byte	-89
	.byte	-17
	.space	1
	.byte	47
	.byte	-115
	.byte	-32
	.space	1
	.byte	10
	.byte	104
	.byte	-78
	.space	1
	.byte	2
	.byte	73
	.byte	-123
	.space	1
	.byte	1
	.byte	44
	.byte	85
	.space	1
	.byte	1
	.byte	22
	.byte	47
	.space	1
	.space	8
	.byte	127
	.byte	-111
	.byte	-13
	.space	1
	.byte	71
	.byte	-127
	.byte	-28
	.space	1
	.byte	17
	.byte	93
	.byte	-79
	.space	1
	.byte	3
	.byte	61
	.byte	124
	.space	1
	.byte	1
	.byte	41
	.byte	84
	.space	1
	.byte	1
	.byte	21
	.byte	52
	.space	1
	.space	8
	.byte	-99
	.byte	78
	.byte	-12
	.space	1
	.byte	-116
	.byte	72
	.byte	-25
	.space	1
	.byte	69
	.byte	58
	.byte	-72
	.space	1
	.byte	31
	.byte	44
	.byte	-119
	.space	1
	.byte	14
	.byte	38
	.byte	105
	.space	1
	.byte	8
	.byte	23
	.byte	61
	.space	1
	.space	8
	.space	64
	.type	vp9_default_coef_probs_8x8, %object
	.size	vp9_default_coef_probs_8x8, 1024
vp9_default_coef_probs_8x8:
	.byte	125
	.byte	34
	.byte	-69
	.space	1
	.byte	52
	.byte	41
	.byte	-123
	.space	1
	.byte	6
	.byte	31
	.byte	56
	.space	1
	.space	20
	.byte	37
	.byte	109
	.byte	-103
	.space	1
	.byte	51
	.byte	102
	.byte	-109
	.space	1
	.byte	23
	.byte	87
	.byte	-128
	.space	1
	.byte	8
	.byte	67
	.byte	101
	.space	1
	.byte	1
	.byte	41
	.byte	63
	.space	1
	.byte	1
	.byte	19
	.byte	29
	.space	1
	.space	8
	.byte	31
	.byte	-102
	.byte	-71
	.space	1
	.byte	17
	.byte	127
	.byte	-81
	.space	1
	.byte	6
	.byte	96
	.byte	-111
	.space	1
	.byte	2
	.byte	73
	.byte	114
	.space	1
	.byte	1
	.byte	51
	.byte	82
	.space	1
	.byte	1
	.byte	28
	.byte	45
	.space	1
	.space	8
	.byte	23
	.byte	-93
	.byte	-56
	.space	1
	.byte	10
	.byte	-125
	.byte	-71
	.space	1
	.byte	2
	.byte	93
	.byte	-108
	.space	1
	.byte	1
	.byte	67
	.byte	111
	.space	1
	.byte	1
	.byte	41
	.byte	69
	.space	1
	.byte	1
	.byte	14
	.byte	24
	.space	1
	.space	8
	.byte	29
	.byte	-80
	.byte	-39
	.space	1
	.byte	12
	.byte	-111
	.byte	-55
	.space	1
	.byte	3
	.byte	101
	.byte	-100
	.space	1
	.byte	1
	.byte	69
	.byte	111
	.space	1
	.byte	1
	.byte	39
	.byte	63
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.byte	57
	.byte	-64
	.byte	-23
	.space	1
	.byte	25
	.byte	-102
	.byte	-41
	.space	1
	.byte	6
	.byte	109
	.byte	-89
	.space	1
	.byte	3
	.byte	78
	.byte	118
	.space	1
	.byte	1
	.byte	48
	.byte	69
	.space	1
	.byte	1
	.byte	21
	.byte	29
	.space	1
	.space	8
	.space	64
	.byte	-54
	.byte	105
	.byte	-11
	.space	1
	.byte	108
	.byte	106
	.byte	-40
	.space	1
	.byte	18
	.byte	90
	.byte	-112
	.space	1
	.space	20
	.byte	33
	.byte	-84
	.byte	-37
	.space	1
	.byte	64
	.byte	-107
	.byte	-50
	.space	1
	.byte	14
	.byte	117
	.byte	-79
	.space	1
	.byte	5
	.byte	90
	.byte	-115
	.space	1
	.byte	2
	.byte	61
	.byte	95
	.space	1
	.byte	1
	.byte	37
	.byte	57
	.space	1
	.space	8
	.byte	33
	.byte	-77
	.byte	-36
	.space	1
	.byte	11
	.byte	-116
	.byte	-58
	.space	1
	.byte	1
	.byte	89
	.byte	-108
	.space	1
	.byte	1
	.byte	60
	.byte	104
	.space	1
	.byte	1
	.byte	33
	.byte	57
	.space	1
	.byte	1
	.byte	12
	.byte	21
	.space	1
	.space	8
	.byte	30
	.byte	-75
	.byte	-35
	.space	1
	.byte	8
	.byte	-115
	.byte	-58
	.space	1
	.byte	1
	.byte	87
	.byte	-111
	.space	1
	.byte	1
	.byte	58
	.byte	100
	.space	1
	.byte	1
	.byte	31
	.byte	55
	.space	1
	.byte	1
	.byte	12
	.byte	20
	.space	1
	.space	8
	.byte	32
	.byte	-70
	.byte	-32
	.space	1
	.byte	7
	.byte	-114
	.byte	-58
	.space	1
	.byte	1
	.byte	86
	.byte	-113
	.space	1
	.byte	1
	.byte	58
	.byte	100
	.space	1
	.byte	1
	.byte	31
	.byte	55
	.space	1
	.byte	1
	.byte	12
	.byte	22
	.space	1
	.space	8
	.byte	57
	.byte	-64
	.byte	-29
	.space	1
	.byte	20
	.byte	-113
	.byte	-52
	.space	1
	.byte	3
	.byte	96
	.byte	-102
	.space	1
	.byte	1
	.byte	68
	.byte	112
	.space	1
	.byte	1
	.byte	42
	.byte	69
	.space	1
	.byte	1
	.byte	19
	.byte	32
	.space	1
	.space	8
	.space	64
	.byte	-44
	.byte	35
	.byte	-41
	.space	1
	.byte	113
	.byte	47
	.byte	-87
	.space	1
	.byte	29
	.byte	48
	.byte	105
	.space	1
	.space	20
	.byte	74
	.byte	-127
	.byte	-53
	.space	1
	.byte	106
	.byte	120
	.byte	-53
	.space	1
	.byte	49
	.byte	107
	.byte	-78
	.space	1
	.byte	19
	.byte	84
	.byte	-112
	.space	1
	.byte	4
	.byte	50
	.byte	84
	.space	1
	.byte	1
	.byte	15
	.byte	25
	.space	1
	.space	8
	.byte	71
	.byte	-84
	.byte	-39
	.space	1
	.byte	44
	.byte	-115
	.byte	-47
	.space	1
	.byte	15
	.byte	102
	.byte	-83
	.space	1
	.byte	6
	.byte	76
	.byte	-123
	.space	1
	.byte	2
	.byte	51
	.byte	89
	.space	1
	.byte	1
	.byte	24
	.byte	42
	.space	1
	.space	8
	.byte	64
	.byte	-71
	.byte	-25
	.space	1
	.byte	31
	.byte	-108
	.byte	-40
	.space	1
	.byte	8
	.byte	103
	.byte	-81
	.space	1
	.byte	3
	.byte	74
	.byte	-125
	.space	1
	.byte	1
	.byte	46
	.byte	81
	.space	1
	.byte	1
	.byte	18
	.byte	30
	.space	1
	.space	8
	.byte	65
	.byte	-60
	.byte	-21
	.space	1
	.byte	25
	.byte	-99
	.byte	-35
	.space	1
	.byte	5
	.byte	105
	.byte	-82
	.space	1
	.byte	1
	.byte	67
	.byte	120
	.space	1
	.byte	1
	.byte	38
	.byte	69
	.space	1
	.byte	1
	.byte	15
	.byte	30
	.space	1
	.space	8
	.byte	65
	.byte	-52
	.byte	-18
	.space	1
	.byte	30
	.byte	-100
	.byte	-32
	.space	1
	.byte	7
	.byte	107
	.byte	-79
	.space	1
	.byte	2
	.byte	70
	.byte	124
	.space	1
	.byte	1
	.byte	42
	.byte	73
	.space	1
	.byte	1
	.byte	18
	.byte	34
	.space	1
	.space	8
	.space	64
	.byte	-31
	.byte	86
	.byte	-5
	.space	1
	.byte	-112
	.byte	104
	.byte	-21
	.space	1
	.byte	42
	.byte	99
	.byte	-75
	.space	1
	.space	20
	.byte	85
	.byte	-81
	.byte	-17
	.space	1
	.byte	112
	.byte	-91
	.byte	-27
	.space	1
	.byte	29
	.byte	-120
	.byte	-56
	.space	1
	.byte	12
	.byte	103
	.byte	-94
	.space	1
	.byte	6
	.byte	77
	.byte	123
	.space	1
	.byte	2
	.byte	53
	.byte	84
	.space	1
	.space	8
	.byte	75
	.byte	-73
	.byte	-17
	.space	1
	.byte	30
	.byte	-101
	.byte	-35
	.space	1
	.byte	3
	.byte	106
	.byte	-85
	.space	1
	.byte	1
	.byte	74
	.byte	-128
	.space	1
	.byte	1
	.byte	44
	.byte	76
	.space	1
	.byte	1
	.byte	17
	.byte	28
	.space	1
	.space	8
	.byte	73
	.byte	-71
	.byte	-16
	.space	1
	.byte	27
	.byte	-97
	.byte	-34
	.space	1
	.byte	2
	.byte	107
	.byte	-84
	.space	1
	.byte	1
	.byte	75
	.byte	127
	.space	1
	.byte	1
	.byte	42
	.byte	73
	.space	1
	.byte	1
	.byte	17
	.byte	29
	.space	1
	.space	8
	.byte	62
	.byte	-66
	.byte	-18
	.space	1
	.byte	21
	.byte	-97
	.byte	-34
	.space	1
	.byte	2
	.byte	107
	.byte	-84
	.space	1
	.byte	1
	.byte	72
	.byte	122
	.space	1
	.byte	1
	.byte	40
	.byte	71
	.space	1
	.byte	1
	.byte	18
	.byte	32
	.space	1
	.space	8
	.byte	61
	.byte	-57
	.byte	-16
	.space	1
	.byte	27
	.byte	-95
	.byte	-30
	.space	1
	.byte	4
	.byte	113
	.byte	-76
	.space	1
	.byte	1
	.byte	76
	.byte	-127
	.space	1
	.byte	1
	.byte	46
	.byte	80
	.space	1
	.byte	1
	.byte	23
	.byte	41
	.space	1
	.space	8
	.space	64
	.type	vp9_default_coef_probs_16x16, %object
	.size	vp9_default_coef_probs_16x16, 1024
vp9_default_coef_probs_16x16:
	.byte	7
	.byte	27
	.byte	-103
	.space	1
	.byte	5
	.byte	30
	.byte	95
	.space	1
	.byte	1
	.byte	16
	.byte	30
	.space	1
	.space	20
	.byte	50
	.byte	75
	.byte	127
	.space	1
	.byte	57
	.byte	75
	.byte	124
	.space	1
	.byte	27
	.byte	67
	.byte	108
	.space	1
	.byte	10
	.byte	54
	.byte	86
	.space	1
	.byte	1
	.byte	33
	.byte	52
	.space	1
	.byte	1
	.byte	12
	.byte	18
	.space	1
	.space	8
	.byte	43
	.byte	125
	.byte	-105
	.space	1
	.byte	26
	.byte	108
	.byte	-108
	.space	1
	.byte	7
	.byte	83
	.byte	122
	.space	1
	.byte	2
	.byte	59
	.byte	89
	.space	1
	.byte	1
	.byte	38
	.byte	60
	.space	1
	.byte	1
	.byte	17
	.byte	27
	.space	1
	.space	8
	.byte	23
	.byte	-112
	.byte	-93
	.space	1
	.byte	13
	.byte	112
	.byte	-102
	.space	1
	.byte	2
	.byte	75
	.byte	117
	.space	1
	.byte	1
	.byte	50
	.byte	81
	.space	1
	.byte	1
	.byte	31
	.byte	51
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.byte	18
	.byte	-94
	.byte	-71
	.space	1
	.byte	6
	.byte	123
	.byte	-85
	.space	1
	.byte	1
	.byte	78
	.byte	125
	.space	1
	.byte	1
	.byte	51
	.byte	86
	.space	1
	.byte	1
	.byte	31
	.byte	54
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.byte	15
	.byte	-57
	.byte	-29
	.space	1
	.byte	3
	.byte	-106
	.byte	-52
	.space	1
	.byte	1
	.byte	91
	.byte	-110
	.space	1
	.byte	1
	.byte	55
	.byte	95
	.space	1
	.byte	1
	.byte	30
	.byte	53
	.space	1
	.byte	1
	.byte	11
	.byte	20
	.space	1
	.space	8
	.space	64
	.byte	19
	.byte	55
	.byte	-16
	.space	1
	.byte	19
	.byte	59
	.byte	-60
	.space	1
	.byte	3
	.byte	52
	.byte	105
	.space	1
	.space	20
	.byte	41
	.byte	-90
	.byte	-49
	.space	1
	.byte	104
	.byte	-103
	.byte	-57
	.space	1
	.byte	31
	.byte	123
	.byte	-75
	.space	1
	.byte	14
	.byte	101
	.byte	-104
	.space	1
	.byte	5
	.byte	72
	.byte	106
	.space	1
	.byte	1
	.byte	36
	.byte	52
	.space	1
	.space	8
	.byte	35
	.byte	-80
	.byte	-45
	.space	1
	.byte	12
	.byte	-125
	.byte	-66
	.space	1
	.byte	2
	.byte	88
	.byte	-112
	.space	1
	.byte	1
	.byte	60
	.byte	101
	.space	1
	.byte	1
	.byte	36
	.byte	60
	.space	1
	.byte	1
	.byte	16
	.byte	28
	.space	1
	.space	8
	.byte	28
	.byte	-73
	.byte	-43
	.space	1
	.byte	8
	.byte	-122
	.byte	-65
	.space	1
	.byte	1
	.byte	86
	.byte	-114
	.space	1
	.byte	1
	.byte	56
	.byte	96
	.space	1
	.byte	1
	.byte	30
	.byte	53
	.space	1
	.byte	1
	.byte	12
	.byte	20
	.space	1
	.space	8
	.byte	20
	.byte	-66
	.byte	-41
	.space	1
	.byte	4
	.byte	-121
	.byte	-64
	.space	1
	.byte	1
	.byte	84
	.byte	-117
	.space	1
	.byte	1
	.byte	53
	.byte	91
	.space	1
	.byte	1
	.byte	28
	.byte	49
	.space	1
	.byte	1
	.byte	11
	.byte	20
	.space	1
	.space	8
	.byte	13
	.byte	-60
	.byte	-40
	.space	1
	.byte	2
	.byte	-119
	.byte	-64
	.space	1
	.byte	1
	.byte	86
	.byte	-113
	.space	1
	.byte	1
	.byte	57
	.byte	99
	.space	1
	.byte	1
	.byte	32
	.byte	56
	.space	1
	.byte	1
	.byte	13
	.byte	24
	.space	1
	.space	8
	.space	64
	.byte	-45
	.byte	29
	.byte	-39
	.space	1
	.byte	96
	.byte	47
	.byte	-100
	.space	1
	.byte	22
	.byte	43
	.byte	87
	.space	1
	.space	20
	.byte	78
	.byte	120
	.byte	-63
	.space	1
	.byte	111
	.byte	116
	.byte	-70
	.space	1
	.byte	46
	.byte	102
	.byte	-92
	.space	1
	.byte	15
	.byte	80
	.byte	-128
	.space	1
	.byte	2
	.byte	49
	.byte	76
	.space	1
	.byte	1
	.byte	18
	.byte	28
	.space	1
	.space	8
	.byte	71
	.byte	-95
	.byte	-53
	.space	1
	.byte	42
	.byte	-124
	.byte	-64
	.space	1
	.byte	10
	.byte	98
	.byte	-106
	.space	1
	.byte	3
	.byte	69
	.byte	109
	.space	1
	.byte	1
	.byte	44
	.byte	70
	.space	1
	.byte	1
	.byte	18
	.byte	29
	.space	1
	.space	8
	.byte	57
	.byte	-70
	.byte	-45
	.space	1
	.byte	30
	.byte	-116
	.byte	-60
	.space	1
	.byte	4
	.byte	93
	.byte	-110
	.space	1
	.byte	1
	.byte	62
	.byte	102
	.space	1
	.byte	1
	.byte	38
	.byte	65
	.space	1
	.byte	1
	.byte	16
	.byte	27
	.space	1
	.space	8
	.byte	47
	.byte	-57
	.byte	-39
	.space	1
	.byte	14
	.byte	-111
	.byte	-60
	.space	1
	.byte	1
	.byte	88
	.byte	-114
	.space	1
	.byte	1
	.byte	57
	.byte	98
	.space	1
	.byte	1
	.byte	36
	.byte	62
	.space	1
	.byte	1
	.byte	15
	.byte	26
	.space	1
	.space	8
	.byte	26
	.byte	-37
	.byte	-27
	.space	1
	.byte	5
	.byte	-101
	.byte	-49
	.space	1
	.byte	1
	.byte	94
	.byte	-105
	.space	1
	.byte	1
	.byte	60
	.byte	104
	.space	1
	.byte	1
	.byte	36
	.byte	62
	.space	1
	.byte	1
	.byte	16
	.byte	28
	.space	1
	.space	8
	.space	64
	.byte	-23
	.byte	29
	.byte	-8
	.space	1
	.byte	-110
	.byte	47
	.byte	-36
	.space	1
	.byte	43
	.byte	52
	.byte	-116
	.space	1
	.space	20
	.byte	100
	.byte	-93
	.byte	-24
	.space	1
	.byte	-77
	.byte	-95
	.byte	-34
	.space	1
	.byte	63
	.byte	-114
	.byte	-52
	.space	1
	.byte	37
	.byte	113
	.byte	-82
	.space	1
	.byte	26
	.byte	89
	.byte	-119
	.space	1
	.byte	18
	.byte	68
	.byte	97
	.space	1
	.space	8
	.byte	85
	.byte	-75
	.byte	-26
	.space	1
	.byte	32
	.byte	-110
	.byte	-47
	.space	1
	.byte	7
	.byte	100
	.byte	-92
	.space	1
	.byte	3
	.byte	71
	.byte	121
	.space	1
	.byte	1
	.byte	45
	.byte	77
	.space	1
	.byte	1
	.byte	18
	.byte	30
	.space	1
	.space	8
	.byte	65
	.byte	-69
	.byte	-26
	.space	1
	.byte	20
	.byte	-108
	.byte	-49
	.space	1
	.byte	2
	.byte	97
	.byte	-97
	.space	1
	.byte	1
	.byte	68
	.byte	116
	.space	1
	.byte	1
	.byte	40
	.byte	70
	.space	1
	.byte	1
	.byte	14
	.byte	29
	.space	1
	.space	8
	.byte	40
	.byte	-62
	.byte	-29
	.space	1
	.byte	8
	.byte	-109
	.byte	-52
	.space	1
	.byte	1
	.byte	94
	.byte	-101
	.space	1
	.byte	1
	.byte	65
	.byte	112
	.space	1
	.byte	1
	.byte	39
	.byte	66
	.space	1
	.byte	1
	.byte	14
	.byte	26
	.space	1
	.space	8
	.byte	16
	.byte	-48
	.byte	-28
	.space	1
	.byte	3
	.byte	-105
	.byte	-49
	.space	1
	.byte	1
	.byte	98
	.byte	-96
	.space	1
	.byte	1
	.byte	67
	.byte	117
	.space	1
	.byte	1
	.byte	41
	.byte	74
	.space	1
	.byte	1
	.byte	17
	.byte	31
	.space	1
	.space	8
	.space	64
	.type	vp9_default_coef_probs_32x32, %object
	.size	vp9_default_coef_probs_32x32, 1024
vp9_default_coef_probs_32x32:
	.byte	17
	.byte	38
	.byte	-116
	.space	1
	.byte	7
	.byte	34
	.byte	80
	.space	1
	.byte	1
	.byte	17
	.byte	29
	.space	1
	.space	20
	.byte	37
	.byte	75
	.byte	-128
	.space	1
	.byte	41
	.byte	76
	.byte	-128
	.space	1
	.byte	26
	.byte	66
	.byte	116
	.space	1
	.byte	12
	.byte	52
	.byte	94
	.space	1
	.byte	2
	.byte	32
	.byte	55
	.space	1
	.byte	1
	.byte	10
	.byte	16
	.space	1
	.space	8
	.byte	50
	.byte	127
	.byte	-102
	.space	1
	.byte	37
	.byte	109
	.byte	-104
	.space	1
	.byte	16
	.byte	82
	.byte	121
	.space	1
	.byte	5
	.byte	59
	.byte	85
	.space	1
	.byte	1
	.byte	35
	.byte	54
	.space	1
	.byte	1
	.byte	13
	.byte	20
	.space	1
	.space	8
	.byte	40
	.byte	-114
	.byte	-89
	.space	1
	.byte	17
	.byte	110
	.byte	-99
	.space	1
	.byte	2
	.byte	71
	.byte	112
	.space	1
	.byte	1
	.byte	44
	.byte	72
	.space	1
	.byte	1
	.byte	27
	.byte	45
	.space	1
	.byte	1
	.byte	11
	.byte	17
	.space	1
	.space	8
	.byte	30
	.byte	-81
	.byte	-68
	.space	1
	.byte	9
	.byte	124
	.byte	-87
	.space	1
	.byte	1
	.byte	74
	.byte	116
	.space	1
	.byte	1
	.byte	48
	.byte	78
	.space	1
	.byte	1
	.byte	30
	.byte	49
	.space	1
	.byte	1
	.byte	11
	.byte	18
	.space	1
	.space	8
	.byte	10
	.byte	-34
	.byte	-33
	.space	1
	.byte	2
	.byte	-106
	.byte	-62
	.space	1
	.byte	1
	.byte	83
	.byte	-128
	.space	1
	.byte	1
	.byte	48
	.byte	79
	.space	1
	.byte	1
	.byte	27
	.byte	45
	.space	1
	.byte	1
	.byte	11
	.byte	17
	.space	1
	.space	8
	.space	64
	.byte	36
	.byte	41
	.byte	-21
	.space	1
	.byte	29
	.byte	36
	.byte	-63
	.space	1
	.byte	10
	.byte	27
	.byte	111
	.space	1
	.space	20
	.byte	85
	.byte	-91
	.byte	-34
	.space	1
	.byte	-79
	.byte	-94
	.byte	-41
	.space	1
	.byte	110
	.byte	-121
	.byte	-61
	.space	1
	.byte	57
	.byte	113
	.byte	-88
	.space	1
	.byte	23
	.byte	83
	.byte	120
	.space	1
	.byte	10
	.byte	49
	.byte	61
	.space	1
	.space	8
	.byte	85
	.byte	-66
	.byte	-33
	.space	1
	.byte	36
	.byte	-117
	.byte	-56
	.space	1
	.byte	5
	.byte	90
	.byte	-110
	.space	1
	.byte	1
	.byte	60
	.byte	103
	.space	1
	.byte	1
	.byte	38
	.byte	65
	.space	1
	.byte	1
	.byte	18
	.byte	30
	.space	1
	.space	8
	.byte	72
	.byte	-54
	.byte	-33
	.space	1
	.byte	23
	.byte	-115
	.byte	-57
	.space	1
	.byte	2
	.byte	86
	.byte	-116
	.space	1
	.byte	1
	.byte	56
	.byte	97
	.space	1
	.byte	1
	.byte	36
	.byte	61
	.space	1
	.byte	1
	.byte	16
	.byte	27
	.space	1
	.space	8
	.byte	55
	.byte	-38
	.byte	-31
	.space	1
	.byte	13
	.byte	-111
	.byte	-56
	.space	1
	.byte	1
	.byte	86
	.byte	-115
	.space	1
	.byte	1
	.byte	57
	.byte	99
	.space	1
	.byte	1
	.byte	35
	.byte	61
	.space	1
	.byte	1
	.byte	13
	.byte	22
	.space	1
	.space	8
	.byte	15
	.byte	-21
	.byte	-44
	.space	1
	.byte	1
	.byte	-124
	.byte	-72
	.space	1
	.byte	1
	.byte	84
	.byte	-117
	.space	1
	.byte	1
	.byte	57
	.byte	97
	.space	1
	.byte	1
	.byte	34
	.byte	56
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.space	64
	.byte	-75
	.byte	21
	.byte	-55
	.space	1
	.byte	61
	.byte	37
	.byte	123
	.space	1
	.byte	10
	.byte	38
	.byte	71
	.space	1
	.space	20
	.byte	47
	.byte	106
	.byte	-84
	.space	1
	.byte	95
	.byte	104
	.byte	-83
	.space	1
	.byte	42
	.byte	93
	.byte	-97
	.space	1
	.byte	18
	.byte	77
	.byte	-125
	.space	1
	.byte	4
	.byte	50
	.byte	81
	.space	1
	.byte	1
	.byte	17
	.byte	23
	.space	1
	.space	8
	.byte	62
	.byte	-109
	.byte	-57
	.space	1
	.byte	44
	.byte	-126
	.byte	-67
	.space	1
	.byte	28
	.byte	102
	.byte	-102
	.space	1
	.byte	18
	.byte	75
	.byte	115
	.space	1
	.byte	2
	.byte	44
	.byte	65
	.space	1
	.byte	1
	.byte	12
	.byte	19
	.space	1
	.space	8
	.byte	55
	.byte	-103
	.byte	-46
	.space	1
	.byte	24
	.byte	-126
	.byte	-62
	.space	1
	.byte	3
	.byte	93
	.byte	-110
	.space	1
	.byte	1
	.byte	61
	.byte	97
	.space	1
	.byte	1
	.byte	31
	.byte	50
	.space	1
	.byte	1
	.byte	10
	.byte	16
	.space	1
	.space	8
	.byte	49
	.byte	-70
	.byte	-33
	.space	1
	.byte	17
	.byte	-108
	.byte	-52
	.space	1
	.byte	1
	.byte	96
	.byte	-114
	.space	1
	.byte	1
	.byte	53
	.byte	83
	.space	1
	.byte	1
	.byte	26
	.byte	44
	.space	1
	.byte	1
	.byte	11
	.byte	17
	.space	1
	.space	8
	.byte	13
	.byte	-39
	.byte	-44
	.space	1
	.byte	2
	.byte	-120
	.byte	-76
	.space	1
	.byte	1
	.byte	78
	.byte	124
	.space	1
	.byte	1
	.byte	50
	.byte	83
	.space	1
	.byte	1
	.byte	29
	.byte	49
	.space	1
	.byte	1
	.byte	14
	.byte	23
	.space	1
	.space	8
	.space	64
	.byte	-59
	.byte	13
	.byte	-9
	.space	1
	.byte	82
	.byte	17
	.byte	-34
	.space	1
	.byte	25
	.byte	17
	.byte	-94
	.space	1
	.space	20
	.byte	126
	.byte	-70
	.byte	-9
	.space	1
	.byte	-22
	.byte	-65
	.byte	-13
	.space	1
	.byte	-80
	.byte	-79
	.byte	-22
	.space	1
	.byte	104
	.byte	-98
	.byte	-36
	.space	1
	.byte	66
	.byte	-128
	.byte	-70
	.space	1
	.byte	55
	.byte	90
	.byte	-119
	.space	1
	.space	8
	.byte	111
	.byte	-59
	.byte	-14
	.space	1
	.byte	46
	.byte	-98
	.byte	-37
	.space	1
	.byte	9
	.byte	104
	.byte	-85
	.space	1
	.byte	2
	.byte	65
	.byte	125
	.space	1
	.byte	1
	.byte	44
	.byte	80
	.space	1
	.byte	1
	.byte	17
	.byte	91
	.space	1
	.space	8
	.byte	104
	.byte	-48
	.byte	-11
	.space	1
	.byte	39
	.byte	-88
	.byte	-32
	.space	1
	.byte	3
	.byte	109
	.byte	-94
	.space	1
	.byte	1
	.byte	79
	.byte	124
	.space	1
	.byte	1
	.byte	50
	.byte	102
	.space	1
	.byte	1
	.byte	43
	.byte	102
	.space	1
	.space	8
	.byte	84
	.byte	-36
	.byte	-10
	.space	1
	.byte	31
	.byte	-79
	.byte	-25
	.space	1
	.byte	2
	.byte	115
	.byte	-76
	.space	1
	.byte	1
	.byte	79
	.byte	-122
	.space	1
	.byte	1
	.byte	55
	.byte	77
	.space	1
	.byte	1
	.byte	60
	.byte	79
	.space	1
	.space	8
	.byte	43
	.byte	-13
	.byte	-16
	.space	1
	.byte	8
	.byte	-76
	.byte	-39
	.space	1
	.byte	1
	.byte	115
	.byte	-90
	.space	1
	.byte	1
	.byte	84
	.byte	121
	.space	1
	.byte	1
	.byte	51
	.byte	67
	.space	1
	.byte	1
	.byte	16
	.byte	6
	.space	1
	.space	8
	.space	64
	.type	vp9_default_if_uv_probs, %object
	.size	vp9_default_if_uv_probs, 160
vp9_default_if_uv_probs:
	.byte	120
	.byte	7
	.byte	76
	.byte	-80
	.byte	-48
	.byte	126
	.byte	28
	.byte	54
	.byte	103
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	48
	.byte	12
	.byte	-102
	.byte	-101
	.byte	-117
	.byte	90
	.byte	34
	.byte	117
	.byte	119
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	67
	.byte	6
	.byte	25
	.byte	-52
	.byte	-13
	.byte	-98
	.byte	13
	.byte	21
	.byte	96
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	97
	.byte	5
	.byte	44
	.byte	-125
	.byte	-80
	.byte	-117
	.byte	48
	.byte	68
	.byte	97
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	83
	.byte	5
	.byte	42
	.byte	-100
	.byte	111
	.byte	-104
	.byte	26
	.byte	49
	.byte	-104
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	80
	.byte	5
	.byte	58
	.byte	-78
	.byte	74
	.byte	83
	.byte	33
	.byte	62
	.byte	-111
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	86
	.byte	5
	.byte	32
	.byte	-102
	.byte	-64
	.byte	-88
	.byte	14
	.byte	22
	.byte	-93
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	85
	.byte	5
	.byte	32
	.byte	-100
	.byte	-40
	.byte	-108
	.byte	19
	.byte	29
	.byte	73
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	77
	.byte	7
	.byte	64
	.byte	116
	.byte	-124
	.byte	122
	.byte	37
	.byte	126
	.byte	120
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	101
	.byte	21
	.byte	107
	.byte	-75
	.byte	-64
	.byte	103
	.byte	19
	.byte	67
	.byte	125
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	vp9_default_if_y_probs, %object
	.size	vp9_default_if_y_probs, 64
vp9_default_if_y_probs:
	.byte	65
	.byte	32
	.byte	18
	.byte	-112
	.byte	-94
	.byte	-62
	.byte	41
	.byte	51
	.byte	98
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-124
	.byte	68
	.byte	18
	.byte	-91
	.byte	-39
	.byte	-60
	.byte	45
	.byte	40
	.byte	78
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-83
	.byte	80
	.byte	19
	.byte	-80
	.byte	-16
	.byte	-63
	.byte	64
	.byte	35
	.byte	46
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-35
	.byte	-121
	.byte	38
	.byte	-62
	.byte	-8
	.byte	121
	.byte	96
	.byte	85
	.byte	29
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	vp9_default_switchable_interp_prob, %object
	.size	vp9_default_switchable_interp_prob, 8
vp9_default_switchable_interp_prob:
	.byte	-21
	.byte	-94
	.byte	36
	.byte	-1
	.byte	34
	.byte	3
	.byte	-107
	.byte	-112
	.type	vp9_default_partition_probs, %object
	.size	vp9_default_partition_probs, 96
vp9_default_partition_probs:
	.byte	-98
	.byte	97
	.byte	94
	.byte	93
	.byte	24
	.byte	99
	.byte	85
	.byte	119
	.byte	44
	.byte	62
	.byte	59
	.byte	67
	.byte	-107
	.byte	53
	.byte	53
	.byte	94
	.byte	20
	.byte	48
	.byte	83
	.byte	53
	.byte	24
	.byte	52
	.byte	18
	.byte	18
	.byte	-106
	.byte	40
	.byte	39
	.byte	78
	.byte	12
	.byte	26
	.byte	67
	.byte	33
	.byte	11
	.byte	24
	.byte	7
	.byte	5
	.byte	-82
	.byte	35
	.byte	49
	.byte	68
	.byte	11
	.byte	27
	.byte	57
	.byte	15
	.byte	9
	.byte	12
	.byte	3
	.byte	3
	.byte	-57
	.byte	122
	.byte	-115
	.byte	-109
	.byte	63
	.byte	-97
	.byte	-108
	.byte	-123
	.byte	118
	.byte	121
	.byte	104
	.byte	114
	.byte	-82
	.byte	73
	.byte	87
	.byte	92
	.byte	41
	.byte	83
	.byte	82
	.byte	99
	.byte	50
	.byte	53
	.byte	39
	.byte	39
	.byte	-79
	.byte	58
	.byte	59
	.byte	68
	.byte	26
	.byte	63
	.byte	52
	.byte	79
	.byte	25
	.byte	17
	.byte	14
	.byte	12
	.byte	-34
	.byte	34
	.byte	30
	.byte	72
	.byte	16
	.byte	44
	.byte	58
	.byte	32
	.byte	12
	.byte	10
	.byte	7
	.byte	6
	.type	vp9_default_intra_inter_p, %object
	.size	vp9_default_intra_inter_p, 4
vp9_default_intra_inter_p:
	.byte	9
	.byte	102
	.byte	-69
	.byte	-31
	.type	vp9_default_comp_inter_p, %object
	.size	vp9_default_comp_inter_p, 5
vp9_default_comp_inter_p:
	.byte	-17
	.byte	-73
	.byte	119
	.byte	96
	.byte	41
	.space	3
	.type	vp9_default_comp_ref_p, %object
	.size	vp9_default_comp_ref_p, 5
vp9_default_comp_ref_p:
	.byte	50
	.byte	126
	.byte	123
	.byte	-35
	.byte	-30
	.space	3
	.type	vp9_default_single_ref_p, %object
	.size	vp9_default_single_ref_p, 10
vp9_default_single_ref_p:
	.byte	33
	.byte	16
	.byte	77
	.byte	74
	.byte	-114
	.byte	-114
	.byte	-84
	.byte	-86
	.byte	-18
	.byte	-9
	.space	2
	.type	vp9_default_mbskip_probs, %object
	.size	vp9_default_mbskip_probs, 3
vp9_default_mbskip_probs:
	.byte	-64
	.byte	-128
	.byte	64
	.space	1
	.type	vp9_default_inter_mode_probs, %object
	.size	vp9_default_inter_mode_probs, 21
vp9_default_inter_mode_probs:
	.byte	2
	.byte	-83
	.byte	34
	.byte	7
	.byte	-111
	.byte	85
	.byte	7
	.byte	-90
	.byte	63
	.byte	7
	.byte	94
	.byte	66
	.byte	8
	.byte	64
	.byte	46
	.byte	17
	.byte	81
	.byte	31
	.byte	25
	.byte	29
	.byte	30
	.space	3
	.type	g_CfgVp9FrmNum, %object
	.size	g_CfgVp9FrmNum, 4
g_CfgVp9FrmNum:
	.word	9
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	ASCII(.ascii	"IN VP9DEC_Init\012\000" )
.LC2:
	ASCII(.ascii	"line: %d,Invalid pointer!\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC4:
	ASCII(.ascii	"data_sz == 0\012\000" )
	.space	2
.LC5:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"line: %d, fs is NULL!\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"%s  idx=%d\012\000" )
.LC11:
	ASCII(.ascii	"FSP_GetLogicFs err\000" )
	.space	1
.LC12:
	ASCII(.ascii	"fsp.c,L%d: %s\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"line: %d,pCtx is NULL!\012\000" )
.LC14:
	ASCII(.ascii	"pCurImg is null\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"err_level(%d) over ref_thr(%d)\012\000" )
.LC16:
	ASCII(.ascii	"line: %d pToQueImg is null\012\000" )
.LC17:
	ASCII(.ascii	"insert img to Voqueue failed!\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"pu8ProbCntVir == NULL\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"line: %d, pCtx is NULL!\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"Invalid frame sync code\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"ref_deltas\000" )
	.space	1
.LC22:
	ASCII(.ascii	"mode_deltas\000" )
.LC23:
	ASCII(.ascii	"delta_q\000" )
.LC24:
	ASCII(.ascii	"%s  %d ERR\012\000" )
.LC25:
	ASCII(.ascii	"%s:%d this_size:%d is invalid!\012\000" )
.LC26:
	ASCII(.ascii	"4:4:4 color is not supported in profile 0 or 2 (%s " )
	ASCII(.ascii	": %d)\012\000" )
	.space	2
.LC27:
	ASCII(.ascii	"Invalid frame marker\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"%s:%d w&h=%dx%d is invalid!\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"VP9_Set_DecParam but logic fs is null!\012\000" )
.LC30:
	ASCII(.ascii	"Decord FS is NULL!\012\000" )
.LC31:
	ASCII(.ascii	"VP9_Set_DecParam but cur logic pstDecodeFs is null!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC33:
	ASCII(.ascii	"pic_width_in_pix:%d, pic_height_in_pix:%d\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"vp9 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC35:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"vp9 alloc frame only\012\000" )
	.space	2
.LC38:
	ASCII(.ascii	"%s:%d size is invalid  size:%d bslen:%d\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"ERROR:Vp9_ReadCompressedHeader\012\000" )
.LC40:
	ASCII(.ascii	"get_free_fb failed!\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"bit_depth(%d) > 10.\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"ERROR: pCtx->StreamParam.Length(%d) < 8\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"widthxheight exceed %d x %d\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"%dx%d, all=%d,cur=%d,ref=%d,ned=%d\012\000" )
.LC45:
	ASCII(.ascii	"ERROR: No Img buffer is allocated\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"%s %d, no fsp\012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"VP9_GetImageBuffer From Queue err\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"ERROR: VP9_Set_DecParam\012\000" )
	.space	3
.LC49:
	ASCII(.ascii	"VP9_DecOneNal ERR\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
