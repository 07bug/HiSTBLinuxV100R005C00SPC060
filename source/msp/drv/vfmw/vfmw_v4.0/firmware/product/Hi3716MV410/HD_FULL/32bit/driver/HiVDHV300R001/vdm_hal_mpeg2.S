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
	.global	MP2HAL_V300R001_WriteSliceMsg
	.type	MP2HAL_V300R001_WriteSliceMsg, %function
MP2HAL_V300R001_WriteSliceMsg:
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
	str	r0, [fp, #-76]
	ldr	r0, [r0, #284]
	mov	r4, r2
	str	r3, [fp, #-64]
	mov	r6, #0
	cmp	r0, #0
	add	r3, lr, #252
	str	r1, [fp, #-56]
	ldr	r7, [ip, #252]
	str	r3, [fp, #-60]
	bne	.L26
.L2:
	cmp	r7, #0
	ble	.L23
	ldr	r8, .L27
	mov	r3, r0, asl #5
	str	r3, [fp, #-68]
	add	r3, r3, r4
	mov	r4, #0
	str	r3, [fp, #-72]
.L18:
	ldr	r3, [fp, #-60]
	cmp	r4, #0
	mov	r5, #44
	mla	r5, r5, r4, r3
	ble	.L7
	ldr	r2, [r5, #32]
	ldr	r3, [r5, #-12]
	cmp	r2, r3
	bls	.L8
.L7:
	ldr	r10, [r5]
	mov	r9, #0
	ldr	r3, [r5, #16]
	mov	r1, r9
	and	r0, r10, #15
	ldr	ip, [r5, #8]
	ldr	lr, [fp, #-68]
	mov	r2, #0
	add	r3, r3, r0, lsl #3
	bfi	r1, ip, #0, #24
	bfi	r2, r3, #0, #7
	str	r1, [fp, #-48]
	strb	r2, [fp, #-45]
	add	r6, lr, r4, lsl #3
	ldr	r2, [fp, #-48]
	mov	r0, #4
	ldr	r3, [fp, #-56]
	bic	r10, r10, #15
	ldr	r1, .L27+4
	add	r4, r4, #1
	str	r2, [r3, r6, asl #2]
	add	r6, r6, #1
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r1, [fp, #-64]
	ldr	r2, [fp, #-56]
	mov	r3, r9
	rsb	r10, r1, r10
	mov	r0, #4
	bfi	r3, r10, #0, #24
	ldr	r1, .L27+8
	str	r3, [r2, r6, asl #2]
	mov	r6, r6, asl #2
	mov	r2, r3
	str	r3, [fp, #-48]
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r10, [r5, #4]
	ldr	r3, [r5, #20]
	mov	r1, r9
	and	ip, r10, #15
	ldr	r0, [r5, #12]
	mov	r2, #0
	add	r3, r3, ip, lsl #3
	bfi	r1, r0, #0, #24
	bfi	r2, r3, #0, #7
	str	r1, [fp, #-48]
	strb	r2, [fp, #-45]
	add	r3, r6, #4
	ldr	ip, [fp, #-56]
	mov	r0, #4
	ldr	r2, [fp, #-48]
	ldr	r1, .L27+12
	str	r2, [ip, r3]
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r3, [r5, #4]
	ldr	r1, .L27+16
	mov	r0, #4
	cmp	r3, r9
	bicne	r10, r10, #15
	streq	r3, [fp, #-48]
	ldrne	r3, [fp, #-64]
	rsbne	r10, r3, r10
	add	r3, r6, #8
	bfine	r9, r10, #0, #24
	ldr	r10, [fp, #-56]
	strne	r9, [fp, #-48]
	mov	r9, #0
	ldr	r2, [fp, #-48]
	str	r2, [r10, r3]
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r3, [r5, #40]
	ldr	r2, [r5, #36]
	add	ip, r6, #12
	and	r3, r3, #63
	str	r9, [fp, #-48]
	bfi	r3, r2, #6, #1
	strb	r3, [fp, #-48]
	ldr	r2, [fp, #-48]
	mov	r3, ip
	ldr	r1, .L27+20
	mov	r0, #4
	str	r2, [r10, r3]
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r1, [r5, #32]
	add	r3, r6, #16
	mov	r2, r9
	mov	r0, #4
	bfi	r2, r1, #0, #20
	ldr	r1, .L27+24
	str	r2, [fp, #-48]
	str	r2, [r10, r3]
	ldr	r3, [r8, #68]
	blx	r3
	cmp	r7, r4
	ble	.L11
	mov	r3, #44
	ldr	r0, [fp, #-60]
	mul	r3, r3, r4
	ldr	r2, [r5, #32]
	add	r1, r0, r3
	ldr	r1, [r1, #32]
	cmp	r2, r1
	bcc	.L11
	sub	r3, r3, #44
	add	r3, r0, r3
	b	.L12
.L14:
	ldr	r1, [r3, #76]
	cmp	r1, r2
	bhi	.L16
.L12:
	add	r4, r4, #1
	add	r3, r3, #44
	cmp	r7, r4
	bne	.L14
.L20:
	ldr	r3, [fp, #-76]
	mov	r9, #0
	mov	r5, r9
	ldrh	r2, [r3, #152]
	ldrh	r3, [r3, #148]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L17:
	ldr	r10, [fp, #-56]
	add	ip, r6, #20
	add	r6, r6, #24
	ldr	r1, .L27+28
	mov	r2, #0
	mov	r0, #4
	bfi	r2, r3, #0, #20
	str	r2, [fp, #-48]
	str	r2, [r10, ip]
	sub	r4, r4, #1
	ldr	r3, [r8, #68]
	blx	r3
	str	r9, [r10, r6]
	mov	r2, r5
	ldr	r1, .L27+32
	mov	r0, #4
	ldr	r3, [r8, #68]
	str	r5, [fp, #-48]
	blx	r3
.L8:
	add	r4, r4, #1
	cmp	r7, r4
	bgt	.L18
.L23:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L11:
	cmp	r7, r4
	beq	.L20
.L16:
	ldr	r2, [fp, #-72]
	mov	r3, #44
	add	r5, r2, r4, lsl #5
	ldr	r2, [fp, #-60]
	mov	r9, r5
	mla	r3, r3, r4, r2
	ldr	r3, [r3, #32]
	sub	r3, r3, #1
	b	.L17
.L26:
	ldr	r8, [lr, #252]
	mov	r0, #1
	ldr	r3, [lr, #268]
	mov	r2, #0
	and	r1, r8, #15
	str	r0, [fp, #-48]
	ldr	r5, .L27
	mov	r0, #4
	add	r3, r3, r1, lsl #3
	ldr	r10, [fp, #-56]
	bfi	r2, r3, #0, #7
	strb	r2, [fp, #-45]
	ldr	r2, [fp, #-48]
	mov	r9, lr
	ldr	r1, .L27+4
	str	r2, [r10]
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r2, [fp, #-64]
	bic	r3, r8, #15
	ldr	r1, .L27+8
	rsb	r3, r2, r3
	mov	r0, #4
	mov	r2, r6
	bfi	r2, r3, #0, #24
	str	r2, [r10, #4]
	str	r2, [fp, #-48]
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r8, [r9, #256]
	ldr	r3, [r9, #272]
	mov	r2, #0
	and	ip, r8, #15
	str	r6, [fp, #-48]
	ldr	r1, .L27+12
	mov	r0, #4
	add	r3, r3, ip, lsl #3
	bfi	r2, r3, #0, #7
	strb	r2, [fp, #-45]
	ldr	r2, [fp, #-48]
	str	r2, [r10, #8]
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r3, [r9, #256]
	ldr	r1, .L27+16
	mov	r0, #4
	cmp	r3, r6
	bicne	r3, r8, #15
	streq	r3, [fp, #-48]
	ldrne	r2, [fp, #-64]
	ldr	r8, [fp, #-56]
	rsbne	r3, r2, r3
	bfine	r6, r3, #0, #24
	strne	r6, [fp, #-48]
	ldr	r2, [fp, #-48]
	mov	r6, #0
	str	r2, [r8, #12]
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r9, [fp, #-76]
	str	r6, [fp, #-48]
	mov	r0, #4
	ldr	r1, .L27+20
	ldr	r3, [r9, #292]
	ldr	r2, [r9, #288]
	and	r3, r3, #63
	bfi	r3, r2, #6, #1
	strb	r3, [fp, #-48]
	ldr	r2, [fp, #-48]
	str	r2, [r8, #16]
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r1, .L27+24
	mov	r2, r6
	mov	r0, #4
	bfi	r2, r6, #0, #20
	str	r2, [r8, #20]
	str	r2, [fp, #-48]
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r3, [r9, #284]
	mov	r2, r6
	ldr	r1, .L27+28
	sub	r3, r3, #1
	mov	r0, #4
	bfi	r2, r3, #0, #20
	str	r2, [r8, #24]
	str	r2, [fp, #-48]
	ldr	r3, [r5, #68]
	blx	r3
	add	r3, r4, #32
	mov	r0, #1
	str	r3, [r8, #28]
	b	.L2
.L28:
	.align	2
.L27:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	UNWIND(.fnend)
	.size	MP2HAL_V300R001_WriteSliceMsg, .-MP2HAL_V300R001_WriteSliceMsg
	.align	2
	.global	MP2HAL_V300R001_CfgReg
	.type	MP2HAL_V300R001_CfgReg, %function
MP2HAL_V300R001_CfgReg:
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
	cmp	r2, #1
	mov	r5, r0
	mov	r0, #0
	str	r0, [fp, #-48]
	bhi	.L70
	cmp	r2, #0
	bgt	.L71
	ldr	r0, [r1]
	cmp	r0, #0
	beq	.L72
.L34:
	movw	r7, #1208
	ldr	r4, .L74
	mul	r7, r7, r2
	mvn	lr, #0
	mov	ip, #0
	mov	r10, #0
	bfi	r10, ip, #5, #1
	mov	r9, #3
	add	r8, r5, #45056
	ldr	r0, [r4, r7]
	str	lr, [r0, #32]
	ldrh	r0, [r5, #148]
	ldrh	r6, [r5, #152]
	mul	r6, r0, r6
	ldr	r0, [fp, #-48]
	add	r6, r6, lr
	bfi	r0, r6, #0, #20
	str	r0, [fp, #-48]
	mov	r6, r0, lsr #24
	ubfx	r0, r0, #16, #8
	and	r6, r6, #62
	orr	r0, r0, #64
	orr	r6, r6, #65
	bfc	r0, #7, #1
	bfc	r6, #1, #1
	strb	r0, [fp, #-46]
	strb	r6, [fp, #-45]
	ldr	r6, [fp, #-48]
	ldr	r0, [r4, r7]
	str	ip, [fp, #-48]
	strb	r10, [fp, #-47]
	str	r6, [r0, #8]
	ldr	r10, [r5, #232]
	ldrh	r6, [fp, #-46]
	strb	r9, [fp, #-48]
	ldrh	r0, [fp, #-48]
	bfi	r6, r9, #0, #12
	mov	r10, r10, lsr #6
	ldr	r9, [r8, #260]
	bfi	r0, r10, #4, #9
	mov	r10, r6, lsr #8
	strh	r0, [fp, #-48]	@ movhi
	ubfx	r0, r0, #8, #8
	orr	r0, r0, #64
	and	r10, r10, #79
	strh	r6, [fp, #-46]	@ movhi
	bfi	r0, ip, #7, #1
	bfi	r10, r9, #6, #1
	strb	r0, [fp, #-47]
	strb	r10, [fp, #-45]
	ldr	r6, [fp, #-48]
	ldr	r0, [r4, r7]
	str	ip, [fp, #-48]
	str	r6, [r0, #12]
	ldr	r6, [r4, r7]
	ldr	r0, [r1, #48]
	bic	r0, r0, #15
	str	r0, [r6, #16]
	ldr	r0, [r4, r7]
	ldr	r1, [r1, #32]
	bic	r1, r1, #15
	str	r1, [r0, #20]
	ldr	r6, [r8, #252]
	cmp	r6, ip
	beq	.L42
	mov	r1, r5
.L43:
	ldr	r0, [r1, #252]
	cmp	r0, #0
	beq	.L38
	ldr	r7, [r1, #260]
	bic	r0, r0, #15
	cmp	r7, #0
	ble	.L38
	cmp	lr, r0
	movcs	lr, r0
.L38:
	ldr	r0, [r1, #256]
	cmp	r0, #0
	beq	.L36
	ldr	r7, [r1, #264]
	bic	r0, r0, #15
	cmp	r7, #0
	ble	.L36
	cmp	lr, r0
	movcs	lr, r0
.L36:
	add	ip, ip, #1
	add	r1, r1, #44
	cmp	ip, r6
	bne	.L43
	cmn	lr, #1
	beq	.L42
	movw	r6, #1208
	str	lr, [r3]
	mul	r6, r6, r2
	movw	r0, #49156
	movt	r0, 63683
	str	r2, [fp, #-56]
	ldr	r3, [r4, r6]
	str	lr, [r3, #24]
	ldrh	r3, [r5, #152]
	cmp	r3, #120
	movhi	r7, #0
	movls	r7, #65536
	bl	MEM_ReadPhyWord
	ldr	r3, .L74+4
	ldr	r3, [r3]
	orr	r1, r0, r7
	add	r0, r3, #4
	bl	MEM_WritePhyWord
	ldr	r1, [r4, r6]
	movw	r3, #3075
	ldr	r2, [fp, #-56]
	movt	r3, 48
	str	r3, [r1, #60]
	ldr	r1, [r4, r6]
	str	r3, [r1, #64]
	ldr	r1, [r4, r6]
	str	r3, [r1, #68]
	ldr	r1, [r4, r6]
	str	r3, [r1, #72]
	ldr	r1, [r4, r6]
	str	r3, [r1, #76]
	ldr	r1, [r4, r6]
	str	r3, [r1, #80]
	ldr	r1, [r4, r6]
	str	r3, [r1, #84]
	ldr	r1, [r4, r6]
	ldr	r3, [r5, #200]
	bic	r3, r3, #15
	str	r3, [r1, #96]
	ldr	r0, [r4, r6]
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	ldr	ip, [r5, #232]
	sub	r3, r3, #1
	ldrh	r1, [r5, #148]
	cmp	r3, #1
	str	ip, [r0, #100]
	ldrh	r0, [r5, #152]
	movls	r3, #2
	movhi	r3, #1
	cmp	r0, #0
	mul	r1, r3, r1
	ble	.L73
	mov	r3, r0, asl #4
	cmp	r3, #2048
	movle	lr, #16
	bgt	.L48
.L41:
	mov	r3, r1, asl #4
	add	ip, r1, #1
	add	r3, r3, #31
	movw	r1, #1208
	ldr	r0, [r5, #232]
	mov	r6, #0
	mov	r3, r3, lsr #5
	str	r6, [fp, #-48]
	mul	r1, r1, r2
	mov	r2, ip, lsr #1
	mul	r3, r3, lr
	mov	ip, #0
	mul	r2, r0, r2
	bfi	ip, r6, #0, #1
	ldr	r0, [r4, r1]
	add	r2, r2, r3, lsl #4
	mov	r3, r3, asl #5
	mov	r2, r2, asl #1
	str	r2, [r0, #104]
	ldr	r0, [r5, #208]
	mov	r2, r3
	ldr	lr, [r5, #204]
	and	r0, r0, #3
	bfi	r0, lr, #2, #2
	strb	r0, [fp, #-48]
	ldr	lr, [r4, r1]
	mov	r0, #3
	ldr	r5, [fp, #-48]
	str	r6, [fp, #-48]
	strb	ip, [fp, #-48]
	str	r5, [lr, #148]
	ldr	r5, [fp, #-48]
	ldr	lr, [r4, r1]
	ldr	ip, .L74+8
	str	r5, [lr, #152]
	ldr	lr, [r4, r1]
	ldr	r1, .L74+12
	str	r3, [lr, #108]
	ldr	r3, [ip, #68]
	blx	r3
	mov	r0, r6
.L66:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L73:
	mov	r3, r0, asl #4
.L48:
	sub	r0, r3, #2048
	sub	r0, r0, #1
	cmp	r0, #2048
	movcc	lr, #32
	bcc	.L41
	sub	r0, r3, #4096
	sub	r0, r0, #1
	cmp	r0, #2048
	movcc	lr, #48
	bcc	.L41
	sub	r3, r3, #6144
	sub	r3, r3, #1
	cmp	r3, #2048
	movcs	lr, #16
	movcc	lr, #64
	b	.L41
.L72:
	movt	r0, 63683
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	str	r1, [fp, #-56]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L35
	ldr	r1, [fp, #-56]
	ldr	r2, [fp, #-60]
	ldr	r3, [fp, #-64]
	str	ip, [r1]
	b	.L34
.L71:
	ldr	r1, .L74+8
	mov	r3, r2
	str	r0, [sp]
	ldr	r2, .L74+16
	ldr	r4, [r1, #68]
	ldr	r1, .L74+20
	blx	r4
	mvn	r0, #0
	b	.L66
.L70:
	ldr	r3, .L74+8
	ldr	r1, .L74+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L66
.L42:
	ldr	ip, .L74+8
	mvn	r2, #0
	ldr	r1, .L74+28
	mov	r0, #0
	str	r3, [fp, #-56]
	ldr	r4, [ip, #68]
	blx	r4
	ldr	r3, [fp, #-56]
	mov	r2, #0
	mvn	r0, #0
	str	r2, [r3]
	b	.L66
.L35:
	ldr	r3, .L74+8
	ldr	r1, .L74+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L66
.L75:
	.align	2
.L74:
	.word	g_HwMem
	.word	s_RegPhyBaseAddr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC12
	.word	.LANCHOR0
	.word	.LC9
	.word	.LC8
	.word	.LC11
	.word	.LC10
	UNWIND(.fnend)
	.size	MP2HAL_V300R001_CfgReg, .-MP2HAL_V300R001_CfgReg
	.align	2
	.global	MP2HAL_V300R001_CfgDnMsg
	.type	MP2HAL_V300R001_CfgDnMsg, %function
MP2HAL_V300R001_CfgDnMsg:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	mov	r4, r0
	ldr	r0, [r1, #48]
	mov	r7, r1
	mov	r9, r3
	mov	r10, #0
	str	r10, [fp, #-48]
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	ldreq	r1, .L109
	ldreq	r3, .L109+4
	beq	.L103
	ldrh	r2, [r4, #152]
	cmp	r2, #512
	bhi	.L104
	ldrh	r1, [r4, #148]
	cmp	r1, #512
	bhi	.L105
	ldrh	r3, [fp, #-46]
	sub	r1, r1, #1
	ldr	r0, [r4, #180]
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
	ldr	r3, [r4, #192]
	bic	r3, r3, #15
	str	r3, [r5, #16]
	ldr	r3, [r4, #196]
	bic	r3, r3, #15
	str	r3, [r5, #20]
	ldr	r3, [r4, #224]
	bic	r3, r3, #15
	str	r3, [r5, #24]
	ldr	r3, [r4, #240]
	bic	r3, r3, #15
	str	r3, [r5, #28]
	ldr	r0, [r4, #156]
	str	r3, [fp, #-48]
	bl	MEM_Phy2Vir
	mov	r6, r0
	ldr	r0, [r4, #160]
	bl	MEM_Phy2Vir
	ldr	r2, [r4, #176]
	cmp	r2, #0
	mov	r8, r0
	beq	.L106
	ldr	ip, [r4, #168]
	mov	r1, r10
	ldr	r2, [r4, #164]
	cmp	r6, #0
	ldr	r0, [r4, #160]
	ldr	r3, [r4, #156]
	add	r0, r0, ip, lsr #3
	str	r0, [fp, #-56]
	add	r3, r3, r2, lsr #3
	bic	r0, r0, #15
	bic	r2, r3, #15
	and	ip, r3, #15
	rsb	r3, r0, r2
	mov	r2, #0
	bfi	r10, r3, #0, #24
	str	r10, [r5, #32]
	ldr	r3, [r4, #164]
	ldr	r0, [r4, #172]
	and	r3, r3, #7
	add	r3, r3, ip, lsl #3
	bfi	r1, r0, #0, #24
	bfi	r2, r3, #0, #7
	str	r1, [fp, #-48]
	strb	r2, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r5, #36]
	beq	.L84
	ldr	r3, [r4, #164]
	mov	r0, #8
	ldr	r10, .L109
	ldr	r1, .L109+8
	add	ip, r6, r3, lsr #3
	ldrb	r2, [r6, r3, lsr #3]	@ zero_extendqisi2
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
	ldr	ip, [r10, #68]
	blx	ip
	ldr	r2, [r4, #172]
	ldr	r3, [r4, #164]
	mov	r0, #9
	add	r1, r2, #7
	cmp	r2, #0
	mov	r3, r3, lsr #3
	movlt	r2, r1
	sub	r3, r3, #8
	ldr	r1, .L109+12
	add	r3, r3, r2, asr #3
	add	ip, r6, r3
	ldrb	r2, [r6, r3]	@ zero_extendqisi2
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
	ldr	ip, [r10, #68]
	blx	ip
	ldr	r1, [r4, #172]
	ldr	r2, [r4, #156]
	mov	r0, #22
	ldr	r3, [r10, #68]
	add	r2, r1, r2
	ldr	r1, .L109+16
	blx	r3
.L84:
	ldr	r2, [fp, #-56]
	mov	r3, #0
	cmp	r8, r3
	and	r1, r2, #15
	mov	r2, r3
	bfi	r2, r3, #0, #24
	str	r2, [r5, #40]
	ldr	r2, [r4, #168]
	ldr	r0, [r4, #176]
	and	r2, r2, #7
	add	r2, r2, r1, lsl #3
	add	r1, r0, #24
	bfi	r3, r1, #0, #24
	mov	r0, #0
	str	r3, [fp, #-48]
	bfi	r0, r2, #0, #7
	strb	r0, [fp, #-45]
	ldr	r3, [fp, #-48]
	str	r3, [r5, #44]
	beq	.L83
	ldr	r3, [r4, #168]
	mov	r0, #8
	ldr	r6, .L109
	ldr	r1, .L109+20
	add	ip, r8, r3, lsr #3
	ldrb	r2, [r8, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	ldr	r10, [r6, #68]
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	blx	r10
	ldr	r2, [r4, #176]
	ldr	r3, [r4, #168]
	mov	r0, #9
	add	r1, r2, #7
	cmp	r2, #0
	ldr	r6, [r6, #68]
	mov	r3, r3, lsr #3
	movlt	r2, r1
	sub	r3, r3, #8
	ldr	r1, .L109+24
	add	r3, r3, r2, asr #3
	add	ip, r8, r3
	ldrb	r2, [r8, r3]	@ zero_extendqisi2
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
	blx	r6
.L83:
	add	r8, r5, #128
	add	r1, r4, #16
	mov	r6, #32
.L89:
	sub	r3, r1, #16
	mov	r2, r8
.L85:
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
	bne	.L85
	add	r6, r6, #2
	add	r8, r8, #8
	cmp	r6, #48
	add	r1, r1, #1
	bne	.L89
	ldr	r3, [r7, #1140]
	bic	r3, r3, #15
	str	r3, [r5, #192]
	ldr	r6, [r7, #48]
	str	r3, [fp, #-48]
	bic	r6, r6, #15
	add	r6, r6, #256
	mov	r0, r6
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L107
	mov	r3, r9
	str	r6, [r5, #252]
	mov	r0, r4
	mov	r2, r6
	str	r6, [fp, #-48]
	bl	MP2HAL_V300R001_WriteSliceMsg
	ldr	r3, .L109+28
	ldr	r3, [r3]
	ands	r0, r3, #16
	bne	.L108
.L102:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L106:
	ldr	ip, [r4, #164]
	mov	r3, r2
	ldr	r1, [r4, #156]
	cmp	r6, #0
	str	r2, [r5, #32]
	ldr	r0, [r4, #172]
	add	r1, r1, ip, lsr #3
	ldr	r2, [r4, #164]
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
	beq	.L82
	ldr	r3, [r4, #164]
	mov	r0, #8
	ldr	r8, .L109
	ldr	r1, .L109+32
	add	ip, r6, r3, lsr #3
	ldrb	r2, [r6, r3, lsr #3]	@ zero_extendqisi2
	ldrb	lr, [ip, #7]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	str	lr, [sp, #20]
	ldrb	lr, [ip, #6]	@ zero_extendqisi2
	ldr	r10, [r8, #68]
	str	lr, [sp, #16]
	ldrb	lr, [ip, #5]	@ zero_extendqisi2
	str	lr, [sp, #12]
	ldrb	lr, [ip, #4]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	str	lr, [sp, #4]
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	str	ip, [sp]
	blx	r10
	ldr	r2, [r4, #172]
	ldr	r3, [r4, #164]
	mov	r0, #9
	add	r1, r2, #7
	cmp	r2, #0
	ldr	r8, [r8, #68]
	mov	r3, r3, lsr #3
	movlt	r2, r1
	sub	r3, r3, #8
	ldr	r1, .L109+36
	add	r3, r3, r2, asr #3
	add	ip, r6, r3
	ldrb	r2, [r6, r3]	@ zero_extendqisi2
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
	blx	r8
.L82:
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
	b	.L83
.L108:
	ldr	r1, .L109+40
	mov	r0, #4
	ldr	r8, .L109
	mov	r6, r5
	ldr	r3, [r7, #48]
	ldr	r2, [r1]
	ldr	r4, [r8, #68]
	add	r2, r2, #1
	str	r2, [r1]
	ldr	r1, .L109+44
	blx	r4
	mov	r4, #0
.L88:
	ldr	r1, [r6, #12]
	mov	r2, r4
	ldr	r3, [r5, r4, asl #2]
	mov	r0, #4
	ldr	r7, [r8, #68]
	add	r4, r4, r0
	str	r1, [sp, #8]
	add	r6, r6, #16
	ldr	ip, [r6, #-8]
	ldr	r1, .L109+48
	ldr	r9, .L109
	str	ip, [sp, #4]
	ldr	ip, [r6, #-12]
	str	ip, [sp]
	blx	r7
	cmp	r4, #64
	bne	.L88
	ldr	r3, [r9, #68]
	mov	r0, #4
	ldr	r1, .L109+52
	blx	r3
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L104:
	ldr	r1, .L109
	mov	r0, r10
	ldr	r3, .L109+56
.L103:
	ldr	r4, [r1, #68]
	ldr	r2, .L109+60
	ldr	r1, .L109+64
	blx	r4
	mvn	r0, #0
	b	.L102
.L105:
	ldr	r1, .L109
	mov	r0, r10
	ldr	r3, .L109+68
	b	.L103
.L107:
	ldr	r3, .L109
	ldr	r1, .L109+72
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L102
.L110:
	.align	2
.L109:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LC19
	.word	.LC20
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	g_PrintEnable
	.word	.LC17
	.word	.LC18
	.word	.LANCHOR1
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC15
	.word	.LANCHOR0+24
	.word	.LC14
	.word	.LC16
	.word	.LC24
	UNWIND(.fnend)
	.size	MP2HAL_V300R001_CfgDnMsg, .-MP2HAL_V300R001_CfgDnMsg
	.align	2
	.global	MP2HAL_V300R001_StartDec
	.type	MP2HAL_V300R001_StartDec, %function
MP2HAL_V300R001_StartDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	cmp	r1, #1
	mov	r4, r1
	mov	r7, r0
	bhi	.L123
	cmp	r1, #0
	bgt	.L124
	movw	r5, #1208
	ldr	r6, .L128
	mul	r5, r5, r1
	add	r8, r5, r6
	ldr	r3, [r5, r6]
	cmp	r3, #0
	beq	.L125
.L116:
	ldr	lr, .L128+4
	sub	r3, fp, #40
	mov	r2, r4
	mov	r1, r8
	mov	r0, r7
	ldr	ip, [lr]
	add	ip, ip, #1
	str	ip, [lr]
	bl	MP2HAL_V300R001_CfgReg
	cmp	r0, #0
	bne	.L126
	mov	r2, r4
	mov	r1, r8
	mov	r0, r7
	ldr	r3, [fp, #-40]
	bl	MP2HAL_V300R001_CfgDnMsg
	cmp	r0, #0
	bne	.L127
.L114:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L125:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L117
	str	r3, [r5, r6]
	b	.L116
.L124:
	ldr	r1, .L128+8
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L128+12
	ldr	r4, [r1, #68]
	ldr	r1, .L128+16
	blx	r4
	mvn	r0, #0
	b	.L114
.L126:
	ldr	r3, .L128+8
	mov	r0, #1
	ldr	r1, .L128+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L114
.L123:
	ldr	r3, .L128+8
	mov	r0, #0
	ldr	r1, .L128+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L114
.L127:
	ldr	r3, .L128+8
	mov	r0, #1
	ldr	r1, .L128+28
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L114
.L117:
	ldr	r3, .L128+8
	ldr	r1, .L128+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L114
.L129:
	.align	2
.L128:
	.word	g_HwMem
	.word	.LANCHOR2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+52
	.word	.LC9
	.word	.LC29
	.word	.LC28
	.word	.LC30
	.word	.LC10
	UNWIND(.fnend)
	.size	MP2HAL_V300R001_StartDec, .-MP2HAL_V300R001_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13722, %object
	.size	__func__.13722, 23
__func__.13722:
	.ascii	"MP2HAL_V300R001_CfgReg\000"
	.space	1
	.type	__func__.13745, %object
	.size	__func__.13745, 25
__func__.13745:
	.ascii	"MP2HAL_V300R001_CfgDnMsg\000"
	.space	3
	.type	__func__.13676, %object
	.size	__func__.13676, 25
__func__.13676:
	.ascii	"MP2HAL_V300R001_StartDec\000"
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
	ASCII(.ascii	"VdhId is wrong! MP2HAL_V200R003_CfgReg\012\000" )
.LC9:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC10:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC11:
	ASCII(.ascii	"stream_base_addr = %#x\012\000" )
.LC12:
	ASCII(.ascii	"HEAD_INF_OFFSET = 0x%x\012\000" )
.LC13:
	ASCII(.ascii	"can not map down msg virtual address!\000" )
	.space	2
.LC14:
	ASCII(.ascii	"%s: %s\012\000" )
.LC15:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC16:
	ASCII(.ascii	"picture height out of range\000" )
.LC17:
	ASCII(.ascii	"Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0" )
	ASCII(.ascii	"x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02x 0" )
	ASCII(.ascii	"x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"1p Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"1p Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"1p last phy addr = 0x%x\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"2p Stream Head (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"2p Stream Tail (8bytes): 0x%02x 0x%02x 0x%02x 0x%02" )
	ASCII(.ascii	"x 0x%02x 0x%02x 0x%02x 0x%02x\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"Map SlcDnMsgPhyAddr to SlcDnMsgVirAddr is NULL \012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC25:
	ASCII(.ascii	"\012*****No.%2d Down Msg (phy addr: %#8x) *****\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC26:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"\012***** Down Msg print finished *****\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"VdhId is wrong! MP2HAL_V200R003_StartDec\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"MP2HAL_V300R001_CfgReg ERROR!\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"MP2HAL_V300R001_CfgDnMsg ERROR!\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	num.13756, %object
	.size	num.13756, 4
num.13756:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
