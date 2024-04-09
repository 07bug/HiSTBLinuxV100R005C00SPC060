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
	.file	"avs2.c"
	.text
	.align	2
	.type	AVS2_ue_v.isra.2, %function
AVS2_ue_v.isra.2:
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
	mov	r1, #32
	mov	r5, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	bls	.L5
	movw	r3, #61166
	mov	r2, r0
	movt	r3, 65535
	ldr	r1, .L6
	mov	r0, #1
	bl	dprint_vfmw
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5:
	add	r4, r0, #1
	mov	r1, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, r4
	mov	r0, r5
	bl	BsShow
	mov	r1, r4
	sub	r4, r0, #1
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L7:
	.align	2
.L6:
	.word	.LC0
	UNWIND(.fnend)
	.size	AVS2_ue_v.isra.2, .-AVS2_ue_v.isra.2
	.align	2
	.type	AVS2_se_v.isra.3, %function
AVS2_se_v.isra.3:
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
	mov	r1, #32
	mov	r5, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	bls	.L13
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L13:
	add	r6, r0, #1
	mov	r1, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, r6
	mov	r0, r5
	bl	BsShow
	mov	r1, r6
	sub	r0, r0, #1
	tst	r0, #1
	mov	r0, r0, asr #1
	addne	r4, r0, #1
	rsbeq	r4, r0, #0
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_se_v.isra.3, .-AVS2_se_v.isra.3
	.align	2
	.type	AVS2_UpdateSceneBuf.part.7, %function
AVS2_UpdateSceneBuf.part.7:
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
	add	r4, r0, #18944
	add	r5, r0, #20736
	mov	r6, r0
	add	r4, r4, #144
	add	r5, r5, #16
	add	r7, r0, #8192
	b	.L18
.L16:
	add	r4, r4, #104
	cmp	r4, r5
	beq	.L23
.L18:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	sub	r3, r3, #5
	cmp	r3, #1
	bhi	.L16
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	tst	r3, #2
	and	r2, r3, #1
	beq	.L16
	ldr	r3, [r7, #2928]
	cmp	r3, r4
	beq	.L16
	cmp	r2, #0
	strb	r2, [r4, #6]
	bne	.L16
	strb	r2, [r4, #5]
	add	r4, r4, #104
	ldr	r1, [r4, #-48]
	ldr	r0, [r6, #4]
	bl	FSP_SetRef
	cmp	r4, r5
	bne	.L18
.L23:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_UpdateSceneBuf.part.7, .-AVS2_UpdateSceneBuf.part.7
	.align	2
	.global	AVS2_Vfmw_EpbRemove
	.type	AVS2_Vfmw_EpbRemove, %function
AVS2_Vfmw_EpbRemove:
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
	add	r5, r0, #44
	mov	r4, r0
	ldr	r7, [r0, #60]
	mov	r1, #8
	mov	r0, r5
	add	r6, r4, #76
	bl	BsGet
	mov	r1, #8
	sub	r7, r7, #3
	strb	r0, [r4, #76]
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #77]
	mov	r0, r5
	bl	BsGet
	mov	r1, #24
	strb	r0, [r4, #78]
	mov	r0, r5
	bl	BsShow
	cmp	r7, #0
	mov	r3, r0
	mov	r9, r0, lsr #8
	beq	.L34
	mov	r8, #3
	mov	r4, #16
.L30:
	bic	r1, r3, #-16777216
	uxtb	r2, r3
	cmp	r1, #2
	mov	r0, r5
	ubfxeq	r2, r3, #2, #6
	addeq	r4, r4, #6
	addne	r4, r4, #8
	orreq	r9, r2, r9, asl #6
	orrne	r9, r2, r9, asl #8
	cmp	r4, #23
	mov	r1, #8
	sub	r7, r7, #1
	mov	r10, r3, asl r1
	ble	.L28
	cmp	r8, #512
	sub	r4, r4, #8
	mov	r3, r9, lsr r4
	bcs	.L29
	strb	r3, [r6, r8]
	add	r8, r8, #1
.L28:
	bl	BsGet
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	cmp	r7, #0
	uxtb	r0, r0
	orr	r3, r0, r10
	bne	.L30
	cmp	r4, #16
	ble	.L32
	cmp	r8, #512
	bcs	.L29
	mov	r9, r9, lsr #16
	rsb	r4, r4, #24
	mov	r4, r9, asl r4
	uxtb	r4, r4
	strb	r4, [r6, r8]
	cmp	r4, #0
	addne	r2, r8, #1
	bne	.L25
.L32:
	mov	r2, r8
.L25:
	mov	r0, r5
	mov	r1, r6
	bl	BsInit
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L29:
	mov	r0, r5
	mov	r1, #32
	bl	BsShow
	ldr	r1, .L36
	uxtb	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L34:
	mov	r2, #3
	b	.L25
.L37:
	.align	2
.L36:
	.word	.LC1
	UNWIND(.fnend)
	.size	AVS2_Vfmw_EpbRemove, .-AVS2_Vfmw_EpbRemove
	.align	2
	.global	AVS2_SkipToNextStartCode
	.type	AVS2_SkipToNextStartCode, %function
AVS2_SkipToNextStartCode:
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
	mov	r5, r0
	bl	BsToNextByte
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #3
	subgt	r6, r6, #3
	movgt	r4, #0
	bgt	.L41
	b	.L42
.L47:
	bl	BsSkip
	cmp	r4, r6
	beq	.L42
.L41:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L47
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L42:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_SkipToNextStartCode, .-AVS2_SkipToNextStartCode
	.align	2
	.global	AVS2_DumpDpbStatus
	.type	AVS2_DumpDpbStatus, %function
AVS2_DumpDpbStatus:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	mov	r4, r0
	mov	r7, r1
	mov	r0, #32
	ldr	r1, .L57
	sub	r7, r7, #1
	bl	dprint_vfmw
	ldr	r1, .L57+4
	mov	r0, #32
	clz	r7, r7
	bl	dprint_vfmw
	add	r4, r4, #18944
	ldr	r8, .L57+8
	mov	r6, #0
	add	r4, r4, #150
	mov	r7, r7, lsr #5
	mov	r5, r6
.L51:
	ldrb	ip, [r4]	@ zero_extendqisi2
	cmp	ip, #0
	moveq	r3, r7
	orrne	r3, r7, #1
	cmp	r3, #0
	beq	.L49
	ldr	lr, [r4, #74]
	mov	r0, #32
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	add	r6, r6, #1
	ldr	r3, .L57+12
	str	lr, [sp, #28]
	cmp	r2, #6
	ldr	lr, [r4, #54]
	ldrls	r3, [r8, r2, asl #2]
	mov	r2, r5
	ldr	r1, .L57+16
	str	lr, [sp, #24]
	ldr	lr, [r4, #50]
	str	lr, [sp, #20]
	ldrsh	lr, [r4, #-4]
	str	lr, [sp, #16]
	ldrsh	lr, [r4, #-6]
	str	lr, [sp, #12]
	ldrb	lr, [r4, #-2]	@ zero_extendqisi2
	str	lr, [sp, #8]
	ldrb	lr, [r4, #-1]	@ zero_extendqisi2
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
.L49:
	add	r5, r5, #1
	add	r4, r4, #104
	cmp	r5, #16
	bne	.L51
	mov	r2, r6
	ldr	r1, .L57+20
	mov	r0, #32
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L58:
	.align	2
.L57:
	.word	.LC3
	.word	.LC4
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	AVS2_DumpDpbStatus, .-AVS2_DumpDpbStatus
	.align	2
	.global	AVS2_ClearPacket
	.type	AVS2_ClearPacket, %function
AVS2_ClearPacket:
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
	add	r4, r0, #16384
	mov	r5, r0
	ldr	r0, [r0, #4]
	ldr	r1, [r4, #2564]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #2550]	@ zero_extendqisi2
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r3, [r4, #2630]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #2636]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, [r4, #2644]
	ldr	r0, [r5, #4]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SM_ReleaseStreamSeg
	UNWIND(.fnend)
	.size	AVS2_ClearPacket, .-AVS2_ClearPacket
	.align	2
	.global	AVS2_ClearPicSlice
	.type	AVS2_ClearPicSlice, %function
AVS2_ClearPicSlice:
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
	ldr	r3, [r0, #1728]
	mov	r5, r0
	cmp	r3, #0
	movne	r6, r0
	movne	r4, #0
	bne	.L67
	b	.L68
.L66:
	ldr	r3, [r5, #1728]
	add	r6, r6, #36
	cmp	r3, r4
	bls	.L68
.L67:
	ldr	r1, [r6, #1760]
	ldr	r0, [r5, #4]
	bl	SM_ReleaseStreamSeg
	mov	r3, r4, asl #5
	add	r3, r3, r4, lsl #2
	add	r4, r4, #1
	add	r3, r5, r3
	add	r3, r3, #1728
	ldrh	r3, [r3, #28]
	cmp	r3, #256
	bne	.L66
	ldr	r3, [r6, #1744]
	cmp	r3, #0
	beq	.L66
	ldr	r1, [r6, #1764]
	add	r6, r6, #36
	ldr	r0, [r5, #4]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r5, #1728]
	cmp	r3, r4
	bhi	.L67
.L68:
	mov	r3, #0
	str	r3, [r5, #1728]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_ClearPicSlice, .-AVS2_ClearPicSlice
	.align	2
	.global	AVS2_ClearDpb
	.type	AVS2_ClearDpb, %function
AVS2_ClearDpb:
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
	add	r4, r0, #18944
	add	r5, r0, #20736
	mov	r6, r0
	add	r4, r4, #200
	add	r5, r5, #72
	mov	r7, #0
	b	.L76
.L75:
	add	r4, r4, #104
	cmp	r4, r5
	beq	.L81
.L76:
	ldrb	r3, [r4, #-50]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L75
	ldr	r1, [r4]
	mov	r2, #0
	ldr	r0, [r6, #4]
	add	r4, r4, #104
	bl	FSP_ClearLogicFs
	strb	r7, [r4, #-154]
	cmp	r4, r5
	bne	.L76
.L81:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_ClearDpb, .-AVS2_ClearDpb
	.align	2
	.global	AVS2_SequenceDisplayExtension
	.type	AVS2_SequenceDisplayExtension, %function
AVS2_SequenceDisplayExtension:
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
	add	r5, r0, #44
	add	r4, r0, #16384
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #924]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #928]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #932]
	bne	.L88
.L83:
	mov	r1, #14
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #948]
	mov	r0, r5
	bl	BsGet
	mov	r1, #14
	str	r0, [r4, #952]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #956]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	mov	r6, r0
	str	r0, [r4, #960]
	beq	.L89
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L88:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #936]
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	str	r0, [r4, #940]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #944]
	b	.L83
.L89:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	str	r0, [r4, #964]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #968]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_SequenceDisplayExtension, .-AVS2_SequenceDisplayExtension
	.align	2
	.global	AVS2_CopyrightExtension
	.type	AVS2_CopyrightExtension, %function
AVS2_CopyrightExtension:
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
	add	r4, r0, #44
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #8
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #7
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #20
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_CopyrightExtension, .-AVS2_CopyrightExtension
	.align	2
	.global	AVS2_CameraParametersExtension
	.type	AVS2_CameraParametersExtension, %function
AVS2_CameraParametersExtension:
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
	add	r4, r0, #44
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #7
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #22
	bl	BsGet
	mov	r0, r4
	mov	r1, #1
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_CameraParametersExtension, .-AVS2_CameraParametersExtension
	.align	2
	.global	AVS2_TemporalScalabilityExtension
	.type	AVS2_TemporalScalabilityExtension, %function
AVS2_TemporalScalabilityExtension:
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
	add	r5, r0, #44
	mov	r1, #4
	add	r7, r0, #16384
	mov	r4, r0
	mov	r0, r5
	bl	BsGet
	mov	r0, r5
	mov	r1, #3
	bl	BsGet
	cmp	r0, #0
	str	r0, [r7, #2044]
	beq	.L97
	add	r4, r4, #18176
	mov	r6, #0
	add	r4, r4, #252
.L94:
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	mov	r1, #18
	add	r6, r6, #1
	str	r0, [r4, #4]!
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #28]
	mov	r0, r5
	bl	BsGet
	mov	r1, #12
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #60]
	ldr	r3, [r7, #2044]
	cmp	r3, r6
	bhi	.L94
.L97:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_TemporalScalabilityExtension, .-AVS2_TemporalScalabilityExtension
	.align	2
	.global	AVS2_PictureDisplayExtension
	.type	AVS2_PictureDisplayExtension, %function
AVS2_PictureDisplayExtension:
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
	add	r4, r0, #44
	add	r7, r0, #12288
	mov	r5, r0
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	ldr	r3, [r7, #2608]
	cmp	r3, #1
	add	r3, r5, #16384
	beq	.L115
	ldr	r2, [r3, #1148]
	cmp	r2, #0
	bne	.L116
.L100:
	mov	r3, #1
	str	r3, [r7, #2596]
.L102:
	add	r5, r5, #18176
	mov	r6, #0
	add	r5, r5, #224
.L104:
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	add	r6, r6, r1
	str	r0, [r5, #4]!
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #12]
	mov	r0, r4
	bl	BsGet
	ldr	r3, [r7, #2596]
	cmp	r6, r3
	bcc	.L104
	mov	r0, r4
	bl	AVS2_SkipToNextStartCode
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L116:
	ldr	r3, [r3, #1156]
	cmp	r3, #1
	beq	.L103
.L101:
	mov	r3, #2
	str	r3, [r7, #2596]
	b	.L102
.L115:
	ldr	r2, [r3, #1156]
	cmp	r2, #1
	bne	.L100
	ldr	r3, [r3, #1152]
	cmp	r3, #1
	bne	.L101
.L103:
	mov	r3, #3
	str	r3, [r7, #2596]
	b	.L102
	UNWIND(.fnend)
	.size	AVS2_PictureDisplayExtension, .-AVS2_PictureDisplayExtension
	.align	2
	.global	AVS2_MasteringMetadataExtension
	.type	AVS2_MasteringMetadataExtension, %function
AVS2_MasteringMetadataExtension:
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
	add	r4, r0, #44
	add	r5, r0, #18432
	mov	r6, r0
	mov	r1, #4
	mov	r0, r4
	mov	r7, r5
	bl	BsGet
	add	r5, r5, #92
	add	r7, r7, #104
.L118:
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #4]!
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #12]
	mov	r0, r4
	bl	BsGet
	cmp	r5, r7
	bne	.L118
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	add	r5, r6, #16384
	mov	r1, #1
	str	r0, [r5, #2168]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2172]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2176]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2180]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2184]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2188]
	mov	r0, r4
	bl	BsGet
	mov	r0, r4
	mov	r1, #16
	bl	BsGet
	mov	r3, #1
	mov	r0, r3
	str	r3, [r5, #2136]
	str	r3, [r5, #2140]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_MasteringMetadataExtension, .-AVS2_MasteringMetadataExtension
	.align	2
	.global	AVS2_Extension
	.type	AVS2_Extension, %function
AVS2_Extension:
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
	add	r4, r0, #44
	mov	r1, #32
	mov	r5, r0
	mov	r0, r4
	bl	BsGet
	mov	r0, r4
	mov	r1, #4
	bl	BsShow
	sub	r0, r0, #2
	cmp	r0, #10
	ldrls	pc, [pc, r0, asl #2]
	b	.L121
.L123:
	.word	.L122
	.word	.L124
	.word	.L125
	.word	.L121
	.word	.L121
	.word	.L126
	.word	.L121
	.word	.L121
	.word	.L127
	.word	.L128
	.word	.L129
.L121:
	mov	r0, r4
	mov	r1, #4
	bl	BsSkip
.L129:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L128:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_CameraParametersExtension
.L122:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_SequenceDisplayExtension
.L124:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_TemporalScalabilityExtension
.L125:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_CopyrightExtension
.L126:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_PictureDisplayExtension
.L127:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_MasteringMetadataExtension
	UNWIND(.fnend)
	.size	AVS2_Extension, .-AVS2_Extension
	.align	2
	.global	AVS2_User_Data
	.type	AVS2_User_Data, %function
AVS2_User_Data:
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
	add	r4, r0, #44
	mov	r5, r0
	ldr	r1, .L137
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #32
	bl	BsGet
	b	.L132
.L135:
	ldr	r3, [r5, #68]
	ldr	r2, [r5, #60]
	add	ip, r3, #8
	cmp	ip, r2, asl #3
	bhi	.L136
	bl	BsGet
.L132:
	mov	r1, #24
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	cmp	r0, #1
	mov	r0, r4
	bne	.L135
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L136:
	str	r2, [sp]
	mov	r0, #1
	ldr	r2, .L137+4
	ldr	r1, .L137+8
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L138:
	.align	2
.L137:
	.word	.LC7
	.word	.LANCHOR0+28
	.word	.LC8
	UNWIND(.fnend)
	.size	AVS2_User_Data, .-AVS2_User_Data
	.align	2
	.global	AVS2_ConvertHDRInfo
	.type	AVS2_ConvertHDRInfo, %function
AVS2_ConvertHDRInfo:
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
	ldr	r3, [r1, #4]
	mov	ip, r2
	add	lr, r0, #484
	add	r5, r2, #16
	add	lr, lr, #2
	add	r4, r0, #492
	strb	r3, [r0, #480]
	mov	r3, #0
	ldr	r6, [r1, #12]
	strb	r6, [r0, #481]
	ldr	r6, [r1, #20]
	strb	r6, [r0, #482]
	ldr	r1, [r1, #16]
	str	r1, [r0, #484]
	ldr	r1, [ip], #4
	strb	r1, [r0, #456]
.L140:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	cmp	r3, #3
	strh	r1, [lr, #2]!	@ movhi
	ldr	r1, [r5, #4]!
	strh	r1, [r4, #2]!	@ movhi
	bne	.L140
	ldr	ip, [r2, #32]
	add	r1, r0, #500
	movw	r3, #502
	strh	ip, [r1]	@ movhi
	ldr	r1, [r2, #36]
	strh	r1, [r0, r3]	@ movhi
	ldr	r3, [r2, #40]
	str	r3, [r0, #504]
	ldr	r3, [r2, #44]
	str	r3, [r0, #508]
	ldr	r3, [r2, #4]
	strb	r3, [r0, #457]
	ldr	r3, [r2, #48]
	str	r3, [r0, #512]
	ldr	r3, [r2, #52]
	str	r3, [r0, #516]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_ConvertHDRInfo, .-AVS2_ConvertHDRInfo
	.align	2
	.global	AVS2_WriteSliceMsg
	.type	AVS2_WriteSliceMsg, %function
AVS2_WriteSliceMsg:
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
	ldr	r2, [r0, #1728]
	mov	r4, r0
	cmp	r2, #255
	bhi	.L148
	add	r7, r0, #44
	mov	r1, #24
	mov	r0, r7
	bl	BsSkip
	mov	r0, r7
	mov	r1, #8
	bl	BsGet
	cmp	r0, #143
	mov	r6, r0
	bhi	.L149
	add	r5, r4, #12288
	mov	r1, #144
	ldr	r2, [r5, #2676]
	ldr	r3, [r5, #2624]
	cmp	r3, r1, asl r2
	bhi	.L150
.L146:
	mov	r1, #8
	mov	r0, r7
	bl	BsGet
	ldr	r2, [r5, #2676]
	ldr	r3, [r5, #2616]
	mov	r1, #255
	cmp	r3, r1, asl r2
	mov	r8, r0
	bhi	.L151
.L147:
	ldr	r2, [r4, #1728]
	add	r5, r5, #4992
	add	r7, r4, #16384
	mov	r0, #1
	add	lr, r2, #1
	mov	r3, r2, asl #5
	add	r3, r3, r2, lsl #2
	add	r3, r4, r3
	add	r2, r3, #1728
	mov	ip, r3
	strh	r6, [r2, #6]	@ movhi
	strh	r8, [r2, #4]	@ movhi
	ldrh	r2, [r5, #16]
	mla	r6, r2, r6, r8
	mov	r2, r3
	str	r6, [ip, #1736]!
	ldr	r5, [r7, #2556]
	str	r5, [ip, #4]
	ldr	ip, [r7, #2636]
	str	ip, [r3, #1744]
	ldr	ip, [r7, #2560]
	str	ip, [r2, #1748]!
	ldr	ip, [r7, #2640]
	str	ip, [r2, #4]
	ldrb	r2, [r7, #2550]	@ zero_extendqisi2
	strb	r2, [r3, #1756]
	ldrb	r2, [r7, #2630]	@ zero_extendqisi2
	strb	r2, [r3, #1757]
	ldr	r2, [r7, #2564]
	str	r2, [r3, #1760]
	ldr	r2, [r7, #2644]
	str	r2, [r3, #1764]
	ldr	r3, [r4, #12]
	str	lr, [r4, #1728]
	orr	r3, r3, #32768
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L148:
	mov	r3, #256
	ldr	r1, .L152
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L149:
	mov	r2, r0
	ldr	r1, .L152+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L151:
	mov	r0, r7
	mov	r1, #2
	bl	BsGet
	add	r8, r8, r0, lsl #8
	b	.L147
.L150:
	mov	r1, #3
	mov	r0, r7
	bl	BsGet
	add	r6, r6, r0, lsl #7
	b	.L146
.L153:
	.align	2
.L152:
	.word	.LC9
	.word	.LC10
	UNWIND(.fnend)
	.size	AVS2_WriteSliceMsg, .-AVS2_WriteSliceMsg
	.align	2
	.global	AVS2_Head_GetRefConfigSet
	.type	AVS2_Head_GetRefConfigSet, %function
AVS2_Head_GetRefConfigSet:
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
	mov	r6, r1
	mov	r5, r0
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #3
	str	r0, [r5]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #4]
	addne	r7, r5, #4
	movne	r4, #0
	beq	.L159
.L158:
	mov	r1, #6
	mov	r0, r6
	bl	BsGet
	add	r4, r4, #1
	str	r0, [r7, #4]!
	ldr	r3, [r5, #4]
	cmp	r3, r4
	bhi	.L158
.L159:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #36]
	addne	r7, r5, #36
	movne	r4, #0
	beq	.L157
.L160:
	mov	r1, #6
	mov	r0, r6
	bl	BsGet
	add	r4, r4, #1
	str	r0, [r7, #4]!
	ldr	r3, [r5, #36]
	cmp	r3, r4
	bhi	.L160
.L157:
	mov	r0, r6
	mov	r1, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	AVS2_Head_GetRefConfigSet, .-AVS2_Head_GetRefConfigSet
	.align	2
	.global	AVS2_WeightQuantMatrix
	.type	AVS2_WeightQuantMatrix, %function
AVS2_WeightQuantMatrix:
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
	add	r8, r0, #16
	mov	r5, r0
	mov	r4, r1
	mov	r6, r2
.L165:
	add	r7, r5, #4
.L164:
	mov	r0, r6
	bl	AVS2_ue_v.isra.2
	strb	r0, [r5], #1
	cmp	r5, r7
	bne	.L164
	cmp	r5, r8
	bne	.L165
	add	r7, r4, #64
.L167:
	add	r5, r4, #8
.L166:
	mov	r0, r6
	bl	AVS2_ue_v.isra.2
	strb	r0, [r4], #1
	cmp	r4, r5
	bne	.L166
	cmp	r4, r7
	bne	.L167
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_WeightQuantMatrix, .-AVS2_WeightQuantMatrix
	.align	2
	.global	AVS2_SetupWqMatrix84DataIdx01
	.type	AVS2_SetupWqMatrix84DataIdx01, %function
AVS2_SetupWqMatrix84DataIdx01:
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
	ldr	r5, .L197
	mov	r4, r0
	mov	r2, #6
	sub	r0, fp, #36
	mov	r1, #0
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r3, [r4, #2716]
	cmp	r3, #0
	beq	.L195
	cmp	r3, #1
	beq	.L196
	cmp	r3, #2
	beq	.L193
.L194:
	add	lr, r4, #2480
	add	lr, lr, #5
.L174:
	ldr	r3, [r4, #2720]
	cmp	r3, #0
	beq	.L185
	cmp	r3, #1
	beq	.L186
	ldr	ip, .L197+4
	add	r2, ip, #64
	b	.L179
.L185:
	ldr	ip, .L197+8
	add	r2, ip, #64
.L179:
	add	r5, r2, #16
.L180:
	add	r0, r2, #4
	mov	r1, lr
.L181:
	ldrb	r3, [r2], #1	@ zero_extendqisi2
	sub	r6, fp, #28
	add	r3, r6, r3
	cmp	r0, r2
	ldrb	r3, [r3, #-8]	@ zero_extendqisi2
	strb	r3, [r1, #1]!
	bne	.L181
	cmp	r0, r5
	add	lr, lr, #4
	mov	r2, r0
	bne	.L180
	add	r0, r4, #2496
	add	lr, ip, #64
	add	r0, r0, #13
.L182:
	sub	r2, r0, #8
	mov	r1, ip
.L183:
	ldrb	r3, [r1], #1	@ zero_extendqisi2
	sub	r4, fp, #28
	add	r3, r4, r3
	ldrb	r3, [r3, #-8]	@ zero_extendqisi2
	strb	r3, [r2, #1]!
	cmp	r0, r2
	bne	.L183
	add	ip, ip, #8
	add	r0, r0, #8
	cmp	ip, lr
	bne	.L182
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L195:
	ldr	r3, [r5, #52]
	sub	r0, fp, #36
	mov	r2, #6
	ldr	r1, .L197+12
	blx	r3
	add	lr, r4, #2480
	add	lr, lr, #5
	b	.L174
.L196:
	add	r2, r4, #2464
	ldr	r0, .L197+16
	sub	r1, fp, #36
	mov	lr, r2
	add	r2, r2, #9
	add	lr, lr, #15
.L176:
	ldrb	ip, [r2, #1]!	@ zero_extendqisi2
	ldrb	r3, [r0], #1	@ zero_extendqisi2
	cmp	r2, lr
	add	r3, r3, ip
	strb	r3, [r1], #1
	bne	.L176
	b	.L194
.L193:
	add	r1, r4, #2464
	add	lr, r4, #2480
	ldr	r0, .L197+20
	add	r1, r1, #15
	add	lr, lr, #5
	sub	r3, fp, #36
.L178:
	ldrb	ip, [r1, #1]!	@ zero_extendqisi2
	ldrb	r2, [r0], #1	@ zero_extendqisi2
	cmp	r1, lr
	add	r2, r2, ip
	strb	r2, [r3], #1
	bne	.L178
	b	.L174
.L186:
	ldr	ip, .L197+24
	add	r2, ip, #64
	b	.L179
.L198:
	.align	2
.L197:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+204
	.word	.LANCHOR0+44
	.word	.LANCHOR0+284
	.word	.LANCHOR0+292
	.word	.LANCHOR0+300
	.word	.LANCHOR0+124
	UNWIND(.fnend)
	.size	AVS2_SetupWqMatrix84DataIdx01, .-AVS2_SetupWqMatrix84DataIdx01
	.align	2
	.global	AVS2_SetupWqMatrix84
	.type	AVS2_SetupWqMatrix84, %function
AVS2_SetupWqMatrix84:
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
	ldr	r3, [r0, #2696]
	mov	r4, r0
	cmp	r3, #0
	beq	.L204
	ldr	r3, [r0, #2700]
	cmp	r3, #0
	bne	.L201
	ldr	r3, [r0, #88]
	add	r0, r0, #2480
	ldr	r5, .L205
	add	r0, r0, #6
	cmp	r3, #0
	mov	r2, #16
	bne	.L202
	ldr	r3, [r5, #52]
	ldr	r1, .L205+4
	blx	r3
	add	r0, r4, #2496
	ldr	r3, [r5, #52]
	add	r0, r0, #6
	mov	r2, #64
	ldr	r1, .L205+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L201:
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_SetupWqMatrix84DataIdx01
.L204:
	ldr	r5, .L205
	add	r0, r0, #2480
	mov	r2, #16
	mov	r1, #64
	add	r0, r0, #6
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #2496
	mov	r2, #64
	ldr	r3, [r5, #48]
	add	r0, r0, #6
	mov	r1, r2
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L202:
	add	r1, r4, #108
	ldr	r3, [r5, #52]
	blx	r3
	add	r0, r4, #2496
	ldr	r3, [r5, #52]
	add	r0, r0, #6
	add	r1, r4, #124
	mov	r2, #64
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L206:
	.align	2
.L205:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+308
	.word	.LANCHOR0+324
	UNWIND(.fnend)
	.size	AVS2_SetupWqMatrix84, .-AVS2_SetupWqMatrix84
	.align	2
	.global	AVS2_ALF_ParameterSet
	.type	AVS2_ALF_ParameterSet, %function
AVS2_ALF_ParameterSet:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 608
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #612)
	sub	sp, sp, #612
	ldr	r6, [r0, #252]
	mov	r5, r0
	mov	r4, r1
	cmp	r6, #1
	beq	.L269
.L208:
	ldr	r3, [r5, #256]
	cmp	r3, #1
	beq	.L270
	ldr	r3, [r5, #260]
	cmp	r3, #1
	beq	.L239
.L241:
	mov	r0, #1
.L264:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L272:
	add	r2, r3, #1088
	cmp	r2, #2160
	bcs	.L234
	add	r3, r5, #904
	add	r0, r5, #936
	mov	r2, #64
.L235:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	sub	r2, r2, r1, asl #1
	bne	.L235
	ldr	r1, [r5, #260]
	ldr	r3, [r5, #940]
	cmp	r1, #1
	add	r2, r3, r2
	str	r2, [r5, #940]
	bne	.L241
.L239:
	mov	r0, r4
	mov	r7, r5
	bl	AVS2_se_v.isra.3
	mov	r6, #0
	mov	r3, r0
	str	r0, [r7, #944]!
	b	.L240
.L244:
	bl	AVS2_se_v.isra.3
	add	r6, r6, #1
	cmp	r6, #8
	mov	r3, r0
	str	r0, [r7, #4]!
	beq	.L271
.L240:
	add	r1, r3, #64
	mov	r0, r4
	cmp	r1, #127
	bls	.L244
	mov	r2, r6
	ldr	r1, .L276
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L264
.L270:
	mov	r0, r4
	mov	r7, r5
	bl	AVS2_se_v.isra.3
	mov	r6, #0
	mov	r3, r0
	str	r0, [r7, #908]!
	b	.L238
.L236:
	bl	AVS2_se_v.isra.3
	add	r6, r6, #1
	cmp	r6, #8
	mov	r3, r0
	str	r0, [r7, #4]!
	beq	.L272
.L238:
	add	r1, r3, #64
	mov	r0, r4
	cmp	r1, #127
	bls	.L236
	mov	r2, r6
	ldr	r1, .L276+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L264
.L269:
	mov	r0, r1
	bl	AVS2_ue_v.isra.2
	cmp	r0, #15
	str	r0, [r5, #264]
	bhi	.L209
	cmn	r0, #1
	beq	.L273
	add	r3, r5, #268
	sub	r7, fp, #624
	str	r6, [fp, #-644]
	mov	r8, #0
	mov	r6, r3
	str	r3, [fp, #-648]
.L223:
	cmp	r8, #0
	movle	r3, #0
	movgt	r3, #1
	cmp	r0, #15
	cmpne	r8, #0
	ble	.L213
	mov	r0, r4
	bl	AVS2_ue_v.isra.2
	sub	r3, r0, #1
	str	r0, [r6]
	cmp	r3, #14
	bhi	.L274
.L215:
	mov	r0, r4
	mov	r9, r7
	bl	AVS2_se_v.isra.3
	mov	r10, #0
	str	r6, [fp, #-640]
	mov	r3, r0
	str	r0, [r9, #4]!
	b	.L222
.L219:
	ldr	ip, [r6]
	cmp	ip, #63
	bhi	.L220
	bl	AVS2_se_v.isra.3
	add	r10, r10, #1
	cmp	r10, #8
	mov	r3, r0
	str	r0, [r9, #4]!
	beq	.L275
.L222:
	cmn	r3, #64
	mov	r0, r4
	bge	.L219
.L220:
	mov	r2, r10
	ldr	r1, .L276+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L264
.L213:
	cmp	r3, #0
	ldrne	r3, [fp, #-644]
	strne	r3, [r6]
	b	.L215
.L209:
	mov	r2, r0
	ldr	r1, .L276+12
	mov	r0, r6
	bl	dprint_vfmw
	mov	r0, #0
	b	.L264
.L274:
	mov	r2, r0
	ldr	r1, .L276+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L264
.L273:
	mov	r0, #0
	strb	r0, [fp, #-636]
.L224:
	sub	r2, fp, #636
	mov	r3, r0
	add	r0, r2, r0
	sub	r2, fp, #44
	add	r1, r2, r3
.L232:
	add	r3, r3, #1
	ldrb	r2, [r1, #-592]	@ zero_extendqisi2
	cmp	r3, #15
	strb	r2, [r0], #1
	ble	.L232
.L231:
	ldr	r6, .L276+20
	add	r7, r5, #332
	ldr	r9, .L276+24
	add	r8, r6, #16
.L233:
	ldrb	r1, [r6, #1]!	@ zero_extendqisi2
	sub	ip, fp, #44
	mov	r2, #36
	mov	r0, r7
	add	r1, ip, r1
	ldr	r3, [r9, #52]
	add	r7, r7, r2
	ldrb	ip, [r1, #-592]	@ zero_extendqisi2
	mov	r1, ip, asl #5
	add	r1, r1, ip, lsl #2
	sub	ip, fp, #620
	add	r1, ip, r1
	blx	r3
	cmp	r6, r8
	bne	.L233
	b	.L208
.L271:
	add	r2, r3, #1088
	cmp	r2, #2160
	bcs	.L242
	add	r3, r5, #940
	add	r0, r5, #972
	mov	r2, #64
.L243:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	sub	r2, r2, r1, asl #1
	bne	.L243
	ldr	r3, [r5, #976]
	mov	r0, #1
	add	r2, r3, r2
	str	r2, [r5, #976]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L275:
	cmn	r3, #1088
	blt	.L217
	ldr	r2, [fp, #-640]
	add	r6, r6, #4
	ldr	r2, [r2]
	cmp	r2, #1072
	bcs	.L217
	add	r0, r7, #32
	mov	r3, r7
	mov	r1, #64
.L218:
	ldr	r2, [r3, #4]!
	cmp	r0, r3
	sub	r1, r1, r2, asl #1
	bne	.L218
	ldr	r0, [r5, #264]
	add	r8, r8, #1
	ldr	r3, [r7, #36]
	add	ip, r0, #1
	cmp	r8, ip
	add	r1, r3, r1
	str	r1, [r7, #36]!
	bcc	.L223
	cmp	ip, #1
	mov	r0, #0
	strb	r0, [fp, #-636]
	bls	.L224
	mov	r8, #1
	mov	lr, r0
.L225:
	ldr	r3, [fp, #-648]
	ldr	r7, [r3, #4]!
	cmp	r7, #1
	str	r3, [fp, #-648]
	subeq	r3, fp, #44
	addeq	r3, r3, lr
	beq	.L229
	sub	r1, fp, #44
	sub	r6, r7, #1
	mov	r3, lr
	mov	r2, #0
	add	r1, r1, lr
	b	.L230
.L226:
	ldrb	r0, [r1, #-592]	@ zero_extendqisi2
.L230:
	add	r2, r2, #1
	add	r3, r3, #1
	cmp	r2, r6
	strb	r0, [r1, #-591]
	uxtb	r3, r3
	sub	r1, fp, #44
	add	r1, r1, r3
	bne	.L226
	add	lr, lr, #1
	sub	r7, r7, #2
	sub	r3, fp, #44
	uxtab	lr, r7, lr
	uxtb	lr, lr
	add	r3, r3, lr
	ldrb	r0, [r3, #-592]	@ zero_extendqisi2
.L229:
	add	r8, r8, #1
	add	lr, lr, #1
	cmp	r8, ip
	add	r0, r0, #1
	uxtb	lr, lr
	strb	r0, [r3, #-591]
	subne	r3, fp, #44
	addne	r3, r3, lr
	ldrneb	r0, [r3, #-592]	@ zero_extendqisi2
	bne	.L225
.L227:
	cmp	lr, #15
	mov	r0, lr
	ble	.L224
	b	.L231
.L234:
	mov	r2, r3
	ldr	r1, .L276+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L264
.L217:
	mov	r2, r3
	ldr	r1, .L276+32
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L264
.L242:
	mov	r2, r3
	ldr	r1, .L276+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L264
.L277:
	.align	2
.L276:
	.word	.LC18
	.word	.LC16
	.word	.LC14
	.word	.LC11
	.word	.LC12
	.word	.LANCHOR0+387
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC15
	.word	.LC13
	.word	.LC17
	UNWIND(.fnend)
	.size	AVS2_ALF_ParameterSet, .-AVS2_ALF_ParameterSet
	.global	__aeabi_uidiv
	.align	2
	.global	AVS2_DeriveMaxDpbNum
	.type	AVS2_DeriveMaxDpbNum, %function
AVS2_DeriveMaxDpbNum:
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
	mov	r5, r0
	cmp	r2, #34
	movls	r3, #15
	strlsb	r3, [r0, #2412]
	ldmlsfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r0, #24]
	cmp	r2, #74
	ldr	r4, [r0, #16]
	add	r3, r3, #7
	movls	r0, #13369344
	add	r4, r4, #7
	bic	r3, r3, #7
	bic	r4, r4, #7
	mul	r4, r4, r3
	mov	r1, r4
	bls	.L286
	cmp	r2, #90
	movls	r0, #56623104
	movhi	r0, #213909504
.L286:
	bl	__aeabi_uidiv
	mov	r3, #57344
	movt	r3, 31
	cmp	r0, #16
	movcs	r0, #16
	sub	r0, r0, #1
	cmp	r4, r3
	uxtb	r0, r0
	movls	r3, #7
	movhi	r3, #6
	movls	r2, #15
	movhi	r2, #10
	cmp	r3, r0
	movcc	r3, r0
	cmp	r3, r2
	movcs	r3, r2
	strb	r3, [r5, #2412]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_DeriveMaxDpbNum, .-AVS2_DeriveMaxDpbNum
	.align	2
	.global	AVS2_IntraPictureHeader
	.type	AVS2_IntraPictureHeader, %function
AVS2_IntraPictureHeader:
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
	ldr	r8, .L383
	ldr	r3, [r0, #12]
	add	r9, r0, #17152
	mov	r7, r0
	add	r9, r9, #204
	mov	r2, #16
	mov	r1, #0
	bic	r3, r3, #262144
	add	r5, r7, #44
	str	r3, [r7, #12]
	add	r0, r9, #268
	ldr	r3, [r8, #48]
	add	r4, r7, #16384
	blx	r3
	mov	r0, r7
	bl	AVS2_Vfmw_EpbRemove
	mov	r1, #32
	mov	r0, r5
	add	r6, r7, #12288
	bl	BsGet
	mov	r0, r5
	mov	r1, #32
	bl	BsGet
	str	r0, [r4, #1068]
	ldr	r3, [r6, #2600]
	cmp	r3, #72
	beq	.L363
.L288:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #1076]
	beq	.L364
.L289:
	ldr	r3, [r6, #2688]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r4, #1112]
	beq	.L365
.L292:
	mov	r3, #0
	str	r3, [r4, #1116]
.L293:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1120]
	ldr	r3, [r6, #2668]
	cmp	r3, #1
	movne	r3, #0
	strne	r3, [r4, #1124]
	beq	.L366
.L295:
	ldr	r3, [r6, #2664]
	cmp	r3, #0
	bne	.L296
	ldr	r3, [r4, #1112]
	cmp	r3, #0
	beq	.L297
	ldr	r3, [r4, #1116]
	cmp	r3, #1
	beq	.L297
.L296:
	mov	r3, #0
	str	r3, [r4, #1128]
.L298:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #1132]
	beq	.L299
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	mov	r2, #68
	mov	r3, r0, asl #6
	str	r0, [r4, #1136]
	add	r1, r3, r0, lsl #2
	ldr	r3, [r8, #52]
	add	r1, r7, r1
	add	r0, r9, #980
	add	r1, r1, #15104
	blx	r3
	ldr	r3, [r6, #2664]
	cmp	r3, #1
	beq	.L367
.L301:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1144]
	ldr	r3, [r6, #2608]
	cmp	r3, #1
	beq	.L368
	ldr	r3, [r6, #2612]
	cmp	r3, #1
	beq	.L369
	cmp	r0, #0
	beq	.L336
.L304:
	mov	r3, #1
	str	r3, [r4, #1148]
.L307:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #1152]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1156]
	ldr	r8, [r6, #2612]
	cmp	r8, #1
	movne	r3, #1
	strne	r3, [r4, #1160]
	beq	.L370
.L309:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #7
	str	r0, [r4, #1164]
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #917]	@ zero_extendqisi2
	mov	r8, r8, asl #3
	sub	r8, r8, #1
	cmp	r8, r0
	str	r0, [r4, #1168]
	bcc	.L371
.L310:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r4, #1180]
	beq	.L372
.L312:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r4, #1204]
	movne	r3, #0
	strne	r3, [r4, #1208]
	strne	r3, [r4, #1212]
	beq	.L373
.L318:
	mov	r8, #2
	strb	r8, [r4, #973]
	ldr	r3, [r6, #2680]
	cmp	r3, #0
	streq	r3, [r4, #1200]
	streq	r3, [r4, #1196]
	bne	.L374
.L359:
	ldr	r3, [r6, #2804]
	cmp	r3, #1
	beq	.L375
	mov	r3, #0
	str	r3, [r4, #1224]
	str	r3, [r4, #1228]
	str	r3, [r4, #1232]
.L330:
	ldr	r3, [r4, #1228]
	cmp	r3, #0
	beq	.L376
.L329:
	mov	r1, r5
	mov	r0, r9
	bl	AVS2_ALF_ParameterSet
	subs	r5, r0, #0
	beq	.L377
.L331:
	ldr	r3, [r4, #1112]
	cmp	r3, #0
	bne	.L378
.L361:
	str	r3, [r4, #1104]
.L334:
	add	r0, r7, #14848
	mov	r5, #1
	mov	r3, #0
	add	r0, r0, #36
	strb	r3, [r4, #972]
	str	r5, [r4, #1108]
	bl	AVS2_SetupWqMatrix84
	ldr	r3, [r7, #12]
	mov	r0, r5
	orr	r3, r3, #262144
	str	r3, [r7, #12]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L375:
	add	r6, r7, #17408
	mov	r8, r6
	add	r6, r6, #196
	add	r8, r8, #208
.L328:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r6, #4]!
	cmp	r6, r8
	bne	.L328
	ldr	r3, [r4, #1224]
	cmp	r3, #0
	bne	.L329
	b	.L330
.L299:
	mov	r1, r5
	add	r0, r9, #980
	bl	AVS2_Head_GetRefConfigSet
	ldr	r3, [r6, #2664]
	cmp	r3, #1
	bne	.L301
.L367:
	mov	r0, r5
	bl	AVS2_ue_v.isra.2
	str	r0, [r4, #1140]
	b	.L301
.L378:
	ldr	r3, [r4, #1116]
	cmp	r3, #1
	moveq	r3, #5
	streq	r3, [r4, #1104]
	beq	.L334
	mov	r3, #6
	b	.L361
.L376:
	ldr	r3, [r4, #1232]
	cmp	r3, #0
	beq	.L331
	b	.L329
.L297:
	mov	r0, r5
	bl	AVS2_ue_v.isra.2
	cmp	r0, #63
	str	r0, [r4, #1128]
	bls	.L298
	mov	r2, r0
	ldr	r1, .L383+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #63
	str	r3, [r4, #1128]
	b	.L298
.L365:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #1112]
	bne	.L292
	mov	r1, r0
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1116]
	b	.L293
.L374:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #1196]
	streq	r0, [r4, #1200]
	beq	.L359
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #1200]
	beq	.L379
	cmp	r0, #2
	bne	.L359
	mov	r2, r5
	add	r1, r9, #30
	add	r0, r9, #14
	bl	AVS2_WeightQuantMatrix
	b	.L359
.L373:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #16
	str	r0, [r4, #1208]
	cmp	r3, #32
	bhi	.L380
.L317:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #16
	str	r0, [r4, #1212]
	cmp	r3, #32
	bls	.L318
	mov	r2, r0
	ldr	r1, .L383+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #1212]
	b	.L318
.L372:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #1184]
	streq	r0, [r4, #1188]
	streq	r0, [r4, #1192]
	beq	.L312
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #8
	str	r0, [r4, #1188]
	cmp	r3, #16
	bhi	.L381
.L314:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #8
	str	r0, [r4, #1192]
	cmp	r3, #16
	bls	.L312
	mov	r2, r0
	ldr	r1, .L383+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #1192]
	b	.L312
.L371:
	mov	r2, r0
	str	r8, [sp]
	mov	r3, r8
	ldr	r1, .L383+16
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #1168]
	b	.L310
.L369:
	cmp	r0, #0
	beq	.L336
.L303:
	ldr	r1, .L383+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #1144]
.L336:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1148]
	b	.L307
.L368:
	str	r3, [r4, #1144]
	ldr	r3, [r6, #2612]
	cmp	r3, #1
	bne	.L304
	b	.L303
.L377:
	ldr	r2, .L383+24
	mov	r0, #1
	ldr	r1, .L383+28
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L363:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #7
	str	r0, [r4, #1084]
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #1068]
	str	r0, [r4, #1072]
	orr	r0, r0, r3, asl #7
	str	r0, [r4, #1068]
	b	.L288
.L370:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	str	r0, [r4, #1160]
	mov	r0, r5
	bl	BsGet
	b	.L309
.L366:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1124]
	b	.L295
.L364:
	mov	r1, #24
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1080]
	b	.L289
.L380:
	mov	r2, r0
	ldr	r1, .L383+32
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #1208]
	b	.L317
.L381:
	mov	r2, r0
	ldr	r1, .L383+36
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #1188]
	b	.L314
.L379:
	mov	r1, r0
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	str	r0, [r4, #1216]
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #1216]
	cmp	r3, #1
	str	r0, [r4, #1220]
	beq	.L382
.L322:
	cmp	r3, #2
	bne	.L359
	add	r8, r7, #17152
	mov	r10, r8
	add	r8, r8, #211
	add	r10, r10, #217
.L324:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	strb	r0, [r8, #1]!
	cmp	r8, r10
	bne	.L324
	b	.L359
.L382:
	add	r8, r7, #17152
	mov	r10, r8
	add	r8, r8, #205
	add	r10, r10, #211
.L323:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	strb	r0, [r8, #1]!
	cmp	r8, r10
	bne	.L323
	ldr	r3, [r4, #1216]
	b	.L322
.L384:
	.align	2
.L383:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	.word	.LC25
	.word	.LC23
	.word	.LC21
	.word	.LC20
	.word	.LANCHOR0+404
	.word	.LC26
	.word	.LC24
	.word	.LC22
	UNWIND(.fnend)
	.size	AVS2_IntraPictureHeader, .-AVS2_IntraPictureHeader
	.align	2
	.global	AVS2_InterPictureHeader
	.type	AVS2_InterPictureHeader, %function
AVS2_InterPictureHeader:
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
	ldr	r3, [r0, #12]
	add	r5, r0, #44
	add	r4, r0, #16384
	bic	r3, r3, #262144
	str	r3, [r0, #12]
	add	r6, r0, #12288
	mov	r7, r0
	bl	AVS2_Vfmw_EpbRemove
	mov	r1, #32
	mov	r0, r5
	bl	BsGet
	mov	r0, r5
	mov	r1, #32
	bl	BsGet
	str	r0, [r4, #1068]
	ldr	r3, [r6, #2600]
	cmp	r3, #72
	beq	.L458
.L386:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #1088]
	beq	.L459
	ldr	r3, [r6, #2688]
	cmp	r0, #1
	cmpeq	r3, #0
	movne	r0, #0
	moveq	r0, #1
	strne	r0, [r4, #1092]
	beq	.L460
.L390:
	cmp	r3, #0
	mov	r3, #0
	str	r3, [r4, #1096]
	beq	.L461
.L391:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1120]
	ldr	r3, [r6, #2668]
	cmp	r3, #1
	movne	r3, #0
	strne	r3, [r4, #1124]
	beq	.L462
.L393:
	ldr	r3, [r6, #2664]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r4, #1128]
	beq	.L463
.L395:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #1132]
	bne	.L464
	add	r9, r7, #17152
	mov	r1, r5
	add	r9, r9, #204
	add	r0, r9, #980
	bl	AVS2_Head_GetRefConfigSet
	ldr	r3, [r6, #2664]
	cmp	r3, #1
	beq	.L465
.L398:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	subs	r3, r0, #1
	str	r0, [r4, #1144]
	ldr	r2, [r6, #2608]
	movne	r3, #1
	cmp	r2, #1
	movne	r3, #0
	cmp	r3, #0
	beq	.L399
	ldr	r1, .L479
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [r4, #1144]
	ldr	r3, [r6, #2612]
	cmp	r3, #1
	beq	.L403
.L400:
	mov	r3, #1
	str	r3, [r4, #1148]
.L404:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #1152]
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1156]
	ldr	r8, [r6, #2612]
	cmp	r8, #1
	beq	.L466
.L405:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #7
	str	r0, [r4, #1164]
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #917]	@ zero_extendqisi2
	mov	r8, r8, asl #3
	sub	r8, r8, #1
	cmp	r8, r0
	str	r0, [r4, #1168]
	bcc	.L467
.L406:
	ldr	r3, [r4, #1088]
	cmp	r3, #2
	bne	.L407
	ldr	r3, [r4, #1148]
	cmp	r3, #1
	beq	.L408
.L407:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1176]
.L408:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r4, #1100]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r4, #1180]
	beq	.L468
.L410:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	mov	r8, r0
	str	r0, [r4, #1204]
	movne	r3, #0
	strne	r3, [r4, #1208]
	strne	r3, [r4, #1212]
	beq	.L469
.L416:
	mov	r8, #2
	strb	r8, [r4, #973]
	ldr	r3, [r6, #2680]
	cmp	r3, #0
	streq	r3, [r4, #1196]
	bne	.L470
.L438:
	ldr	r3, [r6, #2804]
	cmp	r3, #1
	beq	.L471
	mov	r3, #0
	str	r3, [r4, #1224]
	str	r3, [r4, #1228]
	str	r3, [r4, #1232]
.L428:
	ldr	r3, [r4, #1228]
	cmp	r3, #0
	bne	.L427
	ldr	r3, [r4, #1232]
	cmp	r3, #0
	bne	.L427
.L429:
	ldr	r2, [r4, #1088]
	cmp	r2, #1
	beq	.L472
	cmp	r2, #2
	beq	.L435
	cmp	r2, #3
	bne	.L440
.L435:
	ldrb	r3, [r4, #1956]	@ zero_extendqisi2
	str	r2, [r4, #1104]
	strb	r3, [r4, #972]
	sub	r3, r3, #1
	cmp	r3, #6
	bhi	.L473
.L436:
	add	r0, r7, #14848
	mov	r3, #0
	add	r0, r0, #36
	str	r3, [r4, #1108]
	bl	AVS2_SetupWqMatrix84
	ldr	r3, [r7, #12]
	mov	r5, #1
	orr	r3, r3, #262144
	mov	r0, r5
	str	r3, [r7, #12]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L464:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	ldr	r3, .L479+4
	add	r9, r7, #17152
	mov	r2, #68
	add	r9, r9, #204
	ldr	r3, [r3, #52]
	mov	r1, r0, asl #6
	str	r0, [r4, #1136]
	add	r1, r1, r0, lsl #2
	add	r0, r9, #980
	add	r1, r7, r1
	add	r1, r1, #15104
	blx	r3
	ldr	r3, [r6, #2664]
	cmp	r3, #1
	bne	.L398
.L465:
	mov	r0, r5
	bl	AVS2_ue_v.isra.2
	str	r0, [r4, #1140]
	b	.L398
.L461:
	ldr	r3, [r4, #1088]
	cmp	r3, #2
	beq	.L391
	ldr	r3, [r4, #1092]
	cmp	r3, #0
	bne	.L391
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1096]
	b	.L391
.L471:
	add	r6, r7, #17408
	mov	r8, r6
	add	r6, r6, #196
	add	r8, r8, #208
.L426:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r6, #4]!
	cmp	r6, r8
	bne	.L426
	ldr	r3, [r4, #1224]
	cmp	r3, #0
	beq	.L428
.L427:
	mov	r1, r5
	mov	r0, r9
	bl	AVS2_ALF_ParameterSet
	subs	r5, r0, #0
	bne	.L429
	ldr	r2, .L479+8
	mov	r0, #1
	ldr	r1, .L479+12
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L472:
	ldr	r3, [r4, #1092]
	cmp	r3, #0
	streq	r2, [r4, #1104]
	strneb	r2, [r4, #972]
	ldreq	r3, [r4, #1956]
	movne	r3, #4
	strne	r3, [r4, #1104]
	streqb	r3, [r4, #972]
.L440:
	ldrb	r3, [r4, #972]	@ zero_extendqisi2
	sub	r3, r3, #1
	cmp	r3, #6
	bls	.L436
.L473:
	mov	r3, #7
	ldr	r2, .L479+8
	ldr	r1, .L479+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r5, #0
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L399:
	ldr	r3, [r6, #2612]
	cmp	r3, #1
	beq	.L474
	cmp	r0, #0
	bne	.L400
.L437:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1148]
	b	.L404
.L470:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #1196]
	streq	r0, [r4, #1200]
	beq	.L438
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #1200]
	beq	.L475
	cmp	r0, #2
	bne	.L438
	mov	r2, r5
	add	r1, r9, #30
	add	r0, r9, #14
	bl	AVS2_WeightQuantMatrix
	b	.L438
.L469:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #16
	str	r0, [r4, #1208]
	cmp	r3, #32
	bhi	.L476
.L415:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #16
	str	r0, [r4, #1212]
	cmp	r3, #32
	bls	.L416
	mov	r2, r0
	ldr	r1, .L479+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #1212]
	b	.L416
.L463:
	mov	r0, r5
	bl	AVS2_ue_v.isra.2
	cmp	r0, #63
	str	r0, [r4, #1128]
	bls	.L395
	mov	r2, r0
	ldr	r1, .L479+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #63
	str	r3, [r4, #1128]
	b	.L395
.L468:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #1184]
	streq	r0, [r4, #1188]
	streq	r0, [r4, #1192]
	beq	.L410
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #8
	str	r0, [r4, #1188]
	cmp	r3, #16
	bhi	.L477
.L412:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	add	r3, r0, #8
	str	r0, [r4, #1192]
	cmp	r3, #16
	bls	.L410
	mov	r2, r0
	ldr	r1, .L479+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #1192]
	b	.L410
.L467:
	mov	r2, r0
	str	r8, [sp]
	mov	r3, r8
	ldr	r1, .L479+32
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #1168]
	b	.L406
.L474:
	cmp	r0, #0
	beq	.L437
.L403:
	ldr	r1, .L479+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #1144]
	b	.L437
.L459:
	mov	r2, r0
	ldr	r1, .L479+40
	mov	r0, #1
	mov	r5, r2
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L476:
	mov	r2, r0
	ldr	r1, .L479+44
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #1208]
	b	.L415
.L458:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #7
	str	r0, [r4, #1084]
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #1068]
	str	r0, [r4, #1072]
	orr	r0, r0, r3, asl #7
	str	r0, [r4, #1068]
	b	.L386
.L466:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	str	r0, [r4, #1160]
	mov	r0, r5
	bl	BsGet
	b	.L405
.L462:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1124]
	b	.L393
.L460:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #1092]
	ldr	r3, [r6, #2688]
	b	.L390
.L477:
	mov	r2, r0
	ldr	r1, .L479+48
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r4, #1188]
	b	.L412
.L475:
	mov	r1, r0
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	mov	r1, r8
	str	r0, [r4, #1216]
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #1216]
	cmp	r3, #1
	str	r0, [r4, #1220]
	beq	.L478
.L420:
	cmp	r3, #2
	bne	.L438
	add	r8, r7, #17152
	mov	r10, r8
	add	r8, r8, #211
	add	r10, r10, #217
.L422:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	strb	r0, [r8, #1]!
	cmp	r8, r10
	bne	.L422
	b	.L438
.L478:
	add	r8, r7, #17152
	mov	r10, r8
	add	r8, r8, #205
	add	r10, r10, #211
.L421:
	mov	r0, r5
	bl	AVS2_se_v.isra.3
	strb	r0, [r8, #1]!
	cmp	r8, r10
	bne	.L421
	ldr	r3, [r4, #1216]
	b	.L420
.L480:
	.align	2
.L479:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+428
	.word	.LC26
	.word	.LC36
	.word	.LC35
	.word	.LC28
	.word	.LC33
	.word	.LC31
	.word	.LC30
	.word	.LC27
	.word	.LC34
	.word	.LC32
	UNWIND(.fnend)
	.size	AVS2_InterPictureHeader, .-AVS2_InterPictureHeader
	.align	2
	.global	AVS2_SequenceHeader
	.type	AVS2_SequenceHeader, %function
AVS2_SequenceHeader:
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
	ldr	r1, .L531
	mov	r7, r0
	mov	r0, #7
	add	r6, r7, #44
	bl	dprint_vfmw
	ldr	r3, [r7, #12]
	mov	r1, #32
	mov	r0, r6
	bic	r3, r3, #65536
	str	r3, [r7, #12]
	bl	BsGet
	mov	r0, r6
	mov	r1, #8
	add	r5, r7, #12288
	bl	BsGet
	bic	r3, r0, #2
	str	r0, [r5, #2600]
	cmp	r3, #32
	cmpne	r0, #18
	movne	r8, #1
	moveq	r8, #0
	bne	.L519
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	mov	r4, r0
	str	r0, [r5, #2604]
	beq	.L520
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2608]
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r5, #2608]
	cmp	r0, #1
	cmpeq	r3, #1
	str	r0, [r5, #2612]
	beq	.L521
.L485:
	mov	r1, #14
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	mov	r4, r0
	str	r0, [r5, #2616]
	beq	.L522
	mov	r1, #14
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	mov	r4, r0
	str	r0, [r5, #2624]
	beq	.L523
	ldr	r1, [r5, #2616]
	add	r2, r0, #7
	str	r0, [r5, #2628]
	bic	r2, r2, #7
	add	r3, r1, #7
	str	r2, [r5, #2624]
	str	r1, [r5, #2620]
	bic	r3, r3, #7
	mov	r1, #2
	str	r3, [r5, #2616]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	mov	r4, r0
	str	r0, [r5, #2632]
	beq	.L488
	mov	r2, r0
	ldr	r1, .L531+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L520:
	mov	r2, r0
	ldr	r1, .L531+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L519:
	mov	r2, r0
	ldr	r1, .L531+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L523:
	mov	r2, r0
	ldr	r1, .L531+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L522:
	mov	r2, r0
	ldr	r1, .L531+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L488:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	add	r0, r0, #3
	mov	r2, r0, asl #1
	str	r2, [r5, #2636]
	bic	r3, r2, #2
	cmp	r3, #8
	bne	.L524
	ldr	r2, [r5, #2600]
	cmp	r2, #34
	beq	.L525
	add	r9, r7, #16384
	mov	r2, r3
	mov	r1, #0
	str	r1, [r5, #2640]
	strb	r3, [r9, #917]
.L493:
	ldr	r3, [r7, #36]
	mov	r1, #4
	mov	r0, r6
	str	r2, [r3, #932]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #2644]
	beq	.L526
.L494:
	mov	r1, #4
	mov	r0, r6
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #2648]
	beq	.L527
.L495:
	mov	r1, #18
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2652]
	mov	r0, r6
	bl	BsGet
	mov	r1, #12
	str	r0, [r5, #2656]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2660]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2664]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2656]
	mov	r0, r6
	bl	BsGet
	mov	r1, #18
	str	r0, [r5, #2668]
	mov	r0, r6
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #2672]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2676]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	str	r0, [r5, #2680]
	beq	.L528
.L497:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2688]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2692]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2696]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2700]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2784]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2788]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2792]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2796]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2800]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2804]
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #2808]
	mov	r0, r6
	bl	BsGet
	mov	r1, #6
	str	r0, [r5, #2656]
	mov	r0, r6
	bl	BsGet
	cmp	r0, #32
	str	r0, [r5, #2812]
	bhi	.L499
	cmp	r0, #0
	addne	r8, r7, #15104
	movne	r4, #0
	beq	.L504
.L503:
	mov	r0, r8
	mov	r1, r6
	bl	AVS2_Head_GetRefConfigSet
	ldr	r3, [r5, #2812]
	add	r4, r4, #1
	add	r8, r8, #68
	cmp	r3, r4
	bhi	.L503
.L504:
	ldr	r3, [r5, #2664]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r9, #896]
	beq	.L529
.L505:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #1
	add	r1, r5, #2592
	movw	lr, #2408
	add	r1, r1, #8
	movw	ip, #2410
	str	r0, [r9, #900]
	add	r0, r7, #14848
	ldr	r4, [r5, #2676]
	add	r0, r0, #40
	ldr	r2, [r5, #2616]
	mov	r3, r3, asl r4
	sub	r2, r2, #1
	uxth	r3, r3
	add	r2, r3, r2
	uxth	r2, r2
	mov	r2, r2, asr r4
	strh	r2, [r1, lr]	@ movhi
	ldr	r2, [r5, #2624]
	sub	r2, r2, #1
	add	r3, r3, r2
	uxth	r3, r3
	mov	r3, r3, asr r4
	strh	r3, [r1, ip]	@ movhi
	bl	AVS2_DeriveMaxDpbNum
	add	r3, r7, #8192
	ldr	r2, [r3, #3020]
	cmp	r2, #0
	beq	.L506
	ldr	r3, [r3, #3028]
	cmp	r3, #0
	beq	.L506
	ldr	r1, [r5, #2616]
	cmp	r2, r1
	beq	.L530
.L509:
	mov	r3, #1
	str	r3, [r7, #20]
.L508:
	ldr	r3, [r7, #12]
	mov	r0, #1
	orr	r3, r3, #65536
	str	r3, [r7, #12]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L524:
	mov	r0, r4
	ldr	r1, .L531+24
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L506:
	mov	r3, #0
	str	r3, [r7, #20]
	b	.L508
.L521:
	ldr	r1, .L531+28
	mov	r0, #1
	bl	dprint_vfmw
	str	r8, [r5, #2612]
	b	.L485
.L527:
	ldr	r1, .L531+32
	mov	r0, #1
	bl	dprint_vfmw
	b	.L495
.L526:
	ldr	r1, .L531+36
	mov	r0, #1
	bl	dprint_vfmw
	b	.L494
.L529:
	mov	r1, #5
	mov	r0, r6
	bl	BsGet
	str	r0, [r9, #896]
	b	.L505
.L499:
	mov	r2, r0
	mov	r3, #32
	ldr	r1, .L531+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L525:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	add	r9, r7, #16384
	add	r2, r0, #3
	str	r0, [r5, #2640]
	mov	r2, r2, asl #1
	uxtb	r2, r2
	strb	r2, [r9, #917]
	and	r3, r2, #252
	cmp	r3, #8
	ldr	r3, [r5, #2636]
	bne	.L492
	cmp	r2, r3
	bcs	.L493
.L492:
	ldr	r1, .L531+44
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L528:
	mov	r1, r0
	mov	r0, r6
	bl	BsGet
	cmp	r0, #1
	str	r0, [r5, #2684]
	bne	.L497
	add	r0, r7, #14848
	mov	r2, r6
	add	r1, r0, #160
	add	r0, r0, #144
	bl	AVS2_WeightQuantMatrix
	b	.L497
.L530:
	ldr	r2, [r5, #2624]
	cmp	r3, r2
	bne	.L509
	b	.L508
.L532:
	.align	2
.L531:
	.word	.LC37
	.word	.LC43
	.word	.LC39
	.word	.LC38
	.word	.LC42
	.word	.LC41
	.word	.LC44
	.word	.LC40
	.word	.LC47
	.word	.LC46
	.word	.LC48
	.word	.LC45
	UNWIND(.fnend)
	.size	AVS2_SequenceHeader, .-AVS2_SequenceHeader
	.align	2
	.global	AVS2_AllocateVHB
	.type	AVS2_AllocateVHB, %function
AVS2_AllocateVHB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r5, r0, #12288
	mov	r4, r0
	mov	r3, #0
	ldr	r0, [r5, #2608]
	str	r3, [fp, #-56]
	ldr	r1, [r5, #2616]
	cmp	r0, #1
	str	r3, [fp, #-52]
	movw	r0, #510
	str	r3, [fp, #-48]
	add	r2, r1, #15
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	mov	r2, r2, lsr #4
	ldr	r3, [r5, #2624]
	sub	ip, r2, #2
	addne	r3, r3, #31
	addeq	r3, r3, #15
	movne	r3, r3, lsr #5
	moveq	r3, r3, lsr #4
	movne	r3, r3, asl #1
	cmp	ip, r0
	bhi	.L536
	sub	ip, r3, #2
	cmp	ip, r0
	bhi	.L536
	ldr	r2, [r4, #36]
	ldr	r6, [r2, #732]
	ldr	r3, [r2, #28]
	cmp	r6, #0
	bne	.L539
	cmp	r3, #25
	beq	.L563
.L540:
	add	r3, r4, #16384
	mov	r8, #0
	ldrb	r7, [r3, #916]	@ zero_extendqisi2
	add	r7, r7, #1
	mov	r6, r7
.L545:
	ldr	r3, .L566
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #56
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #36]
	ldr	r0, [r5, #2616]
	ldr	r1, [r5, #2624]
	ldr	ip, [r3, #28]
	add	r2, r0, #15
	add	r3, r1, #15
	bic	r2, r2, #15
	cmp	ip, #24
	bic	r3, r3, #15
	str	r0, [fp, #-44]
	str	r1, [fp, #-40]
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	beq	.L551
	uxtb	r6, r6
	strb	r7, [fp, #-55]
	strb	r8, [fp, #-54]
.L556:
	sub	r1, fp, #56
	ldr	r0, [r4, #4]
	strb	r6, [fp, #-53]
	bl	FSP_ConfigInstance
	subs	r6, r0, #0
	bne	.L552
	ldr	r1, [r4, #36]
	sub	r3, fp, #36
	ldr	r0, [r4, #4]
	str	r6, [r3, #-24]!
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L564
	cmp	r0, #0
	moveq	r6, #1
	streq	r6, [r4, #24]
	beq	.L560
	ldr	r1, .L566+4
	mov	r0, r6
	bl	dprint_vfmw
	b	.L560
.L536:
	ldr	r1, .L566+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
.L560:
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L539:
	cmp	r3, #25
	bne	.L540
	ldr	r0, [r2, #692]
	ldr	r3, [r5, #2624]
	cmp	r1, r0
	ldr	ip, [r2, #696]
	bhi	.L548
	cmp	r3, ip
	bhi	.L548
	ldr	r3, [r2, #720]
	ldr	r6, [r2, #716]
	cmp	r3, #0
	add	r7, r6, #2
	bne	.L565
.L558:
	mov	r6, #1
	b	.L550
.L552:
	ldr	r1, .L566+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r6, #0
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L563:
	ldr	r0, [r2, #692]
	ldr	r3, [r5, #2624]
	cmp	r1, r0
	ldr	ip, [r2, #696]
	bhi	.L542
	cmp	r3, ip
	bhi	.L542
	ldr	r6, [r4, #24]
	cmp	r6, #1
	beq	.L560
	ldr	r1, [r2, #720]
	ldr	r3, [r2, #716]
	cmp	r1, #0
	add	r7, r3, #2
	beq	.L558
	add	r6, r3, #1
	cmp	r6, #17
	movge	r6, #17
.L550:
	ldrb	r8, [r2, #740]	@ zero_extendqisi2
	b	.L545
.L551:
	mov	r3, #0
	strb	r8, [fp, #-54]
	mov	r6, #1
	strb	r3, [fp, #-55]
	b	.L556
.L548:
	stmia	sp, {r0, ip}
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L566+16
	bl	dprint_vfmw
	mov	r6, #0
	b	.L560
.L565:
	add	r6, r6, #1
	cmp	r6, #17
	movge	r6, #17
	b	.L550
.L542:
	stmia	sp, {r0, ip}
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L566+20
	bl	dprint_vfmw
	b	.L560
.L564:
	add	r0, r4, #18432
	mov	r6, #3
	add	r0, r0, #144
	bl	ResetVoQueue
	b	.L560
.L567:
	.align	2
.L566:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC52
	.word	.LC49
	.word	.LC53
	.word	.LC51
	.word	.LC50
	UNWIND(.fnend)
	.size	AVS2_AllocateVHB, .-AVS2_AllocateVHB
	.align	2
	.global	AVS2_OutputOneFrame
	.type	AVS2_OutputOneFrame, %function
AVS2_OutputOneFrame:
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
	ldr	r6, [r1, #56]
	mov	r4, r0
	ldr	r0, [r0, #4]
	mov	r1, r6
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L574
	mov	r2, #1
	mov	r1, r6
	ldr	r0, [r4, #4]
	bl	FSP_SetDisplay
	add	r3, r4, #18432
	ldr	r0, [r4, #4]
	add	r3, r3, #144
	str	r5, [sp]
	mov	r2, r4
	mov	r1, #18
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L570
	ldr	r0, [r4, #4]
	mov	r2, #0
	mov	r1, r6
	bl	FSP_SetDisplay
	mov	r2, r6
	ldr	r1, .L575
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
.L570:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L574:
	movw	r2, #2277
	ldr	r1, .L575+4
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L576:
	.align	2
.L575:
	.word	.LC55
	.word	.LC54
	UNWIND(.fnend)
	.size	AVS2_OutputOneFrame, .-AVS2_OutputOneFrame
	.align	2
	.global	AVS2_DisplayFrameInPOI
	.type	AVS2_DisplayFrameInPOI, %function
AVS2_DisplayFrameInPOI:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r2, r0, #10944
	add	r3, r0, #18944
	mov	r7, #0
	add	r3, r3, #154
	mov	r4, r0
	ldrsh	r0, [r2, #6]
	mov	r2, r7
.L579:
	ldrsh	r1, [r3]
	cmp	r1, r0
	bgt	.L578
	ldrb	r1, [r3, #-6]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L578
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	add	lr, r7, #1
	sub	ip, fp, #44
	cmp	r1, #0
	add	ip, ip, r7
	uxtbne	r7, lr
	strneb	r2, [ip, #-16]
.L578:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	bne	.L579
	cmp	r7, #0
	beq	.L577
	sub	r3, fp, #60
	mov	r8, #0
	add	r6, r3, r7
	mov	r9, r8
	mov	r5, #104
.L581:
	cmp	r7, #0
	ble	.L584
	sub	r2, fp, #60
	movw	ip, #32767
.L583:
	ldrb	r1, [r2], #1	@ zero_extendqisi2
	mla	r3, r5, r1, r4
	add	r3, r3, #18944
	add	r3, r3, #144
	ldrb	r0, [r3, #4]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L582
	ldrsh	r3, [r3, #2]
	cmp	r3, ip
	movle	r9, r1
	movle	ip, r3
.L582:
	cmp	r2, r6
	bne	.L583
	movw	r3, #32767
	cmp	ip, r3
	beq	.L584
	mul	r1, r5, r9
	mov	r3, #1
	mov	r0, r4
	add	r10, r4, r1
	add	r1, r1, #18944
	add	r10, r10, #18944
	add	r1, r1, #144
	add	r1, r4, r1
	strb	r3, [r10, #148]
	bl	AVS2_OutputOneFrame
	ldrsh	r2, [r10, #146]
	ldr	r1, .L593
	mov	r0, #13
	bl	dprint_vfmw
.L584:
	add	r8, r8, #1
	uxtb	r3, r8
	cmp	r3, r7
	bcc	.L581
.L577:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L594:
	.align	2
.L593:
	.word	.LC56
	UNWIND(.fnend)
	.size	AVS2_DisplayFrameInPOI, .-AVS2_DisplayFrameInPOI
	.align	2
	.global	AVS2_UpdateSceneBuf
	.type	AVS2_UpdateSceneBuf, %function
AVS2_UpdateSceneBuf:
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
	add	r3, r0, #12288
	ldr	r3, [r3, #1508]
	sub	r3, r3, #5
	cmp	r3, #1
	ldmhifd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2_UpdateSceneBuf.part.7
	UNWIND(.fnend)
	.size	AVS2_UpdateSceneBuf, .-AVS2_UpdateSceneBuf
	.align	2
	.global	AVS2_UpdateRefBuf
	.type	AVS2_UpdateRefBuf, %function
AVS2_UpdateRefBuf:
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
	add	r8, r0, #12288
	mov	r10, r0
	ldr	r1, .L611
	mov	r0, #13
	ldr	r2, [r8, #2392]
	bl	dprint_vfmw
	ldr	r3, [r8, #2392]
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	add	r6, r10, #14656
	add	r7, r10, #18944
	add	r6, r6, #24
	add	r7, r7, #144
	add	r9, r10, #8192
	mov	r5, #0
.L603:
	add	r3, r9, #2752
	ldr	r4, [r6, #4]!
	add	r3, r3, #4
	ldr	r1, .L611+4
	mov	r2, r5
	mov	r0, #13
	ldrh	r3, [r3, #2]
	rsb	r4, r4, r3
	sxth	r4, r4
	mov	r3, r4
	bl	dprint_vfmw
	mov	r3, r7
	mov	r1, #0
	b	.L602
.L599:
	add	r1, r1, #1
	add	r3, r3, #104
	cmp	r1, #16
	beq	.L601
.L602:
	ldrsh	r2, [r3]
	cmp	r2, r4
	bne	.L599
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	and	r0, r2, #2
	cmp	r2, #0
	uxtb	r0, r0
	beq	.L599
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	sub	r2, r2, #5
	cmp	r2, #1
	bhi	.L600
	cmp	r0, #0
	strb	r0, [r3, #6]
	bne	.L599
	mov	r3, #104
	mov	r2, r0
	mla	r3, r3, r1, r10
.L610:
	add	r1, r3, #18944
	strb	r0, [r1, #149]
	ldr	r1, [r1, #200]
	ldr	r0, [r10, #4]
	bl	FSP_SetRef
.L601:
	ldr	r3, [r8, #2392]
	add	r5, r5, #1
	cmp	r5, r3
	bcc	.L603
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L600:
	mov	r3, #104
	mov	r0, #0
	mla	r3, r3, r1, r10
	mov	r2, r0
	b	.L610
.L612:
	.align	2
.L611:
	.word	.LC57
	.word	.LC58
	UNWIND(.fnend)
	.size	AVS2_UpdateRefBuf, .-AVS2_UpdateRefBuf
	.align	2
	.global	AVS2_RefreshBuf
	.type	AVS2_RefreshBuf, %function
AVS2_RefreshBuf:
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
	add	r5, r0, #18944
	mov	r6, r0
	add	r5, r5, #200
	mov	r4, #0
	mov	r7, #104
	b	.L617
.L615:
	cmp	r4, #16
	add	r5, r5, #104
	beq	.L619
.L617:
	mla	r3, r7, r4, r6
	ldrb	r2, [r5, #-50]	@ zero_extendqisi2
	add	r4, r4, #1
	cmp	r2, #0
	add	r3, r3, #18944
	add	r3, r3, #144
	beq	.L615
	ldrh	r3, [r3, #4]
	cmp	r3, #1
	bne	.L615
	and	r2, r2, #2
	uxtb	r2, r2
	strb	r2, [r5, #-50]
	cmp	r2, #0
	bne	.L615
	ldr	r1, [r5]
	add	r5, r5, #104
	ldr	r0, [r6, #4]
	bl	FSP_SetRef
	cmp	r4, #16
	bne	.L617
.L619:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_RefreshBuf, .-AVS2_RefreshBuf
	.align	2
	.global	AVS2_SetPicInfo
	.type	AVS2_SetPicInfo, %function
AVS2_SetPicInfo:
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
	add	r4, r0, #12288
	add	r1, r0, #10944
	add	r6, r0, #8192
	movw	lr, #2756
	ldr	r3, [r4, #1524]
	uxth	r5, r3
	strh	r5, [r1, #6]	@ movhi
	ldr	r2, [r4, #1532]
	ldr	ip, [r4, #1300]
	add	r3, r2, r3
	rsb	r3, ip, r3
	strh	r3, [r1, #8]	@ movhi
	ldr	r3, [r0, #28]
	cmp	r3, #0
	ble	.L622
	ldrsh	r2, [r6, lr]
	sxth	r3, r5
	cmp	r2, r3
	ble	.L622
	add	r2, r0, #18944
	ldr	lr, [r6, #3016]
	add	r0, r0, #20736
	mov	r1, r2
	add	r0, r0, #16
	add	r2, r2, #144
	add	r1, r1, #146
.L624:
	ldrh	r3, [r1, #-2]
	cmp	lr, #0
	add	r1, r1, #104
	sub	r3, r3, #256
	strh	r3, [r1, #-106]	@ movhi
	ldrh	r3, [r2, #2]
	ldrh	ip, [r2, #10]
	sub	r3, r3, #256
	strh	r3, [r2, #2]	@ movhi
	sub	ip, ip, #256
	strh	ip, [r2, #10]	@ movhi
	sxth	r3, r3
	mov	r3, r3, asl #1
	strh	r3, [r2, #8]	@ movhi
	bne	.L623
	ldr	ip, [r4, #1564]
	add	r3, r3, #1
	cmp	ip, #0
	streqh	r3, [r2, #8]	@ movhi
.L623:
	add	r2, r2, #104
	cmp	r2, r0
	bne	.L624
.L622:
	movw	r3, #2756
	strh	r5, [r6, r3]	@ movhi
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_SetPicInfo, .-AVS2_SetPicInfo
	.align	2
	.global	AVS2_VarifyDecMode
	.type	AVS2_VarifyDecMode, %function
AVS2_VarifyDecMode:
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
	ldr	r3, [r0, #36]
	mov	r5, r0
	ldr	r4, [r3, #8]
	cmp	r4, #2
	beq	.L629
	cmp	r4, #3
	moveq	r6, #0
	beq	.L628
	cmp	r4, #1
	movne	r6, #1
	beq	.L645
.L628:
	str	r4, [r5, #32]
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L645:
	add	r6, r0, #12288
	ldr	r3, [r6, #1508]
	cmp	r3, #2
	beq	.L646
.L636:
	mov	r6, r4
.L632:
	ldr	r3, [r5, #32]
	cmp	r3, #1
	beq	.L628
	mov	r0, r5
	bl	AVS2_ClearDpb
	b	.L628
.L629:
	add	r3, r0, #12288
	ldr	r6, [r3, #1512]
	adds	r6, r6, #0
	movne	r6, #1
	b	.L628
.L646:
	ldr	r3, [r6, #2356]
	cmp	r3, #0
	bne	.L636
	bl	AVS2_DisplayFrameInPOI
	ldr	r3, [r6, #2392]
	cmp	r3, #0
	bne	.L647
.L633:
	mov	r0, r5
	mov	r6, #0
	bl	AVS2_RefreshBuf
	b	.L632
.L647:
	mov	r0, r5
	bl	AVS2_UpdateRefBuf
	b	.L633
	UNWIND(.fnend)
	.size	AVS2_VarifyDecMode, .-AVS2_VarifyDecMode
	.align	2
	.global	AVS2_VarifyFrame
	.type	AVS2_VarifyFrame, %function
AVS2_VarifyFrame:
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
	UNWIND(.pad #40)
	sub	sp, sp, #40
	add	r3, r0, #18944
	add	r3, r3, #150
	mov	r2, #0
	b	.L652
.L649:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	beq	.L662
.L652:
	ldrb	ip, [r3]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L649
	ldr	r4, [r1, #56]
	ldr	lr, [r3, #50]
	cmp	r4, lr
	beq	.L650
	ldr	r5, [r1, #100]
	ldr	lr, [r3, #54]
	cmp	r5, lr
	beq	.L654
	ldr	r5, [r1, #80]
	ldr	lr, [r3, #74]
	cmp	r5, lr
	bne	.L649
	ldrb	lr, [r3, #-1]	@ zero_extendqisi2
	cmp	lr, #1
	beq	.L656
	tst	ip, #2
	beq	.L649
.L656:
	mov	lr, r4
	b	.L651
.L662:
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L654:
	mov	lr, r4
.L650:
	ldr	r5, [r1, #80]
.L651:
	mov	r3, #104
	movw	ip, #19168
	mla	r2, r3, r2, r0
	ldrsh	r3, [r1]
	movw	r6, #19144
	movw	r4, #19088
	add	r0, r2, #18944
	ldr	r7, [r2, ip]
	mov	ip, r0
	add	ip, ip, #144
	str	r7, [sp, #36]
	ldr	r7, [r0, #204]
	mov	r0, #1
	str	r7, [sp, #32]
	ldr	r6, [r2, r6]
	str	r6, [sp, #28]
	ldrsh	r6, [r2, r4]
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	ldr	r4, [r1, #60]
	str	r6, [sp, #24]
	ldrb	r6, [ip, #5]	@ zero_extendqisi2
	ldr	r1, .L663
	str	r6, [sp, #20]
	ldrb	r6, [ip, #6]	@ zero_extendqisi2
	str	r6, [sp, #16]
	ldrb	ip, [ip, #7]	@ zero_extendqisi2
	str	r5, [sp, #8]
	str	lr, [sp]
	str	ip, [sp, #12]
	str	r4, [sp, #4]
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L664:
	.align	2
.L663:
	.word	.LC59
	UNWIND(.fnend)
	.size	AVS2_VarifyFrame, .-AVS2_VarifyFrame
	.align	2
	.global	AVS2_ReleaseFrameBuf
	.type	AVS2_ReleaseFrameBuf, %function
AVS2_ReleaseFrameBuf:
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
	add	r4, r0, #8192
	ldr	r3, [r4, #2928]
	cmp	r3, #0
	beq	.L666
	ldr	r1, [r3, #56]
	mov	r2, #0
	ldr	r0, [r0, #4]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2928]
	mov	r2, #0
	strb	r2, [r3, #6]
.L666:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_ReleaseFrameBuf, .-AVS2_ReleaseFrameBuf
	.align	2
	.global	AVS2_SetupFrameBuf
	.type	AVS2_SetupFrameBuf, %function
AVS2_SetupFrameBuf:
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
	add	r7, r0, #12288
	mov	r6, r0
	ldr	r3, [r7, #1508]
	cmp	r3, #6
	beq	.L671
.L675:
	add	r3, r6, #16384
	ldrb	r3, [r3, #2710]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r2, r6, #18944
	movne	r3, #1
	addne	r2, r2, #254
	beq	.L672
.L680:
	ldrb	r1, [r2]	@ zero_extendqisi2
	add	r2, r2, #104
	cmp	r1, #0
	beq	.L672
	add	r3, r3, #1
	cmp	r3, #16
	bne	.L680
.L679:
	ldr	r2, .L709
	mov	r0, #1
	ldr	r1, .L709+4
	mov	r5, #0
	bl	dprint_vfmw
.L681:
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L671:
	add	r3, r0, #18944
	add	r0, r0, #10944
	add	r3, r3, #150
	add	r0, r0, #4
	add	lr, r6, #8192
	mov	r2, #0
	b	.L677
.L674:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	beq	.L675
.L677:
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L674
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #6
	bne	.L674
	ldrsh	ip, [r3, #-6]
	mov	r8, lr
	ldrsh	r1, [r0, #2]
	cmp	ip, r1
	bne	.L674
	mov	r3, #104
	movw	r1, #19144
	mul	r2, r3, r2
	add	r4, r2, #18944
	add	r2, r6, r2
	add	r4, r4, #144
	add	r4, r6, r4
	str	r4, [lr, #2928]
	cmp	r4, #0
	ldr	r9, [r2, r1]
	bne	.L676
	b	.L675
.L672:
	mov	r4, #104
	add	r8, r6, #8192
	mla	r3, r4, r3, r6
	mov	r1, #1
	add	r4, r3, #18944
	add	r4, r4, #144
	str	r4, [r8, #2928]
	ldr	r0, [r6, #4]
	bl	FSP_NewLogicFs
	cmp	r4, #0
	mov	r9, r0
	beq	.L679
.L676:
	mov	r1, r9
	ldr	r0, [r6, #4]
	bl	FSP_GetLogicFs
	mvn	r5, r9
	mov	r5, r5, lsr #31
	cmp	r0, #0
	moveq	r5, #0
	cmp	r5, #0
	beq	.L682
	add	r2, r6, #14784
	add	r1, r6, #13568
	add	r2, r2, #44
	add	r1, r1, #48
	bl	AVS2_ConvertHDRInfo
	mov	r1, r9
	ldr	r0, [r6, #4]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L707
	str	r9, [r4, #56]
	mov	r1, r9
	ldr	r3, [r5, #112]
	add	r9, r5, #608
	str	r3, [r4, #88]
	ldr	r3, [r5, #116]
	str	r3, [r4, #92]
	ldr	r3, [r5, #140]
	str	r3, [r4, #96]
	ldr	r2, [r5, #36]
	ldr	r3, [r5, #40]
	rsb	r3, r2, r3
	str	r3, [r4, #84]
	ldr	r3, [r5, #36]
	str	r3, [r4, #60]
	ldr	r3, [r5, #40]
	str	r3, [r4, #64]
	ldr	r0, [r6, #4]
	bl	FSP_GetPmvAddr
	add	ip, r5, #592
	add	r1, r8, #2752
	mov	lr, #0
	add	r1, r1, #4
	str	r0, [r4, #80]
	ldr	r0, [r5, #212]
	str	r0, [r4, #100]
	ldr	r0, [r5, #144]
	str	r0, [r4, #68]
	ldr	r10, [r5, #36]
	ldr	r0, [r5, #44]
	rsb	r0, r10, r0
	str	r0, [r4, #72]
	ldr	r0, [r5, #48]
	ldr	r10, [r5, #44]
	rsb	r0, r10, r0
	str	r0, [r4, #76]
	ldr	r0, [r6, #28]
	str	r0, [r5, #176]
	ldrb	r0, [r7, #1321]	@ zero_extendqisi2
	str	r0, [r5, #168]
	ldrb	r0, [r7, #1321]	@ zero_extendqisi2
	str	r0, [r5, #172]
	ldr	r0, [r6, #36]
	ldrd	r2, [r0, #64]
	strd	r2, [ip, #-8]
	ldr	r0, [r6, #36]
	ldrd	r2, [r0, #80]
	strd	r2, [ip]
	ldr	r0, [r6, #36]
	ldrd	r2, [r0, #96]
	strd	r2, [r9, #-8]
	mvn	r2, #0
	ldr	r0, [r6, #36]
	mvn	r3, #0
	ldr	r0, [r0, #112]
	str	r0, [r5]
	ldr	r0, [r6, #36]
	ldr	r0, [r0, #116]
	str	r0, [r5, #4]
	ldr	r0, [r6, #36]
	ldr	r0, [r0, #120]
	str	r0, [r5, #8]
	ldr	r0, [r6, #36]
	ldr	r0, [r0, #136]
	str	r0, [r5, #12]
	ldr	r0, [r7, #1552]
	clz	r0, r0
	mov	r0, r0, lsr #5
	str	r0, [r5, #52]
	ldr	r0, [r6, #36]
	strd	r2, [r0, #64]
	ldrh	r3, [r1, #2]
	strh	r3, [r4]	@ movhi
	ldrh	r3, [r1, #4]
	strh	r3, [r4, #2]	@ movhi
	sxth	r3, r3
	ldr	r2, [r7, #1508]
	mov	r3, r3, asl #1
	strb	r2, [r4, #7]
	ldr	r2, [r7, #2356]
	strb	lr, [r4, #4]
	strb	r2, [r4, #5]
	ldrh	r1, [r1, #2]
	ldr	r2, [r7, #1532]
	strh	r3, [r4, #8]	@ movhi
	add	r2, r2, r1
	strh	r2, [r4, #10]	@ movhi
	ldr	r2, [r8, #3016]
	cmp	r2, lr
	ldr	r2, [r7, #1564]
	bne	.L686
	cmp	r2, #0
	addeq	r3, r3, #1
	streqh	r3, [r4, #8]	@ movhi
	ldreq	r2, [r7, #1564]
.L686:
	strb	r2, [r4, #12]
	mov	r1, r4
	ldr	r3, [r7, #1552]
	mov	r2, #0
	mov	r0, r6
	strb	r3, [r4, #13]
	ldr	r3, [r7, #1556]
	strb	r2, [r4, #6]
	strb	r3, [r4, #14]
	bl	AVS2_VarifyFrame
	subs	r5, r0, #0
	beq	.L708
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #4
	bhi	.L688
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	mov	r5, #1
	strb	r5, [r4, #6]
	cmp	r3, #0
	beq	.L681
.L689:
	mov	r2, #1
	ldr	r0, [r6, #4]
	mov	r5, r2
	ldr	r1, [r4, #56]
	bl	FSP_SetRef
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L682:
	ldr	r2, .L709
	mov	r0, #1
	ldr	r1, .L709+8
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L688:
	cmp	r3, #6
	moveq	r3, #2
	movne	r3, #3
	strb	r3, [r4, #6]
	b	.L689
.L708:
	ldrsh	r2, [r4]
	mov	r0, #1
	ldr	r1, .L709+12
	bl	dprint_vfmw
	mov	r0, r6
	bl	AVS2_ReleaseFrameBuf
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L707:
	ldr	r2, .L709
	mov	r0, #1
	ldr	r1, .L709+16
	bl	dprint_vfmw
	b	.L681
.L710:
	.align	2
.L709:
	.word	.LANCHOR0+452
	.word	.LC60
	.word	.LC61
	.word	.LC63
	.word	.LC62
	UNWIND(.fnend)
	.size	AVS2_SetupFrameBuf, .-AVS2_SetupFrameBuf
	.align	2
	.global	AVS2_SetupRefFrame
	.type	AVS2_SetupRefFrame, %function
AVS2_SetupRefFrame:
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
	add	r3, r0, #11072
	add	r2, r0, #11136
	add	r3, r3, #48
	add	r2, r2, #44
	mov	r7, r0
	mov	r1, #0
.L712:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L712
	add	r6, r7, #12288
	ldr	r2, [r6, #1508]
	cmp	r2, #4
	beq	.L749
	ldr	r3, [r6, #2360]
	sub	r1, r3, #1
	cmp	r1, #6
	bhi	.L717
	cmp	r3, #0
	beq	.L718
	add	r5, r7, #14592
	add	r9, r7, #18944
	mov	r10, #0
	add	r5, r5, #56
	add	r9, r9, #150
	add	r8, r7, #8192
	mov	r4, r10
.L723:
	add	r2, r8, #2752
	ldr	r3, [r5, #4]!
	add	r2, r2, #4
	ldrh	r2, [r2, #2]
	rsb	r3, r3, r2
	sxth	r2, r2
	sxth	r3, r3
	cmp	r2, r3
	beq	.L719
	mov	r2, r9
	mov	r1, #0
	b	.L722
.L720:
	add	r1, r1, #1
	add	r2, r2, #104
	cmp	r1, #16
	beq	.L721
.L722:
	ldrb	r0, [r2]	@ zero_extendqisi2
	tst	r0, #1
	beq	.L720
	ldrsh	r0, [r2, #-6]
	cmp	r0, r3
	bne	.L720
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	cmp	r0, #1
	bne	.L720
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #6
	beq	.L720
	mov	r2, #104
	cmp	r1, #15
	mla	r2, r2, r1, r7
	add	r1, r8, r10, lsl #2
	add	r10, r10, #1
	add	r2, r2, #18944
	add	r2, r2, #144
	str	r2, [r1, #2932]
	bgt	.L721
.L719:
	ldr	r3, [r6, #2360]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L723
.L751:
	cmp	r10, r3
	bcc	.L724
	ldr	r2, [r6, #1508]
.L718:
	bic	r2, r2, #2
	cmp	r2, #1
	bne	.L726
	ldr	r2, [r6, #1500]
	cmp	r2, #1
	beq	.L750
.L726:
	mov	r0, #1
.L715:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L721:
	add	r2, r8, #2752
	ldr	r1, .L753
	add	r2, r2, #4
	mov	r0, #1
	add	r4, r4, #1
	ldrsh	r2, [r2, #2]
	bl	dprint_vfmw
	ldr	r3, [r6, #2360]
	cmp	r4, r3
	bcc	.L723
	b	.L751
.L749:
	add	r3, r7, #18944
	mov	r2, #0
	add	r3, r3, #150
.L716:
	ldrb	r1, [r3]	@ zero_extendqisi2
	tst	r1, #2
	beq	.L714
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	sub	r1, r1, #5
	cmp	r1, #1
	bls	.L752
.L714:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	bne	.L716
	ldr	r1, .L753+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L724:
	mov	r2, r10
	ldr	r1, .L753+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L750:
	add	r3, r7, r3, lsl #2
	add	r2, r7, #18944
	add	r3, r3, #8320
	add	r7, r7, #20736
	add	r3, r3, #44
	add	r2, r2, #144
	add	r7, r7, #16
.L728:
	ldrb	r1, [r2, #6]	@ zero_extendqisi2
	tst	r1, #2
	beq	.L727
	ldrb	r1, [r2, #7]	@ zero_extendqisi2
	sub	r1, r1, #5
	cmp	r1, #1
	strls	r2, [r3, #2756]
.L727:
	add	r2, r2, #104
	cmp	r2, r7
	bne	.L728
	b	.L726
.L717:
	mov	r1, #7
	ldr	r2, .L753+12
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L753+16
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L752:
	mov	r3, #104
	add	r1, r7, #8192
	mla	r3, r3, r2, r7
	mov	r0, #1
	add	r3, r3, #18944
	add	r3, r3, #144
	str	r3, [r1, #2932]
	b	.L715
.L754:
	.align	2
.L753:
	.word	.LC65
	.word	.LC64
	.word	.LC66
	.word	.LANCHOR0+472
	.word	.LC67
	UNWIND(.fnend)
	.size	AVS2_SetupRefFrame, .-AVS2_SetupRefFrame
	.align	2
	.global	AVS2_SetupHalConfig
	.type	AVS2_SetupHalConfig, %function
AVS2_SetupHalConfig:
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
	ldr	r2, [r0, #36]
	add	r6, r0, #8192
	mov	r4, r0
	add	r3, r0, #11136
	movw	ip, #2412
	ldr	r1, [r2, #600]
	add	r3, r3, #56
	ldr	r7, [r6, #2932]
	movw	r0, #2414
	add	r5, r4, #12288
	strb	r1, [r4, #590]
	ldr	r1, [r2, #632]
	strb	r1, [r4, #592]
	ldr	r2, [r2, #652]
	strb	r2, [r4, #589]
	ldr	r1, [r6, #2928]
	ldr	r2, [r1, #60]
	str	r2, [r4, #680]
	ldr	r2, [r1, #88]
	str	r2, [r4, #848]
	ldr	r2, [r1, #92]
	str	r2, [r4, #852]
	ldr	r2, [r1, #84]
	str	r2, [r4, #856]
	ldr	r2, [r1, #96]
	str	r2, [r4, #860]
	ldr	r2, [r1, #100]
	str	r2, [r4, #684]
	ldr	r2, [r1, #68]
	str	r2, [r4, #864]
	ldr	r2, [r1, #72]
	str	r2, [r4, #868]
	ldr	r2, [r1, #76]
	str	r2, [r4, #872]
	ldr	r2, [r6, #3020]
	str	r2, [r4, #688]
	ldr	r2, [r6, #3028]
	str	r2, [r4, #692]
	ldrh	r2, [r3, ip]
	str	r2, [r4, #696]
	ldrh	r3, [r3, r0]
	str	r3, [r4, #700]
	ldr	r3, [r5, #1564]
	str	r3, [r4, #708]
	ldrb	r2, [r5, #1321]	@ zero_extendqisi2
	strb	r2, [r4, #588]
	ldr	r2, [r5, #1572]
	str	r2, [r4, #712]
	ldr	r2, [r5, #1568]
	str	r2, [r4, #716]
	ldr	r2, [r5, #1508]
	str	r2, [r4, #720]
	ldr	r2, [r6, #3016]
	cmp	r2, #1
	movne	r3, #0
	strne	r3, [r4, #724]
	beq	.L779
.L758:
	ldr	r3, [r5, #1304]
	str	r3, [r4, #728]
	ldr	r3, [r6, #3192]
	str	r3, [r4, #732]
	ldr	r3, [r6, #3036]
	str	r3, [r4, #736]
	ldr	r3, [r6, #3196]
	str	r3, [r4, #740]
	ldr	r3, [r6, #3096]
	str	r3, [r4, #744]
	ldr	r3, [r6, #3104]
	str	r3, [r4, #748]
	ldr	r3, [r6, #3100]
	str	r3, [r4, #752]
	ldrb	r3, [r5, #1376]	@ zero_extendqisi2
	str	r3, [r4, #756]
	ldr	r3, [r6, #3188]
	str	r3, [r4, #760]
	ldr	r2, [r5, #1632]
	ldr	r3, [r5, #1636]
	ldr	r0, [r5, #1628]
	mov	r2, r2, asl #1
	orr	r3, r2, r3, asl #2
	orr	r3, r3, r0
	str	r3, [r4, #764]
	ldr	r3, [r6, #3204]
	str	r3, [r4, #768]
	ldr	r3, [r6, #3208]
	str	r3, [r4, #772]
	ldr	r3, [r6, #3080]
	str	r3, [r4, #704]
	ldr	r3, [r6, #3200]
	str	r3, [r4, #776]
	ldr	r3, [r6, #3084]
	str	r3, [r4, #780]
	ldr	r3, [r5, #1600]
	str	r3, [r4, #796]
	ldr	r3, [r5, #1616]
	str	r3, [r4, #784]
	ldr	r3, [r5, #1612]
	str	r3, [r4, #788]
	ldr	r3, [r5, #1608]
	str	r3, [r4, #792]
	ldr	r3, [r5, #1596]
	str	r3, [r4, #800]
	ldr	r3, [r5, #1592]
	str	r3, [r4, #804]
	ldr	r3, [r5, #1588]
	str	r3, [r4, #808]
	ldr	r3, [r5, #1584]
	str	r3, [r4, #812]
	ldrb	r3, [r1, #12]	@ zero_extendqisi2
	str	r3, [r4, #816]
	ldrb	r3, [r1, #13]	@ zero_extendqisi2
	str	r3, [r4, #820]
	ldrb	r3, [r1, #14]	@ zero_extendqisi2
	str	r3, [r4, #824]
	ldr	r0, [r5, #1512]
	cmp	r0, #0
	bne	.L759
	add	ip, r4, #11072
	mov	r3, r4
	add	ip, ip, #52
	mov	r2, r7
	b	.L762
.L780:
	ldr	r2, [ip, #4]!
.L762:
	cmp	r2, #0
	add	r0, r0, #1
	beq	.L760
	ldrb	lr, [r2, #12]	@ zero_extendqisi2
	str	lr, [r3, #904]
	ldrb	lr, [r2, #13]	@ zero_extendqisi2
	str	lr, [r3, #932]
	ldrb	lr, [r2, #14]	@ zero_extendqisi2
	str	lr, [r3, #960]
	ldr	r2, [r2, #60]
	str	r2, [r3, #988]
.L760:
	cmp	r0, #7
	add	r3, r3, #4
	bne	.L780
.L761:
	ldr	r3, [r1, #80]
	cmp	r7, #0
	ldr	r8, .L782
	add	r9, r4, #588
	add	r1, r4, #13952
	streq	r7, [r4, #832]
	str	r3, [r4, #828]
	add	r1, r1, #44
	ldrne	r3, [r7, #80]
	mov	r2, #576
	add	r0, r9, #492
	add	r10, r4, #11136
	add	r10, r10, #56
	strne	r3, [r4, #832]
	ldr	r3, [r8, #52]
	blx	r3
	add	r1, r4, #14528
	add	r0, r4, #1648
	ldr	r3, [r8, #52]
	add	r1, r1, #44
	add	r0, r0, #8
	mov	r2, #72
	blx	r3
	ldr	r3, [r5, #1512]
	cmp	r3, #0
	beq	.L781
	ldrb	r3, [r5, #1377]	@ zero_extendqisi2
	str	r3, [r4, #836]
	ldr	r3, [r6, #3212]
	str	r3, [r4, #840]
	ldr	r3, [r5, #1500]
	str	r3, [r4, #844]
.L766:
	add	r0, r4, #876
	ldr	r3, [r8, #48]
	mov	r2, #28
	mov	r1, #0
	blx	r3
.L767:
	add	r1, r10, #2480
	ldr	r3, [r8, #52]
	add	r1, r1, #6
	mov	r2, #16
	add	r0, r9, #5
	blx	r3
	add	r1, r10, #2496
	add	r1, r1, #6
	ldr	r3, [r8, #52]
	add	r0, r9, #21
	mov	r2, #64
	blx	r3
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L759:
	ldrb	r3, [r1, #12]	@ zero_extendqisi2
	str	r3, [r4, #904]
	ldrb	r3, [r1, #13]	@ zero_extendqisi2
	str	r3, [r4, #932]
	ldrb	r3, [r1, #14]	@ zero_extendqisi2
	str	r3, [r4, #960]
	ldr	r3, [r1, #60]
	str	r3, [r4, #988]
	b	.L761
.L781:
	str	r3, [fp, #-52]
	add	r3, r4, #10944
	add	r3, r3, #4
	mov	r2, #14
	add	r1, r3, #12
	ldr	ip, [r8, #52]
	add	r0, r4, #1016
	str	r3, [fp, #-48]
	blx	ip
	ldr	r3, [fp, #-48]
	mov	r2, #14
	ldr	ip, [r8, #52]
	add	r1, r3, #40
	add	r0, r9, #444
	blx	ip
	ldr	r3, [fp, #-48]
	ldr	ip, [r8, #52]
	mov	r2, #14
	add	r1, r3, #26
	add	r0, r9, #460
	blx	ip
	ldr	r3, [fp, #-48]
	mov	r2, #14
	add	r0, r9, #476
	add	r1, r3, #54
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r3, [fp, #-52]
	movw	r2, #474
	movw	r0, #442
	movw	r1, #458
	movw	ip, #490
	strh	r3, [r9, r0]	@ movhi
	strh	r3, [r9, r1]	@ movhi
	strh	r3, [r9, r2]	@ movhi
	strh	r3, [r9, ip]	@ movhi
	ldrb	r2, [r5, #1377]	@ zero_extendqisi2
	ldr	r3, [r5, #1512]
	str	r2, [r4, #836]
	cmp	r3, #0
	ldr	r3, [r6, #3212]
	str	r3, [r4, #840]
	ldr	r3, [r5, #1500]
	str	r3, [r4, #844]
	bne	.L766
	ldrb	r3, [r7, #46]	@ zero_extendqisi2
	str	r3, [r4, #876]
	ldrb	r3, [r7, #47]	@ zero_extendqisi2
	str	r3, [r4, #880]
	ldrb	r3, [r7, #48]	@ zero_extendqisi2
	str	r3, [r4, #884]
	ldrb	r3, [r7, #49]	@ zero_extendqisi2
	str	r3, [r4, #888]
	ldrb	r3, [r7, #50]	@ zero_extendqisi2
	str	r3, [r4, #892]
	ldrb	r3, [r7, #51]	@ zero_extendqisi2
	str	r3, [r4, #896]
	ldrb	r3, [r7, #52]	@ zero_extendqisi2
	str	r3, [r4, #900]
	b	.L767
.L779:
	cmp	r3, #1
	movne	r3, #2
	str	r3, [r4, #724]
	b	.L758
.L783:
	.align	2
.L782:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	AVS2_SetupHalConfig, .-AVS2_SetupHalConfig
	.global	__aeabi_idiv
	.align	2
	.global	AVS2_CalDistance
	.type	AVS2_CalDistance, %function
AVS2_CalDistance:
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
	add	r3, r0, #8192
	str	r3, [fp, #-56]
	mov	r2, r3
	ldr	r3, [r3, #2932]
	str	r0, [fp, #-52]
	cmp	r3, #0
	ldr	r10, [r2, #2928]
	moveq	r3, r0
	addeq	r3, r3, #12288
	ldreqb	r3, [r3, #1376]	@ zero_extendqisi2
	beq	.L786
	ldr	r3, [fp, #-52]
	add	r2, r3, #12288
	ldrb	r3, [r2, #1376]	@ zero_extendqisi2
	sub	r1, r3, #1
	cmp	r1, #6
	bhi	.L786
	add	r3, r10, #16
	add	r6, r10, #30
	mov	lr, #1
	mov	ip, #16384
	mov	r1, r3
	mov	r0, r6
.L789:
	strh	lr, [r1, #2]!	@ movhi
	cmp	r1, r6
	strh	ip, [r0, #2]!	@ movhi
	bne	.L789
	ldrb	r1, [r2, #1376]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L790
	ldr	r1, [fp, #-52]
	add	r9, r10, #45
	add	r4, r10, #18
	mov	r8, r6
	add	r7, r1, #11072
	ldrsh	r1, [r10, #2]
	add	r7, r7, #48
	str	r6, [fp, #-64]
	mov	r5, #0
	mov	r6, r10
	mov	r10, r2
	str	r1, [fp, #-48]
	str	r3, [fp, #-60]
.L795:
	ldr	r1, [r7, #4]!
	ldr	r3, [fp, #-48]
	ldrb	r0, [r1, #12]	@ zero_extendqisi2
	strb	r0, [r9, #1]!
	ldrsh	r0, [r1, #2]
	cmp	r0, r3
	ldrltsh	r0, [r1, #8]
	ldrgesh	r1, [r1, #8]
	ldrltsh	r1, [r6, #8]
	ldrgesh	r0, [r6, #8]
	rsb	r0, r0, r1
	add	r0, r0, #512
	mov	r1, r0, asr #31
	mov	r1, r1, lsr #23
	add	r0, r0, r1
	ubfx	r0, r0, #0, #9
	rsb	r1, r1, r0
	mov	r0, #16384
	mov	ip, r0
	uxth	r1, r1
	strh	r1, [r4]	@ movhi
	cmp	r1, #0
	sxth	r1, r1
	moveq	r3, #1	@ movhi
	streqh	r3, [r4]	@ movhi
	beq	.L794
	bl	__aeabi_idiv
	uxth	ip, r0
.L794:
	strh	ip, [r8, #2]!	@ movhi
	add	r5, r5, #1
	ldrb	r1, [r10, #1376]	@ zero_extendqisi2
	add	r4, r4, #2
	cmp	r1, r5
	bhi	.L795
	ldr	r0, [r10, #1500]
	ldr	r2, [fp, #-56]
	cmp	r0, #1
	ldr	r3, [fp, #-60]
	ldr	r6, [fp, #-64]
	ldr	r2, [r2, #2932]
	beq	.L802
.L803:
	ldr	r1, [fp, #-52]
	add	r5, r2, #16
	add	r4, r1, #10944
	add	r1, r2, #30
	mov	r2, #7
	mov	lr, r4
	mov	ip, r4
	mov	r0, r4
	add	lr, lr, #42
	add	r4, r4, #14
	add	ip, ip, #28
	add	r0, r0, #56
.L800:
	ldrh	r7, [r3, #2]!
	subs	r2, r2, #1
	strh	r7, [r4, #2]!	@ movhi
	ldrh	r7, [r5, #2]!
	strh	r7, [lr, #2]!	@ movhi
	ldrh	r7, [r6, #2]!
	strh	r7, [ip, #2]!	@ movhi
	ldrh	r7, [r1, #2]!
	strh	r7, [r0, #2]!	@ movhi
	bne	.L800
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L786:
	mov	r1, #7
	ldr	r2, .L817
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L817+4
	bl	dprint_vfmw
.L784:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L802:
	cmp	r1, #1
	beq	.L816
.L797:
	ldr	r0, [fp, #-52]
	add	r7, r2, #16
	add	r2, r2, #30
	add	r5, r0, #10944
	mov	r0, #7
	mov	r4, r5
	mov	lr, r5
	mov	ip, r5
	add	r4, r4, #42
	add	r5, r5, #14
	add	lr, lr, #28
	add	ip, ip, #56
.L799:
	ldrh	r8, [r3, #2]!
	subs	r0, r0, #1
	strh	r8, [r5, #2]!	@ movhi
	ldrh	r8, [r7, #2]!
	strh	r8, [r4, #2]!	@ movhi
	ldrh	r8, [r6, #2]!
	strh	r8, [lr, #2]!	@ movhi
	ldrh	r8, [r2, #2]!
	strh	r8, [ip, #2]!	@ movhi
	bne	.L799
	ldr	r3, [fp, #-52]
	movw	r0, #2766
	mov	ip, #1
	mov	r2, #16384
	add	r1, r3, r1, lsl #1
	movw	r3, #2780
	add	r1, r1, #8192
	strh	ip, [r1, r0]	@ movhi
	strh	r2, [r1, r3]	@ movhi
	b	.L784
.L790:
	ldr	r0, [r2, #1500]
	ldr	r2, [fp, #-56]
	cmp	r0, #1
	ldr	r2, [r2, #2932]
	bne	.L803
	b	.L797
.L816:
	ldr	r3, [fp, #-52]
	mov	r4, #16384
	add	lr, r3, #10944
	mov	r3, #7
	mov	ip, lr
	mov	r0, lr
	mov	r2, lr
	add	ip, ip, #42
	add	lr, lr, #14
	add	r0, r0, #28
	add	r2, r2, #56
.L798:
	subs	r3, r3, #1
	strh	r1, [lr, #2]!	@ movhi
	strh	r1, [ip, #2]!	@ movhi
	strh	r4, [r0, #2]!	@ movhi
	strh	r4, [r2, #2]!	@ movhi
	bne	.L798
	b	.L784
.L818:
	.align	2
.L817:
	.word	.LANCHOR0+492
	.word	.LC68
	UNWIND(.fnend)
	.size	AVS2_CalDistance, .-AVS2_CalDistance
	.align	2
	.global	AVS2_SetImgFormat
	.type	AVS2_SetImgFormat, %function
AVS2_SetImgFormat:
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
	add	r5, r0, #8192
	add	r7, r0, #12288
	mov	r6, r0
	ldr	r2, [r5, #3012]
	ldr	r3, [r7, #1328]
	cmp	r2, #1
	ldr	r10, [r7, #1508]
	str	r3, [fp, #-48]
	moveq	r8, #0
	beq	.L820
	ldr	r8, [r7, #1548]
	subs	r8, r8, #1
	movne	r8, #1
.L820:
	ldr	r2, [r5, #3048]
	ldr	r3, [r7, #1556]
	sub	r2, r2, #1
	ldr	r0, [r6, #4]
	cmp	r2, #3
	str	r3, [fp, #-52]
	ldrls	r1, .L834
	movhi	r9, #0
	addls	r2, r1, r2, lsl #2
	ldr	r1, [r5, #2928]
	ldrls	r9, [r2, #512]
	ldr	r1, [r1, #56]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L831
	cmp	r8, #1
	movne	lr, #3
	beq	.L832
.L823:
	ldr	ip, [r4, #64]
	mov	r1, r9
	mov	r0, r4
	bfi	ip, r9, #14, #3
	str	ip, [r4, #64]
	ldr	r3, [fp, #-52]
	mov	r2, ip, lsr #8
	ldrb	r9, [r4, #66]	@ zero_extendqisi2
	bfi	r2, r3, #4, #2
	ldr	r3, [fp, #-48]
	bfi	r2, lr, #2, #2
	bfi	ip, r3, #5, #3
	bfi	r2, r8, #0, #2
	and	ip, ip, #227
	strb	r2, [r4, #65]
	bfi	ip, r10, #0, #2
	strb	ip, [r4, #64]
	ldr	r2, [r5, #2928]
	ldrb	r2, [r2, #15]	@ zero_extendqisi2
	bfi	r9, r2, #1, #1
	strb	r9, [r4, #66]
	ldr	r2, [r5, #2764]
	str	r10, [r4, #56]
	str	r10, [r4, #60]
	str	r2, [r4, #152]
	bl	SetAspectRatio
	ldr	r3, [r5, #2928]
	ldrb	r3, [r3, #16]	@ zero_extendqisi2
	str	r3, [r4, #120]
	ldr	r3, [r6, #36]
	ldr	r3, [r3, #604]
	str	r3, [r4, #124]
	ldr	r3, [r6, #36]
	ldr	r3, [r3, #608]
	str	r3, [r4, #128]
	ldr	r3, [r6, #36]
	ldr	r3, [r3, #612]
	str	r3, [r4, #132]
	ldr	r3, [r5, #3020]
	str	r3, [r4, #68]
	ldr	r3, [r5, #3028]
	str	r3, [r4, #72]
	ldr	r2, [r5, #3024]
	str	r2, [r4, #76]
	ldr	r2, [r5, #3032]
	str	r2, [r4, #80]
	ldr	r2, [r7, #1324]
	str	r2, [r4, #108]
	ldr	r2, [r6, #36]
	ldr	r2, [r2, #28]
	cmp	r2, #25
	beq	.L833
.L824:
	mov	r3, #18
	str	r3, [r4, #296]
	ldr	r1, [r7, #1552]
	mov	r2, #1
	mov	r3, #8
	strb	r2, [r4, #291]
	cmp	r1, r2
	strb	r2, [r4, #289]
	str	r3, [r4, #300]
	moveq	r2, #0
	movne	r2, #4
	str	r3, [r4, #308]
	strb	r2, [r4, #284]
	str	r3, [r4, #304]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L832:
	ldr	r1, [r7, #1564]
	cmp	r1, #1
	moveq	lr, #1
	movne	lr, #2
	b	.L823
.L833:
	ldr	r0, [r4, #112]
	add	r3, r3, #15
	ldr	ip, [r4, #36]
	add	lr, r4, #512
	mov	r3, r3, lsr #4
	mov	r1, r0, asl #4
	add	r5, ip, r0
	mul	r1, r3, r1
	add	r6, r1, ip
	str	r6, [r4, #40]
	ldrd	r2, [lr, #-8]
	add	r0, r6, r0
	adds	r2, r2, r1
	adc	r3, r3, r1, asr #31
	strd	r2, [lr]
	str	r6, [r4, #24]
	str	r0, [r4, #32]
	str	r5, [r4, #28]
	str	ip, [r4, #20]
	b	.L824
.L831:
	movw	r2, #3140
	ldr	r1, .L834+4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L835:
	.align	2
.L834:
	.word	.LANCHOR0
	.word	.LC69
	UNWIND(.fnend)
	.size	AVS2_SetImgFormat, .-AVS2_SetImgFormat
	.align	2
	.global	AVS2_SimpleDirectProcess
	.type	AVS2_SimpleDirectProcess, %function
AVS2_SimpleDirectProcess:
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
	add	r3, r0, #8192
	mov	r2, #1
	mov	r6, r0
	ldr	r4, [r3, #2928]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	strb	r2, [r4, #4]
	cmp	r3, #6
	beq	.L839
	mov	r1, r4
	bl	AVS2_OutputOneFrame
.L838:
	mov	r5, #0
	ldr	r1, [r4, #56]
	strb	r5, [r4, #5]
	mov	r2, r5
	ldr	r0, [r6, #4]
	bl	FSP_SetRef
	strb	r5, [r4, #6]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L839:
	mov	r2, #0
	ldr	r1, [r4, #56]
	ldr	r0, [r0, #4]
	bl	FSP_SetDisplay
	b	.L838
	UNWIND(.fnend)
	.size	AVS2_SimpleDirectProcess, .-AVS2_SimpleDirectProcess
	.align	2
	.global	AVS2_DispOrderProcess
	.type	AVS2_DispOrderProcess, %function
AVS2_DispOrderProcess:
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
	add	r3, r0, #8192
	mov	r4, r0
	ldr	r2, [r3, #2928]
	ldrb	r1, [r2, #7]	@ zero_extendqisi2
	cmp	r1, #6
	beq	.L843
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L842
	ldr	r1, [r0, #36]
	ldr	r1, [r1, #12]
	cmp	r1, #0
	beq	.L844
.L842:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_DisplayFrameInPOI
.L844:
	mov	r5, #1
	strb	r5, [r2, #4]
	ldr	r1, [r3, #2928]
	bl	AVS2_OutputOneFrame
	strb	r5, [r4, #1]
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_DisplayFrameInPOI
.L843:
	mov	r1, #1
	strb	r1, [r2, #4]
	ldr	r3, [r3, #2928]
	mov	r2, #0
	ldr	r0, [r0, #4]
	ldr	r1, [r3, #56]
	bl	FSP_SetDisplay
	b	.L842
	UNWIND(.fnend)
	.size	AVS2_DispOrderProcess, .-AVS2_DispOrderProcess
	.align	2
	.global	AVS2_DecOrderProcess
	.type	AVS2_DecOrderProcess, %function
AVS2_DecOrderProcess:
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
	add	r2, r0, #8192
	mov	ip, #1
	ldr	r1, [r2, #2928]
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	strb	ip, [r1, #4]
	cmp	r2, #6
	beq	.L847
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2_OutputOneFrame
.L847:
	ldr	r1, [r1, #56]
	mov	r2, #0
	ldr	r0, [r0, #4]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetDisplay
	UNWIND(.fnend)
	.size	AVS2_DecOrderProcess, .-AVS2_DecOrderProcess
	.align	2
	.global	AVS2_UpdateFrameBuf
	.type	AVS2_UpdateFrameBuf, %function
AVS2_UpdateFrameBuf:
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
	add	r3, r0, #12288
	mov	r4, r0
	ldr	r3, [r3, #1508]
	sub	r3, r3, #5
	cmp	r3, #1
	bls	.L850
.L849:
	mov	r0, r4
	bl	AVS2_UpdateRefBuf
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_RefreshBuf
.L850:
	bl	AVS2_UpdateSceneBuf.part.7
	b	.L849
	UNWIND(.fnend)
	.size	AVS2_UpdateFrameBuf, .-AVS2_UpdateFrameBuf
	.align	2
	.global	AVS2_FlushFrameInDpb
	.type	AVS2_FlushFrameInDpb, %function
AVS2_FlushFrameInDpb:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	add	r7, r0, #18944
	add	r7, r7, #148
	mov	r8, #0
	mov	r4, r0
	mov	r2, r8
	mov	r3, r7
.L853:
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L852
	ldrb	r1, [r3, #2]	@ zero_extendqisi2
	add	ip, r8, #1
	sub	r0, fp, #44
	cmp	r1, #0
	add	r0, r0, r8
	uxtbne	r8, ip
	strneb	r2, [r0, #-16]
.L852:
	add	r2, r2, #1
	add	r3, r3, #104
	cmp	r2, #16
	bne	.L853
	cmp	r8, #0
	beq	.L854
	sub	r3, fp, #60
	mov	r9, #0
	add	r6, r3, r8
	mov	r10, r9
	mov	r5, #104
.L855:
	cmp	r8, #0
	ble	.L858
	sub	r2, fp, #60
	movw	ip, #32767
.L857:
	ldrb	r1, [r2], #1	@ zero_extendqisi2
	mla	r3, r5, r1, r4
	add	r3, r3, #18944
	add	r3, r3, #144
	ldrb	r0, [r3, #4]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L856
	ldrsh	r3, [r3, #2]
	cmp	r3, ip
	movle	r10, r1
	movle	ip, r3
.L856:
	cmp	r2, r6
	bne	.L857
	movw	r3, #32767
	cmp	ip, r3
	beq	.L858
	mul	r1, r5, r10
	mov	r2, #1
	mov	r0, r4
	add	r3, r4, r1
	add	r1, r1, #18944
	add	r3, r3, #18944
	add	r1, r1, #144
	add	r1, r4, r1
	add	r3, r3, #144
	strb	r2, [r3, #4]
	str	r3, [fp, #-64]
	bl	AVS2_OutputOneFrame
	ldr	r3, [fp, #-64]
	mov	r0, #13
	ldr	r1, .L873
	ldrsh	r2, [r3, #2]
	bl	dprint_vfmw
.L858:
	add	r9, r9, #1
	uxtb	r3, r9
	cmp	r8, r3
	bhi	.L855
.L854:
	add	r4, r4, #20736
	add	r4, r4, #20
	b	.L860
.L859:
	add	r7, r7, #104
	cmp	r7, r4
	beq	.L872
.L860:
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L859
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	add	r7, r7, #104
	cmp	r3, #0
	ldreqb	r3, [r7, #-102]	@ zero_extendqisi2
	andeq	r3, r3, #2
	streqb	r3, [r7, #-102]
	cmp	r7, r4
	bne	.L860
.L872:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L874:
	.align	2
.L873:
	.word	.LC56
	UNWIND(.fnend)
	.size	AVS2_FlushFrameInDpb, .-AVS2_FlushFrameInDpb
	.align	2
	.global	AVS2_FlushPreSizeImg
	.type	AVS2_FlushPreSizeImg, %function
AVS2_FlushPreSizeImg:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	sub	r3, fp, #20
	mov	r4, #0
	mov	r5, r0
	str	r4, [r3, #-4]!
	sub	r2, fp, #28
	ldr	r0, [r0, #4]
	sub	r1, fp, #32
	str	r4, [fp, #-32]
	str	r4, [fp, #-28]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r5, #36]
	ldr	r3, [r3, #732]
	cmp	r3, #1
	movne	r0, #1
	beq	.L880
.L876:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L880:
	ldr	r3, [fp, #-24]
	cmp	r3, r4
	ble	.L881
.L879:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L881:
	ldr	r3, [fp, #-28]
	cmp	r3, #32
	bgt	.L879
	ldr	r4, [r5, #40]
	clz	r0, r4
	mov	r0, r0, lsr #5
	b	.L876
	UNWIND(.fnend)
	.size	AVS2_FlushPreSizeImg, .-AVS2_FlushPreSizeImg
	.align	2
	.global	AVS2_ArrangeFrameBuf
	.type	AVS2_ArrangeFrameBuf, %function
AVS2_ArrangeFrameBuf:
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
	ldr	r3, [r0, #20]
	mov	r4, r0
	cmp	r3, #0
	beq	.L883
	bl	AVS2_FlushPreSizeImg
	cmp	r0, #0
	bne	.L884
.L886:
	mov	r0, #3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L884:
	mov	r0, r4
	bl	AVS2_ClearDpb
	add	r1, r4, #18432
	add	r1, r1, #144
	ldr	r0, [r4, #4]
	bl	FSP_ClearNotInVoQueue
	mov	r3, #0
	str	r3, [r4, #20]
.L883:
	mov	r3, #0
	mov	r0, r4
	str	r3, [r4, #24]
	bl	AVS2_AllocateVHB
	cmp	r0, #3
	mov	r4, r0
	beq	.L886
	cmp	r0, #0
	beq	.L894
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L894:
	ldr	r1, .L895
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L896:
	.align	2
.L895:
	.word	.LC70
	UNWIND(.fnend)
	.size	AVS2_ArrangeFrameBuf, .-AVS2_ArrangeFrameBuf
	.align	2
	.global	AVS2_ParseHeader
	.type	AVS2_ParseHeader, %function
AVS2_ParseHeader:
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
	add	r5, r0, #44
	mov	r3, #0
	mov	r4, r0
	str	r3, [r0, #8]
	mov	r1, #32
	mov	r0, r5
	bl	BsShow
	uxtb	r6, r0
	sub	r3, r6, #176
	cmp	r3, #78
	ldrls	pc, [pc, r3, asl #2]
	b	.L898
.L900:
	.word	.L899
	.word	.L901
	.word	.L902
	.word	.L903
	.word	.L898
	.word	.L904
	.word	.L903
	.word	.L901
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L898
	.word	.L905
.L901:
	ldr	r3, [r4, #12]
	tst	r3, #32768
	bne	.L936
	cmp	r6, #177
	beq	.L937
	ldr	r1, .L942
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r5, .L942+4
.L920:
	ldr	r3, [r5]
	tst	r3, #1
	bne	.L902
	mov	r0, r4
	bl	AVS2_ClearDpb
.L902:
	mov	r0, r4
	mov	r5, #1
	bl	AVS2_ClearPacket
.L907:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L903:
	ldr	r3, [r4, #12]
	tst	r3, #32768
	bne	.L936
	tst	r3, #65536
	beq	.L911
	ldr	r3, [r4, #20]
	cmp	r3, #1
	beq	.L912
	ldr	r3, [r4, #24]
	cmp	r3, #0
	bne	.L913
.L912:
	mov	r0, r4
	bl	AVS2_ArrangeFrameBuf
	cmp	r0, #1
	mov	r5, r0
	beq	.L913
	cmp	r0, #3
	moveq	r3, #1
	streq	r3, [r4, #8]
	beq	.L907
.L934:
	mov	r0, r4
	bl	AVS2_ClearPacket
	b	.L907
.L905:
	mov	r1, #32
	mov	r0, r5
	bl	BsSkip
	mov	r1, #32
	mov	r0, r5
	bl	BsGet
	mov	r1, #32
	mov	r6, r0
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #12]
	tst	r3, #32768
	bne	.L936
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r6, r3
	bne	.L911
	mvn	r3, #0
	mov	r5, #1
	str	r3, [r4, #28]
	mov	r0, r4
	strb	r5, [r4]
	bl	AVS2_ClearPacket
	b	.L907
.L904:
	mov	r0, r4
	mov	r5, #1
	bl	AVS2_Extension
	mov	r0, r4
	bl	AVS2_ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L899:
	ldr	r3, [r4, #12]
	tst	r3, #32768
	bne	.L936
	ldr	r3, [r4, #28]
	mov	r0, r4
	cmn	r3, #1
	beq	.L938
	bl	AVS2_FlushFrameInDpb
.L909:
	mov	r0, r4
	mov	r5, #1
	bl	AVS2_SequenceHeader
	mov	r0, r4
	bl	AVS2_ClearPacket
	b	.L907
.L898:
	cmp	r6, #143
	bhi	.L911
	ldr	r3, [r4, #12]
	and	r3, r3, #327680
	cmp	r3, #327680
	beq	.L939
.L911:
	mov	r0, r4
	mov	r5, #0
	bl	AVS2_ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L936:
	mov	r5, #1
	orr	r3, r3, #16384
	str	r5, [r4, #8]
	mov	r0, r5
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L937:
	ldr	r5, .L942+4
	ldr	r3, [r5]
	tst	r3, #1
	beq	.L940
.L919:
	ldr	r1, .L942+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L920
.L913:
	ldr	r3, [r4, #28]
	cmp	r6, #179
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r4, #28]
	beq	.L941
	bl	AVS2_InterPictureHeader
	b	.L902
.L938:
	bl	AVS2_ClearDpb
	b	.L909
.L939:
	mov	r0, r4
	bl	AVS2_WriteSliceMsg
	subs	r5, r0, #0
	bne	.L907
	b	.L934
.L940:
	mov	r0, r4
	bl	AVS2_FlushFrameInDpb
	b	.L919
.L941:
	bl	AVS2_IntraPictureHeader
	b	.L902
.L943:
	.align	2
.L942:
	.word	.LC72
	.word	g_StandardObedience
	.word	.LC71
	UNWIND(.fnend)
	.size	AVS2_ParseHeader, .-AVS2_ParseHeader
	.align	2
	.global	AVS2_DecodeArbiter
	.type	AVS2_DecodeArbiter, %function
AVS2_DecodeArbiter:
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
	ldr	r5, [r0, #12]
	mov	r4, r0
	and	r3, r5, #376832
	cmp	r3, #376832
	beq	.L947
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L947:
	add	r1, r0, #14848
	add	r0, r0, #11136
	add	r1, r1, #36
	movw	r2, #3692
	add	r0, r0, #56
	bic	r5, r5, #311296
	bl	memcpy
	mov	r0, #1
	str	r5, [r4, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_DecodeArbiter, .-AVS2_DecodeArbiter
	.align	2
	.global	AVS2_PrepareDecode
	.type	AVS2_PrepareDecode, %function
AVS2_PrepareDecode:
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
	bl	AVS2_SetPicInfo
	ldr	r3, [r4, #1728]
	sub	r2, r3, #1
	cmp	r2, #255
	bhi	.L963
	mov	r0, r4
	bl	AVS2_VarifyDecMode
	cmp	r0, #0
	bne	.L964
.L962:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L964:
	mov	r0, r4
	bl	AVS2_SetupFrameBuf
	cmp	r0, #0
	beq	.L962
	add	r3, r4, #12288
	ldr	r3, [r3, #1512]
	cmp	r3, #0
	bne	.L953
	mov	r0, r4
	bl	AVS2_SetupRefFrame
	cmp	r0, #0
	beq	.L955
	mov	r0, r4
	bl	AVS2_CalDistance
.L953:
	mov	r0, r4
	bl	AVS2_SetupHalConfig
	cmp	r0, #0
	beq	.L955
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L963:
	ldr	r2, .L965
	mov	r0, #1
	ldr	r1, .L965+4
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L955:
	mov	r0, r4
	bl	AVS2_ReleaseFrameBuf
	b	.L962
.L966:
	.align	2
.L965:
	.word	.LANCHOR0+528
	.word	.LC73
	UNWIND(.fnend)
	.size	AVS2_PrepareDecode, .-AVS2_PrepareDecode
	.align	2
	.global	AVS2_StartDecode
	.type	AVS2_StartDecode, %function
AVS2_StartDecode:
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
	ldr	r3, [r0, #36]
	add	r2, r0, #588
	str	r2, [r0, #40]
	ldr	r2, [r3, #600]
	strb	r2, [r0, #590]
	ldr	r3, [r3, #652]
	strb	r3, [r0, #589]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2_StartDecode, .-AVS2_StartDecode
	.align	2
	.global	AVS2_PostProcess
	.type	AVS2_PostProcess, %function
AVS2_PostProcess:
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
	bl	AVS2_SetImgFormat
	ldr	r3, [r4, #36]
	ldr	r2, [r3, #8]
	cmp	r2, #2
	beq	.L974
	ldr	r2, [r3, #24]
	cmp	r2, #0
	beq	.L975
	sub	r3, r2, #1
	cmp	r3, #1
	bls	.L973
	ldr	r1, .L976
	mov	r0, #1
	bl	dprint_vfmw
.L973:
	mov	r0, r4
	bl	AVS2_DecOrderProcess
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_UpdateFrameBuf
.L975:
	mov	r0, r4
	bl	AVS2_DispOrderProcess
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_UpdateFrameBuf
.L974:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS2_SimpleDirectProcess
.L977:
	.align	2
.L976:
	.word	.LC74
	UNWIND(.fnend)
	.size	AVS2_PostProcess, .-AVS2_PostProcess
	.align	2
	.global	AVS2DEC_Init
	.type	AVS2DEC_Init, %function
AVS2DEC_Init:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r1
	mov	r4, r0
	moveq	r6, #1
	movne	r6, #0
	beq	.L982
	add	r5, r0, #16384
	ldr	r3, .L984
	movw	r2, #20752
	mov	r1, r6
	ldr	r8, [r5, #2536]
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r4
	str	r8, [r5, #2536]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #4]
	beq	.L983
	add	r0, r4, #18432
	add	r0, r0, #144
	bl	ResetVoQueue
	str	r7, [r4, #36]
	mvn	r3, #0
	str	r6, [r7, #920]
	mov	r0, #1
	str	r3, [r4, #28]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L982:
	movw	r2, #3698
	ldr	r1, .L984+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L983:
	mov	r0, r6
	ldr	r2, .L984+8
	ldr	r1, .L984+12
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L985:
	.align	2
.L984:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC54
	.word	.LANCHOR0+548
	.word	.LC75
	UNWIND(.fnend)
	.size	AVS2DEC_Init, .-AVS2DEC_Init
	.align	2
	.global	AVS2DEC_Destroy
	.type	AVS2DEC_Destroy, %function
AVS2DEC_Destroy:
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
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS2DEC_Destroy, .-AVS2DEC_Destroy
	.align	2
	.global	AVS2_TryReleaseOldestFs
	.type	AVS2_TryReleaseOldestFs, %function
AVS2_TryReleaseOldestFs:
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
	mov	ip, #0
	add	r2, r0, #18944
	mov	r5, r0
	add	r2, r2, #150
	mov	r1, ip
	movw	r3, #4095
	mvn	r4, #0
	b	.L989
.L988:
	add	r1, r1, #1
	add	r2, r2, #104
	cmp	r1, #16
	beq	.L995
.L989:
	ldrb	r0, [r2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L988
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	cmp	r0, #1
	bne	.L988
	ldrh	lr, [r2, #-6]
	sxth	r0, r3
	add	ip, ip, #1
	sxth	r6, lr
	cmp	r6, r0
	bge	.L988
	ldrb	r0, [r2, #-2]	@ zero_extendqisi2
	add	r2, r2, #104
	cmp	r0, #1
	moveq	r4, r1
	add	r1, r1, #1
	moveq	r3, lr
	cmp	r1, #16
	bne	.L989
.L995:
	add	r2, r5, #16384
	cmn	r4, #1
	ldrb	r2, [r2, #916]	@ zero_extendqisi2
	movne	r6, #0
	moveq	r6, #1
	add	r2, r2, #1
	cmp	ip, r2
	orrcc	r6, r6, #1
	cmp	r6, #0
	bne	.L987
	str	ip, [sp]
	sxth	r3, r3
	ldr	r2, .L996
	mov	r0, #1
	ldr	r1, .L996+4
	bl	dprint_vfmw
	mov	r3, #104
	mla	r4, r3, r4, r5
	movw	r1, #19144
	mov	r2, r6
	add	r3, r4, #18944
	add	r3, r3, #144
	strb	r6, [r3, #6]
	strb	r6, [r3, #5]
	ldr	r0, [r5, #4]
	ldr	r1, [r4, r1]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	FSP_SetRef
.L987:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L997:
	.align	2
.L996:
	.word	.LANCHOR0+564
	.word	.LC76
	UNWIND(.fnend)
	.size	AVS2_TryReleaseOldestFs, .-AVS2_TryReleaseOldestFs
	.align	2
	.global	AVS2DEC_GetImageBuffer
	.type	AVS2DEC_GetImageBuffer, %function
AVS2DEC_GetImageBuffer:
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
	beq	.L1005
	ldr	r0, [r4, #4]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #4]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L1006
.L1001:
	mov	r0, r4
	bl	AVS2_TryReleaseOldestFs
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1006:
	add	r1, r4, #18432
	ldr	r0, [r4, #4]
	add	r1, r1, #144
	bl	FSP_ClearNotInVoQueue
	b	.L1001
.L1005:
	movw	r2, #3772
	ldr	r1, .L1007
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1008:
	.align	2
.L1007:
	.word	.LC54
	UNWIND(.fnend)
	.size	AVS2DEC_GetImageBuffer, .-AVS2DEC_GetImageBuffer
	.align	2
	.global	AVS2DEC_Decode
	.type	AVS2DEC_Decode, %function
AVS2DEC_Decode:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r6, r1
	moveq	r5, #1
	movne	r5, #0
	beq	.L1017
	ldr	r2, [r1, #16]
	add	r0, r0, #44
	ldr	r1, [r1]
	bl	BsInit
	ldr	r3, .L1021
	add	r0, r4, #18688
	mov	r1, r6
	mov	r2, #160
	add	r0, r0, #240
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, r4
	str	r3, [r4, #16]
	bl	AVS2_ParseHeader
	cmp	r0, #3
	beq	.L1018
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r6, [r4, #12]
	and	r3, r6, #376832
	cmp	r3, #376832
	beq	.L1019
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1017:
	movw	r2, #3795
	ldr	r1, .L1021+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1018:
	ldr	r3, [r4, #16]
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1019:
	add	r1, r4, #14848
	add	r0, r4, #11136
	add	r1, r1, #36
	movw	r2, #3692
	add	r0, r0, #56
	bic	r6, r6, #311296
	bl	memcpy
	mov	r0, r4
	str	r6, [r4, #12]
	bl	AVS2_PrepareDecode
	subs	r5, r0, #0
	beq	.L1020
	ldr	r3, [r4, #36]
	add	r2, r4, #588
	str	r2, [r4, #40]
	mov	r0, #1
	ldr	r2, [r3, #600]
	strb	r2, [r4, #590]
	ldr	r3, [r3, #652]
	strb	r3, [r4, #589]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1020:
	mov	r0, r4
	bl	AVS2_ClearPicSlice
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1022:
	.align	2
.L1021:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC54
	UNWIND(.fnend)
	.size	AVS2DEC_Decode, .-AVS2DEC_Decode
	.align	2
	.global	AVS2DEC_RecycleImage
	.type	AVS2DEC_RecycleImage, %function
AVS2DEC_RecycleImage:
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
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L1027
	mov	r2, #0
	ldr	r0, [r4, #4]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #4]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L1026
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #4]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1026:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1027:
	movw	r2, #3880
	ldr	r1, .L1028
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1029:
	.align	2
.L1028:
	.word	.LC54
	UNWIND(.fnend)
	.size	AVS2DEC_RecycleImage, .-AVS2DEC_RecycleImage
	.align	2
	.global	AVS2DEC_GetRemainImg
	.type	AVS2DEC_GetRemainImg, %function
AVS2DEC_GetRemainImg:
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
	beq	.L1034
	bl	AVS2_FlushFrameInDpb
	add	r0, r4, #18432
	add	r0, r0, #144
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	GetVoLastImageID
.L1034:
	movw	r2, #3902
	ldr	r1, .L1035
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1036:
	.align	2
.L1035:
	.word	.LC54
	UNWIND(.fnend)
	.size	AVS2DEC_GetRemainImg, .-AVS2DEC_GetRemainImg
	.align	2
	.global	AVS2DEC_ClearCurPic
	.type	AVS2DEC_ClearCurPic, %function
AVS2DEC_ClearCurPic:
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
	beq	.L1040
	bl	AVS2_ClearPicSlice
	mov	r0, r4
	bl	AVS2_ReleaseFrameBuf
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1040:
	movw	r2, #3924
	ldr	r1, .L1041
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1042:
	.align	2
.L1041:
	.word	.LC54
	UNWIND(.fnend)
	.size	AVS2DEC_ClearCurPic, .-AVS2DEC_ClearCurPic
	.align	2
	.global	AVS2DEC_VDMPostProc
	.type	AVS2DEC_VDMPostProc, %function
AVS2DEC_VDMPostProc:
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
	mov	r5, r1
	beq	.L1053
	add	ip, r4, #8192
	ldrb	r1, [r4, #591]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [ip, #2928]
	strb	r1, [r2, #15]
	ldrb	r1, [r4, #590]	@ zero_extendqisi2
	strb	r1, [r2, #16]
	beq	.L1046
	mov	r2, r3, asl #6
	ldr	r1, .L1056
	sub	r3, r2, r3, asl #3
	add	r3, r3, r1
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L1054
	cmp	r3, #1
	beq	.L1046
.L1048:
	ldr	r3, [r4, #36]
	mov	r0, r4
	ldr	r3, [r3, #4]
	cmp	r3, r5
	blt	.L1055
	bl	AVS2_PostProcess
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1046:
	mov	r0, r4
	bl	AVS2_ClearPicSlice
	b	.L1048
.L1055:
	bl	AVS2DEC_ClearCurPic
	ldr	r3, [r4, #36]
	mov	r2, r5
	ldr	r1, .L1056+4
	mov	r0, #1
	ldr	r3, [r3, #4]
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1054:
	bl	AVS2_ClearPicSlice
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1053:
	movw	r2, #3835
	ldr	r1, .L1056+8
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1057:
	.align	2
.L1056:
	.word	g_VdmDrvParam+40
	.word	.LC77
	.word	.LC54
	UNWIND(.fnend)
	.size	AVS2DEC_VDMPostProc, .-AVS2DEC_VDMPostProc
	.global	AVS2_WqM4x4IdxModel2
	.global	AVS2_WqM4x4IdxModel1
	.global	AVS2_WqM4x4IdxModel0
	.global	AVS2_WqM8x8IdxModel2
	.global	AVS2_WqM8x8IdxModel1
	.global	AVS2_WqM8x8IdxModel0
	.global	AVS2_WQM_8x8Default
	.global	AVS2_WQM_4x4Default
	.global	AVS2_WeightQuantParamBase2
	.global	AVS2_WeightQuantParamBase1
	.global	AVS2_WeightQuantParamDefault
	.global	Avs2_AlfRegionTable
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	CSWTCH.37, %object
	.size	CSWTCH.37, 28
CSWTCH.37:
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC84
	.type	__func__.14241, %object
	.size	__func__.14241, 15
__func__.14241:
	.ascii	"AVS2_User_Data\000"
	.space	1
	.type	AVS2_WqM8x8IdxModel0, %object
	.size	AVS2_WqM8x8IdxModel0, 64
AVS2_WqM8x8IdxModel0:
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	5
	.byte	5
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM4x4IdxModel0, %object
	.size	AVS2_WqM4x4IdxModel0, 16
AVS2_WqM4x4IdxModel0:
	.byte	0
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	2
	.byte	1
	.byte	5
	.byte	3
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM8x8IdxModel1, %object
	.size	AVS2_WqM8x8IdxModel1, 64
AVS2_WqM8x8IdxModel1:
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM4x4IdxModel1, %object
	.size	AVS2_WqM4x4IdxModel1, 16
AVS2_WqM4x4IdxModel1:
	.byte	0
	.byte	4
	.byte	4
	.byte	5
	.byte	3
	.byte	2
	.byte	2
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM8x8IdxModel2, %object
	.size	AVS2_WqM8x8IdxModel2, 64
AVS2_WqM8x8IdxModel2:
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	5
	.byte	5
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM4x4IdxModel2, %object
	.size	AVS2_WqM4x4IdxModel2, 16
AVS2_WqM4x4IdxModel2:
	.byte	0
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WeightQuantParamDefault, %object
	.size	AVS2_WeightQuantParamDefault, 6
AVS2_WeightQuantParamDefault:
	.byte	64
	.byte	49
	.byte	53
	.byte	58
	.byte	58
	.byte	64
	.space	2
	.type	AVS2_WeightQuantParamBase1, %object
	.size	AVS2_WeightQuantParamBase1, 6
AVS2_WeightQuantParamBase1:
	.byte	67
	.byte	71
	.byte	71
	.byte	80
	.byte	80
	.byte	106
	.space	2
	.type	AVS2_WeightQuantParamBase2, %object
	.size	AVS2_WeightQuantParamBase2, 6
AVS2_WeightQuantParamBase2:
	.byte	64
	.byte	49
	.byte	53
	.byte	58
	.byte	58
	.byte	64
	.space	2
	.type	AVS2_WQM_4x4Default, %object
	.size	AVS2_WQM_4x4Default, 16
AVS2_WQM_4x4Default:
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	64
	.byte	68
	.byte	76
	.byte	80
	.byte	72
	.byte	76
	.byte	84
	.byte	96
	.type	AVS2_WQM_8x8Default, %object
	.size	AVS2_WQM_8x8Default, 64
AVS2_WQM_8x8Default:
	.byte	64
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	68
	.byte	72
	.byte	76
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	84
	.byte	92
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	80
	.byte	88
	.byte	100
	.byte	64
	.byte	68
	.byte	72
	.byte	80
	.byte	84
	.byte	92
	.byte	100
	.byte	112
	.byte	68
	.byte	72
	.byte	80
	.byte	84
	.byte	92
	.byte	104
	.byte	112
	.byte	-128
	.byte	76
	.byte	80
	.byte	84
	.byte	92
	.byte	104
	.byte	116
	.byte	-124
	.byte	-104
	.byte	96
	.byte	100
	.byte	104
	.byte	116
	.byte	124
	.byte	-116
	.byte	-92
	.byte	-68
	.byte	104
	.byte	108
	.byte	116
	.byte	-128
	.byte	-104
	.byte	-84
	.byte	-64
	.byte	-40
	.type	Avs2_AlfRegionTable, %object
	.size	Avs2_AlfRegionTable, 16
Avs2_AlfRegionTable:
	.byte	0
	.byte	1
	.byte	4
	.byte	5
	.byte	15
	.byte	2
	.byte	3
	.byte	6
	.byte	14
	.byte	11
	.byte	10
	.byte	7
	.byte	13
	.byte	12
	.byte	9
	.byte	8
	.type	__func__.14397, %object
	.size	__func__.14397, 24
__func__.14397:
	.ascii	"AVS2_IntraPictureHeader\000"
	.type	__func__.14415, %object
	.size	__func__.14415, 24
__func__.14415:
	.ascii	"AVS2_InterPictureHeader\000"
	.type	__func__.14552, %object
	.size	__func__.14552, 19
__func__.14552:
	.ascii	"AVS2_SetupFrameBuf\000"
	.space	1
	.type	__func__.14571, %object
	.size	__func__.14571, 19
__func__.14571:
	.ascii	"AVS2_SetupRefFrame\000"
	.space	1
	.type	__func__.14602, %object
	.size	__func__.14602, 17
__func__.14602:
	.ascii	"AVS2_CalDistance\000"
	.space	3
	.type	CSWTCH.83, %object
	.size	CSWTCH.83, 16
CSWTCH.83:
	.word	5
	.word	1
	.word	2
	.word	3
	.type	__func__.14710, %object
	.size	__func__.14710, 19
__func__.14710:
	.ascii	"AVS2_PrepareDecode\000"
	.space	1
	.type	__func__.14727, %object
	.size	__func__.14727, 13
__func__.14727:
	.ascii	"AVS2DEC_Init\000"
	.space	3
	.type	__func__.14742, %object
	.size	__func__.14742, 24
__func__.14742:
	.ascii	"AVS2_TryReleaseOldestFs\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"AVS2_ue_v ERROR: LeadingZeros (%d) >= 32, return 0x" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"Stream StartCode is 0x%x Length is too Long cannot " )
	ASCII(.ascii	"Remove DPB!!\000" )
.LC2:
	ASCII(.ascii	"Unkown\000" )
	.space	1
.LC3:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	" ----> Dump Dpb Status:\012\000" )
	.space	3
.LC5:
	ASCII(.ascii	"Pic %2d, Type %6s, Occupied %d, Ref %d, Disp %d, DO" )
	ASCII(.ascii	"I %d, POI %d, FspID %d, FsPhy 0x%x, PmvPhy 0x%x\012" )
	ASCII(.ascii	"\000" )
.LC6:
	ASCII(.ascii	" ----> Dump End: Totoal Occupied Frame %d\012\012\000" )
.LC7:
	ASCII(.ascii	"User Data:\012\000" )
.LC8:
	ASCII(.ascii	"%s: cosume TotalPos(%d > %d)!\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"Slice num out of slot: %d > %d\012\000" )
.LC10:
	ASCII(.ascii	"Stream ERROR: slice_vertical_position %d out of ran" )
	ASCII(.ascii	"ge [0, 0x8F].\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"Stream ERROR: alf_filter_num_minus1 %d > 15.\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"ALF ERROR: alf_region_distance %d out of range [1, " )
	ASCII(.ascii	"15].\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"ALF ERROR: alf_coef_luma_8 %d out of range [-1088, " )
	ASCII(.ascii	"1071].\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"ALF ERROR: alf_coef_luma_%d %d out of range [-64, 6" )
	ASCII(.ascii	"3].\012\000" )
.LC15:
	ASCII(.ascii	"ALF ERROR: alf_coef_chroma0_8 %d out of range [-108" )
	ASCII(.ascii	"8, 1071].\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"ALF ERROR: alf_coef_chroma0_%d %d out of range [-64" )
	ASCII(.ascii	", 63].\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"ALF ERROR: alf_coef_chroma1_8 %d out of range [-108" )
	ASCII(.ascii	"8, 1071].\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"ALF ERROR: alf_coef_chroma1_%d %d out of range [-64" )
	ASCII(.ascii	", 63].\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"Intra stream ERROR: picture_output_delay out of ran" )
	ASCII(.ascii	"ge [0, 63], force 63.\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"Intra stream ERROR: force progressive_frame to 0 fo" )
	ASCII(.ascii	"r field_coded_sequence = 1\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"Intra stream ERROR: picture_qp %d out of range [0, " )
	ASCII(.ascii	"%d], force %d.\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"Intra stream ERROR: alpha_c_offset %d out of range " )
	ASCII(.ascii	"[-8, 8], force 0.\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"Intra stream ERROR: beta_offset %d out of range [-8" )
	ASCII(.ascii	", 8], force 0.\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"Intra stream ERROR: chroma_quant_param_delta_cb %d " )
	ASCII(.ascii	"out of range [-16, 16], force 0.\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"Intra stream ERROR: chroma_quant_param_delta_cr %d " )
	ASCII(.ascii	"out of range [-16, 16], force 0.\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"%s call AVS2_alf_parameter_set failed\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"Inter stream ERROR: picture_coding_type should not " )
	ASCII(.ascii	"equal 0.\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"Inter stream ERROR: picture_output_delay out of ran" )
	ASCII(.ascii	"ge [0, 63], force 63.\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"Inter stream ERROR: force progressive_frame to 1 fo" )
	ASCII(.ascii	"r progressive_sequence = 1\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"Inter stream ERROR: force progressive_frame to 0 fo" )
	ASCII(.ascii	"r field_coded_sequence = 1\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"Inter stream ERROR: picture_qp %d out of range [0, " )
	ASCII(.ascii	"%d], force %d.\012\000" )
	.space	1
.LC32:
	ASCII(.ascii	"Inter stream ERROR: alpha_c_offset %d out of range " )
	ASCII(.ascii	"[-8, 8], force 0.\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"Inter stream ERROR: beta_offset %d out of range [-8" )
	ASCII(.ascii	", 8], force 0.\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"Inter stream ERROR: chroma_quant_param_delta_cb %d " )
	ASCII(.ascii	"out of range [-16, 16], force 0.\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"Inter stream ERROR: chroma_quant_param_delta_cr %d " )
	ASCII(.ascii	"out of range [-16, 16], force 0.\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"%s ERROR: ucRefPicNum out of range [1, %d].\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"Sequence Header:\012\000" )
	.space	2
.LC38:
	ASCII(.ascii	"Stream ERROR: profile_id 0x%x unsupport.\012\000" )
	.space	2
.LC39:
	ASCII(.ascii	"Stream ERROR: level_id should not equal 0.\012\000" )
.LC40:
	ASCII(.ascii	"Stream ERROR: field_coded_sequence should be 0 when" )
	ASCII(.ascii	" progressive_sequence = 1\012\000" )
	.space	2
.LC41:
	ASCII(.ascii	"Stream ERROR: horizontal_size should not equal 0.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC42:
	ASCII(.ascii	"Stream ERROR: vertical_size should not equal 0.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC43:
	ASCII(.ascii	"Stream ERROR: chroma_format %d not support, only 4:" )
	ASCII(.ascii	"2:0 now.\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"Stream ERROR: sample_precision %d should equal to 8" )
	ASCII(.ascii	"/10\012\000" )
.LC45:
	ASCII(.ascii	"AVS2 sequence ERROR: ucBitDepth %d should equal to " )
	ASCII(.ascii	"8/10, and not less than sample_precision %d\012\000" )
.LC46:
	ASCII(.ascii	"Stream ERROR: aspect_ratio = 0 is forbidden!\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"Stream ERROR: frame_rate_code = 0 is forbidden!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC48:
	ASCII(.ascii	"Stream ERROR: num_of_rcs %d out of range [0, %d]\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC49:
	ASCII(.ascii	"MbWidth = %d, MbHeight = %d, don't support!\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"avs2 actual frame size(%dx%d) exeed max config(%dx%" )
	ASCII(.ascii	"d)\012\000" )
	.space	1
.LC51:
	ASCII(.ascii	"avs2 actual frame size(%dx%d) exceed max config(%dx" )
	ASCII(.ascii	"%d)\012\000" )
.LC52:
	ASCII(.ascii	"ERROR: partition fs memory failed!\012\000" )
.LC53:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance failed!\012\000" )
	.space	1
.LC54:
	ASCII(.ascii	"line: %d\012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"ERROR: AVS2_OutputOneFrame is err(%d)\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"Dump frame, POI: %d\012\000" )
	.space	3
.LC57:
	ASCII(.ascii	"NumOfRemovedPicture: %d\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"Target removal DOI[%d]: %d\012\000" )
.LC59:
	ASCII(.ascii	"Conflict: cur frame(Type %d, DOI %d, FspID %d, FsPh" )
	ASCII(.ascii	"y 0x%x, PmvPhy 0x%x) with frame(Type %d, Occupied %" )
	ASCII(.ascii	"d, UsedAsRef %d, DOI %d, FspID %d, FsPhy 0x%x, PmvP" )
	ASCII(.ascii	"hy 0x%x)\012\000" )
	.space	1
.LC60:
	ASCII(.ascii	"%s: Can't find non-occupied frame memory buffer!!!\012" )
	ASCII(.ascii	"\000" )
.LC61:
	ASCII(.ascii	"%s ERROR: get frame store fail!\012\000" )
	.space	3
.LC62:
	ASCII(.ascii	"%s ERROR: get image pointer fail!\012\000" )
	.space	1
.LC63:
	ASCII(.ascii	"Varify current frame DOI %d failed!\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"Can't find G or GB picture for the reference of S p" )
	ASCII(.ascii	"icture.\012\000" )
.LC65:
	ASCII(.ascii	"CurPic Doi %d cant find ref frame TargetDoi %d\012\000" )
.LC66:
	ASCII(.ascii	"Found ref num %d < num_of_reference_picture %d\012\000" )
.LC67:
	ASCII(.ascii	"%s ERROR: num_of_reference_picture %d out of range " )
	ASCII(.ascii	"[1, %d].\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"%s ERROR: pstRefFrmMem[0] = NULL or ucRefPicNum %d " )
	ASCII(.ascii	"out of range [1, %d].\012\000" )
	.space	2
.LC69:
	ASCII(.ascii	"line: %d pImage is null\012\000" )
	.space	3
.LC70:
	ASCII(.ascii	"ERROR: allocate vhb\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"AVS2_VIDEO_SEQUENCE_END_CODE\012\000" )
	.space	2
.LC72:
	ASCII(.ascii	"AVS2_VIDEO_EDIT_CODE\012\000" )
	.space	2
.LC73:
	ASCII(.ascii	"%s SliceNum %d invalid.\012\000" )
	.space	3
.LC74:
	ASCII(.ascii	"AVS2 unsupport output order %d, force dec order out" )
	ASCII(.ascii	"put.\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"%s get chan id failed!\012\000" )
.LC76:
	ASCII(.ascii	"%s set fs unref with oldest Doi %d to proceed decod" )
	ASCII(.ascii	"ing for ref num %d is full.\012\000" )
.LC77:
	ASCII(.ascii	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\012\000" )
	.space	1
.LC78:
	ASCII(.ascii	"I_PIC\000" )
	.space	2
.LC79:
	ASCII(.ascii	"P_PIC\000" )
	.space	2
.LC80:
	ASCII(.ascii	"B_PIC\000" )
	.space	2
.LC81:
	ASCII(.ascii	"F_PIC\000" )
	.space	2
.LC82:
	ASCII(.ascii	"S_PIC\000" )
	.space	2
.LC83:
	ASCII(.ascii	"G_PIC\000" )
	.space	2
.LC84:
	ASCII(.ascii	"GB_PIC\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
