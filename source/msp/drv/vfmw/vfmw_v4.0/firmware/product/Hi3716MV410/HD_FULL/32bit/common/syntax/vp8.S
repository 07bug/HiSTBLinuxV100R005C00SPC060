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
	add	r0, r0, #6
	ldr	r3, [r6, #52]
	mov	r1, r7
	ldr	r5, .L2+8
	blx	r3
	add	r0, r4, #1312
	add	r1, r7, #40
	ldr	r3, [r6, #52]
	mov	r2, #1056
	add	r0, r0, #6
	blx	r3
	add	r0, r4, #1296
	mov	r1, r5
	ldr	r3, [r6, #52]
	mov	r2, #4
	add	r0, r0, #14
	blx	r3
	add	r0, r4, #1312
	add	r1, r5, #4
	ldr	r3, [r6, #52]
	mov	r5, #0
	mov	r2, #3
	add	r0, r0, #2
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
	add	r0, r4, #32
	blx	r3
	ldr	r3, [r6, #48]
	mov	r1, r5
	add	r0, r4, #36
	mov	r2, #4
	blx	r3
	mov	r3, #1
	strb	r5, [r4, #43]
	strb	r5, [r4, #44]
	strb	r5, [r4, #48]
	strb	r5, [r4, #49]
	strb	r3, [r4, #41]
	strb	r3, [r4, #42]
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
	mov	r6, r1
	ldmia	r0, {r1, r5}
	mov	r7, r0
	ldr	r8, [r0, #8]
	sub	r3, r1, #1
	mul	r2, r3, r2
	mov	r2, r2, lsr #8
	add	r2, r2, #1
	mov	r3, r2, asl #16
	cmp	r5, r3
	rsbcs	r2, r2, r1
	rsbcs	r5, r3, r5
	movcs	r9, #1
	movcc	r9, #0
	cmp	r2, #255
	movhi	r0, #0
	bhi	.L7
	ldr	r3, .L15
	add	r3, r3, r2
	ldrb	r3, [r3, #1096]	@ zero_extendqisi2
	subs	r8, r8, r3
	mov	r4, r2, asl r3
	mov	r5, r5, asl r3
	bmi	.L14
.L8:
	mov	r0, r9
	str	r8, [r7, #8]
	stmia	r7, {r4, r5}
.L7:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L14:
	rsbs	r3, r8, #8
	str	r3, [fp, #-48]
	bmi	.L8
	mov	r10, r3
.L9:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	orr	r5, r5, r0, asl r10
	subs	r10, r10, #8
	bpl	.L9
	ldr	r3, [fp, #-48]
	add	r8, r8, #8
	bic	r10, r3, #7
	add	r8, r8, r10
	b	.L8
.L16:
	.align	2
.L15:
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
	bmi	.L18
.L19:
	mov	r2, #128
	mov	r1, r7
	mov	r0, r6
	bl	Vp8_Vfmw_DecodeBool
	orr	r5, r5, r0, asl r4
	subs	r4, r4, #1
	bcs	.L19
.L18:
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #4096
	add	r3, r0, #8192
	mov	r6, r0
	ldr	r1, [r5, #4056]
	ldr	r0, [r3, #328]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r5, #4064]
	mov	r2, #0
	mov	r1, r2
	strb	r2, [r4, #372]
	and	r3, r3, #3
	mov	ip, #13
	orr	r2, r3, #7168
	str	r3, [r4, #152]
	orr	r2, r2, #32
	str	r3, [r4, #156]
	str	ip, [r4, #384]
	mov	r3, #8
	mov	ip, #1
	str	r2, [r4, #160]
	str	r3, [r4, #388]
	str	r3, [r4, #396]
	str	r3, [r4, #392]
	strb	ip, [r4, #379]
	strb	ip, [r4, #377]
	bl	SetAspectRatio
	ldr	r2, [r5, #1668]
	str	r2, [r4, #164]
	ldr	r3, [r5, #1672]
	str	r3, [r4, #168]
	ldr	r1, [r6]
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L28
.L24:
	str	r2, [r4, #172]
	mov	r2, r2, lsr #1
	str	r3, [r4, #176]
	mov	r3, r3, lsr #1
	str	r2, [r4, #180]
	str	r3, [r4, #184]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L28:
	ldr	r2, [r4, #192]
	add	r3, r3, #15
	ldr	r0, [r4, #104]
	mov	r3, r3, lsr #4
	ldr	r1, [r4, #32]
	mov	lr, r2, asl #4
	add	ip, r0, r2
	str	r0, [r4, #88]
	mul	r3, r3, lr
	str	r0, [r4, #120]
	str	r1, [r4, #48]
	str	ip, [r4, #96]
	add	r0, r3, r0
	add	r3, r1, r3
	add	r2, r0, r2
	str	r3, [r4, #36]
	str	r2, [r4, #100]
	str	r0, [r4, #108]
	str	r0, [r4, #92]
	bl	MEM_Phy2Vir
	ldr	r1, [r4, #92]
	ldr	r2, [r4, #164]
	ldr	r3, [r4, #168]
	str	r1, [r4, #124]
	str	r0, [r4, #52]
	b	.L24
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r5, r0
	add	r4, r0, #4096
	add	r6, r0, #8192
	mov	r7, r1
	mov	r0, #13
	mov	r1, r5
	bl	ReleasePacket
	ldr	r1, [r4, #4056]
	ldr	r0, [r6, #328]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L97
	cmp	r7, #0
	blt	.L32
	cmp	r7, #100
	movlt	r2, r7
	movge	r2, #100
	str	r2, [r3, #200]
	ldr	r3, [r5]
	ldr	r3, [r3]
	cmp	r2, r3
	bhi	.L98
.L33:
	mov	r0, r5
	bl	VP8_SetImgFormat
	ldr	r3, [r4, #4020]
	cmp	r3, #2
	beq	.L99
.L34:
	ldr	r3, [r5, #3268]
	cmp	r3, #0
	bne	.L36
.L35:
	mvn	r3, #0
	ldr	r1, [r4, #4056]
	str	r3, [r4, #4060]
	mov	r2, #0
	ldr	r0, [r6, #328]
	bl	FSP_SetDisplay
	ldr	r1, [r4, #4060]
.L37:
	cmn	r1, #1
	beq	.L38
	ldr	r0, [r6, #328]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L100
	mov	r2, #1
	ldr	r1, [r4, #4060]
	ldr	r0, [r6, #328]
	bl	FSP_SetDisplay
	add	r3, r5, #8128
	ldr	r0, [r6, #328]
	add	r3, r3, #40
	str	r8, [sp]
	mov	r2, r5
	mov	r1, #13
	bl	InsertImgToVoQueue
	cmp	r0, #1
	mov	r7, r0
	bne	.L101
.L38:
	ldr	r2, [r4, #4064]
	ldr	r3, [r4, #4024]
	cmp	r2, #0
	ldr	r8, [r4, #4052]
	add	r3, r3, #1
	str	r3, [r4, #4024]
	bne	.L102
	ldr	r3, [r4, #4044]
	cmp	r8, r3
	beq	.L44
.L42:
	ldr	r3, [r4, #4048]
	cmp	r8, r3
	beq	.L44
	ldr	r1, [r4, #4056]
	subs	r7, r8, r1
	movne	r7, #1
.L43:
	str	r1, [r4, #4052]
	mov	r2, #1
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
.L41:
	ldrb	r3, [r5, #3252]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L103
	cmp	r3, #2
	beq	.L104
.L47:
	ldrb	r3, [r5, #3251]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L105
	cmp	r3, #2
	beq	.L106
.L52:
	ldr	r3, [r4, #4064]
	cmp	r3, #0
	beq	.L55
	ldrb	r3, [r5, #3249]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L56
.L55:
	ldr	r3, [r4, #4044]
	ldr	r2, [r4, #4052]
	cmp	r3, r2
	beq	.L95
	ldr	r2, [r4, #4048]
	cmp	r3, r2
	beq	.L95
	ldr	r1, [r4, #4056]
	cmp	r3, r1
	beq	.L58
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
.L95:
	ldr	r1, [r4, #4056]
.L58:
	str	r1, [r4, #4044]
	mov	r2, #1
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
.L56:
	ldr	r3, [r5, #3264]
	cmp	r3, #0
	beq	.L60
	ldrb	r3, [r5, #3250]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L61
.L60:
	ldr	r3, [r4, #4048]
	ldr	r2, [r4, #4052]
	cmp	r3, r2
	beq	.L96
	ldr	r2, [r4, #4044]
	cmp	r3, r2
	beq	.L96
	ldr	r1, [r4, #4056]
	cmp	r3, r1
	beq	.L63
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
.L96:
	ldr	r1, [r4, #4056]
.L63:
	str	r1, [r4, #4048]
	mov	r2, #1
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
.L61:
	cmp	r7, #1
	movne	r0, #1
	beq	.L107
.L94:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L36:
	ldr	r1, [r4, #4056]
	str	r1, [r4, #4060]
	b	.L37
.L102:
	ldrb	r7, [r5, #3248]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L41
	ldr	r3, [r4, #4044]
	cmp	r8, r3
	bne	.L42
.L44:
	ldr	r1, [r4, #4056]
	mov	r7, #0
	b	.L43
.L32:
	mov	r2, #0
	str	r2, [r3, #200]
	b	.L33
.L99:
	ldr	r3, [r4, #4064]
	cmp	r3, #0
	bne	.L35
	b	.L34
.L105:
	ldr	r1, [r4, #4044]
	ldr	r3, [r4, #4052]
	cmp	r1, r3
	beq	.L51
	ldr	r3, [r4, #4048]
	cmp	r1, r3
	cmpne	r8, r1
	beq	.L51
	mov	r2, #0
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
.L51:
	str	r8, [r4, #4044]
	mov	r2, #1
	ldr	r0, [r6, #328]
	mov	r1, r8
	bl	FSP_SetRef
	mov	r7, #0
	b	.L52
.L103:
	ldr	r1, [r4, #4048]
	ldr	r3, [r4, #4052]
	cmp	r1, r3
	beq	.L46
	ldr	r3, [r4, #4044]
	cmp	r1, r3
	cmpne	r8, r1
	beq	.L46
	mov	r2, #0
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
.L46:
	str	r8, [r4, #4048]
	mov	r2, #1
	ldr	r0, [r6, #328]
	mov	r1, r8
	bl	FSP_SetRef
	mov	r7, #0
	b	.L47
.L101:
	ldr	r1, [r8, #212]
	mov	r5, #0
	ldr	r0, [r6, #328]
	bl	FreeUsdByDec
	str	r5, [r8, #212]
	ldr	r1, [r8, #216]
	ldr	r0, [r6, #328]
	bl	FreeUsdByDec
	str	r5, [r8, #216]
	mov	r2, r5
	ldr	r1, [r4, #4060]
	ldr	r0, [r6, #328]
	bl	FSP_SetDisplay
	ldr	r3, .L108
	mov	r0, r5
	ldr	r1, .L108+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r7
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L106:
	ldr	r3, [r4, #4044]
	ldr	r2, [r4, #4052]
	ldr	r1, [r4, #4048]
	cmp	r3, r2
	beq	.L54
	cmp	r3, r1
	beq	.L54
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
	ldr	r1, [r4, #4048]
.L54:
	str	r1, [r4, #4044]
	mov	r2, #1
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
	b	.L52
.L104:
	ldr	r3, [r4, #4048]
	ldr	r2, [r4, #4052]
	ldr	r1, [r4, #4044]
	cmp	r3, r2
	beq	.L49
	cmp	r3, r1
	beq	.L49
	mov	r1, r3
	mov	r2, #0
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
	ldr	r1, [r4, #4044]
.L49:
	str	r1, [r4, #4048]
	mov	r2, #1
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
	b	.L47
.L107:
	ldr	r0, [r6, #328]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetRef
	mov	r0, r7
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L98:
	ldr	ip, .L108
	mov	r0, #1
	ldr	r1, .L108+8
	mov	r5, #0
	ldr	r7, [ip, #68]
	blx	r7
	mov	r2, #1
	ldr	r1, [r4, #4044]
	ldr	r0, [r6, #328]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #4048]
	ldr	r0, [r6, #328]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #4052]
	ldr	r0, [r6, #328]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #4044]
	str	r5, [r4, #4048]
	str	r5, [r4, #4052]
	ldr	r0, [r6, #328]
	bl	FSP_GetNullLogicFs
	str	r5, [r4, #4024]
	mov	r3, r0
	mvn	r0, #0
	str	r3, [r4, #4052]
	str	r3, [r4, #4048]
	str	r3, [r4, #4044]
	b	.L94
.L100:
	ldr	r3, .L108
	mov	r2, #640
	ldr	r1, .L108+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L94
.L97:
	ldr	r3, .L108
	ldr	r1, .L108+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L94
.L109:
	.align	2
.L108:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC2
	.word	.LC3
	.word	.LC1
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
	ldr	r6, .L114
	add	r5, r0, #8192
	movw	r2, #8528
	mov	r7, r1
	ldr	r8, [r5, #320]
	mov	r1, #0
	ldr	r3, [r6, #48]
	mov	r4, r0
	blx	r3
	add	r0, r4, #8128
	add	r0, r0, #40
	str	r8, [r5, #320]
	bl	ResetVoQueue
	str	r7, [r4]
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r5, #328]
	beq	.L113
	add	r3, r4, #4096
	mov	ip, #0
	mov	r2, #1024
	mov	r1, #3
	str	r2, [r3, #4016]
	mov	r0, #1
	str	ip, [r3, #4028]
	ldr	r2, [r4]
	ldr	lr, [r2, #8]
	str	ip, [r3, #4036]
	str	r1, [r3, #4068]
	str	lr, [r3, #4020]
	str	r1, [r3, #4032]
	ldr	r2, [r2, #40]
	str	r2, [r3, #4040]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L113:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L114+4
	blx	r3
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L115:
	.align	2
.L114:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
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
	ldr	r3, [r0, #64]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L118
.L120:
	.word	.L118
	.word	.L121
	.word	.L122
	.word	.L123
.L118:
	mov	r3, #0
	str	r3, [r0, #76]
	str	r3, [r0, #80]
	str	r3, [r0, #84]
	str	r3, [r0, #88]
	mov	r3, #0
	str	r3, [r0, #92]
	ldmfd	sp, {fp, sp, pc}
.L122:
	mov	r2, #1
	mov	r3, #0
	str	r2, [r0, #76]
	str	r2, [r0, #84]
	str	r3, [r0, #80]
	str	r3, [r0, #88]
.L125:
	mov	r3, #1
	str	r3, [r0, #92]
	ldmfd	sp, {fp, sp, pc}
.L121:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r0, #76]
	str	r2, [r0, #88]
	str	r3, [r0, #80]
	str	r3, [r0, #84]
	b	.L125
.L123:
	mov	r3, #1
	str	r3, [r0, #76]
	str	r3, [r0, #80]
	str	r3, [r0, #84]
	str	r3, [r0, #88]
	b	.L125
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
	ldr	r8, .L139
	mov	r7, r0
	mov	r6, r1
	mov	r9, r2
	add	r10, r8, #38
.L131:
	mov	r4, r8
	mov	r5, r9
	add	r8, r8, #19
	b	.L130
.L128:
	cmp	r4, r8
	add	r5, r5, #1
	beq	.L138
.L130:
	ldrb	r2, [r4], #1	@ zero_extendqisi2
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L128
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
	bne	.L130
.L138:
	cmp	r10, r4
	add	r9, r9, #19
	bne	.L131
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L140:
	.align	2
.L139:
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
	ldr	r3, [r0, #56]
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
	strb	r0, [r6, #50]
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #8
	mov	r1, r5
	strb	r0, [r6, #51]
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #128
	mov	r1, r5
	strb	r0, [r6, #52]
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #1
	beq	.L143
.L147:
	mov	r2, #128
	mov	r1, r5
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #0
	beq	.L145
	add	r7, r6, #1312
	mov	r8, r7
	add	r7, r7, #1
	add	r8, r8, #4
.L148:
	mov	r2, #8
	mov	r1, r5
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	strb	r0, [r7, #1]!
	cmp	r7, r8
	bne	.L148
.L145:
	add	r2, r6, #2368
	mov	r1, r5
	add	r2, r2, #6
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	read_mvcontexts
.L143:
	add	r7, r6, #1296
	add	r8, r6, #1312
	add	r7, r7, #13
	add	r8, r8, #1
.L146:
	mov	r2, #8
	mov	r1, r5
	mov	r0, r4
	bl	Vp8_Vfmw_DecodeValue
	strb	r0, [r7, #1]!
	cmp	r7, r8
	bne	.L146
	b	.L147
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
	bne	.L155
.L152:
	cmp	r0, r5
	movne	r3, #1
	strne	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L155:
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
	b	.L152
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
	ldr	r3, [r0, #56]
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
	ldr	r3, .L249
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
	str	r7, [r9, #2516]
	str	r7, [r1, #864]
	ubfx	r1, r3, #1, #3
	str	r1, [r9, #2524]
	ubfx	r1, r3, #4, #1
	str	r1, [r9, #2520]
	uxtb	r0, r0
	mov	r1, r0, asl #16
	orr	r1, r1, r2, asl #8
	orr	r3, r1, r3
	mov	r3, r3, asr #5
	str	r3, [r9, #2528]
	cmp	r3, r4
	bhi	.L239
	ldr	r4, [fp, #-68]
	add	r3, r4, #2448
	add	r3, r3, #12
	str	r3, [fp, #-80]
	mov	r0, r3
	bl	VP8_setup_version
	ldr	r7, [r4, #2516]
	cmp	r7, #0
	beq	.L240
.L162:
	ldr	r4, [fp, #-68]
	mov	r3, #16
	mov	r2, #255
	mov	r1, #24
	mov	r0, r6
	str	r3, [r4, #2608]
	str	r2, [r4, #2600]
	bl	BsGet
	ldr	r3, [r4, #2516]
	ldr	r1, [fp, #-80]
	cmp	r3, #0
	add	r7, r1, #140
	str	r0, [r4, #2604]
	bne	.L167
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #128
	mov	r1, r6
	str	r0, [r4, #2588]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	str	r0, [r4, #2592]
.L167:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2474]
	cmp	r0, #0
	bne	.L168
.L175:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #6
	mov	r1, r6
	str	r0, [r4, #2596]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	mov	r2, #3
	mov	r1, r6
	strb	r0, [r4, #2470]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	mov	r3, #0
	mov	r2, #128
	strb	r3, [r4, #2461]
	mov	r1, r6
	strb	r0, [r4, #2471]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	uxtb	r0, r0
	strb	r0, [r4, #2462]
	cmp	r0, #0
	bne	.L241
.L170:
	mov	r2, #2
	mov	r1, r6
	mov	r0, r7
	sub	r4, fp, #44
	bl	Vp8_Vfmw_DecodeValue
	ldr	r8, [fp, #-68]
	mov	r2, #7
	mov	r1, r6
	mov	r5, #0
	strb	r0, [r8, #2473]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	movw	r2, #2465
	str	r5, [r4, #-12]!
	mov	r1, r6
	ldrsb	r2, [r8, r2]
	mov	r3, r4
	strb	r0, [r8, #2463]
	mov	r0, r7
	bl	get_delta_q
	movw	r2, #2466
	ldrsb	r2, [r8, r2]
	mov	r3, r4
	mov	r1, r6
	strb	r0, [r8, #2465]
	mov	r0, r7
	bl	get_delta_q
	movw	r2, #2467
	ldrsb	r2, [r8, r2]
	mov	r3, r4
	mov	r1, r6
	strb	r0, [r8, #2466]
	mov	r0, r7
	bl	get_delta_q
	movw	r2, #2468
	ldrsb	r2, [r8, r2]
	mov	r3, r4
	mov	r1, r6
	strb	r0, [r8, #2467]
	mov	r0, r7
	bl	get_delta_q
	movw	r2, #2469
	mov	r3, r4
	ldrsb	r2, [r8, r2]
	mov	r1, r6
	strb	r0, [r8, #2468]
	mov	r0, r7
	bl	get_delta_q
	ldr	r3, [r8, #2516]
	cmp	r3, r5
	strb	r0, [r8, #2469]
	bne	.L242
.L179:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2505]
	cmp	r0, #0
	bne	.L190
	ldr	r0, [fp, #-80]
	movw	r2, #1149
	ldr	r3, .L249+4
	add	r1, r0, #1296
	add	r0, r0, #152
	add	r1, r1, #5
	ldr	r3, [r3, #52]
	blx	r3
.L190:
	ldr	r2, [fp, #-68]
	ldr	r3, [r2, #2516]
	cmp	r3, #0
	bne	.L191
	mov	r3, #1
	strb	r3, [r2, #2500]
.L192:
	ldr	r3, [fp, #-68]
	ldr	r10, .L249+8
	add	r3, r3, #3776
	add	r3, r3, #2
	str	r3, [fp, #-76]
.L203:
	add	r3, r10, #264
	str	r3, [fp, #-72]
	ldr	r3, [fp, #-76]
	str	r3, [fp, #-64]
.L199:
	ldr	r8, [fp, #-64]
	sub	r5, r10, #33
.L197:
	sub	r9, r5, #11
	mov	r4, r8
	b	.L194
.L193:
	cmp	r9, r5
	add	r4, r4, #1
	beq	.L243
.L194:
	ldrb	r2, [r9, #1]!	@ zero_extendqisi2
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	cmp	r0, #1
	bne	.L193
	mov	r2, #8
	mov	r1, r6
	mov	r0, r7
	add	r4, r4, #1
	bl	Vp8_Vfmw_DecodeValue
	cmp	r9, r5
	strb	r0, [r4, #-1]
	bne	.L194
.L243:
	add	r5, r9, #11
	add	r8, r8, #11
	cmp	r5, r10
	bne	.L197
	ldr	r3, [fp, #-64]
	add	r10, r9, #44
	add	r3, r3, #33
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-72]
	cmp	r10, r3
	bne	.L199
	ldr	r3, .L249+12
	cmp	r10, r3
	ldr	r3, [fp, #-76]
	add	r3, r3, #264
	str	r3, [fp, #-76]
	bne	.L203
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	cmp	r0, #0
	str	r0, [r3, #2532]
	ldreq	r3, [fp, #-68]
	streqb	r0, [r3, #2513]
	beq	.L201
	mov	r2, #8
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	ldr	r3, [fp, #-68]
	strb	r0, [r3, #2513]
.L201:
	mov	r2, r6
	mov	r1, r7
	ldr	r0, [fp, #-80]
	bl	VP8_mb_mode_mv_init
	ldr	r3, [fp, #-68]
	ldr	r3, [r3, #2516]
	cmp	r3, #0
	beq	.L202
	ldr	r3, [fp, #-68]
	ldr	r3, [r3, #2500]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	moveq	r0, #1
	beq	.L235
.L202:
	ldr	r2, [fp, #-68]
	mov	r0, #1
	ldrb	r3, [r2, #2463]	@ zero_extendqisi2
	strb	r3, [r2, #2464]
.L235:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L240:
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
	beq	.L163
	ldr	ip, .L249+4
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L249+16
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L239:
	ldr	r3, .L249+4
	mov	r0, #1
	ldr	r1, .L249+20
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L163:
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
	str	r3, [lr, #2572]
	add	r1, r2, #15
	str	r2, [lr, #2564]
	mov	r1, r1, lsr #4
	str	r1, [lr, #2556]
	uxtb	r0, r0
	orr	r8, r8, r0, asl #8
	mov	r0, r0, lsr #6
	ubfx	r3, r8, #0, #14
	str	r0, [lr, #2576]
	add	ip, r3, #15
	cmp	r3, #32
	cmphi	r2, #32
	mov	r0, lr
	str	r3, [lr, #2568]
	mov	ip, ip, lsr #4
	movls	r0, #1
	movhi	r0, #0
	cmp	r1, #512
	orrhi	r0, r0, #1
	mul	r1, r1, ip
	cmp	ip, #512
	orrhi	r0, r0, #1
	cmp	r0, #0
	str	ip, [lr, #2560]
	str	r1, [lr, #2580]
	bne	.L244
	ldr	r9, [fp, #-68]
	ldr	r8, [r9, #116]
	ldr	r4, [r9, #112]
	cmp	r2, r4
	cmpeq	r3, r8
	beq	.L165
	ldr	r7, .L249+4
	mov	r0, #22
	ldr	r1, .L249+24
	ldr	r3, [r7, #68]
	blx	r3
	ldr	r0, [r9, #2560]
	ldr	r1, [r9, #2556]
	mov	r3, r8
	ldr	r7, [r7, #68]
	mov	r2, r4
	str	r0, [sp, #4]
	mov	r0, #22
	str	r1, [sp]
	ldr	r1, .L249+28
	blx	r7
.L165:
	ldr	r3, [fp, #-68]
	ldr	r3, [r3, #2516]
	cmp	r3, #0
	bne	.L162
	ldr	r0, [fp, #-80]
	bl	VP8_init_frame.part.0
	b	.L162
.L191:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	strb	r0, [r3, #2500]
	b	.L192
.L242:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #128
	mov	r1, r6
	strb	r0, [r4, #2501]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldrb	r3, [r4, #2501]	@ zero_extendqisi2
	strb	r5, [r4, #2503]
	cmp	r3, #0
	uxtb	r3, r0
	strb	r3, [r4, #2502]
	bne	.L188
	mov	r2, #2
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	ldr	r2, [fp, #-68]
	ldrb	r3, [r2, #2502]	@ zero_extendqisi2
	strb	r0, [r2, #2503]
.L188:
	ldr	r2, [fp, #-68]
	cmp	r3, #0
	mov	r3, #0
	strb	r3, [r2, #2504]
	bne	.L189
	mov	r2, #2
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	ldr	r3, [fp, #-68]
	strb	r0, [r3, #2504]
.L189:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #128
	mov	r1, r6
	strb	r0, [r4, #2508]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	strb	r0, [r4, #2509]
	b	.L179
.L241:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2461]
	cmp	r0, #0
	beq	.L170
	add	r4, r3, #2480
	add	r5, r3, #2496
	add	r4, r4, #12
	mov	r8, r3
.L183:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	uxtb	r0, r0
	strb	r0, [r8, #2490]
	cmp	r0, #1
	beq	.L245
.L181:
	add	r4, r4, #1
	cmp	r4, r5
	bne	.L183
	ldr	r3, [fp, #-68]
	add	r4, r3, #2496
	add	r4, r4, #4
.L187:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2491]
	cmp	r0, #1
	beq	.L246
.L185:
	add	r5, r5, #1
	cmp	r5, r4
	bne	.L187
	b	.L170
.L168:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r4, [fp, #-68]
	mov	r2, #128
	mov	r1, r6
	strb	r0, [r4, #2475]
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	uxtb	r0, r0
	strb	r0, [r4, #2476]
	cmp	r0, #0
	bne	.L247
.L171:
	ldr	r3, [fp, #-68]
	ldrb	r3, [r3, #2475]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L175
	ldr	r3, .L249+4
	mov	r2, #3
	ldr	r5, [fp, #-68]
	mov	r1, #255
	ldr	r0, [fp, #-80]
	add	r4, r5, #2464
	ldr	r3, [r3, #48]
	add	r0, r0, #18
	add	r5, r5, #2480
	add	r4, r4, #14
	blx	r3
	add	r5, r5, #1
	b	.L177
.L176:
	add	r4, r4, #1
	cmp	r4, r5
	beq	.L175
.L177:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2481]
	cmp	r0, #1
	bne	.L176
	mov	r2, #8
	mov	r1, r6
	mov	r0, r7
	bl	Vp8_Vfmw_DecodeValue
	strb	r0, [r4]
	b	.L176
.L245:
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
	strb	r0, [r8, #2472]
	cmp	r0, #1
	ldreqb	r3, [r4]	@ zero_extendqisi2
	rsbeq	r3, r3, #0
	streqb	r3, [r4]
	b	.L181
.L246:
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
	b	.L185
.L247:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	ldr	r8, [fp, #-68]
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, .L249+4
	add	r4, r8, #2480
	mov	r1, #0
	mov	r2, #8
	add	r4, r4, #5
	ldr	r3, [r3, #48]
	mov	r10, r1
	strb	r0, [r8, #2477]
	ldr	r0, [fp, #-80]
	add	r0, r0, #22
	blx	r3
.L172:
	sub	r9, r4, #4
	str	r4, [fp, #-64]
	b	.L174
.L173:
	ldr	r3, [fp, #-64]
	strb	r4, [r9, #1]!
	cmp	r9, r3
	beq	.L248
.L174:
	mov	r2, #128
	mov	r1, r6
	mov	r0, r7
	mov	r4, #0
	bl	Vp8_Vfmw_DecodeBool
	ldr	r3, [fp, #-68]
	uxtb	r0, r0
	strb	r0, [r3, #2460]
	cmp	r0, #1
	bne	.L173
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
	b	.L173
.L248:
	add	r10, r10, #1
	add	r4, r3, #4
	cmp	r10, #2
	bne	.L172
	b	.L171
.L244:
	ldr	ip, .L249+4
	mov	r0, #1
	ldr	r1, .L249+32
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	b	.L235
.L250:
	.align	2
.L249:
	.word	.LANCHOR0+1392
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1443
	.word	.LANCHOR0+2499
	.word	.LC7
	.word	.LC6
	.word	.LC9
	.word	.LC10
	.word	.LC8
	UNWIND(.fnend)
	.size	VP8_GetPictureHeader, .-VP8_GetPictureHeader
	.align	2
	.global	VP8_ArrangeVHBMem
	.type	VP8_ArrangeVHBMem, %function
VP8_ArrangeVHBMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
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
	add	r5, r0, #4096
	mov	r4, r0
	ldr	r3, [r5, #1672]
	ldr	r2, [r5, #1668]
	cmp	r3, #31
	bls	.L253
	cmp	r2, #31
	bls	.L253
	ldr	r1, [r0]
	ldr	r0, [r1, #776]
	cmp	r0, #0
	ldr	r0, [r1, #28]
	bne	.L256
	cmp	r0, #25
	beq	.L279
.L257:
	mov	r8, r2
	mov	r7, r3
	mov	r10, #5
	mov	r6, #4
	str	r6, [fp, #-88]
.L262:
	ldr	r9, .L281
	mov	r2, #32
	mov	r1, #0
	sub	r0, fp, #76
	ldr	r3, [r9, #48]
	blx	r3
	ldr	r2, [r4]
	str	r7, [fp, #-48]
	mov	r3, #0
	str	r8, [fp, #-68]
	ldr	r2, [r2, #28]
	str	r7, [fp, #-64]
	cmp	r2, #24
	str	r8, [fp, #-52]
	strb	r3, [fp, #-75]
	beq	.L268
	ldrb	r3, [fp, #-88]	@ zero_extendqisi2
	uxtb	r6, r6
	strb	r10, [fp, #-70]
	strb	r3, [fp, #-72]
.L271:
	add	r7, r4, #8192
	sub	r1, fp, #76
	strb	r6, [fp, #-69]
	mov	r6, #0
	ldr	r0, [r7, #328]
	strb	r6, [fp, #-73]
	bl	FSP_ConfigInstance
	subs	r8, r0, #0
	bne	.L269
	ldr	r1, [r4]
	sub	r3, fp, #80
	ldr	r0, [r7, #328]
	ldr	r2, [r1, #24]
	ldr	r1, [r1, #20]
	bl	FSP_ConfigFrameBuf
	cmp	r0, r6
	moveq	r0, #1
	streq	r0, [r5, #4028]
	beq	.L275
	ldr	r3, [r9, #68]
	mov	r0, r8
	ldr	r1, .L281+4
	blx	r3
	mov	r0, r8
	b	.L275
.L253:
	ldr	ip, .L281
	mov	r0, #0
	ldr	r1, .L281+8
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
.L275:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L256:
	cmp	r0, #25
	bne	.L257
	ldr	r0, [r1, #736]
	ldr	ip, [r1, #740]
	cmp	r2, r0
	bhi	.L265
	cmp	r3, ip
	bhi	.L265
	ldr	r0, [r1, #764]
	mov	r7, r3
	ldr	r6, [r1, #760]
	mov	r8, r2
	cmp	r0, #0
	add	r3, r6, #2
	str	r3, [fp, #-88]
	bne	.L280
.L273:
	mov	r6, #1
	b	.L267
.L269:
	ldr	r3, [r9, #68]
	mov	r0, r6
	ldr	r1, .L281+12
	blx	r3
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L279:
	ldr	r8, [r1, #736]
	ldr	r7, [r1, #740]
	cmp	r2, r8
	bhi	.L259
	cmp	r3, r7
	bhi	.L259
	ldr	r0, [r5, #4028]
	cmp	r0, #1
	beq	.L275
	ldr	r2, [r1, #764]
	ldr	r3, [r1, #760]
	cmp	r2, #0
	add	r2, r3, #2
	str	r2, [fp, #-88]
	beq	.L273
	add	r6, r3, #1
	cmp	r6, #17
	movge	r6, #17
.L267:
	ldrb	r10, [r1, #784]	@ zero_extendqisi2
	b	.L262
.L268:
	mov	r6, #1
	strb	r10, [fp, #-70]
	strb	r6, [fp, #-72]
	b	.L271
.L265:
	ldr	r1, .L281
	stmia	sp, {r0, ip}
.L278:
	ldr	r4, [r1, #68]
	mov	r0, #0
	ldr	r1, .L281+16
	blx	r4
	mov	r0, #0
	b	.L275
.L280:
	add	r6, r6, #1
	cmp	r6, #17
	movge	r6, #17
	b	.L267
.L259:
	ldr	r1, .L281
	str	r7, [sp, #4]
	str	r8, [sp]
	b	.L278
.L282:
	.align	2
.L281:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LC11
	.word	.LC14
	.word	.LC12
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
	add	r4, r0, #4096
	mov	r6, r0
	ldr	r5, [r4, #4028]
	cmp	r5, #0
	beq	.L309
	ldr	r3, [r4, #4020]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r3, [r0]
	ldr	r2, [r3, #8]
	bls	.L310
.L287:
	str	r2, [r4, #4020]
	cmp	r2, #4
	ldrls	pc, [pc, r2, asl #2]
	b	.L292
.L293:
	.word	.L291
	.word	.L291
	.word	.L288
	.word	.L290
	.word	.L291
.L311:
	ldr	r3, .L313
	mov	r0, #18
	ldr	r1, .L313+4
	ldr	r3, [r3, #68]
	blx	r3
.L290:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L310:
	cmp	r2, #4
	cmpne	r2, #1
	bhi	.L287
	ldr	r3, .L313
	add	r5, r0, #8192
	ldr	r1, .L313+8
	mov	r0, #2
	mov	r7, #0
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [r5, #328]
	mov	r2, #1
	ldr	r1, [r4, #4044]
	bl	FSP_ClearLogicFs
	ldr	r0, [r5, #328]
	mov	r2, #1
	ldr	r1, [r4, #4048]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r0, [r5, #328]
	ldr	r1, [r4, #4052]
	bl	FSP_ClearLogicFs
	str	r7, [r4, #4044]
	str	r7, [r4, #4048]
	str	r7, [r4, #4052]
	ldr	r0, [r5, #328]
	bl	FSP_GetNullLogicFs
	str	r7, [r4, #4024]
	str	r0, [r4, #4052]
	str	r0, [r4, #4048]
	str	r0, [r4, #4044]
	ldr	r3, [r6]
	ldr	r2, [r3, #8]
	b	.L287
.L309:
	ldr	r3, .L313
	mov	r0, #1
	ldr	r1, .L313+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L288:
	ldr	r2, [r4, #4064]
	cmp	r2, #0
	bne	.L311
.L289:
	add	r3, r6, #8192
	ldr	r1, [r4, #4052]
	ldr	r0, [r3, #328]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L312
	ldr	r3, [r4, #4064]
	cmp	r3, #0
	beq	.L298
	ldr	r3, [r6]
	ldr	r2, [r5, #200]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L298
	ldr	ip, .L313
	mov	r0, #1
	ldr	r1, .L313+16
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L291:
	ldr	r3, [r4, #4064]
	cmp	r3, #0
	beq	.L289
	ldr	r3, [r4, #4024]
	cmp	r3, #0
	bne	.L289
	ldr	ip, .L313
	mov	r0, #18
	ldr	r2, .L313+20
	ldr	r1, .L313+24
	ldr	r4, [ip, #68]
	blx	r4
	b	.L290
.L292:
	ldr	r3, .L313
	mov	r0, #1
	ldr	r1, .L313+28
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L298:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L312:
	ldr	ip, .L313
	movw	r3, #1505
	ldr	r2, .L313+32
	mov	r0, #22
	ldr	r1, .L313+36
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L314:
	.align	2
.L313:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC17
	.word	.LC16
	.word	.LC15
	.word	.LC22
	.word	.LC18
	.word	.LC19
	.word	.LC20
	.word	.LANCHOR0+2456
	.word	.LC21
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	add	r6, r0, #8192
	add	r5, r0, #4096
	mov	r7, r0
	mov	r1, #1
	ldr	r0, [r6, #328]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r5, #4056]
	blt	.L322
	mov	r1, r0
	ldr	r0, [r6, #328]
	bl	FSP_GetLogicFs
	subs	r4, r0, #0
	beq	.L323
	ldr	r6, .L324
	mov	r0, #18
	ldr	r2, [r5, #4056]
	ldr	r1, .L324+4
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r2, [r4, #520]
	cmp	r2, #0
	beq	.L319
	ldr	r0, [r4, #524]
	cmp	r0, #0
	beq	.L317
	ldr	r1, [r4, #528]
	cmp	r1, #0
	moveq	r0, r1
	beq	.L317
	ldr	ip, [r1, #12]
	ldr	r3, [r0, #12]
	mov	r0, #18
	ldr	r2, [r2, #12]
	ldr	r4, [r6, #68]
	ldr	r1, .L324+8
	str	ip, [sp]
	blx	r4
	mov	r0, #1
.L317:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L322:
	ldr	r3, .L324
	mov	r0, #0
	ldr	r1, .L324+12
	mov	r4, r0
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r5, #4044]
	ldr	r0, [r6, #328]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	ldr	r1, [r5, #4048]
	ldr	r0, [r6, #328]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #4052]
	ldr	r0, [r6, #328]
	bl	FSP_ClearLogicFs
	str	r4, [r5, #4044]
	str	r4, [r5, #4048]
	str	r4, [r5, #4052]
	ldr	r0, [r6, #328]
	bl	FSP_GetNullLogicFs
	add	r1, r7, #8128
	str	r4, [r5, #4024]
	add	r1, r1, #40
	str	r0, [r5, #4052]
	str	r0, [r5, #4048]
	str	r0, [r5, #4044]
	ldr	r0, [r6, #328]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L323:
	ldr	r3, .L324
	movw	r2, #1561
	ldr	r1, .L324+16
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	b	.L317
.L319:
	mov	r0, r2
	b	.L317
.L325:
	.align	2
.L324:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC25
	.word	.LC26
	.word	.LC23
	.word	.LC24
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
	ldr	r7, .L367
	mov	r10, r0
	add	r3, r0, #8
	ldr	ip, [r10, #3164]
	add	r8, r0, #4096
	str	r3, [fp, #-116]
	movw	r2, #3144
	mov	r1, #0
	mov	r0, r3
	ldr	r3, [r7, #48]
	add	r4, r10, #8192
	str	ip, [fp, #-120]
	blx	r3
	ldr	r3, [r8, #1620]
	str	r3, [r10, #2804]
	ldr	r3, [r8, #4068]
	str	r3, [r10, #2808]
	ldr	r3, [r8, #1660]
	str	r3, [r10, #2792]
	ldr	r3, [r8, #1664]
	str	r3, [r10, #2796]
	ldr	r3, [r8, #1648]
	str	r3, [r10, #2812]
	ldr	r3, [r8, #1652]
	str	r3, [r10, #2816]
	ldrb	r3, [r8, #1617]	@ zero_extendqisi2
	strb	r3, [r10, #2760]
	ldr	r3, [r8, #1636]
	strb	r3, [r10, #2761]
	ldrb	r3, [r8, #1577]	@ zero_extendqisi2
	strb	r3, [r10, #2762]
	ldrb	r3, [r8, #1578]	@ zero_extendqisi2
	strb	r3, [r10, #2763]
	ldrb	r3, [r8, #1579]	@ zero_extendqisi2
	strb	r3, [r10, #2764]
	ldrb	r3, [r8, #1581]	@ zero_extendqisi2
	strb	r3, [r10, #2765]
	ldrb	r3, [r8, #1566]	@ zero_extendqisi2
	strb	r3, [r10, #2766]
	ldr	r3, [r8, #1700]
	strb	r3, [r10, #2768]
	ldrb	r3, [r8, #1574]	@ zero_extendqisi2
	strb	r3, [r10, #2770]
	ldrb	r3, [r8, #1575]	@ zero_extendqisi2
	strb	r3, [r10, #2771]
	ldr	r3, [r8, #4032]
	strb	r3, [r10, #2769]
	ldr	r3, [r8, #4036]
	strb	r3, [r10, #2772]
	ldrb	r3, [r8, #1567]	@ zero_extendqisi2
	strb	r3, [r10, #2767]
	ldrb	r3, [r8, #1569]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2773]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2774]
	ldrb	r3, [r8, #1570]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2775]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2776]
	ldrb	r3, [r8, #1571]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2777]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2778]
	ldrb	r3, [r8, #1572]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2779]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2780]
	ldrb	r3, [r8, #1573]	@ zero_extendqisi2
	sxtb	r2, r3
	mov	r3, r3, lsr #7
	cmp	r2, #0
	strb	r3, [r10, #2781]
	rsblt	r2, r2, #0
	strb	r2, [r10, #2782]
	ldrb	r3, [r8, #1614]	@ zero_extendqisi2
	strb	r3, [r10, #2783]
	ldrb	r3, [r8, #1615]	@ zero_extendqisi2
	strb	r3, [r10, #2784]
	ldrb	r3, [r8, #1616]	@ zero_extendqisi2
	strb	r3, [r10, #2785]
	ldr	r3, [r8, #1708]
	str	r3, [r10, #2788]
	ldr	r3, [r8, #1704]
	strb	r3, [r10, #2786]
	ldr	r3, [r8, #1712]
	strb	r3, [r10, #2787]
	ldr	r3, [r8, #4040]
	str	r3, [r10, #3144]
	ldr	r1, [r8, #4056]
	ldr	r0, [r4, #328]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #4044]
	mov	r5, r0
	ldr	r0, [r4, #328]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #4048]
	mov	r6, r0
	ldr	r0, [r4, #328]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #4052]
	mov	r9, r0
	ldr	r0, [r4, #328]
	bl	FSP_GetLogicFs
	cmp	r6, #0
	cmpne	r5, #0
	beq	.L327
	cmp	r0, #0
	cmpne	r9, #0
	beq	.L327
	ldr	r4, [r5, #520]
	cmp	r4, #0
	beq	.L366
	ldr	r3, [r4, #12]
	add	r4, r10, #5632
	add	r1, r10, #5696
	mov	r2, #0
	mov	lr, r4
	mov	ip, r4
	str	r3, [r10, #3124]
	add	lr, lr, #53
	ldr	r3, [r5, #532]
	add	ip, ip, #59
	add	r1, r1, #9
	str	r3, [r10, #3140]
	ldr	r3, [r6, #520]
	cmp	r3, #0
	ldreq	r3, [r5, #520]
	ldr	r3, [r3, #12]
	str	r3, [r10, #3132]
	ldr	r3, [r9, #520]
	cmp	r3, #0
	ldreq	r3, [r5, #520]
	ldr	r3, [r3, #12]
	str	r3, [r10, #3128]
	ldr	r3, [r0, #520]
	mov	r0, r4
	add	r4, r4, #49
	add	r0, r0, #63
	cmp	r3, #0
	ldreq	r3, [r5, #520]
	ldr	r3, [r3, #12]
	str	r10, [fp, #-124]
	str	r3, [r10, #3136]
	ldr	r3, [r5, #524]
	ldr	r5, [r3, #20]
	mov	r3, r10
	str	r5, [r8, #4016]
	str	r5, [r10, #2800]
.L337:
	ldrsb	r5, [r4, #1]!
	add	r2, r2, #1
	cmp	r2, #4
	add	r3, r3, #4
	str	r5, [r3, #3040]
	ldrsb	r5, [lr, #1]!
	str	r5, [r3, #3056]
	ldrsb	r5, [ip, #1]!
	str	r5, [r3, #3072]
	ldrsb	r5, [r0, #1]!
	str	r5, [r3, #3088]
	ldrb	r5, [r1, #1]!	@ zero_extendqisi2
	str	r5, [r3, #3104]
	bne	.L337
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	ldr	r0, [fp, #-116]
	blx	r3
	ldrb	r3, [r8, #1617]	@ zero_extendqisi2
	add	ip, r10, #1200
	mov	r2, #16
	mov	r1, #0
	add	r0, r10, #24
	strb	r3, [r10, #8]
	add	r3, ip, #8
	add	ip, r10, #6976
	mov	r9, r3
	ldrb	r3, [r8, #1582]	@ zero_extendqisi2
	add	ip, ip, #2
	strb	r3, [r10, #9]
	mov	r4, ip
	ldrb	r3, [r8, #1583]	@ zero_extendqisi2
	add	ip, r10, #2736
	add	ip, ip, #8
	str	ip, [fp, #-112]
	strb	r3, [r10, #10]
	ldrb	r3, [r8, #1584]	@ zero_extendqisi2
	strb	r3, [r10, #11]
	ldrb	r3, [r8, #1614]	@ zero_extendqisi2
	strb	r3, [r10, #12]
	ldrb	r3, [r8, #1615]	@ zero_extendqisi2
	strb	r3, [r10, #13]
	ldrb	r3, [r8, #1616]	@ zero_extendqisi2
	strb	r3, [r10, #14]
	ldr	r3, [r7, #48]
	blx	r3
	ldrb	r3, [r8, #2874]	@ zero_extendqisi2
	mov	r2, #16
	mov	r1, #0
	add	r0, r10, #40
	strb	r3, [r10, #24]
	ldrb	r3, [r8, #2875]	@ zero_extendqisi2
	strb	r3, [r10, #25]
	ldrb	r3, [r8, #2876]	@ zero_extendqisi2
	strb	r3, [r10, #26]
	ldrb	r3, [r8, #2877]	@ zero_extendqisi2
	strb	r3, [r10, #27]
	ldrb	r3, [r8, #2878]	@ zero_extendqisi2
	strb	r3, [r10, #28]
	ldrb	r3, [r8, #2879]	@ zero_extendqisi2
	strb	r3, [r10, #29]
	ldrb	r3, [r8, #2880]	@ zero_extendqisi2
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
	ldrb	r0, [r8, #3939]	@ zero_extendqisi2
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	strb	r0, [r10, #712]
	ldrb	r0, [r8, #3938]	@ zero_extendqisi2
	strb	r0, [r10, #713]
	ldrb	r0, [r8, #3940]	@ zero_extendqisi2
	strb	r0, [r10, #714]
	ldrb	r0, [r8, #3941]	@ zero_extendqisi2
	strb	r0, [r10, #715]
	ldrb	r0, [r8, #3942]	@ zero_extendqisi2
	strb	r0, [r10, #716]
	ldrb	r0, [r8, #3943]	@ zero_extendqisi2
	strb	r0, [r10, #717]
	ldrb	r0, [r8, #3944]	@ zero_extendqisi2
	strb	r0, [r10, #718]
	ldrb	r0, [r8, #3945]	@ zero_extendqisi2
	strb	r0, [r10, #719]
	add	r0, r10, #728
	ldrb	ip, [r8, #3946]	@ zero_extendqisi2
	strb	ip, [r10, #720]
	blx	r3
	ldrb	r0, [r8, #3939]	@ zero_extendqisi2
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	strb	r0, [r10, #728]
	ldrb	r0, [r8, #3947]	@ zero_extendqisi2
	strb	r0, [r10, #729]
	ldrb	r0, [r8, #3948]	@ zero_extendqisi2
	strb	r0, [r10, #730]
	ldrb	r0, [r8, #3949]	@ zero_extendqisi2
	strb	r0, [r10, #731]
	ldrb	r0, [r8, #3950]	@ zero_extendqisi2
	strb	r0, [r10, #732]
	ldrb	r0, [r8, #3951]	@ zero_extendqisi2
	strb	r0, [r10, #733]
	ldrb	r0, [r8, #3952]	@ zero_extendqisi2
	strb	r0, [r10, #734]
	ldrb	r0, [r8, #3953]	@ zero_extendqisi2
	strb	r0, [r10, #735]
	ldrb	r0, [r8, #3954]	@ zero_extendqisi2
	strb	r0, [r10, #736]
	ldrb	r0, [r8, #3955]	@ zero_extendqisi2
	strb	r0, [r10, #737]
	add	r0, r10, #744
	ldrb	ip, [r8, #3956]	@ zero_extendqisi2
	strb	ip, [r10, #738]
	blx	r3
	ldrb	r0, [r8, #3958]	@ zero_extendqisi2
	ldr	r3, [r7, #48]
	mov	r2, #16
	mov	r1, #0
	strb	r0, [r10, #744]
	ldrb	r0, [r8, #3957]	@ zero_extendqisi2
	strb	r0, [r10, #745]
	ldrb	r0, [r8, #3959]	@ zero_extendqisi2
	strb	r0, [r10, #746]
	ldrb	r0, [r8, #3960]	@ zero_extendqisi2
	strb	r0, [r10, #747]
	ldrb	r0, [r8, #3961]	@ zero_extendqisi2
	strb	r0, [r10, #748]
	ldrb	r0, [r8, #3962]	@ zero_extendqisi2
	strb	r0, [r10, #749]
	ldrb	r0, [r8, #3963]	@ zero_extendqisi2
	strb	r0, [r10, #750]
	ldrb	r0, [r8, #3964]	@ zero_extendqisi2
	strb	r0, [r10, #751]
	add	r0, r10, #760
	ldrb	ip, [r8, #3965]	@ zero_extendqisi2
	strb	ip, [r10, #752]
	blx	r3
	ldrb	r3, [r8, #3958]	@ zero_extendqisi2
	str	r10, [fp, #-128]
	str	r8, [fp, #-132]
	strb	r3, [r10, #760]
	ldrb	r3, [r8, #3966]	@ zero_extendqisi2
	strb	r3, [r10, #761]
	ldrb	r3, [r8, #3967]	@ zero_extendqisi2
	strb	r3, [r10, #762]
	ldrb	r3, [r8, #3968]	@ zero_extendqisi2
	strb	r3, [r10, #763]
	ldrb	r3, [r8, #3969]	@ zero_extendqisi2
	strb	r3, [r10, #764]
	ldrb	r3, [r8, #3970]	@ zero_extendqisi2
	strb	r3, [r10, #765]
	ldrb	r3, [r8, #3971]	@ zero_extendqisi2
	strb	r3, [r10, #766]
	ldrb	r3, [r8, #3972]	@ zero_extendqisi2
	strb	r3, [r10, #767]
	ldrb	r3, [r8, #3973]	@ zero_extendqisi2
	strb	r3, [r10, #768]
	ldrb	r3, [r8, #3974]	@ zero_extendqisi2
	strb	r3, [r10, #769]
	ldrb	r3, [r8, #3975]	@ zero_extendqisi2
	strb	r3, [r10, #770]
	mov	r10, r4
.L338:
	sub	r6, r9, #384
	mov	r8, r10
.L342:
	sub	r4, r6, #48
	mov	r5, r8
.L339:
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
	bne	.L339
	add	r6, r6, #48
	add	r8, r8, #33
	cmp	r9, r6
	bne	.L342
	ldr	r3, [fp, #-112]
	add	r9, r9, #384
	add	r10, r10, #264
	cmp	r9, r3
	bne	.L338
	ldr	r8, [fp, #-132]
	ldr	r9, [fp, #-120]
	ldr	r10, [fp, #-128]
	ldr	r2, [r8, #1620]
	ldr	r3, [r9, #4]
	add	r7, r10, #3168
	cmp	r2, #0
	bic	r3, r3, #15
	mov	r0, r7
	sub	r3, r3, #16
	str	r3, [r10, #2820]
	moveq	r4, #10
	movne	r4, #3
	ldr	r5, [r8, #1632]
	bl	BsPos
	add	r5, r4, r5
	mov	r5, r5, asl #3
	rsb	r0, r0, r5
	str	r0, [r10, #2824]
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
	str	ip, [r10, #2836]
	str	r5, [r10, #2832]
	str	ip, [r10, #2840]
	str	ip, [r10, #2844]
	mov	r3, r0, asr #31
	mov	r3, r3, lsr #29
	add	r2, r0, r3
	and	r2, r2, #7
	rsb	r3, r3, r2
	add	r3, r3, r1, lsl #3
	str	r3, [r10, #2828]
	ldrb	r5, [r8, #1577]	@ zero_extendqisi2
	mov	r3, #1
	ldr	r1, [r8, #1632]
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
	str	r5, [r10, #2848]
	addhi	r4, r4, r4, lsl #1
	addhi	r4, r0, r4
	cmp	r5, #0
	ble	.L353
	rsb	r3, r5, #1
	sub	lr, fp, #76
	sub	r7, r5, #1
	mov	ip, #0
	add	r3, r3, r3, lsl #1
	mov	r6, lr
	rsb	r3, r1, r3
	add	r8, r3, r2
.L348:
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
	bne	.L348
	ldr	r3, [fp, #-120]
	add	r7, r7, r7, lsl #1
	ldr	r1, [fp, #-112]
	mov	r2, #0
	ldr	r0, [fp, #-124]
	add	r9, r10, #2848
	ldr	r3, [r3, #4]
	add	r8, r10, #2880
	add	r6, r10, #2944
	mov	r4, r2
	and	r3, r3, #15
	str	r10, [fp, #-112]
	add	r3, r7, r3
	add	r7, r10, #2912
	add	r3, r3, r1
	sub	r1, fp, #108
	str	r3, [fp, #-120]
.L352:
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
	str	r4, [r0, #2976]
	str	r4, [r0, #3008]
	bne	.L352
	ldr	r10, [fp, #-112]
.L353:
	ldr	r3, [r10]
	mov	r0, #1
	ldr	r2, [fp, #-116]
	str	r2, [r10, #4]
	ldr	r3, [r3, #676]
	str	r3, [r10, #3148]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L327:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L367+4
	blx	r3
	mov	r0, #0
.L360:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L366:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L367+8
	blx	r3
	mov	r0, r4
	b	.L360
.L368:
	.align	2
.L367:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC28
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
	ldrb	r3, [r0, #2505]	@ zero_extendqisi2
	add	r5, r0, #2448
	mov	r4, r0
	add	r5, r5, #12
	cmp	r3, #0
	add	r7, r0, #8
	ldr	r6, .L373
	bne	.L370
	add	r0, r0, #3760
	movw	r2, #1149
	add	r0, r0, #1
	add	r1, r5, #152
	ldr	r3, [r6, #52]
	blx	r3
.L370:
	ldr	r3, [r6, #52]
	movw	r2, #2452
	mov	r1, r5
	mov	r0, r7
	blx	r3
	ldr	r2, [r4, #2516]
	add	r3, r4, #4096
	str	r2, [r3, #868]
	ldr	r2, [r4, #2596]
	str	r2, [r3, #832]
	ldrb	r2, [r4, #2471]	@ zero_extendqisi2
	str	r2, [r3, #836]
	ldrb	r3, [r4, #2500]	@ zero_extendqisi2
	strb	r3, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L374:
	.align	2
.L373:
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
	UNWIND(.pad #24)
	sub	sp, sp, #24
	ldr	r3, [r1]
	mov	r4, r0
	str	r3, [r0, #3152]
	ldr	r2, [r1, #8]
	str	r2, [r0, #3156]
	ldr	r2, [r1, #12]
	cmp	r2, #2
	str	r2, [r0, #3160]
	ble	.L406
	add	r5, r0, #3168
	add	r7, r0, #3200
	mov	r1, r3
	mov	r0, r5
	bl	BsInit
	add	r3, r4, #3152
	mov	r0, r5
	mov	r1, r7
	ldr	r2, [r4, #3160]
	str	r3, [r4, #3164]
	bl	VP8_GetPictureHeader
	cmp	r0, #1
	bne	.L407
	add	r5, r4, #4096
	ldr	r3, [r5, #4028]
	cmp	r3, #0
	bne	.L408
.L379:
	ldr	r3, .L412
	ldr	r8, [r3]
	cmp	r8, #0
	addeq	r6, r4, #8192
	beq	.L381
	ldr	r1, [r4, #3308]
	add	r6, r4, #8192
	ldr	r0, [r5, #1664]
	mov	r3, #8
	ldr	lr, [r4, #3304]
	sub	r2, fp, #44
	ldr	ip, [r5, #1660]
	strh	r1, [fp, #-42]	@ movhi
	mov	r1, #2
	strh	r0, [fp, #-38]	@ movhi
	strh	lr, [fp, #-44]	@ movhi
	strh	ip, [fp, #-40]	@ movhi
	ldr	r0, [r6, #328]
	blx	r8
.L381:
	mov	r2, #1
	ldr	r1, [r5, #4044]
	ldr	r0, [r6, #328]
	mov	r8, #0
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #4048]
	add	r9, r4, #8128
	ldr	r0, [r6, #328]
	add	r9, r9, #40
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #4052]
	ldr	r0, [r6, #328]
	bl	FSP_ClearLogicFs
	str	r8, [r5, #4044]
	str	r8, [r5, #4048]
	str	r8, [r5, #4052]
	ldr	r0, [r6, #328]
	bl	FSP_GetNullLogicFs
	str	r8, [r5, #4024]
	mov	r1, r9
	str	r0, [r5, #4052]
	str	r0, [r5, #4048]
	str	r0, [r5, #4044]
	ldr	r0, [r6, #328]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [r5, #1660]
	ldr	r3, [r5, #1664]
	cmp	r2, #512
	bhi	.L383
	cmp	r3, #512
	bhi	.L383
	ldr	r3, [r4]
	ldr	r2, [r3, #776]
	cmp	r2, #0
	bne	.L385
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L409
.L385:
	ldr	r0, [r6, #328]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L405
.L387:
	mov	r0, r4
	bl	VP8_ArrangeVHBMem
	cmp	r0, #1
	bne	.L410
.L380:
	mov	r0, r4
	bl	VP8_DecodeDecide
	cmp	r0, #1
	mov	r6, r0
	beq	.L389
	ldr	r3, .L412+4
	mov	r0, #1
	ldr	r1, .L412+8
	ldr	r3, [r3, #68]
	blx	r3
	b	.L377
.L407:
	ldr	r3, .L412+4
	mov	r0, #2
	ldr	r1, .L412+12
	ldr	r3, [r3, #68]
	blx	r3
.L377:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L406:
	ldr	r3, .L412+4
	mov	r0, #1
	ldr	r1, .L412+16
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L408:
	ldr	r2, [r4, #3304]
	ldr	r3, [r5, #1660]
	cmp	r2, r3
	bne	.L379
	ldr	r2, [r4, #3308]
	ldr	r3, [r5, #1664]
	cmp	r2, r3
	bne	.L379
	b	.L380
.L383:
	ldr	ip, .L412+4
	mov	r0, #18
	ldr	r1, .L412+20
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L410:
	ldr	r3, .L412+4
	mov	r0, #1
	ldr	r1, .L412+24
	ldr	r3, [r3, #68]
	blx	r3
	b	.L377
.L409:
	ldr	r3, [r5, #4028]
	cmp	r3, #0
	bne	.L387
.L405:
	mov	r0, r9
	bl	ResetVoQueue
	b	.L387
.L389:
	mov	r0, r4
	bl	VP8_GetImageBuffer
	cmp	r0, #1
	beq	.L390
	ldr	r3, .L412+4
	mov	r0, r6
	ldr	r1, .L412+28
	ldr	r3, [r3, #68]
	blx	r3
	b	.L377
.L390:
	add	r6, r4, #8192
	ldr	r1, [r5, #4056]
	ldr	r0, [r6, #328]
	bl	FSP_GetFsImagePtr
	subs	lr, r0, #0
	beq	.L411
	ldr	r0, [r4]
	mov	r1, #0
	mvn	r2, #0
	mvn	r3, #0
	ldr	ip, .L412+4
	ldrd	r8, [r0, #48]
	mov	r0, #29
	strd	r8, [lr, #8]
	ldr	r8, [r4]
	ldrd	r8, [r8, #64]
	strd	r8, [lr, #16]
	ldr	r8, [r4]
	ldrd	r8, [r8, #80]
	strd	r8, [lr, #24]
	ldr	r8, [r4]
	ldr	r8, [r8, #96]
	str	r8, [lr, #68]
	ldr	r8, [r4]
	ldr	r8, [r8, #100]
	str	r8, [lr, #72]
	ldr	r8, [r4]
	ldr	r8, [r8, #104]
	str	r8, [lr, #76]
	ldr	r8, [r4]
	ldr	r8, [r8, #120]
	str	r1, [lr, #148]
	ldr	r1, .L412+32
	str	r8, [lr, #80]
	ldr	r8, [r4]
	strd	r2, [r8, #48]
	ldrd	r8, [lr, #8]
	ldrd	r2, [lr, #16]
	strd	r8, [fp, #-52]
	ldr	r8, [ip, #68]
	strd	r2, [sp]
	ldrd	r2, [fp, #-52]
	blx	r8
	ldr	r2, [r5, #4064]
	cmp	r2, #0
	bne	.L392
	ldr	r1, [r5, #4048]
	ldr	r3, [r5, #4056]
	cmp	r1, r3
	beq	.L393
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
	ldr	r3, [r5, #4056]
.L393:
	ldr	r1, [r5, #4052]
	cmp	r1, r3
	beq	.L394
	mov	r2, #0
	ldr	r0, [r6, #328]
	bl	FSP_SetRef
	ldr	r3, [r5, #4056]
.L394:
	ldr	r1, [r5, #4044]
	cmp	r1, r3
	beq	.L395
	ldr	r0, [r6, #328]
	mov	r2, #0
	bl	FSP_SetRef
.L395:
	mov	r3, #0
	str	r3, [r5, #4024]
.L392:
	mov	r0, r4
	bl	VP8_Set_DecParam
	mov	r0, r7
	bl	VP8_Update_PictHeader
	b	.L377
.L411:
	ldr	r3, .L412+4
	movw	r2, #2006
	ldr	r1, .L412+36
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	b	.L377
.L413:
	.align	2
.L412:
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	.word	.LC30
	.word	.LC29
	.word	.LC31
	.word	.LC32
	.word	.LC34
	.word	.LC35
	.word	.LC24
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	mov	r5, r1
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r4, r0, #8192
	mov	r2, #0
	ldr	r0, [r4, #328]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #328]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L417
	ldr	r1, [r5, #212]
	mov	r6, #0
	ldr	r0, [r4, #328]
	bl	FreeUsdByDec
	str	r6, [r5, #212]
	ldr	r1, [r5, #216]
	ldr	r0, [r4, #328]
	bl	FreeUsdByDec
	str	r6, [r5, #216]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L417:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
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
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r0, r0, #8128
	add	r0, r0, #40
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetVoLastImageID
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
	add	r4, r0, #8192
	mov	r5, r0
	ldr	r0, [r4, #328]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #328]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L425
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L425:
	add	r1, r5, #8128
	ldr	r0, [r4, #328]
	add	r1, r1, #40
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
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
	.type	__FUNCTION__.13375, %object
	.size	__FUNCTION__.13375, 17
__FUNCTION__.13375:
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
	ASCII(.ascii	"pCurImg is null\012\000" )
	.space	3
.LC2:
	ASCII(.ascii	"err_level(%d) over ref_thr(%d)\012\000" )
.LC3:
	ASCII(.ascii	"line: %d pToQueImg is null\012\000" )
.LC4:
	ASCII(.ascii	"insert img to Voqueue failed!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC6:
	ASCII(.ascii	"Error!partition 0 length > streamlength!\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"Invalid frame sync code,data[0-1]:%02x,%02x,%02x\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC8:
	ASCII(.ascii	"Invalid frame width %d and Height %d!\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"We have a new size image!\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"The old size is %d x %d,the new is %d x %d\012\000" )
.LC11:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC12:
	ASCII(.ascii	"vp8 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"ERROR: No Img buffer is allocated\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"----------------- vp8 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"-----I_MODE, but FrameType is %d-----\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"P-frm\000" )
	.space	2
.LC19:
	ASCII(.ascii	"-----cur framtype is %s, but refnum=%d-----\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"error: DecMode illegal\012\000" )
.LC21:
	ASCII(.ascii	"%s %d NULL == pFwdImg!!\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"dec P frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
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
	ASCII(.ascii	"VP8_Set_DecParam but logic fs is null!\012\000" )
.LC28:
	ASCII(.ascii	"VP8_Set_DecParam but cur logic pstDecodeFs is null!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC29:
	ASCII(.ascii	"Error!Truncated packet\012\000" )
.LC30:
	ASCII(.ascii	"VP8_CB_GetPictureHeader Error!\012\000" )
.LC31:
	ASCII(.ascii	"pic width/height to large,MbWidth = %d, MbHeight = " )
	ASCII(.ascii	"%d\000" )
	.space	2
.LC32:
	ASCII(.ascii	"VP8_ArrangeVHBMem error\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"VP8_DecodeDecide err\012\000" )
	.space	2
.LC34:
	ASCII(.ascii	"VP8_GetBufFromQueue err\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
