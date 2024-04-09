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
	.file	"vdm_hal_mpeg2.c"
	.text
	.align	2
	.global	MP2HAL_V5R6C1_WriteSliceMsg
	.type	MP2HAL_V5R6C1_WriteSliceMsg, %function
MP2HAL_V5R6C1_WriteSliceMsg:
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
	mov	lr, r0
	add	ip, r0, #45056
	str	r0, [fp, #-72]
	ldr	r0, [r0, #268]
	mov	r7, r1
	str	r3, [fp, #-60]
	mov	r4, r2
	cmp	r0, #0
	mov	r3, lr
	ldr	r10, [ip, #236]
	add	r9, lr, #236
	mov	r5, #0
	moveq	r3, r0
	bne	.L26
.L2:
	cmp	r10, #0
	ble	.L23
	add	r2, r4, r3, lsl #5
	mov	r4, #0
	mov	r3, r3, asl #3
	str	r2, [fp, #-68]
	str	r3, [fp, #-64]
.L18:
	cmp	r4, #0
	mov	r5, #44
	mla	r5, r5, r4, r9
	ble	.L7
	ldr	r2, [r5, #32]
	ldr	r3, [r5, #-12]
	cmp	r2, r3
	bls	.L8
.L7:
	ldr	r3, [r5]
	mov	r8, #0
	ldr	r2, [r5, #16]
	mov	r0, r8
	and	lr, r3, #15
	ldr	ip, [r5, #8]
	str	r3, [fp, #-56]
	mov	r1, #0
	add	r2, r2, lr, lsl #3
	bfi	r0, ip, #0, #24
	bfi	r1, r2, #0, #7
	str	r0, [fp, #-48]
	ldr	r3, [fp, #-64]
	mov	r0, #4
	strb	r1, [fp, #-45]
	ldr	r2, [fp, #-48]
	add	r6, r3, r4, lsl #3
	ldr	r1, .L27
	add	r4, r4, #1
	str	r2, [r7, r6, asl #2]
	add	r6, r6, #1
	bl	dprint_vfmw
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-60]
	mov	ip, r8
	bic	r3, r3, #15
	ldr	r1, .L27+4
	rsb	r3, r2, r3
	mov	r0, #4
	bfi	ip, r3, #0, #24
	str	ip, [r7, r6, asl #2]
	str	ip, [fp, #-48]
	mov	r6, r6, asl #2
	mov	r2, ip
	bl	dprint_vfmw
	ldr	r3, [r5, #4]
	ldr	r2, [r5, #20]
	mov	r0, r8
	and	ip, r3, #15
	ldr	r1, [r5, #12]
	str	r3, [fp, #-56]
	add	r2, r2, ip, lsl #3
	bfi	r0, r1, #0, #24
	mov	r1, #0
	str	r0, [fp, #-48]
	bfi	r1, r2, #0, #7
	strb	r1, [fp, #-45]
	ldr	r2, [fp, #-48]
	add	ip, r6, #4
	ldr	r1, .L27+8
	mov	r0, #4
	str	r2, [r7, ip]
	bl	dprint_vfmw
	ldr	r2, [r5, #4]
	ldr	r3, [fp, #-56]
	mov	r0, #4
	cmp	r2, r8
	ldr	r1, .L27+12
	bicne	r3, r3, #15
	streq	r2, [fp, #-48]
	ldrne	r2, [fp, #-60]
	rsbne	r3, r2, r3
	bfine	r8, r3, #0, #24
	strne	r8, [fp, #-48]
	ldr	r2, [fp, #-48]
	add	r3, r6, #8
	mov	r8, #0
	str	r2, [r7, r3]
	bl	dprint_vfmw
	ldr	r3, [r5, #40]
	ldr	r2, [r5, #36]
	add	ip, r6, #12
	and	r3, r3, #63
	str	r8, [fp, #-48]
	bfi	r3, r2, #6, #1
	strb	r3, [fp, #-48]
	ldr	r2, [fp, #-48]
	mov	r0, #4
	ldr	r1, .L27+16
	str	r2, [r7, ip]
	bl	dprint_vfmw
	ldr	r2, [r5, #32]
	add	r3, r6, #16
	ldr	r1, .L27+20
	bfi	r8, r2, #0, #20
	mov	r0, #4
	str	r8, [r7, r3]
	mov	r2, r8
	str	r8, [fp, #-48]
	bl	dprint_vfmw
	cmp	r10, r4
	ble	.L11
	mov	r3, #44
	ldr	r2, [r5, #32]
	mul	r3, r3, r4
	add	r1, r9, r3
	ldr	r1, [r1, #32]
	cmp	r2, r1
	bcc	.L11
	sub	r3, r3, #44
	add	r3, r9, r3
	b	.L12
.L14:
	ldr	r1, [r3, #76]
	cmp	r1, r2
	bhi	.L16
.L12:
	add	r4, r4, #1
	add	r3, r3, #44
	cmp	r10, r4
	bne	.L14
.L20:
	ldr	r3, [fp, #-72]
	mov	r8, #0
	mov	r5, r8
	ldrh	r2, [r3, #150]
	ldrh	r3, [r3, #146]
	mul	r2, r3, r2
	sub	r2, r2, #1
.L17:
	add	r0, r6, #20
	mov	r3, #0
	bfi	r3, r2, #0, #20
	add	r6, r6, #24
	str	r3, [r7, r0]
	mov	r0, #4
	mov	r2, r3
	ldr	r1, .L27+24
	str	r3, [fp, #-48]
	bl	dprint_vfmw
	mov	r2, r5
	ldr	r1, .L27+28
	str	r8, [r7, r6]
	mov	r0, #4
	str	r5, [fp, #-48]
	bl	dprint_vfmw
	sub	r4, r4, #1
.L8:
	add	r4, r4, #1
	cmp	r10, r4
	bgt	.L18
.L23:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L11:
	cmp	r10, r4
	beq	.L20
.L16:
	mov	r3, #44
	ldr	r2, [fp, #-68]
	mla	r3, r3, r4, r9
	add	r5, r2, r4, lsl #5
	mov	r8, r5
	ldr	r2, [r3, #32]
	sub	r2, r2, #1
	b	.L17
.L26:
	ldr	r6, [r3, #236]
	mov	r8, r3
	ldr	r3, [r3, #252]
	mov	r1, #1
	and	r0, r6, #15
	str	r1, [fp, #-48]
	mov	r2, #0
	ldr	r1, .L27
	add	r3, r3, r0, lsl #3
	mov	r0, #4
	bfi	r2, r3, #0, #7
	strb	r2, [fp, #-45]
	ldr	r2, [fp, #-48]
	str	r2, [r7]
	bl	dprint_vfmw
	ldr	r2, [fp, #-60]
	bic	r3, r6, #15
	mov	ip, r5
	rsb	r3, r2, r3
	ldr	r1, .L27+4
	bfi	ip, r3, #0, #24
	mov	r0, #4
	str	ip, [r7, #4]
	mov	r2, ip
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	r6, [r8, #240]
	ldr	r3, [r8, #256]
	mov	r2, #0
	and	r0, r6, #15
	str	r5, [fp, #-48]
	ldr	r1, .L27+8
	add	r3, r3, r0, lsl #3
	mov	r0, #4
	bfi	r2, r3, #0, #7
	strb	r2, [fp, #-45]
	ldr	r2, [fp, #-48]
	str	r2, [r7, #8]
	bl	dprint_vfmw
	ldr	r3, [r8, #240]
	ldr	r1, .L27+12
	mov	r0, #4
	cmp	r3, r5
	bicne	r3, r6, #15
	streq	r3, [fp, #-48]
	ldrne	r2, [fp, #-60]
	rsbne	r3, r2, r3
	bfine	r5, r3, #0, #24
	strne	r5, [fp, #-48]
	ldr	r2, [fp, #-48]
	mov	r5, #0
	str	r2, [r7, #12]
	bl	dprint_vfmw
	ldr	r6, [fp, #-72]
	str	r5, [fp, #-48]
	mov	r0, #4
	ldr	r1, .L27+16
	ldr	r3, [r6, #276]
	ldr	r2, [r6, #272]
	and	r3, r3, #63
	bfi	r3, r2, #6, #1
	strb	r3, [fp, #-48]
	ldr	r2, [fp, #-48]
	str	r2, [r7, #16]
	bl	dprint_vfmw
	mov	r3, r5
	bfi	r3, r5, #0, #20
	ldr	r1, .L27+20
	str	r3, [r7, #20]
	mov	r0, #4
	mov	r2, r3
	str	r3, [fp, #-48]
	bl	dprint_vfmw
	ldr	r3, [r6, #268]
	mov	r2, r5
	ldr	r1, .L27+24
	sub	r3, r3, #1
	mov	r0, #4
	bfi	r2, r3, #0, #20
	str	r2, [r7, #24]
	str	r2, [fp, #-48]
	bl	dprint_vfmw
	add	r2, r4, #32
	mov	r3, #1
	str	r2, [r7, #28]
	b	.L2
.L28:
	.align	2
.L27:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	UNWIND(.fnend)
	.size	MP2HAL_V5R6C1_WriteSliceMsg, .-MP2HAL_V5R6C1_WriteSliceMsg
	.align	2
	.global	MP2HAL_V5R6C1_MakeReg
	.type	MP2HAL_V5R6C1_MakeReg, %function
MP2HAL_V5R6C1_MakeReg:
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
	ldrh	ip, [r2, #150]
	mov	r4, #3
	ldrh	r3, [r2, #146]
	mov	lr, #1
	ldr	r5, [r0, #8]
	mul	r3, r3, ip
	ldr	r6, [r5]
	mov	ip, #0
	sub	r3, r3, #1
	bfi	r6, r3, #0, #20
	str	r6, [r5]
	ldr	r5, [r0, #8]
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	orr	r3, r3, #64
	strb	r3, [r5, #3]
	ldr	r3, [r0, #8]
	ldrb	r5, [r3, #3]	@ zero_extendqisi2
	bfc	r5, #7, #1
	strb	r5, [r3, #3]
	ldr	r3, [r0, #12]
	ldrb	r5, [r3]	@ zero_extendqisi2
	bfi	r5, r4, #0, #4
	strb	r5, [r3]
	ldr	r4, [r0, #12]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	orr	r3, r3, #64
	strb	r3, [r4, #1]
	ldr	r3, [r0, #12]
	ldrb	r4, [r3, #1]	@ zero_extendqisi2
	bfc	r4, #7, #1
	strb	r4, [r3, #1]
	ldr	r3, [r0, #12]
	ldrh	r4, [r3, #2]
	bfi	r4, lr, #0, #12
	strh	r4, [r3, #2]	@ movhi
	ldr	lr, [r0, #12]
	ldrh	r3, [r2, #150]
	ldrb	r4, [lr, #3]	@ zero_extendqisi2
	cmp	r3, #120
	movgt	r3, #0
	movle	r3, #1
	bfi	r4, r3, #5, #1
	strb	r4, [lr, #3]
	ldr	r3, [r0, #12]
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	bfc	lr, #7, #1
	strb	lr, [r3, #3]
	ldr	r3, [r0, #12]
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	bfc	lr, #4, #1
	strb	lr, [r3, #3]
	ldr	r3, [r0, #12]
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	bfc	lr, #6, #1
	strb	lr, [r3, #3]
	ldr	r3, [r0, #60]
	ldrb	lr, [r3]	@ zero_extendqisi2
	bfc	lr, #0, #1
	strb	lr, [r3]
	ldr	r3, [r0, #56]
	str	ip, [r3]
	ldr	r3, [r0, #56]
	ldr	lr, [r2, #196]
	ldrb	ip, [r3]	@ zero_extendqisi2
	bfi	ip, lr, #0, #2
	strb	ip, [r3]
	ldr	r3, [r0, #56]
	ldr	lr, [r2, #192]
	ldrb	ip, [r3]	@ zero_extendqisi2
	bfi	ip, lr, #2, #2
	strb	ip, [r3]
	ldr	ip, [r0, #16]
	ldr	r3, [r1, #56]
	bic	r3, r3, #15
	str	r3, [ip]
	ldr	ip, [r0, #20]
	ldr	r3, [r1, #40]
	bic	r3, r3, #15
	str	r3, [ip]
	ldr	r1, [r0, #28]
	ldr	r3, [r2, #188]
	bic	r3, r3, #255
	str	r3, [r1]
	ldrb	r1, [r2, #3]	@ zero_extendqisi2
	ldrh	lr, [r2, #146]
	sub	r1, r1, #1
	ldr	ip, [r0, #32]
	cmp	r1, #1
	ldrh	r1, [r2, #150]
	movls	r3, #2
	movhi	r3, #1
	mul	r3, r3, lr
	str	r1, [ip]
	ldrh	r1, [r2, #150]
	ldr	ip, [r0, #36]
	mul	r3, r1, r3
	mov	r3, r3, asl #8
	str	r3, [ip]
	ldr	r3, [r2, #172]
	cmp	r3, #0
	ldreq	ip, [r2, #160]
	ldrne	ip, [r2, #164]
	ldreq	r1, [r0, #24]
	ldreq	r3, [r2, #152]
	ldrne	r1, [r0, #24]
	mov	r0, #0
	ldrne	r3, [r2, #156]
	add	r3, r3, ip, lsr #3
	bic	r3, r3, #15
	str	r3, [r1]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2HAL_V5R6C1_MakeReg, .-MP2HAL_V5R6C1_MakeReg
	.align	2
	.global	MP2HAL_V5R6C1_MakeDnMsg
	.type	MP2HAL_V5R6C1_MakeDnMsg, %function
MP2HAL_V5R6C1_MakeDnMsg:
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
	UNWIND(.pad #24)
	sub	sp, sp, #24
	ldrh	r3, [r2, #150]
	mov	r4, r2
	mov	r6, r0
	cmp	r3, #512
	mov	r5, r1
	ldrhi	r3, .L59
	bhi	.L56
	ldrh	r2, [r2, #146]
	cmp	r2, #512
	bhi	.L57
	ldr	r2, [r0]
	sub	r3, r3, #1
	ldrh	r1, [r2]
	bfi	r1, r3, #0, #9
	strh	r1, [r2]	@ movhi
	ldr	r2, [r0]
	ldrh	r3, [r4, #146]
	ldrh	r1, [r2, #2]
	sub	r3, r3, #1
	bfi	r1, r3, #0, #9
	strh	r1, [r2, #2]	@ movhi
	ldr	r3, [r0]
	ldr	r1, [r4, #176]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #1, #1
	strb	r2, [r3, #3]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #3]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bfi	r2, r1, #0, #2
	strb	r2, [r3, #1]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bfi	r2, r1, #2, #1
	strb	r2, [r3, #1]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3, #2]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #3
	strb	r2, [r3, #3]
	ldr	r3, [r0, #4]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	bfi	r2, r1, #3, #1
	strb	r2, [r3, #3]
	ldr	r3, [r0, #4]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #4, #1
	strb	r2, [r3, #3]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #15]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #4
	strb	r2, [r3]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #14]	@ zero_extendqisi2
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	bfi	r2, r1, #0, #4
	strb	r2, [r3, #1]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #13]	@ zero_extendqisi2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bfi	r2, r1, #0, #4
	strb	r2, [r3, #2]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #12]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #4
	strb	r2, [r3, #3]
	ldr	r3, [r0, #8]
	ldrb	r1, [r4, #6]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #7, #1
	strb	r2, [r3, #3]
	ldr	r3, [r0, #12]
	ldrb	r1, [r4, #11]	@ zero_extendqisi2
	ldrb	r2, [r3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #2
	strb	r2, [r3]
	ldr	r3, [r0, #12]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	ldrb	r1, [r4, #10]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3, #1]
	ldr	r3, [r0, #12]
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3, #2]
	ldr	r3, [r0, #12]
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfi	r2, r1, #0, #1
	strb	r2, [r3, #3]
	ldr	r2, [r0, #16]
	ldr	r3, [r4, #180]
	bic	r3, r3, #15
	str	r3, [r2]
	ldr	r2, [r0, #20]
	ldr	r3, [r4, #184]
	bic	r3, r3, #15
	str	r3, [r2]
	ldr	r2, [r0, #24]
	ldr	r3, [r4, #200]
	bic	r3, r3, #15
	str	r3, [r2]
	ldr	r2, [r0, #28]
	ldr	r3, [r4, #224]
	bic	r3, r3, #15
	str	r3, [r2]
	ldr	r0, [r4, #152]
	bl	MEM_Phy2Vir
	mov	r7, r0
	ldr	r0, [r4, #156]
	bl	MEM_Phy2Vir
	ldr	r1, [r4, #172]
	cmp	r1, #0
	mov	r9, r0
	beq	.L58
	ldr	r2, [r4, #160]
	cmp	r7, #0
	ldr	r8, [r4, #164]
	ldr	r1, [r4, #156]
	ldr	r0, [r6, #32]
	ldr	r3, [r4, #152]
	add	r8, r1, r8, lsr #3
	bic	lr, r8, #15
	add	r3, r3, r2, lsr #3
	ldr	ip, [r0]
	bic	r1, r3, #15
	and	r2, r3, #15
	rsb	r3, lr, r1
	bfi	ip, r3, #0, #24
	str	ip, [r0]
	ldr	r3, [r6, #36]
	ldr	r0, [r4, #168]
	ldr	r1, [r3]
	bfi	r1, r0, #0, #24
	str	r1, [r3]
	ldr	r1, [r6, #36]
	ldr	r3, [r4, #160]
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	and	r3, r3, #7
	add	r3, r3, r2, lsl #3
	bfi	r0, r3, #0, #7
	strb	r0, [r1, #3]
	beq	.L41
	ldr	r3, [r4, #160]
	mov	r0, #8
	ldr	r1, .L59+4
	add	ip, r7, r3, lsr #3
	ldrb	r2, [r7, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #160]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L59+8
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r7, r3
	ldrb	r2, [r7, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #152]
	mov	r0, #22
	ldr	r1, .L59+12
	add	r2, r2, r3
	bl	dprint_vfmw
.L41:
	ldr	r3, [r6, #40]
	and	r8, r8, #15
	cmp	r9, #0
	ldr	r2, [r3]
	bfc	r2, #0, #24
	str	r2, [r3]
	ldr	r2, [r6, #44]
	ldr	r3, [r4, #172]
	ldr	r1, [r2]
	add	r3, r3, #24
	bfi	r1, r3, #0, #24
	str	r1, [r2]
	ldr	r2, [r6, #44]
	ldr	r3, [r4, #164]
	ldrb	r1, [r2, #3]	@ zero_extendqisi2
	and	r3, r3, #7
	add	r8, r3, r8, lsl #3
	bfi	r1, r8, #0, #7
	strb	r1, [r2, #3]
	beq	.L40
	ldr	r3, [r4, #164]
	mov	r0, #8
	ldr	r1, .L59+16
	add	ip, r9, r3, lsr #3
	ldrb	r2, [r9, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #172]
	ldr	r3, [r4, #164]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L59+20
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r9, r3
	ldrb	r2, [r9, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
.L40:
	add	r7, r6, #64
	mov	r2, r6
.L44:
	mov	r1, r4
	mov	r3, r2
	mov	r0, #2
.L42:
	ldr	ip, [r3, #48]
	subs	r0, r0, #1
	ldrb	lr, [r1, #80]	@ zero_extendqisi2
	add	r3, r3, #4
	add	r1, r1, #8
	strb	lr, [ip]
	ldr	ip, [r3, #44]
	ldrb	lr, [r1, #88]	@ zero_extendqisi2
	strb	lr, [ip, #1]
	ldr	ip, [r3, #44]
	ldrb	lr, [r1, #104]	@ zero_extendqisi2
	strb	lr, [ip, #2]
	ldr	ip, [r3, #44]
	ldrb	lr, [r1, #120]	@ zero_extendqisi2
	strb	lr, [ip, #3]
	ldr	ip, [r3, #172]
	ldrb	lr, [r1, #8]	@ zero_extendqisi2
	strb	lr, [ip]
	ldr	ip, [r3, #172]
	ldrb	lr, [r1, #24]	@ zero_extendqisi2
	strb	lr, [ip, #1]
	ldr	ip, [r3, #172]
	ldrb	lr, [r1, #40]	@ zero_extendqisi2
	strb	lr, [ip, #2]
	ldr	ip, [r3, #172]
	ldrb	lr, [r1, #56]	@ zero_extendqisi2
	strb	lr, [ip, #3]
	bne	.L42
	add	r2, r2, #8
	add	r4, r4, #1
	cmp	r2, r7
	bne	.L44
	ldr	r2, [r6, #304]
	ldr	r3, [r5, #1148]
	bic	r3, r3, #15
	str	r3, [r2]
.L55:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L58:
	ldr	r0, [r6, #32]
	cmp	r7, #0
	ldr	r2, [r4, #160]
	ldr	r3, [r4, #152]
	ldr	ip, [r0]
	add	r3, r3, r2, lsr #3
	bfi	ip, r1, #0, #24
	str	ip, [r0]
	ldr	r1, [r6, #36]
	and	r2, r3, #15
	ldr	r3, [r4, #168]
	ldr	r0, [r1]
	add	r3, r3, #24
	bfi	r0, r3, #0, #24
	str	r0, [r1]
	ldr	r1, [r6, #36]
	ldr	r3, [r4, #160]
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	and	r3, r3, #7
	add	r3, r3, r2, lsl #3
	bfi	r0, r3, #0, #7
	strb	r0, [r1, #3]
	beq	.L39
	ldr	r3, [r4, #160]
	mov	r0, #8
	ldr	r1, .L59+24
	add	ip, r7, r3, lsr #3
	ldrb	r2, [r7, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #160]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L59+28
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r7, r3
	ldrb	r2, [r7, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
.L39:
	ldr	r3, [r6, #40]
	ldr	r2, [r3]
	bfc	r2, #0, #24
	str	r2, [r3]
	ldr	r3, [r6, #44]
	ldr	r2, [r3]
	bfc	r2, #0, #24
	str	r2, [r3]
	ldr	r3, [r6, #44]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bfc	r2, #0, #7
	strb	r2, [r3, #3]
	b	.L40
.L57:
	ldr	r3, .L59+32
.L56:
	mov	r0, #0
	ldr	r2, .L59+36
	ldr	r1, .L59+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L55
.L60:
	.align	2
.L59:
	.word	.LC8
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	.LC11
	.word	.LC12
	.word	.LC10
	.word	.LANCHOR0
	.word	.LC9
	UNWIND(.fnend)
	.size	MP2HAL_V5R6C1_MakeDnMsg, .-MP2HAL_V5R6C1_MakeDnMsg
	.align	2
	.global	MP2HAL_V5R6C1_CfgReg
	.type	MP2HAL_V5R6C1_CfgReg, %function
MP2HAL_V5R6C1_CfgReg:
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
	subs	r5, r2, #0
	mov	r7, r0
	mov	r8, r1
	mov	r0, #0
	str	r3, [fp, #-56]
	ldr	r6, [fp, #4]
	str	r0, [fp, #-48]
	bgt	.L93
	beq	.L80
	cmp	r5, #1
	moveq	r0, #0
	movteq	r0, 63941
	bne	.L94
.L65:
	ldr	r3, [r8]
	cmp	r3, #0
	beq	.L95
.L67:
	ldrh	lr, [r7, #150]
	mov	r3, r6
	ldrh	ip, [r7, #146]
	mov	r2, r5
	ldr	r1, [fp, #-48]
	mov	r0, #8
	add	r9, r7, #45056
	mul	ip, ip, lr
	sub	ip, ip, #1
	bfi	r1, ip, #0, #20
	str	r1, [fp, #-48]
	mov	ip, r1, lsr #24
	ubfx	r1, r1, #16, #8
	and	ip, ip, #62
	orr	r1, r1, #64
	orr	ip, ip, #65
	bfc	r1, #7, #1
	bfc	ip, #1, #1
	strb	r1, [fp, #-46]
	strb	ip, [fp, #-45]
	ldr	r4, [fp, #-48]
	mov	r1, r4
	bl	MFDE_ConfigReg
	mov	r2, r4
	ldr	r1, .L96
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r2, [r9, #244]
	ldrh	r1, [r7, #150]
	mov	r3, #0
	bfi	r3, r2, #4, #1
	mov	r2, #0
	and	r3, r3, #16
	cmp	r1, #120
	orr	r3, r3, #64
	mov	r1, #3
	bfi	r3, r2, #7, #1
	strb	r1, [fp, #-48]
	strb	r3, [fp, #-47]
	strh	r1, [fp, #-46]	@ movhi
	ble	.L78
	ldr	r0, [r9, #240]
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	and	r0, r0, #1
	bfi	r3, r2, #5, #1
	strb	r3, [fp, #-45]
.L69:
	ldrb	r1, [fp, #-45]	@ zero_extendqisi2
	mov	r4, #0
	strb	r4, [r7, #144]
	mov	r3, r6
	and	r1, r1, #111
	mov	r2, r5
	bfi	r1, r0, #6, #1
	strb	r1, [fp, #-45]
	ldr	r10, [fp, #-48]
	mov	r0, #12
	mov	r1, r10
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L96+4
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r8, #56]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #16
	bl	MFDE_ConfigReg
	ldr	r1, [r8, #40]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #20
	bl	MFDE_ConfigReg
	ldr	r1, [r9, #236]
	str	r4, [fp, #-48]
	cmp	r1, r4
	beq	.L70
	mov	r3, r7
	mvn	ip, #0
.L71:
	ldr	r2, [r3, #236]
	cmp	r2, #0
	beq	.L74
	ldr	r0, [r3, #244]
	bic	r2, r2, #15
	cmp	r0, #0
	ble	.L74
	cmp	ip, r2
	movcs	ip, r2
.L74:
	ldr	r2, [r3, #240]
	cmp	r2, #0
	beq	.L72
	ldr	r0, [r3, #248]
	bic	r2, r2, #15
	cmp	r0, #0
	ble	.L72
	cmp	ip, r2
	movcs	ip, r2
.L72:
	add	r4, r4, #1
	add	r3, r3, #44
	cmp	r4, r1
	bne	.L71
	cmn	ip, #1
	beq	.L70
	ldr	r3, [fp, #-56]
	mov	r1, ip
	mov	r2, r5
	mov	r0, #24
	str	ip, [fp, #-48]
	mov	r4, #0
	str	ip, [r3]
	mov	r3, r6
	bl	MFDE_ConfigReg
	ldrh	r1, [r7, #150]
	mov	r3, r6
	mov	r2, r5
	cmp	r1, #120
	mov	r0, #4
	movhi	r1, #0
	movls	r1, #1
	bl	SCD_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #60
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #64
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #68
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #72
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #76
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #80
	movt	r1, 48
	bl	MFDE_ConfigReg
	movw	r1, #3075
	mov	r3, r6
	mov	r2, r5
	mov	r0, #84
	movt	r1, 48
	bl	MFDE_ConfigReg
	ldr	r1, [r7, #188]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #96
	bl	MFDE_ConfigReg
	ldr	r1, [r7, #208]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #100
	bl	MFDE_ConfigReg
	mov	r3, r6
	ldr	r1, [r7, #212]
	mov	r2, r5
	mov	r0, #104
	bl	MFDE_ConfigReg
	ldr	r2, [r7, #212]
	ldr	r1, .L96+8
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r2, [r7, #196]
	ldr	r1, [r7, #192]
	mov	r3, r6
	and	r2, r2, #3
	str	r4, [fp, #-48]
	bfi	r2, r1, #2, #2
	strb	r2, [fp, #-48]
	ldr	r8, [fp, #-48]
	mov	r2, r5
	mov	r0, #148
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L96+12
	mov	r0, #3
	bl	dprint_vfmw
	str	r4, [fp, #-48]
	mov	r3, #0
	bfi	r3, r4, #0, #1
	strb	r3, [fp, #-48]
	mov	r2, r5
	mov	r3, r6
	ldr	r1, [fp, #-48]
	mov	r0, #152
	bl	MFDE_ConfigReg
	ldr	r7, [r7, #220]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #108
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L96+16
	mov	r0, #3
	bl	dprint_vfmw
	mov	r0, #32
	mov	r3, r6
	mov	r2, r5
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, r4
.L89:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L78:
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	mov	r0, r2
	str	r2, [r9, #240]
	bfi	r3, r2, #5, #1
	strb	r3, [fp, #-45]
	b	.L69
.L94:
	ldr	r1, .L96+20
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L80:
	mov	r0, #0
	movt	r0, 63683
	b	.L65
.L93:
	str	r0, [sp]
	mov	r3, r5
	ldr	r2, .L96+24
	ldr	r1, .L96+28
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L95:
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L68
	str	r3, [r8]
	b	.L67
.L70:
	mvn	r2, #0
	ldr	r1, .L96+32
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r2, [fp, #-56]
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r2]
	b	.L89
.L68:
	ldr	r1, .L96+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L89
.L97:
	.align	2
.L96:
	.word	.LC26
	.word	.LC21
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC19
	.word	.LANCHOR0+24
	.word	.LC18
	.word	.LC22
	.word	.LC20
	UNWIND(.fnend)
	.size	MP2HAL_V5R6C1_CfgReg, .-MP2HAL_V5R6C1_CfgReg
	.align	2
	.global	MP2HAL_V5R6C1_CfgDnMsg
	.type	MP2HAL_V5R6C1_CfgDnMsg, %function
MP2HAL_V5R6C1_CfgDnMsg:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	mov	r4, r0
	ldr	r0, [r1, #56]
	mov	r6, r1
	mov	r7, r3
	mov	r8, #0
	str	r8, [fp, #-48]
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L125
	ldrh	r2, [r4, #150]
	cmp	r2, #512
	bhi	.L126
	ldrh	r1, [r4, #146]
	cmp	r1, #512
	bhi	.L127
	ldrh	r3, [fp, #-46]
	sub	r1, r1, #1
	ldr	r0, [r4, #176]
	sub	r2, r2, #1
	bfi	r3, r1, #0, #9
	ldrh	r1, [fp, #-48]
	strh	r3, [fp, #-46]	@ movhi
	mov	ip, #0
	mov	r3, r3, lsr #8
	bfi	r1, r2, #0, #9
	bfi	r3, r0, #1, #1
	strh	r1, [fp, #-48]	@ movhi
	strb	r3, [fp, #-45]
	mov	r0, ip
	ldr	r3, [fp, #-48]
	mov	r1, ip
	str	r3, [r5]
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldrb	lr, [r4, #1]	@ zero_extendqisi2
	and	r3, r3, #7
	bfi	r3, r2, #3, #1
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	bfi	r3, lr, #4, #1
	strb	r3, [fp, #-45]
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	and	r2, r2, #3
	ldrb	lr, [r4, #4]	@ zero_extendqisi2
	bfi	ip, r3, #0, #1
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	strb	ip, [fp, #-48]
	bfi	r2, lr, #2, #1
	mov	ip, r0
	strb	r2, [fp, #-47]
	bfi	r0, r3, #0, #1
	strb	r0, [fp, #-46]
	ldr	r3, [fp, #-48]
	mov	r2, r1
	str	r3, [r5, #4]
	ldrb	r3, [r4, #12]	@ zero_extendqisi2
	ldrb	lr, [r4, #6]	@ zero_extendqisi2
	and	r3, r3, #15
	ldrb	r0, [r4, #15]	@ zero_extendqisi2
	bfi	r3, lr, #7, #1
	strb	r3, [fp, #-45]
	ldrb	r3, [r4, #14]	@ zero_extendqisi2
	bfi	r1, r0, #0, #4
	mov	r0, ip
	strb	r1, [fp, #-48]
	bfi	ip, r3, #0, #4
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	strb	ip, [fp, #-47]
	mov	r1, r2
	bfi	r2, r3, #0, #4
	strb	r2, [fp, #-46]
	ldr	ip, [fp, #-48]
	mov	r2, r0
	mov	r3, r0
	str	ip, [r5, #8]
	ldrb	lr, [r4, #11]	@ zero_extendqisi2
	ldrb	ip, [r4, #10]	@ zero_extendqisi2
	bfi	r0, lr, #0, #2
	strb	r0, [fp, #-48]
	bfi	r1, ip, #0, #1
	ldrb	r0, [r4, #9]	@ zero_extendqisi2
	strb	r1, [fp, #-47]
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	bfi	r2, r0, #0, #1
	strb	r2, [fp, #-46]
	bfi	r3, r1, #0, #1
	strb	r3, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r5, #12]
	ldr	r3, [r4, #180]
	bic	r3, r3, #15
	str	r3, [r5, #16]
	ldr	r3, [r4, #184]
	bic	r3, r3, #15
	str	r3, [r5, #20]
	ldr	r3, [r4, #200]
	bic	r3, r3, #15
	str	r3, [r5, #24]
	ldr	r3, [r4, #224]
	bic	r3, r3, #15
	str	r3, [r5, #28]
	ldr	r0, [r4, #152]
	str	r3, [fp, #-48]
	bl	MEM_Phy2Vir
	mov	r9, r0
	ldr	r0, [r4, #156]
	bl	MEM_Phy2Vir
	ldr	r2, [r4, #172]
	cmp	r2, #0
	mov	r10, r0
	beq	.L128
	ldr	lr, [r4, #164]
	mov	r0, r8
	ldr	r2, [r4, #160]
	mov	r1, r8
	ldr	ip, [r4, #156]
	cmp	r9, #0
	ldr	r3, [r4, #152]
	add	r8, ip, lr, lsr #3
	add	r3, r3, r2, lsr #3
	bic	lr, r8, #15
	bic	r2, r3, #15
	and	ip, r3, #15
	rsb	r3, lr, r2
	mov	r2, #0
	bfi	r0, r3, #0, #24
	str	r0, [r5, #32]
	ldr	r3, [r4, #160]
	ldr	r0, [r4, #168]
	and	r3, r3, #7
	add	r3, r3, ip, lsl #3
	bfi	r1, r0, #0, #24
	bfi	r2, r3, #0, #7
	str	r1, [fp, #-48]
	strb	r2, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r5, #36]
	beq	.L106
	ldr	r3, [r4, #160]
	mov	r0, #8
	ldr	r1, .L131
	add	ip, r9, r3, lsr #3
	ldrb	r2, [r9, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #160]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L131+4
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r9, r3
	ldrb	r2, [r9, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #152]
	mov	r0, #22
	ldr	r1, .L131+8
	add	r2, r2, r3
	bl	dprint_vfmw
.L106:
	mov	r3, #0
	and	r8, r8, #15
	mov	r2, r3
	bfi	r2, r3, #0, #24
	str	r2, [r5, #40]
	cmp	r10, r3
	ldr	r2, [r4, #164]
	ldr	r1, [r4, #172]
	and	r2, r2, #7
	add	r8, r2, r8, lsl #3
	add	r2, r1, #24
	bfi	r3, r2, #0, #24
	mov	r1, #0
	str	r3, [fp, #-48]
	bfi	r1, r8, #0, #7
	strb	r1, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r5, #44]
	beq	.L105
	ldr	r3, [r4, #164]
	mov	r0, #8
	ldr	r1, .L131+12
	add	ip, r10, r3, lsr #3
	ldrb	r2, [r10, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #172]
	ldr	r3, [r4, #164]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L131+16
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r10, r3
	ldrb	r2, [r10, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
.L105:
	add	r9, r5, #128
	add	r1, r4, #16
	mov	r8, #32
.L111:
	sub	r3, r1, #16
	mov	r2, r9
.L107:
	ldrb	r10, [r3, #80]	@ zero_extendqisi2
	add	r3, r3, #8
	ldrb	lr, [r3, #88]	@ zero_extendqisi2
	ldrb	ip, [r3, #104]	@ zero_extendqisi2
	ldrb	r0, [r3, #120]	@ zero_extendqisi2
	strb	r10, [fp, #-48]
	strb	lr, [fp, #-47]
	strb	ip, [fp, #-46]
	strb	r0, [fp, #-45]
	ldr	r0, [fp, #-48]
	str	r0, [r2, #-64]
	ldrb	r0, [r3, #56]	@ zero_extendqisi2
	ldrb	r10, [r3, #8]	@ zero_extendqisi2
	ldrb	lr, [r3, #24]	@ zero_extendqisi2
	ldrb	ip, [r3, #40]	@ zero_extendqisi2
	cmp	r1, r3
	strb	r10, [fp, #-48]
	strb	lr, [fp, #-47]
	strb	ip, [fp, #-46]
	strb	r0, [fp, #-45]
	ldr	r0, [fp, #-48]
	str	r0, [r2], #4
	bne	.L107
	add	r8, r8, #2
	add	r9, r9, #8
	cmp	r8, #48
	add	r1, r1, #1
	bne	.L111
	ldr	r3, [r6, #1148]
	bic	r3, r3, #15
	str	r3, [r5, #192]
	ldr	r8, [r6, #56]
	str	r3, [fp, #-48]
	bic	r8, r8, #15
	add	r8, r8, #256
	mov	r0, r8
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L129
	mov	r3, r7
	str	r8, [r5, #252]
	mov	r0, r4
	mov	r2, r8
	str	r8, [fp, #-48]
	bl	MP2HAL_V5R6C1_WriteSliceMsg
	ldr	r3, .L131+20
	ldr	r3, [r3]
	ands	r0, r3, #16
	bne	.L130
.L124:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L128:
	ldr	ip, [r4, #160]
	mov	r3, r2
	ldr	r1, [r4, #152]
	cmp	r9, #0
	str	r2, [r5, #32]
	ldr	r0, [r4, #168]
	add	r1, r1, ip, lsr #3
	ldr	r2, [r4, #160]
	and	r1, r1, #15
	add	r0, r0, #24
	bfi	r3, r0, #0, #24
	and	r2, r2, #7
	str	r3, [fp, #-48]
	add	r2, r2, r1, lsl #3
	mov	r3, r3, lsr #24
	bfi	r3, r2, #0, #7
	strb	r3, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r5, #36]
	beq	.L104
	ldr	r3, [r4, #160]
	mov	r0, #8
	ldr	r1, .L131+24
	add	ip, r9, r3, lsr #3
	ldrb	r2, [r9, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r2, [r4, #168]
	ldr	r3, [r4, #160]
	mov	r0, #9
	add	ip, r2, #7
	cmp	r2, #0
	ldr	r1, .L131+28
	mov	r3, r3, lsr #3
	movlt	r2, ip
	sub	r3, r3, #8
	add	r3, r3, r2, asr #3
	add	ip, r9, r3
	ldrb	r2, [r9, r3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	bl	dprint_vfmw
.L104:
	mov	r3, #0
	mov	r1, #0
	mov	r2, r3
	bfi	r1, r3, #0, #7
	bfi	r2, r3, #0, #24
	str	r2, [r5, #40]
	mov	r2, r3
	bfi	r2, r3, #0, #24
	str	r2, [fp, #-48]
	strb	r1, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r5, #44]
	b	.L105
.L130:
	ldr	ip, .L131+32
	mov	r0, #4
	ldr	r3, [r6, #56]
	mov	r4, #0
	ldr	r1, .L131+36
	mov	r6, r5
	ldr	r2, [ip]
	add	r2, r2, #1
	str	r2, [ip]
	bl	dprint_vfmw
.L110:
	ldr	ip, [r6, #12]
	mov	r2, r4
	ldr	r3, [r5, r4, asl #2]
	mov	r0, #4
	ldr	r1, .L131+40
	add	r4, r4, r0
	str	ip, [sp, #8]
	add	r6, r6, #16
	ldr	ip, [r6, #-8]
	str	ip, [sp, #4]
	ldr	ip, [r6, #-12]
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r4, #64
	bne	.L110
	ldr	r1, .L131+44
	mov	r0, #4
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L127:
	mov	r0, r8
	ldr	r3, .L131+48
	ldr	r2, .L131+52
	ldr	r1, .L131+56
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L124
.L126:
	mov	r0, r8
	ldr	r3, .L131+60
	ldr	r2, .L131+52
	ldr	r1, .L131+56
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L124
.L129:
	ldr	r1, .L131+64
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L124
.L125:
	ldr	r3, .L131+68
	ldr	r2, .L131+52
	ldr	r1, .L131+56
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L124
.L132:
	.align	2
.L131:
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	g_PrintEnable
	.word	.LC11
	.word	.LC12
	.word	.LANCHOR1
	.word	.LC29
	.word	.LC30
	.word	.LC31
	.word	.LC10
	.word	.LANCHOR0+48
	.word	.LC9
	.word	.LC8
	.word	.LC28
	.word	.LC27
	UNWIND(.fnend)
	.size	MP2HAL_V5R6C1_CfgDnMsg, .-MP2HAL_V5R6C1_CfgDnMsg
	.align	2
	.global	MP2HAL_V5R6C1_StartDec
	.type	MP2HAL_V5R6C1_StartDec, %function
MP2HAL_V5R6C1_StartDec:
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
	ldr	r5, .L147
	cmp	r1, #0
	movw	r4, #1228
	mov	r6, r0
	mla	r4, r4, r1, r5
	bgt	.L144
	bne	.L142
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L145
.L139:
	ldr	lr, .L147+4
	sub	r3, fp, #32
	str	r2, [sp]
	mov	r1, r4
	mov	r2, #0
	mov	r0, r6
	ldr	ip, [lr]
	add	ip, ip, #1
	str	ip, [lr]
	bl	MP2HAL_V5R6C1_CfgReg
	subs	r5, r0, #0
	bne	.L146
	mov	r1, r4
	mov	r0, r6
	ldr	r3, [fp, #-32]
	mov	r2, r5
	bl	MP2HAL_V5R6C1_CfgDnMsg
.L135:
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L145:
	mov	r0, #0
	str	r2, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L140
	str	r3, [r5]
	ldr	r2, [fp, #-40]
	b	.L139
.L144:
	mov	r3, r1
	mov	r0, #0
	ldr	r2, .L147+8
	mvn	r5, #0
	str	r0, [sp]
	ldr	r1, .L147+12
	bl	dprint_vfmw
	b	.L135
.L146:
	ldr	r1, .L147+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L135
.L142:
	ldr	r1, .L147+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L135
.L140:
	ldr	r1, .L147+24
	mvn	r5, #0
	bl	dprint_vfmw
	b	.L135
.L148:
	.align	2
.L147:
	.word	g_HwMem
	.word	.LANCHOR2
	.word	.LANCHOR0+72
	.word	.LC18
	.word	.LC33
	.word	.LC32
	.word	.LC20
	UNWIND(.fnend)
	.size	MP2HAL_V5R6C1_StartDec, .-MP2HAL_V5R6C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14744, %object
	.size	__func__.14744, 24
__func__.14744:
	.ascii	"MP2HAL_V5R6C1_MakeDnMsg\000"
	.type	__func__.14783, %object
	.size	__func__.14783, 21
__func__.14783:
	.ascii	"MP2HAL_V5R6C1_CfgReg\000"
	.space	3
	.type	__func__.14806, %object
	.size	__func__.14806, 23
__func__.14806:
	.ascii	"MP2HAL_V5R6C1_CfgDnMsg\000"
	.space	1
	.type	__func__.14697, %object
	.size	__func__.14697, 23
__func__.14697:
	.ascii	"MP2HAL_V5R6C1_StartDec\000"
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	FrameNum, %object
	.size	FrameNum, 4
FrameNum:
	.word	-1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"D0 = %#x \012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"D1 = %#x \012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"D2 = %#x \012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"D3 = %#x \012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"D4 = %#x \012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"D5 = %#x \012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"D6 = %#x \012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"D7 = %#x \012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC9:
	ASCII(.ascii	"%s: %s\012\000" )
.LC10:
	ASCII(.ascii	"picture height out of range\000" )
.LC11:
	ASCII(.ascii	"Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0" )
	ASCII(.ascii	"x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0" )
	ASCII(.ascii	"x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"1p Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"1p Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"1p last phy addr = 0x%x\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"2p Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"2p Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC19:
	ASCII(.ascii	"VdhId is wrong! MP2HAL_V200R003_CfgReg\012\000" )
.LC20:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC21:
	ASCII(.ascii	"MPEG2  VREG_V5R6C1_BASIC_CFG1= 0x%x\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"stream_base_addr = %#x\012\000" )
.LC23:
	ASCII(.ascii	"MPEG2  VREG_V5R6C1_UVOFFSET_1D= 0x%x\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"MPEG2  VREG_V5R6C1_REF_PIC_TYPE= 0x%x\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"HEAD_INF_OFFSET = 0x%x\012\000" )
.LC26:
	ASCII(.ascii	"MPEG2  VREG_V5R6C1_BASIC_CFG0= 0x%x\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"can not map down msg virtual address!\000" )
	.space	2
.LC28:
	ASCII(.ascii	"Map SlcDnMsgPhyAddr to SlcDnMsgVirAddr is NULL \012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC29:
	ASCII(.ascii	"\012*****No.%2d Down Msg (phy addr: %#8x) *****\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC30:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"\012***** Down Msg print finished *****\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"VdhId is wrong! MP2HAL_V200R003_StartDec\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"MP2HAL_V200R003_CfgReg ERROR!\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	num.14817, %object
	.size	num.14817, 4
num.14817:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
