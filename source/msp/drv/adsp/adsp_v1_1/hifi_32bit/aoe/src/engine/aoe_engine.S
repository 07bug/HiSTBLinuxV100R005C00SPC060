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
	.file	"aoe_engine.c"
	.text
	.align	2
	.type	ENGINECheckAipData, %function
ENGINECheckAipData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #32]
	ldr	r1, [r0, #36]
	ldr	r3, [r0, #40]
	cmp	r2, #0
	cmpne	r1, #0
	beq	.L2
	cmp	r2, #0
	moveq	r0, r2
	beq	.L3
	mov	ip, #0
	mov	r4, #1
	mov	r0, ip
.L5:
	mov	lr, r4, asl ip
	tst	lr, r2
	beq	.L6
	ands	lr, lr, r3
	mov	r0, #1
	beq	.L24
.L6:
	add	ip, ip, #1
	cmp	ip, #8
	bne	.L5
.L3:
	cmp	r1, #0
	movne	r2, #0
	movne	lr, #1
	beq	.L9
.L8:
	mov	ip, lr, asl r2
	tst	ip, r1
	beq	.L11
	tst	ip, r3
	beq	.L25
	orr	r0, r0, #2
.L11:
	add	r2, r2, #1
	cmp	r2, #8
	bne	.L8
.L9:
	and	r0, r0, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L2:
	cmp	r3, #0
	beq	.L26
	mov	r0, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L26:
	ldr	r0, [r0, #200]
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L24:
	mov	r0, lr
	b	.L3
.L25:
	bic	r0, r0, #2
	b	.L9
	UNWIND(.fnend)
	.size	ENGINECheckAipData, .-ENGINECheckAipData
	.align	2
	.type	ENGINECheckAopSpace, %function
ENGINECheckAopSpace:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #64]
	ldr	lr, [r0, #48]
	cmp	r3, #0
	ldr	r0, [r0, #52]
	beq	.L42
	cmp	lr, #0
	beq	.L29
	mov	r2, #0
	mov	r4, #1
	mov	ip, r2
.L31:
	mov	r1, r4, asl r2
	tst	r1, lr
	beq	.L33
	ands	r1, r1, r3
	mov	ip, #1
	beq	.L48
.L33:
	add	r2, r2, #1
	cmp	r2, #8
	bne	.L31
.L32:
	cmp	r0, #0
	beq	.L41
.L39:
	mov	r2, #0
	mov	r4, #1
.L35:
	mov	r1, r4, asl r2
	tst	r1, r0
	beq	.L38
	tst	r1, r3
	beq	.L49
	orr	ip, ip, #2
.L38:
	add	r2, r2, #1
	cmp	r2, #8
	bne	.L35
.L36:
	cmp	lr, #0
	bne	.L41
	and	r0, ip, #2
	ldmfd	sp, {r4, fp, sp, pc}
.L29:
	cmp	r0, #0
	movne	ip, lr
	ldmeqfd	sp, {r4, fp, sp, pc}
	b	.L39
.L42:
	mov	r0, r3
	ldmfd	sp, {r4, fp, sp, pc}
.L41:
	and	r0, ip, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L48:
	mov	ip, r1
	b	.L32
.L49:
	bic	ip, ip, #2
	b	.L36
	UNWIND(.fnend)
	.size	ENGINECheckAopSpace, .-ENGINECheckAopSpace
	.align	2
	.type	ENGINEDestroyChn, %function
ENGINEDestroyChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #12]
	cmp	r3, #0
	bne	.L52
	ldr	r1, [r4, #76]
	cmp	r1, #0
	beq	.L53
	mov	r0, #26
	bl	HI_ADSP_FREE
	ldr	r3, [r4, #12]
	cmp	r3, #0
	bne	.L52
.L53:
	ldr	r1, [r4, #144]
	cmp	r1, #0
	beq	.L52
	mov	r0, #26
	bl	HI_ADSP_FREE
	mov	r3, #0
	str	r3, [r4, #144]
.L52:
	mov	r1, r4
	mov	r0, #26
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HI_ADSP_FREE
	UNWIND(.fnend)
	.size	ENGINEDestroyChn, .-ENGINEDestroyChn
	.align	2
	.type	ENGINEOutRawFrame, %function
ENGINEOutRawFrame:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r1
	mov	r7, r2
	mov	r6, r0
	bl	AIP_GetRingIn
	mov	r4, r0
	mov	r0, r5
	bl	AOP_GetRingOut
	mov	r5, r0
	mov	r0, r6
	bl	AIP_GetMuteStatus
	cmp	r0, #1
	beq	.L63
.L61:
	cmp	r5, #0
	cmpne	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r2, r7
	mov	r1, r5
	mov	r0, r4
	mov	r3, #3
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RBUF_CopyData
.L63:
	mov	r0, r6
	mov	r1, r7
	bl	AIP_MuteRawData
	b	.L61
	UNWIND(.fnend)
	.size	ENGINEOutRawFrame, .-ENGINEOutRawFrame
	.global	__aeabi_uidiv
	.align	2
	.type	ENGINEMixData, %function
ENGINEMixData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	mov	r4, r0
	mov	r5, r1
	mov	r0, r1
	sub	r1, fp, #72
	mov	r3, #0
	mov	r6, r2
	str	r3, [fp, #-72]
	str	r3, [fp, #-68]
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	ldr	r7, [r4, #4]
	ldr	r8, [r4]
	bl	AIP_QueryFiFoInfo
	ldr	r0, [r4, #120]
	ldr	r3, [fp, #-52]
	ldr	r9, [fp, #-56]
	cmp	r3, r0
	bcc	.L64
	cmp	r9, r0
	ldr	r1, [r4, #124]
	bcc	.L68
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-68]
	ldr	r1, [fp, #-72]
	mov	r3, r8
	add	r1, r1, r2
	mul	r2, r7, r0
	mov	r0, r6
	bl	UTIL_MixerPro
.L67:
	ldr	r1, [r4, #120]
	mov	r0, r5
	bl	AIP_ReadDataComplete
.L64:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L68:
	mov	r0, r9
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-68]
	ldr	r1, [fp, #-72]
	mov	r3, r8
	add	r1, r1, r2
	mul	r2, r7, r0
	mov	r0, r6
	bl	UTIL_MixerPro
	ldr	r0, [r4, #120]
	ldr	r1, [r4, #124]
	rsb	r0, r9, r0
	bl	__aeabi_uidiv
	mov	r3, r8
	ldr	r1, [fp, #-72]
	mul	r2, r7, r0
	add	r0, r6, r9
	bl	UTIL_MixerPro
	b	.L67
	UNWIND(.fnend)
	.size	ENGINEMixData, .-ENGINEMixData
	.align	2
	.type	ENGINEReclaimIn, %function
ENGINEReclaimIn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #5
	mov	r5, r1
	mov	r6, r2
	bhi	.L72
	ldr	r3, .L74
	add	r0, r0, #6
	ldr	r4, [r3, r0, asl #2]
	cmp	r1, #0
	cmpne	r4, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L72
	ldr	r3, [r4, #120]
	cmp	r2, r3
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r4, #124]
	mov	r0, r2
	bl	__aeabi_uidiv
	ldr	r2, [r4, #4]
	ldr	r3, [r4]
	mov	r1, r5
	mul	r2, r2, r0
	ldr	r0, [r4, #204]
	bl	UTIL_MixerPro
	mov	r3, #7
	mov	r0, r6
	str	r3, [r4, #200]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L72:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L75:
	.align	2
.L74:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	ENGINEReclaimIn, .-ENGINEReclaimIn
	.align	2
	.global	ENGINECreateAVC
	.type	ENGINECreateAVC, %function
ENGINECreateAVC:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #52)
	sub	sp, sp, #52
	mov	r4, r0
	mov	r5, r1
	sub	r0, fp, #76
	sub	r1, fp, #64
	movw	r2, #48000
	mov	r3, #2
	str	r2, [fp, #-64]
	str	r3, [fp, #-60]
	bl	iMedia_AVC_GetSize
	ldr	r1, [fp, #-76]
	mov	r0, #26
	str	r1, [r4, #80]
	bl	HI_ADSP_MALLOC
	cmp	r0, #0
	str	r0, [r4, #76]
	beq	.L81
	ldr	r6, .L82
	mov	r1, #0
	ldr	r2, [fp, #-76]
	ldr	r3, [r6, #20]
	blx	r3
	ldr	r3, [r5, #72]
	ldr	lr, [r5, #72]
	mov	ip, #0
	ldr	r1, [r5, #76]
	ubfx	r3, r3, #0, #13
	strh	r3, [fp, #-46]
	ubfx	lr, lr, #13, #13
	ubfx	r1, r1, #6, #6
	ldr	r0, [r5, #76]
	rsb	r3, r1, #0
	ldr	r2, [r5, #76]
	ubfx	r0, r0, #12, #4
	strh	lr, [fp, #-44]
	uxth	r3, r3
	strh	r3, [fp, #-40]
	and	r2, r2, #63
	strh	ip, [fp, #-48]
	sxth	r3, r3
	strh	ip, [fp, #-30]
	cmn	r3, #31
	rsb	r2, r2, #0
	strh	r0, [fp, #-38]
	add	r0, r4, #88
	movwge	r3, #65528
	mvnlt	r3, #39
	movtge	r3, 65535
	strh	r2, [fp, #-36]
	rsbge	r3, r1, r3
	mov	r2, #20
	sub	r1, fp, #48
	strh	r3, [fp, #-42]
	ldr	r3, [r6, #24]
	blx	r3
	ldr	r3, [r6, #32]
	blx	r3
	sub	r3, fp, #48
	ldr	r2, [r4, #80]
	add	r0, r4, #72
	ldr	r1, [r4, #76]
	bl	iMedia_AVC_Init
	ldr	r3, [r6, #36]
	mov	r5, r0
	blx	r3
	cmp	r5, #0
	bne	.L80
	mov	r0, r5
	str	r5, [r4, #84]
.L77:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L81:
	mvn	r0, #0
	b	.L77
.L80:
	mov	r0, #26
	ldr	r1, [r4, #76]
	bl	HI_ADSP_FREE
	mvn	r0, #0
	b	.L77
.L83:
	.align	2
.L82:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	ENGINECreateAVC, .-ENGINECreateAVC
	.align	2
	.type	ENGINECreateChn, %function
ENGINECreateChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r3, .L108
	ldr	r6, .L108+4
	mov	r2, #28
	mov	r1, #0
	mov	r7, r0
	ldr	r5, [r3, r0, asl #2]
	sub	r0, fp, #72
	ldr	r3, [r6, #20]
	blx	r3
	sub	r0, fp, #72
	ldr	r1, [r5]
	and	r1, r1, #3
	bl	AOE_REG_ReadBitDepth
	cmp	r0, #0
	bne	.L85
	ldr	r1, [r5]
	sub	r0, fp, #68
	ubfx	r1, r1, #2, #2
	bl	AOE_REG_ReadChannel
	cmp	r0, #0
	bne	.L85
	ldr	r1, [r5]
	sub	r0, fp, #64
	ubfx	r1, r1, #4, #4
	bl	AOE_REG_ReadSampelRate
	cmp	r0, #0
	bne	.L85
	ldr	r1, [r5]
	sub	r0, fp, #60
	ubfx	r1, r1, #8, #2
	bl	AOE_REG_ReadDataFormat
	subs	r8, r0, #0
	bne	.L85
	mov	r1, #232
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	subs	r4, r0, #0
	beq	.L85
	mov	r1, r8
	ldr	r3, [r6, #20]
	mov	r2, #232
	blx	r3
	ldr	r3, [r6, #24]
	mov	r2, #28
	sub	r1, fp, #72
	mov	r0, r4
	blx	r3
	ldr	r1, [r4]
	ldr	r0, [r4, #4]
	bl	UTIL_CalcFrameSize
	ldr	r2, [r4, #8]
	movw	r1, #19923
	mov	ip, #60928
	movt	r1, 4194
	movt	ip, 2
	add	r3, r2, r2, lsl #2
	movw	lr, #48000
	cmp	r2, lr
	cmpne	r2, ip
	umull	r2, r3, r3, r1
	mov	r3, r3, lsr #6
	beq	.L106
	tst	r3, #3
	bicne	r3, r3, #3
	addne	r3, r3, #4
.L90:
	mul	r3, r0, r3
	ldr	r1, [r4]
	ldr	r0, [r4, #4]
	str	r3, [r4, #120]
	bl	UTIL_CalcFrameSize
	ldr	r9, [r4, #120]
	mov	r1, r0
	str	r0, [r4, #124]
	mov	r0, r9
	bl	__aeabi_uidiv
	ldr	r8, [r4, #12]
	cmp	r8, #0
	str	r0, [r4, #16]
	beq	.L107
.L91:
	mov	r0, r4
	mov	r3, #1
	str	r7, [r4, #116]
	str	r3, [r4, #128]
.L105:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L106:
	tst	r3, #255
	bicne	r3, r3, #255
	addne	r3, r3, #256
	b	.L90
.L107:
	ldr	lr, [r4, #4]
	add	r1, r4, #144
	ldr	ip, [r4]
	mov	r2, #28
	ldr	r3, [r4, #8]
	str	lr, [r4, #160]
	str	ip, [r4, #156]
	str	r9, [r4, #148]
	mov	r9, r1
	str	r0, [r4, #152]
	add	r0, r4, #172
	str	r3, [r4, #164]
	str	r8, [r4, #144]
	ldr	r3, [r6, #24]
	str	r8, [r4, #168]
	blx	r3
	mov	r1, r9
	ldr	r3, [r6, #24]
	mov	r2, #28
	add	r0, r4, #204
	ldr	r10, .L108+4
	blx	r3
	ldr	r9, [r4, #148]
	ldr	r3, [r4, #176]
	mov	r0, #26
	add	r9, r3, r9, lsl #1
	mov	r1, r9
	bl	HI_ADSP_MALLOC
	subs	r6, r0, #0
	beq	.L92
	ldr	r3, [r10, #20]
	mov	r2, r9
	mov	r1, r8
	blx	r3
	ldr	r2, [r4, #12]
	ldr	r3, [r4, #148]
	cmp	r2, #0
	str	r6, [r4, #144]
	add	r6, r6, r3
	str	r6, [r4, #204]
	add	r6, r6, r3
	str	r6, [r4, #172]
	bne	.L91
	mov	r1, r5
	mov	r0, r4
	bl	ENGINECreateAVC
	cmp	r0, #0
	beq	.L91
.L92:
	mov	r0, r4
	bl	ENGINEDestroyChn
	mov	r0, #0
	b	.L105
.L85:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L109:
	.align	2
.L108:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	ENGINECreateChn, .-ENGINECreateChn
	.align	2
	.global	ENGINE_Process
	.type	ENGINE_Process, %function
ENGINE_Process:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #116)
	sub	sp, sp, #116
	ldr	r3, .L307
	mov	r9, #0
	add	r10, r3, #24
	str	r3, [fp, #-120]
	b	.L194
.L127:
	add	r9, r9, #1
	add	r10, r10, #4
	cmp	r9, #6
	beq	.L288
.L194:
	ldr	r2, [fp, #-120]
	ldr	r3, [r2], #4
	str	r2, [fp, #-120]
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #2, #1
	cmp	r2, #0
	bne	.L283
	ldr	r1, [r3, #4]
	ands	r1, r1, #3
	beq	.L113
	cmp	r1, #1
	beq	.L114
	ldr	r2, [r3, #4]
	bic	r2, r2, #120
	orr	r2, r2, #32
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
.L283:
	ldr	r4, [r10]
	cmp	r4, #0
	beq	.L127
.L126:
	ldr	r6, [r4, #128]
.L195:
	cmp	r6, #1
	bne	.L127
	ldr	r3, [fp, #-120]
	mov	r2, #0
	ldr	r1, [r4, #16]
	mov	r5, r2
	mov	r7, r2
	ldr	r8, [r3, #-4]
	ldr	r3, [r4]
	str	r3, [fp, #-148]
	ldr	r3, [r4, #4]
	str	r3, [fp, #-156]
	ldr	r3, [r8, #12]
	str	r4, [fp, #-144]
	str	r2, [fp, #-124]
	uxth	r3, r3
	str	r1, [fp, #-152]
	str	r2, [fp, #-136]
	str	r2, [fp, #-128]
	mov	r4, r3
	str	r2, [fp, #-132]
	str	r8, [fp, #-140]
	b	.L134
.L129:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L289
.L134:
	mov	r8, r6, asl r5
	tst	r8, r4
	beq	.L129
	sub	r1, fp, #80
	mov	r0, r5
	bl	AOP_GetChnStatus
	ldr	r1, [fp, #-80]
	cmp	r1, #1
	bne	.L129
	ldr	r1, [fp, #-76]
	cmp	r1, #1
	ldr	r1, [fp, #-72]
	ldreq	r3, [fp, #-132]
	ldrne	r3, [fp, #-128]
	orreq	r3, r3, r8
	orrne	r3, r3, r8
	streq	r3, [fp, #-132]
	strne	r3, [fp, #-128]
	ldr	r3, [fp, #-148]
	cmp	r3, r1
	beq	.L290
.L132:
	ldr	r3, [fp, #-124]
	orr	r3, r3, r8
	str	r3, [fp, #-124]
.L133:
	ldr	r1, [fp, #-64]
	mov	r0, r5
	ldr	r3, [fp, #-152]
	add	r5, r5, #1
	mul	r1, r1, r3
	bl	AOP_QueryRbfFree
	cmp	r0, #0
	orrne	r7, r7, r8
	cmp	r5, #8
	bne	.L134
.L289:
	mov	r3, r4
	ldr	r4, [fp, #-144]
	ldr	r8, [fp, #-140]
	mov	r6, #0
	mov	r5, #1
	str	r3, [r4, #44]
	ldr	r3, [fp, #-132]
	str	r7, [r4, #64]
	str	r6, [r4, #32]
	str	r3, [r4, #48]
	ldr	r3, [fp, #-128]
	str	r6, [r4, #36]
	str	r6, [r4, #40]
	str	r3, [r4, #52]
	ldr	r3, [fp, #-136]
	str	r3, [r4, #56]
	ldr	r3, [fp, #-124]
	str	r3, [r4, #60]
	ldr	r3, [r8, #8]
	uxth	r3, r3
	str	r3, [r4, #28]
	b	.L146
.L135:
	add	r6, r6, #1
	cmp	r6, #8
	beq	.L145
.L292:
	ldr	r3, [r4, #28]
.L146:
	mov	r7, r5, asl r6
	tst	r3, r7
	beq	.L135
	sub	r1, fp, #108
	mov	r0, r6
	bl	AIP_GetChnStatus
	ldr	r3, [fp, #-108]
	cmp	r3, #1
	beq	.L291
.L137:
	mov	r0, r6
	ldr	r2, .L307+4
	ldr	r1, [r4, #116]
	add	r6, r6, #1
	bl	AIP_RegReclaimFun
	cmp	r6, #8
	bne	.L292
.L145:
	ldr	r3, [r8, #4]
	tst	r3, #4096
	beq	.L152
	ldr	r3, [r8, #4]
	bic	r3, r3, #4096
	str	r3, [r8, #4]
	ldr	r1, [r8, #72]
	ubfx	r1, r1, #0, #13
	strh	r1, [fp, #-78]
	ldr	ip, [r8, #72]
	ubfx	ip, ip, #13, #13
	strh	ip, [fp, #-76]
	ldr	r0, [r8, #76]
	ubfx	r0, r0, #6, #6
	rsb	r2, r0, #0
	uxth	r2, r2
	strh	r2, [fp, #-72]
	ldr	lr, [r8, #76]
	sxth	r2, r2
	ubfx	lr, lr, #12, #4
	strh	lr, [fp, #-70]
	ldr	r3, [r8, #76]
	cmn	r2, #31
	and	r3, r3, #63
	movwge	r5, #65528
	rsb	r3, r3, #0
	movtge	r5, 65535
	mvnlt	r0, #39
	rsbge	r5, r0, r5
	strlth	r0, [fp, #-74]
	uxth	r3, r3
	strgeh	r5, [fp, #-74]
	strh	r3, [fp, #-68]
	ldrsh	r5, [r4, #90]
	ldr	r0, [r8, #4]
	cmp	r5, r1
	ubfx	r1, r0, #11, #1
	str	r1, [r4, #84]
	beq	.L293
.L150:
	sub	r1, fp, #44
	mov	r3, #0
	strh	r3, [fp, #-62]
	add	r5, r4, #88
	strh	r3, [r1, #-36]!
	mov	r2, #20
	ldr	r3, .L307+8
	mov	r0, r5
	ldr	r3, [r3, #24]
	blx	r3
	ldr	r3, .L307+8
	ldr	r3, [r3, #32]
	blx	r3
	mov	r3, r5
	ldr	r2, [r4, #80]
	add	r0, r4, #72
	ldr	r1, [r4, #76]
	bl	iMedia_AVC_Init
	ldr	r3, .L307+8
	ldr	r3, [r3, #36]
	blx	r3
.L152:
	ldr	r3, [r8, #4]
	ubfx	r3, r3, #13, #1
	str	r3, [r4, #108]
	ldr	r3, [r8, #4]
	ubfx	r3, r3, #14, #1
	str	r3, [r4, #112]
	ldr	r4, [r10]
	ldr	r3, [r4, #44]
	tst	r3, #1
	bne	.L208
	mov	r5, #1
	mov	r2, r5
.L155:
	ands	r1, r3, r2, asl r5
	bne	.L154
	add	r5, r5, #1
	cmp	r5, #8
	bne	.L155
.L163:
	ldr	r5, [r4, #12]
	cmp	r5, #0
	bne	.L294
	mov	r0, r4
	bl	ENGINECheckAopSpace
	cmp	r0, #0
	beq	.L127
	mov	r0, r4
	bl	ENGINECheckAipData
	cmp	r0, #0
	beq	.L127
	ldr	r3, .L307+8
	mov	r2, #5
	mov	r1, r5
	str	r2, [fp, #-80]
	ldr	r2, [r4, #148]
	ldr	r3, [r3, #20]
	ldr	r0, [r4, #144]
	blx	r3
	ldr	r3, [r4, #200]
	ldr	r6, [r4, #144]
	cmp	r3, #0
	beq	.L169
	cmp	r3, #7
	beq	.L295
	ldr	r3, .L307+8
	mov	r1, r5
	mov	r0, r6
	ldr	r2, [r4, #120]
	ldr	r3, [r3, #20]
	blx	r3
.L171:
	ldr	r3, [r4, #200]
	sub	r3, r3, #1
	str	r3, [r4, #200]
.L169:
	mov	r5, #0
	mov	r6, #1
	b	.L175
.L173:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L296
.L175:
	ldr	r3, [r4, #28]
	ands	r3, r3, r6, asl r5
	beq	.L173
	sub	r1, fp, #80
	mov	r0, r5
	bl	AIP_GetPcmType
	ldr	r3, [fp, #-80]
	cmp	r3, #1
	bhi	.L173
	ldr	r2, [r4, #144]
	mov	r1, r5
	mov	r0, r4
	bl	ENGINEMixData
	b	.L173
.L114:
	ldr	r4, [r10]
	cmp	r4, #0
	beq	.L127
	ldr	r6, [r4, #128]
	cmp	r6, #1
	beq	.L297
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L195
.L196:
	ldr	r2, [r3, #4]
	bic	r2, r2, #120
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
	b	.L126
.L113:
	ldr	r0, [r10]
	cmp	r0, #0
	beq	.L298
	ldr	r2, [r0, #128]
	cmp	r2, #0
	beq	.L299
.L120:
	mov	r2, #1
	str	r2, [r0, #128]
.L119:
	ldr	r2, [r3, #4]
	tst	r2, #4
	ldreq	r2, [r3, #4]
	biceq	r2, r2, #120
	streq	r2, [r3, #4]
	ldreq	r2, [r3, #4]
	orreq	r2, r2, #4
	streq	r2, [r3, #4]
	b	.L283
.L291:
	ldr	r3, [fp, #-104]
	ldr	r2, [r4, #120]
	cmp	r3, #1
	ldreq	r3, [r4, #32]
	ldrne	r3, [r4, #36]
	orreq	r3, r3, r7
	orrne	r3, r3, r7
	streq	r3, [r4, #32]
	strne	r3, [r4, #36]
	ldr	r3, [r4, #12]
	cmp	r3, #0
	beq	.L140
	mov	r0, r6
	str	r2, [fp, #-124]
	bl	AIP_QueryBusy
	ldr	r2, [fp, #-124]
	cmp	r2, r0
	movls	r3, r2
	bhi	.L137
	cmp	r3, #0
	ldrne	r3, [r4, #40]
	orrne	r7, r3, r7
	strne	r7, [r4, #40]
	b	.L137
.L288:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L140:
	sub	r1, fp, #80
	mov	r0, r6
	bl	AIP_GetChnStatus
	ldr	r2, [fp, #-80]
	ldr	r3, [r4, #148]
	cmp	r2, #1
	beq	.L300
.L143:
	mov	r0, r6
	str	r3, [fp, #-124]
	bl	AIP_QueryFiFoBusy
	ldr	r3, [fp, #-124]
	cmp	r0, r3
	bcc	.L137
	cmp	r3, #0
	ldrne	r3, [r4, #40]
	orrne	r7, r3, r7
	strne	r7, [r4, #40]
	b	.L137
.L299:
	bl	ENGINEDestroyChn
	mov	r0, r9
	bl	ENGINECreateChn
	ldr	r3, [fp, #-120]
	cmp	r0, #0
	str	r0, [r10]
	ldr	r3, [r3, #-4]
	bne	.L120
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L127
.L284:
	ldr	r2, [r3, #4]
	bic	r2, r2, #120
	orr	r2, r2, #24
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
	b	.L127
.L297:
	str	r2, [r4, #128]
	ldr	r2, [r3, #4]
	tst	r2, #4
	beq	.L196
	b	.L126
.L154:
	cmp	r5, #8
	beq	.L163
.L153:
	sub	r1, fp, #80
	mov	r0, r5
	bl	AOP_GetChnStatus
	ldr	r3, [fp, #-48]
	cmp	r3, #4
	bhi	.L163
	mov	r6, #0
	mov	r7, #1
	b	.L162
.L158:
	add	r6, r6, #1
	cmp	r6, #8
	beq	.L163
.L162:
	ldr	r3, [r4, #28]
	mov	r8, r7, asl r6
	tst	r8, r3
	beq	.L158
	ldr	r3, [r4, #40]
	tst	r8, r3
	bne	.L158
	mov	r0, r6
	bl	AIP_CheckDataStatusStop
	cmp	r0, #1
	beq	.L158
	sub	r1, fp, #108
	mov	r0, r6
	bl	AIP_GetChnStatus
	ldr	r3, [fp, #-108]
	sub	r3, r3, #1
	cmp	r3, #1
	bhi	.L158
	ldr	r1, [r4, #108]
	mov	r0, r6
	bl	AIP_ContinueOutput
	ldr	r3, [r4, #12]
	cmp	r3, #0
	bne	.L301
	ldr	r3, [r4, #108]
	cmp	r3, #0
	beq	.L158
	mov	r0, r6
	bl	AIP_QueryFiFoBusy
	ldr	r3, [r4, #120]
	cmp	r0, r3
	ldrcs	r3, [r4, #40]
	orrcs	r8, r3, r8
	strcs	r8, [r4, #40]
	b	.L158
.L290:
	ldr	r1, [fp, #-68]
	ldr	r3, [fp, #-156]
	cmp	r3, r1
	bne	.L132
	ldr	r3, [fp, #-136]
	orr	r3, r3, r8
	str	r3, [fp, #-136]
	b	.L133
.L293:
	ldrsh	r1, [r4, #92]
	cmp	r1, ip
	bne	.L150
	ldrsh	r1, [r4, #96]
	cmp	r1, r2
	bne	.L150
	ldrh	r2, [r4, #100]
	cmp	r3, r2
	bne	.L150
	ldrsh	r3, [r4, #98]
	cmp	r3, lr
	beq	.L152
	b	.L150
.L300:
	ldr	r2, [fp, #-64]
	cmp	r2, #1
	movne	r3, r3, asl #1
	b	.L143
.L298:
	mov	r0, r9
	bl	ENGINECreateChn
	cmp	r0, #0
	str	r0, [r10]
	beq	.L302
	mov	r3, #1
	str	r3, [r0, #128]
	ldr	r3, [fp, #-120]
	ldr	r3, [r3, #-4]
	b	.L119
.L208:
	mov	r5, #0
	b	.L153
.L296:
	mov	r3, #5
	str	r3, [fp, #-80]
	ldr	r5, [r4, #12]
	cmp	r5, #0
	beq	.L303
.L182:
	ldr	r6, [r4, #48]
	cmp	r5, #0
	ldr	r3, [r4, #52]
	str	r6, [fp, #-116]
	str	r3, [fp, #-112]
	bne	.L127
.L205:
	sub	r3, fp, #116
	str	r9, [fp, #-124]
	mov	r8, #1
	mov	r9, r3
.L203:
	cmp	r6, #0
	beq	.L193
	mov	r5, #0
	b	.L192
.L188:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L193
.L192:
	mov	r7, r8, asl r5
	tst	r7, r6
	beq	.L188
	mov	r0, r5
	bl	AOP_WriteBuffProcTryCnt
	sub	r1, fp, #80
	mov	r0, r5
	bl	AOP_GetChnStatus
	ldr	r3, [r4, #64]
	tst	r7, r3
	beq	.L188
	mov	r0, r5
	sub	r7, fp, #108
	bl	AOP_WriteBuffProcOKCnt
	ldr	r3, [r4, #68]
	mov	r2, #28
	add	r1, r4, #144
	cmp	r3, #0
	mov	r0, r7
	beq	.L190
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	beq	.L304
.L190:
	ldr	r3, .L307+8
	ldr	r3, [r3, #24]
	blx	r3
.L191:
	mov	r1, r7
	mov	r0, r5
	bl	AOP_WriteRbfData
	mov	r0, r5
	bl	AOP_ProcDelayCompensation
	b	.L188
.L303:
	mov	r6, #1
	b	.L179
.L177:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L178
.L179:
	ldr	r3, [r4, #28]
	ands	r3, r3, r6, asl r5
	beq	.L177
	sub	r1, fp, #80
	mov	r0, r5
	bl	AIP_GetPcmType
	ldr	r3, [fp, #-80]
	cmp	r3, #2
	bne	.L177
	mov	r1, r5
	ldr	r2, [r4, #144]
	mov	r0, r4
	bl	ENGINEMixData
.L178:
	ldr	r3, [r4, #12]
	cmp	r3, #0
	bne	.L127
	ldr	r3, [r4, #84]
	ldr	r5, [r4, #144]
	cmp	r3, #0
	bne	.L305
	ldr	r6, [r4, #48]
	ldr	r3, [r4, #52]
	str	r6, [fp, #-116]
	str	r3, [fp, #-112]
	b	.L205
.L193:
	sub	r3, fp, #112
	cmp	r9, r3
	ldrne	r6, [r9, #4]!
	bne	.L203
.L306:
	ldr	r9, [fp, #-124]
	b	.L127
.L305:
	bl	AOE_GetWKBuf
	ldr	r3, .L307+8
	ldr	r3, [r3, #32]
	mov	r6, r0
	blx	r3
	mov	r1, r5
	mov	r2, r6
	ldr	r0, [r4, #72]
	bl	iMedia_AVC_Apply
	ldr	r3, .L307+8
	ldr	r3, [r3, #36]
	blx	r3
	ldr	r3, .L307+8
	mov	r0, r5
	mov	r1, r6
	ldr	r2, [r4, #120]
	ldr	r3, [r3, #24]
	blx	r3
	ldr	r5, [r4, #12]
	b	.L182
.L295:
	ldr	r1, [r4, #124]
	ldr	r0, [r4, #120]
	bl	__aeabi_uidiv
	ldr	r2, [r4, #4]
	ldr	r3, [r4]
	ldr	r1, [r4, #204]
	mul	r2, r2, r0
	mov	r0, r6
	bl	UTIL_MixerPro
	ldr	r3, .L307+8
	mov	r1, r5
	ldr	r2, [r4, #120]
	ldr	r0, [r4, #204]
	ldr	r3, [r3, #20]
	blx	r3
	b	.L171
.L302:
	ldr	r3, [fp, #-120]
	ldr	r3, [r3, #-4]
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L127
	b	.L284
.L304:
	ldr	r3, .L307+8
	sub	r7, fp, #108
	add	r1, r4, #172
	mov	r0, r7
	ldr	r3, [r3, #24]
	blx	r3
	b	.L191
.L301:
	mov	r0, r6
	bl	AIP_QueryBusy
	subs	r2, r0, #0
	beq	.L161
	mov	r1, r5
	mov	r0, r6
	bl	ENGINEOutRawFrame
.L161:
	ldr	r3, [r4, #108]
	cmp	r3, #0
	beq	.L158
	ldr	r3, [r4, #112]
	mov	r0, r5
	ldr	r2, [fp, #-96]
	ldr	r1, [fp, #-100]
	bl	AOP_ContinueOutput
	b	.L158
.L294:
	ldr	r3, [r4, #44]
	tst	r3, #1
	bne	.L197
	mov	r6, #1
	mov	r2, r6
.L165:
	ands	r1, r3, r2, asl r6
	bne	.L164
	add	r6, r6, #1
	cmp	r6, #8
	bne	.L165
	ldr	r3, [r4, #28]
	tst	r3, #1
	bne	.L127
	mov	r1, #1
.L201:
	mov	r5, #1
	mov	r2, r5
	b	.L168
.L166:
	add	r5, r5, #1
	cmp	r5, #8
	beq	.L127
.L168:
	ands	r0, r3, r2, asl r5
	beq	.L166
	sub	r3, r5, #8
	clz	r3, r3
	mov	r3, r3, lsr #5
.L167:
	orrs	r3, r3, r1
	bne	.L127
.L204:
	mov	r0, r4
	bl	ENGINECheckAopSpace
	cmp	r0, #0
	beq	.L127
	mov	r0, r4
	bl	ENGINECheckAipData
	cmp	r0, #0
	beq	.L127
	mov	r0, r5
	ldr	r2, [r4, #120]
	mov	r1, r6
	bl	ENGINEOutRawFrame
	mov	r0, r6
	bl	AOP_ProcDelayCompensation
	b	.L127
.L164:
	ldr	r3, [r4, #28]
	sub	r1, r6, #8
	clz	r1, r1
	tst	r3, #1
	mov	r1, r1, lsr #5
	beq	.L201
	mov	r3, #0
	mov	r5, r3
	b	.L167
.L197:
	ldr	r3, [r4, #28]
	ands	r6, r3, #1
	moveq	r1, r6
	beq	.L201
.L210:
	mov	r5, #0
	mov	r6, r5
	b	.L204
.L308:
	.align	2
.L307:
	.word	.LANCHOR0
	.word	ENGINEReclaimIn
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	ENGINE_Process, .-ENGINE_Process
	.align	2
	.global	ENGINE_Init
	.type	ENGINE_Init, %function
ENGINE_Init:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L312
	add	r7, r0, #768
	ldr	r8, .L312+4
	mov	r4, r0
	mov	r6, #0
.L310:
	str	r4, [r5], #4
	mov	r0, r4
	ldr	r3, [r8, #20]
	mov	r2, #128
	mov	r1, #0
	add	r4, r4, #128
	blx	r3
	ldr	r3, [r4, #-124]
	orr	r3, r3, #4
	str	r3, [r4, #-124]
	ldr	r3, [r4, #-124]
	bic	r3, r3, #3
	orr	r3, r3, #1
	str	r3, [r4, #-124]
	cmp	r4, r7
	str	r6, [r5, #20]
	bne	.L310
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L313:
	.align	2
.L312:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	ENGINE_Init, .-ENGINE_Init
	.align	2
	.global	ENGINE_DeInit
	.type	ENGINE_DeInit, %function
ENGINE_DeInit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L317
	mov	r6, #0
	add	r5, r4, #24
.L315:
	ldr	r0, [r4, #4]!
	bl	ENGINEDestroyChn
	cmp	r4, r5
	str	r6, [r4]
	bne	.L315
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L318:
	.align	2
.L317:
	.word	.LANCHOR0+20
	UNWIND(.fnend)
	.size	ENGINE_DeInit, .-ENGINE_DeInit
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stEneRm, %object
	.size	g_stEneRm, 48
g_stEneRm:
	.space	48
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
