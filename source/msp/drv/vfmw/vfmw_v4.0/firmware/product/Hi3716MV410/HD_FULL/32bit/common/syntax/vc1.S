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
	.file	"vc1.c"
	.text
	.align	2
	.type	VC1_Vfmw_GenerateIntensityMap, %function
VC1_Vfmw_GenerateIntensityMap:
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
	cmp	r2, #31
	subgt	r2, r2, #64
	cmp	r1, #0
	addne	ip, r1, #32
	moveq	r2, r2, asl #7
	mvneq	ip, #63
	rsbeq	r2, r2, #16320
	movne	r2, r2, asl #6
	cmp	r3, #0
	bne	.L13
	add	r3, r2, #32
	sub	r2, r0, #1
	add	r0, r0, #255
.L5:
	usat	r1, #8, r3, asr #6
	strb	r1, [r2, #1]!
	cmp	r2, r0
	add	r3, r3, ip
	bne	.L5
	ldmfd	sp, {fp, sp, pc}
.L13:
	mov	r3, ip, asl #7
	sub	r2, r0, #1
	rsb	r3, r3, #8192
	add	r0, r0, #255
	add	r3, r3, #32
.L6:
	usat	r1, #8, r3, asr #6
	strb	r1, [r2, #1]!
	cmp	r2, r0
	add	r3, r3, ip
	bne	.L6
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_GenerateIntensityMap, .-VC1_Vfmw_GenerateIntensityMap
	.align	2
	.type	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5, %function
VC1_Vfmw_UpdataLastPicRNDCTRL.part.5:
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
	ldrb	r3, [r2, #2415]	@ zero_extendqisi2
	tst	r3, #251
	moveq	r3, #1
	moveq	r1, r3
	beq	.L15
	cmp	r3, #1
	ldreqsb	r3, [r0, #10]
	ldrneb	r1, [r0, #10]	@ zero_extendqisi2
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	uxtbne	r3, r1
	uxtbeq	r1, r3
.L15:
	strb	r1, [r0, #10]
	strb	r3, [r2, #2434]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5, .-VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
	.align	2
	.global	emp_print
	.type	emp_print, %function
emp_print:
	UNWIND(.fnstart)
	@ args = 4, pretend = 12, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 1
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r1, r2, r3}
	UNWIND(.save {r1, r2, r3})
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-16)
	sub	fp, ip, #16
	mov	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	emp_print, .-emp_print
	.align	2
	.global	AbandonBitsLenthNoUse
	.type	AbandonBitsLenthNoUse, %function
AbandonBitsLenthNoUse:
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
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r2, r3
	bne	.L31
.L23:
	ldrb	r3, [r0, #-1]!	@ zero_extendqisi2
	add	r2, r2, #8
	cmp	r3, #0
	beq	.L23
	add	r0, r2, #1
.L24:
	tst	r3, #1
	bne	.L32
.L25:
	mov	r3, r3, lsr #1
	add	r2, r2, #1
	tst	r3, #1
	beq	.L25
	add	r0, r2, #1
	ldmfd	sp, {fp, sp, pc}
.L31:
	mov	r0, #1
	mov	r2, #0
	b	.L24
.L32:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AbandonBitsLenthNoUse, .-AbandonBitsLenthNoUse
	.align	2
	.global	VC1DEC_Init
	.type	VC1DEC_Init, %function
VC1DEC_Init:
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
	ldr	r7, .L37
	add	r4, r0, #45056
	mov	r8, r1
	movw	r2, #48840
	ldr	r9, [r4, #3768]
	mov	r1, #0
	ldr	r3, [r7, #48]
	mov	r5, r0
	blx	r3
	add	r0, r5, #48384
	add	r0, r0, #96
	str	r9, [r4, #3768]
	bl	ResetVoQueue
	add	r2, r5, #12288
	ldr	r3, [r8, #32]
	mov	r6, #1
	str	r8, [r5]
	mov	r0, r5
	strb	r6, [r2, #433]
	add	r3, r3, #255
	ldr	r1, [r8, #8]
	bic	r3, r3, #255
	add	ip, r3, #2048
	str	r3, [r4, #3352]
	str	ip, [r4, #3356]
	mov	r5, #0
	add	ip, r3, #4096
	str	r1, [r4, #3380]
	str	ip, [r4, #3360]
	add	r1, r3, #6144
	add	ip, r3, #8192
	str	r1, [r4, #3364]
	str	ip, [r4, #3368]
	add	r1, r3, #10240
	add	r3, r3, #12288
	str	r1, [r4, #3372]
	str	r3, [r4, #3376]
	strb	r6, [r2, #434]
	str	r5, [r4, #3312]
	str	r5, [r4, #3316]
	bl	VCTRL_GetChanIDByCtx
	ldr	r3, [r7, #68]
	cmn	r0, #1
	str	r0, [r4, #3776]
	beq	.L36
	ldr	r1, .L37+4
	mov	r0, #22
	blx	r3
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L36:
	mov	r0, r5
	ldr	r1, .L37+8
	blx	r3
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L38:
	.align	2
.L37:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	.LC13
	UNWIND(.fnend)
	.size	VC1DEC_Init, .-VC1DEC_Init
	.align	2
	.global	Vc1SMPSeqHdr
	.type	Vc1SMPSeqHdr, %function
Vc1SMPSeqHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	ldr	r6, .L59
	mov	r4, r2
	mov	r5, r0
	mov	r7, r1
	mov	r2, #32
	ldr	r3, [r6, #48]
	mov	r1, #0
	sub	r0, fp, #60
	blx	r3
	mov	r2, r7, asl #3
	mov	r1, r5
	sub	r0, fp, #60
	bl	BsInit
	mov	r1, #8
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #8
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #16
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #24
	sub	r0, fp, #60
	str	r5, [r4, #24]
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #8
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #16
	sub	r0, fp, #60
	bl	BsGet
	ldr	r3, [r4, #24]
	cmp	r3, #8192
	add	r0, r5, r0, lsl #24
	str	r0, [r4, #28]
	bgt	.L53
	cmp	r0, #8192
	bgt	.L54
	cmp	r3, #31
	ble	.L53
	cmp	r0, #31
	ble	.L54
	mov	r1, #2
	sub	r0, fp, #60
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3]
	cmp	r0, #1
	bhi	.L56
	mov	r1, #2
	sub	r0, fp, #60
	bl	BsGet
	subs	r5, r0, #0
	bne	.L56
	mov	r1, #3
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #5
	strb	r0, [r4, #4]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #5]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #6]
	sub	r0, fp, #60
	bl	BsGet
	subs	r7, r0, #0
	ldrne	r4, [r6, #68]
	movne	r0, r5
	bne	.L55
	mov	r1, #1
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #7]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #8]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #10]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	sub	r0, fp, #60
	bl	BsGet
	subs	r5, r0, #0
	bne	.L57
	mov	r1, #1
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #13]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #14]
	sub	r0, fp, #60
	bl	BsGet
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	mov	r1, #3
	cmp	r3, #0
	strb	r0, [r4, #15]
	sub	r0, fp, #60
	streqb	r5, [r4, #15]
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #16]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #17]
	sub	r0, fp, #60
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #18]
	sub	r0, fp, #60
	bl	BsGet
	sub	r0, fp, #60
	mov	r1, #32
	bl	BsGet
	cmp	r0, #0
	bne	.L58
.L41:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L58:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L59+4
	blx	r3
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L57:
	ldr	r4, [r6, #68]
	mov	r0, r7
.L55:
	ldr	r3, .L59+8
	mvn	r5, #0
	ldr	r2, .L59+12
	ldr	r1, .L59+16
	blx	r4
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L56:
	ldr	r4, [r6, #68]
	mov	r0, #0
	b	.L55
.L54:
	ldr	r4, [r6, #68]
	mov	r0, #0
	ldr	r3, .L59+20
	mvn	r5, #0
	ldr	r2, .L59+12
	ldr	r1, .L59+16
	blx	r4
	b	.L41
.L53:
	ldr	r4, [r6, #68]
	mov	r0, #0
	ldr	r3, .L59+24
	mvn	r5, #0
	ldr	r2, .L59+12
	ldr	r1, .L59+16
	blx	r4
	b	.L41
.L60:
	.align	2
.L59:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	.word	.LC18
	.word	.LANCHOR0
	.word	.LC16
	.word	.LC17
	.word	.LC15
	UNWIND(.fnend)
	.size	Vc1SMPSeqHdr, .-Vc1SMPSeqHdr
	.align	2
	.global	VC1_SetImgFormat
	.type	VC1_SetImgFormat, %function
VC1_SetImgFormat:
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
	add	r5, r0, #32768
	add	r3, r0, #45056
	mov	r6, r0
	add	r7, r0, #12288
	ldr	r1, [r5, #3252]
	ldr	r0, [r3, #3776]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r3, #1
	str	r3, [r4, #384]
	ldrb	r3, [r7, #427]	@ zero_extendqisi2
	cmp	r3, #3
	movne	r2, #0
	movne	r3, #7168
	strneb	r2, [r4, #372]
	beq	.L71
.L70:
	str	r3, [r4, #160]
	mov	r1, #0
	ldr	r3, [r5, #3196]
	mov	r0, r4
	str	r3, [r4, #168]
	ldr	r3, [r5, #3192]
	str	r3, [r4, #164]
	bl	SetAspectRatio
	ldr	r2, [r7, #228]
	ldr	r3, [r4, #104]
	ldr	ip, [r4, #32]
	ldr	r1, [r4, #192]
	add	r0, r3, r2
	str	r3, [r4, #88]
	add	r2, ip, r2
	str	r3, [r4, #120]
	add	r3, r3, r1
	str	r2, [r4, #36]
	add	r1, r0, r1
	str	r3, [r4, #96]
	str	r1, [r4, #100]
	str	r0, [r4, #108]
	str	r0, [r4, #92]
	str	ip, [r4, #48]
	bl	MEM_Phy2Vir
	ldr	r1, [r4, #92]
	mov	r3, #8
	mov	r2, #1
	str	r1, [r4, #124]
	str	r0, [r4, #52]
	ldr	r1, [r5, #3196]
	str	r1, [r4, #176]
	ldr	r1, [r5, #3192]
	strb	r2, [r4, #379]
	strb	r2, [r4, #377]
	str	r1, [r4, #172]
	str	r3, [r4, #388]
	str	r3, [r4, #396]
	str	r3, [r4, #392]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L71:
	mov	r3, #4
	strb	r3, [r4, #372]
	ldr	r2, [r6, #4]
	ldr	r3, [r4, #160]
	ldrb	r1, [r2, #8]	@ zero_extendqisi2
	ubfx	r2, r3, #10, #2
	add	r3, r1, #1
	orr	r3, r3, r2
	cmp	r3, #3
	movls	r3, r3, asl #10
	orrls	r3, r3, #4352
	movhi	r3, #4352
	b	.L70
	UNWIND(.fnend)
	.size	VC1_SetImgFormat, .-VC1_SetImgFormat
	.align	2
	.global	VC1DEC_Destroy
	.type	VC1DEC_Destroy, %function
VC1DEC_Destroy:
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
	.size	VC1DEC_Destroy, .-VC1DEC_Destroy
	.align	2
	.global	VC1DEC_RecycleImage
	.type	VC1DEC_RecycleImage, %function
VC1DEC_RecycleImage:
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
	cmp	r0, #0
	mov	r5, r1
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r4, r0, #45056
	mov	r2, #0
	ldr	r0, [r4, #3776]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #3776]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L76
	ldr	r1, [r5, #212]
	mov	r6, #0
	ldr	r0, [r4, #3776]
	bl	FreeUsdByDec
	str	r6, [r5, #212]
	ldr	r1, [r5, #216]
	ldr	r0, [r4, #3776]
	bl	FreeUsdByDec
	str	r6, [r5, #216]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L76:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1DEC_RecycleImage, .-VC1DEC_RecycleImage
	.align	2
	.global	VC1DEC_GetRemainImg
	.type	VC1DEC_GetRemainImg, %function
VC1DEC_GetRemainImg:
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
	add	r5, r0, #32768
	mov	r4, r0
	add	r7, r0, #12288
	ldr	r3, [r5, #3164]
	cmp	r3, #0
	beq	.L84
	ldr	r3, [r0]
	ldr	r3, [r3, #12]
	cmp	r3, #1
	beq	.L95
	add	r6, r0, #45056
	ldr	r1, [r5, #3248]
	ldr	r0, [r6, #3776]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L95
	ldr	r1, [r5, #3248]
	ldr	r0, [r6, #3776]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L93
.L95:
	add	r5, r4, #48384
	add	r5, r5, #96
.L83:
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	GetVoLastImageID
.L93:
	mov	r0, r4
	mov	r9, #0
	bl	VC1_SetImgFormat
	mov	r3, #1
	mov	r2, r3
	str	r3, [r8, #244]
	str	r9, [r8, #212]
	str	r9, [r8, #216]
	ldr	r1, [r8, #196]
	ldr	r0, [r6, #3776]
	bl	FSP_SetDisplay
	ldr	r3, [r5, #3164]
	mov	r1, #1
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	streqb	r2, [r3, #1]
	ldreq	r2, [r5, #3164]
	add	r5, r4, #48384
	add	r5, r5, #96
	moveq	r3, #3
	streqb	r9, [r2]
	mov	r2, r4
	streqb	r3, [r7, #425]
	mov	r3, r5
	ldr	r0, [r6, #3776]
	str	r8, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L81
	mov	r0, r4
	ldr	r1, [r8, #196]
	bl	VC1DEC_RecycleImage
	ldr	r1, [r8, #212]
	ldr	r0, [r6, #3776]
	mov	r4, #0
	bl	FreeUsdByDec
	str	r4, [r8, #212]
	ldr	r1, [r8, #216]
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	str	r4, [r8, #216]
	b	.L83
.L81:
	ldr	r3, [r8, #200]
	cmp	r3, #100
	bhi	.L83
	ldr	r3, [r8, #164]
	cmp	r3, #31
	bls	.L83
	ldr	r3, [r8, #168]
	cmp	r3, #31
	movhi	r0, #0
	bls	.L83
.L94:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L84:
	mvn	r0, #0
	b	.L94
	UNWIND(.fnend)
	.size	VC1DEC_GetRemainImg, .-VC1DEC_GetRemainImg
	.align	2
	.global	VC1_ArrangeVahbMem
	.type	VC1_ArrangeVahbMem, %function
VC1_ArrangeVahbMem:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	mov	r5, r1
	sub	r1, r1, #32
	movw	r3, #8160
	cmp	r1, r3
	mov	r7, r0
	mov	r6, r2
	bhi	.L97
	sub	r2, r2, #32
	cmp	r2, r3
	bhi	.L97
	add	r2, r0, #28160
	mov	r1, #0
	add	r2, r2, #48
	mov	r0, r1
.L100:
	str	r1, [r2, #-316]
	add	r1, r1, #1
	cmp	r1, #5
	strb	r0, [r2, #-1543]
	strb	r0, [r2, #-1544]
	add	r2, r2, #1536
	add	r2, r2, #8
	bne	.L100
	ldr	r3, [r7]
	ldr	r4, [r3, #776]
	ldr	r2, [r3, #28]
	cmp	r4, #0
	bne	.L101
	cmp	r2, #25
	beq	.L123
.L119:
	mov	r4, r1
	mov	r10, #3
	mov	r8, #2
.L102:
	ldr	r9, .L126
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #76
	ldr	r3, [r9, #48]
	blx	r3
	ldr	r2, [r7]
	str	r6, [fp, #-48]
	mov	r3, #0
	str	r5, [fp, #-68]
	ldr	r2, [r2, #28]
	str	r6, [fp, #-64]
	cmp	r2, #24
	str	r5, [fp, #-52]
	strb	r3, [fp, #-76]
	strb	r3, [fp, #-75]
	beq	.L112
	uxtb	r8, r8
	strb	r10, [fp, #-72]
	strb	r4, [fp, #-70]
.L115:
	add	r6, r7, #45056
	sub	r1, fp, #76
	strb	r8, [fp, #-69]
	mov	r5, #0
	ldr	r0, [r6, #3776]
	strb	r5, [fp, #-73]
	bl	FSP_ConfigInstance
	subs	r4, r0, #0
	bne	.L113
	ldr	r1, [r7]
	sub	r3, fp, #80
	ldr	r0, [r6, #3776]
	ldr	r2, [r1, #24]
	ldr	r1, [r1, #20]
	bl	FSP_ConfigFrameBuf
	cmp	r0, r5
	bne	.L124
.L117:
	mov	r4, #1
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L97:
	ldr	ip, .L126
	mov	r2, r5
	mov	r0, #0
	mov	r3, r6
	ldr	r1, .L126+4
	mov	r4, r0
	ldr	r5, [ip, #68]
	blx	r5
.L122:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L101:
	cmp	r2, #25
	bne	.L119
	ldr	r1, [r3, #736]
	ldr	r2, [r3, #740]
	cmp	r5, r1
	bhi	.L109
	cmp	r6, r2
	bhi	.L109
	ldr	r1, [r3, #764]
	ldr	r2, [r3, #760]
	cmp	r1, #0
	add	r10, r2, #2
	moveq	r8, #1
	bne	.L125
.L111:
	ldrb	r4, [r3, #784]	@ zero_extendqisi2
	b	.L102
.L113:
	ldr	r3, [r9, #68]
	mov	r0, r5
	ldr	r1, .L126+8
	mov	r4, r5
	blx	r3
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L123:
	ldr	r1, [r3, #736]
	cmp	r5, r1
	ldrhi	r0, [r3, #740]
	bhi	.L104
	ldr	r2, [r3, #740]
	cmp	r6, r2
	mov	r0, r2
	bhi	.L104
	add	r0, r7, #12288
	ldrb	r0, [r0, #424]	@ zero_extendqisi2
	tst	r0, #8
	bne	.L117
	ldr	ip, [r3, #764]
	ldr	r0, [r3, #760]
	cmp	ip, #0
	add	r10, r0, #2
	moveq	r8, #1
	beq	.L107
	add	r8, r0, #1
	cmp	r8, #17
	movcs	r8, #17
.L107:
	ldrb	r4, [r3, #784]	@ zero_extendqisi2
	mov	r6, r2
	mov	r5, r1
	b	.L102
.L112:
	mov	r8, #1
	strb	r4, [fp, #-70]
	strb	r8, [fp, #-72]
	b	.L115
.L109:
	ldr	ip, .L126
	mov	r3, r6
	str	r2, [sp, #4]
	mov	r0, #0
	str	r1, [sp]
	mov	r2, r5
	ldr	r1, .L126+12
	mov	r4, r0
	ldr	r5, [ip, #68]
	blx	r5
	b	.L122
.L124:
	ldr	r3, [r9, #68]
	mov	r0, r4
	ldr	r1, .L126+16
	blx	r3
	b	.L122
.L125:
	add	r8, r2, #1
	cmp	r8, #17
	movcs	r8, #17
	b	.L111
.L104:
	ldr	ip, .L126
	mov	r2, r5
	str	r0, [sp, #4]
	mov	r3, r6
	str	r1, [sp]
	mov	r0, #0
	ldr	r5, [ip, #68]
	ldr	r1, .L126+12
	blx	r5
	b	.L122
.L127:
	.align	2
.L126:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	.word	.LC23
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	VC1_ArrangeVahbMem, .-VC1_ArrangeVahbMem
	.align	2
	.global	VC1_WritePicMsg
	.type	VC1_WritePicMsg, %function
VC1_WritePicMsg:
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
	add	r7, r0, #32768
	add	r5, r0, #45056
	mov	r6, r0
	mov	r4, r1
	ldr	r0, [r5, #3776]
	ldr	r1, [r7, #3252]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L151
	add	r3, r6, #15808
	ldrsb	r1, [r3]
	add	r3, r6, #20480
	cmp	r1, #0
	bne	.L152
	strb	r1, [r4, #5]
	add	r2, r6, #12288
	ldrb	ip, [r3, #2588]	@ zero_extendqisi2
	strb	ip, [r4, #4]
	ldrb	ip, [r3, #2839]	@ zero_extendqisi2
	cmp	ip, #4
	moveq	ip, #3
	strb	ip, [r4, #3]
	ldr	ip, [r5, #3332]
	sub	ip, ip, #1
	strh	ip, [r4, #80]	@ movhi
	ldr	ip, [r5, #3328]
	strb	r1, [r4, #8]
	sub	ip, ip, #1
	strh	ip, [r4, #78]	@ movhi
	ldrb	ip, [r3, #2591]	@ zero_extendqisi2
	strb	r1, [r4, #9]
	strb	ip, [r4, #6]
	ldrb	ip, [r2, #432]	@ zero_extendqisi2
	strb	r1, [r4, #10]
	strb	r1, [r4, #11]
	strb	ip, [r4, #7]
	ldrb	ip, [r3, #2594]	@ zero_extendqisi2
	strb	ip, [r4, #13]
	ldrb	ip, [r3, #2598]	@ zero_extendqisi2
	strb	ip, [r4, #14]
	ldrb	ip, [r3, #2858]	@ zero_extendqisi2
	strb	ip, [r4, #12]
	ldrb	ip, [r3, #2868]	@ zero_extendqisi2
	strb	ip, [r4, #18]
	ldrb	ip, [r3, #2843]	@ zero_extendqisi2
	strb	ip, [r4, #19]
	ldrb	ip, [r3, #2842]	@ zero_extendqisi2
	strb	ip, [r4, #17]
	ldr	ip, [r3, #2928]
	strb	ip, [r4, #16]
	ldrb	ip, [r3, #2602]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L143
	ldrb	r1, [r3, #2842]	@ zero_extendqisi2
	cmp	r1, #8
	movhi	r1, #0
	movls	r1, #1
	strb	r1, [r4, #20]
.L144:
	ldrb	ip, [r3, #2862]	@ zero_extendqisi2
	add	r1, r4, #12288
	strb	ip, [r4, #24]
	ldrb	ip, [r3, #2861]	@ zero_extendqisi2
	strb	ip, [r4, #23]
	ldrb	ip, [r3, #2596]	@ zero_extendqisi2
	strb	ip, [r4, #22]
	ldrb	ip, [r3, #2860]	@ zero_extendqisi2
	strb	ip, [r4, #25]
	ldr	ip, [r3, #2872]
	strb	ip, [r4, #26]
	ldrb	ip, [r3, #2863]	@ zero_extendqisi2
	strb	ip, [r4, #21]
	ldrb	ip, [r3, #2847]	@ zero_extendqisi2
	strb	ip, [r4, #27]
	ldrb	ip, [r3, #2848]	@ zero_extendqisi2
	strb	ip, [r4, #28]
	ldr	ip, [r7, #3164]
	ldrb	ip, [ip, #1029]	@ zero_extendqisi2
	strb	ip, [r4, #30]
	ldr	ip, [r7, #3160]
	ldrb	ip, [ip, #1029]	@ zero_extendqisi2
	strb	ip, [r4, #29]
	ldrb	ip, [r3, #2845]	@ zero_extendqisi2
	strb	ip, [r4, #31]
	ldrb	ip, [r3, #2967]	@ zero_extendqisi2
	strb	ip, [r4, #32]
	ldrb	ip, [r3, #2857]	@ zero_extendqisi2
	strb	ip, [r4, #35]
	ldrb	ip, [r3, #2597]	@ zero_extendqisi2
	strb	ip, [r4, #36]
	ldrb	ip, [r3, #2853]	@ zero_extendqisi2
	strb	ip, [r4, #37]
	ldrb	ip, [r3, #2855]	@ zero_extendqisi2
	strb	ip, [r4, #38]
	ldrb	ip, [r3, #2856]	@ zero_extendqisi2
	strb	ip, [r4, #39]
	ldrb	ip, [r3, #2854]	@ zero_extendqisi2
	strb	ip, [r4, #40]
	ldr	ip, [r3, #2920]
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #42]
	ldr	ip, [r3, #2916]
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #43]
	ldr	ip, [r3, #2924]
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #45]
	ldrb	ip, [r3, #2840]	@ zero_extendqisi2
	strb	ip, [r4, #50]
	ldrb	ip, [r3, #2852]	@ zero_extendqisi2
	strb	ip, [r4, #49]
	ldrb	ip, [r3, #2851]	@ zero_extendqisi2
	strb	ip, [r4, #48]
	ldr	ip, [r3, #2932]
	str	ip, [r1, #84]
	ldrb	ip, [r3, #2600]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L153
	mov	ip, #0
	mov	lr, ip
	mov	r9, ip
	mov	r8, ip
.L147:
	strb	r8, [r4, #59]
	strb	r9, [r4, #60]
	strb	lr, [r4, #61]
	str	ip, [r0, #408]
	ldrb	r3, [r3, #2588]	@ zero_extendqisi2
	strb	r3, [r0, #386]
.L141:
	ldr	r3, [r7, #3260]
	add	r6, r6, #12672
	add	r6, r6, #53
	strh	r3, [r4, #72]	@ movhi
	ldr	r3, [r7, #3192]
	strh	r3, [r4, #74]	@ movhi
	ldr	r3, [r7, #3196]
	strh	r3, [r4, #76]	@ movhi
	ldrb	r3, [r2, #435]	@ zero_extendqisi2
	strb	r3, [r4, #63]
	ldrb	r3, [r2, #436]	@ zero_extendqisi2
	strb	r3, [r4, #62]
	ldr	r2, [r7, #3176]
	adds	r3, r2, #127
	addmi	r3, r2, #254
	mov	r3, r3, asr #7
	mov	r3, r3, asl #4
	str	r3, [r1, #116]
	ldr	r3, [r5, #3352]
	str	r3, [r1, #120]
	ldr	r3, [r5, #3356]
	str	r3, [r1, #124]
	ldr	r3, [r5, #3360]
	str	r3, [r1, #128]
	ldr	r3, [r5, #3364]
	str	r3, [r1, #132]
	ldr	r3, [r5, #3368]
	str	r3, [r1, #136]
	ldr	r3, [r5, #3372]
	str	r3, [r1, #140]
	ldr	r3, [r5, #3376]
	str	r3, [r1, #144]
	str	r6, [r4, #64]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L152:
	ldr	r2, [r3, #2980]
	movw	lr, #1544
	strb	r2, [r4, #5]
	ldrb	r2, [r3, #2604]	@ zero_extendqisi2
	strb	r2, [r4, #4]
	ldrb	r2, [r3, #2937]	@ zero_extendqisi2
	cmp	r2, #4
	moveq	r2, #3
	strb	r2, [r4, #3]
	ldr	r2, [r3, #2980]
	cmp	r2, #3
	ldr	r2, [r5, #3332]
	addeq	r2, r2, #1
	addeq	r2, r2, r2, lsr #31
	moveq	r2, r2, asr #1
	sub	r2, r2, #1
	strh	r2, [r4, #80]	@ movhi
	ldr	ip, [r5, #3328]
	add	r2, r6, #12288
	sub	ip, ip, #1
	strh	ip, [r4, #78]	@ movhi
	ldrb	r1, [r3, #2977]	@ zero_extendqisi2
	strb	r1, [r4, #8]
	ldrb	r1, [r3, #2780]	@ zero_extendqisi2
	strb	r1, [r4, #6]
	ldrb	r1, [r3, #2968]	@ zero_extendqisi2
	strb	r1, [r4, #9]
	ldrb	r1, [r2, #432]	@ zero_extendqisi2
	strb	r1, [r4, #7]
	ldr	ip, [r7, #3216]
	mla	ip, lr, ip, r2
	add	ip, ip, #15360
	ldrb	r1, [ip, #43]	@ zero_extendqisi2
	strb	r1, [r4, #10]
	ldr	r1, [r7, #3232]
	mla	r1, lr, r1, r2
	add	r1, r1, #15360
	add	r1, r1, #40
	ldrb	r1, [r1, #3]	@ zero_extendqisi2
	strb	r1, [r4, #11]
	ldrb	r1, [r3, #2966]	@ zero_extendqisi2
	strb	r1, [r4, #15]
	ldrb	r1, [r3, #2781]	@ zero_extendqisi2
	strb	r1, [r4, #13]
	ldrb	r1, [r3, #2785]	@ zero_extendqisi2
	strb	r1, [r4, #14]
	ldrb	r1, [r3, #2936]	@ zero_extendqisi2
	strb	r1, [r4, #12]
	ldrb	r1, [r3, #3104]	@ zero_extendqisi2
	strb	r1, [r4, #18]
	ldrb	r1, [r3, #2939]	@ zero_extendqisi2
	strb	r1, [r4, #19]
	ldrb	r1, [r3, #2946]	@ zero_extendqisi2
	strb	r1, [r4, #17]
	ldr	r1, [r3, #3052]
	strb	r1, [r4, #16]
	ldrb	r1, [r3, #2786]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L134
	ldrb	r1, [r3, #2946]	@ zero_extendqisi2
	cmp	r1, #8
	movhi	r1, #0
	movls	r1, #1
	strb	r1, [r4, #20]
.L135:
	ldrb	ip, [r3, #3098]	@ zero_extendqisi2
	add	r1, r4, #12288
	strb	ip, [r4, #24]
	ldrb	ip, [r3, #3097]	@ zero_extendqisi2
	strb	ip, [r4, #23]
	ldrb	ip, [r3, #2783]	@ zero_extendqisi2
	strb	ip, [r4, #22]
	ldrb	ip, [r3, #3096]	@ zero_extendqisi2
	strb	ip, [r4, #25]
	ldr	ip, [r3, #3108]
	strb	ip, [r4, #26]
	ldrb	ip, [r3, #3099]	@ zero_extendqisi2
	strb	ip, [r4, #21]
	ldrb	ip, [r3, #2950]	@ zero_extendqisi2
	strb	ip, [r4, #27]
	ldrb	ip, [r3, #2951]	@ zero_extendqisi2
	strb	ip, [r4, #28]
	ldrb	ip, [r3, #2969]	@ zero_extendqisi2
	strb	ip, [r4, #34]
	ldrb	ip, [r3, #2961]	@ zero_extendqisi2
	strb	ip, [r4, #33]
	ldrb	lr, [r3, #2977]	@ zero_extendqisi2
	ldr	ip, [r7, #3164]
	add	ip, ip, lr
	ldrb	ip, [ip, #1029]	@ zero_extendqisi2
	strb	ip, [r4, #30]
	ldr	ip, [r7, #3160]
	ldrb	lr, [r3, #2977]	@ zero_extendqisi2
	add	ip, ip, lr
	ldrb	ip, [ip, #1029]	@ zero_extendqisi2
	strb	ip, [r4, #29]
	ldrb	ip, [r3, #2949]	@ zero_extendqisi2
	strb	ip, [r4, #31]
	ldrb	ip, [r3, #2967]	@ zero_extendqisi2
	strb	ip, [r4, #32]
	ldrb	ip, [r3, #2960]	@ zero_extendqisi2
	strb	ip, [r4, #35]
	ldrb	ip, [r3, #2784]	@ zero_extendqisi2
	strb	ip, [r4, #36]
	ldrb	ip, [r3, #2956]	@ zero_extendqisi2
	strb	ip, [r4, #37]
	ldrb	ip, [r3, #2958]	@ zero_extendqisi2
	strb	ip, [r4, #38]
	ldrb	ip, [r3, #2959]	@ zero_extendqisi2
	strb	ip, [r4, #39]
	ldrb	ip, [r3, #2957]	@ zero_extendqisi2
	strb	ip, [r4, #40]
	ldrb	ip, [r3, #2973]	@ zero_extendqisi2
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #46]
	ldrb	ip, [r3, #2971]	@ zero_extendqisi2
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #42]
	ldrb	ip, [r3, #2975]	@ zero_extendqisi2
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #44]
	ldrb	ip, [r3, #2976]	@ zero_extendqisi2
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #41]
	ldrb	ip, [r3, #2970]	@ zero_extendqisi2
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #43]
	ldrb	ip, [r3, #2974]	@ zero_extendqisi2
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #47]
	ldrb	ip, [r3, #2972]	@ zero_extendqisi2
	clz	ip, ip
	mov	ip, ip, lsr #5
	strb	ip, [r4, #45]
	ldrb	ip, [r3, #2938]	@ zero_extendqisi2
	strb	ip, [r4, #50]
	ldrb	ip, [r3, #2955]	@ zero_extendqisi2
	strb	ip, [r4, #49]
	ldrb	ip, [r3, #2954]	@ zero_extendqisi2
	strb	ip, [r4, #48]
	ldrb	ip, [r3, #2965]	@ zero_extendqisi2
	strb	ip, [r4, #53]
	ldrb	ip, [r3, #2962]	@ zero_extendqisi2
	strb	ip, [r4, #54]
	ldrb	ip, [r3, #2963]	@ zero_extendqisi2
	strb	ip, [r4, #51]
	ldrb	ip, [r3, #2964]	@ zero_extendqisi2
	strb	ip, [r4, #52]
	ldr	ip, [r3, #3084]
	str	ip, [r1, #84]
	ldr	ip, [r5, #3304]
	str	ip, [r1, #88]
	ldr	ip, [r5, #3308]
	str	ip, [r1, #92]
	ldrb	ip, [r3, #2789]	@ zero_extendqisi2
	strb	ip, [r4, #55]
	ldrb	ip, [r3, #2790]	@ zero_extendqisi2
	strb	ip, [r4, #56]
	ldrb	ip, [r3, #2791]	@ zero_extendqisi2
	strb	ip, [r4, #57]
	ldrb	ip, [r3, #2792]	@ zero_extendqisi2
	strb	ip, [r4, #58]
	ldr	ip, [r3, #2980]
	cmp	ip, #3
	beq	.L154
	ldrb	ip, [r3, #2789]	@ zero_extendqisi2
	strb	ip, [r0, #381]
	ldrb	ip, [r3, #2790]	@ zero_extendqisi2
	strb	ip, [r0, #382]
	ldrb	ip, [r3, #2791]	@ zero_extendqisi2
	strb	ip, [r0, #383]
	ldrb	ip, [r3, #2792]	@ zero_extendqisi2
	strb	ip, [r0, #384]
.L140:
	ldrb	r3, [r3, #2604]	@ zero_extendqisi2
	strb	r3, [r0, #386]
	ldrb	r3, [r2, #435]	@ zero_extendqisi2
	strb	r3, [r4, #63]
	b	.L141
.L143:
	cmp	ip, #1
	beq	.L155
	cmp	ip, #2
	movne	r1, #1
	strb	r1, [r4, #20]
	b	.L144
.L134:
	cmp	r1, #1
	beq	.L156
	cmp	r1, #2
	moveq	r1, #0
	movne	r1, #1
	strb	r1, [r4, #20]
	b	.L135
.L156:
	ldrb	r1, [r3, #2947]	@ zero_extendqisi2
	adds	r1, r1, #0
	movne	r1, #1
	strb	r1, [r4, #20]
	b	.L135
.L155:
	ldrb	r1, [r3, #2844]	@ zero_extendqisi2
	adds	r1, r1, #0
	movne	r1, #1
	strb	r1, [r4, #20]
	b	.L144
.L154:
	ldrb	ip, [r3, #2977]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L139
	ldrb	ip, [r3, #2789]	@ zero_extendqisi2
	strb	ip, [r0, #381]
	ldrb	ip, [r3, #2790]	@ zero_extendqisi2
	strb	ip, [r0, #382]
	ldrb	ip, [r3, #2791]	@ zero_extendqisi2
	strb	ip, [r0, #383]
	ldrb	ip, [r3, #2792]	@ zero_extendqisi2
	strb	ip, [r0, #384]
	ldrb	ip, [r3, #2977]	@ zero_extendqisi2
.L139:
	cmp	ip, #1
	bne	.L140
	ldrb	ip, [r3, #2789]	@ zero_extendqisi2
	strb	ip, [r0, #376]
	ldrb	ip, [r3, #2790]	@ zero_extendqisi2
	strb	ip, [r0, #377]
	ldrb	ip, [r3, #2791]	@ zero_extendqisi2
	strb	ip, [r0, #378]
	ldrb	ip, [r3, #2792]	@ zero_extendqisi2
	strb	ip, [r0, #379]
	b	.L140
.L153:
	ldr	lr, [r7, #3216]
	movw	r9, #1544
	ldr	ip, [r7, #3232]
	ldrb	r8, [r3, #2839]	@ zero_extendqisi2
	mla	lr, r9, lr, r2
	sub	r8, r8, #2
	mla	ip, r9, ip, r2
	tst	r8, #253
	add	lr, lr, #14336
	ldrneb	r8, [r3, #2838]	@ zero_extendqisi2
	add	ip, ip, #14336
	ldrb	r9, [lr, #42]	@ zero_extendqisi2
	ldrb	lr, [ip, #42]	@ zero_extendqisi2
	movne	ip, r8
	moveq	ip, lr
	moveq	r8, lr
	b	.L147
.L151:
	ldr	r3, .L157
	movw	r2, #1070
	ldr	r1, .L157+4
	mov	r0, #22
	ldr	r3, [r3, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L158:
	.align	2
.L157:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	UNWIND(.fnend)
	.size	VC1_WritePicMsg, .-VC1_WritePicMsg
	.align	2
	.global	VC1_WriteSliceMsg
	.type	VC1_WriteSliceMsg, %function
VC1_WriteSliceMsg:
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
	add	r3, r0, #20480
	mov	r2, r1
	ldr	ip, .L160
	add	r1, r0, #23296
	ldr	lr, [r3, #2836]
	add	r0, r2, #84
	add	r1, r1, #24
	ldr	ip, [ip, #52]
	strb	lr, [r2, #70]
	ldr	r3, [r3, #2836]
	mov	r2, r3, asl #6
	sub	r2, r2, r3, asl #4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L161:
	.align	2
.L160:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_WriteSliceMsg, .-VC1_WriteSliceMsg
	.align	2
	.global	VC1_CfgVDH
	.type	VC1_CfgVDH, %function
VC1_CfgVDH:
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
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L163
	add	r3, r0, #8192
	ldr	r3, [r3, #2556]
	cmp	r3, #3
	beq	.L168
.L163:
	add	r3, r0, #32768
	add	r6, r1, #12288
	ldr	r3, [r3, #2912]
	sub	r3, r3, #1
	str	r3, [r6, #164]
.L164:
	add	r5, r0, #20480
	ldr	r3, [r6, #244]
	movw	r4, #1544
	mov	ip, #0
	ldr	r2, [r5, #2776]
	and	lr, r3, #1
	cmp	r2, #0
	add	r3, r2, #63
	movlt	r2, r3
	mov	r2, r2, asr #6
	mov	r2, r2, asl #4
	add	r3, r2, #81920
	add	r3, r3, #1
	orr	r3, r3, lr, asl #30
	str	r3, [r6, #168]
	ldr	lr, [r5, #2808]
	ldr	r3, [r5, #2792]
	ldr	r2, [r5, #2736]
	mla	lr, r4, lr, r0
	mla	r0, r4, r3, r0
	ldr	r2, [r2, #1180]
	add	r3, lr, #15104
	add	r3, r3, #24
	and	r2, r2, #3
	add	r0, r0, #15104
	ldr	r3, [r3, #4]
	add	r0, r0, #24
	mov	r2, r2, asl #4
	ldr	r0, [r0, #4]
	and	r3, r3, #3
	strb	ip, [r1, #69]
	orr	r3, r2, r3, asl #2
	and	r2, r0, #3
	orr	r3, r3, r2
	strb	r3, [r1, #68]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L168:
	add	r2, r0, #32768
	add	r6, r1, #12288
	ldr	r3, [r2, #2908]
	ldr	r2, [r2, #2904]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	mul	r3, r2, r3
	sub	r3, r3, #1
	str	r3, [r6, #164]
	b	.L164
	UNWIND(.fnend)
	.size	VC1_CfgVDH, .-VC1_CfgVDH
	.align	2
	.global	VC1_Vfmw_GenerateDecPara
	.type	VC1_Vfmw_GenerateDecPara, %function
VC1_Vfmw_GenerateDecPara:
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
	.size	VC1_Vfmw_GenerateDecPara, .-VC1_Vfmw_GenerateDecPara
	.align	2
	.global	VC1DEC_GetImageBuffer
	.type	VC1DEC_GetImageBuffer, %function
VC1DEC_GetImageBuffer:
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
	ldrb	r2, [r3, #427]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L181
.L171:
	add	r5, r4, #45056
	ldr	r0, [r5, #3776]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L173
	ldr	r0, [r5, #3776]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L182
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L181:
	ldrb	r3, [r3, #433]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L171
.L173:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L182:
	add	r1, r4, #48384
	ldr	r0, [r5, #3776]
	add	r1, r1, #96
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1DEC_GetImageBuffer, .-VC1DEC_GetImageBuffer
	.align	2
	.global	VC1_Vfmw_GetImageBuffer
	.type	VC1_Vfmw_GetImageBuffer, %function
VC1_Vfmw_GetImageBuffer:
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
	add	r6, r0, #45056
	add	r4, r0, #32768
	mov	r5, r0
	mov	r1, #1
	ldr	r0, [r6, #3776]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #3252]
	blt	.L203
	add	r3, r5, #26624
	add	r2, r3, #40
	ldrh	r3, [r3, #40]
	cmp	r3, #0
	beq	.L187
	add	r3, r5, #28160
	add	lr, r5, #34304
	add	r3, r3, #48
	add	lr, lr, #80
.L190:
	ldrh	ip, [r3]
	mov	r2, r3
	add	r3, r3, #1536
	cmp	ip, #0
	add	r3, r3, #8
	beq	.L187
	cmp	r3, lr
	bne	.L190
	mov	r1, r0
	mov	r2, #1
	ldr	r0, [r6, #3776]
	bl	FSP_ClearLogicFs
	ldr	r3, .L204
	ldr	r1, .L204+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	add	r3, r5, #26624
	add	r5, r5, #34304
	add	r3, r3, #41
	add	r5, r5, #81
	mov	r2, #0
.L192:
	strb	r2, [r3]
	add	r3, r3, #1536
	strb	r2, [r3, #-1537]
	add	r3, r3, #8
	cmp	r3, r5
	bne	.L192
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L187:
	mov	r3, #0
	str	r2, [r4, #3160]
	mov	r1, #1
	strb	r1, [r2, #1]
.L189:
	ldr	r1, [r4, #3160]
	uxtb	r2, r3
	add	r1, r1, r3
	strb	r2, [r1, #3]
	ldr	r1, [r4, #3160]
	add	r1, r1, r3
	strb	r2, [r1, #259]
	ldr	r1, [r4, #3160]
	add	r1, r1, r3
	strb	r2, [r1, #515]
	ldr	r1, [r4, #3160]
	add	r1, r1, r3
	add	r3, r3, #1
	cmp	r3, #256
	strb	r2, [r1, #771]
	bne	.L189
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L203:
	ldr	r9, .L204
	mov	r0, #0
	ldr	r1, .L204+8
	ldr	r3, [r9, #68]
	blx	r3
	ldr	r1, [r4, #3248]
	ldr	r0, [r6, #3776]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L185
	ldr	r1, [r7, #212]
	mov	r8, #0
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r7, #216]
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r7, #220]
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r7, #224]
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	str	r8, [r7, #212]
	str	r8, [r7, #216]
	mov	r2, #1
	str	r8, [r7, #220]
	str	r8, [r7, #224]
	ldr	r1, [r4, #3248]
	ldr	r0, [r6, #3776]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #3244]
	ldr	r0, [r6, #3776]
	bl	FSP_ClearLogicFs
	str	r8, [r4, #3244]
	str	r8, [r4, #3248]
	ldr	r0, [r6, #3776]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #3248]
	str	r0, [r4, #3244]
.L185:
	add	r1, r5, #48384
	mov	r5, #0
	add	r1, r1, #96
	str	r5, [r4, #3240]
	ldr	r0, [r6, #3776]
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r9, #68]
	ldr	r1, .L204+12
	mov	r0, #1
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L205:
	.align	2
.L204:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC25
	.word	.LC26
	UNWIND(.fnend)
	.size	VC1_Vfmw_GetImageBuffer, .-VC1_Vfmw_GetImageBuffer
	.align	2
	.global	VC1_Vfmw_MemMove
	.type	VC1_Vfmw_MemMove, %function
VC1_Vfmw_MemMove:
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
	add	r0, r0, #20480
	ldr	ip, .L207
	ldr	r3, [r0, #2756]
	ldr	r2, [r0, #2776]
	add	r3, r3, #1
	ldr	r1, [r0, #2740]
	ldr	r0, [r0, #2736]
	add	r3, r3, r3, lsr #31
	ldr	ip, [ip, #52]
	ldr	r1, [r1, #1064]
	mov	r3, r3, asr #1
	ldr	r0, [r0, #1064]
	mov	r3, r3, asl #5
	mul	r3, r2, r3
	add	r2, r3, r3, lsl #1
	mov	r2, r2, asr #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L208:
	.align	2
.L207:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_MemMove, .-VC1_Vfmw_MemMove
	.align	2
	.global	VC1_Vfmw_BuildRefList
	.type	VC1_Vfmw_BuildRefList, %function
VC1_Vfmw_BuildRefList:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 536
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #540)
	sub	sp, sp, #540
	ldr	r5, .L284
	mov	r10, r0
	mov	r4, r1
	mov	r8, r2
	mov	r1, #0
	mov	r2, #256
	ldr	r6, [r5, #48]
	sub	r0, fp, #556
	mov	r9, r3
	blx	r6
	ldr	r3, [r5, #48]
	mov	r2, #256
	mov	r1, #0
	sub	r0, fp, #300
	blx	r3
	add	r0, r10, #23040
	ldr	r3, [r5, #48]
	mov	r2, #16
	mov	r1, #0
	add	r0, r0, #224
	blx	r3
	add	r0, r10, #23040
	ldr	r3, [r5, #48]
	add	r0, r0, #240
	mov	r2, #16
	mov	r1, #0
	blx	r3
	ldrsb	r3, [r10, #4]
	bics	r3, r3, #2
	bne	.L210
	cmp	r4, #1
	beq	.L271
	cmp	r4, #2
	addne	r3, r10, #20480
	beq	.L272
.L219:
	mov	r0, #1
	mov	r2, #0
	str	r2, [r3, #2804]
	str	r2, [r3, #2788]
.L253:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L210:
	add	r5, r10, #8192
	ldrb	r3, [r5, #2516]	@ zero_extendqisi2
	cmp	r3, #1
	ldrb	r3, [r5, #2553]	@ zero_extendqisi2
	beq	.L273
	cmp	r3, #0
	add	r3, r10, #20480
	beq	.L274
.L229:
	ldr	r2, [r3, #2744]
	ldr	r6, [r2, #1228]
	mov	r7, r6
.L228:
	cmp	r4, #1
	beq	.L275
.L230:
	cmp	r4, #2
	bne	.L219
	cmp	r8, #0
	mov	r1, #0
	mov	r2, #1
	str	r4, [r3, #2804]
	str	r4, [r3, #2788]
	strb	r1, [r3, #2784]
	strb	r2, [r3, #2785]
	beq	.L242
	cmp	r9, r1
	beq	.L276
.L242:
	ldr	r2, [r3, #2744]
	ldr	lr, [r3, #2736]
	ldr	ip, [r2, #1228]
.L269:
	ldr	r0, [r3, #2740]
	mov	r1, #1
	str	ip, [r3, #2792]
	mov	r2, #0
	strb	r1, [r3, #2801]
	strb	r2, [r3, #2800]
	ldr	r1, [r0, #1228]
	str	r1, [r3, #2808]
	ldr	r0, [r0, #1228]
	str	r0, [r3, #2812]
	ldr	r0, [r5, #2640]
	ldr	r7, [lr, #1228]
	cmp	r0, #1
	bls	.L277
	bics	r0, r0, #2
	beq	.L248
.L247:
	movw	lr, #1544
	mov	r2, #0
	mul	r7, lr, r7
	str	r2, [fp, #-572]
	mul	r1, lr, r1
	mov	r3, r10
	mul	r0, lr, ip
	add	r2, r7, #13952
	str	r2, [fp, #-568]
	add	r2, r7, #14208
	str	r2, [fp, #-560]
	add	ip, r1, #14720
	ldr	r2, [fp, #-568]
	add	r9, r0, #13952
	add	r5, r1, #13952
	add	r4, r1, #14208
	add	r2, r2, #2
	str	r2, [fp, #-568]
	ldr	r2, [fp, #-560]
	add	lr, r1, #14464
	add	ip, ip, #2
	add	r1, r7, #14464
	add	r8, r0, #14208
	add	r6, r0, #14464
	add	r2, r2, #2
	add	r1, r1, #2
	add	r0, r0, #14720
	str	r1, [fp, #-576]
	add	r7, r7, #14720
	add	r1, r10, ip
	add	r9, r9, #2
	ldr	ip, [fp, #-568]
	add	r9, r10, r9
	add	r6, r6, #2
	add	r0, r0, #2
	add	r5, r5, #2
	add	r4, r4, #2
	add	lr, lr, #2
	add	r7, r7, #2
	str	r9, [fp, #-560]
	add	r9, r10, r2
	ldr	r2, [fp, #-576]
	add	r8, r8, #2
	add	r6, r10, r6
	add	r0, r10, r0
	add	r5, r10, r5
	add	r4, r10, r4
	add	lr, r10, lr
	add	ip, r10, ip
	add	r7, r10, r7
	add	r8, r10, r8
	str	r8, [fp, #-564]
	add	r8, r10, r2
	mov	r2, #0
	str	r1, [fp, #-568]
.L249:
	ldr	r1, [fp, #-560]
	add	r2, r2, #1
	cmp	r2, #256
	add	r3, r3, #1
	ldrb	r10, [r1, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-560]
	ldr	r1, [fp, #-564]
	strb	r10, [r3, #12]
	ldrb	r10, [r1, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #268]
	ldrb	r10, [r6, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-564]
	ldr	r1, [fp, #-568]
	strb	r10, [r3, #524]
	ldrb	r10, [r0, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #780]
	ldrb	r10, [r5, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #1036]
	ldrb	r10, [r4, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #1292]
	ldrb	r10, [lr, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #1548]
	ldrb	r10, [r1, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #1804]
	ldrb	r10, [ip, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-568]
	strb	r10, [r3, #2060]
	ldrb	r10, [r9, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #2316]
	ldrb	r10, [r8, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #2572]
	ldrb	r10, [r7, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #2828]
	bne	.L249
	mov	r0, #1
.L281:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L274:
	ldr	r1, [r3, #2744]
	cmp	r4, #1
	ldr	r2, [r3, #2740]
	ldr	r6, [r1, #1228]
	ldr	r7, [r2, #1228]
	bne	.L230
.L275:
	ldrb	r2, [r5, #2544]	@ zero_extendqisi2
	cmp	r8, #0
	mov	r1, #0
	strb	r4, [r3, #2785]
	add	r2, r2, #1
	str	r1, [r3, #2804]
	str	r2, [r3, #2788]
	strb	r1, [r3, #2784]
	beq	.L231
	cmp	r9, r1
	beq	.L278
.L231:
	ldr	r2, [r3, #2744]
	ldr	r1, [r3, #2736]
	ldr	r4, [r2, #1228]
.L268:
	str	r4, [r3, #2792]
	ldr	r2, [r2, #1228]
	str	r2, [r3, #2796]
	ldr	r3, [r5, #2640]
	ldr	r8, [r1, #1228]
	cmp	r3, #1
	bls	.L279
.L235:
	bics	r2, r3, #2
	bne	.L236
	ldrb	r2, [r5, #2526]	@ zero_extendqisi2
	cmp	r2, #4
	beq	.L280
.L236:
	movw	r1, #1544
	mov	r3, r10
	mul	r4, r1, r4
	mov	r2, #0
	mul	r8, r1, r8
	add	r7, r4, #13952
	add	r6, r4, #14208
	add	r5, r4, #14464
	add	r0, r4, #14720
	add	lr, r8, #14208
	add	r4, r8, #13952
	add	ip, r8, #14464
	add	r8, r8, #14720
	add	r7, r7, #2
	add	r6, r6, #2
	add	r5, r5, #2
	add	r0, r0, #2
	add	r4, r4, #2
	add	lr, lr, #2
	add	ip, ip, #2
	add	r8, r8, #2
	add	r7, r10, r7
	add	r6, r10, r6
	add	r5, r10, r5
	add	r0, r10, r0
	add	r4, r10, r4
	add	lr, r10, lr
	add	ip, r10, ip
	add	r1, r10, r8
.L241:
	ldrb	r8, [r7, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r2, #256
	add	r3, r3, #1
	strb	r8, [r3, #12]
	ldrb	r8, [r6, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #268]
	ldrb	r8, [r5, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #524]
	ldrb	r8, [r0, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #780]
	ldrb	r8, [r4, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #2060]
	ldrb	r8, [lr, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #2316]
	ldrb	r8, [ip, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #2572]
	ldrb	r8, [r1, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #2828]
	bne	.L241
	mov	r0, #1
	b	.L281
.L271:
	add	r2, r10, #20480
	ldr	r1, [r2, #2744]
	str	r4, [r2, #2788]
	str	r3, [r2, #2804]
	strb	r3, [r2, #2784]
	ldr	r4, [r1, #1228]
	str	r4, [r2, #2792]
	ldrb	r3, [r10, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r10, #8192
	beq	.L212
	ldr	r2, [r3, #2556]
	ldrb	r5, [r3, #2528]	@ zero_extendqisi2
	cmp	r2, #2
	ldrb	r6, [r3, #2529]	@ zero_extendqisi2
	ldrb	r2, [r3, #2526]	@ zero_extendqisi2
	beq	.L282
.L213:
	cmp	r2, #4
	beq	.L214
.L215:
	movw	r2, #1544
	add	r6, r10, #12
	mul	r2, r2, r4
	add	r5, r10, #268
	add	r4, r10, #524
	add	lr, r10, #780
	mov	r3, #0
	add	ip, r2, #13952
	add	r0, r2, #14208
	add	r1, r2, #14464
	add	r2, r2, #14720
	add	ip, ip, #2
	add	r0, r0, #2
	add	r1, r1, #2
	add	r2, r2, #2
	add	ip, r10, ip
	add	r0, r10, r0
	add	r1, r10, r1
	add	r2, r10, r2
.L217:
	ldrb	r7, [ip, #1]!	@ zero_extendqisi2
	add	r3, r3, #1
	cmp	r3, #256
	strb	r7, [r6, #1]!
	ldrb	r7, [r0, #1]!	@ zero_extendqisi2
	strb	r7, [r5, #1]!
	ldrb	r7, [r1, #1]!	@ zero_extendqisi2
	strb	r7, [r4, #1]!
	ldrb	r7, [r2, #1]!	@ zero_extendqisi2
	strb	r7, [lr, #1]!
	bne	.L217
	mov	r0, #1
	b	.L281
.L273:
	cmp	r3, #0
	add	r3, r10, #20480
	beq	.L229
	ldr	r1, [r3, #2740]
	ldr	r2, [r3, #2744]
	ldr	r6, [r1, #1228]
	ldr	r7, [r2, #1228]
	b	.L228
.L272:
	add	r2, r10, #20480
	mov	r1, #1
	ldr	r0, [r2, #2744]
	str	r1, [r2, #2804]
	str	r1, [r2, #2788]
	strb	r3, [r2, #2784]
	ldr	r1, [r2, #2740]
	ldr	r4, [r0, #1228]
	strb	r3, [r2, #2800]
	str	r4, [r2, #2792]
	ldr	r3, [r1, #1228]
	str	r3, [r2, #2808]
	str	r3, [fp, #-560]
	ldrb	r3, [r10, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r10, #8192
	ldrneb	r5, [r3, #2528]	@ zero_extendqisi2
	ldrneb	r6, [r3, #2529]	@ zero_extendqisi2
	ldreqb	r5, [r3, #2425]	@ zero_extendqisi2
	ldreqb	r6, [r3, #2426]	@ zero_extendqisi2
	ldrneb	r3, [r3, #2526]	@ zero_extendqisi2
	ldreqb	r3, [r3, #2423]	@ zero_extendqisi2
	cmp	r3, #4
	beq	.L283
.L222:
	ldr	r0, [fp, #-560]
	movw	r1, #1544
	mul	r4, r1, r4
	mov	r3, r10
	mul	r0, r1, r0
	mov	r2, #0
	add	r7, r4, #13952
	add	r6, r4, #14208
	add	r5, r4, #14464
	add	r1, r4, #14720
	add	lr, r0, #14208
	add	r4, r0, #13952
	add	ip, r0, #14464
	add	r0, r0, #14720
	add	r7, r7, #2
	add	r6, r6, #2
	add	r5, r5, #2
	add	r1, r1, #2
	add	r4, r4, #2
	add	lr, lr, #2
	add	ip, ip, #2
	add	r0, r0, #2
	add	r7, r10, r7
	add	r6, r10, r6
	add	r5, r10, r5
	add	r1, r10, r1
	add	r4, r10, r4
	add	lr, r10, lr
	add	ip, r10, ip
	add	r0, r10, r0
.L224:
	ldrb	r8, [r7, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r2, #256
	add	r3, r3, #1
	strb	r8, [r3, #12]
	ldrb	r8, [r6, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #268]
	ldrb	r8, [r5, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #524]
	ldrb	r8, [r1, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #780]
	ldrb	r8, [r4, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #1036]
	ldrb	r8, [lr, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #1292]
	ldrb	r8, [ip, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #1548]
	ldrb	r8, [r0, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #1804]
	bne	.L224
	mov	r0, #1
	b	.L281
.L212:
	ldrb	r5, [r3, #2425]	@ zero_extendqisi2
	ldrb	r6, [r3, #2426]	@ zero_extendqisi2
	ldrb	r2, [r3, #2423]	@ zero_extendqisi2
	b	.L213
.L248:
	ldrb	r3, [r5, #2526]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L247
	b	.L253
.L278:
	ldr	r1, [r3, #2736]
	ldr	r2, [r3, #2744]
	ldr	r4, [r1, #1228]
	b	.L268
.L276:
	ldr	lr, [r3, #2736]
	ldr	ip, [lr, #1228]
	b	.L269
.L279:
	ldrb	r3, [r5, #2526]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L236
	ldrb	r9, [r5, #2528]	@ zero_extendqisi2
	mov	r3, #0
	ldrb	r2, [r5, #2529]	@ zero_extendqisi2
	sub	r0, fp, #556
	mov	r1, r9
	str	r2, [fp, #-560]
	bl	VC1_Vfmw_GenerateIntensityMap
	ldr	r2, [fp, #-560]
	mov	r1, r9
	sub	r0, fp, #300
	mov	r3, #1
	bl	VC1_Vfmw_GenerateIntensityMap
	movw	r2, #1544
	mul	r2, r2, r6
	mov	r1, #0
	add	r0, r2, #13952
	add	r2, r2, #14208
	add	r0, r0, #2
	add	r2, r2, #3
	add	r0, r10, r0
	add	r2, r10, r2
	mov	ip, r0
.L237:
	ldrb	r3, [r0, #1]!	@ zero_extendqisi2
	sub	lr, fp, #44
	add	r1, r1, #1
	add	r3, lr, r3
	cmp	r1, #256
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [ip, #1]!
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r3, lr, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r2], #1
	bne	.L237
	ldr	r3, [r5, #2640]
	b	.L235
.L277:
	ldrb	r3, [r5, #2526]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L247
	mov	r0, r2
	b	.L253
.L280:
	cmp	r3, #0
	sub	r0, fp, #556
	mov	r3, #0
	ldreqb	r6, [r5, #2644]	@ zero_extendqisi2
	ldrneb	r6, [r5, #2528]	@ zero_extendqisi2
	ldreqb	r5, [r5, #2648]	@ zero_extendqisi2
	ldrneb	r5, [r5, #2529]	@ zero_extendqisi2
	mov	r1, r6
	mov	r2, r5
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	r2, r5
	mov	r1, r6
	sub	r0, fp, #300
	mov	r3, #1
	bl	VC1_Vfmw_GenerateIntensityMap
	movw	r2, #1544
	mul	r2, r2, r7
	mov	r1, #0
	add	r0, r2, #14464
	add	r2, r2, #14720
	add	r0, r0, #2
	add	r2, r2, #3
	add	r0, r10, r0
	add	r2, r10, r2
	mov	ip, r0
.L240:
	ldrb	r3, [r0, #1]!	@ zero_extendqisi2
	sub	lr, fp, #44
	add	r1, r1, #1
	add	r3, lr, r3
	cmp	r1, #256
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [ip, #1]!
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r3, lr, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r2], #1
	bne	.L240
	b	.L236
.L282:
	ldr	r3, [r3, #2632]
	cmp	r3, #1
	bne	.L213
.L214:
	mov	r1, r5
	sub	r0, fp, #556
	mov	r3, #0
	mov	r2, r6
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	r1, r5
	mov	r2, r6
	sub	r0, fp, #300
	mov	r3, #1
	bl	VC1_Vfmw_GenerateIntensityMap
	movw	r3, #1544
	mul	r3, r3, r4
	mov	ip, #0
	add	lr, r3, #13952
	add	r0, r3, #14208
	add	r1, r3, #14464
	add	lr, lr, #2
	add	r3, r3, #14720
	add	lr, r10, lr
	add	r0, r0, #3
	add	r1, r1, #3
	add	r3, r3, #3
	add	r0, r10, r0
	add	r1, r10, r1
	add	r2, r10, r3
	mov	r5, lr
.L216:
	ldrb	r3, [lr, #1]!	@ zero_extendqisi2
	sub	r6, fp, #44
	add	ip, ip, #1
	add	r3, r6, r3
	cmp	ip, #256
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r5, #1]!
	ldrb	r3, [r0]	@ zero_extendqisi2
	add	r3, r6, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r0], #1
	ldrb	r3, [r1]	@ zero_extendqisi2
	add	r3, r6, r3
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r1], #1
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r3, r6, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r2], #1
	bne	.L216
	b	.L215
.L283:
	mov	r2, r6
	mov	r1, r5
	sub	r0, fp, #556
	mov	r3, #0
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	r2, r6
	mov	r1, r5
	sub	r0, fp, #300
	mov	r3, #1
	mov	r7, #0
	bl	VC1_Vfmw_GenerateIntensityMap
	ldr	r3, [fp, #-560]
	movw	r2, #1544
	str	r4, [fp, #-564]
	mul	r1, r2, r4
	mul	r2, r2, r3
	add	r8, r1, #13952
	add	r6, r1, #14208
	add	r5, r1, #14464
	add	r8, r8, #2
	add	lr, r2, #13952
	add	ip, r2, #14208
	add	r0, r2, #14464
	add	r1, r1, #14720
	add	r2, r2, #14720
	add	r8, r10, r8
	add	r6, r6, #3
	add	r5, r5, #3
	add	r1, r1, #3
	add	lr, lr, #3
	add	ip, ip, #3
	add	r0, r0, #3
	add	r2, r2, #3
	add	r6, r10, r6
	add	r5, r10, r5
	add	r1, r10, r1
	add	lr, r10, lr
	add	ip, r10, ip
	add	r0, r10, r0
	add	r2, r10, r2
	mov	r9, r8
.L223:
	ldrb	r3, [r8, #1]!	@ zero_extendqisi2
	sub	r4, fp, #44
	add	r7, r7, #1
	add	r3, r4, r3
	cmp	r7, #256
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r9, #1]!
	ldrb	r3, [r6]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r6], #1
	ldrb	r3, [r5]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r5], #1
	ldrb	r3, [r1]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r1], #1
	ldrb	r3, [lr]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [lr], #1
	ldrb	r3, [ip]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [ip], #1
	ldrb	r3, [r0]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r0], #1
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r2], #1
	bne	.L223
	ldr	r4, [fp, #-564]
	b	.L222
.L285:
	.align	2
.L284:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_BuildRefList, .-VC1_Vfmw_BuildRefList
	.align	2
	.global	VC1_Vfmw_GetStreamInfo
	.type	VC1_Vfmw_GetStreamInfo, %function
VC1_Vfmw_GetStreamInfo:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r10, r0, #15808
	add	r4, r0, #32768
	mov	r5, r0
	ldrsb	r3, [r10]
	ldr	r6, [r4, #3176]
	cmp	r3, #0
	beq	.L287
	add	r3, r0, #20480
	ldr	r3, [r3, #2980]
	cmp	r3, #3
	ldr	r3, [r4, #3180]
	addeq	r3, r3, #1
	addeq	r3, r3, r3, lsr #31
	moveq	r3, r3, asr #1
	mul	r3, r3, r6
	str	r3, [fp, #-52]
	add	r3, r0, #12288
	add	r2, r3, #3760
	mov	r3, r2
	ldrh	r2, [r2, #2]
	ldrh	r3, [r3]
	adds	r1, r2, #15
	addmi	r1, r2, #30
	adds	r0, r3, #15
	addmi	r0, r3, #30
	mov	r1, r1, asr #4
	mov	r0, r0, asr #4
.L340:
	mov	r2, r0, asl #4
	movw	ip, #8160
	sub	r3, r2, #32
	cmp	r3, ip
	mov	r3, r1, asl #4
	bhi	.L290
	sub	lr, r3, #32
	cmp	lr, ip
	bhi	.L290
	ldr	r3, [r4, #3188]
	add	r7, r5, #12288
	cmp	r3, r1
	beq	.L377
.L293:
	ldr	r2, [r4, #3180]
	mov	r3, r6, asl #4
	add	r3, r3, #63
	str	r6, [r4, #3184]
	bic	r3, r3, #63
	str	r3, [r4, #3200]
	str	r2, [r4, #3188]
	ldrb	r3, [r7, #432]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L301
	mov	r3, #1
.L295:
	ldrb	r2, [r7, #427]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L378
.L298:
	ldrb	r2, [r7, #424]	@ zero_extendqisi2
	eor	r2, r2, #8
	ubfx	r2, r2, #3, #1
	orrs	r3, r3, r2
	bne	.L301
.L305:
	mov	r0, r5
	bl	VC1_Vfmw_GetImageBuffer
	subs	r8, r0, #0
	beq	.L379
	add	r3, r5, #45056
	ldr	r1, [r4, #3252]
	str	r3, [fp, #-48]
	ldr	r0, [r3, #3776]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L307
	ldr	r2, [r5]
	mov	r0, #29
	ldr	ip, .L387
	ldr	r1, .L387+4
	ldrd	r8, [r2, #48]
	strd	r8, [r3, #8]
	ldr	r2, [r5]
	ldrd	r8, [r2, #64]
	strd	r8, [r3, #16]
	ldr	r2, [r5]
	ldrd	r8, [r2, #80]
	strd	r8, [r3, #24]
	mvn	r8, #0
	ldr	r2, [r5]
	mvn	r9, #0
	ldr	r2, [r2, #96]
	str	r2, [r3, #68]
	ldr	r2, [r5]
	ldr	r2, [r2, #100]
	str	r2, [r3, #72]
	ldr	r2, [r5]
	ldr	r2, [r2, #104]
	str	r2, [r3, #76]
	ldr	r2, [r5]
	ldr	r2, [r2, #120]
	str	r2, [r3, #80]
	ldr	r2, [r5]
	strd	r8, [r2, #48]
	ldrd	r8, [r3, #16]
	ldr	ip, [ip, #68]
	ldrd	r2, [r3, #8]
	strd	r8, [sp]
	blx	ip
.L307:
	ldrsb	r3, [r10]
	cmp	r3, #0
	beq	.L308
	add	r3, r5, #20480
	ldr	r3, [r3, #2980]
	cmp	r3, #3
	beq	.L380
.L308:
	ldr	r3, [r4, #3160]
	mov	r2, #0
	str	r2, [r3, #1180]
.L309:
	ldr	r3, [r4, #3160]
	mov	r2, #0
	strb	r2, [r3, #2]
	ldrsb	r3, [r10]
	cmp	r3, r2
	bne	.L310
	add	r3, r5, #20480
	ldrb	r2, [r3, #2600]	@ zero_extendqisi2
	cmp	r2, #1
	ldreqb	r2, [r3, #2838]	@ zero_extendqisi2
	ldreq	r3, [r4, #3160]
	streqb	r2, [r3, #2]
.L310:
	ldrb	r3, [r7, #426]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #1
	movls	r3, #1
	movhi	r3, #0
	bhi	.L311
	ldr	r3, [r4, #3240]
	ldr	r2, [r4, #3244]
	cmp	r3, #0
	ldr	r3, [r4, #3248]
	movne	r1, #2
	moveq	r1, #1
	cmp	r2, r3
	str	r1, [r4, #3240]
	beq	.L313
	ldr	r3, .L387
	mov	r0, #13
	ldr	r1, .L387+8
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [fp, #-48]
	mov	r2, #0
	ldr	r1, [r4, #3244]
	ldr	r0, [r3, #3776]
	bl	FSP_SetRef
	ldr	r3, [r4, #3248]
.L313:
	ldr	r1, [r4, #3252]
	mov	r2, #1
	ldr	r8, [fp, #-48]
	str	r3, [r4, #3244]
	str	r1, [r4, #3248]
	ldr	r0, [r8, #3776]
	bl	FSP_SetRef
	ldr	r1, [r4, #3244]
	ldr	r0, [r8, #3776]
	bl	FSP_RemovePmv
	ldrb	r3, [r7, #426]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #1
	bhi	.L315
	ldr	r3, [r4, #3168]
	mov	r1, #0
	mov	r2, #1
	strb	r1, [r3]
	ldr	r3, [r4, #3160]
	strb	r2, [r3]
	ldr	r2, [r4, #3164]
	ldr	r3, [r4, #3160]
	str	r2, [r4, #3168]
	str	r3, [r4, #3164]
.L315:
	ldr	r9, [fp, #-48]
	ldr	r1, [r4, #3252]
	ldr	r0, [r9, #3776]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #3244]
	str	r9, [fp, #-48]
	mov	r8, r0
	ldr	r0, [r9, #3776]
	bl	FSP_GetLogicFs
	ldr	r3, [fp, #-48]
	ldr	r1, [r4, #3248]
	mov	r9, r0
	str	r0, [fp, #-56]
	ldr	r0, [r3, #3776]
	bl	FSP_GetLogicFs
	cmp	r8, #0
	cmpne	r9, #0
	mov	r3, r9
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r9, r0
	cmp	r3, #0
	bne	.L381
	ldrsb	r3, [r10]
	cmp	r3, #0
	bne	.L382
.L319:
	mov	r3, #0
.L371:
	str	r3, [r8, #156]
	ldrb	r3, [r7, #426]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L383
.L321:
	ldr	r3, [r8, #520]
	cmp	r3, #0
	beq	.L322
	ldr	r2, [r8, #528]
	cmp	r2, #0
	beq	.L322
	ldr	r2, [r8, #524]
	cmp	r2, #0
	beq	.L322
	ldr	r2, [r9, #520]
	cmp	r2, #0
	ldrne	r3, [r2, #12]
	ldreq	r3, [r3, #12]
	str	r3, [r7, #112]
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #520]
	cmp	r3, #0
	ldreq	r3, [r8, #520]
	ldr	r3, [r3, #12]
	str	r3, [r7, #108]
	ldr	r3, [r8, #520]
	ldr	r3, [r3, #12]
	str	r3, [r7, #220]
	ldr	r3, [r8, #532]
	str	r3, [r7, #116]
	ldr	r3, [r9, #532]
	str	r3, [r7, #120]
	ldr	r3, [r8, #524]
	ldr	r3, [r3, #12]
	str	r3, [r7, #104]
	ldr	r3, [r8, #524]
	ldr	r3, [r3, #20]
	str	r3, [r7, #184]
	ldr	r3, [r8, #520]
	ldr	r8, [r4, #3160]
	ldr	r0, [r3, #12]
	bl	MEM_Phy2Vir
	str	r0, [r8, #1064]
	ldr	r0, [r7, #108]
	ldr	r8, [r4, #3168]
	bl	MEM_Phy2Vir
	str	r0, [r8, #1064]
	ldr	r0, [r7, #112]
	ldr	r8, [r4, #3164]
	bl	MEM_Phy2Vir
	str	r0, [r8, #1064]
.L300:
	ldrsb	r3, [r10]
	cmp	r3, #0
	beq	.L384
	add	ip, r5, #20480
	ldr	r3, [r4, #3160]
	ldr	r2, [ip, #2980]
	strb	r2, [r3, #1027]
	ldr	r3, [r4, #3160]
	ldrb	r2, [ip, #2937]	@ zero_extendqisi2
	strb	r2, [r3, #1028]
	ldrb	r2, [ip, #2950]	@ zero_extendqisi2
	ldr	r3, [r4, #3160]
	sub	r0, r2, #2
	ldrb	r1, [ip, #2977]	@ zero_extendqisi2
	cmp	r0, #1
	movls	r2, #1
	bls	.L332
	cmp	r2, #4
	movne	r2, #0
	beq	.L385
.L332:
	add	r3, r3, r1
	strb	r2, [r3, #1029]
	ldr	lr, [r4, #3260]
	cmp	lr, #0
	beq	.L333
	sub	r0, lr, #1
	cmp	r0, #0
	uxtble	r2, r0
	movle	r1, #0
	ble	.L335
	add	r8, r5, #35840
	mov	r2, #0
	add	r8, r8, #192
.L336:
	ldr	r3, [r8, #72]
	mov	r1, r8
	strb	r2, [r8, #8]
	add	r2, r2, #1
	cmp	r2, #254
	cmple	r2, r0
	add	r8, r8, #48
	mul	r3, r3, r6
	sub	r3, r3, #1
	str	r3, [r8, #-24]
	blt	.L336
	uxtb	r2, r0
.L335:
	cmp	lr, #256
	ble	.L369
	add	r3, r5, #12672
	add	r3, r3, #40
.L337:
	ldr	r0, [fp, #-52]
	strb	r2, [r1, #8]
	sub	r0, r0, #1
	str	r0, [r1, #24]
	ldrb	r1, [r7, #426]	@ zero_extendqisi2
	cmp	r1, #2
	bne	.L331
	ldrb	r2, [ip, #2967]	@ zero_extendqisi2
	add	lr, r5, #45056
	ldr	r0, [ip, #3084]
	mul	r0, r0, r2
	mov	r0, r0, asr #8
	str	r0, [lr, #3304]
	rsb	r2, r0, r2
	subs	r2, r2, #1
	movmi	r2, #0
	str	r2, [lr, #3308]
	b	.L331
.L290:
	ldr	ip, .L387
	mov	r0, #0
	ldr	r1, .L387+12
	mov	r8, r0
	ldr	r4, [ip, #68]
	blx	r4
.L368:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L287:
	ldr	r1, [r4, #3180]
	mov	r0, r6
	mul	r3, r1, r6
	str	r3, [fp, #-52]
	b	.L340
.L301:
	add	r3, r5, #45056
	str	r3, [fp, #-48]
	ldr	r1, [r4, #3248]
	mov	r2, r3
	add	r3, r5, #34304
	add	r3, r3, #80
	str	r3, [r4, #3160]
	str	r3, [r4, #3172]
	str	r3, [r4, #3168]
	str	r3, [r4, #3164]
	ldr	r0, [r2, #3776]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L297
	ldr	r9, [fp, #-48]
	mov	r3, #0
	ldr	r1, [r8, #212]
	str	r3, [fp, #-56]
	ldr	r0, [r9, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r8, #216]
	ldr	r0, [r9, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r8, #220]
	ldr	r0, [r9, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r8, #224]
	ldr	r0, [r9, #3776]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-56]
	mov	r2, #1
	str	r3, [r8, #212]
	str	r3, [r8, #216]
	str	r3, [r8, #220]
	str	r3, [r8, #224]
	ldr	r1, [r4, #3248]
	ldr	r0, [r9, #3776]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #3244]
	ldr	r0, [r9, #3776]
	bl	FSP_ClearLogicFs
	ldr	r3, [fp, #-56]
	str	r3, [r4, #3244]
	str	r3, [r4, #3248]
	ldr	r0, [r9, #3776]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #3248]
	str	r0, [r4, #3244]
.L297:
	add	r3, r5, #26624
	add	r1, r5, #34304
	ldr	r9, [fp, #-48]
	add	r3, r3, #41
	add	r1, r1, #81
	mov	r2, #0
	str	r2, [r4, #3240]
.L303:
	strb	r2, [r3]
	add	r3, r3, #1536
	strb	r2, [r3, #-1537]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L303
	add	r3, r5, #48384
	ldr	r0, [r9, #3776]
	add	r3, r3, #96
	str	r3, [fp, #-48]
	mov	r1, r3
	bl	FSP_ClearNotInVoQueue
	ldrb	r8, [r7, #424]	@ zero_extendqisi2
	ldr	r3, [fp, #-48]
	and	r8, r8, #8
	ands	r8, r8, #255
	bne	.L305
	mov	r0, r3
	bl	ResetVoQueue
	ldr	r1, [r5]
	mov	r3, #2
	mov	r0, r5
	ldr	r2, [r1, #736]
	ldr	ip, [r1, #740]
	adds	r1, r2, #15
	addmi	r1, r2, #30
	adds	r2, ip, #15
	addmi	r2, ip, #30
	mov	r1, r1, asr #4
	str	r1, [r7, #256]
	mov	r2, r2, asr #4
	str	r2, [r7, #260]
	add	r2, r2, #1
	mov	r1, r1, asl #4
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
	mov	r2, r2, asl #5
	bl	VC1_ArrangeVahbMem
	cmp	r0, #1
	bne	.L304
	ldrb	r3, [r7, #424]	@ zero_extendqisi2
	orr	r3, r3, #8
	strb	r3, [r7, #424]
	b	.L305
.L379:
	ldr	r3, .L387
	mov	r0, #1
	ldr	r1, .L387+16
	ldr	r3, [r3, #68]
	blx	r3
	b	.L368
.L377:
	ldr	r3, [r4, #3184]
	cmp	r3, r0
	bne	.L293
	mov	r3, r6, asl #4
	add	r3, r3, #63
	bic	r3, r3, #63
	str	r3, [r4, #3200]
	ldrb	r3, [r7, #432]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #0
	bne	.L295
	b	.L298
.L311:
	ldr	r2, [r4, #3240]
	cmp	r2, #1
	bhi	.L315
	ldr	r2, [fp, #-48]
	mov	r8, r3
	ldr	r1, [r4, #3252]
	str	r3, [fp, #-48]
	ldr	r0, [r2, #3776]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3160]
	ldr	r3, [fp, #-48]
	mov	r0, #1
	ldr	ip, .L387
	ldr	r1, .L387+20
	strb	r3, [r2]
	ldr	r2, [r4, #3160]
	strb	r3, [r2, #1]
	ldr	r3, [ip, #68]
	blx	r3
	b	.L368
.L381:
	ldr	r3, [fp, #-48]
	mov	r2, #1
	ldr	r1, [r4, #3252]
	ldr	r5, .L387
	ldr	r0, [r3, #3776]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3160]
	mov	ip, #0
	mov	r3, r8
	mov	r0, ip
	ldr	r1, .L387+24
	strb	ip, [r2]
	movw	r2, #2346
	ldr	lr, [r4, #3160]
	strb	ip, [lr, #1]
	ldr	ip, [fp, #-56]
	str	r9, [sp, #4]
	str	ip, [sp]
	ldr	r4, [r5, #68]
	blx	r4
	ldrb	r3, [r7, #426]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L376
.L324:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L387+28
	mov	r8, #0
	blx	r3
	b	.L368
.L384:
	ldr	r1, [r4, #3160]
	add	r2, r5, #20480
	strb	r3, [r1, #1027]
	ldr	r1, [r4, #3160]
	ldrb	r0, [r2, #2839]	@ zero_extendqisi2
	strb	r0, [r1, #1028]
	ldrb	r0, [r2, #2847]	@ zero_extendqisi2
	ldr	r1, [r4, #3160]
	sub	ip, r0, #2
	cmp	ip, #1
	movls	r3, #1
	bls	.L330
	cmp	r0, #4
	beq	.L386
.L330:
	add	r6, r5, #45056
	strb	r3, [r1, #1030]
	strb	r3, [r1, #1029]
	mov	r2, #1
	mov	r3, #0
	str	r2, [r4, #3260]
	strb	r3, [r4, #3272]
	ldr	r0, [r7, #3552]
	ldr	r8, [r6, #3268]
	bl	BsPos
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	add	r0, r8, r0, asr #3
	str	r0, [r4, #3264]
	ldr	r0, [r7, #3552]
	ldr	r8, [r6, #3280]
	bl	BsPos
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	add	r0, r8, r0, asr #3
	str	r0, [r4, #3276]
	ldr	r0, [r7, #3552]
	bl	BsPos
	and	r0, r0, #7
	str	r0, [r4, #3280]
	ldr	r0, [r7, #3552]
	ldr	r8, [r6, #3288]
	bl	BsPos
	add	r3, r5, #12672
	add	r3, r3, #40
	mov	r8, r8, asl #3
	rsb	r0, r0, r8
	str	r0, [r4, #3284]
	ldr	r1, [r6, #3328]
	ldr	r2, [r6, #3332]
	mul	r2, r2, r1
	sub	r2, r2, #1
	str	r2, [r4, #3288]
	ldrb	r1, [r7, #426]	@ zero_extendqisi2
.L331:
	mov	r0, r3
	mov	r2, #0
	mov	r3, #1
	bl	VC1_Vfmw_BuildRefList
	subs	r8, r0, #0
	movne	r8, #1
	bne	.L368
	add	r5, r5, #45056
	ldr	r1, [r4, #3252]
	mov	r2, #1
	ldr	r0, [r5, #3776]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3160]
	ldr	r3, .L387
	mov	r0, #1
	ldr	r1, .L387+32
	strb	r8, [r2]
	ldr	r2, [r4, #3160]
	strb	r8, [r2, #1]
	ldr	r3, [r3, #68]
	blx	r3
	b	.L368
.L382:
	add	r3, r5, #20480
	ldr	r3, [r3, #2980]
	cmp	r3, #3
	bne	.L319
	ldr	r3, .L387+36
	ldr	r3, [r3]
	cmp	r3, #1
	bne	.L319
	b	.L371
.L322:
	ldr	r3, [fp, #-48]
	mov	r2, #1
	ldr	r1, [r4, #3252]
	ldr	r5, .L387
	ldr	r0, [r3, #3776]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3160]
	mov	r3, #0
	ldr	r1, .L387+40
	mov	r0, r3
	strb	r3, [r2]
	ldr	r2, [r4, #3160]
	strb	r3, [r2, #1]
	ldr	r2, [r8, #524]
	ldr	r3, [r4, #3252]
	str	r2, [sp, #12]
	ldr	ip, [r8, #528]
	ldr	r2, [r4, #3244]
	ldr	lr, [r4, #3248]
	str	ip, [sp, #8]
	ldr	ip, [r8, #520]
	str	lr, [sp]
	ldr	r4, [r5, #68]
	str	ip, [sp, #4]
	blx	r4
	ldrb	r3, [r7, #426]	@ zero_extendqisi2
	cmp	r3, #5
	bne	.L324
.L376:
	ldr	r2, [fp, #-48]
	ldr	r3, [r2, #3348]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r2, #3348]
	b	.L324
.L378:
	ldrb	r2, [r7, #433]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L300
	b	.L298
.L383:
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #156]
	str	r3, [r8, #156]
	ldr	r2, [r4, #3168]
	ldr	r3, [r4, #3160]
	ldr	r2, [r2, #1180]
	str	r2, [r3, #1180]
	ldr	r2, [fp, #-48]
	ldr	r3, [r2, #3348]
	add	r3, r3, #1
	str	r3, [r2, #3348]
	b	.L321
.L333:
	mov	r2, lr
	mov	r3, #1
	str	r3, [r4, #3260]
.L339:
	mov	r1, lr, asl #6
	add	r3, r5, #12672
	sub	r1, r1, lr, asl #4
	add	r3, r3, #40
	add	r1, r1, #23296
	add	r1, r1, #24
	add	r1, r3, r1
	b	.L337
.L380:
	ldr	r3, .L387+36
	ldr	r3, [r3]
	cmp	r3, #1
	ldreq	r2, [r4, #3160]
	streq	r3, [r2, #1180]
	bne	.L308
	b	.L309
.L304:
	ldr	r3, .L387
	mov	r0, #1
	ldr	r1, .L387+44
	ldr	r3, [r3, #68]
	blx	r3
	ldrb	r3, [r7, #424]	@ zero_extendqisi2
	bic	r3, r3, #8
	strb	r3, [r7, #424]
	b	.L368
.L385:
	ldrb	r2, [ip, #2951]	@ zero_extendqisi2
	sub	r2, r2, #2
	cmp	r2, #1
	movhi	r2, #0
	movls	r2, #1
	b	.L332
.L386:
	ldrb	r3, [r2, #2848]	@ zero_extendqisi2
	sub	r3, r3, #2
	cmp	r3, #1
	movhi	r3, #0
	movls	r3, #1
	b	.L330
.L369:
	mov	lr, r0
	b	.L339
.L388:
	.align	2
.L387:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC30
	.word	.LC31
	.word	.LC20
	.word	.LC29
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC36
	.word	USE_FF_APT_EN
	.word	.LC35
	.word	.LC28
	UNWIND(.fnend)
	.size	VC1_Vfmw_GetStreamInfo, .-VC1_Vfmw_GetStreamInfo
	.align	2
	.global	VC1_Vfmw_PrepareDecode
	.type	VC1_Vfmw_PrepareDecode, %function
VC1_Vfmw_PrepareDecode:
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
	bl	VC1_Vfmw_GetStreamInfo
	subs	r4, r0, #0
	movne	r4, #1
	bne	.L390
	ldr	r3, .L392
	ldr	r1, .L392+4
	ldr	r3, [r3, #68]
	blx	r3
.L390:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L393:
	.align	2
.L392:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC37
	UNWIND(.fnend)
	.size	VC1_Vfmw_PrepareDecode, .-VC1_Vfmw_PrepareDecode
	.align	2
	.global	VC1_DecMvrange
	.type	VC1_DecMvrange, %function
VC1_DecMvrange:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldr	lr, .L395
	mov	r4, r0
	sub	ip, fp, #84
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	mov	r0, r4
	mov	r1, #3
	bl	BsShow
	sub	r3, fp, #20
	add	r3, r3, r0, lsl #3
	mov	r0, r4
	ldr	r1, [r3, #-60]
	ldr	r4, [r3, #-64]
	bl	BsSkip
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L396:
	.align	2
.L395:
	.word	.LANCHOR0+16
	UNWIND(.fnend)
	.size	VC1_DecMvrange, .-VC1_DecMvrange
	.align	2
	.global	VC1_DecTransacfrm
	.type	VC1_DecTransacfrm, %function
VC1_DecTransacfrm:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	mov	r2, #64
	mov	r4, r0
	mov	r1, #0
	sub	r0, fp, #84
	bl	memset
	mov	r3, #2
	mov	r1, r3
	mov	r0, r4
	mov	r2, #1
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r2, [fp, #-80]
	str	r2, [fp, #-72]
	str	r2, [fp, #-68]
	bl	BsShow
	sub	r3, fp, #20
	add	r3, r3, r0, lsl #3
	mov	r0, r4
	ldr	r1, [r3, #-60]
	ldr	r4, [r3, #-64]
	bl	BsSkip
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_DecTransacfrm, .-VC1_DecTransacfrm
	.align	2
	.global	VC1_SetCurPicResolutionInfo
	.type	VC1_SetCurPicResolutionInfo, %function
VC1_SetCurPicResolutionInfo:
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
	add	r3, r0, #20480
	cmp	r1, #1
	add	r0, r0, #32768
	ldr	r2, [r3, #2752]
	beq	.L400
	cmp	r1, #2
	beq	.L406
	cmp	r1, #0
	beq	.L405
	add	r2, r2, #1
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
.L406:
	str	r2, [r0, #2904]
	ldr	r3, [r3, #2756]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	str	r3, [r0, #2908]
	b	.L403
.L400:
	add	r2, r2, #1
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
.L405:
	str	r2, [r0, #2904]
	ldr	r3, [r3, #2756]
	str	r3, [r0, #2908]
.L403:
	mul	r1, r3, r2
	mov	r2, r2, asl #4
	mov	r3, r3, asl #4
	str	r2, [r0, #2896]
	str	r3, [r0, #2900]
	str	r1, [r0, #2912]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_SetCurPicResolutionInfo, .-VC1_SetCurPicResolutionInfo
	.align	2
	.global	VC1_DecMvmodeProgrP
	.type	VC1_DecMvmodeProgrP, %function
VC1_DecMvmodeProgrP:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
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
	mov	r5, r1
	mov	r1, #4
	mov	r6, r0
	bl	BsShow
	ldr	ip, .L418
	sub	r4, fp, #76
	sub	lr, fp, #56
	mov	r7, r0
	cmp	r0, #1
	ldmia	ip!, {r0, r1, r2, r3}
	ldr	r8, [ip], #4
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	str	r8, [r4]
	ldr	ip, [ip]
	stmia	lr!, {r0, r1, r2, r3}
	str	ip, [lr]
	ble	.L416
	cmp	r7, #3
	movle	r1, #3
	movle	r4, #2
	bgt	.L417
.L409:
	mov	r0, r6
	bl	BsSkip
	sub	r3, fp, #36
	add	r4, r3, r4, lsl #2
	cmp	r5, #12
	ldrhi	r0, [r4, #-40]
	ldrls	r0, [r4, #-20]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L417:
	cmp	r7, #8
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
	b	.L409
.L416:
	cmp	r7, #0
	mov	r1, #4
	moveq	r4, #3
	movne	r4, r1
	b	.L409
.L419:
	.align	2
.L418:
	.word	.LANCHOR0+80
	UNWIND(.fnend)
	.size	VC1_DecMvmodeProgrP, .-VC1_DecMvmodeProgrP
	.align	2
	.global	VC1_DecMvmodeProgrB
	.type	VC1_DecMvmodeProgrB, %function
VC1_DecMvmodeProgrB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	mov	r1, #1
	bl	BsSkip
	ldr	r2, .L421
	sub	r3, fp, #12
	add	r3, r3, r0, lsl #2
	ldmia	r2, {r0, r1}
	sub	r2, fp, #12
	stmdb	r2, {r0, r1}
	ldr	r0, [r3, #-8]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L422:
	.align	2
.L421:
	.word	.LANCHOR0+120
	UNWIND(.fnend)
	.size	VC1_DecMvmodeProgrB, .-VC1_DecMvmodeProgrB
	.align	2
	.global	VC1_DecMvmodeInterB
	.type	VC1_DecMvmodeInterB, %function
VC1_DecMvmodeInterB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
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
	mov	r5, r1
	mov	r1, #3
	mov	r6, r0
	bl	BsShow
	ldr	r3, .L431
	mov	r2, #0
	str	r2, [fp, #-44]
	str	r2, [fp, #-32]
	sub	lr, fp, #64
	mov	ip, #1
	mov	r4, #3
	str	ip, [fp, #-48]
	mov	ip, #2
	str	r4, [fp, #-36]
	str	ip, [fp, #-40]
	mov	r7, r0
	cmp	r0, #1
	ldmia	r3, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ble	.L430
	cmp	r7, #4
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
.L425:
	mov	r0, r6
	bl	BsSkip
	sub	r3, fp, #28
	add	ip, r3, r4, lsl #2
	cmp	r5, #12
	ldrhi	r0, [ip, #-36]
	ldrls	r0, [ip, #-20]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L430:
	cmp	r7, #0
	mov	r1, r4
	movne	r4, ip
	b	.L425
.L432:
	.align	2
.L431:
	.word	.LANCHOR0+128
	UNWIND(.fnend)
	.size	VC1_DecMvmodeInterB, .-VC1_DecMvmodeInterB
	.align	2
	.global	VC1_DecMvmode2
	.type	VC1_DecMvmode2, %function
VC1_DecMvmode2:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	mov	r5, r1
	mov	r1, #3
	mov	r6, r0
	bl	BsShow
	ldr	r3, .L442
	sub	lr, fp, #60
	add	ip, r3, #16
	mov	r4, r0
	cmp	r0, #1
	ldmia	r3, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	sub	ip, fp, #28
	stmdb	ip, {r0, r1, r2, r3}
	ble	.L441
	cmp	r4, #4
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
.L435:
	mov	r0, r6
	bl	BsSkip
	sub	r3, fp, #28
	add	r4, r3, r4, lsl #2
	cmp	r5, #12
	ldrhi	r0, [r4, #-32]
	ldrls	r0, [r4, #-16]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L441:
	cmp	r4, #0
	mov	r1, #3
	moveq	r4, r1
	movne	r4, #2
	b	.L435
.L443:
	.align	2
.L442:
	.word	.LANCHOR0+128
	UNWIND(.fnend)
	.size	VC1_DecMvmode2, .-VC1_DecMvmode2
	.align	2
	.global	VC1_DecBfractionSMP
	.type	VC1_DecBfractionSMP, %function
VC1_DecBfractionSMP:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 208
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #212)
	sub	sp, sp, #212
	ldr	ip, .L454
	mov	r8, r0
	str	r1, [fp, #-248]
	str	r2, [fp, #-252]
	sub	r10, fp, #244
	ldmia	ip!, {r0, r1, r2, r3}
	sub	r7, fp, #216
	sub	r4, fp, #156
	sub	lr, fp, #100
	sub	r6, fp, #188
	add	r9, ip, #12
	add	r5, ip, #40
	stmia	r10!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2}
	stmia	r10, {r0, r1, r2}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	r7!, {r0, r1, r2, r3}
	ldmia	r9, {r0, r1, r2}
	add	r9, ip, #96
	add	ip, ip, #152
	stmia	r7, {r0, r1, r2}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	r5, {r0, r1}
	stmia	r4, {r0, r1}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r9, {r0, r1}
	stmia	lr, {r0, r1}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	r6!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	stmia	r6, {r0, r1, r2, r3}
	mov	r0, r8
	mov	r1, #3
	bl	BsShow
	mov	r4, r0
	cmp	r4, #6
	mov	r0, r8
	bgt	.L445
	mov	r1, #3
	bl	BsSkip
	sub	r3, fp, #44
	add	r2, r3, r4, lsl #2
	ldr	r3, [r2, #-172]
	ldr	r1, [r2, #-200]
	sub	r3, r3, #1
	cmp	r3, #7
	bhi	.L451
.L453:
	sub	r2, fp, #44
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-144]
	mul	r3, r3, r1
.L449:
	ldr	r2, [fp, #-248]
	mov	r0, r4
	str	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L445:
	mov	r1, #7
	bl	BsGet
	and	r4, r0, #15
	cmp	r4, #15
	beq	.L452
	sub	r0, r0, #112
	add	r4, r4, #7
	cmp	r0, #13
	bhi	.L451
	sub	r3, fp, #44
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #-56]
	ldr	r1, [r0, #-112]
	sub	r3, r3, #1
	cmp	r3, #7
	bls	.L453
.L451:
	mov	r3, #0
	b	.L449
.L452:
	ldr	r2, [fp, #-252]
	mov	r3, #4
	mov	r0, #22
	strb	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L455:
	.align	2
.L454:
	.word	.LANCHOR0+160
	UNWIND(.fnend)
	.size	VC1_DecBfractionSMP, .-VC1_DecBfractionSMP
	.align	2
	.global	VC1_DecBfraction
	.type	VC1_DecBfraction, %function
VC1_DecBfraction:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 208
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #220)
	sub	sp, sp, #220
	ldr	r5, .L466
	mov	r8, r0
	str	r1, [fp, #-248]
	sub	r10, fp, #244
	sub	r7, fp, #216
	ldmia	r5!, {r0, r1, r2, r3}
	sub	lr, fp, #156
	sub	ip, fp, #100
	sub	r6, fp, #188
	add	r9, r5, #12
	add	r4, r5, #40
	stmia	r10!, {r0, r1, r2, r3}
	ldmia	r5, {r0, r1, r2}
	stmia	r10, {r0, r1, r2}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	r7!, {r0, r1, r2, r3}
	ldmia	r9, {r0, r1, r2}
	add	r9, r5, #96
	stmia	r7, {r0, r1, r2}
	add	r7, r5, #152
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r4, {r0, r1}
	stmia	lr, {r0, r1}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	r9, {r0, r1}
	stmia	ip, {r0, r1}
	ldmia	r7!, {r0, r1, r2, r3}
	stmia	r6!, {r0, r1, r2, r3}
	ldmia	r7, {r0, r1, r2, r3}
	stmia	r6, {r0, r1, r2, r3}
	mov	r0, r8
	mov	r1, #3
	bl	BsShow
	mov	r4, r0
	cmp	r4, #6
	mov	r0, r8
	bgt	.L457
	mov	r1, #3
	bl	BsSkip
	sub	r3, fp, #44
	add	r2, r3, r4, lsl #2
	ldr	r1, [r2, #-200]
	ldr	r2, [r2, #-172]
	sub	r3, r2, #1
	cmp	r3, #7
	ldrhi	r6, .L466+4
	bhi	.L461
.L465:
	sub	r2, fp, #44
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-144]
	mul	r3, r3, r1
.L462:
	ldr	r2, [fp, #-248]
	str	r3, [r2]
.L459:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L457:
	mov	r1, #7
	bl	BsGet
	and	r4, r0, #15
	sub	r3, r4, #14
	add	r4, r4, #7
	cmp	r3, #1
	bls	.L459
	sub	r3, r0, #112
	cmp	r3, #13
	bhi	.L460
	sub	r2, fp, #44
	add	r2, r2, r3, lsl #2
	ldr	r1, [r2, #-112]
	ldr	r2, [r2, #-56]
	sub	r3, r2, #1
	cmp	r3, #7
	ldrhi	r6, .L466+4
	bls	.L465
.L461:
	str	r2, [sp]
	movw	r3, #3533
	ldr	r5, [r6, #68]
	mov	r0, #1
	ldr	r2, .L466+8
	ldr	r1, .L466+12
	blx	r5
	mov	r3, #0
	b	.L462
.L460:
	ldr	r6, .L466+4
	add	r2, r5, #184
	str	r0, [sp]
	movw	r3, #3523
	ldr	r1, .L466+16
	mov	r0, #1
	ldr	r5, [r6, #68]
	blx	r5
	mov	r2, #0
	b	.L461
.L467:
	.align	2
.L466:
	.word	.LANCHOR0+160
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+360
	.word	.LC39
	.word	.LC38
	UNWIND(.fnend)
	.size	VC1_DecBfraction, .-VC1_DecBfraction
	.align	2
	.global	VC1_VopDQuant
	.type	VC1_VopDQuant, %function
VC1_VopDQuant:
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
	cmp	r1, #2
	mov	r6, r2
	mov	r4, r3
	mov	r7, r0
	beq	.L486
	mov	r1, #1
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4]
	cmp	r5, #1
	beq	.L487
.L472:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L486:
	mov	r3, #1
	mov	r1, #3
	strb	r3, [r4, #3]
	strb	r3, [r4]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #7
	addne	r6, r6, #1
	addne	r0, r0, r6
	strneb	r0, [r4, #8]
	beq	.L488
.L471:
	mov	r3, #1
	mov	r0, #1
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L487:
	mov	r1, #2
	mov	r0, r7
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #1]
	cmp	r1, #0
	streq	r5, [r4, #12]
	beq	.L475
	cmp	r1, #2
	beq	.L489
	cmp	r1, #1
	beq	.L490
	cmp	r1, #3
	movne	r3, #0
	strne	r3, [r4, #12]
	beq	.L491
.L475:
	ldr	r3, [r4]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #768
	beq	.L472
	mov	r3, #1
	mov	r1, #3
	strb	r3, [r4, #3]
	mov	r0, r7
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #7
	addne	r6, r6, #1
	addne	r6, r0, r6
	strneb	r6, [r4, #8]
	bne	.L472
	mov	r0, r7
	mov	r1, #5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	strb	r0, [r4, #8]
	b	.L472
.L491:
	mov	r1, r5
	mov	r0, r7
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #2]
	cmp	r0, #0
	movne	r3, #10
	moveq	r3, #11
	str	r3, [r4, #12]
	b	.L475
.L488:
	mov	r0, r7
	mov	r1, #5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	strb	r0, [r4, #8]
	b	.L471
.L489:
	mov	r0, r7
	bl	BsGet
	uxtb	r3, r0
	strb	r0, [r4, #6]
	add	r3, r3, #6
	str	r3, [r4, #12]
	b	.L475
.L490:
	mov	r1, #2
	mov	r0, r7
	bl	BsGet
	uxtb	r3, r0
	strb	r0, [r4, #7]
	add	r3, r3, #2
	str	r3, [r4, #12]
	b	.L475
	UNWIND(.fnend)
	.size	VC1_VopDQuant, .-VC1_VopDQuant
	.align	2
	.global	VC1_DecNormDiff6Tile
	.type	VC1_DecNormDiff6Tile, %function
VC1_DecNormDiff6Tile:
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
	ldr	r9, [r1]
	mov	r8, r1
	mov	r5, r0
	mov	r6, #0
.L493:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	subs	r7, r0, #0
	mov	r0, r5
	bne	.L502
	bl	BsGet
	mov	r4, r0
	cmp	r4, #1
	mov	r1, r0
	mov	r0, r5
	bgt	.L512
	bne	.L496
	bl	BsGet
	cmp	r0, #0
	beq	.L497
	cmp	r6, #0
	mov	r6, r4
	beq	.L493
.L510:
	str	r9, [r8]
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L502:
	mov	r0, #0
.L494:
	cmp	r6, #0
	mov	r7, #1
	eorne	r0, r0, #63
.L511:
	str	r0, [r8]
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L512:
	sub	r4, r4, #2
	mov	r0, #1
	mov	r0, r0, asl r4
	b	.L494
.L496:
	mov	r0, r5
	mov	r1, #4
	bl	BsGet
	cmp	r0, #255
	beq	.L510
	ldr	r3, .L513
	add	r3, r3, r0, lsl #2
	ldr	r0, [r3, #508]
	b	.L494
.L497:
	mov	r0, r5
	mov	r1, #5
	bl	BsGet
	ldr	r3, .L513
	add	r3, r3, r0, lsl #2
	ldr	r3, [r3, #380]
	cmp	r3, #2
	orreq	r0, r0, #32
	beq	.L494
	cmp	r3, #3
	bne	.L511
	b	.L494
.L514:
	.align	2
.L513:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VC1_DecNormDiff6Tile, .-VC1_DecNormDiff6Tile
	.align	2
	.global	VC1_Vfmw_ParseSMPIPicHdr
	.type	VC1_Vfmw_ParseSMPIPicHdr, %function
VC1_Vfmw_ParseSMPIPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #7
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	mov	r1, #5
	strb	r0, [r4, #253]
	mov	r0, r6
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #254]
	cmp	r5, #0
	beq	.L516
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L531
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #36
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #340]
	movhi	r3, #0
	strhib	r3, [r4, #255]
	bls	.L528
.L519:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L529
.L521:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L530
.L523:
	ldrb	r3, [r4, #251]	@ zero_extendqisi2
	sub	r3, r3, #2
	tst	r3, #253
	bne	.L524
.L526:
	ldrb	r1, [r4, #258]	@ zero_extendqisi2
.L525:
	mov	r0, r8
	mov	r5, #1
	bl	VC1_SetCurPicResolutionInfo
	mov	r0, r6
	bl	VC1_DecTransacfrm
	strb	r0, [r4, #267]
	mov	r0, r6
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #268]
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #269]
.L516:
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L524:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L526
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #258]
	b	.L525
.L528:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L519
.L529:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L521
.L530:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L523
.L532:
	.align	2
.L531:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseSMPIPicHdr, .-VC1_Vfmw_ParseSMPIPicHdr
	.align	2
	.global	VC1_Vfmw_ParseSMPPPicHdr
	.type	VC1_Vfmw_ParseSMPPPicHdr, %function
VC1_Vfmw_ParseSMPPPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r7, r1
	mov	r1, #5
	mov	r4, r2
	mov	r5, r0
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #254]
	cmp	r6, #0
	beq	.L546
	ldrb	r8, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L563
	sub	r0, fp, #164
	bl	memcpy
	cmp	r8, #0
	mov	r3, r6
	subeq	r3, fp, #36
	addeq	r3, r3, r6, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r6, #8
	str	r3, [r4, #340]
	movhi	r3, #0
	strhib	r3, [r4, #255]
	bls	.L557
.L538:
	cmp	r8, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L558
.L540:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L559
.L542:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L543
	ldrb	r1, [r4, #258]	@ zero_extendqisi2
.L544:
	ldr	r6, .L563+4
	mov	r0, r7
	bl	VC1_SetCurPicResolutionInfo
	mov	r0, r5
	ldr	r8, [r6, #68]
	bl	BsPos
	ldr	r1, .L563+8
	mov	r2, r0
	mov	r0, #18
	blx	r8
	ldrb	r1, [r4, #340]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #259]
	cmp	r0, #4
	beq	.L560
.L545:
	mov	r1, r7
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L546
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #263]
	mov	r0, r5
	bl	BsGet
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #264]
	bne	.L561
.L547:
	mov	r0, r5
	ldr	r6, [r6, #68]
	bl	BsPos
	ldr	r1, .L563+12
	mov	r2, r0
	mov	r0, #18
	blx	r6
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L562
.L549:
	mov	r0, r5
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #267]
	mov	r0, r5
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #269]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L546:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L557:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L538
.L561:
	add	r3, r4, #272
	ldrb	r2, [r4, #340]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L547
.L559:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L542
.L543:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #258]
	b	.L544
.L558:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L540
.L560:
	ldrb	r1, [r4, #340]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmode2
	mov	r1, #6
	strb	r0, [r4, #260]
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #261]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #262]
	b	.L545
.L562:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #265]
	cmp	r0, #1
	bne	.L549
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #266]
	b	.L549
.L564:
	.align	2
.L563:
	.word	.LANCHOR0+568
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC40
	.word	.LC41
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseSMPPPicHdr, .-VC1_Vfmw_ParseSMPPPicHdr
	.align	2
	.global	VC1_Vfmw_ParseMPBPicHdr
	.type	VC1_Vfmw_ParseMPBPicHdr, %function
VC1_Vfmw_ParseMPBPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #5
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #254]
	cmp	r5, #0
	beq	.L576
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L593
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #36
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #340]
	movhi	r3, #0
	strhib	r3, [r4, #255]
	bls	.L588
.L570:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L589
.L572:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L590
.L574:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #0
	mov	r1, r8
	mov	r2, r4
	cmp	r0, r3
	mov	r0, r6
	moveq	ip, #3
	movne	ip, #1
	strb	ip, [r4, #259]
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L576
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #263]
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #264]
	bne	.L591
.L577:
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L592
.L579:
	mov	r0, r6
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #267]
	mov	r0, r6
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #269]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L576:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L588:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L570
.L591:
	add	r3, r4, #272
	ldrb	r2, [r4, #340]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_VopDQuant
	b	.L577
.L589:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L572
.L590:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L574
.L592:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #265]
	cmp	r0, #1
	bne	.L579
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #266]
	b	.L579
.L594:
	.align	2
.L593:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseMPBPicHdr, .-VC1_Vfmw_ParseMPBPicHdr
	.align	2
	.global	VC1_Vfmw_ParseSMPPicHdr
	.type	VC1_Vfmw_ParseSMPPicHdr, %function
VC1_Vfmw_ParseSMPPicHdr:
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
	ldrb	r8, [r2, #258]	@ zero_extendqisi2
	mov	r5, r0
	mov	r6, r1
	mov	r0, r1
	mov	r4, r2
	mov	r1, r8
	bl	VC1_SetCurPicResolutionInfo
	ldr	r3, [r5, #16]
	cmp	r3, #1
	ble	.L633
	ldr	r7, .L638
	mov	r2, #100
	mov	r1, #0
	add	r0, r4, #248
	add	r9, r6, #32768
	ldr	r3, [r7, #48]
	blx	r3
	add	r0, r6, #23296
	ldr	r3, [r7, #48]
	mov	r2, #12288
	mov	r1, #0
	strb	r8, [r4, #258]
	add	r0, r0, #24
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r2, [r9, #2840]
	mov	r0, #18
	ldr	r1, .L638+4
	blx	r3
	mov	r0, r5
	bl	BsPos
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r4, #324]
	bne	.L598
	ldrb	r2, [r4, #248]	@ zero_extendqisi2
.L599:
	ldr	r3, [r7, #68]
	mov	r0, #18
	ldr	r1, .L638+8
	blx	r3
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #12]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #249]
	bne	.L634
.L600:
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	mov	r1, #1
	mov	r0, r5
	cmp	r3, #0
	bne	.L601
	bl	BsGet
	adds	r0, r0, #0
	movne	r0, #1
	strb	r0, [r4, #251]
.L602:
	mov	r3, #0
	strb	r0, [r6, #2]
	strb	r3, [r6, #4]
	ldrb	r3, [r4, #251]	@ zero_extendqisi2
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L614
.L607:
	.word	.L606
	.word	.L608
	.word	.L609
	.word	.L614
	.word	.L610
.L610:
	ldrb	r8, [r6, #3099]	@ zero_extendqisi2
	cmp	r8, #1
	beq	.L635
.L614:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L633:
	mov	r3, #5
	mov	r0, #1
	strb	r3, [r4, #251]
	strb	r3, [r6, #2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L601:
	bl	BsGet
	cmp	r0, #1
	beq	.L631
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	beq	.L636
	mov	r2, r4
	mov	r3, #2
	add	r1, r4, #344
	strb	r3, [r2, #251]!
	mov	r0, r5
	bl	VC1_DecBfractionSMP
	uxtb	r0, r0
	strb	r0, [r4, #252]
	cmp	r0, #21
	ldrneb	r0, [r4, #251]	@ zero_extendqisi2
	bne	.L602
	b	.L614
.L598:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #248]
	b	.L599
.L636:
	mov	r0, #0
.L631:
	strb	r0, [r4, #251]
	b	.L602
.L609:
	ldrb	r8, [r6, #3099]	@ zero_extendqisi2
	cmp	r8, #1
	bne	.L614
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseMPBPicHdr
	cmp	r0, #1
	mov	r6, r0
	beq	.L611
	mov	r0, r8
	ldr	r3, [r7, #68]
	ldr	r1, .L638+12
	blx	r3
	b	.L611
.L608:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPPPicHdr
	mov	r6, r0
.L611:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #324]
	rsb	r0, r3, r0
	str	r0, [r4, #324]
	mov	r0, r5
	ldr	r4, [r9, #2864]
	bl	BsPos
	mov	r4, r4, asl #3
	rsb	r0, r0, r4
	cmp	r0, #0
	ble	.L637
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L606:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPIPicHdr
	mov	r6, r0
	b	.L611
.L634:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #250]
	b	.L600
.L637:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L638+16
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L635:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPIPicHdr
	cmp	r0, #1
	mov	r6, r0
	beq	.L611
	mov	r0, r8
	ldr	r3, [r7, #68]
	ldr	r1, .L638+20
	blx	r3
	b	.L611
.L639:
	.align	2
.L638:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC42
	.word	.LC43
	.word	.LC44
	.word	.LC46
	.word	.LC45
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseSMPPicHdr, .-VC1_Vfmw_ParseSMPPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvSeqHdr
	.type	VC1_Vfmw_ParseAdvSeqHdr, %function
VC1_Vfmw_ParseAdvSeqHdr:
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
	ldr	r3, .L657
	mov	r5, r0
	mov	r4, r2
	mov	r1, #0
	add	r0, r2, #16
	mov	r2, #172
	ldr	r3, [r3, #48]
	mov	r6, #2
	blx	r3
	mov	r0, r5
	bl	BsPos
	mov	r1, r6
	str	r0, [r4, #184]
	mov	r0, r5
	bl	BsGet
	strb	r6, [r4, #16]
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	strb	r0, [r4, #17]
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #18]
	mov	r0, r5
	bl	BsGet
	mov	r1, #5
	strb	r0, [r4, #19]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #20]
	mov	r0, r5
	bl	BsGet
	mov	r1, #12
	strb	r0, [r4, #21]
	mov	r0, r5
	bl	BsGet
	mov	r1, #12
	uxth	r3, r0
	mov	r0, r5
	add	r3, r3, #1
	mov	r3, r3, asl #1
	strh	r3, [r4, #172]	@ movhi
	bl	BsGet
	mov	r1, #1
	uxth	r3, r0
	mov	r0, r5
	add	r3, r3, r1
	mov	r3, r3, asl r1
	strh	r3, [r4, #174]	@ movhi
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #22]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #24]
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	strb	r0, [r4, #25]
	mov	r0, r5
	bl	BsSkip
	mov	r0, r5
	mov	r1, #1
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #26]
	cmp	r6, #1
	beq	.L654
	ldrh	r2, [r4, #172]
	ldrh	r3, [r4, #174]
	strh	r2, [r4, #176]	@ movhi
	strh	r3, [r4, #178]	@ movhi
.L647:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #39]
	cmp	r0, #1
	beq	.L648
.L650:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #184]
	mov	r2, #1
	rsb	r0, r3, r0
	str	r0, [r4, #184]
.L649:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L648:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #40]
	cmp	r0, #31
	movhi	r2, #0
	bhi	.L649
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	mov	r1, #4
	strb	r0, [r4, #41]
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #42]
	ble	.L650
	add	r7, r4, #42
	mov	r6, #0
.L651:
	mov	r1, #16
	mov	r0, r5
	bl	BsGet
	mov	r1, #16
	add	r6, r6, #1
	strh	r0, [r7, #2]!	@ movhi
	mov	r0, r5
	bl	BsGet
	strh	r0, [r7, #64]	@ movhi
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, r6
	bgt	.L651
	b	.L650
.L654:
	mov	r1, #14
	mov	r0, r5
	bl	BsGet
	mov	r1, #14
	add	r3, r0, #1
	mov	r0, r5
	strh	r3, [r4, #176]	@ movhi
	bl	BsGet
	mov	r1, r6
	add	r3, r0, #1
	mov	r0, r5
	strh	r3, [r4, #178]	@ movhi
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #27]
	cmp	r0, #1
	beq	.L655
.L643:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #31]
	cmp	r1, #1
	beq	.L656
.L645:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #35]
	cmp	r0, #1
	bne	.L647
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #36]
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #37]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #38]
	b	.L647
.L656:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #32]
	cmp	r0, #0
	bne	.L646
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #4
	strb	r0, [r4, #33]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #34]
	b	.L645
.L655:
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #28]
	cmp	r0, #15
	bne	.L643
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #29]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #30]
	b	.L643
.L646:
	mov	r1, #16
	mov	r0, r5
	bl	BsGet
	strh	r0, [r4, #180]	@ movhi
	b	.L645
.L658:
	.align	2
.L657:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvSeqHdr, .-VC1_Vfmw_ParseAdvSeqHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvEntptHdr
	.type	VC1_Vfmw_ParseAdvEntptHdr, %function
VC1_Vfmw_ParseAdvEntptHdr:
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
	ldr	r3, .L684
	mov	r4, r2
	mov	r5, r0
	mov	r1, #0
	add	r0, r2, #188
	mov	r2, #60
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r5
	bl	BsPos
	mov	r1, #1
	str	r0, [r4, #244]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #188]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #189]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #190]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #191]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #192]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #193]
	mov	r0, r5
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #194]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #195]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #196]
	mov	r0, r5
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #197]
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #39]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #198]
	beq	.L660
.L663:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #199]
	cmp	r0, #1
	ldrneh	r2, [r4, #240]
	beq	.L680
.L665:
	ldrh	r1, [r4, #238]
	ldrh	r0, [r4, #172]
	cmp	r1, #15
	movhi	r3, #0
	movls	r3, #1
	cmp	r1, r0
	orrhi	r3, r3, #1
	ldrb	r1, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #0
	ldrh	r3, [r4, #174]
	strneh	r0, [r4, #238]	@ movhi
	cmp	r3, r2
	cmpcs	r2, #15
	strlsh	r3, [r4, #240]	@ movhi
	cmp	r1, #1
	beq	.L681
.L668:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #201]
	cmp	r0, #1
	beq	.L682
.L669:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #203]
	cmp	r0, #1
	beq	.L683
.L670:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #244]
	rsb	r3, r3, r0
	mov	r0, #1
	str	r3, [r4, #244]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L660:
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, #0
	ble	.L663
	add	r7, r4, #204
	mov	r6, #0
.L664:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, r6
	bgt	.L664
	b	.L663
.L683:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #204]
	b	.L670
.L680:
	mov	r1, #12
	mov	r0, r5
	bl	BsGet
	mov	r1, #12
	add	r3, r0, #1
	mov	r0, r5
	mov	r3, r3, asl #1
	strh	r3, [r4, #238]	@ movhi
	bl	BsGet
	add	r0, r0, #1
	mov	r2, r0, asl #1
	uxth	r2, r2
	strh	r2, [r4, #240]	@ movhi
	b	.L665
.L681:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #200]
	b	.L668
.L682:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #202]
	b	.L669
.L685:
	.align	2
.L684:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvEntptHdr, .-VC1_Vfmw_ParseAdvEntptHdr
	.align	2
	.global	VC1_DecFcm
	.type	VC1_DecFcm, %function
VC1_DecFcm:
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
	mov	r1, #2
	mov	r5, r0
	bl	BsShow
	mov	r4, r0
	cmp	r4, #1
	mov	r0, r5
	ble	.L689
	mov	r1, #2
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L689:
	mov	r1, #1
	mov	r4, #0
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_DecFcm, .-VC1_DecFcm
	.align	2
	.global	VC1_DecAdvPtype
	.type	VC1_DecAdvPtype, %function
VC1_DecAdvPtype:
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
	mov	r1, #4
	mov	r4, r0
	bl	BsShow
	cmp	r0, #7
	movle	r1, #1
	movle	r5, r1
	ble	.L691
	cmp	r0, #11
	movle	r1, #2
	movle	r5, r1
	bgt	.L696
.L691:
	mov	r0, r4
	bl	BsSkip
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L696:
	cmp	r0, #13
	movle	r1, #3
	movle	r5, #0
	ble	.L691
	cmp	r0, #14
	mov	r1, #4
	movne	r5, #5
	moveq	r5, r1
	b	.L691
	UNWIND(.fnend)
	.size	VC1_DecAdvPtype, .-VC1_DecAdvPtype
	.align	2
	.global	VC1_Vfmw_ParseAdvIPicHdr
	.type	VC1_Vfmw_ParseAdvIPicHdr, %function
VC1_Vfmw_ParseAdvIPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #1
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	ldrb	r1, [r4, #23]	@ zero_extendqisi2
	cmp	r1, #1
	strb	r0, [r4, #348]
	beq	.L713
.L698:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	bne	.L699
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L714
.L699:
	mov	r1, #5
	mov	r0, r6
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #358]
	cmp	r5, #0
	beq	.L708
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L718
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #36
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L715
.L704:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L716
.L706:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L717
.L707:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r6
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L708
	mov	r0, r6
	bl	VC1_DecTransacfrm
	strb	r0, [r4, #370]
	mov	r0, r6
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #371]
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #372]
	moveq	r0, #1
	beq	.L701
	mov	r0, r6
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	bl	VC1_VopDQuant
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L708:
	mov	r0, #0
.L701:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L715:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L704
.L714:
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #357]
	b	.L699
.L713:
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #356]
	b	.L698
.L716:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L706
.L717:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L707
.L719:
	.align	2
.L718:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvIPicHdr, .-VC1_Vfmw_ParseAdvIPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvPPicHdr
	.type	VC1_Vfmw_ParseAdvPPicHdr, %function
VC1_Vfmw_ParseAdvPPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #1
	mov	r4, r2
	mov	r5, r0
	bl	BsGet
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #348]
	beq	.L721
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L721
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L758
.L723:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #358]
	cmp	r6, #0
	beq	.L738
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L771
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r6
	subeq	r3, fp, #36
	addeq	r3, r3, r6, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r6, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L759
.L728:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L760
.L730:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L761
.L731:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L762
.L732:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	beq	.L763
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #373]
	beq	.L764
.L736:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #374]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #468]
	beq	.L765
.L737:
	mov	r3, #0
	strb	r3, [r4, #382]
.L734:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L738
	ldr	r1, [r4, #392]
	cmp	r1, #2
	beq	.L766
.L739:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #392]
	cmp	r3, #0
	moveq	r1, #2
	movne	r1, #3
	strb	r0, [r4, #366]
	mov	r0, r5
	bl	BsGet
	ldr	r6, [r4, #392]
	cmp	r6, #2
	uxtb	r0, r0
	strb	r0, [r4, #367]
	beq	.L767
.L742:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L768
.L744:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L769
.L746:
	mov	r0, r5
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r5
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #372]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L738:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L721:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	strb	r0, [r4, #356]
	bne	.L723
.L758:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	bne	.L723
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #357]
	b	.L723
.L763:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #362]
	cmp	r0, #4
	bne	.L734
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmode2
	mov	r1, #6
	strb	r0, [r4, #363]
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #364]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #365]
	b	.L734
.L759:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L728
.L768:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L744
.L762:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L732
.L760:
	mov	r1, r7
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L730
.L761:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L731
.L769:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L746
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L746
.L767:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #374]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #376]
	movne	r0, #0
	beq	.L770
.L743:
	strb	r0, [r4, #377]
	b	.L742
.L766:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #375]
	b	.L739
.L764:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L736
.L765:
	mov	r1, #6
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #364]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #365]
	b	.L737
.L770:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	b	.L743
.L772:
	.align	2
.L771:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvPPicHdr, .-VC1_Vfmw_ParseAdvPPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvBPicHdr
	.type	VC1_Vfmw_ParseAdvBPicHdr, %function
VC1_Vfmw_ParseAdvBPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r7, r1
	mov	r1, #1
	mov	r4, r2
	mov	r5, r0
	bl	BsGet
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #348]
	beq	.L774
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L774
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L816
.L776:
	cmp	r3, #0
	bne	.L780
	add	r1, r4, #496
	mov	r0, r5
	bl	VC1_DecBfraction
	uxtb	r0, r0
	strb	r0, [r4, #350]
	cmp	r0, #21
	beq	.L778
.L780:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #358]
	cmp	r6, #0
	beq	.L778
	ldrb	r8, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L828
	sub	r0, fp, #164
	bl	memcpy
	cmp	r8, #0
	mov	r3, r6
	subeq	r3, fp, #36
	addeq	r3, r3, r6, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r6, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L817
	cmp	r8, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L818
.L786:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L819
.L787:
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L820
.L788:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L821
.L789:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	beq	.L822
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L823
.L793:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #468]
.L792:
	mov	r1, r7
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L778
	ldr	r1, [r4, #392]
	cmp	r1, #2
	beq	.L824
.L794:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #392]
	cmp	r3, #0
	moveq	r1, #2
	movne	r1, #3
	strb	r0, [r4, #366]
	mov	r0, r5
	bl	BsGet
	ldr	r6, [r4, #392]
	cmp	r6, #2
	uxtb	r0, r0
	strb	r0, [r4, #367]
	beq	.L825
.L797:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L826
.L798:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L827
.L800:
	mov	r0, r5
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r5
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #372]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L778:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L774:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	ldr	r3, [r4, #392]
	cmp	r1, #1
	strb	r0, [r4, #356]
	bne	.L776
.L816:
	cmp	r3, #0
	bne	.L780
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #392]
	strb	r0, [r4, #357]
	b	.L776
.L822:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	moveq	r3, #3
	movne	r3, #1
	strb	r3, [r4, #362]
	b	.L792
.L817:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #198]	@ zero_extendqisi2
	cmp	r8, #1
	movne	r3, #0
	strb	r0, [r4, #351]
	strneb	r3, [r4, #359]
	bne	.L786
.L818:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L786
.L820:
	add	r1, r4, #496
	mov	r0, r5
	bl	VC1_DecBfraction
	strb	r0, [r4, #350]
	b	.L788
.L821:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L789
.L819:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L787
.L826:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L798
.L827:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L800
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L800
.L825:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	strb	r0, [r4, #376]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #377]
	b	.L797
.L824:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #375]
	b	.L794
.L823:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L793
.L829:
	.align	2
.L828:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvBPicHdr, .-VC1_Vfmw_ParseAdvBPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvFramePicHdr
	.type	VC1_Vfmw_ParseAdvFramePicHdr, %function
VC1_Vfmw_ParseAdvFramePicHdr:
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
	mov	r6, r1
	mov	r1, #4
	mov	r4, r2
	mov	r5, r0
	bl	BsShow
	cmp	r0, #7
	movle	r7, #1
	movle	r1, r7
	ble	.L831
	cmp	r0, #11
	movle	r7, #2
	movle	r1, r7
	bgt	.L862
.L831:
	mov	r0, r5
	bl	BsSkip
	strb	r7, [r4, #349]
	ldrb	r3, [r6, #3513]	@ zero_extendqisi2
	strb	r3, [r6, #2]
	ldrb	r3, [r4, #24]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L863
.L832:
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	beq	.L833
	cmp	r3, #0
	beq	.L864
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #352]
	mov	r0, r5
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #353]
	beq	.L865
.L837:
	cmp	r3, #1
	bne	.L839
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	ldrb	r3, [r4, #354]	@ zero_extendqisi2
	cmp	r1, #1
	add	r3, r3, #1
	str	r3, [r4, #492]
	bne	.L848
.L840:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #355]
	cmp	r0, #1
	bne	.L848
	ldr	r3, [r4, #492]
	cmp	r3, #0
	ble	.L848
	mov	r7, r4
	mov	r8, #0
.L849:
	mov	r1, #18
	mov	r0, r5
	bl	BsGet
	mov	r1, #18
	add	r8, r8, #1
	add	r7, r7, #4
	str	r0, [r7, #396]
	mov	r0, r5
	bl	BsGet
	mov	r1, #14
	str	r0, [r7, #412]
	mov	r0, r5
	bl	BsGet
	mov	r1, #14
	str	r0, [r7, #428]
	mov	r0, r5
	bl	BsGet
	str	r0, [r7, #444]
	ldr	r3, [r4, #492]
	cmp	r3, r8
	bgt	.L849
	b	.L848
.L833:
	mov	r2, #1
	cmp	r3, r2
	strb	r2, [r4, #352]
	beq	.L836
.L839:
	mov	r3, #1
	str	r3, [r4, #492]
.L838:
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L840
.L848:
	ldrb	r3, [r4, #349]	@ zero_extendqisi2
	cmp	r3, #5
	ldrls	pc, [pc, r3, asl #2]
	b	.L841
.L843:
	.word	.L846
	.word	.L844
	.word	.L845
	.word	.L841
	.word	.L846
	.word	.L854
.L846:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvIPicHdr
.L864:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #354]
	bne	.L837
.L865:
	cmp	r3, #1
	beq	.L866
.L836:
	mov	r3, #2
	str	r3, [r4, #492]
	b	.L838
.L862:
	cmp	r0, #13
	movle	r7, #0
	movle	r1, #3
	ble	.L831
	cmp	r0, #14
	moveq	r7, #4
	movne	r7, #5
	movne	r1, #4
	moveq	r1, r7
	b	.L831
.L863:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #396]
	b	.L832
.L854:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L844:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvPPicHdr
.L845:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvBPicHdr
.L841:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L866:
	ldrb	r3, [r4, #353]	@ zero_extendqisi2
	add	r3, r3, #2
	str	r3, [r4, #492]
	b	.L838
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvFramePicHdr, .-VC1_Vfmw_ParseAdvFramePicHdr
	.align	2
	.global	VC1_DecRefdist
	.type	VC1_DecRefdist, %function
VC1_DecRefdist:
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
	mov	r1, #5
	mov	r5, r0
	bl	BsShow
	cmp	r0, #23
	bgt	.L868
	mov	r4, r0, asr #3
	mov	r1, #2
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L868:
	cmp	r0, #27
	movle	r4, #3
	bgt	.L874
.L870:
	mov	r0, r5
	mov	r1, r4
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L874:
	cmp	r0, #29
	movgt	r4, #5
	movle	r4, #4
	b	.L870
	UNWIND(.fnend)
	.size	VC1_DecRefdist, .-VC1_DecRefdist
	.align	2
	.global	VC1_DecIntCompField
	.type	VC1_DecIntCompField, %function
VC1_DecIntCompField:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	lr, .L876
	mov	r4, r0
	sub	ip, fp, #52
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	mov	r0, r4
	mov	r1, #2
	bl	BsShow
	sub	r3, fp, #20
	add	r3, r3, r0, lsl #3
	mov	r0, r4
	ldr	r1, [r3, #-28]
	ldr	r4, [r3, #-32]
	bl	BsSkip
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L877:
	.align	2
.L876:
	.word	.LANCHOR0+696
	UNWIND(.fnend)
	.size	VC1_DecIntCompField, .-VC1_DecIntCompField
	.align	2
	.global	VC1_Vfmw_ParseAdvIFieldHdr
	.type	VC1_Vfmw_ParseAdvIFieldHdr, %function
VC1_Vfmw_ParseAdvIFieldHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #5
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #358]
	cmp	r5, #0
	beq	.L887
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L895
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #36
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L892
.L883:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L893
.L885:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L894
.L886:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r6
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L887
	mov	r0, r6
	bl	VC1_DecTransacfrm
	strb	r0, [r4, #370]
	mov	r0, r6
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #371]
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #372]
	moveq	r0, #1
	beq	.L880
	mov	r0, r6
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	bl	VC1_VopDQuant
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L887:
	mov	r0, #0
.L880:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L892:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L883
.L893:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L885
.L894:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L886
.L896:
	.align	2
.L895:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvIFieldHdr, .-VC1_Vfmw_ParseAdvIFieldHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvPFieldHdr
	.type	VC1_Vfmw_ParseAdvPFieldHdr, %function
VC1_Vfmw_ParseAdvPFieldHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #128)
	sub	sp, sp, #128
	mov	r1, #5
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #358]
	cmp	r5, #0
	beq	.L898
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L935
	sub	r0, fp, #156
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #28
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L926
.L901:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L927
.L903:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L928
.L904:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #380]
	cmp	r0, #0
	beq	.L929
.L905:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L930
.L906:
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L931
.L907:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #362]
	cmp	r0, #4
	beq	.L932
.L909:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #380]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r1, #2
	movne	r1, #3
	strb	r0, [r4, #375]
	mov	r0, r6
	bl	BsGet
	mov	r1, #3
	uxtb	r0, r0
	strb	r0, [r4, #366]
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #362]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #367]
	beq	.L913
	movw	r3, #362
	ldrh	r3, [r4, r3]
	cmp	r3, #4
	beq	.L913
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L933
.L915:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L934
.L917:
	mov	r0, r6
	mov	r5, #1
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #372]
.L898:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L913:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #377]
	beq	.L915
.L933:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_VopDQuant
	b	.L915
.L929:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	clz	r0, r0
	mov	r0, r0, lsr #5
	strb	r0, [r4, #381]
	b	.L905
.L926:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L901
.L930:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L906
.L931:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L907
.L927:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L903
.L934:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L917
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L917
.L928:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L904
.L932:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_DecMvmode2
	strb	r0, [r4, #363]
	mov	r0, r6
	bl	VC1_DecIntCompField
	mov	r1, #6
	str	r0, [r4, #476]
	mov	r0, r6
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #364]
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r4, #476]
	cmp	r3, #0
	strb	r0, [r4, #365]
	bne	.L909
	mov	r1, #6
	mov	r0, r6
	bl	BsGet
	mov	r1, #6
	str	r0, [r4, #480]
	mov	r0, r6
	bl	BsGet
	str	r0, [r4, #484]
	b	.L909
.L936:
	.align	2
.L935:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvPFieldHdr, .-VC1_Vfmw_ParseAdvPFieldHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvBFieldHdr
	.type	VC1_Vfmw_ParseAdvBFieldHdr, %function
VC1_Vfmw_ParseAdvBFieldHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r3, #1
	mov	r8, r1
	strb	r3, [r2, #380]
	mov	r1, #5
	mov	r4, r2
	mov	r5, r0
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #358]
	cmp	r6, #0
	beq	.L948
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L968
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r6
	subeq	r3, fp, #36
	addeq	r3, r3, r6, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r6, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L960
.L942:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L961
.L944:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L962
.L945:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L963
.L946:
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L964
.L947:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmodeInterB
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	strb	r0, [r4, #362]
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L948
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #375]
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #366]
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #362]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #367]
	beq	.L965
.L949:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L966
.L950:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L967
.L952:
	mov	r0, r5
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r5
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #372]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L948:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L960:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L942
.L966:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L950
.L965:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #377]
	b	.L949
.L962:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L945
.L963:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L946
.L961:
	mov	r1, r7
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L944
.L964:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L947
.L967:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L952
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L952
.L969:
	.align	2
.L968:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvBFieldHdr, .-VC1_Vfmw_ParseAdvBFieldHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvFieldPicHdr
	.type	VC1_Vfmw_ParseAdvFieldPicHdr, %function
VC1_Vfmw_ParseAdvFieldPicHdr:
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
	ldrb	r3, [r1, #8]	@ zero_extendqisi2
	mov	r5, r1
	mov	r6, r0
	mov	r4, r2
	cmp	r3, #0
	beq	.L971
	add	r3, r1, #20480
	ldr	r3, [r3, #2836]
	cmp	r3, #0
	ble	.L972
.L971:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	ldr	r3, .L1016
	str	r0, [r4, #472]
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #732]
	ldr	r2, [r0, #728]
	str	r3, [r4, #504]
	str	r2, [r4, #500]
	ldrb	r1, [r5, #8]	@ zero_extendqisi2
	cmp	r1, #0
	uxtbeq	r3, r2
	uxtbne	r3, r3
	strb	r3, [r4, #349]
	ldrb	r3, [r5, #3513]	@ zero_extendqisi2
	strb	r3, [r5, #2]
	ldrb	r3, [r4, #24]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1010
.L975:
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	bne	.L1011
	mov	r2, #1
	cmp	r3, r2
	strb	r2, [r4, #352]
	beq	.L979
.L982:
	mov	r3, #1
	str	r3, [r4, #492]
.L981:
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L983
.L986:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #348]
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #191]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #356]
	beq	.L1012
.L985:
	ldr	r3, [r4, #472]
	cmp	r3, #3
	bgt	.L990
.L989:
	ldrb	r3, [r4, #349]	@ zero_extendqisi2
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L998
.L993:
	.word	.L992
	.word	.L994
	.word	.L995
	.word	.L998
	.word	.L992
.L1011:
	cmp	r3, #0
	bne	.L977
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	strb	r0, [r4, #354]
.L978:
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1013
	cmp	r3, #1
	bne	.L982
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	ldrb	r3, [r4, #354]	@ zero_extendqisi2
	cmp	r1, #1
	add	r3, r3, #1
	str	r3, [r4, #492]
	bne	.L986
.L983:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #355]
	cmp	r0, #1
	bne	.L986
	ldr	r3, [r4, #492]
	cmp	r3, #0
	ble	.L986
	mov	r7, r4
	mov	r8, #0
.L987:
	mov	r1, #18
	mov	r0, r6
	bl	BsGet
	mov	r1, #18
	add	r8, r8, #1
	add	r7, r7, #4
	str	r0, [r7, #396]
	mov	r0, r6
	bl	BsGet
	mov	r1, #14
	str	r0, [r7, #412]
	mov	r0, r6
	bl	BsGet
	mov	r1, #14
	str	r0, [r7, #428]
	mov	r0, r6
	bl	BsGet
	str	r0, [r7, #444]
	ldr	r3, [r4, #492]
	cmp	r3, r8
	bgt	.L987
	b	.L986
.L995:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvBFieldHdr
.L991:
	ldrb	r3, [r4, #352]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	bne	.L1014
.L996:
	subs	r3, r3, #1
	movne	r3, #1
	strb	r3, [r4, #389]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L994:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvPFieldHdr
	ldrb	r3, [r4, #352]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	beq	.L996
.L1014:
	adds	r3, r3, #0
	movne	r3, #1
	strb	r3, [r4, #389]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L992:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvIFieldHdr
	b	.L991
.L1012:
	ldr	r3, [r4, #472]
	cmp	r3, #3
	ble	.L988
.L990:
	add	r1, r4, #496
	mov	r0, r6
	bl	VC1_DecBfraction
	strb	r0, [r4, #350]
	b	.L989
.L1010:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	str	r0, [r4, #396]
	b	.L975
.L1013:
	cmp	r3, #1
	beq	.L1015
.L979:
	mov	r3, #2
	str	r3, [r4, #492]
	b	.L981
.L977:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #352]
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	strb	r0, [r4, #353]
	b	.L978
.L998:
	mov	r0, #0
	b	.L991
.L988:
	mov	r0, r6
	bl	VC1_DecRefdist
	strb	r0, [r4, #379]
	b	.L985
.L1015:
	ldrb	r3, [r4, #353]	@ zero_extendqisi2
	add	r3, r3, #2
	str	r3, [r4, #492]
	b	.L981
.L972:
	ldr	r3, [r2, #504]
	strb	r3, [r2, #349]
	ldrb	r3, [r1, #3513]	@ zero_extendqisi2
	strb	r3, [r1, #2]
	b	.L989
.L1017:
	.align	2
.L1016:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvFieldPicHdr, .-VC1_Vfmw_ParseAdvFieldPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvPicHdr
	.type	VC1_Vfmw_ParseAdvPicHdr, %function
VC1_Vfmw_ParseAdvPicHdr:
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
	mov	r4, r1
	mov	r6, r0
	mov	r1, #0
	mov	r0, r4
	mov	r5, r2
	bl	VC1_SetCurPicResolutionInfo
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1019
	add	r3, r4, #20480
	ldr	r3, [r3, #2836]
	cmp	r3, #0
	ldrle	r3, [r5, #392]
	bicle	r3, r3, #2
	ble	.L1020
.L1019:
	ldrb	r8, [r5, #23]	@ zero_extendqisi2
	cmp	r8, #1
	movne	r3, #0
	movne	r0, r3
	beq	.L1028
.L1021:
	str	r0, [r5, #392]
.L1020:
	cmp	r3, #0
	mov	r2, r5
	mov	r1, r4
	mov	r0, r6
	beq	.L1029
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvFieldPicHdr
.L1029:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvFramePicHdr
.L1028:
	mov	r1, #2
	mov	r0, r6
	bl	BsShow
	cmp	r0, #1
	mov	r7, r0
	ble	.L1030
	mov	r1, #2
	mov	r0, r6
	bl	BsSkip
	bic	r3, r7, #2
	mov	r0, r7
	b	.L1021
.L1030:
	mov	r1, r8
	mov	r0, r6
	bl	BsSkip
	mov	r3, #0
	mov	r0, r3
	b	.L1021
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvPicHdr, .-VC1_Vfmw_ParseAdvPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvSlcHdr
	.type	VC1_Vfmw_ParseAdvSlcHdr, %function
VC1_Vfmw_ParseAdvSlcHdr:
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
	add	r3, r1, #20480
	mov	r5, r1
	mov	r1, #9
	mov	r6, r2
	ldr	r4, [r3, #2836]
	mov	r7, r0
	bl	BsGet
	mov	r1, #1
	mov	r3, r4, asl #4
	sub	r4, r3, r4, asl #2
	add	r4, r6, r4
	add	r4, r4, #520
	str	r0, [r4, #8]
	mov	r0, r7
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #1
	beq	.L1033
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1033:
	add	lr, r6, #188
	add	ip, r5, #6912
	add	ip, ip, #36
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	add	r0, r5, #6720
	add	r1, r6, #16
	mov	r2, #172
	add	r0, r0, #56
	bl	memcpy
	add	r0, r5, #7104
	add	r1, r6, #348
	mov	r2, #176
	add	r0, r0, #4
	bl	memcpy
	add	r2, r5, #6720
	mov	r0, r7
	add	r2, r2, #40
	mov	r1, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvPicHdr
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvSlcHdr, .-VC1_Vfmw_ParseAdvSlcHdr
	.align	2
	.global	VC1_Vfmw_next_start_code
	.type	VC1_Vfmw_next_start_code, %function
VC1_Vfmw_next_start_code:
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
	bgt	.L1037
	b	.L1038
.L1043:
	bl	BsSkip
	cmp	r4, r6
	beq	.L1038
.L1037:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L1043
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1038:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_next_start_code, .-VC1_Vfmw_next_start_code
	.align	2
	.global	VC1_Vfmw_UserData
	.type	VC1_Vfmw_UserData, %function
VC1_Vfmw_UserData:
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
	.size	VC1_Vfmw_UserData, .-VC1_Vfmw_UserData
	.align	2
	.global	VC1_RecordSlcStream
	.type	VC1_RecordSlcStream, %function
VC1_RecordSlcStream:
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
	add	r7, r0, #20480
	ldr	r3, [r0, #3128]
	mov	r5, r0
	ldr	r6, [r7, #2836]
	movw	lr, #23328
	mov	r10, r1
	movw	r0, #23320
	movw	ip, #23336
	mov	r9, r6, asl #4
	mov	r8, r6, asl #6
	rsb	r4, r9, r8
	add	r4, r5, r4
	strb	r6, [r4, lr]
	ldr	r1, [r3, #24]
	cmp	r1, #0
	add	lr, r1, #7
	movge	lr, r1
	add	r1, r4, #23296
	add	r2, r2, lr, asr #3
	str	r2, [r4, r0]
	ldr	lr, [r3, #24]
	add	r2, r1, #32
	str	r2, [fp, #-48]
	and	lr, lr, #7
	str	lr, [r4, ip]
	ldr	ip, [r3, #16]
	ldr	lr, [r3, #24]
	add	r3, r1, #24
	str	r3, [fp, #-52]
	rsb	ip, lr, ip, lsl #3
	str	ip, [r1, #44]
	ldr	r0, [r4, r0]
	str	r3, [fp, #-56]
	bl	MEM_Vir2Phy
	ldr	r2, [fp, #-48]
	add	r1, r5, #32768
	movw	lr, #23360
	add	ip, r4, #23296
	add	ip, ip, #64
	str	r0, [r2, #4]
	ldr	r2, [r1, #2872]
	str	r2, [r4, lr]
	ldr	r2, [r1, #2848]
	cmp	r2, #0
	beq	.L1046
	ldr	r0, [r1, #2860]
	ldr	r3, [fp, #-52]
	cmp	r0, #0
	bne	.L1065
.L1046:
	rsb	r3, r9, r8
	movw	lr, #23352
	add	r3, r5, r3
	mov	r2, #0
	add	ip, r3, #23296
	str	r2, [ip, #28]
	str	r2, [r3, lr]
	str	r2, [ip, #60]
	str	r2, [ip, #52]
	str	r2, [ip, #68]
.L1047:
	ldr	lr, [r7, #2756]
	sub	r6, r9, r6, asl #2
	ldr	ip, [r7, #2752]
	ldrb	r4, [r5, #8]	@ zero_extendqisi2
	mul	ip, ip, lr
	cmp	r4, #0
	sub	ip, ip, #1
	beq	.L1048
	add	r10, r10, r6
	add	r3, lr, #1
	rsb	r1, r9, r8
	movw	r0, #23344
	ldr	r2, [r10, #528]
	add	r3, r3, r3, lsr #31
	add	r1, r5, r1
	add	r10, r10, #520
	sub	r3, r2, r3, asr #1
	cmp	ip, r3
	str	r3, [r1, r0]
	movcs	ip, #0
	movcc	ip, #1
	cmp	r3, #0
	movle	ip, #0
	cmp	ip, #0
	bne	.L1066
.L1049:
	rsb	r0, r9, r8
	add	r0, r5, r0
	add	r3, r0, #23296
	add	r3, r3, #40
	ldr	r3, [r3, #4]
	cmp	r3, #0
	ble	.L1051
	add	r3, r0, #23296
	add	r3, r3, #24
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1052
	add	r0, r0, #23296
	ldr	r3, [r0, #60]
	cmp	r3, #0
	ble	.L1051
.L1052:
	ldr	r3, [r7, #2836]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r7, #2836]
.L1050:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1048:
	add	r6, r10, r6
	rsb	r2, r9, r8
	add	r2, r5, r2
	movw	r1, #23344
	ldr	r3, [r6, #528]
	add	r6, r6, #520
	cmp	ip, r3
	str	r3, [r2, r1]
	bcs	.L1049
	ldr	lr, .L1067
	mov	r0, #1
	ldr	r2, [r6, #8]
	ldr	r1, .L1067+4
	str	ip, [sp]
	ldr	r5, [lr, #68]
	blx	r5
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1065:
	movw	lr, #23352
	str	r2, [r3, #4]
	mov	r3, #0
	str	r3, [r4, lr]
	ldr	r2, [r1, #2868]
	add	r3, r4, #23296
	str	r0, [r3, #52]
	mov	r2, r2, asl #3
	str	r2, [r3, #60]
	ldr	r3, [r1, #2876]
	str	r3, [ip, #4]
	b	.L1047
.L1066:
	ldr	ip, .L1067
	mov	r0, #1
	ldr	r2, [r10, #8]
	ldr	r1, .L1067+8
	str	lr, [sp]
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	b	.L1050
.L1051:
	ldr	r3, .L1067
	mov	r0, #1
	ldr	r1, .L1067+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1068:
	.align	2
.L1067:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC48
	.word	.LC47
	.word	.LC49
	UNWIND(.fnend)
	.size	VC1_RecordSlcStream, .-VC1_RecordSlcStream
	.align	2
	.global	VC1_Vfmw_UpdateAdvSPS
	.type	VC1_Vfmw_UpdateAdvSPS, %function
VC1_Vfmw_UpdateAdvSPS:
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
	add	r5, r0, #8192
	movw	r3, #2402
	ldrh	r2, [r1, #238]
	mov	r4, r1
	ldrh	r3, [r5, r3]
	cmp	r3, r2
	beq	.L1070
	adds	r3, r2, #15
	add	r0, r0, #20480
	addmi	r3, r2, #30
	movw	r1, #2404
	mov	r3, r3, asr #4
	str	r3, [r0, #2752]
	ldrh	r3, [r4, #238]
	str	r3, [r0, #2768]
	ldrh	r2, [r4, #240]
	ldrh	r3, [r5, r1]
	cmp	r3, r2
	beq	.L1071
.L1072:
	adds	r3, r2, #15
	addmi	r3, r2, #30
	mov	r3, r3, asr #4
	str	r3, [r0, #2756]
	ldrh	r3, [r4, #240]
	str	r3, [r0, #2772]
.L1071:
	add	r0, r5, #2176
	add	r1, r4, #16
	mov	r2, #172
	add	r0, r0, #4
	bl	memcpy
	add	lr, r4, #188
	add	ip, r5, #2352
	mov	r4, #1
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
.L1075:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1070:
	movw	r3, #2404
	ldrh	r2, [r1, #240]
	ldrh	r3, [r5, r3]
	cmp	r3, r2
	addne	r0, r0, #20480
	bne	.L1072
	mov	r4, #0
	b	.L1075
	UNWIND(.fnend)
	.size	VC1_Vfmw_UpdateAdvSPS, .-VC1_Vfmw_UpdateAdvSPS
	.align	2
	.global	VC1_Vfmw_UpdataLastPicRNDCTRL
	.type	VC1_Vfmw_UpdataLastPicRNDCTRL, %function
VC1_Vfmw_UpdataLastPicRNDCTRL:
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
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1078
	bl	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
.L1078:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_UpdataLastPicRNDCTRL, .-VC1_Vfmw_UpdataLastPicRNDCTRL
	.align	2
	.global	VC1_Vfmw_DecPQUANT
	.type	VC1_Vfmw_DecPQUANT, %function
VC1_Vfmw_DecPQUANT:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #128)
	sub	sp, sp, #128
	mov	r2, #128
	mov	r4, r1
	mov	r5, r0
	ldr	r1, .L1082
	sub	r0, fp, #148
	bl	memcpy
	cmp	r5, #0
	subeq	r3, fp, #20
	movne	r0, r4
	addeq	r4, r3, r4, lsl #2
	ldreq	r0, [r4, #-128]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1083:
	.align	2
.L1082:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_DecPQUANT, .-VC1_Vfmw_DecPQUANT
	.align	2
	.global	VC1_ClearCurPacket
	.type	VC1_ClearCurPacket, %function
VC1_ClearCurPacket:
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
	mov	r4, r1
	ldr	r1, [r1, #28]
	mov	r5, r0
	bl	SM_ReleaseStreamSeg
	ldrsb	r3, [r4, #8]
	cmp	r3, #1
	beq	.L1085
	mov	r0, r5
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
.L1085:
	ldr	r3, .L1089
	mov	r0, r4
	mov	r2, #36
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L1090:
	.align	2
.L1089:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_ClearCurPacket, .-VC1_ClearCurPacket
	.align	2
	.global	VC1_ClearCurPic
	.type	VC1_ClearCurPic, %function
VC1_ClearCurPic:
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
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	mov	r6, r1
	cmp	r3, #0
	beq	.L1092
	add	r7, r0, #20480
	ldr	r3, [r7, #2836]
	cmp	r3, #0
	ble	.L1106
	add	r4, r0, #23296
	mov	r5, #0
	add	r4, r4, #64
	b	.L1096
.L1095:
	ldr	r3, [r7, #2836]
	add	r4, r4, #48
	cmp	r3, r5
	movgt	r3, #1
	movle	r3, #0
	cmp	r5, #255
	movgt	r3, #0
	cmp	r3, #0
	beq	.L1107
.L1096:
	ldr	r1, [r4]
	mov	r0, r6
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #-36]
	add	r5, r5, #1
	cmp	r3, #0
	beq	.L1095
	ldr	r3, [r4, #-12]
	cmp	r3, #0
	beq	.L1095
	ldr	r1, [r4, #4]
	mov	r0, r6
	bl	SM_ReleaseStreamSeg
	b	.L1095
.L1107:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1092:
	add	r1, r0, #35584
	mov	r0, r6
	add	r1, r1, #28
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1_ClearCurPacket
.L1106:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_ClearCurPic, .-VC1_ClearCurPic
	.align	2
	.global	VC1DEC_VDMPostProc
	.type	VC1DEC_VDMPostProc, %function
VC1DEC_VDMPostProc:
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
	add	r4, r0, #45056
	mov	r6, r0
	add	r0, r0, #12672
	add	r7, r6, #32768
	add	r0, r0, #40
	mov	r8, r1
	ldr	r1, [r4, #3776]
	bl	VC1_ClearCurPic
	ldr	r1, [r7, #3252]
	ldr	r0, [r4, #3776]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r7, #3248]
	mov	r5, r0
	ldr	r0, [r4, #3776]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r7, #3244]
	mov	r10, r0
	ldr	r0, [r4, #3776]
	bl	FSP_GetFsImagePtr
	cmp	r5, #0
	beq	.L1141
	cmp	r8, #0
	movlt	r8, #0
	blt	.L1111
	cmp	r8, #100
	movge	r8, #100
.L1111:
	add	r9, r6, #12288
	str	r8, [r5, #200]
	mov	r0, r6
	bl	VC1_SetImgFormat
	ldrb	r3, [r9, #427]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L1142
.L1112:
	mov	r0, #0
	str	r0, [r5, #212]
	str	r0, [r5, #216]
	ldr	r3, [r6]
	ldr	r3, [r3, #12]
	cmp	r3, #1
	beq	.L1113
	ldrb	r0, [r9, #426]	@ zero_extendqisi2
	sub	r0, r0, #2
	ands	ip, r0, #253
	beq	.L1114
	ldr	r0, [r7, #3240]
	cmp	r0, #1
	ldrhi	lr, [r7, #3244]
	mvnls	lr, #0
	cmp	r0, #1
	movls	r5, #0
	movhi	r5, #1
	str	lr, [r7, #3256]
.L1116:
	ldr	r3, [r4, #3264]
	cmn	lr, #1
	add	r3, r3, #1
	str	r3, [r4, #3264]
	beq	.L1117
	mov	r1, lr
	ldr	r0, [r4, #3776]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L1143
	ldr	r2, [r8, #200]
	cmp	r2, #0
	beq	.L1119
	ldr	r3, [r6]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	bhi	.L1120
.L1119:
	ldr	r2, [r7, #3256]
	ldr	r3, .L1146
	ldr	r0, [r4, #3776]
	mov	r1, r2
	str	r2, [fp, #-48]
	ldr	r10, [r3, #68]
	bl	FSP_GetRef
	ldr	r2, [fp, #-48]
	ldr	r1, .L1146+4
	mov	r3, r0
	mov	r0, #12
	blx	r10
	mov	r2, #1
	ldr	r1, [r7, #3256]
	ldr	r0, [r4, #3776]
	bl	FSP_SetDisplay
	cmp	r5, #1
	ldreq	r3, [r7, #3168]
	movne	r1, #1
	ldrne	r2, [r7, #3160]
	movne	r3, #2
	strneb	r1, [r2, #1]
	mov	r2, r6
	streqb	r5, [r3, #1]
	mov	r1, #1
	strneb	r3, [r9, #425]
	add	r3, r6, #48384
	streqb	r5, [r9, #425]
	add	r3, r3, #96
	ldr	r0, [r4, #3776]
	str	r8, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L1123
	ldr	r1, [r8, #212]
	mov	r6, #0
	ldr	r0, [r4, #3776]
	bl	FreeUsdByDec
	str	r6, [r8, #212]
	ldr	r1, [r8, #216]
	ldr	r0, [r4, #3776]
	bl	FreeUsdByDec
	str	r6, [r8, #216]
	mov	r2, r6
	ldr	r0, [r4, #3776]
	ldr	r1, [r7, #3256]
	bl	FSP_SetDisplay
	cmp	r5, #1
	mov	r0, r6
	ldreq	r3, [r7, #3168]
	ldrne	r3, [r7, #3160]
	strb	r6, [r3, #1]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1114:
	ldr	lr, [r7, #3252]
	cmp	r10, #0
	moveq	r5, r10
	str	lr, [r7, #3256]
	beq	.L1116
	ldrd	r2, [r5, #8]
	ldrd	r0, [r10, #8]
	cmp	r0, r2
	sbcs	r8, r1, r3
	movge	r5, ip
	strltd	r0, [r5, #8]
	movlt	r5, ip
	strltd	r2, [r10, #8]
	ldrlt	lr, [r7, #3256]
	b	.L1116
.L1144:
	ldr	r2, [r7, #3164]
	mov	r3, #0
	strb	r3, [r2, #1]
	strb	r3, [r9, #425]
.L1117:
	mov	r0, #1
.L1110:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1142:
	ldrb	r3, [r9, #433]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1117
	b	.L1112
.L1113:
	ldr	lr, [r7, #3252]
	mov	r5, r0
	str	lr, [r7, #3256]
	b	.L1116
.L1123:
	ldrb	r5, [r9, #425]	@ zero_extendqisi2
	sxtb	r5, r5
	cmp	r5, #3
	beq	.L1144
	cmp	r5, #1
	beq	.L1145
	cmp	r5, #2
	bne	.L1117
	ldr	r2, [r7, #3160]
	mov	r3, #0
	strb	r3, [r2, #1]
	strb	r3, [r9, #425]
	b	.L1110
.L1120:
	ldr	ip, .L1146
	mov	r0, #1
	ldr	r1, .L1146+8
	mov	r6, #0
	ldr	r9, [ip, #68]
	blx	r9
	ldr	r1, [r8, #212]
	ldr	r0, [r4, #3776]
	bl	FreeUsdByDec
	str	r6, [r8, #212]
	ldr	r1, [r8, #216]
	ldr	r0, [r4, #3776]
	bl	FreeUsdByDec
	str	r6, [r8, #216]
	mov	r2, r6
	ldr	r0, [r4, #3776]
	ldr	r1, [r7, #3256]
	bl	FSP_SetDisplay
	cmp	r5, #1
	ldreq	r3, [r7, #3168]
	moveq	r0, r5
	ldrne	r3, [r7, #3160]
	movne	r0, #1
	strb	r6, [r3, #1]
	b	.L1110
.L1145:
	ldr	r2, [r7, #3168]
	mov	r3, #0
	mov	r0, r5
	strb	r3, [r2, #1]
	strb	r3, [r9, #425]
	b	.L1110
.L1141:
	ldr	ip, .L1146
	mov	r3, r10
	str	r0, [sp]
	mov	r2, r5
	ldr	r1, .L1146+12
	mov	r0, r5
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	b	.L1110
.L1143:
	ldr	r3, .L1146
	mov	r2, #680
	ldr	r1, .L1146+16
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r8
	b	.L1110
.L1147:
	.align	2
.L1146:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC52
	.word	.LC53
	.word	.LC50
	.word	.LC51
	UNWIND(.fnend)
	.size	VC1DEC_VDMPostProc, .-VC1DEC_VDMPostProc
	.align	2
	.global	VC1_Vfmw_DecodeArbiter
	.type	VC1_Vfmw_DecodeArbiter, %function
VC1_Vfmw_DecodeArbiter:
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
	add	r5, r0, #12288
	mov	r4, r0
	ldrb	r3, [r5, #424]	@ zero_extendqisi2
	tst	r3, #16
	beq	.L1199
	add	r6, r0, #45056
	bic	r3, r3, #20
	strb	r3, [r5, #424]
	ldr	r3, [r6, #3380]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r3, [r0]
	bls	.L1151
	add	r7, r0, #32768
	ldr	r2, [r3, #8]
	ldr	r1, [r7, #3240]
.L1152:
	sub	r3, r2, #1
	str	r2, [r6, #3380]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L1178
.L1160:
	.word	.L1159
	.word	.L1161
	.word	.L1177
	.word	.L1163
.L1184:
	mov	r1, #0
.L1163:
	ldrb	r3, [r5, #426]	@ zero_extendqisi2
	cmp	r3, #0
	streq	r3, [r6, #3312]
	moveq	r3, #1
	beq	.L1162
	cmp	r3, #2
	bne	.L1165
	ldr	r3, [r6, #3312]
	adds	r3, r3, #0
	movne	r3, #1
	cmp	r1, #0
	bne	.L1167
.L1166:
	ldr	r3, .L1203
	mov	r0, #1
	ldr	r1, .L1203+4
	ldr	r3, [r3, #68]
	blx	r3
.L1175:
	add	r0, r4, #12672
	ldr	r1, [r6, #3776]
	add	r0, r0, #40
	bl	VC1_ClearCurPic
	ldr	r3, .L1203+8
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1199
	mov	r3, #0
	ldr	r0, [r6, #3776]
	mov	r2, r3
	mov	r1, #113
	blx	r4
.L1199:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1151:
	ldr	r2, [r3, #8]
	cmp	r2, #4
	cmpne	r2, #1
	bls	.L1153
	add	r7, r0, #32768
	ldr	r1, [r7, #3240]
	b	.L1152
.L1177:
	mov	r3, #0
.L1162:
	cmp	r1, #0
	beq	.L1168
.L1167:
	cmp	r1, #1
	bls	.L1200
.L1171:
	cmp	r3, #0
	beq	.L1175
	add	r3, r4, #15808
	ldrsb	r3, [r3]
	cmp	r3, #0
	beq	.L1201
	add	r1, r5, #3600
	add	r0, r4, #23040
	add	r1, r1, #4
	mov	r2, #172
	add	r0, r0, #44
	bl	memcpy
	add	lr, r4, #16064
	add	ip, r4, #23040
	ldmia	lr!, {r0, r1, r2, r3}
	add	ip, ip, #216
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	add	r0, r4, #23296
	add	r0, r0, #120
	mov	r2, #176
	add	r1, r5, #3936
	bl	memcpy
	ldr	r3, [r5, #3980]
	strb	r3, [r5, #428]
	ldr	r3, [r7, #3260]
	cmp	r3, #256
	ble	.L1202
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1182:
	mov	r1, #0
.L1161:
	ldrb	r3, [r5, #426]	@ zero_extendqisi2
	cmp	r1, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	bne	.L1167
.L1168:
	ldrb	r2, [r5, #426]	@ zero_extendqisi2
	sub	r0, r2, #4
	sub	r1, r2, #1
	cmp	r1, #1
	cmphi	r0, #1
	bls	.L1166
.L1169:
	sub	r2, r2, #2
	tst	r2, #253
	bne	.L1171
	ldr	r3, .L1203
	mov	r0, #1
	ldr	r1, .L1203+12
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1175
.L1181:
	mov	r1, #0
.L1159:
	ldrb	r3, [r5, #426]	@ zero_extendqisi2
	sub	r3, r3, #2
	tst	r3, #253
	movne	r3, #1
	moveq	r3, #0
	b	.L1162
.L1201:
	add	r3, r5, #3584
	add	ip, r4, #23040
	add	r3, r3, #4
	add	ip, ip, #28
	ldmia	r3, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	add	r1, r5, #3824
	add	r0, r4, #23296
	add	r1, r1, #12
	mov	r2, #100
	add	r0, r0, #20
	bl	memcpy
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1180:
	mov	r1, #0
.L1178:
	mov	r3, #1
	b	.L1162
.L1202:
	ldr	ip, .L1203
	mov	r2, r3, asl #4
	add	r1, r4, #16384
	add	r0, r4, #23552
	sub	r2, r2, r3, asl #2
	add	r1, r1, #16
	ldr	r3, [ip, #52]
	add	r0, r0, #40
	blx	r3
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1165:
	and	r3, r3, #251
	cmp	r3, #1
	bne	.L1178
	str	r3, [r6, #3312]
	b	.L1162
.L1153:
	ldr	r3, .L1203
	add	r7, r0, #32768
	ldr	r1, .L1203+16
	mov	r0, #2
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r7, #3248]
	ldr	r0, [r6, #3776]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L1154
	ldr	r1, [r8, #212]
	mov	r9, #0
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r8, #216]
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r8, #220]
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	ldr	r1, [r8, #224]
	ldr	r0, [r6, #3776]
	bl	FreeUsdByDec
	str	r9, [r8, #212]
	str	r9, [r8, #216]
	mov	r2, #1
	str	r9, [r8, #220]
	str	r9, [r8, #224]
	ldr	r1, [r7, #3248]
	ldr	r0, [r6, #3776]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r7, #3244]
	ldr	r0, [r6, #3776]
	bl	FSP_ClearLogicFs
	str	r9, [r7, #3244]
	str	r9, [r7, #3248]
	ldr	r0, [r6, #3776]
	bl	FSP_GetNullLogicFs
	str	r0, [r7, #3248]
	str	r0, [r7, #3244]
.L1154:
	ldr	r2, [r7, #3164]
	mov	r3, #0
	str	r3, [r7, #3240]
	cmp	r2, r3
	beq	.L1198
	ldr	r1, [r7, #3168]
	cmp	r1, #0
	beq	.L1198
	strb	r3, [r2, #1]
	ldr	r2, [r7, #3168]
	strb	r3, [r2, #1]
	ldr	r2, [r7, #3164]
	strb	r3, [r2]
	ldr	r2, [r7, #3168]
	strb	r3, [r2]
	ldr	r3, [r4]
	ldr	r1, [r7, #3240]
	ldr	r2, [r3, #8]
	b	.L1152
.L1198:
	ldr	r3, [r4]
	ldr	r2, [r3, #8]
	sub	r3, r2, #1
	str	r2, [r6, #3380]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L1180
.L1176:
	.word	.L1181
	.word	.L1182
	.word	.L1183
	.word	.L1184
.L1183:
	mov	r3, #0
	b	.L1168
.L1200:
	ldrb	r2, [r5, #426]	@ zero_extendqisi2
	b	.L1169
.L1204:
	.align	2
.L1203:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC55
	.word	g_event_report
	.word	.LC56
	.word	.LC54
	UNWIND(.fnend)
	.size	VC1_Vfmw_DecodeArbiter, .-VC1_Vfmw_DecodeArbiter
	.align	2
	.global	VC1_Vfmw_StartDecode
	.type	VC1_Vfmw_StartDecode, %function
VC1_Vfmw_StartDecode:
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
	ldr	r2, [r0]
	add	r5, r0, #12288
	add	r3, r0, #15808
	add	r6, r0, #12672
	mov	r4, r0
	add	r8, r0, #8
	ldr	r2, [r2, #676]
	add	r6, r6, #40
	str	r2, [r5, #252]
	ldrsb	r3, [r3]
	cmp	r3, #0
	beq	.L1220
.L1206:
	add	r7, r4, #32768
	mov	r1, r8
	mov	r0, r4
	bl	VC1_WritePicMsg
	ldr	r3, [r7, #3260]
	ldr	ip, .L1225
	add	r1, r6, #23296
	add	r1, r1, #24
	add	r0, r4, #92
	mov	r2, r3, asl #6
	strb	r3, [r4, #78]
	sub	r2, r2, r3, asl #4
	ldr	r3, [ip, #52]
	blx	r3
	mov	r1, r8
	mov	r0, r6
	bl	VC1_CfgVDH
	ldrb	r3, [r5, #426]	@ zero_extendqisi2
	cmp	r3, #1
	ldrlsb	r2, [r5, #428]	@ zero_extendqisi2
	strlsb	r2, [r5, #429]
	cmp	r3, #5
	beq	.L1221
	mov	r3, #0
	strb	r3, [r4, #9]
	ldrb	r3, [r5, #428]	@ zero_extendqisi2
	ldrb	r2, [r5, #432]	@ zero_extendqisi2
.L1209:
	strb	r3, [r4, #8]
	strb	r3, [r5, #427]
	strb	r2, [r5, #433]
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1222
	and	r2, r3, #251
	cmp	r2, #1
	addeq	r1, r4, #45056
	streq	r2, [r1, #3312]
.L1211:
	ldr	r2, [r4]
	str	r8, [r4, #4]
	ldr	r0, [r2, #900]
	cmp	r0, #1
	beq	.L1223
	cmp	r0, #2
	beq	.L1224
.L1216:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1224:
	ldr	r2, [r2, #904]
	cmp	r8, #0
	cmpne	r2, #0
	ble	.L1216
	sub	r3, r3, #2
	ands	r5, r3, #253
	bne	.L1216
	ldr	r3, [r7, #3160]
	add	r1, r4, #45056
	mov	r0, r6
	strb	r5, [r3, #1]
	ldr	r2, [r4]
	ldr	r3, [r2, #904]
	sub	r3, r3, #1
	str	r3, [r2, #904]
	ldr	r1, [r1, #3776]
	bl	VC1_ClearCurPic
	str	r5, [r4, #4]
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1222:
	add	r9, r4, #45056
	ldr	r5, [r9, #3312]
	cmp	r5, #0
	bne	.L1211
	mov	r0, r6
	ldr	r1, [r9, #3776]
	bl	VC1_ClearCurPic
	ldr	r3, [r7, #3160]
	mov	r0, r5
	strb	r5, [r3]
	ldr	r3, [r9, #3316]
	add	r3, r3, #1
	str	r3, [r9, #3316]
	str	r5, [r4, #4]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1221:
	mov	r2, #1
	strb	r2, [r4, #9]
	ldrb	r3, [r5, #429]	@ zero_extendqisi2
	add	r1, r4, #45056
	strb	r2, [r5, #432]
	strb	r3, [r5, #428]
	ldr	r1, [r1, #3336]
	sub	r1, r1, #1
	str	r1, [r5, #172]
	b	.L1209
.L1223:
	cmp	r8, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	sub	r3, r3, #2
	ands	r5, r3, #253
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r2, [r7, #3160]
	add	r3, r4, #45056
	mov	r0, r6
	strb	r5, [r2, #1]
	ldr	r1, [r3, #3776]
	bl	VC1_ClearCurPic
	str	r5, [r4, #4]
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1220:
	mov	r0, r6
	bl	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
	b	.L1206
.L1226:
	.align	2
.L1225:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_StartDecode, .-VC1_Vfmw_StartDecode
	.align	2
	.global	VC1_Vfmw_ParseAdvHdr
	.type	VC1_Vfmw_ParseAdvHdr, %function
VC1_Vfmw_ParseAdvHdr:
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
	ldr	r6, [r0, #3128]
	add	r10, r0, #32768
	mov	r4, r0
	str	r1, [fp, #-52]
	mov	r5, #0
	mov	r1, #32
	strb	r5, [r0, #6]
	mov	r0, r6
	str	r2, [fp, #-48]
	bl	BsGet
	ldr	r1, [r6, #24]
	ldr	r7, [r10, #2844]
	add	r8, r4, #35584
	cmp	r1, r5
	add	ip, r1, #7
	ldr	r2, [r10, #2864]
	add	r8, r8, #28
	movlt	r1, ip
	mov	r1, r1, asr #3
	add	r7, r7, r1
	rsb	r2, r1, r2
	mov	r1, r7
	uxtb	r9, r0
	mov	r0, r6
	bl	BsInit
	sub	r2, r9, #10
	cmp	r2, #5
	bhi	.L1228
	cmp	r9, #11
	beq	.L1290
	ldrb	r1, [r4]	@ zero_extendqisi2
	and	r0, r1, #7
	cmp	r0, #7
	beq	.L1291
	add	r9, r4, #20480
	strb	r5, [r4, #8]
	str	r5, [r9, #2836]
	cmp	r2, #5
	ldrls	pc, [pc, r2, asl #2]
	b	.L1260
.L1243:
	.word	.L1242
	.word	.L1260
	.word	.L1244
	.word	.L1261
	.word	.L1246
	.word	.L1247
.L1228:
	sub	r3, r9, #27
	cmp	r3, #4
	bls	.L1292
	cmp	r9, #254
	beq	.L1293
.L1260:
	ldr	r0, [fp, #-48]
	mov	r1, r8
	bl	VC1_ClearCurPacket
	mov	r0, #0
.L1233:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1292:
	ldr	r0, [fp, #-48]
	mov	r1, r8
	bl	VC1_ClearCurPacket
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1290:
	ldrb	r2, [r4]	@ zero_extendqisi2
	and	r2, r2, #7
	cmp	r2, #7
	beq	.L1294
.L1258:
	ldr	r0, [fp, #-48]
	mov	r1, r8
	bl	VC1_ClearCurPacket
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1261:
	ldr	r3, .L1299
	str	r3, [fp, #-56]
.L1289:
	ldr	r0, [fp, #-52]
	mov	r2, #176
	ldr	r3, [fp, #-56]
	mov	r1, #0
	add	r0, r0, #348
	ldrb	r5, [r0, #31]	@ zero_extendqisi2
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r0, [fp, #-52]
	strb	r5, [r0, #379]
.L1248:
	ldr	r3, [fp, #-56]
	add	r0, r4, #23296
	mov	r2, #12288
	mov	r1, #0
	add	r0, r0, #24
	ldr	r5, [r3, #48]
	blx	r5
	mov	r0, r6
	bl	BsPos
	ldr	r3, [fp, #-52]
	mov	r1, r4
	mov	r2, r3
	str	r0, [r3, #488]
	mov	r0, r6
	bl	VC1_Vfmw_ParseAdvPicHdr
	cmp	r0, #1
	mov	r5, r0
	beq	.L1295
	mov	r1, r8
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	ldr	r3, .L1299
	movw	r2, #6075
	ldr	r1, .L1299+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	b	.L1233
.L1293:
	mov	r1, #32
	mov	r0, r6
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r6
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r5, r3
	bne	.L1260
	ldrb	r3, [r4]	@ zero_extendqisi2
	mov	r2, #1
	mov	r0, r2
	strb	r2, [r4, #7]
	orr	r3, r3, #16
	strb	r2, [r4, #6]
	strb	r3, [r4]
	b	.L1233
.L1291:
	mov	r5, #1
	orr	r1, r1, #16
	strb	r5, [r4, #6]
	mov	r0, r5
	strb	r1, [r4]
	b	.L1233
.L1244:
	ldr	r3, .L1299
	mov	r1, #1
	ldr	r0, [fp, #-52]
	mov	r2, #16
	strb	r1, [r4, #8]
	mov	r1, #0
	add	r0, r0, #508
	ldr	r5, [r3, #48]
	str	r3, [fp, #-56]
	blx	r5
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1248
	b	.L1289
.L1247:
	ldr	r2, [fp, #-52]
	mov	r0, r6
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvSeqHdr
	cmp	r0, #1
	mov	r5, r0
	ldreqb	r3, [r4]	@ zero_extendqisi2
	orreq	r3, r3, #1
	streqb	r3, [r4]
	b	.L1258
.L1246:
	mov	r0, r6
	ldr	r2, [fp, #-52]
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvEntptHdr
	cmp	r0, #1
	mov	r5, r0
	bne	.L1258
	ldr	r1, [fp, #-52]
	mov	r0, r4
	bl	VC1_Vfmw_UpdateAdvSPS
	ldrb	r3, [r4]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r4]
	b	.L1258
.L1242:
	orr	r3, r1, #32
	ldr	r0, [fp, #-48]
	mov	r1, r8
	strb	r3, [r4]
	bl	VC1_ClearCurPacket
	mov	r0, #1
	b	.L1233
.L1294:
	mov	r0, r6
	ldr	r2, [fp, #-52]
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvSlcHdr
	cmp	r0, #1
	mov	r6, r0
	bne	.L1231
	add	r9, r4, #20480
	ldr	r8, [r9, #2836]
	cmp	r8, #255
	bgt	.L1296
	mov	r3, r8, asl #4
	mov	r2, r8, asl #6
	ldr	r0, [r4, #3128]
	rsb	r6, r3, r2
	add	r6, r4, r6
	str	r2, [fp, #-56]
	movw	r2, #23328
	movw	ip, #23320
	strb	r8, [r6, r2]
	movw	lr, #23336
	ldr	r2, [r0, #24]
	str	r3, [fp, #-48]
	cmp	r2, #0
	add	r1, r2, #7
	movlt	r2, r1
	add	r1, r6, #23296
	add	r2, r7, r2, asr #3
	str	r2, [r6, ip]
	ldr	r2, [r0, #24]
	mov	r7, r1
	add	r3, r1, #24
	str	r3, [fp, #-60]
	and	r2, r2, #7
	str	r2, [r6, lr]
	ldr	r2, [r0, #16]
	ldr	r0, [r0, #24]
	str	r3, [fp, #-64]
	rsb	r2, r0, r2, lsl #3
	str	r2, [r1, #44]
	ldr	r0, [r6, ip]
	bl	MEM_Vir2Phy
	movw	r1, #23360
	add	r2, r7, #64
	str	r0, [r7, #36]
	ldr	r0, [r10, #2872]
	str	r0, [r6, r1]
	ldr	r1, [r10, #2848]
	cmp	r1, #0
	beq	.L1234
	ldr	r0, [r10, #2860]
	ldr	r3, [fp, #-60]
	cmp	r0, #0
	beq	.L1234
	movw	ip, #23352
	str	r1, [r3, #4]
	str	r5, [r6, ip]
	add	r1, r6, #23296
	ldr	ip, [r10, #2868]
	str	r0, [r1, #52]
	mov	ip, ip, asl #3
	str	ip, [r1, #60]
	ldr	r3, [r10, #2876]
	str	r3, [r2, #4]
.L1235:
	ldr	ip, [r9, #2756]
	ldr	r1, [r9, #2752]
	ldrb	r5, [r4, #8]	@ zero_extendqisi2
	mul	r1, r1, ip
	cmp	r5, #0
	sub	r1, r1, #1
	beq	.L1236
	ldr	r2, [fp, #-48]
	add	r3, ip, #1
	ldr	lr, [fp, #-52]
	movw	r5, #23344
	sub	r0, r2, r8, asl #2
	add	r3, r3, r3, lsr #31
	add	r0, lr, r0
	ldr	lr, [fp, #-56]
	add	r0, r0, #520
	rsb	lr, r2, lr
	ldr	r2, [r0, #8]
	add	lr, r4, lr
	sub	r3, r2, r3, asr #1
	cmp	r1, r3
	str	r3, [lr, r5]
	movcs	r1, #0
	movcc	r1, #1
	cmp	r3, #0
	movle	r1, #0
	cmp	r1, #0
	bne	.L1297
.L1237:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-48]
	rsb	r3, r2, r3
	add	r4, r4, r3
	add	r3, r4, #23296
	add	r3, r3, #40
	ldr	r3, [r3, #4]
	cmp	r3, #0
	ble	.L1238
	add	r3, r4, #23296
	add	r3, r3, #24
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1256
	add	r4, r4, #23296
	ldr	r3, [r4, #60]
	cmp	r3, #0
	ble	.L1238
.L1256:
	ldr	r3, [r9, #2836]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r9, #2836]
	b	.L1233
.L1295:
	mov	r0, r6
	bl	BsPos
	ldr	r3, [fp, #-52]
	ldr	r2, [r3, #488]
	rsb	r0, r2, r0
	str	r0, [r3, #488]
	ldrb	r2, [r4]	@ zero_extendqisi2
	mov	r0, r6
	orr	r2, r2, #4
	strb	r2, [r4]
	bl	BsPos
	ldr	r2, [r10, #2864]
	add	r0, r0, #32
	cmp	r0, r2, asl #3
	bge	.L1250
	ldr	r6, [r9, #2836]
	movw	r2, #23328
	ldr	r1, [r4, #3128]
	movw	lr, #23336
	mov	r3, r6, asl #6
	mov	r8, r6, asl #4
	rsb	r5, r8, r3
	str	r3, [fp, #-48]
	add	r5, r4, r5
	add	ip, r5, #23296
	strb	r6, [r5, r2]
	add	r3, ip, #32
	ldr	r2, [r1, #24]
	str	r3, [fp, #-60]
	cmp	r2, #0
	add	r0, r2, #7
	str	r3, [fp, #-64]
	movw	r3, #23320
	movlt	r2, r0
	add	r7, r7, r2, asr #3
	str	r7, [r5, r3]
	ldr	r2, [r1, #24]
	add	r7, ip, #24
	and	r2, r2, #7
	str	r2, [r5, lr]
	ldr	r2, [r1, #16]
	ldr	r1, [r1, #24]
	rsb	r2, r1, r2, lsl #3
	str	r2, [ip, #44]
	ldr	r0, [r5, r3]
	bl	MEM_Vir2Phy
	ldr	r3, [fp, #-60]
	movw	r1, #23360
	add	r2, r5, #23296
	add	r2, r2, #64
	str	r0, [r3, #4]
	ldr	r0, [r10, #2872]
	str	r0, [r5, r1]
	ldr	r1, [r10, #2848]
	cmp	r1, #0
	beq	.L1251
	ldr	r0, [r10, #2860]
	cmp	r0, #0
	beq	.L1251
	movw	ip, #23352
	str	r1, [r7, #4]
	mov	r1, #0
	str	r1, [r5, ip]
	ldr	ip, [r10, #2868]
	add	r1, r5, #23296
	str	r0, [r1, #52]
	mov	ip, ip, asl #3
	str	ip, [r1, #60]
	ldr	r3, [r10, #2876]
	str	r3, [r2, #4]
.L1252:
	ldr	r0, [r9, #2756]
	sub	r2, r8, r6, asl #2
	ldr	r1, [r9, #2752]
	ldrb	r5, [r4, #8]	@ zero_extendqisi2
	mul	r1, r1, r0
	cmp	r5, #0
	sub	r1, r1, #1
	beq	.L1253
	ldr	ip, [fp, #-52]
	add	r3, r0, #1
	movw	r5, #23344
	add	r2, ip, r2
	add	lr, r3, r3, lsr #31
	ldr	ip, [fp, #-48]
	add	r2, r2, #520
	ldr	r3, [r2, #8]
	rsb	ip, r8, ip
	sub	r3, r3, lr, asr #1
	add	ip, r4, ip
	cmp	r1, r3
	str	r3, [ip, r5]
	movcs	r1, #0
	movcc	r1, #1
	cmp	r3, #0
	movle	r1, #0
	cmp	r1, #0
	bne	.L1298
.L1254:
	ldr	r3, [fp, #-48]
	rsb	r8, r8, r3
	add	r4, r4, r8
	add	r3, r4, #23296
	add	r3, r3, #40
	ldr	r3, [r3, #4]
	cmp	r3, #0
	ble	.L1255
	add	r3, r4, #23296
	add	r3, r3, #24
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1256
	add	r4, r4, #23296
	ldr	r3, [r4, #60]
	cmp	r3, #0
	bgt	.L1256
.L1255:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r1, .L1299+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	b	.L1233
.L1231:
	mov	r1, r8
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	ldr	r3, .L1299
	movw	r2, #5986
	ldr	r1, .L1299+12
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r6
	b	.L1233
.L1250:
	mov	r1, r8
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	ldr	r3, .L1299
	movw	r2, #6069
	ldr	r1, .L1299+4
	mov	r0, r5
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	b	.L1233
.L1251:
	ldr	r3, [fp, #-48]
	movw	lr, #23352
	mov	r2, #0
	rsb	r3, r8, r3
	add	r3, r4, r3
	add	ip, r3, #23296
	str	r2, [ip, #28]
	str	r2, [r3, lr]
	str	r2, [ip, #60]
	str	r2, [ip, #52]
	str	r2, [ip, #68]
	b	.L1252
.L1296:
	ldr	r1, [fp, #-48]
	mov	r0, r4
	bl	VC1_ClearCurPic
	ldr	r3, .L1299
	ldr	r2, [r9, #2836]
	mov	r0, r6
	ldr	r1, .L1299+16
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	b	.L1233
.L1234:
	ldr	r2, [fp, #-48]
	movw	lr, #23352
	ldr	r3, [fp, #-56]
	rsb	r3, r2, r3
	mov	r2, #0
	add	r3, r4, r3
	add	ip, r3, #23296
	str	r2, [ip, #28]
	str	r2, [r3, lr]
	str	r2, [ip, #60]
	str	r2, [ip, #52]
	str	r2, [ip, #68]
	b	.L1235
.L1253:
	ldr	r3, [fp, #-48]
	movw	ip, #23344
	rsb	r0, r8, r3
	ldr	r3, [fp, #-52]
	add	r0, r4, r0
	add	r2, r3, r2
	add	r2, r2, #520
	ldr	r3, [r2, #8]
	cmp	r1, r3
	str	r3, [r0, ip]
	bcs	.L1254
	ldr	r2, [r2, #8]
	mov	r0, #1
	str	r1, [sp]
	ldr	r1, [fp, #-56]
	ldr	r4, [r1, #68]
	ldr	r1, .L1299+20
	blx	r4
	mov	r0, r5
	b	.L1233
.L1236:
	ldr	r3, [fp, #-48]
	movw	ip, #23344
	ldr	r0, [fp, #-56]
	sub	r2, r3, r8, asl #2
	rsb	r0, r3, r0
	ldr	r3, [fp, #-52]
	add	r0, r4, r0
	add	r2, r3, r2
	add	r2, r2, #520
	ldr	r3, [r2, #8]
	cmp	r1, r3
	str	r3, [r0, ip]
	bcs	.L1237
	ldr	ip, .L1299
	mov	r0, #1
	ldr	r2, [r2, #8]
	str	r1, [sp]
	ldr	r1, .L1299+20
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	b	.L1233
.L1238:
	ldr	r3, .L1299
	mov	r0, #1
	ldr	r1, .L1299+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	b	.L1233
.L1298:
	ldr	r1, [fp, #-56]
	ldr	r2, [r2, #8]
	str	r0, [sp]
	mov	r0, #1
	ldr	r4, [r1, #68]
	ldr	r1, .L1299+24
	blx	r4
	mov	r0, #0
	b	.L1233
.L1297:
	ldr	lr, .L1299
	ldr	r2, [r0, #8]
	mov	r0, #1
	str	ip, [sp]
	ldr	r1, .L1299+24
	ldr	r4, [lr, #68]
	blx	r4
	mov	r0, #0
	b	.L1233
.L1300:
	.align	2
.L1299:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	.word	.LC49
	.word	.LC58
	.word	.LC57
	.word	.LC48
	.word	.LC47
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvHdr, .-VC1_Vfmw_ParseAdvHdr
	.align	2
	.global	VC1_Vfmw_ParseHeader
	.type	VC1_Vfmw_ParseHeader, %function
VC1_Vfmw_ParseHeader:
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
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #0
	bne	.L1302
	ldrb	r3, [r0]	@ zero_extendqisi2
	mov	r2, r1
	mov	r1, r0
	ldr	r0, [r0, #3128]
	orr	r3, r3, #3
	strb	r3, [r4]
	bl	VC1_Vfmw_ParseSMPPicHdr
	cmp	r0, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r3, [r4]	@ zero_extendqisi2
	orr	r3, r3, #20
	strb	r3, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1302:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvHdr
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseHeader, .-VC1_Vfmw_ParseHeader
	.align	2
	.global	VC1_SetCodeInfo
	.type	VC1_SetCodeInfo, %function
VC1_SetCodeInfo:
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
	add	r4, r0, #12288
	mov	r5, r0
	add	r0, r0, #15808
	ldrb	r3, [r4, #3522]	@ zero_extendqisi2
	add	r0, r0, #36
	str	r0, [r4, #3552]
	cmp	r3, #8
	strneb	r3, [r4, #435]
	moveq	r3, #6
	movne	r3, #0
	streqb	r3, [r4, #435]
	moveq	r2, #1
	strneb	r3, [r4, #436]
	add	r3, r5, #15808
	streqb	r2, [r4, #436]
	ldrsb	r3, [r3]
	ldr	r2, [r1, #20]
	cmp	r3, #0
	ldr	r1, [r1]
	beq	.L1310
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	BsInit
.L1310:
	bl	BsInit
	ldr	lr, [r4, #3544]
	add	r5, r5, #32768
	add	r1, r4, #3520
	adds	r3, lr, #15
	add	r0, r4, #3584
	addmi	r3, lr, #30
	add	r1, r1, #3
	mov	r2, #16
	add	r0, r0, #4
	mov	r3, r3, asr #4
	str	r3, [r5, #3176]
	ldr	ip, [r4, #3548]
	str	lr, [r5, #3192]
	adds	r3, ip, #15
	addmi	r3, ip, #30
	str	ip, [r5, #3196]
	mov	r3, r3, asr #4
	str	r3, [r5, #3180]
	bl	memcpy
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_SetCodeInfo, .-VC1_SetCodeInfo
	.align	2
	.global	VC1_ReceivePacket
	.type	VC1_ReceivePacket, %function
VC1_ReceivePacket:
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
	add	r1, r0, #48128
	add	r1, r1, #196
	beq	.L1319
	ldr	r2, [r4, #8]
	add	r3, r0, #45056
	str	r2, [r3, #3280]
	ldr	r2, [r4]
	str	r2, [r3, #3268]
	ldr	r2, [r4, #12]
	str	r2, [r3, #3288]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #3276]
	ldr	r2, [r4, #16]
	str	r2, [r3, #3296]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1314
	ldr	r2, [r4, #88]
	str	r2, [r3, #3284]
	ldr	r2, [r4, #80]
	str	r2, [r3, #3272]
	ldr	r2, [r4, #92]
	str	r2, [r3, #3292]
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	strb	r2, [r3, #3277]
	ldr	r2, [r4, #96]
	str	r2, [r3, #3300]
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1320
.L1315:
	bl	VC1_SetCodeInfo
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1320:
	ldr	r0, [r3, #3776]
	bl	VC1_ClearCurPacket
	ldr	r3, .L1321
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	mov	r0, #1
	ldr	r1, .L1321+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1314:
	mov	r2, #0
	str	r2, [r3, #3284]
	str	r2, [r3, #3272]
	str	r2, [r3, #3292]
	strb	r2, [r3, #3277]
	str	r2, [r3, #3300]
	b	.L1315
.L1319:
	ldr	r3, .L1321
	mov	r0, r4
	ldr	r1, .L1321+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1322:
	.align	2
.L1321:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC61
	.word	.LC60
	UNWIND(.fnend)
	.size	VC1_ReceivePacket, .-VC1_ReceivePacket
	.align	2
	.global	VC1DEC_Decode
	.type	VC1DEC_Decode, %function
VC1DEC_Decode:
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
	ldr	r6, .L1352
	add	r5, r0, #12544
	add	r5, r5, #8
	mov	r4, r0
	mov	r2, #160
	ldr	r3, [r6, #52]
	mov	r0, r5
	blx	r3
	mov	r1, r5
	mov	r0, r4
	bl	VC1_ReceivePacket
	subs	r7, r0, #0
	beq	.L1347
	ldr	r3, [r4]
	ldr	r2, [r3, #868]
	cmp	r2, #1
	beq	.L1348
.L1326:
	add	r3, r4, #12288
	add	r6, r4, #45056
	ldrb	r3, [r3, #424]	@ zero_extendqisi2
	strb	r3, [r6, #3384]
.L1327:
	add	r5, r4, #12672
	add	r1, r4, #15872
	add	r5, r5, #40
	add	r1, r1, #4
	ldr	r2, [r6, #3776]
	mov	r0, r5
	bl	VC1_Vfmw_ParseHeader
	subs	r8, r0, #0
	beq	.L1349
	mov	r0, r4
	bl	VC1_Vfmw_DecodeArbiter
	cmp	r0, #0
	bne	.L1350
.L1330:
	mov	r7, #0
.L1325:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1349:
	add	r1, r4, #48128
	ldr	r0, [r6, #3776]
	add	r1, r1, #196
	bl	VC1_ClearCurPacket
	ldr	r3, .L1352+4
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1330
	ldr	r0, [r6, #3776]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	mov	r7, r8
	blx	r4
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1348:
	ldr	r3, [r3, #908]
	cmp	r3, #1
	bne	.L1326
	add	r6, r4, #45056
	add	r3, r4, #12288
	ldrb	r2, [r6, #3384]	@ zero_extendqisi2
	strb	r2, [r3, #424]
	b	.L1327
.L1347:
	add	r4, r4, #45056
	ldr	r3, [r6, #68]
	ldr	r1, .L1352+8
	ldr	r2, [r4, #3264]
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1350:
	mov	r0, r4
	bl	VC1_Vfmw_PrepareDecode
	subs	r7, r0, #0
	bne	.L1331
	ldr	r3, [r4]
	ldr	r2, [r3, #868]
	cmp	r2, #1
	beq	.L1351
.L1332:
	mov	r0, r5
	ldr	r1, [r6, #3776]
	bl	VC1_ClearCurPic
.L1333:
	ldr	r3, .L1352+4
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1330
	mov	r3, #0
	ldr	r0, [r6, #3776]
	mov	r2, r3
	mov	r1, #113
	blx	r4
	b	.L1325
.L1351:
	ldr	r3, [r3, #908]
	cmp	r3, #1
	bne	.L1332
	b	.L1333
.L1331:
	mov	r0, r4
	bl	VC1_Vfmw_StartDecode
	subs	r7, r0, #0
	movne	r7, r8
	bne	.L1325
	add	r4, r4, #32768
	mov	r2, #1
	ldr	r0, [r6, #3776]
	ldr	r1, [r4, #3252]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3160]
	ldr	r3, .L1352+4
	strb	r7, [r2]
	ldr	r2, [r4, #3160]
	strb	r7, [r2, #1]
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1330
	ldr	r0, [r6, #3776]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #113
	blx	r4
	b	.L1325
.L1353:
	.align	2
.L1352:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC62
	UNWIND(.fnend)
	.size	VC1DEC_Decode, .-VC1DEC_Decode
	.align	2
	.global	VC1_GetPacketState
	.type	VC1_GetPacketState, %function
VC1_GetPacketState:
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
	add	r0, r0, #12672
	ldrsb	r3, [r0, #46]
	cmp	r3, #1
	moveq	r0, #2
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_GetPacketState, .-VC1_GetPacketState
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13306, %object
	.size	__func__.13306, 13
__func__.13306:
	.ascii	"Vc1SMPSeqHdr\000"
	.space	3
.LC0:
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	1
	.word	2
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
.LC1:
	.word	3
	.word	1
	.word	2
	.word	0
	.word	4
.LC2:
	.word	1
	.word	0
	.word	2
	.word	3
	.word	4
.LC3:
	.word	3
	.word	1
.LC4:
	.word	3
	.word	1
	.word	2
	.word	0
.LC5:
	.word	1
	.word	0
	.word	2
	.word	3
.LC6:
	.word	1
	.word	1
	.word	2
	.word	1
	.word	3
	.word	1
	.word	2
.LC7:
	.word	2
	.word	3
	.word	3
	.word	4
	.word	4
	.word	5
	.word	5
.LC8:
	.word	3
	.word	4
	.word	1
	.word	5
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	1
	.word	3
	.word	5
	.word	7
.LC9:
	.word	5
	.word	5
	.word	6
	.word	6
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	8
	.word	8
	.word	8
	.word	8
.LC10:
	.word	256
	.word	128
	.word	85
	.word	64
	.word	51
	.word	43
	.word	37
	.word	32
	.type	__func__.13617, %object
	.size	__func__.13617, 17
__func__.13617:
	.ascii	"VC1_DecBfraction\000"
	.space	3
	.type	aCount, %object
	.size	aCount, 128
aCount:
	.word	0
	.word	1
	.word	1
	.word	2
	.word	1
	.word	2
	.word	2
	.word	3
	.word	1
	.word	2
	.word	2
	.word	3
	.word	2
	.word	3
	.word	3
	.word	4
	.word	1
	.word	2
	.word	2
	.word	3
	.word	2
	.word	3
	.word	3
	.word	4
	.word	2
	.word	3
	.word	3
	.word	4
	.word	3
	.word	4
	.word	4
	.word	5
	.type	a2On4Off, %object
	.size	a2On4Off, 60
a2On4Off:
	.word	3
	.word	5
	.word	6
	.word	9
	.word	10
	.word	12
	.word	17
	.word	18
	.word	20
	.word	24
	.word	33
	.word	34
	.word	36
	.word	40
	.word	48
.LC12:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	16
	.word	17
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	25
	.word	27
	.word	29
	.word	31
.LC11:
	.word	1
	.word	2
	.word	2
	.word	2
	.word	0
	.word	1
	.word	0
	.word	1
	.type	FldPTypeTab, %object
	.size	FldPTypeTab, 64
FldPTypeTab:
	.word	0
	.word	0
	.word	0
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	4
	.word	4
	.word	2
	.word	4
	.word	4
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC13:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC14:
	ASCII(.ascii	"VC1 INIT!!!\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC16:
	ASCII(.ascii	"%s: %s\012\000" )
.LC17:
	ASCII(.ascii	"picture height out of range\000" )
.LC18:
	ASCII(.ascii	"Vc1SMPSeqHdr Err, BS is wrong\000" )
	.space	2
.LC19:
	ASCII(.ascii	"Vc1SMPSeqHdr Err, BS is wrong\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC21:
	ASCII(.ascii	"vc1 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"VC1_Vfmw_GetImageBuffer get imgbuf err, clear all r" )
	ASCII(.ascii	"ef!\012\000" )
.LC27:
	ASCII(.ascii	"VC1_Vfmw_GetImageBuffer get_flag!=1, FSP_ClearLogic" )
	ASCII(.ascii	"Fs.\012\000" )
.LC28:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_ArrangeVahbMem err!\012\000" )
.LC29:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_GetImageBuffer err!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo B pic pCodecInf->RefNum < 2 " )
	ASCII(.ascii	"err!\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"line: %d (pCur,pFwd,pBwd)(%p,%p,%p)\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo imgbuf = NULL err!\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_BuildRefList err!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC37:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo error! Release all packets!\012" )
	ASCII(.ascii	"\000" )
.LC38:
	ASCII(.ascii	"%s:%d Code(%d) is invalid\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"%s:%d Denominator(%d) is invalid\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"Check Pos 2: %d\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"Check Pos 3: %d\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"\012======PicNum  :%6d=========\012\000" )
	.space	2
.LC43:
	ASCII(.ascii	"INTERPFRM  :%#x\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"VC1_Vfmw_ParseMPBPicHdr err!\012\000" )
	.space	2
.LC45:
	ASCII(.ascii	"VC1_Vfmw_ParseSMPIPicHdr err!\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"After VC1_Vfmw_ParseSMPPicHdr BS Len <= 0 err!\012\000" )
.LC47:
	ASCII(.ascii	"SLICE_ADDR = %d,SlcEndMbn = %d, MbHeight = %d\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"SLICE_ADDR = %d,SlcEndMbn = %d, totalMbMin1 = %d\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC49:
	ASCII(.ascii	"VC1_RecordSlcStream stream len <= 0\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"pImg is null, pCurImg %#x pBwdImg %#x pFwdImg %#x\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC51:
	ASCII(.ascii	"line: %d, pToQueImg is Null!\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC54:
	ASCII(.ascii	"----------------- VC1 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"NOTE: Drop non-I\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"NOTE: Drop B\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	" pCodecInf->SlcNum = %d >= 256 \012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"line %d, Code = VC1_SCSLC failed!\012\000" )
	.space	1
.LC59:
	ASCII(.ascii	"line %d, Code = VC1_SCFRM failed!\012\000" )
	.space	1
.LC60:
	ASCII(.ascii	"bitsream para error -----\012\000" )
	.space	1
.LC61:
	ASCII(.ascii	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\012\000" )
.LC62:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
