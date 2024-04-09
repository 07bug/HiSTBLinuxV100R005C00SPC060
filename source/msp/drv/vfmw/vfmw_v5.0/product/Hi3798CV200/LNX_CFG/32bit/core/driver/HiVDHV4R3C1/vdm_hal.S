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
	.global	VDMHAL_V4R3C1_GetHalMemSize
	.type	VDMHAL_V4R3C1_GetHalMemSize, %function
VDMHAL_V4R3C1_GetHalMemSize:
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
	.size	VDMHAL_V4R3C1_GetHalMemSize, .-VDMHAL_V4R3C1_GetHalMemSize
	.align	2
	.global	VDMHAL_V4R3C1_OpenHAL
	.type	VDMHAL_V4R3C1_OpenHAL, %function
VDMHAL_V4R3C1_OpenHAL:
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
	beq	.L23
	ldmia	r3, {r6, r8}
	ldr	r7, [r3, #8]
	cmp	r6, #0
	beq	.L24
	cmp	r8, #6291456
	blt	.L25
	cmp	r7, #0
	bgt	.L26
	ldr	r4, .L28
	mov	r2, #268
	ldr	r10, .L28+4
	mov	r1, #0
	ldr	r5, .L28+8
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
	ldr	r1, .L28+12
	mov	r3, r0
	mov	r2, r0
	str	r3, [r5, r9]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, #53248
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r1, .L28+16
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
.L19:
	str	r1, [r2, #4]!
	cmp	r2, r0
	add	r1, r1, #1280
	bne	.L19
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
	bcc	.L20
	mov	r0, r4
	bl	H264HAL_V4R3C1_InitHal
	mov	r5, r0
	mov	r0, r4
	bl	HEVCHAL_V4R3C1_InitHal
	cmp	r0, #0
	beq	.L27
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L27:
	adds	r0, r5, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L26:
	ldr	r1, .L28+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L20:
	mov	r3, r8
	ldr	r1, .L28+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L24:
	mov	r0, r6
	ldr	r3, .L28+28
	ldr	r2, .L28+32
	ldr	r1, .L28+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L25:
	ldr	r3, .L28+40
	mov	r0, #0
	ldr	r2, .L28+32
	ldr	r1, .L28+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L23:
	ldr	r3, .L28+44
	ldr	r2, .L28+32
	ldr	r1, .L28+36
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L29:
	.align	2
.L28:
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
	.size	VDMHAL_V4R3C1_OpenHAL, .-VDMHAL_V4R3C1_OpenHAL
	.align	2
	.global	VDMHAL_V4R3C1_CloseHAL
	.type	VDMHAL_V4R3C1_CloseHAL, %function
VDMHAL_V4R3C1_CloseHAL:
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
	.size	VDMHAL_V4R3C1_CloseHAL, .-VDMHAL_V4R3C1_CloseHAL
	.align	2
	.global	VDMHAL_V4R3C1_CalcFsSize
	.type	VDMHAL_V4R3C1_CalcFsSize, %function
VDMHAL_V4R3C1_CalcFsSize:
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
	str	r3, [fp, #-60]
	bhi	.L32
	sub	r3, r2, #32
	mov	r4, r2
	cmp	r3, r1
	bhi	.L32
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
	beq	.L50
	ldr	r2, [fp, #4]
	ldr	r9, .L56
	cmp	r2, #17
	beq	.L51
	add	r4, r8, #31
	ldr	r0, [r9, r7, asl #2]
	mov	r5, r5, asl #4
	bic	r4, r4, #31
	add	r5, r5, #255
	mov	r2, #0
	bic	r1, r5, #255
	str	r2, [fp, #-64]
	str	r1, [fp, #-56]
	str	r2, [fp, #-68]
.L36:
	ldr	r2, [r0, #1176]
	cmp	r2, #1
	movne	r5, #0
	movne	r10, r5
	movne	r8, r5
	beq	.L52
.L38:
	ldr	r2, [fp, #-60]
	cmp	r2, #1
	beq	.L53
	ldr	r2, [fp, #-56]
	add	r6, r8, r8, lsl #1
	ldr	r1, [fp, #-64]
	mul	r4, r4, r2
	ldr	r2, [fp, #-68]
	mul	r2, r2, r1
	add	r1, r4, r4, lsl #1
	mov	r1, r1, lsr #1
	add	r2, r2, r2, lsl #1
	add	r2, r1, r2, lsr #1
	add	r6, r2, r6, lsr #1
.L40:
	add	r2, r0, #290816
	ldr	r1, [r2, #1104]
	cmp	r1, #0
	beq	.L54
.L41:
	ldr	r1, [fp, #4]
	add	ip, r0, #294912
	cmp	r1, #17
	add	r1, r3, r3, lsr #31
	str	r6, [ip, #576]
	mov	r1, r1, asr #1
	str	r10, [r2, #3452]
	str	r5, [r2, #3456]
	str	r1, [r2, #3492]
	beq	.L42
	ldr	r1, [r2, #1112]
	ldr	ip, [fp, #-56]
	cmp	r1, #32
	ldr	lr, [fp, #4]
	mov	r5, ip, asl #4
	movge	r1, #32
	cmp	lr, #16
	str	r5, [r2, #3444]
	add	ip, r4, r8
	mov	r5, r5, lsr #1
	str	r1, [r2, #3496]
	str	r5, [r2, #3448]
	str	ip, [r2, #3476]
	beq	.L55
.L44:
	ldr	r2, [r9, r7, asl #2]
	mov	r0, #1024
	add	r6, r6, #1056
	add	r1, r2, #294912
	add	ip, r3, r6
	str	r3, [r1, #580]
	str	r0, [r1, #588]
	ldrsb	r2, [r2, #44]
	cmp	r2, #1
	ldr	r2, [fp, #8]
	addeq	ip, ip, r0
	cmp	r2, #0
	beq	.L48
	str	r6, [r2, #4]
	mov	r1, #1024
	ldr	r2, [r9, r7, asl #2]
	mov	r0, #0
	ldr	lr, [fp, #8]
	add	r2, r2, #290816
	ldr	r2, [r2, #1112]
	str	r3, [lr, #12]
	str	r2, [lr, #8]
	ldr	r3, [r9, r7, asl #2]
	add	r3, r3, #290816
	ldr	r3, [r3, #3496]
	str	ip, [lr]
	str	r1, [lr, #20]
	str	r3, [lr, #16]
	ldr	r3, [r9, r7, asl #2]
	add	r3, r3, #294912
	str	r6, [r3, #584]
.L34:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L55:
	ldr	r1, [r0, #1508]
	cmp	r1, #8
	ble	.L44
	ldr	r1, [fp, #-64]
	add	r8, r8, r8, lsl #1
	str	r3, [fp, #-56]
	add	r4, r4, r4, lsl #1
	ldr	r3, [fp, #-68]
	mul	ip, r1, r3
	mov	r1, r8, lsr #1
	mov	r0, r3, asl #5
	add	r4, r1, r4, lsr #1
	str	r0, [r2, #3460]
	mov	r0, #31
	ldr	r1, .L56+4
	str	r4, [r2, #3468]
	str	ip, [r2, #3472]
	bl	dprint_vfmw
	ldr	r3, [fp, #-56]
	b	.L44
.L54:
	ldr	ip, .L56+8
	add	r0, r2, #3440
	str	r3, [fp, #-60]
	mov	r2, #1248
	ldr	r3, [ip, #48]
	blx	r3
	ldr	r0, [r9, r7, asl #2]
	ldr	r3, [fp, #-60]
	add	r2, r0, #290816
	b	.L41
.L42:
	ldr	r1, [fp, #-56]
	add	r4, r4, r8
	str	r4, [r2, #3476]
	mov	r5, r1, asl #4
	mov	r1, #1
	str	r5, [r2, #3444]
	str	r1, [r2, #3496]
	mov	r5, r5, lsr r1
	str	r5, [r2, #3448]
	b	.L44
.L53:
	mov	r2, r6, asl #5
	add	r6, r2, r6, lsl #4
	ldr	r2, [fp, #-56]
	mul	r4, r4, r2
	mul	r6, r2, r6
	b	.L40
.L52:
	add	r2, r10, #508
	add	r10, r10, #1020
	add	r2, r2, #3
	add	r10, r10, #2
	cmp	r2, #0
	movge	r10, r2
	adds	r2, r8, #63
	addmi	r8, r8, #126
	movpl	r8, r2
	mov	r10, r10, asr #9
	mov	r8, r8, asr #6
	mov	r10, r10, asl #4
	mov	r8, r8, asl #5
	mul	r8, r10, r8
	mov	r5, r8
	b	.L38
.L50:
	ldr	r9, .L56
	add	r5, r10, #255
	bic	r2, r5, #255
	str	r2, [fp, #-56]
	ldr	r0, [r9, r7, asl #2]
	ldr	r2, [r0, #1508]
	cmp	r2, #8
	ble	.L46
	ldr	r1, [fp, #-56]
	add	r2, r8, #31
	bic	r2, r2, #31
	str	r2, [fp, #-64]
	mov	r1, r1, lsr #2
	str	r1, [fp, #-68]
	b	.L36
.L46:
	mov	r2, #0
	str	r2, [fp, #-64]
	str	r2, [fp, #-68]
	b	.L36
.L51:
	add	r5, r10, #255
	add	r4, r8, #63
	mov	r2, #0
	bic	r1, r5, #255
	str	r2, [fp, #-64]
	bic	r4, r4, #63
	str	r1, [fp, #-56]
	ldr	r0, [r9, r7, asl #2]
	str	r2, [fp, #-68]
	b	.L36
.L32:
	ldr	r3, .L56+12
	mov	r0, #0
	ldr	r2, .L56+16
	ldr	r1, .L56+20
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L48:
	ldr	r0, [fp, #8]
	b	.L34
.L57:
	.align	2
.L56:
	.word	s_pstVfmwChan
	.word	.LC9
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	.LANCHOR0+24
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CalcFsSize, .-VDMHAL_V4R3C1_CalcFsSize
	.align	2
	.global	VDMHAL_V4R3C1_GetRpuSize
	.type	VDMHAL_V4R3C1_GetRpuSize, %function
VDMHAL_V4R3C1_GetRpuSize:
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
	.size	VDMHAL_V4R3C1_GetRpuSize, .-VDMHAL_V4R3C1_GetRpuSize
	.align	2
	.global	VDMHAL_V4R3C1_CalcFsNum
	.type	VDMHAL_V4R3C1_CalcFsNum, %function
VDMHAL_V4R3C1_CalcFsNum:
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
	beq	.L64
	cmp	r1, #17
	ldr	ip, .L66
	beq	.L65
	ldr	lr, [ip, r0, asl #2]
	add	r0, lr, #290816
	ldr	r1, [r0, #1112]
	cmp	r1, #32
	movge	r1, #32
	str	r1, [r0, #3496]
	ldr	r1, [lr, #600]
	cmp	r1, #2
	ldreq	r1, [r0, #1116]
	streq	r1, [r0, #3496]
.L63:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #0
	add	r1, r1, #290816
	ldr	r1, [r1, #1112]
	str	r1, [r3, #8]
	ldr	r2, [ip, r2, asl #2]
	add	r2, r2, #290816
	ldr	r2, [r2, #3496]
	str	r2, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L65:
	ldr	r1, [ip, r2, asl #2]
	mov	r0, #1
	add	r1, r1, #290816
	str	r0, [r1, #3496]
	b	.L63
.L64:
	ldr	r2, .L66+4
	mov	r0, #1
	ldr	r1, .L66+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L67:
	.align	2
.L66:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+52
	.word	.LC10
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CalcFsNum, .-VDMHAL_V4R3C1_CalcFsNum
	.align	2
	.global	VDMHAL_V4R3C1_DynamicAllocFrame
	.type	VDMHAL_V4R3C1_DynamicAllocFrame, %function
VDMHAL_V4R3C1_DynamicAllocFrame:
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
	ldr	r6, .L88
	mov	r8, r1
	mov	r4, r0
	mov	r7, r2
	mov	r5, r3
	ldr	r1, [r6, r0, asl #2]
	add	r1, r1, #290816
	add	r1, r1, #1136
	bl	DelAllFrameMemRecord
	cmp	r0, #0
	bne	.L87
.L69:
	ldr	r2, [r6, r4, asl #2]
	mov	r3, #0
	mov	r1, #255
	add	r2, r2, #290816
	add	r2, r2, #1136
.L70:
	str	r1, [r2, r3]
	add	r3, r3, #72
	cmp	r3, #2304
	bne	.L70
	cmp	r8, #1920
	cmple	r7, #1088
	ble	.L71
	ldr	r2, [r5, #8]
	ldr	r3, [r6, r4, asl #2]
.L72:
	ldr	r1, [r3, #1456]
	add	r3, r3, #290816
	mov	r0, r4
	add	r2, r2, r1
	str	r2, [r3, #1116]
	bl	VCTRL_GetVidStd
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L88
	ldr	r2, [r3, #600]
	subs	r0, r0, #17
	movne	r0, #1
	cmp	r2, #2
	movne	r0, #0
	cmp	r0, #0
	addne	r3, r3, #290816
	mov	r0, #1
	ldrne	r3, [r3, #1116]
	strne	r3, [r5, #16]
	ldrne	r3, [r1, r4, asl #2]
	add	r1, r3, #294912
	add	r2, r3, #262144
	mov	r3, #0
	str	r3, [r1, #616]
	mov	r3, r7
	str	r0, [r2, #2016]
	mov	r2, r8
	str	r0, [r1, #1156]
	mov	r0, #31
	ldr	r1, [r5, #8]
	ldr	ip, [r5, #16]
	stmia	sp, {r1, ip}
	ldr	r1, .L88+4
	bl	dprint_vfmw
	ldr	r3, .L88+8
	ldr	r9, [r3]
	cmp	r9, #0
	beq	.L76
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
.L76:
	ldr	r0, [r6, r4, asl #2]
	mov	r1, #0
	ldr	r3, .L88+12
	mov	r2, #528
	add	r0, r0, #294912
	add	r0, r0, #624
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #0
	mov	r0, r4
	add	r3, r3, #294912
	str	r2, [r3, #1152]
	bl	FSP_ClearContextAll
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L71:
	ldr	r3, [r6, r4, asl #2]
	ldr	r1, .L88
	ldr	r2, [r3, #36]
	cmp	r2, #24
	ldreq	r2, [r5, #8]
	beq	.L72
	add	r2, r3, #294912
	ldr	r2, [r2, #1212]
	cmp	r2, #0
	ldr	r2, [r5, #8]
	addeq	r2, r2, #4
	streq	r2, [r5, #8]
	ldreq	r3, [r1, r4, asl #2]
	b	.L72
.L87:
	ldr	r1, .L88+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L69
.L89:
	.align	2
.L88:
	.word	s_pstVfmwChan
	.word	.LC12
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_DynamicAllocFrame, .-VDMHAL_V4R3C1_DynamicAllocFrame
	.align	2
	.global	VDMHAL_V4R3C1_DynamicAllocFrame_Only
	.type	VDMHAL_V4R3C1_DynamicAllocFrame_Only, %function
VDMHAL_V4R3C1_DynamicAllocFrame_Only:
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
	ldr	ip, .L95
	ldr	lr, [r3, #8]
	mov	r4, r3
	mov	r8, r0
	mov	r3, r2
	ldr	ip, [ip, r0, asl #2]
	mov	r7, r1
	mov	r6, r2
	mov	r0, #31
	add	ip, ip, #290816
	mov	r2, r1
	ldr	r1, .L95+4
	str	lr, [ip, #1116]
	ldr	lr, [r4, #16]
	ldr	ip, [r4, #8]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldr	r3, .L95+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L90
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
.L90:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L96:
	.align	2
.L95:
	.word	s_pstVfmwChan
	.word	.LC13
	.word	g_event_report
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_DynamicAllocFrame_Only, .-VDMHAL_V4R3C1_DynamicAllocFrame_Only
	.align	2
	.global	VDMHAL_V4R3C1_ArrangeMem_Normal
	.type	VDMHAL_V4R3C1_ArrangeMem_Normal, %function
VDMHAL_V4R3C1_ArrangeMem_Normal:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 40
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
	bhi	.L127
	ldr	r10, .L135
	ldr	r1, [r10, r4, asl #2]
	add	r2, r1, #290816
	ldr	r3, [r1, #100]
	ldr	r2, [r2, #1108]
	cmp	r3, #2
	str	r2, [fp, #-76]
	beq	.L128
	ldr	ip, [r1, #1188]
	mov	r2, #1
	ldr	r3, [r1, #1180]
	mov	r0, r2
	str	r2, [r1, #1176]
	str	ip, [sp, #4]
	ldr	ip, [r1, #1184]
	ldr	r1, .L135+4
	str	ip, [sp]
	bl	dprint_vfmw
.L101:
	sub	r6, fp, #68
	ldr	r2, [fp, #4]
	mov	r1, r5
	mov	r0, r4
	mov	r3, r6
	bl	VDMHAL_V4R3C1_CalcFsNum
	ldr	r3, [fp, #8]
	str	r6, [sp, #4]
	mov	r2, r8
	str	r5, [sp]
	mov	r1, r7
	mov	r9, r0
	mov	r0, r4
	bl	VDMHAL_V4R3C1_CalcFsSize
	orrs	r3, r0, r9
	bne	.L129
	ldr	r3, [r10, r4, asl #2]
	ldr	r1, [fp, #-76]
	ldr	r5, [fp, #-68]
	str	r3, [fp, #-72]
	add	r3, r3, #290816
	cmp	r1, r5
	ldr	r2, .L135
	ldr	r9, [r3, #1112]
	ldr	r1, [r3, #1128]
	beq	.L130
.L104:
	str	r1, [sp, #4]
	mov	r3, r5
	ldr	r2, .L135+8
	mov	r0, #31
	ldr	r1, .L135+12
	str	r9, [sp]
	bl	dprint_vfmw
	ldr	r3, [r10, r4, asl #2]
	mov	r1, r7
	mov	r0, r4
	add	r3, r3, #290816
	ldr	r2, [r3, #1104]
	str	r5, [r3, #1108]
	mov	r3, r6
	cmp	r2, #0
	mov	r2, r8
	beq	.L131
	bl	VDMHAL_V4R3C1_DynamicAllocFrame_Only
.L107:
	ldr	ip, [r10, r4, asl #2]
	mov	r3, r9
	mov	r2, r5
	ldr	r1, .L135+16
	add	ip, ip, #290816
	mov	r0, #31
	ldr	ip, [ip, #1128]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, .L135+20
	ldr	r4, [r10, r4, asl #2]
	ldr	r3, [r3]
	add	r4, r4, #294912
	blx	r3
	mov	r3, #2
	str	r0, [r4, #592]
.L99:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L130:
	cmp	r1, #1
	beq	.L104
	ldr	r0, [r3, #1104]
	cmp	r0, #1
	beq	.L104
	ldr	r1, [fp, #12]
	cmp	r1, #0
	beq	.L132
	ldr	r1, [fp, #-72]
	cmp	r9, #0
	add	r0, r3, #3440
	str	r0, [fp, #-80]
	add	r1, r1, #294912
	ldrne	r2, [fp, #-72]
	ldr	r9, [r1, #576]
	beq	.L133
.L109:
	add	r2, r2, #290816
	ldr	r2, [r2, #1116]
	cmp	r2, #30
	bgt	.L134
.L110:
	str	r2, [r3, #3488]
	mov	r0, #8
	str	r3, [fp, #-76]
	ldr	r3, .L135+20
	ldr	r2, [r3, #12]
	blx	r2
	ldr	r1, [r10, r4, asl #2]
	ldr	r3, [fp, #-76]
	add	r8, r1, #294912
	ldr	r2, [r8, #616]
	cmp	r2, #0
	beq	.L115
	ldr	r2, [r3, #3500]
	movw	r5, #8047
	ldr	r0, [r3, #3496]
	movt	r5, 1
	ldr	lr, [fp, #-72]
	add	r5, r2, r5
	add	r1, r1, #290816
	mov	ip, #0
	str	r0, [fp, #-76]
	mov	r0, r2, asl #4
	sub	r0, r0, r2, asl #2
	add	r2, r2, #1
	add	r0, r0, #290816
	add	r1, r1, #1168
	add	r0, r0, #3904
	add	r5, lr, r5, lsl #2
	add	r0, lr, r0
	mov	r6, r2
	mov	r7, #1
	str	r4, [fp, #-84]
.L114:
	ldr	r2, [r1]
	add	lr, r6, ip
	ldr	r4, [r1, #-20]
	add	ip, ip, #1
	add	r2, r2, #1020
	strb	r7, [r0, #8]
	add	r2, r2, #3
	add	r0, r0, #12
	bic	r2, r2, #1020
	str	r4, [r0, #-8]
	bic	r2, r2, #3
	str	r2, [r0, #-12]
	add	r2, r2, r9
	str	r2, [r5, #4]!
	str	lr, [r3, #3500]
	ldr	r2, [r1, #-28]
	cmp	r2, #255
	beq	.L112
	ldr	lr, [r3, #3508]
	add	r4, lr, #1
	mov	r2, lr, asl #4
	sub	r2, r2, lr, asl #2
	ldr	lr, [r1, #16]
	add	r2, r3, r2
	add	r2, r2, #4288
	str	lr, [r2]
	str	r4, [r3, #3508]
.L112:
	ldr	r2, [r3, #3504]
	ldr	lr, [fp, #-76]
	cmp	r2, lr
	bcs	.L113
	ldr	r4, [r1, #-24]
	ldr	lr, [fp, #-72]
	cmp	r4, #255
	add	lr, lr, r2, lsl #3
	add	r2, r2, #1
	ldrne	r4, [r1, #32]
	add	lr, lr, #290816
	strneb	r7, [lr, #3652]
	strne	r4, [lr, #3648]
	strne	r2, [r3, #3504]
.L113:
	ldr	r2, [r8, #616]
	add	r1, r1, #72
	cmp	ip, r2
	bcc	.L114
	ldr	r4, [fp, #-84]
.L115:
	ldr	r3, .L135+20
	mov	r2, #1232
	ldr	r1, [fp, #-80]
	ldr	r0, [fp, #12]
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r10, r4, asl #2]
	ldr	r2, .L135+20
	mov	r1, #1
	add	r3, r3, #294912
	mov	r0, #8
	str	r1, [r3, #620]
	ldr	r2, [r2, #16]
	blx	r2
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L131:
	bl	VDMHAL_V4R3C1_DynamicAllocFrame
	b	.L107
.L128:
	mvn	r3, #0
	str	r0, [r1, #1176]
	str	r0, [r1, #1180]
	str	r3, [r1, #1184]
	str	r3, [r1, #1188]
	b	.L101
.L133:
	ldr	r1, .L135+24
	mov	r0, #31
	str	r3, [fp, #-84]
	str	r2, [fp, #-76]
	bl	dprint_vfmw
	ldr	r2, [fp, #-76]
	ldr	r3, [fp, #-84]
	ldr	r2, [r2, r4, asl #2]
	b	.L109
.L134:
	ldr	r1, .L135+28
	mov	r0, #31
	str	r3, [fp, #-76]
	bl	dprint_vfmw
	ldr	r1, [r10, r4, asl #2]
	mov	r0, #30
	mov	r2, r0
	ldr	r3, [fp, #-76]
	add	r1, r1, #290816
	str	r0, [r1, #1116]
	b	.L110
.L127:
	ldr	r3, .L135+32
	ldr	r2, .L135+36
	ldr	r1, .L135+40
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L99
.L129:
	ldr	r1, .L135+44
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L99
.L132:
	ldr	r3, .L135+48
	mov	r0, r1
	ldr	r2, .L135+52
	ldr	r1, .L135+40
	bl	dprint_vfmw
	mvn	r3, #0
	b	.L99
.L136:
	.align	2
.L135:
	.word	s_pstVfmwChan
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
	.size	VDMHAL_V4R3C1_ArrangeMem_Normal, .-VDMHAL_V4R3C1_ArrangeMem_Normal
	.global	__aeabi_idiv
	.align	2
	.global	VDMHAL_V4R3C1_ArrangeMem_Specific
	.type	VDMHAL_V4R3C1_ArrangeMem_Specific, %function
VDMHAL_V4R3C1_ArrangeMem_Specific:
	UNWIND(.fnstart)
	@ args = 28, pretend = 0, frame = 64
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
	cmp	r2, #0
	str	r3, [fp, #-76]
	mov	r10, r0
	str	r2, [fp, #-72]
	mov	r8, r1
	ldmib	fp, {r5, r9}
	ldr	r3, [fp, #12]
	ldr	r4, [fp, #28]
	beq	.L202
	sub	r1, r5, #32
	movw	r2, #8160
	cmp	r1, r2
	bhi	.L140
	sub	r1, r9, #32
	cmp	r1, r2
	bhi	.L140
	cmp	r4, #0
	beq	.L203
	ldr	ip, .L211
	cmp	r3, #20
	mov	r2, #1232
	mov	r1, #0
	mov	r0, r4
	movge	r3, #20
	ldr	r6, [ip, #48]
	str	r3, [fp, #-80]
	blx	r6
	sub	r2, fp, #44
	add	r1, r9, #15
	add	r6, r5, #15
	mov	r0, r8
	mov	r3, r1, asr #4
	sub	r1, fp, #64
	str	r3, [r2, #-16]!
	mov	r6, r6, asr #4
	str	r3, [fp, #-96]
	str	r6, [fp, #-64]
	bl	VDMHAL_CalcPmvSlotLen.isra.0
	ldr	r3, [fp, #-80]
	ldr	r1, [fp, #-76]
	mul	r2, r3, r0
	mov	r7, r0
	cmp	r2, r1
	str	r2, [fp, #-92]
	ldrge	r3, .L211+4
	bge	.L201
	ldr	r0, [fp, #-72]
	add	r1, r7, r7, lsr #31
	cmp	r8, #16
	str	r3, [r4, #56]
	add	r2, r0, #1020
	mov	r3, r1, asr #1
	add	r2, r2, #3
	str	r3, [r4, #52]
	bic	r2, r2, #1020
	bic	r2, r2, #3
	rsb	r1, r0, r2
	str	r1, [fp, #-80]
	beq	.L204
	cmp	r8, #17
	beq	.L205
	mov	r6, r6, asl #4
	add	r3, r9, #31
	add	r6, r6, #255
	bic	r3, r3, #31
	bic	r6, r6, #255
	add	r1, r9, #63
	mov	r0, #0
	str	r0, [fp, #-84]
	str	r0, [fp, #-88]
.L146:
	add	r0, r5, #508
	add	r5, r5, #1020
	add	r0, r0, #3
	add	r5, r5, #2
	cmp	r0, #0
	add	ip, r1, #63
	movlt	r0, r5
	cmp	r1, #0
	mov	r0, r0, asr #9
	movlt	r1, ip
	ldr	ip, [fp, #20]
	mov	r1, r1, asr #6
	cmp	ip, #1
	mov	ip, r6, asl #4
	str	ip, [r4, #4]
	mov	ip, r0, asl #9
	mov	r0, r0, asl #4
	str	r0, [r4, #12]
	mul	r1, r1, ip
	mov	r0, r6, asl #3
	str	r0, [r4, #8]
	str	r1, [r4, #16]
	beq	.L206
	ldr	ip, [fp, #-84]
	add	r5, r1, r1, lsl #1
	ldr	r0, [fp, #-88]
	mul	r0, r0, ip
	mul	ip, r6, r3
	add	r0, r0, r0, lsl #1
	add	r0, r0, r0, lsr #31
	add	ip, ip, ip, lsl #1
	mov	r0, r0, asr #1
	add	r0, r0, ip, asr #1
	add	r5, r0, r5, lsr #1
.L150:
	ldr	r0, [fp, #24]
	cmp	r0, #0
	blt	.L151
	str	r3, [fp, #-104]
	str	r1, [fp, #-100]
	str	r2, [fp, #-96]
	bl	VCTRL_GetChanWidth
	mov	r9, r0
	ldr	r0, [fp, #24]
	bl	VCTRL_GetChanHeight
	ldr	r2, [fp, #-96]
	ldr	r1, [fp, #-100]
	ldr	r3, [fp, #-104]
	cmn	r0, #1
	cmnne	r9, #1
	beq	.L207
	ldr	lr, [fp, #20]
	add	ip, r9, #15
	bic	ip, ip, #15
	add	r0, r0, #15
	cmp	lr, #1
	add	r9, ip, #255
	bic	r0, r0, #15
	bic	r9, r9, #255
	beq	.L208
	add	lr, ip, #508
	adds	r10, r0, #63
	add	lr, lr, #3
	addmi	r10, r0, #126
	cmp	lr, #0
	add	ip, ip, #1020
	add	ip, ip, #2
	ldr	r0, [fp, #-88]
	movge	ip, lr
	mov	lr, r10, asr #6
	ldr	r10, [fp, #-84]
	mul	r9, lr, r9
	mul	r10, r0, r10
	mov	r0, ip, asr #9
	mov	ip, lr, asl #7
	mov	r0, r0, asl #4
	sub	lr, ip, lr, asl #5
	mul	lr, r0, lr
	add	r10, r10, r10, lsl #1
	mov	r0, r9, asl #7
	add	r10, r10, r10, lsr #31
	sub	r9, r0, r9, asl #5
	add	r9, r9, r10, asr #1
	add	lr, r9, lr, lsr #1
.L154:
	cmp	r5, lr
	ldrgt	r3, .L211+8
	bgt	.L201
	ldr	r10, [fp, #24]
.L151:
	mul	r6, r6, r3
	cmp	r10, #0
	cmpge	r8, #16
	mvn	r9, r10
	str	r1, [fp, #-96]
	mov	r9, r9, lsr #31
	add	r3, r1, r6
	str	r3, [r4, #36]
	bne	.L156
	ldr	r3, .L211+12
	str	r2, [fp, #-100]
	ldr	r0, [r3, r10, asl #2]
	add	r0, r0, #294912
	add	r0, r0, #1232
	bl	IsMain10Profile
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-96]
	cmp	r0, #0
	bne	.L209
.L156:
	ldr	r3, [fp, #16]
	cmp	r3, #0
	streq	r3, [r4, #48]
	beq	.L159
	ldr	r3, [fp, #-76]
	ldr	r1, [fp, #-92]
	str	r2, [fp, #-76]
	rsb	r0, r1, r3
	ldr	r3, [fp, #-80]
	mov	r1, r5
	rsb	r0, r3, r0
	ldr	r3, [fp, #16]
	cmp	r3, #32
	movlt	r6, r3
	movge	r6, #32
	bl	__aeabi_idiv
	ldr	r2, [fp, #-76]
	cmp	r6, r0
	movlt	r1, r6
	movge	r1, r0
	cmp	r1, #0
	str	r1, [r4, #48]
	beq	.L159
	ldr	lr, [r4, #60]
	mov	ip, r4
	mov	r0, r2
	mov	r3, #0
.L164:
	add	r3, r3, #1
	str	r0, [ip, #464]
	cmp	r3, r1
	add	r0, r0, r5
	add	ip, ip, #12
	bne	.L164
	ldr	r3, [fp, #20]
	cmp	r3, #1
	add	r3, lr, r1
	str	r3, [r4, #60]
	beq	.L210
	ldr	r3, [fp, #-80]
	mla	r5, r1, r5, r3
	ldr	r3, [fp, #-72]
	add	r3, r5, r3
.L177:
	add	r0, r4, #76
	mov	r2, #0
.L168:
	add	r2, r2, #1
	str	r3, [r0, #4]!
	cmp	r2, r1
	add	r3, r3, #32
	bne	.L168
.L167:
	ldr	ip, [r4, #56]
	add	r5, r5, r1, lsl #5
	ldr	r3, [fp, #-72]
	cmp	ip, #0
	add	lr, r5, r3
	beq	.L173
	ldr	r6, [r4, #64]
	mov	r0, r4
	mov	r2, lr
	mov	r3, #0
.L172:
	add	r3, r3, #1
	str	r2, [r0, #208]
	cmp	ip, r3
	add	r2, r2, r7
	add	r0, r0, #8
	bne	.L172
	add	r3, ip, r6
	str	r3, [r4, #64]
.L173:
	mla	r7, ip, r7, r5
	cmp	r9, #0
	str	r7, [r4]
	beq	.L171
	ldr	r3, .L211+12
	ldr	r3, [r3, r10, asl #2]
	cmp	r3, #0
	beq	.L171
	cmp	r1, #0
	add	r3, r7, lr
	beq	.L171
	mov	r0, r4
	mov	r2, #0
.L174:
	add	r2, r2, #1
	str	r3, [r0, #848]
	cmp	r2, r1
	add	r3, r3, #1024
	add	r0, r0, #12
	bne	.L174
.L171:
	mov	r0, #0
	add	r7, r7, r1, lsl #10
	str	r7, [r4]
.L199:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L204:
	cmp	r10, #0
	add	r6, r5, #255
	bic	r6, r6, #255
	blt	.L200
	ldr	r3, .L211+12
	str	r2, [fp, #-84]
	ldr	r0, [r3, r10, asl #2]
	add	r0, r0, #294912
	add	r0, r0, #1232
	bl	IsMain10Profile
	ldr	r2, [fp, #-84]
	cmp	r0, #0
	beq	.L200
	cmp	r6, #0
	add	r0, r6, #3
	add	r3, r9, #31
	add	r1, r9, #63
	movge	r0, r6
	bic	r3, r3, #31
	mov	r0, r0, asr #2
	str	r3, [fp, #-84]
	str	r0, [fp, #-88]
	mov	r3, r9
	b	.L146
.L206:
	ldr	r0, [fp, #-96]
	mov	r5, r0, asl #4
	mul	r5, r6, r5
	add	r5, r5, r5, lsl #1
	b	.L150
.L210:
	ldr	r3, .L211+16
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L166
	str	r2, [fp, #-56]
	mov	r3, #12
	str	r1, [fp, #-48]
	sub	r2, fp, #56
	mov	r1, #128
	str	r5, [fp, #-52]
	mov	r0, r10
	blx	r6
	ldr	r1, [r4, #48]
.L166:
	ldr	r3, [fp, #-80]
	cmp	r1, #0
	mla	r5, r1, r5, r3
	ldr	r3, [fp, #-72]
	add	r3, r5, r3
	bne	.L177
	b	.L167
.L200:
	mov	r3, #0
	add	r1, r9, #63
	str	r3, [fp, #-84]
	str	r3, [fp, #-88]
	mov	r3, r9
	b	.L146
.L159:
	ldr	r3, .L211+20
.L201:
	ldr	r2, .L211+24
	mov	r0, #0
	ldr	r1, .L211+28
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L208:
	mul	lr, r0, r9
	add	lr, lr, lr, lsl #1
	b	.L154
.L205:
	mov	r3, #0
	add	r1, r9, #63
	add	r6, r5, #255
	mov	r0, r3
	str	r3, [fp, #-84]
	bic	r6, r6, #255
	bic	r3, r1, #63
	str	r0, [fp, #-88]
	b	.L146
.L140:
	ldr	r3, .L211+32
	b	.L201
.L209:
	ldr	r0, [fp, #-84]
	add	r6, r6, r6, lsl #1
	str	r2, [fp, #-96]
	add	r3, r1, r1, lsl #1
	ldr	r2, [fp, #-88]
	mov	r6, r6, asr #1
	add	r6, r6, r3, lsr #1
	str	r6, [r4, #28]
	mul	ip, r2, r0
	mov	r0, r2, asl #5
	str	r0, [r4, #20]
	mov	r0, #0
	add	r1, ip, r1, lsr #1
	str	r1, [r4, #32]
	ldr	r1, .L211+36
	bl	dprint_vfmw
	ldr	r2, [fp, #-96]
	b	.L156
.L202:
	mov	r0, r2
	ldr	r3, .L211+40
	ldr	r2, .L211+24
	ldr	r1, .L211+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L199
.L207:
	ldr	r1, .L211+44
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L199
.L203:
	mov	r0, r4
	ldr	r3, .L211+48
	ldr	r2, .L211+24
	ldr	r1, .L211+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L199
.L212:
	.align	2
.L211:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	.word	.LC26
	.word	s_pstVfmwChan
	.word	g_event_report
	.word	.LC27
	.word	.LANCHOR0+176
	.word	.LC1
	.word	.LC8
	.word	.LC9
	.word	.LC22
	.word	.LC25
	.word	.LC23
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ArrangeMem_Specific, .-VDMHAL_V4R3C1_ArrangeMem_Specific
	.align	2
	.global	VDMHAL_V4R3C1_ArrangeMem
	.type	VDMHAL_V4R3C1_ArrangeMem, %function
VDMHAL_V4R3C1_ArrangeMem:
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
	beq	.L216
	cmp	r4, #0
	blt	.L217
	mov	r0, r4
	str	r3, [fp, #-52]
	str	r1, [fp, #-48]
	bl	VCTRL_GetVidStd
	ldr	r2, .L220
	ldr	r1, [fp, #-48]
	ldr	r3, [fp, #-52]
	ldr	r2, [r2, r4, asl #2]
	ldr	r2, [r2, #1448]
	cmp	r2, #1
	beq	.L219
.L215:
	str	r3, [sp, #24]
	mov	r2, r9
	mov	r3, r1
	str	r4, [sp, #20]
	mov	r1, r0
	str	r8, [sp, #16]
	str	r10, [sp, #12]
	mov	r0, r4
	stmia	sp, {r5, r6, r7}
	bl	VDMHAL_V4R3C1_ArrangeMem_Specific
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L217:
	mov	r0, #22
	b	.L215
.L216:
	mov	r0, #16
	b	.L215
.L219:
	str	r3, [fp, #12]
	mov	r1, r0
	mov	r3, r6
	str	r8, [fp, #8]
	mov	r2, r5
	str	r7, [fp, #4]
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDMHAL_V4R3C1_ArrangeMem_Normal
.L221:
	.align	2
.L220:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ArrangeMem, .-VDMHAL_V4R3C1_ArrangeMem
	.align	2
	.global	VDMHAL_V4R3C1_ResetVdm
	.type	VDMHAL_V4R3C1_ResetVdm, %function
VDMHAL_V4R3C1_ResetVdm:
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
	ble	.L223
	mov	r3, r7
	str	r0, [sp]
	ldr	r2, .L237
	ldr	r1, .L237+4
	bl	dprint_vfmw
.L222:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L223:
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L235
	movw	r3, #1228
	ldr	r9, .L237+8
	mul	r3, r3, r7
	ldr	r5, .L237+12
	ldr	r2, [r5]
	ldr	r3, [r9, r3]
	ldr	r10, [r3, #36]
	ldr	r8, [r2, #120]
	tst	r8, #1
	beq	.L222
	ldr	r6, .L237+16
	mov	r3, #2
	bfi	r8, r3, #8, #2
	str	r8, [r2, #120]
	mov	r4, #0
	orr	r8, r8, #64
	ldr	r3, [r6, #112]
	blx	r3
	ldr	r3, [r5]
	str	r8, [r3, #120]
	b	.L227
.L236:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L228
.L227:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	ldr	r3, [r5]
	ldr	r3, [r3, #372]
	tst	r3, #4
	beq	.L236
	cmp	r4, #1000
	bge	.L228
	mov	r3, r7
	ldr	r2, .L237
	ldr	r1, .L237+20
	mov	r0, #0
	bl	dprint_vfmw
.L230:
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
.L228:
	mov	r3, r7
	ldr	r2, .L237
	ldr	r1, .L237+24
	mov	r0, #0
	bl	dprint_vfmw
	b	.L230
.L235:
	ldr	r1, .L237+28
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L238:
	.align	2
.L237:
	.word	.LANCHOR0+212
	.word	.LC28
	.word	g_HwMem
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ResetVdm, .-VDMHAL_V4R3C1_ResetVdm
	.align	2
	.global	VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.type	VDMHAL_V4R3C1_SetSmmuPageTableAddr, %function
VDMHAL_V4R3C1_SetSmmuPageTableAddr:
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
	ldr	r3, .L245
	mov	r4, r0
	ldr	r3, [r3, #196]
	cmp	r3, #0
	beq	.L239
	sub	r2, fp, #24
	sub	r1, fp, #28
	sub	r0, fp, #32
	blx	r3
	cmp	r4, #0
	bne	.L241
	ldr	r3, .L245+4
	ldr	r0, [fp, #-32]
	ldr	r1, [fp, #-28]
	ldr	r3, [r3]
	ldr	r2, [fp, #-24]
	add	r3, r3, #61440
	str	r0, [r3, #524]
	str	r1, [r3, #772]
	str	r2, [r3, #776]
.L239:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L241:
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L245+8
	ldr	r1, .L245+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L245+8
	ldr	r1, .L245+12
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L245+8
	ldr	r1, .L245+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L246:
	.align	2
.L245:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HwMem
	.word	.LANCHOR0+236
	.word	.LC32
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_SetSmmuPageTableAddr, .-VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.align	2
	.global	VDMHAL_V4R3C1_EnableSmmu
	.type	VDMHAL_V4R3C1_EnableSmmu, %function
VDMHAL_V4R3C1_EnableSmmu:
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
	ldr	r3, .L248
	mov	r2, #8
	ldr	r3, [r3]
	add	r3, r3, #61440
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L249:
	.align	2
.L248:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_EnableSmmu, .-VDMHAL_V4R3C1_EnableSmmu
	.align	2
	.global	VDMHAL_V4R3C1_GlbResetX
	.type	VDMHAL_V4R3C1_GlbResetX, %function
VDMHAL_V4R3C1_GlbResetX:
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
	mov	r8, r0
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L262
	ldr	r5, .L264
	ldr	r3, [r5]
	ldr	r7, [r3, #120]
	tst	r7, #1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r6, .L264+4
	mov	r2, #2
	bfi	r7, r2, #8, #2
	str	r7, [r3, #120]
	mov	r4, #0
	orr	r7, r7, #16
	ldr	r3, [r6, #112]
	blx	r3
	ldr	r3, [r5]
	str	r7, [r3, #120]
	b	.L254
.L263:
	add	r4, r4, #1
	cmp	r4, #1000
	beq	.L255
.L254:
	ldr	r3, [r6, #116]
	mov	r0, #30
	blx	r3
	ldr	r3, [r5]
	ldr	r3, [r3, #372]
	tst	r3, #1
	beq	.L263
	cmp	r4, #1000
	bge	.L255
	mov	r3, r8
	ldr	r2, .L264+8
	ldr	r1, .L264+12
	mov	r0, #0
	bl	dprint_vfmw
.L257:
	ldr	r2, [r5]
	bfc	r7, #4, #1
	ldr	r3, [r6, #112]
	str	r7, [r2, #120]
	bfc	r7, #8, #2
	blx	r3
	ldr	r3, [r5]
	str	r7, [r3, #120]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L255:
	mov	r3, r8
	ldr	r2, .L264+8
	ldr	r1, .L264+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L257
.L262:
	mov	r3, #0
	ldr	r2, .L264+8
	movt	r3, 63683
	ldr	r1, .L264+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L265:
	.align	2
.L264:
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+272
	.word	.LC35
	.word	.LC34
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_GlbResetX, .-VDMHAL_V4R3C1_GlbResetX
	.align	2
	.global	VDMHAL_V4R3C1_GlbReset
	.type	VDMHAL_V4R3C1_GlbReset, %function
VDMHAL_V4R3C1_GlbReset:
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
	beq	.L268
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMHAL_V4R3C1_GlbResetX
.L268:
	mov	r3, #0
	ldr	r2, .L269
	movt	r3, 63683
	ldr	r1, .L269+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L270:
	.align	2
.L269:
	.word	.LANCHOR0+296
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_GlbReset, .-VDMHAL_V4R3C1_GlbReset
	.align	2
	.global	VDMHAL_V4R3C1_ClearIntState
	.type	VDMHAL_V4R3C1_ClearIntState, %function
VDMHAL_V4R3C1_ClearIntState:
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
	ldr	r7, .L287
	mov	r5, r0, asl #3
	mov	r8, r0, asl #6
	rsb	r3, r5, r8
	ldr	r2, .L287+4
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1208]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L284
	movw	r6, #1228
	ldr	r9, .L287+8
	mul	r6, r6, r0
	ldr	r3, [r9, r6]
	cmp	r3, #0
	beq	.L285
.L275:
	cmp	r4, #1
	beq	.L286
.L282:
	mvn	r2, #0
	str	r2, [r3, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L284:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L287+12
	ldr	r2, .L287+16
	bl	dprint_vfmw
.L271:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L286:
	rsb	r5, r5, r8
	add	r7, r7, r5
	ldr	r2, [r7, #44]
	cmp	r2, #1
	beq	.L282
	cmp	r2, #2
	ldr	r1, [r3, #28]
	mvneq	r2, #11
	streq	r2, [r3, #32]
	beq	.L271
	cmp	r2, #3
	mvneq	r2, #14
	streq	r2, [r3, #32]
	b	.L271
.L285:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r9, r6]
	bne	.L275
.L276:
	ldr	r1, .L287+20
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L288:
	.align	2
.L287:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+320
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ClearIntState, .-VDMHAL_V4R3C1_ClearIntState
	.align	2
	.global	VDMHAL_V4R3C1_ClearMMUIntState
	.type	VDMHAL_V4R3C1_ClearMMUIntState, %function
VDMHAL_V4R3C1_ClearMMUIntState:
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
	bgt	.L294
	movw	r2, #1228
	ldr	r5, .L296
	mul	r4, r2, r3
	ldr	r2, [r5, r4]
	cmp	r2, #0
	beq	.L295
.L292:
	add	r2, r2, #61440
	mov	r3, #7
	str	r3, [r2, #44]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L294:
	mov	r0, #0
	ldr	r2, .L296+4
	str	r0, [sp]
	ldr	r1, .L296+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L295:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	strne	r2, [r5, r4]
	bne	.L292
.L293:
	ldr	r1, .L296+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L297:
	.align	2
.L296:
	.word	g_HwMem
	.word	.LANCHOR0+348
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ClearMMUIntState, .-VDMHAL_V4R3C1_ClearMMUIntState
	.align	2
	.global	VDMHAL_V4R3C1_MaskInt
	.type	VDMHAL_V4R3C1_MaskInt, %function
VDMHAL_V4R3C1_MaskInt:
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
	bgt	.L303
	movw	r2, #1228
	ldr	r5, .L305
	mul	r4, r2, r3
	ldr	r3, [r5, r4]
	cmp	r3, #0
	beq	.L304
.L301:
	mvn	r2, #0
	str	r2, [r3, #36]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L303:
	mov	r0, #0
	ldr	r2, .L305+4
	str	r0, [sp]
	ldr	r1, .L305+8
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L304:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r5, r4]
	bne	.L301
.L302:
	ldr	r1, .L305+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L306:
	.align	2
.L305:
	.word	g_HwMem
	.word	.LANCHOR0+380
	.word	.LC28
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_MaskInt, .-VDMHAL_V4R3C1_MaskInt
	.align	2
	.global	VDMHAL_V4R3C1_GetIntMaskCfg
	.type	VDMHAL_V4R3C1_GetIntMaskCfg, %function
VDMHAL_V4R3C1_GetIntMaskCfg:
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
	.size	VDMHAL_V4R3C1_GetIntMaskCfg, .-VDMHAL_V4R3C1_GetIntMaskCfg
	.align	2
	.global	VDMHAL_V4R3C1_EnableInt
	.type	VDMHAL_V4R3C1_EnableInt, %function
VDMHAL_V4R3C1_EnableInt:
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
	ldr	r2, .L321
	mov	r3, r0, asl #6
	ldr	r1, .L321+4
	sub	r3, r3, r0, asl #3
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1208]
	moveq	r4, r3
	cmp	r0, #0
	bgt	.L319
	movw	r5, #1228
	ldr	r6, .L321+8
	mul	r5, r5, r0
	ldr	r3, [r6, r5]
	cmp	r3, #0
	beq	.L320
.L314:
	cmp	r4, #1
	mvneq	r2, #5
	mvnne	r2, #1
	str	r2, [r3, #36]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L319:
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r1, .L321+12
	ldr	r2, .L321+16
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L320:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r6, r5]
	bne	.L314
.L315:
	ldr	r1, .L321+20
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L322:
	.align	2
.L321:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	.LC28
	.word	.LANCHOR0+404
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_EnableInt, .-VDMHAL_V4R3C1_EnableInt
	.align	2
	.global	VDMHAL_V4R3C1_CheckReg
	.type	VDMHAL_V4R3C1_CheckReg, %function
VDMHAL_V4R3C1_CheckReg:
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
	bgt	.L340
	movw	r4, #1228
	ldr	r6, .L342
	mul	r4, r4, r5
	ldr	r3, [r6, r4]
	cmp	r3, #0
	beq	.L341
.L326:
	sub	r2, r7, #1
	cmp	r2, #6
	ldrls	pc, [pc, r2, asl #2]
	b	.L332
.L334:
	.word	.L337
	.word	.L335
	.word	.L336
	.word	.L338
	.word	.L328
	.word	.L330
	.word	.L331
.L338:
	mov	r3, #40
.L333:
	movw	r1, #1228
	mul	r5, r1, r5
	ldr	r2, [r6, r5]
	ldr	r0, [r2, r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L337:
	mov	r3, #28
	b	.L333
.L336:
	mov	r3, #36
	b	.L333
.L335:
	mov	r3, #32
	b	.L333
.L331:
	movw	r3, #62272
	b	.L333
.L328:
	movw	r3, #61480
	b	.L333
.L330:
	movw	r3, #62304
	b	.L333
.L332:
	mov	r3, r7
	ldr	r2, .L342+4
	ldr	r1, .L342+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L341:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L327
	str	r8, [r6, r4]
	b	.L326
.L340:
	mov	r3, r5
	ldr	r2, .L342+4
	ldr	r1, .L342+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L327:
	ldr	r2, .L342+4
	ldr	r1, .L342+16
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L343:
	.align	2
.L342:
	.word	g_HwMem
	.word	.LANCHOR0+428
	.word	.LC39
	.word	.LC37
	.word	.LC38
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CheckReg, .-VDMHAL_V4R3C1_CheckReg
	.align	2
	.global	VDMHAL_V4R3C1_ReadMMUMask
	.type	VDMHAL_V4R3C1_ReadMMUMask, %function
VDMHAL_V4R3C1_ReadMMUMask:
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
	ble	.L347
	mov	r1, #1
	ldr	r2, .L348
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L348+4
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L347:
	movw	r0, #1228
	ldr	r2, .L348+8
	mul	r3, r0, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	ldr	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L349:
	.align	2
.L348:
	.word	.LANCHOR0+452
	.word	.LC40
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ReadMMUMask, .-VDMHAL_V4R3C1_ReadMMUMask
	.align	2
	.global	VDMHAL_V4R3C1_WriteMMUMask
	.type	VDMHAL_V4R3C1_WriteMMUMask, %function
VDMHAL_V4R3C1_WriteMMUMask:
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
	ble	.L353
	mov	r1, #1
	ldr	r2, .L354
	str	r1, [sp]
	mov	r0, #32
	ldr	r1, .L354+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L353:
	movw	r1, #1228
	ldr	r2, .L354+8
	mul	r3, r1, r3
	ldr	r3, [r2, r3]
	add	r3, r3, #61440
	str	r0, [r3, #32]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L355:
	.align	2
.L354:
	.word	.LANCHOR0+480
	.word	.LC32
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_WriteMMUMask, .-VDMHAL_V4R3C1_WriteMMUMask
	.align	2
	.global	VDMHAL_V4R3C1_PrepareDec
	.type	VDMHAL_V4R3C1_PrepareDec, %function
VDMHAL_V4R3C1_PrepareDec:
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
	subs	r7, r1, #0
	mov	r5, r0
	mov	r4, r2
	mov	r6, r3
	beq	.L375
	cmp	r2, #0
	bne	.L376
	sub	r1, r0, #6
	mov	r0, r2
	clz	r1, r1
	mov	r1, r1, lsr #5
	bl	SCD_ConfigReg
	mov	r3, r6
	mov	r2, r4
	mov	r1, #1
	mov	r0, #8
	bl	SCD_ConfigReg
	cmp	r5, #17
	ldrls	pc, [pc, r5, asl #2]
	b	.L358
.L361:
	.word	.L371
	.word	.L362
	.word	.L363
	.word	.L364
	.word	.L358
	.word	.L365
	.word	.L366
	.word	.L358
	.word	.L367
	.word	.L368
	.word	.L369
	.word	.L369
	.word	.L369
	.word	.L370
	.word	.L358
	.word	.L371
	.word	.L372
	.word	.L373
.L371:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264HAL_V4R3C1_StartDec
.L372:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCHAL_V4R3C1_StartDec
.L373:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP9HAL_V4R3C1_StartDec
.L362:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1HAL_V4R3C1_StartDec
.L363:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP4HAL_V4R3C1_StartDec
.L364:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP2HAL_V4R3C1_StartDec
.L365:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DIVX3HAL_V4R3C1_StartDec
.L366:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVSHAL_V4R3C1_StartDec
.L367:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV8HAL_V4R3C1_StartDec
.L368:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV9HAL_V4R3C1_StartDec
.L369:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP6HAL_V4R3C1_StartDec
.L370:
	mov	r2, r6
	mov	r0, r7
	mov	r1, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP8HAL_V4R3C1_StartDec
.L375:
	mov	r3, r7
	mov	r0, r7
	ldr	r2, .L377
	ldr	r1, .L377+4
	bl	dprint_vfmw
.L358:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L376:
	mov	r3, r2
	ldr	r1, .L377+8
	ldr	r2, .L377
	mov	r0, #0
	bl	dprint_vfmw
	b	.L358
.L378:
	.align	2
.L377:
	.word	.LANCHOR0+508
	.word	.LC41
	.word	.LC42
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_PrepareDec, .-VDMHAL_V4R3C1_PrepareDec
	.align	2
	.global	VDMHAL_V4R3C1_IsVdmReady
	.type	VDMHAL_V4R3C1_IsVdmReady, %function
VDMHAL_V4R3C1_IsVdmReady:
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
	ldr	r3, .L386
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L384
	cmp	r0, #0
	ble	.L385
	mov	r3, r0
	mov	r1, #1
	ldr	r2, .L386+4
	mov	r0, #32
	str	r1, [sp]
	ldr	r1, .L386+8
	bl	dprint_vfmw
	mov	r0, #0
.L381:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L385:
	ldr	r0, [r3, #28]
	ubfx	r0, r0, #17, #1
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L384:
	mov	r0, r3
	ldr	r2, .L386+4
	ldr	r3, .L386+12
	ldr	r1, .L386+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L381
.L387:
	.align	2
.L386:
	.word	g_HwMem
	.word	.LANCHOR0+536
	.word	.LC40
	.word	.LC43
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_IsVdmReady, .-VDMHAL_V4R3C1_IsVdmReady
	.align	2
	.global	VDMHAL_V4R3C1_IsVdmRun
	.type	VDMHAL_V4R3C1_IsVdmRun, %function
VDMHAL_V4R3C1_IsVdmRun:
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
	ldr	r3, .L395
	ldr	r4, [r3, r2]
	cmp	r4, #0
	beq	.L393
	cmp	r0, #0
	ble	.L394
	mov	r3, r0
	mov	r4, #1
	ldr	r2, .L395+4
	mov	r0, #32
	str	r4, [sp]
	ldr	r1, .L395+8
	bl	dprint_vfmw
	mov	r0, r4
.L390:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L394:
	ldr	r0, [r4, #40]
	subs	r0, r0, #1
	movne	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L393:
	ldr	r1, .L395+12
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	b	.L390
.L396:
	.align	2
.L395:
	.word	g_HwMem
	.word	.LANCHOR0+564
	.word	.LC40
	.word	.LC44
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_IsVdmRun, .-VDMHAL_V4R3C1_IsVdmRun
	.align	2
	.global	VDMHAL_V4R3C1_IsVdhDecOver
	.type	VDMHAL_V4R3C1_IsVdhDecOver, %function
VDMHAL_V4R3C1_IsVdhDecOver:
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
	ldr	r3, .L407
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L405
	bl	VDMHAL_V4R3C1_CheckReg
	cmp	r4, #2
	beq	.L402
	cmp	r4, #3
	beq	.L402
	cmp	r4, #1
	beq	.L406
	mov	r3, r4
	ldr	r2, .L407+4
	ldr	r1, .L407+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L402:
	and	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L406:
	ubfx	r0, r0, #17, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L405:
	mov	r0, r3
	ldr	r2, .L407+4
	ldr	r3, .L407+12
	ldr	r1, .L407+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L408:
	.align	2
.L407:
	.word	g_HwMem
	.word	.LANCHOR0+588
	.word	.LC39
	.word	.LC43
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_IsVdhDecOver, .-VDMHAL_V4R3C1_IsVdhDecOver
	.align	2
	.global	VDMHAL_V4R3C1_IsVdhPartDecOver
	.type	VDMHAL_V4R3C1_IsVdhPartDecOver, %function
VDMHAL_V4R3C1_IsVdhPartDecOver:
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
	ldr	r3, .L419
	mul	r2, r2, r1
	mov	r4, r0
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L417
	bl	VDMHAL_V4R3C1_CheckReg
	cmp	r4, #1
	beq	.L413
	cmp	r4, #2
	bne	.L418
	ubfx	r0, r0, #2, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L418:
	mov	r3, r4
	ldr	r2, .L419+4
	ldr	r1, .L419+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L413:
	ubfx	r0, r0, #19, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L417:
	mov	r0, r3
	ldr	r2, .L419+4
	ldr	r3, .L419+12
	ldr	r1, .L419+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L420:
	.align	2
.L419:
	.word	g_HwMem
	.word	.LANCHOR0+616
	.word	.LC39
	.word	.LC43
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_IsVdhPartDecOver, .-VDMHAL_V4R3C1_IsVdhPartDecOver
	.align	2
	.global	VDMHAL_V4R3C1_UpdateHardwareInfo
	.type	VDMHAL_V4R3C1_UpdateHardwareInfo, %function
VDMHAL_V4R3C1_UpdateHardwareInfo:
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
	subs	r4, r0, #0
	bgt	.L422
	ldr	r2, .L470
	ldr	r3, [r2]
	cmp	r3, #1
	addne	r1, r2, #124
	bne	.L426
	b	.L423
.L466:
	cmp	r2, r1
	beq	.L465
.L426:
	ldr	r3, [r2, #4]!
	cmp	r3, #1
	bne	.L466
.L423:
	movw	r3, #1228
	ldr	r7, .L470+4
	mul	r3, r3, r4
	ldr	r3, [r7, r3]
	cmp	r3, #0
	beq	.L467
	mov	r2, #180
	ldr	r0, [r3, #12]
	mul	r2, r2, r4
	ldr	r6, .L470+8
	mov	r5, #1
	add	r1, r6, r2
	str	r0, [r6, r2]
	ldr	r8, [r3, #28]
	str	r8, [r1, #4]
.L429:
	movw	r3, #1228
	ubfx	r8, r8, #0, #17
	mla	r3, r3, r4, r7
	ldr	r0, [r3, #40]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L468
	movw	r1, #1228
	sub	r3, r8, #1
	mul	r1, r1, r4
	cmp	r3, #199
	subls	r3, r8, #-1073741823
	mov	r2, #180
	mla	r2, r2, r4, r6
	movls	r3, r3, asl #4
	movhi	r3, #0
	addls	r0, r3, #8
	ldr	lr, [ip, r3]
	movhi	r0, #8
	ldr	r3, [r7, r1]
	str	lr, [r2, #16]
	ldr	lr, [r3, #208]
	ldr	r0, [ip, r0]
	ldr	r1, [r3, #212]
	str	lr, [r2, #8]
	str	r0, [r2, #20]
	str	r1, [r2, #12]
	b	.L433
.L465:
	movw	r3, #1228
	ldr	r7, .L470+4
	mul	r3, r3, r4
	ldr	r3, [r7, r3]
	cmp	r3, #0
	beq	.L469
	mov	r2, #180
	ldr	r0, [r3, #12]
	mul	r2, r2, r4
	ldr	r6, .L470+8
	mov	r5, #0
	add	r1, r6, r2
	str	r0, [r6, r2]
	ldr	r2, [r3, #28]
	str	r2, [r1, #4]
.L430:
	mov	r2, #180
	add	r1, r3, #4096
	mla	r2, r2, r4, r6
	ldr	lr, [r1]
	ldr	ip, [r1, #20]
	cmp	r5, #0
	ldr	r0, [r3, #208]
	ldr	r1, [r3, #212]
	str	lr, [r2, #16]
	str	ip, [r2, #20]
	str	r0, [r2, #8]
	str	r1, [r2, #12]
	bne	.L433
	ldr	r1, [r3, #176]
	ldr	lr, [r3, #180]
	ldr	ip, [r3, #184]
	str	r1, [r2, #24]
	ldr	r0, [r3, #188]
	ldr	r1, [r3, #192]
	str	lr, [r2, #28]
	str	ip, [r2, #32]
	str	r0, [r2, #36]
	str	r1, [r2, #40]
.L433:
	mov	lr, #180
	add	r1, r3, #33024
	mul	lr, lr, r4
	add	r2, lr, #48
	add	lr, lr, #176
	add	r2, r6, r2
	add	lr, r6, lr
.L434:
	ldr	ip, [r1], #4
	str	ip, [r2, #4]!
	cmp	r2, lr
	bne	.L434
	cmp	r5, #0
	movne	r0, #0
	bne	.L455
	mov	r2, #180
	add	r3, r3, #32768
	mla	r4, r2, r4, r6
	ldr	r2, [r3, #384]
	ldr	r3, [r3, #388]
	mov	r0, r5
	str	r2, [r4, #48]
	str	r3, [r4, #44]
.L455:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L422:
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L470+12
	ldr	r1, .L470+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L455
.L467:
	mov	r5, #1
.L437:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L428
	movw	r1, #1228
	mov	r2, #180
	mul	r1, r1, r4
	ldr	r6, .L470+8
	mul	r2, r2, r4
	cmp	r5, #1
	str	r3, [r7, r1]
	add	r1, r6, r2
	ldr	r0, [r3, #12]
	str	r0, [r6, r2]
	ldr	r8, [r3, #28]
	str	r8, [r1, #4]
	bne	.L430
	b	.L429
.L469:
	mov	r5, r3
	b	.L437
.L468:
	ldr	r3, .L470+20
	ldr	r2, .L470+12
	ldr	r1, .L470+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L455
.L428:
	ldr	r1, .L470+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L455
.L471:
	.align	2
.L470:
	.word	g_DSPState
	.word	g_HwMem
	.word	g_BackUp
	.word	.LANCHOR0+648
	.word	.LC28
	.word	.LC45
	.word	.LC1
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_UpdateHardwareInfo, .-VDMHAL_V4R3C1_UpdateHardwareInfo
	.align	2
	.global	VDMHAL_V4R3C1_ReadMsgSlot
	.type	VDMHAL_V4R3C1_ReadMsgSlot, %function
VDMHAL_V4R3C1_ReadMsgSlot:
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
	beq	.L476
	cmp	r2, #800
	bhi	.L477
	ldr	r3, .L478
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L477:
	mov	r0, r4
	ldr	r1, .L478+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L476:
	mov	r2, r0
	ldr	r1, .L478+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L479:
	.align	2
.L478:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LC46
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_ReadMsgSlot, .-VDMHAL_V4R3C1_ReadMsgSlot
	.align	2
	.global	VDMHAL_V4R3C1_WriteMsgSlot
	.type	VDMHAL_V4R3C1_WriteMsgSlot, %function
VDMHAL_V4R3C1_WriteMsgSlot:
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
	beq	.L481
	sub	r3, r2, #1
	cmp	r3, #255
	bhi	.L481
	ldr	r3, .L484
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L481:
	ldr	r1, .L484+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L485:
	.align	2
.L484:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC48
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_WriteMsgSlot, .-VDMHAL_V4R3C1_WriteMsgSlot
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	VDMHAL_V4R3C1_CfgRpMsg
	.type	VDMHAL_V4R3C1_CfgRpMsg, %function
VDMHAL_V4R3C1_CfgRpMsg:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r8, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L524
	ldr	r0, [r1, #48]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-68]
	beq	.L525
	ldr	r2, [r8, #44]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L526
	ldr	r1, [r8, #28]
	ldr	r0, [r8, #64]
	ldrb	ip, [r8]	@ zero_extendqisi2
	mov	r1, r1, asl r0
	ldr	r3, [r8, #32]
	add	r2, r1, #255
	cmp	ip, #1
	bic	r2, r2, #255
	mov	r3, r3, asl r0
	movne	r1, r4
	mov	ip, r2, asl #4
	beq	.L527
.L491:
	ldr	r0, [r8, #4]
	cmp	r0, #16
	beq	.L492
	add	r3, r3, #31
	mov	r0, #8
	bic	r3, r3, #31
	str	r0, [fp, #-80]
	mla	r3, r3, r2, r1
.L513:
	ldr	r2, [r8, #20]
	ldr	r4, [fp, #-68]
	mov	lr, #0	@ movhi
	mov	r0, lr	@ movhi
	str	r2, [r4]
	ldr	r2, [r8, #20]
	add	r2, r3, r2
	str	r2, [r4, #4]
	ldr	r2, [r8, #8]
	str	r2, [r4, #8]
	ldr	r2, [r8, #8]
	add	r3, r3, r2
	str	r3, [r4, #12]
	str	ip, [r4, #16]
	str	r1, [r4, #20]
	ldr	r2, [r8, #28]
	ldr	r3, [r8, #32]
	sub	r2, r2, #1
	sub	r3, r3, #1
	bfi	lr, r2, #0, #9
	bfi	r0, r3, #0, #9
	strh	lr, [fp, #-52]	@ movhi
	strh	r0, [fp, #-50]	@ movhi
	ldr	r3, [fp, #-52]
	str	r3, [r4, #24]
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
	strne	r3, [fp, #-60]
	beq	.L528
.L495:
	cmp	r1, #1
	beq	.L511
.L534:
	ldr	r3, [fp, #-60]
	sub	r3, r3, #1
	uxth	r3, r3
.L512:
	ldrb	r1, [r8]	@ zero_extendqisi2
	mov	r0, #0
	ldrb	r2, [fp, #-50]	@ zero_extendqisi2
	ldr	ip, [r8, #52]
	ldr	lr, [r8, #64]
	bfi	r2, r1, #0, #1
	ldrb	r1, [fp, #-49]	@ zero_extendqisi2
	and	ip, ip, #3
	sub	lr, lr, #4
	bfi	r2, ip, #4, #2
	bfi	r1, lr, #0, #2
	strh	r3, [fp, #-52]	@ movhi
	mov	r3, r2
	bfi	r3, ip, #6, #2
	mov	r2, r1
	ldr	r1, [fp, #-80]
	strb	r3, [fp, #-50]
	bfi	r2, r1, #2, #4
	strb	r2, [fp, #-49]
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-68]
	str	r3, [r2, #28]
.L522:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L528:
	ldr	r3, [r8, #64]
	cmp	r3, #6
	moveq	r4, #2
	beq	.L496
	cmp	r3, #5
	moveq	r4, #4
	beq	.L496
	cmp	r3, #4
	moveq	r4, #8
	bne	.L529
.L496:
	ldr	r9, [r8, #44]
	cmp	r9, #0
	movle	r3, #0
	ldrle	r1, [r8, #56]
	strle	r3, [fp, #-60]
	ble	.L495
	ldr	r2, [fp, #-84]
	mov	r6, #0
	ldr	r3, [fp, #-76]
	str	r6, [fp, #-72]
	str	r6, [fp, #-60]
	mul	r3, r3, r2
	str	r8, [fp, #-56]
	sub	r2, r4, #1
	str	r2, [fp, #-88]
	str	r3, [fp, #-92]
	sub	r3, r3, #1
	str	r3, [fp, #-96]
	b	.L499
.L532:
	ldrsh	r0, [r5, #74]
	mov	r1, r4
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r3, r4, r0
	cmp	r7, r3
	str	r3, [fp, #-72]
	ldrgt	r7, [fp, #-88]
	bgt	.L502
.L501:
	add	r6, r6, #1
	cmp	r6, r9
	bge	.L530
.L510:
	cmp	r6, #199
	bgt	.L531
.L499:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r5, r3, r6, lsl #2
	ldrsh	r10, [r5, #78]
	ldrh	r3, [r5, #76]
	sub	r0, r10, #1
	add	r0, r0, r4
	str	r3, [fp, #-64]
	bl	__aeabi_uidiv
	cmp	r6, #0
	mul	r7, r4, r0
	bgt	.L532
	ldr	r3, [fp, #-72]
	cmp	r7, r3
	movgt	r3, #0
	movle	r3, #1
	cmp	r6, #0
	moveq	r3, #0
	cmp	r3, #0
	bne	.L501
.L504:
	ldrsh	r0, [fp, #-64]
	mov	r1, r4
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-92]
	ldr	r3, [fp, #-96]
	cmp	r2, r7
	movls	r7, r3
	ldr	r3, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-60]
	mul	r5, r4, r0
	cmp	r5, r7
	movgt	r5, #0
	cmp	r3, #250
	bgt	.L533
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
	ldr	r3, [fp, #-60]
	ldr	r9, [fp, #-68]
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
	blt	.L510
.L530:
	ldr	r8, [fp, #-56]
	ldr	r1, [r8, #56]
	cmp	r1, #1
	bne	.L534
.L511:
	ldr	r3, [fp, #-76]
	mov	ip, #0	@ movhi
	str	r1, [r8, #44]
	sub	r2, r3, #1
	ldr	r3, [fp, #-84]
	ldr	r1, [fp, #-68]
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
	b	.L512
.L505:
	bl	__aeabi_uidiv
	mov	r1, r4
	mul	r10, r4, r0
	ldrsh	r0, [r5, #80]
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r10, r0
	add	r3, r0, #1
	bhi	.L506
	cmp	r10, r3
	mov	r1, r4
	beq	.L506
	ldrsh	r0, [r5, #74]
	add	r0, r0, r7
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r10, r0
	bhi	.L535
.L506:
	cmp	r8, #198
	mov	r6, r8
	add	r5, r5, #4
	bgt	.L536
	ldrsh	r10, [r5, #78]
.L502:
	add	r8, r6, #1
	mov	r1, r4
	cmp	r8, r9
	add	r0, r7, r10
	blt	.L505
	ldr	r3, [fp, #-88]
	add	r0, r3, r10
	bl	__aeabi_uidiv
	mul	r7, r4, r0
	b	.L504
.L536:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r2, r3, r8, lsl #2
	ldrsh	r0, [r2, #78]
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r7, r4, r0
	b	.L504
.L492:
	mla	r3, r2, r3, r1
	mov	r2, #10
	str	r2, [fp, #-80]
	b	.L513
.L527:
	add	r0, r1, #508
	adds	lr, r3, #63
	add	r0, r0, #3
	addmi	lr, r3, #126
	add	r1, r1, #1020
	cmp	r0, #0
	add	r1, r1, #2
	movge	r1, r0
	mov	r0, lr, asr #6
	mov	r1, r1, asr #9
	mov	r0, r0, asl #5
	mov	r1, r1, asl #4
	mul	r1, r1, r0
	b	.L491
.L535:
	mov	r7, r10
	b	.L504
.L531:
	ldr	r8, [fp, #-56]
	mov	r0, #0
	ldr	r1, .L537
	movw	r3, #2111
	str	r6, [sp]
	ldr	r2, .L537+4
	str	r0, [fp, #-60]
	bl	dprint_vfmw
	ldr	r1, [r8, #56]
	b	.L495
.L529:
	ldr	r1, .L537+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r4, #1
	b	.L496
.L524:
	mov	r3, r1
	mov	r2, r0
	ldr	r1, .L537+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L522
.L533:
	ldr	r8, [fp, #-56]
	mov	r1, #1
	str	r1, [r8, #56]
	b	.L511
.L526:
	mov	r0, r4
	ldr	r1, .L537+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L522
.L525:
	ldr	r3, .L537+20
	ldr	r2, .L537+24
	ldr	r1, .L537+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L522
.L538:
	.align	2
.L537:
	.word	.LC53
	.word	.LANCHOR0+708
	.word	.LC52
	.word	.LC49
	.word	.LC51
	.word	.LC50
	.word	.LANCHOR0+684
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CfgRpMsg, .-VDMHAL_V4R3C1_CfgRpMsg
	.align	2
	.global	VDMHAL_V4R3C1_CfgRpReg
	.type	VDMHAL_V4R3C1_CfgRpReg, %function
VDMHAL_V4R3C1_CfgRpReg:
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
	cmp	r1, #0
	cmpne	r2, #0
	mov	ip, #0
	mov	r5, r3
	moveq	r0, #1
	movne	r0, #0
	str	ip, [fp, #-32]
	beq	.L574
	cmp	r3, #0
	bgt	.L575
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L576
.L543:
	ldr	r4, .L578
	ldr	r3, [r1, #48]
	ldrb	r2, [r4]	@ zero_extendqisi2
	bic	r3, r3, #15
	str	r3, [fp, #-32]
	cmp	r2, #1
	bne	.L577
	movw	r1, #1228
	ldr	r2, .L578+4
	mul	r1, r1, r5
	ldr	r1, [r2, r1]
	str	r3, [r1, #16]
.L546:
	movw	r3, #1228
	movw	r1, #53763
	mul	r3, r3, r5
	movt	r1, 8192
	ldr	r3, [r2, r3]
	str	r1, [r3, #12]
.L548:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r5
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #60]
.L550:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r5
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #64]
.L552:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r5
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #68]
.L554:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r5
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #72]
.L556:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r5
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #76]
.L558:
	movw	r3, #1228
	movw	r1, #3075
	mul	r3, r3, r5
	movt	r1, 48
	ldr	r3, [r2, r3]
	str	r1, [r3, #80]
.L560:
	movw	r3, #1228
	movw	r1, #3075
	mul	r5, r3, r5
	mov	r0, #0
	movt	r1, 48
	ldr	r3, [r2, r5]
	str	r1, [r3, #84]
.L563:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L577:
	mov	r2, #16
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r2, [r4]	@ zero_extendqisi2
	movw	r3, #53763
	cmp	r2, #1
	movt	r3, 8192
	str	r3, [fp, #-32]
	ldreq	r2, .L578+4
	beq	.L546
	mov	r2, #12
	mov	r1, #2
	ldr	r0, [fp, #4]
	movw	r6, #3075
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	movt	r6, 48
	str	r6, [fp, #-32]
	cmp	r3, #1
	ldreq	r2, .L578+4
	beq	.L548
	mov	r3, r6
	mov	r2, #60
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L578+4
	beq	.L550
	mov	r3, r6
	mov	r2, #64
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L578+4
	beq	.L552
	mov	r3, r6
	mov	r2, #68
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L578+4
	beq	.L554
	mov	r3, r6
	mov	r2, #72
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L578+4
	beq	.L556
	mov	r3, r6
	mov	r2, #76
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L578+4
	beq	.L558
	mov	r3, r6
	mov	r2, #80
	mov	r1, #2
	ldr	r0, [fp, #4]
	bl	VDH_Record_RegData
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r2, .L578+4
	beq	.L560
	ldr	r0, [fp, #4]
	mov	r3, r6
	mov	r2, #84
	mov	r1, #2
	bl	VDH_Record_RegData
	mov	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L576:
	mov	r0, #0
	str	r1, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L544
	ldr	r1, [fp, #-40]
	str	r3, [r1]
	b	.L543
.L575:
	str	r0, [sp]
	ldr	r2, .L578+8
	ldr	r1, .L578+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L563
.L574:
	mov	r3, r1
	mov	r0, ip
	ldr	r1, .L578+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L563
.L544:
	ldr	r1, .L578+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L563
.L579:
	.align	2
.L578:
	.word	g_HalDisable
	.word	g_HwMem
	.word	.LANCHOR0+732
	.word	.LC28
	.word	.LC54
	.word	.LC36
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CfgRpReg, .-VDMHAL_V4R3C1_CfgRpReg
	.align	2
	.global	VDMHAL_V4R3C1_MakeDecReport
	.type	VDMHAL_V4R3C1_MakeDecReport, %function
VDMHAL_V4R3C1_MakeDecReport:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r3, r0, #0
	beq	.L609
	ldr	r5, [r3, #4]
	ldr	r8, [r3]
	cmp	r5, #0
	ldr	r6, [r3, #8]
	beq	.L610
	movw	r3, #1228
	ldr	r7, .L618
	mul	r3, r3, r6
	ldr	r0, [r7, r3]
	cmp	r0, #0
	beq	.L584
	ldr	r3, .L618+4
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #124
	bne	.L587
	b	.L599
.L612:
	cmp	r3, r1
	beq	.L611
.L587:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	bne	.L612
.L599:
	mov	r4, r2
.L585:
	ldr	r3, .L618+8
	mov	r2, #824
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r3, #48]
	blx	r3
	movw	r3, #1228
	mla	r3, r3, r6, r7
	ldr	r1, .L618+12
	mov	r2, #180
	mla	r2, r2, r6, r1
	ldr	r3, [r3, #24]
	str	r3, [r5, #4]
	ldr	r3, [r2, #4]
	mov	r3, r3, lsr #17
	and	r2, r3, #3
	cmp	r2, #1
	moveq	r3, #0
	beq	.L588
	eor	r3, r3, #1
	and	r3, r3, #1
	cmp	r8, #3
	orrne	r3, r3, #1
.L588:
	mov	r2, #180
	str	r3, [r5]
	mla	r3, r2, r6, r1
	cmp	r8, #0
	cmpne	r8, #15
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #0, #17
	str	r2, [r5, #12]
	beq	.L613
.L589:
	cmp	r2, #200
	bhi	.L614
.L591:
	movw	r3, #1228
	mla	r7, r3, r6, r7
	ldr	r7, [r7, #40]
	mov	r0, r7
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L615
	ldr	r8, .L618+16
	mov	r0, #3200
	ldr	r2, [r5, #12]
	mla	r4, r0, r6, r8
	mov	r2, r2, asl #2
	mov	r0, r4
	bl	VDMHAL_V4R3C1_ReadMsgSlot
	ldr	ip, [r5, #12]
	cmp	ip, #0
	movne	r0, r4
	movne	r3, r5
	movne	r2, #0
	beq	.L596
.L595:
	ldr	r1, [r0, #4]
	add	r2, r2, #1
	cmp	r2, ip
	add	r0, r0, #16
	add	r3, r3, #4
	strh	r1, [r3, #16]	@ movhi
	ldr	r1, [r0, #-8]
	strh	r1, [r3, #18]	@ movhi
	bne	.L595
.L596:
	mov	r0, #6
	bl	IsDprintTypeEnable
	cmp	r0, #0
	bne	.L616
.L582:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L613:
	cmp	r4, #1
	beq	.L617
	ldr	r1, .L618+20
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L589
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L589
	mov	r3, #1
	strh	r1, [r5, #20]	@ movhi
	mov	r0, r1
	strh	r1, [r5, #22]	@ movhi
	str	r3, [r5, #12]
	b	.L582
.L611:
	mov	r4, #0
	b	.L585
.L616:
	ldr	r2, [r5, #12]
	mov	r0, #6
	ldr	r1, .L618+24
	mov	r4, #0
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L618+28
	mov	r0, #6
	bl	dprint_vfmw
	mov	r3, #3200
	mla	r6, r3, r6, r8
.L597:
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
	ldr	r1, .L618+32
	bl	dprint_vfmw
	ldr	r3, [r5, #12]
	mov	r3, r3, asl #2
	sub	r3, r3, #3
	cmp	r3, r4
	bhi	.L597
	ldr	r1, .L618+36
	mov	r0, #6
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L614:
	mov	r3, #200
	ldr	r1, .L618+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5, #12]
	b	.L591
.L617:
	ldr	r3, [r3, #16]
	ubfx	r3, r3, #21, #2
	cmp	r3, #2
	bne	.L589
	mov	r3, #0
	str	r4, [r5, #12]
	strh	r3, [r5, #20]	@ movhi
	mov	r0, r3
	strh	r3, [r5, #22]	@ movhi
	b	.L582
.L615:
	ldr	r3, .L618+44
	ldr	r2, .L618+48
	ldr	r1, .L618+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L582
.L584:
	ldr	r3, .L618+56
	ldr	r2, .L618+48
	ldr	r1, .L618+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L582
.L610:
	mov	r0, r5
	ldr	r3, .L618+60
	ldr	r2, .L618+48
	ldr	r1, .L618+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L582
.L609:
	ldr	r3, .L618+64
	ldr	r2, .L618+48
	ldr	r1, .L618+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L582
.L619:
	.align	2
.L618:
	.word	g_HwMem
	.word	g_DSPState
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_BackUp
	.word	g_UpMsg
	.word	g_not_allow_H264FullPictureRepair_flag
	.word	.LC58
	.word	.LC59
	.word	.LC60
	.word	.LC61
	.word	.LC57
	.word	.LC45
	.word	.LANCHOR0+756
	.word	.LC1
	.word	.LC43
	.word	.LC56
	.word	.LC55
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_MakeDecReport, .-VDMHAL_V4R3C1_MakeDecReport
	.align	2
	.global	VDMHAL_V4R3C1_PrepareRepair
	.type	VDMHAL_V4R3C1_PrepareRepair, %function
VDMHAL_V4R3C1_PrepareRepair:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
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
	movw	r4, #1228
	mul	r4, r4, r3
	ldr	r5, .L637
	subs	r9, r1, #0
	mov	r6, r3
	mov	r7, r0
	add	r8, r4, r5
	beq	.L632
	cmp	r3, #0
	bgt	.L633
	ldr	r3, [r4, r5]
	cmp	r3, #0
	beq	.L634
.L624:
	cmp	r2, #0
	beq	.L635
	cmp	r2, #1
	movne	r0, #0
	beq	.L636
.L622:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L635:
	ldr	r4, .L637+4
	movw	r3, #1752
	mla	r3, r3, r6, r4
	ldr	r1, [r3, #44]
	cmp	r1, #0
	ble	.L627
	cmp	r7, #6
	bne	.L628
	ldrb	r1, [r9, #17]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r2, r1
	str	r2, [r3, #928]
.L628:
	ldr	r3, [fp, #4]
	mov	r2, r9
	mov	r1, r8
	mov	r0, r7
	str	r3, [sp]
	mov	r3, r6
	bl	VDMHAL_V4R3C1_CfgRpReg
	movw	r0, #1752
	mov	r1, r8
	mov	r2, r6
	mla	r0, r0, r6, r4
	bl	VDMHAL_V4R3C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L636:
	cmp	r7, #6
	bne	.L630
	ldrb	r3, [r9, #17]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L630
	movw	r4, #1752
	ldr	r5, .L637+4
	mul	r4, r4, r6
	add	r1, r5, r4
	ldr	r3, [r1, #920]
	cmp	r3, #0
	ble	.L630
	ldr	r3, [fp, #4]
	mov	ip, #2
	mov	r2, r9
	mov	r0, r7
	str	r3, [sp]
	mov	r3, r6
	str	ip, [r1, #928]
	mov	r1, r8
	bl	VDMHAL_V4R3C1_CfgRpReg
	add	r0, r4, #876
	add	r0, r5, r0
	mov	r2, r6
	mov	r1, r8
	bl	VDMHAL_V4R3C1_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L634:
	mov	r0, #0
	str	r2, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L625
	str	r3, [r4, r5]
	ldr	r2, [fp, #-40]
	b	.L624
.L633:
	mov	r0, #0
	ldr	r2, .L637+8
	str	r0, [sp]
	ldr	r1, .L637+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L622
.L630:
	ldr	r1, .L637+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L622
.L632:
	mov	r2, r9
	mov	r0, r9
	ldr	r1, .L637+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L622
.L627:
	mov	r0, r2
	ldr	r1, .L637+24
	str	r2, [fp, #-40]
	bl	dprint_vfmw
	ldr	r2, [fp, #-40]
	mov	r0, r2
	b	.L622
.L625:
	ldr	r1, .L637+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L622
.L638:
	.align	2
.L637:
	.word	g_HwMem
	.word	g_RepairParam
	.word	.LANCHOR0+784
	.word	.LC28
	.word	.LC65
	.word	.LC62
	.word	.LC64
	.word	.LC63
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_PrepareRepair, .-VDMHAL_V4R3C1_PrepareRepair
	.align	2
	.global	VDMHAL_V4R3C1_StartHwRepair
	.type	VDMHAL_V4R3C1_StartHwRepair, %function
VDMHAL_V4R3C1_StartHwRepair:
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
	ldr	r6, .L669
	mov	r5, r0
	mov	r4, r1
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L663
	cmp	r0, #0
	ble	.L664
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L669+4
	mov	r0, #32
	ldr	r1, .L669+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L665
.L647:
	mov	r2, #1
	mov	r3, r5
	str	r2, [sp]
	mov	r0, #32
	ldr	r2, .L669+4
	ldr	r1, .L669+8
	bl	dprint_vfmw
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L659
.L642:
	cmp	r4, #0
	beq	.L666
	mov	r3, r5, asl #6
	ldr	r2, .L669+12
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
.L664:
	movw	r3, #1228
	ldr	r4, .L669+16
	mul	r3, r3, r0
	mov	r2, #67108864
	ldr	r3, [r4, r3]
	str	r2, [r3, #8]
.L645:
	movw	r3, #1228
	ldr	r2, .L669+20
	mul	r3, r3, r5
	mvn	r1, #1
	ldr	r3, [r4, r3]
	str	r1, [r3, #36]
	ldr	r3, [r2, #112]
	blx	r3
.L654:
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
.L639:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L663:
	mov	r3, #67108864
	mov	r2, #8
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L667
	cmp	r5, #0
	ldrle	r4, .L669+16
	bgt	.L647
	b	.L645
.L667:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L642
	ldr	r3, .L669+20
	ldr	r3, [r3, #112]
	blx	r3
	cmp	r5, #0
	ble	.L668
.L651:
	mov	r4, #1
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L669+24
	ldr	r1, .L669+8
	bl	dprint_vfmw
	mov	r3, r5
	str	r4, [sp]
	mov	r0, #32
	ldr	r2, .L669+24
	ldr	r1, .L669+8
	bl	dprint_vfmw
	str	r4, [sp]
	mov	r3, r5
	ldr	r2, .L669+24
	ldr	r1, .L669+8
	mov	r0, #32
	bl	dprint_vfmw
	b	.L639
.L665:
	mvn	r3, #1
	mov	r2, #36
	mov	r1, #2
	mov	r0, r4
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L642
.L659:
	ldr	r3, .L669+20
	ldr	r3, [r3, #112]
	blx	r3
	b	.L651
.L666:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L669+24
	ldr	r1, .L669+28
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	dprint_vfmw
.L668:
	ldr	r4, .L669+16
	b	.L654
.L670:
	.align	2
.L669:
	.word	g_HalDisable
	.word	.LANCHOR0+812
	.word	.LC32
	.word	g_VdmDrvParam
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+828
	.word	.LC66
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_StartHwRepair, .-VDMHAL_V4R3C1_StartHwRepair
	.align	2
	.global	VDMHAL_V4R3C1_CalVdhClkSkip
	.type	VDMHAL_V4R3C1_CalVdhClkSkip, %function
VDMHAL_V4R3C1_CalVdhClkSkip:
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
	ldr	r9, .L701
	ldr	r10, [r9, #128]
	cmp	r10, #0
	blt	.L693
	mov	r7, #0
	add	r4, r9, #128
	mov	r6, r7
	mov	r5, r7
	add	r9, r9, #252
	mov	r8, #30
	b	.L673
.L700:
	mov	r3, r10
	ldr	r2, .L701+4
	ldr	r1, .L701+8
	mov	r0, #1
	bl	dprint_vfmw
.L675:
	cmp	r4, r9
	beq	.L699
.L692:
	ldr	r10, [r4, #4]!
	cmp	r10, #0
	blt	.L699
.L673:
	mov	r0, r10
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L700
	mov	r0, r10
	bl	FSP_GetInst
	cmp	r0, #0
	beq	.L676
	ldr	r1, [r0, #40]
	ldr	r2, [r0, #44]
	adds	r5, r1, #15
	addmi	r5, r1, #30
	adds	r6, r2, #15
	addmi	r6, r2, #30
	mov	r5, r5, asr #4
	mov	r6, r6, asr #4
.L676:
	ldr	r3, .L701+12
	mov	r0, r10
	ldr	r2, [r3, r10, asl #2]
	ldr	r3, [r2, #1536]
	cmp	r3, #30
	movgt	r8, r3
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L694
.L679:
	.word	.L688
	.word	.L688
	.word	.L688
	.word	.L688
	.word	.L694
	.word	.L688
	.word	.L688
	.word	.L694
	.word	.L688
	.word	.L688
	.word	.L688
	.word	.L688
	.word	.L688
	.word	.L688
	.word	.L694
	.word	.L689
	.word	.L688
	.word	.L688
.L688:
	mul	r7, r6, r5
	cmp	r4, r9
	mul	r7, r7, r8
	bne	.L692
.L699:
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
.L689:
	mul	r7, r6, r5
	mul	r7, r7, r8
	mov	r7, r7, asl #1
	b	.L675
.L694:
	mov	r7, #0
	b	.L675
.L693:
	mov	r0, #25
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L702:
	.align	2
.L701:
	.word	g_ChanCtx
	.word	.LANCHOR0+856
	.word	.LC67
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_CalVdhClkSkip, .-VDMHAL_V4R3C1_CalVdhClkSkip
	.align	2
	.global	VDMHAL_V4R3C1_GetVdmClk
	.type	VDMHAL_V4R3C1_GetVdmClk, %function
VDMHAL_V4R3C1_GetVdmClk:
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
	ldr	r2, .L711
	sub	r0, r3, r0, asl #3
	cmp	r1, #3
	ldrls	pc, [pc, r1, asl #2]
	b	.L704
.L706:
	.word	.L704
	.word	.L707
	.word	.L708
	.word	.L709
.L704:
	add	r3, r2, r0
	mov	r1, #500
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L708:
	add	r3, r2, r0
	mov	r1, #100
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L707:
	add	r3, r2, r0
	mov	r1, #540
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L709:
	add	r3, r2, r0
	mov	r1, #600
	mov	r0, r1
	str	r1, [r3, #16]
	ldmfd	sp, {fp, sp, pc}
.L712:
	.align	2
.L711:
	.word	g_VdmDrvParam
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_GetVdmClk, .-VDMHAL_V4R3C1_GetVdmClk
	.align	2
	.global	VDMHAL_V4R3C1_StartHwDecode
	.type	VDMHAL_V4R3C1_StartHwDecode, %function
VDMHAL_V4R3C1_StartHwDecode:
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
	ble	.L714
	mov	r0, #0
	mov	r3, r5
	str	r0, [sp]
	ldr	r2, .L751
	ldr	r1, .L751+4
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L714:
	ldr	r6, .L751+8
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L748
	ldr	r2, .L751+12
	mov	r0, #500
	ldr	r8, .L751+16
	ldr	r1, [r2]
	ldr	r3, [r1, #120]
	tst	r3, #768
	bfcne	r3, #8, #2
	strne	r3, [r1, #120]
	mov	r3, r5, asl #6
	ldr	r1, .L751+20
	sub	r3, r3, r5, asl #3
	add	r3, r8, r3
	ldr	r7, [r3, #8]
	str	r0, [r3, #16]
	ldr	r3, [r1, r7, asl #2]
	ldr	r9, [r3, #1208]
.L718:
	ldr	r2, [r2]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
.L720:
	mov	r2, r5
	mov	r3, r4
	mov	r1, #3
	mov	r0, #12
	bl	SCD_ConfigReg
	ldrb	r2, [r6]	@ zero_extendqisi2
	ldr	r10, .L751+8
	cmp	r2, #1
	bne	.L749
	movw	r2, #1228
	ldr	r3, .L751+24
	mul	r2, r2, r5
	ldr	r4, .L751+28
	ldr	r1, [r3]
	movw	r3, #43690
	bfi	r3, r3, #16, #16
	cmp	r1, #1
	ldr	r2, [r4, r2]
	moveq	r1, #7
	movne	r1, #0
	str	r3, [r2, #156]
.L722:
	movw	r2, #1228
	cmp	r9, #1
	mul	r2, r2, r5
	mvneq	r3, #5
	mvnne	r3, #1
	ldr	r2, [r4, r2]
	add	r2, r2, #61440
	str	r1, [r2, #32]
.L724:
	movw	r2, #1228
	mul	r2, r2, r5
	ldr	r2, [r4, r2]
	str	r3, [r2, #36]
.L726:
	ldr	r6, .L751+32
	mov	r0, #30
	ldr	r3, [r6, #116]
	blx	r3
	ldr	r3, [r6, #112]
	blx	r3
	movw	r3, #1228
	mul	r3, r3, r5
	mov	r1, #56
	mov	r2, #0
	mov	lr, #1
	mla	r5, r1, r5, r8
	ldr	ip, .L751+36
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
.L749:
	movw	r3, #43690
	mov	r1, #2
	mov	r2, #156
	movt	r3, 43690
	mov	r0, r4
	bl	VDH_Record_RegData
	ldr	r3, .L751+24
	ldrb	r2, [r10]	@ zero_extendqisi2
	ldr	r3, [r3]
	cmp	r3, #1
	moveq	r1, #7
	movne	r1, #0
	cmp	r2, #1
	ldreq	r4, .L751+28
	beq	.L722
	mov	r3, r1
	movw	r2, #61472
	mov	r0, r4
	mov	r1, #2
	bl	VDH_Record_RegData
	cmp	r9, #1
	ldrb	r2, [r6]	@ zero_extendqisi2
	mvneq	r3, #5
	mvnne	r3, #1
	cmp	r2, #1
	ldreq	r4, .L751+28
	beq	.L724
	mov	r0, r4
	mov	r2, #36
	mov	r1, #2
	bl	VDH_Record_RegData
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r4, .L751+28
	beq	.L726
	cmp	r4, #0
	beq	.L750
	mov	r3, #1
	str	r7, [r4, #8]
	strb	r5, [r4]
	mov	r0, r4
	str	r3, [r4, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDH_PostTask
.L748:
	mov	r3, #0
	mov	r0, r1
	mov	r2, r3
	mov	r1, r3
	bl	VDH_Record_RegData
	ldr	r8, .L751+16
	mov	r3, r5, asl #6
	ldr	r2, .L751+20
	sub	r3, r3, r5, asl #3
	ldrb	r0, [r6]	@ zero_extendqisi2
	add	r3, r8, r3
	mov	r1, #500
	cmp	r0, #1
	ldr	r7, [r3, #8]
	str	r1, [r3, #16]
	ldr	r3, [r2, r7, asl #2]
	ldreq	r2, .L751+12
	ldr	r9, [r3, #1208]
	beq	.L718
	mov	r3, #0
	mov	r2, #1
	mov	r1, r3
	mov	r0, r4
	bl	VDH_Record_RegData
	b	.L720
.L750:
	mov	r3, r4
	mov	r0, r4
	ldr	r2, .L751
	ldr	r1, .L751+40
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L752:
	.align	2
.L751:
	.word	.LANCHOR0+884
	.word	.LC28
	.word	g_HalDisable
	.word	g_pstRegCrg
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	mask_mmu_err_int
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_LowDelaySeqIndex
	.word	.LC66
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_StartHwDecode, .-VDMHAL_V4R3C1_StartHwDecode
	.align	2
	.global	VDMHAL_V4R3C1_GetCharacter
	.type	VDMHAL_V4R3C1_GetCharacter, %function
VDMHAL_V4R3C1_GetCharacter:
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
	ldr	r1, .L754
	mov	r0, #15
	ldr	r3, .L754+4
	mov	r2, #4
	str	r0, [r1]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L755:
	.align	2
.L754:
	.word	g_VdmCharacter
	.word	g_eVdmVersion
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_GetCharacter, .-VDMHAL_V4R3C1_GetCharacter
	.align	2
	.global	VDMHAL_V4R3C1_WriteBigTitle1DYuv
	.type	VDMHAL_V4R3C1_WriteBigTitle1DYuv, %function
VDMHAL_V4R3C1_WriteBigTitle1DYuv:
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
	beq	.L757
	cmp	ip, #2
	moveq	r4, #1
	movne	r4, #2
.L757:
	ldr	r3, [fp, #-108]
	cmp	r3, #0
	beq	.L756
	mov	r3, #0
	mov	r2, #4194304
	mov	r1, r3
	str	r3, [sp]
	ldr	r0, .L846
	sub	r3, fp, #92
	bl	MEM_AllocMemBlock
	subs	r1, r0, #0
	bne	.L760
	str	r1, [sp]
	mov	r2, #4194304
	sub	r3, fp, #68
	ldr	r0, .L846+4
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L760
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
	bne	.L761
	ldr	r3, [fp, #-100]
	mov	r1, r5, lsr #1
	ldr	r2, [fp, #-64]
	cmp	r3, #0
	ldr	r6, .L846+8
	mov	r3, r3, lsr #1
	ldr	r7, [fp, #-88]
	str	r2, [fp, #-120]
	movne	r10, r0
	add	r2, r2, #2097152
	str	r1, [fp, #-124]
	str	r2, [fp, #-128]
	str	r3, [fp, #-112]
	strne	r10, [fp, #-96]
	beq	.L763
.L762:
	cmp	r5, #0
	beq	.L765
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	ldr	r2, [fp, #-104]
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L764:
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
	bhi	.L764
.L765:
	ldr	r3, [fp, #-96]
	add	r10, r10, r5
	ldr	r2, [fp, #-100]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r2, r3
	bne	.L762
.L763:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	ldr	r3, [r6, #44]
	blx	r3
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L766
	ldr	r3, [fp, #-104]
	mov	r9, #0
	ldr	r10, [fp, #-116]
	str	r9, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L767:
	cmp	r5, #0
	beq	.L770
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L768:
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
	bhi	.L768
.L770:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L767
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L844
.L772:
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L773
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
.L773:
	ldr	r3, [fp, #-124]
.L843:
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
.L756:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L760:
	ldr	r1, .L846+12
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L761:
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
	ldr	r6, .L846+8
	ldr	r7, [fp, #-88]
	strhi	r3, [fp, #-96]
	bls	.L780
.L782:
	cmp	r5, #0
	beq	.L783
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	mov	r10, r2, lsr #1
	ldr	r2, [fp, #-104]
	mul	r10, r5, r10
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L781:
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
	bhi	.L781
.L783:
	ldr	r3, [fp, #-96]
	ldr	r2, [fp, #-100]
	add	r3, r3, #2
	str	r3, [fp, #-96]
	cmp	r2, r3
	bhi	.L782
.L780:
	ldr	r3, [fp, #-100]
	mov	r0, r7
	ldr	r2, [fp, #-108]
	mul	r1, r5, r3
	ldr	r3, [r6, #44]
	mov	r1, r1, lsr #1
	blx	r3
	ldr	r3, [fp, #-112]
	cmp	r3, #0
	beq	.L784
	ldr	r3, [fp, #-104]
	mov	r9, #0
	ldr	r10, [fp, #-116]
	str	r9, [fp, #-96]
	mov	r3, r3, asr #1
	str	r3, [fp, #-100]
.L785:
	cmp	r5, #0
	beq	.L788
	ldr	r2, [fp, #-96]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-100]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L786:
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
	bhi	.L786
.L788:
	ldr	r3, [fp, #-96]
	add	r9, r9, r5
	ldr	r2, [fp, #-112]
	add	r3, r3, #1
	str	r3, [fp, #-96]
	cmp	r3, r2
	bne	.L785
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L845
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L791
	ldr	r2, [fp, #-112]
	ldr	r3, [fp, #-124]
	cmp	r2, r3
	bls	.L796
.L797:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L797
.L796:
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
.L791:
	ldr	r3, [fp, #-132]
	b	.L843
.L844:
	ldr	r3, [fp, #-120]
	add	r7, r7, #1
	ldr	r4, [fp, #-124]
	mov	lr, #0
	ldr	r8, [fp, #-112]
.L774:
	cmp	r4, #0
	moveq	ip, r3
	beq	.L777
	sub	r1, r3, #-67108863
	add	ip, r3, r4
	sub	r1, r1, #65011712
	mov	r2, r7
.L775:
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	strb	r0, [r1, #1]!
	ldrb	r0, [r2], #2	@ zero_extendqisi2
	strb	r0, [r3], #1
	cmp	r3, ip
	bne	.L775
.L777:
	add	lr, lr, #1
	mov	r3, ip
	cmp	lr, r8
	add	r7, r7, r5
	bne	.L774
	b	.L773
.L845:
	ldr	r3, [fp, #-124]
	mov	r4, #0
	ldr	lr, [fp, #-120]
	ldr	ip, [fp, #-132]
	mla	r3, r5, r3, r7
	ldr	r7, [fp, #-112]
	mov	r5, r5, asl #1
	add	r3, r3, #1
.L792:
	cmp	ip, #0
	beq	.L795
	mov	r2, r4, lsr #1
	mov	r1, r3
	mul	r2, ip, r2
	sub	r0, r2, #-67108863
	add	r9, r2, ip
	sub	r0, r0, #65011712
	add	r9, lr, r9
	add	r0, lr, r0
	add	r2, lr, r2
.L793:
	ldrb	r8, [r1, #-1]	@ zero_extendqisi2
	strb	r8, [r0, #1]!
	ldrb	r8, [r1], #2	@ zero_extendqisi2
	strb	r8, [r2], #1
	cmp	r2, r9
	bne	.L793
.L795:
	add	r4, r4, #2
	add	r3, r3, r5
	cmp	r7, r4
	bhi	.L792
	b	.L791
.L766:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	bne	.L772
	b	.L773
.L784:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L791
	cmp	r3, #0
	beq	.L796
	b	.L791
.L847:
	.align	2
.L846:
	.word	.LC68
	.word	.LC70
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC69
	UNWIND(.fnend)
	.size	VDMHAL_V4R3C1_WriteBigTitle1DYuv, .-VDMHAL_V4R3C1_WriteBigTitle1DYuv
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
	ldr	ip, .L855
	mov	lr, r2
	ldrb	r2, [ip]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L854
	cmp	r0, #0
	bne	.L850
	ldr	r3, .L855+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	ubfx	r0, r2, #8, #2
	cmp	r1, r0
	bfine	r2, r1, #8, #2
	strne	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L850:
	cmp	r0, #1
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, .L855+4
	ldr	r3, [r3]
	ldr	r2, [r3, #120]
	bfi	r2, r1, #12, #5
	bfc	r2, #17, #1
	str	r2, [r3, #120]
	ldr	r2, [r3, #120]
	orr	r2, r2, #131072
	str	r2, [r3, #120]
	ldmfd	sp, {fp, sp, pc}
.L854:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #0
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L856:
	.align	2
.L855:
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
	ldr	ip, .L863
	mov	lr, r3
	ldrb	r3, [ip]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L861
	cmp	r2, #0
	ble	.L862
	str	r3, [sp]
	mov	r0, #32
	mov	r3, r2
	ldr	r1, .L863+4
	ldr	r2, .L863+8
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L862:
	movw	r3, #1228
	ldr	ip, .L863+12
	mul	r2, r3, r2
	ldr	r3, [ip, r2]
	str	r1, [r3, r0]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L861:
	mov	r3, r1
	mov	r2, r0
	mov	r1, #2
	mov	r0, lr
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Record_RegData
.L864:
	.align	2
.L863:
	.word	g_HalDisable
	.word	.LC32
	.word	.LANCHOR0+812
	.word	g_HwMem
	UNWIND(.fnend)
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.56369, %object
	.size	__func__.56369, 22
__func__.56369:
	.ascii	"VDMHAL_V4R3C1_OpenHAL\000"
	.space	2
	.type	__func__.56443, %object
	.size	__func__.56443, 25
__func__.56443:
	.ascii	"VDMHAL_V4R3C1_CalcFsSize\000"
	.space	3
	.type	__func__.56469, %object
	.size	__func__.56469, 24
__func__.56469:
	.ascii	"VDMHAL_V4R3C1_CalcFsNum\000"
	.type	__func__.56511, %object
	.size	__func__.56511, 32
__func__.56511:
	.ascii	"VDMHAL_V4R3C1_ArrangeMem_Normal\000"
	.type	__FUNCTION__.56512, %object
	.size	__FUNCTION__.56512, 32
__FUNCTION__.56512:
	.ascii	"VDMHAL_V4R3C1_ArrangeMem_Normal\000"
	.type	__func__.56455, %object
	.size	__func__.56455, 33
__func__.56455:
	.ascii	"VDMHAL_V4R3C1_FillMemArrangeInfo\000"
	.space	3
	.type	__func__.56592, %object
	.size	__func__.56592, 34
__func__.56592:
	.ascii	"VDMHAL_V4R3C1_ArrangeMem_Specific\000"
	.space	2
	.type	__func__.56616, %object
	.size	__func__.56616, 23
__func__.56616:
	.ascii	"VDMHAL_V4R3C1_ResetVdm\000"
	.space	1
	.type	__func__.56626, %object
	.size	__func__.56626, 35
__func__.56626:
	.ascii	"VDMHAL_V4R3C1_SetSmmuPageTableAddr\000"
	.space	1
	.type	__func__.56647, %object
	.size	__func__.56647, 24
__func__.56647:
	.ascii	"VDMHAL_V4R3C1_GlbResetX\000"
	.type	__func__.56636, %object
	.size	__func__.56636, 23
__func__.56636:
	.ascii	"VDMHAL_V4R3C1_GlbReset\000"
	.space	1
	.type	__func__.56659, %object
	.size	__func__.56659, 28
__func__.56659:
	.ascii	"VDMHAL_V4R3C1_ClearIntState\000"
	.type	__func__.56665, %object
	.size	__func__.56665, 31
__func__.56665:
	.ascii	"VDMHAL_V4R3C1_ClearMMUIntState\000"
	.space	1
	.type	__func__.56671, %object
	.size	__func__.56671, 22
__func__.56671:
	.ascii	"VDMHAL_V4R3C1_MaskInt\000"
	.space	2
	.type	__func__.56684, %object
	.size	__func__.56684, 24
__func__.56684:
	.ascii	"VDMHAL_V4R3C1_EnableInt\000"
	.type	__func__.56693, %object
	.size	__func__.56693, 23
__func__.56693:
	.ascii	"VDMHAL_V4R3C1_CheckReg\000"
	.space	1
	.type	__func__.56707, %object
	.size	__func__.56707, 26
__func__.56707:
	.ascii	"VDMHAL_V4R3C1_ReadMMUMask\000"
	.space	2
	.type	__func__.56712, %object
	.size	__func__.56712, 27
__func__.56712:
	.ascii	"VDMHAL_V4R3C1_WriteMMUMask\000"
	.space	1
	.type	__func__.56743, %object
	.size	__func__.56743, 25
__func__.56743:
	.ascii	"VDMHAL_V4R3C1_PrepareDec\000"
	.space	3
	.type	__func__.56748, %object
	.size	__func__.56748, 25
__func__.56748:
	.ascii	"VDMHAL_V4R3C1_IsVdmReady\000"
	.space	3
	.type	__func__.56753, %object
	.size	__func__.56753, 23
__func__.56753:
	.ascii	"VDMHAL_V4R3C1_IsVdmRun\000"
	.space	1
	.type	__func__.56759, %object
	.size	__func__.56759, 27
__func__.56759:
	.ascii	"VDMHAL_V4R3C1_IsVdhDecOver\000"
	.space	1
	.type	__func__.56769, %object
	.size	__func__.56769, 31
__func__.56769:
	.ascii	"VDMHAL_V4R3C1_IsVdhPartDecOver\000"
	.space	1
	.type	__func__.56784, %object
	.size	__func__.56784, 33
__func__.56784:
	.ascii	"VDMHAL_V4R3C1_UpdateHardwareInfo\000"
	.space	3
	.type	__func__.56857, %object
	.size	__func__.56857, 23
__func__.56857:
	.ascii	"VDMHAL_V4R3C1_CfgRpMsg\000"
	.space	1
	.type	__func__.56834, %object
	.size	__func__.56834, 24
__func__.56834:
	.ascii	"VDMHAL_CfgNotFullRepair\000"
	.type	__func__.56868, %object
	.size	__func__.56868, 23
__func__.56868:
	.ascii	"VDMHAL_V4R3C1_CfgRpReg\000"
	.space	1
	.type	__func__.56881, %object
	.size	__func__.56881, 28
__func__.56881:
	.ascii	"VDMHAL_V4R3C1_MakeDecReport\000"
	.type	__func__.56920, %object
	.size	__func__.56920, 28
__func__.56920:
	.ascii	"VDMHAL_V4R3C1_PrepareRepair\000"
	.type	__func__.57107, %object
	.size	__func__.57107, 15
__func__.57107:
	.ascii	"MFDE_ConfigReg\000"
	.space	1
	.type	__func__.56927, %object
	.size	__func__.56927, 28
__func__.56927:
	.ascii	"VDMHAL_V4R3C1_StartHwRepair\000"
	.type	__func__.56966, %object
	.size	__func__.56966, 28
__func__.56966:
	.ascii	"VDMHAL_V4R3C1_CalVdhClkSkip\000"
	.type	__func__.56989, %object
	.size	__func__.56989, 28
__func__.56989:
	.ascii	"VDMHAL_V4R3C1_StartHwDecode\000"
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
	ASCII(.ascii	"VDMHAL_V4R3C1_OpenHAL: Size error!\000" )
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
	ASCII(.ascii	"VDMHAL ArrangeMem HEVC 10 bit\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"%s pstVfmwFrameSizeInfo = NULL\012\000" )
.LC11:
	ASCII(.ascii	"DelAllFrameMemRecord err in VDMHAL_V4R3C1_ArrangeMe" )
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
	ASCII(.ascii	"VDMHAL_V4R3C1_CalcFsSize err!\012\000" )
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
	ASCII(.ascii	"VDMHAL_V4R3C1_ArrangeMem Mem addr is NULL\000" )
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
	ASCII(.ascii	"VDMHAL_V4R3C1_ResetVdm: map vdm register fail, vir(" )
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
	ASCII(.ascii	"%s: map vdm register 0x%x failed!\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"%s VdhId %d failed!\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"%s VdhId %d success!\012\000" )
	.space	2
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
	ASCII(.ascii	"%s: VdhId(%d)overgrown its limits\012\000" )
	.space	1
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
	ASCII(.ascii	"VDMHAL_V4R3C1_CfgRpMsg error! pRepairParam=%p, pHwM" )
	ASCII(.ascii	"em=%p\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"can not map repair msg virtual address!\000" )
.LC51:
	ASCII(.ascii	"ValidGroupNum=%d out of range!\012\000" )
.LC52:
	ASCII(.ascii	"align_mb error\012\000" )
.LC53:
	ASCII(.ascii	"[%s][%d]sclie_num is wrong! %d \012\000" )
	.space	3
.LC54:
	ASCII(.ascii	"VDMHAL_V4R3C1_CfgRpReg error! pDecParam=%p, pHwMem=" )
	ASCII(.ascii	"%p\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"'pMakeDecReport' is NULL\000" )
	.space	3
.LC56:
	ASCII(.ascii	"'pDecReport' is NULL\000" )
	.space	3
.LC57:
	ASCII(.ascii	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full" )
	ASCII(.ascii	" repair.\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"\012***** UpMsg DecSliceNum=%d\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"\012***** Up Msg (phy addr: %#8x) *****\012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"\012***** Up Msg print finished *****\012\000" )
.LC62:
	ASCII(.ascii	"VDMHAL_V4R3C1_PrepareRepair error! pDecParam=%p\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC63:
	ASCII(.ascii	"vdm register virtual address not mapped, VDMHAL_V20" )
	ASCII(.ascii	"0R003_PrepareRepair failed!\012\000" )
.LC64:
	ASCII(.ascii	"FIRST_REPAIR Parameter Error!\012\000" )
	.space	1
.LC65:
	ASCII(.ascii	"SECOND_REPAIR Parameter Error!\012\000" )
.LC66:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC67:
	ASCII(.ascii	"%s The channel %d is not active\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"BigTile1d_y\000" )
.LC69:
	ASCII(.ascii	"failed mem_allocMemBlock BigTile_yuv save!\012\000" )
.LC70:
	ASCII(.ascii	"BigTile1d_uv\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
