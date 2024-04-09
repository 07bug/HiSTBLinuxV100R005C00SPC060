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
	.file	"drv_venc_hal.c"
	.text
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_ClrInt
	.type	DRV_VENC_HAL_V400R004C02_ClrInt, %function
DRV_VENC_HAL_V400R004C02_ClrInt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L11
	cmp	r0, #1
	ldr	r3, [r3]
	beq	.L3
	bcc	.L4
	cmp	r0, #2
	bne	.L10
	ldr	r2, [r3, #12]
	orr	r2, r2, #134217728
	str	r2, [r3, #12]
	ldmfd	sp, {fp, sp, pc}
.L10:
	mvn	r2, #0
	str	r2, [r3, #12]
	ldmfd	sp, {fp, sp, pc}
.L4:
	ldr	r2, [r3, #12]
	orr	r2, r2, #1
	str	r2, [r3, #12]
	ldmfd	sp, {fp, sp, pc}
.L3:
	ldr	r2, [r3, #12]
	orr	r2, r2, #1024
	str	r2, [r3, #12]
	ldmfd	sp, {fp, sp, pc}
.L12:
	.align	2
.L11:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_ClrInt, .-DRV_VENC_HAL_V400R004C02_ClrInt
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_DisableInt
	.type	DRV_VENC_HAL_V400R004C02_DisableInt, %function
DRV_VENC_HAL_V400R004C02_DisableInt:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L22
	cmp	r0, #1
	ldr	r3, [r3]
	beq	.L15
	bcc	.L16
	cmp	r0, #2
	bne	.L21
	ldr	r2, [r3, #4]
	bic	r2, r2, #134217728
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L21:
	mov	r2, #0
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L16:
	ldr	r2, [r3, #4]
	bic	r2, r2, #1
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L15:
	ldr	r2, [r3, #4]
	bic	r2, r2, #1024
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L23:
	.align	2
.L22:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_DisableInt, .-DRV_VENC_HAL_V400R004C02_DisableInt
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu
	.type	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu, %function
DRV_VENC_HAL_V400R004C02_ReadReg_Smmu:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L29
	cmp	r0, #0
	ldr	r3, [r3]
	ldmeqfd	sp, {fp, sp, pc}
	add	r3, r3, #61440
	mvn	r1, #0
	ldr	r2, [r3, #40]
	and	r2, r2, #1
	str	r2, [r0]
	ldr	r2, [r3, #40]
	ubfx	r2, r2, #1, #1
	str	r2, [r0, #4]
	ldr	r2, [r3, #40]
	ubfx	r2, r2, #2, #1
	str	r2, [r0, #8]
	ldr	r2, [r3, #40]
	ubfx	r2, r2, #3, #1
	str	r2, [r0, #12]
	ldr	r2, [r3, #24]
	and	r2, r2, #1
	str	r2, [r0, #16]
	ldr	r2, [r3, #24]
	ubfx	r2, r2, #1, #1
	str	r2, [r0, #20]
	ldr	r2, [r3, #24]
	ubfx	r2, r2, #2, #1
	str	r2, [r0, #24]
	ldr	r2, [r3, #24]
	ubfx	r2, r2, #3, #1
	str	r2, [r0, #28]
	ldr	r2, [r3, #864]
	str	r2, [r0, #32]
	ldr	r2, [r3, #848]
	str	r2, [r0, #40]
	ldr	r2, [r3, #832]
	str	r2, [r0, #36]
	ldr	r2, [r3, #816]
	str	r2, [r0, #44]
	str	r1, [r3, #28]
	ldmfd	sp, {fp, sp, pc}
.L30:
	.align	2
.L29:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_ReadReg_Smmu, .-DRV_VENC_HAL_V400R004C02_ReadReg_Smmu
	.global	__aeabi_uidiv
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_ReadReg
	.type	DRV_VENC_HAL_V400R004C02_ReadReg, %function
DRV_VENC_HAL_V400R004C02_ReadReg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L38
	subs	r4, r0, #0
	ldmia	r3, {r5, ip}
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, [r5]
	and	r3, r3, #1
	str	r3, [r4, #8]
	ldr	r3, [r5]
	ubfx	r3, r3, #1, #1
	str	r3, [r4, #12]
	ldr	r2, [r5]
	ubfx	r2, r2, #3, #1
	str	r2, [r4, #16]
	ldr	r1, [r5]
	orrs	r3, r2, r3
	ubfx	r3, r1, #27, #1
	str	r3, [r4]
	ldr	r3, [r5]
	ubfx	r3, r3, #10, #1
	str	r3, [r4, #4]
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r7, r5, #4096
	ldr	r0, [r7, #1644]
	bic	r0, r0, #-67108864
	str	r0, [r4, #24]
	ldr	r3, [ip, #4]
	cmp	r3, #0
	beq	.L37
	ldr	r3, [r7, #3712]
	mov	r3, r3, asl #3
	str	r3, [r4, #20]
	ldr	r6, [r7, #1540]
	ldr	r3, [r7, #1572]
	ubfx	r6, r6, #0, #19
	ubfx	r3, r3, #0, #17
	add	r6, r6, r3
	str	r6, [r4, #28]
	ldr	r3, [ip, #16]
	ldr	r1, [ip, #12]
	add	r3, r3, #7
	add	r1, r1, #7
	mov	r3, r3, lsr #3
	mov	r1, r1, lsr #3
	mul	r1, r1, r3
	bl	__aeabi_uidiv
	str	r0, [r4, #24]
	ldr	r3, [r7, #3720]
	str	r3, [r4, #32]
	ldr	r3, [r7, #3724]
	str	r3, [r4, #36]
.L36:
	add	r3, r6, #3
	cmp	r6, #0
	movlt	r6, r3
	mov	r6, r6, asr #2
	str	r6, [r4, #28]
	ldr	r3, [r5, #1808]
	bic	r3, r3, #-33554432
	str	r3, [r4, #40]
	ldr	r3, [r5, #1812]
	bic	r3, r3, #-33554432
	str	r3, [r4, #44]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L37:
	add	r8, r5, #8192
	ldr	r3, [r8, #132]
	mov	r3, r3, asl #3
	str	r3, [r4, #20]
	ldr	r3, [r7, #1544]
	ldr	r1, [r7, #1548]
	ldr	r6, [r7, #1576]
	ubfx	r2, r3, #0, #19
	ubfx	r3, r1, #0, #19
	add	r3, r2, r3
	ubfx	r6, r6, #0, #19
	add	r6, r3, r6
	str	r6, [r4, #28]
	ldr	r3, [ip, #16]
	ldr	r1, [ip, #12]
	add	r3, r3, #15
	add	r1, r1, #15
	mov	r3, r3, lsr #4
	mov	r1, r1, lsr #4
	mul	r1, r1, r3
	bl	__aeabi_uidiv
	str	r0, [r4, #24]
	ldr	r3, [r8, #136]
	str	r3, [r4, #32]
	ldr	r3, [r8, #140]
	str	r3, [r4, #36]
	b	.L36
.L39:
	.align	2
.L38:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_ReadReg, .-DRV_VENC_HAL_V400R004C02_ReadReg
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_CfgReg
	.type	DRV_VENC_HAL_V400R004C02_CfgReg, %function
DRV_VENC_HAL_V400R004C02_CfgReg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #84)
	sub	sp, sp, #84
	subs	r7, r0, #0
	beq	.L40
	ldr	r0, .L124
	mov	r1, r7
	ldr	r3, .L124+4
	mov	r2, #680
	ldr	r10, [r7, #676]
	ldr	r8, [r0, #4]
	ldr	r3, [r3, #4]
	ldr	r9, [r0]
	mov	r0, r8
	blx	r3
	ldr	r3, [r7, #520]
	ldr	r1, [r7, #512]
	cmp	r3, #25
	movls	r3, #0
	movls	ip, r3
	bls	.L42
	sub	r2, r3, #26
	cmp	r2, #3
	movls	r3, #1
	movls	ip, r3
	bls	.L42
	sub	r2, r3, #30
	cmp	r2, #4
	movls	r3, #2
	movls	ip, r3
	bls	.L42
	sub	r3, r3, #35
	cmp	r3, #7
	movcc	r3, #3
	movcs	r3, #4
	mov	ip, r3
.L42:
	cmp	r1, #0
	movw	r3, #2600
	mov	r2, #84
	add	r0, r8, #680
	moveq	r4, r3
	movne	r4, #0
	mla	r1, r2, ip, r4
	mov	r5, ip
	add	r1, r8, r1
	add	r1, r1, #1200
	bl	memcpy
	mov	r2, #404
	mla	r1, r2, r5, r4
	add	r0, r8, #764
	add	r1, r8, r1
	add	r1, r1, #1616
	add	r1, r1, #4
	bl	memcpy
	add	ip, r4, r5, lsl #5
	add	ip, r8, ip
	add	lr, r8, #1168
	add	ip, ip, #3632
	add	ip, ip, #8
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ldr	r3, [r7, #4]
	cmp	r3, #0
	bne	.L120
	ldr	r3, .L124+8
	add	r2, r8, #844
	ldr	r5, [fp, #-48]
	add	r0, r3, #160
	str	r2, [fp, #-120]
.L43:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L43
	ldr	r3, .L124+12
	add	r2, r8, #1004
	add	r0, r3, #160
.L44:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L44
	mov	r2, #7
	mov	r3, #4
	mov	r1, #9
	str	r3, [r8, #780]
	str	r2, [r8, #804]
	mov	r3, #32
	str	r2, [r8, #808]
	str	r3, [r8, #1196]
	mov	r3, #0
	str	r2, [r8, #812]
	mov	r2, #14
	str	r3, [r8, #784]
	str	r3, [r8, #788]
	str	r3, [r8, #792]
	str	r3, [r8, #796]
	str	r3, [r8, #800]
	mov	r3, #11
	str	r2, [r8, #824]
	mov	r2, #25
	str	r3, [r8, #820]
	mov	r3, #18
	str	r5, [fp, #-48]
	str	r3, [r8, #828]
	mov	r3, #255
	str	r1, [r8, #816]
	str	r2, [r8, #832]
	str	r3, [r8, #836]
	str	r3, [r8, #840]
	str	r3, [r8, #844]
.L45:
	ldr	r3, [r7, #40]
	add	r4, r8, #4096
	ldr	r2, [r7, #12]
	cmp	r3, #0
	beq	.L48
	cmp	r2, #1920
	movcs	r3, #3
	strcs	r3, [r4, #2304]
	bcs	.L48
	cmp	r2, #720
	movcs	r3, #2
	movcc	r3, #1
	str	r3, [r4, #2304]
.L48:
	ldmib	r7, {r2, r3}
	cmp	r2, #0
	bne	.L51
	cmp	r3, #3
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #2316]
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r4, #2312]
	moveq	r3, #7
	movne	r3, #5
	str	r3, [r4, #2308]
.L53:
	ldr	r3, [r7, #12]
	sub	r3, r3, #128
	cmp	r3, #127
	bhi	.L54
	ldr	r3, [r7, #4]
	cmp	r3, #0
	bne	.L54
	mov	r2, #28
	str	r2, [r7, #528]
	str	r2, [r7, #524]
	str	r2, [r7, #520]
	str	r3, [r8, #780]
	str	r3, [r7, #20]
	str	r3, [r4, #3740]
	str	r3, [r4, #3448]
.L54:
	ldr	r1, [r7, #40]
	mov	r2, #11
	mov	r3, #0
	bfc	r3, #0, #1
	bfi	r2, r1, #10, #1
	orr	r3, r3, #6
	bfc	r2, #16, #1
	mov	r1, #0
	bfc	r2, #17, #1
	bfc	r1, #0, #9
	orr	r2, r2, #134217728
	bfc	r1, #16, #9
	bfc	r2, #30, #1
	str	r2, [r9, #4]
	ldr	r0, [r7, #4]
	mov	r2, #0
	ldr	lr, [r4, #2416]
	subs	ip, r0, #2
	movne	ip, #1
	cmp	r0, #2
	ldr	r0, [r7, #40]
	bfi	r3, ip, #3, #2
	ldr	ip, [r4, #3788]
	bfi	r3, r0, #5, #1
	ldr	r0, [r4, #3784]
	bfi	r3, ip, #6, #1
	ldr	ip, [r7, #512]
	bfi	r3, r0, #7, #1
	bfc	r3, #8, #1
	clz	r0, ip
	bfc	r3, #24, #1
	mov	r0, r0, lsr #5
	bfi	r3, lr, #9, #1
	bfi	r3, r0, #10, #2
	ldr	r0, [r4, #2316]
	bfi	r3, r0, #12, #1
	ldr	r0, [r4, #2312]
	bfi	r3, ip, #16, #1
	movne	ip, r2
	orr	r3, r3, #131072
	moveq	ip, #2
	bfi	r3, r0, #18, #2
	ldr	r0, [r7, #44]
	bfc	r3, #21, #1
	bfc	r3, #22, #1
	bfc	r3, #25, #1
	bfi	r3, ip, #26, #2
	bfi	r3, r0, #28, #2
	mov	r0, r2
	bfc	r3, #30, #1
	bfc	r0, #0, #5
	bfc	r3, #31, #1
	str	r3, [r9, #20]
	str	r1, [r10, #512]
	mov	r3, r2
	ldr	r1, [r7, #20]
	bfc	r0, #5, #5
	bfi	r2, r1, #17, #1
	ldr	r1, [r7, #28]
	bfc	r2, #16, #1
	bfi	r2, r1, #0, #16
	str	r2, [r10, #516]
	ldr	ip, [r7, #520]
	mov	r2, r3
	ldr	r1, [r4, #3448]
	bfi	r2, r3, #0, #1
	bfi	r0, ip, #10, #6
	bfi	r2, r3, #1, #1
	ldr	ip, [r4, #3432]
	bfi	r0, r1, #18, #1
	mov	r1, r3
	bfi	r1, r3, #8, #2
	bfi	r2, r3, #2, #1
	bfi	r1, r3, #4, #4
	bfi	r0, ip, #19, #1
	bfi	r1, r3, #0, #4
	str	r0, [r9, #32]
	bfi	r2, r3, #3, #1
	str	r3, [r9, #36]
	orr	r2, r2, #458752
	str	r3, [r9, #40]
	mov	r0, r3
	str	r1, [r10, #520]
	ldr	ip, [r4, #3892]
	ldr	r1, [r4, #3896]
	bfi	r2, ip, #19, #2
	bfi	r2, r1, #21, #1
	mov	r1, r3
	bfi	r2, r3, #23, #1
	str	r2, [r9, #48]
	ldr	ip, [r7, #16]
	bfi	r1, r3, #16, #9
	ldr	r2, [r7, #12]
	bfi	r1, r3, #0, #9
	sub	r3, ip, #1
	bfi	r0, r3, #16, #13
	sub	r3, r2, #1
	bfi	r0, r3, #0, #13
	str	r0, [r10]
	str	r1, [r9, #56]
	mov	r3, #0
	ldr	r2, [r4, #3900]
	str	r2, [r9, #60]
	ldr	r1, [r4, #3800]
	ldr	r2, [r4, #3804]
	bfi	r3, r1, #4, #4
	bfi	r3, r2, #0, #4
	str	r3, [r9, #64]
	ldr	r3, [r7, #4]
	cmp	r3, #2
	beq	.L121
	cmp	r3, #0
	moveq	r3, #15
	moveq	r6, #0
	bfieq	r6, r3, #16, #6
	moveq	r3, #31
	bfieq	r6, r3, #0, #7
.L59:
	mov	r2, #3
	mov	r3, #0
	bfi	r3, r2, #0, #3
	mov	r1, #1
	bfi	r3, r1, #3, #2
	str	r6, [r10, #16]
	bfi	r3, r2, #5, #3
	str	r2, [r10, #20]
	bfi	r3, r2, #8, #3
	mov	r1, #1
	str	r1, [r10, #524]
	mov	ip, #0
	str	r3, [r9, #100]
	mov	r1, ip
	ldr	r3, [r7, #172]
	mov	r0, ip
	str	r3, [r10, #128]
	mov	r3, ip
	ldr	lr, [r7, #68]
	bfc	r3, #0, #1
	bfc	r3, #1, #1
	bfc	r3, #2, #1
	str	lr, [r10, #132]
	bfc	r3, #3, #3
	ldr	lr, [r7, #72]
	str	lr, [r10, #136]
	ldr	lr, [r7, #76]
	str	lr, [r10, #140]
	ldr	lr, [r7, #80]
	bfi	ip, lr, #16, #16
	ldr	lr, [r7, #84]
	bfi	ip, lr, #0, #16
	str	ip, [r10, #152]
	ldr	ip, [r7, #144]
	add	ip, r7, ip, lsl #2
	ldr	ip, [ip, #132]
	str	ip, [r10, #156]
	ldr	ip, [r7, #112]
	add	ip, r7, ip, lsl #2
	ldr	ip, [ip, #88]
	str	ip, [r10, #160]
	ldr	ip, [r7, #112]
	add	ip, r7, ip, lsl #2
	ldr	ip, [ip, #96]
	str	ip, [r10, #164]
	ldr	ip, [r7, #104]
	bfi	r0, ip, #0, #16
	ldr	ip, [r7, #108]
	bfi	r0, ip, #16, #16
	str	r0, [r10, #168]
	ldr	r0, [r7, #112]
	cmp	r0, r1
	moveq	r0, #84
	movne	r0, #80
	add	r0, r7, r0
	ldr	r0, [r0, #8]
	str	r0, [r10, #184]
	ldr	r0, [r7, #112]
	cmp	r0, r1
	moveq	r0, #92
	movne	r0, #88
	add	r0, r7, r0
	ldr	r0, [r0, #8]
	str	r0, [r10, #188]
	ldr	ip, [r7, #108]
	ldr	r0, [r7, #104]
	bfi	r1, ip, #0, #16
	bfi	r1, r0, #16, #16
	str	r1, [r10, #192]
	ldr	r1, [r7, #112]
	cmp	r1, #0
	moveq	r1, #124
	movne	r1, #120
	add	r1, r7, r1
	ldr	r1, [r1, #4]
	str	r1, [r10, #208]
	ldr	r1, [r7, #112]
	add	r1, r7, r1, lsl #2
	ldr	r1, [r1, #124]
	str	r1, [r10, #212]
	ldr	r1, [r7, #112]
	add	r1, r7, r1, lsl #2
	ldr	r1, [r1, #116]
	str	r1, [r10, #48]
	ldr	r1, [r7, #112]
	cmp	r1, #0
	moveq	r1, #116
	movne	r1, #112
	add	r1, r7, r1
	ldr	r1, [r1, #4]
	str	r1, [r10, #52]
	ldr	r1, [r7, #176]
	str	r1, [r10, #56]
	ldr	r1, [r7, #308]
	str	r1, [r10, #60]
	ldr	r1, [r7, #304]
	str	r1, [r10, #64]
	ldr	r1, [r7, #60]
	cmp	r1, #2
	beq	.L60
	cmp	r1, #1
	beq	.L102
	cmp	r1, #0
	bfc	r3, #6, #4
	bfc	r3, #14, #1
	bne	.L61
	ldr	r2, [r7, #64]
	clz	r2, r2
	mov	r2, r2, lsr #5
	b	.L125
.L126:
	.align	2
.L124:
	.word	.LANCHOR0
	.word	venc_Osal_Func_Ptr_S
	.word	.LANCHOR1+476
	.word	.LANCHOR1-4
.L125:
.L62:
	bfi	r3, r2, #16, #8
	str	r3, [r10, #4]
	ldr	r1, [r4, #2308]
	mov	r2, #0
	ldr	ip, [r4, #3780]
	mov	r0, #5
	mov	r3, r2
	bfi	r2, r1, #0, #3
	bfc	r3, #0, #1
	mov	r1, #0
	bfi	r1, r0, #24, #8
	bfi	r2, ip, #4, #1
	bfi	r1, r0, #16, #8
	bfc	r3, #1, #1
	mov	ip, #15
	bfc	r2, #5, #1
	bfi	r1, ip, #8, #8
	bfc	r3, #2, #1
	mov	r0, #0
	bfi	r1, ip, #0, #8
	orr	r2, r2, #30464
	str	r1, [r10, #544]
	str	r2, [r10, #528]
	orr	r3, r3, #24
	mov	r2, #500
	str	r3, [r10, #532]
	movt	r0, 100
	mov	r3, #3
	bfi	r0, r2, #0, #16
	str	r3, [r10, #72]
	str	r0, [r10, #536]
	mov	ip, #0
	ldr	r2, [r4, #2420]
	mov	r3, ip
	ldr	r0, [r8, #684]
	mov	r1, ip
	ldr	lr, [r8, #680]
	bfi	ip, r2, #0, #1
	bfi	ip, r0, #1, #1
	mvn	r2, #127
	bfi	ip, lr, #2, #1
	mov	r0, r3
	orr	ip, ip, #8
	bfi	r0, r2, #0, #8
	bfc	ip, #4, #1
	str	ip, [r9, #352]
	ldr	ip, [r7, #672]
	bfi	r0, r2, #8, #8
	bfi	r0, r2, #16, #8
	mov	lr, #2
	str	ip, [r9, #392]
	mov	ip, r3
	ldr	r6, [r4, #3424]
	bfi	ip, r2, #0, #8
	bfi	ip, r2, #8, #8
	ldr	r2, [r8, #772]
	bfi	r3, r6, #0, #1
	ldr	r6, [r4, #3428]
	ldr	r5, [r4, #3412]
	bfi	r3, r6, #1, #1
	ldr	r6, [r4, #3444]
	bfi	r3, r2, #2, #1
	ldr	r2, [r8, #768]
	bfi	r3, r6, #4, #1
	ldr	r6, [r4, #3420]
	bfi	r3, r2, #8, #1
	ldr	r2, [r4, #3492]
	bfi	r3, r6, #9, #1
	ldr	r6, [r4, #3496]
	bfi	r3, r2, #10, #1
	ldr	r2, [r4, #3500]
	bfi	r3, r6, #11, #1
	ldr	r6, [r4, #3416]
	bfi	r3, r2, #12, #1
	ldr	r2, [r4, #3504]
	bfi	r3, r6, #13, #1
	mov	r6, #0
	bfi	r3, r5, #14, #1
	bfc	r6, #0, #1
	bfi	r3, r2, #15, #1
	str	r3, [r9, #440]
	ldr	r2, [r8, #776]
	mov	r3, #128
	str	r0, [r10, #1760]
	mov	r0, r1
	bfi	r1, r2, #1, #1
	bfi	r0, r3, #0, #10
	bfi	r1, lr, #16, #8
	bfc	r6, #1, #8
	bfi	r1, lr, #24, #8
	bfi	r0, r3, #10, #10
	str	ip, [r10, #1764]
	movw	r2, #43691
	str	r1, [r10, #540]
	movt	r2, 43690
	str	r0, [r10, #1768]
	mov	ip, #1
	str	r6, [r10, #32]
	ldr	r3, [r7, #144]
	add	r3, r3, lr
	umull	r0, r1, r3, r2
	mov	r1, r1, lsr ip
	add	r1, r1, r1, lsl #1
	rsb	r3, r1, r3
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #132]
	str	r3, [r10, #216]
	ldr	r1, [r7, #144]
	add	r1, r1, ip
	umull	r2, r3, r1, r2
	mov	r3, r3, lsr ip
	add	r3, r3, r3, lsl #1
	rsb	r3, r3, r1
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #132]
	str	r3, [r10, #220]
	mov	r3, #0
	str	ip, [r9, #492]
	str	r3, [r10, #1024]
	ldr	r3, [r7, #4]
	ldr	r0, [r7, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r6, #16
	movne	r6, #64
	mov	r1, r6
	add	r0, r0, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	str	r0, [fp, #-52]
	ldr	r0, [r7, #16]
	sub	r0, r0, #1
	add	r0, r0, r6
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-52]
	mul	r1, r3, r0
	ldr	r0, [r7, #516]
	bl	__aeabi_uidiv
	mov	r3, #0
	mov	r5, r3
	mov	r2, r3
	mov	r6, r3
	str	r3, [fp, #-52]
	str	r3, [fp, #-56]
	mov	r1, r3
	str	r3, [fp, #-60]
	mov	ip, r3
	str	r3, [fp, #-64]
	mov	lr, r3
	str	r3, [fp, #-68]
	str	r3, [fp, #-72]
	str	r3, [fp, #-76]
	str	r3, [fp, #-80]
	str	r3, [fp, #-84]
	str	r3, [fp, #-88]
	str	r3, [fp, #-92]
	str	r3, [fp, #-96]
	str	r3, [fp, #-100]
	str	r3, [fp, #-104]
	str	r3, [fp, #-108]
	str	r3, [fp, #-112]
	str	r3, [fp, #-116]
	bfi	r5, r0, #0, #20
	str	r5, [r9, #588]
	ldr	r0, [r4, #2424]
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2428]
	bfi	r3, r0, #0, #10
	str	r3, [r10, #1536]
	ldr	r0, [r8, #688]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2432]
	bfi	r3, r0, #0, #8
	str	r3, [r10, #1540]
	ldr	r0, [r4, #2436]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2440]
	bfi	r3, r0, #0, #10
	str	r3, [r10, #1544]
	ldr	r0, [r4, #2444]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r8, #692]
	bfi	r3, r0, #0, #8
	str	r3, [r10, #1548]
	ldr	r0, [r4, #2448]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2452]
	bfi	r3, r0, #0, #10
	str	r3, [r10, #1552]
	ldr	r0, [r8, #696]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r8, #700]
	bfi	r3, r0, #0, #8
	str	r3, [r10, #1556]
	ldr	r0, [r4, #2456]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r4, #2460]
	bfi	r3, r0, #0, #10
	str	r3, [r10, #1560]
	ldr	r0, [r8, #704]
	mov	r3, r2
	bfi	r3, r0, #16, #5
	ldr	r0, [r8, #708]
	bfi	r3, r0, #0, #8
	str	r3, [r10, #1564]
	ldr	r0, [r4, #2464]
	mov	r3, r6
	bfi	lr, r0, #12, #4
	ldr	r0, [r4, #2468]
	bfi	lr, r0, #8, #4
	ldr	r0, [r4, #2472]
	bfi	lr, r0, #4, #4
	ldr	r0, [r4, #2476]
	bfi	lr, r0, #0, #4
	ldr	r0, [r4, #2480]
	bfi	lr, r0, #28, #4
	ldr	r0, [r8, #712]
	bfi	lr, r0, #24, #4
	ldr	r0, [r4, #2484]
	bfi	lr, r0, #20, #4
	ldr	r0, [r4, #2488]
	bfi	lr, r0, #16, #4
	str	lr, [r10, #1568]
	ldr	r0, [r4, #2492]
	bfi	ip, r0, #12, #4
	ldr	r0, [r4, #2496]
	bfi	ip, r0, #8, #4
	ldr	r0, [r4, #2500]
	bfi	ip, r0, #4, #4
	ldr	r0, [r4, #2504]
	bfi	ip, r0, #0, #4
	ldr	r0, [r4, #2508]
	bfi	ip, r0, #28, #4
	ldr	r0, [r4, #2512]
	bfi	ip, r0, #24, #4
	ldr	r0, [r8, #716]
	bfi	ip, r0, #20, #4
	ldr	r0, [r4, #2516]
	bfi	ip, r0, #16, #4
	str	ip, [r10, #1572]
	ldr	r0, [r4, #2520]
	bfi	r1, r0, #12, #4
	ldr	r0, [r4, #2524]
	bfi	r1, r0, #8, #4
	ldr	r0, [r4, #2528]
	bfi	r1, r0, #4, #4
	ldr	r0, [r4, #2532]
	bfi	r1, r0, #0, #4
	ldr	r0, [r4, #2536]
	bfi	r1, r0, #28, #4
	ldr	r0, [r4, #2540]
	bfi	r1, r0, #24, #4
	ldr	r0, [r8, #720]
	bfi	r1, r0, #20, #4
	ldr	r0, [r4, #2544]
	bfi	r1, r0, #16, #4
	str	r1, [r10, #1576]
	ldr	r1, [r4, #2548]
	bfi	r2, r1, #12, #4
	ldr	r1, [r8, #724]
	bfi	r2, r1, #8, #4
	ldr	r1, [r4, #2552]
	bfi	r2, r1, #4, #4
	ldr	r1, [r4, #2556]
	bfi	r2, r1, #0, #4
	ldr	r1, [r4, #2560]
	bfi	r2, r1, #28, #4
	ldr	r1, [r4, #2564]
	bfi	r2, r1, #24, #4
	ldr	r1, [r4, #2568]
	bfi	r2, r1, #20, #4
	ldr	r1, [r4, #2572]
	bfi	r2, r1, #16, #4
	str	r2, [r10, #1580]
	ldr	r2, [r4, #2576]
	bfi	r3, r2, #12, #4
	ldr	r2, [r4, #2580]
	bfi	r3, r2, #8, #4
	ldr	r2, [r8, #728]
	bfi	r3, r2, #4, #4
	ldr	r2, [r4, #2584]
	bfi	r3, r2, #0, #4
	ldr	r2, [r4, #2588]
	bfi	r3, r2, #28, #4
	ldr	r2, [r4, #2592]
	bfi	r3, r2, #24, #4
	ldr	r2, [r4, #2596]
	bfi	r3, r2, #20, #4
	ldr	r2, [r4, #2600]
	bfi	r3, r2, #16, #4
	str	r3, [r10, #1584]
	ldr	r3, [r4, #2604]
	mov	r2, r6
	bfi	r2, r3, #12, #4
	ldr	r3, [r4, #2608]
	bfi	r2, r3, #8, #4
	ldr	r3, [r8, #732]
	bfi	r2, r3, #4, #4
	ldr	r3, [r4, #2612]
	bfi	r2, r3, #0, #4
	ldr	r3, [r4, #2616]
	bfi	r2, r3, #28, #4
	ldr	r3, [r4, #2620]
	bfi	r2, r3, #24, #4
	ldr	r3, [r4, #2624]
	bfi	r2, r3, #20, #4
	ldr	r3, [r4, #2628]
	bfi	r2, r3, #16, #4
	str	r2, [r10, #1588]
	ldr	r3, [r4, #2632]
	mov	r2, r6
	bfi	r2, r3, #12, #4
	ldr	r3, [r8, #736]
	bfi	r2, r3, #8, #4
	ldr	r3, [r4, #2636]
	bfi	r2, r3, #4, #4
	ldr	r3, [r4, #2640]
	bfi	r2, r3, #0, #4
	ldr	r3, [r4, #2644]
	bfi	r2, r3, #28, #4
	ldr	r3, [r4, #2648]
	bfi	r2, r3, #24, #4
	ldr	r3, [r4, #2652]
	bfi	r2, r3, #20, #4
	ldr	r3, [r4, #2656]
	bfi	r2, r3, #16, #4
	str	r2, [r10, #1592]
	ldr	r3, [r4, #2660]
	mov	r2, r6
	bfi	r2, r3, #12, #4
	ldr	r3, [r4, #2664]
	bfi	r2, r3, #8, #4
	ldr	r3, [r4, #2668]
	bfi	r2, r3, #4, #4
	ldr	r3, [r4, #2672]
	bfi	r2, r3, #0, #4
	ldr	r3, [r4, #2676]
	bfi	r2, r3, #28, #4
	ldr	r3, [r4, #2680]
	bfi	r2, r3, #24, #4
	ldr	r3, [r4, #2684]
	bfi	r2, r3, #20, #4
	ldr	r3, [r4, #2688]
	bfi	r2, r3, #16, #4
	str	r2, [r10, #1596]
	ldr	r3, [r4, #2692]
	mov	r2, #0
	bfi	r6, r3, #12, #4
	ldr	r3, [r4, #2696]
	bfi	r6, r3, #8, #4
	ldr	r3, [r4, #2700]
	bfi	r6, r3, #4, #4
	ldr	r3, [r4, #2704]
	bfi	r6, r3, #0, #4
	ldr	r3, [r4, #2708]
	bfi	r6, r3, #28, #4
	ldr	r3, [r4, #2712]
	bfi	r6, r3, #24, #4
	ldr	r3, [r4, #2716]
	bfi	r6, r3, #20, #4
	ldr	r3, [r4, #2720]
	bfi	r6, r3, #16, #4
	str	r6, [r10, #1600]
	ldr	r3, [r4, #2724]
	bfi	r2, r3, #0, #3
	ldr	r3, [r4, #2728]
	bfi	r2, r3, #3, #7
	ldr	r3, [r4, #2732]
	bfi	r2, r3, #10, #3
	ldr	r3, [r4, #2736]
	bfi	r2, r3, #13, #5
	ldr	r3, [r4, #2740]
	bfi	r2, r3, #18, #4
	ldr	r3, [r4, #2744]
	bfi	r2, r3, #22, #4
	ldr	r3, [r4, #2748]
	bfi	r2, r3, #26, #4
	str	r2, [r10, #1604]
	ldr	r3, [r4, #2752]
	mov	r2, #0
	mov	r1, r2
	mov	r0, r2
	bfi	r1, r3, #0, #3
	ldr	r3, [r4, #2756]
	mov	ip, r2
	mov	lr, r2
	bfi	r1, r3, #3, #7
	ldr	r3, [r4, #2760]
	bfi	r1, r3, #10, #3
	ldr	r3, [r4, #2764]
	bfi	r1, r3, #13, #5
	ldr	r3, [r4, #2768]
	bfi	r1, r3, #18, #4
	ldr	r3, [r4, #2772]
	bfi	r1, r3, #22, #4
	ldr	r3, [r4, #2776]
	bfi	r1, r3, #26, #4
	str	r1, [r10, #1608]
	ldr	r3, [r4, #2780]
	mov	r1, r2
	bfi	r0, r3, #0, #3
	ldr	r3, [r4, #2784]
	bfi	r0, r3, #3, #7
	ldr	r3, [r4, #2788]
	bfi	r0, r3, #10, #3
	ldr	r3, [r4, #2792]
	bfi	r0, r3, #13, #5
	ldr	r3, [r4, #2796]
	bfi	r0, r3, #18, #4
	ldr	r3, [r4, #2800]
	bfi	r0, r3, #22, #4
	ldr	r3, [r4, #2804]
	bfi	r0, r3, #26, #4
	str	r0, [r10, #1612]
	ldr	r0, [r4, #3072]
	mov	r3, r2
	bfi	ip, r0, #0, #3
	ldr	r0, [r4, #3076]
	bfi	ip, r0, #3, #7
	ldr	r0, [r4, #3080]
	bfi	ip, r0, #10, #3
	ldr	r0, [r4, #3084]
	bfi	ip, r0, #13, #5
	ldr	r0, [r4, #3088]
	bfi	ip, r0, #18, #4
	ldr	r0, [r4, #3092]
	bfi	ip, r0, #22, #4
	ldr	r0, [r4, #3096]
	bfi	ip, r0, #26, #4
	str	ip, [r10, #1616]
	ldr	ip, [r4, #3100]
	mov	r0, r2
	bfi	lr, ip, #0, #3
	ldr	ip, [r4, #3104]
	bfi	lr, ip, #3, #7
	ldr	ip, [r4, #3108]
	bfi	lr, ip, #10, #3
	ldr	ip, [r4, #3112]
	bfi	lr, ip, #13, #5
	ldr	ip, [r4, #3116]
	bfi	lr, ip, #18, #4
	ldr	ip, [r4, #3120]
	bfi	lr, ip, #22, #4
	ldr	ip, [r4, #3124]
	bfi	lr, ip, #26, #4
	str	lr, [r10, #1620]
	ldr	lr, [r8, #748]
	mov	ip, r2
	bfi	r2, lr, #0, #3
	ldr	lr, [r4, #3128]
	bfi	r2, lr, #3, #7
	ldr	lr, [r4, #3132]
	bfi	r2, lr, #10, #3
	ldr	lr, [r4, #3136]
	bfi	r2, lr, #13, #5
	ldr	lr, [r4, #3140]
	bfi	r2, lr, #18, #4
	ldr	lr, [r4, #3144]
	bfi	r2, lr, #22, #4
	ldr	lr, [r4, #3148]
	bfi	r2, lr, #26, #4
	str	r2, [r10, #1624]
	ldr	r2, [r4, #3152]
	mov	lr, r1
	bfi	r1, r2, #0, #3
	ldr	r2, [r4, #3156]
	bfi	r1, r2, #3, #7
	ldr	r2, [r4, #3160]
	bfi	r1, r2, #10, #3
	ldr	r2, [r4, #3164]
	bfi	r1, r2, #13, #5
	ldr	r2, [r4, #3168]
	bfi	r1, r2, #18, #4
	ldr	r2, [r4, #3172]
	bfi	r1, r2, #22, #4
	ldr	r2, [r4, #3176]
	bfi	r1, r2, #26, #4
	str	r1, [r10, #1628]
	ldr	r1, [r4, #2808]
	mov	r2, r3
	bfi	r3, r1, #0, #4
	ldr	r1, [r4, #2812]
	bfi	r3, r1, #4, #4
	ldr	r1, [r4, #2816]
	bfi	r3, r1, #8, #4
	ldr	r1, [r4, #2820]
	bfi	r3, r1, #12, #4
	ldr	r1, [r4, #2824]
	bfi	r3, r1, #16, #4
	ldr	r1, [r4, #2828]
	bfi	r3, r1, #20, #4
	ldr	r1, [r4, #2832]
	bfi	r3, r1, #24, #4
	ldr	r1, [r4, #2836]
	bfi	r3, r1, #28, #4
	str	r3, [r10, #1632]
	ldr	r3, [r4, #2840]
	mov	r1, r0
	bfi	r0, r3, #0, #4
	ldr	r3, [r4, #2844]
	bfi	r0, r3, #4, #4
	ldr	r3, [r4, #2848]
	bfi	r0, r3, #8, #4
	ldr	r3, [r4, #2852]
	bfi	r0, r3, #12, #4
	ldr	r3, [r4, #2856]
	bfi	r0, r3, #16, #4
	ldr	r3, [r4, #2860]
	bfi	r0, r3, #20, #4
	str	r0, [r10, #1636]
	ldr	r3, [r4, #2864]
	mov	r0, ip
	bfi	ip, r3, #0, #10
	ldr	r3, [r4, #2868]
	bfi	ip, r3, #16, #5
	str	ip, [r10, #1640]
	ldr	r3, [r8, #740]
	mov	ip, lr
	bfi	lr, r3, #0, #8
	ldr	r3, [r8, #744]
	bfi	lr, r3, #16, #5
	str	lr, [r10, #1644]
	ldr	lr, [r4, #2872]
	mov	r3, r2
	bfi	r2, lr, #0, #10
	ldr	lr, [r4, #2876]
	bfi	r2, lr, #16, #5
	str	r2, [r10, #1648]
	ldr	lr, [r4, #2880]
	mov	r2, r1
	bfi	r1, lr, #0, #8
	ldr	lr, [r4, #2884]
	bfi	r1, lr, #16, #5
	str	r1, [r10, #1652]
	ldr	r1, [r4, #2888]
	mov	lr, r0
	bfi	r0, r1, #0, #10
	ldr	r1, [r4, #2892]
	bfi	r0, r1, #16, #5
	str	r0, [r10, #1656]
	ldr	r0, [r4, #2896]
	mov	r1, ip
	bfi	ip, r0, #0, #8
	ldr	r0, [r4, #2900]
	bfi	ip, r0, #16, #5
	str	ip, [r10, #1660]
	ldr	ip, [r4, #3180]
	mov	r0, r3
	bfi	r3, ip, #0, #4
	ldr	ip, [r4, #3184]
	bfi	r3, ip, #4, #4
	ldr	ip, [r4, #3188]
	bfi	r3, ip, #8, #4
	ldr	ip, [r4, #3192]
	bfi	r3, ip, #12, #4
	ldr	ip, [r4, #3196]
	bfi	r3, ip, #16, #4
	ldr	ip, [r4, #3200]
	bfi	r3, ip, #20, #4
	str	r3, [r10, #1664]
	ldr	ip, [r8, #752]
	mov	r3, r2
	bfi	r2, ip, #0, #12
	ldr	ip, [r8, #756]
	bfi	r2, ip, #12, #12
	ldr	ip, [r4, #3204]
	bfi	r2, ip, #24, #8
	str	r2, [r10, #1668]
	ldr	r2, [r4, #3208]
	mov	ip, lr
	bfi	lr, r2, #0, #12
	ldr	r2, [r4, #3212]
	bfi	lr, r2, #12, #12
	ldr	r2, [r4, #3216]
	bfi	lr, r2, #24, #8
	str	lr, [r10, #1672]
	ldr	lr, [r8, #760]
	mov	r2, r1
	bfi	r1, lr, #0, #12
	ldr	lr, [r4, #3220]
	bfi	r1, lr, #12, #12
	ldr	lr, [r4, #3224]
	bfi	r1, lr, #24, #8
	str	r1, [r10, #1676]
	ldr	lr, [r4, #3228]
	mov	r1, r0
	mov	r5, r1
	bfi	r0, lr, #0, #8
	ldr	lr, [r4, #3232]
	bfi	r0, lr, #8, #8
	ldr	lr, [r4, #3236]
	bfi	r0, lr, #16, #8
	str	r0, [r10, #1680]
	ldr	lr, [r4, #2904]
	mov	r0, r3
	bfi	r3, lr, #0, #1
	ldr	lr, [r4, #2908]
	bfi	r3, lr, #1, #3
	ldr	lr, [r4, #2912]
	bfi	r3, lr, #4, #6
	ldr	lr, [r4, #2916]
	bfi	r3, lr, #10, #5
	ldr	lr, [r4, #2920]
	bfi	r3, lr, #15, #6
	ldr	lr, [r4, #2924]
	bfi	r3, lr, #21, #5
	str	r3, [r10, #1684]
	ldr	r3, [r4, #2928]
	mov	lr, ip
	bfi	ip, r3, #0, #1
	ldr	r3, [r4, #2932]
	bfi	ip, r3, #1, #3
	ldr	r3, [r4, #2936]
	bfi	ip, r3, #4, #6
	ldr	r3, [r4, #2940]
	bfi	ip, r3, #10, #5
	ldr	r3, [r4, #2944]
	bfi	ip, r3, #15, #6
	ldr	r3, [r4, #2948]
	bfi	ip, r3, #21, #5
	str	ip, [r10, #1688]
	ldr	ip, [r4, #2952]
	mov	r3, r2
	bfi	r2, ip, #0, #1
	ldr	ip, [r4, #2956]
	bfi	r2, ip, #1, #3
	ldr	ip, [r4, #2960]
	bfi	r2, ip, #4, #6
	ldr	ip, [r4, #2964]
	bfi	r2, ip, #10, #5
	ldr	ip, [r4, #2968]
	bfi	r2, ip, #15, #6
	ldr	ip, [r4, #2972]
	bfi	r2, ip, #21, #5
	str	r2, [r10, #1692]
	ldr	ip, [r4, #2976]
	mov	r2, r1
	bfi	r2, r1, #14, #1
	bfi	r1, ip, #0, #1
	ldr	ip, [r4, #2980]
	bfi	r2, r0, #15, #1
	bfi	r1, ip, #1, #3
	ldr	ip, [r4, #2984]
	bfi	r1, ip, #4, #6
	ldr	ip, [r4, #2988]
	bfi	r1, ip, #10, #5
	ldr	ip, [r4, #2992]
	bfi	r1, ip, #15, #6
	ldr	ip, [r4, #2996]
	bfi	r1, ip, #21, #5
	str	r1, [r10, #1696]
	ldr	ip, [r4, #3000]
	mov	r1, r0
	bfi	r1, r0, #0, #8
	bfi	r0, ip, #0, #1
	ldr	ip, [r4, #3004]
	orr	r1, r1, #65280
	bfi	r0, ip, #1, #3
	ldr	ip, [r4, #3008]
	movt	r1, 65280
	bfi	r0, ip, #4, #6
	ldr	ip, [r4, #3012]
	bfi	r0, ip, #10, #5
	ldr	ip, [r4, #3016]
	bfi	r0, ip, #15, #6
	ldr	ip, [r4, #3020]
	bfi	r0, ip, #21, #5
	str	r0, [r10, #1700]
	ldr	ip, [r4, #3024]
	mov	r0, lr
	bfi	lr, ip, #0, #1
	ldr	ip, [r4, #3028]
	bfi	lr, ip, #1, #3
	ldr	ip, [r4, #3032]
	bfi	lr, ip, #4, #6
	ldr	ip, [r4, #3036]
	bfi	lr, ip, #10, #5
	ldr	ip, [r4, #3040]
	bfi	lr, ip, #15, #6
	ldr	ip, [r4, #3044]
	bfi	lr, ip, #21, #5
	str	lr, [r10, #1704]
	ldr	lr, [r4, #3048]
	mov	ip, r3
	bfi	r3, lr, #0, #1
	ldr	lr, [r4, #3052]
	bfi	r3, lr, #1, #3
	ldr	lr, [r4, #3056]
	bfi	r3, lr, #4, #6
	ldr	lr, [r4, #3060]
	bfi	r3, lr, #10, #5
	ldr	lr, [r4, #3064]
	bfi	r3, lr, #15, #6
	ldr	lr, [r4, #3068]
	bfi	r3, lr, #21, #5
	str	r3, [r10, #1708]
	ldr	lr, [r4, #2304]
	mov	r3, r5
	bfi	r2, lr, #20, #8
	ldr	lr, [r7, #40]
	str	r1, [r10, #12]
	mov	r1, r5
	bfi	r2, lr, #28, #1
	str	r2, [r10, #8]
	ldr	r2, [r4, #3560]
	bfi	r0, r2, #0, #1
	str	r0, [r10, #1824]
	ldr	r2, [r4, #3564]
	mov	r0, r5
	bfi	ip, r2, #0, #16
	str	ip, [r10, #1828]
	ldr	ip, [r4, #3568]
	mov	r2, r5
	bfi	r3, ip, #0, #16
	str	r3, [r10, #1832]
	ldr	ip, [r4, #3572]
	mov	r3, r5
	bfi	r1, ip, #0, #16
	str	r1, [r10, #1836]
	ldr	ip, [r4, #3576]
	mov	r1, #3
	ldr	lr, [r4, #3580]
	bfi	r0, ip, #18, #9
	ldr	ip, [r4, #3584]
	bfi	r0, lr, #9, #9
	bfi	r0, ip, #0, #9
	str	r0, [r10, #1844]
	ldr	r0, [r4, #3588]
	mov	ip, #20
	ldr	lr, [r4, #3592]
	bfi	r2, r0, #16, #8
	ldr	r0, [r4, #3596]
	bfi	r2, lr, #8, #8
	bfi	r2, r0, #0, #8
	str	r2, [r10, #1848]
	ldr	r0, [r4, #3600]
	mov	r2, r5
	ldr	lr, [r4, #3604]
	bfi	r3, r0, #8, #4
	ldr	r0, [r4, #3608]
	bfi	r3, lr, #4, #4
	bfi	r3, r0, #0, #4
	mov	r0, r5
	bfi	r3, r1, #20, #8
	mov	r1, r5
	bfi	r3, ip, #12, #8
	str	r3, [r10, #1852]
	ldr	ip, [r4, #3708]
	mov	r3, r5
	bfi	r2, ip, #0, #16
	mov	ip, r5
	bfi	r2, r5, #16, #8
	bfi	r2, r5, #24, #8
	str	r2, [r10, #1856]
	ldr	lr, [r4, #3724]
	mov	r2, r5
	bfi	r0, lr, #0, #8
	ldr	lr, [r4, #3720]
	bfi	r0, lr, #8, #8
	ldr	lr, [r4, #3716]
	bfi	r0, lr, #16, #8
	ldr	lr, [r4, #3712]
	bfi	r0, lr, #24, #8
	str	r0, [r10, #1860]
	ldr	lr, [r4, #3612]
	mov	r0, r5
	bfi	r1, lr, #24, #8
	ldr	lr, [r4, #3616]
	bfi	r1, lr, #16, #8
	ldr	lr, [r4, #3620]
	bfi	r1, lr, #8, #8
	ldr	lr, [r4, #3624]
	bfi	r1, lr, #0, #8
	str	r1, [r10, #1872]
	ldr	lr, [r4, #3628]
	mov	r1, r5
	bfi	r3, lr, #0, #8
	ldr	lr, [r4, #3632]
	bfi	r3, lr, #8, #8
	ldr	lr, [r4, #3636]
	bfi	r3, lr, #16, #1
	ldr	lr, [r4, #3752]
	bfi	r3, lr, #17, #1
	str	r3, [r10, #1876]
	ldr	lr, [r4, #3640]
	mov	r3, r5
	bfi	ip, lr, #0, #16
	ldr	lr, [r4, #3644]
	bfi	ip, lr, #16, #16
	str	ip, [r10, #1880]
	ldr	lr, [r8, #1168]
	mov	ip, r5
	bfi	r2, lr, #22, #9
	ldr	lr, [r8, #1172]
	bfi	r2, lr, #17, #5
	ldr	lr, [r8, #1176]
	bfi	r2, lr, #9, #8
	ldr	lr, [r8, #1196]
	bfi	r2, lr, #0, #9
	str	r2, [r10, #1884]
	ldr	lr, [r8, #1192]
	mov	r2, r5
	bfi	r0, lr, #8, #14
	ldr	lr, [r4, #3648]
	bfi	r0, lr, #0, #8
	str	r0, [r10, #1792]
	ldr	lr, [r8, #1180]
	mov	r0, r5
	bfi	r1, lr, #16, #8
	ldr	lr, [r8, #1184]
	bfi	r1, lr, #8, #8
	ldr	lr, [r8, #1188]
	bfi	r1, lr, #0, #8
	str	r1, [r10, #1796]
	ldr	lr, [r4, #3656]
	mov	r1, r5
	bfi	r3, lr, #17, #1
	ldr	lr, [r4, #3660]
	bfi	r3, lr, #12, #2
	ldr	lr, [r4, #3664]
	bfi	r3, lr, #4, #4
	ldr	lr, [r4, #3668]
	bfi	r3, lr, #0, #4
	str	r3, [r10, #1800]
	ldr	r3, [r4, #3672]
	mov	lr, r5
	bfi	ip, r3, #0, #10
	ldr	r3, [r4, #3676]
	bfi	ip, r3, #16, #9
	str	ip, [r10, #1808]
	ldr	ip, [r4, #3680]
	mov	r3, r5
	bfi	r2, ip, #0, #10
	ldr	ip, [r4, #3684]
	bfi	r2, ip, #16, #9
	str	r2, [r10, #1812]
	ldr	r2, [r4, #3688]
	mov	ip, r5
	bfi	r0, r2, #0, #10
	ldr	r2, [r4, #3692]
	bfi	r0, r2, #16, #9
	str	r0, [r10, #1816]
	ldr	r0, [r4, #3696]
	mov	r2, r5
	bfi	r1, r0, #0, #10
	ldr	r0, [r4, #3700]
	bfi	r1, r0, #16, #9
	str	r1, [r10, #1820]
	ldr	r0, [r4, #3704]
	mov	r1, r5
	bfi	lr, r0, #0, #16
	str	lr, [r10, #1804]
	ldr	lr, [r4, #3728]
	mov	r0, r5
	bfi	r3, lr, #0, #13
	ldr	lr, [r4, #3732]
	bfi	r3, lr, #13, #1
	str	r3, [r10, #36]
	ldr	r3, [r4, #3736]
	mov	lr, #1
	bfi	ip, r3, #0, #18
	str	ip, [r10, #40]
	ldr	ip, [r4, #3740]
	mov	r3, r5
	bfi	r3, lr, #0, #8
	bfi	r2, ip, #0, #18
	str	r2, [r10, #44]
	ldr	ip, [r4, #3764]
	bfi	r3, lr, #8, #8
	ldr	r2, [r4, #3768]
	bfi	r1, ip, #16, #7
	movt	r3, 200
	bfi	r1, r2, #23, #7
	str	r1, [r9, #1792]
	ldr	r1, [r4, #3756]
	mov	r2, r5
	ldr	ip, [r4, #3760]
	bfi	r0, r1, #0, #8
	ldr	r1, [r4, #3744]
	bfi	r0, ip, #8, #8
	bfi	r0, r1, #16, #8
	str	r0, [r9, #1796]
	ldr	r1, [r4, #3748]
	ldr	r0, [r4, #3772]
	bfi	r2, r1, #12, #8
	ldr	r1, [r4, #3776]
	bfi	r2, r0, #8, #4
	bfi	r2, r1, #0, #8
	str	r2, [r9, #1800]
	str	r3, [r9, #1804]
	ldr	r2, [r7, #4]
	cmp	r2, r5
	bne	.L64
	mov	r1, #23
	mov	r3, r5
	bfi	r3, r1, #0, #5
	mov	r0, #15
	bfi	r3, r0, #5, #5
	bfi	r3, r1, #10, #5
	bfi	r3, r0, #15, #5
	bfi	r3, r2, #20, #1
	str	r3, [r10, #24]
.L65:
	mov	r1, #16
	mov	r2, #0
	mov	r3, #0
	bfc	r2, #16, #16
	bfi	r3, r1, #6, #6
	bfc	r2, #0, #16
	mov	r1, #10
	str	r2, [r10, #552]
	bfi	r3, r1, #0, #6
	mov	r2, #2
	str	r3, [r10, #556]
	mov	r3, #0
	str	r2, [r10, #548]
	ldr	r2, [r7, #528]
	ldr	r0, [r7, #524]
	bfi	r3, r2, #8, #6
	ldr	r1, [r4, #3368]
	orr	r3, r3, #64
	ldr	r2, [r4, #3340]
	bfi	r3, r0, #0, #6
	bfi	r3, r1, #16, #6
	bfi	r3, r2, #24, #4
	str	r3, [r9, #3076]
	ldr	r3, [r7, #4]
	ldr	r0, [r7, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r6, #16
	movne	r6, #64
	mov	r1, r6
	add	r0, r0, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	str	r0, [fp, #-52]
	ldr	r0, [r7, #16]
	sub	r0, r0, #1
	add	r0, r0, r6
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-52]
	mul	r1, r3, r0
	ldr	r0, [r7, #516]
	bl	__aeabi_uidiv
	mov	r3, #0
	mov	r5, r3
	mov	lr, r3
	mov	ip, r3
	mov	r1, r3
	mov	r2, r3
	str	r3, [fp, #-52]
	str	r3, [fp, #-56]
	mov	r6, r3
	bfi	r5, r0, #0, #16
	ldr	r0, [r4, #3356]
	bfi	r5, r0, #16, #6
	str	r5, [r9, #3080]
	ldr	r0, [r8, #780]
	bfi	lr, r0, #0, #6
	ldr	r0, [r4, #3348]
	bfi	lr, r0, #24, #6
	ldr	r0, [r4, #3352]
	bfi	lr, r0, #16, #6
	ldr	r0, [r4, #3360]
	bfi	lr, r0, #8, #6
	str	lr, [r9, #3084]
	ldr	r0, [r8, #796]
	bfi	ip, r0, #24, #8
	ldr	r0, [r8, #792]
	bfi	ip, r0, #16, #8
	ldr	r0, [r8, #788]
	bfi	ip, r0, #8, #8
	ldr	r0, [r8, #784]
	bfi	ip, r0, #0, #8
	str	ip, [r9, #3088]
	ldr	r0, [r8, #812]
	bfi	r1, r0, #24, #8
	ldr	r0, [r8, #808]
	bfi	r1, r0, #16, #8
	ldr	r0, [r8, #804]
	bfi	r1, r0, #8, #8
	ldr	r0, [r8, #800]
	bfi	r1, r0, #0, #8
	str	r1, [r9, #3092]
	ldr	r1, [r8, #828]
	bfi	r2, r1, #24, #8
	ldr	r1, [r8, #824]
	bfi	r2, r1, #16, #8
	ldr	r1, [r8, #820]
	bfi	r2, r1, #8, #8
	ldr	r1, [r8, #816]
	bfi	r2, r1, #0, #8
	str	r2, [r9, #3096]
	ldr	r2, [r8, #844]
	ldr	r1, [r8, #840]
	ldr	r0, [r8, #836]
	bfi	r3, r2, #24, #8
	bfi	r3, r1, #16, #8
	ldr	r2, [r8, #832]
	bfi	r3, r0, #8, #8
	mov	r1, r6
	bfi	r3, r2, #0, #8
	str	r3, [r9, #3072]
	ldr	r2, [r4, #3384]
	ldr	r3, [r4, #3388]
	bfi	r1, r2, #0, #4
	mov	r2, r6
	bfi	r1, r3, #4, #4
	str	r1, [r9, #3100]
	ldr	r3, [r4, #3332]
	bfi	r2, r3, #0, #4
	str	r2, [r9, #3104]
	ldr	r2, [r4, #3328]
	ldr	r3, [r4, #3336]
	bfi	r6, r2, #0, #4
	bfi	r6, r3, #4, #4
	str	r6, [r9, #3108]
	ldr	r3, [r7, #4]
	cmp	r3, #0
	ldrne	r2, [r8, #764]
	moveq	r2, #2
	movne	r3, #0
	bfi	r3, r2, #0, #4
	str	r3, [r9, #3112]
	ldr	r1, [r4, #3260]
	mov	r3, #0
	ldr	r0, [r4, #3264]
	bfi	r3, r1, #0, #2
	ldr	r1, [r4, #3268]
	bfi	r3, r0, #2, #2
	ldr	r0, [r4, #3272]
	bfi	r3, r1, #4, #2
	ldr	r1, [r4, #3276]
	bfi	r3, r0, #6, #2
	ldr	r0, [r4, #3280]
	bfi	r3, r1, #8, #2
	ldr	r1, [r4, #3284]
	bfi	r3, r0, #10, #2
	ldr	r0, [r4, #3288]
	bfi	r3, r1, #12, #2
	ldr	r1, [r4, #3292]
	bfi	r3, r0, #14, #2
	ldr	r0, [r4, #3296]
	bfi	r3, r1, #16, #2
	ldr	r1, [r4, #3300]
	bfi	r3, r0, #18, #2
	ldr	r2, [fp, #-120]
	ldr	r0, [r4, #3304]
	bfi	r3, r1, #20, #2
	ldr	r1, [r4, #3308]
	bfi	r3, r0, #22, #2
	ldr	r0, [r4, #3312]
	bfi	r3, r1, #24, #2
	ldr	r1, [r4, #3316]
	bfi	r3, r0, #26, #2
	ldr	r0, [r4, #3320]
	bfi	r3, r1, #28, #2
	mov	r1, #0
	bfi	r3, r0, #30, #2
	str	r3, [r9, #3116]
	ldr	r3, [r4, #3324]
	mov	r0, r1
	ldr	r5, [fp, #-48]
	bfi	r1, r3, #0, #5
	str	r1, [r9, #3120]
	ldr	ip, [r4, #3372]
	add	r1, r10, #1088
	ldr	r3, [r4, #3376]
	add	r1, r1, #12
	bfi	r0, ip, #24, #4
	ldr	ip, [r4, #3380]
	bfi	r0, r3, #28, #4
	ldr	r3, [r4, #3344]
	bfi	r0, ip, #16, #6
	ldr	ip, [r4, #3364]
	bfi	r0, r3, #8, #4
	add	r3, r8, #908
	bfi	r0, ip, #0, #6
	str	r0, [r9, #3124]
.L69:
	ldr	r0, [r2, #4]!
	cmp	r2, r3
	bfi	r5, r0, #0, #20
	str	r5, [r1, #4]!
	bne	.L69
	add	r0, r8, #1152
	add	r2, r10, #1264
	add	r0, r0, #12
	add	r2, r2, #12
.L70:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	bfi	r5, r1, #0, #20
	str	r5, [r2, #4]!
	bne	.L70
	mov	r2, #0
	str	r2, [r9, #3660]
	mov	r0, r2
	mov	r1, r2
	bfi	r0, r2, #0, #16
	bfi	r1, r2, #0, #16
	mov	r3, r2
	bfi	r3, r2, #16, #16
	str	r2, [r10, #572]
	bfi	r0, r2, #16, #16
	str	r2, [r10, #580]
	bfi	r1, r2, #16, #16
	str	r0, [r10, #584]
	bfi	r3, r2, #0, #16
	str	r1, [r10, #588]
	mov	r0, r2
	str	r3, [r10, #592]
	bfi	r0, r2, #0, #1
	mov	r3, #13
	str	r0, [r10, #564]
	str	r3, [r10, #576]
	mov	r1, r2
	mov	r3, #7
	bfi	r1, r2, #0, #1
	str	r3, [r10, #600]
	mov	ip, r2
	str	r1, [r10, #568]
	mvn	r1, #0
	str	r3, [r10, #608]
	mov	r0, r2
	str	r1, [r10, #596]
	str	r1, [r10, #604]
	str	r1, [r10, #612]
	str	r1, [r10, #620]
	mov	r1, r2
	str	r3, [r10, #616]
	str	r3, [r10, #624]
	ldr	r3, [r4, #3796]
	bfi	ip, r3, #0, #1
	str	ip, [r10, #120]
	ldr	ip, [r7, #148]
	mov	r3, r2
	str	ip, [r10, #96]
	ldr	ip, [r7, #152]
	str	ip, [r10, #100]
	ldr	ip, [r7, #156]
	str	ip, [r10, #104]
	ldr	ip, [r7, #160]
	str	ip, [r10, #108]
	ldr	ip, [r7, #164]
	str	ip, [r10, #112]
	ldr	ip, [r7, #168]
	str	ip, [r10, #116]
	ldr	ip, [r4, #3240]
	bfi	r1, ip, #0, #16
	ldr	ip, [r4, #3244]
	bfi	r1, ip, #16, #16
	str	r1, [r10, #1728]
	ldr	r1, [r4, #3256]
	bfi	r0, r1, #16, #16
	str	r0, [r10, #1732]
	ldr	r0, [r4, #3248]
	ldr	r1, [r4, #3252]
	bfi	r3, r0, #0, #16
	bfi	r3, r1, #16, #16
	str	r3, [r10, #1736]
	ldr	r1, [r7, #4]
	ldr	r3, [r7, #676]
	cmp	r1, #2
	beq	.L122
	ldr	ip, [r7, #580]
	mov	r1, #0
	mov	r0, r1
	bfi	r0, r2, #0, #1
	str	ip, [r3, #256]
	ldr	r2, [r7, #584]
	str	r2, [r3, #260]
	ldr	r2, [r7, #588]
	str	r2, [r3, #264]
	ldr	r2, [r7, #592]
	str	r2, [r3, #268]
	ldr	r2, [r7, #596]
	str	r2, [r3, #272]
	ldr	r2, [r7, #600]
	str	r2, [r3, #276]
	ldr	r2, [r7, #604]
	str	r2, [r3, #280]
	ldr	r2, [r7, #608]
	str	r2, [r3, #284]
	ldr	r2, [r7, #612]
	str	r0, [r3, #292]
	sub	ip, r2, #1
	mov	r0, r2, lsr #8
	bfi	r1, ip, #16, #7
	sub	r0, r0, #1
	mov	r2, r2, lsr #16
	bfi	r1, r0, #8, #6
	sub	r2, r2, #1
	bfi	r1, r2, #0, #6
	str	r1, [r3, #288]
.L79:
	ldr	r2, [r7, #4]
	cmp	r2, #2
	beq	.L123
	ldr	r2, [r4, #2340]
	mov	r1, #0
	str	r2, [r3, #296]
	ldr	r2, [r4, #2344]
	str	r2, [r3, #300]
	ldr	r2, [r4, #2348]
	str	r2, [r3, #304]
	ldr	r2, [r4, #2352]
	str	r2, [r3, #308]
	ldr	r2, [r4, #2356]
	str	r2, [r3, #312]
	ldr	r2, [r4, #2360]
	str	r2, [r3, #316]
	ldr	r2, [r4, #2364]
	str	r2, [r3, #320]
	ldr	r2, [r4, #2368]
	str	r2, [r3, #324]
	ldr	r2, [r4, #2336]
	sub	ip, r2, #1
	mov	r0, r2, lsr #8
	bfi	r1, ip, #16, #7
	sub	r0, r0, #1
	mov	r2, r2, lsr #16
	bfi	r1, r0, #8, #6
	sub	r2, r2, #1
	bfi	r1, r2, #0, #6
	str	r1, [r3, #328]
.L86:
	ldr	r1, [r7, #240]
	add	r5, r9, #8192
	mov	r2, #0
	bfc	r2, #0, #1
	mov	r3, #0
	bfc	r3, #16, #8
	str	r1, [r10, #68]
	mvn	r1, #84
	str	r2, [r5, #1040]
	ldr	r2, [r4, #3904]
	str	r2, [r5, #1044]
	ldr	r2, [r7, #512]
	cmp	r2, #0
	bfieq	r3, r2, #0, #1
	orrne	r3, r3, #1
	str	r3, [r10, #76]
	ldr	r3, [r7, #656]
	str	r3, [r10, #80]
	ldr	r3, [r7, #660]
	str	r3, [r10, #84]
	ldr	r3, [r7, #664]
	str	r3, [r10, #88]
	mov	r3, #0
	ldr	r2, [r7, #664]
	bfi	r3, r1, #0, #8
	mov	r1, #0
	cmp	r2, #0
	ldrne	r2, [r7, #668]
	str	r2, [r10, #92]
	mov	r2, #85
	bfi	r3, r2, #8, #8
	str	r3, [r10, #28]
	ldr	r0, [r4, #3392]
	mov	r3, r1
	ldr	r2, [r4, #3396]
	mov	r6, r3
	bfi	r1, r0, #0, #6
	ldr	r0, [r4, #3400]
	bfi	r1, r2, #8, #2
	ldr	r2, [r4, #3404]
	bfi	r1, r0, #10, #1
	ldr	r0, [r4, #3408]
	bfi	r1, r2, #12, #4
	mov	r2, r3
	bfi	r1, r0, #16, #5
	str	r1, [r5, #4048]
	ldr	r0, [r4, #3452]
	mov	r1, r3
	str	r0, [r5, #4052]
	ldr	r0, [r4, #3456]
	str	r0, [r5, #4056]
	ldr	r0, [r4, #3460]
	bfi	r3, r0, #0, #16
	ldr	r0, [r4, #3464]
	bfi	r3, r0, #16, #2
	ldr	r0, [r4, #3468]
	bfi	r3, r0, #18, #2
	ldr	r0, [r4, #3472]
	bfi	r3, r0, #20, #4
	ldr	r0, [r4, #3476]
	bfi	r3, r0, #24, #1
	ldr	r0, [r4, #3484]
	bfi	r3, r0, #25, #2
	ldr	r0, [r4, #3488]
	bfi	r3, r0, #27, #1
	ldr	r0, [r4, #3480]
	bfi	r3, r0, #28, #1
	str	r3, [r5, #4060]
	ldr	r0, [r4, #3520]
	ldr	r3, [r4, #3516]
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #3512]
	bfi	r2, r3, #2, #2
	ldr	r3, [r4, #3508]
	bfi	r2, r0, #4, #2
	ldr	r0, [r4, #3528]
	bfi	r2, r3, #6, #1
	ldr	r3, [r4, #3532]
	bfi	r2, r0, #8, #6
	bfi	r2, r3, #24, #6
	str	r2, [r5, #4064]
	ldr	r2, [r4, #3536]
	ldr	r3, [r4, #3540]
	bfi	r1, r2, #0, #6
	ldr	r2, [r4, #3544]
	bfi	r1, r3, #8, #6
	ldr	r3, [r4, #3548]
	bfi	r1, r2, #16, #6
	bfi	r1, r3, #24, #6
	str	r1, [r5, #4068]
	ldr	r1, [r7, #16]
	ldr	r3, [r7, #4]
	ldr	r2, [r4, #3552]
	cmp	r3, r6
	ldr	r3, [r4, #3556]
	bfi	r6, r2, #0, #6
	ldr	r0, [r7, #516]
	moveq	r1, r1, lsr #4
	movne	r1, r1, lsr #6
	bfi	r6, r3, #6, #25
	bl	__aeabi_uidiv
	mov	r3, #0
	mov	r2, r3
	bfi	r6, r0, #6, #25
	str	r6, [r5, #4072]
	ldr	r1, [r7, #552]
	ldr	r0, [r7, #548]
	bfi	r3, r1, #10, #1
	ldr	r1, [r7, #544]
	bfi	r3, r0, #9, #1
	ldr	r0, [r4, #3840]
	bfi	r3, r1, #8, #1
	ldr	r1, [r4, #3844]
	bfi	r3, r0, #7, #1
	ldr	r0, [r4, #3820]
	bfi	r3, r1, #6, #1
	ldr	r1, [r4, #3816]
	bfi	r3, r0, #5, #1
	ldr	r0, [r4, #3848]
	bfi	r3, r1, #4, #1
	ldr	r1, [r4, #3852]
	bfi	r3, r0, #3, #1
	ldr	r0, [r4, #3856]
	bfi	r3, r1, #2, #1
	ldr	r1, [r4, #3860]
	bfi	r3, r0, #1, #1
	ldr	r0, .L127
	bfi	r3, r1, #0, #1
	mov	r1, r2
	ldr	lr, [r0]
	str	r3, [r9, #504]
	ldr	r0, [r4, #3824]
	add	r3, lr, #61440
	ldr	ip, [r4, #3864]
	bfi	r2, r0, #7, #1
	ldr	r0, [r4, #3868]
	bfi	r2, ip, #6, #1
	ldr	ip, [r4, #3872]
	bfi	r2, r0, #5, #1
	ldr	r0, [r4, #3876]
	bfi	r2, ip, #4, #1
	ldr	ip, [r4, #3880]
	bfi	r2, r0, #3, #1
	ldr	r0, [r4, #3884]
	bfi	r2, ip, #2, #1
	ldr	ip, [r4, #3888]
	bfi	r2, r0, #1, #1
	add	r0, r9, #61440
	bfi	r2, ip, #0, #1
	str	r2, [r9, #508]
	ldr	lr, [r4, #3808]
	mov	r2, r1
	ldr	ip, [r4, #3812]
	bfi	r2, r1, #1, #1
	bfi	r1, lr, #0, #1
	bfc	r2, #2, #1
	bfi	r1, ip, #3, #1
	bfc	r2, #3, #1
	mov	ip, #3
	bfi	r1, ip, #16, #4
	str	r1, [r0]
	mov	r1, #0
	str	r2, [r0, #32]
	mov	r2, #1
	ldr	ip, [r7, #556]
	str	ip, [r3, #520]
	ldr	ip, [r7, #556]
	str	ip, [r3, #524]
	ldr	ip, [r7, #564]
	str	ip, [r3, #752]
	ldr	ip, [r7, #560]
	str	ip, [r3, #756]
	ldr	ip, [r7, #564]
	str	ip, [r3, #772]
	ldr	ip, [r7, #560]
	str	ip, [r3, #776]
	str	r1, [r0, #8]
	str	r1, [r9, #16]
	str	r2, [r9, #16]
.L40:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L120:
	ldr	r3, .L127+4
	add	r2, r8, #844
	ldr	r5, [fp, #-48]
	add	r0, r3, #160
	str	r2, [fp, #-120]
.L46:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L46
	ldr	r3, .L127+8
	add	r2, r8, #1004
	add	r0, r3, #160
.L47:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L47
	mov	r2, #3
	mov	r3, #2
	str	r2, [r8, #800]
	str	r3, [r8, #780]
	mov	r3, #96
	str	r2, [r8, #804]
	mov	r2, #10
	str	r3, [r8, #1196]
	mov	r3, #0
	str	r2, [r8, #816]
	mov	r2, #20
	str	r3, [r8, #784]
	str	r3, [r8, #788]
	str	r3, [r8, #792]
	str	r3, [r8, #796]
	mov	r3, #5
	str	r5, [fp, #-48]
	str	r3, [r8, #808]
	str	r3, [r8, #812]
	mov	r3, #15
	str	r2, [r8, #824]
	str	r3, [r8, #820]
	mov	r3, #255
	str	r3, [r8, #828]
	str	r3, [r8, #832]
	str	r3, [r8, #836]
	str	r3, [r8, #840]
	str	r3, [r8, #844]
	b	.L45
.L51:
	mov	r3, #0
	str	r3, [r4, #2316]
	str	r3, [r4, #2312]
	mov	r3, #7
	str	r3, [r4, #2308]
	b	.L53
.L64:
	mov	r2, #15
	mov	r3, #0
	bfi	r3, r2, #0, #5
	bfi	r3, r2, #5, #5
	bfi	r3, r2, #10, #5
	bfi	r3, r2, #15, #5
	mov	r2, #0
	bfi	r3, r2, #20, #1
	str	r3, [r10, #24]
	b	.L65
.L102:
	mov	r2, #6
.L60:
	bfi	r3, r2, #6, #4
	bfc	r3, #14, #1
.L61:
	ldrb	r2, [r7, #64]
	b	.L62
.L121:
	ldr	r2, [r7, #16]
	ldr	r3, [r7, #12]
	mov	r2, r2, lsr #2
	sub	r2, r2, #16
	mov	r3, r3, lsr #2
	sub	r3, r3, #16
	mov	r2, r2, lsr #1
	cmp	r2, #32
	mov	r3, r3, lsr #1
	movcs	r2, #32
	cmp	r3, #72
	bic	r2, r2, #-2147483645
	movcs	r3, #72
	cmp	r2, #7
	bic	r3, r3, #-2147483645
	movls	r2, #7
	bls	.L57
	cmp	r2, #32
	movcs	r2, #32
	sub	r2, r2, #1
	and	r2, r2, #63
.L57:
	cmp	r3, #7
	movls	r3, #7
	bls	.L58
	cmp	r3, #72
	movcs	r3, #72
	sub	r3, r3, #1
	and	r3, r3, #127
.L58:
	mov	r6, #0
	bfi	r6, r2, #16, #6
	bfi	r6, r3, #0, #7
	b	.L59
.L123:
	ldr	r2, [r4, #2412]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r4, #2372]
	ldrhi	r2, [r4, #2372]
	movls	r2, r1, asl r2
	str	r2, [r3, #308]
	ldr	r2, [r4, #2412]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r4, #2376]
	ldrls	r1, [r4, #2376]
	movls	r2, r1, asl r2
	str	r2, [r3, #312]
	ldr	r2, [r4, #2412]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r4, #2380]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #316]
	ldr	r2, [r4, #2384]
	str	r2, [r3, #320]
	ldr	r2, [r4, #2388]
	str	r2, [r3, #324]
	ldr	r2, [r4, #2392]
	str	r2, [r3, #328]
	ldr	r2, [r4, #2396]
	str	r2, [r3, #332]
	ldr	r2, [r4, #2400]
	str	r2, [r3, #336]
	b	.L86
.L122:
	ldr	lr, [r7, #512]
	mov	r0, r2
	ldr	ip, [r4, #3792]
	movw	r1, #513
	cmp	lr, r2
	bfi	r0, ip, #8, #3
	movw	ip, #9729
	moveq	ip, r1
	bfi	r0, ip, #16, #16
	str	r0, [r3, #256]
	mov	r1, r2
	ldr	r0, [r7, #612]
	mov	ip, r2
	ldr	lr, [r7, #616]
	bfi	r1, r0, #0, #5
	mov	r0, r2
	bfi	r1, lr, #16, #16
	str	r1, [r3, #260]
	ldr	lr, [r4, #2408]
	ldr	r1, [r4, #2412]
	bfi	r2, lr, #0, #5
	bfi	r2, r1, #16, #16
	str	r2, [r3, #300]
	ldr	r1, [r7, #612]
	ldr	r2, [r7, #652]
	rsb	r1, r1, #16
	mov	r2, r2, asl r1
	bfi	ip, r2, #0, #16
	str	ip, [r3, #264]
	ldr	r1, [r4, #2408]
	ldr	r2, [r4, #2404]
	rsb	r1, r1, #16
	mov	r2, r2, asl r1
	bfi	r0, r2, #0, #16
	str	r0, [r3, #304]
	ldr	r2, [r7, #616]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r7, #620]
	ldrhi	r2, [r7, #620]
	movls	r2, r1, asl r2
	str	r2, [r3, #268]
	ldr	r2, [r7, #616]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r7, #624]
	ldrls	r1, [r7, #624]
	movls	r2, r1, asl r2
	str	r2, [r3, #272]
	ldr	r2, [r7, #616]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r7, #628]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #276]
	ldr	r2, [r7, #632]
	str	r2, [r3, #280]
	ldr	r2, [r7, #636]
	str	r2, [r3, #284]
	ldr	r2, [r7, #640]
	str	r2, [r3, #288]
	ldr	r2, [r7, #644]
	str	r2, [r3, #292]
	ldr	r2, [r7, #648]
	str	r2, [r3, #296]
	b	.L79
.L128:
	.align	2
.L127:
	.word	.LANCHOR0
	.word	.LANCHOR1+316
	.word	.LANCHOR1+156
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_CfgReg, .-DRV_VENC_HAL_V400R004C02_CfgReg
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_Init
	.type	DRV_VENC_HAL_V400R004C02_Init, %function
DRV_VENC_HAL_V400R004C02_Init:
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
	ldr	r4, .L159
	ldr	r3, [r4]
	cmp	r3, #0
	ldr	r3, .L159+4
	str	r3, [fp, #-52]
	beq	.L130
.L133:
	ldr	r3, [fp, #-52]
	movw	r0, #8004
	ldr	r3, [r3, #20]
	blx	r3
	ldr	r3, .L159+4
	cmp	r0, #0
	str	r0, [r4, #4]
	mov	r5, r0
	ldr	r4, .L159
	beq	.L157
	mov	r1, #0
	ldr	r3, [r3]
	movw	r2, #8004
	blx	r3
	ldr	r1, [r4, #4]
	cmp	r1, #0
	beq	.L145
	ldr	lr, [r4]
	add	r2, r1, #7296
	add	r0, r1, #7360
	add	r3, r1, #4096
	add	r2, r2, #56
	add	r0, r0, #56
	mov	ip, #1
	str	lr, [r1]
	str	ip, [r1, #40]
	mov	r4, #3
	str	ip, [r1, #56]
	mov	lr, #0
	str	r4, [r1, #8]
	mov	r5, #1280
	str	lr, [r1, #4]
	mov	lr, ip
	str	r4, [r1, #44]
	str	r5, [r1, #12]
	mov	r5, #720
	str	r5, [r1, #16]
	mov	r5, #10240
	str	r5, [r1, #28]
	mov	r5, #28
	str	r5, [r1, #520]
	mov	r5, #16
	str	r5, [r1, #524]
	mov	r5, #48
	str	r5, [r1, #528]
	str	r4, [r3, #2444]
	mov	r4, #256
	str	ip, [r3, #2420]
	str	ip, [r3, #2416]
	str	ip, [r3, #3072]
	str	ip, [r3, #3100]
	str	ip, [r3, #3152]
	str	ip, [r3, #2724]
	mov	ip, #6
	str	r4, [r3, #2428]
	mov	r4, #4
	str	ip, [r3, #2868]
	mov	ip, #128
	str	r4, [r3, #2424]
	str	r4, [r3, #2436]
	mov	r4, #8
	str	ip, [r3, #2432]
	str	ip, [r3, #2440]
	mov	ip, #32
	str	r4, [r3, #2448]
	str	r4, [r3, #2456]
	str	ip, [r3, #2452]
	str	ip, [r3, #2460]
	str	ip, [r3, #2864]
.L137:
	str	lr, [r2, #4]!
	cmp	r2, r0
	mov	ip, #1
	bne	.L137
	ldr	r2, .L159+8
	add	r0, r1, #844
	mov	r4, #4
	mov	r5, #8
	add	lr, r2, #160
	mov	r6, #10
	mov	r8, #12
	mov	r7, #48
	mov	r9, #51
	str	r7, [r3, #3352]
	str	r7, [r3, #3348]
	mov	r10, #5
	str	r7, [r3, #3356]
	mov	r7, #2
	str	r6, [r3, #3544]
	str	r6, [r3, #3532]
	str	r6, [r3, #3540]
	str	r6, [r3, #3528]
	str	r6, [r3, #3548]
	str	r9, [r3, #3360]
	str	r9, [r3, #3364]
	str	r9, [r3, #3380]
	mov	r9, #20
	str	r4, [r3, #3372]
	str	r4, [r3, #3472]
	str	r4, [r3, #3404]
	str	r4, [r3, #3584]
	str	r8, [r3, #3384]
	str	r8, [r3, #3388]
	str	r8, [r3, #3576]
	str	r10, [r3, #3392]
	mov	r10, #44
	str	r7, [r3, #3340]
	str	r10, [r3, #3368]
	mov	r10, #50
	str	r9, [r3, #3564]
	str	r10, [r3, #3568]
	mov	r10, #150
	str	ip, [r3, #3424]
	str	r10, [r3, #3572]
	mov	r10, #6
	str	ip, [r3, #3428]
	str	ip, [r3, #3432]
	str	ip, [r3, #3444]
	str	ip, [r3, #3400]
	str	r5, [r3, #3324]
	str	r5, [r3, #3376]
	str	r5, [r3, #3580]
	str	r8, [r3, #3588]
	mov	r8, #11520
	str	r6, [r3, #3628]
	mov	r6, #5
	str	r4, [r3, #3596]
	movt	r8, 305
	str	r7, [r3, #3600]
	str	r4, [r3, #3604]
	str	r7, [r3, #3664]
	str	r6, [r3, #3760]
	mov	r6, #131
	str	r9, [r3, #3632]
	mov	r9, #160
	str	r7, [r3, #3792]
	str	r10, [r3, #3608]
	mov	r10, #100
	str	r6, [r3, #3612]
	mov	r6, #127
	str	r9, [r3, #3616]
	mov	r9, #3
	str	r10, [r3, #3620]
	mov	r10, #16
	str	r6, [r3, #3624]
	mov	r6, #24
	str	r5, [r3, #3592]
	str	r6, [r3, #3696]
	str	r6, [r3, #3700]
	mov	r6, #60
	str	r5, [r3, #3672]
	str	r6, [r3, #3744]
	movw	r6, #767
	str	r5, [r3, #3676]
	str	r6, [r3, #3640]
	mov	r6, #15
	str	r5, [r3, #3680]
	str	r6, [r3, #3800]
	str	r6, [r3, #3804]
	mov	r6, #0
	str	r5, [r3, #3684]
	str	ip, [r3, #3636]
	str	ip, [r3, #3780]
	str	ip, [r3, #3784]
	str	ip, [r3, #3788]
	str	ip, [r3, #3796]
	str	r9, [r3, #3648]
	str	r10, [r3, #3688]
	str	r10, [r3, #3692]
	str	r6, [r3, #3808]
	mov	r6, #2304
	str	r7, [r3, #3892]
	movt	r6, 61
	str	r8, [r3, #3900]
	mov	r7, #64
	str	r6, [r3, #3904]
	mov	r8, #9
	str	ip, [r3, #3812]
	mov	r6, #7
	str	ip, [r3, #3896]
	str	r4, [r1, #696]
	str	r4, [r1, #704]
	str	r4, [r1, #744]
	str	r4, [r1, #780]
	str	r4, [r1, #764]
	mov	r4, #11
	str	r7, [r1, #692]
	mov	r7, #14
	str	r6, [r1, #804]
	str	r6, [r1, #808]
	str	r6, [r1, #812]
	mov	r6, #18
	str	r8, [r1, #816]
	mov	r8, #25
	str	r4, [r1, #820]
	mov	r4, #255
	str	r7, [r1, #824]
	mov	r7, #96
	str	r6, [r1, #828]
	movw	r6, #378
	str	r4, [r1, #836]
	str	r4, [r1, #840]
	str	r4, [r1, #844]
	mov	r4, #128
	str	r9, [r1, #688]
	str	r10, [r1, #700]
	str	r10, [r1, #708]
	str	r10, [r1, #740]
	str	ip, [r1, #684]
	str	ip, [r1, #680]
	str	ip, [r1, #748]
	str	ip, [r1, #772]
	str	ip, [r1, #768]
	str	r8, [r1, #832]
	str	r7, [r1, #1196]
	str	ip, [r1, #1168]
	str	r5, [r1, #1188]
	str	r9, [r1, #1172]
	str	r8, [r1, #1176]
	str	r9, [r1, #1184]
	str	r6, [r1, #1192]
	str	r4, [r1, #1180]
.L138:
	ldr	ip, [r2, #4]!
	cmp	r2, lr
	str	ip, [r0, #4]!
	bne	.L138
	ldr	r2, .L159+12
	add	r0, r1, #1004
	add	lr, r2, #160
.L139:
	ldr	ip, [r2, #4]!
	cmp	r2, lr
	str	ip, [r0, #4]!
	bne	.L139
	mov	r6, #3
	add	r4, r1, #1200
	add	r2, r1, #6400
	str	r4, [fp, #-48]
	str	r2, [fp, #-56]
	mov	r2, #0
	str	r4, [fp, #-60]
	str	r2, [r3, #2316]
	str	r2, [r3, #2312]
	mov	r2, #7
	str	r2, [r3, #2308]
.L141:
	ldr	r4, [fp, #-48]
	movw	r2, #2600
	ldr	r3, [fp, #-52]
	mov	r1, #0
	mov	r10, #0
	mov	r0, r4
	ldr	r3, [r3]
	blx	r3
	mov	r0, r4
	mov	r3, r4
	mov	r2, r4
	mov	r1, r10
	mov	lr, #4
	mov	r4, #64
	mov	ip, #1
.L140:
	add	r10, r10, #1
	str	r6, [r3, #8]
	cmp	r10, #5
	mov	r9, #32
	mov	r5, #96
	mov	r7, #384
	str	r5, [r2, #2468]
	mov	r8, #2
	str	lr, [r0, #420]
	mov	r5, #20
	str	r1, [r3, #44]
	add	r0, r0, #404
	str	r1, [r3, #72]
	add	r3, r3, #84
	str	r4, [r3, #-72]
	str	ip, [r3, #-80]
	str	r5, [r2, #2448]
	mov	r5, #8
	str	r6, [r2, #2444]
	str	r5, [r2, #2460]
	mov	r5, #16
	str	r4, [r2, #2452]
	str	lr, [r2, #2456]
	str	r1, [r3, #-28]
	str	r1, [r3, #-8]
	str	lr, [r3, #-60]
	str	r9, [r3, #-56]
	str	ip, [r0, #24]
	str	r1, [r0, #28]
	str	r7, [r2, #2464]
	str	r9, [r3, #-24]
	str	r1, [r3, #-52]
	str	r1, [r3, #-4]
	str	lr, [r3, #-20]
	str	ip, [r3, #-84]
	str	r8, [r2, #2440]
	add	r2, r2, r9
	str	ip, [r3, #-16]
	str	lr, [r3, #-68]
	str	r5, [r3, #-64]
	str	ip, [r0, #20]
	bne	.L140
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-56]
	add	r3, r3, #2592
	add	r3, r3, #8
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L141
	ldr	r4, [fp, #-60]
	mov	r3, #1
	mov	r7, #0
	str	r3, [fp, #-48]
	mov	r0, r3
	mov	ip, r9
	mov	lr, r8
	mov	r3, r7
	mov	r5, #128
	mov	r2, #64
	str	r10, [fp, #-52]
.L142:
	mov	r8, #6
	str	r8, [r4, #824]
	ldr	r8, [fp, #-52]
	cmp	r7, #0
	mov	r6, #15
	str	r0, [r4, #8]
	str	r6, [r4, #2576]
	mov	r1, #3
	mov	r6, #4
	str	r5, [r4, #12]
	str	r5, [r4, #28]
	mov	r10, #256
	str	r5, [r4, #60]
	mov	r9, #34
	str	r3, [r4, #424]
	str	r3, [r4]
	str	r3, [r4, #428]
	str	r3, [r4, #4]
	str	r3, [r4, #832]
	str	r2, [r4, #96]
	str	r2, [r4, #112]
	str	r2, [r4, #144]
	str	r2, [r4, #180]
	str	r2, [r4, #196]
	str	r2, [r4, #228]
	str	r8, [r4, #1228]
	str	r0, [r4, #380]
	str	ip, [r4, #408]
	str	r3, [r4, #388]
	str	r3, [r4, #384]
	str	lr, [r4, #2572]
	str	r2, [r4, #2580]
	str	lr, [r4, #2584]
	str	r6, [r4, #2588]
	beq	.L158
	ldr	r8, [fp, #-48]
	str	r1, [r4, #392]
	cmp	r8, #1
	str	r1, [r4, #360]
	str	r1, [r4, #368]
	str	r1, [r4, #376]
	str	r1, [r4, #372]
	str	r1, [r4, #400]
	mov	r1, #16
	str	r3, [r4, #412]
	str	ip, [r4, #364]
	str	r0, [r4, #2048]
	str	r10, [r4, #2592]
	str	r9, [r4, #416]
	str	ip, [r4, #396]
	str	r0, [r4, #336]
	str	lr, [r4, #2568]
	str	r0, [r4, #404]
	str	r6, [r4, #352]
	str	r1, [r4, #356]
	bhi	.L145
.L144:
	ldr	r1, [fp, #-48]
	add	r4, r4, #2592
	add	r7, r7, #1
	add	r4, r4, #8
	add	r1, r1, #1
	str	r1, [fp, #-48]
	b	.L142
.L145:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L157:
	ldr	r0, [r4]
	cmp	r0, #0
	beq	.L155
	ldr	r3, [r3, #16]
	blx	r3
	str	r5, [r4]
.L155:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L130:
	mov	r0, #0
	mov	r1, #63232
	movt	r0, 63688
	ldr	r3, [r3, #12]
	blx	r3
	cmp	r0, #0
	str	r0, [r4]
	beq	.L155
	b	.L133
.L158:
	mov	r8, #16
	str	r6, [r4, #392]
	str	r7, [r4, #412]
	str	ip, [r4, #364]
	str	r0, [r4, #2048]
	str	r1, [r4, #360]
	str	r10, [r4, #2592]
	str	r6, [r4, #368]
	str	r1, [r4, #376]
	str	r1, [r4, #372]
	str	r1, [r4, #400]
	str	ip, [r4, #396]
	str	r0, [r4, #336]
	str	lr, [r4, #2568]
	str	r0, [r4, #404]
	str	r6, [r4, #352]
	str	r9, [r4, #416]
	str	r8, [r4, #356]
	b	.L144
.L160:
	.align	2
.L159:
	.word	.LANCHOR0
	.word	venc_Osal_Func_Ptr_S
	.word	.LANCHOR1+476
	.word	.LANCHOR1-4
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_Init, .-DRV_VENC_HAL_V400R004C02_Init
	.align	2
	.global	DRV_VENC_HAL_V400R004C02_Deinit
	.type	DRV_VENC_HAL_V400R004C02_Deinit, %function
DRV_VENC_HAL_V400R004C02_Deinit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L170
	ldr	r0, [r4]
	cmp	r0, #0
	beq	.L162
	ldr	r3, .L170+4
	ldr	r3, [r3, #16]
	blx	r3
	mov	r3, #0
	str	r3, [r4]
.L162:
	ldr	r0, [r4, #4]
	ldr	r4, .L170
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L170+4
	ldr	r3, [r3, #24]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L171:
	.align	2
.L170:
	.word	.LANCHOR0
	.word	venc_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V400R004C02_Deinit, .-DRV_VENC_HAL_V400R004C02_Deinit
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	g_h264LambdaSad, %object
	.size	g_h264LambdaSad, 160
g_h264LambdaSad:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	4
	.word	4
	.word	4
	.word	5
	.word	6
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
	.word	23
	.word	25
	.word	29
	.word	32
	.word	36
	.word	40
	.word	45
	.word	51
	.word	57
	.word	64
	.word	72
	.word	81
	.word	91
	.type	g_h265LambdaSad, %object
	.size	g_h265LambdaSad, 160
g_h265LambdaSad:
	.word	193
	.word	216
	.word	243
	.word	273
	.word	306
	.word	344
	.word	386
	.word	433
	.word	487
	.word	546
	.word	613
	.word	688
	.word	773
	.word	867
	.word	974
	.word	1093
	.word	1227
	.word	1377
	.word	1546
	.word	1735
	.word	1948
	.word	2186
	.word	2454
	.word	2755
	.word	3092
	.word	3471
	.word	3896
	.word	4373
	.word	4908
	.word	5510
	.word	6184
	.word	6942
	.word	7792
	.word	8746
	.word	9817
	.word	11020
	.word	12369
	.word	13884
	.word	15584
	.word	17493
	.type	g_h265LambdaSsd, %object
	.size	g_h265LambdaSsd, 160
g_h265LambdaSsd:
	.word	18
	.word	22
	.word	28
	.word	36
	.word	45
	.word	57
	.word	72
	.word	91
	.word	115
	.word	145
	.word	183
	.word	231
	.word	291
	.word	367
	.word	463
	.word	583
	.word	735
	.word	926
	.word	1167
	.word	1470
	.word	1853
	.word	2334
	.word	2941
	.word	3706
	.word	4669
	.word	5883
	.word	7412
	.word	9338
	.word	11766
	.word	14824
	.word	18677
	.word	23532
	.word	29649
	.word	37355
	.word	47065
	.word	59298
	.word	74711
	.word	94130
	.word	118596
	.word	131071
	.type	g_h264LambdaSsd, %object
	.size	g_h264LambdaSsd, 160
g_h264LambdaSsd:
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	4
	.word	5
	.word	7
	.word	9
	.word	11
	.word	14
	.word	17
	.word	22
	.word	27
	.word	34
	.word	43
	.word	54
	.word	69
	.word	86
	.word	109
	.word	137
	.word	173
	.word	218
	.word	274
	.word	345
	.word	435
	.word	548
	.word	691
	.word	870
	.word	1097
	.word	1382
	.word	1741
	.word	2193
	.word	2763
	.word	3482
	.word	4095
	.word	4095
	.word	4095
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_pRegBase, %object
	.size	g_pRegBase, 4
g_pRegBase:
	.space	4
	.type	g_pHalRegInfo, %object
	.size	g_pHalRegInfo, 4
g_pHalRegInfo:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
