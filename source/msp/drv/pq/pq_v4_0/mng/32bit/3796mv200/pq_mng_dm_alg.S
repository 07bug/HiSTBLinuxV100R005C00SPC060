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
	.file	"pq_mng_dm_alg.c"
	.text
	.align	2
	.global	DM_GetDetRatio
	.type	DM_GetDetRatio, %function
DM_GetDetRatio:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #160]
	cmp	r3, #0
	movgt	r0, #15
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	DM_GetDetRatio, .-DM_GetDetRatio
	.align	2
	.global	DM_GetDMParaFlag
	.type	DM_GetDMParaFlag, %function
DM_GetDMParaFlag:
	UNWIND(.fnstart)


	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrh	r3, [r1]
	cmp	r3, r0
	bhi	.L9
	ldrh	r3, [r1, #2]
	cmp	r3, r0
	bhi	.L10
	ldrh	r3, [r1, #4]
	cmp	r3, r0
	bhi	.L11
	ldrh	r3, [r1, #6]
	cmp	r3, r0
	movhi	r3, #3
	bhi	.L5
	ldrb	r0, [r2, #4]
	ldmfd	sp, {fp, sp, pc}
.L9:
	mov	r3, #0
.L5:
	ldrb	r0, [r2, r3]
	ldmfd	sp, {fp, sp, pc}
.L10:
	mov	r3, #1
	b	.L5
.L11:
	mov	r3, #2
	b	.L5
	UNWIND(.fnend)
	.size	DM_GetDMParaFlag, .-DM_GetDMParaFlag
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r2, [r0, #160]
	mov	r3, #0
	mov	r5, r0
	cmp	r2, #720
	mov	r4, r1
	add	r6, r0, #180
	str	r3, [fp, #-36]
	str	r3, [fp, #-32]
	str	r3, [fp, #-44]
	strb	r3, [fp, #-40]
	bgt	.L15
	ldrb	r1, [r0, #165]
	cmp	r1, #1
	beq	.L48
.L15:
	ldrb	r2, [r5, #164]
.L27:
	mov	r3, #44
	smulbb	r3, r2, r3
	add	r5, r6, r3
	ldrh	r3, [r6, r3]
	strh	r3, [r4, #82]
	ldrh	r3, [r5, #2]
	strh	r3, [r4, #84]
	ldrh	r3, [r5, #4]
	strh	r3, [r4, #92]
	ldrh	r3, [r5, #6]
	strh	r3, [r4, #94]
	ldrb	r3, [r5, #8]
	strb	r3, [r4, #282]
	ldrb	r3, [r5, #9]
	strb	r3, [r4, #283]
	ldrh	ip, [r5, #10]
	strh	ip, [r4, #102]
	ldrh	r1, [r5, #12]
	strh	r1, [r4, #104]
	ldrh	r0, [r5, #14]
	strh	r0, [r4, #106]
	ldrh	r2, [r5, #16]
	strh	r2, [r4, #108]
	ldrb	r3, [r5, #20]
	cmp	r3, #1
	beq	.L49
.L46:
	strb	r3, [r4, #281]
	ldrb	r3, [r5, #19]
	strb	r3, [r4, #280]
	ldrb	r3, [r5, #18]
	strb	r3, [r4, #100]
	ldr	r1, [r5, #40]
	cmp	r1, #0
	beq	.L31
	mov	r2, #62
	add	r0, r4, #114
	bl	pq_alg_memcpy
.L31:
	ldrh	r0, [r5, #22]
	movw	r1, #286
	add	r3, r4, #288
	ldr	r2, .L50
	strh	r0, [r4, r1]
	mov	r0, #0
	ldrh	r1, [r5, #24]
	ldr	r2, [r2]
	strh	r1, [r3]
	ldrb	r3, [r5, #26]
	strb	r3, [r4, #284]
	ldrb	r3, [r5, #27]
	strb	r3, [r4, #285]
	ldrb	r3, [r5, #28]
	strb	r3, [r4, #86]
	ldrh	r3, [r5, #30]
	strh	r3, [r4, #88]
	ldrh	r3, [r5, #32]
	strh	r3, [r4, #90]
	ldrh	r3, [r5, #34]
	strh	r3, [r4, #96]
	ldrh	r3, [r5, #36]
	strb	r2, [r4, #80]
	strh	r3, [r4, #98]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L48:
	cmp	r2, r3
	movgt	ip, #15
	movle	ip, r3
	cmp	r0, r3
	beq	.L17
	ldr	r0, .L50+4
	ldr	r2, [r0]
	cmp	r2, #31
	addls	r1, r2, #1
	str	r1, [r0]
	movhi	r2, r3
	add	r2, r2, #2
	add	r2, r5, r2, lsl #2
	mov	r3, r2
	str	ip, [r3, #4]!
	ldr	r1, [r5, #140]
	str	r3, [r5, #152]
	cmp	r1, #0
	ldreqh	r7, [r2, #4]
	beq	.L22
	movle	r0, #0
	ble	.L21
	mov	r2, #0
	add	lr, r5, #12
	mov	r0, r2
.L24:
	ldr	ip, [r3], #-4
	add	r2, r2, #1
	cmp	r3, lr
	add	r0, r0, ip
	addcc	r3, r5, #136
	cmp	r2, r1
	bne	.L24
.L21:
	bl	__aeabi_idiv
	uxth	r7, r0
.L22:
	mov	r2, #8
	add	r1, r5, #166
	sub	r0, fp, #36
	bl	pq_alg_memcpy
	add	r1, r5, #174
	sub	r0, fp, #44
	mov	r2, #5
	bl	pq_alg_memcpy
	ldrh	r3, [fp, #-36]
	cmp	r3, r7
	bhi	.L35
.L32:
	ldrh	r3, [fp, #-34]
	cmp	r3, r7
	bhi	.L36
	ldrh	r3, [fp, #-32]
	cmp	r3, r7
	bhi	.L37
	ldrh	r3, [fp, #-30]
	cmp	r3, r7
	subhi	r3, fp, #41
	bhi	.L25
	ldrb	r2, [fp, #-40]
	b	.L27
.L49:
	sxth	ip, ip
	sxth	r0, r0
	sxth	r1, r1
	sxth	r2, r2
	cmp	r1, r2
	cmpgt	ip, r0
	movle	r3, #0
	b	.L46
.L37:
	sub	r3, fp, #42
.L25:
	ldrb	r2, [r3]
	b	.L27
.L17:
	sub	r0, fp, #36
	mov	r2, #8
	mov	r1, #166
	movw	r7, #65535
	bl	pq_alg_memcpy
	mov	r2, #5
	mov	r1, #174
	sub	r0, fp, #44
	bl	pq_alg_memcpy
	b	.L32
.L35:
	sub	r3, fp, #44
	b	.L25
.L36:
	sub	r3, fp, #43
	b	.L25
.L51:
	.align	2
.L50:
	.word	.LANCHOR1
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	PQ_MNG_ALG_UpdateDMCfg, .-PQ_MNG_ALG_UpdateDMCfg
	.global	g_u32DmStr
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	g_u32DmStr, %object
	.size	g_u32DmStr, 4
g_u32DmStr:
	.word	8
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	i.4685, %object
	.size	i.4685, 4
i.4685:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
