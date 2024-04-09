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
	.file	"mpeg2.c"
	.global	__aeabi_idiv
	.text
	.align	2
	.type	MP2_SetImgFormat, %function
MP2_SetImgFormat:
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
	add	r6, r0, #77824
	add	r3, r0, #110592
	mov	r7, r0
	ldr	r1, [r6, #1440]
	ldr	r0, [r3, #4080]
	ldr	r5, [r6, #2680]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldrb	r3, [r5, #22]	@ zero_extendqisi2
	ldrb	r1, [r5, #27]	@ zero_extendqisi2
	cmp	r3, #4
	ldr	r2, [r4, #160]
	subne	r3, r3, #1
	ldrb	lr, [r5, #9]	@ zero_extendqisi2
	andne	r3, r3, #3
	moveq	r3, #0
	cmp	r1, #0
	ubfx	r2, r2, #10, #2
	orr	r2, r2, lr
	ldr	r0, [r5, #128]
	moveq	ip, #1
	movne	ip, #0
	movne	lr, #4096
	beq	.L33
.L4:
	ldr	r1, [r6, #2680]
	and	r0, r0, #3
	and	r9, r2, #3
	mov	r0, r0, asl #5
	ldr	r1, [r1, #84]
	orr	ip, r0, ip, asl #8
	orr	r2, ip, r9, asl #10
	str	r3, [r4, #152]
	sub	r1, r1, #1
	str	r3, [r4, #156]
	cmp	r1, #2
	orr	r3, r2, r3
	orr	r3, r3, lr
	mov	r0, r4
	ldrls	r8, .L38
	movhi	r1, #0
	movhi	r8, r1
	ldrls	r1, [r8, r1, asl #2]
	andls	r8, r1, #7
	movls	r8, r8, asl #14
	orr	r8, r3, r8
	str	r8, [r4, #160]
	bl	SetAspectRatio
	mov	r3, #3
	str	r3, [r4, #384]
	mov	r2, #1
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	strb	r2, [r4, #379]
	cmp	r3, #3
	moveq	r3, #0
	movne	r3, #4
	strb	r3, [r4, #372]
	ldr	r3, [r7, #4]
	cmp	r3, #0
	streqb	r3, [r4, #379]
	ldrneb	r3, [r3, #144]	@ zero_extendqisi2
	moveq	r2, #32
	moveq	r3, r2
	streq	r2, [r4, #388]
	mov	r2, #1
	strb	r2, [r4, #377]
	strne	r3, [r4, #388]
	str	r3, [r4, #396]
	str	r3, [r4, #392]
	ldr	r3, [r5, #72]
	str	r3, [r4, #188]
	ldr	r2, [r5, #48]
	str	r2, [r4, #164]
	ldr	r3, [r5, #52]
	str	r3, [r4, #168]
	ldr	r1, [r7]
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L34
.L11:
	mov	r1, r3, lsr #1
	mov	r0, r2, lsr #1
	str	r1, [r4, #184]
	str	r0, [r4, #180]
	ldr	r1, [r5, #148]
	cmp	r1, #0
	bne	.L35
.L12:
	str	r2, [r4, #172]
	str	r3, [r4, #176]
.L13:
	ldrb	r3, [r5, #27]	@ zero_extendqisi2
	str	r3, [r4, #484]
	ldrb	r3, [r5, #18]	@ zero_extendqisi2
	str	r3, [r4, #488]
	ldr	r3, [r5, #144]
	str	r3, [r4, #496]
	ldr	r3, [r6, #2680]
	ldr	r7, [r6, #1496]
	ldr	r5, [r6, #1508]
	ldrb	r2, [r3, #22]	@ zero_extendqisi2
	ldr	lr, [r3, #72]
	cmp	r2, #1
	ldr	r1, [r6, #1504]
	ldr	r2, [r6, #1492]
	ldr	ip, [r6, #1488]
	ldr	r0, [r6, #1500]
	ldrne	r3, [r6, #1524]
	beq	.L36
	str	r3, [r4, #492]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L35:
	ldr	r0, [r5, #152]
	cmp	r0, #0
	beq	.L12
	cmp	r2, r1
	movcs	r2, r1
	str	r2, [r4, #172]
	ldr	r2, [r5, #152]
	cmp	r3, r2
	movcs	r3, r2
	str	r3, [r4, #176]
	b	.L13
.L33:
	cmp	lr, #3
	beq	.L37
	ldr	r1, [r6, #1368]
	cmp	r1, #0
	bne	.L6
	sub	lr, lr, #1
	clz	lr, lr
	mov	lr, lr, lsr #5
	mov	lr, lr, asl #12
	b	.L4
.L36:
	cmp	lr, #0
	add	r0, ip, r0
	add	r1, r2, r1
	movgt	r2, #1
	movle	r2, #0
	cmp	r0, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r1, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r2, #0
	beq	.L16
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r0, r0, asl #1
	addeq	r1, r7, r5
	mul	r0, r0, lr
	bl	__aeabi_idiv
	mov	r3, #100
	mul	r0, r3, r0
	add	r3, r0, #1020
	cmp	r0, #0
	add	r3, r3, #3
	movlt	r0, r3
	mov	r3, r0, asr #10
	str	r3, [r6, #1524]
	str	r3, [r4, #492]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L16:
	mov	r3, r2
	str	r2, [r6, #1524]
	str	r3, [r4, #492]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L6:
	subs	lr, lr, #1
	movne	lr, #1
	mov	lr, lr, asl #12
	b	.L4
.L37:
	ldrb	lr, [r5, #10]	@ zero_extendqisi2
	and	lr, lr, #1
	mov	lr, lr, asl #12
	b	.L4
.L34:
	ldr	r2, [r4, #192]
	add	r3, r3, #15
	ldr	r0, [r4, #104]
	mov	r3, r3, lsr #4
	ldr	r1, [r4, #32]
	mov	ip, r2, asl #4
	str	r0, [r4, #88]
	mul	r3, r3, ip
	str	r0, [r4, #120]
	add	ip, r0, r2
	str	r1, [r4, #48]
	str	ip, [r4, #96]
	add	r0, r3, r0
	add	r3, r1, r3
	add	r2, r0, r2
	str	r3, [r4, #36]
	str	r2, [r4, #100]
	str	r0, [r4, #108]
	str	r0, [r4, #92]
	bl	MEM_Phy2Vir
	ldr	r1, [r4, #92]
	ldr	r2, [r4, #164]
	ldr	r3, [r4, #168]
	str	r1, [r4, #124]
	str	r0, [r4, #52]
	b	.L11
.L39:
	.align	2
.L38:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MP2_SetImgFormat, .-MP2_SetImgFormat
	.align	2
	.type	MP2_SearchStartCode.part.1, %function
MP2_SearchStartCode.part.1:
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
	add	r3, r0, #2
	add	ip, r0, r1
.L51:
	cmp	ip, r3
	bls	.L41
.L53:
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bls	.L52
.L47:
	add	r3, r3, #3
	cmp	ip, r3
	bhi	.L53
.L41:
	sub	r0, r1, #3
	ldmfd	sp, {fp, sp, pc}
.L52:
	cmp	r2, #0
	bne	.L44
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #1
	beq	.L51
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #2
	addne	r3, r3, #4
	b	.L51
.L44:
	cmp	r2, #1
	bne	.L51
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L47
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L47
	rsb	r3, r0, r3
	sub	r0, r3, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_SearchStartCode.part.1, .-MP2_SearchStartCode.part.1
	.align	2
	.type	MP2_ExitMb.part.8, %function
MP2_ExitMb.part.8:
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
	ldr	ip, .L55
	mov	r3, #4016
	ldr	r2, .L55+4
	mov	r0, #1
	ldr	r1, .L55+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L56:
	.align	2
.L55:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+12
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_ExitMb.part.8, .-MP2_ExitMb.part.8
	.align	2
	.global	MP2_VerifyMemPara
	.type	MP2_VerifyMemPara, %function
MP2_VerifyMemPara:
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
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_VerifyMemPara, .-MP2_VerifyMemPara
	.align	2
	.global	MP2_ArrangeVHBMem
	.type	MP2_ArrangeVHBMem, %function
MP2_ArrangeVHBMem:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	subs	r4, r0, #0
	beq	.L83
	add	r3, r4, #77824
	ldr	r3, [r3, #2680]
	ldr	r2, [r3, #48]
	ldr	r3, [r3, #52]
	cmp	r2, #31
	bls	.L62
	cmp	r3, #31
	bls	.L62
	ldr	r1, [r4]
	ldr	r0, [r1, #28]
	cmp	r0, #25
	beq	.L84
	mov	r6, r2
	mov	r5, r3
	mov	r8, #5
	mov	r10, #2
	mov	r9, #3
.L70:
	ldr	r7, .L86
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #76
	ldr	r3, [r7, #48]
	blx	r3
	ldr	r2, [r4]
	str	r5, [fp, #-48]
	mov	r3, #0
	str	r6, [fp, #-68]
	ldr	r2, [r2, #28]
	str	r5, [fp, #-64]
	cmp	r2, #24
	str	r6, [fp, #-52]
	strb	r3, [fp, #-75]
	beq	.L75
	uxtb	r3, r10
	strb	r9, [fp, #-72]
	strb	r8, [fp, #-70]
.L78:
	add	r6, r4, #110592
	sub	r1, fp, #76
	strb	r3, [fp, #-69]
	mov	r5, #0
	ldr	r0, [r6, #4080]
	strb	r5, [fp, #-73]
	bl	FSP_ConfigInstance
	subs	r8, r0, #0
	bne	.L76
	ldr	r1, [r4]
	sub	r3, fp, #80
	ldr	r0, [r6, #4080]
	ldr	r2, [r1, #24]
	ldr	r1, [r1, #20]
	bl	FSP_PartitionFsMemory
	cmp	r0, r5
	moveq	r0, #1
	beq	.L81
	ldr	r3, [r7, #68]
	mov	r0, r8
	ldr	r1, .L86+4
	blx	r3
	mov	r0, r8
	b	.L81
.L62:
	ldr	ip, .L86
	mov	r0, #0
	ldr	r1, .L86+8
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
.L81:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L76:
	ldr	r3, [r7, #68]
	mov	r0, r5
	ldr	r1, .L86+12
	blx	r3
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L84:
	ldr	r0, [r1, #776]
	cmp	r0, #0
	bne	.L65
	ldr	r6, [r1, #736]
	ldr	r5, [r1, #740]
	cmp	r2, r6
	bhi	.L67
	cmp	r3, r5
	bhi	.L67
	ldr	r2, [r1, #764]
	ldr	r3, [r1, #760]
	cmp	r2, #0
	add	r9, r3, #2
	beq	.L80
	add	r3, r3, #1
	cmp	r3, #17
	movlt	r10, r3
	movge	r10, #17
.L74:
	ldrb	r8, [r1, #784]	@ zero_extendqisi2
	b	.L70
.L65:
	ldr	r0, [r1, #736]
	ldr	ip, [r1, #740]
	cmp	r2, r0
	bhi	.L72
	cmp	r3, ip
	bhi	.L72
	ldr	r0, [r1, #764]
	mov	r6, r2
	ldr	r10, [r1, #760]
	mov	r5, r3
	cmp	r0, #0
	add	r9, r10, #2
	bne	.L85
.L80:
	mov	r10, #1
	b	.L74
.L75:
	mov	r3, #1
	strb	r8, [fp, #-70]
	strb	r3, [fp, #-72]
	b	.L78
.L72:
	ldr	r1, .L86
	stmia	sp, {r0, ip}
.L82:
	ldr	r4, [r1, #68]
	mov	r0, #0
	ldr	r1, .L86+16
	blx	r4
	mov	r0, #0
	b	.L81
.L85:
	add	r3, r10, #1
	cmp	r3, #17
	movlt	r10, r3
	movge	r10, #17
	b	.L74
.L67:
	ldr	r1, .L86
	str	r5, [sp, #4]
	str	r6, [sp]
	b	.L82
.L83:
	ldr	ip, .L86
	mov	r3, #210
	ldr	r2, .L86+20
	mov	r0, #1
	ldr	r1, .L86+24
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	b	.L81
.L87:
	.align	2
.L86:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC2
	.word	.LC5
	.word	.LC3
	.word	.LANCHOR0+24
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_ArrangeVHBMem, .-MP2_ArrangeVHBMem
	.align	2
	.global	MP2_GetSequenceInfo
	.type	MP2_GetSequenceInfo, %function
MP2_GetSequenceInfo:
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
	subs	r7, r0, #0
	mov	r3, #0
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	beq	.L136
	add	r4, r7, #77824
	ldr	r2, [r4, #1392]
	ldr	r5, [r4, #2680]
	cmp	r2, #1
	ldr	r9, [r4, #2684]
	beq	.L92
	cmp	r2, #2
	bne	.L137
	ldr	r3, [r4, #1356]
	and	r3, r3, #1769472
	cmp	r3, #589824
	beq	.L95
.L94:
	ldr	r3, .L145
	mov	r0, #17
	ldr	r1, .L145+4
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #1392]
	cmp	r3, #1
	beq	.L138
.L97:
	ldr	r3, [r5, #48]
	add	r3, r3, #15
	mov	r3, r3, lsr #4
	str	r3, [r5, #56]
	ldr	r2, [r4, #1392]
	cmp	r2, #2
	beq	.L139
.L98:
	ldr	r1, [r5, #52]
	add	r2, r1, #15
	mov	r2, r2, lsr #4
.L99:
	mov	r0, #0
	str	r2, [r5, #60]
	str	r0, [r5, #64]
	ldr	r0, [r4, #1392]
	cmp	r0, #2
	beq	.L140
.L100:
	ldr	r1, [r4, #1404]
	cmp	r1, #0
	beq	.L101
	ldr	r0, [r9, #56]
	cmp	r3, r0
	beq	.L141
.L101:
	add	r6, r7, #110592
	ldr	r1, [r4, #1436]
	ldr	r0, [r6, #4080]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L104
	ldr	r1, [r8, #212]
	mov	r10, #0
	ldr	r0, [r6, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r8, #216]
	ldr	r0, [r6, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r8, #220]
	ldr	r0, [r6, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r8, #224]
	ldr	r0, [r6, #4080]
	bl	FreeUsdByDec
	str	r10, [r8, #212]
	str	r10, [r8, #216]
	mov	r2, #1
	str	r10, [r8, #220]
	str	r10, [r8, #224]
	ldr	r1, [r4, #1436]
	ldr	r0, [r6, #4080]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1432]
	ldr	r0, [r6, #4080]
	bl	FSP_ClearLogicFs
	str	r10, [r4, #1432]
	str	r10, [r4, #1436]
	ldr	r0, [r6, #4080]
	bl	FSP_GetFspType
	cmp	r0, r10
	bne	.L142
.L104:
	add	r8, r7, #79872
	mov	r3, #0
	add	r8, r8, #640
	str	r3, [r4, #1396]
	ldr	r0, [r6, #4080]
	mov	r1, r8
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r7]
	ldr	r2, [r3, #776]
	cmp	r2, #0
	bne	.L106
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L143
.L106:
	ldr	r3, [r4, #1404]
	cmp	r3, #0
	beq	.L109
	ldr	r3, [r9, #56]
	cmp	r3, #0
	beq	.L109
	ldr	r3, [r9, #60]
	cmp	r3, #0
	beq	.L109
	ldr	r2, .L145
	mov	r3, #0
	mov	r0, #1
	str	r3, [r4, #1404]
	ldr	r1, .L145+8
	ldr	r2, [r2, #68]
	str	r3, [fp, #-72]
	blx	r2
	ldr	r2, .L145+12
	ldr	r10, [r2]
	cmp	r10, #0
	beq	.L109
	ldr	r3, [fp, #-72]
	mov	r1, #120
	ldr	r0, [r6, #4080]
	mov	r2, r3
	blx	r10
.L109:
	ldr	r0, [r6, #4080]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L111
	sub	r3, fp, #56
	sub	r2, fp, #60
	sub	r1, fp, #64
	ldr	r0, [r6, #4080]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r7]
	ldr	r3, [r3, #776]
	cmp	r3, #1
	beq	.L144
.L112:
	mov	r0, r8
	bl	ResetVoQueue
	add	r3, r7, #114688
	mov	r2, #0
	strb	r2, [r3, #1]
.L111:
	mov	r3, #0
	mov	r0, r7
	mov	r1, r3
	str	r3, [r4, #1404]
	str	r3, [r4, #1420]
	bl	MP2_ArrangeVHBMem
	ldr	r3, .L145
	ldr	r1, .L145+16
	ldr	r7, [r3, #68]
	str	r0, [r4, #1404]
	mov	r0, #1
	ldr	r3, [r5, #60]
	ldr	r2, [r5, #56]
	mov	r3, r3, asl #4
	mov	r2, r2, asl #4
	blx	r7
.L107:
	ldr	r3, .L145+12
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L134
	ldr	r1, [r9, #60]
	mov	r3, #8
	ldr	r8, [r9, #56]
	sub	r2, fp, #52
	ldr	lr, [r5, #56]
	ldr	ip, [r5, #60]
	strh	r1, [fp, #-50]	@ movhi
	mov	r1, #2
	ldr	r0, [r6, #4080]
	strh	r8, [fp, #-52]	@ movhi
	strh	lr, [fp, #-48]	@ movhi
	strh	ip, [fp, #-46]	@ movhi
	blx	r7
.L134:
	ldr	r1, [r4, #1404]
.L102:
	str	r1, [r4, #1352]
.L88:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L137:
	ldr	r3, [r4, #1356]
	tst	r3, #3538944
	beq	.L95
	tst	r3, #131072
	mov	r2, #2
	orreq	r3, r3, r2
	streq	r3, [r4, #1356]
	tst	r3, #1048576
	str	r2, [r4, #1392]
	orreq	r3, r3, #16
	streq	r3, [r4, #1356]
	moveq	r2, #2
	movne	r2, #2
	b	.L94
.L95:
	mov	r2, #1
	str	r2, [r4, #1392]
	b	.L94
.L92:
	ldr	r3, [r4, #1356]
	mov	r1, #18
	bfi	r1, r1, #16, #16
	and	r3, r3, r1
	cmp	r3, #1179648
	moveq	r2, #2
	streq	r2, [r4, #1392]
	b	.L94
.L138:
	strb	r3, [r5, #27]
	mov	r1, #3
	strb	r3, [r5, #18]
	mov	r2, #5
	strb	r3, [r5, #11]
	strb	r3, [r5, #28]
	mov	r3, #0
	strb	r1, [r5, #9]
	str	r2, [r5, #144]
	strb	r3, [r5, #12]
	strb	r3, [r5, #13]
	strb	r3, [r5, #14]
	strb	r3, [r5, #15]
	strb	r3, [r5, #8]
	b	.L97
.L140:
	ldrb	r0, [r5, #27]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L100
	add	r0, r1, #31
	add	r1, r1, #15
	mov	r0, r0, lsr #5
	mov	r1, r1, lsr #4
	rsb	r1, r1, r0, lsl #1
	str	r1, [r5, #64]
	b	.L100
.L139:
	ldrb	r2, [r5, #27]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L98
	ldr	r1, [r5, #52]
	add	r2, r1, #31
	mov	r2, r2, lsr #5
	mov	r2, r2, asl #1
	b	.L99
.L144:
	ldr	r2, [fp, #-60]
	ldr	r1, [fp, #-56]
	add	r2, r2, r1
	cmp	r2, #0
	ble	.L112
	add	r7, r7, #114688
	strb	r3, [r7, #1]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L141:
	ldr	r3, [r9, #60]
	cmp	r2, r3
	bne	.L101
	b	.L102
.L142:
	ldr	r0, [r6, #4080]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #1432]
	str	r0, [r4, #1436]
	b	.L104
.L143:
	ldr	r10, [r4, #1404]
	cmp	r10, #0
	bne	.L107
	mov	r0, r8
	bl	ResetVoQueue
	mov	r1, r10
	mov	r0, r7
	bl	MP2_ArrangeVHBMem
	str	r10, [r4, #1420]
	str	r0, [r4, #1404]
	b	.L107
.L136:
	ldr	ip, .L145
	movw	r3, #1282
	ldr	r2, .L145+20
	mov	r0, #1
	ldr	r1, .L145+24
	ldr	r4, [ip, #68]
	blx	r4
	b	.L88
.L146:
	.align	2
.L145:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC7
	.word	g_event_report
	.word	.LC8
	.word	.LANCHOR0+44
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_GetSequenceInfo, .-MP2_GetSequenceInfo
	.align	2
	.global	MP2_ProtocolPPSCheck
	.type	MP2_ProtocolPPSCheck, %function
MP2_ProtocolPPSCheck:
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
	beq	.L174
	add	r4, r0, #77824
	ldr	r3, [r4, #1392]
	ldr	r1, [r4, #2680]
	cmp	r3, #1
	beq	.L150
	cmp	r3, #2
	beq	.L151
	ldr	r3, [r4, #1356]
	orr	r3, r3, #63
	str	r3, [r4, #1356]
	ldrb	r2, [r1, #22]	@ zero_extendqisi2
.L157:
	tst	r3, #24
	beq	.L159
.L175:
	cmp	r2, #3
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L160:
	add	r5, r0, #110592
	orr	r3, r3, #64
	ldr	r1, [r4, #1436]
	str	r3, [r4, #1356]
	ldr	r0, [r5, #4080]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L163
	ldr	r1, [r6, #212]
	mov	r7, #0
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r6, #216]
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r6, #220]
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r6, #224]
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	str	r7, [r6, #212]
	str	r7, [r6, #216]
	mov	r2, #1
	str	r7, [r6, #220]
	str	r7, [r6, #224]
	ldr	r1, [r4, #1436]
	ldr	r0, [r5, #4080]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1432]
	ldr	r0, [r5, #4080]
	bl	FSP_ClearLogicFs
	str	r7, [r4, #1432]
	str	r7, [r4, #1436]
	ldr	r0, [r5, #4080]
	bl	FSP_GetFspType
	cmp	r0, r7
	beq	.L163
	ldr	r0, [r5, #4080]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #1432]
	str	r0, [r4, #1436]
.L163:
	mov	r3, #0
	str	r3, [r4, #1396]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L151:
	ldr	r3, [r4, #1356]
	tst	r3, #1048576
	orreq	r3, r3, #16
	streq	r3, [r4, #1356]
	ldrb	r2, [r1, #22]	@ zero_extendqisi2
	sub	ip, r2, #1
	cmp	ip, #2
	bls	.L157
.L172:
	orr	r3, r3, #8
	str	r3, [r4, #1356]
	tst	r3, #24
	ldrb	r2, [r1, #22]	@ zero_extendqisi2
	bne	.L175
.L159:
	cmp	r2, #1
	biceq	r3, r3, #192
	streq	r3, [r4, #1356]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L150:
	ldrb	r2, [r1, #22]	@ zero_extendqisi2
	sub	r3, r2, #1
	cmp	r3, #3
	ldr	r3, [r4, #1356]
	orrhi	r3, r3, #8
	strhi	r3, [r4, #1356]
	ldrhib	r2, [r1, #22]	@ zero_extendqisi2
	sub	ip, r2, #2
	cmp	ip, #1
	bls	.L176
.L154:
	cmp	r2, #3
	beq	.L177
	tst	r3, #24
	bne	.L160
	b	.L159
.L177:
	ldrb	r2, [r1, #26]	@ zero_extendqisi2
	cmp	r2, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	b	.L172
.L176:
	ldrb	ip, [r1, #24]	@ zero_extendqisi2
	cmp	ip, #0
	orreq	r3, r3, #8
	streq	r3, [r4, #1356]
	ldreqb	r2, [r1, #22]	@ zero_extendqisi2
	b	.L154
.L174:
	ldr	ip, .L178
	movw	r3, #1780
	ldr	r2, .L178+4
	mov	r0, #1
	ldr	r1, .L178+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L179:
	.align	2
.L178:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+64
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_ProtocolPPSCheck, .-MP2_ProtocolPPSCheck
	.align	2
	.global	MP2_GetImageBuffer
	.type	MP2_GetImageBuffer, %function
MP2_GetImageBuffer:
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
	beq	.L194
	add	r5, r4, #110592
	mov	r1, #1
	add	r6, r4, #77824
	ldr	r0, [r5, #4080]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r6, #1440]
	blt	.L195
	mov	r1, r0
	ldr	r0, [r5, #4080]
	bl	FSP_GetLogicFs
	subs	r4, r0, #0
	beq	.L196
	ldr	r5, .L197
	mov	r0, #18
	ldr	r2, [r6, #1440]
	ldr	r1, .L197+4
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r2, [r4, #520]
	cmp	r2, #0
	beq	.L190
	ldr	r3, [r4, #524]
	cmp	r3, #0
	beq	.L190
	ldr	r1, [r4, #528]
	cmp	r1, #0
	beq	.L190
	ldr	ip, [r1, #12]
	mov	r0, #18
	ldr	r3, [r3, #12]
	ldr	r2, [r2, #12]
	ldr	r4, [r5, #68]
	ldr	r1, .L197+8
	str	ip, [sp]
	blx	r4
	mov	r0, #1
.L182:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L190:
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L195:
	ldr	r3, .L197
	mov	r0, #0
	ldr	r1, .L197+12
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r6, #1436]
	ldr	r0, [r5, #4080]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L185
	ldr	r1, [r7, #212]
	mov	r8, #0
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r7, #216]
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r7, #220]
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r7, #224]
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	str	r8, [r7, #212]
	str	r8, [r7, #216]
	mov	r2, #1
	str	r8, [r7, #220]
	str	r8, [r7, #224]
	ldr	r1, [r6, #1436]
	ldr	r0, [r5, #4080]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r6, #1432]
	ldr	r0, [r5, #4080]
	bl	FSP_ClearLogicFs
	str	r8, [r6, #1432]
	str	r8, [r6, #1436]
	ldr	r0, [r5, #4080]
	bl	FSP_GetFspType
	cmp	r0, r8
	beq	.L185
	ldr	r0, [r5, #4080]
	bl	FSP_GetNullLogicFs
	str	r0, [r6, #1432]
	str	r0, [r6, #1436]
.L185:
	add	r1, r4, #79872
	mov	r4, #0
	add	r1, r1, #640
	str	r4, [r6, #1396]
	ldr	r0, [r5, #4080]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L194:
	ldr	ip, .L197
	movw	r3, #1868
	ldr	r2, .L197+16
	mov	r0, #1
	ldr	r1, .L197+20
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L196:
	ldr	r3, .L197
	movw	r2, #1897
	ldr	r1, .L197+24
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	b	.L182
.L198:
	.align	2
.L197:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	.word	.LC12
	.word	.LC9
	.word	.LANCHOR0+88
	.word	.LC1
	.word	.LC10
	UNWIND(.fnend)
	.size	MP2_GetImageBuffer, .-MP2_GetImageBuffer
	.align	2
	.global	MP2_SetVDMInf
	.type	MP2_SetVDMInf, %function
MP2_SetVDMInf:
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
	beq	.L203
	add	r5, r4, #77824
	add	r0, r4, #78848
	add	r0, r0, #576
	ldrb	r3, [r5, #1308]	@ zero_extendqisi2
	ldr	lr, [r5, #1320]
	cmp	r3, #1
	ldr	r3, [r5, #1624]
	ldr	ip, [r5, #1304]
	add	r1, r3, #7
	beq	.L204
	cmp	r3, #0
	add	r2, lr, r3, lsr #3
	ldr	r6, [r5, #1324]
	bic	r2, r2, #3
	movge	r1, r3
	add	r3, r3, lr, lsl #3
	and	r3, r3, #31
	add	r1, ip, r1, asr #3
	str	r1, [r5, #1304]
	bic	r6, r6, #3
	str	r3, [r4, #172]
	str	r2, [r4, #164]
	bl	BsResidBits
	str	r6, [r4, #168]
	str	r0, [r4, #180]
	ldr	r3, [r5, #1324]
	and	r3, r3, #3
	mov	r3, r3, asl #3
	str	r3, [r4, #176]
	ldr	r3, [r5, #1332]
	mov	r3, r3, asl #3
	str	r3, [r4, #184]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L204:
	cmp	r3, #0
	add	r2, lr, r3, lsr #3
	bic	r2, r2, #3
	movge	r1, r3
	add	r3, r3, lr, lsl #3
	and	r3, r3, #31
	add	r1, ip, r1, asr #3
	str	r1, [r5, #1304]
	str	r3, [r4, #172]
	str	r2, [r4, #164]
	bl	BsResidBits
	mov	r3, #0
	str	r3, [r4, #168]
	str	r3, [r4, #176]
	str	r3, [r4, #184]
	str	r0, [r4, #180]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L203:
	ldr	ip, .L205
	movw	r3, #1930
	ldr	r2, .L205+4
	mov	r0, #1
	ldr	r1, .L205+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L206:
	.align	2
.L205:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+108
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_SetVDMInf, .-MP2_SetVDMInf
	.align	2
	.global	MP2_RecordVFMWState
	.type	MP2_RecordVFMWState, %function
MP2_RecordVFMWState:
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
	beq	.L213
	add	ip, r0, #77824
	ldr	r3, [r0]
	add	r0, r0, #110592
	ldr	r1, [ip, #2680]
	ldr	r2, [r1, #48]
	str	r2, [r3, #560]
	ldr	r2, [r1, #52]
	str	r2, [r3, #564]
	ldr	r2, [ip, #2680]
	ldr	r2, [r2, #84]
	sub	r2, r2, #1
	cmp	r2, #2
	ldrls	lr, .L214
	movhi	r2, #0
	ldrls	r2, [lr, r2, asl #2]
	str	r2, [r3, #568]
	mov	r2, #0
	str	r2, [r3, #572]
	str	r2, [r3, #576]
	ldr	lr, [r1, #72]
	str	r2, [r3, #584]
	str	lr, [r3, #580]
	ldr	ip, [ip, #1392]
	sub	ip, ip, #1
	clz	ip, ip
	mov	ip, ip, lsr #5
	str	ip, [r3, #588]
	ldr	ip, [r1, #40]
	str	ip, [r3, #592]
	ldr	r1, [r1, #44]
	str	r1, [r3, #596]
	ldr	r1, [r0, #4084]
	str	r1, [r3, #600]
	ldr	ip, [r0, #4084]
	ldr	r1, [r0, #4088]
	cmp	ip, r1
	rsbge	r2, r1, ip
	str	r2, [r3, #604]
	ldmfd	sp, {fp, sp, pc}
.L213:
	ldr	ip, .L214+4
	movw	r3, #1985
	ldr	r2, .L214+8
	mov	r0, #1
	ldr	r1, .L214+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L215:
	.align	2
.L214:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+124
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_RecordVFMWState, .-MP2_RecordVFMWState
	.align	2
	.global	MP2_GetUsrData
	.type	MP2_GetUsrData, %function
MP2_GetUsrData:
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
	subs	r8, r0, #0
	beq	.L253
	add	r9, r8, #78848
	add	r4, r9, #576
	mov	r0, r4
	bl	BsToNextByte
	mov	r0, r4
	bl	BsResidBits
	add	r10, r0, #7
	cmp	r0, #0
	movlt	r0, r10
	mov	r10, r0, asr #3
	cmp	r10, #0
	ble	.L238
	mov	r5, #0
	ldr	r6, .L257
	mov	r7, r5
	b	.L223
.L254:
	bl	BsGet
	add	r7, r7, #1
	cmp	r7, r10
	strb	r0, [r6, r5]
	add	r5, r5, #1
	beq	.L219
.L223:
	mov	r1, #24
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	bic	r3, r0, #-16777216
	mov	r0, r4
	cmp	r3, #1
	beq	.L220
	cmp	r5, #1024
	blt	.L254
	mov	r1, #8
	mov	r0, r4
	add	r7, r7, #1
	bl	BsGet
	cmp	r7, r10
	bne	.L223
.L219:
	add	r7, r8, #77824
	movw	r3, #1308
	ldrsb	r10, [r7, r3]
	cmp	r10, #0
	beq	.L235
	mov	r3, #0
	str	r3, [fp, #-48]
	ldr	r3, .L257+4
	str	r3, [fp, #-52]
.L224:
	ldr	r3, [r7, #1388]
	cmp	r3, #3
	addle	r4, r8, #110592
	movle	r9, r3
	ble	.L237
.L236:
	add	r6, r9, #344
	add	r4, r8, #110592
	add	r9, r9, #360
	mov	r10, #0
.L228:
	ldr	r1, [r6, #4]!
	ldr	r0, [r4, #4080]
	bl	FreeUsdByDec
	cmp	r6, r9
	str	r10, [r6]
	mov	r2, #0
	bne	.L228
	mov	r9, r2
	str	r2, [r7, #1388]
.L237:
	ldr	r0, [r4, #4080]
	add	r9, r8, r9, lsl #2
	bl	GetUsd
	add	r9, r9, #77824
	str	r0, [r9, #1372]
	ldr	r2, [r7, #1388]
	add	r3, r8, r2, lsl #2
	add	r3, r3, #78848
	add	r3, r3, #72
	ldr	r3, [r3, #276]
	cmp	r3, #0
	beq	.L229
	ldr	r3, [r8]
	add	r0, r0, #1056
	ldr	r1, .L257
	ldrd	r2, [r3, #48]
	strd	r2, [r0]
	ldr	r3, [r9, #1372]
	ldr	r2, [r7, #1360]
	str	r2, [r3, #1040]
	ldr	r3, [r9, #1372]
	str	r5, [r3, #1048]
	ldr	r2, [r7, #2680]
	ldr	r3, [r9, #1372]
	ldrb	r2, [r2, #22]	@ zero_extendqisi2
	strb	r2, [r3, #1024]
	ldr	r3, [r9, #1372]
	ldr	r2, [r4, #4084]
	str	r2, [r3, #1028]
	ldr	r2, [r7, #2680]
	ldr	r3, [r9, #1372]
	ldrb	r2, [r2, #10]	@ zero_extendqisi2
	strb	r2, [r3, #1025]
	ldr	r3, [r7, #1356]
	tst	r3, #524288
	ldr	r3, [r9, #1372]
	movne	r2, #3
	moveq	r2, #1
	str	r2, [r3, #1036]
	ldr	r0, [r9, #1372]
	ldr	r2, [r0, #1048]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r0, #1048]
	ldr	r3, [fp, #-52]
	ldrgt	r0, [r9, #1372]
	ldr	r3, [r3, #52]
	ldrgt	r2, [r0, #1048]
	blx	r3
	ldr	r3, .L257+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L233
	ldr	r2, [r9, #1372]
	mov	r3, #1072
	ldr	r0, [r4, #4080]
	mov	r1, #6
	blx	r5
.L233:
	ldr	r3, [r7, #1388]
	add	r3, r3, #1
	str	r3, [r7, #1388]
.L251:
	ldr	r0, [fp, #-48]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L220:
	add	r7, r8, #77824
	ldr	r2, [r7, #1388]
	cmp	r2, #3
	bgt	.L242
	str	r3, [fp, #-48]
	mov	r9, r2
	ldr	r3, .L257+4
	add	r4, r8, #110592
	str	r3, [fp, #-52]
	b	.L237
.L235:
	movw	r3, #1309
	ldrsb	r6, [r7, r3]
	cmp	r6, #0
	beq	.L239
	ldr	r3, [r7, #1332]
	cmp	r3, #0
	str	r3, [fp, #-48]
	ldr	r3, .L257+4
	str	r3, [fp, #-52]
	beq	.L224
	ldr	r1, .L257+12
	mov	r0, r10
	ldr	r3, [r3, #68]
	mov	r6, #1
	blx	r3
	ldr	r3, [r7, #1328]
	ldr	r1, [r7, #1312]
	mov	r2, #3
	sub	r3, r3, #3
	ldr	r0, [r7, #1316]
	add	r1, r1, r3
	ldr	r3, [fp, #-52]
	sub	r0, r0, #3
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r2, [r7, #1332]
	ldr	r1, [r7, #1316]
	mov	r0, r4
	ldr	r3, [r7, #1324]
	add	r2, r2, #3
	sub	r1, r1, #3
	str	r2, [r7, #1328]
	sub	r3, r3, #3
	str	r1, [r7, #1312]
	str	r3, [r7, #1320]
	strb	r6, [r7, #1308]
	strb	r10, [r7, #1309]
	str	r10, [r7, #1332]
	str	r10, [r7, #1316]
	str	r10, [r7, #1324]
	bl	BsInit
	strb	r6, [r7, #1309]
	strb	r10, [r7, #1308]
	mov	r0, r4
	bl	BsToNextByte
	mov	r0, r4
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #3
	ble	.L240
	sub	r6, r6, #3
	b	.L227
.L256:
	bl	BsGet
	ldr	r3, .L257
	strb	r0, [r3, r5]
	add	r5, r5, #1
.L226:
	add	r10, r10, #1
	cmp	r10, r6
	beq	.L255
.L227:
	mov	r1, #24
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	bic	r3, r0, #-16777216
	mov	r0, r4
	cmp	r3, #1
	beq	.L241
	cmp	r5, #1024
	blt	.L256
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	b	.L226
.L242:
	ldr	r2, .L257+4
	str	r3, [fp, #-48]
	str	r2, [fp, #-52]
	b	.L236
.L239:
	ldr	r3, .L257+4
	str	r6, [fp, #-48]
	str	r3, [fp, #-52]
	b	.L224
.L253:
	ldr	ip, .L257+4
	movw	r3, #2018
	ldr	r2, .L257+16
	mov	r0, #1
	ldr	r1, .L257+20
	ldr	r4, [ip, #68]
	str	r8, [fp, #-48]
	blx	r4
	ldr	r0, [fp, #-48]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L229:
	ldr	r1, [fp, #-52]
	mov	r0, r3
	ldr	r4, [r1, #68]
	ldr	r1, .L257+24
	blx	r4
	b	.L251
.L238:
	mov	r5, #0
	b	.L219
.L241:
	str	r3, [fp, #-48]
	b	.L224
.L255:
	mov	r3, #0
	str	r3, [fp, #-48]
	b	.L224
.L240:
	str	r10, [fp, #-48]
	b	.L224
.L258:
	.align	2
.L257:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC13
	.word	.LANCHOR0+144
	.word	.LC1
	.word	.LC14
	UNWIND(.fnend)
	.size	MP2_GetUsrData, .-MP2_GetUsrData
	.align	2
	.global	next_start_code
	.type	next_start_code, %function
next_start_code:
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
	subs	r7, r0, #0
	beq	.L285
	add	r5, r7, #78848
	add	r5, r5, #576
	mov	r0, r5
	bl	BsToNextByte
	mov	r0, r5
	bl	BsGetNextBytePtr
	mov	r4, r0
	mov	r0, r5
	bl	BsResidBits
	add	r1, r0, #7
	cmp	r0, #0
	movlt	r0, r1
	mov	r1, r0, asr #3
	cmp	r1, #4
	movle	r1, #0
	bgt	.L286
.L262:
	mov	r0, r5
	bl	BsLongSkip
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #3
	subgt	r6, r6, #3
	movgt	r4, #0
	bgt	.L267
	b	.L268
.L266:
	bl	BsSkip
	cmp	r4, r6
	beq	.L268
.L267:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, #1
	mov	r0, r5
	bne	.L266
.L270:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L268:
	add	r7, r7, #77824
	movw	r3, #1308
	ldrsb	r4, [r7, r3]
	cmp	r4, #0
	bne	.L265
	ldrb	r3, [r7, #1309]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L265
	ldr	r3, [r7, #1332]
	cmp	r3, #0
	beq	.L265
	ldr	r8, .L289
	mov	r0, #7
	ldr	r1, .L289+4
	mov	r6, #1
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r3, [r7, #1328]
	ldr	r1, [r7, #1312]
	mov	r2, #3
	ldr	r0, [r7, #1316]
	sub	r3, r3, #3
	add	r1, r1, r3
	ldr	r8, [r8, #52]
	sub	r0, r0, #3
	blx	r8
	ldr	r2, [r7, #1332]
	ldr	r1, [r7, #1316]
	mov	r0, r5
	ldr	r3, [r7, #1324]
	add	r2, r2, #3
	sub	r1, r1, #3
	str	r2, [r7, #1328]
	sub	r3, r3, #3
	str	r1, [r7, #1312]
	str	r3, [r7, #1320]
	strb	r6, [r7, #1308]
	strb	r4, [r7, #1309]
	str	r4, [r7, #1332]
	str	r4, [r7, #1316]
	str	r4, [r7, #1324]
	bl	BsInit
	strb	r6, [r7, #1309]
	strb	r4, [r7, #1308]
	mov	r0, r5
	bl	BsToNextByte
	mov	r0, r5
	bl	BsGetNextBytePtr
	mov	r6, r0
	mov	r0, r5
	bl	BsResidBits
	add	r1, r0, #7
	cmp	r0, #0
	movlt	r0, r1
	mov	r1, r0, asr #3
	cmp	r1, #4
	movle	r1, r4
	bgt	.L287
.L269:
	mov	r0, r5
	bl	BsLongSkip
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #3
	ble	.L265
	sub	r6, r6, #3
	mov	r4, #0
	b	.L271
.L288:
	bl	BsSkip
	cmp	r4, r6
	beq	.L265
.L271:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, #1
	mov	r0, r5
	bne	.L288
	b	.L270
.L265:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L286:
	mov	r0, r4
	bl	MP2_SearchStartCode.part.1
	mov	r1, r0, asl #3
	b	.L262
.L285:
	ldr	ip, .L289
	movw	r3, #2207
	ldr	r2, .L289+8
	mov	r0, #1
	ldr	r1, .L289+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L287:
	mov	r0, r6
	bl	MP2_SearchStartCode.part.1
	mov	r1, r0, asl #3
	b	.L269
.L290:
	.align	2
.L289:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LANCHOR0+160
	.word	.LC1
	UNWIND(.fnend)
	.size	next_start_code, .-next_start_code
	.align	2
	.global	GetSliceHdr
	.type	GetSliceHdr, %function
GetSliceHdr:
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
	subs	r6, r0, #0
	addne	r5, r6, #78848
	addne	r7, r6, #77824
	addne	r5, r5, #576
	bne	.L294
	b	.L306
.L300:
	bl	BsShow
	mov	r4, r0
	mov	r0, r5
	bl	BsPos
	sub	r3, r4, #256
	sub	r3, r3, #1
	mov	r1, #32
	cmp	r3, #174
	str	r0, [r7, #1416]
	mov	r0, r5
	bls	.L307
	bl	BsSkip
.L294:
	mov	r0, r6
	bl	next_start_code
	mov	r1, #32
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	beq	.L300
	cmn	r3, #1
	beq	.L296
.L301:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L307:
	bl	BsResidBits
	cmp	r0, #40
	ble	.L296
	ldr	r3, [r7, #1352]
	mov	r2, #0
	str	r2, [r7, #1412]
	cmp	r3, r2
	bne	.L299
	mov	r0, r6
	bl	MP2_GetSequenceInfo
	ldr	r3, [r7, #1404]
	cmp	r3, #0
	beq	.L301
.L299:
	mov	r0, r6
	bl	MP2_ProtocolPPSCheck
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L296:
	ldr	r3, .L308
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L302
	add	r0, r6, #110592
	mov	r3, #0
	mov	r2, r3
	mov	r1, #113
	ldr	r0, [r0, #4080]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L302:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L306:
	ldr	ip, .L308+4
	movw	r3, #667
	ldr	r2, .L308+8
	mov	r0, #1
	ldr	r1, .L308+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L309:
	.align	2
.L308:
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+176
	.word	.LC1
	UNWIND(.fnend)
	.size	GetSliceHdr, .-GetSliceHdr
	.align	2
	.global	sequence_header
	.type	sequence_header, %function
sequence_header:
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
	subs	r5, r0, #0
	beq	.L327
	add	r4, r5, #78848
	add	r7, r5, #77824
	add	r6, r4, #576
	mov	r2, #65536
	mov	r3, #0
	str	r2, [r7, #1356]
	str	r3, [r7, #1352]
	mov	r1, #12
	mov	r0, r6
	ldr	r8, [r7, #2680]
	bl	BsGet
	mov	r1, #12
	str	r0, [r8, #48]
	mov	r0, r6
	bl	BsGet
	mov	r1, #4
	str	r0, [r8, #52]
	mov	r0, r6
	bl	BsGet
	mov	r1, #4
	str	r0, [r8, #84]
	mov	r0, r6
	bl	BsGet
	mov	r1, #18
	str	r0, [r8, #88]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #92]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	beq	.L328
.L313:
	mov	r1, #10
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #96]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #1]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	str	r0, [r8, #76]
	beq	.L320
	ldr	r3, .L329
	add	r2, r4, #604
	add	r1, r3, #64
	str	r1, [fp, #-48]
	mov	r0, r1
.L316:
	ldrb	r1, [r3, #1]!	@ zero_extendqisi2
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L316
.L315:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	str	r0, [r8, #80]
	beq	.L321
	add	r5, r5, #79872
	add	r3, r4, #860
	add	r5, r5, #92
	mov	r2, #16
.L318:
	str	r2, [r3, #4]!
	cmp	r3, r5
	bne	.L318
.L319:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L328:
	ldr	r3, [r7, #1356]
	orr	r3, r3, #1
	str	r3, [r7, #1356]
	b	.L313
.L321:
	ldr	r7, [fp, #-48]
	add	r8, r7, #64
.L317:
	mov	r1, #8
	mov	r0, r6
	ldrb	r4, [r7, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r4, #19712
	cmp	r7, r8
	add	r3, r3, #216
	str	r0, [r5, r3, asl #2]
	bne	.L317
	b	.L319
.L320:
	ldr	r3, .L329+4
	add	r9, r3, #64
	mov	r7, r3
	str	r3, [fp, #-48]
.L314:
	mov	r1, #8
	mov	r0, r6
	ldrb	r10, [r7, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r10, #19712
	cmp	r7, r9
	add	r3, r3, #152
	str	r0, [r5, r3, asl #2]
	bne	.L314
	b	.L315
.L327:
	ldr	ip, .L329+8
	movw	r3, #2298
	ldr	r2, .L329+12
	mov	r0, #1
	ldr	r1, .L329+16
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L330:
	.align	2
.L329:
	.word	.LANCHOR2-1
	.word	.LANCHOR2+63
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+188
	.word	.LC1
	UNWIND(.fnend)
	.size	sequence_header, .-sequence_header
	.align	2
	.global	group_of_pictures_header
	.type	group_of_pictures_header, %function
group_of_pictures_header:
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
	beq	.L333
	add	r5, r4, #78848
	add	r7, r4, #77824
	add	r5, r5, #576
	mov	r1, #1
	ldr	r6, [r7, #2680]
	mov	r0, r5
	bl	BsGet
	mov	r1, #5
	strb	r0, [r6, #2]
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #100]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #104]
	mov	r0, r5
	bl	BsSkip
	mov	r0, r5
	mov	r1, #6
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #108]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #112]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #116]
	mov	r0, r5
	bl	BsGet
	add	ip, r7, #1488
	add	lr, r4, #78848
	add	r4, r4, #78848
	add	r4, r4, #488
	mov	r5, #0
	mov	r3, lr
	add	lr, lr, #452
	add	r3, r3, #476
	str	r0, [r6, #120]
	ldmia	ip, {r0, r1, r2}
	stmia	lr, {r0, r1, r2}
	ldmia	r3, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	ldmia	r4, {r0, r1, r2}
	stmia	r3, {r0, r1, r2}
	str	r5, [r7, #1512]
	str	r5, [r7, #1520]
	str	r5, [r7, #1516]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L333:
	ldr	ip, .L334
	movw	r3, #2359
	ldr	r2, .L334+4
	mov	r0, #1
	ldr	r1, .L334+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L335:
	.align	2
.L334:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+204
	.word	.LC1
	UNWIND(.fnend)
	.size	group_of_pictures_header, .-group_of_pictures_header
	.align	2
	.global	extra_bit_information
	.type	extra_bit_information, %function
extra_bit_information:
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
	addne	r4, r4, #78848
	movne	r5, #0
	addne	r4, r4, #576
	bne	.L339
	b	.L342
.L340:
	bl	BsSkip
	mov	r0, r4
	bl	BsResidBits
	add	r5, r5, #1
	cmp	r0, #8
	ble	.L341
.L339:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	cmp	r0, #0
	mov	r0, r4
	bne	.L340
.L341:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L342:
	ldr	ip, .L343
	movw	r3, #2862
	ldr	r2, .L343+4
	mov	r0, #1
	ldr	r1, .L343+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L344:
	.align	2
.L343:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+232
	.word	.LC1
	UNWIND(.fnend)
	.size	extra_bit_information, .-extra_bit_information
	.align	2
	.global	picture_header
	.type	picture_header, %function
picture_header:
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
	subs	r5, r0, #0
	beq	.L350
	add	r2, r5, #77824
	add	r4, r5, #78848
	add	r4, r4, #576
	mov	r1, #10
	ldr	r3, [r2, #1356]
	mov	r0, r4
	ldr	r6, [r2, #2680]
	bic	r3, r3, #3145728
	bic	r3, r3, #56
	orr	r3, r3, #524288
	str	r3, [r2, #1356]
	bl	BsGet
	mov	r1, #3
	str	r0, [r6, #156]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #22]
	mov	r0, r4
	bl	BsGet
	ldrb	r7, [r6, #22]	@ zero_extendqisi2
	sub	r3, r7, #2
	cmp	r3, #1
	str	r0, [r6, #160]
	bls	.L351
.L348:
	cmp	r7, #3
	beq	.L352
.L349:
	mov	r0, r5
	bl	extra_bit_information
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L352:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, r7
	strb	r0, [r6, #25]
	mov	r0, r4
	bl	BsGet
	strb	r0, [r6, #26]
	b	.L349
.L351:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #3
	strb	r0, [r6, #23]
	mov	r0, r4
	bl	BsGet
	ldrb	r7, [r6, #22]	@ zero_extendqisi2
	strb	r0, [r6, #24]
	b	.L348
.L350:
	ldr	ip, .L353
	mov	r3, #2400
	ldr	r2, .L353+4
	mov	r0, #1
	ldr	r1, .L353+8
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L354:
	.align	2
.L353:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+256
	.word	.LC1
	UNWIND(.fnend)
	.size	picture_header, .-picture_header
	.align	2
	.global	copyright_extension
	.type	copyright_extension, %function
copyright_extension:
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
	beq	.L357
	add	r0, r0, #78848
	mov	r1, #32
	add	r0, r0, #576
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
.L357:
	ldr	ip, .L358
	movw	r3, #2894
	ldr	r2, .L358+4
	mov	r0, #1
	ldr	r1, .L358+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L359:
	.align	2
.L358:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+272
	.word	.LC1
	UNWIND(.fnend)
	.size	copyright_extension, .-copyright_extension
	.align	2
	.global	extension
	.type	extension, %function
extension:
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
	subs	r5, r0, #0
	beq	.L451
	add	r6, r5, #77824
	add	r4, r5, #78848
	add	r4, r4, #576
	mov	r2, #0
	ldr	r3, [r6, #2680]
	mov	r1, #4
	mov	r0, r4
	str	r2, [r3, #148]
	str	r2, [r3, #152]
	str	r2, [r3, #128]
	str	r2, [r3, #132]
	str	r2, [r3, #136]
	str	r2, [r3, #140]
	str	r2, [r3, #144]
	bl	BsGet
	sub	r0, r0, #1
	cmp	r0, #9
	ldrls	pc, [pc, r0, asl #2]
	b	.L449
.L364:
	.word	.L363
	.word	.L365
	.word	.L366
	.word	.L367
	.word	.L372
	.word	.L449
	.word	.L369
	.word	.L370
	.word	.L372
	.word	.L372
.L372:
	mov	r0, r4
	mov	r1, #32
	bl	BsSkip
	mov	r5, #1
.L446:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L367:
	mov	r0, r5
	bl	copyright_extension
.L449:
	mov	r5, #1
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L369:
	ldr	r5, [r6, #2680]
	ldr	r3, [r6, #1356]
	orr	r3, r3, #2097152
	str	r3, [r6, #1356]
	ldrb	r3, [r5, #27]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L452
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L453
.L411:
	mov	r8, #1
.L395:
	add	r5, r5, #160
	mov	r7, #0
	b	.L398
.L454:
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #12]
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	beq	.L450
	cmp	r7, r8
	bge	.L449
.L398:
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	add	r7, r7, r1
	str	r0, [r5, #4]!
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	cmp	r0, #0
	mov	r0, r4
	bne	.L454
.L450:
	ldr	r3, [r6, #1356]
	mov	r5, #1
	orr	r3, r3, #32
	str	r3, [r6, #1356]
	b	.L446
.L370:
	ldr	r8, [r6, #2680]
	ldr	r3, [r6, #1356]
	add	r10, r8, #4
	add	r9, r8, #8
	orr	r3, r3, #1048576
	str	r3, [r6, #1356]
.L399:
	mov	r7, r10
	mov	r5, #0
.L401:
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	add	r5, r5, #1
	uxtb	r0, r0
	strb	r0, [r7], #1
	sub	r3, r0, #10
	cmp	r0, #0
	cmpne	r3, #4
	ldrls	r3, [r6, #1356]
	orrls	r3, r3, #16
	strls	r3, [r6, #1356]
	cmp	r5, #2
	bne	.L401
	add	r10, r10, #2
	cmp	r10, r9
	bne	.L399
	mov	r1, r5
	mov	r0, r4
	bl	BsGet
	mov	r1, r5
	strb	r0, [r8, #8]
	mov	r0, r4
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #9]
	cmp	r0, #0
	bne	.L403
	ldr	r3, [r6, #1356]
	mov	r5, #1
	orr	r3, r3, #16
	str	r3, [r6, #1356]
	b	.L446
.L363:
	ldr	r3, [r6, #1356]
	mov	r2, #0
	mov	r1, #8
	str	r2, [r6, #1352]
	orr	r3, r3, #131072
	mov	r0, r4
	str	r3, [r6, #1356]
	ldr	r7, [r6, #2680]
	bl	BsGet
	mov	r1, #1
	str	r0, [r7, #124]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r7, #27]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r7, #28]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	mov	r10, r0
	mov	r0, r4
	bl	BsGet
	mov	r1, #12
	mov	r9, r0
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	mov	r8, r0
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	bne	.L373
	ldr	r3, [r6, #1356]
	mov	r5, #1
	orr	r3, r3, #2
	str	r3, [r6, #1356]
	b	.L446
.L365:
	ldr	r3, [r6, #1356]
	mov	r1, #3
	mov	r0, r4
	ldr	r7, [r6, #2680]
	orr	r3, r3, #262144
	str	r3, [r6, #1356]
	bl	BsGet
	mov	r1, #1
	str	r0, [r7, #128]
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	str	r0, [r7, #132]
	bne	.L455
.L384:
	mov	r1, #14
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r7, #148]
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	bne	.L385
	ldr	r3, [r6, #1356]
	mov	r5, #1
	orr	r3, r3, #4
	str	r3, [r6, #1356]
	b	.L446
.L366:
	mov	r1, #1
	mov	r0, r4
	ldr	r9, [r6, #2680]
	bl	BsGet
	cmp	r0, #1
	str	r0, [r9, #76]
	beq	.L456
.L386:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	cmp	r0, #1
	str	r0, [r9, #80]
	ldreq	r7, .L458
	addeq	r8, r7, #64
	beq	.L388
.L404:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	beq	.L448
	mov	r5, #64
.L391:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	subs	r5, r5, #1
	bne	.L391
.L448:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	beq	.L449
	mov	r5, #64
.L393:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	subs	r5, r5, #1
	bne	.L393
	b	.L449
.L388:
	mov	r1, #8
	mov	r0, r4
	ldrb	r6, [r7, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r6, #19712
	cmp	r7, r8
	add	r3, r3, #216
	str	r0, [r5, r3, asl #2]
	bne	.L388
	b	.L404
.L451:
	ldr	ip, .L458+4
	movw	r3, #2916
	ldr	r2, .L458+8
	mov	r0, #1
	ldr	r1, .L458+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L452:
	ldrb	r3, [r5, #16]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L411
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r8, #2
	movne	r8, #3
	b	.L395
.L385:
	mov	r0, r4
	mov	r1, #14
	bl	BsGet
	mov	r5, #1
	str	r0, [r7, #152]
	b	.L446
.L373:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [fp, #-48]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r7, #29]
	mov	r0, r4
	bl	BsGet
	mov	r1, #5
	strb	r0, [r7, #30]
	mov	r0, r4
	bl	BsGet
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	uxtb	r1, r0
	strb	r0, [r7, #31]
	add	r1, r1, #1
	add	r0, r3, #1
	bl	__aeabi_idiv
	ldr	r1, [r7, #88]
	ldr	r2, .L458+16
	ldr	r3, [r7, #124]
	add	r2, r2, r1, lsl #2
	tst	r3, #128
	ldr	r2, [r2, #304]
	mul	r0, r2, r0
	str	r0, [r7, #72]
	beq	.L374
	and	r3, r3, #15
	cmp	r3, #5
	beq	.L457
.L375:
	ldr	r3, [r7, #48]
	ldr	r2, [r7, #52]
	ubfx	r3, r3, #0, #12
	ubfx	r2, r2, #0, #12
	orr	r10, r3, r10, asl #12
	orr	r9, r2, r9, asl #12
	str	r10, [r7, #48]
	cmp	r9, #0
	cmpne	r10, #0
	str	r9, [r7, #52]
	ldreq	r3, [r6, #1356]
	orreq	r3, r3, #1
	streq	r3, [r6, #1356]
	ldreq	r10, [r7, #48]
	cmp	r10, #8192
	bhi	.L377
	ldr	r3, [r7, #52]
	cmp	r3, #8192
	bls	.L378
.L377:
	ldr	r2, .L458+20
	ldr	r3, [r6, #1356]
	ldr	r4, [r2]
	orr	r3, r3, #1
	str	r3, [r6, #1356]
	cmp	r4, #0
	beq	.L378
	add	r0, r5, #110592
	mov	r3, #0
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r0, #4080]
	blx	r4
.L378:
	ldr	r3, [r7, #92]
	mov	r1, #400
	ldr	r2, [r7, #40]
	add	r8, r3, r8, lsl #18
	str	r8, [r7, #92]
	sub	r0, r2, #4
	ldr	r3, [r7, #96]
	mul	r8, r1, r8
	ldr	r1, [fp, #-48]
	cmp	r0, #1
	add	r3, r3, r1, lsl #10
	str	r3, [r7, #96]
	str	r8, [r7, #68]
	bls	.L380
	ldr	r3, .L458+20
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L381
	add	r0, r5, #110592
	mov	r3, #0
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r0, #4080]
	blx	r4
	ldr	r2, [r7, #40]
.L381:
	ldr	r3, .L458+4
	mov	r0, #1
	ldr	r1, .L458+24
	ldr	r3, [r3, #68]
	blx	r3
.L380:
	ldr	r2, [r7, #44]
	sub	r3, r2, #4
	cmp	r3, #6
	bls	.L449
	ldr	r3, .L458+20
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L383
	add	r5, r5, #110592
	mov	r3, #0
	mov	r2, r3
	mov	r1, #102
	ldr	r0, [r5, #4080]
	blx	r4
	ldr	r2, [r7, #44]
.L383:
	ldr	r3, .L458+4
	mov	r0, #1
	ldr	r1, .L458+28
	mov	r5, #1
	ldr	r3, [r3, #68]
	blx	r3
	b	.L446
.L403:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #10]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #11]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #12]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #13]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #14]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #15]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #16]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #17]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #18]
	mov	r0, r4
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #3]
	cmp	r0, #0
	beq	.L449
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #3
	mov	r5, #1
	strb	r0, [r8, #19]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #20]
	mov	r0, r4
	bl	BsGet
	mov	r1, #7
	strb	r0, [r8, #21]
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	str	r0, [r8, #32]
	mov	r0, r4
	bl	BsGet
	str	r0, [r8, #36]
	b	.L446
.L455:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	str	r0, [r7, #136]
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	str	r0, [r7, #140]
	mov	r0, r4
	bl	BsGet
	str	r0, [r7, #144]
	b	.L384
.L456:
	ldr	r7, .L458
	add	r8, r7, #64
.L387:
	mov	r1, #8
	mov	r0, r4
	ldrb	r6, [r7, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r6, #19712
	cmp	r7, r8
	add	r3, r3, #152
	str	r0, [r5, r3, asl #2]
	bne	.L387
	b	.L386
.L374:
	ubfx	r2, r3, #4, #3
	and	r3, r3, #15
	str	r2, [r7, #40]
	str	r3, [r7, #44]
	b	.L375
.L453:
	ldrb	r3, [r5, #16]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r8, #2
	movne	r8, #3
	b	.L395
.L457:
	mov	r3, #133
	str	r3, [r7, #40]
	mov	r3, #8
	str	r3, [r7, #44]
	b	.L375
.L459:
	.align	2
.L458:
	.word	.LANCHOR2+63
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+292
	.word	.LC1
	.word	.LANCHOR0
	.word	g_event_report
	.word	.LC15
	.word	.LC16
	UNWIND(.fnend)
	.size	extension, .-extension
	.align	2
	.global	MPEG2DEC_Init
	.type	MPEG2DEC_Init, %function
MPEG2DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 904
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #908)
	sub	sp, sp, #908
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r7, r1
	moveq	r8, #1
	movne	r8, #0
	beq	.L467
	ldr	r3, [r1, #688]
	add	r4, r0, #77824
	ldr	r6, .L471
	cmp	r3, #1
	strne	r8, [fp, #-944]
	strne	r8, [fp, #-940]
	beq	.L468
.L463:
	ldr	r10, [r4, #3032]
	movw	r2, #49160
	ldr	r3, [r6, #48]
	movt	r2, 1
	mov	r1, #0
	add	r6, r5, #79872
	mov	r0, r5
	mov	r9, #1
	blx	r3
	add	r0, r6, #640
	str	r10, [r4, #3032]
	add	r10, r5, #110592
	bl	ResetVoQueue
	add	r1, r5, #45056
	str	r7, [r5]
	mov	r2, #0
	add	r3, r6, #256
	mov	ip, #3
	str	r3, [r4, #2684]
	add	r6, r6, #444
	str	r6, [r4, #2680]
	mov	r0, r5
	str	r2, [r10, #4092]
	str	r9, [r4, #1368]
	strb	ip, [r1, #273]
	str	r2, [r4, #1412]
	ldr	r1, [r7, #8]
	str	r2, [r4, #1404]
	str	r2, [fp, #-936]
	str	r1, [r4, #1344]
	bl	VCTRL_GetChanIDByCtx
	ldr	r6, .L471
	ldr	r2, [fp, #-936]
	cmn	r0, #1
	str	r0, [r10, #4080]
	beq	.L469
	ldr	r7, [r7, #688]
	cmp	r7, #1
	movne	r7, r9
	beq	.L470
.L462:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L467:
	ldr	ip, .L471
	movw	r3, #3010
	ldr	r2, .L471+4
	mov	r0, #1
	ldr	r1, .L471+8
	mov	r7, #0
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L470:
	ldr	r2, [fp, #-940]
	add	r5, r5, #78848
	ldr	r3, [r4, #1356]
	sub	r1, fp, #556
	add	r0, r5, #608
	str	r8, [r4, #1352]
	str	r2, [r4, #1392]
	orr	r3, r3, #65536
	ldr	r2, [fp, #-944]
	str	r3, [r4, #1356]
	ldr	r3, [r6, #52]
	str	r2, [r4, #1404]
	mov	r2, #256
	blx	r3
	ldr	r3, [r6, #52]
	sub	r1, fp, #300
	add	r0, r5, #864
	mov	r2, #256
	blx	r3
	ldr	r3, [r6, #52]
	sub	r1, fp, #932
	mov	r2, #188
	ldr	r0, [r4, #2680]
	blx	r3
	ldr	r3, [r6, #52]
	ldr	r0, [r4, #2684]
	mov	r2, #188
	sub	r1, fp, #744
	blx	r3
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L468:
	ldr	ip, [r4, #1392]
	add	r10, r0, #78848
	add	r1, r10, #608
	ldr	r3, [r6, #52]
	mov	r2, #256
	sub	r0, fp, #556
	str	ip, [fp, #-940]
	ldr	ip, [r4, #1404]
	ldr	r8, [r4, #1352]
	str	ip, [fp, #-944]
	blx	r3
	add	r1, r10, #864
	ldr	r3, [r6, #52]
	mov	r2, #256
	sub	r0, fp, #300
	blx	r3
	ldr	r3, [r6, #52]
	ldr	r1, [r4, #2680]
	mov	r2, #188
	sub	r0, fp, #932
	blx	r3
	ldr	r3, [r6, #52]
	ldr	r1, [r4, #2684]
	mov	r2, #188
	sub	r0, fp, #744
	blx	r3
	b	.L463
.L469:
	ldr	r3, [r6, #68]
	mov	r0, r2
	ldr	r1, .L471+12
	mvn	r7, #19
	blx	r3
	b	.L462
.L472:
	.align	2
.L471:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+368
	.word	.LC1
	.word	.LC17
	UNWIND(.fnend)
	.size	MPEG2DEC_Init, .-MPEG2DEC_Init
	.align	2
	.global	MPEG2DEC_Destroy
	.type	MPEG2DEC_Destroy, %function
MPEG2DEC_Destroy:
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
	beq	.L476
	ldr	r3, .L477
	add	r4, r4, #77824
	ldr	r1, .L477+4
	mov	r0, #2
	ldr	r2, [r4, #1364]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L476:
	ldr	ip, .L477
	movw	r3, #3098
	ldr	r2, .L477+8
	mov	r0, #1
	ldr	r1, .L477+12
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L478:
	.align	2
.L477:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC18
	.word	.LANCHOR0+384
	.word	.LC1
	UNWIND(.fnend)
	.size	MPEG2DEC_Destroy, .-MPEG2DEC_Destroy
	.align	2
	.global	MPEG2DEC_RecycleImage
	.type	MPEG2DEC_RecycleImage, %function
MPEG2DEC_RecycleImage:
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
	mov	r4, r1
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #110592
	mov	r2, #0
	ldr	r0, [r5, #4080]
	bl	FSP_SetDisplay
	mov	r1, r4
	ldr	r0, [r5, #4080]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	addne	r4, r0, #208
	addne	r6, r0, #224
	movne	r7, #0
	beq	.L483
.L482:
	ldr	r1, [r4, #4]!
	ldr	r0, [r5, #4080]
	bl	FreeUsdByDec
	cmp	r4, r6
	str	r7, [r4]
	bne	.L482
.L483:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG2DEC_RecycleImage, .-MPEG2DEC_RecycleImage
	.align	2
	.global	MPEG2DEC_GetRemainImg
	.type	MPEG2DEC_GetRemainImg, %function
MPEG2DEC_GetRemainImg:
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
	subs	r4, r0, #0
	beq	.L511
	ldr	r3, [r4]
	ldr	r3, [r3, #12]
	cmp	r3, #1
	beq	.L510
	add	r5, r4, #77824
	add	r6, r4, #110592
	ldr	r1, [r5, #1436]
	ldr	r0, [r6, #4080]
	bl	FSP_GetFsImagePtr
	subs	r9, r0, #0
	beq	.L510
	ldr	r1, [r5, #1436]
	ldr	r0, [r6, #4080]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L508
.L510:
	add	r5, r4, #79872
.L489:
	add	r7, r5, #640
.L494:
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	GetVoLastImageID
.L508:
	mov	r0, r4
	bl	MP2_SetImgFormat
	add	r0, r4, #78848
	add	r3, r0, #344
	add	r2, r9, #212
	add	r0, r0, #360
	mov	ip, #0
.L491:
	ldr	r1, [r3, #4]!
	mov	r8, #0
	add	r2, r2, #4
	cmp	r1, r8
	strne	r1, [r2, #-4]
	cmp	r3, r0
	str	ip, [r3]
	bne	.L491
	str	r8, [r5, #1388]
	add	r5, r4, #79872
	mov	r3, #1
	add	r7, r5, #640
	mov	r2, r3
	str	r3, [r9, #244]
	ldr	r1, [r9, #196]
	ldr	r0, [r6, #4080]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #4080]
	mov	r3, r7
	str	r9, [sp]
	mov	r2, r4
	mov	r1, #3
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L492
	ldr	r1, [r9, #196]
	mov	r0, r4
	bl	MPEG2DEC_RecycleImage
	b	.L494
.L492:
	ldr	r3, [r9, #200]
	cmp	r3, #100
	bhi	.L489
	ldr	r3, [r9, #164]
	cmp	r3, #31
	bls	.L489
	ldr	r3, [r9, #168]
	cmp	r3, #31
	movhi	r0, r8
	bls	.L494
.L505:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L511:
	ldr	ip, .L512
	movw	r3, #3369
	ldr	r2, .L512+4
	mov	r0, #1
	ldr	r1, .L512+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L505
.L513:
	.align	2
.L512:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+404
	.word	.LC1
	UNWIND(.fnend)
	.size	MPEG2DEC_GetRemainImg, .-MPEG2DEC_GetRemainImg
	.align	2
	.global	MPEG2DEC_GetImageBuffer
	.type	MPEG2DEC_GetImageBuffer, %function
MPEG2DEC_GetImageBuffer:
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
	beq	.L526
	add	r3, r4, #45056
	ldrb	r3, [r3, #273]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L517
	add	r3, r4, #77824
	ldr	r3, [r3, #1368]
	cmp	r3, #0
	beq	.L518
.L517:
	add	r5, r4, #110592
	ldr	r0, [r5, #4080]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L518
	ldr	r0, [r5, #4080]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L527
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L518:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L527:
	add	r1, r4, #79872
	ldr	r0, [r5, #4080]
	add	r1, r1, #640
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L526:
	ldr	ip, .L528
	movw	r3, #3658
	ldr	r2, .L528+4
	mov	r0, #1
	ldr	r1, .L528+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L529:
	.align	2
.L528:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+428
	.word	.LC1
	UNWIND(.fnend)
	.size	MPEG2DEC_GetImageBuffer, .-MPEG2DEC_GetImageBuffer
	.align	2
	.global	MP2_ClearCurPacket
	.type	MP2_ClearCurPacket, %function
MP2_ClearCurPacket:
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
	cmp	r0, #15
	mov	r5, r0
	mov	r4, r1
	ldrhi	ip, .L539
	movwhi	r3, #3787
	bhi	.L537
	cmp	r1, #0
	beq	.L538
	ldr	r1, [r1, #28]
	bl	SM_ReleaseStreamSeg
	ldrsb	r3, [r4]
	cmp	r3, #1
	beq	.L533
	mov	r0, r5
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
.L533:
	ldr	r3, .L539
	mov	r0, r4
	mov	r2, #36
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L538:
	ldr	ip, .L539
	movw	r3, #3788
.L537:
	ldr	r2, .L539+4
	mov	r0, #1
	ldr	r1, .L539+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L540:
	.align	2
.L539:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+452
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_ClearCurPacket, .-MP2_ClearCurPacket
	.align	2
	.global	MP2_ReceivePacket
	.type	MP2_ReceivePacket, %function
MP2_ReceivePacket:
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
	cmp	r2, #15
	mov	r4, r1
	ldrhi	ip, .L551
	movwhi	r3, #3735
	bhi	.L548
	clz	r6, r1
	mov	r6, r6, lsr #5
	cmp	r0, #0
	movne	r5, r6
	orreq	r5, r6, #1
	cmp	r5, #0
	bne	.L549
	cmp	r6, #0
	bne	.L550
	add	r3, r0, #32768
	str	r6, [r3, #1032]
	ldr	r1, [r1, #12]
	str	r1, [r3, #1076]
	ldr	r1, [r4, #8]
	str	r1, [r3, #1048]
	ldr	r1, [r4]
	str	r1, [r3, #1040]
	ldr	r1, [r4, #12]
	str	r1, [r3, #1056]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	strb	r1, [r3, #1036]
	ldr	r1, [r4, #16]
	str	r1, [r3, #1064]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L546
	ldr	r1, [r4, #88]
	str	r1, [r3, #1052]
	ldr	r1, [r4, #80]
	str	r1, [r3, #1044]
	ldr	r1, [r4, #92]
	str	r1, [r3, #1060]
	ldrb	r1, [r4, #85]	@ zero_extendqisi2
	strb	r1, [r3, #1037]
	ldr	r1, [r4, #96]
	str	r1, [r3, #1068]
	ldrb	r3, [r4, #85]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L547
	add	r1, r0, #33792
	mov	r0, r2
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	ldr	r3, .L551
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	mov	r0, #1
	ldr	r1, .L551+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L549:
	ldr	ip, .L551
	movw	r3, #3736
.L548:
	ldr	r2, .L551+8
	mov	r0, #1
	ldr	r1, .L551+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L547:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L546:
	str	r6, [r3, #1052]
	mov	r0, r1
	str	r6, [r3, #1044]
	str	r6, [r3, #1060]
	strb	r6, [r3, #1037]
	str	r6, [r3, #1068]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L550:
	ldr	r3, .L551
	add	r2, r0, #32768
	ldr	r1, .L551+16
	mov	r0, #1
	ldr	r2, [r2, #1092]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L552:
	.align	2
.L551:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	.word	.LANCHOR0+472
	.word	.LC1
	.word	.LC19
	UNWIND(.fnend)
	.size	MP2_ReceivePacket, .-MP2_ReceivePacket
	.align	2
	.global	MP2_ClearCurPic
	.type	MP2_ClearCurPic, %function
MP2_ClearCurPic:
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
	beq	.L554
	add	r6, r0, #45056
	ldr	r3, [r6, #260]
	cmp	r3, #0
	movne	r4, r0
	movne	r5, #0
	addne	r7, r4, #110592
	bne	.L558
	b	.L559
.L557:
	ldr	r3, [r6, #260]
	add	r4, r4, #44
	cmp	r5, r3
	bcs	.L559
.L558:
	ldr	r1, [r4, #284]
	add	r5, r5, #1
	ldr	r0, [r7, #4080]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #264]
	cmp	r3, #0
	beq	.L557
	ldr	r3, [r4, #272]
	cmp	r3, #0
	beq	.L557
	ldr	r1, [r4, #288]
	add	r4, r4, #44
	ldr	r0, [r7, #4080]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #260]
	cmp	r5, r3
	bcc	.L558
.L559:
	mov	r3, #0
	str	r3, [r6, #260]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L554:
	ldr	ip, .L568
	movw	r3, #3806
	ldr	r2, .L568+4
	mov	r0, #1
	ldr	r1, .L568+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L569:
	.align	2
.L568:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+492
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_ClearCurPic, .-MP2_ClearCurPic
	.align	2
	.global	MPEG2DEC_VDMPostProc
	.type	MPEG2DEC_VDMPostProc, %function
MPEG2DEC_VDMPostProc:
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
	mov	r10, r1
	beq	.L632
	ldrb	ip, [r4, #152]	@ zero_extendqisi2
	add	r5, r4, #77824
	ldr	r9, .L638
	mov	r2, r1
	mov	r0, #22
	ldr	r1, .L638+4
	strb	ip, [r5, #1536]
	add	r3, r4, #45056
	ldr	r6, [r9, #68]
	add	r7, r4, #110592
	str	r3, [fp, #-48]
	ldr	r8, [r5, #2680]
	blx	r6
	mov	r0, r4
	bl	MP2_RecordVFMWState
	mov	r0, r4
	bl	MP2_ClearCurPic
	movw	r2, #45320
	ldr	r6, [r9, #48]
	mov	r1, #0
	add	r0, r4, #8
	blx	r6
	ldr	r1, [r5, #1440]
	ldr	r0, [r7, #4080]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r5, #1436]
	mov	r6, r0
	ldr	r0, [r7, #4080]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r5, #1432]
	str	r0, [fp, #-52]
	ldr	r0, [r7, #4080]
	bl	FSP_GetFsImagePtr
	cmp	r6, #0
	beq	.L633
	ldrb	r2, [r8, #22]	@ zero_extendqisi2
	cmp	r10, #0
	ldr	r3, [fp, #-48]
	strb	r2, [r3, #272]
	str	r10, [r6, #200]
	blt	.L574
	cmp	r10, #100
	movlt	r3, r10
	movge	r3, #100
	str	r3, [r6, #200]
	ldrb	r2, [r8, #22]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L575
	ldr	r2, [r4]
	ldr	r2, [r2]
	cmp	r3, r2
	bhi	.L634
.L575:
	ldr	r3, [r9, #68]
	mov	r0, #22
	ldr	r1, .L638+8
	blx	r3
	mov	r0, r4
	bl	MP2_SetImgFormat
	ldrb	r3, [r8, #9]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L581
	ldr	r3, [r5, #1368]
	cmp	r3, #1
	movne	r0, #1
	beq	.L581
.L627:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L581:
	add	r1, r4, #78848
	add	r6, r6, #212
	add	r3, r1, #344
	add	r1, r1, #360
	mov	ip, #0
.L580:
	ldr	r2, [r3, #4]!
	mov	r0, #0
	add	r6, r6, #4
	cmp	r2, r0
	strne	r2, [r6, #-4]
	cmp	r3, r1
	str	ip, [r3]
	bne	.L580
	str	r0, [r5, #1388]
	ldr	r3, [r4]
	ldr	r3, [r3, #12]
	cmp	r3, #1
	beq	.L583
	ldrb	r3, [r8, #22]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L583
	ldr	r1, [r5, #1432]
	str	r1, [r5, #1444]
.L584:
	cmn	r1, #1
	beq	.L586
	ldr	r0, [r7, #4080]
	bl	FSP_GetDisplay
	cmp	r0, #1
	beq	.L590
	ldr	r1, [r5, #1444]
	ldr	r0, [r7, #4080]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L590
.L586:
	ldrb	r3, [r8, #27]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L635
	ldrb	r3, [r8, #18]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r5, #1520]
	addeq	r3, r3, #1
	addne	r3, r3, #1
	streq	r3, [r5, #1520]
	ldreqb	r3, [r8, #16]	@ zero_extendqisi2
	ldreq	r2, [r5, #1516]
	addeq	r3, r3, #2
	strne	r3, [r5, #1520]
	addeq	r3, r2, r3
	movne	r3, r3, asl #1
	str	r3, [r5, #1516]
.L597:
	ldr	r2, [r5, #1512]
	mov	r0, #1
	ldr	r3, [r5, #1364]
	add	r2, r2, r0
	str	r2, [r5, #1512]
	add	r3, r3, r0
	str	r3, [r5, #1364]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L574:
	mov	r3, #0
	str	r3, [r6, #200]
	b	.L575
.L634:
	ldr	r1, [r5, #1436]
	ldr	r0, [r7, #4080]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L577
	ldr	r1, [r4, #212]
	mov	r6, #0
	ldr	r0, [r7, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r4, #216]
	ldr	r0, [r7, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r4, #220]
	ldr	r0, [r7, #4080]
	bl	FreeUsdByDec
	ldr	r1, [r4, #224]
	ldr	r0, [r7, #4080]
	bl	FreeUsdByDec
	str	r6, [r4, #212]
	str	r6, [r4, #216]
	mov	r2, #1
	str	r6, [r4, #220]
	str	r6, [r4, #224]
	ldr	r1, [r5, #1436]
	ldr	r0, [r7, #4080]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #1432]
	ldr	r0, [r7, #4080]
	bl	FSP_ClearLogicFs
	str	r6, [r5, #1432]
	str	r6, [r5, #1436]
	ldr	r0, [r7, #4080]
	bl	FSP_GetFspType
	cmp	r0, r6
	beq	.L577
	ldr	r0, [r7, #4080]
	bl	FSP_GetNullLogicFs
	str	r0, [r5, #1432]
	str	r0, [r5, #1436]
.L577:
	mov	r3, #0
	mov	r0, #1
	str	r3, [r5, #1396]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L583:
	ldr	r1, [r5, #1440]
	str	r1, [r5, #1444]
	b	.L584
.L632:
	ldr	ip, .L638
	movw	r3, #3450
	ldr	r2, .L638+12
	mov	r0, #1
	ldr	r1, .L638+16
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L590:
	ldr	r1, [r5, #1444]
	ldr	r0, [r7, #4080]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L636
	ldr	r2, [r6, #200]
	cmp	r2, #0
	beq	.L592
	ldr	r3, [r4]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	bhi	.L637
.L592:
	ldr	r10, [r5, #1444]
	ldr	r0, [r7, #4080]
	ldr	r9, [r9, #68]
	mov	r1, r10
	bl	FSP_GetRef
	mov	r2, r10
	ldr	r1, .L638+20
	mov	r3, r0
	mov	r0, #12
	blx	r9
	mov	r2, #1
	ldr	r1, [r5, #1444]
	ldr	r0, [r7, #4080]
	bl	FSP_SetDisplay
	add	r3, r4, #79872
	ldr	r0, [r7, #4080]
	add	r3, r3, #640
	str	r6, [sp]
	mov	r2, r4
	mov	r1, #3
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L599
	add	r8, r6, #208
	add	r6, r6, #224
	mov	r4, #0
.L594:
	ldr	r1, [r8, #4]!
	ldr	r0, [r7, #4080]
	bl	FreeUsdByDec
	cmp	r8, r6
	str	r4, [r8]
	bne	.L594
	ldr	r0, [r7, #4080]
	mov	r2, #0
	ldr	r1, [r5, #1444]
	bl	FSP_SetDisplay
	mov	r0, #0
	b	.L627
.L635:
	ldrb	r2, [r8, #16]	@ zero_extendqisi2
	ldrb	r3, [r8, #10]	@ zero_extendqisi2
	ldr	r1, [r5, #1520]
	add	r3, r2, r3
	add	r3, r3, #1
	add	r3, r3, r1
	str	r3, [r5, #1520]
	mov	r3, r3, asl #1
	str	r3, [r5, #1516]
	b	.L597
.L599:
	ldr	r3, [r7, #4088]
	add	r3, r3, #1
	str	r3, [r7, #4088]
	b	.L586
.L637:
	ldr	r9, [r9, #68]
	mov	r0, #1
	ldr	r1, .L638+24
	add	r4, r6, #208
	add	r6, r6, #224
	blx	r9
	mov	r9, #0
.L595:
	ldr	r1, [r4, #4]!
	ldr	r0, [r7, #4080]
	bl	FreeUsdByDec
	cmp	r4, r6
	str	r9, [r4]
	bne	.L595
	ldr	r0, [r7, #4080]
	mov	r2, #0
	ldr	r1, [r5, #1444]
	bl	FSP_SetDisplay
	b	.L586
.L633:
	str	r0, [sp]
	mov	r2, r6
	ldr	r3, [fp, #-52]
	mov	r0, r6
	ldr	r4, [r9, #68]
	ldr	r1, .L638+28
	blx	r4
	mov	r0, r6
	b	.L627
.L636:
	ldr	r3, [r9, #68]
	movw	r2, #3573
	ldr	r1, .L638+32
	blx	r3
	mov	r0, r6
	b	.L627
.L639:
	.align	2
.L638:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC21
	.word	.LC23
	.word	.LANCHOR0+508
	.word	.LC1
	.word	.LC25
	.word	.LC24
	.word	.LC22
	.word	.LC10
	UNWIND(.fnend)
	.size	MPEG2DEC_VDMPostProc, .-MPEG2DEC_VDMPostProc
	.align	2
	.global	MP2_u_v
	.type	MP2_u_v, %function
MP2_u_v:
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
	mov	r5, r2
	mov	r6, r0
	mov	r7, r1
	bl	BsShow
	mov	r1, r7
	mov	r4, r0
	mov	r0, r6
	bl	BsSkip
	ldr	ip, .L641
	mov	r2, r5
	mov	r3, r4
	ldr	r1, .L641+4
	mov	r0, #2
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L642:
	.align	2
.L641:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC26
	UNWIND(.fnend)
	.size	MP2_u_v, .-MP2_u_v
	.align	2
	.global	MP2_DecSliceHeader
	.type	MP2_DecSliceHeader, %function
MP2_DecSliceHeader:
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
	beq	.L657
	ldr	r2, [r5, #4]
	mov	r1, #1
	mov	r3, #0
	str	r1, [r5, #16]
	cmp	r2, #175
	str	r3, [r5, #24]
	ldr	r4, [r5, #52]
	bhi	.L658
.L646:
	ldr	r1, [r5, #20]
	mov	r0, r4
	ldr	r2, [r5, #8]
	sub	r1, r1, #1
	add	r3, r1, r3
	mov	r1, #5
	mul	r3, r2, r3
	ldr	r2, .L659
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r5, #28]
	bl	MP2_u_v
	mov	r3, #0
	mov	r1, #1
	str	r3, [r5, #32]
	str	r0, [r5, #48]
	mov	r0, r4
	bl	BsShow
	cmp	r0, #0
	bne	.L648
.L651:
	mov	r0, r4
	ldr	r2, .L659+4
	mov	r1, #1
	bl	MP2_u_v
.L645:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L658:
	ldr	r2, [r5]
	cmp	r2, r3
	bne	.L646
	ldr	r2, .L659+8
	mov	r1, #3
	mov	r0, r4
	bl	MP2_u_v
	mov	r3, r0, asl #7
	str	r0, [r5, #24]
	b	.L646
.L648:
	ldr	r2, .L659+12
	mov	r1, #1
	mov	r0, r4
	bl	MP2_u_v
	ldr	r2, .L659+16
	mov	r1, #1
	mov	r0, r4
	bl	MP2_u_v
	ldr	r2, .L659+20
	mov	r1, #7
	str	r0, [r5, #32]
	mov	r0, r4
	bl	MP2_u_v
	b	.L649
.L650:
	bl	MP2_u_v
	ldr	r2, .L659+24
	mov	r1, #8
	mov	r0, r4
	bl	MP2_u_v
.L649:
	mov	r1, #1
	mov	r0, r4
	bl	BsShow
	ldr	r2, .L659+4
	mov	r1, #1
	cmp	r0, #0
	mov	r0, r4
	bne	.L650
	b	.L651
.L657:
	ldr	ip, .L659+28
	mov	r3, #3888
	ldr	r2, .L659+32
	mov	r0, #1
	ldr	r1, .L659+36
	ldr	r4, [ip, #68]
	blx	r4
	b	.L645
.L660:
	.align	2
.L659:
	.word	.LC28
	.word	.LC29
	.word	.LC27
	.word	.LC30
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+532
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_DecSliceHeader, .-MP2_DecSliceHeader
	.align	2
	.global	MP2_ExitMb
	.type	MP2_ExitMb, %function
MP2_ExitMb:
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
	movne	r3, #0
	strne	r3, [r0, #16]
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP2_ExitMb.part.8
	UNWIND(.fnend)
	.size	MP2_ExitMb, .-MP2_ExitMb
	.align	2
	.global	MP2_WriteSliceInfo
	.type	MP2_WriteSliceInfo, %function
MP2_WriteSliceInfo:
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
	subs	r6, r0, #0
	beq	.L670
	add	r7, r6, #45056
	mov	r4, #44
	add	r5, r6, #77824
	ldr	r2, [r7, #260]
	ldr	r1, [r5, #1576]
	cmp	r2, #1024
	mla	r4, r4, r2, r6
	str	r1, [r4, #296]
	ldr	r1, [r5, #1592]
	str	r1, [r4, #300]
	ldr	r1, [r5, #1588]
	str	r1, [r4, #292]
	bcs	.L671
	ldr	r2, [r5, #1624]
	add	r0, r6, #78848
	ldr	r3, [r5, #1320]
	add	r0, r0, #576
	and	r1, r2, #7
	str	r1, [r4, #276]
	add	r3, r3, r2, lsr #3
	str	r3, [r4, #260]
	ldr	r3, [r5, #1336]
	str	r3, [r4, #284]
	bl	BsResidBits
	movw	r2, #1308
	str	r0, [r4, #268]
	ldrsh	r3, [r5, r2]
	cmp	r3, #1
	beq	.L672
	cmp	r3, #256
	bne	.L669
	ldr	r1, [r5, #1324]
	mov	r2, #0
	str	r2, [r4, #280]
	str	r1, [r4, #264]
	ldr	r3, [r5, #1340]
	str	r3, [r4, #288]
	ldr	r3, [r5, #1332]
	mov	r3, r3, asl #3
	str	r3, [r4, #272]
.L668:
	ldr	r3, [r7, #260]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r7, #260]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L671:
	ldr	ip, .L673
	mov	r3, #1024
	ldr	r1, .L673+4
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r6
	bl	MP2_ClearCurPic
	ldr	r3, [r5, #1356]
	mov	r0, #0
	str	r0, [r5, #1412]
	bic	r3, r3, #5767168
	str	r3, [r5, #1356]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L672:
	mov	r3, #0
	add	r4, r4, #268
	str	r3, [r4, #-4]
	str	r3, [r4, #12]
	str	r3, [r4, #20]
	str	r3, [r4, #4]
	b	.L668
.L669:
	ldr	r1, .L673
	movw	r3, #1309
	ldrsb	r2, [r5, r2]
	mov	r0, #1
	ldrsb	r3, [r5, r3]
	ldr	r4, [r1, #68]
	ldr	r1, .L673+8
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L670:
	ldr	ip, .L673
	movw	r3, #4031
	ldr	r2, .L673+12
	mov	r0, #1
	ldr	r1, .L673+16
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L674:
	.align	2
.L673:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC34
	.word	.LC35
	.word	.LANCHOR0+552
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_WriteSliceInfo, .-MP2_WriteSliceInfo
	.align	2
	.global	MP2_MbAddrInc
	.type	MP2_MbAddrInc, %function
MP2_MbAddrInc:
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
	mov	r1, #4
	mov	r6, r0
	bl	BsShow
	ldr	r5, .L681
	add	r0, r5, r0, lsl #3
	ldr	r4, [r0, #572]
	ldr	r1, [r0, #576]
	cmp	r4, #6
	bls	.L679
	cmp	r4, #9
	beq	.L680
	mov	r1, #11
	mov	r0, r6
	bl	BsShow
	ldr	r2, .L681+4
	and	r3, r0, #127
	mov	r0, r6
	sub	r3, r3, #24
	add	r5, r5, r3, lsl #3
	ldr	r4, [r5, #700]
	ldr	r1, [r5, #704]
	bl	MP2_u_v
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L679:
	mov	r0, r6
	ldr	r2, .L681+4
	bl	MP2_u_v
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L680:
	mov	r0, r6
	ldr	r2, .L681+4
	bl	MP2_u_v
	rsb	r0, r0, #9
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L682:
	.align	2
.L681:
	.word	.LANCHOR0
	.word	.LC36
	UNWIND(.fnend)
	.size	MP2_MbAddrInc, .-MP2_MbAddrInc
	.align	2
	.global	MP2_InitMb
	.type	MP2_InitMb, %function
MP2_InitMb:
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
	subs	r6, r0, #0
	ldrne	r4, [r6, #52]
	movne	r5, #0
	bne	.L686
	b	.L697
.L689:
	cmp	r0, #15
	beq	.L687
	cmp	r0, #8
	add	r5, r5, #33
	bne	.L698
.L687:
	ldr	r2, .L700
	mov	r1, #11
	mov	r0, r4
	bl	MP2_u_v
.L686:
	mov	r1, #11
	mov	r0, r4
	bl	BsShow
	cmp	r0, #23
	bls	.L689
	mov	r0, r4
	bl	MP2_MbAddrInc
	ldr	r4, [r6, #16]
	cmp	r4, #0
	beq	.L690
	ldr	r3, [r6, #28]
	add	r5, r5, r0
	cmp	r3, #0
	addne	r2, r5, r3
	ldr	r3, [r6, #12]
	subeq	r2, r5, #1
	str	r2, [r6, #44]
	sub	r3, r3, #1
	cmp	r2, r3
	bhi	.L699
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L698:
	ldr	r3, .L700+4
	mov	r0, #1
	ldr	r1, .L700+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L690:
	ldr	r3, .L700+4
	mov	r2, r4
	ldr	r1, .L700+12
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L699:
	ldr	ip, .L700+4
	mov	r0, #1
	ldr	r1, .L700+16
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L697:
	ldr	ip, .L700+4
	movw	r3, #3950
	ldr	r2, .L700+20
	mov	r0, #1
	ldr	r1, .L700+24
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L701:
	.align	2
.L700:
	.word	.LC38
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC37
	.word	.LC40
	.word	.LC39
	.word	.LANCHOR0+1532
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_InitMb, .-MP2_InitMb
	.align	2
	.global	MP2_GetFirstMbInSlice
	.type	MP2_GetFirstMbInSlice, %function
MP2_GetFirstMbInSlice:
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
	beq	.L705
	bl	MP2_DecSliceHeader
	mov	r0, r4
	bl	MP2_InitMb
	mov	r3, #0
	str	r3, [r4, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L705:
	ldr	ip, .L706
	movw	r3, #3869
	ldr	r2, .L706+4
	mov	r0, #1
	ldr	r1, .L706+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L707:
	.align	2
.L706:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1544
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_GetFirstMbInSlice, .-MP2_GetFirstMbInSlice
	.align	2
	.global	MP2_DecSlice
	.type	MP2_DecSlice, %function
MP2_DecSlice:
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
	beq	.L715
	add	r3, r4, #77824
	uxtb	lr, r1
	add	r0, r4, #78848
	ldr	ip, [r3, #1312]
	add	r5, r0, #576
	ldr	r2, [r3, #2680]
	add	r0, r0, #520
	ldr	r1, [r3, #1328]
	str	ip, [r3, #1580]
	ldr	ip, [r3, #1392]
	str	r1, [r3, #1584]
	sub	ip, ip, #1
	clz	ip, ip
	mov	ip, ip, lsr #5
	str	ip, [r3, #1544]
	ldr	r1, [r2, #60]
	str	r1, [r3, #1548]
	ldr	r1, [r2, #56]
	str	r1, [r3, #1552]
	ldr	r1, [r2, #52]
	ldr	r2, [r2, #48]
	add	r1, r1, #15
	str	r5, [r3, #1596]
	add	r2, r2, #15
	str	lr, [r3, #1564]
	mov	r1, r1, lsr #4
	mov	r2, r2, lsr #4
	mul	r2, r2, r1
	str	r2, [r3, #1556]
	bl	MP2_GetFirstMbInSlice
	cmp	r0, #1
	mov	r5, r0
	beq	.L711
	ldr	r3, .L716
	mov	r0, #1
	ldr	r1, .L716+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L711:
	mov	r0, r4
	bl	MP2_WriteSliceInfo
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L716
	mov	r0, r5
	ldr	r1, .L716+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L715:
	ldr	ip, .L716
	movw	r3, #3831
	ldr	r2, .L716+12
	mov	r0, #1
	ldr	r1, .L716+16
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L717:
	.align	2
.L716:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC41
	.word	.LC42
	.word	.LANCHOR0+1568
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_DecSlice, .-MP2_DecSlice
	.align	2
	.global	MP2_GetHDR
	.type	MP2_GetHDR, %function
MP2_GetHDR:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	subs	r7, r0, #0
	beq	.L801
	add	r5, r7, #77824
	add	r6, r7, #78848
	add	r6, r6, #576
	add	r8, r7, #114688
	ldr	r3, [r5, #2680]
	mov	r1, #32
	ldr	r10, [r5, #2684]
	mov	r9, #0
	mov	r0, r6
	strb	r9, [r8]
	str	r3, [fp, #-80]
	bl	BsShow
	ldr	r3, [r5, #1356]
	str	r3, [fp, #-84]
	mov	r4, r0
	mov	r0, r6
	bl	BsPos
	mov	r1, #32
	str	r0, [r5, #1416]
	mov	r0, r6
	bl	BsSkip
	movw	r3, #439
	cmp	r4, r3
	beq	.L802
	movw	r3, #442
	cmp	r4, r3
	beq	.L803
	movw	r3, #435
	cmp	r4, r3
	cmpne	r4, #440
	bne	.L722
	ldr	r3, [r5, #1412]
	cmp	r3, #1
	beq	.L804
.L726:
	movw	r3, #435
	cmp	r4, r3
	beq	.L731
	cmp	r4, #436
	bcc	.L805
	movw	r3, #437
	cmp	r4, r3
	beq	.L735
	cmp	r4, #436
	bls	.L752
	movw	r3, #439
	cmp	r4, r3
	beq	.L752
	cmp	r4, #440
	bne	.L730
	ldr	r4, .L810
	mov	r0, r6
	ldr	r3, [r5, #1408]
	ldr	r8, [r5, #1304]
	ldr	r9, [r4, #68]
	add	r8, r3, r8
	bl	BsPos
	ldr	r1, .L810+4
	add	r2, r8, r0, lsr #3
	mov	r0, #22
	blx	r9
	mov	r0, r7
	bl	group_of_pictures_header
	mov	r0, r6
	bl	BsResidBits
	cmp	r0, #0
	blt	.L806
.L752:
	mov	r6, #0
.L720:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L722:
	movw	r3, #439
	cmp	r4, #256
	cmpne	r4, r3
	bne	.L726
	ldr	r3, [r5, #1412]
	cmp	r3, #1
	bne	.L726
	b	.L804
.L805:
	cmp	r4, #256
	beq	.L733
	bcc	.L730
	cmp	r4, #432
	bls	.L730
	ldr	r8, .L810
	mov	r0, r6
	ldr	r3, [r5, #1408]
	ldr	r4, [r5, #1304]
	ldr	r5, [r8, #68]
	add	r4, r3, r4
	bl	BsPos
	ldr	r1, .L810+8
	add	r2, r4, r0, lsr #3
	mov	r0, #22
	blx	r5
	mov	r0, r7
	bl	MP2_GetUsrData
	subs	r6, r0, #0
	bne	.L746
	add	r5, r7, #110592
	add	r1, r7, #78848
	add	r1, r1, #284
	ldr	r0, [r5, #4080]
	bl	MP2_ClearCurPacket
	ldr	r3, [r8, #68]
	ldr	r1, .L810+12
	mov	r0, #1
	blx	r3
	ldr	r3, .L810+16
	ldr	r4, [r3]
	cmp	r4, #0
	mvneq	r6, #0
	beq	.L720
	mov	r3, r6
	mov	r2, r6
	ldr	r0, [r5, #4080]
	mov	r1, #113
	blx	r4
	mvn	r6, #0
	b	.L720
.L804:
	ldr	r2, [r5, #1356]
	tst	r2, #4194304
	beq	.L726
	strb	r3, [r8]
	orr	r2, r2, #8388608
	mov	r0, r7
	str	r2, [r5, #1356]
	mov	r2, #0
	str	r2, [r5, #1412]
	mov	r6, r3
	bl	MP2_ProtocolPPSCheck
	b	.L720
.L733:
	ldr	r4, .L810
	mov	r0, r6
	ldr	r3, [r5, #1408]
	ldr	r8, [r5, #1304]
	ldr	r9, [r4, #68]
	add	r8, r3, r8
	bl	BsPos
	ldr	r1, .L810+20
	add	r2, r8, r0, lsr #3
	mov	r0, #22
	blx	r9
	mov	r0, r7
	bl	picture_header
	mov	r0, r6
	bl	BsResidBits
	cmp	r0, #0
	bge	.L752
	ldr	r3, .L810+16
	ldr	r2, [fp, #-84]
	ldr	r6, [r3]
	str	r2, [r5, #1356]
	add	r5, r7, #110592
	cmp	r6, #0
	beq	.L745
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r5, #4080]
	blx	r6
.L745:
	add	r1, r7, #78848
	ldr	r0, [r5, #4080]
	add	r1, r1, #284
	mvn	r6, #0
	bl	MP2_ClearCurPacket
	ldr	r3, [r4, #68]
	mov	r2, #256
	ldr	r1, .L810+24
	mov	r0, #1
	blx	r3
	b	.L720
.L802:
	ldr	r3, .L810
	mov	r2, #32
	mov	r1, r6
	sub	r0, fp, #76
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #32
	str	r0, [fp, #-88]
	sub	r0, fp, #76
	bl	BsGet
	ldr	r3, [fp, #-88]
	movw	r1, #20036
	movw	r2, #20553
	movt	r1, 17221
	movt	r2, 18515
	cmp	r0, r1
	cmpeq	r3, r2
	bne	.L722
	ldr	r6, [r5, #1412]
	cmp	r6, #1
	beq	.L807
.L723:
	mov	r3, #1
	mov	r6, #0
	strb	r3, [r8, #2]
	b	.L720
.L803:
	ldr	r3, .L810
	mov	r2, #32
	mov	r1, r6
	sub	r0, fp, #76
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #32
	str	r0, [fp, #-88]
	sub	r0, fp, #76
	bl	BsGet
	ldr	r3, [fp, #-88]
	movw	r1, #20036
	movw	r2, #20553
	movt	r1, 17221
	movt	r2, 18515
	cmp	r0, r1
	cmpeq	r3, r2
	bne	.L726
	ldr	r6, [r5, #1412]
	cmp	r6, #1
	bne	.L752
	ldr	r3, [r5, #1356]
	tst	r3, #4194304
	beq	.L752
	strb	r6, [r8]
	orr	r3, r3, #8388608
	str	r9, [r5, #1412]
	mov	r0, r7
	str	r3, [r5, #1356]
	bl	MP2_ProtocolPPSCheck
	b	.L720
.L735:
	ldr	r2, .L810
	mov	r0, r6
	ldr	r3, [r5, #1408]
	ldr	r4, [r5, #1304]
	ldr	r8, [r2, #68]
	add	r4, r3, r4
	bl	BsPos
	ldr	r1, .L810+28
	add	r2, r4, r0, lsr #3
	mov	r0, #22
	blx	r8
	mov	r0, r7
	bl	extension
	mov	r0, r6
	bl	BsResidBits
	cmp	r0, #0
	bge	.L752
	ldr	r3, .L810+16
	ldr	r2, [fp, #-84]
	ldr	r4, [r3]
	str	r2, [r5, #1356]
	add	r5, r7, #110592
	cmp	r4, #0
	beq	.L747
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r5, #4080]
	blx	r4
.L747:
	add	r1, r7, #78848
	ldr	r0, [r5, #4080]
	add	r1, r1, #284
	mvn	r6, #0
	bl	MP2_ClearCurPacket
	b	.L720
.L730:
	sub	r3, r4, #256
	sub	r3, r3, #1
	cmp	r3, #174
	bhi	.L748
	ldr	r3, [r5, #1352]
	cmp	r3, #0
	beq	.L749
.L751:
	ldr	r3, [r5, #1356]
	tst	r3, #589824
	beq	.L752
	orr	r3, r3, #4194304
	mov	r0, r7
	str	r3, [r5, #1356]
	mov	r7, #1
	mov	r1, r4
	str	r7, [r5, #1412]
	bl	MP2_DecSlice
	cmp	r0, r7
	mov	r6, r0
	beq	.L720
	ldr	r3, .L810
	mov	r2, r4
	mov	r0, r7
	ldr	r1, .L810+32
	mov	r6, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L720
.L731:
	ldr	r4, .L810
	mov	r0, r6
	ldr	r3, [r5, #1408]
	ldr	r9, [r5, #1304]
	ldr	r8, [r4, #68]
	add	r9, r3, r9
	bl	BsPos
	ldr	r1, .L810+36
	add	r2, r9, r0, lsr #3
	mov	r0, #22
	blx	r8
	mov	r0, r7
	bl	sequence_header
	mov	r0, r6
	bl	BsResidBits
	cmp	r0, #0
	blt	.L808
	ldr	r6, [r5, #1356]
	ands	r6, r6, #7
	bne	.L740
	ldr	r2, [fp, #-80]
	mov	r3, #1
	mov	r0, r10
	strb	r3, [r2]
	mov	r1, r2
	mov	r2, #188
	bl	memcpy
	ldr	r3, [r5, #1360]
	add	r3, r3, #1
	str	r3, [r5, #1360]
	b	.L720
.L801:
	ldr	ip, .L810
	movw	r3, #346
	ldr	r2, .L810+40
	mov	r0, #1
	ldr	r1, .L810+44
	mov	r6, r7
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L740:
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L809
.L748:
	ldr	r3, .L810+16
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L752
.L797:
	add	r7, r7, #110592
	mov	r3, #0
	mov	r2, r3
	mov	r1, #113
	ldr	r0, [r7, #4080]
	mov	r6, r3
	blx	r4
	b	.L720
.L746:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L810+48
	blx	r3
	b	.L720
.L807:
	ldr	r3, [r5, #1356]
	tst	r3, #4194304
	beq	.L723
	strb	r6, [r8, #2]
	orr	r3, r3, #8388608
	strb	r6, [r8]
	mov	r0, r7
	str	r3, [r5, #1356]
	str	r9, [r5, #1412]
	bl	MP2_ProtocolPPSCheck
	b	.L720
.L749:
	mov	r0, r7
	bl	MP2_GetSequenceInfo
	ldr	r3, [r5, #1404]
	cmp	r3, #0
	beq	.L752
	ldrb	r3, [r8, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L751
	b	.L752
.L809:
	mov	r2, #188
	mov	r1, r10
	ldr	r0, [fp, #-80]
	bl	memcpy
	ldr	r2, .L810+16
	ldr	r3, [r5, #1356]
	ldr	r4, [r2]
	bic	r3, r3, #7
	str	r3, [r5, #1356]
	cmp	r4, #0
	bne	.L797
	b	.L752
.L806:
	ldr	r3, .L810+16
	ldr	r2, [fp, #-84]
	ldr	r6, [r3]
	str	r2, [r5, #1356]
	add	r5, r7, #110592
	cmp	r6, #0
	beq	.L744
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r5, #4080]
	blx	r6
.L744:
	add	r1, r7, #78848
	ldr	r0, [r5, #4080]
	add	r1, r1, #284
	mvn	r6, #0
	bl	MP2_ClearCurPacket
	ldr	r3, [r4, #68]
	mov	r2, #440
	ldr	r1, .L810+52
	mov	r0, #1
	blx	r3
	b	.L720
.L808:
	ldr	r3, .L810+16
	ldr	r2, [fp, #-84]
	ldr	r6, [r3]
	str	r2, [r5, #1356]
	add	r5, r7, #110592
	cmp	r6, #0
	beq	.L739
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r5, #4080]
	blx	r6
.L739:
	add	r1, r7, #78848
	ldr	r0, [r5, #4080]
	add	r1, r1, #284
	mvn	r6, #0
	bl	MP2_ClearCurPacket
	ldr	r3, [r4, #68]
	movw	r2, #435
	ldr	r1, .L810+56
	mov	r0, #1
	blx	r3
	b	.L720
.L811:
	.align	2
.L810:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC45
	.word	.LC49
	.word	.LC50
	.word	g_event_report
	.word	.LC47
	.word	.LC48
	.word	.LC52
	.word	.LC53
	.word	.LC43
	.word	.LANCHOR0+1584
	.word	.LC1
	.word	.LC51
	.word	.LC46
	.word	.LC44
	UNWIND(.fnend)
	.size	MP2_GetHDR, .-MP2_GetHDR
	.align	2
	.global	MPEG2DEC_Decode
	.type	MPEG2DEC_Decode, %function
MPEG2DEC_Decode:
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
	UNWIND(.pad #180)
	sub	sp, sp, #180
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	moveq	r6, #1
	movne	r6, #0
	beq	.L990
	add	r9, r0, #79872
	ldr	r7, .L1018
	add	r9, r9, #96
	add	r5, r0, #45312
	add	r5, r5, #16
	add	r8, r4, #110592
	mov	r2, #160
	ldr	r3, [r7, #52]
	mov	r0, r9
	blx	r3
	mov	r1, r9
	mov	r0, r5
	ldr	r2, [r8, #4080]
	bl	MP2_ReceivePacket
	cmp	r0, #1
	beq	.L815
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L1018+4
	blx	r3
	mov	r0, r6
.L979:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L815:
	add	r10, r4, #78848
	add	r6, r4, #77824
	add	r9, r10, #576
	ldr	r2, [r6, #1328]
	mov	r0, r9
	ldr	r1, [r6, #1312]
	bl	BsInit
	ldr	r3, [r4]
	ldr	r2, [r3, #868]
	cmp	r2, #1
	beq	.L991
.L816:
	ldr	r3, [r6, #1356]
	str	r3, [r6, #1540]
.L817:
	mov	r0, r4
	bl	MP2_GetHDR
	add	r0, r0, #1
	cmp	r0, #1
	bls	.L992
	ldr	r3, [r6, #1356]
	ldr	r2, [r6, #2680]
	ands	r0, r3, #8388608
	str	r2, [fp, #-176]
	beq	.L979
	ldrb	r2, [r2, #9]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L820
	ldr	r2, [r6, #1368]
	cmp	r2, #1
	beq	.L820
.L821:
	ands	r2, r3, #255
	str	r2, [fp, #-180]
	beq	.L822
	ldr	r9, .L1018+128
	ldr	r10, [r9]
	cmp	r10, #0
	beq	.L823
	mov	r3, #0
	mov	r1, #103
	mov	r2, r3
	ldr	r0, [r8, #4080]
	blx	r10
	ldr	r3, [r6, #1356]
.L823:
	ldr	r2, [r6, #1364]
	mov	r0, #22
	ldr	r6, [r7, #68]
	ldr	r1, .L1018+8
	blx	r6
.L824:
	add	r1, r5, #33792
	ldr	r0, [r8, #4080]
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r4, [r9]
	cmp	r4, #0
	beq	.L906
	mov	r3, #0
	ldr	r0, [r8, #4080]
	mov	r2, r3
	mov	r1, #113
	blx	r4
.L906:
	ldr	r3, [r7, #68]
	mov	r0, #22
	ldr	r1, .L1018+12
	blx	r3
	mov	r0, #0
	b	.L979
.L990:
	ldr	ip, .L1018
	movw	r3, #3121
	ldr	r2, .L1018+16
	mov	r0, #1
	ldr	r1, .L1018+20
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L992:
	ldr	r3, [r4]
	ldr	r2, [r3, #868]
	cmp	r2, #1
	beq	.L993
.L819:
	add	r4, r4, #114688
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L912
	add	r1, r5, #33792
	ldr	r0, [r8, #4080]
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	mov	r0, #0
	b	.L979
.L991:
	ldr	r3, [r3, #908]
	cmp	r3, #1
	ldreq	r3, [r6, #1540]
	streq	r3, [r6, #1356]
	bne	.L816
	b	.L817
.L993:
	ldr	r3, [r3, #908]
	cmp	r3, #0
	beq	.L819
.L912:
	mov	r0, #0
	b	.L979
.L822:
	ldr	r3, [r6, #1404]
	cmp	r3, #0
	beq	.L994
	ldr	r3, [r6, #1344]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r3, [r4]
	ldr	r2, [r3, #8]
	bls	.L995
.L827:
	sub	r3, r2, #1
	str	r2, [r6, #1344]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L831
.L833:
	.word	.L832
	.word	.L834
	.word	.L835
	.word	.L836
.L836:
	ldr	r3, [fp, #-176]
	ldrb	r2, [r3, #22]	@ zero_extendqisi2
	cmp	r2, #1
	mov	r3, r2
	beq	.L996
	cmp	r2, #3
	beq	.L997
.L840:
	cmp	r2, #2
	ldreq	r2, [fp, #-176]
	movne	r3, r2
	movne	r2, #1
	strne	r2, [fp, #-180]
	ldrne	r2, [fp, #-176]
	moveq	r3, #1
	streq	r3, [r8, #4092]
	streq	r3, [fp, #-180]
	moveq	r3, r2
	ldreqb	r3, [r3, #22]	@ zero_extendqisi2
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
.L837:
	ldr	ip, [r6, #1408]
	mov	r0, r9
	ldr	r2, [r6, #1304]
	str	r3, [fp, #-200]
	add	r9, ip, r2
	ldr	r3, [r7, #68]
	ldr	r2, [r6, #1364]
	str	r1, [fp, #-204]
	str	r3, [fp, #-188]
	str	r2, [fp, #-196]
	bl	BsPos
	ldr	r1, [fp, #-204]
	ldr	r3, [fp, #-200]
	ldr	r2, [fp, #-196]
	str	r1, [sp]
	ldr	ip, [fp, #-188]
	ldr	r1, .L1018+24
	add	r0, r9, r0, lsr #3
	str	r0, [sp, #4]
	mov	r0, #18
	blx	ip
	ldr	r3, [r6, #1356]
	bic	r3, r3, #14155776
	str	r3, [r6, #1356]
	ldr	r3, [r4]
	ldr	r0, [r3, #692]
	cmp	r0, #1
	beq	.L998
	ldr	r3, [r6, #1396]
	cmp	r3, #0
	bne	.L848
	ldr	r2, [fp, #-176]
	ldrb	r2, [r2, #22]	@ zero_extendqisi2
	sub	r1, r2, #2
	cmp	r1, #1
	bls	.L999
.L849:
	cmp	r2, #3
	beq	.L1000
.L846:
	ldr	r1, [r6, #1432]
	ldr	r0, [r8, #4080]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r6, #1436]
	mov	r9, r0
	ldr	r0, [r8, #4080]
	bl	FSP_GetFsImagePtr
	clz	r3, r9
	mov	r3, r3, lsr #5
	clz	r1, r0
	mov	r1, r1, lsr #5
	orrs	r2, r1, r3
	bne	.L1001
	ldr	r2, [fp, #-176]
	ldrb	r2, [r2, #22]	@ zero_extendqisi2
	cmp	r2, #2
	beq	.L1002
	cmp	r2, #3
	beq	.L1003
.L854:
	ldr	r3, [fp, #-180]
	cmp	r3, #0
	bne	.L859
	ldr	r3, [fp, #-176]
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L860
	ldr	r3, [r6, #1368]
	cmp	r3, #0
	ldrne	r9, .L1018+128
	bne	.L824
.L860:
	ldr	r3, [fp, #-176]
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [fp, #-176]
	beq	.L1004
	ldrb	r3, [r3, #18]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1005
	ldr	r3, [r6, #1520]
	add	r3, r3, #1
	str	r3, [r6, #1520]
	mov	r3, r3, asl #1
	str	r3, [r6, #1516]
.L862:
	ldr	r2, [r6, #1512]
	ldr	r3, [r6, #1364]
	add	r2, r2, #1
	ldr	r9, .L1018+128
	add	r3, r3, #1
	str	r2, [r6, #1512]
	str	r3, [r6, #1364]
	b	.L824
.L835:
	ldr	r2, [fp, #-176]
	mov	r1, #0
	str	r1, [fp, #-180]
	ldrb	r3, [r2, #22]	@ zero_extendqisi2
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	b	.L837
.L834:
	ldr	r3, [fp, #-176]
	ldrb	r3, [r3, #22]	@ zero_extendqisi2
	sub	r2, r3, #2
	cmp	r2, #1
	bls	.L1006
.L917:
	mov	r2, #1
	str	r2, [fp, #-180]
	ldr	r2, [fp, #-176]
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	b	.L837
.L832:
	ldr	r3, [fp, #-176]
	ldrb	r3, [r3, #22]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L917
	ldr	r2, [fp, #-176]
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	cmp	r1, #3
	mov	r3, r1
	beq	.L919
	ldr	r3, [r6, #1368]
	mov	r1, #0
	str	r1, [fp, #-180]
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r6, #1368]
	ldrb	r3, [r2, #22]	@ zero_extendqisi2
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	b	.L837
.L820:
	ldr	r2, [r8, #4084]
	add	r2, r2, #1
	str	r2, [r8, #4084]
	b	.L821
.L848:
	cmp	r3, #1
	bhi	.L846
	ldr	r3, [fp, #-176]
	ldrb	r2, [r3, #22]	@ zero_extendqisi2
	b	.L849
.L998:
	ldr	r2, [r6, #1396]
	cmp	r2, #0
	bne	.L846
	ldr	r3, [fp, #-176]
	ldrb	r3, [r3, #22]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L1007
	cmp	r3, #2
	bne	.L846
	ldr	r3, .L1018
	ldr	r1, .L1018+28
	ldr	r3, [r3, #68]
	blx	r3
	b	.L846
.L995:
	cmp	r2, #4
	cmpne	r2, #1
	bhi	.L827
	ldr	r3, [r7, #68]
	mov	r0, #2
	ldr	r1, .L1018+32
	blx	r3
	ldr	r3, [r6, #1356]
	ldr	r1, [r6, #1436]
	orr	r3, r3, #128
	str	r3, [r6, #1356]
	ldr	r0, [r8, #4080]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L829
	ldr	r1, [r3, #212]
	ldr	r0, [r8, #4080]
	str	r3, [fp, #-188]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-188]
	ldr	r0, [r8, #4080]
	ldr	r1, [r3, #216]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-188]
	ldr	r0, [r8, #4080]
	ldr	r1, [r3, #220]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-188]
	ldr	r0, [r8, #4080]
	ldr	r1, [r3, #224]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-188]
	ldr	r1, [fp, #-180]
	mov	r2, #1
	str	r1, [r3, #212]
	str	r1, [r3, #216]
	str	r1, [r3, #220]
	str	r1, [r3, #224]
	ldr	r1, [r6, #1436]
	ldr	r0, [r8, #4080]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r6, #1432]
	ldr	r0, [r8, #4080]
	bl	FSP_ClearLogicFs
	ldr	r2, [fp, #-180]
	str	r2, [r6, #1432]
	str	r2, [r6, #1436]
	ldr	r0, [r8, #4080]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L829
	ldr	r0, [r8, #4080]
	bl	FSP_GetNullLogicFs
	str	r0, [r6, #1432]
	str	r0, [r6, #1436]
.L829:
	mov	r3, #0
	str	r3, [r6, #1396]
	ldr	r3, [r4]
	ldr	r2, [r3, #8]
	b	.L827
.L994:
	ldr	r2, [r6, #1364]
	mov	r0, #1
	ldr	r3, [r7, #68]
	ldr	r1, .L1018+36
	blx	r3
	ldr	r9, .L1018+128
	b	.L824
.L1002:
	cmp	r3, #0
	bne	.L852
	ldr	r3, [r4]
	ldr	r2, [r9, #200]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L854
	ldr	r6, [r7, #68]
	mov	r0, #1
	ldr	r1, .L1018+40
	blx	r6
	ldr	r9, .L1018+128
	b	.L824
.L859:
	ldr	r3, [r6, #1392]
	ldr	r9, [r6, #2680]
	cmp	r3, #1
	ldr	r3, [r6, #2684]
	str	r3, [fp, #-176]
	bne	.L904
	ldrb	r2, [r9, #26]	@ zero_extendqisi2
	ldrb	r3, [r9, #24]	@ zero_extendqisi2
	strb	r2, [r9, #7]
	strb	r2, [r9, #6]
	strb	r3, [r9, #5]
	strb	r3, [r9, #4]
.L904:
	ldrb	r3, [r9, #9]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L864
	ldr	r2, [r6, #1368]
	ldr	r1, [r6, #1400]
	clz	r3, r2
	mov	r3, r3, lsr #5
	str	r3, [r6, #1368]
	ldr	r2, [r9, #156]
	cmp	r2, r1
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	bne	.L1008
.L983:
	add	r3, r4, #45056
	str	r3, [fp, #-180]
.L866:
	ldrb	r3, [r9, #9]	@ zero_extendqisi2
	ldr	r2, [fp, #-180]
	strb	r3, [r2, #273]
	ldr	r3, [r9, #156]
	str	r3, [r6, #1400]
	ldr	r3, [r9, #56]
	strh	r3, [r4, #160]	@ movhi
	ldrb	r3, [r9, #9]	@ zero_extendqisi2
	cmp	r3, #3
	ldr	r3, [r9, #60]
	ldreq	r2, [r9, #64]
	movne	r3, r3, lsr #1
	rsbeq	r3, r2, r3
	strh	r3, [r4, #156]	@ movhi
	ldr	r3, [r9, #60]
	strh	r3, [r4, #158]	@ movhi
	ldrb	r3, [r9, #11]	@ zero_extendqisi2
	strb	r3, [r4, #13]
	ldrb	r3, [r9, #9]	@ zero_extendqisi2
	strb	r3, [r4, #11]
	ldr	r2, [r6, #1368]
	strb	r2, [r4, #12]
	ldrb	r3, [r9, #12]	@ zero_extendqisi2
	strb	r3, [r4, #15]
	ldrb	r3, [r9, #22]	@ zero_extendqisi2
	strb	r3, [r4, #8]
	ldr	r3, [r6, #1392]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #188]
	cmp	r3, #0
	ldrneb	r3, [r9, #25]	@ zero_extendqisi2
	strneb	r3, [r4, #9]
	ldrneb	r3, [r9, #23]	@ zero_extendqisi2
	strneb	r3, [r4, #10]
	ldrb	r3, [r9, #4]	@ zero_extendqisi2
	strb	r3, [r4, #20]
	ldrb	r3, [r9, #5]	@ zero_extendqisi2
	strb	r3, [r4, #21]
	ldrb	r3, [r9, #6]	@ zero_extendqisi2
	strb	r3, [r4, #22]
	ldrb	r3, [r9, #7]	@ zero_extendqisi2
	strb	r3, [r4, #23]
	ldrb	r3, [r9, #10]	@ zero_extendqisi2
	strb	r3, [r4, #14]
	ldrb	r3, [r9, #8]	@ zero_extendqisi2
	strb	r3, [r4, #19]
	ldrb	r3, [r9, #13]	@ zero_extendqisi2
	strb	r3, [r4, #18]
	ldrb	r3, [r9, #14]	@ zero_extendqisi2
	strb	r3, [r4, #17]
	ldrb	r3, [r9, #15]	@ zero_extendqisi2
	strb	r3, [r4, #16]
	ldrb	r3, [r9, #9]	@ zero_extendqisi2
	cmp	r2, #0
	cmpne	r3, #3
	bne	.L875
	mov	r1, #0
	mov	r0, r4
	bl	MP2_GetImageBuffer
	cmp	r0, #0
	beq	.L1009
	ldr	r1, [r6, #1440]
	ldr	r0, [r8, #4080]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	mov	lr, r3
	beq	.L878
	ldr	ip, [r4]
	mov	r0, #29
	ldr	r1, .L1018+44
	str	lr, [fp, #-176]
	ldrd	r2, [ip, #48]
	strd	r2, [lr, #8]
	ldr	ip, [r4]
	ldrd	r2, [ip, #64]
	strd	r2, [lr, #16]
	ldr	ip, [r4]
	ldrd	r2, [ip, #80]
	strd	r2, [lr, #24]
	mvn	r2, #0
	ldr	ip, [r4]
	mvn	r3, #0
	ldr	ip, [ip, #96]
	str	ip, [lr, #68]
	ldr	ip, [r4]
	ldr	ip, [ip, #100]
	str	ip, [lr, #72]
	ldr	ip, [r4]
	ldr	ip, [ip, #104]
	str	ip, [lr, #76]
	ldr	ip, [r4]
	ldr	ip, [ip, #120]
	str	ip, [lr, #80]
	ldr	ip, [r4]
	strd	r2, [ip, #48]
	ldrd	r2, [lr, #16]
	ldr	ip, [r7, #68]
	strd	r2, [fp, #-196]
	ldrd	r2, [lr, #8]
	strd	r2, [fp, #-188]
	ldrd	r2, [fp, #-196]
	strd	r2, [sp]
	ldrd	r2, [fp, #-188]
	blx	ip
	ldrb	r3, [r9, #9]	@ zero_extendqisi2
	ldr	r2, [fp, #-176]
	subs	r3, r3, #3
	movne	r3, #1
	str	r3, [r2, #148]
.L878:
	ldrb	r3, [r9, #22]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L875
	ldr	r3, [r6, #1396]
	ldr	r2, [r6, #1432]
	cmp	r3, #0
	ldr	r3, [r6, #1436]
	movne	r1, #2
	moveq	r1, #1
	cmp	r2, r3
	str	r1, [r6, #1396]
	beq	.L881
	ldr	r3, [r7, #68]
	mov	r0, #13
	ldr	r1, .L1018+48
	blx	r3
	mov	r2, #0
	ldr	r1, [r6, #1432]
	ldr	r0, [r8, #4080]
	bl	FSP_SetRef
	ldr	r3, [r6, #1436]
.L881:
	ldr	r1, [r6, #1440]
	mov	r2, #1
	str	r3, [r6, #1432]
	str	r1, [r6, #1436]
	ldr	r0, [r8, #4080]
	bl	FSP_SetRef
	ldr	r1, [r6, #1432]
	ldr	r0, [r8, #4080]
	bl	FSP_RemovePmv
	ldr	r3, [r7, #68]
	ldr	r2, [r6, #1440]
	mov	r0, #13
	ldr	r1, .L1018+52
	blx	r3
.L875:
	ldr	r1, [r6, #1440]
	ldr	r0, [r8, #4080]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #1432]
	mov	r9, r0
	ldr	r0, [r8, #4080]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #1436]
	str	r0, [fp, #-176]
	ldr	r0, [r8, #4080]
	bl	FSP_GetLogicFs
	ldr	r3, [fp, #-176]
	cmp	r9, #0
	cmpne	r3, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	str	r0, [fp, #-188]
	cmp	r3, #0
	bne	.L1010
	ldr	r2, [r9, #520]
	cmp	r2, #0
	beq	.L883
	ldr	r3, [r9, #528]
	cmp	r3, #0
	beq	.L883
	ldr	r3, [r9, #524]
	cmp	r3, #0
	beq	.L883
	ldr	r3, [fp, #-188]
	mov	r0, #13
	ldr	r3, [r3, #520]
	cmp	r3, #0
	ldreq	r3, [r2, #12]
	ldrne	r3, [r3, #12]
	str	r3, [fp, #-196]
	ldr	r3, [fp, #-196]
	str	r3, [r4, #200]
	ldr	r3, [fp, #-176]
	ldr	r3, [r3, #520]
	cmp	r3, #0
	ldreq	r3, [r9, #520]
	ldr	r3, [r3, #12]
	str	r3, [fp, #-200]
	ldr	r3, [fp, #-200]
	str	r3, [r4, #204]
	ldr	r3, [r9, #520]
	ldr	r2, [r3, #12]
	str	r2, [r4, #208]
	ldr	r3, [r9, #532]
	str	r3, [r4, #248]
	str	r3, [fp, #-204]
	ldr	r3, [fp, #-188]
	ldr	r3, [r3, #528]
	cmp	r3, #0
	ldreq	r3, [r9, #528]
	ldr	r3, [r3, #12]
	str	r3, [r4, #220]
	ldr	r3, [fp, #-176]
	ldr	r3, [r3, #528]
	cmp	r3, #0
	ldreq	r3, [r9, #528]
	ldr	r3, [r3, #12]
	str	r3, [r4, #224]
	ldr	r3, [r9, #528]
	ldr	r3, [r3, #12]
	str	r3, [r4, #228]
	ldr	r3, [r9, #524]
	ldr	r1, [fp, #-188]
	ldr	lr, [fp, #-180]
	ldr	r3, [r3, #12]
	str	r3, [r4, #232]
	ldr	r1, [r1, #156]
	str	r1, [r4, #212]
	ldr	r1, [fp, #-176]
	ldr	r1, [r1, #156]
	str	r1, [r4, #216]
	ldr	ip, [r9, #528]
	ldr	r1, .L1018+56
	ldr	ip, [ip, #12]
	str	ip, [lr, #264]
	ldr	ip, [fp, #-204]
	str	ip, [sp, #8]
	ldr	ip, [fp, #-196]
	str	ip, [sp, #4]
	ldr	ip, [fp, #-200]
	str	ip, [sp]
	ldr	ip, [r7, #68]
	blx	ip
	ldr	r3, [r9, #524]
	add	ip, r10, #604
	add	r0, r10, #860
	add	r1, r4, #87
	add	r2, r4, #23
	ldr	lr, [r3, #20]
	mov	r3, #0
	str	lr, [r4, #240]
.L893:
	ldr	lr, [ip, #4]!
	add	r3, r3, #1
	cmp	r3, #64
	strb	lr, [r1, #1]!
	ldr	lr, [r0, #4]!
	strb	lr, [r2, #1]!
	bne	.L893
	mov	r2, #128
	ldr	r1, .L1018+60
	sub	r0, fp, #172
	bl	memcpy
	ldr	r2, [r6, #1392]
	ldr	r3, [r4, #300]
	cmp	r2, #1
	beq	.L894
	ldr	r2, [r6, #2680]
	ldrb	r2, [r2, #13]	@ zero_extendqisi2
	cmp	r2, #0
	subne	r2, fp, #44
	moveq	r3, r3, asl #1
	addne	r3, r2, r3, lsl #2
	ldrne	r3, [r3, #-128]
.L894:
	strb	r3, [r4, #152]
	mov	r0, r4
	bl	MP2_SetVDMInf
	ldr	r3, [r4]
	ldr	r1, [fp, #-180]
	ldr	r2, [r3, #676]
	str	r2, [r1, #268]
	ldr	r2, [r6, #2680]
	ldrb	r1, [r2, #22]	@ zero_extendqisi2
	cmp	r1, #3
	beq	.L1011
	cmp	r1, #2
	moveq	r1, #1
	streq	r1, [r8, #4092]
.L898:
	add	r0, r4, #8
	str	r0, [r4, #4]
	ldr	r1, [r3, #900]
	cmp	r1, #1
	beq	.L1012
	cmp	r1, #2
	beq	.L1013
.L901:
	ldr	r3, [r6, #1356]
	bic	r3, r3, #16252928
	str	r3, [r6, #1356]
	ldrb	r3, [r2, #22]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1014
.L902:
	ldr	r0, [r6, #1304]
	ldr	r3, [r6, #1408]
	ldr	r2, [r6, #1328]
	mov	r0, r0, asl #3
	add	r3, r3, r2
	str	r3, [r6, #1408]
	b	.L979
.L864:
	add	r3, r4, #45056
	str	r3, [fp, #-180]
	ldrb	r1, [r3, #273]	@ zero_extendqisi2
	cmp	r1, #3
	beq	.L869
	ldr	r3, [r6, #1368]
	cmp	r3, #0
	beq	.L1015
.L869:
	mov	r3, #1
	str	r3, [r6, #1368]
	b	.L866
.L1010:
	ldr	r1, [r6, #1440]
	mov	r2, #1
	ldr	r0, [r8, #4080]
	bl	FSP_ClearLogicFs
	ldr	r3, [fp, #-188]
	ldr	r6, [r7, #68]
	movw	r2, #1214
	ldr	r1, .L1018+64
	mov	r0, #0
	str	r3, [sp, #4]
	ldr	r3, [fp, #-176]
	str	r3, [sp]
	mov	r3, r9
	blx	r6
.L877:
	add	r1, r5, #33792
	ldr	r0, [r8, #4080]
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r3, .L1018+128
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L908
	mov	r3, #0
	ldr	r0, [r8, #4080]
	mov	r2, r3
	mov	r1, #113
	blx	r4
.L908:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L1018+68
	blx	r3
	mov	r0, #0
	b	.L979
.L1009:
	ldr	r2, [r6, #1364]
	ldr	r3, [r7, #68]
	ldr	r1, .L1018+72
	blx	r3
	b	.L877
.L1014:
	ldr	r3, .L1018+128
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L902
	ldr	lr, [r4, #184]
	sub	r2, fp, #172
	ldr	ip, [r4, #180]
	mov	r3, #4
	ldr	r0, [r8, #4080]
	mov	r1, #20
	add	ip, ip, lr
	add	lr, ip, #7
	cmp	ip, #0
	movlt	ip, lr
	mov	ip, ip, asr #3
	str	ip, [fp, #-172]
	blx	r5
	b	.L902
.L1011:
	ldr	r1, [r8, #4092]
	cmp	r1, #0
	bne	.L898
	ldr	r1, [r6, #1396]
	cmp	r1, #2
	beq	.L898
	ldrb	r3, [r2, #9]	@ zero_extendqisi2
	cmp	r3, #3
	ldrne	r3, [r6, #1368]
	clzne	r3, r3
	movne	r3, r3, lsr #5
	strne	r3, [r6, #1368]
.L899:
	mov	r2, #1
	ldr	r1, [r6, #1440]
	ldr	r0, [r8, #4080]
	bl	FSP_ClearLogicFs
	add	r1, r5, #33792
	add	r1, r1, #12
	ldr	r0, [r8, #4080]
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r3, .L1018+128
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L910
	mov	r3, #0
	ldr	r0, [r8, #4080]
	mov	r2, r3
	mov	r1, #113
	blx	r4
.L910:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L1018+76
	blx	r3
	mov	r0, #0
	b	.L979
.L883:
	ldr	r1, [r6, #1440]
	mov	r2, #1
	ldr	r0, [r8, #4080]
	bl	FSP_ClearLogicFs
	ldr	r1, [r9, #524]
	ldr	r3, [r6, #1440]
	mov	r0, #0
	ldr	r2, [r6, #1432]
	str	r1, [sp, #12]
	ldr	r1, [r9, #528]
	ldr	r10, [r7, #68]
	str	r1, [sp, #8]
	ldr	ip, [r9, #520]
	ldr	r1, .L1018+80
	str	ip, [sp, #4]
	ldr	ip, [r6, #1436]
	str	ip, [sp]
	blx	r10
	b	.L877
.L1012:
	cmp	r0, #0
	beq	.L901
	ldrb	r3, [r2, #22]	@ zero_extendqisi2
	cmp	r3, #3
	moveq	r3, #0
	streq	r3, [r4, #4]
	bne	.L901
	b	.L899
.L1013:
	ldr	r1, [r3, #904]
	cmp	r0, #0
	cmpne	r1, #0
	ble	.L901
	ldrb	r1, [r2, #22]	@ zero_extendqisi2
	cmp	r1, #3
	bne	.L901
	mov	r2, #0
	str	r2, [r4, #4]
	ldr	r2, [r3, #904]
	sub	r2, r2, #1
	str	r2, [r3, #904]
	b	.L899
.L1008:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r2, [r6, #1364]
	ldr	r1, .L1018+84
	blx	r3
	mov	r3, #0
	mov	r2, #1
	str	r3, [r6, #1368]
	ldr	r1, [r6, #1440]
	ldr	r0, [r8, #4080]
	bl	FSP_ClearLogicFs
	ldr	r3, [fp, #-176]
	ldrb	r3, [r3, #22]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L983
	ldr	r3, [r6, #1356]
	add	r2, r4, #45056
	str	r2, [fp, #-180]
	orr	r3, r3, #192
	str	r3, [r6, #1356]
	b	.L866
.L1001:
	ldr	r6, [r7, #68]
	movw	r3, #913
	ldr	r2, .L1018+120
	mov	r0, #1
	ldr	r1, .L1018+88
	blx	r6
	ldr	r9, .L1018+128
	b	.L824
.L831:
	ldr	r2, [fp, #-176]
	mov	r1, #1
	str	r1, [fp, #-180]
	ldrb	r3, [r2, #22]	@ zero_extendqisi2
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	b	.L837
.L1015:
	ldr	r2, [r6, #1364]
	mov	r0, #1
	str	r1, [sp]
	ldr	ip, [r7, #68]
	ldr	r1, .L1018+92
	blx	ip
	mov	r2, #1
	ldr	r1, [r6, #1440]
	ldr	r0, [r8, #4080]
	bl	FSP_ClearLogicFs
	ldr	r3, [fp, #-176]
	ldrb	r3, [r3, #22]	@ zero_extendqisi2
	cmp	r3, #3
	ldrne	r3, [r6, #1356]
	orrne	r3, r3, #192
	strne	r3, [r6, #1356]
	b	.L869
.L1003:
	cmp	r3, #0
	ldr	r3, [r4]
	ldr	r2, [r9, #200]
	ldr	r3, [r3]
	bne	.L856
	cmp	r2, r3
	bhi	.L856
	cmp	r1, #0
	bne	.L858
	ldr	r2, [r0, #200]
	cmp	r3, r2
	bcs	.L854
.L858:
	ldr	r2, [r0, #200]
	mov	r0, #1
	ldr	r6, [r7, #68]
	ldr	r1, .L1018+96
	blx	r6
	ldr	r9, .L1018+128
	b	.L824
.L856:
	ldr	r6, [r7, #68]
	mov	r0, #1
	ldr	r1, .L1018+100
	blx	r6
	ldr	r9, .L1018+128
	b	.L824
.L1004:
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	ldr	r1, [r6, #1520]
	add	r3, r2, r3
	add	r3, r3, #1
	add	r3, r3, r1
	str	r3, [r6, #1520]
	mov	r3, r3, asl #1
	str	r3, [r6, #1516]
	b	.L862
.L1006:
	cmp	r3, #2
	beq	.L1016
.L838:
	ldr	r2, [fp, #-176]
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	cmp	r1, #3
	beq	.L919
	ldr	r3, [r6, #1368]
	mov	r1, #0
	str	r1, [fp, #-180]
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r6, #1368]
	ldrb	r3, [r2, #22]	@ zero_extendqisi2
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	b	.L837
.L996:
	mov	r3, #0
	str	r3, [r8, #4092]
	ldr	r3, [fp, #-176]
	ldrb	r2, [r3, #22]	@ zero_extendqisi2
	cmp	r2, #3
	bne	.L840
.L843:
	ldr	r3, [fp, #-176]
	ldrb	r1, [r3, #9]	@ zero_extendqisi2
	cmp	r1, #3
	beq	.L1017
	ldr	r3, [r6, #1368]
	mov	r2, #0
	str	r2, [fp, #-180]
	ldr	r2, [fp, #-176]
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r6, #1368]
	ldrb	r3, [r2, #22]	@ zero_extendqisi2
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	b	.L837
.L997:
	ldr	r2, [r8, #4092]
	cmp	r2, #0
	beq	.L843
	b	.L917
.L1005:
	ldr	r2, [r6, #1520]
	ldr	r3, [r6, #1516]
	add	r2, r2, #1
	str	r2, [r6, #1520]
	ldr	r2, [fp, #-176]
	ldrb	r2, [r2, #16]	@ zero_extendqisi2
	add	r2, r2, #2
	add	r3, r3, r2
	str	r3, [r6, #1516]
	b	.L862
.L999:
	ldr	r2, .L1018
	mov	r0, #1
	ldr	r1, .L1018+104
	str	r3, [fp, #-180]
	ldr	r2, [r2, #68]
	blx	r2
	b	.L846
.L1019:
	.align	2
.L1018:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC54
	.word	.LC55
	.word	.LC68
	.word	.LANCHOR0+1596
	.word	.LC1
	.word	.LC58
	.word	.LC60
	.word	.LC57
	.word	.LC56
	.word	.LC65
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LC77
	.word	.LANCHOR0+1632
	.word	.LC75
	.word	.LC78
	.word	.LC71
	.word	.LC79
	.word	.LC76
	.word	.LC69
	.word	.LC63
	.word	.LC70
	.word	.LC67
	.word	.LC66
	.word	.LC61
	.word	.LC62
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	.word	.LANCHOR0+1612
	.word	.LC64
	.word	g_event_report
.L1000:
	mov	r2, #0
	ldr	r3, [r7, #68]
	ldr	r1, .L1018+108
	mov	r0, #1
	str	r2, [fp, #-180]
	blx	r3
	b	.L846
.L919:
	mov	r2, #0
	str	r2, [fp, #-180]
	b	.L837
.L1007:
	ldr	r3, .L1018+112
	ldr	r1, .L1018+116
	str	r2, [fp, #-180]
	ldr	r3, [r3, #68]
	blx	r3
	b	.L846
.L852:
	ldr	r6, [r7, #68]
	movw	r3, #923
	ldr	r2, .L1018+120
	mov	r0, #1
	ldr	r1, .L1018+124
	blx	r6
	ldr	r9, .L1018+128
	b	.L824
.L1016:
	add	r2, r4, #45056
	mov	r1, r2
	ldrb	r2, [r2, #273]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L838
	ldrb	r2, [r1, #272]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L838
	str	r2, [fp, #-180]
	ldr	r2, [fp, #-176]
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	b	.L837
.L1017:
	mov	r2, #0
	mov	r3, r1
	str	r2, [fp, #-180]
	b	.L837
	UNWIND(.fnend)
	.size	MPEG2DEC_Decode, .-MPEG2DEC_Decode
	.align	2
	.global	MP2_GetPacketState
	.type	MP2_GetPacketState, %function
MP2_GetPacketState:
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
	beq	.L1024
	add	r4, r4, #114688
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r0, #0
	moveq	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1024:
	ldr	ip, .L1025
	movw	r3, #4159
	ldr	r2, .L1025+4
	mov	r0, #1
	ldr	r1, .L1025+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1026:
	.align	2
.L1025:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1760
	.word	.LC1
	UNWIND(.fnend)
	.size	MP2_GetPacketState, .-MP2_GetPacketState
	.global	g_tmpusd
	.global	zigzag
	.global	default_intra_quantizer_matrix
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	CSWTCH.45, %object
	.size	CSWTCH.45, 12
CSWTCH.45:
	.word	5
	.word	1
	.word	2
	.type	__func__.13763, %object
	.size	__func__.13763, 11
__func__.13763:
	.ascii	"MP2_ExitMb\000"
	.space	1
	.type	__func__.13260, %object
	.size	__func__.13260, 18
__func__.13260:
	.ascii	"MP2_ArrangeVHBMem\000"
	.space	2
	.type	__func__.13348, %object
	.size	__func__.13348, 20
__func__.13348:
	.ascii	"MP2_GetSequenceInfo\000"
	.type	__func__.13409, %object
	.size	__func__.13409, 21
__func__.13409:
	.ascii	"MP2_ProtocolPPSCheck\000"
	.space	3
	.type	__func__.13422, %object
	.size	__func__.13422, 19
__func__.13422:
	.ascii	"MP2_GetImageBuffer\000"
	.space	1
	.type	__func__.13433, %object
	.size	__func__.13433, 14
__func__.13433:
	.ascii	"MP2_SetVDMInf\000"
	.space	2
	.type	__func__.13440, %object
	.size	__func__.13440, 20
__func__.13440:
	.ascii	"MP2_RecordVFMWState\000"
	.type	__func__.13454, %object
	.size	__func__.13454, 15
__func__.13454:
	.ascii	"MP2_GetUsrData\000"
	.space	1
	.type	__func__.13474, %object
	.size	__func__.13474, 16
__func__.13474:
	.ascii	"next_start_code\000"
	.type	__func__.13294, %object
	.size	__func__.13294, 12
__func__.13294:
	.ascii	"GetSliceHdr\000"
	.type	__func__.13489, %object
	.size	__func__.13489, 16
__func__.13489:
	.ascii	"sequence_header\000"
	.type	__func__.13507, %object
	.size	__func__.13507, 25
__func__.13507:
	.ascii	"group_of_pictures_header\000"
	.space	3
	.type	__func__.13592, %object
	.size	__func__.13592, 22
__func__.13592:
	.ascii	"extra_bit_information\000"
	.space	2
	.type	__func__.13515, %object
	.size	__func__.13515, 15
__func__.13515:
	.ascii	"picture_header\000"
	.space	1
	.type	__func__.13600, %object
	.size	__func__.13600, 20
__func__.13600:
	.ascii	"copyright_extension\000"
	.type	__func__.13608, %object
	.size	__func__.13608, 10
__func__.13608:
	.ascii	"extension\000"
	.space	2
	.type	frame_rate_Table, %object
	.size	frame_rate_Table, 64
frame_rate_Table:
	.word	0
	.word	24551
	.word	24576
	.word	25600
	.word	30689
	.word	30720
	.word	51200
	.word	61378
	.word	61440
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.type	__func__.13633, %object
	.size	__func__.13633, 14
__func__.13633:
	.ascii	"MPEG2DEC_Init\000"
	.space	2
	.type	__func__.13638, %object
	.size	__func__.13638, 17
__func__.13638:
	.ascii	"MPEG2DEC_Destroy\000"
	.space	3
	.type	__func__.13664, %object
	.size	__func__.13664, 22
__func__.13664:
	.ascii	"MPEG2DEC_GetRemainImg\000"
	.space	2
	.type	__func__.13696, %object
	.size	__func__.13696, 24
__func__.13696:
	.ascii	"MPEG2DEC_GetImageBuffer\000"
	.type	__func__.13707, %object
	.size	__func__.13707, 19
__func__.13707:
	.ascii	"MP2_ClearCurPacket\000"
	.space	1
	.type	__func__.13702, %object
	.size	__func__.13702, 18
__func__.13702:
	.ascii	"MP2_ReceivePacket\000"
	.space	2
	.type	__func__.13713, %object
	.size	__func__.13713, 16
__func__.13713:
	.ascii	"MP2_ClearCurPic\000"
	.type	__func__.13680, %object
	.size	__func__.13680, 21
__func__.13680:
	.ascii	"MPEG2DEC_VDMPostProc\000"
	.space	3
	.type	__func__.13737, %object
	.size	__func__.13737, 19
__func__.13737:
	.ascii	"MP2_DecSliceHeader\000"
	.space	1
	.type	__func__.13774, %object
	.size	__func__.13774, 19
__func__.13774:
	.ascii	"MP2_WriteSliceInfo\000"
	.space	1
	.type	tab_for_first_4bit, %object
	.size	tab_for_first_4bit, 128
tab_for_first_4bit:
	.word	8
	.word	4
	.word	9
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	3
	.word	2
	.word	3
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.type	tab_for_last_7bit, %object
	.size	tab_for_last_7bit, 832
tab_for_last_7bit:
	.word	33
	.word	11
	.word	32
	.word	11
	.word	31
	.word	11
	.word	30
	.word	11
	.word	29
	.word	11
	.word	28
	.word	11
	.word	27
	.word	11
	.word	26
	.word	11
	.word	25
	.word	11
	.word	24
	.word	11
	.word	23
	.word	11
	.word	22
	.word	11
	.word	21
	.word	10
	.word	21
	.word	10
	.word	20
	.word	10
	.word	20
	.word	10
	.word	19
	.word	10
	.word	19
	.word	10
	.word	18
	.word	10
	.word	18
	.word	10
	.word	17
	.word	10
	.word	17
	.word	10
	.word	16
	.word	10
	.word	16
	.word	10
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.type	__func__.13756, %object
	.size	__func__.13756, 11
__func__.13756:
	.ascii	"MP2_InitMb\000"
	.space	1
	.type	__func__.13730, %object
	.size	__func__.13730, 22
__func__.13730:
	.ascii	"MP2_GetFirstMbInSlice\000"
	.space	2
	.type	__func__.13725, %object
	.size	__func__.13725, 13
__func__.13725:
	.ascii	"MP2_DecSlice\000"
	.space	3
	.type	__func__.13276, %object
	.size	__func__.13276, 11
__func__.13276:
	.ascii	"MP2_GetHDR\000"
	.space	1
	.type	__func__.13645, %object
	.size	__func__.13645, 16
__func__.13645:
	.ascii	"MPEG2DEC_Decode\000"
	.type	__FUNCTION__.13314, %object
	.size	__FUNCTION__.13314, 19
__FUNCTION__.13314:
	.ascii	"MP2_DecodingDecide\000"
	.space	1
.LC0:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	10
	.word	12
	.word	14
	.word	16
	.word	18
	.word	20
	.word	22
	.word	24
	.word	28
	.word	32
	.word	36
	.word	40
	.word	44
	.word	48
	.word	52
	.word	56
	.word	64
	.word	72
	.word	80
	.word	88
	.word	96
	.word	104
	.word	112
	.type	__func__.13785, %object
	.size	__func__.13785, 19
__func__.13785:
	.ascii	"MP2_GetPacketState\000"
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	default_intra_quantizer_matrix, %object
	.size	default_intra_quantizer_matrix, 64
default_intra_quantizer_matrix:
	.byte	8
	.byte	16
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	16
	.byte	16
	.byte	22
	.byte	24
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	34
	.byte	38
	.byte	22
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	40
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	58
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	27
	.byte	29
	.byte	35
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	83
	.type	zigzag, %object
	.size	zigzag, 64
zigzag:
	.byte	0
	.byte	1
	.byte	8
	.byte	16
	.byte	9
	.byte	2
	.byte	3
	.byte	10
	.byte	17
	.byte	24
	.byte	32
	.byte	25
	.byte	18
	.byte	11
	.byte	4
	.byte	5
	.byte	12
	.byte	19
	.byte	26
	.byte	33
	.byte	40
	.byte	48
	.byte	41
	.byte	34
	.byte	27
	.byte	20
	.byte	13
	.byte	6
	.byte	7
	.byte	14
	.byte	21
	.byte	28
	.byte	35
	.byte	42
	.byte	49
	.byte	56
	.byte	57
	.byte	50
	.byte	43
	.byte	36
	.byte	29
	.byte	22
	.byte	15
	.byte	23
	.byte	30
	.byte	37
	.byte	44
	.byte	51
	.byte	58
	.byte	59
	.byte	52
	.byte	45
	.byte	38
	.byte	31
	.byte	39
	.byte	46
	.byte	53
	.byte	60
	.byte	61
	.byte	54
	.byte	47
	.byte	55
	.byte	62
	.byte	63
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	ASCII(.ascii	"[%s %d]assert warning\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC3:
	ASCII(.ascii	"mp2 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"Protocol %d\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"seq size change, call vpss to release all frames.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC8:
	ASCII(.ascii	"new seq size %dx%d\012\000" )
.LC9:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"\012mpeg2 copy last 3 bytes of the first packet!\012" )
	ASCII(.ascii	"\012\000" )
.LC14:
	ASCII(.ascii	"pMp2CodecInfo->pUsrDatArray[%d] is null\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"ERROR: unsupported profile %d\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"ERROR: unsupported level %d\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC18:
	ASCII(.ascii	"Decoding quits at frm %d\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
.LC20:
	ASCII(.ascii	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\012\000" )
.LC21:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"pImg is null, pCurImg %#x pBwdImg %#x pFwdImg %#x\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC23:
	ASCII(.ascii	"DEBUG: DEC over\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"%-40s%20d\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"slice_vertical_position\000" )
.LC28:
	ASCII(.ascii	"quantiser_scale_code\000" )
	.space	3
.LC29:
	ASCII(.ascii	"extra_bit_slice\000" )
.LC30:
	ASCII(.ascii	"intra_slice_flag\000" )
	.space	3
.LC31:
	ASCII(.ascii	"intra_slice\000" )
.LC32:
	ASCII(.ascii	"reserved_bits\000" )
	.space	2
.LC33:
	ASCII(.ascii	"extra_infrmation_slice\000" )
	.space	1
.LC34:
	ASCII(.ascii	"Slice num = %d >= %d\012\000" )
	.space	2
.LC35:
	ASCII(.ascii	"seg info is wrong! IsLastSeg[0] = %d, IsLastSeg[1] " )
	ASCII(.ascii	"= %d\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"macroblock_address_increment\000" )
	.space	3
.LC37:
	ASCII(.ascii	"macroblock_escape ERROR\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"macroblock_escape\000" )
	.space	2
.LC39:
	ASCII(.ascii	"SlcStartMbNum = %d > PicEndMum = %d\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"FirstMbInSliceFlag = %d\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"MP2_GetFirstMbInSlice Failed!\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"MP2_WriteSliceInfo Failed!\012\000" )
.LC43:
	ASCII(.ascii	"found sh %#x\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"SEQUENCE_HEADER_CODE Bitstream is not enough!\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"found gh %#x\012\000" )
	.space	2
.LC46:
	ASCII(.ascii	"GROUP_START_CODE Bitstream is not enough!\012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"found ph %#x\012\000" )
	.space	2
.LC48:
	ASCII(.ascii	"PICTURE_START_CODE Bitstream is not enough!\012\000" )
	.space	3
.LC49:
	ASCII(.ascii	"found ud %#x\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"get usd err\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"cann't get ud pointer\012\000" )
	.space	1
.LC52:
	ASCII(.ascii	"found ext %#x\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"MP2_DecSlice is wrong!\012\000" )
.LC54:
	ASCII(.ascii	"line %d, MP2_ReceivePacket receive packet failed!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC55:
	ASCII(.ascii	"ERROR: frm %d, integrality: %#x\012\000" )
	.space	3
.LC56:
	ASCII(.ascii	"ERROR: frm %d, No Img buffer is allocated\012\000" )
	.space	1
.LC57:
	ASCII(.ascii	"----------------- mp2 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC58:
	ASCII(.ascii	"frm %d pic type %d struct is %d total pos %#x\012\000" )
	.space	1
.LC59:
	ASCII(.ascii	"NOTE: Drop non-I, cur is B\012\000" )
.LC60:
	ASCII(.ascii	"NOTE: Drop non-I, cur is P\012\000" )
.LC61:
	ASCII(.ascii	"NOTE: Drop non-I\012\000" )
	.space	2
.LC62:
	ASCII(.ascii	"NOTE: Drop B\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"%s %d pFwdImg = NULL,  pBwdImg = NULL!!\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"fuction return value is null,%s %d !!\012\000" )
	.space	1
.LC65:
	ASCII(.ascii	"dec P frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC66:
	ASCII(.ascii	"dec B frame, bwd ref err(%d) > ref_thr(%d)\012\000" )
.LC67:
	ASCII(.ascii	"dec B frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC68:
	ASCII(.ascii	"MP2 Decode Decide is wrong!\012\000" )
	.space	3
.LC69:
	ASCII(.ascii	"ERROR: frm %d, lost one field\012\000" )
	.space	1
.LC70:
	ASCII(.ascii	"ERROR: frm %d, lost one field flg = %d, last_struct" )
	ASCII(.ascii	" = %d\012\000" )
	.space	2
.LC71:
	ASCII(.ascii	"Fatal Error: frm%d, get image buffer failed\012\000" )
	.space	3
.LC72:
	ASCII(.ascii	"dec_pts: %lld Usertag: %lld\012\000" )
	.space	3
.LC73:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC74:
	ASCII(.ascii	"++++++++++ ref %d\012\000" )
	.space	1
.LC75:
	ASCII(.ascii	"line: %d(pCur, pFwd, pBwd)(%p, %p, %p)\012\000" )
.LC76:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC77:
	ASCII(.ascii	"dec addr: cur,cur2d,fwd,bwd,pmv = %p,%p,%p,%p,%p\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC78:
	ASCII(.ascii	"MP2 get picture info is wrong!\012\000" )
.LC79:
	ASCII(.ascii	"MP2 dec new pic failed!\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	g_tmpusd, %object
	.size	g_tmpusd, 1024
g_tmpusd:
	.space	1024
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
