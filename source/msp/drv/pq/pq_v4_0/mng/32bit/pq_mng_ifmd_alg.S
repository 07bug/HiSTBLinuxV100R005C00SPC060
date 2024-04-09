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
	.file	"pq_mng_ifmd_alg.c"
	.text
	.align	2
	.type	DetectSceneChange, %function
DetectSceneChange:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r1, #128]
	mov	ip, #0
	ldr	r3, [r1, #124]
	mov	lr, r0
	ldr	r5, [r1, #132]
	mov	r2, ip
	add	r3, r3, r4, lsl #1
	ldr	r1, [r0]
	add	r5, r3, r5, lsl #2
	mov	r4, r1
	mov	r5, r5, asl #1
.L4:
	ldr	r3, [lr], #4
	cmp	r1, r3
	add	ip, ip, r3
	movge	r1, r3
	cmp	r4, r3
	movlt	r4, r3
	cmp	r2, #4
	add	r2, r2, #1
	strgt	r5, [r0, #20]
	ldrle	r3, [lr]
	strle	r3, [lr, #-4]
	cmp	r2, #6
	bne	.L4
	rsb	ip, r1, ip
	mov	r3, #3392
	rsb	ip, r4, ip
	movt	r3, 3
	add	r2, ip, #3
	cmp	ip, #0
	movlt	ip, r2
	mov	ip, ip, asr #2
	cmp	r5, ip, asl #1
	movgt	r0, #1
	movle	r0, #0
	cmp	r5, r3
	movle	r0, #0
	andgt	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	DetectSceneChange, .-DetectSceneChange
	.align	2
	.global	calc_MCorMA
	.type	calc_MCorMA, %function
calc_MCorMA:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	lr, [fp, #4]
	rsb	r1, r0, r1
	movw	r4, #34464
	movt	r4, 1
	ldrsb	ip, [lr, #100]
	cmp	ip, #100
	movge	ip, #100
	cmp	r1, r4
	bic	ip, ip, ip, asr #31
	uxtb	ip, ip
	strb	ip, [lr, #100]
	ble	.L8
	add	r3, ip, #10
	uxtb	r3, r3
	strb	r3, [lr, #100]
.L9:
	sxtb	r3, r3
	cmp	r3, #59
	movgt	r3, #0
	movle	r3, #1
	str	r3, [lr, #96]
	ldmfd	sp, {r4, fp, sp, pc}
.L8:
	rsb	r2, r3, r2
	movw	r3, #20000
	cmp	r1, r3
	cmpgt	r2, #1000
	addgt	r3, ip, #6
	suble	r3, ip, #5
	uxtb	r3, r3
	strb	r3, [lr, #100]
	b	.L9
	UNWIND(.fnend)
	.size	calc_MCorMA, .-calc_MCorMA
	.align	2
	.type	Calc22PLD_4FLD, %function
Calc22PLD_4FLD:
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
	mov	r4, r2
	ldr	r2, [r0, #40]
	clz	r1, r1
	ldr	ip, [r0, #32]
	mov	r1, r1, lsr #5
	ldr	r5, [r0, #28]
	str	r2, [fp, #-48]
	cmp	r1, #1
	ldr	r2, [r0, #4]
	ldr	r10, [r0, #44]
	str	r3, [fp, #-64]
	str	r2, [fp, #-52]
	ldr	r2, [r0, #8]
	ldr	r3, [r0, #24]
	ldreq	r3, [fp, #-48]
	str	r2, [fp, #-56]
	ldr	r2, [r0, #16]
	ldr	r9, [r0, #124]
	ldreq	ip, [r4, #40]
	str	r2, [fp, #-68]
	movne	r2, r5
	ldreq	r2, [r4, #44]
	ldr	lr, [r0, #120]
	ldr	r7, [r0, #128]
	ldr	r6, [r0, #132]
	add	lr, lr, r9, lsl #1
	ldr	r8, [r0, #12]
	streq	r10, [fp, #-48]
	moveq	r10, r3
	strne	ip, [r4, #40]
	moveq	r3, r5
	strne	r5, [r4, #44]
	cmp	r2, ip
	add	r7, lr, r7, lsl #2
	movlt	lr, r2
	movge	lr, ip
	cmp	r2, #80
	cmple	r3, #80
	add	r7, r7, r6, lsl #3
	mov	lr, lr, asl #1
	str	r7, [fp, #-60]
	ble	.L16
	add	r8, r3, r3, lsl #1
	mov	r7, r2, asl #1
	cmp	r8, r7
	bgt	.L78
	add	r8, r2, r2, lsl #2
	add	r8, r8, r8, lsr #31
	cmp	ip, r8, asr #1
	bgt	.L19
	cmp	ip, #1000
	bgt	.L79
.L21:
	cmp	r3, #99
	ble	.L22
	cmp	r3, #500
	add	ip, r4, r1
	movlt	lr, r3, asr #31
	movwlt	r6, #34079
	ldrb	r5, [ip, #88]
	movtlt	r6, 20971
	movge	lr, #5
	smulllt	r6, r7, r3, r6
	mov	r6, #1
	rsblt	lr, lr, r7, asr #5
	uxtblt	lr, lr
	rsb	r5, lr, r5
	strb	r5, [ip, #88]
	b	.L18
.L79:
	add	r8, ip, ip, lsl #2
	rsb	r9, r2, r2, lsl #3
	cmp	r8, r9
	blt	.L21
.L19:
	add	ip, r4, r1
	mov	r6, #1
	ldrb	lr, [ip, #88]
	sub	lr, lr, #1
	strb	lr, [ip, #88]
.L18:
	ldr	ip, [fp, #8]
	ldr	lr, [fp, #4]
	mul	lr, ip, lr
	ldr	ip, [fp, #-48]
	mov	lr, lr, asr #16
	mul	ip, lr, ip
	mul	lr, lr, r10
	mov	ip, ip, asr #2
	cmp	ip, #29
	mov	lr, lr, asr #2
	movle	r5, #1
	movgt	r5, #0
	cmp	lr, #400
	movle	r5, #0
	cmp	r5, #0
	bne	.L47
.L58:
	mov	ip, ip, asl #4
	cmp	ip, #127
	ble	.L47
	add	ip, r4, r1
.L63:
	ldrb	r1, [ip, #88]
	sub	r1, r1, #5
	strb	r1, [ip, #88]
.L47:
	cmp	r6, #1
	beq	.L62
.L48:
	mov	lr, #0
.L43:
	ldrsb	ip, [r4, #88]
	ldrsb	r1, [r4, #89]
	cmp	ip, #32
	str	lr, [r4, #36]
	movge	ip, #32
	cmp	r1, #32
	bic	ip, ip, ip, asr #31
	movge	r1, #32
	bic	r1, r1, r1, asr #31
	uxtb	ip, ip
	strb	ip, [r4, #88]
	uxtb	r1, r1
	sxtb	ip, ip
	strb	r1, [r4, #89]
	sxtb	r1, r1
	cmp	ip, #24
	cmpgt	r1, #24
	movgt	r7, #1
	movgt	lr, #1
	movle	lr, #0
	strgt	r7, [r4, #92]
	bgt	.L50
	cmp	r1, #19
	cmpgt	ip, #19
	strle	lr, [r4, #92]
	ldrgt	r7, [r4, #92]
	movle	r7, lr
.L50:
	ldr	r9, [r4, #12]
	movw	r1, #26215
	ldr	r8, [r4, #8]
	movt	r1, 26214
	ldr	r6, [r4, #4]
	add	ip, r9, r8
	ldr	r5, [r4]
	ldr	lr, [r0]
	add	ip, r6, ip
	add	ip, r5, ip
	str	r8, [r4, #12]
	add	ip, lr, ip
	ldr	r8, [r4, #28]
	str	r9, [r4, #16]
	smull	r0, r1, ip, r1
	mov	ip, ip, asr #31
	ldr	r9, [r4, #20]
	stmib	r4, {r5, r6}
	str	lr, [r4]
	rsb	ip, ip, r1, asr #1
	movw	r1, #62537
	add	r8, ip, r8
	movt	r1, 65535
	rsb	r9, r9, r8
	str	ip, [r4, #24]
	cmp	r9, r1
	str	r9, [r4, #28]
	blt	.L52
	movw	r1, #3000
	cmp	r9, r1
	str	ip, [r4, #20]
	movge	r9, r1
	cmp	r7, #0
	str	r9, [r4, #28]
	beq	.L60
	cmp	r9, #1000
	movge	r1, #0
	strgeb	r1, [r4, #88]
	strgeb	r1, [r4, #89]
	strge	r1, [r4, #92]
.L54:
	str	r4, [sp]
	ldr	r1, [fp, #-56]
	ldr	r0, [fp, #-52]
	bl	calc_MCorMA
	ldr	r3, [fp, #-60]
	str	r3, [r4, #32]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L52:
	cmp	r7, #0
	movw	r1, #62536
	movt	r1, 65535
	str	ip, [r4, #20]
	str	r1, [r4, #28]
	bne	.L54
.L60:
	mov	r1, #0
	str	r1, [r4, #28]
	b	.L54
.L78:
	add	ip, r4, r1
	mov	lr, #0
	mov	r6, #1
	strb	lr, [ip, #88]
	b	.L18
.L83:
	rsb	ip, ip, r2
	add	lr, lr, #50
	cmp	ip, #0
	rsblt	ip, ip, #0
	cmp	ip, lr
	ble	.L37
	ldr	ip, [r4, #32]
	cmp	ip, #10
	ble	.L37
	ldr	lr, [r4, #92]
	cmp	lr, #1
	beq	.L45
	movw	lr, #5000
	cmp	ip, lr
	ble	.L36
.L45:
	add	ip, r4, r1
	ldr	lr, [r4, #36]
	ldrb	r5, [ip, #88]
	mvn	lr, lr
	add	lr, lr, r5
	strb	lr, [ip, #88]
.L36:
	ldr	ip, [fp, #8]
	ldr	lr, [fp, #4]
	mul	lr, ip, lr
	ldr	ip, [fp, #-48]
	mov	lr, lr, asr #16
	mul	ip, lr, ip
	mul	lr, lr, r10
	mov	ip, ip, asr #2
	cmp	ip, #29
	mov	lr, lr, asr #2
	movle	r5, #1
	movgt	r5, #0
	cmp	lr, #400
	movle	r5, #0
	cmp	r5, #0
	moveq	r6, #1
	beq	.L58
.L62:
	ldr	lr, [r4, #36]
	add	lr, lr, #1
	cmp	lr, #50
	movge	lr, #50
	bic	lr, lr, lr, asr #31
	b	.L43
.L22:
	mov	r8, r3, asl #3
	str	r8, [fp, #-64]
	cmp	r2, r8
	blt	.L24
	cmp	r3, #10
	mov	r8, ip, asl #1
	str	r8, [fp, #-68]
	movge	r9, r3
	movlt	r9, #10
	mov	r8, r9
	ldr	r9, [fp, #-68]
	cmp	r9, r8, asl #3
	bge	.L25
.L24:
	rsb	r9, ip, r2
	cmp	r9, #0
	rsblt	r9, r9, #0
	cmp	lr, #150
	movlt	lr, #150
	add	lr, lr, #50
	cmp	r9, lr
	ble	.L25
	ldr	lr, [r4, #32]
	cmp	lr, #10
	bgt	.L80
.L25:
	ldr	lr, [fp, #-64]
	cmp	lr, r7
	bge	.L26
	cmp	lr, ip, asl #1
	bge	.L81
.L27:
	add	r6, r6, #100
	add	ip, r4, r1
	cmp	r6, r3, asl #2
	ldrltb	lr, [ip, #88]
	movlt	r6, #1
	ldrgeb	lr, [ip, #88]
	movge	r6, #0
	sublt	lr, lr, #15
	addge	lr, lr, #1
	strb	lr, [ip, #88]
	b	.L18
.L81:
	ldr	ip, [r4, #32]
	cmp	ip, #9
	ble	.L27
.L26:
	add	ip, r2, #150
	cmp	r3, ip
	ble	.L82
.L29:
	ldr	r6, [r4, #92]
	add	ip, r4, r1
	cmp	r6, #1
	ldreqb	lr, [ip, #88]
	movne	r6, #1
	ldrneb	lr, [ip, #88]
	subeq	lr, lr, #1
	subne	lr, lr, #3
	strb	lr, [ip, #88]
	b	.L18
.L82:
	add	r5, r5, #150
	cmp	r3, r5
	movle	r6, #1
	bgt	.L29
	b	.L18
.L80:
	add	ip, r4, r1
	mov	r6, #1
	ldrb	lr, [ip, #88]
	sub	lr, lr, #5
	strb	lr, [ip, #88]
	b	.L18
.L16:
	ldr	r5, [fp, #-52]
	movw	r6, #5499
	cmp	r5, r6
	bgt	.L32
	ldr	r5, [fp, #-56]
	ldr	r7, [fp, #-52]
	cmp	r5, #0
	moveq	r5, #20
	cmp	r7, r5
	bgt	.L32
	cmp	r8, r6
	bgt	.L33
	ldr	r5, [fp, #-68]
	add	r5, r5, #150
	cmp	r8, r5
	ble	.L34
.L33:
	ldr	r5, [fp, #-64]
	cmp	r5, #0
	beq	.L32
.L34:
	cmp	r3, #39
	ble	.L35
	cmp	r3, r2, asl #1
	bge	.L32
.L35:
	cmp	ip, #80
	bgt	.L83
.L37:
	ldr	ip, [fp, #-56]
	cmp	ip, #1000
	ble	.L39
	ldr	ip, [fp, #-52]
	ldr	lr, [fp, #-56]
	mov	ip, ip, asl #3
	cmp	ip, lr, asl #1
	bge	.L40
	ldr	lr, [fp, #-64]
	cmp	lr, #0
	bne	.L41
	ldr	lr, [fp, #-68]
	cmp	lr, r8, asl #1
	ble	.L40
.L41:
	ldr	lr, [fp, #-56]
	movw	ip, #9000
	cmp	lr, ip
	ble	.L36
	ldr	ip, [fp, #8]
	ldr	lr, [fp, #4]
	mul	lr, ip, lr
	add	ip, r4, r1
	ldrb	r1, [ip, #88]
	add	r1, r1, #1
	strb	r1, [ip, #88]
	mov	r1, lr, asr #16
	ldr	lr, [fp, #-48]
	mul	lr, r1, lr
	mul	r1, r1, r10
	mov	lr, lr, asr #2
	cmp	lr, #29
	mov	r1, r1, asr #2
	movle	r6, #1
	movgt	r6, #0
	cmp	r1, #400
	movle	r6, #0
	cmp	r6, #0
	bne	.L48
	mov	lr, lr, asl #4
	cmp	lr, #127
	bgt	.L63
	b	.L48
.L32:
	add	ip, r4, r1
	mov	lr, #0
	strb	lr, [ip, #88]
	b	.L36
.L39:
	add	ip, r4, r1
	ldrb	lr, [ip, #88]
	sub	lr, lr, #1
	strb	lr, [ip, #88]
	b	.L36
.L40:
	ldr	lr, [r4, #92]
	cmp	lr, #1
	bne	.L39
	ldr	lr, [fp, #-56]
	cmp	ip, lr, asl #2
	ble	.L45
	ldr	ip, [fp, #-64]
	cmp	ip, #0
	bne	.L46
	ldr	lr, [fp, #-68]
	mov	ip, r8, asl #3
	cmp	ip, lr, asl #1
	ble	.L45
.L46:
	add	ip, r4, r1
	ldr	lr, [r4, #36]
	ldrb	r5, [ip, #88]
	mvn	lr, lr
	add	lr, r5, lr, lsl #1
	strb	lr, [ip, #88]
	b	.L36
	UNWIND(.fnend)
	.size	Calc22PLD_4FLD, .-Calc22PLD_4FLD
	.global	__aeabi_idiv
	.align	2
	.global	PQ_MNG_ALG_FmdSet
	.type	PQ_MNG_ALG_FmdSet, %function
PQ_MNG_ALG_FmdSet:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #276)
	sub	sp, sp, #276
	ldr	r3, [r0]
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #0
	mov	r10, r2
	beq	.L353
	mov	r2, #28
	mov	r1, #0
	mov	r0, r10
	bl	pq_alg_memset
	ldr	r3, [r5, #68]
	cmp	r3, #1
	beq	.L354
	ldrb	r3, [r4, #7]
	cmp	r3, #255
	beq	.L88
	ldrb	r3, [r4, #8]
	cmp	r3, #255
	beq	.L88
	ldrb	r3, [r4, #9]
	cmp	r3, #255
	beq	.L88
	ldrb	r3, [r4, #4]
	cmp	r3, #255
	beq	.L90
.L361:
	ldrb	r3, [r4, #5]
	cmp	r3, #255
	beq	.L90
	ldrb	r3, [r4, #6]
	cmp	r3, #255
	beq	.L90
.L91:
	ldr	r3, [r5, #48]
	cmp	r3, #0
	ldrneb	r1, [r4, #9]
	ldreqb	r1, [r4, #8]
	str	r1, [r4, #20]
	ldr	r3, [r5, #48]
	cmp	r3, #0
	ldrneb	r3, [r4, #6]
	ldreqb	r3, [r4, #5]
	str	r3, [r4, #24]
	ldr	r2, [r5, #48]
	cmp	r2, #0
	movne	r2, #1
	moveq	r2, #2
	str	r2, [r4, #28]
	ldr	r2, [r5, #48]
	cmp	r2, #0
	ldrne	r2, [r5, #64]
	ldrne	r0, [r5, #60]
	ldreqb	r2, [r4, #6]
	ldreqb	r0, [r4, #9]
	orrs	ip, r3, r1
	moveq	r3, ip
	beq	.L105
	cmp	r3, #1
	cmpeq	r1, #1
	moveq	r3, #1
	movne	r3, #0
	eor	r3, r3, #1
.L105:
	orrs	r1, r2, r0
	beq	.L106
	cmp	r2, #1
	cmpeq	r0, #1
	moveq	r2, #1
	movne	r2, #0
	eor	r1, r2, #1
.L106:
	ldr	ip, [r4, #456]
	add	r6, r4, #96
	ldr	r0, [r4, #460]
	mov	r2, r4
	str	r3, [r4, #12]
	mov	r3, r4
	str	r1, [r4, #16]
	str	ip, [r4, #452]
	str	r0, [r4, #456]
	ldr	r1, [r4, #472]
	ldr	r0, [r5, #52]
	ldr	ip, [r4, #468]
	str	r1, [r4, #468]
	str	r0, [r4, #460]
	str	ip, [r4, #464]
	ldr	r1, [r5, #56]
	str	r1, [r4, #472]
	ldr	r0, [r5, #44]
	ldr	r1, [r5, #40]
	mul	r1, r1, r0
	mov	r1, r1, asr #11
	str	r1, [r4, #476]
.L107:
	ldrh	ip, [r3, #150]
	add	r3, r3, #6
	ldrh	r0, [r3, #142]
	strh	ip, [r3, #146]
	strh	r0, [r3, #144]
	cmp	r3, r6
	bne	.L107
	add	r0, r5, #232
	mov	r3, #0
.L109:
	ldrh	ip, [r2, #152]
	cmp	r1, ip
	ble	.L108
	ldrh	ip, [r2, #148]
	cmp	r1, ip
	ble	.L108
	ldrh	ip, [r2, #150]
	cmp	r1, ip
	addgt	r3, r3, #1
.L108:
	ldr	ip, [r0, #4]!
	add	r2, r2, #6
	strh	ip, [r2, #142]
	cmp	r2, r6
	bne	.L109
	ldr	r2, [r5, #20]
	str	r3, [r5, #232]
	cmp	r2, #1
	beq	.L355
	cmp	r2, #2
	ldr	r9, [r4, #12]
	moveq	r3, #0
	streq	r3, [fp, #-248]
	beq	.L112
	cmp	r2, #3
	moveq	r3, #1
	movne	r3, #2
	str	r3, [fp, #-248]
.L112:
	add	r3, r4, #124
	add	r7, r5, #84
	str	r3, [fp, #-252]
	add	r8, r4, r9
	mov	r0, r3
	mov	r1, r7
	bl	DetectSceneChange
	cmp	r9, #0
	ldr	r3, [fp, #-252]
	streq	r9, [fp, #-256]
	streq	r9, [fp, #-252]
	strb	r0, [r8, #111]
	beq	.L162
	ldrsb	r2, [r4, #111]
	cmp	r2, #0
	bne	.L356
.L256:
	str	r2, [fp, #-252]
	str	r2, [fp, #-256]
.L162:
	mov	r0, r3
	mov	r1, r7
	bl	DetectSceneChange
	strb	r0, [r8, #111]
	ldr	r8, [r5, #24]
	cmp	r8, #0
	beq	.L163
	ldr	r3, .L375+12
	ldr	r3, [r3, #16]
	cmp	r3, #1
	beq	.L357
	ldr	r8, [r5, #76]
	cmp	r8, #1
	beq	.L358
.L171:
	ldr	r2, [r5, #40]
	cmp	r2, #288
	bgt	.L172
	ldr	r8, [r5, #72]
	cmp	r8, #1
	beq	.L163
.L172:
	ldr	r3, [r4, #452]
	cmp	r3, #0
	beq	.L359
.L168:
	ldr	r7, [r5, #28]
	ldr	r8, [r4, #252]
	cmp	r7, #0
	bne	.L360
	ldrsb	ip, [r4, #108]
	ldrsb	r3, [r4, #109]
	cmp	ip, #1
	beq	.L214
	cmp	ip, #2
	beq	.L275
.L220:
	cmp	r8, #1
	beq	.L268
.L349:
	uxtb	r3, r3
	b	.L215
.L88:
	ldr	r3, [r5, #60]
	strb	r3, [r4, #7]
	ldr	r3, [r5, #60]
	strb	r3, [r4, #8]
	ldr	r3, [r5, #60]
	strb	r3, [r4, #9]
	ldrb	r3, [r4, #4]
	cmp	r3, #255
	bne	.L361
.L90:
	ldr	r3, [r5, #48]
	cmp	r3, #0
	ldrne	r3, [r5, #60]
	ldreqb	r3, [r5, #60]
	clzne	r3, r3
	movne	r3, r3, lsr #5
	strb	r3, [r4, #4]
	ldr	r3, [r5, #48]
	cmp	r3, #0
	ldreq	r3, [r5, #60]
	ldrneb	r3, [r5, #60]
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	strb	r3, [r4, #5]
	ldr	r3, [r5, #48]
	cmp	r3, #0
	ldrne	r3, [r5, #60]
	ldreqb	r3, [r5, #60]
	clzne	r3, r3
	movne	r3, r3, lsr #5
	strb	r3, [r4, #6]
	b	.L91
.L366:
	cmp	r8, #0
	bne	.L166
	ldr	r1, .L375
	ldr	r2, [r5, #80]
	ldr	r0, [r1]
	cmp	r2, r0
	bcc	.L167
	ldr	r1, [r1, #4]
	cmp	r2, r1
	bcs	.L167
	mov	r8, r3
.L163:
	ldr	r7, [r5, #28]
	cmp	r7, #0
	bne	.L362
.L173:
	ldrsb	ip, [r4, #108]
	ldrsb	r3, [r4, #109]
	cmp	ip, #1
	beq	.L214
	cmp	ip, #2
	bne	.L220
	mov	r2, #0
.L213:
	cmp	r8, #1
	beq	.L349
	sub	ip, r2, #1
	mov	r3, #2
	clz	ip, ip
	mov	ip, ip, lsr #5
.L215:
	ldr	r6, .L375+4
	sub	lr, fp, #144
	strb	r3, [r4, #109]
	cmp	ip, #1
	strb	ip, [r4, #108]
	ldmia	r6!, {r0, r1, r2, r3}
	ldr	r8, [r5, #8]
	ldr	r9, [r4, #28]
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r6!, {r0, r1, r2, r3}
	str	r8, [fp, #-256]
	ldr	r8, [r4, #16]
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r6, {r0, r1}
	stmia	lr, {r0, r1}
	beq	.L222
	cmp	ip, #2
	beq	.L223
	cmp	ip, #0
	beq	.L224
	mov	r3, #0
	str	r3, [r10, #4]
	str	r3, [r10, #8]
	tst	r9, #1
	ldr	r3, [fp, #-248]
	clzne	r8, r8
	movne	r8, r8, lsr #5
	cmp	ip, #2
	str	r3, [r10, #20]
	ldr	r3, [fp, #-252]
	str	r8, [r10]
	str	r3, [r10, #16]
	mov	r3, #0
	str	r3, [r10, #12]
	beq	.L269
	subs	ip, ip, #1
	mvnne	ip, #0
	mov	r3, ip
.L238:
	cmp	ip, #1
	bls	.L232
.L235:
	str	r3, [r10, #24]
	ldrb	r2, [r4, #8]
	ldrb	r3, [r4, #9]
	strb	r2, [r4, #7]
	strb	r3, [r4, #8]
	ldr	r3, [r5, #20]
	cmp	r3, #1
	beq	.L363
.L236:
	add	r0, r4, #480
	mov	r1, r10
	mov	r2, #28
	bl	pq_alg_memcpy
	ldrb	r3, [r4, #6]
	ldrb	r2, [r4, #5]
	mov	r0, #0
	strb	r3, [r4, #5]
	strb	r2, [r4, #4]
	ldr	r3, [r5, #64]
	strb	r3, [r4, #6]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L353:
	str	r3, [r2]
	mov	r1, r2
	str	r3, [r2, #8]
	str	r3, [r2, #4]
	mov	r2, #28
	str	r3, [r10, #12]
	ldr	r3, [r5, #60]
	str	r3, [r10, #20]
	ldr	r3, [r4]
	add	r3, r3, #1
	str	r3, [r0], #480
	bl	pq_alg_memcpy
.L338:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L356:
	ldrsb	r2, [r4, #112]
	cmp	r2, #0
	beq	.L256
	mov	r2, #1
	str	r2, [fp, #-252]
	str	r2, [fp, #-256]
	b	.L162
.L358:
	ldr	r2, .L375
	ldr	r3, [r5, #80]
	ldr	r1, [r2]
	cmp	r3, r1
	bcc	.L171
	ldr	r2, [r2, #4]
	cmp	r3, r2
	bcc	.L163
	b	.L171
.L268:
	mov	r8, #0
.L216:
	strb	r8, [r4, #109]
	mov	r3, #2
	ldr	r8, [r4, #16]
	ldr	r9, [r4, #28]
	strb	r3, [r4, #108]
.L223:
	mov	r3, #1
	str	r3, [r10, #4]
	str	r3, [r10, #8]
	tst	r9, #1
	ldr	r3, [fp, #-248]
	clzne	r8, r8
	mov	r2, #1
	str	r2, [r10, #12]
	movne	r8, r8, lsr #5
	str	r8, [r10]
	str	r3, [r10, #20]
	ldr	r3, [fp, #-252]
	str	r3, [r10, #16]
	mov	r3, r2
.L232:
	ldr	r2, .L375+8
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #140]
	b	.L235
.L363:
	ldr	r3, [r10, #20]
	cmp	r3, #2
	strneb	r3, [r4, #9]
	b	.L236
.L355:
	ldr	r7, [r4, #452]
	cmp	r7, #0
	beq	.L111
	mov	r3, #2
	ldr	r9, [r4, #12]
	str	r3, [fp, #-248]
	b	.L112
.L265:
	cmp	r2, #1
	beq	.L349
.L214:
	cmp	r8, #1
	beq	.L216
	ldr	r8, [r4, #16]
	mov	r2, #0
	ldr	r9, [r4, #28]
	mov	r3, #1
	strb	r2, [r4, #108]
	strb	r3, [r4, #109]
.L224:
	tst	r9, #1
	mvn	ip, #0
	clzne	r8, r8
	mov	r3, #0
	str	r3, [r10, #4]
	mov	r2, #0
	str	r3, [r10, #8]
	mov	r3, ip
	movne	r8, r8, lsr #5
	str	r2, [r10, #12]
	str	r8, [r10]
.L227:
	ldr	r2, [fp, #-248]
	str	r2, [r10, #20]
	ldr	r2, [fp, #-252]
	str	r2, [r10, #16]
	b	.L238
.L362:
	ldr	r7, [r4, #452]
	ldr	r3, [r4, #28]
	cmp	r7, #0
	ldr	r0, [r5, #212]
	ldr	r2, [r5, #216]
	str	r3, [fp, #-260]
	ldr	r3, [r5, #208]
	bne	.L174
	ldr	r1, [r4, #464]
	cmp	r1, #1
	bgt	.L364
	ldr	r1, [r4, #104]
	cmp	r1, #0
	beq	.L180
	add	r3, r3, r0, lsl #1
	add	r3, r3, r2, lsl #2
	mov	r3, r3, asl #1
	str	r3, [r1]
	ldr	r3, [r4, #104]
	ldr	r2, [r4, #32]
	add	r3, r3, #4
	cmp	r3, r6
	addhi	r3, r4, #36
	str	r2, [fp, #-272]
	cmp	r3, #0
	str	r3, [r4, #104]
	add	r3, r2, #1
	str	r3, [r4, #32]
	beq	.L180
	cmp	r3, #4
	bgt	.L365
.L180:
	sub	r0, fp, #144
	add	r2, r4, #360
	mov	r3, #0
	mvn	r1, #0
	mov	lr, r0
	strb	r3, [r4, #368]
	str	r3, [r4, #360]
	str	r0, [fp, #-272]
	strb	r3, [r4, #369]
	strb	r1, [r4, #113]
	ldmia	r2, {r0, r1, r2}
	ldr	ip, [r4, #408]
	cmp	ip, #1
	stmia	lr, {r0, r1, r2}
	beq	.L177
.L178:
	add	lr, r4, #384
	add	ip, r4, #396
	add	r6, r4, #372
	add	r7, r4, #408
	ldmia	lr, {r0, r1, r2}
	str	r3, [fp, #-144]
	add	r3, r4, #420
	stmia	r6, {r0, r1, r2}
	ldmia	ip, {r0, r1, r2}
	stmia	lr, {r0, r1, r2}
	ldmia	r7, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	ldmia	r3, {r0, r1, r2}
	stmia	r7, {r0, r1, r2}
	ldr	r2, [fp, #-272]
	ldmia	r2, {r0, r1, r2}
	stmia	r3, {r0, r1, r2}
.L174:
	ldr	r3, [r4, #460]
	cmp	r3, #0
	ldr	r3, [r4, #456]
	beq	.L207
	cmp	r3, #0
	beq	.L208
	ldr	r3, [fp, #-260]
	add	r2, r4, #12
	sub	r1, r3, #2
	mov	r3, r1, asl #4
.L348:
	sub	r3, r3, r1, asl #2
	ldrsb	ip, [r4, #108]
	add	r3, r3, #360
	add	r1, r2, r3
	cmp	ip, #1
	ldr	r2, [r2, r3]
	ldrb	r7, [r1, #10]
	ldrsb	r3, [r4, #109]
	beq	.L265
	cmp	ip, #2
	beq	.L213
	cmp	r2, #1
	bne	.L220
	ldr	lr, .L375+4
	mov	r3, #0
	strb	r2, [r4, #108]
	sub	ip, fp, #144
	strb	r3, [r4, #109]
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	r6, [r5, #8]
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	str	r6, [fp, #-256]
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1}
	stmia	ip, {r0, r1}
.L222:
	ldr	r3, [fp, #-256]
	mov	r2, #1
	cmp	r3, #0
	mov	r3, #0
	stmib	r10, {r2, r3}
	bne	.L228
	sxtb	r3, r7
	movw	r0, #26215
	add	r3, r3, #1
.L350:
	movt	r0, 26214
	mov	r2, r3, asr #31
	smull	r0, r1, r3, r0
	rsb	r2, r2, r1, asr #2
	mov	r1, r2, asl #3
	add	r2, r1, r2, lsl #1
	rsb	r3, r2, r3
	sub	r2, fp, #44
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-100]
	str	r3, [r10]
.L229:
	mov	ip, #0
	str	ip, [r10, #12]
	mov	r3, ip
	b	.L227
.L357:
	ldr	r3, [r5, #76]
	ldr	r8, [r5, #72]
	cmp	r3, #1
	beq	.L366
.L166:
	cmp	r8, #1
	beq	.L163
.L167:
	ldr	r3, [r4, #452]
	cmp	r3, #0
	bne	.L168
	ldr	r8, [r5, #44]
	mov	r1, r9
	ldr	lr, [r5, #40]
	mov	r0, r7
	ldr	r3, [r5, #8]
	add	r2, r4, #256
	ldr	ip, [r4, #248]
	stmia	sp, {r8, lr}
	ldr	lr, [r4, #252]
	str	ip, [r4, #244]
	str	lr, [r4, #248]
	bl	Calc22PLD_4FLD
	ldr	r8, [r4, #348]
	str	r8, [r4, #252]
	b	.L163
.L228:
	ldr	r3, [fp, #-256]
	cmp	r3, #1
	bne	.L229
	sxtb	r3, r7
	movw	r0, #26215
	add	r3, r3, #2
	b	.L350
.L354:
	add	r1, r4, #480
	mov	r0, r10
	mov	r2, #28
	bl	pq_alg_memcpy
	b	.L338
.L275:
	mov	r2, r7
	b	.L213
.L207:
	cmp	r3, #0
	bne	.L208
	ldr	r1, [fp, #-260]
	add	r2, r4, #12
	mov	r3, r1, asl #4
	b	.L348
.L364:
	mov	r1, r7
	add	r0, r4, #372
	mov	r2, #60
	bl	pq_alg_memset
	mov	r1, r7
	mov	r2, #20
	add	r0, r4, #432
	ldrb	r7, [r4, #382]
	bl	pq_alg_memset
	b	.L173
.L359:
	ldr	r3, [r5, #8]
	mov	r0, r7
	ldr	ip, [r5, #44]
	mov	r1, r9
	ldr	lr, [r4, #248]
	str	r2, [sp, #4]
	add	r2, r4, #256
	ldr	r7, [r4, #252]
	str	ip, [sp]
	str	lr, [r4, #244]
	str	r7, [r4, #248]
	bl	Calc22PLD_4FLD
	ldr	r8, [r4, #348]
	str	r8, [r4, #252]
	b	.L163
.L208:
	ldr	r3, [fp, #-260]
	add	r2, r4, #12
	sub	r1, r3, #1
	mov	r3, r1, asl #4
	b	.L348
.L111:
	ldr	r2, [r5, #8]
	cmp	r2, #2
	streq	r2, [r4, #120]
	beq	.L114
	cmp	r2, #1
	beq	.L367
.L115:
	ldr	r9, [r4, #12]
	cmp	r9, #0
	beq	.L346
	ldr	r2, [r4, #20]
	rsb	r3, r3, #16
	ldr	r8, [r5, #220]
	cmp	r2, #1
	ldr	r2, [r5, #224]
	ldr	ip, .L375+12
	ldreq	r1, [r5, #228]
	str	r2, [fp, #-248]
	moveq	r2, r8
	ldrne	r2, [r5, #228]
	ldreq	r8, [fp, #-248]
	streq	r1, [fp, #-252]
	streq	r2, [fp, #-248]
	strne	r2, [fp, #-252]
	ldr	r1, [r5, #40]
	ldr	r2, [r5, #44]
	ldr	r0, [fp, #-248]
	mul	r2, r2, r1
	ldr	r1, .L375+12
	rsb	r0, r0, r8
	ldr	r1, [r1]
	mov	r2, r2, asr #9
	cmp	r2, #0
	str	r1, [fp, #-268]
	str	r1, [ip, #4]
	str	r1, [ip, #8]
	str	r1, [ip, #12]
	add	r1, r2, #31
	movlt	r2, r1
	mov	r2, r2, asr #5
	mul	r3, r3, r2
	add	r2, r3, #15
	cmp	r3, #0
	movlt	r3, r2
	mov	r1, r3, asr #4
	add	r1, r1, r1, lsl #1
	add	r1, r1, r1, lsr #31
	mov	r1, r1, asr #1
	cmp	r1, #6
	movlt	r1, #6
	bl	__aeabi_idiv
	ldr	r3, [fp, #-248]
	cmp	r8, r3
	movlt	r2, r8
	movge	r2, r3
	str	r2, [fp, #-260]
	movge	r2, r8
	movlt	r2, r3
	str	r2, [fp, #-256]
	subs	r2, r0, #0
	str	r2, [fp, #-264]
	ble	.L123
	cmp	r3, #254
	movgt	r1, r3, asr #31
	movwgt	r2, #26215
	movle	r1, #50
	movtgt	r2, 26214
	smullgt	r2, r3, r3, r2
	rsbgt	r1, r1, r3, asr #1
	ldr	r3, [fp, #-248]
	add	r1, r1, r3
	cmp	r1, r8
	bge	.L125
	ldr	r2, .L375+12
	mov	r3, #1
	str	r3, [r2]
	mov	r2, r3
.L126:
	ldr	r3, [fp, #-256]
	cmp	r3, #100
	ble	.L345
	ldr	r1, [fp, #-256]
	mov	r0, #100
	str	r2, [fp, #-272]
	ldr	r2, [fp, #-260]
	rsb	r3, r2, r1
	mul	r0, r0, r3
	bl	__aeabi_idiv
	ldr	r2, [fp, #-272]
	cmp	r0, #19
	movle	r1, #0
	ble	.L129
.L345:
	ldr	r1, [fp, #-264]
	movw	r3, #65036
	movt	r3, 65535
	cmp	r1, r3
	movlt	r1, r3
	cmp	r1, #500
	movge	r1, #500
.L129:
	ldr	r3, .L375+12
	ldr	r0, [r3, #8]
	ldr	r3, [fp, #-268]
	cmp	r0, r2
	ldr	r0, .L375+12
	rsb	r3, r3, r2
	clz	r3, r3
	ldr	r0, [r0, #12]
	mov	r3, r3, lsr #5
	addeq	r3, r3, #1
	cmp	r0, r2
	addeq	r3, r3, #1
	ldr	r2, [fp, #-248]
	ldr	r0, [fp, #-252]
	cmp	r3, #0
	mov	r3, #0
	str	r3, [fp, #-144]
	moveq	r1, r3
	cmp	r2, r0
	str	r3, [fp, #-140]
	movge	r0, r2
	cmp	r0, #254
	str	r3, [fp, #-136]
	movgt	ip, r0, asr #31
	movwgt	r2, #26215
	str	r3, [fp, #-132]
	movtgt	r2, 26214
	str	r3, [fp, #-128]
	str	r3, [fp, #-124]
	movle	ip, #50
	smullgt	r2, r3, r0, r2
	rsbgt	ip, ip, r3, asr #1
	ldr	r3, [fp, #-252]
	add	ip, r0, ip
	cmp	ip, r8
	movlt	r0, #1
	movge	r0, #0
	strlt	r0, [fp, #-144]
	cmp	r8, r3
	movlt	ip, r3
	movge	ip, r8
	cmp	ip, #254
	movgt	lr, ip, asr #31
	movwgt	r2, #26215
	movle	lr, #50
	movtgt	r2, 26214
	smullgt	r2, r3, ip, r2
	rsbgt	lr, lr, r3, asr #1
	ldr	r3, [fp, #-248]
	add	lr, ip, lr
	cmp	lr, r3
	movlt	r3, #1
	strlt	r3, [fp, #-140]
	ldr	r3, [fp, #-256]
	cmp	r3, #254
	movgt	ip, r3, asr #31
	movwgt	r2, #26215
	movle	ip, #50
	movtgt	r2, 26214
	smullgt	r2, r3, r3, r2
	ldr	r2, [fp, #-252]
	rsbgt	ip, ip, r3, asr #1
	ldr	r3, [fp, #-256]
	add	ip, r3, ip
	ldr	r3, [fp, #-252]
	cmp	ip, r3
	movlt	r3, #1
	strlt	r3, [fp, #-136]
	ldr	r3, [fp, #-248]
	cmp	r3, r2
	movge	ip, r2
	movlt	ip, r3
	cmp	ip, #254
	movgt	lr, ip, asr #31
	movwgt	r2, #26215
	movle	lr, #50
	movtgt	r2, 26214
	smullgt	r2, r3, ip, r2
	rsbgt	lr, lr, r3, asr #1
	rsb	lr, lr, ip
	cmp	lr, r8
	movgt	r3, #1
	strgt	r3, [fp, #-132]
	ldr	r3, [fp, #-252]
	cmp	r8, r3
	movge	ip, r3
	movlt	ip, r8
	cmp	ip, #254
	movgt	lr, ip, asr #31
	movwgt	r2, #26215
	movle	lr, #50
	movtgt	r2, 26214
	smullgt	r2, r3, ip, r2
	rsbgt	lr, lr, r3, asr #1
	ldr	r3, [fp, #-248]
	rsb	lr, lr, ip
	cmp	lr, r3
	movgt	r3, #1
	strgt	r3, [fp, #-128]
	ldr	r3, [fp, #-260]
	cmp	r3, #254
	movgt	ip, r3, asr #31
	movwgt	r2, #26215
	movle	ip, #50
	movtgt	r2, 26214
	smullgt	r2, r3, r3, r2
	ldr	r2, [fp, #-252]
	rsbgt	ip, ip, r3, asr #1
	ldr	r3, [fp, #-260]
	rsb	r3, ip, r3
	cmp	r3, r2
	movgt	r7, #1
	strgt	r7, [fp, #-124]
	cmp	r0, #0
	beq	.L145
	ldr	r3, [fp, #-128]
	cmp	r3, #0
	bne	.L145
	eor	r3, r1, r1, asr #31
	sub	r3, r3, r1, asr #31
	cmp	r3, #20
	ble	.L146
	cmp	r1, #50
	movlt	r1, #50
.L146:
	cmp	r7, #0
	bne	.L147
	ldr	r3, [fp, #-136]
	cmp	r3, #0
	movne	r1, r7
	bne	.L147
	ldr	r3, [fp, #-128]
	cmp	r0, #0
	cmpne	r3, #0
	bne	.L147
	ldr	r2, [fp, #-132]
	cmp	r2, #0
	bne	.L368
.L148:
	ldr	ip, [fp, #-248]
	cmp	ip, #0
	cmpne	r8, #0
	beq	.L147
	orrs	r3, r2, r3
	movne	r1, #0
.L147:
	sub	r3, fp, #144
	sub	ip, fp, #124
	mov	r2, #0
	b	.L150
.L369:
	ldr	r0, [r3, #4]!
.L150:
	cmp	r3, ip
	add	r2, r2, r0
	bne	.L369
	cmp	r2, #0
	bne	.L151
	cmp	r1, #50
	mvn	r3, #49
	movge	r1, #50
	cmp	r1, r3
	movlt	r1, r3
.L151:
	add	r3, r1, #49
	cmp	r3, #98
	movls	r3, #1
	movls	r1, #0
	bls	.L152
	cmp	r1, #99
	movgt	r3, #0
	movle	r3, #1
.L152:
	ldr	r2, [fp, #-252]
	cmp	r2, #1
	movgt	r3, #0
	andle	r3, r3, #1
	ldr	r2, [r4, #116]
	cmp	r3, #0
	movne	r1, #0
	add	r1, r1, r2
	cmp	r1, #1000
	str	r1, [r4, #116]
	movgt	r3, #1000
	strgt	r3, [r4, #116]
	bgt	.L155
	cmn	r1, #1000
	movw	r3, #64536
	movt	r3, 65535
	strlt	r3, [r4, #116]
	bge	.L370
.L157:
	mov	r3, #1
	str	r3, [r4, #120]
	str	r3, [fp, #-248]
	b	.L112
.L269:
	mov	r3, #1
	b	.L232
.L145:
	ldr	r3, [fp, #-140]
	cmp	r3, #0
	beq	.L146
	ldr	r3, [fp, #-132]
	cmp	r3, #0
	bne	.L146
	eor	r3, r1, r1, asr #31
	sub	r3, r3, r1, asr #31
	cmp	r3, #20
	ble	.L146
	mvn	r3, #49
	cmp	r1, r3
	movge	r1, r3
	b	.L146
.L125:
	ldr	r2, .L375+12
	mov	r3, #0
	str	r3, [r2]
	mov	r2, r3
	b	.L126
.L370:
	cmp	r1, #200
	bgt	.L155
	cmn	r1, #200
	blt	.L157
.L346:
	ldr	r3, [r4, #120]
	str	r3, [fp, #-248]
	b	.L112
.L155:
	mov	r3, #0
	str	r3, [r4, #120]
	str	r3, [fp, #-248]
	b	.L112
.L365:
	ldr	r3, [r4, #100]
	sub	ip, fp, #44
	mov	r1, #0
	str	r1, [fp, #-264]
	mov	r2, r3
	str	r3, [fp, #-276]
	ldr	r3, [r3]
	str	r3, [ip, #-196]!
	mov	r9, r3
	mov	lr, ip
	str	r3, [fp, #-268]
	str	ip, [fp, #-280]
.L181:
	cmp	r9, r3
	add	r2, r2, #4
	add	r1, r1, #1
	movlt	r9, r3
	cmp	r6, r2
	addcc	r2, r4, #36
	cmp	r1, #5
	beq	.L371
	ldr	r3, [r2]
	ldr	r0, [fp, #-268]
	str	r3, [lr, #4]!
	cmp	r3, r0
	strlt	r3, [fp, #-268]
	strlt	r1, [fp, #-264]
	b	.L181
.L371:
	ldr	r0, [fp, #-280]
	mov	r3, #0
	ldr	r1, [fp, #-264]
	str	r9, [fp, #-292]
.L186:
	ldr	r2, [r0], #4
	cmp	r3, r1
	cmpne	r2, r9
	add	r3, r3, #1
	movlt	r9, r2
	cmp	r3, #5
	bne	.L186
	ldr	r3, [fp, #-276]
	add	r2, r4, #432
	str	r9, [fp, #-216]
	sub	lr, fp, #208
	add	r3, r3, #4
	str	r3, [fp, #-264]
	cmp	r6, r3
	ldr	r6, [fp, #-268]
	addcc	r3, r4, #36
	strcc	r3, [fp, #-264]
	ldr	r3, [fp, #-292]
	str	r6, [fp, #-220]
	mov	r6, r6, asl #1
	str	r2, [fp, #-288]
	str	r3, [fp, #-212]
	ldmia	ip!, {r0, r1, r2, r3}
	str	r6, [fp, #-280]
	sub	r6, fp, #148
	str	r6, [fp, #-296]
	mov	r6, #0
	str	ip, [fp, #-276]
	mov	ip, #0
	str	ip, [fp, #-284]
	ldr	ip, [fp, #-264]
	stmia	lr!, {r0, r1, r2, r3}
	sub	r1, fp, #144
	ldr	r3, [fp, #-276]
	str	ip, [r4, #100]
	mvn	ip, #0
	str	ip, [fp, #-264]
	ldr	ip, [fp, #-272]
	str	r1, [fp, #-272]
	ldmia	r3, {r0, r1, r2, r3}
	str	ip, [r4, #32]
	ldr	ip, [fp, #-288]
	str	r7, [fp, #-300]
	str	r8, [fp, #-304]
	ldr	r7, [fp, #-292]
	mov	r8, ip
	str	r4, [fp, #-292]
	ldr	r4, [fp, #-296]
	str	r5, [fp, #-296]
	ldr	r5, [fp, #-268]
	str	r10, [fp, #-268]
	mov	r10, r6
	stmia	lr, {r0, r1, r2, r3}
	mvn	r2, #0
	str	r2, [fp, #-276]
.L197:
	sub	lr, fp, #208
	str	r5, [fp, #-188]
	str	r9, [fp, #-184]
	sub	ip, fp, #176
	str	r7, [fp, #-180]
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	mov	r2, #100
	ldr	r1, .L375+8
	ldr	r0, [fp, #-272]
	bl	memcpy
	ldr	r3, [fp, #-280]
	cmp	r3, r9
	bgt	.L192
	sub	ip, fp, #156
	sub	r3, fp, #176
	mov	r1, r4
	mov	r2, #0
	b	.L191
.L373:
	cmp	r0, r5
	addeq	r2, r2, #1
.L190:
	add	r3, r3, #4
	cmp	r3, ip
	beq	.L372
.L191:
	ldr	r0, [r1, #4]!
	cmp	r0, #0
	ldr	r0, [r3]
	beq	.L373
	mov	r0, r0, asl #5
	cmp	r0, r7
	addgt	r2, r2, #1
	b	.L190
.L372:
	cmp	r2, #4
	movle	r2, #0
	movgt	r2, #1
	cmp	r2, #0
	beq	.L192
	cmp	r2, #1
	bne	.L264
	ldr	r3, [fp, #-292]
	ldrsb	r3, [r3, #113]
	add	r2, r3, #1
	cmp	r6, r2
	beq	.L193
	add	r2, r6, #4
	cmp	r3, r2
	beq	.L193
.L264:
	str	r6, [fp, #-276]
.L192:
	add	r10, r10, #1
.L196:
	add	r6, r6, #1
	add	r8, r8, #4
	cmp	r6, #5
	add	r4, r4, #20
	bne	.L197
	ldr	r5, [fp, #-296]
	mov	r1, r10
	ldr	r4, [fp, #-292]
	ldr	r7, [fp, #-300]
	ldr	r2, [r5, #124]
	ldr	r3, [r5, #128]
	ldr	r8, [fp, #-304]
	cmp	r3, r2
	ldr	r10, [fp, #-268]
	movge	r3, r2
	cmp	r3, #64
	ldr	r3, [fp, #-256]
	movle	r2, #0
	movgt	r2, #1
	cmp	r3, #0
	moveq	r3, r2
	orrne	r3, r2, #1
	str	r2, [r4, #364]
	cmp	r1, #4
	orrgt	r3, r3, #1
	cmp	r3, #0
	bne	.L374
	ldr	r3, [fp, #-264]
	cmp	r3, #4
	ldrhi	ip, [r4, #360]
	bhi	.L202
	ldr	r3, [fp, #-264]
	ldr	r1, [r4, #12]
	add	r2, r4, r3, lsl #2
	and	r3, r3, #1
	ldr	r2, [r2, #432]
	cmp	r2, #3
	strb	r2, [r4, #368]
	movle	ip, #0
	movgt	ip, #1
	cmp	r1, r3
	str	ip, [r4, #360]
	ldrne	r3, [fp, #-264]
	ldreqb	r3, [fp, #-264]
	addne	r3, r3, #5
	uxtbne	r3, r3
	strb	r3, [r4, #370]
.L202:
	ldr	r2, [fp, #-264]
	cmp	r2, #0
	mov	r3, r2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #369]
	blt	.L205
	uxtb	r9, r2
	mov	r3, ip
.L206:
	add	r2, r4, #360
	ldr	lr, [r4, #408]
	strb	r9, [r4, #113]
	ldmia	r2, {r0, r1, r2}
	cmp	lr, #1
	ldr	lr, [fp, #-272]
	stmia	lr, {r0, r1, r2}
	bne	.L178
	cmp	ip, #0
	bne	.L178
.L177:
	mov	r1, #2
	mov	r2, #0
	strb	r1, [r4, #428]
	strb	r1, [r4, #416]
	strb	r1, [r4, #404]
	strb	r1, [r4, #392]
	str	r2, [r4, #420]
	str	r2, [r4, #408]
	str	r2, [r4, #396]
	str	r2, [r4, #384]
	b	.L178
.L367:
	ldr	r2, [r4, #20]
	cmp	r2, #0
	bne	.L116
	ldr	r2, [r4, #24]
	cmp	r2, #0
	bne	.L115
.L117:
	ldr	r2, [r4, #120]
.L114:
	str	r2, [fp, #-248]
	ldr	r9, [r4, #12]
	b	.L112
.L374:
	cmp	r2, #0
	movne	r3, #0
	strneb	r3, [r4, #368]
	bne	.L200
	ldrb	r3, [r4, #368]
	sub	r3, r3, #1
	sxtb	r3, r3
	cmp	r3, #4
	movlt	r7, r3
	movge	r7, #4
	bic	r7, r7, r7, asr #31
	uxtb	r7, r7
	strb	r7, [r4, #368]
	sxtb	r7, r7
.L200:
	mov	r3, #0
	str	r7, [r4, #432]
	mov	ip, r3
	str	r7, [r4, #436]
	str	r7, [r4, #440]
	str	r7, [r4, #444]
	str	r7, [r4, #448]
	str	r3, [r4, #360]
	strb	r3, [r4, #370]
	strb	r3, [r4, #369]
.L205:
	ldrb	r9, [fp, #-276]
	mov	r3, ip
	b	.L206
.L376:
	.align	2
.L375:
	.word	.LANCHOR1
	.word	.LANCHOR2+100
	.word	.LANCHOR2
	.word	.LANCHOR0
.L193:
	ldr	r3, [r8]
	add	r3, r3, #1
	cmp	r3, #5
	movge	r3, #5
	bic	r3, r3, r3, asr #31
	str	r3, [r8]
	cmp	r3, #3
	ble	.L347
	ldr	r2, [fp, #-288]
	mov	r3, #0
	mov	r1, #3
.L195:
	cmp	r6, r3
	add	r3, r3, #1
	strne	r1, [r2]
	cmp	r3, #5
	add	r2, r2, #4
	bne	.L195
.L347:
	str	r6, [fp, #-276]
	str	r6, [fp, #-264]
	b	.L196
.L123:
	bge	.L125
	cmp	r8, #254
	movgt	r1, r8, asr #31
	movwgt	r2, #26215
	movle	r1, #50
	movtgt	r2, 26214
	smullgt	r2, r3, r8, r2
	rsbgt	r1, r1, r3, asr #1
	ldr	r3, [fp, #-248]
	add	r1, r1, r8
	cmp	r1, r3
	bge	.L125
	ldr	r2, .L375+12
	mov	r3, #2
	str	r3, [r2]
	mov	r2, r3
	b	.L126
.L116:
	cmp	r2, #1
	bne	.L115
	ldr	r2, [r4, #24]
	cmp	r2, #1
	bne	.L115
	b	.L117
.L368:
	ldr	ip, [fp, #-140]
	cmp	ip, #0
	bne	.L147
	b	.L148
.L360:
	ldr	r3, [r4, #28]
	str	r3, [fp, #-260]
	b	.L174
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_FmdSet, .-PQ_MNG_ALG_FmdSet
	.global	g_u32FrmRateThr_H
	.global	g_u32FrmRateThr_L
	.global	g_u32IPDetect
	.section	.rodata
	.align	2
.LANCHOR2 = . + 0
.LC0:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	1
	.word	1
.LC1:
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.type	g_u32PDTypeNum, %object
	.size	g_u32PDTypeNum, 8
g_u32PDTypeNum:
	.word	32
	.word	22
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	g_u32FrmRateThr_L, %object
	.size	g_u32FrmRateThr_L, 4
g_u32FrmRateThr_L:
	.word	23800
	.type	g_u32FrmRateThr_H, %object
	.size	g_u32FrmRateThr_H, 4
g_u32FrmRateThr_H:
	.word	24200
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	stastlasi1432big.4488, %object
	.size	stastlasi1432big.4488, 16
stastlasi1432big.4488:
	.space	16
	.type	g_u32IPDetect, %object
	.size	g_u32IPDetect, 4
g_u32IPDetect:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
