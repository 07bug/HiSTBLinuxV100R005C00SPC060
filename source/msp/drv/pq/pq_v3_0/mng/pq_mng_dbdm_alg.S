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
	.file	"pq_mng_dbdm_alg.c"
	.text
	.align	2
	.type	CheckStartEndBorder.part.0, %function
CheckStartEndBorder.part.0:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ble	.L2
	add	r6, r1, r1, lsr #31
	mov	lr, r2
	mov	ip, #0
	mov	r6, r6, asr #1
	b	.L4
.L3:
	add	ip, ip, #1
	cmp	ip, r0
	beq	.L2
.L4:
	mov	r4, lr
	add	lr, lr, #1
	ldrb	r5, [r4]
	cmp	r5, #1
	bne	.L3
	cmp	r6, ip
	blt	.L3
	mov	ip, #0
	strb	ip, [r4]
	ldr	ip, [r3]
	sub	ip, ip, #1
	str	ip, [r3]
.L2:
	cmp	r0, #1
	ldmlefd	sp, {r4, r5, r6, fp, sp, pc}
	add	r1, r1, r1, lsr #31
	sub	ip, r0, #1
	add	r2, r2, ip
	mov	ip, #1
	mov	r4, r1, asr ip
	b	.L7
.L6:
	add	ip, ip, #1
	cmp	ip, r0
	beq	.L11
.L7:
	mov	r1, r2
	sub	r2, r2, #1
	ldrb	lr, [r1]
	cmp	lr, #1
	bne	.L6
	cmp	r4, ip
	blt	.L6
	mov	r2, #0
	strb	r2, [r1]
	ldr	r2, [r3]
	sub	r2, r2, #1
	str	r2, [r3]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L11:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	CheckStartEndBorder.part.0, .-CheckStartEndBorder.part.0
	.align	2
	.type	DetBorderOffsetRuler.isra.2, %function
DetBorderOffsetRuler.isra.2:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	cmp	r1, #1
	mov	r5, r3
	str	r0, [fp, #-88]
	mov	r3, #0
	mov	r4, r2
	str	r3, [fp, #-76]
	str	r3, [fp, #-72]
	str	r3, [fp, #-68]
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	str	r3, [fp, #-80]
	strb	r3, [fp, #-81]
	beq	.L82
	cmp	r1, #2
	subne	r6, fp, #80
	subne	r3, fp, #81
	ldreq	r3, [fp, #4]
	ldreq	r2, [fp, #4]
	addeq	r3, r3, #8192
	strne	r3, [fp, #-92]
	addeq	r6, r2, #8640
	ldreq	r3, [r3, #440]
	addeq	r6, r6, #16
	streq	r3, [fp, #-92]
.L14:
	ldr	r3, [fp, #-88]
	cmp	r3, #4096
	bhi	.L12
	cmp	r4, #8
	beq	.L17
	sub	r1, r3, #3
	cmp	r1, #4
	bls	.L57
	ldrb	r3, [r5, #4]
	cmp	r3, #1
	beq	.L57
	add	r2, r5, #4
	mov	r10, r1
	mov	r3, #4
	b	.L19
.L31:
	ldrb	r0, [r2, #1]!
	cmp	r0, #1
	beq	.L59
.L19:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L31
.L18:
	rsb	ip, r4, r10
	cmp	ip, #3
	ble	.L36
	rsb	r2, r4, ip
	rsb	r7, r4, #0
	add	ip, r5, ip
	mov	r3, #0
	mov	lr, #1
.L35:
	add	r2, r2, r7
	strb	lr, [ip, r3]
	add	r0, r2, r4
	rsb	r3, r4, r3
	cmp	r0, #3
	bgt	.L35
.L36:
	cmp	r1, #0
	mov	r2, r1
	ble	.L34
	ldrb	r0, [r5, r1]
	add	r3, r5, r1
	cmp	r0, #1
	bne	.L37
	b	.L34
.L38:
	ldrb	r0, [r3, #-1]!
	cmp	r0, #1
	beq	.L34
.L37:
	subs	r2, r2, #1
	bne	.L38
.L34:
	add	r3, r4, r2
	cmp	r3, r1
	movcc	r0, #1
	bcs	.L43
.L42:
	strb	r0, [r5, r3]
	add	r3, r3, r4
	cmp	r3, r1
	bcc	.L42
.L43:
	cmp	r10, r2
	bgt	.L41
	add	r3, r2, #1
	str	r6, [fp, #-96]
	mov	r2, r10
	mov	r0, r10
	mov	r1, r3
	rsb	r9, r4, #0
	sub	r3, r4, #1
	add	r8, r4, #1
	mov	r7, #1
	mov	r6, r1
	b	.L45
.L46:
	mov	r2, lr
.L45:
	add	lr, r2, #1
	cmp	lr, r6
	beq	.L83
	cmp	lr, r10
	moveq	r0, r10
	beq	.L46
	ldrb	r1, [r5, lr]
	cmp	r1, #1
	bne	.L46
	add	r0, r4, r0
	rsb	r1, r0, lr
	cmp	r1, r3
	blt	.L61
	add	r1, r4, r0
	rsb	r2, r1, r2
.L47:
	add	r2, r2, r9
	strb	r7, [r5, r0]
	add	ip, r8, r2
	mov	r0, r1
	cmp	ip, r3
	add	r1, r4, r1
	bge	.L47
.L61:
	mov	r0, lr
	b	.L46
.L84:
	ldr	r1, [fp, #-76]
.L20:
	mov	r3, #0
	sub	r0, fp, #76
	mov	ip, r3
	mov	r2, r3
	b	.L54
.L24:
	ldr	r1, [r0, #4]!
.L54:
	cmp	r1, ip
	movhi	r3, r2
	add	r2, r2, #1
	movhi	ip, r1
	cmp	r2, #8
	bne	.L24
	ldr	r2, [fp, #-88]
	mov	r1, #0
	mov	r0, r5
	uxtb	r7, r3
	bl	memset
	cmp	r7, #0
	mov	r3, #0
	str	r3, [r6]
	sxtbne	r3, r7
	moveq	r3, r7
	addne	r1, r5, r3
	add	r3, r3, #7
	movne	r2, #1
	strneb	r2, [r1, #-1]
	strne	r2, [r6]
	cmp	r3, r8
	movcc	r1, #1
	bcs	.L30
.L29:
	strb	r1, [r5, r3]
	add	r3, r3, #8
	ldr	r2, [r6]
	cmp	r3, r8
	add	r2, r2, #1
	str	r2, [r6]
	bcc	.L29
.L30:
	ldr	r3, [fp, #-88]
	cmp	r3, #4096
	bgt	.L12
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	ldr	r0, [fp, #-88]
	bl	CheckStartEndBorder.part.0
.L12:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L83:
	ldr	r6, [fp, #-96]
.L41:
	ldr	r3, [fp, #-88]
	mov	lr, #0
	str	lr, [r6]
	cmp	r3, #4
	bls	.L30
	ldr	r3, [fp, #-88]
	add	r1, r5, #3
	sub	r0, r3, #1
	ldr	r3, [fp, #4]
	add	ip, r3, #8192
	ldr	r3, [fp, #-92]
	add	r0, r3, r0
	add	r3, r3, #3
	b	.L53
.L49:
	ldrb	r2, [r3]
	sub	r7, r2, #1
	sxtb	r2, r2
	cmp	r2, #0
	strleb	lr, [r3]
	ble	.L51
.L80:
	strb	r7, [r3]
.L51:
	add	r3, r3, #1
	cmp	r3, r0
	beq	.L30
.L53:
	ldrb	r2, [r1, #1]!
	cmp	r2, #1
	bne	.L49
	ldr	r7, [r6]
	add	r7, r7, #1
	str	r7, [r6]
	strb	lr, [r1]
	strb	r2, [r1, #-1]
	ldrb	r2, [r3]
	ldrb	r7, [ip, #452]
	add	r8, r2, #1
	sxtb	r2, r2
	cmp	r2, r7
	strltb	r8, [r3]
	blt	.L51
	b	.L80
.L82:
	ldr	r3, [fp, #4]
	ldr	r2, [fp, #4]
	add	r3, r3, #8192
	add	r6, r2, #8640
	ldr	r3, [r3, #444]
	add	r6, r6, #12
	str	r3, [fp, #-92]
	b	.L14
.L17:
	ldr	r3, [fp, #-88]
	sub	r8, r3, #3
	cmp	r8, #4
	bls	.L58
	add	r2, r5, #3
	mov	r3, #4
	b	.L22
.L21:
	add	r3, r3, #1
	cmp	r3, r8
	beq	.L84
.L22:
	ldrb	r1, [r2, #1]!
	cmp	r1, #1
	bne	.L21
	and	r1, r3, #7
	sub	r0, fp, #44
	add	r1, r0, r1, lsl #2
	ldr	r0, [r1, #-32]
	add	r0, r0, #1
	str	r0, [r1, #-32]
	b	.L21
.L59:
	mov	r10, r3
	b	.L18
.L57:
	mov	r10, #4
	b	.L18
.L58:
	mov	r1, #0
	b	.L20
	UNWIND(.fnend)
	.size	DetBorderOffsetRuler.isra.2, .-DetBorderOffsetRuler.isra.2
	.global	__aeabi_uidiv
	.align	2
	.global	PQ_MNG_ALG_GetDbDetInfo
	.type	PQ_MNG_ALG_GetDbDetInfo, %function
PQ_MNG_ALG_GetDbDetInfo:
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
	mov	r4, r2
	mov	r5, r0
	str	r0, [fp, #-92]
	movw	r2, #20508
	mov	r7, r1
	ldr	r0, .L301
	mov	r1, #0
	bl	memset
	mov	r1, r4
	movw	r2, #8260
	mov	r0, r5
	bl	memcpy
	ldr	r2, [r4, #48]
	ldr	r1, .L301+4
	add	r3, r2, #1
	ldr	r0, .L301+4
	strb	r2, [r1, #12]
	uxtb	r3, r3
	ldr	r2, [r4, #64]
	cmp	r3, #64
	strb	r2, [r1, #13]
	add	r2, r2, #1
	ldr	r3, [r4, #56]
	uxtb	r2, r2
	strb	r3, [r1, #14]
	add	r3, r3, #1
	ldr	r1, [r4, #44]
	uxtb	r3, r3
	str	r1, [r0]
	ldr	r1, [r4, #60]
	str	r1, [r0, #4]
	ldr	r1, [r4, #52]
	str	r1, [r0, #8]
	mvnhi	r1, #0
	strhib	r1, [r0, #12]
	cmp	r2, #64
	ldr	r0, .L301
	ldrhi	r1, .L301+4
	mvnhi	r2, #0
	strhib	r2, [r1, #13]
	cmp	r3, #64
	mov	r1, #0
	ldrhi	r2, .L301+4
	mvnhi	r3, #0
	strhib	r3, [r2, #14]
	mov	r2, #16384
	bl	memset
	ldr	r2, .L301+8
	add	r1, r4, #576
	add	ip, r2, #15360
.L89:
	ldr	r3, [r1, #4]!
	ubfx	r0, r3, #0, #11
	ubfx	r3, r3, #16, #11
	str	r0, [r2, #-4]
	str	r3, [r2], #8
	cmp	r2, ip
	bne	.L89
	movw	r2, #3960
	mov	r1, #0
	ldr	r0, .L301+12
	mov	r6, #1
	bl	memset
	ldr	lr, .L301
	add	ip, r4, #64
	movw	r8, #3969
	movw	r5, #3959
.L90:
	cmp	r6, r8
	ldr	r3, [ip, #4]!
	beq	.L91
	add	r2, r6, #16384
	and	r3, r3, #1
	add	r2, r2, #14
	mov	r1, r6
	mov	r0, #1
	strb	r3, [lr, r2]
	b	.L92
.L290:
	mov	r2, r2, asr r0
	add	r0, r0, #1
	cmp	r0, #32
	and	r2, r2, #1
	add	r1, r1, #1
	strb	r2, [r3]
	beq	.L289
.L92:
	add	r3, lr, r1
	cmp	r1, r5
	add	r3, r3, #16384
	ldr	r2, [ip]
	add	r3, r3, #15
	bls	.L290
.L91:
	ldr	r5, .L301+16
	ldr	r1, .L301+12
	add	r3, r1, #2880
	add	r2, r1, #1920
	str	r3, [r5, #24]
	str	r1, [r5, #16]
	str	r2, [r5, #20]
	ldr	r6, [r4]
	ldr	r10, [r4, #8]
	cmp	r6, #4096
	ldr	r8, [r4, #4]
	movle	r3, #0
	movgt	r3, #1
	str	r3, [fp, #-80]
	cmp	r10, #4096
	orrgt	r3, r3, #1
	cmp	r8, #2160
	orrgt	r3, r3, #1
	cmp	r3, #0
	addne	r9, r7, #8192
	bne	.L217
	sub	r2, r6, #4
	movw	r3, #3836
	cmp	r2, r3
	bls	.L291
.L94:
	mov	r3, #0
	str	r3, [r4, #28]
.L95:
	movw	r3, #1080
	cmp	r6, #1920
	cmple	r8, r3
	movgt	r3, #0
	strgt	r3, [r4, #36]
	strgt	r3, [r4, #40]
	cmp	r10, #960
	movgt	r3, #0
	strgt	r3, [r4, #36]
	ldr	r3, [r4, #32]
	cmp	r3, #1
	beq	.L292
.L98:
	add	r9, r7, #8192
	mvn	r3, #0
	strb	r3, [r7]
.L167:
	ldr	r3, [r4, #36]
	cmp	r3, #1
	beq	.L293
.L168:
	mvn	r3, #0
	strb	r3, [r7, #1]
.L192:
	ldr	r3, [r4, #40]
	cmp	r3, #1
	beq	.L294
.L193:
	mvn	r3, #0
	strb	r3, [r7, #2]
.L217:
	ldr	r3, [r7, #4]
	mov	r0, #0
	ldr	r2, [fp, #-92]
	str	r3, [r2, #44]
	ldrsb	r3, [r7]
	str	r3, [r2, #48]
	ldr	r3, [r7, #8]
	str	r3, [r2, #52]
	ldrsb	r3, [r7, #2]
	str	r3, [r2, #56]
	ldr	r3, [r7, #12]
	str	r3, [r2, #60]
	ldrsb	r3, [r7, #1]
	str	r3, [r2, #64]
	ldr	r3, [r9, #456]
	str	r3, [r2, #16]
	ldr	r3, [r9, #460]
	str	r3, [r2, #20]
	ldr	r3, [r9, #464]
	str	r3, [r2, #24]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L289:
	add	r6, r6, #32
	b	.L90
.L291:
	sub	r3, r8, #1
	cmp	r3, #2160
	bcc	.L95
	b	.L94
.L292:
	ldr	r3, [r4, #28]
	cmp	r3, #1
	bne	.L98
	add	r3, r7, #4096
	str	r3, [fp, #-84]
	mov	r2, r3
	ldr	r3, .L301+4
	ldrb	r2, [r2, #30]
	ldr	r1, [r3]
	cmp	r1, r2
	bcc	.L99
	ldrb	r0, [r3, #12]
	add	r3, r0, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L100
.L101:
	ldr	r3, [fp, #-84]
	ldrb	r2, [r3, #28]
	add	r3, r7, #4096
	add	r3, r3, #52
	sub	r1, r2, #1
	uxtb	r1, r1
	sxtb	ip, r1
	cmp	ip, #0
	ble	.L102
.L103:
	sxtb	ip, r1
	sub	r1, r1, #1
	ands	r1, r1, #255
	sxth	ip, ip
	mov	r0, ip, asl #3
	sub	r2, r0, #8
	add	r0, r3, r0
	add	lr, r3, r2
	ldrb	r2, [r3, r2]
	strb	r2, [r3, ip, asl #3]
	ldr	r2, [lr, #4]
	str	r2, [r0, #4]
	bne	.L103
	ldr	r2, .L301+4
	ldrb	r0, [r2, #12]
	ldr	r2, [fp, #-84]
	ldrb	r2, [r2, #28]
.L102:
	ldr	ip, [fp, #-84]
	strb	r0, [ip, #52]
	ldr	r0, .L301+4
	ldr	r1, [ip, #36]
	ldr	r0, [r0]
	cmp	r1, r2
	addcc	r1, r1, #1
	str	r0, [ip, #56]
	movcc	r0, ip
	strcc	r1, [r0, #36]
	cmp	r2, r1
	beq	.L105
	ldr	r2, .L301+4
	ldrb	r3, [r7]
	ldrb	r2, [r2, #12]
.L106:
	cmp	r2, r3
	sxtb	r2, r3
	str	r2, [fp, #-112]
	bne	.L111
	uxtb	r3, r3
	str	r3, [fp, #-96]
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L112
	ldr	r2, [r5, #16]
	cmp	r6, #4096
	mov	r3, #0
	str	r3, [fp, #-76]
	str	r3, [fp, #-72]
	str	r2, [fp, #-88]
	str	r3, [fp, #-68]
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	bhi	.L285
	ldr	r2, [fp, #-96]
	cmp	r2, #8
	beq	.L114
	sub	r9, r6, #3
	cmp	r9, #4
	bls	.L222
	ldr	r2, [fp, #-88]
	ldrb	r3, [r2, #4]
	cmp	r3, #1
	beq	.L222
	add	r3, r2, #4
	mov	r2, #4
.L116:
	add	r2, r2, #1
	str	r2, [fp, #-100]
	cmp	r2, r9
	beq	.L282
	ldrb	r1, [r3, #1]!
	cmp	r1, #1
	bne	.L116
.L282:
	str	r2, [fp, #-108]
.L115:
	ldr	r2, [fp, #-96]
	ldr	r3, [fp, #-100]
	rsb	r3, r2, r3
	cmp	r3, #4
	ldrgt	r2, .L301
	strgt	r2, [fp, #-116]
	ble	.L133
.L132:
	sub	r2, r3, #-1073741823
	ldr	lr, [fp, #-116]
	mov	r1, #0
	add	r2, lr, r2, lsl #2
	mov	ip, r1
	mov	r0, r1
.L131:
	ldr	lr, [r2], #4
	cmp	lr, ip
	movhi	r1, r0
	add	r0, r0, #1
	movhi	ip, lr
	cmp	r0, #3
	bne	.L131
	sub	r3, r3, #1
	ldr	r2, [fp, #-88]
	add	r1, r3, r1
	ldr	r3, [fp, #-96]
	mov	r0, #1
	rsb	r3, r3, r1
	strb	r0, [r2, r1]
	cmp	r3, #4
	bgt	.L132
.L133:
	cmp	r9, #0
	mov	r3, r9
	ble	.L283
	ldr	r2, [fp, #-88]
	ldrb	r1, [r2, r9]
	add	r2, r2, r9
	cmp	r1, #1
	bne	.L136
	b	.L283
.L137:
	ldrb	r1, [r2, #-1]!
	cmp	r1, #1
	beq	.L225
.L136:
	subs	r3, r3, #1
	bne	.L137
.L225:
	str	r3, [fp, #-104]
.L134:
	ldr	r2, [fp, #-96]
	ldr	r3, [fp, #-104]
	add	r3, r3, r2
	cmp	r3, r9
	ldrcc	r2, .L301
	strcc	r2, [fp, #-116]
	bcs	.L144
.L143:
	sub	r2, r3, #-1073741823
	ldr	lr, [fp, #-116]
	mov	r1, #0
	add	r2, lr, r2, lsl #2
	mov	ip, r1
	mov	r0, r1
.L142:
	ldr	lr, [r2], #4
	cmp	lr, ip
	movhi	r1, r0
	add	r0, r0, #1
	movhi	ip, lr
	cmp	r0, #3
	bne	.L142
	sub	r3, r3, #1
	ldr	r2, [fp, #-88]
	add	r1, r3, r1
	ldr	r3, [fp, #-96]
	mov	r0, #1
	add	r3, r1, r3
	strb	r0, [r2, r1]
	cmp	r3, r9
	bcc	.L143
.L144:
	ldr	r3, [fp, #-100]
	ldr	r2, [fp, #-104]
	cmp	r3, r2
	bhi	.L140
	ldr	r3, [fp, #-100]
	mov	r2, #0
	str	r6, [fp, #-116]
	mov	r9, r2
	str	r4, [fp, #-120]
	mov	r6, r3
	b	.L151
.L147:
	ldr	r3, [fp, #-108]
	ldr	r2, [fp, #-104]
	add	r3, r3, #1
	str	r3, [fp, #-108]
	cmp	r3, r2
	mov	r6, r3
	bhi	.L295
.L151:
	ldr	r3, [fp, #-88]
	ldrb	r3, [r3, r6]
	cmp	r3, #1
	bne	.L147
	ldr	r2, [fp, #-100]
	cmp	r2, r6
	beq	.L226
	ldr	r2, [fp, #-96]
	cmp	r2, #0
	beq	.L147
	mov	r1, r2
	rsb	r0, r9, r6
	str	r3, [fp, #-124]
	bl	__aeabi_uidiv
	cmp	r0, #1
	mov	r4, r0
	bls	.L227
	ldr	r3, [fp, #-124]
	mov	r0, r3
.L150:
	ldr	r3, [fp, #-96]
	ldr	lr, .L301
	add	r3, r9, r3
	mov	r9, #0
	sub	r2, r3, #-1073741823
	mov	ip, r9
	mov	r1, r9
	add	r2, lr, r2, lsl #2
.L149:
	ldr	lr, [r2], #4
	cmp	lr, ip
	movhi	r9, r1
	add	r1, r1, #1
	movhi	ip, lr
	cmp	r1, #3
	bne	.L149
	sub	r3, r3, #1
	add	r0, r0, #1
	add	r9, r3, r9
	ldr	r3, [fp, #-88]
	cmp	r0, r4
	mov	r2, #1
	strb	r2, [r3, r9]
	bne	.L150
.L227:
	mov	r9, r6
	b	.L147
.L294:
	ldr	r3, [r4, #28]
	cmp	r3, #1
	bne	.L193
	add	r3, r7, #4096
	str	r3, [fp, #-84]
	mov	r2, r3
	ldr	r3, .L301+4
	ldrb	r2, [r2, #32]
	ldr	r1, [r3, #8]
	cmp	r1, r2
	bcc	.L194
	ldrb	r0, [r3, #14]
	add	r3, r0, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L195
.L196:
	ldr	r3, [fp, #-84]
	ldrb	r1, [r3, #28]
	add	r3, r7, #4224
	add	r3, r3, #52
	sub	r2, r1, #1
	uxtb	r2, r2
	sxtb	ip, r2
	cmp	ip, #0
	ble	.L197
.L198:
	sxtb	r0, r2
	sub	r2, r2, #1
	ands	r2, r2, #255
	sxth	r0, r0
	mov	r1, r0, asl #3
	sub	ip, r1, #8
	add	r1, r3, r1
	add	lr, r3, ip
	ldrb	ip, [r3, ip]
	strb	ip, [r3, r0, asl #3]
	ldr	r0, [lr, #4]
	str	r0, [r1, #4]
	bne	.L198
	ldr	r2, .L301+4
	ldrb	r0, [r2, #14]
	ldr	r2, [fp, #-84]
	ldrb	r1, [r2, #28]
.L197:
	ldr	ip, [fp, #-84]
	strb	r0, [ip, #180]
	ldr	r0, .L301+4
	ldr	r2, [ip, #44]
	ldr	r0, [r0, #8]
	cmp	r2, r1
	addcc	r2, r2, #1
	str	r0, [ip, #184]
	movcc	r0, ip
	strcc	r2, [r0, #44]
	cmp	r1, r2
	beq	.L200
	ldr	r2, .L301+4
	ldrb	r3, [r7, #2]
	ldrb	r2, [r2, #14]
.L201:
	cmp	r2, r3
	sxtb	r2, r3
	bne	.L206
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L207
	ldr	r3, [r5, #24]
	mov	r1, #1
	str	r7, [sp]
	mov	r0, r8
	bl	DetBorderOffsetRuler.isra.2
	ldrsb	r3, [r7, #2]
	ldr	r4, .L301+16
	cmp	r3, #8
	beq	.L208
	ldrb	r3, [r9, #450]
	ldrb	r2, [r9, #451]
	cmp	r3, r2
	addcc	r3, r3, #1
	uxtbcc	r3, r3
	strccb	r3, [r9, #450]
	cmp	r2, r3
	bne	.L210
	cmp	r8, #4
	ble	.L232
	mov	r2, #0
	add	r10, r8, #1
	str	r7, [fp, #-80]
	mov	r8, r2
	mov	r3, #5
	ldr	r7, [fp, #-84]
	b	.L215
.L212:
	add	r3, r3, #1
	cmp	r3, r10
	beq	.L296
.L215:
	ldr	ip, [r7, #20]
	sub	r1, r3, #1
	ldrb	r6, [ip, r1]
	cmp	r6, #1
	bne	.L212
	ldr	r0, [r9, #444]
	sub	r5, r3, #2
	ldrb	r4, [r9, #451]
	add	r2, r2, #1
	ldrsb	lr, [r0, r1]
	cmp	lr, r4
	bge	.L212
	ldrsb	lr, [r0, r5]
	ldrsb	r0, [r0, r3]
	cmp	r4, lr
	bgt	.L214
	cmp	lr, r0
	blt	.L214
	strb	r6, [ip, r5]
	ldr	r0, [r7, #20]
	strb	r8, [r0, r1]
	b	.L212
.L293:
	ldr	r3, [r4, #28]
	cmp	r3, #1
	bne	.L168
	add	r3, r7, #4096
	str	r3, [fp, #-84]
	mov	r2, r3
	ldr	r3, .L301+4
	ldrb	r2, [r2, #31]
	ldr	r1, [r3, #4]
	cmp	r1, r2
	bcc	.L169
	ldrb	r0, [r3, #13]
	add	r3, r0, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L170
.L171:
	ldr	r3, [fp, #-84]
	ldrb	r2, [r3, #28]
	add	r3, r7, #4352
	add	r3, r3, #52
	sub	r1, r2, #1
	uxtb	r1, r1
	sxtb	ip, r1
	cmp	ip, #0
	ble	.L172
.L173:
	sxtb	ip, r1
	sub	r1, r1, #1
	ands	r1, r1, #255
	sxth	ip, ip
	mov	r0, ip, asl #3
	sub	r2, r0, #8
	add	r0, r3, r0
	add	lr, r3, r2
	ldrb	r2, [r3, r2]
	strb	r2, [r3, ip, asl #3]
	ldr	r2, [lr, #4]
	str	r2, [r0, #4]
	bne	.L173
	ldr	r2, .L301+4
	ldrb	r0, [r2, #13]
	ldr	r2, [fp, #-84]
	ldrb	r2, [r2, #28]
.L172:
	ldr	ip, [fp, #-84]
	strb	r0, [ip, #308]
	ldr	r0, .L301+4
	ldr	r1, [ip, #40]
	ldr	r0, [r0, #4]
	cmp	r1, r2
	addcc	r1, r1, #1
	str	r0, [ip, #312]
	movcc	r0, ip
	strcc	r1, [r0, #40]
	cmp	r2, r1
	beq	.L175
	ldr	r2, .L301+4
	ldrb	r3, [r7, #1]
	ldrb	r2, [r2, #13]
.L176:
	cmp	r2, r3
	sxtb	r2, r3
	bne	.L181
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L182
	ldr	r3, [r5, #20]
	mov	r1, #2
	str	r7, [sp]
	mov	r0, r10
	bl	DetBorderOffsetRuler.isra.2
	ldrsb	r3, [r7, #1]
	ldr	r6, .L301+16
	cmp	r3, #8
	beq	.L183
	ldrb	r3, [r9, #449]
	ldrb	r2, [r9, #451]
	cmp	r3, r2
	addcc	r3, r3, #1
	uxtbcc	r3, r3
	strccb	r3, [r9, #449]
	cmp	r2, r3
	bne	.L185
	cmp	r10, #4
	ble	.L230
	add	r3, r10, #1
	str	r4, [fp, #-96]
	str	r3, [fp, #-80]
	mov	r6, #0
	mov	r3, #5
	str	r7, [fp, #-88]
	ldr	r4, [fp, #-84]
	b	.L190
.L187:
	ldr	r2, [fp, #-80]
	add	r3, r3, #1
	cmp	r3, r2
	beq	.L297
.L190:
	ldr	r0, [r4, #24]
	sub	r2, r3, #1
	ldrb	r7, [r0, r2]
	cmp	r7, #1
	bne	.L187
	ldr	r1, [r9, #440]
	sub	r10, r3, #2
	ldrb	lr, [r9, #451]
	add	r6, r6, #1
	ldrsb	ip, [r1, r2]
	cmp	ip, lr
	bge	.L187
	ldrsb	ip, [r1, r10]
	ldrsb	r1, [r1, r3]
	cmp	lr, ip
	bgt	.L189
	cmp	ip, r1
	blt	.L189
	strb	r7, [r0, r10]
	mov	r0, #0
	ldr	r1, [r4, #24]
	strb	r0, [r1, r2]
	b	.L187
.L194:
	mov	r0, #255
	mvn	r2, #0
	strb	r2, [r3, #14]
.L195:
	ldr	r2, .L301+4
	mov	r3, #100
	str	r3, [r2, #8]
	b	.L196
.L169:
	mov	r0, #255
	mvn	r2, #0
	strb	r2, [r3, #13]
.L170:
	ldr	r2, .L301+4
	mov	r3, #100
	str	r3, [r2, #4]
	b	.L171
.L99:
	mov	r0, #255
	mvn	r2, #0
	strb	r2, [r3, #12]
.L100:
	ldr	r2, .L301+4
	mov	r3, #100
	str	r3, [r2]
	b	.L101
.L206:
	mov	r2, r8
	mov	r1, #0
	ldr	r0, [r9, #444]
	bl	memset
	mov	r3, #0
	strb	r3, [r9, #450]
	b	.L217
.L200:
	ldr	r2, .L301+4
	cmp	r1, #1
	ldrb	r2, [r2, #14]
	ble	.L231
	mov	ip, #1
	sxtb	lr, r2
	mov	r0, ip
.L204:
	ldrsb	r4, [r3, #8]
	add	ip, ip, #1
	cmp	r4, lr
	bne	.L203
	ldr	r4, [fp, #-84]
	ldr	r10, [r3, #12]
	ldrb	r6, [r4, #51]
	add	r4, r0, #1
	cmp	r10, r6
	uxtbcs	r0, r4
.L203:
	cmp	ip, r1
	add	r3, r3, #8
	bne	.L204
.L202:
	ldr	r3, [fp, #-84]
	ldrb	r3, [r3, #48]
	cmp	r3, r0
	strlsb	r2, [r7, #2]
	movls	r3, r2
	ldrls	r2, .L301+4
	ldrhib	r3, [r7, #2]
	ldrlsb	r2, [r2, #14]
	b	.L201
.L111:
	add	r9, r7, #8192
	mov	r2, r6
	mov	r1, #0
	ldr	r0, [r9, #436]
	bl	memset
	mov	r3, #0
	strb	r3, [r9, #448]
	b	.L167
.L105:
	ldr	r1, .L301+4
	cmp	r2, #1
	ldrb	lr, [r1, #12]
	ble	.L220
	mov	r9, #1
	mov	ip, r10
	mov	r0, r9
	mov	r10, r6
	sxtb	r1, lr
	str	r2, [fp, #-100]
	str	r1, [fp, #-96]
.L109:
	ldrsb	r1, [r3, #8]
	add	r9, r9, #1
	ldr	r6, [fp, #-96]
	uxtb	r9, r9
	cmp	r1, r6
	sxtb	r1, r9
	bne	.L108
	ldr	r6, [fp, #-84]
	add	r2, r0, #1
	str	r2, [fp, #-88]
	ldr	r2, [r3, #12]
	ldrb	r6, [r6, #49]
	cmp	r2, r6
	ldrcsb	r0, [fp, #-88]
.L108:
	ldr	r2, [fp, #-100]
	add	r3, r3, #8
	cmp	r1, r2
	blt	.L109
	mov	r6, r10
	mov	r10, ip
.L107:
	ldr	r3, [fp, #-84]
	ldrb	r3, [r3, #48]
	cmp	r3, r0
	strlsb	lr, [r7]
	ldrls	r2, .L301+4
	movhi	r2, lr
	ldrhib	r3, [r7]
	movls	r3, lr
	ldrlsb	r2, [r2, #12]
	b	.L106
.L181:
	mov	r2, r10
	mov	r1, #0
	ldr	r0, [r9, #440]
	bl	memset
	mov	r3, #0
	strb	r3, [r9, #449]
	b	.L192
.L175:
	ldr	r1, .L301+4
	cmp	r2, #1
	ldrb	r6, [r1, #13]
	ble	.L229
	mov	r0, #1
	sxtb	r1, r6
	str	r1, [fp, #-80]
	mov	r1, r0
	str	r2, [fp, #-88]
.L179:
	ldrsb	ip, [r3, #8]
	add	r0, r0, #1
	ldr	lr, [fp, #-80]
	cmp	ip, lr
	bne	.L178
	ldr	ip, [fp, #-84]
	ldr	r2, [r3, #12]
	ldrb	lr, [ip, #50]
	add	ip, r1, #1
	cmp	r2, lr
	uxtbcs	r1, ip
.L178:
	ldr	r2, [fp, #-88]
	add	r3, r3, #8
	cmp	r0, r2
	bne	.L179
.L177:
	ldr	r3, [fp, #-84]
	ldrb	r3, [r3, #48]
	cmp	r3, r1
	strlsb	r6, [r7, #1]
	ldrls	r2, .L301+4
	movhi	r2, r6
	ldrhib	r3, [r7, #1]
	movls	r3, r6
	ldrlsb	r2, [r2, #13]
	b	.L176
.L229:
	mov	r1, #1
	b	.L177
.L220:
	mov	r0, #1
	b	.L107
.L183:
	ldr	r3, [fp, #-84]
	mov	r2, r10
	ldr	r1, [r6, #20]
	ldr	r0, [r3, #24]
	bl	memcpy
.L191:
	ldr	r3, .L301+4
	ldr	r3, [r3, #4]
	str	r3, [r7, #12]
	b	.L192
.L182:
	ldr	r3, [fp, #-84]
	mov	r1, #0
	mov	r6, r1
	mov	r2, r10
	ldr	r0, [r3, #24]
	bl	memset
	str	r6, [r7, #12]
	mvn	r3, #0
	mov	r2, r10
	strb	r3, [r7, #1]
	mov	r1, r6
	ldr	r0, [r9, #440]
	bl	memset
	strb	r6, [r9, #449]
	str	r6, [r9, #464]
	b	.L192
.L232:
	mov	r2, #0
.L211:
	str	r2, [r9, #460]
.L216:
	ldr	r3, .L301+4
	ldr	r3, [r3, #8]
	str	r3, [r7, #8]
	b	.L217
.L210:
	ldr	r3, [fp, #-84]
	mov	r2, r8
	ldr	r1, [r5, #24]
	ldr	r0, [r3, #20]
	bl	memcpy
	b	.L216
.L208:
	ldr	r3, [fp, #-84]
	mov	r2, r8
	ldr	r1, [r4, #24]
	ldr	r0, [r3, #20]
	bl	memcpy
	b	.L216
.L207:
	ldr	r3, [fp, #-84]
	mov	r1, #0
	mov	r4, r1
	mov	r2, r8
	ldr	r0, [r3, #20]
	bl	memset
	str	r4, [r7, #8]
	mvn	r3, #0
	mov	r2, r8
	strb	r3, [r7, #2]
	mov	r1, r4
	ldr	r0, [r9, #444]
	bl	memset
	strb	r4, [r9, #450]
	str	r4, [r9, #460]
	b	.L217
.L230:
	mov	r6, #0
.L186:
	str	r6, [r9, #464]
	b	.L191
.L185:
	ldr	r3, [fp, #-84]
	mov	r2, r10
	ldr	r1, [r5, #20]
	ldr	r0, [r3, #24]
	bl	memcpy
	b	.L191
.L297:
	ldr	r7, [fp, #-88]
	ldr	r4, [fp, #-96]
	b	.L186
.L214:
	cmp	r4, r0
	cmple	lr, r0
	movlt	r0, #1
	strltb	r0, [ip, r3]
	ldrlt	r0, [r7, #20]
	strltb	r8, [r0, r1]
	b	.L212
.L231:
	mov	r0, #1
	b	.L202
.L189:
	cmp	lr, r1
	cmple	ip, r1
	movlt	r1, #1
	strltb	r1, [r0, r3]
	ldrlt	r1, [r4, #24]
	movlt	r0, #0
	strltb	r0, [r1, r2]
	b	.L187
.L285:
	add	r9, r7, #8192
.L113:
	ldr	r3, [fp, #-112]
	cmp	r3, #8
	beq	.L158
	ldrb	r3, [r9, #448]
	ldrb	r2, [r9, #451]
	cmp	r3, r2
	addcc	r3, r3, #1
	uxtbcc	r3, r3
	strccb	r3, [r9, #448]
	cmp	r2, r3
	bne	.L158
	cmp	r6, #4
	ble	.L228
	add	r3, r6, #1
	str	r4, [fp, #-100]
	str	r3, [fp, #-80]
	mov	lr, #0
	mov	r6, #5
	str	r10, [fp, #-88]
	str	r7, [fp, #-96]
	ldr	r4, [fp, #-84]
	b	.L165
.L162:
	ldr	r3, [fp, #-80]
	add	r6, r6, #1
	cmp	r6, r3
	beq	.L298
.L165:
	ldr	r1, [r4, #16]
	sub	r3, r6, #1
	ldrb	r7, [r1, r3]
	cmp	r7, #1
	bne	.L162
	ldr	r2, [r9, #436]
	sub	r10, r6, #2
	ldrb	ip, [r9, #451]
	add	lr, lr, #1
	ldrsb	r0, [r2, r3]
	cmp	r0, ip
	bge	.L162
	ldrsb	r0, [r2, r10]
	ldrsb	r2, [r2, r6]
	cmp	ip, r0
	bgt	.L164
	cmp	r0, r2
	blt	.L164
	strb	r7, [r1, r10]
	mov	r1, #0
	ldr	r2, [r4, #16]
	strb	r1, [r2, r3]
	b	.L162
.L228:
	mov	lr, #0
.L161:
	str	lr, [r9, #456]
.L166:
	ldr	r3, .L301+4
	ldr	r3, [r3]
	str	r3, [r7, #4]
	b	.L167
.L296:
	ldr	r7, [fp, #-80]
	b	.L211
.L222:
	mov	r3, #4
	str	r3, [fp, #-108]
	str	r3, [fp, #-100]
	b	.L115
.L114:
	sub	r2, r6, #3
	str	r2, [fp, #-96]
	cmp	r2, #4
	bls	.L117
	ldr	r3, [fp, #-88]
	add	r0, r3, #3
	mov	r3, #4
	b	.L119
.L118:
	ldr	r2, [fp, #-96]
	add	r3, r3, #1
	cmp	r3, r2
	beq	.L299
.L119:
	ldrb	r2, [r0, #1]!
	cmp	r2, #1
	bne	.L118
	and	r2, r3, #7
	sub	r1, fp, #44
	add	r2, r1, r2, lsl #2
	ldr	r1, [r2, #-32]
	add	r1, r1, #1
	str	r1, [r2, #-32]
	b	.L118
.L226:
	ldr	r9, [fp, #-100]
	b	.L147
.L295:
	ldr	r6, [fp, #-116]
	ldr	r4, [fp, #-120]
.L140:
	cmp	r6, #4
	addls	r9, r7, #8192
	movls	r3, #0
	bls	.L146
	ldr	r3, [fp, #-88]
	mov	ip, #0
	add	r9, r7, #8192
	str	r4, [fp, #-100]
	add	lr, r3, #3
	sub	r3, r6, #1
	str	r3, [fp, #-96]
	mov	r3, #3
	b	.L156
.L152:
	ldr	r1, [r9, #436]
	ldrb	r2, [r1, r3]
	sub	r0, r2, #1
	sxtb	r2, r2
	cmp	r2, #0
	ble	.L155
.L284:
	strb	r0, [r1, r3]
.L154:
	ldr	r2, [fp, #-96]
	add	r3, r3, #1
	cmp	r3, r2
	beq	.L300
.L156:
	ldrb	r2, [lr, #1]!
	cmp	r2, #1
	bne	.L152
	strb	r2, [lr, #-1]
	mov	r1, #0
	strb	r1, [lr]
	add	ip, ip, #1
	ldr	r1, [r9, #436]
	ldrb	r0, [r9, #452]
	ldrb	r2, [r1, r3]
	add	r4, r2, #1
	sxtb	r2, r2
	cmp	r2, r0
	movlt	r2, r4
	strltb	r2, [r1, r3]
	blt	.L154
	b	.L284
.L155:
	mov	r2, #0
	strb	r2, [r1, r3]
	b	.L154
.L300:
	ldr	r4, [fp, #-100]
	mov	r3, ip
.L146:
	str	r3, [r9, #456]
.L125:
	ldr	r3, [fp, #-80]
	cmp	r3, #0
	add	r3, r7, #8640
	add	r3, r3, #8
	bne	.L286
	ldr	r2, [fp, #-88]
	mov	r0, r6
	ldr	r1, [fp, #-112]
	bl	CheckStartEndBorder.part.0
.L286:
	ldrsb	r3, [r7]
	str	r3, [fp, #-112]
	b	.L113
.L283:
	str	r9, [fp, #-104]
	b	.L134
.L302:
	.align	2
.L301:
	.word	.LANCHOR0
	.word	.LANCHOR0+16384
	.word	.LANCHOR0+4
	.word	.LANCHOR0+16399
	.word	.LANCHOR0+20480
.L299:
	ldr	r3, [fp, #-76]
.L117:
	mov	r9, #0
	sub	r1, fp, #76
	mov	r0, r9
	mov	r2, r9
	b	.L219
.L121:
	ldr	r3, [r1, #4]!
.L219:
	cmp	r0, r3
	movcc	r9, r2
	add	r2, r2, #1
	movcc	r0, r3
	cmp	r2, #8
	bne	.L121
	ldr	r3, [fp, #-88]
	cmn	r3, r6
	beq	.L285
	mov	r2, r6
	mov	r1, #0
	ldr	r0, [fp, #-88]
	bl	memset
	cmp	r9, #0
	ldrne	r3, [fp, #-88]
	movne	r1, #1
	moveq	r3, r9
	addne	r2, r3, r9
	add	r9, r9, #7
	movne	r3, r1
	strneb	r1, [r2, #-1]
	ldr	r2, [fp, #-96]
	cmp	r9, r2
	bcs	.L123
	mov	r2, #1
.L124:
	ldr	r1, [fp, #-88]
	add	r3, r3, #1
	strb	r2, [r1, r9]
	add	r9, r9, #8
	ldr	r1, [fp, #-96]
	cmp	r9, r1
	bcc	.L124
.L123:
	add	r9, r7, #8192
	str	r3, [r9, #456]
	b	.L125
.L112:
	ldr	r3, [fp, #-84]
	add	r9, r7, #8192
	mov	r2, r6
	mov	r1, #0
	ldr	r0, [r3, #16]
	bl	memset
	mov	r3, #0
	mov	r2, r6
	str	r3, [r7, #4]
	mov	r1, #0
	mvn	r3, #0
	strb	r3, [r7]
	ldr	r0, [r9, #436]
	bl	memset
	mov	r3, #0
	strb	r3, [r9, #448]
	mov	r3, #0
	str	r3, [r9, #456]
	b	.L167
.L158:
	ldr	r3, [fp, #-84]
	mov	r2, r6
	ldr	r1, [r5, #16]
	ldr	r0, [r3, #16]
	bl	memcpy
	b	.L166
.L164:
	cmp	ip, r2
	cmple	r0, r2
	movlt	r2, #1
	strltb	r2, [r1, r6]
	ldrlt	r2, [r4, #16]
	movlt	r1, #0
	strltb	r1, [r2, r3]
	b	.L162
.L298:
	ldr	r10, [fp, #-88]
	ldr	r7, [fp, #-96]
	ldr	r4, [fp, #-100]
	b	.L161
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_GetDbDetInfo, .-PQ_MNG_ALG_GetDbDetInfo
	.align	2
	.global	PQ_MNG_ALG_DBCfgDetector
	.type	PQ_MNG_ALG_DBCfgDetector, %function
PQ_MNG_ALG_DBCfgDetector:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	ldr	ip, [r1, #8]
	ldr	r0, [r1]
	mov	r4, r2
	ldr	lr, [r1, #4]
	cmp	r0, #4096
	cmple	ip, #4096
	movgt	r2, #1
	movle	r2, #0
	cmp	lr, #2160
	orrgt	r2, r2, #1
	cmp	r2, #0
	bne	.L314
	ldr	r2, [r1, #48]
	cmp	r2, #8
	strneh	r3, [r5, #20]
	beq	.L320
.L306:
	ldr	r3, [r1, #64]
	cmp	r3, #8
	ldrneh	r3, [fp, #4]
	strneh	r3, [r5, #22]
	beq	.L321
.L308:
	movw	r3, #1080
	cmp	r0, #1920
	cmple	lr, r3
	mov	r2, #512
	mov	r3, #1
	add	r0, r5, #36
	strh	r3, [r5, #16]
	strh	r3, [r5, #18]
	mov	r1, #0
	movgt	r3, #0
	add	r4, r4, #16
	strgth	r3, [r5, #16]
	strgth	r3, [r5, #18]
	bl	memset
	add	ip, r5, #32
	mov	lr, #0
	movw	r5, #3959
.L310:
	cmp	lr, #3968
	ldr	r2, [ip, #4]!
	beq	.L311
	mov	r0, r4
	mov	r3, #1
	ldrb	r1, [r0, lr]!
	and	r1, r1, r3
	orr	r1, r1, r2
	str	r1, [ip]
	b	.L312
.L323:
	ldrb	r2, [r0, #1]!
	and	r2, r2, #1
	orr	r1, r1, r2, asl r3
	add	r3, r3, #1
	cmp	r3, #32
	str	r1, [ip]
	beq	.L322
.L312:
	add	r2, r3, lr
	cmp	r2, r5
	bls	.L323
.L311:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L322:
	add	lr, lr, #32
	b	.L310
.L320:
	cmp	r0, #0
	add	r3, r0, #7
	movge	r3, r0
	mov	r3, r3, asr #3
	strh	r3, [r5, #20]
	b	.L306
.L321:
	add	r3, ip, #7
	cmp	ip, #0
	movlt	ip, r3
	mov	r3, ip, asr #3
	strh	r3, [r5, #22]
	b	.L308
.L314:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_DBCfgDetector, .-PQ_MNG_ALG_DBCfgDetector
	.global	__aeabi_idiv
	.align	2
	.global	PQ_MNG_ALG_UpdateDMCfg
	.type	PQ_MNG_ALG_UpdateDMCfg, %function
PQ_MNG_ALG_UpdateDMCfg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	lr, .L352
	mov	r5, r0
	mov	r4, r1
	cmp	r0, #0
	sub	ip, fp, #92
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	beq	.L337
	ldr	r6, [r5]
	ldr	r0, [r5, #144]
	cmp	r6, #0
	ldr	r3, [r5, #148]
	bne	.L351
	mov	r0, r6
.L326:
	ldr	r6, .L352+4
	mov	r3, #8
	mov	r2, #4
	strb	r3, [r4, #8]
	strb	r2, [r4, #7]
	strb	r3, [r4, #5]
.L328:
	ldr	r2, .L352+8
	sub	r3, fp, #28
	add	r0, r3, r0, lsl #2
	ldr	r3, [r2, #-4044]
	ldrh	ip, [r0, #-64]
	cmp	r3, #31
	movhi	r1, #1
	movhi	r3, #0
	addls	r1, r3, #1
.L329:
	add	r3, r3, #2
	str	r1, [r2, #-4044]
	add	r3, r5, r3, lsl #2
	str	ip, [r3, #4]!
	ldr	r1, [r5, #140]
	str	r3, [r5, #152]
	cmp	r1, #0
	beq	.L335
	ble	.L340
	mov	r2, #0
	add	lr, r5, #12
	mov	r0, r2
.L333:
	ldr	ip, [r3], #-4
	add	r2, r2, #1
	cmp	r3, lr
	add	r0, r0, ip
	addcc	r3, r5, #136
	cmp	r2, r1
	bne	.L333
.L331:
	bl	__aeabi_idiv
	mov	ip, r0
.L335:
	uxth	r3, ip
	mov	r5, #1
	rsb	r2, r3, #8
	mov	r0, r3, asl #2
	mov	r1, r2, asl #6
	add	lr, r0, r3
	sub	r1, r1, r2, asl #2
	add	r2, r2, lr
	adds	lr, r1, #4
	mov	r3, r3, lsr r5
	addmi	lr, r1, #11
	adds	r1, r0, #4
	rsb	r7, r3, #4
	addmi	r0, r0, #11
	movpl	r0, r1
	adds	r1, r2, #4
	mov	lr, lr, asr #3
	addmi	r2, r2, #11
	movpl	r2, r1
	cmp	r7, #2
	mov	r1, r0, asr #3
	mov	r3, r5, asl r3
	mov	r2, r2, asr #3
	strb	lr, [r4]
	strb	r1, [r4, #2]
	movle	r7, #2
	strb	r2, [r4, #3]
	strb	r3, [r4, #1]
	ble	.L334
	cmp	r7, #4
	movge	r7, #4
	uxtb	r7, r7
.L334:
	mov	r0, #0
	strb	r7, [r4, #4]
	strb	ip, [r4, #6]
	str	r6, [r4, #12]
.L347:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L351:
	mul	r0, r3, r0
	mov	r1, r6
	mov	r0, r0, asl #4
	bl	__aeabi_idiv
	cmp	r6, #720
	usat	r0, #4, r0
	bls	.L326
	mov	r3, #12
	mov	r2, #0
	strb	r3, [r4, #8]
	mov	r3, #10
	ldr	r6, .L352+12
	strb	r2, [r4, #7]
	strb	r3, [r4, #5]
	b	.L328
.L340:
	mov	r0, #0
	b	.L331
.L337:
	mvn	r0, #0
	b	.L347
.L353:
	.align	2
.L352:
	.word	.LANCHOR2
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	.LANCHOR1+16
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_UpdateDMCfg, .-PQ_MNG_ALG_UpdateDMCfg
	.global	DM_DIR_STR_LUT_HD
	.global	DM_DIR_STR_LUT
	.section	.rodata
	.align	2
.LANCHOR2 = . + 0
.LC0:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	5
	.word	6
	.word	6
	.word	7
	.word	8
	.word	8
	.word	8
	.word	8
	.word	8
	.word	8
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	DM_DIR_STR_LUT, %object
	.size	DM_DIR_STR_LUT, 16
DM_DIR_STR_LUT:
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	6
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	DM_DIR_STR_LUT_HD, %object
	.size	DM_DIR_STR_LUT_HD, 16
DM_DIR_STR_LUT_HD:
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	6
	.byte	4
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.bss
	.align	2
.LANCHOR0 = . + 0
.LANCHOR3 = . + 24552
	.type	stDetStaticInfo, %object
	.size	stDetStaticInfo, 20508
stDetStaticInfo:
	.space	20508
	.type	i.4623, %object
	.size	i.4623, 4
i.4623:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
