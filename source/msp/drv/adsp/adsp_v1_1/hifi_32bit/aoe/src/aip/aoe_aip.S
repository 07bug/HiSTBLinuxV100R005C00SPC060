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
	.file	"aoe_aip.c"
	.text
	.align	2
	.type	AIPCalcProcBlockSize, %function
AIPCalcProcBlockSize:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r3, r1
	mov	r4, r0
	mov	r1, r2
	mov	r0, r3
	bl	UTIL_CalcFrameSize
	add	r3, r4, r4, lsl #2
	movw	r2, #19923
	mov	r1, #25856
	movt	r2, 4194
	movt	r1, 4
	umull	r2, r3, r3, r2
	movw	r2, #48000
	cmp	r4, r1
	cmpne	r4, r2
	mov	r3, r3, lsr #6
	bne	.L2
	ands	r2, r3, #255
	addne	r3, r3, #256
	rsbne	r3, r2, r3
	mul	r0, r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2:
	tst	r3, #3
	bicne	r3, r3, #3
	addne	r3, r3, #4
	mul	r0, r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AIPCalcProcBlockSize, .-AIPCalcProcBlockSize
	.align	2
	.type	AIPDestroyChn, %function
AIPDestroyChn:
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
	ldr	r0, [r4, #132]
	mov	r3, #0
	str	r3, [r4, #156]
	cmp	r0, r3
	beq	.L13
	bl	RBUF_Destroy
.L13:
	ldr	r0, [r4, #136]
	cmp	r0, #0
	beq	.L14
	bl	RBUF_Destroy
.L14:
	ldr	r0, [r4, #148]
	cmp	r0, #0
	beq	.L15
	bl	FADE_Destroy
.L15:
	ldr	r0, [r4, #140]
	cmp	r0, #0
	beq	.L16
	bl	LSRC_Destroy
.L16:
	ldr	r0, [r4, #144]
	cmp	r0, #0
	beq	.L17
	ldr	r3, [r4, #244]
	cmp	r3, #2
	beq	.L41
.L18:
	bl	ResamplerFree
.L17:
	ldr	r1, [r4, #220]
	cmp	r1, #0
	beq	.L19
	mov	r0, #26
	bl	HI_ADSP_FREE
.L19:
	mov	r1, r4
	mov	r0, #26
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HI_ADSP_FREE
.L41:
	ldr	r1, [r4, #152]
	cmp	r1, #0
	beq	.L18
	mov	r0, #26
	bl	HI_ADSP_FREE
	b	.L17
	UNWIND(.fnend)
	.size	AIPDestroyChn, .-AIPDestroyChn
	.align	2
	.type	AIPUpdateChnState, %function
AIPUpdateChnState:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L52
	add	r2, r0, #8
	ldr	r4, [r3, r2, asl #2]
	ldr	r5, [r3, r0, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r3, #0
	str	r3, [r4, #160]
	ldr	r3, [r5, #48]
	uxtb	r3, r3
	str	r3, [r4, #164]
	ldr	r3, [r5, #48]
	ubfx	r3, r3, #8, #8
	str	r3, [r4, #168]
	ldr	r3, [r5, #76]
	uxtb	r3, r3
	str	r3, [r4, #180]
	ldr	r3, [r5, #76]
	tst	r3, #2048
	ldr	r3, [r5, #76]
	ubfxeq	r3, r3, #8, #3
	streq	r3, [r4, #184]
	beq	.L46
	tst	r3, #2048
	ldrne	r3, [r5, #76]
	ubfxne	r3, r3, #8, #3
	rsbne	r3, r3, #0
	strne	r3, [r4, #184]
.L46:
	ldr	r3, [r5, #48]
	ubfx	r3, r3, #16, #1
	str	r3, [r4, #188]
	ldr	r3, [r5, #48]
	ubfx	r3, r3, #17, #3
	str	r3, [r4, #192]
	ldr	r3, [r5, #48]
	ubfx	r3, r3, #23, #2
	str	r3, [r4, #196]
	cmp	r3, #1
	ldrne	r3, [r5, #48]
	moveq	r3, #256
	movne	r3, r3, lsr #25
	rsbne	r3, r3, #0
	str	r3, [r4, #292]
	ldr	r3, [r5, #48]
	ubfx	r3, r3, #20, #3
	str	r3, [r4, #296]
	ldr	r3, [r5, #8]
	tst	r3, #1610612736
	ldr	r3, [r5, #8]
	ubfxeq	r3, r3, #24, #5
	streq	r3, [r4, #212]
	beq	.L50
	ubfx	r3, r3, #29, #2
	cmp	r3, #1
	ldreq	r3, [r5, #8]
	ubfxeq	r3, r3, #24, #5
	rsbeq	r3, r3, #0
	streq	r3, [r4, #212]
.L50:
	ldr	r3, [r5]
	ldr	r2, [r4, #88]
	ubfx	r3, r3, #14, #1
	str	r3, [r4, #4]
	ldr	r3, [r5, #4]
	ldr	r1, [r4, #232]
	ubfx	r3, r3, #24, #1
	str	r3, [r4, #248]
	ldr	r3, [r5, #76]
	ubfx	r3, r3, #24, #1
	str	r3, [r4, #252]
	ldr	r3, [r5, #76]
	ubfx	r3, r3, #12, #4
	str	r3, [r4, #260]
	ldr	r3, [r5, #76]
	ubfx	r3, r3, #16, #8
	str	r3, [r4, #264]
	ldr	r3, [r5, #8]
	ubfx	r3, r3, #15, #1
	str	r3, [r4, #256]
	ldr	r0, [r5, #4]
	ubfx	r0, r0, #10, #7
	str	r0, [r4, #128]
	bl	UTIL_LatencyMs2ByteSize
	add	r1, r4, #96
	str	r0, [r4, #124]
	ldr	r0, [r4, #136]
	bl	RBUF_UpdateAttr
	ldr	r3, [r5, #84]
	ubfx	r3, r3, #20, #1
	cmp	r3, #1
	streq	r3, [r4, #20]
	ldreq	r3, [r5, #84]
	biceq	r3, r3, #1048576
	streq	r3, [r5, #84]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L53:
	.align	2
.L52:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPUpdateChnState, .-AIPUpdateChnState
	.align	2
	.type	AIPGainPcmData, %function
AIPGainPcmData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, .L67
	mov	r4, #0
	mov	r6, r0
	mov	r2, #20
	str	r4, [fp, #-48]
	ldr	r3, [r3, #24]
	mov	r5, r1
	str	r4, [fp, #-44]
	add	r1, r6, #160
	str	r4, [fp, #-40]
	sub	r0, fp, #48
	str	r4, [fp, #-36]
	str	r4, [fp, #-32]
	blx	r3
	ldr	r3, [r6, #180]
	ldr	r2, [fp, #-44]
	ldr	r1, [fp, #-32]
	add	r2, r3, r2
	cmp	r2, #120
	subhi	r4, r2, #121
	ldr	r2, [fp, #-40]
	str	r4, [fp, #-44]
	add	r3, r3, r2
	ldr	r2, [fp, #-36]
	cmp	r3, #120
	subhi	r3, r3, #121
	movls	r3, #0
	cmp	r4, #121
	str	r3, [fp, #-40]
	ldr	r3, [r6, #184]
	add	r2, r3, r2
	add	r3, r3, r1
	str	r2, [fp, #-36]
	str	r3, [fp, #-32]
	beq	.L66
.L59:
	sub	r2, fp, #48
	mov	r0, r5
	mov	r1, #0
	bl	UTIL_LRGainProcess
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L66:
	ldr	r1, [fp, #-40]
	cmp	r2, #0
	cmpeq	r1, #121
	movne	r2, #1
	moveq	r2, #0
	cmp	r3, #0
	moveq	r3, r2
	orrne	r3, r2, #1
	cmp	r3, #0
	bne	.L59
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L68:
	.align	2
.L67:
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIPGainPcmData, .-AIPGainPcmData
	.align	2
	.type	AIPUpdateTrackLatency, %function
AIPUpdateTrackLatency:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	mov	r5, r0
	mov	r6, r1
	mov	r0, #0
	sub	r1, fp, #64
	bl	AOP_GetChnStatus
	ldr	r0, [r5, #136]
	bl	RBUF_QueryBusy
	ldr	r2, [r5, #88]
	ldr	r1, [r5, #232]
	bl	UTIL_LatencyMs
	mov	r4, r0
	ldr	r0, [r5, #132]
	bl	RBUF_QueryBusy
	ldr	r2, [r5, #32]
	ldr	r1, [r5, #236]
	bl	UTIL_LatencyMs
	ldr	r3, [fp, #-32]
	add	r0, r4, r0
	add	r0, r0, r3
	ldr	r3, [r6, #56]
	cmp	r0, #1000
	ubfxcc	r0, r0, #0, #10
	biccc	r3, r3, #66846720
	orrcs	r3, r3, #66846720
	biccc	r3, r3, #196608
	orrcc	r0, r3, r0, asl #16
	orrcs	r3, r3, #196608
	strcc	r0, [r6, #56]
	strcs	r3, [r6, #56]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	AIPUpdateTrackLatency, .-AIPUpdateTrackLatency
	.align	2
	.type	AIPReclaimFifo, %function
AIPReclaimFifo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #136]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	bl	RBUF_QueryBusy
	ldr	r3, [r4, #228]
	cmp	r0, r3
	bcc	.L84
	bl	AOE_GetWKBuf
	ldr	r5, [r4, #228]
	mov	r2, r5
	mov	r1, r0
	mov	r6, r0
	ldr	r0, [r4, #136]
	bl	RBUF_ReadData
	cmp	r5, r0
	bne	.L84
	ldr	r3, [r4, #256]
	cmp	r3, #0
	bne	.L85
.L76:
	ldr	r3, [r4, #320]
	ldr	r2, [r4, #228]
	cmp	r3, #0
	ldr	r0, [r4, #316]
	beq	.L77
	mov	r1, r6
	blx	r3
.L77:
	ldr	r0, [r4, #136]
	bl	RBUF_Flush
	ldr	r2, [r4, #228]
	ldr	r0, [r4, #136]
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RBUF_WriteData
.L84:
	ldr	r0, [r4, #136]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RBUF_Flush
.L85:
	ldr	r0, [r4, #148]
	mov	r2, #6
	mov	r1, #2
	bl	FADE_Active
	mov	r2, #256
	mov	r1, r6
	ldr	r0, [r4, #148]
	bl	FADE_OutProcess
	b	.L76
	UNWIND(.fnend)
	.size	AIPReclaimFifo, .-AIPReclaimFifo
	.align	2
	.global	AIP_GetPcmType
	.type	AIP_GetPcmType, %function
AIP_GetPcmType:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L89
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r3, [r3]
	moveq	r3, #5
	ubfxne	r3, r3, #11, #3
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L90:
	.align	2
.L89:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_GetPcmType, .-AIP_GetPcmType
	.align	2
	.global	AIPGetRbfFiFoAttr
	.type	AIPGetRbfFiFoAttr, %function
AIPGetRbfFiFoAttr:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, .L95
	mov	r4, r1
	ldr	r5, [r3, r0, asl #2]
	add	r0, r1, #80
	ldr	r1, [r5, #4]
	and	r1, r1, #3
	bl	AOE_REG_ReadBitDepth
	cmp	r0, #0
	bne	.L94
	ldr	r1, [r5, #4]
	add	r0, r4, #84
	ubfx	r1, r1, #2, #2
	bl	AOE_REG_ReadChannel
	cmp	r0, #0
	bne	.L94
	ldr	r1, [r5, #4]
	add	r0, r4, #88
	ubfx	r1, r1, #4, #4
	bl	AOE_REG_ReadSampelRate
	cmp	r0, #0
	bne	.L94
	ldr	r1, [r5, #4]
	add	r0, r4, #92
	ubfx	r1, r1, #8, #2
	bl	AOE_REG_ReadDataFormat
	cmp	r0, #0
	bne	.L94
	ldr	r1, [r5, #4]
	sub	r0, fp, #32
	ubfx	r1, r1, #10, #7
	bl	AOE_REG_ReadBufLatencyMs
	subs	r6, r0, #0
	bne	.L94
	ldr	r3, [fp, #-32]
	cmp	r3, #80
	bhi	.L94
	ldr	r1, [r4, #80]
	ldr	r0, [r4, #84]
	bl	UTIL_CalcFrameSize
	ldr	r2, [r4, #88]
	str	r6, [r4, #96]
	str	r6, [r4, #116]
	mov	r7, r0
	mov	r1, r0
	mov	r0, #80
	bl	UTIL_LatencyMs2ByteSize
	ldr	r3, [fp, #-32]
	add	r2, r5, #68
	str	r7, [r4, #120]
	str	r2, [r4, #108]
	mov	r1, r7
	add	r5, r5, #72
	str	r3, [r4, #128]
	str	r5, [r4, #112]
	ldr	r2, [r4, #88]
	str	r0, [r4, #104]
	mov	r0, r3
	bl	UTIL_LatencyMs2ByteSize
	str	r0, [r4, #124]
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L94:
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L96:
	.align	2
.L95:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPGetRbfFiFoAttr, .-AIPGetRbfFiFoAttr
	.align	2
	.global	AIPGetRbfInAttr
	.type	AIPGetRbfInAttr, %function
AIPGetRbfInAttr:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, .L109
	mov	r4, r1
	ldr	r5, [r3, r0, asl #2]
	add	r0, r1, #24
	ldr	r1, [r5]
	and	r1, r1, #3
	bl	AOE_REG_ReadBitDepth
	cmp	r0, #0
	bne	.L100
	ldr	r1, [r5]
	add	r0, r4, #28
	ubfx	r1, r1, #2, #3
	bl	AOE_REG_ReadChannel
	cmp	r0, #0
	bne	.L100
	ldr	r1, [r5]
	add	r0, r4, #32
	ubfx	r1, r1, #5, #4
	bl	AOE_REG_ReadSampelRate
	cmp	r0, #0
	beq	.L103
	ldr	r3, [r5]
	ubfx	r3, r3, #5, #4
	cmp	r3, #15
	beq	.L107
.L103:
	ldr	r1, [r5]
	add	r0, r4, #36
	ubfx	r1, r1, #9, #2
	bl	AOE_REG_ReadDataFormat
	cmp	r0, #0
	bne	.L100
	ldr	r1, [r5]
	mov	r0, r4
	ubfx	r1, r1, #11, #3
	bl	AOE_REG_ReadPcmType
	subs	r6, r0, #0
	bne	.L100
	ldr	r3, [r5]
	ldr	r1, [r4, #24]
	ubfx	r3, r3, #14, #1
	ldr	r0, [r4, #28]
	str	r3, [r4, #4]
	bl	UTIL_CalcFrameSize
	str	r6, [fp, #-36]
	mov	r3, #1
	str	r6, [fp, #-32]
	str	r3, [r4, #44]
	ldr	r3, [r5, #16]
	str	r3, [fp, #-36]
	ldr	r2, [fp, #-36]
	ldr	r3, [r5, #20]
	str	r2, [r4, #48]
	str	r3, [fp, #-32]
	ldr	r3, [r5, #24]
	bic	r3, r3, #-16777216
	str	r3, [r4, #52]
	ldr	r2, [r5, #24]
	tst	r2, #16777216
	bne	.L108
	add	r1, r5, #28
	add	r2, r5, #36
	str	r1, [r4, #56]
	str	r2, [r4, #60]
.L105:
	ldr	r2, [r5, #24]
	mov	ip, #0
	str	r0, [r4, #68]
	mov	r1, #16
	ubfx	r2, r2, #24, #1
	str	r3, [r4, #72]
	str	r2, [r4, #64]
	mov	r3, #2
	mov	r2, #8
	mov	r0, r6
	str	ip, [r4, #76]
	str	r1, [r4, #12]
	str	r2, [r4, #16]
	str	r3, [r4, #20]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L108:
	str	r6, [fp, #-36]
	str	r6, [fp, #-32]
	ldr	r2, [r5, #28]
	str	r2, [fp, #-36]
	ldr	r1, [fp, #-36]
	ldr	r2, [r5, #32]
	str	r1, [r4, #56]
	str	r2, [fp, #-32]
	str	r6, [fp, #-36]
	str	r6, [fp, #-32]
	ldr	r2, [r5, #36]
	str	r2, [fp, #-36]
	ldr	r1, [fp, #-36]
	ldr	r2, [r5, #40]
	str	r1, [r4, #60]
	str	r2, [fp, #-32]
	b	.L105
.L107:
	ldr	r3, [r5, #12]
	movw	r2, #56928
	movt	r2, 2
	bic	r3, r3, #-16777216
	str	r3, [r4, #32]
	sub	r3, r3, #4000
	cmp	r3, r2
	bhi	.L100
	ldr	r3, [r4, #28]
	cmp	r3, #2
	bhi	.L100
	ldr	r3, [r4, #24]
	cmp	r3, #16
	beq	.L103
.L100:
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L110:
	.align	2
.L109:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPGetRbfInAttr, .-AIPGetRbfInAttr
	.align	2
	.global	AIPGetChnCreateAttr
	.type	AIPGetChnCreateAttr, %function
AIPGetChnCreateAttr:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	mov	r5, r1
	bl	AIPGetRbfInAttr
	cmp	r0, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AIPGetRbfFiFoAttr
	UNWIND(.fnend)
	.size	AIPGetChnCreateAttr, .-AIPGetChnCreateAttr
	.align	2
	.global	AIPIsChnAttrChange
	.type	AIPIsChnAttrChange, %function
AIPIsChnAttrChange:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #140)
	sub	sp, sp, #140
	ldr	r3, .L114
	add	r2, r0, #8
	sub	r1, fp, #160
	ldr	r5, [r3, r2, asl #2]
	bl	AIPGetChnCreateAttr
	ldr	ip, [fp, #-132]
	ldr	r0, [fp, #-136]
	ldr	lr, [r5, #28]
	ldr	r1, [r5, #24]
	subs	lr, lr, ip
	ldr	r3, [r5, #32]
	ldr	r4, [fp, #-128]
	movne	lr, #1
	cmp	r1, r0
	moveq	ip, lr
	addne	ip, lr, #1
	ldr	r0, [r5, #36]
	cmp	r3, r4
	moveq	r1, ip
	addne	r1, ip, #1
	ldr	lr, [fp, #-124]
	ldr	r4, [r5]
	ldr	ip, [fp, #-160]
	cmp	r0, lr
	moveq	r2, r1
	addne	r2, r1, #1
	ldr	lr, [r5, #4]
	ldr	r1, [fp, #-156]
	cmp	r4, ip
	moveq	r3, r2
	addne	r3, r2, #1
	ldr	ip, [r5, #48]
	ldr	r2, [fp, #-112]
	cmp	lr, r1
	moveq	r0, r3
	addne	r0, r3, #1
	ldr	r1, [r5, #52]
	ldr	r3, [fp, #-108]
	cmp	ip, r2
	moveq	r4, r0
	addne	r4, r0, #1
	ldr	r2, [r5, #64]
	ldr	r0, [fp, #-96]
	cmp	r1, r3
	moveq	lr, r4
	addne	lr, r4, #1
	ldr	r6, [fp, #-80]
	ldr	r3, [r5, #80]
	cmp	r2, r0
	moveq	ip, lr
	addne	ip, lr, #1
	ldr	r4, [fp, #-76]
	ldr	r0, [r5, #84]
	cmp	r3, r6
	moveq	r1, ip
	addne	r1, ip, #1
	ldr	lr, [r5, #88]
	ldr	ip, [fp, #-72]
	cmp	r0, r4
	moveq	r2, r1
	addne	r2, r1, #1
	ldr	r0, [r5, #92]
	ldr	r1, [fp, #-68]
	cmp	lr, ip
	moveq	r3, r2
	addne	r3, r2, #1
	cmp	r0, r1
	moveq	r0, r3
	addne	r0, r3, #1
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L115:
	.align	2
.L114:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPIsChnAttrChange, .-AIPIsChnAttrChange
	.align	2
	.global	AIPCreateChn
	.type	AIPCreateChn, %function
AIPCreateChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #252)
	sub	sp, sp, #252
	ldr	r3, .L176
	sub	r1, fp, #168
	mov	r4, #0
	mov	r6, r0
	str	r4, [fp, #-276]
	ldr	r5, [r3, r0, asl #2]
	str	r4, [fp, #-272]
	str	r4, [fp, #-268]
	str	r4, [fp, #-264]
	str	r4, [fp, #-260]
	bl	AIPGetChnCreateAttr
	subs	r8, r0, #0
	movne	r3, r4
	bne	.L171
	mov	r1, #332
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	subs	r4, r0, #0
	beq	.L118
	ldr	r7, .L176+4
	mov	r2, #332
	mov	r1, r8
	ldr	r3, [r7, #20]
	blx	r3
	ldr	r3, [r7, #24]
	sub	r1, fp, #168
	mov	r2, #132
	mov	r0, r4
	blx	r3
	str	r6, [r4, #240]
	sub	r1, fp, #124
	sub	r0, fp, #264
	bl	RBUF_Create_EXT
	ldr	r3, [fp, #-264]
	cmp	r3, #0
	beq	.L118
	ldr	r2, [fp, #-132]
	str	r3, [r4, #132]
	cmp	r2, #0
	beq	.L172
	str	r8, [r5, #60]
	ldr	r3, [r5, #64]
	mov	r3, r3, lsr #16
	mov	r3, r3, asl #16
	str	r3, [r5, #64]
.L120:
	mov	r1, #768
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	cmp	r0, #0
	str	r0, [r4, #220]
	beq	.L118
	ldr	r3, [fp, #-132]
	cmp	r3, #0
	ldrne	r2, [r4]
	beq	.L173
.L122:
	ldr	r3, [r5, #8]
	cmp	r2, #4
	ubfx	r3, r3, #15, #1
	str	r3, [r4, #256]
	moveq	r3, #24576
	streq	r3, [r4, #328]
	beq	.L134
.L133:
	mov	r3, #6144
	str	r3, [r4, #328]
.L134:
	mov	r3, #0
	mov	r1, #256
	str	r3, [r4, #160]
	mov	r2, #3
	str	r3, [r4, #164]
	str	r3, [r4, #168]
	str	r3, [r4, #192]
	str	r1, [r4, #292]
	str	r2, [r4, #296]
	ldr	r1, [r4, #28]
	ldr	r2, [r4, #24]
	ldr	r0, [r4, #32]
	bl	AIPCalcProcBlockSize
	ldr	r2, [r4, #80]
	ldr	r1, [r4, #84]
	str	r0, [r4, #224]
	ldr	r0, [r4, #88]
	bl	AIPCalcProcBlockSize
	ldr	r1, [r4, #80]
	str	r0, [r4, #228]
	ldr	r0, [r4, #84]
	bl	UTIL_CalcFrameSize
	ldr	r1, [r4, #24]
	str	r0, [r4, #232]
	ldr	r0, [r4, #28]
	bl	UTIL_CalcFrameSize
	mov	r3, r4
	mov	r2, #1
	str	r2, [r4, #156]
	str	r0, [r4, #236]
.L171:
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L173:
	ldr	ip, [fp, #-136]
	ldr	r2, [fp, #-80]
	cmp	ip, r2
	beq	.L123
	cmp	ip, #32000
	beq	.L124
	bls	.L174
	movw	r3, #22664
	movt	r3, 1
	cmp	ip, r3
	beq	.L124
	bhi	.L128
	movw	r3, #44100
	cmp	ip, r3
	bne	.L124
	ldr	lr, [fp, #-84]
	mov	r0, #2
	ldr	r3, [fp, #-88]
	sub	r1, fp, #252
	str	r0, [r4, #244]
	sub	r0, fp, #256
	str	ip, [fp, #-252]
	str	r2, [fp, #-248]
	str	lr, [fp, #-240]
	str	r3, [fp, #-244]
	bl	iMedia_ASRC_GetSize
	cmp	r0, #0
	bne	.L118
	ldr	r1, [fp, #-256]
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	cmp	r0, #0
	str	r0, [r4, #152]
	beq	.L118
	ldr	r2, [fp, #-88]
	mov	r1, r0
	ldr	r6, [fp, #-84]
	sub	r3, fp, #236
	ldr	lr, [fp, #-136]
	sub	r0, fp, #276
	ldr	ip, [fp, #-80]
	str	r2, [fp, #-228]
	ldr	r2, [fp, #-256]
	str	r6, [fp, #-224]
	str	lr, [fp, #-236]
	str	ip, [fp, #-232]
	bl	iMedia_ASRC_Init
	cmp	r0, #0
	bne	.L118
	ldr	r0, [fp, #-276]
	b	.L135
.L174:
	movw	r3, #12000
	cmp	ip, r3
	beq	.L124
.L124:
	mov	r3, #1
	mov	r1, r2
	str	r3, [r4, #244]
	mov	r0, ip
	ldr	r3, [fp, #-88]
	mov	ip, #0
	ldr	r2, [fp, #-84]
	str	ip, [sp]
	bl	ResamplerCreate
	cmp	r0, #0
	str	r0, [fp, #-276]
	beq	.L118
.L135:
	ldr	r2, [fp, #-80]
	str	r0, [r4, #144]
.L123:
	ldr	ip, [fp, #-84]
	mov	r1, r2
	ldr	r3, [fp, #-88]
	sub	r0, fp, #272
	str	ip, [sp]
	bl	LSRC_Create
	ldr	r3, [fp, #-272]
	cmp	r3, #0
	beq	.L118
	str	r3, [r4, #140]
	mov	r6, #0
	str	r6, [r5, #80]
	ldr	r3, [r4]
	cmp	r3, r6
	bne	.L175
	ldr	r3, [r5, #8]
	ubfx	r3, r3, #15, #1
	str	r3, [r4, #256]
	b	.L133
.L172:
	sub	r0, fp, #260
	sub	r1, fp, #72
	bl	RBUF_Create
	ldr	r0, [fp, #-260]
	cmp	r0, #0
	beq	.L118
	str	r0, [r4, #136]
	sub	r1, fp, #204
	bl	RBUF_QueryInfo
	ldr	r3, [r5, #64]
	ldrh	r2, [fp, #-192]
	mov	r3, r3, lsr #16
	mov	r3, r3, asl #16
	orr	r3, r3, r2
	str	r3, [r5, #64]
	b	.L120
.L118:
	mov	r0, r4
	bl	AIPDestroyChn
	mov	r3, #0
	b	.L171
.L175:
	ldr	r3, [fp, #-140]
	sub	r0, fp, #268
	ldr	r2, [fp, #-144]
	ldr	r1, [fp, #-136]
	bl	FADE_Create
	ldr	r3, [fp, #-268]
	cmp	r3, r6
	beq	.L118
	ldr	r2, [r4]
	str	r3, [r4, #148]
	str	r6, [r4, #208]
	b	.L122
.L128:
	b	.L124
.L177:
	.align	2
.L176:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIPCreateChn, .-AIPCreateChn
	.align	2
	.global	AIPFlushChnCtx
	.type	AIPFlushChnCtx, %function
AIPFlushChnCtx:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r0, [r0, #144]
	cmp	r0, #0
	beq	.L179
	ldr	r3, [r4, #244]
	cmp	r3, #2
	beq	.L189
	bl	ResampleFlush
.L179:
	ldr	r0, [r4, #140]
	cmp	r0, #0
	beq	.L181
	bl	LSRC_Flush
.L181:
	ldr	r0, [r4, #148]
	mov	r3, #0
	str	r3, [r4, #216]
	cmp	r0, r3
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r2, #8
	mov	r1, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	FADE_Active
.L189:
	bl	iMedia_ASRC_Flush
	b	.L179
	UNWIND(.fnend)
	.size	AIPFlushChnCtx, .-AIPFlushChnCtx
	.align	2
	.type	AIPFlushChn, %function
AIPFlushChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	tst	r1, #1
	mov	r4, r1
	mov	r5, r0
	bne	.L209
.L191:
	tst	r4, #2
	beq	.L192
	ldr	r0, [r5, #132]
	cmp	r0, #0
	beq	.L192
	bl	RBUF_Flush
.L192:
	tst	r4, #4
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r5, #136]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	RBUF_Flush
.L209:
	bl	AIPFlushChnCtx
	b	.L191
	UNWIND(.fnend)
	.size	AIPFlushChn, .-AIPFlushChn
	.align	2
	.global	AIPFlushChnRufIn
	.type	AIPFlushChnRufIn, %function
AIPFlushChnRufIn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0, #132]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_Flush
	UNWIND(.fnend)
	.size	AIPFlushChnRufIn, .-AIPFlushChnRufIn
	.align	2
	.global	AIPFlushChnFifo
	.type	AIPFlushChnFifo, %function
AIPFlushChnFifo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0, #136]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_Flush
	UNWIND(.fnend)
	.size	AIPFlushChnFifo, .-AIPFlushChnFifo
	.align	2
	.global	AIPGetChnCmd
	.type	AIPGetChnCmd, %function
AIPGetChnCmd:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L224
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #8]
	tst	r2, #8
	movne	r0, #4
	beq	.L223
.L215:
	str	r0, [r1]
	ldmfd	sp, {fp, sp, pc}
.L223:
	ldr	r2, [r3, #8]
	and	r2, r2, #3
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L216
.L217:
	.word	.L222
	.word	.L218
	.word	.L219
	.word	.L220
.L222:
	mov	r0, #0
	b	.L215
.L220:
	mov	r0, #3
	b	.L215
.L219:
	mov	r0, #2
	b	.L215
.L218:
	mov	r0, #1
	b	.L215
.L216:
	ldr	r2, [r3, #8]
	mov	r0, #4
	bic	r2, r2, #240
	orr	r2, r2, #64
	str	r2, [r3, #8]
	ldr	r2, [r3, #8]
	orr	r2, r2, #8
	str	r2, [r3, #8]
	b	.L215
.L225:
	.align	2
.L224:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPGetChnCmd, .-AIPGetChnCmd
	.align	2
	.global	AIPAckChnCmd
	.type	AIPAckChnCmd, %function
AIPAckChnCmd:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L228
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #8]
	tst	r2, #8
	ldmnefd	sp, {fp, sp, pc}
	ldr	r2, [r3, #8]
	and	r1, r1, #15
	bic	r2, r2, #240
	orr	r1, r2, r1, asl #4
	str	r1, [r3, #8]
	ldr	r2, [r3, #8]
	orr	r2, r2, #8
	str	r2, [r3, #8]
	ldmfd	sp, {fp, sp, pc}
.L229:
	.align	2
.L228:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIPAckChnCmd, .-AIPAckChnCmd
	.align	2
	.global	AIP_Init
	.type	AIP_Init, %function
AIP_Init:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L233
	mov	r4, r0
	ldr	r8, .L233+4
	mov	r7, #0
	add	r6, r5, #32
.L231:
	str	r4, [r5, #4]!
	mov	r0, r4
	ldr	r3, [r8, #20]
	mov	r2, #96
	mov	r1, #0
	blx	r3
	ldr	r3, [r4, #8]
	cmp	r5, r6
	orr	r3, r3, #8
	str	r3, [r4, #8]
	ldr	r3, [r4, #8]
	bic	r3, r3, #32512
	orr	r3, r3, #30976
	str	r3, [r4, #8]
	ldr	r3, [r4]
	bic	r3, r3, #14336
	orr	r3, r3, #10240
	str	r3, [r4], #96
	str	r7, [r5, #32]
	bne	.L231
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L234:
	.align	2
.L233:
	.word	.LANCHOR0-4
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIP_Init, .-AIP_Init
	.align	2
	.global	AIP_DeInit
	.type	AIP_DeInit, %function
AIP_DeInit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L238
	mov	r6, #0
	add	r5, r4, #32
.L236:
	ldr	r0, [r4, #4]!
	bl	AIPDestroyChn
	cmp	r4, r5
	str	r6, [r4]
	bne	.L236
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L239:
	.align	2
.L238:
	.word	.LANCHOR0+28
	UNWIND(.fnend)
	.size	AIP_DeInit, .-AIP_DeInit
	.global	__aeabi_uidiv
	.align	2
	.global	AIP_Process
	.type	AIP_Process, %function
AIP_Process:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #108)
	sub	sp, sp, #108
	ldr	r3, .L409
	movw	r8, #19923
	mov	r4, #0
	add	r5, r3, #32
	movt	r8, 4194
	mov	r7, r3
.L312:
	sub	r1, fp, #80
	mov	r0, r4
	bl	AIPGetChnCmd
	cmp	r0, #4
	beq	.L384
	ldr	r3, [fp, #-80]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L384
.L245:
	.word	.L244
	.word	.L246
	.word	.L247
	.word	.L248
.L248:
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L265
	ldr	r9, [r6, #156]
	cmp	r9, #1
	beq	.L389
	cmp	r9, #2
	beq	.L390
.L259:
	mov	r3, #0
	str	r3, [r6, #324]
	mov	r3, #2
	str	r3, [r6, #20]
.L387:
	ldr	r3, [r7]
.L388:
	ldr	r2, [r3, #8]
	tst	r2, #8
	bne	.L384
	ldr	r2, [r3, #8]
	bic	r2, r2, #240
.L385:
	str	r2, [r3, #8]
	ldr	r2, [r3, #8]
	orr	r2, r2, #8
	str	r2, [r3, #8]
.L384:
	ldr	r6, [r5]
.L242:
	cmp	r6, #0
	beq	.L265
	ldr	r9, [r6, #156]
	cmp	r9, #1
	beq	.L391
.L265:
	add	r4, r4, #1
	add	r7, r7, #4
	cmp	r4, #8
	add	r5, r5, #4
	bne	.L312
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L247:
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L265
	ldr	r9, [r6, #156]
	cmp	r9, #1
	bne	.L259
	mov	r0, r6
	bl	AIPReclaimFifo
	mov	r1, r9
	mov	r0, r6
	bl	AIPFlushChn
	mov	r3, #2
	str	r3, [r6, #156]
	b	.L259
.L244:
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L383
	ldr	r3, [r6, #156]
	cmp	r3, #0
	beq	.L392
	cmp	r3, #2
	bne	.L387
	mov	r1, #1
	ldr	r0, [r6, #148]
	str	r1, [r6, #156]
	mov	r2, #8
	bl	FADE_Active
	ldr	r0, [r5]
	cmp	r0, #0
	bne	.L387
.L401:
	ldr	r3, [r7]
	ldr	r2, [r3, #8]
	tst	r2, #8
	bne	.L265
	ldr	r2, [r3, #8]
	bic	r2, r2, #240
	orr	r2, r2, #16
	b	.L385
.L246:
	ldr	r6, [r5]
	ldr	r9, [r7]
	cmp	r6, #0
	cmpne	r9, #0
	beq	.L242
	ldr	r3, [r6, #156]
	sub	r2, r3, #1
	cmp	r2, #1
	movhi	r3, r9
	bhi	.L388
	cmp	r3, #1
	beq	.L393
.L262:
	mov	r1, #3
	mov	r0, r6
	bl	AIPFlushChn
	mov	r3, #0
	mov	r2, #2
	str	r3, [r6, #156]
	str	r2, [r6, #20]
	str	r3, [r9, #80]
	str	r3, [r6, #324]
	ldr	r3, [r7]
	b	.L388
.L391:
	mov	r0, r4
	bl	AIPUpdateChnState
	ldr	r3, [r7]
	ldr	r10, [r5]
	cmp	r10, #0
	cmpne	r3, #0
	str	r3, [fp, #-120]
	beq	.L268
	ldr	r2, [r10, #20]
	cmp	r2, #1
	bls	.L268
	ldr	r0, [r10, #132]
	bl	RBUF_QueryBusy
	cmp	r0, #0
	beq	.L268
	ldr	r1, [r10, #32]
	ldr	ip, [r10, #68]
	ldr	r3, [fp, #-120]
	mul	ip, ip, r1
	ldr	r2, [r3, #84]
	ldr	lr, [r3, #84]
	ubfx	r2, r2, #0, #10
	ldr	r1, [r10, #20]
	ubfx	lr, lr, #10, #10
	mul	r2, r2, ip
	umull	r2, r3, r2, r8
	cmp	r0, r3, lsr #6
	movcc	r3, #1
	movcs	r3, #0
	cmp	r1, #2
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r3, #0
	bne	.L268
	mul	r2, ip, lr
	umull	r2, r3, r2, r8
	cmp	r0, r3, lsr #6
	movcc	r3, #1
	movcs	r3, #0
	cmp	r1, #3
	movne	r1, #0
	andeq	r1, r3, #1
	cmp	r1, #0
	bne	.L268
	str	r9, [r10, #20]
	mov	r1, r9
	ldr	r0, [r10, #148]
	mov	r2, #8
	bl	FADE_Active
.L268:
	ldr	r3, [r6, #36]
	cmp	r3, #0
	bne	.L265
	mov	r0, r4
	bl	AIPUpdateChnState
	ldr	r3, [r6, #20]
	cmp	r3, #1
	beq	.L394
.L271:
	ldr	r6, [r5]
	ldr	r9, [r7]
	ldr	r0, [r6, #136]
	bl	RBUF_QueryBusy
	ldr	r2, [r6, #88]
	ldr	r1, [r6, #232]
	bl	UTIL_LatencyMs
	ldr	r3, [r9, #4]
	mov	r1, r9
	bic	r3, r3, #16646144
	and	r2, r0, #127
	mov	r0, r6
	orr	r3, r3, r2, asl #17
	str	r3, [r9, #4]
	bl	AIPUpdateTrackLatency
	mov	r2, #6
	mov	r3, #0
	str	r2, [r6, #316]
	str	r3, [r6, #320]
	b	.L265
.L394:
	ldr	r3, [r6, #248]
	cmp	r3, #1
	beq	.L271
	ldr	r3, [r6, #252]
	cmp	r3, #0
	bne	.L273
	ldr	r2, [r6, #268]
	cmp	r2, #1
	streq	r3, [r6, #268]
.L283:
	ldr	r10, [r6, #216]
	ldr	r1, [r6, #232]
	ldr	r9, [r6, #228]
	mul	r3, r10, r1
	cmp	r3, r9
	bcs	.L395
	ldr	r3, [r6, #36]
	ldr	r2, [r6, #88]
	cmp	r3, #0
	ldr	r3, [r6, #84]
	movne	r10, r9
	str	r3, [fp, #-120]
	ldr	r3, [r6, #80]
	beq	.L396
.L286:
	ldr	r0, [r6, #132]
	bl	RBUF_QueryBusy
	cmp	r0, r10
	bcc	.L271
	cmp	r10, #0
	beq	.L271
	ldr	r0, [r6, #136]
	cmp	r0, #0
	beq	.L271
	mov	r1, r9
	bl	RBUF_CheckFree
	cmp	r0, #0
	beq	.L271
	cmp	r9, #0
	beq	.L271
	bl	AOE_GetWKBuf
	ldr	r1, [r6, #236]
	str	r10, [fp, #-104]
	mov	r9, r0
	mov	r0, r10
	str	r9, [fp, #-108]
	bl	__aeabi_uidiv
	ldr	ip, [r6, #24]
	mov	r1, r9
	ldr	r3, [r6, #28]
	mov	r2, r10
	ldr	lr, [r6, #32]
	str	ip, [fp, #-96]
	ldr	ip, [r6, #36]
	str	r3, [fp, #-92]
	mov	r3, #0
	str	lr, [fp, #-88]
	str	ip, [fp, #-84]
	str	r0, [fp, #-100]
	ldr	r0, [r6, #132]
	bl	RBUF_ReadDataDma
	ldr	r3, [r6, #36]
	cmp	r3, #0
	beq	.L397
.L292:
	ldr	r3, [r6, #188]
	cmp	r3, #1
	beq	.L398
.L307:
	ldr	r2, [r6, #232]
	ldr	r3, [r6, #216]
	ldr	r10, [r6, #228]
	mul	r2, r3, r2
	cmp	r2, #0
	bne	.L399
.L308:
	cmp	r10, #0
	ldr	r3, [fp, #-104]
	beq	.L310
	cmp	r10, r3
	movcs	r10, r3
	cmp	r10, #0
	beq	.L310
	mov	r2, r10
	ldr	r1, [fp, #-108]
	ldr	r0, [r6, #136]
	bl	RBUF_WriteData
	ldr	r3, [fp, #-104]
.L310:
	subs	r9, r3, r10
	beq	.L311
	ldr	r3, .L409+4
	mov	r2, r9
	ldr	r1, [fp, #-108]
	ldr	r0, [r6, #220]
	ldr	r3, [r3, #24]
	add	r1, r1, r10
	blx	r3
.L311:
	mov	r0, r9
	ldr	r1, [r6, #232]
	bl	__aeabi_uidiv
	ldr	r3, [r6, #324]
	add	r3, r3, #1
	str	r3, [r6, #324]
	str	r0, [r6, #216]
	b	.L271
.L392:
	mov	r0, r4
	bl	AIPIsChnAttrChange
	cmp	r0, #0
	bne	.L400
	mov	r3, #1
	str	r3, [r6, #156]
	ldr	r0, [r5]
.L250:
	cmp	r0, #0
	bne	.L387
	b	.L401
.L400:
	ldr	r0, [r5]
	bl	AIPDestroyChn
.L383:
	mov	r0, r4
	bl	AIPCreateChn
	str	r0, [r5]
	b	.L250
.L389:
	mov	r0, r6
	bl	AIPReclaimFifo
	mov	r0, r6
	mov	r1, #3
	bl	AIPFlushChn
	mov	r1, r9
	mov	r2, #8
	ldr	r0, [r6, #148]
	bl	FADE_Active
	b	.L259
.L390:
	mov	r1, #7
	mov	r0, r6
	bl	AIPFlushChn
	b	.L259
.L273:
	ldr	r3, [r6, #268]
	cmp	r3, #0
	beq	.L276
	ldr	r3, [r6, #272]
.L277:
	ldr	r9, [r6, #228]
	ldr	r0, [r6, #260]
	str	r3, [fp, #-112]
	mov	r1, r9
	bl	AOP_QueryRbfFree
	cmp	r0, #0
	beq	.L283
	ldr	r0, [r6, #132]
	sub	r1, fp, #112
	bl	RBUF_QueryBusy_ProvideRptr
	cmp	r9, r0
	bhi	.L283
	bl	AOE_GetWKBuf
	ldr	r1, [r6, #236]
	str	r9, [fp, #-104]
	mov	r10, r0
	mov	r0, r9
	str	r10, [fp, #-108]
	bl	__aeabi_uidiv
	ldr	lr, [r6, #28]
	mov	r1, r10
	ldr	ip, [r6, #32]
	sub	r3, fp, #112
	ldr	r10, [r6, #24]
	mov	r2, r9
	str	lr, [fp, #-92]
	sub	r9, fp, #108
	ldr	lr, [r6, #36]
	str	r10, [fp, #-96]
	str	ip, [fp, #-88]
	str	lr, [fp, #-84]
	str	r0, [fp, #-100]
	ldr	r0, [r6, #132]
	bl	RBUF_ReadDataDma
	ldr	r3, [r6, #196]
	cmp	r3, #1
	beq	.L402
.L280:
	mov	r1, r9
	mov	r0, r6
	bl	AIPGainPcmData
	ldr	r1, [r6, #192]
	ldr	r2, [r6, #80]
	sub	r3, r1, #1
	cmp	r3, #6
	bls	.L403
.L281:
	ldr	r3, [r6, #188]
	cmp	r3, #1
	beq	.L404
.L282:
	mov	r1, r9
	ldr	r0, [r6, #260]
	bl	AOP_WriteRbfData
	ldr	r3, [fp, #-112]
	str	r3, [r6, #272]
	b	.L283
.L395:
	ldr	r0, [r6, #136]
	cmp	r0, #0
	beq	.L271
	mov	r1, r9
	bl	RBUF_CheckFree
	cmp	r0, #0
	beq	.L271
	cmp	r9, #0
	beq	.L271
	ldr	r2, [r6, #228]
	ldr	r1, [r6, #220]
	ldr	r0, [r6, #136]
	bl	RBUF_WriteData
	ldr	r1, [r6, #232]
	ldr	r0, [r6, #228]
	bl	__aeabi_uidiv
	ldr	r3, [r6, #216]
	rsb	r0, r0, r3
	str	r0, [r6, #216]
	b	.L271
.L393:
	mov	r0, r6
	bl	AIPReclaimFifo
	b	.L262
.L276:
	ldr	r1, [r6, #80]
	ldr	r0, [r6, #84]
	bl	UTIL_CalcFrameSize
	ldr	r3, [r6, #264]
	ldr	r2, [r6, #32]
	sub	r1, fp, #80
	mul	r2, r3, r2
	mul	r2, r0, r2
	ldr	r0, [r6, #132]
	umull	r2, r3, r2, r8
	mov	r9, r3, lsr #6
	bl	RBUF_QueryInfo
	ldr	r1, [fp, #-52]
	ldr	r2, [fp, #-76]
	cmp	r9, r1
	ldr	r0, [fp, #-68]
	movcs	r9, r1
	add	r3, r9, r2
	cmp	r3, r0
	rsbcs	r3, r0, r2
	mov	r2, #1
	addcs	r3, r3, r9
	str	r2, [r6, #268]
	str	r3, [r6, #272]
	b	.L277
.L396:
	mov	r0, r9
	str	r3, [fp, #-128]
	str	r2, [fp, #-124]
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-120]
	ldr	ip, [r6, #140]
	ldr	r3, [fp, #-128]
	str	r2, [sp]
	ldr	r2, [fp, #-124]
	mov	r1, r2
	rsb	r10, r10, r0
	mov	r0, ip
	bl	LSRC_UpdateChange
	ldr	r1, [r6, #212]
	ldr	r0, [r6, #140]
	bl	LSRC_SetSpeedAdjust
	mov	r1, r10
	ldr	r0, [r6, #140]
	bl	LSRC_GetMinInputNum
	ldr	r3, [r6, #144]
	cmp	r3, #0
	beq	.L287
	ldr	r2, [r6, #244]
	cmp	r2, #2
	bne	.L288
	ldr	r3, [r6, #32]
	ldr	r1, [r6, #88]
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	cmp	r0, #0
	addne	r0, r0, #1
	beq	.L289
.L287:
	tst	r0, #3
	bicne	r0, r0, #3
	addne	r0, r0, #4
.L289:
	ldr	r10, [r6, #236]
	mul	r10, r10, r0
	b	.L286
.L288:
	mov	r1, r0
	mov	r0, r3
	bl	ResamplerGetMinInputNum
	b	.L287
.L397:
	ldr	r10, [r6, #84]
	ldr	r3, [fp, #-92]
	ldr	r2, [r6, #80]
	cmp	r10, r3
	subeq	r9, fp, #108
	str	r2, [fp, #-120]
	beq	.L293
	bls	.L294
	bl	AOE_GetWKBuf
	sub	r9, fp, #108
	mov	r2, r9
	mov	r1, r0
	mov	r0, r10
	bl	UTIL_UpmixPcmData
.L293:
	ldr	r3, [fp, #-96]
	ldr	r10, [fp, #-120]
	cmp	r10, r3
	beq	.L295
	bl	AOE_GetWKBuf
	mov	r2, r9
	mov	r1, r0
	mov	r0, r10
	bl	UTIL_UnifyBitDepthPcmData
.L295:
	ldr	r3, [r6, #144]
	ldr	r2, [r6, #88]
	cmp	r3, #0
	str	r2, [fp, #-120]
	beq	.L299
	bl	AOE_GetWKBuf
	ldr	r3, [r6, #244]
	cmp	r3, #2
	mov	r10, r0
	beq	.L405
	ldr	r2, [fp, #-88]
	mov	ip, #1
	ldr	lr, [fp, #-120]
	ldr	r0, [r6, #144]
	ldr	r3, [fp, #-100]
	str	r2, [sp]
	mov	r2, r10
	ldr	r1, [fp, #-108]
	str	lr, [sp, #4]
	str	ip, [sp, #8]
	bl	ResamplerProcessFrame
	ldr	r3, [fp, #-92]
	mov	r2, r0
.L298:
	mov	r0, r3
	ldr	r3, [fp, #-120]
	ldr	r1, [fp, #-96]
	str	r10, [fp, #-108]
	str	r3, [fp, #-88]
	str	r2, [fp, #-100]
	bl	UTIL_CalcFrameSize
	ldr	r3, [fp, #-100]
	mul	r0, r3, r0
	str	r0, [fp, #-104]
.L299:
	ldr	r3, [r6, #240]
	ldr	r2, .L409
	ldr	r0, [r6, #140]
	ldr	r3, [r2, r3, asl #2]
	cmp	r0, #0
	str	r3, [fp, #-120]
	beq	.L301
	bl	LSRC_CheckDoSRC
	cmp	r0, #0
	beq	.L301
	ldr	r3, [fp, #-100]
	str	r3, [fp, #-124]
	bl	AOE_GetWKBuf
	ldr	r3, [fp, #-124]
	ldr	r1, [fp, #-108]
	mov	r2, r0
	mov	r10, r0
	ldr	r0, [r6, #140]
	bl	LSRC_ProcessFrame
	ldr	r1, [fp, #-96]
	str	r10, [fp, #-108]
	str	r0, [fp, #-100]
	ldr	r0, [fp, #-92]
	bl	UTIL_CalcFrameSize
	ldr	r3, [fp, #-100]
	ldr	r1, [fp, #-120]
	ldr	r2, [r1, #80]
	add	r2, r2, #1
	str	r2, [r1, #80]
	mul	r0, r3, r0
	str	r0, [fp, #-104]
.L301:
	ldr	r3, [r6, #196]
	cmp	r3, #1
	beq	.L406
.L303:
	mov	r1, r9
	mov	r0, r6
	bl	AIPGainPcmData
	ldr	r1, [r6, #192]
	ldr	r2, [r6, #80]
	sub	r3, r1, #1
	cmp	r3, #6
	bls	.L407
.L304:
	ldr	r0, [r6, #148]
	cmp	r0, #0
	beq	.L292
	ldr	r1, [r6, #256]
	cmp	r1, #0
	bne	.L408
	mov	r2, #8
	bl	FADE_Active
	b	.L292
.L399:
	ldr	r1, [r6, #220]
	rsb	r10, r2, r10
	ldr	r0, [r6, #136]
	bl	RBUF_WriteData
	b	.L308
.L398:
	ldr	r3, .L409+4
	mov	r1, #0
	ldr	r2, [fp, #-104]
	ldr	r0, [fp, #-108]
	ldr	r3, [r3, #20]
	blx	r3
	b	.L307
.L408:
	ldr	r2, [fp, #-96]
	ldr	r1, [fp, #-88]
	ldr	r3, [fp, #-92]
	bl	FADE_Flush
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [r6, #148]
	bl	FADE_InProcess
	b	.L292
.L294:
	bl	AOE_GetWKBuf
	sub	r9, fp, #108
	mov	r2, r9
	mov	r1, r0
	mov	r0, r10
	bl	UTIL_DownmixPcmData
	b	.L293
.L405:
	ldr	r1, [fp, #-92]
	ldr	r3, [fp, #-100]
	ldr	r2, [fp, #-108]
	str	r0, [fp, #-76]
	mul	r3, r3, r1
	str	r2, [fp, #-80]
	ldr	r2, .L409+4
	ldr	r2, [r2, #32]
	str	r3, [fp, #-72]
	blx	r2
	sub	r1, fp, #80
	ldr	r0, [r6, #144]
	bl	iMedia_ASRC_Apply
	ldr	r3, .L409+4
	ldr	r3, [r3, #36]
	blx	r3
	ldr	r3, [fp, #-92]
	ldr	r0, [fp, #-68]
	mov	r1, r3
	str	r3, [fp, #-124]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-124]
	mov	r2, r0
	b	.L298
.L404:
	ldr	r3, .L409+4
	mov	r1, #0
	ldr	r2, [fp, #-104]
	ldr	r0, [fp, #-108]
	ldr	r3, [r3, #20]
	blx	r3
	b	.L282
.L407:
	mov	r0, r9
	bl	UTIL_ChannelModeProcess
	b	.L304
.L406:
	add	r1, r6, #276
	mov	r0, r9
	bl	UTIL_DRE_16BIT_Process
	b	.L303
.L403:
	mov	r0, r9
	bl	UTIL_ChannelModeProcess
	b	.L281
.L402:
	add	r1, r6, #276
	mov	r0, r9
	bl	UTIL_DRE_16BIT_Process
	b	.L280
.L410:
	.align	2
.L409:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIP_Process, .-AIP_Process
	.align	2
	.global	AIP_GetChnStatus
	.type	AIP_GetChnStatus, %function
AIP_GetChnStatus:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L414
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	streq	r3, [r1]
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r3, #156]
	str	r2, [r1]
	ldr	r2, [r3, #4]
	str	r2, [r1, #4]
	ldr	r2, [r3]
	str	r2, [r1, #8]
	ldr	r2, [r3, #328]
	str	r2, [r1, #12]
	ldr	r3, [r3, #248]
	str	r3, [r1, #16]
	ldmfd	sp, {fp, sp, pc}
.L415:
	.align	2
.L414:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_GetChnStatus, .-AIP_GetChnStatus
	.align	2
	.global	AIP_CheckDataStatusStop
	.type	AIP_CheckDataStatusStop, %function
AIP_CheckDataStatusStop:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L419
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r0, [r3, #20]
	subne	r0, r0, #2
	clzne	r0, r0
	movne	r0, r0, lsr #5
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L420:
	.align	2
.L419:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_CheckDataStatusStop, .-AIP_CheckDataStatusStop
	.align	2
	.global	AIP_QueryFiFoInfo
	.type	AIP_QueryFiFoInfo, %function
AIP_QueryFiFoInfo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L428
	add	r2, r0, #8
	mov	r0, r1
	ldr	r3, [r3, r2, asl #2]
	cmp	r3, #0
	beq	.L425
	ldr	r2, [r3, #248]
	cmp	r2, #0
	beq	.L426
	ldr	r2, [r3, #156]
	cmp	r2, #1
	beq	.L427
	ldr	r3, .L428+4
	mov	r2, #36
	mov	r1, #0
	ldr	r3, [r3, #20]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L426:
	ldr	r0, [r3, #136]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryInfo
.L427:
	ldr	r0, [r3, #132]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryInfo
.L425:
	ldr	ip, .L428+4
	mov	r1, r3
	mov	r2, #36
	ldr	r3, [ip, #20]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L429:
	.align	2
.L428:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AIP_QueryFiFoInfo, .-AIP_QueryFiFoInfo
	.align	2
	.global	AIP_QueryFiFoBusy
	.type	AIP_QueryFiFoBusy, %function
AIP_QueryFiFoBusy:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L434
	add	r0, r0, #8
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r0, #248]
	cmp	r3, #0
	beq	.L433
	ldr	r0, [r0, #132]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryBusy
.L433:
	ldr	r0, [r0, #136]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryBusy
.L435:
	.align	2
.L434:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_QueryFiFoBusy, .-AIP_QueryFiFoBusy
	.align	2
	.global	AIP_QueryBusy
	.type	AIP_QueryBusy, %function
AIP_QueryBusy:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L444
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L437
	ldr	r0, [r3, #132]
	cmp	r0, #0
	beq	.L437
	ldr	r3, [r3, #20]
	cmp	r3, #1
	beq	.L443
.L437:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L443:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_QueryBusy
.L445:
	.align	2
.L444:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_QueryBusy, .-AIP_QueryBusy
	.align	2
	.global	AIP_ReadDataComplete
	.type	AIP_ReadDataComplete, %function
AIP_ReadDataComplete:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L450
	add	r2, r0, #8
	ldr	r4, [r3, r2, asl #2]
	ldr	r5, [r3, r0, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #248]
	cmp	r3, #0
	beq	.L449
	ldr	r0, [r4, #132]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	RBUF_ReadDataComplete
.L449:
	ldr	r0, [r4, #136]
	bl	RBUF_ReadDataComplete
	ldr	r0, [r4, #136]
	bl	RBUF_QueryBusy
	ldr	r2, [r4, #88]
	ldr	r1, [r4, #232]
	bl	UTIL_LatencyMs
	ldr	r3, [r5, #4]
	mov	r1, r5
	bic	r3, r3, #16646144
	and	r2, r0, #127
	mov	r0, r4
	orr	r3, r3, r2, asl #17
	str	r3, [r5, #4]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AIPUpdateTrackLatency
.L451:
	.align	2
.L450:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_ReadDataComplete, .-AIP_ReadDataComplete
	.align	2
	.global	AIP_UnderFlowCalc
	.type	AIP_UnderFlowCalc, %function
AIP_UnderFlowCalc:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L457
	ldr	r2, [r3, r0, asl #2]
	cmp	r2, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r2, #64]
	ldr	r1, [r2, #64]
	mov	r3, r3, lsr #16
	uxth	r1, r1
	mov	r3, r3, asl #16
	add	r3, r3, #65536
	orr	r3, r1, r3
	str	r3, [r2, #64]
	ldmfd	sp, {fp, sp, pc}
.L458:
	.align	2
.L457:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_UnderFlowCalc, .-AIP_UnderFlowCalc
	.align	2
	.global	AIP_GetRingIn
	.type	AIP_GetRingIn, %function
AIP_GetRingIn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L462
	add	r0, r0, #8
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #132]
	ldmfd	sp, {fp, sp, pc}
.L463:
	.align	2
.L462:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_GetRingIn, .-AIP_GetRingIn
	.align	2
	.global	AIP_MuteRawData
	.type	AIP_MuteRawData, %function
AIP_MuteRawData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L472
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r0, [r3, #132]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_MuteRawData
.L473:
	.align	2
.L472:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_MuteRawData, .-AIP_MuteRawData
	.align	2
	.global	AIP_GetMuteStatus
	.type	AIP_GetMuteStatus, %function
AIP_GetMuteStatus:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L477
	add	r0, r0, #8
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #188]
	ldmfd	sp, {fp, sp, pc}
.L478:
	.align	2
.L477:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_GetMuteStatus, .-AIP_GetMuteStatus
	.align	2
	.global	AIP_ContinueOutputCnt
	.type	AIP_ContinueOutputCnt, %function
AIP_ContinueOutputCnt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L484
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r2, [r3, #88]
	addne	r2, r2, #1
	strne	r2, [r3, #88]
	ldmfd	sp, {fp, sp, pc}
.L485:
	.align	2
.L484:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_ContinueOutputCnt, .-AIP_ContinueOutputCnt
	.align	2
	.global	AIP_ContinueOutput
	.type	AIP_ContinueOutput, %function
AIP_ContinueOutput:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r5, .L510
	add	r3, r0, #8
	mov	r6, r0
	ldr	r4, [r5, r3, asl #2]
	cmp	r4, #0
	beq	.L486
	ldr	r3, [r4, #36]
	cmp	r3, #0
	beq	.L489
	cmp	r1, #1
	beq	.L507
	ldr	r3, [r4, #20]
	cmp	r3, #1
	beq	.L508
.L486:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L489:
	ldr	r3, [r4, #324]
	cmp	r3, #4
	bhi	.L494
	ldr	r3, [r4, #156]
	cmp	r3, #1
	beq	.L486
.L494:
	ldr	r3, [r4, #20]
	bic	r2, r3, #2
	cmp	r2, #1
	bne	.L486
	cmp	r3, #1
	beq	.L509
.L495:
	cmp	r1, #1
	bne	.L486
	ldr	r2, [r4, #328]
	mov	r1, #0
	ldr	r0, [r4, #136]
	bl	RBUF_WriteData
	ldr	r3, [r5, r6, asl #2]
	cmp	r3, #0
	ldrne	r2, [r3, #88]
	addne	r2, r2, #1
	strne	r2, [r3, #88]
	b	.L486
.L508:
	cmp	r1, #0
	moveq	r3, #2
	movne	r3, #3
.L493:
	str	r3, [r4, #20]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L507:
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	ldrne	r2, [r3, #88]
	addne	r2, r2, #1
	strne	r2, [r3, #88]
.L491:
	ldr	r3, [r4, #20]
	cmp	r3, #1
	bne	.L486
	mov	r3, #3
	b	.L493
.L509:
	mov	r3, #3
	mov	r0, r4
	str	r3, [r4, #20]
	str	r1, [fp, #-32]
	bl	AIPReclaimFifo
	mov	r0, r4
	bl	AIPFlushChnCtx
	ldr	r1, [fp, #-32]
	cmp	r1, #0
	streq	r1, [r4, #324]
	bne	.L495
	b	.L486
.L511:
	.align	2
.L510:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_ContinueOutput, .-AIP_ContinueOutput
	.align	2
	.global	AIP_RegReclaimFun
	.type	AIP_RegReclaimFun, %function
AIP_RegReclaimFun:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #7
	bhi	.L515
	ldr	r3, .L516
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L515
	str	r1, [r3, #316]
	mov	r0, #0
	str	r2, [r3, #320]
	ldmfd	sp, {fp, sp, pc}
.L515:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L517:
	.align	2
.L516:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AIP_RegReclaimFun, .-AIP_RegReclaimFun
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stAipRm, %object
	.size	g_stAipRm, 64
g_stAipRm:
	.space	64
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
