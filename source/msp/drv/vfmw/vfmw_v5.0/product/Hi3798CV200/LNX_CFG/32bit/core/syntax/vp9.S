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
	.global	__aeabi_uidiv
	.text
	.align	2
	.type	Vp9_ModeMvMergeProbs, %function
Vp9_ModeMvMergeProbs:
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
	mov	r4, r0
	ldmia	r1, {r0, r1}
	adds	r3, r0, r1
	beq	.L3
	cmp	r3, #20
	ldr	r2, .L5
	mov	r0, r0, asl #8
	mov	r1, r3
	add	r0, r0, r3, lsr #1
	movcs	r3, #20
	ldrb	r5, [r2, r3]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	rsb	r3, r5, #256
	mul	r4, r4, r3
	add	r4, r4, #128
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r0, r0
	mla	r0, r5, r0, r4
	ubfx	r0, r0, #8, #8
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ModeMvMergeProbs, .-Vp9_ModeMvMergeProbs
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
	beq	.L13
	cmp	r1, #0
	ble	.L14
	add	r0, r0, r1
	cmp	r2, r0
	movcc	r0, #0
	movcs	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L13:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L14:
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
	blt	.L17
	ldr	r3, [r0, #28]
.L18:
	mov	r2, r4, asl #24
	cmp	r2, r3
	rsbls	r3, r2, r3
	ldr	r2, .L21
	ldrls	r1, [r5, #36]
	movls	r0, #1
	movhi	r0, #0
	rsbls	r4, r4, r1
	add	r2, r2, r4
	ldrb	r1, [r2, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r1
	rsb	r6, r1, r6
	mov	r4, r4, asl r1
	str	r3, [r5, #28]
	str	r6, [r5, #32]
	str	r4, [r5, #36]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L17:
	rsb	r1, r6, #24
	rsb	r8, r6, #16
	bic	r1, r1, #7
	ldr	r7, [r0, #28]
	rsb	r8, r1, r8
	add	r6, r6, r1
	bl	BsGet
	and	r3, r8, #7
	orr	r3, r7, r0, asl r3
	b	.L18
.L22:
	.align	2
.L21:
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
	bmi	.L28
	ldr	r8, [r0, #28]
	mov	r9, #0
	ldr	r4, [r0, #36]
	mov	r3, #1
	ldr	r5, [r0, #32]
	ldr	r10, .L32
	b	.L27
.L25:
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
	add	r2, r10, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L24
.L27:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L25
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
	b	.L25
.L28:
	mov	r9, #0
.L24:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L33:
	.align	2
.L32:
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
	ldr	r1, .L37
	rsbcs	r3, r3, r0
	movcc	r0, r5
	add	r1, r1, r3
	movcs	r0, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r2, r2, asl r1
	mov	r3, r3, asl r1
	str	r2, [r4, #28]
	rsb	r1, r1, #24
	str	r3, [r4, #36]
	str	r1, [r4, #32]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L38:
	.align	2
.L37:
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
	ldr	r10, .L53
	ldr	r4, [r0, #36]
	mov	r3, r7
	ldr	r5, [r0, #32]
	mov	r9, #0
	ldr	r8, [r0, #28]
	b	.L42
.L40:
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
	add	r2, r10, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L50
.L42:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L40
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
	b	.L40
.L50:
	cmp	r9, #3
	beq	.L51
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L51:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	add	r4, r4, #1
	movge	r0, r8
	blt	.L52
.L44:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r2, [r6, #36]
	movls	r9, #4
	rsbls	r4, r4, r2
	add	r10, r10, r4
	ldrb	r3, [r10, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	mov	r0, r9
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L52:
	rsb	r1, r5, #24
	rsb	r7, r5, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r7, r1, r7
	add	r5, r1, r5
	bl	BsGet
	and	r7, r7, #7
	orr	r0, r8, r0, asl r7
	b	.L44
.L54:
	.align	2
.L53:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_ReadTxMode, .-Vp9_ReadTxMode
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
	blt	.L57
	ldr	r7, [r0, #28]
.L58:
	mov	r0, r10, asl #24
	cmp	r0, r7
	bhi	.L59
	ldr	r4, [r6, #36]
	rsb	r7, r0, r7
	ldr	r8, .L112
	rsb	r4, r10, r4
	add	r3, r8, r4
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L106
.L61:
	mov	r10, r4, asl #24
	cmp	r10, r7
	bhi	.L66
	ldr	r1, [r6, #36]
	rsb	r7, r10, r7
	rsb	r4, r4, r1
	add	r3, r8, r4
	ldrb	r10, [r3, #24]	@ zero_extendqisi2
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
	blt	.L107
.L68:
	mov	r3, r4, asl #24
	cmp	r3, r10
	bhi	.L72
	ldr	r1, [r6, #36]
	rsb	r10, r3, r10
	mov	r3, #6
	mov	r9, #0
	rsb	r4, r4, r1
	mov	r2, #1
	add	r1, r8, r4
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	rsb	r7, r1, r5
	mov	r10, r10, asl r1
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r7, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L73
.L77:
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
	add	r3, r8, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r10, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
	beq	.L108
.L73:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L77
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
	b	.L77
.L66:
	add	r1, r8, r4
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r7, r7, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L71
.L69:
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
	add	r3, r8, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L109
.L71:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L69
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
	b	.L69
.L59:
	ldr	r8, .L112
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	add	r1, r8, r10
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r7, [r6, #28]
	mov	r4, r10, asl r4
	str	r5, [r6, #32]
	mov	r10, r3
	str	r4, [r6, #36]
	b	.L64
.L62:
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
	add	r3, r8, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L65
.L64:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L62
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
	b	.L62
.L108:
	cmp	r9, #64
	ble	.L79
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r9, r9, asl #1
	add	r4, r4, #1
	sub	r9, r9, #65
	movge	r0, r10
	blt	.L110
.L80:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldrls	r1, [r6, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r9, r9, r2
	rsbls	r4, r4, r1
	add	r3, r8, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r10, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
.L79:
	add	r9, r9, #64
.L65:
	ldr	r3, [fp, #-48]
	add	r8, r8, r9
	ldrb	r1, [r8, #280]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L82
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L83
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L83:
	ldr	r2, [fp, #-48]
	add	r3, r3, #1
	strb	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L82:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L86
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L86:
	ldr	r2, [fp, #-48]
	rsb	r3, r3, #255
	strb	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L109:
	add	r9, r9, #16
	b	.L65
.L72:
	add	r2, r8, r4
	mov	r9, #0
	mov	r7, #4
	mov	r3, #1
	ldrb	r1, [r2, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r10, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L76
.L74:
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
	add	r2, r8, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L111
.L76:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L74
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
	b	.L74
.L111:
	add	r9, r9, #32
	b	.L65
.L57:
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
	b	.L58
.L106:
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
	b	.L61
.L107:
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
	b	.L68
.L110:
	rsb	r1, r7, #24
	rsb	r5, r7, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r5, r1, r5
	add	r7, r1, r7
	bl	BsGet
	and	r5, r5, #7
	orr	r0, r10, r0, asl r5
	b	.L80
.L113:
	.align	2
.L112:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp9_DiffUpdateProb, .-Vp9_DiffUpdateProb
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
	ldr	r4, [r1, #28]
	ldr	r9, [r1, #36]
	add	r8, r0, #10
	ldr	r7, [r1, #32]
	mov	r5, r1
	add	r3, r0, #12
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
.L145:
	sub	r9, r9, #1
	cmp	r7, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L354
.L115:
	mov	r6, r9, asl #24
	cmp	r6, r4
	bhi	.L116
	ldr	r3, [r5, #36]
	rsb	r6, r6, r4
	rsb	r9, r9, r3
	ldr	r3, .L400
	add	r3, r3, r9
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r7, r3, r7
	sub	r4, r9, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r6, r6, asl r3
	str	r9, [r5, #36]
	add	r10, r4, #1
	str	r7, [r5, #32]
	str	r6, [r5, #28]
	blt	.L355
.L117:
	mov	r3, r10, asl #24
	cmp	r3, r6
	bhi	.L118
	ldr	r4, [r5, #36]
	rsb	r3, r3, r6
	ldr	r2, .L400
	rsb	r4, r10, r4
	add	r2, r2, r4
	ldrb	r10, [r2, #24]	@ zero_extendqisi2
	mov	r2, r4, asl r10
	rsb	r7, r10, r7
	sub	r6, r2, #1
	cmp	r7, #0
	ubfx	r6, r6, #1, #24
	mov	r10, r3, asl r10
	str	r2, [r5, #36]
	add	r6, r6, #1
	str	r7, [r5, #32]
	str	r10, [r5, #28]
	blt	.L356
.L120:
	mov	r3, r6, asl #24
	cmp	r3, r10
	bhi	.L125
	ldr	r1, [r5, #36]
	rsb	r10, r3, r10
	ldr	r3, .L400
	rsb	r6, r6, r1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r1, r6, asl r3
	rsb	r7, r3, r7
	sub	r6, r1, #1
	cmp	r7, #0
	ubfx	r6, r6, #1, #24
	mov	r10, r10, asl r3
	str	r1, [r5, #36]
	add	r6, r6, #1
	str	r7, [r5, #32]
	str	r10, [r5, #28]
	blt	.L357
.L127:
	mov	r3, r6, asl #24
	cmp	r3, r10
	bhi	.L131
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	ldr	r1, .L400
	mov	r9, #0
	rsb	r6, r6, r4
	mov	r10, #6
	add	r1, r1, r6
	mov	r2, #1
	str	r8, [fp, #-60]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r7, r4, r7
	str	r3, [r5, #28]
	mov	r4, r6, asl r4
	str	r7, [r5, #32]
	mov	r6, r3
	str	r4, [r5, #36]
	b	.L132
.L136:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r6, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L358
.L132:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L136
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-56]
	rsb	r8, r1, r3
	add	r7, r1, r7
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-56]
	orr	r0, r6, r0, asl r3
	b	.L136
.L116:
	ldr	r3, .L400
	add	r3, r3, r9
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r7, r3, r7
	mov	r9, r9, asl r3
	str	r4, [r5, #28]
	str	r7, [r5, #32]
	str	r9, [r5, #36]
.L271:
	ldr	r3, [fp, #-48]
	add	r8, r8, #1
	cmp	r8, r3
	bne	.L145
	ldr	r3, [fp, #-52]
	add	r2, r3, #4
	str	r2, [fp, #-48]
	mov	r8, r3
	str	r3, [fp, #-56]
.L206:
	sub	r6, r9, #1
	cmp	r7, #0
	mov	r3, r6, asl #8
	sub	r6, r3, r6, asl #2
	mov	r6, r6, lsr #8
	add	r6, r6, #1
	blt	.L359
.L146:
	mov	r9, r6, asl #24
	cmp	r9, r4
	bhi	.L147
	ldr	r3, [r5, #36]
	rsb	r9, r9, r4
	rsb	r6, r6, r3
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r2, [r3, #24]	@ zero_extendqisi2
	mov	r3, r6, asl r2
	rsb	r7, r2, r7
	sub	r6, r3, #1
	cmp	r7, #0
	ubfx	r6, r6, #1, #24
	mov	r9, r9, asl r2
	str	r3, [r5, #36]
	add	r6, r6, #1
	str	r7, [r5, #32]
	str	r9, [r5, #28]
	blt	.L360
.L148:
	mov	r2, r6, asl #24
	cmp	r2, r9
	bhi	.L149
	ldr	r3, [r5, #36]
	rsb	r9, r2, r9
	rsb	r6, r6, r3
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
	mov	r3, r6, asl r0
	rsb	r4, r0, r7
	sub	r6, r3, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r9, r9, asl r0
	str	r3, [r5, #36]
	add	r6, r6, #1
	str	r4, [r5, #32]
	str	r9, [r5, #28]
	blt	.L361
.L151:
	mov	r7, r6, asl #24
	cmp	r7, r9
	bhi	.L156
	ldr	r1, [r5, #36]
	rsb	r9, r7, r9
	ldr	r3, .L400
	rsb	r6, r6, r1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r1, r6, asl r3
	rsb	r7, r3, r4
	sub	r6, r1, #1
	cmp	r7, #0
	ubfx	r6, r6, #1, #24
	mov	r9, r9, asl r3
	str	r1, [r5, #36]
	add	r6, r6, #1
	str	r7, [r5, #32]
	str	r9, [r5, #28]
	blt	.L362
.L158:
	mov	r3, r6, asl #24
	cmp	r3, r9
	bhi	.L162
	ldr	r4, [r5, #36]
	rsb	r3, r3, r9
	ldr	r1, .L400
	mov	r10, #0
	rsb	r6, r6, r4
	mov	r9, #6
	add	r1, r1, r6
	mov	r2, #1
	str	r8, [fp, #-64]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r7, r4, r7
	str	r3, [r5, #28]
	mov	r4, r6, asl r4
	str	r7, [r5, #32]
	mov	r6, r3
	str	r4, [r5, #36]
	b	.L163
.L167:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r6, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L363
.L163:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L167
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-60]
	rsb	r8, r1, r3
	add	r7, r1, r7
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-60]
	orr	r0, r6, r0, asl r3
	b	.L167
.L147:
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r7, r3, r7
	mov	r6, r6, asl r3
	str	r4, [r5, #28]
	str	r7, [r5, #32]
	str	r6, [r5, #36]
.L272:
	sub	r6, r6, #1
	cmp	r7, #0
	mov	r3, r6, asl #8
	sub	r6, r3, r6, asl #2
	mov	r6, r6, lsr #8
	add	r6, r6, #1
	blt	.L364
.L176:
	mov	r0, r6, asl #24
	cmp	r0, r4
	bhi	.L177
	ldr	r3, [r5, #36]
	rsb	r0, r0, r4
	rsb	r6, r6, r3
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r2, [r3, #24]	@ zero_extendqisi2
	mov	r3, r6, asl r2
	rsb	r4, r2, r7
	sub	r6, r3, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	str	r3, [r5, #36]
	add	r10, r6, #1
	str	r4, [r5, #32]
	mov	r6, r0, asl r2
	str	r6, [r5, #28]
	blt	.L365
.L178:
	mov	r2, r10, asl #24
	cmp	r2, r6
	bhi	.L179
	ldr	r3, [r5, #36]
	rsb	r2, r2, r6
	ldr	r1, .L400
	rsb	r3, r10, r3
	add	r1, r1, r3
	ldrb	r10, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r10
	rsb	r4, r10, r4
	sub	r6, r3, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r10, r2, asl r10
	str	r3, [r5, #36]
	add	r6, r6, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L366
.L181:
	mov	r7, r6, asl #24
	cmp	r7, r10
	bhi	.L186
	ldr	r1, [r5, #36]
	rsb	r10, r7, r10
	ldr	r3, .L400
	rsb	r6, r6, r1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r1, r6, asl r3
	rsb	r7, r3, r4
	sub	r6, r1, #1
	cmp	r7, #0
	ubfx	r6, r6, #1, #24
	mov	r10, r10, asl r3
	str	r1, [r5, #36]
	add	r6, r6, #1
	str	r7, [r5, #32]
	str	r10, [r5, #28]
	blt	.L367
.L188:
	mov	r3, r6, asl #24
	cmp	r3, r10
	bhi	.L192
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	ldr	r1, .L400
	mov	r9, #0
	rsb	r6, r6, r4
	mov	r10, #6
	add	r1, r1, r6
	mov	r2, #1
	str	r8, [fp, #-64]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r7, r4, r7
	str	r3, [r5, #28]
	mov	r4, r6, asl r4
	str	r7, [r5, #32]
	mov	r6, r3
	str	r4, [r5, #36]
	b	.L193
.L197:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r6, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L368
.L193:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L197
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-60]
	rsb	r8, r1, r3
	add	r7, r1, r7
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-60]
	orr	r0, r6, r0, asl r3
	b	.L197
.L177:
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r9, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r9
	rsb	r7, r9, r7
	str	r4, [r5, #28]
	mov	r9, r6, asl r9
	str	r7, [r5, #32]
	str	r9, [r5, #36]
.L273:
	ldr	r3, [fp, #-48]
	add	r8, r8, #2
	cmp	r8, r3
	bne	.L206
	ldr	r3, [fp, #-52]
	ldr	r8, [fp, #-56]
	add	r6, r3, #6
	str	r6, [fp, #-48]
	mov	r6, r9
.L270:
	sub	r6, r6, #1
	cmp	r7, #0
	mov	r3, r6, asl #8
	sub	r6, r3, r6, asl #2
	mov	r6, r6, lsr #8
	add	r6, r6, #1
	blt	.L369
.L207:
	mov	r9, r6, asl #24
	cmp	r9, r4
	bhi	.L208
	ldr	r3, [r5, #36]
	rsb	r9, r9, r4
	mov	r1, r8
	mov	r0, r5
	rsb	r6, r6, r3
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r4, r3, r7
	mov	r6, r6, asl r3
	str	r9, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	bl	Vp9_DiffUpdateProb
	ldr	r9, [r5, #28]
	ldr	r6, [r5, #36]
	ldr	r4, [r5, #32]
.L274:
	sub	r6, r6, #1
	cmp	r4, #0
	mov	r3, r6, asl #8
	sub	r6, r3, r6, asl #2
	mov	r6, r6, lsr #8
	add	r6, r6, #1
	blt	.L370
.L209:
	mov	r7, r6, asl #24
	cmp	r7, r9
	bhi	.L210
	ldr	r3, [r5, #36]
	rsb	r7, r7, r9
	rsb	r6, r6, r3
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r2, [r3, #24]	@ zero_extendqisi2
	mov	r3, r6, asl r2
	rsb	r4, r2, r4
	sub	r6, r3, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r7, r7, asl r2
	str	r3, [r5, #36]
	add	r10, r6, #1
	str	r4, [r5, #32]
	str	r7, [r5, #28]
	blt	.L371
.L211:
	mov	r2, r10, asl #24
	cmp	r2, r7
	bhi	.L212
	ldr	r6, [r5, #36]
	rsb	r7, r2, r7
	ldr	r3, .L400
	rsb	r6, r10, r6
	add	r3, r3, r6
	ldrb	r10, [r3, #24]	@ zero_extendqisi2
	mov	r3, r6, asl r10
	rsb	r4, r10, r4
	sub	r6, r3, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r10, r7, asl r10
	str	r3, [r5, #36]
	add	r6, r6, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L372
.L214:
	mov	r7, r6, asl #24
	cmp	r7, r10
	bhi	.L219
	ldr	r1, [r5, #36]
	rsb	r10, r7, r10
	ldr	r3, .L400
	rsb	r6, r6, r1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r1, r6, asl r3
	rsb	r7, r3, r4
	sub	r6, r1, #1
	cmp	r7, #0
	ubfx	r6, r6, #1, #24
	mov	r10, r10, asl r3
	str	r1, [r5, #36]
	add	r6, r6, #1
	str	r7, [r5, #32]
	str	r10, [r5, #28]
	blt	.L373
.L221:
	mov	r3, r6, asl #24
	cmp	r3, r10
	bhi	.L225
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	ldr	r1, .L400
	mov	r9, #0
	rsb	r6, r6, r4
	mov	r10, #6
	add	r1, r1, r6
	mov	r2, #1
	str	r8, [fp, #-56]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r7, r4, r7
	str	r3, [r5, #28]
	mov	r4, r6, asl r4
	str	r7, [r5, #32]
	mov	r6, r3
	str	r4, [r5, #36]
	b	.L226
.L230:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r6, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L374
.L226:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L230
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-52]
	rsb	r8, r1, r3
	add	r7, r1, r7
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	orr	r0, r6, r0, asl r3
	b	.L230
.L208:
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r4, asl r3
	mov	r6, r6, asl r3
	rsb	r4, r3, r7
	str	r9, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	b	.L274
.L210:
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r9, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
.L275:
	sub	r6, r6, #1
	cmp	r4, #0
	mov	r3, r6, asl #8
	sub	r6, r3, r6, asl #2
	mov	r6, r6, lsr #8
	add	r6, r6, #1
	blt	.L375
.L239:
	mov	r7, r6, asl #24
	cmp	r7, r9
	bhi	.L240
	ldr	r3, [r5, #36]
	rsb	r7, r7, r9
	rsb	r6, r6, r3
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r2, [r3, #24]	@ zero_extendqisi2
	mov	r3, r6, asl r2
	rsb	r4, r2, r4
	sub	r6, r3, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r7, r7, asl r2
	str	r3, [r5, #36]
	add	r10, r6, #1
	str	r4, [r5, #32]
	str	r7, [r5, #28]
	blt	.L376
.L241:
	mov	r2, r10, asl #24
	cmp	r2, r7
	bhi	.L242
	ldr	r6, [r5, #36]
	rsb	r7, r2, r7
	ldr	r3, .L400
	rsb	r6, r10, r6
	add	r3, r3, r6
	ldrb	r10, [r3, #24]	@ zero_extendqisi2
	mov	r3, r6, asl r10
	rsb	r4, r10, r4
	sub	r6, r3, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r10, r7, asl r10
	str	r3, [r5, #36]
	add	r6, r6, #1
	str	r4, [r5, #32]
	str	r10, [r5, #28]
	blt	.L377
.L244:
	mov	r7, r6, asl #24
	cmp	r7, r10
	bhi	.L249
	ldr	r1, [r5, #36]
	rsb	r10, r7, r10
	ldr	r3, .L400
	rsb	r6, r6, r1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r1, r6, asl r3
	rsb	r7, r3, r4
	sub	r6, r1, #1
	cmp	r7, #0
	ubfx	r6, r6, #1, #24
	mov	r10, r10, asl r3
	str	r1, [r5, #36]
	add	r6, r6, #1
	str	r7, [r5, #32]
	str	r10, [r5, #28]
	blt	.L378
.L251:
	mov	r3, r6, asl #24
	cmp	r3, r10
	bhi	.L255
	ldr	r4, [r5, #36]
	rsb	r3, r3, r10
	ldr	r1, .L400
	mov	r9, #0
	rsb	r6, r6, r4
	mov	r10, #6
	add	r1, r1, r6
	mov	r2, #1
	str	r8, [fp, #-56]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r7, r4, r7
	str	r3, [r5, #28]
	mov	r4, r6, asl r4
	str	r7, [r5, #32]
	mov	r6, r3
	str	r4, [r5, #36]
	b	.L256
.L260:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r6, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L379
.L256:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L260
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-52]
	rsb	r8, r1, r3
	add	r7, r1, r7
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	orr	r0, r6, r0, asl r3
	b	.L260
.L240:
	ldr	r3, .L400
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r9, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
.L276:
	ldr	r3, [fp, #-48]
	add	r8, r8, #3
	cmp	r8, r3
	ldrne	r4, [r5, #28]
	ldrne	r6, [r5, #36]
	ldrne	r7, [r5, #32]
	bne	.L270
.L114:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L212:
	ldr	r3, .L400
	mov	r9, #0
	mov	r2, #1
	str	r8, [fp, #-56]
	add	r1, r3, r10
	mov	r3, #3
	ldrb	r6, [r1, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r6
	rsb	r4, r6, r4
	str	r7, [r5, #28]
	mov	r6, r10, asl r6
	str	r4, [r5, #32]
	mov	r10, r3
	str	r6, [r5, #36]
	b	.L217
.L215:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r6, r6, ip
	cmn	r10, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L380
.L217:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r7
	add	r6, r6, #1
	bge	.L215
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-52]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	orr	r0, r7, r0, asl r3
	b	.L215
.L179:
	ldr	r3, .L400
	mov	r9, #0
	mov	r2, #1
	str	r8, [fp, #-64]
	add	r1, r3, r10
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r6, asl r1
	rsb	r4, r1, r4
	mov	r6, r10, asl r1
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r6, [r5, #36]
	b	.L184
.L182:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r6, r6, ip
	cmn	r10, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L381
.L184:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r7
	add	r6, r6, #1
	bge	.L182
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-60]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-60]
	orr	r0, r7, r0, asl r3
	b	.L182
.L149:
	ldr	r3, .L400
	mov	r10, #0
	mov	r2, #1
	str	r8, [fp, #-64]
	add	r1, r3, r6
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	rsb	r4, r1, r7
	mov	r9, r9, asl r1
	mov	r6, r6, asl r1
	str	r9, [r5, #28]
	str	r4, [r5, #32]
	mov	r7, r3
	str	r6, [r5, #36]
	b	.L154
.L152:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r6, r6, ip
	cmn	r7, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r9, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L382
.L154:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r9
	add	r6, r6, #1
	bge	.L152
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-60]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-60]
	orr	r0, r9, r0, asl r3
	b	.L152
.L118:
	ldr	r3, .L400
	mov	r9, #0
	mov	r2, #1
	str	r8, [fp, #-60]
	add	r1, r3, r10
	mov	r3, #3
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	rsb	r7, r4, r7
	str	r6, [r5, #28]
	mov	r4, r10, asl r4
	str	r7, [r5, #32]
	mov	r10, r3
	str	r4, [r5, #36]
	b	.L123
.L121:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r10, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r6, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L383
.L123:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L121
	rsb	r1, r7, #24
	rsb	r3, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-56]
	rsb	r8, r1, r3
	add	r7, r1, r7
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-56]
	orr	r0, r6, r0, asl r3
	b	.L121
.L242:
	ldr	r3, .L400
	mov	r9, #0
	mov	r2, #1
	str	r8, [fp, #-56]
	add	r1, r3, r10
	mov	r3, #3
	ldrb	r6, [r1, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r6
	rsb	r4, r6, r4
	str	r7, [r5, #28]
	mov	r6, r10, asl r6
	str	r4, [r5, #32]
	mov	r10, r3
	str	r6, [r5, #36]
	b	.L247
.L245:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r6, r6, ip
	cmn	r10, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L384
.L247:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r7
	add	r6, r6, #1
	bge	.L245
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-52]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	orr	r0, r7, r0, asl r3
	b	.L245
.L364:
	rsb	r10, r7, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r7, #16
	rsb	r9, r10, r9
	add	r7, r10, r7
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r7, [r5, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L176
.L369:
	rsb	r10, r7, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r7, #16
	rsb	r9, r10, r9
	add	r7, r10, r7
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r7, [r5, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L207
.L401:
	.align	2
.L400:
	.word	.LANCHOR0
.L370:
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
	orr	r0, r9, r0, asl r7
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L209
.L375:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r7, r4, #16
	rsb	r7, r10, r7
	add	r4, r10, r4
	mov	r1, r10
	bl	BsGet
	and	r3, r7, #7
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r3
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L239
.L359:
	rsb	r10, r7, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r9, r7, #16
	rsb	r9, r10, r9
	add	r7, r10, r7
	mov	r1, r10
	and	r9, r9, #7
	bl	BsGet
	str	r7, [r5, #32]
	orr	r0, r4, r0, asl r9
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L146
.L354:
	rsb	r10, r7, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r6, r7, #16
	rsb	r6, r10, r6
	add	r7, r10, r7
	mov	r1, r10
	and	r6, r6, #7
	bl	BsGet
	str	r7, [r5, #32]
	orr	r0, r4, r0, asl r6
	str	r0, [r5, #28]
	mov	r4, r0
	b	.L115
.L382:
	ldr	r8, [fp, #-64]
.L155:
	ldrb	r2, [r8, #6]	@ zero_extendqisi2
	ldr	r3, .L400
	sub	ip, r2, #1
	add	r10, r3, r10
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	bgt	.L170
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L171
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L171:
	add	r3, r3, #1
.L173:
	strb	r3, [r8, #6]
	ldr	r4, [r5, #28]
	ldr	r6, [r5, #36]
	ldr	r7, [r5, #32]
	b	.L272
.L170:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L385
	rsb	r3, r3, #255
	b	.L173
.L383:
	ldr	r8, [fp, #-60]
.L124:
	ldrb	r2, [r8]	@ zero_extendqisi2
	ldr	r3, .L400
	sub	ip, r2, #1
	add	r9, r3, r9
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	bgt	.L139
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L140
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L140:
	add	r3, r3, #1
.L142:
	add	r4, r5, #28
	strb	r3, [r8]
	ldmia	r4, {r4, r7, r9}
	b	.L271
.L139:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L386
	rsb	r3, r3, #255
	b	.L142
.L384:
	ldr	r8, [fp, #-56]
.L248:
	ldrb	r2, [r8, #2]	@ zero_extendqisi2
	ldr	r3, .L400
	sub	ip, r2, #1
	add	r9, r3, r9
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	bgt	.L263
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L264
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L264:
	add	r3, r3, #1
.L266:
	strb	r3, [r8, #2]
	b	.L276
.L263:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L387
	rsb	r3, r3, #255
	b	.L266
.L381:
	ldr	r8, [fp, #-64]
.L185:
	ldrb	r2, [r8, #7]	@ zero_extendqisi2
	ldr	r3, .L400
	sub	ip, r2, #1
	add	r9, r3, r9
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	bgt	.L200
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L201
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L201:
	add	r3, r3, #1
.L203:
	add	r4, r5, #28
	strb	r3, [r8, #7]
	ldmia	r4, {r4, r7, r9}
	b	.L273
.L200:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L388
	rsb	r3, r3, #255
	b	.L203
.L380:
	ldr	r8, [fp, #-56]
.L218:
	ldrb	r2, [r8, #1]	@ zero_extendqisi2
	ldr	r3, .L400
	sub	ip, r2, #1
	add	r9, r3, r9
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
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
	strb	r3, [r8, #1]
	ldr	r9, [r5, #28]
	ldr	r6, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L275
.L233:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	ble	.L389
	rsb	r3, r3, #255
	b	.L236
.L386:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L142
.L385:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L173
.L388:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L203
.L387:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L266
.L389:
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
	rsb	r3, r3, #255
	b	.L236
.L162:
	ldr	r3, .L400
	mov	r2, #4
	mov	r10, #0
	str	r8, [fp, #-64]
	add	r1, r3, r6
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	mov	r9, r9, asl r4
	rsb	r7, r4, r7
	str	r6, [r5, #36]
	mov	r4, r6
	str	r9, [r5, #28]
	str	r7, [r5, #32]
	mov	r6, r2
	b	.L166
.L164:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r6
	cmp	r2, r0
	sub	r6, r6, #1
	rsbls	r0, r2, r0
	ldr	r2, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r6, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r9, r0, asl r2
	rsb	r7, r2, r7
	mov	r4, r4, asl r2
	str	r9, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L390
.L166:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r9
	add	r4, r4, #1
	bge	.L164
	rsb	r1, r7, #24
	rsb	r2, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r3, [fp, #-60]
	rsb	r8, r1, r2
	add	r7, r1, r7
	bl	BsGet
	and	r2, r8, #7
	ldr	r3, [fp, #-60]
	orr	r0, r9, r0, asl r2
	b	.L164
.L192:
	ldr	r3, .L400
	mov	r2, #4
	mov	r9, #0
	str	r8, [fp, #-64]
	add	r1, r3, r6
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	mov	r10, r10, asl r4
	rsb	r7, r4, r7
	str	r6, [r5, #36]
	mov	r4, r6
	str	r10, [r5, #28]
	str	r7, [r5, #32]
	mov	r6, r2
	b	.L196
.L194:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r6
	cmp	r2, r0
	sub	r6, r6, #1
	rsbls	r0, r2, r0
	ldr	r2, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r6, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r7, r2, r7
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L391
.L196:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L194
	rsb	r1, r7, #24
	rsb	r2, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r3, [fp, #-60]
	rsb	r8, r1, r2
	add	r7, r1, r7
	bl	BsGet
	and	r2, r8, #7
	ldr	r3, [fp, #-60]
	orr	r0, r10, r0, asl r2
	b	.L194
.L255:
	ldr	r3, .L400
	mov	r2, #4
	mov	r9, #0
	str	r8, [fp, #-56]
	add	r1, r3, r6
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	mov	r10, r10, asl r4
	rsb	r7, r4, r7
	str	r6, [r5, #36]
	mov	r4, r6
	str	r10, [r5, #28]
	str	r7, [r5, #32]
	mov	r6, r2
	b	.L259
.L257:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r6
	cmp	r2, r0
	sub	r6, r6, #1
	rsbls	r0, r2, r0
	ldr	r2, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r6, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r7, r2, r7
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L392
.L259:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L257
	rsb	r1, r7, #24
	rsb	r2, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r3, [fp, #-52]
	rsb	r8, r1, r2
	add	r7, r1, r7
	bl	BsGet
	and	r2, r8, #7
	ldr	r3, [fp, #-52]
	orr	r0, r10, r0, asl r2
	b	.L257
.L131:
	ldr	r3, .L400
	mov	r2, #4
	mov	r9, #0
	str	r8, [fp, #-60]
	add	r1, r3, r6
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	mov	r10, r10, asl r4
	rsb	r7, r4, r7
	str	r6, [r5, #36]
	mov	r4, r6
	str	r10, [r5, #28]
	str	r7, [r5, #32]
	mov	r6, r2
	b	.L135
.L133:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r6
	cmp	r2, r0
	sub	r6, r6, #1
	rsbls	r0, r2, r0
	ldr	r2, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r6, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r7, r2, r7
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L393
.L135:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L133
	rsb	r1, r7, #24
	rsb	r2, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r3, [fp, #-56]
	rsb	r8, r1, r2
	add	r7, r1, r7
	bl	BsGet
	and	r2, r8, #7
	ldr	r3, [fp, #-56]
	orr	r0, r10, r0, asl r2
	b	.L133
.L225:
	ldr	r3, .L400
	mov	r2, #4
	mov	r9, #0
	str	r8, [fp, #-56]
	add	r1, r3, r6
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	mov	r10, r10, asl r4
	rsb	r7, r4, r7
	str	r6, [r5, #36]
	mov	r4, r6
	str	r10, [r5, #28]
	str	r7, [r5, #32]
	mov	r6, r2
	b	.L229
.L227:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r6
	cmp	r2, r0
	sub	r6, r6, #1
	rsbls	r0, r2, r0
	ldr	r2, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r6, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r7, r2, r7
	mov	r4, r4, asl r2
	str	r10, [r5, #28]
	str	r7, [r5, #32]
	str	r4, [r5, #36]
	beq	.L394
.L229:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L227
	rsb	r1, r7, #24
	rsb	r2, r7, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r3, [fp, #-52]
	rsb	r8, r1, r2
	add	r7, r1, r7
	bl	BsGet
	and	r2, r8, #7
	ldr	r3, [fp, #-52]
	orr	r0, r10, r0, asl r2
	b	.L227
.L156:
	ldr	r3, .L400
	mov	r10, #0
	mov	r2, #1
	str	r8, [fp, #-64]
	add	r1, r3, r6
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r9, asl r1
	rsb	r4, r1, r4
	mov	r6, r6, asl r1
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	mov	r9, r3
	str	r6, [r5, #36]
	b	.L161
.L159:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r6, r6, ip
	cmn	r9, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L395
.L161:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r7
	add	r6, r6, #1
	bge	.L159
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-60]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-60]
	orr	r0, r7, r0, asl r3
	b	.L159
.L125:
	ldr	r3, .L400
	mov	r9, #0
	mov	r2, #1
	str	r8, [fp, #-60]
	add	r1, r3, r6
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	rsb	r4, r1, r7
	mov	r10, r10, asl r1
	mov	r6, r6, asl r1
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	mov	r7, r3
	str	r6, [r5, #36]
	b	.L130
.L128:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r6, r6, ip
	cmn	r7, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r10, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L396
.L130:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r10
	add	r6, r6, #1
	bge	.L128
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-56]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-56]
	orr	r0, r10, r0, asl r3
	b	.L128
.L186:
	ldr	r3, .L400
	mov	r9, #0
	mov	r2, #1
	str	r8, [fp, #-64]
	add	r1, r3, r6
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r10, asl r1
	rsb	r4, r1, r4
	mov	r6, r6, asl r1
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r6, [r5, #36]
	b	.L191
.L189:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r6, r6, ip
	cmn	r10, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L397
.L191:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r7
	add	r6, r6, #1
	bge	.L189
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-60]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-60]
	orr	r0, r7, r0, asl r3
	b	.L189
.L219:
	ldr	r3, .L400
	mov	r9, #0
	mov	r2, #1
	str	r8, [fp, #-56]
	add	r1, r3, r6
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r10, asl r1
	rsb	r4, r1, r4
	mov	r6, r6, asl r1
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r6, [r5, #36]
	b	.L224
.L222:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r6, r6, ip
	cmn	r10, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L398
.L224:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r7
	add	r6, r6, #1
	bge	.L222
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-52]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	orr	r0, r7, r0, asl r3
	b	.L222
.L249:
	ldr	r3, .L400
	mov	r9, #0
	mov	r2, #1
	str	r8, [fp, #-56]
	add	r1, r3, r6
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r10, asl r1
	rsb	r4, r1, r4
	mov	r6, r6, asl r1
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	mov	r10, r3
	str	r6, [r5, #36]
	b	.L254
.L252:
	mov	r3, r6, asl #24
	mov	r1, r2, asl r10
	cmp	r3, r0
	sub	r10, r10, #1
	rsbls	r0, r3, r0
	ldr	r3, .L400
	ldrls	ip, [r5, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r6, r6, ip
	cmn	r10, #1
	add	r3, r3, r6
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r6, r6, asl r3
	str	r7, [r5, #28]
	str	r4, [r5, #32]
	str	r6, [r5, #36]
	beq	.L399
.L254:
	sub	r6, r6, #1
	cmp	r4, #0
	ubfx	r6, r6, #1, #24
	mov	r0, r7
	add	r6, r6, #1
	bge	.L252
	rsb	r1, r4, #24
	rsb	r3, r4, #16
	bic	r1, r1, #7
	mov	r0, r5
	str	r2, [fp, #-52]
	rsb	r8, r1, r3
	add	r4, r1, r4
	bl	BsGet
	and	r3, r8, #7
	ldr	r2, [fp, #-52]
	orr	r0, r7, r0, asl r3
	b	.L252
.L399:
	ldr	r8, [fp, #-56]
	add	r9, r9, #16
	b	.L248
.L395:
	ldr	r8, [fp, #-64]
	add	r10, r10, #16
	b	.L155
.L398:
	ldr	r8, [fp, #-56]
	add	r9, r9, #16
	b	.L218
.L397:
	ldr	r8, [fp, #-64]
	add	r9, r9, #16
	b	.L185
.L396:
	ldr	r8, [fp, #-60]
	add	r9, r9, #16
	b	.L124
.L358:
	cmp	r9, #64
	ldr	r8, [fp, #-60]
	ble	.L138
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L138:
	add	r9, r9, #64
	b	.L124
.L374:
	cmp	r9, #64
	ldr	r8, [fp, #-56]
	ble	.L232
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L232:
	add	r9, r9, #64
	b	.L218
.L379:
	cmp	r9, #64
	ldr	r8, [fp, #-56]
	ble	.L262
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L262:
	add	r9, r9, #64
	b	.L248
.L368:
	cmp	r9, #64
	ldr	r8, [fp, #-64]
	ble	.L199
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L199:
	add	r9, r9, #64
	b	.L185
.L363:
	cmp	r10, #64
	ldr	r8, [fp, #-64]
	ble	.L169
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r10, lsl #1
	sub	r10, r0, #65
.L169:
	add	r10, r10, #64
	b	.L155
.L393:
	ldr	r8, [fp, #-60]
	add	r9, r9, #32
	b	.L124
.L390:
	ldr	r8, [fp, #-64]
	add	r10, r10, #32
	b	.L155
.L394:
	ldr	r8, [fp, #-56]
	add	r9, r9, #32
	b	.L218
.L392:
	ldr	r8, [fp, #-56]
	add	r9, r9, #32
	b	.L248
.L391:
	ldr	r8, [fp, #-64]
	add	r9, r9, #32
	b	.L185
.L365:
	rsb	r7, r4, #24
	mov	r0, r5
	bic	r7, r7, #7
	rsb	r9, r4, #16
	rsb	r9, r7, r9
	add	r4, r4, r7
	mov	r1, r7
	and	r9, r9, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r6, r0, asl r9
	str	r0, [r5, #28]
	mov	r6, r0
	b	.L178
.L360:
	rsb	r10, r7, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r4, r7, #16
	rsb	r4, r10, r4
	add	r7, r7, r10
	mov	r1, r10
	bl	BsGet
	and	r2, r4, #7
	str	r7, [r5, #32]
	orr	r0, r9, r0, asl r2
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L148
.L355:
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
	orr	r0, r6, r0, asl r3
	str	r0, [r5, #28]
	mov	r6, r0
	b	.L117
.L376:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r6, r4, #16
	rsb	r6, r9, r6
	add	r4, r4, r9
	mov	r1, r9
	and	r6, r6, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r7, r0, asl r6
	str	r0, [r5, #28]
	mov	r7, r0
	b	.L241
.L371:
	rsb	r9, r4, #24
	mov	r0, r5
	bic	r9, r9, #7
	rsb	r6, r4, #16
	rsb	r6, r9, r6
	add	r4, r4, r9
	mov	r1, r9
	and	r6, r6, #7
	bl	BsGet
	str	r4, [r5, #32]
	orr	r0, r7, r0, asl r6
	str	r0, [r5, #28]
	mov	r7, r0
	b	.L211
.L357:
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
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L127
.L378:
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
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L251
.L373:
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
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L221
.L367:
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
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L188
.L362:
	rsb	r10, r7, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r4, r7, #16
	rsb	r4, r10, r4
	add	r7, r7, r10
	mov	r1, r10
	bl	BsGet
	and	r3, r4, #7
	str	r7, [r5, #32]
	orr	r0, r9, r0, asl r3
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L158
.L377:
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
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L244
.L356:
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
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L120
.L366:
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
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L181
.L361:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	rsb	r7, r4, #16
	rsb	r7, r10, r7
	mov	r1, r10
	bl	BsGet
	and	r3, r7, #7
	add	r7, r4, r10
	str	r7, [r5, #32]
	mov	r4, r7
	orr	r0, r9, r0, asl r3
	str	r0, [r5, #28]
	mov	r9, r0
	b	.L151
.L372:
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
	orr	r0, r10, r0, asl r3
	str	r0, [r5, #28]
	mov	r10, r0
	b	.L214
	UNWIND(.fnend)
	.size	Vp9_ReadTxProbs, .-Vp9_ReadTxProbs
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
	blt	.L403
	ldr	r3, [r1, #28]
.L404:
	mov	r1, r4, asl #24
	cmp	r1, r3
	bhi	.L405
	ldr	r2, [r10, #36]
	rsb	r3, r1, r3
	ldr	r9, .L594
	add	r1, r6, #648
	rsb	r4, r4, r2
	add	r2, r1, #2
	str	r2, [fp, #-80]
	add	r2, r9, r4
	add	r1, r6, #218
	str	r1, [fp, #-76]
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	rsb	r5, r2, r5
	str	r5, [r10, #32]
	mov	r5, r10
	mov	r3, r3, asl r2
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r4, [r10, #36]
.L406:
	ldr	r3, [fp, #-76]
	mov	r10, r5
	sub	r3, r3, #216
	str	r3, [fp, #-72]
.L511:
	ldr	r3, [fp, #-72]
	str	r3, [fp, #-60]
	mov	r3, #0
	str	r3, [fp, #-56]
.L509:
	ldr	r3, [fp, #-60]
	str	r3, [fp, #-48]
	mov	r3, #0
	str	r3, [fp, #-52]
.L507:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-52]
	cmp	r3, #0
	moveq	r3, #3
	movne	r3, #6
	cmp	r2, r3
	bge	.L567
	ldr	r5, [r10, #36]
	ldr	r4, [r10, #32]
	sub	r5, r5, #1
	cmp	r4, #0
	mov	r3, r5, asl #8
	sub	r5, r3, r5, asl #2
	mov	r5, r5, lsr #8
	add	r5, r5, #1
	blt	.L407
	ldr	r7, [r10, #28]
.L408:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L409
	ldr	r3, [r10, #36]
	rsb	r7, r6, r7
	rsb	r5, r5, r3
	add	r3, r9, r5
	ldrb	r6, [r3, #24]	@ zero_extendqisi2
	mov	r3, r5, asl r6
	rsb	r4, r6, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r7, asl r6
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r7, [r10, #28]
	blt	.L568
.L410:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L411
	ldr	r3, [r10, #36]
	rsb	r6, r6, r7
	rsb	r5, r5, r3
	add	r3, r9, r5
	ldrb	r7, [r3, #24]	@ zero_extendqisi2
	mov	r3, r5, asl r7
	rsb	r4, r7, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r6, asl r7
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r7, [r10, #28]
	blt	.L569
.L413:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L418
	ldr	r2, [r10, #36]
	rsb	r7, r6, r7
	rsb	r5, r5, r2
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r2, r5, asl r3
	rsb	r6, r3, r4
	sub	r5, r2, #1
	cmp	r6, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r7, asl r3
	str	r2, [r10, #36]
	add	r5, r5, #1
	str	r6, [r10, #32]
	str	r7, [r10, #28]
	blt	.L570
.L420:
	mov	r3, r5, asl #24
	cmp	r3, r7
	bhi	.L424
	ldr	r4, [r10, #36]
	rsb	r3, r3, r7
	mov	r8, #0
	mov	r7, #6
	rsb	r5, r5, r4
	mov	r2, #1
	add	r1, r9, r5
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r6, r4, r6
	str	r3, [r10, #28]
	mov	r4, r5, asl r4
	str	r6, [r10, #32]
	mov	r5, r3
	str	r4, [r10, #36]
	b	.L425
.L429:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	add	r3, r9, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r6, r3, r6
	mov	r4, r4, asl r3
	str	r5, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L571
.L425:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L429
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
	b	.L429
.L409:
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
.L512:
	sub	r5, r5, #1
	cmp	r4, #0
	mov	r3, r5, asl #8
	sub	r5, r3, r5, asl #2
	mov	r5, r5, lsr #8
	add	r5, r5, #1
	blt	.L572
.L440:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L441
	ldr	r3, [r10, #36]
	rsb	r7, r6, r7
	rsb	r5, r5, r3
	add	r3, r9, r5
	ldrb	r6, [r3, #24]	@ zero_extendqisi2
	mov	r3, r5, asl r6
	rsb	r4, r6, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r7, asl r6
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r7, [r10, #28]
	blt	.L573
.L442:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L443
	ldr	r3, [r10, #36]
	rsb	r6, r6, r7
	rsb	r5, r5, r3
	add	r3, r9, r5
	ldrb	r7, [r3, #24]	@ zero_extendqisi2
	mov	r3, r5, asl r7
	rsb	r4, r7, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r6, asl r7
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r7, [r10, #28]
	blt	.L574
.L445:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L450
	ldr	r2, [r10, #36]
	rsb	r7, r6, r7
	rsb	r5, r5, r2
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r2, r5, asl r3
	rsb	r6, r3, r4
	sub	r5, r2, #1
	cmp	r6, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r7, asl r3
	str	r2, [r10, #36]
	add	r5, r5, #1
	str	r6, [r10, #32]
	str	r7, [r10, #28]
	blt	.L575
.L452:
	mov	r3, r5, asl #24
	cmp	r3, r7
	bhi	.L456
	ldr	r4, [r10, #36]
	rsb	r3, r3, r7
	mov	r8, #0
	mov	r7, #6
	rsb	r5, r5, r4
	mov	r2, #1
	add	r1, r9, r5
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r6, r4, r6
	str	r3, [r10, #28]
	mov	r4, r5, asl r4
	str	r6, [r10, #32]
	mov	r5, r3
	str	r4, [r10, #36]
	b	.L457
.L461:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	add	r3, r9, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r6, r3, r6
	mov	r4, r4, asl r3
	str	r5, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L576
.L457:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L461
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
	b	.L461
.L441:
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
.L513:
	sub	r5, r5, #1
	cmp	r4, #0
	mov	r3, r5, asl #8
	sub	r5, r3, r5, asl #2
	mov	r5, r5, lsr #8
	add	r5, r5, #1
	blt	.L577
.L472:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L473
	ldr	r3, [r10, #36]
	rsb	r7, r6, r7
	rsb	r5, r5, r3
	add	r3, r9, r5
	ldrb	r6, [r3, #24]	@ zero_extendqisi2
	mov	r3, r5, asl r6
	rsb	r4, r6, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r7, asl r6
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r7, [r10, #28]
	blt	.L578
.L474:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L475
	ldr	r3, [r10, #36]
	rsb	r6, r6, r7
	rsb	r5, r5, r3
	add	r3, r9, r5
	ldrb	r7, [r3, #24]	@ zero_extendqisi2
	mov	r3, r5, asl r7
	rsb	r4, r7, r4
	sub	r5, r3, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r6, asl r7
	str	r3, [r10, #36]
	add	r5, r5, #1
	str	r4, [r10, #32]
	str	r7, [r10, #28]
	blt	.L579
.L477:
	mov	r6, r5, asl #24
	cmp	r6, r7
	bhi	.L482
	ldr	r2, [r10, #36]
	rsb	r7, r6, r7
	rsb	r5, r5, r2
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r2, r5, asl r3
	rsb	r6, r3, r4
	sub	r5, r2, #1
	cmp	r6, #0
	ubfx	r5, r5, #1, #24
	mov	r7, r7, asl r3
	str	r2, [r10, #36]
	add	r5, r5, #1
	str	r6, [r10, #32]
	str	r7, [r10, #28]
	blt	.L580
.L484:
	mov	r3, r5, asl #24
	cmp	r3, r7
	bhi	.L488
	ldr	r4, [r10, #36]
	rsb	r3, r3, r7
	mov	r8, #0
	mov	r7, #6
	rsb	r5, r5, r4
	mov	r2, #1
	add	r1, r9, r5
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r6, r4, r6
	str	r3, [r10, #28]
	mov	r4, r5, asl r4
	str	r6, [r10, #32]
	mov	r5, r3
	str	r4, [r10, #36]
	b	.L489
.L493:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	add	r3, r9, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r6, r3, r6
	mov	r4, r4, asl r3
	str	r5, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L581
.L489:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L493
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
	b	.L493
.L473:
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
.L514:
	ldr	r3, [fp, #-52]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r3, r3, #3
	str	r3, [fp, #-48]
	b	.L507
.L577:
	rsb	r8, r4, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r4, #16
	rsb	r6, r8, r6
	add	r4, r8, r4
	mov	r1, r8
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L472
.L572:
	rsb	r8, r4, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r4, #16
	rsb	r6, r8, r6
	add	r4, r8, r4
	mov	r1, r8
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L440
.L407:
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
	mov	r7, r0
	b	.L408
.L475:
	add	r1, r9, r5
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r6, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r7, r3
	str	r5, [r10, #36]
	b	.L480
.L478:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r7, #1
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L481
.L480:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L478
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
	b	.L478
.L581:
	cmp	r8, #64
	mov	r3, r5
	bgt	.L582
.L495:
	add	r8, r8, #64
.L481:
	ldr	r3, [fp, #-48]
	add	r8, r9, r8
	ldrb	r1, [r8, #280]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L498
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L499
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L499:
	add	r3, r3, #1
.L501:
	ldr	r2, [fp, #-48]
	strb	r3, [r2]
	b	.L514
.L498:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L502
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L502:
	rsb	r3, r3, #255
	b	.L501
.L443:
	add	r1, r9, r5
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r6, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r7, r3
	str	r5, [r10, #36]
	b	.L448
.L446:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r7, #1
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L449
.L448:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L446
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
	b	.L446
.L576:
	cmp	r8, #64
	mov	r3, r5
	bgt	.L583
.L463:
	add	r8, r8, #64
.L449:
	ldr	r3, [fp, #-48]
	add	r8, r9, r8
	ldrb	r1, [r8, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L466
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L467
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L467:
	add	r3, r3, #1
.L469:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #-1]
	ldr	r5, [r10, #36]
	ldr	r4, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L513
.L466:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L470
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L470:
	rsb	r3, r3, #255
	b	.L469
.L411:
	add	r1, r9, r5
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r6, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r7, r3
	str	r5, [r10, #36]
	b	.L416
.L414:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r7, #1
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L417
.L416:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L414
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
	b	.L414
.L571:
	cmp	r8, #64
	mov	r3, r5
	bgt	.L584
.L431:
	add	r8, r8, #64
.L417:
	ldr	r3, [fp, #-48]
	add	r8, r9, r8
	ldrb	r1, [r8, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L434
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L435
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L435:
	add	r3, r3, #1
.L437:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #-2]
	ldr	r5, [r10, #36]
	ldr	r4, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L512
.L434:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L438
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L438:
	rsb	r3, r3, #255
	b	.L437
.L567:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r3, #6
	add	r2, r2, #18
	str	r2, [fp, #-60]
	bne	.L509
	ldr	r3, [fp, #-72]
	ldr	r2, [fp, #-76]
	add	r3, r3, #108
	str	r3, [fp, #-72]
	cmp	r2, r3
	bne	.L511
	ldr	r3, [fp, #-76]
	mov	r5, r10
	ldr	r2, [fp, #-80]
	add	r3, r3, #216
	str	r3, [fp, #-76]
	cmp	r3, r2
	bne	.L406
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L418:
	add	r1, r9, r5
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r6, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r7, r3
	str	r5, [r10, #36]
	b	.L423
.L421:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r7, #1
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L585
.L423:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L421
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
	b	.L421
.L482:
	add	r1, r9, r5
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r6, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r7, r3
	str	r5, [r10, #36]
	b	.L487
.L485:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r7, #1
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L586
.L487:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L485
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
	b	.L485
.L450:
	add	r1, r9, r5
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r6, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	mov	r7, r3
	str	r5, [r10, #36]
	b	.L455
.L453:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r5, r5, ip
	cmn	r7, #1
	add	r3, r9, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r6, [r10, #28]
	str	r4, [r10, #32]
	str	r5, [r10, #36]
	beq	.L587
.L455:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r6
	add	r5, r5, #1
	bge	.L453
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
	b	.L453
.L587:
	add	r8, r8, #16
	b	.L449
.L586:
	add	r8, r8, #16
	b	.L481
.L585:
	add	r8, r8, #16
	b	.L417
.L488:
	add	r1, r9, r5
	mov	r2, #4
	mov	r8, #0
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r5, r5, asl r4
	mov	r7, r7, asl r4
	rsb	r6, r4, r6
	str	r5, [r10, #36]
	mov	r4, r5
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	mov	r5, r2
	b	.L492
.L490:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	add	r2, r9, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L588
.L492:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L490
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
	orr	r0, r7, r0, asl r2
	b	.L490
.L424:
	add	r1, r9, r5
	mov	r2, #4
	mov	r8, #0
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r5, r5, asl r4
	mov	r7, r7, asl r4
	rsb	r6, r4, r6
	str	r5, [r10, #36]
	mov	r4, r5
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	mov	r5, r2
	b	.L428
.L595:
	.align	2
.L594:
	.word	.LANCHOR0
.L426:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	add	r2, r9, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L589
.L428:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L426
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
	orr	r0, r7, r0, asl r2
	b	.L426
.L456:
	add	r1, r9, r5
	mov	r2, #4
	mov	r8, #0
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r5, r5, asl r4
	mov	r7, r7, asl r4
	rsb	r6, r4, r6
	str	r5, [r10, #36]
	mov	r4, r5
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	mov	r5, r2
	b	.L460
.L458:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r5
	cmp	r2, r0
	sub	r5, r5, #1
	rsbls	r0, r2, r0
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r8, r8, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	add	r2, r9, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L590
.L460:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L458
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
	orr	r0, r7, r0, asl r2
	b	.L458
.L590:
	add	r8, r8, #32
	b	.L449
.L588:
	add	r8, r8, #32
	b	.L481
.L589:
	add	r8, r8, #32
	b	.L417
.L568:
	rsb	r8, r4, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r4, #16
	rsb	r6, r8, r6
	add	r4, r4, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L410
.L578:
	rsb	r8, r4, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r4, #16
	rsb	r6, r8, r6
	add	r4, r4, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L474
.L573:
	rsb	r8, r4, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r4, #16
	rsb	r6, r8, r6
	add	r4, r4, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L442
.L583:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r8, r8, asl #1
	add	r4, r4, #1
	sub	r8, r8, #65
	movge	r0, r5
	blt	.L591
.L464:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r10, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r8, r8, r1
	rsbls	r4, r4, r3
	add	r2, r9, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L463
.L584:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r8, r8, asl #1
	add	r4, r4, #1
	sub	r8, r8, #65
	movge	r0, r5
	blt	.L592
.L432:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r10, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r8, r8, r1
	rsbls	r4, r4, r3
	add	r2, r9, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L431
.L582:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r8, r8, asl #1
	add	r4, r4, #1
	sub	r8, r8, #65
	movge	r0, r5
	blt	.L593
.L496:
	mov	r2, r4, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r10, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r8, r8, r1
	rsbls	r4, r4, r3
	add	r2, r9, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L495
.L569:
	rsb	r8, r4, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r4, #16
	rsb	r6, r8, r6
	add	r4, r4, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L413
.L574:
	rsb	r8, r4, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r4, #16
	rsb	r6, r8, r6
	add	r4, r4, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L445
.L579:
	rsb	r8, r4, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r6, r4, #16
	rsb	r6, r8, r6
	add	r4, r4, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r6, #7
	str	r4, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L477
.L580:
	rsb	r8, r6, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r4, r6, #16
	rsb	r4, r8, r4
	add	r6, r6, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r4, #7
	str	r6, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L484
.L570:
	rsb	r8, r6, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r4, r6, #16
	rsb	r4, r8, r4
	add	r6, r6, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r4, #7
	str	r6, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L420
.L575:
	rsb	r8, r6, #24
	mov	r0, r10
	bic	r8, r8, #7
	rsb	r4, r6, #16
	rsb	r4, r8, r4
	add	r6, r6, r8
	mov	r1, r8
	bl	BsGet
	and	r3, r4, #7
	str	r6, [r10, #32]
	orr	r0, r7, r0, asl r3
	str	r0, [r10, #28]
	mov	r7, r0
	b	.L452
.L593:
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
	b	.L496
.L591:
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
	b	.L464
.L592:
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
	b	.L432
.L405:
	ldr	r2, .L594
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r3, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L403:
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
	b	.L404
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
	add	r0, r6, #432
	bl	Vp9_ReadCoefProbsCommon
	cmp	r4, #1
	bls	.L598
	mov	r1, r5
	add	r0, r6, #864
	bl	Vp9_ReadCoefProbsCommon
.L598:
	cmp	r4, #2
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	add	r0, r6, #1296
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
	ldr	r6, .L771
	mov	r5, r1
	add	r3, r0, #21
	str	r0, [fp, #-48]
	str	r3, [fp, #-52]
.L695:
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L602
	ldr	r8, [r5, #28]
.L603:
	mov	r0, r7, asl #24
	cmp	r0, r8
	bhi	.L604
	ldr	r3, [r5, #36]
	rsb	r8, r0, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L749
.L605:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L606
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L750
.L608:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L613
	ldr	r2, [r5, #36]
	rsb	r8, r3, r8
	rsb	r7, r7, r2
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L751
.L615:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L619
	ldr	r1, [r5, #36]
	rsb	r8, r3, r8
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r1
	mov	r2, #1
	add	r3, r6, r7
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L620
.L624:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L752
.L620:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L624
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
	b	.L624
.L604:
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L696:
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L753
.L635:
	mov	r0, r7, asl #24
	cmp	r0, r8
	bhi	.L636
	ldr	r3, [r5, #36]
	rsb	r8, r0, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L754
.L637:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L638
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L755
.L640:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L645
	ldr	r2, [r5, #36]
	rsb	r8, r3, r8
	rsb	r7, r7, r2
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L756
.L647:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L651
	ldr	r1, [r5, #36]
	rsb	r8, r3, r8
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r1
	mov	r2, #1
	add	r3, r6, r7
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L652
.L656:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L757
.L652:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L656
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
	b	.L656
.L636:
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L697:
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L758
.L665:
	mov	r0, r7, asl #24
	cmp	r0, r8
	bhi	.L666
	ldr	r3, [r5, #36]
	rsb	r8, r0, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L759
.L667:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L668
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L760
.L670:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L675
	ldr	r2, [r5, #36]
	rsb	r8, r3, r8
	rsb	r7, r7, r2
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L761
.L677:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L681
	ldr	r1, [r5, #36]
	rsb	r8, r3, r8
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r1
	mov	r2, #1
	add	r3, r6, r7
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L682
.L686:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L762
.L682:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L686
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
	b	.L686
.L666:
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L698:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #3
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L695
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L758:
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
	b	.L665
.L753:
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
	b	.L635
.L602:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	ldr	r9, [r5, #28]
	rsb	r8, r4, #16
	add	r4, r4, r10
	mov	r1, r10
	rsb	r8, r10, r8
	bl	BsGet
	and	r8, r8, #7
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r8
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L603
.L606:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L611
.L609:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L612
.L611:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L609
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
	b	.L609
.L752:
	cmp	r9, #64
	mov	r3, r8
	bgt	.L763
.L626:
	add	r9, r9, #64
.L612:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #1958]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L629
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L630
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L630:
	add	r3, r3, #1
.L632:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1958]
	ldr	r8, [r5, #28]
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L696
.L629:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L633
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L633:
	rsb	r3, r3, #255
	b	.L632
.L668:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L673
.L671:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L674
.L673:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L671
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
	b	.L671
.L762:
	cmp	r9, #64
	ble	.L688
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L688:
	add	r9, r9, #64
.L674:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #1960]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L689
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L690
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L690:
	add	r3, r3, #1
.L692:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1960]
	b	.L698
.L689:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L693
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L693:
	rsb	r3, r3, #255
	b	.L692
.L638:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L643
.L641:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L644
.L643:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L641
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
	b	.L641
.L757:
	cmp	r9, #64
	ble	.L658
	mov	r1, #128
	mov	r0, r5
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L658:
	add	r9, r9, #64
.L644:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #1959]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L659
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L660
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L660:
	add	r3, r3, #1
.L662:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1959]
	ldr	r8, [r5, #28]
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L697
.L659:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L663
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L663:
	rsb	r3, r3, #255
	b	.L662
.L619:
	add	r3, r6, r7
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L623
.L621:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L764
.L623:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L621
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
	b	.L621
.L681:
	add	r3, r6, r7
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L685
.L683:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L765
.L685:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L683
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
	b	.L683
.L651:
	add	r3, r6, r7
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L655
.L653:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L766
.L655:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L653
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
	b	.L653
.L675:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L680
.L678:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L767
.L680:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L678
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
	b	.L678
.L645:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L650
.L648:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L768
.L650:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L648
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
	b	.L648
.L613:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L618
.L772:
	.align	2
.L771:
	.word	.LANCHOR0
.L616:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L769
.L618:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L616
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
	b	.L616
.L769:
	add	r9, r9, #16
	b	.L612
.L768:
	add	r9, r9, #16
	b	.L644
.L767:
	add	r9, r9, #16
	b	.L674
.L766:
	add	r9, r9, #32
	b	.L644
.L765:
	add	r9, r9, #32
	b	.L674
.L764:
	add	r9, r9, #32
	b	.L612
.L754:
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
	b	.L637
.L759:
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
	b	.L667
.L749:
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
	b	.L605
.L763:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r9, r9, asl #1
	add	r7, r7, #1
	sub	r9, r9, #65
	movge	r0, r8
	blt	.L770
.L627:
	mov	r2, r7, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r9, r9, r1
	rsbls	r7, r7, r3
	add	r2, r6, r7
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L626
.L760:
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
	b	.L670
.L755:
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
	b	.L640
.L750:
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
	b	.L608
.L761:
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
	b	.L677
.L756:
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
	b	.L647
.L751:
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
	b	.L615
.L770:
	rsb	r1, r4, #24
	str	r8, [fp, #-56]
	bic	r1, r1, #7
	rsb	r8, r4, #16
	mov	r0, r5
	rsb	r8, r1, r8
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	and	r8, r8, #7
	orr	r0, r3, r0, asl r8
	b	.L627
	UNWIND(.fnend)
	.size	Vp9_ReadInterModeProbs, .-Vp9_ReadInterModeProbs
	.align	2
	.global	Vp9_ReadSwitchableInterpProbs
	.type	Vp9_ReadSwitchableInterpProbs, %function
Vp9_ReadSwitchableInterpProbs:
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
	ldr	r6, .L894
	mov	r5, r1
	add	r3, r0, #8
	str	r0, [fp, #-48]
	str	r3, [fp, #-52]
.L839:
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L774
	ldr	r8, [r5, #28]
.L775:
	mov	r0, r7, asl #24
	cmp	r0, r8
	bhi	.L776
	ldr	r3, [r5, #36]
	rsb	r8, r0, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L879
.L777:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L778
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L880
.L780:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L785
	ldr	r2, [r5, #36]
	rsb	r8, r3, r8
	rsb	r7, r7, r2
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L881
.L787:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L791
	ldr	r1, [r5, #36]
	rsb	r8, r3, r8
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r1
	mov	r2, #1
	add	r3, r6, r7
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L792
.L796:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L882
.L792:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L796
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
	b	.L796
.L776:
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L840:
	sub	r7, r7, #1
	cmp	r4, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L883
.L807:
	mov	r0, r7, asl #24
	cmp	r0, r8
	bhi	.L808
	ldr	r3, [r5, #36]
	rsb	r8, r0, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L884
.L809:
	mov	r2, r7, asl #24
	cmp	r2, r8
	bhi	.L810
	ldr	r3, [r5, #36]
	rsb	r8, r2, r8
	rsb	r7, r7, r3
	add	r3, r6, r7
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L885
.L812:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L817
	ldr	r2, [r5, #36]
	rsb	r8, r3, r8
	rsb	r7, r7, r2
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L886
.L819:
	mov	r3, r7, asl #24
	cmp	r3, r8
	bhi	.L823
	ldr	r1, [r5, #36]
	rsb	r8, r3, r8
	mov	r9, #0
	mov	r10, #6
	rsb	r7, r7, r1
	mov	r2, #1
	add	r3, r6, r7
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r3, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	mov	r8, r3
	str	r7, [r5, #36]
	b	.L824
.L828:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L887
.L824:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L828
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
	b	.L828
.L808:
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L841:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #2
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L839
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L883:
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
	b	.L807
.L774:
	rsb	r10, r4, #24
	mov	r0, r5
	bic	r10, r10, #7
	ldr	r9, [r5, #28]
	rsb	r8, r4, #16
	add	r4, r4, r10
	mov	r1, r10
	rsb	r8, r10, r8
	bl	BsGet
	and	r8, r8, #7
	str	r4, [r5, #32]
	orr	r0, r9, r0, asl r8
	str	r0, [r5, #28]
	mov	r8, r0
	b	.L775
.L785:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L790
.L788:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L888
.L790:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L788
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
	b	.L788
.L817:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L822
.L820:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L889
.L822:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L820
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
	b	.L820
.L778:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L783
.L781:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L784
.L783:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L781
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
	b	.L781
.L882:
	cmp	r9, #64
	mov	r3, r8
	ble	.L798
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r9, r9, asl #1
	add	r7, r7, #1
	sub	r9, r9, #65
	movge	r0, r8
	blt	.L890
.L799:
	mov	r2, r7, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r9, r9, r1
	rsbls	r7, r7, r3
	add	r2, r6, r7
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L798:
	add	r9, r9, #64
.L784:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #1950]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L801
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L802
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L802:
	add	r3, r3, #1
.L804:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1950]
	ldr	r8, [r5, #28]
	ldr	r7, [r5, #36]
	ldr	r4, [r5, #32]
	b	.L840
.L801:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L805
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L805:
	rsb	r3, r3, #255
	b	.L804
.L810:
	add	r1, r6, r7
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r10, r3
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L815
.L813:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L816
.L815:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L813
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
	b	.L813
.L887:
	cmp	r9, #64
	mov	r3, r8
	ble	.L830
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r9, r9, asl #1
	add	r7, r7, #1
	sub	r9, r9, #65
	movge	r0, r8
	blt	.L891
.L831:
	mov	r2, r7, asl #24
	cmp	r2, r0
	rsbls	r0, r2, r0
	ldrls	r3, [r5, #36]
	movls	r1, #1
	movhi	r1, #0
	add	r9, r9, r1
	rsbls	r7, r7, r3
	add	r2, r6, r7
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r0, asl r2
	rsb	r4, r2, r4
	mov	r7, r7, asl r2
	str	r3, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
.L830:
	add	r9, r9, #64
.L816:
	ldr	r3, [fp, #-48]
	add	r9, r6, r9
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #1951]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L833
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L834
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L834:
	add	r3, r3, #1
.L836:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1951]
	b	.L841
.L833:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L837
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L837:
	rsb	r3, r3, #255
	b	.L836
.L889:
	add	r9, r9, #16
	b	.L816
.L888:
	add	r9, r9, #16
	b	.L784
.L791:
	add	r3, r6, r7
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L795
.L793:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L892
.L795:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L793
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
	b	.L793
.L823:
	add	r3, r6, r7
	mov	r9, #0
	mov	r10, #4
	mov	r2, #1
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r4, r1, r4
	mov	r7, r7, asl r1
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	b	.L827
.L825:
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
	add	r3, r6, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r7, r7, asl r3
	str	r8, [r5, #28]
	str	r4, [r5, #32]
	str	r7, [r5, #36]
	beq	.L893
.L827:
	sub	r7, r7, #1
	cmp	r4, #0
	ubfx	r7, r7, #1, #24
	mov	r0, r8
	add	r7, r7, #1
	bge	.L825
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
	b	.L825
.L892:
	add	r9, r9, #32
	b	.L784
.L893:
	add	r9, r9, #32
	b	.L816
.L884:
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
	b	.L809
.L879:
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
	b	.L777
.L880:
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
	b	.L780
.L885:
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
	b	.L812
.L881:
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
	b	.L787
.L886:
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
	b	.L819
.L891:
	rsb	r1, r4, #24
	str	r8, [fp, #-56]
	bic	r1, r1, #7
	rsb	r8, r4, #16
	mov	r0, r5
	rsb	r8, r1, r8
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	and	r8, r8, #7
	orr	r0, r3, r0, asl r8
	b	.L831
.L890:
	rsb	r1, r4, #24
	str	r8, [fp, #-56]
	bic	r1, r1, #7
	rsb	r8, r4, #16
	mov	r0, r5
	rsb	r8, r1, r8
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-56]
	and	r8, r8, #7
	orr	r0, r3, r0, asl r8
	b	.L799
.L895:
	.align	2
.L894:
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
	bne	.L1059
	str	r2, [fp, #-56]
	ldr	r4, [r1, #28]
	ldr	r3, [r1, #36]
	ldr	r5, [r1, #32]
	ldr	r2, .L1085
.L905:
	ldr	r1, [fp, #-60]
	mov	r10, r4
	mov	r9, r3
	mov	r7, r2
	add	r0, r1, #10
	str	r0, [fp, #-52]
	str	r1, [fp, #-48]
.L968:
	sub	r9, r9, #1
	cmp	r5, #0
	mov	r2, r9, asl #8
	sub	r9, r2, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L1060
.L907:
	mov	r8, r9, asl #24
	cmp	r8, r10
	bhi	.L908
	ldr	r3, [r6, #36]
	rsb	r8, r8, r10
	rsb	r9, r9, r3
	add	r3, r7, r9
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1061
.L909:
	mov	r2, r10, asl #24
	cmp	r2, r8
	bhi	.L910
	ldr	r3, [r6, #36]
	rsb	r8, r2, r8
	rsb	r3, r10, r3
	add	r2, r7, r3
	ldrb	r10, [r2, #24]	@ zero_extendqisi2
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
	blt	.L1062
.L912:
	mov	r8, r5, asl #24
	cmp	r8, r10
	bhi	.L917
	ldr	r2, [r6, #36]
	rsb	r10, r8, r10
	rsb	r5, r5, r2
	add	r3, r7, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1063
.L919:
	mov	r3, r5, asl #24
	cmp	r3, r10
	bhi	.L923
	ldr	r4, [r6, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r5, r5, r4
	mov	r2, #1
	add	r1, r7, r5
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r6, #28]
	mov	r4, r5, asl r4
	str	r8, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L924
.L928:
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
	add	r3, r7, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r5, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1064
.L924:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L928
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
	b	.L928
.L908:
	add	r3, r7, r9
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r5
	mov	r9, r9, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r9, [r6, #36]
.L1003:
	sub	r9, r9, #1
	cmp	r4, #0
	mov	r3, r9, asl #8
	sub	r9, r3, r9, asl #2
	mov	r9, r9, lsr #8
	add	r9, r9, #1
	blt	.L1065
.L937:
	mov	r8, r9, asl #24
	cmp	r8, r10
	bhi	.L938
	ldr	r3, [r6, #36]
	rsb	r10, r8, r10
	rsb	r9, r9, r3
	add	r3, r7, r9
	ldrb	r8, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1066
.L939:
	mov	r8, r5, asl #24
	cmp	r8, r10
	bhi	.L940
	ldr	r3, [r6, #36]
	rsb	r8, r8, r10
	rsb	r5, r5, r3
	add	r3, r7, r5
	ldrb	r10, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1067
.L942:
	mov	r8, r5, asl #24
	cmp	r8, r10
	bhi	.L947
	ldr	r2, [r6, #36]
	rsb	r10, r8, r10
	rsb	r5, r5, r2
	add	r3, r7, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1068
.L949:
	mov	r3, r5, asl #24
	cmp	r3, r10
	bhi	.L953
	ldr	r4, [r6, #36]
	rsb	r3, r3, r10
	mov	r9, #0
	mov	r10, #6
	rsb	r5, r5, r4
	mov	r2, #1
	add	r1, r7, r5
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r4
	rsb	r8, r4, r8
	str	r3, [r6, #28]
	mov	r4, r5, asl r4
	str	r8, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L954
.L958:
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
	add	r3, r7, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r5, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1069
.L954:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L958
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
	b	.L958
.L938:
	add	r3, r7, r9
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r3
	rsb	r4, r3, r4
	mov	r9, r9, asl r3
	str	r10, [r6, #28]
	str	r4, [r6, #32]
	str	r9, [r6, #36]
.L1004:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #2
	str	r3, [fp, #-48]
	cmp	r3, r2
	ldrne	r10, [r6, #28]
	ldrne	r9, [r6, #36]
	ldrne	r5, [r6, #32]
	bne	.L968
.L967:
	ldr	r3, [fp, #-56]
	mov	r2, r7
	cmp	r3, #0
	bne	.L1070
.L999:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-56]
	str	r2, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1070:
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r5, [r6, #32]
.L906:
	ldr	r1, [fp, #-60]
	mov	r8, r3
	mov	r10, r2
	add	r7, r1, #1984
	add	r1, r1, #2000
	add	r7, r7, #14
	add	r1, r1, #3
	str	r7, [fp, #-48]
	str	r1, [fp, #-52]
.L1000:
	sub	r8, r8, #1
	cmp	r5, #0
	mov	r2, r8, asl #8
	sub	r8, r2, r8, asl #2
	mov	r8, r8, lsr #8
	add	r8, r8, #1
	blt	.L1071
.L969:
	mov	r7, r8, asl #24
	cmp	r7, r4
	bhi	.L970
	ldr	r3, [r6, #36]
	rsb	r7, r7, r4
	rsb	r8, r8, r3
	add	r3, r10, r8
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1072
.L971:
	mov	r2, r9, asl #24
	cmp	r2, r7
	bhi	.L972
	ldr	r3, [r6, #36]
	rsb	r7, r2, r7
	rsb	r9, r9, r3
	add	r3, r10, r9
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1073
.L974:
	mov	r3, r9, asl #24
	cmp	r3, r7
	bhi	.L979
	ldr	r5, [r6, #36]
	rsb	r7, r3, r7
	rsb	r9, r9, r5
	add	r3, r10, r9
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1074
.L981:
	mov	r3, r5, asl #24
	cmp	r3, r7
	bhi	.L985
	ldr	r1, [r6, #36]
	rsb	r7, r3, r7
	mov	r8, #0
	mov	r9, #6
	rsb	r5, r5, r1
	mov	r2, #1
	add	r3, r10, r5
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r3, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r3, [r6, #28]
	str	r4, [r6, #32]
	mov	r7, r3
	str	r5, [r6, #36]
	b	.L986
.L990:
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
	add	r3, r10, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1075
.L986:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L990
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
	b	.L990
.L947:
	add	r1, r7, r5
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r3
	str	r5, [r6, #36]
	b	.L952
.L950:
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
	add	r3, r7, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1076
.L952:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L950
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
	b	.L950
.L917:
	add	r1, r7, r5
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r3
	str	r5, [r6, #36]
	b	.L922
.L920:
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
	add	r3, r7, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1077
.L922:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L920
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
	b	.L920
.L970:
	add	r3, r10, r8
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	mov	r8, r8, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r8, [r6, #36]
.L1005:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	beq	.L999
	add	r4, r6, #28
	ldmia	r4, {r4, r5, r8}
	b	.L1000
.L1065:
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
	b	.L937
.L1060:
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
	b	.L907
.L940:
	add	r1, r7, r5
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r10, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r3
	str	r5, [r6, #36]
	b	.L945
.L943:
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
	add	r3, r7, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L946
.L945:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L943
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
	b	.L943
.L1069:
	cmp	r9, #64
	ble	.L960
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L960:
	add	r9, r9, #64
.L946:
	ldr	r3, [fp, #-48]
	add	r9, r7, r9
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #1989]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L961
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L962
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L962:
	add	r3, r3, #1
.L964:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1989]
	b	.L1004
.L961:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L965
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L965:
	rsb	r3, r3, #255
	b	.L964
.L910:
	add	r1, r7, r10
	mov	r3, #3
	mov	r9, #0
	mov	r2, #1
	ldrb	r5, [r1, #24]	@ zero_extendqisi2
	mov	r10, r10, asl r5
	mov	r8, r8, asl r5
	rsb	r4, r5, r4
	str	r10, [r6, #36]
	mov	r5, r10
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	mov	r10, r3
	b	.L915
.L913:
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
	add	r3, r7, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r8, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L916
.L915:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r8
	add	r5, r5, #1
	bge	.L913
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
	b	.L913
.L1064:
	cmp	r9, #64
	ble	.L930
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r9, lsl #1
	sub	r9, r0, #65
.L930:
	add	r9, r9, #64
.L916:
	ldr	r3, [fp, #-48]
	add	r9, r7, r9
	ldrb	r1, [r9, #280]	@ zero_extendqisi2
	ldrb	r2, [r3, #1988]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L931
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L932
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L932:
	add	r3, r3, #1
.L934:
	ldr	r2, [fp, #-48]
	strb	r3, [r2, #1988]
	ldr	r10, [r6, #28]
	ldr	r9, [r6, #36]
	ldr	r4, [r6, #32]
	b	.L1003
.L931:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L935
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L935:
	rsb	r3, r3, #255
	b	.L934
.L1071:
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
	b	.L969
.L972:
	add	r1, r10, r9
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r4
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r9, [r6, #36]
	mov	r4, r9
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	mov	r9, r3
	b	.L977
.L975:
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
	add	r3, r10, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L978
.L977:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L975
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
	b	.L975
.L1075:
	cmp	r8, #64
	ble	.L992
	mov	r1, #128
	mov	r0, r6
	bl	Vp9_Cabac_Read
	add	r0, r0, r8, lsl #1
	sub	r8, r0, #65
.L992:
	add	r8, r8, #64
.L978:
	ldr	r3, [fp, #-48]
	add	r8, r10, r8
	ldrb	r1, [r8, #280]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	ip, r2, #1
	mov	r0, ip, asl #1
	cmp	r0, #255
	bgt	.L993
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L994
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L994:
	add	r3, r3, #1
.L996:
	ldr	r2, [fp, #-48]
	strb	r3, [r2]
	b	.L1005
.L993:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L997
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L997:
	rsb	r3, r3, #255
	b	.L996
.L1059:
	ldr	r7, [r1, #36]
	ldr	r5, [r1, #32]
	sub	r7, r7, #1
	cmp	r5, #0
	ubfx	r7, r7, #1, #24
	add	r7, r7, #1
	blt	.L898
	ldr	r0, [r1, #28]
.L899:
	mov	r4, r7, asl #24
	cmp	r4, r0
	bhi	.L900
	ldr	r3, [r6, #36]
	rsb	r4, r4, r0
	ldr	r2, .L1085
	mov	r1, #128
	rsb	r7, r7, r3
	mov	r0, r6
	add	r3, r2, r7
	str	r2, [fp, #-48]
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	mov	r7, r7, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r7, [r6, #36]
	bl	Vp9_Cabac_Read
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r5, [r6, #32]
	add	r2, r0, #1
	str	r2, [fp, #-56]
	cmp	r2, #2
	ldr	r2, [fp, #-48]
	bne	.L901
	ldr	r1, [fp, #-60]
	mov	r10, r2
	add	r8, r1, #1968
	add	r9, r1, #1984
	add	r8, r8, #15
	add	r9, r9, #4
	b	.L904
.L1080:
	ldr	r3, [r6, #36]
	add	r8, r8, #1
	rsb	r7, r7, r3
	add	r3, r10, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	rsb	r5, r3, r5
	mov	r2, r2, asl r3
	mov	r7, r7, asl r3
	str	r5, [r6, #32]
	str	r2, [r6, #28]
	str	r7, [r6, #36]
	bl	Vp9_DiffUpdateProb
	cmp	r8, r9
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r5, [r6, #32]
	beq	.L1078
.L904:
	sub	r7, r3, #1
	cmp	r5, #0
	mov	r3, r7, asl #8
	sub	r7, r3, r7, asl #2
	mov	r7, r7, lsr #8
	add	r7, r7, #1
	blt	.L1079
.L902:
	mov	r3, r7, asl #24
	mov	r1, r8
	cmp	r3, r4
	mov	r0, r6
	rsb	r2, r3, r4
	bls	.L1080
	add	r3, r10, r7
	add	r8, r8, #1
	cmp	r8, r9
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r5
	str	r4, [r6, #28]
	mov	r3, r7, asl r3
	str	r5, [r6, #32]
	str	r3, [r6, #36]
	bne	.L904
.L1078:
	mov	r2, r10
	b	.L905
.L1076:
	add	r9, r9, #16
	b	.L946
.L1077:
	add	r9, r9, #16
	b	.L916
.L979:
	add	r1, r10, r9
	mov	r3, #3
	mov	r8, #0
	mov	r2, #1
	ldrb	r5, [r1, #24]	@ zero_extendqisi2
	mov	r9, r9, asl r5
	mov	r7, r7, asl r5
	rsb	r4, r5, r4
	str	r9, [r6, #36]
	mov	r5, r9
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	mov	r9, r3
	b	.L984
.L982:
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
	add	r3, r10, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1081
.L984:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L982
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
	b	.L982
.L900:
	ldr	r2, .L1085
	mov	r3, #0
	str	r3, [fp, #-56]
	add	r3, r2, r7
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r0, asl r3
	rsb	r5, r3, r5
	str	r4, [r6, #28]
	mov	r3, r7, asl r3
	str	r5, [r6, #32]
	str	r3, [r6, #36]
	b	.L905
.L1081:
	add	r8, r8, #16
	b	.L978
.L1086:
	.align	2
.L1085:
	.word	.LANCHOR0
.L1079:
	rsb	r2, r5, #24
	rsb	r3, r5, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r3, r2, r3
	str	r2, [fp, #-48]
	mov	r1, r2
	str	r3, [fp, #-52]
	bl	BsGet
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-48]
	and	r3, r3, #7
	add	r5, r2, r5
	str	r5, [r6, #32]
	orr	r0, r4, r0, asl r3
	str	r0, [r6, #28]
	mov	r4, r0
	b	.L902
.L923:
	add	r1, r7, r5
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r5, r5, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r5, [r6, #36]
	mov	r4, r5
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	mov	r5, r2
	b	.L927
.L925:
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
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1082
.L927:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L925
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
	b	.L925
.L953:
	add	r1, r7, r5
	mov	r2, #4
	mov	r9, #0
	mov	r3, #1
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r5, r5, asl r4
	mov	r10, r10, asl r4
	rsb	r8, r4, r8
	str	r5, [r6, #36]
	mov	r4, r5
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	mov	r5, r2
	b	.L957
.L955:
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
	add	r2, r7, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r10, r0, asl r2
	rsb	r8, r2, r8
	mov	r4, r4, asl r2
	str	r10, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1083
.L957:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r10
	add	r4, r4, #1
	bge	.L955
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
	b	.L955
.L1083:
	add	r9, r9, #32
	b	.L946
.L1082:
	add	r9, r9, #32
	b	.L916
.L1061:
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
	b	.L909
.L1066:
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
	b	.L939
.L985:
	add	r3, r10, r5
	mov	r8, #0
	mov	r9, #4
	mov	r2, #1
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	b	.L989
.L987:
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
	add	r3, r10, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1084
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
	str	r2, [fp, #-68]
	str	r3, [fp, #-60]
	add	r4, r1, r4
	bl	BsGet
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-68]
	and	r3, r3, #7
	orr	r0, r7, r0, asl r3
	b	.L987
.L1084:
	add	r8, r8, #32
	b	.L978
.L1072:
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
	b	.L971
.L1062:
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
	b	.L912
.L1067:
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
	b	.L942
.L1073:
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
	b	.L974
.L1068:
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
	b	.L949
.L1063:
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
	b	.L919
.L1074:
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
	b	.L981
.L898:
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
	b	.L899
.L901:
	ldr	r1, [fp, #-56]
	cmp	r1, #1
	beq	.L906
	b	.L905
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
	ldr	r4, [r0, #36]
	ldr	r6, [r0, #32]
	mov	r3, r1
	ldr	r5, [r0, #28]
	mov	r10, r0
	str	r2, [fp, #-76]
	mov	r2, r3
	str	r1, [fp, #-72]
	add	r1, r1, #3
	str	r3, [fp, #-80]
	str	r1, [fp, #-48]
.L1093:
	sub	r1, r4, #1
	cmp	r6, #0
	mov	r4, r1, asl #8
	sub	r1, r4, r1, asl #2
	mov	r1, r1, lsr #8
	add	r4, r1, #1
	blt	.L1195
.L1088:
	mov	r7, r4, asl #24
	cmp	r7, r5
	bhi	.L1089
	ldr	r1, [r10, #36]
	rsb	r7, r7, r5
	ldr	r0, .L1213
	mov	r9, #0
	rsb	r1, r4, r1
	mov	r8, #6
	add	r0, r0, r1
	mov	r3, #1
	str	r2, [fp, #-56]
	ldrb	r4, [r0, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r6
	str	r7, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1092
.L1090:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldr	r2, .L1213
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1196
.L1092:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1090
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
	b	.L1090
.L1089:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r5, r5, asl r1
	rsb	r6, r1, r6
	mov	r4, r4, asl r1
	str	r5, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
.L1150:
	ldr	r3, [fp, #-48]
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L1093
	ldr	r3, [fp, #-72]
	mov	r7, r5
	add	r2, r3, #25
	add	r3, r3, #91
	str	r2, [fp, #-48]
	str	r3, [fp, #-64]
.L1120:
	sub	r4, r4, #1
	cmp	r6, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1197
.L1094:
	mov	r2, r4, asl #24
	cmp	r2, r7
	bhi	.L1095
	ldr	r3, [r10, #36]
	rsb	r7, r2, r7
	ldr	r2, .L1213
	mov	r5, #0
	rsb	r4, r4, r3
	mov	r9, #6
	add	r2, r2, r4
	mov	r3, #1
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r7, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L1098
.L1096:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r9
	cmp	r2, r0
	sub	r9, r9, #1
	rsbls	r0, r2, r0
	ldr	r2, .L1213
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r5, r5, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r8, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1198
.L1098:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1096
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
	b	.L1096
.L1196:
	ldr	r2, [fp, #-56]
	mov	r3, r9, asl #1
	orr	r3, r3, #1
	strb	r3, [r2]
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r5, [r10, #28]
	b	.L1150
.L1095:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r5, r3, r6
	mov	r4, r4, asl r3
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
.L1151:
	ldr	r3, [fp, #-48]
	sub	r2, r3, #21
	sub	r3, r3, #11
	str	r3, [fp, #-52]
.L1104:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r1, r4, asl #8
	sub	r4, r1, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1199
.L1099:
	mov	r3, r4, asl #24
	cmp	r3, r7
	bhi	.L1100
	ldr	r1, [r10, #36]
	rsb	r7, r3, r7
	ldr	r0, .L1213
	mov	r9, #0
	rsb	r1, r4, r1
	mov	r8, #6
	add	r0, r0, r1
	mov	r3, #1
	str	r2, [fp, #-60]
	ldrb	r4, [r0, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r7, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1103
.L1101:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldr	r2, .L1213
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1200
.L1103:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1101
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
	b	.L1101
.L1100:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
.L1152:
	ldr	r3, [fp, #-52]
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L1104
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1201
.L1105:
	mov	r2, r4, asl #24
	cmp	r2, r7
	bhi	.L1106
	ldr	r3, [r10, #36]
	rsb	r7, r2, r7
	ldr	r2, .L1213
	mov	r8, #6
	rsb	r4, r4, r3
	mov	r9, #0
	add	r2, r2, r4
	mov	r3, #1
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1109
.L1108:
	ldr	ip, [r10, #36]
	rsb	r0, r2, r0
	rsb	r4, r4, ip
.L1111:
	ldr	r2, .L1213
	sub	r8, r8, #1
	cmn	r8, #1
	orr	r9, r9, r1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1202
.L1109:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	blt	.L1107
.L1112:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r8
	cmp	r2, r0
	bls	.L1108
	mov	r1, #0
	b	.L1111
.L1200:
	ldr	r2, [fp, #-60]
	mov	r9, r9, asl #1
	orr	r9, r9, #1
	strb	r9, [r2]
	ldr	r5, [r10, #32]
	ldr	r4, [r10, #36]
	ldr	r7, [r10, #28]
	b	.L1152
.L1199:
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
	b	.L1099
.L1107:
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
	b	.L1112
.L1106:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r6, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
.L1113:
	ldr	r3, [fp, #-48]
	sub	r2, r3, #10
.L1119:
	sub	r4, r4, #1
	cmp	r6, #0
	mov	r1, r4, asl #8
	sub	r4, r1, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1203
.L1114:
	mov	r3, r4, asl #24
	cmp	r3, r7
	bhi	.L1115
	ldr	r1, [r10, #36]
	rsb	r7, r3, r7
	ldr	r0, .L1213
	mov	r9, #0
	rsb	r1, r4, r1
	mov	r8, #6
	add	r0, r0, r1
	mov	r3, #1
	str	r2, [fp, #-56]
	ldrb	r4, [r0, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r6
	str	r7, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1118
.L1116:
	mov	r2, r4, asl #24
	mov	r1, r3, asl r8
	cmp	r2, r0
	sub	r8, r8, #1
	rsbls	r0, r2, r0
	ldr	r2, .L1213
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r9, r9, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1204
.L1118:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1116
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
	b	.L1116
.L1115:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r1
	rsb	r6, r1, r6
	mov	r4, r4, asl r1
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
.L1153:
	ldr	r3, [fp, #-48]
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L1119
	add	r3, r2, #33
	ldr	r2, [fp, #-64]
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L1120
	ldr	r3, [fp, #-72]
	add	r2, r3, #31
	add	r3, r3, #97
	str	r2, [fp, #-64]
	str	r3, [fp, #-68]
.L1121:
	ldr	r3, [fp, #-64]
	sub	r3, r3, #6
	str	r3, [fp, #-48]
	mov	r3, #2
	str	r3, [fp, #-60]
.L1136:
	ldr	r2, [fp, #-48]
	mov	r3, #0
	mov	r5, r6
	mov	r6, r3
.L1127:
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1205
.L1122:
	mov	r3, r4, asl #24
	cmp	r3, r7
	bhi	.L1123
	ldr	r1, [r10, #36]
	rsb	r7, r3, r7
	mov	r9, #0
	str	r6, [fp, #-52]
	rsb	r3, r4, r1
	ldr	r1, .L1213
	mov	r8, #6
	mov	r6, r9
	add	r1, r1, r3
	str	r2, [fp, #-56]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r5, r4, r5
	str	r7, [r10, #28]
	mov	r4, r3, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1126
.L1124:
	mov	r2, r4, asl #24
	mov	r3, #1
	cmp	r2, r0
	mov	r1, r3, asl r8
	ldr	r3, .L1213
	rsbls	r0, r2, r0
	ldrls	ip, [r10, #36]
	sub	r8, r8, #1
	movhi	r1, #0
	orr	r6, r6, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r2, r3, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1206
.L1126:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1124
	rsb	r1, r5, #24
	rsb	r2, r5, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r9, r1, r2
	add	r5, r1, r5
	bl	BsGet
	and	r2, r9, #7
	orr	r0, r7, r0, asl r2
	b	.L1124
.L1204:
	ldr	r2, [fp, #-56]
	mov	r9, r9, asl #1
	orr	r9, r9, #1
	strb	r9, [r2]
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1153
.L1123:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
.L1154:
	add	r6, r6, #1
	add	r2, r2, #1
	cmp	r6, #3
	bne	.L1127
	ldr	r3, [fp, #-60]
	mov	r6, r5
	subs	r3, r3, #1
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-48]
	add	r3, r3, #3
	str	r3, [fp, #-48]
	bne	.L1136
	ldr	r5, [fp, #-60]
	ldr	r3, [fp, #-64]
.L1128:
	sub	r4, r4, #1
	cmp	r6, #0
	mov	r2, r4, asl #8
	sub	r4, r2, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1207
.L1129:
	mov	r1, r4, asl #24
	cmp	r1, r7
	bhi	.L1130
	ldr	r2, [r10, #36]
	rsb	r7, r1, r7
	ldr	r1, .L1213
	mov	r9, #0
	rsb	r2, r4, r2
	str	r5, [fp, #-48]
	add	r1, r1, r2
	mov	r8, #6
	mov	r5, r9
	str	r3, [fp, #-52]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	rsb	r6, r4, r6
	str	r7, [r10, #28]
	mov	r4, r2, asl r4
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	b	.L1133
.L1131:
	mov	r2, r4, asl #24
	mov	r3, #1
	cmp	r2, r0
	mov	r1, r3, asl r8
	ldr	r3, .L1213
	rsbls	r0, r2, r0
	ldrls	ip, [r10, #36]
	sub	r8, r8, #1
	movhi	r1, #0
	orr	r5, r5, r1
	rsbls	r4, r4, ip
	cmn	r8, #1
	add	r2, r3, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1208
.L1133:
	sub	r4, r4, #1
	cmp	r6, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1131
	rsb	r1, r6, #24
	rsb	r2, r6, #16
	bic	r1, r1, #7
	mov	r0, r10
	rsb	r9, r1, r2
	add	r6, r1, r6
	bl	BsGet
	and	r2, r9, #7
	orr	r0, r7, r0, asl r2
	b	.L1131
.L1206:
	ldr	r2, [fp, #-56]
	mov	r9, r6
	mov	r9, r9, asl #1
	ldr	r6, [fp, #-52]
	orr	r9, r9, #1
	strb	r9, [r2]
	ldr	r4, [r10, #36]
	ldr	r5, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1154
.L1203:
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
	b	.L1114
.L1130:
	ldr	r2, .L1213
	add	r5, r5, #1
	cmp	r5, #3
	add	r3, r3, #1
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r2
	rsb	r6, r2, r6
	mov	r4, r4, asl r2
	str	r7, [r10, #28]
	str	r6, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1134
.L1209:
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1128
.L1208:
	mov	r9, r5
	ldr	r5, [fp, #-48]
	ldr	r3, [fp, #-52]
	mov	r9, r9, asl #1
	add	r5, r5, #1
	orr	r9, r9, #1
	cmp	r5, #3
	add	r3, r3, #1
	strb	r9, [r3, #-1]
	bne	.L1209
.L1134:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	add	r3, r3, #33
	str	r3, [fp, #-64]
	cmp	r3, r2
	beq	.L1135
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1121
.L1205:
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
	b	.L1122
.L1207:
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
	b	.L1129
.L1198:
	ldr	r2, [fp, #-48]
	mov	r3, r5, asl #1
	orr	r3, r3, #1
	strb	r3, [r2, #-22]
	ldr	r4, [r10, #36]
	ldr	r5, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1151
.L1202:
	ldr	r2, [fp, #-48]
	mov	r3, r9, asl #1
	orr	r3, r3, #1
	strb	r3, [r2, #-11]
	ldr	r4, [r10, #36]
	ldr	r6, [r10, #32]
	ldr	r7, [r10, #28]
	b	.L1113
.L1135:
	ldr	r3, [fp, #-76]
	cmp	r3, #0
	beq	.L1087
	ldr	r8, [fp, #-80]
	ldr	r3, [fp, #-72]
	add	r3, r3, #66
	str	r3, [fp, #-48]
.L1148:
	ldr	r1, [r10, #36]
	ldr	r5, [r10, #32]
	sub	r1, r1, #1
	cmp	r5, #0
	mov	r3, r1, asl #8
	sub	r1, r3, r1, asl #2
	mov	r1, r1, lsr #8
	add	r4, r1, #1
	blt	.L1137
	ldr	r6, [r10, #28]
.L1138:
	mov	r3, r4, asl #24
	cmp	r3, r6
	bhi	.L1139
	ldr	r1, [r10, #36]
	rsb	r6, r3, r6
	ldr	r0, .L1213
	mov	r3, #0
	rsb	r1, r4, r1
	mov	r9, #6
	add	r0, r0, r1
	mov	r2, #1
	mov	r7, r3
	str	r8, [fp, #-56]
	ldrb	r4, [r0, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r4
	rsb	r5, r4, r5
	str	r6, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	b	.L1142
.L1140:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r7, r7, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r6, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1210
.L1142:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r6
	add	r4, r4, #1
	bge	.L1140
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
	b	.L1140
.L1144:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r1, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r1
	rsb	r5, r1, r5
	str	r6, [r10, #28]
	mov	r1, r4, asl r1
	str	r5, [r10, #32]
	str	r1, [r10, #36]
.L1157:
	ldr	r3, [fp, #-48]
	add	r8, r8, #33
	cmp	r8, r3
	bne	.L1148
.L1087:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1139:
	ldr	r3, .L1213
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r6, r6, asl r3
	rsb	r5, r3, r5
	str	r6, [r10, #28]
	mov	r3, r4, asl r3
	str	r5, [r10, #32]
	str	r3, [r10, #36]
.L1156:
	sub	r3, r3, #1
	cmp	r5, #0
	mov	r1, r3, asl #8
	sub	r3, r1, r3, asl #2
	mov	r1, r3, lsr #8
	add	r4, r1, #1
	blt	.L1211
.L1143:
	mov	r3, r4, asl #24
	cmp	r3, r6
	bhi	.L1144
	ldr	r1, [r10, #36]
	rsb	r6, r3, r6
	ldr	r0, .L1213
	mov	r3, #0
	rsb	r1, r4, r1
	mov	r9, #6
	add	r0, r0, r1
	mov	r2, #1
	str	r8, [fp, #-56]
	ldrb	r4, [r0, #24]	@ zero_extendqisi2
	mov	r7, r6, asl r4
	rsb	r5, r4, r5
	str	r7, [r10, #28]
	mov	r4, r1, asl r4
	str	r5, [r10, #32]
	mov	r6, r3
	str	r4, [r10, #36]
	b	.L1147
.L1145:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r9
	cmp	r3, r0
	sub	r9, r9, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1213
	ldrls	ip, [r10, #36]
	movhi	r1, #0
	orr	r6, r6, r1
	rsbls	r4, r4, ip
	cmn	r9, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r7, [r10, #28]
	str	r5, [r10, #32]
	str	r4, [r10, #36]
	beq	.L1212
.L1147:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1145
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
	b	.L1145
.L1212:
	ldr	r8, [fp, #-56]
	mov	r3, r6, asl #1
	orr	r3, r3, #1
	strb	r3, [r8, #35]
	b	.L1157
.L1210:
	ldr	r8, [fp, #-56]
	mov	r3, r7, asl #1
	orr	r3, r3, #1
	strb	r3, [r8, #34]
	ldr	r3, [r10, #36]
	ldr	r5, [r10, #32]
	ldr	r6, [r10, #28]
	b	.L1156
.L1195:
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
	b	.L1088
.L1201:
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
	b	.L1105
.L1197:
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
	b	.L1094
.L1137:
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
	b	.L1138
.L1211:
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
	b	.L1143
.L1214:
	.align	2
.L1213:
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
	add	r7, r0, #2000
	str	r0, [fp, #-68]
	add	r0, r0, #2016
	add	r0, r0, #2
	add	r7, r7, #15
	mov	r6, r1
	mov	r8, r2
	mov	r5, r0
	str	r3, [fp, #-56]
	str	r0, [fp, #-76]
	mov	r3, #0
	str	r3, [fp, #-48]
.L1219:
	ldr	r4, [r6, #36]
	ldr	r9, [r6, #32]
	sub	r4, r4, #1
	cmp	r9, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1216
	ldr	r3, [r6, #28]
.L1217:
	mov	r2, r4, asl #24
	mov	r1, r7
	cmp	r2, r3
	mov	r0, r6
	rsb	ip, r2, r3
	bhi	.L1218
	ldr	r3, [r6, #36]
	rsb	r4, r4, r3
	ldr	r3, .L1365
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	ip, ip, asl r3
	rsb	r9, r3, r9
	mov	r4, r4, asl r3
	str	ip, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	bl	Vp9_DiffUpdateProb
.L1296:
	add	r7, r7, #1
	cmp	r7, r5
	bne	.L1219
	adds	r8, r8, #0
	ldr	r3, [fp, #-56]
	movne	r8, #1
	cmp	r3, #0
	movne	r8, #0
	cmp	r8, #0
	bne	.L1342
.L1220:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #16]
	str	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1218:
	ldr	r2, .L1365
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r9, r2, r9
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r9, [r6, #32]
	str	r4, [r6, #36]
	b	.L1296
.L1216:
	rsb	r2, r9, #24
	rsb	r3, r9, #16
	bic	r2, r2, #7
	mov	r0, r6
	rsb	r3, r2, r3
	ldr	r10, [r6, #28]
	mov	r1, r2
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	bl	BsGet
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-60]
	and	r3, r3, #7
	add	r9, r9, r2
	str	r9, [r6, #32]
	orr	r0, r10, r0, asl r3
	str	r0, [r6, #28]
	mov	r3, r0
	b	.L1217
.L1342:
	mov	r1, r6
	ldr	r0, [fp, #-68]
	bl	Vp9_ReadInterModeProbs
	ldr	r3, [fp, #4]
	cmp	r3, #4
	beq	.L1343
.L1221:
	ldr	r3, [fp, #-68]
	add	r9, r3, #1968
	mov	r10, r9
	add	r9, r9, #11
	add	r10, r10, #15
.L1225:
	ldr	r4, [r6, #36]
	ldr	r5, [r6, #32]
	sub	r4, r4, #1
	cmp	r5, #0
	mov	r3, r4, asl #8
	sub	r4, r3, r4, asl #2
	mov	r4, r4, lsr #8
	add	r4, r4, #1
	blt	.L1222
	ldr	r3, [r6, #28]
.L1223:
	mov	r2, r4, asl #24
	mov	r1, r9
	cmp	r2, r3
	mov	r0, r6
	rsb	ip, r2, r3
	bhi	.L1224
	ldr	r3, [r6, #36]
	rsb	r4, r4, r3
	ldr	r3, .L1365
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	ip, ip, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	ip, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	bl	Vp9_DiffUpdateProb
.L1297:
	add	r9, r9, #1
	cmp	r9, r10
	bne	.L1225
	ldr	ip, [fp, #-68]
	sub	r3, fp, #48
	ldr	r2, [fp, #8]
	mov	r1, r6
	add	lr, ip, #1728
	mov	r0, ip
	add	ip, ip, #1760
	mov	r4, lr
	mov	r5, ip
	bl	Vp9_ReadCompPred
	add	r3, r4, #9
	add	r4, r6, #28
	str	r3, [fp, #-56]
	mov	ip, r5
	add	r3, r5, #13
	str	r3, [fp, #-72]
	ldmia	r4, {r4, r5, r8}
	mov	r7, r5
.L1226:
	ldr	r3, [fp, #-56]
	mov	r10, r8
	sub	r9, r3, #9
.L1259:
	sub	r10, r10, #1
	cmp	r7, #0
	mov	r3, r10, asl #8
	sub	r10, r3, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1344
.L1227:
	mov	r8, r10, asl #24
	cmp	r8, r4
	bhi	.L1228
	ldr	r3, [r6, #36]
	rsb	r8, r8, r4
	rsb	r10, r10, r3
	ldr	r3, .L1365
	add	r3, r3, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1345
.L1229:
	mov	r3, r4, asl #24
	cmp	r3, r8
	bhi	.L1230
	ldr	r2, [r6, #36]
	rsb	r8, r3, r8
	ldr	r3, .L1365
	rsb	r4, r4, r2
	add	r3, r3, r4
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1346
.L1232:
	mov	r2, r5, asl #24
	cmp	r2, r8
	bhi	.L1237
	ldr	r3, [r6, #36]
	rsb	r8, r2, r8
	rsb	r5, r5, r3
	ldr	r3, .L1365
	add	r3, r3, r5
	ldrb	r0, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1347
.L1239:
	mov	r3, r5, asl #24
	cmp	r3, r8
	bhi	.L1243
	ldr	r4, [r6, #36]
	rsb	r8, r3, r8
	ldr	r1, .L1365
	mov	r3, #6
	rsb	r5, r5, r4
	mov	r10, #0
	add	r1, r1, r5
	mov	r2, #1
	str	r9, [fp, #-64]
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r7, r4, r7
	str	r8, [r6, #28]
	mov	r4, r5, asl r4
	str	r7, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L1244
.L1248:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1348
.L1244:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1248
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
	b	.L1248
.L1228:
	ldr	r3, .L1365
	add	r3, r3, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r7, r3, r7
	mov	r10, r10, asl r3
	str	r4, [r6, #28]
	str	r7, [r6, #32]
	str	r10, [r6, #36]
.L1298:
	ldr	r3, [fp, #-56]
	add	r9, r9, #1
	cmp	r9, r3
	bne	.L1259
	ldr	r2, [fp, #-72]
	add	r3, r9, #9
	mov	r8, r10
	str	r3, [fp, #-56]
	cmp	r3, r2
	bne	.L1226
	ldr	r3, [fp, #-68]
	add	r2, r3, #1888
	add	r3, r3, #1936
	add	r3, r3, #14
	str	r3, [fp, #-64]
	mov	r3, r10
	add	r2, r2, #14
	str	r2, [fp, #-60]
.L1260:
	ldr	r2, [fp, #-60]
	mov	r9, #0
	mov	r10, r3
	str	r2, [fp, #-56]
.L1295:
	sub	r10, r10, #1
	cmp	r7, #0
	mov	r2, r10, asl #8
	sub	r10, r2, r10, asl #2
	mov	r10, r10, lsr #8
	add	r10, r10, #1
	blt	.L1349
.L1261:
	mov	r8, r10, asl #24
	cmp	r8, r4
	bhi	.L1262
	ldr	r3, [r6, #36]
	rsb	r8, r8, r4
	rsb	r10, r10, r3
	ldr	r3, .L1365
	add	r3, r3, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1350
.L1263:
	mov	r7, r4, asl #24
	cmp	r7, r8
	bhi	.L1264
	ldr	r2, [r6, #36]
	rsb	r8, r7, r8
	ldr	r3, .L1365
	rsb	r4, r4, r2
	add	r3, r3, r4
	ldrb	r7, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1351
.L1266:
	mov	r8, r5, asl #24
	cmp	r8, r7
	bhi	.L1271
	ldr	r1, [r6, #36]
	rsb	r0, r8, r7
	ldr	r3, .L1365
	rsb	r1, r5, r1
	add	r3, r3, r1
	ldrb	r5, [r3, #24]	@ zero_extendqisi2
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
	blt	.L1352
.L1273:
	mov	r3, r7, asl #24
	cmp	r3, r5
	bhi	.L1277
	ldr	r4, [r6, #36]
	rsb	r5, r3, r5
	ldr	r1, .L1365
	mov	r3, #6
	rsb	r4, r7, r4
	mov	r10, #0
	add	r1, r1, r4
	mov	r2, #1
	str	r9, [fp, #-72]
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r5, asl r1
	rsb	r8, r1, r8
	mov	r4, r4, asl r1
	str	r7, [r6, #28]
	str	r8, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L1278
.L1282:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1353
.L1278:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r7
	add	r4, r4, #1
	bge	.L1282
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
	b	.L1282
.L1262:
	ldr	r3, .L1365
	add	r3, r3, r10
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r4, r4, asl r3
	rsb	r5, r3, r7
	mov	r10, r10, asl r3
	str	r4, [r6, #28]
	str	r5, [r6, #32]
	str	r10, [r6, #36]
.L1299:
	add	r9, r9, #1
	ldr	r3, [fp, #-56]
	cmp	r9, #3
	add	r3, r3, #1
	str	r3, [fp, #-56]
	addne	r4, r6, #28
	ldmneia	r4, {r4, r7, r10}
	bne	.L1295
.L1354:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-64]
	add	r3, r3, #3
	str	r3, [fp, #-60]
	cmp	r3, r2
	beq	.L1294
	ldr	r4, [r6, #28]
	ldr	r3, [r6, #36]
	ldr	r7, [r6, #32]
	b	.L1260
.L1349:
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
	b	.L1261
.L1264:
	ldr	r3, .L1365
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-72]
	add	r1, r3, r4
	mov	r3, #3
	mov	r7, r3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r1
	rsb	r5, r1, r5
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L1269
.L1267:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1355
.L1269:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1267
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
	b	.L1267
.L1355:
	ldr	r9, [fp, #-72]
.L1270:
	ldr	r3, [fp, #-56]
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L1365
	sub	ip, r2, #1
	add	r10, r3, r10
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	bgt	.L1287
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1288
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1288:
	add	r3, r3, #1
.L1290:
	ldr	r2, [fp, #-56]
	strb	r3, [r2]
	b	.L1299
.L1287:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1291
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1291:
	rsb	r3, r3, #255
	b	.L1290
.L1344:
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
	b	.L1227
.L1230:
	ldr	r3, .L1365
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-64]
	add	r1, r3, r4
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	rsb	r5, r1, r7
	mov	r8, r8, asl r1
	mov	r4, r4, asl r1
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	mov	r7, r3
	str	r4, [r6, #36]
	b	.L1235
.L1233:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r5, r3, r5
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1356
.L1235:
	sub	r4, r4, #1
	cmp	r5, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1233
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
	b	.L1233
.L1356:
	ldr	r9, [fp, #-64]
.L1236:
	ldrb	r2, [r9]	@ zero_extendqisi2
	ldr	r3, .L1365
	sub	ip, r2, #1
	add	r10, r3, r10
	mov	r0, ip, asl #1
	cmp	r0, #255
	ldrb	r1, [r10, #280]	@ zero_extendqisi2
	bgt	.L1253
	add	r3, r1, #1
	cmp	r3, r0
	bgt	.L1254
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, ip, r3, asr #1
	addeq	r3, ip, r3, asr #1
.L1254:
	add	r3, r3, #1
.L1256:
	add	r4, r6, #28
	strb	r3, [r9]
	ldmia	r4, {r4, r7, r10}
	b	.L1298
.L1253:
	rsb	r2, r2, #255
	add	r3, r1, #1
	cmp	r3, r2, asl #1
	bgt	.L1257
	tst	r3, #1
	addne	r3, r1, #2
	addeq	r3, r3, r3, lsr #31
	subne	r3, r2, r3, asr #1
	addeq	r3, r2, r3, asr #1
.L1257:
	rsb	r3, r3, #255
	b	.L1256
.L1271:
	ldr	r3, .L1365
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-72]
	add	r1, r3, r5
	mov	r3, #3
	mov	r8, r3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	b	.L1276
.L1274:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	add	r3, r3, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1357
.L1276:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1274
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
	b	.L1274
.L1357:
	ldr	r9, [fp, #-72]
	add	r10, r10, #16
	b	.L1270
.L1353:
	cmp	r10, #64
	ldr	r9, [fp, #-72]
	bgt	.L1358
.L1284:
	add	r10, r10, #64
	b	.L1270
.L1237:
	ldr	r3, .L1365
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-64]
	add	r1, r3, r5
	mov	r3, #3
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	mov	r7, r8, asl r1
	rsb	r4, r1, r4
	mov	r5, r5, asl r1
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	mov	r8, r3
	str	r5, [r6, #36]
	b	.L1242
.L1240:
	mov	r3, r5, asl #24
	mov	r1, r2, asl r8
	cmp	r3, r0
	sub	r8, r8, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r5, r5, ip
	cmn	r8, #1
	add	r3, r3, r5
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r4, r3, r4
	mov	r5, r5, asl r3
	str	r7, [r6, #28]
	str	r4, [r6, #32]
	str	r5, [r6, #36]
	beq	.L1359
.L1242:
	sub	r5, r5, #1
	cmp	r4, #0
	ubfx	r5, r5, #1, #24
	mov	r0, r7
	add	r5, r5, #1
	bge	.L1240
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
	b	.L1240
.L1359:
	ldr	r9, [fp, #-64]
	add	r10, r10, #16
	b	.L1236
.L1348:
	cmp	r10, #64
	ldr	r9, [fp, #-64]
	bgt	.L1360
.L1250:
	add	r10, r10, #64
	b	.L1236
.L1277:
	ldr	r3, .L1365
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-72]
	add	r1, r3, r7
	mov	r3, #4
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r7, r7, asl r4
	mov	r5, r5, asl r4
	rsb	r8, r4, r8
	str	r7, [r6, #36]
	mov	r4, r7
	str	r5, [r6, #28]
	str	r8, [r6, #32]
	mov	r7, r3
	b	.L1281
.L1279:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r7
	cmp	r3, r0
	sub	r7, r7, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r7, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r5, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r5, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1361
.L1281:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r5
	add	r4, r4, #1
	bge	.L1279
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
	b	.L1279
.L1361:
	ldr	r9, [fp, #-72]
	add	r10, r10, #32
	b	.L1270
.L1350:
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
	b	.L1263
.L1224:
	ldr	r2, .L1365
	add	r2, r2, r4
	ldrb	r2, [r2, #24]	@ zero_extendqisi2
	mov	r3, r3, asl r2
	rsb	r5, r2, r5
	mov	r4, r4, asl r2
	str	r3, [r6, #28]
	str	r5, [r6, #32]
	str	r4, [r6, #36]
	b	.L1297
.L1243:
	ldr	r3, .L1365
	mov	r10, #0
	mov	r2, #1
	str	r9, [fp, #-64]
	add	r1, r3, r5
	mov	r3, #4
	ldrb	r4, [r1, #24]	@ zero_extendqisi2
	mov	r8, r8, asl r4
	rsb	r7, r4, r7
	str	r8, [r6, #28]
	mov	r4, r5, asl r4
	str	r7, [r6, #32]
	mov	r5, r3
	str	r4, [r6, #36]
	b	.L1247
.L1245:
	mov	r3, r4, asl #24
	mov	r1, r2, asl r5
	cmp	r3, r0
	sub	r5, r5, #1
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	ip, [r6, #36]
	movhi	r1, #0
	orr	r10, r10, r1
	rsbls	r4, r4, ip
	cmn	r5, #1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
	beq	.L1362
.L1247:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r0, r8
	add	r4, r4, #1
	bge	.L1245
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
	b	.L1245
.L1362:
	ldr	r9, [fp, #-64]
	add	r10, r10, #32
	b	.L1236
.L1345:
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
	b	.L1229
.L1358:
	sub	r4, r4, #1
	cmp	r8, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r10, r10, #65
	movge	r0, r7
	blt	.L1363
.L1285:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	r1, [r6, #36]
	movls	r2, #1
	movhi	r2, #0
	add	r10, r10, r2
	rsbls	r4, r4, r1
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r7, r0, asl r3
	rsb	r8, r3, r8
	mov	r4, r4, asl r3
	str	r7, [r6, #28]
	str	r8, [r6, #32]
	str	r4, [r6, #36]
	b	.L1284
.L1351:
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
	b	.L1266
.L1294:
	ldr	r1, [fp, #-76]
	mov	r0, r6
	ldr	r2, [fp, #12]
	bl	Vp9_ReadMvProbs
	b	.L1220
.L1360:
	sub	r4, r4, #1
	cmp	r7, #0
	ubfx	r4, r4, #1, #24
	mov	r10, r10, asl #1
	add	r4, r4, #1
	sub	r5, r10, #65
	movge	r0, r8
	blt	.L1364
.L1251:
	mov	r3, r4, asl #24
	cmp	r3, r0
	rsbls	r0, r3, r0
	ldr	r3, .L1365
	ldrls	r2, [r6, #36]
	movls	r10, #1
	movhi	r10, #0
	add	r10, r5, r10
	rsbls	r4, r4, r2
	add	r3, r3, r4
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	mov	r8, r0, asl r3
	rsb	r7, r3, r7
	mov	r4, r4, asl r3
	str	r8, [r6, #28]
	str	r7, [r6, #32]
	str	r4, [r6, #36]
	b	.L1250
.L1346:
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
	b	.L1232
.L1352:
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
	b	.L1273
.L1222:
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
	b	.L1223
.L1366:
	.align	2
.L1365:
	.word	.LANCHOR0
.L1347:
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
	b	.L1239
.L1363:
	rsb	r1, r8, #24
	rsb	r5, r8, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r5, r1, r5
	add	r8, r1, r8
	bl	BsGet
	and	r5, r5, #7
	orr	r0, r7, r0, asl r5
	b	.L1285
.L1343:
	mov	r1, r6
	ldr	r0, [fp, #-68]
	bl	Vp9_ReadSwitchableInterpProbs
	b	.L1221
.L1364:
	rsb	r1, r7, #24
	rsb	r10, r7, #16
	bic	r1, r1, #7
	mov	r0, r6
	rsb	r10, r1, r10
	add	r7, r1, r7
	bl	BsGet
	and	r10, r10, #7
	orr	r0, r8, r0, asl r10
	b	.L1251
	UNWIND(.fnend)
	.size	Vp9_PrepareReadModeInfo, .-Vp9_PrepareReadModeInfo
	.global	__aeabi_idiv
	.align	2
	.global	Vp9_AdaptCoefProbs
	.type	Vp9_AdaptCoefProbs, %function
Vp9_AdaptCoefProbs:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 80
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
	mov	lr, #432
	mul	lr, lr, r3
	mov	ip, r3, asl #9
	add	ip, ip, r3, lsl #6
	ldr	r9, [fp, #4]
	mov	r4, r3, asl #11
	add	ip, ip, #9216
	add	r0, r0, lr
	add	r1, r1, lr
	add	r3, r4, r3, lsl #8
	add	ip, ip, #8
	add	lr, r0, #432
	add	r1, r1, #2
	add	r3, r2, r3
	str	r1, [fp, #-108]
	str	r3, [fp, #-112]
	add	r1, r2, ip
	add	r3, lr, #2
	str	r1, [fp, #-104]
	str	r3, [fp, #-120]
	add	r3, r0, #2
	str	r3, [fp, #-88]
.L1368:
	ldr	r3, [fp, #-88]
	add	r3, r3, #216
	str	r3, [fp, #-116]
	ldr	r3, [fp, #-104]
	str	r3, [fp, #-92]
	ldr	r3, [fp, #-112]
	str	r3, [fp, #-96]
	ldr	r3, [fp, #-108]
	str	r3, [fp, #-100]
.L1379:
	ldr	r3, [fp, #-92]
	str	r3, [fp, #-84]
	ldr	r3, [fp, #-96]
	str	r3, [fp, #-80]
	ldr	r3, [fp, #-100]
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-88]
	str	r3, [fp, #-72]
	mov	r3, #0
	str	r3, [fp, #-64]
.L1377:
	ldr	r3, [fp, #-84]
	ldr	r8, [fp, #-72]
	ldr	r7, [fp, #-80]
	str	r3, [fp, #-56]
	mov	r3, #0
	ldr	r10, [fp, #-76]
	str	r3, [fp, #-52]
	str	r8, [fp, #-48]
	b	.L1375
.L1373:
	ldr	r2, [fp, #-56]
	ldr	r4, [r7, #8]
	ldr	r6, [r7]
	ldr	r3, [r2, #4]!
	ldrb	r8, [r10, #-2]	@ zero_extendqisi2
	subs	r1, r3, #0
	str	r2, [fp, #-56]
	ldr	r2, [r7, #4]
	moveq	r5, #128
	add	r4, r2, r4
	str	r2, [fp, #-60]
	ldr	r2, [r7, #12]
	beq	.L1369
	mov	r0, r1, asr #1
	str	r3, [fp, #-68]
	add	r0, r0, r2, lsl #8
	bl	__aeabi_idiv
	ldr	r3, [fp, #-68]
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r5, r0
.L1369:
	cmp	r9, r3
	mov	r1, r9
	movcs	r0, r3
	ldr	r3, [fp, #8]
	movcc	r0, r9
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	adds	r3, r4, r6
	moveq	r6, #128
	rsb	r2, r0, #256
	mul	r8, r2, r8
	ldr	r2, [fp, #-48]
	add	r8, r8, #128
	mla	r8, r0, r5, r8
	mov	r8, r8, lsr #8
	strb	r8, [r2, #-2]
	ldrb	r5, [r10, #-1]	@ zero_extendqisi2
	beq	.L1370
	mov	r0, r3, asr #1
	mov	r1, r3
	add	r0, r0, r6, lsl #8
	str	r3, [fp, #-68]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-68]
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r6, r0
.L1370:
	cmp	r3, r9
	mov	r1, r9
	movcc	r0, r3
	ldr	r3, [fp, #8]
	movcs	r0, r9
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	cmp	r4, #0
	rsb	r3, r0, #256
	mul	r5, r5, r3
	ldr	r3, [fp, #-48]
	add	r5, r5, #128
	mla	r6, r0, r6, r5
	mov	r6, r6, lsr #8
	strb	r6, [r3, #-1]
	moveq	r6, #128
	ldrb	r5, [r10]	@ zero_extendqisi2
	beq	.L1371
	ldr	r3, [fp, #-60]
	mov	r0, r4, asr #1
	mov	r1, r4
	add	r0, r0, r3, lsl #8
	bl	__aeabi_idiv
	cmp	r0, #1
	movlt	r0, #1
	cmp	r0, #255
	movge	r0, #255
	uxtb	r6, r0
.L1371:
	ldr	r3, [fp, #-52]
	cmp	r4, r9
	mov	r1, r9
	add	r10, r10, #3
	add	r3, r3, #1
	str	r3, [fp, #-52]
	ldr	r3, [fp, #8]
	movcc	r0, r4
	movcs	r0, r9
	add	r7, r7, #16
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	rsb	r3, r0, #256
	mul	r5, r5, r3
	ldr	r3, [fp, #-48]
	add	r5, r5, #128
	mla	r6, r0, r6, r5
	ubfx	r6, r6, #8, #8
	strb	r6, [r3], #3
	str	r3, [fp, #-48]
.L1375:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-52]
	cmp	r3, #0
	moveq	r3, #3
	movne	r3, #6
	cmp	r2, r3
	blt	.L1373
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-72]
	add	r3, r3, #1
	str	r3, [fp, #-64]
	cmp	r3, #6
	ldr	r3, [fp, #-76]
	add	r2, r2, #18
	str	r2, [fp, #-72]
	add	r3, r3, #18
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-80]
	add	r3, r3, #96
	str	r3, [fp, #-80]
	ldr	r3, [fp, #-84]
	add	r3, r3, #24
	str	r3, [fp, #-84]
	bne	.L1377
	ldr	r2, [fp, #-100]
	ldr	r3, [fp, #-88]
	add	r2, r2, #108
	str	r2, [fp, #-100]
	ldr	r2, [fp, #-116]
	add	r3, r3, #108
	str	r3, [fp, #-88]
	cmp	r3, r2
	ldr	r3, [fp, #-96]
	add	r3, r3, #576
	str	r3, [fp, #-96]
	ldr	r3, [fp, #-92]
	add	r3, r3, #144
	str	r3, [fp, #-92]
	bne	.L1379
	ldr	r3, [fp, #-88]
	ldr	r2, [fp, #-120]
	cmp	r3, r2
	ldr	r3, [fp, #-108]
	add	r3, r3, #216
	str	r3, [fp, #-108]
	ldr	r3, [fp, #-112]
	add	r3, r3, #1152
	str	r3, [fp, #-112]
	ldr	r3, [fp, #-104]
	add	r3, r3, #288
	str	r3, [fp, #-104]
	bne	.L1368
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_AdaptCoefProbs, .-Vp9_AdaptCoefProbs
	.align	2
	.global	Vp9_AdaptResidualProbs
	.type	Vp9_AdaptResidualProbs, %function
Vp9_AdaptResidualProbs:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 0
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
	ldr	r5, [fp, #12]
	mov	r7, r0
	ldr	r0, [fp, #8]
	clz	r3, r5
	ldr	r5, [fp, #4]
	adds	r0, r0, #0
	mov	r6, r1
	mov	r3, r3, lsr #5
	mov	r8, r2
	movne	r0, #1
	cmp	r5, #0
	orreq	r0, r0, #1
	cmp	r3, r0
	mov	r4, #0
	mov	r9, #24
	movhi	r5, #128
	movls	r5, #112
.L1386:
	mov	r3, r4
	str	r5, [sp, #4]
	str	r9, [sp]
	add	r4, r4, #1
	mov	r2, r8
	mov	r1, r6
	mov	r0, r7
	bl	Vp9_AdaptCoefProbs
	cmp	r4, #4
	bne	.L1386
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_AdaptResidualProbs, .-Vp9_AdaptResidualProbs
	.align	2
	.global	Vp9_AdaptProbs
	.type	Vp9_AdaptProbs, %function
Vp9_AdaptProbs:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r4, r0
	ldrsb	r0, [r1, r0]
	mov	r5, r1
	mov	r7, r2
	mov	r8, r3
	cmp	r0, #0
	ldr	r6, [fp, #4]
	ble	.L1394
	str	r6, [sp]
	bl	Vp9_AdaptProbs
	add	r3, r5, r4
	mov	r9, r0
	ldrsb	r0, [r3, #1]
	cmp	r0, #0
	ble	.L1395
.L1392:
	mov	r1, r5
	str	r6, [sp]
	mov	r3, r8
	mov	r2, r7
	bl	Vp9_AdaptProbs
	mov	r5, r0
.L1393:
	ldrb	r0, [r8, r4, lsr #1]	@ zero_extendqisi2
	sub	r1, fp, #44
	str	r9, [fp, #-44]
	str	r5, [fp, #-40]
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r7, r4, lsr #1]
	add	r0, r5, r9
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1394:
	mov	r0, r0, asl #2
	add	r3, r5, r4
	rsb	r0, r0, #0
	ldr	r9, [r6, r0]
	ldrsb	r0, [r3, #1]
	cmp	r0, #0
	bgt	.L1392
.L1395:
	mov	r0, r0, asl #2
	rsb	r0, r0, #0
	ldr	r5, [r6, r0]
	b	.L1393
	UNWIND(.fnend)
	.size	Vp9_AdaptProbs, .-Vp9_AdaptProbs
	.align	2
	.global	Vp9_AdaptModeProbs
	.type	Vp9_AdaptModeProbs, %function
Vp9_AdaptModeProbs:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 80
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
	add	r5, r0, #1968
	add	r6, r1, #1968
	add	r4, r2, #8192
	add	r6, r6, #10
	add	r5, r5, #10
	mov	r8, r0
	mov	r9, r1
	mov	r10, r3
	mov	r7, #0
.L1397:
	ldr	r1, [r4, #3348]
	ldrb	r0, [r6, #1]!	@ zero_extendqisi2
	add	r1, r1, r7
	add	r7, r7, #8
	bl	Vp9_ModeMvMergeProbs
	cmp	r7, #32
	strb	r0, [r5, #1]!
	bne	.L1397
	add	r7, r9, #1968
	add	r6, r8, #1968
	add	r7, r7, #14
	add	r6, r6, #14
	mov	r5, #0
.L1398:
	ldr	r1, [r4, #3352]
	ldrb	r0, [r7, #1]!	@ zero_extendqisi2
	add	r1, r1, r5
	add	r5, r5, #8
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #40
	strb	r0, [r6, #1]!
	bne	.L1398
	add	r7, r9, #1984
	add	r6, r8, #1984
	add	r7, r7, #13
	add	r6, r6, #13
	mov	r5, #0
.L1399:
	ldr	r1, [r4, #3360]
	ldrb	r0, [r7, #1]!	@ zero_extendqisi2
	add	r1, r1, r5
	add	r5, r5, #8
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #40
	strb	r0, [r6, #1]!
	bne	.L1399
	mov	r7, r8
	mov	r6, r9
	mov	r5, #8
	str	r9, [fp, #-100]
	str	r8, [fp, #-96]
.L1400:
	ldr	r1, [r4, #3356]
	sub	r3, r5, #8
	ldrb	r0, [r6, #1988]	@ zero_extendqisi2
	add	r7, r7, #2
	add	r1, r1, r3
	add	r6, r6, #2
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r7, #1986]
	ldr	r1, [r4, #3356]
	ldrb	r0, [r6, #1987]	@ zero_extendqisi2
	add	r1, r1, r5
	add	r5, r5, #16
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #88
	strb	r0, [r7, #1987]
	bne	.L1400
	add	r7, r8, #1952
	add	r6, r9, #1952
	add	r7, r7, #6
	add	r6, r6, #6
	mov	r5, #0
.L1401:
	ldr	r0, [r4, #3344]
	mov	r3, r6
	mov	r2, r7
	ldr	r1, .L1438
	add	r0, r0, r5
	add	r5, r5, #16
	str	r0, [sp]
	mov	r0, #0
	bl	Vp9_AdaptProbs
	cmp	r5, #112
	add	r6, r6, #3
	add	r7, r7, #3
	bne	.L1401
	add	r7, r8, #1728
	add	r6, r9, #1728
	mov	r5, #0
.L1402:
	ldr	r0, [r4, #1024]
	mov	r3, r6
	mov	r2, r7
	ldr	r1, .L1438+4
	add	r0, r0, r5
	add	r5, r5, #40
	str	r0, [sp]
	mov	r0, #0
	bl	Vp9_AdaptProbs
	cmp	r5, #160
	add	r6, r6, #9
	add	r7, r7, #9
	bne	.L1402
	add	r7, r8, #1760
	add	r6, r9, #1760
	add	r7, r7, #4
	add	r6, r6, #4
	mov	r5, #0
.L1403:
	ldr	r0, [r4, #1028]
	mov	r3, r6
	mov	r2, r7
	ldr	r1, .L1438+4
	add	r0, r0, r5
	add	r5, r5, #40
	str	r0, [sp]
	mov	r0, #0
	bl	Vp9_AdaptProbs
	cmp	r5, #400
	add	r6, r6, #9
	add	r7, r7, #9
	bne	.L1403
	add	r7, r8, #1888
	add	r6, r9, #1888
	add	r7, r7, #14
	add	r6, r6, #14
	mov	r5, #0
.L1404:
	ldr	r0, [r4, #1032]
	mov	r3, r6
	mov	r2, r7
	ldr	r1, .L1438+8
	add	r0, r0, r5
	add	r5, r5, #16
	str	r0, [sp]
	mov	r0, #0
	bl	Vp9_AdaptProbs
	cmp	r5, #256
	add	r6, r6, #3
	add	r7, r7, #3
	bne	.L1404
	cmp	r10, #4
	beq	.L1436
	ldr	r3, [fp, #4]
	cmp	r3, #4
	beq	.L1437
.L1414:
	add	r9, r9, #2000
	add	r8, r8, #2000
	add	r9, r9, #14
	add	r8, r8, #14
	mov	r5, #0
.L1411:
	ldr	r1, [r4, #3376]
	ldrb	r0, [r9, #1]!	@ zero_extendqisi2
	add	r1, r1, r5
	add	r5, r5, #8
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #24
	strb	r0, [r8, #1]!
	bne	.L1411
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1436:
	add	r7, r8, #1936
	add	r6, r9, #1936
	add	r7, r7, #14
	add	r6, r6, #14
	mov	r5, #0
.L1406:
	ldr	r0, [r4, #3340]
	mov	r3, r6
	mov	r2, r7
	ldr	r1, .L1438+12
	add	r0, r0, r5
	add	r5, r5, #12
	str	r0, [sp]
	mov	r0, #0
	bl	Vp9_AdaptProbs
	cmp	r5, #48
	add	r6, r6, #2
	add	r7, r7, #2
	bne	.L1406
	ldr	r3, [fp, #4]
	cmp	r3, #4
	bne	.L1414
.L1437:
	mov	r6, #0
	add	r3, r9, #2000
	add	r2, r8, #2000
	str	r8, [fp, #-120]
	str	r9, [fp, #-124]
	mov	r9, r6
	ldr	r8, [fp, #-96]
	mov	r1, r3
	ldr	r6, [fp, #-100]
	add	r3, r3, #12
	str	r3, [fp, #-116]
	add	r3, r2, #12
	str	r3, [fp, #-112]
	add	r3, r1, #2
	str	r3, [fp, #-108]
	add	r3, r2, #2
	str	r3, [fp, #-104]
.L1410:
	ldr	r3, [r4, #3372]
	sub	r1, fp, #92
	ldr	r2, [fp, #-116]
	mov	r5, r9, asl #4
	ldr	r10, [fp, #-104]
	ldr	ip, [r3, r9, asl #3]
	add	r3, r3, r9, lsl #3
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	ldr	r7, [fp, #-108]
	str	ip, [fp, #-92]
	ldr	r3, [r3, #4]
	str	r2, [fp, #-116]
	str	r3, [fp, #-88]
	bl	Vp9_ModeMvMergeProbs
	ldr	r3, [fp, #-112]
	sub	ip, r5, r9, asl #2
	sub	r1, fp, #84
	str	r5, [fp, #-96]
	mov	r5, #0
	strb	r0, [r3, #1]!
	ldr	r0, [r4, #3368]
	str	r3, [fp, #-112]
	ldr	lr, [r0, ip]
	add	r0, r0, ip
	str	lr, [fp, #-84]
	ldmib	r0, {ip, lr}
	add	ip, ip, lr
	str	ip, [fp, #-80]
	ldr	ip, [r0, #4]
	str	ip, [fp, #-76]
	ldr	ip, [r0, #8]
	ldrb	r0, [r6, #2009]	@ zero_extendqisi2
	str	ip, [fp, #-72]
	bl	Vp9_ModeMvMergeProbs
	sub	r1, fp, #76
	strb	r0, [r8, #2009]
	ldrb	r0, [r6, #2010]	@ zero_extendqisi2
	bl	Vp9_ModeMvMergeProbs
	ldr	r3, [fp, #-96]
	strb	r0, [r8, #2010]
	ldr	r1, [r4, #3364]
	add	r3, r1, r3
	ldr	r1, [r1, r9, asl #4]
	str	r1, [fp, #-68]
	ldmib	r3, {r0, r1}
	add	r1, r1, r0
	ldr	r0, [r3, #12]
	add	r1, r1, r0
	str	r1, [fp, #-64]
	ldr	r1, [r3, #4]
	str	r1, [fp, #-60]
	ldr	r1, [r3, #8]
	add	r1, r1, r0
	str	r1, [fp, #-56]
	ldr	r1, [r3, #8]
	str	r1, [fp, #-52]
	ldr	r3, [r3, #12]
	str	r3, [fp, #-48]
.L1409:
	sub	r3, fp, #68
	ldrb	r0, [r7, #1]!	@ zero_extendqisi2
	add	r1, r3, r5
	add	r5, r5, #8
	bl	Vp9_ModeMvMergeProbs
	cmp	r5, #24
	strb	r0, [r10, #1]!
	bne	.L1409
	ldr	r3, [fp, #-108]
	add	r9, r9, #1
	cmp	r9, #2
	add	r6, r6, #2
	add	r3, r3, #3
	str	r3, [fp, #-108]
	ldr	r3, [fp, #-104]
	add	r8, r8, #2
	add	r3, r3, #3
	str	r3, [fp, #-104]
	bne	.L1410
	ldr	r8, [fp, #-120]
	ldr	r9, [fp, #-124]
	b	.L1414
.L1439:
	.align	2
.L1438:
	.word	.LANCHOR0+536
	.word	.LANCHOR0+544
	.word	.LANCHOR0+564
	.word	.LANCHOR0+572
	UNWIND(.fnend)
	.size	Vp9_AdaptModeProbs, .-Vp9_AdaptModeProbs
	.align	2
	.global	Vp9_AdaptMvProbs
	.type	Vp9_AdaptMvProbs, %function
Vp9_AdaptMvProbs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	mov	r8, r0
	mov	r9, r1
	mov	r4, r2
	str	r2, [fp, #-100]
	sub	r0, fp, #88
	mov	r2, #6
	ldr	r1, .L1449
	str	r3, [fp, #-104]
	bl	memcpy
	mov	r2, #20
	ldr	r1, .L1449+4
	sub	r0, fp, #64
	bl	memcpy
	mov	r2, #6
	ldr	r1, .L1449
	sub	r0, fp, #80
	bl	memcpy
	add	r1, r4, #8192
	add	r3, r9, #2016
	add	r2, r8, #2016
	ldr	ip, [r1, #3380]
	add	r3, r3, #2
	sub	r1, fp, #88
	add	r2, r2, #2
	mov	r0, #0
	str	ip, [sp]
	bl	Vp9_AdaptProbs
	mov	r3, #0
	str	r3, [fp, #-96]
.L1443:
	ldr	r2, [fp, #-96]
	mov	r4, #0
	ldr	r3, [fp, #-100]
	mov	r6, r9
	ldrb	r0, [r9, #2021]	@ zero_extendqisi2
	mov	r5, r8
	add	r10, r3, r2, lsl #5
	add	r3, r10, #11520
	add	r7, r10, #11584
	add	r7, r7, #4
	ldr	r1, [r3, #56]
	bl	Vp9_ModeMvMergeProbs
	add	ip, r10, #11520
	add	ip, ip, #60
	add	r3, r9, #2016
	add	r2, r8, #2016
	add	r3, r3, #6
	add	r2, r2, #6
	sub	r1, fp, #64
	strb	r0, [r8, #2021]
	mov	r0, r4
	ldr	ip, [ip]
	str	ip, [sp]
	bl	Vp9_AdaptProbs
	add	r3, r10, #11584
	ldrb	r0, [r6, #2032]!	@ zero_extendqisi2
	sub	r1, fp, #72
	ldr	r3, [r3]
	ldmia	r3, {r2, r3}
	str	r2, [fp, #-72]
	str	r3, [fp, #-68]
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r5, #2032]!
.L1441:
	ldr	r1, [r7]
	ldrb	r0, [r6, #1]!	@ zero_extendqisi2
	add	r1, r1, r4
	add	r4, r4, #8
	bl	Vp9_ModeMvMergeProbs
	cmp	r4, #80
	strb	r0, [r5, #1]!
	bne	.L1441
	add	r4, r10, #11584
	add	r3, r9, #2032
	add	r2, r8, #2032
	add	r3, r3, #11
	ldr	ip, [r4, #8]
	add	r2, r2, #11
	sub	r1, fp, #80
	mov	r0, #0
	str	ip, [sp]
	bl	Vp9_AdaptProbs
	ldr	r1, [r4, #8]
	add	r3, r9, #2032
	add	r2, r8, #2032
	add	r1, r1, #16
	add	r3, r3, #14
	str	r1, [sp]
	add	r2, r2, #14
	sub	r1, fp, #80
	mov	r0, #0
	bl	Vp9_AdaptProbs
	add	r1, r10, #11584
	add	r3, r9, #2048
	add	r2, r8, #2048
	ldr	ip, [r1, #12]
	add	r3, r3, #1
	add	r2, r2, #1
	sub	r1, fp, #80
	mov	r0, #0
	str	ip, [sp]
	bl	Vp9_AdaptProbs
	ldr	r3, [fp, #-104]
	cmp	r3, #0
	beq	.L1442
	add	r3, r10, #11584
	ldrb	r0, [r9, #2052]	@ zero_extendqisi2
	add	r10, r10, #11584
	ldr	r1, [r3, #16]
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r8, #2052]
	ldr	r1, [r10, #20]
	ldrb	r0, [r9, #2053]	@ zero_extendqisi2
	bl	Vp9_ModeMvMergeProbs
	strb	r0, [r8, #2053]
.L1442:
	ldr	r3, [fp, #-96]
	add	r9, r9, #33
	add	r8, r8, #33
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, #2
	bne	.L1443
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1450:
	.align	2
.L1449:
	.word	.LANCHOR0+576
	.word	.LANCHOR0+584
	UNWIND(.fnend)
	.size	Vp9_AdaptMvProbs, .-Vp9_AdaptMvProbs
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
	ldr	r7, .L1454
	movw	r6, #10820
	movt	r6, 4
	add	r6, r0, r6
	mov	r5, r0
	mov	r1, #0
	movw	r2, #2868
	ldr	r3, [r7, #48]
	mov	r0, r6
	add	r4, r5, #270336
	blx	r3
	add	r3, r5, #274432
	movw	r0, #13688
	mov	r2, #3
	movt	r0, 4
	str	r2, [r3, #980]
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
.L1455:
	.align	2
.L1454:
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
	ldr	r1, .L1472
	bl	dprint_vfmw
	cmp	r6, #0
	cmpne	r4, #0
	moveq	r7, #1
	movne	r7, #0
	beq	.L1470
	ldr	r3, [r6, #624]
	add	r5, r4, #294912
	add	r8, r4, #274432
	ldr	r9, .L1472+4
	cmp	r3, #1
	mov	r1, #0
	addeq	r3, r4, #270336
	ldr	r10, [r8, #1744]
	ldreq	r2, [r5, #3380]
	mov	r0, r4
	ldreq	r7, [r3, #2568]
	ldr	r3, [r9, #48]
	streq	r2, [fp, #-48]
	movw	r2, #36296
	movt	r2, 4
	strne	r7, [fp, #-48]
	blx	r3
	movw	r0, #13688
	str	r10, [r8, #1744]
	movt	r0, 4
	add	r0, r4, r0
	bl	ResetVoQueue
	str	r6, [r4]
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r5, #3516]
	beq	.L1471
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
	movw	r0, #36196
	str	r10, [r5, #3392]
	movt	r0, 4
	str	r10, [r5, #3396]
	add	r0, r4, r0
	str	r10, [r5, #3420]
	str	r10, [r5, #3424]
	str	r10, [r5, #3460]
	str	r10, [r5, #3464]
	ldr	r3, [r6, #624]
	cmp	r3, #1
	strne	r10, [r5, #3380]
	strne	r10, [r8, #2568]
	ldreq	r3, [fp, #-48]
	streq	r3, [r5, #3380]
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
.L1463:
	str	r0, [r3, #4]!
	cmp	r3, ip
	str	r0, [r1, #4]!
	bne	.L1463
	movw	r3, #11012
	movw	r1, #11048
	movt	r3, 4
	movt	r1, 4
	add	r3, r4, r3
	add	r1, r4, r1
	mvn	r0, #0
.L1464:
	str	r0, [r3, #4]!
	cmp	r3, r1
	bne	.L1464
	movw	r1, #10968
	mov	r3, #0
	movt	r1, 4
	add	r1, r4, r1
	mov	r0, #1
.L1465:
	str	r3, [r1, #4]!
	add	r3, r3, #1
	cmp	r3, #8
	str	r0, [r2, #4]!
	bne	.L1465
	mov	r0, #0
.L1458:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1470:
	movw	r2, #2013
	ldr	r1, .L1472+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L1458
.L1471:
	ldr	r1, .L1472+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L1458
.L1473:
	.align	2
.L1472:
	.word	.LC3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC5
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
	ble	.L1486
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
	beq	.L1477
	sub	r9, r2, #4
.L1478:
	cmp	r7, #0
	beq	.L1481
	mov	r2, #0
	sub	r1, r4, #1
	add	lr, r4, r8
	mov	r0, r2
.L1479:
	ldrb	ip, [r1, #1]!	@ zero_extendqisi2
	cmp	r1, lr
	orr	r0, r0, ip, asl r2
	add	r2, r2, #8
	bne	.L1479
	add	r4, r4, r7
.L1480:
	add	r5, r5, #1
	str	r0, [r9, #4]!
	cmp	r6, r5
	bhi	.L1478
.L1477:
	str	r6, [r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1486:
	ldr	r1, .L1487
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1481:
	mov	r0, r7
	b	.L1480
.L1488:
	.align	2
.L1487:
	.word	.LC6
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
	add	r5, r0, #294912
	add	r6, r0, #270336
	mov	r4, r0
	ldr	r3, [r7, #1000]
	ldr	r0, [r5, #3516]
	cmp	r3, #1
	moveq	r1, #0
	movne	r1, #1
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r6, #2612]
	blt	.L1508
	mov	r1, r0
	ldr	r0, [r5, #3516]
	bl	FSP_GetLogicFs
	subs	r4, r0, #0
	beq	.L1509
	ldr	r2, [r6, #2612]
	mov	r0, #18
	ldr	r1, .L1512
	bl	dprint_vfmw
	ldr	r2, [r4, #28]
	cmp	r2, #0
	beq	.L1495
	ldr	r3, [r4, #32]
	cmp	r3, #0
	beq	.L1495
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L1512+4
	bl	dprint_vfmw
	ldr	r3, [r7, #1000]
	cmp	r3, #1
	beq	.L1510
	ldr	r2, [r4, #28]
	mov	r3, #0
	mov	r0, r3
	str	r3, [r2, #80]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1495:
	mov	r2, #2240
	ldr	r1, .L1512+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1508:
	ldr	r1, .L1512+12
	mov	r0, #0
	bl	dprint_vfmw
	movw	r1, #13688
	ldr	r0, [r5, #3516]
	movt	r1, 4
	add	r1, r4, r1
	bl	FSP_ClearNotInVoQueue
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1509:
	movw	r2, #2228
	ldr	r1, .L1512+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1510:
	ldr	r3, [r7, #1004]
	cmp	r3, #8
	bls	.L1498
	ldr	r2, .L1512+20
	mov	r0, #0
	ldr	r1, .L1512+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1498:
	add	r6, r6, r3, lsl #2
	ldr	r0, [r5, #3516]
	ldr	r1, [r6, #2824]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1511
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
.L1511:
	ldr	r3, .L1512+28
	movw	r2, #2257
	ldr	r1, .L1512+32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1513:
	.align	2
.L1512:
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC7
	.word	.LC8
	.word	.LANCHOR0+604
	.word	.LC12
	.word	.LC13
	.word	.LC14
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
	add	r4, r0, #294912
	ldr	r1, [r5, #2612]
	cmp	r1, #0
	blt	.L1515
	mov	r2, #1
	ldr	r0, [r4, #3516]
	bl	FSP_ClearLogicFs
.L1515:
	ldr	r3, [r4, #3416]
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
	beq	.L1519
	add	r3, r6, #294912
	add	r5, r6, #270336
	ldr	r0, [r3, #3516]
	ldr	r1, [r5, #2612]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1519
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
	beq	.L1523
	add	r7, r4, #512
	ldr	lr, [r4, #36]
	ldrd	r2, [r7, #-8]
	strd	r2, [fp, #-52]
.L1524:
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
.L1519:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1523:
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
	b	.L1524
	UNWIND(.fnend)
	.size	VP9_SetImgFormat, .-VP9_SetImgFormat
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
	beq	.L1531
	add	r4, r4, #294912
	mov	r2, #0
	ldr	r0, [r4, #3516]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #3516]
	bl	FSP_GetFsImagePtr
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1531:
	movw	r2, #2698
	ldr	r1, .L1532
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1533:
	.align	2
.L1532:
	.word	.LC15
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
	beq	.L1538
	movw	r0, #13688
	movt	r0, 4
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetVoLastImageID
.L1538:
	movw	r2, #2717
	ldr	r1, .L1539
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1540:
	.align	2
.L1539:
	.word	.LC16
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
	beq	.L1548
	add	r4, r5, #294912
	ldr	r0, [r4, #3516]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #3516]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L1549
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1549:
	movw	r1, #13688
	ldr	r0, [r4, #3516]
	movt	r1, 4
	add	r1, r5, r1
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1548:
	movw	r2, #2729
	ldr	r1, .L1550
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1551:
	.align	2
.L1550:
	.word	.LC16
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
	beq	.L1553
.L1554:
	ldr	r1, .L1555
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1553:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	cmp	r0, #131
	bne	.L1554
	mov	r0, r4
	mov	r1, #8
	bl	BsGet
	cmp	r0, #66
	bne	.L1554
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1556:
	.align	2
.L1555:
	.word	.LC17
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
	beq	.L1559
	add	r3, r1, #80
	mov	r0, #1
.L1560:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1559
	add	r0, r0, #1
	cmp	r0, #9
	bne	.L1560
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1559:
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
	beq	.L1568
	mov	r0, r4
	sub	r2, fp, #24
	sub	r1, fp, #28
	bl	Read_Frame_Size
.L1568:
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
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	lr, [r0, #2492]
	ldr	ip, [r0, #2496]
	ldr	r3, [r0, #2440]
	add	r1, lr, #7
	add	r2, ip, #7
	bic	r1, r1, #7
	bic	r2, r2, #7
	add	r3, r0, r3, lsl #4
	mov	r4, r1, asr #3
	str	r4, [r0, #2532]
	mov	r4, r2, asr #3
	str	r4, [r0, #2536]
	str	r1, [r3, #2676]
	str	r2, [r3, #2680]
	str	lr, [r3, #2684]
	str	ip, [r3, #2688]
	ldmfd	sp, {r4, fp, sp, pc}
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r1, #2492]
	mov	r4, r1
	ldr	r3, [r1, #2496]
	add	r5, r1, #2432
	add	r1, r5, #60
	add	r2, r4, #2496
	str	ip, [r4, #2512]
	mov	r6, r0
	str	r3, [r4, #2516]
	add	r5, r5, #8
	bl	Read_Frame_Size
	ldr	r7, [r4, #2492]
	ldr	lr, [r4, #2496]
	mov	r1, r5
	ldr	r3, [r4, #2440]
	add	ip, r7, #7
	add	r2, lr, #7
	bic	ip, ip, #7
	bic	r2, r2, #7
	mov	r0, r6
	add	r3, r4, r3, lsl #4
	mov	r5, ip, asr #3
	str	r5, [r4, #2532]
	mov	r5, r2, asr #3
	str	r5, [r4, #2536]
	str	ip, [r3, #2676]
	str	r2, [r3, #2680]
	str	r7, [r3, #2684]
	str	lr, [r3, #2688]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r7, r1, #2432
	mov	r4, r1
	add	r7, r7, #8
	mov	r6, r0
	mov	r5, #0
.L1578:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	bne	.L1583
	add	r5, r5, #1
	cmp	r5, #3
	bne	.L1578
	ldr	ip, [r4, #2492]
	add	r2, r4, #2496
	ldr	r3, [r4, #2496]
	add	r1, r7, #52
	mov	r0, r6
	str	ip, [r4, #2512]
	str	r3, [r4, #2516]
	bl	Read_Frame_Size
	ldr	r5, [r4, #2492]
	ldr	lr, [r4, #2496]
.L1577:
	ldr	r3, [r4, #2440]
	add	ip, r5, #7
	add	r2, lr, #7
	bic	ip, ip, #7
	bic	r2, r2, #7
	mov	r0, r6
	add	r3, r4, r3, lsl #4
	mov	r6, ip, asr #3
	mov	r1, r7
	str	r6, [r4, #2532]
	mov	r6, r2, asr #3
	str	r6, [r4, #2536]
	str	ip, [r3, #2676]
	str	r5, [r3, #2684]
	str	lr, [r3, #2688]
	str	r2, [r3, #2680]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	Setup_Display_Size
.L1583:
	add	r5, r5, #46
	ldr	r1, [r4, #2492]
	ldr	r2, [r4, #2496]
	ldr	r3, [r4, r5, asl #2]
	str	r1, [r4, #2512]
	str	r2, [r4, #2516]
	add	r3, r4, r3, lsl #4
	ldr	r5, [r3, #2684]
	str	r5, [r4, #2492]
	ldr	lr, [r3, #2688]
	str	lr, [r4, #2496]
	b	.L1577
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
	ldr	r5, .L1586
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
.L1587:
	.align	2
.L1586:
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
	ldr	r5, .L1589
	mov	r4, r0
	add	r0, r0, #2640
	mov	r2, #32
	mov	r1, #0
	add	r0, r0, #4
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r5, [r5, #48]
	mov	r3, #0
	mov	ip, #1
	mvn	lr, #0
	mov	r1, r3
	strb	r3, [r4, #2567]
	add	r0, r4, #64
	strb	r3, [r4, #339]
	mov	r2, #16
	strb	r3, [r4, #342]
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
.L1590:
	.align	2
.L1589:
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
.L1595:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1609
.L1594:
	add	r6, r6, #1
	cmp	r6, r7
	bne	.L1595
	add	r4, r4, #8
.L1597:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1610
.L1596:
	add	r7, r7, #1
	cmp	r7, r4
	bne	.L1597
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1609:
	ldr	r2, .L1611
	mov	r1, #6
	mov	r0, r5
	bl	VP9_s_v
	strb	r0, [r6]
	b	.L1594
.L1610:
	ldr	r2, .L1611+4
	mov	r1, #6
	mov	r0, r5
	bl	VP9_s_v
	strb	r0, [r7]
	b	.L1596
.L1612:
	.align	2
.L1611:
	.word	.LC18
	.word	.LC19
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
	beq	.L1614
	mov	r0, r6
	ldr	r2, .L1618
	mov	r1, #4
	bl	VP9_s_v
.L1614:
	str	r0, [r4]
	subs	r0, r0, r5
	movne	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1619:
	.align	2
.L1618:
	.word	.LC20
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
	bne	.L1621
	ldr	r2, [r4, #244]
	cmp	r2, #0
	bne	.L1621
	ldr	r2, [r4, #248]
	cmp	r2, #0
	ldreq	r3, [r4, #252]
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
.L1621:
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
	ldr	r3, .L1626
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #624]
	ldmfd	sp, {fp, sp, pc}
.L1627:
	.align	2
.L1626:
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
	bls	.L1632
	subs	r3, r0, #1
	beq	.L1633
	mov	r0, #0
.L1631:
	movs	r3, r3, lsr #1
	add	r0, r0, #1
	bne	.L1631
	ldmfd	sp, {fp, sp, pc}
.L1632:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1633:
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
	bls	.L1636
	subs	r3, r4, #1
	beq	.L1640
	mov	r1, #0
.L1638:
	movs	r3, r3, lsr #1
	add	r1, r1, #1
	bne	.L1638
.L1636:
	bl	BsGet
	cmp	r0, r4
	movge	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1640:
	mov	r1, r3
	b	.L1636
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
	ldr	r3, .L1643
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #640]
	ldmfd	sp, {fp, sp, pc}
.L1644:
	.align	2
.L1643:
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
	ldr	r7, .L1654
	mov	r10, r2, asl #2
	mov	r5, r3
	mov	r4, r2
	add	r3, r7, r10
	mov	r6, r0
	mov	r9, r1
	ldr	r8, [r3, #624]
	cmp	r8, r5
	blt	.L1651
.L1646:
	cmp	r5, #0
	blt	.L1652
.L1648:
	add	r4, r4, r9, lsl #2
	add	r4, r6, r4, lsl #1
	strh	r5, [r4, #16]	@ movhi
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1652:
	add	r7, r7, r10
	ldr	r0, [r7, #640]
	cmp	r0, #0
	beq	.L1653
.L1649:
	rsb	r3, r5, #0
	cmp	r8, r3
	bge	.L1648
	movw	r3, #3010
	ldr	r2, .L1654+4
	ldr	r1, .L1654+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1648
.L1651:
	movw	r3, #2998
	add	r2, r7, #656
	ldr	r1, .L1654+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L1646
.L1653:
	movw	r3, #3005
	ldr	r2, .L1654+4
	ldr	r1, .L1654+8
	bl	dprint_vfmw
	b	.L1649
.L1655:
	.align	2
.L1654:
	.word	.LANCHOR0
	.word	.LANCHOR0+656
	.word	.LC21
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
	ble	.L1659
.L1660:
	add	r3, r3, #1
	mov	ip, r0, asr r3
	cmp	ip, #3
	bgt	.L1660
	sub	r3, r3, #1
	bic	r3, r3, r3, asr #31
.L1659:
	cmp	r0, #64
	mov	ip, #0
	ble	.L1661
	mov	lr, #64
.L1662:
	add	ip, ip, #1
	cmp	r0, lr, asl ip
	bgt	.L1662
.L1661:
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
	ble	.L1668
	mov	r4, #0
	b	.L1669
.L1680:
	mov	r4, r3
.L1669:
	add	r3, r4, #1
	mov	r1, r2, asr r3
	cmp	r1, #3
	bgt	.L1680
	cmp	r2, #64
	bic	r4, r4, r4, asr #31
	ble	.L1691
.L1678:
	mov	r3, #0
	mov	r1, #64
.L1671:
	add	r3, r3, #1
	cmp	r2, r1, asl r3
	bgt	.L1671
.L1670:
	subs	r4, r4, r3
	str	r3, [r6, #100]
	bne	.L1674
	b	.L1673
.L1676:
	ldr	r3, [r6, #100]
	subs	r4, r4, #1
	add	r3, r3, #1
	str	r3, [r6, #100]
	beq	.L1673
.L1674:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L1676
.L1673:
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
.L1668:
	cmp	r2, #64
	movgt	r4, #0
	bgt	.L1678
	mov	r3, #0
	str	r3, [r6, #100]
	b	.L1673
.L1691:
	mov	r3, #0
	b	.L1670
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
	bne	.L1729
.L1693:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1729:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L1696
	add	r4, r5, #4
	add	r7, r5, #11
	b	.L1698
.L1697:
	strb	r3, [r4, #1]!
	cmp	r4, r7
	beq	.L1730
.L1698:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #255
	cmp	r0, #0
	beq	.L1697
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #1]!
	cmp	r4, r7
	bne	.L1698
.L1730:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #4]
	cmp	r0, #0
	addne	r4, r5, #14
	bne	.L1701
	mvn	r3, #0
	strb	r3, [r5, #12]
	strb	r3, [r5, #13]
	strb	r3, [r5, #14]
.L1696:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #2]
	cmp	r0, #0
	beq	.L1693
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	add	r8, r5, #80
	mov	r7, #0
	ldr	r10, .L1733
	strb	r0, [r5, #3]
	mov	r0, r5
	bl	VP9_Clearall_Segfeatures
.L1703:
	mov	r4, #0
	mov	r9, #1
.L1706:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	moveq	r3, r0
	bne	.L1731
.L1705:
	mov	r2, r4
	mov	r1, r7
	add	r4, r4, #1
	mov	r0, r5
	bl	VP9_Set_Segdata
	cmp	r4, #4
	bne	.L1706
	add	r7, r7, #1
	add	r8, r8, #4
	cmp	r7, #8
	bne	.L1703
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1731:
	ldr	r3, [r8]
	mov	r0, r6
	ldr	r1, [r10, r4, asl #2]
	orr	r3, r3, r9, asl r4
	str	r3, [r8]
	bl	Decode_Unsigned_Max
	ldr	r2, .L1733+4
	ldr	r2, [r2, r4, asl #2]
	cmp	r2, #0
	mov	r3, r0
	beq	.L1705
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
	b	.L1705
.L1701:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #255
	cmp	r0, #0
	bne	.L1732
.L1700:
	strb	r3, [r7, #1]!
	cmp	r7, r4
	bne	.L1701
	b	.L1696
.L1732:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	uxtb	r3, r0
	b	.L1700
.L1734:
	.align	2
.L1733:
	.word	.LANCHOR0+624
	.word	.LANCHOR0+640
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
	ldr	r3, .L1739
	mov	r4, r0
	sub	ip, fp, #20
	ldmia	r3, {r0, r1, r2, r3}
	stmdb	ip, {r0, r1, r2, r3}
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	cmp	r0, #0
	movne	r0, #4
	beq	.L1738
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1738:
	mov	r0, r4
	mov	r1, #2
	bl	BsGet
	sub	r3, fp, #20
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #-16]
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1740:
	.align	2
.L1739:
	.word	.LANCHOR0+672
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
	beq	.L1747
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
.L1746:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1747:
	str	r3, [sp]
	mov	r0, #1
	movw	r3, #3203
	ldr	r2, .L1748
	ldr	r1, .L1748+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1746
.L1749:
	.align	2
.L1748:
	.word	.LANCHOR0+688
	.word	.LC22
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
	bgt	.L1754
	cmp	r1, r3, asl #1
	bgt	.L1754
	cmp	r2, r0, asl #4
	bgt	.L1754
	cmp	r3, r1, asl #4
	movle	r0, #1
	movgt	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1754:
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
	bgt	.L1757
	cmp	r2, r6, asl #1
	ble	.L1767
.L1757:
	mvn	r2, #0
	mov	r3, #16
	str	r2, [r4]
	stmib	r4, {r2, r3}
	str	r3, [r4, #12]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1767:
	cmp	r3, r1, asl #4
	bgt	.L1757
	cmp	r6, r2, asl #4
	bgt	.L1757
	cmp	r3, #0
	beq	.L1768
	mov	r1, r3
	mov	r0, ip, asl #14
	bl	__aeabi_idiv
	cmp	r6, #0
	mov	r5, r0
	str	r5, [r4]
	beq	.L1769
.L1760:
	mov	r1, r6
	mov	r0, r7, asl #14
	bl	__aeabi_idiv
	mov	r7, r0, asr #31
	ubfx	r3, r0, #10, #18
	mov	r1, r7, asl #4
	orr	r1, r1, r0, lsr #28
	orr	r1, r3, r1, asl #18
.L1761:
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
.L1768:
	str	r3, [sp]
	mov	r0, #1
	movw	r3, #3203
	ldr	r2, .L1770
	ldr	r1, .L1770+4
	mvn	r5, #0
	bl	dprint_vfmw
	cmp	r6, #0
	str	r5, [r4]
	bne	.L1760
.L1769:
	ldr	r1, .L1770+4
	movw	r3, #3203
	str	r6, [sp]
	mov	r0, #1
	ldr	r2, .L1770
	bl	dprint_vfmw
	mvn	r1, #0
	mov	r0, r1
	ldr	r5, [r4]
	b	.L1761
.L1771:
	.align	2
.L1770:
	.word	.LANCHOR0+688
	.word	.LC22
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
	ble	.L1773
	mov	r0, r5
	mov	r1, #1
	bl	BsGet
	add	r4, r0, r4
.L1773:
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
	ldr	r3, [r1, #2452]
	mov	r2, #8
	mov	r4, r1
	mov	r5, r0
	cmp	r3, #1
	str	r2, [r1, #2508]
	bls	.L1775
	mov	r1, #1
	bl	BsGet
	cmp	r0, #0
	movne	r3, #12
	moveq	r3, #10
	str	r3, [r4, #2508]
.L1775:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	cmp	r0, #7
	str	r0, [r4, #2456]
	beq	.L1777
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldr	r6, [r4, #2452]
	bic	r6, r6, #2
	cmp	r6, #1
	movne	r3, #1
	str	r0, [r4, #2460]
	strne	r3, [r4, #2488]
	strne	r3, [r4, #2484]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #2484]
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #2488]
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
.L1777:
	ldr	r1, [r4, #2452]
	bic	r1, r1, #2
	cmp	r1, #1
	beq	.L1783
	movw	r3, #3306
	ldr	r2, .L1784
	ldr	r1, .L1784+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1783:
	mov	r3, #0
	mov	r0, r5
	str	r3, [r4, #2488]
	str	r3, [r4, #2484]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
.L1785:
	.align	2
.L1784:
	.word	.LANCHOR0+724
	.word	.LC23
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
	beq	.L1791
.L1787:
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
.L1791:
	bl	Vp9_ReadTxMode
	cmp	r0, #4
	mov	r4, r0
	bne	.L1787
	add	r0, r6, #2000
	mov	r1, r5
	add	r0, r0, #3
	bl	Vp9_ReadTxProbs
	b	.L1787
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	mov	r4, r1
	ldr	r3, [r4, #2448]
	mov	r1, #2
	mov	r5, r0
	str	r3, [r4, #2444]
	bl	BsGet
	cmp	r0, #2
	beq	.L1793
	ldr	r1, .L1827
	mov	r0, #1
	bl	dprint_vfmw
.L1793:
	mov	r0, r5
	bl	Vp9_Vfmw_ReadProfile
	mov	r1, #1
	str	r0, [r4, #2452]
	mov	r0, r5
	bl	BsGet
	subs	r6, r0, #0
	bne	.L1823
	mov	r1, #1
	str	r6, [r4, #2468]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #2448]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #2464]
	mov	r0, r5
	bl	BsGet
	ldr	r2, [r4, #2448]
	cmp	r2, #0
	mov	r3, r0
	str	r0, [r4, #2480]
	beq	.L1824
	ldr	r2, [r4, #2464]
	cmp	r2, #0
	strne	r6, [r4, #2548]
	beq	.L1825
.L1799:
	cmp	r3, #0
	beq	.L1800
	mov	r3, #0
	str	r3, [r4, #2552]
.L1801:
	ldr	r3, [r4, #2548]
	cmp	r3, #0
	beq	.L1802
	mov	r0, r5
	bl	Check_Sync_Code
	ldr	r3, [r4, #2452]
	cmp	r3, #1
	bls	.L1803
	mov	r1, r4
	mov	r0, r5
	bl	Vp9_ReadBitDepthColorSpaceSampling
.L1804:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, r4
	str	r0, [r4, #2556]
	mov	r0, r5
	bl	Setup_Frame_Size
	b	.L1797
.L1823:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r3, #0
	mov	r6, r3
	mov	r2, #1
	add	r0, r0, #38
	ldr	r1, [r4, r0, asl #2]
	str	r3, [r4, #2556]
	str	r3, [r4, #344]
	str	r1, [r4, #2472]
	str	r2, [r4, #2468]
	str	r2, [r4, #2464]
.L1795:
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1802:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	add	r8, r4, #180
	add	r9, r4, #192
	mov	r7, r8
	str	r0, [r4, #2556]
.L1805:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	add	r3, r0, #38
	mov	r0, r5
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r7, #4]!
	bl	BsGet
	cmp	r7, r9
	str	r0, [r7, #-116]
	bne	.L1805
	mov	r1, r4
	mov	r0, r5
	bl	setup_frame_size_with_refs
	ldr	r2, [r4, #2492]
	sub	r3, r2, #1
	cmp	r3, #4096
	ldr	r3, [r4, #2496]
	bcs	.L1807
	sub	r1, r3, #1
	cmp	r1, #4096
	bcs	.L1807
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	add	r7, r4, #2816
	add	r7, r7, #4
	str	r0, [r4, #56]
	mov	r0, r5
	bl	read_interp_filter_type
	str	r0, [r4, #2560]
.L1809:
	ldr	r1, [r8, #4]!
	mov	r0, r7
	ldr	ip, [r4, #2496]
	add	r7, r7, #16
	ldr	r3, [r4, #2492]
	add	r1, r4, r1, lsl #4
	add	r1, r1, #2672
	ldr	r2, [r1, #16]
	add	r1, r1, #4
	ldr	r1, [r1, #8]
	str	ip, [sp]
	bl	vp9_setup_scale_factors
	cmp	r9, r8
	bne	.L1809
	ldr	r3, [r4, #68]
	ldr	r1, [r4, #76]
	ldr	r2, [r4, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r4, #60]
	b	.L1797
.L1824:
	mov	r0, r5
	bl	Check_Sync_Code
	mov	r1, r4
	mov	r0, r5
	bl	Vp9_ReadBitDepthColorSpaceSampling
	ldr	r3, [r4, #2440]
	mov	r2, #255
	mov	r1, r4
	str	r2, [r4, #2556]
	mov	r0, r5
	str	r3, [r4, #184]
	str	r3, [r4, #188]
	str	r3, [r4, #192]
	bl	Setup_Frame_Size
.L1797:
	ldr	r3, [r4, #2480]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r4, #2520]
	strne	r3, [r4, #2524]
	beq	.L1826
.L1811:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #2448]
	cmp	r3, #0
	str	r0, [r4, #2528]
	beq	.L1812
	ldr	r3, [r4, #2480]
	cmp	r3, #0
	bne	.L1812
	ldr	r3, [r4, #2548]
	cmp	r3, #0
	bne	.L1812
.L1814:
	ldr	r3, [r4, #68]
	ldr	r1, [r4, #76]
	ldr	r2, [r4, #72]
	cmp	r2, r3
	cmpeq	r3, r1
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r4, #60]
.L1813:
	add	r1, r4, #336
	mov	r0, r5
	bl	Setup_LoopFilter
	mov	r1, r4
	mov	r0, r5
	bl	Setup_Quantization
	add	r1, r4, #2560
	mov	r0, r5
	add	r1, r1, #4
	bl	Setup_Segmentation
	add	r1, r4, #2432
	mov	r0, r5
	add	r1, r1, #8
	bl	Setup_Tile_Info
	mov	r0, r5
	mov	r1, #16
	bl	BsGet
	str	r0, [r4, #8]
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1803:
	mov	r3, #1
	mov	r2, #8
	str	r3, [r4, #2484]
	str	r2, [r4, #2508]
	str	r3, [r4, #2488]
	str	r3, [r4, #2456]
	b	.L1804
.L1812:
	mov	r0, r4
	bl	VP9_Setup_Past_Independence
	ldr	r3, [r4, #2448]
	cmp	r3, #0
	beq	.L1813
	b	.L1814
.L1826:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #2520]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #2524]
	b	.L1811
.L1800:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #2552]
	b	.L1801
.L1825:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #2480]
	str	r0, [r4, #2548]
	b	.L1799
.L1807:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	movw	r3, #3459
	ldr	r2, .L1827+4
	mvn	r6, #0
	ldr	r1, .L1827+8
	bl	dprint_vfmw
	b	.L1795
.L1828:
	.align	2
.L1827:
	.word	.LC24
	.word	.LANCHOR0+760
	.word	.LC25
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
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #2556]
	cmp	r3, #0
	addne	r2, r0, #152
	addne	lr, r0, #80
	beq	.L1834
.L1833:
	tst	r3, #1
	beq	.L1831
	ldr	r4, [r2]
	ldr	ip, [r0, #2440]
	ldr	r1, [lr, r4, asl #2]
	cmp	r1, #0
	sub	r1, r1, #1
	strgt	r1, [lr, r4, asl #2]
	str	ip, [r2]
	ldr	r1, [lr, ip, asl #2]
	add	r1, r1, #1
	str	r1, [lr, ip, asl #2]
.L1831:
	movs	r3, r3, asr #1
	add	r2, r2, #4
	bne	.L1833
.L1834:
	ldr	r3, [r0, #2440]
	mvn	r2, #-2147483648
	add	r3, r0, r3, lsl #2
	ldr	r1, [r3, #80]
	sub	r1, r1, #1
	str	r1, [r3, #80]
	str	r2, [r0, #184]
	str	r2, [r0, #188]
	str	r2, [r0, #192]
	ldmfd	sp, {r4, fp, sp, pc}
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
	ldr	r6, [r7, #1000]
	cmp	r6, #1
	beq	.L1875
	add	r8, r0, #262144
	mov	r3, #0
	strb	r3, [r8, #1036]
	ldr	r2, [r7, #980]
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
	addgt	r6, r5, #294912
	addle	r1, r4, r1, lsl #2
	addle	r6, r5, #294912
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
	ldrgt	r3, [r6, #3416]
	ldrle	r3, [r1, #2824]
	addgt	r3, r4, r3, lsl #2
	ldrgt	r3, [r3, #2824]
	str	r3, [r4, #2604]
	ldr	r3, [r4, #2816]
	cmp	r3, #8
	ldrgt	r3, [r6, #3416]
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #2824]
	str	r3, [r4, #2600]
	ldr	r3, [r4, #2812]
	cmp	r3, #8
	ldrgt	r3, [r6, #3416]
	cmp	r2, #0
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #2824]
	str	r3, [r4, #2608]
	bne	.L1876
.L1853:
	ldr	r1, [r4, #2612]
	str	r1, [r4, #2604]
	str	r1, [r4, #2600]
	str	r1, [r4, #2608]
.L1854:
	ldr	r0, [r6, #3516]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2604]
	mov	r7, r0
	ldr	r0, [r6, #3516]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2600]
	mov	r10, r0
	ldr	r0, [r6, #3516]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2608]
	mov	r9, r0
	ldr	r0, [r6, #3516]
	bl	FSP_GetLogicFs
	cmp	r9, #0
	cmpne	r7, #0
	beq	.L1855
	cmp	r0, #0
	cmpne	r10, #0
	beq	.L1855
	ldr	r3, [r7, #28]
	cmp	r3, #0
	beq	.L1877
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
	ldr	r3, [r6, #3524]
	str	r3, [r6, #3520]
	str	r3, [r8, #1032]
	str	r2, [r5, #4]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1876:
	ldr	r3, [r7, #1080]
	cmp	r3, #1
	beq	.L1853
	ldr	r1, [r4, #2612]
	b	.L1854
.L1875:
	add	r3, r0, #262144
	add	r8, r0, #294912
	strb	r6, [r3, #1036]
	ldr	r3, [r0]
	ldr	r1, [r4, #2612]
	ldr	r2, [r3, #600]
	str	r2, [r4, #2476]
	ldr	r3, [r3, #652]
	str	r3, [r4, #2496]
	ldr	r0, [r8, #3516]
	bl	FSP_GetLogicFs
	ldr	r3, [r7, #1004]
	add	r3, r4, r3, lsl #2
	ldr	r1, [r3, #2824]
	mov	r9, r0
	ldr	r0, [r8, #3516]
	bl	FSP_GetLogicFs
	ldr	r3, [r7, #1004]
	add	r3, r4, r3, lsl #2
	ldr	r1, [r3, #2824]
	mov	r10, r0
	ldr	r0, [r8, #3516]
	bl	FSP_GetFsImagePtr
	cmp	r9, #0
	cmpne	r10, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r2, r0
	cmp	r3, #0
	bne	.L1855
	ldr	r3, [r9, #28]
	cmp	r3, #0
	beq	.L1878
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
.L1855:
	ldr	r1, .L1879
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1877:
	ldr	r1, .L1879+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1878:
	mov	r0, r6
	ldr	r1, .L1879+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1880:
	.align	2
.L1879:
	.word	.LC26
	.word	.LC28
	.word	.LC27
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
	bls	.L1883
	sub	r0, r2, #32
	movw	r1, #8160
	cmp	r3, #8192
	cmpls	r0, r1
	bls	.L1884
.L1883:
	ldr	r1, .L1915
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L1885:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1884:
	ldr	r1, .L1915+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r0, [r3, #732]
	ldr	r2, [r3, #28]
	cmp	r0, #0
	bne	.L1886
	cmp	r2, #25
	beq	.L1912
.L1899:
	mov	r7, #5
.L1887:
	ldr	r3, [r4, #2568]
	add	r6, r5, #294912
	cmp	r3, #0
	bne	.L1892
	ldr	r0, [r6, #3516]
	mov	r1, r3
	ldr	r2, .L1915+8
	ldr	ip, .L1915+12
	ldr	r8, [ip, #48]
	ldr	ip, [r2, r0, asl #2]
	mov	r2, #20
	sub	r0, fp, #64
	add	ip, ip, #290816
	str	r3, [ip, #1104]
	blx	r8
	ldr	ip, [r4, #2648]
	ldr	r2, [r4, #2652]
	sub	r1, fp, #64
	ldr	r0, [r6, #3516]
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
	beq	.L1913
.L1893:
	ldr	r1, .L1915+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1885
.L1886:
	cmp	r2, #25
	bne	.L1899
	ldr	r2, [r4, #2648]
	ldr	ip, [r3, #692]
	cmp	r2, ip
	bhi	.L1911
	ldr	r0, [r4, #2652]
	ldr	r1, [r3, #696]
	cmp	r0, r1
	bls	.L1891
.L1890:
	ldr	r3, [r4, #2652]
	mov	r0, #0
	str	r1, [sp, #4]
	str	ip, [sp]
	ldr	r1, .L1915+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1885
.L1892:
	ldr	r3, [r6, #3516]
	mov	r7, #1
	ldr	r8, .L1915+8
	mov	r1, #0
	ldr	r2, .L1915+12
	sub	r0, fp, #64
	ldr	r9, [r6, #3388]
	ldr	r3, [r8, r3, asl #2]
	ldr	r10, [r2, #48]
	mov	r2, #20
	add	r3, r3, #290816
	str	r7, [r3, #1104]
	blx	r10
	ldr	r1, [r5]
	ldr	r3, [r4, #2652]
	ldr	r2, [r4, #2648]
	ldr	r1, [r1, #28]
	ldr	r0, [r6, #3516]
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
	bne	.L1893
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r6, #3516]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	bne	.L1914
.L1896:
	ldr	r3, [r6, #3516]
	mov	r2, #0
	ldr	r3, [r8, r3, asl #2]
	str	r2, [r3, #1496]
.L1894:
	mov	r3, #1
	mov	r0, #0
	str	r3, [r4, #2568]
	b	.L1885
.L1911:
	ldr	r1, [r3, #696]
	b	.L1890
.L1912:
	ldr	r2, [r4, #2648]
	ldr	ip, [r3, #692]
	cmp	r2, ip
	bhi	.L1911
	ldr	lr, [r4, #2652]
	ldr	r1, [r3, #696]
	cmp	lr, r1
	bhi	.L1890
	ldr	r2, [r4, #2568]
	cmp	r2, #1
	beq	.L1885
.L1891:
	ldr	r7, [r3, #740]
	b	.L1887
.L1913:
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r6, #3516]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #0
	beq	.L1894
	mov	r0, r7
	ldr	r1, .L1915+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1885
.L1914:
	ldr	r1, .L1915+28
	mov	r0, #2
	bl	dprint_vfmw
	b	.L1896
.L1916:
	.align	2
.L1915:
	.word	.LC29
	.word	.LC30
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	.word	.LC31
	.word	.LC32
	.word	.LC34
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
	ldr	r8, .L1936
	movw	r6, #10820
	sub	r4, fp, #72
	add	r7, r0, #274432
	movt	r6, 4
	add	r6, r0, r6
	ldr	r3, [r8, #52]
	add	r1, r6, #80
	mov	r2, #36
	mov	r0, r4
	ldr	r5, [r7, #972]
	blx	r3
	ldr	r3, [r8, #52]
	add	r1, r6, #152
	sub	r0, fp, #104
	mov	r2, #32
	blx	r3
	ldr	r3, [r7, #1000]
	cmp	r3, #1
	beq	.L1935
.L1918:
	ldr	r3, [r7, #1088]
	mov	lr, r5, asl #2
	cmp	r3, #0
	subne	r2, fp, #104
	addne	ip, r4, lr
	beq	.L1925
.L1924:
	tst	r3, #1
	beq	.L1922
	ldr	r0, [r2]
	str	r5, [r2]
	ldr	r1, [r4, r0, asl #2]
	cmp	r1, #0
	sub	r1, r1, #1
	strgt	r1, [r4, r0, asl #2]
	ldr	r1, [ip]
	add	r1, r1, #1
	str	r1, [ip]
.L1922:
	movs	r3, r3, asr #1
	add	r2, r2, #4
	bne	.L1924
.L1925:
	sub	r3, fp, #36
	sub	r1, fp, #40
	add	r2, r3, lr
	sub	r3, fp, #76
	mov	r0, #0
	ldr	ip, [r2, #-36]
	sub	ip, ip, #1
	str	ip, [r2, #-36]
.L1921:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	addne	r0, r0, #1
	cmp	r3, r1
	bne	.L1921
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1935:
	ldr	r3, [r4, r5, asl #2]
	ldr	r2, [r7, #1004]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r4, r5, asl #2]
	ldr	r3, [r4, r2, asl #2]
	mov	r5, r2
	add	r3, r3, #1
	str	r3, [r4, r2, asl #2]
	b	.L1918
.L1937:
	.align	2
.L1936:
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
	ldr	r4, .L1939
	mov	r2, #432
	ldr	r5, .L1939+4
	mov	r6, r0
	mov	r1, r4
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #432
	add	r0, r6, #432
	mov	r2, #432
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #864
	add	r0, r6, #864
	mov	r2, #432
	blx	r3
	ldr	r3, [r5, #52]
	add	r1, r4, #1296
	add	r0, r6, #1296
	mov	r2, #432
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1940:
	.align	2
.L1939:
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L1942
	mov	r4, r0
	ldr	r6, .L1942+4
	add	r0, r0, #1760
	mov	r2, #90
	add	r0, r0, #4
	ldr	r3, [r5, #52]
	add	r1, r6, #1728
	blx	r3
	add	r1, r6, #1808
	ldr	r3, [r5, #52]
	add	r1, r1, #12
	add	r0, r4, #1728
	mov	r2, #36
	blx	r3
	add	r0, r4, #1936
	ldr	r3, [r5, #52]
	add	r1, r6, #1856
	mov	r2, #8
	add	r0, r0, #14
	blx	r3
	add	r1, r6, #1856
	add	r0, r4, #1840
	ldr	r3, [r5, #52]
	add	r1, r1, #8
	mov	r2, #96
	add	r0, r0, #14
	blx	r3
	add	r1, r6, #1952
	add	r0, r4, #1968
	ldr	r3, [r5, #52]
	add	r1, r1, #8
	mov	r2, #4
	add	r0, r0, #11
	blx	r3
	add	r1, r6, #1952
	add	r0, r4, #1968
	ldr	r3, [r5, #52]
	add	r1, r1, #12
	mov	r2, #5
	add	r0, r0, #15
	blx	r3
	add	r1, r6, #1968
	add	r0, r4, #1984
	ldr	r3, [r5, #52]
	add	r1, r1, #4
	mov	r2, #5
	add	r0, r0, #14
	blx	r3
	add	r1, r6, #1968
	add	r0, r4, #1984
	ldr	r3, [r5, #52]
	add	r1, r1, #12
	mov	r2, #10
	add	r0, r0, #4
	blx	r3
	add	r0, r4, #2000
	mov	r2, #12
	ldr	r1, .L1942+8
	add	r0, r0, #3
	bl	memcpy
	add	r1, r6, #1984
	add	r0, r4, #2000
	add	r1, r1, #8
	add	r0, r0, #15
	ldr	r3, [r5, #52]
	mov	r2, #3
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1943:
	.align	2
.L1942:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LANCHOR0+788
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
	add	r0, r0, #2016
	mov	r2, #69
	ldr	r1, .L1945
	add	r0, r0, #2
	bl	memcpy
	ldmfd	sp, {fp, sp, pc}
.L1946:
	.align	2
.L1945:
	.word	.LANCHOR0+800
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
	add	r0, r5, #2016
	mov	r2, #69
	ldr	r1, .L1955
	add	r0, r0, #2
	bl	memcpy
	ldr	r3, .L1955+4
	add	r0, r5, #1952
	mov	r2, #21
	add	r0, r0, #6
	ldr	r1, .L1955+8
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
	bne	.L1953
	cmp	r4, #2
	beq	.L1954
.L1950:
	mov	r3, #0
	str	r3, [r7]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1953:
	mov	r4, #0
	movw	r8, #8348
.L1949:
	add	r0, r6, r4
	add	r4, r4, #2080
	add	r4, r4, #7
	movw	r2, #2087
	mov	r1, r5
	bl	memcpy
	cmp	r4, r8
	bne	.L1949
	b	.L1950
.L1954:
	ldr	r0, [r7]
	movw	r2, #2087
	mov	r1, r5
	mla	r0, r2, r0, r6
	bl	memcpy
	b	.L1950
.L1956:
	.align	2
.L1955:
	.word	.LANCHOR0+800
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+1996
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
	beq	.L1959
	add	r1, r1, #20
	mov	ip, #1
	ldr	r3, [r0, r1, asl #2]
	ands	r3, r3, ip, asl r2
	movne	r0, ip
	moveq	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1959:
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
.L1968:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1971
	ldr	r3, [r7]
	tst	r3, #2
	beq	.L1971
	ldrb	r3, [r9, #3]	@ zero_extendqisi2
	ldrsh	r1, [r8, #18]
	cmp	r3, #1
	ldrb	r3, [r5]	@ zero_extendqisi2
	addne	r1, r1, r10
	cmp	r3, #0
	usat	r1, #6, r1
	beq	.L1976
.L1965:
	mov	r0, r5
	add	lr, r5, #5
	ldrsb	r3, [r0, #2]!
	mov	ip, r6
	add	r3, r1, r3, asl r4
	usat	r3, #6, r3
	strb	r3, [r6]
.L1967:
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
	bne	.L1967
.L1966:
	ldr	r3, [fp, #-48]
	add	r7, r7, #4
	add	r6, r6, #8
	add	r8, r8, #8
	cmp	r7, r3
	bne	.L1968
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1971:
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r1, r10
	cmp	r3, #0
	bne	.L1965
.L1976:
	ldr	r3, .L1977
	mov	r2, #8
	mov	r0, r6
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1966
.L1978:
	.align	2
.L1977:
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
	add	r10, r6, #294912
	bl	GetCompressRatio
	ldr	r1, [r4, #2492]
	str	r0, [fp, #-48]
	ldr	r0, [r4, #2480]
	bl	GetCompressRatio
	ldr	r0, [r4, #2860]
	ldr	r2, [r4, #2864]
	and	r0, r0, #7
	ldr	r1, [r9, #980]
	ldr	r3, [r9, #976]
	and	r2, r2, #3
	mov	r0, r0, asl #10
	and	r1, r1, #1
	orr	r2, r0, r2, asl #13
	and	r3, r3, #3
	ldr	r0, [r9, #1040]
	orr	r2, r2, r1
	orr	r2, r2, r3, asl #1
	ldr	ip, [r9, #1056]
	and	r3, r0, #15
	ldr	r0, [r9, #1080]
	ldr	r1, [r9, #1052]
	and	ip, ip, #1
	orr	r3, r2, r3, asl #15
	ldr	r2, [r9, #1020]
	and	r1, r1, #1
	mov	r0, r0, asl #7
	orr	r3, r3, ip, asl #9
	orr	r1, r3, r1, asl #8
	uxtb	r0, r0
	and	r3, r2, #1
	orr	r1, r1, r0
	ldr	r2, [r9, #1016]
	orr	r1, r1, r3, asl #6
	ldr	r3, [r9, #1012]
	ldr	r0, [r9, #1008]
	and	r2, r2, #1
	and	r3, r3, #1
	orr	r2, r1, r2, asl #5
	and	r1, r0, #1
	orr	r3, r2, r3, asl #4
	orr	r3, r3, r1, asl #3
	str	r3, [r5]
	ldr	r2, [r9, #1024]
	ldr	r3, [r10, #3408]
	cmp	r2, r3
	movne	r0, #1048576
	beq	.L2021
.L1985:
	ldr	r3, [r4, #2816]
	mov	r7, #0
	ldr	r2, [r4, #2820]
	ldr	lr, [r9, #1092]
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
	ldr	r2, [r9, #1028]
	ldr	r3, [r9, #1024]
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
.L1986:
	add	r0, r5, r7, lsl #3
	mov	lr, r7, asl #2
	add	r0, r0, #12
	mov	ip, #0
.L1987:
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
	bne	.L1987
	add	r7, r7, #1
	cmp	r7, #8
	bne	.L1986
	ldr	ip, [r4, #2880]
	movw	r1, #13460
	ldr	r3, [r4, #2876]
	movt	r1, 4
	cmp	ip, #0
	ldr	r2, [r4, #2872]
	ldrb	r7, [r4, #2868]	@ zero_extendqisi2
	add	r1, r6, r1
	movlt	r0, #268435456
	movge	r0, #0
	cmp	ip, #0
	eor	r8, r2, r2, asr #31
	rsblt	ip, ip, #0
	cmp	r3, #0
	and	ip, ip, #15
	sub	r8, r8, r2, asr #31
	movlt	lr, #1048576
	movge	lr, #0
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r2, #0
	and	r3, r3, #15
	and	r2, r8, #15
	mov	r3, r3, asl #16
	orr	r3, r3, ip, asl #24
	movlt	ip, #4096
	orr	r7, r3, r7
	movge	ip, #0
	orr	r2, r7, r2, asl #8
	mov	r3, #0
	orr	r2, r2, r0
	mov	r0, r3
	orr	lr, r2, lr
	orr	ip, lr, ip
	str	ip, [r5, #80]
	ldrb	lr, [r9, #1099]	@ zero_extendqisi2
	ldrb	r8, [r9, #1100]	@ zero_extendqisi2
	and	lr, lr, #1
	ldrb	r7, [r9, #1096]	@ zero_extendqisi2
	ldrb	ip, [r9, #1097]	@ zero_extendqisi2
	and	r8, r8, #1
	mov	lr, lr, asl #2
	and	r7, r7, #1
	orr	lr, lr, r8, asl #3
	and	ip, ip, #1
	orr	r2, lr, r7
	orr	r2, r2, ip, asl #1
	str	r2, [r5, #84]
.L1992:
	ldr	r2, [r1, #4]!
	and	r2, r2, #15
	orr	r0, r0, r2, asl r3
	add	r3, r3, #4
	cmp	r3, #32
	bne	.L1992
	add	r3, r4, #2624
	movw	r1, #2588
	add	r3, r3, #4
	str	r0, [r5, #88]
	movw	r2, #2596
	movw	r0, #2580
	ldrh	r1, [r3, r1]
	movw	ip, #2604
	ldrh	r2, [r3, r2]
	ubfx	r1, r1, #0, #9
	ldrh	r0, [r3, r0]
	ubfx	r2, r2, #0, #9
	mov	r1, r1, asl #9
	ubfx	r0, r0, #0, #9
	orr	r2, r1, r2, asl #18
	movw	r1, #2612
	orr	r2, r2, r0
	add	r0, r4, #5248
	str	r2, [r5, #92]
	ldrh	r1, [r3, r1]
	ldrh	r2, [r0]
	ubfx	r1, r1, #0, #9
	ldrh	r0, [r3, ip]
	ubfx	r2, r2, #0, #9
	mov	r1, r1, asl #9
	ubfx	r0, r0, #0, #9
	orr	r2, r1, r2, asl #18
	movw	r1, #2636
	orr	r2, r2, r0
	str	r2, [r5, #96]
	movw	r2, #2628
	ldrh	r0, [r3, r1]
	ldrh	r2, [r3, r2]
	mov	r3, #0
	ubfx	r0, r0, #0, #9
	mov	r1, r3
	ubfx	r2, r2, #0, #9
	orr	r2, r2, r0, asl #9
	str	r2, [r5, #100]
.L1993:
	movw	r2, #13402
	movt	r2, 4
	add	r2, r3, r2
	ldrb	r2, [r6, r2]	@ zero_extendqisi2
	orr	r1, r1, r2, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	bne	.L1993
	mov	r3, #0
	str	r1, [r5, #104]
	mov	r1, r3
.L1994:
	movw	r2, #13434
	movt	r2, 4
	add	r2, r3, r2
	ldrb	r2, [r6, r2]	@ zero_extendqisi2
	orr	r1, r1, r2, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	bne	.L1994
	movw	r7, #13404
	mov	lr, #0
	movt	r7, 4
	add	r7, r6, r7
	mov	r6, lr
	str	r1, [r5, #108]
.L1995:
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
	bne	.L1995
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
	ldr	r3, [r9, #1356]
	ldr	r2, [r9, #1352]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #180]
	ldr	r3, [r9, #1372]
	ldr	r2, [r9, #1368]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #184]
	ldr	r3, [r9, #1388]
	ldr	r2, [r9, #1384]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #188]
	ldr	r2, [r9, #1380]
	ldr	r3, [r9, #1396]
	and	r2, r2, #63
	ldr	r1, [r9, #1364]
	and	r3, r3, #63
	mov	r2, r2, asl #8
	and	r1, r1, #63
	orr	r3, r2, r3, asl #16
	orr	r3, r3, r1
	str	r3, [r5, #192]
	ldr	r2, [r9, #1376]
	ldr	r3, [r9, #1392]
	and	r2, r2, #63
	ldr	r1, [r9, #1360]
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
	bls	.L2022
.L1997:
	ldr	r3, [r4, #2816]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #204]
	bhi	.L1999
	add	r3, r4, r3, lsl #4
	add	r3, r3, #5248
	add	r3, r3, #60
	ldr	r2, [r3, #4]
	str	r2, [r4, #2532]
	uxth	r2, r2
	ldr	r3, [r3, #8]
	str	r3, [r4, #2544]
	orr	r2, r2, r3, asl #16
	str	r2, [r5, #204]
.L1999:
	ldr	r3, [r4, #2820]
	cmp	r3, #8
	movhi	r3, #0
	strhi	r3, [r5, #208]
	bhi	.L2001
	add	r3, r4, r3, lsl #4
	add	r3, r3, #5248
	add	r3, r3, #60
	ldr	r2, [r3, #4]
	str	r2, [r4, #2536]
	uxth	r2, r2
	ldr	r3, [r3, #8]
	str	r3, [r4, #2548]
	orr	r2, r2, r3, asl #16
	str	r2, [r5, #208]
.L2001:
	ldr	r3, [r10, #3408]
	ldr	r2, [r10, #3412]
	uxth	r3, r3
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #212]
	ldr	r2, [r4, #2812]
	cmp	r2, #8
	bls	.L2002
	mov	r3, #0
	str	r3, [r5, #216]
	str	r3, [r5, #220]
	str	r3, [r5, #224]
.L2003:
	ldr	r2, [r4, #2816]
	cmp	r2, #8
	bls	.L2005
	mov	r3, #0
	str	r3, [r5, #228]
	str	r3, [r5, #232]
	str	r3, [r5, #236]
	ldr	r2, [r4, #2820]
	cmp	r2, #8
	bhi	.L2023
.L2008:
	mov	r2, r2, asl #4
	ldr	lr, [fp, #-48]
	add	r1, r4, r2
	add	r1, r1, #5248
	ldr	r3, [r1, #64]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, lr, r3
	add	r0, r3, #7
	cmp	r3, #0
	movlt	r3, r0
	mov	r3, r3, asr #3
	str	r3, [r5, #240]
	ldr	r0, [r1, #64]
	ldr	ip, [r1, #68]
	add	r3, r0, #255
	ldr	r6, [r4, #2476]
	bic	r3, r3, #255
	add	r1, ip, #63
	mul	r3, lr, r3
	bic	lr, r1, #63
	cmp	r3, #0
	add	r7, r3, #7
	movlt	r3, r7
	cmp	r6, #1
	mov	r3, r3, asr #3
	mul	r3, lr, r3
	beq	.L2024
.L2010:
	add	r4, r4, r2
	str	r3, [r5, #244]
	add	r4, r4, #5248
	ldr	r1, [r4, #64]
	ldr	r0, [r4, #68]
	add	r3, r1, #508
	add	r1, r1, #1020
	add	r3, r3, #3
	adds	r2, r0, #63
	addmi	r2, r0, #126
	add	r1, r1, #2
	cmp	r3, #0
	mov	r2, r2, asr #6
	movlt	r3, r1
	mov	r3, r3, asr #9
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #248]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2022:
	add	r3, r4, r3, lsl #4
	add	r3, r3, #5248
	add	r3, r3, #60
	ldr	r2, [r3, #4]
	str	r2, [r4, #2528]
	uxth	r2, r2
	ldr	r3, [r3, #8]
	str	r3, [r4, #2540]
	orr	r2, r2, r3, asl #16
	str	r2, [r5, #200]
	b	.L1997
.L2005:
	mov	r2, r2, asl #4
	ldr	lr, [fp, #-48]
	add	r1, r4, r2
	add	r1, r1, #5248
	ldr	r3, [r1, #64]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, lr, r3
	add	r0, r3, #7
	cmp	r3, #0
	movlt	r3, r0
	mov	r3, r3, asr #3
	str	r3, [r5, #228]
	ldr	r0, [r1, #64]
	ldr	ip, [r1, #68]
	add	r3, r0, #255
	ldr	r6, [r4, #2476]
	bic	r3, r3, #255
	add	r1, ip, #63
	mul	r3, lr, r3
	bic	lr, r1, #63
	cmp	r3, #0
	add	r7, r3, #7
	movlt	r3, r7
	cmp	r6, #1
	mov	r3, r3, asr #3
	mul	r3, lr, r3
	beq	.L2025
.L2007:
	add	r2, r4, r2
	str	r3, [r5, #232]
	add	r2, r2, #5248
	ldr	r1, [r2, #64]
	ldr	r0, [r2, #68]
	add	r3, r1, #508
	add	r1, r1, #1020
	add	r3, r3, #3
	adds	r2, r0, #63
	addmi	r2, r0, #126
	add	r1, r1, #2
	cmp	r3, #0
	mov	r2, r2, asr #6
	movlt	r3, r1
	mov	r3, r3, asr #9
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #236]
	ldr	r2, [r4, #2820]
	cmp	r2, #8
	bls	.L2008
.L2023:
	mov	r3, #0
	str	r3, [r5, #240]
	str	r3, [r5, #244]
	str	r3, [r5, #248]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2002:
	mov	r2, r2, asl #4
	ldr	lr, [fp, #-48]
	add	r1, r4, r2
	add	r1, r1, #5248
	ldr	r3, [r1, #64]
	add	r3, r3, #255
	bic	r3, r3, #255
	mov	r3, r3, asl #4
	mul	r3, lr, r3
	add	r0, r3, #7
	cmp	r3, #0
	movlt	r3, r0
	mov	r3, r3, asr #3
	str	r3, [r5, #216]
	ldr	r0, [r1, #64]
	ldr	ip, [r1, #68]
	add	r3, r0, #255
	ldr	r6, [r4, #2476]
	bic	r3, r3, #255
	add	r1, ip, #63
	mul	r3, lr, r3
	bic	lr, r1, #63
	cmp	r3, #0
	add	r7, r3, #7
	movlt	r3, r7
	cmp	r6, #1
	mov	r3, r3, asr #3
	mul	r3, lr, r3
	beq	.L2026
.L2004:
	add	r2, r4, r2
	str	r3, [r5, #220]
	add	r2, r2, #5248
	ldr	r1, [r2, #64]
	ldr	r0, [r2, #68]
	add	r3, r1, #508
	add	r1, r1, #1020
	add	r3, r3, #3
	adds	r2, r0, #63
	addmi	r2, r0, #126
	add	r1, r1, #2
	cmp	r3, #0
	mov	r2, r2, asr #6
	movlt	r3, r1
	mov	r3, r3, asr #9
	mov	r2, r2, asl #5
	mov	r3, r3, asl #4
	mul	r3, r3, r2
	str	r3, [r5, #224]
	b	.L2003
.L2021:
	ldr	r0, [r9, #1028]
	ldr	r3, [r10, #3412]
	cmp	r0, r3
	movne	r0, #1048576
	moveq	r0, #0
	b	.L1985
.L2024:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L2010
	add	lr, r0, #508
	cmp	r1, #0
	add	lr, lr, #3
	addlt	r1, ip, #126
	add	r0, r0, #1020
	cmp	lr, #0
	add	r0, r0, #2
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #9
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2010
.L2025:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L2007
	add	lr, r0, #508
	cmp	r1, #0
	add	lr, lr, #3
	addlt	r1, ip, #126
	add	r0, r0, #1020
	cmp	lr, #0
	add	r0, r0, #2
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #9
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2007
.L2026:
	ldr	lr, [r4, #2480]
	cmp	lr, #0
	bne	.L2004
	add	lr, r0, #508
	cmp	r1, #0
	add	lr, lr, #3
	addlt	r1, ip, #126
	add	r0, r0, #1020
	cmp	lr, #0
	add	r0, r0, #2
	mov	r1, r1, asr #6
	movge	r0, lr
	mov	r0, r0, asr #9
	mov	r1, r1, asl #5
	mov	r0, r0, asl #4
	mla	r3, r0, r1, r3
	b	.L2004
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
	@ args = 0, pretend = 0, frame = 168
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #180)
	sub	sp, sp, #180
	add	r3, r0, #274432
	add	ip, r0, #294912
	mov	r7, r1
	mov	r2, r3
	str	ip, [fp, #-168]
	ldr	r1, [r2, #1076]
	mov	r5, ip
	mov	ip, r2
	ldr	r2, [r2, #1072]
	str	r3, [fp, #-164]
	mov	r3, #1
	mov	lr, r1
	add	r4, r0, #270336
	mov	r6, r2
	str	r2, [fp, #-148]
	mov	r2, r3, asl lr
	mov	r3, r3, asl r6
	str	r3, [fp, #-120]
	ldr	r3, [ip, #1068]
	mov	r10, r2
	ldr	r9, [r7]
	str	r2, [fp, #-196]
	ldr	r2, [r7, #16]
	str	r1, [fp, #-200]
	add	r1, r0, #8
	str	r3, [fp, #-192]
	add	r3, r9, r2
	str	r0, [fp, #-180]
	str	r3, [fp, #-116]
	ldr	r8, [ip, #1064]
	bl	Vp9_SetPoolInfoFrame
	mov	r1, #0
	str	r1, [r5, #3524]
	ldr	r2, [r4, #2552]
	cmp	r10, #0
	ldr	r3, [r4, #2556]
	str	r2, [fp, #-160]
	and	r3, r3, #15
	str	r3, [fp, #-156]
	ble	.L2043
	ldr	r2, [fp, #-192]
	add	r3, r8, #7
	str	r1, [fp, #-184]
	add	r2, r2, #7
	mov	r0, r3, asr #3
	str	r1, [fp, #-172]
	mov	r3, r2, asr #3
	str	r0, [fp, #-152]
	str	r0, [fp, #-208]
	str	r3, [fp, #-204]
	str	r1, [fp, #-112]
	str	r1, [fp, #-188]
.L2042:
	ldr	r3, [fp, #-184]
	ldr	r2, [fp, #-204]
	ldr	r0, [fp, #-200]
	add	r3, r3, r2
	str	r3, [fp, #-184]
	ldr	r2, [fp, #-192]
	mov	r1, r3
	ldr	r3, [fp, #-188]
	mov	r1, r1, asr r0
	str	r1, [fp, #-188]
	ldr	ip, [fp, #-120]
	mov	r3, r3, asl #3
	mov	r0, r1
	cmp	r3, r2
	movge	r3, r2
	str	r3, [fp, #-132]
	mov	r1, r3
	mov	r3, r0, asl #3
	cmp	r3, r2
	movge	r3, r2
	str	r3, [fp, #-136]
	mov	r0, r3
	rsb	r3, r1, r0
	add	r3, r3, #7
	cmp	ip, #0
	mov	r2, r1
	mov	r3, r3, asr #3
	str	r3, [fp, #-128]
	ble	.L2035
	add	r3, r0, #7
	ldr	r0, [fp, #-208]
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
	str	r3, [fp, #-140]
	sub	r3, ip, #1
	str	r3, [fp, #-124]
	ldr	r3, [fp, #-196]
	str	r1, [fp, #-144]
	sub	r3, r3, #1
	str	r3, [fp, #-176]
	b	.L2041
.L2053:
	ldr	r2, [fp, #-176]
	ldr	r1, [fp, #-172]
	cmp	r2, r1
	ldrle	r2, [fp, #-116]
	rsble	r10, r9, r2
	bgt	.L2036
.L2038:
	ldrh	r2, [fp, #-132]
	rsb	r1, r3, r4
	add	r1, r1, #7
	mov	r0, #0
	str	r0, [fp, #-84]
	strh	r2, [fp, #-72]	@ movhi
	mov	r1, r1, asr #3
	ldrh	r2, [fp, #-136]
	ldr	r0, [fp, #-128]
	strh	r4, [fp, #-66]	@ movhi
	strh	r2, [fp, #-70]	@ movhi
	add	r2, r4, #7
	mul	r4, r0, r1
	ldr	r1, [fp, #-160]
	ldr	r0, [fp, #-156]
	ldr	ip, [fp, #-112]
	rsb	r1, r1, r9
	add	r1, r1, r0
	ldr	r0, [fp, #-140]
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
	ldr	ip, [fp, #-144]
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
	bne	.L2051
.L2039:
	ldr	r3, [fp, #-164]
	ldr	r3, [r3, #1768]
	cmp	r10, r3
	movle	r2, #0
	movgt	r2, #1
	orrs	r2, r2, r10, lsr #31
	bne	.L2052
	ldr	r3, [fp, #-120]
	add	r5, r5, #1
	ldr	r2, [r7, #16]
	add	r9, r9, r10
	cmp	r5, r3
	str	r4, [fp, #-112]
	rsb	r2, r10, r2
	str	r2, [r7, #16]
	beq	.L2035
.L2041:
	ldr	r3, [fp, #-152]
	mov	r0, r7
	ldr	r1, [fp, #-148]
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
	ldr	r3, [fp, #-124]
	cmp	r5, r3
	ldr	r3, [fp, #-108]
	bge	.L2053
.L2036:
	ldr	r2, [fp, #-116]
	cmp	r2, #0
	cmpne	r9, #0
	beq	.L2045
	add	r9, r9, #4
	str	r3, [fp, #-108]
	cmp	r2, r9
	bcc	.L2045
	mov	r1, #32
	mov	r0, r7
	bl	BsGet
	ldr	r3, [fp, #-108]
	mov	r10, r0
	b	.L2038
.L2051:
	ldr	r3, [fp, #-168]
	sub	r1, fp, #96
	ldr	r2, [r3, #3524]
	mov	r3, r1
	ldr	r1, [fp, #-180]
	mov	r0, r1
	add	r1, r1, r2, lsl #8
	add	r1, r1, #1024
	add	r1, r1, #8
	bl	Vp9_SetPoolInfoTile
	ldr	r2, [fp, #-168]
	ldr	r3, [r2, #3524]
	add	r3, r3, #1
	str	r3, [r2, #3524]
	b	.L2039
.L2045:
	mvn	r0, #0
.L2034:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2052:
	str	r3, [sp, #4]
	mov	r0, #0
	movw	r3, #4556
	str	r10, [sp]
	ldr	r2, .L2054
	ldr	r1, .L2054+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2035:
	ldr	r3, [fp, #-172]
	ldr	r2, [fp, #-196]
	add	r3, r3, #1
	str	r3, [fp, #-172]
	cmp	r3, r2
	bne	.L2042
.L2043:
	mov	r0, #0
	b	.L2034
.L2055:
	.align	2
.L2054:
	.word	.LANCHOR0+872
	.word	.LC35
	UNWIND(.fnend)
	.size	Vp9_DecodeTilesCtrl, .-Vp9_DecodeTilesCtrl
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
	ldr	r4, .L2057
	mov	r2, #18
	mov	r5, r0
	mov	r6, r1
	add	r7, r1, #108
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
	mov	r1, r7
	ldr	r3, [r4, #52]
	add	r0, r5, #192
	mov	r2, #18
	blx	r3
	mov	r1, r7
	ldr	r3, [r4, #52]
	add	r0, r5, #256
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #126
	add	r0, r5, #288
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #144
	add	r0, r5, #320
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #162
	add	r0, r5, #352
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #180
	add	r0, r5, #384
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #198
	add	r0, r5, #416
	mov	r2, #18
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r6, #216
	add	r0, r5, #448
	mov	r2, #18
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L2058:
	.align	2
.L2057:
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r1
	mov	r7, r2
	mov	r8, r3
	mov	r5, r0
	ldr	r6, [fp, #4]
	bl	Vp9_TxCoefProbConvert2
	add	r1, r4, #216
	add	r0, r5, #512
	bl	Vp9_TxCoefProbConvert2
	add	r1, r4, #432
	add	r0, r5, #1024
	add	r10, r4, #1728
	bl	Vp9_TxCoefProbConvert2
	add	r1, r4, #648
	add	r0, r5, #1536
	add	r9, r4, #1760
	bl	Vp9_TxCoefProbConvert2
	add	r1, r4, #864
	add	r0, r5, #2048
	add	r10, r10, #8
	bl	Vp9_TxCoefProbConvert2
	add	r1, r4, #1072
	add	r1, r1, #8
	add	r0, r5, #2560
	bl	Vp9_TxCoefProbConvert2
	add	r1, r4, #1296
	add	r0, r5, #3072
	add	r9, r9, #12
	bl	Vp9_TxCoefProbConvert2
	add	r1, r4, #1504
	add	r1, r1, #8
	add	r0, r5, #3584
	bl	Vp9_TxCoefProbConvert2
	add	r2, r5, #4096
	mov	r3, #0
.L2060:
	mov	r0, r10
	mov	r1, #8
	ldrb	ip, [r0, #-8]!	@ zero_extendqisi2
	b	.L2064
.L2062:
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	orr	ip, ip, lr, asl r1
	add	r1, r1, #8
	cmp	r1, #32
	streq	ip, [r2, r3, asl #2]
	addeq	r3, r3, #1
	moveq	ip, #0
	moveq	r1, ip
.L2064:
	cmp	r10, r0
	bne	.L2062
	add	r10, r10, #9
	str	ip, [r2, r3, asl #2]
	cmp	r10, r9
	add	r3, r3, #2
	bne	.L2060
	add	r10, r4, #1856
	add	r10, r10, #6
.L2063:
	mov	r0, r9
	mov	r1, #8
	ldrb	ip, [r0, #-8]!	@ zero_extendqisi2
	b	.L2068
.L2066:
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	orr	ip, ip, lr, asl r1
	add	r1, r1, #8
	cmp	r1, #32
	streq	ip, [r2, r3, asl #2]
	addeq	r3, r3, #1
	moveq	ip, #0
	moveq	r1, ip
.L2068:
	cmp	r9, r0
	bne	.L2066
	add	r9, r9, #9
	str	ip, [r2, r3, asl #2]
	cmp	r9, r10
	add	r3, r3, #2
	bne	.L2063
	ldrb	r0, [r7, #7]	@ zero_extendqisi2
	cmp	r6, #0
	ldrb	r1, [r7, #8]	@ zero_extendqisi2
	add	r5, r5, #4352
	ldrb	r3, [r7, #5]	@ zero_extendqisi2
	movne	r8, #0
	ldrb	ip, [r7, #6]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r1, r0, r1, asl #24
	mov	r6, #3
	orr	r1, r1, r3
	mov	r3, r8, asl #6
	orr	r1, r1, ip, asl #8
	str	r1, [r2, #256]
	ldrb	r1, [r7, #10]	@ zero_extendqisi2
	sub	r8, r3, r8, asl #4
	ldrb	r0, [r7, #11]	@ zero_extendqisi2
	add	lr, r8, #1840
	add	r8, r8, #1888
	add	lr, lr, #13
	mov	r3, r1, asl #8
	ldrb	r1, [r7, #9]	@ zero_extendqisi2
	orr	r3, r3, r0, asl #16
	add	r8, r8, #13
	orr	r3, r3, r1
	str	r3, [r2, #260]
	ldrb	r3, [r7, #13]	@ zero_extendqisi2
	add	lr, r4, lr
	ldrb	r1, [r7, #14]	@ zero_extendqisi2
	add	r8, r4, r8
	ldrb	r0, [r7, #12]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	orr	r1, r3, r1, asl #16
	mov	r3, #0
	orr	r1, r1, r0
	str	r1, [r2, #264]
	mov	r1, r3
.L2070:
	mov	r0, lr
	mov	r2, #0
.L2072:
	ldrb	ip, [r0, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	orr	r1, r1, ip, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r1, [r5, r6, asl #2]
	addeq	r6, r6, #1
	moveq	r1, #0
	moveq	r3, r1
	cmp	r2, #3
	bne	.L2072
	add	lr, lr, #3
	cmp	lr, r8
	bne	.L2070
	ldrb	r3, [r4, #2016]	@ zero_extendqisi2
	add	r2, r5, r6, lsl #2
	ldrb	r0, [r4, #2017]	@ zero_extendqisi2
	add	lr, r6, #11
	ldrb	r1, [r4, #2015]	@ zero_extendqisi2
	mov	r7, #0
	mov	r3, r3, asl #8
	orr	r3, r3, r0, asl #16
	orr	r3, r3, r1
	str	r3, [r5, r6, asl #2]
	ldrb	r0, [r4, #2009]	@ zero_extendqisi2
	mov	r3, r7
	ldrb	ip, [r4, #2010]	@ zero_extendqisi2
	mov	r1, r7
	ldrb	r6, [r4, #2014]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r0, r0, ip, asl #24
	ldrb	ip, [r4, #2013]	@ zero_extendqisi2
	orr	r0, r0, ip
	orr	r0, r0, r6, asl #8
	str	r0, [r2, #4]
	ldrb	r0, [r4, #2003]	@ zero_extendqisi2
	ldrb	ip, [r4, #2004]	@ zero_extendqisi2
	ldrb	r6, [r4, #2012]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r0, r0, ip, asl #24
	ldrb	ip, [r4, #2011]	@ zero_extendqisi2
	orr	r0, r0, ip
	orr	r0, r0, r6, asl #8
	str	r0, [r2, #8]
	ldrb	r0, [r4, #2007]	@ zero_extendqisi2
	ldrb	ip, [r4, #2008]	@ zero_extendqisi2
	ldrb	r6, [r4, #2006]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r0, r0, ip, asl #24
	ldrb	ip, [r4, #2005]	@ zero_extendqisi2
	orr	r0, r0, ip
	orr	r0, r0, r6, asl #8
	str	r0, [r2, #12]
	ldrb	r0, [r4, #1981]	@ zero_extendqisi2
	ldrb	ip, [r4, #1982]	@ zero_extendqisi2
	ldrb	r6, [r4, #1980]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r0, r0, ip, asl #24
	ldrb	ip, [r4, #1979]	@ zero_extendqisi2
	orr	r0, r0, ip
	orr	r0, r0, r6, asl #8
	str	r0, [r2, #16]
	ldrb	r0, [r4, #1985]	@ zero_extendqisi2
	ldrb	ip, [r4, #1986]	@ zero_extendqisi2
	ldrb	r6, [r4, #1984]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r0, r0, ip, asl #24
	ldrb	ip, [r4, #1983]	@ zero_extendqisi2
	orr	r0, r0, ip
	orr	r0, r0, r6, asl #8
	str	r0, [r2, #20]
	ldrb	r0, [r4, #1999]	@ zero_extendqisi2
	ldrb	ip, [r4, #2000]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r0, r0, ip, asl #24
	ldrb	ip, [r4, #1987]	@ zero_extendqisi2
	ldrb	r6, [r4, #1998]	@ zero_extendqisi2
	orr	r0, r0, ip
	orr	r0, r0, r6, asl #8
	str	r0, [r2, #24]
	ldrb	ip, [r4, #2002]	@ zero_extendqisi2
	ldrb	r0, [r4, #2001]	@ zero_extendqisi2
	orr	r0, r0, ip, asl #8
	str	r0, [r2, #28]
	ldrb	r0, [r4, #1990]	@ zero_extendqisi2
	ldrb	ip, [r4, #1991]	@ zero_extendqisi2
	ldrb	r6, [r4, #1989]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r0, r0, ip, asl #24
	ldrb	ip, [r4, #1988]	@ zero_extendqisi2
	orr	r0, r0, ip
	orr	r0, r0, r6, asl #8
	str	r0, [r2, #32]
	ldrb	r0, [r4, #1994]	@ zero_extendqisi2
	ldrb	ip, [r4, #1995]	@ zero_extendqisi2
	ldrb	r6, [r4, #1993]	@ zero_extendqisi2
	mov	r0, r0, asl #16
	orr	r0, r0, ip, asl #24
	ldrb	ip, [r4, #1992]	@ zero_extendqisi2
	orr	r0, r0, ip
	orr	r0, r0, r6, asl #8
	str	r0, [r2, #36]
	ldrb	r0, [r4, #1997]	@ zero_extendqisi2
	ldrb	ip, [r4, #1958]	@ zero_extendqisi2
	mov	r0, r0, asl #8
	orr	r0, r0, ip, asl #16
	ldrb	ip, [r4, #1996]	@ zero_extendqisi2
	orr	r0, r0, ip
	str	r0, [r2, #40]
	mov	r2, #1
.L2074:
	add	r0, r2, r7
	add	r0, r0, #1952
	add	r0, r0, #5
	add	r0, r4, r0
.L2076:
	ldrb	ip, [r0, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	orr	r1, r1, ip, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r1, [r5, lr, asl #2]
	addeq	lr, lr, #1
	moveq	r1, #0
	moveq	r3, r1
	cmp	r2, #2
	ble	.L2076
	add	r7, r7, #3
	mov	r2, #0
	cmp	r7, #21
	bne	.L2074
	add	r6, r4, #8
	mov	r3, r4
	mov	r1, r2
.L2077:
	add	r0, r2, #8
	ldrb	ip, [r3, #1950]	@ zero_extendqisi2
	cmp	r0, #32
	orr	r1, r1, ip, asl r2
	add	r2, r2, #16
	beq	.L2107
	ldrb	ip, [r3, #1951]	@ zero_extendqisi2
	cmp	r2, #32
	orr	r1, r1, ip, asl r0
	streq	r1, [r5, lr, asl #2]
	moveq	r1, #0
	addeq	lr, lr, #1
	moveq	r2, r1
.L2080:
	add	r3, r3, #2
	cmp	r3, r6
	bne	.L2077
	ldrb	r2, [r4, #2054]	@ zero_extendqisi2
	add	ip, r4, #2016
	ldrb	r3, [r4, #2021]	@ zero_extendqisi2
	add	r6, r4, #2096
	add	r0, r5, lr, lsl #2
	add	ip, ip, #15
	orr	r3, r3, r2, asl #8
	str	r3, [r5, lr, asl #2]
	ldrb	r3, [r4, #2019]	@ zero_extendqisi2
	add	lr, lr, #2
	ldrb	r2, [r4, #2020]	@ zero_extendqisi2
	add	r6, r6, #1
	ldrb	r1, [r4, #2018]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	orr	r2, r3, r2, asl #16
	mov	r3, #0
	orr	r2, r2, r1
	mov	r1, r3
	str	r2, [r0, #4]
.L2082:
	sub	r2, ip, #10
.L2084:
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	orr	r1, r1, r0, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r1, [r5, lr, asl #2]
	addeq	lr, lr, #1
	moveq	r1, #0
	moveq	r3, r1
	cmp	ip, r2
	bne	.L2084
	add	ip, ip, #33
	cmp	ip, r6
	bne	.L2082
	ldrb	r1, [r4, #2065]	@ zero_extendqisi2
	add	r6, r4, #2032
	ldrb	r2, [r4, #2032]	@ zero_extendqisi2
	add	r6, r6, #10
	add	r7, r4, #2096
	mov	r3, #0
	add	r7, r7, #12
	orr	r2, r2, r1, asl #8
	add	ip, lr, #1
	str	r2, [r5, lr, asl #2]
	mov	r1, r3
	mov	lr, r6
.L2086:
	sub	r2, lr, #10
.L2088:
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	orr	r1, r1, r0, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r1, [r5, ip, asl #2]
	addeq	ip, ip, #1
	moveq	r1, #0
	moveq	r3, r1
	cmp	r2, lr
	bne	.L2088
	add	lr, r2, #33
	cmp	lr, r7
	bne	.L2086
	mov	r3, #0
	mov	r1, r3
.L2089:
	mov	r8, r6
	mov	r9, #2
.L2094:
	mov	r0, r8
	mov	r2, #0
.L2091:
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	orr	r1, r1, lr, asl r3
	add	r3, r3, #8
	cmp	r3, #32
	streq	r1, [r5, ip, asl #2]
	addeq	ip, ip, #1
	moveq	r1, #0
	moveq	r3, r1
	cmp	r2, #3
	bne	.L2091
	subs	r9, r9, #1
	add	r8, r8, #3
	bne	.L2094
	add	r6, r6, #33
	cmp	r6, r7
	bne	.L2089
	ldrb	r3, [r4, #2050]	@ zero_extendqisi2
	add	r0, r5, ip, lsl #2
	ldrb	r1, [r4, #2051]	@ zero_extendqisi2
	ldrb	r2, [r4, #2049]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	orr	r3, r3, r1, asl #16
	orr	r3, r3, r2
	str	r3, [r5, ip, asl #2]
	ldrb	r3, [r4, #2083]	@ zero_extendqisi2
	ldrb	r1, [r4, #2084]	@ zero_extendqisi2
	ldrb	r2, [r4, #2082]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	orr	r3, r3, r1, asl #16
	orr	r3, r3, r2
	str	r3, [r0, #4]
	ldrb	r1, [r4, #2053]	@ zero_extendqisi2
	ldrb	r3, [r4, #2086]	@ zero_extendqisi2
	ldrb	r2, [r4, #2052]	@ zero_extendqisi2
	ldrb	ip, [r4, #2085]	@ zero_extendqisi2
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r0, #8]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2107:
	str	r1, [r5, lr, asl #2]
	mov	r2, #8
	add	lr, lr, #1
	ldrb	r1, [r3, #1951]	@ zero_extendqisi2
	b	.L2080
	UNWIND(.fnend)
	.size	Vp9_ProbBurstConvert, .-Vp9_ProbBurstConvert
	.align	2
	.global	Vp9_DecodeTiles
	.type	Vp9_DecodeTiles, %function
Vp9_DecodeTiles:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
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
	add	r5, r0, #274432
	add	r4, r0, #294912
	add	r7, r0, #270336
	ldr	r9, [r5, #980]
	mov	r6, r0
	ldr	r3, [r5, #1084]
	sub	r0, fp, #84
	clz	ip, r9
	ldr	r8, [r5, #1060]
	ldr	r10, [r7, #2688]
	mov	lr, #0
	str	r3, [fp, #-108]
	mov	ip, ip, lsr #5
	ldr	r3, [r7, #2680]
	str	ip, [r4, #3480]
	str	r9, [r4, #3492]
	ldr	ip, [r5, #1012]
	str	r3, [fp, #-104]
	str	r8, [fp, #-96]
	movw	r8, #14072
	str	ip, [r4, #3500]
	movt	r8, 4
	ldr	ip, [r5, #1080]
	add	r8, r6, r8
	str	r2, [fp, #-116]
	str	r1, [fp, #-112]
	str	ip, [r4, #3484]
	ldr	ip, [r5, #1056]
	str	lr, [fp, #-92]
	str	lr, [fp, #-88]
	str	ip, [r4, #3504]
	ldr	ip, [r7, #2684]
	str	ip, [r4, #3508]
	ldr	ip, [r5, #1092]
	str	ip, [r4, #3512]
	ldr	ip, [r5, #976]
	str	ip, [r4, #3496]
	bl	BsInit
	ldr	r2, [r4, #3480]
	ldr	r3, [fp, #-108]
	cmp	r2, #0
	ldr	r2, [r4, #3500]
	bne	.L2110
	cmp	r2, #0
	beq	.L2119
.L2110:
	movw	r1, #16159
	stmia	sp, {r2, r9}
	mov	r0, r8
	sub	r2, fp, #96
	movt	r1, 4
	add	r1, r6, r1
	bl	Vp9_SetupPastIndependence
	ldr	r3, .L2121
	movw	r0, #10884
	mov	r2, #16
	movt	r0, 4
	mov	r1, #0
	add	r0, r6, r0
	ldr	r3, [r3, #48]
	blx	r3
.L2111:
	ldr	r3, [fp, #-96]
	movw	r2, #2087
	movw	r1, #16159
	add	r0, r5, #1776
	movt	r1, 4
	add	r0, r0, #8
	mla	r3, r2, r3, r6
	add	r1, r3, r1
	bl	memcpy
	sub	r0, fp, #84
	bl	Vp9_Cabac_ReaderInit
	ldr	r1, [r4, #3508]
	ldr	r0, [r4, #3512]
	sub	lr, fp, #88
	ldr	ip, [fp, #-104]
	mov	r2, r9
	ldr	r3, [r4, #3484]
	str	r1, [sp, #4]
	mov	r1, r8
	str	ip, [sp, #12]
	sub	ip, fp, #92
	str	r0, [sp]
	sub	r0, fp, #84
	str	r10, [sp, #8]
	str	lr, [sp, #20]
	str	ip, [sp, #16]
	bl	Vp9_ReadCompressedHeader
	cmp	r0, #0
	bne	.L2120
	ldr	r3, [fp, #-88]
	ldr	r2, [fp, #-92]
	str	r3, [r7, #2860]
	str	r3, [r4, #3488]
	ldr	r3, [r7, #2972]
	str	r2, [r7, #2864]
	cmp	r3, #0
	bne	.L2114
	movw	r9, #13384
	movt	r9, 4
	add	r9, r6, r9
.L2115:
	ldr	ip, [r4, #3484]
	movw	r0, #1037
	ldr	r3, [r5, #980]
	mov	r2, r9
	mov	r1, r8
	movt	r0, 4
	str	ip, [sp]
	add	r0, r6, r0
	bl	Vp9_ProbBurstConvert
	ldr	r2, [r7, #2636]
	ldr	r3, [fp, #-112]
	sub	r1, fp, #84
	ldr	ip, [fp, #-116]
	mov	r0, r6
	add	r3, r3, r2
	str	r3, [fp, #-84]
	rsb	r10, r2, ip
	str	r10, [fp, #-68]
	bl	Vp9_DecodeTilesCtrl
	mov	r0, #0
.L2113:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2119:
	ldr	r1, [r4, #3484]
	cmp	r1, #0
	beq	.L2111
	b	.L2110
.L2114:
	movw	r0, #10820
	movt	r0, 4
	add	r0, r6, r0
	add	r9, r0, #2560
	add	r1, r0, #336
	add	r9, r9, #4
	add	r0, r0, #256
	mov	r2, r9
	bl	Vp9_Vfmw_LoopFilterFrameInit
	b	.L2115
.L2120:
	ldr	r1, .L2121+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2113
.L2122:
	.align	2
.L2121:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC36
	UNWIND(.fnend)
	.size	Vp9_DecodeTiles, .-Vp9_DecodeTiles
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
.L2124:
	ldr	r9, [fp, #-48]
	sub	r8, r7, #1152
	ldr	r4, [fp, #-52]
.L2130:
	add	r6, r4, #576
	mov	r5, r8
	mov	ip, r9
.L2128:
	add	lr, ip, #24
	mov	r0, r5
	mov	r1, r4
.L2125:
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
	bne	.L2125
	add	r4, r4, #96
	add	r5, r5, #96
	cmp	r6, r4
	mov	ip, lr
	bne	.L2128
	add	r8, r8, #576
	add	r9, r9, #144
	cmp	r7, r8
	mov	r4, r6
	bne	.L2130
	ldr	r3, [fp, #-52]
	add	r7, r7, #1152
	add	r3, r3, #1152
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-56]
	cmp	r7, r3
	ldr	r3, [fp, #-48]
	add	r3, r3, #288
	str	r3, [fp, #-48]
	bne	.L2124
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_CoefCountRestore, .-Vp9_CoefCountRestore
	.align	2
	.global	Vp9_RestoreCounts
	.type	Vp9_RestoreCounts, %function
Vp9_RestoreCounts:
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
	mov	r4, r2
	mov	r5, r1
	add	r2, r2, #9216
	mov	r6, r0
	add	r2, r2, #12
	mov	r1, r4
	mov	r0, r5
	bl	Vp9_CoefCountRestore
	add	r2, r4, #9792
	add	r2, r2, #12
	add	r1, r4, #2304
	add	r0, r5, #2304
	bl	Vp9_CoefCountRestore
	add	r2, r4, #10368
	add	r2, r2, #12
	add	r1, r4, #4608
	add	r0, r5, #4608
	bl	Vp9_CoefCountRestore
	add	r2, r4, #10944
	add	r0, r5, #6912
	add	r2, r2, #12
	add	r1, r4, #6912
	bl	Vp9_CoefCountRestore
	add	r0, r6, #294912
	ldr	r3, [r0, #3480]
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r0, #3484]
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r2, r4, #8192
	add	r0, r5, #9600
	add	r3, r5, #9984
	add	lr, r5, #10176
	add	r0, r0, #32
	add	r3, r3, #48
	str	r0, [r2, #1028]
	add	r0, r5, #10304
	str	r3, [r2, #3340]
	add	r3, r5, #10368
	add	r0, r0, #40
	str	r0, [r2, #3360]
	add	r0, r5, #10496
	mov	r1, lr
	add	r4, r5, #10048
	add	lr, lr, #16
	add	r1, r1, #48
	str	lr, [r2, #3348]
	str	r1, [r2, #3352]
	mov	lr, r3
	add	r1, r5, #10432
	add	lr, lr, #56
	str	lr, [r2, #3364]
	add	lr, r5, #10560
	add	ip, r5, #9216
	add	r4, r4, #32
	str	ip, [r2, #1032]
	add	ip, r5, #10240
	str	r4, [r2, #3344]
	mov	r4, r3
	add	r3, r3, #16
	add	r4, r4, #32
	str	r3, [r2, #3372]
	mov	r3, r0
	str	r4, [r2, #3368]
	mov	r4, r0
	add	r0, r0, #8
	str	r0, [r2, #3416]
	add	r0, r5, #10688
	add	r6, r5, #9472
	add	ip, ip, #24
	add	r0, r0, #8
	str	r6, [r2, #1024]
	mov	r6, r3
	str	ip, [r2, #3356]
	mov	ip, r1
	str	r3, [r2, #3384]
	add	r1, r1, #24
	add	ip, ip, #48
	add	r3, r3, #16
	str	r1, [r2, #3376]
	mov	r1, lr
	str	ip, [r2, #3380]
	mov	ip, lr
	str	r3, [r2, #3388]
	add	lr, lr, #40
	add	r3, r5, #10752
	str	lr, [r2, #3392]
	str	r0, [r2, #3428]
	add	lr, r5, #10816
	add	r0, r5, #10880
	add	r4, r4, #60
	add	r1, r1, #48
	add	ip, ip, #56
	str	r4, [r2, #3420]
	mov	r4, r3
	str	r1, [r2, #3424]
	add	r3, r3, #24
	mov	r1, lr
	str	ip, [r2, #3396]
	add	r4, r4, #56
	mov	ip, lr
	str	r3, [r2, #3400]
	add	lr, lr, #24
	mov	r3, r0
	add	r1, r1, #40
	add	ip, ip, #56
	str	r0, [r2, #3440]
	add	r3, r3, #16
	add	r0, r0, #8
	str	r4, [r2, #3432]
	str	lr, [r2, #3404]
	str	r1, [r2, #3436]
	str	ip, [r2, #3408]
	str	r0, [r2, #3412]
	str	r3, [r2, #3444]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp9_RestoreCounts, .-Vp9_RestoreCounts
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	subs	r9, r0, #0
	str	r1, [fp, #-56]
	str	r2, [fp, #-48]
	str	r3, [fp, #-60]
	beq	.L2187
	ldr	r3, [fp, #-48]
	add	r8, r9, #270336
	cmp	r3, #0
	add	r3, r9, #274432
	ldrb	r2, [r8, #2089]	@ zero_extendqisi2
	mov	r1, r3
	str	r3, [fp, #-52]
	ldr	r0, [r1, #1060]
	ldr	r3, [r8, #2476]
	ldr	r1, [r1, #1052]
	str	r0, [fp, #-72]
	strb	r2, [r8, #2628]
	str	r1, [fp, #-68]
	str	r3, [r8, #2632]
	bne	.L2188
	add	r7, r9, #294912
	ldr	r3, [r7, #3424]
	cmp	r3, #0
	beq	.L2140
.L2196:
	ldr	r2, [r7, #3464]
	ldr	r3, [r7, #3460]
	cmp	r2, r3
	beq	.L2140
.L2141:
	ldr	r1, [r8, #2612]
	ldr	r0, [r7, #3516]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	str	r3, [fp, #-64]
	beq	.L2158
	movw	r4, #10932
	movw	r5, #11012
	movw	r10, #10968
	movt	r4, 4
	movt	r5, 4
	movt	r10, 4
	add	r4, r9, r4
	add	r5, r9, r5
	add	r6, r8, #2704
	add	r10, r9, r10
	b	.L2144
.L2142:
	clz	r3, r3
	cmp	r0, #0
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L2189
.L2143:
	cmp	r4, r10
	beq	.L2190
.L2144:
	ldr	r3, [r6, #4]!
	ldr	r0, [r4, #4]!
	adds	r2, r3, #0
	ldr	r1, [r5, #4]!
	movne	r2, #1
	cmp	r0, #0
	movne	r2, #0
	cmp	r2, #0
	beq	.L2142
	mov	r2, #1
	ldr	r0, [r7, #3516]
	bl	FSP_SetRef
	cmp	r4, r10
	bne	.L2144
.L2190:
	ldr	r3, .L2200
	movw	r0, #10820
	movt	r0, 4
	add	r0, r9, r0
	add	r1, r0, #80
	mov	r2, #36
	ldr	r3, [r3, #52]
	add	r0, r0, #116
	blx	r3
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	blt	.L2145
	cmp	r3, #100
	movlt	r2, r3
	ldr	r3, [fp, #-64]
	movge	r2, #100
	str	r2, [r3, #152]
	ldr	r3, [r9]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L2191
.L2146:
	mov	r0, r9
	bl	VP9_SetImgFormat
	ldr	r3, [r8, #2564]
	cmp	r3, #2
	beq	.L2192
.L2147:
	ldr	r3, [fp, #-52]
	ldr	r3, [r3, #996]
	cmp	r3, #0
	bne	.L2149
.L2148:
	mvn	r3, #0
	ldr	r1, [r8, #2612]
	str	r3, [r8, #2616]
	mov	r2, #0
	ldr	r0, [r7, #3516]
	bl	FSP_SetDisplay
	ldr	r1, [r8, #2616]
.L2150:
	cmn	r1, #1
	beq	.L2151
	ldr	r0, [r7, #3516]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L2193
	mov	r2, #1
	ldr	r1, [r8, #2616]
	ldr	r0, [r7, #3516]
	bl	FSP_SetDisplay
	movw	r3, #13688
	ldr	r0, [r7, #3516]
	movt	r3, 4
	str	r4, [sp]
	mov	r2, r9
	add	r3, r9, r3
	mov	r1, #17
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r4, r0
	bne	.L2194
.L2151:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L2153
	ldr	r1, [fp, #-60]
	ldr	r2, .L2200+4
	mov	r3, r1, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #2
	beq	.L2139
.L2153:
	ldr	r3, [fp, #-52]
	ldr	r4, [r3, #1000]
	cmp	r4, #0
	beq	.L2195
.L2139:
	mov	r4, #0
.L2184:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2189:
	ldr	r0, [r7, #3516]
	bl	FSP_SetRef
	b	.L2143
.L2188:
	ldr	r1, [fp, #-60]
	ldr	r2, .L2200+4
	mov	r3, r1, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L2153
	add	r7, r9, #294912
	ldr	r3, [r7, #3424]
	cmp	r3, #0
	bne	.L2196
.L2140:
	mov	r1, r9
	mov	r0, #17
	bl	ReleasePacket
	mov	r3, #0
	str	r3, [r7, #3424]
	b	.L2141
.L2149:
	ldr	r1, [r8, #2612]
	str	r1, [r8, #2616]
	b	.L2150
.L2195:
	ldr	r0, [r8, #2364]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L2197
	add	r7, r9, #294912
	ldr	r2, [r7, #3480]
	cmp	r2, #0
	ldr	r2, [r7, #3500]
	bne	.L2198
	cmp	r2, #0
	movne	r5, r4
	bne	.L2157
	ldr	r2, [r7, #3484]
	cmp	r2, #0
	ldr	r2, [fp, #-72]
	movne	r5, #0
	moveq	r5, r2
.L2156:
	ldr	r2, [r7, #3504]
	cmp	r2, #0
	beq	.L2199
.L2157:
	ldr	r3, [fp, #-68]
	cmp	r3, #0
	beq	.L2139
	movw	r2, #2087
	ldr	r3, [fp, #-52]
	mla	r9, r2, r5, r9
	add	r1, r3, #1776
	movw	r0, #16159
	add	r1, r1, #8
	movt	r0, 4
	add	r0, r9, r0
	bl	memcpy
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2145:
	ldr	r2, [fp, #-64]
	mov	r3, #0
	str	r3, [r2, #152]
	b	.L2146
.L2192:
	ldr	r3, [r8, #2620]
	cmp	r3, #0
	bne	.L2148
	b	.L2147
.L2198:
	cmp	r2, #0
	mov	r5, r4
	beq	.L2156
	b	.L2157
.L2194:
	ldr	r1, [r8, #2616]
	mov	r2, #0
	ldr	r0, [r7, #3516]
	bl	FSP_SetDisplay
	ldr	r1, .L2200+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2199:
	ldr	r1, [fp, #-72]
	movw	ip, #2087
	ldr	r2, .L2200
	mov	r0, r3
	movw	r10, #16159
	str	r3, [fp, #-48]
	mla	ip, ip, r1, r9
	ldr	r1, [r8, #2364]
	ldr	r8, [r2, #140]
	mov	r2, #11264
	movw	r6, #24508
	movt	r10, 4
	add	r10, ip, r10
	blx	r8
	ldr	r3, [fp, #-48]
	movt	r6, 4
	add	r6, r9, r6
	mov	r0, r9
	movw	r8, #14072
	mov	r1, r3
	mov	r2, r6
	bl	Vp9_RestoreCounts
	ldr	r3, [r7, #3496]
	movt	r8, 4
	add	r8, r9, r8
	mov	r2, r6
	mov	r1, r10
	str	r3, [sp, #8]
	mov	r0, r8
	ldr	ip, [r7, #3484]
	mov	r3, r5
	str	ip, [sp, #4]
	ldr	ip, [r7, #3492]
	str	ip, [sp]
	bl	Vp9_AdaptResidualProbs
	ldr	r3, [r7, #3480]
	cmp	r3, #0
	bne	.L2157
	ldr	r3, [r7, #3484]
	cmp	r3, #0
	bne	.L2157
	ldr	ip, [r7, #3488]
	mov	r2, r6
	ldr	r3, [r7, #3512]
	mov	r1, r10
	mov	r0, r8
	str	ip, [sp]
	bl	Vp9_AdaptModeProbs
	ldr	r3, [r7, #3508]
	mov	r2, r6
	mov	r1, r10
	mov	r0, r8
	bl	Vp9_AdaptMvProbs
	b	.L2157
.L2191:
	ldr	r1, .L2200+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r8, #2612]
	ldr	r0, [r7, #3516]
	mov	r2, #0
	bl	FSP_SetDisplay
	ldr	r1, [r8, #2612]
	ldr	r0, [r7, #3516]
	mov	r2, #0
	mvn	r4, #0
	bl	FSP_SetRef
	b	.L2184
.L2187:
	movw	r2, #2504
	ldr	r1, .L2200+16
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2184
.L2193:
	movw	r2, #2597
	ldr	r1, .L2200+20
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2184
.L2158:
	ldr	r1, .L2200+24
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L2184
.L2197:
	ldr	r1, .L2200+28
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L2184
.L2201:
	.align	2
.L2200:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_VdmDrvParam+40
	.word	.LC40
	.word	.LC38
	.word	.LC15
	.word	.LC39
	.word	.LC37
	.word	.LC41
	UNWIND(.fnend)
	.size	VP9DEC_VDMPostProc, .-VP9DEC_VDMPostProc
	.align	2
	.global	VP9DEC_DecodeFame
	.type	VP9DEC_DecodeFame, %function
VP9DEC_DecodeFame:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r4, r0, #294912
	movw	r9, #14040
	movw	r10, #10820
	ldr	r3, [r4, #3420]
	movt	r9, 4
	movt	r10, 4
	mov	r6, r0
	cmp	r3, #0
	str	r1, [fp, #-60]
	add	r7, r0, #274432
	add	r9, r0, r9
	add	r10, r0, r10
	beq	.L2203
	ldr	r3, [r7, #972]
	cmp	r3, #0
	blt	.L2203
.L2204:
	str	r3, [r4, #3416]
	mov	r1, r10
	mov	r0, r9
	bl	Read_UnCompressed_Header
	subs	r8, r0, #0
	bne	.L2245
	ldr	r2, [r7, #1040]
	ldr	r3, [r6]
	str	r2, [r3, #932]
	ldr	r2, [r7, #1040]
	cmp	r2, #8
	beq	.L2210
	ldr	r1, .L2298
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2298+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2210
	ldr	ip, [r7, #1040]
	mov	r3, #8
	str	r8, [fp, #-52]
	sub	r2, fp, #52
	mov	r1, #119
	ldr	r0, [r4, #3516]
	str	ip, [fp, #-48]
	blx	r5
.L2210:
	ldr	r3, [r7, #1000]
	add	r5, r6, #270336
	cmp	r3, #0
	beq	.L2282
.L2212:
	ldr	r2, [r7, #1024]
	sub	r3, r2, #128
	cmp	r3, #3968
	bhi	.L2213
	ldr	r3, [r7, #1028]
	sub	r1, r3, #80
	cmp	r1, #4016
	bhi	.L2213
	adds	r1, r2, #63
	str	r2, [r5, #2648]
	addmi	r1, r2, #126
	adds	r2, r3, #63
	addmi	r2, r3, #126
	str	r3, [r5, #2652]
	mov	r0, r6
	mov	r3, r1, asr #6
	str	r3, [r5, #2640]
	mov	r3, r2, asr #6
	str	r3, [r5, #2644]
	bl	VP9_GetRefNum
	str	r0, [r4, #3392]
	ldr	r0, [r4, #3516]
	ldr	r2, [r5, #2652]
	ldr	r1, [r5, #2648]
	bl	VCTRL_GetFsSize
	mov	r1, r0
	str	r0, [r4, #3380]
	ldr	r0, [r4, #3516]
	bl	FSP_GetPhyFsNum
	ldr	r3, .L2298+8
	ldr	r1, [r4, #3516]
	ldr	r2, [r3, r1, asl #2]
	str	r0, [r4, #3384]
	ldr	r3, [r2, #1456]
	str	r3, [r4, #3388]
	ldr	r0, [r5, #2648]
	cmp	r0, #1920
	bls	.L2283
.L2216:
	add	r2, r4, #3392
	ldmia	r2, {r2, ip, lr}
	cmp	r2, ip
	movge	ip, r2
	cmp	r0, lr
	add	r3, ip, r3
	str	r3, [r4, #3388]
	beq	.L2284
.L2217:
	str	r2, [r4, #3396]
.L2219:
	mov	r0, r1
	mov	r1, #0
	bl	FSP_GetPhyFsNum
	ldr	r2, [r4, #3384]
	cmp	r0, r2
	str	r0, [fp, #-56]
	ble	.L2220
	rsb	r3, r2, r0
	cmp	r3, #0
	ble	.L2220
	mov	r8, #0
	b	.L2222
.L2285:
	ldr	r3, [fp, #-56]
	rsb	r1, r2, r3
	cmp	r1, r8
	ble	.L2220
.L2222:
	ldr	r1, [r4, #3380]
	add	r8, r8, #1
	ldr	r0, [r4, #3516]
	bl	FSP_RelsePhyFs
	ldr	r2, [r4, #3384]
	cmp	r0, #0
	beq	.L2285
.L2220:
	ldr	r3, [r4, #3388]
	cmp	r2, r3
	ble	.L2225
	rsb	r2, r3, r2
	cmp	r2, #0
	ble	.L2225
	mov	r8, #0
	b	.L2226
.L2286:
	ldr	r3, [r4, #3384]
	ldr	r2, [r4, #3388]
	rsb	r3, r2, r3
	cmp	r3, r8
	ble	.L2225
.L2226:
	mov	r1, #0
	ldr	r0, [r4, #3516]
	bl	FSP_RelsePhyFs
	add	r8, r8, #1
	cmp	r0, #0
	beq	.L2286
.L2225:
	mov	r1, #0
	ldr	r0, [r4, #3516]
	bl	FSP_GetPhyFsNum
	ldr	r3, [r4, #3388]
	add	r3, r3, #4
	cmp	r0, r3
	mov	r8, r0
	bgt	.L2287
	ldr	r1, [r4, #3380]
	ldr	r0, [r4, #3516]
	bl	FSP_GetPhyFsNum
	ldr	r2, [r4, #3392]
	ldr	r1, [r4, #3388]
	add	r3, r2, #1
	cmp	r0, r3
	rsb	r3, r8, r0
	addgt	ip, r2, #2
	addle	ip, r0, #1
	add	r3, r3, r1
	str	r0, [r4, #3384]
	cmp	ip, r3
	str	r0, [sp, #4]
	str	r2, [sp, #8]
	mov	r0, #2
	movlt	ip, r3
	str	r8, [sp]
	ldr	r1, .L2298+12
	str	ip, [r4, #3388]
	ldr	r3, [r5, #2652]
	ldr	r2, [r5, #2648]
	str	ip, [sp, #12]
	bl	dprint_vfmw
	ldr	r3, [r5, #2568]
	cmp	r3, #0
	beq	.L2229
	ldr	r2, [r4, #3400]
	ldr	r3, [r5, #2648]
	cmp	r2, r3
	beq	.L2288
.L2229:
	mov	r0, r6
	bl	VP9_ArrangeVHBMem
	ldr	r3, [r5, #2568]
	cmp	r3, #0
	beq	.L2289
.L2230:
	ldr	r3, [r6]
	ldr	r3, [r3, #8]
	str	r3, [r5, #2564]
	ldr	r3, [r7, #1000]
	ldr	r0, [r4, #3516]
	cmp	r3, #0
	ldreq	r3, [r5, #2648]
	streq	r3, [r4, #3400]
	ldreq	r3, [r5, #2652]
	streq	r3, [r4, #3404]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	bne	.L2290
	mov	r0, r9
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	bne	.L2291
	ldr	r3, [r7, #1000]
	cmp	r3, #0
	beq	.L2292
.L2234:
	mov	r0, r6
	bl	VP9_GetImageBuffer
	cmp	r0, #0
	bne	.L2293
	ldr	r3, [r4, #3416]
	mov	r0, r6
	ldr	r2, [r5, #2612]
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #2824]
	bl	VP9_Set_DecParam
	cmp	r0, #0
	bne	.L2294
	ldr	r3, [r7, #1000]
	cmp	r3, #1
	beq	.L2295
	ldr	r3, [r5, #2648]
	str	r3, [r4, #3408]
	ldr	r3, [r5, #2652]
	str	r3, [r4, #3412]
.L2239:
	mov	r0, r10
	bl	swap_frame_buffers
	ldr	r2, [r4, #3468]
	ldr	r0, [r4, #3472]
	cmp	r2, r0
	bcs	.L2240
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2240
	add	r3, r2, #1
	b	.L2241
.L2296:
	ldrb	r1, [r2]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2240
.L2241:
	cmp	r3, r0
	str	r3, [r4, #3468]
	mov	r2, r3
	add	r3, r3, #1
	bne	.L2296
.L2240:
	ldr	r3, [r4, #3424]
	cmp	r3, #1
	beq	.L2297
.L2242:
	mov	r5, #0
	str	r5, [r4, #3420]
	ldr	r0, [r7, #1000]
	cmp	r0, r5
	bne	.L2243
	ldr	r3, [r7, #996]
	str	r3, [r7, #1008]
.L2277:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2203:
	add	r5, r6, #270336
	ldr	r3, [r5, #2708]
	cmp	r3, #0
	beq	.L2205
	movw	r2, #10900
	mov	r3, #1
	movt	r2, 4
	add	r2, r6, r2
.L2206:
	ldr	r1, [r2, #4]!
	cmp	r1, #0
	beq	.L2205
	add	r3, r3, #1
	cmp	r3, #9
	bne	.L2206
	mvn	r3, #0
	str	r3, [r7, #972]
.L2244:
	ldr	r1, .L2298+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2277
.L2282:
	ldr	r2, [r5, #2560]
	cmp	r2, #7
	bgt	.L2212
	ldr	r1, .L2298+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2277
.L2283:
	ldr	ip, [r5, #2652]
	cmp	ip, #1088
	bhi	.L2216
	ldr	ip, [r2, #36]
	cmp	ip, #24
	beq	.L2216
	add	r2, r2, #294912
	ldr	r2, [r2, #1212]
	cmp	r2, #0
	addeq	r3, r3, #4
	b	.L2216
.L2284:
	ldr	r3, [r5, #2652]
	ldr	r0, [r4, #3404]
	cmp	r0, r3
	streq	ip, [r4, #3396]
	bne	.L2217
	b	.L2219
.L2291:
	mov	r0, r9
	bl	BsGet
	ldr	r3, [r7, #1000]
	cmp	r3, #0
	bne	.L2234
.L2292:
	ldr	r3, [r7, #1776]
	mov	r0, r6
	ldr	r2, [r7, #1768]
	add	r3, r3, #7
	ldr	r1, [fp, #-60]
	mov	r3, r3, lsr #3
	add	r1, r1, r3
	rsb	r2, r3, r2
	bl	Vp9_DecodeTiles
	b	.L2234
.L2295:
	ldr	r0, [r7, #972]
	movw	r3, #10900
	movt	r3, 4
	add	r3, r6, r3
	ldr	r1, [r7, #1004]
	ldr	r2, [r3, r0, asl #2]
	cmp	r2, #0
	subgt	r2, r2, #1
	strgt	r2, [r3, r0, asl #2]
	str	r1, [r7, #972]
	ldr	r2, [r3, r1, asl #2]
	add	r2, r2, #1
	str	r2, [r3, r1, asl #2]
	b	.L2239
.L2288:
	ldr	r2, [r4, #3404]
	ldr	r3, [r5, #2652]
	cmp	r2, r3
	bne	.L2229
	ldr	r2, [r4, #3384]
	ldr	r3, [r4, #3388]
	cmp	r2, r3
	bge	.L2230
	b	.L2229
.L2205:
	add	r5, r5, r3, lsl #2
	cmp	r3, #0
	mov	r2, #1
	str	r2, [r5, #2708]
	str	r3, [r7, #972]
	bge	.L2204
	b	.L2244
.L2243:
	mov	r0, r6
	mov	r3, r5
	mov	r2, r5
	mov	r1, r5
	bl	VP9DEC_VDMPostProc
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2297:
	ldr	r1, [r4, #3464]
	add	r3, r1, #73728
	add	r1, r1, #1
	add	r3, r3, #856
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r1, [r4, #3464]
	add	r2, r2, r3
	str	r2, [r4, #3468]
	b	.L2242
.L2213:
	ldr	r3, .L2298+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2215
	mov	r3, #0
	ldr	r0, [r4, #3516]
	mov	r2, r3
	mov	r1, #102
	blx	r5
	ldr	r2, [r7, #1024]
.L2215:
	ldr	r3, [r7, #1028]
	mov	r0, #1
	ldr	r1, .L2298+24
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2287:
	mvn	r0, #1
	b	.L2277
.L2290:
	movw	r3, #4072
	ldr	r2, .L2298+28
	ldr	r1, .L2298+32
	mov	r0, #23
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2277
.L2245:
	mvn	r0, #0
	b	.L2277
.L2293:
	ldr	r1, .L2298+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2277
.L2289:
	ldr	r1, .L2298+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L2277
.L2294:
	ldr	r1, .L2298+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2277
.L2299:
	.align	2
.L2298:
	.word	.LC43
	.word	g_event_report
	.word	s_pstVfmwChan
	.word	.LC46
	.word	.LC42
	.word	.LC44
	.word	.LC45
	.word	.LANCHOR0+892
	.word	.LC48
	.word	.LC49
	.word	.LC47
	.word	.LC50
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
	beq	.L2310
	ldr	r0, [r1]
	add	r8, r5, #270336
	add	r4, r5, #294912
	str	r0, [r8, #2552]
	ldr	r3, [r1, #12]
	str	r3, [r8, #2556]
	ldr	r1, [r1, #16]
	str	r1, [r8, #2560]
	ldr	r6, [r4, #3424]
	cmp	r6, #0
	beq	.L2319
	ldr	r2, [r4, #3476]
	ldr	r7, [r4, #3468]
.L2306:
	cmp	r2, #0
	beq	.L2305
	ldrb	r0, [r7]	@ zero_extendqisi2
	and	r1, r0, #7
	ubfx	ip, r0, #3, #2
	add	r3, r1, #1
	and	r1, r0, #224
	cmp	r1, #192
	mla	r3, ip, r3, r3
	bne	.L2305
	add	r1, r7, r3
	add	r3, r3, #2
	cmp	r3, r2
	bhi	.L2305
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, r0
	bne	.L2305
	ldr	r1, [r4, #3472]
	add	r7, r7, r3
	rsb	r2, r3, r2
	str	r7, [r4, #3468]
	cmp	r7, r1
	str	r2, [r4, #3476]
	bcc	.L2306
.L2305:
	cmp	r6, #1
	movw	r0, #14040
	mov	r1, r7
	movt	r0, 4
	ldreq	r3, [r4, #3464]
	add	r0, r5, r0
	addeq	r3, r3, #73728
	addeq	r3, r3, #856
	addeq	r3, r5, r3, lsl #2
	ldreq	r2, [r3, #4]
	bl	BsInit
	mov	r1, r7
	mov	r0, r5
	bl	VP9DEC_DecodeFame
	cmn	r0, #2
	mov	r6, r0
	moveq	r3, #1
	streq	r3, [r4, #3420]
	beq	.L2301
	cmp	r6, #0
	moveq	r0, r6
	bne	.L2320
.L2301:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2320:
	mov	r0, r5
	bl	VP9_FreeCurFb
	mov	r3, #0
	mov	r1, r5
	str	r3, [r4, #3424]
	mov	r0, #17
	bl	ReleasePacket
	ldr	r1, .L2322
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2319:
	sub	r3, fp, #72
	sub	r2, fp, #68
	bl	Vp9_ParseSuperFrameIndex
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	bne	.L2321
.L2303:
	ldr	r7, [r8, #2552]
	ldr	r6, [r4, #3424]
	str	r7, [r4, #3468]
	ldr	r2, [r8, #2560]
	add	r3, r7, r2
	str	r3, [r4, #3472]
	str	r2, [r4, #3476]
	b	.L2306
.L2321:
	ldr	r2, .L2322+4
	movw	r0, #36196
	str	r3, [r4, #3460]
	sub	r1, fp, #68
	str	r6, [r4, #3464]
	movt	r0, 4
	ldr	r3, [r2, #52]
	add	r0, r5, r0
	mov	r2, #1
	str	r2, [r4, #3424]
	mov	r2, #32
	blx	r3
	b	.L2303
.L2310:
	mvn	r0, #0
	b	.L2301
.L2323:
	.align	2
.L2322:
	.word	.LC51
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP9DEC_DecodePacket, .-VP9DEC_DecodePacket
	.global	g_CfgVp9FrmNum
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
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
	.type	vp9_inter_mode_tree, %object
	.size	vp9_inter_mode_tree, 6
vp9_inter_mode_tree:
	.byte	-2
	.byte	2
	.byte	0
	.byte	4
	.byte	-1
	.byte	-3
	.space	2
	.type	vp9_intra_mode_tree, %object
	.size	vp9_intra_mode_tree, 18
vp9_intra_mode_tree:
	.byte	0
	.byte	2
	.byte	-9
	.byte	4
	.byte	-1
	.byte	6
	.byte	8
	.byte	12
	.byte	-2
	.byte	10
	.byte	-4
	.byte	-5
	.byte	-3
	.byte	14
	.byte	-8
	.byte	16
	.byte	-6
	.byte	-7
	.space	2
	.type	vp9_partition_tree, %object
	.size	vp9_partition_tree, 6
vp9_partition_tree:
	.byte	0
	.byte	2
	.byte	-1
	.byte	4
	.byte	-2
	.byte	-3
	.space	2
	.type	vp9_switchable_interp_tree, %object
	.size	vp9_switchable_interp_tree, 4
vp9_switchable_interp_tree:
	.byte	0
	.byte	2
	.byte	-1
	.byte	-2
.LC0:
	.byte	0
	.byte	2
	.byte	-1
	.byte	4
	.byte	-2
	.byte	-3
	.space	2
.LC1:
	.byte	0
	.byte	2
	.byte	-1
	.byte	4
	.byte	6
	.byte	8
	.byte	-2
	.byte	-3
	.byte	10
	.byte	12
	.byte	-4
	.byte	-5
	.byte	-6
	.byte	14
	.byte	16
	.byte	18
	.byte	-7
	.byte	-8
	.byte	-9
	.byte	-10
	.type	__func__.14069, %object
	.size	__func__.14069, 19
__func__.14069:
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
	.type	__func__.14247, %object
	.size	__func__.14247, 16
__func__.14247:
	.ascii	"VP9_Set_Segdata\000"
.LC2:
	.word	1
	.word	0
	.word	2
	.word	3
	.type	__FUNCTION__.14323, %object
	.size	__FUNCTION__.14323, 33
__FUNCTION__.14323:
	.ascii	"VP9_get_fixed_point_scale_factor\000"
	.space	3
	.type	__FUNCTION__.14352, %object
	.size	__FUNCTION__.14352, 35
__FUNCTION__.14352:
	.ascii	"Vp9_ReadBitDepthColorSpaceSampling\000"
	.space	1
	.type	__FUNCTION__.14382, %object
	.size	__FUNCTION__.14382, 25
__FUNCTION__.14382:
	.ascii	"Read_UnCompressed_Header\000"
	.space	3
	.type	vp9_default_tx_probs, %object
	.size	vp9_default_tx_probs, 12
vp9_default_tx_probs:
	.byte	3
	.byte	-120
	.byte	37
	.byte	5
	.byte	52
	.byte	13
	.byte	20
	.byte	-104
	.byte	15
	.byte	101
	.byte	100
	.byte	66
	.type	vp9_default_nmv_context, %object
	.size	vp9_default_nmv_context, 69
vp9_default_nmv_context:
	.byte	32
	.byte	64
	.byte	96
	.byte	-128
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
	.byte	64
	.byte	96
	.byte	64
	.byte	-96
	.byte	-128
	.byte	-128
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
	.byte	-128
	.byte	-128
	.byte	64
	.byte	96
	.byte	112
	.byte	64
	.byte	64
	.byte	96
	.byte	64
	.byte	-96
	.byte	-128
	.space	3
	.type	__func__.14602, %object
	.size	__func__.14602, 20
__func__.14602:
	.ascii	"Vp9_DecodeTilesCtrl\000"
	.type	__func__.14462, %object
	.size	__func__.14462, 18
__func__.14462:
	.ascii	"VP9DEC_DecodeFame\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	vp9_default_coef_probs_4x4, %object
	.size	vp9_default_coef_probs_4x4, 432
vp9_default_coef_probs_4x4:
	.byte	-61
	.byte	29
	.byte	-73
	.byte	84
	.byte	49
	.byte	-120
	.byte	8
	.byte	42
	.byte	71
	.space	9
	.byte	31
	.byte	107
	.byte	-87
	.byte	35
	.byte	99
	.byte	-97
	.byte	17
	.byte	82
	.byte	-116
	.byte	8
	.byte	66
	.byte	114
	.byte	2
	.byte	44
	.byte	76
	.byte	1
	.byte	19
	.byte	32
	.byte	40
	.byte	-124
	.byte	-55
	.byte	29
	.byte	114
	.byte	-69
	.byte	13
	.byte	91
	.byte	-99
	.byte	7
	.byte	75
	.byte	127
	.byte	3
	.byte	58
	.byte	95
	.byte	1
	.byte	28
	.byte	47
	.byte	69
	.byte	-114
	.byte	-35
	.byte	42
	.byte	122
	.byte	-55
	.byte	15
	.byte	91
	.byte	-97
	.byte	6
	.byte	67
	.byte	121
	.byte	1
	.byte	42
	.byte	77
	.byte	1
	.byte	17
	.byte	31
	.byte	102
	.byte	-108
	.byte	-28
	.byte	67
	.byte	117
	.byte	-52
	.byte	17
	.byte	82
	.byte	-102
	.byte	6
	.byte	59
	.byte	114
	.byte	2
	.byte	39
	.byte	75
	.byte	1
	.byte	15
	.byte	29
	.byte	-100
	.byte	57
	.byte	-23
	.byte	119
	.byte	57
	.byte	-44
	.byte	58
	.byte	48
	.byte	-93
	.byte	29
	.byte	40
	.byte	124
	.byte	12
	.byte	30
	.byte	81
	.byte	3
	.byte	12
	.byte	31
	.byte	-65
	.byte	107
	.byte	-30
	.byte	124
	.byte	117
	.byte	-52
	.byte	25
	.byte	99
	.byte	-101
	.space	9
	.byte	29
	.byte	-108
	.byte	-46
	.byte	37
	.byte	126
	.byte	-62
	.byte	8
	.byte	93
	.byte	-99
	.byte	2
	.byte	68
	.byte	118
	.byte	1
	.byte	39
	.byte	69
	.byte	1
	.byte	17
	.byte	33
	.byte	41
	.byte	-105
	.byte	-43
	.byte	27
	.byte	123
	.byte	-63
	.byte	3
	.byte	82
	.byte	-112
	.byte	1
	.byte	58
	.byte	105
	.byte	1
	.byte	32
	.byte	60
	.byte	1
	.byte	13
	.byte	26
	.byte	59
	.byte	-97
	.byte	-36
	.byte	23
	.byte	126
	.byte	-58
	.byte	4
	.byte	88
	.byte	-105
	.byte	1
	.byte	66
	.byte	114
	.byte	1
	.byte	38
	.byte	71
	.byte	1
	.byte	18
	.byte	34
	.byte	114
	.byte	-120
	.byte	-24
	.byte	51
	.byte	114
	.byte	-49
	.byte	11
	.byte	83
	.byte	-101
	.byte	3
	.byte	56
	.byte	105
	.byte	1
	.byte	33
	.byte	65
	.byte	1
	.byte	17
	.byte	34
	.byte	-107
	.byte	65
	.byte	-22
	.byte	121
	.byte	57
	.byte	-41
	.byte	61
	.byte	49
	.byte	-90
	.byte	28
	.byte	36
	.byte	114
	.byte	12
	.byte	25
	.byte	76
	.byte	3
	.byte	16
	.byte	42
	.byte	-42
	.byte	49
	.byte	-36
	.byte	-124
	.byte	63
	.byte	-68
	.byte	42
	.byte	65
	.byte	-119
	.space	9
	.byte	85
	.byte	-119
	.byte	-35
	.byte	104
	.byte	-125
	.byte	-40
	.byte	49
	.byte	111
	.byte	-64
	.byte	21
	.byte	87
	.byte	-101
	.byte	2
	.byte	49
	.byte	87
	.byte	1
	.byte	16
	.byte	28
	.byte	89
	.byte	-93
	.byte	-26
	.byte	90
	.byte	-119
	.byte	-36
	.byte	29
	.byte	100
	.byte	-73
	.byte	10
	.byte	70
	.byte	-121
	.byte	2
	.byte	42
	.byte	81
	.byte	1
	.byte	17
	.byte	33
	.byte	108
	.byte	-89
	.byte	-19
	.byte	55
	.byte	-123
	.byte	-34
	.byte	15
	.byte	97
	.byte	-77
	.byte	4
	.byte	72
	.byte	-121
	.byte	1
	.byte	45
	.byte	85
	.byte	1
	.byte	19
	.byte	38
	.byte	124
	.byte	-110
	.byte	-16
	.byte	66
	.byte	124
	.byte	-32
	.byte	17
	.byte	88
	.byte	-81
	.byte	4
	.byte	58
	.byte	122
	.byte	1
	.byte	36
	.byte	75
	.byte	1
	.byte	18
	.byte	37
	.byte	-115
	.byte	79
	.byte	-15
	.byte	126
	.byte	70
	.byte	-29
	.byte	66
	.byte	58
	.byte	-74
	.byte	30
	.byte	44
	.byte	-120
	.byte	12
	.byte	34
	.byte	96
	.byte	2
	.byte	20
	.byte	47
	.byte	-27
	.byte	99
	.byte	-7
	.byte	-113
	.byte	111
	.byte	-21
	.byte	46
	.byte	109
	.byte	-64
	.space	9
	.byte	82
	.byte	-98
	.byte	-20
	.byte	94
	.byte	-110
	.byte	-32
	.byte	25
	.byte	117
	.byte	-65
	.byte	9
	.byte	87
	.byte	-107
	.byte	3
	.byte	56
	.byte	99
	.byte	1
	.byte	33
	.byte	57
	.byte	83
	.byte	-89
	.byte	-19
	.byte	68
	.byte	-111
	.byte	-34
	.byte	10
	.byte	103
	.byte	-79
	.byte	2
	.byte	72
	.byte	-125
	.byte	1
	.byte	41
	.byte	79
	.byte	1
	.byte	20
	.byte	39
	.byte	99
	.byte	-89
	.byte	-17
	.byte	47
	.byte	-115
	.byte	-32
	.byte	10
	.byte	104
	.byte	-78
	.byte	2
	.byte	73
	.byte	-123
	.byte	1
	.byte	44
	.byte	85
	.byte	1
	.byte	22
	.byte	47
	.byte	127
	.byte	-111
	.byte	-13
	.byte	71
	.byte	-127
	.byte	-28
	.byte	17
	.byte	93
	.byte	-79
	.byte	3
	.byte	61
	.byte	124
	.byte	1
	.byte	41
	.byte	84
	.byte	1
	.byte	21
	.byte	52
	.byte	-99
	.byte	78
	.byte	-12
	.byte	-116
	.byte	72
	.byte	-25
	.byte	69
	.byte	58
	.byte	-72
	.byte	31
	.byte	44
	.byte	-119
	.byte	14
	.byte	38
	.byte	105
	.byte	8
	.byte	23
	.byte	61
	.type	vp9_default_coef_probs_8x8, %object
	.size	vp9_default_coef_probs_8x8, 432
vp9_default_coef_probs_8x8:
	.byte	125
	.byte	34
	.byte	-69
	.byte	52
	.byte	41
	.byte	-123
	.byte	6
	.byte	31
	.byte	56
	.space	9
	.byte	37
	.byte	109
	.byte	-103
	.byte	51
	.byte	102
	.byte	-109
	.byte	23
	.byte	87
	.byte	-128
	.byte	8
	.byte	67
	.byte	101
	.byte	1
	.byte	41
	.byte	63
	.byte	1
	.byte	19
	.byte	29
	.byte	31
	.byte	-102
	.byte	-71
	.byte	17
	.byte	127
	.byte	-81
	.byte	6
	.byte	96
	.byte	-111
	.byte	2
	.byte	73
	.byte	114
	.byte	1
	.byte	51
	.byte	82
	.byte	1
	.byte	28
	.byte	45
	.byte	23
	.byte	-93
	.byte	-56
	.byte	10
	.byte	-125
	.byte	-71
	.byte	2
	.byte	93
	.byte	-108
	.byte	1
	.byte	67
	.byte	111
	.byte	1
	.byte	41
	.byte	69
	.byte	1
	.byte	14
	.byte	24
	.byte	29
	.byte	-80
	.byte	-39
	.byte	12
	.byte	-111
	.byte	-55
	.byte	3
	.byte	101
	.byte	-100
	.byte	1
	.byte	69
	.byte	111
	.byte	1
	.byte	39
	.byte	63
	.byte	1
	.byte	14
	.byte	23
	.byte	57
	.byte	-64
	.byte	-23
	.byte	25
	.byte	-102
	.byte	-41
	.byte	6
	.byte	109
	.byte	-89
	.byte	3
	.byte	78
	.byte	118
	.byte	1
	.byte	48
	.byte	69
	.byte	1
	.byte	21
	.byte	29
	.byte	-54
	.byte	105
	.byte	-11
	.byte	108
	.byte	106
	.byte	-40
	.byte	18
	.byte	90
	.byte	-112
	.space	9
	.byte	33
	.byte	-84
	.byte	-37
	.byte	64
	.byte	-107
	.byte	-50
	.byte	14
	.byte	117
	.byte	-79
	.byte	5
	.byte	90
	.byte	-115
	.byte	2
	.byte	61
	.byte	95
	.byte	1
	.byte	37
	.byte	57
	.byte	33
	.byte	-77
	.byte	-36
	.byte	11
	.byte	-116
	.byte	-58
	.byte	1
	.byte	89
	.byte	-108
	.byte	1
	.byte	60
	.byte	104
	.byte	1
	.byte	33
	.byte	57
	.byte	1
	.byte	12
	.byte	21
	.byte	30
	.byte	-75
	.byte	-35
	.byte	8
	.byte	-115
	.byte	-58
	.byte	1
	.byte	87
	.byte	-111
	.byte	1
	.byte	58
	.byte	100
	.byte	1
	.byte	31
	.byte	55
	.byte	1
	.byte	12
	.byte	20
	.byte	32
	.byte	-70
	.byte	-32
	.byte	7
	.byte	-114
	.byte	-58
	.byte	1
	.byte	86
	.byte	-113
	.byte	1
	.byte	58
	.byte	100
	.byte	1
	.byte	31
	.byte	55
	.byte	1
	.byte	12
	.byte	22
	.byte	57
	.byte	-64
	.byte	-29
	.byte	20
	.byte	-113
	.byte	-52
	.byte	3
	.byte	96
	.byte	-102
	.byte	1
	.byte	68
	.byte	112
	.byte	1
	.byte	42
	.byte	69
	.byte	1
	.byte	19
	.byte	32
	.byte	-44
	.byte	35
	.byte	-41
	.byte	113
	.byte	47
	.byte	-87
	.byte	29
	.byte	48
	.byte	105
	.space	9
	.byte	74
	.byte	-127
	.byte	-53
	.byte	106
	.byte	120
	.byte	-53
	.byte	49
	.byte	107
	.byte	-78
	.byte	19
	.byte	84
	.byte	-112
	.byte	4
	.byte	50
	.byte	84
	.byte	1
	.byte	15
	.byte	25
	.byte	71
	.byte	-84
	.byte	-39
	.byte	44
	.byte	-115
	.byte	-47
	.byte	15
	.byte	102
	.byte	-83
	.byte	6
	.byte	76
	.byte	-123
	.byte	2
	.byte	51
	.byte	89
	.byte	1
	.byte	24
	.byte	42
	.byte	64
	.byte	-71
	.byte	-25
	.byte	31
	.byte	-108
	.byte	-40
	.byte	8
	.byte	103
	.byte	-81
	.byte	3
	.byte	74
	.byte	-125
	.byte	1
	.byte	46
	.byte	81
	.byte	1
	.byte	18
	.byte	30
	.byte	65
	.byte	-60
	.byte	-21
	.byte	25
	.byte	-99
	.byte	-35
	.byte	5
	.byte	105
	.byte	-82
	.byte	1
	.byte	67
	.byte	120
	.byte	1
	.byte	38
	.byte	69
	.byte	1
	.byte	15
	.byte	30
	.byte	65
	.byte	-52
	.byte	-18
	.byte	30
	.byte	-100
	.byte	-32
	.byte	7
	.byte	107
	.byte	-79
	.byte	2
	.byte	70
	.byte	124
	.byte	1
	.byte	42
	.byte	73
	.byte	1
	.byte	18
	.byte	34
	.byte	-31
	.byte	86
	.byte	-5
	.byte	-112
	.byte	104
	.byte	-21
	.byte	42
	.byte	99
	.byte	-75
	.space	9
	.byte	85
	.byte	-81
	.byte	-17
	.byte	112
	.byte	-91
	.byte	-27
	.byte	29
	.byte	-120
	.byte	-56
	.byte	12
	.byte	103
	.byte	-94
	.byte	6
	.byte	77
	.byte	123
	.byte	2
	.byte	53
	.byte	84
	.byte	75
	.byte	-73
	.byte	-17
	.byte	30
	.byte	-101
	.byte	-35
	.byte	3
	.byte	106
	.byte	-85
	.byte	1
	.byte	74
	.byte	-128
	.byte	1
	.byte	44
	.byte	76
	.byte	1
	.byte	17
	.byte	28
	.byte	73
	.byte	-71
	.byte	-16
	.byte	27
	.byte	-97
	.byte	-34
	.byte	2
	.byte	107
	.byte	-84
	.byte	1
	.byte	75
	.byte	127
	.byte	1
	.byte	42
	.byte	73
	.byte	1
	.byte	17
	.byte	29
	.byte	62
	.byte	-66
	.byte	-18
	.byte	21
	.byte	-97
	.byte	-34
	.byte	2
	.byte	107
	.byte	-84
	.byte	1
	.byte	72
	.byte	122
	.byte	1
	.byte	40
	.byte	71
	.byte	1
	.byte	18
	.byte	32
	.byte	61
	.byte	-57
	.byte	-16
	.byte	27
	.byte	-95
	.byte	-30
	.byte	4
	.byte	113
	.byte	-76
	.byte	1
	.byte	76
	.byte	-127
	.byte	1
	.byte	46
	.byte	80
	.byte	1
	.byte	23
	.byte	41
	.type	vp9_default_coef_probs_16x16, %object
	.size	vp9_default_coef_probs_16x16, 432
vp9_default_coef_probs_16x16:
	.byte	7
	.byte	27
	.byte	-103
	.byte	5
	.byte	30
	.byte	95
	.byte	1
	.byte	16
	.byte	30
	.space	9
	.byte	50
	.byte	75
	.byte	127
	.byte	57
	.byte	75
	.byte	124
	.byte	27
	.byte	67
	.byte	108
	.byte	10
	.byte	54
	.byte	86
	.byte	1
	.byte	33
	.byte	52
	.byte	1
	.byte	12
	.byte	18
	.byte	43
	.byte	125
	.byte	-105
	.byte	26
	.byte	108
	.byte	-108
	.byte	7
	.byte	83
	.byte	122
	.byte	2
	.byte	59
	.byte	89
	.byte	1
	.byte	38
	.byte	60
	.byte	1
	.byte	17
	.byte	27
	.byte	23
	.byte	-112
	.byte	-93
	.byte	13
	.byte	112
	.byte	-102
	.byte	2
	.byte	75
	.byte	117
	.byte	1
	.byte	50
	.byte	81
	.byte	1
	.byte	31
	.byte	51
	.byte	1
	.byte	14
	.byte	23
	.byte	18
	.byte	-94
	.byte	-71
	.byte	6
	.byte	123
	.byte	-85
	.byte	1
	.byte	78
	.byte	125
	.byte	1
	.byte	51
	.byte	86
	.byte	1
	.byte	31
	.byte	54
	.byte	1
	.byte	14
	.byte	23
	.byte	15
	.byte	-57
	.byte	-29
	.byte	3
	.byte	-106
	.byte	-52
	.byte	1
	.byte	91
	.byte	-110
	.byte	1
	.byte	55
	.byte	95
	.byte	1
	.byte	30
	.byte	53
	.byte	1
	.byte	11
	.byte	20
	.byte	19
	.byte	55
	.byte	-16
	.byte	19
	.byte	59
	.byte	-60
	.byte	3
	.byte	52
	.byte	105
	.space	9
	.byte	41
	.byte	-90
	.byte	-49
	.byte	104
	.byte	-103
	.byte	-57
	.byte	31
	.byte	123
	.byte	-75
	.byte	14
	.byte	101
	.byte	-104
	.byte	5
	.byte	72
	.byte	106
	.byte	1
	.byte	36
	.byte	52
	.byte	35
	.byte	-80
	.byte	-45
	.byte	12
	.byte	-125
	.byte	-66
	.byte	2
	.byte	88
	.byte	-112
	.byte	1
	.byte	60
	.byte	101
	.byte	1
	.byte	36
	.byte	60
	.byte	1
	.byte	16
	.byte	28
	.byte	28
	.byte	-73
	.byte	-43
	.byte	8
	.byte	-122
	.byte	-65
	.byte	1
	.byte	86
	.byte	-114
	.byte	1
	.byte	56
	.byte	96
	.byte	1
	.byte	30
	.byte	53
	.byte	1
	.byte	12
	.byte	20
	.byte	20
	.byte	-66
	.byte	-41
	.byte	4
	.byte	-121
	.byte	-64
	.byte	1
	.byte	84
	.byte	-117
	.byte	1
	.byte	53
	.byte	91
	.byte	1
	.byte	28
	.byte	49
	.byte	1
	.byte	11
	.byte	20
	.byte	13
	.byte	-60
	.byte	-40
	.byte	2
	.byte	-119
	.byte	-64
	.byte	1
	.byte	86
	.byte	-113
	.byte	1
	.byte	57
	.byte	99
	.byte	1
	.byte	32
	.byte	56
	.byte	1
	.byte	13
	.byte	24
	.byte	-45
	.byte	29
	.byte	-39
	.byte	96
	.byte	47
	.byte	-100
	.byte	22
	.byte	43
	.byte	87
	.space	9
	.byte	78
	.byte	120
	.byte	-63
	.byte	111
	.byte	116
	.byte	-70
	.byte	46
	.byte	102
	.byte	-92
	.byte	15
	.byte	80
	.byte	-128
	.byte	2
	.byte	49
	.byte	76
	.byte	1
	.byte	18
	.byte	28
	.byte	71
	.byte	-95
	.byte	-53
	.byte	42
	.byte	-124
	.byte	-64
	.byte	10
	.byte	98
	.byte	-106
	.byte	3
	.byte	69
	.byte	109
	.byte	1
	.byte	44
	.byte	70
	.byte	1
	.byte	18
	.byte	29
	.byte	57
	.byte	-70
	.byte	-45
	.byte	30
	.byte	-116
	.byte	-60
	.byte	4
	.byte	93
	.byte	-110
	.byte	1
	.byte	62
	.byte	102
	.byte	1
	.byte	38
	.byte	65
	.byte	1
	.byte	16
	.byte	27
	.byte	47
	.byte	-57
	.byte	-39
	.byte	14
	.byte	-111
	.byte	-60
	.byte	1
	.byte	88
	.byte	-114
	.byte	1
	.byte	57
	.byte	98
	.byte	1
	.byte	36
	.byte	62
	.byte	1
	.byte	15
	.byte	26
	.byte	26
	.byte	-37
	.byte	-27
	.byte	5
	.byte	-101
	.byte	-49
	.byte	1
	.byte	94
	.byte	-105
	.byte	1
	.byte	60
	.byte	104
	.byte	1
	.byte	36
	.byte	62
	.byte	1
	.byte	16
	.byte	28
	.byte	-23
	.byte	29
	.byte	-8
	.byte	-110
	.byte	47
	.byte	-36
	.byte	43
	.byte	52
	.byte	-116
	.space	9
	.byte	100
	.byte	-93
	.byte	-24
	.byte	-77
	.byte	-95
	.byte	-34
	.byte	63
	.byte	-114
	.byte	-52
	.byte	37
	.byte	113
	.byte	-82
	.byte	26
	.byte	89
	.byte	-119
	.byte	18
	.byte	68
	.byte	97
	.byte	85
	.byte	-75
	.byte	-26
	.byte	32
	.byte	-110
	.byte	-47
	.byte	7
	.byte	100
	.byte	-92
	.byte	3
	.byte	71
	.byte	121
	.byte	1
	.byte	45
	.byte	77
	.byte	1
	.byte	18
	.byte	30
	.byte	65
	.byte	-69
	.byte	-26
	.byte	20
	.byte	-108
	.byte	-49
	.byte	2
	.byte	97
	.byte	-97
	.byte	1
	.byte	68
	.byte	116
	.byte	1
	.byte	40
	.byte	70
	.byte	1
	.byte	14
	.byte	29
	.byte	40
	.byte	-62
	.byte	-29
	.byte	8
	.byte	-109
	.byte	-52
	.byte	1
	.byte	94
	.byte	-101
	.byte	1
	.byte	65
	.byte	112
	.byte	1
	.byte	39
	.byte	66
	.byte	1
	.byte	14
	.byte	26
	.byte	16
	.byte	-48
	.byte	-28
	.byte	3
	.byte	-105
	.byte	-49
	.byte	1
	.byte	98
	.byte	-96
	.byte	1
	.byte	67
	.byte	117
	.byte	1
	.byte	41
	.byte	74
	.byte	1
	.byte	17
	.byte	31
	.type	vp9_default_coef_probs_32x32, %object
	.size	vp9_default_coef_probs_32x32, 432
vp9_default_coef_probs_32x32:
	.byte	17
	.byte	38
	.byte	-116
	.byte	7
	.byte	34
	.byte	80
	.byte	1
	.byte	17
	.byte	29
	.space	9
	.byte	37
	.byte	75
	.byte	-128
	.byte	41
	.byte	76
	.byte	-128
	.byte	26
	.byte	66
	.byte	116
	.byte	12
	.byte	52
	.byte	94
	.byte	2
	.byte	32
	.byte	55
	.byte	1
	.byte	10
	.byte	16
	.byte	50
	.byte	127
	.byte	-102
	.byte	37
	.byte	109
	.byte	-104
	.byte	16
	.byte	82
	.byte	121
	.byte	5
	.byte	59
	.byte	85
	.byte	1
	.byte	35
	.byte	54
	.byte	1
	.byte	13
	.byte	20
	.byte	40
	.byte	-114
	.byte	-89
	.byte	17
	.byte	110
	.byte	-99
	.byte	2
	.byte	71
	.byte	112
	.byte	1
	.byte	44
	.byte	72
	.byte	1
	.byte	27
	.byte	45
	.byte	1
	.byte	11
	.byte	17
	.byte	30
	.byte	-81
	.byte	-68
	.byte	9
	.byte	124
	.byte	-87
	.byte	1
	.byte	74
	.byte	116
	.byte	1
	.byte	48
	.byte	78
	.byte	1
	.byte	30
	.byte	49
	.byte	1
	.byte	11
	.byte	18
	.byte	10
	.byte	-34
	.byte	-33
	.byte	2
	.byte	-106
	.byte	-62
	.byte	1
	.byte	83
	.byte	-128
	.byte	1
	.byte	48
	.byte	79
	.byte	1
	.byte	27
	.byte	45
	.byte	1
	.byte	11
	.byte	17
	.byte	36
	.byte	41
	.byte	-21
	.byte	29
	.byte	36
	.byte	-63
	.byte	10
	.byte	27
	.byte	111
	.space	9
	.byte	85
	.byte	-91
	.byte	-34
	.byte	-79
	.byte	-94
	.byte	-41
	.byte	110
	.byte	-121
	.byte	-61
	.byte	57
	.byte	113
	.byte	-88
	.byte	23
	.byte	83
	.byte	120
	.byte	10
	.byte	49
	.byte	61
	.byte	85
	.byte	-66
	.byte	-33
	.byte	36
	.byte	-117
	.byte	-56
	.byte	5
	.byte	90
	.byte	-110
	.byte	1
	.byte	60
	.byte	103
	.byte	1
	.byte	38
	.byte	65
	.byte	1
	.byte	18
	.byte	30
	.byte	72
	.byte	-54
	.byte	-33
	.byte	23
	.byte	-115
	.byte	-57
	.byte	2
	.byte	86
	.byte	-116
	.byte	1
	.byte	56
	.byte	97
	.byte	1
	.byte	36
	.byte	61
	.byte	1
	.byte	16
	.byte	27
	.byte	55
	.byte	-38
	.byte	-31
	.byte	13
	.byte	-111
	.byte	-56
	.byte	1
	.byte	86
	.byte	-115
	.byte	1
	.byte	57
	.byte	99
	.byte	1
	.byte	35
	.byte	61
	.byte	1
	.byte	13
	.byte	22
	.byte	15
	.byte	-21
	.byte	-44
	.byte	1
	.byte	-124
	.byte	-72
	.byte	1
	.byte	84
	.byte	-117
	.byte	1
	.byte	57
	.byte	97
	.byte	1
	.byte	34
	.byte	56
	.byte	1
	.byte	14
	.byte	23
	.byte	-75
	.byte	21
	.byte	-55
	.byte	61
	.byte	37
	.byte	123
	.byte	10
	.byte	38
	.byte	71
	.space	9
	.byte	47
	.byte	106
	.byte	-84
	.byte	95
	.byte	104
	.byte	-83
	.byte	42
	.byte	93
	.byte	-97
	.byte	18
	.byte	77
	.byte	-125
	.byte	4
	.byte	50
	.byte	81
	.byte	1
	.byte	17
	.byte	23
	.byte	62
	.byte	-109
	.byte	-57
	.byte	44
	.byte	-126
	.byte	-67
	.byte	28
	.byte	102
	.byte	-102
	.byte	18
	.byte	75
	.byte	115
	.byte	2
	.byte	44
	.byte	65
	.byte	1
	.byte	12
	.byte	19
	.byte	55
	.byte	-103
	.byte	-46
	.byte	24
	.byte	-126
	.byte	-62
	.byte	3
	.byte	93
	.byte	-110
	.byte	1
	.byte	61
	.byte	97
	.byte	1
	.byte	31
	.byte	50
	.byte	1
	.byte	10
	.byte	16
	.byte	49
	.byte	-70
	.byte	-33
	.byte	17
	.byte	-108
	.byte	-52
	.byte	1
	.byte	96
	.byte	-114
	.byte	1
	.byte	53
	.byte	83
	.byte	1
	.byte	26
	.byte	44
	.byte	1
	.byte	11
	.byte	17
	.byte	13
	.byte	-39
	.byte	-44
	.byte	2
	.byte	-120
	.byte	-76
	.byte	1
	.byte	78
	.byte	124
	.byte	1
	.byte	50
	.byte	83
	.byte	1
	.byte	29
	.byte	49
	.byte	1
	.byte	14
	.byte	23
	.byte	-59
	.byte	13
	.byte	-9
	.byte	82
	.byte	17
	.byte	-34
	.byte	25
	.byte	17
	.byte	-94
	.space	9
	.byte	126
	.byte	-70
	.byte	-9
	.byte	-22
	.byte	-65
	.byte	-13
	.byte	-80
	.byte	-79
	.byte	-22
	.byte	104
	.byte	-98
	.byte	-36
	.byte	66
	.byte	-128
	.byte	-70
	.byte	55
	.byte	90
	.byte	-119
	.byte	111
	.byte	-59
	.byte	-14
	.byte	46
	.byte	-98
	.byte	-37
	.byte	9
	.byte	104
	.byte	-85
	.byte	2
	.byte	65
	.byte	125
	.byte	1
	.byte	44
	.byte	80
	.byte	1
	.byte	17
	.byte	91
	.byte	104
	.byte	-48
	.byte	-11
	.byte	39
	.byte	-88
	.byte	-32
	.byte	3
	.byte	109
	.byte	-94
	.byte	1
	.byte	79
	.byte	124
	.byte	1
	.byte	50
	.byte	102
	.byte	1
	.byte	43
	.byte	102
	.byte	84
	.byte	-36
	.byte	-10
	.byte	31
	.byte	-79
	.byte	-25
	.byte	2
	.byte	115
	.byte	-76
	.byte	1
	.byte	79
	.byte	-122
	.byte	1
	.byte	55
	.byte	77
	.byte	1
	.byte	60
	.byte	79
	.byte	43
	.byte	-13
	.byte	-16
	.byte	8
	.byte	-76
	.byte	-39
	.byte	1
	.byte	115
	.byte	-90
	.byte	1
	.byte	84
	.byte	121
	.byte	1
	.byte	51
	.byte	67
	.byte	1
	.byte	16
	.byte	6
	.type	vp9_default_if_uv_probs, %object
	.size	vp9_default_if_uv_probs, 90
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
	.byte	48
	.byte	12
	.byte	-102
	.byte	-101
	.byte	-117
	.byte	90
	.byte	34
	.byte	117
	.byte	119
	.byte	67
	.byte	6
	.byte	25
	.byte	-52
	.byte	-13
	.byte	-98
	.byte	13
	.byte	21
	.byte	96
	.byte	97
	.byte	5
	.byte	44
	.byte	-125
	.byte	-80
	.byte	-117
	.byte	48
	.byte	68
	.byte	97
	.byte	83
	.byte	5
	.byte	42
	.byte	-100
	.byte	111
	.byte	-104
	.byte	26
	.byte	49
	.byte	-104
	.byte	80
	.byte	5
	.byte	58
	.byte	-78
	.byte	74
	.byte	83
	.byte	33
	.byte	62
	.byte	-111
	.byte	86
	.byte	5
	.byte	32
	.byte	-102
	.byte	-64
	.byte	-88
	.byte	14
	.byte	22
	.byte	-93
	.byte	85
	.byte	5
	.byte	32
	.byte	-100
	.byte	-40
	.byte	-108
	.byte	19
	.byte	29
	.byte	73
	.byte	77
	.byte	7
	.byte	64
	.byte	116
	.byte	-124
	.byte	122
	.byte	37
	.byte	126
	.byte	120
	.byte	101
	.byte	21
	.byte	107
	.byte	-75
	.byte	-64
	.byte	103
	.byte	19
	.byte	67
	.byte	125
	.space	2
	.type	vp9_default_if_y_probs, %object
	.size	vp9_default_if_y_probs, 36
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
	.byte	-124
	.byte	68
	.byte	18
	.byte	-91
	.byte	-39
	.byte	-60
	.byte	45
	.byte	40
	.byte	78
	.byte	-83
	.byte	80
	.byte	19
	.byte	-80
	.byte	-16
	.byte	-63
	.byte	64
	.byte	35
	.byte	46
	.byte	-35
	.byte	-121
	.byte	38
	.byte	-62
	.byte	-8
	.byte	121
	.byte	96
	.byte	85
	.byte	29
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
	.word	16
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC3:
	ASCII(.ascii	"IN VP9DEC_Init\012\000" )
.LC4:
	ASCII(.ascii	"line: %d,Invalid pointer!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC6:
	ASCII(.ascii	"data_sz == 0\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"line: %d, fs is NULL!\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"%s  idx=%d\012\000" )
.LC13:
	ASCII(.ascii	"FSP_GetLogicFs err\000" )
	.space	1
.LC14:
	ASCII(.ascii	"fsp.c,L%d: %s\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"line: %d,pCtx is NULL!\012\000" )
.LC16:
	ASCII(.ascii	"line: %d, pCtx is NULL!\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"Invalid frame sync code\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"ref_deltas\000" )
	.space	1
.LC19:
	ASCII(.ascii	"mode_deltas\000" )
.LC20:
	ASCII(.ascii	"delta_q\000" )
.LC21:
	ASCII(.ascii	"%s  %d ERR\012\000" )
.LC22:
	ASCII(.ascii	"%s:%d this_size:%d is invalid!\012\000" )
.LC23:
	ASCII(.ascii	"4:4:4 color is not supported in profile 0 or 2 (%s " )
	ASCII(.ascii	": %d)\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"Invalid frame marker\012\000" )
	.space	2
.LC25:
	ASCII(.ascii	"%s:%d w&h=%dx%d is invalid!\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"VP9_Set_DecParam but logic fs is null!\012\000" )
.LC27:
	ASCII(.ascii	"Decord FS is NULL!\012\000" )
.LC28:
	ASCII(.ascii	"VP9_Set_DecParam but cur logic pstDecodeFs is null!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC30:
	ASCII(.ascii	"pic_width_in_pix:%d, pic_height_in_pix:%d\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"vp9 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC34:
	ASCII(.ascii	"vp9 alloc frame only\012\000" )
	.space	2
.LC35:
	ASCII(.ascii	"%s:%d size is invalid  size:%d bslen:%d\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"ERROR:Vp9_ReadCompressedHeader\012\000" )
.LC37:
	ASCII(.ascii	"pCurImg is null\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"err_level(%d) over ref_thr(%d)\012\000" )
.LC39:
	ASCII(.ascii	"line: %d pToQueImg is null\012\000" )
.LC40:
	ASCII(.ascii	"insert img to Voqueue failed!\012\000" )
	.space	1
.LC41:
	ASCII(.ascii	"pu8ProbCntVir == NULL\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"get_free_fb failed!\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"bit_depth(%d) not equal 8.\012\000" )
.LC44:
	ASCII(.ascii	"ERROR: pCtx->StreamParam.Length(%d) < 8\012\000" )
	.space	3
.LC45:
	ASCII(.ascii	"widthxheight exceed %d x %d\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"%dx%d, all=%d,cur=%d,ref=%d,ned=%d\012\000" )
.LC47:
	ASCII(.ascii	"ERROR: No Img buffer is allocated\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"%s %d, no fsp\012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"VP9_GetImageBuffer From Queue err\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"ERROR: VP9_Set_DecParam\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"VP9_DecOneNal ERR\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
