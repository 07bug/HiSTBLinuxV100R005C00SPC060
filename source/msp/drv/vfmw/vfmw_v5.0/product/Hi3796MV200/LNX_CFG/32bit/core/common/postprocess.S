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
	.file	"postprocess.c"
	.text
	.align	2
	.global	PostPro_BubbleSort
	.type	PostPro_BubbleSort, %function
PostPro_BubbleSort:
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
	ldr	r8, [r0, #12]
	cmp	r8, #1
	bls	.L14
	mov	r7, #1
.L6:
	mov	r4, #0
	rsb	lr, r7, r8
	mov	r2, r4
	mov	r3, r0
	b	.L7
.L5:
	ldrh	r1, [r3, #20]
	ldrh	ip, [r3, #24]
	cmp	r1, ip
	bls	.L4
	ldrh	r6, [r3, #22]
	mov	r4, #1
	ldrh	r5, [r3, #26]
	strh	ip, [r3, #20]	@ movhi
	strh	r1, [r3, #24]	@ movhi
	strh	r6, [r3, #26]	@ movhi
	strh	r5, [r3, #22]	@ movhi
.L4:
	add	r3, r3, #4
.L7:
	cmp	r2, lr
	add	r2, r2, #1
	bne	.L5
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	add	r7, r7, #1
	cmp	r8, r7
	movls	r4, #0
	andhi	r4, r4, #1
	cmp	r4, #0
	bne	.L6
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L14:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	PostPro_BubbleSort, .-PostPro_BubbleSort
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.global	PostPro_GetH264MbOfMBAFF
	.type	PostPro_GetH264MbOfMBAFF, %function
PostPro_GetH264MbOfMBAFF:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 832
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #836)
	sub	sp, sp, #836
	ldr	r3, [r1, #12]
	ldr	r2, [r0, #28]
	mov	r9, r1
	cmp	r3, #0
	mov	r10, r0
	mov	r4, r3
	str	r3, [fp, #-856]
	ldr	r3, [r0, #32]
	mov	r6, r2, asl #1
	str	r2, [fp, #-868]
	str	r3, [fp, #-872]
	beq	.L28
	sub	lr, fp, #844
	mov	r2, r1
	mov	r1, #0
	str	lr, [fp, #-876]
	mov	r3, lr
.L17:
	ldrh	ip, [r2, #20]
	add	r1, r1, #1
	ldrh	r0, [r2, #22]
	cmp	r1, r4
	add	r2, r2, #4
	add	r3, r3, #4
	strh	ip, [r3, #-4]	@ movhi
	strh	r0, [r3, #-2]	@ movhi
	bne	.L17
	ldrh	r8, [lr]
	cmp	r6, #0
	ldrh	r3, [lr, #2]
	bic	r8, r8, #1
	orr	r3, r3, #1
	str	r3, [fp, #-848]
	uxth	r8, r8
	strh	r3, [lr, #2]	@ movhi
	strh	r8, [lr]	@ movhi
	beq	.L29
	mov	r5, #0
	sub	r3, r6, #2
	mov	r7, r5
	str	r3, [fp, #-852]
	uxth	r3, r6
	str	r3, [fp, #-864]
.L25:
	mov	r1, r6
	mov	r0, r8
	bl	__aeabi_uidivmod
	ldr	r0, [fp, #-848]
	mov	r4, r1
	cmp	r4, #1
	mov	r1, r6
	bls	.L19
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-852]
	cmp	r2, r1
	bls	.L20
	str	r1, [fp, #-860]
	mov	r0, r8
	mov	r1, r6
	mov	r4, r4, lsr #1
	bl	__aeabi_uidiv
	mov	r1, r6
	mov	r8, r0
	ldr	r0, [fp, #-848]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-860]
	mov	r3, r3, lsr #1
	cmp	r0, r8
	beq	.L21
	ldr	lr, [fp, #-864]
	add	r2, r9, r5, lsl #2
	add	r1, r5, #1
	cmp	r1, #199
	smulbb	r8, r8, lr
	uxth	r8, r8
	add	r4, r8, r4
	uxth	r4, r4
	strh	r4, [r2, #20]	@ movhi
	ldr	ip, [r10, #28]
	sub	ip, ip, #1
	add	r8, r8, ip
	strh	r8, [r2, #22]	@ movhi
	bhi	.L22
	smulbb	r0, r0, lr
	add	ip, r5, #2
	ldr	lr, [r10, #28]
	add	r1, r9, r1, lsl #2
	cmp	ip, #199
	uxth	r3, r3
	add	r4, r4, lr
	strh	r4, [r2, #24]	@ movhi
	uxth	r0, r0
	add	lr, r3, r0
	strh	lr, [r1, #22]	@ movhi
	bhi	.L22
	ldr	r1, [r10, #28]
	add	r5, r5, #3
	add	ip, r9, ip, lsl #2
	cmp	r5, #199
	add	r0, r0, r1
	uxth	r0, r0
	strh	r0, [r2, #28]	@ movhi
	add	r3, r0, r3
	strh	r3, [ip, #22]	@ movhi
	bhi	.L22
.L23:
	ldr	r3, [fp, #-856]
	add	r7, r7, #1
	cmp	r7, r3
	beq	.L18
.L26:
	ldr	r2, [fp, #-876]
	ldrh	r3, [r2, #6]
	ldrh	r8, [r2, #4]
	orr	r3, r3, #1
	str	r3, [fp, #-848]
	bic	r8, r8, #1
	strh	r8, [r2, #4]	@ movhi
	mov	r1, r3
	mov	r3, r2
	strh	r1, [r3, #6]	@ movhi
	add	r3, r3, #4
	str	r3, [fp, #-876]
	b	.L25
.L20:
	mov	r1, r6
	mov	r0, r8
	bl	__aeabi_uidiv
	add	r2, r9, r5, lsl #2
	add	r3, r5, #1
	cmp	r3, #199
	smulbb	r0, r0, r6
	uxth	r0, r0
	add	r4, r0, r4, lsr #1
	uxth	r4, r4
	strh	r4, [r2, #20]	@ movhi
	ldr	r1, [r10, #28]
	sub	r1, r1, #1
	add	r0, r0, r1
	strh	r0, [r2, #22]	@ movhi
	bhi	.L22
	ldr	r1, [r10, #28]
	add	r5, r5, #2
	add	r3, r9, r3, lsl #2
	cmp	r5, #199
	add	r4, r4, r1
	strh	r4, [r2, #24]	@ movhi
	ldr	r2, [fp, #-848]
	strh	r2, [r3, #22]	@ movhi
	bls	.L23
.L22:
	ldr	r2, [fp, #-868]
	mov	r1, #1
	ldr	r3, [fp, #-872]
	mov	r0, r9
	str	r1, [r9, #12]
	mul	r3, r3, r2
	mov	r2, #0
	strh	r2, [r9, #20]	@ movhi
	sub	r3, r3, #1
	strh	r3, [r9, #22]	@ movhi
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	PostPro_BubbleSort
.L19:
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-852]
	cmp	r2, r1
	bls	.L24
	add	r4, r9, r5, lsl #2
	str	r1, [fp, #-860]
	ldr	r0, [fp, #-848]
	mov	r1, r6
	strh	r8, [r4, #20]	@ movhi
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-860]
	add	r2, r5, #1
	cmp	r2, #199
	ubfx	r1, r3, #1, #16
	smulbb	r0, r0, r6
	uxth	r0, r0
	add	r3, r1, r0
	strh	r3, [r4, #22]	@ movhi
	bhi	.L22
	ldr	r3, [r10, #28]
	add	r5, r5, #2
	add	r2, r9, r2, lsl #2
	cmp	r5, #199
	add	r0, r0, r3
	uxth	r3, r0
	strh	r3, [r4, #24]	@ movhi
	add	r3, r3, r1
	strh	r3, [r2, #22]	@ movhi
	bhi	.L22
	ldr	r3, [fp, #-856]
	add	r7, r7, #1
	cmp	r7, r3
	bne	.L26
.L18:
	str	r5, [r9, #12]
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	PostPro_BubbleSort
.L24:
	add	r2, r9, r5, lsl #2
	add	r5, r5, #1
	cmp	r5, #199
	mov	r3, r2
	strh	r8, [r2, #20]	@ movhi
	ldr	r2, [fp, #-848]
	strh	r2, [r3, #22]	@ movhi
	bls	.L23
	b	.L22
.L21:
	smulbb	r0, r0, r6
	add	r2, r5, #1
	add	r1, r9, r5, lsl #2
	cmp	r2, #199
	uxth	r0, r0
	add	r4, r0, r4
	add	r3, r0, r3
	uxth	r4, r4
	uxth	r3, r3
	strh	r4, [r1, #20]	@ movhi
	strh	r3, [r1, #22]	@ movhi
	bhi	.L22
	ldr	r0, [r10, #28]
	add	r5, r5, #2
	add	r2, r9, r2, lsl #2
	cmp	r5, #199
	add	r4, r4, r0
	strh	r4, [r1, #24]	@ movhi
	ldr	r0, [r10, #28]
	add	r3, r3, r0
	strh	r3, [r2, #22]	@ movhi
	bls	.L23
	b	.L22
.L28:
	ldr	r5, [fp, #-856]
	b	.L18
.L29:
	mov	r5, r6
	b	.L18
	UNWIND(.fnend)
	.size	PostPro_GetH264MbOfMBAFF, .-PostPro_GetH264MbOfMBAFF
	.align	2
	.global	PostPro_GetH264MbGroup
	.type	PostPro_GetH264MbGroup, %function
PostPro_GetH264MbGroup:
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
	ldr	r3, [r1, #12]
	mov	r5, r1
	mov	r6, r0
	sub	ip, r3, #1
	cmp	ip, #199
	bhi	.L55
	ldr	r3, [r0, #28]
	cmp	r2, #0
	ldr	r4, [r0, #32]
	mul	r4, r4, r3
	bne	.L56
.L40:
	mov	r1, #0
	str	r1, [r6, #44]
	str	r1, [r6, #56]
	mvn	ip, #0
	ldr	r3, [r5, #12]
	uxth	r10, r4
	add	r2, r4, ip
	mov	lr, ip
	str	r2, [fp, #-48]
	add	r0, r5, r3, lsl #2
	mov	r3, r5
	strh	r10, [r0, #22]	@ movhi
	strh	r10, [r0, #20]	@ movhi
	b	.L48
.L60:
	cmp	r2, ip
	movlt	ip, lr
	add	r7, ip, #1
	cmp	r2, r7
	ble	.L43
	ldr	r7, [r6, #44]
	cmp	r7, #199
	bgt	.L57
	add	lr, lr, lr, lsr #31
	add	r8, r6, r7, lsl #2
	sub	ip, ip, #100
	add	r7, r7, #1
	sxth	r9, lr
	strh	lr, [r8, #76]	@ movhi
	cmp	ip, r9
	sub	lr, r2, #1
	strgth	ip, [r8, #76]	@ movhi
	strh	lr, [r8, #78]	@ movhi
	str	r7, [r6, #44]
.L43:
	ldr	r7, [r5, #12]
	sub	ip, r7, #1
	cmp	ip, r1
	beq	.L58
.L50:
	add	r1, r1, #1
	mov	ip, r0
	cmp	r1, r7
	mov	lr, r2
	add	r3, r3, #4
	bhi	.L59
.L48:
	ldrh	r2, [r3, #20]
	ldrh	r0, [r3, #22]
	cmp	r2, r4
	cmple	r0, r4
	movgt	r7, #1
	movle	r7, #0
	cmp	r2, r0
	orrgt	r7, r7, #1
	cmp	r7, #0
	beq	.L60
	ldr	r7, [r5, #12]
	add	r1, r1, #1
	add	r3, r3, #4
	cmp	r1, r7
	bls	.L48
.L59:
	mov	r0, #0
.L39:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L58:
	add	ip, r5, r1, lsl #2
	ldr	lr, [fp, #-48]
	ldrh	ip, [ip, #22]
	cmp	ip, lr
	bge	.L50
	ldr	r3, [r6, #44]
	cmp	r3, #199
	bgt	.L61
	add	r2, r6, r3, lsl #2
	sub	r10, r10, #1
	add	r3, r3, #1
	mov	r0, #0
	strh	r10, [r2, #78]	@ movhi
	strh	ip, [r2, #76]	@ movhi
	str	r3, [r6, #44]
	b	.L39
.L56:
	bl	PostPro_GetH264MbOfMBAFF
	b	.L40
.L55:
	mov	r2, r3
	ldr	r1, .L62
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L57:
	movw	r2, #270
	ldr	r1, .L62+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	b	.L39
.L61:
	movw	r2, #295
	ldr	r1, .L62+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	b	.L39
.L63:
	.align	2
.L62:
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetH264MbGroup, .-PostPro_GetH264MbGroup
	.align	2
	.global	PostPro_GetH264RepairParam
	.type	PostPro_GetH264RepairParam, %function
PostPro_GetH264RepairParam:
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
	ldr	r3, [r1, #308]
	mov	r4, r1
	mov	r5, r0
	mov	r1, r2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #324]
	str	r3, [r0, #8]
	ldr	r3, [r4, #944]
	ldr	ip, [r3, #1640]
	add	r3, r4, ip, lsl #2
	ldr	r3, [r3, #324]
	str	r3, [r0, #20]
	ldr	r3, [r4, #316]
	add	r3, r3, #146
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r0, #24]
	ldr	r3, [r4, #44]
	str	r3, [r0, #28]
	ldr	r3, [r4, #36]
	str	r3, [r0, #32]
	ldrb	r3, [r4]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r0, #36]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r0, #40]
	ldr	lr, [r4, #936]
	cmp	lr, #0
	beq	.L65
	ldr	r3, [r4, #1116]
	cmp	r3, ip
	addne	r2, r4, #1104
	movne	r3, #0
	addne	r2, r2, #12
	bne	.L68
	b	.L102
.L69:
	ldr	r0, [r2, #4]!
	cmp	r0, ip
	beq	.L66
.L68:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L69
.L65:
	ldr	r2, [r4, #48]
	ldrsb	r3, [r4, #2]
	cmp	r2, #0
	ldrneb	r2, [r4]	@ zero_extendqisi2
	clzne	r2, r2
	movne	r2, r2, lsr #5
	cmp	r3, #0
	streq	r3, [r1, #12]
	bne	.L103
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	beq	.L104
.L73:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L82
	cmp	r3, #1
	beq	.L100
	cmp	r3, #2
	beq	.L100
	cmp	r3, #3
	bne	.L79
.L82:
	mov	r3, #0
	str	r3, [r5, #52]
.L79:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	mov	r2, #4
	str	r2, [r5, #64]
	strb	r3, [r5]
	ldr	r3, [r4, #720]
	str	r3, [r5, #12]
	ldr	r3, [r4, #724]
	str	r3, [r5, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L100:
	str	r3, [r5, #52]
	b	.L79
.L102:
	mov	r3, #0
.L66:
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #1052]
	str	r3, [r5, #48]
	b	.L65
.L103:
	mov	r0, r5
	bl	PostPro_GetH264MbGroup
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	bne	.L73
.L104:
	ldr	ip, [r4, #580]
	cmp	ip, #0
	beq	.L73
	ldr	r2, [r4, #324]
	cmp	r0, r2
	addeq	r1, r4, #324
	moveq	r3, #0
	bne	.L74
.L76:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L73
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	beq	.L76
.L74:
	str	r2, [r5, #20]
	b	.L73
	UNWIND(.fnend)
	.size	PostPro_GetH264RepairParam, .-PostPro_GetH264RepairParam
	.align	2
	.global	PostPro_GetMVCRepairParam
	.type	PostPro_GetMVCRepairParam, %function
PostPro_GetMVCRepairParam:
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
	ldr	r3, [r1, #308]
	mov	r4, r1
	mov	r5, r0
	mov	r1, r2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #324]
	str	r3, [r0, #8]
	ldr	r3, [r4, #944]
	ldr	ip, [r3, #1640]
	add	r3, r4, ip, lsl #2
	ldr	r3, [r3, #324]
	str	r3, [r0, #20]
	ldr	r3, [r4, #316]
	add	r3, r3, #146
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r0, #24]
	ldr	r3, [r4, #44]
	str	r3, [r0, #28]
	ldr	r3, [r4, #36]
	str	r3, [r0, #32]
	ldrb	r3, [r4]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r0, #36]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r0, #40]
	ldr	lr, [r4, #936]
	cmp	lr, #0
	beq	.L106
	ldr	r3, [r4, #1116]
	cmp	r3, ip
	addne	r2, r4, #1104
	movne	r3, #0
	addne	r2, r2, #12
	bne	.L109
	b	.L143
.L110:
	ldr	r0, [r2, #4]!
	cmp	r0, ip
	beq	.L107
.L109:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L110
.L106:
	ldr	r2, [r4, #48]
	ldrsb	r3, [r4, #2]
	cmp	r2, #0
	ldrneb	r2, [r4]	@ zero_extendqisi2
	clzne	r2, r2
	movne	r2, r2, lsr #5
	cmp	r3, #0
	streq	r3, [r1, #12]
	bne	.L144
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	beq	.L145
.L114:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L123
	cmp	r3, #1
	beq	.L141
	cmp	r3, #2
	beq	.L141
	cmp	r3, #3
	bne	.L120
.L123:
	mov	r3, #0
	str	r3, [r5, #52]
.L120:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	mov	r2, #4
	str	r2, [r5, #64]
	strb	r3, [r5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L141:
	str	r3, [r5, #52]
	b	.L120
.L143:
	mov	r3, #0
.L107:
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #1052]
	str	r3, [r5, #48]
	b	.L106
.L144:
	mov	r0, r5
	bl	PostPro_GetH264MbGroup
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	bne	.L114
.L145:
	ldr	ip, [r4, #580]
	cmp	ip, #0
	beq	.L114
	ldr	r2, [r4, #324]
	cmp	r0, r2
	addeq	r1, r4, #324
	moveq	r3, #0
	bne	.L115
.L117:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L114
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	beq	.L117
.L115:
	str	r2, [r5, #20]
	b	.L114
	UNWIND(.fnend)
	.size	PostPro_GetMVCRepairParam, .-PostPro_GetMVCRepairParam
	.align	2
	.global	PostPro_GetHevcMbGroupOfTile
	.type	PostPro_GetHevcMbGroupOfTile, %function
PostPro_GetHevcMbGroupOfTile:
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
	mov	r9, r2
	ldr	r2, .L202
	mov	r6, r0
	mov	r5, r1
	ldr	r0, [r2]
	cmp	r0, #0
	beq	.L197
	mov	r1, r3, asl #6
	ldr	r2, .L202+4
	sub	r3, r1, r3, asl #3
	mov	r7, #0
	add	r3, r2, r3
	str	r7, [r6, #44]
	ldr	r2, .L202+8
	movw	r0, #17736
	ldr	r1, [r3, #8]
	movt	r0, 7
	str	r7, [r6, #56]
	ldr	r3, [r6, #28]
	ldr	r2, [r2, r1, asl #2]
	ldr	r4, [r6, #32]
	add	r0, r2, r0
	mul	r4, r4, r3
	bl	HEVC_CalcTileMap
	ldr	r8, [r5, #12]
	cmp	r8, r7
	beq	.L155
	ldr	r3, .L202
	mov	lr, r7
	mov	r0, r5
	mov	r7, #1
	ldr	ip, [r3]
.L154:
	ldrh	r3, [r0, #20]
	ldrh	r1, [r0, #22]
	cmp	r3, r1
	mov	r2, r3
	bls	.L153
	b	.L152
.L191:
	ldrh	r3, [r0, #20]
.L153:
	cmp	r4, r3
	blt	.L156
	mov	r3, r2, asl #2
	cmp	r4, r1
	add	r3, r3, #483328
	add	r3, r3, #336
	ldrge	r3, [ip, r3]
	addge	r3, ip, r3
	addge	r3, r3, #630784
	strgeb	r7, [r3, #336]
	ldrgeh	r1, [r0, #22]
.L156:
	add	r2, r2, #1
	cmp	r1, r2
	bcs	.L191
	ldr	r8, [r5, #12]
.L152:
	add	lr, lr, #1
	add	r0, r0, #4
	cmp	r8, lr
	bhi	.L154
.L155:
	ldr	r3, [r9, #2488]
	cmp	r3, #199
	mov	r1, r3
	bhi	.L198
	cmp	r3, #0
	beq	.L157
	ldr	r3, [r9, #3584]
	cmp	r3, #36864
	bcs	.L199
	ldr	r2, .L202
	mov	r8, r9
	str	r6, [fp, #-52]
	mov	r6, r1
	str	r4, [fp, #-48]
	ldr	r7, [r2]
	mov	r2, #0
	mov	r10, r2
.L160:
	ldr	r4, [r9, #3580]
	cmp	r4, r3
	bhi	.L166
	add	r5, r4, #120832
	add	r5, r5, #84
	ldr	r0, [r7, r5, asl #2]
	add	r0, r7, r0
	add	r1, r0, #630784
	ldrb	r1, [r1, #336]	@ zero_extendqisi2
	cmp	r1, #0
	addne	lr, r7, r5, lsl #2
	movne	ip, r4
	bne	.L165
	b	.L163
.L168:
	ldr	r1, [lr, #4]!
	add	r1, r7, r1
	add	r1, r1, #630784
	ldrb	r1, [r1, #336]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L163
.L165:
	add	ip, ip, #1
	cmp	ip, r3
	bls	.L168
.L166:
	add	r2, r2, #1
	cmp	r6, r2
	bls	.L200
.L162:
	add	r9, r9, #8
	ldr	r3, [r9, #3584]
	cmp	r3, #36864
	bcc	.L160
.L158:
	mov	r0, #36864
	ldr	r1, .L202+12
	str	r0, [sp]
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L163:
	ldr	r3, [r9, #3584]
	cmp	r4, r3
	bhi	.L166
	add	r5, r7, r5, lsl #2
	b	.L167
.L194:
	ldr	r0, [r5, #4]!
	add	r0, r7, r0
.L167:
	add	r0, r0, #630784
	add	r4, r4, #1
	strb	r10, [r0, #336]
	ldr	r3, [r9, #3584]
	cmp	r3, r4
	bcs	.L194
	ldr	r6, [r8, #2488]
	add	r2, r2, #1
	cmp	r6, r2
	bhi	.L162
.L200:
	ldr	r4, [fp, #-48]
	ldr	r6, [fp, #-52]
.L157:
	ldr	r3, .L202
	mov	ip, #0
	ldr	lr, [r3]
.L174:
	cmp	ip, r4
	bcs	.L201
	add	r3, lr, ip
	add	r3, r3, #630784
	ldrb	r3, [r3, #336]	@ zero_extendqisi2
	cmp	r3, #1
	addeq	ip, ip, #1
	ldreq	r0, [r6, #44]
	beq	.L170
	add	r2, ip, #630784
	mov	r1, ip
	add	r2, r2, #336
	add	r2, lr, r2
	b	.L172
.L171:
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L173
	mov	r1, r3
.L172:
	add	r3, r1, #1
	cmp	r4, r3
	bhi	.L171
.L173:
	ldr	r2, [r6, #44]
	add	r0, r2, #1
	add	r2, r6, r2, lsl #2
	strh	ip, [r2, #76]	@ movhi
	mov	ip, r3
	strh	r1, [r2, #78]	@ movhi
	str	r0, [r6, #44]
.L170:
	cmp	r0, #199
	ble	.L174
	ldr	r1, .L202+16
	mov	r0, #1
	bl	dprint_vfmw
	sub	r4, r4, #1
	mov	r0, #0
	mov	r3, #1
	strh	r0, [r6, #76]	@ movhi
	strh	r4, [r6, #78]	@ movhi
	str	r3, [r6, #44]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L201:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L198:
	mov	r2, r3
	ldr	r1, .L202+20
	mov	r3, #200
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L197:
	ldr	r2, .L202+24
	ldr	r1, .L202+28
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L199:
	mov	r2, #0
	b	.L158
.L203:
	.align	2
.L202:
	.word	g_pGlbVar
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC4
	.word	.LC5
	.word	.LC3
	.word	.LANCHOR0
	.word	.LC2
	UNWIND(.fnend)
	.size	PostPro_GetHevcMbGroupOfTile, .-PostPro_GetHevcMbGroupOfTile
	.align	2
	.global	PostPro_GetHevcMbGroupOfNoTile
	.type	PostPro_GetHevcMbGroupOfNoTile, %function
PostPro_GetHevcMbGroupOfNoTile:
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
	ldr	r2, .L224
	mov	ip, r3, asl #6
	mov	r8, r0
	sub	r3, ip, r3, asl #3
	mov	ip, #0
	add	r3, r2, r3
	str	ip, [r0, #44]
	ldr	r2, .L224+4
	movw	r0, #17736
	ldr	lr, [r3, #8]
	movt	r0, 7
	str	ip, [r8, #56]
	mov	r7, r1
	ldr	r3, [r8, #28]
	ldr	r2, [r2, lr, asl #2]
	ldr	r4, [r8, #32]
	add	r0, r2, r0
	mul	r4, r4, r3
	bl	HEVC_CalcTileMap
	cmp	r0, #0
	bne	.L218
	ldr	r3, [r7, #12]
	mvn	r5, #0
	uxth	r10, r4
	add	r2, r4, r5
	mov	r6, r5
	str	r2, [fp, #-48]
	add	r1, r7, r3, lsl #2
	mov	r2, r7
	mov	r3, r1
	strh	r10, [r1, #22]	@ movhi
	strh	r10, [r1, #20]	@ movhi
	b	.L214
.L222:
	cmp	ip, r5
	movlt	r5, r6
	add	r3, r5, #1
	cmp	ip, r3
	ble	.L209
	ldr	r3, [r8, #44]
	cmp	r3, #199
	bgt	.L219
	add	r6, r6, r6, lsr #31
	sub	r1, r5, #100
	add	r5, r8, r3, lsl #2
	add	r3, r3, #1
	sxth	r9, r6
	strh	r6, [r5, #76]	@ movhi
	cmp	r1, r9
	sub	r6, ip, #1
	strgth	r1, [r5, #76]	@ movhi
	strh	r6, [r5, #78]	@ movhi
	str	r3, [r8, #44]
.L209:
	ldr	r3, [r7, #12]
	sub	r1, r3, #1
	cmp	r0, r1
	beq	.L220
.L216:
	add	r0, r0, #1
	mov	r5, lr
	cmp	r0, r3
	mov	r6, ip
	add	r2, r2, #4
	bhi	.L221
.L214:
	ldrh	ip, [r2, #20]
	ldrh	lr, [r2, #22]
	cmp	ip, r4
	cmple	lr, r4
	movgt	r3, #1
	movle	r3, #0
	cmp	ip, lr
	orrgt	r3, r3, #1
	cmp	r3, #0
	beq	.L222
	ldr	r3, [r7, #12]
	add	r0, r0, #1
	add	r2, r2, #4
	cmp	r0, r3
	bls	.L214
.L221:
	mov	r0, #0
.L206:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L220:
	ldrh	r1, [r2, #22]
	ldr	r5, [fp, #-48]
	cmp	r1, r5
	bge	.L216
	ldr	r3, [r8, #44]
	cmp	r3, #199
	bgt	.L223
	add	r2, r8, r3, lsl #2
	sub	r10, r10, #1
	add	r3, r3, #1
	mov	r0, #0
	strh	r10, [r2, #78]	@ movhi
	strh	r1, [r2, #76]	@ movhi
	str	r3, [r8, #44]
	b	.L206
.L218:
	ldr	r2, .L224+8
	mov	r0, #1
	ldr	r1, .L224+12
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L219:
	ldr	r2, .L224+8
	mov	r0, #1
	ldr	r1, .L224+16
	bl	dprint_vfmw
	mov	r0, #1
	b	.L206
.L223:
	ldr	r2, .L224+8
	mov	r0, #1
	ldr	r1, .L224+20
	bl	dprint_vfmw
	mov	r0, #1
	b	.L206
.L225:
	.align	2
.L224:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LANCHOR0+32
	.word	.LC6
	.word	.LC7
	.word	.LC8
	UNWIND(.fnend)
	.size	PostPro_GetHevcMbGroupOfNoTile, .-PostPro_GetHevcMbGroupOfNoTile
	.align	2
	.global	PostPro_GetHevcMbGroup
	.type	PostPro_GetHevcMbGroup, %function
PostPro_GetHevcMbGroup:
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
	ldr	ip, [r1, #12]
	mov	r4, r0
	sub	lr, ip, #1
	cmp	lr, #199
	bhi	.L231
	ldr	ip, [r0, #68]
	cmp	ip, #0
	bne	.L232
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	PostPro_GetHevcMbGroupOfNoTile
.L232:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	PostPro_GetHevcMbGroupOfTile
.L231:
	mov	r2, ip
	ldr	r1, .L233
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L234:
	.align	2
.L233:
	.word	.LC0
	UNWIND(.fnend)
	.size	PostPro_GetHevcMbGroup, .-PostPro_GetHevcMbGroup
	.align	2
	.global	PostPro_GetHEVCRepairParam
	.type	PostPro_GetHEVCRepairParam, %function
PostPro_GetHEVCRepairParam:
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
	ldr	r1, [r1, #1288]
	mov	r6, #1
	mov	r5, r0
	add	r1, r1, #336
	ldr	r1, [r4, r1, asl #2]
	str	r1, [r0, #8]
	ldr	r1, [r4, #2492]
	ldr	r1, [r1, #372]
	add	r1, r1, #336
	ldr	r1, [r4, r1, asl #2]
	str	r1, [r0, #20]
	ldr	r1, [r4, #1292]
	add	r1, r4, r1, lsl #2
	ldr	r1, [r1, #1476]
	str	r1, [r0, #24]
	ldr	r1, [r4, #76]
	mov	ip, r6, asl r1
	str	r1, [r0, #64]
	ldrb	lr, [r4]	@ zero_extendqisi2
	strb	lr, [r0]
	ldr	lr, [r4, #196]
	sub	lr, lr, #1
	add	lr, lr, ip
	mov	lr, lr, lsr r1
	str	lr, [r0, #28]
	ldr	lr, [r4, #192]
	sub	lr, lr, #1
	add	ip, lr, ip
	mov	ip, ip, lsr r1
	str	ip, [r0, #32]
	ldrb	r1, [r4, #225]	@ zero_extendqisi2
	str	r6, [r0, #36]
	str	r1, [r0, #68]
	ldr	r1, [r4, #12]
	clz	r1, r1
	mov	r1, r1, lsr #5
	str	r1, [r0, #40]
	ldr	r1, [r4, #1340]
	cmp	r1, #0
	streq	r1, [r2, #12]
	bne	.L248
.L237:
	ldr	r0, [r5, #8]
	ldr	r3, [r5, #20]
	cmp	r0, r3
	beq	.L249
.L238:
	mov	r3, #0
	str	r3, [r5, #52]
	ldr	r3, [r4, #1296]
	str	r3, [r5, #12]
	ldr	r3, [r4, #1300]
	str	r3, [r5, #16]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L249:
	ldr	ip, [r4, #1472]
	cmp	ip, #0
	beq	.L238
	ldr	r2, [r4, #1344]
	cmp	r0, r2
	addeq	r1, r4, #1344
	moveq	r3, #0
	bne	.L239
.L241:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L238
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	beq	.L241
.L239:
	str	r2, [r5, #20]
	b	.L238
.L248:
	mov	r1, r2
	mov	r2, r4
	bl	PostPro_GetHevcMbGroup
	b	.L237
	UNWIND(.fnend)
	.size	PostPro_GetHEVCRepairParam, .-PostPro_GetHEVCRepairParam
	.align	2
	.global	PostPro_CopyYuv_Vp9
	.type	PostPro_CopyYuv_Vp9, %function
PostPro_CopyYuv_Vp9:
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
	movw	r3, #1752
	mul	r9, r3, r1
	add	r5, r0, #270336
	ldr	r10, .L253
	ldr	lr, [r5, #2088]
	ldr	ip, [r5, #2092]
	add	r4, r10, r9
	ldr	r3, [r5, #2440]
	ldr	r6, [r5, #2448]
	ldr	r7, [r5, #2456]
	str	r1, [fp, #-56]
	str	r0, [fp, #-52]
	mov	r0, #22
	str	r2, [fp, #-60]
	mov	r2, lr
	str	r3, [r4, #8]
	mov	r3, ip
	str	r6, [r4, #20]
	mov	r6, #1
	str	r7, [r4, #24]
	mov	r7, #0
	str	lr, [r4, #28]
	str	ip, [r4, #32]
	add	ip, r4, #40
	ldr	r1, .L253+4
	str	r6, [r4, #36]
	str	r7, [r4, #40]
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	ip, .L253+8
	ldr	r3, [r4, #28]
	ldr	lr, [r4, #32]
	ldr	r8, [ip, #136]
	ldrb	ip, [r5, #2081]	@ zero_extendqisi2
	smulbb	r3, lr, r3
	ldr	r0, [r5, #2468]
	strb	ip, [r4, #1]
	cmp	r8, r7
	ldr	ip, [fp, #-48]
	sub	r3, r3, #1
	strb	r0, [r10, r9]
	str	r7, [r4, #48]
	mov	r0, #6
	str	r6, [r4, #56]
	str	r0, [r4, #64]
	moveq	r0, r6
	strh	r3, [r4, #78]	@ movhi
	strh	r7, [r4, #76]	@ movhi
	str	r6, [ip, #4]
	str	r7, [r4, #52]
	beq	.L251
	ldr	r2, [fp, #-60]
	mov	r0, #17
	ldr	r3, [fp, #-56]
	ldr	r1, [fp, #-52]
	str	r2, [sp]
	mov	r2, r7
	blx	r8
	subs	r0, r0, r7
	movne	r0, #1
.L251:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L254:
	.align	2
.L253:
	.word	g_RepairParam
	.word	.LC9
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Vp9, .-PostPro_CopyYuv_Vp9
	.align	2
	.global	PostPro_GetVp9MbGroup
	.type	PostPro_GetVp9MbGroup, %function
PostPro_GetVp9MbGroup:
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
	ldr	r3, [r1, #12]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L268
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	r3, [r0, #44]
	mov	lr, r3
	str	r3, [r0, #56]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #12]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #22]	@ movhi
	strh	r8, [ip, #20]	@ movhi
	b	.L264
.L272:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L260
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L260
	ldr	r2, [r0, #44]
	cmp	r2, #199
	bgt	.L269
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #76]	@ movhi
	strh	r6, [r10, #78]	@ movhi
	str	r2, [r0, #44]
.L260:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L270
.L266:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L271
.L264:
	ldrh	ip, [r3, #20]
	ldrh	r4, [r3, #22]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L272
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L264
.L271:
	mov	r3, #0
.L257:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L270:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #22]
	cmp	r6, r9
	bge	.L266
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L273
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #78]	@ movhi
	strh	r6, [r1, #76]	@ movhi
	str	r2, [r0, #44]
	b	.L257
.L268:
	ldr	r1, .L274
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L269:
	movw	r2, #794
	ldr	r1, .L274+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L257
.L273:
	mov	r2, #808
	ldr	r1, .L274+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L257
.L275:
	.align	2
.L274:
	.word	.LC10
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetVp9MbGroup, .-PostPro_GetVp9MbGroup
	.align	2
	.global	PostPro_GetVP9RepairParam
	.type	PostPro_GetVP9RepairParam, %function
PostPro_GetVP9RepairParam:
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
	add	ip, r1, #270336
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	ldr	r6, [ip, #2440]
	mov	r4, #6
	str	r6, [r0, #8]
	ldr	r2, [ip, #2448]
	str	r2, [r0, #20]
	ldr	r2, [ip, #2456]
	str	r2, [r0, #24]
	ldr	r2, [ip, #2088]
	str	r2, [r0, #28]
	ldr	r2, [ip, #2092]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #2468]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetVp9MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetVP9RepairParam, .-PostPro_GetVP9RepairParam
	.align	2
	.global	PostPro_GetMp24MbGroup
	.type	PostPro_GetMp24MbGroup, %function
PostPro_GetMp24MbGroup:
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
	ldr	r2, [r1, #12]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L297
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r4, [r0, #32]
	str	r3, [r0, #44]
	str	r3, [r0, #56]
	mul	r4, r4, r2
	ldr	r3, [r1, #12]
	cmp	r3, #0
	add	ip, r1, r3, lsl #2
	mov	r2, ip
	uxth	lr, r4
	strh	lr, [ip, #22]	@ movhi
	str	lr, [fp, #-52]
	strh	lr, [r2, #20]	@ movhi
	bne	.L298
.L280:
	mvn	r6, #0
	mov	r3, r1
	add	r2, r4, r6
	mov	r5, r6
	mov	ip, #0
	str	r2, [fp, #-48]
	b	.L289
.L302:
	cmp	r2, lr
	movle	r7, #0
	movgt	r7, #1
	cmp	r2, r5
	orrlt	r7, r7, #1
	cmp	r7, #0
	bne	.L281
	cmp	r2, r6
	movlt	r6, r5
	add	r7, r6, #1
	cmp	r7, r2
	beq	.L285
	add	r5, r5, r5, lsr #31
	sub	r8, r2, #1
	cmp	r5, r8
	bge	.L285
	ldr	r7, [r0, #44]
	cmp	r7, #199
	bgt	.L299
	add	r9, r0, r7, lsl #2
	sxth	r10, r5
	cmp	r6, r10
	add	r7, r7, #1
	strh	r5, [r9, #76]	@ movhi
	strh	r8, [r9, #78]	@ movhi
	strgth	r6, [r9, #76]	@ movhi
	str	r7, [r0, #44]
.L285:
	ldr	r7, [r1, #12]
	sub	r5, r7, #1
	cmp	r5, ip
	beq	.L300
.L291:
	add	ip, ip, #1
	mov	r6, lr
	cmp	ip, r7
	mov	r5, r2
	add	r3, r3, #4
	bhi	.L301
.L289:
	ldrh	r2, [r3, #20]
	ldrh	lr, [r3, #22]
	cmp	r2, r4
	cmple	lr, r4
	ble	.L302
.L281:
	ldr	r7, [r1, #12]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r7
	bls	.L289
.L301:
	mov	r3, #0
.L296:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L300:
	add	r5, r1, ip, lsl #2
	ldr	r6, [fp, #-48]
	ldrh	r5, [r5, #22]
	cmp	r5, r6
	bge	.L291
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L303
	add	r1, r0, r3, lsl #2
	ldr	r2, [fp, #-52]
	strh	r5, [r1, #76]	@ movhi
	sub	ip, r2, #1
	add	r2, r3, #1
	strh	ip, [r1, #78]	@ movhi
	mov	r3, #0
	str	r2, [r0, #44]
	b	.L296
.L298:
	mov	r3, r2
	sub	r2, r4, #10
	ldrh	ip, [r3, #18]
	add	r3, r3, #14
	cmp	ip, r2
	subge	r2, lr, #1
	strgeh	r2, [r3, #4]	@ movhi
	b	.L280
.L297:
	ldr	r1, .L304
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L299:
	mov	r2, #900
	ldr	r1, .L304+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L296
.L303:
	movw	r2, #926
	ldr	r1, .L304+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L296
.L305:
	.align	2
.L304:
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetMp24MbGroup, .-PostPro_GetMp24MbGroup
	.align	2
	.global	PostPro_GetMPEG2RepairParam
	.type	PostPro_GetMPEG2RepairParam, %function
PostPro_GetMPEG2RepairParam:
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
	mov	r3, r0
	ldr	r0, [r1, #188]
	mov	ip, #0
	str	r0, [r3, #8]
	ldr	r0, [r1, #184]
	str	r0, [r3, #20]
	ldr	r0, [r1, #224]
	str	r0, [r3, #24]
	ldrh	r0, [r1, #150]
	str	r0, [r3, #28]
	ldrh	r0, [r1, #146]
	str	r0, [r3, #32]
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	str	ip, [r3, #40]
	sub	r0, r0, #3
	clz	r0, r0
	mov	r0, r0, lsr #5
	str	r0, [r3, #36]
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L310
	cmp	r0, #2
	beq	.L310
	cmp	r0, #3
	streq	ip, [r3, #52]
.L308:
	add	ip, r1, #45056
	mov	r1, r2
	mov	lr, #4
	mov	r0, r3
	ldr	r2, [ip, #240]
	str	lr, [r3, #64]
	strb	r2, [r3]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	PostPro_GetMp24MbGroup
.L310:
	str	r0, [r3, #52]
	b	.L308
	UNWIND(.fnend)
	.size	PostPro_GetMPEG2RepairParam, .-PostPro_GetMPEG2RepairParam
	.align	2
	.global	PostPro_CopyYuv_Mpeg4
	.type	PostPro_CopyYuv_Mpeg4, %function
PostPro_CopyYuv_Mpeg4:
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
	subs	ip, r0, #0
	mov	r3, r1
	beq	.L316
	cmp	r1, #0
	bne	.L317
	ldrh	r6, [ip, #164]
	add	r0, ip, #12288
	ldrh	r5, [ip, #166]
	ldr	r1, .L318
	ldr	r4, .L318+4
	smulbb	lr, r5, r6
	str	r6, [r1, #28]
	str	r5, [r1, #32]
	ldr	r6, [r0, #2288]
	sub	lr, lr, #1
	ldr	r5, [ip, #220]
	strh	lr, [r1, #78]	@ movhi
	ldr	lr, [ip, #228]
	ldr	r4, [r4, #136]
	ldr	r7, [r0, #2372]
	str	r6, [r1, #8]
	cmp	r4, #0
	ldr	r6, [r0, #2300]
	str	r5, [r1, #20]
	str	lr, [r1, #24]
	ldr	r5, [r0, #2304]
	mov	r0, #4
	ldrb	lr, [ip, #159]	@ zero_extendqisi2
	str	r0, [r1, #64]
	mov	r0, #1
	str	r3, [r1, #40]
	strh	r3, [r1, #76]	@ movhi
	str	r3, [r1, #52]
	strb	r7, [r1]
	str	r6, [r1, #12]
	str	r5, [r1, #16]
	strb	lr, [r1, #1]
	str	r0, [r1, #36]
	str	r0, [r1, #44]
	str	r0, [r1, #56]
	beq	.L313
	str	r2, [sp]
	mov	r1, ip
	mov	r2, r3
	mov	r0, #2
	blx	r4
	adds	r0, r0, #0
	movne	r0, #1
.L313:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L317:
	ldr	r2, .L318+8
	mov	r0, #0
	ldr	r1, .L318+12
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L316:
	ldr	r2, .L318+8
	ldr	r1, .L318+16
	bl	dprint_vfmw
	mov	r0, #1
	b	.L313
.L319:
	.align	2
.L318:
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0+64
	.word	.LC12
	.word	.LC11
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Mpeg4, .-PostPro_CopyYuv_Mpeg4
	.align	2
	.global	PostPro_GetMPEG4RepairParam
	.type	PostPro_GetMPEG4RepairParam, %function
PostPro_GetMPEG4RepairParam:
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
	ldr	lr, [r1, #212]
	mov	ip, r1
	add	r4, r1, #12288
	mov	r5, #1
	mov	r1, r2
	mov	r2, #0
	str	lr, [r0, #8]
	mov	lr, #4
	ldr	r6, [ip, #220]
	str	r6, [r0, #20]
	ldr	r6, [ip, #228]
	str	r6, [r0, #24]
	ldrh	r6, [ip, #164]
	str	r6, [r0, #28]
	ldrh	ip, [ip, #166]
	str	r5, [r0, #36]
	str	r2, [r0, #40]
	str	ip, [r0, #32]
	str	r2, [r0, #52]
	ldr	r2, [r4, #2372]
	str	lr, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetMp24MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetMPEG4RepairParam, .-PostPro_GetMPEG4RepairParam
	.align	2
	.global	PostPro_GetAvsMbGroup
	.type	PostPro_GetAvsMbGroup, %function
PostPro_GetAvsMbGroup:
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
	ldr	r2, [r1, #12]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L332
	ldr	lr, [r0, #28]
	mov	r3, #0
	ldr	r4, [r0, #32]
	mvn	r7, #0
	str	r3, [r0, #56]
	mov	ip, r3
	ldr	r2, [r1, #12]
	mov	r9, r3
	mul	r4, r4, lr
	mov	r6, r7
	add	r5, r1, r2, lsl #2
	str	r1, [fp, #-56]
	mov	r8, r0
	add	lr, r4, r7
	str	lr, [fp, #-48]
	mov	r2, r5
	add	lr, r4, r4, lsr #31
	uxth	r10, r4
	strh	r10, [r5, #22]	@ movhi
	mov	lr, lr, asr #1
	str	r10, [fp, #-64]
	add	r3, lr, r7
	str	lr, [fp, #-60]
	str	r3, [fp, #-52]
	mov	r3, r1
	strh	r10, [r2, #20]	@ movhi
	b	.L328
.L335:
	cmp	r2, r7
	movlt	r7, r6
	add	r7, r7, #1
	cmp	r2, r7
	ble	.L326
	ldr	r7, [r8, #44]
	uxth	r5, r9
	rsb	r10, r5, r6, lsr #31
	rsb	r5, r5, r2
	add	r6, r10, r6
	sub	r5, r5, #1
	add	r10, r8, r7, lsl #2
	add	r7, r7, #1
	strh	r6, [r10, #76]	@ movhi
	strh	r5, [r10, #78]	@ movhi
	ldr	r5, [r8, #36]
	str	r7, [r8, #44]
	cmp	r5, #0
	bne	.L326
	ldr	r5, [fp, #-52]
	cmp	r2, r5
	addge	r8, r0, #876
	ldrge	r9, [fp, #-60]
.L326:
	ldr	r5, [r1, #12]
	sub	r6, r5, #1
	cmp	r6, ip
	beq	.L333
.L330:
	add	ip, ip, #1
	mov	r7, lr
	cmp	ip, r5
	mov	r6, r2
	add	r3, r3, #4
	bhi	.L334
.L328:
	ldrh	r2, [r3, #20]
	ldrh	lr, [r3, #22]
	cmp	r2, r4
	cmple	lr, r4
	movgt	r5, #1
	movle	r5, #0
	cmp	r2, lr
	orrgt	r5, r5, #1
	cmp	r5, #0
	beq	.L335
	ldr	r5, [r1, #12]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r5
	bls	.L328
.L334:
	mov	r2, #0
.L323:
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L333:
	add	r6, r1, ip, lsl #2
	ldr	r7, [fp, #-48]
	ldrh	r6, [r6, #22]
	cmp	r6, r7
	bge	.L330
	ldr	r1, [r0, #44]
	mov	r2, #0
	ldr	r3, [fp, #-64]
	add	ip, r1, #1
	add	r1, r0, r1, lsl #2
	sub	r3, r3, #1
	strh	r6, [r1, #76]	@ movhi
	strh	r3, [r1, #78]	@ movhi
	str	ip, [r0, #44]
	b	.L323
.L332:
	ldr	r1, .L336
	mov	r0, #0
	bl	dprint_vfmw
	mov	r2, #1
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L337:
	.align	2
.L336:
	.word	.LC0
	UNWIND(.fnend)
	.size	PostPro_GetAvsMbGroup, .-PostPro_GetAvsMbGroup
	.align	2
	.global	PostPro_GetAVSRepairParam
	.type	PostPro_GetAVSRepairParam, %function
PostPro_GetAVSRepairParam:
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
	add	ip, r1, #12288
	mov	r3, r0
	mov	r6, #0
	ldr	r5, [ip, #2164]
	str	r5, [r0, #8]
	ldr	r10, [ip, #2156]
	str	r10, [r0, #20]
	ldr	r7, [ip, #2168]
	str	r7, [r0, #24]
	ldrh	r8, [r1, #60]
	str	r8, [r0, #28]
	ldrh	r4, [r1, #62]
	str	r4, [r0, #32]
	mov	r9, r4, lsr #1
	ldrb	lr, [r1, #17]	@ zero_extendqisi2
	str	r6, [r0, #40]
	sub	lr, lr, #3
	clz	lr, lr
	mov	lr, lr, lsr #5
	str	lr, [r0, #36]
	ldr	r0, [r2, #4]
	str	r10, [r3, #896]
	add	r5, r0, r5
	str	r5, [r3, #884]
	ldr	r0, [r2, #4]
	str	lr, [r3, #912]
	str	r4, [r3, #908]
	add	r0, r0, r0, lsl #3
	str	r8, [r3, #904]
	str	r6, [r3, #916]
	mla	r0, r9, r0, r7
	str	r0, [r3, #900]
	ldrb	r1, [r1, #17]	@ zero_extendqisi2
	cmp	r1, #3
	streq	r6, [r3, #52]
	beq	.L340
	cmp	r1, #1
	streq	r1, [r3, #52]
.L340:
	ldr	ip, [ip, #2604]
	mov	r1, r2
	mov	r0, r3
	mov	r2, #4
	str	r2, [r3, #64]
	strb	ip, [r3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	PostPro_GetAvsMbGroup
	UNWIND(.fnend)
	.size	PostPro_GetAVSRepairParam, .-PostPro_GetAVSRepairParam
	.align	2
	.global	PostPro_GetAvs2MbGroup
	.type	PostPro_GetAvs2MbGroup, %function
PostPro_GetAvs2MbGroup:
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
	ldr	r2, [r1, #12]
	mov	r8, r0
	cmp	r2, #200
	bhi	.L355
	cmp	r2, #0
	beq	.L356
	ldr	r3, [r0, #28]
	mov	lr, #0
	ldr	r5, [r0, #32]
	mvn	r7, #0
	str	lr, [r0, #56]
	mov	r6, r7
	ldr	r2, [r1, #12]
	mul	r5, r5, r3
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r7
	mov	r2, ip
	uxth	r0, r5
	strh	r0, [ip, #22]	@ movhi
	strh	r0, [ip, #20]	@ movhi
	b	.L351
.L360:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	ip, r6
	beq	.L347
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L347
	ldr	r2, [r8, #44]
	cmp	r2, #199
	bgt	.L357
	add	r10, r8, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #76]	@ movhi
	strh	r6, [r10, #78]	@ movhi
	str	r2, [r8, #44]
.L347:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	lr, r6
	beq	.L358
.L353:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L359
.L351:
	ldrh	ip, [r3, #20]
	ldrh	r4, [r3, #22]
	cmp	r5, ip
	cmpge	r5, r4
	movlt	r2, #1
	movge	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L360
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L351
.L359:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L356:
	mov	r3, #1
	mov	r0, r2
	str	r3, [r8, #56]
	str	r3, [r8, #44]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L358:
	ldrh	r6, [r3, #22]
	cmp	r6, r9
	bge	.L353
	ldr	r2, [r8, #44]
	cmp	r2, #199
	bgt	.L361
	add	r1, r8, r2, lsl #2
	sub	r3, r0, #1
	add	r2, r2, #1
	mov	r0, #0
	strh	r3, [r1, #78]	@ movhi
	strh	r6, [r1, #76]	@ movhi
	str	r2, [r8, #44]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L355:
	ldr	r1, .L362
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L357:
	movw	r2, #1203
	ldr	r1, .L362+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L361:
	movw	r2, #1217
	ldr	r1, .L362+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L363:
	.align	2
.L362:
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetAvs2MbGroup, .-PostPro_GetAvs2MbGroup
	.align	2
	.global	PostPro_GetAVS2RepairParam
	.type	PostPro_GetAVS2RepairParam, %function
PostPro_GetAVS2RepairParam:
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
	ldr	r5, [r1, #92]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r4, #1
	str	r5, [r0, #8]
	ldr	r2, [ip, #400]
	str	r2, [r0, #20]
	ldr	r2, [ip, #240]
	str	r2, [r0, #24]
	ldr	r2, [ip, #108]
	str	r2, [r0, #28]
	ldr	r2, [ip, #112]
	str	r4, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldrb	r2, [ip, #2]	@ zero_extendqisi2
	strb	r2, [r0]
	ldr	r2, [ip, #116]
	str	r2, [r0, #64]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	PostPro_GetAvs2MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetAVS2RepairParam, .-PostPro_GetAVS2RepairParam
	.align	2
	.global	PostPro_CopyYuv_Vc1
	.type	PostPro_CopyYuv_Vc1, %function
PostPro_CopyYuv_Vc1:
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
	subs	lr, r0, #0
	beq	.L375
	cmp	r1, #0
	bne	.L376
	ldrh	r3, [lr, #74]
	sub	r1, r3, #1
	cmp	r1, #2048
	movcc	r6, #16
	bcs	.L377
.L369:
	add	r0, lr, #12288
	ldr	r1, .L378
	ldr	r3, .L378+4
	ldr	r5, [r0, #272]
	ldr	ip, [r0, #268]
	ldr	r7, [r0, #228]
	ldr	r4, [r3, #136]
	mov	r3, #0
	str	ip, [r1, #28]
	smulbb	ip, r5, ip
	ldr	r8, [r0, #108]
	strh	r3, [r1, #76]	@ movhi
	cmp	r4, r3
	str	r5, [r1, #32]
	sub	ip, ip, #1
	strh	ip, [r1, #78]	@ movhi
	ldr	ip, [r0, #100]
	ldr	r5, [r0, #180]
	str	r6, [r1, #60]
	str	r7, [r1, #8]
	ldr	r6, [r0, #260]
	ldr	r7, [r0, #176]
	mov	r0, #1
	str	ip, [r1, #20]
	ldrb	ip, [lr, #71]	@ zero_extendqisi2
	strb	r6, [r1]
	mov	r6, #4
	str	r8, [r1, #24]
	str	r7, [r1, #12]
	str	r6, [r1, #64]
	str	r5, [r1, #16]
	str	r3, [r1, #40]
	str	r3, [r1, #48]
	str	r3, [r1, #52]
	strb	ip, [r1, #1]
	str	r0, [r1, #36]
	str	r0, [r1, #44]
	str	r0, [r1, #56]
	beq	.L367
	str	r2, [sp]
	mov	r1, lr
	mov	r2, r3
	blx	r4
	adds	r0, r0, #0
	movne	r0, #1
.L367:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L377:
	sub	r1, r3, #2048
	sub	r1, r1, #1
	cmp	r1, #2048
	movcc	r6, #32
	bcc	.L369
	sub	r1, r3, #4096
	sub	r1, r1, #1
	cmp	r1, #2048
	movcc	r6, #48
	bcc	.L369
	sub	r3, r3, #6144
	sub	r3, r3, #1
	cmp	r3, #2048
	movcs	r6, #16
	movcc	r6, #64
	b	.L369
.L376:
	mov	r3, r1
	ldr	r2, .L378+8
	ldr	r1, .L378+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L375:
	ldr	r2, .L378+8
	ldr	r1, .L378+16
	bl	dprint_vfmw
	mov	r0, #1
	b	.L367
.L379:
	.align	2
.L378:
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0+88
	.word	.LC12
	.word	.LC13
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Vc1, .-PostPro_CopyYuv_Vc1
	.align	2
	.global	PostPro_GetVc1MbGroup
	.type	PostPro_GetVc1MbGroup, %function
PostPro_GetVc1MbGroup:
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
	ldr	r3, [r1, #12]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L393
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	r3, [r0, #44]
	mov	lr, r3
	str	r3, [r0, #56]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #12]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #22]	@ movhi
	strh	r8, [ip, #20]	@ movhi
	b	.L389
.L397:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L385
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L385
	ldr	r2, [r0, #44]
	cmp	r2, #199
	bgt	.L394
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #76]	@ movhi
	strh	r6, [r10, #78]	@ movhi
	str	r2, [r0, #44]
.L385:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L395
.L391:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L396
.L389:
	ldrh	ip, [r3, #20]
	ldrh	r4, [r3, #22]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L397
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L389
.L396:
	mov	r3, #0
.L382:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L395:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #22]
	cmp	r6, r9
	bge	.L391
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L398
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #78]	@ movhi
	strh	r6, [r1, #76]	@ movhi
	str	r2, [r0, #44]
	b	.L382
.L393:
	ldr	r1, .L399
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L394:
	movw	r2, #1363
	ldr	r1, .L399+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L382
.L398:
	movw	r2, #1379
	ldr	r1, .L399+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L382
.L400:
	.align	2
.L399:
	.word	.LC10
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetVc1MbGroup, .-PostPro_GetVc1MbGroup
	.align	2
	.global	PostPro_GetVC1RepairParam
	.type	PostPro_GetVC1RepairParam, %function
PostPro_GetVC1RepairParam:
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
	add	r6, r1, #12288
	mov	r5, r1
	mov	r7, #0
	mov	r4, r0
	ldr	r3, [r6, #228]
	mov	r1, r2
	str	r3, [r0, #8]
	ldr	r3, [r6, #100]
	str	r3, [r0, #20]
	ldr	r3, [r6, #108]
	str	r3, [r0, #24]
	ldrh	r3, [r5, #78]
	add	r3, r3, #1
	str	r3, [r0, #28]
	ldrh	r3, [r5, #80]
	add	r3, r3, #1
	str	r3, [r0, #32]
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	str	r7, [r0, #40]
	tst	r3, #253
	moveq	r3, #1
	movne	r3, r7
	str	r3, [r0, #36]
	bl	PostPro_GetVc1MbGroup
	ldr	r2, [r4, #36]
	ldrb	r3, [r5, #68]	@ zero_extendqisi2
	cmp	r2, #1
	streq	r7, [r4, #52]
	and	r3, r3, #3
	str	r3, [r4, #48]
	beq	.L403
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L405
.L403:
	mov	r3, #4
	str	r3, [r4, #64]
	ldr	r3, [r6, #260]
	strb	r3, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L405:
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r3, #1
	streq	r3, [r4, #52]
	beq	.L403
	cmp	r3, #1
	moveq	r3, #2
	streq	r3, [r4, #52]
	b	.L403
	UNWIND(.fnend)
	.size	PostPro_GetVC1RepairParam, .-PostPro_GetVC1RepairParam
	.align	2
	.global	PostPro_GetREAL8RepairParam
	.type	PostPro_GetREAL8RepairParam, %function
PostPro_GetREAL8RepairParam:
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
	ldr	r6, [r1, #56]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	mov	r4, #4
	str	r6, [r0, #8]
	ldr	r2, [ip, #52]
	str	r2, [r0, #20]
	ldr	r2, [ip, #68]
	str	r2, [r0, #24]
	ldr	r2, [ip, #4]
	str	r2, [r0, #28]
	ldr	r2, [ip, #8]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #76]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetMp24MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetREAL8RepairParam, .-PostPro_GetREAL8RepairParam
	.align	2
	.global	PostPro_GetREAL9RepairParam
	.type	PostPro_GetREAL9RepairParam, %function
PostPro_GetREAL9RepairParam:
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
	ldr	r6, [r1, #52]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	mov	r4, #4
	str	r6, [r0, #8]
	ldr	r2, [ip, #48]
	str	r2, [r0, #20]
	ldr	r2, [ip, #64]
	str	r2, [r0, #24]
	ldr	r2, [ip, #4]
	str	r2, [r0, #28]
	ldr	r2, [ip, #8]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #72]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetMp24MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetREAL9RepairParam, .-PostPro_GetREAL9RepairParam
	.align	2
	.global	PostPro_GetDivx3MbGroup
	.type	PostPro_GetDivx3MbGroup, %function
PostPro_GetDivx3MbGroup:
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
	ldr	r2, [r1, #12]
	sub	r3, r2, #1
	cmp	r3, #3
	bhi	.L419
	ldr	lr, [r0, #28]
	mov	r3, #0
	ldr	r4, [r0, #32]
	mvn	r7, #0
	str	r3, [r0, #56]
	mov	ip, r3
	ldr	r2, [r1, #12]
	mov	r9, r3
	mul	r4, r4, lr
	mov	r6, r7
	add	r5, r1, r2, lsl #2
	str	r1, [fp, #-56]
	mov	r8, r0
	add	lr, r4, r7
	str	lr, [fp, #-48]
	mov	r2, r5
	add	lr, r4, r4, lsr #31
	uxth	r10, r4
	strh	r10, [r5, #22]	@ movhi
	mov	lr, lr, asr #1
	str	r10, [fp, #-64]
	add	r3, lr, r7
	str	lr, [fp, #-60]
	str	r3, [fp, #-52]
	mov	r3, r1
	strh	r10, [r2, #20]	@ movhi
	b	.L415
.L422:
	cmp	r2, r7
	movlt	r7, r6
	add	r7, r7, #1
	cmp	r2, r7
	ble	.L413
	ldr	r7, [r8, #44]
	uxth	r5, r9
	rsb	r10, r5, r6, lsr #31
	rsb	r5, r5, r2
	add	r6, r10, r6
	sub	r5, r5, #1
	add	r10, r8, r7, lsl #2
	add	r7, r7, #1
	strh	r6, [r10, #76]	@ movhi
	strh	r5, [r10, #78]	@ movhi
	ldr	r5, [r8, #36]
	str	r7, [r8, #44]
	cmp	r5, #0
	bne	.L413
	ldr	r5, [fp, #-52]
	cmp	r2, r5
	addge	r8, r0, #876
	ldrge	r9, [fp, #-60]
.L413:
	ldr	r5, [r1, #12]
	sub	r6, r5, #1
	cmp	r6, ip
	beq	.L420
.L417:
	add	ip, ip, #1
	mov	r7, lr
	cmp	ip, r5
	mov	r6, r2
	add	r3, r3, #4
	bhi	.L421
.L415:
	ldrh	r2, [r3, #20]
	ldrh	lr, [r3, #22]
	cmp	r2, r4
	cmple	lr, r4
	movgt	r5, #1
	movle	r5, #0
	cmp	r2, lr
	orrgt	r5, r5, #1
	cmp	r5, #0
	beq	.L422
	ldr	r5, [r1, #12]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r5
	bls	.L415
.L421:
	mov	r2, #0
.L410:
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L420:
	add	r6, r1, ip, lsl #2
	ldr	r7, [fp, #-48]
	ldrh	r6, [r6, #22]
	cmp	r6, r7
	bge	.L417
	ldr	r1, [r0, #44]
	mov	r2, #0
	ldr	r3, [fp, #-64]
	add	ip, r1, #1
	add	r1, r0, r1, lsl #2
	sub	r3, r3, #1
	strh	r6, [r1, #76]	@ movhi
	strh	r3, [r1, #78]	@ movhi
	str	ip, [r0, #44]
	b	.L410
.L419:
	ldr	r1, .L423
	mov	r0, #0
	bl	dprint_vfmw
	mov	r2, #1
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L424:
	.align	2
.L423:
	.word	.LC0
	UNWIND(.fnend)
	.size	PostPro_GetDivx3MbGroup, .-PostPro_GetDivx3MbGroup
	.align	2
	.global	PostPro_GetDIVX3RepairParam
	.type	PostPro_GetDIVX3RepairParam, %function
PostPro_GetDIVX3RepairParam:
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
	ldr	r6, [r1, #128]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	mov	r4, #4
	str	r6, [r0, #8]
	ldr	r2, [ip, #124]
	str	r2, [r0, #20]
	ldr	r2, [ip, #152]
	str	r2, [r0, #24]
	ldr	r2, [ip, #8]
	str	r2, [r0, #28]
	ldr	r2, [ip, #12]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #160]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetDivx3MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetDIVX3RepairParam, .-PostPro_GetDIVX3RepairParam
	.align	2
	.global	PostPro_CopyYuv_Vp6
	.type	PostPro_CopyYuv_Vp6, %function
PostPro_CopyYuv_Vp6:
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
	subs	ip, r0, #0
	mov	r3, r1
	beq	.L431
	cmp	r1, #0
	bne	.L432
	ldrh	r6, [ip, #54]
	mov	r0, #1
	ldrh	r5, [ip, #56]
	mov	r7, #4
	ldr	r1, .L433
	ldr	r4, .L433+4
	smulbb	lr, r5, r6
	str	r6, [r1, #28]
	str	r5, [r1, #32]
	ldr	r6, [ip, #184]
	sub	lr, lr, #1
	strh	lr, [r1, #78]	@ movhi
	ldr	lr, [ip, #176]
	ldr	r5, [ip, #188]
	ldr	r4, [r4, #136]
	str	lr, [r1, #8]
	ldr	lr, [ip, #212]
	cmp	r4, #0
	strh	r3, [r1, #76]	@ movhi
	str	r3, [r1, #52]
	str	r7, [r1, #64]
	str	r0, [r1, #56]
	str	r6, [r1, #20]
	str	r5, [r1, #24]
	ldr	r6, [ip, #192]
	ldr	r5, [ip, #196]
	strb	lr, [r1]
	ldrb	lr, [ip, #52]	@ zero_extendqisi2
	str	r3, [r1, #40]
	str	r3, [r1, #48]
	str	r6, [r1, #12]
	str	r5, [r1, #16]
	str	r0, [r1, #36]
	str	r0, [r1, #44]
	strb	lr, [r1, #1]
	beq	.L428
	str	r2, [sp]
	mov	r1, ip
	mov	r2, r3
	mov	r0, #10
	blx	r4
	adds	r0, r0, #0
	movne	r0, #1
.L428:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L432:
	ldr	r2, .L433+8
	mov	r0, #0
	ldr	r1, .L433+12
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L431:
	ldr	r2, .L433+8
	ldr	r1, .L433+16
	bl	dprint_vfmw
	mov	r0, #1
	b	.L428
.L434:
	.align	2
.L433:
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0+108
	.word	.LC12
	.word	.LC14
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Vp6, .-PostPro_CopyYuv_Vp6
	.align	2
	.global	PostPro_GetVp6MbGroup
	.type	PostPro_GetVp6MbGroup, %function
PostPro_GetVp6MbGroup:
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
	ldr	r3, [r1, #12]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L448
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	r3, [r0, #44]
	mov	lr, r3
	str	r3, [r0, #56]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #12]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #22]	@ movhi
	strh	r8, [ip, #20]	@ movhi
	b	.L444
.L452:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L440
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L440
	ldr	r2, [r0, #44]
	cmp	r2, #199
	bgt	.L449
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #76]	@ movhi
	strh	r6, [r10, #78]	@ movhi
	str	r2, [r0, #44]
.L440:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L450
.L446:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L451
.L444:
	ldrh	ip, [r3, #20]
	ldrh	r4, [r3, #22]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L452
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L444
.L451:
	mov	r3, #0
.L437:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L450:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #22]
	cmp	r6, r9
	bge	.L446
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L453
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #78]	@ movhi
	strh	r6, [r1, #76]	@ movhi
	str	r2, [r0, #44]
	b	.L437
.L448:
	ldr	r1, .L454
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L449:
	movw	r2, #1656
	ldr	r1, .L454+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L437
.L453:
	movw	r2, #1672
	ldr	r1, .L454+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L437
.L455:
	.align	2
.L454:
	.word	.LC10
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetVp6MbGroup, .-PostPro_GetVp6MbGroup
	.align	2
	.global	PostPro_GetVP6RepairParam
	.type	PostPro_GetVP6RepairParam, %function
PostPro_GetVP6RepairParam:
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
	ldr	r3, [r1, #176]
	mov	r5, r1
	mov	r4, r0
	mov	r6, #0
	mov	r1, r2
	mov	r2, #1
	str	r3, [r0, #8]
	ldr	r3, [r5, #184]
	str	r3, [r0, #20]
	ldr	r3, [r5, #188]
	str	r3, [r0, #24]
	ldrh	r3, [r5, #54]
	str	r3, [r0, #28]
	ldrh	r3, [r5, #56]
	str	r2, [r0, #36]
	str	r6, [r0, #40]
	str	r3, [r0, #32]
	bl	PostPro_GetVp6MbGroup
	str	r6, [r4, #48]
	str	r6, [r4, #52]
	mov	r2, #4
	ldr	r3, [r5, #212]
	str	r2, [r4, #64]
	strb	r3, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	PostPro_GetVP6RepairParam, .-PostPro_GetVP6RepairParam
	.align	2
	.global	PostPro_GetVp8MbGroup
	.type	PostPro_GetVp8MbGroup, %function
PostPro_GetVp8MbGroup:
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
	ldr	r3, [r1, #12]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L470
	ldr	r2, [r0, #28]
	mov	r3, #0
	ldr	r5, [r0, #32]
	mvn	r6, #0
	str	r3, [r0, #44]
	mov	lr, r3
	str	r3, [r0, #56]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #12]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #22]	@ movhi
	strh	r8, [ip, #20]	@ movhi
	b	.L466
.L474:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L462
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L462
	ldr	r2, [r0, #44]
	cmp	r2, #199
	bgt	.L471
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #76]	@ movhi
	strh	r6, [r10, #78]	@ movhi
	str	r2, [r0, #44]
.L462:
	ldr	r2, [r1, #12]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L472
.L468:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L473
.L466:
	ldrh	ip, [r3, #20]
	ldrh	r4, [r3, #22]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L474
	ldr	r2, [r1, #12]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L466
.L473:
	mov	r3, #0
.L459:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L472:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #22]
	cmp	r6, r9
	bge	.L468
	ldr	r3, [r0, #44]
	cmp	r3, #199
	bgt	.L475
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #78]	@ movhi
	strh	r6, [r1, #76]	@ movhi
	str	r2, [r0, #44]
	b	.L459
.L470:
	ldr	r1, .L476
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L471:
	movw	r2, #1756
	ldr	r1, .L476+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L459
.L475:
	movw	r2, #1772
	ldr	r1, .L476+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r3, #1
	b	.L459
.L477:
	.align	2
.L476:
	.word	.LC10
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetVp8MbGroup, .-PostPro_GetVp8MbGroup
	.align	2
	.global	PostPro_GetVP8RepairParam
	.type	PostPro_GetVP8RepairParam, %function
PostPro_GetVP8RepairParam:
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
	ldr	r6, [r1, #3120]
	mov	ip, r1
	mov	r1, r2
	mov	lr, #0
	mov	r5, #1
	mov	r4, #4
	str	r6, [r0, #8]
	ldr	r2, [ip, #3132]
	str	r2, [r0, #20]
	ldr	r2, [ip, #3136]
	str	r2, [r0, #24]
	ldr	r2, [ip, #2788]
	str	r2, [r0, #28]
	ldr	r2, [ip, #2792]
	str	r5, [r0, #36]
	str	lr, [r0, #40]
	str	r2, [r0, #32]
	str	lr, [r0, #52]
	ldr	r2, [ip, #3144]
	str	r4, [r0, #64]
	strb	r2, [r0]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	PostPro_GetVp8MbGroup
	UNWIND(.fnend)
	.size	PostPro_GetVP8RepairParam, .-PostPro_GetVP8RepairParam
	.align	2
	.global	PostPro_SetDecReport
	.type	PostPro_SetDecReport, %function
PostPro_SetDecReport:
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
	ldr	r3, .L498
	mov	r5, r0
	mov	r4, r2
	mov	r6, r1
	mov	r0, r2
	mov	r1, #0
	mov	r2, #824
	ldr	r3, [r3, #48]
	blx	r3
	cmp	r5, #17
	ldrls	pc, [pc, r5, asl #2]
	b	.L480
.L482:
	.word	.L491
	.word	.L491
	.word	.L491
	.word	.L491
	.word	.L480
	.word	.L491
	.word	.L487
	.word	.L480
	.word	.L491
	.word	.L491
	.word	.L491
	.word	.L491
	.word	.L491
	.word	.L491
	.word	.L480
	.word	.L491
	.word	.L491
	.word	.L491
.L487:
	ldrb	r3, [r6, #17]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L497
.L491:
	mov	r3, #0
	mov	r2, #1
	strh	r3, [r4, #20]	@ movhi
	str	r2, [r4, #12]
	strh	r3, [r4, #22]	@ movhi
.L495:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L480:
	movw	r3, #1976
	ldr	r2, .L498+4
	ldr	r1, .L498+8
	mov	r0, #0
	bl	dprint_vfmw
	b	.L495
.L497:
	mov	r3, #0
	mov	r2, #2
	strh	r3, [r4, #20]	@ movhi
	str	r2, [r4, #12]
	strh	r3, [r4, #22]	@ movhi
	ldrh	r2, [r6, #60]
	ldrh	r3, [r6, #62]
	mul	r3, r3, r2
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	strh	r3, [r4, #24]	@ movhi
	ldrh	r2, [r6, #60]
	ldrh	r3, [r6, #62]
	mul	r3, r3, r2
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	strh	r3, [r4, #26]	@ movhi
	b	.L495
.L499:
	.align	2
.L498:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+128
	.word	.LC15
	UNWIND(.fnend)
	.size	PostPro_SetDecReport, .-PostPro_SetDecReport
	.align	2
	.global	PostPro_GetRepairParam
	.type	PostPro_GetRepairParam, %function
PostPro_GetRepairParam:
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
	mov	r8, r3
	mov	r6, r1
	mov	r3, #0
	str	r0, [r1, #4]
	str	r3, [r1, #44]
	str	r3, [r1, #920]
	cmp	r0, #18
	ldrls	pc, [pc, r0, asl #2]
	b	.L501
.L503:
	.word	.L502
	.word	.L504
	.word	.L505
	.word	.L506
	.word	.L501
	.word	.L507
	.word	.L508
	.word	.L501
	.word	.L509
	.word	.L510
	.word	.L511
	.word	.L511
	.word	.L511
	.word	.L512
	.word	.L501
	.word	.L513
	.word	.L514
	.word	.L515
	.word	.L516
.L516:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetAVS2RepairParam
.L517:
	ldr	r5, [r6, #44]
	ldr	r3, [r6, #28]
	ldr	r7, [r6, #32]
	cmp	r5, #0
	mul	r7, r7, r3
	beq	.L518
	mov	r5, #0
	mov	r4, r6
	mov	r9, r5
.L519:
	ldrsh	r3, [r4, #76]
	mov	r0, #22
	ldrsh	r2, [r4, #78]
	add	r9, r9, #1
	ldr	r1, .L533
	add	r4, r4, #4
	bl	dprint_vfmw
	ldrsh	r3, [r4, #74]
	ldrsh	r2, [r4, #72]
	ldr	r1, [r6, #44]
	rsb	r3, r2, r3
	cmp	r1, r9
	add	r3, r3, #1
	add	r5, r5, r3
	bhi	.L519
.L518:
	ldr	ip, [r6, #920]
	cmp	ip, #0
	beq	.L520
	add	r2, r6, #952
	mov	r1, #0
	add	r2, r2, #2
.L521:
	ldrsh	r3, [r2]
	add	r1, r1, #1
	ldrsh	r0, [r2, #-2]
	cmp	r1, ip
	add	r2, r2, #4
	rsb	r3, r0, r3
	add	r3, r3, #1
	add	r5, r5, r3
	bne	.L521
.L520:
	cmp	r7, #0
	beq	.L522
	mov	r0, #100
	mov	r1, r7
	mul	r0, r0, r5
	bl	__aeabi_uidiv
	cmp	r0, #100
	movcc	r4, r0
	movcs	r4, #100
	cmp	r4, #0
	beq	.L522
.L523:
	mov	r3, #0
	str	r3, [r8, #12]
	ldr	ip, [r6, #72]
	mov	r3, r5
	mov	r2, r7
	ldr	r1, .L533+4
	mov	r0, #22
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L502:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetH264RepairParam
	b	.L517
.L504:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetVC1RepairParam
	b	.L517
.L505:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetMPEG4RepairParam
	b	.L517
.L506:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetMPEG2RepairParam
	b	.L517
.L507:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetDIVX3RepairParam
	b	.L517
.L508:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetAVSRepairParam
	b	.L517
.L509:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetREAL8RepairParam
	b	.L517
.L510:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetREAL9RepairParam
	b	.L517
.L511:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetVP6RepairParam
	b	.L517
.L512:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetVP8RepairParam
	b	.L517
.L513:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetMVCRepairParam
	b	.L517
.L514:
	mov	r1, r2
	ldr	r3, [fp, #4]
	mov	r2, r8
	mov	r0, r6
	bl	PostPro_GetHEVCRepairParam
	b	.L517
.L515:
	mov	r1, r2
	mov	r0, r6
	mov	r2, r8
	bl	PostPro_GetVP9RepairParam
	b	.L517
.L501:
	movw	r3, #2068
	ldr	r2, .L533+8
	ldr	r1, .L533+12
	mov	r0, #0
	bl	dprint_vfmw
	b	.L517
.L522:
	ldr	r4, [r6, #72]
	sub	r4, r4, #1
	clz	r4, r4
	mov	r4, r4, lsr #5
	b	.L523
.L534:
	.align	2
.L533:
	.word	.LC16
	.word	.LC17
	.word	.LANCHOR0+152
	.word	.LC15
	UNWIND(.fnend)
	.size	PostPro_GetRepairParam, .-PostPro_GetRepairParam
	.align	2
	.global	PostPro_GetErrRatio
	.type	PostPro_GetErrRatio, %function
PostPro_GetErrRatio:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r3, r0, #0
	beq	.L540
	ldr	ip, .L541
	mov	r2, #12
	mov	r1, #0
	sub	r0, fp, #48
	ldr	r5, [r3]
	ldr	r4, [ip, #48]
	ldr	r7, [r3, #4]
	ldr	r8, [r3, #8]
	blx	r4
	ldr	r3, .L541+4
	mov	r4, #824
	ldr	r1, .L541+8
	movw	r2, #1752
	ldr	r6, .L541+12
	mla	r4, r4, r5, r3
	ldr	r3, [r1, #140]
	str	r7, [fp, #-48]
	cmp	r3, #0
	str	r5, [fp, #-40]
	mla	r6, r2, r5, r6
	str	r4, [fp, #-44]
	beq	.L538
	sub	r0, fp, #48
	blx	r3
.L539:
	str	r5, [sp]
	mov	r3, r4
	mov	r2, r8
	mov	r1, r6
	mov	r0, r7
	bl	PostPro_GetRepairParam
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L538:
	mov	r0, r3
	movw	r2, #2140
	ldr	r1, .L541+16
	bl	dprint_vfmw
	b	.L539
.L540:
	ldr	r1, .L541+20
	bl	dprint_vfmw
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L542:
	.align	2
.L541:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_DecReport
	.word	g_vdm_hal_fun_ptr
	.word	g_RepairParam
	.word	.LC19
	.word	.LC18
	UNWIND(.fnend)
	.size	PostPro_GetErrRatio, .-PostPro_GetErrRatio
	.align	2
	.global	PostPro_SetFullRepair
	.type	PostPro_SetFullRepair, %function
PostPro_SetFullRepair:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r4, r1, #0
	mov	r1, r2
	beq	.L547
	cmp	r2, #0
	bne	.L548
	ldr	ip, .L549
	mov	r2, r4
	ldr	r4, .L549+4
	mov	r5, #1
	str	r1, [sp]
	str	r1, [ip, #12]
	mov	r3, ip
	mov	r1, r4
	str	r5, [ip]
	bl	PostPro_GetRepairParam
	mov	r0, #100
	str	r5, [r4, #56]
	str	r5, [r4, #44]
.L545:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L548:
	mov	r3, r2
	ldr	r1, .L549+8
	ldr	r2, .L549+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L547:
	ldr	r2, .L549+12
	mov	r0, r4
	ldr	r1, .L549+16
	bl	dprint_vfmw
	mov	r0, r4
	b	.L545
.L550:
	.align	2
.L549:
	.word	g_DecReport
	.word	g_RepairParam
	.word	.LC12
	.word	.LANCHOR0+176
	.word	.LC20
	UNWIND(.fnend)
	.size	PostPro_SetFullRepair, .-PostPro_SetFullRepair
	.align	2
	.global	PostPro_GetRepairStratage
	.type	PostPro_GetRepairStratage, %function
PostPro_GetRepairStratage:
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
	cmp	r1, #0
	beq	.L559
	cmp	r0, #0
	beq	.L555
	cmp	r0, #15
	beq	.L555
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L555:
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L559:
	mov	r0, r1
	ldr	r2, .L560
	ldr	r1, .L560+4
	bl	dprint_vfmw
	mov	r0, #2
	ldmfd	sp, {fp, sp, pc}
.L561:
	.align	2
.L560:
	.word	.LANCHOR0+200
	.word	.LC20
	UNWIND(.fnend)
	.size	PostPro_GetRepairStratage, .-PostPro_GetRepairStratage
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14214, %object
	.size	__func__.14214, 29
__func__.14214:
	.ascii	"PostPro_GetHevcMbGroupOfTile\000"
	.space	3
	.type	__func__.14250, %object
	.size	__func__.14250, 31
__func__.14250:
	.ascii	"PostPro_GetHevcMbGroupOfNoTile\000"
	.space	1
	.type	__func__.14326, %object
	.size	__func__.14326, 22
__func__.14326:
	.ascii	"PostPro_CopyYuv_Mpeg4\000"
	.space	2
	.type	__func__.14382, %object
	.size	__func__.14382, 20
__func__.14382:
	.ascii	"PostPro_CopyYuv_Vc1\000"
	.type	__func__.14443, %object
	.size	__func__.14443, 20
__func__.14443:
	.ascii	"PostPro_CopyYuv_Vp6\000"
	.type	__func__.14519, %object
	.size	__func__.14519, 21
__func__.14519:
	.ascii	"PostPro_SetDecReport\000"
	.space	3
	.type	__func__.14549, %object
	.size	__func__.14549, 23
__func__.14549:
	.ascii	"PostPro_GetRepairParam\000"
	.space	1
	.type	__func__.14574, %object
	.size	__func__.14574, 22
__func__.14574:
	.ascii	"PostPro_SetFullRepair\000"
	.space	2
	.type	__func__.14579, %object
	.size	__func__.14579, 26
__func__.14579:
	.ascii	"PostPro_GetRepairStratage\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"DecSliceNum(=%d) out of range!\012\000" )
.LC1:
	ASCII(.ascii	"line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"%s: g_pGlbVar is NULL!\012\000" )
.LC3:
	ASCII(.ascii	"NumSlicePara %d out of range[0 %d).\012\000" )
	.space	3
.LC4:
	ASCII(.ascii	"SliceGroup[%d][1] %d out of range[0 %d).\012\000" )
	.space	2
.LC5:
	ASCII(.ascii	"pRepairParam->ValidGroupNum >(MAX_UP_MSG_SLICE_NUM " )
	ASCII(.ascii	"- 1)\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"%s:call HEVC_CalcTileMap fail!\012\000" )
.LC7:
	ASCII(.ascii	"%s:0 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"%s:1 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"pRepairParam->ImageWidth=%d,pRepairParam->ImageHeig" )
	ASCII(.ascii	"ht=%d\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"DecSliceNum out of range!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"%s pMp4DecParam is null\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"%s VdhId %d invalid!\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"%s pVc1DecParam is null\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"%s pVp6DecParam is null\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"%s %d VidStd Err!\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"pRepairParam[0].MbGroup[i].EndMbn=%d,pRepairParam[0" )
	ASCII(.ascii	"].MbGroup[i].StartMbn=%d\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"total_mbs=%d,err_mbs=%d, ErrFrame_Flag: %d\012\000" )
.LC18:
	ASCII(.ascii	"PostPro_GetErrRatio: pParam = NULL\012\000" )
.LC19:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"%s pDecParam is null\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
