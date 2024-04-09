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
	.file	"vdm_hal.c"
	.text
	.align	2
	.type	VDMHAL_CalcPmvSlotLen.isra.0, %function
VDMHAL_CalcPmvSlotLen.isra.0:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	lr, .L10
	ldr	ip, [r1]
	ldr	r3, [r2]
	ldrb	r4, [lr]	@ zero_extendqisi2
	cmp	ip, #45
	cmple	r3, #36
	movle	lr, #64
	movgt	lr, #32
	cmp	r4, #1
	moveq	lr, #64
	cmp	r0, #16
	moveq	lr, r0
	beq	.L4
	cmp	r0, #17
	beq	.L9
.L4:
	mul	r0, ip, lr
	mul	r0, r3, r0
	add	r0, r0, #143
	bic	r0, r0, #127
	ldmfd	sp, {r4, fp, sp, pc}
.L9:
	mov	r0, #144
	mov	ip, #256
	mov	r3, r0
	str	ip, [r1]
	mov	lr, #64
	str	r0, [r2]
	ldr	ip, [r1]
	b	.L4
.L11:
	.align	2
.L10:
	.word	g_not_direct_8x8_inference_flag
	UNWIND(.fnend)
	.size	VDMHAL_CalcPmvSlotLen.isra.0, .-VDMHAL_CalcPmvSlotLen.isra.0
	.align	2
	.type	VDMHAL_V5R6C1_CfgRpReg.isra.9, %function
VDMHAL_V5R6C1_CfgRpReg.isra.9:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	subs	r7, r2, #0
	mov	r4, r0
	mov	r5, r3
	mov	r0, #0
	str	r0, [fp, #-32]
	bgt	.L46
	ldr	r3, [r4]
	cmp	r3, #0
	beq	.L47
.L15:
	ldr	r4, .L49
	ldr	r3, [r1]
	ldrb	r2, [r4]	@ zero_extendqisi2
	bic	r3, r3, #15
	str	r3, [fp, #-32]
	cmp	r2, #1
	bne	.L48
	movw	r1, #1228
	ldr	r2, .L49+4
	mul	r1, r1, r7
	ldr	r1, [r2, r1]
	str	r3, [r1, #16]
.L18:
	movw	r3, #1228
	movw	r1, #53763
	mul	r3, r3, r7
	movt	r1, 8192
	ldr	r3, [r2, r3]
	str	r1, [r3, #12]
.L20:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r7
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #60]
.L22:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r7
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #64]
.L24:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r7
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #68]
.L26:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r7
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #72]
.L28:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r7
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #76]
.L30:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r7
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #80]
.L32:
	movw	r3, #1228
	movw	r1, #3075
	mul	r7, r3, r7
	mov	r0, #0
	movt	r1, 48
	ldr	r3, [r2, r7]
	str	r1, [r3, #84]
.L35:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L48:
	mov	r2, #16
	mov	r1, #2
	mov	r0, r5
	bl	VDH_Record_RegData
	ldrb	r2, [r4]	@ zero_extendqisi2
	movw	r3, #53763
	cmp	r2, #1
	movt	r3, 8192
	str	r3, [fp, #-32]
	ldreq	r2, .L49+4
	beq	.L18
	mov	r2, #12
	mov	r1, #2
	mov	r0, r5
	movw	r6, #3075
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	movt	r6, 48
	str	r6, [fp, #-32]
	cmp	r3, #1
	ldreq	r2, .L49+4
	beq	.L20
	mov	r3, r6
	mov	r2, #60
	mov	r1, #2
	mov	r0, r5
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L49+4
	beq	.L22
	mov	r3, r6
	mov	r2, #64
	mov	r1, #2
	mov	r0, r5
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L49+4
	beq	.L24
	mov	r3, r6
	mov	r2, #68
	mov	r1, #2
	mov	r0, r5
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L49+4
	beq	.L26
	mov	r3, r6
	mov	r2, #72
	mov	r1, #2
	mov	r0, r5
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L49+4
	beq	.L28
	mov	r3, r6
	mov	r2, #76
	mov	r1, #2
	mov	r0, r5
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L49+4
	beq	.L30
	mov	r3, r6
	mov	r2, #80
	mov	r1, #2
	mov	r0, r5
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L49+4
	beq	.L32
	mov	r0, r5
	mov	r3, r6
	mov	r2, #84
	mov	r1, #2
	bl	VDH_Record_RegData
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L47:
	mov	r0, #0
	str	r1, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L16
	str	r3, [r4]
	ldr	r1, [fp, #-40]
	b	.L15
.L46:
	str	r0, [sp]
	mov	r3, r7
	ldr	r2, .L49+8
	ldr	r1, .L49+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L35
.L16:
	ldr	r1, .L49+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L35
.L50:
	.align	2
.L49:
	.word	g_HalDisable
	.word	g_HwMem
	.word	.LANCHOR0
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CfgRpReg.isra.9, .-VDMHAL_V5R6C1_CfgRpReg.isra.9
	.align	2
	.global	VDMHAL_V5R6C1_GetHalMemSize
	.type	VDMHAL_V5R6C1_GetHalMemSize, %function
VDMHAL_V5R6C1_GetHalMemSize:
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
	mov	r0, #6291456
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetHalMemSize, .-VDMHAL_V5R6C1_GetHalMemSize
	.align	2
	.global	VDMHAL_V5R6C1_OpenHAL
	.type	VDMHAL_V5R6C1_OpenHAL, %function
VDMHAL_V5R6C1_OpenHAL:
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
	subs	r3, r0, #0
	beq	.L62
	ldmia	r3, {r6, r8}
	ldr	r7, [r3, #8]
	cmp	r6, #0
	beq	.L63
	cmp	r8, #6291456
	blt	.L64
	cmp	r7, #0
	bgt	.L65
	ldr	r4, .L67
	mov	r2, #268
	ldr	r10, .L67+4
	mov	r1, #0
	ldr	r5, .L67+8
	mla	r0, r2, r7, r4
	ldr	r3, [r10, #48]
	blx	r3
	movw	r2, #1228
	mul	r9, r2, r7
	mov	r1, #4
	str	r1, [r4]
	mov	r1, #0
	ldr	r3, [r10, #48]
	add	r4, r5, r9
	mov	r0, r4
	blx	r3
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r1, .L67+12
	mov	r3, r0
	mov	r2, r0
	str	r3, [r5, r9]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #53248
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r1, .L67+16
	mov	r3, r0
	mov	r2, r0
	str	r3, [r4, #8]
	mov	r0, #22
	bl	dprint_vfmw
	add	r3, r6, #1020
	add	r3, r3, #3
	add	r2, r9, #36
	bic	r3, r3, #1020
	add	r0, r9, #876
	bic	r3, r3, #3
	add	r2, r5, r2
	add	r0, r5, r0
	add	ip, r8, r6
	mov	r1, r3
	rsb	ip, r3, ip
	str	r3, [r4, #16]
	str	ip, [r4, #20]
	mov	ip, #1024
	str	ip, [r4, #24]
.L58:
	str	r1, [r2, #4]!
	cmp	r2, r0
	add	r1, r1, #1280
	bne	.L58
	movw	r2, #1228
	add	r0, r3, #266240
	mla	r5, r2, r7, r5
	add	lr, r3, #274432
	add	r3, r0, #41728
	add	r0, r0, #3072
	add	r3, r3, #255
	mov	r9, #210
	bic	r3, r3, #32512
	bic	r3, r3, #255
	add	r1, r3, #4390912
	add	ip, r3, #1769472
	add	r7, ip, #5248
	add	r2, r1, #37888
	str	r0, [r5, #1088]
	add	r0, r3, #1081344
	cmp	r7, r2
	rsbcs	r2, r6, r7
	rsbcc	r2, r6, r2
	add	r0, r0, #12288
	str	lr, [r5, #1108]
	add	lr, r3, #2129920
	str	r0, [r5, #1148]
	add	r0, r3, #3178496
	add	lr, lr, #12288
	add	r0, r0, #12288
	str	lr, [r5, #1152]
	cmp	r8, r2
	add	lr, r3, #4194304
	str	r0, [r5, #1160]
	add	r0, r3, #4325376
	add	r6, r3, #45056
	add	lr, lr, #45056
	str	r3, [r5, #1156]
	str	r3, [r5, #1092]
	add	ip, ip, #2048
	str	r3, [r5, #1096]
	str	r3, [r5, #1100]
	str	r6, [r5, #1144]
	add	r6, r0, #47104
	str	lr, [r5, #1192]
	add	lr, r0, #50176
	add	r0, r3, #589824
	add	r3, r3, #1179648
	add	r3, r3, #2048
	str	lr, [r5, #1180]
	str	r0, [r5, #1104]
	add	lr, r1, #33792
	str	r0, [r5, #1112]
	add	r1, r1, #1024
	str	lr, [r5, #1184]
	add	lr, r0, #2048
	str	r9, [r5, #1064]
	mov	r0, #0
	str	r7, [r5, #1136]
	str	r6, [r5, #1176]
	str	r1, [r5, #1204]
	str	lr, [r5, #1116]
	str	r1, [r5, #1188]
	str	r3, [r5, #1120]
	str	r3, [r5, #1124]
	str	ip, [r5, #1128]
	str	ip, [r5, #1132]
	str	r0, [r5, #1168]
	str	r0, [r5, #1140]
	bcc	.L59
	mov	r0, r4
	bl	H264HAL_V5R6C1_InitHal
	mov	r5, r0
	mov	r0, r4
	bl	HEVCHAL_V5R6C1_InitHal
	cmp	r0, #0
	beq	.L66
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L66:
	adds	r0, r5, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L65:
	ldr	r1, .L67+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L59:
	mov	r3, r8
	ldr	r1, .L67+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L63:
	mov	r0, r6
	ldr	r3, .L67+28
	ldr	r2, .L67+32
	ldr	r1, .L67+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L64:
	ldr	r3, .L67+40
	mov	r0, #0
	ldr	r2, .L67+32
	ldr	r1, .L67+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L62:
	ldr	r3, .L67+44
	ldr	r2, .L67+32
	ldr	r1, .L67+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L68:
	.align	2
.L67:
	.word	g_VdmExtParam
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LC7
	.word	.LC8
	.word	.LC6
	.word	.LC9
	.word	.LC4
	.word	.LANCHOR0+24
	.word	.LC3
	.word	.LC5
	.word	.LC2
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_OpenHAL, .-VDMHAL_V5R6C1_OpenHAL
	.align	2
	.global	VDMHAL_V5R6C1_CloseHAL
	.type	VDMHAL_V5R6C1_CloseHAL, %function
VDMHAL_V5R6C1_CloseHAL:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CloseHAL, .-VDMHAL_V5R6C1_CloseHAL
	.align	2
	.global	VDMHAL_V5R6C1_CalcFsSize
	.type	VDMHAL_V5R6C1_CalcFsSize, %function
VDMHAL_V5R6C1_CalcFsSize:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 24
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
	sub	ip, r1, #32
	mov	r10, r1
	movw	r1, #8160
	cmp	ip, r1
	mov	r7, r0
	mov	r8, r2
	str	r3, [fp, #-56]
	bhi	.L71
	sub	r3, r2, #32
	mov	r4, r2
	cmp	r3, r1
	bhi	.L71
	add	r6, r2, #15
	sub	r2, fp, #44
	add	r5, r10, #15
	sub	r1, fp, #52
	mov	r6, r6, asr #4
	ldr	r0, [fp, #4]
	str	r6, [r2, #-4]!
	mov	r5, r5, asr #4
	str	r5, [fp, #-52]
	bl	VDMHAL_CalcPmvSlotLen.isra.0
	ldr	r2, [fp, #4]
	cmp	r2, #16
	mov	r3, r0
	beq	.L91
	ldr	r2, [fp, #4]
	ldr	r9, .L96
	sub	r2, r2, #17
	cmp	r2, #1
	bls	.L92
	mov	r5, r5, asl #4
	add	r4, r8, #31
	add	r5, r5, #255
	ldr	ip, [r9, r7, asl #2]
	bic	r5, r5, #255
	bic	r4, r4, #31
	mov	r2, #0
	str	r2, [fp, #-64]
	str	r2, [fp, #-68]
.L75:
	ldr	r2, [ip, #1176]
	cmp	r2, #1
	movne	r10, #0
	strne	r10, [fp, #-60]
	movne	r8, r10
	beq	.L93
.L77:
	ldr	r2, [fp, #-56]
	cmp	r2, #1
	beq	.L94
	ldr	r1, [fp, #-64]
	add	r6, r8, r8, lsl #1
	ldr	r2, [fp, #-68]
	mul	r4, r4, r5
	mul	r2, r2, r1
	add	r1, r4, r4, lsl #1
	add	r2, r2, r2, lsl #1
	mov	r1, r1, lsr #1
	add	r2, r1, r2, lsr #1
	add	r6, r2, r6, lsr #1
.L79:
	add	r2, ip, #471040
	ldr	r1, [r2, #1224]
	cmp	r1, #0
	beq	.L95
.L80:
	add	r0, ip, #475136
	ldr	r1, [fp, #4]
	str	r6, [r0, #696]
	cmp	r1, #17
	ldr	r0, [fp, #-60]
	add	r1, r3, r3, lsr #31
	str	r10, [r2, #3576]
	mov	r1, r1, asr #1
	str	r1, [r2, #3612]
	str	r0, [r2, #3572]
	beq	.L81
	ldr	r1, [r2, #1232]
	mov	r5, r5, asl #4
	cmp	r1, #32
	movlt	r0, r1
	movge	r0, #32
	str	r0, [r2, #3616]
	ldr	r0, [ip, #600]
	str	r5, [r2, #3564]
	mov	r5, r5, lsr #1
	cmp	r0, #2
	str	r5, [r2, #3568]
	addeq	r1, r1, #1
	streq	r1, [r2, #3616]
	ldr	r1, [fp, #4]
	sub	r1, r1, #16
	cmp	r1, #2
	add	r1, r4, r8
	str	r1, [r2, #3596]
	bls	.L83
.L84:
	ldr	r2, [r9, r7, asl #2]
	mov	r0, #1024
	add	r6, r6, #1056
	add	r1, r2, #475136
	add	ip, r3, r6
	str	r3, [r1, #700]
	str	r0, [r1, #708]
	ldrsb	r2, [r2, #44]
	cmp	r2, #1
	ldr	r2, [fp, #8]
	addeq	ip, ip, r0
	cmp	r2, #0
	beq	.L90
	str	r6, [r2, #4]
	mov	r1, #1024
	ldr	r2, [r9, r7, asl #2]
	mov	r0, #0
	ldr	lr, [fp, #8]
	add	r2, r2, #471040
	ldr	r2, [r2, #1232]
	str	r3, [lr, #12]
	str	r2, [lr, #8]
	ldr	r3, [r9, r7, asl #2]
	add	r3, r3, #471040
	ldr	r3, [r3, #3616]
	str	ip, [lr]
	str	r1, [lr, #20]
	str	r3, [lr, #16]
	ldr	r3, [r9, r7, asl #2]
	add	r3, r3, #475136
	str	r6, [r3, #704]
.L73:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L81:
	mov	r5, r5, asl #4
	mov	r1, #1
	str	r5, [r2, #3564]
	str	r1, [r2, #3616]
	mov	r5, r5, lsr r1
	add	r1, r4, r8
	str	r5, [r2, #3568]
	str	r1, [r2, #3596]
.L83:
	ldr	r1, [ip, #1508]
	cmp	r1, #8
	ble	.L84
	ldr	r1, [fp, #-64]
	add	r8, r8, r8, lsl #1
	str	r3, [fp, #-56]
	add	r4, r4, r4, lsl #1
	ldr	r3, [fp, #-68]
	mov	r8, r8, lsr #1
	add	r4, r8, r4, lsr #1
	mov	r0, #31
	str	r4, [r2, #3588]
	mul	ip, r1, r3
	mov	r1, r3, asl #5
	str	r1, [r2, #3580]
	ldr	r1, .L96+4
	str	ip, [r2, #3592]
	bl	dprint_vfmw
	ldr	r3, [fp, #-56]
	b	.L84
.L95:
	ldr	lr, .L96+8
	movw	r0, #15848
	str	r3, [fp, #-56]
	mov	r2, #1248
	movt	r0, 7
	add	r0, ip, r0
	ldr	r3, [lr, #48]
	blx	r3
	ldr	ip, [r9, r7, asl #2]
	ldr	r3, [fp, #-56]
	add	r2, ip, #471040
	b	.L80
.L94:
	mov	r2, r6, asl #5
	add	r6, r2, r6, lsl #4
	mul	r4, r4, r5
	mul	r6, r5, r6
	b	.L79
.L93:
	add	r2, r10, #2032
	add	r10, r10, #4080
	add	r2, r2, #15
	add	r10, r10, #14
	cmp	r2, #0
	movge	r10, r2
	adds	r2, r8, #63
	addmi	r8, r8, #126
	movpl	r8, r2
	mov	r10, r10, asr #11
	mov	r8, r8, asr #6
	mov	r2, r10, asl #4
	str	r2, [fp, #-60]
	mov	r8, r8, asl #5
	mul	r8, r2, r8
	mov	r10, r8
	b	.L77
.L91:
	ldr	r9, .L96
	add	r5, r10, #255
	bic	r5, r5, #255
	ldr	ip, [r9, r7, asl #2]
	ldr	r2, [ip, #1508]
	cmp	r2, #8
	ble	.L88
	add	r2, r8, #31
	mov	r1, r5, lsr #2
	bic	r2, r2, #31
	str	r1, [fp, #-68]
	str	r2, [fp, #-64]
	b	.L75
.L88:
	mov	r2, #0
	str	r2, [fp, #-64]
	str	r2, [fp, #-68]
	b	.L75
.L92:
	ldr	ip, [r9, r7, asl #2]
	add	r5, r10, #255
	add	r4, r8, #63
	bic	r5, r5, #255
	bic	r4, r4, #63
	ldr	r2, [ip, #1508]
	cmp	r2, #8
	ble	.L88
	mov	r2, r5, lsr #2
	str	r4, [fp, #-64]
	str	r2, [fp, #-68]
	b	.L75
.L71:
	ldr	r3, .L96+12
	mov	r0, #0
	ldr	r2, .L96+16
	ldr	r1, .L96+20
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L90:
	ldr	r0, [fp, #8]
	b	.L73
.L97:
	.align	2
.L96:
	.word	s_pstVfmwChan
	.word	.LC11
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	.word	.LANCHOR0+48
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CalcFsSize, .-VDMHAL_V5R6C1_CalcFsSize
	.align	2
	.global	VDMHAL_V5R6C1_GetRpuSize
	.type	VDMHAL_V5R6C1_GetRpuSize, %function
VDMHAL_V5R6C1_GetRpuSize:
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
	mov	r0, #1024
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetRpuSize, .-VDMHAL_V5R6C1_GetRpuSize
	.align	2
	.global	VDMHAL_V5R6C1_CalcFsNum
	.type	VDMHAL_V5R6C1_CalcFsNum, %function
VDMHAL_V5R6C1_CalcFsNum:
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
	cmp	r3, #0
	beq	.L104
	cmp	r1, #17
	ldr	r1, .L106
	beq	.L105
	ldr	lr, [r1, r0, asl #2]
	add	ip, lr, #471040
	ldr	r2, [ip, #1232]
	cmp	r2, #32
	movlt	r4, r2
	movge	r4, #32
	str	r4, [ip, #3616]
	ldr	lr, [lr, #600]
	cmp	lr, #2
	addeq	lr, r2, #1
	streq	lr, [ip, #3616]
.L103:
	str	r2, [r3, #8]
	mov	ip, #0
	ldr	r2, [r1, r0, asl #2]
	add	r2, r2, #471040
	ldr	r2, [r2, #3616]
	str	r2, [r3, #16]
.L101:
	mov	r0, ip
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L105:
	ldr	r2, [r1, r0, asl #2]
	mov	ip, #1
	add	r2, r2, #471040
	str	ip, [r2, #3616]
	ldr	r2, [r2, #1232]
	b	.L103
.L104:
	ldr	r2, .L106+4
	mov	r0, #1
	ldr	r1, .L106+8
	bl	dprint_vfmw
	mvn	ip, #0
	b	.L101
.L107:
	.align	2
.L106:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+76
	.word	.LC12
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CalcFsNum, .-VDMHAL_V5R6C1_CalcFsNum
	.align	2
	.global	VDMHAL_V5R6C1_DynamicAllocFrame
	.type	VDMHAL_V5R6C1_DynamicAllocFrame, %function
VDMHAL_V5R6C1_DynamicAllocFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	ldr	r6, .L132
	mov	r7, r2
	mov	r8, r1
	movw	r1, #13544
	mov	r4, r0
	ldr	r2, [r6, r0, asl #2]
	movt	r1, 7
	mov	r5, r3
	add	r1, r2, r1
	bl	DelAllFrameMemRecord
	cmp	r0, #0
	bne	.L130
.L109:
	ldr	r1, [r6, r4, asl #2]
	movw	r2, #13544
	movt	r2, 7
	mov	r3, #0
	add	r2, r1, r2
	mov	r1, #255
.L110:
	str	r1, [r2, r3]
	add	r3, r3, #72
	cmp	r3, #2304
	bne	.L110
	ldr	r3, [r6, r4, asl #2]
	ldr	r0, .L132
	add	r2, r3, #475136
	ldr	r1, [r2, #1336]
	cmp	r1, #0
	bne	.L129
	cmp	r8, #1920
	cmple	r7, #1088
	ble	.L131
.L129:
	ldr	r2, [r5, #8]
.L112:
	ldr	r1, [r3, #1456]
	add	r3, r3, #471040
	mov	r0, r4
	add	r2, r2, r1
	str	r2, [r3, #1236]
	bl	VCTRL_GetVidStd
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L132
	ldr	r2, [r3, #600]
	subs	r0, r0, #17
	movne	r0, #1
	cmp	r2, #2
	movne	r0, #0
	cmp	r0, #0
	addne	r3, r3, #471040
	mov	r0, #1
	ldrne	r3, [r3, #1236]
	strne	r3, [r5, #16]
	ldrne	r3, [r1, r4, asl #2]
	add	r1, r3, #475136
	add	r2, r3, #442368
	mov	r3, #0
	str	r3, [r1, #736]
	mov	r3, r7
	str	r0, [r2, #2136]
	mov	r2, r8
	str	r0, [r1, #1276]
	mov	r0, #31
	ldr	r1, [r5, #8]
	ldr	ip, [r5, #16]
	stmia	sp, {r1, ip}
	ldr	r1, .L132+4
	bl	dprint_vfmw
	ldr	r3, .L132+8
	ldr	r9, [r3]
	cmp	r9, #0
	beq	.L117
	ldr	r2, [r5, #4]
	mov	r3, #28
	ldr	r1, [r5, #16]
	ldr	r0, [r5, #12]
	ldr	lr, [r5, #8]
	ldr	ip, [r5, #20]
	str	r2, [fp, #-60]
	sub	r2, fp, #64
	str	r1, [fp, #-56]
	mov	r1, #121
	str	r0, [fp, #-52]
	mov	r0, r4
	str	r8, [fp, #-44]
	str	r7, [fp, #-40]
	str	lr, [fp, #-64]
	str	ip, [fp, #-48]
	blx	r9
.L117:
	ldr	r0, [r6, r4, asl #2]
	mov	r1, #0
	ldr	r3, .L132+12
	mov	r2, #528
	add	r0, r0, #475136
	add	r0, r0, #744
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #0
	mov	r0, r4
	add	r3, r3, #475136
	str	r2, [r3, #1272]
	bl	FSP_ClearContextAll
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L131:
	ldr	r1, [r3, #36]
	cmp	r1, #24
	beq	.L129
	ldr	r2, [r2, #1332]
	cmp	r2, #0
	ldr	r2, [r5, #8]
	addeq	r2, r2, #4
	streq	r2, [r5, #8]
	ldreq	r3, [r0, r4, asl #2]
	b	.L112
.L130:
	ldr	r1, .L132+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L109
.L133:
	.align	2
.L132:
	.word	s_pstVfmwChan
	.word	.LC14
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_DynamicAllocFrame, .-VDMHAL_V5R6C1_DynamicAllocFrame
	.align	2
	.global	VDMHAL_V5R6C1_DynamicAllocFrame_Only
	.type	VDMHAL_V5R6C1_DynamicAllocFrame_Only, %function
VDMHAL_V5R6C1_DynamicAllocFrame_Only:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldr	ip, .L139
	ldr	lr, [r3, #8]
	mov	r4, r3
	mov	r8, r0
	mov	r3, r2
	ldr	ip, [ip, r0, asl #2]
	mov	r7, r1
	mov	r6, r2
	mov	r0, #31
	add	ip, ip, #471040
	mov	r2, r1
	ldr	r1, .L139+4
	str	lr, [ip, #1236]
	ldr	lr, [r4, #16]
	ldr	ip, [r4, #8]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L139+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L134
	ldr	r2, [r4, #8]
	mov	r0, r8
	ldr	r1, [r4, #4]
	mov	r3, #28
	ldr	r8, [r4, #16]
	ldr	lr, [r4, #12]
	ldr	ip, [r4, #20]
	str	r2, [fp, #-64]
	sub	r2, fp, #64
	str	r1, [fp, #-60]
	mov	r1, #122
	str	r7, [fp, #-44]
	str	r6, [fp, #-40]
	str	r8, [fp, #-56]
	str	lr, [fp, #-52]
	str	ip, [fp, #-48]
	blx	r5
.L134:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L140:
	.align	2
.L139:
	.word	s_pstVfmwChan
	.word	.LC15
	.word	g_event_report
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_DynamicAllocFrame_Only, .-VDMHAL_V5R6C1_DynamicAllocFrame_Only
	.align	2
	.global	VDMHAL_V5R6C1_ArrangeMem_Normal
	.type	VDMHAL_V5R6C1_ArrangeMem_Normal, %function
VDMHAL_V5R6C1_ArrangeMem_Normal:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	cmp	r1, #21
	mov	r4, r0
	mov	r5, r1
	mov	r0, #0
	mov	r6, r2
	mov	r7, r3
	str	r0, [fp, #-68]
	str	r0, [fp, #-64]
	str	r0, [fp, #-60]
	str	r0, [fp, #-56]
	str	r0, [fp, #-52]
	str	r0, [fp, #-48]
	bhi	.L181
	bl	PDT_Is3716MV450
	cmp	r0, #0
	beq	.L144
	mul	r2, r7, r6
	movw	r3, #36863
	movt	r3, 126
	cmp	r2, r3
	bgt	.L182
.L144:
	ldr	r10, .L191
	ldr	r1, [r10, r4, asl #2]
	add	r2, r1, #471040
	ldr	r3, [r1, #100]
	ldr	r2, [r2, #1228]
	cmp	r3, #2
	str	r2, [fp, #-76]
	beq	.L183
	bics	r3, r5, #16
	moveq	r3, #1
	movne	r3, #0
	cmp	r5, #18
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L184
.L147:
	sub	r3, r5, #17
	clz	r3, r3
	mov	r3, r3, lsr #5
	mov	ip, r3
.L148:
	ldr	lr, [r1, #1188]
	mov	r2, r3
	str	r3, [r1, #1176]
	mov	r0, #1
	ldr	r3, [r1, #1180]
	str	lr, [sp, #4]
	ldr	lr, .L191+4
	ldr	r1, [r1, #1184]
	str	r1, [sp]
	ldr	r1, .L191+8
	str	ip, [lr, r4, asl #4]
	bl	dprint_vfmw
.L146:
	sub	r8, fp, #68
	ldr	r2, [fp, #4]
	mov	r1, r5
	mov	r0, r4
	mov	r3, r8
	bl	VDMHAL_V5R6C1_CalcFsNum
	ldr	r3, [fp, #8]
	str	r8, [sp, #4]
	mov	r2, r7
	str	r5, [sp]
	mov	r1, r6
	mov	r9, r0
	mov	r0, r4
	bl	VDMHAL_V5R6C1_CalcFsSize
	orrs	r3, r0, r9
	bne	.L185
	ldr	r3, [r10, r4, asl #2]
	ldr	r1, [fp, #-76]
	ldr	r5, [fp, #-68]
	str	r3, [fp, #-72]
	add	r3, r3, #471040
	cmp	r1, r5
	ldr	r2, .L191
	ldr	r9, [r3, #1232]
	ldr	r1, [r3, #1248]
	beq	.L186
.L151:
	str	r1, [sp, #4]
	mov	r3, r5
	ldr	r2, .L191+12
	mov	r0, #31
	ldr	r1, .L191+16
	str	r9, [sp]
	bl	dprint_vfmw
	ldr	r3, [r10, r4, asl #2]
	mov	r1, r6
	mov	r0, r4
	add	r3, r3, #471040
	ldr	r2, [r3, #1224]
	str	r5, [r3, #1228]
	mov	r3, r8
	cmp	r2, #0
	mov	r2, r7
	beq	.L187
	bl	VDMHAL_V5R6C1_DynamicAllocFrame_Only
.L154:
	ldr	ip, [r10, r4, asl #2]
	mov	r3, r9
	mov	r2, r5
	ldr	r1, .L191+20
	add	ip, ip, #471040
	mov	r0, #31
	ldr	ip, [ip, #1248]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, .L191+24
	ldr	r4, [r10, r4, asl #2]
	ldr	r3, [r3]
	add	r4, r4, #475136
	blx	r3
	mov	r3, #2
	str	r0, [r4, #712]
.L143:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L186:
	cmp	r1, #1
	beq	.L151
	ldr	r0, [r3, #1224]
	cmp	r0, #1
	beq	.L151
	ldr	r1, [fp, #12]
	cmp	r1, #0
	beq	.L188
	ldr	r0, [fp, #-72]
	cmp	r9, #0
	movw	ip, #15848
	add	r1, r0, #475136
	movt	ip, 7
	ldrne	r2, [fp, #-72]
	ldr	r1, [r1, #696]
	str	r1, [fp, #-76]
	add	r1, r0, ip
	str	r1, [fp, #-80]
	beq	.L189
.L156:
	add	r2, r2, #471040
	ldr	r2, [r2, #1236]
	cmp	r2, #30
	bgt	.L190
.L157:
	str	r2, [r3, #3608]
	mov	r0, #8
	str	r3, [fp, #-84]
	ldr	r3, .L191+24
	ldr	r2, [r3, #12]
	blx	r2
	ldr	r2, [r10, r4, asl #2]
	ldr	r3, [fp, #-84]
	add	r8, r2, #475136
	ldr	r1, [r8, #736]
	cmp	r1, #0
	beq	.L162
	ldr	r9, [r3, #3620]
	movw	r5, #53133
	movw	r0, #16312
	ldr	lr, [r3, #3616]
	movt	r5, 1
	movt	r0, 7
	mov	ip, r9, asl #4
	add	r5, r9, r5
	sub	ip, ip, r9, asl #2
	movw	r1, #13576
	add	r0, ip, r0
	ldr	ip, [fp, #-72]
	movt	r1, 7
	add	r9, r9, #1
	add	r1, r2, r1
	add	r5, ip, r5, lsl #2
	add	r0, ip, r0
	mov	r7, #1
	mov	ip, #0
	mov	r6, lr
	str	r4, [fp, #-84]
.L161:
	ldr	r2, [r1]
	add	lr, r9, ip
	ldr	r4, [r1, #-20]
	add	ip, ip, #1
	add	r2, r2, #1020
	strb	r7, [r0, #8]
	add	r2, r2, #3
	add	r0, r0, #12
	str	r4, [r0, #-8]
	bic	r2, r2, #1020
	ldr	r4, [fp, #-76]
	bic	r2, r2, #3
	str	r2, [r0, #-12]
	add	r2, r2, r4
	str	r2, [r5, #4]!
	str	lr, [r3, #3620]
	ldr	r2, [r1, #-28]
	cmp	r2, #255
	beq	.L159
	ldr	lr, [r3, #3628]
	add	r4, lr, #1
	mov	r2, lr, asl #4
	sub	r2, r2, lr, asl #2
	ldr	lr, [r1, #16]
	add	r2, r3, r2
	add	r2, r2, #4352
	str	lr, [r2, #56]
	str	r4, [r3, #3628]
.L159:
	ldr	r2, [r3, #3624]
	cmp	r2, r6
	bcs	.L160
	ldr	r4, [r1, #-24]
	ldr	lr, [fp, #-72]
	cmp	r4, #255
	add	lr, lr, r2, lsl #3
	add	r2, r2, #1
	ldrne	r4, [r1, #32]
	add	lr, lr, #471040
	strneb	r7, [lr, #3772]
	strne	r4, [lr, #3768]
	strne	r2, [r3, #3624]
.L160:
	ldr	r2, [r8, #736]
	add	r1, r1, #72
	cmp	ip, r2
	bcc	.L161
	ldr	r4, [fp, #-84]
.L162:
	ldr	r3, .L191+24
	mov	r2, #1232
	ldr	r1, [fp, #-80]
	ldr	r0, [fp, #12]
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r10, r4, asl #2]
	ldr	r2, .L191+24
	mov	r1, #1
	add	r3, r3, #475136
	mov	r0, #8
	str	r1, [r3, #740]
	ldr	r2, [r2, #16]
	blx	r2
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L187:
	bl	VDMHAL_V5R6C1_DynamicAllocFrame
	b	.L154
.L184:
	cmp	r7, #2160
	cmplt	r6, #3840
	movge	ip, #1
	movge	r3, ip
	bge	.L148
	b	.L147
.L183:
	mov	r3, #0
	str	r3, [r1, #1176]
	str	r3, [r1, #1180]
	mvn	r3, #0
	str	r3, [r1, #1184]
	str	r3, [r1, #1188]
	b	.L146
.L189:
	ldr	r1, .L191+28
	mov	r0, #31
	str	r3, [fp, #-88]
	str	r2, [fp, #-84]
	bl	dprint_vfmw
	ldr	r2, [fp, #-84]
	ldr	r3, [fp, #-88]
	ldr	r2, [r2, r4, asl #2]
	b	.L156
.L190:
	ldr	r1, .L191+32
	mov	r0, #31
	str	r3, [fp, #-84]
	bl	dprint_vfmw
	ldr	r1, [r10, r4, asl #2]
	mov	r0, #30
	mov	r2, r0
	ldr	r3, [fp, #-84]
	add	r1, r1, #471040
	str	r0, [r1, #1236]
	b	.L157
.L181:
	ldr	r3, .L191+36
	ldr	r2, .L191+40
	ldr	r1, .L191+44
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L143
.L185:
	ldr	r1, .L191+48
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L143
.L182:
	bl	PDT_Is3716MV450
	ldr	r1, .L191+52
	mov	r2, r0
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L143
.L188:
	ldr	r3, .L191+56
	mov	r0, r1
	ldr	r2, .L191+60
	ldr	r1, .L191+44
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L143
.L192:
	.align	2
.L191:
	.word	s_pstVfmwChan
	.word	g_VfmwCompressPara
	.word	.LC18
	.word	.LANCHOR0+132
	.word	.LC20
	.word	.LC21
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC23
	.word	.LC24
	.word	.LC16
	.word	.LANCHOR0+100
	.word	.LC3
	.word	.LC19
	.word	.LC17
	.word	.LC22
	.word	.LANCHOR0+164
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ArrangeMem_Normal, .-VDMHAL_V5R6C1_ArrangeMem_Normal
	.global	__aeabi_idiv
	.align	2
	.global	VDMHAL_V5R6C1_ArrangeMem_Specific
	.type	VDMHAL_V5R6C1_ArrangeMem_Specific, %function
VDMHAL_V5R6C1_ArrangeMem_Specific:
	UNWIND(.fnstart)
	@ args = 28, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	subs	r5, r2, #0
	mov	r10, r0
	mov	r9, r1
	ldr	r7, [fp, #12]
	ldr	r6, [fp, #28]
	beq	.L268
	ldr	r2, [fp, #4]
	sub	r1, r2, #32
	movw	r2, #8160
	cmp	r1, r2
	bhi	.L196
	ldr	r1, [fp, #8]
	sub	r1, r1, #32
	cmp	r1, r2
	bhi	.L196
	cmp	r6, #0
	beq	.L269
	ldr	ip, .L278
	cmp	r7, #20
	mov	r2, #1232
	mov	r1, #0
	mov	r0, r6
	movge	r7, #20
	ldr	r4, [ip, #48]
	str	r3, [fp, #-72]
	blx	r4
	ldr	r3, [fp, #8]
	sub	r2, fp, #44
	mov	r0, r9
	add	r1, r3, #15
	ldr	r3, [fp, #4]
	add	r4, r3, #15
	mov	r3, r1, asr #4
	sub	r1, fp, #64
	str	r3, [r2, #-16]!
	str	r3, [fp, #-92]
	mov	r4, r4, asr #4
	str	r4, [fp, #-64]
	bl	VDMHAL_CalcPmvSlotLen.isra.0
	ldr	r3, [fp, #-72]
	mul	r1, r7, r0
	mov	r8, r0
	cmp	r1, r3
	ldrge	r3, .L278+4
	bge	.L267
	add	r2, r5, #1020
	rsb	r3, r1, r3
	add	r2, r2, #3
	add	r1, r0, r0, lsr #31
	bic	r2, r2, #1020
	cmp	r9, #16
	bic	r2, r2, #3
	mov	r1, r1, asr #1
	rsb	r0, r5, r2
	str	r7, [r6, #56]
	rsb	r3, r0, r3
	str	r0, [fp, #-84]
	str	r3, [fp, #-88]
	str	r1, [r6, #52]
	beq	.L270
	sub	r3, r9, #17
	cmp	r3, #1
	bls	.L271
	mov	r7, r4, asl #4
	ldr	r3, [fp, #8]
	add	r7, r7, #255
	cmp	r10, #0
	bic	r7, r7, #255
	add	r3, r3, #31
	bic	r3, r3, #31
	str	r3, [fp, #-72]
	mov	r3, r7, asl #4
	str	r3, [r6, #4]
	mov	r3, r7, asl #3
	str	r3, [r6, #8]
	blt	.L238
	ldr	r4, .L278+8
	mov	r3, #0
	str	r3, [fp, #-76]
	str	r3, [fp, #-80]
.L231:
	ldr	r3, [r4, r10, asl #2]
	ldr	r3, [r3, #1176]
	cmp	r3, #1
	movne	r1, #0
	movne	r0, r1
	movne	r3, r1
	beq	.L272
.L204:
	ldr	ip, [fp, #20]
	str	r0, [r6, #12]
	cmp	ip, #1
	str	r1, [r6, #16]
	beq	.L273
	ldr	r0, [fp, #-80]
	add	r4, r3, r3, lsl #1
	ldr	r1, [fp, #-76]
	mul	r1, r1, r0
	ldr	r0, [fp, #-72]
	mul	r0, r7, r0
	add	r1, r1, r1, lsl #1
	add	r1, r1, r1, lsr #31
	add	r0, r0, r0, lsl #1
	mov	r1, r1, asr #1
	add	r1, r1, r0, asr #1
	add	r4, r1, r4, lsr #1
.L206:
	ldr	r1, [fp, #24]
	cmp	r1, #0
	blt	.L207
	mov	r0, r1
	str	r3, [fp, #-92]
	str	r2, [fp, #-96]
	bl	VCTRL_GetChanWidth
	mov	r10, r0
	ldr	r0, [fp, #24]
	bl	VCTRL_GetChanHeight
	ldr	r2, [fp, #-96]
	cmn	r0, #1
	cmnne	r10, #1
	moveq	r3, #1
	movne	r3, #0
	str	r3, [fp, #-100]
	ldr	r3, [fp, #-92]
	beq	.L274
	ldr	r1, [fp, #20]
	add	r10, r10, #15
	bic	r10, r10, #15
	add	r0, r0, #15
	cmp	r1, #1
	add	r1, r10, #255
	bic	r0, r0, #15
	bic	r1, r1, #255
	beq	.L275
	ldr	lr, .L278+8
	ldr	ip, [fp, #24]
	ldr	lr, [lr, ip, asl #2]
	ldr	lr, [lr, #1176]
	cmp	lr, #1
	beq	.L211
	adds	lr, r0, #63
	ldr	ip, [fp, #-100]
	addmi	lr, r0, #126
	mov	lr, lr, asr #6
.L212:
	ldr	r0, [fp, #-76]
	ldr	r10, [fp, #-80]
	mul	r1, lr, r1
	mul	r0, r0, r10
	mov	lr, r1, asl #7
	sub	r1, lr, r1, asl #5
	add	r0, r0, r0, lsl #1
	add	r0, r0, r0, lsr #31
	add	r1, r1, r0, asr #1
	add	r1, r1, ip
.L210:
	cmp	r4, r1
	ldrgt	r3, .L278+12
	bgt	.L267
	ldr	r10, [fp, #24]
.L207:
	ldr	r1, [fp, #-72]
	mul	r7, r7, r1
	sub	r1, r9, #16
	cmp	r1, #1
	add	r1, r7, r3
	str	r1, [r6, #36]
	bls	.L276
	ldr	r3, [fp, #16]
	cmp	r3, #0
	beq	.L216
	cmp	r9, #3
	cmpne	r9, #0
	strne	r2, [fp, #-72]
	beq	.L214
.L266:
	cmp	r3, #32
	mov	r1, r4
	ldr	r0, [fp, #-88]
	movlt	r7, r3
	movge	r7, #32
	bl	__aeabi_idiv
	ldr	r2, [fp, #-72]
	cmp	r7, r0
	movlt	r1, r7
	movge	r1, r0
	cmp	r1, #0
	str	r1, [r6, #48]
	beq	.L215
	ldr	lr, [r6, #60]
	mov	ip, r6
	mov	r0, r2
	mov	r3, #0
.L220:
	add	r3, r3, #1
	str	r0, [ip, #464]
	cmp	r1, r3
	add	r0, r0, r4
	add	ip, ip, #12
	bne	.L220
	ldr	r3, [fp, #20]
	cmp	r3, #1
	add	r3, r1, lr
	str	r3, [r6, #60]
	beq	.L277
	ldr	r3, [fp, #-84]
	mla	r4, r1, r4, r3
	add	r3, r4, r5
.L234:
	add	r0, r6, #76
	mov	r2, #0
.L224:
	add	r2, r2, #1
	str	r3, [r0, #4]!
	cmp	r2, r1
	add	r3, r3, #32
	bne	.L224
.L223:
	ldr	ip, [r6, #56]
	add	r4, r4, r1, lsl #5
	add	r5, r4, r5
	cmp	ip, #0
	beq	.L229
	ldr	lr, [r6, #64]
	mov	r0, r6
	mov	r2, r5
	mov	r3, #0
.L228:
	add	r3, r3, #1
	str	r2, [r0, #208]
	cmp	ip, r3
	add	r2, r2, r8
	add	r0, r0, #8
	bne	.L228
	add	r3, ip, lr
	str	r3, [r6, #64]
.L229:
	mla	r8, ip, r8, r4
	cmp	r10, #0
	str	r8, [r6]
	blt	.L227
	ldr	r3, .L278+8
	ldr	r3, [r3, r10, asl #2]
	cmp	r3, #0
	beq	.L227
	cmp	r1, #0
	add	r5, r8, r5
	beq	.L227
	mov	r2, r6
	mov	r3, #0
.L230:
	add	r3, r3, #1
	str	r5, [r2, #848]
	cmp	r3, r1
	add	r5, r5, #1024
	add	r2, r2, #12
	bne	.L230
.L227:
	mov	r0, #0
	add	r8, r8, r1, lsl #10
	str	r8, [r6]
.L265:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L276:
	ldr	r0, [fp, #16]
	mov	r1, r3, lsr #1
	ldr	ip, [fp, #-80]
	add	r3, r3, r3, lsl #1
	cmp	r0, #0
	ldr	r0, [fp, #-76]
	add	r7, r7, r7, lsl #1
	mov	r3, r3, lsr #1
	mla	r1, r0, ip, r1
	add	r7, r3, r7, asr #1
	mov	r3, r0, asl #4
	str	r7, [r6, #28]
	str	r3, [r6, #20]
	str	r1, [r6, #32]
	bne	.L214
.L216:
	mov	r3, #0
	str	r3, [r6, #48]
.L215:
	ldr	r3, .L278+16
.L267:
	ldr	r2, .L278+20
	mov	r0, #0
	ldr	r1, .L278+24
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L214:
	str	r2, [fp, #-72]
	ldr	r3, [fp, #16]
	b	.L266
.L270:
	ldr	r3, [fp, #4]
	cmp	r10, #0
	add	r7, r3, #255
	bic	r7, r7, #255
	blt	.L201
	ldr	r4, .L278+8
	movw	r0, #17736
	movt	r0, 7
	str	r2, [fp, #-72]
	ldr	r3, [r4, r10, asl #2]
	add	r0, r3, r0
	bl	IsMain10Profile
	ldr	r2, [fp, #-72]
	cmp	r0, #0
	beq	.L235
	ldr	r1, [fp, #8]
	cmp	r7, #0
	add	r3, r7, #3
	add	r1, r1, #31
	movge	r3, r7
	bic	r1, r1, #31
	str	r1, [fp, #-80]
	ldr	r1, [fp, #8]
	mov	r3, r3, asr #2
	str	r3, [fp, #-76]
	str	r1, [fp, #-72]
	b	.L202
.L273:
	ldr	r1, [fp, #-92]
	mov	r4, r1, asl #4
	mul	r4, r7, r4
	add	r4, r4, r4, lsl #1
	b	.L206
.L277:
	ldr	r3, .L278+28
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L222
	str	r2, [fp, #-56]
	mov	r3, #12
	str	r1, [fp, #-48]
	sub	r2, fp, #56
	mov	r1, #128
	str	r4, [fp, #-52]
	mov	r0, r10
	blx	r7
	ldr	r1, [r6, #48]
.L222:
	ldr	r3, [fp, #-84]
	cmp	r1, #0
	mla	r4, r1, r4, r3
	add	r3, r4, r5
	bne	.L234
	b	.L223
.L271:
	ldr	r3, [fp, #4]
	cmp	r10, #0
	add	r7, r3, #255
	ldr	r3, [fp, #8]
	bic	r7, r7, #255
	add	r3, r3, #63
	bic	r3, r3, #63
	str	r3, [fp, #-72]
	blt	.L236
	ldr	r4, .L278+8
	ldr	r3, [r4, r10, asl #2]
	ldr	r3, [r3, #1508]
	cmp	r3, #8
	ble	.L237
	ldr	r1, [fp, #-72]
	cmp	r7, #0
	add	r3, r7, #3
	movge	r3, r7
	mov	r3, r3, asr #2
	str	r1, [fp, #-80]
	str	r3, [fp, #-76]
.L202:
	mov	r3, r7, asl #4
	str	r3, [r6, #4]
	mov	r3, r7, asl #3
	str	r3, [r6, #8]
	b	.L231
.L236:
	ldr	r3, [fp, #-72]
	str	r3, [fp, #8]
.L201:
	ldr	r3, [fp, #8]
	mov	r1, #0
	mov	ip, r7, asl #4
	mov	r0, r1
	str	ip, [r6, #4]
	mov	ip, r7, asl #3
	str	r3, [fp, #-72]
	mov	r3, r1
	str	r1, [fp, #-76]
	str	r1, [fp, #-80]
	str	ip, [r6, #8]
	b	.L204
.L272:
	sub	r1, r9, #17
	ldr	r3, [fp, #4]
	clz	r1, r1
	mov	r1, r1, lsr #5
	cmp	r3, #1920
	orrgt	r1, r1, #1
	cmp	r1, #0
	moveq	r0, r1
	moveq	r3, r1
	beq	.L204
	ldr	r1, [fp, #4]
	add	r3, r3, #2032
	add	r3, r3, #15
	ldr	r0, [fp, #8]
	add	r1, r1, #4080
	cmp	r3, #0
	add	r1, r1, #14
	movlt	r3, r1
	ldr	r1, [fp, #8]
	mov	r3, r3, asr #11
	adds	r1, r1, #63
	addmi	r1, r0, #126
	mov	r0, r3, asl #4
	mov	r1, r1, asr #6
	mov	r3, r1, asl #5
	mul	r3, r0, r3
	mov	r1, r3
	b	.L204
.L275:
	mul	r1, r0, r1
	add	r1, r1, r1, lsl #1
	b	.L210
.L238:
	mov	r1, #0
	str	r1, [fp, #-76]
	mov	r0, r1
	str	r1, [fp, #-80]
	mov	r3, r1
	b	.L204
.L211:
	add	lr, r10, #2032
	adds	ip, r0, #63
	add	lr, lr, #15
	addmi	ip, r0, #126
	add	r10, r10, #4080
	cmp	lr, #0
	add	r10, r10, #14
	movge	r10, lr
	mov	lr, ip, asr #6
	mov	r10, r10, asr #11
	mov	ip, lr, asl #7
	sub	ip, ip, lr, asl #5
	mov	r0, r10, asl #4
	mul	ip, r0, ip
	mov	ip, ip, lsr #1
	b	.L212
.L235:
	ldr	r1, [fp, #8]
	str	r0, [fp, #-80]
	str	r0, [fp, #-76]
	str	r1, [fp, #-72]
	b	.L202
.L237:
	mov	r3, #0
	str	r3, [fp, #-80]
	str	r3, [fp, #-76]
	b	.L202
.L196:
	ldr	r3, .L278+32
	b	.L267
.L268:
	mov	r0, r5
	ldr	r3, .L278+36
	ldr	r2, .L278+20
	ldr	r1, .L278+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L265
.L274:
	ldr	r1, .L278+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L265
.L269:
	mov	r0, r6
	ldr	r3, .L278+44
	ldr	r2, .L278+20
	ldr	r1, .L278+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L265
.L279:
	.align	2
.L278:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	s_pstVfmwChan
	.word	.LC29
	.word	.LC30
	.word	.LANCHOR0+200
	.word	.LC3
	.word	g_event_report
	.word	.LC10
	.word	.LC25
	.word	.LC28
	.word	.LC26
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ArrangeMem_Specific, .-VDMHAL_V5R6C1_ArrangeMem_Specific
	.align	2
	.global	VDMHAL_V5R6C1_ArrangeMem
	.type	VDMHAL_V5R6C1_ArrangeMem, %function
VDMHAL_V5R6C1_ArrangeMem:
	UNWIND(.fnstart)
	@ args = 20, pretend = 0, frame = 8
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
	ldr	r4, [fp, #16]
	mov	r6, r3
	mov	r9, r0
	cmn	r4, #2
	mov	r5, r2
	ldmib	fp, {r7, r10}
	ldr	r8, [fp, #12]
	ldr	r3, [fp, #20]
	beq	.L283
	cmp	r4, #0
	blt	.L284
	mov	r0, r4
	str	r3, [fp, #-52]
	str	r1, [fp, #-48]
	bl	VCTRL_GetVidStd
	ldr	r2, .L287
	ldr	r1, [fp, #-48]
	ldr	r3, [fp, #-52]
	ldr	r2, [r2, r4, asl #2]
	ldr	r2, [r2, #1448]
	cmp	r2, #1
	beq	.L286
.L282:
	str	r3, [sp, #24]
	mov	r2, r9
	mov	r3, r1
	str	r4, [sp, #20]
	mov	r1, r0
	str	r8, [sp, #16]
	str	r10, [sp, #12]
	mov	r0, r4
	stmia	sp, {r5, r6, r7}
	bl	VDMHAL_V5R6C1_ArrangeMem_Specific
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L284:
	mov	r0, #22
	b	.L282
.L283:
	mov	r0, #16
	b	.L282
.L286:
	str	r3, [fp, #12]
	mov	r1, r0
	mov	r3, r6
	str	r8, [fp, #8]
	mov	r2, r5
	str	r7, [fp, #4]
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDMHAL_V5R6C1_ArrangeMem_Normal
.L288:
	.align	2
.L287:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ArrangeMem, .-VDMHAL_V5R6C1_ArrangeMem
	.align	2
	.global	VDMHAL_V5R6C1_ResetVdm
	.type	VDMHAL_V5R6C1_ResetVdm, %function
VDMHAL_V5R6C1_ResetVdm:
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
	subs	r5, r0, #0
	mov	r0, #0
	ble	.L290
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L307
	ldr	r1, .L307+4
	bl	dprint_vfmw
.L289:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L290:
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L305
	movw	r10, #1228
	ldr	r6, .L307+8
	mul	r10, r10, r5
	ldr	r3, [r6, r10]
	add	r2, r3, #61440
	ldr	r7, [r3, #36]
	ldr	r3, [r2, #2052]
	tst	r3, #3
	str	r3, [fp, #-48]
	beq	.L289
	ldr	r4, .L307+12
	mov	r9, r6
	mov	r8, #0
	ldr	r3, [r4, #112]
	blx	r3
	ldr	r2, [r9, r10]!
	add	r2, r2, #61440
	ldr	r3, [r2, #2060]
	str	r3, [fp, #-48]
	uxtb	r3, r3
	orr	r3, r3, #2
	strb	r3, [fp, #-48]
	ldr	r3, [fp, #-48]
	str	r3, [r2, #2060]
	b	.L295
.L306:
	add	r8, r8, #1
	cmp	r8, #1000
	beq	.L296
.L295:
	ldr	r3, [r4, #116]
	mov	r0, #30
	blx	r3
	ldr	r3, [r9]
	add	r3, r3, #61440
	ldr	r3, [r3, #2064]
	tst	r3, #2
	str	r3, [fp, #-48]
	beq	.L306
	cmp	r8, #1000
	bge	.L296
	mov	r3, r5
	ldr	r2, .L307
	ldr	r1, .L307+16
	mov	r0, #0
	bl	dprint_vfmw
.L298:
	movw	r3, #1228
	ldr	r1, [r4, #112]
	mul	r5, r3, r5
	ldr	r2, [r6, r5]
	add	r2, r2, #61440
	ldr	r3, [r2, #2060]
	str	r3, [fp, #-48]
	bfc	r3, #1, #1
	strb	r3, [fp, #-48]
	ldr	r3, [fp, #-48]
	str	r3, [r2, #2060]
	blx	r1
	ldr	r3, [r6, r5]
	str	r7, [r3, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L296:
	mov	r3, r5
	ldr	r2, .L307
	ldr	r1, .L307+20
	mov	r0, #0
	bl	dprint_vfmw
	b	.L298
.L305:
	ldr	r1, .L307+24
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L308:
	.align	2
.L307:
	.word	.LANCHOR0+236
	.word	.LC0
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	.word	.LC32
	.word	.LC31
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ResetVdm, .-VDMHAL_V5R6C1_ResetVdm
	.align	2
	.global	VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.type	VDMHAL_V5R6C1_SetSmmuPageTableAddr, %function
VDMHAL_V5R6C1_SetSmmuPageTableAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	ldr	r3, .L315
	mov	r4, r0
	ldr	r3, [r3, #196]
	cmp	r3, #0
	beq	.L309
	sub	r2, fp, #24
	sub	r1, fp, #28
	sub	r0, fp, #32
	blx	r3
	cmp	r4, #0
	bne	.L311
	ldr	r3, .L315+4
	ldr	r0, [fp, #-32]
	ldr	r1, [fp, #-28]
	ldr	r3, [r3]
	ldr	r2, [fp, #-24]
	add	r3, r3, #61440
	str	r0, [r3, #524]
	str	r1, [r3, #772]
	str	r2, [r3, #776]
.L309:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L311:
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L315+8
	ldr	r1, .L315+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L315+8
	ldr	r1, .L315+12
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L315+8
	ldr	r1, .L315+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L316:
	.align	2
.L315:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LANCHOR0+260
	.word	.LC34
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_SetSmmuPageTableAddr, .-VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.align	2
	.global	VDMHAL_V5R6C1_EnableSmmu
	.type	VDMHAL_V5R6C1_EnableSmmu, %function
VDMHAL_V5R6C1_EnableSmmu:
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
	ldr	r3, .L318
	mov	r2, #8
	movt	r2, 3
	ldr	r3, [r3]
	add	r3, r3, #61440
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L319:
	.align	2
.L318:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_EnableSmmu, .-VDMHAL_V5R6C1_EnableSmmu
	.align	2
	.global	VDMHAL_V5R6C1_GlbResetX
	.type	VDMHAL_V5R6C1_GlbResetX, %function
VDMHAL_V5R6C1_GlbResetX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r4, r0
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L339
	cmp	r4, #0
	ble	.L340
	mov	r2, #1
	mov	r3, r4
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L344
	ldr	r1, .L344+4
	bl	dprint_vfmw
	ldrb	r5, [fp, #-32]	@ zero_extendqisi2
	and	r5, r5, #3
	cmp	r5, #1
	beq	.L341
.L320:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L340:
	movw	r5, #1228
	ldr	r7, .L344+8
	mul	r5, r5, r4
	ldr	r3, [r7, r5]
	add	r3, r3, #61440
	ldr	r3, [r3, #2052]
	and	r2, r3, #3
	cmp	r2, #1
	str	r3, [fp, #-32]
	bne	.L320
	ldr	r6, .L344+12
	ldr	r3, [r6, #112]
	blx	r3
	ldr	r3, [r7, r5]
	add	r3, r3, #61440
	ldr	r1, [r3, #2060]
	uxtb	r2, r1
	str	r1, [fp, #-32]
	orr	r2, r2, #1
	strb	r2, [fp, #-32]
	ldr	r2, [fp, #-32]
	str	r2, [r3, #2060]
	b	.L335
.L341:
	ldr	r6, .L344+12
	ldr	r3, [r6, #112]
	blx	r3
	mov	r3, r4
	ldr	r2, .L344
	mov	r0, #32
	ldr	r1, .L344+4
	str	r5, [sp]
	bl	dprint_vfmw
	ldrb	ip, [fp, #-32]	@ zero_extendqisi2
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L344
	mov	r0, #32
	ldr	r1, .L344+16
	orr	ip, ip, #1
	strb	ip, [fp, #-32]
	bl	dprint_vfmw
.L335:
	ldr	r3, .L344+8
	movw	r7, #1228
	mov	r5, #0
	mla	r7, r7, r4, r3
	b	.L330
.L327:
	str	ip, [sp]
	bl	dprint_vfmw
	ldrb	r3, [fp, #-32]	@ zero_extendqisi2
	tst	r3, #1
	bne	.L329
.L342:
	add	r5, r5, #1
	cmp	r5, #1000
	beq	.L331
.L330:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	cmp	r4, #0
	mov	ip, #1
	mov	r3, r4
	ldr	r2, .L344
	mov	r0, #32
	ldr	r1, .L344+4
	bgt	.L327
	ldr	r3, [r7]
	add	r3, r3, #61440
	ldr	r3, [r3, #2064]
	str	r3, [fp, #-32]
	ldrb	r3, [fp, #-32]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L342
.L329:
	cmp	r5, #1000
	bge	.L331
	mov	r3, r4
	ldr	r2, .L344
	ldr	r1, .L344+20
	mov	r0, #0
	bl	dprint_vfmw
.L333:
	cmp	r4, #0
	ble	.L343
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L344
	ldr	r1, .L344+4
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L344
	ldr	r1, .L344+16
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L331:
	mov	r3, r4
	ldr	r2, .L344
	ldr	r1, .L344+24
	mov	r0, #0
	bl	dprint_vfmw
	b	.L333
.L343:
	movw	r3, #1228
	ldr	r2, .L344+8
	mul	r4, r3, r4
	ldr	r2, [r2, r4]
	add	r2, r2, #61440
	ldr	r3, [r2, #2060]
	str	r3, [fp, #-32]
	bfc	r3, #0, #1
	strb	r3, [fp, #-32]
	ldr	r3, [fp, #-32]
	str	r3, [r2, #2060]
	b	.L320
.L339:
	mov	r3, #0
	ldr	r2, .L344
	movt	r3, 63683
	ldr	r1, .L344+28
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L345:
	.align	2
.L344:
	.word	.LANCHOR0+296
	.word	.LC36
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC34
	.word	.LC38
	.word	.LC37
	.word	.LC35
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GlbResetX, .-VDMHAL_V5R6C1_GlbResetX
	.align	2
	.global	VDMHAL_V5R6C1_GlbReset
	.type	VDMHAL_V5R6C1_GlbReset, %function
VDMHAL_V5R6C1_GlbReset:
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
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L348
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMHAL_V5R6C1_GlbResetX
.L348:
	mov	r3, #0
	ldr	r2, .L349
	movt	r3, 63683
	ldr	r1, .L349+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L350:
	.align	2
.L349:
	.word	.LANCHOR0+320
	.word	.LC35
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GlbReset, .-VDMHAL_V5R6C1_GlbReset
	.align	2
	.global	VDMHAL_V5R6C1_ClearIntState
	.type	VDMHAL_V5R6C1_ClearIntState, %function
VDMHAL_V5R6C1_ClearIntState:
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
	ldr	r7, .L367
	mov	r5, r0, asl #3
	mov	r8, r0, asl #6
	rsb	r3, r5, r8
	ldr	r2, .L367+4
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1208]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L364
	movw	r6, #1228
	ldr	r9, .L367+8
	mul	r6, r6, r0
	ldr	r3, [r9, r6]
	cmp	r3, #0
	beq	.L365
.L355:
	cmp	r4, #1
	beq	.L366
.L362:
	mvn	r2, #0
	str	r2, [r3, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L364:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L367+12
	ldr	r2, .L367+16
	bl	dprint_vfmw
.L351:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L366:
	rsb	r5, r5, r8
	add	r7, r7, r5
	ldr	r2, [r7, #44]
	cmp	r2, #1
	beq	.L362
	cmp	r2, #2
	ldr	r1, [r3, #28]
	mvneq	r2, #11
	streq	r2, [r3, #32]
	beq	.L351
	cmp	r2, #3
	mvneq	r2, #14
	streq	r2, [r3, #32]
	b	.L351
.L365:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r9, r6]
	bne	.L355
.L356:
	ldr	r1, .L367+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L368:
	.align	2
.L367:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC0
	.word	.LANCHOR0+344
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ClearIntState, .-VDMHAL_V5R6C1_ClearIntState
	.align	2
	.global	VDMHAL_V5R6C1_ClearMMUIntState
	.type	VDMHAL_V5R6C1_ClearMMUIntState, %function
VDMHAL_V5R6C1_ClearMMUIntState:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r3, r0, #0
	bgt	.L374
	movw	r2, #1228
	ldr	r5, .L376
	mul	r4, r2, r3
	ldr	r2, [r5, r4]
	cmp	r2, #0
	beq	.L375
.L372:
	add	r2, r2, #61440
	mov	r3, #7
	str	r3, [r2, #44]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L374:
	mov	r0, #0
	ldr	r2, .L376+4
	str	r0, [sp]
	ldr	r1, .L376+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L375:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	strne	r2, [r5, r4]
	bne	.L372
.L373:
	ldr	r1, .L376+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L377:
	.align	2
.L376:
	.word	g_HwMem
	.word	.LANCHOR0+372
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ClearMMUIntState, .-VDMHAL_V5R6C1_ClearMMUIntState
	.align	2
	.global	VDMHAL_V5R6C1_MaskInt
	.type	VDMHAL_V5R6C1_MaskInt, %function
VDMHAL_V5R6C1_MaskInt:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r3, r0, #0
	bgt	.L383
	movw	r2, #1228
	ldr	r5, .L385
	mul	r4, r2, r3
	ldr	r3, [r5, r4]
	cmp	r3, #0
	beq	.L384
.L381:
	mvn	r2, #0
	str	r2, [r3, #36]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L383:
	mov	r0, #0
	ldr	r2, .L385+4
	str	r0, [sp]
	ldr	r1, .L385+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L384:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r5, r4]
	bne	.L381
.L382:
	ldr	r1, .L385+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L386:
	.align	2
.L385:
	.word	g_HwMem
	.word	.LANCHOR0+404
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_MaskInt, .-VDMHAL_V5R6C1_MaskInt
	.align	2
	.global	VDMHAL_V5R6C1_GetIntMaskCfg
	.type	VDMHAL_V5R6C1_GetIntMaskCfg, %function
VDMHAL_V5R6C1_GetIntMaskCfg:
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
	cmp	r0, #1
	mvneq	r0, #5
	mvnne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetIntMaskCfg, .-VDMHAL_V5R6C1_GetIntMaskCfg
	.align	2
	.global	VDMHAL_V5R6C1_EnableInt
	.type	VDMHAL_V5R6C1_EnableInt, %function
VDMHAL_V5R6C1_EnableInt:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	ldr	r2, .L401
	mov	r3, r0, asl #6
	ldr	r1, .L401+4
	sub	r3, r3, r0, asl #3
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1208]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L399
	movw	r5, #1228
	ldr	r6, .L401+8
	mul	r5, r5, r0
	ldr	r3, [r6, r5]
	cmp	r3, #0
	beq	.L400
.L394:
	cmp	r4, #1
	mvneq	r2, #5
	mvnne	r2, #1
	str	r2, [r3, #36]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L399:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L401+12
	ldr	r2, .L401+16
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L400:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r6, r5]
	bne	.L394
.L395:
	ldr	r1, .L401+20
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L402:
	.align	2
.L401:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC0
	.word	.LANCHOR0+428
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_EnableInt, .-VDMHAL_V5R6C1_EnableInt
	.align	2
	.global	VDMHAL_V5R6C1_CheckReg
	.type	VDMHAL_V5R6C1_CheckReg, %function
VDMHAL_V5R6C1_CheckReg:
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
	subs	r5, r1, #0
	mov	r7, r0
	bgt	.L420
	movw	r4, #1228
	ldr	r6, .L422
	mul	r4, r4, r5
	ldr	r3, [r6, r4]
	cmp	r3, #0
	beq	.L421
.L406:
	sub	r2, r7, #1
	cmp	r2, #6
	ldrls	pc, [pc, r2, asl #2]
	b	.L412
.L414:
	.word	.L417
	.word	.L415
	.word	.L416
	.word	.L418
	.word	.L408
	.word	.L410
	.word	.L411
.L418:
	mov	r3, #40
.L413:
	movw	r1, #1228
	mul	r5, r1, r5
	ldr	r2, [r6, r5]
	ldr	r0, [r2, r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L417:
	mov	r3, #28
	b	.L413
.L416:
	mov	r3, #36
	b	.L413
.L415:
	mov	r3, #32
	b	.L413
.L411:
	movw	r3, #62272
	b	.L413
.L408:
	movw	r3, #61480
	b	.L413
.L410:
	movw	r3, #62304
	b	.L413
.L412:
	mov	r3, r7
	ldr	r2, .L422+4
	ldr	r1, .L422+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L421:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L407
	str	r8, [r6, r4]
	b	.L406
.L420:
	mov	r3, r5
	ldr	r2, .L422+4
	ldr	r1, .L422+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L407:
	ldr	r2, .L422+4
	ldr	r1, .L422+16
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L423:
	.align	2
.L422:
	.word	g_HwMem
	.word	.LANCHOR0+452
	.word	.LC41
	.word	.LC39
	.word	.LC40
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CheckReg, .-VDMHAL_V5R6C1_CheckReg
	.align	2
	.global	VDMHAL_V5R6C1_ReadMMUMask
	.type	VDMHAL_V5R6C1_ReadMMUMask, %function
VDMHAL_V5R6C1_ReadMMUMask:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r3, r0, #0
	ble	.L427
	mov	r1, #1
	ldr	r2, .L428
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L428+4
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L427:
	movw	r0, #1228
	ldr	r2, .L428+8
	mul	r3, r0, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	ldr	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L429:
	.align	2
.L428:
	.word	.LANCHOR0+476
	.word	.LC36
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ReadMMUMask, .-VDMHAL_V5R6C1_ReadMMUMask
	.align	2
	.global	VDMHAL_V5R6C1_WriteMMUMask
	.type	VDMHAL_V5R6C1_WriteMMUMask, %function
VDMHAL_V5R6C1_WriteMMUMask:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r3, r1, #0
	ble	.L433
	mov	r1, #1
	ldr	r2, .L434
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L434+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L433:
	movw	r1, #1228
	ldr	r2, .L434+8
	mul	r3, r1, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	str	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L435:
	.align	2
.L434:
	.word	.LANCHOR0+504
	.word	.LC34
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_WriteMMUMask, .-VDMHAL_V5R6C1_WriteMMUMask
	.align	2
	.global	VDMHAL_V5R6C1_PrepareDec
	.type	VDMHAL_V5R6C1_PrepareDec, %function
VDMHAL_V5R6C1_PrepareDec:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r7, r1, #0
	mov	r4, r0
	mov	r5, r2
	mov	r6, r3
	beq	.L456
	cmp	r2, #0
	bgt	.L457
	sub	r1, r0, #6
	mov	r2, #0
	clz	r1, r1
	mov	r0, r2
	mov	r1, r1, lsr #5
	bl	SCD_ConfigReg
	mov	r3, r6
	mov	r2, #0
	mov	r1, #1
	mov	r0, #8
	bl	SCD_ConfigReg
	cmp	r4, #18
	ldrls	pc, [pc, r4, asl #2]
	b	.L438
.L441:
	.word	.L451
	.word	.L442
	.word	.L443
	.word	.L444
	.word	.L438
	.word	.L445
	.word	.L446
	.word	.L438
	.word	.L447
	.word	.L448
	.word	.L449
	.word	.L449
	.word	.L449
	.word	.L450
	.word	.L438
	.word	.L451
	.word	.L452
	.word	.L453
	.word	.L454
.L451:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264HAL_V5R6C1_StartDec
.L452:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCHAL_V5R6C1_StartDec
.L453:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP9HAL_V5R6C1_StartDec
.L454:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS2HAL_V5R6C1_StartDec
.L442:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1HAL_V5R6C1_StartDec
.L443:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP4HAL_V5R6C1_StartDec
.L444:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP2HAL_V5R6C1_StartDec
.L445:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DIVX3HAL_V5R6C1_StartDec
.L446:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVSHAL_V5R6C1_StartDec
.L447:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV8HAL_V5R6C1_StartDec
.L448:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV9HAL_V5R6C1_StartDec
.L449:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP6HAL_V5R6C1_StartDec
.L450:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP8HAL_V5R6C1_StartDec
.L456:
	mov	r3, r7
	mov	r0, r7
	ldr	r2, .L458
	ldr	r1, .L458+4
	bl	dprint_vfmw
.L438:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L457:
	mov	r3, r2
	mov	r0, #0
	ldr	r2, .L458
	str	r0, [sp]
	ldr	r1, .L458+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L459:
	.align	2
.L458:
	.word	.LANCHOR0+532
	.word	.LC42
	.word	.LC0
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_PrepareDec, .-VDMHAL_V5R6C1_PrepareDec
	.align	2
	.global	VDMHAL_V5R6C1_IsVdmReady
	.type	VDMHAL_V5R6C1_IsVdmReady, %function
VDMHAL_V5R6C1_IsVdmReady:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	movw	r2, #1228
	mul	r2, r2, r0
	ldr	r3, .L467
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L465
	cmp	r0, #0
	ble	.L466
	mov	r3, r0
	mov	r1, #1
	ldr	r2, .L467+4
	mov	r0, #32
	str	r1, [sp]
	ldr	r1, .L467+8
	bl	dprint_vfmw
	mov	r0, #0
.L462:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L466:
	ldr	r0, [r3, #28]
	ubfx	r0, r0, #17, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L465:
	mov	r0, r3
	ldr	r2, .L467+4
	ldr	r3, .L467+12
	ldr	r1, .L467+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L462
.L468:
	.align	2
.L467:
	.word	g_HwMem
	.word	.LANCHOR0+560
	.word	.LC36
	.word	.LC43
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_IsVdmReady, .-VDMHAL_V5R6C1_IsVdmReady
	.align	2
	.global	VDMHAL_V5R6C1_IsVdmRun
	.type	VDMHAL_V5R6C1_IsVdmRun, %function
VDMHAL_V5R6C1_IsVdmRun:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	movw	r2, #1228
	mul	r2, r2, r0
	ldr	r3, .L476
	ldr	r4, [r3, r2]
	cmp	r4, #0
	beq	.L474
	cmp	r0, #0
	ble	.L475
	mov	r3, r0
	mov	r4, #1
	ldr	r2, .L476+4
	mov	r0, #32
	str	r4, [sp]
	ldr	r1, .L476+8
	bl	dprint_vfmw
	mov	r0, r4
.L471:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L475:
	ldr	r0, [r4, #40]
	subs	r0, r0, #1
	movne	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L474:
	ldr	r1, .L476+12
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	b	.L471
.L477:
	.align	2
.L476:
	.word	g_HwMem
	.word	.LANCHOR0+588
	.word	.LC36
	.word	.LC44
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_IsVdmRun, .-VDMHAL_V5R6C1_IsVdmRun
	.align	2
	.global	VDMHAL_V5R6C1_IsVdhDecOver
	.type	VDMHAL_V5R6C1_IsVdhDecOver, %function
VDMHAL_V5R6C1_IsVdhDecOver:
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
	movw	r2, #1228
	ldr	r3, .L488
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L486
	bl	VDMHAL_V5R6C1_CheckReg
	cmp	r4, #2
	beq	.L483
	cmp	r4, #3
	beq	.L483
	cmp	r4, #1
	beq	.L487
	mov	r3, r4
	ldr	r2, .L488+4
	ldr	r1, .L488+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L483:
	and	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L487:
	ubfx	r0, r0, #17, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L486:
	mov	r0, r3
	ldr	r2, .L488+4
	ldr	r3, .L488+12
	ldr	r1, .L488+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L489:
	.align	2
.L488:
	.word	g_HwMem
	.word	.LANCHOR0+612
	.word	.LC41
	.word	.LC43
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_IsVdhDecOver, .-VDMHAL_V5R6C1_IsVdhDecOver
	.align	2
	.global	VDMHAL_V5R6C1_IsVdhPartDecOver
	.type	VDMHAL_V5R6C1_IsVdhPartDecOver, %function
VDMHAL_V5R6C1_IsVdhPartDecOver:
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
	movw	r2, #1228
	ldr	r3, .L500
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L498
	bl	VDMHAL_V5R6C1_CheckReg
	cmp	r4, #1
	beq	.L494
	cmp	r4, #2
	bne	.L499
	ubfx	r0, r0, #2, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L499:
	mov	r3, r4
	ldr	r2, .L500+4
	ldr	r1, .L500+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L494:
	ubfx	r0, r0, #19, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L498:
	mov	r0, r3
	ldr	r2, .L500+4
	ldr	r3, .L500+12
	ldr	r1, .L500+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L501:
	.align	2
.L500:
	.word	g_HwMem
	.word	.LANCHOR0+640
	.word	.LC41
	.word	.LC43
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_IsVdhPartDecOver, .-VDMHAL_V5R6C1_IsVdhPartDecOver
	.align	2
	.global	VDMHAL_V5R6C1_UpdateHardwareInfo
	.type	VDMHAL_V5R6C1_UpdateHardwareInfo, %function
VDMHAL_V5R6C1_UpdateHardwareInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r5, r0, #0
	bgt	.L503
	ldr	r2, .L537
	ldr	r4, [r2]
	cmp	r4, #1
	addne	r3, r2, #124
	bne	.L507
	b	.L504
.L531:
	cmp	r2, r3
	beq	.L530
.L507:
	ldr	r4, [r2, #4]!
	cmp	r4, #1
	bne	.L531
.L504:
	movw	r6, #1228
	ldr	r7, .L537+4
	mul	r6, r6, r5
	ldr	lr, [r7, r6]
	cmp	lr, #0
	beq	.L532
.L508:
	mov	r2, #180
	ldr	r1, .L537+8
	mul	r2, r2, r5
	mov	r3, r5, asl #6
	sub	r3, r3, r5, asl #3
	ldr	r0, [lr, #12]
	ldr	r6, .L537+12
	add	r3, r3, r1
	ldr	r1, [r3, #4]
	add	r3, r6, r2
	str	r0, [r6, r2]
	ldr	r2, [lr, #28]
	cmp	r1, #1
	str	r2, [r3, #4]
	beq	.L533
	cmp	r4, #1
	beq	.L534
	add	r2, lr, #4096
	cmp	r4, #0
	ldr	ip, [r2]
	ldr	r0, [r2, #12]
	ldr	r1, [lr, #208]
	ldr	r2, [lr, #212]
	str	ip, [r3, #16]
	str	r0, [r3, #20]
	str	r1, [r3, #8]
	str	r2, [r3, #12]
	bne	.L513
	ldr	r2, [lr, #176]
	ldr	ip, [lr, #180]
	ldr	r0, [lr, #184]
	str	r2, [r3, #24]
	ldr	r1, [lr, #188]
	ldr	r2, [lr, #192]
	str	ip, [r3, #28]
	str	r0, [r3, #32]
	str	r1, [r3, #36]
	str	r2, [r3, #40]
.L513:
	mov	r0, #180
	add	r1, lr, #33024
	mul	r0, r0, r5
	add	r2, r0, #48
	add	r0, r0, #176
	add	r2, r6, r2
	add	r0, r6, r0
.L514:
	ldr	ip, [r1], #4
	str	ip, [r2, #4]!
	cmp	r2, r0
	bne	.L514
	cmp	r4, #0
	bne	.L535
	mov	r3, #180
	add	lr, lr, #32768
	mla	r5, r3, r5, r6
	ldr	r2, [lr, #384]
	ldr	r3, [lr, #388]
	mov	r0, r4
	str	r2, [r5, #48]
	str	r3, [r5, #44]
.L525:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L535:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L530:
	mov	r4, #0
	b	.L504
.L533:
	add	r1, lr, #4096
	mov	r0, #0
	ldr	r1, [r1, #12]
	ubfx	ip, r1, #0, #20
	str	r1, [r3, #20]
	ldr	r1, [lr, #176]
	str	ip, [r3, #20]
	str	r1, [r3, #24]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L534:
	movw	r3, #1228
	ubfx	r8, r2, #0, #17
	mla	r3, r3, r5, r7
	ldr	r0, [r3, #40]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L536
	sub	r3, r8, #1
	movw	r1, #1228
	cmp	r3, #199
	mov	r2, #180
	subls	r3, r8, #-1073741823
	mul	r1, r1, r5
	movls	r3, r3, asl #4
	movhi	r3, #0
	addls	r8, r3, #8
	ldr	r0, [ip, r3]
	movhi	r8, #8
	mla	r3, r2, r5, r6
	ldr	lr, [r7, r1]
	str	r0, [r3, #16]
	ldr	r0, [lr, #208]
	ldr	r1, [ip, r8]
	ldr	r2, [lr, #212]
	str	r0, [r3, #8]
	str	r1, [r3, #20]
	str	r2, [r3, #12]
	b	.L513
.L532:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	lr, r0, #0
	beq	.L509
	str	lr, [r7, r6]
	b	.L508
.L503:
	mov	r0, #0
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L537+16
	ldr	r1, .L537+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L525
.L509:
	ldr	r1, .L537+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L525
.L536:
	ldr	r3, .L537+28
	ldr	r2, .L537+16
	ldr	r1, .L537+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L525
.L538:
	.align	2
.L537:
	.word	g_DSPState
	.word	g_HwMem
	.word	g_VdmDrvParam+48
	.word	g_BackUp
	.word	.LANCHOR0+672
	.word	.LC0
	.word	.LC1
	.word	.LC45
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_UpdateHardwareInfo, .-VDMHAL_V5R6C1_UpdateHardwareInfo
	.align	2
	.global	VDMHAL_V5R6C1_ReadMsgSlot
	.type	VDMHAL_V5R6C1_ReadMsgSlot, %function
VDMHAL_V5R6C1_ReadMsgSlot:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r3, r1
	moveq	r4, #1
	movne	r4, #0
	beq	.L543
	cmp	r2, #800
	bhi	.L544
	ldr	r3, .L545
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L544:
	mov	r0, r4
	ldr	r1, .L545+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L543:
	mov	r2, r0
	ldr	r1, .L545+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L546:
	.align	2
.L545:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LC46
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_ReadMsgSlot, .-VDMHAL_V5R6C1_ReadMsgSlot
	.align	2
	.global	VDMHAL_V5R6C1_WriteMsgSlot
	.type	VDMHAL_V5R6C1_WriteMsgSlot, %function
VDMHAL_V5R6C1_WriteMsgSlot:
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
	cmp	r1, #0
	cmpne	r0, #0
	moveq	r4, #1
	movne	r4, #0
	beq	.L548
	sub	r3, r2, #1
	cmp	r3, #255
	bhi	.L548
	ldr	r3, .L551
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L548:
	ldr	r1, .L551+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L552:
	.align	2
.L551:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC48
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_WriteMsgSlot, .-VDMHAL_V5R6C1_WriteMsgSlot
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	VDMHAL_V5R6C1_CfgRpMsg
	.type	VDMHAL_V5R6C1_CfgRpMsg, %function
VDMHAL_V5R6C1_CfgRpMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	mov	r8, r0
	ldr	r0, [r1, #48]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-60]
	beq	.L596
	ldr	r2, [r8, #44]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L597
	ldr	r0, [r8, #28]
	ldr	r3, [r8, #64]
	ldr	r2, [r8, #32]
	mov	r0, r0, asl r3
	ldr	ip, [r8, #4]
	cmp	r0, #1920
	add	r1, r0, #255
	mov	r3, r2, asl r3
	bic	r1, r1, #255
	bgt	.L594
	cmp	ip, #17
	movne	r2, #0
	strneb	r2, [r8]
	strneb	r2, [r8, #1]
	beq	.L594
.L560:
	cmp	ip, #16
	beq	.L561
.L599:
	add	r3, r3, #31
	mov	r0, #8
	bic	r3, r3, #31
	str	r0, [fp, #-80]
	mla	r3, r3, r1, r2
.L584:
	ldr	r0, [r8, #20]
	ldr	ip, [fp, #-60]
	str	r0, [ip]
	ldr	r0, [r8, #20]
	add	r0, r3, r0
	str	r0, [ip, #4]
	ldr	r0, [r8, #8]
	str	r0, [ip, #8]
	ldr	r0, [r8, #8]
	add	r3, r3, r0
	str	r3, [ip, #12]
	ldr	ip, [fp, #-60]
	mov	r0, #0	@ movhi
	ldrb	r3, [r8, #1]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r1, r1, asl #4
	str	r1, [ip, #16]
	str	r2, [ip, #20]
	mov	r1, r0	@ movhi
	ldr	r2, [r8, #28]
	ldr	r3, [r8, #32]
	sub	r2, r2, #1
	sub	r3, r3, #1
	bfi	r0, r2, #0, #9
	bfi	r1, r3, #0, #9
	strh	r0, [fp, #-52]	@ movhi
	strh	r1, [fp, #-50]	@ movhi
	ldr	r3, [fp, #-52]
	str	r3, [ip, #24]
	ldr	r3, [r8, #52]
	ldr	r1, [r8, #56]
	sub	r3, r3, #1
	ldr	r2, [r8, #28]
	cmp	r3, #1
	ldr	r3, [r8, #32]
	str	r2, [fp, #-76]
	addls	r3, r3, r3, lsr #31
	movls	r3, r3, asr #1
	cmp	r1, #0
	str	r3, [fp, #-84]
	movne	r3, #0
	strne	r3, [fp, #-64]
	beq	.L598
.L566:
	cmp	r1, #1
	beq	.L582
.L605:
	ldr	r3, [fp, #-64]
	sub	r3, r3, #1
	uxth	r3, r3
.L583:
	ldr	ip, [r8, #64]
	mov	r0, #0
	ldrb	r1, [fp, #-49]	@ zero_extendqisi2
	ldrb	lr, [r8]	@ zero_extendqisi2
	sub	ip, ip, #4
	ldrb	r2, [fp, #-50]	@ zero_extendqisi2
	bfi	r1, ip, #0, #2
	strh	r3, [fp, #-52]	@ movhi
	ldr	ip, [r8, #52]
	bfi	r2, lr, #0, #1
	ldr	r3, [fp, #-80]
	ldrb	lr, [r8, #1]	@ zero_extendqisi2
	and	ip, ip, #3
	bfi	r1, r3, #2, #4
	mov	r3, r2
	bfi	r3, ip, #4, #2
	bfi	r3, ip, #6, #2
	mov	r2, r1
	strb	r3, [fp, #-50]
	bfi	r2, lr, #6, #1
	strb	r2, [fp, #-49]
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-60]
	str	r3, [r2, #28]
.L593:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L594:
	ldrb	r2, [r8]	@ zero_extendqisi2
	cmp	r2, #1
	mov	r2, #0
	strb	r2, [r8, #1]
	bne	.L560
	add	r2, r0, #2032
	adds	lr, r3, #63
	add	r2, r2, #15
	add	r0, r0, #4080
	add	r0, r0, #14
	addmi	lr, r3, #126
	cmp	r2, #0
	movlt	r2, r0
	mov	r0, lr, asr #6
	mov	r2, r2, asr #11
	cmp	ip, #16
	mov	r0, r0, asl #5
	mov	r2, r2, asl #4
	mul	r2, r2, r0
	bne	.L599
.L561:
	mov	r0, #10
	str	r0, [fp, #-80]
	mla	r3, r1, r3, r2
	b	.L584
.L598:
	ldr	r3, [r8, #64]
	cmp	r3, #6
	moveq	r4, #2
	beq	.L567
	cmp	r3, #5
	moveq	r4, #4
	beq	.L567
	cmp	r3, #4
	moveq	r4, #8
	bne	.L600
.L567:
	ldr	r9, [r8, #44]
	cmp	r9, #0
	movle	r3, #0
	ldrle	r1, [r8, #56]
	strle	r3, [fp, #-64]
	ble	.L566
	ldr	r2, [fp, #-84]
	mov	r6, #0
	ldr	r3, [fp, #-76]
	str	r6, [fp, #-72]
	str	r6, [fp, #-64]
	mul	r3, r3, r2
	str	r8, [fp, #-56]
	sub	r2, r4, #1
	str	r2, [fp, #-88]
	str	r3, [fp, #-92]
	sub	r3, r3, #1
	str	r3, [fp, #-96]
	b	.L570
.L603:
	ldrsh	r0, [r5, #74]
	mov	r1, r4
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r3, r4, r0
	cmp	r7, r3
	str	r3, [fp, #-72]
	ldrgt	r7, [fp, #-88]
	bgt	.L573
.L572:
	add	r6, r6, #1
	cmp	r6, r9
	bge	.L601
.L581:
	cmp	r6, #199
	bgt	.L602
.L570:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r5, r3, r6, lsl #2
	ldrsh	r10, [r5, #78]
	ldrh	r3, [r5, #76]
	sub	r0, r10, #1
	add	r0, r0, r4
	str	r3, [fp, #-68]
	bl	__aeabi_uidiv
	cmp	r6, #0
	mul	r7, r4, r0
	bgt	.L603
	ldr	r3, [fp, #-72]
	cmp	r7, r3
	movgt	r3, #0
	movle	r3, #1
	cmp	r6, #0
	moveq	r3, #0
	cmp	r3, #0
	bne	.L572
.L575:
	ldrsh	r0, [fp, #-68]
	mov	r1, r4
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-92]
	ldr	r3, [fp, #-96]
	cmp	r2, r7
	movls	r7, r3
	ldr	r3, [fp, #-64]
	add	r3, r3, #1
	str	r3, [fp, #-64]
	mul	r5, r4, r0
	cmp	r5, r7
	movgt	r5, #0
	cmp	r3, #250
	bgt	.L604
	ldr	r8, [fp, #-76]
	mov	r0, r5
	add	r6, r6, #1
	mov	r1, r8
	bl	__aeabi_uidivmod
	mov	r0, r5
	mov	r3, #0	@ movhi
	bfi	r3, r1, #0, #9
	mov	r1, r8
	strh	r3, [fp, #-48]	@ movhi
	bl	__aeabi_uidiv
	mov	r2, #0	@ movhi
	ldr	r3, [fp, #-64]
	ldr	r9, [fp, #-60]
	mov	r1, r8
	add	r3, r3, #5
	mov	r5, r3, asl #3
	add	r5, r5, #4
	bfi	r2, r0, #0, #9
	strh	r2, [fp, #-46]	@ movhi
	ldr	r2, [fp, #-48]
	mov	r0, r7
	str	r2, [r9, r3, asl #3]
	bl	__aeabi_uidivmod
	mov	r0, r7
	mov	r3, #0	@ movhi
	bfi	r3, r1, #0, #9
	mov	r1, r8
	strh	r3, [fp, #-48]	@ movhi
	bl	__aeabi_uidiv
	mov	r3, #0	@ movhi
	bfi	r3, r0, #0, #9
	strh	r3, [fp, #-46]	@ movhi
	ldr	r3, [fp, #-48]
	str	r3, [r9, r5]
	ldr	r3, [fp, #-56]
	ldr	r9, [r3, #44]
	cmp	r6, r9
	blt	.L581
.L601:
	ldr	r8, [fp, #-56]
	ldr	r1, [r8, #56]
	cmp	r1, #1
	bne	.L605
.L582:
	ldr	r3, [fp, #-76]
	mov	ip, #0	@ movhi
	str	r1, [r8, #44]
	sub	r2, r3, #1
	ldr	r3, [fp, #-84]
	ldr	r1, [fp, #-60]
	sub	r0, r3, #1
	mov	r3, #0
	bfi	ip, r3, #0, #9
	strh	ip, [fp, #-52]	@ movhi
	mov	ip, #0	@ movhi
	bfi	ip, r3, #0, #9
	strh	ip, [fp, #-50]	@ movhi
	mov	ip, #0	@ movhi
	ldr	lr, [fp, #-52]
	bfi	ip, r2, #0, #9
	mov	r2, #0	@ movhi
	strh	ip, [fp, #-52]	@ movhi
	bfi	r2, r0, #0, #9
	strh	r2, [fp, #-50]	@ movhi
	ldr	r2, [fp, #-52]
	str	lr, [r1, #48]
	str	r2, [r1, #52]
	b	.L583
.L576:
	bl	__aeabi_uidiv
	mov	r1, r4
	mul	r10, r4, r0
	ldrsh	r0, [r5, #80]
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r10, r0
	add	r3, r0, #1
	bhi	.L577
	cmp	r10, r3
	mov	r1, r4
	beq	.L577
	ldrsh	r0, [r5, #74]
	add	r0, r0, r7
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r10, r0
	bhi	.L606
.L577:
	cmp	r8, #198
	mov	r6, r8
	add	r5, r5, #4
	bgt	.L607
	ldrsh	r10, [r5, #78]
.L573:
	add	r8, r6, #1
	mov	r1, r4
	cmp	r8, r9
	add	r0, r7, r10
	blt	.L576
	ldr	r3, [fp, #-88]
	add	r0, r3, r10
	bl	__aeabi_uidiv
	mul	r7, r4, r0
	b	.L575
.L607:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r2, r3, r8, lsl #2
	ldrsh	r0, [r2, #78]
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r7, r4, r0
	b	.L575
.L606:
	mov	r7, r10
	b	.L575
.L602:
	ldr	r8, [fp, #-56]
	mov	r0, #0
	ldr	r1, .L608
	movw	r3, #2152
	str	r6, [sp]
	ldr	r2, .L608+4
	str	r0, [fp, #-64]
	bl	dprint_vfmw
	ldr	r1, [r8, #56]
	b	.L566
.L600:
	ldr	r1, .L608+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r4, #1
	b	.L567
.L604:
	ldr	r8, [fp, #-56]
	mov	r1, #1
	str	r1, [r8, #56]
	b	.L582
.L597:
	ldr	r1, .L608+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L593
.L596:
	ldr	r3, .L608+16
	ldr	r2, .L608+20
	ldr	r1, .L608+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L593
.L609:
	.align	2
.L608:
	.word	.LC52
	.word	.LANCHOR0+732
	.word	.LC51
	.word	.LC50
	.word	.LC49
	.word	.LANCHOR0+708
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CfgRpMsg, .-VDMHAL_V5R6C1_CfgRpMsg
	.align	2
	.global	VDMHAL_V5R6C1_MakeDecReport
	.type	VDMHAL_V5R6C1_MakeDecReport, %function
VDMHAL_V5R6C1_MakeDecReport:
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
	subs	r3, r0, #0
	beq	.L639
	ldr	r5, [r3, #4]
	ldr	r8, [r3]
	cmp	r5, #0
	ldr	r6, [r3, #8]
	beq	.L640
	movw	r3, #1228
	ldr	r7, .L648
	mul	r3, r3, r6
	ldr	r0, [r7, r3]
	cmp	r0, #0
	beq	.L614
	ldr	r3, .L648+4
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #124
	bne	.L617
	b	.L629
.L642:
	cmp	r3, r1
	beq	.L641
.L617:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	bne	.L642
.L629:
	mov	r4, r2
.L615:
	ldr	r3, .L648+8
	mov	r2, #824
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r3, #48]
	blx	r3
	movw	r3, #1228
	mla	r3, r3, r6, r7
	ldr	r1, .L648+12
	mov	r2, #180
	mla	r2, r2, r6, r1
	ldr	r3, [r3, #24]
	str	r3, [r5, #4]
	ldr	r3, [r2, #4]
	mov	r3, r3, lsr #17
	and	r2, r3, #3
	cmp	r2, #1
	moveq	r3, #0
	beq	.L618
	eor	r3, r3, #1
	and	r3, r3, #1
	cmp	r8, #3
	orrne	r3, r3, #1
.L618:
	mov	r2, #180
	str	r3, [r5]
	mla	r3, r2, r6, r1
	cmp	r8, #0
	cmpne	r8, #15
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #0, #17
	str	r2, [r5, #12]
	beq	.L643
.L619:
	cmp	r2, #200
	bhi	.L644
.L621:
	movw	r3, #1228
	mla	r7, r3, r6, r7
	ldr	r8, [r7, #40]
	mov	r0, r8
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L645
	mov	r9, #3200
	ldr	r7, .L648+16
	mul	r9, r9, r6
	ldr	r2, [r5, #12]
	add	r4, r7, r9
	mov	r2, r2, asl #2
	mov	r0, r4
	bl	VDMHAL_V5R6C1_ReadMsgSlot
	ldr	ip, [r5, #12]
	ldr	r3, [r7, r9]
	cmp	ip, #0
	mov	r3, r3, lsr #31
	movne	r0, r4
	str	r3, [r5, #16]
	movne	r2, #0
	movne	r3, r5
	beq	.L626
.L625:
	ldr	r1, [r0, #4]
	add	r2, r2, #1
	cmp	r2, ip
	add	r0, r0, #16
	add	r3, r3, #4
	strh	r1, [r3, #16]	@ movhi
	ldr	r1, [r0, #-8]
	strh	r1, [r3, #18]	@ movhi
	bne	.L625
.L626:
	mov	r0, #6
	bl	IsDprintTypeEnable
	cmp	r0, #0
	bne	.L646
.L612:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L643:
	cmp	r4, #1
	beq	.L647
	ldr	r1, .L648+20
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L619
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L619
	mov	r3, #1
	strh	r1, [r5, #20]	@ movhi
	mov	r0, r1
	strh	r1, [r5, #22]	@ movhi
	str	r3, [r5, #12]
	b	.L612
.L641:
	mov	r4, #0
	b	.L615
.L646:
	ldr	r2, [r5, #12]
	mov	r0, #6
	ldr	r1, .L648+24
	mov	r4, #0
	bl	dprint_vfmw
	mov	r2, r8
	ldr	r1, .L648+28
	mov	r0, #6
	bl	dprint_vfmw
	mov	r3, #3200
	mla	r6, r3, r6, r7
.L627:
	ldr	r1, [r6, #4]
	ldr	lr, [r6, #12]
	mov	r2, r4
	ldr	ip, [r6, #8]
	mov	r0, #6
	ldr	r3, [r6]
	add	r4, r4, #4
	str	r1, [sp]
	add	r6, r6, #16
	str	lr, [sp, #8]
	str	ip, [sp, #4]
	ldr	r1, .L648+32
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r3, r3, asl #2
	sub	r3, r3, #3
	cmp	r3, r4
	bhi	.L627
	ldr	r1, .L648+36
	mov	r0, #6
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L644:
	mov	r3, #200
	ldr	r1, .L648+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5, #12]
	b	.L621
.L647:
	ldr	r3, [r3, #16]
	ubfx	r3, r3, #21, #2
	cmp	r3, #2
	bne	.L619
	mov	r3, #0
	str	r4, [r5, #12]
	strh	r3, [r5, #20]	@ movhi
	mov	r0, r3
	strh	r3, [r5, #22]	@ movhi
	b	.L612
.L645:
	ldr	r3, .L648+44
	ldr	r2, .L648+48
	ldr	r1, .L648+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L612
.L614:
	ldr	r3, .L648+56
	ldr	r2, .L648+48
	ldr	r1, .L648+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L612
.L640:
	mov	r0, r5
	ldr	r3, .L648+60
	ldr	r2, .L648+48
	ldr	r1, .L648+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L612
.L639:
	ldr	r3, .L648+64
	ldr	r2, .L648+48
	ldr	r1, .L648+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L612
.L649:
	.align	2
.L648:
	.word	g_HwMem
	.word	g_DSPState
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_BackUp
	.word	g_UpMsg
	.word	g_not_allow_H264FullPictureRepair_flag
	.word	.LC56
	.word	.LC57
	.word	.LC58
	.word	.LC59
	.word	.LC55
	.word	.LC45
	.word	.LANCHOR0+756
	.word	.LC3
	.word	.LC43
	.word	.LC54
	.word	.LC53
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_MakeDecReport, .-VDMHAL_V5R6C1_MakeDecReport
	.align	2
	.global	VDMHAL_V5R6C1_PrepareRepair
	.type	VDMHAL_V5R6C1_PrepareRepair, %function
VDMHAL_V5R6C1_PrepareRepair:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	movw	r4, #1228
	mul	r4, r4, r3
	ldr	r5, .L665
	cmp	r3, #0
	mov	r6, r3
	mov	r8, r0
	add	r7, r4, r5
	bgt	.L661
	ldr	r3, [r4, r5]
	cmp	r3, #0
	beq	.L662
.L653:
	cmp	r2, #0
	beq	.L663
	cmp	r2, #1
	movne	r0, #0
	beq	.L664
.L652:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L663:
	ldr	r4, .L665+4
	movw	r3, #1752
	mla	r3, r3, r6, r4
	ldr	r0, [r3, #44]
	cmp	r0, #0
	ble	.L656
	cmp	r8, #6
	bne	.L657
	ldrb	r1, [r1, #17]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r2, r1
	str	r2, [r3, #928]
.L657:
	ldr	r3, [fp, #4]
	mov	r2, r6
	add	r1, r7, #48
	mov	r0, r7
	bl	VDMHAL_V5R6C1_CfgRpReg.isra.9
	movw	r0, #1752
	mov	r1, r7
	mov	r2, r6
	mla	r0, r0, r6, r4
	bl	VDMHAL_V5R6C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L664:
	cmp	r8, #6
	bne	.L659
	ldrb	r3, [r1, #17]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L659
	movw	r4, #1752
	ldr	r5, .L665+4
	mul	r4, r4, r6
	add	r0, r5, r4
	ldr	r3, [r0, #920]
	cmp	r3, #0
	ble	.L659
	mov	ip, #2
	ldr	r3, [fp, #4]
	str	ip, [r0, #928]
	mov	r2, r6
	add	r1, r7, #48
	mov	r0, r7
	bl	VDMHAL_V5R6C1_CfgRpReg.isra.9
	add	r0, r4, #876
	add	r0, r5, r0
	mov	r2, r6
	mov	r1, r7
	bl	VDMHAL_V5R6C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L662:
	mov	r0, #0
	str	r2, [fp, #-44]
	movt	r0, 63683
	str	r1, [fp, #-40]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L654
	str	r3, [r4, r5]
	ldr	r1, [fp, #-40]
	ldr	r2, [fp, #-44]
	b	.L653
.L661:
	mov	r0, #0
	ldr	r2, .L665+8
	str	r0, [sp]
	ldr	r1, .L665+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L652
.L659:
	ldr	r1, .L665+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L652
.L656:
	mov	r0, r2
	ldr	r1, .L665+20
	str	r2, [fp, #-40]
	bl	dprint_vfmw
	ldr	r2, [fp, #-40]
	mov	r0, r2
	b	.L652
.L654:
	ldr	r1, .L665+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L652
.L666:
	.align	2
.L665:
	.word	g_HwMem
	.word	g_RepairParam
	.word	.LANCHOR0+784
	.word	.LC0
	.word	.LC62
	.word	.LC61
	.word	.LC60
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_PrepareRepair, .-VDMHAL_V5R6C1_PrepareRepair
	.align	2
	.global	VDMHAL_V5R6C1_StartHwRepair
	.type	VDMHAL_V5R6C1_StartHwRepair, %function
VDMHAL_V5R6C1_StartHwRepair:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	ldr	r6, .L697
	mov	r5, r0
	mov	r4, r1
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L691
	cmp	r0, #0
	ble	.L692
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L697+4
	mov	r0, #32
	ldr	r1, .L697+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L693
.L675:
	mov	r2, #1
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L697+4
	ldr	r1, .L697+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L687
.L670:
	cmp	r4, #0
	beq	.L694
	mov	r3, r5, asl #6
	ldr	r2, .L697+12
	sub	r3, r3, r5, asl #3
	mov	r1, #1
	add	r3, r2, r3
	str	r1, [r4, #4]
	mov	r0, r4
	ldr	r3, [r3, #8]
	strb	r1, [r4, #2]
	strb	r5, [r4]
	str	r3, [r4, #8]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	VDH_PostTask
.L692:
	movw	r3, #1228
	ldr	r4, .L697+16
	mul	r3, r3, r0
	mov	r2, #67108864
	ldr	r3, [r4, r3]
	str	r2, [r3, #8]
.L673:
	movw	r3, #1228
	ldr	r2, .L697+20
	mul	r3, r3, r5
	mvn	r1, #1
	ldr	r3, [r4, r3]
	str	r1, [r3, #36]
	ldr	r3, [r2, #112]
	blx	r3
.L682:
	movw	r3, #1228
	mov	r2, #0
	mul	r5, r3, r5
	mov	r1, #1
	ldr	r3, [r4, r5]
	str	r2, [r3]
	ldr	r3, [r4, r5]
	str	r1, [r3]
	ldr	r3, [r4, r5]
	str	r2, [r3]
.L667:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L691:
	mov	r3, #67108864
	mov	r2, #8
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L695
	cmp	r5, #0
	ldrle	r4, .L697+16
	bgt	.L675
	b	.L673
.L695:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L670
	ldr	r3, .L697+20
	ldr	r3, [r3, #112]
	blx	r3
	cmp	r5, #0
	ble	.L696
.L679:
	mov	r4, #1
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L697+24
	ldr	r1, .L697+8
	bl	dprint_vfmw
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L697+24
	ldr	r1, .L697+8
	bl	dprint_vfmw
	str	r4, [sp]
	mov	r3, r5
	ldr	r2, .L697+24
	ldr	r1, .L697+8
	mov	r0, #32
	bl	dprint_vfmw
	b	.L667
.L693:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L670
.L687:
	ldr	r3, .L697+20
	ldr	r3, [r3, #112]
	blx	r3
	b	.L679
.L694:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L697+24
	ldr	r1, .L697+28
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L696:
	ldr	r4, .L697+16
	b	.L682
.L698:
	.align	2
.L697:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC34
	.word	g_VdmDrvParam
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+828
	.word	.LC63
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_StartHwRepair, .-VDMHAL_V5R6C1_StartHwRepair
	.align	2
	.global	VDMHAL_V5R6C1_CalVdhClkSkip
	.type	VDMHAL_V5R6C1_CalVdhClkSkip, %function
VDMHAL_V5R6C1_CalVdhClkSkip:
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
	ldr	r9, .L729
	ldr	r10, [r9, #128]
	cmp	r10, #0
	blt	.L721
	mov	r7, #0
	add	r4, r9, #128
	mov	r6, r7
	mov	r5, r7
	add	r9, r9, #252
	mov	r8, #30
	b	.L701
.L728:
	mov	r3, r10
	ldr	r2, .L729+4
	ldr	r1, .L729+8
	mov	r0, #1
	bl	dprint_vfmw
.L703:
	cmp	r4, r9
	beq	.L727
.L720:
	ldr	r10, [r4, #4]!
	cmp	r10, #0
	blt	.L727
.L701:
	mov	r0, r10
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L728
	mov	r0, r10
	bl	FSP_GetInst
	cmp	r0, #0
	beq	.L704
	ldr	r1, [r0, #40]
	ldr	r2, [r0, #44]
	adds	r5, r1, #15
	addmi	r5, r1, #30
	adds	r6, r2, #15
	addmi	r6, r2, #30
	mov	r5, r5, asr #4
	mov	r6, r6, asr #4
.L704:
	ldr	r3, .L729+12
	mov	r0, r10
	ldr	r2, [r3, r10, asl #2]
	ldr	r3, [r2, #1536]
	cmp	r3, #30
	movgt	r8, r3
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L722
.L707:
	.word	.L716
	.word	.L716
	.word	.L716
	.word	.L716
	.word	.L722
	.word	.L716
	.word	.L716
	.word	.L722
	.word	.L716
	.word	.L716
	.word	.L716
	.word	.L716
	.word	.L716
	.word	.L716
	.word	.L722
	.word	.L717
	.word	.L716
	.word	.L716
.L716:
	mul	r7, r6, r5
	cmp	r4, r9
	mul	r7, r7, r8
	bne	.L720
.L727:
	mov	r2, r7, asl #8
	movw	r3, #23813
	sub	r7, r2, r7, asl #6
	movt	r3, 56143
	umull	r2, r3, r7, r3
	mov	r0, r3, lsr #21
	rsb	r0, r0, #32
	cmp	r0, #25
	movge	r0, #25
	bic	r0, r0, r0, asr #31
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L717:
	mul	r7, r6, r5
	mul	r7, r7, r8
	mov	r7, r7, asl #1
	b	.L703
.L722:
	mov	r7, #0
	b	.L703
.L721:
	mov	r0, #25
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L730:
	.align	2
.L729:
	.word	g_ChanCtx
	.word	.LANCHOR0+856
	.word	.LC64
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_CalVdhClkSkip, .-VDMHAL_V5R6C1_CalVdhClkSkip
	.align	2
	.global	VDMHAL_V5R6C1_GetVdmClk
	.type	VDMHAL_V5R6C1_GetVdmClk, %function
VDMHAL_V5R6C1_GetVdmClk:
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
	mov	r3, r0, asl #6
	ldr	r2, .L739
	sub	r0, r3, r0, asl #3
	cmp	r1, #3
	ldrls	pc, [pc, r1, asl #2]
	b	.L732
.L734:
	.word	.L732
	.word	.L735
	.word	.L736
	.word	.L737
.L732:
	add	r3, r2, r0
	mov	r1, #500
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L736:
	add	r3, r2, r0
	mov	r1, #100
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L735:
	add	r3, r2, r0
	mov	r1, #540
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L737:
	add	r3, r2, r0
	mov	r1, #600
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L740:
	.align	2
.L739:
	.word	g_VdmDrvParam
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetVdmClk, .-VDMHAL_V5R6C1_GetVdmClk
	.align	2
	.global	VDMHAL_V5R6C1_StartHwDecode
	.type	VDMHAL_V5R6C1_StartHwDecode, %function
VDMHAL_V5R6C1_StartHwDecode:
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
	subs	r4, r0, #0
	mov	r3, #8
	mov	r5, r1
	str	r3, [fp, #-48]
	ble	.L742
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L775
	ldr	r1, .L775+4
	bl	dprint_vfmw
.L741:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L742:
	ldr	r6, .L775+8
	sub	r0, fp, #48
	bl	HI_DRV_SYS_GetChipPackageType
	ldr	r7, [fp, #-48]
	ldrb	r3, [r6]	@ zero_extendqisi2
	adds	r7, r7, #0
	movne	r7, #1
	cmp	r3, #1
	bne	.L771
	ldr	r3, .L775+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	ubfx	r1, r3, #8, #2
	cmp	r1, r7
	bfine	r3, r7, #8, #2
	strne	r3, [r2, #120]
.L745:
	mov	r1, r7
	mov	r0, r4
	bl	VDMHAL_V5R6C1_GetVdmClk
	ldr	r7, .L775+16
	mov	r3, r4, asl #6
	ldr	r2, .L775+20
	sub	r3, r3, r4, asl #3
	ldrb	r1, [r6]	@ zero_extendqisi2
	add	r3, r7, r3
	cmp	r1, #1
	ldr	r8, [r3, #8]
	ldr	r3, [r2, r8, asl #2]
	ldr	r9, [r3, #1208]
	bne	.L772
	ldr	r3, .L775+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
.L748:
	mov	r2, r4
	mov	r3, r5
	mov	r1, #3
	mov	r0, #12
	bl	SCD_ConfigReg
	ldrb	r2, [r6]	@ zero_extendqisi2
	ldr	r10, .L775+8
	cmp	r2, #1
	bne	.L773
	movw	r2, #1228
	ldr	r3, .L775+24
	mul	r2, r2, r4
	ldr	r5, .L775+28
	ldr	r1, [r3]
	movw	r3, #43690
	bfi	r3, r3, #16, #16
	cmp	r1, #1
	ldr	r2, [r5, r2]
	moveq	r1, #15
	movne	r1, #0
	str	r3, [r2, #156]
.L750:
	movw	r2, #1228
	cmp	r9, #1
	mul	r2, r2, r4
	mvneq	r3, #5
	mvnne	r3, #1
	ldr	r2, [r5, r2]
	add	r2, r2, #61440
	str	r1, [r2, #32]
.L752:
	movw	r2, #1228
	mul	r2, r2, r4
	ldr	r2, [r5, r2]
	str	r3, [r2, #36]
.L754:
	ldr	r6, .L775+32
	mov	r0, #30
	ldr	r3, [r6, #116]
	blx	r3
	ldr	r3, [r6, #112]
	blx	r3
	movw	r3, #1228
	mul	r3, r3, r4
	mov	r1, #56
	mov	r2, #0
	mov	lr, #1
	mla	r4, r1, r4, r7
	ldr	ip, .L775+36
	mov	r1, #4
	ldr	r0, [r5, r3]
	str	r2, [r0]
	ldr	r0, [r5, r3]
	str	lr, [r0]
	ldr	r3, [r5, r3]
	str	r2, [r3]
	ldr	r0, [r4, #8]
	ldr	r2, [ip, r0, asl #2]
	bl	VDEC_Lowdelay_Event_Time
	b	.L741
.L773:
	movw	r3, #43690
	mov	r1, #2
	mov	r2, #156
	movt	r3, 43690
	mov	r0, r5
	bl	VDH_Record_RegData
	ldr	r3, .L775+24
	ldrb	r2, [r10]	@ zero_extendqisi2
	ldr	r3, [r3]
	cmp	r3, #1
	moveq	r1, #15
	movne	r1, #0
	cmp	r2, #1
	ldreq	r5, .L775+28
	beq	.L750
	mov	r3, r1
	movw	r2, #61472
	mov	r0, r5
	mov	r1, #2
	bl	VDH_Record_RegData
	cmp	r9, #1
	ldrb	r2, [r6]	@ zero_extendqisi2
	mvneq	r3, #5
	mvnne	r3, #1
	cmp	r2, #1
	ldreq	r5, .L775+28
	beq	.L752
	mov	r0, r5
	mov	r2, #36
	mov	r1, #2
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r5, .L775+28
	beq	.L754
	cmp	r5, #0
	beq	.L774
	mov	r3, #1
	str	r8, [r5, #8]
	strb	r4, [r5]
	mov	r0, r5
	str	r3, [r5, #4]
	bl	VDH_PostTask
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L772:
	mov	r3, #0
	mov	r2, #1
	mov	r1, r3
	mov	r0, r5
	bl	VDH_Record_RegData
	b	.L748
.L771:
	mov	r2, #0
	mov	r3, r7
	mov	r1, r2
	mov	r0, r5
	bl	VDH_Record_RegData
	b	.L745
.L774:
	mov	r3, r5
	mov	r0, r5
	ldr	r2, .L775
	ldr	r1, .L775+40
	bl	dprint_vfmw
	b	.L741
.L776:
	.align	2
.L775:
	.word	.LANCHOR0+884
	.word	.LC0
	.word	g_HalDisable
	.word	g_pstRegCrg
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	mask_mmu_err_int
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_LowDelaySeqIndex
	.word	.LC63
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_StartHwDecode, .-VDMHAL_V5R6C1_StartHwDecode
	.align	2
	.global	VDMHAL_V5R6C1_GetCharacter
	.type	VDMHAL_V5R6C1_GetCharacter, %function
VDMHAL_V5R6C1_GetCharacter:
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
	ldr	r1, .L778
	mov	r0, #15
	ldr	r3, .L778+4
	mov	r2, #4
	str	r0, [r1]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L779:
	.align	2
.L778:
	.word	g_VdmCharacter
	.word	g_eVdmVersion
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_GetCharacter, .-VDMHAL_V5R6C1_GetCharacter
	.align	2
	.global	VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.type	VDMHAL_V5R6C1_WriteBigTitle1DYuv, %function
VDMHAL_V5R6C1_WriteBigTitle1DYuv:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 88
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #100)
	sub	sp, sp, #100
	ubfx	ip, r3, #29, #2
	cmp	ip, #1
	mov	r6, r3
	mov	r3, #0
	str	r0, [fp, #-108]
	mov	r8, r1
	mov	r5, r2
	str	r3, [fp, #-92]
	moveq	r4, r3
	str	r3, [fp, #-88]
	str	r3, [fp, #-84]
	str	r3, [fp, #-80]
	str	r3, [fp, #-76]
	str	r3, [fp, #-72]
	str	r3, [fp, #-68]
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	beq	.L781
	cmp	ip, #2
	moveq	r4, #1
	movne	r4, #2
.L781:
	ldr	r3, [fp, #-108]
	cmp	r3, #0
	beq	.L780
	mov	r3, #0
	mov	r2, #4194304
	mov	r1, r3
	str	r3, [sp]
	ldr	r0, .L870
	sub	r3, fp, #92
	bl	MEM_AllocMemBlock
	subs	r1, r0, #0
	bne	.L784
	str	r1, [sp]
	mov	r2, #4194304
	sub	r3, fp, #68
	ldr	r0, .L870+4
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L784
	add	r6, r6, #15
	add	r5, r5, #15
	bic	r3, r6, #15
	str	r3, [fp, #-100]
	bic	r5, r5, #15
	mov	r1, r3
	adds	r3, r3, #31
	addmi	r3, r1, #62
	add	r2, r5, #255
	bic	r2, r2, #255
	cmp	r4, #0
	cmpne	r4, #3
	mov	r3, r3, asr #5
	mov	r1, r2, asl #4
	str	r1, [fp, #-104]
	mla	r3, r3, r2, r8
	str	r3, [fp, #-116]
	bne	.L785
	ldr	r3, [fp, #-100]
	mov	r1, r5, lsr #1
	ldr	r2, [fp, #-64]
	cmp	r3, #0
	ldr	r6, .L870+8
	mov	r3, r3, lsr #1
	ldr	r7, [fp, #-88]
	str	r2, [fp, #-120]
	movne	r10, r0
	add	r2, r2, #2097152
	str	r1, [fp, #-124]
	str	r2, [fp, #-128]
	str	r3, [fp, #-112]
	strne	r10, [fp, #-96]
	beq	.L787
.L786:
	cmp	r5, #0
	beq	.L789
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	ldr	r2, [fp, #-104]
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L788:
	mov	r1, r4, lsr #8
	add	r0, r10, r4
	add	r0, r7, r0
	add	r4, r4, #256
	add	r1, r9, r1, lsl #12
	ldr	r3, [r6, #52]
	add	r1, r8, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L788
.L789:
	ldr	r3, [fp, #-96]
	add	r10, r10, r5
	ldr	r2, [fp, #-100]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r2, r3
	bne	.L786
.L787:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	ldr	r3, [r6, #44]
	blx	r3
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L790
	ldr	r3, [fp, #-104]
	mov	r9, #0
	ldr	r10, [fp, #-116]
	str	r9, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L791:
	cmp	r5, #0
	beq	.L794
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L792:
	mov	r1, r4, lsr #8
	add	r0, r9, r4
	add	r0, r7, r0
	add	r4, r4, #256
	add	r1, r8, r1, lsl #11
	ldr	r3, [r6, #52]
	add	r1, r10, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L792
.L794:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L791
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L868
.L796:
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L797
	ldr	r3, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-128]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-120]
	blx	r3
.L797:
	ldr	r3, [fp, #-124]
.L867:
	ldr	r2, [fp, #-112]
	ldr	r5, [fp, #-108]
	ldr	r0, [fp, #-120]
	mul	r4, r3, r2
	ldr	r3, [r6, #44]
	mov	r2, r5
	mov	r1, r4
	blx	r3
	mov	r2, r5
	ldr	r3, [r6, #44]
	mov	r1, r4
	ldr	r0, [fp, #-128]
	blx	r3
	ldr	r1, [fp, #-88]
	ldr	r0, [fp, #-84]
	bl	MEM_ReleaseMemBlock
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #92
	blx	r3
	ldr	r1, [fp, #-64]
	ldr	r0, [fp, #-60]
	bl	MEM_ReleaseMemBlock
	ldr	r3, [r6, #48]
	sub	r0, fp, #68
	mov	r2, #24
	mov	r1, #0
	blx	r3
.L780:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L784:
	ldr	r1, .L870+12
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L785:
	subs	r3, r4, #1
	ldr	r1, [fp, #-100]
	ldr	r2, [fp, #-64]
	movne	r3, #1
	cmp	r1, r3
	str	r3, [fp, #-124]
	add	r3, r2, #2097152
	str	r3, [fp, #-128]
	mov	r3, r5, lsr #1
	str	r3, [fp, #-132]
	mov	r3, r1, lsr #1
	str	r3, [fp, #-112]
	ldrhi	r3, [fp, #-124]
	str	r2, [fp, #-120]
	ldr	r6, .L870+8
	ldr	r7, [fp, #-88]
	strhi	r3, [fp, #-96]
	bls	.L804
.L806:
	cmp	r5, #0
	beq	.L807
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	mov	r10, r2, lsr #1
	ldr	r2, [fp, #-104]
	mul	r10, r5, r10
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L805:
	mov	r1, r4, lsr #8
	add	r0, r4, r10
	add	r0, r7, r0
	add	r4, r4, #256
	add	r1, r9, r1, lsl #12
	ldr	r3, [r6, #52]
	add	r1, r8, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L805
.L807:
	ldr	r3, [fp, #-96]
	ldr	r2, [fp, #-100]
	add	r3, r3, #2
	str	r3, [fp, #-96]
	cmp	r2, r3
	bhi	.L806
.L804:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	ldr	r3, [r6, #44]
	mov	r1, r1, lsr #1
	blx	r3
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L808
	ldr	r3, [fp, #-104]
	mov	r9, #0
	ldr	r10, [fp, #-116]
	str	r9, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L809:
	cmp	r5, #0
	beq	.L812
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L810:
	mov	r1, r4, lsr #8
	add	r0, r9, r4
	add	r0, r7, r0
	add	r4, r4, #256
	add	r1, r8, r1, lsl #11
	ldr	r3, [r6, #52]
	add	r1, r10, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L810
.L812:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L809
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L869
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L815
	ldr	r2, [fp, #-112]
	ldr	r3, [fp, #-124]
	cmp	r2, r3
	bls	.L820
.L821:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L821
.L820:
	ldr	r3, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-128]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-120]
	blx	r3
.L815:
	ldr	r3, [fp, #-132]
	b	.L867
.L868:
	ldr	r3, [fp, #-120]
	add	r7, r7, #1
	ldr	r4, [fp, #-124]
	mov	lr, #0
	ldr	r8, [fp, #-112]
.L798:
	cmp	r4, #0
	moveq	ip, r3
	beq	.L801
	sub	r1, r3, #-67108863
	add	ip, r3, r4
	sub	r1, r1, #65011712
	mov	r2, r7
.L799:
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	strb	r0, [r1, #1]!
	ldrb	r0, [r2], #2	@ zero_extendqisi2
	strb	r0, [r3], #1
	cmp	r3, ip
	bne	.L799
.L801:
	add	lr, lr, #1
	mov	r3, ip
	cmp	lr, r8
	add	r7, r7, r5
	bne	.L798
	b	.L797
.L869:
	ldr	r3, [fp, #-124]
	mov	r4, #0
	ldr	lr, [fp, #-120]
	ldr	ip, [fp, #-132]
	mla	r3, r5, r3, r7
	ldr	r7, [fp, #-112]
	mov	r5, r5, asl #1
	add	r3, r3, #1
.L816:
	cmp	ip, #0
	beq	.L819
	mov	r2, r4, lsr #1
	mov	r1, r3
	mul	r2, ip, r2
	sub	r0, r2, #-67108863
	add	r9, r2, ip
	sub	r0, r0, #65011712
	add	r9, lr, r9
	add	r0, lr, r0
	add	r2, lr, r2
.L817:
	ldrb	r8, [r1, #-1]	@ zero_extendqisi2
	strb	r8, [r0, #1]!
	ldrb	r8, [r1], #2	@ zero_extendqisi2
	strb	r8, [r2], #1
	cmp	r2, r9
	bne	.L817
.L819:
	add	r4, r4, #2
	add	r3, r3, r5
	cmp	r7, r4
	bhi	.L816
	b	.L815
.L790:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	bne	.L796
	b	.L797
.L808:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L815
	cmp	r3, #0
	beq	.L820
	b	.L815
.L871:
	.align	2
.L870:
	.word	.LC65
	.word	.LC67
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC66
	UNWIND(.fnend)
	.size	VDMHAL_V5R6C1_WriteBigTitle1DYuv, .-VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.align	2
	.global	CRG_ConfigReg
	.type	CRG_ConfigReg, %function
CRG_ConfigReg:
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
	ldr	ip, .L879
	mov	lr, r2
	ldrb	r2, [ip]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L878
	cmp	r0, #0
	bne	.L874
	ldr	r3, .L879+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	ubfx	r0, r2, #8, #2
	cmp	r1, r0
	bfine	r2, r1, #8, #2
	strne	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L874:
	cmp	r0, #1
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L879+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	bfi	r2, r1, #12, #5
	bfc	r2, #17, #1
	str	r2, [r3, #120]
	ldr	r2, [r3, #120]
	orr	r2, r2, #131072
	str	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L878:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #0
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L880:
	.align	2
.L879:
	.word	g_HalDisable
	.word	g_pstRegCrg
	UNWIND(.fnend)
	.size	CRG_ConfigReg, .-CRG_ConfigReg
	.align	2
	.global	MFDE_ConfigReg
	.type	MFDE_ConfigReg, %function
MFDE_ConfigReg:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	ip, .L887
	mov	lr, r3
	ldrb	r3, [ip]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L885
	cmp	r2, #0
	ble	.L886
	str	r3, [sp]
	mov	r0, #32
	mov	r3, r2
	ldr	r1, .L887+4
	ldr	r2, .L887+8
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L886:
	movw	r3, #1228
	ldr	ip, .L887+12
	mul	r2, r3, r2
	ldr	r3, [ip, r2]
	str	r1, [r3, r0]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L885:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #2
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L888:
	.align	2
.L887:
	.word	g_HalDisable
	.word	.LC34
	.word	.LANCHOR0+812
	.word	g_HwMem
	UNWIND(.fnend)
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.59016, %object
	.size	__func__.59016, 23
__func__.59016:
	.ascii	"VDMHAL_V5R6C1_CfgRpReg\000"
	.space	1
	.type	__func__.58516, %object
	.size	__func__.58516, 22
__func__.58516:
	.ascii	"VDMHAL_V5R6C1_OpenHAL\000"
	.space	2
	.type	__func__.58589, %object
	.size	__func__.58589, 25
__func__.58589:
	.ascii	"VDMHAL_V5R6C1_CalcFsSize\000"
	.space	3
	.type	__func__.58615, %object
	.size	__func__.58615, 24
__func__.58615:
	.ascii	"VDMHAL_V5R6C1_CalcFsNum\000"
	.type	__func__.58658, %object
	.size	__func__.58658, 32
__func__.58658:
	.ascii	"VDMHAL_V5R6C1_ArrangeMem_Normal\000"
	.type	__FUNCTION__.58659, %object
	.size	__FUNCTION__.58659, 32
__FUNCTION__.58659:
	.ascii	"VDMHAL_V5R6C1_ArrangeMem_Normal\000"
	.type	__func__.58601, %object
	.size	__func__.58601, 33
__func__.58601:
	.ascii	"VDMHAL_V5R6C1_FillMemArrangeInfo\000"
	.space	3
	.type	__func__.58741, %object
	.size	__func__.58741, 34
__func__.58741:
	.ascii	"VDMHAL_V5R6C1_ArrangeMem_Specific\000"
	.space	2
	.type	__func__.58764, %object
	.size	__func__.58764, 23
__func__.58764:
	.ascii	"VDMHAL_V5R6C1_ResetVdm\000"
	.space	1
	.type	__func__.58774, %object
	.size	__func__.58774, 35
__func__.58774:
	.ascii	"VDMHAL_V5R6C1_SetSmmuPageTableAddr\000"
	.space	1
	.type	__func__.58794, %object
	.size	__func__.58794, 24
__func__.58794:
	.ascii	"VDMHAL_V5R6C1_GlbResetX\000"
	.type	__func__.58784, %object
	.size	__func__.58784, 23
__func__.58784:
	.ascii	"VDMHAL_V5R6C1_GlbReset\000"
	.space	1
	.type	__func__.58806, %object
	.size	__func__.58806, 28
__func__.58806:
	.ascii	"VDMHAL_V5R6C1_ClearIntState\000"
	.type	__func__.58812, %object
	.size	__func__.58812, 31
__func__.58812:
	.ascii	"VDMHAL_V5R6C1_ClearMMUIntState\000"
	.space	1
	.type	__func__.58818, %object
	.size	__func__.58818, 22
__func__.58818:
	.ascii	"VDMHAL_V5R6C1_MaskInt\000"
	.space	2
	.type	__func__.58831, %object
	.size	__func__.58831, 24
__func__.58831:
	.ascii	"VDMHAL_V5R6C1_EnableInt\000"
	.type	__func__.58840, %object
	.size	__func__.58840, 23
__func__.58840:
	.ascii	"VDMHAL_V5R6C1_CheckReg\000"
	.space	1
	.type	__func__.58854, %object
	.size	__func__.58854, 26
__func__.58854:
	.ascii	"VDMHAL_V5R6C1_ReadMMUMask\000"
	.space	2
	.type	__func__.58859, %object
	.size	__func__.58859, 27
__func__.58859:
	.ascii	"VDMHAL_V5R6C1_WriteMMUMask\000"
	.space	1
	.type	__func__.58891, %object
	.size	__func__.58891, 25
__func__.58891:
	.ascii	"VDMHAL_V5R6C1_PrepareDec\000"
	.space	3
	.type	__func__.58896, %object
	.size	__func__.58896, 25
__func__.58896:
	.ascii	"VDMHAL_V5R6C1_IsVdmReady\000"
	.space	3
	.type	__func__.58901, %object
	.size	__func__.58901, 23
__func__.58901:
	.ascii	"VDMHAL_V5R6C1_IsVdmRun\000"
	.space	1
	.type	__func__.58907, %object
	.size	__func__.58907, 27
__func__.58907:
	.ascii	"VDMHAL_V5R6C1_IsVdhDecOver\000"
	.space	1
	.type	__func__.58917, %object
	.size	__func__.58917, 31
__func__.58917:
	.ascii	"VDMHAL_V5R6C1_IsVdhPartDecOver\000"
	.space	1
	.type	__func__.58932, %object
	.size	__func__.58932, 33
__func__.58932:
	.ascii	"VDMHAL_V5R6C1_UpdateHardwareInfo\000"
	.space	3
	.type	__func__.59005, %object
	.size	__func__.59005, 23
__func__.59005:
	.ascii	"VDMHAL_V5R6C1_CfgRpMsg\000"
	.space	1
	.type	__func__.58982, %object
	.size	__func__.58982, 24
__func__.58982:
	.ascii	"VDMHAL_CfgNotFullRepair\000"
	.type	__func__.59029, %object
	.size	__func__.59029, 28
__func__.59029:
	.ascii	"VDMHAL_V5R6C1_MakeDecReport\000"
	.type	__func__.59068, %object
	.size	__func__.59068, 28
__func__.59068:
	.ascii	"VDMHAL_V5R6C1_PrepareRepair\000"
	.type	__func__.59256, %object
	.size	__func__.59256, 15
__func__.59256:
	.ascii	"MFDE_ConfigReg\000"
	.space	1
	.type	__func__.59075, %object
	.size	__func__.59075, 28
__func__.59075:
	.ascii	"VDMHAL_V5R6C1_StartHwRepair\000"
	.type	__func__.59114, %object
	.size	__func__.59114, 28
__func__.59114:
	.ascii	"VDMHAL_V5R6C1_CalVdhClkSkip\000"
	.type	__func__.59138, %object
	.size	__func__.59138, 28
__func__.59138:
	.ascii	"VDMHAL_V5R6C1_StartHwDecode\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC1:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC2:
	ASCII(.ascii	"pOpenParam = NULL error!\000" )
	.space	3
.LC3:
	ASCII(.ascii	"%s: %s\012\000" )
.LC4:
	ASCII(.ascii	"MemBaseAddr = 0 error!\000" )
	.space	1
.LC5:
	ASCII(.ascii	"VDMHAL_V5R6C1_OpenHAL: Size error!\000" )
	.space	1
.LC6:
	ASCII(.ascii	"VdhId is wrong!!!\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"BPDRegVirAddr %p\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"!!!!!! HAL memory not enouph! need %d, have %d\012\000" )
.LC10:
	ASCII(.ascii	"image size out of range\000" )
.LC11:
	ASCII(.ascii	"VDMHAL ArrangeMem HEVC/VP9/AVS2 10 bit\012\000" )
.LC12:
	ASCII(.ascii	"%s pstVfmwFrameSizeInfo = NULL\012\000" )
.LC13:
	ASCII(.ascii	"DelAllFrameMemRecord err in VDMHAL_V5R6C1_ArrangeMe" )
	ASCII(.ascii	"m!\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"Report arrange frame buffer: wxh %dx%d, FsNum %d, P" )
	ASCII(.ascii	"mvNum %d\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"Report arrange frame buffer only: wxh %dx%d, FsNum " )
	ASCII(.ascii	"%d, PmvNum %d\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"VidStd Invalid\000" )
	.space	1
.LC17:
	ASCII(.ascii	"decoder not support, ISMV450 = %d\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"Set CompressEn %d, LossCompressEn %d, YCompRatio %d" )
	ASCII(.ascii	", UVCompRatio %d\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"VDMHAL_V5R6C1_CalcFsSize err!\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"%s, need arrange, Size: %#x, Num: %#x, RefChanged: " )
	ASCII(.ascii	"%#x\012\000" )
.LC21:
	ASCII(.ascii	"DFS, report event. Size: 0x%x, Num: %d, RefChanged:" )
	ASCII(.ascii	" %d\012\000" )
.LC22:
	ASCII(.ascii	"pVdmMemArrange is NULL\000" )
	.space	1
.LC23:
	ASCII(.ascii	"DFS, no ref frame!\012\000" )
.LC24:
	ASCII(.ascii	"DFS, Frame number = %d > 30, Then, Frame num = 30, " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"VDMHAL_V5R6C1_ArrangeMem Mem addr is NULL\000" )
	.space	2
.LC26:
	ASCII(.ascii	"'pVdmMemArrange' is NULL\000" )
	.space	3
.LC27:
	ASCII(.ascii	"MemSize not enough for pmv slot\000" )
.LC28:
	ASCII(.ascii	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight" )
	ASCII(.ascii	" failed!\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"ImgSlotLen > ChanSlotLen\000" )
	.space	3
.LC30:
	ASCII(.ascii	"cann't allocate img slot\000" )
	.space	3
.LC31:
	ASCII(.ascii	"VDMHAL_V5R6C1_ResetVdm: map vdm register fail, vir(" )
	ASCII(.ascii	"reg) = (%p)\012\000" )
.LC32:
	ASCII(.ascii	"%s module id %d failed!\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"%s module id %d success!\012\000" )
	.space	2
.LC34:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"%s: map vdm register 0x%x failed!\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"%s VdhId %d failed!\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"%s VdhId %d success!\012\000" )
	.space	2
.LC39:
	ASCII(.ascii	"%s: VdhId(%d) Invalid!\012\000" )
.LC40:
	ASCII(.ascii	"%s: vdm register virtual address not mapped, reset " )
	ASCII(.ascii	"failed!\012\000" )
.LC41:
	ASCII(.ascii	"%s: unkown reg_id = %d\012\000" )
.LC42:
	ASCII(.ascii	"%s: pDecParam(%p) = NULL\012\000" )
	.space	2
.LC43:
	ASCII(.ascii	"VDM register not mapped yet!\000" )
	.space	3
.LC44:
	ASCII(.ascii	"VDM register not mapped yet!\012\000" )
	.space	2
.LC45:
	ASCII(.ascii	"can NOT map vir addr for up-msg\000" )
.LC46:
	ASCII(.ascii	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"ReadUpMsgSlot error! upmsg_size(%d) > 512\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"WriteMsgSlot error!\012\000" )
	.space	3
.LC49:
	ASCII(.ascii	"can not map repair msg virtual address!\000" )
.LC50:
	ASCII(.ascii	"ValidGroupNum=%d out of range!\012\000" )
.LC51:
	ASCII(.ascii	"align_mb error\012\000" )
.LC52:
	ASCII(.ascii	"[%s][%d]sclie_num is wrong! %d \012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"'pMakeDecReport' is NULL\000" )
	.space	3
.LC54:
	ASCII(.ascii	"'pDecReport' is NULL\000" )
	.space	3
.LC55:
	ASCII(.ascii	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full" )
	ASCII(.ascii	" repair.\012\000" )
	.space	3
.LC56:
	ASCII(.ascii	"\012***** UpMsg DecSliceNum=%d\012\000" )
	.space	3
.LC57:
	ASCII(.ascii	"\012***** Up Msg (phy addr: %#8x) *****\012\000" )
	.space	2
.LC58:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"\012***** Up Msg print finished *****\012\000" )
.LC60:
	ASCII(.ascii	"vdm register virtual address not mapped, VDMHAL_V20" )
	ASCII(.ascii	"0R003_PrepareRepair failed!\012\000" )
.LC61:
	ASCII(.ascii	"FIRST_REPAIR Parameter Error!\012\000" )
	.space	1
.LC62:
	ASCII(.ascii	"SECOND_REPAIR Parameter Error!\012\000" )
.LC63:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC64:
	ASCII(.ascii	"%s The channel %d is not active\012\000" )
	.space	3
.LC65:
	ASCII(.ascii	"BigTile1d_y\000" )
.LC66:
	ASCII(.ascii	"failed mem_allocMemBlock BigTile_yuv save!\012\000" )
.LC67:
	ASCII(.ascii	"BigTile1d_uv\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
