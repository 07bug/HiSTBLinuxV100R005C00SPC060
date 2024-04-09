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
	bne	.L27
.L19:
	ldrb	r3, [r0, #-1]!	@ zero_extendqisi2
	add	r2, r2, #8
	cmp	r3, #0
	beq	.L19
	add	r0, r2, #1
.L20:
	tst	r3, #1
	bne	.L28
.L21:
	mov	r3, r3, lsr #1
	add	r2, r2, #1
	tst	r3, #1
	beq	.L21
	add	r0, r2, #1
	ldmfd	sp, {fp, sp, pc}
.L27:
	mov	r0, #1
	mov	r2, #0
	b	.L20
.L28:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r8, r1
	mov	r6, r0
	moveq	r7, #1
	movne	r7, #0
	beq	.L33
	add	r4, r0, #49152
	ldr	r3, .L35
	movw	r2, #49680
	mov	r1, r7
	ldr	r9, [r4, #512]
	mov	r5, #1
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r4, #168
	str	r9, [r4, #512]
	bl	ResetVoQueue
	add	r2, r6, #12288
	ldr	r3, [r8, #32]
	mov	r0, r6
	str	r8, [r6]
	strb	r5, [r2, #457]
	add	r3, r3, #255
	ldr	r1, [r8, #8]
	bic	r3, r3, #255
	add	ip, r3, #2048
	str	r3, [r4, #96]
	str	ip, [r4, #100]
	add	ip, r3, #4096
	str	r1, [r4, #124]
	add	r1, r3, #6144
	str	ip, [r4, #104]
	add	ip, r3, #8192
	str	r1, [r4, #108]
	add	r1, r3, #10240
	str	ip, [r4, #112]
	add	r3, r3, #12288
	str	r1, [r4, #116]
	str	r3, [r4, #120]
	strb	r5, [r2, #458]
	str	r7, [r4, #56]
	str	r7, [r4, #60]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #520]
	beq	.L34
	ldr	r1, .L35+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L33:
	ldr	r1, .L35+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L34:
	mov	r0, r7
	ldr	r1, .L35+12
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L36:
	.align	2
.L35:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC15
	.word	.LC13
	.word	.LC14
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	cmp	r2, #0
	cmpne	r0, #0
	mov	r4, r2
	beq	.L51
	mov	r2, r1, asl #3
	mov	r1, r0
	sub	r0, fp, #52
	bl	BsInit
	mov	r1, #8
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #8
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #16
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #24
	sub	r0, fp, #52
	str	r5, [r4, #8]
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #8
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #16
	sub	r0, fp, #52
	bl	BsGet
	ldr	r3, [r4, #8]
	cmp	r3, #8192
	add	r0, r5, r0, lsl #24
	str	r0, [r4, #12]
	bgt	.L42
	cmp	r0, #8192
	bgt	.L43
	cmp	r3, #31
	ble	.L42
	cmp	r0, #31
	ble	.L43
	mov	r1, #2
	sub	r0, fp, #52
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #16]
	cmp	r0, #1
	bhi	.L45
	mov	r1, #2
	sub	r0, fp, #52
	bl	BsGet
	cmp	r0, #0
	bne	.L45
	mov	r1, #3
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #5
	strb	r0, [r4, #17]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #18]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	sub	r0, fp, #52
	bl	BsGet
	cmp	r0, #0
	bne	.L45
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #20]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #21]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #22]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #23]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #24]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #25]
	sub	r0, fp, #52
	bl	BsGet
	subs	r5, r0, #0
	bne	.L45
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #26]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #27]
	sub	r0, fp, #52
	bl	BsGet
	ldrb	r3, [r4, #16]	@ zero_extendqisi2
	mov	r1, #3
	cmp	r3, #0
	strb	r0, [r4, #28]
	sub	r0, fp, #52
	streqb	r3, [r4, #28]
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #29]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #30]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #31]
	sub	r0, fp, #52
	bl	BsGet
	sub	r0, fp, #52
	mov	r1, #32
	bl	BsGet
	cmp	r0, #0
	bne	.L52
.L39:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L52:
	ldr	r1, .L53
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L45:
	ldr	r3, .L53+4
.L50:
	ldr	r2, .L53+8
	mov	r0, #0
	ldr	r1, .L53+12
	mvn	r5, #0
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L43:
	ldr	r3, .L53+16
	b	.L50
.L51:
	ldr	r1, .L53+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L39
.L42:
	ldr	r3, .L53+24
	b	.L50
.L54:
	.align	2
.L53:
	.word	.LC21
	.word	.LC20
	.word	.LANCHOR0
	.word	.LC18
	.word	.LC19
	.word	.LC16
	.word	.LC17
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #32768
	add	r8, r0, #49152
	mov	r6, r0
	add	r7, r0, #12288
	ldr	r1, [r5, #4092]
	ldr	r0, [r8, #520]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r9, #1
	str	r9, [r4, #296]
	ldrb	r3, [r7, #451]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L64
	ldr	ip, .L65
	mov	r3, #0
	mov	r1, r3
	strb	r3, [r4, #284]
	mov	r2, #4
	add	r0, r4, #64
	ldr	r3, [ip, #48]
	blx	r3
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	orr	r3, r3, #12
	bfi	r3, r9, #4, #2
	strb	r3, [r4, #65]
.L59:
	ldrb	r2, [r8, #129]	@ zero_extendqisi2
	mov	r1, #0
	ldrb	r3, [r4, #66]	@ zero_extendqisi2
	mov	r0, r4
	bfi	r3, r2, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r8, #132]
	str	r3, [r4, #120]
	ldr	r3, [r5, #4036]
	str	r3, [r4, #72]
	ldr	r3, [r5, #4032]
	str	r3, [r4, #68]
	bl	SetAspectRatio
	ldr	r7, [r7, #244]
	ldr	r0, [r4, #36]
	add	lr, r4, #512
	ldr	r1, [r4, #112]
	add	ip, r0, r7
	str	ip, [r4, #40]
	ldrd	r2, [lr, #-8]
	add	r6, ip, r1
	add	r1, r0, r1
	adds	r2, r2, r7
	adc	r3, r3, #0
	strd	r2, [lr]
	ldr	r3, [r4, #68]
	mov	r2, #8
	str	ip, [r4, #24]
	mov	lr, #1
	str	r6, [r4, #32]
	add	r3, r3, #508
	str	r1, [r4, #28]
	add	r3, r3, #3
	str	r0, [r4, #20]
	bic	r3, r3, #508
	ldr	r1, [r5, #4036]
	bic	r3, r3, #3
	mov	r3, r3, lsr #5
	str	r1, [r4, #80]
	ldr	r1, [r5, #4032]
	str	r3, [r4, #136]
	strb	lr, [r4, #291]
	str	r1, [r4, #76]
	strb	lr, [r4, #289]
	str	r2, [r4, #300]
	str	r2, [r4, #308]
	str	r2, [r4, #304]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L64:
	mov	r3, #4
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	strb	r3, [r4, #284]
	mov	r1, #1
	ldrb	r3, [r6, #16]	@ zero_extendqisi2
	ubfx	r2, r2, #2, #2
	add	r3, r3, r9
	orr	r3, r3, r2
	cmp	r3, #3
	andls	r2, r3, #3
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	movhi	r2, #0
	bfi	r3, r2, #2, #2
	bfi	r3, r1, #0, #2
	bfi	r3, r1, #4, #2
	strb	r3, [r4, #65]
	b	.L59
.L66:
	.align	2
.L65:
	.word	vfmw_Osal_Func_Ptr_S
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L72
	add	r4, r4, #49152
	mov	r2, #0
	ldr	r0, [r4, #520]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #520]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L71
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #520]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #520]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L71:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L72:
	ldr	r1, .L73
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L74:
	.align	2
.L73:
	.word	.LC22
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r4, r0, #0
	beq	.L95
	add	r5, r4, #32768
	add	r9, r4, #12288
	ldr	r3, [r5, #4004]
	cmp	r3, #0
	beq	.L83
	ldr	r3, [r4]
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L94
	add	r6, r4, #49152
	ldr	r1, [r5, #4088]
	ldr	r0, [r6, #520]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	moveq	r5, r6
	addeq	r5, r5, #168
	beq	.L82
	ldr	r1, [r5, #4088]
	ldr	r0, [r6, #520]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L93
.L94:
	add	r5, r4, #49152
	add	r5, r5, #168
.L82:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	GetVoLastImageID
.L93:
	add	r10, r8, #544
	add	r7, r8, #560
	mov	r0, r4
	bl	VC1_SetImgFormat
	mov	r2, #1
	mov	r0, #0
	str	r2, [r8, #180]
	mov	r1, #0
	strd	r0, [r10]
	strd	r0, [r7, #-8]
	ldr	r1, [r8, #148]
	ldr	r0, [r6, #520]
	bl	FSP_SetDisplay
	ldr	r3, [r5, #4004]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L96
.L79:
	add	r5, r4, #49152
	ldr	r0, [r6, #520]
	add	r5, r5, #168
	str	r8, [sp]
	mov	r2, r4
	mov	r1, #1
	mov	r3, r5
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L80
	ldr	r1, [r8, #148]
	mov	r0, r4
	bl	VC1DEC_RecycleImage
	ldr	r1, [r8, #544]
	ldr	r0, [r6, #520]
	mov	r8, #0
	bl	FreeUsdByDec
	mov	r9, #0
	strd	r8, [r10]
	ldr	r0, [r6, #520]
	ldr	r1, [r7, #-8]
	bl	FreeUsdByDec
	strd	r8, [r7, #-8]
	b	.L82
.L80:
	ldr	r3, [r8, #152]
	cmp	r3, #100
	bhi	.L82
	ldr	r3, [r8, #68]
	cmp	r3, #31
	bls	.L82
	ldr	r3, [r8, #72]
	cmp	r3, #31
	movhi	r0, #0
	bls	.L82
.L90:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L96:
	strb	r2, [r3, #1]
	mov	r1, #0
	ldr	r2, [r5, #4004]
	mov	r3, #3
	strb	r1, [r2]
	strb	r3, [r9, #449]
	b	.L79
.L83:
	mvn	r0, #0
	b	.L90
.L95:
	ldr	r3, .L97
	movw	r2, #397
	ldr	r1, .L97+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L90
.L98:
	.align	2
.L97:
	.word	.LC23
	.word	.LC24
	UNWIND(.fnend)
	.size	VC1DEC_GetRemainImg, .-VC1DEC_GetRemainImg
	.align	2
	.global	VC1_ArrangeVahbMem
	.type	VC1_ArrangeVahbMem, %function
VC1_ArrangeVahbMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	mov	r5, r1
	sub	r1, r1, #32
	movw	r3, #8160
	cmp	r1, r3
	mov	r7, r0
	mov	r6, r2
	bhi	.L100
	sub	r2, r2, #32
	cmp	r2, r3
	bhi	.L100
	add	r2, r0, #28160
	mov	r1, #0
	add	r2, r2, #208
	mov	r0, r1
.L103:
	str	r1, [r2, #-492]
	add	r1, r1, #1
	cmp	r1, #5
	strb	r0, [r2, #-1679]
	strb	r0, [r2, #-1680]
	add	r2, r2, #1680
	bne	.L103
	ldr	r3, [r7]
	ldr	r4, [r3, #732]
	ldr	r2, [r3, #28]
	cmp	r4, #0
	bne	.L104
	cmp	r2, #25
	beq	.L128
.L124:
	mov	r4, r1
	mov	r8, #3
	mov	r9, #2
.L105:
	ldr	r3, .L131
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #56
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r7]
	str	r5, [fp, #-52]
	str	r6, [fp, #-48]
	ldr	r3, [r3, #28]
	str	r5, [fp, #-44]
	cmp	r3, #24
	str	r6, [fp, #-40]
	beq	.L115
	uxtb	r3, r9
	strb	r8, [fp, #-55]
	strb	r4, [fp, #-54]
.L120:
	add	r5, r7, #49152
	sub	r1, fp, #56
	strb	r3, [fp, #-53]
	ldr	r0, [r5, #520]
	bl	FSP_ConfigInstance
	subs	r4, r0, #0
	bne	.L116
	ldr	r1, [r7]
	sub	r3, fp, #60
	ldr	r0, [r5, #520]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L129
	cmp	r0, #0
	bne	.L118
.L122:
	mov	r4, #1
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L100:
	mov	r3, r6
	mov	r2, r5
	ldr	r1, .L131+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r4, #0
.L127:
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L104:
	cmp	r2, #25
	bne	.L124
	ldr	r2, [r3, #692]
	ldr	r1, [r3, #696]
	cmp	r5, r2
	bhi	.L112
	cmp	r6, r1
	bhi	.L112
	ldr	r1, [r3, #720]
	ldr	r2, [r3, #716]
	cmp	r1, #0
	add	r8, r2, #2
	moveq	r9, #1
	bne	.L130
.L114:
	ldrb	r4, [r3, #740]	@ zero_extendqisi2
	b	.L105
.L116:
	ldr	r1, .L131+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r4, #0
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L128:
	ldr	r2, [r3, #692]
	cmp	r5, r2
	ldrhi	r0, [r3, #696]
	bhi	.L107
	ldr	r1, [r3, #696]
	cmp	r6, r1
	mov	r0, r1
	bhi	.L107
	add	r0, r7, #12288
	ldrb	r0, [r0, #448]	@ zero_extendqisi2
	tst	r0, #8
	bne	.L122
	ldr	ip, [r3, #720]
	ldr	r0, [r3, #716]
	cmp	ip, #0
	add	r8, r0, #2
	moveq	r9, #1
	beq	.L110
	add	r9, r0, #1
	cmp	r9, #17
	movcs	r9, #17
.L110:
	ldrb	r4, [r3, #740]	@ zero_extendqisi2
	mov	r6, r1
	mov	r5, r2
	b	.L105
.L115:
	mov	r3, #1
	strb	r4, [fp, #-54]
	strb	r3, [fp, #-55]
	b	.L120
.L112:
	str	r1, [sp, #4]
	mov	r3, r6
	str	r2, [sp]
	mov	r0, #0
	mov	r2, r5
	ldr	r1, .L131+12
	bl	dprint_vfmw
	mov	r4, #0
	b	.L127
.L129:
	add	r0, r5, #168
	bl	ResetVoQueue
.L118:
	ldr	r1, .L131+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L127
.L130:
	add	r9, r2, #1
	cmp	r9, #17
	movcs	r9, #17
	b	.L114
.L107:
	str	r0, [sp, #4]
	mov	r3, r6
	str	r2, [sp]
	mov	r0, #0
	mov	r2, r5
	ldr	r1, .L131+12
	bl	dprint_vfmw
	b	.L127
.L132:
	.align	2
.L131:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC25
	.word	.LC28
	.word	.LC26
	.word	.LC27
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
	add	r5, r0, #49152
	mov	r6, r0
	mov	r4, r1
	add	r8, r0, #12288
	ldr	r1, [r7, #4092]
	ldr	r0, [r5, #520]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L156
	movw	r3, #3544
	ldrsb	r2, [r8, r3]
	add	r3, r6, #20480
	cmp	r2, #0
	bne	.L157
	strb	r2, [r4, #5]
	ldrb	r1, [r3, #2612]	@ zero_extendqisi2
	strb	r1, [r4, #4]
	ldrb	r1, [r3, #2863]	@ zero_extendqisi2
	cmp	r1, #4
	moveq	r1, #3
	strb	r1, [r4, #3]
	ldr	r1, [r5, #76]
	sub	r1, r1, #1
	strh	r1, [r4, #80]	@ movhi
	ldr	r1, [r5, #72]
	strb	r2, [r4, #8]
	sub	r1, r1, #1
	strh	r1, [r4, #78]	@ movhi
	ldrb	r1, [r3, #2615]	@ zero_extendqisi2
	strb	r2, [r4, #9]
	strb	r1, [r4, #6]
	ldrb	r1, [r8, #456]	@ zero_extendqisi2
	strb	r2, [r4, #10]
	strb	r2, [r4, #11]
	strb	r1, [r4, #7]
	ldrb	r1, [r3, #2618]	@ zero_extendqisi2
	strb	r1, [r4, #13]
	ldrb	r1, [r3, #2622]	@ zero_extendqisi2
	strb	r1, [r4, #14]
	ldrb	r1, [r3, #2882]	@ zero_extendqisi2
	strb	r1, [r4, #12]
	ldrb	r1, [r3, #2892]	@ zero_extendqisi2
	strb	r1, [r4, #18]
	ldrb	r1, [r3, #2867]	@ zero_extendqisi2
	strb	r1, [r4, #19]
	ldrb	r1, [r3, #2866]	@ zero_extendqisi2
	strb	r1, [r4, #17]
	ldr	r1, [r3, #2952]
	strb	r1, [r4, #16]
	ldrb	r1, [r3, #2626]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L148
	ldrb	r2, [r3, #2866]	@ zero_extendqisi2
	cmp	r2, #8
	movhi	r2, #0
	movls	r2, #1
	strb	r2, [r4, #20]
.L149:
	ldrb	r1, [r3, #2886]	@ zero_extendqisi2
	add	r2, r4, #12288
	strb	r1, [r4, #24]
	ldrb	r1, [r3, #2885]	@ zero_extendqisi2
	strb	r1, [r4, #23]
	ldrb	r1, [r3, #2620]	@ zero_extendqisi2
	strb	r1, [r4, #22]
	ldrb	r1, [r3, #2884]	@ zero_extendqisi2
	strb	r1, [r4, #25]
	ldr	r1, [r3, #2896]
	strb	r1, [r4, #26]
	ldrb	r1, [r3, #2887]	@ zero_extendqisi2
	strb	r1, [r4, #21]
	ldrb	r1, [r3, #2871]	@ zero_extendqisi2
	strb	r1, [r4, #27]
	ldrb	r1, [r3, #2872]	@ zero_extendqisi2
	strb	r1, [r4, #28]
	ldr	r1, [r7, #4004]
	ldrb	r1, [r1, #1029]	@ zero_extendqisi2
	strb	r1, [r4, #30]
	ldr	r1, [r7, #4000]
	ldrb	r1, [r1, #1029]	@ zero_extendqisi2
	strb	r1, [r4, #29]
	ldrb	r1, [r3, #2869]	@ zero_extendqisi2
	strb	r1, [r4, #31]
	ldrb	r1, [r3, #2991]	@ zero_extendqisi2
	strb	r1, [r4, #32]
	ldrb	r1, [r3, #2881]	@ zero_extendqisi2
	strb	r1, [r4, #35]
	ldrb	r1, [r3, #2621]	@ zero_extendqisi2
	strb	r1, [r4, #36]
	ldrb	r1, [r3, #2877]	@ zero_extendqisi2
	strb	r1, [r4, #37]
	ldrb	r1, [r3, #2879]	@ zero_extendqisi2
	strb	r1, [r4, #38]
	ldrb	r1, [r3, #2880]	@ zero_extendqisi2
	strb	r1, [r4, #39]
	ldrb	r1, [r3, #2878]	@ zero_extendqisi2
	strb	r1, [r4, #40]
	ldr	r1, [r3, #2944]
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #42]
	ldr	r1, [r3, #2940]
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #43]
	ldr	r1, [r3, #2948]
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #45]
	ldrb	r1, [r3, #2864]	@ zero_extendqisi2
	strb	r1, [r4, #50]
	ldrb	r1, [r3, #2876]	@ zero_extendqisi2
	strb	r1, [r4, #49]
	ldrb	r1, [r3, #2875]	@ zero_extendqisi2
	strb	r1, [r4, #48]
	ldr	r1, [r3, #2956]
	str	r1, [r2, #84]
	ldrb	r1, [r3, #2624]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L158
	mov	r1, #0
	mov	ip, r1
	mov	r9, r1
	mov	lr, r1
.L152:
	strb	lr, [r4, #59]
	strb	r9, [r4, #60]
	strb	ip, [r4, #61]
	str	r1, [r0, #352]
	ldrb	r3, [r3, #2612]	@ zero_extendqisi2
	strb	r3, [r0, #330]
.L146:
	add	r3, r6, #36864
	add	r6, r6, #12736
	ldr	r1, .L162
	add	r6, r6, #13
	ldr	r3, [r3, #4]
	strh	r3, [r4, #72]	@ movhi
	ldr	r3, [r7, #4032]
	strh	r3, [r4, #74]	@ movhi
	ldr	r3, [r7, #4036]
	strh	r3, [r4, #76]	@ movhi
	ldrb	r3, [r8, #459]	@ zero_extendqisi2
	strb	r3, [r4, #63]
	ldrb	r3, [r8, #460]	@ zero_extendqisi2
	strb	r3, [r4, #62]
	ldr	r0, [r7, #4016]
	adds	r3, r0, #127
	addmi	r3, r0, #254
	mov	r3, r3, asr #7
	mov	r3, r3, asl #4
	str	r3, [r2, #116]
	ldr	r3, [r5, #96]
	str	r3, [r2, #120]
	ldr	r3, [r5, #100]
	str	r3, [r2, #124]
	ldr	r3, [r5, #104]
	str	r3, [r2, #128]
	ldr	r3, [r5, #108]
	str	r3, [r2, #132]
	ldr	r3, [r5, #112]
	str	r3, [r2, #136]
	ldr	r3, [r5, #116]
	str	r3, [r2, #140]
	ldr	r3, [r5, #120]
	str	r3, [r2, #144]
	str	r6, [r4, #64]
	ldr	r2, [r5, #520]
	ldrh	r3, [r4, #78]
	ldr	r2, [r1, r2, asl #2]
	add	r3, r3, #1
	str	r3, [r2, #1500]
	ldr	r3, [r5, #520]
	ldr	r2, [r1, r3, asl #2]
	ldrh	r3, [r4, #80]
	add	r3, r3, #1
	str	r3, [r2, #1504]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L157:
	ldr	r2, [r3, #3004]
	mov	ip, #1680
	strb	r2, [r4, #5]
	ldrb	r2, [r3, #2628]	@ zero_extendqisi2
	strb	r2, [r4, #4]
	ldrb	r2, [r3, #2961]	@ zero_extendqisi2
	cmp	r2, #4
	moveq	r2, #3
	strb	r2, [r4, #3]
	ldr	r2, [r3, #3004]
	cmp	r2, #3
	ldr	r2, [r5, #76]
	addeq	r2, r2, #1
	addeq	r2, r2, r2, lsr #31
	moveq	r2, r2, asr #1
	sub	r2, r2, #1
	strh	r2, [r4, #80]	@ movhi
	ldr	r1, [r5, #72]
	sub	r1, r1, #1
	strh	r1, [r4, #78]	@ movhi
	ldrb	r2, [r3, #3001]	@ zero_extendqisi2
	strb	r2, [r4, #8]
	ldrb	r2, [r3, #2804]	@ zero_extendqisi2
	strb	r2, [r4, #6]
	ldrb	r2, [r3, #2992]	@ zero_extendqisi2
	strb	r2, [r4, #9]
	ldrb	r2, [r8, #456]	@ zero_extendqisi2
	strb	r2, [r4, #7]
	ldr	r1, [r7, #4056]
	mla	r1, ip, r1, r8
	add	r1, r1, #15424
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	strb	r2, [r4, #10]
	ldr	r2, [r7, #4072]
	mla	r2, ip, r2, r8
	add	r2, r2, #15424
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	strb	r2, [r4, #11]
	ldrb	r2, [r3, #2990]	@ zero_extendqisi2
	strb	r2, [r4, #15]
	ldrb	r2, [r3, #2805]	@ zero_extendqisi2
	strb	r2, [r4, #13]
	ldrb	r2, [r3, #2809]	@ zero_extendqisi2
	strb	r2, [r4, #14]
	ldrb	r2, [r3, #2960]	@ zero_extendqisi2
	strb	r2, [r4, #12]
	ldrb	r2, [r3, #3128]	@ zero_extendqisi2
	strb	r2, [r4, #18]
	ldrb	r2, [r3, #2963]	@ zero_extendqisi2
	strb	r2, [r4, #19]
	ldrb	r2, [r3, #2970]	@ zero_extendqisi2
	strb	r2, [r4, #17]
	ldr	r2, [r3, #3076]
	strb	r2, [r4, #16]
	ldrb	r2, [r3, #2810]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L139
	ldrb	r2, [r3, #2970]	@ zero_extendqisi2
	cmp	r2, #8
	movhi	r2, #0
	movls	r2, #1
	strb	r2, [r4, #20]
.L140:
	ldrb	r1, [r3, #3122]	@ zero_extendqisi2
	add	r2, r4, #12288
	strb	r1, [r4, #24]
	ldrb	r1, [r3, #3121]	@ zero_extendqisi2
	strb	r1, [r4, #23]
	ldrb	r1, [r3, #2807]	@ zero_extendqisi2
	strb	r1, [r4, #22]
	ldrb	r1, [r3, #3120]	@ zero_extendqisi2
	strb	r1, [r4, #25]
	ldr	r1, [r3, #3132]
	strb	r1, [r4, #26]
	ldrb	r1, [r3, #3123]	@ zero_extendqisi2
	strb	r1, [r4, #21]
	ldrb	r1, [r3, #2974]	@ zero_extendqisi2
	strb	r1, [r4, #27]
	ldrb	r1, [r3, #2975]	@ zero_extendqisi2
	strb	r1, [r4, #28]
	ldrb	r1, [r3, #2993]	@ zero_extendqisi2
	strb	r1, [r4, #34]
	ldrb	r1, [r3, #2985]	@ zero_extendqisi2
	strb	r1, [r4, #33]
	ldrb	ip, [r3, #3001]	@ zero_extendqisi2
	ldr	r1, [r7, #4004]
	add	r1, r1, ip
	ldrb	r1, [r1, #1029]	@ zero_extendqisi2
	strb	r1, [r4, #30]
	ldr	r1, [r7, #4000]
	ldrb	ip, [r3, #3001]	@ zero_extendqisi2
	add	r1, r1, ip
	ldrb	r1, [r1, #1029]	@ zero_extendqisi2
	strb	r1, [r4, #29]
	ldrb	r1, [r3, #2973]	@ zero_extendqisi2
	strb	r1, [r4, #31]
	ldrb	r1, [r3, #2991]	@ zero_extendqisi2
	strb	r1, [r4, #32]
	ldrb	r1, [r3, #2984]	@ zero_extendqisi2
	strb	r1, [r4, #35]
	ldrb	r1, [r3, #2808]	@ zero_extendqisi2
	strb	r1, [r4, #36]
	ldrb	r1, [r3, #2980]	@ zero_extendqisi2
	strb	r1, [r4, #37]
	ldrb	r1, [r3, #2982]	@ zero_extendqisi2
	strb	r1, [r4, #38]
	ldrb	r1, [r3, #2983]	@ zero_extendqisi2
	strb	r1, [r4, #39]
	ldrb	r1, [r3, #2981]	@ zero_extendqisi2
	strb	r1, [r4, #40]
	ldrb	r1, [r3, #2997]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #46]
	ldrb	r1, [r3, #2995]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #42]
	ldrb	r1, [r3, #2999]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #44]
	ldrb	r1, [r3, #3000]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #41]
	ldrb	r1, [r3, #2994]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #43]
	ldrb	r1, [r3, #2998]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #47]
	ldrb	r1, [r3, #2996]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #45]
	ldrb	r1, [r3, #2962]	@ zero_extendqisi2
	strb	r1, [r4, #50]
	ldrb	r1, [r3, #2979]	@ zero_extendqisi2
	strb	r1, [r4, #49]
	ldrb	r1, [r3, #2978]	@ zero_extendqisi2
	strb	r1, [r4, #48]
	ldrb	r1, [r3, #2989]	@ zero_extendqisi2
	strb	r1, [r4, #53]
	ldrb	r1, [r3, #2986]	@ zero_extendqisi2
	strb	r1, [r4, #54]
	ldrb	r1, [r3, #2987]	@ zero_extendqisi2
	strb	r1, [r4, #51]
	ldrb	r1, [r3, #2988]	@ zero_extendqisi2
	strb	r1, [r4, #52]
	ldr	r1, [r3, #3108]
	str	r1, [r2, #84]
	ldr	r1, [r5, #48]
	str	r1, [r2, #88]
	ldr	r1, [r5, #52]
	str	r1, [r2, #92]
	ldrb	r1, [r3, #2813]	@ zero_extendqisi2
	strb	r1, [r4, #55]
	ldrb	r1, [r3, #2814]	@ zero_extendqisi2
	strb	r1, [r4, #56]
	ldrb	r1, [r3, #2815]	@ zero_extendqisi2
	strb	r1, [r4, #57]
	ldrb	r1, [r3, #2816]	@ zero_extendqisi2
	strb	r1, [r4, #58]
	ldr	r1, [r3, #3004]
	cmp	r1, #3
	beq	.L159
	ldrb	r1, [r3, #2813]	@ zero_extendqisi2
	strb	r1, [r0, #325]
	ldrb	r1, [r3, #2814]	@ zero_extendqisi2
	strb	r1, [r0, #326]
	ldrb	r1, [r3, #2815]	@ zero_extendqisi2
	strb	r1, [r0, #327]
	ldrb	r1, [r3, #2816]	@ zero_extendqisi2
	strb	r1, [r0, #328]
.L145:
	ldrb	r3, [r3, #2628]	@ zero_extendqisi2
	strb	r3, [r0, #330]
	ldrb	r3, [r8, #459]	@ zero_extendqisi2
	strb	r3, [r4, #63]
	b	.L146
.L148:
	cmp	r1, #1
	beq	.L160
	cmp	r1, #2
	movne	r2, #1
	strb	r2, [r4, #20]
	b	.L149
.L139:
	cmp	r2, #1
	beq	.L161
	cmp	r2, #2
	moveq	r2, #0
	movne	r2, #1
	strb	r2, [r4, #20]
	b	.L140
.L161:
	ldrb	r2, [r3, #2971]	@ zero_extendqisi2
	adds	r2, r2, #0
	movne	r2, #1
	strb	r2, [r4, #20]
	b	.L140
.L160:
	ldrb	r2, [r3, #2868]	@ zero_extendqisi2
	adds	r2, r2, #0
	movne	r2, #1
	strb	r2, [r4, #20]
	b	.L149
.L159:
	ldrb	r1, [r3, #3001]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L144
	ldrb	r1, [r3, #2813]	@ zero_extendqisi2
	strb	r1, [r0, #325]
	ldrb	r1, [r3, #2814]	@ zero_extendqisi2
	strb	r1, [r0, #326]
	ldrb	r1, [r3, #2815]	@ zero_extendqisi2
	strb	r1, [r0, #327]
	ldrb	r1, [r3, #2816]	@ zero_extendqisi2
	strb	r1, [r0, #328]
	ldrb	r1, [r3, #3001]	@ zero_extendqisi2
.L144:
	cmp	r1, #1
	bne	.L145
	ldrb	r1, [r3, #2813]	@ zero_extendqisi2
	strb	r1, [r0, #320]
	ldrb	r1, [r3, #2814]	@ zero_extendqisi2
	strb	r1, [r0, #321]
	ldrb	r1, [r3, #2815]	@ zero_extendqisi2
	strb	r1, [r0, #322]
	ldrb	r1, [r3, #2816]	@ zero_extendqisi2
	strb	r1, [r0, #323]
	b	.L145
.L158:
	ldr	ip, [r7, #4056]
	mov	r9, #1680
	ldr	r1, [r7, #4072]
	ldrb	lr, [r3, #2863]	@ zero_extendqisi2
	mla	ip, r9, ip, r8
	sub	lr, lr, #2
	mla	r1, r9, r1, r8
	tst	lr, #253
	add	ip, ip, #14400
	ldrneb	lr, [r3, #2862]	@ zero_extendqisi2
	add	r1, r1, #14400
	ldrb	r9, [ip, #2]	@ zero_extendqisi2
	ldrb	ip, [r1, #2]	@ zero_extendqisi2
	movne	r1, lr
	moveq	r1, ip
	moveq	lr, ip
	b	.L152
.L156:
	mov	r2, #916
	ldr	r1, .L162+4
	mov	r0, #22
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L163:
	.align	2
.L162:
	.word	s_pstVfmwChan
	.word	.LC29
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
	ldr	ip, .L165
	add	r1, r0, #24064
	ldr	lr, [r3, #3652]
	add	r0, r2, #84
	add	r1, r1, #72
	ldr	ip, [ip, #52]
	strb	lr, [r2, #70]
	ldr	r3, [r3, #3652]
	mov	r2, r3, asl #6
	sub	r2, r2, r3, asl #4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L166:
	.align	2
.L165:
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
	beq	.L168
	add	r3, r0, #8192
	ldr	r3, [r3, #2556]
	cmp	r3, #3
	beq	.L173
.L168:
	add	r3, r0, #32768
	add	r6, r1, #12288
	ldr	r3, [r3, #3728]
	sub	r3, r3, #1
	str	r3, [r6, #164]
.L169:
	add	r5, r0, #20480
	ldr	r3, [r6, #260]
	mov	r4, #1680
	mov	ip, #0
	ldr	r2, [r5, #3592]
	and	lr, r3, #1
	cmp	r2, #0
	add	r3, r2, #63
	movlt	r2, r3
	mov	r2, r2, asr #6
	mov	r2, r2, asl #4
	add	r3, r2, #536870913
	add	r3, r3, #81920
	orr	r3, r3, lr, asl #30
	str	r3, [r6, #168]
	ldr	lr, [r5, #3624]
	ldr	r3, [r5, #3608]
	ldr	r2, [r5, #3552]
	mla	lr, r4, lr, r0
	mla	r0, r4, r3, r0
	ldr	r2, [r2, #1092]
	add	r3, lr, #15040
	and	r2, r2, #3
	ldr	r3, [r3, #4]
	add	r0, r0, #15040
	mov	r2, r2, asl #4
	ldr	r0, [r0, #4]
	and	r3, r3, #3
	strb	ip, [r1, #69]
	orr	r3, r2, r3, asl #2
	and	r2, r0, #3
	orr	r3, r3, r2
	strb	r3, [r1, #68]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L173:
	add	r2, r0, #32768
	add	r6, r1, #12288
	ldr	r3, [r2, #3724]
	ldr	r2, [r2, #3720]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	mul	r3, r2, r3
	sub	r3, r3, #1
	str	r3, [r6, #164]
	b	.L169
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
	subs	r4, r0, #0
	beq	.L187
	add	r3, r4, #12288
	ldrb	r2, [r3, #451]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L188
.L178:
	add	r5, r4, #49152
	ldr	r0, [r5, #520]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L179
	ldr	r0, [r5, #520]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L189
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L188:
	ldrb	r3, [r3, #457]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L178
.L179:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L189:
	ldr	r0, [r5, #520]
	add	r1, r5, #168
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L187:
	ldr	r3, .L190
	movw	r2, #1794
	ldr	r1, .L190+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L191:
	.align	2
.L190:
	.word	.LC23
	.word	.LC24
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r6, r0, #49152
	add	r4, r0, #32768
	mov	r5, r0
	mov	r1, #1
	ldr	r0, [r6, #520]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #4092]
	blt	.L212
	add	r3, r5, #26624
	add	r3, r3, #64
	mov	r2, r3
	ldrh	r3, [r3]
	cmp	r3, #0
	beq	.L196
	add	r3, r5, #28160
	add	lr, r5, #35072
	add	r3, r3, #208
	add	lr, lr, #16
.L199:
	ldrh	ip, [r3]
	mov	r2, r3
	add	r3, r3, #1680
	cmp	ip, #0
	beq	.L196
	cmp	r3, lr
	bne	.L199
	mov	r1, r0
	mov	r2, #1
	ldr	r0, [r6, #520]
	bl	FSP_ClearLogicFs
	ldr	r1, .L213
	mov	r0, #1
	bl	dprint_vfmw
	add	r3, r5, #26624
	add	r5, r5, #35072
	add	r3, r3, #65
	add	r5, r5, #17
	mov	r2, #0
.L201:
	strb	r2, [r3]
	add	r3, r3, #1680
	strb	r2, [r3, #-1681]
	cmp	r3, r5
	bne	.L201
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L196:
	mov	r3, #0
	str	r2, [r4, #4000]
	mov	r1, #1
	strb	r1, [r2, #1]
.L198:
	ldr	r1, [r4, #4000]
	uxtb	r2, r3
	add	r1, r1, r3
	strb	r2, [r1, #3]
	ldr	r1, [r4, #4000]
	add	r1, r1, r3
	strb	r2, [r1, #259]
	ldr	r1, [r4, #4000]
	add	r1, r1, r3
	strb	r2, [r1, #515]
	ldr	r1, [r4, #4000]
	add	r1, r1, r3
	add	r3, r3, #1
	cmp	r3, #256
	strb	r2, [r1, #771]
	bne	.L198
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L212:
	ldr	r1, .L213+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #4088]
	ldr	r0, [r6, #520]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L194
	ldr	r1, [r7, #544]
	add	r9, r7, #560
	ldr	r0, [r6, #520]
	add	r8, r7, #576
	bl	FreeUsdByDec
	ldr	r1, [r7, #552]
	ldr	r0, [r6, #520]
	add	r10, r7, #544
	bl	FreeUsdByDec
	ldr	r1, [r7, #560]
	ldr	r0, [r6, #520]
	bl	FreeUsdByDec
	ldr	r1, [r7, #568]
	ldr	r0, [r6, #520]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r10]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #4088]
	ldr	r0, [r6, #520]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #4084]
	ldr	r0, [r6, #520]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	str	r3, [r4, #4084]
	str	r3, [r4, #4088]
	ldr	r0, [r6, #520]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #4088]
	str	r0, [r4, #4084]
.L194:
	add	r1, r5, #49152
	mov	r5, #0
	add	r1, r1, #168
	str	r5, [r4, #4080]
	ldr	r0, [r6, #520]
	bl	FSP_ClearNotInVoQueue
	ldr	r1, .L213+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L214:
	.align	2
.L213:
	.word	.LC32
	.word	.LC30
	.word	.LC31
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
	ldr	ip, .L216
	ldr	r3, [r0, #3572]
	ldr	r2, [r0, #3592]
	add	r3, r3, #1
	ldr	r1, [r0, #3556]
	ldr	r0, [r0, #3552]
	add	r3, r3, r3, lsr #31
	ldr	ip, [ip, #52]
	ldr	r1, [r1, #1544]
	mov	r3, r3, asr #1
	ldr	r0, [r0, #1544]
	mov	r3, r3, asl #5
	mul	r3, r2, r3
	add	r2, r3, r3, lsl #1
	mov	r2, r2, asr #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L217:
	.align	2
.L216:
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
	mov	r10, r0
	mov	r4, r1
	mov	r8, r2
	mov	r1, #0
	mov	r2, #256
	sub	r0, fp, #556
	mov	r9, r3
	bl	memset
	sub	r0, fp, #300
	mov	r2, #256
	mov	r1, #0
	bl	memset
	cmp	r10, #0
	beq	.L281
	ldr	r5, .L295
	add	r0, r10, #24064
	mov	r2, #16
	mov	r1, #0
	add	r0, r0, #16
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r10, #24064
	ldr	r3, [r5, #48]
	add	r0, r0, #32
	mov	r2, #16
	mov	r1, #0
	blx	r3
	ldrsb	r3, [r10, #4]
	bics	r3, r3, #2
	bne	.L221
	cmp	r4, #1
	beq	.L282
	cmp	r4, #2
	addne	r3, r10, #20480
	beq	.L283
.L229:
	mov	r0, #1
	mov	r2, #0
	str	r2, [r3, #3620]
	str	r2, [r3, #3604]
.L263:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L221:
	add	r5, r10, #8192
	ldrb	r3, [r5, #2516]	@ zero_extendqisi2
	cmp	r3, #1
	ldrb	r3, [r5, #2553]	@ zero_extendqisi2
	beq	.L284
	cmp	r3, #0
	add	r3, r10, #20480
	beq	.L285
.L239:
	ldr	r2, [r3, #3560]
	ldr	r6, [r2, #1188]
	mov	r7, r6
.L238:
	cmp	r4, #1
	beq	.L286
.L240:
	cmp	r4, #2
	bne	.L229
	cmp	r8, #0
	mov	r1, #0
	mov	r2, #1
	str	r4, [r3, #3620]
	str	r4, [r3, #3604]
	strb	r1, [r3, #3600]
	strb	r2, [r3, #3601]
	bne	.L287
.L252:
	ldr	r2, [r3, #3560]
	ldr	lr, [r3, #3552]
	ldr	ip, [r2, #1188]
.L279:
	ldr	r0, [r3, #3556]
	mov	r1, #1
	str	ip, [r3, #3608]
	mov	r2, #0
	strb	r1, [r3, #3617]
	strb	r2, [r3, #3616]
	ldr	r1, [r0, #1188]
	str	r1, [r3, #3624]
	ldr	r0, [r0, #1188]
	str	r0, [r3, #3628]
	ldr	r0, [r5, #2640]
	ldr	r7, [lr, #1188]
	cmp	r0, #1
	bls	.L288
	bics	r0, r0, #2
	beq	.L258
.L257:
	mov	lr, #1680
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
.L259:
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
	bne	.L259
	mov	r0, #1
.L292:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L285:
	ldr	r1, [r3, #3560]
	cmp	r4, #1
	ldr	r2, [r3, #3556]
	ldr	r6, [r1, #1188]
	ldr	r7, [r2, #1188]
	bne	.L240
.L286:
	ldrb	r2, [r5, #2544]	@ zero_extendqisi2
	cmp	r8, #0
	mov	r1, #0
	strb	r4, [r3, #3601]
	add	r2, r2, #1
	str	r1, [r3, #3620]
	str	r2, [r3, #3604]
	strb	r1, [r3, #3600]
	beq	.L241
	cmp	r9, r1
	beq	.L289
.L241:
	ldr	r2, [r3, #3560]
	ldr	r1, [r3, #3552]
	ldr	r4, [r2, #1188]
.L278:
	str	r4, [r3, #3608]
	ldr	r2, [r2, #1188]
	str	r2, [r3, #3612]
	ldr	r3, [r5, #2640]
	ldr	r8, [r1, #1188]
	cmp	r3, #1
	bls	.L290
.L245:
	bics	r2, r3, #2
	bne	.L246
	ldrb	r2, [r5, #2526]	@ zero_extendqisi2
	cmp	r2, #4
	beq	.L291
.L246:
	mov	r1, #1680
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
.L251:
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
	bne	.L251
	mov	r0, #1
	b	.L292
.L284:
	cmp	r3, #0
	add	r3, r10, #20480
	beq	.L239
	ldr	r1, [r3, #3556]
	ldr	r2, [r3, #3560]
	ldr	r6, [r1, #1188]
	ldr	r7, [r2, #1188]
	b	.L238
.L282:
	add	r2, r10, #20480
	ldr	r1, [r2, #3560]
	str	r4, [r2, #3604]
	str	r3, [r2, #3620]
	strb	r3, [r2, #3600]
	ldr	r4, [r1, #1188]
	str	r4, [r2, #3608]
	ldrb	r3, [r10, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r10, #8192
	beq	.L223
	ldr	r2, [r3, #2556]
	ldrb	r5, [r3, #2528]	@ zero_extendqisi2
	cmp	r2, #2
	ldrb	r6, [r3, #2529]	@ zero_extendqisi2
	ldrb	r2, [r3, #2526]	@ zero_extendqisi2
	beq	.L293
.L224:
	cmp	r2, #4
	beq	.L225
.L226:
	mov	r2, #1680
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
.L228:
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
	bne	.L228
	mov	r0, #1
	b	.L292
.L283:
	add	r2, r10, #20480
	mov	r1, #1
	ldr	r0, [r2, #3560]
	str	r1, [r2, #3620]
	str	r1, [r2, #3604]
	strb	r3, [r2, #3600]
	ldr	r1, [r2, #3556]
	ldr	r4, [r0, #1188]
	strb	r3, [r2, #3616]
	str	r4, [r2, #3608]
	ldr	r3, [r1, #1188]
	str	r3, [r2, #3624]
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
	beq	.L294
.L232:
	ldr	r0, [fp, #-560]
	mov	r1, #1680
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
.L234:
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
	bne	.L234
	mov	r0, #1
	b	.L292
.L281:
	ldr	r1, .L295+4
	mov	r0, r10
	bl	dprint_vfmw
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L223:
	ldrb	r5, [r3, #2425]	@ zero_extendqisi2
	ldrb	r6, [r3, #2426]	@ zero_extendqisi2
	ldrb	r2, [r3, #2423]	@ zero_extendqisi2
	b	.L224
.L287:
	cmp	r9, r1
	bne	.L252
	ldr	lr, [r3, #3552]
	ldr	ip, [lr, #1188]
	b	.L279
.L258:
	ldrb	r3, [r5, #2526]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L257
	b	.L263
.L289:
	ldr	r1, [r3, #3552]
	ldr	r2, [r3, #3560]
	ldr	r4, [r1, #1188]
	b	.L278
.L293:
	ldr	r3, [r3, #2632]
	cmp	r3, #1
	bne	.L224
.L225:
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
	mov	r3, #1680
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
.L227:
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
	bne	.L227
	b	.L226
.L291:
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
	mov	r2, #1680
	mul	r2, r2, r7
	mov	r1, #0
	add	r0, r2, #14464
	add	r2, r2, #14720
	add	r0, r0, #2
	add	r2, r2, #3
	add	r0, r10, r0
	add	r2, r10, r2
	mov	ip, r0
.L250:
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
	bne	.L250
	b	.L246
.L290:
	ldrb	r3, [r5, #2526]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L246
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
	mov	r2, #1680
	mul	r2, r2, r6
	mov	r1, #0
	add	r0, r2, #13952
	add	r2, r2, #14208
	add	r0, r0, #2
	add	r2, r2, #3
	add	r0, r10, r0
	add	r2, r10, r2
	mov	ip, r0
.L247:
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
	bne	.L247
	ldr	r3, [r5, #2640]
	b	.L245
.L288:
	ldrb	r3, [r5, #2526]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L257
	mov	r0, r2
	b	.L263
.L294:
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
	mov	r2, #1680
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
.L233:
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
	bne	.L233
	ldr	r4, [fp, #-564]
	b	.L232
.L296:
	.align	2
.L295:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	UNWIND(.fnend)
	.size	VC1_Vfmw_BuildRefList, .-VC1_Vfmw_BuildRefList
	.align	2
	.global	VC1_Vfmw_GetStreamInfo
	.type	VC1_Vfmw_GetStreamInfo, %function
VC1_Vfmw_GetStreamInfo:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r6, r0, #12288
	add	r4, r0, #32768
	mov	r5, r0
	ldrb	r3, [r6, #3544]	@ zero_extendqisi2
	ldr	r7, [r4, #4016]
	cmp	r3, #0
	beq	.L298
	add	r3, r0, #20480
	ldr	r8, [r4, #4020]
	movw	r2, #3338
	movw	r1, #3336
	ldr	r3, [r3, #3004]
	cmp	r3, #3
	add	r3, r0, #12736
	addeq	r8, r8, #1
	ldrh	r2, [r3, r2]
	addeq	r8, r8, r8, lsr #31
	ldrh	r3, [r3, r1]
	moveq	r8, r8, asr #1
	adds	r1, r2, #15
	addmi	r1, r2, #30
	adds	r0, r3, #15
	mul	r8, r8, r7
	addmi	r0, r3, #30
	mov	r1, r1, asr #4
	mov	r0, r0, asr #4
.L350:
	mov	r2, r0, asl #4
	movw	ip, #8160
	sub	r3, r2, #32
	cmp	r3, ip
	mov	r3, r1, asl #4
	bhi	.L301
	sub	lr, r3, #32
	cmp	lr, ip
	bhi	.L301
	ldr	r3, [r4, #4028]
	cmp	r3, r1
	beq	.L383
.L304:
	ldr	r2, [r4, #4020]
	mov	r3, r7, asl #4
	add	r3, r3, #63
	str	r7, [r4, #4024]
	bic	r3, r3, #63
	str	r3, [r4, #4040]
	str	r2, [r4, #4028]
	ldrb	r3, [r6, #456]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L312
	mov	r3, #1
.L306:
	ldrb	r2, [r6, #451]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L384
.L309:
	ldrb	r2, [r6, #448]	@ zero_extendqisi2
	eor	r2, r2, #8
	ubfx	r2, r2, #3, #1
	orrs	r3, r3, r2
	bne	.L312
.L316:
	mov	r0, r5
	bl	VC1_Vfmw_GetImageBuffer
	subs	r9, r0, #0
	beq	.L385
	add	r9, r5, #49152
	ldr	r1, [r4, #4092]
	ldr	r0, [r9, #520]
	bl	FSP_GetFsImagePtr
	subs	lr, r0, #0
	beq	.L318
	ldr	r3, [r5]
	add	ip, lr, #592
	add	r10, lr, #608
	ldr	r1, .L392
	mov	r0, #29
	ldrd	r2, [r3, #64]
	strd	r2, [ip, #-8]
	ldr	r3, [r5]
	ldrd	r2, [r3, #80]
	strd	r2, [ip]
	ldr	r3, [r5]
	ldrd	r2, [r3, #96]
	strd	r2, [r10, #-8]
	mvn	r2, #0
	ldr	r10, [r5]
	mvn	r3, #0
	ldr	r10, [r10, #112]
	str	r10, [lr]
	ldr	r10, [r5]
	ldr	r10, [r10, #116]
	str	r10, [lr, #4]
	ldr	r10, [r5]
	ldr	r10, [r10, #120]
	str	r10, [lr, #8]
	ldr	r10, [r5]
	ldr	r10, [r10, #136]
	str	r10, [lr, #12]
	ldr	lr, [r5]
	strd	r2, [lr, #64]
	ldrd	r2, [ip]
	strd	r2, [fp, #-60]
	ldrd	r2, [ip, #-8]
	strd	r2, [fp, #-52]
	ldrd	r2, [fp, #-60]
	strd	r2, [sp]
	ldrd	r2, [fp, #-52]
	bl	dprint_vfmw
.L318:
	ldrb	r3, [r6, #3544]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L319
	add	r3, r5, #20480
	ldr	r3, [r3, #3004]
	cmp	r3, #3
	beq	.L386
.L319:
	ldr	r3, [r4, #4000]
	mov	r2, #0
	str	r2, [r3, #1092]
.L320:
	ldr	r3, [r4, #4000]
	mov	r2, #0
	strb	r2, [r3, #2]
	ldrb	r3, [r6, #3544]	@ zero_extendqisi2
	cmp	r3, r2
	bne	.L321
	add	r3, r5, #20480
	ldrb	r2, [r3, #2624]	@ zero_extendqisi2
	cmp	r2, #1
	ldreqb	r2, [r3, #2862]	@ zero_extendqisi2
	ldreq	r3, [r4, #4000]
	streqb	r2, [r3, #2]
.L321:
	ldrb	r3, [r6, #450]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #1
	ldr	r3, [r4, #4080]
	movls	r10, #1
	movhi	r10, #0
	bhi	.L322
	cmp	r3, #0
	ldr	r2, [r4, #4084]
	ldr	r3, [r4, #4088]
	movne	r1, #2
	moveq	r1, #1
	cmp	r2, r3
	str	r1, [r4, #4080]
	beq	.L324
	ldr	r1, .L392+4
	mov	r0, #13
	bl	dprint_vfmw
	mov	r2, #0
	ldr	r1, [r4, #4084]
	ldr	r0, [r9, #520]
	bl	FSP_SetRef
	ldr	r3, [r4, #4088]
.L324:
	ldr	r1, [r4, #4092]
	mov	r2, #1
	str	r3, [r4, #4084]
	str	r1, [r4, #4088]
	ldr	r0, [r9, #520]
	bl	FSP_SetRef
	ldr	r1, [r4, #4084]
	ldr	r0, [r9, #520]
	bl	FSP_RemovePmv
	ldrb	r3, [r6, #450]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #1
	bhi	.L326
	ldr	r3, [r4, #4008]
	mov	r1, #0
	mov	r2, #1
	strb	r1, [r3]
	ldr	r3, [r4, #4000]
	strb	r2, [r3]
	ldr	r2, [r4, #4004]
	ldr	r3, [r4, #4000]
	str	r2, [r4, #4008]
	str	r3, [r4, #4004]
.L326:
	ldr	r1, [r4, #4092]
	ldr	r0, [r9, #520]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #4084]
	str	r0, [fp, #-52]
	ldr	r0, [r9, #520]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #4088]
	mov	r10, r0
	ldr	r0, [r9, #520]
	bl	FSP_GetLogicFs
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	cmpne	r10, #0
	moveq	r2, #1
	movne	r2, #0
	cmp	r0, #0
	orreq	r2, r2, #1
	str	r0, [fp, #-52]
	cmp	r2, #0
	bne	.L387
	ldrb	r2, [r6, #3544]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L388
.L332:
	mov	r2, #0
.L377:
	str	r2, [r3, #92]
	ldrb	r2, [r6, #450]	@ zero_extendqisi2
	cmp	r2, #5
	beq	.L389
.L334:
	ldr	r1, [r3, #28]
	cmp	r1, #0
	beq	.L335
	ldr	r2, [r3, #32]
	cmp	r2, #0
	beq	.L335
	ldr	r2, [fp, #-52]
	mov	r9, #0
	ldr	r2, [r2, #28]
	cmp	r2, #0
	ldreq	r2, [r1, #8]
	ldrne	r2, [r2, #8]
	str	r2, [r6, #112]
	ldr	r2, [r10, #28]
	cmp	r2, #0
	ldreq	r2, [r3, #28]
	ldr	r2, [r2, #8]
	str	r2, [r6, #108]
	ldr	r2, [r3, #28]
	ldr	r2, [r2, #8]
	str	r2, [r6, #236]
	ldr	r2, [r3, #8]
	str	r2, [r6, #116]
	ldr	r2, [fp, #-52]
	ldr	r2, [r2, #8]
	str	r2, [r6, #120]
	ldr	r2, [r3, #32]
	ldr	r2, [r2, #8]
	str	r2, [r6, #104]
	ldr	r2, [r3, #32]
	ldr	r2, [r2, #24]
	str	r2, [r6, #184]
	ldr	r2, [r3, #32]
	ldr	r2, [r2, #28]
	str	r2, [r6, #188]
	ldr	r2, [r3, #32]
	ldr	r2, [r2, #60]
	str	r2, [r6, #192]
	ldr	r2, [r3, #32]
	ldr	r2, [r2, #44]
	str	r2, [r6, #196]
	ldr	r2, [r3, #32]
	ldr	r2, [r2, #48]
	str	r2, [r6, #200]
	ldr	r3, [r3, #28]
	ldr	r10, [r4, #4000]
	ldr	r0, [r3, #8]
	bl	MEM_Phy2Vir
	str	r9, [r10, #1548]
	str	r0, [r10, #1544]
	ldr	r0, [r6, #108]
	ldr	r10, [r4, #4008]
	bl	MEM_Phy2Vir
	str	r9, [r10, #1548]
	str	r0, [r10, #1544]
	ldr	r0, [r6, #112]
	ldr	r10, [r4, #4004]
	bl	MEM_Phy2Vir
	str	r9, [r10, #1548]
	str	r0, [r10, #1544]
.L311:
	movw	r3, #3544
	ldrsb	r3, [r6, r3]
	cmp	r3, #0
	bne	.L341
	ldr	r1, [r4, #4000]
	add	r2, r5, #20480
	strb	r3, [r1, #1027]
	ldr	r1, [r4, #4000]
	ldrb	r0, [r2, #2863]	@ zero_extendqisi2
	strb	r0, [r1, #1028]
	ldrb	r0, [r2, #2871]	@ zero_extendqisi2
	ldr	r1, [r4, #4000]
	sub	ip, r0, #2
	cmp	ip, #1
	movls	r3, #1
	bls	.L342
	cmp	r0, #4
	beq	.L390
.L342:
	add	r7, r5, #36864
	add	r8, r5, #49152
	strb	r3, [r1, #1030]
	mov	r2, #1
	strb	r3, [r1, #1029]
	mov	r3, #0
	str	r2, [r7, #4]
	strb	r3, [r7, #16]
	ldr	r0, [r6, #3576]
	ldr	r9, [r8, #12]
	bl	BsPos
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	add	r0, r9, r0, asr #3
	str	r0, [r7, #8]
	ldr	r0, [r6, #3576]
	ldr	r9, [r8, #24]
	bl	BsPos
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	add	r0, r9, r0, asr #3
	str	r0, [r7, #20]
	ldr	r0, [r6, #3576]
	bl	BsPos
	and	r0, r0, #7
	str	r0, [r7, #24]
	ldr	r0, [r6, #3576]
	ldr	r9, [r8, #32]
	bl	BsPos
	mov	r9, r9, asl #3
	rsb	r0, r0, r9
	str	r0, [r7, #28]
	ldr	r2, [r8, #72]
	ldr	r3, [r8, #76]
	mul	r3, r3, r2
	sub	r3, r3, #1
	str	r3, [r7, #32]
	ldrb	r1, [r6, #450]	@ zero_extendqisi2
.L343:
	mov	r3, #1
	mov	r2, #0
	add	r0, r5, #12736
	bl	VC1_Vfmw_BuildRefList
	subs	r9, r0, #0
	movne	r9, #1
	bne	.L374
	add	r5, r5, #49152
	ldr	r1, [r4, #4092]
	mov	r2, #1
	ldr	r0, [r5, #520]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #4000]
	ldr	r1, .L392+8
	mov	r0, #1
	strb	r9, [r3]
	ldr	r3, [r4, #4000]
	strb	r9, [r3, #1]
	bl	dprint_vfmw
	b	.L374
.L301:
	ldr	r1, .L392+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r9, #0
.L374:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L298:
	ldr	r1, [r4, #4020]
	mov	r0, r7
	mul	r8, r1, r7
	b	.L350
.L312:
	add	r9, r5, #49152
	add	r3, r5, #35072
	add	r3, r3, #16
	ldr	r1, [r4, #4088]
	str	r3, [r4, #4000]
	str	r3, [r4, #4012]
	str	r3, [r4, #4008]
	str	r3, [r4, #4004]
	ldr	r0, [r9, #520]
	bl	FSP_GetFsImagePtr
	subs	r2, r0, #0
	beq	.L308
	ldr	r1, [r2, #544]
	add	r3, r2, #576
	ldr	r0, [r9, #520]
	add	r10, r2, #560
	str	r3, [fp, #-52]
	str	r2, [fp, #-60]
	bl	FreeUsdByDec
	ldr	r2, [fp, #-60]
	ldr	r1, [r10, #-8]
	ldr	r0, [r9, #520]
	add	ip, r2, #544
	str	r2, [fp, #-64]
	str	ip, [fp, #-60]
	bl	FreeUsdByDec
	ldr	r2, [fp, #-64]
	ldr	r0, [r9, #520]
	ldr	r1, [r2, #560]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-52]
	ldr	r0, [r9, #520]
	ldr	r1, [r3, #-8]
	bl	FreeUsdByDec
	ldr	ip, [fp, #-60]
	ldr	r3, [fp, #-52]
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [ip]
	strd	r0, [r10, #-8]
	strd	r0, [r10]
	strd	r0, [r3, #-8]
	ldr	r1, [r4, #4088]
	ldr	r0, [r9, #520]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #4084]
	ldr	r0, [r9, #520]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	str	r3, [r4, #4084]
	str	r3, [r4, #4088]
	ldr	r0, [r9, #520]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #4088]
	str	r0, [r4, #4084]
.L308:
	add	r3, r5, #26624
	add	r1, r5, #35072
	add	r3, r3, #65
	add	r1, r1, #17
	mov	r2, #0
	str	r2, [r4, #4080]
.L314:
	strb	r2, [r3]
	add	r3, r3, #1680
	strb	r2, [r3, #-1681]
	cmp	r3, r1
	bne	.L314
	add	r10, r5, #49152
	ldr	r0, [r9, #520]
	add	r10, r10, #168
	mov	r1, r10
	bl	FSP_ClearNotInVoQueue
	ldrb	r9, [r6, #448]	@ zero_extendqisi2
	and	r9, r9, #8
	ands	r9, r9, #255
	bne	.L316
	mov	r0, r10
	bl	ResetVoQueue
	ldr	r1, [r5]
	mov	r3, #2
	mov	r0, r5
	ldr	r2, [r1, #692]
	ldr	ip, [r1, #696]
	adds	r1, r2, #15
	addmi	r1, r2, #30
	adds	r2, ip, #15
	addmi	r2, ip, #30
	mov	r1, r1, asr #4
	str	r1, [r6, #276]
	mov	r2, r2, asr #4
	str	r2, [r6, #280]
	add	r2, r2, #1
	mov	r1, r1, asl #4
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
	mov	r2, r2, asl #5
	bl	VC1_ArrangeVahbMem
	cmp	r0, #1
	bne	.L315
	ldrb	r3, [r6, #448]	@ zero_extendqisi2
	orr	r3, r3, #8
	strb	r3, [r6, #448]
	b	.L316
.L385:
	ldr	r1, .L392+16
	mov	r0, #1
	bl	dprint_vfmw
	b	.L374
.L383:
	ldr	r3, [r4, #4024]
	cmp	r3, r0
	bne	.L304
	mov	r3, r7, asl #4
	add	r3, r3, #63
	bic	r3, r3, #63
	str	r3, [r4, #4040]
	ldrb	r3, [r6, #456]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #0
	bne	.L306
	b	.L309
.L322:
	cmp	r3, #1
	bhi	.L326
	ldr	r0, [r9, #520]
	mov	r2, #1
	ldr	r1, [r4, #4092]
	mov	r9, r10
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #4000]
	ldr	r1, .L392+20
	mov	r0, #1
	strb	r10, [r3]
	ldr	r3, [r4, #4000]
	strb	r10, [r3, #1]
	bl	dprint_vfmw
	b	.L374
.L387:
	mov	r2, #1
	ldr	r1, [r4, #4092]
	ldr	r0, [r9, #520]
	str	r3, [fp, #-60]
	bl	FSP_ClearLogicFs
	ldr	r1, [r4, #4000]
	mov	ip, #0
	mov	r0, ip
	ldr	r3, [fp, #-60]
	movw	r2, #2066
	strb	ip, [r1]
	ldr	lr, [r4, #4000]
	ldr	r1, .L392+24
	strb	ip, [lr, #1]
	ldr	ip, [fp, #-52]
	stmia	sp, {r10, ip}
	bl	dprint_vfmw
	ldrb	r3, [r6, #450]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L382
.L330:
	ldr	r1, .L392+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r9, #0
	b	.L374
.L341:
	add	lr, r5, #20480
	ldr	r3, [r4, #4000]
	ldr	r2, [lr, #3004]
	strb	r2, [r3, #1027]
	ldr	r3, [r4, #4000]
	ldrb	r2, [lr, #2961]	@ zero_extendqisi2
	strb	r2, [r3, #1028]
	ldrb	r2, [lr, #2974]	@ zero_extendqisi2
	ldr	r3, [r4, #4000]
	sub	r0, r2, #2
	ldrb	r1, [lr, #3001]	@ zero_extendqisi2
	cmp	r0, #1
	movls	r2, #1
	bls	.L344
	cmp	r2, #4
	movne	r2, #0
	beq	.L391
.L344:
	add	r3, r3, r1
	add	r1, r5, #36864
	strb	r2, [r3, #1029]
	ldr	ip, [r1, #4]
	cmp	ip, #0
	beq	.L345
	subs	ip, ip, #1
	addne	r2, r5, #36864
	movne	r1, #0
	addne	r2, r2, #16
	beq	.L379
.L348:
	ldr	r3, [r2, #64]
	add	r2, r2, #48
	strb	r1, [r2, #-48]
	add	r1, r1, #1
	cmp	r1, ip
	mul	r3, r3, r7
	movcs	r0, #0
	movcc	r0, #1
	cmp	r1, #254
	movgt	r0, #0
	cmp	r0, #0
	sub	r3, r3, #1
	str	r3, [r2, #-32]
	bne	.L348
	uxtb	r1, ip
.L347:
	mov	r3, ip, asl #6
	movw	r2, #24608
	sub	ip, r3, ip, asl #4
	movw	r3, #24592
	add	ip, r6, ip
	sub	r8, r8, #1
	str	r8, [ip, r2]
	strb	r1, [ip, r3]
	ldrb	r1, [r6, #450]	@ zero_extendqisi2
	cmp	r1, #2
	bne	.L343
	ldrb	r3, [lr, #2991]	@ zero_extendqisi2
	add	r0, r5, #49152
	ldr	r2, [lr, #3108]
	mul	r2, r2, r3
	mov	r2, r2, asr #8
	str	r2, [r0, #48]
	rsb	r3, r2, r3
	subs	r3, r3, #1
	movmi	r3, #0
	str	r3, [r0, #52]
	b	.L343
.L388:
	add	r2, r5, #20480
	ldr	r2, [r2, #3004]
	cmp	r2, #3
	bne	.L332
	ldr	r2, .L392+32
	ldr	r2, [r2]
	cmp	r2, #1
	bne	.L332
	b	.L377
.L335:
	mov	r2, #1
	ldr	r1, [r4, #4092]
	ldr	r0, [r9, #520]
	str	r3, [fp, #-52]
	bl	FSP_ClearLogicFs
	ldr	ip, [r4, #4000]
	mov	r2, #0
	ldr	r3, [fp, #-52]
	mov	r0, r2
	ldr	r1, .L392+36
	strb	r2, [ip]
	ldr	ip, [r4, #4000]
	strb	r2, [ip, #1]
	ldr	ip, [r3, #32]
	ldr	r2, [r4, #4092]
	str	ip, [sp, #8]
	ldr	lr, [r3, #28]
	mov	r3, r2
	ldr	ip, [r4, #4088]
	ldr	r2, [r4, #4084]
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldrb	r3, [r6, #450]	@ zero_extendqisi2
	cmp	r3, #5
	bne	.L330
.L382:
	ldr	r3, [r9, #92]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r9, #92]
	b	.L330
.L384:
	ldrb	r2, [r6, #457]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L311
	b	.L309
.L345:
	mov	r3, #1
	str	r3, [r1, #4]
.L379:
	mov	r1, ip
	b	.L347
.L389:
	ldr	r2, [r10, #92]
	str	r2, [r3, #92]
	ldr	r1, [r4, #4008]
	ldr	r2, [r4, #4000]
	ldr	r1, [r1, #1092]
	str	r1, [r2, #1092]
	ldr	r2, [r9, #92]
	add	r2, r2, #1
	str	r2, [r9, #92]
	b	.L334
.L386:
	ldr	r3, .L392+32
	ldr	r3, [r3]
	cmp	r3, #1
	ldreq	r2, [r4, #4000]
	streq	r3, [r2, #1092]
	bne	.L319
	b	.L320
.L315:
	ldr	r1, .L392+40
	mov	r0, #1
	bl	dprint_vfmw
	ldrb	r3, [r6, #448]	@ zero_extendqisi2
	bic	r3, r3, #8
	strb	r3, [r6, #448]
	b	.L374
.L391:
	ldrb	r2, [lr, #2975]	@ zero_extendqisi2
	sub	r2, r2, #2
	cmp	r2, #1
	movhi	r2, #0
	movls	r2, #1
	b	.L344
.L390:
	ldrb	r3, [r2, #2872]	@ zero_extendqisi2
	sub	r3, r3, #2
	cmp	r3, #1
	movhi	r3, #0
	movls	r3, #1
	b	.L342
.L393:
	.align	2
.L392:
	.word	.LC36
	.word	.LC37
	.word	.LC42
	.word	.LC25
	.word	.LC35
	.word	.LC38
	.word	.LC39
	.word	.LC40
	.word	USE_FF_APT_EN
	.word	.LC41
	.word	.LC34
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
	cmp	r0, #0
	beq	.L398
	bl	VC1_Vfmw_GetStreamInfo
	subs	r4, r0, #0
	movne	r4, #1
	bne	.L396
	ldr	r1, .L399
	bl	dprint_vfmw
.L396:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L398:
	ldr	r3, .L399+4
	movw	r2, #2242
	ldr	r1, .L399+8
	mvn	r4, #0
	bl	dprint_vfmw
	b	.L396
.L400:
	.align	2
.L399:
	.word	.LC44
	.word	.LC43
	.word	.LC24
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
	ldr	lr, .L402
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
.L403:
	.align	2
.L402:
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
	ldr	r2, [r3, #3568]
	beq	.L407
	cmp	r1, #2
	beq	.L413
	cmp	r1, #0
	beq	.L412
	add	r2, r2, #1
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
.L413:
	str	r2, [r0, #3720]
	ldr	r3, [r3, #3572]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	str	r3, [r0, #3724]
	b	.L410
.L407:
	add	r2, r2, #1
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
.L412:
	str	r2, [r0, #3720]
	ldr	r3, [r3, #3572]
	str	r3, [r0, #3724]
.L410:
	mul	r1, r3, r2
	mov	r2, r2, asl #4
	mov	r3, r3, asl #4
	str	r2, [r0, #3712]
	str	r3, [r0, #3716]
	str	r1, [r0, #3728]
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
	ldr	ip, .L425
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
	ble	.L423
	cmp	r7, #3
	movle	r1, #3
	movle	r4, #2
	bgt	.L424
.L416:
	mov	r0, r6
	bl	BsSkip
	sub	r3, fp, #36
	add	r4, r3, r4, lsl #2
	cmp	r5, #12
	ldrhi	r0, [r4, #-40]
	ldrls	r0, [r4, #-20]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L424:
	cmp	r7, #8
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
	b	.L416
.L423:
	cmp	r7, #0
	mov	r1, #4
	moveq	r4, #3
	movne	r4, r1
	b	.L416
.L426:
	.align	2
.L425:
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
	ldr	r2, .L428
	sub	r3, fp, #12
	add	r3, r3, r0, lsl #2
	ldmia	r2, {r0, r1}
	sub	r2, fp, #12
	stmdb	r2, {r0, r1}
	ldr	r0, [r3, #-8]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L429:
	.align	2
.L428:
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
	ldr	r3, .L438
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
	ble	.L437
	cmp	r7, #4
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
.L432:
	mov	r0, r6
	bl	BsSkip
	sub	r3, fp, #28
	add	ip, r3, r4, lsl #2
	cmp	r5, #12
	ldrhi	r0, [ip, #-36]
	ldrls	r0, [ip, #-20]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L437:
	cmp	r7, #0
	mov	r1, r4
	movne	r4, ip
	b	.L432
.L439:
	.align	2
.L438:
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
	ldr	r3, .L449
	sub	lr, fp, #60
	add	ip, r3, #16
	mov	r4, r0
	cmp	r0, #1
	ldmia	r3, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	sub	ip, fp, #28
	stmdb	ip, {r0, r1, r2, r3}
	ble	.L448
	cmp	r4, #4
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
.L442:
	mov	r0, r6
	bl	BsSkip
	sub	r3, fp, #28
	add	r4, r3, r4, lsl #2
	cmp	r5, #12
	ldrhi	r0, [r4, #-32]
	ldrls	r0, [r4, #-16]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L448:
	cmp	r4, #0
	mov	r1, #3
	moveq	r4, r1
	movne	r4, #2
	b	.L442
.L450:
	.align	2
.L449:
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
	ldr	ip, .L457
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
	bgt	.L452
	mov	r1, #3
	bl	BsSkip
	sub	r3, fp, #44
	add	r3, r3, r4, lsl #2
	ldr	r1, [r3, #-200]
	ldr	r2, [r3, #-172]
.L453:
	sub	r3, fp, #44
	mov	r0, r4
	add	r2, r3, r2, lsl #2
	ldr	r3, [r2, #-148]
	ldr	r2, [fp, #-248]
	mul	r3, r3, r1
	str	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L452:
	mov	r1, #7
	bl	BsGet
	and	r4, r0, #15
	cmp	r4, #15
	beq	.L456
	sub	r0, r0, #112
	sub	r3, fp, #44
	add	r4, r4, #7
	add	r0, r3, r0, lsl #2
	ldr	r1, [r0, #-112]
	ldr	r2, [r0, #-56]
	b	.L453
.L456:
	ldr	r2, [fp, #-252]
	mov	r3, #4
	mov	r0, #22
	strb	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L458:
	.align	2
.L457:
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
	ldr	r5, .L467
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
	bgt	.L460
	mov	r1, #3
	bl	BsSkip
	sub	r3, fp, #44
	add	r2, r3, r4, lsl #2
	ldr	r1, [r2, #-200]
	ldr	r2, [r2, #-172]
	sub	r3, r2, #1
	cmp	r3, #7
	bhi	.L464
.L466:
	sub	r2, fp, #44
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-144]
	mul	r3, r3, r1
.L465:
	ldr	r2, [fp, #-248]
	str	r3, [r2]
.L462:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L460:
	mov	r1, #7
	bl	BsGet
	and	r4, r0, #15
	sub	r3, r4, #14
	add	r4, r4, #7
	cmp	r3, #1
	bls	.L462
	sub	r3, r0, #112
	cmp	r3, #13
	bhi	.L463
	sub	r2, fp, #44
	add	r2, r2, r3, lsl #2
	ldr	r1, [r2, #-112]
	ldr	r2, [r2, #-56]
	sub	r3, r2, #1
	cmp	r3, #7
	bls	.L466
.L464:
	str	r2, [sp]
	movw	r3, #3214
	ldr	r2, .L467+4
	mov	r0, #1
	ldr	r1, .L467+8
	bl	dprint_vfmw
	mov	r3, #0
	b	.L465
.L463:
	str	r0, [sp]
	add	r2, r5, #184
	movw	r3, #3204
	ldr	r1, .L467+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, #0
	b	.L464
.L468:
	.align	2
.L467:
	.word	.LANCHOR0+160
	.word	.LANCHOR0+360
	.word	.LC46
	.word	.LC45
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
	beq	.L487
	mov	r1, #1
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4]
	cmp	r5, #1
	beq	.L488
.L473:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L487:
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
	beq	.L489
.L472:
	mov	r3, #1
	mov	r0, #1
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L488:
	mov	r1, #2
	mov	r0, r7
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #1]
	cmp	r1, #0
	streq	r5, [r4, #12]
	beq	.L476
	cmp	r1, #2
	beq	.L490
	cmp	r1, #1
	beq	.L491
	cmp	r1, #3
	movne	r3, #0
	strne	r3, [r4, #12]
	beq	.L492
.L476:
	ldr	r3, [r4]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #768
	beq	.L473
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
	bne	.L473
	mov	r0, r7
	mov	r1, #5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	strb	r0, [r4, #8]
	b	.L473
.L492:
	mov	r1, r5
	mov	r0, r7
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #2]
	cmp	r0, #0
	movne	r3, #10
	moveq	r3, #11
	str	r3, [r4, #12]
	b	.L476
.L489:
	mov	r0, r7
	mov	r1, #5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	strb	r0, [r4, #8]
	b	.L472
.L490:
	mov	r0, r7
	bl	BsGet
	uxtb	r3, r0
	strb	r0, [r4, #6]
	add	r3, r3, #6
	str	r3, [r4, #12]
	b	.L476
.L491:
	mov	r1, #2
	mov	r0, r7
	bl	BsGet
	uxtb	r3, r0
	strb	r0, [r4, #7]
	add	r3, r3, #2
	str	r3, [r4, #12]
	b	.L476
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
.L494:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	subs	r7, r0, #0
	mov	r0, r5
	bne	.L503
	bl	BsGet
	mov	r4, r0
	cmp	r4, #1
	mov	r1, r0
	mov	r0, r5
	bgt	.L513
	bne	.L497
	bl	BsGet
	cmp	r0, #0
	beq	.L498
	cmp	r6, #0
	mov	r6, r4
	beq	.L494
.L511:
	str	r9, [r8]
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L503:
	mov	r0, #0
.L495:
	cmp	r6, #0
	mov	r7, #1
	eorne	r0, r0, #63
.L512:
	str	r0, [r8]
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L513:
	sub	r4, r4, #2
	mov	r0, #1
	mov	r0, r0, asl r4
	b	.L495
.L497:
	mov	r0, r5
	mov	r1, #4
	bl	BsGet
	cmp	r0, #255
	beq	.L511
	ldr	r3, .L514
	add	r3, r3, r0, lsl #2
	ldr	r0, [r3, #508]
	b	.L495
.L498:
	mov	r0, r5
	mov	r1, #5
	bl	BsGet
	ldr	r3, .L514
	add	r3, r3, r0, lsl #2
	ldr	r3, [r3, #380]
	cmp	r3, #2
	orreq	r0, r0, #32
	beq	.L495
	cmp	r3, #3
	bne	.L512
	b	.L495
.L515:
	.align	2
.L514:
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
	beq	.L517
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L532
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
	bls	.L529
.L520:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L530
.L522:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L531
.L524:
	ldrb	r3, [r4, #251]	@ zero_extendqisi2
	sub	r3, r3, #2
	tst	r3, #253
	bne	.L525
.L527:
	ldrb	r1, [r4, #258]	@ zero_extendqisi2
.L526:
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
.L517:
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L525:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L527
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #258]
	b	.L526
.L529:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L520
.L530:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L522
.L531:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L524
.L533:
	.align	2
.L532:
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
	beq	.L547
	ldrb	r8, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L564
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
	bls	.L558
.L539:
	cmp	r8, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L559
.L541:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L560
.L543:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L544
	ldrb	r1, [r4, #258]	@ zero_extendqisi2
.L545:
	mov	r0, r7
	bl	VC1_SetCurPicResolutionInfo
	mov	r0, r5
	bl	BsPos
	ldr	r1, .L564+4
	mov	r2, r0
	mov	r0, #18
	bl	dprint_vfmw
	ldrb	r1, [r4, #340]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #259]
	cmp	r0, #4
	beq	.L561
.L546:
	mov	r1, r7
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L547
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
	bne	.L562
.L548:
	mov	r0, r5
	bl	BsPos
	ldr	r1, .L564+8
	mov	r2, r0
	mov	r0, #18
	bl	dprint_vfmw
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L563
.L550:
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
.L547:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L558:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L539
.L562:
	add	r3, r4, #272
	ldrb	r2, [r4, #340]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L548
.L560:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L543
.L544:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #258]
	b	.L545
.L559:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L541
.L561:
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
	b	.L546
.L563:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #265]
	cmp	r0, #1
	bne	.L550
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #266]
	b	.L550
.L565:
	.align	2
.L564:
	.word	.LANCHOR0+568
	.word	.LC47
	.word	.LC48
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
	beq	.L577
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L594
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
	bls	.L589
.L571:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L590
.L573:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L591
.L575:
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
	beq	.L577
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
	bne	.L592
.L578:
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L593
.L580:
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
.L577:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L589:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L571
.L592:
	add	r3, r4, #272
	ldrb	r2, [r4, #340]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_VopDQuant
	b	.L578
.L590:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L573
.L591:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L575
.L593:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #265]
	cmp	r0, #1
	bne	.L580
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #266]
	b	.L580
.L595:
	.align	2
.L594:
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
	ldrb	r7, [r2, #258]	@ zero_extendqisi2
	mov	r5, r0
	mov	r6, r1
	mov	r0, r1
	mov	r4, r2
	mov	r1, r7
	bl	VC1_SetCurPicResolutionInfo
	ldr	r3, [r5, #16]
	cmp	r3, #1
	ble	.L634
	ldr	r9, .L639
	mov	r2, #100
	mov	r1, #0
	add	r0, r4, #248
	add	r8, r6, #32768
	ldr	r3, [r9, #48]
	blx	r3
	add	r0, r6, #24064
	ldr	r3, [r9, #48]
	mov	r2, #12288
	mov	r1, #0
	add	r0, r0, #72
	strb	r7, [r4, #258]
	blx	r3
	ldr	r2, [r8, #3656]
	ldr	r1, .L639+4
	mov	r0, #18
	bl	dprint_vfmw
	mov	r0, r5
	bl	BsPos
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r4, #324]
	bne	.L599
	ldrb	r2, [r4, #248]	@ zero_extendqisi2
.L600:
	ldr	r1, .L639+8
	mov	r0, #18
	bl	dprint_vfmw
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #12]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #249]
	bne	.L635
.L601:
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	mov	r1, #1
	mov	r0, r5
	cmp	r3, #0
	bne	.L602
	bl	BsGet
	adds	r0, r0, #0
	movne	r0, #1
	strb	r0, [r4, #251]
.L603:
	mov	r3, #0
	strb	r0, [r6, #2]
	strb	r3, [r6, #4]
	ldrb	r3, [r4, #251]	@ zero_extendqisi2
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L615
.L608:
	.word	.L607
	.word	.L609
	.word	.L610
	.word	.L615
	.word	.L611
.L611:
	ldrb	r7, [r6, #3112]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L636
.L615:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L634:
	mov	r3, #5
	mov	r0, #1
	strb	r3, [r4, #251]
	strb	r3, [r6, #2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L602:
	bl	BsGet
	cmp	r0, #1
	beq	.L632
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	beq	.L637
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
	bne	.L603
	b	.L615
.L599:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #248]
	b	.L600
.L637:
	mov	r0, #0
.L632:
	strb	r0, [r4, #251]
	b	.L603
.L610:
	ldrb	r7, [r6, #3112]	@ zero_extendqisi2
	cmp	r7, #1
	bne	.L615
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseMPBPicHdr
	cmp	r0, #1
	mov	r6, r0
	beq	.L612
	mov	r0, r7
	ldr	r1, .L639+12
	bl	dprint_vfmw
	b	.L612
.L609:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPPPicHdr
	mov	r6, r0
.L612:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #324]
	rsb	r0, r3, r0
	str	r0, [r4, #324]
	mov	r0, r5
	ldr	r4, [r8, #3680]
	bl	BsPos
	mov	r4, r4, asl #3
	rsb	r0, r0, r4
	cmp	r0, #0
	ble	.L638
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L607:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPIPicHdr
	mov	r6, r0
	b	.L612
.L635:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #250]
	b	.L601
.L638:
	ldr	r1, .L639+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L636:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPIPicHdr
	cmp	r0, #1
	mov	r6, r0
	beq	.L612
	mov	r0, r7
	ldr	r1, .L639+20
	bl	dprint_vfmw
	b	.L612
.L640:
	.align	2
.L639:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC49
	.word	.LC50
	.word	.LC51
	.word	.LC53
	.word	.LC52
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
	ldr	r3, .L658
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
	beq	.L655
	ldrh	r2, [r4, #172]
	ldrh	r3, [r4, #174]
	strh	r2, [r4, #176]	@ movhi
	strh	r3, [r4, #178]	@ movhi
.L648:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #39]
	cmp	r0, #1
	beq	.L649
.L651:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #184]
	mov	r2, #1
	rsb	r0, r3, r0
	str	r0, [r4, #184]
.L650:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L649:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #40]
	cmp	r0, #31
	movhi	r2, #0
	bhi	.L650
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
	ble	.L651
	add	r7, r4, #42
	mov	r6, #0
.L652:
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
	bgt	.L652
	b	.L651
.L655:
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
	beq	.L656
.L644:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #31]
	cmp	r1, #1
	beq	.L657
.L646:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #35]
	cmp	r0, #1
	bne	.L648
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
	b	.L648
.L657:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #32]
	cmp	r0, #0
	bne	.L647
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #4
	strb	r0, [r4, #33]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #34]
	b	.L646
.L656:
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #28]
	cmp	r0, #15
	bne	.L644
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #29]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #30]
	b	.L644
.L647:
	mov	r1, #16
	mov	r0, r5
	bl	BsGet
	strh	r0, [r4, #180]	@ movhi
	b	.L646
.L659:
	.align	2
.L658:
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
	ldr	r3, .L685
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
	beq	.L661
.L664:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #199]
	cmp	r0, #1
	ldrneh	r2, [r4, #240]
	beq	.L681
.L666:
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
	beq	.L682
.L669:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #201]
	cmp	r0, #1
	beq	.L683
.L670:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #203]
	cmp	r0, #1
	beq	.L684
.L671:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #244]
	rsb	r3, r3, r0
	mov	r0, #1
	str	r3, [r4, #244]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L661:
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, #0
	ble	.L664
	add	r7, r4, #204
	mov	r6, #0
.L665:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, r6
	bgt	.L665
	b	.L664
.L684:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #204]
	b	.L671
.L681:
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
	b	.L666
.L682:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #200]
	b	.L669
.L683:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #202]
	b	.L670
.L686:
	.align	2
.L685:
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
	ble	.L690
	mov	r1, #2
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L690:
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
	ble	.L692
	cmp	r0, #11
	movle	r1, #2
	movle	r5, r1
	bgt	.L697
.L692:
	mov	r0, r4
	bl	BsSkip
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L697:
	cmp	r0, #13
	movle	r1, #3
	movle	r5, #0
	ble	.L692
	cmp	r0, #14
	mov	r1, #4
	movne	r5, #5
	moveq	r5, r1
	b	.L692
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
	beq	.L714
.L699:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	bne	.L700
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L715
.L700:
	mov	r1, #5
	mov	r0, r6
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #358]
	cmp	r5, #0
	beq	.L709
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L719
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
	bls	.L716
.L705:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L717
.L707:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L718
.L708:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r6
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L709
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
	beq	.L702
	mov	r0, r6
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	bl	VC1_VopDQuant
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L709:
	mov	r0, #0
.L702:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L716:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L705
.L715:
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #357]
	b	.L700
.L714:
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #356]
	b	.L699
.L717:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L707
.L718:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L708
.L720:
	.align	2
.L719:
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
	beq	.L722
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L722
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L759
.L724:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #358]
	cmp	r6, #0
	beq	.L739
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L772
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
	bls	.L760
.L729:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L761
.L731:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L762
.L732:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L763
.L733:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	beq	.L764
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #373]
	beq	.L765
.L737:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #374]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #468]
	beq	.L766
.L738:
	mov	r3, #0
	strb	r3, [r4, #382]
.L735:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L739
	ldr	r1, [r4, #392]
	cmp	r1, #2
	beq	.L767
.L740:
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
	beq	.L768
.L743:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L769
.L745:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L770
.L747:
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
.L739:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L722:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	strb	r0, [r4, #356]
	bne	.L724
.L759:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	bne	.L724
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #357]
	b	.L724
.L764:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #362]
	cmp	r0, #4
	bne	.L735
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
	b	.L735
.L760:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L729
.L769:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L745
.L763:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L733
.L761:
	mov	r1, r7
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L731
.L762:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L732
.L770:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L747
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L747
.L768:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #374]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #376]
	movne	r0, #0
	beq	.L771
.L744:
	strb	r0, [r4, #377]
	b	.L743
.L767:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #375]
	b	.L740
.L765:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L737
.L766:
	mov	r1, #6
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #364]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #365]
	b	.L738
.L771:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	b	.L744
.L773:
	.align	2
.L772:
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
	beq	.L775
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L775
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L817
.L777:
	cmp	r3, #0
	bne	.L781
	add	r1, r4, #496
	mov	r0, r5
	bl	VC1_DecBfraction
	uxtb	r0, r0
	strb	r0, [r4, #350]
	cmp	r0, #21
	beq	.L779
.L781:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #358]
	cmp	r6, #0
	beq	.L779
	ldrb	r8, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L829
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
	bls	.L818
	cmp	r8, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L819
.L787:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L820
.L788:
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L821
.L789:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L822
.L790:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	beq	.L823
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L824
.L794:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #468]
.L793:
	mov	r1, r7
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L779
	ldr	r1, [r4, #392]
	cmp	r1, #2
	beq	.L825
.L795:
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
	beq	.L826
.L798:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L827
.L799:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L828
.L801:
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
.L779:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L775:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	ldr	r3, [r4, #392]
	cmp	r1, #1
	strb	r0, [r4, #356]
	bne	.L777
.L817:
	cmp	r3, #0
	bne	.L781
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #392]
	strb	r0, [r4, #357]
	b	.L777
.L823:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	moveq	r3, #3
	movne	r3, #1
	strb	r3, [r4, #362]
	b	.L793
.L818:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #198]	@ zero_extendqisi2
	cmp	r8, #1
	movne	r3, #0
	strb	r0, [r4, #351]
	strneb	r3, [r4, #359]
	bne	.L787
.L819:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L787
.L821:
	add	r1, r4, #496
	mov	r0, r5
	bl	VC1_DecBfraction
	strb	r0, [r4, #350]
	b	.L789
.L822:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L790
.L820:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L788
.L827:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L799
.L828:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L801
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L801
.L826:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	strb	r0, [r4, #376]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #377]
	b	.L798
.L825:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #375]
	b	.L795
.L824:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L794
.L830:
	.align	2
.L829:
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
	ble	.L832
	cmp	r0, #11
	movle	r7, #2
	movle	r1, r7
	bgt	.L863
.L832:
	mov	r0, r5
	bl	BsSkip
	strb	r7, [r4, #349]
	ldrb	r3, [r6, #3513]	@ zero_extendqisi2
	strb	r3, [r6, #2]
	ldrb	r3, [r4, #24]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L864
.L833:
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	beq	.L834
	cmp	r3, #0
	beq	.L865
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
	beq	.L866
.L838:
	cmp	r3, #1
	bne	.L840
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	ldrb	r3, [r4, #354]	@ zero_extendqisi2
	cmp	r1, #1
	add	r3, r3, #1
	str	r3, [r4, #492]
	bne	.L849
.L841:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #355]
	cmp	r0, #1
	bne	.L849
	ldr	r3, [r4, #492]
	cmp	r3, #0
	ble	.L849
	mov	r7, r4
	mov	r8, #0
.L850:
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
	bgt	.L850
	b	.L849
.L834:
	mov	r2, #1
	cmp	r3, r2
	strb	r2, [r4, #352]
	beq	.L837
.L840:
	mov	r3, #1
	str	r3, [r4, #492]
.L839:
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L841
.L849:
	ldrb	r3, [r4, #349]	@ zero_extendqisi2
	cmp	r3, #5
	ldrls	pc, [pc, r3, asl #2]
	b	.L842
.L844:
	.word	.L847
	.word	.L845
	.word	.L846
	.word	.L842
	.word	.L847
	.word	.L855
.L847:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvIPicHdr
.L865:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #354]
	bne	.L838
.L866:
	cmp	r3, #1
	beq	.L867
.L837:
	mov	r3, #2
	str	r3, [r4, #492]
	b	.L839
.L863:
	cmp	r0, #13
	movle	r7, #0
	movle	r1, #3
	ble	.L832
	cmp	r0, #14
	moveq	r7, #4
	movne	r7, #5
	movne	r1, #4
	moveq	r1, r7
	b	.L832
.L864:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #396]
	b	.L833
.L855:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L845:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvPPicHdr
.L846:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvBPicHdr
.L842:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L867:
	ldrb	r3, [r4, #353]	@ zero_extendqisi2
	add	r3, r3, #2
	str	r3, [r4, #492]
	b	.L839
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
	bgt	.L869
	mov	r4, r0, asr #3
	mov	r1, #2
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L869:
	cmp	r0, #27
	movle	r4, #3
	bgt	.L875
.L871:
	mov	r0, r5
	mov	r1, r4
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L875:
	cmp	r0, #29
	movgt	r4, #5
	movle	r4, #4
	b	.L871
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
	ldr	lr, .L877
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
.L878:
	.align	2
.L877:
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
	beq	.L888
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L896
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
	bls	.L893
.L884:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L894
.L886:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L895
.L887:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r6
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L888
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
	beq	.L881
	mov	r0, r6
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	bl	VC1_VopDQuant
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L888:
	mov	r0, #0
.L881:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L893:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L884
.L894:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L886
.L895:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L887
.L897:
	.align	2
.L896:
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
	beq	.L899
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L936
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
	bls	.L927
.L902:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L928
.L904:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L929
.L905:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #380]
	cmp	r0, #0
	beq	.L930
.L906:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L931
.L907:
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L932
.L908:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #362]
	cmp	r0, #4
	beq	.L933
.L910:
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
	beq	.L914
	movw	r3, #362
	ldrh	r3, [r4, r3]
	cmp	r3, #4
	beq	.L914
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L934
.L916:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L935
.L918:
	mov	r0, r6
	mov	r5, #1
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #372]
.L899:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L914:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #377]
	beq	.L916
.L934:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_VopDQuant
	b	.L916
.L930:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	clz	r0, r0
	mov	r0, r0, lsr #5
	strb	r0, [r4, #381]
	b	.L906
.L927:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L902
.L931:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L907
.L932:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L908
.L928:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L904
.L935:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L918
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L918
.L929:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L905
.L933:
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
	bne	.L910
	mov	r1, #6
	mov	r0, r6
	bl	BsGet
	mov	r1, #6
	str	r0, [r4, #480]
	mov	r0, r6
	bl	BsGet
	str	r0, [r4, #484]
	b	.L910
.L937:
	.align	2
.L936:
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
	beq	.L949
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L969
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
	bls	.L961
.L943:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L962
.L945:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L963
.L946:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L964
.L947:
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L965
.L948:
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
	beq	.L949
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
	beq	.L966
.L950:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L967
.L951:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L968
.L953:
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
.L949:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L961:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L943
.L967:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L951
.L966:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #377]
	b	.L950
.L963:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L946
.L964:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L947
.L962:
	mov	r1, r7
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L945
.L965:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L948
.L968:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L953
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L953
.L970:
	.align	2
.L969:
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
	beq	.L972
	add	r3, r1, #20480
	ldr	r3, [r3, #3652]
	cmp	r3, #0
	bne	.L972
	ldr	r3, [r2, #504]
	strb	r3, [r2, #349]
	ldrb	r3, [r1, #3513]	@ zero_extendqisi2
	strb	r3, [r1, #2]
.L990:
	ldrb	r3, [r4, #349]	@ zero_extendqisi2
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L999
.L994:
	.word	.L993
	.word	.L995
	.word	.L996
	.word	.L999
	.word	.L993
.L972:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	ldr	r3, .L1018
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
	bne	.L1011
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	bne	.L1012
.L977:
	mov	r2, #1
	cmp	r3, r2
	strb	r2, [r4, #352]
	beq	.L980
.L983:
	mov	r3, #1
	str	r3, [r4, #492]
.L982:
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L984
.L987:
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
	beq	.L1013
.L986:
	ldr	r3, [r4, #472]
	cmp	r3, #3
	ble	.L990
.L991:
	add	r1, r4, #496
	mov	r0, r6
	bl	VC1_DecBfraction
	strb	r0, [r4, #350]
	b	.L990
.L1012:
	cmp	r3, #0
	beq	.L1014
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #352]
	mov	r0, r6
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #353]
	beq	.L1015
.L981:
	cmp	r3, #1
	bne	.L983
	ldrb	r3, [r4, #354]	@ zero_extendqisi2
	add	r3, r3, #1
	str	r3, [r4, #492]
	b	.L982
.L996:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvBFieldHdr
.L992:
	ldrb	r3, [r4, #352]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	bne	.L1016
.L997:
	subs	r3, r3, #1
	movne	r3, #1
	strb	r3, [r4, #389]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L995:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvPFieldHdr
	ldrb	r3, [r4, #352]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	beq	.L997
.L1016:
	adds	r3, r3, #0
	movne	r3, #1
	strb	r3, [r4, #389]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L993:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvIFieldHdr
	b	.L992
.L1011:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	str	r0, [r4, #396]
	beq	.L977
	b	.L1012
.L1014:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #354]
	bne	.L981
.L1015:
	cmp	r3, #1
	beq	.L1017
.L980:
	mov	r3, #2
	str	r3, [r4, #492]
	b	.L982
.L999:
	mov	r0, #0
	b	.L992
.L1013:
	ldr	r3, [r4, #472]
	cmp	r3, #3
	bgt	.L991
	mov	r0, r6
	bl	VC1_DecRefdist
	strb	r0, [r4, #379]
	b	.L986
.L984:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #355]
	cmp	r0, #1
	bne	.L987
	ldr	r3, [r4, #492]
	cmp	r3, #0
	ble	.L987
	mov	r7, r4
	mov	r8, #0
.L988:
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
	bgt	.L988
	b	.L987
.L1017:
	ldrb	r3, [r4, #353]	@ zero_extendqisi2
	add	r3, r3, #2
	str	r3, [r4, #492]
	b	.L982
.L1019:
	.align	2
.L1018:
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
	beq	.L1021
	add	r3, r4, #20480
	ldr	r3, [r3, #3652]
	cmp	r3, #0
	beq	.L1030
.L1021:
	ldrb	r8, [r5, #23]	@ zero_extendqisi2
	cmp	r8, #1
	movne	r3, #0
	movne	r0, r3
	beq	.L1031
.L1023:
	str	r0, [r5, #392]
.L1022:
	cmp	r3, #0
	mov	r2, r5
	mov	r1, r4
	mov	r0, r6
	beq	.L1032
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvFieldPicHdr
.L1030:
	ldr	r3, [r5, #392]
	bic	r3, r3, #2
	b	.L1022
.L1032:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvFramePicHdr
.L1031:
	mov	r1, #2
	mov	r0, r6
	bl	BsShow
	cmp	r0, #1
	mov	r7, r0
	ble	.L1033
	mov	r1, #2
	mov	r0, r6
	bl	BsSkip
	bic	r3, r7, #2
	mov	r0, r7
	b	.L1023
.L1033:
	mov	r1, r8
	mov	r0, r6
	bl	BsSkip
	mov	r3, #0
	mov	r0, r3
	b	.L1023
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
	ldr	r4, [r3, #3652]
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
	beq	.L1036
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1036:
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
	bgt	.L1040
	b	.L1041
.L1046:
	bl	BsSkip
	cmp	r4, r6
	beq	.L1041
.L1040:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L1046
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1041:
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
	ldr	r6, [r7, #3652]
	movw	r0, #24144
	movw	ip, #24136
	mov	r10, r1
	movw	r1, #24152
	mov	r9, r6, asl #4
	mov	r8, r6, asl #6
	rsb	r4, r9, r8
	add	r4, r5, r4
	strb	r6, [r4, r0]
	add	r0, r4, #24064
	ldr	lr, [r3, #24]
	add	r2, r2, lr, lsr #3
	str	r2, [r4, ip]
	ldr	lr, [r3, #24]
	add	r2, r0, #80
	str	r2, [fp, #-48]
	and	lr, lr, #7
	str	lr, [r4, r1]
	ldr	lr, [r3, #16]
	add	r1, r0, #72
	ldr	r3, [r3, #24]
	str	r1, [fp, #-52]
	rsb	r3, r3, lr, lsl #3
	str	r3, [r0, #92]
	ldr	r0, [r4, ip]
	str	r1, [fp, #-56]
	bl	MEM_Vir2Phy
	ldr	r2, [fp, #-48]
	add	r3, r5, #32768
	movw	lr, #24176
	add	ip, r4, #24064
	add	ip, ip, #112
	str	r0, [r2, #4]
	ldr	r2, [r3, #3688]
	str	r2, [r4, lr]
	ldr	r2, [r3, #3664]
	cmp	r2, #0
	beq	.L1049
	ldr	r0, [r3, #3676]
	ldr	r1, [fp, #-52]
	cmp	r0, #0
	bne	.L1068
.L1049:
	rsb	r3, r9, r8
	movw	lr, #24168
	add	r3, r5, r3
	mov	r2, #0
	add	ip, r3, #24064
	str	r2, [ip, #76]
	str	r2, [r3, lr]
	str	r2, [ip, #108]
	str	r2, [ip, #100]
	str	r2, [ip, #116]
.L1050:
	ldr	ip, [r7, #3572]
	sub	r6, r9, r6, asl #2
	ldr	r0, [r7, #3568]
	ldrb	r4, [r5, #8]	@ zero_extendqisi2
	mul	r0, r0, ip
	cmp	r4, #0
	sub	r0, r0, #1
	beq	.L1051
	add	r10, r10, r6
	add	r3, ip, #1
	rsb	r1, r9, r8
	movw	lr, #24160
	ldr	r2, [r10, #528]
	add	r3, r3, r3, lsr #31
	add	r1, r5, r1
	add	r10, r10, #520
	sub	r3, r2, r3, asr #1
	cmp	r0, r3
	str	r3, [r1, lr]
	movcs	r0, #0
	movcc	r0, #1
	cmp	r3, #0
	movle	r0, #0
	cmp	r0, #0
	bne	.L1069
.L1052:
	rsb	r0, r9, r8
	add	r0, r5, r0
	add	r3, r0, #24064
	add	r3, r3, #88
	ldr	r3, [r3, #4]
	cmp	r3, #0
	ble	.L1054
	add	r3, r0, #24064
	add	r3, r3, #72
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1055
	add	r0, r0, #24064
	ldr	r3, [r0, #108]
	cmp	r3, #0
	ble	.L1054
.L1055:
	ldr	r3, [r7, #3652]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r7, #3652]
.L1053:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1051:
	add	r6, r10, r6
	rsb	r2, r9, r8
	add	r2, r5, r2
	movw	r1, #24160
	ldr	r3, [r6, #528]
	add	r6, r6, #520
	cmp	r0, r3
	str	r3, [r2, r1]
	bcs	.L1052
	ldr	r2, [r6, #8]
	ldr	r1, .L1070
	str	r0, [sp]
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1068:
	movw	lr, #24168
	str	r2, [r1, #4]
	mov	r2, #0
	str	r2, [r4, lr]
	ldr	r1, [r3, #3684]
	add	r2, r4, #24064
	str	r0, [r2, #100]
	mov	r1, r1, asl #3
	str	r1, [r2, #108]
	ldr	r3, [r3, #3692]
	str	r3, [ip, #4]
	b	.L1050
.L1069:
	ldr	r2, [r10, #8]
	mov	r0, #1
	str	ip, [sp]
	ldr	r1, .L1070+4
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1053
.L1054:
	ldr	r1, .L1070+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1071:
	.align	2
.L1070:
	.word	.LC55
	.word	.LC54
	.word	.LC56
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
	beq	.L1073
	adds	r3, r2, #15
	add	r0, r0, #20480
	addmi	r3, r2, #30
	movw	r1, #2404
	mov	r3, r3, asr #4
	str	r3, [r0, #3568]
	ldrh	r3, [r4, #238]
	str	r3, [r0, #3584]
	ldrh	r2, [r4, #240]
	ldrh	r3, [r5, r1]
	cmp	r3, r2
	beq	.L1074
.L1075:
	adds	r3, r2, #15
	addmi	r3, r2, #30
	mov	r3, r3, asr #4
	str	r3, [r0, #3572]
	ldrh	r3, [r4, #240]
	str	r3, [r0, #3588]
.L1074:
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
.L1078:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1073:
	movw	r3, #2404
	ldrh	r2, [r1, #240]
	ldrh	r3, [r5, r3]
	cmp	r3, r2
	addne	r0, r0, #20480
	bne	.L1075
	mov	r4, #0
	b	.L1078
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
	subs	r3, r0, #0
	beq	.L1087
	ldrb	r2, [r3, #3096]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1085
	add	r1, r3, #8192
	ldrb	r2, [r1, #2415]	@ zero_extendqisi2
	tst	r2, #251
	moveq	r2, #1
	moveq	r0, r2
	bne	.L1088
.L1083:
	strb	r0, [r3, #10]
	mov	r0, #1
	strb	r2, [r1, #2434]
	ldmfd	sp, {fp, sp, pc}
.L1088:
	cmp	r2, #1
	ldreqsb	r2, [r3, #10]
	ldrneb	r0, [r3, #10]	@ zero_extendqisi2
	clzeq	r2, r2
	moveq	r2, r2, lsr #5
	uxtbne	r2, r0
	uxtbeq	r0, r2
	b	.L1083
.L1085:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1087:
	ldr	r3, .L1089
	movw	r2, #5809
	ldr	r1, .L1089+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1090:
	.align	2
.L1089:
	.word	.LC57
	.word	.LC24
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
	ldr	r1, .L1094
	sub	r0, fp, #148
	bl	memcpy
	cmp	r5, #0
	subeq	r3, fp, #20
	movne	r0, r4
	addeq	r4, r3, r4, lsl #2
	ldreq	r0, [r4, #-128]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1095:
	.align	2
.L1094:
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
	beq	.L1097
	mov	r0, r5
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
.L1097:
	ldr	r3, .L1101
	mov	r0, r4
	mov	r2, #36
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L1102:
	.align	2
.L1101:
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
	subs	r4, r0, #0
	mov	r6, r1
	beq	.L1120
	cmp	r1, #32
	bhi	.L1121
	ldrb	r3, [r4, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1106
	add	r7, r4, #20480
	ldr	r3, [r7, #3652]
	cmp	r3, #0
	beq	.L1122
	add	r4, r4, #24064
	mov	r5, #0
	add	r4, r4, #112
	b	.L1110
.L1109:
	ldr	r3, [r7, #3652]
	add	r4, r4, #48
	cmp	r5, r3
	bcs	.L1123
.L1110:
	ldr	r1, [r4]
	mov	r0, r6
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #-36]
	add	r5, r5, #1
	cmp	r3, #0
	beq	.L1109
	ldr	r3, [r4, #-12]
	cmp	r3, #0
	beq	.L1109
	ldr	r1, [r4, #4]
	mov	r0, r6
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r7, #3652]
	add	r4, r4, #48
	cmp	r5, r3
	bcc	.L1110
.L1123:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1121:
	ldr	r1, .L1124
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1106:
	add	r1, r4, #36352
	mov	r0, r6
	add	r1, r1, #76
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1_ClearCurPacket
.L1122:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1120:
	ldr	r1, .L1124+4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1125:
	.align	2
.L1124:
	.word	.LC59
	.word	.LC58
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
	subs	r5, r0, #0
	mov	r9, r1
	beq	.L1160
	ldr	r3, [r5, #4]
	add	r4, r5, #49152
	add	r6, r5, #32768
	add	r0, r5, #12736
	add	r2, r3, #12288
	ldr	r1, [r4, #520]
	ldrb	r3, [r3, #71]	@ zero_extendqisi2
	strb	r3, [r4, #129]
	ldr	r3, [r2, #260]
	str	r3, [r4, #132]
	bl	VC1_ClearCurPic
	ldr	r1, [r6, #4092]
	ldr	r0, [r4, #520]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r6, #4088]
	mov	r8, r0
	ldr	r0, [r4, #520]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r6, #4084]
	mov	r7, r0
	ldr	r0, [r4, #520]
	bl	FSP_GetFsImagePtr
	cmp	r8, #0
	beq	.L1161
	cmp	r9, #0
	movlt	r3, #0
	blt	.L1130
	cmp	r9, #100
	movlt	r3, r9
	movge	r3, #100
.L1130:
	add	r9, r5, #12288
	str	r3, [r8, #152]
	mov	r0, r5
	bl	VC1_SetImgFormat
	ldrb	r3, [r9, #451]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L1162
.L1131:
	add	r3, r8, #560
	add	r2, r8, #544
	mov	r0, #0
	mov	r1, #0
	strd	r0, [r2]
	strd	r0, [r3, #-8]
	ldr	r3, [r5]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L1163
	ldr	ip, [r6, #4092]
	add	r10, r5, #36864
	mov	r7, #0
	str	ip, [r10]
.L1135:
	ldr	r3, [r4, #8]
	cmn	ip, #1
	add	r3, r3, #1
	str	r3, [r4, #8]
	beq	.L1136
	mov	r1, ip
	ldr	r0, [r4, #520]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L1164
	ldr	r2, [r8, #152]
	cmp	r2, #0
	beq	.L1138
	ldr	r3, [r5]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	bhi	.L1139
.L1138:
	ldr	r2, [r10]
	ldr	r0, [r4, #520]
	mov	r1, r2
	str	r2, [fp, #-48]
	bl	FSP_GetRef
	ldr	r2, [fp, #-48]
	ldr	r1, .L1168
	mov	r3, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r10]
	ldr	r0, [r4, #520]
	bl	FSP_SetDisplay
	cmp	r7, #1
	ldreq	r3, [r6, #4008]
	movne	r1, #1
	ldrne	r2, [r6, #4000]
	movne	r3, #2
	strneb	r1, [r2, #1]
	mov	r2, r5
	streqb	r7, [r3, #1]
	mov	r1, #1
	strneb	r3, [r9, #449]
	add	r3, r5, #49152
	streqb	r7, [r9, #449]
	add	r3, r3, #168
	ldr	r0, [r4, #520]
	str	r8, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L1142
	ldr	r1, [r8, #544]
	add	r3, r8, #544
	ldr	r0, [r4, #520]
	add	r5, r8, #560
	str	r3, [fp, #-48]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-48]
	mov	r8, #0
	mov	r9, #0
	strd	r8, [r3]
	ldr	r1, [r5, #-8]
	ldr	r0, [r4, #520]
	bl	FreeUsdByDec
	mov	r2, #0
	strd	r8, [r5, #-8]
	ldr	r0, [r4, #520]
	ldr	r1, [r10]
	bl	FSP_SetDisplay
	cmp	r7, #1
	mov	r3, #0
	ldreq	r2, [r6, #4008]
	mov	r0, r3
	ldrne	r2, [r6, #4000]
	strb	r3, [r2, #1]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1163:
	ldrb	lr, [r9, #450]	@ zero_extendqisi2
	sub	lr, lr, #2
	ands	lr, lr, #253
	bne	.L1165
	ldr	ip, [r6, #4092]
	add	r10, r5, #36864
	cmp	r7, #0
	str	ip, [r10]
	beq	.L1135
	add	r3, r7, #592
	add	r8, r8, #592
	str	r3, [fp, #-48]
	ldrd	r0, [r3, #-8]
	ldrd	r2, [r8, #-8]
	cmp	r0, r2
	sbcs	r7, r1, r3
	movge	r7, lr
	bge	.L1135
	strd	r0, [r8, #-8]
	mov	r7, lr
	ldr	r1, [fp, #-48]
	strd	r2, [r1, #-8]
	ldr	ip, [r10]
	b	.L1135
.L1166:
	ldr	r2, [r6, #4004]
	mov	r3, #0
	strb	r3, [r2, #1]
	strb	r3, [r9, #449]
.L1136:
	mov	r0, #1
.L1128:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1160:
	ldr	r3, .L1168+4
	movw	r2, #502
	ldr	r1, .L1168+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1165:
	ldr	r7, [r6, #4080]
	add	r10, r5, #36864
	cmp	r7, #1
	ldrhi	ip, [r6, #4084]
	mvnls	ip, #0
	cmp	r7, #1
	str	ip, [r10]
	movls	r7, #0
	movhi	r7, #1
	b	.L1135
.L1142:
	ldrb	r3, [r9, #449]	@ zero_extendqisi2
	sxtb	r3, r3
	cmp	r3, #3
	beq	.L1166
	cmp	r3, #1
	beq	.L1167
	cmp	r3, #2
	bne	.L1136
	ldr	r2, [r6, #4000]
	mov	r3, #0
	strb	r3, [r2, #1]
	strb	r3, [r9, #449]
	b	.L1128
.L1139:
	ldr	r1, .L1168+12
	mov	r0, #1
	add	ip, r8, #544
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	r1, [r8, #544]
	ldr	r0, [r4, #520]
	add	r5, r8, #560
	bl	FreeUsdByDec
	ldr	ip, [fp, #-48]
	mov	r8, #0
	mov	r9, #0
	strd	r8, [ip]
	ldr	r1, [r5, #-8]
	ldr	r0, [r4, #520]
	bl	FreeUsdByDec
	strd	r8, [r5, #-8]
	mov	r2, #0
	ldr	r0, [r4, #520]
	ldr	r1, [r10]
	bl	FSP_SetDisplay
	cmp	r7, #1
	mov	r2, #0
	ldreq	r3, [r6, #4008]
	moveq	r0, r7
	ldrne	r3, [r6, #4000]
	movne	r0, #1
	strb	r2, [r3, #1]
	b	.L1128
.L1162:
	ldrb	r3, [r9, #457]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1136
	b	.L1131
.L1167:
	ldr	r2, [r6, #4008]
	mov	r0, r3
	mov	r3, #0
	strb	r3, [r2, #1]
	strb	r3, [r9, #449]
	b	.L1128
.L1161:
	str	r0, [sp]
	mov	r3, r7
	mov	r2, r8
	ldr	r1, .L1168+16
	mov	r0, r8
	bl	dprint_vfmw
	mov	r0, r8
	b	.L1128
.L1164:
	mov	r2, #584
	ldr	r1, .L1168+20
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r8
	b	.L1128
.L1169:
	.align	2
.L1168:
	.word	.LC62
	.word	.LC23
	.word	.LC24
	.word	.LC63
	.word	.LC60
	.word	.LC61
	UNWIND(.fnend)
	.size	VC1DEC_VDMPostProc, .-VC1DEC_VDMPostProc
	.align	2
	.global	VC1_Vfmw_DecodeArbiter
	.type	VC1_Vfmw_DecodeArbiter, %function
VC1_Vfmw_DecodeArbiter:
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
	subs	r4, r0, #0
	beq	.L1222
	add	r5, r4, #12288
	ldrb	r3, [r5, #448]	@ zero_extendqisi2
	tst	r3, #16
	beq	.L1221
	add	r6, r4, #49152
	bic	r3, r3, #20
	strb	r3, [r5, #448]
	ldr	r3, [r6, #124]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r3, [r4]
	bls	.L1174
	add	r2, r4, #32768
	ldr	r1, [r2, #4080]
	ldr	r2, [r3, #8]
.L1175:
	sub	r3, r2, #1
	str	r2, [r6, #124]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L1201
.L1183:
	.word	.L1182
	.word	.L1184
	.word	.L1200
	.word	.L1186
.L1206:
	mov	r1, #0
.L1186:
	ldrb	r3, [r5, #450]	@ zero_extendqisi2
	cmp	r3, #0
	streq	r3, [r6, #56]
	moveq	r3, #1
	beq	.L1185
	cmp	r3, #2
	bne	.L1188
	ldr	r3, [r6, #56]
	adds	r3, r3, #0
	movne	r3, #1
	cmp	r1, #0
	bne	.L1190
.L1189:
	ldr	r1, .L1224
	mov	r0, #1
	bl	dprint_vfmw
.L1198:
	add	r0, r4, #12736
	ldr	r1, [r6, #520]
	bl	VC1_ClearCurPic
	ldr	r3, .L1224+4
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1221
	mov	r3, #0
	ldr	r0, [r6, #520]
	mov	r2, r3
	mov	r1, #113
	blx	r4
.L1221:
	mov	r0, #0
.L1219:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1174:
	ldr	r2, [r3, #8]
	cmp	r2, #4
	cmpne	r2, #1
	bls	.L1176
	add	r3, r4, #32768
	ldr	r1, [r3, #4080]
	b	.L1175
.L1200:
	mov	r3, #0
.L1185:
	cmp	r1, #0
	beq	.L1191
.L1190:
	cmp	r1, #1
	bls	.L1223
.L1194:
	cmp	r3, #0
	beq	.L1198
	ldrb	r3, [r5, #3544]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1197
	add	r3, r5, #3600
	add	ip, r4, #23040
	add	r3, r3, #12
	add	ip, ip, #52
	ldmia	r3, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	add	r1, r5, #3856
	add	r0, r4, #23296
	add	r1, r1, #4
	mov	r2, #100
	add	r0, r0, #44
	bl	memcpy
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1204:
	mov	r1, #0
.L1184:
	ldrb	r3, [r5, #450]	@ zero_extendqisi2
	cmp	r1, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	bne	.L1190
.L1191:
	ldrb	r2, [r5, #450]	@ zero_extendqisi2
	sub	r0, r2, #4
	sub	r1, r2, #1
	cmp	r1, #1
	cmphi	r0, #1
	bls	.L1189
.L1192:
	sub	r2, r2, #2
	tst	r2, #253
	bne	.L1194
	ldr	r1, .L1224+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1198
.L1203:
	mov	r1, #0
.L1182:
	ldrb	r3, [r5, #450]	@ zero_extendqisi2
	sub	r3, r3, #2
	tst	r3, #253
	movne	r3, #1
	moveq	r3, #0
	b	.L1185
.L1197:
	add	r1, r5, #3616
	add	r0, r4, #23040
	add	r1, r1, #12
	mov	r2, #172
	add	r0, r0, #68
	add	r6, r4, #20480
	bl	memcpy
	add	ip, r5, #3792
	add	ip, ip, #8
	add	lr, r6, #2800
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2}
	stmia	lr, {r0, r1, r2}
	add	r1, r5, #3952
	add	r0, r6, #2960
	add	r1, r1, #8
	mov	r2, #176
	bl	memcpy
	ldr	ip, [r5, #4004]
	add	r3, r4, #36864
	ldr	r2, .L1224+12
	add	r1, r4, #16384
	add	r0, r4, #23552
	strb	ip, [r5, #452]
	add	r1, r1, #40
	ldr	r3, [r3, #4]
	add	r0, r0, #64
	ldr	r4, [r2, #52]
	mov	r2, r3, asl #4
	sub	r2, r2, r3, asl #2
	blx	r4
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1202:
	mov	r1, #0
.L1201:
	mov	r3, #1
	b	.L1185
.L1188:
	and	r3, r3, #251
	cmp	r3, #1
	bne	.L1201
	str	r3, [r6, #56]
	b	.L1185
.L1176:
	add	r7, r4, #32768
	ldr	r1, .L1224+16
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r1, [r7, #4088]
	ldr	r0, [r6, #520]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L1177
	ldr	r1, [r8, #544]
	add	r9, r8, #560
	ldr	r0, [r6, #520]
	add	r10, r8, #576
	bl	FreeUsdByDec
	ldr	r1, [r8, #552]
	ldr	r0, [r6, #520]
	add	r3, r8, #544
	str	r3, [fp, #-48]
	bl	FreeUsdByDec
	ldr	r1, [r8, #560]
	ldr	r0, [r6, #520]
	bl	FreeUsdByDec
	ldr	r1, [r8, #568]
	ldr	r0, [r6, #520]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-48]
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r3]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r10, #-8]
	ldr	r1, [r7, #4088]
	ldr	r0, [r6, #520]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r7, #4084]
	ldr	r0, [r6, #520]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	str	r3, [r7, #4084]
	str	r3, [r7, #4088]
	ldr	r0, [r6, #520]
	bl	FSP_GetNullLogicFs
	str	r0, [r7, #4088]
	str	r0, [r7, #4084]
.L1177:
	ldr	r2, [r7, #4004]
	mov	r3, #0
	str	r3, [r7, #4080]
	cmp	r2, r3
	beq	.L1220
	ldr	r1, [r7, #4008]
	cmp	r1, #0
	beq	.L1220
	strb	r3, [r2, #1]
	ldr	r2, [r7, #4008]
	strb	r3, [r2, #1]
	ldr	r2, [r7, #4004]
	strb	r3, [r2]
	ldr	r2, [r7, #4008]
	strb	r3, [r2]
	ldr	r3, [r4]
	ldr	r1, [r7, #4080]
	ldr	r2, [r3, #8]
	b	.L1175
.L1220:
	ldr	r3, [r4]
	ldr	r2, [r3, #8]
	sub	r3, r2, #1
	str	r2, [r6, #124]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L1202
.L1199:
	.word	.L1203
	.word	.L1204
	.word	.L1205
	.word	.L1206
.L1205:
	mov	r3, #0
	b	.L1191
.L1222:
	ldr	r3, .L1224+20
	movw	r2, #2259
	ldr	r1, .L1224+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1219
.L1223:
	ldrb	r2, [r5, #450]	@ zero_extendqisi2
	b	.L1192
.L1225:
	.align	2
.L1224:
	.word	.LC65
	.word	g_event_report
	.word	.LC66
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC64
	.word	.LC43
	.word	.LC24
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
	subs	r4, r0, #0
	beq	.L1245
	ldr	r3, [r4]
	add	r5, r4, #12288
	add	r6, r4, #12736
	add	r7, r4, #8
	ldrb	r1, [r5, #3544]	@ zero_extendqisi2
	ldr	r2, [r3, #600]
	cmp	r1, #1
	str	r2, [r5, #268]
	ldr	r3, [r3, #652]
	str	r3, [r5, #272]
	beq	.L1229
	mov	r0, r6
	bl	VC1_Vfmw_UpdataLastPicRNDCTRL
.L1229:
	mov	r1, r7
	mov	r0, r4
	bl	VC1_WritePicMsg
	add	r3, r4, #36864
	ldr	r2, .L1250
	add	r1, r6, #24064
	ldr	r3, [r3, #4]
	add	r1, r1, #72
	add	r0, r4, #92
	ldr	r8, [r2, #52]
	mov	r2, r3, asl #6
	strb	r3, [r4, #78]
	sub	r2, r2, r3, asl #4
	blx	r8
	mov	r1, r7
	mov	r0, r6
	bl	VC1_CfgVDH
	ldrb	r3, [r5, #450]	@ zero_extendqisi2
	cmp	r3, #1
	ldrlsb	r2, [r5, #452]	@ zero_extendqisi2
	strlsb	r2, [r5, #453]
	cmp	r3, #5
	beq	.L1246
	mov	r3, #0
	strb	r3, [r4, #9]
	ldrb	r3, [r5, #452]	@ zero_extendqisi2
	ldrb	r2, [r5, #456]	@ zero_extendqisi2
.L1232:
	strb	r3, [r4, #8]
	strb	r3, [r5, #451]
	strb	r2, [r5, #457]
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1247
	and	r2, r3, #251
	cmp	r2, #1
	addeq	r1, r4, #49152
	streq	r2, [r1, #56]
.L1234:
	ldr	r2, [r4]
	str	r7, [r4, #4]
	ldr	r0, [r2, #912]
	cmp	r0, #1
	beq	.L1248
	cmp	r0, #2
	beq	.L1249
.L1238:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1249:
	ldr	r2, [r2, #916]
	cmp	r7, #0
	cmpne	r2, #0
	ble	.L1238
	sub	r3, r3, #2
	ands	r5, r3, #253
	bne	.L1238
	add	r3, r4, #32768
	add	r1, r4, #49152
	mov	r0, r6
	ldr	r3, [r3, #4000]
	strb	r5, [r3, #1]
	ldr	r2, [r4]
	ldr	r3, [r2, #916]
	sub	r3, r3, #1
	str	r3, [r2, #916]
	ldr	r1, [r1, #520]
	bl	VC1_ClearCurPic
	str	r5, [r4, #4]
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1247:
	add	r8, r4, #49152
	ldr	r5, [r8, #56]
	cmp	r5, #0
	bne	.L1234
	mov	r0, r6
	ldr	r1, [r8, #520]
	bl	VC1_ClearCurPic
	add	r3, r4, #32768
	mov	r0, r5
	ldr	r3, [r3, #4000]
	strb	r5, [r3]
	ldr	r3, [r8, #60]
	add	r3, r3, #1
	str	r3, [r8, #60]
	str	r5, [r4, #4]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1246:
	mov	r2, #1
	strb	r2, [r4, #9]
	ldrb	r3, [r5, #453]	@ zero_extendqisi2
	add	r1, r4, #49152
	strb	r2, [r5, #456]
	strb	r3, [r5, #452]
	ldr	r1, [r1, #80]
	sub	r1, r1, #1
	str	r1, [r5, #172]
	b	.L1232
.L1248:
	cmp	r7, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	sub	r3, r3, #2
	ands	r5, r3, #253
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r2, r4, #32768
	add	r3, r4, #49152
	mov	r0, r6
	ldr	r2, [r2, #4000]
	strb	r5, [r2, #1]
	ldr	r1, [r3, #520]
	bl	VC1_ClearCurPic
	str	r5, [r4, #4]
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1245:
	ldr	r3, .L1250+4
	movw	r2, #2404
	ldr	r1, .L1250+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1251:
	.align	2
.L1250:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC43
	.word	.LC24
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
	ldr	r5, [r0, #3128]
	add	r8, r0, #32768
	mov	r4, r0
	str	r1, [fp, #-52]
	mov	r10, #0
	mov	r1, #32
	strb	r10, [r0, #6]
	mov	r0, r5
	str	r2, [fp, #-48]
	bl	BsGet
	ldr	r3, [r5, #24]
	ldr	r6, [r8, #3660]
	add	r7, r4, #36352
	ldr	r2, [r8, #3680]
	add	r7, r7, #76
	mov	r3, r3, lsr #3
	add	r6, r6, r3
	rsb	r2, r3, r2
	mov	r1, r6
	uxtb	r9, r0
	mov	r0, r5
	bl	BsInit
	sub	r2, r9, #10
	cmp	r2, #5
	bhi	.L1253
	cmp	r9, #11
	ldrb	r3, [r4]	@ zero_extendqisi2
	beq	.L1321
	and	r1, r3, #7
	cmp	r1, #7
	beq	.L1322
	add	r9, r4, #20480
	strb	r10, [r4, #8]
	str	r10, [r9, #3652]
	cmp	r2, #5
	ldrls	pc, [pc, r2, asl #2]
	b	.L1285
.L1269:
	.word	.L1268
	.word	.L1285
	.word	.L1270
	.word	.L1286
	.word	.L1272
	.word	.L1273
.L1253:
	sub	r2, r9, #27
	cmp	r2, #4
	bls	.L1323
	cmp	r9, #254
	beq	.L1324
.L1285:
	ldr	r0, [fp, #-48]
	mov	r1, r7
	bl	VC1_ClearCurPacket
	mov	r0, #0
.L1258:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1323:
	ldr	r0, [fp, #-48]
	mov	r1, r7
	bl	VC1_ClearCurPacket
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1321:
	and	r3, r3, #7
	cmp	r3, #7
	beq	.L1325
.L1283:
	ldr	r0, [fp, #-48]
	mov	r1, r7
	bl	VC1_ClearCurPacket
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1286:
	ldr	r10, .L1330
.L1315:
	ldr	r0, [fp, #-52]
	mov	r2, #176
	mov	r1, #0
	add	r0, r0, #348
	ldrb	r3, [r0, #31]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	ldr	r3, [r10, #48]
	blx	r3
	ldr	r0, [fp, #-52]
	ldrb	r3, [fp, #-56]	@ zero_extendqisi2
	strb	r3, [r0, #379]
.L1274:
	add	r0, r4, #24064
	ldr	r3, [r10, #48]
	mov	r2, #12288
	mov	r1, #0
	add	r0, r0, #72
	blx	r3
	mov	r0, r5
	bl	BsPos
	ldr	r3, [fp, #-52]
	mov	r1, r4
	mov	r2, r3
	str	r0, [r3, #488]
	mov	r0, r5
	bl	VC1_Vfmw_ParseAdvPicHdr
	cmp	r0, #1
	mov	r10, r0
	beq	.L1326
	mov	r1, r7
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	movw	r2, #5701
	ldr	r1, .L1330+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1258
.L1324:
	mov	r1, #32
	mov	r0, r5
	bl	BsGet
	mov	r1, #32
	mov	r6, r0
	mov	r0, r5
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r6, r3
	bne	.L1285
	add	r3, r4, #20480
	mov	r2, #1
	strb	r2, [r4, #7]
	ldr	r3, [r3, #3652]
	cmp	r3, #0
	moveq	r0, r2
	beq	.L1258
	ldrb	r3, [r4]	@ zero_extendqisi2
	mov	r0, r2
	strb	r2, [r4, #6]
	orr	r3, r3, #16
	strb	r3, [r4]
	b	.L1258
.L1322:
	mov	r10, #1
	orr	r3, r3, #16
	strb	r10, [r4, #6]
	mov	r0, r10
	strb	r3, [r4]
	b	.L1258
.L1270:
	ldr	r10, .L1330
	mov	r3, #1
	strb	r3, [r4, #8]
	mov	r2, #16
	ldr	r3, [fp, #-52]
	mov	r1, #0
	add	r0, r3, #508
	ldr	r3, [r10, #48]
	blx	r3
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1274
	b	.L1315
.L1273:
	ldr	r2, [fp, #-52]
	mov	r0, r5
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvSeqHdr
	cmp	r0, #1
	mov	r10, r0
	ldreqb	r3, [r4]	@ zero_extendqisi2
	orreq	r3, r3, #1
	streqb	r3, [r4]
	b	.L1283
.L1272:
	mov	r0, r5
	ldr	r2, [fp, #-52]
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvEntptHdr
	cmp	r0, #1
	mov	r10, r0
	bne	.L1283
	ldr	r1, [fp, #-52]
	mov	r0, r4
	bl	VC1_Vfmw_UpdateAdvSPS
	ldrb	r3, [r4]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r4]
	b	.L1283
.L1268:
	orr	r3, r3, #32
	ldr	r0, [fp, #-48]
	mov	r1, r7
	strb	r3, [r4]
	bl	VC1_ClearCurPacket
	mov	r0, #1
	b	.L1258
.L1325:
	mov	r0, r5
	ldr	r2, [fp, #-52]
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvSlcHdr
	cmp	r0, #1
	mov	r5, r0
	bne	.L1256
	add	r9, r4, #20480
	ldr	r7, [r9, #3652]
	cmp	r7, #255
	bhi	.L1327
	mov	r3, r7, asl #4
	mov	r2, r7, asl #6
	rsb	r5, r3, r2
	str	r3, [fp, #-48]
	ldr	r3, [r4, #3128]
	add	r5, r4, r5
	str	r2, [fp, #-56]
	movw	r2, #24144
	strb	r7, [r5, r2]
	movw	ip, #24136
	ldr	r1, [r3, #24]
	movw	r0, #24152
	add	r2, r5, #24064
	add	r1, r6, r1, lsr #3
	str	r1, [r5, ip]
	ldr	r1, [r3, #24]
	mov	r6, r2
	and	r1, r1, #7
	str	r1, [r5, r0]
	ldr	r1, [r3, #16]
	ldr	r0, [r3, #24]
	add	r3, r2, #72
	str	r3, [fp, #-60]
	rsb	r1, r0, r1, lsl #3
	str	r1, [r2, #92]
	ldr	r0, [r5, ip]
	str	r3, [fp, #-64]
	bl	MEM_Vir2Phy
	movw	r1, #24176
	add	r2, r6, #112
	str	r0, [r6, #84]
	ldr	r0, [r8, #3688]
	str	r0, [r5, r1]
	ldr	r1, [r8, #3664]
	cmp	r1, #0
	beq	.L1259
	ldr	r0, [r8, #3676]
	ldr	r3, [fp, #-60]
	cmp	r0, #0
	beq	.L1259
	movw	ip, #24168
	str	r1, [r3, #4]
	str	r10, [r5, ip]
	add	r3, r5, #24064
	ldr	r1, [r8, #3684]
	str	r0, [r3, #100]
	mov	r1, r1, asl #3
	str	r1, [r3, #108]
	ldr	r3, [r8, #3692]
	str	r3, [r2, #4]
.L1260:
	ldr	r0, [r9, #3572]
	ldr	r1, [r9, #3568]
	ldrb	r10, [r4, #8]	@ zero_extendqisi2
	mul	r1, r1, r0
	cmp	r10, #0
	sub	r1, r1, #1
	beq	.L1261
	ldr	r2, [fp, #-48]
	add	r3, r0, #1
	ldr	lr, [fp, #-52]
	movw	r5, #24160
	sub	ip, r2, r7, asl #2
	add	r3, r3, r3, lsr #31
	add	ip, lr, ip
	ldr	lr, [fp, #-56]
	add	ip, ip, #520
	rsb	lr, r2, lr
	ldr	r2, [ip, #8]
	add	lr, r4, lr
	sub	r3, r2, r3, asr #1
	cmp	r1, r3
	str	r3, [lr, r5]
	movcs	r1, #0
	movcc	r1, #1
	cmp	r3, #0
	movle	r1, #0
	cmp	r1, #0
	bne	.L1328
.L1262:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-48]
	rsb	r3, r2, r3
	add	r4, r4, r3
.L1320:
	add	r3, r4, #24064
	add	r3, r3, #88
	ldr	r3, [r3, #4]
	cmp	r3, #0
	ble	.L1265
	add	r3, r4, #24064
	add	r3, r3, #72
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1281
	add	r4, r4, #24064
	ldr	r3, [r4, #108]
	cmp	r3, #0
	ble	.L1265
.L1281:
	ldr	r3, [r9, #3652]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r9, #3652]
	b	.L1258
.L1326:
	mov	r0, r5
	bl	BsPos
	ldr	r2, [fp, #-52]
	ldr	r3, [r2, #488]
	rsb	r0, r3, r0
	str	r0, [r2, #488]
	ldrb	r3, [r4]	@ zero_extendqisi2
	mov	r0, r5
	orr	r3, r3, #4
	strb	r3, [r4]
	bl	BsPos
	ldr	r3, [r8, #3680]
	add	r0, r0, #32
	cmp	r0, r3, asl #3
	bge	.L1276
	ldr	r7, [r9, #3652]
	movw	r1, #24144
	ldr	r3, [r4, #3128]
	movw	ip, #24152
	mov	r2, r7, asl #4
	mov	r0, r7, asl #6
	rsb	r5, r2, r0
	str	r0, [fp, #-48]
	add	r5, r4, r5
	str	r2, [fp, #-56]
	movw	r2, #24136
	strb	r7, [r5, r1]
	add	r1, r5, #24064
	ldr	r0, [r3, #24]
	add	r10, r1, #72
	add	r0, r6, r0, lsr #3
	str	r0, [r5, r2]
	ldr	r0, [r3, #24]
	mov	r6, r1
	and	r0, r0, #7
	str	r0, [r5, ip]
	ldr	r0, [r3, #16]
	ldr	r3, [r3, #24]
	rsb	r3, r3, r0, lsl #3
	str	r3, [r1, #92]
	ldr	r0, [r5, r2]
	bl	MEM_Vir2Phy
	movw	r1, #24176
	add	r3, r6, #112
	ldr	r2, [fp, #-56]
	str	r0, [r6, #84]
	ldr	r0, [r8, #3688]
	str	r0, [r5, r1]
	ldr	r1, [r8, #3664]
	cmp	r1, #0
	beq	.L1277
	ldr	r0, [r8, #3676]
	cmp	r0, #0
	beq	.L1277
	movw	ip, #24168
	str	r1, [r10, #4]
	mov	r1, #0
	str	r1, [r5, ip]
	ldr	ip, [r8, #3684]
	add	r1, r5, #24064
	str	r0, [r1, #100]
	mov	ip, ip, asl #3
	str	ip, [r1, #108]
	ldr	r1, [r8, #3692]
	str	r1, [r3, #4]
.L1278:
	ldr	r1, [r9, #3572]
	ldr	r0, [r9, #3568]
	ldrb	r10, [r4, #8]	@ zero_extendqisi2
	mul	r0, r0, r1
	cmp	r10, #0
	sub	r0, r0, #1
	beq	.L1279
	ldr	ip, [fp, #-52]
	sub	lr, r2, r7, asl #2
	add	r3, r1, #1
	movw	r6, #24160
	add	lr, ip, lr
	ldr	ip, [fp, #-48]
	add	r3, r3, r3, lsr #31
	add	lr, lr, #520
	rsb	r5, r2, ip
	ldr	ip, [lr, #8]
	add	r5, r4, r5
	sub	r3, ip, r3, asr #1
	cmp	r0, r3
	str	r3, [r5, r6]
	movcs	r0, #0
	movcc	r0, #1
	cmp	r3, #0
	movle	r0, #0
	cmp	r0, #0
	bne	.L1329
.L1280:
	ldr	r3, [fp, #-48]
	rsb	r2, r2, r3
	add	r4, r4, r2
	b	.L1320
.L1256:
	mov	r1, r7
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	movw	r2, #5616
	ldr	r1, .L1330+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L1258
.L1276:
	mov	r1, r7
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	movw	r2, #5695
	ldr	r1, .L1330+4
	mov	r0, r10
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1258
.L1277:
	ldr	r3, [fp, #-48]
	movw	r5, #24168
	mov	r1, #0
	rsb	r3, r2, r3
	add	r3, r4, r3
	add	lr, r3, #24064
	str	r1, [lr, #76]
	str	r1, [r3, r5]
	str	r1, [lr, #108]
	str	r1, [lr, #100]
	str	r1, [lr, #116]
	b	.L1278
.L1327:
	ldr	r1, [fp, #-48]
	mov	r0, r4
	bl	VC1_ClearCurPic
	ldr	r2, [r9, #3652]
	mov	r0, r5
	ldr	r1, .L1330+12
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1258
.L1279:
	ldr	r3, [fp, #-48]
	sub	r1, r2, r7, asl #2
	movw	lr, #24160
	rsb	ip, r2, r3
	ldr	r3, [fp, #-52]
	add	ip, r4, ip
	add	r1, r3, r1
	add	r1, r1, #520
	ldr	r3, [r1, #8]
	cmp	r0, r3
	str	r3, [ip, lr]
	bcs	.L1280
	ldr	r2, [r1, #8]
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L1330+16
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1258
.L1259:
	ldr	r2, [fp, #-48]
	movw	lr, #24168
	ldr	r3, [fp, #-56]
	rsb	r3, r2, r3
	mov	r2, #0
	add	r3, r4, r3
	add	ip, r3, #24064
	str	r2, [ip, #76]
	str	r2, [r3, lr]
	str	r2, [ip, #108]
	str	r2, [ip, #100]
	str	r2, [ip, #116]
	b	.L1260
.L1261:
	ldr	r3, [fp, #-48]
	movw	ip, #24160
	ldr	r0, [fp, #-56]
	sub	r2, r3, r7, asl #2
	rsb	r0, r3, r0
	ldr	r3, [fp, #-52]
	add	r0, r4, r0
	add	r2, r3, r2
	add	r2, r2, #520
	ldr	r3, [r2, #8]
	cmp	r1, r3
	str	r3, [r0, ip]
	bcs	.L1262
	ldr	r2, [r2, #8]
	mov	r0, #1
	str	r1, [sp]
	ldr	r1, .L1330+16
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1258
.L1265:
	ldr	r1, .L1330+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1258
.L1329:
	ldr	r2, [lr, #8]
	mov	r0, #1
	str	r1, [sp]
	ldr	r1, .L1330+24
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1258
.L1328:
	ldr	r2, [ip, #8]
	ldr	r1, .L1330+24
	str	r0, [sp]
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1258
.L1331:
	.align	2
.L1330:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC69
	.word	.LC68
	.word	.LC67
	.word	.LC55
	.word	.LC56
	.word	.LC54
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L1338
	cmp	r2, #32
	bhi	.L1339
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1336
	ldrb	r3, [r0]	@ zero_extendqisi2
	mov	r2, r1
	mov	r1, r0
	ldr	r0, [r0, #3128]
	orr	r3, r3, #3
	strb	r3, [r5]
	bl	VC1_Vfmw_ParseSMPPicHdr
	cmp	r0, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r3, [r5]	@ zero_extendqisi2
	orr	r3, r3, #20
	strb	r3, [r5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1336:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvHdr
.L1338:
	ldr	r1, .L1340
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1339:
	ldr	r1, .L1340+4
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1341:
	.align	2
.L1340:
	.word	.LC70
	.word	.LC59
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
	ldrb	r3, [r4, #3546]	@ zero_extendqisi2
	add	r0, r0, #60
	str	r0, [r4, #3576]
	cmp	r3, #8
	strneb	r3, [r4, #459]
	moveq	r3, #6
	movne	r3, #0
	streqb	r3, [r4, #459]
	moveq	r2, #1
	strneb	r3, [r4, #460]
	ldrb	r3, [r4, #3544]	@ zero_extendqisi2
	streqb	r2, [r4, #460]
	cmp	r3, #0
	ldr	r2, [r1, #20]
	ldr	r1, [r1]
	beq	.L1348
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	BsInit
.L1348:
	bl	BsInit
	ldr	r0, [r4, #3552]
	add	r5, r5, #32768
	add	r3, r4, #3552
	adds	r2, r0, #15
	add	r3, r3, #8
	addmi	r2, r0, #30
	add	ip, r4, #3600
	add	ip, ip, #12
	mov	r2, r2, asr #4
	str	r2, [r5, #4016]
	ldr	r1, [r4, #3556]
	str	r0, [r5, #4032]
	adds	r2, r1, #15
	addmi	r2, r1, #30
	str	r1, [r5, #4036]
	mov	r2, r2, asr #4
	str	r2, [r5, #4020]
	ldmia	r3, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
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
	add	r1, r0, #49152
	add	r1, r1, #12
	beq	.L1357
	ldr	r2, [r4, #12]
	add	r3, r0, #49152
	str	r2, [r3, #24]
	ldr	r2, [r4]
	str	r2, [r3, #12]
	ldr	r2, [r4, #16]
	str	r2, [r3, #32]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #20]
	ldr	r2, [r4, #20]
	str	r2, [r3, #40]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1352
	ldr	r2, [r4, #92]
	str	r2, [r3, #28]
	ldr	r2, [r4, #80]
	str	r2, [r3, #16]
	ldr	r2, [r4, #96]
	str	r2, [r3, #36]
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	strb	r2, [r3, #21]
	ldr	r2, [r4, #100]
	str	r2, [r3, #44]
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1358
.L1353:
	bl	VC1_SetCodeInfo
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1358:
	ldr	r0, [r3, #520]
	bl	VC1_ClearCurPacket
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	ldr	r1, .L1359
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1352:
	mov	r2, #0
	str	r2, [r3, #28]
	str	r2, [r3, #16]
	str	r2, [r3, #36]
	strb	r2, [r3, #21]
	str	r2, [r3, #44]
	b	.L1353
.L1357:
	ldr	r1, .L1359+4
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1360:
	.align	2
.L1359:
	.word	.LC72
	.word	.LC71
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
	subs	r5, r1, #0
	mov	r4, r0
	beq	.L1387
	cmp	r0, #0
	beq	.L1388
	add	r5, r0, #12544
	ldr	r3, .L1394
	add	r5, r5, #32
	mov	r2, #160
	mov	r0, r5
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, r5
	mov	r0, r4
	bl	VC1_ReceivePacket
	subs	r5, r0, #0
	beq	.L1389
	ldr	r3, [r4]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L1390
.L1366:
	add	r3, r4, #12288
	add	r6, r4, #49152
	ldrb	r3, [r3, #448]	@ zero_extendqisi2
	strb	r3, [r6, #128]
.L1367:
	add	r7, r4, #12736
	add	r1, r4, #15872
	add	r1, r1, #28
	ldr	r2, [r6, #520]
	mov	r0, r7
	bl	VC1_Vfmw_ParseHeader
	subs	r8, r0, #0
	beq	.L1391
	mov	r0, r4
	bl	VC1_Vfmw_DecodeArbiter
	cmp	r0, #0
	bne	.L1392
.L1370:
	mov	r5, #0
.L1363:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1391:
	add	r1, r4, #49152
	ldr	r0, [r6, #520]
	add	r1, r1, #12
	bl	VC1_ClearCurPacket
	ldr	r3, .L1394+4
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1370
	ldr	r0, [r6, #520]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	mov	r5, r8
	blx	r4
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1390:
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L1366
	add	r6, r4, #49152
	add	r3, r4, #12288
	ldrb	r2, [r6, #128]	@ zero_extendqisi2
	strb	r2, [r3, #448]
	b	.L1367
.L1389:
	add	r4, r4, #49152
	ldr	r1, .L1394+8
	ldr	r2, [r4, #8]
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1392:
	mov	r0, r4
	bl	VC1_Vfmw_PrepareDecode
	subs	r5, r0, #0
	bne	.L1371
	ldr	r3, [r4]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L1393
.L1372:
	mov	r0, r7
	ldr	r1, [r6, #520]
	bl	VC1_ClearCurPic
.L1373:
	ldr	r3, .L1394+4
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1370
	mov	r3, #0
	ldr	r0, [r6, #520]
	mov	r2, r3
	mov	r1, #113
	blx	r4
	b	.L1363
.L1388:
	ldr	r1, .L1394+12
	mov	r5, r0
	bl	dprint_vfmw
	b	.L1363
.L1393:
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L1372
	b	.L1373
.L1387:
	ldr	r1, .L1394+16
	mov	r0, r5
	bl	dprint_vfmw
	b	.L1363
.L1371:
	mov	r0, r4
	bl	VC1_Vfmw_StartDecode
	subs	r5, r0, #0
	movne	r5, r8
	bne	.L1363
	add	r4, r4, #32768
	mov	r2, #1
	ldr	r0, [r6, #520]
	ldr	r1, [r4, #4092]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #4000]
	ldr	r3, .L1394+4
	strb	r5, [r2]
	ldr	r2, [r4, #4000]
	strb	r5, [r2, #1]
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1370
	ldr	r0, [r6, #520]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r4
	b	.L1363
.L1395:
	.align	2
.L1394:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC75
	.word	.LC74
	.word	.LC73
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
	subs	r3, r0, #0
	beq	.L1400
	add	r3, r3, #12736
	ldrsb	r3, [r3, #6]
	cmp	r3, #1
	movne	r0, #0
	moveq	r0, #2
	ldmfd	sp, {fp, sp, pc}
.L1400:
	ldr	r3, .L1401
	movw	r2, #5981
	ldr	r1, .L1401+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1402:
	.align	2
.L1401:
	.word	.LC23
	.word	.LC24
	UNWIND(.fnend)
	.size	VC1_GetPacketState, .-VC1_GetPacketState
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13701, %object
	.size	__func__.13701, 13
__func__.13701:
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
	.type	__func__.14012, %object
	.size	__func__.14012, 17
__func__.14012:
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
	ASCII(.ascii	"pCtx or pstExtraData is NULL! \012\000" )
.LC14:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC15:
	ASCII(.ascii	"VC1 INIT!!!\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"pBitBuf or pVc1Info is NULL! \012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC18:
	ASCII(.ascii	"%s: %s\012\000" )
.LC19:
	ASCII(.ascii	"picture height out of range\000" )
.LC20:
	ASCII(.ascii	"Vc1SMPSeqHdr Err, BS is wrong\000" )
	.space	2
.LC21:
	ASCII(.ascii	"Vc1SMPSeqHdr Err, BS is wrong\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"pCtx is NULL! \012\000" )
.LC23:
	ASCII(.ascii	"pCtx is NULL!\000" )
	.space	2
.LC24:
	ASCII(.ascii	"vc1.c,L%d: %s\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC26:
	ASCII(.ascii	"vc1 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC27:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"VC1_Vfmw_GetImageBuffer get imgbuf err, clear all r" )
	ASCII(.ascii	"ef!\012\000" )
.LC32:
	ASCII(.ascii	"VC1_Vfmw_GetImageBuffer get_flag!=1, FSP_ClearLogic" )
	ASCII(.ascii	"Fs.\012\000" )
.LC33:
	ASCII(.ascii	"pCodecInf is NULL! \012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_ArrangeVahbMem err!\012\000" )
.LC35:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_GetImageBuffer err!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo B pic pCodecInf->RefNum < 2 " )
	ASCII(.ascii	"err!\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"line: %d (pCur,pFwd,pBwd)(%p,%p,%p)\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo imgbuf = NULL err!\012\000" )
	.space	1
.LC41:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p)\012\000" )
	.space	2
.LC42:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_BuildRefList err!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC43:
	ASCII(.ascii	"pVC1_CTX_S is NULL!\000" )
.LC44:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo error! Release all packets!\012" )
	ASCII(.ascii	"\000" )
.LC45:
	ASCII(.ascii	"%s:%d Code(%d) is invalid\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"%s:%d Denominator(%d) is invalid\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"Check Pos 2: %d\012\000" )
	.space	3
.LC48:
	ASCII(.ascii	"Check Pos 3: %d\012\000" )
	.space	3
.LC49:
	ASCII(.ascii	"\012======PicNum  :%6d=========\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"INTERPFRM  :%#x\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"VC1_Vfmw_ParseMPBPicHdr err!\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	"VC1_Vfmw_ParseSMPIPicHdr err!\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"After VC1_Vfmw_ParseSMPPicHdr BS Len <= 0 err!\012\000" )
.LC54:
	ASCII(.ascii	"SLICE_ADDR = %d,SlcEndMbn = %d, MbHeight = %d\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"SLICE_ADDR = %d,SlcEndMbn = %d, totalMbMin1 = %d\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC56:
	ASCII(.ascii	"VC1_RecordSlcStream stream len <= 0\012\000" )
	.space	3
.LC57:
	ASCII(.ascii	"pCodecInf is NULL!\000" )
	.space	1
.LC58:
	ASCII(.ascii	"pCodeInfo  is NULL! \012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"ChanID is out of range! \012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"pImg is null, pCurImg %p pBwdImg %p pFwdImg %p\012\000" )
.LC61:
	ASCII(.ascii	"line: %d, pToQueImg is Null!\012\000" )
	.space	2
.LC62:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC64:
	ASCII(.ascii	"----------------- VC1 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC65:
	ASCII(.ascii	"NOTE: Drop non-I\012\000" )
	.space	2
.LC66:
	ASCII(.ascii	"NOTE: Drop B\012\000" )
	.space	2
.LC67:
	ASCII(.ascii	" pCodecInf->SlcNum = %d >= 256 \012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"line %d, Code = VC1_SCSLC failed!\012\000" )
	.space	1
.LC69:
	ASCII(.ascii	"line %d, Code = VC1_SCFRM failed!\012\000" )
	.space	1
.LC70:
	ASCII(.ascii	"pCodecInf or pSyntax is NULL! \012\000" )
.LC71:
	ASCII(.ascii	"bitsream para error -----\012\000" )
	.space	1
.LC72:
	ASCII(.ascii	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\012\000" )
.LC73:
	ASCII(.ascii	"ERROR: p_Packet is Null pointer!\012\000" )
	.space	2
.LC74:
	ASCII(.ascii	"ERROR: pVC1_CTX_S is Null pointer!\012\000" )
.LC75:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
