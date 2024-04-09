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
	ldrb	r5, [r0, #65]	@ zero_extendqisi2
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
	ldr	r8, [r3, #708]
	ldr	r10, [r3, #704]
	cmp	r8, #1
	mov	r2, r8, asl #4
	str	r2, [r9, #8]
	str	r2, [fp, #-64]
	ldr	r2, [r3, #704]
	mov	r2, r2, asl #4
	str	r2, [r9, #12]
	ldrb	r2, [r3, #65]	@ zero_extendqisi2
	str	r2, [r9, #4]
	ldrb	r2, [r3, #64]	@ zero_extendqisi2
	str	r2, [r9]
	str	r2, [fp, #-68]
	ldr	r2, [r3, #688]
	ldr	r1, [r3, #680]
	ldr	lr, [r3, #692]
	str	r2, [fp, #-52]
	ldr	r2, [r3, #700]
	ldr	ip, [r3, #696]
	str	r2, [fp, #-72]
	str	r0, [fp, #-48]
	ldr	r0, [r3, #684]
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
	mov	r7, r7, lsr r4
	str	r0, [fp, #-68]
	add	r3, r3, ip
	str	ip, [fp, #-84]
	ldr	ip, [fp, #-52]
	mov	r0, r2
	add	r2, r8, r1, asl r5
	mov	r1, r10
	str	r2, [r9, #32]
	mov	r4, r6, lsr r4
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
	strne	r0, [r3, #1036]
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
	add	r0, r0, #8
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r5, #48]
	mov	r2, #604
	mov	r1, #0
	add	r0, r0, #32
	blx	r3
	add	r0, r4, #20992
	ldr	r3, [r5, #48]
	mov	r2, #60
	mov	r1, #0
	add	r0, r0, #216
	blx	r3
	add	r0, r4, #21248
	ldr	r3, [r5, #48]
	mov	r2, #768
	mov	r1, #0
	add	r0, r0, #20
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r5, #48]
	mov	r2, #7
	mov	r1, #0
	add	r0, r0, #20
	blx	r3
	ldr	r3, .L61+4
	add	r2, r4, #19968
	add	r1, r4, #20480
	add	r2, r2, #116
	add	r0, r3, #256
	mov	ip, #1
	strb	ip, [r1, #805]
	str	ip, [r1, #2120]
.L57:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L57
	ldr	r3, .L61+8
	add	r2, r4, #20224
	add	r2, r2, #116
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
	add	r0, r0, #48
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r5, #48]
	mov	r2, #16
	mov	r1, #0
	add	r0, r0, #28
	blx	r3
	mov	r0, r4
	bl	Mp4_Syntax_Init
	add	r3, r4, #20480
	mov	r2, #0
	mov	r0, r2
	str	r2, [r3, #2100]
	str	r2, [r3, #2104]
	str	r2, [r3, #2108]
	str	r2, [r3, #2112]
	str	r2, [r3, #2072]
	str	r2, [r3, #1612]
	str	r2, [r3, #2056]
	str	r2, [r3, #2060]
	str	r2, [r3, #2064]
	str	r2, [r3, #2116]
	str	r2, [r3, #2076]
	str	r2, [r3, #2080]
	str	r2, [r3, #2084]
	str	r2, [r3, #2088]
	str	r2, [r3, #2092]
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	ip, .L95
	mov	r5, r2
	mov	r4, r1
	mov	r2, #32
	mov	r1, #0
	ldr	r8, [ip, #48]
	mov	r6, r0
	sub	r0, fp, #68
	mov	r7, r3
	blx	r8
	mov	r2, r5
	mov	r1, r4
	sub	r0, fp, #68
	mov	r4, r5, asl #3
	bl	BsInit
	movw	r5, #438
	mov	r0, #0
	b	.L79
.L83:
	cmp	lr, #256
	beq	.L92
.L87:
	bl	BsSkip
	sub	r0, fp, #68
	bl	BsPos
.L79:
	rsb	r3, r0, r4
	mov	r1, #32
	cmp	r3, #31
	sub	r0, fp, #68
	ble	.L93
	bl	BsShow
	mov	r1, #8
	mov	r3, r0
	cmp	r3, r5
	bic	r2, r0, #1020
	bic	ip, r0, #15
	bic	lr, r0, #255
	bic	r2, r2, #3
	sub	r0, fp, #68
	beq	.L82
	cmp	ip, #288
	beq	.L82
	cmp	r2, #32768
	bne	.L83
	ldrb	r3, [r6, #9]	@ zero_extendqisi2
	mov	r1, #8
	sub	r0, fp, #68
	cmp	r3, #2
	bne	.L94
	ldr	r3, [r6, #744]
	add	r3, r3, #1
	str	r3, [r6, #744]
	cmp	r3, #18
	bls	.L87
	mov	r2, #196
	mov	r3, #1
	str	r2, [r7]
	sub	r0, fp, #68
	strb	r3, [r6, #9]
	bl	BsPos
	b	.L81
.L82:
	mov	r1, #2
	mov	r2, #0
	strb	r1, [r6, #9]
	sub	r0, fp, #68
	str	r2, [r6, #744]
	str	r3, [r7]
	bl	BsPos
.L81:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L93:
	mov	r3, #197
	str	r3, [r7]
	bl	BsPos
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L92:
	str	r3, [r7]
	sub	r0, fp, #68
	bl	BsPos
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L94:
	mov	r2, #1
	mov	r3, #196
	strb	r2, [r6, #9]
	str	r3, [r7]
	bl	BsPos
	b	.L81
.L96:
	.align	2
.L95:
	.word	vfmw_Osal_Func_Ptr_S
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
	ble	.L109
	add	lr, r0, r1
	add	r3, r0, #2
.L114:
	cmp	lr, r3
	bls	.L99
.L115:
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bls	.L100
	and	ip, r2, #252
	cmp	ip, #128
	beq	.L100
.L107:
	add	r3, r3, #3
	cmp	lr, r3
	bhi	.L115
.L99:
	sub	r0, r1, #2
	ldmfd	sp, {fp, sp, pc}
.L100:
	cmp	r2, #0
	bne	.L102
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #1
	beq	.L114
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #2
	addne	r3, r3, #4
	b	.L114
.L102:
	cmp	r2, #1
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	beq	.L116
	cmp	r2, #0
	bne	.L107
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L107
	rsb	r0, r0, r3
	sub	r0, r0, #2
	ldmfd	sp, {fp, sp, pc}
.L116:
	cmp	r2, #0
	bne	.L107
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L107
	rsb	r3, r0, r3
	sub	r0, r3, #2
	ldmfd	sp, {fp, sp, pc}
.L109:
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
	ldr	r5, .L121
	mov	r6, r1
	mov	r7, r2
	mov	r1, #0
	mov	r2, #32
	ldr	r3, [r5, #48]
	mov	r4, r0
	sub	r0, fp, #60
	blx	r3
	mov	r2, r7
	mov	r1, r6
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
	bne	.L118
	add	r4, r4, #20480
	ldr	r3, [r5, #68]
	ldr	r1, .L121+4
	mov	r0, #1
	blx	r3
	strb	r6, [r4, #1558]
	sub	r0, fp, #60
	bl	BsPos
	ldr	r3, .L121+8
	ldr	r7, [r3]
	cmp	r7, #0
	mov	r5, r0
	beq	.L119
	ldr	r0, [r4, #2480]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #103
	blx	r7
	mov	r0, r5
.L119:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L118:
	mov	r1, #6
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	sub	r0, fp, #60
	add	r4, r4, #20480
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #790]
	sub	r0, fp, #60
	bl	BsGet
	mov	r3, #1
	strb	r3, [r4, #1558]
	strb	r0, [r4, #791]
	sub	r0, fp, #60
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L122:
	.align	2
.L121:
	.word	vfmw_Osal_Func_Ptr_S
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
	ble	.L124
	cmp	r2, #4
	ble	.L125
	ldrb	ip, [r1, #4]!	@ zero_extendqisi2
	mov	r5, r0
	movw	r7, #1030
	mov	r0, #4
	mvn	r3, ip, asl #24
	strb	ip, [r5, #3]!
	mvn	r3, r3, lsr #24
	mov	lr, r5
	mov	r3, r3, asl #8
	b	.L126
.L131:
	ldrb	ip, [r1, #1]!	@ zero_extendqisi2
	orr	r3, r3, ip
	mov	r3, r3, asl #8
	cmp	r3, #256
	beq	.L185
	cmp	r0, r7
	strb	ip, [lr, #1]!
	beq	.L186
.L126:
	sub	r6, r0, #3
	add	r0, r0, #1
	cmp	r0, r2
	bne	.L131
.L182:
	add	r8, r4, #20480
	cmp	r6, #2
	mov	r3, #1
	mov	r10, r6
	mov	r7, r2, asl #3
	strb	r3, [r8, #1562]
	bhi	.L187
.L163:
	mov	r0, r7
.L181:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L124:
	add	r4, r0, #20480
	add	r7, r2, #1
	strb	r3, [r4, #1562]
	mov	r0, r7, asl #3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L185:
	sub	r0, r0, #2
	cmp	r2, r0
	bge	.L188
.L130:
	add	r7, r2, #1
	mov	r0, r7, asl #3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L187:
	add	r1, r4, #22528
	ldr	r2, [r8, #2092]
	add	r1, r1, #52
	ldr	r0, [r8, #2480]
	bl	Mp4_GetUserDataBuf
	ldr	r9, .L192
	cmp	r0, #0
	str	r0, [r8, #2116]
	beq	.L134
	cmn	r6, #-2147483648
	ldr	r3, [r9, #52]
	sub	r6, r6, #2
	str	r6, [r0, #1048]
	movpl	r2, #0
	ldr	r0, [r8, #2116]
	bmi	.L189
.L135:
	mov	r1, r5
	blx	r3
	ldr	r1, .L192+4
	ldr	r2, [r8, #1580]
	ldr	r3, [r8, #2116]
	ldr	r10, [r1]
	ldrd	r0, [r2, #48]
	add	r3, r3, #1056
	cmp	r10, #0
	strd	r0, [r3]
	beq	.L134
	mov	r3, #1072
	ldr	r2, [r8, #2116]
	mov	r1, #6
	ldr	r0, [r8, #2480]
	blx	r10
.L134:
	cmn	r6, #-2147483646
	movpl	r6, #0
	bmi	.L190
.L136:
	add	r6, r4, r6
	mov	r2, #0
	sub	r0, fp, #61
	sub	r3, fp, #56
	strb	r2, [r6, #3]
	sub	r2, fp, #60
	str	r0, [sp]
	mov	r0, r5
	ldr	r4, [r9, #76]
	ldr	r1, .L192+8
	blx	r4
	ldr	r2, .L192
	cmp	r0, #1
	ble	.L191
.L137:
	ldr	r3, [fp, #-56]
	cmp	r0, #3
	ldr	r2, [fp, #-60]
	str	r3, [r8, #1540]
	movne	r3, #0
	ldreqsb	r3, [fp, #-61]
	str	r2, [r8, #1536]
	subeq	r3, r3, #112
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	str	r3, [r8, #1544]
.L138:
	ldr	r3, [r9, #76]
	sub	r2, fp, #56
	ldr	r1, .L192+12
	mov	r0, r5
	blx	r3
	ldr	r4, .L192
	cmp	r0, #1
	beq	.L140
	sub	r3, fp, #56
	sub	r6, fp, #48
	str	r3, [sp, #4]
	sub	r2, fp, #60
	ldr	r10, [r4, #76]
	sub	r3, fp, #52
	str	r6, [sp]
	mov	r0, r5
	ldr	r1, .L192+16
	blx	r10
	cmp	r0, #4
	beq	.L140
	str	r6, [sp]
	sub	r3, fp, #52
	ldr	r4, [r4, #76]
	sub	r2, fp, #60
	ldr	r1, .L192+20
	mov	r0, r5
	blx	r4
	add	r0, r0, #1
	cmp	r0, #1
	ble	.L141
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-60]
	ldr	r1, [fp, #-48]
	mov	r2, r2, asl #8
	add	r3, r2, r3, lsl #16
	add	r3, r3, r1
	str	r3, [fp, #-56]
.L141:
	cmp	r0, #4
	beq	.L140
	ldr	r3, [r9, #80]
	mov	r2, #7
	ldr	r1, .L192+24
	mov	r0, r5
	blx	r3
	cmp	r0, #0
	movweq	r3, #4600
	streq	r3, [r8, #1552]
.L152:
	sub	r2, fp, #56
	ldr	r3, [r9, #76]
	ldr	r1, .L192+28
	mov	r0, r5
	blx	r3
	mov	r3, #0
	ldr	r1, [r8, #1536]
	strb	r3, [r8, #801]
	strb	r3, [r8, #802]
	strb	r3, [r8, #799]
	strb	r3, [r8, #798]
	strb	r3, [r8, #800]
	cmp	r0, #1
	ldreq	r2, [fp, #-56]
	ldrne	r2, [r8, #1548]
	streq	r2, [r8, #1548]
	cmp	r2, #0
	beq	.L145
	cmp	r1, r3
	strne	r3, [r8, #1536]
	strne	r3, [r8, #1540]
	cmp	r2, #1
	mvnne	r0, #0
	movne	r1, #0
	beq	.L184
.L155:
	movw	r3, #502
	cmp	r1, r3
	bls	.L147
.L154:
	mov	r3, #1
	strb	r3, [r8, #802]
.L147:
	sub	r2, r2, #1
	cmp	r2, #11
	bhi	.L148
.L156:
	mov	r3, #1
	strb	r3, [r8, #799]
.L148:
	ldr	r3, [r8, #1552]
	movw	r2, #4668
	sub	r3, r3, #1
	cmp	r3, r2
	movls	r3, #1
	strlsb	r3, [r8, #799]
	movw	r3, #498
	cmp	r0, r3
	movls	r3, #1
	strlsb	r3, [r8, #799]
	cmp	r1, #500
	bne	.L163
	ldr	r2, [r8, #1540]
	movw	r3, #413
	mov	r0, r7
	cmp	r2, r3
	moveq	r3, #1
	streqb	r3, [r8, #800]
	b	.L181
.L186:
	add	r4, r4, #20480
	mov	r3, #0
	movw	r0, #8224
	strb	r3, [r4, #1562]
	b	.L181
.L140:
	ldr	r3, [fp, #-56]
	str	r3, [r8, #1552]
	b	.L152
.L189:
	cmp	r10, #1024
	movlt	r2, r10
	movge	r2, #1024
	b	.L135
.L145:
	cmp	r1, #500
	subcs	r0, r1, #1
	movcs	r3, #1
	strcsb	r3, [r8, #801]
	bcs	.L155
	movw	r3, #502
	cmp	r1, r3
	sub	r0, r1, #1
	bhi	.L154
	b	.L148
.L190:
	add	r6, r6, #2
	cmp	r6, #1024
	movge	r6, #1024
	b	.L136
.L125:
	cmp	r2, #3
	ble	.L130
	add	r4, r4, #20480
	mov	r3, #1
	mov	r0, #32
	strb	r3, [r4, #1562]
	b	.L181
.L188:
	mov	r2, r0
	b	.L182
.L191:
	sub	r3, fp, #61
	ldr	r1, .L192+32
	str	r3, [sp]
	mov	r0, r5
	ldr	r4, [r2, #76]
	sub	r3, fp, #56
	sub	r2, fp, #60
	blx	r4
	cmp	r0, #1
	ble	.L138
	b	.L137
.L184:
	strb	r2, [r8, #801]
	mvn	r0, #0
	mov	r1, #0
	b	.L156
.L193:
	.align	2
.L192:
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
	ldr	r3, .L212
	mov	r5, r0
	mov	r6, r1
	add	r4, r5, #20480
	mov	r7, r2
	ldr	r3, [r3, #48]
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #60
	blx	r3
	mov	r2, r7
	mov	r1, r6
	sub	r0, fp, #60
	bl	BsInit
	mov	r6, #1
	mov	r3, #0
	mov	r1, #32
	strb	r3, [r4, #804]
	sub	r0, fp, #60
	strb	r3, [r4, #806]
	add	r5, r5, #16384
	strb	r3, [r4, #807]
	strb	r3, [r4, #808]
	strb	r3, [r4, #809]
	strb	r3, [r4, #810]
	strb	r3, [r4, #811]
	str	r3, [r4, #816]
	str	r3, [r4, #820]
	str	r3, [r4, #824]
	strb	r6, [r4, #805]
	bl	BsSkip
	mov	r1, r6
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3592]
	cmp	r0, #0
	streqb	r6, [r5, #3593]
	bne	.L209
.L196:
	mov	r1, #4
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r5, #3595]
	cmp	r6, #1
	beq	.L210
	mov	r7, #0
	sub	r0, fp, #60
	strb	r7, [r4, #1557]
	bl	BsPos
	ldr	r3, .L212+4
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r5, r0
	beq	.L200
	ldr	r0, [r4, #2480]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
	mov	r0, r5
.L200:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L209:
	mov	r1, #4
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #3
	strb	r0, [r5, #3593]
	sub	r0, fp, #60
	bl	BsGet
	strb	r0, [r5, #3594]
	b	.L196
.L210:
	mov	r1, r6
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3596]
	cmp	r0, #0
	bne	.L211
.L199:
	mov	r3, #1
	sub	r0, fp, #60
	strb	r3, [r4, #1557]
	bl	BsPos
	cmp	r0, r7, asl #3
	bgt	.L201
	ldrb	r3, [r5, #3592]	@ zero_extendqisi2
	strb	r3, [r4, #804]
	ldrb	r3, [r5, #3593]	@ zero_extendqisi2
	strb	r3, [r4, #805]
	ldrb	r3, [r5, #3594]	@ zero_extendqisi2
	strb	r3, [r4, #806]
	ldrb	r3, [r5, #3595]	@ zero_extendqisi2
	strb	r3, [r4, #807]
	ldrb	r3, [r5, #3596]	@ zero_extendqisi2
	strb	r3, [r4, #808]
	ldrb	r3, [r5, #3597]	@ zero_extendqisi2
	strb	r3, [r4, #809]
	ldrb	r3, [r5, #3598]	@ zero_extendqisi2
	strb	r3, [r4, #810]
	ldrb	r3, [r5, #3599]	@ zero_extendqisi2
	strb	r3, [r4, #811]
	ldr	r3, [r5, #3604]
	str	r3, [r4, #816]
	ldr	r3, [r5, #3608]
	str	r3, [r4, #820]
	ldr	r3, [r5, #3612]
	str	r3, [r4, #824]
.L201:
	sub	r0, fp, #60
	bl	BsPos
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L211:
	mov	r1, #3
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, r6
	strb	r0, [r5, #3597]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, r6
	strb	r0, [r5, #3598]
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #3599]
	cmp	r0, #0
	beq	.L199
	mov	r1, #8
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #3604]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #3608]
	sub	r0, fp, #60
	bl	BsGet
	str	r0, [r5, #3612]
	b	.L199
.L213:
	.align	2
.L212:
	.word	vfmw_Osal_Func_Ptr_S
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
	ldr	r8, .L376
	add	r5, r0, #20480
	mov	r6, r0
	mov	r4, r1
	mov	r10, r2
	ldr	r7, [r8, #48]
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #76
	blx	r7
	ldr	r1, [r5, #2480]
	ldr	r2, .L376+4
	add	r7, r6, #19968
	add	r7, r7, #32
	sub	r0, fp, #76
	ldr	r2, [r2, r1, asl #2]
	mov	r1, r4
	add	r4, r6, #16384
	cmp	r2, #0
	ldrne	r3, [r2, #1272]
	moveq	r9, #8192
	ldrne	r9, [r2, #1276]
	mov	r2, r10
	streq	r9, [fp, #-80]
	strne	r3, [fp, #-80]
	bl	BsInit
	ldr	r3, [r8, #48]
	mov	r2, #604
	mov	r1, #0
	mov	r0, r7
	strb	r1, [r5, #789]
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #3620]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3644]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3616]
	cmp	r0, #0
	ldreqb	r3, [r5, #805]	@ zero_extendqisi2
	streqb	r3, [r4, #3617]
	bne	.L365
.L217:
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3619]
	cmp	r0, #15
	beq	.L366
.L218:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3621]
	cmp	r0, #0
	moveq	r3, #1
	streqb	r3, [r4, #3622]
	bne	.L367
.L223:
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3624]
	cmp	r10, #0
	subne	r0, fp, #76
	movne	r7, #0
	beq	.L368
.L359:
	strb	r7, [r5, #1559]
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L294
	ldr	r0, [r5, #2480]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
	mov	r0, r4
.L329:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L368:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L344
	mov	r1, #16
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #3688]
	beq	.L231
	subs	r0, r0, #1
	beq	.L231
	mov	r2, r10
	mov	r3, r0
.L233:
	add	r2, r2, #1
	movs	r3, r3, lsr #1
	uxth	r2, r2
	bne	.L233
	sxth	r2, r2
	cmp	r2, #0
	ble	.L231
.L235:
	add	r3, r3, #1
	movs	r0, r0, lsr #1
	uxth	r3, r3
	bne	.L235
	sxth	r3, r3
.L331:
	str	r3, [r4, #3684]
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L344
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3625]
	cmp	r0, #0
	bne	.L369
.L238:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L344
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3696]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L344
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #3700]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L344
	ldr	r3, [r4, #3696]
	cmp	r3, #31
	bls	.L242
	ldr	r2, [r4, #3700]
	cmp	r2, #31
	bls	.L242
	mul	r3, r3, r2
	ldr	r2, [fp, #-80]
	mul	r9, r9, r2
	cmp	r3, r9
	bls	.L243
.L242:
	mov	r7, #0
	sub	r0, fp, #76
	strb	r7, [r5, #1559]
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L294
.L338:
	ldr	r0, [r5, #2480]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #103
	blx	r6
	mov	r0, r4
	b	.L329
.L344:
	str	r3, [fp, #-80]
	mov	r0, #1
	ldr	r2, [r8, #68]
	ldr	r1, .L376+12
	blx	r2
.L346:
	ldr	r3, [fp, #-80]
	sub	r0, fp, #76
	strb	r3, [r5, #1559]
	bl	BsPos
	ldr	r2, .L376+8
	ldr	r6, [r2]
	cmp	r6, #0
	mov	r4, r0
	beq	.L294
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r5, #2480]
	mov	r2, r3
	blx	r6
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L367:
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3622]
	cmp	r10, #1
	beq	.L220
	mov	r3, #0
	sub	r0, fp, #76
	strb	r3, [r5, #1559]
	bl	BsPos
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L365:
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #3617]
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #3618]
	b	.L217
.L220:
	mov	r1, r10
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	strb	r0, [r4, #3623]
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #3656]
	beq	.L223
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3660]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L361
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3664]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L361
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3668]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L361
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #11
	str	r0, [r4, #3672]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3676]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L361
	mov	r1, #15
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r10
	str	r0, [r4, #3680]
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	str	r3, [fp, #-84]
	bne	.L223
	ldr	r3, [r8, #68]
	mov	r0, r10
	ldr	r1, .L376+12
	blx	r3
	ldr	r7, [fp, #-84]
	sub	r0, fp, #76
	strb	r7, [r5, #1559]
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r4, r0
	bne	.L338
.L294:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L366:
	mov	r1, #8
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #3648]
	sub	r0, fp, #76
	bl	BsGet
	str	r0, [r4, #3652]
	b	.L218
.L231:
	mov	r3, #1
	b	.L331
.L361:
	str	r3, [fp, #-80]
	mov	r0, r10
	ldr	r4, [r8, #68]
	ldr	r1, .L376+12
	blx	r4
	b	.L346
.L369:
	ldr	r1, [r4, #3684]
	sub	r0, fp, #76
	bl	BsGet
	str	r0, [r4, #3692]
	b	.L238
.L243:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3626]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r3, r0
	strb	r3, [r4, #3627]
	cmp	r3, #0
	bne	.L245
	ldr	r2, .L376+8
	strb	r3, [r5, #1559]
	ldr	r9, [r2]
	cmp	r9, #0
	beq	.L245
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r5, #2480]
	blx	r9
.L245:
	ldrb	r3, [r4, #3617]	@ zero_extendqisi2
	sub	r0, fp, #76
	cmp	r3, #1
	moveq	r1, #1
	movne	r1, #2
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3628]
	cmp	r9, #0
	beq	.L248
	ldr	r3, .L376+16
	ldr	r10, [r3]
	ands	r10, r10, #8
	beq	.L370
	sub	r3, r9, #1
	cmp	r3, #1
	bls	.L371
	mov	r7, #0
	sub	r0, fp, #76
	strb	r7, [r5, #1559]
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L255
	ldr	r0, [r5, #2480]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
.L255:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+20
	blx	r3
	mov	r0, r4
	b	.L329
.L372:
	mov	r1, #6
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, r9
	strb	r0, [r4, #3640]
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3641]
	sub	r0, fp, #76
	bl	BsGet
	ldrb	r3, [r4, #3628]	@ zero_extendqisi2
	cmp	r3, #2
	strb	r0, [r4, #3642]
	bne	.L363
.L248:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3629]
	cmp	r0, #0
	beq	.L256
	mov	r7, #0
	sub	r0, fp, #76
	strb	r7, [r5, #1559]
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L257
	ldr	r0, [r5, #2480]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
.L257:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+24
	blx	r3
	mov	r0, r4
	b	.L329
.L371:
	cmp	r9, #2
	beq	.L372
.L363:
	mov	r7, #0
	sub	r0, fp, #76
	strb	r7, [r5, #1559]
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, r7
	mov	r4, r0
	beq	.L254
	ldr	r0, [r5, #2480]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #102
	blx	r6
.L254:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+28
	blx	r3
	mov	r0, r4
	b	.L329
.L256:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3630]
	cmp	r0, #0
	bne	.L373
.L259:
	ldrb	r3, [r4, #3617]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r3, #0
	streqb	r3, [r4, #3633]
	beq	.L266
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #3633]
.L266:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3634]
	cmp	r9, #0
	bne	.L267
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+32
.L355:
	blx	r3
	strb	r9, [r5, #1559]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r4, r0
	beq	.L294
	ldr	r0, [r5, #2480]
	mov	r3, r9
	mov	r2, r9
	mov	r1, #102
	blx	r6
	mov	r0, r4
	b	.L329
.L370:
	strb	r10, [r5, #1559]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r4, r0
	beq	.L250
	ldr	r0, [r5, #2480]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #102
	blx	r6
.L250:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+36
	blx	r3
	mov	r0, r4
	b	.L329
.L373:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3631]
	cmp	r0, #0
	bne	.L374
	ldr	r3, .L376+40
	add	r2, r6, #19968
	add	r2, r2, #116
	add	r0, r3, #256
.L262:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L262
.L261:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3632]
	cmp	r0, #0
	bne	.L274
	ldr	r3, .L376+44
	add	r2, r6, #20224
	add	r2, r2, #116
	add	r0, r3, #256
.L263:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L263
	b	.L259
.L267:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #3635]
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r10, r0
	strb	r10, [r4, #3636]
	cmp	r10, #0
	bne	.L375
	ldrb	r3, [r4, #3617]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L269
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r9, r0
	strb	r9, [r4, #3637]
	cmp	r9, #0
	beq	.L270
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+48
	blx	r3
	strb	r10, [r5, #1559]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L376+8
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r4, r0
	beq	.L294
	ldr	r0, [r5, #2480]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #102
	blx	r6
	mov	r0, r4
	b	.L329
.L374:
	add	r1, r6, #19968
	sub	r0, fp, #76
	add	r1, r1, #120
	bl	Bs_Get_Matrix
	b	.L261
.L269:
	strb	r10, [r4, #3637]
	strb	r10, [r4, #3638]
.L271:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3639]
	cmp	r0, #0
	beq	.L272
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+52
.L357:
	blx	r3
	mov	r7, #0
	sub	r0, fp, #76
	b	.L359
.L375:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+56
	b	.L357
.L272:
	add	r0, r6, #20480
	mov	r3, #1
	ldr	r4, [r8, #52]
	mov	r1, r7
	mov	r2, #604
	strb	r3, [r5, #1559]
	strb	r3, [r5, #789]
	add	r0, r0, #124
	strb	r3, [r5, #1560]
	blx	r4
	sub	r0, fp, #76
	bl	BsPos
	b	.L329
.L270:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3638]
	cmp	r0, #0
	beq	.L271
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L376+60
	b	.L355
.L274:
	add	r1, r6, #20224
	sub	r0, fp, #76
	add	r1, r1, #120
	bl	Bs_Get_Matrix
	b	.L259
.L377:
	.align	2
.L376:
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	g_event_report
	.word	.LC8
	.word	g_VdmCharacter
	.word	.LC11
	.word	.LC12
	.word	.LC10
	.word	.LC13
	.word	.LC9
	.word	.LANCHOR1-4
	.word	.LANCHOR1+252
	.word	.LC15
	.word	.LC17
	.word	.LC14
	.word	.LC16
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r6, .L386
	mov	r4, r0
	mov	r7, r1
	add	r5, r4, #20480
	mov	r8, r2
	ldr	r3, [r6, #48]
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #68
	blx	r3
	mov	r2, r8
	mov	r1, r7
	sub	r0, fp, #68
	bl	BsInit
	mov	r3, #0
	mov	r1, #32
	str	r3, [r5, #812]
	sub	r0, fp, #68
	add	r4, r4, #16384
	bl	BsSkip
	sub	r0, fp, #68
	mov	r1, #8
	bl	BsGet
	sub	r3, r0, #1
	sub	r2, r0, #240
	cmp	r2, #5
	cmphi	r3, #2
	str	r0, [r4, #3600]
	movls	r3, #1
	movhi	r3, #0
	cmp	r0, #8
	orreq	r3, r3, #1
	cmp	r3, #0
	strne	r0, [r5, #812]
	movne	r3, #1
	strneb	r3, [r5, #1556]
	bne	.L380
	cmp	r0, #0
	beq	.L385
	ldr	r2, .L386+4
	strb	r3, [r5, #1556]
	ldr	r4, [r2]
	cmp	r4, #0
	beq	.L380
	ldr	r0, [r5, #2480]
	mov	r2, r3
	mov	r1, #102
	blx	r4
.L380:
	sub	r0, fp, #68
	bl	BsPos
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L385:
	ldr	r3, [r6, #68]
	mov	r2, r0
	ldr	r1, .L386+8
	mov	r0, #1
	blx	r3
	mov	r3, #1
	strb	r3, [r5, #1556]
	ldr	r3, [r4, #3600]
	str	r3, [r5, #812]
	b	.L380
.L387:
	.align	2
.L386:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC18
	UNWIND(.fnend)
	.size	Mp4_Syntax_Vos, .-Mp4_Syntax_Vos
	.align	2
	.global	Frame_Init
	.type	Frame_Init, %function
Frame_Init:
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
	UNWIND(.pad #76)
	sub	sp, sp, #76
	add	r4, r0, #20480
	mov	r6, r2
	mov	r5, r1
	ldr	r3, [r4, #1580]
	ldr	r8, [r3, #776]
	ldr	r2, [r3, #28]
	cmp	r8, #0
	bne	.L389
	cmp	r2, #25
	beq	.L420
.L413:
	mov	r9, #5
	mov	r10, #3
	mov	r2, #2
	str	r2, [fp, #-88]
.L390:
	ldr	r2, [r3, #868]
	cmp	r2, #1
	beq	.L401
	ldr	r2, .L423
	ldr	r8, [r2, #48]
	cmp	r8, #0
	beq	.L403
	ldr	r7, .L423+4
	mov	ip, #0
	ldr	r1, [r3, #24]
	mov	r2, #40
	ldr	r0, [r3, #20]
	str	r7, [sp, #16]
	ldr	r3, [r4, #2480]
	stmib	sp, {r2, ip}
	mov	r2, #2
	str	r2, [sp]
	mov	r2, r5
	str	r3, [sp, #12]
	mov	r3, r6
	blx	r8
	cmp	r0, #0
	bne	.L403
	ldr	r2, [r7, #552]
	ldr	r3, [r7, #292]
	cmp	r2, #1
	ble	.L405
	cmp	r3, #2
	ble	.L405
	ldr	r0, [r7, #8]
	str	r0, [r4, #1600]
	bl	MEM_Phy2Vir
	str	r0, [r4, #1588]
.L401:
	ldr	r7, .L423+8
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #76
	ldr	r3, [r7, #48]
	blx	r3
	ldr	r2, [r4, #1580]
	str	r6, [fp, #-48]
	mov	r3, #0
	str	r5, [fp, #-68]
	ldr	r2, [r2, #28]
	str	r6, [fp, #-64]
	cmp	r2, #24
	str	r5, [fp, #-52]
	strb	r3, [fp, #-75]
	beq	.L407
	ldrb	r3, [fp, #-88]	@ zero_extendqisi2
	strb	r10, [fp, #-72]
	strb	r9, [fp, #-70]
.L410:
	sub	r1, fp, #76
	ldr	r0, [r4, #2480]
	strb	r3, [fp, #-69]
	mov	r5, #0
	strb	r5, [fp, #-73]
	bl	FSP_ConfigInstance
	subs	r8, r0, #0
	bne	.L408
	ldr	r1, [r4, #1580]
	sub	r3, fp, #80
	ldr	r0, [r4, #2480]
	ldr	r2, [r1, #24]
	ldr	r1, [r1, #20]
	bl	FSP_PartitionFsMemory
	cmp	r0, r5
	moveq	r3, #1
	streq	r3, [r4, #2484]
	bne	.L421
.L416:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L389:
	cmp	r2, #25
	bne	.L413
	ldr	r1, [r3, #736]
	ldr	r2, [r3, #740]
	cmp	r5, r1
	bhi	.L397
	cmp	r6, r2
	bhi	.L397
	ldr	r1, [r3, #764]
	ldr	r2, [r3, #760]
	cmp	r1, #0
	add	r10, r2, #2
	moveq	r2, #1
	streq	r2, [fp, #-88]
	bne	.L422
	ldr	r9, [r3, #784]
	b	.L390
.L407:
	mov	r3, #1
	strb	r9, [fp, #-70]
	strb	r3, [fp, #-72]
	b	.L410
.L420:
	ldr	r0, [r3, #736]
	cmp	r0, r1
	ldrcc	r1, [r3, #740]
	bcc	.L392
	ldr	r2, [r3, #740]
	cmp	r2, r6
	mov	r1, r2
	bcc	.L392
	ldr	r1, [r4, #2484]
	cmp	r1, #1
	beq	.L416
	ldr	ip, [r3, #764]
	ldr	r1, [r3, #760]
	cmp	ip, #0
	add	r10, r1, #2
	moveq	r1, #1
	streq	r1, [fp, #-88]
	beq	.L395
	add	r1, r1, #1
	cmp	r1, #17
	movge	r1, #17
	str	r1, [fp, #-88]
.L395:
	mov	r6, r2
	mov	r5, r0
	ldr	r9, [r3, #784]
	b	.L390
.L422:
	add	r2, r2, #1
	ldr	r9, [r3, #784]
	cmp	r2, #17
	movge	r2, #17
	str	r2, [fp, #-88]
	b	.L390
.L405:
	ldr	ip, .L423+8
	mov	r0, #0
	ldr	r1, .L423+12
	mvn	r8, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L416
.L403:
	ldr	r3, .L423+8
	mov	r0, #0
	ldr	r1, .L423+16
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L416
.L408:
	ldr	r3, [r7, #68]
	mov	r0, r5
	ldr	r1, .L423+20
	mvn	r8, #0
	blx	r3
	b	.L416
.L397:
	ldr	ip, .L423+8
	mov	r3, r6
	str	r2, [sp, #4]
	mov	r2, r5
	str	r1, [sp]
.L419:
	ldr	r4, [ip, #68]
	mov	r0, #0
	ldr	r1, .L423+24
	mvn	r8, #0
	blx	r4
	b	.L416
.L421:
	mov	r0, r8
	ldr	r3, [r7, #68]
	ldr	r1, .L423+28
	blx	r3
	str	r8, [r4, #2484]
	mvn	r8, #0
	b	.L416
.L392:
	ldr	ip, .L423+8
	mov	r3, r6
	str	r1, [sp, #4]
	mov	r2, r5
	str	r0, [sp]
	b	.L419
.L424:
	.align	2
.L423:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC21
	.word	.LC20
	.word	.LC23
	.word	.LC19
	.word	.LC22
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
	add	r8, r0, #20480
	mov	r4, r1
	ldrb	r3, [r8, #831]	@ zero_extendqisi2
	cmp	r3, #15
	beq	.L444
	sub	r2, r3, #2
	cmp	r2, #1
	movls	r9, #1
	bls	.L428
	sub	r2, r3, #4
	cmp	r2, #1
	movls	r9, #2
	bls	.L428
	cmp	r3, #1
	moveq	r9, #5
	movne	r9, #0
.L428:
	mov	r1, r4
	ldr	r0, [r8, #2480]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L426
	ldr	r3, [r8, #1496]
	mov	r1, r9
	str	r3, [r4, #164]
	ldr	r3, [r8, #1492]
	str	r3, [r4, #168]
	bl	SetAspectRatio
	ldr	r3, [r8, #1580]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L445
.L434:
	ldr	r3, [r8, #1496]
	mov	r5, #0
	mvn	r6, #0
	mvn	r7, #0
	ldr	ip, .L446
	mov	r0, #29
	str	r3, [r4, #172]
	ldr	r3, [r8, #1492]
	str	r3, [r4, #176]
	ldr	r3, [r8, #1496]
	mov	r3, r3, lsr #1
	str	r3, [r4, #180]
	ldr	r3, [r8, #1492]
	mov	r3, r3, lsr #1
	str	r3, [r4, #184]
	ldr	r3, [r8, #2060]
	str	r3, [r4, #208]
	ldr	r3, [r8, #2056]
	str	r3, [r4, #204]
	ldrb	r1, [r8, #1437]	@ zero_extendqisi2
	ldrb	r2, [r8, #1432]	@ zero_extendqisi2
	ldrb	r3, [r8, #809]	@ zero_extendqisi2
	and	r2, r2, #3
	orr	r2, r2, r1, asl #12
	ldrb	r1, [r8, #838]	@ zero_extendqisi2
	mov	r3, r3, asl #5
	orr	r2, r2, #3072
	and	r1, r1, #1
	uxtb	r3, r3
	orr	r3, r2, r3
	orr	r1, r3, r1, asl #8
	orr	r1, r1, r9, asl #14
	str	r1, [r4, #160]
	ldrb	r3, [r8, #1432]	@ zero_extendqisi2
	ldr	r1, .L446+4
	and	r3, r3, #3
	str	r3, [r4, #152]
	ldrb	r3, [r8, #1432]	@ zero_extendqisi2
	str	r5, [r4, #148]
	and	r3, r3, #3
	str	r3, [r4, #156]
	ldr	r3, [r8, #2100]
	str	r3, [r4, #212]
	ldr	r3, [r8, #2104]
	str	r3, [r4, #216]
	ldr	r3, [r8, #2108]
	str	r3, [r4, #220]
	ldr	r3, [r8, #2112]
	str	r3, [r4, #224]
	ldr	r3, [r8, #1580]
	ldrd	r2, [r3, #48]
	strd	r2, [r4, #8]
	ldr	r3, [r8, #1580]
	ldrd	r2, [r3, #64]
	strd	r2, [r4, #16]
	ldr	r3, [r8, #1580]
	ldrd	r2, [r3, #80]
	strd	r2, [r4, #24]
	ldr	r3, [r8, #1580]
	ldr	r3, [r3, #96]
	str	r3, [r4, #68]
	ldr	r3, [r8, #1580]
	ldr	r3, [r3, #100]
	str	r3, [r4, #72]
	ldr	r3, [r8, #1580]
	ldr	r3, [r3, #104]
	str	r3, [r4, #76]
	ldr	r3, [r8, #1580]
	ldr	r3, [r3, #120]
	str	r3, [r4, #80]
	ldr	r3, [r8, #1580]
	strd	r6, [r3, #48]
	ldrd	r6, [r4, #16]
	ldrd	r2, [r4, #8]
	ldr	r8, [ip, #68]
	strd	r6, [sp]
	blx	r8
	mov	r3, #8
	mov	r2, #2
	strb	r5, [r4, #372]
	str	r2, [r4, #384]
	mov	r2, #1
	strb	r5, [r4, #379]
	str	r3, [r4, #388]
	str	r3, [r4, #396]
	str	r3, [r4, #392]
	strb	r2, [r4, #377]
.L426:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L445:
	ldr	r3, [r4, #168]
	ldr	r1, [r4, #192]
	add	r3, r3, #15
	ldr	r0, [r4, #104]
	ldr	ip, [r4, #32]
	mov	r2, r3, lsr #4
	mov	r3, r1, asl #4
	str	r0, [r4, #88]
	mul	r3, r2, r3
	str	r0, [r4, #120]
	add	r2, r0, r1
	str	ip, [r4, #48]
	str	r2, [r4, #96]
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
	b	.L434
.L444:
	ldr	r2, [r8, #860]
	ldr	r1, [r8, #864]
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r9, #0
	beq	.L428
	ldr	r3, [r8, #912]
	mul	r1, r3, r1
	cmp	r1, #0
	beq	.L436
	ldr	r0, [r8, #908]
	mov	r2, r2, asl #10
	mul	r0, r0, r2
	bl	__aeabi_uidiv
	movw	r3, #1364
	cmp	r0, r3
	movw	r3, #1819
	rsble	r1, r0, #1360
	subgt	r1, r0, #1360
	addle	r1, r1, #5
	subgt	r1, r1, #5
	cmp	r0, r3
	rsble	r0, r0, #1808
	subgt	r0, r0, #1808
	addle	r0, r0, #12
	subgt	r0, r0, #12
	cmp	r1, r0
	movlt	r9, #1
	movge	r9, #2
	b	.L428
.L436:
	mov	r9, r1
	b	.L428
.L447:
	.align	2
.L446:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
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
	add	r6, r5, #53248
	ldrb	r3, [r4, #1432]	@ zero_extendqisi2
	cmp	r3, #4
	strb	r3, [r0, #2]
	ldreq	r2, .L458
	moveq	r3, #300
	ldr	r0, [r4, #2480]
	mlaeq	r3, r3, r0, r2
	ldreq	r2, [r3, #12]
	addeq	r2, r2, #1
	streq	r2, [r3, #12]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r6, #3552]
	blt	.L451
	ldr	r3, [r4, #2484]
	cmp	r3, #0
	beq	.L451
	mov	r1, r0
	mov	r0, r5
	bl	Mp4_RecordFrameAtr
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2064]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L451:
	ldr	r3, .L458+4
	mov	r0, #0
	ldr	r1, .L458+8
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r6, #3544]
	ldr	r0, [r4, #2480]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L453
	ldr	r1, [r7, #212]
	mov	r8, #0
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r7, #216]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r7, #220]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r7, #224]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	str	r8, [r7, #212]
	str	r8, [r7, #216]
	mov	r2, #1
	str	r8, [r7, #220]
	str	r8, [r7, #224]
	ldr	r1, [r6, #3544]
	ldr	r0, [r4, #2480]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r6, #3536]
	ldr	r0, [r4, #2480]
	bl	FSP_ClearLogicFs
	str	r8, [r6, #3536]
	str	r8, [r6, #3544]
	ldr	r0, [r4, #2480]
	bl	FSP_GetNullLogicFs
	str	r0, [r6, #3544]
	str	r0, [r6, #3536]
.L453:
	add	r1, r5, #22528
	mov	r3, #0
	add	r1, r1, #80
	str	r3, [r4, #2488]
	ldr	r0, [r4, #2480]
	bl	FSP_ClearNotInVoQueue
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L459:
	.align	2
.L458:
	.word	g_VfmwChanStat
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC25
	UNWIND(.fnend)
	.size	Mp4_Frame_Atr, .-Mp4_Frame_Atr
	.align	2
	.global	Mp4_Set_DecPar
	.type	Mp4_Set_DecPar, %function
Mp4_Set_DecPar:
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
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r9, .L488
	mov	r6, r2
	mov	r4, r0
	mov	r2, #48
	sub	r0, fp, #92
	ldr	r3, [r9, #48]
	mov	r1, #0
	blx	r3
	ldrb	r3, [r6, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L485
	ldr	r3, [r6, #88]
	add	r5, r4, #20480
	mov	r1, #0
	bic	r3, r3, #3
	str	r3, [r4, #1208]
	ldr	r3, [r5, #1568]
	and	r2, r3, #3
	str	r3, [r4, #1220]
	ldr	r3, [r5, #1564]
	str	r3, [r4, #1056]
	ldr	r3, [r5, #1576]
	add	r2, r3, r2, lsl #3
	str	r2, [r4, #1228]
	ldr	r2, [r5, #1572]
	rsb	r3, r3, r2, lsl #3
	str	r3, [r4, #1236]
	ldr	r3, [r6, #88]
	str	r3, [r4, #1224]
	ldr	r3, [r6, #80]
	str	r3, [r4, #1060]
	ldr	r3, [r6, #88]
	and	r3, r3, #3
	mov	r3, r3, asl #3
	str	r3, [r4, #1232]
	ldr	r3, [r6, #92]
	str	r1, [r4, #1216]
	mov	r3, r3, asl #3
	str	r3, [r4, #1240]
.L462:
	ldr	r2, [r5, #1496]
	add	r8, r4, #1040
	add	r6, r4, #12288
	add	r3, r2, #15
	mov	r3, r3, lsr #4
	strh	r3, [r8, #164]	@ movhi
	ldr	r1, [r5, #1492]
	add	r3, r1, #15
	mov	r3, r3, lsr #4
	strh	r3, [r8, #166]	@ movhi
	ldrb	r3, [r5, #1432]	@ zero_extendqisi2
	strb	r3, [r4, #1040]
	ldrb	r0, [r5, #842]	@ zero_extendqisi2
	strb	r0, [r4, #1041]
	ldrb	r0, [r5, #797]	@ zero_extendqisi2
	strb	r0, [r4, #1042]
	ldrb	r0, [r5, #1439]	@ zero_extendqisi2
	strb	r0, [r4, #1043]
	ldrb	r0, [r5, #1444]	@ zero_extendqisi2
	strb	r0, [r4, #1044]
	ldrb	r0, [r5, #1443]	@ zero_extendqisi2
	strb	r0, [r4, #1045]
	ldr	r0, [r5, #896]
	strb	r0, [r4, #1046]
	ldrb	r0, [r5, #1440]	@ zero_extendqisi2
	strb	r0, [r4, #1047]
	ldrb	r0, [r5, #1441]	@ zero_extendqisi2
	strb	r0, [r4, #1048]
	ldrb	r0, [r5, #1436]	@ zero_extendqisi2
	strb	r0, [r4, #1049]
	ldrb	r0, [r5, #847]	@ zero_extendqisi2
	strb	r0, [r4, #1050]
	ldrb	r0, [r5, #845]	@ zero_extendqisi2
	strb	r0, [r4, #1051]
	ldrb	r0, [r5, #1434]	@ zero_extendqisi2
	strb	r0, [r4, #1052]
	ldrb	r0, [r5, #1438]	@ zero_extendqisi2
	strb	r0, [r4, #1053]
	ldrb	r0, [r5, #1437]	@ zero_extendqisi2
	strb	r0, [r4, #1054]
	ldrb	r0, [r5, #838]	@ zero_extendqisi2
	strb	r0, [r4, #1055]
	ldr	r0, [r5, #1528]
	str	r0, [r4, #1244]
	ldr	r0, [r5, #1524]
	str	r0, [r4, #1248]
	ldrb	r0, [r5, #800]	@ zero_extendqisi2
	strb	r0, [r4, #1194]
	ldrb	r0, [r5, #799]	@ zero_extendqisi2
	strb	r0, [r4, #1193]
	ldrb	r0, [r5, #798]	@ zero_extendqisi2
	strb	r0, [r4, #1192]
	ldrb	r0, [r5, #801]	@ zero_extendqisi2
	strb	r0, [r4, #1195]
	ldrb	r0, [r5, #802]	@ zero_extendqisi2
	strb	r0, [r4, #1196]
	ldrb	r0, [r5, #803]	@ zero_extendqisi2
	strb	r0, [r4, #1197]
	str	r1, [r6, #3360]
	str	r2, [r6, #3364]
	ldrb	r2, [r5, #840]	@ zero_extendqisi2
	cmp	r2, #2
	cmpeq	r3, #3
	str	r2, [r6, #3368]
	moveq	r3, #1
	movne	r3, #0
	beq	.L486
	ldrb	r2, [r5, #853]	@ zero_extendqisi2
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
.L464:
	add	r10, r4, #53248
	ldr	r0, [r5, #2480]
	ldr	r1, [r10, #3552]
	bl	FSP_GetLogicFs
	ldr	r1, [r10, #3536]
	mov	r7, r0
	ldr	r0, [r5, #2480]
	bl	FSP_GetLogicFs
	ldr	r1, [r10, #3544]
	str	r0, [fp, #-96]
	ldr	r0, [r5, #2480]
	bl	FSP_GetLogicFs
	ldr	r2, [fp, #-96]
	cmp	r7, #0
	cmpne	r2, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L487
	ldr	r1, [r7, #520]
	ldr	ip, [r7, #528]
	cmp	r1, #0
	ldr	lr, [r7, #524]
	beq	.L468
	cmp	ip, #0
	beq	.L468
	cmp	lr, #0
	beq	.L468
	ldr	r3, [r7, #532]
	add	ip, r4, #21248
	add	r1, r4, #21504
	add	ip, ip, #144
	add	r1, r1, #144
	str	r3, [r4, #1268]
	ldr	r3, [r0, #532]
	str	r3, [r4, #1272]
	ldr	r3, [r0, #520]
	cmp	r3, #0
	ldreq	r3, [r7, #520]
	ldr	r3, [r3, #12]
	str	r3, [r4, #1264]
	ldr	r3, [r2, #520]
	cmp	r3, #0
	ldreq	r3, [r7, #520]
	ldr	r3, [r3, #12]
	str	r3, [r4, #1260]
	ldr	r3, [r7, #520]
	ldr	r3, [r3, #12]
	str	r3, [r4, #1252]
	ldr	r3, [r0, #528]
	add	r0, r4, #1056
	add	r0, r0, #7
	cmp	r3, #0
	ldreq	r3, [r7, #528]
	ldr	r3, [r3, #12]
	str	r3, [r6, #3332]
	ldr	r3, [r2, #528]
	add	r2, r4, #1120
	add	r2, r2, #7
	cmp	r3, #0
	ldreq	r3, [r7, #528]
	ldr	r3, [r3, #12]
	str	r3, [r6, #3336]
	ldr	r3, [r7, #528]
	ldr	lr, [r3, #12]
	mov	r3, #0
	str	lr, [r6, #3340]
	ldr	lr, [r7, #524]
	ldr	lr, [lr, #12]
	str	lr, [r6, #3344]
	ldr	lr, [r7, #524]
	ldr	lr, [lr, #20]
	str	lr, [r6, #3356]
.L479:
	ldr	lr, [ip, #4]!
	add	r3, r3, #1
	cmp	r3, #64
	strb	lr, [r0, #1]!
	ldr	lr, [r1, #4]!
	strb	lr, [r2, #1]!
	bne	.L479
	ldrh	r1, [r8, #164]
	ldrh	r3, [r8, #166]
	ldr	r2, [r5, #1580]
	mul	r3, r3, r1
	str	r3, [r5, #1464]
	ldr	r3, [r2, #676]
	str	r3, [r6, #3412]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L487:
	ldr	r4, [r9, #68]
	movw	r3, #3457
	ldr	r2, .L488+4
	mov	r0, #0
	ldr	r1, .L488+8
	blx	r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L485:
	add	r5, r4, #20480
	mov	r0, #0
	ldr	r2, [r5, #1568]
	bic	r1, r2, #3
	str	r1, [r4, #1220]
	str	r2, [r4, #1208]
	and	r2, r2, #3
	ldr	r1, [r5, #1564]
	str	r1, [r4, #1056]
	ldr	r1, [r5, #1576]
	add	r2, r1, r2, lsl #3
	str	r2, [r4, #1228]
	ldr	r2, [r5, #1572]
	str	r3, [r4, #1216]
	str	r0, [r4, #1224]
	rsb	r1, r1, r2, lsl #3
	str	r0, [r4, #1232]
	str	r1, [r4, #1236]
	str	r0, [r4, #1240]
	b	.L462
.L468:
	ldr	r5, [r10, #3544]
	mov	r0, #0
	ldr	r3, [r10, #3552]
	ldr	r2, [r10, #3536]
	ldr	r4, [r9, #68]
	stmib	sp, {r1, ip, lr}
	str	r5, [sp]
	ldr	r1, .L488+12
	blx	r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L486:
	add	r0, r4, #21248
	sub	r1, fp, #92
	add	r0, r0, #20
	bl	MP4_GetGMCparam
	ldrb	r2, [r5, #853]	@ zero_extendqisi2
	ldr	r3, [fp, #-92]
	ldr	r0, [fp, #-76]
	ldr	r1, [fp, #-72]
	str	r2, [r6, #3376]
	str	r3, [r6, #3372]
	ldr	r2, [fp, #-68]
	ldr	r3, [fp, #-64]
	str	r0, [r6, #3380]
	str	r1, [r6, #3384]
	ldr	r0, [fp, #-60]
	ldr	r1, [fp, #-56]
	str	r2, [r6, #3388]
	str	r3, [r6, #3392]
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	str	r0, [r6, #3396]
	str	r1, [r6, #3400]
	str	r2, [r6, #3404]
	str	r3, [r6, #3408]
	b	.L464
.L489:
	.align	2
.L488:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+1280
	.word	.LC26
	.word	.LC27
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
	ldr	r3, [r0, #1612]
	cmp	r3, #2
	ldr	r3, [r0, #1580]
	beq	.L502
.L492:
	ldr	r3, [r3, #8]
	cmp	r3, #2
	beq	.L495
	cmp	r3, #1
	beq	.L501
	cmp	r3, #4
	movne	r3, #0
.L501:
	str	r3, [r0, #1612]
	ldmfd	sp, {fp, sp, pc}
.L502:
	ldr	r2, [r3, #8]
	cmp	r2, #2
	movne	r2, #1
	strne	r2, [r0, #2120]
	bne	.L492
.L495:
	mov	r3, #2
	str	r3, [r0, #1612]
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
	beq	.L506
	mov	r0, #0
.L505:
	mov	r3, r3, lsr #1
	add	r0, r0, #1
	tst	r3, #1
	bne	.L505
	cmp	r0, #0
	addne	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
.L506:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetTrailingOneLen, .-GetTrailingOneLen
	.align	2
	.global	MPEG4DEC_Init
	.type	MPEG4DEC_Init, %function
MPEG4DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 776
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #780)
	sub	sp, sp, #780
	ldr	r7, .L520
	mov	r4, r0
	mov	r6, r1
	mov	r0, #2
	ldr	r1, .L520+4
	ldr	r3, [r7, #68]
	blx	r3
	cmp	r6, #0
	cmpne	r4, #0
	beq	.L516
	ldr	r3, [r6, #688]
	cmp	r3, #1
	beq	.L517
.L514:
	add	r5, r4, #20480
	ldr	r3, [r7, #48]
	movw	r2, #56824
	mov	r1, #0
	ldr	r8, [r5, #2472]
	mov	r0, r4
	blx	r3
	add	r0, r4, #22528
	add	r0, r0, #80
	mov	r7, #0
	str	r8, [r5, #2472]
	bl	ResetVoQueue
	str	r6, [r5, #1580]
	mov	r0, r4
	str	r7, [r6, #908]
	bl	VCTRL_GetChanIDByCtx
	ldr	r8, .L520
	cmn	r0, #1
	str	r0, [r5, #2480]
	beq	.L518
	mov	r0, r4
	bl	Global_Data_Init
	subs	r7, r0, #0
	bne	.L516
	str	r7, [r5, #2096]
	mov	r2, #1
	ldr	r3, [r8, #68]
	mov	r0, #2
	str	r2, [r5, #2068]
	ldr	r1, .L520+8
	blx	r3
	ldr	r5, [r6, #688]
	cmp	r5, #1
	beq	.L519
.L513:
	mov	r0, r7
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L519:
	add	r0, r4, #21248
	ldr	r3, [r8, #52]
	sub	r1, fp, #804
	mov	r2, #768
	add	r0, r0, #20
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r8, #52]
	sub	r1, fp, #788
	mov	r2, #24
	add	r0, r0, #8
	blx	r3
	add	r0, r4, #19968
	ldr	r3, [r8, #52]
	sub	r1, fp, #764
	mov	r2, #604
	add	r0, r0, #32
	blx	r3
	add	r0, r4, #22016
	ldr	r3, [r8, #52]
	mov	r2, #7
	sub	r1, fp, #812
	add	r0, r0, #20
	blx	r3
	add	r4, r4, #53248
	mov	r0, r7
	strb	r5, [r4, #3561]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L517:
	add	r1, r4, #21248
	ldr	r3, [r7, #52]
	add	r1, r1, #20
	mov	r2, #768
	sub	r0, fp, #804
	blx	r3
	add	r1, r4, #19968
	ldr	r3, [r7, #52]
	add	r1, r1, #8
	mov	r2, #24
	sub	r0, fp, #788
	blx	r3
	add	r1, r4, #19968
	ldr	r3, [r7, #52]
	add	r1, r1, #32
	mov	r2, #604
	sub	r0, fp, #764
	blx	r3
	add	r1, r4, #22016
	add	r1, r1, #20
	ldr	r3, [r7, #52]
	mov	r2, #7
	sub	r0, fp, #812
	blx	r3
	b	.L514
.L516:
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L518:
	ldr	r3, [r8, #68]
	mov	r0, r7
	ldr	r1, .L520+12
	mvn	r7, #19
	blx	r3
	b	.L513
.L521:
	.align	2
.L520:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	.word	.LC30
	.word	.LC29
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
	subs	r4, r0, #0
	ldr	r3, .L526
	mov	r0, #2
	beq	.L523
	add	r4, r4, #20480
	ldr	r3, [r3, #68]
	ldr	r1, .L526+4
	blx	r3
	mov	r3, #0
	str	r3, [r4, #2068]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L523:
	ldr	r1, .L526+8
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L527:
	.align	2
.L526:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC32
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	mov	r5, r1
	beq	.L532
	add	r4, r0, #20480
	mov	r2, #0
	ldr	r0, [r4, #2480]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #2480]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L531
	ldr	r1, [r5, #212]
	mov	r6, #0
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	str	r6, [r5, #212]
	ldr	r1, [r5, #216]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	str	r6, [r5, #216]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L531:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L532:
	ldr	r3, .L533
	mov	r0, #1
	ldr	r1, .L533+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L534:
	.align	2
.L533:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
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
	add	r3, r0, #53248
	add	r4, r0, #20480
	ldr	r1, [r3, #3552]
	ldr	r0, [r4, #2480]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #1496]
	cmp	r3, #0
	beq	.L537
	ldr	r2, [r4, #1492]
	cmp	r2, #0
	beq	.L537
	ldr	r1, [r0, #164]
	ldr	r2, [r0, #168]
	cmp	r1, r3
	movcs	r1, r3
	str	r1, [r0, #172]
	ldr	r3, [r4, #1492]
	cmp	r2, r3
	movcs	r2, r3
	str	r2, [r0, #176]
	b	.L538
.L537:
	ldr	r2, [r0, #164]
	ldr	r3, [r0, #168]
	str	r2, [r0, #172]
	str	r3, [r0, #176]
.L538:
	mov	r3, #2
	mov	r2, #0
	str	r3, [r0, #384]
	mov	r1, #1
	mov	r3, #8
	strb	r2, [r0, #372]
	strb	r2, [r0, #379]
	str	r3, [r0, #388]
	str	r3, [r0, #396]
	str	r3, [r0, #392]
	strb	r1, [r0, #377]
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r6, r0, #20480
	mov	r4, r0
	ldr	r3, [r6, #1580]
	ldr	r3, [r3, #12]
	cmp	r3, #1
	beq	.L563
	add	r5, r0, #53248
	ldr	r0, [r6, #2480]
	ldr	r1, [r5, #3544]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L563
	ldr	r1, [r5, #3544]
	ldr	r0, [r6, #2480]
	bl	FSP_GetDisplay
	cmp	r0, #2
	mov	r8, r0
	beq	.L562
.L563:
	add	r5, r4, #22528
	add	r5, r5, #80
.L553:
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	GetVoLastImageID
.L562:
	mov	r0, r4
	add	r5, r4, #22528
	bl	MP4_SetImgFormat
	add	r5, r5, #80
	mov	r3, #1
	ldr	r1, [r7, #196]
	mov	r2, r3
	str	r3, [r7, #244]
	ldr	r0, [r6, #2480]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #2480]
	mov	r1, r8
	str	r7, [sp]
	mov	r3, r5
	mov	r2, r4
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L550
	mov	r0, r4
	ldr	r1, [r7, #196]
	bl	MPEG4DEC_RecycleImage
	ldr	r1, [r7, #212]
	ldr	r0, [r6, #2480]
	mov	r4, #0
	bl	FreeUsdByDec
	str	r4, [r7, #212]
	ldr	r1, [r7, #216]
	ldr	r0, [r6, #2480]
	bl	FreeUsdByDec
	str	r4, [r7, #216]
	b	.L553
.L550:
	ldr	r3, [r7, #200]
	cmp	r3, #100
	bhi	.L553
	ldr	r3, [r7, #164]
	cmp	r3, #31
	bls	.L553
	ldr	r3, [r7, #168]
	cmp	r3, #31
	bls	.L553
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
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
	add	r4, r0, #20480
	mov	r5, r0
	ldr	r0, [r4, #2480]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #2480]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L570
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L570:
	add	r1, r5, #22528
	ldr	r0, [r4, #2480]
	add	r1, r1, #80
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
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
	add	r0, r0, #16384
	ldr	r3, [r0, #3588]
	cmp	r3, #1
	mvnne	r0, #0
	moveq	r0, #3
	ldmfd	sp, {fp, sp, pc}
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
	ldr	r1, [r1, #16]
	mov	r5, r0
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L575
	ldrb	r3, [r4, #85]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L576
.L575:
	ldr	r3, .L577
	mov	r0, r4
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L576:
	mov	r0, r5
	ldr	r1, [r4, #96]
	bl	SM_ReleaseStreamSeg
	b	.L575
.L578:
	.align	2
.L577:
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
	add	r8, r0, #16384
	add	r3, r0, #20480
	ldr	r6, [r8, #3580]
	ldr	r7, [r3, #2480]
	cmp	r6, #0
	addgt	r5, r0, #15808
	movgt	r4, #0
	addgt	r5, r5, #56
	ble	.L582
.L581:
	add	r4, r4, #1
	ldr	r1, [r5, #4]!
	mov	r0, r7
	bl	SM_ReleaseStreamSeg
	cmp	r6, r4
	bne	.L581
.L582:
	mov	r3, #0
	str	r3, [r8, #3580]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
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
	ldr	ip, .L596
	mov	r9, r3
	ldr	r3, [fp, #8]
	mov	r4, r0
	mov	r6, r1
	mov	r10, r2
	ldr	r1, .L596+4
	ldr	r2, [ip, #68]
	mov	r0, #2
	ldr	r8, [fp, #4]
	add	r7, r4, #20480
	str	r3, [fp, #-48]
	ldr	r5, [fp, #12]
	blx	r2
	add	r2, r4, #12288
	ldr	r3, [fp, #-48]
	str	r10, [r4, #1252]
	add	r5, r5, #15
	str	r9, [r2, #3344]
	add	r3, r3, #15
	ldr	lr, [r6, #532]
	movw	r0, #1206
	movw	ip, #1204
	str	r8, [r4, #1260]
	mov	r3, r3, lsr #4
	mov	r5, r5, lsr #4
	str	lr, [r4, #1268]
	add	r1, r4, #1040
	strh	r3, [r4, ip]	@ movhi
	strh	r5, [r4, r0]	@ movhi
	ldr	r3, [r6, #524]
	ldr	r3, [r3, #20]
	str	r3, [r2, #3356]
	ldr	r3, [r7, #1580]
	ldr	r0, [r3, #676]
	str	r0, [r2, #3412]
	str	r1, [r4, #1036]
	ldr	r2, [r3, #900]
	cmp	r2, #1
	beq	.L594
	cmp	r2, #2
	beq	.L595
.L587:
	mov	r3, #1
	strb	r3, [r4, #1198]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L594:
	cmp	r1, #0
	beq	.L587
	add	r1, r4, #53248
	mov	r3, #0
	mov	r2, r3
	str	r3, [r4, #1036]
	ldr	r0, [r7, #2480]
	ldr	r1, [r1, #3552]
	bl	FSP_SetDisplay
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MP4_ClearCurPic
.L595:
	ldr	r3, [r3, #904]
	cmp	r1, #0
	cmpne	r3, #0
	ble	.L587
	add	r1, r4, #53248
	mov	r3, #0
	mov	r2, r3
	str	r3, [r4, #1036]
	ldr	r0, [r7, #2480]
	ldr	r1, [r1, #3552]
	bl	FSP_SetDisplay
	ldr	r2, [r7, #1580]
	mov	r0, r4
	ldr	r3, [r2, #904]
	sub	r3, r3, #1
	str	r3, [r2, #904]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MP4_ClearCurPic
.L597:
	.align	2
.L596:
	.word	vfmw_Osal_Func_Ptr_S
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
	add	r2, r0, #20480
	add	r3, r0, #15808
	add	r4, r0, #56576
	add	r3, r3, #56
	ldr	r2, [r2, #1580]
	add	r4, r4, #240
	ldr	r0, [r2, #868]
	cmp	r0, #1
	beq	.L600
.L599:
	ldr	r6, .L601
	add	r5, r1, #72
	mov	r0, r3
	mov	r2, #4
	mov	r1, r5
	ldr	r3, [r6, #52]
	blx	r3
	ldr	r3, [r6, #52]
	mov	r1, r5
	mov	r0, r4
	mov	r2, #4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L600:
	ldr	r2, [r2, #908]
	cmp	r2, #1
	bne	.L599
	ldr	ip, .L601
	mov	r0, r3
	mov	r1, r4
	mov	r2, #4
	ldr	r3, [ip, #52]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L602:
	.align	2
.L601:
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
	add	r2, r0, #16384
	add	r3, r0, #20480
	ldrb	r1, [r2, #3635]	@ zero_extendqisi2
	ldrb	r2, [r3, #728]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L613
	add	r0, r0, #12288
	ldrb	r1, [r0, #3576]	@ zero_extendqisi2
	tst	r1, #120
	bne	.L613
	movw	r1, #3576
	ldrh	r0, [r0, r1]
	ubfx	r0, r0, #7, #4
	add	r0, r0, #17
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L605
.L607:
	.word	.L614
	.word	.L608
	.word	.L609
	.word	.L608
.L613:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L614:
	mov	r3, #17
.L606:
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L609:
	ldrb	r2, [r3, #736]	@ zero_extendqisi2
	ldrb	r3, [r3, #737]	@ zero_extendqisi2
	cmp	r3, r2
	movcc	r3, r2
	cmp	r3, #1
	addgt	r3, r3, #16
	movle	r3, #18
	b	.L606
.L608:
	ldrb	r3, [r3, #736]	@ zero_extendqisi2
	add	r3, r3, #16
	b	.L606
.L605:
	ldr	r3, .L617
	mov	r0, #1
	ldr	r1, .L617+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L618:
	.align	2
.L617:
	.word	vfmw_Osal_Func_Ptr_S
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
	add	r0, r0, #1280
	ldr	ip, [r2, #3584]
	ldr	r2, [r3, #3328]
	tst	ip, #2
	beq	.L620
	ldrb	lr, [r3, #3421]	@ zero_extendqisi2
	cmp	lr, #1
	beq	.L636
	cmp	lr, #0
	bne	.L628
	ldrb	ip, [r3, #3501]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L628
	mov	ip, r2, asl #5
	sub	r2, ip, r2, asl #2
	sub	r2, r2, #28
	add	r2, r0, r2
	ldr	r0, [r2, #12]
	cmp	r0, #0
	bne	.L635
	ldr	r0, [r2, #20]
	cmp	r0, #0
	bne	.L635
	ldr	ip, [r2, #8]
	add	r1, ip, r1, lsl #3
	str	r1, [r2, #8]
	ldr	r1, [r3, #3504]
	str	r1, [r2, #20]
	ldr	r3, [r3, #3508]
	mov	r3, r3, asl #3
	str	r3, [r2, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L636:
	sub	r4, r2, #1
	movw	ip, #510
	cmp	r4, ip
	bhi	.L637
	mov	ip, r2, asl #5
	sub	r2, ip, r2, asl #2
	sub	r2, r2, #28
	add	r2, r0, r2
	ldr	r0, [r2, #12]
	cmp	r0, #0
	beq	.L624
	ldr	ip, [r2, #20]
	cmp	ip, #0
	beq	.L624
	ldr	r3, [r3, #3424]
	cmp	ip, r3
	bhi	.L638
	add	r1, r0, r1, lsl #3
	mov	r0, #0
	str	r1, [r2, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L624:
	ldr	ip, [r3, #3424]
	ldr	r0, [r2, #16]
	cmp	ip, r0
	movls	r1, r1, asl #3
	strls	r1, [r2, #12]
	ldrls	r3, [r3, #3424]
	movhi	r0, #0
	ldrhi	r3, [r2, #8]
	movls	r0, #0
	addhi	r1, r3, r1, lsl #3
	strls	r3, [r2, #20]
	strhi	r1, [r2, #8]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L628:
	ldr	r3, .L639
	movw	r2, #4816
.L634:
	ldr	r1, .L639+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
.L635:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L620:
	ldr	r3, .L639
	movw	r2, #4822
	b	.L634
.L637:
	ldr	r3, .L639
	mov	r0, lr
	ldr	r1, .L639+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L638:
	ldr	r3, .L639
	mov	r0, lr
	movw	r2, #4792
	ldr	r1, .L639+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L640:
	.align	2
.L639:
	.word	vfmw_Osal_Func_Ptr_S
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
	ldrb	r3, [r2, #3576]	@ zero_extendqisi2
	tst	r3, #1
	bne	.L642
	mov	r3, #2
	strb	r3, [r0, #797]
	ldr	r3, [r1]
	mov	r3, r3, lsr #8
	sub	r3, r3, #128
	cmp	r3, #3
	ldrlsb	r3, [r2, #3576]	@ zero_extendqisi2
	orrls	r3, r3, #2
	strlsb	r3, [r2, #3576]
.L643:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L642:
	mov	r2, #196
	mov	r3, #1
	str	r2, [r1]
	strb	r3, [r0, #797]
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
	ldr	r6, [r3, #2036]
	ldr	r7, [r3, #2480]
	cmp	r6, #64
	movge	r6, #64
	cmp	r6, #0
	addgt	r5, r0, #22016
	movgt	r4, #0
	addgt	r5, r5, #240
	ble	.L647
.L646:
	add	r4, r4, #1
	ldr	r1, [r5, #4]!
	mov	r0, r7
	bl	SM_ReleaseStreamSeg
	cmp	r4, r6
	bne	.L646
.L647:
	ldr	r3, .L649
	add	r0, r8, #22016
	add	r0, r0, #80
	mov	r2, #440
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L650:
	.align	2
.L649:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MP4_Clean_HeadPacket, .-MP4_Clean_HeadPacket
	.align	2
	.global	MPEG4DEC_VDMPostProc
	.type	MPEG4DEC_VDMPostProc, %function
MPEG4DEC_VDMPostProc:
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
	ldr	r7, .L702
	mov	r5, r0
	movw	r2, #14664
	mov	r8, r1
	add	r0, r0, #1040
	ldr	r3, [r7, #48]
	mov	r1, #0
	blx	r3
	add	r4, r5, #20480
	mov	r0, r5
	add	r6, r5, #53248
	bl	MP4_ClearCurPic
	mov	r0, r5
	bl	MP4_Clean_HeadPacket
	str	r8, [r4, #2064]
	ldr	r0, [r4, #2480]
	ldr	r1, [r6, #3552]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r6, #3544]
	mov	r8, r0
	ldr	r0, [r4, #2480]
	bl	FSP_GetFsImagePtr
	cmp	r8, #0
	mov	r9, r0
	beq	.L697
	ldr	r3, [r7, #68]
	mov	r0, #11
	ldr	r2, [r4, #2072]
	ldr	r1, .L702+4
	blx	r3
	ldr	r3, [r7, #68]
	ldrb	r2, [r4, #1432]	@ zero_extendqisi2
	mov	r0, #11
	ldr	r1, .L702+8
	blx	r3
	ldr	r3, [r4, #2064]
	add	r1, r5, #22528
	add	r1, r1, #52
	str	r3, [r8, #200]
	ldr	r0, [r4, #2480]
	bl	Mp4_ClearUsrData
	ldrb	r3, [r4, #1432]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L654
	ldr	r3, [r4, #1580]
	ldr	r2, [r4, #2064]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L698
.L654:
	mov	r3, #0
	mov	r0, r5
	str	r3, [r4, #2120]
	bl	MP4_SetImgFormat
	ldr	r3, [r4, #1580]
	ldr	r3, [r3, #12]
	cmp	r3, #1
	beq	.L657
	ldrb	lr, [r4, #1432]	@ zero_extendqisi2
	cmp	lr, #2
	beq	.L658
	ldr	r3, [r4, #2488]
	cmp	r3, #1
	ble	.L659
	ldr	ip, [r6, #3536]
	ldr	r3, [r6, #3540]
	str	ip, [r6, #3556]
	ldrb	r8, [r5]	@ zero_extendqisi2
	str	r3, [fp, #-56]
.L660:
	cmn	ip, #1
	beq	.L662
	mov	r1, ip
	ldr	r0, [r4, #2480]
	bl	FSP_GetFsImagePtr
	subs	r9, r0, #0
	beq	.L699
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	cmpeq	r8, #4
	beq	.L700
	ldr	r2, [r9, #200]
	cmp	r2, #0
	beq	.L665
	ldr	r3, [r4, #1580]
	ldr	r1, [r3, #4]
	cmp	r2, r1
	bhi	.L666
.L665:
	ldr	r1, [r6, #3556]
	ldr	r0, [r4, #2480]
	bl	FSP_GetLogicFs
	subs	r10, r0, #0
	beq	.L701
	cmp	r8, #2
	beq	.L668
	ldrsb	r3, [r10, #1]
	cmp	r3, #2
	beq	.L668
	ldr	r3, [r7, #68]
	mov	r0, #11
	ldr	r2, [r6, #3556]
	ldr	r1, .L702+12
	blx	r3
.L662:
	ldr	r3, [r4, #2072]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #2072]
.L695:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L657:
	ldr	ip, [r6, #3552]
	str	ip, [r6, #3556]
	ldr	r3, [r4, #1524]
	ldrb	r8, [r4, #1432]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	b	.L660
.L666:
	ldr	r3, .L702+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L671
	str	r2, [fp, #-52]
	mov	r3, #8
	str	r1, [fp, #-48]
	sub	r2, fp, #52
	mov	r1, #104
	ldr	r0, [r4, #2480]
	blx	r5
	ldr	r3, [r4, #1580]
	ldr	r2, [r9, #200]
	ldr	r1, [r3, #4]
.L671:
	mov	r3, r1
	ldr	r7, [r7, #68]
	ldr	r1, .L702+20
	mov	r0, #1
	blx	r7
	ldr	r1, [r9, #212]
	ldr	r0, [r4, #2480]
	mov	r5, #0
	bl	FreeUsdByDec
	str	r5, [r9, #212]
	ldr	r1, [r9, #216]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	str	r5, [r9, #216]
	mov	r2, r5
	ldr	r1, [r6, #3556]
	ldr	r0, [r4, #2480]
	bl	FSP_SetDisplay
	b	.L662
.L659:
	mvn	r3, #0
	str	r3, [r6, #3556]
	b	.L662
.L668:
	mov	r2, #1
	ldr	r1, [r6, #3556]
	ldr	r0, [r4, #2480]
	bl	FSP_SetDisplay
	add	r3, r5, #22528
	ldr	r0, [r4, #2480]
	add	r3, r3, #80
	str	r9, [sp]
	mov	r2, r5
	mov	r1, #2
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L662
	ldr	r1, [r9, #212]
	mov	r5, #0
	ldr	r0, [r4, #2480]
.L696:
	bl	FreeUsdByDec
	str	r5, [r9, #212]
	ldr	r1, [r9, #216]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	str	r5, [r9, #216]
	mov	r2, r5
	ldr	r0, [r4, #2480]
	ldr	r1, [r6, #3556]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L695
.L658:
	ldr	ip, [r6, #3552]
	cmp	r9, #0
	str	ip, [r6, #3556]
	ldr	r3, [r4, #1524]
	str	r3, [fp, #-56]
	beq	.L673
	ldrd	r2, [r9, #8]
	ldrd	r0, [r8, #8]
	cmp	r2, r0
	sbcs	r10, r3, r1
	bge	.L673
	strd	r2, [r8, #8]
	mov	r8, lr
	strd	r0, [r9, #8]
	ldr	ip, [r6, #3556]
	b	.L660
.L673:
	mov	r8, lr
	b	.L660
.L698:
	ldr	r3, [r7, #112]
	blx	r3
	ldr	r3, .L702+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L655
	ldr	ip, [r4, #2064]
	mov	r3, #8
	ldr	r0, [r4, #1580]
	sub	r2, fp, #52
	mov	r1, #104
	str	ip, [fp, #-52]
	ldr	ip, [r0]
	ldr	r0, [r4, #2480]
	str	ip, [fp, #-48]
	blx	r5
.L655:
	mov	r8, #1
	ldr	r0, [r4, #2480]
	str	r8, [r4, #2120]
	ldr	r1, [r6, #3544]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L656
	ldr	r1, [r5, #212]
	mov	r7, #0
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r5, #216]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r5, #220]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r5, #224]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	str	r7, [r5, #212]
	str	r7, [r5, #216]
	mov	r2, r8
	str	r7, [r5, #220]
	str	r7, [r5, #224]
	ldr	r1, [r6, #3544]
	ldr	r0, [r4, #2480]
	bl	FSP_ClearLogicFs
	mov	r2, r8
	ldr	r1, [r6, #3536]
	ldr	r0, [r4, #2480]
	bl	FSP_ClearLogicFs
	str	r7, [r6, #3536]
	str	r7, [r6, #3544]
	ldr	r0, [r4, #2480]
	bl	FSP_GetNullLogicFs
	str	r0, [r6, #3544]
	str	r0, [r6, #3536]
.L656:
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r4, #2488]
	b	.L695
.L700:
	ldr	r1, [r4, #2480]
	mov	r2, #300
	ldr	r3, .L702+24
	mov	r5, #0
	mov	r0, r1
	mla	r3, r2, r1, r3
	ldr	r2, [r3, #16]
	add	r2, r2, #1
	str	r2, [r3, #16]
	ldr	r1, [r9, #212]
	b	.L696
.L697:
	mov	r3, r0
	ldr	r4, [r7, #68]
	mov	r2, r8
	mov	r0, r8
	ldr	r1, .L702+28
	blx	r4
	mvn	r0, #0
	b	.L695
.L699:
	ldr	r3, [r7, #68]
	movw	r2, #4523
	ldr	r1, .L702+32
	blx	r3
	mvn	r0, #0
	b	.L695
.L701:
	ldr	r1, [r9, #212]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	str	r10, [r9, #212]
	ldr	r1, [r9, #216]
	ldr	r0, [r4, #2480]
	bl	FreeUsdByDec
	str	r10, [r9, #216]
	mov	r2, r10
	ldr	r0, [r4, #2480]
	ldr	r1, [r6, #3556]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L695
.L703:
	.align	2
.L702:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC39
	.word	.LC40
	.word	.LC42
	.word	g_event_report
	.word	.LC43
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
	ldr	r2, [r5, #3580]
	cmp	r2, r6
	bhi	.L707
	add	r1, r0, #12288
	add	r4, r0, r2, lsl #2
	add	r4, r4, #12288
	add	r3, r2, #1
	ldr	r0, [r1, #3432]
	str	r0, [r4, #3580]
	str	r3, [r5, #3580]
	ldrb	r3, [r1, #3421]	@ zero_extendqisi2
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r1, #3501]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r1, #3512]
	addeq	r2, r2, #2
	streq	r3, [r4, #3584]
	streq	r2, [r5, #3580]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L707:
	bl	MP4_Clean_HeadPacket
	mov	r0, r4
	bl	MP4_ClearCurPic
	add	r3, r4, #20480
	add	r1, r4, #15680
	ldr	r0, [r3, #2480]
	add	r1, r1, #24
	bl	MP4_ClearCurPacket
	ldr	ip, .L708
	mov	r3, r6
	ldr	r2, [r5, #3580]
	ldr	r1, .L708+4
	mov	r0, #0
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L709:
	.align	2
.L708:
	.word	vfmw_Osal_Func_Ptr_S
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
	ldr	r7, .L751
	add	r8, r0, #12288
	mov	r6, r0
	mov	r5, r1
	mov	r4, r2
	ldr	r3, [r7, #48]
	mov	r2, #32
	sub	r0, fp, #76
	mov	r1, #0
	blx	r3
	ldr	r2, [r8, #3328]
	cmp	r2, #0
	bne	.L746
.L711:
	mov	r1, r5
	mov	r2, r4
	sub	r0, fp, #76
	add	r5, r6, #20480
	bl	BsInit
	add	r0, r6, #20992
	ldr	r3, [r7, #48]
	mov	r2, #60
	mov	r1, #0
	add	r0, r0, #216
	blx	r3
	mov	r1, #22
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #13
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #738]
	sub	r0, r0, #1
	cmp	r0, #3
	ldrls	pc, [pc, r0, asl #2]
	b	.L712
.L714:
	.word	.L713
	.word	.L715
	.word	.L716
	.word	.L717
.L717:
	mov	r3, #18
	strb	r3, [r5, #739]
	mov	r3, #88
	strb	r3, [r5, #740]
	mov	r3, #704
	str	r3, [r5, #1496]
	mov	r3, #576
	str	r3, [r5, #1492]
.L718:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	ldrb	r3, [r5, #795]	@ zero_extendqisi2
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r5, #728]
	beq	.L720
	adds	r0, r0, #0
	ldr	r3, [r5, #2120]
	movne	r0, #1
	cmp	r3, #1
	movne	r0, #0
	cmp	r0, #0
	bne	.L720
	mov	r1, #4
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #76
	mov	r10, r4, asl #3
	bl	BsGet
	mov	r1, #1
	mov	r4, #0
	uxtb	r0, r0
	cmp	r0, #0
	strneb	r0, [r5, #735]
	sub	r0, fp, #76
	moveq	r3, #1
	streqb	r3, [r5, #735]
	bl	BsSkip
.L726:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #1
	beq	.L747
	add	r4, r4, #1
	cmp	r4, #15
	bls	.L727
.L745:
	mov	r6, #0
	sub	r0, fp, #76
	strb	r6, [r5, #1561]
	bl	BsPos
	ldr	r3, .L751+4
	ldr	r4, [r3]
	cmp	r4, r6
	mov	r9, r0
	beq	.L733
	ldr	r0, [r5, #2480]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #103
	blx	r4
	mov	r0, r9
.L744:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L716:
	mov	r3, #18
	strb	r3, [r5, #739]
	mov	r3, #22
	strb	r3, [r5, #740]
	mov	r3, #352
	str	r3, [r5, #1496]
	mov	r3, #288
	str	r3, [r5, #1492]
	b	.L718
.L715:
	mov	r3, #9
	strb	r3, [r5, #739]
	mov	r3, #11
	strb	r3, [r5, #740]
	mov	r3, #176
	str	r3, [r5, #1496]
	mov	r3, #144
	str	r3, [r5, #1492]
	b	.L718
.L713:
	mov	r3, #6
	strb	r3, [r5, #739]
	mov	r3, #8
	strb	r3, [r5, #740]
	mov	r3, #128
	str	r3, [r5, #1496]
	mov	r3, #96
	str	r3, [r5, #1492]
	b	.L718
.L747:
	sub	r0, fp, #76
	add	r4, r4, #1
	bl	BsPos
	mov	r1, #8
	cmp	r0, r10
	sub	r0, fp, #76
	bgt	.L748
	bl	BsSkip
	cmp	r4, #15
	bls	.L726
	b	.L745
.L746:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L751+8
	blx	r3
	mov	r3, #0
	str	r3, [r8, #3328]
	b	.L711
.L727:
	add	r4, r6, #16384
	mov	r2, #1
	strb	r2, [r5, #1561]
	sub	r0, fp, #76
	ldr	r3, [r4, #3584]
	orr	r3, r3, #2
	str	r3, [r4, #3584]
	ldr	r3, [r8, #3328]
	add	r3, r3, r2
	str	r3, [r8, #3328]
	strb	r2, [r5, #736]
	bl	BsPos
	mov	r3, r0, asr #31
	cmp	r0, #0
	add	r1, r0, #7
	rsb	r10, r0, r10
	mov	r3, r3, lsr #29
	str	r10, [r6, #1288]
	add	r2, r0, r3
	movge	r1, r0
	mov	r9, r0
	and	r2, r2, #7
	ldr	r0, [r5, #1576]
	rsb	r3, r3, r2
	add	r3, r3, r0
	strb	r3, [r6, #1286]
	ldr	r3, [r5, #1568]
	add	r3, r3, r1, asr #3
	str	r3, [r6, #1296]
	ldrb	r3, [r8, #3421]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L749
.L728:
	mov	r3, #0
	str	r3, [r6, #1292]
	strb	r3, [r6, #1287]
	str	r3, [r6, #1300]
.L729:
	ldrb	r3, [r5, #728]	@ zero_extendqisi2
	strb	r3, [r6, #1284]
	ldrb	r3, [r5, #737]	@ zero_extendqisi2
	strb	r3, [r6, #1282]
	ldrb	r3, [r5, #736]	@ zero_extendqisi2
	strb	r3, [r6, #1281]
	ldrb	r3, [r5, #735]	@ zero_extendqisi2
	strb	r3, [r6, #1285]
	ldrb	r3, [r5, #732]	@ zero_extendqisi2
	strb	r3, [r6, #1283]
	ldr	r2, [r4, #3580]
	cmp	r2, #0
	bne	.L750
.L730:
	mov	r0, r6
	bl	MP4_Record_SlcSegID
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L720:
	sub	r0, fp, #76
	bl	BsPos
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L712:
	mov	r6, #0
	sub	r0, fp, #76
	strb	r6, [r5, #1561]
	bl	BsPos
	ldr	r3, .L751+4
	ldr	r4, [r3]
	cmp	r4, r6
	mov	r9, r0
	beq	.L733
	ldr	r0, [r5, #2480]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	r4
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L749:
	ldrb	r2, [r8, #3501]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L728
	ldr	r2, [r8, #3508]
	strb	r3, [r6, #1287]
	mov	r3, r2, asl #3
	str	r3, [r6, #1292]
	ldr	r3, [r8, #3504]
	str	r3, [r6, #1300]
	b	.L729
.L750:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L751+12
	blx	r3
	mov	r0, r6
	bl	MP4_ClearCurPic
	b	.L730
.L733:
	mov	r0, r9
	b	.L744
.L748:
	bl	BsPos
	b	.L744
.L752:
	.align	2
.L751:
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
	ldr	r7, .L847
	add	r8, r0, #12288
	mov	r5, r0
	mov	r10, r1
	mov	r6, r2
	ldr	r3, [r7, #48]
	mov	r2, #32
	sub	r0, fp, #76
	mov	r1, #0
	blx	r3
	ldr	r2, [r8, #3328]
	cmp	r2, #0
	bne	.L831
	add	r4, r5, #20480
	ldrb	r3, [r4, #789]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L755
.L832:
	mov	r0, #32
	strb	r3, [r4, #1561]
.L756:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L831:
	add	r4, r5, #20480
	ldr	r3, [r7, #68]
	ldr	r1, .L847+4
	mov	r0, #1
	blx	r3
	mov	r3, #0
	str	r3, [r8, #3328]
	ldrb	r3, [r4, #789]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L832
.L755:
	add	r9, r5, #20992
	mov	r1, r10
	add	r9, r9, #216
	mov	r2, r6
	sub	r0, fp, #76
	bl	BsInit
	mov	r2, #60
	ldr	r3, [r7, #48]
	mov	r1, #0
	mov	r0, r9
	blx	r3
	mov	r3, #0
	mov	r1, #32
	strb	r3, [r4, #1561]
	sub	r0, fp, #76
	bl	BsSkip
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	ldr	r3, [r7, #68]
	ldr	r1, .L847+8
	uxtb	r2, r0
	strb	r0, [r4, #728]
	mov	r0, #18
	blx	r3
	ldrb	r10, [r4, #728]	@ zero_extendqisi2
	cmp	r10, #3
	beq	.L833
.L757:
	adds	r10, r10, #0
	ldrb	r3, [r4, #795]	@ zero_extendqisi2
	movne	r10, #1
	cmp	r3, #1
	movne	r2, #0
	andeq	r2, r10, #1
	cmp	r2, #0
	bne	.L760
	cmp	r3, #2
	beq	.L760
	ldr	r3, [r4, #2120]
	cmp	r3, #1
	movne	r10, #0
	andeq	r10, r10, #1
	cmp	r10, #0
	bne	.L760
	mov	r6, r6, asl #3
	b	.L763
.L835:
	bl	BsPos
	add	r10, r10, #1
	cmp	r0, r6
	bgt	.L834
	cmp	r10, #6400
	beq	.L764
.L763:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	sub	r0, fp, #76
	bne	.L835
	cmp	r10, #6400
	bcs	.L764
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	subs	r3, r0, #0
	beq	.L836
	ldr	r1, [r4, #896]
	cmp	r1, #0
	moveq	r0, r1
	bne	.L837
.L767:
	str	r10, [r4, #1500]
	mov	r1, #1
	str	r0, [r4, #1504]
	sub	r0, fp, #76
	bl	BsGet
	subs	r10, r0, #0
	bne	.L768
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L847+12
	blx	r3
	strb	r10, [r4, #1561]
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, .L847+16
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r5, r0
	beq	.L794
	ldr	r0, [r4, #2480]
	mov	r3, r10
	mov	r2, r10
	mov	r1, #103
	blx	r6
	mov	r0, r5
	b	.L756
.L764:
	mov	r3, #0
	sub	r0, fp, #76
	strb	r3, [r4, #1561]
	bl	BsPos
	ldr	r3, [r7, #68]
	mov	r2, r10
	ldr	r1, .L847+20
	mov	r4, r0
	mov	r0, #1
	blx	r3
	mov	r0, r4
	b	.L756
.L834:
	sub	r0, fp, #76
	bl	BsPos
	ldr	r3, [r7, #68]
	ldr	r1, .L847+24
	mov	r4, r0
	mov	r0, #1
	blx	r3
	mov	r0, r4
	b	.L756
.L833:
	ldr	r3, .L847+28
	ldr	r3, [r3]
	ands	r3, r3, #8
	bne	.L757
	strb	r3, [r4, #1561]
	sub	r0, fp, #76
	str	r3, [fp, #-80]
	bl	BsPos
	ldr	r2, .L847+16
	ldr	r6, [r2]
	cmp	r6, #0
	mov	r5, r0
	beq	.L758
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2480]
	mov	r2, r3
	blx	r6
.L758:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L847+32
	blx	r3
	mov	r0, r5
	b	.L756
.L760:
	sub	r0, fp, #76
	bl	BsPos
	b	.L756
.L768:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #729]
	cmp	r0, #0
	beq	.L838
	ldrb	r3, [r4, #728]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L770
	cmp	r3, #3
	beq	.L839
.L771:
	mov	r3, #0
	strb	r3, [r4, #730]
.L772:
	ldrb	r3, [r4, #836]	@ zero_extendqisi2
	mov	r2, #0
	strb	r2, [r4, #731]
	cmp	r3, #2
	addeq	r10, r5, #16384
	beq	.L773
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	add	r10, r5, #16384
	strb	r0, [r4, #732]
	ldrb	r3, [r10, #3626]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r4, #734]
	moveq	r3, #2
	streqb	r3, [r4, #733]
	bne	.L840
.L775:
	ldrb	r3, [r4, #840]	@ zero_extendqisi2
	sub	r3, r3, #1
	cmp	r3, #1
	bls	.L776
.L779:
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	moveq	r3, #1
	streqb	r3, [r4, #735]
	strneb	r0, [r4, #735]
.L785:
	ldrb	r3, [r4, #728]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L841
.L773:
	mov	r3, #1
	strb	r3, [r4, #1561]
	ldr	r3, [r10, #3584]
	add	r0, r5, #21760
	mov	r1, r9
	mov	r2, #60
	orr	r3, r3, #2
	str	r3, [r10, #3584]
	ldr	r3, [r8, #3328]
	add	r0, r0, #152
	ldr	r9, [r7, #52]
	add	r3, r3, #1
	str	r3, [r8, #3328]
	blx	r9
	sub	r0, fp, #76
	bl	BsPos
	mov	r3, r0, asr #31
	mov	r9, r0
	add	r1, r0, #7
	rsb	r6, r0, r6
	mov	r3, r3, lsr #29
	str	r6, [r5, #1288]
	add	r2, r9, r3
	ldr	r0, [r4, #1576]
	and	r2, r2, #7
	cmp	r9, #0
	rsb	r3, r3, r2
	add	r3, r3, r0
	strb	r3, [r5, #1286]
	ldr	r3, [r4, #1568]
	movge	r1, r9
	add	r3, r3, r1, asr #3
	str	r3, [r5, #1296]
	ldrb	r3, [r8, #3421]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L789
	ldrb	r2, [r8, #3501]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L842
.L789:
	mov	r3, #0
	str	r3, [r5, #1292]
	strb	r3, [r5, #1287]
	str	r3, [r5, #1300]
.L790:
	ldrb	r3, [r4, #728]	@ zero_extendqisi2
	strb	r3, [r5, #1284]
	ldrb	r3, [r4, #737]	@ zero_extendqisi2
	strb	r3, [r5, #1282]
	ldrb	r3, [r4, #736]	@ zero_extendqisi2
	strb	r3, [r5, #1281]
	ldrb	r3, [r4, #735]	@ zero_extendqisi2
	strb	r3, [r5, #1285]
	ldrb	r3, [r4, #732]	@ zero_extendqisi2
	strb	r3, [r5, #1283]
	ldr	r2, [r10, #3580]
	cmp	r2, #0
	bne	.L843
.L791:
	mov	r0, r5
	bl	MP4_Record_SlcSegID
	mov	r0, r9
	b	.L756
.L836:
	ldr	r2, [r7, #68]
	mov	r0, #1
	ldr	r1, .L847+12
	str	r3, [fp, #-80]
	blx	r2
	ldr	r3, [fp, #-80]
	sub	r0, fp, #76
	strb	r3, [r4, #1561]
	bl	BsPos
	ldr	r2, .L847+16
	ldr	r6, [r2]
	cmp	r6, #0
	mov	r5, r0
	beq	.L794
	ldr	r3, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2480]
	mov	r2, r3
	blx	r6
	mov	r0, r5
	b	.L756
.L837:
	sub	r0, fp, #76
	bl	BsGet
	b	.L767
.L794:
	mov	r0, r5
	b	.L756
.L843:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L847+36
	blx	r3
	mov	r0, r5
	bl	MP4_ClearCurPic
	b	.L791
.L838:
	add	r5, r5, #16384
	mov	r3, #4
	mov	r2, #1
	strb	r3, [r4, #728]
	strb	r3, [r4, #1432]
	sub	r0, fp, #76
	strb	r2, [r4, #1561]
	ldr	r3, [r5, #3584]
	orr	r3, r3, #128
	str	r3, [r5, #3584]
	bl	BsPos
	b	.L756
.L839:
	ldrb	r3, [r4, #840]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L771
.L770:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #730]
	b	.L772
.L841:
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #736]
	cmp	r2, #0
	beq	.L844
	ldrb	r3, [r4, #728]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L773
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #737]
	cmp	r2, #0
	bne	.L773
	strb	r2, [r4, #1561]
	sub	r0, fp, #76
	str	r2, [fp, #-80]
	bl	BsPos
	ldr	r3, .L847+16
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r5, r0
	beq	.L788
	ldr	r2, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2480]
	mov	r3, r2
	blx	r6
.L788:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L847+40
	blx	r3
	mov	r0, r5
	b	.L756
.L840:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #733]
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r4, #734]
	b	.L775
.L776:
	ldrb	r3, [r4, #728]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L779
	ldrb	r3, [r4, #852]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L779
	add	r3, r5, #20992
	mov	r2, #0
	add	r3, r3, #252
	str	r5, [fp, #-84]
	str	r6, [fp, #-88]
	mov	r6, r2
	str	r9, [fp, #-80]
	mov	r5, r3
	str	r8, [fp, #-92]
	b	.L784
.L780:
	ldr	r3, [r4, #1536]
	cmp	r3, #500
	bne	.L781
	ldr	r2, [r4, #1540]
	movw	r3, #413
	cmp	r2, r3
	beq	.L782
.L781:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
.L782:
	sub	r0, fp, #76
	bl	bs_get_spritetrajectory
	subs	r3, r0, #0
	moveq	r8, r3
	bne	.L845
.L783:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsSkip
	str	r9, [r5]
	str	r8, [r5, #4]
	add	r6, r6, #1
	ldrb	r3, [r4, #852]	@ zero_extendqisi2
	add	r5, r5, #8
	cmp	r3, r6
	bls	.L846
.L784:
	sub	r0, fp, #76
	bl	bs_get_spritetrajectory
	subs	r8, r0, #0
	moveq	r9, r8
	beq	.L780
	mov	r1, r8
	sub	r0, fp, #76
	bl	BsGet
	sub	r2, r8, #1
	movs	r3, r0, asr r2
	mov	r9, r0
	moveq	r3, #1
	moveq	r3, r3, asl r8
	subeq	r3, r3, #1
	eoreq	r9, r9, r3
	rsbeq	r9, r9, #0
	b	.L780
.L845:
	mov	r1, r3
	sub	r0, fp, #76
	str	r3, [fp, #-96]
	bl	BsGet
	ldr	r3, [fp, #-96]
	sub	r1, r3, #1
	movs	r2, r0, asr r1
	mov	r8, r0
	moveq	r2, #1
	moveq	r3, r2, asl r3
	subeq	r3, r3, #1
	eoreq	r3, r3, r0
	rsbeq	r8, r3, #0
	b	.L783
.L842:
	ldr	r2, [r8, #3508]
	strb	r3, [r5, #1287]
	mov	r3, r2, asl #3
	str	r3, [r5, #1292]
	ldr	r3, [r8, #3504]
	str	r3, [r5, #1300]
	b	.L790
.L844:
	strb	r2, [r4, #1561]
	sub	r0, fp, #76
	str	r2, [fp, #-80]
	bl	BsPos
	ldr	r3, .L847+16
	ldr	r6, [r3]
	cmp	r6, #0
	mov	r5, r0
	beq	.L787
	ldr	r2, [fp, #-80]
	mov	r1, #103
	ldr	r0, [r4, #2480]
	mov	r3, r2
	blx	r6
.L787:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldrb	r2, [r4, #728]	@ zero_extendqisi2
	ldr	r1, .L847+44
	blx	r3
	mov	r0, r5
	b	.L756
.L846:
	ldr	r9, [fp, #-80]
	ldr	r5, [fp, #-84]
	ldr	r6, [fp, #-88]
	ldr	r8, [fp, #-92]
	b	.L779
.L848:
	.align	2
.L847:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC45
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
	ldr	r10, .L875
	add	r9, r0, #12288
	mov	r4, r0
	mov	r7, r1
	mov	r5, r2
	ldr	r3, [r10, #48]
	mov	r2, #32
	sub	r0, fp, #76
	mov	r1, #0
	blx	r3
	ldr	r6, [r9, #3328]
	movw	r3, #510
	sub	r2, r6, #1
	cmp	r2, r3
	bhi	.L870
	movw	r3, #3576
	mov	r1, r7
	ldrh	r7, [r9, r3]
	mov	r2, r5
	add	r3, r6, #1
	sub	r0, fp, #76
	ubfx	r7, r7, #7, #4
	str	r3, [r9, #3328]
	add	r7, r7, #17
	add	r8, r4, #20480
	bl	BsInit
	sub	r0, fp, #76
	mov	r1, r7
	bl	BsSkip
	ldr	r3, [r8, #1492]
	ldr	r1, [r8, #1496]
	add	r3, r3, #15
	add	r1, r1, #15
	mov	r2, r3, lsr #4
	mov	r3, r1, lsr #4
	mul	r3, r3, r2
	cmp	r3, #0
	beq	.L852
	mov	r2, r3
	mov	r1, #0
.L853:
	add	r1, r1, #1
	movs	r2, r2, lsr #1
	uxth	r1, r1
	bne	.L853
	sxth	r1, r1
	sub	r0, fp, #76
	str	r3, [fp, #-80]
	bl	BsGet
	ldr	r3, [fp, #-80]
	mov	r7, r6, asl #2
	mov	r6, r6, asl #5
	sub	ip, r3, #1
	rsb	r1, r7, r6
	add	r1, r4, r1
	cmp	r0, ip
	str	r0, [r1, #1304]
	bhi	.L871
.L854:
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	rsb	r10, r7, r6
	add	r10, r4, r10
	mov	r1, #1
	strb	r0, [r10, #1285]
	sub	r0, fp, #76
	bl	BsGet
	cmp	r0, #0
	bne	.L872
	ldrb	r3, [r8, #728]	@ zero_extendqisi2
	mov	r5, r5, asl #3
	add	r2, r4, #16384
	strb	r3, [r10, #1284]
	ldrb	r3, [r8, #732]	@ zero_extendqisi2
	strb	r3, [r10, #1283]
.L858:
	ldrb	r1, [r8, #736]	@ zero_extendqisi2
	rsb	r3, r7, r6
	add	r3, r4, r3
	sub	r0, fp, #76
	str	r3, [fp, #-80]
	strb	r1, [r3, #1281]
	ldrb	r1, [r8, #737]	@ zero_extendqisi2
	strb	r1, [r3, #1282]
	ldr	r1, [r2, #3584]
	orr	r1, r1, #16
	str	r1, [r2, #3584]
	bl	BsPos
	ldr	r3, [fp, #-80]
	mov	r2, r0, asr #31
	mov	r10, r0
	rsb	r5, r0, r5
	str	r5, [r3, #1288]
	mov	r2, r2, lsr #29
	ldr	ip, [r8, #1576]
	add	r1, r10, r2
	cmp	r10, #0
	and	r1, r1, #7
	add	r0, r0, #7
	rsb	r2, r2, r1
	movge	r0, r10
	add	r2, r2, ip
	strb	r2, [r3, #1286]
	ldr	r2, [r8, #1568]
	add	r2, r2, r0, asr #3
	str	r2, [r3, #1296]
	ldrb	r2, [r9, #3421]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L859
	ldrb	r1, [r9, #3501]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L873
.L859:
	rsb	r6, r7, r6
	mov	r3, #0
	add	r6, r4, r6
	str	r3, [r6, #1292]
	strb	r3, [r6, #1287]
	str	r3, [r6, #1300]
.L860:
	mov	r0, r4
	bl	MP4_Record_SlcSegID
	mov	r0, r10
.L869:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L872:
	mov	r5, r5, asl #3
.L856:
	mov	r1, #1
	sub	r0, fp, #76
	bl	BsGet
	mov	r10, r0
	sub	r0, fp, #76
	bl	BsPos
	cmp	r10, #0
	cmpne	r0, r5
	blt	.L856
	mov	r1, #1
	sub	r0, fp, #76
	add	r2, r4, #16384
	str	r2, [fp, #-80]
	bl	BsSkip
	ldr	r2, [fp, #-80]
	ldr	r1, [r2, #3684]
	cmp	r1, #0
	bne	.L874
.L857:
	mov	r1, #1
	sub	r0, fp, #76
	str	r2, [fp, #-80]
	bl	BsSkip
	mov	r1, #2
	sub	r0, fp, #76
	bl	BsGet
	rsb	r10, r7, r6
	add	r10, r4, r10
	mov	r1, #3
	strb	r0, [r10, #1284]
	sub	r0, fp, #76
	bl	BsGet
	ldrb	r3, [r10, #1284]	@ zero_extendqisi2
	ldr	r2, [fp, #-80]
	cmp	r3, #0
	strb	r0, [r10, #1283]
	beq	.L858
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsSkip
	ldrb	r3, [r10, #1284]	@ zero_extendqisi2
	ldr	r2, [fp, #-80]
	cmp	r3, #2
	bne	.L858
	mov	r1, #3
	sub	r0, fp, #76
	bl	BsSkip
	ldr	r2, [fp, #-80]
	b	.L858
.L870:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #24
	ldr	r0, [r3, #2480]
	bl	MP4_ClearCurPacket
	mov	r0, r4
	add	r4, r4, #16384
	bl	MP4_ClearCurPic
	ldr	r5, [r10, #68]
	mov	r0, #1
	ldr	r3, [r4, #3584]
	ldr	r2, .L875+4
	bic	r3, r3, #432
	ldr	r1, .L875+8
	bic	r3, r3, #2
	str	r3, [r4, #3584]
	ldr	r3, [r9, #3328]
	blx	r5
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L874:
	sub	r0, fp, #76
	bl	BsSkip
	ldr	r2, [fp, #-80]
	b	.L857
.L873:
	ldr	r1, [r9, #3508]
	strb	r2, [r3, #1287]
	mov	r2, r1, asl #3
	str	r2, [r3, #1292]
	ldr	r2, [r9, #3504]
	str	r2, [r3, #1300]
	b	.L860
.L852:
	mov	r1, r3
	sub	r0, fp, #76
	bl	BsGet
	mov	r7, r6, asl #2
	mov	r6, r6, asl #5
	rsb	r3, r7, r6
	add	r3, r4, r3
	str	r0, [r3, #1304]
	b	.L854
.L871:
	mov	r2, r0
	ldr	r4, [r10, #68]
	ldr	r1, .L875+12
	mov	r0, #1
	blx	r4
	mvn	r0, #0
	b	.L869
.L876:
	.align	2
.L875:
	.word	vfmw_Osal_Func_Ptr_S
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
	ldr	r10, .L895
	add	r8, r0, #12288
	mov	r4, r0
	mov	r6, r1
	mov	r9, r2
	ldr	r3, [r10, #48]
	mov	r2, #32
	sub	r0, fp, #76
	mov	r1, #0
	blx	r3
	ldr	r5, [r8, #3328]
	movw	r3, #510
	sub	r2, r5, #1
	str	r2, [fp, #-80]
	cmp	r2, r3
	bhi	.L891
	ldrb	r3, [r8, #3576]	@ zero_extendqisi2
	mov	r1, r6
	add	r0, r5, #1
	mov	r2, r9
	ubfx	r6, r3, #3, #4
	str	r0, [r8, #3328]
	add	r6, r6, #17
	sub	r0, fp, #76
	bl	BsInit
	sub	r0, fp, #76
	mov	r1, r6
	add	r7, r4, #20480
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	ldrb	lr, [r7, #740]	@ zero_extendqisi2
	mov	r3, r5, asl #2
	mov	r5, r5, asl #5
	rsb	r6, r3, r5
	movw	ip, #1206
	add	r6, r4, r6
	movw	r1, #1204
	mul	r0, lr, r0
	str	r0, [r6, #1304]
	ldrh	ip, [r4, ip]
	ldrh	r1, [r4, r1]
	mul	r1, r1, ip
	sub	r1, r1, #1
	cmp	r0, r1
	bhi	.L892
	mov	r1, #2
	sub	r0, fp, #76
	str	r3, [fp, #-84]
	bl	BsSkip
	mov	r1, #5
	sub	r0, fp, #76
	bl	BsGet
	strb	r0, [r6, #1285]
	sub	r0, fp, #76
	ldrb	r1, [r7, #728]	@ zero_extendqisi2
	strb	r1, [r6, #1284]
	ldrb	r1, [r7, #732]	@ zero_extendqisi2
	strb	r1, [r6, #1283]
	ldrb	r1, [r7, #736]	@ zero_extendqisi2
	strb	r1, [r6, #1281]
	ldrb	r1, [r7, #737]	@ zero_extendqisi2
	strb	r1, [r6, #1282]
	bl	BsPos
	ldr	r3, [fp, #-84]
	mov	r1, r0, asr #31
	cmp	r0, #0
	add	ip, r0, #7
	rsb	r9, r0, r9, lsl #3
	mov	r1, r1, lsr #29
	movge	ip, r0
	mov	r10, r0
	add	r0, r0, r1
	str	r9, [r6, #1288]
	and	r0, r0, #7
	ldr	lr, [r7, #1576]
	rsb	r1, r1, r0
	add	r0, r4, #16384
	add	r1, r1, lr
	strb	r1, [r6, #1286]
	ldr	r2, [r7, #1568]
	add	ip, r2, ip, asr #3
	str	ip, [r6, #1296]
	ldr	r2, [r0, #3584]
	orr	r2, r2, #16
	str	r2, [r0, #3584]
	ldrb	r2, [r8, #3421]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L893
.L881:
	rsb	r5, r3, r5
	mov	r3, #0
	add	r5, r4, r5
	str	r3, [r5, #1292]
	strb	r3, [r5, #1287]
	str	r3, [r5, #1300]
.L882:
	ldr	r3, [fp, #-80]
	mov	r2, r3, asl #2
	mov	r7, r3, asl #5
	rsb	r3, r2, r7
	add	r3, r4, r3
	ldr	r1, [r3, #1300]
	cmp	r1, #0
	bne	.L894
.L883:
	rsb	r7, r2, r7
	ldrb	r3, [r8, #3576]	@ zero_extendqisi2
	add	r7, r4, r7
	ubfx	r3, r3, #3, #4
	ldr	r2, [r7, #1288]
	add	r3, r3, r2
	str	r3, [r7, #1288]
.L884:
	mov	r0, r4
	bl	MP4_Record_SlcSegID
	mov	r0, r10
.L879:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L894:
	ldr	r1, [r3, #1292]
	cmp	r1, #0
	beq	.L883
	ldrb	r2, [r8, #3576]	@ zero_extendqisi2
	ubfx	r2, r2, #3, #4
	add	r2, r2, r1
	str	r2, [r3, #1292]
	b	.L884
.L893:
	ldrb	r1, [r8, #3501]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L881
	ldr	r3, [r8, #3508]
	strb	r2, [r6, #1287]
	mov	r3, r3, asl #3
	str	r3, [r6, #1292]
	ldr	r3, [r8, #3504]
	str	r3, [r6, #1300]
	b	.L882
.L891:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #24
	ldr	r0, [r3, #2480]
	bl	MP4_ClearCurPacket
	mov	r0, r4
	add	r4, r4, #16384
	bl	MP4_ClearCurPic
	ldr	r5, [r10, #68]
	mov	r0, #1
	ldr	r3, [r4, #3584]
	ldr	r2, .L895+4
	bic	r3, r3, #432
	ldr	r1, .L895+8
	bic	r3, r3, #2
	str	r3, [r4, #3584]
	ldr	r3, [r8, #3328]
	blx	r5
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L892:
	mov	r3, r1
	mov	r2, r0
	ldr	r4, [r10, #68]
	mov	r0, #1
	ldr	r1, .L895+12
	blx	r4
	mvn	r0, #0
	b	.L879
.L896:
	.align	2
.L895:
	.word	vfmw_Osal_Func_Ptr_S
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
	ldrb	r3, [ip, #3576]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L907
	tst	r3, #4
	beq	.L908
	mov	r0, r4
	bl	Mp4_Syntax_Slice_SH
	cmn	r0, #1
	beq	.L905
.L901:
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L908:
	movw	r0, #3576
	ldrh	r0, [ip, r0]
	ubfx	r0, r0, #7, #4
	sub	lr, r0, #1
	cmp	lr, #6
	bfils	r3, r0, #3, #4
	mov	r0, r4
	strlsb	r3, [ip, #3576]
	bl	Mp4_Syntax_Slice_SH
	cmn	r0, #1
	bne	.L901
.L905:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #24
	ldr	r0, [r3, #2480]
	bl	MP4_ClearCurPacket
	ldr	r3, .L910
	ldr	r2, .L910+4
	mov	r0, #1
	ldr	r1, .L910+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L907:
	str	r2, [fp, #-28]
	str	r1, [fp, #-24]
	bl	Mp4_Check_Slice_NotSH
	ldr	r1, [fp, #-24]
	ldr	r2, [fp, #-28]
	cmp	r0, #0
	beq	.L909
	mov	r1, r2
	mov	r0, r4
	bl	Mp4_Combine_SliceData
	cmp	r0, #0
	bne	.L905
	mov	r0, r4
	bl	MP4_Record_SlcSegID
	b	.L901
.L909:
	mov	r0, r4
	bl	Mp4_Syntax_Slice_NotSH
	cmn	r0, #1
	beq	.L905
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L911:
	.align	2
.L910:
	.word	vfmw_Osal_Func_Ptr_S
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
	ldr	r3, [r5, #2036]
	cmp	r3, #62
	bgt	.L915
	add	r1, r0, #12288
	add	r4, r0, r3, lsl #2
	add	r4, r4, #20480
	add	r2, r3, #1
	ldr	r0, [r1, #3432]
	str	r0, [r4, #1780]
	str	r2, [r5, #2036]
	ldrb	r2, [r1, #3421]	@ zero_extendqisi2
	cmp	r2, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r2, [r1, #3501]	@ zero_extendqisi2
	cmp	r2, #1
	ldreq	r2, [r1, #3512]
	addeq	r3, r3, #2
	streq	r2, [r4, #1784]
	streq	r3, [r5, #2036]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L915:
	bl	MP4_Clean_HeadPacket
	add	r1, r4, #15680
	ldr	r0, [r5, #2480]
	add	r1, r1, #24
	bl	MP4_ClearCurPacket
	ldr	ip, .L916
	ldr	r2, [r5, #2036]
	mov	r3, #62
	ldr	r1, .L916+4
	mov	r0, #0
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L917:
	.align	2
.L916:
	.word	vfmw_Osal_Func_Ptr_S
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
	beq	.L921
	ldr	r6, .L923
	add	r1, r4, #15680
	add	r0, r4, #22016
	add	r1, r1, #24
	mov	r2, #160
	add	r0, r0, #80
	ldr	r3, [r6, #52]
	add	r5, r4, #20480
	blx	r3
	add	r1, r4, #15808
	add	r0, r4, #22016
	ldr	r3, [r6, #52]
	add	r1, r1, #56
	add	r0, r0, #240
	mov	r2, #4
	blx	r3
	ldr	r3, [r5, #2044]
	str	r7, [r5, #2040]
	cmp	r3, #0
	beq	.L922
.L920:
	ldr	r3, [r5, #2048]
	add	r3, r3, #1
	str	r3, [r5, #2048]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L922:
	mov	r0, r4
	bl	MP4_Record_PacketID
	mov	r3, #1
	str	r3, [r5, #2044]
	b	.L920
.L921:
	ldr	r3, .L923
	mov	r0, #1
	ldr	r1, .L923+4
	ldr	r3, [r3, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L924:
	.align	2
.L923:
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
	ldr	r9, .L1076
	mov	r5, r2
	mov	r4, r0
	mov	r8, r1
	str	r2, [fp, #-120]
	ldr	r3, [r9, #48]
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #108
	blx	r3
	mov	r2, r5
	mov	r1, r8
	sub	r0, fp, #108
	bl	BsInit
	sub	r0, fp, #108
	mov	r1, #32
	add	r7, r4, #16384
	bl	BsShow
	movw	r3, #510
	mov	r10, #0
	str	r10, [r7, #3588]
	cmp	r0, r3
	mov	r5, r0
	beq	.L1055
	add	r1, r4, #12288
	ldrb	r3, [r1, #3576]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L1056
.L931:
	add	r6, r4, #20480
	mov	r5, #196
	mov	r2, #1
	strb	r2, [r6, #797]
.L932:
	and	r3, r3, #2
	ands	r3, r3, #255
	bne	.L933
	ldr	r2, [r7, #3584]
	ands	r10, r2, #130
	bne	.L1057
	cmp	r5, #197
	beq	.L1058
	cmp	r5, #432
	beq	.L1059
	movw	r3, #437
	cmp	r5, r3
	beq	.L1060
	bic	r3, r5, #15
	cmp	r3, #288
	beq	.L1061
	movw	r3, #435
	cmp	r5, r3
	beq	.L1062
	movw	r3, #438
	cmp	r5, r3
	beq	.L1063
	cmp	r5, #196
	beq	.L1064
	movw	r3, #434
	cmp	r5, r3
	beq	.L1065
	movw	r3, #286
	cmp	r5, r3
	bne	.L948
	ldr	r3, .L1076+4
	ldr	r10, [r3]
	cmp	r10, #0
	beq	.L949
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r6, #2480]
	blx	r10
.L949:
	ldr	r3, [fp, #-120]
	add	r1, r4, #15680
	ldr	r0, [r6, #2480]
	add	r1, r1, #24
	sub	r3, r3, #4
	str	r3, [fp, #-120]
	bl	MP4_ClearCurPacket
	ldr	r3, [r7, #3584]
	add	r2, r8, #4
	str	r2, [fp, #-128]
	tst	r3, #2
	orrne	r3, r3, #256
	strne	r3, [r7, #3584]
.L950:
	add	r10, r4, #53248
	ldrb	r3, [r10, #3561]	@ zero_extendqisi2
	cmp	r3, #1
	mov	r3, #0
	str	r3, [fp, #-124]
	beq	.L987
.L956:
	ldrb	r3, [r6, #1559]	@ zero_extendqisi2
	cmp	r3, #1
	ldrne	r10, [fp, #-124]
	bne	.L1050
	ldr	r3, [r6, #2056]
	add	r1, r4, #19968
	add	r0, r4, #21248
	add	r1, r1, #32
	add	r3, r3, #1
	mov	ip, #0
	str	r3, [r6, #2056]
	mov	r2, #604
	add	r0, r0, #60
	ldr	r3, [r9, #52]
	str	ip, [r6, #2060]
	blx	r3
	ldr	r2, [r6, #1492]
	ldr	r0, [r7, #3700]
	ldr	r1, [r7, #3696]
	cmp	r2, r0
	beq	.L1066
.L975:
	ldr	r3, .L1076+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L977
	ldr	ip, [r6, #1496]
	mov	r3, #8
	strh	r2, [fp, #-114]	@ movhi
	sub	r2, fp, #116
	strh	r1, [fp, #-112]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-110]	@ movhi
	strh	ip, [fp, #-116]	@ movhi
	ldr	r0, [r6, #2480]
	blx	r5
	ldr	r0, [r7, #3700]
	ldr	r1, [r7, #3696]
.L977:
	mov	r5, #1
	str	r0, [r6, #1492]
	str	r1, [r6, #1496]
.L976:
	sxtb	r5, r5
	cmp	r5, #1
	beq	.L1067
.L979:
	ldr	r3, [r6, #1496]
	mov	r2, #0
	ldr	r1, [r6, #1492]
	ldr	r10, [fp, #-124]
	str	r3, [r6, #2080]
	str	r1, [r6, #2076]
	ldr	r3, [r7, #3700]
	str	r3, [r6, #1492]
	ldr	r3, [r7, #3696]
	strb	r2, [r6, #1559]
	str	r3, [r6, #1496]
	b	.L1050
.L1057:
	orr	r2, r2, #32
	mov	r10, r3
	str	r2, [r7, #3584]
	mov	r3, #1
	str	r3, [r7, #3588]
.L1050:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L933:
	ldr	r2, [fp, #-120]
	mov	r1, r8
	mov	r0, r4
	bl	MP4_Dec_Slice
	str	r0, [fp, #-124]
.L937:
	add	r10, r4, #53248
	str	r8, [fp, #-128]
	ldrb	r3, [r10, #3561]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L987
	ldr	r2, [fp, #-120]
	ldr	r3, [fp, #-124]
	cmp	r3, r2, asl #3
	bhi	.L955
.L1072:
	movw	r3, #438
	cmp	r5, r3
	cmpne	r5, #196
	bne	.L956
	ldr	r3, [r7, #3584]
	tst	r3, #130
	beq	.L956
	ldrb	r3, [r6, #797]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1068
	ldr	r2, [r6, #1496]
	ldr	r1, [r6, #1492]
	cmp	r2, #0
	str	r2, [r6, #2084]
	str	r1, [r6, #2088]
	beq	.L960
	ldr	r3, [r6, #2076]
	cmp	r2, r3
	beq	.L960
.L995:
	mov	r7, #1
.L961:
	ldr	r3, .L1076+4
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L965
	ldr	r0, [r6, #2080]
	mov	r3, #8
	ldr	ip, [r6, #2076]
	strh	r2, [fp, #-112]	@ movhi
	sub	r2, fp, #116
	strh	r1, [fp, #-110]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-114]	@ movhi
	strh	ip, [fp, #-116]	@ movhi
	ldr	r0, [r6, #2480]
	blx	r5
.L965:
	sxtb	r5, r7
	cmp	r5, #1
	beq	.L1069
.L967:
	ldr	r2, [r6, #2084]
	ldr	r3, [r6, #2088]
	str	r2, [r6, #2076]
	str	r3, [r6, #2080]
.L959:
	add	r1, r4, #20992
	add	r0, r4, #21760
	ldr	r3, [r9, #52]
	mov	r2, #60
	add	r1, r1, #216
	add	r0, r0, #152
	blx	r3
	ldr	r3, [r9, #68]
	ldr	r1, .L1076+8
	mov	r0, #2
	blx	r3
	ldr	r3, [fp, #-128]
	ldr	r2, [fp, #-124]
	rsb	r10, r8, r3
	ldr	r3, [r6, #2060]
	add	r10, r2, r10, lsl #3
	add	r3, r3, #1
	str	r3, [r6, #2060]
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1056:
	mov	r2, r0, lsr #8
	add	r6, r4, #20480
	sub	r2, r2, #128
	mov	r0, #2
	cmp	r2, #3
	strb	r0, [r6, #797]
	ldrlsb	r3, [r1, #3576]	@ zero_extendqisi2
	orrls	r3, r3, r0
	strlsb	r3, [r1, #3576]
	b	.L932
.L960:
	cmp	r1, #0
	beq	.L962
	ldr	r3, [r6, #2080]
	cmp	r1, r3
	beq	.L1070
	cmp	r2, #0
	beq	.L995
	ldr	r3, [r6, #2076]
	cmp	r2, r3
	bne	.L995
	mov	r7, #1
	b	.L988
.L987:
	ldr	r1, [r7, #3696]
	cmp	r1, #0
	beq	.L953
	ldr	r2, [r7, #3700]
	cmp	r2, #0
	bne	.L1071
.L953:
	ldr	r2, [fp, #-120]
	mov	r3, #0
	strb	r3, [r10, #3561]
	ldr	r3, [fp, #-124]
	cmp	r3, r2, asl #3
	bls	.L1072
.L955:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+12
	blx	r3
	ldr	r2, [fp, #-128]
	ldr	r3, [r7, #3584]
	rsb	r10, r8, r2
	bic	r3, r3, #432
	mov	r10, r10, asl #3
	bic	r3, r3, #2
	str	r3, [r7, #3584]
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1055:
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
	mov	r6, r0
	sub	r0, fp, #76
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r6, r3
	bne	.L927
	ldr	r2, .L1076+4
	add	r3, r4, #53248
	mov	r1, #1
	add	r6, r4, #20480
	strb	r1, [r3, #3560]
	ldr	r5, [r2]
	cmp	r5, r10
	beq	.L928
	mov	r3, r10
	mov	r2, r10
	mov	r1, #117
	ldr	r0, [r6, #2480]
	blx	r5
.L928:
	ldr	r3, [r7, #3584]
	add	r1, r4, #15680
	add	r1, r1, #24
	mov	r10, #0
	tst	r3, #130
	orrne	r3, r3, #32
	strne	r3, [r7, #3584]
	movne	r2, #1
	strne	r2, [r7, #3588]
	ldr	r0, [r6, #2480]
	bl	MP4_ClearCurPacket
	b	.L1050
.L927:
	add	r3, r4, #12288
	ldrb	r3, [r3, #3576]	@ zero_extendqisi2
	tst	r3, #1
	bne	.L931
	add	r6, r4, #20480
	mov	r2, #2
	strb	r2, [r6, #797]
	b	.L932
.L948:
	ldr	r3, [fp, #-120]
	add	r1, r4, #15680
	ldr	r0, [r6, #2480]
	add	r1, r1, #24
	sub	r3, r3, #4
	str	r3, [fp, #-120]
	add	r3, r8, #4
	str	r3, [fp, #-128]
	bl	MP4_ClearCurPacket
	b	.L950
.L1059:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+16
	blx	r3
	mov	r1, r8
	str	r10, [r6, #2092]
	mov	r0, r4
	ldr	r2, [fp, #-120]
	bl	Mp4_Syntax_Vos
	mov	r1, r5
	str	r0, [fp, #-124]
	mov	r0, r4
	bl	MP4_Record_HeadPacketInfo
	b	.L937
.L962:
	ldr	r5, [r6, #2484]
	subs	r7, r5, #1
	movne	r7, #1
	cmp	r2, #0
	beq	.L965
.L989:
	ldr	r3, [r6, #2076]
	cmp	r2, r3
	bne	.L961
.L964:
	cmp	r1, #0
	beq	.L965
.L988:
	ldr	r3, [r6, #2080]
	cmp	r3, r1
	beq	.L965
	b	.L961
.L1063:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+20
	blx	r3
	ldr	r3, [fp, #-120]
	cmp	r3, #4
	beq	.L1073
	ldr	r2, [fp, #-120]
	mov	r1, r8
	mov	r0, r4
	bl	Mp4_Syntax_Vop
	ldr	r3, [r7, #3584]
	tst	r3, #2
	str	r0, [fp, #-124]
	bne	.L944
	add	r1, r4, #15680
	ldr	r0, [r6, #2480]
	add	r1, r1, #24
	bl	MP4_ClearCurPacket
.L943:
	ldr	r3, [r9, #68]
	mov	r0, #7
	ldr	r2, [fp, #-124]
	ldr	r1, .L1076+24
	blx	r3
	b	.L937
.L1066:
	ldr	r3, [r6, #1496]
	cmp	r3, r1
	bne	.L975
	ldr	r5, [r6, #2484]
	subs	r5, r5, #1
	movne	r5, #1
	b	.L976
.L1060:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+28
	blx	r3
	mov	r3, #1
	mov	r1, r8
	ldr	r2, [fp, #-120]
	str	r3, [r6, #2092]
	mov	r0, r4
	bl	Mp4_Syntax_Vo
	mov	r1, r5
	str	r0, [fp, #-124]
	mov	r0, r4
	bl	MP4_Record_HeadPacketInfo
	b	.L937
.L1061:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+32
	blx	r3
	mov	r3, #2
	ldr	r2, [fp, #-120]
	mov	r1, r8
	str	r3, [r6, #2092]
	mov	r0, r4
	bl	Mp4_Syntax_Vol
	mov	r1, r5
	str	r0, [fp, #-124]
	mov	r0, r4
	bl	MP4_Record_HeadPacketInfo
	ldrb	r3, [r6, #1559]	@ zero_extendqisi2
	ldr	r2, .L1076
	cmp	r3, #1
	beq	.L937
	ldrb	r10, [r6, #1560]	@ zero_extendqisi2
	cmp	r10, #1
	bne	.L937
	add	r1, r4, #20480
	add	r0, r4, #19968
	ldr	r3, [r2, #52]
	add	r1, r1, #124
	add	r0, r0, #32
	mov	r2, #604
	blx	r3
	strb	r10, [r6, #1559]
	strb	r10, [r6, #789]
	b	.L937
.L1058:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+36
	blx	r3
	add	r1, r4, #15680
	add	r1, r1, #24
	ldr	r0, [r6, #2480]
	bl	MP4_ClearCurPacket
	b	.L1050
.L1070:
	ldr	r5, [r6, #2484]
	subs	r7, r5, #1
	movne	r7, #1
	cmp	r2, #0
	beq	.L964
	b	.L989
.L1068:
	ldrb	r3, [r6, #728]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L958
	ldr	r2, [r6, #1508]
	ldr	r3, [r6, #1500]
	ldr	r0, [r6, #1504]
	str	r2, [r6, #1512]
	add	r2, r2, r3
	str	r2, [r6, #1508]
	ldr	r3, [r7, #3688]
	ldr	r1, [r6, #1520]
	mla	r3, r3, r2, r0
	rsb	r2, r1, r3
	str	r2, [r6, #1524]
	str	r3, [r6, #1516]
	str	r3, [r6, #1520]
	b	.L959
.L1062:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+40
	blx	r3
	mov	r3, #3
	mov	r1, r8
	ldr	r2, [fp, #-120]
	str	r3, [r6, #2092]
	mov	r0, r4
	bl	Mp4_Syntax_Gop
	mov	r1, r5
	str	r0, [fp, #-124]
	mov	r0, r4
	bl	MP4_Record_HeadPacketInfo
	b	.L937
.L1071:
	mov	r0, r4
	bl	Frame_Init
	cmp	r0, #0
	beq	.L953
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L1076+44
	blx	r3
	b	.L953
.L1064:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+48
	blx	r3
	ldr	r2, [fp, #-120]
	mov	r1, r8
	mov	r0, r4
	bl	Mp4_Syntax_ShortHeader
	ldr	r3, [r7, #3584]
	tst	r3, #2
	str	r0, [fp, #-124]
	beq	.L1051
	mov	r1, #196
	mov	r0, r4
	bl	MP4_Record_HeadPacketInfo
	b	.L937
.L1065:
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L1076+52
	blx	r3
	ldr	r2, [fp, #-120]
	mov	r1, r8
	mov	r0, r4
	bl	Mp4_Syntax_UserData
	str	r0, [fp, #-124]
.L1051:
	add	r1, r4, #15680
	ldr	r0, [r6, #2480]
	add	r1, r1, #24
	bl	MP4_ClearCurPacket
	b	.L937
.L1069:
	ldr	r1, [r10, #3544]
	ldr	r0, [r6, #2480]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L968
	ldr	r1, [r7, #212]
	mov	r3, #0
	ldr	r0, [r6, #2480]
	str	r3, [fp, #-120]
	bl	FreeUsdByDec
	ldr	r1, [r7, #216]
	ldr	r0, [r6, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r7, #220]
	ldr	r0, [r6, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r7, #224]
	ldr	r0, [r6, #2480]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-120]
	mov	r2, r5
	str	r3, [r7, #212]
	str	r3, [r7, #216]
	str	r3, [r7, #220]
	str	r3, [r7, #224]
	ldr	r1, [r10, #3544]
	ldr	r0, [r6, #2480]
	bl	FSP_ClearLogicFs
	mov	r2, r5
	ldr	r1, [r10, #3536]
	ldr	r0, [r6, #2480]
	bl	FSP_ClearLogicFs
	ldr	r3, [fp, #-120]
	str	r3, [r10, #3536]
	str	r3, [r10, #3544]
	ldr	r0, [r6, #2480]
	bl	FSP_GetNullLogicFs
	str	r0, [r10, #3544]
	str	r0, [r10, #3536]
.L968:
	add	r5, r4, #22528
	mov	r3, #0
	add	r5, r5, #80
	str	r3, [r6, #2488]
	ldr	r0, [r6, #2480]
	mov	r1, r5
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r6, #1580]
	ldr	r2, [r3, #776]
	cmp	r2, #0
	bne	.L969
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1074
.L969:
	ldr	r0, [r6, #2480]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L1052
.L971:
	ldr	r2, [r6, #2088]
	mov	r0, r4
	ldr	r1, [r6, #2084]
	bl	Frame_Init
	cmp	r0, #0
	beq	.L967
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L1076+56
	blx	r3
	b	.L967
.L944:
	movw	r1, #438
	mov	r0, r4
	bl	MP4_Record_HeadPacketInfo
	b	.L943
.L958:
	ldr	r1, [r6, #1512]
	ldr	r2, [r6, #1500]
	ldr	r3, [r7, #3688]
	ldr	r0, [r6, #1504]
	add	r2, r2, r1
	ldr	r1, [r6, #1524]
	mla	r3, r3, r2, r0
	ldr	r2, [r6, #1520]
	rsb	r2, r2, r1
	add	r2, r2, r3
	str	r2, [r6, #1528]
	str	r3, [r6, #1516]
	b	.L959
.L1073:
	mov	r1, r5
	mov	r0, r4
	str	r10, [fp, #-124]
	bl	MP4_Record_HeadPacketInfo
	b	.L943
.L1067:
	ldr	r1, [r10, #3544]
	ldr	r0, [r6, #2480]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L980
	ldr	r1, [r8, #212]
	mov	r3, #0
	ldr	r0, [r6, #2480]
	str	r3, [fp, #-120]
	bl	FreeUsdByDec
	ldr	r1, [r8, #216]
	ldr	r0, [r6, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r8, #220]
	ldr	r0, [r6, #2480]
	bl	FreeUsdByDec
	ldr	r1, [r8, #224]
	ldr	r0, [r6, #2480]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-120]
	mov	r2, r5
	str	r3, [r8, #212]
	str	r3, [r8, #216]
	str	r3, [r8, #220]
	str	r3, [r8, #224]
	ldr	r1, [r10, #3544]
	ldr	r0, [r6, #2480]
	bl	FSP_ClearLogicFs
	mov	r2, r5
	ldr	r1, [r10, #3536]
	ldr	r0, [r6, #2480]
	bl	FSP_ClearLogicFs
	ldr	r3, [fp, #-120]
	str	r3, [r10, #3536]
	str	r3, [r10, #3544]
	ldr	r0, [r6, #2480]
	bl	FSP_GetNullLogicFs
	str	r0, [r10, #3544]
	str	r0, [r10, #3536]
.L980:
	add	r5, r4, #22528
	mov	r3, #0
	add	r5, r5, #80
	str	r3, [r6, #2488]
	ldr	r0, [r6, #2480]
	mov	r1, r5
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r6, #1580]
	ldr	r2, [r3, #776]
	cmp	r2, #0
	bne	.L981
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1075
.L981:
	ldr	r0, [r6, #2480]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L1053
.L983:
	mov	r0, r4
	ldr	r2, [r6, #1492]
	ldr	r1, [r6, #1496]
	bl	Frame_Init
	cmp	r0, #0
	beq	.L979
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L1076+60
	blx	r3
	b	.L979
.L1074:
	ldr	r3, [r6, #2484]
	cmp	r3, #0
	bne	.L971
.L1052:
	mov	r0, r5
	bl	ResetVoQueue
	b	.L971
.L1075:
	ldr	r3, [r6, #2484]
	cmp	r3, #0
	bne	.L983
.L1053:
	mov	r0, r5
	bl	ResetVoQueue
	b	.L983
.L1077:
	.align	2
.L1076:
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
	ldr	r3, [r5, #1616]
	cmp	r3, #0
	beq	.L1091
	add	r3, r0, #12288
	ldrb	r4, [r3, #3421]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L1092
	cmp	r4, #0
	bne	.L1086
	ldrb	r2, [r3, #3501]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1086
	ldr	ip, .L1095
	add	r1, r0, #15744
	ldr	r2, [r3, #3428]
	add	r0, r0, #22016
	ldr	r3, [r5, #1628]
	add	r1, r1, #40
	ldr	r6, [ip, #52]
	add	r0, r0, #160
	add	r3, r3, r2
	mov	r2, #80
	str	r3, [r5, #1628]
	blx	r6
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1092:
	ldrb	r4, [r5, #1621]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L1093
	cmp	r4, #0
	bne	.L1085
	ldrb	r2, [r5, #1701]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1085
	ldr	r2, [r3, #3428]
	mov	r0, r4
	ldr	r3, [r5, #1708]
	add	r3, r3, r2
	str	r3, [r5, #1708]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1086:
	ldr	r3, .L1095
	movw	r2, #5367
.L1090:
	ldr	r1, .L1095+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1093:
	ldr	r1, [r3, #3424]
	ldr	r2, [r5, #1624]
	cmp	r1, r2
	bcc	.L1094
	ldr	r2, [r3, #3428]
	mov	r0, #0
	ldr	r3, [r5, #1628]
	add	r3, r3, r2
	str	r3, [r5, #1628]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1085:
	ldr	r3, .L1095
	movw	r2, #5353
	b	.L1090
.L1094:
	ldr	r3, .L1095
	add	r1, r0, #15680
	add	r0, r0, #22016
	add	r1, r1, #24
	mov	r2, #80
	add	r0, r0, #160
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #0
	strb	r4, [r5, #1701]
	mov	r0, r3
	strb	r3, [r5, #1621]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1091:
	ldr	r2, .L1095+8
	ldr	r4, [r2]
	cmp	r4, #0
	beq	.L1080
	ldr	r0, [r5, #2480]
	mov	r2, r3
	mov	r1, #103
	blx	r4
.L1080:
	ldr	r3, .L1095
	mov	r0, #1
	ldr	r1, .L1095+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1096:
	.align	2
.L1095:
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
	beq	.L1100
	ldr	r5, .L1101
	mov	r0, r4
	bl	MP4_Record_PacketID
	add	r1, r4, #22016
	add	r0, r4, #15680
	add	r1, r1, #80
	ldr	r3, [r5, #52]
	mov	r2, #160
	add	r0, r0, #24
	blx	r3
	add	r1, r4, #22016
	add	r0, r4, #15744
	ldr	r3, [r5, #52]
	add	r1, r1, #240
	mov	r2, #4
	add	r0, r0, #32
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1100:
	add	r3, r4, #20480
	add	r1, r4, #15680
	add	r1, r1, #24
	ldr	r0, [r3, #2480]
	bl	MP4_ClearCurPacket
	ldr	r3, .L1101
	movw	r2, #5383
	ldr	r1, .L1101+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1102:
	.align	2
.L1101:
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
	ldr	r2, [r4, #3424]
	mov	r6, r0
	sub	r0, fp, #60
	str	r2, [r5, #1568]
	ldr	r1, [r4, #3416]
	str	r1, [r5, #1564]
	ldr	r2, [r4, #3428]
	str	r3, [r5, #1576]
	str	r2, [r5, #1572]
	bl	BsInit
	sub	r0, fp, #60
	mov	r1, #32
	bl	BsShow
	ldrb	r3, [r4, #3576]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L1129
	mov	r3, #1
	strb	r3, [r5, #797]
	ldrb	r3, [r4, #3576]	@ zero_extendqisi2
	tst	r3, #2
	bne	.L1106
	ldr	r3, [r5, #2040]
	mov	r1, #196
.L1110:
	movw	r2, #438
	cmp	r1, r2
	cmpeq	r3, r2
	beq	.L1117
	cmp	r1, #196
	cmpeq	r3, #196
	bne	.L1127
.L1117:
	ldr	r3, [r5, #2048]
	cmp	r3, #1
	bgt	.L1109
	b	.L1127
.L1129:
	mov	r3, r0, lsr #8
	mov	r2, #2
	sub	r3, r3, #128
	strb	r2, [r5, #797]
	cmp	r3, #3
	mov	r1, r0
	bls	.L1130
.L1105:
	ldrb	r3, [r4, #3576]	@ zero_extendqisi2
	tst	r3, #2
	ldr	r3, [r5, #2040]
	bne	.L1108
	movw	r2, #438
	cmp	r3, r2
	cmpne	r0, #196
	beq	.L1110
.L1109:
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
.L1127:
	mov	r0, #0
.L1114:
	ldr	r3, [r4, #3416]
	cmp	r3, #0
	beq	.L1120
	ldr	r3, [r4, #3424]
	cmp	r3, #0
	mvneq	r0, #0
.L1126:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1108:
	movw	r2, #438
	sub	r0, r0, #196
	rsb	r3, r2, r3
	clz	r0, r0
	clz	r3, r3
	mov	r0, r0, lsr #5
	mov	r3, r3, lsr #5
	orrs	r2, r0, r3
	beq	.L1111
	ldrb	r2, [r5, #1561]	@ zero_extendqisi2
	cmp	r2, #1
	orreq	r0, r0, #1
	cmp	r0, #0
	bne	.L1119
.L1111:
	mov	r0, r6
	bl	MP4_Renew_CurPacket
	b	.L1114
.L1106:
	ldr	r3, [r5, #2040]
	movw	r2, #438
	rsb	r3, r2, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
.L1119:
	ldr	r2, [r5, #2044]
	cmp	r2, #1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r3, #0
	beq	.L1127
	ldr	r3, [r5, #1628]
	cmp	r3, #4
	bne	.L1127
	b	.L1111
.L1130:
	ldrb	r3, [r4, #3576]	@ zero_extendqisi2
	orr	r3, r3, r2
	strb	r3, [r4, #3576]
	b	.L1105
.L1120:
	mvn	r0, #0
	b	.L1126
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
	add	r4, r0, #20480
	mov	r6, r0
	mov	r5, r1
	ldr	r3, [r4, #2068]
	cmp	r3, #0
	beq	.L1132
	ldr	r3, [r1, #12]
	cmp	r3, #0
	ble	.L1132
	ldr	r3, [r1, #8]
	cmp	r3, #0
	beq	.L1132
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L1132
	ldr	r7, .L1234
	mov	r0, #2
	ldr	r1, .L1234+4
	add	r8, r6, #15680
	add	r8, r8, #24
	ldr	r3, [r7, #68]
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r2, [r5, #8]
	mov	r0, #7
	ldr	r1, .L1234+8
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r2, [r5, #12]
	mov	r0, #7
	ldr	r1, .L1234+12
	blx	r3
	ldr	r3, [r7, #68]
	ldrb	r2, [r5, #5]	@ zero_extendqisi2
	mov	r0, #7
	ldr	r1, .L1234+16
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r2, [r5, #88]
	mov	r0, #7
	ldr	r1, .L1234+20
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r2, [r5, #92]
	mov	r0, #7
	ldr	r1, .L1234+24
	blx	r3
	ldr	r3, [r7, #68]
	ldrb	r2, [r5, #85]	@ zero_extendqisi2
	mov	r0, #7
	ldr	r1, .L1234+28
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r2, [r5, #12]
	mov	r0, #7
	ldr	r1, .L1234+32
	blx	r3
	ldr	r2, [r5]
	ldr	r3, [r7, #68]
	mov	r0, #7
	ldr	r1, .L1234+36
	ldrb	r2, [r2]	@ zero_extendqisi2
	blx	r3
	ldr	r2, [r5]
	ldr	r3, [r7, #68]
	mov	r0, #7
	ldr	r1, .L1234+40
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	blx	r3
	ldr	r2, [r5]
	ldr	r3, [r7, #68]
	mov	r0, #7
	ldr	r1, .L1234+44
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	blx	r3
	ldr	r2, [r5]
	ldr	r3, [r7, #68]
	mov	r0, #7
	ldr	r1, .L1234+48
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	blx	r3
	ldr	r3, [r7, #52]
	mov	r2, #160
	mov	r1, r5
	mov	r0, r8
	blx	r3
	mov	r1, r8
	mov	r0, r6
	bl	MP4_GetScdUpMsg
	mov	r0, r6
	bl	MP4_Check_CurPacket
	cmn	r0, #1
	mov	r9, r0
	beq	.L1220
	mov	r1, r8
	mov	r0, r6
	bl	MP4_GetScdUpMsg
	add	r3, r6, #12288
	mov	r2, #0
	mov	r0, r6
	ldr	r1, [r3, #3424]
	str	r1, [r4, #1568]
	ldr	r1, [r3, #3416]
	str	r1, [r4, #1564]
	ldr	r3, [r3, #3428]
	str	r2, [r4, #1576]
	str	r3, [r4, #1572]
	bl	Mp4_Get_DecMode
	ldr	r3, [r4, #1580]
	ldr	r2, [r3, #868]
	cmp	r2, #1
	beq	.L1221
.L1136:
	add	r9, r6, #16384
	add	r8, r6, #53248
	ldr	r3, [r9, #3584]
	str	r3, [r8, #3564]
.L1137:
	ldr	r2, [r4, #1572]
	mov	r0, r6
	ldr	r1, [r4, #1564]
	bl	Mp4_Syntax_Parse
	ldr	r3, [r4, #1564]
	ldr	ip, [r4, #1580]
	ldr	r1, [r4, #1568]
	mov	r2, r0, lsr #3
	and	r0, r0, #7
	add	r3, r3, r2
	str	r3, [r4, #1564]
	ldr	r3, [r4, #1572]
	add	r1, r2, r1
	str	r0, [r4, #1576]
	rsb	r3, r2, r3
	str	r1, [r4, #1568]
	str	r3, [r4, #1572]
	ldr	r3, [ip, #868]
	cmp	r3, #1
	beq	.L1222
.L1138:
	ldr	r3, [r9, #3584]
	tst	r3, #288
	beq	.L1139
	bic	r3, r3, #432
	bic	r3, r3, #2
	str	r3, [r9, #3584]
	ldr	r3, [r4, #1612]
	cmp	r3, #2
	beq	.L1223
	cmp	r3, #1
	beq	.L1224
	cmp	r3, #4
	bne	.L1142
	ldrb	r3, [r4, #1432]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1144
	ldr	r3, [r4, #2096]
	cmp	r3, #0
	moveq	r3, #2
	movne	r3, #1
	str	r3, [r4, #2096]
.L1142:
	mov	r0, r6
	bl	Mp4_Frame_Atr
	cmn	r0, #1
	mov	r9, r0
	beq	.L1225
	ldr	r1, [r8, #3536]
	ldr	r0, [r4, #2480]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r8, #3544]
	mov	r10, r0
	ldr	r0, [r4, #2480]
	bl	FSP_GetFsImagePtr
	clz	r2, r10
	mov	r2, r2, lsr #5
	clz	r1, r0
	str	r0, [fp, #-56]
	mov	r1, r1, lsr #5
	orrs	r9, r1, r2
	bne	.L1226
	ldrb	r0, [r4, #795]	@ zero_extendqisi2
	and	r3, r0, #253
	cmp	r3, #1
	beq	.L1227
	cmp	r0, #2
	beq	.L1228
.L1153:
	ldrb	r3, [r4, #1432]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1163
	ldr	r3, [r4, #2488]
	cmp	r3, #0
	movgt	r3, #2
	movle	r3, #1
	str	r3, [r4, #2488]
	ldr	r1, [r8, #3536]
	ldr	r3, [r8, #3544]
	cmp	r1, r3
	beq	.L1161
	mov	r2, #0
	ldr	r0, [r4, #2480]
	bl	FSP_SetRef
	ldr	r1, [r8, #3536]
	ldr	r0, [r4, #2480]
	bl	FSP_GetDisplay
	cmp	r0, #3
	beq	.L1218
	mov	r2, #0
	ldr	r1, [r8, #3536]
	ldr	r0, [r4, #2480]
	bl	FSP_SetDisplay
.L1218:
	ldr	r3, [r8, #3544]
.L1161:
	str	r3, [r8, #3536]
	mov	r2, #1
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	strb	r3, [r6]
	ldr	r3, [r8, #3548]
	ldr	r1, [r8, #3552]
	str	r3, [r8, #3540]
	str	r1, [r8, #3544]
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	strb	r3, [r6, #1]
	ldr	r3, [r4, #1524]
	str	r3, [r8, #3548]
	ldr	r0, [r4, #2480]
	bl	FSP_SetRef
	ldr	r1, [r8, #3536]
	ldr	r0, [r4, #2480]
	bl	FSP_RemovePmv
	ldrb	r3, [r4, #1432]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L1163
	ldrb	r10, [r4, #792]	@ zero_extendqisi2
	cmp	r10, #0
	beq	.L1229
.L1173:
	mov	r9, #0
.L1213:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1227:
	cmp	r2, #0
	bne	.L1151
	ldr	r2, [r4, #1580]
	ldr	r1, [r10, #200]
	ldr	r2, [r2]
	cmp	r1, r2
	bls	.L1153
	ldr	r1, [r8, #3552]
	mov	r2, r3
	ldr	r0, [r4, #2480]
	mvn	r9, #0
	str	r3, [fp, #-56]
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r1, [r4, #1580]
	ldr	r3, [fp, #-56]
	ldr	r4, [r7, #68]
	ldr	r2, [r10, #200]
	mov	r0, r3
	ldr	r3, [r1]
	ldr	r1, .L1234+52
	blx	r4
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1144:
	sub	r2, r3, #2
	tst	r2, #253
	bne	.L1147
	ldr	r2, [r4, #2096]
	cmp	r2, #2
	beq	.L1180
.L1147:
	cmp	r3, #1
	streq	r3, [r4, #2096]
	b	.L1142
.L1222:
	ldr	r3, [ip, #908]
	cmp	r3, #0
	beq	.L1138
	b	.L1173
.L1221:
	ldr	r3, [r3, #908]
	cmp	r3, #1
	bne	.L1136
	add	r8, r6, #53248
	add	r9, r6, #16384
	ldr	r3, [r8, #3564]
	str	r3, [r9, #3584]
	b	.L1137
.L1163:
	mov	r2, r5
	mov	r1, #0
	mov	r0, r6
	bl	Mp4_Set_DecPar
	ldrb	ip, [r4, #1432]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1230
	ldr	r3, [r4, #2096]
	cmp	r3, #0
	moveq	r3, #2
	movne	r3, #1
	str	r3, [r4, #2096]
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1580]
	ldr	r2, [r1, #900]
	cmp	r2, #1
	beq	.L1172
.L1171:
	cmp	r2, #2
	beq	.L1178
.L1172:
	cmp	ip, #0
	mov	r3, #0
	strb	r3, [r6, #1198]
	bne	.L1173
	ldr	r3, .L1234+56
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L1173
	sub	r2, fp, #44
	ldr	r0, [r4, #2480]
	mov	r3, #4
	mov	r1, #20
	str	ip, [r2, #-4]!
	mov	r9, ip
	blx	r5
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1230:
	sub	r3, ip, #2
	sub	r9, ip, #2
	clz	r9, r9
	tst	r3, #253
	mov	r9, r9, lsr #5
	bne	.L1167
	ldr	r3, [r4, #2096]
	cmp	r3, #2
	beq	.L1231
.L1167:
	cmp	ip, #1
	beq	.L1232
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1580]
	ldr	r2, [r1, #900]
	cmp	r2, #1
	bne	.L1171
	cmp	r3, #0
	moveq	r9, #0
	andne	r9, r9, #1
	cmp	r9, #0
	beq	.L1172
	mov	r3, #0
	str	r3, [r6, #1036]
	ldr	r1, [r8, #3552]
	mvn	r9, #0
	ldr	r0, [r4, #2480]
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1213
.L1223:
	ldrb	r3, [r4, #1432]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1142
.L1141:
	mov	r0, r6
	mvn	r9, #0
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1213
.L1224:
	ldrb	r3, [r4, #1432]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L1142
	b	.L1141
.L1229:
	ldr	r3, [r7, #68]
	mov	r0, #11
	ldr	r1, .L1234+60
	blx	r3
	ldr	r1, [r8, #3552]
	ldr	r0, [r4, #2480]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #3536]
	mov	r5, r0
	ldr	r0, [r4, #2480]
	bl	FSP_GetLogicFs
	cmp	r5, #0
	cmpne	r0, #0
	beq	.L1233
	ldr	r2, [r5, #520]
	cmp	r2, #0
	beq	.L1175
	ldr	r1, [r5, #528]
	cmp	r1, #0
	beq	.L1175
	ldr	r1, [r5, #524]
	cmp	r1, #0
	beq	.L1175
	ldr	r0, [r0, #520]
	mov	r9, #0
	ldr	r3, [r1, #12]
	cmp	r0, #0
	ldr	r2, [r2, #12]
	ldr	lr, [r4, #1492]
	ldrne	r1, [r0, #12]
	mov	r0, r6
	ldr	ip, [r4, #1496]
	moveq	r1, r2
	str	r1, [sp]
	mov	r1, r5
	stmib	sp, {ip, lr}
	bl	Vdm_Mem_Move
	b	.L1213
.L1232:
	str	ip, [r4, #2096]
	add	r3, r6, #1040
	str	r3, [r6, #1036]
	ldr	r1, [r4, #1580]
	ldr	r2, [r1, #900]
	cmp	r2, #1
	beq	.L1169
	cmp	r2, #2
	beq	.L1178
.L1169:
	mov	r3, #0
	strb	r3, [r6, #1198]
	b	.L1173
.L1228:
	cmp	r2, #0
	bne	.L1154
	ldr	r3, [r4, #1580]
	ldr	r2, [r10, #200]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L1155
	cmp	r1, #0
	bne	.L1156
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #200]
	cmp	r3, r2
	bcs	.L1153
.L1156:
	ldr	r1, [r8, #3552]
	mov	r2, #1
	ldr	r0, [r4, #2480]
	mvn	r9, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [r4, #1580]
	ldr	r2, [fp, #-56]
	mov	r0, #1
	ldr	r4, [r7, #68]
	ldr	r3, [r3]
	ldr	r2, [r2, #200]
	ldr	r1, .L1234+64
	blx	r4
	b	.L1213
.L1132:
	ldr	r3, .L1234
	mov	r0, #1
	ldr	r1, .L1234+68
	mvn	r9, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1213
.L1155:
	ldr	r1, [r8, #3552]
	mov	r2, #1
	ldr	r0, [r4, #2480]
	mvn	r9, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [r4, #1580]
	ldr	r2, [r10, #200]
	mov	r0, #1
	ldr	r4, [r7, #68]
	ldr	r3, [r3]
	ldr	r1, .L1234+72
	blx	r4
	b	.L1213
.L1180:
	mvn	r9, #0
	b	.L1213
.L1231:
	ldr	r1, [r8, #3552]
	mov	r2, #1
	ldr	r0, [r4, #2480]
	mvn	r9, #0
	bl	FSP_ClearLogicFs
	b	.L1213
.L1178:
	ldr	r2, [r1, #904]
	cmp	r2, #0
	andgt	r9, r9, #1
	movle	r9, #0
	cmp	r3, #0
	moveq	r3, #0
	andne	r3, r9, #1
	cmp	r3, #0
	beq	.L1172
	mov	r3, #0
	mov	r2, #1
	str	r3, [r6, #1036]
	mvn	r9, #0
	ldr	r1, [r8, #3552]
	ldr	r0, [r4, #2480]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #1580]
	mov	r0, r6
	ldr	r3, [r2, #904]
	add	r3, r3, r9
	str	r3, [r2, #904]
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1213
.L1151:
	ldr	r1, [r8, #3552]
	mov	r2, r3
	ldr	r0, [r4, #2480]
	mvn	r9, #0
	str	r3, [fp, #-56]
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r3, [fp, #-56]
	ldr	r4, [r7, #68]
	ldr	r2, .L1234+76
	mov	r0, r3
	ldr	r1, .L1234+80
	movw	r3, #3923
	blx	r4
	b	.L1213
.L1220:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L1234+84
	blx	r3
	b	.L1213
.L1139:
	ldr	r3, [r7, #68]
	mov	r0, #2
	ldr	r1, .L1234+88
	mvn	r9, #0
	blx	r3
	b	.L1213
.L1226:
	ldr	r4, [r7, #68]
	movw	r3, #3909
	ldr	r2, .L1234+76
	mov	r0, #1
	ldr	r1, .L1234+92
	mvn	r9, #0
	blx	r4
	b	.L1213
.L1225:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L1234+96
	blx	r3
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1213
.L1154:
	ldr	r1, [r8, #3552]
	mov	r2, #1
	ldr	r0, [r4, #2480]
	mvn	r9, #0
	bl	FSP_ClearLogicFs
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	ldr	r4, [r7, #68]
	movw	r3, #3943
	ldr	r2, .L1234+76
	ldr	r1, .L1234+80
	mov	r0, #1
	blx	r4
	b	.L1213
.L1175:
	ldr	r0, [r4, #2480]
	mov	r2, #1
	ldr	r1, [r8, #3552]
	mvn	r9, #0
	bl	FSP_ClearLogicFs
	ldr	r2, [r5, #524]
	ldr	r3, [r8, #3552]
	mov	r0, #0
	ldr	r4, [r7, #68]
	str	r2, [sp, #12]
	ldr	ip, [r5, #528]
	ldr	r2, [r8, #3536]
	ldr	r1, [r8, #3544]
	str	ip, [sp, #8]
	ldr	ip, [r5, #520]
	str	r1, [sp]
	ldr	r1, .L1234+100
	str	ip, [sp, #4]
	blx	r4
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1213
.L1233:
	str	r0, [fp, #-56]
	mov	r2, #1
	ldr	r1, [r8, #3552]
	mvn	r9, #0
	ldr	r0, [r4, #2480]
	bl	FSP_ClearLogicFs
	ldr	r3, [fp, #-56]
	movw	r2, #4148
	ldr	r1, .L1234+104
	mov	r0, r10
	str	r3, [sp]
	ldr	r3, .L1234
	ldr	r4, [r3, #68]
	mov	r3, r5
	blx	r4
	mov	r0, r6
	bl	MP4_ClearCurPic
	mov	r0, r6
	bl	MP4_Clean_HeadPacket
	b	.L1213
.L1235:
	.align	2
.L1234:
	.word	vfmw_Osal_Func_Ptr_S
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
	.word	.LC95
	.word	g_event_report
	.word	.LC90
	.word	.LC97
	.word	.LC74
	.word	.LC96
	.word	.LANCHOR1+1356
	.word	.LC94
	.word	.LC87
	.word	.LC93
	.word	.LC89
	.word	.LC88
	.word	.LC92
	.word	.LC91
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
	add	r0, r0, #20480
	ldr	r0, [r0, #1496]
	ldmfd	sp, {fp, sp, pc}
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
	add	r0, r0, #20480
	ldr	r0, [r0, #1492]
	ldmfd	sp, {fp, sp, pc}
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
	.type	__FUNCTION__.13531, %object
	.size	__FUNCTION__.13531, 15
__FUNCTION__.13531:
	.ascii	"Mp4_Set_DecPar\000"
	.space	1
	.type	__FUNCTION__.13665, %object
	.size	__FUNCTION__.13665, 23
__FUNCTION__.13665:
	.ascii	"Mp4_Syntax_Slice_NotSH\000"
	.space	1
	.type	__FUNCTION__.13679, %object
	.size	__FUNCTION__.13679, 20
__FUNCTION__.13679:
	.ascii	"Mp4_Syntax_Slice_SH\000"
	.type	__FUNCTION__.13694, %object
	.size	__FUNCTION__.13694, 14
__FUNCTION__.13694:
	.ascii	"MP4_Dec_Slice\000"
	.space	2
	.type	__FUNCTION__.13568, %object
	.size	__FUNCTION__.13568, 16
__FUNCTION__.13568:
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
	ASCII(.ascii	"actual frame size(%dx%d) exeed max config(%dx%d)\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC20:
	ASCII(.ascii	"MPEG4 Frame_Init return err!\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"MPEG4 Frame_Init PmvNum=%d, FrameNum=%d, error!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC22:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"dec_pts: %lld Usertag: %lld\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"%s %d  abnormal!\012\000" )
	.space	2
.LC27:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"MPEG4DEC Init  -----\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC30:
	ASCII(.ascii	"MPEG4DEC Init success -----\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"MPEG4 destroy\012\000" )
	.space	1
.LC32:
	ASCII(.ascii	"MPEG4 Already Destroyed!\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"pCtx = NULL in MPEG4\012\000" )
	.space	2
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
	.type	MemArrange.13469, %object
	.size	MemArrange.13469, 564
MemArrange.13469:
	.space	564
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
