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
	.file	"pq_mng_dei_alg.c"
	.text
	.align	2
	.type	PQ_MNG_CopyU32ByBitWithSignal.part.0, %function
PQ_MNG_CopyU32ByBitWithSignal.part.0:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	rsb	lr, r3, #32
	sub	ip, r3, #1
	rsb	r1, r1, lr
	mov	r0, r0, asl r1
	mvn	r1, #0
	mov	r0, r0, lsr lr
	mov	ip, r0, lsr ip
	tst	ip, #1
	eorne	r0, r0, r1, asl r3
	biceq	r0, r0, r1, asl r3
	str	r0, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	PQ_MNG_CopyU32ByBitWithSignal.part.0, .-PQ_MNG_CopyU32ByBitWithSignal.part.0
	.align	2
	.global	PQ_MNG_CopyU32ByBitWithSignal
	.type	PQ_MNG_CopyU32ByBitWithSignal, %function
PQ_MNG_CopyU32ByBitWithSignal:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [fp, #4]
	add	lr, r1, ip
	cmp	lr, #32
	ldmhifd	sp, {fp, sp, pc}
	add	r3, ip, r3
	cmp	r3, #32
	ldmhifd	sp, {fp, sp, pc}
	mov	r3, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	PQ_MNG_CopyU32ByBitWithSignal.part.0
	UNWIND(.fnend)
	.size	PQ_MNG_CopyU32ByBitWithSignal, .-PQ_MNG_CopyU32ByBitWithSignal
	.align	2
	.global	PQ_MNG_CopyU32ByBitWithoutSignal
	.type	PQ_MNG_CopyU32ByBitWithoutSignal, %function
PQ_MNG_CopyU32ByBitWithoutSignal:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [fp, #4]
	add	lr, r1, ip
	cmp	lr, #32
	ldmhifd	sp, {fp, sp, pc}
	add	r3, ip, r3
	cmp	r3, #32
	ldmhifd	sp, {fp, sp, pc}
	rsb	lr, ip, #32
	mvn	r3, #0
	rsb	r1, r1, lr
	mvn	ip, r3, asl ip
	mov	r1, r0, asl r1
	and	r1, ip, r1, lsr lr
	str	r1, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	PQ_MNG_CopyU32ByBitWithoutSignal, .-PQ_MNG_CopyU32ByBitWithoutSignal
	.global	__aeabi_idiv
	.align	2
	.global	PQ_MNG_ALG_API_GMD
	.type	PQ_MNG_ALG_API_GMD, %function
PQ_MNG_ALG_API_GMD:
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
	cmp	r1, #0
	cmpne	r2, #0
	mov	r4, r0
	mov	r5, r3
	mov	r9, r1
	beq	.L17
	add	r0, r2, r2, lsr #31
	mov	r1, r2
	mov	r0, r0, asr #1
	add	r0, r0, #1048576
	bl	__aeabi_idiv
	mov	r1, r9
	mov	r10, r0
	add	r0, r9, r9, lsr #31
	mov	r0, r0, asr #1
	add	r0, r0, #1048576
	bl	__aeabi_idiv
	ldr	ip, .L22
	ldr	r3, [ip, #4]
	cmp	r3, #0
	bgt	.L21
.L11:
	ldr	r2, [ip, #48]
	ldr	r3, .L22
	cmp	r2, #3
	subgt	r2, r2, #4
	movle	r2, #0
	usatgt	r2, #4, r2
	str	r2, [r3, #48]
.L12:
	str	r2, [r5]
	mov	r8, r0
	ldr	r2, [r4]
	mov	r9, r0, asr #31
	ldr	r3, [r4, #4]
	sub	r5, fp, #60
	ldr	r1, [ip, #56]
	sub	lr, fp, #76
	ldr	r0, [ip, #52]
	str	r2, [ip, #52]
	ldr	r2, [r4, #8]
	str	r3, [ip, #56]
	str	r1, [fp, #-72]
	ldr	r3, [r4, #12]
	movw	r4, #65535
	ldr	r1, [ip, #60]
	str	r2, [ip, #60]
	ldr	r2, [ip, #64]
	str	r0, [fp, #-76]
	str	r1, [fp, #-68]
	str	r3, [ip, #64]
	str	r2, [fp, #-64]
.L15:
	smull	r0, r1, r0, r10
	mov	r2, r0, lsr #12
	mov	r3, r1, asr #12
	orr	r2, r2, r1, asl #20
	mul	r1, r2, r9
	mla	r1, r3, r8, r1
	umull	r2, r3, r2, r8
	add	r3, r1, r3
	mov	r7, r3, asr #11
	mov	r6, r2, lsr #11
	orr	r6, r6, r3, asl #21
	adds	r2, r6, #1
	adc	r3, r7, #0
	movs	r3, r3, asr #1
	mov	r2, r2, rrx
	cmp	r4, r2
	movge	r3, r2
	sub	r2, fp, #64
	movlt	r3, r4
	cmp	lr, r2
	str	r3, [r5], #4
	ldrne	r0, [lr, #4]!
	bne	.L15
.L14:
	ldr	r2, [ip, #72]
	ldr	r3, [ip, #76]
	ldr	r1, [ip, #80]
	mov	r2, r2, lsr #2
	add	r3, r2, r3, lsr #1
	add	r3, r3, r1
	cmp	r3, #3072
	movge	r0, #255
	bge	.L16
	cmp	r3, #1024
	movlt	r0, #0
	blt	.L16
	sub	r3, r3, #1024
	add	r0, r3, #7
	cmp	r3, #0
	movlt	r3, r0
	mov	r0, r3, asr #3
.L16:
	sub	r1, fp, #56
	ldr	lr, [fp, #-60]
	ldmia	r1, {r1, r2, r3}
	str	lr, [ip, #68]
	str	r1, [ip, #72]
	str	r2, [ip, #76]
	str	r3, [ip, #80]
.L10:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L21:
	ldr	r3, [ip]
	cmp	r3, #0
	bge	.L11
	ldr	r3, [ip, #8]
	cmp	r3, #0
	ble	.L11
	ldr	r2, [ip, #48]
	add	r2, r2, #1
	usat	r2, #4, r2
	str	r2, [ip, #48]
	b	.L12
.L17:
	mvn	r0, #0
	b	.L10
.L23:
	.align	2
.L22:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_API_GMD, .-PQ_MNG_ALG_API_GMD
	.align	2
	.global	PQ_MNG_ALG_API_GMD_P
	.type	PQ_MNG_ALG_API_GMD_P, %function
PQ_MNG_ALG_API_GMD_P:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r1, #0
	cmpne	r2, #0
	mov	r4, r0
	mov	r5, r3
	mov	r6, r1
	beq	.L32
	add	r0, r2, r2, lsr #31
	mov	r1, r2
	mov	r0, r0, asr #1
	add	r0, r0, #1048576
	bl	__aeabi_idiv
	mov	r1, r6
	mov	r10, r0
	add	r0, r6, r6, lsr #31
	mov	r0, r0, asr #1
	add	r0, r0, #1048576
	bl	__aeabi_idiv
	ldr	lr, .L37
	ldr	r3, [lr, #92]
	ldr	r2, [lr, #16]
	mov	r1, r3
	str	r3, [fp, #-80]
	ldr	r3, [lr, #84]
	rsb	r3, r1, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	ldr	r3, [lr, #88]
	str	r3, [fp, #-84]
	blt	.L36
.L27:
	mov	r3, #0
	str	r3, [lr, #96]
.L28:
	str	r3, [r5]
	mov	r6, r0
	ldr	r3, [r4, #4]
	mov	r7, r0, asr #31
	ldr	r2, [r4, #8]
	sub	r5, fp, #60
	ldr	r0, [r4]
	sub	ip, fp, #76
	ldr	r1, [r4, #12]
	movw	r4, #65535
	str	r3, [fp, #-72]
	str	r0, [fp, #-76]
	str	r2, [fp, #-68]
	str	r1, [fp, #-64]
.L30:
	smull	r0, r1, r0, r10
	mov	r2, r0, lsr #12
	mov	r3, r1, asr #12
	orr	r2, r2, r1, asl #20
	mul	r1, r2, r7
	mla	r1, r3, r6, r1
	umull	r2, r3, r2, r6
	add	r3, r1, r3
	mov	r9, r3, asr #11
	mov	r8, r2, lsr #11
	orr	r8, r8, r3, asl #21
	adds	r2, r8, #1
	adc	r3, r9, #0
	movs	r3, r3, asr #1
	mov	r2, r2, rrx
	cmp	r4, r2
	movge	r3, r2
	sub	r2, fp, #64
	movlt	r3, r4
	cmp	ip, r2
	str	r3, [r5], #4
	ldrne	r0, [ip, #4]!
	bne	.L30
.L29:
	ldr	r2, [fp, #-56]
	ldr	r3, [fp, #-52]
	ldr	r1, [fp, #-48]
	mov	r2, r2, lsr #2
	add	r3, r2, r3, lsr #1
	add	r3, r3, r1
	cmp	r3, #3072
	movge	r3, #255
	bge	.L31
	cmp	r3, #1024
	movlt	r3, #0
	blt	.L31
	sub	r3, r3, #1024
	add	r2, r3, #7
	cmp	r3, #0
	movlt	r3, r2
	mov	r3, r3, asr #3
.L31:
	ldr	r2, [fp, #-84]
	mov	r0, r3
	str	r3, [lr, #92]
	str	r2, [lr, #84]
	ldr	r2, [fp, #-80]
	str	r2, [lr, #88]
.L25:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L36:
	rsb	r3, r1, r3
	ldr	r2, [lr, #12]
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	ble	.L27
	ldr	r3, [lr, #96]
	add	r3, r3, #1
	usat	r3, #4, r3
	str	r3, [lr, #96]
	b	.L28
.L32:
	mvn	r0, #0
	b	.L25
.L38:
	.align	2
.L37:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_API_GMD_P, .-PQ_MNG_ALG_API_GMD_P
	.global	__aeabi_uidiv
	.align	2
	.global	PQ_MNG_ALG_RGMV_HVCHK
	.type	PQ_MNG_ALG_RGMV_HVCHK, %function
PQ_MNG_ALG_RGMV_HVCHK:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	subs	r8, r2, #0
	str	r1, [fp, #-116]
	mov	ip, r3
	str	r0, [fp, #-112]
	ldr	r1, [fp, #4]
	ldr	r10, [fp, #12]
	beq	.L39
	cmp	r3, #0
	cmpne	r1, #0
	mov	r2, #0
	str	r2, [fp, #-72]
	moveq	lr, #1
	movne	lr, #0
	str	r2, [fp, #-68]
	str	r2, [fp, #-64]
	str	r2, [fp, #-56]
	str	r2, [fp, #-48]
	str	r2, [fp, #-52]
	str	r2, [fp, #-60]
	beq	.L39
	add	r0, r3, #380
	movw	r2, #43691
	add	r0, r0, #3
	movt	r2, 10922
	add	r1, r1, r1, lsr #31
	smull	r2, r3, r0, r2
	mov	r0, r0, asr #31
	rsb	r3, r0, r3, asr #6
	cmp	r3, #2
	movhi	r2, #192
	movls	r2, #0
	cmp	r3, #1
	str	r2, [fp, #-80]
	subhi	r3, r3, r3, asl #2
	addhi	r2, ip, #544
	addhi	r2, r2, #1
	strls	lr, [fp, #-92]
	addhi	r3, r2, r3, lsl #7
	movhi	r3, r3, lsr #6
	movhi	r3, r3, asl #4
	addhi	r3, r3, #63
	bichi	r3, r3, #63
	strhi	r3, [fp, #-92]
	cmp	r10, #5
	mov	r3, r1, asr #1
	beq	.L82
	adds	r2, r3, #9
	addmi	r3, r3, #24
	movpl	r3, r2
	mov	r3, r3, asr #4
	str	r3, [fp, #-88]
.L46:
	cmp	ip, #960
	ble	.L47
	add	r3, ip, ip, lsr #31
	mov	r3, r3, asr #1
	adds	r9, r3, #33
	addmi	r9, r3, #96
	cmp	r10, #5
	mov	r9, r9, asr #6
	beq	.L83
.L49:
	ldr	r3, [fp, #-88]
	cmp	r3, #0
	beq	.L39
	movw	r2, #43691
	mov	r3, #0
	movt	r2, 10922
	str	r3, [fp, #-100]
	str	r3, [fp, #-84]
	str	r3, [fp, #-108]
	str	r3, [fp, #-104]
	str	r2, [fp, #-96]
.L50:
	cmp	r9, #0
	beq	.L60
	ldr	r3, [fp, #-100]
	mov	r5, #0
	bic	r6, r3, #3
	add	r6, r8, r6
	b	.L58
.L84:
	cmp	r5, #5
	ble	.L63
	ldr	r2, [fp, #-92]
	cmp	r5, #23
	ldr	r3, [fp, #-80]
	mov	ip, #8
	movgt	r3, r2
.L52:
	ldr	r2, [fp, #-96]
	cmp	r5, #5
	smull	r0, r1, r5, r2
	movle	r2, #0
	movgt	r2, #1
	cmp	r5, #11
	sub	r1, r1, r5, asr #31
	mov	r2, r2, asl #7
	ldrgt	lr, [fp, #-80]
	mov	r0, r1, asl #3
	sub	r0, r0, r1, asl #1
	subgt	r1, r1, #1
	movle	r1, #0
	rsb	r0, r0, r5
	mulgt	r1, lr, r1
	add	ip, ip, r0, lsl #2
	add	r1, r1, r2
	ldr	r2, [fp, #-84]
	mul	r0, r2, r3
	ldr	r2, [fp, #-88]
	mov	r3, #9
	mul	lr, r2, r1
	sub	r2, fp, #72
	add	ip, ip, r0, lsr #2
	mov	r1, #0
	add	r4, ip, lr, lsr #2
	ldr	r0, [r8, r4, asl #2]
	mov	r7, r4, asl #2
	bl	PQ_MNG_CopyU32ByBitWithSignal.part.0
	add	r7, r7, #4
	ldr	r1, [r8, r4, asl #2]
	mov	r3, #8
	ldr	r0, [r8, r7]
	sub	r2, fp, #56
	ubfx	lr, r1, #9, #10
	ubfx	ip, r1, #19, #10
	mov	r1, #7
	str	lr, [fp, #-68]
	str	ip, [fp, #-64]
	bl	PQ_MNG_CopyU32ByBitWithSignal.part.0
	ldr	r3, [r8, r7]
	ubfx	r0, r3, #15, #10
	ubfx	r3, r3, #25, #4
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
.L55:
	ldr	r3, [fp, #-64]
	add	r5, r5, #1
	ldr	r2, [fp, #-56]
	add	r6, r6, #16
	cmp	r3, #127
	ubfx	r1, r3, #4, #26
	rsb	r0, r1, r0
	movls	r3, #0
	movhi	r3, #1
	cmp	r2, #0
	bic	r0, r0, r0, asr #31
	rsblt	r2, r2, #0
	cmp	r2, #3
	movle	r2, #0
	andgt	r2, r3, #1
	cmp	r0, #255
	movhi	r2, #0
	andls	r2, r2, #1
	ldr	r0, [fp, #-72]
	cmp	r2, #0
	ldrne	r2, [fp, #-104]
	addne	r2, r2, #1
	strne	r2, [fp, #-104]
	ldr	r2, [fp, #-68]
	rsb	r2, r1, r2
	eor	r1, r0, r0, asr #31
	sub	r1, r1, r0, asr #31
	cmp	r1, #3
	movle	r3, #0
	andgt	r3, r3, #1
	bic	r2, r2, r2, asr #31
	cmp	r2, #255
	movhi	r3, #0
	andls	r3, r3, #1
	cmp	r3, #0
	ldrne	r3, [fp, #-108]
	addne	r3, r3, #1
	strne	r3, [fp, #-108]
	cmp	r5, r9
	beq	.L60
.L58:
	cmp	r10, #5
	beq	.L84
	mov	r3, #9
	sub	r2, fp, #72
	mov	r1, #0
	ldr	r0, [r6]
	bl	PQ_MNG_CopyU32ByBitWithSignal.part.0
	ldr	r0, [r6]
	mov	r3, #8
	sub	r2, fp, #56
	ubfx	lr, r0, #9, #10
	ubfx	ip, r0, #19, #10
	mov	r1, #7
	ldr	r0, [r6, #4]
	str	lr, [fp, #-68]
	str	ip, [fp, #-64]
	bl	PQ_MNG_CopyU32ByBitWithSignal.part.0
	ldr	r3, [r6, #4]
	ubfx	r0, r3, #15, #10
	ubfx	r3, r3, #25, #4
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
	b	.L55
.L60:
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #8]
	ldr	r3, [fp, #-84]
	add	r2, r2, r1
	str	r2, [fp, #-100]
	ldr	r2, [fp, #-88]
	add	r3, r3, #1
	str	r3, [fp, #-84]
	cmp	r3, r2
	bne	.L50
	cmp	r9, #0
	beq	.L39
	ldr	r3, [fp, #-84]
	movw	r5, #511
	mul	r9, r3, r9
	ldr	r3, [fp, #-104]
	mov	r0, r3, asl #7
	ldr	r3, [fp, #-108]
	mov	r1, r9
	mov	r4, r3, asl #7
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-112]
	mov	r1, r9
	cmp	r0, r5
	movcc	r3, r0
	movcs	r3, r5
	mov	r0, r4
	str	r3, [r2]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-116]
	cmp	r0, r5
	movcs	r0, r5
	str	r0, [r3]
.L39:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L47:
	adds	r9, ip, #33
	addmi	r9, ip, #96
	cmp	r10, #5
	mov	r9, r9, asr #6
	bne	.L49
.L83:
	adds	r9, ip, #33
	addmi	r9, ip, #96
	mov	r9, r9, asr #6
	b	.L49
.L82:
	adds	r2, r3, #5
	addmi	r3, r3, #12
	movpl	r3, r2
	mov	r3, r3, asr #3
	str	r3, [fp, #-88]
	b	.L46
.L63:
	mov	r3, #128
	mov	ip, #0
	b	.L52
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_RGMV_HVCHK, .-PQ_MNG_ALG_RGMV_HVCHK
	.global	g_pstDeiSwAlgPara
	.global	g_bMcDiEn
	.data
	.align	2
	.type	g_bMcDiEn, %object
	.size	g_bMcDiEn, 4
g_bMcDiEn:
	.word	1
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_pstDeiSwAlgPara, %object
	.size	g_pstDeiSwAlgPara, 48
g_pstDeiSwAlgPara:
	.space	48
	.type	nAdjK_STAT.4304, %object
	.size	nAdjK_STAT.4304, 4
nAdjK_STAT.4304:
	.space	4
	.type	g_mtnsum0, %object
	.size	g_mtnsum0, 4
g_mtnsum0:
	.space	4
	.type	g_mtnsum1, %object
	.size	g_mtnsum1, 4
g_mtnsum1:
	.space	4
	.type	g_mtnsum2, %object
	.size	g_mtnsum2, 4
g_mtnsum2:
	.space	4
	.type	g_mtnsum3, %object
	.size	g_mtnsum3, 4
g_mtnsum3:
	.space	4
	.type	g_MTSum_GMD, %object
	.size	g_MTSum_GMD, 16
g_MTSum_GMD:
	.space	16
	.type	nAdjK_status.4326, %object
	.size	nAdjK_status.4326, 12
nAdjK_status.4326:
	.space	12
	.type	nAdjK_STAT_p.4325, %object
	.size	nAdjK_STAT_p.4325, 4
nAdjK_STAT_p.4325:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
