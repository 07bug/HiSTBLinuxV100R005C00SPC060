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
	.file	"pq_mng_db_alg.c"
	.text
	.align	2
	.type	FillBorder_Size8, %function
FillBorder_Size8:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	cmp	r2, #4096
	mov	r4, r3
	mov	r5, r2
	mov	r3, #0
	mov	r6, r0
	mov	r7, r1
	str	r3, [r4]
	str	r3, [fp, #-68]
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	bhi	.L1
	sub	r0, r2, #3
	cmp	r0, #4
	bls	.L3
	add	r2, r6, #3
	mov	r3, #4
	b	.L5
.L4:
	add	r3, r3, #1
	cmp	r3, r0
	beq	.L19
.L5:
	ldrb	r1, [r2, #1]!
	cmp	r1, #1
	bne	.L4
	and	r1, r3, #7
	sub	ip, fp, #36
	add	r3, r3, #1
	add	r1, ip, r1, lsl #2
	cmp	r3, r0
	ldr	ip, [r1, #-32]
	add	ip, ip, #1
	str	ip, [r1, #-32]
	bne	.L5
.L19:
	ldr	r3, [fp, #-68]
.L3:
	mov	r8, #0
	sub	r1, fp, #68
	mov	r0, r8
	mov	r2, r8
	b	.L11
.L7:
	ldr	r3, [r1, #4]!
.L11:
	cmp	r3, r0
	movhi	r8, r2
	add	r2, r2, #1
	movhi	r0, r3
	cmp	r2, #8
	bne	.L7
	mov	r2, r5
	mov	r1, #0
	mov	r0, r6
	bl	pq_alg_memset
	cmp	r8, #0
	bne	.L20
.L8:
	sub	r2, r7, #1
	add	r2, r2, r8
	cmp	r5, r2
	bls	.L1
	mov	r3, #1
.L10:
	strb	r3, [r6, r2]
	add	r2, r2, r7
	ldr	r1, [r4]
	cmp	r5, r2
	add	r1, r1, #1
	str	r1, [r4]
	bhi	.L10
.L1:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L20:
	add	r3, r6, r8
	mov	r2, #1
	strb	r2, [r3, #-1]
	ldr	r3, [r4]
	add	r3, r3, r2
	str	r3, [r4]
	b	.L8
	UNWIND(.fnend)
	.size	FillBorder_Size8, .-FillBorder_Size8
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
	ble	.L22
	add	r6, r1, r1, lsr #31
	mov	lr, r2
	mov	ip, #0
	mov	r6, r6, asr #1
	b	.L24
.L23:
	add	ip, ip, #1
	cmp	ip, r0
	beq	.L22
.L24:
	mov	r4, lr
	add	lr, lr, #1
	ldrb	r5, [r4]
	cmp	r5, #1
	bne	.L23
	cmp	r6, ip
	blt	.L23
	mov	ip, #0
	strb	ip, [r4]
	ldr	ip, [r3]
	sub	ip, ip, #1
	str	ip, [r3]
.L22:
	cmp	r0, #1
	ldmlefd	sp, {r4, r5, r6, fp, sp, pc}
	add	r1, r1, r1, lsr #31
	sub	ip, r0, #1
	add	r2, r2, ip
	mov	ip, #1
	mov	r4, r1, asr ip
	b	.L27
.L26:
	add	ip, ip, #1
	cmp	ip, r0
	beq	.L30
.L27:
	mov	r1, r2
	sub	r2, r2, #1
	ldrb	lr, [r1]
	cmp	lr, #1
	bne	.L26
	cmp	r4, ip
	blt	.L26
	mov	r2, #0
	strb	r2, [r1]
	ldr	r2, [r3]
	sub	r2, r2, #1
	str	r2, [r3]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L30:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	CheckStartEndBorder.part.0, .-CheckStartEndBorder.part.0
	.global	__aeabi_uidiv
	.align	2
	.type	FillBorderHchrVy.constprop.13, %function
FillBorderHchrVy.constprop.13:
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
	add	r3, r0, #8192
	str	r1, [fp, #-48]
	cmp	r1, #4096
	ldrb	r1, [r3, #452]
	str	r1, [fp, #-60]
	bhi	.L31
	ldr	r1, .L84
	cmp	r2, #1
	ldr	ip, [r3, #440]
	add	r2, r0, #4096
	ldr	lr, [r3, #444]
	add	r4, r0, #8640
	mov	r3, r2
	ldreqb	r5, [r1, #-4082]
	ldrneb	r5, [r1, #-4083]
	addeq	r4, r4, #12
	str	ip, [fp, #-64]
	addne	r4, r4, #16
	ldr	ip, [r1, #24]
	ldr	r2, [r2, #20]
	sxtb	r5, r5
	ldr	r3, [r3, #24]
	ldr	r8, [r1, #20]
	moveq	r8, ip
	streq	lr, [fp, #-64]
	str	r3, [fp, #-56]
	streq	r2, [fp, #-56]
	cmp	r5, #8
	beq	.L82
	ldr	r3, [fp, #-48]
	sub	r0, r3, #3
	mov	r3, #0
	cmp	r0, #4
	str	r3, [r4]
	bls	.L79
	ldrb	r3, [r8, #4]
	cmp	r3, #1
	beq	.L79
	add	r2, r8, #4
	mov	r9, r0
	mov	r3, #4
	b	.L37
.L38:
	ldrb	r1, [r2, #1]!
	cmp	r1, #1
	beq	.L68
.L37:
	add	r10, r3, #1
	cmp	r10, r0
	mov	r3, r10
	bne	.L38
.L36:
	rsb	lr, r5, r10
	cmp	lr, #4
	ble	.L43
	rsb	r1, r5, lr
	rsb	r7, r5, #0
	add	lr, r8, lr
	mov	r2, #0
	mov	r6, #1
.L42:
	add	r1, r1, r7
	strb	r6, [lr, r2]
	add	ip, r5, r1
	ldr	r3, [r4]
	cmp	ip, #4
	rsb	r2, r5, r2
	add	r3, r3, #1
	str	r3, [r4]
	bgt	.L42
.L43:
	cmp	r0, #0
	mov	r7, r0
	ble	.L80
	ldrb	r2, [r8, r0]
	add	r3, r8, r0
	cmp	r2, #1
	bne	.L46
	b	.L80
.L47:
	ldrb	r2, [r3, #-1]!
	cmp	r2, #1
	beq	.L44
.L46:
	subs	r7, r7, #1
	bne	.L47
.L44:
	add	r3, r7, r5
	cmp	r3, r0
	movcc	r1, #1
	bcs	.L52
.L51:
	strb	r1, [r8, r3]
	add	r3, r3, r5
	ldr	r2, [r4]
	cmp	r3, r0
	add	r2, r2, #1
	str	r2, [r4]
	bcc	.L51
.L52:
	cmp	r7, r10
	bcc	.L50
	mov	r3, r10
	mov	r2, #0
	mov	r10, r7
	str	r2, [fp, #-52]
	mov	r7, r3
	mov	r2, #1
	b	.L57
.L55:
	add	r9, r9, #1
	cmp	r10, r9
	mov	r7, r9
	bcc	.L50
.L57:
	ldrb	r6, [r8, r7]
	cmp	r6, #1
	bne	.L55
	ldr	r1, [r4]
	cmp	r5, #0
	cmpne	r3, r7
	add	r1, r1, #1
	str	r1, [r4]
	beq	.L71
	str	r3, [fp, #-72]
	mov	r1, r5
	ldr	r3, [fp, #-52]
	str	r2, [fp, #-68]
	rsb	r0, r3, r7
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-68]
	ldr	r3, [fp, #-72]
	cmp	r0, #1
	bls	.L71
	ldr	r1, [fp, #-52]
	add	ip, r5, r1
.L56:
	add	r6, r6, #1
	strb	r2, [r8, ip]
	cmp	r6, r0
	ldr	r1, [r4]
	add	ip, ip, r5
	add	r1, r1, #1
	str	r1, [r4]
	bne	.L56
.L71:
	add	r9, r9, #1
	str	r7, [fp, #-52]
	cmp	r10, r9
	mov	r7, r9
	bcs	.L57
.L50:
	ldr	r3, [fp, #-48]
	cmp	r3, #4
	bls	.L35
	ldr	r3, [fp, #-48]
	add	r1, r8, #3
	ldr	r2, [fp, #-64]
	mov	ip, #0
	sub	r0, r3, #1
	ldr	lr, [fp, #-60]
	add	r3, r2, #3
	add	r0, r2, r0
	b	.L62
.L58:
	ldrb	r2, [r3]
	sub	r6, r2, #1
	sxtb	r2, r2
	cmp	r2, #0
	strleb	ip, [r3]
	ble	.L60
.L81:
	strb	r6, [r3]
.L60:
	add	r3, r3, #1
	cmp	r3, r0
	beq	.L35
.L62:
	ldrb	r2, [r1, #1]!
	cmp	r2, #1
	bne	.L58
	strb	ip, [r1]
	strb	r2, [r1, #-1]
	ldrb	r2, [r3]
	add	r6, r2, #1
	sxtb	r2, r2
	cmp	r2, lr
	strgeb	lr, [r3]
	bge	.L60
	b	.L81
.L31:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L82:
	mov	r3, r4
	ldr	r2, [fp, #-48]
	mov	r1, r5
	mov	r0, r8
	bl	FillBorder_Size8
.L35:
	ldr	r3, [fp, #-48]
	cmp	r3, #4096
	ble	.L83
.L63:
	ldr	r2, [fp, #-48]
	mov	r1, r8
	ldr	r0, [fp, #-56]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	pq_alg_memcpy
.L83:
	mov	r3, r4
	mov	r1, r5
	mov	r2, r8
	ldr	r0, [fp, #-48]
	bl	CheckStartEndBorder.part.0
	b	.L63
.L68:
	mov	r9, r10
	b	.L36
.L80:
	mov	r7, r0
	b	.L44
.L79:
	mov	r9, #4
	mov	r10, r9
	b	.L36
.L85:
	.align	2
.L84:
	.word	.LANCHOR0+20480
	UNWIND(.fnend)
	.size	FillBorderHchrVy.constprop.13, .-FillBorderHchrVy.constprop.13
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
	UNWIND(.pad #60)
	sub	sp, sp, #60
	mov	r7, r2
	mov	r9, r0
	movw	r2, #20508
	ldr	r0, .L298
	mov	r4, r1
	mov	r1, #0
	ldr	r8, .L298+4
	bl	pq_alg_memset
	mov	r1, r7
	mov	r0, r9
	movw	r2, #8808
	bl	pq_alg_memcpy
	ldr	r2, [r7, #48]
	ldr	r0, .L298
	add	r3, r2, #1
	strb	r2, [r8, #12]
	ldr	r2, [r7, #64]
	uxtb	r3, r3
	cmp	r3, #64
	strb	r2, [r8, #13]
	add	r2, r2, #1
	ldr	r3, [r7, #56]
	uxtb	r2, r2
	strb	r3, [r8, #14]
	add	r3, r3, #1
	ldr	r1, [r7, #44]
	uxtb	r3, r3
	str	r1, [r8]
	ldr	r1, [r7, #60]
	str	r1, [r8, #4]
	ldr	r1, [r7, #52]
	str	r1, [r8, #8]
	mvnhi	r1, #0
	strhib	r1, [r8, #12]
	cmp	r2, #64
	mov	r1, #0
	mvnhi	r2, #0
	strhib	r2, [r8, #13]
	cmp	r3, #64
	mov	r2, #16384
	mvnhi	r3, #0
	strhib	r3, [r8, #14]
	bl	pq_alg_memset
	ldr	r2, .L298+8
	add	r1, r7, #576
	add	ip, r2, #16384
.L90:
	ldr	r3, [r1, #4]!
	ubfx	r0, r3, #0, #11
	ubfx	r3, r3, #16, #11
	str	r0, [r2, #-4]
	str	r3, [r2], #8
	cmp	r2, ip
	bne	.L90
	mov	r2, #4096
	mov	r1, #0
	ldr	r0, .L298+12
	movw	r5, #4097
	ldr	r6, .L298
	bl	pq_alg_memset
	add	ip, r7, #64
	mov	lr, #1
.L91:
	add	r3, lr, #16384
	ldr	r2, [ip, #4]!
	add	r3, r3, #14
	mov	r1, lr
	and	r2, r2, #1
	mov	r0, #1
	strb	r2, [r6, r3]
	b	.L93
.L277:
	mov	r2, r2, lsr r0
	add	r0, r0, #1
	cmp	r0, #32
	and	r2, r2, #1
	add	r1, r1, #1
	strb	r2, [r3]
	beq	.L276
.L93:
	add	r3, r6, r1
	cmp	r1, #4096
	add	r3, r3, #16384
	ldr	r2, [ip]
	add	r3, r3, #15
	bcc	.L277
.L92:
	ldr	r0, .L298+16
	ldr	r1, .L298+12
	add	r2, r1, #1920
	add	r3, r1, #2880
	str	r1, [r0, #16]
	str	r2, [r0, #20]
	str	r3, [r0, #24]
	ldr	r3, [r7]
	ldr	r2, [r7, #8]
	cmp	r3, #4096
	ldr	r1, [r7, #4]
	str	r3, [fp, #-48]
	movle	r0, #0
	movgt	r0, #1
	cmp	r2, #4096
	movle	r3, r0
	orrgt	r3, r0, #1
	cmp	r1, #2160
	orrgt	r3, r3, #1
	cmp	r3, #0
	addne	r5, r4, #8192
	bne	.L96
	ldr	r3, [fp, #-48]
	sub	ip, r3, #4
	movw	r3, #3836
	cmp	ip, r3
	bls	.L278
.L97:
	mov	r3, #0
	str	r3, [r7, #28]
.L98:
	ldr	ip, [fp, #-48]
	movw	r3, #1080
	cmp	ip, #1920
	cmple	r1, r3
	movgt	r3, #0
	strgt	r3, [r7, #36]
	strgt	r3, [r7, #40]
	cmp	r2, #960
	movgt	r3, #0
	strgt	r3, [r7, #36]
	ldr	r3, [r7, #32]
	cmp	r3, #1
	beq	.L279
.L101:
	add	r5, r4, #8192
	mvn	r3, #0
	strb	r3, [r4]
.L116:
	ldr	r3, [r7, #36]
	cmp	r3, #1
	beq	.L280
.L162:
	mvn	r3, #0
	strb	r3, [r4, #1]
.L177:
	ldr	r3, [r7, #40]
	cmp	r3, #1
	beq	.L281
.L187:
	mvn	r3, #0
	strb	r3, [r4, #2]
.L96:
	ldr	r3, [r4, #4]
	mov	r0, #0
	str	r3, [r9, #44]
	ldrsb	r3, [r4]
	str	r3, [r9, #48]
	ldr	r3, [r4, #8]
	str	r3, [r9, #52]
	ldrsb	r3, [r4, #2]
	str	r3, [r9, #56]
	ldr	r3, [r4, #12]
	str	r3, [r9, #60]
	ldrsb	r3, [r4, #1]
	str	r3, [r9, #64]
	ldr	r3, [r5, #456]
	str	r3, [r9, #16]
	ldr	r3, [r5, #460]
	str	r3, [r9, #20]
	ldr	r3, [r5, #464]
	str	r3, [r9, #24]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L276:
	add	lr, lr, #32
	cmp	lr, r5
	bne	.L91
	b	.L92
.L278:
	sub	r3, r1, #1
	cmp	r3, #2160
	bcc	.L98
	b	.L97
.L279:
	ldr	r3, [r7, #28]
	cmp	r3, #1
	bne	.L101
	cmp	r0, #0
	beq	.L282
	ldr	r3, [r7, #36]
	add	r5, r4, #8192
	cmp	r3, #1
	bne	.L162
	str	r2, [fp, #-48]
.L211:
	ldr	r3, [fp, #-48]
	cmp	r3, #4096
	ble	.L283
	ldr	r3, [r7, #40]
	cmp	r3, #1
	bne	.L187
.L212:
	ldr	r6, [r7, #4]
	cmp	r6, #2160
	bgt	.L96
	add	r10, r4, #4096
	ldr	r1, [r8, #8]
	ldr	r3, .L298+4
	ldrb	r2, [r10, #32]
	cmp	r1, r2
	bcc	.L189
	ldrb	r1, [r3, #14]
	add	r3, r1, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L190
.L191:
	ldrb	r0, [r10, #28]
	add	r2, r4, #4224
	add	r2, r2, #52
	sub	r3, r0, #1
	uxtb	r3, r3
	sxtb	ip, r3
	cmp	ip, #0
	ble	.L192
.L193:
	sxtb	ip, r3
	sub	r3, r3, #1
	ands	r3, r3, #255
	sxth	ip, ip
	mov	r0, ip, asl #3
	sub	r1, r0, #8
	add	r0, r2, r0
	add	lr, r2, r1
	ldrb	r1, [r2, r1]
	strb	r1, [r2, ip, asl #3]
	ldr	r1, [lr, #4]
	str	r1, [r0, #4]
	bne	.L193
	ldrb	r1, [r8, #14]
	ldrb	r0, [r10, #28]
.L192:
	ldr	r3, [r10, #44]
	strb	r1, [r10, #180]
	cmp	r3, r0
	ldr	r1, [r8, #8]
	addcc	r3, r3, #1
	strcc	r3, [r10, #44]
	cmp	r0, r3
	str	r1, [r10, #184]
	beq	.L195
	ldrb	r3, [r4, #2]
	ldrb	r2, [r8, #14]
.L196:
	cmp	r2, r3
	bne	.L284
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L285
	mov	r2, #1
	mov	r1, r6
	mov	r0, r4
	bl	FillBorderHchrVy.constprop.13
	ldrsb	r3, [r4, #2]
	cmp	r3, #8
	beq	.L204
	ldrb	r3, [r5, #450]
	ldrb	r2, [r5, #451]
	cmp	r2, r3
	addhi	r3, r3, #1
	strhib	r3, [r5, #450]
	bhi	.L204
	sub	r2, r6, #5
	movw	r3, #4091
	cmp	r2, r3
	bhi	.L204
	mov	r3, #5
	str	r4, [fp, #-48]
.L210:
	ldr	r0, [r10, #20]
	sub	r2, r3, #1
	ldrb	r4, [r0, r2]
	cmp	r4, #1
	beq	.L286
.L228:
	mov	r7, r3
.L207:
	cmp	r6, r7
	add	r3, r3, #1
	bhi	.L210
	ldr	r4, [fp, #-48]
.L204:
	ldr	r3, [r8, #8]
	str	r3, [r4, #8]
	b	.L96
.L281:
	ldr	r3, [r7, #28]
	cmp	r3, #1
	bne	.L187
	b	.L212
.L280:
	ldr	r3, [r7, #28]
	cmp	r3, #1
	ldreq	r3, [r7, #8]
	streq	r3, [fp, #-48]
	bne	.L162
	b	.L211
.L283:
	add	r10, r4, #4096
	ldr	r1, [r8, #4]
	ldr	r3, .L298+4
	ldrb	r2, [r10, #31]
	cmp	r1, r2
	bcc	.L164
	ldrb	r1, [r3, #13]
	add	r3, r1, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L165
.L166:
	ldrb	r0, [r10, #28]
	add	r2, r4, #4352
	add	r2, r2, #52
	sub	r3, r0, #1
	uxtb	r3, r3
	sxtb	ip, r3
	cmp	ip, #0
	ble	.L167
.L168:
	sxtb	ip, r3
	sub	r3, r3, #1
	ands	r3, r3, #255
	sxth	ip, ip
	mov	r0, ip, asl #3
	sub	r1, r0, #8
	add	r0, r2, r0
	add	lr, r2, r1
	ldrb	r1, [r2, r1]
	strb	r1, [r2, ip, asl #3]
	ldr	r1, [lr, #4]
	str	r1, [r0, #4]
	bne	.L168
	ldrb	r1, [r8, #13]
	ldrb	r0, [r10, #28]
.L167:
	ldr	r3, [r10, #40]
	strb	r1, [r10, #308]
	cmp	r3, r0
	ldr	r1, [r8, #4]
	addcc	r3, r3, #1
	strcc	r3, [r10, #40]
	cmp	r0, r3
	str	r1, [r10, #312]
	beq	.L170
	ldrb	r3, [r4, #1]
	ldrb	r2, [r8, #13]
.L171:
	cmp	r2, r3
	bne	.L287
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L288
	mov	r2, #2
	ldr	r1, [fp, #-48]
	mov	r0, r4
	bl	FillBorderHchrVy.constprop.13
	ldrsb	r3, [r4, #1]
	cmp	r3, #8
	beq	.L180
	ldrb	r3, [r5, #449]
	ldrb	r2, [r5, #451]
	cmp	r2, r3
	addhi	r3, r3, #1
	strhib	r3, [r5, #449]
	bhi	.L180
	ldr	r3, [fp, #-48]
	sub	r2, r3, #5
	movw	r3, #4091
	cmp	r2, r3
	bhi	.L180
	mov	r3, #5
	str	r4, [fp, #-52]
	b	.L186
.L224:
	mov	r6, r3
.L183:
	ldr	r2, [fp, #-48]
	add	r3, r3, #1
	cmp	r2, r6
	bls	.L289
.L186:
	ldr	r0, [r10, #24]
	sub	r2, r3, #1
	ldrb	r6, [r0, r2]
	cmp	r6, #1
	bne	.L224
	ldr	r1, [r5, #440]
	ldrb	lr, [r5, #451]
	ldrsb	ip, [r1, r2]
	cmp	ip, lr
	bge	.L224
	sub	r4, r3, #2
	ldrsb	ip, [r1, r4]
	ldrsb	r1, [r1, r3]
	cmp	lr, ip
	bgt	.L225
	cmp	ip, r1
	blt	.L225
	strb	r6, [r0, r4]
	mov	r0, #0
	ldr	r1, [r10, #24]
	mov	r6, r3
	strb	r0, [r1, r2]
	b	.L183
.L282:
	add	r10, r4, #4096
	ldr	r1, [r8]
	ldr	r3, .L298+4
	ldrb	r2, [r10, #30]
	cmp	r1, r2
	bcc	.L103
	ldrb	r0, [r3, #12]
	add	r3, r0, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L104
.L105:
	ldrb	r1, [r10, #28]
	add	r3, r4, #4096
	add	r3, r3, #52
	sub	r2, r1, #1
	uxtb	r2, r2
	sxtb	ip, r2
	cmp	ip, #0
	ble	.L106
.L107:
	sxtb	ip, r2
	sub	r2, r2, #1
	ands	r2, r2, #255
	sxth	ip, ip
	mov	r0, ip, asl #3
	sub	r1, r0, #8
	add	r0, r3, r0
	add	lr, r3, r1
	ldrb	r1, [r3, r1]
	strb	r1, [r3, ip, asl #3]
	ldr	r1, [lr, #4]
	str	r1, [r0, #4]
	bne	.L107
	ldrb	r0, [r8, #12]
	ldrb	r1, [r10, #28]
.L106:
	ldr	r2, [r10, #36]
	strb	r0, [r10, #52]
	cmp	r2, r1
	ldr	r0, [r8]
	addcc	r2, r2, #1
	strcc	r2, [r10, #36]
	cmp	r1, r2
	str	r0, [r10, #56]
	beq	.L109
	ldrb	r3, [r4]
	ldrb	r2, [r8, #12]
.L110:
	cmp	r2, r3
	sxtb	r2, r3
	str	r2, [fp, #-52]
	bne	.L290
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L291
	ldr	r3, [fp, #-48]
	add	r5, r4, #8192
	cmp	r3, #4096
	add	r3, r4, #8640
	mov	r2, r3
	ldr	r3, .L298+16
	add	r2, r2, #8
	str	r2, [fp, #-72]
	ldr	r3, [r3, #16]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [r5, #456]
	ldrb	r3, [r5, #452]
	str	r3, [fp, #-76]
	bhi	.L118
	ldr	r3, [fp, #-52]
	cmp	r3, #8
	beq	.L292
	ldr	r3, [fp, #-48]
	sub	ip, r3, #3
	ldr	r3, [r5, #436]
	cmp	ip, #4
	str	r3, [fp, #-80]
	bls	.L215
	ldr	r2, [fp, #-56]
	ldrb	r3, [r2, #4]
	cmp	r3, #1
	beq	.L215
	add	r3, r2, #4
	mov	r2, #4
	b	.L122
.L123:
	ldrb	r1, [r3, #1]!
	cmp	r1, #1
	beq	.L272
.L122:
	add	r2, r2, #1
	str	r2, [fp, #-60]
	cmp	r2, ip
	bne	.L123
.L272:
	str	r2, [fp, #-64]
.L121:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-52]
	rsb	r3, r2, r3
	cmp	r3, #4
	strgt	ip, [fp, #-68]
	ble	.L130
.L129:
	sub	r2, r3, #-1073741823
	mov	r1, #0
	mov	ip, r1
	mov	r0, r1
	add	r2, r6, r2, lsl #2
.L128:
	ldr	lr, [r2], #4
	cmp	lr, ip
	movhi	r1, r0
	add	r0, r0, #1
	movhi	ip, lr
	cmp	r0, #3
	bne	.L128
	sub	r3, r3, #1
	ldr	r2, [fp, #-56]
	add	r1, r3, r1
	ldr	r3, [fp, #-52]
	mov	r0, #1
	rsb	r3, r3, r1
	strb	r0, [r2, r1]
	cmp	r3, #4
	ldr	r2, [r5, #456]
	add	r2, r2, #1
	str	r2, [r5, #456]
	bgt	.L129
	ldr	ip, [fp, #-68]
.L130:
	cmp	ip, #0
	mov	r3, ip
	ble	.L273
	ldr	r2, [fp, #-56]
	ldrb	r1, [r2, ip]
	add	r2, r2, ip
	cmp	r1, #1
	bne	.L133
	b	.L273
.L134:
	ldrb	r1, [r2, #-1]!
	cmp	r1, #1
	beq	.L216
.L133:
	subs	r3, r3, #1
	bne	.L134
.L216:
	str	r3, [fp, #-68]
.L131:
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-52]
	add	r3, r3, r2
	cmp	r3, ip
	strcc	r9, [fp, #-84]
	bcs	.L141
.L140:
	sub	r2, r3, #-1073741823
	mov	r1, #0
	mov	lr, r1
	mov	r0, r1
	add	r2, r6, r2, lsl #2
.L139:
	ldr	r9, [r2], #4
	cmp	r9, lr
	movhi	r1, r0
	add	r0, r0, #1
	movhi	lr, r9
	cmp	r0, #3
	bne	.L139
	sub	r3, r3, #1
	ldr	r2, [fp, #-56]
	add	r1, r3, r1
	ldr	r3, [fp, #-52]
	mov	r0, #1
	add	r3, r1, r3
	strb	r0, [r2, r1]
	cmp	r3, ip
	ldr	r2, [r5, #456]
	add	r2, r2, #1
	str	r2, [r5, #456]
	bcc	.L140
	ldr	r9, [fp, #-84]
.L141:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-68]
	cmp	r3, r2
	bhi	.L137
	ldr	r3, [fp, #-60]
	mov	r2, #0
	str	r9, [fp, #-84]
	mov	r9, r2
	str	r4, [fp, #-88]
	str	r7, [fp, #-92]
	mov	r4, r3
	b	.L148
.L144:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-64]
	cmp	r3, r2
	bhi	.L293
	mov	r9, r4
	ldr	r4, [fp, #-64]
.L148:
	ldr	r3, [fp, #-56]
	ldrb	r3, [r3, r4]
	cmp	r3, #1
	movne	r4, r9
	bne	.L144
	ldr	r2, [fp, #-60]
	str	r3, [fp, #-96]
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	cmpne	r2, r4
	ldr	r2, [r5, #456]
	add	r2, r2, #1
	str	r2, [r5, #456]
	beq	.L144
	mov	r1, r3
	rsb	r0, r9, r4
	bl	__aeabi_uidiv
	cmp	r0, #1
	mov	r7, r0
	bls	.L144
	ldr	r3, [fp, #-96]
	mov	r1, r3
.L147:
	ldr	r3, [fp, #-52]
	add	r3, r9, r3
	mov	r9, #0
	sub	r2, r3, #-1073741823
	mov	ip, r9
	mov	r0, r9
	add	r2, r6, r2, lsl #2
.L146:
	ldr	lr, [r2], #4
	cmp	lr, ip
	movhi	r9, r0
	add	r0, r0, #1
	movhi	ip, lr
	cmp	r0, #3
	bne	.L146
	sub	r3, r3, #1
	add	r1, r1, #1
	add	r9, r3, r9
	ldr	r3, [fp, #-56]
	mov	r2, #1
	cmp	r1, r7
	strb	r2, [r3, r9]
	ldr	r3, [r5, #456]
	add	r3, r3, #1
	str	r3, [r5, #456]
	bne	.L147
	b	.L144
.L164:
	mov	r1, #255
	mvn	r2, #0
	strb	r2, [r3, #13]
.L165:
	mov	r3, #100
	str	r3, [r8, #4]
	b	.L166
.L289:
	ldr	r4, [fp, #-52]
.L180:
	ldr	r3, [r8, #4]
	str	r3, [r4, #12]
	b	.L177
.L288:
	ldr	r0, [r10, #24]
	mov	r1, #0
	ldr	r10, [fp, #-48]
	mov	r6, r1
	mov	r2, r10
	bl	pq_alg_memset
	str	r6, [r4, #12]
	mvn	r3, #0
	mov	r2, r10
	strb	r3, [r4, #1]
	mov	r1, r6
	ldr	r0, [r5, #440]
	bl	pq_alg_memset
	strb	r6, [r5, #449]
	str	r6, [r5, #464]
	b	.L177
.L225:
	cmp	lr, r1
	cmple	ip, r1
	mov	r6, r3
	bge	.L183
	mov	r1, #1
	strb	r1, [r0, r3]
	ldr	r1, [r10, #24]
	mov	r0, #0
	strb	r0, [r1, r2]
	b	.L183
.L287:
	ldr	r2, [fp, #-48]
	mov	r1, #0
	ldr	r0, [r5, #440]
	bl	pq_alg_memset
	mov	r3, #0
	strb	r3, [r5, #449]
	b	.L177
.L170:
	cmp	r0, #1
	ldrb	r3, [r8, #13]
	ble	.L222
	mov	r1, #1
	sxtb	ip, r3
	mov	lr, r9
	str	ip, [fp, #-60]
	mov	r9, r3
	mov	ip, r1
	b	.L174
.L173:
	ldr	r3, [fp, #-56]
	add	r2, r2, #8
	cmp	r3, r0
	bge	.L294
.L174:
	ldrsb	r3, [r2, #8]
	add	r1, r1, #1
	ldr	r6, [fp, #-60]
	uxtb	r1, r1
	cmp	r3, r6
	sxtb	r3, r1
	str	r3, [fp, #-56]
	bne	.L173
	add	r3, ip, #1
	ldrb	r6, [r10, #50]
	str	r3, [fp, #-52]
	ldr	r3, [r2, #12]
	cmp	r3, r6
	ldrcsb	ip, [fp, #-52]
	b	.L173
.L294:
	mov	r3, r9
	mov	r9, lr
.L172:
	ldrb	r2, [r10, #48]
	cmp	r2, ip
	strlsb	r3, [r4, #1]
	movhi	r2, r3
	ldrlsb	r2, [r8, #13]
	ldrhib	r3, [r4, #1]
	b	.L171
.L286:
	ldr	r1, [r5, #444]
	ldrb	lr, [r5, #451]
	ldrsb	ip, [r1, r2]
	cmp	ip, lr
	bge	.L228
	sub	r7, r3, #2
	ldrsb	ip, [r1, r7]
	ldrsb	r1, [r1, r3]
	cmp	lr, ip
	bgt	.L229
	cmp	ip, r1
	blt	.L229
	strb	r4, [r0, r7]
	mov	r0, #0
	ldr	r1, [r10, #20]
	mov	r7, r3
	strb	r0, [r1, r2]
	b	.L207
.L285:
	mov	r1, #0
	ldr	r0, [r10, #20]
	mov	r7, r1
	mov	r2, r6
	bl	pq_alg_memset
	str	r7, [r4, #8]
	mvn	r3, #0
	mov	r2, r6
	strb	r3, [r4, #2]
	mov	r1, r7
	ldr	r0, [r5, #444]
	bl	pq_alg_memset
	strb	r7, [r5, #450]
	str	r7, [r5, #460]
	b	.L96
.L229:
	cmp	lr, r1
	cmple	ip, r1
	mov	r7, r3
	bge	.L207
	mov	r1, #1
	strb	r1, [r0, r3]
	ldr	r1, [r10, #20]
	mov	r0, #0
	strb	r0, [r1, r2]
	b	.L207
.L284:
	mov	r2, r6
	mov	r1, #0
	ldr	r0, [r5, #444]
	bl	pq_alg_memset
	mov	r3, #0
	strb	r3, [r5, #450]
	b	.L96
.L195:
	cmp	r0, #1
	ldrb	r3, [r8, #14]
	ble	.L226
	mov	r1, #1
	mov	r7, r9
	sxtb	lr, r3
	mov	r9, r6
	mov	ip, r1
	str	r0, [fp, #-56]
	mov	r6, r3
	b	.L199
.L198:
	ldr	r3, [fp, #-56]
	add	r2, r2, #8
	ldr	r0, [fp, #-52]
	cmp	r3, r0
	ble	.L295
.L199:
	ldrsb	r3, [r2, #8]
	add	r1, r1, #1
	cmp	r3, lr
	uxtb	r1, r1
	sxtb	r3, r1
	str	r3, [fp, #-52]
	bne	.L198
	add	r0, ip, #1
	ldrb	r3, [r10, #51]
	str	r0, [fp, #-48]
	ldr	r0, [r2, #12]
	cmp	r0, r3
	ldrcsb	ip, [fp, #-48]
	b	.L198
.L295:
	mov	r3, r6
	mov	r6, r9
	mov	r9, r7
.L197:
	ldrb	r2, [r10, #48]
	cmp	r2, ip
	strlsb	r3, [r4, #2]
	movhi	r2, r3
	ldrlsb	r2, [r8, #14]
	ldrhib	r3, [r4, #2]
	b	.L196
.L215:
	mov	r3, #4
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	b	.L121
.L292:
	sub	r0, fp, #56
	mov	r3, r2
	ldmia	r0, {r0, r1, r2}
	bl	FillBorder_Size8
.L120:
	ldr	r6, [fp, #-48]
	ldr	r3, [fp, #-72]
	ldr	r2, [fp, #-56]
	ldr	r1, [fp, #-52]
	mov	r0, r6
	bl	CheckStartEndBorder.part.0
	ldr	r3, .L298+16
	mov	r2, r6
	ldr	r0, [r10, #16]
	ldr	r1, [r3, #16]
	bl	pq_alg_memcpy
	ldrsb	r3, [r4]
	str	r3, [fp, #-52]
.L118:
	ldr	r3, [fp, #-52]
	cmp	r3, #8
	beq	.L155
	ldrb	r3, [r5, #448]
	ldrb	r2, [r5, #451]
	cmp	r2, r3
	addhi	r3, r3, #1
	strhib	r3, [r5, #448]
	bhi	.L155
	ldr	r3, [fp, #-48]
	sub	r2, r3, #5
	movw	r3, #4091
	cmp	r2, r3
	bhi	.L155
	mov	r3, #5
	str	r4, [fp, #-52]
	b	.L161
.L220:
	mov	r6, r3
.L158:
	ldr	r2, [fp, #-48]
	add	r3, r3, #1
	cmp	r2, r6
	bls	.L296
.L161:
	ldr	r0, [r10, #16]
	sub	r2, r3, #1
	ldrb	r6, [r0, r2]
	cmp	r6, #1
	bne	.L220
	ldr	r1, [r5, #436]
	ldrb	lr, [r5, #451]
	ldrsb	ip, [r1, r2]
	cmp	ip, lr
	bge	.L220
	sub	r4, r3, #2
	ldrsb	ip, [r1, r4]
	ldrsb	r1, [r1, r3]
	cmp	lr, ip
	bgt	.L221
	cmp	ip, r1
	blt	.L221
	strb	r6, [r0, r4]
	mov	r0, #0
	ldr	r1, [r10, #16]
	mov	r6, r3
	strb	r0, [r1, r2]
	b	.L158
.L291:
	ldr	r0, [r10, #16]
	add	r5, r4, #8192
	ldr	r10, [fp, #-48]
	mov	r1, #0
	mov	r6, r1
	mov	r2, r10
	bl	pq_alg_memset
	str	r6, [r4, #4]
	mvn	r3, #0
	mov	r2, r10
	strb	r3, [r4]
	mov	r1, r6
	ldr	r0, [r5, #436]
	bl	pq_alg_memset
	strb	r6, [r5, #448]
	str	r6, [r5, #456]
	b	.L116
.L296:
	ldr	r4, [fp, #-52]
.L155:
	ldr	r3, [r8]
	str	r3, [r4, #4]
	b	.L116
.L290:
	add	r5, r4, #8192
	ldr	r2, [fp, #-48]
	mov	r1, #0
	ldr	r0, [r5, #436]
	bl	pq_alg_memset
	mov	r3, #0
	strb	r3, [r5, #448]
	b	.L116
.L273:
	str	ip, [fp, #-68]
	b	.L131
.L221:
	cmp	lr, r1
	cmple	ip, r1
	mov	r6, r3
	bge	.L158
	mov	r1, #1
	strb	r1, [r0, r3]
	ldr	r1, [r10, #16]
	mov	r0, #0
	strb	r0, [r1, r2]
	b	.L158
.L109:
	cmp	r1, #1
	ldrb	lr, [r8, #12]
	ble	.L213
	mov	r2, #1
	str	r1, [fp, #-60]
	mov	r1, r9
	sxtb	r0, lr
	mov	r9, lr
	str	r0, [fp, #-56]
	mov	lr, r1
	mov	r0, r2
	b	.L113
.L112:
	ldr	r1, [fp, #-60]
	add	r3, r3, #8
	cmp	ip, r1
	bge	.L297
.L113:
	ldrsb	ip, [r3, #8]
	add	r2, r2, #1
	ldr	r5, [fp, #-56]
	uxtb	r2, r2
	cmp	ip, r5
	sxtb	ip, r2
	bne	.L112
	add	r1, r0, #1
	ldrb	r5, [r10, #49]
	str	r1, [fp, #-52]
	ldr	r1, [r3, #12]
	cmp	r1, r5
	ldrcsb	r0, [fp, #-52]
	b	.L112
.L293:
	ldr	r9, [fp, #-84]
	ldr	r4, [fp, #-88]
	ldr	r7, [fp, #-92]
.L137:
	ldr	r3, [fp, #-48]
	cmp	r3, #4
	bls	.L120
	ldr	r3, [fp, #-48]
	mov	r0, #0
	ldr	r2, [fp, #-80]
	sub	lr, r3, #1
	ldr	ip, [fp, #-76]
	add	r3, r2, #3
	add	lr, r2, lr
	ldr	r2, [fp, #-56]
	add	r2, r2, #3
	b	.L153
.L149:
	ldrb	r1, [r3]
	sub	r6, r1, #1
	sxtb	r1, r1
	cmp	r1, #0
	strleb	r0, [r3]
	ble	.L151
.L274:
	strb	r6, [r3]
.L151:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L120
.L153:
	ldrb	r1, [r2, #1]!
	cmp	r1, #1
	bne	.L149
	strb	r0, [r2]
	strb	r1, [r2, #-1]
	ldrb	r1, [r3]
	add	r6, r1, #1
	sxtb	r1, r1
	cmp	r1, ip
	strgeb	ip, [r3]
	bge	.L151
	b	.L274
.L297:
	mov	r3, lr
	mov	lr, r9
	mov	r9, r3
.L111:
	ldrb	r3, [r10, #48]
	cmp	r3, r0
	strlsb	lr, [r4]
	movhi	r2, lr
	ldrhib	r3, [r4]
	movls	r3, lr
	ldrlsb	r2, [r8, #12]
	b	.L110
.L213:
	mov	r0, #1
	b	.L111
.L189:
	mov	r1, #255
	mvn	r2, #0
	strb	r2, [r3, #14]
.L190:
	mov	r3, #100
	str	r3, [r8, #8]
	b	.L191
.L222:
	mov	ip, #1
	b	.L172
.L103:
	mov	r0, #255
	mvn	r2, #0
	strb	r2, [r3, #12]
.L104:
	mov	r3, #100
	str	r3, [r8]
	b	.L105
.L226:
	mov	ip, #1
	b	.L197
.L299:
	.align	2
.L298:
	.word	.LANCHOR0
	.word	.LANCHOR0+16384
	.word	.LANCHOR0+4
	.word	.LANCHOR0+16399
	.word	.LANCHOR0+20480
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_GetDbDetInfo, .-PQ_MNG_ALG_GetDbDetInfo
	.global	__aeabi_idiv
	.align	2
	.global	PQ_MNG_ALG_DBCfgDetector
	.type	PQ_MNG_ALG_DBCfgDetector, %function
PQ_MNG_ALG_DBCfgDetector:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r8, [r1]
	mov	r6, r1
	ldr	r9, [r1, #4]
	mov	r5, r0
	mov	r4, r2
	cmp	r8, #4096
	cmple	r9, #2160
	bgt	.L323
	str	r8, [r0, #668]
	ldr	r3, [r1, #4]
	str	r3, [r0, #672]
	ldr	r1, [r1]
	ldr	r2, [r6, #8]
	ldr	r7, [r6, #4]
	cmp	r1, #4096
	cmple	r2, #4096
	movgt	r3, #1
	movle	r3, #0
	cmp	r7, #2160
	orrgt	r3, r3, #1
	cmp	r3, #0
	bne	.L303
	ldr	r3, [r6, #48]
	cmp	r3, #8
	movne	r3, #90
	strneh	r3, [r0, #24]
	beq	.L331
.L305:
	ldr	r3, [r6, #64]
	cmp	r3, #8
	movne	r3, #60
	strneh	r3, [r5, #26]
	beq	.L332
.L307:
	ldr	r1, [r6, #56]
	add	r3, r1, #1
	cmp	r3, #1
	bls	.L303
	mov	r0, r7
	bl	__aeabi_idiv
	cmp	r7, #0
	add	r2, r7, #7
	add	r3, r7, #63
	movge	r2, r7
	mov	r2, r2, asr #3
	uxth	r0, r0
	cmp	r0, r2
	movge	r0, r2
	cmp	r7, #0
	movlt	r7, r3
	mov	r3, r7, asr #6
	cmp	r0, r3
	movlt	r0, r3
	strh	r0, [r5, #28]
.L303:
	movw	r3, #1080
	cmp	r8, #1920
	cmple	r9, r3
	mov	r2, #0
	mov	r3, #1
	strh	r2, [r5, #20]
	strh	r3, [r5, #22]
	strh	r3, [r5, #16]
	strh	r3, [r5, #18]
	movle	r3, #6
	movgt	r3, #8
	strgth	r2, [r5, #22]
	strh	r3, [r5, #30]
	ldmia	r6, {r0, r1, r2}
	cmp	r0, #4096
	cmple	r2, #4096
	movgt	r3, #1
	movle	r3, #0
	cmp	r1, #2160
	orrgt	r3, r3, #1
	cmp	r3, #0
	bne	.L311
	cmp	r0, #720
	movle	r3, #16
	strleh	r3, [r5, #32]
	ble	.L313
	cmp	r0, #1920
	movle	r3, #42
	movgt	r3, #63
	strh	r3, [r5, #32]
.L313:
	cmp	r1, #576
	movle	r3, #16
	strleh	r3, [r5, #36]
	bgt	.L333
.L316:
	cmp	r2, #360
	movle	r3, #16
	strleh	r3, [r5, #34]
	ble	.L311
	cmp	r2, #960
	movle	r3, #42
	movgt	r3, #63
	strh	r3, [r5, #34]
.L311:
	mov	r2, #512
	mov	r1, #0
	add	r0, r5, #40
	add	r4, r4, #16
	bl	pq_alg_memset
	add	ip, r5, #36
	mov	lr, #0
.L320:
	mov	r0, r4
	ldr	r2, [ip, #4]!
	ldrb	r1, [r0, lr]!
	mov	r3, #1
	and	r1, r1, r3
	orr	r1, r1, r2
	str	r1, [ip]
	b	.L321
.L335:
	ldrb	r2, [r0, #1]!
	and	r2, r2, #1
	orr	r1, r1, r2, asl r3
	add	r3, r3, #1
	cmp	r3, #32
	str	r1, [ip]
	beq	.L334
.L321:
	add	r2, r3, lr
	cmp	r2, #4096
	bcc	.L335
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L334:
	add	lr, lr, #32
	cmp	lr, #4096
	bne	.L320
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L333:
	movw	r3, #1080
	cmp	r1, r3
	movle	r3, #36
	movgt	r3, #63
	strh	r3, [r5, #36]
	b	.L316
.L331:
	add	r3, r1, #7
	cmp	r1, #0
	movlt	r1, r3
	mov	r3, r1, asr #3
	strh	r3, [r0, #24]
	b	.L305
.L332:
	add	r3, r2, #7
	cmp	r2, #0
	movlt	r2, r3
	mov	r3, r2, asr #3
	strh	r3, [r5, #26]
	b	.L307
.L323:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_DBCfgDetector, .-PQ_MNG_ALG_DBCfgDetector
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	stDetStaticInfo, %object
	.size	stDetStaticInfo, 20508
stDetStaticInfo:
	.space	20508
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
