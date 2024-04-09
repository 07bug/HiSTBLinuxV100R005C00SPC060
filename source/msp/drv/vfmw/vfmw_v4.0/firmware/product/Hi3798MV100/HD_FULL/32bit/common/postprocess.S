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
	.file	"postprocess.c"
	.text
	.align	2
	.global	PostPro_GetRepairStratage
	.type	PostPro_GetRepairStratage, %function
PostPro_GetRepairStratage:
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
	cmp	r1, #0
	beq	.L3
	bics	r3, r0, #16
	bne	.L4
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L4:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L3:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	PostPro_GetRepairStratage, .-PostPro_GetRepairStratage
	.align	2
	.global	PostPro_CopyYuv
	.type	PostPro_CopyYuv, %function
PostPro_CopyYuv:
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
	ldr	r3, .L9
	mov	ip, #1744
	add	lr, r0, #12288
	ldr	r5, .L9+4
	mov	r2, #0
	mla	ip, ip, r1, r3
	ldr	r4, [lr, #2304]
	ldr	r3, [lr, #2316]
	ldr	r7, [lr, #2372]
	ldr	r5, [r5, #104]
	add	r6, ip, #32
	str	r3, [ip, #12]
	cmp	r5, r2
	str	r4, [ip, #4]
	str	r4, [ip, #8]
	ldr	r3, [r0, #220]
	str	r3, [ip, #16]
	ldr	lr, [r0, #228]
	str	lr, [ip, #20]
	ldrh	lr, [r0, #164]
	str	lr, [ip, #24]
	ldrh	r4, [r0, #166]
	str	r7, [ip, #848]
	str	r2, [ip, #36]
	smulbb	lr, r4, lr
	str	r4, [ip, #28]
	strh	r2, [ip, #40]	@ movhi
	mov	r4, #1
	str	r2, [ip, #852]
	sub	lr, lr, #1
	str	r4, [ip, #32]
	strh	lr, [ip, #42]	@ movhi
	str	r4, [ip, #840]
	str	r4, [ip, #856]
	beq	.L8
	mov	r3, r1
	mov	r1, r0
	mov	r0, #2
	blx	r5
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L8:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L10:
	.align	2
.L9:
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PostPro_CopyYuv, .-PostPro_CopyYuv
	.align	2
	.global	PostPro_CopyYuv_Vc1
	.type	PostPro_CopyYuv_Vc1, %function
PostPro_CopyYuv_Vc1:
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
	ldrh	r3, [r0, #74]
	mov	r8, r0
	mov	r9, r1
	sub	r2, r3, #1
	cmp	r2, #2048
	movcc	r3, #16
	strcc	r3, [fp, #-48]
	bcc	.L12
	sub	r2, r3, #2048
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r3, #32
	strcc	r3, [fp, #-48]
	bcs	.L19
.L12:
	ldr	r3, .L20
	mov	r4, #1744
	add	r5, r8, #12288
	ldr	ip, .L20+4
	mov	r6, #1
	mov	r7, #0
	mla	r4, r4, r9, r3
	ldr	lr, [r5, #212]
	ldr	r3, [r5, #248]
	mov	r0, #22
	ldr	r2, [r5, #100]
	ldr	r1, [r5, #96]
	str	lr, [r4, #4]
	ldr	lr, [r5, #108]
	str	r2, [r4, #16]
	mov	r2, r3
	str	r3, [r4, #24]
	ldr	r3, [ip, #68]
	str	r1, [r4, #8]
	str	lr, [r4, #20]
	ldrh	lr, [r8, #76]
	mov	ip, r3
	str	r7, [r4, #36]
	adds	r3, lr, #15
	str	r6, [r4, #32]
	addmi	r3, lr, #30
	ldr	r1, .L20+8
	mov	r3, r3, asr #4
	add	r3, r3, r6
	add	r3, r3, r3, lsr #31
	bic	r3, r3, #1
	str	r3, [r4, #28]
	blx	ip
	ldr	ip, .L20+12
	ldr	lr, [r4, #28]
	ldr	r3, [r4, #24]
	ldr	r0, [r5, #244]
	ldr	r5, [ip, #104]
	smulbb	r3, lr, r3
	ldr	ip, [fp, #-48]
	cmp	r5, r7
	str	r0, [r4, #848]
	str	r6, [r4, #840]
	sub	r3, r3, #1
	strh	r7, [r4, #40]	@ movhi
	str	r6, [r4, #856]
	moveq	r0, r6
	str	ip, [r4, #860]
	strh	r3, [r4, #42]	@ movhi
	str	r7, [r4, #844]
	str	r7, [r4, #852]
	beq	.L13
	mov	r3, r9
	mov	r2, r7
	mov	r1, r8
	mov	r0, r6
	blx	r5
	subs	r0, r0, r7
	movne	r0, #1
.L13:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L19:
	sub	r2, r3, #4096
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r3, #48
	strcc	r3, [fp, #-48]
	bcc	.L12
	sub	r3, r3, #6144
	sub	r3, r3, #1
	cmp	r3, #2048
	movcs	r3, #16
	movcc	r3, #64
	str	r3, [fp, #-48]
	b	.L12
.L21:
	.align	2
.L20:
	.word	g_RepairParam
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Vc1, .-PostPro_CopyYuv_Vc1
	.align	2
	.global	PostPro_CopyYuv_Vp6
	.type	PostPro_CopyYuv_Vp6, %function
PostPro_CopyYuv_Vp6:
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
	ldr	r2, .L25
	mov	r4, #1744
	ldr	r3, [r0, #172]
	mov	r5, r0
	mov	r7, #0
	mov	r6, #1
	mla	r4, r4, r1, r2
	ldr	r2, .L25+4
	mov	r9, r1
	mov	r0, #22
	ldr	r1, .L25+8
	ldr	r10, [r2, #68]
	str	r3, [r4, #4]
	ldr	r3, [r5, #172]
	str	r3, [r4, #8]
	ldr	r3, [r5, #180]
	str	r3, [r4, #16]
	ldr	r3, [r5, #184]
	str	r3, [r4, #20]
	ldrh	r2, [r5, #52]
	str	r2, [r4, #24]
	ldrh	r3, [r5, #54]
	str	r7, [r4, #36]
	str	r6, [r4, #32]
	str	r3, [r4, #28]
	blx	r10
	ldr	ip, [r4, #28]
	ldr	r3, [r4, #24]
	ldr	r0, .L25+12
	str	r6, [r4, #840]
	smulbb	r3, ip, r3
	ldr	r8, [r0, #104]
	strh	r7, [r4, #40]	@ movhi
	str	r7, [r4, #844]
	cmp	r8, r7
	sub	r3, r3, #1
	strh	r3, [r4, #42]	@ movhi
	ldr	r3, [r5, #192]
	str	r6, [r4, #856]
	str	r7, [r4, #852]
	str	r3, [r4, #848]
	beq	.L24
	mov	r3, r9
	mov	r2, r7
	mov	r1, r5
	mov	r0, #10
	blx	r8
	subs	r0, r0, r7
	movne	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L24:
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L26:
	.align	2
.L25:
	.word	g_RepairParam
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PostPro_CopyYuv_Vp6, .-PostPro_CopyYuv_Vp6
	.align	2
	.global	PostPro_GetHevcMbGroup
	.type	PostPro_GetHevcMbGroup, %function
PostPro_GetHevcMbGroup:
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
	mov	r7, r1
	ldr	r1, [r1, #8]
	mov	r6, r0
	str	r2, [fp, #-48]
	sub	r2, r1, #1
	cmp	r2, #199
	bhi	.L77
	ldr	ip, [r0, #868]
	mov	r5, #0
	ldr	r2, [r0, #24]
	ldr	r4, [r0, #28]
	cmp	ip, r5
	str	r5, [r0, #840]
	str	r5, [r0, #856]
	mul	r4, r4, r2
	bne	.L78
	ldr	r3, [r7, #8]
	mvn	r5, #0
	uxth	r10, r4
	add	r2, r4, r5
	mov	r1, r5
	str	r2, [fp, #-48]
	add	r0, r7, r3, lsl #2
	mov	r2, r7
	mov	r3, r0
	strh	r10, [r0, #14]	@ movhi
	strh	r10, [r0, #12]	@ movhi
	b	.L61
.L81:
	cmp	r0, r5
	movlt	r5, r1
	add	r3, r5, #1
	cmp	r0, r3
	ble	.L56
	ldr	r3, [r6, #840]
	cmp	r3, #199
	bgt	.L79
	add	r8, r1, r1, lsr #31
	sub	r1, r5, #100
	add	r5, r6, r3, lsl #2
	add	r3, r3, #1
	sxth	r9, r8
	strh	r8, [r5, #40]	@ movhi
	cmp	r1, r9
	sub	r8, r0, #1
	strgth	r1, [r5, #40]	@ movhi
	strh	r8, [r5, #42]	@ movhi
	str	r3, [r6, #840]
.L56:
	ldr	r3, [r7, #8]
	sub	r1, r3, #1
	cmp	r1, ip
	beq	.L80
.L65:
	add	ip, ip, #1
	mov	r5, lr
	cmp	r3, ip
	mov	r1, r0
	add	r2, r2, #4
	bcc	.L62
.L61:
	ldrh	r0, [r2, #12]
	ldrh	lr, [r2, #14]
	cmp	r0, r4
	cmple	lr, r4
	movgt	r3, #1
	movle	r3, #0
	cmp	r0, lr
	orrgt	r3, r3, #1
	cmp	r3, #0
	beq	.L81
	ldr	r3, [r7, #8]
	add	ip, ip, #1
	add	r2, r2, #4
	cmp	r3, ip
	bcs	.L61
.L62:
	mov	r0, #0
.L29:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L80:
	ldrh	r1, [r2, #14]
	ldr	r5, [fp, #-48]
	cmp	r1, r5
	bge	.L65
	ldr	r3, [r6, #840]
	cmp	r3, #199
	bgt	.L82
	add	r2, r6, r3, lsl #2
	sub	r10, r10, #1
	add	r3, r3, #1
	mov	r0, #0
	strh	r10, [r2, #42]	@ movhi
	strh	r1, [r2, #40]	@ movhi
	str	r3, [r6, #840]
	b	.L29
.L78:
	mov	r1, r3, asl #6
	ldr	r2, .L84
	sub	r3, r1, r3, asl #3
	ldr	r1, .L84+4
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r0, [r1, r3, asl #2]
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	HEVC_CalcTileMap
	ldr	r9, [r7, #8]
	cmp	r9, r5
	beq	.L37
	mov	ip, r5
	ldr	r8, .L84+8
	ldr	r5, .L84+12
	mov	r0, r7
	mov	lr, #1
.L36:
	ldrh	r2, [r0, #12]
	ldrh	r1, [r0, #14]
	cmp	r2, r1
	mov	r3, r2
	bls	.L35
	b	.L34
.L75:
	ldrh	r2, [r0, #12]
.L35:
	cmp	r4, r2
	blt	.L38
	cmp	r4, r1
	ldrge	r2, [r5, r3, asl #2]
	strgeb	lr, [r8, r2]
	ldrgeh	r1, [r0, #14]
.L38:
	add	r3, r3, #1
	cmp	r1, r3
	bcs	.L75
	ldr	r9, [r7, #8]
.L34:
	add	ip, ip, #1
	add	r0, r0, #4
	cmp	r9, ip
	bhi	.L36
.L37:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #2416]
	subs	r2, r3, #0
	beq	.L33
	ldr	r3, [fp, #-48]
	mov	r10, #0
	ldr	ip, .L84+8
	mov	r9, r10
	str	r6, [fp, #-52]
	mov	r7, r2
	mov	r8, r3
	mov	r6, r3
	str	r4, [fp, #-48]
.L40:
	ldr	r0, [r8, #3532]
	ldr	lr, [r8, #3536]
	cmp	r0, lr
	bhi	.L45
	ldr	r3, .L84+12
	mov	r4, r0, asl #2
	ldr	r5, [r3, r0, asl #2]
	ldrb	r3, [ip, r5]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r2, .L84+12
	movne	r3, r0
	addne	r2, r2, r4
	bne	.L44
	b	.L43
.L46:
	ldr	r1, [r2, #4]!
	ldrb	r1, [ip, r1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L43
.L44:
	add	r3, r3, #1
	cmp	r3, lr
	bls	.L46
.L45:
	add	r10, r10, #1
	add	r8, r8, #8
	cmp	r7, r10
	bhi	.L40
.L83:
	ldr	r4, [fp, #-48]
	ldr	r6, [fp, #-52]
.L33:
	ldr	lr, .L84+8
	mov	ip, #0
.L52:
	cmp	ip, r4
	bcs	.L62
	ldrb	r3, [lr, ip]	@ zero_extendqisi2
	cmp	r3, #1
	addeq	ip, ip, #1
	ldreq	r0, [r6, #840]
	beq	.L48
	add	r1, ip, lr
	mov	r2, ip
	b	.L50
.L49:
	ldrb	r0, [r1, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L51
	mov	r2, r3
.L50:
	add	r3, r2, #1
	cmp	r4, r3
	bhi	.L49
.L51:
	ldr	r1, [r6, #840]
	add	r0, r1, #1
	add	r1, r6, r1, lsl #2
	strh	ip, [r1, #40]	@ movhi
	mov	ip, r3
	strh	r2, [r1, #42]	@ movhi
	str	r0, [r6, #840]
.L48:
	cmp	r0, #199
	ble	.L52
	ldr	r3, .L84+16
	mov	r0, #1
	ldr	r1, .L84+20
	sub	r4, r4, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	mov	r3, #1
	strh	r0, [r6, #40]	@ movhi
	strh	r4, [r6, #42]	@ movhi
	str	r3, [r6, #840]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L43:
	ldr	r3, .L84+12
	add	r4, r3, r4
	b	.L42
.L76:
	ldr	r5, [r4, #4]!
.L42:
	strb	r9, [ip, r5]
	add	r0, r0, #1
	ldr	r3, [r8, #3536]
	cmp	r3, r0
	bcs	.L76
	ldr	r7, [r6, #2416]
	add	r10, r10, #1
	add	r8, r8, #8
	cmp	r7, r10
	bhi	.L40
	b	.L83
.L77:
	ldr	r3, .L84+16
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L84+24
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L79:
	ldr	ip, .L84+16
	mov	r0, #1
	ldr	r2, .L84+28
	ldr	r1, .L84+32
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #1
	b	.L29
.L82:
	ldr	ip, .L84+16
	mov	r0, #1
	ldr	r2, .L84+28
	ldr	r1, .L84+36
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #1
	b	.L29
.L85:
	.align	2
.L84:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_IsDeced
	.word	g_TsToRsMap
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LANCHOR0
	.word	.LC3
	.word	.LC4
	UNWIND(.fnend)
	.size	PostPro_GetHevcMbGroup, .-PostPro_GetHevcMbGroup
	.align	2
	.global	PostPro_GetMp24MbGroup
	.type	PostPro_GetMp24MbGroup, %function
PostPro_GetMp24MbGroup:
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
	ldr	r2, [r1, #8]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L107
	ldr	r2, [r0, #24]
	mov	r3, #0
	ldr	r4, [r0, #28]
	str	r3, [r0, #840]
	str	r3, [r0, #856]
	mul	r4, r4, r2
	ldr	r3, [r1, #8]
	cmp	r3, #0
	add	ip, r1, r3, lsl #2
	uxth	r10, r4
	strh	r10, [ip, #14]	@ movhi
	strh	r10, [ip, #12]	@ movhi
	bne	.L108
.L89:
	mvn	r6, #0
	mov	r3, r1
	add	r2, r4, r6
	mov	r5, r6
	mov	ip, #0
	str	r2, [fp, #-48]
	b	.L98
.L112:
	cmp	r2, lr
	movle	r7, #0
	movgt	r7, #1
	cmp	r2, r5
	orrlt	r7, r7, #1
	cmp	r7, #0
	bne	.L90
	cmp	r2, r6
	movlt	r6, r5
	add	r7, r6, #1
	cmp	r7, r2
	beq	.L94
	add	r5, r5, r5, lsr #31
	sub	r8, r2, #1
	cmp	r5, r8
	bge	.L94
	ldr	r7, [r0, #840]
	cmp	r7, #199
	bgt	.L109
	sub	r6, r6, #100
	sxth	r9, r5
	cmp	r6, r9
	add	r9, r0, r7, lsl #2
	add	r7, r7, #1
	strh	r5, [r9, #40]	@ movhi
	strh	r8, [r9, #42]	@ movhi
	strgth	r6, [r9, #40]	@ movhi
	str	r7, [r0, #840]
.L94:
	ldr	r7, [r1, #8]
	sub	r5, r7, #1
	cmp	r5, ip
	beq	.L110
.L100:
	add	ip, ip, #1
	mov	r6, lr
	cmp	ip, r7
	mov	r5, r2
	add	r3, r3, #4
	bhi	.L111
.L98:
	ldrh	r2, [r3, #12]
	ldrh	lr, [r3, #14]
	cmp	r2, r4
	cmple	lr, r4
	ble	.L112
.L90:
	ldr	r7, [r1, #8]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r7
	bls	.L98
.L111:
	mov	r3, #0
.L105:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L110:
	add	r5, r1, ip, lsl #2
	ldr	r6, [fp, #-48]
	ldrh	r5, [r5, #14]
	cmp	r5, r6
	bge	.L100
	ldr	r3, [r0, #840]
	cmp	r3, #199
	bgt	.L113
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r10, r10, #1
	mov	r3, #0
	strh	r10, [r1, #42]	@ movhi
	strh	r5, [r1, #40]	@ movhi
	str	r2, [r0, #840]
	b	.L105
.L108:
	mov	r3, ip
	ldrh	ip, [ip, #10]
	sub	r2, r4, #10
	add	r3, r3, #6
	cmp	ip, r2
	subge	r2, r10, #1
	strgeh	r2, [r3, #4]	@ movhi
	b	.L89
.L107:
	ldr	r3, .L114
	mov	r0, #0
	ldr	r1, .L114+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #1
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L109:
	ldr	r3, .L114
	mov	r2, #1328
.L106:
	ldr	r3, [r3, #68]
	mov	r0, #22
	ldr	r1, .L114+8
	blx	r3
	mov	r3, #1
	b	.L105
.L113:
	ldr	r3, .L114
	movw	r2, #1359
	b	.L106
.L115:
	.align	2
.L114:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC1
	.word	.LC5
	UNWIND(.fnend)
	.size	PostPro_GetMp24MbGroup, .-PostPro_GetMp24MbGroup
	.align	2
	.global	PostPro_GetVc1MbGroup
	.type	PostPro_GetVc1MbGroup, %function
PostPro_GetVc1MbGroup:
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
	ldr	r3, [r1, #8]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L130
	ldr	r2, [r0, #24]
	mov	r3, #0
	ldr	r5, [r0, #28]
	mvn	r6, #0
	str	r3, [r0, #840]
	mov	lr, r3
	str	r3, [r0, #856]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #8]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #14]	@ movhi
	strh	r8, [ip, #12]	@ movhi
	b	.L125
.L134:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L121
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L121
	ldr	r2, [r0, #840]
	cmp	r2, #199
	bgt	.L131
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #40]	@ movhi
	strh	r6, [r10, #42]	@ movhi
	str	r2, [r0, #840]
.L121:
	ldr	r2, [r1, #8]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L132
.L127:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L133
.L125:
	ldrh	ip, [r3, #12]
	ldrh	r4, [r3, #14]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L134
	ldr	r2, [r1, #8]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L125
.L133:
	mov	r3, #0
.L118:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L132:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #14]
	cmp	r6, r9
	bge	.L127
	ldr	r3, [r0, #840]
	cmp	r3, #199
	bgt	.L135
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #42]	@ movhi
	strh	r6, [r1, #40]	@ movhi
	str	r2, [r0, #840]
	b	.L118
.L130:
	ldr	r3, .L136
	mov	r0, #0
	ldr	r1, .L136+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L131:
	ldr	r3, .L136
	movw	r2, #1423
.L129:
	ldr	r3, [r3, #68]
	mov	r0, #22
	ldr	r1, .L136+8
	blx	r3
	mov	r3, #1
	b	.L118
.L135:
	ldr	r3, .L136
	movw	r2, #1443
	b	.L129
.L137:
	.align	2
.L136:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC5
	UNWIND(.fnend)
	.size	PostPro_GetVc1MbGroup, .-PostPro_GetVc1MbGroup
	.align	2
	.global	PostPro_GetVp6MbGroup
	.type	PostPro_GetVp6MbGroup, %function
PostPro_GetVp6MbGroup:
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
	ldr	r3, [r1, #8]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L152
	ldr	r2, [r0, #24]
	mov	r3, #0
	ldr	r5, [r0, #28]
	mvn	r6, #0
	str	r3, [r0, #840]
	mov	lr, r3
	str	r3, [r0, #856]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #8]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #14]	@ movhi
	strh	r8, [ip, #12]	@ movhi
	b	.L147
.L156:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L143
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L143
	ldr	r2, [r0, #840]
	cmp	r2, #199
	bgt	.L153
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #40]	@ movhi
	strh	r6, [r10, #42]	@ movhi
	str	r2, [r0, #840]
.L143:
	ldr	r2, [r1, #8]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L154
.L149:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L155
.L147:
	ldrh	ip, [r3, #12]
	ldrh	r4, [r3, #14]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L156
	ldr	r2, [r1, #8]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L147
.L155:
	mov	r3, #0
.L140:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L154:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #14]
	cmp	r6, r9
	bge	.L149
	ldr	r3, [r0, #840]
	cmp	r3, #199
	bgt	.L157
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #42]	@ movhi
	strh	r6, [r1, #40]	@ movhi
	str	r2, [r0, #840]
	b	.L140
.L152:
	ldr	r3, .L158
	mov	r0, #0
	ldr	r1, .L158+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L153:
	ldr	r3, .L158
	movw	r2, #1508
.L151:
	ldr	r3, [r3, #68]
	mov	r0, #22
	ldr	r1, .L158+8
	blx	r3
	mov	r3, #1
	b	.L140
.L157:
	ldr	r3, .L158
	movw	r2, #1528
	b	.L151
.L159:
	.align	2
.L158:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC5
	UNWIND(.fnend)
	.size	PostPro_GetVp6MbGroup, .-PostPro_GetVp6MbGroup
	.align	2
	.global	PostPro_GetVp8MbGroup
	.type	PostPro_GetVp8MbGroup, %function
PostPro_GetVp8MbGroup:
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
	ldr	r3, [r1, #8]
	sub	r3, r3, #1
	cmp	r3, #199
	bhi	.L174
	ldr	r2, [r0, #24]
	mov	r3, #0
	ldr	r5, [r0, #28]
	mvn	r6, #0
	str	r3, [r0, #840]
	mov	lr, r3
	str	r3, [r0, #856]
	mov	r7, r6
	mul	r5, r5, r2
	ldr	r2, [r1, #8]
	mov	r3, r1
	add	ip, r1, r2, lsl #2
	add	r9, r5, r6
	uxth	r8, r5
	mov	r2, ip
	strh	r8, [ip, #14]	@ movhi
	strh	r8, [ip, #12]	@ movhi
	b	.L169
.L178:
	cmp	ip, r6
	movlt	r6, r7
	add	r6, r6, #1
	cmp	r6, ip
	beq	.L165
	add	r7, r7, r7, lsr #31
	sub	r6, ip, #1
	cmp	r7, r6
	bge	.L165
	ldr	r2, [r0, #840]
	cmp	r2, #199
	bgt	.L175
	add	r10, r0, r2, lsl #2
	add	r2, r2, #1
	strh	r7, [r10, #40]	@ movhi
	strh	r6, [r10, #42]	@ movhi
	str	r2, [r0, #840]
.L165:
	ldr	r2, [r1, #8]
	sub	r6, r2, #1
	cmp	r6, lr
	beq	.L176
.L171:
	add	lr, lr, #1
	mov	r6, r4
	cmp	lr, r2
	mov	r7, ip
	add	r3, r3, #4
	bhi	.L177
.L169:
	ldrh	ip, [r3, #12]
	ldrh	r4, [r3, #14]
	cmp	ip, r5
	cmple	r4, r5
	movgt	r2, #1
	movle	r2, #0
	cmp	ip, r4
	orrgt	r2, r2, #1
	cmp	r2, #0
	beq	.L178
	ldr	r2, [r1, #8]
	add	lr, lr, #1
	add	r3, r3, #4
	cmp	lr, r2
	bls	.L169
.L177:
	mov	r3, #0
.L162:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L176:
	add	r6, r1, lr, lsl #2
	ldrh	r6, [r6, #14]
	cmp	r6, r9
	bge	.L171
	ldr	r3, [r0, #840]
	cmp	r3, #199
	bgt	.L179
	add	r1, r0, r3, lsl #2
	add	r2, r3, #1
	sub	r8, r8, #1
	mov	r3, #0
	strh	r8, [r1, #42]	@ movhi
	strh	r6, [r1, #40]	@ movhi
	str	r2, [r0, #840]
	b	.L162
.L174:
	ldr	r3, .L180
	mov	r0, #0
	ldr	r1, .L180+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r3, #1
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L175:
	ldr	r3, .L180
	movw	r2, #1592
.L173:
	ldr	r3, [r3, #68]
	mov	r0, #22
	ldr	r1, .L180+8
	blx	r3
	mov	r3, #1
	b	.L162
.L179:
	ldr	r3, .L180
	movw	r2, #1612
	b	.L173
.L181:
	.align	2
.L180:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC5
	UNWIND(.fnend)
	.size	PostPro_GetVp8MbGroup, .-PostPro_GetVp8MbGroup
	.align	2
	.global	PostPro_GetAvsMbGroup
	.type	PostPro_GetAvsMbGroup, %function
PostPro_GetAvsMbGroup:
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
	ldr	r2, [r1, #8]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L193
	ldr	lr, [r0, #24]
	mov	r3, #0
	ldr	r4, [r0, #28]
	mvn	r7, #0
	str	r3, [r0, #856]
	mov	ip, r3
	ldr	r2, [r1, #8]
	mov	r9, r3
	mul	r4, r4, lr
	mov	r6, r7
	add	r5, r1, r2, lsl #2
	str	r1, [fp, #-56]
	mov	r8, r0
	add	lr, r4, r7
	str	lr, [fp, #-48]
	mov	r2, r5
	add	lr, r4, r4, lsr #31
	uxth	r10, r4
	strh	r10, [r5, #14]	@ movhi
	mov	lr, lr, asr #1
	str	r10, [fp, #-64]
	add	r3, lr, r7
	str	lr, [fp, #-60]
	str	r3, [fp, #-52]
	mov	r3, r1
	strh	r10, [r2, #12]	@ movhi
	b	.L189
.L196:
	cmp	r2, r7
	movlt	r7, r6
	add	r7, r7, #1
	cmp	r2, r7
	ble	.L187
	ldr	r7, [r8, #840]
	uxth	r5, r9
	rsb	r10, r5, r6, lsr #31
	rsb	r5, r5, r2
	add	r6, r10, r6
	sub	r5, r5, #1
	add	r10, r8, r7, lsl #2
	add	r7, r7, #1
	strh	r6, [r10, #40]	@ movhi
	strh	r5, [r10, #42]	@ movhi
	ldr	r5, [r8, #32]
	str	r7, [r8, #840]
	cmp	r5, #0
	bne	.L187
	ldr	r5, [fp, #-52]
	cmp	r2, r5
	addge	r8, r0, #872
	ldrge	r9, [fp, #-60]
.L187:
	ldr	r5, [r1, #8]
	sub	r6, r5, #1
	cmp	r6, ip
	beq	.L194
.L191:
	add	ip, ip, #1
	mov	r7, lr
	cmp	ip, r5
	mov	r6, r2
	add	r3, r3, #4
	bhi	.L195
.L189:
	ldrh	r2, [r3, #12]
	ldrh	lr, [r3, #14]
	cmp	r2, r4
	cmple	lr, r4
	movgt	r5, #1
	movle	r5, #0
	cmp	r2, lr
	orrgt	r5, r5, #1
	cmp	r5, #0
	beq	.L196
	ldr	r5, [r1, #8]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r5
	bls	.L189
.L195:
	mov	r2, #0
.L184:
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L194:
	add	r6, r1, ip, lsl #2
	ldr	r7, [fp, #-48]
	ldrh	r6, [r6, #14]
	cmp	r6, r7
	bge	.L191
	ldr	r1, [r0, #840]
	mov	r2, #0
	ldr	r3, [fp, #-64]
	add	ip, r1, #1
	add	r1, r0, r1, lsl #2
	sub	r3, r3, #1
	strh	r6, [r1, #40]	@ movhi
	strh	r3, [r1, #42]	@ movhi
	str	ip, [r0, #840]
	b	.L184
.L193:
	ldr	r3, .L197
	mov	r0, #0
	ldr	r1, .L197+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r2, #1
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L198:
	.align	2
.L197:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetAvsMbGroup, .-PostPro_GetAvsMbGroup
	.align	2
	.global	PostPro_GetDivx3MbGroup
	.type	PostPro_GetDivx3MbGroup, %function
PostPro_GetDivx3MbGroup:
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
	ldr	r2, [r1, #8]
	sub	r3, r2, #1
	cmp	r3, #3
	bhi	.L210
	ldr	lr, [r0, #24]
	mov	r3, #0
	ldr	r4, [r0, #28]
	mvn	r7, #0
	str	r3, [r0, #856]
	mov	ip, r3
	ldr	r2, [r1, #8]
	mov	r9, r3
	mul	r4, r4, lr
	mov	r6, r7
	add	r5, r1, r2, lsl #2
	str	r1, [fp, #-56]
	mov	r8, r0
	add	lr, r4, r7
	str	lr, [fp, #-48]
	mov	r2, r5
	add	lr, r4, r4, lsr #31
	uxth	r10, r4
	strh	r10, [r5, #14]	@ movhi
	mov	lr, lr, asr #1
	str	r10, [fp, #-64]
	add	r3, lr, r7
	str	lr, [fp, #-60]
	str	r3, [fp, #-52]
	mov	r3, r1
	strh	r10, [r2, #12]	@ movhi
	b	.L206
.L213:
	cmp	r2, r7
	movlt	r7, r6
	add	r7, r7, #1
	cmp	r2, r7
	ble	.L204
	ldr	r7, [r8, #840]
	uxth	r5, r9
	rsb	r10, r5, r6, lsr #31
	rsb	r5, r5, r2
	add	r6, r10, r6
	sub	r5, r5, #1
	add	r10, r8, r7, lsl #2
	add	r7, r7, #1
	strh	r6, [r10, #40]	@ movhi
	strh	r5, [r10, #42]	@ movhi
	ldr	r5, [r8, #32]
	str	r7, [r8, #840]
	cmp	r5, #0
	bne	.L204
	ldr	r5, [fp, #-52]
	cmp	r2, r5
	addge	r8, r0, #872
	ldrge	r9, [fp, #-60]
.L204:
	ldr	r5, [r1, #8]
	sub	r6, r5, #1
	cmp	r6, ip
	beq	.L211
.L208:
	add	ip, ip, #1
	mov	r7, lr
	cmp	ip, r5
	mov	r6, r2
	add	r3, r3, #4
	bhi	.L212
.L206:
	ldrh	r2, [r3, #12]
	ldrh	lr, [r3, #14]
	cmp	r2, r4
	cmple	lr, r4
	movgt	r5, #1
	movle	r5, #0
	cmp	r2, lr
	orrgt	r5, r5, #1
	cmp	r5, #0
	beq	.L213
	ldr	r5, [r1, #8]
	add	ip, ip, #1
	add	r3, r3, #4
	cmp	ip, r5
	bls	.L206
.L212:
	mov	r2, #0
.L201:
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L211:
	add	r6, r1, ip, lsl #2
	ldr	r7, [fp, #-48]
	ldrh	r6, [r6, #14]
	cmp	r6, r7
	bge	.L208
	ldr	r1, [r0, #840]
	mov	r2, #0
	ldr	r3, [fp, #-64]
	add	ip, r1, #1
	add	r1, r0, r1, lsl #2
	sub	r3, r3, #1
	strh	r6, [r1, #40]	@ movhi
	strh	r3, [r1, #42]	@ movhi
	str	ip, [r0, #840]
	b	.L201
.L210:
	ldr	r3, .L214
	mov	r0, #0
	ldr	r1, .L214+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r2, #1
	mov	r0, r2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L215:
	.align	2
.L214:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC1
	UNWIND(.fnend)
	.size	PostPro_GetDivx3MbGroup, .-PostPro_GetDivx3MbGroup
	.align	2
	.global	PostPro_BubbleSort
	.type	PostPro_BubbleSort, %function
PostPro_BubbleSort:
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
	ldr	r8, [r0, #8]
	cmp	r8, #1
	bls	.L228
	mov	r7, #1
.L221:
	mov	r4, #0
	rsb	lr, r7, r8
	mov	r2, r4
	mov	r3, r0
	b	.L222
.L220:
	ldrh	r1, [r3, #12]
	ldrh	ip, [r3, #16]
	cmp	r1, ip
	bls	.L219
	ldrh	r6, [r3, #14]
	mov	r4, #1
	ldrh	r5, [r3, #18]
	strh	ip, [r3, #12]	@ movhi
	strh	r1, [r3, #16]	@ movhi
	strh	r6, [r3, #18]	@ movhi
	strh	r5, [r3, #14]	@ movhi
.L219:
	add	r3, r3, #4
.L222:
	cmp	r2, lr
	add	r2, r2, #1
	bne	.L220
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	add	r7, r7, #1
	cmp	r8, r7
	movls	r4, #0
	andhi	r4, r4, #1
	cmp	r4, #0
	bne	.L221
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L228:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	PostPro_BubbleSort, .-PostPro_BubbleSort
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.global	PostPro_GetH264MbGroup
	.type	PostPro_GetH264MbGroup, %function
PostPro_GetH264MbGroup:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 824
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #828)
	sub	sp, sp, #828
	ldr	r8, [r1, #8]
	mov	r5, r1
	mov	r9, r0
	sub	r3, r8, #1
	cmp	r3, #199
	bhi	.L267
	ldr	r10, [r0, #24]
	cmp	r2, #0
	ldr	r4, [r0, #28]
	mul	r4, r4, r10
	uxtheq	r7, r4
	bne	.L268
.L233:
	mov	r1, #0
	str	r1, [r9, #840]
	str	r1, [r9, #856]
	mvn	ip, #0
	ldr	r3, [r5, #8]
	add	r2, r4, ip
	mov	lr, ip
	str	r2, [fp, #-848]
	add	r0, r5, r3, lsl #2
	mov	r3, r5
	strh	r7, [r0, #14]	@ movhi
	strh	r7, [r0, #12]	@ movhi
	b	.L250
.L272:
	cmp	r2, ip
	movlt	ip, lr
	add	r6, ip, #1
	cmp	r2, r6
	ble	.L245
	ldr	r6, [r9, #840]
	cmp	r6, #199
	bgt	.L269
	add	lr, lr, lr, lsr #31
	add	r8, r9, r6, lsl #2
	sub	ip, ip, #100
	add	r6, r6, #1
	sxth	r10, lr
	strh	lr, [r8, #40]	@ movhi
	cmp	ip, r10
	sub	lr, r2, #1
	strgth	ip, [r8, #40]	@ movhi
	strh	lr, [r8, #42]	@ movhi
	str	r6, [r9, #840]
.L245:
	ldr	r6, [r5, #8]
	sub	ip, r6, #1
	cmp	ip, r1
	beq	.L270
.L257:
	add	r1, r1, #1
	mov	ip, r0
	cmp	r6, r1
	mov	lr, r2
	add	r3, r3, #4
	bcc	.L271
.L250:
	ldrh	r2, [r3, #12]
	ldrh	r0, [r3, #14]
	cmp	r2, r4
	cmple	r0, r4
	movgt	r6, #1
	movle	r6, #0
	cmp	r2, r0
	orrgt	r6, r6, #1
	cmp	r6, #0
	beq	.L272
	ldr	r6, [r5, #8]
	add	r1, r1, #1
	add	r3, r3, #4
	cmp	r6, r1
	bcs	.L250
.L271:
	mov	r0, #0
.L260:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L270:
	add	ip, r5, r1, lsl #2
	ldr	lr, [fp, #-848]
	ldrh	ip, [ip, #14]
	cmp	ip, lr
	bge	.L257
	ldr	r3, [r9, #840]
	cmp	r3, #199
	bgt	.L273
	add	r2, r9, r3, lsl #2
	sub	r7, r7, #1
	add	r3, r3, #1
	mov	r0, #0
	strh	r7, [r2, #42]	@ movhi
	strh	ip, [r2, #40]	@ movhi
	str	r3, [r9, #840]
	b	.L260
.L268:
	cmp	r8, #0
	mov	r10, r10, asl #1
	beq	.L236
	sub	ip, fp, #844
	mov	r8, r8, asl #2
	add	lr, r1, r8
	mov	r3, r1
	mov	r2, ip
	str	ip, [fp, #-852]
.L235:
	ldrh	r0, [r3, #12]
	add	r3, r3, #4
	ldrh	r1, [r3, #10]
	cmp	r3, lr
	add	r2, r2, #4
	strh	r0, [r2, #-4]	@ movhi
	strh	r1, [r2, #-2]	@ movhi
	bne	.L235
	ldrh	r7, [ip]
	cmp	r10, #0
	ldrh	r3, [ip, #2]
	bic	r7, r7, #1
	orr	r3, r3, #1
	strh	r3, [ip, #2]	@ movhi
	uxth	r7, r7
	strh	r7, [ip]	@ movhi
	mov	r6, r3
	beq	.L255
	sub	r8, r8, #4
	sub	r3, r10, #2
	str	r3, [fp, #-848]
	add	r3, ip, r8
	mov	r8, #0
	str	r3, [fp, #-856]
	str	r4, [fp, #-868]
	uxth	r3, r10
	str	r3, [fp, #-864]
.L251:
	mov	r1, r10
	mov	r0, r7
	bl	__aeabi_uidivmod
	mov	r0, r6
	mov	r4, r1
	cmp	r4, #1
	mov	r1, r10
	bls	.L237
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-848]
	cmp	r2, r1
	bls	.L238
	str	r1, [fp, #-860]
	mov	r0, r7
	mov	r1, r10
	mov	r4, r4, lsr #1
	bl	__aeabi_uidiv
	mov	r1, r10
	mov	r7, r0
	mov	r0, r6
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-860]
	mov	r3, r3, lsr #1
	cmp	r0, r7
	beq	.L239
	ldr	r6, [fp, #-864]
	add	r1, r5, r8, lsl #2
	add	ip, r8, #1
	cmp	ip, #199
	smulbb	r7, r7, r6
	uxth	r7, r7
	add	r4, r7, r4
	uxth	r2, r4
	strh	r2, [r1, #12]	@ movhi
	ldr	lr, [r9, #24]
	sub	lr, lr, #1
	add	r7, r7, lr
	strh	r7, [r1, #14]	@ movhi
	bhi	.L265
	smulbb	r0, r0, r6
	add	lr, r8, #2
	ldr	r4, [r9, #24]
	add	ip, r5, ip, lsl #2
	cmp	lr, #199
	uxth	r3, r3
	add	r2, r2, r4
	strh	r2, [r1, #16]	@ movhi
	uxth	r0, r0
	add	r2, r3, r0
	strh	r2, [ip, #14]	@ movhi
	bhi	.L265
	ldr	r2, [r9, #24]
	add	r8, r8, #3
	add	lr, r5, lr, lsl #2
	cmp	r8, #199
	add	r0, r0, r2
	uxth	r0, r0
	strh	r0, [r1, #20]	@ movhi
	add	r3, r0, r3
	strh	r3, [lr, #14]	@ movhi
	bhi	.L265
.L241:
	ldr	r3, [fp, #-852]
	ldr	r2, [fp, #-856]
	cmp	r3, r2
	beq	.L274
	ldr	r3, [fp, #-852]
	add	r3, r3, #4
	ldrh	r7, [r3]
	ldrh	r6, [r3, #2]
	bic	r7, r7, #1
	strh	r7, [r3]	@ movhi
	orr	r6, r6, #1
	strh	r6, [r3, #2]	@ movhi
	str	r3, [fp, #-852]
	b	.L251
.L238:
	mov	r1, r10
	mov	r0, r7
	bl	__aeabi_uidiv
	add	r2, r5, r8, lsl #2
	add	r3, r8, #1
	cmp	r3, #199
	smulbb	r0, r0, r10
	uxth	r0, r0
	add	r4, r0, r4, lsr #1
	uxth	r4, r4
	strh	r4, [r2, #12]	@ movhi
	ldr	r1, [r9, #24]
	sub	r1, r1, #1
	add	r0, r0, r1
	strh	r0, [r2, #14]	@ movhi
	bhi	.L265
	add	r8, r8, #2
	ldr	r1, [r9, #24]
	add	r3, r5, r3, lsl #2
	cmp	r8, #199
	add	r4, r4, r1
	strh	r4, [r2, #16]	@ movhi
	strh	r6, [r3, #14]	@ movhi
	bls	.L241
.L265:
	ldr	r4, [fp, #-868]
	mov	r2, #1
	str	r2, [r5, #8]
	uxth	r7, r4
	sub	r3, r7, #1
	strh	r3, [r5, #14]	@ movhi
	mov	r3, #0
	strh	r3, [r5, #12]	@ movhi
.L253:
	mov	r0, r5
	bl	PostPro_BubbleSort
	b	.L233
.L237:
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-848]
	cmp	r2, r1
	bls	.L242
	add	r4, r5, r8, lsl #2
	str	r1, [fp, #-860]
	mov	r0, r6
	mov	r1, r10
	strh	r7, [r4, #12]	@ movhi
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-860]
	add	ip, r8, #1
	cmp	ip, #199
	ubfx	r1, r3, #1, #16
	smulbb	r0, r0, r10
	uxth	r0, r0
	add	r3, r1, r0
	strh	r3, [r4, #14]	@ movhi
	bhi	.L265
	ldr	r3, [r9, #24]
	add	r8, r8, #2
	add	ip, r5, ip, lsl #2
	cmp	r8, #199
	add	r2, r0, r3
	uxth	r3, r2
	strh	r3, [r4, #16]	@ movhi
	add	r3, r3, r1
	strh	r3, [ip, #14]	@ movhi
	bls	.L241
	b	.L265
.L242:
	add	r2, r5, r8, lsl #2
	add	r8, r8, #1
	cmp	r8, #199
	strh	r7, [r2, #12]	@ movhi
	strh	r6, [r2, #14]	@ movhi
	bls	.L241
	b	.L265
.L239:
	smulbb	r0, r0, r10
	add	r1, r8, #1
	add	ip, r5, r8, lsl #2
	cmp	r1, #199
	uxth	r0, r0
	add	r4, r0, r4
	add	r3, r0, r3
	uxth	r4, r4
	uxth	r3, r3
	strh	r4, [ip, #12]	@ movhi
	strh	r3, [ip, #14]	@ movhi
	bhi	.L265
	ldr	r2, [r9, #24]
	add	r8, r8, #2
	add	r1, r5, r1, lsl #2
	cmp	r8, #199
	add	r4, r4, r2
	strh	r4, [ip, #16]	@ movhi
	ldr	r2, [r9, #24]
	add	r3, r3, r2
	strh	r3, [r1, #14]	@ movhi
	bls	.L241
	b	.L265
.L255:
	mov	r8, r10
.L236:
	uxth	r7, r4
	str	r8, [r5, #8]
	b	.L253
.L267:
	ldr	r3, .L275
	mov	r2, r8
	ldr	r1, .L275+4
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L274:
	ldr	r4, [fp, #-868]
	b	.L236
.L269:
	ldr	r3, .L275
	movw	r2, #1222
.L266:
	ldr	r1, .L275+8
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L260
.L273:
	ldr	r3, .L275
	movw	r2, #1251
	b	.L266
.L276:
	.align	2
.L275:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC1
	.word	.LC5
	UNWIND(.fnend)
	.size	PostPro_GetH264MbGroup, .-PostPro_GetH264MbGroup
	.align	2
	.global	PostPro_GetRepairParam
	.type	PostPro_GetRepairParam, %function
PostPro_GetRepairParam:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r8, r3
	mov	r4, r1
	mov	r3, #0
	mov	r5, r2
	str	r0, [r1]
	str	r3, [r1, #840]
	str	r3, [r1, #1712]
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L278
.L280:
	.word	.L279
	.word	.L281
	.word	.L282
	.word	.L283
	.word	.L278
	.word	.L284
	.word	.L285
	.word	.L278
	.word	.L286
	.word	.L287
	.word	.L288
	.word	.L288
	.word	.L288
	.word	.L289
	.word	.L278
	.word	.L278
	.word	.L290
	.word	.L291
.L291:
	ldr	r3, [r2, #1280]
	mov	r0, #1
	cmp	r3, #31
	addls	r3, r3, #328
	addls	r3, r3, #2
	ldrhi	r3, [r2, #1320]
	ldrls	r3, [r2, r3, asl #2]
	str	r3, [r1, #4]
	ldr	r3, [r2, #2640]
	str	r3, [r1, #8]
	ldr	r3, [r2, #2420]
	ldr	r3, [r3, #372]
	cmp	r3, #31
	addls	r3, r3, #328
	addls	r3, r3, #2
	ldrhi	r3, [r2, #1320]
	ldrls	r3, [r2, r3, asl #2]
	str	r3, [r1, #16]
	ldr	r3, [r2, #1284]
	cmp	r3, #19
	addls	r3, r2, r3, lsl #2
	ldrhi	r3, [r2, #1452]
	ldrls	r3, [r3, #1452]
	str	r3, [r1, #20]
	ldr	r1, [r2, #68]
	mov	r3, r0, asl r1
	str	r1, [r4, #864]
	ldr	r2, [r2, #188]
	sub	r2, r2, #1
	add	r2, r2, r3
	mov	r2, r2, lsr r1
	str	r2, [r4, #24]
	ldr	r2, [r5, #184]
	sub	r2, r2, #1
	add	r3, r2, r3
	mov	r3, r3, lsr r1
	str	r3, [r4, #28]
	ldrb	r3, [r5, #217]	@ zero_extendqisi2
	str	r0, [r4, #32]
	str	r3, [r4, #868]
	ldr	r3, [r5, #8]
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #36]
	ldr	r3, [r5, #1316]
	cmp	r3, #0
	streq	r3, [r8, #8]
	bne	.L422
.L324:
	ldr	r1, [r4, #4]
	ldr	r3, [r4, #16]
	cmp	r1, r3
	beq	.L423
.L325:
	ldr	r9, .L430
	mov	r3, #0
	str	r3, [r4, #852]
.L316:
	ldr	r6, [r4, #840]
	ldr	r3, [r4, #24]
	ldr	r10, [r4, #28]
	cmp	r6, #0
	mul	r10, r10, r3
	beq	.L362
	mov	r6, #0
	mov	r5, r4
	mov	r7, r6
.L363:
	ldrsh	r2, [r5, #42]
	mov	r0, #22
	ldrsh	r3, [r5, #40]
	add	r7, r7, #1
	ldr	r1, .L430+4
	add	r5, r5, #4
	ldr	ip, [r9, #68]
	blx	ip
	ldr	r0, [r4, #840]
	ldrsh	r3, [r5, #38]
	cmp	r0, r7
	ldrsh	r1, [r5, #36]
	movhi	r2, #1
	movls	r2, #0
	cmp	r7, #199
	rsb	r3, r1, r3
	add	r3, r3, #1
	movhi	r2, #0
	add	r6, r6, r3
	cmp	r2, #0
	bne	.L363
.L362:
	ldr	r0, [r4, #1712]
	cmp	r0, #0
	beq	.L364
	add	r4, r4, #912
	mov	r1, #0
	add	r4, r4, #2
.L365:
	ldrsh	r3, [r4]
	add	r1, r1, #1
	ldrsh	r2, [r4, #-2]
	cmp	r1, #199
	cmpls	r1, r0
	add	r4, r4, #4
	rsb	r3, r2, r3
	add	r3, r3, #1
	add	r6, r6, r3
	bcc	.L365
.L364:
	cmp	r10, #0
	moveq	r4, r10
	beq	.L366
	mov	r0, #100
	mov	r1, r10
	mul	r0, r0, r6
	bl	__aeabi_uidiv
	cmp	r0, #100
	movcc	r4, r0
	movcs	r4, #100
.L366:
	mov	r3, r6
	mov	r2, r10
	mov	r0, #0
	ldr	r1, .L430+8
	str	r0, [r8, #8]
	mov	r0, #22
	ldr	r5, [r9, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L279:
	ldr	r3, [r2, #292]
	cmp	r3, #31
	addls	r3, r2, r3, lsl #2
	ldrhi	r3, [r2, #308]
	ldrls	r3, [r3, #308]
	str	r3, [r1, #4]
	ldr	r3, [r2, #296]
	str	r3, [r1, #8]
	ldr	r3, [r2, #868]
	ldr	r0, [r3, #1640]
	cmp	r0, #31
	addls	r3, r2, r0, lsl #2
	ldrhi	r3, [r2, #308]
	ldrls	r3, [r3, #308]
	str	r3, [r1, #16]
	ldr	r3, [r2, #300]
	cmp	r3, #19
	addls	r3, r3, #142
	ldrhi	r3, [r2, #568]
	ldrls	r3, [r2, r3, asl #2]
	str	r3, [r1, #20]
	ldr	r3, [r2, #28]
	str	r3, [r1, #24]
	ldr	r3, [r2, #20]
	str	r3, [r1, #28]
	ldrb	r3, [r2]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r1, #32]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r1, #36]
	ldr	ip, [r2, #860]
	cmp	ip, #0
	beq	.L298
	ldr	r3, [r2, #1064]
	cmp	r3, r0
	addne	r2, r2, #1056
	movne	r3, #0
	addne	r2, r2, #8
	bne	.L301
	b	.L424
.L302:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L299
.L301:
	add	r3, r3, #1
	cmp	r3, #15
	cmpls	r3, ip
	bcc	.L302
.L298:
	ldr	r2, [r5, #32]
	ldrsb	r3, [r5, #2]
	cmp	r2, #0
	ldrneb	r2, [r5]	@ zero_extendqisi2
	clzne	r2, r2
	movne	r2, r2, lsr #5
	cmp	r3, #0
	streq	r3, [r8, #8]
	bne	.L425
.L305:
	ldr	r0, [r4, #4]
	ldr	r3, [r4, #16]
	cmp	r0, r3
	bne	.L344
	ldr	ip, [r5, #564]
	cmp	ip, #0
	beq	.L344
	ldr	r2, [r5, #308]
	cmp	r0, r2
	addeq	r1, r5, #308
	moveq	r3, #0
	bne	.L345
.L309:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L344
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	beq	.L309
.L345:
	str	r2, [r4, #16]
	b	.L344
.L281:
	add	r6, r2, #12288
	mov	r7, #0
	mov	r1, r8
	mov	r0, r4
	ldr	r3, [r6, #212]
	str	r3, [r4, #4]
	ldr	r3, [r6, #96]
	str	r3, [r4, #8]
	ldr	r3, [r6, #100]
	str	r3, [r4, #16]
	ldr	r3, [r6, #108]
	str	r3, [r4, #20]
	ldrh	r3, [r2, #78]
	add	r3, r3, #1
	str	r3, [r4, #24]
	ldrh	r3, [r2, #80]
	add	r3, r3, #1
	str	r3, [r4, #28]
	ldrb	r3, [r2, #5]	@ zero_extendqisi2
	str	r7, [r4, #36]
	tst	r3, #253
	moveq	r3, #1
	movne	r3, r7
	str	r3, [r4, #32]
	bl	PostPro_GetVc1MbGroup
	ldr	r2, [r4, #32]
	ldrb	r3, [r5, #68]	@ zero_extendqisi2
	cmp	r2, #1
	streq	r7, [r4, #852]
	and	r3, r3, #3
	str	r3, [r4, #844]
	beq	.L360
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L426
.L360:
	mov	r3, #4
	str	r3, [r4, #864]
	ldr	r3, [r6, #244]
	ldr	r9, .L430
	str	r3, [r4, #848]
	b	.L316
.L282:
	ldr	r1, [r2, #212]
	add	r3, r2, #12288
	mov	r6, #1
	mov	r2, #0
	mov	ip, #4
	ldr	r9, .L430
	str	r1, [r4, #4]
	mov	r1, r8
	ldr	r0, [r3, #2304]
	str	r0, [r4, #8]
	mov	r0, r4
	ldr	lr, [r5, #220]
	str	lr, [r4, #16]
	ldr	lr, [r5, #228]
	str	lr, [r4, #20]
	ldrh	lr, [r5, #164]
	str	lr, [r4, #24]
	ldrh	lr, [r5, #166]
	str	r6, [r4, #32]
	str	r2, [r4, #36]
	str	lr, [r4, #28]
	str	r2, [r4, #852]
	ldr	r3, [r3, #2372]
	str	ip, [r4, #864]
	str	r3, [r4, #848]
	bl	PostPro_GetMp24MbGroup
	b	.L316
.L283:
	ldr	r3, [r2, #200]
	mov	r2, #0
	str	r3, [r1, #4]
	ldr	r3, [r5, #224]
	str	r3, [r1, #8]
	ldr	r3, [r5, #196]
	str	r3, [r1, #16]
	ldr	r3, [r5, #240]
	str	r3, [r1, #20]
	ldrh	r3, [r5, #152]
	str	r3, [r1, #24]
	ldrh	r3, [r5, #148]
	str	r3, [r1, #28]
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	str	r2, [r1, #36]
	sub	r3, r3, #3
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r1, #32]
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L415
	cmp	r3, #2
	beq	.L415
	cmp	r3, #3
	streq	r2, [r1, #852]
.L355:
	add	r5, r5, #45056
	mov	r2, #4
	mov	r1, r8
	mov	r0, r4
	ldr	r3, [r5, #260]
	str	r2, [r4, #864]
	ldr	r9, .L430
	str	r3, [r4, #848]
	bl	PostPro_GetMp24MbGroup
	b	.L316
.L284:
	ldr	r0, [r2, #128]
	mov	r3, #0
	mov	lr, #1
	mov	r2, #4
	mov	r1, r8
	ldr	r9, .L430
	str	r0, [r4, #4]
	mov	r0, r4
	ldr	ip, [r5, #124]
	str	ip, [r4, #16]
	ldr	ip, [r5, #144]
	str	ip, [r4, #20]
	ldr	ip, [r5, #8]
	str	ip, [r4, #24]
	ldr	ip, [r5, #12]
	str	lr, [r4, #32]
	str	r3, [r4, #36]
	str	ip, [r4, #28]
	str	r3, [r4, #852]
	ldr	r3, [r5, #152]
	str	r2, [r4, #864]
	str	r3, [r4, #848]
	bl	PostPro_GetDivx3MbGroup
	b	.L316
.L285:
	add	r6, r2, #12288
	mov	ip, #0
	ldr	r3, [r6, #2272]
	str	r3, [r1, #4]
	ldr	r2, [r6, #2284]
	str	r2, [r1, #8]
	ldr	r0, [r6, #2264]
	str	r0, [r1, #16]
	ldr	lr, [r6, #2276]
	str	lr, [r1, #20]
	ldr	r7, [r5, #164]
	str	r7, [r1, #24]
	ldr	r2, [r5, #168]
	str	r2, [r1, #28]
	ldr	r1, [r5, #32]
	str	r3, [r4, #876]
	add	r3, r2, r2, lsr #31
	sub	r1, r1, #3
	str	r0, [r4, #888]
	clz	r1, r1
	mov	r0, r3, asr #1
	str	ip, [r4, #36]
	mov	r1, r1, lsr #5
	str	r1, [r4, #32]
	ldr	r3, [r8, #4]
	str	r1, [r4, #904]
	str	r2, [r4, #900]
	add	r3, r3, r3, lsl #3
	str	r7, [r4, #896]
	str	ip, [r4, #908]
	mla	r3, r0, r3, lr
	str	r3, [r4, #892]
	ldr	r3, [r5, #32]
	cmp	r3, #3
	streq	ip, [r4, #852]
	beq	.L358
	cmp	r3, #1
	streq	r3, [r4, #852]
.L358:
	ldr	r2, [r6, #2696]
	mov	r3, #4
	str	r3, [r4, #864]
	mov	r1, r8
	mov	r0, r4
	ldr	r9, .L430
	str	r2, [r4, #848]
	ldr	r2, [r6, #2696]
	str	r3, [r4, #1736]
	str	r2, [r4, #1720]
	bl	PostPro_GetAvsMbGroup
	b	.L316
.L286:
	ldr	r1, [r2, #56]
	add	ip, r2, #8192
	mov	r3, #0
	mov	r6, #1
	mov	r2, #4
	ldr	r9, .L430
	str	r1, [r4, #4]
	mov	r1, r8
	ldr	r0, [r5, #52]
	str	r0, [r4, #16]
	mov	r0, r4
	ldr	lr, [r5, #72]
	str	lr, [r4, #20]
	ldr	lr, [r5, #4]
	str	lr, [r4, #24]
	ldr	lr, [r5, #8]
	str	r6, [r4, #32]
	str	r3, [r4, #36]
	str	lr, [r4, #28]
	str	r3, [r4, #852]
	ldr	r3, [ip, #3152]
	str	r2, [r4, #864]
	str	r3, [r4, #848]
	bl	PostPro_GetMp24MbGroup
	b	.L316
.L287:
	ldr	r1, [r2, #52]
	add	ip, r2, #8192
	mov	r3, #0
	mov	r6, #1
	mov	r2, #4
	ldr	r9, .L430
	str	r1, [r4, #4]
	mov	r1, r8
	ldr	r0, [r5, #48]
	str	r0, [r4, #16]
	mov	r0, r4
	ldr	lr, [r5, #68]
	str	lr, [r4, #20]
	ldr	lr, [r5, #4]
	str	lr, [r4, #24]
	ldr	lr, [r5, #8]
	str	r6, [r4, #32]
	str	r3, [r4, #36]
	str	lr, [r4, #28]
	str	r3, [r4, #852]
	ldr	r3, [ip, #3148]
	str	r2, [r4, #864]
	str	r3, [r4, #848]
	bl	PostPro_GetMp24MbGroup
	b	.L316
.L288:
	ldr	r3, [r2, #172]
	mov	r6, #0
	mov	r2, #1
	mov	r1, r8
	mov	r0, r4
	ldr	r9, .L430
	str	r3, [r4, #4]
	ldr	r3, [r5, #172]
	str	r3, [r4, #8]
	ldr	r3, [r5, #180]
	str	r3, [r4, #16]
	ldr	r3, [r5, #184]
	str	r3, [r4, #20]
	ldrh	r3, [r5, #52]
	str	r3, [r4, #24]
	ldrh	r3, [r5, #54]
	str	r2, [r4, #32]
	str	r6, [r4, #36]
	str	r3, [r4, #28]
	bl	PostPro_GetVp6MbGroup
	str	r6, [r4, #844]
	str	r6, [r4, #852]
	mov	r2, #4
	ldr	r3, [r5, #192]
	str	r2, [r4, #864]
	str	r3, [r4, #848]
	b	.L316
.L289:
	ldr	r0, [r2, #3116]
	mov	r3, #0
	mov	lr, #1
	mov	r2, #4
	mov	r1, r8
	ldr	r9, .L430
	str	r0, [r4, #4]
	mov	r0, r4
	ldr	ip, [r5, #3116]
	str	ip, [r4, #8]
	ldr	ip, [r5, #3128]
	str	ip, [r4, #16]
	ldr	ip, [r5, #3132]
	str	ip, [r4, #20]
	ldr	ip, [r5, #2784]
	str	ip, [r4, #24]
	ldr	ip, [r5, #2788]
	str	lr, [r4, #32]
	str	r3, [r4, #36]
	str	ip, [r4, #28]
	str	r3, [r4, #852]
	ldr	r3, [r5, #3140]
	str	r2, [r4, #864]
	str	r3, [r4, #848]
	bl	PostPro_GetVp8MbGroup
	b	.L316
.L290:
	ldr	r3, [r2, #292]
	cmp	r3, #31
	addls	r3, r2, r3, lsl #2
	ldrhi	r3, [r2, #308]
	ldrls	r3, [r3, #308]
	str	r3, [r1, #4]
	ldr	r3, [r2, #296]
	str	r3, [r1, #8]
	ldr	r3, [r2, #868]
	ldr	r0, [r3, #1640]
	cmp	r0, #31
	addls	r3, r2, r0, lsl #2
	ldrhi	r3, [r2, #308]
	ldrls	r3, [r3, #308]
	str	r3, [r1, #16]
	ldr	r3, [r2, #300]
	cmp	r3, #19
	addls	r3, r3, #142
	ldrhi	r3, [r2, #568]
	ldrls	r3, [r2, r3, asl #2]
	str	r3, [r1, #20]
	ldr	r3, [r2, #28]
	str	r3, [r1, #24]
	ldr	r3, [r2, #20]
	str	r3, [r1, #28]
	ldrb	r3, [r2]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r1, #32]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r1, #36]
	ldr	ip, [r2, #860]
	cmp	ip, #0
	beq	.L336
	ldr	r3, [r2, #1064]
	cmp	r3, r0
	addne	r2, r2, #1056
	movne	r3, #0
	addne	r2, r2, #8
	bne	.L339
	b	.L427
.L340:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L337
.L339:
	add	r3, r3, #1
	cmp	r3, #15
	cmpls	r3, ip
	bcc	.L340
.L336:
	ldr	r2, [r5, #32]
	ldrsb	r3, [r5, #2]
	cmp	r2, #0
	ldrneb	r2, [r5]	@ zero_extendqisi2
	clzne	r2, r2
	movne	r2, r2, lsr #5
	cmp	r3, #0
	streq	r3, [r8, #8]
	bne	.L428
.L343:
	ldr	r0, [r4, #4]
	ldr	r3, [r4, #16]
	cmp	r0, r3
	beq	.L429
.L344:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L353
	cmp	r3, #1
	beq	.L416
	cmp	r3, #2
	beq	.L416
	cmp	r3, #3
	bne	.L350
.L353:
	mov	r3, #0
.L416:
	str	r3, [r4, #852]
.L350:
	ldr	r3, [r5, #1128]
	mov	r2, #4
	ldr	r9, .L430
	str	r2, [r4, #864]
	str	r3, [r4, #848]
	b	.L316
.L278:
	ldr	r9, .L430
	movw	r3, #789
	ldr	r2, .L430+12
	mov	r0, #0
	ldr	r1, .L430+16
	ldr	r5, [r9, #68]
	blx	r5
	b	.L316
.L415:
	str	r3, [r4, #852]
	b	.L355
.L426:
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r3, #1
	streq	r3, [r4, #852]
	beq	.L360
	cmp	r3, #1
	moveq	r3, #2
	streq	r3, [r4, #852]
	b	.L360
.L425:
	mov	r1, r8
	mov	r0, r4
	bl	PostPro_GetH264MbGroup
	b	.L305
.L423:
	ldr	r0, [r5, #1448]
	cmp	r0, #0
	beq	.L325
	ldr	r2, [r5, #1320]
	cmp	r1, r2
	addeq	r5, r5, #1312
	moveq	r3, #0
	addeq	r5, r5, #8
	bne	.L326
.L328:
	add	r3, r3, #1
	cmp	r3, r0
	beq	.L325
	ldr	r2, [r5, #4]!
	cmp	r1, r2
	beq	.L328
.L326:
	str	r2, [r4, #16]
	b	.L325
.L422:
	ldr	r3, [fp, #4]
	mov	r2, r5
	mov	r1, r8
	mov	r0, r4
	bl	PostPro_GetHevcMbGroup
	b	.L324
.L429:
	ldr	ip, [r5, #564]
	cmp	ip, #0
	beq	.L344
	ldr	r2, [r5, #308]
	cmp	r0, r2
	addeq	r1, r5, #308
	moveq	r3, #0
	bne	.L345
.L347:
	add	r3, r3, #1
	cmp	r3, #31
	cmpls	r3, ip
	bcs	.L344
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	beq	.L347
	b	.L345
.L428:
	mov	r1, r8
	mov	r0, r4
	bl	PostPro_GetH264MbGroup
	b	.L343
.L427:
	mov	r3, #0
.L337:
	add	r3, r3, #250
	ldr	r3, [r5, r3, asl #2]
	str	r3, [r4, #844]
	b	.L336
.L424:
	mov	r3, #0
.L299:
	add	r3, r3, #250
	ldr	r3, [r5, r3, asl #2]
	str	r3, [r4, #844]
	b	.L298
.L431:
	.align	2
.L430:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	.LC9
	.word	.LANCHOR0+24
	.word	.LC7
	UNWIND(.fnend)
	.size	PostPro_GetRepairParam, .-PostPro_GetRepairParam
	.align	2
	.global	PostPro_GetErrRatio
	.type	PostPro_GetErrRatio, %function
PostPro_GetErrRatio:
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
	subs	r3, r0, #0
	beq	.L438
	ldr	r7, [r3, #4]
	ldr	r9, [r3]
	cmp	r7, #0
	ldr	r4, [r3, #8]
	beq	.L439
	ldr	r8, .L440
	mov	r2, #12
	mov	r1, #0
	sub	r0, fp, #48
	mov	r5, #816
	mov	r6, #1744
	ldr	r3, [r8, #48]
	blx	r3
	ldr	r3, .L440+4
	ldr	r1, .L440+8
	ldr	r2, .L440+12
	mla	r5, r5, r4, r3
	ldr	r3, [r1, #108]
	str	r9, [fp, #-48]
	cmp	r3, #0
	str	r4, [fp, #-40]
	mla	r6, r6, r4, r2
	str	r5, [fp, #-44]
	beq	.L436
	sub	r0, fp, #48
	blx	r3
.L437:
	str	r4, [sp]
	mov	r3, r5
	mov	r2, r7
	mov	r1, r6
	mov	r0, r9
	bl	PostPro_GetRepairParam
	ldr	r3, [r8, #68]
	ldr	r1, .L440+16
	mov	r4, r0
	mov	r2, r0
	mov	r0, #22
	blx	r3
	mov	r0, r4
.L434:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L436:
	mov	r0, r3
	mov	r2, #97
	ldr	r3, [r8, #68]
	ldr	r1, .L440+20
	blx	r3
	b	.L437
.L439:
	ldr	r3, .L440
	mov	r0, r7
	ldr	r1, .L440+24
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L434
.L438:
	ldr	r3, .L440
	ldr	r1, .L440+28
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L434
.L441:
	.align	2
.L440:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_DecReport
	.word	g_vdm_hal_fun_ptr
	.word	g_RepairParam
	.word	.LC13
	.word	.LC12
	.word	.LC11
	.word	.LC10
	UNWIND(.fnend)
	.size	PostPro_GetErrRatio, .-PostPro_GetErrRatio
	.align	2
	.global	PostPro_SetFullRepair
	.type	PostPro_SetFullRepair, %function
PostPro_SetFullRepair:
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
	mov	ip, #816
	mul	ip, ip, r2
	ldr	r4, .L443
	ldr	r5, .L443+4
	mov	r3, r2
	mov	r6, #1744
	str	r2, [sp]
	add	lr, r4, ip
	mov	r2, r1
	mla	r1, r6, r3, r5
	mov	r3, lr
	mov	r5, #1
	str	r5, [r4, ip]
	mov	ip, #0
	str	ip, [lr, #8]
	bl	PostPro_GetRepairParam
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L444:
	.align	2
.L443:
	.word	g_DecReport
	.word	g_RepairParam
	UNWIND(.fnend)
	.size	PostPro_SetFullRepair, .-PostPro_SetFullRepair
	.align	2
	.global	PostPro_SetDecReport
	.type	PostPro_SetDecReport, %function
PostPro_SetDecReport:
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
	ldr	r6, .L463
	mov	r5, r0
	mov	r4, r2
	mov	r7, r1
	mov	r0, r2
	mov	r1, #0
	mov	r2, #816
	ldr	r3, [r6, #48]
	blx	r3
	cmp	r5, #17
	ldrls	pc, [pc, r5, asl #2]
	b	.L446
.L448:
	.word	.L457
	.word	.L457
	.word	.L457
	.word	.L457
	.word	.L446
	.word	.L457
	.word	.L453
	.word	.L446
	.word	.L457
	.word	.L457
	.word	.L457
	.word	.L457
	.word	.L457
	.word	.L457
	.word	.L446
	.word	.L446
	.word	.L457
	.word	.L457
.L453:
	ldr	r3, [r7, #32]
	cmp	r3, #1
	beq	.L462
.L457:
	mov	r3, #0
	mov	r2, #1
	strh	r3, [r4, #12]	@ movhi
	str	r2, [r4, #8]
	strh	r3, [r4, #14]	@ movhi
.L460:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L446:
	ldr	r4, [r6, #68]
	movw	r3, #2012
	ldr	r2, .L463+4
	mov	r0, #0
	ldr	r1, .L463+8
	blx	r4
	b	.L460
.L462:
	mov	r3, #0
	mov	r2, #2
	strh	r3, [r4, #12]	@ movhi
	str	r2, [r4, #8]
	strh	r3, [r4, #14]	@ movhi
	ldr	r2, [r7, #168]
	ldr	r3, [r7, #164]
	mul	r3, r3, r2
	mov	r3, r3, lsr #1
	strh	r3, [r4, #16]	@ movhi
	ldr	r2, [r7, #168]
	ldr	r3, [r7, #164]
	mul	r3, r3, r2
	mov	r3, r3, lsr #1
	strh	r3, [r4, #18]	@ movhi
	b	.L460
.L464:
	.align	2
.L463:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+48
	.word	.LC7
	UNWIND(.fnend)
	.size	PostPro_SetDecReport, .-PostPro_SetDecReport
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13355, %object
	.size	__func__.13355, 23
__func__.13355:
	.ascii	"PostPro_GetHevcMbGroup\000"
	.space	1
	.type	__func__.13308, %object
	.size	__func__.13308, 23
__func__.13308:
	.ascii	"PostPro_GetRepairParam\000"
	.space	1
	.type	__func__.13533, %object
	.size	__func__.13533, 21
__func__.13533:
	.ascii	"PostPro_SetDecReport\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"pRepairParam->ImageWidth=%d,pRepairParam->ImageHeig" )
	ASCII(.ascii	"ht=%d\012\000" )
	.space	2
.LC1:
	ASCII(.ascii	"DecSliceNum(=%d) out of range!\012\000" )
.LC2:
	ASCII(.ascii	"pRepairParam->ValidGroupNum >(MAX_UP_MSG_SLICE_NUM " )
	ASCII(.ascii	"- 1)\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"%s:0 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"%s:1 pRepairParam->ValidGroupNum(%d) > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"line:%d! pRepairParam->ValidGroupNum > (MAX_UP_MSG_" )
	ASCII(.ascii	"SLICE_NUM - 1)\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"DecSliceNum out of range!\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"%s %d VidStd Err!\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"pRepairParam[0].MbGroup[i].EndMbn=%d,pRepairParam[0" )
	ASCII(.ascii	"].MbGroup[i].StartMbn=%d\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"total_mbs=%d,err_mbs=%d\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"PostPro_GetErrRatio: pParam = NULL\012\000" )
.LC11:
	ASCII(.ascii	"PostPro_GetErrRatio: pDecParam = NULL\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"err_ratio=%d\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
