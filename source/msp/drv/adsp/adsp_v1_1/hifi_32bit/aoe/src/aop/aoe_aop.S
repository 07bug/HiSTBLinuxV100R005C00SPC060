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
	.file	"aoe_aop.c"
	.text
	.align	2
	.type	AOPCalcSize, %function
AOPCalcSize:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r1
	mov	r5, r0
	ldr	r1, [r1]
	ldr	r0, [r4, #4]
	bl	UTIL_CalcFrameSize
	ldr	r3, [r4, #8]
	movw	r1, #19923
	movt	r1, 4194
	mul	r3, r3, r5
	umull	r2, r3, r3, r1
	mov	r3, r3, lsr #6
	tst	r3, #3
	bicne	r3, r3, #3
	addne	r3, r3, #4
	mul	r0, r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AOPCalcSize, .-AOPCalcSize
	.align	2
	.global	AOPFlushChnBuf
	.type	AOPFlushChnBuf, %function
AOPFlushChnBuf:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r0, [r0, #112]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_Flush
	UNWIND(.fnend)
	.size	AOPFlushChnBuf, .-AOPFlushChnBuf
	.align	2
	.global	AOP_ProcDelayCompensation
	.type	AOP_ProcDelayCompensation, %function
AOP_ProcDelayCompensation:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	ldr	r3, .L30
	add	r2, r0, #8
	ldr	r4, [r3, r2, asl #2]
	cmp	r4, #0
	beq	.L9
	ldr	r2, [r4, #116]
	cmp	r2, #0
	beq	.L9
	ldr	r2, [r4, #128]
	cmp	r2, #1
	beq	.L28
	ldr	r5, [r4, #120]
	ldr	r7, [r3, r0, asl #2]
	cmp	r5, #9
	bhi	.L29
.L9:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L29:
	add	r6, r4, #48
	sub	r1, fp, #64
	ldr	r0, [r4, #112]
	bl	RBUF_QueryInfo
	mov	r1, r6
	mov	r0, r5
	mov	r5, r6
	bl	AOPCalcSize
	mov	r1, r5
	mov	r6, r0
	mov	r0, #10
	bl	AOPCalcSize
	ldr	r2, [fp, #-44]
	cmp	r6, r2
	bcc	.L9
	add	r6, r6, r0
	subs	r2, r6, r2
	beq	.L9
	ldr	r3, [fp, #-36]
	mov	r1, #0
	ldr	r0, [r4, #112]
	cmp	r2, r3
	movcs	r2, r3
	bl	RBUF_WriteData
	ldr	r3, [r7, #100]
	add	r3, r3, #1
	str	r3, [r7, #100]
	b	.L9
.L28:
	ldr	r5, [r3, r0, asl #2]
	mov	r3, #0
	str	r3, [fp, #-64]
	sub	r1, fp, #64
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	str	r3, [fp, #-36]
	str	r3, [fp, #-32]
	ldr	r3, [r5, #4]
	orr	r3, r3, #1048576
	str	r3, [r5, #4]
	ldr	r0, [r4, #112]
	bl	RBUF_QueryInfo
	ldr	r0, [r4, #112]
	cmp	r0, #0
	beq	.L12
	bl	RBUF_Flush
.L12:
	add	r6, r4, #48
	ldr	r0, [r4, #124]
	mov	r1, r6
	bl	AOPCalcSize
	mov	r1, r6
	mov	r7, r0
	ldr	r0, [r4, #120]
	bl	AOPCalcSize
	ldr	r3, [fp, #-44]
	mov	r1, #0
	cmp	r7, r3
	mov	r2, r0
	addls	r2, r0, r3
	ldr	r3, [fp, #-36]
	rsbls	r2, r7, r2
	ldr	r0, [r4, #112]
	cmp	r2, r3
	movcs	r2, r3
	bl	RBUF_WriteData
	ldr	r3, [r5, #100]
	mov	r2, #0
	add	r3, r3, #1
	str	r3, [r5, #100]
	ldr	r3, [r4, #120]
	str	r2, [r4, #128]
	str	r3, [r4, #124]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L31:
	.align	2
.L30:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_ProcDelayCompensation, .-AOP_ProcDelayCompensation
	.align	2
	.global	AOP_DestroyChn
	.type	AOP_DestroyChn, %function
AOP_DestroyChn:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L36
	add	r2, r0, #8
	ldr	r4, [r3, r2, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #108]
	cmp	r3, #1
	beq	.L35
.L34:
	ldr	r0, [r4, #112]
	bl	RBUF_Destroy
	mov	r1, r4
	mov	r0, #26
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HI_ADSP_FREE
.L35:
	bl	CAST_Destroy
	b	.L34
.L37:
	.align	2
.L36:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_DestroyChn, .-AOP_DestroyChn
	.align	2
	.global	AOP_Init
	.type	AOP_Init, %function
AOP_Init:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L41
	mov	r8, r0
	ldr	r9, .L41+4
	mov	r4, r0
	add	r7, r5, #32
	mov	r6, #0
.L39:
	str	r4, [r5, #4]!
	mov	r0, r4
	ldr	r3, [r9, #20]
	mov	r2, #128
	mov	r1, #0
	add	r4, r4, #128
	blx	r3
	ldr	r3, [r4, #-124]
	cmp	r5, r7
	orr	r3, r3, #4
	str	r3, [r4, #-124]
	str	r6, [r5, #32]
	bne	.L39
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	CAST_Init
.L42:
	.align	2
.L41:
	.word	.LANCHOR0-4
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AOP_Init, .-AOP_Init
	.align	2
	.global	AOP_DeInit
	.type	AOP_DeInit, %function
AOP_DeInit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L46
	mov	r4, #0
	mov	r6, r4
.L44:
	mov	r0, r4
	add	r4, r4, #1
	bl	AOP_DestroyChn
	cmp	r4, #8
	str	r6, [r5, #4]!
	bne	.L44
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	CAST_DeInit
.L47:
	.align	2
.L46:
	.word	.LANCHOR0+28
	UNWIND(.fnend)
	.size	AOP_DeInit, .-AOP_DeInit
	.align	2
	.global	AOP_Process
	.type	AOP_Process, %function
AOP_Process:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	ldr	r7, .L97
	mov	r6, #0
	ldr	r9, .L97+4
	mov	r8, r6
	add	r5, r7, #36
	b	.L74
.L67:
	add	r6, r6, #1
	add	r5, r5, #4
	cmp	r6, #8
	beq	.L94
.L74:
	ldr	r4, [r7, #4]!
	ldr	r10, [r4, #4]
	ubfx	r10, r10, #2, #1
	cmp	r10, #0
	bne	.L65
	ldr	r3, [r4, #4]
	ands	r3, r3, #3
	beq	.L51
	cmp	r3, #1
	beq	.L52
	ldr	r3, [r4, #4]
	bic	r3, r3, #120
	orr	r3, r3, #32
	str	r3, [r4, #4]
	ldr	r3, [r4, #4]
	orr	r3, r3, #4
	str	r3, [r4, #4]
.L65:
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L67
.L66:
	ldr	r3, [r4, #116]
	str	r8, [r4, #132]
	cmp	r3, #1
	bne	.L67
	ldr	r10, [r7]
	add	r6, r6, #1
	str	r8, [r4, #20]
	add	r5, r5, #4
	ldr	r1, [r4, #48]
	ldr	r3, [r10, #12]
	ldr	r0, [r4, #52]
	uxtb	r3, r3
	str	r3, [r4, #24]
	ldr	r3, [r10, #12]
	ubfx	r3, r3, #8, #8
	str	r3, [r4, #28]
	ldr	r3, [r10, #12]
	tst	r3, #524288
	ldr	r3, [r10, #12]
	ubfx	r3, r3, #16, #3
	rsbne	r3, r3, #0
	str	r3, [r4, #32]
	str	r3, [r4, #36]
	ldr	r3, [r10, #12]
	tst	r3, #1073741824
	ldr	r3, [r10, #12]
	ubfx	r3, r3, #24, #6
	rsbne	r3, r3, #0
	str	r3, [r4, #40]
	ldr	r3, [r10, #12]
	mov	r3, r3, lsr #31
	str	r3, [r4, #44]
	ldr	r3, [r10, #4]
	ubfx	r3, r3, #8, #1
	str	r3, [r4, #104]
	ldr	r3, [r10]
	mov	r3, r3, lsr #20
	str	r3, [r4, #100]
	str	r3, [fp, #-120]
	bl	UTIL_CalcFrameSize
	ldr	r3, [fp, #-120]
	ldr	r2, [r4, #56]
	mov	r1, r0
	mov	r0, r3
	bl	UTIL_LatencyMs2ByteSize
	add	r1, r4, #68
	str	r0, [r4, #96]
	ldr	r0, [r4, #112]
	bl	RBUF_UpdateAttr
	ldr	r3, [r10, #4]
	ldr	r2, [r4, #124]
	ubfx	r3, r3, #21, #9
	ldr	r0, [r4, #112]
	cmp	r3, r2
	str	r3, [r4, #120]
	movne	r3, #1
	strne	r3, [r4, #128]
	bl	RBUF_QueryBusy
	ldr	r1, [r4, #48]
	mov	r10, r0
	ldr	r0, [r4, #52]
	bl	UTIL_CalcFrameSize
	ldr	r2, [r4, #56]
	mov	r1, r0
	mov	r0, r10
	bl	UTIL_LatencyMs
	cmp	r6, #8
	str	r0, [r4, #132]
	bne	.L74
.L94:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L52:
	mov	r0, r6
	bl	AOP_DestroyChn
	str	r10, [r5]
	ldr	r3, [r7]
.L64:
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L67
.L61:
	ldr	r2, [r3, #4]
	bic	r2, r2, #120
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
	b	.L65
.L51:
	str	r3, [fp, #-116]
	sub	r0, fp, #100
	ldr	r1, [r4]
	and	r1, r1, #3
	bl	AOE_REG_ReadBitDepth
	cmp	r0, #0
	bne	.L56
	ldr	r1, [r4]
	sub	r0, fp, #96
	ubfx	r1, r1, #2, #2
	bl	AOE_REG_ReadChannel
	cmp	r0, #0
	bne	.L56
	ldr	r1, [r4]
	sub	r0, fp, #92
	ubfx	r1, r1, #4, #4
	bl	AOE_REG_ReadSampelRate
	cmp	r0, #0
	bne	.L56
	ldr	r1, [r4]
	sub	r0, fp, #88
	ubfx	r1, r1, #8, #2
	bl	AOE_REG_ReadDataFormat
	cmp	r0, #0
	bne	.L56
	ldr	r1, [r4]
	sub	r0, fp, #112
	mov	r1, r1, lsr #20
	bl	AOE_REG_ReadBufLatencyMs
	subs	r10, r0, #0
	bne	.L56
	ldr	r3, [r4]
	ldr	r1, [fp, #-100]
	ldr	r0, [fp, #-96]
	ubfx	r3, r3, #10, #1
	str	r3, [fp, #-84]
	bl	UTIL_CalcFrameSize
	mov	r3, #1
	str	r3, [fp, #-80]
	ldr	r3, [r4, #24]
	str	r10, [fp, #-108]
	ubfx	r3, r3, #24, #1
	str	r10, [fp, #-104]
	str	r3, [fp, #-60]
	cmp	r3, #0
	ldr	r3, [r4, #16]
	str	r3, [fp, #-108]
	ldr	r3, [fp, #-108]
	ldr	r2, [r4, #20]
	str	r3, [fp, #-76]
	str	r2, [fp, #-104]
	ldr	r3, [r4, #24]
	bic	r3, r3, #-16777216
	str	r3, [fp, #-72]
	beq	.L54
	str	r10, [fp, #-108]
	str	r10, [fp, #-104]
	ldr	r3, [r4, #28]
	str	r3, [fp, #-108]
	ldr	r3, [r4, #32]
	ldr	r2, [fp, #-108]
	str	r3, [fp, #-104]
	str	r10, [fp, #-108]
	str	r10, [fp, #-104]
	ldr	r3, [r4, #36]
	str	r2, [fp, #-68]
	str	r3, [fp, #-108]
	ldr	r2, [fp, #-108]
	ldr	r3, [r4, #40]
	str	r2, [fp, #-64]
	str	r3, [fp, #-104]
.L55:
	ldr	r3, [fp, #-112]
	mov	r1, r0
	ldr	r2, [fp, #-92]
	str	r0, [fp, #-56]
	mov	r0, r3
	str	r3, [fp, #-48]
	bl	UTIL_LatencyMs2ByteSize
	sub	r1, fp, #80
	str	r0, [fp, #-52]
	sub	r0, fp, #116
	bl	RBUF_Create
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	beq	.L56
	mov	r1, #136
	mov	r0, #26
	bl	HI_ADSP_MALLOC
	subs	r4, r0, #0
	beq	.L57
	ldr	r3, [r9, #20]
	mov	r2, #136
	mov	r1, #0
	blx	r3
	ldr	r3, [r9, #24]
	mov	r2, #56
	sub	r1, fp, #100
	add	r0, r4, #48
	blx	r3
	ldr	r3, [fp, #-116]
	str	r3, [r4, #112]
	ldr	r3, [r7]
	ldr	r2, [r3, #4]
	tst	r2, #524288
	bne	.L95
.L58:
	str	r8, [r4, #108]
.L76:
	mov	r3, #121
	str	r8, [r4, #20]
	str	r8, [r4, #32]
	mov	r2, #1
	str	r8, [r4, #36]
	str	r8, [r4]
	str	r8, [r4, #12]
	str	r8, [r4, #16]
	str	r8, [r4, #124]
	str	r8, [r4, #120]
	str	r3, [r4, #24]
	str	r3, [r4, #28]
	str	r3, [r4, #4]
	str	r3, [r4, #8]
	str	r2, [r4, #116]
	str	r4, [r5]
	ldr	r3, [r7]
	ldr	r2, [r3, #4]
	tst	r2, #4
	beq	.L61
	b	.L66
.L96:
.L62:
.L63:
	mov	r1, r4
	mov	r0, #26
	bl	HI_ADSP_FREE
.L57:
	ldr	r0, [fp, #-116]
	bl	RBUF_Destroy
.L56:
	str	r8, [r5]
	ldr	r3, [r7]
	ldr	r2, [r3, #4]
	tst	r2, #4
	bne	.L64
	ldr	r2, [r3, #4]
	bic	r2, r2, #120
	orr	r2, r2, #8
	str	r2, [r3, #4]
	ldr	r2, [r3, #4]
	orr	r2, r2, #4
	str	r2, [r3, #4]
	ldr	r3, [r7]
	ldr	r2, [r3, #4]
	tst	r2, #4
	beq	.L61
	b	.L65
.L54:
	add	r3, r4, #28
	add	r4, r4, #36
	str	r3, [fp, #-68]
	str	r4, [fp, #-64]
	b	.L55
.L95:
	ldr	ip, [r3, #4]
	ubfx	ip, ip, #18, #1
	cmp	ip, #1
	bne	.L58
	ldr	lr, [r4, #56]
	add	r1, r4, #68
	ldr	r3, [r4, #52]
	mov	r0, r6
	ldr	r2, [r4, #48]
	str	ip, [r4, #108]
	str	lr, [sp]
	bl	CAST_Create
	subs	r10, r0, #0
	beq	.L96
	ldr	r1, [r4, #112]
	mov	r0, r6
	bl	CAST_SetAopBuf
	str	r10, [r4, #112]
	b	.L76
.L98:
	.align	2
.L97:
	.word	.LANCHOR0-4
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AOP_Process, .-AOP_Process
	.align	2
	.global	AOP_GetChnStatus
	.type	AOP_GetChnStatus, %function
AOP_GetChnStatus:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L102
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	streq	r3, [r1]
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r2, [r3, #116]
	str	r2, [r1]
	ldr	r2, [r3, #64]
	str	r2, [r1, #4]
	ldr	r2, [r3, #92]
	str	r2, [r1, #16]
	ldr	r2, [r3, #48]
	str	r2, [r1, #8]
	ldr	r2, [r3, #52]
	str	r2, [r1, #12]
	ldr	r2, [r3, #104]
	str	r2, [r1, #20]
	ldr	r2, [r3, #108]
	str	r2, [r1, #24]
	ldr	r2, [r3, #120]
	str	r2, [r1, #28]
	ldr	r3, [r3, #132]
	str	r3, [r1, #32]
	ldmfd	sp, {fp, sp, pc}
.L103:
	.align	2
.L102:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_GetChnStatus, .-AOP_GetChnStatus
	.align	2
	.global	AOP_QueryRbfFree
	.type	AOP_QueryRbfFree, %function
AOP_QueryRbfFree:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L112
	add	r0, r0, #8
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L105
	ldr	r2, [r3, #116]
	cmp	r2, #0
	beq	.L105
	ldr	r0, [r3, #112]
	cmp	r0, #0
	beq	.L105
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	RBUF_CheckFree
.L105:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L113:
	.align	2
.L112:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_QueryRbfFree, .-AOP_QueryRbfFree
	.align	2
	.global	AOP_WriteBuffProcTryCnt
	.type	AOP_WriteBuffProcTryCnt, %function
AOP_WriteBuffProcTryCnt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L119
	add	r2, r0, #8
	ldr	r3, [r3, r2, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r3, #108]
	cmp	r3, #1
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CAST_FiFoTryCnt
.L120:
	.align	2
.L119:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_WriteBuffProcTryCnt, .-AOP_WriteBuffProcTryCnt
	.align	2
	.global	AOP_WriteBuffProcOKCnt
	.type	AOP_WriteBuffProcOKCnt, %function
AOP_WriteBuffProcOKCnt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L126
	add	r2, r0, #8
	ldr	r3, [r3, r2, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, [r3, #108]
	cmp	r3, #1
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CAST_FiFoFreeCnt
.L127:
	.align	2
.L126:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_WriteBuffProcOKCnt, .-AOP_WriteBuffProcOKCnt
	.align	2
	.global	AOP_WriteRbfData
	.type	AOP_WriteRbfData, %function
AOP_WriteRbfData:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L158
	add	r0, r0, #8
	mov	r5, r1
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L129
	ldr	r3, [r4, #116]
	cmp	r3, #0
	beq	.L129
	ldr	r3, [r1, #24]
	cmp	r3, #0
	beq	.L154
.L131:
	ldr	r3, [r4, #108]
	ldr	r0, [r4, #112]
	cmp	r3, #1
	ldmia	r5, {r1, r2}
	beq	.L155
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	RBUF_WriteDataDma
.L129:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L154:
	ldr	r2, [r1, #12]
	ldr	r3, [r4, #48]
	cmp	r2, r3
	beq	.L153
	bl	AOE_GetWKBuf
	mov	r2, r5
	mov	r1, r0
	ldr	r0, [r4, #48]
	bl	UTIL_UnifyBitDepthPcmData
.L153:
	ldr	r2, [r5, #16]
	ldr	r3, [r4, #52]
	cmp	r2, r3
	beq	.L134
	bl	AOE_GetWKBuf
	mov	r2, r5
	mov	r1, r0
	ldr	r0, [r4, #52]
	bl	UTIL_UpmixPcmData
.L134:
	ldr	r3, [r4, #44]
	cmp	r3, #0
	beq	.L136
	bl	AOE_GetWKBuf
	ldr	r3, .L158+4
	mov	r1, #0
	ldr	r2, [r5, #4]
	ldr	r3, [r3, #20]
	mov	r6, r0
	blx	r3
	str	r6, [r5]
.L136:
	ldr	r3, [r4, #24]
	ldr	r2, [r4, #4]
	cmp	r3, r2
	beq	.L156
.L137:
	ldr	r2, [r4, #108]
	cmp	r2, #1
	beq	.L138
	bl	AOE_GetWKBuf
	ldr	r7, .L158+4
	add	r6, r4, #20
	ldr	r2, [r5, #4]
	ldr	r1, [r5]
	ldr	r3, [r7, #24]
	mov	r8, r0
	blx	r3
	str	r8, [r5]
	mov	r3, r6
	ldr	r1, [r4, #40]
	mov	r2, r4
	mov	r0, r5
	bl	UTIL_LRFadeGainProcess
	ldr	r3, [r7, #24]
	mov	r1, r6
	mov	r2, #20
	mov	r0, r4
	blx	r3
	b	.L131
.L155:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	RBUF_WriteData
.L156:
	ldr	r1, [r4, #32]
	ldr	r2, [r4, #12]
	cmp	r1, r2
	bne	.L137
.L138:
	cmp	r3, #121
	bne	.L140
	ldr	r3, [r4, #28]
	cmp	r3, #121
	beq	.L157
.L140:
	bl	AOE_GetWKBuf
	ldr	r3, .L158+4
	ldmia	r5, {r1, r2}
	ldr	r3, [r3, #24]
	mov	r6, r0
	blx	r3
	str	r6, [r5]
	add	r2, r4, #20
	ldr	r1, [r4, #40]
	mov	r0, r5
	bl	UTIL_LRGainProcess
	b	.L131
.L157:
	ldr	r3, [r4, #32]
	cmp	r3, #0
	bne	.L140
	ldr	r3, [r4, #36]
	cmp	r3, #0
	bne	.L140
	ldr	r3, [r4, #40]
	cmp	r3, #0
	beq	.L131
	b	.L140
.L159:
	.align	2
.L158:
	.word	.LANCHOR0
	.word	g_AdspOsalFunc
	UNWIND(.fnend)
	.size	AOP_WriteRbfData, .-AOP_WriteRbfData
	.align	2
	.global	AOP_GetRingOut
	.type	AOP_GetRingOut, %function
AOP_GetRingOut:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L163
	add	r0, r0, #8
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #112]
	ldmfd	sp, {fp, sp, pc}
.L164:
	.align	2
.L163:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	AOP_GetRingOut, .-AOP_GetRingOut
	.align	2
	.global	AOP_ContinueOutput
	.type	AOP_ContinueOutput, %function
AOP_ContinueOutput:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L175
	add	r0, r0, #8
	mov	r5, r2
	ldr	r4, [ip, r0, asl #2]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	cmp	r1, #4
	beq	.L174
	cmp	r1, #3
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	movw	r2, #2568
	ldr	r1, .L175+4
	ldr	r0, [r4, #112]
	bl	RBUF_WriteDataDma
	sub	r2, r5, #2560
	sub	r2, r2, #8
	b	.L173
.L174:
	cmp	r3, #1
	ldr	r3, .L175+8
	movw	r2, #1544
	movw	r6, #3260
	movne	r6, r2
	ldr	r1, .L175+12
	mov	r2, r6
	ldr	r0, [r4, #112]
	movne	r1, r3
	bl	RBUF_WriteDataDma
	rsb	r2, r6, r5
.L173:
	ldr	r0, [r4, #112]
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RBUF_WriteDataDma
.L176:
	.align	2
.L175:
	.word	.LANCHOR0
	.word	.LANCHOR2-3380
	.word	.LANCHOR1
	.word	.LANCHOR1+1544
	UNWIND(.fnend)
	.size	AOP_ContinueOutput, .-AOP_ContinueOutput
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
.LANCHOR2 = . + 8184
	.type	ddp_heard, %object
	.size	ddp_heard, 1544
ddp_heard:
	.short	-1934
	.short	19999
	.short	21
	.short	1536
	.short	2935
	.short	767
	.short	16263
	.short	-8159
	.short	1568
	.short	0
	.short	2
	.short	0
	.short	7
	.short	-1727
	.short	318
	.short	-11256
	.short	2056
	.short	2050
	.short	514
	.short	512
	.short	-32640
	.short	-32640
	.short	8224
	.short	8224
	.short	2056
	.short	2056
	.short	12787
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12353
	.short	-6313
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12353
	.short	-1579
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3089
	.short	-395
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31995
	.short	-99
	.short	24382
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	-25
	.short	22479
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-16391
	.short	-10455
	.short	-5998
	.short	18887
	.short	95
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-16
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	9
	.short	5258
	.short	17698
	.short	-28344
	.short	-23470
	.short	10516
	.short	-30139
	.short	8895
	.short	-1
	.short	-1
	.short	-64
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	51
	.short	13107
	.short	13107
	.short	13107
	.short	13107
	.short	13107
	.short	13103
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-8
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	4
	.short	-30139
	.short	8849
	.short	18596
	.short	21033
	.short	5258
	.short	17698
	.short	-28321
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-16
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	9
	.short	5258
	.short	17698
	.short	-28344
	.short	-23470
	.short	10516
	.short	-30139
	.short	8895
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-32
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	18
	.short	10516
	.short	-30139
	.short	8849
	.short	18596
	.short	21033
	.short	5258
	.short	17791
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-1
	.short	-64
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	36
	.short	21033
	.short	5258
	.short	17698
	.short	-28344
	.short	-23470
	.short	10516
	.short	-29954
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	16448
	.short	20772
	.short	-28096
	.short	16465
	.short	9362
	.short	16448
	.short	20772
	.short	-28096
	.short	16465
	.short	9362
	.short	16448
	.short	20772
	.short	-28160
	.short	0
	.short	0
	.short	0
	.short	24528
	.short	-1342
	.type	atmos_heard, %object
	.size	atmos_heard, 3260
atmos_heard:
	.byte	114
	.byte	-8
	.byte	31
	.byte	78
	.byte	21
	.byte	0
	.byte	-76
	.byte	12
	.byte	119
	.byte	11
	.byte	89
	.byte	6
	.byte	103
	.byte	63
	.byte	-38
	.byte	-31
	.byte	0
	.byte	73
	.byte	1
	.byte	65
	.byte	1
	.byte	7
	.byte	0
	.byte	32
	.byte	0
	.byte	0
	.byte	0
	.byte	16
	.byte	0
	.byte	0
	.byte	-124
	.byte	35
	.byte	-122
	.byte	121
	.byte	97
	.byte	24
	.byte	-4
	.byte	-121
	.byte	-7
	.byte	-22
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-13
	.byte	127
	.byte	-25
	.byte	-85
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	125
	.byte	62
	.byte	-50
	.byte	-1
	.byte	-97
	.byte	-81
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-9
	.byte	-7
	.byte	58
	.byte	-1
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-33
	.byte	-25
	.byte	-22
	.byte	-4
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	127
	.byte	-97
	.byte	-82
	.byte	-13
	.byte	-29
	.byte	83
	.byte	-39
	.byte	-128
	.byte	27
	.byte	-14
	.byte	111
	.byte	-121
	.byte	60
	.byte	30
	.byte	-18
	.byte	120
	.byte	-18
	.byte	-18
	.byte	-32
	.byte	-18
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
	.byte	1
	.byte	0
	.byte	-35
	.byte	-35
	.byte	-74
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-33
	.byte	-74
	.byte	107
	.byte	62
	.byte	-42
	.byte	90
	.byte	-83
	.byte	-75
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	62
	.byte	27
	.byte	112
	.byte	67
	.byte	-29
	.byte	-19
	.byte	-113
	.byte	-57
	.byte	-35
	.byte	29
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-36
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
	.byte	59
	.byte	0
	.byte	-69
	.byte	-69
	.byte	-37
	.byte	-74
	.byte	-74
	.byte	109
	.byte	-25
	.byte	-37
	.byte	107
	.byte	-51
	.byte	-42
	.byte	90
	.byte	-81
	.byte	-75
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-61
	.byte	-25
	.byte	-56
	.byte	103
	.byte	29
	.byte	110
	.byte	120
	.byte	-68
	.byte	-29
	.byte	-15
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	0
	.byte	-128
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
	.byte	119
	.byte	7
	.byte	118
	.byte	119
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-7
	.byte	124
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-20
	.byte	-5
	.byte	125
	.byte	1
	.byte	103
	.byte	-128
	.byte	30
	.byte	-113
	.byte	119
	.byte	60
	.byte	119
	.byte	119
	.byte	112
	.byte	119
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
	.byte	-18
	.byte	-18
	.byte	-37
	.byte	-18
	.byte	-74
	.byte	109
	.byte	111
	.byte	-37
	.byte	53
	.byte	-97
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-49
	.byte	0
	.byte	24
	.byte	-16
	.byte	-15
	.byte	14
	.byte	-57
	.byte	-29
	.byte	-18
	.byte	-114
	.byte	-18
	.byte	-18
	.byte	0
	.byte	-18
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
	.byte	29
	.byte	0
	.byte	-35
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-13
	.byte	109
	.byte	-75
	.byte	-26
	.byte	107
	.byte	-83
	.byte	-41
	.byte	90
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-17
	.byte	-13
	.byte	7
	.byte	-100
	.byte	-3
	.byte	-13
	.byte	71
	.byte	-98
	.byte	108
	.byte	-128
	.byte	13
	.byte	-7
	.byte	-73
	.byte	-61
	.byte	30
	.byte	-113
	.byte	119
	.byte	60
	.byte	119
	.byte	119
	.byte	112
	.byte	119
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
	.byte	-18
	.byte	-18
	.byte	-37
	.byte	-18
	.byte	-74
	.byte	109
	.byte	111
	.byte	-37
	.byte	53
	.byte	-97
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-97
	.byte	13
	.byte	-72
	.byte	33
	.byte	-15
	.byte	118
	.byte	-57
	.byte	-29
	.byte	-18
	.byte	-114
	.byte	-18
	.byte	-18
	.byte	0
	.byte	-18
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
	.byte	29
	.byte	0
	.byte	-35
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-13
	.byte	109
	.byte	-75
	.byte	-26
	.byte	107
	.byte	-83
	.byte	-41
	.byte	90
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-31
	.byte	-13
	.byte	-28
	.byte	-77
	.byte	14
	.byte	55
	.byte	60
	.byte	-34
	.byte	-15
	.byte	120
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-64
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
	.byte	-69
	.byte	3
	.byte	-69
	.byte	-69
	.byte	-74
	.byte	109
	.byte	109
	.byte	-37
	.byte	124
	.byte	-66
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-7
	.byte	90
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-10
	.byte	125
	.byte	-66
	.byte	0
	.byte	51
	.byte	-64
	.byte	-113
	.byte	-57
	.byte	59
	.byte	30
	.byte	-69
	.byte	-69
	.byte	-72
	.byte	-69
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
	.byte	119
	.byte	119
	.byte	109
	.byte	119
	.byte	-37
	.byte	-74
	.byte	-73
	.byte	109
	.byte	-102
	.byte	-49
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	62
	.byte	95
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	103
	.byte	-128
	.byte	12
	.byte	-8
	.byte	120
	.byte	7
	.byte	-29
	.byte	-15
	.byte	119
	.byte	-57
	.byte	119
	.byte	119
	.byte	0
	.byte	119
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
	.byte	14
	.byte	0
	.byte	-18
	.byte	-18
	.byte	-74
	.byte	-19
	.byte	109
	.byte	-37
	.byte	-7
	.byte	-74
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-9
	.byte	-7
	.byte	3
	.byte	-50
	.byte	-2
	.byte	-7
	.byte	35
	.byte	-49
	.byte	-1
	.byte	-61
	.byte	56
	.byte	88
	.byte	73
	.byte	0
	.byte	-32
	.byte	10
	.byte	-128
	.byte	-4
	.byte	24
	.byte	1
	.byte	17
	.byte	62
	.byte	0
	.byte	15
	.byte	-100
	.byte	3
	.byte	112
	.byte	0
	.byte	-128
	.byte	0
	.byte	-1
	.byte	0
	.byte	0
	.byte	1
	.byte	-33
	.byte	1
	.byte	0
	.byte	2
	.byte	-127
	.byte	3
	.byte	0
	.byte	-12
	.byte	-5
	.byte	7
	.byte	0
	.byte	-24
	.byte	-5
	.byte	14
	.byte	8
	.byte	-16
	.byte	-9
	.byte	29
	.byte	16
	.byte	-32
	.byte	-48
	.byte	1
	.byte	64
	.byte	126
	.byte	84
	.byte	0
	.byte	16
	.byte	-58
	.byte	60
	.byte	10
	.byte	32
	.byte	16
	.byte	4
	.byte	-127
	.byte	32
	.byte	8
	.byte	0
	.byte	65
	.byte	2
	.byte	-82
	.byte	10
	.byte	-72
	.byte	43
	.byte	-32
	.byte	-82
	.byte	-128
	.byte	9
	.byte	0
	.byte	-121
	.byte	-103
	.byte	-82
	.byte	104
	.byte	-51
	.byte	52
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	50
	.byte	-51
	.byte	48
	.byte	30
	.byte	-51
	.byte	108
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
	.byte	-51
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
	.byte	27
	.byte	0
	.byte	67
	.byte	62
	.byte	-19
	.byte	112
	.byte	-57
	.byte	-29
	.byte	29
	.byte	-113
	.byte	-35
	.byte	-35
	.byte	-36
	.byte	-35
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
	.byte	-69
	.byte	59
	.byte	-74
	.byte	-69
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-51
	.byte	-25
	.byte	90
	.byte	107
	.byte	-75
	.byte	-42
	.byte	-97
	.byte	-81
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	103
	.byte	-61
	.byte	110
	.byte	-56
	.byte	-68
	.byte	29
	.byte	-15
	.byte	120
	.byte	-69
	.byte	-29
	.byte	-69
	.byte	-69
	.byte	-128
	.byte	-69
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
	.byte	7
	.byte	0
	.byte	119
	.byte	119
	.byte	-37
	.byte	118
	.byte	-74
	.byte	109
	.byte	124
	.byte	-37
	.byte	-83
	.byte	-7
	.byte	90
	.byte	107
	.byte	-75
	.byte	-42
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-8
	.byte	124
	.byte	-7
	.byte	108
	.byte	-61
	.byte	13
	.byte	-113
	.byte	-73
	.byte	60
	.byte	30
	.byte	119
	.byte	119
	.byte	119
	.byte	119
	.byte	0
	.byte	112
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
	.byte	-18
	.byte	0
	.byte	-18
	.byte	-18
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-97
	.byte	111
	.byte	-83
	.byte	53
	.byte	90
	.byte	107
	.byte	-66
	.byte	-42
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	125
	.byte	-97
	.byte	47
	.byte	-128
	.byte	12
	.byte	-80
	.byte	-29
	.byte	-15
	.byte	-114
	.byte	-57
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	-18
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
	.byte	-35
	.byte	29
	.byte	-37
	.byte	-35
	.byte	-74
	.byte	109
	.byte	109
	.byte	-37
	.byte	-26
	.byte	-13
	.byte	-83
	.byte	-75
	.byte	90
	.byte	107
	.byte	-49
	.byte	-41
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	25
	.byte	-32
	.byte	3
	.byte	-2
	.byte	-34
	.byte	1
	.byte	120
	.byte	60
	.byte	-35
	.byte	-15
	.byte	-35
	.byte	-35
	.byte	-64
	.byte	-35
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
	.byte	3
	.byte	0
	.byte	-69
	.byte	-69
	.byte	109
	.byte	-69
	.byte	-37
	.byte	-74
	.byte	-66
	.byte	109
	.byte	-42
	.byte	124
	.byte	-83
	.byte	-75
	.byte	90
	.byte	107
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	125
	.byte	62
	.byte	-128
	.byte	-13
	.byte	127
	.byte	-2
	.byte	-56
	.byte	-77
	.byte	-82
	.byte	-16
	.byte	0
	.byte	64
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
	.byte	6
	.byte	0
	.byte	-112
	.byte	-49
	.byte	59
	.byte	-36
	.byte	-15
	.byte	120
	.byte	-57
	.byte	-29
	.byte	119
	.byte	119
	.byte	119
	.byte	119
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
	.byte	-18
	.byte	14
	.byte	-19
	.byte	-18
	.byte	-37
	.byte	-74
	.byte	-74
	.byte	109
	.byte	-13
	.byte	-7
	.byte	-42
	.byte	90
	.byte	-83
	.byte	-75
	.byte	-25
	.byte	107
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-39
	.byte	-16
	.byte	27
	.byte	-14
	.byte	111
	.byte	-121
	.byte	60
	.byte	30
	.byte	-18
	.byte	120
	.byte	-18
	.byte	-18
	.byte	-32
	.byte	-18
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
	.byte	1
	.byte	0
	.byte	-35
	.byte	-35
	.byte	-74
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-33
	.byte	-74
	.byte	107
	.byte	62
	.byte	-42
	.byte	90
	.byte	-83
	.byte	-75
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	62
	.byte	27
	.byte	112
	.byte	67
	.byte	-29
	.byte	-19
	.byte	-113
	.byte	-57
	.byte	-35
	.byte	29
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-36
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
	.byte	59
	.byte	0
	.byte	-69
	.byte	-69
	.byte	-37
	.byte	-74
	.byte	-74
	.byte	109
	.byte	-25
	.byte	-37
	.byte	107
	.byte	-51
	.byte	-42
	.byte	90
	.byte	-81
	.byte	-75
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-33
	.byte	-25
	.byte	11
	.byte	96
	.byte	3
	.byte	-20
	.byte	120
	.byte	60
	.byte	-29
	.byte	-15
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	0
	.byte	-128
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
	.byte	119
	.byte	7
	.byte	118
	.byte	119
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-7
	.byte	124
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	6
	.byte	-8
	.byte	-128
	.byte	127
	.byte	119
	.byte	-64
	.byte	30
	.byte	-113
	.byte	119
	.byte	60
	.byte	119
	.byte	119
	.byte	112
	.byte	119
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
	.byte	-18
	.byte	-18
	.byte	-37
	.byte	-18
	.byte	-74
	.byte	109
	.byte	111
	.byte	-37
	.byte	53
	.byte	-97
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-32
	.byte	124
	.byte	-97
	.byte	63
	.byte	-14
	.byte	-20
	.byte	3
	.byte	60
	.byte	-56
	.byte	103
	.byte	29
	.byte	110
	.byte	120
	.byte	-68
	.byte	-29
	.byte	-15
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	-69
	.byte	0
	.byte	-128
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
	.byte	119
	.byte	7
	.byte	118
	.byte	119
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-7
	.byte	124
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	108
	.byte	-8
	.byte	13
	.byte	-7
	.byte	-73
	.byte	-61
	.byte	30
	.byte	-113
	.byte	119
	.byte	60
	.byte	119
	.byte	119
	.byte	112
	.byte	119
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
	.byte	-18
	.byte	-18
	.byte	-37
	.byte	-18
	.byte	-74
	.byte	109
	.byte	111
	.byte	-37
	.byte	53
	.byte	-97
	.byte	107
	.byte	-83
	.byte	-42
	.byte	90
	.byte	124
	.byte	-66
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	-97
	.byte	13
	.byte	-72
	.byte	33
	.byte	-15
	.byte	118
	.byte	-57
	.byte	-29
	.byte	-18
	.byte	-114
	.byte	-18
	.byte	-18
	.byte	0
	.byte	-18
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
	.byte	29
	.byte	0
	.byte	-35
	.byte	-35
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-13
	.byte	109
	.byte	-75
	.byte	-26
	.byte	107
	.byte	-83
	.byte	-41
	.byte	90
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-17
	.byte	-13
	.byte	5
	.byte	-80
	.byte	1
	.byte	-10
	.byte	60
	.byte	-98
	.byte	-15
	.byte	120
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-64
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
	.byte	-69
	.byte	3
	.byte	-69
	.byte	-69
	.byte	-74
	.byte	109
	.byte	109
	.byte	-37
	.byte	124
	.byte	-66
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-7
	.byte	90
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	3
	.byte	124
	.byte	-64
	.byte	63
	.byte	59
	.byte	96
	.byte	-113
	.byte	-57
	.byte	59
	.byte	30
	.byte	-69
	.byte	-69
	.byte	-72
	.byte	-69
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
	.byte	119
	.byte	119
	.byte	109
	.byte	119
	.byte	-37
	.byte	-74
	.byte	-73
	.byte	109
	.byte	-102
	.byte	-49
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	62
	.byte	95
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	112
	.byte	-66
	.byte	-49
	.byte	31
	.byte	121
	.byte	-10
	.byte	1
	.byte	30
	.byte	-28
	.byte	-77
	.byte	14
	.byte	55
	.byte	60
	.byte	-34
	.byte	-15
	.byte	120
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	-35
	.byte	0
	.byte	-64
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
	.byte	-69
	.byte	3
	.byte	-69
	.byte	-69
	.byte	-74
	.byte	109
	.byte	109
	.byte	-37
	.byte	124
	.byte	-66
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-7
	.byte	90
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	54
	.byte	124
	.byte	-122
	.byte	124
	.byte	-37
	.byte	-31
	.byte	-113
	.byte	-57
	.byte	59
	.byte	30
	.byte	-69
	.byte	-69
	.byte	-72
	.byte	-69
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
	.byte	119
	.byte	119
	.byte	109
	.byte	119
	.byte	-37
	.byte	-74
	.byte	-73
	.byte	109
	.byte	-102
	.byte	-49
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	62
	.byte	95
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	-49
	.byte	-122
	.byte	-36
	.byte	-112
	.byte	120
	.byte	59
	.byte	-29
	.byte	-15
	.byte	119
	.byte	-57
	.byte	119
	.byte	119
	.byte	0
	.byte	119
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
	.byte	14
	.byte	0
	.byte	-18
	.byte	-18
	.byte	-74
	.byte	-19
	.byte	109
	.byte	-37
	.byte	-7
	.byte	-74
	.byte	90
	.byte	-13
	.byte	-75
	.byte	-42
	.byte	107
	.byte	-83
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	124
	.byte	62
	.byte	-9
	.byte	-7
	.byte	2
	.byte	-40
	.byte	0
	.byte	-5
	.byte	30
	.byte	-49
	.byte	120
	.byte	60
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	0
	.byte	-32
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
	.byte	-35
	.byte	1
	.byte	-35
	.byte	-35
	.byte	-37
	.byte	-74
	.byte	-74
	.byte	109
	.byte	62
	.byte	-33
	.byte	90
	.byte	107
	.byte	-75
	.byte	-42
	.byte	124
	.byte	-83
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	-97
	.byte	-49
	.byte	1
	.byte	62
	.byte	-32
	.byte	-97
	.byte	29
	.byte	48
	.byte	-57
	.byte	-29
	.byte	29
	.byte	-113
	.byte	-35
	.byte	-35
	.byte	-36
	.byte	-35
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
	.byte	-69
	.byte	59
	.byte	-74
	.byte	-69
	.byte	109
	.byte	-37
	.byte	-37
	.byte	-74
	.byte	-51
	.byte	-25
	.byte	90
	.byte	107
	.byte	-75
	.byte	-42
	.byte	-97
	.byte	-81
	.byte	124
	.byte	62
	.byte	-13
	.byte	-7
	.byte	-49
	.byte	-25
	.byte	62
	.byte	-97
	.byte	-7
	.byte	124
	.byte	-25
	.byte	-13
	.byte	56
	.byte	-33
	.byte	-25
	.byte	15
	.byte	60
	.byte	-5
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
	.byte	-112
	.byte	113
	.byte	21
	.byte	-8
	.type	dd_heard, %object
	.size	dd_heard, 2568
dd_heard:
	.short	-1934
	.short	19999
	.short	1
	.short	20480
	.short	2935
	.short	3061
	.short	9264
	.short	-7684
	.short	1216
	.short	16129
	.short	-27299
	.short	5201
	.short	17695
	.short	-3157
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-13922
	.short	-15501
	.short	-50
	.short	-20577
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24791
	.short	-30999
	.short	14335
	.short	15038
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-23052
	.short	14143
	.short	-790
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3481
	.short	19051
	.short	32755
	.short	-21529
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6198
	.short	-27867
	.short	32255
	.short	-12615
	.short	20366
	.short	9288
	.short	-28382
	.short	17408
	.short	0
	.short	7
	.short	30961
	.short	-7225
	.short	30583
	.short	30583
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	3822
	.short	-4371
	.short	-18725
	.short	28086
	.short	-1549
	.short	23254
	.short	-19027
	.short	27623
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-4096
	.short	0
	.short	239
	.short	7740
	.short	30958
	.short	-4370
	.short	-4384
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	1
	.short	-8739
	.short	-8778
	.short	-9363
	.short	-18721
	.short	15979
	.short	23254
	.short	-19027
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	0
	.short	0
	.short	7651
	.short	-14449
	.short	7645
	.short	-8739
	.short	-9216
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	59
	.short	-17477
	.short	-18725
	.short	28086
	.short	-9241
	.short	-12949
	.short	23254
	.short	-19025
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6208
	.short	0
	.short	3
	.short	-17288
	.short	-3613
	.short	-17477
	.short	-17477
	.short	-32768
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	1911
	.short	30582
	.short	-9363
	.short	-18725
	.short	31993
	.short	-21141
	.short	23254
	.short	-18957
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-2048
	.short	0
	.short	119
	.short	-28898
	.short	15479
	.short	30583
	.short	30576
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-4370
	.short	-4389
	.short	28086
	.short	-9361
	.short	-24779
	.short	-21141
	.short	23254
	.short	-16772
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	0
	.short	0
	.short	3824
	.short	8064
	.short	-32768
	.short	0
	.short	0
	.short	3825
	.short	-7225
	.short	-28946
	.short	-4370
	.short	-4608
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	29
	.short	-8739
	.short	-9363
	.short	-18725
	.short	28147
	.short	-6475
	.short	-21141
	.short	23255
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3104
	.short	0
	.short	1
	.short	-8644
	.short	30961
	.short	-8739
	.short	-8739
	.short	-16384
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	955
	.short	-17477
	.short	28086
	.short	-9363
	.short	-16772
	.short	-10571
	.short	-21141
	.short	23289
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31744
	.short	0
	.short	59
	.short	-14449
	.short	7739
	.short	-17477
	.short	-17480
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	30583
	.short	30573
	.short	-18725
	.short	28087
	.short	-12390
	.short	-10571
	.short	-21141
	.short	24382
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-32768
	.short	0
	.short	1912
	.short	-3613
	.short	-14473
	.short	30583
	.short	30464
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	14
	.short	-4370
	.short	-4682
	.short	-9363
	.short	-18695
	.short	-3238
	.short	-10571
	.short	-21141
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1552
	.short	0
	.short	0
	.short	-4322
	.short	15480
	.short	-4370
	.short	-4370
	.short	-8192
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	477
	.short	-8739
	.short	-18725
	.short	28086
	.short	-8386
	.short	27482
	.short	-10571
	.short	-21124
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15872
	.short	0
	.short	29
	.short	-8129
	.short	256
	.short	0
	.short	0
	.short	29
	.short	-7225
	.short	-28899
	.short	-8739
	.short	-8740
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	15291
	.short	-17482
	.short	-9363
	.short	-18725
	.short	-6195
	.short	27482
	.short	-10571
	.short	-20577
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-16384
	.short	0
	.short	956
	.short	30961
	.short	-7237
	.short	-17477
	.short	-17536
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	7
	.short	30583
	.short	30427
	.short	28086
	.short	-9348
	.short	-1619
	.short	27482
	.short	-10571
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31992
	.short	0
	.short	0
	.short	30607
	.short	7740
	.short	30583
	.short	30583
	.short	28672
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	238
	.short	-4370
	.short	-9363
	.short	-18725
	.short	28575
	.short	13741
	.short	27482
	.short	-10562
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24832
	.short	0
	.short	14
	.short	-3613
	.short	-14450
	.short	-4370
	.short	-4370
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	7645
	.short	-8741
	.short	28086
	.short	-9363
	.short	-3098
	.short	-19027
	.short	27482
	.short	-10289
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-8192
	.short	0
	.short	478
	.short	15480
	.short	-3619
	.short	-8739
	.short	-8768
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	3
	.short	-17477
	.short	-17555
	.short	-18725
	.short	28094
	.short	31958
	.short	-19027
	.short	27482
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	0
	.short	0
	.short	15296
	.short	32258
	.short	2
	.short	13056
	.short	-17629
	.short	-26289
	.short	-991
	.short	6727
	.short	31487
	.short	29080
	.short	-23057
	.short	-29454
	.short	-4832
	.short	23813
	.short	-15679
	.short	-11646
	.short	-27644
	.short	-9193
	.short	-11496
	.short	27765
	.short	-4564
	.short	28748
	.short	22386
	.short	-9652
	.short	32025
	.short	-26586
	.short	-12207
	.short	-25464
	.short	-16311
	.short	0
	.short	0
	.short	7651
	.short	-14449
	.short	7645
	.short	-8739
	.short	-9216
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	59
	.short	-17477
	.short	-18725
	.short	28086
	.short	-9241
	.short	-12949
	.short	23254
	.short	-19025
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6208
	.short	0
	.short	3
	.short	-17288
	.short	-3613
	.short	-17477
	.short	-17477
	.short	-32768
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	1911
	.short	30582
	.short	-9363
	.short	-18725
	.short	31993
	.short	-21141
	.short	23254
	.short	-18957
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-2048
	.short	0
	.short	119
	.short	-28898
	.short	15479
	.short	30583
	.short	30576
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-4370
	.short	-4389
	.short	28086
	.short	-9361
	.short	-24779
	.short	-21141
	.short	23254
	.short	-16772
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	0
	.short	0
	.short	3825
	.short	-7225
	.short	-28946
	.short	-4370
	.short	-4608
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	29
	.short	-8739
	.short	-9363
	.short	-18725
	.short	28147
	.short	-6475
	.short	-21141
	.short	23255
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3104
	.short	0
	.short	1
	.short	-8644
	.short	30961
	.short	-8739
	.short	-8739
	.short	-16384
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	955
	.short	-17477
	.short	28086
	.short	-9363
	.short	-16772
	.short	-10571
	.short	-21141
	.short	23289
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31744
	.short	0
	.short	59
	.short	-16258
	.short	512
	.short	600
	.short	212
	.short	9149
	.short	13105
	.short	-22729
	.short	16036
	.short	-15202
	.short	-26341
	.short	11106
	.short	30344
	.short	-29965
	.short	1241
	.short	-27967
	.short	29184
	.short	-3268
	.short	-3349
	.short	24020
	.short	-19572
	.short	-32519
	.short	-6959
	.short	3355
	.short	-18517
	.short	-19798
	.short	23307
	.short	8213
	.short	-33
	.short	1998
	.short	-10983
	.short	5956
	.short	3239
	.short	487
	.short	-11141
	.short	29479
	.short	23683
	.short	7796
	.short	-10576
	.short	-19906
	.short	29171
	.short	-8203
	.short	23610
	.short	22025
	.short	-13961
	.short	-14870
	.short	-6248
	.short	-8952
	.short	0
	.short	0
	.short	7651
	.short	-14449
	.short	7645
	.short	-8739
	.short	-9216
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	59
	.short	-17477
	.short	-18725
	.short	28086
	.short	-9241
	.short	-12949
	.short	23254
	.short	-19025
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6208
	.short	0
	.short	3
	.short	-17288
	.short	-3613
	.short	-17477
	.short	-17477
	.short	-32768
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	1911
	.short	30582
	.short	-9363
	.short	-18725
	.short	31993
	.short	-21141
	.short	23254
	.short	-18957
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-2048
	.short	0
	.short	119
	.short	-28898
	.short	15479
	.short	30583
	.short	30576
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	-4370
	.short	-4389
	.short	28086
	.short	-9361
	.short	-24779
	.short	-21141
	.short	23254
	.short	-16772
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	0
	.short	0
	.short	3825
	.short	-7225
	.short	-28946
	.short	-4370
	.short	-4608
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	29
	.short	-8739
	.short	-9363
	.short	-18725
	.short	28147
	.short	-6475
	.short	-21141
	.short	23255
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3104
	.short	0
	.short	1
	.short	-8644
	.short	30961
	.short	-8739
	.short	-8739
	.short	-16384
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	955
	.short	-17477
	.short	28086
	.short	-9363
	.short	-16772
	.short	-10571
	.short	-21141
	.short	23289
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31744
	.short	0
	.short	59
	.short	-16258
	.short	512
	.short	599
	.short	229
	.short	-28850
	.short	-11275
	.short	19144
	.short	-17594
	.short	-17413
	.short	12295
	.short	-12136
	.short	-23958
	.short	31309
	.short	-32354
	.short	-21813
	.short	15570
	.short	20162
	.short	17720
	.short	22754
	.short	3071
	.short	-18724
	.short	-425
	.short	23134
	.short	-29073
	.short	12825
	.short	11129
	.short	12221
	.short	17828
	.short	17146
	.short	19487
	.short	22913
	.short	-20452
	.short	26112
	.short	-7734
	.short	22312
	.short	20312
	.short	7849
	.short	27384
	.short	-22221
	.short	-23847
	.short	-5514
	.short	26410
	.short	-12509
	.short	10525
	.short	18920
	.short	22753
	.short	18688
	.short	0
	.short	29
	.short	-7225
	.short	-28899
	.short	-8739
	.short	-8740
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	15291
	.short	-17482
	.short	-9363
	.short	-18725
	.short	-6195
	.short	27482
	.short	-10571
	.short	-20577
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-16384
	.short	0
	.short	956
	.short	30961
	.short	-7237
	.short	-17477
	.short	-17536
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	7
	.short	30583
	.short	30427
	.short	28086
	.short	-9348
	.short	-1619
	.short	27482
	.short	-10571
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31992
	.short	0
	.short	0
	.short	30607
	.short	7740
	.short	30583
	.short	30583
	.short	28672
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	238
	.short	-4370
	.short	-9363
	.short	-18725
	.short	28575
	.short	13741
	.short	27482
	.short	-10562
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-6193
	.short	-24832
	.short	0
	.short	14
	.short	-3613
	.short	-14450
	.short	-4370
	.short	-4370
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	7645
	.short	-8741
	.short	28086
	.short	-9363
	.short	-3098
	.short	-19027
	.short	27482
	.short	-10289
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	-1549
	.short	-8192
	.short	0
	.short	478
	.short	15480
	.short	-3619
	.short	-8739
	.short	-8768
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	3
	.short	-17477
	.short	-17555
	.short	-18725
	.short	28094
	.short	31958
	.short	-19027
	.short	27482
	.short	-1549
	.short	-6193
	.short	-24770
	.short	31993
	.short	-3097
	.short	-12385
	.short	15996
	.short	0
	.short	0
	.short	15296
	.short	29987
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_stAopRm, %object
	.size	g_stAopRm, 64
g_stAopRm:
	.space	64
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
