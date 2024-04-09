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
	.file	"vp8.c"
	.text
	.align	2
	.type	VP8_init_frame.part.0, %function
VP8_init_frame.part.0:
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
	ldr	r6, .L2
	mov	r4, r0
	ldr	r7, .L2+4
	add	r0, r0, #2368
	mov	r2, #38
	add	r0, r0, #14
	ldr	r3, [r6, #52]
	mov	r1, r7
	ldr	r5, .L2+8
	blx	r3
	add	r0, r4, #1312
	add	r1, r7, #40
	ldr	r3, [r6, #52]
	mov	r2, #1056
	add	r0, r0, #14
	blx	r3
	add	r0, r4, #1312
	mov	r1, r5
	ldr	r3, [r6, #52]
	mov	r2, #4
	add	r0, r0, #6
	blx	r3
	add	r0, r4, #1312
	add	r1, r5, #4
	ldr	r3, [r6, #52]
	mov	r5, #0
	mov	r2, #3
	add	r0, r0, #10
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #8
	mov	r1, r5
	add	r0, r4, #22
	blx	r3
	strb	r5, [r4, #17]
	mov	r1, r5
	ldr	r3, [r6, #48]
	mov	r2, #4
	add	r0, r4, #40
	blx	r3
	ldr	r3, [r6, #48]
	mov	r1, r5
	add	r0, r4, #44
	mov	r2, #4
	blx	r3
	mov	r3, #1
	strb	r5, [r4, #51]
	strb	r5, [r4, #52]
	strb	r5, [r4, #56]
	strb	r5, [r4, #57]
	strb	r3, [r4, #49]
	strb	r3, [r4, #50]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VP8_init_frame.part.0, .-VP8_init_frame.part.0
	.align	2
	.global	Vp8_Vfmw_StartBoolDecode
	.type	Vp8_Vfmw_StartBoolDecode, %function
Vp8_Vfmw_StartBoolDecode:
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
	mov	r2, #255
	mov	r0, r1
	mov	r3, #16
	str	r2, [r4]
	mov	r1, #24
	str	r3, [r4, #8]
	bl	BsGet
	str	r0, [r4, #4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp8_Vfmw_StartBoolDecode, .-Vp8_Vfmw_StartBoolDecode
	.align	2
	.global	Vp8_Vfmw_DecodeBool
	.type	Vp8_Vfmw_DecodeBool, %function
Vp8_Vfmw_DecodeBool:
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
	mov	r7, r0
	mov	r8, r1
	ldmia	r0, {r0, r1}
	ldr	r6, [r7, #8]
	sub	r5, r0, #1
	mul	r2, r5, r2
	mov	r5, r2, lsr #8
	ldr	r2, .L13
	add	r5, r5, #1
	mov	r3, r5, asl #16
	cmp	r1, r3
	rsbcs	r5, r5, r0
	rsbcs	r1, r3, r1
	add	r2, r2, r5
	movcs	r9, #1
	movcc	r9, #0
	ldrb	r3, [r2, #1096]	@ zero_extendqisi2
	subs	r6, r6, r3
	mov	r5, r5, asl r3
	mov	r10, r1, asl r3
	bmi	.L12
.L7:
	mov	r0, r9
	str	r6, [r7, #8]
	stmia	r7, {r5, r10}
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L12:
	rsbs	r3, r6, #8
	str	r3, [fp, #-48]
	bmi	.L7
	mov	r4, r3
.L8:
	mov	r1, #8
	mov	r0, r8
	bl	BsGet
	orr	r10, r10, r0, asl r4
	subs	r4, r4, #8
	bpl	.L8
	ldr	r3, [fp, #-48]
	add	r6, r6, #8
	bic	r3, r3, #7
	add	r6, r6, r3
	b	.L7
.L14:
	.align	2
.L13:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Vp8_Vfmw_DecodeBool, .-Vp8_Vfmw_DecodeBool
	.align	2
	.global	Vp8_Vfmw_DecodeValue
	.type	Vp8_Vfmw_DecodeValue, %function
Vp8_Vfmw_DecodeValue:
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
	subs	r4, r2, #1
	mov	r5, #0
	mov	r6, r0
	mov	r7, r1
	bmi	.L16
.L17:
	mov	r2, #128
	mov	r1, r7
	mov	r0, r6
	bl	Vp8_Vfmw_DecodeBool
	orr	r5, r5, r0, asl r4
	subs	r4, r4, #1
	bcs	.L17
.L16:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Vp8_Vfmw_DecodeValue, .-Vp8_Vfmw_DecodeValue
	.align	2
	.global	VP8_SetImgFormat
	.type	VP8_SetImgFormat, %function
VP8_SetImgFormat:
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
	add	r5, r0, #4096
	add	r7, r0, #8192
	mov	r6, r0
	ldr	r1, [r5, #4092]
	ldr	r0, [r7, #368]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r2, [r7, #4]
	mov	ip, #1
	ldrb	r1, [r4, #64]	@ zero_extendqisi2
	mov	lr, #5
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	bfi	r1, r2, #0, #2
	and	r2, r2, #3
	and	r3, r3, #252
	and	r1, r1, #227
	orr	r3, r3, #12
	bfi	r1, lr, #5, #3
	bfi	r3, ip, #4, #2
	strb	r1, [r4, #64]
	strb	r3, [r4, #65]
	mov	lr, #0
	ldr	r3, [r4, #64]
	mov	r1, lr
	bfc	r3, #14, #3
	str	r3, [r4, #64]
	ldrb	r7, [r5, #1624]	@ zero_extendqisi2
	mov	r3, r3, lsr #16
	bfi	r3, r7, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r5, #1628]
	str	r2, [r4, #56]
	str	r2, [r4, #60]
	mov	r2, #13
	str	r3, [r4, #120]
	mov	r3, #8
	str	r2, [r4, #296]
	str	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	strb	ip, [r4, #291]
	strb	ip, [r4, #289]
	strb	lr, [r4, #284]
	bl	SetAspectRatio
	ldr	r2, [r5, #1704]
	str	r2, [r4, #68]
	ldr	r3, [r5, #1708]
	str	r3, [r4, #72]
	ldr	r1, [r6]
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L26
.L22:
	str	r2, [r4, #76]
	mov	r2, r2, lsr #1
	str	r3, [r4, #80]
	mov	r3, r3, lsr #1
	str	r2, [r4, #84]
	str	r3, [r4, #88]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L26:
	ldr	lr, [r4, #112]
	add	ip, r3, #15
	ldr	r5, [r4, #36]
	add	r7, r4, #512
	mov	r1, ip, lsr #4
	mov	ip, lr, asl #4
	add	r8, r5, lr
	mul	ip, r1, ip
	add	r6, ip, r5
	str	r6, [r4, #40]
	ldrd	r0, [r7, #-8]
	add	lr, r6, lr
	adds	r0, r0, ip
	adc	r1, r1, ip, asr #31
	strd	r0, [r7]
	str	r6, [r4, #24]
	str	lr, [r4, #32]
	str	r8, [r4, #28]
	str	r5, [r4, #20]
	b	.L22
	UNWIND(.fnend)
	.size	VP8_SetImgFormat, .-VP8_SetImgFormat
	.align	2
	.global	VP8DEC_VDMPostProc
	.type	VP8DEC_VDMPostProc, %function
VP8DEC_VDMPostProc:
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
	mov	r7, r1
	beq	.L96
	ldr	r3, [r5, #4]
	add	r4, r5, #4096
	add	r6, r5, #8192
	mov	r1, r5
	mov	r0, #13
	ldrb	r2, [r3, #2778]	@ zero_extendqisi2
	strb	r2, [r4, #1624]
	ldr	r3, [r3, #3144]
	str	r3, [r4, #1628]
	bl	ReleasePacket
	ldr	r1, [r4, #4092]
	ldr	r0, [r6, #368]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L97
	cmp	r7, #0
	blt	.L31
	cmp	r7, #100
	movlt	r2, r7
	movge	r2, #100
	str	r2, [r3, #152]
	ldr	r3, [r5]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L98
.L32:
	mov	r0, r5
	bl	VP8_SetImgFormat
	ldr	r3, [r4, #4056]
	cmp	r3, #2
	beq	.L99
.L33:
	ldr	r3, [r5, #3296]
	cmp	r3, #0
	bne	.L35
.L34:
	mvn	r3, #0
	mov	r2, #0
	str	r3, [r6]
	ldr	r0, [r6, #368]
	ldr	r1, [r4, #4092]
	bl	FSP_SetDisplay
	ldr	r1, [r6]
.L36:
	cmn	r1, #1
	beq	.L37
	ldr	r0, [r6, #368]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L100
	mov	r2, #1
	ldr	r1, [r6]
	ldr	r0, [r6, #368]
	bl	FSP_SetDisplay
	add	r3, r5, #8192
	ldr	r0, [r6, #368]
	add	r3, r3, #16
	str	r8, [sp]
	mov	r2, r5
	mov	r1, #13
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r7, r0
	bne	.L101
.L37:
	ldr	r3, [r4, #4060]
	ldr	r8, [r4, #4088]
	add	r3, r3, #1
	str	r3, [r4, #4060]
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L39
	ldrb	r0, [r5, #3276]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	r7, r0
	bne	.L39
	ldrb	r3, [r5, #3280]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L102
.L44:
	cmp	r3, #2
	beq	.L103
.L46:
	ldrb	r3, [r5, #3279]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L104
.L49:
	cmp	r3, #2
	beq	.L105
.L51:
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L54
	ldrb	r3, [r5, #3277]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L55
.L54:
	ldr	r3, [r4, #4080]
	ldr	r2, [r4, #4088]
	cmp	r3, r2
	beq	.L94
	ldr	r2, [r4, #4084]
	cmp	r3, r2
	beq	.L94
	ldr	r1, [r4, #4092]
	cmp	r3, r1
	beq	.L57
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
.L94:
	ldr	r1, [r4, #4092]
.L57:
	str	r1, [r4, #4080]
	mov	r2, #1
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
.L55:
	ldr	r3, [r5, #3292]
	cmp	r3, #0
	beq	.L59
	ldrb	r3, [r5, #3278]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L60
.L59:
	ldr	r3, [r4, #4084]
	ldr	r2, [r4, #4088]
	cmp	r3, r2
	beq	.L95
	ldr	r2, [r4, #4080]
	cmp	r3, r2
	beq	.L95
	ldr	r1, [r4, #4092]
	cmp	r3, r1
	beq	.L62
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
.L95:
	ldr	r1, [r4, #4092]
.L62:
	str	r1, [r4, #4084]
	mov	r2, #1
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
.L60:
	cmp	r7, #1
	movne	r0, #1
	beq	.L106
.L93:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L35:
	ldr	r1, [r4, #4092]
	str	r1, [r6]
	b	.L36
.L39:
	ldr	r3, [r4, #4080]
	cmp	r8, r3
	beq	.L43
	ldr	r3, [r4, #4084]
	cmp	r8, r3
	beq	.L43
	ldr	r1, [r4, #4092]
	subs	r7, r8, r1
	movne	r7, #1
.L42:
	str	r1, [r4, #4088]
	mov	r2, #1
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
	ldrb	r3, [r5, #3280]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L44
.L102:
	ldr	r1, [r4, #4084]
	ldr	r3, [r4, #4088]
	cmp	r1, r3
	beq	.L45
	ldr	r3, [r4, #4080]
	cmp	r1, r3
	cmpne	r8, r1
	beq	.L45
	mov	r2, #0
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
.L45:
	str	r8, [r4, #4084]
	mov	r2, #1
	ldr	r0, [r6, #368]
	mov	r1, r8
	bl	FSP_SetRef
	ldrb	r3, [r5, #3279]	@ zero_extendqisi2
	mov	r7, #0
	cmp	r3, #1
	bne	.L49
.L104:
	ldr	r1, [r4, #4080]
	ldr	r3, [r4, #4088]
	cmp	r1, r3
	beq	.L50
	ldr	r3, [r4, #4084]
	cmp	r1, r3
	cmpne	r8, r1
	beq	.L50
	mov	r2, #0
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
.L50:
	str	r8, [r4, #4080]
	mov	r2, #1
	ldr	r0, [r6, #368]
	mov	r1, r8
	bl	FSP_SetRef
	mov	r7, #0
	b	.L51
.L43:
	ldr	r1, [r4, #4092]
	mov	r7, #0
	b	.L42
.L31:
	mov	r2, #0
	str	r2, [r3, #152]
	b	.L32
.L99:
	ldr	r3, [r6, #4]
	cmp	r3, #0
	bne	.L34
	b	.L33
.L101:
	add	r10, r8, #544
	ldr	r1, [r8, #544]
	ldr	r0, [r6, #368]
	add	r9, r8, #560
	bl	FreeUsdByDec
	mov	r4, #0
	mov	r5, #0
	strd	r4, [r10]
	ldr	r1, [r8, #552]
	ldr	r0, [r6, #368]
	bl	FreeUsdByDec
	strd	r4, [r9, #-8]
	mov	r2, #0
	ldr	r1, [r6]
	ldr	r0, [r6, #368]
	bl	FSP_SetDisplay
	ldr	r1, .L107
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L103:
	ldr	r3, [r4, #4084]
	ldr	r2, [r4, #4088]
	ldr	r1, [r4, #4080]
	cmp	r3, r2
	beq	.L48
	cmp	r3, r1
	beq	.L48
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
	ldr	r1, [r4, #4080]
.L48:
	str	r1, [r4, #4084]
	mov	r2, #1
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
	b	.L46
.L105:
	ldr	r3, [r4, #4080]
	ldr	r2, [r4, #4088]
	ldr	r1, [r4, #4084]
	cmp	r3, r2
	beq	.L53
	cmp	r3, r1
	beq	.L53
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
	ldr	r1, [r4, #4084]
.L53:
	str	r1, [r4, #4080]
	mov	r2, #1
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
	b	.L51
.L106:
	ldr	r0, [r6, #368]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetRef
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L96:
	movw	r2, #581
	ldr	r1, .L107+4
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L98:
	ldr	r1, .L107+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #4080]
	mov	r5, #0
	ldr	r0, [r6, #368]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #4084]
	ldr	r0, [r6, #368]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #4088]
	ldr	r0, [r6, #368]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #4080]
	str	r5, [r4, #4084]
	str	r5, [r4, #4088]
	ldr	r0, [r6, #368]
	bl	FSP_GetNullLogicFs
	str	r5, [r4, #4060]
	mov	r3, r0
	mvn	r0, #0
	str	r3, [r4, #4088]
	str	r3, [r4, #4084]
	str	r3, [r4, #4080]
	b	.L93
.L100:
	movw	r2, #626
	ldr	r1, .L107+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L93
.L97:
	ldr	r1, .L107+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L93
.L108:
	.align	2
.L107:
	.word	.LC5
	.word	.LC1
	.word	.LC3
	.word	.LC4
	.word	.LC2
	UNWIND(.fnend)
	.size	VP8DEC_VDMPostProc, .-VP8DEC_VDMPostProc
	.align	2
	.global	VP8DEC_Init
	.type	VP8DEC_Init, %function
VP8DEC_Init:
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
	beq	.L113
	add	r5, r0, #8192
	ldr	r3, .L115
	mov	r2, #8576
	mov	r1, r6
	ldr	r8, [r5, #360]
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r5, #16
	str	r8, [r5, #360]
	bl	ResetVoQueue
	str	r7, [r4]
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r5, #368]
	beq	.L114
	add	r3, r4, #4096
	mov	r2, #1024
	mov	r1, #3
	mov	r0, #1
	str	r6, [r3, #4064]
	str	r2, [r3, #4052]
	ldr	r2, [r4]
	ldr	ip, [r2, #8]
	str	ip, [r3, #4056]
	str	r1, [r5, #8]
	str	r6, [r3, #4072]
	str	r1, [r3, #4068]
	ldr	r2, [r2, #40]
	str	r2, [r3, #4076]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L113:
	mov	r2, #760
	ldr	r1, .L115+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L114:
	mov	r0, r6
	ldr	r1, .L115+8
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L116:
	.align	2
.L115:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC1
	.word	.LC6
	UNWIND(.fnend)
	.size	VP8DEC_Init, .-VP8DEC_Init
	.align	2
	.global	VP8DEC_Destroy
	.type	VP8DEC_Destroy, %function
VP8DEC_Destroy:
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
	.size	VP8DEC_Destroy, .-VP8DEC_Destroy
	.align	2
	.global	VP8_setup_version
	.type	VP8_setup_version, %function
VP8_setup_version:
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
	ldr	r3, [r0, #72]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L119
.L121:
	.word	.L119
	.word	.L122
	.word	.L123
	.word	.L124
.L119:
	mov	r3, #0
	str	r3, [r0, #84]
	str	r3, [r0, #88]
	str	r3, [r0, #92]
	str	r3, [r0, #96]
	mov	r3, #0
	str	r3, [r0, #100]
	ldmfd	sp, {fp, sp, pc}
.L123:
	mov	r2, #1
	mov	r3, #0
	str	r2, [r0, #84]
	str	r2, [r0, #92]
	str	r3, [r0, #88]
	str	r3, [r0, #96]
.L126:
	mov	r3, #1
	str	r3, [r0, #100]
	ldmfd	sp, {fp, sp, pc}
.L122:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r0, #84]
	str	r2, [r0, #96]
	str	r3, [r0, #88]
	str	r3, [r0, #92]
	b	.L126
.L124:
	mov	r3, #1
	str	r3, [r0, #84]
	str	r3, [r0, #88]
	str	r3, [r0, #92]
	str	r3, [r0, #96]
	b	.L126
	UNWIND(.fnend)
	.size	VP8_setup_version, .-VP8_setup_version
	.align	2
	.global	read_mvcontexts
	.type	read_mvcontexts, %function
read_mvcontexts:
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
	ldr	r8, .L140
	mov	r7, r0
	mov	r6, r1
	mov	r9, r2
	add	r10, r8, #38
.L132:
	mov	r4, r8
	mov	r5, r9
	add	r8, r8, #19
	b	.L131
.L129:
	cmp	r4, r8
	add	r5, r5, #1
	beq	.L139
.L131:
	ldrb	r2, [r4], #1	@ zero_extendqisi2
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L129
	mov	r2, #7
	mov	r1, r6
	mov	r0, r7
	add	r5, r5, #1
	bl	Vp8_Vfmw_DecodeValue
	mov	r3, #1
	uxtb	r0, r0
	cmp	r0, #0
	mov	r0, r0, asl r3
	uxtbne	r3, r0
	cmp	r4, r8
	strb	r3, [r5, #-1]
	bne	.L131
.L139:
	cmp	r10, r4
	add	r9, r9, #19
	bne	.L132
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L141:
	.align	2
.L140:
	.word	.LANCHOR0+1352
	UNWIND(.fnend)
	.size	read_mvcontexts, .-read_mvcontexts
	.align	2
	.global	VP8_mb_mode_mv_init
	.type	VP8_mb_mode_mv_init, %function
VP8_mb_mode_mv_init:
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
	ldr	r3, [r0, #64]
	mov	r6, r0
	mov	r4, r1
	mov	r5, r2
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r2, #8
	mov	r1, r5
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #8
	mov	r1, r5
	strb	r0, [r6, #58]
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #8
	mov	r1, r5
	strb	r0, [r6, #59]
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #128
	mov	r1, r5
	strb	r0, [r6, #60]
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #1
	beq	.L144
.L148:
	mov	r2, #128
	mov	r1, r5
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L146
	add	r7, r6, #1312
	mov	r8, r7
	add	r7, r7, #9
	add	r8, r8, #12
.L149:
	mov	r2, #8
	mov	r1, r5
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	strb	r0, [r7, #1]!
	cmp	r7, r8
	bne	.L149
.L146:
	add	r2, r6, #2368
	mov	r1, r5
	add	r2, r2, #14
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	read_mvcontexts
.L144:
	add	r7, r6, #1312
	mov	r8, r7
	add	r7, r7, #5
	add	r8, r8, #9
.L147:
	mov	r2, #8
	mov	r1, r5
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	strb	r0, [r7, #1]!
	cmp	r7, r8
	bne	.L147
	b	.L148
	UNWIND(.fnend)
	.size	VP8_mb_mode_mv_init, .-VP8_mb_mode_mv_init
	.align	2
	.global	get_delta_q
	.type	get_delta_q, %function
get_delta_q:
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
	mov	r5, r2
	mov	r2, #128
	mov	r6, r3
	mov	r7, r0
	mov	r8, r1
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #0
	bne	.L156
.L153:
	cmp	r0, r5
	movne	r3, #1
	strne	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L156:
	mov	r2, #4
	mov	r1, r8
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	mov	r1, r8
	mov	r2, #128
	mov	r4, r0
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r3, r0, #0
	eor	r4, r4, r3
	add	r0, r4, r0
	b	.L153
	UNWIND(.fnend)
	.size	get_delta_q, .-get_delta_q
	.align	2
	.global	VP8_init_frame
	.type	VP8_init_frame, %function
VP8_init_frame:
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
	ldr	r3, [r0, #64]
	cmp	r3, #0
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8_init_frame.part.0
	UNWIND(.fnend)
	.size	VP8_init_frame, .-VP8_init_frame
	.align	2
	.global	VP8_GetPictureHeader
	.type	VP8_GetPictureHeader, %function
VP8_GetPictureHeader:
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
	ldr	r3, .L250
	mov	r9, r1
	mov	r6, r0
	str	r1, [fp, #-68]
	sub	r5, fp, #52
	ldmia	r3, {r0, r1}
	mov	r4, r2
	stmia	r5, {r0, r1}
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	mov	r1, #8
	mov	r7, r0
	mov	r0, r6
	bl	BsGet
	mov	r1, #8
	mov	r8, r0
	mov	r0, r6
	bl	BsGet
	add	r1, r9, #4096
	uxtb	r3, r7
	uxtb	r2, r8
	and	r7, r7, #1
	str	r7, [r9, #2532]
	str	r7, [r1, #880]
	ubfx	r1, r3, #1, #3
	str	r1, [r9, #2540]
	ubfx	r1, r3, #4, #1
	str	r1, [r9, #2536]
	uxtb	r0, r0
	mov	r1, r0, asl #16
	orr	r1, r1, r2, asl #8
	orr	r3, r1, r3
	mov	r3, r3, asr #5
	str	r3, [r9, #2544]
	cmp	r3, r4
	bhi	.L240
	ldr	r4, [fp, #-68]
	add	r3, r4, #2464
	add	r3, r3, #4
	str	r3, [fp, #-80]
	mov	r0, r3
	bl	VP8_setup_version
	ldr	r7, [r4, #2532]
	cmp	r7, #0
	beq	.L241
.L163:
	ldr	r4, [fp, #-68]
	mov	r3, #16
	mov	r2, #255
	mov	r1, #24
	mov	r0, r6
	str	r3, [r4, #2624]
	str	r2, [r4, #2616]
	bl	BsGet
	ldr	r3, [r4, #2532]
	ldr	r1, [fp, #-80]
	cmp	r3, #0
	add	r7, r1, #148
	str	r0, [r4, #2620]
	bne	.L168
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #128
	mov	r1, r6
	str	r0, [r4, #2604]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	str	r0, [r4, #2608]
.L168:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2482]
	cmp	r0, #0
	bne	.L169
.L176:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #6
	mov	r1, r6
	str	r0, [r4, #2612]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #3
	mov	r1, r6
	strb	r0, [r4, #2478]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	mov	r3, #0
	mov	r2, #128
	strb	r3, [r4, #2469]
	mov	r1, r6
	strb	r0, [r4, #2479]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	uxtb	r0, r0
	strb	r0, [r4, #2470]
	cmp	r0, #0
	bne	.L242
.L171:
	mov	r2, #2
	mov	r1, r6
	mov	r0, r7
	sub	r4, fp, #44
	bl	Vp8_Vfmw_DecodeValue
	ldr	r8, [fp, #-68]
	mov	r2, #7
	mov	r1, r6
	mov	r5, #0
	strb	r0, [r8, #2481]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	movw	r2, #2473
	str	r5, [r4, #-12]!
	mov	r1, r6
	ldrsb	r2, [r8, r2]
	mov	r3, r4
	strb	r0, [r8, #2471]
	mov	r0, r7
	bl	get_delta_q
	movw	r2, #2474
	ldrsb	r2, [r8, r2]
	mov	r3, r4
	mov	r1, r6
	strb	r0, [r8, #2473]
	mov	r0, r7
	bl	get_delta_q
	movw	r2, #2475
	ldrsb	r2, [r8, r2]
	mov	r3, r4
	mov	r1, r6
	strb	r0, [r8, #2474]
	mov	r0, r7
	bl	get_delta_q
	movw	r2, #2476
	ldrsb	r2, [r8, r2]
	mov	r3, r4
	mov	r1, r6
	strb	r0, [r8, #2475]
	mov	r0, r7
	bl	get_delta_q
	movw	r2, #2477
	mov	r3, r4
	ldrsb	r2, [r8, r2]
	mov	r1, r6
	strb	r0, [r8, #2476]
	mov	r0, r7
	bl	get_delta_q
	ldr	r3, [r8, #2532]
	cmp	r3, r5
	strb	r0, [r8, #2477]
	bne	.L243
.L180:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2521]
	cmp	r0, #0
	bne	.L191
	ldr	r0, [fp, #-80]
	movw	r2, #1149
	ldr	r3, .L250+4
	add	r1, r0, #1296
	add	r0, r0, #160
	add	r1, r1, #13
	ldr	r3, [r3, #52]
	blx	r3
.L191:
	ldr	r2, [fp, #-68]
	ldr	r3, [r2, #2532]
	cmp	r3, #0
	bne	.L192
	mov	r3, #1
	strb	r3, [r2, #2516]
.L193:
	ldr	r3, [fp, #-68]
	ldr	r10, .L250+8
	add	r3, r3, #3792
	add	r3, r3, #2
	str	r3, [fp, #-76]
.L204:
	add	r3, r10, #264
	str	r3, [fp, #-72]
	ldr	r3, [fp, #-76]
	str	r3, [fp, #-64]
.L200:
	ldr	r8, [fp, #-64]
	sub	r5, r10, #33
.L198:
	sub	r9, r5, #11
	mov	r4, r8
	b	.L195
.L194:
	cmp	r9, r5
	add	r4, r4, #1
	beq	.L244
.L195:
	ldrb	r2, [r9, #1]!	@ zero_extendqisi2
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #1
	bne	.L194
	mov	r2, #8
	mov	r1, r6
	mov	r0, r7
	add	r4, r4, #1
	bl	Vp8_Vfmw_DecodeValue
	cmp	r9, r5
	strb	r0, [r4, #-1]
	bne	.L195
.L244:
	add	r5, r9, #11
	add	r8, r8, #11
	cmp	r5, r10
	bne	.L198
	ldr	r3, [fp, #-64]
	add	r10, r9, #44
	add	r3, r3, #33
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-72]
	cmp	r10, r3
	bne	.L200
	ldr	r3, .L250+12
	cmp	r10, r3
	ldr	r3, [fp, #-76]
	add	r3, r3, #264
	str	r3, [fp, #-76]
	bne	.L204
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	cmp	r0, #0
	str	r0, [r3, #2548]
	ldreq	r3, [fp, #-68]
	streqb	r0, [r3, #2529]
	beq	.L202
	mov	r2, #8
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	ldr	r3, [fp, #-68]
	strb	r0, [r3, #2529]
.L202:
	mov	r2, r6
	mov	r1, r7
	ldr	r0, [fp, #-80]
	bl	VP8_mb_mode_mv_init
	ldr	r3, [fp, #-68]
	ldr	r3, [r3, #2532]
	cmp	r3, #0
	beq	.L203
	ldr	r3, [fp, #-68]
	ldr	r3, [r3, #2516]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	moveq	r0, #1
	beq	.L236
.L203:
	ldr	r2, [fp, #-68]
	mov	r0, #1
	ldrb	r3, [r2, #2471]	@ zero_extendqisi2
	strb	r3, [r2, #2472]
.L236:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L241:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	mov	r1, #8
	mov	r4, r0
	mov	r0, r6
	bl	BsGet
	mov	r1, #8
	mov	r8, r0
	mov	r0, r6
	bl	BsGet
	uxtb	r2, r4
	uxtb	r3, r8
	cmp	r2, #157
	cmpeq	r3, #1
	movne	r4, #1
	moveq	r4, #0
	uxtb	r0, r0
	cmp	r0, #42
	orrne	r4, r4, #1
	cmp	r4, #0
	beq	.L164
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L250+16
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L240:
	ldr	r1, .L250+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L164:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	mov	r1, #8
	mov	r9, r0
	mov	r0, r6
	bl	BsGet
	mov	r1, #8
	mov	r7, r0
	mov	r0, r6
	bl	BsGet
	mov	r1, #8
	mov	r8, r0
	mov	r0, r6
	bl	BsGet
	ldr	lr, [fp, #-68]
	uxtb	r3, r7
	uxtb	r2, r9
	uxtb	r8, r8
	orr	r2, r2, r3, asl #8
	mov	r3, r3, lsr #6
	ubfx	r2, r2, #0, #14
	str	r3, [lr, #2588]
	add	r1, r2, #15
	str	r2, [lr, #2580]
	mov	r1, r1, lsr #4
	str	r1, [lr, #2572]
	uxtb	r0, r0
	orr	r8, r8, r0, asl #8
	mov	r0, r0, lsr #6
	ubfx	r3, r8, #0, #14
	str	r0, [lr, #2592]
	add	ip, r3, #15
	cmp	r3, #32
	cmphi	r2, #32
	mov	r0, lr
	str	r3, [lr, #2584]
	mov	ip, ip, lsr #4
	movls	r0, #1
	movhi	r0, #0
	cmp	r1, #512
	orrhi	r0, r0, #1
	mul	r1, r1, ip
	cmp	ip, #512
	orrhi	r0, r0, #1
	cmp	r0, #0
	str	ip, [lr, #2576]
	str	r1, [lr, #2596]
	bne	.L245
	ldr	r8, [fp, #-68]
	ldr	r7, [r8, #124]
	ldr	r4, [r8, #120]
	cmp	r2, r4
	cmpeq	r3, r7
	beq	.L166
	ldr	r1, .L250+24
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r0, [r8, #2576]
	ldr	ip, [r8, #2572]
	mov	r3, r7
	mov	r2, r4
	ldr	r1, .L250+28
	str	r0, [sp, #4]
	mov	r0, #22
	str	ip, [sp]
	bl	dprint_vfmw
.L166:
	ldr	r3, [fp, #-68]
	ldr	r3, [r3, #2532]
	cmp	r3, #0
	bne	.L163
	ldr	r0, [fp, #-80]
	bl	VP8_init_frame.part.0
	b	.L163
.L192:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	strb	r0, [r3, #2516]
	b	.L193
.L243:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #128
	mov	r1, r6
	strb	r0, [r4, #2517]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldrb	r3, [r4, #2517]	@ zero_extendqisi2
	strb	r5, [r4, #2519]
	cmp	r3, #0
	uxtb	r3, r0
	strb	r3, [r4, #2518]
	bne	.L189
	mov	r2, #2
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	ldr	r2, [fp, #-68]
	ldrb	r3, [r2, #2518]	@ zero_extendqisi2
	strb	r0, [r2, #2519]
.L189:
	ldr	r2, [fp, #-68]
	cmp	r3, #0
	mov	r3, #0
	strb	r3, [r2, #2520]
	bne	.L190
	mov	r2, #2
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	ldr	r3, [fp, #-68]
	strb	r0, [r3, #2520]
.L190:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #128
	mov	r1, r6
	strb	r0, [r4, #2524]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	strb	r0, [r4, #2525]
	b	.L180
.L242:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2469]
	cmp	r0, #0
	beq	.L171
	add	r4, r3, #2496
	add	r5, r3, #2512
	add	r4, r4, #12
	mov	r8, r3
.L184:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	uxtb	r0, r0
	strb	r0, [r8, #2498]
	cmp	r0, #1
	beq	.L246
.L182:
	add	r4, r4, #1
	cmp	r4, r5
	bne	.L184
	ldr	r3, [fp, #-68]
	add	r4, r3, #2512
	add	r4, r4, #4
.L188:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2499]
	cmp	r0, #1
	beq	.L247
.L186:
	add	r5, r5, #1
	cmp	r5, r4
	bne	.L188
	b	.L171
.L169:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #128
	mov	r1, r6
	strb	r0, [r4, #2483]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	uxtb	r0, r0
	strb	r0, [r4, #2484]
	cmp	r0, #0
	bne	.L248
.L172:
	ldr	r3, [fp, #-68]
	ldrb	r3, [r3, #2483]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L176
	ldr	r3, .L250+4
	mov	r2, #3
	ldr	r5, [fp, #-68]
	mov	r1, #255
	ldr	r0, [fp, #-80]
	add	r4, r5, #2480
	ldr	r3, [r3, #48]
	add	r0, r0, #18
	add	r5, r5, #2480
	add	r4, r4, #6
	blx	r3
	add	r5, r5, #9
	b	.L178
.L177:
	add	r4, r4, #1
	cmp	r4, r5
	beq	.L176
.L178:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2489]
	cmp	r0, #1
	bne	.L177
	mov	r2, #8
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	strb	r0, [r4]
	b	.L177
.L246:
	mov	r2, #6
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #128
	mov	r1, r6
	strb	r0, [r4]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	uxtb	r0, r0
	strb	r0, [r8, #2480]
	cmp	r0, #1
	ldreqb	r3, [r4]	@ zero_extendqisi2
	rsbeq	r3, r3, #0
	streqb	r3, [r4]
	b	.L182
.L247:
	mov	r2, #6
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #128
	mov	r1, r6
	strb	r0, [r5]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #0
	ldrneb	r3, [r5]	@ zero_extendqisi2
	rsbne	r3, r3, #0
	strneb	r3, [r5]
	b	.L186
.L248:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	ldr	r8, [fp, #-68]
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, .L250+4
	add	r4, r8, #2480
	mov	r1, #0
	mov	r2, #8
	add	r4, r4, #13
	ldr	r3, [r3, #48]
	mov	r10, r1
	strb	r0, [r8, #2485]
	ldr	r0, [fp, #-80]
	add	r0, r0, #22
	blx	r3
.L173:
	sub	r9, r4, #4
	str	r4, [fp, #-64]
	b	.L175
.L174:
	ldr	r3, [fp, #-64]
	strb	r4, [r9, #1]!
	cmp	r9, r3
	beq	.L249
.L175:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	mov	r4, #0
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2468]
	cmp	r0, #1
	bne	.L174
	ldr	r2, [r5, r10, asl #2]
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #128
	mov	r1, r6
	mov	r8, r0
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	uxtb	r4, r8
	rsb	r8, r8, #0
	cmp	r0, #0
	uxtbne	r4, r8
	b	.L174
.L249:
	add	r10, r10, #1
	add	r4, r3, #4
	cmp	r10, #2
	bne	.L173
	b	.L172
.L245:
	ldr	r1, .L250+32
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L236
.L251:
	.align	2
.L250:
	.word	.LANCHOR0+1392
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1443
	.word	.LANCHOR0+2499
	.word	.LC8
	.word	.LC7
	.word	.LC10
	.word	.LC11
	.word	.LC9
	UNWIND(.fnend)
	.size	VP8_GetPictureHeader, .-VP8_GetPictureHeader
	.align	2
	.global	VP8_ArrangeVHBMem
	.type	VP8_ArrangeVHBMem, %function
VP8_ArrangeVHBMem:
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
	add	r4, r0, #4096
	mov	r5, r0
	ldr	r3, [r4, #1708]
	ldr	r2, [r4, #1704]
	cmp	r3, #31
	bls	.L254
	sub	r0, r2, #32
	movw	r1, #8160
	cmp	r3, #8192
	cmpls	r0, r1
	bhi	.L254
	ldr	r1, [r5]
	ldr	r0, [r1, #732]
	cmp	r0, #0
	ldr	r0, [r1, #28]
	bne	.L257
	cmp	r0, #25
	beq	.L281
.L258:
	mov	r6, #4
	mov	r7, r2
	mov	r8, r3
	mov	r9, r6
	mov	r10, #5
.L263:
	ldr	r3, .L283
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r5]
	str	r7, [fp, #-60]
	str	r8, [fp, #-56]
	ldr	r3, [r3, #28]
	str	r7, [fp, #-52]
	cmp	r3, #24
	str	r8, [fp, #-48]
	beq	.L269
	uxtb	r6, r6
	strb	r9, [fp, #-63]
	strb	r10, [fp, #-62]
.L274:
	add	r7, r5, #8192
	sub	r1, fp, #64
	strb	r6, [fp, #-61]
	ldr	r0, [r7, #368]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L270
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r7, #368]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L282
	cmp	r0, #0
	moveq	r0, #1
	streq	r0, [r4, #4064]
	beq	.L278
.L272:
	ldr	r1, .L283+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L278
.L254:
	ldr	r1, .L283+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
.L278:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L257:
	cmp	r0, #25
	bne	.L258
	ldr	r0, [r1, #692]
	ldr	ip, [r1, #696]
	cmp	r2, r0
	bhi	.L266
	cmp	r3, ip
	bhi	.L266
	ldr	r0, [r1, #720]
	mov	r7, r2
	ldr	r2, [r1, #716]
	mov	r8, r3
	cmp	r0, #0
	add	r9, r2, #2
	beq	.L276
	add	r6, r2, #1
	cmp	r6, #17
	movge	r6, #17
.L268:
	ldrb	r10, [r1, #740]	@ zero_extendqisi2
	b	.L263
.L270:
	ldr	r1, .L283+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L278
.L269:
	mov	r6, #1
	strb	r10, [fp, #-62]
	strb	r6, [fp, #-63]
	b	.L274
.L281:
	ldr	r7, [r1, #692]
	ldr	r8, [r1, #696]
	cmp	r2, r7
	bhi	.L260
	cmp	r3, r8
	bhi	.L260
	ldr	r0, [r4, #4064]
	cmp	r0, #1
	beq	.L278
	ldr	r2, [r1, #720]
	ldr	r3, [r1, #716]
	cmp	r2, #0
	add	r9, r3, #2
	beq	.L276
	add	r6, r3, #1
	cmp	r6, #17
	movge	r6, #17
	b	.L268
.L266:
	stmia	sp, {r0, ip}
	mov	r0, #0
	ldr	r1, .L283+16
	bl	dprint_vfmw
	mov	r0, #0
	b	.L278
.L276:
	mov	r6, #1
	b	.L268
.L260:
	stmia	sp, {r7, r8}
	mov	r0, #0
	ldr	r1, .L283+16
	bl	dprint_vfmw
	mov	r0, #0
	b	.L278
.L282:
	add	r0, r7, #16
	bl	ResetVoQueue
	b	.L272
.L284:
	.align	2
.L283:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	.LC12
	.word	.LC15
	.word	.LC13
	UNWIND(.fnend)
	.size	VP8_ArrangeVHBMem, .-VP8_ArrangeVHBMem
	.align	2
	.global	VP8_DecodeDecide
	.type	VP8_DecodeDecide, %function
VP8_DecodeDecide:
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
	add	r5, r0, #4096
	mov	r6, r0
	ldr	r4, [r5, #4064]
	cmp	r4, #0
	beq	.L311
	ldr	r3, [r5, #4056]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r3, [r0]
	ldr	r2, [r3, #8]
	bls	.L312
.L289:
	str	r2, [r5, #4056]
	cmp	r2, #4
	ldrls	pc, [pc, r2, asl #2]
	b	.L294
.L295:
	.word	.L293
	.word	.L293
	.word	.L290
	.word	.L292
	.word	.L293
.L313:
	ldr	r1, .L315
	mov	r0, #18
	bl	dprint_vfmw
.L292:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L312:
	cmp	r2, #4
	cmpne	r2, #1
	bhi	.L289
	add	r4, r0, #8192
	ldr	r1, .L315+4
	mov	r0, #2
	mov	r7, #0
	bl	dprint_vfmw
	ldr	r0, [r4, #368]
	mov	r2, #1
	ldr	r1, [r5, #4080]
	bl	FSP_ClearLogicFs
	ldr	r0, [r4, #368]
	mov	r2, #1
	ldr	r1, [r5, #4084]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r0, [r4, #368]
	ldr	r1, [r5, #4088]
	bl	FSP_ClearLogicFs
	str	r7, [r5, #4080]
	str	r7, [r5, #4084]
	str	r7, [r5, #4088]
	ldr	r0, [r4, #368]
	bl	FSP_GetNullLogicFs
	str	r7, [r5, #4060]
	str	r0, [r5, #4088]
	str	r0, [r5, #4084]
	str	r0, [r5, #4080]
	ldr	r3, [r6]
	ldr	r2, [r3, #8]
	b	.L289
.L311:
	ldr	r1, .L315+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L290:
	add	r7, r6, #8192
	ldr	r2, [r7, #4]
	cmp	r2, #0
	bne	.L313
.L291:
	ldr	r1, [r5, #4088]
	ldr	r0, [r7, #368]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L314
	ldr	r3, [r7, #4]
	cmp	r3, #0
	beq	.L300
	ldr	r3, [r6]
	ldr	r2, [r4, #152]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L300
	ldr	r1, .L315+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L293:
	add	r7, r6, #8192
	ldr	r3, [r7, #4]
	cmp	r3, #0
	beq	.L291
	ldr	r3, [r5, #4060]
	cmp	r3, #0
	bne	.L291
	ldr	r2, .L315+16
	mov	r0, #18
	ldr	r1, .L315+20
	bl	dprint_vfmw
	b	.L292
.L294:
	ldr	r1, .L315+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L300:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L314:
	movw	r3, #1486
	ldr	r2, .L315+28
	ldr	r1, .L315+32
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L316:
	.align	2
.L315:
	.word	.LC18
	.word	.LC17
	.word	.LC16
	.word	.LC23
	.word	.LC19
	.word	.LC20
	.word	.LC21
	.word	.LANCHOR0+2456
	.word	.LC22
	UNWIND(.fnend)
	.size	VP8_DecodeDecide, .-VP8_DecodeDecide
	.align	2
	.global	VP8_GetImageBuffer
	.type	VP8_GetImageBuffer, %function
VP8_GetImageBuffer:
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
	add	r6, r0, #8192
	add	r5, r0, #4096
	mov	r7, r0
	mov	r1, #1
	ldr	r0, [r6, #368]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r5, #4092]
	blt	.L323
	mov	r1, r0
	ldr	r0, [r6, #368]
	bl	FSP_GetLogicFs
	subs	r4, r0, #0
	beq	.L324
	ldr	r2, [r5, #4092]
	mov	r0, #18
	ldr	r1, .L325
	bl	dprint_vfmw
	ldr	r2, [r4, #28]
	cmp	r2, #0
	beq	.L321
	ldr	r0, [r4, #32]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r0, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L325+4
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L323:
	ldr	r1, .L325+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r5, #4080]
	ldr	r0, [r6, #368]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	ldr	r1, [r5, #4084]
	ldr	r0, [r6, #368]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #4088]
	mov	r4, #0
	ldr	r0, [r6, #368]
	bl	FSP_ClearLogicFs
	str	r4, [r5, #4080]
	str	r4, [r5, #4084]
	str	r4, [r5, #4088]
	ldr	r0, [r6, #368]
	bl	FSP_GetNullLogicFs
	str	r4, [r5, #4060]
	add	r1, r6, #16
	str	r0, [r5, #4088]
	str	r0, [r5, #4084]
	str	r0, [r5, #4080]
	ldr	r0, [r6, #368]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L324:
	movw	r2, #1542
	ldr	r1, .L325+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L321:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L326:
	.align	2
.L325:
	.word	.LC26
	.word	.LC27
	.word	.LC24
	.word	.LC25
	UNWIND(.fnend)
	.size	VP8_GetImageBuffer, .-VP8_GetImageBuffer
	.align	2
	.global	VP8_Set_DecParam
	.type	VP8_Set_DecParam, %function
VP8_Set_DecParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 88
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	ldr	r7, .L368
	mov	r10, r0
	add	r3, r0, #8
	ldr	ip, [r10, #3184]
	add	r8, r0, #4096
	str	r3, [fp, #-116]
	movw	r2, #3164
	mov	r1, #0
	mov	r0, r3
	ldr	r3, [r7, #48]
	add	r5, r10, #8192
	str	ip, [fp, #-120]
	blx	r3
	ldr	r3, [r8, #1656]
	str	r3, [r10, #2808]
	ldr	r3, [r5, #8]
	str	r3, [r10, #2812]
	ldr	r3, [r8, #1696]
	str	r3, [r10, #2796]
	ldr	r3, [r8, #1700]
	str	r3, [r10, #2800]
	ldr	r3, [r8, #1684]
	str	r3, [r10, #2816]
	ldr	r3, [r8, #1688]
	str	r3, [r10, #2820]
	ldrb	r3, [r8, #1653]	@ zero_extendqisi2
	strb	r3, [r10, #2760]
	ldr	r3, [r8, #1672]
	strb	r3, [r10, #2761]
	ldrb	r3, [r8, #1605]	@ zero_extendqisi2
	strb	r3, [r10, #2762]
	ldrb	r3, [r8, #1606]	@ zero_extendqisi2
	strb	r3, [r10, #2763]
	ldrb	r3, [r8, #1607]	@ zero_extendqisi2
	strb	r3, [r10, #2764]
	ldrb	r3, [r8, #1609]	@ zero_extendqisi2
	strb	r3, [r10, #2765]
	ldrb	r3, [r8, #1594]	@ zero_extendqisi2
	strb	r3, [r10, #2766]
	ldr	r3, [r8, #1736]
	strb	r3, [r10, #2768]
	ldrb	r3, [r8, #1602]	@ zero_extendqisi2
	strb	r3, [r10, #2770]
	ldrb	r3, [r8, #1603]	@ zero_extendqisi2
	strb	r3, [r10, #2771]
	ldr	r3, [r8, #4068]
	strb	r3, [r10, #2769]
	ldr	r3, [r8, #4072]
	strb	r3, [r10, #2772]
	ldrb	r3, [r8, #1595]	@ zero_extendqisi2
	strb	r3, [r10, #2767]
	ldrb	r3, [r8, #1597]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2773]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2774]
	ldrb	r3, [r8, #1598]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2775]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2776]
	ldrb	r3, [r8, #1599]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2777]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2778]
	ldrb	r3, [r8, #1600]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2779]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2780]
	ldrb	r3, [r8, #1601]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2781]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2782]
	ldrb	r3, [r8, #1650]	@ zero_extendqisi2
	strb	r3, [r10, #2783]
	ldrb	r3, [r8, #1651]	@ zero_extendqisi2
	strb	r3, [r10, #2784]
	ldrb	r3, [r8, #1652]	@ zero_extendqisi2
	strb	r3, [r10, #2785]
	ldr	r3, [r8, #1744]
	str	r3, [r10, #2792]
	ldr	r3, [r8, #1740]
	strb	r3, [r10, #2787]
	ldr	r3, [r8, #1748]
	strb	r3, [r10, #2788]
	ldr	r3, [r8, #4076]
	str	r3, [r10, #3148]
	ldr	r1, [r8, #4092]
	ldr	r0, [r5, #368]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #4080]
	mov	r4, r0
	ldr	r0, [r5, #368]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #4084]
	mov	r6, r0
	ldr	r0, [r5, #368]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #4088]
	mov	r9, r0
	ldr	r0, [r5, #368]
	bl	FSP_GetLogicFs
	cmp	r6, #0
	cmpne	r4, #0
	beq	.L328
	cmp	r0, #0
	cmpne	r9, #0
	beq	.L328
	ldr	r5, [r4, #28]
	cmp	r5, #0
	beq	.L367
	ldr	r3, [r5, #8]
	add	r5, r10, #5696
	mov	lr, r5
	mov	ip, r5
	str	r3, [r10, #3128]
	mov	r1, r5
	ldr	r3, [r4, #8]
	add	lr, lr, #17
	add	ip, ip, #31
	add	r1, r1, #45
	str	r3, [r10, #3144]
	ldr	r3, [r6, #28]
	cmp	r3, #0
	ldreq	r3, [r4, #28]
	ldr	r3, [r3, #8]
	str	r3, [r10, #3136]
	ldr	r3, [r9, #28]
	cmp	r3, #0
	ldreq	r3, [r4, #28]
	ldr	r3, [r3, #8]
	str	r3, [r10, #3132]
	ldr	r3, [r0, #28]
	mov	r0, r5
	add	r5, r5, #13
	add	r0, r0, #35
	cmp	r3, #0
	ldreq	r3, [r4, #28]
	ldr	r3, [r3, #8]
	str	r10, [fp, #-124]
	str	r3, [r10, #3140]
	ldr	r3, [r4, #32]
	ldr	r2, [r3, #24]
	mov	r3, r10
	str	r2, [r8, #4052]
	str	r2, [r10, #2804]
	mov	r2, #0
	ldr	r6, [r4, #32]
	ldr	r6, [r6, #60]
	str	r6, [r10, #3160]
	ldr	r6, [r4, #32]
	ldr	r6, [r6, #44]
	str	r6, [r10, #3164]
	ldr	r4, [r4, #32]
	ldr	r4, [r4, #48]
	str	r4, [r10, #3168]
.L338:
	ldrsb	r4, [r5, #1]!
	add	r2, r2, #1
	cmp	r2, #4
	add	r3, r3, #4
	str	r4, [r3, #3044]
	ldrsb	r4, [lr, #1]!
	str	r4, [r3, #3060]
	ldrsb	r4, [ip, #1]!
	str	r4, [r3, #3076]
	ldrsb	r4, [r0, #1]!
	str	r4, [r3, #3092]
	ldrb	r4, [r1, #1]!	@ zero_extendqisi2
	str	r4, [r3, #3108]
	bne	.L338
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	ldr	r0, [fp, #-116]
	blx	r3
	ldrb	r3, [r8, #1653]	@ zero_extendqisi2
	add	ip, r10, #1200
	mov	r2, #16
	mov	r1, #0
	add	r0, r10, #24
	strb	r3, [r10, #8]
	add	r3, ip, #8
	add	ip, r10, #6976
	mov	r9, r3
	ldrb	r3, [r8, #1610]	@ zero_extendqisi2
	add	ip, ip, #38
	strb	r3, [r10, #9]
	mov	r4, ip
	ldrb	r3, [r8, #1611]	@ zero_extendqisi2
	add	ip, r10, #2736
	add	ip, ip, #8
	str	ip, [fp, #-112]
	strb	r3, [r10, #10]
	ldrb	r3, [r8, #1612]	@ zero_extendqisi2
	strb	r3, [r10, #11]
	ldrb	r3, [r8, #1650]	@ zero_extendqisi2
	strb	r3, [r10, #12]
	ldrb	r3, [r8, #1651]	@ zero_extendqisi2
	strb	r3, [r10, #13]
	ldrb	r3, [r8, #1652]	@ zero_extendqisi2
	strb	r3, [r10, #14]
	ldr	r3, [r7, #48]
	blx	r3
	ldrb	r3, [r8, #2910]	@ zero_extendqisi2
	mov	r2, #16
	mov	r1, #0
	add	r0, r10, #40
	strb	r3, [r10, #24]
	ldrb	r3, [r8, #2911]	@ zero_extendqisi2
	strb	r3, [r10, #25]
	ldrb	r3, [r8, #2912]	@ zero_extendqisi2
	strb	r3, [r10, #26]
	ldrb	r3, [r8, #2913]	@ zero_extendqisi2
	strb	r3, [r10, #27]
	ldrb	r3, [r8, #2914]	@ zero_extendqisi2
	strb	r3, [r10, #28]
	ldrb	r3, [r8, #2915]	@ zero_extendqisi2
	strb	r3, [r10, #29]
	ldrb	r3, [r8, #2916]	@ zero_extendqisi2
	strb	r3, [r10, #30]
	ldr	r3, [r7, #48]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	add	r0, r10, #56
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	add	r0, r10, #712
	blx	r3
	ldrb	r0, [r8, #3975]	@ zero_extendqisi2
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	strb	r0, [r10, #712]
	ldrb	r0, [r8, #3974]	@ zero_extendqisi2
	strb	r0, [r10, #713]
	ldrb	r0, [r8, #3976]	@ zero_extendqisi2
	strb	r0, [r10, #714]
	ldrb	r0, [r8, #3977]	@ zero_extendqisi2
	strb	r0, [r10, #715]
	ldrb	r0, [r8, #3978]	@ zero_extendqisi2
	strb	r0, [r10, #716]
	ldrb	r0, [r8, #3979]	@ zero_extendqisi2
	strb	r0, [r10, #717]
	ldrb	r0, [r8, #3980]	@ zero_extendqisi2
	strb	r0, [r10, #718]
	ldrb	r0, [r8, #3981]	@ zero_extendqisi2
	strb	r0, [r10, #719]
	add	r0, r10, #728
	ldrb	ip, [r8, #3982]	@ zero_extendqisi2
	strb	ip, [r10, #720]
	blx	r3
	ldrb	r0, [r8, #3975]	@ zero_extendqisi2
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	strb	r0, [r10, #728]
	ldrb	r0, [r8, #3983]	@ zero_extendqisi2
	strb	r0, [r10, #729]
	ldrb	r0, [r8, #3984]	@ zero_extendqisi2
	strb	r0, [r10, #730]
	ldrb	r0, [r8, #3985]	@ zero_extendqisi2
	strb	r0, [r10, #731]
	ldrb	r0, [r8, #3986]	@ zero_extendqisi2
	strb	r0, [r10, #732]
	ldrb	r0, [r8, #3987]	@ zero_extendqisi2
	strb	r0, [r10, #733]
	ldrb	r0, [r8, #3988]	@ zero_extendqisi2
	strb	r0, [r10, #734]
	ldrb	r0, [r8, #3989]	@ zero_extendqisi2
	strb	r0, [r10, #735]
	ldrb	r0, [r8, #3990]	@ zero_extendqisi2
	strb	r0, [r10, #736]
	ldrb	r0, [r8, #3991]	@ zero_extendqisi2
	strb	r0, [r10, #737]
	add	r0, r10, #744
	ldrb	ip, [r8, #3992]	@ zero_extendqisi2
	strb	ip, [r10, #738]
	blx	r3
	ldrb	r0, [r8, #3994]	@ zero_extendqisi2
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	strb	r0, [r10, #744]
	ldrb	r0, [r8, #3993]	@ zero_extendqisi2
	strb	r0, [r10, #745]
	ldrb	r0, [r8, #3995]	@ zero_extendqisi2
	strb	r0, [r10, #746]
	ldrb	r0, [r8, #3996]	@ zero_extendqisi2
	strb	r0, [r10, #747]
	ldrb	r0, [r8, #3997]	@ zero_extendqisi2
	strb	r0, [r10, #748]
	ldrb	r0, [r8, #3998]	@ zero_extendqisi2
	strb	r0, [r10, #749]
	ldrb	r0, [r8, #3999]	@ zero_extendqisi2
	strb	r0, [r10, #750]
	ldrb	r0, [r8, #4000]	@ zero_extendqisi2
	strb	r0, [r10, #751]
	add	r0, r10, #760
	ldrb	ip, [r8, #4001]	@ zero_extendqisi2
	strb	ip, [r10, #752]
	blx	r3
	ldrb	r3, [r8, #3994]	@ zero_extendqisi2
	str	r10, [fp, #-128]
	str	r8, [fp, #-132]
	strb	r3, [r10, #760]
	ldrb	r3, [r8, #4002]	@ zero_extendqisi2
	strb	r3, [r10, #761]
	ldrb	r3, [r8, #4003]	@ zero_extendqisi2
	strb	r3, [r10, #762]
	ldrb	r3, [r8, #4004]	@ zero_extendqisi2
	strb	r3, [r10, #763]
	ldrb	r3, [r8, #4005]	@ zero_extendqisi2
	strb	r3, [r10, #764]
	ldrb	r3, [r8, #4006]	@ zero_extendqisi2
	strb	r3, [r10, #765]
	ldrb	r3, [r8, #4007]	@ zero_extendqisi2
	strb	r3, [r10, #766]
	ldrb	r3, [r8, #4008]	@ zero_extendqisi2
	strb	r3, [r10, #767]
	ldrb	r3, [r8, #4009]	@ zero_extendqisi2
	strb	r3, [r10, #768]
	ldrb	r3, [r8, #4010]	@ zero_extendqisi2
	strb	r3, [r10, #769]
	ldrb	r3, [r8, #4011]	@ zero_extendqisi2
	strb	r3, [r10, #770]
	mov	r10, r4
.L339:
	sub	r6, r9, #384
	mov	r8, r10
.L343:
	sub	r4, r6, #48
	mov	r5, r8
.L340:
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	mov	r0, r4
	blx	r3
	mov	r1, r5
	mov	r0, r4
	ldr	r3, [r7, #52]
	mov	r2, #11
	add	r4, r4, #16
	blx	r3
	cmp	r6, r4
	add	r5, r5, #11
	bne	.L340
	add	r6, r6, #48
	add	r8, r8, #33
	cmp	r9, r6
	bne	.L343
	ldr	r3, [fp, #-112]
	add	r9, r9, #384
	add	r10, r10, #264
	cmp	r9, r3
	bne	.L339
	ldr	r8, [fp, #-132]
	ldr	r9, [fp, #-120]
	ldr	r10, [fp, #-128]
	ldr	r2, [r8, #1656]
	ldr	r3, [r9, #4]
	add	r7, r10, #3184
	add	r7, r7, #4
	cmp	r2, #0
	bic	r3, r3, #15
	sub	r3, r3, #16
	mov	r0, r7
	str	r3, [r10, #2824]
	moveq	r4, #10
	movne	r4, #3
	ldr	r5, [r8, #1668]
	bl	BsPos
	add	r5, r4, r5
	mov	r5, r5, asl #3
	rsb	r0, r0, r5
	str	r0, [r10, #2828]
	mov	r0, r7
	ldr	r6, [r9, #4]
	bl	BsPos
	and	r6, r6, #15
	add	r6, r6, #16
	cmp	r0, #0
	add	r5, r0, #7
	movge	r5, r0
	mov	r0, r7
	bl	BsPos
	add	r5, r6, r5, asr #3
	and	r1, r5, #15
	mov	ip, #0
	bic	r5, r5, #15
	str	ip, [r10, #2840]
	str	r5, [r10, #2836]
	str	ip, [r10, #2844]
	str	ip, [r10, #2848]
	mov	r3, r0, asr #31
	mov	r3, r3, lsr #29
	add	r2, r0, r3
	and	r2, r2, #7
	rsb	r3, r3, r2
	add	r3, r3, r1, lsl #3
	str	r3, [r10, #2832]
	ldrb	r5, [r8, #1605]	@ zero_extendqisi2
	mov	r3, #1
	ldr	r1, [r8, #1668]
	mov	r5, r3, asl r5
	ldr	r2, [r9, #8]
	ldr	r0, [r9]
	add	r3, r4, r1
	uxtb	r5, r5
	rsb	r2, r4, r2
	cmp	r5, #1
	add	r0, r0, r3
	subhi	r4, r5, #1
	str	r3, [fp, #-112]
	movls	r4, r0
	str	r5, [r10, #2852]
	addhi	r4, r4, r4, lsl #1
	addhi	r4, r0, r4
	cmp	r5, #0
	ble	.L354
	rsb	r3, r5, #1
	sub	lr, fp, #76
	sub	r7, r5, #1
	mov	ip, #0
	add	r3, r3, r3, lsl #1
	mov	r6, lr
	rsb	r3, r1, r3
	add	r8, r3, r2
.L349:
	cmp	ip, r7
	add	ip, ip, #1
	rsbge	r3, r4, r0
	add	r0, r0, #3
	ldrltb	r3, [r0, #-2]	@ zero_extendqisi2
	addge	r3, r3, r8
	ldrltb	r2, [r0, #-3]	@ zero_extendqisi2
	ldrltb	r1, [r0, #-1]	@ zero_extendqisi2
	addlt	r3, r2, r3, lsl #8
	addlt	r3, r3, r1, lsl #16
	cmp	ip, r5
	str	r3, [r6], #4
	add	r4, r4, r3
	bne	.L349
	ldr	r3, [fp, #-120]
	add	r9, r10, #2848
	ldr	r1, [fp, #-112]
	add	r8, r10, #2880
	add	r6, r10, #2944
	ldr	r0, [fp, #-124]
	ldr	r2, [r3, #4]
	add	r3, r7, r7, lsl #1
	add	r7, r10, #2912
	add	r9, r9, #4
	and	r2, r2, #15
	add	r8, r8, #4
	add	r3, r3, r2
	add	r7, r7, #4
	add	r3, r3, r1
	mov	r2, #0
	add	r6, r6, #4
	sub	r1, fp, #108
	mov	r4, r2
	str	r3, [fp, #-120]
	str	r10, [fp, #-112]
.L353:
	cmp	r2, #0
	add	r2, r2, #1
	add	r1, r1, #4
	add	r0, r0, #4
	ldreq	r3, [fp, #-120]
	ldrne	r3, [r1, #-8]
	ldrne	ip, [lr, #-4]
	streq	r3, [fp, #-108]
	ldreq	r3, [r1, #-4]
	addne	r3, ip, r3
	ldr	r10, [lr], #4
	strne	r3, [r1, #-4]
	and	ip, r3, #15
	cmp	r2, r5
	bic	r3, r3, #15
	mov	r10, r10, asl #3
	mov	ip, ip, asl #3
	str	r10, [r9, #4]!
	add	r3, r3, #16
	str	ip, [r8, #4]!
	str	r3, [r7, #4]!
	str	r4, [r6, #4]!
	str	r4, [r0, #2980]
	str	r4, [r0, #3012]
	bne	.L353
	ldr	r10, [fp, #-112]
.L354:
	ldr	r3, [r10]
	mov	r0, #1
	ldr	r2, [fp, #-116]
	str	r2, [r10, #4]
	ldr	r2, [r3, #600]
	str	r2, [r10, #3152]
	ldr	r3, [r3, #652]
	str	r3, [r10, #3156]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L328:
	ldr	r1, .L368+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
.L361:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L367:
	ldr	r1, .L368+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L361
.L369:
	.align	2
.L368:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	.word	.LC29
	UNWIND(.fnend)
	.size	VP8_Set_DecParam, .-VP8_Set_DecParam
	.align	2
	.global	VP8_Update_PictHeader
	.type	VP8_Update_PictHeader, %function
VP8_Update_PictHeader:
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
	ldrb	r3, [r0, #2521]	@ zero_extendqisi2
	add	r5, r0, #2464
	mov	r4, r0
	add	r5, r5, #4
	cmp	r3, #0
	add	r7, r0, #8
	ldr	r6, .L374
	bne	.L371
	add	r0, r0, #3776
	movw	r2, #1149
	add	r0, r0, #1
	add	r1, r5, #160
	ldr	r3, [r6, #52]
	blx	r3
.L371:
	ldr	r3, [r6, #52]
	movw	r2, #2460
	mov	r1, r5
	mov	r0, r7
	blx	r3
	ldr	r2, [r4, #2532]
	add	r3, r4, #4096
	str	r2, [r3, #884]
	ldr	r2, [r4, #2612]
	str	r2, [r3, #848]
	ldrb	r2, [r4, #2479]	@ zero_extendqisi2
	str	r2, [r3, #852]
	ldrb	r3, [r4, #2516]	@ zero_extendqisi2
	strb	r3, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L375:
	.align	2
.L374:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VP8_Update_PictHeader, .-VP8_Update_PictHeader
	.align	2
	.global	VP8DEC_Decode
	.type	VP8DEC_Decode, %function
VP8DEC_Decode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	moveq	r8, #1
	movne	r8, #0
	beq	.L416
	ldr	r3, [r1]
	str	r3, [r0, #3172]
	ldr	r2, [r1, #12]
	str	r2, [r0, #3176]
	ldr	r2, [r1, #16]
	cmp	r2, #2
	str	r2, [r0, #3180]
	ble	.L417
	add	r5, r0, #3184
	add	r7, r0, #3216
	add	r5, r5, #4
	mov	r1, r3
	add	r7, r7, #4
	mov	r0, r5
	bl	BsInit
	add	r3, r4, #3168
	add	r3, r3, #4
	mov	r0, r5
	mov	r1, r7
	ldr	r2, [r4, #3180]
	str	r3, [r4, #3184]
	bl	VP8_GetPictureHeader
	cmp	r0, #1
	bne	.L418
	add	r5, r4, #4096
	ldr	r3, [r5, #4064]
	cmp	r3, #0
	bne	.L419
.L381:
	ldr	r9, .L424
	ldr	r8, [r9]
	cmp	r8, #0
	addeq	r6, r4, #8192
	beq	.L383
	ldr	r1, [r4, #3336]
	add	r6, r4, #8192
	ldr	r0, [r5, #1700]
	mov	r3, #8
	ldr	lr, [r4, #3332]
	sub	r2, fp, #44
	ldr	ip, [r5, #1696]
	strh	r1, [fp, #-42]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-38]	@ movhi
	strh	lr, [fp, #-44]	@ movhi
	strh	ip, [fp, #-40]	@ movhi
	ldr	r0, [r6, #368]
	blx	r8
.L383:
	ldr	r0, [r6, #368]
	bl	FSP_GetFspType
	subs	ip, r0, #0
	beq	.L420
.L384:
	mov	r2, #1
	ldr	r1, [r5, #4080]
	ldr	r0, [r6, #368]
	mov	r8, #0
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #4084]
	add	r9, r4, #8192
	ldr	r0, [r6, #368]
	add	r9, r9, #16
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #4088]
	ldr	r0, [r6, #368]
	bl	FSP_ClearLogicFs
	str	r8, [r5, #4080]
	str	r8, [r5, #4084]
	str	r8, [r5, #4088]
	ldr	r0, [r6, #368]
	bl	FSP_GetNullLogicFs
	str	r8, [r5, #4060]
	mov	r1, r9
	str	r0, [r5, #4088]
	str	r0, [r5, #4084]
	str	r0, [r5, #4080]
	ldr	r0, [r6, #368]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [r5, #1696]
	ldr	r3, [r5, #1700]
	cmp	r2, #512
	bhi	.L391
	cmp	r3, #512
	bhi	.L391
	ldr	r3, [r4]
	ldr	r2, [r3, #732]
	cmp	r2, #0
	bne	.L393
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L421
.L393:
	mov	r0, r4
	bl	VP8_ArrangeVHBMem
	cmp	r0, #1
	bne	.L422
.L382:
	mov	r0, r4
	bl	VP8_DecodeDecide
	cmp	r0, #1
	mov	r6, r0
	beq	.L394
	ldr	r1, .L424+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L378
.L417:
	ldr	r1, .L424+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r8
.L378:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L416:
	movw	r2, #1891
	ldr	r1, .L424+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L419:
	ldr	r2, [r4, #3332]
	ldr	r3, [r5, #1696]
	cmp	r2, r3
	bne	.L381
	ldr	r2, [r4, #3336]
	ldr	r3, [r5, #1700]
	cmp	r2, r3
	bne	.L381
	b	.L382
.L420:
	sub	r3, fp, #36
	sub	r2, fp, #48
	sub	r1, fp, #52
	ldr	r0, [r6, #368]
	str	ip, [r3, #-8]!
	str	ip, [fp, #-52]
	str	ip, [fp, #-48]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4]
	ldr	r2, [r3, #732]
	cmp	r2, #1
	bne	.L384
	ldr	r3, [fp, #-44]
	cmp	r3, #0
	bgt	.L387
	ldr	r3, [fp, #-48]
	cmp	r3, #32
	bgt	.L387
	ldr	r8, [r4, #4]
	cmp	r8, #0
	bne	.L387
	ldr	r3, [r4, #3332]
	cmp	r3, #0
	beq	.L384
	ldr	r1, [r5, #1700]
	ldr	r0, [r6, #372]
	cmp	r1, r0
	beq	.L384
	ldr	r0, [r5, #1696]
	ldr	ip, [r6, #376]
	cmp	r0, ip
	beq	.L384
	stmib	sp, {r0, r1}
	mov	r0, r2
	ldr	ip, [r4, #3336]
	ldr	r1, .L424+16
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #1700]
	ldr	r9, [r9]
	str	r3, [r6, #372]
	cmp	r9, #0
	ldr	r3, [r5, #1696]
	str	r3, [r6, #376]
	beq	.L384
	mov	r3, r8
	mov	r2, r8
	mov	r1, #120
	ldr	r0, [r6, #368]
	blx	r9
	b	.L384
.L391:
	ldr	r1, .L424+20
	mov	r0, #18
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L418:
	ldr	r1, .L424+24
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L422:
	ldr	r1, .L424+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L378
.L421:
	ldr	r3, [r5, #4064]
	cmp	r3, #0
	bne	.L393
	mov	r0, r9
	bl	ResetVoQueue
	b	.L393
.L394:
	mov	r0, r4
	bl	VP8_GetImageBuffer
	cmp	r0, #1
	beq	.L395
	mov	r0, r6
	ldr	r1, .L424+32
	bl	dprint_vfmw
	mov	r0, #0
	b	.L378
.L395:
	add	r6, r4, #8192
	ldr	r1, [r5, #4092]
	ldr	r0, [r6, #368]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L423
	ldr	r3, [r4]
	add	ip, r8, #592
	add	lr, r8, #608
	mov	r1, #0
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
	str	lr, [r8]
	ldr	lr, [r4]
	ldr	lr, [lr, #116]
	str	lr, [r8, #4]
	ldr	lr, [r4]
	ldr	lr, [lr, #120]
	str	lr, [r8, #8]
	ldr	lr, [r4]
	ldr	lr, [lr, #136]
	str	r1, [r8, #52]
	ldr	r1, .L424+36
	str	lr, [r8, #12]
	ldr	lr, [r4]
	strd	r2, [lr, #64]
	ldrd	r8, [ip]
	ldrd	r2, [ip, #-8]
	strd	r8, [sp]
	bl	dprint_vfmw
	ldr	r2, [r6, #4]
	cmp	r2, #0
	bne	.L397
	ldr	r1, [r5, #4084]
	ldr	r3, [r5, #4092]
	cmp	r1, r3
	beq	.L398
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
	ldr	r3, [r5, #4092]
.L398:
	ldr	r1, [r5, #4088]
	cmp	r1, r3
	beq	.L399
	mov	r2, #0
	ldr	r0, [r6, #368]
	bl	FSP_SetRef
	ldr	r3, [r5, #4092]
.L399:
	ldr	r1, [r5, #4080]
	cmp	r1, r3
	beq	.L400
	ldr	r0, [r6, #368]
	mov	r2, #0
	bl	FSP_SetRef
.L400:
	mov	r3, #0
	str	r3, [r5, #4060]
.L397:
	mov	r0, r4
	bl	VP8_Set_DecParam
	mov	r0, r7
	bl	VP8_Update_PictHeader
	mov	r0, #0
	b	.L378
.L387:
	mvn	r0, #1
	b	.L378
.L423:
	movw	r2, #2013
	ldr	r1, .L424+40
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r8
	b	.L378
.L425:
	.align	2
.L424:
	.word	g_event_report
	.word	.LC35
	.word	.LC30
	.word	.LC1
	.word	.LC32
	.word	.LC33
	.word	.LC31
	.word	.LC34
	.word	.LC36
	.word	.LC37
	.word	.LC25
	UNWIND(.fnend)
	.size	VP8DEC_Decode, .-VP8DEC_Decode
	.align	2
	.global	VP8DEC_RecycleImage
	.type	VP8DEC_RecycleImage, %function
VP8DEC_RecycleImage:
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
	beq	.L430
	add	r4, r4, #8192
	mov	r2, #0
	ldr	r0, [r4, #368]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #368]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L429
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #368]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #368]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L429:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L430:
	mov	r2, #2064
	ldr	r1, .L431
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L432:
	.align	2
.L431:
	.word	.LC1
	UNWIND(.fnend)
	.size	VP8DEC_RecycleImage, .-VP8DEC_RecycleImage
	.align	2
	.global	VP8DEC_GetRemainImg
	.type	VP8DEC_GetRemainImg, %function
VP8DEC_GetRemainImg:
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
	beq	.L437
	add	r0, r4, #8192
	add	r0, r0, #16
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	GetVoLastImageID
.L437:
	movw	r2, #2084
	ldr	r1, .L438
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L439:
	.align	2
.L438:
	.word	.LC1
	UNWIND(.fnend)
	.size	VP8DEC_GetRemainImg, .-VP8DEC_GetRemainImg
	.align	2
	.global	VP8DEC_GetImageBuffer
	.type	VP8DEC_GetImageBuffer, %function
VP8DEC_GetImageBuffer:
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
	subs	r5, r0, #0
	beq	.L447
	add	r4, r5, #8192
	ldr	r0, [r4, #368]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #368]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L448
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L448:
	ldr	r0, [r4, #368]
	add	r1, r4, #16
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L447:
	movw	r2, #2093
	ldr	r1, .L449
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L450:
	.align	2
.L449:
	.word	.LC1
	UNWIND(.fnend)
	.size	VP8DEC_GetImageBuffer, .-VP8DEC_GetImageBuffer
	.global	default_uv_mode_prob
	.global	default_ymode_prob
	.global	VP8_VFMWBITREADER_NORM
	.global	vp8_mv_update_probs
	.global	vp8_default_mv_context
	.global	vp8_coef_update_probs
	.global	default_coef_probs
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	vp8_default_mv_context, %object
	.size	vp8_default_mv_context, 38
vp8_default_mv_context:
	.byte	-94
	.byte	-128
	.byte	-31
	.byte	-110
	.byte	-84
	.byte	-109
	.byte	-42
	.byte	39
	.byte	-100
	.byte	-128
	.byte	-127
	.byte	-124
	.byte	75
	.byte	-111
	.byte	-78
	.byte	-50
	.byte	-17
	.byte	-2
	.byte	-2
	.byte	-92
	.byte	-128
	.byte	-52
	.byte	-86
	.byte	119
	.byte	-21
	.byte	-116
	.byte	-26
	.byte	-28
	.byte	-128
	.byte	-126
	.byte	-126
	.byte	74
	.byte	-108
	.byte	-76
	.byte	-53
	.byte	-20
	.byte	-2
	.byte	-2
	.space	2
	.type	default_coef_probs, %object
	.size	default_coef_probs, 1056
default_coef_probs:
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-3
	.byte	-120
	.byte	-2
	.byte	-1
	.byte	-28
	.byte	-37
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-67
	.byte	-127
	.byte	-14
	.byte	-1
	.byte	-29
	.byte	-43
	.byte	-1
	.byte	-37
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	106
	.byte	126
	.byte	-29
	.byte	-4
	.byte	-42
	.byte	-47
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	98
	.byte	-8
	.byte	-1
	.byte	-20
	.byte	-30
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-75
	.byte	-123
	.byte	-18
	.byte	-2
	.byte	-35
	.byte	-22
	.byte	-1
	.byte	-102
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	78
	.byte	-122
	.byte	-54
	.byte	-9
	.byte	-58
	.byte	-76
	.byte	-1
	.byte	-37
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-71
	.byte	-7
	.byte	-1
	.byte	-13
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-72
	.byte	-106
	.byte	-9
	.byte	-1
	.byte	-20
	.byte	-32
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	77
	.byte	110
	.byte	-40
	.byte	-1
	.byte	-20
	.byte	-26
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	101
	.byte	-5
	.byte	-1
	.byte	-15
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-86
	.byte	-117
	.byte	-15
	.byte	-4
	.byte	-20
	.byte	-47
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	37
	.byte	116
	.byte	-60
	.byte	-13
	.byte	-28
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-52
	.byte	-2
	.byte	-1
	.byte	-11
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-49
	.byte	-96
	.byte	-6
	.byte	-1
	.byte	-18
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	102
	.byte	103
	.byte	-25
	.byte	-1
	.byte	-45
	.byte	-85
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-104
	.byte	-4
	.byte	-1
	.byte	-16
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-79
	.byte	-121
	.byte	-13
	.byte	-1
	.byte	-22
	.byte	-31
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	80
	.byte	-127
	.byte	-45
	.byte	-1
	.byte	-62
	.byte	-32
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-10
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-58
	.byte	35
	.byte	-19
	.byte	-33
	.byte	-63
	.byte	-69
	.byte	-94
	.byte	-96
	.byte	-111
	.byte	-101
	.byte	62
	.byte	-125
	.byte	45
	.byte	-58
	.byte	-35
	.byte	-84
	.byte	-80
	.byte	-36
	.byte	-99
	.byte	-4
	.byte	-35
	.byte	1
	.byte	68
	.byte	47
	.byte	-110
	.byte	-48
	.byte	-107
	.byte	-89
	.byte	-35
	.byte	-94
	.byte	-1
	.byte	-33
	.byte	-128
	.byte	1
	.byte	-107
	.byte	-15
	.byte	-1
	.byte	-35
	.byte	-32
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-72
	.byte	-115
	.byte	-22
	.byte	-3
	.byte	-34
	.byte	-36
	.byte	-1
	.byte	-57
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	81
	.byte	99
	.byte	-75
	.byte	-14
	.byte	-80
	.byte	-66
	.byte	-7
	.byte	-54
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	-127
	.byte	-24
	.byte	-3
	.byte	-42
	.byte	-59
	.byte	-14
	.byte	-60
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	99
	.byte	121
	.byte	-46
	.byte	-6
	.byte	-55
	.byte	-58
	.byte	-1
	.byte	-54
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	23
	.byte	91
	.byte	-93
	.byte	-14
	.byte	-86
	.byte	-69
	.byte	-9
	.byte	-46
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	-56
	.byte	-10
	.byte	-1
	.byte	-22
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	109
	.byte	-78
	.byte	-15
	.byte	-1
	.byte	-25
	.byte	-11
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	44
	.byte	-126
	.byte	-55
	.byte	-3
	.byte	-51
	.byte	-64
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-124
	.byte	-17
	.byte	-5
	.byte	-37
	.byte	-47
	.byte	-1
	.byte	-91
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	94
	.byte	-120
	.byte	-31
	.byte	-5
	.byte	-38
	.byte	-66
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	22
	.byte	100
	.byte	-82
	.byte	-11
	.byte	-70
	.byte	-95
	.byte	-1
	.byte	-57
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-74
	.byte	-7
	.byte	-1
	.byte	-24
	.byte	-21
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	124
	.byte	-113
	.byte	-15
	.byte	-1
	.byte	-29
	.byte	-22
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	35
	.byte	77
	.byte	-75
	.byte	-5
	.byte	-63
	.byte	-45
	.byte	-1
	.byte	-51
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-99
	.byte	-9
	.byte	-1
	.byte	-20
	.byte	-25
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	121
	.byte	-115
	.byte	-21
	.byte	-1
	.byte	-31
	.byte	-29
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	45
	.byte	99
	.byte	-68
	.byte	-5
	.byte	-61
	.byte	-39
	.byte	-1
	.byte	-32
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	1
	.byte	-5
	.byte	-1
	.byte	-43
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-53
	.byte	1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-119
	.byte	1
	.byte	-79
	.byte	-1
	.byte	-32
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-3
	.byte	9
	.byte	-8
	.byte	-5
	.byte	-49
	.byte	-48
	.byte	-1
	.byte	-64
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-81
	.byte	13
	.byte	-32
	.byte	-13
	.byte	-63
	.byte	-71
	.byte	-7
	.byte	-58
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	73
	.byte	17
	.byte	-85
	.byte	-35
	.byte	-95
	.byte	-77
	.byte	-20
	.byte	-89
	.byte	-1
	.byte	-22
	.byte	-128
	.byte	1
	.byte	95
	.byte	-9
	.byte	-3
	.byte	-44
	.byte	-73
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-17
	.byte	90
	.byte	-12
	.byte	-6
	.byte	-45
	.byte	-47
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-101
	.byte	77
	.byte	-61
	.byte	-8
	.byte	-68
	.byte	-61
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	24
	.byte	-17
	.byte	-5
	.byte	-38
	.byte	-37
	.byte	-1
	.byte	-51
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-55
	.byte	51
	.byte	-37
	.byte	-1
	.byte	-60
	.byte	-70
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	69
	.byte	46
	.byte	-66
	.byte	-17
	.byte	-55
	.byte	-38
	.byte	-1
	.byte	-28
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-65
	.byte	-5
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-33
	.byte	-91
	.byte	-7
	.byte	-1
	.byte	-43
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-115
	.byte	124
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	16
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-66
	.byte	36
	.byte	-26
	.byte	-1
	.byte	-20
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-107
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-30
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-9
	.byte	-64
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-16
	.byte	-128
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-122
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-43
	.byte	62
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	55
	.byte	93
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-54
	.byte	24
	.byte	-43
	.byte	-21
	.byte	-70
	.byte	-65
	.byte	-36
	.byte	-96
	.byte	-16
	.byte	-81
	.byte	-1
	.byte	126
	.byte	38
	.byte	-74
	.byte	-24
	.byte	-87
	.byte	-72
	.byte	-28
	.byte	-82
	.byte	-1
	.byte	-69
	.byte	-128
	.byte	61
	.byte	46
	.byte	-118
	.byte	-37
	.byte	-105
	.byte	-78
	.byte	-16
	.byte	-86
	.byte	-1
	.byte	-40
	.byte	-128
	.byte	1
	.byte	112
	.byte	-26
	.byte	-6
	.byte	-57
	.byte	-65
	.byte	-9
	.byte	-97
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-90
	.byte	109
	.byte	-28
	.byte	-4
	.byte	-45
	.byte	-41
	.byte	-1
	.byte	-82
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	39
	.byte	77
	.byte	-94
	.byte	-24
	.byte	-84
	.byte	-76
	.byte	-11
	.byte	-78
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	52
	.byte	-36
	.byte	-10
	.byte	-58
	.byte	-57
	.byte	-7
	.byte	-36
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	124
	.byte	74
	.byte	-65
	.byte	-13
	.byte	-73
	.byte	-63
	.byte	-6
	.byte	-35
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	24
	.byte	71
	.byte	-126
	.byte	-37
	.byte	-102
	.byte	-86
	.byte	-13
	.byte	-74
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	-74
	.byte	-31
	.byte	-7
	.byte	-37
	.byte	-16
	.byte	-1
	.byte	-32
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-107
	.byte	-106
	.byte	-30
	.byte	-4
	.byte	-40
	.byte	-51
	.byte	-1
	.byte	-85
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	28
	.byte	108
	.byte	-86
	.byte	-14
	.byte	-73
	.byte	-62
	.byte	-2
	.byte	-33
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	1
	.byte	81
	.byte	-26
	.byte	-4
	.byte	-52
	.byte	-53
	.byte	-1
	.byte	-64
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	123
	.byte	102
	.byte	-47
	.byte	-9
	.byte	-68
	.byte	-60
	.byte	-1
	.byte	-23
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	20
	.byte	95
	.byte	-103
	.byte	-13
	.byte	-92
	.byte	-83
	.byte	-1
	.byte	-53
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	-34
	.byte	-8
	.byte	-1
	.byte	-40
	.byte	-43
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-88
	.byte	-81
	.byte	-10
	.byte	-4
	.byte	-21
	.byte	-51
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	47
	.byte	116
	.byte	-41
	.byte	-1
	.byte	-45
	.byte	-44
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	121
	.byte	-20
	.byte	-3
	.byte	-44
	.byte	-42
	.byte	-1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-115
	.byte	84
	.byte	-43
	.byte	-4
	.byte	-55
	.byte	-54
	.byte	-1
	.byte	-37
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	42
	.byte	80
	.byte	-96
	.byte	-16
	.byte	-94
	.byte	-71
	.byte	-1
	.byte	-51
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	1
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-12
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-18
	.byte	1
	.byte	-1
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	-128
	.type	VP8_VFMWBITREADER_NORM, %object
	.size	VP8_VFMWBITREADER_NORM, 256
VP8_VFMWBITREADER_NORM:
	.byte	0
	.byte	7
	.byte	6
	.byte	6
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	vp8_mv_update_probs, %object
	.size	vp8_mv_update_probs, 38
vp8_mv_update_probs:
	.byte	-19
	.byte	-10
	.byte	-3
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-6
	.byte	-6
	.byte	-4
	.byte	-2
	.byte	-2
	.byte	-25
	.byte	-13
	.byte	-11
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-5
	.byte	-5
	.byte	-2
	.byte	-2
	.byte	-2
	.space	2
.LC0:
	.word	7
	.word	6
	.type	vp8_coef_update_probs, %object
	.size	vp8_coef_update_probs, 1056
vp8_coef_update_probs:
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-80
	.byte	-10
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-33
	.byte	-15
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-3
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-12
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-22
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-10
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-17
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-3
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-6
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-39
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-31
	.byte	-4
	.byte	-15
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-22
	.byte	-6
	.byte	-15
	.byte	-6
	.byte	-3
	.byte	-1
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-33
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-18
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-9
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-70
	.byte	-5
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-22
	.byte	-5
	.byte	-12
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-5
	.byte	-13
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-20
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-3
	.byte	-3
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-6
	.byte	-2
	.byte	-4
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-2
	.byte	-7
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-10
	.byte	-3
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-4
	.byte	-2
	.byte	-5
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-8
	.byte	-2
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-2
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-11
	.byte	-5
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-5
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-4
	.byte	-3
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-7
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-3
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-6
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.type	__FUNCTION__.13751, %object
	.size	__FUNCTION__.13751, 17
__FUNCTION__.13751:
	.ascii	"VP8_DecodeDecide\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	default_ymode_prob, %object
	.size	default_ymode_prob, 4
default_ymode_prob:
	.byte	112
	.byte	86
	.byte	-116
	.byte	37
	.type	default_uv_mode_prob, %object
	.size	default_uv_mode_prob, 3
default_uv_mode_prob:
	.byte	-94
	.byte	101
	.byte	-52
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	ASCII(.ascii	"line: %d\012\000" )
	.space	2
.LC2:
	ASCII(.ascii	"pCurImg is null\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"err_level(%d) over ref_thr(%d)\012\000" )
.LC4:
	ASCII(.ascii	"line: %d pToQueImg is null\012\000" )
.LC5:
	ASCII(.ascii	"insert img to Voqueue failed!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC7:
	ASCII(.ascii	"Error!partition 0 length > streamlength!\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"Invalid frame sync code,data[0-1]:%02x,%02x,%02x\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC9:
	ASCII(.ascii	"Invalid frame width %d and Height %d!\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"We have a new size image!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"The old size is %d x %d,the new is %d x %d\012\000" )
.LC12:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC13:
	ASCII(.ascii	"vp8 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"ERROR: No Img buffer is allocated\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"----------------- vp8 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"-----I_MODE, but FrameType is %d-----\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"P-frm\000" )
	.space	2
.LC20:
	ASCII(.ascii	"-----cur framtype is %s, but refnum=%d-----\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"error: DecMode illegal\012\000" )
.LC22:
	ASCII(.ascii	"%s %d NULL == pFwdImg!!\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"dec P frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC24:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"VP8_Set_DecParam but logic fs is null!\012\000" )
.LC29:
	ASCII(.ascii	"VP8_Set_DecParam but cur logic pstDecodeFs is null!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"Error!Truncated packet\012\000" )
.LC31:
	ASCII(.ascii	"VP8_CB_GetPictureHeader Error!\012\000" )
.LC32:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"pic width/height to large,MbWidth = %d, MbHeight = " )
	ASCII(.ascii	"%d\000" )
	.space	2
.LC34:
	ASCII(.ascii	"VP8_ArrangeVHBMem error\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"VP8_DecodeDecide err\012\000" )
	.space	2
.LC36:
	ASCII(.ascii	"VP8_GetBufFromQueue err\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
