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
	.file	"mpeg2.c"
	.text
	.align	2
	.type	MP2_SearchStartCode.part.2, %function
MP2_SearchStartCode.part.2:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #2
	add	ip, r0, r1
.L12:
	cmp	ip, r3
	bls	.L2
.L15:
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bls	.L14
.L8:
	add	r3, r3, #3
	cmp	ip, r3
	bhi	.L15
.L2:
	sub	r0, r1, #3
	ldmfd	sp, {fp, sp, pc}
.L14:
	cmp	r2, #0
	bne	.L5
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #1
	beq	.L12
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #2
	addne	r3, r3, #4
	b	.L12
.L5:
	cmp	r2, #1
	bne	.L12
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L8
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L8
	rsb	r3, r0, r3
	sub	r0, r3, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_SearchStartCode.part.2, .-MP2_SearchStartCode.part.2
	.align	2
	.global	MP2_ArrangeVHBMem
	.type	MP2_ArrangeVHBMem, %function
MP2_ArrangeVHBMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r5, r0, #86016
	mov	r4, r0
	ldr	r3, [r5, #2680]
	ldr	r2, [r3, #56]
	ldr	r3, [r3, #60]
	cmp	r2, #31
	bls	.L18
	sub	r0, r3, #32
	movw	r1, #8160
	cmp	r2, #8192
	cmpls	r0, r1
	bhi	.L18
	ldr	r0, [r4]
	ldr	r1, [r0, #28]
	cmp	r1, #25
	beq	.L43
	mov	r7, r2
	mov	r8, r3
	mov	r10, #5
	mov	r6, #2
	mov	r9, #3
.L27:
	ldr	r3, .L46
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4]
	str	r7, [fp, #-60]
	str	r8, [fp, #-56]
	ldr	r2, [r3, #28]
	str	r7, [fp, #-52]
	cmp	r2, #24
	str	r8, [fp, #-48]
	beq	.L32
	uxtb	r1, r6
	strb	r9, [fp, #-63]
	strb	r10, [fp, #-62]
.L38:
	ldr	r2, [r3, #692]
	ldr	r3, [r3, #696]
	mul	r0, r8, r7
	strb	r1, [fp, #-61]
	mul	ip, r3, r2
	cmp	r0, ip
	ble	.L33
	stmia	sp, {r7, r8}
	mov	r0, #0
	ldr	r1, .L46+4
	bl	dprint_vfmw
	ldr	r3, .L46+8
	ldr	r4, [r3]
	cmp	r4, #0
	mvneq	r0, #0
	beq	.L42
	mov	r3, #0
	ldr	r0, [r5, #3040]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	b	.L42
.L18:
	ldr	r1, .L46+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
.L42:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L33:
	sub	r1, fp, #64
	ldr	r0, [r5, #3040]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L34
	ldr	r1, [r4]
	sub	r3, fp, #68
	ldr	r0, [r5, #3040]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L44
	cmp	r0, #0
	moveq	r0, #1
	beq	.L42
.L36:
	ldr	r1, .L46+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L42
.L43:
	ldr	r1, [r0, #732]
	cmp	r1, #0
	beq	.L45
	ldr	r1, [r0, #692]
	ldr	ip, [r0, #696]
	cmp	r2, r1
	bhi	.L29
	cmp	r3, ip
	bhi	.L29
	ldr	r1, [r0, #720]
	mov	r7, r2
	ldr	r2, [r0, #716]
	mov	r8, r3
	cmp	r1, #0
	add	r9, r2, #2
	beq	.L40
	add	r1, r2, #1
	cmp	r1, #17
	movlt	r6, r1
	movge	r6, #17
.L31:
	ldrb	r10, [r0, #740]	@ zero_extendqisi2
	b	.L27
.L34:
	ldr	r1, .L46+20
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L42
.L45:
	ldr	r7, [r0, #692]
	ldr	r8, [r0, #696]
	cmp	r2, r7
	bhi	.L24
	cmp	r3, r8
	bhi	.L24
	ldr	r2, [r0, #720]
	ldr	r3, [r0, #716]
	cmp	r2, #0
	add	r9, r3, #2
	beq	.L40
	add	r1, r3, #1
	cmp	r1, #17
	movlt	r6, r1
	movge	r6, #17
	b	.L31
.L32:
	mov	r1, #1
	strb	r10, [fp, #-62]
	strb	r1, [fp, #-63]
	b	.L38
.L29:
	stmia	sp, {r1, ip}
	mov	r0, #0
	ldr	r1, .L46+24
	bl	dprint_vfmw
	mov	r0, #0
	b	.L42
.L40:
	mov	r6, #1
	b	.L31
.L24:
	stmia	sp, {r7, r8}
	mov	r0, #0
	ldr	r1, .L46+24
	bl	dprint_vfmw
	mov	r0, #0
	b	.L42
.L44:
	add	r0, r4, #88064
	add	r0, r0, #640
	bl	ResetVoQueue
	b	.L36
.L47:
	.align	2
.L46:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	.word	g_event_report
	.word	.LC1
	.word	.LC4
	.word	.LC5
	.word	.LC2
	UNWIND(.fnend)
	.size	MP2_ArrangeVHBMem, .-MP2_ArrangeVHBMem
	.align	2
	.global	MP2_DecodingDecide
	.type	MP2_DecodingDecide, %function
MP2_DecodingDecide:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r4, r0, #86016
	mov	r5, r0
	ldr	r3, [r4, #1340]
	ldr	r7, [r4, #2680]
	tst	r3, #8388608
	mvneq	r6, #0
	bne	.L138
.L49:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L138:
	ldrb	r2, [r7, #17]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L50
	ldr	r2, [r4, #1352]
	cmp	r2, #1
	beq	.L50
	ands	r6, r3, #255
	beq	.L52
.L141:
	ldr	r2, .L159
	ldr	r5, [r2]
	cmp	r5, #0
	beq	.L53
	mov	r3, #0
	mov	r1, #103
	mov	r2, r3
	ldr	r0, [r4, #3040]
	blx	r5
	ldr	r3, [r4, #1340]
.L53:
	ldr	r2, [r4, #1348]
	mov	r0, #22
	ldr	r1, .L159+4
	mov	r6, #0
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L52:
	ldr	r3, [r4, #1388]
	cmp	r3, #0
	beq	.L139
	ldr	r3, [r4, #1328]
	ldr	r1, [r5]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r2, [r1, #8]
	bls	.L140
.L56:
	sub	r3, r2, #1
	str	r2, [r4, #1328]
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L61
.L63:
	.word	.L62
	.word	.L64
	.word	.L134
	.word	.L66
	.word	.L67
.L50:
	ldr	r2, [r4, #3044]
	ands	r6, r3, #255
	add	r2, r2, #1
	str	r2, [r4, #3044]
	beq	.L52
	b	.L141
.L134:
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	mov	r3, #0
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	str	r3, [fp, #-52]
.L68:
	ldr	r2, [r4, #1348]
	add	r0, r5, #87040
	ldr	r1, [r4, #1288]
	add	r0, r0, #560
	ldr	r8, [r4, #1392]
	str	r2, [fp, #-48]
	add	r8, r8, r1
	bl	BsPos
	mov	r3, r10
	str	r9, [sp]
	ldr	r2, [fp, #-48]
	ldr	r1, .L159+8
	add	r8, r8, r0, lsr #3
	mov	r0, #18
	str	r8, [sp, #4]
	bl	dprint_vfmw
	ldr	r3, [r4, #1340]
	bic	r3, r3, #14155776
	str	r3, [r4, #1340]
	ldr	r3, [r5]
	ldr	r0, [r3, #628]
	ldr	r3, [r4, #1380]
	cmp	r0, #1
	beq	.L142
	cmp	r3, #0
	bne	.L85
	ldrb	r2, [r7, #30]	@ zero_extendqisi2
	sub	r1, r2, #2
	cmp	r1, #1
	bls	.L143
.L86:
	cmp	r2, #3
	beq	.L144
.L83:
	ldr	r1, [r4, #1416]
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #1420]
	mov	r8, r0
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	clz	r3, r8
	mov	r3, r3, lsr #5
	clz	r1, r0
	mov	r1, r1, lsr #5
	orrs	r2, r1, r3
	bne	.L145
	ldrb	r2, [r7, #30]	@ zero_extendqisi2
	cmp	r2, #2
	beq	.L146
	cmp	r2, #3
	beq	.L147
.L91:
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	movne	r6, #1
	bne	.L49
	ldrb	r3, [r7, #17]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L97
	ldr	r3, [r4, #1352]
	cmp	r3, #0
	bne	.L49
.L97:
	ldrb	r3, [r7, #35]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L148
	ldrb	r3, [r7, #26]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L149
	ldr	r3, [r4, #1504]
	add	r3, r3, #1
	str	r3, [r4, #1504]
	mov	r3, r3, asl #1
	str	r3, [r4, #1500]
.L99:
	ldr	r2, [r4, #1496]
	ldr	r3, [r4, #1348]
	add	r2, r2, #1
	str	r2, [r4, #1496]
	add	r3, r3, #1
	str	r3, [r4, #1348]
	b	.L49
.L64:
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	sub	r3, r10, #2
	cmp	r3, #1
	bls	.L150
.L136:
	mov	r3, #1
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	str	r3, [fp, #-52]
	b	.L68
.L67:
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	cmp	r10, #1
	beq	.L151
	cmp	r10, #2
	beq	.L152
.L73:
	ldrb	r3, [r7, #17]	@ zero_extendqisi2
	cmp	r3, #3
	ldrne	r3, [r4, #1352]
	clzne	r3, r3
	movne	r3, r3, lsr #5
	strne	r3, [r4, #1352]
	ldr	r3, [r1, #956]
	cmp	r3, #1
	bne	.L134
	mov	r3, #2
	mov	r2, #0
	str	r3, [r1, #956]
	str	r2, [fp, #-52]
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	b	.L68
.L62:
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	cmp	r10, #3
	bne	.L136
	ldrb	r10, [r7, #17]	@ zero_extendqisi2
	cmp	r10, #3
	beq	.L153
.L78:
	ldr	r3, [r4, #1352]
	mov	r2, #0
	str	r2, [fp, #-52]
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #1352]
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	b	.L68
.L66:
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #1
	mov	r10, r3
	beq	.L154
	cmp	r3, #3
	beq	.L155
.L77:
	cmp	r3, #2
	beq	.L81
	mov	r10, r3
	b	.L136
.L85:
	cmp	r3, #1
	bhi	.L83
	ldrb	r2, [r7, #30]	@ zero_extendqisi2
	b	.L86
.L142:
	cmp	r3, #0
	bne	.L83
	ldrb	r2, [r7, #30]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L156
	cmp	r2, #2
	bne	.L83
	ldr	r1, .L159+12
	bl	dprint_vfmw
	b	.L83
.L140:
	cmp	r2, #4
	cmpne	r2, #1
	bhi	.L56
	ldr	r1, .L159+16
	mov	r0, #2
	bl	dprint_vfmw
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L131
	ldr	r3, [r4, #1340]
	ldr	r1, [r4, #1420]
	orr	r3, r3, #128
	ldr	r0, [r4, #3040]
	str	r3, [r4, #1340]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L59
	add	r9, r8, #560
	ldr	r1, [r8, #544]
	ldr	r0, [r4, #3040]
	add	r10, r8, #576
	bl	FreeUsdByDec
	ldr	r1, [r9, #-8]
	ldr	r0, [r4, #3040]
	add	r3, r8, #544
	str	r3, [fp, #-48]
	bl	FreeUsdByDec
	ldr	r1, [r8, #560]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	ldr	r1, [r10, #-8]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-48]
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r3]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r10, #-8]
	ldr	r1, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1416]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	str	r6, [r4, #1416]
	str	r6, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L157
.L59:
	mov	r3, #0
	str	r3, [r4, #1380]
.L131:
	ldr	r1, [r5]
	ldr	r2, [r1, #8]
	b	.L56
.L139:
	ldr	r2, [r4, #1348]
	mov	r0, #1
	ldr	r1, .L159+20
	bl	dprint_vfmw
	b	.L49
.L146:
	cmp	r3, #0
	bne	.L89
	ldr	r3, [r5]
	ldr	r2, [r8, #152]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L91
	ldr	r1, .L159+24
	mov	r0, #1
	bl	dprint_vfmw
	b	.L49
.L145:
	movw	r3, #869
	ldr	r2, .L159+28
	ldr	r1, .L159+32
	mov	r0, #1
	bl	dprint_vfmw
	b	.L49
.L61:
	mov	r3, #1
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	str	r3, [fp, #-52]
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	b	.L68
.L147:
	cmp	r3, #0
	ldr	r3, [r5]
	ldr	r2, [r8, #152]
	ldr	r3, [r3]
	bne	.L93
	cmp	r2, r3
	bhi	.L93
	cmp	r1, #0
	ldr	r2, [r0, #152]
	bne	.L96
	cmp	r3, r2
	bcs	.L91
.L96:
	ldr	r1, .L159+36
	mov	r0, #1
	bl	dprint_vfmw
	b	.L49
.L148:
	ldrb	r2, [r7, #24]	@ zero_extendqisi2
	ldrb	r3, [r7, #18]	@ zero_extendqisi2
	ldr	r1, [r4, #1504]
	add	r3, r2, r3
	add	r3, r3, #1
	add	r3, r3, r1
	str	r3, [r4, #1504]
	mov	r3, r3, asl #1
	str	r3, [r4, #1500]
	b	.L99
.L93:
	ldr	r1, .L159+40
	mov	r0, #1
	bl	dprint_vfmw
	b	.L49
.L149:
	ldr	r2, [r4, #1504]
	ldr	r3, [r4, #1500]
	add	r2, r2, #1
	str	r2, [r4, #1504]
	ldrb	r2, [r7, #24]	@ zero_extendqisi2
	add	r2, r2, #2
	add	r3, r3, r2
	str	r3, [r4, #1500]
	b	.L99
.L143:
	ldr	r1, .L159+44
	mov	r0, #1
	str	r3, [fp, #-52]
	bl	dprint_vfmw
	b	.L83
.L155:
	ldr	r3, [r4, #3052]
	cmp	r3, #0
	bne	.L136
.L80:
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	cmp	r9, #3
	bne	.L78
	mov	r3, #0
	mov	r10, r9
	str	r3, [fp, #-52]
	b	.L68
.L154:
	mov	r3, #0
	str	r3, [r4, #3052]
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L77
	b	.L80
.L151:
	ldr	r3, [r1, #956]
	cmp	r3, #0
	bne	.L73
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	str	r10, [fp, #-52]
	b	.L68
.L150:
	cmp	r10, #2
	beq	.L158
.L71:
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	cmp	r9, #3
	bne	.L78
	mov	r3, #0
	str	r3, [fp, #-52]
	b	.L68
.L81:
	mov	r9, #1
	str	r9, [r4, #3052]
	str	r9, [fp, #-52]
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	b	.L68
.L152:
	add	r3, r5, #45056
	ldrb	r2, [r3, #257]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L73
	ldrb	r9, [r3, #256]	@ zero_extendqisi2
	cmp	r9, #1
	bne	.L73
.L135:
	str	r9, [fp, #-52]
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	b	.L68
.L144:
	ldr	r1, .L159+48
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [fp, #-52]
	b	.L83
.L89:
	movw	r3, #879
	ldr	r2, .L159+28
	ldr	r1, .L159+52
	mov	r0, #1
	bl	dprint_vfmw
	b	.L49
.L156:
	ldr	r1, .L159+56
	str	r3, [fp, #-52]
	bl	dprint_vfmw
	b	.L83
.L153:
	mov	r3, #0
	mov	r9, r10
	str	r3, [fp, #-52]
	b	.L68
.L158:
	add	r3, r5, #45056
	ldrb	r2, [r3, #257]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L71
	ldrb	r9, [r3, #256]	@ zero_extendqisi2
	cmp	r9, #1
	bne	.L71
	b	.L135
.L157:
	ldr	r0, [r4, #3040]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #1416]
	str	r0, [r4, #1420]
	b	.L59
.L160:
	.align	2
.L159:
	.word	g_event_report
	.word	.LC6
	.word	.LC9
	.word	.LC11
	.word	.LC8
	.word	.LC7
	.word	.LC16
	.word	.LANCHOR0
	.word	.LC14
	.word	.LC18
	.word	.LC17
	.word	.LC12
	.word	.LC13
	.word	.LC15
	.word	.LC10
	UNWIND(.fnend)
	.size	MP2_DecodingDecide, .-MP2_DecodingDecide
	.align	2
	.global	MP2_EstimatePicQp
	.type	MP2_EstimatePicQp, %function
MP2_EstimatePicQp:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r2, #128
	mov	r4, r0
	ldr	r1, .L167
	sub	r0, fp, #148
	bl	memcpy
	add	r3, r4, #86016
	ldr	r0, [r4, #284]
	ldr	r2, [r3, #1376]
	cmp	r2, #1
	beq	.L162
	ldr	r3, [r3, #2680]
	ldrb	r3, [r3, #21]	@ zero_extendqisi2
	cmp	r3, #0
	subne	r3, fp, #20
	moveq	r0, r0, asl #1
	addne	r0, r3, r0, lsl #2
	ldrne	r0, [r0, #-128]
.L162:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L168:
	.align	2
.L167:
	.word	.LANCHOR0+20
	UNWIND(.fnend)
	.size	MP2_EstimatePicQp, .-MP2_EstimatePicQp
	.align	2
	.global	MP2_GetSequenceInfo
	.type	MP2_GetSequenceInfo, %function
MP2_GetSequenceInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #52)
	sub	sp, sp, #52
	add	r4, r0, #86016
	mov	r3, #0
	mov	r6, r0
	ldr	r2, [r4, #1376]
	str	r3, [fp, #-64]
	cmp	r2, #1
	ldr	r5, [r4, #2680]
	ldr	r7, [r4, #2684]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	beq	.L171
	cmp	r2, #2
	bne	.L237
	ldr	r3, [r4, #1340]
	and	r3, r3, #1769472
	cmp	r3, #589824
	beq	.L174
.L173:
	ldr	r1, .L247
	mov	r0, #17
	bl	dprint_vfmw
	ldr	r3, [r4, #1376]
	cmp	r3, #1
	beq	.L238
.L176:
	ldr	r3, [r5, #56]
	add	r3, r3, #15
	mov	r3, r3, lsr #4
	str	r3, [r5, #64]
	ldr	r2, [r4, #1376]
	cmp	r2, #2
	beq	.L239
.L177:
	ldr	r1, [r5, #60]
	add	r2, r1, #15
	mov	r2, r2, lsr #4
.L178:
	mov	r0, #0
	str	r2, [r5, #68]
	str	r0, [r5, #72]
	ldr	r0, [r4, #1376]
	cmp	r0, #2
	beq	.L240
.L179:
	ldr	r1, [r4, #1388]
	cmp	r1, #0
	beq	.L180
	ldr	r0, [r7, #64]
	cmp	r3, r0
	beq	.L241
.L180:
	ldr	r1, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L183
	ldr	r1, [r8, #544]
	add	r9, r8, #560
	ldr	r0, [r4, #3040]
	add	r10, r8, #576
	bl	FreeUsdByDec
	ldr	r1, [r8, #552]
	ldr	r0, [r4, #3040]
	add	r3, r8, #544
	str	r3, [fp, #-72]
	bl	FreeUsdByDec
	ldr	r1, [r8, #560]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	ldr	r1, [r8, #568]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-72]
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r3]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r10, #-8]
	ldr	r1, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1416]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #3040]
	str	r3, [r4, #1416]
	str	r3, [r4, #1420]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L242
.L183:
	add	r1, r6, #88064
	mov	r3, #0
	add	r1, r1, #640
	str	r3, [r4, #1380]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r6]
	ldr	r2, [r3, #732]
	cmp	r2, #0
	bne	.L185
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L243
.L185:
	ldr	r3, [r4, #1388]
	cmp	r3, #0
	beq	.L187
	ldr	r3, [r7, #64]
	cmp	r3, #0
	beq	.L187
	ldr	r3, [r7, #68]
	cmp	r3, #0
	bne	.L244
.L187:
	ldr	r0, [r4, #3040]
	bl	FSP_GetFspType
	cmp	r0, #0
	ldrne	r8, .L247+4
	bne	.L188
	sub	r3, fp, #56
	sub	r2, fp, #60
	sub	r1, fp, #64
	ldr	r0, [r4, #3040]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r6]
	ldr	r2, [r3, #732]
	cmp	r2, #1
	beq	.L245
.L234:
	ldr	r8, .L247+4
.L190:
	mov	r3, #0
	strb	r3, [r4, #3057]
.L188:
	mov	r3, #0
	mov	r0, r6
	mov	r1, r3
	str	r3, [r4, #1388]
	str	r3, [r4, #1404]
	bl	MP2_ArrangeVHBMem
	ldr	r1, .L247+8
	str	r0, [r4, #1388]
	mov	r0, #1
	ldr	r3, [r5, #68]
	ldr	r2, [r5, #64]
	mov	r3, r3, asl #4
	mov	r2, r2, asl #4
	bl	dprint_vfmw
.L186:
	ldr	r6, [r8]
	cmp	r6, #0
	beq	.L235
	ldr	r1, [r7, #64]
	mov	r3, #8
	ldr	r0, [r5, #68]
	sub	r2, fp, #52
	ldr	lr, [r7, #68]
	ldr	ip, [r5, #64]
	strh	r1, [fp, #-52]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-46]	@ movhi
	strh	lr, [fp, #-50]	@ movhi
	strh	ip, [fp, #-48]	@ movhi
	ldr	r0, [r4, #3040]
	blx	r6
.L235:
	ldr	r1, [r4, #1388]
.L181:
	str	r1, [r4, #1336]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L237:
	ldr	r3, [r4, #1340]
	tst	r3, #3538944
	beq	.L174
	tst	r3, #131072
	mov	r2, #2
	orreq	r3, r3, r2
	streq	r3, [r4, #1340]
	tst	r3, #1048576
	str	r2, [r4, #1376]
	orreq	r3, r3, #16
	streq	r3, [r4, #1340]
	moveq	r2, #2
	movne	r2, #2
	b	.L173
.L174:
	mov	r2, #1
	str	r2, [r4, #1376]
	b	.L173
.L171:
	ldr	r3, [r4, #1340]
	mov	r1, #18
	bfi	r1, r1, #16, #16
	and	r3, r3, r1
	cmp	r3, #1179648
	moveq	r2, #2
	streq	r2, [r4, #1376]
	b	.L173
.L240:
	ldrb	r0, [r5, #35]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L179
	add	r0, r1, #31
	add	r1, r1, #15
	mov	r0, r0, lsr #5
	mov	r1, r1, lsr #4
	rsb	r1, r1, r0, lsl #1
	str	r1, [r5, #72]
	b	.L179
.L239:
	ldrb	r2, [r5, #35]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L177
	ldr	r1, [r5, #60]
	add	r2, r1, #31
	mov	r2, r2, lsr #5
	mov	r2, r2, asl #1
	b	.L178
.L238:
	mov	r2, #0
	mov	r0, #3
	mov	r1, #5
	strb	r3, [r5, #35]
	strb	r3, [r5, #26]
	strb	r3, [r5, #19]
	strb	r3, [r5, #36]
	strb	r0, [r5, #17]
	str	r1, [r5, #152]
	strb	r2, [r5, #20]
	strb	r2, [r5, #21]
	strb	r2, [r5, #22]
	strb	r2, [r5, #23]
	strb	r2, [r5, #16]
	b	.L176
.L244:
	mov	r3, #0
	ldr	r1, .L247+12
	str	r3, [r4, #1388]
	mov	r0, #1
	bl	dprint_vfmw
	b	.L187
.L241:
	ldr	r3, [r7, #68]
	cmp	r2, r3
	bne	.L180
	b	.L181
.L242:
	ldr	r0, [r4, #3040]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #1416]
	str	r0, [r4, #1420]
	b	.L183
.L243:
	ldr	r9, [r4, #1388]
	cmp	r9, #0
	beq	.L227
	ldr	r8, .L247+4
	b	.L186
.L245:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	ble	.L246
.L191:
	mov	r3, #1
	strb	r3, [r4, #3057]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L246:
	ldr	r3, [fp, #-60]
	cmp	r3, #32
	bgt	.L191
	ldr	r3, [r6, #4]
	cmp	r3, #0
	bne	.L191
	ldr	r3, [r4, #3044]
	cmp	r3, #0
	beq	.L234
	ldr	r1, [r5, #64]
	cmp	r1, #0
	beq	.L234
	ldr	lr, [r5, #68]
	ldr	r0, [r4, #3064]
	cmp	lr, r0
	beq	.L234
	ldr	ip, [r4, #3060]
	cmp	r1, ip
	beq	.L234
	stmib	sp, {r0, r1, lr}
	mov	r0, r2
	str	ip, [sp]
	ldr	r1, .L247+16
	ldr	r8, .L247+4
	bl	dprint_vfmw
	ldr	r3, [r5, #68]
	ldr	r9, [r8]
	str	r3, [r4, #3064]
	ldr	r3, [r5, #64]
	cmp	r9, #0
	str	r3, [r4, #3060]
	beq	.L190
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #3040]
	blx	r9
	b	.L190
.L227:
	mov	r0, r6
	mov	r1, r9
	bl	MP2_ArrangeVHBMem
	ldr	r8, .L247+4
	str	r9, [r4, #1404]
	str	r0, [r4, #1388]
	b	.L186
.L248:
	.align	2
.L247:
	.word	.LC19
	.word	g_event_report
	.word	.LC22
	.word	.LC20
	.word	.LC21
	UNWIND(.fnend)
	.size	MP2_GetSequenceInfo, .-MP2_GetSequenceInfo
	.global	__aeabi_idiv
	.align	2
	.global	MP2_CalcRealEncFrameRate
	.type	MP2_CalcRealEncFrameRate, %function
MP2_CalcRealEncFrameRate:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #86016
	ldr	r3, [r4, #2680]
	ldr	r5, [r4, #1480]
	ldr	lr, [r4, #1492]
	ldrb	r2, [r3, #30]	@ zero_extendqisi2
	ldr	ip, [r3, #80]
	cmp	r2, #1
	ldr	r1, [r4, #1488]
	ldr	r2, [r4, #1476]
	ldr	r6, [r4, #1472]
	ldr	r0, [r4, #1484]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	cmp	ip, #0
	add	r0, r6, r0
	add	r1, r2, r1
	movgt	r2, #1
	movle	r2, #0
	cmp	r0, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r1, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r2, #0
	streq	r2, [r4, #1508]
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r3, #35]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r0, r0, asl #1
	addeq	r1, r5, lr
	mul	r0, ip, r0
	bl	__aeabi_idiv
	movw	r2, #26215
	movt	r2, 26214
	mov	r3, r0, asr #31
	smull	r0, r1, r0, r2
	rsb	r3, r3, r1, asr #2
	str	r3, [r4, #1508]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_CalcRealEncFrameRate, .-MP2_CalcRealEncFrameRate
	.align	2
	.global	MP2_CalcDar
	.type	MP2_CalcDar, %function
MP2_CalcDar:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r0, #86016
	ldr	r3, [r0, #2680]
	ldr	r3, [r3, #92]
	sub	r3, r3, #1
	cmp	r3, #2
	ldrls	r2, .L257
	addls	r3, r2, r3, lsl #2
	ldrls	r0, [r3, #148]
	movhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L258:
	.align	2
.L257:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MP2_CalcDar, .-MP2_CalcDar
	.align	2
	.global	MP2_SetImgFormat
	.type	MP2_SetImgFormat, %function
MP2_SetImgFormat:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r6, r0, #86016
	mov	r7, r0
	ldr	r1, [r6, #1424]
	ldr	r0, [r6, #3040]
	ldr	r5, [r6, #2680]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L259
	ldrb	r3, [r5, #30]	@ zero_extendqisi2
	ldrb	r2, [r5, #35]	@ zero_extendqisi2
	cmp	r3, #4
	ldrb	lr, [r4, #65]	@ zero_extendqisi2
	subne	r3, r3, #1
	ldr	r9, [r5, #136]
	andne	r3, r3, #3
	moveq	r3, #0
	moveq	r10, r3
	ubfx	lr, lr, #2, #2
	uxtbne	r10, r3
	cmp	r2, #0
	ldrb	r2, [r5, #17]	@ zero_extendqisi2
	moveq	r0, #1
	movne	r0, #0
	orr	lr, r2, lr
	movne	r2, #1
	strne	r2, [fp, #-48]
	beq	.L277
.L262:
	ldr	r2, [r6, #2680]
	ldrb	ip, [r4, #64]	@ zero_extendqisi2
	ldr	r2, [r2, #92]
	bfi	ip, r10, #0, #2
	and	ip, ip, #227
	sub	r2, r2, #1
	bfi	ip, r9, #5, #3
	cmp	r2, #2
	strb	ip, [r4, #64]
	ldrls	r1, .L280
	movhi	r1, #0
	movhi	r8, r1
	addls	r2, r1, r2, lsl #2
	ldrls	r1, [r2, #148]
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	andls	r8, r1, #7
	bfi	r2, r0, #0, #2
	mov	r0, r4
	bfi	r2, lr, #2, #2
	ldr	lr, [fp, #-48]
	bfi	r2, lr, #4, #2
	strb	r2, [r4, #65]
	ldr	r2, [r4, #64]
	bfi	r2, r8, #14, #3
	str	r2, [r4, #64]
	ldrb	ip, [r5, #4]	@ zero_extendqisi2
	mov	r2, r2, lsr #16
	bfi	r2, ip, #1, #1
	strb	r2, [r4, #66]
	ldr	r2, [r5, #8]
	str	r3, [r4, #56]
	str	r3, [r4, #60]
	str	r2, [r4, #120]
	bl	SetAspectRatio
	mov	r3, #3
	str	r3, [r4, #296]
	mov	r2, #1
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	strb	r2, [r4, #291]
	cmp	r3, #3
	moveq	r3, #0
	movne	r3, #4
	strb	r3, [r4, #284]
	ldr	r3, [r7, #4]
	cmp	r3, #0
	streqb	r3, [r4, #291]
	ldrneb	r3, [r3, #145]	@ zero_extendqisi2
	moveq	r2, #32
	moveq	r3, r2
	streq	r2, [r4, #300]
	mov	r2, #1
	strb	r2, [r4, #289]
	strne	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	ldr	r3, [r5, #80]
	str	r3, [r4, #108]
	ldr	r2, [r5, #56]
	str	r2, [r4, #68]
	ldr	r3, [r5, #60]
	str	r3, [r4, #72]
	ldr	r1, [r7]
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L278
.L269:
	mov	r1, r2, lsr #1
	str	r1, [r4, #84]
	mov	r1, r3, lsr #1
	str	r1, [r4, #88]
	ldr	r1, [r5, #156]
	mov	r0, r7
	str	r1, [r4, #92]
	ldr	r1, [r5, #160]
	str	r2, [r4, #76]
	str	r3, [r4, #80]
	str	r1, [r4, #96]
	ldrb	r3, [r5, #35]	@ zero_extendqisi2
	str	r3, [r4, #396]
	ldrb	r3, [r5, #26]	@ zero_extendqisi2
	str	r3, [r4, #400]
	ldr	r3, [r5, #152]
	str	r3, [r4, #408]
	bl	MP2_CalcRealEncFrameRate
	ldr	r3, [r6, #1508]
	str	r3, [r4, #404]
.L259:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L277:
	cmp	r2, #3
	beq	.L279
	ldr	r1, [r6, #1352]
	cmp	r1, #0
	bne	.L264
	sub	r2, r2, #1
	clz	r2, r2
	mov	r2, r2, lsr #5
	str	r2, [fp, #-48]
	b	.L262
.L278:
	ldr	lr, [r4, #112]
	add	ip, r3, #15
	ldr	r8, [r4, #36]
	add	r10, r4, #512
	mov	r1, ip, lsr #4
	mov	ip, lr, asl #4
	add	r0, r8, lr
	str	r0, [fp, #-48]
	mul	ip, r1, ip
	add	r9, ip, r8
	str	r9, [r4, #40]
	ldrd	r0, [r10, #-8]
	add	lr, r9, lr
	adds	r0, r0, ip
	adc	r1, r1, ip, asr #31
	strd	r0, [r10]
	ldr	r0, [fp, #-48]
	str	r9, [r4, #24]
	str	lr, [r4, #32]
	str	r0, [r4, #28]
	str	r8, [r4, #20]
	b	.L269
.L264:
	subs	r2, r2, #1
	movne	r2, #1
	str	r2, [fp, #-48]
	b	.L262
.L279:
	ldrb	r2, [r5, #18]	@ zero_extendqisi2
	and	r2, r2, #1
	str	r2, [fp, #-48]
	b	.L262
.L281:
	.align	2
.L280:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MP2_SetImgFormat, .-MP2_SetImgFormat
	.align	2
	.global	MP2_SearchStartCode
	.type	MP2_SearchStartCode, %function
MP2_SearchStartCode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #4
	ble	.L283
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP2_SearchStartCode.part.2
.L283:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_SearchStartCode, .-MP2_SearchStartCode
	.align	2
	.global	MP2_ProtocolPPSCheck
	.type	MP2_ProtocolPPSCheck, %function
MP2_ProtocolPPSCheck:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #86016
	ldr	r3, [r4, #1376]
	ldr	r1, [r4, #2680]
	cmp	r3, #1
	beq	.L286
	cmp	r3, #2
	beq	.L287
	ldr	r3, [r4, #1340]
	orr	r3, r3, #63
	str	r3, [r4, #1340]
	ldrb	r2, [r1, #30]	@ zero_extendqisi2
.L293:
	tst	r3, #24
	beq	.L295
.L311:
	cmp	r2, #3
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L296:
	orr	r3, r3, #64
	ldr	r1, [r4, #1420]
	str	r3, [r4, #1340]
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L299
	ldr	r1, [r5, #544]
	add	r6, r5, #560
	ldr	r0, [r4, #3040]
	add	r7, r5, #576
	bl	FreeUsdByDec
	ldr	r1, [r5, #552]
	ldr	r0, [r4, #3040]
	add	r8, r5, #544
	bl	FreeUsdByDec
	ldr	r1, [r5, #560]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	ldr	r1, [r5, #568]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r8]
	strd	r0, [r6, #-8]
	strd	r0, [r6]
	strd	r0, [r7, #-8]
	ldr	r1, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1416]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #3040]
	str	r3, [r4, #1416]
	str	r3, [r4, #1420]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L310
.L299:
	mov	r3, #0
	str	r3, [r4, #1380]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L287:
	ldr	r3, [r4, #1340]
	tst	r3, #1048576
	orreq	r3, r3, #16
	streq	r3, [r4, #1340]
	ldrb	r2, [r1, #30]	@ zero_extendqisi2
	sub	r0, r2, #1
	cmp	r0, #2
	bls	.L293
.L308:
	orr	r3, r3, #8
	str	r3, [r4, #1340]
	tst	r3, #24
	ldrb	r2, [r1, #30]	@ zero_extendqisi2
	bne	.L311
.L295:
	cmp	r2, #1
	biceq	r3, r3, #192
	streq	r3, [r4, #1340]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L286:
	ldrb	r2, [r1, #30]	@ zero_extendqisi2
	sub	r3, r2, #1
	cmp	r3, #3
	ldr	r3, [r4, #1340]
	orrhi	r3, r3, #8
	strhi	r3, [r4, #1340]
	ldrhib	r2, [r1, #30]	@ zero_extendqisi2
	sub	r0, r2, #2
	cmp	r0, #1
	bls	.L312
.L290:
	cmp	r2, #3
	beq	.L313
	tst	r3, #24
	bne	.L296
	b	.L295
.L310:
	ldr	r0, [r4, #3040]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #1416]
	str	r0, [r4, #1420]
	b	.L299
.L313:
	ldrb	r2, [r1, #34]	@ zero_extendqisi2
	cmp	r2, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	b	.L308
.L312:
	ldrb	r0, [r1, #32]	@ zero_extendqisi2
	cmp	r0, #0
	orreq	r3, r3, #8
	streq	r3, [r4, #1340]
	ldreqb	r2, [r1, #30]	@ zero_extendqisi2
	b	.L290
	UNWIND(.fnend)
	.size	MP2_ProtocolPPSCheck, .-MP2_ProtocolPPSCheck
	.align	2
	.global	MP2_GetImageBuffer
	.type	MP2_GetImageBuffer, %function
MP2_GetImageBuffer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #86016
	mov	r5, r0
	mov	r1, #1
	ldr	r0, [r4, #3040]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #1424]
	blt	.L326
	mov	r1, r0
	ldr	r0, [r4, #3040]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L327
	ldr	r2, [r4, #1424]
	mov	r0, #18
	ldr	r1, .L329
	bl	dprint_vfmw
	ldr	r2, [r5, #28]
	cmp	r2, #0
	beq	.L322
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L322
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L329+4
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L326:
	ldr	r1, .L329+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L317
	ldr	r1, [r6, #544]
	add	r7, r6, #560
	ldr	r0, [r4, #3040]
	add	r8, r6, #576
	bl	FreeUsdByDec
	ldr	r1, [r6, #552]
	ldr	r0, [r4, #3040]
	add	r9, r6, #544
	bl	FreeUsdByDec
	ldr	r1, [r6, #560]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	ldr	r1, [r6, #568]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r9]
	strd	r0, [r7, #-8]
	strd	r0, [r7]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1416]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #3040]
	str	r3, [r4, #1416]
	str	r3, [r4, #1420]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L328
.L317:
	add	r1, r5, #88064
	ldr	r0, [r4, #3040]
	mov	r5, #0
	add	r1, r1, #640
	str	r5, [r4, #1380]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L322:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L328:
	ldr	r0, [r4, #3040]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #1416]
	str	r0, [r4, #1420]
	b	.L317
.L327:
	movw	r2, #1841
	ldr	r1, .L329+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L330:
	.align	2
.L329:
	.word	.LC25
	.word	.LC26
	.word	.LC23
	.word	.LC24
	UNWIND(.fnend)
	.size	MP2_GetImageBuffer, .-MP2_GetImageBuffer
	.align	2
	.global	MP2_GetPictureInfo
	.type	MP2_GetPictureInfo, %function
MP2_GetPictureInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	add	r6, r0, #86016
	mov	r4, r0
	ldr	r3, [r6, #1376]
	ldr	r5, [r6, #2680]
	cmp	r3, #1
	ldr	r7, [r6, #2684]
	beq	.L382
.L332:
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L333
	ldr	r2, [r6, #1352]
	ldr	r1, [r6, #1384]
	clz	r3, r2
	mov	r3, r3, lsr #5
	str	r3, [r6, #1352]
	ldr	r2, [r5, #164]
	cmp	r2, r1
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	bne	.L383
.L380:
	add	r8, r4, #45056
.L335:
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	strb	r3, [r8, #257]
	ldr	r3, [r5, #164]
	str	r3, [r6, #1384]
	ldr	r3, [r5, #64]
	strh	r3, [r4, #158]	@ movhi
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	cmp	r3, #3
	ldr	r3, [r5, #68]
	ldreq	r2, [r5, #72]
	movne	r3, r3, lsr #1
	rsbeq	r3, r2, r3
	strh	r3, [r4, #154]	@ movhi
	ldr	r3, [r5, #68]
	strh	r3, [r4, #156]	@ movhi
	ldrb	r3, [r5, #19]	@ zero_extendqisi2
	strb	r3, [r4, #13]
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	strb	r3, [r4, #11]
	ldr	r2, [r6, #1352]
	strb	r2, [r4, #12]
	ldrb	r3, [r5, #20]	@ zero_extendqisi2
	strb	r3, [r4, #15]
	ldrb	r3, [r5, #30]	@ zero_extendqisi2
	strb	r3, [r4, #8]
	ldr	r3, [r6, #1376]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #184]
	cmp	r3, #0
	ldrneb	r3, [r5, #33]	@ zero_extendqisi2
	strneb	r3, [r4, #9]
	ldrneb	r3, [r5, #31]	@ zero_extendqisi2
	strneb	r3, [r4, #10]
	ldrb	r3, [r5, #12]	@ zero_extendqisi2
	strb	r3, [r4, #20]
	ldrb	r3, [r5, #13]	@ zero_extendqisi2
	strb	r3, [r4, #21]
	ldrb	r3, [r5, #14]	@ zero_extendqisi2
	strb	r3, [r4, #22]
	ldrb	r3, [r5, #15]	@ zero_extendqisi2
	strb	r3, [r4, #23]
	ldrb	r3, [r5, #18]	@ zero_extendqisi2
	strb	r3, [r4, #14]
	ldrb	r3, [r5, #16]	@ zero_extendqisi2
	strb	r3, [r4, #19]
	ldrb	r3, [r5, #21]	@ zero_extendqisi2
	strb	r3, [r4, #18]
	ldrb	r3, [r5, #22]	@ zero_extendqisi2
	strb	r3, [r4, #17]
	ldrb	r3, [r5, #23]	@ zero_extendqisi2
	strb	r3, [r4, #16]
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	cmp	r2, #0
	cmpne	r3, #3
	bne	.L344
	mov	r1, #0
	mov	r0, r4
	bl	MP2_GetImageBuffer
	subs	r8, r0, #0
	beq	.L384
	ldr	r1, [r6, #1424]
	ldr	r0, [r6, #3040]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L347
	ldr	r3, [r4]
	add	ip, r7, #592
	add	lr, r7, #608
	ldr	r1, .L387
	mov	r0, #29
	ldrd	r2, [r3, #64]
	strd	r2, [ip, #-8]
	ldr	r3, [r4]
	ldrd	r2, [r3, #80]
	strd	r2, [ip]
	ldr	r3, [r4]
	ldrd	r2, [r3, #96]
	strd	r2, [lr, #-8]
	mvn	r2, #0
	ldr	lr, [r4]
	mvn	r3, #0
	ldr	lr, [lr, #112]
	str	lr, [r7]
	ldr	lr, [r4]
	ldr	lr, [lr, #116]
	str	lr, [r7, #4]
	ldr	lr, [r4]
	ldr	lr, [lr, #120]
	str	lr, [r7, #8]
	ldr	lr, [r4]
	ldr	lr, [lr, #136]
	str	lr, [r7, #12]
	ldr	lr, [r5, #144]
	strb	lr, [r7, #441]
	ldr	lr, [r5, #152]
	strb	lr, [r7, #442]
	ldr	lr, [r5, #148]
	str	lr, [r7, #444]
	ldr	lr, [r4]
	strd	r2, [lr, #64]
	ldrd	r8, [ip]
	ldrd	r2, [ip, #-8]
	strd	r8, [sp]
	bl	dprint_vfmw
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	subs	r3, r3, #3
	movne	r3, #1
	str	r3, [r7, #52]
.L347:
	ldrb	r3, [r5, #30]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L344
	ldr	r3, [r6, #1380]
	ldr	r2, [r6, #1416]
	cmp	r3, #0
	ldr	r1, [r6, #1420]
	movne	r3, #2
	moveq	r3, #1
	cmp	r2, r1
	str	r3, [r6, #1380]
	ldr	r3, [r6, #1424]
	beq	.L351
	cmp	r2, r3
	beq	.L351
	ldr	r1, .L387+4
	mov	r0, #13
	bl	dprint_vfmw
	ldr	r1, [r6, #1416]
	mov	r2, #0
	ldr	r0, [r6, #3040]
	bl	FSP_SetRef
	ldr	r1, [r6, #1420]
	ldr	r3, [r6, #1424]
.L351:
	mov	r2, #1
	str	r1, [r6, #1416]
	str	r3, [r6, #1420]
	mov	r1, r3
	ldr	r0, [r6, #3040]
	bl	FSP_SetRef
	ldr	r1, [r6, #1416]
	ldr	r0, [r6, #3040]
	bl	FSP_RemovePmv
	ldr	r2, [r6, #1424]
	ldr	r1, .L387+8
	mov	r0, #13
	bl	dprint_vfmw
.L344:
	ldr	r1, [r6, #1424]
	ldr	r0, [r6, #3040]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #1416]
	mov	r5, r0
	ldr	r0, [r6, #3040]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #1420]
	mov	r7, r0
	ldr	r0, [r6, #3040]
	bl	FSP_GetLogicFs
	cmp	r5, #0
	cmpne	r7, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r9, r0
	cmp	r3, #0
	bne	.L385
	ldr	r2, [r5, #28]
	cmp	r2, #0
	beq	.L353
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L353
	ldr	r3, [r0, #28]
	mov	r0, #13
	ldr	r1, .L387+12
	cmp	r3, #0
	ldrne	lr, [r3, #8]
	ldreq	lr, [r2, #8]
	str	lr, [r4, #188]
	ldr	r3, [r7, #28]
	cmp	r3, #0
	ldreq	r3, [r5, #28]
	ldr	ip, [r3, #8]
	str	ip, [r4, #192]
	ldr	r3, [r5, #28]
	ldr	r2, [r3, #8]
	str	r2, [r4, #196]
	ldr	r6, [r5, #8]
	str	r6, [r4, #232]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #8]
	str	r3, [r4, #208]
	ldr	r8, [r9, #92]
	str	r8, [r4, #200]
	ldr	r7, [r7, #92]
	str	lr, [sp, #4]
	str	r6, [sp, #8]
	str	r7, [r4, #204]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #32]
	add	r2, r4, #87040
	add	lr, r4, #87
	add	ip, r2, #588
	add	r1, r4, #23
	ldr	r0, [r3, #24]
	add	r2, r2, #844
	mov	r3, #0
	str	r0, [r4, #216]
	ldr	r0, [r5, #32]
	ldr	r0, [r0, #60]
	str	r0, [r4, #220]
	ldr	r0, [r5, #32]
	ldr	r0, [r0, #44]
	str	r0, [r4, #224]
	ldr	r0, [r5, #32]
	ldr	r0, [r0, #48]
	str	r0, [r4, #228]
.L359:
	ldr	r0, [ip, #4]!
	add	r3, r3, #1
	cmp	r3, #64
	strb	r0, [lr, #1]!
	ldr	r0, [r2, #4]!
	strb	r0, [r1, #1]!
	bne	.L359
	mov	r0, r4
	mov	r8, #1
	bl	MP2_EstimatePicQp
	strb	r0, [r4, #153]
.L346:
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L384:
	ldr	r2, [r6, #1348]
	ldr	r1, .L387+16
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L333:
	add	r8, r4, #45056
	ldrb	r1, [r8, #257]	@ zero_extendqisi2
	cmp	r1, #3
	beq	.L338
	ldr	r3, [r6, #1352]
	cmp	r3, #0
	beq	.L386
.L338:
	mov	r3, #1
	str	r3, [r6, #1352]
	b	.L335
.L382:
	ldrb	r2, [r5, #34]	@ zero_extendqisi2
	ldrb	r3, [r5, #32]	@ zero_extendqisi2
	strb	r2, [r5, #15]
	strb	r2, [r5, #14]
	strb	r3, [r5, #13]
	strb	r3, [r5, #12]
	b	.L332
.L385:
	ldr	r1, [r6, #1424]
	mov	r8, #0
	ldr	r0, [r6, #3040]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	stmia	sp, {r7, r9}
	mov	r3, r5
	mov	r2, #1168
	ldr	r1, .L387+20
	mov	r0, r8
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L386:
	ldr	r2, [r6, #1348]
	mov	r0, #1
	str	r1, [sp]
	ldr	r1, .L387+24
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r6, #1424]
	ldr	r0, [r6, #3040]
	bl	FSP_ClearLogicFs
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #3
	ldrne	r3, [r6, #1340]
	orrne	r3, r3, #192
	strne	r3, [r6, #1340]
	b	.L338
.L353:
	ldr	r1, [r6, #1424]
	mov	r2, #1
	ldr	r0, [r6, #3040]
	mov	r8, #0
	bl	FSP_ClearLogicFs
	ldr	r1, [r5, #32]
	ldr	r3, [r6, #1424]
	mov	r0, r8
	ldr	r2, [r6, #1416]
	str	r1, [sp, #8]
	ldr	lr, [r6, #1420]
	ldr	ip, [r5, #28]
	ldr	r1, .L387+28
	str	lr, [sp]
	str	ip, [sp, #4]
	bl	dprint_vfmw
	b	.L346
.L383:
	ldr	r2, [r6, #1348]
	mov	r0, #1
	ldr	r1, .L387+32
	bl	dprint_vfmw
	mov	r3, #0
	mov	r2, #1
	str	r3, [r6, #1352]
	ldr	r1, [r6, #1424]
	ldr	r0, [r6, #3040]
	bl	FSP_ClearLogicFs
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L380
	ldr	r3, [r6, #1340]
	add	r8, r4, #45056
	orr	r3, r3, #192
	str	r3, [r6, #1340]
	b	.L335
.L388:
	.align	2
.L387:
	.word	.LC30
	.word	.LC31
	.word	.LC32
	.word	.LC35
	.word	.LC29
	.word	.LC33
	.word	.LC28
	.word	.LC34
	.word	.LC27
	UNWIND(.fnend)
	.size	MP2_GetPictureInfo, .-MP2_GetPictureInfo
	.align	2
	.global	MP2_SetVDMInf
	.type	MP2_SetVDMInf, %function
MP2_SetVDMInf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #86016
	mov	r4, r0
	add	r0, r0, #87040
	ldrb	r3, [r5, #1292]	@ zero_extendqisi2
	add	r0, r0, #560
	ldr	r2, [r5, #1296]
	cmp	r3, #1
	ldr	r3, [r5, #1608]
	beq	.L392
	ldr	ip, [r5, #1288]
	mov	r1, r3, lsr #3
	add	r3, r3, r2, lsl #3
	add	r2, r1, r2
	ldr	r6, [r5, #1300]
	and	r3, r3, #31
	bic	r2, r2, #3
	add	r1, r1, ip
	str	r1, [r5, #1288]
	bic	r6, r6, #3
	str	r3, [r4, #168]
	str	r2, [r4, #160]
	bl	BsResidBits
	str	r6, [r4, #164]
	str	r0, [r4, #176]
	ldr	r3, [r5, #1300]
	and	r3, r3, #3
	mov	r3, r3, asl #3
	str	r3, [r4, #172]
	ldr	r3, [r5, #1308]
	mov	r3, r3, asl #3
	str	r3, [r4, #180]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L392:
	ldr	r1, [r5, #1288]
	mov	ip, r3, lsr #3
	add	r3, r3, r2, lsl #3
	add	r2, ip, r2
	and	r3, r3, #31
	bic	r2, r2, #3
	add	r1, r1, ip
	str	r1, [r5, #1288]
	str	r3, [r4, #168]
	str	r2, [r4, #160]
	bl	BsResidBits
	mov	r3, #0
	str	r3, [r4, #164]
	str	r3, [r4, #172]
	str	r3, [r4, #180]
	str	r0, [r4, #176]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_SetVDMInf, .-MP2_SetVDMInf
	.align	2
	.global	MP2_DecNewPic
	.type	MP2_DecNewPic, %function
MP2_DecNewPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r4, r0
	bl	MP2_SetVDMInf
	ldr	r3, [r4]
	add	r2, r4, #45056
	add	r1, r4, #86016
	ldr	r0, [r3, #600]
	str	r0, [r2, #248]
	ldr	r0, [r3, #652]
	str	r0, [r2, #252]
	ldr	r2, [r1, #2680]
	ldrb	r0, [r2, #30]	@ zero_extendqisi2
	cmp	r0, #3
	beq	.L411
	cmp	r0, #2
	moveq	r0, #1
	streq	r0, [r1, #3052]
.L395:
	add	ip, r4, #8
	str	ip, [r4, #4]
	ldr	r0, [r3, #912]
	cmp	r0, #1
	beq	.L412
	cmp	r0, #2
	beq	.L413
.L398:
	ldr	r3, [r1, #1340]
	bic	r3, r3, #16252928
	str	r3, [r1, #1340]
	ldrb	r5, [r2, #30]	@ zero_extendqisi2
	cmp	r5, #1
	movne	r0, #1
	beq	.L414
.L396:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L414:
	ldr	r3, .L415
	ldr	r6, [r3]
	cmp	r6, #0
	moveq	r0, r5
	beq	.L396
	ldr	lr, [r4, #180]
	sub	r2, fp, #28
	ldr	ip, [r4, #176]
	mov	r3, #4
	ldr	r0, [r1, #3040]
	mov	r1, #20
	add	ip, ip, lr
	add	lr, ip, #7
	cmp	ip, #0
	movlt	ip, lr
	mov	ip, ip, asr #3
	str	ip, [r2, #-4]!
	blx	r6
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L411:
	ldr	r0, [r1, #3052]
	cmp	r0, #0
	bne	.L395
	ldr	ip, [r1, #1380]
	cmp	ip, #2
	beq	.L395
	ldrb	r3, [r2, #17]	@ zero_extendqisi2
	cmp	r3, #3
	ldrne	r3, [r1, #1352]
	clzne	r3, r3
	movne	r3, r3, lsr #5
	strne	r3, [r1, #1352]
	b	.L396
.L412:
	cmp	ip, #0
	beq	.L398
	ldrb	r3, [r2, #30]	@ zero_extendqisi2
	cmp	r3, #3
	moveq	r0, #0
	streq	r0, [r4, #4]
	bne	.L398
	b	.L396
.L413:
	ldr	r0, [r3, #916]
	cmp	ip, #0
	cmpne	r0, #0
	ble	.L398
	ldrb	r0, [r2, #30]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L398
	mov	r0, #0
	str	r0, [r4, #4]
	ldr	r2, [r3, #916]
	sub	r2, r2, #1
	str	r2, [r3, #916]
	b	.L396
.L416:
	.align	2
.L415:
	.word	g_event_report
	UNWIND(.fnend)
	.size	MP2_DecNewPic, .-MP2_DecNewPic
	.align	2
	.global	MP2_RecordVFMWState
	.type	MP2_RecordVFMWState, %function
MP2_RecordVFMWState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r0, #86016
	ldr	r1, [r0]
	ldr	r3, [r2, #2680]
	ldr	ip, [r3, #48]
	str	ip, [r1, #576]
	ldr	r1, [r3, #52]
	ldr	r3, [r0]
	str	r1, [r3, #580]
	ldr	r3, [r2, #3044]
	ldr	r2, [r2, #3048]
	ldr	r1, [r0]
	cmp	r3, r2
	rsbge	r3, r2, r3
	movlt	r3, #0
	str	r3, [r1, #584]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_RecordVFMWState, .-MP2_RecordVFMWState
	.align	2
	.global	MP2_GetUsrData
	.type	MP2_GetUsrData, %function
MP2_GetUsrData:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r8, r0, #87040
	mov	r7, r0
	add	r4, r8, #560
	mov	r0, r4
	bl	BsToNextByte
	mov	r0, r4
	bl	BsResidBits
	add	r9, r0, #7
	cmp	r0, #0
	movlt	r0, r9
	mov	r9, r0, asr #3
	cmp	r9, #0
	ble	.L440
	mov	r5, #0
	ldr	r10, .L458
	mov	r6, r5
	b	.L425
.L456:
	bl	BsGet
	add	r6, r6, #1
	cmp	r6, r9
	strb	r0, [r10, r5]
	add	r5, r5, #1
	beq	.L421
.L425:
	mov	r1, #24
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	bic	r3, r0, #-16777216
	mov	r0, r4
	cmp	r3, #1
	beq	.L422
	cmp	r5, #1024
	blt	.L456
	mov	r1, #8
	mov	r0, r4
	add	r6, r6, #1
	bl	BsGet
	cmp	r6, r9
	bne	.L425
.L421:
	add	r6, r7, #86016
	movw	r3, #1292
	ldrsb	r9, [r6, r3]
	cmp	r9, #0
	beq	.L437
.L455:
	mov	r10, #0
.L426:
	ldr	r4, [r6, #1372]
	cmp	r4, #3
	ble	.L439
.L438:
	add	r4, r8, #328
	add	r8, r8, #344
	mov	r9, #0
.L430:
	ldr	r1, [r4, #4]!
	ldr	r0, [r6, #3040]
	bl	FreeUsdByDec
	cmp	r4, r8
	str	r9, [r4]
	mov	r3, #0
	bne	.L430
	mov	r4, r3
	str	r3, [r6, #1372]
.L439:
	ldr	r0, [r6, #3040]
	add	r4, r7, r4, lsl #2
	bl	GetUsd
	add	r4, r4, #86016
	str	r0, [r4, #1356]
	ldr	r2, [r6, #1372]
	add	r3, r7, r2, lsl #2
	add	r3, r3, #87040
	add	r3, r3, #72
	ldr	r3, [r3, #260]
	cmp	r3, #0
	beq	.L431
	ldr	r3, [r7]
	add	r0, r0, #1056
	ldr	r1, .L458
	ldrd	r2, [r3, #64]
	strd	r2, [r0]
	ldr	r3, [r4, #1356]
	ldr	r2, [r6, #1344]
	str	r2, [r3, #1044]
	ldr	r3, [r4, #1356]
	str	r5, [r3, #1052]
	ldr	r2, [r6, #2680]
	ldr	r3, [r4, #1356]
	ldrb	r2, [r2, #30]	@ zero_extendqisi2
	strb	r2, [r3, #1024]
	ldr	r3, [r4, #1356]
	ldr	r2, [r6, #3044]
	str	r2, [r3, #1032]
	ldr	r2, [r6, #2680]
	ldr	r3, [r4, #1356]
	ldrb	r2, [r2, #18]	@ zero_extendqisi2
	strb	r2, [r3, #1025]
	ldr	r3, [r6, #1340]
	tst	r3, #524288
	ldr	r3, [r4, #1356]
	movne	r2, #3
	moveq	r2, #1
	str	r2, [r3, #1040]
	ldr	r0, [r4, #1356]
	ldr	r2, [r0, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r0, #1052]
	ldr	r3, .L458+4
	ldrgt	r0, [r4, #1356]
	ldr	r3, [r3, #52]
	ldrgt	r2, [r0, #1052]
	blx	r3
	ldr	r3, .L458+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L435
	ldr	r2, [r4, #1356]
	movw	r3, #1064
	mov	r1, #6
	ldr	r0, [r6, #3040]
	blx	r5
.L435:
	ldr	r3, [r6, #1372]
	add	r3, r3, #1
	str	r3, [r6, #1372]
.L454:
	mov	r0, r10
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L437:
	movw	r3, #1293
	ldrsb	r3, [r6, r3]
	cmp	r3, #0
	beq	.L443
	ldr	r10, [r6, #1308]
	cmp	r10, #0
	beq	.L426
	ldr	r1, .L458+12
	mov	r0, r9
	bl	dprint_vfmw
	ldr	ip, .L458+4
	ldr	r3, [r6, #1304]
	mov	r2, #3
	ldr	r1, [r6, #1320]
	mov	r10, #1
	ldr	r0, [r6, #1324]
	sub	r3, r3, #3
	add	r1, r1, r3
	ldr	r3, [ip, #52]
	sub	r0, r0, #3
	blx	r3
	ldr	r2, [r6, #1308]
	ldr	r1, [r6, #1324]
	mov	r0, r4
	ldr	r3, [r6, #1300]
	add	r2, r2, #3
	sub	r1, r1, #3
	str	r2, [r6, #1304]
	sub	r3, r3, #3
	str	r1, [r6, #1320]
	str	r3, [r6, #1296]
	strb	r10, [r6, #1292]
	strb	r9, [r6, #1293]
	str	r9, [r6, #1308]
	str	r9, [r6, #1324]
	str	r9, [r6, #1300]
	bl	BsInit
	strb	r10, [r6, #1293]
	strb	r9, [r6, #1292]
	mov	r0, r4
	bl	BsToNextByte
	mov	r0, r4
	bl	BsResidBits
	add	r10, r0, #7
	cmp	r0, #0
	movlt	r0, r10
	mov	r10, r0, asr #3
	cmp	r10, #3
	ble	.L442
	sub	r10, r10, #3
	b	.L429
.L457:
	bl	BsGet
	ldr	r3, .L458
	strb	r0, [r3, r5]
	add	r5, r5, #1
.L428:
	add	r9, r9, #1
	cmp	r9, r10
	beq	.L455
.L429:
	mov	r1, #24
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	bic	r3, r0, #-16777216
	mov	r0, r4
	cmp	r3, #1
	beq	.L443
	cmp	r5, #1024
	blt	.L457
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	b	.L428
.L422:
	add	r6, r7, #86016
	mov	r10, r3
	ldr	r4, [r6, #1372]
	cmp	r4, #3
	bgt	.L438
	b	.L439
.L443:
	mov	r10, r3
	b	.L426
.L431:
	mov	r0, r3
	ldr	r1, .L458+16
	bl	dprint_vfmw
	b	.L454
.L440:
	mov	r5, #0
	b	.L421
.L442:
	mov	r10, r9
	b	.L426
.L459:
	.align	2
.L458:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC36
	.word	.LC37
	UNWIND(.fnend)
	.size	MP2_GetUsrData, .-MP2_GetUsrData
	.align	2
	.global	next_start_code
	.type	next_start_code, %function
next_start_code:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #87040
	mov	r7, r0
	add	r5, r5, #560
	mov	r0, r5
	bl	BsToNextByte
	mov	r0, r5
	bl	BsGetNextBytePtr
	mov	r4, r0
	mov	r0, r5
	bl	BsResidBits
	add	r1, r0, #7
	cmp	r0, #0
	movlt	r0, r1
	mov	r1, r0, asr #3
	cmp	r1, #4
	movle	r1, #0
	bgt	.L485
.L461:
	mov	r0, r5
	bl	BsLongSkip
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #3
	subgt	r6, r6, #3
	movgt	r4, #0
	bgt	.L467
	b	.L468
.L465:
	bl	BsSkip
	cmp	r4, r6
	beq	.L468
.L467:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, #1
	mov	r0, r5
	bne	.L465
.L470:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L468:
	add	r7, r7, #86016
	movw	r3, #1292
	ldrsb	r4, [r7, r3]
	cmp	r4, #0
	bne	.L464
	ldrb	r3, [r7, #1293]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L464
	ldr	r3, [r7, #1308]
	cmp	r3, #0
	beq	.L464
	ldr	r1, .L488
	mov	r0, #7
	bl	dprint_vfmw
	ldr	ip, .L488+4
	ldr	r3, [r7, #1304]
	mov	r2, #3
	ldr	r1, [r7, #1320]
	mov	r6, #1
	ldr	r0, [r7, #1324]
	sub	r3, r3, #3
	add	r1, r1, r3
	ldr	r3, [ip, #52]
	sub	r0, r0, #3
	blx	r3
	ldr	r2, [r7, #1308]
	ldr	r1, [r7, #1324]
	mov	r0, r5
	ldr	r3, [r7, #1300]
	add	r2, r2, #3
	sub	r1, r1, #3
	str	r2, [r7, #1304]
	sub	r3, r3, #3
	str	r1, [r7, #1320]
	str	r3, [r7, #1296]
	strb	r6, [r7, #1292]
	strb	r4, [r7, #1293]
	str	r4, [r7, #1308]
	str	r4, [r7, #1324]
	str	r4, [r7, #1300]
	bl	BsInit
	strb	r6, [r7, #1293]
	strb	r4, [r7, #1292]
	mov	r0, r5
	bl	BsToNextByte
	mov	r0, r5
	bl	BsGetNextBytePtr
	mov	r6, r0
	mov	r0, r5
	bl	BsResidBits
	add	r1, r0, #7
	cmp	r0, #0
	movlt	r0, r1
	mov	r1, r0, asr #3
	cmp	r1, #4
	movle	r1, r4
	bgt	.L486
.L469:
	mov	r0, r5
	bl	BsLongSkip
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #3
	ble	.L464
	sub	r6, r6, #3
	mov	r4, #0
	b	.L471
.L487:
	bl	BsSkip
	cmp	r4, r6
	beq	.L464
.L471:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, #1
	mov	r0, r5
	bne	.L487
	b	.L470
.L464:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L485:
	mov	r0, r4
	bl	MP2_SearchStartCode.part.2
	mov	r1, r0, asl #3
	b	.L461
.L486:
	mov	r0, r6
	bl	MP2_SearchStartCode.part.2
	mov	r1, r0, asl #3
	b	.L469
.L489:
	.align	2
.L488:
	.word	.LC36
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	next_start_code, .-next_start_code
	.align	2
	.global	GetSliceHdr
	.type	GetSliceHdr, %function
GetSliceHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #87040
	mov	r6, r0
	add	r5, r5, #560
	add	r7, r0, #86016
	b	.L491
.L498:
	bl	BsShow
	mov	r4, r0
	mov	r0, r5
	bl	BsPos
	sub	r3, r4, #256
	sub	r3, r3, #1
	mov	r1, #32
	cmp	r3, #174
	str	r0, [r7, #1400]
	mov	r0, r5
	bls	.L504
	bl	BsSkip
.L491:
	mov	r0, r6
	bl	next_start_code
	mov	r1, #32
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	beq	.L498
	cmn	r3, #1
	beq	.L493
.L499:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L493:
	ldr	r3, .L505
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L500
	add	r6, r6, #86016
	mov	r3, #0
	mov	r2, r3
	mov	r1, #113
	ldr	r0, [r6, #3040]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L504:
	bl	BsResidBits
	cmp	r0, #40
	ble	.L493
	ldr	r3, [r7, #1336]
	mov	r2, #0
	str	r2, [r7, #1396]
	cmp	r3, r2
	bne	.L497
	mov	r0, r6
	bl	MP2_GetSequenceInfo
	ldr	r3, [r7, #1388]
	cmp	r3, #0
	beq	.L499
.L497:
	mov	r0, r6
	bl	MP2_ProtocolPPSCheck
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L500:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L506:
	.align	2
.L505:
	.word	g_event_report
	UNWIND(.fnend)
	.size	GetSliceHdr, .-GetSliceHdr
	.align	2
	.global	sequence_header
	.type	sequence_header, %function
sequence_header:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r4, r0, #87040
	add	r6, r4, #560
	add	r7, r0, #86016
	mov	r2, #65536
	mov	r3, #0
	str	r2, [r7, #1340]
	mov	r1, #12
	str	r3, [r7, #1336]
	mov	r5, r0
	mov	r0, r6
	ldr	r8, [r7, #2680]
	bl	BsGet
	mov	r1, #12
	str	r0, [r8, #56]
	mov	r0, r6
	bl	BsGet
	mov	r1, #4
	str	r0, [r8, #60]
	mov	r0, r6
	bl	BsGet
	mov	r1, #4
	str	r0, [r8, #92]
	mov	r0, r6
	bl	BsGet
	mov	r1, #18
	str	r0, [r8, #96]
	mov	r0, r6
	bl	BsGet
	mov	r3, #2
	mov	r1, #1
	str	r3, [r8, #152]
	str	r0, [r8, #100]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	ldreq	r3, [r7, #1340]
	orreq	r3, r3, #1
	streq	r3, [r7, #1340]
.L508:
	mov	r1, #10
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #104]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #1]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	str	r0, [r8, #84]
	beq	.L515
	ldr	r3, .L522
	add	r2, r4, #588
	add	r1, r3, #64
	str	r1, [fp, #-48]
	mov	r0, r1
.L511:
	ldrb	r1, [r3, #1]!	@ zero_extendqisi2
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L511
.L510:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	str	r0, [r8, #88]
	beq	.L516
	add	r5, r5, #88064
	add	r3, r4, #844
	add	r5, r5, #76
	mov	r2, #16
.L513:
	str	r2, [r3, #4]!
	cmp	r3, r5
	bne	.L513
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L515:
	ldr	r3, .L522+4
	add	r9, r3, #64
	mov	r7, r3
	str	r3, [fp, #-48]
.L509:
	mov	r1, #8
	mov	r0, r6
	ldrb	r10, [r7, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r10, #21760
	cmp	r7, r9
	add	r3, r3, #148
	str	r0, [r5, r3, asl #2]
	bne	.L509
	b	.L510
.L516:
	ldr	r7, [fp, #-48]
	add	r8, r7, #64
.L512:
	mov	r1, #8
	mov	r0, r6
	ldrb	r4, [r7, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r4, #21760
	cmp	r7, r8
	add	r3, r3, #212
	str	r0, [r5, r3, asl #2]
	bne	.L512
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L523:
	.align	2
.L522:
	.word	.LANCHOR2-1
	.word	.LANCHOR2+63
	UNWIND(.fnend)
	.size	sequence_header, .-sequence_header
	.align	2
	.global	group_of_pictures_header
	.type	group_of_pictures_header, %function
group_of_pictures_header:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #87040
	add	r4, r0, #86016
	add	r5, r5, #560
	mov	r1, #1
	ldr	r6, [r4, #2680]
	mov	r7, #0
	mov	r0, r5
	bl	BsGet
	mov	r1, #5
	strb	r0, [r6, #2]
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #108]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #112]
	mov	r0, r5
	bl	BsSkip
	mov	r0, r5
	mov	r1, #6
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #116]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #120]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #124]
	mov	r0, r5
	bl	BsGet
	add	ip, r4, #1472
	add	r5, r4, #1456
	add	r3, ip, #12
	add	r5, r5, #4
	add	lr, r4, #1488
	add	lr, lr, #8
	str	r0, [r6, #128]
	ldmia	ip, {r0, r1, r2}
	stmia	r5, {r0, r1, r2}
	ldmia	r3, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	ldmia	lr, {r0, r1, r2}
	stmia	r3, {r0, r1, r2}
	str	r7, [r4, #1496]
	str	r7, [r4, #1504]
	str	r7, [r4, #1500]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	group_of_pictures_header, .-group_of_pictures_header
	.align	2
	.global	sequence_extension
	.type	sequence_extension, %function
sequence_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r6, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #560
	mov	r2, #0
	ldr	r3, [r6, #1340]
	mov	r1, #8
	str	r2, [r6, #1336]
	mov	r0, r4
	orr	r3, r3, #131072
	str	r3, [r6, #1340]
	ldr	r5, [r6, #2680]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #132]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r5, #35]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r5, #36]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	mov	r10, r0
	mov	r0, r4
	bl	BsGet
	mov	r1, #12
	mov	r8, r0
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	mov	r7, r0
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	bne	.L526
	ldr	r3, [r6, #1340]
	orr	r3, r3, #2
	str	r3, [r6, #1340]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L526:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	mov	r9, r0
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r5, #37]
	mov	r0, r4
	bl	BsGet
	mov	r1, #5
	strb	r0, [r5, #38]
	mov	r0, r4
	bl	BsGet
	ldrb	r3, [r5, #38]	@ zero_extendqisi2
	uxtb	r1, r0
	strb	r0, [r5, #39]
	add	r1, r1, #1
	add	r0, r3, #1
	bl	__aeabi_idiv
	ldr	r1, [r5, #96]
	ldr	r2, .L550
	ldr	r3, [r5, #132]
	add	r2, r2, r1, lsl #2
	tst	r3, #128
	ldr	r2, [r2, #160]
	mul	r0, r2, r0
	str	r0, [r5, #80]
	bne	.L549
	ubfx	r2, r3, #4, #3
	and	r3, r3, #15
	str	r2, [r5, #48]
	str	r3, [r5, #52]
.L529:
	ldr	r3, [r5, #56]
	ldr	r2, [r5, #60]
	ubfx	r3, r3, #0, #12
	ubfx	r2, r2, #0, #12
	orr	r3, r3, r10, asl #12
	orr	r8, r2, r8, asl #12
	str	r3, [r5, #56]
	cmp	r8, #0
	cmpne	r3, #0
	str	r8, [r5, #60]
	ldreq	r3, [r6, #1340]
	orreq	r3, r3, #1
	streq	r3, [r6, #1340]
	ldreq	r3, [r5, #56]
	cmp	r3, #8192
	bhi	.L531
	ldr	r3, [r5, #60]
	cmp	r3, #8192
	bls	.L532
.L531:
	ldr	r2, .L550+4
	ldr	r3, [r6, #1340]
	ldr	r4, [r2]
	orr	r3, r3, #1
	str	r3, [r6, #1340]
	cmp	r4, #0
	beq	.L532
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r6, #3040]
	blx	r4
.L532:
	ldr	r3, [r5, #100]
	mov	r1, #400
	ldr	r2, [r5, #48]
	add	r7, r3, r7, lsl #18
	str	r7, [r5, #100]
	sub	r0, r2, #4
	ldr	r3, [r5, #104]
	mul	r7, r1, r7
	cmp	r0, #1
	add	r9, r3, r9, lsl #10
	str	r9, [r5, #104]
	str	r7, [r5, #76]
	bls	.L534
	ldr	r3, .L550+4
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L535
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r6, #3040]
	blx	r4
	ldr	r2, [r5, #48]
.L535:
	ldr	r1, .L550+8
	mov	r0, #1
	bl	dprint_vfmw
.L534:
	ldr	r2, [r5, #52]
	sub	r3, r2, #4
	cmp	r3, #6
	ldmlsfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, .L550+4
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L536
	mov	r3, #0
	ldr	r0, [r6, #3040]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	ldr	r2, [r5, #52]
.L536:
	ldr	r1, .L550+12
	mov	r0, #1
	sub	sp, fp, #44
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L549:
	and	r3, r3, #15
	cmp	r3, #5
	moveq	r3, #133
	streq	r3, [r5, #48]
	moveq	r3, #8
	streq	r3, [r5, #52]
	b	.L529
.L551:
	.align	2
.L550:
	.word	.LANCHOR0
	.word	g_event_report
	.word	.LC38
	.word	.LC39
	UNWIND(.fnend)
	.size	sequence_extension, .-sequence_extension
	.align	2
	.global	sequence_display_extension
	.type	sequence_display_extension, %function
sequence_display_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r6, r0, #86016
	add	r5, r0, #87040
	mov	r3, #0
	mov	r2, #2
	ldr	r4, [r6, #2680]
	add	r5, r5, #560
	mov	r1, #3
	mov	r0, r5
	str	r2, [r4, #152]
	str	r3, [r4, #136]
	str	r3, [r4, #140]
	str	r3, [r4, #144]
	str	r3, [r4, #148]
	str	r3, [r4, #156]
	str	r3, [r4, #160]
	ldr	r3, [r6, #1340]
	orr	r3, r3, #262144
	str	r3, [r6, #1340]
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #136]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #140]
	bne	.L559
.L553:
	mov	r1, #14
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #156]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L554
	ldr	r3, [r6, #1340]
	orr	r3, r3, #4
	str	r3, [r6, #1340]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L554:
	mov	r0, r5
	mov	r1, #14
	bl	BsGet
	str	r0, [r4, #160]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L559:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #144]
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #148]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #152]
	b	.L553
	UNWIND(.fnend)
	.size	sequence_display_extension, .-sequence_display_extension
	.align	2
	.global	quant_matrix_extension
	.type	quant_matrix_extension, %function
quant_matrix_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #87040
	add	r3, r0, #86016
	add	r5, r5, #560
	mov	r7, r0
	mov	r1, #1
	ldr	r9, [r3, #2680]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r9, #84]
	beq	.L585
.L561:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r9, #88]
	ldreq	r6, .L587
	addeq	r8, r6, #64
	beq	.L563
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	beq	.L565
.L571:
	mov	r4, #64
.L566:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	subs	r4, r4, #1
	bne	.L566
.L565:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	beq	.L586
.L567:
	mov	r4, #64
.L568:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	subs	r4, r4, #1
	bne	.L568
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L563:
	mov	r1, #8
	mov	r0, r5
	ldrb	r4, [r6, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r4, #21760
	cmp	r6, r8
	add	r3, r3, #212
	str	r0, [r7, r3, asl #2]
	bne	.L563
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L571
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L567
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L586:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L585:
	ldr	r6, .L587
	add	r8, r6, #64
.L562:
	mov	r1, #8
	mov	r0, r5
	ldrb	r4, [r6, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r4, #21760
	cmp	r6, r8
	add	r3, r3, #148
	str	r0, [r7, r3, asl #2]
	bne	.L562
	b	.L561
.L588:
	.align	2
.L587:
	.word	.LANCHOR2+63
	UNWIND(.fnend)
	.size	quant_matrix_extension, .-quant_matrix_extension
	.align	2
	.global	sequence_scalable_extension
	.type	sequence_scalable_extension, %function
sequence_scalable_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r0, #87040
	mov	r1, #32
	add	r0, r0, #560
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
	UNWIND(.fnend)
	.size	sequence_scalable_extension, .-sequence_scalable_extension
	.align	2
	.global	picture_display_extension
	.type	picture_display_extension, %function
picture_display_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r8, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #560
	ldr	r5, [r8, #2680]
	ldr	r3, [r8, #1340]
	orr	r3, r3, #2097152
	str	r3, [r8, #1340]
	ldrb	r3, [r5, #35]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L591
	ldrb	r3, [r5, #24]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L603
.L599:
	mov	r7, #1
.L592:
	add	r5, r5, #168
	mov	r6, #0
	b	.L596
.L605:
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #12]
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	beq	.L602
	cmp	r6, r7
	bge	.L604
.L596:
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	add	r6, r6, r1
	str	r0, [r5, #4]!
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	cmp	r0, #0
	mov	r0, r4
	bne	.L605
.L602:
	ldr	r3, [r8, #1340]
	orr	r3, r3, #32
	str	r3, [r8, #1340]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L591:
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L599
	ldrb	r3, [r5, #24]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r7, #2
	movne	r7, #3
	b	.L592
.L603:
	ldrb	r3, [r5, #18]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r7, #2
	movne	r7, #3
	b	.L592
.L604:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	picture_display_extension, .-picture_display_extension
	.align	2
	.global	picture_coding_extension
	.type	picture_coding_extension, %function
picture_coding_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r8, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #560
	ldr	r7, [r8, #2680]
	ldr	r3, [r8, #1340]
	add	r10, r7, #12
	add	r9, r7, #16
	orr	r3, r3, #1048576
	str	r3, [r8, #1340]
.L607:
	mov	r6, r10
	mov	r5, #0
.L609:
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	add	r5, r5, #1
	uxtb	r0, r0
	strb	r0, [r6], #1
	sub	r3, r0, #10
	cmp	r0, #0
	cmpne	r3, #4
	ldrls	r3, [r8, #1340]
	orrls	r3, r3, #16
	strls	r3, [r8, #1340]
	cmp	r5, #2
	bne	.L609
	add	r10, r10, #2
	cmp	r10, r9
	bne	.L607
	mov	r1, r5
	mov	r0, r4
	bl	BsGet
	mov	r1, r5
	strb	r0, [r7, #16]
	mov	r0, r4
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #17]
	cmp	r0, #0
	bne	.L611
	ldr	r3, [r8, #1340]
	orr	r3, r3, #16
	str	r3, [r8, #1340]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L611:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #18]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #19]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #20]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #21]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #22]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #23]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #24]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #25]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #26]
	mov	r0, r4
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #3]
	cmp	r0, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #3
	strb	r0, [r7, #27]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #28]
	mov	r0, r4
	bl	BsGet
	mov	r1, #7
	strb	r0, [r7, #29]
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	str	r0, [r7, #40]
	mov	r0, r4
	bl	BsGet
	str	r0, [r7, #44]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	picture_coding_extension, .-picture_coding_extension
	.align	2
	.global	picture_spatial_scalable_extension
	.type	picture_spatial_scalable_extension, %function
picture_spatial_scalable_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r0, #87040
	mov	r1, #32
	add	r0, r0, #560
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
	UNWIND(.fnend)
	.size	picture_spatial_scalable_extension, .-picture_spatial_scalable_extension
	.align	2
	.global	picture_temporal_scalable_extension
	.type	picture_temporal_scalable_extension, %function
picture_temporal_scalable_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r0, #87040
	mov	r1, #32
	add	r0, r0, #560
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
	UNWIND(.fnend)
	.size	picture_temporal_scalable_extension, .-picture_temporal_scalable_extension
	.align	2
	.global	extra_bit_information
	.type	extra_bit_information, %function
extra_bit_information:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #87040
	mov	r5, #0
	add	r4, r4, #560
	b	.L623
.L625:
	bl	BsSkip
	mov	r0, r4
	bl	BsResidBits
	add	r5, r5, #1
	cmp	r0, #8
	ble	.L624
.L623:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	cmp	r0, #0
	mov	r0, r4
	bne	.L625
.L624:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	extra_bit_information, .-extra_bit_information
	.align	2
	.global	picture_header
	.type	picture_header, %function
picture_header:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #560
	mov	r1, #10
	ldr	r3, [r2, #1340]
	mov	r6, r0
	mov	r0, r4
	ldr	r5, [r2, #2680]
	bic	r3, r3, #3145728
	bic	r3, r3, #56
	orr	r3, r3, #524288
	str	r3, [r2, #1340]
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #164]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	strb	r0, [r5, #30]
	mov	r0, r4
	bl	BsGet
	ldrb	r7, [r5, #30]	@ zero_extendqisi2
	sub	r3, r7, #2
	cmp	r3, #1
	str	r0, [r5, #168]
	bls	.L629
.L627:
	cmp	r7, #3
	beq	.L630
.L628:
	mov	r0, r6
	bl	extra_bit_information
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L630:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, r7
	strb	r0, [r5, #33]
	mov	r0, r4
	bl	BsGet
	strb	r0, [r5, #34]
	b	.L628
.L629:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #3
	strb	r0, [r5, #31]
	mov	r0, r4
	bl	BsGet
	ldrb	r7, [r5, #30]	@ zero_extendqisi2
	strb	r0, [r5, #32]
	b	.L627
	UNWIND(.fnend)
	.size	picture_header, .-picture_header
	.align	2
	.global	copyright_extension
	.type	copyright_extension, %function
copyright_extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r0, #87040
	mov	r1, #32
	add	r0, r0, #560
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
	UNWIND(.fnend)
	.size	copyright_extension, .-copyright_extension
	.align	2
	.global	extension
	.type	extension, %function
extension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #87040
	mov	r5, r0
	add	r4, r4, #560
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	sub	r0, r0, #1
	cmp	r0, #9
	ldrls	pc, [pc, r0, asl #2]
	b	.L633
.L635:
	.word	.L634
	.word	.L636
	.word	.L637
	.word	.L638
	.word	.L638
	.word	.L633
	.word	.L640
	.word	.L641
	.word	.L638
	.word	.L638
.L640:
	mov	r0, r5
	bl	picture_display_extension
.L633:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L638:
	mov	r0, r4
	mov	r1, #32
	bl	BsSkip
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L637:
	mov	r0, r5
	bl	quant_matrix_extension
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L641:
	mov	r0, r5
	bl	picture_coding_extension
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L634:
	mov	r0, r5
	bl	sequence_extension
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L636:
	mov	r0, r5
	bl	sequence_display_extension
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	extension, .-extension
	.align	2
	.global	MPEG2DEC_Init
	.type	MPEG2DEC_Init, %function
MPEG2DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 912
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #916)
	sub	sp, sp, #916
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r0
	mov	r7, r1
	moveq	r8, #1
	movne	r8, #0
	beq	.L651
	ldr	r3, [r1, #624]
	add	r4, r0, #86016
	ldr	r5, .L655
	cmp	r3, #1
	strne	r8, [fp, #-956]
	strne	r8, [fp, #-952]
	beq	.L652
.L647:
	ldr	r10, [r4, #3032]
	mov	r2, #89088
	ldr	r3, [r5, #48]
	mov	r1, #0
	add	r5, r6, #88064
	mov	r0, r6
	blx	r3
	add	r0, r5, #640
	str	r10, [r4, #3032]
	mov	r9, #1
	bl	ResetVoQueue
	add	r3, r6, #45056
	str	r7, [r6]
	mov	r10, #0
	add	r2, r5, #240
	str	r10, [r4, #3052]
	str	r2, [r4, #2684]
	add	r5, r5, #436
	str	r9, [r4, #1352]
	mov	r1, #3
	str	r5, [r4, #2680]
	mov	r0, r6
	strb	r1, [r3, #257]
	str	r10, [r4, #1396]
	ldr	r3, [r7, #8]
	str	r10, [r4, #1388]
	ldr	r5, .L655
	str	r3, [r4, #1328]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #3040]
	beq	.L653
	ldr	r7, [r7, #624]
	cmp	r7, #1
	movne	r7, r9
	beq	.L654
.L646:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L654:
	ldr	r2, [fp, #-952]
	add	r6, r6, #87040
	ldr	r3, [r4, #1340]
	sub	r1, fp, #556
	add	r0, r6, #592
	str	r8, [r4, #1336]
	str	r2, [r4, #1376]
	orr	r3, r3, #65536
	ldr	r2, [fp, #-956]
	str	r3, [r4, #1340]
	ldr	r3, [r5, #52]
	str	r2, [r4, #1388]
	mov	r2, #256
	blx	r3
	ldr	r3, [r5, #52]
	sub	r1, fp, #300
	add	r0, r6, #848
	mov	r2, #256
	blx	r3
	ldr	r3, [r5, #52]
	sub	r1, fp, #948
	mov	r2, #196
	ldr	r0, [r4, #2680]
	blx	r3
	ldr	r3, [r5, #52]
	ldr	r0, [r4, #2684]
	mov	r2, #196
	sub	r1, fp, #752
	blx	r3
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L652:
	ldr	ip, [r4, #1376]
	add	r10, r0, #87040
	add	r1, r10, #592
	ldr	r3, [r5, #52]
	mov	r2, #256
	sub	r0, fp, #556
	str	ip, [fp, #-952]
	ldr	ip, [r4, #1388]
	ldr	r8, [r4, #1336]
	str	ip, [fp, #-956]
	blx	r3
	add	r1, r10, #848
	ldr	r3, [r5, #52]
	mov	r2, #256
	sub	r0, fp, #300
	blx	r3
	ldr	r3, [r5, #52]
	ldr	r1, [r4, #2680]
	mov	r2, #196
	sub	r0, fp, #948
	blx	r3
	ldr	r3, [r5, #52]
	ldr	r1, [r4, #2684]
	mov	r2, #196
	sub	r0, fp, #752
	blx	r3
	b	.L647
.L651:
	ldr	r1, .L655+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r7, #1
	b	.L646
.L653:
	mov	r0, r10
	ldr	r1, .L655+8
	bl	dprint_vfmw
	mvn	r7, #19
	b	.L646
.L656:
	.align	2
.L655:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC40
	.word	.LC41
	UNWIND(.fnend)
	.size	MPEG2DEC_Init, .-MPEG2DEC_Init
	.align	2
	.global	MPEG2DEC_Destroy
	.type	MPEG2DEC_Destroy, %function
MPEG2DEC_Destroy:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r3, r0, #0
	beq	.L660
	add	r3, r3, #86016
	ldr	r1, .L661
	mov	r0, #2
	ldr	r2, [r3, #1348]
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L660:
	ldr	r3, .L661+4
	movw	r2, #2954
	ldr	r1, .L661+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L662:
	.align	2
.L661:
	.word	.LC44
	.word	.LC42
	.word	.LC43
	UNWIND(.fnend)
	.size	MPEG2DEC_Destroy, .-MPEG2DEC_Destroy
	.align	2
	.global	MPEG2DEC_RecycleImage
	.type	MPEG2DEC_RecycleImage, %function
MPEG2DEC_RecycleImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	mov	r4, r1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r1, #31
	bhi	.L671
	add	r5, r0, #86016
	mov	r2, #0
	ldr	r0, [r5, #3040]
	bl	FSP_SetDisplay
	mov	r1, r4
	ldr	r0, [r5, #3040]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	addne	r4, r0, #536
	addne	r8, r0, #568
	movne	r6, #0
	movne	r7, #0
	beq	.L668
.L667:
	ldr	r1, [r4, #8]!
	ldr	r0, [r5, #3040]
	bl	FreeUsdByDec
	cmp	r4, r8
	strd	r6, [r4]
	bne	.L667
.L668:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L671:
	ldr	r3, .L672
	movw	r2, #3086
	ldr	r1, .L672+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L673:
	.align	2
.L672:
	.word	.LC45
	.word	.LC43
	UNWIND(.fnend)
	.size	MPEG2DEC_RecycleImage, .-MPEG2DEC_RecycleImage
	.align	2
	.global	MPEG2DEC_GetRemainImg
	.type	MPEG2DEC_GetRemainImg, %function
MPEG2DEC_GetRemainImg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r4, r0, #0
	beq	.L699
	ldr	r3, [r4]
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L698
	add	r5, r4, #86016
	ldr	r1, [r5, #1420]
	ldr	r0, [r5, #3040]
	bl	FSP_GetFsImagePtr
	subs	r9, r0, #0
	beq	.L698
	ldr	r1, [r5, #1420]
	ldr	r0, [r5, #3040]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L696
.L698:
	add	r6, r4, #88064
.L677:
	add	r7, r6, #640
.L682:
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	GetVoLastImageID
.L696:
	mov	r0, r4
	bl	MP2_SetImgFormat
	add	ip, r4, #87040
	add	r3, ip, #328
	add	r2, r9, #544
	add	ip, ip, #344
	mov	r0, #0
.L679:
	ldr	r1, [r3, #4]!
	mov	r8, #0
	add	r2, r2, #8
	cmp	r1, r8
	strne	r0, [r2, #-4]
	strne	r1, [r2, #-8]
	cmp	r3, ip
	str	r0, [r3]
	bne	.L679
	add	r6, r4, #88064
	mov	r3, #1
	add	r7, r6, #640
	str	r8, [r5, #1372]
	mov	r2, r3
	str	r3, [r9, #180]
	ldr	r1, [r9, #148]
	ldr	r0, [r5, #3040]
	bl	FSP_SetDisplay
	ldr	r0, [r5, #3040]
	mov	r3, r7
	str	r9, [sp]
	mov	r2, r4
	mov	r1, #3
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L680
	ldr	r1, [r9, #148]
	mov	r0, r4
	bl	MPEG2DEC_RecycleImage
	b	.L682
.L680:
	ldr	r3, [r9, #152]
	cmp	r3, #100
	bhi	.L677
	ldr	r3, [r9, #68]
	cmp	r3, #31
	bls	.L677
	ldr	r3, [r9, #72]
	cmp	r3, #31
	movhi	r0, r8
	bls	.L682
.L693:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L699:
	ldr	r3, .L700
	movw	r2, #3114
	ldr	r1, .L700+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L693
.L701:
	.align	2
.L700:
	.word	.LC42
	.word	.LC43
	UNWIND(.fnend)
	.size	MPEG2DEC_GetRemainImg, .-MPEG2DEC_GetRemainImg
	.align	2
	.global	MPEG2DEC_GetImageBuffer
	.type	MPEG2DEC_GetImageBuffer, %function
MPEG2DEC_GetImageBuffer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	beq	.L714
	add	r3, r4, #45056
	add	r5, r4, #86016
	ldrb	r3, [r3, #257]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L705
	ldr	r3, [r5, #1352]
	cmp	r3, #0
	beq	.L706
.L705:
	ldr	r0, [r5, #3040]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L706
	ldr	r0, [r5, #3040]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L715
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L706:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L715:
	add	r1, r4, #88064
	ldr	r0, [r5, #3040]
	add	r1, r1, #640
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L714:
	ldr	r3, .L716
	movw	r2, #3403
	ldr	r1, .L716+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L717:
	.align	2
.L716:
	.word	.LC42
	.word	.LC43
	UNWIND(.fnend)
	.size	MPEG2DEC_GetImageBuffer, .-MPEG2DEC_GetImageBuffer
	.align	2
	.global	MP2_ClearCurPacket
	.type	MP2_ClearCurPacket, %function
MP2_ClearCurPacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r1, #0
	mov	r5, r0
	beq	.L724
	ldr	r1, [r4, #20]
	bl	SM_ReleaseStreamSeg
	ldrsb	r3, [r4]
	cmp	r3, #1
	beq	.L720
	mov	r0, r5
	ldr	r1, [r4, #24]
	bl	SM_ReleaseStreamSeg
.L720:
	ldr	r3, .L725
	mov	r0, r4
	mov	r2, #36
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L724:
	mov	r0, r4
	ldr	r3, .L725+4
	movw	r2, #3478
	ldr	r1, .L725+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L726:
	.align	2
.L725:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC46
	.word	.LC43
	UNWIND(.fnend)
	.size	MP2_ClearCurPacket, .-MP2_ClearCurPacket
	.align	2
	.global	MP2_ReceivePacket
	.type	MP2_ReceivePacket, %function
MP2_ReceivePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r1, #0
	add	r3, r0, #40960
	beq	.L732
	mov	r5, #0
	str	r5, [r3, #1032]
	ldr	r1, [r4, #16]
	str	r1, [r3, #1076]
	ldr	r1, [r4, #12]
	str	r1, [r3, #1040]
	ldr	r1, [r4]
	str	r1, [r3, #1064]
	ldr	r1, [r4, #16]
	str	r1, [r3, #1048]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	strb	r1, [r3, #1036]
	ldr	r1, [r4, #20]
	str	r1, [r3, #1056]
	ldrb	ip, [r4, #5]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L730
	ldr	r1, [r4, #92]
	str	r1, [r3, #1044]
	ldr	r1, [r4, #80]
	str	r1, [r3, #1068]
	ldr	r1, [r4, #96]
	str	r1, [r3, #1052]
	ldrb	r1, [r4, #85]	@ zero_extendqisi2
	strb	r1, [r3, #1037]
	ldr	r1, [r4, #100]
	str	r1, [r3, #1060]
	ldrb	ip, [r4, #85]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L731
	add	r1, r0, #41984
	mov	r0, r2
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	ldr	r1, .L733
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L731:
	mov	r0, ip
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L730:
	str	r5, [r3, #1044]
	mov	r0, ip
	str	r5, [r3, #1068]
	str	r5, [r3, #1052]
	strb	r5, [r3, #1037]
	str	r5, [r3, #1060]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L732:
	ldr	r1, .L733+4
	mov	r0, #1
	ldr	r2, [r3, #1092]
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L734:
	.align	2
.L733:
	.word	.LC48
	.word	.LC47
	UNWIND(.fnend)
	.size	MP2_ReceivePacket, .-MP2_ReceivePacket
	.align	2
	.global	MP2_ClearCurPic
	.type	MP2_ClearCurPic, %function
MP2_ClearCurPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	beq	.L736
	add	r6, r4, #45056
	ldr	r3, [r6, #244]
	cmp	r3, #0
	addne	r7, r4, #86016
	movne	r5, #0
	bne	.L740
	b	.L741
.L739:
	ldr	r3, [r6, #244]
	add	r4, r4, #44
	cmp	r5, r3
	bcs	.L741
.L740:
	ldr	r1, [r4, #268]
	add	r5, r5, #1
	ldr	r0, [r7, #3040]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #248]
	cmp	r3, #0
	beq	.L739
	ldr	r3, [r4, #256]
	cmp	r3, #0
	beq	.L739
	ldr	r1, [r4, #272]
	add	r4, r4, #44
	ldr	r0, [r7, #3040]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #244]
	cmp	r5, r3
	bcc	.L740
.L741:
	mov	r3, #0
	str	r3, [r6, #244]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L736:
	ldr	r3, .L750
	movw	r2, #3499
	ldr	r1, .L750+4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L751:
	.align	2
.L750:
	.word	.LC42
	.word	.LC43
	UNWIND(.fnend)
	.size	MP2_ClearCurPic, .-MP2_ClearCurPic
	.align	2
	.global	MPEG2DEC_VDMPostProc
	.type	MPEG2DEC_VDMPostProc, %function
MPEG2DEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r5, r0, #0
	mov	r8, r1
	beq	.L821
	ldrb	r3, [r5, #153]	@ zero_extendqisi2
	add	r4, r5, #86016
	mov	r2, r1
	mov	r0, #22
	ldr	r1, .L829
	add	r6, r5, #8
	strb	r3, [r4, #1520]
	add	r9, r5, #45056
	ldr	r7, [r4, #2680]
	bl	dprint_vfmw
	ldr	r2, [r5, #4]
	mov	r0, r5
	ldr	r3, [r4, #2680]
	add	r1, r2, #45056
	ldrb	r2, [r2, #144]	@ zero_extendqisi2
	strb	r2, [r3, #4]
	ldr	r2, [r1, #240]
	str	r2, [r3, #8]
	ldr	r3, [r4, #2680]
	ldr	r2, [r5]
	ldr	r1, [r3, #48]
	str	r1, [r2, #576]
	ldr	r2, [r3, #52]
	ldr	r3, [r5]
	str	r2, [r3, #580]
	ldr	r3, [r4, #3044]
	ldr	r2, [r4, #3048]
	ldr	r1, [r5]
	cmp	r3, r2
	rsbge	r3, r2, r3
	movlt	r3, #0
	str	r3, [r1, #584]
	bl	MP2_ClearCurPic
	ldr	r3, .L829+4
	movw	r2, #45304
	mov	r0, r6
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, [r4, #1424]
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #1420]
	mov	r6, r0
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #1416]
	mov	r10, r0
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	cmp	r6, #0
	beq	.L822
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r8, #0
	movlt	r8, #0
	strb	r3, [r9, #256]
	blt	.L757
	cmp	r8, #100
	movge	r8, #100
.L757:
	ldr	r1, .L829+8
	mov	r0, #22
	str	r8, [r6, #152]
	bl	dprint_vfmw
	mov	r0, r5
	bl	MP2_SetImgFormat
	ldrb	r3, [r7, #17]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L760
	ldr	r3, [r4, #1352]
	cmp	r3, #1
	beq	.L760
.L761:
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L792
	ldr	r3, [r5]
	ldr	r2, [r6, #152]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L823
.L792:
	mov	r0, #1
.L817:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L823:
	mov	r2, #1
	ldr	r1, [r4, #1424]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	ldr	r1, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L786
	ldr	r1, [r5, #544]
	add	r6, r5, #560
	ldr	r0, [r4, #3040]
	add	r7, r5, #576
	bl	FreeUsdByDec
	ldr	r1, [r5, #552]
	ldr	r0, [r4, #3040]
	add	r8, r5, #544
	bl	FreeUsdByDec
	ldr	r1, [r5, #560]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	ldr	r1, [r5, #568]
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r8]
	strd	r0, [r6, #-8]
	strd	r0, [r6]
	strd	r0, [r7, #-8]
	ldr	r1, [r4, #1420]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1416]
	ldr	r0, [r4, #3040]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #3040]
	str	r3, [r4, #1416]
	str	r3, [r4, #1420]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L824
.L786:
	mov	r3, #0
	mov	r0, #1
	str	r3, [r4, #1380]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L760:
	add	r0, r5, #87040
	add	r2, r6, #544
	add	r3, r0, #328
	add	r0, r0, #344
	mov	ip, #0
.L759:
	ldr	r1, [r3, #4]!
	mov	lr, #0
	cmp	r1, lr
	stmneia	r2, {r1, ip}
	cmp	r3, r0
	str	ip, [r3]
	add	r2, r2, #8
	bne	.L759
	str	lr, [r4, #1372]
	ldr	r3, [r5]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	bne	.L763
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L763
	ldr	r1, [r4, #1416]
	cmn	r1, #1
	str	r1, [r4, #1428]
	beq	.L766
.L826:
	ldr	r0, [r4, #3040]
	bl	FSP_GetDisplay
	cmp	r0, #1
	beq	.L770
	ldr	r1, [r4, #1428]
	ldr	r0, [r4, #3040]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L770
.L766:
	ldrb	r3, [r7, #35]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L825
	ldrb	r3, [r7, #26]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #1504]
	addeq	r3, r3, #1
	addne	r3, r3, #1
	streq	r3, [r4, #1504]
	ldreqb	r3, [r7, #24]	@ zero_extendqisi2
	ldreq	r2, [r4, #1500]
	addeq	r3, r3, #2
	strne	r3, [r4, #1504]
	addeq	r3, r2, r3
	movne	r3, r3, asl #1
	str	r3, [r4, #1500]
.L783:
	ldr	r2, [r4, #1496]
	ldr	r3, [r4, #1348]
	add	r2, r2, #1
	str	r2, [r4, #1496]
	add	r3, r3, #1
	str	r3, [r4, #1348]
	b	.L761
.L763:
	ldr	r1, [r4, #1424]
	cmn	r1, #1
	str	r1, [r4, #1428]
	bne	.L826
	b	.L766
.L821:
	ldr	r3, .L829+12
	movw	r2, #3222
	ldr	r1, .L829+16
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L770:
	ldr	r1, [r4, #1428]
	ldr	r0, [r4, #3040]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L827
	ldr	r2, [r8, #152]
	cmp	r2, #0
	beq	.L772
	ldr	r3, [r5]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	bhi	.L773
.L772:
	ldr	r9, [r4, #1428]
	ldr	r0, [r4, #3040]
	mov	r1, r9
	bl	FSP_GetRef
	mov	r2, r9
	ldr	r1, .L829+20
	mov	r3, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #1428]
	ldr	r0, [r4, #3040]
	bl	FSP_SetDisplay
	ldr	r10, [r4, #3040]
	ldr	r1, [r4, #1420]
	mov	r0, r10
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #1428]
	mov	r9, r0
	str	r0, [fp, #-52]
	mov	r0, r10
	bl	FSP_GetFsImagePtr
	cmp	r9, #0
	cmpne	r0, #0
	beq	.L828
	add	r9, r0, #592
	mvn	r1, #0
	mvn	r0, #0
	ldrd	r2, [r9, #-8]
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L775
	ldr	r1, [r4, #1420]
	mov	r0, r10
	bl	FSP_GetDisplay
	cmp	r0, #1
	beq	.L779
	ldr	r1, [r4, #1420]
	mov	r0, r10
	bl	FSP_GetDisplay
	cmp	r0, #2
	bne	.L775
.L779:
	ldr	r3, [fp, #-52]
	add	r1, r3, #592
	ldrd	r2, [r9, #-8]
	str	r1, [fp, #-52]
	ldrd	r0, [r1, #-8]
	cmp	r3, r1
	cmpeq	r2, r0
	bls	.L775
	strd	r0, [sp]
	mov	r0, r10
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L775
	ldr	r10, [fp, #-52]
	mov	r0, #29
	ldr	r1, .L829+24
	ldrd	r2, [r10, #-8]
	strd	r2, [fp, #-60]
	ldrd	r2, [r9, #-8]
	strd	r2, [fp, #-52]
	ldrd	r2, [fp, #-60]
	strd	r2, [sp]
	ldrd	r2, [fp, #-52]
	bl	dprint_vfmw
	ldrd	r0, [r9, #-8]
	ldrd	r2, [r10, #-8]
	strd	r2, [r9, #-8]
	strd	r0, [r10, #-8]
.L775:
	add	r3, r5, #88064
	ldr	r0, [r4, #3040]
	add	r3, r3, #640
	str	r8, [sp]
	mov	r2, r5
	mov	r1, #3
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L788
	add	r5, r8, #536
	add	r8, r8, #568
	mov	r6, #0
	mov	r7, #0
.L780:
	ldr	r1, [r5, #8]!
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	cmp	r5, r8
	strd	r6, [r5]
	bne	.L780
	ldr	r0, [r4, #3040]
	mov	r2, #0
	ldr	r1, [r4, #1428]
	bl	FSP_SetDisplay
	mov	r0, #0
	b	.L817
.L825:
	ldrb	r2, [r7, #24]	@ zero_extendqisi2
	ldrb	r3, [r7, #18]	@ zero_extendqisi2
	ldr	r1, [r4, #1504]
	add	r3, r2, r3
	add	r3, r3, #1
	add	r3, r3, r1
	str	r3, [r4, #1504]
	mov	r3, r3, asl #1
	str	r3, [r4, #1500]
	b	.L783
.L824:
	ldr	r0, [r4, #3040]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #1416]
	str	r0, [r4, #1420]
	b	.L786
.L788:
	ldr	r3, [r5]
	str	r0, [r3, #956]
	ldr	r3, [r4, #3048]
	add	r3, r3, #1
	str	r3, [r4, #3048]
	b	.L766
.L773:
	ldr	r1, .L829+28
	mov	r0, #1
	bl	dprint_vfmw
	add	r9, r8, #536
	add	r10, r8, #568
.L781:
	ldr	r1, [r9, #8]!
	ldr	r0, [r4, #3040]
	bl	FreeUsdByDec
	cmp	r9, r10
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r9]
	bne	.L781
	ldr	r1, [r4, #1428]
	ldr	r0, [r4, #3040]
	bl	FSP_SetDisplay
	b	.L766
.L822:
	str	r0, [sp]
	mov	r3, r10
	mov	r2, r6
	ldr	r1, .L829+32
	mov	r0, r6
	bl	dprint_vfmw
	mov	r0, r6
	b	.L817
.L828:
	ldr	r1, .L829+36
	mov	r0, #0
	bl	dprint_vfmw
	b	.L775
.L827:
	movw	r2, #3319
	ldr	r1, .L829+40
	bl	dprint_vfmw
	mov	r0, r8
	b	.L817
.L830:
	.align	2
.L829:
	.word	.LC49
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC51
	.word	.LC42
	.word	.LC43
	.word	.LC52
	.word	.LC54
	.word	.LC55
	.word	.LC50
	.word	.LC53
	.word	.LC24
	UNWIND(.fnend)
	.size	MPEG2DEC_VDMPostProc, .-MPEG2DEC_VDMPostProc
	.align	2
	.global	MP2_u_v
	.type	MP2_u_v, %function
MP2_u_v:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r2
	mov	r6, r0
	mov	r7, r1
	bl	BsShow
	mov	r1, r7
	mov	r4, r0
	mov	r0, r6
	bl	BsSkip
	mov	r3, r4
	mov	r2, r5
	ldr	r1, .L832
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L833:
	.align	2
.L832:
	.word	.LC56
	UNWIND(.fnend)
	.size	MP2_u_v, .-MP2_u_v
	.align	2
	.global	MP2_DecSliceHeader
	.type	MP2_DecSliceHeader, %function
MP2_DecSliceHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r0, #4]
	mov	r1, #1
	mov	r3, #0
	mov	r5, r0
	cmp	r2, #175
	str	r1, [r0, #16]
	ldr	r4, [r0, #52]
	str	r3, [r0, #24]
	bls	.L835
	ldr	r2, [r0]
	cmp	r2, r3
	beq	.L847
.L835:
	ldr	r2, [r5, #20]
	mov	r0, r4
	ldr	r1, [r5, #8]
	sub	r2, r2, #1
	add	r3, r2, r3
	ldr	r2, .L850
	mul	r3, r1, r3
	mov	r1, #5
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r5, #28]
	bl	MP2_u_v
	mov	r3, #0
	mov	r1, #1
	str	r3, [r5, #32]
	str	r0, [r5, #44]
	mov	r0, r4
	bl	BsShow
	cmp	r0, #0
	bne	.L848
.L839:
	mov	r0, r4
	ldr	r2, .L850+4
	mov	r1, #1
	bl	MP2_u_v
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L848:
	ldr	r2, .L850+8
	mov	r1, #1
	mov	r0, r4
	bl	MP2_u_v
	ldr	r2, .L850+12
	mov	r1, #1
	mov	r0, r4
	bl	MP2_u_v
	ldr	r2, .L850+16
	mov	r1, #7
	str	r0, [r5, #32]
	mov	r0, r4
	bl	MP2_u_v
	b	.L838
.L849:
	bl	BsShow
	ldr	r2, .L850+4
	mov	r1, #1
	cmp	r0, #0
	mov	r0, r4
	beq	.L839
	bl	MP2_u_v
	ldr	r2, .L850+20
	mov	r1, #8
	mov	r0, r4
	bl	MP2_u_v
.L838:
	mov	r0, r4
	bl	BsResidBits
	mov	r1, #1
	cmp	r0, #0
	mov	r0, r4
	bgt	.L849
	b	.L839
.L847:
	ldr	r2, .L850+24
	mov	r1, #3
	mov	r0, r4
	bl	MP2_u_v
	mov	r3, r0, asl #7
	str	r0, [r5, #24]
	b	.L835
.L851:
	.align	2
.L850:
	.word	.LC58
	.word	.LC59
	.word	.LC60
	.word	.LC61
	.word	.LC62
	.word	.LC63
	.word	.LC57
	UNWIND(.fnend)
	.size	MP2_DecSliceHeader, .-MP2_DecSliceHeader
	.align	2
	.global	MP2_ExitMb
	.type	MP2_ExitMb, %function
MP2_ExitMb:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r3, #0
	str	r3, [r0, #16]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_ExitMb, .-MP2_ExitMb
	.align	2
	.global	MP2_WriteSliceInfo
	.type	MP2_WriteSliceInfo, %function
MP2_WriteSliceInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r7, r0, #45056
	mov	r4, #44
	add	r5, r0, #86016
	mov	r6, r0
	ldr	r2, [r7, #244]
	ldr	r1, [r5, #1560]
	cmp	r2, #1024
	mla	r4, r4, r2, r0
	str	r1, [r4, #280]
	ldr	r1, [r5, #1572]
	str	r1, [r4, #284]
	ldr	r1, [r5, #1568]
	str	r1, [r4, #276]
	bcs	.L859
	ldr	r2, [r5, #1608]
	add	r0, r0, #87040
	ldr	r3, [r5, #1296]
	add	r0, r0, #560
	and	r1, r2, #7
	str	r1, [r4, #260]
	add	r3, r3, r2, lsr #3
	str	r3, [r4, #244]
	ldr	r3, [r5, #1312]
	str	r3, [r4, #268]
	bl	BsResidBits
	movw	r2, #1292
	str	r0, [r4, #252]
	ldrsh	r3, [r5, r2]
	cmp	r3, #1
	beq	.L860
	cmp	r3, #256
	bne	.L858
	ldr	r1, [r5, #1300]
	mov	r2, #0
	str	r2, [r4, #264]
	str	r1, [r4, #248]
	ldr	r3, [r5, #1316]
	str	r3, [r4, #272]
	ldr	r3, [r5, #1308]
	mov	r3, r3, asl #3
	str	r3, [r4, #256]
.L857:
	ldr	r3, [r7, #244]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r7, #244]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L859:
	mov	r3, #1024
	ldr	r1, .L861
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP2_ClearCurPic
	ldr	r3, [r5, #1340]
	mov	r0, #0
	str	r0, [r5, #1396]
	bic	r3, r3, #5767168
	str	r3, [r5, #1340]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L860:
	mov	r3, #0
	add	r4, r4, #252
	str	r3, [r4, #-4]
	str	r3, [r4, #12]
	str	r3, [r4, #20]
	str	r3, [r4, #4]
	b	.L857
.L858:
	movw	r3, #1293
	ldrsb	r2, [r5, r2]
	ldrsb	r3, [r5, r3]
	mov	r0, #1
	ldr	r1, .L861+4
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L862:
	.align	2
.L861:
	.word	.LC64
	.word	.LC65
	UNWIND(.fnend)
	.size	MP2_WriteSliceInfo, .-MP2_WriteSliceInfo
	.align	2
	.global	MP2_MbAddrInc
	.type	MP2_MbAddrInc, %function
MP2_MbAddrInc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r1, #4
	mov	r6, r0
	bl	BsShow
	ldr	r5, .L869
	add	r0, r5, r0, lsl #3
	ldr	r4, [r0, #224]
	ldr	r1, [r0, #228]
	cmp	r4, #6
	bls	.L867
	cmp	r4, #9
	beq	.L868
	mov	r1, #11
	mov	r0, r6
	bl	BsShow
	ldr	r2, .L869+4
	and	r3, r0, #127
	mov	r0, r6
	sub	r3, r3, #24
	add	r5, r5, r3, lsl #3
	ldr	r4, [r5, #352]
	ldr	r1, [r5, #356]
	bl	MP2_u_v
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L867:
	mov	r0, r6
	ldr	r2, .L869+4
	bl	MP2_u_v
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L868:
	mov	r0, r6
	ldr	r2, .L869+4
	bl	MP2_u_v
	rsb	r0, r0, #9
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L870:
	.align	2
.L869:
	.word	.LANCHOR0
	.word	.LC66
	UNWIND(.fnend)
	.size	MP2_MbAddrInc, .-MP2_MbAddrInc
	.align	2
	.global	MP2_InitMb
	.type	MP2_InitMb, %function
MP2_InitMb:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, #0
	mov	r6, r0
	ldr	r4, [r0, #52]
	b	.L872
.L876:
	cmp	r0, #15
	beq	.L873
	cmp	r0, #8
	add	r5, r5, #33
	bne	.L885
.L873:
	ldr	r2, .L888
	mov	r1, #11
	mov	r0, r4
	bl	MP2_u_v
	mov	r0, r4
	bl	BsPos
	ldr	r3, [r4, #16]
	cmp	r0, r3, asl #3
	bge	.L886
.L872:
	mov	r1, #11
	mov	r0, r4
	bl	BsShow
	cmp	r0, #23
	bls	.L876
	mov	r0, r4
	bl	MP2_MbAddrInc
	ldr	r4, [r6, #16]
	cmp	r4, #0
	beq	.L877
	ldr	r3, [r6, #28]
	add	r2, r5, r0
	cmp	r3, #0
	addne	r2, r2, r3
	ldr	r3, [r6, #12]
	subeq	r2, r2, #1
	str	r2, [r6, #40]
	sub	r3, r3, #1
	cmp	r2, r3
	bhi	.L887
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L886:
	ldr	r1, .L888+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L885:
	ldr	r1, .L888+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L877:
	mov	r2, r4
	ldr	r1, .L888+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L887:
	ldr	r1, .L888+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L889:
	.align	2
.L888:
	.word	.LC68
	.word	.LC69
	.word	.LC67
	.word	.LC71
	.word	.LC70
	UNWIND(.fnend)
	.size	MP2_InitMb, .-MP2_InitMb
	.align	2
	.global	MP2_GetFirstMbInSlice
	.type	MP2_GetFirstMbInSlice, %function
MP2_GetFirstMbInSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	MP2_DecSliceHeader
	mov	r0, r4
	bl	MP2_InitMb
	mov	r3, #0
	str	r3, [r4, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_GetFirstMbInSlice, .-MP2_GetFirstMbInSlice
	.align	2
	.global	MP2_DecSlice
	.type	MP2_DecSlice, %function
MP2_DecSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #86016
	add	ip, r0, #87040
	mov	r5, r0
	add	r6, ip, #504
	ldr	r3, [r4, #1320]
	uxtb	r1, r1
	ldr	r2, [r4, #2680]
	add	ip, ip, #560
	ldr	r0, [r4, #1304]
	mov	r7, #0
	str	r3, [r4, #1576]
	ldr	r3, [r4, #1376]
	str	r0, [r4, #1564]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #1528]
	ldr	r3, [r2, #68]
	str	r3, [r4, #1532]
	ldr	r3, [r2, #64]
	str	r3, [r4, #1536]
	ldr	r0, [r2, #60]
	ldr	r3, [r2, #56]
	add	r0, r0, #15
	add	r3, r3, #15
	mov	r0, r0, lsr #4
	mov	r3, r3, lsr #4
	mul	r3, r3, r0
	mov	r0, r6
	str	r3, [r4, #1540]
	ldrb	r2, [r2, #17]	@ zero_extendqisi2
	str	r1, [r4, #1548]
	cmp	r2, #3
	str	ip, [r4, #1580]
	movne	r3, r3, lsr #1
	strne	r3, [r4, #1540]
	bl	MP2_DecSliceHeader
	mov	r0, r6
	bl	MP2_InitMb
	str	r7, [r4, #1544]
	cmp	r0, #1
	mov	r6, r0
	beq	.L893
	ldr	r1, .L907
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L907+4
	ldr	r5, [r3]
	cmp	r5, r7
	beq	.L896
.L906:
	ldr	r0, [r4, #3040]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #127
	blx	r5
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L893:
	mov	r0, r5
	bl	MP2_WriteSliceInfo
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r6
	ldr	r1, .L907+8
	bl	dprint_vfmw
	ldr	r3, .L907+4
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L906
.L896:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L908:
	.align	2
.L907:
	.word	.LC72
	.word	g_event_report
	.word	.LC73
	UNWIND(.fnend)
	.size	MP2_DecSlice, .-MP2_DecSlice
	.align	2
	.global	MP2_GetHDR
	.type	MP2_GetHDR, %function
MP2_GetHDR:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r6, r0, #87040
	add	r4, r0, #86016
	add	r6, r6, #560
	mov	r1, #32
	mov	r7, r0
	mov	r8, #0
	mov	r0, r6
	strb	r8, [r4, #3056]
	ldr	r9, [r4, #2680]
	ldr	r10, [r4, #2684]
	bl	BsShow
	ldr	r3, [r4, #1340]
	str	r3, [fp, #-80]
	mov	r5, r0
	mov	r0, r6
	bl	BsPos
	mov	r1, #32
	str	r0, [r4, #1400]
	mov	r0, r6
	bl	BsSkip
	movw	r3, #439
	cmp	r5, r3
	beq	.L977
	movw	r3, #435
	cmp	r5, r3
	cmpne	r5, #440
	bne	.L916
.L912:
	ldr	r3, [r4, #1396]
	cmp	r3, #1
	beq	.L978
.L913:
	movw	r3, #435
	cmp	r5, r3
	beq	.L918
.L981:
	cmp	r5, #436
	bcc	.L979
	movw	r3, #437
	cmp	r5, r3
	beq	.L922
	cmp	r5, #436
	bls	.L973
	movw	r3, #439
	cmp	r5, r3
	beq	.L973
	cmp	r5, #440
	bne	.L917
	ldr	r3, [r4, #1392]
	mov	r0, r6
	ldr	r5, [r4, #1288]
	add	r5, r3, r5
	bl	BsPos
	ldr	r1, .L985
	add	r2, r5, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r7
	bl	group_of_pictures_header
	mov	r0, r6
	bl	BsResidBits
	cmp	r0, #0
	blt	.L980
.L973:
	mov	r6, #0
.L915:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L916:
	cmp	r5, #256
	beq	.L912
	movw	r3, #435
	cmp	r5, r3
	bne	.L981
.L918:
	ldr	r3, [r4, #1392]
	mov	r0, r6
	ldr	r5, [r4, #1288]
	add	r5, r3, r5
	bl	BsPos
	ldr	r1, .L985+4
	add	r2, r5, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r7
	bl	sequence_header
	mov	r0, r6
	bl	BsResidBits
	cmp	r0, #0
	blt	.L982
	ldr	r6, [r4, #1340]
	ands	r6, r6, #7
	bne	.L927
	mov	r3, #1
	mov	r0, r10
	strb	r3, [r9]
	mov	r1, r9
	mov	r2, #196
	bl	memcpy
	ldr	r3, [r4, #1344]
	add	r3, r3, #1
	str	r3, [r4, #1344]
	b	.L915
.L979:
	cmp	r5, #256
	beq	.L920
	bcc	.L917
	cmp	r5, #432
	bls	.L917
	ldr	r3, [r4, #1392]
	mov	r0, r6
	ldr	r5, [r4, #1288]
	add	r5, r3, r5
	bl	BsPos
	ldr	r1, .L985+8
	add	r2, r5, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r7
	bl	MP2_GetUsrData
	subs	r6, r0, #0
	bne	.L933
	add	r1, r7, #87040
	ldr	r0, [r4, #3040]
	add	r1, r1, #268
	bl	MP2_ClearCurPacket
	ldr	r3, .L985+12
	ldr	r5, [r3]
	cmp	r5, #0
	mvneq	r6, #0
	beq	.L915
	mov	r3, r6
	mov	r2, r6
	ldr	r0, [r4, #3040]
	mov	r1, #113
	blx	r5
	mvn	r6, #0
	b	.L915
.L920:
	ldr	r3, [r4, #1392]
	mov	r0, r6
	ldr	r5, [r4, #1288]
	add	r5, r3, r5
	bl	BsPos
	ldr	r1, .L985+16
	add	r2, r5, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r7
	bl	picture_header
	mov	r0, r6
	bl	BsResidBits
	cmp	r0, #0
	bge	.L973
	ldr	r3, .L985+12
	ldr	r2, [fp, #-80]
	ldr	r5, [r3]
	str	r2, [r4, #1340]
	cmp	r5, #0
	beq	.L932
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #3040]
	blx	r5
.L932:
	add	r1, r7, #87040
	ldr	r0, [r4, #3040]
	add	r1, r1, #268
	mvn	r6, #0
	bl	MP2_ClearCurPacket
	mov	r2, #256
	ldr	r1, .L985+20
	mov	r0, #1
	bl	dprint_vfmw
	b	.L915
.L978:
	ldr	r2, [r4, #1340]
	tst	r2, #4194304
	beq	.L913
	orr	r2, r2, #8388608
	strb	r3, [r4, #3056]
	str	r2, [r4, #1340]
	mov	r0, r7
	mov	r2, #0
	str	r2, [r4, #1396]
	mov	r6, r3
	bl	MP2_ProtocolPPSCheck
	b	.L915
.L977:
	ldr	r3, .L985+24
	mov	r2, #32
	mov	r1, r6
	sub	r0, fp, #76
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #32
	str	r0, [fp, #-84]
	sub	r0, fp, #76
	bl	BsGet
	ldr	r3, [fp, #-84]
	movw	r1, #20036
	movw	r2, #20553
	movt	r1, 17221
	movt	r2, 18515
	cmp	r0, r1
	cmpeq	r3, r2
	bne	.L912
	ldr	r6, [r4, #1396]
	cmp	r6, #1
	beq	.L983
.L914:
	mov	r3, #1
	mov	r6, #0
	strb	r3, [r4, #3058]
	b	.L915
.L917:
	sub	r3, r5, #256
	sub	r3, r3, #1
	cmp	r3, #174
	bhi	.L935
	ldr	r8, [r4, #1336]
	cmp	r8, #0
	beq	.L936
.L938:
	ldr	r3, [r4, #1340]
	tst	r3, #589824
	beq	.L973
	orr	r3, r3, #4194304
	mov	r0, r7
	str	r3, [r4, #1340]
	mov	r7, #1
	mov	r1, r5
	str	r7, [r4, #1396]
	bl	MP2_DecSlice
	cmp	r0, r7
	mov	r6, r0
	beq	.L915
	mov	r2, r5
	mov	r0, r7
	ldr	r1, .L985+28
	mov	r6, #0
	bl	dprint_vfmw
	b	.L915
.L922:
	ldr	r3, [r4, #1392]
	mov	r0, r6
	ldr	r5, [r4, #1288]
	add	r5, r3, r5
	bl	BsPos
	ldr	r1, .L985+32
	add	r2, r5, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r7
	bl	extension
	mov	r0, r6
	bl	BsResidBits
	cmp	r0, #0
	bge	.L973
	ldr	r3, .L985+12
	ldr	r2, [fp, #-80]
	ldr	r5, [r3]
	str	r2, [r4, #1340]
	cmp	r5, #0
	beq	.L934
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #3040]
	blx	r5
.L934:
	add	r1, r7, #87040
	ldr	r0, [r4, #3040]
	add	r1, r1, #268
	mvn	r6, #0
	bl	MP2_ClearCurPacket
	b	.L915
.L927:
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L984
.L935:
	ldr	r3, .L985+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L973
.L972:
	mov	r3, #0
	ldr	r0, [r4, #3040]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L973
.L933:
	ldr	r1, .L985+36
	mov	r0, #1
	bl	dprint_vfmw
	b	.L915
.L983:
	ldr	r3, [r4, #1340]
	tst	r3, #4194304
	beq	.L914
	orr	r3, r3, #8388608
	strb	r6, [r4, #3058]
	str	r3, [r4, #1340]
	mov	r0, r7
	strb	r6, [r4, #3056]
	str	r8, [r4, #1396]
	bl	MP2_ProtocolPPSCheck
	b	.L915
.L936:
	mov	r0, r7
	bl	MP2_GetSequenceInfo
	ldr	r6, [r4, #1388]
	cmp	r6, #0
	beq	.L915
	ldrb	r3, [r4, #3057]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r6, r8
	beq	.L915
	ldr	r6, [r4, #1336]
	cmp	r6, #0
	bne	.L938
	b	.L915
.L984:
	mov	r2, #196
	mov	r1, r10
	mov	r0, r9
	bl	memcpy
	ldr	r2, .L985+12
	ldr	r3, [r4, #1340]
	ldr	r5, [r2]
	bic	r3, r3, #7
	str	r3, [r4, #1340]
	cmp	r5, #0
	bne	.L972
	b	.L973
.L980:
	ldr	r3, .L985+12
	ldr	r2, [fp, #-80]
	ldr	r5, [r3]
	str	r2, [r4, #1340]
	cmp	r5, #0
	beq	.L931
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #3040]
	blx	r5
.L931:
	add	r1, r7, #87040
	ldr	r0, [r4, #3040]
	add	r1, r1, #268
	mvn	r6, #0
	bl	MP2_ClearCurPacket
	mov	r2, #440
	ldr	r1, .L985+40
	mov	r0, #1
	bl	dprint_vfmw
	b	.L915
.L982:
	ldr	r3, .L985+12
	ldr	r2, [fp, #-80]
	ldr	r5, [r3]
	str	r2, [r4, #1340]
	cmp	r5, #0
	beq	.L926
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #3040]
	blx	r5
.L926:
	add	r1, r7, #87040
	ldr	r0, [r4, #3040]
	add	r1, r1, #268
	mvn	r6, #0
	bl	MP2_ClearCurPacket
	movw	r2, #435
	ldr	r1, .L985+44
	mov	r0, #1
	bl	dprint_vfmw
	b	.L915
.L986:
	.align	2
.L985:
	.word	.LC76
	.word	.LC74
	.word	.LC80
	.word	g_event_report
	.word	.LC78
	.word	.LC79
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC83
	.word	.LC82
	.word	.LC81
	.word	.LC77
	.word	.LC75
	UNWIND(.fnend)
	.size	MP2_GetHDR, .-MP2_GetHDR
	.align	2
	.global	MPEG2DEC_Decode
	.type	MPEG2DEC_Decode, %function
MPEG2DEC_Decode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	beq	.L1022
	cmp	r1, #0
	beq	.L1023
	add	r5, r4, #88064
	ldr	r3, .L1029
	add	r5, r5, #80
	add	r6, r4, #86016
	add	r7, r4, #45312
	mov	r2, #160
	ldr	r3, [r3, #52]
	mov	r0, r5
	blx	r3
	mov	r1, r5
	ldr	r2, [r6, #3040]
	mov	r0, r7
	bl	MP2_ReceivePacket
	cmp	r0, #1
	beq	.L991
	ldr	r1, .L1029+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r5, #0
.L989:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L991:
	add	r0, r4, #87040
	ldr	r2, [r6, #1304]
	add	r0, r0, #560
	ldr	r1, [r6, #1320]
	bl	BsInit
	ldr	r3, [r4]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L1024
.L992:
	ldr	r3, [r6, #1340]
	str	r3, [r6, #1524]
.L993:
	mov	r0, r4
	bl	MP2_GetHDR
	add	r0, r0, #1
	cmp	r0, #1
	bls	.L1025
	mov	r0, r4
	bl	MP2_DecodingDecide
	subs	r5, r0, #0
	beq	.L1026
	cmn	r5, #1
	beq	.L1021
	mov	r0, r4
	bl	MP2_GetPictureInfo
	subs	r5, r0, #0
	bne	.L999
	add	r1, r7, #41984
	ldr	r0, [r6, #3040]
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r3, .L1029+8
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1000
	ldr	r0, [r6, #3040]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r4
.L1000:
	ldr	r1, .L1029+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r5, #0
	b	.L989
.L1025:
	ldr	r3, [r4]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L1027
.L995:
	ldrb	r3, [r6, #3057]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1021
	add	r1, r7, #41984
	ldr	r0, [r6, #3040]
	add	r1, r1, #12
	mov	r5, #0
	bl	MP2_ClearCurPacket
	b	.L989
.L1026:
	add	r1, r7, #41984
	ldr	r0, [r6, #3040]
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r3, .L1029+8
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L998
	ldr	r0, [r6, #3040]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r4
.L998:
	ldr	r1, .L1029+16
	mov	r0, #22
	bl	dprint_vfmw
.L1021:
	mov	r5, #0
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1024:
	ldr	r3, [r3, #920]
	cmp	r3, #1
	ldreq	r3, [r6, #1524]
	streq	r3, [r6, #1340]
	bne	.L992
	b	.L993
.L999:
	mov	r0, r4
	bl	MP2_DecNewPic
	subs	r5, r0, #0
	beq	.L1028
	ldr	r5, [r6, #1288]
	ldr	r3, [r6, #1392]
	ldr	r2, [r6, #1304]
	mov	r5, r5, asl #3
	add	r3, r3, r2
	str	r3, [r6, #1392]
	b	.L989
.L1027:
	ldr	r3, [r3, #920]
	cmp	r3, #0
	beq	.L995
	b	.L1021
.L1028:
	mov	r2, #1
	ldr	r1, [r6, #1424]
	ldr	r0, [r6, #3040]
	bl	FSP_ClearLogicFs
	add	r1, r7, #41984
	add	r1, r1, #12
	ldr	r0, [r6, #3040]
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r3, .L1029+8
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1002
	ldr	r0, [r6, #3040]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r4
.L1002:
	ldr	r1, .L1029+20
	mov	r0, #1
	bl	dprint_vfmw
	b	.L989
.L1023:
	mov	r0, r1
	ldr	r3, .L1029+24
	movw	r2, #2977
	ldr	r1, .L1029+28
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L989
.L1022:
	ldr	r3, .L1029+32
	mov	r2, #2976
	ldr	r1, .L1029+28
	mvn	r5, #0
	bl	dprint_vfmw
	b	.L989
.L1030:
	.align	2
.L1029:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC85
	.word	g_event_report
	.word	.LC87
	.word	.LC86
	.word	.LC88
	.word	.LC84
	.word	.LC43
	.word	.LC42
	UNWIND(.fnend)
	.size	MPEG2DEC_Decode, .-MPEG2DEC_Decode
	.align	2
	.global	MP2_GetPacketState
	.type	MP2_GetPacketState, %function
MP2_GetPacketState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r3, r0, #0
	beq	.L1035
	add	r3, r3, #86016
	ldrb	r3, [r3, #3056]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r0, #0
	moveq	r0, #2
	ldmfd	sp, {fp, sp, pc}
.L1035:
	ldr	r3, .L1036
	movw	r2, #3828
	ldr	r1, .L1036+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1037:
	.align	2
.L1036:
	.word	.LC42
	.word	.LC43
	UNWIND(.fnend)
	.size	MP2_GetPacketState, .-MP2_GetPacketState
	.global	g_tmpusd
	.global	zigzag
	.global	default_intra_quantizer_matrix
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__FUNCTION__.13721, %object
	.size	__FUNCTION__.13721, 19
__FUNCTION__.13721:
	.ascii	"MP2_DecodingDecide\000"
	.space	1
.LC0:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	10
	.word	12
	.word	14
	.word	16
	.word	18
	.word	20
	.word	22
	.word	24
	.word	28
	.word	32
	.word	36
	.word	40
	.word	44
	.word	48
	.word	52
	.word	56
	.word	64
	.word	72
	.word	80
	.word	88
	.word	96
	.word	104
	.word	112
	.type	CSWTCH.50, %object
	.size	CSWTCH.50, 12
CSWTCH.50:
	.word	5
	.word	1
	.word	2
	.type	frame_rate_Table, %object
	.size	frame_rate_Table, 64
frame_rate_Table:
	.word	0
	.word	23976
	.word	24000
	.word	25000
	.word	29970
	.word	30000
	.word	50000
	.word	59940
	.word	60000
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.type	tab_for_first_4bit, %object
	.size	tab_for_first_4bit, 128
tab_for_first_4bit:
	.word	8
	.word	4
	.word	9
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	3
	.word	2
	.word	3
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.type	tab_for_last_7bit, %object
	.size	tab_for_last_7bit, 832
tab_for_last_7bit:
	.word	33
	.word	11
	.word	32
	.word	11
	.word	31
	.word	11
	.word	30
	.word	11
	.word	29
	.word	11
	.word	28
	.word	11
	.word	27
	.word	11
	.word	26
	.word	11
	.word	25
	.word	11
	.word	24
	.word	11
	.word	23
	.word	11
	.word	22
	.word	11
	.word	21
	.word	10
	.word	21
	.word	10
	.word	20
	.word	10
	.word	20
	.word	10
	.word	19
	.word	10
	.word	19
	.word	10
	.word	18
	.word	10
	.word	18
	.word	10
	.word	17
	.word	10
	.word	17
	.word	10
	.word	16
	.word	10
	.word	16
	.word	10
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	default_intra_quantizer_matrix, %object
	.size	default_intra_quantizer_matrix, 64
default_intra_quantizer_matrix:
	.byte	8
	.byte	16
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	16
	.byte	16
	.byte	22
	.byte	24
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	34
	.byte	38
	.byte	22
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	40
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	58
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	27
	.byte	29
	.byte	35
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	83
	.type	zigzag, %object
	.size	zigzag, 64
zigzag:
	.byte	0
	.byte	1
	.byte	8
	.byte	16
	.byte	9
	.byte	2
	.byte	3
	.byte	10
	.byte	17
	.byte	24
	.byte	32
	.byte	25
	.byte	18
	.byte	11
	.byte	4
	.byte	5
	.byte	12
	.byte	19
	.byte	26
	.byte	33
	.byte	40
	.byte	48
	.byte	41
	.byte	34
	.byte	27
	.byte	20
	.byte	13
	.byte	6
	.byte	7
	.byte	14
	.byte	21
	.byte	28
	.byte	35
	.byte	42
	.byte	49
	.byte	56
	.byte	57
	.byte	50
	.byte	43
	.byte	36
	.byte	29
	.byte	22
	.byte	15
	.byte	23
	.byte	30
	.byte	37
	.byte	44
	.byte	51
	.byte	58
	.byte	59
	.byte	52
	.byte	45
	.byte	38
	.byte	31
	.byte	39
	.byte	46
	.byte	53
	.byte	60
	.byte	61
	.byte	54
	.byte	47
	.byte	55
	.byte	62
	.byte	63
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC2:
	ASCII(.ascii	"mp2 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"user set decode channel max resolution is (w=%d,h=%" )
	ASCII(.ascii	"d), this stream (w=%d,h=%d) can NOT be decoded!\012" )
	ASCII(.ascii	"\000" )
.LC4:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"ERROR: frm %d, integrality: %#x\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"ERROR: frm %d, No Img buffer is allocated\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"----------------- mp2 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"frm %d pic type %d struct is %d total pos %#x\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"NOTE: Drop non-I, cur is B\012\000" )
.LC11:
	ASCII(.ascii	"NOTE: Drop non-I, cur is P\012\000" )
.LC12:
	ASCII(.ascii	"NOTE: Drop non-I\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"NOTE: Drop B\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"%s %d pFwdImg = NULL,  pBwdImg = NULL!!\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"fuction return value is null,%s %d !!\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"dec P frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC17:
	ASCII(.ascii	"dec B frame, bwd ref err(%d) > ref_thr(%d)\012\000" )
.LC18:
	ASCII(.ascii	"dec B frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC19:
	ASCII(.ascii	"Protocol %d\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"seq size change, call vpss to release all frames.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC21:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"new seq size %dx%d\012\000" )
.LC23:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"ERROR: frm %d, lost one field\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"ERROR: frm %d, lost one field flg = %d, last_struct" )
	ASCII(.ascii	" = %d\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"Fatal Error: frm%d, get image buffer failed\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"dec_pts: %lld Usertag: %lld\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"++++++++++ ref %d\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"line: %d(pCur, pFwd, pBwd)(%p, %p, %p)\012\000" )
.LC34:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"dec addr: cur,cur2d,fwd,bwd,pmv = %p,%p,%p,%p,%p\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC36:
	ASCII(.ascii	"\012mpeg2 copy last 3 bytes of the first packet!\012" )
	ASCII(.ascii	"\012\000" )
.LC37:
	ASCII(.ascii	"pMp2CodecInfo->pUsrDatArray[%d] is null\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"ERROR: unsupported profile %d\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"ERROR: unsupported level %d\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"pCtx or pstExtraData is NULL! \012\000" )
.LC41:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC42:
	ASCII(.ascii	"pCtx is NULL!\000" )
	.space	2
.LC43:
	ASCII(.ascii	"mpeg2.c,L%d: %s\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"Decoding quits at frm %d\012\000" )
	.space	2
.LC45:
	ASCII(.ascii	"img_id out of range\000" )
.LC46:
	ASCII(.ascii	"pMp2Packet is NULL!\000" )
.LC47:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
.LC48:
	ASCII(.ascii	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\012\000" )
.LC49:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"pImg is null, pCurImg %#x pBwdImg %#x pFwdImg %#x\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC51:
	ASCII(.ascii	"DEBUG: DEC over\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"ERROR,pBwdImg == NULL || pToQueImg == NULL\012\000" )
.LC54:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC55:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"%-40s%20d\012\000" )
	.space	1
.LC57:
	ASCII(.ascii	"slice_vertical_position\000" )
.LC58:
	ASCII(.ascii	"quantiser_scale_code\000" )
	.space	3
.LC59:
	ASCII(.ascii	"extra_bit_slice\000" )
.LC60:
	ASCII(.ascii	"intra_slice_flag\000" )
	.space	3
.LC61:
	ASCII(.ascii	"intra_slice\000" )
.LC62:
	ASCII(.ascii	"reserved_bits\000" )
	.space	2
.LC63:
	ASCII(.ascii	"extra_infrmation_slice\000" )
	.space	1
.LC64:
	ASCII(.ascii	"Slice num = %d >= %d\012\000" )
	.space	2
.LC65:
	ASCII(.ascii	"seg info is wrong! IsLastSeg[0] = %d, IsLastSeg[1] " )
	ASCII(.ascii	"= %d\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"macroblock_address_increment\000" )
	.space	3
.LC67:
	ASCII(.ascii	"macroblock_escape ERROR\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"macroblock_escape\000" )
	.space	2
.LC69:
	ASCII(.ascii	"macroblock_escape ERROR, overflow\012\000" )
	.space	1
.LC70:
	ASCII(.ascii	"SlcStartMbNum = %d > PicEndMum = %d\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"FirstMbInSliceFlag = %d\012\000" )
	.space	3
.LC72:
	ASCII(.ascii	"MP2_GetFirstMbInSlice Failed!\012\000" )
	.space	1
.LC73:
	ASCII(.ascii	"MP2_WriteSliceInfo Failed!\012\000" )
.LC74:
	ASCII(.ascii	"found sh %#x\012\000" )
	.space	2
.LC75:
	ASCII(.ascii	"SEQUENCE_HEADER_CODE Bitstream is not enough!\012\000" )
	.space	1
.LC76:
	ASCII(.ascii	"found gh %#x\012\000" )
	.space	2
.LC77:
	ASCII(.ascii	"GROUP_START_CODE Bitstream is not enough!\012\000" )
	.space	1
.LC78:
	ASCII(.ascii	"found ph %#x\012\000" )
	.space	2
.LC79:
	ASCII(.ascii	"PICTURE_START_CODE Bitstream is not enough!\012\000" )
	.space	3
.LC80:
	ASCII(.ascii	"found ud %#x\012\000" )
	.space	2
.LC81:
	ASCII(.ascii	"cann't get ud pointer\012\000" )
	.space	1
.LC82:
	ASCII(.ascii	"found ext %#x\012\000" )
	.space	1
.LC83:
	ASCII(.ascii	"MP2_DecSlice is wrong!\012\000" )
.LC84:
	ASCII(.ascii	"pPacket is NULL!\000" )
	.space	3
.LC85:
	ASCII(.ascii	"line %d, MP2_ReceivePacket receive packet failed!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC86:
	ASCII(.ascii	"MP2 Decode Decide is wrong!\012\000" )
	.space	3
.LC87:
	ASCII(.ascii	"MP2 get picture info is wrong!\012\000" )
.LC88:
	ASCII(.ascii	"MP2 dec new pic failed!\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	g_tmpusd, %object
	.size	g_tmpusd, 1024
g_tmpusd:
	.space	1024
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
