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
	.file	"drv_venc_ratecontrol.c"
	.global	__aeabi_uidiv
	.text
	.align	2
	.type	VEDU_DRV_RCModifyQPDeltaOfIP, %function
VEDU_DRV_RCModifyQPDeltaOfIP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	mov	r1, #0
	ldrd	r2, [r4, #120]
	mvn	r0, #0
	ldr	r6, [r4, #28]
	cmp	r3, r1
	ldr	r1, [r4, #68]
	cmpeq	r2, r0
	bls	.L2
	ldr	r1, [r4, #128]
	mov	r3, r1, asl #4
	add	r1, r3, r1, lsl #2
.L3:
	cmp	r1, #16711680
	mov	r3, #0
	movt	r3, 510
	add	r5, r4, #4096
	movhi	r1, r3
	cmp	r1, r6
	ldr	r4, [r5, #468]
	bcc	.L6
	cmp	r4, #0
	ldmlefd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L6:
	rsb	r0, r1, r6
	mov	r0, r0, asl #8
	bl	__aeabi_uidiv
	mvn	r3, #255
	ldr	r2, [r5, #352]
	ldr	r1, .L9
	cmp	r0, r3
	movlt	r0, r3
	cmp	r2, #3264
	movcs	r2, #3264
	cmp	r0, #256
	mov	r2, r2, lsr #6
	movge	r0, #256
	add	r3, r4, r0, asr #6
	ldr	r2, [r1, r2, asl #2]
	bic	r3, r3, r3, asr #31
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r5, #468]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2:
	mov	r0, r2, asl #4
	add	r1, r1, #19
	add	r0, r0, r2, lsl #2
	bl	__aeabi_uidiv
	mov	r1, r0
	b	.L3
.L10:
	.align	2
.L9:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VEDU_DRV_RCModifyQPDeltaOfIP, .-VEDU_DRV_RCModifyQPDeltaOfIP
	.align	2
	.type	VEDU_DRV_RcModifyQPForLargeFrmBits, %function
VEDU_DRV_RcModifyQPForLargeFrmBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r0, #4096
	ldr	r3, [r0, #56]
	ldr	ip, [r2, #840]
	ldr	r1, [r2, #360]
	rsb	r3, ip, r3
	ldr	r2, [r0, #28]
	cmp	r3, #10
	movhi	r0, #0
	movls	r0, #1
	cmp	r2, r1
	movcc	r0, #0
	cmp	r0, #0
	beq	.L12
	cmp	r3, #0
	ble	.L13
	mul	r1, r1, r3
	mov	r0, #0
	bl	__aeabi_uidiv
	ldmfd	sp, {fp, sp, pc}
.L12:
	cmp	r3, #0
	ldmlefd	sp, {fp, sp, pc}
	add	ip, r1, r1, lsl #1
	cmp	r2, ip, lsr #1
	ldmccfd	sp, {fp, sp, pc}
	mul	r1, r1, r3
	bl	__aeabi_uidiv
	ldmfd	sp, {fp, sp, pc}
.L13:
	bne	.L15
	mov	r0, r3
	bl	__aeabi_uidiv
	ldmfd	sp, {fp, sp, pc}
.L15:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RcModifyQPForLargeFrmBits, .-VEDU_DRV_RcModifyQPForLargeFrmBits
	.global	__aeabi_idiv
	.align	2
	.type	VEDU_DRV_RCGetTimeOfP, %function
VEDU_DRV_RCGetTimeOfP:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #4096
	mov	r5, r0
	ldr	r3, [r4, #480]
	cmp	r3, #0
	beq	.L19
	ldr	r3, [r4, #512]
	add	r3, r3, #1
	cmp	r3, #1
	movhi	r3, #0
	str	r3, [r4, #512]
	add	r3, r3, #1136
	ldr	r2, [r0, #28]
	add	r3, r3, #8
	add	r3, r0, r3, lsl #2
	str	r2, [r3, #4]
.L22:
	add	r3, r5, #4544
	ldr	r2, [r4, #488]
	ldr	r0, [r4, #484]
	mov	r1, #0
	mov	ip, r3
	add	r3, r3, #40
	add	ip, ip, #60
	add	r0, r2, r0
.L25:
	ldr	r2, [r3, #4]!
	cmp	r3, ip
	add	r1, r1, r2
	bne	.L25
	cmp	r0, #0
	cmpne	r1, #0
	beq	.L31
	mov	r1, r1, asl #1
	add	r0, r0, r0, lsl #2
	bl	__aeabi_idiv
	cmp	r0, #2
	str	r0, [r4, #460]
	movle	r0, #3
	bgt	.L39
.L30:
	mov	r3, #1
	str	r0, [r4, #460]
	str	r3, [r4, #464]
	ldr	r3, [r5, #68]
	cmp	r3, #1
	beq	.L40
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L19:
	ldr	r2, [r4, #516]
	add	r2, r2, #1
	cmp	r2, #4
	strhi	r3, [r4, #516]
	strls	r2, [r4, #516]
	movls	r3, r2
	add	r3, r3, #1136
	add	r3, r3, #10
	ldr	r2, [r0, #28]
	add	r3, r0, r3, lsl #2
	str	r2, [r3, #4]
	b	.L22
.L39:
	cmp	r0, #50
	movge	r0, #50
	b	.L30
.L40:
	str	r3, [r4, #460]
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L31:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCGetTimeOfP, .-VEDU_DRV_RCGetTimeOfP
	.align	2
	.global	RC_DRV_NewModeMovingDecision
	.type	RC_DRV_NewModeMovingDecision, %function
RC_DRV_NewModeMovingDecision:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r3, r0, #4096
	add	ip, r0, #212
	str	r0, [fp, #-48]
	ldr	r3, [r3, #432]
	add	lr, r0, #220
	ldr	r5, [r0, #52]
	mov	r1, ip
	mov	r0, #0
	mov	r4, r3
	str	r3, [fp, #-60]
	mov	r2, r4
.L43:
	ldr	r3, [r1, #4]!
	cmn	r3, #1
	add	r3, r3, #8
	rsb	r2, r2, r3
	ldr	r3, .L61
	usatne	r2, #4, r2
	moveq	r2, #8
	cmp	r1, lr
	add	r2, r3, r2, lsl #2
	ldr	r3, [r1, #-64]
	ldr	r2, [r2, #208]
	mul	r3, r3, r2
	add	r0, r0, r3, lsr #5
	bne	.L43
	ldr	r3, [fp, #-48]
	mov	r1, #0
	add	r3, r3, #180
.L44:
	ldr	r2, [r3, #4]!
	cmp	ip, r3
	add	r1, r1, r2
	bne	.L44
	cmp	r0, #0
	cmpne	r1, #0
	moveq	r4, #255
	bne	.L59
.L45:
	rsb	r2, r5, #100
	add	r3, r5, #16777216
	sub	r3, r3, #30
	str	r2, [fp, #-52]
	mov	r1, r2
	ldr	r2, [fp, #-48]
	mov	r3, r3, asl #8
	str	r3, [fp, #-56]
	movw	r5, #41195
	mov	r8, #0
	mov	lr, r3
	ldr	ip, [r2, #280]
	mov	r3, r2
	mov	r9, r2
	mov	r2, r1
	movt	r5, 59918
	mla	r4, r2, r4, lr
	ldr	r0, [r9, #248]!
	add	r10, r3, #280
	mov	lr, ip
	mov	r3, ip
	mov	r7, r8
	mov	r2, r0
	mov	r1, r0
	mov	r6, r8
	mov	r4, r4, lsr #1
	umull	r4, r5, r4, r5
	mov	r4, r5, lsr #5
	b	.L48
.L60:
	ldr	r2, [r9, #4]!
	ldr	r3, [r10, #4]!
.L48:
	cmp	ip, r3
	add	r6, r6, #1
	add	r7, r2, r7
	add	r8, r3, r8
	movcc	ip, r3
	cmp	lr, r3
	movcs	lr, r3
	cmp	r0, r2
	movcc	r0, r2
	cmp	r1, r2
	movcs	r1, r2
	cmp	r6, #8
	bne	.L60
	rsb	r7, r0, r7
	subs	r7, r7, r1
	bne	.L49
	ldr	r1, [fp, #-48]
	mov	r2, #256
	mov	r3, #100
	str	r3, [r1, #312]
.L50:
	ldr	r3, [fp, #-56]
	movw	r1, #8969
	ldr	ip, [fp, #-52]
	movt	r1, 22765
	add	r3, r3, #6400
	add	r0, r4, #1
	mla	r2, ip, r2, r3
	ldr	ip, [fp, #-48]
	str	r4, [ip, #436]
	umull	r4, r5, r2, r1
	rsb	r3, r5, r2
	add	r3, r5, r3, lsr #1
	mov	r3, r3, lsr #6
	str	r3, [ip, #440]
	add	r0, r0, r3
	mov	r0, r0, lsr #1
	str	r0, [ip, #444]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L59:
	mov	r0, r0, asl #6
	bl	__aeabi_idiv
	mov	r0, r0, asr #4
	cmp	r0, #0
	movle	r0, #1
	ble	.L46
	cmp	r0, #99
	movge	r0, #99
.L46:
	ldr	r3, .L61
	movw	r2, #34079
	movt	r2, 20971
	add	r0, r3, r0, lsl #2
	ldr	r4, [r0, #272]
	mov	r4, r4, asl #8
	smull	r2, r3, r4, r2
	mov	r4, r4, asr #31
	rsb	r4, r4, r3, asr #5
	b	.L45
.L49:
	ldr	r3, [fp, #-60]
	rsb	r8, ip, r8
	ldr	r2, .L61
	rsb	r8, lr, r8
	mov	r1, r7
	mov	r3, r3, lsr #6
	sub	r3, r3, #22
	usat	r3, #4, r3
	add	r3, r2, r3, lsl #2
	ldr	r0, [r3, #672]
	mul	r0, r0, r8
	bl	__aeabi_idiv
	cmp	r0, #0
	movle	r3, #1
	ble	.L51
	cmp	r0, #16
	movlt	r3, r0
	movge	r3, #16
.L51:
	ldr	r2, .L61
	mov	r0, #100
	mov	r1, r7
	movw	r6, #34079
	add	r3, r2, r3, lsl #2
	movt	r6, 20971
	mul	r0, r0, r8
	ldr	r5, [r3, #736]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-48]
	mov	r2, r5, asl #8
	smull	r6, r7, r2, r6
	mov	r2, r2, asr #31
	rsb	r2, r2, r7, asr #5
	str	r0, [r3, #312]
	b	.L50
.L62:
	.align	2
.L61:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	RC_DRV_NewModeMovingDecision, .-RC_DRV_NewModeMovingDecision
	.align	2
	.global	VEDU_DRV_EflRCCalcTargetFrameBits
	.type	VEDU_DRV_EflRCCalcTargetFrameBits, %function
VEDU_DRV_EflRCCalcTargetFrameBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #4096
	ldr	ip, [r0, #68]
	mov	lr, r1
	mov	r4, r0
	ldr	r1, [r5, #808]
	mov	r8, r3
	cmp	r1, ip
	ldrne	r6, [r0, #128]
	umullne	r6, r7, ip, r6
	strned	r6, [r0, #120]
	strne	ip, [r5, #808]
.L64:
	umull	r0, r1, lr, r2
	mov	r3, #0
	mvn	r2, #0
	mla	r1, lr, r8, r1
	cmp	r1, r3
	cmpeq	r0, r2
	bls	.L66
	ldr	r3, .L67
	ldr	r0, .L67+4
	ldr	r3, [r3, #8]
	blx	r3
	ldr	ip, [r4, #68]
	mvn	r0, #0
.L66:
	ldr	r1, [r5, #460]
	sub	r1, r1, #1
	add	r1, r1, ip
	bl	__aeabi_uidiv
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L68:
	.align	2
.L67:
	.word	venc_Osal_Func_Ptr_S
	.word	.LC0
	UNWIND(.fnend)
	.size	VEDU_DRV_EflRCCalcTargetFrameBits, .-VEDU_DRV_EflRCCalcTargetFrameBits
	.align	2
	.type	VEDU_DRV_RCGetTargetFrameBits, %function
VEDU_DRV_RCGetTargetFrameBits:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #4096
	ldr	r6, [r0, #64]
	mov	r4, r0
	ldr	r3, [r5, #812]
	cmp	r3, r6
	ldreq	r0, [r0, #128]
	beq	.L71
	ldr	r1, [r4, #56]
	mov	r0, r6
	bl	__aeabi_uidiv
	str	r0, [r4, #128]
	str	r6, [r5, #812]
.L71:
	ldr	r2, [r4, #68]
	ldr	r3, [r4, #72]
	umull	r6, r7, r0, r2
	cmp	r3, #0
	strd	r6, [r4, #120]
	ldreq	r1, [r5, #464]
	bne	.L78
	cmp	r2, #1000
	mulcs	r0, r0, r1
	bcc	.L75
.L77:
	adds	r3, r3, #0
	str	r0, [r5, #428]
	movne	r3, #1
	str	r3, [r5, #480]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L78:
	cmp	r2, #1
	ldr	lr, [r5, #460]
	ldr	r1, [r5, #440]
	ldr	ip, [r5, #444]
	beq	.L73
	cmp	r1, lr
	movlt	r1, lr
	cmp	r1, ip
	movge	r1, ip
	cmp	r2, #1000
	str	r1, [r5, #460]
	mulcs	r0, r0, r1
	bcs	.L77
.L75:
	mov	r3, r7
	mov	r2, r6
	mov	r0, r4
	bl	VEDU_DRV_EflRCCalcTargetFrameBits
	ldr	r3, [r4, #72]
	b	.L77
.L73:
	str	r2, [r5, #460]
	mov	r1, r2
	b	.L75
	UNWIND(.fnend)
	.size	VEDU_DRV_RCGetTargetFrameBits, .-VEDU_DRV_RCGetTargetFrameBits
	.align	2
	.global	VEDU_DRV_RCCalculateCurQP_AVBR
	.type	VEDU_DRV_RCCalculateCurQP_AVBR, %function
VEDU_DRV_RCCalculateCurQP_AVBR:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r5, r0, #4096
	mov	r4, r0
	ldr	r3, [r5, #480]
	ldr	r9, [r5, #792]
	cmp	r3, #0
	ldr	r6, [r5, #800]
	str	r3, [fp, #-48]
	bne	.L102
.L80:
	ldr	r3, [r4, #28]
	mov	r0, r4
	ldr	r1, [r5, #360]
	str	r3, [fp, #-56]
	str	r1, [fp, #-52]
	bl	VEDU_DRV_RcModifyQPForLargeFrmBits
	ldr	r1, [fp, #-52]
	ldr	r3, [fp, #-56]
	ldr	r7, [r5, #460]
	cmp	r3, r1
	mov	r8, r7, asr #4
	mov	r10, r0
	bcc	.L81
	rsb	r0, r1, r3
	mov	r0, r0, asl #6
	bl	__aeabi_uidiv
	ldr	r3, [r4, #316]
	mul	r0, r3, r0
	mov	r0, r0, asr #8
.L82:
	add	r0, r0, r10
	mvn	r3, #53
	cmp	r0, r3
	movlt	r0, r3
	cmp	r0, #256
	movge	r0, #256
	cmp	r8, #9
	movle	r1, #10
	ble	.L83
	cmp	r8, #200
	movlt	r1, r8
	movge	r1, #200
.L83:
	mov	r3, r0, asl #3
	add	r0, r3, r0, lsl #1
	bl	__aeabi_idiv
	cmp	r7, #640
	mov	r8, r0
	ble	.L84
	mvn	r3, #15
	cmp	r0, r3
	movlt	r8, r3
	cmp	r8, #32
	movge	r8, #32
.L84:
	ldr	r10, [r4, #64]
	mov	r0, r6, asl #5
	ldr	r2, [r4, #136]
	mov	r1, r10
	str	r2, [fp, #-56]
	bl	__aeabi_uidiv
	mov	r1, r10
	str	r0, [fp, #-52]
	mov	r0, r9, asl #5
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-52]
	ldr	r1, .L104
	cmp	r9, r6
	usat	r3, #6, r3
	ldr	r2, [fp, #-56]
	add	r3, r1, r3, lsl #2
	mov	ip, r2, lsr #4
	ldr	r3, [r3, #804]
	usat	r0, #6, r0
	add	r1, r1, r0, lsl #2
	ldr	r1, [r1, #804]
	rsb	r3, r3, r1
	bls	.L85
	rsb	r1, ip, r2
	cmp	r9, r1
	bls	.L85
	mov	r2, r3, asl #3
	mvn	r1, #127
	sub	r6, r2, r3, asl #1
	mov	r6, r6, asr #2
	cmp	r6, r1
	movlt	r6, r1
	cmp	r6, #256
	movge	r6, #256
	b	.L86
.L85:
	cmp	r9, r6
	bcc	.L103
.L94:
	mov	r6, #0
.L86:
	cmp	r7, #640
	ble	.L87
	mvn	r3, #15
	cmp	r6, r3
	movlt	r6, r3
	cmp	r6, #32
	movge	r6, #32
.L87:
	ldr	r0, [r4, #392]
	add	r2, r4, #400
	ldr	ip, [r4, #396]
	ldr	r3, [r4, #144]
	mov	r0, r0, lsr #10
	str	r2, [fp, #-56]
	orr	r0, r0, ip, asl #22
	rsb	r0, r3, r0
	mov	r1, r3
	str	r3, [fp, #-52]
	add	r0, r0, r0, lsl #1
	mov	r0, r0, asl #3
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-56]
	ldr	r3, [fp, #-52]
	ldr	r2, [r2, #4]
	mov	r1, r3
	mov	r7, r0
	ldr	r0, [r4, #400]
	orr	r7, r7, r7, asr #31
	mov	r0, r0, lsr #10
	orr	r0, r0, r2, asl #22
	rsb	r0, r3, r0
	add	r0, r0, r0, lsl #1
	mov	r0, r0, asl #4
	bl	__aeabi_uidiv
	cmp	r7, #1
	add	r2, r8, r6
	movge	r7, #1
	orr	r0, r0, r0, asr #31
	cmp	r0, #1
	movge	r0, #1
	cmp	r9, r10
	bls	.L88
	add	r2, r7, r2
	ldr	r3, [r5, #424]
	add	r2, r0, r2
	mov	r1, #0
.L89:
	ldr	ip, [fp, #-48]
	add	r2, r1, r2
	add	r3, r2, r3
	str	r8, [r4, #416]
	cmp	ip, #0
	str	r6, [r4, #420]
	str	r7, [r4, #424]
	str	r0, [r4, #428]
	str	r1, [r4, #432]
	str	r3, [r5, #424]
	beq	.L91
	ldr	r2, [r5, #356]
	cmp	r3, r2
	bcs	.L91
	ldr	r1, [r4, #68]
	cmp	r1, #1
	addhi	r3, r3, r2
	movhi	r3, r3, lsr #1
.L91:
	ldmib	r4, {r1, r2}
	mov	r2, r2, asl #6
	mov	r1, r1, asl #6
	cmp	r3, r1
	movcc	r3, r1
	cmp	r3, r2
	movcs	r3, r2
	str	r3, [r5, #424]
	mov	r3, r3, lsr #6
	str	r3, [r5, #432]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L88:
	add	r2, r2, r7
	add	r2, r2, r0
	cmp	r2, #0
	ldrle	r3, [r5, #424]
	movle	r1, #0
	ble	.L89
	ldr	r1, [r4, #148]
	ldr	r3, [r5, #424]
	cmp	r3, r1, asl #6
	addcs	r2, r6, r7
	mvncs	r1, #5
	addcs	r2, r0, r2
	movcs	r8, #0
	movcc	r1, #0
	b	.L89
.L81:
	rsb	r3, r3, r1
	mov	r0, r3, asl #6
	sub	r0, r0, r3, asl #3
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
	b	.L82
.L103:
	add	r2, ip, r2
	cmp	r6, r2
	bcs	.L94
	add	r6, r3, r3, lsl #1
	mvn	r3, #127
	mov	r6, r6, asr #2
	cmp	r6, r3
	movlt	r6, r3
	cmp	r6, #256
	movge	r6, #256
	b	.L86
.L102:
	bl	VEDU_DRV_RCModifyQPDeltaOfIP
	ldr	r3, [r5, #480]
	str	r3, [fp, #-48]
	b	.L80
.L105:
	.align	2
.L104:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VEDU_DRV_RCCalculateCurQP_AVBR, .-VEDU_DRV_RCCalculateCurQP_AVBR
	.align	2
	.global	VEDU_DRV_RCGetTargetFrameBits_AVBR
	.type	VEDU_DRV_RCGetTargetFrameBits_AVBR, %function
VEDU_DRV_RCGetTargetFrameBits_AVBR:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #4096
	ldr	r6, [r0, #64]
	mov	r4, r0
	ldr	r3, [r5, #812]
	cmp	r3, r6
	ldreq	r3, [r0, #128]
	beq	.L108
	ldr	r1, [r0, #56]
	mov	r0, r6
	bl	__aeabi_uidiv
	mov	r3, r0
	str	r0, [r4, #128]
	str	r6, [r5, #812]
.L108:
	ldr	r2, [r4, #68]
	mov	r0, r4
	umull	r2, r3, r3, r2
	strd	r2, [r4, #120]
	bl	RC_DRV_NewModeMovingDecision
	ldr	r3, [r4, #316]
	ldr	ip, [r4, #148]
	sub	r2, r3, #2
	ldr	r1, [r5, #424]
	cmp	r0, r2
	movcc	r0, r2
	cmp	r1, ip, asl #6
	bcc	.L109
	cmp	r3, r0
	bhi	.L122
.L109:
	str	r0, [r4, #316]
.L111:
	ldr	r6, [r4, #120]
	ldr	r2, [r4, #124]
	ldr	r3, [r4, #64]
	umull	r6, r7, r6, r0
	mul	r3, r3, r0
	mla	r7, r0, r2, r7
	mov	r2, r6, lsr #8
	mov	r3, r3, lsr #8
	str	r3, [r4, #136]
	orr	r2, r2, r7, asl #24
	str	r2, [r4, #140]
	movs	r3, r2, lsr #10
	moveq	r3, #1
	str	r3, [r4, #144]
	ldr	r3, [r4, #72]
	cmp	r3, #0
	bne	.L123
	ldr	r1, [r5, #464]
	ldr	r0, [r4, #68]
.L116:
	cmp	r0, #1000
	bcc	.L117
	ldr	r0, [r4, #128]
	mul	r0, r0, r1
.L119:
	adds	r3, r3, #0
	str	r0, [r5, #428]
	movne	r3, #1
	str	r3, [r5, #480]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L122:
	add	r3, r3, #1
	cmp	r3, #254
	movgt	r3, #255
	str	r3, [r4, #316]
	b	.L111
.L123:
	ldr	r1, [r5, #440]
	ldr	ip, [r5, #460]
	ldr	r0, [r5, #444]
	cmp	r1, ip
	movlt	r1, ip
	cmp	r1, r0
	movge	r1, r0
	str	r1, [r5, #460]
	ldr	r0, [r4, #68]
	cmp	r0, #1
	streq	r0, [r5, #460]
	moveq	r1, r0
	bne	.L116
.L117:
	mov	r3, #0
	mov	r0, r4
	bl	VEDU_DRV_EflRCCalcTargetFrameBits
	ldr	r3, [r4, #72]
	b	.L119
	UNWIND(.fnend)
	.size	VEDU_DRV_RCGetTargetFrameBits_AVBR, .-VEDU_DRV_RCGetTargetFrameBits_AVBR
	.align	2
	.global	VENC_DRV_RcOpenOneFrm
	.type	VENC_DRV_RcOpenOneFrm, %function
VENC_DRV_RcOpenOneFrm:
	UNWIND(.fnstart)


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
	beq	.L145
	add	r4, r5, #4096
	ldr	r3, [r4, #520]
	cmp	r3, #0
	bne	.L194
	ldr	r2, [r5, #20]
	cmp	r2, #0
	bne	.L195
	ldr	r3, [r5, #132]
	cmp	r3, #0
	beq	.L144
	ldr	r3, [r5, #56]
	str	r3, [r4, #788]
	bl	VEDU_DRV_RCCalculateCurQP_AVBR
	mov	r0, r5
	bl	VEDU_DRV_RCGetTimeOfP
	cmn	r0, #1
	beq	.L145
	mov	r0, r5
	bl	VEDU_DRV_RCGetTargetFrameBits_AVBR
.L141:
	ldr	r3, [r5, #104]
	cmp	r3, #0
	beq	.L158
	ldr	r3, [r4, #432]
	add	r3, r3, #1
	cmp	r3, #22
	movls	r3, #23
	bhi	.L196
.L159:
	str	r3, [r4, #432]
	mov	r3, #0
	str	r3, [r5, #104]
.L158:
	ldr	r0, [r5, #100]
	cmp	r0, #0
	ldrne	r3, [r4, #432]
	movne	r0, #0
	addne	r3, r3, #1
	strne	r3, [r4, #432]
.L126:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L194:
	ldr	r3, [r4, #524]
	mov	r0, #0
	add	r2, r3, #128
	str	r2, [r4, #356]
	str	r3, [r4, #424]
	mov	r3, r3, lsr #6
	str	r3, [r4, #432]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L144:
	ldr	r7, [r4, #480]
	ldr	r3, [r5, #56]
	cmp	r7, #0
	str	r3, [r4, #788]
	bne	.L197
.L146:
	mov	r0, r5
	ldr	r8, [r5, #28]
	bl	VEDU_DRV_RcModifyQPForLargeFrmBits
	ldr	r9, [r4, #360]
	cmp	r8, r9
	mov	r6, r0
	bcs	.L198
	rsb	r8, r8, r9
	mov	r1, r9
	mov	r0, r8, asl #6
	sub	r0, r0, r8, asl #3
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
.L148:
	add	r6, r6, r0
	mvn	r2, #127
	ldr	r9, [r5, #64]
	cmp	r6, r2
	ldr	r10, [r4, #800]
	movlt	r6, r2
	cmp	r6, #256
	mov	r1, r9
	str	r2, [fp, #-52]
	mov	r0, r10, asl #5
	movge	r6, #256
	bl	__aeabi_uidiv
	ldr	r8, [r4, #792]
	mov	r1, r9
	str	r0, [fp, #-48]
	mov	r0, r8, asl #5
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	ldr	r1, .L200
	cmp	r8, r10
	usat	r3, #6, r3
	mov	ip, r9, lsr #4
	ldr	r2, [fp, #-52]
	add	r3, r1, r3, lsl #2
	ldr	r3, [r3, #804]
	usat	r0, #6, r0
	add	r1, r1, r0, lsl #2
	ldr	r1, [r1, #804]
	rsb	r3, r3, r1
	bls	.L149
	rsb	r1, ip, r9
	cmp	r10, r1
	bls	.L149
	mov	r1, r3, asl #3
	sub	r3, r1, r3, asl #1
.L193:
	cmp	r3, r2
	movlt	r3, r2
	cmp	r3, #256
	movge	r3, #256
	cmp	r8, r9
	add	r6, r6, r3
	bls	.L151
.L199:
	rsb	r8, r9, r8
	mov	r1, r9
	mov	r0, r8, asl #7
	sub	r0, r0, r8, asl #5
	bl	__aeabi_uidiv
.L152:
	mvn	r3, #63
	ldr	r1, [r4, #472]
	cmp	r0, r3
	ldr	r2, [r4, #476]
	movlt	r0, r3
	cmp	r0, #64
	addle	r6, r6, r0
	addgt	r6, r6, #64
	cmp	r1, r2
	bcs	.L153
	rsb	r2, r1, r2
	movw	r3, #60293
	movt	r3, 81
	cmp	r2, r3
	movls	r0, #400
	mvnhi	r0, #-2147483648
	mulls	r0, r0, r2
	bl	__aeabi_uidiv
.L156:
	mvn	r2, #31
	cmp	r0, r2
	ldr	r3, [r4, #424]
	movlt	r0, r2
	cmp	r0, #32
	addle	r6, r6, r0
	addgt	r6, r6, #32
	cmp	r7, #0
	add	r3, r6, r3
	str	r3, [r4, #424]
	beq	.L157
	ldr	r2, [r4, #356]
	cmp	r3, r2
	bcs	.L157
	ldr	r1, [r5, #68]
	cmp	r1, #1
	addhi	r3, r3, r2
	movhi	r3, r3, lsr #1
.L157:
	ldr	r1, [r5, #4]
	mov	r0, r5
	ldr	r2, [r5, #8]
	mov	r1, r1, asl #6
	cmp	r3, r1
	mov	r2, r2, asl #6
	movcc	r3, r1
	cmp	r3, r2
	movcs	r3, r2
	str	r3, [r4, #424]
	mov	r3, r3, lsr #6
	str	r3, [r4, #432]
	bl	VEDU_DRV_RCGetTimeOfP
	cmn	r0, #1
	beq	.L145
	mov	r0, r5
	bl	VEDU_DRV_RCGetTargetFrameBits
	b	.L141
.L195:
	ldr	r2, [r4, #440]
	mov	r0, #1
	ldr	r1, [r4, #444]
	cmp	r2, #8
	str	r3, [r4, #468]
	str	r0, [r4, #464]
	movge	r3, r2
	movlt	r3, #8
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r4, #460]
	ldr	r8, [r5, #68]
	mov	r3, #1
	str	r3, [r4, #480]
	cmp	r8, r0
	streq	r8, [r4, #460]
	ldr	r7, [r5, #56]
	str	r7, [r4, #804]
	mov	r1, r7
	ldr	r6, [r5, #64]
	mov	r3, r6, asl #3
	mov	r0, r6
	add	r3, r3, r6, lsl #1
	mov	r3, r3, lsr #3
	str	r3, [r4, #472]
	str	r3, [r4, #476]
	bl	__aeabi_uidiv
	umull	r2, r3, r0, r8
	str	r0, [r5, #128]
	mov	r1, r2, lsr #10
	strd	r2, [r5, #120]
	orr	r1, r1, r3, asl #22
	str	r1, [r5, #144]
	str	r6, [r4, #812]
	add	r6, r5, #4608
	str	r8, [r4, #808]
	add	r6, r6, #16
	ldr	r3, [r5, #104]
	ldr	r2, .L200+4
	mov	r0, r6
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r5, #112]
	mov	r3, #0
	str	r7, [r4, #788]
	mov	r1, r3
	ldr	r7, [r2]
	str	r3, [r4, #796]
	mov	r2, #260
	str	r3, [r4, #792]
	str	r3, [r4, #800]
	blx	r7
	ldrd	r0, [r5, #120]
	mov	r3, #0
	mvn	r2, #0
	cmp	r1, r3
	cmpeq	r0, r2
	bls	.L131
	ldr	r0, [r5, #128]
	ldr	r7, [r4, #460]
.L132:
	mul	r3, r0, r7
	ldr	r1, [r4, #788]
	ldr	ip, [r4, #792]
	cmp	r1, #1
	add	ip, r3, ip
	str	ip, [r4, #792]
	str	r3, [r4, #528]
	bls	.L133
	mov	r2, r6
	mov	r3, #1
.L134:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L134
	sub	r3, r3, #2
	mla	r3, r3, r0, r0
	add	ip, ip, r3
	str	ip, [r4, #792]
.L133:
	str	ip, [r4, #800]
	mov	r0, r5
	bl	VEDU_DRV_RCGetTargetFrameBits
	ldr	r6, [r4, #428]
	mvn	r3, #0
	ldr	r1, [r4, #460]
	str	r3, [r4, #512]
	str	r3, [r4, #516]
	mov	r0, r6
	str	r6, [r4, #484]
	str	r6, [r4, #488]
	bl	__aeabi_uidiv
	movw	r3, #23592
	movt	r3, 655
	cmp	r6, r3
	strhi	r3, [r4, #428]
	str	r0, [r4, #492]
	str	r0, [r4, #496]
	str	r0, [r4, #500]
	str	r0, [r4, #504]
	str	r0, [r4, #508]
	movls	r0, #100
	ldr	r3, [r5, #16]
	mvnhi	r0, #95
	ldr	r1, [r5, #12]
	mulls	r0, r0, r6
	mul	r1, r3, r1
	add	r1, r1, r1, lsl #1
	mov	r1, r1, lsr #1
	bl	__aeabi_uidiv
	cmp	r0, #170
	bhi	.L160
	sub	r3, r0, #121
	cmp	r3, #49
	bls	.L161
	sub	r3, r0, #81
	cmp	r3, #39
	bls	.L162
	sub	r3, r0, #41
	cmp	r3, #39
	bls	.L163
	sub	r3, r0, #16
	cmp	r3, #24
	bls	.L164
	sub	r3, r0, #6
	cmp	r3, #9
	bls	.L165
	sub	r0, r0, #3
	cmp	r0, #3
	movcc	lr, #2688
	movcs	lr, #2880
	movcc	r3, #2560
	movcs	r3, #2752
	movcc	r2, #40
	movcs	r2, #43
	b	.L137
.L196:
	cmp	r3, #35
	movcs	r3, #35
	b	.L159
.L198:
	rsb	r0, r9, r8
	mov	r1, r9
	mov	r0, r0, asl #6
	bl	__aeabi_uidiv
	b	.L148
.L197:
	bl	VEDU_DRV_RCModifyQPDeltaOfIP
	ldr	r7, [r4, #480]
	b	.L146
.L149:
	cmp	r8, r10
	bcs	.L168
	add	ip, ip, r9
	cmp	r10, ip
	movcc	r3, r3, asl #2
	mvncc	r2, #127
	bcc	.L193
.L168:
	cmp	r8, r9
	mov	r3, #0
	add	r6, r6, r3
	bhi	.L199
.L151:
	rsb	r8, r8, r9
	mov	r1, r9
	mov	r0, r8, asl #6
	add	r0, r0, r8, lsl #3
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
	b	.L152
.L153:
	rsb	r2, r2, r1
	mov	r0, #400
	mul	r0, r0, r2
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
	b	.L156
.L131:
	ldr	r1, [r5, #68]
	ldr	r7, [r4, #460]
	sub	r1, r1, #1
	add	r1, r1, r7
	bl	__aeabi_uidiv
	b	.L132
.L160:
	mov	lr, #576
	mov	r3, #448
	mov	r2, #7
.L137:
	ldr	ip, [r4, #528]
	mvn	r0, #0
	ldr	r1, [r4, #468]
	str	r3, [r4, #424]
	add	r3, r5, #180
	str	lr, [r4, #356]
	rsb	r2, r1, r2
	str	r2, [r4, #432]
	add	r1, r5, #212
	str	r2, [r4, #436]
	str	ip, [r5, #152]
	str	ip, [r5, #156]
	str	r0, [r5, #216]
	str	r0, [r5, #220]
	ldr	r6, [r5, #68]
	ldr	r2, [r4, #532]
.L138:
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L138
	add	lr, r5, #244
	add	ip, r5, #276
	add	r0, r5, #316
	add	r1, r5, #348
	mov	r3, #8
	mov	r2, #0
.L139:
	subs	r3, r3, #1
	str	r2, [lr, #4]!
	str	r2, [ip, #4]!
	str	r2, [r0, #4]!
	str	r2, [r1, #4]!
	bne	.L139
	cmp	r6, #1000
	ldrd	r8, [r5, #120]
	add	r2, r5, #400
	str	r3, [r5, #384]
	movcc	r1, r6
	movcs	r1, #1000
	cmp	r1, #0
	str	r1, [r5, #388]
	mov	r0, #100
	strd	r8, [r2, #-8]
	strd	r8, [r2]
	str	r0, [r5, #316]
	str	r0, [r5, #312]
	ble	.L141
	add	r2, r5, #444
	mov	r0, r3
.L142:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r1, r3
	bne	.L142
	b	.L141
.L162:
	mov	lr, #1408
	mov	r3, #1280
	mov	r2, #20
	b	.L137
.L161:
	mov	lr, #1088
	mov	r3, #960
	mov	r2, #15
	b	.L137
.L145:
	mvn	r0, #0
	b	.L126
.L163:
	mov	lr, #1728
	mov	r3, #1600
	mov	r2, #25
	b	.L137
.L164:
	mov	lr, #2048
	mov	r3, #1920
	mov	r2, #30
	b	.L137
.L165:
	mov	lr, #2560
	mov	r3, #2432
	mov	r2, #38
	b	.L137
.L201:
	.align	2
.L200:
	.word	.LANCHOR0
	.word	venc_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VENC_DRV_RcOpenOneFrm, .-VENC_DRV_RcOpenOneFrm
	.align	2
	.global	VENC_DRV_EflRcAverage
	.type	VENC_DRV_EflRcAverage, %function
VENC_DRV_EflRcAverage:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	cmp	r1, #0
	ble	.L208
	sub	ip, r0, #4
	mov	r0, #0
	mov	r3, r0
	mov	lr, r1
.L206:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	cmp	r2, #0
	add	r0, r0, r2
	subeq	lr, lr, #1
	cmp	r3, r1
	bne	.L206
.L204:
	cmp	lr, #0
	bne	.L211
	mov	r0, lr
	ldmfd	sp, {fp, sp, pc}
.L211:
	mov	r1, lr
	bl	__aeabi_idiv
	ldmfd	sp, {fp, sp, pc}
.L208:
	mov	lr, r1
	mov	r0, #0
	b	.L204
	UNWIND(.fnend)
	.size	VENC_DRV_EflRcAverage, .-VENC_DRV_EflRcAverage
	.align	2
	.global	VENC_DRV_RcCloseOneFrm
	.type	VENC_DRV_RcCloseOneFrm, %function
VENC_DRV_RcCloseOneFrm:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	clz	ip, r1
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	ip, ip, lsr #5
	beq	.L247
	cmp	r3, #0
	cmpne	r2, #0
	beq	.L247
	ldr	r0, [r0, #88]
	cmp	r0, #0
	bne	.L214
	ldr	r0, [r4, #92]
	cmp	r0, #0
	bne	.L214
	str	r0, [r4, #20]
	ldr	r5, [r4, #60]
	ldr	lr, [r2]
	rsb	lr, r5, lr
	str	lr, [r2]
	ldr	r2, [r4, #72]
	cmp	r2, #0
	ldreq	r2, [r3]
	movne	r2, r0
	addeq	r2, r2, #1
	cmp	ip, #0
	str	r2, [r3]
	ldr	r6, [r4, #28]
	bne	.L223
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L223
	ldr	r2, [r1, #12]
	ldr	ip, [r1, #16]
	cmp	r2, ip
	ldrhi	ip, [r1, #8]
	ldrls	r2, [r1, #8]
	ldrhi	r0, [r3, ip, asl #2]
	addhi	r3, r3, ip, lsl #2
	addls	r3, r3, r2, lsl #2
	rsbhi	r0, r0, r2
	add	r0, r0, r6
	str	r0, [r1, #12]
	str	r6, [r3]
	ldmib	r1, {r2, r3}
	add	r3, r3, #1
	str	r3, [r1, #8]
	cmp	r3, r2
	rsbcs	r3, r2, r3
	strcs	r3, [r1, #8]
	ldr	r6, [r4, #28]
.L223:
	ldr	r3, [r4, #108]
	add	r5, r4, #4096
	cmp	r3, #1
	ldr	r1, [r5, #388]
	add	r3, r4, #4416
	ldr	lr, [r5, #384]
	ldreq	r2, [r5, #396]
	add	r3, r3, #52
	ldrne	r2, [r5, #368]
	ldr	ip, [r5, #380]
	ldr	r0, [r5, #376]
	str	r1, [r5, #392]
	ldr	r1, [r5, #372]
	streq	r2, [r5, #368]
	cmp	r3, #0
	str	lr, [r5, #388]
	str	ip, [r5, #384]
	str	r0, [r5, #380]
	str	r1, [r5, #376]
	str	r2, [r5, #372]
	beq	.L250
	add	ip, r4, #4480
	mov	r0, #0
	add	ip, ip, #8
	mov	r1, #6
	b	.L232
.L265:
	ldr	r2, [r3, #4]!
.L232:
	cmp	r2, #0
	add	r0, r0, r2
	subeq	r1, r1, #1
	cmp	r3, ip
	bne	.L265
	cmp	r1, #0
	moveq	r0, r1
	beq	.L229
	bl	__aeabi_idiv
.L229:
	str	r0, [r5, #396]
	ldr	r3, [r4, #132]
	ldr	ip, [r4, #72]
	cmp	r3, #0
	bne	.L266
.L234:
	ldr	r3, [r5, #424]
	cmp	ip, #0
	mov	r0, #0
	str	r6, [r5, #364]
	strne	r3, [r5, #352]
	streq	r3, [r5, #356]
	ldr	r3, [r5, #428]
	str	r3, [r5, #360]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L266:
	cmp	ip, #0
	beq	.L235
	ldr	r1, [r4, #220]
	add	r3, r4, #180
	ldr	r8, [r4, #156]
	mov	r2, r6
	str	r6, [r4, #156]
	str	r1, [r4, #216]
	str	r8, [r4, #152]
	ldr	r1, [r5, #432]
	str	r1, [r4, #220]
.L236:
	add	r0, r4, #212
	add	r8, r2, r8
	mov	r2, #0
.L239:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	add	r2, r2, r1
	bne	.L239
	ldr	lr, [r4, #388]
	mov	r7, r2, lsr #3
	ldr	r9, [r4, #384]
	mov	r8, r8, lsr #1
	sub	r0, lr, #1
	add	r2, r9, #1
	add	r9, r9, #112
	mov	r3, r0, asr #31
	cmp	lr, r2
	umull	r0, r1, r7, r0
	movle	r2, #0
	str	r6, [r4, r9, asl #2]
	adds	r0, r0, r8
	str	r2, [r4, #384]
	mla	r1, r7, r3, r1
	adc	r1, r1, #0
	cmp	lr, #0
	ble	.L252
	add	r8, r4, #444
	mov	r2, #0
	mov	r3, #0
	mov	r7, #0
.L243:
	ldr	r9, [r8, #4]!
	add	r7, r7, #1
	adds	r2, r2, r9
	adc	r3, r3, #0
	cmp	r7, lr
	bne	.L243
.L242:
	add	r4, r4, #400
	strd	r2, [r4, #-8]
	strd	r0, [r4]
	b	.L234
.L235:
	add	r3, r4, #180
	add	r8, r4, #184
	add	r7, r4, #248
	add	lr, r4, #244
	add	ip, r4, #280
	add	r0, r4, #276
	mov	r1, r3
	mov	r2, #7
.L237:
	ldr	r9, [r8, #4]!
	subs	r2, r2, #1
	str	r9, [r1, #4]!
	ldr	r9, [r7, #4]!
	str	r9, [lr, #4]!
	ldr	r9, [ip, #4]!
	str	r9, [r0, #4]!
	bne	.L237
	ldr	r1, [r4, #36]
	add	lr, r4, #320
	ldr	r7, [r4, #40]
	add	ip, r4, #316
	add	r0, r4, #352
	str	r6, [r4, #212]
	str	r1, [r4, #276]
	add	r1, r4, #348
	str	r7, [r4, #308]
.L238:
	ldr	r6, [lr, #4]!
	add	r2, r2, #1
	cmp	r2, #7
	str	r6, [ip, #4]!
	ldr	r6, [r0, #4]!
	str	r6, [r1, #4]!
	bne	.L238
	ldr	r0, [r4, #48]
	ldr	r1, [r4, #44]
	ldr	r6, [r4, #28]
	ldr	r8, [r4, #152]
	ldr	r2, [r4, #156]
	ldr	ip, [r4, #72]
	str	r0, [r4, #348]
	str	r1, [r4, #380]
	b	.L236
.L250:
	mov	r0, r3
	b	.L229
.L247:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L214:
	ldr	r3, [r4, #76]
	ldr	r2, [r4, #80]
	clz	r3, r3
	ldr	r0, [r4, #84]
	cmp	r2, #0
	mov	r3, r3, lsr #5
	str	r3, [r4, #76]
	ldr	r3, [r4, #20]
	subne	r2, r2, #1
	moveq	r2, #2
	sub	r0, r0, #1
	cmp	r3, #0
	orrne	ip, ip, #1
	str	r0, [r4, #84]
	cmp	ip, #0
	str	r2, [r4, #80]
	bne	.L218
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L218
	ldr	r2, [r1, #12]
	ldr	r0, [r1, #16]
	cmp	r2, r0
	strls	ip, [r1, #12]
	ldrhi	r0, [r1, #8]
	ldrls	r2, [r1, #8]
	ldrhi	ip, [r3, r0, asl #2]
	addhi	r3, r3, r0, lsl #2
	addls	r3, r3, r2, lsl #2
	rsbhi	r2, ip, r2
	strhi	r2, [r1, #12]
	mov	r2, #0
	str	r2, [r3]
	ldmib	r1, {r2, r3}
	add	r3, r3, #1
	str	r3, [r1, #8]
	cmp	r3, r2
	rsbcs	r3, r2, r3
	strcs	r3, [r1, #8]
.L218:
	add	r3, r4, #4096
	mvn	r0, #0
	ldr	r3, [r3, #364]
	str	r3, [r4, #28]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L252:
	mov	r2, #0
	mov	r3, #0
	b	.L242
	UNWIND(.fnend)
	.size	VENC_DRV_RcCloseOneFrm, .-VENC_DRV_RcCloseOneFrm
	.align	2
	.global	VEDU_DRV_RCUpdateInfo
	.type	VEDU_DRV_RCUpdateInfo, %function
VEDU_DRV_RCUpdateInfo:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r5, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r4, r5, #4096
	ldr	r8, [r4, #520]
	cmp	r8, #0
	beq	.L270
	ldr	r3, [r4, #796]
	cmp	r3, #0
	ldreq	r3, [r4, #788]
	sub	r3, r3, #1
	str	r3, [r4, #796]
	ldr	r3, [r5, #72]
	cmp	r3, #0
	beq	.L275
	ldr	r2, [r5, #56]
	ldr	r3, [r5, #68]
	cmp	r3, r2, asl #1
	bls	.L275
	ldr	r3, [r5, #132]
	cmp	r3, #0
	beq	.L298
.L297:
	cmp	r8, #0
	beq	.L273
.L275:
	ldr	r1, [r4, #796]
	ldr	r0, [r4, #428]
	add	r1, r1, #1152
	ldr	r2, [r4, #476]
	add	r1, r1, #4
	add	r2, r0, r2
	ldr	r3, [r5, r1, asl #2]
	rsb	r3, r3, r2
	b	.L278
.L270:
	ldr	r3, [r5, #72]
	cmp	r3, #0
	bne	.L299
.L273:
	ldr	r3, [r4, #476]
	ldr	r0, [r4, #428]
.L278:
	ldr	r7, [r4, #788]
	ldr	r2, [r4, #804]
	ldr	r6, [r5, #28]
	cmp	r7, r2
	add	r3, r3, r6
	rsb	r3, r0, r3
	str	r3, [r4, #476]
	beq	.L300
	ldr	r9, [r5, #64]
	ldr	r1, [r5, #56]
	mov	r0, r9
	bl	__aeabi_uidiv
	add	r3, r5, #4608
	add	r2, r5, #4864
	add	r3, r3, #12
	add	r2, r2, #16
.L279:
	str	r0, [r3, #4]!
	cmp	r3, r2
	bne	.L279
	mov	r1, #0
	mov	r2, #1
	mov	r3, r1
	str	r9, [r4, #792]
	str	r7, [r4, #804]
	str	r1, [r4, #796]
.L284:
	add	r5, r5, r3, lsl #2
	cmp	r8, #0
	add	r5, r5, #4096
	streq	r9, [r4, #800]
	cmp	r7, r2
	add	r9, r9, r6
	ldr	r3, [r5, #528]
	rsb	r9, r3, r9
	movls	r3, #0
	str	r9, [r4, #792]
	str	r6, [r5, #528]
	strhi	r2, [r4, #796]
	strls	r3, [r4, #796]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L299:
	ldr	r2, [r5, #56]
	ldr	r3, [r5, #68]
	cmp	r3, r2, asl #1
	bls	.L273
	ldr	r3, [r5, #132]
	cmp	r3, #0
	bne	.L297
.L298:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L300:
	ldr	r3, [r4, #796]
	ldr	r9, [r4, #792]
	add	r2, r3, #1
	b	.L284
	UNWIND(.fnend)
	.size	VEDU_DRV_RCUpdateInfo, .-VEDU_DRV_RCUpdateInfo
	.align	2
	.global	VEDU_DRV_RCIsNeedRecoding
	.type	VEDU_DRV_RCIsNeedRecoding, %function
VEDU_DRV_RCIsNeedRecoding:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	beq	.L309
	ldr	r3, [r0, #96]
	cmp	r3, #0
	bne	.L315
	ldr	r3, [r0, #88]
	cmp	r3, #0
	addne	r3, r0, #4096
	bne	.L304
	ldr	r3, [r0, #92]
	cmp	r3, #0
	add	r3, r0, #4096
	bne	.L304
	ldr	r2, [r3, #520]
	cmp	r2, #0
	bne	.L305
	ldr	r2, [r0, #132]
	cmp	r2, #0
	bne	.L305
	ldr	r2, [r0, #72]
	cmp	r2, #0
	bne	.L316
	ldr	r1, [r3, #428]
	ldr	r2, [r0, #28]
	cmp	r2, r1, asl #1
	movhi	r2, #1
	movls	r2, #0
.L307:
	cmp	r2, #1
	beq	.L304
.L309:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L304:
	ldr	r0, [r3, #520]
	add	r0, r0, #1
	str	r0, [r3, #520]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
.L316:
	ldr	r2, [r3, #428]
	ldr	r1, [r0, #28]
	add	r2, r2, r2, lsl #1
	cmp	r1, r2, lsr #1
	movhi	r2, #1
	movls	r2, #0
	b	.L307
.L315:
	add	r3, r0, #4096
.L305:
	mov	r2, #0
	mvn	r0, #0
	str	r2, [r3, #520]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCIsNeedRecoding, .-VEDU_DRV_RCIsNeedRecoding
	.align	2
	.global	VEDU_DRV_RCStartQPChange
	.type	VEDU_DRV_RCStartQPChange, %function
VEDU_DRV_RCStartQPChange:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	beq	.L324
	ldr	r3, [r0, #88]
	add	lr, r0, #4096
	cmp	r3, #0
	ldr	r3, [lr, #428]
	beq	.L327
.L319:
	ldr	r1, [lr, #520]
	ldr	r2, [r0, #24]
	mul	r1, r2, r1
.L321:
	cmp	r1, r3
	mov	r2, #0
	bcc	.L322
	mov	ip, #88
.L323:
	mul	r3, ip, r3
	add	r2, r2, #1
	mov	r3, r3, lsr #6
	cmp	r1, r3
	bcs	.L323
	mov	r2, r2, asl #6
.L322:
	ldr	ip, [r0, #4]
	ldr	r3, [lr, #424]
	ldr	r1, [r0, #8]
	add	r2, r2, r3
	mov	r0, ip, asl #6
	cmp	r2, r0
	mov	r1, r1, asl #6
	movcc	r2, r0
	cmp	r2, r1
	movcs	r2, r1
	cmp	r3, r2
	str	r2, [lr, #524]
	movne	r0, #0
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L327:
	ldr	r2, [r0, #92]
	cmp	r2, #0
	ldreq	r1, [r0, #28]
	beq	.L321
	b	.L319
.L324:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VEDU_DRV_RCStartQPChange, .-VEDU_DRV_RCStartQPChange
	.align	2
	.global	VENC_DRV_CalRCRatio
	.type	VENC_DRV_CalRCRatio, %function
VENC_DRV_CalRCRatio:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, r1
	bhi	.L331
	rsb	r0, r0, r1
	mov	r3, #100
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
.L331:
	rsb	r0, r1, r0
	mov	r3, #100
	mul	r0, r3, r0
	bl	__aeabi_uidiv
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VENC_DRV_CalRCRatio, .-VENC_DRV_CalRCRatio
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	MaxIPropDeltaQP, %object
	.size	MaxIPropDeltaQP, 208
MaxIPropDeltaQP:
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	10
	.word	9
	.word	9
	.word	8
	.word	8
	.word	7
	.word	7
	.word	6
	.word	6
	.word	5
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	s32QPOffsetTab3.4539, %object
	.size	s32QPOffsetTab3.4539, 64
s32QPOffsetTab3.4539:
	.word	14
	.word	15
	.word	16
	.word	18
	.word	20
	.word	22
	.word	25
	.word	28
	.word	32
	.word	36
	.word	40
	.word	44
	.word	50
	.word	56
	.word	64
	.word	72
	.type	s32PercentTab0.4538, %object
	.size	s32PercentTab0.4538, 400
s32PercentTab0.4538:
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	99
	.word	95
	.word	90
	.word	85
	.word	80
	.word	75
	.word	72
	.word	69
	.word	66
	.word	64
	.word	62
	.word	60
	.word	58
	.word	57
	.word	56
	.word	55
	.word	54
	.word	53
	.word	52
	.word	51
	.word	50
	.word	49
	.word	48
	.word	47
	.word	47
	.word	46
	.word	46
	.word	45
	.word	45
	.word	44
	.word	44
	.word	43
	.word	43
	.word	43
	.word	42
	.word	42
	.word	42
	.word	41
	.word	41
	.word	41
	.word	40
	.word	40
	.word	40
	.word	39
	.word	39
	.word	39
	.word	38
	.word	38
	.word	38
	.word	37
	.word	37
	.word	37
	.word	37
	.word	37
	.word	37
	.word	37
	.word	36
	.word	36
	.word	36
	.word	36
	.word	36
	.word	36
	.word	36
	.word	35
	.word	35
	.word	35
	.word	34
	.word	34
	.word	34
	.word	34
	.word	34
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	33
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.word	32
	.type	s32QPOffsetTab2.4560, %object
	.size	s32QPOffsetTab2.4560, 64
s32QPOffsetTab2.4560:
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	13
	.word	14
	.word	16
	.word	18
	.word	20
	.word	22
	.word	25
	.word	28
	.word	32
	.word	36
	.type	s32PercentTab1.4559, %object
	.size	s32PercentTab1.4559, 68
s32PercentTab1.4559:
	.word	5
	.word	5
	.word	28
	.word	40
	.word	50
	.word	57
	.word	64
	.word	70
	.word	76
	.word	81
	.word	85
	.word	89
	.word	92
	.word	95
	.word	97
	.word	99
	.word	100
	.type	TabLnx, %object
	.size	TabLnx, 256
TabLnx:
	.word	0
	.word	-1216
	.word	-972
	.word	-830
	.word	-729
	.word	-651
	.word	-587
	.word	-533
	.word	-486
	.word	-445
	.word	-408
	.word	-374
	.word	-344
	.word	-316
	.word	-290
	.word	-265
	.word	-243
	.word	-221
	.word	-201
	.word	-182
	.word	-164
	.word	-147
	.word	-131
	.word	-115
	.word	-100
	.word	-86
	.word	-72
	.word	-59
	.word	-46
	.word	-34
	.word	-22
	.word	-11
	.word	0
	.word	10
	.word	21
	.word	31
	.word	41
	.word	50
	.word	60
	.word	69
	.word	78
	.word	86
	.word	95
	.word	103
	.word	111
	.word	119
	.word	127
	.word	134
	.word	142
	.word	149
	.word	156
	.word	163
	.word	170
	.word	177
	.word	183
	.word	190
	.word	196
	.word	202
	.word	208
	.word	214
	.word	220
	.word	226
	.word	232
	.word	237
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"u32BitsPerGop > 0xffffffff!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
