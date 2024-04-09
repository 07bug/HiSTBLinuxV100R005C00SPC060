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
	mov	r4, r2
	mov	r5, r0
	str	r0, [fp, #-48]
	movw	r2, #20508
	ldr	r0, .L298
	mov	r6, r1
	mov	r1, #0
	bl	pq_alg_memset
	mov	r1, r4
	mov	r0, r5
	movw	r2, #8808
	bl	pq_alg_memcpy
	ldr	r9, .L298+4
	ldr	r2, [r4, #48]
	ldr	r0, .L298
	add	r3, r2, #1
	strb	r2, [r9, #12]
	ldr	r2, [r4, #64]
	uxtb	r3, r3
	cmp	r3, #64
	strb	r2, [r9, #13]
	add	r2, r2, #1
	ldr	r3, [r4, #56]
	uxtb	r2, r2
	strb	r3, [r9, #14]
	add	r3, r3, #1
	ldr	r1, [r4, #44]
	uxtb	r3, r3
	str	r1, [r9]
	ldr	r1, [r4, #60]
	str	r1, [r9, #4]
	ldr	r1, [r4, #52]
	str	r1, [r9, #8]
	mvnhi	r1, #0
	strhib	r1, [r9, #12]
	cmp	r2, #64
	mov	r1, #0
	mvnhi	r2, #0
	strhib	r2, [r9, #13]
	cmp	r3, #64
	mov	r2, #16384
	mvnhi	r3, #0
	strhib	r3, [r9, #14]
	bl	pq_alg_memset
	ldr	r2, .L298+8
	add	r1, r4, #576
	add	ip, r2, #15360
.L90:
	ldr	r3, [r1, #4]!
	ubfx	r0, r3, #0, #11
	ubfx	r3, r3, #16, #11
	str	r0, [r2, #-4]
	str	r3, [r2], #8
	cmp	r2, ip
	bne	.L90
	mov	r2, #2048
	mov	r1, #0
	ldr	r0, .L298+12
	mov	r5, #1
	bl	pq_alg_memset
	ldr	lr, .L298
	add	ip, r4, #64
	movw	r7, #2049
.L91:
	cmp	r5, r7
	ldr	r3, [ip, #4]!
	beq	.L92
	add	r2, r5, #16384
	and	r3, r3, #1
	add	r2, r2, #14
	mov	r1, r5
	mov	r0, #1
	strb	r3, [lr, r2]
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
	add	r3, lr, r1
	cmp	r1, #2048
	add	r3, r3, #16384
	ldr	r2, [ip]
	add	r3, r3, #15
	bcc	.L277
.L92:
	ldr	r1, .L298+12
	ldr	r5, .L298+16
	add	r2, r1, #1920
	add	r3, r1, #2880
	str	r1, [r5, #16]
	str	r3, [r5, #24]
	str	r2, [r5, #20]
	ldr	r7, [r4]
	ldr	r10, [r4, #8]
	cmp	r7, #4096
	ldr	r2, [r4, #4]
	movle	r1, #0
	movgt	r1, #1
	cmp	r10, #4096
	movle	r3, r1
	orrgt	r3, r1, #1
	cmp	r2, #2160
	orrgt	r3, r3, #1
	cmp	r3, #0
	addne	r8, r6, #8192
	bne	.L95
	sub	r0, r7, #4
	movw	r3, #3836
	cmp	r0, r3
	bls	.L278
.L96:
	mov	r3, #0
	str	r3, [r4, #28]
.L97:
	movw	r3, #1080
	cmp	r7, #1920
	cmple	r2, r3
	movgt	r3, #0
	strgt	r3, [r4, #36]
	strgt	r3, [r4, #40]
	cmp	r10, #960
	movgt	r3, #0
	strgt	r3, [r4, #36]
	ldr	r3, [r4, #32]
	cmp	r3, #1
	beq	.L279
.L100:
	add	r8, r6, #8192
	mvn	r3, #0
	strb	r3, [r6]
.L115:
	ldr	r3, [r4, #36]
	cmp	r3, #1
	beq	.L280
.L161:
	mvn	r3, #0
	strb	r3, [r6, #1]
.L176:
	ldr	r3, [r4, #40]
	cmp	r3, #1
	beq	.L281
.L186:
	mvn	r3, #0
	strb	r3, [r6, #2]
.L95:
	ldr	r3, [r6, #4]
	mov	r0, #0
	ldr	r2, [fp, #-48]
	str	r3, [r2, #44]
	ldrsb	r3, [r6]
	str	r3, [r2, #48]
	ldr	r3, [r6, #8]
	str	r3, [r2, #52]
	ldrsb	r3, [r6, #2]
	str	r3, [r2, #56]
	ldr	r3, [r6, #12]
	str	r3, [r2, #60]
	ldrsb	r3, [r6, #1]
	str	r3, [r2, #64]
	ldr	r3, [r8, #456]
	str	r3, [r2, #16]
	ldr	r3, [r8, #460]
	str	r3, [r2, #20]
	ldr	r3, [r8, #464]
	str	r3, [r2, #24]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L276:
	add	r5, r5, #32
	b	.L91
.L278:
	sub	r3, r2, #1
	cmp	r3, #2160
	bcc	.L97
	b	.L96
.L279:
	ldr	r3, [r4, #28]
	cmp	r3, #1
	bne	.L100
	cmp	r1, #0
	beq	.L282
	ldr	r3, [r4, #36]
	add	r8, r6, #8192
	cmp	r3, #1
	bne	.L161
	mov	r7, r10
.L211:
	cmp	r7, #4096
	ble	.L283
	ldr	r3, [r4, #40]
	cmp	r3, #1
	bne	.L186
.L212:
	ldr	r4, [r4, #4]
	cmp	r4, #2160
	bgt	.L95
	add	r10, r6, #4096
	ldr	r1, [r9, #8]
	ldr	r3, .L298+4
	ldrb	r2, [r10, #32]
	cmp	r1, r2
	bcc	.L188
	ldrb	r1, [r3, #14]
	add	r3, r1, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L189
.L190:
	ldrb	r0, [r10, #28]
	add	r2, r6, #4224
	add	r2, r2, #52
	sub	r3, r0, #1
	uxtb	r3, r3
	sxtb	ip, r3
	cmp	ip, #0
	ble	.L191
.L192:
	sxtb	r0, r3
	sub	r3, r3, #1
	ands	r3, r3, #255
	sxth	r0, r0
	mov	r1, r0, asl #3
	sub	ip, r1, #8
	add	r1, r2, r1
	add	lr, r2, ip
	ldrb	ip, [r2, ip]
	strb	ip, [r2, r0, asl #3]
	ldr	r0, [lr, #4]
	str	r0, [r1, #4]
	bne	.L192
	ldrb	r1, [r9, #14]
	ldrb	r0, [r10, #28]
.L191:
	ldr	r3, [r10, #44]
	strb	r1, [r10, #180]
	cmp	r3, r0
	ldr	r1, [r9, #8]
	addcc	r3, r3, #1
	strcc	r3, [r10, #44]
	cmp	r0, r3
	str	r1, [r10, #184]
	beq	.L194
	ldrb	r3, [r6, #2]
	ldrb	r2, [r9, #14]
.L195:
	cmp	r2, r3
	bne	.L284
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L285
	mov	r2, #1
	mov	r1, r4
	mov	r0, r6
	bl	FillBorderHchrVy.constprop.13
	ldrsb	r3, [r6, #2]
	cmp	r3, #8
	beq	.L203
	ldrb	r3, [r8, #450]
	ldrb	r2, [r8, #451]
	cmp	r2, r3
	addhi	r3, r3, #1
	strhib	r3, [r8, #450]
	bhi	.L203
	sub	r2, r4, #5
	movw	r3, #4091
	cmp	r2, r3
	bhi	.L203
	mov	r3, #5
.L209:
	ldr	ip, [r10, #20]
	sub	r1, r3, #1
	ldrb	r7, [ip, r1]
	cmp	r7, #1
	beq	.L286
.L228:
	mov	r2, r3
.L206:
	cmp	r4, r2
	add	r3, r3, #1
	bhi	.L209
.L203:
	ldr	r3, [r9, #8]
	str	r3, [r6, #8]
	b	.L95
.L281:
	ldr	r3, [r4, #28]
	cmp	r3, #1
	bne	.L186
	b	.L212
.L280:
	ldr	r3, [r4, #28]
	cmp	r3, #1
	ldreq	r7, [r4, #8]
	bne	.L161
	b	.L211
.L283:
	add	r10, r6, #4096
	ldr	r1, [r9, #4]
	ldr	r3, .L298+4
	ldrb	r2, [r10, #31]
	cmp	r1, r2
	bcc	.L163
	ldrb	r1, [r3, #13]
	add	r3, r1, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L164
.L165:
	ldrb	r0, [r10, #28]
	add	r2, r6, #4352
	add	r2, r2, #52
	sub	r3, r0, #1
	uxtb	r3, r3
	sxtb	ip, r3
	cmp	ip, #0
	ble	.L166
.L167:
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
	bne	.L167
	ldrb	r1, [r9, #13]
	ldrb	r0, [r10, #28]
.L166:
	ldr	r3, [r10, #40]
	strb	r1, [r10, #308]
	cmp	r3, r0
	ldr	r1, [r9, #4]
	addcc	r3, r3, #1
	strcc	r3, [r10, #40]
	cmp	r0, r3
	str	r1, [r10, #312]
	beq	.L169
	ldrb	r3, [r6, #1]
	ldrb	r2, [r9, #13]
.L170:
	cmp	r2, r3
	bne	.L287
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L288
	mov	r2, #2
	mov	r1, r7
	mov	r0, r6
	bl	FillBorderHchrVy.constprop.13
	ldrsb	r3, [r6, #1]
	cmp	r3, #8
	beq	.L179
	ldrb	r3, [r8, #449]
	ldrb	r2, [r8, #451]
	cmp	r2, r3
	addhi	r3, r3, #1
	strhib	r3, [r8, #449]
	bhi	.L179
	sub	r2, r7, #5
	movw	r3, #4091
	cmp	r2, r3
	bhi	.L179
	mov	r3, #5
	str	r4, [fp, #-52]
	b	.L185
.L224:
	mov	r5, r3
.L182:
	cmp	r7, r5
	add	r3, r3, #1
	bls	.L289
.L185:
	ldr	r0, [r10, #24]
	sub	r2, r3, #1
	ldrb	r5, [r0, r2]
	cmp	r5, #1
	bne	.L224
	ldr	r1, [r8, #440]
	ldrb	lr, [r8, #451]
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
	strb	r5, [r0, r4]
	mov	r0, #0
	ldr	r1, [r10, #24]
	mov	r5, r3
	strb	r0, [r1, r2]
	b	.L182
.L282:
	add	r10, r6, #4096
	ldr	r1, [r9]
	ldr	r3, .L298+4
	ldrb	r2, [r10, #30]
	cmp	r1, r2
	bcc	.L102
	ldrb	r1, [r3, #12]
	add	r3, r1, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L103
.L104:
	ldrb	r0, [r10, #28]
	add	r2, r6, #4096
	add	r2, r2, #52
	sub	r3, r0, #1
	uxtb	r3, r3
	sxtb	ip, r3
	cmp	ip, #0
	ble	.L105
.L106:
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
	bne	.L106
	ldrb	r1, [r9, #12]
	ldrb	r0, [r10, #28]
.L105:
	ldr	r3, [r10, #36]
	strb	r1, [r10, #52]
	cmp	r3, r0
	ldr	r1, [r9]
	addcc	r3, r3, #1
	strcc	r3, [r10, #36]
	cmp	r0, r3
	str	r1, [r10, #56]
	beq	.L108
	ldrb	r3, [r6]
	ldrb	r2, [r9, #12]
.L109:
	cmp	r2, r3
	sxtb	r2, r3
	str	r2, [fp, #-52]
	bne	.L290
	add	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #1
	bls	.L291
	add	r3, r6, #8640
	add	r8, r6, #8192
	cmp	r7, #4096
	mov	r2, r3
	ldr	r3, [r5, #16]
	add	r2, r2, #8
	str	r2, [fp, #-76]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [r8, #456]
	ldrb	r3, [r8, #452]
	str	r3, [fp, #-80]
	bhi	.L117
	ldr	r3, [fp, #-52]
	cmp	r3, #8
	beq	.L292
	sub	ip, r7, #3
	ldr	r3, [r8, #436]
	cmp	ip, #4
	str	r3, [fp, #-84]
	bls	.L215
	ldr	r2, [fp, #-56]
	ldrb	r3, [r2, #4]
	cmp	r3, #1
	beq	.L215
	add	r3, r2, #4
	mov	r2, #4
	b	.L121
.L122:
	ldrb	r1, [r3, #1]!
	cmp	r1, #1
	beq	.L272
.L121:
	add	r2, r2, #1
	str	r2, [fp, #-60]
	cmp	r2, ip
	bne	.L122
.L272:
	str	r2, [fp, #-64]
.L120:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-60]
	rsb	r3, r2, r3
	cmp	r3, #4
	strgt	r7, [fp, #-68]
	ldrgt	r2, .L298
	strgt	r2, [fp, #-72]
	ble	.L129
.L128:
	sub	r2, r3, #-1073741823
	ldr	r7, [fp, #-72]
	mov	r1, #0
	add	r2, r7, r2, lsl #2
	mov	lr, r1
	mov	r0, r1
.L127:
	ldr	r7, [r2], #4
	cmp	r7, lr
	movhi	r1, r0
	add	r0, r0, #1
	movhi	lr, r7
	cmp	r0, #3
	bne	.L127
	sub	r3, r3, #1
	ldr	r2, [fp, #-56]
	add	r1, r3, r1
	ldr	r3, [fp, #-52]
	mov	r0, #1
	rsb	r3, r3, r1
	strb	r0, [r2, r1]
	cmp	r3, #4
	ldr	r2, [r8, #456]
	add	r2, r2, #1
	str	r2, [r8, #456]
	bgt	.L128
	ldr	r7, [fp, #-68]
.L129:
	cmp	ip, #0
	mov	r3, ip
	ble	.L273
	ldr	r2, [fp, #-56]
	ldrb	r1, [r2, ip]
	add	r2, r2, ip
	cmp	r1, #1
	bne	.L132
	b	.L273
.L133:
	ldrb	r1, [r2, #-1]!
	cmp	r1, #1
	beq	.L216
.L132:
	subs	r3, r3, #1
	bne	.L133
.L216:
	str	r3, [fp, #-68]
.L130:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-68]
	add	r3, r3, r2
	cmp	r3, ip
	strcc	r7, [fp, #-88]
	ldrcc	r2, .L298
	strcc	r2, [fp, #-72]
	bcs	.L140
.L139:
	sub	r2, r3, #-1073741823
	ldr	r7, [fp, #-72]
	mov	r1, #0
	add	r2, r7, r2, lsl #2
	mov	lr, r1
	mov	r0, r1
.L138:
	ldr	r7, [r2], #4
	cmp	r7, lr
	movhi	r1, r0
	add	r0, r0, #1
	movhi	lr, r7
	cmp	r0, #3
	bne	.L138
	sub	r3, r3, #1
	ldr	r2, [fp, #-56]
	add	r1, r3, r1
	ldr	r3, [fp, #-52]
	mov	r0, #1
	add	r3, r1, r3
	strb	r0, [r2, r1]
	cmp	r3, ip
	ldr	r2, [r8, #456]
	add	r2, r2, #1
	str	r2, [r8, #456]
	bcc	.L139
	ldr	r7, [fp, #-88]
.L140:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-68]
	cmp	r3, r2
	bhi	.L136
	ldr	r3, [fp, #-60]
	mov	r2, #0
	str	r7, [fp, #-72]
	mov	r7, r2
	str	r4, [fp, #-92]
	str	r6, [fp, #-88]
	mov	r4, r3
	b	.L147
.L143:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-64]
	cmp	r3, r2
	bhi	.L293
	mov	r7, r4
	ldr	r4, [fp, #-64]
.L147:
	ldr	r3, [fp, #-56]
	ldrb	r3, [r3, r4]
	cmp	r3, #1
	movne	r4, r7
	bne	.L143
	ldr	r2, [fp, #-60]
	str	r3, [fp, #-96]
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	cmpne	r2, r4
	ldr	r2, [r8, #456]
	add	r2, r2, #1
	str	r2, [r8, #456]
	beq	.L143
	mov	r1, r3
	rsb	r0, r7, r4
	bl	__aeabi_uidiv
	cmp	r0, #1
	mov	r6, r0
	bls	.L143
	ldr	r3, [fp, #-96]
	mov	r1, r3
.L146:
	ldr	r3, [fp, #-52]
	ldr	lr, .L298
	add	r3, r7, r3
	mov	r7, #0
	sub	r2, r3, #-1073741823
	mov	ip, r7
	mov	r0, r7
	add	r2, lr, r2, lsl #2
.L145:
	ldr	lr, [r2], #4
	cmp	lr, ip
	movhi	r7, r0
	add	r0, r0, #1
	movhi	ip, lr
	cmp	r0, #3
	bne	.L145
	sub	r3, r3, #1
	add	r1, r1, #1
	add	r7, r3, r7
	ldr	r3, [fp, #-56]
	mov	r2, #1
	cmp	r1, r6
	strb	r2, [r3, r7]
	ldr	r3, [r8, #456]
	add	r3, r3, #1
	str	r3, [r8, #456]
	bne	.L146
	b	.L143
.L163:
	mov	r1, #255
	mvn	r2, #0
	strb	r2, [r3, #13]
.L164:
	mov	r3, #100
	str	r3, [r9, #4]
	b	.L165
.L289:
	ldr	r4, [fp, #-52]
.L179:
	ldr	r3, [r9, #4]
	str	r3, [r6, #12]
	b	.L176
.L288:
	mov	r1, #0
	ldr	r0, [r10, #24]
	mov	r5, r1
	mov	r2, r7
	bl	pq_alg_memset
	str	r5, [r6, #12]
	mvn	r3, #0
	mov	r2, r7
	strb	r3, [r6, #1]
	mov	r1, r5
	ldr	r0, [r8, #440]
	bl	pq_alg_memset
	strb	r5, [r8, #449]
	str	r5, [r8, #464]
	b	.L176
.L225:
	cmp	lr, r1
	cmple	ip, r1
	mov	r5, r3
	bge	.L182
	mov	r1, #1
	strb	r1, [r0, r3]
	ldr	r1, [r10, #24]
	mov	r0, #0
	strb	r0, [r1, r2]
	b	.L182
.L287:
	mov	r2, r7
	mov	r1, #0
	ldr	r0, [r8, #440]
	bl	pq_alg_memset
	mov	r3, #0
	strb	r3, [r8, #449]
	b	.L176
.L169:
	cmp	r0, #1
	ldrb	r3, [r9, #13]
	ble	.L222
	mov	r1, #1
	sxtb	ip, r3
	mov	lr, r7
	str	ip, [fp, #-60]
	mov	r7, r3
	mov	ip, r1
	b	.L173
.L172:
	ldr	r3, [fp, #-56]
	add	r2, r2, #8
	cmp	r3, r0
	bge	.L294
.L173:
	ldrsb	r3, [r2, #8]
	add	r1, r1, #1
	ldr	r5, [fp, #-60]
	uxtb	r1, r1
	cmp	r3, r5
	sxtb	r3, r1
	str	r3, [fp, #-56]
	bne	.L172
	add	r3, ip, #1
	ldrb	r5, [r10, #50]
	str	r3, [fp, #-52]
	ldr	r3, [r2, #12]
	cmp	r3, r5
	ldrcsb	ip, [fp, #-52]
	b	.L172
.L294:
	mov	r3, r7
	mov	r7, lr
.L171:
	ldrb	r2, [r10, #48]
	cmp	r2, ip
	strlsb	r3, [r6, #1]
	movhi	r2, r3
	ldrlsb	r2, [r9, #13]
	ldrhib	r3, [r6, #1]
	b	.L170
.L286:
	ldr	r0, [r8, #444]
	ldrb	r5, [r8, #451]
	ldrsb	r2, [r0, r1]
	cmp	r2, r5
	bge	.L228
	sub	r2, r3, #2
	ldrsb	lr, [r0, r2]
	ldrsb	r0, [r0, r3]
	cmp	r5, lr
	bgt	.L229
	cmp	lr, r0
	blt	.L229
	strb	r7, [ip, r2]
	mov	ip, #0
	ldr	r0, [r10, #20]
	mov	r2, r3
	strb	ip, [r0, r1]
	b	.L206
.L284:
	mov	r2, r4
	mov	r1, #0
	ldr	r0, [r8, #444]
	bl	pq_alg_memset
	mov	r3, #0
	strb	r3, [r8, #450]
	b	.L95
.L194:
	cmp	r0, #1
	ldrb	r3, [r9, #14]
	ble	.L226
	mov	r1, #1
	mov	r7, r4
	sxtb	lr, r3
	mov	ip, r1
	mov	r4, r3
	b	.L198
.L197:
	ldr	r3, [fp, #-56]
	add	r2, r2, #8
	cmp	r0, r3
	ble	.L295
.L198:
	ldrsb	r3, [r2, #8]
	add	r1, r1, #1
	cmp	r3, lr
	uxtb	r1, r1
	sxtb	r3, r1
	str	r3, [fp, #-56]
	bne	.L197
	add	r3, ip, #1
	ldrb	r5, [r10, #51]
	str	r3, [fp, #-52]
	ldr	r3, [r2, #12]
	cmp	r3, r5
	ldrcsb	ip, [fp, #-52]
	b	.L197
.L285:
	mov	r1, #0
	ldr	r0, [r10, #20]
	mov	r5, r1
	mov	r2, r4
	bl	pq_alg_memset
	str	r5, [r6, #8]
	mvn	r3, #0
	mov	r2, r4
	strb	r3, [r6, #2]
	mov	r1, r5
	ldr	r0, [r8, #444]
	bl	pq_alg_memset
	strb	r5, [r8, #450]
	str	r5, [r8, #460]
	b	.L95
.L229:
	cmp	r5, r0
	cmple	lr, r0
	mov	r2, r3
	bge	.L206
	mov	r0, #1
	strb	r0, [ip, r3]
	ldr	r0, [r10, #20]
	mov	ip, #0
	strb	ip, [r0, r1]
	b	.L206
.L295:
	mov	r3, r4
	mov	r4, r7
.L196:
	ldrb	r2, [r10, #48]
	cmp	r2, ip
	strlsb	r3, [r6, #2]
	movhi	r2, r3
	ldrlsb	r2, [r9, #14]
	ldrhib	r3, [r6, #2]
	b	.L195
.L226:
	mov	ip, #1
	b	.L196
.L102:
	mov	r1, #255
	mvn	r2, #0
	strb	r2, [r3, #12]
.L103:
	mov	r3, #100
	str	r3, [r9]
	b	.L104
.L215:
	mov	r3, #4
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	b	.L120
.L292:
	mov	r3, r2
	ldr	r1, [fp, #-52]
	mov	r2, r7
	ldr	r0, [fp, #-56]
	bl	FillBorder_Size8
.L119:
	ldr	r3, [fp, #-76]
	mov	r0, r7
	ldr	r2, [fp, #-56]
	ldr	r1, [fp, #-52]
	bl	CheckStartEndBorder.part.0
	mov	r2, r7
	ldr	r1, [r5, #16]
	ldr	r0, [r10, #16]
	bl	pq_alg_memcpy
	ldrsb	r3, [r6]
	str	r3, [fp, #-52]
.L117:
	ldr	r3, [fp, #-52]
	cmp	r3, #8
	beq	.L154
	ldrb	r3, [r8, #448]
	ldrb	r2, [r8, #451]
	cmp	r2, r3
	addhi	r3, r3, #1
	strhib	r3, [r8, #448]
	bhi	.L154
	sub	r2, r7, #5
	movw	r3, #4091
	cmp	r2, r3
	bhi	.L154
	mov	r3, #5
	str	r4, [fp, #-52]
	b	.L160
.L220:
	mov	r5, r3
.L157:
	cmp	r7, r5
	add	r3, r3, #1
	bls	.L296
.L160:
	ldr	r0, [r10, #16]
	sub	r2, r3, #1
	ldrb	r5, [r0, r2]
	cmp	r5, #1
	bne	.L220
	ldr	r1, [r8, #436]
	ldrb	lr, [r8, #451]
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
	strb	r5, [r0, r4]
	mov	r0, #0
	ldr	r1, [r10, #16]
	mov	r5, r3
	strb	r0, [r1, r2]
	b	.L157
.L291:
	add	r8, r6, #8192
	mov	r1, #0
	mov	r5, r1
	ldr	r0, [r10, #16]
	mov	r2, r7
	bl	pq_alg_memset
	str	r5, [r6, #4]
	mvn	r3, #0
	mov	r2, r7
	strb	r3, [r6]
	mov	r1, r5
	ldr	r0, [r8, #436]
	bl	pq_alg_memset
	strb	r5, [r8, #448]
	str	r5, [r8, #456]
	b	.L115
.L296:
	ldr	r4, [fp, #-52]
.L154:
	ldr	r3, [r9]
	str	r3, [r6, #4]
	b	.L115
.L188:
	mov	r1, #255
	mvn	r2, #0
	strb	r2, [r3, #14]
.L189:
	mov	r3, #100
	str	r3, [r9, #8]
	b	.L190
.L222:
	mov	ip, #1
	b	.L171
.L290:
	add	r8, r6, #8192
	mov	r2, r7
	mov	r1, #0
	ldr	r0, [r8, #436]
	bl	pq_alg_memset
	mov	r3, #0
	strb	r3, [r8, #448]
	b	.L115
.L108:
	cmp	r0, #1
	ldrb	r3, [r9, #12]
	ble	.L213
	mov	r1, #1
	sxtb	ip, r3
	mov	r8, r7
	str	ip, [fp, #-60]
	mov	lr, r3
	mov	ip, r1
	b	.L112
.L111:
	ldr	r3, [fp, #-56]
	add	r2, r2, #8
	cmp	r3, r0
	bge	.L297
.L112:
	ldrsb	r3, [r2, #8]
	add	r1, r1, #1
	ldr	r7, [fp, #-60]
	uxtb	r1, r1
	cmp	r3, r7
	sxtb	r3, r1
	str	r3, [fp, #-56]
	bne	.L111
	add	r3, ip, #1
	ldrb	r7, [r10, #49]
	str	r3, [fp, #-52]
	ldr	r3, [r2, #12]
	cmp	r3, r7
	ldrcsb	ip, [fp, #-52]
	b	.L111
.L273:
	str	ip, [fp, #-68]
	b	.L130
.L221:
	cmp	lr, r1
	cmple	ip, r1
	mov	r5, r3
	bge	.L157
	mov	r1, #1
	strb	r1, [r0, r3]
	ldr	r1, [r10, #16]
	mov	r0, #0
	strb	r0, [r1, r2]
	b	.L157
.L297:
	mov	r7, r8
	mov	r3, lr
.L110:
	ldrb	r2, [r10, #48]
	cmp	r2, ip
	strlsb	r3, [r6]
	movhi	r2, r3
	ldrlsb	r2, [r9, #12]
	ldrhib	r3, [r6]
	b	.L109
.L213:
	mov	ip, #1
	b	.L110
.L293:
	ldr	r7, [fp, #-72]
	ldr	r6, [fp, #-88]
	ldr	r4, [fp, #-92]
.L136:
	cmp	r7, #4
	bls	.L119
	ldr	r2, [fp, #-84]
	sub	lr, r7, #1
	add	r3, r2, #3
	add	lr, r2, lr
	ldr	r2, [fp, #-56]
	add	r2, r2, #3
	b	.L152
.L148:
	ldrb	r1, [r3]
	sub	ip, r1, #1
	sxtb	r1, r1
	cmp	r1, #0
	ble	.L151
.L274:
	strb	ip, [r3]
.L150:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L119
.L152:
	ldrb	r1, [r2, #1]!
	cmp	r1, #1
	bne	.L148
	mov	r0, #0
	strb	r1, [r2, #-1]
	strb	r0, [r2]
	ldrb	r1, [r3]
	ldr	r0, [fp, #-80]
	add	ip, r1, #1
	sxtb	r1, r1
	cmp	r1, r0
	blt	.L274
	ldrb	r1, [fp, #-80]
	strb	r1, [r3]
	b	.L150
.L151:
	mov	r1, #0
	strb	r1, [r3]
	b	.L150
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
	bgt	.L324
	str	r8, [r0, #636]
	ldr	r3, [r1, #4]
	str	r3, [r0, #640]
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
	beq	.L327
.L305:
	ldr	r3, [r6, #64]
	cmp	r3, #8
	movne	r3, #60
	strneh	r3, [r5, #26]
	beq	.L328
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
	bgt	.L329
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
	cmp	lr, #2048
	ldr	r2, [ip, #4]!
	beq	.L321
	mov	r0, r4
	mov	r3, #1
	ldrb	r1, [r0, lr]!
	and	r1, r1, r3
	orr	r1, r1, r2
	str	r1, [ip]
	b	.L322
.L331:
	ldrb	r2, [r0, #1]!
	and	r2, r2, #1
	orr	r1, r1, r2, asl r3
	add	r3, r3, #1
	cmp	r3, #32
	str	r1, [ip]
	beq	.L330
.L322:
	add	r2, r3, lr
	cmp	r2, #2048
	bcc	.L331
.L321:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L330:
	add	lr, lr, #32
	b	.L320
.L329:
	movw	r3, #1080
	cmp	r1, r3
	movle	r3, #36
	movgt	r3, #63
	strh	r3, [r5, #36]
	b	.L316
.L327:
	add	r3, r1, #7
	cmp	r1, #0
	movlt	r1, r3
	mov	r3, r1, asr #3
	strh	r3, [r0, #24]
	b	.L305
.L328:
	add	r3, r2, #7
	cmp	r2, #0
	movlt	r2, r3
	mov	r3, r2, asr #3
	strh	r3, [r5, #26]
	b	.L307
.L324:
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
