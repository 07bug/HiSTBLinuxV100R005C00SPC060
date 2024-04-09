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
	.type	VDMHAL_UpdateParam, %function
VDMHAL_UpdateParam:
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
	ldr	r3, [r2, #28]
	ldr	ip, [r2, #64]
	mov	r3, r3, asl ip
	cmp	r3, #1920
	ldmgtfd	sp, {fp, sp, pc}
	ldr	r3, [r2, #4]
	cmp	r3, #17
	ldmeqfd	sp, {fp, sp, pc}
	mov	ip, #0
	mov	r3, #1
	strb	ip, [r2]
	strb	r3, [r2, #1]
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L12
.L15:
	.word	.L25
	.word	.L16
	.word	.L17
	.word	.L18
	.word	.L12
	.word	.L19
	.word	.L20
	.word	.L12
	.word	.L21
	.word	.L22
	.word	.L23
	.word	.L23
	.word	.L23
	.word	.L24
	.word	.L12
	.word	.L25
	.word	.L26
	.word	.L27
.L25:
	mov	r2, #0
	mov	r3, #1
	strb	r2, [r1, #4]
	strb	r3, [r1, #17]
.L12:
	ldmfd	sp, {fp, sp, pc}
.L24:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #3144]
	strb	r3, [r1, #2778]
	ldmfd	sp, {fp, sp, pc}
.L26:
	mov	r2, #0
	mov	r3, #1
	strb	r2, [r1]
	strb	r3, [r1, #5]
	ldmfd	sp, {fp, sp, pc}
.L27:
	add	r1, r1, #270336
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #2468]
	strb	r3, [r1, #2081]
	ldmfd	sp, {fp, sp, pc}
.L16:
	add	r2, r1, #12288
	mov	r0, #0
	mov	r3, #1
	str	r0, [r2, #260]
	strb	r3, [r1, #71]
	ldmfd	sp, {fp, sp, pc}
.L17:
	add	r2, r1, #12288
	mov	r0, #0
	mov	r3, #1
	str	r0, [r2, #2372]
	strb	r3, [r1, #159]
	ldmfd	sp, {fp, sp, pc}
.L18:
	add	r2, r1, #45056
	mov	r0, #0
	mov	r3, #1
	str	r0, [r2, #240]
	strb	r3, [r1, #144]
	ldmfd	sp, {fp, sp, pc}
.L19:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #160]
	strb	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L20:
	add	r2, r1, #12288
	mov	r0, #0
	mov	r3, #1
	str	r0, [r2, #2604]
	strb	r3, [r1, #48]
	ldmfd	sp, {fp, sp, pc}
.L21:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #76]
	strb	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
.L22:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #72]
	strb	r3, [r1, #1]
	ldmfd	sp, {fp, sp, pc}
.L23:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r1, #212]
	strb	r3, [r1, #52]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_UpdateParam, .-VDMHAL_UpdateParam
	.align	2
	.global	VDMHAL_V5R2C1_GetHalMemSize
	.type	VDMHAL_V5R2C1_GetHalMemSize, %function
VDMHAL_V5R2C1_GetHalMemSize:
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
	.size	VDMHAL_V5R2C1_GetHalMemSize, .-VDMHAL_V5R2C1_GetHalMemSize
	.align	2
	.global	VDMHAL_V5R2C1_OpenHAL
	.type	VDMHAL_V5R2C1_OpenHAL, %function
VDMHAL_V5R2C1_OpenHAL:
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
	beq	.L42
	ldmia	r3, {r6, r8}
	ldr	r7, [r3, #8]
	cmp	r6, #0
	beq	.L43
	cmp	r8, #6291456
	blt	.L44
	cmp	r7, #0
	bgt	.L45
	ldr	r4, .L47
	mov	r2, #268
	ldr	r10, .L47+4
	mov	r1, #0
	ldr	r5, .L47+8
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
	ldr	r1, .L47+12
	mov	r3, r0
	mov	r2, r0
	str	r3, [r5, r9]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #53248
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r1, .L47+16
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
.L38:
	str	r1, [r2, #4]!
	cmp	r2, r0
	add	r1, r1, #1280
	bne	.L38
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
	bcc	.L39
	mov	r0, r4
	bl	H264HAL_V5R2C1_InitHal
	mov	r5, r0
	mov	r0, r4
	bl	HEVCHAL_V5R2C1_InitHal
	cmp	r0, #0
	beq	.L46
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L46:
	adds	r0, r5, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L45:
	ldr	r1, .L47+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L39:
	mov	r3, r8
	ldr	r1, .L47+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L43:
	mov	r0, r6
	ldr	r3, .L47+28
	ldr	r2, .L47+32
	ldr	r1, .L47+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L44:
	ldr	r3, .L47+40
	mov	r0, #0
	ldr	r2, .L47+32
	ldr	r1, .L47+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L42:
	ldr	r3, .L47+44
	ldr	r2, .L47+32
	ldr	r1, .L47+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L48:
	.align	2
.L47:
	.word	g_VdmExtParam
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LC5
	.word	.LC6
	.word	.LC4
	.word	.LC7
	.word	.LC2
	.word	.LANCHOR0
	.word	.LC1
	.word	.LC3
	.word	.LC0
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_OpenHAL, .-VDMHAL_V5R2C1_OpenHAL
	.align	2
	.global	VDMHAL_V5R2C1_CloseHAL
	.type	VDMHAL_V5R2C1_CloseHAL, %function
VDMHAL_V5R2C1_CloseHAL:
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
	.size	VDMHAL_V5R2C1_CloseHAL, .-VDMHAL_V5R2C1_CloseHAL
	.align	2
	.global	VDMHAL_V5R2C1_CalcFsSize
	.type	VDMHAL_V5R2C1_CalcFsSize, %function
VDMHAL_V5R2C1_CalcFsSize:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 32
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
	sub	ip, r1, #32
	mov	r4, r1
	movw	r1, #8160
	cmp	ip, r1
	mov	r7, r0
	mov	r6, r2
	str	r3, [fp, #-64]
	bhi	.L51
	sub	r3, r2, #32
	mov	r5, r2
	cmp	r3, r1
	bhi	.L51
	add	r3, r2, #15
	sub	r2, fp, #44
	add	r10, r4, #15
	sub	r1, fp, #52
	mov	r3, r3, asr #4
	ldr	r0, [fp, #4]
	str	r3, [r2, #-4]!
	mov	r10, r10, asr #4
	str	r3, [fp, #-56]
	str	r10, [fp, #-52]
	bl	VDMHAL_CalcPmvSlotLen.isra.0
	ldr	r3, [fp, #4]
	cmp	r3, #16
	ldr	r3, [fp, #-56]
	mov	r9, r0
	beq	.L78
	ldr	r2, [fp, #4]
	ldr	r8, .L83
	cmp	r2, #17
	beq	.L79
	mov	r10, r10, asl #4
	mov	r2, #0
	add	r10, r10, #255
	mov	r1, r2
	add	r5, r6, #31
	str	r2, [fp, #-68]
	bic	r2, r10, #255
	str	r2, [fp, #-56]
	ldr	r2, [r8, r7, asl #2]
	bic	r5, r5, #31
	str	r1, [fp, #-72]
.L55:
	ldr	r1, [r2, #1176]
	cmp	r1, #1
	beq	.L80
.L77:
	mov	r10, #0
	str	r10, [fp, #-60]
	mov	r6, r10
.L58:
	ldr	r1, [fp, #-64]
	cmp	r1, #1
	beq	.L81
.L59:
	ldr	r1, [fp, #-72]
	add	r4, r6, r6, lsl #1
	ldr	r3, [fp, #-68]
	mul	r3, r3, r1
	ldr	r1, [fp, #-56]
	mul	r5, r1, r5
	add	r3, r3, r3, lsl #1
	mov	r3, r3, lsr #1
	add	r1, r5, r5, lsl #1
	add	r3, r3, r1, lsr #1
	add	r4, r3, r4, lsr #1
	add	r3, r2, #471040
	ldr	r1, [r3, #1224]
	cmp	r1, #0
	beq	.L82
.L61:
	add	r0, r2, #475136
	ldr	r1, [fp, #4]
	str	r4, [r0, #696]
	cmp	r1, #17
	ldr	r0, [fp, #-60]
	add	r1, r9, r9, lsr #31
	str	r10, [r3, #3576]
	mov	r1, r1, asr #1
	str	r1, [r3, #3612]
	str	r0, [r3, #3572]
	beq	.L62
	ldr	r1, [r3, #1232]
	ldr	r0, [fp, #4]
	ldr	ip, [fp, #-56]
	cmp	r1, #32
	sub	r0, r0, #16
	movge	r1, #32
	cmp	r0, #1
	mov	r10, ip, asl #4
	str	r1, [r3, #3616]
	str	r10, [r3, #3564]
	add	r1, r5, r6
	mov	r10, r10, lsr #1
	str	r1, [r3, #3596]
	str	r10, [r3, #3568]
	bls	.L63
.L64:
	ldr	r3, [r8, r7, asl #2]
	mov	r0, #1024
	add	r4, r4, #1056
	add	r2, r3, #475136
	add	r1, r9, r4
	str	r9, [r2, #700]
	str	r0, [r2, #708]
	ldrsb	r3, [r3, #44]
	cmp	r3, #1
	ldr	r3, [fp, #8]
	addeq	r1, r1, r0
	cmp	r3, #0
	beq	.L72
	str	r4, [r3, #4]
	mov	r2, #1024
	ldr	r3, [r8, r7, asl #2]
	mov	r0, #0
	ldr	ip, [fp, #8]
	add	r3, r3, #471040
	ldr	r3, [r3, #1232]
	str	r9, [ip, #12]
	str	r3, [ip, #8]
	ldr	r3, [r8, r7, asl #2]
	add	r3, r3, #471040
	ldr	r3, [r3, #3616]
	str	r1, [ip]
	str	r2, [ip, #20]
	str	r3, [ip, #16]
	ldr	r3, [r8, r7, asl #2]
	add	r3, r3, #475136
	str	r4, [r3, #704]
.L76:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L80:
	ldr	r1, [fp, #4]
	cmp	r1, #17
	cmpne	r6, #2160
	movge	r10, #1
	movlt	r10, #0
	cmp	r4, #3840
	orrge	r10, r10, #1
	cmp	r10, #0
	streq	r10, [fp, #-60]
	moveq	r6, r10
	beq	.L58
	add	r6, r6, #63
.L67:
	add	r1, r4, #2032
	add	r4, r4, #4080
	add	r1, r1, #15
	add	r4, r4, #14
	cmp	r1, #0
	add	r0, r6, #63
	movlt	r1, r4
	cmp	r6, #0
	mov	r1, r1, asr #11
	movlt	r6, r0
	mov	r6, r6, asr #6
	mov	r0, r1, asl #9
	mov	r1, r1, asl #4
	str	r1, [fp, #-60]
	mul	r6, r6, r0
	ldr	r1, [fp, #-64]
	cmp	r1, #1
	mov	r10, r6
	bne	.L59
.L81:
	mov	r4, r3, asl #5
	add	r4, r4, r3, lsl #4
	ldr	r3, [fp, #-56]
	mul	r5, r3, r5
	mul	r4, r3, r4
	add	r3, r2, #471040
	ldr	r1, [r3, #1224]
	cmp	r1, #0
	bne	.L61
.L82:
	ldr	r3, .L83+4
	movw	r0, #15848
	movt	r0, 7
	add	r0, r2, r0
	mov	r2, #1248
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r2, [r8, r7, asl #2]
	add	r3, r2, #471040
	b	.L61
.L62:
	ldr	r1, [fp, #-56]
	mov	r10, r1, asl #4
	mov	r1, #1
	str	r10, [r3, #3564]
	str	r1, [r3, #3616]
	mov	r10, r10, lsr r1
	add	r1, r5, r6
	str	r10, [r3, #3568]
	str	r1, [r3, #3596]
.L63:
	ldr	r2, [r2, #1508]
	cmp	r2, #8
	ble	.L64
	ldr	r1, [fp, #-72]
	add	r6, r6, r6, lsl #1
	ldr	r0, [fp, #-68]
	add	r5, r5, r5, lsl #1
	mov	r6, r6, lsr #1
	add	r5, r6, r5, lsr #1
	str	r5, [r3, #3588]
	mul	r2, r1, r0
	mov	r1, r1, asl #4
	mov	r0, #31
	str	r1, [r3, #3580]
	ldr	r1, .L83+8
	str	r2, [r3, #3592]
	bl	dprint_vfmw
	b	.L64
.L78:
	ldr	r8, .L83
	add	r10, r4, #255
	bic	r2, r10, #255
	str	r2, [fp, #-56]
	ldr	r2, [r8, r7, asl #2]
	ldr	r1, [r2, #1508]
	cmp	r1, #8
	ble	.L68
	ldr	r0, [fp, #-56]
	add	r1, r6, #31
	bic	r1, r1, #31
	str	r1, [fp, #-68]
	mov	r0, r0, lsr #2
	str	r0, [fp, #-72]
	b	.L55
.L79:
	add	r10, r4, #255
	add	r6, r6, #63
	bic	r2, r10, #255
	str	r2, [fp, #-56]
	ldr	r2, [r8, r7, asl #2]
	bic	r5, r6, #63
	ldr	r1, [r2, #1508]
	cmp	r1, #8
	ble	.L69
	ldr	r1, [fp, #-56]
	str	r5, [fp, #-68]
	mov	r1, r1, lsr #2
	str	r1, [fp, #-72]
.L57:
	ldr	r1, [r2, #1176]
	cmp	r1, #1
	bne	.L77
	b	.L67
.L68:
	mov	r1, #0
	str	r1, [fp, #-68]
	str	r1, [fp, #-72]
	b	.L55
.L51:
	ldr	r3, .L83+12
	mov	r0, #0
	ldr	r2, .L83+16
	ldr	r1, .L83+20
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L72:
	ldr	r0, [fp, #8]
	b	.L76
.L69:
	mov	r1, #0
	str	r1, [fp, #-68]
	str	r1, [fp, #-72]
	b	.L57
.L84:
	.align	2
.L83:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC9
	.word	.LC8
	.word	.LANCHOR0+24
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CalcFsSize, .-VDMHAL_V5R2C1_CalcFsSize
	.align	2
	.global	VDMHAL_V5R2C1_GetRpuSize
	.type	VDMHAL_V5R2C1_GetRpuSize, %function
VDMHAL_V5R2C1_GetRpuSize:
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
	.size	VDMHAL_V5R2C1_GetRpuSize, .-VDMHAL_V5R2C1_GetRpuSize
	.align	2
	.global	VDMHAL_V5R2C1_CalcFsNum
	.type	VDMHAL_V5R2C1_CalcFsNum, %function
VDMHAL_V5R2C1_CalcFsNum:
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
	cmp	r3, #0
	mov	r2, r0
	beq	.L91
	cmp	r1, #17
	ldr	ip, .L93
	beq	.L92
	ldr	lr, [ip, r0, asl #2]
	add	r0, lr, #471040
	ldr	r1, [r0, #1232]
	cmp	r1, #32
	movge	r1, #32
	str	r1, [r0, #3616]
	ldr	r1, [lr, #600]
	cmp	r1, #2
	ldreq	r1, [r0, #1236]
	streq	r1, [r0, #3616]
.L90:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #0
	add	r1, r1, #471040
	ldr	r1, [r1, #1232]
	str	r1, [r3, #8]
	ldr	r2, [ip, r2, asl #2]
	add	r2, r2, #471040
	ldr	r2, [r2, #3616]
	str	r2, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L92:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #1
	add	r1, r1, #471040
	str	r0, [r1, #3616]
	b	.L90
.L91:
	ldr	r2, .L93+4
	mov	r0, #1
	ldr	r1, .L93+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L94:
	.align	2
.L93:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+52
	.word	.LC10
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CalcFsNum, .-VDMHAL_V5R2C1_CalcFsNum
	.align	2
	.global	VDMHAL_V5R2C1_DynamicAllocFrame
	.type	VDMHAL_V5R2C1_DynamicAllocFrame, %function
VDMHAL_V5R2C1_DynamicAllocFrame:
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
	ldr	r6, .L115
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
	bne	.L114
.L96:
	ldr	r1, [r6, r4, asl #2]
	movw	r2, #13544
	movt	r2, 7
	mov	r3, #0
	add	r2, r1, r2
	mov	r1, #255
.L97:
	str	r1, [r2, r3]
	add	r3, r3, #72
	cmp	r3, #2304
	bne	.L97
	cmp	r8, #1920
	cmple	r7, #1088
	ble	.L98
	ldr	r2, [r5, #8]
	ldr	r3, [r6, r4, asl #2]
.L99:
	ldr	r1, [r3, #1456]
	add	r3, r3, #471040
	mov	r0, r4
	add	r2, r2, r1
	str	r2, [r3, #1236]
	bl	VCTRL_GetVidStd
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L115
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
	ldr	r1, .L115+4
	bl	dprint_vfmw
	ldr	r3, .L115+8
	ldr	r9, [r3]
	cmp	r9, #0
	beq	.L103
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
.L103:
	ldr	r0, [r6, r4, asl #2]
	mov	r1, #0
	ldr	r3, .L115+12
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
.L98:
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L115
	ldr	r2, [r3, #36]
	cmp	r2, #24
	ldreq	r2, [r5, #8]
	beq	.L99
	add	r2, r3, #475136
	ldr	r2, [r2, #1332]
	cmp	r2, #0
	ldr	r2, [r5, #8]
	addeq	r2, r2, #4
	streq	r2, [r5, #8]
	ldreq	r3, [r1, r4, asl #2]
	b	.L99
.L114:
	ldr	r1, .L115+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L96
.L116:
	.align	2
.L115:
	.word	s_pstVfmwChan
	.word	.LC12
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_DynamicAllocFrame, .-VDMHAL_V5R2C1_DynamicAllocFrame
	.align	2
	.global	VDMHAL_V5R2C1_DynamicAllocFrame_Only
	.type	VDMHAL_V5R2C1_DynamicAllocFrame_Only, %function
VDMHAL_V5R2C1_DynamicAllocFrame_Only:
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
	ldr	ip, .L122
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
	ldr	r1, .L122+4
	str	lr, [ip, #1236]
	ldr	lr, [r4, #16]
	ldr	ip, [r4, #8]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L122+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L117
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
.L117:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L123:
	.align	2
.L122:
	.word	s_pstVfmwChan
	.word	.LC13
	.word	g_event_report
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_DynamicAllocFrame_Only, .-VDMHAL_V5R2C1_DynamicAllocFrame_Only
	.align	2
	.global	VDMHAL_V5R2C1_ArrangeMem_Normal
	.type	VDMHAL_V5R2C1_ArrangeMem_Normal, %function
VDMHAL_V5R2C1_ArrangeMem_Normal:
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
	mov	r7, r2
	mov	r8, r3
	str	r0, [fp, #-68]
	str	r0, [fp, #-64]
	str	r0, [fp, #-60]
	str	r0, [fp, #-56]
	str	r0, [fp, #-52]
	str	r0, [fp, #-48]
	bhi	.L160
	ldr	r10, .L169
	ldr	r1, [r10, r4, asl #2]
	add	r2, r1, #471040
	ldr	r3, [r1, #100]
	ldr	r2, [r2, #1228]
	cmp	r3, #2
	str	r2, [fp, #-76]
	beq	.L161
	bics	r3, r5, #16
	moveq	r3, #1
	movne	r3, #0
	cmp	r5, #18
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L162
.L129:
	sub	r3, r5, #17
	clz	r3, r3
	mov	r3, r3, lsr #5
	mov	ip, r3
.L130:
	ldr	lr, [r1, #1188]
	mov	r2, r3
	str	r3, [r1, #1176]
	mov	r0, #1
	ldr	r3, [r1, #1180]
	str	lr, [sp, #4]
	ldr	lr, .L169+4
	ldr	r1, [r1, #1184]
	str	r1, [sp]
	ldr	r1, .L169+8
	str	ip, [lr, r4, asl #4]
	bl	dprint_vfmw
.L128:
	sub	r6, fp, #68
	ldr	r2, [fp, #4]
	mov	r1, r5
	mov	r0, r4
	mov	r3, r6
	bl	VDMHAL_V5R2C1_CalcFsNum
	ldr	r3, [fp, #8]
	str	r6, [sp, #4]
	mov	r2, r8
	str	r5, [sp]
	mov	r1, r7
	mov	r9, r0
	mov	r0, r4
	bl	VDMHAL_V5R2C1_CalcFsSize
	orrs	r3, r0, r9
	bne	.L163
	ldr	r3, [r10, r4, asl #2]
	ldr	r1, [fp, #-76]
	ldr	r5, [fp, #-68]
	str	r3, [fp, #-72]
	add	r3, r3, #471040
	cmp	r1, r5
	ldr	r2, .L169
	ldr	r9, [r3, #1232]
	ldr	r1, [r3, #1248]
	beq	.L164
.L133:
	str	r1, [sp, #4]
	mov	r3, r5
	ldr	r2, .L169+12
	mov	r0, #31
	ldr	r1, .L169+16
	str	r9, [sp]
	bl	dprint_vfmw
	ldr	r3, [r10, r4, asl #2]
	mov	r1, r7
	mov	r0, r4
	add	r3, r3, #471040
	ldr	r2, [r3, #1224]
	str	r5, [r3, #1228]
	mov	r3, r6
	cmp	r2, #0
	mov	r2, r8
	beq	.L165
	bl	VDMHAL_V5R2C1_DynamicAllocFrame_Only
.L136:
	ldr	ip, [r10, r4, asl #2]
	mov	r3, r9
	mov	r2, r5
	ldr	r1, .L169+20
	add	ip, ip, #471040
	mov	r0, #31
	ldr	ip, [ip, #1248]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, .L169+24
	ldr	r4, [r10, r4, asl #2]
	ldr	r3, [r3]
	add	r4, r4, #475136
	blx	r3
	mov	r3, #2
	str	r0, [r4, #712]
.L126:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L164:
	cmp	r1, #1
	beq	.L133
	ldr	r0, [r3, #1224]
	cmp	r0, #1
	beq	.L133
	ldr	r1, [fp, #12]
	cmp	r1, #0
	beq	.L166
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
	beq	.L167
.L138:
	add	r2, r2, #471040
	ldr	r2, [r2, #1236]
	cmp	r2, #30
	bgt	.L168
.L139:
	str	r2, [r3, #3608]
	mov	r0, #8
	str	r3, [fp, #-84]
	ldr	r3, .L169+24
	ldr	r2, [r3, #12]
	blx	r2
	ldr	r2, [r10, r4, asl #2]
	ldr	r3, [fp, #-84]
	add	r8, r2, #475136
	ldr	r1, [r8, #736]
	cmp	r1, #0
	beq	.L144
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
.L143:
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
	beq	.L141
	ldr	lr, [r3, #3628]
	add	r4, lr, #1
	mov	r2, lr, asl #4
	sub	r2, r2, lr, asl #2
	ldr	lr, [r1, #16]
	add	r2, r3, r2
	add	r2, r2, #4352
	str	lr, [r2, #56]
	str	r4, [r3, #3628]
.L141:
	ldr	r2, [r3, #3624]
	cmp	r2, r6
	bcs	.L142
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
.L142:
	ldr	r2, [r8, #736]
	add	r1, r1, #72
	cmp	ip, r2
	bcc	.L143
	ldr	r4, [fp, #-84]
.L144:
	ldr	r3, .L169+24
	mov	r2, #1232
	ldr	r1, [fp, #-80]
	ldr	r0, [fp, #12]
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r10, r4, asl #2]
	ldr	r2, .L169+24
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
.L165:
	bl	VDMHAL_V5R2C1_DynamicAllocFrame
	b	.L136
.L162:
	cmp	r8, #2160
	cmplt	r7, #3840
	movge	ip, #1
	movge	r3, ip
	bge	.L130
	b	.L129
.L161:
	mvn	r3, #0
	str	r0, [r1, #1176]
	str	r0, [r1, #1180]
	str	r3, [r1, #1184]
	str	r3, [r1, #1188]
	b	.L128
.L167:
	ldr	r1, .L169+28
	mov	r0, #31
	str	r3, [fp, #-88]
	str	r2, [fp, #-84]
	bl	dprint_vfmw
	ldr	r2, [fp, #-84]
	ldr	r3, [fp, #-88]
	ldr	r2, [r2, r4, asl #2]
	b	.L138
.L168:
	ldr	r1, .L169+32
	mov	r0, #31
	str	r3, [fp, #-84]
	bl	dprint_vfmw
	ldr	r1, [r10, r4, asl #2]
	mov	r0, #30
	mov	r2, r0
	ldr	r3, [fp, #-84]
	add	r1, r1, #471040
	str	r0, [r1, #1236]
	b	.L139
.L160:
	ldr	r3, .L169+36
	ldr	r2, .L169+40
	ldr	r1, .L169+44
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L126
.L163:
	ldr	r1, .L169+48
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L126
.L166:
	ldr	r3, .L169+52
	mov	r0, r1
	ldr	r2, .L169+56
	ldr	r1, .L169+44
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L126
.L170:
	.align	2
.L169:
	.word	s_pstVfmwChan
	.word	g_VfmwCompressPara
	.word	.LC15
	.word	.LANCHOR0+108
	.word	.LC17
	.word	.LC18
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	.word	.LC21
	.word	.LC14
	.word	.LANCHOR0+76
	.word	.LC1
	.word	.LC16
	.word	.LC19
	.word	.LANCHOR0+140
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ArrangeMem_Normal, .-VDMHAL_V5R2C1_ArrangeMem_Normal
	.global	__aeabi_idiv
	.align	2
	.global	VDMHAL_V5R2C1_ArrangeMem_Specific
	.type	VDMHAL_V5R2C1_ArrangeMem_Specific, %function
VDMHAL_V5R2C1_ArrangeMem_Specific:
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
	beq	.L246
	ldr	r2, [fp, #4]
	sub	r1, r2, #32
	movw	r2, #8160
	cmp	r1, r2
	bhi	.L174
	ldr	r1, [fp, #8]
	sub	r1, r1, #32
	cmp	r1, r2
	bhi	.L174
	cmp	r6, #0
	beq	.L247
	ldr	ip, .L256
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
	ldrge	r3, .L256+4
	bge	.L245
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
	beq	.L248
	cmp	r9, #17
	beq	.L249
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
	blt	.L216
	ldr	r4, .L256+8
	mov	r3, #0
	str	r3, [fp, #-76]
	str	r3, [fp, #-80]
.L209:
	ldr	r3, [r4, r10, asl #2]
	ldr	r3, [r3, #1176]
	cmp	r3, #1
	movne	r1, #0
	movne	r0, r1
	movne	r3, r1
	beq	.L250
.L182:
	ldr	ip, [fp, #20]
	str	r0, [r6, #12]
	cmp	ip, #1
	str	r1, [r6, #16]
	beq	.L251
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
.L184:
	ldr	r1, [fp, #24]
	cmp	r1, #0
	blt	.L185
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
	beq	.L252
	ldr	r1, [fp, #20]
	add	r10, r10, #15
	bic	r10, r10, #15
	add	r0, r0, #15
	cmp	r1, #1
	add	r1, r10, #255
	bic	r0, r0, #15
	bic	r1, r1, #255
	beq	.L253
	ldr	lr, .L256+8
	ldr	ip, [fp, #24]
	ldr	lr, [lr, ip, asl #2]
	ldr	lr, [lr, #1176]
	cmp	lr, #1
	beq	.L189
	adds	lr, r0, #63
	ldr	ip, [fp, #-100]
	addmi	lr, r0, #126
	mov	lr, lr, asr #6
.L190:
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
.L188:
	cmp	r4, r1
	ldrgt	r3, .L256+12
	bgt	.L245
	ldr	r10, [fp, #24]
.L185:
	ldr	r1, [fp, #-72]
	mul	r7, r7, r1
	sub	r1, r9, #16
	cmp	r1, #1
	add	r1, r7, r3
	str	r1, [r6, #36]
	bls	.L254
	ldr	r3, [fp, #16]
	cmp	r3, #0
	beq	.L194
	cmp	r9, #3
	cmpne	r9, #0
	strne	r2, [fp, #-72]
	beq	.L192
.L244:
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
	beq	.L193
	ldr	lr, [r6, #60]
	mov	ip, r6
	mov	r0, r2
	mov	r3, #0
.L198:
	add	r3, r3, #1
	str	r0, [ip, #464]
	cmp	r1, r3
	add	r0, r0, r4
	add	ip, ip, #12
	bne	.L198
	ldr	r3, [fp, #20]
	cmp	r3, #1
	add	r3, r1, lr
	str	r3, [r6, #60]
	beq	.L255
	ldr	r3, [fp, #-84]
	mla	r4, r1, r4, r3
	add	r3, r4, r5
.L212:
	add	r0, r6, #76
	mov	r2, #0
.L202:
	add	r2, r2, #1
	str	r3, [r0, #4]!
	cmp	r2, r1
	add	r3, r3, #32
	bne	.L202
.L201:
	ldr	ip, [r6, #56]
	add	r4, r4, r1, lsl #5
	add	r5, r4, r5
	cmp	ip, #0
	beq	.L207
	ldr	lr, [r6, #64]
	mov	r0, r6
	mov	r2, r5
	mov	r3, #0
.L206:
	add	r3, r3, #1
	str	r2, [r0, #208]
	cmp	ip, r3
	add	r2, r2, r8
	add	r0, r0, #8
	bne	.L206
	add	r3, ip, lr
	str	r3, [r6, #64]
.L207:
	mla	r8, ip, r8, r4
	cmp	r10, #0
	str	r8, [r6]
	blt	.L205
	ldr	r3, .L256+8
	ldr	r3, [r3, r10, asl #2]
	cmp	r3, #0
	beq	.L205
	cmp	r1, #0
	add	r5, r8, r5
	beq	.L205
	mov	r2, r6
	mov	r3, #0
.L208:
	add	r3, r3, #1
	str	r5, [r2, #848]
	cmp	r3, r1
	add	r5, r5, #1024
	add	r2, r2, #12
	bne	.L208
.L205:
	mov	r0, #0
	add	r8, r8, r1, lsl #10
	str	r8, [r6]
.L243:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L254:
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
	bne	.L192
.L194:
	mov	r3, #0
	str	r3, [r6, #48]
.L193:
	ldr	r3, .L256+16
.L245:
	ldr	r2, .L256+20
	mov	r0, #0
	ldr	r1, .L256+24
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L192:
	str	r2, [fp, #-72]
	ldr	r3, [fp, #16]
	b	.L244
.L248:
	ldr	r3, [fp, #4]
	cmp	r10, #0
	add	r7, r3, #255
	bic	r7, r7, #255
	blt	.L179
	ldr	r4, .L256+8
	movw	r0, #17736
	movt	r0, 7
	str	r2, [fp, #-72]
	ldr	r3, [r4, r10, asl #2]
	add	r0, r3, r0
	bl	IsMain10Profile
	ldr	r2, [fp, #-72]
	cmp	r0, #0
	beq	.L213
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
	b	.L180
.L251:
	ldr	r1, [fp, #-92]
	mov	r4, r1, asl #4
	mul	r4, r7, r4
	add	r4, r4, r4, lsl #1
	b	.L184
.L255:
	ldr	r3, .L256+28
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L200
	str	r2, [fp, #-56]
	mov	r3, #12
	str	r1, [fp, #-48]
	sub	r2, fp, #56
	mov	r1, #128
	str	r4, [fp, #-52]
	mov	r0, r10
	blx	r7
	ldr	r1, [r6, #48]
.L200:
	ldr	r3, [fp, #-84]
	cmp	r1, #0
	mla	r4, r1, r4, r3
	add	r3, r4, r5
	bne	.L212
	b	.L201
.L249:
	ldr	r3, [fp, #4]
	cmp	r10, #0
	add	r7, r3, #255
	ldr	r3, [fp, #8]
	bic	r7, r7, #255
	add	r3, r3, #63
	bic	r3, r3, #63
	str	r3, [fp, #-72]
	blt	.L214
	ldr	r4, .L256+8
	ldr	r3, [r4, r10, asl #2]
	ldr	r3, [r3, #1508]
	cmp	r3, #8
	ble	.L215
	ldr	r1, [fp, #-72]
	cmp	r7, #0
	add	r3, r7, #3
	movge	r3, r7
	mov	r3, r3, asr #2
	str	r1, [fp, #-80]
	str	r3, [fp, #-76]
.L180:
	mov	r3, r7, asl #4
	str	r3, [r6, #4]
	mov	r3, r7, asl #3
	str	r3, [r6, #8]
	b	.L209
.L214:
	ldr	r3, [fp, #-72]
	str	r3, [fp, #8]
.L179:
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
	b	.L182
.L250:
	sub	r1, r9, #17
	ldr	r3, [fp, #4]
	clz	r1, r1
	mov	r1, r1, lsr #5
	cmp	r3, #1920
	orrgt	r1, r1, #1
	cmp	r1, #0
	moveq	r0, r1
	moveq	r3, r1
	beq	.L182
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
	b	.L182
.L253:
	mul	r1, r0, r1
	add	r1, r1, r1, lsl #1
	b	.L188
.L216:
	mov	r1, #0
	str	r1, [fp, #-76]
	mov	r0, r1
	str	r1, [fp, #-80]
	mov	r3, r1
	b	.L182
.L189:
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
	b	.L190
.L213:
	ldr	r1, [fp, #8]
	str	r0, [fp, #-80]
	str	r0, [fp, #-76]
	str	r1, [fp, #-72]
	b	.L180
.L215:
	mov	r3, #0
	str	r3, [fp, #-80]
	str	r3, [fp, #-76]
	b	.L180
.L174:
	ldr	r3, .L256+32
	b	.L245
.L246:
	mov	r0, r5
	ldr	r3, .L256+36
	ldr	r2, .L256+20
	ldr	r1, .L256+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L243
.L252:
	ldr	r1, .L256+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L243
.L247:
	mov	r0, r6
	ldr	r3, .L256+44
	ldr	r2, .L256+20
	ldr	r1, .L256+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L243
.L257:
	.align	2
.L256:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	.word	s_pstVfmwChan
	.word	.LC26
	.word	.LC27
	.word	.LANCHOR0+176
	.word	.LC1
	.word	g_event_report
	.word	.LC8
	.word	.LC22
	.word	.LC25
	.word	.LC23
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ArrangeMem_Specific, .-VDMHAL_V5R2C1_ArrangeMem_Specific
	.align	2
	.global	VDMHAL_V5R2C1_ArrangeMem
	.type	VDMHAL_V5R2C1_ArrangeMem, %function
VDMHAL_V5R2C1_ArrangeMem:
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
	beq	.L261
	cmp	r4, #0
	blt	.L262
	mov	r0, r4
	str	r3, [fp, #-52]
	str	r1, [fp, #-48]
	bl	VCTRL_GetVidStd
	ldr	r2, .L265
	ldr	r1, [fp, #-48]
	ldr	r3, [fp, #-52]
	ldr	r2, [r2, r4, asl #2]
	ldr	r2, [r2, #1448]
	cmp	r2, #1
	beq	.L264
.L260:
	str	r3, [sp, #24]
	mov	r2, r9
	mov	r3, r1
	str	r4, [sp, #20]
	mov	r1, r0
	str	r8, [sp, #16]
	str	r10, [sp, #12]
	mov	r0, r4
	stmia	sp, {r5, r6, r7}
	bl	VDMHAL_V5R2C1_ArrangeMem_Specific
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L262:
	mov	r0, #22
	b	.L260
.L261:
	mov	r0, #16
	b	.L260
.L264:
	str	r3, [fp, #12]
	mov	r1, r0
	mov	r3, r6
	str	r8, [fp, #8]
	mov	r2, r5
	str	r7, [fp, #4]
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDMHAL_V5R2C1_ArrangeMem_Normal
.L266:
	.align	2
.L265:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ArrangeMem, .-VDMHAL_V5R2C1_ArrangeMem
	.align	2
	.global	VDMHAL_V5R2C1_ResetVdm
	.type	VDMHAL_V5R2C1_ResetVdm, %function
VDMHAL_V5R2C1_ResetVdm:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	subs	r7, r0, #0
	mov	r0, #0
	ble	.L268
	mov	r3, r7
	str	r0, [sp]
	ldr	r2, .L282
	ldr	r1, .L282+4
	bl	dprint_vfmw
.L267:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L268:
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L280
	movw	r3, #1228
	ldr	r9, .L282+8
	mul	r3, r3, r7
	ldr	r5, .L282+12
	ldr	r2, [r5]
	ldr	r3, [r9, r3]
	ldr	r10, [r3, #36]
	ldr	r8, [r2, #120]
	tst	r8, #1
	beq	.L267
	ldr	r6, .L282+16
	mov	r3, #2
	bfi	r8, r3, #8, #2
	str	r8, [r2, #120]
	mov	r4, #0
	orr	r8, r8, #64
	ldr	r3, [r6, #112]
	blx	r3
	ldr	r3, [r5]
	str	r8, [r3, #120]
	b	.L272
.L281:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L273
.L272:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	ldr	r3, [r5]
	ldr	r3, [r3, #372]
	tst	r3, #4
	beq	.L281
	cmp	r4, #1000
	bge	.L273
	mov	r3, r7
	ldr	r2, .L282
	ldr	r1, .L282+20
	mov	r0, #0
	bl	dprint_vfmw
.L275:
	ldr	r2, [r5]
	bfc	r8, #6, #1
	ldr	r3, [r6, #112]
	str	r8, [r2, #120]
	bfc	r8, #8, #2
	blx	r3
	movw	r3, #1228
	mul	r7, r3, r7
	ldr	r3, [r5]
	str	r8, [r3, #120]
	ldr	r3, [r9, r7]
	str	r10, [r3, #36]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L273:
	mov	r3, r7
	ldr	r2, .L282
	ldr	r1, .L282+24
	mov	r0, #0
	bl	dprint_vfmw
	b	.L275
.L280:
	ldr	r1, .L282+28
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L283:
	.align	2
.L282:
	.word	.LANCHOR0+212
	.word	.LC28
	.word	g_HwMem
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ResetVdm, .-VDMHAL_V5R2C1_ResetVdm
	.align	2
	.global	VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.type	VDMHAL_V5R2C1_SetSmmuPageTableAddr, %function
VDMHAL_V5R2C1_SetSmmuPageTableAddr:
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
	ldr	r3, .L290
	mov	r4, r0
	ldr	r3, [r3, #196]
	cmp	r3, #0
	beq	.L284
	sub	r2, fp, #24
	sub	r1, fp, #28
	sub	r0, fp, #32
	blx	r3
	cmp	r4, #0
	bne	.L286
	ldr	r3, .L290+4
	ldr	r0, [fp, #-32]
	ldr	r1, [fp, #-28]
	ldr	r3, [r3]
	ldr	r2, [fp, #-24]
	add	r3, r3, #61440
	str	r0, [r3, #524]
	str	r1, [r3, #772]
	str	r2, [r3, #776]
.L284:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L286:
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L290+8
	ldr	r1, .L290+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L290+8
	ldr	r1, .L290+12
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L290+8
	ldr	r1, .L290+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L291:
	.align	2
.L290:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LANCHOR0+236
	.word	.LC32
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_SetSmmuPageTableAddr, .-VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.align	2
	.global	VDMHAL_V5R2C1_EnableSmmu
	.type	VDMHAL_V5R2C1_EnableSmmu, %function
VDMHAL_V5R2C1_EnableSmmu:
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
	ldr	r3, .L293
	mov	r2, #8
	movt	r2, 3
	ldr	r3, [r3]
	add	r3, r3, #61440
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L294:
	.align	2
.L293:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_EnableSmmu, .-VDMHAL_V5R2C1_EnableSmmu
	.align	2
	.global	VDMHAL_V5R2C1_GlbResetX
	.type	VDMHAL_V5R2C1_GlbResetX, %function
VDMHAL_V5R2C1_GlbResetX:
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
	ldr	r5, .L307
	mov	r8, r0
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r3, [r5]
	ldr	r7, [r3, #120]
	tst	r7, #1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r6, .L307+4
	mov	r2, #2
	bfi	r7, r2, #8, #2
	str	r7, [r3, #120]
	mov	r4, #0
	orr	r7, r7, #16
	ldr	r3, [r6, #112]
	blx	r3
	ldr	r3, [r5]
	str	r7, [r3, #120]
	b	.L298
.L306:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L299
.L298:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	ldr	r3, [r5]
	ldr	r3, [r3, #372]
	tst	r3, #1
	beq	.L306
	cmp	r4, #1000
	bge	.L299
	mov	r3, r8
	ldr	r2, .L307+8
	ldr	r1, .L307+12
	mov	r0, #0
	bl	dprint_vfmw
.L301:
	ldr	r2, [r5]
	bfc	r7, #4, #1
	ldr	r3, [r6, #112]
	str	r7, [r2, #120]
	bfc	r7, #8, #2
	blx	r3
	ldr	r3, [r5]
	str	r7, [r3, #120]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L299:
	mov	r3, r8
	ldr	r2, .L307+8
	ldr	r1, .L307+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L301
.L308:
	.align	2
.L307:
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+272
	.word	.LC34
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_GlbResetX, .-VDMHAL_V5R2C1_GlbResetX
	.align	2
	.global	VDMHAL_V5R2C1_GlbReset
	.type	VDMHAL_V5R2C1_GlbReset, %function
VDMHAL_V5R2C1_GlbReset:
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
	beq	.L311
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMHAL_V5R2C1_GlbResetX
.L311:
	mov	r3, #0
	ldr	r2, .L312
	movt	r3, 63683
	ldr	r1, .L312+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L313:
	.align	2
.L312:
	.word	.LANCHOR0+296
	.word	.LC35
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_GlbReset, .-VDMHAL_V5R2C1_GlbReset
	.align	2
	.global	VDMHAL_V5R2C1_ClearIntState
	.type	VDMHAL_V5R2C1_ClearIntState, %function
VDMHAL_V5R2C1_ClearIntState:
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
	ldr	r7, .L330
	mov	r5, r0, asl #3
	mov	r8, r0, asl #6
	rsb	r3, r5, r8
	ldr	r2, .L330+4
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1208]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L327
	movw	r6, #1228
	ldr	r9, .L330+8
	mul	r6, r6, r0
	ldr	r3, [r9, r6]
	cmp	r3, #0
	beq	.L328
.L318:
	cmp	r4, #1
	beq	.L329
.L325:
	mvn	r2, #0
	str	r2, [r3, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L327:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L330+12
	ldr	r2, .L330+16
	bl	dprint_vfmw
.L314:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L329:
	rsb	r5, r5, r8
	add	r7, r7, r5
	ldr	r2, [r7, #44]
	cmp	r2, #1
	beq	.L325
	cmp	r2, #2
	ldr	r1, [r3, #28]
	mvneq	r2, #11
	streq	r2, [r3, #32]
	beq	.L314
	cmp	r2, #3
	mvneq	r2, #14
	streq	r2, [r3, #32]
	b	.L314
.L328:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r9, r6]
	bne	.L318
.L319:
	ldr	r1, .L330+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L331:
	.align	2
.L330:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+320
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ClearIntState, .-VDMHAL_V5R2C1_ClearIntState
	.align	2
	.global	VDMHAL_V5R2C1_ClearMMUIntState
	.type	VDMHAL_V5R2C1_ClearMMUIntState, %function
VDMHAL_V5R2C1_ClearMMUIntState:
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
	bgt	.L337
	movw	r2, #1228
	ldr	r5, .L339
	mul	r4, r2, r3
	ldr	r2, [r5, r4]
	cmp	r2, #0
	beq	.L338
.L335:
	add	r2, r2, #61440
	mov	r3, #7
	str	r3, [r2, #44]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L337:
	mov	r0, #0
	ldr	r2, .L339+4
	str	r0, [sp]
	ldr	r1, .L339+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L338:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	strne	r2, [r5, r4]
	bne	.L335
.L336:
	ldr	r1, .L339+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L340:
	.align	2
.L339:
	.word	g_HwMem
	.word	.LANCHOR0+348
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ClearMMUIntState, .-VDMHAL_V5R2C1_ClearMMUIntState
	.align	2
	.global	VDMHAL_V5R2C1_MaskInt
	.type	VDMHAL_V5R2C1_MaskInt, %function
VDMHAL_V5R2C1_MaskInt:
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
	bgt	.L346
	movw	r2, #1228
	ldr	r5, .L348
	mul	r4, r2, r3
	ldr	r3, [r5, r4]
	cmp	r3, #0
	beq	.L347
.L344:
	mvn	r2, #0
	str	r2, [r3, #36]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L346:
	mov	r0, #0
	ldr	r2, .L348+4
	str	r0, [sp]
	ldr	r1, .L348+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L347:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r5, r4]
	bne	.L344
.L345:
	ldr	r1, .L348+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L349:
	.align	2
.L348:
	.word	g_HwMem
	.word	.LANCHOR0+380
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_MaskInt, .-VDMHAL_V5R2C1_MaskInt
	.align	2
	.global	VDMHAL_V5R2C1_GetIntMaskCfg
	.type	VDMHAL_V5R2C1_GetIntMaskCfg, %function
VDMHAL_V5R2C1_GetIntMaskCfg:
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
	.size	VDMHAL_V5R2C1_GetIntMaskCfg, .-VDMHAL_V5R2C1_GetIntMaskCfg
	.align	2
	.global	VDMHAL_V5R2C1_EnableInt
	.type	VDMHAL_V5R2C1_EnableInt, %function
VDMHAL_V5R2C1_EnableInt:
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
	ldr	r2, .L364
	mov	r3, r0, asl #6
	ldr	r1, .L364+4
	sub	r3, r3, r0, asl #3
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1208]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L362
	movw	r5, #1228
	ldr	r6, .L364+8
	mul	r5, r5, r0
	ldr	r3, [r6, r5]
	cmp	r3, #0
	beq	.L363
.L357:
	cmp	r4, #1
	mvneq	r2, #5
	mvnne	r2, #1
	str	r2, [r3, #36]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L362:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L364+12
	ldr	r2, .L364+16
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L363:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r6, r5]
	bne	.L357
.L358:
	ldr	r1, .L364+20
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L365:
	.align	2
.L364:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+404
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_EnableInt, .-VDMHAL_V5R2C1_EnableInt
	.align	2
	.global	VDMHAL_V5R2C1_CheckReg
	.type	VDMHAL_V5R2C1_CheckReg, %function
VDMHAL_V5R2C1_CheckReg:
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
	bgt	.L383
	movw	r4, #1228
	ldr	r6, .L385
	mul	r4, r4, r5
	ldr	r3, [r6, r4]
	cmp	r3, #0
	beq	.L384
.L369:
	sub	r2, r7, #1
	cmp	r2, #6
	ldrls	pc, [pc, r2, asl #2]
	b	.L375
.L377:
	.word	.L380
	.word	.L378
	.word	.L379
	.word	.L381
	.word	.L371
	.word	.L373
	.word	.L374
.L381:
	mov	r3, #40
.L376:
	movw	r1, #1228
	mul	r5, r1, r5
	ldr	r2, [r6, r5]
	ldr	r0, [r2, r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L380:
	mov	r3, #28
	b	.L376
.L379:
	mov	r3, #36
	b	.L376
.L378:
	mov	r3, #32
	b	.L376
.L374:
	movw	r3, #62272
	b	.L376
.L371:
	movw	r3, #61480
	b	.L376
.L373:
	movw	r3, #62304
	b	.L376
.L375:
	mov	r3, r7
	ldr	r2, .L385+4
	ldr	r1, .L385+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L384:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L370
	str	r8, [r6, r4]
	b	.L369
.L383:
	mov	r3, r5
	ldr	r2, .L385+4
	ldr	r1, .L385+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L370:
	ldr	r2, .L385+4
	ldr	r1, .L385+16
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L386:
	.align	2
.L385:
	.word	g_HwMem
	.word	.LANCHOR0+428
	.word	.LC39
	.word	.LC37
	.word	.LC38
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CheckReg, .-VDMHAL_V5R2C1_CheckReg
	.align	2
	.global	VDMHAL_V5R2C1_ReadMMUMask
	.type	VDMHAL_V5R2C1_ReadMMUMask, %function
VDMHAL_V5R2C1_ReadMMUMask:
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
	ble	.L390
	mov	r1, #1
	ldr	r2, .L391
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L391+4
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L390:
	movw	r0, #1228
	ldr	r2, .L391+8
	mul	r3, r0, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	ldr	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L392:
	.align	2
.L391:
	.word	.LANCHOR0+452
	.word	.LC40
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ReadMMUMask, .-VDMHAL_V5R2C1_ReadMMUMask
	.align	2
	.global	VDMHAL_V5R2C1_WriteMMUMask
	.type	VDMHAL_V5R2C1_WriteMMUMask, %function
VDMHAL_V5R2C1_WriteMMUMask:
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
	ble	.L396
	mov	r1, #1
	ldr	r2, .L397
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L397+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L396:
	movw	r1, #1228
	ldr	r2, .L397+8
	mul	r3, r1, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	str	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L398:
	.align	2
.L397:
	.word	.LANCHOR0+480
	.word	.LC32
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_WriteMMUMask, .-VDMHAL_V5R2C1_WriteMMUMask
	.align	2
	.global	VDMHAL_V5R2C1_PrepareDec
	.type	VDMHAL_V5R2C1_PrepareDec, %function
VDMHAL_V5R2C1_PrepareDec:
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
	beq	.L418
	cmp	r2, #0
	bgt	.L419
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
	cmp	r4, #17
	ldrls	pc, [pc, r4, asl #2]
	b	.L401
.L404:
	.word	.L414
	.word	.L405
	.word	.L406
	.word	.L407
	.word	.L401
	.word	.L408
	.word	.L409
	.word	.L401
	.word	.L410
	.word	.L411
	.word	.L412
	.word	.L412
	.word	.L412
	.word	.L413
	.word	.L401
	.word	.L414
	.word	.L415
	.word	.L416
.L414:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264HAL_V5R2C1_StartDec
.L415:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCHAL_V5R2C1_StartDec
.L416:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP9HAL_V5R2C1_StartDec
.L405:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1HAL_V5R2C1_StartDec
.L406:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP4HAL_V5R2C1_StartDec
.L407:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP2HAL_V5R2C1_StartDec
.L408:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DIVX3HAL_V5R2C1_StartDec
.L409:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVSHAL_V5R2C1_StartDec
.L410:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV8HAL_V5R2C1_StartDec
.L411:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV9HAL_V5R2C1_StartDec
.L412:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP6HAL_V5R2C1_StartDec
.L413:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP8HAL_V5R2C1_StartDec
.L418:
	mov	r3, r7
	mov	r0, r7
	ldr	r2, .L420
	ldr	r1, .L420+4
	bl	dprint_vfmw
.L401:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L419:
	mov	r3, r2
	mov	r0, #0
	ldr	r2, .L420
	str	r0, [sp]
	ldr	r1, .L420+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L421:
	.align	2
.L420:
	.word	.LANCHOR0+508
	.word	.LC41
	.word	.LC28
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_PrepareDec, .-VDMHAL_V5R2C1_PrepareDec
	.align	2
	.global	VDMHAL_V5R2C1_IsVdmReady
	.type	VDMHAL_V5R2C1_IsVdmReady, %function
VDMHAL_V5R2C1_IsVdmReady:
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
	ldr	r3, .L429
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L427
	cmp	r0, #0
	ble	.L428
	mov	r3, r0
	mov	r1, #1
	ldr	r2, .L429+4
	mov	r0, #32
	str	r1, [sp]
	ldr	r1, .L429+8
	bl	dprint_vfmw
	mov	r0, #0
.L424:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L428:
	ldr	r0, [r3, #28]
	ubfx	r0, r0, #17, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L427:
	mov	r0, r3
	ldr	r2, .L429+4
	ldr	r3, .L429+12
	ldr	r1, .L429+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L424
.L430:
	.align	2
.L429:
	.word	g_HwMem
	.word	.LANCHOR0+536
	.word	.LC40
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_IsVdmReady, .-VDMHAL_V5R2C1_IsVdmReady
	.align	2
	.global	VDMHAL_V5R2C1_IsVdmRun
	.type	VDMHAL_V5R2C1_IsVdmRun, %function
VDMHAL_V5R2C1_IsVdmRun:
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
	ldr	r3, .L438
	ldr	r4, [r3, r2]
	cmp	r4, #0
	beq	.L436
	cmp	r0, #0
	ble	.L437
	mov	r3, r0
	mov	r4, #1
	ldr	r2, .L438+4
	mov	r0, #32
	str	r4, [sp]
	ldr	r1, .L438+8
	bl	dprint_vfmw
	mov	r0, r4
.L433:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L437:
	ldr	r0, [r4, #40]
	subs	r0, r0, #1
	movne	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L436:
	ldr	r1, .L438+12
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	b	.L433
.L439:
	.align	2
.L438:
	.word	g_HwMem
	.word	.LANCHOR0+564
	.word	.LC40
	.word	.LC43
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_IsVdmRun, .-VDMHAL_V5R2C1_IsVdmRun
	.align	2
	.global	VDMHAL_V5R2C1_IsVdhDecOver
	.type	VDMHAL_V5R2C1_IsVdhDecOver, %function
VDMHAL_V5R2C1_IsVdhDecOver:
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
	ldr	r3, .L450
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L448
	bl	VDMHAL_V5R2C1_CheckReg
	cmp	r4, #2
	beq	.L445
	cmp	r4, #3
	beq	.L445
	cmp	r4, #1
	beq	.L449
	mov	r3, r4
	ldr	r2, .L450+4
	ldr	r1, .L450+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L445:
	and	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L449:
	ubfx	r0, r0, #17, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L448:
	mov	r0, r3
	ldr	r2, .L450+4
	ldr	r3, .L450+12
	ldr	r1, .L450+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L451:
	.align	2
.L450:
	.word	g_HwMem
	.word	.LANCHOR0+588
	.word	.LC39
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_IsVdhDecOver, .-VDMHAL_V5R2C1_IsVdhDecOver
	.align	2
	.global	VDMHAL_V5R2C1_IsVdhPartDecOver
	.type	VDMHAL_V5R2C1_IsVdhPartDecOver, %function
VDMHAL_V5R2C1_IsVdhPartDecOver:
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
	ldr	r3, .L462
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L460
	bl	VDMHAL_V5R2C1_CheckReg
	cmp	r4, #1
	beq	.L456
	cmp	r4, #2
	bne	.L461
	ubfx	r0, r0, #2, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L461:
	mov	r3, r4
	ldr	r2, .L462+4
	ldr	r1, .L462+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L456:
	ubfx	r0, r0, #19, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L460:
	mov	r0, r3
	ldr	r2, .L462+4
	ldr	r3, .L462+12
	ldr	r1, .L462+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L463:
	.align	2
.L462:
	.word	g_HwMem
	.word	.LANCHOR0+616
	.word	.LC39
	.word	.LC42
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_IsVdhPartDecOver, .-VDMHAL_V5R2C1_IsVdhPartDecOver
	.align	2
	.global	VDMHAL_V5R2C1_UpdateHardwareInfo
	.type	VDMHAL_V5R2C1_UpdateHardwareInfo, %function
VDMHAL_V5R2C1_UpdateHardwareInfo:
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
	bgt	.L465
	ldr	r2, .L499
	ldr	r4, [r2]
	cmp	r4, #1
	addne	r3, r2, #124
	bne	.L469
	b	.L466
.L493:
	cmp	r2, r3
	beq	.L492
.L469:
	ldr	r4, [r2, #4]!
	cmp	r4, #1
	bne	.L493
.L466:
	movw	r6, #1228
	ldr	r7, .L499+4
	mul	r6, r6, r5
	ldr	lr, [r7, r6]
	cmp	lr, #0
	beq	.L494
.L470:
	mov	r2, #180
	ldr	r1, .L499+8
	mul	r2, r2, r5
	mov	r3, r5, asl #6
	sub	r3, r3, r5, asl #3
	ldr	r0, [lr, #12]
	ldr	r6, .L499+12
	add	r3, r3, r1
	ldr	r1, [r3, #4]
	add	r3, r6, r2
	str	r0, [r6, r2]
	ldr	r2, [lr, #28]
	cmp	r1, #1
	str	r2, [r3, #4]
	beq	.L495
	cmp	r4, #1
	beq	.L496
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
	bne	.L475
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
.L475:
	mov	r0, #180
	add	r1, lr, #33024
	mul	r0, r0, r5
	add	r2, r0, #48
	add	r0, r0, #176
	add	r2, r6, r2
	add	r0, r6, r0
.L476:
	ldr	ip, [r1], #4
	str	ip, [r2, #4]!
	cmp	r2, r0
	bne	.L476
	cmp	r4, #0
	bne	.L497
	mov	r3, #180
	add	lr, lr, #32768
	mla	r5, r3, r5, r6
	ldr	r2, [lr, #384]
	ldr	r3, [lr, #388]
	mov	r0, r4
	str	r2, [r5, #48]
	str	r3, [r5, #44]
.L487:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L497:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L492:
	mov	r4, #0
	b	.L466
.L495:
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
.L496:
	movw	r3, #1228
	ubfx	r8, r2, #0, #17
	mla	r3, r3, r5, r7
	ldr	r0, [r3, #40]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L498
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
	b	.L475
.L494:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	lr, r0, #0
	beq	.L471
	str	lr, [r7, r6]
	b	.L470
.L465:
	mov	r0, #0
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L499+16
	ldr	r1, .L499+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L487
.L471:
	ldr	r1, .L499+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L487
.L498:
	ldr	r3, .L499+28
	ldr	r2, .L499+16
	ldr	r1, .L499+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L487
.L500:
	.align	2
.L499:
	.word	g_DSPState
	.word	g_HwMem
	.word	g_VdmDrvParam+48
	.word	g_BackUp
	.word	.LANCHOR0+648
	.word	.LC28
	.word	.LC36
	.word	.LC44
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_UpdateHardwareInfo, .-VDMHAL_V5R2C1_UpdateHardwareInfo
	.align	2
	.global	VDMHAL_V5R2C1_ReadMsgSlot
	.type	VDMHAL_V5R2C1_ReadMsgSlot, %function
VDMHAL_V5R2C1_ReadMsgSlot:
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
	beq	.L505
	cmp	r2, #800
	bhi	.L506
	ldr	r3, .L507
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L506:
	mov	r0, r4
	ldr	r1, .L507+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L505:
	mov	r2, r0
	ldr	r1, .L507+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L508:
	.align	2
.L507:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC46
	.word	.LC45
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_ReadMsgSlot, .-VDMHAL_V5R2C1_ReadMsgSlot
	.align	2
	.global	VDMHAL_V5R2C1_WriteMsgSlot
	.type	VDMHAL_V5R2C1_WriteMsgSlot, %function
VDMHAL_V5R2C1_WriteMsgSlot:
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
	beq	.L510
	sub	r3, r2, #1
	cmp	r3, #255
	bhi	.L510
	ldr	r3, .L513
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L510:
	ldr	r1, .L513+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L514:
	.align	2
.L513:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_WriteMsgSlot, .-VDMHAL_V5R2C1_WriteMsgSlot
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	VDMHAL_V5R2C1_CfgRpMsg
	.type	VDMHAL_V5R2C1_CfgRpMsg, %function
VDMHAL_V5R2C1_CfgRpMsg:
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
	beq	.L554
	ldr	r2, [r8, #44]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L555
	ldr	r1, [r8, #28]
	ldr	r3, [r8, #64]
	ldrb	r2, [r8]	@ zero_extendqisi2
	ldr	r0, [r8, #32]
	mov	r1, r1, asl r3
	cmp	r2, #1
	add	r2, r1, #255
	bic	r2, r2, #255
	mov	r3, r0, asl r3
	movne	r1, #0
	beq	.L556
.L519:
	ldr	r0, [r8, #4]
	cmp	r0, #16
	beq	.L520
	add	r3, r3, #31
	mov	r0, #8
	bic	r3, r3, #31
	str	r0, [fp, #-80]
	mla	r3, r3, r2, r1
.L543:
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
	moveq	r2, r2, asl #4
	str	r2, [ip, #16]
	str	r1, [ip, #20]
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
	beq	.L557
.L525:
	cmp	r1, #1
	beq	.L541
.L563:
	ldr	r3, [fp, #-64]
	sub	r3, r3, #1
	uxth	r3, r3
.L542:
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
.L552:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L557:
	ldr	r3, [r8, #64]
	cmp	r3, #6
	moveq	r4, #2
	beq	.L526
	cmp	r3, #5
	moveq	r4, #4
	beq	.L526
	cmp	r3, #4
	moveq	r4, #8
	bne	.L558
.L526:
	ldr	r9, [r8, #44]
	cmp	r9, #0
	movle	r3, #0
	ldrle	r1, [r8, #56]
	strle	r3, [fp, #-64]
	ble	.L525
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
	b	.L529
.L561:
	ldrsh	r0, [r5, #74]
	mov	r1, r4
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r3, r4, r0
	cmp	r7, r3
	str	r3, [fp, #-72]
	ldrgt	r7, [fp, #-88]
	bgt	.L532
.L531:
	add	r6, r6, #1
	cmp	r6, r9
	bge	.L559
.L540:
	cmp	r6, #199
	bgt	.L560
.L529:
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
	bgt	.L561
	ldr	r3, [fp, #-72]
	cmp	r7, r3
	movgt	r3, #0
	movle	r3, #1
	cmp	r6, #0
	moveq	r3, #0
	cmp	r3, #0
	bne	.L531
.L534:
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
	bgt	.L562
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
	blt	.L540
.L559:
	ldr	r8, [fp, #-56]
	ldr	r1, [r8, #56]
	cmp	r1, #1
	bne	.L563
.L541:
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
	b	.L542
.L535:
	bl	__aeabi_uidiv
	mov	r1, r4
	mul	r10, r4, r0
	ldrsh	r0, [r5, #80]
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r10, r0
	add	r3, r0, #1
	bhi	.L536
	cmp	r10, r3
	mov	r1, r4
	beq	.L536
	ldrsh	r0, [r5, #74]
	add	r0, r0, r7
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r10, r0
	bhi	.L564
.L536:
	cmp	r8, #198
	mov	r6, r8
	add	r5, r5, #4
	bgt	.L565
	ldrsh	r10, [r5, #78]
.L532:
	add	r8, r6, #1
	mov	r1, r4
	cmp	r8, r9
	add	r0, r7, r10
	blt	.L535
	ldr	r3, [fp, #-88]
	add	r0, r3, r10
	bl	__aeabi_uidiv
	mul	r7, r4, r0
	b	.L534
.L565:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r2, r3, r8, lsl #2
	ldrsh	r0, [r2, #78]
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r7, r4, r0
	b	.L534
.L520:
	mov	r0, #10
	str	r0, [fp, #-80]
	mla	r3, r2, r3, r1
	b	.L543
.L556:
	add	r0, r1, #2032
	adds	ip, r3, #63
	add	r0, r0, #15
	addmi	ip, r3, #126
	add	r1, r1, #4080
	cmp	r0, #0
	add	r1, r1, #14
	movge	r1, r0
	mov	r0, ip, asr #6
	mov	r1, r1, asr #11
	mov	r0, r0, asl #5
	mov	r1, r1, asl #4
	mul	r1, r1, r0
	b	.L519
.L564:
	mov	r7, r10
	b	.L534
.L560:
	ldr	r8, [fp, #-56]
	mov	r0, #0
	ldr	r1, .L566
	mov	r3, #2128
	str	r6, [sp]
	ldr	r2, .L566+4
	str	r0, [fp, #-64]
	bl	dprint_vfmw
	ldr	r1, [r8, #56]
	b	.L525
.L558:
	ldr	r1, .L566+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r4, #1
	b	.L526
.L562:
	ldr	r8, [fp, #-56]
	mov	r1, #1
	str	r1, [r8, #56]
	b	.L541
.L555:
	ldr	r1, .L566+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L552
.L554:
	ldr	r3, .L566+16
	ldr	r2, .L566+20
	ldr	r1, .L566+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L552
.L567:
	.align	2
.L566:
	.word	.LC51
	.word	.LANCHOR0+708
	.word	.LC50
	.word	.LC49
	.word	.LC48
	.word	.LANCHOR0+684
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CfgRpMsg, .-VDMHAL_V5R2C1_CfgRpMsg
	.align	2
	.global	VDMHAL_V5R2C1_CfgRpReg
	.type	VDMHAL_V5R2C1_CfgRpReg, %function
VDMHAL_V5R2C1_CfgRpReg:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r6, r3, #0
	mov	r0, #0
	str	r0, [fp, #-32]
	bgt	.L602
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L603
.L571:
	ldr	r4, .L605
	ldr	r3, [r1, #48]
	ldrb	r2, [r4]	@ zero_extendqisi2
	bic	r3, r3, #15
	str	r3, [fp, #-32]
	cmp	r2, #1
	bne	.L604
	movw	r1, #1228
	ldr	r2, .L605+4
	mul	r1, r1, r6
	ldr	r1, [r2, r1]
	str	r3, [r1, #16]
.L574:
	movw	r3, #1228
	movw	r1, #53763
	mul	r3, r3, r6
	movt	r1, 8192
	ldr	r3, [r2, r3]
	str	r1, [r3, #12]
.L576:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #60]
.L578:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #64]
.L580:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #68]
.L582:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #72]
.L584:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #76]
.L586:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r6
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #80]
.L588:
	movw	r3, #1228
	movw	r1, #3075
	mul	r6, r3, r6
	mov	r0, #0
	movt	r1, 48
	ldr	r3, [r2, r6]
	str	r1, [r3, #84]
.L591:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L604:
	mov	r2, #16
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r2, [r4]	@ zero_extendqisi2
	movw	r3, #53763
	cmp	r2, #1
	movt	r3, 8192
	str	r3, [fp, #-32]
	ldreq	r2, .L605+4
	beq	.L574
	mov	r2, #12
	mov	r1, #2
	ldr	r0, [fp, #4]
	movw	r5, #3075
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	movt	r5, 48
	str	r5, [fp, #-32]
	cmp	r3, #1
	ldreq	r2, .L605+4
	beq	.L576
	mov	r3, r5
	mov	r2, #60
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L605+4
	beq	.L578
	mov	r3, r5
	mov	r2, #64
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L605+4
	beq	.L580
	mov	r3, r5
	mov	r2, #68
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L605+4
	beq	.L582
	mov	r3, r5
	mov	r2, #72
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L605+4
	beq	.L584
	mov	r3, r5
	mov	r2, #76
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L605+4
	beq	.L586
	mov	r3, r5
	mov	r2, #80
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L605+4
	beq	.L588
	ldr	r0, [fp, #4]
	mov	r3, r5
	mov	r2, #84
	mov	r1, #2
	bl	VDH_Record_RegData
	mov	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L603:
	mov	r0, #0
	str	r1, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L572
	ldr	r1, [fp, #-40]
	str	r3, [r1]
	b	.L571
.L602:
	str	r0, [sp]
	ldr	r2, .L605+8
	ldr	r1, .L605+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L591
.L572:
	ldr	r1, .L605+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L591
.L606:
	.align	2
.L605:
	.word	g_HalDisable
	.word	g_HwMem
	.word	.LANCHOR0+732
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CfgRpReg, .-VDMHAL_V5R2C1_CfgRpReg
	.align	2
	.global	VDMHAL_V5R2C1_MakeDecReport
	.type	VDMHAL_V5R2C1_MakeDecReport, %function
VDMHAL_V5R2C1_MakeDecReport:
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
	beq	.L636
	ldr	r5, [r3, #4]
	ldr	r8, [r3]
	cmp	r5, #0
	ldr	r6, [r3, #8]
	beq	.L637
	movw	r3, #1228
	ldr	r7, .L645
	mul	r3, r3, r6
	ldr	r0, [r7, r3]
	cmp	r0, #0
	beq	.L611
	ldr	r3, .L645+4
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #124
	bne	.L614
	b	.L626
.L639:
	cmp	r3, r1
	beq	.L638
.L614:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	bne	.L639
.L626:
	mov	r4, r2
.L612:
	ldr	r3, .L645+8
	mov	r2, #824
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r3, #48]
	blx	r3
	movw	r3, #1228
	mla	r3, r3, r6, r7
	ldr	r1, .L645+12
	mov	r2, #180
	mla	r2, r2, r6, r1
	ldr	r3, [r3, #24]
	str	r3, [r5, #4]
	ldr	r3, [r2, #4]
	mov	r3, r3, lsr #17
	and	r2, r3, #3
	cmp	r2, #1
	moveq	r3, #0
	beq	.L615
	eor	r3, r3, #1
	and	r3, r3, #1
	cmp	r8, #3
	orrne	r3, r3, #1
.L615:
	mov	r2, #180
	str	r3, [r5]
	mla	r3, r2, r6, r1
	cmp	r8, #0
	cmpne	r8, #15
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #0, #17
	str	r2, [r5, #12]
	beq	.L640
.L616:
	cmp	r2, #200
	bhi	.L641
.L618:
	movw	r3, #1228
	mla	r7, r3, r6, r7
	ldr	r8, [r7, #40]
	mov	r0, r8
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L642
	mov	r9, #3200
	ldr	r7, .L645+16
	mul	r9, r9, r6
	ldr	r2, [r5, #12]
	add	r4, r7, r9
	mov	r2, r2, asl #2
	mov	r0, r4
	bl	VDMHAL_V5R2C1_ReadMsgSlot
	ldr	ip, [r5, #12]
	ldr	r3, [r7, r9]
	cmp	ip, #0
	mov	r3, r3, lsr #31
	movne	r0, r4
	str	r3, [r5, #16]
	movne	r2, #0
	movne	r3, r5
	beq	.L623
.L622:
	ldr	r1, [r0, #4]
	add	r2, r2, #1
	cmp	r2, ip
	add	r0, r0, #16
	add	r3, r3, #4
	strh	r1, [r3, #16]	@ movhi
	ldr	r1, [r0, #-8]
	strh	r1, [r3, #18]	@ movhi
	bne	.L622
.L623:
	mov	r0, #6
	bl	IsDprintTypeEnable
	cmp	r0, #0
	bne	.L643
.L609:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L640:
	cmp	r4, #1
	beq	.L644
	ldr	r1, .L645+20
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L616
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L616
	mov	r3, #1
	strh	r1, [r5, #20]	@ movhi
	mov	r0, r1
	strh	r1, [r5, #22]	@ movhi
	str	r3, [r5, #12]
	b	.L609
.L638:
	mov	r4, #0
	b	.L612
.L643:
	ldr	r2, [r5, #12]
	mov	r0, #6
	ldr	r1, .L645+24
	mov	r4, #0
	bl	dprint_vfmw
	mov	r2, r8
	ldr	r1, .L645+28
	mov	r0, #6
	bl	dprint_vfmw
	mov	r3, #3200
	mla	r6, r3, r6, r7
.L624:
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
	ldr	r1, .L645+32
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r3, r3, asl #2
	sub	r3, r3, #3
	cmp	r3, r4
	bhi	.L624
	ldr	r1, .L645+36
	mov	r0, #6
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L641:
	mov	r3, #200
	ldr	r1, .L645+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5, #12]
	b	.L618
.L644:
	ldr	r3, [r3, #16]
	ubfx	r3, r3, #21, #2
	cmp	r3, #2
	bne	.L616
	mov	r3, #0
	str	r4, [r5, #12]
	strh	r3, [r5, #20]	@ movhi
	mov	r0, r3
	strh	r3, [r5, #22]	@ movhi
	b	.L609
.L642:
	ldr	r3, .L645+44
	ldr	r2, .L645+48
	ldr	r1, .L645+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L609
.L611:
	ldr	r3, .L645+56
	ldr	r2, .L645+48
	ldr	r1, .L645+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L609
.L637:
	mov	r0, r5
	ldr	r3, .L645+60
	ldr	r2, .L645+48
	ldr	r1, .L645+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L609
.L636:
	ldr	r3, .L645+64
	ldr	r2, .L645+48
	ldr	r1, .L645+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L609
.L646:
	.align	2
.L645:
	.word	g_HwMem
	.word	g_DSPState
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_BackUp
	.word	g_UpMsg
	.word	g_not_allow_H264FullPictureRepair_flag
	.word	.LC55
	.word	.LC56
	.word	.LC57
	.word	.LC58
	.word	.LC54
	.word	.LC44
	.word	.LANCHOR0+756
	.word	.LC1
	.word	.LC42
	.word	.LC53
	.word	.LC52
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_MakeDecReport, .-VDMHAL_V5R2C1_MakeDecReport
	.align	2
	.global	VDMHAL_V5R2C1_PrepareRepair
	.type	VDMHAL_V5R2C1_PrepareRepair, %function
VDMHAL_V5R2C1_PrepareRepair:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
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
	ldr	r7, .L662
	movw	ip, #1752
	mov	r9, r1
	movw	r4, #1228
	ldr	r6, .L662+4
	mla	r1, ip, r3, r7
	cmp	r3, #0
	mul	r4, r4, r3
	mov	r5, r3
	mov	r8, r0
	add	r10, r4, r6
	str	r1, [fp, #-48]
	bgt	.L658
	ldr	r3, [r4, r6]
	cmp	r3, #0
	beq	.L659
.L650:
	cmp	r2, #0
	beq	.L660
	cmp	r2, #1
	movne	r0, #0
	beq	.L661
.L649:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L660:
	movw	r3, #1752
	mla	r7, r3, r5, r7
	ldr	r3, [r7, #44]
	cmp	r3, #0
	ble	.L653
	cmp	r8, #6
	bne	.L654
	ldrb	r3, [r9, #17]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r2, r3
	str	r2, [r7, #928]
.L654:
	ldr	r4, [fp, #-48]
	mov	r1, r9
	mov	r0, r8
	mov	r2, r4
	bl	VDMHAL_UpdateParam
	ldr	r3, [fp, #4]
	mov	r2, r9
	mov	r1, r10
	mov	r0, r8
	str	r3, [sp]
	mov	r3, r5
	bl	VDMHAL_V5R2C1_CfgRpReg
	mov	r2, r5
	mov	r1, r10
	mov	r0, r4
	bl	VDMHAL_V5R2C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L661:
	cmp	r8, #6
	bne	.L656
	ldrb	r3, [r9, #17]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L656
	movw	r4, #1752
	ldr	r6, .L662
	mul	r4, r4, r5
	add	r7, r7, r4
	ldr	r3, [r7, #920]
	cmp	r3, #0
	ble	.L656
	ldr	r2, [fp, #-48]
	mov	r1, r9
	mov	r3, #2
	mov	r0, r8
	str	r3, [r7, #928]
	bl	VDMHAL_UpdateParam
	ldr	r3, [fp, #4]
	mov	r2, r9
	mov	r1, r10
	mov	r0, r8
	str	r3, [sp]
	mov	r3, r5
	bl	VDMHAL_V5R2C1_CfgRpReg
	add	r0, r4, #876
	add	r0, r6, r0
	mov	r2, r5
	mov	r1, r10
	bl	VDMHAL_V5R2C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L659:
	mov	r0, #0
	str	r2, [fp, #-52]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L651
	str	r3, [r4, r6]
	ldr	r2, [fp, #-52]
	b	.L650
.L658:
	mov	r0, #0
	ldr	r2, .L662+8
	str	r0, [sp]
	ldr	r1, .L662+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L649
.L656:
	ldr	r1, .L662+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L649
.L653:
	mov	r0, r2
	ldr	r1, .L662+20
	str	r2, [fp, #-48]
	bl	dprint_vfmw
	ldr	r2, [fp, #-48]
	mov	r0, r2
	b	.L649
.L651:
	ldr	r1, .L662+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L649
.L663:
	.align	2
.L662:
	.word	g_RepairParam
	.word	g_HwMem
	.word	.LANCHOR0+784
	.word	.LC28
	.word	.LC61
	.word	.LC60
	.word	.LC59
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_PrepareRepair, .-VDMHAL_V5R2C1_PrepareRepair
	.align	2
	.global	VDMHAL_V5R2C1_StartHwRepair
	.type	VDMHAL_V5R2C1_StartHwRepair, %function
VDMHAL_V5R2C1_StartHwRepair:
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
	ldr	r6, .L694
	mov	r5, r0
	mov	r4, r1
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L688
	cmp	r0, #0
	ble	.L689
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L694+4
	mov	r0, #32
	ldr	r1, .L694+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L690
.L672:
	mov	r2, #1
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L694+4
	ldr	r1, .L694+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L684
.L667:
	cmp	r4, #0
	beq	.L691
	mov	r3, r5, asl #6
	ldr	r2, .L694+12
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
.L689:
	movw	r3, #1228
	ldr	r4, .L694+16
	mul	r3, r3, r0
	mov	r2, #67108864
	ldr	r3, [r4, r3]
	str	r2, [r3, #8]
.L670:
	movw	r3, #1228
	ldr	r2, .L694+20
	mul	r3, r3, r5
	mvn	r1, #1
	ldr	r3, [r4, r3]
	str	r1, [r3, #36]
	ldr	r3, [r2, #112]
	blx	r3
.L679:
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
.L664:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L688:
	mov	r3, #67108864
	mov	r2, #8
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L692
	cmp	r5, #0
	ldrle	r4, .L694+16
	bgt	.L672
	b	.L670
.L692:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L667
	ldr	r3, .L694+20
	ldr	r3, [r3, #112]
	blx	r3
	cmp	r5, #0
	ble	.L693
.L676:
	mov	r4, #1
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L694+24
	ldr	r1, .L694+8
	bl	dprint_vfmw
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L694+24
	ldr	r1, .L694+8
	bl	dprint_vfmw
	str	r4, [sp]
	mov	r3, r5
	ldr	r2, .L694+24
	ldr	r1, .L694+8
	mov	r0, #32
	bl	dprint_vfmw
	b	.L664
.L690:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L667
.L684:
	ldr	r3, .L694+20
	ldr	r3, [r3, #112]
	blx	r3
	b	.L676
.L691:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L694+24
	ldr	r1, .L694+28
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L693:
	ldr	r4, .L694+16
	b	.L679
.L695:
	.align	2
.L694:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC32
	.word	g_VdmDrvParam
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+828
	.word	.LC62
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_StartHwRepair, .-VDMHAL_V5R2C1_StartHwRepair
	.align	2
	.global	VDMHAL_V5R2C1_CalVdhClkSkip
	.type	VDMHAL_V5R2C1_CalVdhClkSkip, %function
VDMHAL_V5R2C1_CalVdhClkSkip:
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
	ldr	r9, .L726
	ldr	r10, [r9, #128]
	cmp	r10, #0
	blt	.L718
	mov	r7, #0
	add	r4, r9, #128
	mov	r6, r7
	mov	r5, r7
	add	r9, r9, #252
	mov	r8, #30
	b	.L698
.L725:
	mov	r3, r10
	ldr	r2, .L726+4
	ldr	r1, .L726+8
	mov	r0, #1
	bl	dprint_vfmw
.L700:
	cmp	r4, r9
	beq	.L724
.L717:
	ldr	r10, [r4, #4]!
	cmp	r10, #0
	blt	.L724
.L698:
	mov	r0, r10
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L725
	mov	r0, r10
	bl	FSP_GetInst
	cmp	r0, #0
	beq	.L701
	ldr	r1, [r0, #40]
	ldr	r2, [r0, #44]
	adds	r5, r1, #15
	addmi	r5, r1, #30
	adds	r6, r2, #15
	addmi	r6, r2, #30
	mov	r5, r5, asr #4
	mov	r6, r6, asr #4
.L701:
	ldr	r3, .L726+12
	mov	r0, r10
	ldr	r2, [r3, r10, asl #2]
	ldr	r3, [r2, #1536]
	cmp	r3, #30
	movgt	r8, r3
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L719
.L704:
	.word	.L713
	.word	.L713
	.word	.L713
	.word	.L713
	.word	.L719
	.word	.L713
	.word	.L713
	.word	.L719
	.word	.L713
	.word	.L713
	.word	.L713
	.word	.L713
	.word	.L713
	.word	.L713
	.word	.L719
	.word	.L714
	.word	.L713
	.word	.L713
.L713:
	mul	r7, r6, r5
	cmp	r4, r9
	mul	r7, r7, r8
	bne	.L717
.L724:
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
.L714:
	mul	r7, r6, r5
	mul	r7, r7, r8
	mov	r7, r7, asl #1
	b	.L700
.L719:
	mov	r7, #0
	b	.L700
.L718:
	mov	r0, #25
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L727:
	.align	2
.L726:
	.word	g_ChanCtx
	.word	.LANCHOR0+856
	.word	.LC63
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_CalVdhClkSkip, .-VDMHAL_V5R2C1_CalVdhClkSkip
	.align	2
	.global	VDMHAL_V5R2C1_GetVdmClk
	.type	VDMHAL_V5R2C1_GetVdmClk, %function
VDMHAL_V5R2C1_GetVdmClk:
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
	ldr	r2, .L736
	sub	r0, r3, r0, asl #3
	cmp	r1, #3
	ldrls	pc, [pc, r1, asl #2]
	b	.L729
.L731:
	.word	.L729
	.word	.L732
	.word	.L733
	.word	.L734
.L729:
	add	r3, r2, r0
	mov	r1, #500
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L733:
	add	r3, r2, r0
	mov	r1, #100
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L732:
	add	r3, r2, r0
	mov	r1, #540
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L734:
	add	r3, r2, r0
	mov	r1, #600
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L737:
	.align	2
.L736:
	.word	g_VdmDrvParam
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_GetVdmClk, .-VDMHAL_V5R2C1_GetVdmClk
	.align	2
	.global	VDMHAL_V5R2C1_StartHwDecode
	.type	VDMHAL_V5R2C1_StartHwDecode, %function
VDMHAL_V5R2C1_StartHwDecode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	subs	r5, r0, #0
	mov	r4, r1
	bgt	.L778
	mov	r3, r5, asl #6
	ldr	r6, .L784
	sub	r3, r3, r5, asl #3
	ldr	r8, .L784+4
	add	r3, r6, r3
	ldr	r9, [r3, #8]
	ldr	r3, [r8, r9, asl #2]
	ldr	r2, [r3, #1524]
	cmp	r2, #1
	beq	.L779
.L762:
	mov	r10, #0
.L741:
	ldr	r7, .L784+8
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L780
	ldr	r3, .L784+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	ubfx	r1, r3, #8, #2
	cmp	r10, r1
	bfine	r3, r10, #8, #2
	strne	r3, [r2, #120]
.L745:
	mov	r1, r10
	mov	r0, r5
	bl	VDMHAL_V5R2C1_GetVdmClk
	ldrb	r2, [r7]	@ zero_extendqisi2
	ldr	r3, [r8, r9, asl #2]
	cmp	r2, #1
	ldr	r8, [r3, #1208]
	bne	.L781
	ldr	r3, .L784+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
.L748:
	mov	r2, r5
	mov	r3, r4
	mov	r1, #3
	mov	r0, #12
	bl	SCD_ConfigReg
	ldrb	r2, [r7]	@ zero_extendqisi2
	ldr	r10, .L784+8
	cmp	r2, #1
	bne	.L782
	movw	r2, #1228
	ldr	r3, .L784+16
	mul	r2, r2, r5
	ldr	r4, .L784+20
	ldr	r1, [r3]
	movw	r3, #43690
	bfi	r3, r3, #16, #16
	cmp	r1, #1
	ldr	r2, [r4, r2]
	moveq	r1, #15
	movne	r1, #0
	str	r3, [r2, #156]
.L750:
	movw	r2, #1228
	cmp	r8, #1
	mul	r2, r2, r5
	mvneq	r3, #5
	mvnne	r3, #1
	ldr	r2, [r4, r2]
	add	r2, r2, #61440
	str	r1, [r2, #32]
.L752:
	movw	r2, #1228
	mul	r2, r2, r5
	ldr	r2, [r4, r2]
	str	r3, [r2, #36]
.L754:
	ldr	r7, .L784+24
	mov	r0, #30
	ldr	r3, [r7, #116]
	blx	r3
	ldr	r3, [r7, #112]
	blx	r3
	movw	r3, #1228
	mul	r3, r3, r5
	mov	r1, #56
	mov	r2, #0
	mov	lr, #1
	mla	r5, r1, r5, r6
	ldr	ip, .L784+28
	mov	r1, #4
	ldr	r0, [r4, r3]
	str	r2, [r0]
	ldr	r0, [r4, r3]
	str	lr, [r0]
	ldr	r3, [r4, r3]
	str	r2, [r3]
	ldr	r0, [r5, #8]
	ldr	r2, [ip, r0, asl #2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDEC_Lowdelay_Event_Time
.L780:
	mov	r2, #0
	mov	r3, r10
	mov	r1, r2
	mov	r0, r4
	bl	VDH_Record_RegData
	b	.L745
.L778:
	mov	r0, #0
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L784+32
	ldr	r1, .L784+36
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L782:
	movw	r3, #43690
	mov	r1, #2
	mov	r2, #156
	movt	r3, 43690
	mov	r0, r4
	bl	VDH_Record_RegData
	ldr	r3, .L784+16
	ldrb	r2, [r10]	@ zero_extendqisi2
	ldr	r3, [r3]
	cmp	r3, #1
	moveq	r1, #15
	movne	r1, #0
	cmp	r2, #1
	ldreq	r4, .L784+20
	beq	.L750
	mov	r3, r1
	movw	r2, #61472
	mov	r0, r4
	mov	r1, #2
	bl	VDH_Record_RegData
	cmp	r8, #1
	ldrb	r2, [r7]	@ zero_extendqisi2
	mvneq	r3, #5
	mvnne	r3, #1
	cmp	r2, #1
	ldreq	r4, .L784+20
	beq	.L752
	mov	r0, r4
	mov	r2, #36
	mov	r1, #2
	bl	VDH_Record_RegData
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r4, .L784+20
	beq	.L754
	cmp	r4, #0
	beq	.L783
	mov	r3, #1
	str	r9, [r4, #8]
	strb	r5, [r4]
	mov	r0, r4
	str	r3, [r4, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDH_PostTask
.L781:
	mov	r3, #0
	mov	r2, #1
	mov	r1, r3
	mov	r0, r4
	bl	VDH_Record_RegData
	b	.L748
.L779:
	ldr	r3, [r3, #568]
	cmp	r3, #17
	bne	.L762
	ldr	r3, .L784+40
	ldr	r3, [r3, r9, asl #2]
	ldr	r2, [r3, #40]
	cmp	r2, #3840
	bge	.L742
	ldr	r3, [r3, #44]
	cmp	r3, #2160
	blt	.L762
.L742:
	ldr	r3, .L784+24
	movw	r0, #12320
	movt	r0, 63650
	mov	r1, #65536
	ldr	r3, [r3, #152]
	blx	r3
	ldr	r3, .L784+44
	ldr	r3, [r3]
	ldr	r3, [r3, #196]
	mov	r3, r3, lsr #24
	cmp	r3, #3
	beq	.L763
	cmp	r3, #2
	beq	.L764
	mov	r2, #221
	cmp	r3, #1
	mov	r1, r2
	movt	r2, 137
	movt	r1, 113
	moveq	r3, r2
	movne	r3, r1
.L743:
	str	r3, [r0]
	mov	r10, #2
	b	.L741
.L783:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L784+32
	ldr	r1, .L784+48
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L763:
	mov	r3, #221
	movt	r3, 113
	b	.L743
.L764:
	mov	r3, #221
	movt	r3, 125
	b	.L743
.L785:
	.align	2
.L784:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HalDisable
	.word	g_pstRegCrg
	.word	mask_mmu_err_int
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_LowDelaySeqIndex
	.word	.LANCHOR0+884
	.word	.LC28
	.word	s_pFspInst
	.word	g_pstRegSysCtrl
	.word	.LC62
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_StartHwDecode, .-VDMHAL_V5R2C1_StartHwDecode
	.align	2
	.global	VDMHAL_V5R2C1_GetCharacter
	.type	VDMHAL_V5R2C1_GetCharacter, %function
VDMHAL_V5R2C1_GetCharacter:
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
	ldr	r1, .L787
	mov	r0, #15
	ldr	r3, .L787+4
	mov	r2, #4
	str	r0, [r1]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L788:
	.align	2
.L787:
	.word	g_VdmCharacter
	.word	g_eVdmVersion
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_GetCharacter, .-VDMHAL_V5R2C1_GetCharacter
	.align	2
	.global	VDMHAL_V5R2C1_WriteBigTitle1DYuv
	.type	VDMHAL_V5R2C1_WriteBigTitle1DYuv, %function
VDMHAL_V5R2C1_WriteBigTitle1DYuv:
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
	beq	.L790
	cmp	ip, #2
	moveq	r4, #1
	movne	r4, #2
.L790:
	ldr	r3, [fp, #-108]
	cmp	r3, #0
	beq	.L789
	mov	r3, #0
	mov	r2, #4194304
	mov	r1, r3
	str	r3, [sp]
	ldr	r0, .L879
	sub	r3, fp, #92
	bl	MEM_AllocMemBlock
	subs	r1, r0, #0
	bne	.L793
	str	r1, [sp]
	mov	r2, #4194304
	sub	r3, fp, #68
	ldr	r0, .L879+4
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L793
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
	bne	.L794
	ldr	r3, [fp, #-100]
	mov	r1, r5, lsr #1
	ldr	r2, [fp, #-64]
	cmp	r3, #0
	ldr	r6, .L879+8
	mov	r3, r3, lsr #1
	ldr	r7, [fp, #-88]
	str	r2, [fp, #-120]
	movne	r10, r0
	add	r2, r2, #2097152
	str	r1, [fp, #-124]
	str	r2, [fp, #-128]
	str	r3, [fp, #-112]
	strne	r10, [fp, #-96]
	beq	.L796
.L795:
	cmp	r5, #0
	beq	.L798
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	ldr	r2, [fp, #-104]
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L797:
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
	bhi	.L797
.L798:
	ldr	r3, [fp, #-96]
	add	r10, r10, r5
	ldr	r2, [fp, #-100]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r2, r3
	bne	.L795
.L796:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	ldr	r3, [r6, #44]
	blx	r3
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L799
	ldr	r3, [fp, #-104]
	mov	r9, #0
	ldr	r10, [fp, #-116]
	str	r9, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L800:
	cmp	r5, #0
	beq	.L803
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L801:
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
	bhi	.L801
.L803:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L800
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L877
.L805:
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L806
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
.L806:
	ldr	r3, [fp, #-124]
.L876:
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
.L789:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L793:
	ldr	r1, .L879+12
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L794:
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
	ldr	r6, .L879+8
	ldr	r7, [fp, #-88]
	strhi	r3, [fp, #-96]
	bls	.L813
.L815:
	cmp	r5, #0
	beq	.L816
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	mov	r10, r2, lsr #1
	ldr	r2, [fp, #-104]
	mul	r10, r5, r10
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L814:
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
	bhi	.L814
.L816:
	ldr	r3, [fp, #-96]
	ldr	r2, [fp, #-100]
	add	r3, r3, #2
	str	r3, [fp, #-96]
	cmp	r2, r3
	bhi	.L815
.L813:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	ldr	r3, [r6, #44]
	mov	r1, r1, lsr #1
	blx	r3
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L817
	ldr	r3, [fp, #-104]
	mov	r9, #0
	ldr	r10, [fp, #-116]
	str	r9, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L818:
	cmp	r5, #0
	beq	.L821
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L819:
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
	bhi	.L819
.L821:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L818
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L878
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L824
	ldr	r2, [fp, #-112]
	ldr	r3, [fp, #-124]
	cmp	r2, r3
	bls	.L829
.L830:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L830
.L829:
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
.L824:
	ldr	r3, [fp, #-132]
	b	.L876
.L877:
	ldr	r3, [fp, #-120]
	add	r7, r7, #1
	ldr	r4, [fp, #-124]
	mov	lr, #0
	ldr	r8, [fp, #-112]
.L807:
	cmp	r4, #0
	moveq	ip, r3
	beq	.L810
	sub	r1, r3, #-67108863
	add	ip, r3, r4
	sub	r1, r1, #65011712
	mov	r2, r7
.L808:
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	strb	r0, [r1, #1]!
	ldrb	r0, [r2], #2	@ zero_extendqisi2
	strb	r0, [r3], #1
	cmp	r3, ip
	bne	.L808
.L810:
	add	lr, lr, #1
	mov	r3, ip
	cmp	lr, r8
	add	r7, r7, r5
	bne	.L807
	b	.L806
.L878:
	ldr	r3, [fp, #-124]
	mov	r4, #0
	ldr	lr, [fp, #-120]
	ldr	ip, [fp, #-132]
	mla	r3, r5, r3, r7
	ldr	r7, [fp, #-112]
	mov	r5, r5, asl #1
	add	r3, r3, #1
.L825:
	cmp	ip, #0
	beq	.L828
	mov	r2, r4, lsr #1
	mov	r1, r3
	mul	r2, ip, r2
	sub	r0, r2, #-67108863
	add	r9, r2, ip
	sub	r0, r0, #65011712
	add	r9, lr, r9
	add	r0, lr, r0
	add	r2, lr, r2
.L826:
	ldrb	r8, [r1, #-1]	@ zero_extendqisi2
	strb	r8, [r0, #1]!
	ldrb	r8, [r1], #2	@ zero_extendqisi2
	strb	r8, [r2], #1
	cmp	r2, r9
	bne	.L826
.L828:
	add	r4, r4, #2
	add	r3, r3, r5
	cmp	r7, r4
	bhi	.L825
	b	.L824
.L799:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	bne	.L805
	b	.L806
.L817:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L824
	cmp	r3, #0
	beq	.L829
	b	.L824
.L880:
	.align	2
.L879:
	.word	.LC64
	.word	.LC66
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC65
	UNWIND(.fnend)
	.size	VDMHAL_V5R2C1_WriteBigTitle1DYuv, .-VDMHAL_V5R2C1_WriteBigTitle1DYuv
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
	ldr	ip, .L888
	mov	lr, r2
	ldrb	r2, [ip]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L887
	cmp	r0, #0
	bne	.L883
	ldr	r3, .L888+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	ubfx	r0, r2, #8, #2
	cmp	r1, r0
	bfine	r2, r1, #8, #2
	strne	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L883:
	cmp	r0, #1
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L888+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	bfi	r2, r1, #12, #5
	bfc	r2, #17, #1
	str	r2, [r3, #120]
	ldr	r2, [r3, #120]
	orr	r2, r2, #131072
	str	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L887:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #0
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L889:
	.align	2
.L888:
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
	ldr	ip, .L896
	mov	lr, r3
	ldrb	r3, [ip]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L894
	cmp	r2, #0
	ble	.L895
	str	r3, [sp]
	mov	r0, #32
	mov	r3, r2
	ldr	r1, .L896+4
	ldr	r2, .L896+8
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L895:
	movw	r3, #1228
	ldr	ip, .L896+12
	mul	r2, r3, r2
	ldr	r3, [ip, r2]
	str	r1, [r3, r0]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L894:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #2
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L897:
	.align	2
.L896:
	.word	g_HalDisable
	.word	.LC32
	.word	.LANCHOR0+812
	.word	g_HwMem
	UNWIND(.fnend)
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.55048, %object
	.size	__func__.55048, 22
__func__.55048:
	.ascii	"VDMHAL_V5R2C1_OpenHAL\000"
	.space	2
	.type	__func__.55122, %object
	.size	__func__.55122, 25
__func__.55122:
	.ascii	"VDMHAL_V5R2C1_CalcFsSize\000"
	.space	3
	.type	__func__.55148, %object
	.size	__func__.55148, 24
__func__.55148:
	.ascii	"VDMHAL_V5R2C1_CalcFsNum\000"
	.type	__func__.55191, %object
	.size	__func__.55191, 32
__func__.55191:
	.ascii	"VDMHAL_V5R2C1_ArrangeMem_Normal\000"
	.type	__FUNCTION__.55192, %object
	.size	__FUNCTION__.55192, 32
__FUNCTION__.55192:
	.ascii	"VDMHAL_V5R2C1_ArrangeMem_Normal\000"
	.type	__func__.55134, %object
	.size	__func__.55134, 33
__func__.55134:
	.ascii	"VDMHAL_V5R2C1_FillMemArrangeInfo\000"
	.space	3
	.type	__func__.55274, %object
	.size	__func__.55274, 34
__func__.55274:
	.ascii	"VDMHAL_V5R2C1_ArrangeMem_Specific\000"
	.space	2
	.type	__func__.55298, %object
	.size	__func__.55298, 23
__func__.55298:
	.ascii	"VDMHAL_V5R2C1_ResetVdm\000"
	.space	1
	.type	__func__.55308, %object
	.size	__func__.55308, 35
__func__.55308:
	.ascii	"VDMHAL_V5R2C1_SetSmmuPageTableAddr\000"
	.space	1
	.type	__func__.55332, %object
	.size	__func__.55332, 24
__func__.55332:
	.ascii	"VDMHAL_V5R2C1_GlbResetX\000"
	.type	__func__.55318, %object
	.size	__func__.55318, 23
__func__.55318:
	.ascii	"VDMHAL_V5R2C1_GlbReset\000"
	.space	1
	.type	__func__.55341, %object
	.size	__func__.55341, 28
__func__.55341:
	.ascii	"VDMHAL_V5R2C1_ClearIntState\000"
	.type	__func__.55347, %object
	.size	__func__.55347, 31
__func__.55347:
	.ascii	"VDMHAL_V5R2C1_ClearMMUIntState\000"
	.space	1
	.type	__func__.55353, %object
	.size	__func__.55353, 22
__func__.55353:
	.ascii	"VDMHAL_V5R2C1_MaskInt\000"
	.space	2
	.type	__func__.55366, %object
	.size	__func__.55366, 24
__func__.55366:
	.ascii	"VDMHAL_V5R2C1_EnableInt\000"
	.type	__func__.55375, %object
	.size	__func__.55375, 23
__func__.55375:
	.ascii	"VDMHAL_V5R2C1_CheckReg\000"
	.space	1
	.type	__func__.55389, %object
	.size	__func__.55389, 26
__func__.55389:
	.ascii	"VDMHAL_V5R2C1_ReadMMUMask\000"
	.space	2
	.type	__func__.55394, %object
	.size	__func__.55394, 27
__func__.55394:
	.ascii	"VDMHAL_V5R2C1_WriteMMUMask\000"
	.space	1
	.type	__func__.55425, %object
	.size	__func__.55425, 25
__func__.55425:
	.ascii	"VDMHAL_V5R2C1_PrepareDec\000"
	.space	3
	.type	__func__.55430, %object
	.size	__func__.55430, 25
__func__.55430:
	.ascii	"VDMHAL_V5R2C1_IsVdmReady\000"
	.space	3
	.type	__func__.55435, %object
	.size	__func__.55435, 23
__func__.55435:
	.ascii	"VDMHAL_V5R2C1_IsVdmRun\000"
	.space	1
	.type	__func__.55441, %object
	.size	__func__.55441, 27
__func__.55441:
	.ascii	"VDMHAL_V5R2C1_IsVdhDecOver\000"
	.space	1
	.type	__func__.55451, %object
	.size	__func__.55451, 31
__func__.55451:
	.ascii	"VDMHAL_V5R2C1_IsVdhPartDecOver\000"
	.space	1
	.type	__func__.55466, %object
	.size	__func__.55466, 33
__func__.55466:
	.ascii	"VDMHAL_V5R2C1_UpdateHardwareInfo\000"
	.space	3
	.type	__func__.55539, %object
	.size	__func__.55539, 23
__func__.55539:
	.ascii	"VDMHAL_V5R2C1_CfgRpMsg\000"
	.space	1
	.type	__func__.55516, %object
	.size	__func__.55516, 24
__func__.55516:
	.ascii	"VDMHAL_CfgNotFullRepair\000"
	.type	__func__.55550, %object
	.size	__func__.55550, 23
__func__.55550:
	.ascii	"VDMHAL_V5R2C1_CfgRpReg\000"
	.space	1
	.type	__func__.55563, %object
	.size	__func__.55563, 28
__func__.55563:
	.ascii	"VDMHAL_V5R2C1_MakeDecReport\000"
	.type	__func__.55632, %object
	.size	__func__.55632, 28
__func__.55632:
	.ascii	"VDMHAL_V5R2C1_PrepareRepair\000"
	.type	__func__.55822, %object
	.size	__func__.55822, 15
__func__.55822:
	.ascii	"MFDE_ConfigReg\000"
	.space	1
	.type	__func__.55639, %object
	.size	__func__.55639, 28
__func__.55639:
	.ascii	"VDMHAL_V5R2C1_StartHwRepair\000"
	.type	__func__.55678, %object
	.size	__func__.55678, 28
__func__.55678:
	.ascii	"VDMHAL_V5R2C1_CalVdhClkSkip\000"
	.type	__func__.55704, %object
	.size	__func__.55704, 28
__func__.55704:
	.ascii	"VDMHAL_V5R2C1_StartHwDecode\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"pOpenParam = NULL error!\000" )
	.space	3
.LC1:
	ASCII(.ascii	"%s: %s\012\000" )
.LC2:
	ASCII(.ascii	"MemBaseAddr = 0 error!\000" )
	.space	1
.LC3:
	ASCII(.ascii	"VDMHAL_V5R2C1_OpenHAL: Size error!\000" )
	.space	1
.LC4:
	ASCII(.ascii	"VdhId is wrong!!!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"BPDRegVirAddr %p\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"!!!!!! HAL memory not enouph! need %d, have %d\012\000" )
.LC8:
	ASCII(.ascii	"image size out of range\000" )
.LC9:
	ASCII(.ascii	"VDMHAL ArrangeMem HEVC/VP9 10 bit\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"%s pstVfmwFrameSizeInfo = NULL\012\000" )
.LC11:
	ASCII(.ascii	"DelAllFrameMemRecord err in VDMHAL_V5R2C1_ArrangeMe" )
	ASCII(.ascii	"m!\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"Report arrange frame buffer: wxh %dx%d, FsNum %d, P" )
	ASCII(.ascii	"mvNum %d\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"Report arrange frame buffer only: wxh %dx%d, FsNum " )
	ASCII(.ascii	"%d, PmvNum %d\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"VidStd Invalid\000" )
	.space	1
.LC15:
	ASCII(.ascii	"Set CompressEn %d, LossCompressEn %d, YCompRatio %d" )
	ASCII(.ascii	", UVCompRatio %d\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"VDMHAL_V5R2C1_CalcFsSize err!\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"%s, need arrange, Size: %#x, Num: %#x, RefChanged: " )
	ASCII(.ascii	"%#x\012\000" )
.LC18:
	ASCII(.ascii	"DFS, report event. Size: 0x%x, Num: %d, RefChanged:" )
	ASCII(.ascii	" %d\012\000" )
.LC19:
	ASCII(.ascii	"pVdmMemArrange is NULL\000" )
	.space	1
.LC20:
	ASCII(.ascii	"DFS, no ref frame!\012\000" )
.LC21:
	ASCII(.ascii	"DFS, Frame number = %d > 30, Then, Frame num = 30, " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"VDMHAL_V5R2C1_ArrangeMem Mem addr is NULL\000" )
	.space	2
.LC23:
	ASCII(.ascii	"'pVdmMemArrange' is NULL\000" )
	.space	3
.LC24:
	ASCII(.ascii	"MemSize not enough for pmv slot\000" )
.LC25:
	ASCII(.ascii	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight" )
	ASCII(.ascii	" failed!\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"ImgSlotLen > ChanSlotLen\000" )
	.space	3
.LC27:
	ASCII(.ascii	"cann't allocate img slot\000" )
	.space	3
.LC28:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC29:
	ASCII(.ascii	"VDMHAL_V5R2C1_ResetVdm: map vdm register fail, vir(" )
	ASCII(.ascii	"reg) = (%p)\012\000" )
.LC30:
	ASCII(.ascii	"%s module id %d failed!\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"%s module id %d success!\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"%s VdhId %d failed!\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"%s VdhId %d success!\012\000" )
	.space	2
.LC35:
	ASCII(.ascii	"%s: map vdm register 0x%x failed!\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC37:
	ASCII(.ascii	"%s: VdhId(%d) Invalid!\012\000" )
.LC38:
	ASCII(.ascii	"%s: vdm register virtual address not mapped, reset " )
	ASCII(.ascii	"failed!\012\000" )
.LC39:
	ASCII(.ascii	"%s: unkown reg_id = %d\012\000" )
.LC40:
	ASCII(.ascii	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"%s: pDecParam(%p) = NULL\012\000" )
	.space	2
.LC42:
	ASCII(.ascii	"VDM register not mapped yet!\000" )
	.space	3
.LC43:
	ASCII(.ascii	"VDM register not mapped yet!\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"can NOT map vir addr for up-msg\000" )
.LC45:
	ASCII(.ascii	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"ReadUpMsgSlot error! upmsg_size(%d) > 512\012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"WriteMsgSlot error!\012\000" )
	.space	3
.LC48:
	ASCII(.ascii	"can not map repair msg virtual address!\000" )
.LC49:
	ASCII(.ascii	"ValidGroupNum=%d out of range!\012\000" )
.LC50:
	ASCII(.ascii	"align_mb error\012\000" )
.LC51:
	ASCII(.ascii	"[%s][%d]sclie_num is wrong! %d \012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"'pMakeDecReport' is NULL\000" )
	.space	3
.LC53:
	ASCII(.ascii	"'pDecReport' is NULL\000" )
	.space	3
.LC54:
	ASCII(.ascii	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full" )
	ASCII(.ascii	" repair.\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"\012***** UpMsg DecSliceNum=%d\012\000" )
	.space	3
.LC56:
	ASCII(.ascii	"\012***** Up Msg (phy addr: %#8x) *****\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"\012***** Up Msg print finished *****\012\000" )
.LC59:
	ASCII(.ascii	"vdm register virtual address not mapped, VDMHAL_V20" )
	ASCII(.ascii	"0R003_PrepareRepair failed!\012\000" )
.LC60:
	ASCII(.ascii	"FIRST_REPAIR Parameter Error!\012\000" )
	.space	1
.LC61:
	ASCII(.ascii	"SECOND_REPAIR Parameter Error!\012\000" )
.LC62:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"%s The channel %d is not active\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"BigTile1d_y\000" )
.LC65:
	ASCII(.ascii	"failed mem_allocMemBlock BigTile_yuv save!\012\000" )
.LC66:
	ASCII(.ascii	"BigTile1d_uv\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
