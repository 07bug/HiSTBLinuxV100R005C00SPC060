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
	.file	"mpeg4.c"
	.text
	.align	2
	.global	log2bin
	.type	log2bin, %function
log2bin:
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
	mov	r3, #0
.L3:
	add	r3, r3, #1
	movs	r0, r0, lsr #1
	uxth	r3, r3
	bne	.L3
	sxth	r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	log2bin, .-log2bin
	.align	2
	.global	bs_get_spritetrajectory
	.type	bs_get_spritetrajectory, %function
bs_get_spritetrajectory:
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
	ldr	r6, .L13
	mov	r7, r0
	mov	r4, #0
	mov	r5, r6
.L10:
	ldrb	r1, [r5, #4]	@ zero_extendqisi2
	mov	r0, r7
	bl	BsShow
	ldr	r3, [r6, r4, asl #3]
	ldr	r2, .L13
	mov	r1, r4, asl #3
	add	r5, r5, #8
	cmp	r0, r3
	beq	.L12
	add	r4, r4, #1
	cmp	r4, #12
	bne	.L10
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L12:
	add	r2, r2, r1
	mov	r0, r7
	ldrb	r1, [r2, #4]	@ zero_extendqisi2
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L14:
	.align	2
.L13:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	bs_get_spritetrajectory, .-bs_get_spritetrajectory
	.global	__aeabi_idiv
	.align	2
	.global	MP4_GetGMCparam
	.type	MP4_GetGMCparam, %function
MP4_GetGMCparam:
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
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldrb	r5, [r0, #73]	@ zero_extendqisi2
	mov	r2, #2
	mov	r9, r1
	mov	r3, r2, asl r5
	str	r0, [fp, #-52]
	mov	r0, #16
	rsb	r2, r5, #3
	mov	r1, r3
	str	r3, [fp, #-56]
	str	r2, [fp, #-100]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-52]
	ldr	r8, [r3, #716]
	ldr	r10, [r3, #712]
	cmp	r8, #1
	mov	r2, r8, asl #4
	str	r2, [r9, #8]
	str	r2, [fp, #-64]
	ldr	r2, [r3, #712]
	mov	r2, r2, asl #4
	str	r2, [r9, #12]
	ldrb	r2, [r3, #73]	@ zero_extendqisi2
	str	r2, [r9, #4]
	ldrb	r2, [r3, #72]	@ zero_extendqisi2
	str	r2, [r9]
	str	r2, [fp, #-68]
	ldr	r2, [r3, #696]
	ldr	r1, [r3, #688]
	ldr	lr, [r3, #700]
	str	r2, [fp, #-52]
	ldr	r2, [r3, #708]
	ldr	ip, [r3, #704]
	str	r2, [fp, #-72]
	str	r0, [fp, #-48]
	ldr	r0, [r3, #692]
	ble	.L40
	mov	r5, #0
	mov	r2, #1
.L17:
	add	r5, r5, #1
	mov	r6, r2, asl r5
	cmp	r8, r6
	bgt	.L17
	mov	r2, r6, asl #4
	str	r2, [fp, #-96]
.L16:
	cmp	r10, #1
	ble	.L41
	mov	r4, #0
	mov	r2, #1
.L19:
	add	r4, r4, #1
	mov	r7, r2, asl r4
	cmp	r10, r7
	bgt	.L19
	mov	r2, r7, asl #4
	str	r2, [fp, #-104]
.L18:
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L45
	add	ip, r1, ip
	str	ip, [fp, #-76]
	ldr	ip, [fp, #-52]
	add	r2, r1, r8, lsl #1
	add	r3, r0, r10, lsl #1
	add	lr, r0, lr
	add	r2, ip, r2
	ldr	ip, [fp, #-56]
	mov	ip, ip, asr #1
	str	ip, [fp, #-52]
	ldr	ip, [fp, #-72]
	add	r3, ip, r3
	mov	ip, r3
	ldr	r3, [fp, #-52]
	mul	r1, r3, r1
	mul	r2, r2, r3
	str	r1, [fp, #-60]
	mul	r1, lr, r3
	str	r1, [fp, #-84]
	ldr	r1, [fp, #-76]
	mul	r1, r1, r3
	str	r1, [fp, #-88]
	mul	r1, ip, r3
	mul	r3, r3, r0
	str	r1, [fp, #-92]
	str	r3, [fp, #-52]
.L21:
	ldr	ip, [fp, #-48]
	ldr	r3, [fp, #-64]
	ldr	r1, [fp, #-60]
	rsb	r0, r3, #0
	mul	r3, r1, ip
	mla	r0, r2, ip, r0
	mov	r2, r8, asr #1
	str	r2, [fp, #-80]
	mov	r1, r3
	str	r3, [fp, #-72]
	rsb	r3, r6, r8
	str	r3, [fp, #-76]
	mul	r0, r6, r0
	mla	r0, r1, r3, r0
	mov	r1, r8
	cmp	r0, #0
	addgt	r0, r0, r2
	rsble	r0, r2, r0
	bl	__aeabi_idiv
	ldr	r2, [fp, #-84]
	ldr	r3, [fp, #-48]
	mov	r1, r8
	mul	lr, r2, r3
	ldr	r2, [fp, #-52]
	mul	r3, r2, r3
	mul	lr, r6, lr
	mov	r2, r3
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-76]
	mla	r3, r2, r3, lr
	ldr	r2, [fp, #-96]
	cmp	r3, #0
	add	r2, r0, r2
	str	r2, [fp, #-76]
	ldr	r2, [fp, #-80]
	addgt	r0, r3, r2
	rsble	r0, r2, r3
	bl	__aeabi_idiv
	ldr	r3, [fp, #-88]
	ldr	ip, [fp, #-48]
	ldr	r2, [fp, #-48]
	ldr	lr, [fp, #-92]
	ldr	r1, [fp, #-72]
	mul	r2, r3, r2
	rsb	r3, r7, r10
	mul	r2, r7, r2
	mla	r2, r3, r1, r2
	mov	r1, r10, asr #1
	cmp	r2, #0
	addgt	r2, r2, r1
	rsble	r2, r1, r2
	str	r0, [fp, #-80]
	mov	r0, r10, asl #4
	rsb	r0, r0, #0
	mla	r0, lr, ip, r0
	ldr	ip, [fp, #-64]
	mul	r0, r7, r0
	mla	r3, r3, ip, r0
	cmp	r3, #0
	addgt	r3, r3, r1
	rsble	r3, r1, r3
	str	r3, [fp, #-72]
	ldr	r3, [fp, #-68]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L30
.L32:
	.word	.L42
	.word	.L33
	.word	.L34
	.word	.L35
.L42:
	mov	ip, #0
	mov	r6, ip
	mov	r8, ip
	mov	r2, ip
.L31:
	mov	r5, #0
	mov	r1, r5
.L39:
	mov	r6, r6, asr r1
	mov	r1, ip, asr r1
	str	r1, [r9, #44]
	mov	r2, r2, asr r5
	ldr	r1, [fp, #-56]
	mov	r3, #0
	mov	r5, r8, asr r5
	str	r2, [r9, #32]
	str	r5, [r9, #36]
	mov	r2, #1
	str	r6, [r9, #40]
	str	r1, [r9, #16]
	str	r1, [r9, #28]
	str	r3, [r9, #20]
	str	r3, [r9, #24]
	str	r2, [r9]
	b	.L15
.L35:
	ldr	r3, [fp, #-48]
	cmp	r4, r5
	ldr	r1, [fp, #-60]
	rsb	r3, r3, #0
	ldr	r8, [fp, #-100]
	mov	r0, r3
	add	r3, r5, r4
	mul	ip, r1, r0
	add	r3, r3, r8
	movge	r4, r5
	rsb	r5, r4, r3
	sub	r8, r5, #1
	mov	r3, #1
	mov	r8, r3, asl r8
	ldr	r3, [fp, #-76]
	mov	r7, r7, asr r4
	str	r0, [fp, #-68]
	add	r3, r3, ip
	str	ip, [fp, #-84]
	ldr	ip, [fp, #-52]
	mov	r0, r2
	add	r2, r8, r1, asl r5
	mov	r1, r10
	str	r2, [r9, #32]
	mov	r4, r6, asr r4
	add	r8, r8, ip, asl r5
	str	r8, [r9, #36]
	str	r2, [fp, #-88]
	str	r4, [fp, #-64]
	mul	r4, r7, r3
	bl	__aeabi_idiv
	mov	r3, r6, asl #1
	mov	r6, r6, asl #4
	ldr	lr, [fp, #-68]
	ldr	ip, [fp, #-52]
	rsb	r6, r6, #0
	mul	r3, r7, r3
	mov	r1, r10
	mul	r6, r7, r6
	ldr	r2, [fp, #-80]
	mul	r10, ip, lr
	ldr	lr, [fp, #-48]
	add	ip, r5, #1
	mul	r3, lr, r3
	ldr	lr, [fp, #-84]
	str	r6, [fp, #-68]
	mov	r6, #1
	mov	r6, r6, asl ip
	str	r10, [fp, #-48]
	add	ip, r2, r10
	ldr	r2, [fp, #-60]
	str	r6, [fp, #-76]
	str	r3, [fp, #-60]
	mul	r7, r7, ip
	ldr	ip, [fp, #-76]
	add	r10, r0, lr
	ldr	lr, [fp, #-64]
	ldr	r0, [fp, #-72]
	mul	r10, lr, r10
	add	r6, r4, r10
	mla	r6, r2, r3, r6
	ldr	r3, [fp, #-68]
	add	r6, r6, r3
	add	r6, r6, ip
	str	r6, [r9, #40]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-104]
	ldr	r3, [fp, #-48]
	add	r1, r5, #2
	ldr	lr, [fp, #-64]
	str	r10, [r9, #20]
	str	r4, [r9, #16]
	str	r7, [r9, #24]
	add	r0, r0, r2
	ldr	r2, [fp, #-52]
	add	r0, r0, r3
	ldr	r3, [fp, #-60]
	mul	r0, lr, r0
	add	ip, r7, r0
	mla	r3, r2, r3, ip
	ldr	r2, [fp, #-68]
	str	r0, [r9, #28]
	add	ip, r2, r3
	ldr	r2, [fp, #-88]
	ldr	r3, [fp, #-76]
	add	ip, r3, ip
	str	ip, [r9, #44]
.L36:
	ldr	r3, [fp, #-56]
	cmp	r4, r3, asl r5
	beq	.L46
.L37:
	rsb	r5, r5, #16
	rsb	r1, r1, #16
	mov	r2, r2, asl r5
	mov	r8, r8, asl r5
	mov	r4, r4, asl r5
	mov	r10, r10, asl r5
	mov	r7, r7, asl r5
	mov	r6, r6, asl r1
	mov	r5, r0, asl r5
	mov	r1, ip, asl r1
	str	r2, [r9, #32]
	str	r8, [r9, #36]
	str	r4, [r9, #16]
	str	r10, [r9, #20]
	str	r7, [r9, #24]
	str	r5, [r9, #28]
	str	r6, [r9, #40]
	str	r1, [r9, #44]
.L15:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L34:
	ldr	r0, [fp, #-80]
	mov	r3, r6, asl #1
	ldr	r1, [fp, #-64]
	mov	r6, r6, asl #4
	ldr	ip, [fp, #-48]
	rsb	r10, r0, r1
	ldr	lr, [fp, #-60]
	ldr	r8, [fp, #-52]
	rsb	r7, ip, #0
	ldr	r1, [fp, #-76]
	mul	r3, ip, r3
	ldr	r2, [fp, #-100]
	mla	r4, lr, r7, r1
	add	r5, r5, r2
	mla	r7, r8, r7, r0
	rsb	r0, r6, #0
	add	r6, r10, r4
	mov	r2, #1
	add	r1, r5, #1
	str	r10, [r9, #20]
	add	ip, r4, r7
	mov	r1, r2, asl r1
	mla	r6, lr, r3, r6
	str	r4, [r9, #16]
	mla	r3, r8, r3, ip
	sub	r8, r5, #1
	add	r6, r6, r0
	mov	r8, r2, asl r8
	add	r6, r6, r1
	add	r2, r8, lr, asl r5
	add	ip, r0, r3
	ldr	r3, [fp, #-56]
	add	ip, r1, ip
	ldr	r1, [fp, #-52]
	str	r7, [r9, #24]
	mov	r0, r4
	cmp	r4, r3, asl r5
	str	r4, [r9, #28]
	add	r8, r8, r1, asl r5
	str	r6, [r9, #40]
	str	ip, [r9, #44]
	add	r1, r5, #2
	str	r2, [r9, #32]
	str	r8, [r9, #36]
	bne	.L37
.L46:
	cmp	r10, #0
	bne	.L37
	cmp	r7, #0
	bne	.L37
	cmp	r4, r0
	bne	.L37
	b	.L39
.L33:
	ldr	r3, [fp, #-60]
	ldr	r1, [fp, #-52]
	and	r6, r3, #1
	and	ip, r1, #1
	orr	r6, r6, r3, asr #1
	mov	r2, r3
	orr	ip, ip, r1, asr #1
	mov	r8, r1
	b	.L31
.L45:
	ldr	r3, [fp, #-56]
	add	ip, r1, ip
	str	r1, [fp, #-60]
	add	lr, r0, lr
	str	ip, [fp, #-88]
	mla	r2, r8, r3, r1
	ldr	ip, [fp, #-52]
	mla	r3, r10, r3, r0
	ldr	r1, [fp, #-72]
	str	lr, [fp, #-84]
	add	r2, ip, r2
	str	r0, [fp, #-52]
	add	r3, r1, r3
	str	r3, [fp, #-92]
	b	.L21
.L30:
	mov	r1, #0
	ldr	r4, [r9, #16]
	mov	r5, r1
	ldr	r2, [r9, #32]
	ldr	r8, [r9, #36]
	ldr	r6, [r9, #40]
	ldr	ip, [r9, #44]
	ldr	r10, [r9, #20]
	ldr	r7, [r9, #24]
	ldr	r0, [r9, #28]
	b	.L36
.L40:
	mov	r2, #16
	mov	r6, #1
	str	r2, [fp, #-96]
	mov	r5, #0
	b	.L16
.L41:
	mov	r2, #16
	mov	r7, #1
	str	r2, [fp, #-104]
	mov	r4, #0
	b	.L18
	UNWIND(.fnend)
	.size	MP4_GetGMCparam, .-MP4_GetGMCparam
	.align	2
	.global	Mp4_GetUserDataBuf
	.type	Mp4_GetUserDataBuf, %function
Mp4_GetUserDataBuf:
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
	ldr	r3, [r1, r2, asl #2]
	cmp	r3, #0
	beq	.L52
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L52:
	str	r2, [fp, #-20]
	str	r1, [fp, #-16]
	bl	GetUsd
	ldr	r2, [fp, #-20]
	ldr	r1, [fp, #-16]
	cmp	r0, #0
	mov	r3, r0
	str	r0, [r1, r2, asl #2]
	addne	r0, r2, #4
	strne	r0, [r3, #1040]
	ldrne	r3, [r1, r2, asl #2]
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4_GetUserDataBuf, .-Mp4_GetUserDataBuf
	.align	2
	.global	Mp4_ClearUsrData
	.type	Mp4_ClearUsrData, %function
Mp4_ClearUsrData:
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
	sub	r4, r1, #4
	add	r5, r1, #12
	mov	r7, r0
	mov	r6, #0
.L54:
	ldr	r1, [r4, #4]!
	mov	r0, r7
	bl	FreeUsdByDec
	cmp	r4, r5
	str	r6, [r4]
	bne	.L54
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4_ClearUsrData, .-Mp4_ClearUsrData
	.align	2
	.global	Mp4_Syntax_Init
	.type	Mp4_Syntax_Init, %function
Mp4_Syntax_Init:
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
	ldr	r5, .L61
	mov	r4, r0
	add	r0, r0, #19968
	mov	r2, #24
	mov	r1, #0
	add	r0, r0, #16
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r5, #48]
	mov	r2, #604
	mov	r1, #0
	add	r0, r0, #40
	blx	r3
	add	r0, r4, #20992
	ldr	r3, [r5, #48]
	mov	r2, #60
	mov	r1, #0
	add	r0, r0, #224
	blx	r3
	add	r0, r4, #21248
	ldr	r3, [r5, #48]
	mov	r2, #776
	mov	r1, #0
	add	r0, r0, #28
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r5, #48]
	mov	r2, #7
	mov	r1, #0
	add	r0, r0, #36
	blx	r3
	ldr	r3, .L61+4
	add	r2, r4, #19968
	add	r1, r4, #20480
	add	r2, r2, #124
	add	r0, r3, #256
	mov	ip, #1
	strb	ip, [r1, #821]
	str	ip, [r1, #2136]
.L57:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L57
	ldr	r3, .L61+8
	add	r2, r4, #20224
	add	r2, r2, #124
	add	r0, r3, #256
.L58:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L58
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L62:
	.align	2
.L61:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1-4
	.word	.LANCHOR1+252
	UNWIND(.fnend)
	.size	Mp4_Syntax_Init, .-Mp4_Syntax_Init
	.align	2
	.global	Global_Data_Init
	.type	Global_Data_Init, %function
Global_Data_Init:
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
	ldr	r5, .L64
	mov	r4, r0
	add	r0, r0, #22016
	mov	r2, #24
	mov	r1, #0
	add	r0, r0, #64
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r5, #48]
	mov	r2, #16
	mov	r1, #0
	add	r0, r0, #44
	blx	r3
	mov	r0, r4
	bl	Mp4_Syntax_Init
	add	r3, r4, #20480
	mov	r2, #0
	mov	r0, r2
	str	r2, [r3, #2116]
	str	r2, [r3, #2120]
	str	r2, [r3, #2124]
	str	r2, [r3, #2128]
	str	r2, [r3, #2088]
	str	r2, [r3, #1628]
	str	r2, [r3, #2072]
	str	r2, [r3, #2076]
	str	r2, [r3, #2080]
	str	r2, [r3, #2132]
	str	r2, [r3, #2092]
	str	r2, [r3, #2096]
	str	r2, [r3, #2100]
	str	r2, [r3, #2104]
	str	r2, [r3, #2108]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L65:
	.align	2
.L64:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Global_Data_Init, .-Global_Data_Init
	.align	2
	.global	Bs_Get_Matrix
	.type	Bs_Get_Matrix, %function
Bs_Get_Matrix:
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
	mov	r5, #0
	mov	r8, r0
	mov	r6, r1
	mov	r4, r5
	ldr	r7, .L76
	b	.L67
.L71:
	mov	r5, r0
.L67:
	mov	r1, #8
	mov	r0, r8
	bl	BsGet
	add	ip, r4, #1
	sxth	r9, r4
	uxth	r3, ip
	add	r1, r7, r9, lsl #2
	sxth	r2, r3
	uxth	r3, r3
	ldr	r1, [r1, #512]
	mov	r4, r3
	adds	lr, r0, #0
	str	r0, [r6, r1, asl #2]
	movne	lr, #1
	cmp	r2, #63
	movgt	r2, #0
	andle	r2, lr, #1
	cmp	r2, #0
	bne	.L71
	cmp	lr, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r9, #63
	ldmgtfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L70:
	uxth	r4, ip
	str	r5, [r6, r1, asl #2]
	add	ip, r4, #1
	sxth	r3, r4
	cmp	r3, #64
	add	r3, r7, r3, lsl #2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r1, [r3, #512]
	b	.L70
.L77:
	.align	2
.L76:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	Bs_Get_Matrix, .-Bs_Get_Matrix
	.align	2
	.global	NextStartCode
	.type	NextStartCode, %function
NextStartCode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	mov	r6, r0
	sub	r0, fp, #60
	mov	r7, r3
	mov	r4, r2, asl #3
	movw	r5, #438
	bl	BsInit
	mov	r0, #0
	b	.L79
.L83:
	cmp	lr, #256
	beq	.L92
.L87:
	bl	BsSkip
	sub	r0, fp, #60
	bl	BsPos
.L79:
	rsb	r3, r0, r4
	mov	r1, #32
	cmp	r3, #31
	sub	r0, fp, #60
	ble	.L93
	bl	BsShow
	mov	r1, #8
	mov	r3, r0
	cmp	r3, r5
	bic	r2, r0, #1020
	bic	ip, r0, #15
	bic	lr, r0, #255
	bic	r2, r2, #3
	sub	r0, fp, #60
	beq	.L82
	cmp	ip, #288
	beq	.L82
	cmp	r2, #32768
	bne	.L83
	ldrb	r3, [r6, #9]	@ zero_extendqisi2
	mov	r1, #8
	sub	r0, fp, #60
	cmp	r3, #2
	bne	.L94
	ldr	r3, [r6, #752]
	add	r3, r3, #1
	str	r3, [r6, #752]
	cmp	r3, #18
	bls	.L87
	mov	r2, #196
	mov	r3, #1
	str	r2, [r7]
	sub	r0, fp, #60
	strb	r3, [r6, #9]
	bl	BsPos
	b	.L81
.L82:
	mov	r1, #2
	mov	r2, #0
	strb	r1, [r6, #9]
	sub	r0, fp, #60
	str	r2, [r6, #752]
	str	r3, [r7]
	bl	BsPos
.L81:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L93:
	mov	r3, #197
	str	r3, [r7]
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L92:
	str	r3, [r7]
	sub	r0, fp, #60
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L94:
	mov	r2, #1
	mov	r3, #196
	strb	r2, [r6, #9]
	str	r3, [r7]
	bl	BsPos
	b	.L81
	UNWIND(.fnend)
	.size	NextStartCode, .-NextStartCode
	.align	2
	.global	Mp4SearchStartCode
	.type	Mp4SearchStartCode, %function
Mp4SearchStartCode:
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
	cmp	r1, #4
	ble	.L107
	add	lr, r0, r1
	add	r3, r0, #2
.L112:
	cmp	lr, r3
	bls	.L97
.L113:
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bls	.L98
	and	ip, r2, #252
	cmp	ip, #128
	beq	.L98
.L105:
	add	r3, r3, #3
	cmp	lr, r3
	bhi	.L113
.L97:
	sub	r0, r1, #2
	ldmfd	sp, {fp, sp, pc}
.L98:
	cmp	r2, #0
	bne	.L100
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #1
	beq	.L112
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #2
	addne	r3, r3, #4
	b	.L112
.L100:
	cmp	r2, #1
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	beq	.L114
	cmp	r2, #0
	bne	.L105
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L105
	rsb	r0, r0, r3
	sub	r0, r0, #2
	ldmfd	sp, {fp, sp, pc}
.L114:
	cmp	r2, #0
	bne	.L105
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L105
	rsb	r3, r0, r3
	sub	r0, r3, #2
	ldmfd	sp, {fp, sp, pc}
.L107:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4SearchStartCode, .-Mp4SearchStartCode
	.align	2
	.global	Mp4_Syntax_Gop
	.type	Mp4_Syntax_Gop, %function
Mp4_Syntax_Gop:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	mov	r4, r0
	sub	r0, fp, #60
	bl	BsInit
	mov	r1, #32
	sub	r0, fp, #60
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #6
	sub	r0, fp, #60
	bl	BsGet
	sub	r0, fp, #60
	mov	r1, #1
	bl	BsGet
	subs	r6, r0, #0
	bne	.L116
	add	r4, r4, #20480
	ldr	r1, .L119
	mov	r0, #1
	bl	dprint_vfmw
	strb	r6, [r4, #1574]
	sub	r0, fp, #60
	bl	BsPos
	ldr	r3, .L119+4
	ldr	r7, [r3]
	cmp	r7, #0
	mov	r5, r0
	beq	.L117
	ldr	r0, [r4, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #103
	blx	r7
	mov	r0, r5
.L117:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L116:
	mov	r1, #6
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	sub	r0, fp, #60
	add	r4, r4, #20480
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #798]
	sub	r0, fp, #60
	bl	BsGet
	mov	r3, #1
	strb	r3, [r4, #1574]
	strb	r0, [r4, #799]
	sub	r0, fp, #60
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L120:
	.align	2
.L119:
	.word	.LC0
	.word	g_event_report
	UNWIND(.fnend)
	.size	Mp4_Syntax_Gop, .-Mp4_Syntax_Gop
	.align	2
	.global	Mp4_Syntax_UserData
	.type	Mp4_Syntax_UserData, %function
Mp4_Syntax_UserData:
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
	cmp	r2, #6
	mov	r3, #0
	mov	r4, r0
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	strb	r3, [fp, #-61]
	ble	.L122
	cmp	r2, #4
	ble	.L123
	ldrb	ip, [r1, #4]!	@ zero_extendqisi2
	mov	r5, r0
	movw	r7, #1030
	mov	r0, #4
	mvn	r3, ip, asl #24
	strb	ip, [r5, #3]!
	mvn	r3, r3, lsr #24
	mov	lr, r5
	mov	r3, r3, asl #8
	b	.L124
.L129:
	ldrb	ip, [r1, #1]!	@ zero_extendqisi2
	orr	r3, r3, ip
	mov	r3, r3, asl #8
	cmp	r3, #256
	beq	.L183
	cmp	r0, r7
	strb	ip, [lr, #1]!
	beq	.L184
.L124:
	sub	r6, r0, #3
	add	r0, r0, #1
	cmp	r0, r2
	bne	.L129
.L180:
	add	r8, r4, #20480
	cmp	r6, #2
	mov	r3, #1
	mov	r10, r6
	mov	r7, r2, asl #3
	strb	r3, [r8, #1578]
	bhi	.L185
.L161:
	mov	r0, r7
.L179:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L122:
	add	r4, r0, #20480
	add	r7, r2, #1
	strb	r3, [r4, #1578]
	mov	r0, r7, asl #3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L183:
	sub	r0, r0, #2
	cmp	r2, r0
	bge	.L186
.L128:
	add	r7, r2, #1
	mov	r0, r7, asl #3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L185:
	add	r1, r4, #22528
	ldr	r2, [r8, #2108]
	add	r1, r1, #68
	ldr	r0, [r8, #2496]
	bl	Mp4_GetUserDataBuf
	ldr	r9, .L190
	cmp	r0, #0
	str	r0, [r8, #2132]
	beq	.L132
	cmn	r6, #-2147483648
	ldr	r3, [r9, #52]
	sub	r6, r6, #2
	str	r6, [r0, #1052]
	movpl	r2, #0
	ldr	r0, [r8, #2132]
	bmi	.L187
.L133:
	mov	r1, r5
	blx	r3
	ldr	r1, .L190+4
	ldr	r2, [r8, #1596]
	ldr	r3, [r8, #2132]
	ldr	r10, [r1]
	ldrd	r0, [r2, #64]
	add	r3, r3, #1056
	cmp	r10, #0
	strd	r0, [r3]
	beq	.L132
	movw	r3, #1064
	ldr	r2, [r8, #2132]
	mov	r1, #6
	ldr	r0, [r8, #2496]
	blx	r10
.L132:
	cmn	r6, #-2147483646
	movpl	r6, #0
	bmi	.L188
.L134:
	add	r6, r4, r6
	mov	r2, #0
	sub	r0, fp, #61
	sub	r3, fp, #56
	strb	r2, [r6, #3]
	sub	r2, fp, #60
	str	r0, [sp]
	mov	r0, r5
	ldr	r4, [r9, #72]
	ldr	r1, .L190+8
	blx	r4
	ldr	r2, .L190
	cmp	r0, #1
	ble	.L189
.L135:
	ldr	r3, [fp, #-56]
	cmp	r0, #3
	ldr	r2, [fp, #-60]
	str	r3, [r8, #1556]
	movne	r3, #0
	ldreqsb	r3, [fp, #-61]
	str	r2, [r8, #1552]
	subeq	r3, r3, #112
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	str	r3, [r8, #1560]
.L136:
	ldr	r3, [r9, #72]
	sub	r2, fp, #56
	ldr	r1, .L190+12
	mov	r0, r5
	blx	r3
	ldr	r4, .L190
	cmp	r0, #1
	beq	.L138
	sub	r3, fp, #56
	sub	r6, fp, #48
	str	r3, [sp, #4]
	sub	r2, fp, #60
	ldr	r10, [r4, #72]
	sub	r3, fp, #52
	str	r6, [sp]
	mov	r0, r5
	ldr	r1, .L190+16
	blx	r10
	cmp	r0, #4
	beq	.L138
	str	r6, [sp]
	sub	r3, fp, #52
	ldr	r4, [r4, #72]
	sub	r2, fp, #60
	ldr	r1, .L190+20
	mov	r0, r5
	blx	r4
	add	r0, r0, #1
	cmp	r0, #1
	ble	.L139
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-60]
	ldr	r1, [fp, #-48]
	mov	r2, r2, asl #8
	add	r3, r2, r3, lsl #16
	add	r3, r3, r1
	str	r3, [fp, #-56]
.L139:
	cmp	r0, #4
	beq	.L138
	ldr	r3, [r9, #76]
	mov	r2, #7
	ldr	r1, .L190+24
	mov	r0, r5
	blx	r3
	cmp	r0, #0
	movweq	r3, #4600
	streq	r3, [r8, #1568]
.L150:
	sub	r2, fp, #56
	ldr	r3, [r9, #72]
	ldr	r1, .L190+28
	mov	r0, r5
	blx	r3
	mov	r3, #0
	ldr	r1, [r8, #1552]
	strb	r3, [r8, #809]
	strb	r3, [r8, #810]
	strb	r3, [r8, #807]
	strb	r3, [r8, #806]
	strb	r3, [r8, #808]
	cmp	r0, #1
	ldreq	r2, [fp, #-56]
	ldrne	r2, [r8, #1564]
	streq	r2, [r8, #1564]
	cmp	r2, #0
	beq	.L143
	cmp	r1, r3
	strne	r3, [r8, #1552]
	strne	r3, [r8, #1556]
	cmp	r2, #1
	mvnne	r0, #0
	movne	r1, #0
	beq	.L182
.L153:
	movw	r3, #502
	cmp	r1, r3
	bls	.L145
.L152:
	mov	r3, #1
	strb	r3, [r8, #810]
.L145:
	sub	r2, r2, #1
	cmp	r2, #11
	bhi	.L146
.L154:
	mov	r3, #1
	strb	r3, [r8, #807]
.L146:
	ldr	r3, [r8, #1568]
	movw	r2, #4668
	sub	r3, r3, #1
	cmp	r3, r2
	movls	r3, #1
	strlsb	r3, [r8, #807]
	movw	r3, #498
	cmp	r0, r3
	movls	r3, #1
	strlsb	r3, [r8, #807]
	cmp	r1, #500
	bne	.L161
	ldr	r2, [r8, #1556]
	movw	r3, #413
	mov	r0, r7
	cmp	r2, r3
	moveq	r3, #1
	streqb	r3, [r8, #808]
	b	.L179
.L184:
	add	r4, r4, #20480
	mov	r3, #0
	movw	r0, #8224
	strb	r3, [r4, #1578]
	b	.L179
.L138:
	ldr	r3, [fp, #-56]
	str	r3, [r8, #1568]
	b	.L150
.L187:
	cmp	r10, #1024
	movlt	r2, r10
	movge	r2, #1024
	b	.L133
.L143:
	cmp	r1, #500
	subcs	r0, r1, #1
	movcs	r3, #1
	strcsb	r3, [r8, #809]
	bcs	.L153
	movw	r3, #502
	cmp	r1, r3
	sub	r0, r1, #1
	bhi	.L152
	b	.L146
.L188:
	add	r6, r6, #2
	cmp	r6, #1024
	movge	r6, #1024
	b	.L134
.L123:
	cmp	r2, #3
	ble	.L128
	add	r4, r4, #20480
	mov	r3, #1
	mov	r0, #32
	strb	r3, [r4, #1578]
	b	.L179
.L186:
	mov	r2, r0
	b	.L180
.L189:
	sub	r3, fp, #61
	ldr	r1, .L190+32
	str	r3, [sp]
	mov	r0, r5
	ldr	r4, [r2, #72]
	sub	r3, fp, #56
	sub	r2, fp, #60
	blx	r4
	cmp	r0, #1
	ble	.L136
	b	.L135
.L182:
	strb	r2, [r8, #809]
	mvn	r0, #0
	mov	r1, #0
	b	.L154
.L191:
	.align	2
.L190:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC1
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC2
	UNWIND(.fnend)
	.size	Mp4_Syntax_UserData, .-Mp4_Syntax_UserData
	.align	2
	.global	Mp4_Syntax_Vo
	.type	Mp4_Syntax_Vo, %function
Mp4_Syntax_Vo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	add	r4, r0, #20480
	mov	r5, r0
	sub	r0, fp, #60
	mov	r7, r2
	mov	r6, #1
	bl	BsInit
	mov	r3, #0
	mov	r1, #32
	strb	r3, [r4, #820]
	strb	r3, [r4, #822]
	sub	r0, fp, #60
	strb	r3, [r4, #823]
	add	r5, r5, #16384
	strb	r3, [r4, #824]
	strb	r3, [r4, #825]
	strb	r3, [r4, #826]
	strb	r3, [r4, #827]
	str	r3, [r4, #832]
	str	r3, [r4, #836]
	str	r3, [r4, #840]
	strb	r6, [r4, #821]
	bl	BsSkip
	mov	r1, r6
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3600]
	cmp	r0, #0
	streqb	r6, [r5, #3601]
	bne	.L207
.L194:
	mov	r1, #4
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r5, #3603]
	cmp	r6, #1
	beq	.L208
	mov	r7, #0
	sub	r0, fp, #60
	strb	r7, [r4, #1573]
	bl	BsPos
	ldr	r3, .L210
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r5, r0
	beq	.L198
	ldr	r0, [r4, #2496]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
	mov	r0, r5
.L198:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L207:
	mov	r1, #4
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #3
	strb	r0, [r5, #3601]
	sub	r0, fp, #60
	bl	BsGet
	strb	r0, [r5, #3602]
	b	.L194
.L208:
	mov	r1, r6
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3604]
	cmp	r0, #0
	bne	.L209
.L197:
	mov	r3, #1
	sub	r0, fp, #60
	strb	r3, [r4, #1573]
	bl	BsPos
	cmp	r0, r7, asl #3
	bgt	.L199
	ldrb	r3, [r5, #3600]	@ zero_extendqisi2
	strb	r3, [r4, #820]
	ldrb	r3, [r5, #3601]	@ zero_extendqisi2
	strb	r3, [r4, #821]
	ldrb	r3, [r5, #3602]	@ zero_extendqisi2
	strb	r3, [r4, #822]
	ldrb	r3, [r5, #3603]	@ zero_extendqisi2
	strb	r3, [r4, #823]
	ldrb	r3, [r5, #3604]	@ zero_extendqisi2
	strb	r3, [r4, #824]
	ldrb	r3, [r5, #3605]	@ zero_extendqisi2
	strb	r3, [r4, #825]
	ldrb	r3, [r5, #3606]	@ zero_extendqisi2
	strb	r3, [r4, #826]
	ldrb	r3, [r5, #3607]	@ zero_extendqisi2
	strb	r3, [r4, #827]
	ldr	r3, [r5, #3612]
	str	r3, [r4, #832]
	ldr	r3, [r5, #3616]
	str	r3, [r4, #836]
	ldr	r3, [r5, #3620]
	str	r3, [r4, #840]
.L199:
	sub	r0, fp, #60
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L209:
	mov	r1, #3
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, r6
	strb	r0, [r5, #3605]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, r6
	strb	r0, [r5, #3606]
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3607]
	cmp	r0, #0
	beq	.L197
	mov	r1, #8
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #3612]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #3616]
	sub	r0, fp, #60
	bl	BsGet
	str	r0, [r5, #3620]
	b	.L197
.L211:
	.align	2
.L210:
	.word	g_event_report
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vo, .-Mp4_Syntax_Vo
	.align	2
	.global	Mp4_Syntax_Vol
	.type	Mp4_Syntax_Vol, %function
Mp4_Syntax_Vol:
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
	add	r5, r0, #20480
	mov	r6, r0
	ldr	r3, .L374
	ldr	r0, [r5, #2496]
	add	r7, r6, #19968
	ldr	r8, .L374+4
	add	r7, r7, #40
	add	r4, r6, #16384
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r0, [r3, #1268]
	moveq	r9, #8192
	ldrne	r9, [r3, #1272]
	streq	r9, [fp, #-80]
	strne	r0, [fp, #-80]
	sub	r0, fp, #76
	bl	BsInit
	ldr	r3, [r8, #48]
	mov	r2, #604
	mov	r1, #0
	mov	r0, r7
	strb	r1, [r5, #797]
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #3628]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3652]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3624]
	cmp	r0, #0
	ldreqb	r3, [r5, #821]	@ zero_extendqisi2
	streqb	r3, [r4, #3625]
	bne	.L363
.L215:
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3627]
	cmp	r0, #15
	beq	.L364
.L216:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3629]
	cmp	r0, #0
	moveq	r3, #1
	streqb	r3, [r4, #3630]
	bne	.L365
.L221:
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3632]
	cmp	r10, #0
	subne	r0, fp, #76
	movne	r7, #0
	beq	.L366
.L357:
	strb	r7, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L292
	ldr	r0, [r5, #2496]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
	mov	r0, r4
.L327:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L366:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	mov	r1, #16
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #3696]
	beq	.L229
	subs	r0, r0, #1
	beq	.L229
	mov	r2, r10
	mov	r3, r0
.L231:
	add	r2, r2, #1
	movs	r3, r3, lsr #1
	uxth	r2, r2
	bne	.L231
	sxth	r2, r2
	cmp	r2, #0
	ble	.L229
.L233:
	add	r3, r3, #1
	movs	r0, r0, lsr #1
	uxth	r3, r3
	bne	.L233
	sxth	r3, r3
.L329:
	str	r3, [r4, #3692]
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3633]
	cmp	r0, #0
	bne	.L367
.L236:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3704]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3708]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L342
	ldr	r3, [r4, #3704]
	cmp	r3, #31
	bls	.L240
	ldr	r2, [r4, #3708]
	cmp	r2, #31
	bls	.L240
	mul	r3, r3, r2
	ldr	r2, [fp, #-80]
	mul	r9, r9, r2
	cmp	r3, r9
	bls	.L241
.L240:
	mov	r7, #0
	sub	r0, fp, #76
	strb	r7, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L292
.L336:
	ldr	r0, [r5, #2496]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #103
	blx	r6
	mov	r0, r4
	b	.L327
.L342:
	ldr	r1, .L374+12
	mov	r0, #1
	str	r3, [fp, #-80]
.L344:
	bl	dprint_vfmw
	ldr	r3, [fp, #-80]
	sub	r0, fp, #76
	strb	r3, [r5, #1575]
	bl	BsPos
	ldr	r2, .L374+8
	ldr	r6, [r2]
	cmp	r6, #0
	mov	r4, r0
	beq	.L292
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r5, #2496]
	mov	r2, r3
	blx	r6
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L365:
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3630]
	cmp	r10, #1
	beq	.L218
	mov	r3, #0
	sub	r0, fp, #76
	strb	r3, [r5, #1575]
	bl	BsPos
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L363:
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #3625]
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #3626]
	b	.L215
.L218:
	mov	r1, r10
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	strb	r0, [r4, #3631]
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #3664]
	beq	.L221
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3668]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L359
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3672]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L359
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3676]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L359
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #11
	str	r0, [r4, #3680]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3684]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L359
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3688]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	str	r3, [fp, #-84]
	bne	.L221
	ldr	r1, .L374+12
	mov	r0, r10
	bl	dprint_vfmw
	ldr	r7, [fp, #-84]
	sub	r0, fp, #76
	strb	r7, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r4, r0
	bne	.L336
.L292:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L364:
	mov	r1, #8
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #3656]
	sub	r0, fp, #76
	bl	BsGet
	str	r0, [r4, #3660]
	b	.L216
.L229:
	mov	r3, #1
	b	.L329
.L359:
	str	r3, [fp, #-80]
	mov	r0, r10
	ldr	r1, .L374+12
	b	.L344
.L367:
	ldr	r1, [r4, #3692]
	sub	r0, fp, #76
	bl	BsGet
	str	r0, [r4, #3700]
	b	.L236
.L241:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3634]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #3635]
	cmp	r3, #0
	bne	.L243
	ldr	r2, .L374+8
	strb	r3, [r5, #1575]
	ldr	r9, [r2]
	cmp	r9, #0
	beq	.L243
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r5, #2496]
	blx	r9
.L243:
	ldrb	r3, [r4, #3625]	@ zero_extendqisi2
	sub	r0, fp, #76
	cmp	r3, #1
	moveq	r1, #1
	movne	r1, #2
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3636]
	cmp	r9, #0
	beq	.L246
	ldr	r3, .L374+16
	ldr	r10, [r3]
	ands	r10, r10, #8
	beq	.L368
	sub	r3, r9, #1
	cmp	r3, #1
	bls	.L369
	mov	r7, #0
	sub	r0, fp, #76
	strb	r7, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L253
	ldr	r0, [r5, #2496]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
.L253:
	ldr	r1, .L374+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L327
.L370:
	mov	r1, #6
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r9
	strb	r0, [r4, #3648]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3649]
	sub	r0, fp, #76
	bl	BsGet
	ldrb	r3, [r4, #3636]	@ zero_extendqisi2
	cmp	r3, #2
	strb	r0, [r4, #3650]
	bne	.L361
.L246:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3637]
	cmp	r0, #0
	beq	.L254
	mov	r7, #0
	sub	r0, fp, #76
	strb	r7, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L255
	ldr	r0, [r5, #2496]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
.L255:
	ldr	r1, .L374+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L327
.L369:
	cmp	r9, #2
	beq	.L370
.L361:
	mov	r7, #0
	sub	r0, fp, #76
	strb	r7, [r5, #1575]
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L252
	ldr	r0, [r5, #2496]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
.L252:
	ldr	r1, .L374+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L327
.L254:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3638]
	cmp	r0, #0
	bne	.L371
.L257:
	ldrb	r3, [r4, #3625]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r3, #0
	streqb	r3, [r4, #3641]
	beq	.L264
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #3641]
.L264:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3642]
	cmp	r9, #0
	ldreq	r1, .L374+32
	beq	.L353
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3643]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3644]
	cmp	r10, #0
	ldrne	r1, .L374+36
	bne	.L355
	ldrb	r3, [r4, #3625]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L267
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3645]
	cmp	r9, #0
	beq	.L268
	ldr	r1, .L374+40
	mov	r0, #1
	bl	dprint_vfmw
	strb	r10, [r5, #1575]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r4, r0
	beq	.L292
	ldr	r0, [r5, #2496]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #102
	blx	r6
	mov	r0, r4
	b	.L327
.L368:
	strb	r10, [r5, #1575]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r4, r0
	beq	.L248
	ldr	r0, [r5, #2496]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #102
	blx	r6
.L248:
	ldr	r1, .L374+44
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L327
.L371:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3639]
	cmp	r0, #0
	bne	.L372
	ldr	r3, .L374+48
	add	r2, r6, #19968
	add	r2, r2, #124
	add	r0, r3, #256
.L260:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L260
.L259:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3640]
	cmp	r0, #0
	bne	.L272
	ldr	r3, .L374+52
	add	r2, r6, #20224
	add	r2, r2, #124
	add	r0, r3, #256
.L261:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L261
	b	.L257
.L373:
	ldr	r1, .L374+56
.L353:
	mov	r0, #1
	bl	dprint_vfmw
	strb	r9, [r5, #1575]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L374+8
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r4, r0
	beq	.L292
	ldr	r0, [r5, #2496]
	mov	r3, r9
	mov	r2, r9
	mov	r1, #102
	blx	r6
	mov	r0, r4
	b	.L327
.L268:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3646]
	cmp	r0, #0
	bne	.L373
.L269:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3647]
	cmp	r0, #0
	beq	.L270
	ldr	r1, .L374+60
.L355:
	mov	r0, #1
	mov	r7, #0
	bl	dprint_vfmw
	sub	r0, fp, #76
	b	.L357
.L372:
	add	r1, r6, #19968
	sub	r0, fp, #76
	add	r1, r1, #128
	bl	Bs_Get_Matrix
	b	.L259
.L272:
	add	r1, r6, #20224
	sub	r0, fp, #76
	add	r1, r1, #128
	bl	Bs_Get_Matrix
	b	.L257
.L267:
	strb	r10, [r4, #3645]
	strb	r10, [r4, #3646]
	b	.L269
.L270:
	add	r0, r6, #20480
	mov	r3, #1
	ldr	r4, [r8, #52]
	mov	r1, r7
	mov	r2, #604
	strb	r3, [r5, #1575]
	strb	r3, [r5, #797]
	add	r0, r0, #132
	strb	r3, [r5, #1576]
	blx	r4
	sub	r0, fp, #76
	bl	BsPos
	b	.L327
.L375:
	.align	2
.L374:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC8
	.word	g_VdmCharacter
	.word	.LC11
	.word	.LC12
	.word	.LC10
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC9
	.word	.LANCHOR1-4
	.word	.LANCHOR1+252
	.word	.LC16
	.word	.LC17
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vol, .-Mp4_Syntax_Vol
	.align	2
	.global	Mp4_Syntax_Vos
	.type	Mp4_Syntax_Vos, %function
Mp4_Syntax_Vos:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	add	r5, r0, #20480
	add	r4, r0, #16384
	sub	r0, fp, #52
	bl	BsInit
	mov	r3, #0
	mov	r1, #32
	str	r3, [r5, #828]
	sub	r0, fp, #52
	bl	BsSkip
	sub	r0, fp, #52
	mov	r1, #8
	bl	BsGet
	sub	r3, r0, #1
	sub	r2, r0, #240
	cmp	r2, #5
	cmphi	r3, #2
	str	r0, [r4, #3608]
	movls	r3, #1
	movhi	r3, #0
	cmp	r0, #8
	orreq	r3, r3, #1
	cmp	r3, #0
	strne	r0, [r5, #828]
	movne	r3, #1
	strneb	r3, [r5, #1572]
	bne	.L378
	cmp	r0, #0
	beq	.L383
	ldr	r2, .L384
	strb	r3, [r5, #1572]
	ldr	r4, [r2]
	cmp	r4, #0
	beq	.L378
	ldr	r0, [r5, #2496]
	mov	r2, r3
	mov	r1, #102
	blx	r4
.L378:
	sub	r0, fp, #52
	bl	BsPos
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L383:
	mov	r2, r0
	ldr	r1, .L384+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #1
	strb	r3, [r5, #1572]
	ldr	r3, [r4, #3608]
	str	r3, [r5, #828]
	b	.L378
.L385:
	.align	2
.L384:
	.word	g_event_report
	.word	.LC18
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vos, .-Mp4_Syntax_Vos
	.align	2
	.global	Frame_Init
	.type	Frame_Init, %function
Frame_Init:
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
	UNWIND(.pad #60)
	sub	sp, sp, #60
	mov	r5, r2
	sub	r2, r1, #32
	sub	r3, r5, #32
	cmp	r3, #2128
	cmpcc	r2, #3808
	mov	r4, r1
	mov	r7, r0
	bcs	.L425
	add	r6, r0, #20480
	ldr	r3, [r6, #1596]
	ldr	r8, [r3, #732]
	ldr	r2, [r3, #28]
	cmp	r8, #0
	bne	.L389
	cmp	r2, #25
	beq	.L426
.L416:
	mov	r10, #5
	mov	r2, #2
	str	r2, [fp, #-76]
	mov	r2, #3
	str	r2, [fp, #-72]
.L390:
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L401
	ldr	r2, .L429
	ldr	r9, [r2, #64]
	cmp	r9, #0
	beq	.L403
	ldr	r1, [r3, #20]
	mov	ip, #0
	ldr	r0, [r3, #16]
	mov	r2, #40
	ldr	r3, [r6, #2496]
	ldr	r8, .L429+4
	str	ip, [sp, #8]
	mov	ip, #2
	str	r3, [sp, #12]
	mov	r3, r5
	str	r2, [sp, #4]
	mov	r2, r4
	str	r8, [sp, #16]
	str	ip, [sp]
	blx	r9
	cmp	r0, #0
	bne	.L403
	ldr	r2, [r8, #56]
	ldr	r3, [r8, #48]
	cmp	r2, #1
	ble	.L405
	cmp	r3, #2
	ble	.L405
	ldr	r0, [r8, #464]
	str	r0, [r6, #1616]
	bl	MEM_Phy2Vir
	str	r0, [r6, #1604]
.L401:
	ldr	r3, .L429+8
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6, #1596]
	str	r4, [fp, #-60]
	str	r5, [fp, #-56]
	ldr	r3, [r3, #28]
	str	r4, [fp, #-52]
	cmp	r3, #24
	str	r5, [fp, #-48]
	beq	.L407
	ldrb	r2, [fp, #-72]	@ zero_extendqisi2
	ldrb	r3, [fp, #-76]	@ zero_extendqisi2
	strb	r10, [fp, #-62]
	strb	r2, [fp, #-63]
.L412:
	sub	r1, fp, #64
	ldr	r0, [r6, #2496]
	strb	r3, [fp, #-61]
	bl	FSP_ConfigInstance
	subs	r8, r0, #0
	bne	.L408
	ldr	r1, [r6, #1596]
	sub	r3, fp, #68
	ldr	r0, [r6, #2496]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L427
	cmp	r0, #0
	moveq	r3, #1
	streq	r3, [r6, #2500]
	bne	.L410
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L425:
	mov	r3, r5
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L429+12
	bl	dprint_vfmw
	ldr	r3, .L429+16
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L423
	add	r7, r7, #20480
	mov	r3, #0
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r7, #2496]
	mvn	r8, #0
	blx	r4
.L419:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L397:
	mov	r3, r5
	str	r1, [sp, #4]
	str	r2, [sp]
.L422:
	mov	r2, r4
	ldr	r1, .L429+20
	mov	r0, #0
	bl	dprint_vfmw
.L423:
	mvn	r8, #0
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L389:
	cmp	r2, #25
	bne	.L416
	ldr	r2, [r3, #692]
	ldr	r1, [r3, #696]
	cmp	r4, r2
	bhi	.L397
	cmp	r5, r1
	bhi	.L397
	ldr	r1, [r3, #720]
	ldr	r2, [r3, #716]
	cmp	r1, #0
	add	r1, r2, #2
	str	r1, [fp, #-72]
	moveq	r2, #1
	streq	r2, [fp, #-76]
	bne	.L428
.L399:
	ldr	r10, [r3, #740]
	b	.L390
.L407:
	mov	r3, #1
	strb	r10, [fp, #-62]
	strb	r3, [fp, #-63]
	b	.L412
.L428:
	add	r2, r2, #1
	cmp	r2, #17
	movge	r2, #17
	str	r2, [fp, #-76]
	b	.L399
.L426:
	ldr	r0, [r3, #692]
	cmp	r1, r0
	ldrhi	r1, [r3, #696]
	bhi	.L392
	ldr	r2, [r3, #696]
	cmp	r5, r2
	mov	r1, r2
	bhi	.L392
	ldr	r1, [r6, #2500]
	cmp	r1, #1
	beq	.L419
	ldr	ip, [r3, #720]
	ldr	r1, [r3, #716]
	cmp	ip, #0
	add	ip, r1, #2
	str	ip, [fp, #-72]
	moveq	r1, #1
	streq	r1, [fp, #-76]
	beq	.L395
	add	r1, r1, #1
	cmp	r1, #17
	movge	r1, #17
	str	r1, [fp, #-76]
.L395:
	mov	r5, r2
	mov	r4, r0
	ldr	r10, [r3, #740]
	b	.L390
.L427:
	add	r0, r7, #22528
	add	r0, r0, #96
	bl	ResetVoQueue
.L410:
	ldr	r1, .L429+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r8, #0
	mov	r3, #0
	str	r3, [r6, #2500]
	b	.L419
.L405:
	ldr	r1, .L429+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L419
.L403:
	ldr	r1, .L429+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L419
.L408:
	ldr	r1, .L429+36
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L419
.L392:
	str	r1, [sp, #4]
	mov	r3, r5
	str	r0, [sp]
	b	.L422
.L430:
	.align	2
.L429:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	.word	g_event_report
	.word	.LC20
	.word	.LC23
	.word	.LC22
	.word	.LC21
	.word	.LC24
	UNWIND(.fnend)
	.size	Frame_Init, .-Frame_Init
	.align	2
	.global	Mp4_RecordVFMWState
	.type	Mp4_RecordVFMWState, %function
Mp4_RecordVFMWState:
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
	.size	Mp4_RecordVFMWState, .-Mp4_RecordVFMWState
	.global	__aeabi_uidiv
	.align	2
	.global	Mp4_RecordFrameAtr
	.type	Mp4_RecordFrameAtr, %function
Mp4_RecordFrameAtr:
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
	add	r5, r0, #20480
	mov	r6, r0
	mov	r4, r1
	ldrb	r3, [r5, #847]	@ zero_extendqisi2
	cmp	r3, #15
	beq	.L452
	sub	r2, r3, #2
	cmp	r2, #1
	movls	r7, #1
	bls	.L434
	sub	r2, r3, #4
	cmp	r2, #1
	movls	r7, #2
	bls	.L434
	cmp	r3, #1
	moveq	r7, #5
	movne	r7, #0
.L434:
	mov	r1, r4
	ldr	r0, [r5, #2496]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L432
	ldr	r3, [r5, #1512]
	mov	r1, r7
	str	r3, [r4, #68]
	ldr	r3, [r5, #1508]
	str	r3, [r4, #72]
	bl	SetAspectRatio
	ldr	r3, [r5, #1596]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L453
.L440:
	ldr	r3, [r5, #1512]
	add	r6, r6, #22528
	ldrb	ip, [r4, #64]	@ zero_extendqisi2
	mov	r0, #0
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	add	r6, r6, #64
	str	r3, [r4, #76]
	add	r3, r4, #536
	ldr	r1, [r5, #1508]
	str	r1, [r4, #80]
	add	r1, r4, #568
	ldr	lr, [r5, #1512]
	mov	lr, lr, lsr #1
	str	lr, [r4, #84]
	ldr	lr, [r5, #1508]
	mov	lr, lr, lsr #1
	str	lr, [r4, #88]
	ldr	lr, [r5, #2076]
	str	lr, [r4, #160]
	ldr	lr, [r5, #2072]
	str	lr, [r4, #156]
	ldrb	lr, [r5, #1448]	@ zero_extendqisi2
	bfi	ip, lr, #0, #2
	strb	ip, [r4, #64]
	ldrb	lr, [r5, #825]	@ zero_extendqisi2
	bfi	ip, lr, #5, #3
	strb	ip, [r4, #64]
	ldrb	ip, [r5, #854]	@ zero_extendqisi2
	and	ip, ip, #1
	bfi	r2, ip, #0, #2
	uxtb	r2, r2
	orr	r2, r2, #12
	strb	r2, [r4, #65]
	ldrb	ip, [r5, #1453]	@ zero_extendqisi2
	bfi	r2, ip, #4, #2
	strb	r2, [r4, #65]
	ldr	r2, [r4, #64]
	mov	ip, r0
	bfi	r2, r7, #14, #3
	str	r2, [r4, #64]
	ldrb	lr, [r5, #812]	@ zero_extendqisi2
	mov	r2, r2, lsr #16
	bfi	r2, lr, #1, #1
	strb	r2, [r4, #66]
	ldr	r2, [r5, #816]
	str	r2, [r4, #120]
	ldrb	r2, [r5, #1448]	@ zero_extendqisi2
	and	r2, r2, #3
	str	r2, [r4, #56]
	ldrb	r2, [r5, #1448]	@ zero_extendqisi2
	and	r2, r2, #3
	str	r2, [r4, #60]
	str	r0, [r4, #52]
.L441:
	ldr	r2, [r6, #4]!
	mov	r7, #0
	str	r2, [r3, #8]!
	cmp	r3, r1
	str	ip, [r3, #4]
	bne	.L441
	ldr	r3, [r5, #1596]
	add	ip, r4, #592
	add	lr, r4, #608
	ldr	r1, .L454
	mov	r0, #29
	ldrd	r2, [r3, #64]
	strd	r2, [ip, #-8]
	ldr	r3, [r5, #1596]
	ldrd	r2, [r3, #80]
	strd	r2, [ip]
	ldr	r3, [r5, #1596]
	ldrd	r2, [r3, #96]
	strd	r2, [lr, #-8]
	mvn	r2, #0
	ldr	lr, [r5, #1596]
	mvn	r3, #0
	ldr	lr, [lr, #112]
	str	lr, [r4]
	ldr	lr, [r5, #1596]
	ldr	lr, [lr, #116]
	str	lr, [r4, #4]
	ldr	lr, [r5, #1596]
	ldr	lr, [lr, #120]
	str	lr, [r4, #8]
	ldr	lr, [r5, #1596]
	ldr	lr, [lr, #136]
	str	lr, [r4, #12]
	ldr	lr, [r5, #1596]
	strd	r2, [lr, #64]
	ldrd	r8, [ip]
	ldrd	r2, [ip, #-8]
	strd	r8, [sp]
	bl	dprint_vfmw
	mov	r3, #8
	mov	r2, #2
	strb	r7, [r4, #284]
	str	r2, [r4, #296]
	mov	r2, #1
	strb	r7, [r4, #291]
	str	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	strb	r2, [r4, #289]
.L432:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L453:
	ldr	r3, [r4, #72]
	add	r8, r4, #512
	ldr	r2, [r4, #112]
	add	r3, r3, #15
	ldr	ip, [r4, #36]
	mov	r1, r2, asl #4
	mov	r3, r3, lsr #4
	add	r9, ip, r2
	mul	r3, r3, r1
	add	lr, r3, ip
	str	lr, [r4, #40]
	ldrd	r0, [r8, #-8]
	add	r2, lr, r2
	adds	r0, r0, r3
	adc	r1, r1, r3, asr #31
	strd	r0, [r8]
	str	lr, [r4, #24]
	str	r2, [r4, #32]
	str	r9, [r4, #28]
	str	ip, [r4, #20]
	b	.L440
.L452:
	ldr	r2, [r5, #876]
	ldr	r1, [r5, #880]
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r7, #0
	beq	.L434
	ldr	r3, [r5, #928]
	mul	r1, r3, r1
	cmp	r1, #0
	beq	.L443
	ldr	r0, [r5, #924]
	mov	r2, r2, asl #10
	mul	r0, r0, r2
	bl	__aeabi_uidiv
	movw	r3, #1364
	cmp	r0, r3
	movw	r3, #1819
	rsble	r7, r0, #1360
	subgt	r7, r0, #1360
	addle	r7, r7, #5
	subgt	r7, r7, #5
	cmp	r0, r3
	rsble	r0, r0, #1808
	subgt	r0, r0, #1808
	addle	r0, r0, #12
	subgt	r0, r0, #12
	cmp	r7, r0
	movlt	r7, #1
	movge	r7, #2
	b	.L434
.L443:
	mov	r7, r1
	b	.L434
.L455:
	.align	2
.L454:
	.word	.LC25
	UNWIND(.fnend)
	.size	Mp4_RecordFrameAtr, .-Mp4_RecordFrameAtr
	.align	2
	.global	Mp4_Frame_Atr
	.type	Mp4_Frame_Atr, %function
Mp4_Frame_Atr:
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
	add	r4, r0, #20480
	mov	r5, r0
	mov	r1, #1
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #4
	strb	r3, [r0, #2]
	ldr	r0, [r4, #2496]
	ldreq	r2, .L466
	moveq	r3, r0, asl #5
	subeq	r3, r3, r0, asl #3
	addeq	r3, r3, r2
	ldreq	r2, [r3, #4]
	addeq	r2, r2, #1
	streq	r2, [r3, #4]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #2524]
	blt	.L459
	ldr	r3, [r4, #2500]
	cmp	r3, #0
	beq	.L459
	mov	r1, r0
	mov	r0, r5
	bl	Mp4_RecordFrameAtr
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2080]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L459:
	ldr	r1, .L466+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L461
	ldr	r1, [r6, #544]
	add	r7, r6, #560
	ldr	r0, [r4, #2496]
	add	r8, r6, #576
	bl	FreeUsdByDec
	ldr	r1, [r6, #552]
	ldr	r0, [r4, #2496]
	add	r9, r6, #544
	bl	FreeUsdByDec
	ldr	r1, [r6, #560]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	ldr	r1, [r6, #568]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r9]
	strd	r0, [r7, #-8]
	strd	r0, [r7]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2508]
	str	r3, [r4, #2516]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2516]
	str	r0, [r4, #2508]
.L461:
	add	r1, r5, #22528
	mov	r3, #0
	add	r1, r1, #96
	str	r3, [r4, #2504]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearNotInVoQueue
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L467:
	.align	2
.L466:
	.word	g_VfmwChanStat+8
	.word	.LC26
	UNWIND(.fnend)
	.size	Mp4_Frame_Atr, .-Mp4_Frame_Atr
	.align	2
	.global	Mp4_Set_DecPar
	.type	Mp4_Set_DecPar, %function
Mp4_Set_DecPar:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r3, .L489
	mov	r6, r2
	mov	r4, r0
	mov	r2, #48
	sub	r0, fp, #84
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	ldrb	r3, [r6, #6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L486
	ldr	r3, [r6, #92]
	add	r5, r4, #20480
	mov	r1, #0
	bic	r3, r3, #3
	str	r3, [r4, #1208]
	ldr	r3, [r5, #1584]
	and	r2, r3, #3
	str	r3, [r4, #1220]
	ldr	r3, [r5, #1580]
	str	r3, [r4, #1056]
	ldr	r3, [r5, #1592]
	add	r2, r3, r2, lsl #3
	str	r2, [r4, #1228]
	ldr	r2, [r5, #1588]
	rsb	r3, r3, r2, lsl #3
	str	r3, [r4, #1236]
	ldr	r3, [r6, #92]
	str	r3, [r4, #1224]
	ldr	r3, [r6, #80]
	str	r3, [r4, #1060]
	ldr	r3, [r6, #92]
	and	r3, r3, #3
	mov	r3, r3, asl #3
	str	r3, [r4, #1232]
	ldr	r3, [r6, #96]
	str	r1, [r4, #1216]
	mov	r3, r3, asl #3
	str	r3, [r4, #1240]
.L470:
	ldr	r2, [r5, #1512]
	add	r8, r4, #1040
	add	r6, r4, #12288
	add	r3, r2, #15
	mov	r3, r3, lsr #4
	strh	r3, [r8, #164]	@ movhi
	ldr	r1, [r5, #1508]
	add	r3, r1, #15
	mov	r3, r3, lsr #4
	strh	r3, [r8, #166]	@ movhi
	ldrb	r3, [r5, #1448]	@ zero_extendqisi2
	strb	r3, [r4, #1040]
	ldrb	r0, [r5, #858]	@ zero_extendqisi2
	strb	r0, [r4, #1041]
	ldrb	r0, [r5, #805]	@ zero_extendqisi2
	strb	r0, [r4, #1042]
	ldrb	r0, [r5, #1455]	@ zero_extendqisi2
	strb	r0, [r4, #1043]
	ldrb	r0, [r5, #1460]	@ zero_extendqisi2
	strb	r0, [r4, #1044]
	ldrb	r0, [r5, #1459]	@ zero_extendqisi2
	strb	r0, [r4, #1045]
	ldr	r0, [r5, #912]
	strb	r0, [r4, #1046]
	ldrb	r0, [r5, #1456]	@ zero_extendqisi2
	strb	r0, [r4, #1047]
	ldrb	r0, [r5, #1457]	@ zero_extendqisi2
	strb	r0, [r4, #1048]
	ldrb	r0, [r5, #1452]	@ zero_extendqisi2
	strb	r0, [r4, #1049]
	ldrb	r0, [r5, #863]	@ zero_extendqisi2
	strb	r0, [r4, #1050]
	ldrb	r0, [r5, #861]	@ zero_extendqisi2
	strb	r0, [r4, #1051]
	ldrb	r0, [r5, #1450]	@ zero_extendqisi2
	strb	r0, [r4, #1052]
	ldrb	r0, [r5, #1454]	@ zero_extendqisi2
	strb	r0, [r4, #1053]
	ldrb	r0, [r5, #1453]	@ zero_extendqisi2
	strb	r0, [r4, #1054]
	ldrb	r0, [r5, #854]	@ zero_extendqisi2
	strb	r0, [r4, #1055]
	ldr	r0, [r5, #1544]
	str	r0, [r4, #1244]
	ldr	r0, [r5, #1540]
	str	r0, [r4, #1248]
	ldrb	r0, [r5, #808]	@ zero_extendqisi2
	strb	r0, [r4, #1194]
	ldrb	r0, [r5, #807]	@ zero_extendqisi2
	strb	r0, [r4, #1193]
	ldrb	r0, [r5, #806]	@ zero_extendqisi2
	strb	r0, [r4, #1192]
	ldrb	r0, [r5, #809]	@ zero_extendqisi2
	strb	r0, [r4, #1195]
	ldrb	r0, [r5, #810]	@ zero_extendqisi2
	strb	r0, [r4, #1196]
	ldrb	r0, [r5, #811]	@ zero_extendqisi2
	strb	r0, [r4, #1197]
	str	r1, [r6, #3360]
	str	r2, [r6, #3364]
	ldrb	r2, [r5, #856]	@ zero_extendqisi2
	cmp	r2, #2
	cmpeq	r3, #3
	str	r2, [r6, #3368]
	moveq	r3, #1
	movne	r3, #0
	beq	.L487
	ldrb	r2, [r5, #869]	@ zero_extendqisi2
	str	r3, [r6, #3372]
	str	r3, [r6, #3380]
	str	r2, [r6, #3376]
	str	r3, [r6, #3384]
	str	r3, [r6, #3388]
	str	r3, [r6, #3392]
	str	r3, [r6, #3396]
	str	r3, [r6, #3400]
	str	r3, [r6, #3404]
	str	r3, [r6, #3408]
.L472:
	ldr	r1, [r5, #2524]
	ldr	r0, [r5, #2496]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #2508]
	mov	r7, r0
	ldr	r0, [r5, #2496]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #2516]
	mov	r9, r0
	ldr	r0, [r5, #2496]
	bl	FSP_GetLogicFs
	cmp	r7, #0
	cmpne	r9, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L488
	ldr	ip, [r7, #28]
	ldr	r1, [r7, #32]
	cmp	ip, #0
	beq	.L476
	cmp	r1, #0
	beq	.L476
	ldr	r3, [r7, #8]
	add	ip, r4, #21248
	add	r1, r4, #21504
	add	r2, r4, #1120
	add	ip, ip, #160
	add	r1, r1, #160
	str	r3, [r4, #1268]
	add	r2, r2, #7
	ldr	r3, [r0, #8]
	str	r3, [r4, #1272]
	ldr	r3, [r0, #28]
	add	r0, r4, #1056
	add	r0, r0, #7
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #1264]
	ldr	r3, [r9, #28]
	cmp	r3, #0
	ldreq	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #1260]
	ldr	r3, [r7, #28]
	ldr	r3, [r3, #8]
	str	r3, [r4, #1252]
	mov	r3, #0
	ldr	lr, [r7, #32]
	ldr	lr, [lr, #8]
	str	lr, [r6, #3328]
	ldr	lr, [r7, #32]
	ldr	lr, [lr, #24]
	str	lr, [r6, #3340]
	ldr	lr, [r7, #32]
	ldr	lr, [lr, #28]
	str	lr, [r6, #3344]
	ldr	lr, [r7, #32]
	ldr	lr, [lr, #60]
	str	lr, [r6, #3348]
	ldr	lr, [r7, #32]
	ldr	lr, [lr, #44]
	str	lr, [r6, #3352]
	ldr	lr, [r7, #32]
	ldr	lr, [lr, #48]
	str	lr, [r6, #3356]
.L482:
	ldr	lr, [ip, #4]!
	add	r3, r3, #1
	cmp	r3, #64
	strb	lr, [r0, #1]!
	ldr	lr, [r1, #4]!
	strb	lr, [r2, #1]!
	bne	.L482
	ldrh	r1, [r8, #164]
	ldrh	r3, [r8, #166]
	ldr	r2, [r5, #1596]
	mul	r3, r3, r1
	str	r3, [r5, #1480]
	ldr	r3, [r2, #600]
	str	r3, [r6, #3412]
	ldr	r3, [r2, #652]
	str	r3, [r6, #3416]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L488:
	mov	r3, #3296
	ldr	r2, .L489+4
	ldr	r1, .L489+8
	mov	r0, #0
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L486:
	add	r5, r4, #20480
	mov	r0, #0
	ldr	r2, [r5, #1584]
	bic	r1, r2, #3
	str	r1, [r4, #1220]
	str	r2, [r4, #1208]
	and	r2, r2, #3
	ldr	r1, [r5, #1580]
	str	r1, [r4, #1056]
	ldr	r1, [r5, #1592]
	add	r2, r1, r2, lsl #3
	str	r2, [r4, #1228]
	ldr	r2, [r5, #1588]
	str	r3, [r4, #1216]
	str	r0, [r4, #1224]
	rsb	r1, r1, r2, lsl #3
	str	r0, [r4, #1232]
	str	r1, [r4, #1236]
	str	r0, [r4, #1240]
	b	.L470
.L476:
	ldr	lr, [r5, #2516]
	mov	r0, #0
	ldr	r3, [r5, #2524]
	ldr	r2, [r5, #2508]
	str	r1, [sp, #8]
	str	ip, [sp, #4]
	str	lr, [sp]
	ldr	r1, .L489+12
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L487:
	add	r0, r4, #21248
	sub	r1, fp, #84
	add	r0, r0, #28
	bl	MP4_GetGMCparam
	sub	r1, fp, #68
	ldrb	ip, [r5, #869]	@ zero_extendqisi2
	ldmia	r1, {r1, r2, r3}
	ldr	r0, [fp, #-84]
	str	ip, [r6, #3376]
	ldr	ip, [fp, #-56]
	str	r0, [r6, #3372]
	str	r1, [r6, #3380]
	ldr	r0, [fp, #-52]
	ldr	r1, [fp, #-48]
	str	r2, [r6, #3384]
	str	r3, [r6, #3388]
	ldr	r2, [fp, #-44]
	ldr	r3, [fp, #-40]
	str	ip, [r6, #3392]
	str	r0, [r6, #3396]
	str	r1, [r6, #3400]
	str	r2, [r6, #3404]
	str	r3, [r6, #3408]
	b	.L472
.L490:
	.align	2
.L489:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+1280
	.word	.LC27
	.word	.LC28
	UNWIND(.fnend)
	.size	Mp4_Set_DecPar, .-Mp4_Set_DecPar
	.align	2
	.global	Mp4_Get_DecMode
	.type	Mp4_Get_DecMode, %function
Mp4_Get_DecMode:
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
	add	r0, r0, #20480
	ldr	r3, [r0, #1628]
	cmp	r3, #2
	ldr	r3, [r0, #1596]
	beq	.L503
.L493:
	ldr	r3, [r3, #8]
	cmp	r3, #2
	beq	.L496
	cmp	r3, #1
	beq	.L502
	cmp	r3, #4
	movne	r3, #0
.L502:
	str	r3, [r0, #1628]
	ldmfd	sp, {fp, sp, pc}
.L503:
	ldr	r2, [r3, #8]
	cmp	r2, #2
	movne	r2, #1
	strne	r2, [r0, #2136]
	bne	.L493
.L496:
	mov	r3, #2
	str	r3, [r0, #1628]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Mp4_Get_DecMode, .-Mp4_Get_DecMode
	.align	2
	.global	GetTrailingOneLen
	.type	GetTrailingOneLen, %function
GetTrailingOneLen:
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
	add	r1, r0, r1
	ldrb	r3, [r1, #-1]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L507
	mov	r0, #0
.L506:
	mov	r3, r3, lsr #1
	add	r0, r0, #1
	tst	r3, #1
	bne	.L506
	cmp	r0, #0
	addne	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L507:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetTrailingOneLen, .-GetTrailingOneLen
	.align	2
	.global	MPEG4DEC_Init
	.type	MPEG4DEC_Init, %function
MPEG4DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 784
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #788)
	sub	sp, sp, #788
	mov	r4, r0
	mov	r6, r1
	mov	r0, #2
	ldr	r1, .L524
	bl	dprint_vfmw
	cmp	r6, #0
	cmpne	r4, #0
	beq	.L520
	ldr	r3, [r6, #624]
	ldr	r7, .L524+4
	cmp	r3, #1
	beq	.L521
.L515:
	add	r5, r4, #20480
	ldr	r3, [r7, #48]
	movw	r2, #23024
	mov	r1, #0
	ldr	r8, [r5, #2488]
	mov	r0, r4
	blx	r3
	add	r0, r4, #22528
	add	r0, r0, #96
	mov	r7, #0
	str	r8, [r5, #2488]
	bl	ResetVoQueue
	str	r6, [r5, #1596]
	mov	r0, r4
	str	r7, [r6, #920]
	bl	VCTRL_GetChanIDByCtx
	ldr	r8, .L524+4
	cmn	r0, #1
	str	r0, [r5, #2496]
	beq	.L522
	mov	r0, r4
	bl	Global_Data_Init
	subs	r7, r0, #0
	bne	.L517
	mov	r3, #1
	str	r7, [r5, #2112]
	ldr	r1, .L524+8
	mov	r0, #2
	str	r3, [r5, #2084]
	bl	dprint_vfmw
	ldr	r6, [r6, #624]
	cmp	r6, #1
	beq	.L523
.L514:
	mov	r0, r7
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L523:
	add	r0, r4, #21248
	ldr	r3, [r8, #52]
	sub	r1, fp, #812
	mov	r2, #776
	add	r0, r0, #28
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r8, #52]
	sub	r1, fp, #788
	mov	r2, #24
	add	r0, r0, #16
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r8, #52]
	sub	r1, fp, #764
	mov	r2, #604
	add	r0, r0, #40
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r8, #52]
	mov	r2, #7
	sub	r1, fp, #820
	add	r0, r0, #36
	blx	r3
	mov	r0, r7
	strb	r6, [r5, #2533]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L521:
	add	r1, r4, #21248
	ldr	r3, [r7, #52]
	add	r1, r1, #28
	mov	r2, #776
	sub	r0, fp, #812
	blx	r3
	add	r1, r4, #19968
	ldr	r3, [r7, #52]
	add	r1, r1, #16
	mov	r2, #24
	sub	r0, fp, #788
	blx	r3
	add	r1, r4, #19968
	ldr	r3, [r7, #52]
	add	r1, r1, #40
	mov	r2, #604
	sub	r0, fp, #764
	blx	r3
	add	r1, r4, #22016
	ldr	r3, [r7, #52]
	add	r1, r1, #36
	mov	r2, #7
	sub	r0, fp, #820
	blx	r3
	b	.L515
.L517:
	mvn	r7, #0
	b	.L514
.L520:
	movw	r2, #3442
	ldr	r1, .L524+12
	mov	r0, #0
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L514
.L522:
	mov	r0, r7
	ldr	r1, .L524+16
	bl	dprint_vfmw
	mvn	r7, #19
	b	.L514
.L525:
	.align	2
.L524:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC32
	.word	.LC30
	.word	.LC31
	UNWIND(.fnend)
	.size	MPEG4DEC_Init, .-MPEG4DEC_Init
	.align	2
	.global	MPEG4DEC_Destroy
	.type	MPEG4DEC_Destroy, %function
MPEG4DEC_Destroy:
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
	ldr	r1, .L528
	mov	r4, r0
	mov	r0, #2
	bl	dprint_vfmw
	cmp	r4, #0
	addne	r4, r4, #20480
	movne	r3, #0
	strne	r3, [r4, #2084]
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r4
	movw	r2, #3524
	ldr	r1, .L528+4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L529:
	.align	2
.L528:
	.word	.LC33
	.word	.LC30
	UNWIND(.fnend)
	.size	MPEG4DEC_Destroy, .-MPEG4DEC_Destroy
	.align	2
	.global	MPEG4DEC_RecycleImage
	.type	MPEG4DEC_RecycleImage, %function
MPEG4DEC_RecycleImage:
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
	beq	.L534
	add	r4, r4, #20480
	mov	r2, #0
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L533
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #2496]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #2496]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L533:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L534:
	movw	r2, #3928
	ldr	r1, .L535
	bl	dprint_vfmw
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L536:
	.align	2
.L535:
	.word	.LC30
	UNWIND(.fnend)
	.size	MPEG4DEC_RecycleImage, .-MPEG4DEC_RecycleImage
	.align	2
	.global	MP4_SetImgFormat
	.type	MP4_SetImgFormat, %function
MP4_SetImgFormat:
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
	add	r4, r0, #20480
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #1512]
	cmp	r3, #0
	beq	.L539
	ldr	r2, [r4, #1508]
	cmp	r2, #0
	beq	.L539
	ldr	r1, [r0, #68]
	ldr	r2, [r0, #72]
	cmp	r1, r3
	movcs	r1, r3
	str	r1, [r0, #76]
	ldr	r3, [r4, #1508]
	cmp	r2, r3
	movcs	r2, r3
	str	r2, [r0, #80]
	b	.L540
.L539:
	ldr	r2, [r0, #68]
	ldr	r3, [r0, #72]
	str	r2, [r0, #76]
	str	r3, [r0, #80]
.L540:
	ldrb	r5, [r4, #812]	@ zero_extendqisi2
	mov	r3, #8
	ldrb	r1, [r0, #66]	@ zero_extendqisi2
	mov	r2, #0
	mov	lr, #2
	mov	ip, #1
	bfi	r1, r5, #1, #1
	strb	r1, [r0, #66]
	ldr	r1, [r4, #816]
	str	lr, [r0, #296]
	strb	r2, [r0, #284]
	str	r1, [r0, #120]
	strb	r2, [r0, #291]
	str	r3, [r0, #300]
	str	r3, [r0, #308]
	str	r3, [r0, #304]
	strb	ip, [r0, #289]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP4_SetImgFormat, .-MP4_SetImgFormat
	.align	2
	.global	MPEG4DEC_GetRemainImg
	.type	MPEG4DEC_GetRemainImg, %function
MPEG4DEC_GetRemainImg:
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
	subs	r6, r0, #0
	beq	.L568
	add	r4, r6, #20480
	ldr	r3, [r4, #1596]
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L567
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L567
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetDisplay
	cmp	r0, #2
	mov	r8, r0
	beq	.L566
.L567:
	add	r5, r6, #22528
	add	r5, r5, #96
.L556:
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	GetVoLastImageID
.L566:
	mov	r0, r6
	add	r5, r6, #22528
	bl	MP4_SetImgFormat
	add	r5, r5, #96
	mov	r3, #1
	ldr	r1, [r7, #148]
	mov	r2, r3
	str	r3, [r7, #180]
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
	ldr	r0, [r4, #2496]
	mov	r1, r8
	mov	r3, r5
	str	r7, [sp]
	mov	r2, r6
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L554
	ldr	r1, [r7, #148]
	add	r8, r7, #560
	mov	r0, r6
	add	r9, r7, #544
	bl	MPEG4DEC_RecycleImage
	ldr	r1, [r7, #544]
	ldr	r0, [r4, #2496]
	mov	r6, #0
	bl	FreeUsdByDec
	mov	r7, #0
	strd	r6, [r9]
	ldr	r0, [r4, #2496]
	ldr	r1, [r8, #-8]
	bl	FreeUsdByDec
	strd	r6, [r8, #-8]
	b	.L556
.L554:
	ldr	r3, [r7, #152]
	cmp	r3, #100
	bhi	.L556
	ldr	r3, [r7, #68]
	cmp	r3, #31
	bls	.L556
	ldr	r3, [r7, #72]
	cmp	r3, #31
	movhi	r0, #0
	bls	.L556
.L563:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L568:
	movw	r2, #3988
	ldr	r1, .L569
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L563
.L570:
	.align	2
.L569:
	.word	.LC30
	UNWIND(.fnend)
	.size	MPEG4DEC_GetRemainImg, .-MPEG4DEC_GetRemainImg
	.align	2
	.global	MPEG4DEC_GetImageBuffer
	.type	MPEG4DEC_GetImageBuffer, %function
MPEG4DEC_GetImageBuffer:
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
	beq	.L578
	add	r4, r5, #20480
	ldr	r0, [r4, #2496]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #2496]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L579
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L579:
	add	r1, r5, #22528
	ldr	r0, [r4, #2496]
	add	r1, r1, #96
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L578:
	movw	r2, #4221
	ldr	r1, .L580
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L581:
	.align	2
.L580:
	.word	.LC30
	UNWIND(.fnend)
	.size	MPEG4DEC_GetImageBuffer, .-MPEG4DEC_GetImageBuffer
	.align	2
	.global	MP4_GetPacketState
	.type	MP4_GetPacketState, %function
MP4_GetPacketState:
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
	beq	.L586
	add	r3, r3, #16384
	ldr	r3, [r3, #3596]
	cmp	r3, #1
	mvnne	r0, #0
	moveq	r0, #3
	ldmfd	sp, {fp, sp, pc}
.L586:
	movw	r2, #4239
	ldr	r1, .L587
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L588:
	.align	2
.L587:
	.word	.LC30
	UNWIND(.fnend)
	.size	MP4_GetPacketState, .-MP4_GetPacketState
	.align	2
	.global	MP4_ClearCurPacket
	.type	MP4_ClearCurPacket, %function
MP4_ClearCurPacket:
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
	ldr	r1, [r1, #20]
	mov	r5, r0
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L590
	ldrb	r3, [r4, #86]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L591
.L590:
	ldr	r3, .L592
	mov	r0, r4
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L591:
	mov	r0, r5
	ldr	r1, [r4, #100]
	bl	SM_ReleaseStreamSeg
	b	.L590
.L593:
	.align	2
.L592:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MP4_ClearCurPacket, .-MP4_ClearCurPacket
	.align	2
	.global	MP4_ClearCurPic
	.type	MP4_ClearCurPic, %function
MP4_ClearCurPic:
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
	subs	r5, r0, #0
	beq	.L602
	add	r8, r5, #16384
	add	r3, r5, #20480
	ldr	r6, [r8, #3588]
	ldr	r7, [r3, #2496]
	cmp	r6, #0
	addgt	r5, r5, #15872
	movgt	r4, #0
	ble	.L599
.L598:
	add	r4, r4, #1
	ldr	r1, [r5, #4]!
	mov	r0, r7
	bl	SM_ReleaseStreamSeg
	cmp	r6, r4
	bne	.L598
.L599:
	mov	r3, #0
	str	r3, [r8, #3588]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L602:
	movw	r2, #4271
	ldr	r1, .L603
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L604:
	.align	2
.L603:
	.word	.LC30
	UNWIND(.fnend)
	.size	MP4_ClearCurPic, .-MP4_ClearCurPic
	.align	2
	.global	Vdm_Mem_Move
	.type	Vdm_Mem_Move, %function
Vdm_Mem_Move:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 8
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
	mov	r9, r3
	ldr	r3, [fp, #8]
	mov	r4, r0
	mov	r5, r1
	mov	r0, #2
	ldr	r1, .L616
	mov	r10, r2
	ldr	r8, [fp, #4]
	add	r7, r4, #20480
	str	r3, [fp, #-48]
	ldr	r6, [fp, #12]
	bl	dprint_vfmw
	add	r1, r4, #12288
	ldr	r3, [fp, #-48]
	str	r10, [r4, #1252]
	add	r6, r6, #15
	str	r9, [r1, #3328]
	add	r3, r3, #15
	ldr	lr, [r5, #8]
	movw	r2, #1206
	movw	ip, #1204
	str	r8, [r4, #1260]
	mov	r3, r3, lsr #4
	mov	r6, r6, lsr #4
	str	lr, [r4, #1268]
	add	r0, r4, #1040
	strh	r3, [r4, ip]	@ movhi
	strh	r6, [r4, r2]	@ movhi
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #24]
	str	r3, [r1, #3340]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #28]
	str	r3, [r1, #3344]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #60]
	str	r3, [r1, #3348]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #44]
	str	r3, [r1, #3352]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #48]
	str	r3, [r1, #3356]
	ldr	r3, [r7, #1596]
	ldr	r2, [r3, #600]
	str	r2, [r1, #3412]
	ldr	r2, [r3, #652]
	str	r2, [r1, #3416]
	str	r0, [r4, #1036]
	ldr	r2, [r3, #912]
	cmp	r2, #1
	beq	.L614
	cmp	r2, #2
	beq	.L615
.L607:
	mov	r3, #1
	strb	r3, [r4, #1198]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L614:
	cmp	r0, #0
	beq	.L607
	mov	r2, #0
	str	r2, [r4, #1036]
	ldr	r0, [r7, #2496]
	ldr	r1, [r7, #2524]
	bl	FSP_SetDisplay
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MP4_ClearCurPic
.L615:
	ldr	r3, [r3, #916]
	cmp	r0, #0
	cmpne	r3, #0
	ble	.L607
	mov	r2, #0
	str	r2, [r4, #1036]
	ldr	r0, [r7, #2496]
	ldr	r1, [r7, #2524]
	bl	FSP_SetDisplay
	ldr	r2, [r7, #1596]
	mov	r0, r4
	ldr	r3, [r2, #916]
	sub	r3, r3, #1
	str	r3, [r2, #916]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MP4_ClearCurPic
.L617:
	.align	2
.L616:
	.word	.LC34
	UNWIND(.fnend)
	.size	Vdm_Mem_Move, .-Vdm_Mem_Move
	.align	2
	.global	MP4_GetScdUpMsg
	.type	MP4_GetScdUpMsg, %function
MP4_GetScdUpMsg:
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
	add	r3, r0, #20480
	add	r5, r0, #22784
	add	r5, r5, #236
	add	r0, r0, #15872
	ldr	r3, [r3, #1596]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L620
.L619:
	ldr	r6, .L621
	add	r4, r1, #72
	mov	r2, #4
	mov	r1, r4
	ldr	r3, [r6, #52]
	blx	r3
	ldr	r3, [r6, #52]
	mov	r1, r4
	mov	r0, r5
	mov	r2, #4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L620:
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L619
	ldr	r3, .L621
	mov	r1, r5
	mov	r2, #4
	ldr	r3, [r3, #52]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L622:
	.align	2
.L621:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MP4_GetScdUpMsg, .-MP4_GetScdUpMsg
	.align	2
	.global	Mp4_Check_Slice_NotSH
	.type	Mp4_Check_Slice_NotSH, %function
Mp4_Check_Slice_NotSH:
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
	add	r3, r0, #16384
	add	r1, r0, #20480
	ldrb	r3, [r3, #3643]	@ zero_extendqisi2
	ldrb	r2, [r1, #736]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L631
	add	r3, r0, #12288
	ldrb	r3, [r3, #3584]	@ zero_extendqisi2
	tst	r3, #120
	bne	.L631
	add	r0, r0, #15872
	ldrh	r0, [r0]
	ubfx	r0, r0, #7, #4
	add	r0, r0, #17
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L625
.L627:
	.word	.L632
	.word	.L628
	.word	.L629
	.word	.L628
.L631:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L632:
	mov	r3, #17
.L626:
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L629:
	ldrb	r3, [r1, #745]	@ zero_extendqisi2
	ldrb	r2, [r1, #744]	@ zero_extendqisi2
	cmp	r3, r2
	movcc	r3, r2
	cmp	r3, #1
	addgt	r3, r3, #16
	movle	r3, #18
	b	.L626
.L628:
	ldrb	r3, [r1, #744]	@ zero_extendqisi2
	add	r3, r3, #16
	b	.L626
.L625:
	ldr	r1, .L635
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L636:
	.align	2
.L635:
	.word	.LC35
	UNWIND(.fnend)
	.size	Mp4_Check_Slice_NotSH, .-Mp4_Check_Slice_NotSH
	.align	2
	.global	Mp4_Combine_SliceData
	.type	Mp4_Combine_SliceData, %function
Mp4_Combine_SliceData:
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
	add	r2, r0, #16384
	add	r3, r0, #12288
	add	r0, r0, #1264
	ldr	ip, [r2, #3592]
	add	r0, r0, #12
	ldr	r2, [r3, #3324]
	tst	ip, #2
	beq	.L638
	ldrb	lr, [r3, #3430]	@ zero_extendqisi2
	cmp	lr, #1
	beq	.L652
	cmp	lr, #0
	bne	.L646
	ldrb	ip, [r3, #3510]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L646
	mov	ip, r2, asl #5
	sub	r2, ip, r2, asl #2
	sub	r2, r2, #28
	add	r2, r0, r2
	ldr	r0, [r2, #12]
	cmp	r0, #0
	bne	.L648
	ldr	r0, [r2, #20]
	cmp	r0, #0
	bne	.L648
	ldr	ip, [r2, #8]
	add	r1, ip, r1, lsl #3
	str	r1, [r2, #8]
	ldr	r1, [r3, #3516]
	str	r1, [r2, #20]
	ldr	r3, [r3, #3520]
	mov	r3, r3, asl #3
	str	r3, [r2, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L652:
	sub	r4, r2, #1
	movw	ip, #510
	cmp	r4, ip
	bhi	.L653
	mov	ip, r2, asl #5
	sub	r2, ip, r2, asl #2
	sub	r2, r2, #28
	add	r2, r0, r2
	ldr	r0, [r2, #12]
	cmp	r0, #0
	beq	.L642
	ldr	ip, [r2, #20]
	cmp	ip, #0
	beq	.L642
	ldr	r3, [r3, #3436]
	cmp	ip, r3
	bhi	.L654
	add	r1, r0, r1, lsl #3
	mov	r0, #0
	str	r1, [r2, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L642:
	ldr	ip, [r3, #3436]
	ldr	r0, [r2, #16]
	cmp	ip, r0
	movls	r1, r1, asl #3
	strls	r1, [r2, #12]
	ldrls	r3, [r3, #3436]
	movhi	r0, #0
	ldrhi	r3, [r2, #8]
	movls	r0, #0
	addhi	r1, r3, r1, lsl #3
	strls	r3, [r2, #20]
	strhi	r1, [r2, #8]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L646:
	movw	r2, #4428
	ldr	r1, .L655
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L648:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L638:
	movw	r2, #4434
	ldr	r1, .L655
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L653:
	mov	r0, lr
	ldr	r1, .L655+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L654:
	mov	r0, lr
	movw	r2, #4404
	ldr	r1, .L655
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L656:
	.align	2
.L655:
	.word	.LC37
	.word	.LC36
	UNWIND(.fnend)
	.size	Mp4_Combine_SliceData, .-Mp4_Combine_SliceData
	.align	2
	.global	MP4_Check_StreamType
	.type	MP4_Check_StreamType, %function
MP4_Check_StreamType:
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
	add	r2, r0, #12288
	add	r0, r0, #20480
	ldrb	r3, [r2, #3584]	@ zero_extendqisi2
	tst	r3, #1
	bne	.L658
	mov	r3, #2
	strb	r3, [r0, #805]
	ldr	r3, [r1]
	mov	r3, r3, lsr #8
	sub	r3, r3, #128
	cmp	r3, #3
	ldrlsb	r3, [r2, #3584]	@ zero_extendqisi2
	orrls	r3, r3, #2
	strlsb	r3, [r2, #3584]
.L659:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L658:
	mov	r2, #196
	mov	r3, #1
	str	r2, [r1]
	strb	r3, [r0, #805]
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP4_Check_StreamType, .-MP4_Check_StreamType
	.align	2
	.global	MP4_Clean_HeadPacket
	.type	MP4_Clean_HeadPacket, %function
MP4_Clean_HeadPacket:
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
	add	r3, r0, #20480
	mov	r8, r0
	ldr	r6, [r3, #2052]
	ldr	r7, [r3, #2496]
	cmp	r6, #64
	movge	r6, #64
	cmp	r6, #0
	addgt	r5, r0, #22272
	movgt	r4, #0
	ble	.L663
.L662:
	add	r4, r4, #1
	ldr	r1, [r5, #4]!
	mov	r0, r7
	bl	SM_ReleaseStreamSeg
	cmp	r4, r6
	bne	.L662
.L663:
	ldr	r3, .L665
	add	r0, r8, #22016
	add	r0, r0, #96
	mov	r2, #440
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L666:
	.align	2
.L665:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MP4_Clean_HeadPacket, .-MP4_Clean_HeadPacket
	.align	2
	.global	MPEG4DEC_VDMPostProc
	.type	MPEG4DEC_VDMPostProc, %function
MPEG4DEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r2, #0
	cmpne	r0, #0
	mov	r6, r1
	mov	r5, r0
	moveq	r2, #1
	movne	r2, #0
	beq	.L714
	ldr	r3, [r0, #1036]
	add	r4, r0, #20480
	ldr	r0, .L721
	mov	r1, r2
	add	ip, r3, #12288
	movw	r2, #14668
	ldrb	lr, [r3, #159]	@ zero_extendqisi2
	ldr	r3, [r0, #48]
	add	r0, r5, #1040
	strb	lr, [r4, #812]
	ldr	ip, [ip, #2372]
	str	ip, [r4, #816]
	blx	r3
	mov	r0, r5
	bl	MP4_ClearCurPic
	mov	r0, r5
	bl	MP4_Clean_HeadPacket
	str	r6, [r4, #2080]
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #2516]
	mov	r6, r0
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	cmp	r6, #0
	mov	r8, r0
	beq	.L715
	ldr	r2, [r4, #2088]
	mov	r0, #11
	ldr	r1, .L721+4
	bl	dprint_vfmw
	ldrb	r2, [r4, #1448]	@ zero_extendqisi2
	ldr	r1, .L721+8
	mov	r0, #11
	bl	dprint_vfmw
	ldr	r3, [r4, #2080]
	add	r1, r5, #22528
	add	r1, r1, #68
	str	r3, [r6, #152]
	ldr	r0, [r4, #2496]
	bl	Mp4_ClearUsrData
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L671
	ldr	r2, [r4, #1596]
	ldr	r3, [r4, #2080]
	ldr	r1, [r2]
	cmp	r3, r1
	bhi	.L716
.L671:
	mov	r3, #0
	mov	r0, r5
	str	r3, [r4, #2136]
	bl	MP4_SetImgFormat
	ldr	r3, [r4, #1596]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L717
	ldr	r1, [r4, #2524]
	ldrb	r6, [r4, #1448]	@ zero_extendqisi2
	ldr	r7, [r4, #1540]
	str	r1, [r4, #2528]
.L677:
	cmn	r1, #1
	beq	.L679
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L718
	cmp	r7, #0
	cmpeq	r6, #4
	beq	.L719
	ldr	r2, [r8, #152]
	cmp	r2, #0
	beq	.L682
	ldr	r3, [r4, #1596]
	ldr	r1, [r3, #4]
	cmp	r2, r1
	bhi	.L683
.L682:
	ldr	r1, [r4, #2528]
	ldr	r0, [r4, #2496]
	bl	FSP_GetLogicFs
	subs	r7, r0, #0
	beq	.L720
	cmp	r6, #2
	beq	.L685
	ldrsb	r3, [r7, #1]
	cmp	r3, #2
	beq	.L685
	ldr	r2, [r4, #2528]
	mov	r0, #11
	ldr	r1, .L721+12
	bl	dprint_vfmw
.L679:
	ldr	r3, [r4, #2088]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #2088]
.L712:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L717:
	ldrb	ip, [r4, #1448]	@ zero_extendqisi2
	cmp	ip, #2
	beq	.L675
	ldr	r3, [r4, #2504]
	cmp	r3, #1
	ble	.L676
	ldr	r1, [r4, #2508]
	ldr	r7, [r4, #2512]
	str	r1, [r4, #2528]
	ldrb	r6, [r5]	@ zero_extendqisi2
	b	.L677
.L683:
	ldr	r3, .L721+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L688
	str	r2, [fp, #-44]
	mov	r3, #8
	str	r1, [fp, #-40]
	sub	r2, fp, #44
	mov	r1, #104
	ldr	r0, [r4, #2496]
	blx	r5
	ldr	r3, [r4, #1596]
	ldr	r2, [r8, #152]
	ldr	r1, [r3, #4]
.L688:
	mov	r3, r1
	add	r9, r8, #544
	ldr	r1, .L721+20
	mov	r0, #1
	bl	dprint_vfmw
	add	r5, r8, #560
	ldr	r1, [r8, #544]
	mov	r6, #0
	ldr	r0, [r4, #2496]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r9]
	ldr	r1, [r8, #552]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r2, #0
	ldr	r1, [r4, #2528]
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
	b	.L679
.L685:
	mov	r2, #1
	ldr	r1, [r4, #2528]
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
	add	r3, r5, #22528
	ldr	r0, [r4, #2496]
	add	r3, r3, #96
	str	r8, [sp]
	mov	r2, r5
	mov	r1, #2
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L679
	ldr	r1, [r8, #544]
	add	r9, r8, #544
	ldr	r0, [r4, #2496]
	add	r5, r8, #560
	mov	r6, #0
	mov	r7, #0
.L713:
	bl	FreeUsdByDec
	strd	r6, [r9]
	ldr	r1, [r8, #552]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r2, #0
	ldr	r0, [r4, #2496]
	ldr	r1, [r4, #2528]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L712
.L675:
	ldr	r1, [r4, #2524]
	cmp	r8, #0
	ldr	r7, [r4, #1540]
	str	r1, [r4, #2528]
	beq	.L690
	add	r0, r8, #592
	add	r6, r6, #592
	ldrd	r8, [r0, #-8]
	ldrd	r2, [r6, #-8]
	cmp	r8, r2
	sbcs	lr, r9, r3
	bge	.L690
	strd	r8, [r6, #-8]
	mov	r6, ip
	strd	r2, [r0, #-8]
	ldr	r1, [r4, #2528]
	b	.L677
.L676:
	mvn	r3, #0
	str	r3, [r4, #2528]
	b	.L679
.L690:
	mov	r6, ip
	b	.L677
.L714:
	movw	r2, #4050
	ldr	r1, .L721+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L712
.L716:
	ldr	r1, .L721+16
	ldr	r5, [r1]
	cmp	r5, #0
	beq	.L672
	str	r3, [fp, #-44]
	mov	r1, #104
	ldr	ip, [r2]
	mov	r3, #8
	sub	r2, fp, #44
	ldr	r0, [r4, #2496]
	str	ip, [fp, #-40]
	blx	r5
.L672:
	mov	r6, #1
	ldr	r1, [r4, #2516]
	str	r6, [r4, #2136]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L673
	ldr	r1, [r5, #544]
	add	r7, r5, #560
	ldr	r0, [r4, #2496]
	add	r8, r5, #576
	bl	FreeUsdByDec
	ldr	r1, [r5, #552]
	ldr	r0, [r4, #2496]
	add	r9, r5, #544
	bl	FreeUsdByDec
	ldr	r1, [r5, #560]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	ldr	r1, [r5, #568]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, r6
	strd	r0, [r9]
	strd	r0, [r7, #-8]
	strd	r0, [r7]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r2, r6
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2508]
	str	r3, [r4, #2516]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2516]
	str	r0, [r4, #2508]
.L673:
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r4, #2504]
	b	.L712
.L719:
	ldr	r1, [r4, #2496]
	add	r9, r8, #544
	ldr	r3, .L721+28
	add	r5, r8, #560
	mov	r6, #0
	mov	r7, #0
	mov	r2, r1, asl #5
	mov	r0, r1
	sub	r2, r2, r1, asl #3
	add	r3, r3, r2
	ldr	r2, [r3, #16]
	add	r2, r2, #1
	str	r2, [r3, #16]
	ldr	r1, [r8, #544]
	b	.L713
.L715:
	mov	r3, r0
	mov	r2, r6
	mov	r0, r6
	ldr	r1, .L721+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L712
.L718:
	movw	r2, #4141
	ldr	r1, .L721+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L712
.L720:
	add	r5, r8, #560
	add	r6, r8, #544
	ldr	r1, [r8, #544]
	mov	r9, #0
	ldr	r0, [r4, #2496]
	mov	r8, #0
	bl	FreeUsdByDec
	strd	r8, [r6]
	ldr	r1, [r5, #-8]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	strd	r8, [r5, #-8]
	mov	r2, r7
	ldr	r0, [r4, #2496]
	ldr	r1, [r4, #2528]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L712
.L722:
	.align	2
.L721:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC39
	.word	.LC40
	.word	.LC42
	.word	g_event_report
	.word	.LC43
	.word	.LC30
	.word	g_VfmwChanStat
	.word	.LC38
	.word	.LC41
	UNWIND(.fnend)
	.size	MPEG4DEC_VDMPostProc, .-MPEG4DEC_VDMPostProc
	.align	2
	.global	MP4_Record_SlcSegID
	.type	MP4_Record_SlcSegID, %function
MP4_Record_SlcSegID:
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
	add	r5, r0, #16384
	movw	r6, #1022
	mov	r4, r0
	ldr	r2, [r5, #3588]
	cmp	r2, r6
	bhi	.L726
	add	r1, r0, #12288
	add	r4, r0, r2, lsl #2
	add	r4, r4, #12288
	add	r3, r2, #1
	ldr	r0, [r1, #3444]
	str	r0, [r4, #3588]
	str	r3, [r5, #3588]
	ldrb	r3, [r1, #3430]	@ zero_extendqisi2
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r1, #3510]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r1, #3524]
	addeq	r2, r2, #2
	streq	r3, [r4, #3592]
	streq	r2, [r5, #3588]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L726:
	bl	MP4_Clean_HeadPacket
	mov	r0, r4
	bl	MP4_ClearCurPic
	add	r3, r4, #20480
	add	r1, r4, #15680
	ldr	r0, [r3, #2496]
	add	r1, r1, #32
	bl	MP4_ClearCurPacket
	mov	r3, r6
	ldr	r2, [r5, #3588]
	mov	r0, #0
	ldr	r1, .L727
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L728:
	.align	2
.L727:
	.word	.LC44
	UNWIND(.fnend)
	.size	MP4_Record_SlcSegID, .-MP4_Record_SlcSegID
	.align	2
	.global	Mp4_Syntax_ShortHeader
	.type	Mp4_Syntax_ShortHeader, %function
Mp4_Syntax_ShortHeader:
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
	add	r7, r0, #12288
	mov	r4, r2
	mov	r6, r0
	ldr	r2, [r7, #3324]
	mov	r5, r1
	cmp	r2, #0
	bne	.L765
.L730:
	mov	r1, r5
	mov	r2, r4
	sub	r0, fp, #76
	add	r5, r6, #20480
	bl	BsInit
	ldr	r3, .L770
	add	r0, r6, #20992
	mov	r2, #60
	mov	r1, #0
	add	r0, r0, #224
	ldr	r3, [r3, #48]
	blx	r3
	mov	r1, #22
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsSkip
	sub	r0, fp, #76
	mov	r1, #3
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #746]
	sub	r0, r0, #1
	cmp	r0, #3
	ldrls	pc, [pc, r0, asl #2]
	b	.L731
.L733:
	.word	.L732
	.word	.L734
	.word	.L735
	.word	.L736
.L736:
	mov	r2, #18
	mov	r3, #88
	strb	r2, [r5, #747]
	mov	r2, #704
	strb	r3, [r5, #748]
	mov	r3, #576
	str	r2, [r5, #1512]
	str	r3, [r5, #1508]
.L737:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	ldrb	r3, [r5, #803]	@ zero_extendqisi2
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r5, #736]
	beq	.L739
	adds	r0, r0, #0
	ldr	r3, [r5, #2136]
	movne	r0, #1
	cmp	r3, #1
	movne	r0, #0
	cmp	r0, #0
	bne	.L739
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #76
	mov	r9, r4, asl #3
	bl	BsGet
	mov	r1, #1
	mov	r4, #0
	uxtb	r0, r0
	cmp	r0, #0
	strneb	r0, [r5, #743]
	sub	r0, fp, #76
	moveq	r3, #1
	streqb	r3, [r5, #743]
	bl	BsSkip
.L745:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #1
	beq	.L766
	add	r4, r4, #1
	cmp	r4, #15
	bls	.L746
.L764:
	mov	r6, #0
	sub	r0, fp, #76
	strb	r6, [r5, #1577]
	bl	BsPos
	ldr	r3, .L770+4
	ldr	r4, [r3]
	cmp	r4, r6
	mov	r8, r0
	beq	.L752
	ldr	r0, [r5, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #103
	blx	r4
	mov	r0, r8
.L763:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L735:
	mov	r2, #18
	mov	r3, #22
	strb	r2, [r5, #747]
	mov	r2, #352
	strb	r3, [r5, #748]
	mov	r3, #288
	str	r2, [r5, #1512]
	str	r3, [r5, #1508]
	b	.L737
.L734:
	mov	r2, #9
	mov	r3, #11
	strb	r2, [r5, #747]
	mov	r2, #176
	strb	r3, [r5, #748]
	mov	r3, #144
	str	r2, [r5, #1512]
	str	r3, [r5, #1508]
	b	.L737
.L732:
	mov	r2, #6
	mov	r3, #8
	strb	r2, [r5, #747]
	mov	r2, #128
	strb	r3, [r5, #748]
	mov	r3, #96
	str	r2, [r5, #1512]
	str	r3, [r5, #1508]
	b	.L737
.L766:
	sub	r0, fp, #76
	add	r4, r4, #1
	bl	BsPos
	mov	r1, #8
	cmp	r0, r9
	sub	r0, fp, #76
	bgt	.L767
	bl	BsSkip
	cmp	r4, #15
	bls	.L745
	b	.L764
.L765:
	ldr	r1, .L770+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r7, #3324]
	b	.L730
.L746:
	add	r10, r6, #16384
	mov	r2, #1
	strb	r2, [r5, #1577]
	sub	r0, fp, #76
	ldr	r3, [r10, #3592]
	orr	r3, r3, #2
	str	r3, [r10, #3592]
	ldr	r3, [r7, #3324]
	add	r3, r3, r2
	str	r3, [r7, #3324]
	strb	r2, [r5, #744]
	bl	BsPos
	mov	r3, r0, asr #31
	cmp	r0, #0
	add	r1, r0, #7
	rsb	r4, r0, r9
	mov	r3, r3, lsr #29
	str	r4, [r6, #1284]
	add	r2, r0, r3
	movge	r1, r0
	mov	r8, r0
	and	r2, r2, #7
	ldr	r0, [r5, #1592]
	rsb	r3, r3, r2
	add	r3, r3, r0
	strb	r3, [r6, #1282]
	ldr	r3, [r5, #1584]
	add	r3, r3, r1, asr #3
	str	r3, [r6, #1292]
	ldrb	r3, [r7, #3430]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L768
.L747:
	mov	r3, #0
	str	r3, [r6, #1288]
	strb	r3, [r6, #1283]
	str	r3, [r6, #1296]
.L748:
	ldrb	r3, [r5, #736]	@ zero_extendqisi2
	strb	r3, [r6, #1280]
	ldrb	r3, [r5, #745]	@ zero_extendqisi2
	strb	r3, [r6, #1278]
	ldrb	r3, [r5, #744]	@ zero_extendqisi2
	strb	r3, [r6, #1277]
	ldrb	r3, [r5, #743]	@ zero_extendqisi2
	strb	r3, [r6, #1281]
	ldrb	r3, [r5, #740]	@ zero_extendqisi2
	strb	r3, [r6, #1279]
	ldr	r2, [r10, #3588]
	cmp	r2, #0
	bne	.L769
.L749:
	mov	r0, r6
	bl	MP4_Record_SlcSegID
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L739:
	sub	r0, fp, #76
	bl	BsPos
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L731:
	mov	r6, #0
	sub	r0, fp, #76
	strb	r6, [r5, #1577]
	bl	BsPos
	ldr	r3, .L770+4
	ldr	r4, [r3]
	cmp	r4, r6
	mov	r8, r0
	beq	.L752
	ldr	r0, [r5, #2496]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	r4
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L768:
	ldrb	r2, [r7, #3510]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L747
	ldr	r2, [r7, #3520]
	strb	r3, [r6, #1283]
	mov	r3, r2, asl #3
	str	r3, [r6, #1288]
	ldr	r3, [r7, #3516]
	str	r3, [r6, #1296]
	b	.L748
.L769:
	ldr	r1, .L770+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP4_ClearCurPic
	b	.L749
.L752:
	mov	r0, r8
	b	.L763
.L767:
	bl	BsPos
	b	.L763
.L771:
	.align	2
.L770:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC45
	.word	.LC46
	UNWIND(.fnend)
	.size	Mp4_Syntax_ShortHeader, .-Mp4_Syntax_ShortHeader
	.align	2
	.global	Mp4_Syntax_Vop
	.type	Mp4_Syntax_Vop, %function
Mp4_Syntax_Vop:
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
	add	r7, r0, #12288
	mov	r6, r2
	mov	r5, r0
	ldr	r2, [r7, #3324]
	mov	r10, r1
	cmp	r2, #0
	bne	.L850
	add	r4, r5, #20480
	ldrb	r3, [r4, #797]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L774
.L851:
	mov	r0, #32
	strb	r3, [r4, #1577]
.L775:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L850:
	add	r4, r5, #20480
	ldr	r1, .L866
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r7, #3324]
	ldrb	r3, [r4, #797]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L851
.L774:
	add	r8, r5, #20992
	ldr	r9, .L866+4
	add	r8, r8, #224
	mov	r1, r10
	sub	r0, fp, #76
	mov	r2, r6
	bl	BsInit
	mov	r2, #60
	ldr	r3, [r9, #48]
	mov	r1, #0
	mov	r0, r8
	blx	r3
	mov	r3, #0
	mov	r1, #32
	strb	r3, [r4, #1577]
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	ldr	r1, .L866+8
	uxtb	r2, r0
	strb	r0, [r4, #736]
	mov	r0, #18
	bl	dprint_vfmw
	ldrb	r10, [r4, #736]	@ zero_extendqisi2
	cmp	r10, #3
	beq	.L852
.L776:
	adds	r10, r10, #0
	ldrb	r3, [r4, #803]	@ zero_extendqisi2
	movne	r10, #1
	cmp	r3, #1
	movne	r2, #0
	andeq	r2, r10, #1
	cmp	r2, #0
	bne	.L779
	cmp	r3, #2
	beq	.L779
	ldr	r3, [r4, #2136]
	cmp	r3, #1
	movne	r10, #0
	andeq	r10, r10, #1
	cmp	r10, #0
	bne	.L779
	mov	r6, r6, asl #3
	b	.L782
.L854:
	bl	BsPos
	add	r10, r10, #1
	cmp	r0, r6
	bgt	.L853
	cmp	r10, #6400
	beq	.L783
.L782:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	sub	r0, fp, #76
	bne	.L854
	cmp	r10, #6400
	bcs	.L783
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L855
	ldr	r1, [r4, #912]
	cmp	r1, #0
	moveq	r0, r1
	bne	.L856
.L786:
	str	r10, [r4, #1516]
	mov	r1, #1
	str	r0, [r4, #1520]
	sub	r0, fp, #76
	bl	BsGet
	subs	r10, r0, #0
	bne	.L787
	ldr	r1, .L866+12
	mov	r0, #1
	bl	dprint_vfmw
	strb	r10, [r4, #1577]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L866+16
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r5, r0
	beq	.L813
	ldr	r0, [r4, #2496]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #103
	blx	r6
	mov	r0, r5
	b	.L775
.L783:
	mov	r3, #0
	sub	r0, fp, #76
	strb	r3, [r4, #1577]
	bl	BsPos
	mov	r2, r10
	ldr	r1, .L866+20
	mov	r4, r0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L775
.L853:
	sub	r0, fp, #76
	bl	BsPos
	ldr	r1, .L866+24
	mov	r4, r0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L775
.L852:
	ldr	r3, .L866+28
	ldr	r3, [r3]
	ands	r3, r3, #8
	bne	.L776
	strb	r3, [r4, #1577]
	sub	r0, fp, #76
	str	r3, [fp, #-80]
	bl	BsPos
	ldr	r2, .L866+16
	ldr	r6, [r2]
	cmp	r6, #0
	mov	r5, r0
	beq	.L777
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2496]
	mov	r2, r3
	blx	r6
.L777:
	ldr	r1, .L866+32
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L775
.L779:
	sub	r0, fp, #76
	bl	BsPos
	b	.L775
.L787:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #737]
	cmp	r0, #0
	beq	.L857
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L789
	cmp	r3, #3
	beq	.L858
.L790:
	mov	r3, #0
	strb	r3, [r4, #738]
.L791:
	ldrb	r3, [r4, #852]	@ zero_extendqisi2
	mov	r2, #0
	strb	r2, [r4, #739]
	cmp	r3, #2
	addeq	r10, r5, #16384
	beq	.L792
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	add	r10, r5, #16384
	strb	r0, [r4, #740]
	ldrb	r3, [r10, #3634]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r4, #742]
	moveq	r3, #2
	streqb	r3, [r4, #741]
	bne	.L859
.L794:
	ldrb	r3, [r4, #856]	@ zero_extendqisi2
	sub	r3, r3, #1
	cmp	r3, #1
	bls	.L795
.L798:
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	moveq	r3, #1
	streqb	r3, [r4, #743]
	strneb	r0, [r4, #743]
.L804:
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L860
.L792:
	mov	r3, #1
	strb	r3, [r4, #1577]
	ldr	r3, [r10, #3592]
	add	r0, r5, #21760
	mov	r1, r8
	mov	r2, #60
	orr	r3, r3, #2
	str	r3, [r10, #3592]
	ldr	r3, [r7, #3324]
	add	r0, r0, #168
	ldr	r9, [r9, #52]
	add	r3, r3, #1
	str	r3, [r7, #3324]
	blx	r9
	sub	r0, fp, #76
	bl	BsPos
	mov	r3, r0, asr #31
	mov	r8, r0
	add	r1, r0, #7
	rsb	r6, r0, r6
	mov	r3, r3, lsr #29
	str	r6, [r5, #1284]
	add	r2, r8, r3
	ldr	r0, [r4, #1592]
	and	r2, r2, #7
	cmp	r8, #0
	rsb	r3, r3, r2
	add	r3, r3, r0
	strb	r3, [r5, #1282]
	ldr	r3, [r4, #1584]
	movge	r1, r8
	add	r3, r3, r1, asr #3
	str	r3, [r5, #1292]
	ldrb	r3, [r7, #3430]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L808
	ldrb	r2, [r7, #3510]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L861
.L808:
	mov	r3, #0
	str	r3, [r5, #1288]
	strb	r3, [r5, #1283]
	str	r3, [r5, #1296]
.L809:
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	strb	r3, [r5, #1280]
	ldrb	r3, [r4, #745]	@ zero_extendqisi2
	strb	r3, [r5, #1278]
	ldrb	r3, [r4, #744]	@ zero_extendqisi2
	strb	r3, [r5, #1277]
	ldrb	r3, [r4, #743]	@ zero_extendqisi2
	strb	r3, [r5, #1281]
	ldrb	r3, [r4, #740]	@ zero_extendqisi2
	strb	r3, [r5, #1279]
	ldr	r2, [r10, #3588]
	cmp	r2, #0
	bne	.L862
.L810:
	mov	r0, r5
	bl	MP4_Record_SlcSegID
	mov	r0, r8
	b	.L775
.L855:
	ldr	r1, .L866+12
	mov	r0, #1
	str	r3, [fp, #-80]
	bl	dprint_vfmw
	ldr	r3, [fp, #-80]
	sub	r0, fp, #76
	strb	r3, [r4, #1577]
	bl	BsPos
	ldr	r2, .L866+16
	ldr	r6, [r2]
	cmp	r6, #0
	mov	r5, r0
	beq	.L813
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2496]
	mov	r2, r3
	blx	r6
	mov	r0, r5
	b	.L775
.L856:
	sub	r0, fp, #76
	bl	BsGet
	b	.L786
.L813:
	mov	r0, r5
	b	.L775
.L862:
	ldr	r1, .L866+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	bl	MP4_ClearCurPic
	b	.L810
.L857:
	add	r5, r5, #16384
	mov	r3, #4
	mov	r2, #1
	strb	r3, [r4, #736]
	strb	r3, [r4, #1448]
	sub	r0, fp, #76
	strb	r2, [r4, #1577]
	ldr	r3, [r5, #3592]
	orr	r3, r3, #128
	str	r3, [r5, #3592]
	bl	BsPos
	b	.L775
.L858:
	ldrb	r3, [r4, #856]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L790
.L789:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #738]
	b	.L791
.L860:
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #744]
	cmp	r2, #0
	beq	.L863
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L792
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #745]
	cmp	r2, #0
	bne	.L792
	strb	r2, [r4, #1577]
	sub	r0, fp, #76
	str	r2, [fp, #-80]
	bl	BsPos
	ldr	r3, .L866+16
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r5, r0
	beq	.L807
	ldr	r2, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2496]
	mov	r3, r2
	blx	r6
.L807:
	ldr	r1, .L866+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L775
.L859:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #741]
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #742]
	b	.L794
.L795:
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L798
	ldrb	r3, [r4, #868]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L798
	add	r3, r5, #21248
	mov	r2, #0
	add	r3, r3, #4
	str	r5, [fp, #-84]
	str	r6, [fp, #-88]
	mov	r6, r2
	str	r8, [fp, #-80]
	mov	r5, r3
	str	r7, [fp, #-92]
	b	.L803
.L799:
	ldr	r3, [r4, #1552]
	cmp	r3, #500
	bne	.L800
	ldr	r2, [r4, #1556]
	movw	r3, #413
	cmp	r2, r3
	beq	.L801
.L800:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
.L801:
	sub	r0, fp, #76
	bl	bs_get_spritetrajectory
	subs	r3, r0, #0
	moveq	r7, r3
	bne	.L864
.L802:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
	str	r8, [r5]
	str	r7, [r5, #4]
	add	r6, r6, #1
	ldrb	r3, [r4, #868]	@ zero_extendqisi2
	add	r5, r5, #8
	cmp	r3, r6
	bls	.L865
.L803:
	sub	r0, fp, #76
	bl	bs_get_spritetrajectory
	subs	r7, r0, #0
	moveq	r8, r7
	beq	.L799
	mov	r1, r7
	sub	r0, fp, #76
	bl	BsGet
	sub	r2, r7, #1
	movs	r3, r0, asr r2
	mov	r8, r0
	moveq	r3, #1
	moveq	r3, r3, asl r7
	subeq	r3, r3, #1
	eoreq	r8, r8, r3
	rsbeq	r8, r8, #0
	b	.L799
.L864:
	mov	r1, r3
	sub	r0, fp, #76
	str	r3, [fp, #-96]
	bl	BsGet
	ldr	r3, [fp, #-96]
	sub	r1, r3, #1
	movs	r2, r0, asr r1
	mov	r7, r0
	moveq	r2, #1
	moveq	r3, r2, asl r3
	subeq	r3, r3, #1
	eoreq	r3, r3, r0
	rsbeq	r7, r3, #0
	b	.L802
.L861:
	ldr	r2, [r7, #3520]
	strb	r3, [r5, #1283]
	mov	r3, r2, asl #3
	str	r3, [r5, #1288]
	ldr	r3, [r7, #3516]
	str	r3, [r5, #1296]
	b	.L809
.L863:
	strb	r2, [r4, #1577]
	sub	r0, fp, #76
	str	r2, [fp, #-80]
	bl	BsPos
	ldr	r3, .L866+16
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r5, r0
	beq	.L806
	ldr	r2, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2496]
	mov	r3, r2
	blx	r6
.L806:
	ldrb	r2, [r4, #736]	@ zero_extendqisi2
	mov	r0, #1
	ldr	r1, .L866+44
	bl	dprint_vfmw
	mov	r0, r5
	b	.L775
.L865:
	ldr	r8, [fp, #-80]
	ldr	r5, [fp, #-84]
	ldr	r6, [fp, #-88]
	ldr	r7, [fp, #-92]
	b	.L798
.L867:
	.align	2
.L866:
	.word	.LC45
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LC8
	.word	g_event_report
	.word	.LC50
	.word	.LC49
	.word	g_VdmCharacter
	.word	.LC48
	.word	.LC46
	.word	.LC52
	.word	.LC51
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vop, .-Mp4_Syntax_Vop
	.align	2
	.global	Mp4_Syntax_Slice_NotSH
	.type	Mp4_Syntax_Slice_NotSH, %function
Mp4_Syntax_Slice_NotSH:
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
	add	r7, r0, #12288
	mov	r4, r0
	movw	r3, #510
	ldr	r8, [r7, #3324]
	mov	r5, r2
	sub	r0, r8, #1
	cmp	r0, r3
	bhi	.L889
	add	r3, r4, #15872
	add	r0, r8, #1
	str	r0, [r7, #3324]
	add	r6, r4, #20480
	ldrh	r9, [r3]
	sub	r0, fp, #76
	bl	BsInit
	sub	r0, fp, #76
	ubfx	r9, r9, #7, #4
	add	r9, r9, #17
	mov	r1, r9
	bl	BsSkip
	ldr	r2, [r6, #1508]
	ldr	r9, [r6, #1512]
	add	r2, r2, #15
	add	r9, r9, #15
	mov	r2, r2, lsr #4
	mov	r9, r9, lsr #4
	mul	r9, r9, r2
	cmp	r9, #0
	beq	.L871
	mov	r2, r9
	mov	r1, #0
.L872:
	add	r1, r1, #1
	movs	r2, r2, lsr #1
	uxth	r1, r1
	bne	.L872
	sxth	r1, r1
	sub	r0, fp, #76
	bl	BsGet
	mov	r10, r8, asl #2
	mov	r8, r8, asl #5
	sub	r1, r9, #1
	rsb	r3, r10, r8
	add	r3, r4, r3
	cmp	r0, r1
	str	r0, [r3, #1300]
	bhi	.L890
.L873:
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	rsb	r3, r10, r8
	add	r3, r4, r3
	mov	r1, #1
	add	r3, r3, #1264
	strb	r0, [r3, #17]
	sub	r0, fp, #76
	add	r3, r3, #8
	str	r3, [fp, #-80]
	bl	BsGet
	ldr	r3, [fp, #-80]
	cmp	r0, #0
	bne	.L891
	ldrb	r2, [r6, #736]	@ zero_extendqisi2
	mov	r5, r5, asl #3
	add	r9, r4, #16384
	strb	r2, [r3, #8]
	ldrb	r2, [r6, #740]	@ zero_extendqisi2
	strb	r2, [r3, #7]
.L877:
	ldrb	r1, [r6, #744]	@ zero_extendqisi2
	rsb	r3, r10, r8
	add	r3, r4, r3
	sub	r0, fp, #76
	add	r2, r3, #1264
	str	r3, [fp, #-84]
	strb	r1, [r3, #1277]
	add	r2, r2, #8
	ldrb	r1, [r6, #745]	@ zero_extendqisi2
	str	r2, [fp, #-80]
	strb	r1, [r3, #1278]
	ldr	r1, [r9, #3592]
	orr	r1, r1, #16
	str	r1, [r9, #3592]
	bl	BsPos
	ldr	r3, [fp, #-84]
	ldr	r2, [fp, #-80]
	mov	r1, r0, asr #31
	cmp	r0, #0
	add	ip, r0, #7
	rsb	r5, r0, r5
	mov	r1, r1, lsr #29
	movge	ip, r0
	mov	r9, r0
	add	r0, r0, r1
	str	r5, [r3, #1284]
	and	r0, r0, #7
	ldr	lr, [r6, #1592]
	rsb	r1, r1, r0
	add	r1, r1, lr
	strb	r1, [r2, #10]
	ldr	r2, [r6, #1584]
	add	r2, r2, ip, asr #3
	str	r2, [r3, #1292]
	ldrb	r2, [r7, #3430]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L878
	ldrb	r1, [r7, #3510]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L892
.L878:
	rsb	r8, r10, r8
	mov	r3, #0
	add	r8, r4, r8
	add	r1, r8, #1280
	add	r2, r8, #1264
	str	r3, [r1, #8]
	mov	r8, r1
	strb	r3, [r2, #19]
	str	r3, [r8, #16]
.L879:
	mov	r0, r4
	bl	MP4_Record_SlcSegID
	mov	r0, r9
.L888:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L891:
	mov	r5, r5, asl #3
.L875:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r9, r0
	sub	r0, fp, #76
	bl	BsPos
	cmp	r9, #0
	cmpne	r0, r5
	blt	.L875
	add	r9, r4, #16384
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
	ldr	r1, [r9, #3692]
	cmp	r1, #0
	bne	.L893
.L876:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	rsb	r3, r10, r8
	add	r3, r4, r3
	mov	r1, #3
	add	r3, r3, #1264
	strb	r0, [r3, #16]
	sub	r0, fp, #76
	add	r3, r3, #8
	str	r3, [fp, #-80]
	bl	BsGet
	ldr	r3, [fp, #-80]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #0
	strb	r0, [r3, #7]
	beq	.L877
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsSkip
	ldr	r3, [fp, #-80]
	ldrb	r3, [r3, #8]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L877
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsSkip
	b	.L877
.L889:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #32
	ldr	r0, [r3, #2496]
	bl	MP4_ClearCurPacket
	mov	r0, r4
	add	r4, r4, #16384
	bl	MP4_ClearCurPic
	ldr	r2, .L894
	mov	r0, #1
	ldr	r3, [r4, #3592]
	ldr	r1, .L894+4
	bic	r3, r3, #432
	bic	r3, r3, #2
	str	r3, [r4, #3592]
	ldr	r3, [r7, #3324]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L893:
	sub	r0, fp, #76
	bl	BsSkip
	b	.L876
.L892:
	ldr	r1, [r7, #3520]
	strb	r2, [r3, #1283]
	mov	r2, r1, asl #3
	str	r2, [r3, #1288]
	ldr	r2, [r7, #3516]
	str	r2, [r3, #1296]
	b	.L879
.L871:
	mov	r1, r9
	sub	r0, fp, #76
	bl	BsGet
	mov	r10, r8, asl #2
	mov	r8, r8, asl #5
	rsb	r3, r10, r8
	add	r3, r4, r3
	str	r0, [r3, #1300]
	b	.L873
.L890:
	mov	r2, r0
	mov	r3, r9
	ldr	r1, .L894+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L888
.L895:
	.align	2
.L894:
	.word	.LANCHOR1+1296
	.word	.LC53
	.word	.LC54
	UNWIND(.fnend)
	.size	Mp4_Syntax_Slice_NotSH, .-Mp4_Syntax_Slice_NotSH
	.align	2
	.global	Mp4_Syntax_Slice_SH
	.type	Mp4_Syntax_Slice_SH, %function
Mp4_Syntax_Slice_SH:
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
	add	r8, r0, #12288
	movw	r3, #510
	mov	r5, r0
	ldr	r4, [r8, #3324]
	mov	r9, r2
	sub	r6, r4, #1
	cmp	r6, r3
	bhi	.L910
	ldrb	r7, [r8, #3584]	@ zero_extendqisi2
	add	r3, r4, #1
	sub	r0, fp, #76
	str	r3, [r8, #3324]
	ubfx	r7, r7, #3, #4
	bl	BsInit
	add	r7, r7, #17
	sub	r0, fp, #76
	add	r10, r5, #20480
	mov	r1, r7
	bl	BsSkip
	mov	r3, r4, asl #2
	mov	r1, #5
	sub	r0, fp, #76
	mov	r7, r3
	str	r3, [fp, #-80]
	bl	BsGet
	ldrb	lr, [r10, #748]	@ zero_extendqisi2
	mov	r3, r4, asl #5
	movw	ip, #1206
	movw	r1, #1204
	str	r3, [fp, #-84]
	mov	r2, r3
	rsb	r2, r7, r2
	add	r4, r5, r2
	mul	r0, lr, r0
	str	r0, [r4, #1300]
	ldrh	ip, [r5, ip]
	ldrh	r1, [r5, r1]
	mul	r1, r1, ip
	sub	r3, r1, #1
	cmp	r0, r3
	bhi	.L911
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #1281]
	sub	r0, fp, #76
	ldrb	r1, [r10, #736]	@ zero_extendqisi2
	strb	r1, [r4, #1280]
	ldrb	r1, [r10, #740]	@ zero_extendqisi2
	strb	r1, [r4, #1279]
	ldrb	r1, [r10, #744]	@ zero_extendqisi2
	strb	r1, [r4, #1277]
	ldrb	r1, [r10, #745]	@ zero_extendqisi2
	strb	r1, [r4, #1278]
	bl	BsPos
	mov	r1, r0
	mov	r0, r0, asr #31
	rsb	r9, r1, r9, lsl #3
	str	r9, [r4, #1284]
	mov	r0, r0, lsr #29
	ldr	r9, [r10, #1592]
	add	ip, r1, r0
	cmp	r1, #0
	and	ip, ip, #7
	add	lr, r1, #7
	rsb	r0, r0, ip
	movge	lr, r1
	add	r0, r0, r9
	strb	r0, [r4, #1282]
	add	r0, r5, #16384
	ldr	r3, [r10, #1584]
	add	lr, r3, lr, asr #3
	str	lr, [r4, #1292]
	ldr	r3, [r0, #3592]
	orr	r3, r3, #16
	str	r3, [r0, #3592]
	ldrb	r3, [r8, #3430]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L912
.L900:
	ldr	r2, [fp, #-80]
	ldr	r3, [fp, #-84]
	rsb	r4, r2, r3
	mov	r3, #0
	add	r4, r5, r4
	add	r0, r4, #1280
	add	r2, r4, #1264
	str	r3, [r0, #8]
	mov	r4, r0
	strb	r3, [r2, #19]
	str	r3, [r4, #16]
.L901:
	mov	r2, r6, asl #2
	mov	r6, r6, asl #5
	rsb	r3, r2, r6
	add	r3, r5, r3
	ldr	r0, [r3, #1296]
	cmp	r0, #0
	bne	.L913
.L902:
	rsb	r6, r2, r6
	ldrb	r3, [r8, #3584]	@ zero_extendqisi2
	add	r6, r5, r6
	ubfx	r3, r3, #3, #4
	ldr	r2, [r6, #1284]
	add	r3, r3, r2
	str	r3, [r6, #1284]
.L903:
	mov	r0, r5
	str	r1, [fp, #-80]
	bl	MP4_Record_SlcSegID
	ldr	r1, [fp, #-80]
	mov	r0, r1
.L898:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L913:
	ldr	r0, [r3, #1288]
	add	r3, r3, #1280
	add	r3, r3, #4
	cmp	r0, #0
	beq	.L902
	ldrb	r2, [r8, #3584]	@ zero_extendqisi2
	ubfx	r2, r2, #3, #4
	add	r2, r2, r0
	str	r2, [r3, #4]
	b	.L903
.L912:
	ldrb	r0, [r8, #3510]	@ zero_extendqisi2
	cmp	r0, #1
	bne	.L900
	ldr	r0, [r8, #3520]
	strb	r3, [r4, #1283]
	mov	r3, r0, asl #3
	str	r3, [r4, #1288]
	ldr	r3, [r8, #3516]
	str	r3, [r4, #1296]
	b	.L901
.L910:
	add	r3, r0, #20480
	add	r1, r0, #15680
	add	r1, r1, #32
	ldr	r0, [r3, #2496]
	bl	MP4_ClearCurPacket
	mov	r0, r5
	add	r5, r5, #16384
	bl	MP4_ClearCurPic
	ldr	r2, .L914
	mov	r0, #1
	ldr	r3, [r5, #3592]
	ldr	r1, .L914+4
	bic	r3, r3, #432
	bic	r3, r3, #2
	str	r3, [r5, #3592]
	ldr	r3, [r8, #3324]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L911:
	mov	r2, r0
	ldr	r1, .L914+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L898
.L915:
	.align	2
.L914:
	.word	.LANCHOR1+1320
	.word	.LC53
	.word	.LC55
	UNWIND(.fnend)
	.size	Mp4_Syntax_Slice_SH, .-Mp4_Syntax_Slice_SH
	.align	2
	.global	MP4_Dec_Slice
	.type	MP4_Dec_Slice, %function
MP4_Dec_Slice:
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
	add	ip, r0, #12288
	mov	r4, r0
	ldrb	r3, [ip, #3584]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L926
	tst	r3, #4
	beq	.L927
	mov	r0, r4
	bl	Mp4_Syntax_Slice_SH
	cmn	r0, #1
	beq	.L924
.L920:
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L927:
	add	r0, r0, #15872
	ldrh	r0, [r0]
	ubfx	r0, r0, #7, #4
	sub	lr, r0, #1
	cmp	lr, #6
	bfils	r3, r0, #3, #4
	mov	r0, r4
	strlsb	r3, [ip, #3584]
	bl	Mp4_Syntax_Slice_SH
	cmn	r0, #1
	bne	.L920
.L924:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #32
	ldr	r0, [r3, #2496]
	bl	MP4_ClearCurPacket
	ldr	r2, .L929
	ldr	r1, .L929+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L926:
	str	r2, [fp, #-28]
	str	r1, [fp, #-24]
	bl	Mp4_Check_Slice_NotSH
	ldr	r1, [fp, #-24]
	ldr	r2, [fp, #-28]
	cmp	r0, #0
	beq	.L928
	mov	r1, r2
	mov	r0, r4
	bl	Mp4_Combine_SliceData
	cmp	r0, #0
	bne	.L924
	mov	r0, r4
	bl	MP4_Record_SlcSegID
	b	.L920
.L928:
	mov	r0, r4
	bl	Mp4_Syntax_Slice_NotSH
	cmn	r0, #1
	beq	.L924
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L930:
	.align	2
.L929:
	.word	.LANCHOR1+1340
	.word	.LC56
	UNWIND(.fnend)
	.size	MP4_Dec_Slice, .-MP4_Dec_Slice
	.align	2
	.global	MP4_Record_PacketID
	.type	MP4_Record_PacketID, %function
MP4_Record_PacketID:
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
	add	r5, r0, #20480
	mov	r4, r0
	ldr	r3, [r5, #2052]
	cmp	r3, #62
	bgt	.L934
	add	r1, r0, #12288
	add	r4, r0, r3, lsl #2
	add	r4, r4, #20480
	add	r2, r3, #1
	ldr	r0, [r1, #3444]
	str	r0, [r4, #1796]
	str	r2, [r5, #2052]
	ldrb	r2, [r1, #3430]	@ zero_extendqisi2
	cmp	r2, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r2, [r1, #3510]	@ zero_extendqisi2
	cmp	r2, #1
	ldreq	r2, [r1, #3524]
	addeq	r3, r3, #2
	streq	r2, [r4, #1800]
	streq	r3, [r5, #2052]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L934:
	bl	MP4_Clean_HeadPacket
	add	r1, r4, #15680
	ldr	r0, [r5, #2496]
	add	r1, r1, #32
	bl	MP4_ClearCurPacket
	ldr	r2, [r5, #2052]
	mov	r3, #62
	ldr	r1, .L935
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L936:
	.align	2
.L935:
	.word	.LC44
	UNWIND(.fnend)
	.size	MP4_Record_PacketID, .-MP4_Record_PacketID
	.align	2
	.global	MP4_Record_HeadPacketInfo
	.type	MP4_Record_HeadPacketInfo, %function
MP4_Record_HeadPacketInfo:
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
	mov	r7, r1
	beq	.L940
	ldr	r6, .L942
	add	r1, r4, #15680
	add	r0, r4, #22016
	add	r1, r1, #32
	mov	r2, #160
	add	r5, r4, #20480
	ldr	r3, [r6, #52]
	add	r0, r0, #96
	blx	r3
	ldr	r3, [r6, #52]
	mov	r2, #4
	add	r1, r4, #15872
	add	r0, r4, #22272
	blx	r3
	ldr	r3, [r5, #2060]
	str	r7, [r5, #2056]
	cmp	r3, #0
	beq	.L941
.L939:
	ldr	r3, [r5, #2064]
	add	r3, r3, #1
	str	r3, [r5, #2064]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L941:
	mov	r0, r4
	bl	MP4_Record_PacketID
	mov	r3, #1
	str	r3, [r5, #2060]
	b	.L939
.L940:
	ldr	r1, .L942+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L943:
	.align	2
.L942:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC57
	UNWIND(.fnend)
	.size	MP4_Record_HeadPacketInfo, .-MP4_Record_HeadPacketInfo
	.align	2
	.global	Mp4_Syntax_Parse
	.type	Mp4_Syntax_Parse, %function
Mp4_Syntax_Parse:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 88
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
	ldr	r9, .L1094
	mov	r6, r0
	mov	r8, r1
	mov	r4, r2
	str	r2, [fp, #-120]
	ldr	r3, [r9, #48]
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #108
	blx	r3
	mov	r2, r4
	mov	r1, r8
	sub	r0, fp, #108
	bl	BsInit
	sub	r0, fp, #108
	mov	r1, #32
	add	r7, r6, #16384
	bl	BsShow
	movw	r3, #510
	mov	r10, #0
	str	r10, [r7, #3596]
	cmp	r0, r3
	mov	r5, r0
	beq	.L1073
	add	r1, r6, #12288
	ldrb	r3, [r1, #3584]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L1074
.L950:
	add	r4, r6, #20480
	mov	r5, #196
	mov	r2, #1
	strb	r2, [r4, #805]
.L951:
	and	r3, r3, #2
	ands	r3, r3, #255
	bne	.L952
	ldr	r2, [r7, #3592]
	ands	r10, r2, #130
	bne	.L1075
	cmp	r5, #197
	beq	.L1076
	cmp	r5, #432
	beq	.L1077
	movw	r3, #437
	cmp	r5, r3
	beq	.L1078
	bic	r3, r5, #15
	cmp	r3, #288
	beq	.L1079
	movw	r3, #435
	cmp	r5, r3
	beq	.L1080
	movw	r3, #438
	cmp	r5, r3
	beq	.L1081
	cmp	r5, #196
	beq	.L1082
	movw	r3, #434
	cmp	r5, r3
	beq	.L1083
	movw	r3, #286
	cmp	r5, r3
	bne	.L967
	ldr	r10, .L1094+4
	ldr	r3, [r10]
	subs	ip, r3, #0
	beq	.L968
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #2496]
	blx	ip
.L968:
	ldr	r3, [fp, #-120]
	add	r1, r6, #15680
	ldr	r0, [r4, #2496]
	add	r1, r1, #32
	sub	r3, r3, #4
	str	r3, [fp, #-120]
	bl	MP4_ClearCurPacket
	ldr	r3, [r7, #3592]
	add	r2, r8, #4
	str	r2, [fp, #-124]
	tst	r3, #2
	orrne	r3, r3, #256
	strne	r3, [r7, #3592]
	ldr	r3, [r7, #3592]
	and	r3, r3, #18
	cmp	r3, #18
	beq	.L970
	ldr	r10, [r10]
	cmp	r10, #0
	beq	.L970
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #2496]
	blx	r10
.L970:
	ldrb	r3, [r4, #2533]	@ zero_extendqisi2
	mov	r10, #0
	cmp	r3, #1
	beq	.L1001
.L976:
	ldrb	r3, [r4, #1575]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1070
	ldr	r3, [r4, #2072]
	add	r1, r6, #19968
	add	r0, r6, #21248
	add	r1, r1, #40
	add	r3, r3, #1
	mov	r2, #604
	str	r3, [r4, #2072]
	add	r0, r0, #76
	mov	r3, #0
	ldr	r5, [r9, #52]
	str	r3, [r4, #2076]
	blx	r5
	ldr	r2, [r4, #1508]
	ldr	r0, [r7, #3708]
	ldr	r1, [r7, #3704]
	cmp	r2, r0
	beq	.L1084
.L992:
	ldr	r3, .L1094+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L994
	ldr	ip, [r4, #1512]
	mov	r3, #8
	strh	r2, [fp, #-114]	@ movhi
	sub	r2, fp, #116
	strh	r1, [fp, #-112]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-110]	@ movhi
	strh	ip, [fp, #-116]	@ movhi
	ldr	r0, [r4, #2496]
	blx	r5
	ldr	r0, [r7, #3708]
	ldr	r1, [r7, #3704]
.L994:
	mov	r5, #1
	str	r0, [r4, #1508]
	str	r1, [r4, #1512]
.L993:
	sxtb	r5, r5
	cmp	r5, #1
	beq	.L1085
.L996:
	ldr	r3, [r4, #1508]
	mov	r2, #0
	ldr	r1, [r4, #1512]
	str	r3, [r4, #2096]
	str	r1, [r4, #2092]
	ldr	r3, [r7, #3708]
	str	r3, [r4, #1508]
	ldr	r3, [r7, #3704]
	strb	r2, [r4, #1575]
	str	r3, [r4, #1512]
	b	.L1070
.L1075:
	orr	r2, r2, #32
	mov	r10, r3
	str	r2, [r7, #3592]
	mov	r3, #1
	str	r3, [r7, #3596]
.L1070:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L952:
	ldr	r2, [fp, #-120]
	mov	r1, r8
	mov	r0, r6
	bl	MP4_Dec_Slice
	mov	r10, r0
.L956:
	ldrb	r3, [r4, #2533]	@ zero_extendqisi2
	str	r8, [fp, #-124]
	cmp	r3, #1
	beq	.L1001
	ldr	r3, [fp, #-120]
	cmp	r10, r3, asl #3
	bhi	.L975
.L1090:
	movw	r3, #438
	cmp	r5, r3
	cmpne	r5, #196
	bne	.L976
	ldr	r3, [r7, #3592]
	tst	r3, #130
	beq	.L976
	ldrb	r3, [r4, #805]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1086
	ldr	r2, [r4, #1512]
	ldr	r1, [r4, #1508]
	cmp	r2, #0
	str	r2, [r4, #2100]
	str	r1, [r4, #2104]
	beq	.L980
	ldr	r3, [r4, #2092]
	cmp	r2, r3
	beq	.L980
.L1009:
	mov	r7, #1
.L981:
	ldr	r3, .L1094+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L985
	ldr	r0, [r4, #2096]
	mov	r3, #8
	ldr	ip, [r4, #2092]
	strh	r2, [fp, #-112]	@ movhi
	sub	r2, fp, #116
	strh	r1, [fp, #-110]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-114]	@ movhi
	strh	ip, [fp, #-116]	@ movhi
	ldr	r0, [r4, #2496]
	blx	r5
.L985:
	sxtb	r7, r7
	cmp	r7, #1
	beq	.L1087
.L987:
	ldr	r2, [r4, #2100]
	ldr	r3, [r4, #2104]
	str	r2, [r4, #2092]
	str	r3, [r4, #2096]
.L979:
	add	r1, r6, #20992
	add	r0, r6, #21760
	ldr	r3, [r9, #52]
	mov	r2, #60
	add	r1, r1, #224
	add	r0, r0, #168
	blx	r3
	ldr	r1, .L1094+8
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r3, [fp, #-124]
	rsb	r8, r8, r3
	ldr	r3, [r4, #2076]
	add	r10, r10, r8, lsl #3
	add	r3, r3, #1
	str	r3, [r4, #2076]
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1074:
	mov	r2, r0, lsr #8
	add	r4, r6, #20480
	sub	r2, r2, #128
	mov	r0, #2
	cmp	r2, #3
	strb	r0, [r4, #805]
	ldrlsb	r3, [r1, #3584]	@ zero_extendqisi2
	orrls	r3, r3, r0
	strlsb	r3, [r1, #3584]
	b	.L951
.L980:
	cmp	r1, #0
	beq	.L982
	ldr	r3, [r4, #2096]
	cmp	r1, r3
	beq	.L1088
	cmp	r2, #0
	beq	.L1009
	ldr	r3, [r4, #2092]
	cmp	r2, r3
	bne	.L1009
	mov	r7, #1
	b	.L1002
.L1001:
	ldr	r1, [r7, #3704]
	cmp	r1, #0
	beq	.L973
	ldr	r2, [r7, #3708]
	cmp	r2, #0
	bne	.L1089
.L973:
	mov	r3, #0
	strb	r3, [r4, #2533]
	ldr	r3, [fp, #-120]
	cmp	r10, r3, asl #3
	bls	.L1090
.L975:
	ldr	r1, .L1094+12
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r2, [fp, #-124]
	ldr	r3, [r7, #3592]
	rsb	r8, r8, r2
	bic	r3, r3, #432
	mov	r10, r8, asl #3
	bic	r3, r3, #2
	str	r3, [r7, #3592]
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1073:
	ldr	r3, [r9, #52]
	mov	r2, #32
	sub	r1, fp, #108
	sub	r0, fp, #76
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #32
	mov	r4, r0
	sub	r0, fp, #76
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r4, r3
	bne	.L946
	ldr	r3, .L1094+4
	add	r4, r6, #20480
	mov	r2, #1
	strb	r2, [r4, #2532]
	ldr	r5, [r3]
	cmp	r5, r10
	beq	.L947
	mov	r3, r10
	mov	r2, r10
	mov	r1, #117
	ldr	r0, [r4, #2496]
	blx	r5
.L947:
	ldr	r3, [r7, #3592]
	add	r1, r6, #15680
	add	r1, r1, #32
	mov	r10, #0
	tst	r3, #130
	orrne	r3, r3, #32
	strne	r3, [r7, #3592]
	movne	r2, #1
	strne	r2, [r7, #3596]
	ldr	r0, [r4, #2496]
	bl	MP4_ClearCurPacket
	b	.L1070
.L946:
	add	r3, r6, #12288
	ldrb	r3, [r3, #3584]	@ zero_extendqisi2
	tst	r3, #1
	bne	.L950
	add	r4, r6, #20480
	mov	r2, #2
	strb	r2, [r4, #805]
	b	.L951
.L967:
	ldr	r3, [fp, #-120]
	add	r1, r6, #15680
	ldr	r0, [r4, #2496]
	add	r1, r1, #32
	sub	r3, r3, #4
	str	r3, [fp, #-120]
	add	r3, r8, #4
	str	r3, [fp, #-124]
	bl	MP4_ClearCurPacket
	b	.L970
.L1077:
	ldr	r1, .L1094+16
	mov	r0, #2
	bl	dprint_vfmw
	str	r10, [r4, #2108]
	mov	r1, r8
	ldr	r2, [fp, #-120]
	mov	r0, r6
	bl	Mp4_Syntax_Vos
	mov	r1, r5
	mov	r10, r0
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L956
.L982:
	ldr	r7, [r4, #2500]
	subs	r7, r7, #1
	movne	r7, #1
	cmp	r2, #0
	beq	.L985
.L1003:
	ldr	r3, [r4, #2092]
	cmp	r2, r3
	bne	.L981
.L984:
	cmp	r1, #0
	beq	.L985
.L1002:
	ldr	r3, [r4, #2096]
	cmp	r1, r3
	beq	.L985
	b	.L981
.L1081:
	ldr	r1, .L1094+20
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r3, [fp, #-120]
	cmp	r3, #4
	beq	.L1091
	ldr	r2, [fp, #-120]
	mov	r1, r8
	mov	r0, r6
	bl	Mp4_Syntax_Vop
	ldr	r3, [r7, #3592]
	tst	r3, #2
	mov	r10, r0
	bne	.L963
	add	r1, r6, #15680
	ldr	r0, [r4, #2496]
	add	r1, r1, #32
	bl	MP4_ClearCurPacket
.L962:
	mov	r2, r10
	ldr	r1, .L1094+24
	mov	r0, #7
	bl	dprint_vfmw
	b	.L956
.L1084:
	ldr	r3, [r4, #1512]
	cmp	r3, r1
	bne	.L992
	ldr	r5, [r4, #2500]
	subs	r5, r5, #1
	movne	r5, #1
	b	.L993
.L1078:
	ldr	r1, .L1094+28
	mov	r0, #2
	bl	dprint_vfmw
	mov	r3, #1
	mov	r1, r8
	ldr	r2, [fp, #-120]
	str	r3, [r4, #2108]
	mov	r0, r6
	bl	Mp4_Syntax_Vo
	mov	r1, r5
	mov	r10, r0
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L956
.L1079:
	ldr	r1, .L1094+32
	mov	r0, #2
	bl	dprint_vfmw
	mov	r3, #2
	ldr	r2, [fp, #-120]
	mov	r1, r8
	str	r3, [r4, #2108]
	mov	r0, r6
	bl	Mp4_Syntax_Vol
	mov	r1, r5
	mov	r10, r0
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	ldrb	r3, [r4, #1575]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L956
	ldrb	r3, [r4, #1576]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L956
	add	r1, r6, #20480
	add	r0, r6, #19968
	str	r3, [fp, #-124]
	add	r1, r1, #132
	ldr	r3, [r9, #52]
	add	r0, r0, #40
	mov	r2, #604
	blx	r3
	ldr	r3, [fp, #-124]
	strb	r3, [r4, #1575]
	strb	r3, [r4, #797]
	b	.L956
.L1076:
	ldr	r1, .L1094+36
	mov	r0, #2
	bl	dprint_vfmw
	add	r1, r6, #15680
	add	r1, r1, #32
	ldr	r0, [r4, #2496]
	bl	MP4_ClearCurPacket
	b	.L1070
.L1088:
	ldr	r7, [r4, #2500]
	subs	r7, r7, #1
	movne	r7, #1
	cmp	r2, #0
	beq	.L984
	b	.L1003
.L1086:
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L978
	ldr	r2, [r4, #1524]
	ldr	r3, [r4, #1516]
	ldr	r0, [r4, #1520]
	str	r2, [r4, #1528]
	add	r2, r2, r3
	str	r2, [r4, #1524]
	ldr	r3, [r7, #3696]
	ldr	r1, [r4, #1536]
	mla	r3, r3, r2, r0
	rsb	r2, r1, r3
	str	r2, [r4, #1540]
	str	r3, [r4, #1532]
	str	r3, [r4, #1536]
	b	.L979
.L1080:
	ldr	r1, .L1094+40
	mov	r0, #2
	bl	dprint_vfmw
	mov	r3, #3
	mov	r1, r8
	ldr	r2, [fp, #-120]
	str	r3, [r4, #2108]
	mov	r0, r6
	bl	Mp4_Syntax_Gop
	mov	r1, r5
	mov	r10, r0
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L956
.L1089:
	mov	r0, r6
	bl	Frame_Init
	cmp	r0, #0
	beq	.L973
	ldr	r1, .L1094+44
	mov	r0, #0
	bl	dprint_vfmw
	b	.L973
.L1082:
	ldr	r1, .L1094+48
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r2, [fp, #-120]
	mov	r1, r8
	mov	r0, r6
	bl	Mp4_Syntax_ShortHeader
	ldr	r3, [r7, #3592]
	tst	r3, #2
	mov	r10, r0
	beq	.L1071
	mov	r1, #196
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L956
.L1083:
	ldr	r1, .L1094+52
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r2, [fp, #-120]
	mov	r1, r8
	mov	r0, r6
	bl	Mp4_Syntax_UserData
	mov	r10, r0
.L1071:
	add	r1, r6, #15680
	ldr	r0, [r4, #2496]
	add	r1, r1, #32
	bl	MP4_ClearCurPacket
	b	.L956
.L1087:
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L988
	ldr	r1, [r3, #544]
	add	r5, r3, #560
	ldr	r0, [r4, #2496]
	add	r2, r3, #576
	str	r3, [fp, #-128]
	str	r2, [fp, #-120]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-128]
	ldr	r1, [r5, #-8]
	ldr	r0, [r4, #2496]
	add	r2, r3, #544
	str	r3, [fp, #-132]
	str	r2, [fp, #-128]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-132]
	ldr	r0, [r4, #2496]
	ldr	r1, [r3, #560]
	bl	FreeUsdByDec
	ldr	r2, [fp, #-120]
	ldr	r0, [r4, #2496]
	ldr	r1, [r2, #-8]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-120]
	ldr	r2, [fp, #-128]
	mov	r0, #0
	mov	r1, #0
	strd	r0, [r2]
	mov	r2, r7
	strd	r0, [r5, #-8]
	strd	r0, [r5]
	strd	r0, [r3, #-8]
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r2, r7
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2508]
	str	r3, [r4, #2516]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2516]
	str	r0, [r4, #2508]
.L988:
	add	r5, r6, #22528
	mov	r3, #0
	add	r5, r5, #96
	str	r3, [r4, #2504]
	ldr	r0, [r4, #2496]
	mov	r1, r5
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r4, #1596]
	ldr	r2, [r3, #732]
	cmp	r2, #0
	bne	.L989
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1092
.L989:
	ldr	r2, [r4, #2104]
	mov	r0, r6
	ldr	r1, [r4, #2100]
	bl	Frame_Init
	cmp	r0, #0
	beq	.L987
	ldr	r1, .L1094+56
	mov	r0, #0
	bl	dprint_vfmw
	b	.L987
.L963:
	movw	r1, #438
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L962
.L978:
	ldr	r1, [r4, #1528]
	ldr	r2, [r4, #1516]
	ldr	r3, [r7, #3696]
	ldr	r0, [r4, #1520]
	add	r2, r2, r1
	ldr	r1, [r4, #1540]
	mla	r3, r3, r2, r0
	ldr	r2, [r4, #1536]
	rsb	r2, r2, r1
	add	r2, r2, r3
	str	r2, [r4, #1544]
	str	r3, [r4, #1532]
	b	.L979
.L1091:
	mov	r1, r5
	mov	r0, r6
	bl	MP4_Record_HeadPacketInfo
	b	.L962
.L1085:
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L997
	ldr	r1, [r8, #544]
	add	r3, r8, #576
	ldr	r0, [r4, #2496]
	add	r9, r8, #560
	str	r3, [fp, #-120]
	bl	FreeUsdByDec
	ldr	r1, [r8, #552]
	add	r3, r8, #544
	ldr	r0, [r4, #2496]
	str	r3, [fp, #-124]
	bl	FreeUsdByDec
	ldr	r1, [r8, #560]
	ldr	r0, [r4, #2496]
	bl	FreeUsdByDec
	ldr	r8, [fp, #-120]
	ldr	r0, [r4, #2496]
	ldr	r1, [r8, #-8]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-124]
	mov	r0, #0
	mov	r1, #0
	mov	r2, r5
	strd	r0, [r3]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #2516]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r2, r5
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2508]
	str	r3, [r4, #2516]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2516]
	str	r0, [r4, #2508]
.L997:
	add	r5, r6, #22528
	mov	r3, #0
	add	r5, r5, #96
	str	r3, [r4, #2504]
	ldr	r0, [r4, #2496]
	mov	r1, r5
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r4, #1596]
	ldr	r2, [r3, #732]
	cmp	r2, #0
	bne	.L998
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1093
.L998:
	mov	r0, r6
	ldr	r2, [r4, #1508]
	ldr	r1, [r4, #1512]
	bl	Frame_Init
	cmp	r0, #0
	beq	.L996
	ldr	r1, .L1094+60
	mov	r0, #0
	bl	dprint_vfmw
	b	.L996
.L1092:
	ldr	r3, [r4, #2500]
	cmp	r3, #0
	bne	.L989
	mov	r0, r5
	bl	ResetVoQueue
	b	.L989
.L1093:
	ldr	r3, [r4, #2500]
	cmp	r3, #0
	bne	.L998
	mov	r0, r5
	bl	ResetVoQueue
	b	.L998
.L1095:
	.align	2
.L1094:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC69
	.word	.LC71
	.word	.LC59
	.word	.LC63
	.word	.LC64
	.word	.LC60
	.word	.LC61
	.word	.LC58
	.word	.LC62
	.word	.LC67
	.word	.LC65
	.word	.LC66
	.word	.LC68
	.word	.LC70
	UNWIND(.fnend)
	.size	Mp4_Syntax_Parse, .-Mp4_Syntax_Parse
	.align	2
	.global	MP4_Combine_HdPacket
	.type	MP4_Combine_HdPacket, %function
MP4_Combine_HdPacket:
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
	add	r5, r0, #20480
	ldr	r3, [r5, #1632]
	cmp	r3, #0
	beq	.L1108
	add	r3, r0, #12288
	ldrb	r4, [r3, #3430]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L1109
	cmp	r4, #0
	bne	.L1104
	ldrb	r2, [r3, #3510]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1104
	ldr	ip, .L1112
	add	r1, r0, #15744
	ldr	r2, [r5, #1648]
	add	r0, r0, #22016
	ldr	r3, [r3, #3440]
	add	r1, r1, #48
	ldr	r6, [ip, #52]
	add	r0, r0, #176
	add	r3, r3, r2
	mov	r2, #80
	str	r3, [r5, #1648]
	blx	r6
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1109:
	ldrb	r4, [r5, #1638]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L1110
	cmp	r4, #0
	bne	.L1103
	ldrb	r2, [r5, #1718]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1103
	ldr	r3, [r3, #3440]
	mov	r0, r4
	ldr	r2, [r5, #1728]
	add	r3, r3, r2
	str	r3, [r5, #1728]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1104:
	movw	r2, #4974
	ldr	r1, .L1112+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1110:
	ldr	r1, [r3, #3436]
	ldr	r2, [r5, #1644]
	cmp	r1, r2
	bcc	.L1111
	ldr	r3, [r3, #3440]
	mov	r0, #0
	ldr	r2, [r5, #1648]
	add	r3, r3, r2
	str	r3, [r5, #1648]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1103:
	movw	r2, #4960
	ldr	r1, .L1112+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1111:
	ldr	r3, .L1112
	add	r1, r0, #15680
	add	r0, r0, #22016
	add	r1, r1, #32
	mov	r2, #80
	add	r0, r0, #176
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #0
	strb	r4, [r5, #1718]
	mov	r0, r3
	strb	r3, [r5, #1638]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1108:
	ldr	r2, .L1112+8
	ldr	r4, [r2]
	cmp	r4, #0
	beq	.L1098
	ldr	r0, [r5, #2496]
	mov	r2, r3
	mov	r1, #103
	blx	r4
.L1098:
	ldr	r1, .L1112+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1113:
	.align	2
.L1112:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC37
	.word	g_event_report
	.word	.LC72
	UNWIND(.fnend)
	.size	MP4_Combine_HdPacket, .-MP4_Combine_HdPacket
	.align	2
	.global	MP4_Renew_CurPacket
	.type	MP4_Renew_CurPacket, %function
MP4_Renew_CurPacket:
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
	bl	MP4_Combine_HdPacket
	cmn	r0, #1
	mov	r5, r0
	beq	.L1117
	ldr	r5, .L1118
	mov	r0, r4
	bl	MP4_Record_PacketID
	add	r1, r4, #22016
	add	r0, r4, #15680
	add	r1, r1, #96
	ldr	r3, [r5, #52]
	mov	r2, #160
	add	r0, r0, #32
	blx	r3
	add	r0, r4, #15744
	ldr	r3, [r5, #52]
	add	r1, r4, #22272
	mov	r2, #4
	add	r0, r0, #40
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1117:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #32
	ldr	r0, [r3, #2496]
	bl	MP4_ClearCurPacket
	movw	r2, #4990
	ldr	r1, .L1118+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1119:
	.align	2
.L1118:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC73
	UNWIND(.fnend)
	.size	MP4_Renew_CurPacket, .-MP4_Renew_CurPacket
	.align	2
	.global	MP4_Check_CurPacket
	.type	MP4_Check_CurPacket, %function
MP4_Check_CurPacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r4, r0, #12288
	add	r5, r0, #20480
	mov	r3, #0
	ldr	r2, [r4, #3436]
	mov	r6, r0
	sub	r0, fp, #60
	str	r2, [r5, #1584]
	ldr	r1, [r4, #3424]
	str	r1, [r5, #1580]
	ldr	r2, [r4, #3440]
	str	r3, [r5, #1592]
	str	r2, [r5, #1588]
	bl	BsInit
	sub	r0, fp, #60
	mov	r1, #32
	bl	BsShow
	ldrb	r3, [r4, #3584]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L1146
	mov	r3, #1
	strb	r3, [r5, #805]
	ldrb	r3, [r4, #3584]	@ zero_extendqisi2
	tst	r3, #2
	bne	.L1123
	ldr	r3, [r5, #2056]
	mov	r1, #196
.L1127:
	movw	r2, #438
	cmp	r1, r2
	cmpeq	r3, r2
	beq	.L1134
	cmp	r1, #196
	cmpeq	r3, #196
	bne	.L1144
.L1134:
	ldr	r3, [r5, #2064]
	cmp	r3, #1
	bgt	.L1126
	b	.L1144
.L1146:
	mov	r3, r0, lsr #8
	mov	r2, #2
	sub	r3, r3, #128
	strb	r2, [r5, #805]
	cmp	r3, #3
	mov	r1, r0
	bls	.L1147
.L1122:
	ldrb	r3, [r4, #3584]	@ zero_extendqisi2
	tst	r3, #2
	ldr	r3, [r5, #2056]
	bne	.L1125
	movw	r2, #438
	cmp	r3, r2
	cmpne	r0, #196
	beq	.L1127
.L1126:
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
.L1144:
	mov	r0, #0
.L1131:
	ldr	r3, [r4, #3424]
	cmp	r3, #0
	beq	.L1137
	ldr	r3, [r4, #3436]
	cmp	r3, #0
	mvneq	r0, #0
.L1143:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1125:
	movw	r2, #438
	sub	r0, r0, #196
	rsb	r3, r2, r3
	clz	r0, r0
	clz	r3, r3
	mov	r0, r0, lsr #5
	mov	r3, r3, lsr #5
	orrs	r2, r0, r3
	beq	.L1128
	ldrb	r2, [r5, #1577]	@ zero_extendqisi2
	cmp	r2, #1
	orreq	r0, r0, #1
	cmp	r0, #0
	bne	.L1136
.L1128:
	mov	r0, r6
	bl	MP4_Renew_CurPacket
	b	.L1131
.L1123:
	ldr	r3, [r5, #2056]
	movw	r2, #438
	rsb	r3, r2, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
.L1136:
	ldr	r2, [r5, #2060]
	cmp	r2, #1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r3, #0
	beq	.L1144
	ldr	r3, [r5, #1648]
	cmp	r3, #4
	bne	.L1144
	b	.L1128
.L1147:
	ldrb	r3, [r4, #3584]	@ zero_extendqisi2
	orr	r3, r3, r2
	strb	r3, [r4, #3584]
	b	.L1122
.L1137:
	mvn	r0, #0
	b	.L1143
	UNWIND(.fnend)
	.size	MP4_Check_CurPacket, .-MP4_Check_CurPacket
	.align	2
	.global	MPEG4DEC_Decode
	.type	MPEG4DEC_Decode, %function
MPEG4DEC_Decode:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r0
	mov	r5, r1
	moveq	r9, #1
	movne	r9, #0
	beq	.L1242
	add	r4, r0, #20480
	ldr	r3, [r4, #2084]
	cmp	r3, #0
	beq	.L1151
	ldr	r3, [r1, #16]
	cmp	r3, #0
	beq	.L1151
	ldr	r3, [r1, #12]
	cmp	r3, #0
	beq	.L1151
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L1151
	ldr	r1, .L1257
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r2, [r5, #12]
	ldr	r1, .L1257+4
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r2, [r5, #16]
	ldr	r1, .L1257+8
	mov	r0, #7
	bl	dprint_vfmw
	ldrb	r2, [r5, #6]	@ zero_extendqisi2
	ldr	r1, .L1257+12
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r2, [r5, #92]
	ldr	r1, .L1257+16
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r2, [r5, #96]
	ldr	r1, .L1257+20
	mov	r0, #7
	bl	dprint_vfmw
	ldrb	r2, [r5, #86]	@ zero_extendqisi2
	ldr	r1, .L1257+24
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r2, [r5, #16]
	ldr	r1, .L1257+28
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r1, .L1257+32
	mov	r0, #7
	add	r8, r6, #15680
	ldrb	r2, [r3]	@ zero_extendqisi2
	add	r8, r8, #32
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r1, .L1257+36
	mov	r0, #7
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r1, .L1257+40
	mov	r0, #7
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r1, .L1257+44
	mov	r0, #7
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r3, .L1257+48
	mov	r2, #160
	mov	r1, r5
	mov	r0, r8
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, r8
	mov	r0, r6
	bl	MP4_GetScdUpMsg
	mov	r0, r6
	bl	MP4_Check_CurPacket
	cmn	r0, #1
	mov	r7, r0
	beq	.L1243
	mov	r1, r8
	mov	r0, r6
	bl	MP4_GetScdUpMsg
	add	r3, r6, #12288
	mov	r0, r6
	ldr	r2, [r3, #3436]
	str	r2, [r4, #1584]
	ldr	r2, [r3, #3424]
	str	r2, [r4, #1580]
	ldr	r3, [r3, #3440]
	str	r9, [r4, #1592]
	str	r3, [r4, #1588]
	bl	Mp4_Get_DecMode
	ldr	r3, [r4, #1596]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L1244
.L1154:
	add	r7, r6, #16384
	ldr	r3, [r7, #3592]
	str	r3, [r4, #2536]
.L1155:
	ldr	r2, [r4, #1588]
	mov	r0, r6
	ldr	r1, [r4, #1580]
	bl	Mp4_Syntax_Parse
	ldr	r3, [r4, #1580]
	ldr	ip, [r4, #1596]
	ldr	r1, [r4, #1584]
	mov	r2, r0, lsr #3
	and	r0, r0, #7
	add	r3, r3, r2
	str	r3, [r4, #1580]
	ldr	r3, [r4, #1588]
	add	r1, r2, r1
	str	r0, [r4, #1592]
	rsb	r3, r2, r3
	str	r1, [r4, #1584]
	str	r3, [r4, #1588]
	ldr	r3, [ip, #872]
	cmp	r3, #1
	beq	.L1245
.L1156:
	ldr	r3, [r7, #3592]
	tst	r3, #288
	beq	.L1157
	bic	r3, r3, #432
	bic	r3, r3, #2
	str	r3, [r7, #3592]
	ldr	r3, [r4, #1628]
	cmp	r3, #2
	beq	.L1246
	cmp	r3, #1
	beq	.L1247
	cmp	r3, #4
	bne	.L1160
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1162
	ldr	r3, [r4, #2112]
	cmp	r3, #0
	moveq	r3, #2
	movne	r3, #1
	str	r3, [r4, #2112]
.L1160:
	mov	r0, r6
	bl	Mp4_Frame_Atr
	cmn	r0, #1
	mov	r7, r0
	beq	.L1248
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #2516]
	mov	r8, r0
	ldr	r0, [r4, #2496]
	bl	FSP_GetFsImagePtr
	clz	r2, r8
	mov	r2, r2, lsr #5
	clz	r1, r0
	mov	r3, r0
	mov	r1, r1, lsr #5
	orrs	r10, r1, r2
	bne	.L1249
	ldrb	r0, [r4, #803]	@ zero_extendqisi2
	and	r9, r0, #253
	cmp	r9, #1
	beq	.L1250
	cmp	r0, #2
	beq	.L1251
.L1171:
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1181
	ldr	r3, [r4, #2504]
	ldr	r1, [r4, #2508]
	cmp	r3, #0
	ldr	r3, [r4, #2516]
	movgt	r2, #2
	movle	r2, #1
	cmp	r1, r3
	str	r2, [r4, #2504]
	beq	.L1179
	mov	r2, #0
	ldr	r0, [r4, #2496]
	bl	FSP_SetRef
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_GetDisplay
	cmp	r0, #3
	beq	.L1239
	mov	r2, #0
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_SetDisplay
.L1239:
	ldr	r3, [r4, #2516]
.L1179:
	str	r3, [r4, #2508]
	mov	r2, #1
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	strb	r3, [r6]
	ldr	r3, [r4, #2520]
	ldr	r1, [r4, #2524]
	str	r3, [r4, #2512]
	str	r1, [r4, #2516]
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	strb	r3, [r6, #1]
	ldr	r3, [r4, #1540]
	ldr	r0, [r4, #2496]
	str	r3, [r4, #2520]
	bl	FSP_SetRef
	ldr	r1, [r4, #2508]
	ldr	r0, [r4, #2496]
	bl	FSP_RemovePmv
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L1181
	ldrb	r5, [r4, #800]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L1252
.L1192:
	mov	r7, #0
.L1234:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1250:
	cmp	r2, #0
	bne	.L1169
	ldr	r3, [r4, #1596]
	ldr	r2, [r8, #152]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L1171
	mov	r2, r9
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [r4, #1596]
	ldr	r2, [r8, #152]
	mov	r0, r9
	ldr	r1, .L1257+52
	ldr	r3, [r3]
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1162:
	sub	r2, r3, #2
	tst	r2, #253
	bne	.L1165
	ldr	r2, [r4, #2112]
	cmp	r2, #2
	beq	.L1240
.L1165:
	cmp	r3, #1
	streq	r3, [r4, #2112]
	b	.L1160
.L1245:
	ldr	r3, [ip, #920]
	cmp	r3, #0
	beq	.L1156
	b	.L1192
.L1244:
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L1154
	ldr	r3, [r4, #2536]
	add	r7, r6, #16384
	str	r3, [r7, #3592]
	b	.L1155
.L1181:
	mov	r2, r5
	mov	r1, #0
	mov	r0, r6
	bl	Mp4_Set_DecPar
	ldrb	r7, [r4, #1448]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L1253
	ldr	r3, [r4, #2112]
	cmp	r3, #0
	moveq	r3, #2
	movne	r3, #1
	str	r3, [r4, #2112]
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1596]
	ldr	r2, [r1, #912]
	cmp	r2, #1
	beq	.L1191
.L1190:
	cmp	r2, #2
	beq	.L1197
.L1191:
	cmp	r7, #0
	mov	r3, #0
	strb	r3, [r6, #1198]
	bne	.L1192
	ldr	r3, .L1257+56
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L1192
	sub	r2, fp, #44
	ldr	r0, [r4, #2496]
	mov	r3, #4
	mov	r1, #20
	str	r7, [r2, #-4]!
	blx	r5
	b	.L1234
.L1253:
	sub	r3, r7, #2
	sub	r10, r7, #2
	clz	r10, r10
	ands	r5, r3, #253
	mov	r10, r10, lsr #5
	bne	.L1185
	ldr	r3, [r4, #2112]
	cmp	r3, #2
	beq	.L1254
.L1185:
	cmp	r7, #1
	beq	.L1255
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1596]
	ldr	r2, [r1, #912]
	cmp	r2, #1
	bne	.L1190
	cmp	r3, #0
	moveq	r10, #0
	andne	r10, r10, #1
	cmp	r10, #0
	beq	.L1191
	mov	r3, #0
	str	r3, [r6, #1036]
	ldr	r1, [r4, #2524]
	mvn	r7, #0
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1234
.L1246:
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1160
.L1159:
	mov	r0, r6
	mvn	r7, #0
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1234
.L1247:
	ldrb	r3, [r4, #1448]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L1160
	b	.L1159
.L1252:
	ldr	r1, .L1257+60
	mov	r0, #11
	bl	dprint_vfmw
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #2508]
	mov	r8, r0
	ldr	r0, [r4, #2496]
	bl	FSP_GetLogicFs
	cmp	r8, #0
	cmpne	r0, #0
	mov	r9, r0
	beq	.L1256
	ldr	r2, [r8, #28]
	cmp	r2, #0
	beq	.L1194
	ldr	r3, [r8, #32]
	cmp	r3, #0
	beq	.L1194
	ldr	r1, [r0, #28]
	mov	r0, r6
	ldr	ip, [r4, #1508]
	mov	r7, #0
	cmp	r1, #0
	ldr	r2, [r2, #8]
	ldr	r3, [r3, #8]
	ldrne	lr, [r1, #8]
	mov	r1, r8
	str	ip, [sp, #8]
	moveq	lr, r2
	ldr	ip, [r4, #1512]
	str	lr, [sp]
	str	ip, [sp, #4]
	bl	Vdm_Mem_Move
	b	.L1234
.L1255:
	str	r7, [r4, #2112]
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1596]
	ldr	r2, [r1, #912]
	cmp	r2, #1
	beq	.L1188
	cmp	r2, #2
	beq	.L1197
.L1188:
	mov	r3, #0
	strb	r3, [r6, #1198]
	b	.L1192
.L1151:
	ldr	r1, .L1257+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1251:
	cmp	r2, #0
	bne	.L1172
	ldr	r2, [r4, #1596]
	ldr	r0, [r8, #152]
	ldr	r2, [r2]
	cmp	r0, r2
	bhi	.L1173
	cmp	r1, #0
	bne	.L1174
	ldr	r1, [r3, #152]
	cmp	r2, r1
	bcs	.L1171
.L1174:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	str	r3, [fp, #-56]
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [fp, #-56]
	ldr	ip, [r4, #1596]
	mov	r0, #1
	ldr	r1, .L1257+68
	ldr	r2, [r3, #152]
	ldr	r3, [ip]
	bl	dprint_vfmw
	b	.L1234
.L1173:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [r4, #1596]
	ldr	r2, [r8, #152]
	mov	r0, #1
	ldr	r1, .L1257+72
	ldr	r3, [r3]
	bl	dprint_vfmw
	b	.L1234
.L1254:
	mov	r2, #1
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	ldr	r3, .L1257+56
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L1240
	ldr	r0, [r4, #2496]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #127
	blx	r6
	mvn	r7, #0
	b	.L1234
.L1249:
	movw	r3, #3683
	ldr	r2, .L1257+76
	ldr	r1, .L1257+80
	mov	r0, #1
	bl	dprint_vfmw
.L1240:
	mvn	r7, #0
	b	.L1234
.L1197:
	ldr	r2, [r1, #916]
	cmp	r2, #0
	andgt	r10, r10, #1
	movle	r10, #0
	cmp	r3, #0
	moveq	r3, #0
	andne	r3, r10, #1
	cmp	r3, #0
	beq	.L1191
	mov	r3, #0
	mov	r2, #1
	str	r3, [r6, #1036]
	mvn	r7, #0
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #1596]
	mov	r0, r6
	ldr	r3, [r2, #916]
	add	r3, r3, r7
	str	r3, [r2, #916]
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1234
.L1169:
	mov	r2, r9
	ldr	r1, [r4, #2524]
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	mov	r0, r9
	movw	r3, #3697
	ldr	r2, .L1257+76
	ldr	r1, .L1257+84
	bl	dprint_vfmw
	b	.L1234
.L1242:
	movw	r2, #3556
	ldr	r1, .L1257+88
	mov	r0, #0
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L1234
.L1243:
	ldr	r1, .L1257+92
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1234
.L1157:
	ldr	r1, .L1257+96
	mov	r0, #2
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L1234
.L1248:
	ldr	r1, .L1257+100
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1234
.L1172:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	movw	r3, #3717
	ldr	r2, .L1257+76
	mov	r0, #1
	ldr	r1, .L1257+84
	bl	dprint_vfmw
	b	.L1234
.L1256:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	mov	r3, r8
	movw	r2, #3868
	ldr	r1, .L1257+104
	str	r9, [sp]
	mov	r0, r5
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1234
.L1194:
	ldr	r1, [r4, #2524]
	mov	r2, #1
	ldr	r0, [r4, #2496]
	mvn	r7, #0
	bl	FSP_ClearLogicFs
	ldr	r3, [r8, #32]
	ldr	r1, .L1257+108
	mov	r0, #0
	str	r3, [sp, #8]
	ldr	r3, [r8, #28]
	str	r3, [sp, #4]
	ldr	r3, [r4, #2516]
	str	r3, [sp]
	ldr	r3, [r4, #2524]
	ldr	r2, [r4, #2508]
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1234
.L1258:
	.align	2
.L1257:
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC84
	.word	.LC85
	.word	.LC86
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC95
	.word	g_event_report
	.word	.LC90
	.word	.LC74
	.word	.LC97
	.word	.LC96
	.word	.LANCHOR1+1356
	.word	.LC89
	.word	.LC94
	.word	.LC30
	.word	.LC87
	.word	.LC93
	.word	.LC88
	.word	.LC91
	.word	.LC92
	UNWIND(.fnend)
	.size	MPEG4DEC_Decode, .-MPEG4DEC_Decode
	.align	2
	.global	MPEG4DEC_GetImageWidth
	.type	MPEG4DEC_GetImageWidth, %function
MPEG4DEC_GetImageWidth:
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
	beq	.L1262
	add	r3, r3, #20480
	ldr	r0, [r3, #1512]
	ldmfd	sp, {fp, sp, pc}
.L1262:
	movw	r2, #5010
	ldr	r1, .L1263
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1264:
	.align	2
.L1263:
	.word	.LC30
	UNWIND(.fnend)
	.size	MPEG4DEC_GetImageWidth, .-MPEG4DEC_GetImageWidth
	.align	2
	.global	MPEG4DEC_GetImageHeight
	.type	MPEG4DEC_GetImageHeight, %function
MPEG4DEC_GetImageHeight:
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
	beq	.L1268
	add	r3, r3, #20480
	ldr	r0, [r3, #1508]
	ldmfd	sp, {fp, sp, pc}
.L1268:
	movw	r2, #5021
	ldr	r1, .L1269
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1270:
	.align	2
.L1269:
	.word	.LC30
	UNWIND(.fnend)
	.size	MPEG4DEC_GetImageHeight, .-MPEG4DEC_GetImageHeight
	.global	sprite_trajectory_len
	.global	default_inter_matrix
	.global	default_intra_matrix
	.global	scan_tables
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	default_intra_matrix, %object
	.size	default_intra_matrix, 256
default_intra_matrix:
	.word	8
	.word	17
	.word	18
	.word	19
	.word	21
	.word	23
	.word	25
	.word	27
	.word	17
	.word	18
	.word	19
	.word	21
	.word	23
	.word	25
	.word	27
	.word	28
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	26
	.word	28
	.word	30
	.word	21
	.word	22
	.word	23
	.word	24
	.word	26
	.word	28
	.word	30
	.word	32
	.word	22
	.word	23
	.word	24
	.word	26
	.word	28
	.word	30
	.word	32
	.word	35
	.word	23
	.word	24
	.word	26
	.word	28
	.word	30
	.word	32
	.word	35
	.word	38
	.word	25
	.word	26
	.word	28
	.word	30
	.word	32
	.word	35
	.word	38
	.word	41
	.word	27
	.word	28
	.word	30
	.word	32
	.word	35
	.word	38
	.word	41
	.word	45
	.type	default_inter_matrix, %object
	.size	default_inter_matrix, 256
default_inter_matrix:
	.word	16
	.word	17
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	17
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	25
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	26
	.word	27
	.word	20
	.word	21
	.word	22
	.word	23
	.word	25
	.word	26
	.word	27
	.word	28
	.word	21
	.word	22
	.word	23
	.word	24
	.word	26
	.word	27
	.word	28
	.word	30
	.word	22
	.word	23
	.word	24
	.word	26
	.word	27
	.word	28
	.word	30
	.word	31
	.word	23
	.word	24
	.word	25
	.word	27
	.word	28
	.word	30
	.word	31
	.word	33
	.type	scan_tables, %object
	.size	scan_tables, 768
scan_tables:
	.word	0
	.word	1
	.word	8
	.word	16
	.word	9
	.word	2
	.word	3
	.word	10
	.word	17
	.word	24
	.word	32
	.word	25
	.word	18
	.word	11
	.word	4
	.word	5
	.word	12
	.word	19
	.word	26
	.word	33
	.word	40
	.word	48
	.word	41
	.word	34
	.word	27
	.word	20
	.word	13
	.word	6
	.word	7
	.word	14
	.word	21
	.word	28
	.word	35
	.word	42
	.word	49
	.word	56
	.word	57
	.word	50
	.word	43
	.word	36
	.word	29
	.word	22
	.word	15
	.word	23
	.word	30
	.word	37
	.word	44
	.word	51
	.word	58
	.word	59
	.word	52
	.word	45
	.word	38
	.word	31
	.word	39
	.word	46
	.word	53
	.word	60
	.word	61
	.word	54
	.word	47
	.word	55
	.word	62
	.word	63
	.word	0
	.word	1
	.word	2
	.word	3
	.word	8
	.word	9
	.word	16
	.word	17
	.word	10
	.word	11
	.word	4
	.word	5
	.word	6
	.word	7
	.word	15
	.word	14
	.word	13
	.word	12
	.word	19
	.word	18
	.word	24
	.word	25
	.word	32
	.word	33
	.word	26
	.word	27
	.word	20
	.word	21
	.word	22
	.word	23
	.word	28
	.word	29
	.word	30
	.word	31
	.word	34
	.word	35
	.word	40
	.word	41
	.word	48
	.word	49
	.word	42
	.word	43
	.word	36
	.word	37
	.word	38
	.word	39
	.word	44
	.word	45
	.word	46
	.word	47
	.word	50
	.word	51
	.word	56
	.word	57
	.word	58
	.word	59
	.word	52
	.word	53
	.word	54
	.word	55
	.word	60
	.word	61
	.word	62
	.word	63
	.word	0
	.word	8
	.word	16
	.word	24
	.word	1
	.word	9
	.word	2
	.word	10
	.word	17
	.word	25
	.word	32
	.word	40
	.word	48
	.word	56
	.word	57
	.word	49
	.word	41
	.word	33
	.word	26
	.word	18
	.word	3
	.word	11
	.word	4
	.word	12
	.word	19
	.word	27
	.word	34
	.word	42
	.word	50
	.word	58
	.word	35
	.word	43
	.word	51
	.word	59
	.word	20
	.word	28
	.word	5
	.word	13
	.word	6
	.word	14
	.word	21
	.word	29
	.word	36
	.word	44
	.word	52
	.word	60
	.word	37
	.word	45
	.word	53
	.word	61
	.word	22
	.word	30
	.word	7
	.word	15
	.word	23
	.word	31
	.word	38
	.word	46
	.word	54
	.word	62
	.word	39
	.word	47
	.word	55
	.word	63
	.type	__FUNCTION__.13965, %object
	.size	__FUNCTION__.13965, 15
__FUNCTION__.13965:
	.ascii	"Mp4_Set_DecPar\000"
	.space	1
	.type	__FUNCTION__.14099, %object
	.size	__FUNCTION__.14099, 23
__FUNCTION__.14099:
	.ascii	"Mp4_Syntax_Slice_NotSH\000"
	.space	1
	.type	__FUNCTION__.14113, %object
	.size	__FUNCTION__.14113, 20
__FUNCTION__.14113:
	.ascii	"Mp4_Syntax_Slice_SH\000"
	.type	__FUNCTION__.14128, %object
	.size	__FUNCTION__.14128, 14
__FUNCTION__.14128:
	.ascii	"MP4_Dec_Slice\000"
	.space	2
	.type	__FUNCTION__.14002, %object
	.size	__FUNCTION__.14002, 16
__FUNCTION__.14002:
	.ascii	"MPEG4DEC_Decode\000"
	.data
	.align	2
.LANCHOR0 = . + 0
	.type	sprite_trajectory_len, %object
	.size	sprite_trajectory_len, 120
sprite_trajectory_len:
	.word	0
	.byte	2
	.space	3
	.word	2
	.byte	3
	.space	3
	.word	3
	.byte	3
	.space	3
	.word	4
	.byte	3
	.space	3
	.word	5
	.byte	3
	.space	3
	.word	6
	.byte	3
	.space	3
	.word	14
	.byte	4
	.space	3
	.word	30
	.byte	5
	.space	3
	.word	62
	.byte	6
	.space	3
	.word	126
	.byte	7
	.space	3
	.word	254
	.byte	8
	.space	3
	.word	510
	.byte	9
	.space	3
	.word	1022
	.byte	10
	.space	3
	.word	2046
	.byte	11
	.space	3
	.word	4094
	.byte	12
	.space	3
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"fatal stream error --- GOP marker_bit = 0\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"DivX%4dBuild%4d%c\000" )
	.space	2
.LC2:
	ASCII(.ascii	"DivX%4db%4d%c\000" )
	.space	2
.LC3:
	ASCII(.ascii	"FFmpe%*[^b]b%4d\000" )
.LC4:
	ASCII(.ascii	"FFmpeg v%4d.%4d.%4d / libavcodec build: %d\000" )
	.space	1
.LC5:
	ASCII(.ascii	"Lavc%d.%d.%d\000" )
	.space	3
.LC6:
	ASCII(.ascii	"ffmpeg\000" )
	.space	1
.LC7:
	ASCII(.ascii	"XviD%4d\000" )
.LC8:
	ASCII(.ascii	"fatal stream error --- VOP marker_bit = 0\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"VDH doesn't support SPRITE_STATIC & SPRITE_GMC\012\000" )
.LC10:
	ASCII(.ascii	"VDH doesn't support SPRITE_STATIC\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"Unknown sprite_enable\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"ERROR: not_8_bit !=0\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"not support no complexity_estimation_disable\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"not support data_partitioned\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"not support newpred_enable\012\000" )
.LC16:
	ASCII(.ascii	"not support reduced_resolution_vop_eanble\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"not support scalability\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"warning! profile_and_level_indication=%#x, maybe HD" )
	ASCII(.ascii	" pic...\012\000" )
.LC19:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC20:
	ASCII(.ascii	"actual frame size(%dx%d) exeed max config(%dx%d)\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC21:
	ASCII(.ascii	"MPEG4 Frame_Init return err!\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"MPEG4 Frame_Init PmvNum=%d, FrameNum=%d, error!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC23:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"dec_pts: %lld Usertag: %lld\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"%s %d  abnormal!\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"MPEG4DEC Init  -----\012\000" )
	.space	2
.LC30:
	ASCII(.ascii	"line: %d\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC32:
	ASCII(.ascii	"MPEG4DEC Init success -----\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"MPEG4 destroy\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"NVOP VDM copy process................\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"vop_coding_type = %d is not expected!\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	" slice num %d is not extpected!\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	" line %d packet is wrong!\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"pImg is null, pCurImg %#x pBwdImg %#x\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"FrameNum=%d\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"vop_coding_type=%d\012\000" )
.LC41:
	ASCII(.ascii	"line: %d pToQueImg is null!\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"CurImage %d is already out put\012\000" )
.LC43:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC44:
	ASCII(.ascii	"StreamIDNum = %d > (%d)\012\000" )
	.space	3
.LC45:
	ASCII(.ascii	"Warning : vop slice num %d != 0\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"warning streamIDNum %d != 0 \012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"vop ---%d\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"VDH doesn't support S_VOP\012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"parse time_module_base stream not enough\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"module time base parse error, more than %d '1' was " )
	ASCII(.ascii	"found!\012\000" )
	.space	1
.LC51:
	ASCII(.ascii	"error: vop_coding_type = %d, but vop_fcode_forward " )
	ASCII(.ascii	"= 0\012\000" )
.LC52:
	ASCII(.ascii	"error: B vop, but vop_fcode_backward = 0\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"FUN: %s Invalid SlcNum = %d\012\000" )
	.space	3
.LC54:
	ASCII(.ascii	" pSlcPara->mb_start_num = %d, MbCnt = %d\012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"pSlcPara->mb_start_num = %d, totalMbMin1 = %d\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"FUN: %s MP4_ClearCurPacket\012\000" )
.LC57:
	ASCII(.ascii	"pCtx is NUL!!!\012\000" )
.LC58:
	ASCII(.ascii	"Not find start code \012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"VOS beginning ~ !\012\000" )
	.space	1
.LC60:
	ASCII(.ascii	"VO beginning ~ !\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"VOL beginning ~ !\012\000" )
	.space	1
.LC62:
	ASCII(.ascii	"GOP beginning ~ !\012\000" )
	.space	1
.LC63:
	ASCII(.ascii	"VOP beginning ~ !\012\000" )
	.space	1
.LC64:
	ASCII(.ascii	"BitUsed=%d\012\000" )
.LC65:
	ASCII(.ascii	"SHVOP beginning ~ !\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"USERDATA beginning ~ !\012\000" )
.LC67:
	ASCII(.ascii	"MPEG4 Frame_Init return err 3!\012\000" )
.LC68:
	ASCII(.ascii	"MPEG4 Frame_Init return err 1!\012\000" )
.LC69:
	ASCII(.ascii	"vop right\012\000" )
	.space	1
.LC70:
	ASCII(.ascii	"MPEG4 Frame_Init return err 2!\012\000" )
.LC71:
	ASCII(.ascii	"bits over boundary\012\000" )
.LC72:
	ASCII(.ascii	"pLastPacket->StreamPack[0].VirAddr is NULL!!\012\000" )
	.space	2
.LC73:
	ASCII(.ascii	"line %d MP4_Combine_HdPacket failed!!\012\000" )
	.space	1
.LC74:
	ASCII(.ascii	"bitsream para error -----\012\000" )
	.space	1
.LC75:
	ASCII(.ascii	"MPEG4DEC Decode -----\012\000" )
	.space	1
.LC76:
	ASCII(.ascii	"ptr_strm_para->PhyAddr0=0x%x\012\000" )
	.space	2
.LC77:
	ASCII(.ascii	"ptr_strm_para->Length0=%d\012\000" )
	.space	1
.LC78:
	ASCII(.ascii	"ptr_strm_para->IsLastSeg0=%d\012\000" )
	.space	2
.LC79:
	ASCII(.ascii	"ptr_strm_para->PhyAddr1=0x%x\012\000" )
	.space	2
.LC80:
	ASCII(.ascii	"ptr_strm_para->Length1=%d\012\000" )
	.space	1
.LC81:
	ASCII(.ascii	"ptr_strm_para->IsLastSeg1=%d\012\000" )
	.space	2
.LC82:
	ASCII(.ascii	"ptr_strm_para->Length0 = %d\012\000" )
	.space	3
.LC83:
	ASCII(.ascii	"byte0: = 0x%x\012\000" )
	.space	1
.LC84:
	ASCII(.ascii	"byte1: = 0x%x\012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"byte2: = 0x%x\012\000" )
	.space	1
.LC86:
	ASCII(.ascii	"byte3: = 0x%x\012\000" )
	.space	1
.LC87:
	ASCII(.ascii	"MP4_Check_CurPacket failed!\012\000" )
	.space	3
.LC88:
	ASCII(.ascii	"Mp4_Frame_Atr return fail\012\000" )
	.space	1
.LC89:
	ASCII(.ascii	"fuction return value is null, %s %d!!\012\000" )
	.space	1
.LC90:
	ASCII(.ascii	"NVOP mem move--\012\000" )
	.space	3
.LC91:
	ASCII(.ascii	"line: %d pCur = %p, pFwd = %p\012\000" )
	.space	1
.LC92:
	ASCII(.ascii	"CurFsID(f%d,%d,b%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC93:
	ASCII(.ascii	"bits not enought\012\000" )
	.space	2
.LC94:
	ASCII(.ascii	"fuction return value is null,%s %d!!\012\000" )
	.space	2
.LC95:
	ASCII(.ascii	"dec P/S frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
	.space	2
.LC96:
	ASCII(.ascii	"dec B frame, bwd ref err(%d) > ref_thr(%d)\012\000" )
.LC97:
	ASCII(.ascii	"dec B frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
	.bss
	.align	2
.LANCHOR2 = . + 0
	.type	MemArrange.13903, %object
	.size	MemArrange.13903, 1232
MemArrange.13903:
	.space	1232
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
