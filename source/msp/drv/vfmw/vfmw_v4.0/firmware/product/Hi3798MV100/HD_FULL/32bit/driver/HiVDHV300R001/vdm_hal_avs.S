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
	.file	"vdm_hal_avs.c"
	.text
	.align	2
	.global	AVSHAL_V300R001_WirteSlicMsg
	.type	AVSHAL_V300R001_WirteSlicMsg, %function
AVSHAL_V300R001_WirteSlicMsg:
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
	ldr	ip, .L43
	movw	r3, #1208
	mov	r6, r0
	str	r0, [fp, #-60]
	mla	r3, r3, r2, ip
	str	r1, [fp, #-56]
	add	r1, r0, #208
	str	r2, [fp, #-68]
	str	r1, [fp, #-48]
	ldr	r5, [r3, #48]
	add	r4, r5, #320
	mov	r0, r5
	bl	MEM_Phy2Vir
	ldr	r2, [r6, #224]
	cmp	r2, #0
	add	r10, r0, #320
	beq	.L2
	ldr	lr, [fp, #-60]
	mov	r1, #0
	ldr	ip, [fp, #-56]
	add	r3, r5, #576
	ldr	r2, [lr, #208]
	add	r2, r2, #4
	rsb	r2, ip, r2
	bic	ip, r2, #-16777216
	bic	ip, ip, #15
	mov	r2, r2, asl #28
	str	r2, [r0, #320]
	mov	r2, #1
	str	ip, [r0, #324]
	str	r1, [r0, #328]
	str	r1, [r0, #332]
	ldr	r1, [lr, #224]
	sub	r1, r1, #1
	mov	r1, r1, asl #16
	str	r1, [r0, #336]
	str	r3, [r0, #572]
.L2:
	ldr	r3, [fp, #-60]
	add	r3, r3, #12288
	ldr	r1, [r3, #2256]
	cmp	r1, #0
	ble	.L1
	add	r2, r4, r2, lsl #8
	str	r2, [fp, #-64]
	mov	r2, #0
	mov	r8, r3
	mov	r9, r2
	mov	r4, r2
.L24:
	cmp	r9, #512
	bge	.L4
	cmp	r4, #0
	mov	r3, r4, asl #2
	mov	r7, r4, asl #5
	ldrle	r2, [fp, #-48]
	rsb	r5, r3, r7
	addle	r5, r2, r5
	ble	.L6
	ldr	r1, [fp, #-48]
	add	r5, r1, r5
	ldr	r0, [r5, #16]
	ldr	r1, [r5, #-12]
	cmp	r0, r1
	bls	.L7
.L6:
	str	r3, [fp, #-52]
	ldr	r3, .L43+4
	ldr	r0, [r5]
	ldr	r2, [r3, #188]
	add	r0, r0, #3
	blx	r2
	ldr	r3, [fp, #-52]
	ldr	r2, [r0]
	bic	r2, r2, #-16777216
	cmp	r2, #131072
	beq	.L41
	ldr	r6, [r5]
	ldr	r2, [fp, #-56]
	add	r6, r6, #4
	rsb	r6, r2, r6
	and	r2, r6, #15
	bic	r6, r6, #15
	mov	r2, r2, asl #3
.L14:
	ldmib	r5, {r0, r1}
	cmp	r0, #0
	mov	r1, r1, asl #3
	beq	.L38
	ldr	ip, [fp, #-60]
	rsb	r3, r3, r7
	add	r3, ip, r3
	ldr	r3, [r3, #220]
	cmp	r3, #0
	ble	.L28
	ldr	r3, [fp, #-56]
	cmp	r1, #0
	ldr	r7, [r5, #12]
	rsb	r0, r3, r0
	and	ip, r0, #15
	bic	lr, r0, #15
	mov	r3, ip, asl #3
	mov	ip, r7, asl #3
	beq	.L29
	bic	ip, ip, #-33554432
	bic	r0, r0, #-16777216
	orr	ip, ip, r3, asl #25
	bic	r0, r0, #15
.L15:
	mov	r3, r4, asl #8
	bic	r1, r1, #-33554432
	orr	r2, r1, r2, asl #25
	add	r7, r3, #4
	add	lr, r3, #8
	add	r1, r3, #12
	str	r2, [r10, r4, asl #8]
	bic	r6, r6, #-16777216
	str	r6, [r10, r7]
	add	r2, r4, #1
	str	ip, [r10, lr]
	str	r0, [r10, r1]
	ldr	r0, [r8, #2256]
	cmp	r2, r0
	ldrge	ip, [r5, #16]
	bge	.L17
	mov	r1, r2, asl #5
	ldr	r4, [fp, #-48]
	sub	r1, r1, r2, asl #2
	ldr	ip, [r5, #16]
	add	lr, r4, r1
	ldr	lr, [lr, #16]
	cmp	ip, lr
	bcc	.L17
	sub	r1, r1, #28
	add	r1, r4, r1
	b	.L18
.L20:
	ldr	lr, [r1, #44]
	cmp	lr, ip
	bhi	.L22
.L18:
	add	r2, r2, #1
	add	r1, r1, #28
	cmp	r2, r0
	bne	.L20
.L21:
	ldr	lr, [fp, #-60]
	mov	r2, r0
	ldr	r1, [lr, #168]
	ldr	r0, [lr, #164]
	mov	lr, #0
	mul	r1, r0, r1
	sub	r1, r1, #1
.L23:
	add	r0, r3, #16
	add	r9, r9, #1
	add	r3, r3, #252
	uxth	ip, ip
	orr	ip, ip, r1, asl #16
	str	ip, [r10, r0]
	str	lr, [r10, r3]
.L4:
	sub	r4, r2, #1
.L7:
	ldr	r3, [r8, #2256]
	add	r4, r4, #1
	cmp	r3, r4
	bgt	.L24
.L1:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L17:
	cmp	r2, r0
	beq	.L21
.L22:
	ldr	r0, [fp, #-64]
	mov	r1, r2, asl #5
	sub	r1, r1, r2, asl #2
	add	lr, r0, r2, lsl #8
	ldr	r0, [fp, #-48]
	add	r1, r0, r1
	ldr	r1, [r1, #16]
	sub	r1, r1, #1
	b	.L23
.L29:
	mov	r0, #0
	mov	r6, lr
	mov	r1, ip
	mov	r2, r3
.L38:
	mov	ip, r0
	b	.L15
.L41:
	ldr	r3, .L43+4
	mov	r6, #64
	ldr	r0, [r5]
	ldr	r2, [r3, #188]
	add	r0, r0, #2
	blx	r2
	mov	r3, #0
	strb	r3, [r0]
	ldr	r3, .L43+4
	ldr	r0, [r5]
	ldr	r2, [r3, #188]
	add	r0, r0, #4
	blx	r2
	ldr	r3, .L43+4
	strb	r6, [r0]
	ldr	r0, [r5]
	ldr	r2, [r3, #188]
	add	r0, r0, #5
	blx	r2
	strb	r6, [r0]
	ldr	r0, [fp, #-68]
	bl	VDMHAL_V300R001_ResetVdm
	ldr	r6, [r5]
	ldr	r3, [fp, #-56]
	ldr	r1, [fp, #-68]
	add	r6, r6, #2
	rsb	r6, r3, r6
	ldr	r3, [fp, #-52]
	and	r2, r6, #15
	cmp	r1, #0
	bic	r6, r6, #15
	mov	r2, r2, asl #3
	beq	.L10
	cmp	r1, #1
	bne	.L42
	str	r3, [fp, #-76]
	ldr	r3, .L43+8
	ldr	r1, [fp, #-68]
	str	r2, [fp, #-72]
	ldr	r0, [r3]
	str	r3, [fp, #-52]
	add	r0, r0, #2032
	bl	MEM_WritePhyWord
	ldr	r3, .L43+8
	ldr	r1, [fp, #-68]
	ldr	r0, [r3]
	add	r0, r0, #1792
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r3, .L43+8
	mov	r1, #0
	ldr	r0, [r3]
	add	r0, r0, #2032
	bl	MEM_WritePhyWord
	ldr	r2, [fp, #-72]
	ldr	r3, [fp, #-76]
.L13:
	str	r3, [fp, #-76]
	mov	r1, #0
	ldr	r3, [fp, #-52]
	str	r2, [fp, #-72]
	ldr	r0, [r3]
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	ldr	r2, [fp, #-72]
	ldr	r3, [fp, #-76]
	b	.L14
.L28:
	mov	r0, #0
	mov	ip, r0
	b	.L15
.L42:
	ldr	r1, [fp, #-68]
	cmp	r1, #0
	ldreq	r1, .L43+12
	streq	r1, [fp, #-52]
	beq	.L13
	ldr	r1, [fp, #-68]
	cmp	r1, #1
	bne	.L14
	ldr	r1, .L43+8
	str	r1, [fp, #-52]
	b	.L13
.L10:
	str	r3, [fp, #-76]
	mov	r1, #1
	ldr	r3, .L43+12
	str	r2, [fp, #-72]
	ldr	r0, [r3]
	str	r3, [fp, #-52]
	add	r0, r0, #2032
	bl	MEM_WritePhyWord
	ldr	r3, .L43+12
	mov	r1, #1
	ldr	r0, [r3]
	add	r0, r0, #1792
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r3, .L43+12
	ldr	r1, [fp, #-68]
	ldr	r0, [r3]
	add	r0, r0, #2032
	bl	MEM_WritePhyWord
	ldr	r2, [fp, #-72]
	ldr	r3, [fp, #-76]
	b	.L13
.L44:
	.align	2
.L43:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_RegPhyBaseAddr_1
	.word	s_RegPhyBaseAddr
	UNWIND(.fnend)
	.size	AVSHAL_V300R001_WirteSlicMsg, .-AVSHAL_V300R001_WirteSlicMsg
	.align	2
	.global	AVSHAL_V300R001_StartDec
	.type	AVSHAL_V300R001_StartDec, %function
AVSHAL_V300R001_StartDec:
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
	subs	r4, r0, #0
	str	r1, [fp, #-60]
	ldreq	r3, .L87
	ldreq	r1, .L87+4
	beq	.L82
	ldr	ip, [r4, #164]
	cmp	ip, #512
	bhi	.L83
	ldr	lr, [r4, #168]
	cmp	lr, #512
	bhi	.L83
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	bgt	.L50
	add	r3, r4, #12288
	str	r3, [fp, #-56]
	ldr	r0, [r3, #2256]
	cmp	r0, #0
	ble	.L51
	mov	r3, r4
	mov	r1, #0
	mvn	r5, #0
.L52:
	ldr	r2, [r3, #208]
	cmp	r2, #0
	beq	.L55
	ldr	r6, [r3, #216]
	bic	r2, r2, #15
	cmp	r6, #0
	ble	.L55
	cmp	r5, r2
	movcs	r5, r2
.L55:
	ldr	r2, [r3, #212]
	cmp	r2, #0
	beq	.L53
	ldr	r6, [r3, #220]
	bic	r2, r2, #15
	cmp	r6, #0
	ble	.L53
	cmp	r5, r2
	movcs	r5, r2
.L53:
	add	r1, r1, #1
	add	r3, r3, #28
	cmp	r1, r0
	bne	.L52
	cmn	r5, #1
	beq	.L51
	mul	ip, ip, lr
	ldr	r3, [fp, #-60]
	movw	r6, #1208
	mov	r7, #0
	ldr	r8, .L87+8
	mov	r2, #65
	mul	r6, r6, r3
	sub	ip, ip, #1
	mov	r3, r7
	bfi	r3, ip, #0, #20
	str	r3, [fp, #-48]
	bfi	r2, r7, #1, #1
	mov	r3, r3, lsr #16
	strb	r2, [fp, #-45]
	orr	r3, r3, #64
	ldr	r10, .L87+4
	bfi	r3, r7, #7, #1
	strb	r3, [fp, #-46]
	ldr	r3, [fp, #-48]
	mov	r0, #3
	ldr	r1, [r8, r6]
	add	r9, r8, r6
	mov	r2, r3
	str	r3, [r1, #8]
	ldr	r1, .L87+12
	ldr	r3, [r10, #68]
	blx	r3
	ldr	ip, [fp, #-56]
	mov	r3, #805306368
	str	r3, [fp, #-48]
	ldrh	r2, [fp, #-46]
	mov	r1, #1
	ldr	r0, [ip, #2676]
	mov	r3, #6
	bfi	r2, r1, #0, #12
	strb	r3, [fp, #-48]
	ldrh	r1, [fp, #-48]
	mov	r3, r2, lsr #8
	mov	r0, r0, lsr #6
	bfi	r1, r0, #4, #10
	and	r3, r3, #239
	ldr	r0, [ip, #2696]
	orr	r3, r3, #32
	strh	r2, [fp, #-46]	@ movhi
	ubfx	r2, r1, #8, #8
	bfi	r3, r0, #6, #1
	orr	r2, r2, #64
	strh	r1, [fp, #-48]	@ movhi
	bfi	r2, r7, #7, #1
	bfi	r3, r7, #7, #1
	strb	r2, [fp, #-47]
	strb	r3, [fp, #-45]
	mov	r0, #3
	ldr	ip, [r8, r6]
	ldr	r3, [fp, #-48]
	ldr	r1, .L87+16
	str	r3, [ip, #12]
	mov	r2, r3
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r8, r6]
	ldr	r2, [r9, #48]
	mov	r0, #3
	ldr	r1, .L87+20
	bic	r2, r2, #15
	str	r2, [r3, #16]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r8, r6]
	ldr	r2, [r9, #32]
	mov	r0, #3
	ldr	r1, .L87+24
	bic	r2, r2, #15
	str	r2, [r3, #20]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r8, r6]
	mov	r2, r5
	ldr	r1, .L87+28
	mov	r0, #3
	str	r5, [fp, #-48]
	str	r5, [r3, #24]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r4, #164]
	movw	r0, #49156
	cmp	r3, #120
	movt	r0, 63683
	movls	r7, #65536
	bl	MEM_ReadPhyWord
	ldr	r3, .L87+32
	ldr	r3, [r3]
	orr	r1, r0, r7
	add	r0, r3, #4
	bl	MEM_WritePhyWord
	ldr	r2, [r8, r6]
	movw	r3, #3075
	ldr	r7, [fp, #-56]
	movt	r3, 48
	ldr	r1, .L87+36
	str	r3, [r2, #60]
	mov	r0, #3
	ldr	r2, [r8, r6]
	str	r3, [r2, #64]
	ldr	r2, [r8, r6]
	str	r3, [r2, #68]
	ldr	r2, [r8, r6]
	str	r3, [r2, #72]
	ldr	r2, [r8, r6]
	str	r3, [r2, #76]
	ldr	r2, [r8, r6]
	str	r3, [r2, #80]
	ldr	r2, [r8, r6]
	str	r3, [r2, #84]
	ldr	r3, [r8, r6]
	ldr	r2, [r7, #2272]
	bic	r2, r2, #15
	str	r2, [r3, #96]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r8, r6]
	ldr	r2, [r7, #2676]
	mov	r0, #3
	ldr	r6, [r4, #168]
	ldr	r1, .L87+40
	str	r2, [r3, #100]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r4, #164]
	mov	r3, r3, asl #4
	sub	r2, r3, #1
	cmp	r2, #2048
	movcc	lr, #16
	bcs	.L85
.L59:
	ldr	r3, [fp, #-56]
	mov	r7, r6, asl #4
	ldr	r0, [fp, #-60]
	add	r7, r7, #31
	add	r2, r6, #1
	movw	r9, #1208
	ldr	ip, [r3, #2676]
	mov	r3, r7, lsr #5
	mul	r9, r9, r0
	mov	r2, r2, lsr #1
	mul	r7, r3, lr
	ldr	r1, .L87+44
	mul	r2, ip, r2
	add	r3, r8, r9
	str	r3, [fp, #-64]
	mov	r0, #3
	ldr	r3, [r8, r9]
	mov	r6, #0
	add	r2, r2, r7, lsl #4
	mov	r2, r2, asl #1
	str	r2, [r3, #104]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r8, r9]
	mov	r2, r7, asl #5
	ldr	r1, .L87+48
	mov	r0, #3
	str	r2, [r3, #108]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r7, [fp, #-64]
	ldr	r3, [r8, r9]
	mov	r0, #3
	ldr	r1, .L87+52
	ldr	r2, [r7, #1184]
	str	r2, [r3, #144]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r8, r9]
	mov	r2, r6
	ldr	r1, .L87+56
	mov	r0, #3
	str	r6, [fp, #-48]
	str	r6, [r3, #148]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r8, r9]
	mov	r2, r6
	ldr	r1, .L87+60
	mov	r0, #3
	str	r6, [r3, #152]
	ldr	r3, [r10, #68]
	blx	r3
	ldr	r3, [r8, r9]
	mvn	r2, #0
	ldr	r9, .L87+4
	str	r2, [r3, #32]
	ldr	r0, [r7, #48]
	bl	MEM_Phy2Vir
	subs	r7, r0, #0
	beq	.L86
	ldr	r3, [r4, #168]
	mov	r0, #4
	ldrh	r1, [fp, #-46]
	ldr	ip, [r4, #164]
	sub	r3, r3, #1
	ldrh	r2, [fp, #-48]
	bfi	r1, r3, #0, #9
	ldr	lr, [r4, #124]
	sub	ip, ip, #1
	bfi	r2, ip, #0, #9
	mov	r3, r1, lsr #8
	ldr	ip, [r4, #120]
	bfi	r3, lr, #1, #2
	strh	r1, [fp, #-46]	@ movhi
	mov	r1, r2, lsr #8
	bfi	r3, ip, #3, #2
	strh	r2, [fp, #-48]	@ movhi
	bfi	r1, r6, #1, #7
	bfi	r3, r6, #5, #3
	strb	r1, [fp, #-47]
	strb	r3, [fp, #-45]
	ldr	r2, [fp, #-48]
	ldr	r1, .L87+64
	str	r2, [r7]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r2, [r4, #64]
	ldr	ip, [r4, #32]
	mov	r3, r6
	ldr	r0, [r4, #40]
	bfi	r3, r2, #0, #1
	mov	r1, r6, lsr #24
	ldr	r2, [r4, #28]
	bfi	r3, ip, #1, #2
	bfi	r1, r0, #0, #1
	ldr	r0, [r4, #48]
	bfi	r3, r2, #3, #2
	mov	r2, r6, lsr #24
	ldr	ip, [r4, #60]
	bfi	r2, r0, #0, #6
	ldr	r0, [r4, #36]
	bfi	r3, ip, #5, #1
	ldr	ip, [r4, #56]
	bfi	r1, r0, #1, #1
	ldr	r0, [r4, #44]
	str	r6, [fp, #-48]
	bfi	r3, ip, #6, #1
	strb	r1, [fp, #-46]
	bfi	r2, r0, #6, #1
	ldr	ip, [r4, #88]
	ldr	r1, [r4, #52]
	ldrh	r0, [fp, #-46]
	bfi	r2, ip, #7, #1
	bfi	r3, r1, #7, #1
	strb	r2, [fp, #-47]
	bfi	r0, r6, #2, #14
	strb	r3, [fp, #-48]
	strh	r0, [fp, #-46]	@ movhi
	mov	r0, #4
	ldr	r2, [fp, #-48]
	ldr	r1, .L87+68
	str	r2, [r7, #4]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r1, [r4, #80]
	ldr	r2, [r4, #76]
	mov	r3, r6
	bfi	r3, r1, #0, #1
	ldr	r1, [r4, #72]
	bfi	r3, r2, #1, #1
	str	r6, [fp, #-48]
	ldr	r2, [r4, #68]
	bfi	r3, r1, #2, #5
	strb	r3, [fp, #-48]
	mov	r0, #4
	ldrh	r3, [fp, #-48]
	ldr	r1, .L87+72
	bfi	r3, r2, #7, #5
	strh	r3, [fp, #-48]	@ movhi
	ldr	r2, [fp, #-48]
	str	r2, [r7, #8]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r2, [r4, #100]
	ldr	ip, [r4, #104]
	mov	r3, r6
	ldr	r1, [r4, #108]
	bfi	r3, r2, #0, #1
	bfi	r3, ip, #1, #2
	ldr	r2, [r4, #112]
	bfi	r3, r1, #3, #1
	ldr	r1, [r4, #92]
	bfi	r3, r2, #4, #2
	str	r6, [fp, #-48]
	ldr	r2, [r4, #96]
	bfi	r3, r1, #6, #1
	strb	r3, [fp, #-48]
	mov	r0, #4
	ldrh	r3, [fp, #-48]
	ldr	r1, .L87+76
	bfi	r3, r2, #7, #2
	strh	r3, [fp, #-48]	@ movhi
	ldr	r2, [fp, #-48]
	bfi	r2, r6, #9, #23
	str	r2, [fp, #-48]
	str	r2, [r7, #12]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r3, [fp, #-56]
	ldr	r1, .L87+80
	mov	r0, #4
	ldr	r2, [r3, #2260]
	bic	r2, r2, #15
	str	r2, [r7, #16]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r3, [fp, #-56]
	ldr	r1, .L87+84
	mov	r0, #4
	ldr	r2, [r3, #2264]
	bic	r2, r2, #15
	str	r2, [r7, #20]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r3, [fp, #-56]
	ldr	r1, .L87+88
	mov	r0, #4
	ldr	r2, [r3, #2268]
	bic	r2, r2, #15
	str	r2, [r7, #24]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r3, [fp, #-56]
	ldr	r1, .L87+92
	mov	r0, #4
	ldr	r2, [r3, #2284]
	bic	r2, r2, #15
	str	r2, [r7, #28]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r1, [r4, #116]
	ldr	r0, [r4, #84]
	mov	r2, r6, lsr #24
	str	r6, [fp, #-48]
	mov	r3, r6
	bfi	r2, r0, #0, #2
	bfi	r3, r1, #0, #1
	strb	r2, [fp, #-45]
	mov	r0, #4
	strb	r3, [fp, #-48]
	ldr	r2, [fp, #-48]
	ldr	r1, .L87+96
	str	r2, [r7, #32]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r2, [r4, #184]
	mov	r3, r6
	ldr	r1, .L87+100
	bfi	r3, r2, #0, #24
	mov	r0, #4
	str	r3, [fp, #-48]
	mov	r2, r3
	str	r3, [r7, #36]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r2, [r4, #200]
	mov	r3, r6
	ldr	r1, .L87+104
	bfi	r3, r2, #0, #24
	str	r3, [fp, #-48]
	ldr	r2, [r4, #192]
	mov	r0, #4
	mov	r3, r3, lsr #24
	bfi	r3, r2, #0, #7
	strb	r3, [fp, #-45]
	ldr	r2, [fp, #-48]
	str	r2, [r7, #40]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r2, [r4, #188]
	mov	r3, r6
	ldr	r1, .L87+108
	bfi	r3, r2, #0, #24
	mov	r0, #4
	str	r3, [fp, #-48]
	mov	r2, r3
	str	r3, [r7, #44]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r0, [r4, #128]
	ldr	r1, [r4, #136]
	mov	r3, r6, lsr #24
	mov	r2, r6
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #132]
	bfi	r3, r1, #0, #6
	ldr	r1, [r4, #144]
	ldr	ip, [r4, #140]
	bfi	r2, r0, #1, #1
	ldr	lr, [r4, #152]
	bfi	r3, r1, #6, #1
	ldr	r0, [r4, #148]
	mov	r1, r6, lsr #24
	str	r6, [fp, #-48]
	bfi	r2, ip, #2, #6
	bfi	r1, lr, #0, #1
	bfi	r3, r0, #7, #1
	strb	r1, [fp, #-46]
	mov	r0, #4
	strb	r3, [fp, #-47]
	strb	r2, [fp, #-48]
	ldr	r2, [fp, #-48]
	ldr	r1, .L87+112
	str	r2, [r7, #48]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r6, [fp, #-64]
	ldr	r1, .L87+116
	mov	r0, #4
	ldr	r2, [r6, #1140]
	bic	r2, r2, #15
	str	r2, [r7, #52]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r2, [r6, #1144]
	ldr	r1, .L87+120
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r7, #56]
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r3, [fp, #-56]
	ldr	r1, .L87+124
	mov	r0, #4
	ldr	r2, [r3, #2280]
	bic	r2, r2, #15
	str	r2, [r7, #64]
	ldr	r3, [r9, #68]
	blx	r3
	add	r3, r4, #14528
	add	r0, r4, #14656
	add	r3, r3, #48
	add	r0, r0, #48
	add	r2, r7, #68
.L60:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2], #4
	bne	.L60
	ldr	r3, [fp, #-56]
	mov	r0, #4
	ldr	r1, .L87+128
	ldr	r2, [r3, #2276]
	ldr	r3, [r10, #68]
	bic	r2, r2, #15
	str	r2, [r7, #196]
	blx	r3
	ldr	r2, [fp, #-60]
	movw	r3, #1208
	ldr	r1, .L87+132
	mov	r0, #4
	mla	r8, r3, r2, r8
	ldr	r3, [r10, #68]
	ldr	r2, [r8, #1152]
	bic	r2, r2, #15
	str	r2, [r7, #200]
	blx	r3
	ldr	r2, [r8, #1136]
	ldr	r3, [r10, #68]
	mov	r0, #4
	bic	r2, r2, #15
	ldr	r1, .L87+136
	str	r2, [r7, #204]
	blx	r3
	ldr	r3, [r8, #48]
	ldr	r6, [r10, #68]
	mov	r0, #4
	add	r3, r3, #320
	ldr	r1, .L87+140
	str	r3, [r7, #252]
	mov	r2, r3
	str	r3, [fp, #-48]
	blx	r6
	ldr	ip, [r4, #128]
	cmp	ip, #1
	beq	.L61
.L65:
	mov	r0, r4
	ldr	r2, [fp, #-60]
	mov	r1, r5
	bl	AVSHAL_V300R001_WirteSlicMsg
	mov	r0, #0
.L79:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L85:
	sub	r2, r3, #2048
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	lr, #32
	bcc	.L59
	sub	r2, r3, #4096
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	lr, #48
	bcc	.L59
	sub	r3, r3, #6144
	sub	r3, r3, #1
	cmp	r3, #2048
	movcs	lr, #16
	movcc	lr, #64
	b	.L59
.L61:
	add	r0, r4, #14720
	add	lr, r7, #256
	add	r0, r0, #12
	add	r7, r7, #320
.L64:
	tst	ip, #1
	add	r0, r0, #16
	add	ip, ip, #1
	ldrneb	r1, [r0, #-24]	@ zero_extendqisi2
	ldreqb	r1, [r0, #-36]	@ zero_extendqisi2
	ldrneb	r3, [r0, #-16]	@ zero_extendqisi2
	ldreqb	r3, [r0, #-28]	@ zero_extendqisi2
	movne	r1, r1, asl #16
	ldrneb	r2, [r0, #-40]	@ zero_extendqisi2
	moveq	r1, r1, asl #16
	ldrneb	r6, [r0, #-32]	@ zero_extendqisi2
	ldreqb	r2, [r0, #-52]	@ zero_extendqisi2
	orr	r3, r1, r3, asl #24
	ldreqb	r6, [r0, #-44]	@ zero_extendqisi2
	orr	r3, r3, r2
	orr	r3, r3, r6, asl #8
	str	r3, [lr], #4
	cmp	lr, r7
	bne	.L64
	b	.L65
.L50:
	ldr	r1, .L87+4
	mov	r0, #0
	ldr	r3, [fp, #-60]
	str	r0, [sp]
	ldr	r2, .L87+144
	ldr	r4, [r1, #68]
	ldr	r1, .L87+148
	blx	r4
	mvn	r0, #0
	b	.L79
.L83:
	ldr	r1, .L87+4
	mov	r0, #0
	ldr	r3, .L87+152
.L82:
	ldr	r4, [r1, #68]
	ldr	r2, .L87+144
	ldr	r1, .L87+156
	blx	r4
	mvn	r0, #0
	b	.L79
.L86:
	ldr	r4, [r9, #68]
	ldr	r3, .L87+160
	ldr	r2, .L87+144
	ldr	r1, .L87+156
	blx	r4
	mvn	r0, #0
	b	.L79
.L51:
	ldr	r3, .L87+4
	mvn	r2, #0
	ldr	r1, .L87+164
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L79
.L88:
	.align	2
.L87:
	.word	.LC0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	s_RegPhyBaseAddr
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC35
	.word	.LC36
	.word	.LC37
	.word	.LC11
	.word	.LC12
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	.LC18
	.word	.LC19
	.word	.LC20
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC30
	.word	.LANCHOR0
	.word	.LC3
	.word	.LC2
	.word	.LC1
	.word	.LC10
	.word	.LC4
	UNWIND(.fnend)
	.size	AVSHAL_V300R001_StartDec, .-AVSHAL_V300R001_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13613, %object
	.size	__func__.13613, 25
__func__.13613:
	.ascii	"AVSHAL_V300R001_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"point of picture para null\012\000" )
.LC1:
	ASCII(.ascii	"%s: %s\012\000" )
.LC2:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC3:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC4:
	ASCII(.ascii	"stream_base_addr = %#x\012\000" )
.LC5:
	ASCII(.ascii	"BASIC_V300R001_CFG0 = 0x%x\012\000" )
.LC6:
	ASCII(.ascii	"BASIC_V300R001_CFG1 = 0x%x\012\000" )
.LC7:
	ASCII(.ascii	"AVM_V300R001_ADDR = 0x%x\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"VAM_V300R001_ADDR = 0x%x\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"STREAM_V300R001_BASE_ADDR = 0x%x\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"can not map down msg virtual address!\000" )
	.space	2
.LC11:
	ASCII(.ascii	"D0 = 0x%x\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"D1 = 0x%x\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"D2 = 0x%x\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"D3 = 0x%x\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"D4 = 0x%x\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"D5 = 0x%x\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"D6 = 0x%x\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"D7 = 0x%x\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"D8 = 0x%x\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"D9 = 0x%x\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"D10 = 0x%x\012\000" )
.LC22:
	ASCII(.ascii	"D11 = 0x%x\012\000" )
.LC23:
	ASCII(.ascii	"D12 = 0x%x\012\000" )
.LC24:
	ASCII(.ascii	"D13 = 0x%x\012\000" )
.LC25:
	ASCII(.ascii	"D14 = 0x%x\012\000" )
.LC26:
	ASCII(.ascii	"D16 = 0x%x\012\000" )
.LC27:
	ASCII(.ascii	"D49 = 0x%x\012\000" )
.LC28:
	ASCII(.ascii	"D50 = 0x%x\012\000" )
.LC29:
	ASCII(.ascii	"D51 = 0x%x\012\000" )
.LC30:
	ASCII(.ascii	"D63 = 0x%x\012\000" )
.LC31:
	ASCII(.ascii	"YSTADDR_V300R001_1D = 0x%x\012\000" )
.LC32:
	ASCII(.ascii	"YSTRIDE_V300R001_1D = 0x%x\012\000" )
.LC33:
	ASCII(.ascii	"UVOFFSET_V300R001_1D = 0x%x\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"PRCNUM_1D_CNT = 0x%x\012\000" )
	.space	2
.LC35:
	ASCII(.ascii	"VREG_V300R001_DNR_MBINFO_STADDR = 0x%x\012\000" )
.LC36:
	ASCII(.ascii	"VREG_V200R003_REF_PIC_TYPE = 0x%x\012\000" )
	.space	1
.LC37:
	ASCII(.ascii	"VREG_V300R001_FF_APT_EN = 0x%x\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
