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
	.global	DRV_VENC_HAL_V500R001_ClrInt
	.type	DRV_VENC_HAL_V500R001_ClrInt, %function
DRV_VENC_HAL_V500R001_ClrInt:
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
	ldr	r2, [r3, #4]
	orr	r2, r2, #64
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L10:
	mvn	r2, #0
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L4:
	ldr	r2, [r3, #4]
	orr	r2, r2, #1
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L3:
	ldr	r2, [r3, #4]
	orr	r2, r2, #2
	str	r2, [r3, #4]
	ldmfd	sp, {fp, sp, pc}
.L12:
	.align	2
.L11:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_ClrInt, .-DRV_VENC_HAL_V500R001_ClrInt
	.align	2
	.global	DRV_VENC_HAL_V500R001_DisableInt
	.type	DRV_VENC_HAL_V500R001_DisableInt, %function
DRV_VENC_HAL_V500R001_DisableInt:
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
	ldr	r2, [r3]
	bic	r2, r2, #64
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L21:
	mov	r2, #0
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L16:
	ldr	r2, [r3]
	bic	r2, r2, #1
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L15:
	ldr	r2, [r3]
	bic	r2, r2, #2
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L23:
	.align	2
.L22:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_DisableInt, .-DRV_VENC_HAL_V500R001_DisableInt
	.align	2
	.global	DRV_VENC_HAL_V500R001_ReadReg_Smmu
	.type	DRV_VENC_HAL_V500R001_ReadReg_Smmu, %function
DRV_VENC_HAL_V500R001_ReadReg_Smmu:
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
	.size	DRV_VENC_HAL_V500R001_ReadReg_Smmu, .-DRV_VENC_HAL_V500R001_ReadReg_Smmu
	.align	2
	.global	DRV_VENC_HAL_V500R001_ReadReg
	.type	DRV_VENC_HAL_V500R001_ReadReg, %function
DRV_VENC_HAL_V500R001_ReadReg:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, .L40
	cmp	r0, #0
	ldmia	r2, {r3, ip}
	ldmeqfd	sp, {fp, sp, pc}
	add	r3, r3, #12288
	ldr	r2, [r3, #4]
	and	r2, r2, #1
	str	r2, [r0, #8]
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #2, #1
	str	r2, [r0, #12]
	ldr	r1, [r3, #4]
	ubfx	r1, r1, #6, #1
	str	r1, [r0]
	ldr	r1, [r3, #4]
	ubfx	r1, r1, #1, #1
	str	r1, [r0, #4]
	ldr	r1, [r3, #4]
	ubfx	r1, r1, #3, #1
	str	r1, [r0, #16]
	orrs	r2, r1, r2
	bne	.L33
	ldr	r2, [ip, #4]
	cmp	r2, #0
	beq	.L39
	ldr	r2, [r3, #1984]
	mov	r2, r2, asl #3
	str	r2, [r0, #20]
	ldr	r2, [r3, #2756]
	ldr	ip, [r3, #2788]
	ubfx	r1, r2, #0, #19
	ubfx	r2, ip, #0, #17
	add	r2, r1, r2
.L35:
	add	r1, r2, #3
	cmp	r2, #0
	movlt	r2, r1
	mov	r2, r2, asr #2
	str	r2, [r0, #28]
	ldr	r2, [r3, #1992]
	str	r2, [r0, #32]
	ldr	r2, [r3, #1996]
	str	r2, [r0, #36]
	ldr	r2, [r3, #448]
	bic	r2, r2, #-33554432
	str	r2, [r0, #40]
	ldr	r2, [r3, #452]
	bic	r2, r2, #-33554432
	str	r2, [r0, #44]
.L33:
	ldr	r1, [r3, #2116]
	ldr	r2, [r3, #2120]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #48]
	ldr	r1, [r3, #2124]
	ldr	r2, [r3, #2128]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #52]
	ldr	r1, [r3, #2132]
	ldr	r2, [r3, #2136]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #56]
	ldr	r1, [r3, #2140]
	ldr	r2, [r3, #2144]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #60]
	ldr	r1, [r3, #2148]
	ldr	r2, [r3, #2152]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #64]
	ldr	r1, [r3, #2156]
	ldr	r2, [r3, #2160]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #68]
	ldr	r1, [r3, #2164]
	ldr	r2, [r3, #2168]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #72]
	ldr	r1, [r3, #2172]
	ldr	r2, [r3, #2176]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #76]
	ldr	r1, [r3, #2180]
	ldr	r2, [r3, #2184]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #80]
	ldr	r1, [r3, #2188]
	ldr	r2, [r3, #2192]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #84]
	ldr	r1, [r3, #2196]
	ldr	r2, [r3, #2200]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #88]
	ldr	r1, [r3, #2204]
	ldr	r2, [r3, #2208]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #92]
	ldr	r1, [r3, #2212]
	ldr	r2, [r3, #2216]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #96]
	ldr	r1, [r3, #2220]
	ldr	r2, [r3, #2224]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #100]
	ldr	r1, [r3, #2228]
	ldr	r2, [r3, #2232]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #104]
	ldr	r1, [r3, #2236]
	ldr	r2, [r3, #2240]
	bic	r1, r1, #-536870912
	and	r2, r2, #127
	rsb	r2, r2, r1
	str	r2, [r0, #108]
	ldr	r2, [r3, #2120]
	mov	r2, r2, lsr #31
	str	r2, [r0, #112]
	ldr	r2, [r3, #2128]
	mov	r2, r2, lsr #31
	str	r2, [r0, #116]
	ldr	r2, [r3, #2136]
	mov	r2, r2, lsr #31
	str	r2, [r0, #120]
	ldr	r2, [r3, #2144]
	mov	r2, r2, lsr #31
	str	r2, [r0, #124]
	ldr	r2, [r3, #2152]
	mov	r2, r2, lsr #31
	str	r2, [r0, #128]
	ldr	r2, [r3, #2160]
	mov	r2, r2, lsr #31
	str	r2, [r0, #132]
	ldr	r2, [r3, #2168]
	mov	r2, r2, lsr #31
	str	r2, [r0, #136]
	ldr	r2, [r3, #2176]
	mov	r2, r2, lsr #31
	str	r2, [r0, #140]
	ldr	r2, [r3, #2184]
	mov	r2, r2, lsr #31
	str	r2, [r0, #144]
	ldr	r2, [r3, #2192]
	mov	r2, r2, lsr #31
	str	r2, [r0, #148]
	ldr	r2, [r3, #2200]
	mov	r2, r2, lsr #31
	str	r2, [r0, #152]
	ldr	r2, [r3, #2208]
	mov	r2, r2, lsr #31
	str	r2, [r0, #156]
	ldr	r2, [r3, #2216]
	mov	r2, r2, lsr #31
	str	r2, [r0, #160]
	ldr	r2, [r3, #2224]
	mov	r2, r2, lsr #31
	str	r2, [r0, #164]
	ldr	r2, [r3, #2232]
	mov	r2, r2, lsr #31
	str	r2, [r0, #168]
	ldr	r3, [r3, #2240]
	mov	r3, r3, lsr #31
	str	r3, [r0, #172]
	ldmfd	sp, {fp, sp, pc}
.L39:
	ldr	r2, [r3, #2112]
	mov	r2, r2, asl #3
	str	r2, [r0, #20]
	ldr	r1, [r3, #2760]
	ldr	lr, [r3, #2764]
	ldr	r2, [r3, #2792]
	ubfx	ip, r1, #0, #19
	ubfx	r1, lr, #0, #19
	add	r1, ip, r1
	ubfx	r2, r2, #0, #19
	add	r2, r1, r2
	b	.L35
.L41:
	.align	2
.L40:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_ReadReg, .-DRV_VENC_HAL_V500R001_ReadReg
	.global	__aeabi_uidiv
	.align	2
	.global	DRV_VENC_HAL_V500R001_CfgReg
	.type	DRV_VENC_HAL_V500R001_CfgReg, %function
DRV_VENC_HAL_V500R001_CfgReg:
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
	subs	r7, r0, #0
	beq	.L42
	ldr	r0, .L140
	mov	r2, #680
	ldr	r3, .L140+4
	mov	r1, r7
	ldr	r5, [r7, #676]
	ldr	r4, [r0, #4]
	ldr	r3, [r3, #4]
	ldr	r9, [r0]
	mov	r0, r4
	blx	r3
	ldr	r3, [r7, #4]
	cmp	r3, #0
	bne	.L44
	ldr	r3, .L140+8
	add	r2, r4, #848
	ldr	r10, [fp, #-48]
	add	r0, r3, #160
	str	r2, [fp, #-60]
.L45:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L45
	ldr	r3, .L140+12
	add	r2, r4, #1008
	str	r10, [fp, #-48]
	add	r0, r3, #160
.L46:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L46
	mov	r2, #7
	mov	r3, #4
	mov	r1, #9
	str	r3, [r4, #780]
	str	r2, [r4, #808]
	mov	r3, #32
	str	r2, [r4, #812]
	str	r3, [r4, #1200]
	mov	r3, #0
	str	r2, [r4, #816]
	mov	r2, #14
	str	r3, [r4, #788]
	str	r3, [r4, #792]
	str	r3, [r4, #796]
	str	r3, [r4, #800]
	str	r3, [r4, #804]
	mov	r3, #11
	str	r2, [r4, #828]
	mov	r2, #25
	str	r3, [r4, #824]
	mov	r3, #18
	str	r10, [fp, #-48]
	str	r3, [r4, #832]
	mov	r3, #255
	str	r1, [r4, #820]
	str	r2, [r4, #836]
	str	r3, [r4, #840]
	str	r3, [r4, #844]
	str	r3, [r4, #848]
.L47:
	ldr	r3, [r7, #40]
	ldr	r2, [r7, #12]
	cmp	r3, #0
	beq	.L50
	cmp	r2, #1920
	movcs	r3, #3
	strcs	r3, [r4, #1204]
	bcs	.L50
	cmp	r2, #720
	movcs	r3, #2
	movcc	r3, #1
	str	r3, [r4, #1204]
.L50:
	ldmib	r7, {r2, r3}
	cmp	r2, #0
	bne	.L53
	cmp	r3, #3
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #1216]
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r4, #1212]
	moveq	r3, #7
	movne	r3, #5
	str	r3, [r4, #1208]
.L55:
	ldr	r3, [r7, #12]
	sub	r3, r3, #128
	cmp	r3, #127
	addhi	r8, r4, #4096
	bhi	.L56
	ldr	r3, [r7, #4]
	add	r8, r4, #4096
	cmp	r3, #0
	bne	.L56
	mov	r2, #28
	str	r2, [r7, #528]
	str	r2, [r7, #524]
	str	r2, [r7, #520]
	str	r3, [r4, #780]
	str	r3, [r7, #20]
	str	r3, [r8, #200]
	str	r3, [r4, #3880]
	str	r3, [r4, #3876]
	str	r3, [r4, #3624]
	str	r3, [r4, #3372]
	str	r3, [r4, #2460]
	str	r3, [r8, #172]
.L56:
	ldr	ip, [r7, #672]
	mov	r0, #0
	mov	r1, r0
	bfc	r1, #16, #1
	mov	r2, #207
	mov	r3, r0
	str	ip, [r9, #280]
	mov	ip, #4
	bfi	r1, ip, #13, #3
	str	r2, [r9]
	bfi	r1, ip, #10, #3
	ldr	lr, [r4, #3508]
	mov	r2, #3
	bfi	r1, r2, #7, #3
	mov	r2, #1
	bfi	r1, r2, #5, #2
	str	lr, [r9, #16]
	bfi	r1, ip, #2, #3
	ldr	lr, [r4, #3468]
	bfi	r1, r2, #0, #2
	str	r2, [fp, #-56]
	mov	ip, r0
	ldr	r2, [r4, #3472]
	bfi	r0, lr, #31, #1
	ldr	lr, [r4, #3516]
	bfi	r0, r2, #30, #1
	ldr	r2, [r4, #3520]
	sub	lr, lr, #1
	bfi	r0, lr, #16, #9
	sub	lr, r2, #1
	bfi	r0, lr, #0, #9
	str	r0, [r9, #20]
	ldr	r0, [r8, #356]
	str	r0, [r9, #24]
	ldr	r0, [r8, #352]
	ldr	lr, [r8, #348]
	bfi	r3, r0, #21, #1
	ldr	r0, [r8, #200]
	bfi	r3, lr, #19, #2
	ldr	lr, [r8, #228]
	orr	r3, r3, #458752
	ldr	r2, [r8, #204]
	bfi	r3, r0, #2, #1
	ldr	r0, [r8, #212]
	bfi	r3, lr, #23, #1
	bfi	r3, r2, #3, #1
	ldr	r2, [r8, #208]
	bfi	r3, r2, #1, #1
	bfi	r3, r0, #0, #1
	str	r3, [r9, #52]
	ldr	r0, [r8, #256]
	ldr	r3, [r8, #260]
	bfi	ip, r0, #4, #4
	bfi	ip, r3, #0, #4
	str	ip, [r9, #56]
	str	r1, [r9, #68]
	ldr	r3, [r7, #4]
	ldr	r0, [r7, #12]
	cmp	r3, #0
	sub	r0, r0, #1
	moveq	r3, #16
	movne	r3, #32
	mov	r1, r3
	add	r0, r0, r3
	str	r3, [fp, #-52]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-52]
	mov	r1, r3
	mov	r10, r0
	ldr	r0, [r7, #16]
	sub	r0, r0, #1
	add	r0, r0, r3
	bl	__aeabi_uidiv
	mul	r1, r10, r0
	ldr	r0, [r7, #516]
	bl	__aeabi_uidiv
	ldr	r2, .L140
	mov	ip, #0
	mov	r1, ip
	mov	r3, ip
	ldr	r2, [r2]
	str	r2, [fp, #-52]
	bfi	ip, r0, #0, #20
	str	ip, [r9, #588]
	ldr	r0, [r4, #3928]
	bfi	r1, r0, #0, #4
	str	r1, [r9, #592]
	ldr	ip, [r7, #4]
	ldr	r0, [r4, #3972]
	cmp	ip, #2
	ldr	r1, [r4, #1212]
	bfi	r3, r0, #31, #1
	ldr	r0, [r4, #1216]
	ldr	r2, [fp, #-56]
	bfc	r3, #28, #2
	bfieq	r3, r2, #26, #2
	beq	.L59
	cmp	ip, #0
	bfieq	r3, ip, #26, #2
	orrne	r3, r3, #201326592
.L59:
	ldr	lr, [r4, #3676]
	subs	r2, ip, #2
	ldr	ip, [r7, #512]
	bfi	r3, lr, #30, #1
	ldr	lr, [r4, #3664]
	bfi	r3, r1, #18, #2
	ldr	r1, [r4, #3660]
	movne	r2, #1
	bfi	r3, r1, #21, #1
	clz	r1, ip
	bfi	r3, lr, #17, #1
	ldr	lr, [r4, #3496]
	bfi	r3, ip, #16, #1
	mov	r1, r1, lsr #5
	bfi	r3, r0, #12, #1
	ldr	r0, [r4, #1316]
	ldr	ip, [r4, #3644]
	bfi	r3, r1, #10, #2
	bfi	r3, r0, #9, #1
	ldr	r1, [r4, #3696]
	ldr	r0, [r4, #3700]
	bfi	r3, ip, #8, #1
	bfi	r3, r1, #7, #1
	ldr	ip, [r7, #40]
	ldr	r1, [r7, #56]
	bfi	r3, r0, #6, #1
	bfi	r3, ip, #5, #1
	mov	ip, #0
	adds	r0, r1, #0
	bfi	r3, r2, #2, #2
	bfc	r3, #15, #1
	mov	r1, ip
	movne	r0, #1
	bfi	r3, r0, #4, #1
	orr	r3, r3, #2
	mov	r2, ip
	bfi	r3, lr, #0, #1
	ldr	lr, [fp, #-52]
	mov	r0, ip
	str	r3, [lr, #28]
	mov	r3, ip
	ldr	lr, [r4, #3872]
	mov	r10, lr
	ldr	lr, [r4, #3868]
	bfi	ip, lr, #16, #9
	bfi	ip, r10, #0, #9
	str	ip, [r5]
	ldr	lr, [r7, #20]
	ldr	ip, [r7, #28]
	bfi	r1, lr, #17, #1
	orr	r1, r1, #65536
	bfi	r1, ip, #0, #16
	str	r1, [r5, #8]
	ldr	r1, [r7, #520]
	ldr	ip, [r4, #3524]
	bfi	r2, r1, #10, #6
	ldr	r1, [r4, #3528]
	bfi	r2, ip, #5, #5
	ldr	ip, [r4, #2460]
	bfi	r2, r1, #0, #5
	ldr	r1, [r4, #2444]
	bfi	r2, ip, #18, #1
	bfi	r2, r1, #19, #1
	str	r2, [r5, #12]
	ldr	r2, [r4, #3684]
	ldr	r1, [r4, #3688]
	bfi	r0, r2, #8, #2
	ldr	r2, [r4, #3692]
	bfi	r0, r1, #4, #4
	bfi	r0, r2, #0, #4
	str	r0, [r5, #16]
	ldr	r1, [r7, #16]
	ldr	r2, [r7, #12]
	sub	r1, r1, #1
	sub	r2, r2, #1
	bfi	r3, r1, #16, #13
	bfi	r3, r2, #0, #13
	str	r3, [r5, #4]
	ldr	r3, [r4, #4080]
	cmp	r3, #1
	ldrne	r2, [r4, #3704]
	movne	r3, #0
	moveq	r3, #3
	bfine	r3, r2, #0, #2
	str	r3, [r5, #20]
	ldr	r1, [r4, #3712]
	mov	r3, #0
	mov	r2, r3
	bfi	r3, r1, #0, #1
	mov	r1, r2
	bfc	r3, #1, #1
	str	r3, [r5, #24]
	ldr	r0, [r4, #3616]
	mov	r3, r2
	bfi	r2, r0, #12, #4
	ldr	r0, [r4, #3620]
	bfi	r2, r0, #8, #4
	ldr	r0, [r4, #3632]
	bfi	r2, r0, #4, #1
	ldr	r0, [r4, #1208]
	bfi	r2, r0, #0, #3
	ldr	r0, [r4, #3636]
	bfi	r2, r0, #5, #1
	str	r2, [r5, #28]
	ldr	r0, [r4, #3584]
	mov	r2, r1
	bfi	r1, r0, #12, #1
	ldr	r0, [r4, #3592]
	bfi	r1, r0, #4, #2
	orr	r1, r1, #3
	str	r1, [r5, #32]
	ldr	r0, [r4, #3908]
	mov	r1, r3
	bfi	r3, r0, #4, #1
	ldr	r0, [r4, #3624]
	bfi	r3, r0, #2, #1
	ldr	r0, [r4, #3628]
	bfi	r3, r0, #3, #1
	ldr	r0, [r4, #3876]
	bfi	r3, r0, #1, #1
	ldr	r0, [r4, #3880]
	bfi	r3, r0, #0, #1
	str	r3, [r5, #36]
	ldr	r0, [r4, #3884]
	mov	r3, r2
	bfi	r2, r0, #16, #16
	ldr	r0, [r4, #3888]
	bfi	r2, r0, #0, #16
	str	r2, [r5, #40]
	ldr	r0, [r4, #3892]
	mov	r2, r1
	bfi	r1, r0, #24, #8
	ldr	r0, [r4, #3896]
	bfi	r1, r0, #16, #8
	ldr	r0, [r4, #3900]
	bfi	r1, r0, #8, #8
	ldr	r0, [r4, #3904]
	bfi	r1, r0, #0, #8
	str	r1, [r5, #44]
	ldr	r0, [r4, #776]
	mov	r1, r3
	bfc	r1, #4, #2
	bfi	r3, r0, #1, #1
	ldr	r0, [r8, #188]
	bfc	r1, #2, #2
	bfi	r3, r0, #16, #8
	ldr	r0, [r8, #184]
	orr	r1, r1, #2
	bfi	r3, r0, #24, #8
	str	r3, [r5, #48]
	ldr	r0, [r4, #680]
	mov	r3, r2
	bfi	r2, r0, #2, #1
	ldr	r0, [r4, #684]
	bfi	r2, r0, #1, #1
	ldr	r0, [r4, #1320]
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #3912]
	bfi	r2, r0, #3, #1
	ldr	r0, [r4, #3916]
	str	r1, [r5, #56]
	bfi	r2, r0, #4, #1
	str	r2, [r5, #52]
	ldr	r1, [r4, #2428]
	mov	r2, r3
	ldr	r0, [r4, #2432]
	bfi	r3, r1, #0, #1
	ldr	r1, [r4, #772]
	bfi	r3, r0, #1, #1
	ldr	r0, [r4, #2456]
	bfi	r3, r1, #2, #1
	ldr	r1, [r4, #2424]
	bfi	r3, r0, #4, #1
	ldr	r0, [r4, #768]
	bfi	r3, r1, #9, #1
	ldr	r1, [r4, #2476]
	bfi	r3, r0, #8, #1
	ldr	r0, [r4, #2532]
	bfi	r3, r1, #3, #1
	ldr	r1, [r4, #2416]
	bfi	r3, r0, #15, #1
	ldr	r0, [r4, #2420]
	bfi	r3, r1, #14, #1
	ldr	r1, [r4, #2528]
	bfi	r3, r0, #13, #1
	ldr	r0, [r4, #2524]
	ldr	ip, [r4, #2520]
	bfi	r3, r1, #12, #1
	bfi	r3, r0, #11, #1
	ldr	r1, [r4, #2464]
	bfi	r3, ip, #10, #1
	bfi	r3, r1, #18, #1
	str	r3, [r5, #60]
	ldr	r0, [r8, #172]
	mov	r3, r2
	ldr	r1, [r8, #176]
	bfi	r2, r0, #8, #1
	bfi	r2, r1, #0, #8
	str	r2, [r5, #64]
	ldr	r1, [r8, #180]
	mov	r2, r3
	bfi	r3, r1, #0, #1
	str	r3, [r5, #68]
	ldr	r1, [r8, #344]
	mov	r3, r2
	ldr	r0, [r8, #340]
	bfi	r2, r1, #0, #1
	ldr	r1, [r8, #336]
	bfi	r2, r0, #1, #1
	ldr	r0, [r8, #332]
	bfi	r2, r1, #2, #1
	ldr	r1, [r8, #328]
	bfi	r2, r0, #3, #1
	ldr	r0, [r8, #324]
	bfi	r2, r1, #4, #1
	ldr	ip, [r8, #320]
	ldr	r1, [r8, #280]
	bfi	r2, r0, #5, #1
	bfi	r2, ip, #6, #1
	bfi	r2, r1, #7, #1
	str	r2, [r5, #72]
	ldr	r2, [r8, #316]
	ldr	r1, [r8, #312]
	bfi	r3, r2, #0, #1
	ldr	r2, [r8, #308]
	bfi	r3, r1, #1, #1
	ldr	r1, [r8, #304]
	bfi	r3, r2, #2, #1
	ldr	r2, [r8, #272]
	bfi	r3, r1, #3, #1
	ldr	r1, [r8, #276]
	bfi	r3, r2, #4, #1
	ldr	r2, [r8, #300]
	bfi	r3, r1, #5, #1
	ldr	r1, [r8, #296]
	bfi	r3, r2, #6, #1
	ldr	r2, [r8, #284]
	bfi	r3, r1, #7, #1
	ldr	r1, [r8, #292]
	bfi	r3, r2, #8, #1
	ldr	r2, [r8, #288]
	bfi	r3, r1, #9, #1
	bfi	r3, r2, #10, #1
	str	r3, [r5, #76]
	ldr	r3, [r7, #4]
	ldr	r2, [r7, #676]
	cmp	r3, #2
	beq	.L138
	cmp	r3, #0
	bne	.L64
	mov	r3, #15
	mov	r1, #0
	bfi	r1, r3, #16, #6
	mov	r3, #31
	bfi	r1, r3, #0, #7
	str	r1, [fp, #-64]
.L64:
	ldr	r3, [r7, #56]
	mov	r1, #1
	cmp	r3, #0
	ldrne	r3, [fp, #-64]
	ldreq	r3, [fp, #-52]
	ldreq	r2, [fp, #-64]
	strne	r3, [r2, #80]
	streq	r2, [r3, #124]
	mov	r3, #0
	bfi	r3, r1, #16, #6
	movw	r2, #43691
	bfi	r3, r1, #0, #7
	str	r3, [r9, #128]
	ldr	r3, [r7, #144]
	movt	r2, 43690
	mov	r1, r2
	mov	r2, #0
	mov	lr, r2
	mov	ip, r2
	add	r3, r7, r3, lsl #2
	str	r2, [fp, #-56]
	mov	r2, r1
	mov	r10, lr
	ldr	r3, [r3, #132]
	str	r3, [r5, #88]
	ldr	r3, [r7, #144]
	add	r3, r3, #2
	umull	r0, r1, r3, r1
	mov	r1, r1, lsr #1
	add	r1, r1, r1, lsl #1
	rsb	r1, r1, r3
	add	r1, r7, r1, lsl #2
	ldr	r3, [r1, #132]
	str	r3, [r5, #92]
	mov	r3, r2
	ldr	r1, [r7, #144]
	add	r1, r1, #1
	umull	r2, r3, r1, r3
	mov	r2, lr
	mov	r3, r3, lsr #1
	add	r3, r3, r3, lsl #1
	rsb	r3, r3, r1
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #132]
	str	r3, [r5, #96]
	ldr	r3, [r7, #172]
	str	r3, [r5, #100]
	ldr	r3, [r7, #68]
	str	r3, [r5, #104]
	ldr	r3, [r7, #72]
	str	r3, [r5, #108]
	ldr	r3, [r7, #76]
	str	r3, [r5, #112]
	ldr	r1, [r7, #80]
	ldr	r3, [r7, #84]
	bfi	r2, r1, #16, #16
	bfi	r2, r3, #0, #16
	str	r2, [r5, #124]
	ldr	r3, [r7, #112]
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #88]
	str	r3, [r5, #128]
	ldr	r3, [r7, #112]
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #96]
	str	r3, [r5, #132]
	ldr	r2, [r7, #104]
	ldr	r3, [r7, #108]
	bfi	lr, r2, #0, #16
	bfi	lr, r3, #16, #16
	str	lr, [r5, #136]
	ldr	r3, [r7, #112]
	cmp	r3, ip
	moveq	r3, #84
	movne	r3, #80
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	str	r3, [r5, #152]
	ldr	r3, [r7, #112]
	cmp	r3, ip
	moveq	r3, #92
	movne	r3, #88
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	str	r3, [r5, #156]
	ldr	r2, [r7, #104]
	ldr	r3, [r7, #108]
	bfi	ip, r2, #16, #16
	bfi	ip, r3, #0, #16
	str	ip, [r5, #160]
	ldr	r3, [r7, #112]
	cmp	r3, r10
	moveq	r3, #124
	movne	r3, #120
	add	r3, r7, r3
	ldr	r3, [r3, #4]
	str	r3, [r5, #176]
	ldr	r3, [r7, #112]
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #124]
	str	r3, [r5, #208]
	ldr	r3, [r7, #112]
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #116]
	str	r3, [r5, #216]
	ldr	r3, [r7, #112]
	cmp	r3, r10
	moveq	r3, #116
	movne	r3, #112
	add	r3, r7, r3
	ldr	r3, [r3, #4]
	str	r3, [r5, #220]
	ldr	r3, [r7, #176]
	str	r3, [r5, #224]
	ldr	r3, [r7, #308]
	str	r3, [r5, #228]
	ldr	r3, [r7, #304]
	str	r3, [r5, #232]
	ldr	r3, [r7, #60]
	ldr	r1, [r8, #8]
	cmp	r3, r10
	ldr	r2, [r7, #676]
	bfi	r10, r1, #14, #1
	mov	r0, r10
	bne	.L67
	ldr	r1, [r7, #64]
	clz	r1, r1
	mov	r1, r1, lsr #5
	bfi	r0, r1, #16, #8
	b	.L141
.L142:
	.align	2
.L140:
	.word	.LANCHOR0
	.word	venc_Osal_Func_Ptr_S
	.word	.LANCHOR1-4
	.word	.LANCHOR1+156
.L141:
.L68:
	mov	r1, r0
	bfi	r1, r3, #6, #4
	bfc	r1, #3, #3
	ldr	r3, [r7, #56]
	bfc	r1, #2, #1
	cmp	r3, #0
	mov	r3, r1
	bfc	r3, #1, #1
	bfc	r3, #0, #1
	strne	r3, [r2, #236]
	mov	r0, r3
	ldreq	r3, [fp, #-52]
	moveq	r2, r0
	streq	r2, [r3, #284]
	mov	r3, #0
	str	r3, [r5, #256]
	mov	r2, r3
	ldr	r1, [r4, #688]
	ldr	r3, [r4, #1332]
	bfi	r2, r1, #16, #5
	ldr	r1, [r4, #1708]
	bfi	r2, r3, #0, #8
	mov	r3, #0
	bfi	r2, r1, #24, #4
	str	r2, [r5, #332]
	ldr	r1, [r4, #1972]
	mov	r2, r3
	ldr	r0, [r4, #1976]
	bfi	r3, r1, #0, #3
	ldr	r1, [r4, #1980]
	bfi	r3, r0, #3, #7
	ldr	r0, [r4, #1988]
	bfi	r3, r1, #10, #3
	ldr	r1, [r4, #1996]
	bfi	r3, r0, #18, #4
	bfi	r3, r1, #26, #4
	str	r3, [r5, #336]
	ldr	r0, [r4, #1804]
	mov	r1, r2
	ldr	r3, [r4, #1808]
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #1820]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #1824]
	bfi	r2, r0, #15, #6
	bfi	r2, r3, #21, #5
	str	r2, [r5, #340]
	ldr	r2, [r4, #1344]
	mov	r3, r1
	ldr	r0, [r4, #692]
	bfi	r1, r2, #16, #5
	ldr	r2, [r4, #1716]
	bfi	r1, r0, #0, #8
	bfi	r1, r2, #24, #4
	str	r1, [r5, #344]
	ldr	r1, [r4, #2000]
	mov	r2, r3
	ldr	r0, [r4, #2004]
	bfi	r3, r1, #0, #3
	ldr	r1, [r4, #2008]
	bfi	r3, r0, #3, #7
	ldr	r0, [r4, #2016]
	bfi	r3, r1, #10, #3
	ldr	r1, [r4, #2024]
	bfi	r3, r0, #18, #4
	bfi	r3, r1, #26, #4
	str	r3, [r5, #348]
	ldr	r0, [r4, #1828]
	mov	r1, r2
	ldr	r3, [r4, #1832]
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #1844]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #1848]
	bfi	r2, r0, #15, #6
	bfi	r2, r3, #21, #5
	str	r2, [r5, #352]
	ldr	r2, [r4, #704]
	mov	r3, r1
	ldr	r0, [r4, #708]
	bfi	r1, r2, #16, #5
	ldr	r2, [r4, #1732]
	bfi	r1, r0, #0, #8
	bfi	r1, r2, #24, #4
	str	r1, [r5, #356]
	ldr	r1, [r4, #2052]
	mov	r2, r3
	ldr	r0, [r4, #2056]
	bfi	r3, r1, #0, #3
	ldr	r1, [r4, #2060]
	bfi	r3, r0, #3, #7
	ldr	r0, [r4, #2068]
	bfi	r3, r1, #10, #3
	ldr	r1, [r4, #2076]
	bfi	r3, r0, #18, #4
	bfi	r3, r1, #26, #4
	str	r3, [r5, #360]
	ldr	r0, [r4, #1876]
	mov	r1, r2
	ldr	r3, [r4, #1880]
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #1892]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #1896]
	bfi	r2, r0, #15, #6
	bfi	r2, r3, #21, #5
	str	r2, [r5, #364]
	ldr	r2, [r4, #740]
	mov	r3, r1
	ldr	r0, [r4, #744]
	bfi	r1, r2, #0, #8
	ldr	r2, [r4, #1740]
	bfi	r1, r0, #16, #5
	bfi	r1, r2, #24, #4
	str	r1, [r5, #368]
	ldr	r1, [r4, #1624]
	mov	r2, r3
	ldr	r0, [r4, #1628]
	bfi	r3, r1, #0, #3
	ldr	r1, [r4, #1632]
	bfi	r3, r0, #3, #7
	ldr	r0, [r4, #1640]
	bfi	r3, r1, #10, #3
	ldr	r1, [r4, #1648]
	bfi	r3, r0, #18, #4
	bfi	r3, r1, #26, #4
	str	r3, [r5, #372]
	ldr	r0, [r4, #1900]
	mov	r1, r2
	ldr	r3, [r4, #1904]
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #1916]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #1920]
	bfi	r2, r0, #15, #6
	bfi	r2, r3, #21, #5
	str	r2, [r5, #376]
	ldr	r2, [r4, #696]
	mov	r3, r1
	ldr	r0, [r4, #700]
	bfi	r1, r2, #16, #5
	ldr	r2, [r4, #1724]
	bfi	r1, r0, #0, #8
	bfi	r1, r2, #24, #4
	str	r1, [r5, #380]
	ldr	r1, [r4, #748]
	mov	r2, r3
	ldr	r0, [r4, #2028]
	bfi	r3, r1, #0, #3
	ldr	r1, [r4, #2032]
	bfi	r3, r0, #3, #7
	ldr	r0, [r4, #2040]
	bfi	r3, r1, #10, #3
	ldr	r1, [r4, #2048]
	bfi	r3, r0, #18, #4
	bfi	r3, r1, #26, #4
	str	r3, [r5, #384]
	ldr	r0, [r4, #1852]
	mov	r1, r2
	ldr	r3, [r4, #1856]
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #1868]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #1872]
	bfi	r2, r0, #15, #6
	bfi	r2, r3, #21, #5
	str	r2, [r5, #388]
	ldr	r2, [r4, #1780]
	mov	r3, r1
	ldr	r0, [r4, #1784]
	bfi	r1, r2, #0, #8
	ldr	r2, [r4, #1748]
	bfi	r1, r0, #16, #5
	bfi	r1, r2, #24, #4
	str	r1, [r5, #392]
	ldr	r1, [r4, #1652]
	mov	r2, r3
	ldr	r0, [r4, #1656]
	bfi	r3, r1, #0, #3
	ldr	r1, [r4, #1660]
	bfi	r3, r0, #3, #7
	ldr	r0, [r4, #1668]
	bfi	r3, r1, #10, #3
	ldr	r1, [r4, #1676]
	bfi	r3, r0, #18, #4
	bfi	r3, r1, #26, #4
	str	r3, [r5, #396]
	ldr	r0, [r4, #1924]
	mov	r1, r2
	ldr	r3, [r4, #1928]
	bfi	r2, r0, #0, #1
	ldr	r0, [r4, #1940]
	bfi	r2, r3, #1, #3
	ldr	r3, [r4, #1944]
	bfi	r2, r0, #15, #6
	bfi	r2, r3, #21, #5
	str	r2, [r5, #400]
	ldr	r2, [r4, #1796]
	mov	r3, r1
	ldr	r0, [r4, #1800]
	bfi	r1, r2, #0, #8
	ldr	r2, [r4, #1756]
	bfi	r1, r0, #16, #5
	bfi	r1, r2, #24, #4
	str	r1, [r5, #404]
	ldr	r2, [r4, #1680]
	mov	r1, r3
	ldr	r0, [r4, #1684]
	bfi	r3, r2, #0, #3
	ldr	r2, [r4, #1688]
	bfi	r3, r0, #3, #7
	ldr	r0, [r4, #1696]
	bfi	r3, r2, #10, #3
	ldr	r2, [r4, #1704]
	bfi	r3, r0, #18, #4
	bfi	r3, r2, #26, #4
	str	r3, [r5, #408]
	ldr	r0, [r4, #1948]
	mov	r2, r1
	ldr	r3, [r4, #1952]
	bfi	r1, r0, #0, #1
	ldr	r0, [r4, #1964]
	bfi	r1, r3, #1, #3
	ldr	r3, [r4, #1968]
	bfi	r1, r0, #15, #6
	bfi	r1, r3, #21, #5
	str	r1, [r5, #412]
	ldr	r0, [r4, #1376]
	mov	r3, r2
	ldr	r1, [r4, #1372]
	bfi	r2, r0, #0, #4
	ldr	r0, [r4, #1368]
	bfi	r2, r1, #4, #4
	ldr	r1, [r4, #1388]
	bfi	r2, r0, #8, #4
	ldr	r0, [r4, #1384]
	bfi	r2, r1, #16, #4
	ldr	r1, [r4, #712]
	bfi	r2, r0, #20, #4
	bfi	r2, r1, #24, #4
	str	r2, [r5, #416]
	ldr	r0, [r4, #1456]
	mov	r2, r3
	ldr	r1, [r4, #1452]
	bfi	r3, r0, #0, #4
	ldr	r0, [r4, #724]
	bfi	r3, r1, #4, #4
	ldr	r1, [r4, #1472]
	bfi	r3, r0, #8, #4
	ldr	r0, [r4, #1468]
	bfi	r3, r1, #16, #4
	ldr	r1, [r4, #1464]
	bfi	r3, r0, #20, #4
	bfi	r3, r1, #24, #4
	str	r3, [r5, #420]
	ldr	r0, [r4, #1540]
	mov	r3, r2
	ldr	r1, [r4, #1536]
	bfi	r2, r0, #0, #4
	ldr	r0, [r4, #736]
	bfi	r2, r1, #4, #4
	ldr	r1, [r4, #1556]
	bfi	r2, r0, #8, #4
	ldr	r0, [r4, #1552]
	bfi	r2, r1, #16, #4
	ldr	r1, [r4, #1548]
	bfi	r2, r0, #20, #4
	bfi	r2, r1, #24, #4
	str	r2, [r5, #424]
	ldr	r0, [r4, #1396]
	mov	r2, r3
	ldr	r1, [r4, #1400]
	bfi	r3, r0, #8, #4
	ldr	r0, [r4, #1404]
	bfi	r3, r1, #4, #4
	ldr	r1, [r4, #1412]
	bfi	r3, r0, #0, #4
	ldr	r0, [r4, #716]
	bfi	r3, r1, #24, #4
	ldr	r1, [r4, #1416]
	bfi	r3, r0, #20, #4
	bfi	r3, r1, #16, #4
	str	r3, [r5, #428]
	ldr	r0, [r4, #1480]
	mov	r3, r2
	ldr	r1, [r4, #728]
	bfi	r2, r0, #8, #4
	ldr	r0, [r4, #1484]
	bfi	r2, r1, #4, #4
	ldr	r1, [r4, #1492]
	bfi	r2, r0, #0, #4
	ldr	r0, [r4, #1496]
	bfi	r2, r1, #24, #4
	ldr	r1, [r4, #1500]
	bfi	r2, r0, #20, #4
	bfi	r2, r1, #16, #4
	str	r2, [r5, #432]
	ldr	r0, [r4, #1564]
	mov	r2, r3
	ldr	r1, [r4, #1568]
	bfi	r3, r0, #8, #4
	ldr	r0, [r4, #1572]
	bfi	r3, r1, #4, #4
	ldr	r1, [r4, #1580]
	bfi	r3, r0, #0, #4
	ldr	r0, [r4, #1584]
	bfi	r3, r1, #24, #4
	ldr	r1, [r4, #1588]
	bfi	r3, r0, #20, #4
	bfi	r3, r1, #16, #4
	str	r3, [r5, #436]
	ldr	r0, [r4, #1424]
	mov	r3, r2
	ldr	r1, [r4, #1428]
	bfi	r2, r0, #8, #4
	ldr	r0, [r4, #1432]
	bfi	r2, r1, #4, #4
	ldr	r1, [r4, #1440]
	bfi	r2, r0, #0, #4
	ldr	r0, [r4, #720]
	bfi	r2, r1, #24, #4
	ldr	r1, [r4, #1444]
	bfi	r2, r0, #20, #4
	bfi	r2, r1, #16, #4
	str	r2, [r5, #440]
	ldr	r0, [r4, #1508]
	mov	r2, r3
	ldr	r1, [r4, #732]
	bfi	r3, r0, #8, #4
	ldr	r0, [r4, #1512]
	bfi	r3, r1, #4, #4
	ldr	r1, [r4, #1520]
	bfi	r3, r0, #0, #4
	ldr	r0, [r4, #1524]
	bfi	r3, r1, #24, #4
	ldr	r1, [r4, #1528]
	bfi	r3, r0, #20, #4
	bfi	r3, r1, #16, #4
	str	r3, [r5, #444]
	ldr	r0, [r4, #1596]
	mov	r3, r2
	ldr	r1, [r4, #1600]
	bfi	r2, r0, #8, #4
	ldr	r0, [r4, #1604]
	bfi	r2, r1, #4, #4
	ldr	r1, [r4, #1612]
	bfi	r2, r0, #0, #4
	ldr	r0, [r4, #1616]
	bfi	r2, r1, #24, #4
	ldr	r1, [r4, #1620]
	bfi	r2, r0, #20, #4
	bfi	r2, r1, #16, #4
	str	r2, [r5, #448]
	ldr	r0, [r4, #2080]
	mov	r2, r3
	ldr	r1, [r4, #2084]
	bfi	r3, r0, #0, #4
	ldr	r0, [r4, #2088]
	bfi	r3, r1, #4, #4
	ldr	r1, [r4, #2092]
	bfi	r3, r0, #8, #4
	ldr	r0, [r4, #2096]
	bfi	r3, r1, #12, #4
	ldr	r1, [r4, #2100]
	bfi	r3, r0, #16, #4
	bfi	r3, r1, #20, #4
	str	r3, [r5, #452]
	ldr	r1, [r4, #752]
	mov	r3, r2
	ldr	r0, [r4, #756]
	bfi	r2, r1, #0, #12
	ldr	r1, [r4, #2104]
	bfi	r2, r0, #12, #12
	bfi	r2, r1, #24, #8
	str	r2, [r5, #456]
	ldr	r1, [r4, #2108]
	mov	r2, r3
	ldr	r0, [r4, #2112]
	bfi	r3, r1, #0, #12
	ldr	r1, [r4, #2116]
	bfi	r3, r0, #12, #12
	bfi	r3, r1, #24, #8
	str	r3, [r5, #460]
	ldr	r1, [r4, #760]
	mov	r3, r2
	ldr	r0, [r4, #2120]
	bfi	r2, r1, #0, #12
	ldr	r1, [r4, #2124]
	bfi	r2, r0, #12, #12
	bfi	r2, r1, #24, #8
	str	r2, [r5, #464]
	ldr	r1, [r4, #2128]
	mov	r2, r3
	ldr	r0, [r4, #2132]
	bfi	r3, r1, #0, #8
	ldr	r1, [r4, #2136]
	bfi	r3, r0, #8, #8
	bfi	r3, r1, #16, #8
	str	r3, [r5, #468]
	ldr	r0, [r8, #52]
	mov	r3, r2
	ldr	r1, [r8, #56]
	bfi	r2, r0, #14, #1
	ldr	r0, [r7, #40]
	bfi	r2, r1, #15, #1
	ldr	r1, [r4, #1204]
	bfi	r2, r0, #28, #1
	bfi	r2, r1, #20, #8
	str	r2, [r5, #480]
	ldr	r0, [r8, #72]
	mov	r2, r3
	ldr	r1, [r8, #68]
	bfi	r3, r0, #0, #8
	ldr	r0, [r8, #64]
	bfi	r3, r1, #8, #8
	ldr	r1, [r8, #60]
	bfi	r3, r0, #16, #8
	bfi	r3, r1, #24, #8
	str	r3, [r5, #484]
	ldr	r1, [r4, #2596]
	mov	r3, r2
	bfi	r2, r1, #0, #1
	str	r2, [r5, #488]
	ldr	r1, [r4, #2600]
	mov	r2, r3
	bfi	r3, r1, #0, #16
	str	r3, [r5, #492]
	ldr	r1, [r4, #2604]
	mov	r3, r2
	bfi	r2, r1, #0, #16
	str	r2, [r5, #496]
	ldr	r1, [r4, #2608]
	mov	r2, r3
	bfi	r3, r1, #0, #16
	str	r3, [r5, #500]
	ldr	r0, [r4, #2656]
	mov	r3, r2
	ldr	r1, [r4, #2660]
	bfi	r2, r0, #16, #1
	bfi	r2, r1, #0, #16
	str	r2, [r5, #504]
	ldr	r1, [r4, #2612]
	mov	r2, r3
	ldr	r0, [r4, #2616]
	bfi	r3, r1, #18, #9
	ldr	r1, [r4, #2620]
	bfi	r3, r0, #9, #9
	bfi	r3, r1, #0, #9
	str	r3, [r5, #508]
	ldr	r1, [r4, #2624]
	mov	r3, r2
	ldr	r0, [r4, #2628]
	bfi	r2, r1, #16, #8
	ldr	r1, [r4, #2632]
	bfi	r2, r0, #8, #8
	bfi	r2, r1, #0, #8
	str	r2, [r5, #512]
	ldr	r1, [r4, #2636]
	mov	r2, r3
	ldr	r0, [r4, #2640]
	bfi	r3, r1, #8, #4
	ldr	r1, [r4, #2644]
	bfi	r3, r0, #4, #4
	ldr	r0, [r4, #2652]
	bfi	r3, r1, #0, #4
	ldr	r1, [r4, #2648]
	bfi	r3, r0, #12, #8
	bfi	r3, r1, #20, #8
	str	r3, [r5, #516]
	ldr	r0, [r4, #3356]
	mov	r3, r2
	ldr	r1, [r4, #3352]
	bfi	r2, r0, #0, #8
	ldr	r0, [r4, #3348]
	bfi	r2, r1, #8, #8
	ldr	r1, [r4, #3344]
	bfi	r2, r0, #16, #8
	bfi	r2, r1, #24, #8
	str	r2, [r5, #524]
	ldr	r0, [r4, #2664]
	mov	r1, r3
	ldr	r2, [r4, #2668]
	bfi	r3, r0, #24, #8
	ldr	r0, [r4, #2672]
	bfi	r3, r2, #16, #8
	ldr	r2, [r4, #2676]
	bfi	r3, r0, #8, #8
	bfi	r3, r2, #0, #8
	str	r3, [r5, #528]
	ldr	r0, [r4, #2728]
	mov	r2, r1
	ldr	r3, [r4, #3384]
	bfi	r1, r0, #0, #8
	bfi	r1, r3, #17, #1
	str	r1, [r5, #532]
	ldr	r0, [r4, #2740]
	mov	r3, r2
	ldr	r1, [r4, #2744]
	bfi	r2, r0, #0, #16
	bfi	r2, r1, #16, #16
	str	r2, [r5, #536]
	ldr	r0, [r4, #1172]
	mov	r1, r3
	ldr	r2, [r4, #1176]
	bfi	r3, r0, #22, #9
	ldr	r0, [r4, #1180]
	bfi	r3, r2, #17, #5
	ldr	r2, [r4, #1200]
	bfi	r3, r0, #9, #8
	bfi	r3, r2, #0, #9
	str	r3, [r5, #540]
	ldr	r0, [r4, #1196]
	mov	r2, r1
	ldr	r3, [r4, #3268]
	bfi	r1, r0, #8, #14
	bfi	r1, r3, #0, #8
	str	r1, [r5, #544]
	ldr	r1, [r4, #1184]
	mov	r3, r2
	ldr	r0, [r4, #1188]
	bfi	r2, r1, #16, #8
	ldr	r1, [r4, #1192]
	bfi	r2, r0, #8, #8
	bfi	r2, r1, #0, #8
	str	r2, [r5, #548]
	ldr	r0, [r4, #3276]
	mov	r2, r3
	ldr	r1, [r4, #3280]
	bfi	r3, r0, #18, #1
	ldr	r0, [r4, #3288]
	bfi	r3, r1, #12, #2
	ldr	r1, [r4, #3292]
	bfi	r3, r0, #4, #4
	bfi	r3, r1, #0, #4
	str	r3, [r5, #552]
	ldr	r0, [r4, #3296]
	mov	r3, r2
	ldr	r1, [r4, #3300]
	bfi	r2, r0, #0, #10
	bfi	r2, r1, #16, #9
	str	r2, [r5, #556]
	ldr	r0, [r4, #3304]
	mov	r2, r3
	ldr	r1, [r4, #3308]
	bfi	r3, r0, #0, #10
	bfi	r3, r1, #16, #9
	str	r3, [r5, #560]
	ldr	r0, [r4, #3312]
	mov	r3, r2
	ldr	r1, [r4, #3316]
	bfi	r2, r0, #0, #10
	bfi	r2, r1, #16, #9
	str	r2, [r5, #564]
	ldr	r0, [r4, #3320]
	mov	r2, r3
	ldr	r1, [r4, #3324]
	bfi	r3, r0, #0, #10
	bfi	r3, r1, #16, #9
	str	r3, [r5, #568]
	ldr	r1, [r4, #3328]
	mov	r3, r2
	bfi	r2, r1, #0, #16
	str	r2, [r5, #572]
	ldr	r0, [r4, #3360]
	mov	r2, r3
	ldr	r1, [r4, #3364]
	bfi	r3, r0, #0, #13
	bfi	r3, r1, #13, #1
	str	r3, [r5, #576]
	ldr	r1, [r4, #3368]
	mov	r3, r2
	bfi	r2, r1, #0, #18
	str	r2, [r5, #580]
	ldr	r1, [r4, #3372]
	mov	r2, r3
	bfi	r3, r1, #0, #18
	str	r3, [r5, #584]
	ldr	r0, [r4, #3396]
	mov	r3, r2
	ldr	r1, [r4, #3400]
	bfi	r2, r0, #16, #7
	bfi	r2, r1, #23, #7
	str	r2, [r5, #588]
	ldr	r2, [r4, #3380]
	mov	r1, r3
	ldr	r0, [r4, #3404]
	bfi	r3, r2, #12, #8
	ldr	r2, [r4, #3408]
	bfi	r3, r0, #8, #4
	ldr	r0, [r4, #3412]
	bfi	r3, r2, #0, #8
	ldr	r2, [r4, #3416]
	bfi	r3, r0, #20, #8
	bfi	r3, r2, #28, #4
	str	r3, [r5, #592]
	ldr	r3, [r4, #3388]
	mov	r2, r1
	ldr	r0, [r4, #3392]
	bfi	r1, r3, #0, #8
	ldr	r3, [r4, #3376]
	bfi	r1, r0, #8, #8
	bfi	r1, r3, #16, #8
	str	r1, [r5, #596]
	ldr	r1, [r4, #3420]
	mov	r3, r2
	ldr	r0, [r4, #3424]
	bfi	r2, r1, #0, #8
	ldr	r1, [r4, #3428]
	bfi	r2, r0, #8, #8
	bfi	r2, r1, #16, #16
	str	r2, [r5, #600]
	ldr	r0, [r4, #2680]
	mov	r2, r3
	ldr	r1, [r4, #2684]
	bfi	r3, r0, #24, #8
	ldr	r0, [r4, #2688]
	bfi	r3, r1, #16, #8
	ldr	r1, [r4, #2692]
	bfi	r3, r0, #8, #8
	bfi	r3, r1, #0, #8
	str	r3, [r5, #604]
	ldr	r0, [r4, #2696]
	mov	r3, r2
	ldr	r1, [r4, #2700]
	bfi	r2, r0, #24, #8
	ldr	r0, [r4, #2704]
	bfi	r2, r1, #16, #8
	ldr	r1, [r4, #2708]
	bfi	r2, r0, #8, #8
	bfi	r2, r1, #0, #8
	str	r2, [r5, #608]
	ldr	r0, [r4, #2712]
	mov	r2, r3
	ldr	r1, [r4, #2716]
	bfi	r3, r0, #28, #4
	ldr	r0, [r4, #2720]
	bfi	r3, r1, #23, #5
	ldr	r1, [r4, #2724]
	bfi	r3, r0, #14, #9
	bfi	r3, r1, #0, #14
	str	r3, [r5, #612]
	ldr	r3, [r7, #528]
	ldr	r1, [r4, #3532]
	bfi	r2, r3, #8, #6
	ldr	r3, [r7, #524]
	bfi	r2, r1, #16, #1
	bfi	r2, r3, #0, #6
	str	r2, [r5, #624]
	ldr	r3, [r7, #4]
	ldr	r1, [r7, #16]
	cmp	r3, #0
	ldr	r0, [r7, #516]
	moveq	r1, r1, lsr #4
	movne	r1, r1, lsr #5
	bl	__aeabi_uidiv
	mov	r3, #0
	mov	r2, #2
	bfi	r3, r0, #6, #25
	bfi	r3, r2, #0, #6
	str	r3, [r5, #628]
	ldr	r1, [r4, #2304]
	mov	r3, #0
	mov	r2, r3
	bfi	r3, r1, #0, #16
	str	r3, [r5, #632]
	ldr	r1, [r4, #2276]
	mov	r3, r2
	ldr	r0, [r4, #2252]
	bfi	r2, r1, #8, #6
	ldr	r1, [r4, #2280]
	bfi	r2, r0, #16, #4
	bfi	r2, r1, #0, #6
	str	r2, [r5, #636]
	ldr	r1, [r4, #2264]
	mov	r2, r3
	ldr	r0, [r4, #2244]
	bfi	r3, r1, #8, #6
	ldr	r1, [r4, #2580]
	bfi	r3, r0, #16, #4
	bfi	r3, r1, #0, #6
	str	r3, [r5, #640]
	ldr	r1, [r4, #2264]
	mov	r3, r2
	ldr	r0, [r4, #2248]
	bfi	r2, r1, #8, #6
	ldr	r1, [r4, #2568]
	bfi	r2, r0, #16, #4
	bfi	r2, r1, #0, #6
	str	r2, [r5, #644]
	ldr	r1, [r4, #2260]
	mov	r2, r3
	ldr	r0, [r4, #2240]
	bfi	r3, r1, #8, #6
	ldr	r1, [r4, #2576]
	bfi	r3, r0, #16, #4
	bfi	r3, r1, #0, #6
	str	r3, [r5, #648]
	ldr	r1, [r4, #784]
	mov	r3, r2
	ldr	r0, [r4, #764]
	bfi	r2, r1, #8, #6
	ldr	r1, [r4, #2564]
	bfi	r2, r0, #16, #4
	bfi	r2, r1, #0, #6
	str	r2, [r5, #652]
	ldr	r1, [r4, #2256]
	mov	r2, r3
	ldr	r0, [r4, #2272]
	bfi	r3, r1, #16, #4
	ldr	r1, [r4, #2572]
	bfi	r3, r0, #8, #6
	bfi	r3, r1, #0, #6
	str	r3, [r5, #656]
	ldr	r0, [r4, #2284]
	mov	r3, r2
	ldr	r1, [r4, #2288]
	bfi	r2, r0, #16, #4
	ldr	r0, [r4, #2292]
	bfi	r2, r1, #20, #4
	ldr	r1, [r4, #2584]
	bfi	r2, r0, #8, #6
	bfi	r2, r1, #0, #6
	str	r2, [r5, #660]
	ldr	r0, [r4, #800]
	mov	r2, r3
	ldr	r1, [r4, #796]
	bfi	r3, r0, #24, #8
	ldr	r0, [r4, #792]
	bfi	r3, r1, #16, #8
	ldr	r1, [r4, #788]
	bfi	r3, r0, #8, #8
	bfi	r3, r1, #0, #8
	str	r3, [r5, #664]
	ldr	r0, [r4, #816]
	mov	r3, r2
	ldr	r1, [r4, #812]
	bfi	r2, r0, #24, #8
	ldr	r0, [r4, #808]
	bfi	r2, r1, #16, #8
	ldr	r1, [r4, #804]
	bfi	r2, r0, #8, #8
	bfi	r2, r1, #0, #8
	str	r2, [r5, #668]
	ldr	r0, [r4, #832]
	mov	r2, r3
	ldr	r1, [r4, #828]
	bfi	r3, r0, #24, #8
	ldr	r0, [r4, #824]
	bfi	r3, r1, #16, #8
	ldr	r1, [r4, #820]
	bfi	r3, r0, #8, #8
	bfi	r3, r1, #0, #8
	str	r3, [r5, #672]
	ldr	r0, [r4, #848]
	mov	r3, r2
	ldr	r1, [r4, #844]
	bfi	r2, r0, #24, #8
	ldr	r0, [r4, #840]
	bfi	r2, r1, #16, #8
	ldr	r1, [r4, #836]
	bfi	r2, r0, #8, #8
	bfi	r2, r1, #0, #8
	str	r2, [r5, #676]
	ldr	r0, [r4, #2164]
	mov	r2, r3
	ldr	r1, [r4, #2168]
	bfi	r3, r0, #0, #2
	ldr	r0, [r4, #2172]
	bfi	r3, r1, #2, #2
	ldr	r1, [r4, #2176]
	bfi	r3, r0, #4, #2
	ldr	r0, [r4, #2180]
	bfi	r3, r1, #6, #2
	ldr	r1, [r4, #2184]
	bfi	r3, r0, #8, #2
	ldr	r0, [r4, #2188]
	bfi	r3, r1, #10, #2
	ldr	r1, [r4, #2192]
	bfi	r3, r0, #12, #2
	ldr	r0, [r4, #2196]
	bfi	r3, r1, #14, #2
	ldr	r1, [r4, #2200]
	bfi	r3, r0, #16, #2
	ldr	r0, [r4, #2204]
	bfi	r3, r1, #18, #2
	ldr	r1, [r4, #2208]
	bfi	r3, r0, #20, #2
	ldr	r0, [r4, #2212]
	bfi	r3, r1, #22, #2
	ldr	r1, [r4, #2216]
	bfi	r3, r0, #24, #2
	ldr	r0, [r4, #2220]
	bfi	r3, r1, #26, #2
	ldr	r1, [r4, #2224]
	bfi	r3, r0, #28, #2
	bfi	r3, r1, #30, #2
	str	r3, [r5, #680]
	ldr	r1, [r4, #2228]
	mov	r3, r2
	bfi	r2, r1, #0, #5
	str	r2, [r5, #684]
	ldr	r1, [r4, #2296]
	ldr	r2, [r4, #2300]
	bfi	r3, r1, #0, #4
	bfi	r3, r2, #4, #4
	str	r3, [r5, #688]
	ldr	r3, [r7, #4]
	cmp	r3, #2
	beq	.L139
	ldr	r3, [fp, #-60]
	add	r2, r5, #688
	add	r0, r4, #1168
.L82:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	bfi	r6, r1, #0, #20
	str	r6, [r2, #4]!
	bne	.L82
.L81:
	ldr	r1, [r4, #2512]
	mov	r3, #0
	ldr	r2, [r4, #2516]
	bfi	r3, r1, #8, #2
	ldr	r1, [r4, #2324]
	bfi	r3, r2, #12, #1
	mov	r2, #0
	bfi	r3, r1, #0, #5
	str	r3, [r5, #1012]
	ldr	r1, [r4, #2320]
	mov	r3, r2
	ldr	r0, [r4, #2500]
	bfi	r2, r1, #16, #4
	ldr	r1, [r4, #2312]
	bfi	r2, r0, #12, #4
	ldr	r0, [r4, #2316]
	bfi	r2, r1, #9, #2
	ldr	r1, [r4, #2308]
	bfi	r2, r0, #8, #1
	mov	r0, r3
	bfi	r2, r1, #0, #6
	str	r2, [r5, #1016]
	ldr	r1, [r4, #2480]
	mov	r2, r3
	str	r1, [r5, #1020]
	mov	r1, r3
	ldr	ip, [r4, #2484]
	str	ip, [r5, #1024]
	ldr	ip, [r4, #2488]
	bfi	r3, ip, #0, #16
	ldr	ip, [r4, #2508]
	bfc	r3, #20, #1
	bfi	r3, ip, #21, #1
	ldr	ip, [r4, #2496]
	bfi	r3, ip, #18, #2
	ldr	ip, [r4, #2492]
	bfi	r3, ip, #16, #2
	str	r3, [r5, #1028]
	ldr	r3, [r8, #196]
	bfi	r2, r3, #4, #2
	ldr	r3, [r4, #3640]
	bfi	r2, r3, #1, #1
	ldr	r3, [r8, #216]
	bfi	r2, r3, #2, #1
	str	r2, [r5, #1040]
	ldr	r3, [r4, #3992]
	mov	r2, r0
	bfi	r0, r3, #16, #16
	ldr	r3, [r4, #3996]
	bfi	r0, r3, #0, #16
	str	r0, [r5, #1044]
	ldr	r0, [r8, #220]
	mov	r3, r1
	bfi	r1, r0, #6, #6
	ldr	r0, [r8, #224]
	bfi	r1, r0, #0, #6
	str	r1, [r5, #1048]
	ldr	r0, [r4, #3976]
	ldr	r1, [r4, #3980]
	bfi	r2, r0, #31, #1
	bfi	r2, r1, #0, #17
	str	r2, [r5, #1052]
	ldr	r1, [r4, #3984]
	ldr	r2, [r4, #3988]
	bfi	r3, r1, #16, #11
	bfi	r3, r2, #0, #10
	str	r3, [r5, #1056]
	ldr	r3, [r7, #540]
	cmp	r3, #0
	beq	.L80
	ldr	r3, [r7, #512]
	cmp	r3, #0
	moveq	r3, #15
	beq	.L83
.L80:
	ldr	r1, [r4, #4088]
	mov	r3, #0
	ldr	r2, [r4, #4092]
	bfi	r3, r1, #3, #1
	ldr	r1, [r8]
	bfi	r3, r2, #2, #1
	ldr	r2, [r4, #4084]
	bfi	r3, r1, #1, #1
	bfi	r3, r2, #0, #1
.L83:
	str	r3, [r5, #1060]
	ldr	r3, [r7, #540]
	cmp	r3, #0
	beq	.L84
	ldr	r3, [r7, #512]
	cmp	r3, #0
	moveq	r3, #16
	beq	.L85
.L84:
	ldr	r2, [r8, #4]
	mov	r3, #0
	bfi	r3, r2, #4, #1
.L85:
	str	r3, [r5, #1064]
	mov	r1, #0
	ldr	r0, [r4, #3744]
	mov	r3, r1
	mov	ip, r1
	mov	r2, r1
	bfi	r1, r0, #0, #1
	str	r1, [r5, #1068]
	ldr	r1, [r4, #3752]
	mov	r0, r3
	ldr	lr, [r4, #3756]
	bfi	r3, r1, #15, #1
	ldr	r1, [r4, #3760]
	bfi	r3, lr, #14, #1
	ldr	lr, [r4, #3764]
	bfi	r3, r1, #13, #1
	ldr	r1, [r4, #3768]
	bfi	r3, lr, #12, #1
	ldr	lr, [r4, #3772]
	bfi	r3, r1, #8, #4
	ldr	r1, [r4, #3776]
	bfi	r3, lr, #4, #4
	bfi	r3, r1, #0, #4
	str	r3, [r5, #1072]
	ldr	r3, [r4, #3780]
	mvn	r1, #0
	bfi	ip, r3, #0, #4
	str	ip, [r5, #1076]
	ldr	r3, [r4, #3792]
	mov	ip, #7
	ldr	lr, [r4, #3788]
	bfi	r2, r3, #0, #8
	ldr	r3, [r4, #3784]
	bfi	r2, lr, #8, #8
	bfi	r2, r3, #16, #8
	str	r2, [r5, #1080]
	ldr	r2, [r4, #3800]
	mov	r3, r0
	str	r1, [r5, #1088]
	mov	r6, r3
	str	r1, [r5, #1092]
	bfi	r0, r2, #0, #16
	str	r1, [r5, #1100]
	mov	lr, r3
	str	r0, [r5, #1084]
	mov	r1, r3
	str	ip, [r5, #1096]
	mov	r0, r3
	str	ip, [r5, #1104]
	mov	ip, r6
	ldr	r2, [r4, #3864]
	bfi	r3, r2, #3, #1
	ldr	r2, [r4, #3860]
	bfi	r3, r2, #2, #1
	ldr	r2, [r4, #3856]
	bfi	r3, r2, #1, #1
	mov	r2, r6
	orr	r3, r3, #1
	str	r3, [r5, #1108]
	ldr	r3, [r8, #12]
	str	r3, [r5, #1112]
	ldr	r3, [r8, #16]
	str	r3, [r5, #1116]
	ldr	r3, [r8, #20]
	str	r3, [r5, #1120]
	ldr	r3, [r8, #24]
	str	r3, [r5, #1124]
	ldr	r3, [r8, #28]
	str	r3, [r5, #1128]
	ldr	r3, [r8, #32]
	str	r3, [r5, #1132]
	ldr	r3, [r4, #4080]
	bfi	r6, r3, #0, #1
	str	r6, [r5, #1136]
	ldr	r3, [r8, #248]
	bfi	r0, r3, #0, #8
	ldr	r3, [r8, #252]
	bfi	r0, r3, #8, #8
	str	r0, [r5, #1140]
	ldr	r0, [r4, #2140]
	mov	r3, r1
	bfi	r1, r0, #0, #16
	ldr	r0, [r4, #2144]
	bfi	r1, r0, #16, #16
	str	r1, [r5, #1144]
	ldr	r1, [r4, #2156]
	movw	r0, #513
	bfi	lr, r1, #16, #16
	str	lr, [r5, #1148]
	ldr	lr, [r4, #2148]
	movw	r1, #9729
	bfi	r2, lr, #0, #16
	ldr	lr, [r4, #2152]
	bfi	r2, lr, #16, #16
	str	r2, [r5, #1152]
	ldr	lr, [r4, #2160]
	mov	r2, ip
	bfi	ip, lr, #0, #3
	str	ip, [r5, #1156]
	ldr	ip, [r7, #512]
	ldr	lr, [r4, #4048]
	cmp	ip, r2
	mov	ip, r2
	bfi	r3, lr, #8, #3
	moveq	r1, r0
	bfi	r3, r1, #16, #16
	str	r3, [r5, #1172]
	mov	r3, r2
	ldr	r1, [r7, #612]
	ldr	r0, [r7, #616]
	bfi	r2, r1, #0, #5
	mov	r1, ip
	bfi	r2, r0, #16, #16
	str	r2, [r5, #1176]
	ldr	r2, [r7, #612]
	ldr	r0, [r7, #652]
	rsb	r2, r2, #16
	mov	r2, r0, asl r2
	bfi	ip, r2, #0, #16
	str	ip, [r5, #1180]
	ldr	r0, [r4, #1308]
	ldr	r2, [r4, #1312]
	bfi	r3, r0, #0, #5
	bfi	r3, r2, #16, #16
	str	r3, [r5, #1216]
	ldr	r2, [r4, #1304]
	ldr	r3, [r4, #1308]
	rsb	r3, r3, #16
	mov	r3, r2, asl r3
	bfi	r1, r3, #0, #16
	str	r1, [r5, #1220]
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #676]
	cmp	r2, #2
	bne	.L88
	ldr	r2, [r7, #616]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r7, #620]
	ldrhi	r2, [r7, #620]
	movls	r2, r1, asl r2
	str	r2, [r3, #1184]
	ldr	r2, [r7, #616]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r7, #624]
	ldrls	r1, [r7, #624]
	movls	r2, r1, asl r2
	str	r2, [r3, #1188]
	ldr	r2, [r7, #616]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r7, #628]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #1192]
	ldr	r2, [r7, #632]
	str	r2, [r3, #1196]
	ldr	r2, [r7, #636]
	str	r2, [r3, #1200]
	ldr	r2, [r7, #640]
	str	r2, [r3, #1204]
	ldr	r2, [r7, #644]
	str	r2, [r3, #1208]
	ldr	r2, [r7, #648]
	str	r2, [r3, #1212]
	ldr	r2, [r7, #4]
.L88:
	cmp	r2, #0
	bne	.L94
	ldr	r3, [r7, #612]
	sub	r0, r3, #1
	mov	r1, r3, lsr #8
	bfi	r2, r0, #16, #7
	sub	r1, r1, #1
	mov	r3, r3, lsr #16
	sub	r3, r3, #1
	bfi	r2, r1, #8, #6
	bfi	r2, r3, #0, #6
	str	r2, [r5, #1288]
	ldr	r3, [r7, #580]
	str	r3, [r5, #1256]
	ldr	r3, [r7, #584]
	str	r3, [r5, #1260]
	ldr	r3, [r7, #588]
	str	r3, [r5, #1264]
	ldr	r3, [r7, #592]
	str	r3, [r5, #1268]
	ldr	r3, [r7, #596]
	str	r3, [r5, #1272]
	ldr	r3, [r7, #600]
	str	r3, [r5, #1276]
	ldr	r3, [r7, #604]
	str	r3, [r5, #1280]
	ldr	r3, [r7, #608]
	str	r3, [r5, #1284]
.L94:
	ldr	r2, [r4, #4076]
	mov	r3, #0
	bfi	r3, r2, #1, #24
	bfc	r3, #0, #1
	str	r3, [r5, #1292]
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #676]
	cmp	r2, #2
	bne	.L95
	ldr	r2, [r4, #1312]
	cmp	r2, #31
	rsbls	r2, r2, #32
	ldrls	r1, [r4, #1272]
	ldrhi	r2, [r4, #1272]
	movls	r2, r1, asl r2
	str	r2, [r3, #1224]
	ldr	r2, [r4, #1312]
	cmp	r2, #63
	rsbls	r2, r2, #64
	ldrhi	r2, [r4, #1276]
	ldrls	r1, [r4, #1276]
	movls	r2, r1, asl r2
	str	r2, [r3, #1228]
	ldr	r2, [r4, #1312]
	cmp	r2, #64
	rsbhi	r2, r2, #96
	ldrhi	r1, [r4, #1280]
	movhi	r2, r1, asl r2
	strhi	r2, [r3, #1232]
	ldr	r2, [r4, #1284]
	str	r2, [r3, #1236]
	ldr	r2, [r4, #1288]
	str	r2, [r3, #1240]
	ldr	r2, [r4, #1292]
	str	r2, [r3, #1244]
	ldr	r2, [r4, #1296]
	str	r2, [r3, #1248]
	ldr	r2, [r4, #1300]
	str	r2, [r3, #1252]
	ldr	r2, [r7, #4]
.L95:
	cmp	r2, #0
	bne	.L101
	ldr	r3, [r4, #1236]
	sub	r0, r3, #1
	mov	r1, r3, lsr #8
	bfi	r2, r0, #16, #7
	sub	r1, r1, #1
	mov	r3, r3, lsr #16
	sub	r3, r3, #1
	bfi	r2, r1, #8, #6
	bfi	r2, r3, #0, #6
	str	r2, [r5, #1328]
	ldr	r3, [r4, #1240]
	str	r3, [r5, #1296]
	ldr	r3, [r4, #1244]
	str	r3, [r5, #1300]
	ldr	r3, [r4, #1248]
	str	r3, [r5, #1304]
	ldr	r3, [r4, #1252]
	str	r3, [r5, #1308]
	ldr	r3, [r4, #1256]
	str	r3, [r5, #1312]
	ldr	r3, [r4, #1260]
	str	r3, [r5, #1316]
	ldr	r3, [r4, #1264]
	str	r3, [r5, #1320]
	ldr	r3, [r4, #1268]
	str	r3, [r5, #1324]
.L101:
	ldr	r2, [r7, #48]
	mov	r3, #0
	bfi	r3, r2, #0, #1
	str	r3, [r5, #1332]
	ldr	r3, [r8, #360]
	str	r3, [r5, #1336]
	ldr	r3, [r7, #52]
	cmp	r3, #0
	moveq	ip, #0
	bfieq	ip, r3, #16, #1
	movne	ip, #65536
	orr	ip, ip, #256
	tst	ip, #65536
	beq	.L107
	mov	r3, r7
	add	r2, r5, #1472
	ldr	r1, [r3, #316]!
	add	r0, r7, #508
	bfi	ip, r1, #0, #8
.L106:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L106
.L107:
	add	r1, r5, #1392
	add	r2, r5, #1328
	str	ip, [r5, #1472]
	add	r1, r1, #8
	add	r2, r2, #8
	add	ip, r7, #172
	add	r0, r7, #236
	mov	r3, #16
.L105:
	ldr	lr, [ip, #4]!
	subs	r3, r3, #1
	str	lr, [r1, #4]!
	ldr	lr, [r0, #4]!
	str	lr, [r2, #4]!
	bne	.L105
	ldr	r1, [r7, #312]
	mov	ip, #9
	ldr	r2, .L143
	mov	r0, #0
	bfi	r0, ip, #24, #8
	mov	ip, #0
	str	r1, [r5, #1468]
	ldr	r1, [r8, #264]
	ldr	lr, [r8, #268]
	bfi	ip, r1, #0, #1
	add	r1, r9, #61440
	bfi	ip, lr, #3, #1
	mov	lr, #7
	bfi	r0, lr, #16, #8
	ldr	r2, [r2]
	bfi	r0, r3, #8, #8
	mov	lr, #3
	bfi	ip, lr, #16, #4
	str	ip, [r1]
	str	r3, [r1, #8]
	mov	ip, #1
	str	r3, [r1, #16]
	bfi	r0, ip, #0, #8
	str	r3, [r1, #28]
	add	r2, r2, #61440
	str	r3, [r1, #32]
	str	r3, [r1, #44]
	str	r0, [r1, #1328]
	str	r3, [r9, #4]
	ldr	r3, [r7, #556]
	str	r3, [r2, #520]
	ldr	r3, [r7, #556]
	str	r3, [r2, #524]
	ldr	r3, [r7, #564]
	str	r3, [r2, #752]
	ldr	r3, [r7, #560]
	str	r3, [r2, #756]
	ldr	r3, [r7, #564]
	str	r3, [r2, #772]
	ldr	r3, [r7, #560]
	str	r3, [r2, #776]
	str	ip, [r9, #8]
.L42:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L44:
	ldr	r3, .L143+4
	add	r2, r4, #848
	ldr	r10, [fp, #-48]
	add	r0, r3, #160
	str	r2, [fp, #-60]
.L48:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L48
	ldr	r3, .L143+8
	add	r2, r4, #1008
	str	r10, [fp, #-48]
	add	r0, r3, #160
.L49:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L49
	mov	r2, #3
	mov	r3, #2
	str	r2, [r4, #804]
	str	r3, [r4, #780]
	mov	r3, #96
	str	r2, [r4, #808]
	mov	r2, #10
	str	r3, [r4, #1200]
	mov	r3, #0
	str	r2, [r4, #820]
	mov	r2, #20
	str	r3, [r4, #788]
	str	r3, [r4, #792]
	str	r3, [r4, #796]
	str	r3, [r4, #800]
	mov	r3, #5
	str	r10, [fp, #-48]
	str	r3, [r4, #812]
	str	r3, [r4, #816]
	mov	r3, #15
	str	r2, [r4, #828]
	str	r3, [r4, #824]
	mov	r3, #255
	str	r3, [r4, #832]
	str	r3, [r4, #836]
	str	r3, [r4, #840]
	str	r3, [r4, #844]
	str	r3, [r4, #848]
	b	.L47
.L53:
	mov	r3, #0
	str	r3, [r4, #1216]
	str	r3, [r4, #1212]
	mov	r3, #7
	str	r3, [r4, #1208]
	b	.L55
.L67:
	cmp	r3, #2
	ldr	r1, [r7, #64]
	moveq	r3, #3
	bfi	r0, r1, #16, #8
	beq	.L68
	cmp	r3, #1
	moveq	r3, #6
	movne	r3, #0
	b	.L68
.L139:
	ldr	r3, [r7, #540]
	cmp	r3, #0
	beq	.L74
	ldr	r3, [r7, #512]
	cmp	r3, #0
	bne	.L74
	ldr	r1, .L143+12
	ldr	r0, [fp, #-68]
.L77:
	add	r2, r3, #592
	add	r3, r3, #1
	ldr	ip, [r1, #4]!
	cmp	r3, #40
	add	r2, r9, r2, lsl #2
	bfi	r0, ip, #0, #20
	str	r0, [r2, #4]
	bne	.L77
	ldr	r1, .L143+16
	ldr	r0, [fp, #-72]
	add	ip, r1, #160
.L78:
	ldr	lr, [r1, #4]!
	add	r2, r3, #592
	add	r3, r3, #1
	add	r2, r9, r2, lsl #2
	cmp	r1, ip
	bfi	r0, lr, #0, #20
	str	r0, [r2, #4]
	bne	.L78
	b	.L81
.L138:
	mov	r3, #19
	mov	r1, #0
	bfi	r1, r3, #16, #6
	mov	r3, #27
	bfi	r1, r3, #0, #7
	str	r1, [fp, #-64]
	b	.L64
.L74:
	ldr	r3, [fp, #-60]
	add	r2, r5, #688
	ldr	r10, [fp, #-48]
	add	r0, r4, #1168
.L76:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	bfi	r10, r1, #0, #20
	str	r10, [r2, #4]!
	bne	.L76
	b	.L81
.L144:
	.align	2
.L143:
	.word	.LANCHOR0
	.word	.LANCHOR1+316
	.word	.LANCHOR1+516
	.word	.LANCHOR1+328
	.word	.LANCHOR1+528
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_CfgReg, .-DRV_VENC_HAL_V500R001_CfgReg
	.align	2
	.global	DRV_VENC_HAL_V500R001_Init
	.type	DRV_VENC_HAL_V500R001_Init, %function
DRV_VENC_HAL_V500R001_Init:
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
	ldr	r4, .L166
	ldr	r5, .L166+4
	ldr	r3, [r4]
	cmp	r3, #0
	beq	.L146
.L149:
	ldr	r3, [r5, #20]
	movw	r0, #4460
	blx	r3
	ldr	r3, .L166+4
	cmp	r0, #0
	str	r0, [r4, #4]
	mov	r5, r0
	ldr	r4, .L166
	beq	.L165
	ldr	r3, [r3]
	movw	r2, #4460
	mov	r1, #0
	blx	r3
	ldr	r3, [r4, #4]
	cmp	r3, #0
	moveq	r0, r3
	beq	.L150
	ldr	lr, [r4]
	add	r2, r3, #2160
	add	ip, r3, #2224
	mov	r1, #1
	mov	r5, #0
	mov	r4, #1280
	mov	r0, r1
	str	r1, [r3, #40]
	str	lr, [r3]
	mov	r6, #720
	mov	lr, #3
	str	r1, [r3, #56]
	str	r1, [r3, #2000]
	str	r1, [r3, #2052]
	str	r1, [r3, #1624]
	str	r1, [r3, #1320]
	mov	r1, #10240
	str	r5, [r3, #4]
	mov	r5, #28
	str	lr, [r3, #8]
	str	lr, [r3, #44]
	str	lr, [r3, #1344]
	mov	lr, #48
	str	r4, [r3, #12]
	mov	r4, #16
	str	r1, [r3, #28]
	mov	r1, #4
	str	r5, [r3, #520]
	mov	r5, #256
	str	r4, [r3, #524]
	mov	r4, #128
	str	lr, [r3, #528]
	mov	lr, #8
	str	r1, [r3, #1324]
	str	r1, [r3, #1336]
	mov	r1, #32
	str	r5, [r3, #1328]
	mov	r5, #6
	str	r6, [r3, #16]
	str	r4, [r3, #1332]
	str	r4, [r3, #1340]
	str	lr, [r3, #1348]
	str	lr, [r3, #1356]
	str	r1, [r3, #1352]
	str	r1, [r3, #1360]
	str	r1, [r3, #1764]
	str	r5, [r3, #1768]
.L152:
	str	r0, [r2, #4]!
	cmp	r2, ip
	mov	r1, #1
	bne	.L152
	ldr	r2, .L166+8
	mov	ip, #0
	mov	r5, #4
	mov	r9, #160
	mov	r4, #48
	mov	r6, #50
	mov	r0, #8
	mov	r8, #44
	str	r0, [r3, #2228]
	mov	r7, #2592
	str	r0, [r3, #2288]
	mov	r10, #2
	mov	r0, #10
	str	r4, [r3, #2260]
	str	r4, [r3, #2268]
	add	lr, r2, r9
	str	r4, [r3, #2264]
	movw	r4, #21845
	str	r0, [r3, #2576]
	str	r0, [r3, #2568]
	str	r0, [r3, #2580]
	str	r0, [r3, #2280]
	str	r0, [r3, #2564]
	str	r10, [r3, #2232]
	mov	r10, #3
	str	r5, [r3, #2284]
	str	r10, [r3, #2236]
	mov	r10, #60
	str	r5, [r3, #2328]
	str	r8, [r3, #2276]
	mov	r8, #51
	str	r7, [r3, #2304]
	mov	r7, #70
	str	r8, [r3, #2272]
	str	r8, [r3, #2292]
	mov	r8, #5
	str	ip, [r3, #2240]
	str	ip, [r3, #2456]
	str	ip, [r3, #2248]
	str	ip, [r3, #2244]
	str	ip, [r3, #2460]
	str	ip, [r3, #2256]
	str	ip, [r3, #2572]
	str	ip, [r3, #2520]
	str	ip, [r3, #2424]
	str	ip, [r3, #2588]
	str	ip, [r3, #2296]
	str	ip, [r3, #2300]
	str	ip, [r3, #2468]
	str	ip, [r3, #2472]
	str	r5, [r3, #2332]
	str	r5, [r3, #2336]
	str	r5, [r3, #2340]
	str	r6, [r3, #2352]
	str	r9, [r3, #2376]
	str	r6, [r3, #2384]
	str	r9, [r3, #2408]
	str	r5, [r3, #2500]
	str	r5, [r3, #2320]
	str	r8, [r3, #2308]
	mov	r8, #12
	str	r1, [r3, #2428]
	str	r1, [r3, #2432]
	str	r1, [r3, #2440]
	str	r4, [r3, #2344]
	str	r4, [r3, #2348]
	mov	r4, #80
	str	r10, [r3, #2356]
	str	r10, [r3, #2388]
	str	r7, [r3, #2360]
	str	r7, [r3, #2392]
	mov	r7, #120
	str	r4, [r3, #2364]
	str	r4, [r3, #2396]
	mov	r4, #140
	str	r7, [r3, #2368]
	str	r7, [r3, #2400]
	mov	r7, #180
	str	r4, [r3, #2372]
	str	r4, [r3, #2404]
	mov	r4, #20
	str	r7, [r3, #2380]
	str	r7, [r3, #2412]
	mov	r7, #150
	str	ip, [r3, #2436]
	str	ip, [r3, #2444]
	str	ip, [r3, #2536]
	str	ip, [r3, #2540]
	str	ip, [r3, #2316]
	str	ip, [r3, #2312]
	str	ip, [r3, #2476]
	str	r6, [r3, #2604]
	mov	r6, #8
	str	r5, [r3, #2620]
	str	r6, [r3, #2616]
	str	r6, [r3, #2628]
	mov	r6, #2
	str	r5, [r3, #2632]
	str	r6, [r3, #2636]
	mov	r6, #5
	str	r5, [r3, #2640]
	str	r5, [r3, #2648]
	str	r6, [r3, #3356]
	str	r6, [r3, #3352]
	mov	r6, #6
	str	r9, [r3, #2668]
	mov	r9, #3
	str	r1, [r3, #2596]
	str	r9, [r3, #3268]
	mov	r9, #2
	str	r1, [r3, #3280]
	str	r4, [r3, #2600]
	str	r7, [r3, #2608]
	mov	r7, #30
	str	r8, [r3, #2612]
	str	r8, [r3, #2624]
	movw	r8, #511
	str	r6, [r3, #2644]
	str	r7, [r3, #2652]
	mov	r7, #15
	str	r8, [r3, #3340]
	mov	r8, #131
	str	r7, [r3, #3348]
	str	r7, [r3, #3344]
	str	r8, [r3, #2664]
	str	r8, [r3, #2676]
	mov	r8, #100
	str	ip, [r3, #2524]
	str	r8, [r3, #2672]
	str	ip, [r3, #2528]
	str	ip, [r3, #2532]
	str	ip, [r3, #2416]
	str	ip, [r3, #2420]
	str	ip, [r3, #2464]
	str	r9, [r3, #3288]
	mov	r9, #16
	str	r0, [r3, #2728]
	add	r0, r3, #848
	str	r6, [r3, #3292]
	mov	r6, #8
	str	r0, [fp, #-48]
	mov	r0, #2
	str	r6, [r3, #3296]
	str	r6, [r3, #3300]
	str	r6, [r3, #3304]
	str	r6, [r3, #3308]
	mov	r6, #24
	str	r10, [r3, #3376]
	mov	r10, #5
	str	r4, [r3, #3428]
	str	r10, [r3, #3392]
	mov	r10, #8
	str	r4, [r3, #2732]
	movw	r4, #767
	str	r10, [r3, #3412]
	str	r10, [r3, #3416]
	mov	r10, #3
	str	r1, [r3, #3476]
	str	r10, [r3, #3704]
	mov	r10, #23040
	str	r1, [r3, #3480]
	movt	r10, 610
	str	r1, [r3, #3512]
	str	r1, [r3, #3516]
	str	r1, [r3, #3520]
	str	r1, [r3, #3640]
	str	r1, [r3, #3664]
	str	r1, [r3, #3680]
	str	r1, [r3, #3712]
	str	r9, [r3, #3312]
	str	r9, [r3, #3316]
	str	r6, [r3, #3320]
	str	r6, [r3, #3324]
	mov	r6, #7
	str	r4, [r3, #2740]
	mvn	r4, #0
	str	r6, [r3, #3616]
	str	r6, [r3, #3620]
	str	r6, [r3, #3824]
	str	r4, [r3, #3820]
	str	r4, [r3, #3828]
	str	r4, [r3, #3836]
	str	r4, [r3, #3844]
	mov	r4, #5
	str	r4, [r3, #3892]
	str	r4, [r3, #3896]
	mov	r4, #500
	str	r4, [r3, #3888]
	add	r4, r3, #4096
	str	r6, [r3, #3832]
	str	r8, [r3, #3884]
	mov	r8, #255
	str	r6, [r3, #3840]
	str	r6, [r3, #3848]
	str	r7, [r3, #3900]
	str	r7, [r3, #3904]
	str	r1, [r3, #3852]
	str	r1, [r3, #3856]
	str	r1, [r3, #3860]
	str	r1, [r3, #3864]
	str	r1, [r3, #3908]
	str	r1, [r3, #3880]
	str	r1, [r3, #3876]
	str	r0, [r4, #188]
	str	r0, [r4, #184]
	str	r7, [r3, #3992]
	str	r7, [r3, #3996]
	str	r0, [r3, #4024]
	mov	r0, #3
	str	r1, [r3, #3912]
	str	r0, [r3, #4032]
	str	r0, [r3, #4036]
	str	r0, [r3, #3928]
	mov	r0, #2
	str	r1, [r3, #3956]
	str	r8, [r4, #68]
	str	r8, [r4, #60]
	str	r1, [r3, #3532]
	str	r1, [r3, #3632]
	str	r1, [r3, #3696]
	str	r1, [r3, #3700]
	str	r0, [r3, #4048]
	str	r1, [r3, #4080]
	str	r10, [r4, #356]
	mov	r10, #2304
	str	r7, [r4, #220]
	movt	r10, 61
	str	r1, [r4, #208]
	str	r1, [r4, #200]
	str	r6, [r4, #256]
	str	r7, [r4, #260]
	mov	r7, #171
	str	r1, [r4, #268]
	str	r0, [r4, #348]
	mov	r0, #3
	str	r1, [r4, #352]
	str	r7, [r4, #248]
	mov	r7, #85
	str	r10, [r4, #360]
	mov	r10, #18
	str	r7, [r4, #252]
	mov	r7, #9
	str	ip, [r4, #264]
	str	r7, [r4, #224]
	mov	r4, #64
	str	r0, [r3, #688]
	mov	r0, #51
	str	r5, [r3, #696]
	str	r9, [r3, #700]
	str	r5, [r3, #704]
	str	r9, [r3, #708]
	str	r5, [r3, #744]
	str	r9, [r3, #740]
	mov	r9, #256
	str	r5, [r3, #780]
	mov	r5, #11
	str	r6, [r3, #808]
	str	r6, [r3, #812]
	str	r6, [r3, #816]
	mov	r6, #14
	str	r1, [r3, #684]
	str	r1, [r3, #680]
	str	r1, [r3, #748]
	mov	r1, #25
	str	r4, [r3, #692]
	str	r9, [r3, #752]
	movw	r9, #378
	str	r0, [r3, #784]
	mov	r0, #2
	str	r0, [r3, #764]
	mov	r0, #3
	str	r0, [r3, #1176]
	str	r0, [r3, #1188]
	mov	r0, #8
	str	r0, [r3, #1192]
	ldr	r0, [fp, #-48]
	str	r7, [r3, #820]
	mov	r7, #128
	str	r8, [r3, #840]
	str	r8, [r3, #844]
	str	r8, [r3, #848]
	str	r4, [r3, #1200]
	str	ip, [r3, #1172]
	str	r5, [r3, #824]
	str	r6, [r3, #828]
	str	r10, [r3, #832]
	str	r1, [r3, #836]
	str	r1, [r3, #1180]
	str	r9, [r3, #1196]
	str	r7, [r3, #1184]
.L153:
	ldr	r1, [r2, #4]!
	cmp	r2, lr
	str	r1, [r0, #4]!
	bne	.L153
	ldr	r2, .L166+12
	add	r1, r3, #1008
	add	ip, r2, #160
.L154:
	ldr	r0, [r2, #4]!
	cmp	r2, ip
	str	r0, [r1, #4]!
	bne	.L154
	mov	r2, #0
	mov	r1, #7
	mov	r0, r2
	str	r2, [r3, #1216]
	str	r2, [r3, #1212]
	str	r1, [r3, #1208]
.L150:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L165:
	ldr	r0, [r4]
	cmp	r0, #0
	beq	.L163
	ldr	r3, [r3, #16]
	blx	r3
	str	r5, [r4]
.L163:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L146:
	mov	r0, #0
	mov	r1, #63232
	movt	r0, 63688
	ldr	r3, [r5, #12]
	blx	r3
	cmp	r0, #0
	str	r0, [r4]
	beq	.L163
	b	.L149
.L167:
	.align	2
.L166:
	.word	.LANCHOR0
	.word	venc_Osal_Func_Ptr_S
	.word	.LANCHOR1-4
	.word	.LANCHOR1+156
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_Init, .-DRV_VENC_HAL_V500R001_Init
	.align	2
	.global	DRV_VENC_HAL_V500R001_Deinit
	.type	DRV_VENC_HAL_V500R001_Deinit, %function
DRV_VENC_HAL_V500R001_Deinit:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L177
	ldr	r0, [r4]
	cmp	r0, #0
	beq	.L169
	ldr	r3, .L177+4
	ldr	r3, [r3, #16]
	blx	r3
	mov	r3, #0
	str	r3, [r4]
.L169:
	ldr	r0, [r4, #4]
	ldr	r4, .L177
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L177+4
	ldr	r3, [r3, #24]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L178:
	.align	2
.L177:
	.word	.LANCHOR0
	.word	venc_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	DRV_VENC_HAL_V500R001_Deinit, .-DRV_VENC_HAL_V500R001_Deinit
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
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
	.type	g_h265LambdaSsd, %object
	.size	g_h265LambdaSsd, 200
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
	.word	188260
	.word	237192
	.word	262142
	.space	28
	.type	g_h265LambdaSad, %object
	.size	g_h265LambdaSad, 200
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
	.word	19636
	.word	22040
	.word	23170
	.space	28
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
