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
	.global	VDMHAL_V300R001_GetHalMemSize
	.type	VDMHAL_V300R001_GetHalMemSize, %function
VDMHAL_V300R001_GetHalMemSize:
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
	mov	r0, #36864
	movt	r0, 65
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_GetHalMemSize, .-VDMHAL_V300R001_GetHalMemSize
	.align	2
	.global	VDMHAL_V300R001_OpenHAL
	.type	VDMHAL_V300R001_OpenHAL, %function
VDMHAL_V300R001_OpenHAL:
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
	subs	r3, r0, #0
	ldreq	r1, .L24
	ldreq	r3, .L24+4
	beq	.L17
	ldmia	r3, {r7, r8}
	ldr	r4, [r3, #8]
	cmp	r7, #0
	beq	.L19
	movw	r3, #36863
	movt	r3, 65
	cmp	r8, r3
	ble	.L20
	cmp	r4, #1
	bhi	.L21
	cmp	r4, #0
	bgt	.L22
	movw	r2, #1208
	ldr	r5, .L24+8
	mul	r10, r2, r4
	ldr	r9, .L24
	mov	r1, #0
	add	r6, r5, r10
	ldr	r3, [r9, #48]
	mov	r0, r6
	blx	r3
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r3, [r9, #68]
	ldr	r1, .L24+12
	mov	r2, r0
	str	r0, [r5, r10]
	mov	r0, #22
	blx	r3
	mov	r0, #0
	movt	r0, 63686
	bl	MEM_Phy2Vir
	ldr	r3, [r9, #68]
	ldr	r1, .L24+16
	mov	r2, r0
	str	r0, [r6, #8]
	mov	r0, #22
	blx	r3
	add	r0, r7, #1020
	add	r0, r0, #3
	add	r2, r10, #28
	bic	r0, r0, #1020
	add	r3, r10, #868
	bic	r0, r0, #3
	add	r2, r5, r2
	add	r3, r5, r3
	add	ip, r8, r7
	mov	r1, r0
	rsb	ip, r0, ip
	str	r0, [r6, #16]
	str	ip, [r6, #20]
	mov	ip, #1024
	str	ip, [r6, #24]
.L10:
	str	r1, [r2, #4]!
	cmp	r2, r3
	add	r1, r1, #1280
	bne	.L10
	movw	r1, #1208
	movw	r3, #45567
	mla	r1, r1, r4, r5
	movt	r3, 4
	add	r3, r0, r3
	bic	r3, r3, #32512
	bic	r3, r3, #255
	add	r6, r1, #1088
	add	ip, r3, #1769472
	add	r2, r3, #348160
	add	r10, ip, #5248
	add	ip, ip, #2048
	str	ip, [r1, #1120]
	add	r2, r2, #2048
	str	ip, [r1, #1124]
	mov	ip, #210
	str	ip, [r1, #1056]
	add	ip, r3, #294912
	add	ip, ip, #2048
	str	ip, [r1, #1172]
	movw	ip, #799
	str	ip, [r1, #1160]
	add	ip, r3, #344064
	cmp	r10, r2
	rsbcs	r2, r7, r10
	rsbcc	r2, r7, r2
	add	ip, ip, #2048
	str	ip, [r1, #1176]
	add	ip, r3, #589824
	add	r7, r3, #290816
	str	ip, [r1, #1096]
	cmp	r8, r2
	str	ip, [r1, #1104]
	add	ip, ip, #2048
	str	ip, [r1, #1108]
	add	ip, r3, #311296
	add	ip, ip, #2048
	add	r7, r7, #3072
	str	ip, [r1, #1184]
	add	r6, r6, #8
	str	r7, [r1, #1168]
	add	r7, r3, #123904
	str	ip, [r1, #1180]
	add	ip, r3, #1179648
	str	r7, [r1, #1152]
	add	r7, r3, #191488
	str	r7, [r1, #1156]
	add	r7, r0, #270336
	add	r0, r0, #266240
	add	ip, ip, #2048
	str	r10, [r1, #1128]
	add	r7, r7, #3584
	add	r10, r3, #33792
	str	r3, [r1, #1136]
	str	r3, [r1, #1084]
	add	r0, r0, #2560
	str	r3, [r1, #1088]
	str	r3, [r1, #1092]
	add	r3, r3, #78848
	str	ip, [r1, #1112]
	str	ip, [r1, #1116]
	mov	ip, #0
	str	r10, [r1, #1140]
	str	r3, [r1, #1144]
	str	r3, [r1, #1148]
	str	r7, [r1, #1100]
	str	r0, [r1, #1080]
	str	ip, [r1, #1132]
	bcc	.L11
	bl	H264HAL_V300R001_InitHal
	mov	r7, r0
	ldr	r0, [r6, #4]
	bl	HEVCHAL_V300R001_InitHal
	cmp	r0, #0
	mvnne	r6, #0
	beq	.L23
.L12:
	movw	r3, #1208
	mla	r4, r3, r4, r5
	ldr	r0, [r4, #1080]
	bl	H264HAL_V300R001_InitHal
	cmp	r0, #0
	moveq	r0, r6
	mvnne	r0, #0
.L4:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L23:
	adds	r0, r7, #0
	movne	r0, #1
	rsb	r6, r0, #0
	b	.L12
.L22:
	ldr	r1, .L24
	mov	r3, r4
	mov	r0, #0
	ldr	r2, .L24+20
	str	r0, [sp]
	ldr	r4, [r1, #68]
	ldr	r1, .L24+24
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L19:
	ldr	r1, .L24
	mov	r0, r7
	ldr	r3, .L24+28
.L17:
	ldr	r4, [r1, #68]
	ldr	r2, .L24+20
	ldr	r1, .L24+32
	blx	r4
	mvn	r0, #0
	b	.L4
.L11:
	ldr	r4, [r9, #68]
	mov	r3, r8
	mov	r0, ip
	ldr	r1, .L24+36
	blx	r4
	mvn	r0, #0
	b	.L4
.L20:
	ldr	r1, .L24
	mov	r0, #0
	ldr	r3, .L24+40
	b	.L17
.L21:
	ldr	r3, .L24
	mov	r0, #0
	ldr	r1, .L24+44
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L4
.L25:
	.align	2
.L24:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	g_HwMem
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR0
	.word	.LC5
	.word	.LC2
	.word	.LC1
	.word	.LC8
	.word	.LC3
	.word	.LC4
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_OpenHAL, .-VDMHAL_V300R001_OpenHAL
	.align	2
	.global	VDMHAL_V300R001_CloseHAL
	.type	VDMHAL_V300R001_CloseHAL, %function
VDMHAL_V300R001_CloseHAL:
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
	cmp	r0, #1
	mov	r4, r0
	bhi	.L32
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L33
	ldr	r3, [r3, #56]
	cmp	r3, #0
	beq	.L30
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L32:
	ldr	r3, .L33+4
	mov	r0, #0
	ldr	r1, .L33+8
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L30:
	ldr	ip, .L33+4
	mov	r0, r3
	movw	r2, #374
	ldr	r1, .L33+12
	ldr	r3, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L34:
	.align	2
.L33:
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC9
	.word	.LC10
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_CloseHAL, .-VDMHAL_V300R001_CloseHAL
	.global	__aeabi_idiv
	.align	2
	.global	VDMHAL_V300R001_ArrangeMem
	.type	VDMHAL_V300R001_ArrangeMem, %function
VDMHAL_V300R001_ArrangeMem:
	UNWIND(.fnstart)
	@ args = 20, pretend = 0, frame = 56
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
	ldr	r8, [fp, #16]
	mov	r4, r0
	str	r1, [fp, #-76]
	cmn	r8, #2
	mov	r7, r2
	str	r3, [fp, #-72]
	ldr	r9, [fp, #4]
	ldr	r6, [fp, #20]
	beq	.L113
	cmp	r8, #0
	blt	.L114
	mov	r0, r8
	bl	VCTRL_GetVidStd
	ldr	r3, .L184
	mov	r10, r0
	ldr	r0, [r3, r8, asl #2]
	ldr	r3, [r0, #1404]
	cmp	r3, #1
	beq	.L163
.L37:
	cmp	r4, #0
	subne	r2, r7, #32
	movwne	r3, #8160
	beq	.L164
	cmp	r2, r3
	bhi	.L76
	ldr	r2, [fp, #-72]
	sub	r2, r2, #32
	cmp	r2, r3
	bhi	.L76
	cmp	r6, #0
	beq	.L165
	ldr	r3, .L184+4
	cmp	r9, #20
	mov	r2, #812
	mov	r1, #0
	mov	r0, r6
	movge	r9, #20
	str	r3, [fp, #-84]
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [fp, #-72]
	add	r2, r7, #15
	add	r1, r3, #15
	ldr	r3, .L184+8
	mov	r2, r2, asr #4
	mov	r1, r1, asr #4
	cmp	r2, #45
	cmple	r1, #36
	ldrb	lr, [r3]	@ zero_extendqisi2
	mov	r0, r2, asl #4
	mov	r3, r1, asl #4
	movle	ip, #64
	movgt	ip, #32
	cmp	lr, #1
	moveq	ip, #64
	cmp	r10, #17
	beq	.L82
	mul	r5, r2, ip
	mul	r5, r5, r1
	ldr	r1, [fp, #-76]
	add	r5, r5, #127
	bic	r5, r5, #127
	mul	r2, r9, r5
	cmp	r2, r1
	str	r2, [fp, #-80]
	bge	.L111
	add	r1, r0, #255
	mov	r2, r5, asr #1
	bic	r1, r1, #255
	str	r9, [r6, #800]
	str	r2, [r6, #796]
.L110:
	sub	r2, r0, #1
	mov	ip, r1, asl #4
	cmp	r2, #2048
	str	ip, [r6]
	movcc	r9, #16
	bcc	.L84
	sub	r2, r0, #2048
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r9, #32
	bcc	.L84
	sub	r2, r0, #4096
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r9, #48
	bcs	.L166
.L84:
	ldr	r2, [fp, #12]
	cmp	r2, #1
	beq	.L167
	cmp	r10, #17
	beq	.L168
	adds	r2, r3, #31
	addmi	r2, r3, #62
	cmp	r8, #0
	mov	r2, r2, asr #5
	mov	r0, r2
	mov	ip, r2, asl #7
	sub	ip, ip, r0, asl #5
	mul	r2, r1, r2
	mul	ip, r9, ip
	mov	r7, r2, asl #6
	sub	r7, r7, r2, asl #4
	add	r7, r7, ip, lsr #1
	blt	.L90
.L86:
	mov	r0, r8
	str	r3, [fp, #-96]
	str	r1, [fp, #-92]
	bl	VCTRL_GetChanWidth
	str	r0, [fp, #-88]
	mov	r0, r8
	bl	VCTRL_GetChanHeight
	ldr	r2, [fp, #-88]
	ldr	r1, [fp, #-92]
	ldr	r3, [fp, #-96]
	cmn	r0, #1
	cmnne	r2, #1
	beq	.L169
	add	r2, r2, #15
	add	r0, r0, #15
	bic	r2, r2, #15
	bic	r0, r0, #15
	sub	lr, r2, #1
	add	ip, r2, #255
	cmp	lr, #2048
	bic	ip, ip, #255
	movcc	lr, #16
	bcc	.L92
	sub	lr, r2, #2048
	sub	lr, lr, #1
	cmp	lr, #2048
	movcc	lr, #32
	bcs	.L170
.L92:
	ldr	r2, [fp, #12]
	cmp	r2, #1
	beq	.L171
	adds	r2, r0, #31
	addmi	r2, r0, #62
	mov	r2, r2, asr #5
	mov	r0, r2, asl #7
	mul	ip, ip, r2
	sub	r2, r0, r2, asl #5
	mul	lr, lr, r2
	mov	r2, ip, asl #6
	sub	ip, r2, ip, asl #4
	add	ip, ip, lr, lsr #1
.L94:
	cmp	ip, r7
	blt	.L172
	cmp	r10, #17
	beq	.L95
.L175:
	adds	r0, r3, #31
	addmi	r0, r3, #62
	mov	r0, r0, asr #5
	mul	r2, r0, r1
.L90:
	mov	r9, r9, asl #5
	mov	r2, r2, asl #5
	mla	r0, r0, r9, r2
	str	r0, [r6, #408]
.L96:
	ldr	r3, [fp, #8]
	cmp	r3, #0
	streq	r3, [r6, #420]
	bne	.L173
.L98:
	ldr	r3, [fp, #-84]
	mov	r0, #0
	ldr	r2, .L184+12
	ldr	r1, .L184+16
	ldr	r4, [r3, #68]
	ldr	r3, .L184+20
	blx	r4
	mvn	r3, #0
.L150:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L114:
	mov	r10, #20
	b	.L37
.L173:
	ldr	r3, [fp, #8]
	add	r8, r4, #1020
	ldr	r2, [fp, #-80]
	add	r8, r8, #3
	cmp	r3, #32
	ldr	r3, [fp, #-76]
	bic	r8, r8, #1020
	mov	r1, r7
	rsb	r0, r2, r3
	bic	r8, r8, #3
	ldr	r3, [fp, #8]
	rsb	r9, r4, r8
	rsb	r0, r9, r0
	movge	r10, #32
	movlt	r10, r3
	bl	__aeabi_idiv
	cmp	r10, r0
	movlt	r0, r10
	cmp	r0, #0
	str	r0, [r6, #420]
	beq	.L98
	ldrgt	r1, [r6, #804]
	addgt	r2, r0, #1
	movgt	r3, #1
	ble	.L174
.L101:
	str	r8, [r6, r3, asl #3]
	add	r3, r3, #1
	cmp	r3, r2
	add	r8, r8, r7
	bne	.L101
	mla	r7, r7, r0, r9
	add	r3, r0, r1
	add	r1, r6, #260
	str	r3, [r6, #804]
	mov	r2, #0
	add	r3, r7, r4
.L103:
	add	r2, r2, #1
	str	r3, [r1, #4]!
	cmp	r2, r0
	add	r3, r3, #32
	bne	.L103
.L109:
	ldr	r1, [r6, #800]
	add	r7, r7, r0, lsl #5
	add	r4, r7, r4
	cmp	r1, #0
	ldrgt	r0, [r6, #808]
	movgt	r2, r6
	movgt	r3, #0
	ble	.L106
.L105:
	add	r3, r3, #1
	str	r4, [r2, #556]
	cmp	r3, r1
	add	r4, r4, r5
	add	r2, r2, #12
	bne	.L105
	add	r3, r1, r0
	str	r3, [r6, #808]
.L106:
	mla	r7, r1, r5, r7
	mov	r3, #0
	mov	r0, r3
	str	r7, [r6, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L113:
	mov	r10, #17
	b	.L37
.L82:
	mul	r5, r0, r1
	ldr	r1, [fp, #-76]
	add	r5, r5, #127
	bic	r5, r5, #127
	mul	r2, r9, r5
	cmp	r2, r1
	str	r2, [fp, #-80]
	bge	.L111
	add	r1, r7, #255
	mov	r2, r5, asr #1
	str	r9, [r6, #800]
	bic	r1, r1, #255
	str	r2, [r6, #796]
	b	.L110
.L167:
	mul	r7, r3, r1
	cmp	r8, #0
	add	r7, r7, r7, lsl #1
	bge	.L86
	cmp	r10, #17
	bne	.L175
.L95:
	ldr	r3, [fp, #-72]
	mul	r2, r3, r1
.L89:
	str	r2, [r6, #408]
	b	.L96
.L170:
	sub	lr, r2, #4096
	sub	lr, lr, #1
	cmp	lr, #2048
	movcc	lr, #48
	bcc	.L92
	sub	r2, r2, #6144
	sub	r2, r2, #1
	cmp	r2, #2048
	movcs	lr, #16
	movcc	lr, #64
	b	.L92
.L166:
	sub	r0, r0, #6144
	sub	r0, r0, #1
	cmp	r0, #2048
	movcs	r9, #16
	movcc	r9, #64
	b	.L84
.L168:
	ldr	r2, [fp, #-72]
	cmp	r8, #0
	mul	r2, r2, r1
	add	r7, r2, r2, lsl #1
	mov	r7, r7, asr #1
	bge	.L86
	b	.L89
.L171:
	mul	ip, r0, ip
	add	ip, ip, ip, lsl #1
	b	.L94
.L163:
	sub	r2, r7, #32
	movw	r3, #8160
	cmp	r2, r3
	add	r2, r0, #225280
	ldr	r4, [r2, #3288]
	bhi	.L38
	ldr	r2, [fp, #-72]
	sub	r2, r2, #32
	cmp	r2, r3
	bls	.L39
.L38:
	ldr	r3, .L184+4
	mov	r0, #0
	ldr	r2, .L184+24
	mov	r1, r3
	str	r3, [fp, #-84]
	ldr	r4, [r1, #68]
	ldr	r3, .L184+28
	ldr	r1, .L184+16
	blx	r4
	mvn	r2, #0
.L40:
	ldr	r3, [fp, #-84]
	mov	r0, #31
	ldr	r1, .L184+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L150
.L174:
	mla	r7, r7, r0, r9
	b	.L109
.L76:
	ldr	r1, .L184+4
	mov	r0, #0
	ldr	r3, .L184+28
.L156:
	ldr	r4, [r1, #68]
	ldr	r2, .L184+12
	ldr	r1, .L184+16
	blx	r4
	mvn	r3, #0
	b	.L150
.L39:
	ldr	r3, [fp, #-72]
	add	r2, r7, #15
	ldr	r1, .L184+8
	add	r3, r3, #15
	mov	r2, r2, asr #4
	mov	r3, r3, asr #4
	ldrb	lr, [r1]	@ zero_extendqisi2
	cmp	r2, #45
	cmple	r3, #36
	mov	ip, r2, asl #4
	mov	r5, r3, asl #4
	str	r5, [fp, #-96]
	movle	r1, #64
	movgt	r1, #32
	cmp	lr, #1
	moveq	r1, #64
	cmp	r10, #17
	beq	.L176
	mul	r2, r1, r2
	add	r5, ip, #255
	bic	r5, r5, #255
	mul	r3, r2, r3
	add	r3, r3, #127
	bic	r3, r3, #127
	str	r3, [fp, #-76]
.L107:
	sub	r3, ip, #1
	cmp	r3, #2048
	movcc	r9, #16
	bcc	.L45
	sub	r3, ip, #2048
	sub	r3, r3, #1
	cmp	r3, #2048
	movcc	r9, #32
	bcc	.L45
	sub	r3, ip, #4096
	sub	r3, r3, #1
	cmp	r3, #2048
	movcc	r9, #48
	bcc	.L45
	sub	ip, ip, #6144
	sub	ip, ip, #1
	cmp	ip, #2048
	movcs	r9, #0
	movcc	r9, #64
.L45:
	ldr	r3, [fp, #12]
	cmp	r3, #1
	beq	.L177
	cmp	r10, #17
	beq	.L178
	ldr	r3, [fp, #-96]
	add	r9, r5, r9
	add	r0, r0, #228352
	mov	r2, #820
	adds	ip, r3, #31
	mov	r1, #0
	addmi	ip, r3, #62
	ldr	r3, .L184+4
	add	r0, r0, #888
	mov	r5, r5, asl #4
	mov	ip, ip, asr #5
	str	r3, [fp, #-84]
	mul	r9, ip, r9
	ldr	r3, [r3, #48]
	mov	ip, r9, asl #6
	sub	ip, ip, r9, asl #4
	str	ip, [fp, #-80]
	blx	r3
	ldr	r3, .L184
	ldr	r2, [r3, r8, asl #2]
	ldr	r3, [fp, #-76]
	add	r0, r2, #225280
	mov	r1, r3, asr #1
	add	r3, r2, #229376
	str	r1, [r3, #660]
	ldr	r2, [r2, #1412]
	ldr	r1, [r0, #3292]
	add	r2, r1, r2
	cmp	r2, #20
	str	r1, [fp, #-88]
	movge	r2, #20
	str	r2, [r3, #664]
	str	r2, [fp, #-92]
	str	r5, [r0, #3960]
.L51:
	mov	r9, r9, asl #5
.L155:
	str	r9, [r3, #272]
	ldr	r1, [fp, #-76]
	ldr	r0, [fp, #-80]
	add	r2, r1, r0
	str	r1, [r3, #680]
	adds	r2, r2, #1056
	str	r0, [r3, #676]
	bmi	.L40
	ldr	r3, .L184
	cmp	r4, r2
	ldr	r4, [r3, r8, asl #2]
	add	r9, r4, #225280
	beq	.L179
.L56:
	add	r5, r4, #229376
	str	r2, [r9, #3288]
	add	r4, r4, #228352
	ldr	r2, [r5, #728]
	add	r3, r4, #248
	cmp	r2, #1
	addeq	lr, r4, #888
	moveq	r2, r3
	beq	.L60
.L108:
	add	r4, r4, #888
	mvn	r2, #0
.L61:
	strb	r2, [r3, #16]
	add	r3, r3, #20
	cmp	r3, r4
	bne	.L61
	ldr	r4, .L184+36
	ldr	r5, [r4]
	cmp	r5, #0
	beq	.L63
	ldr	r3, .L184
	mov	r1, #122
	sub	r2, fp, #68
	mov	r0, r8
	ldr	ip, [r3, r8, asl #2]
	mov	r3, #16
	add	ip, ip, #229376
	ldr	lr, [ip, #716]
	str	lr, [fp, #-68]
	ldr	lr, [ip, #720]
	str	lr, [fp, #-64]
	ldr	lr, [ip, #724]
	str	lr, [fp, #-60]
	ldr	ip, [ip, #728]
	str	ip, [fp, #-56]
	blx	r5
	ldr	r4, [r4]
	cmp	r4, #0
	beq	.L63
	ldr	r3, [fp, #-88]
	sub	r2, fp, #68
	ldr	r1, [fp, #-92]
	ldr	r0, [fp, #-76]
	str	r3, [fp, #-68]
	ldr	ip, [fp, #-72]
	ldr	r3, [fp, #-80]
	str	r1, [fp, #-60]
	mov	r1, #121
	str	r0, [fp, #-56]
	mov	r0, r8
	str	r3, [fp, #-64]
	mov	r3, #24
	str	r7, [fp, #-52]
	str	ip, [fp, #-48]
	blx	r4
.L63:
	ldr	r3, .L184
	mov	r2, #0
	ldr	r4, [r3, r8, asl #2]
	ldr	r3, [fp, #-84]
	add	r4, r4, #229376
	ldr	r3, [r3]
	str	r2, [r4, #708]
	blx	r3
	ldr	r3, .L184
	mov	r1, #1
	ldr	r2, [r3, r8, asl #2]
	mov	r3, #2
	add	ip, r2, #225280
	add	r2, r2, #229376
	str	r0, [r4, #684]
	str	r1, [ip, #3272]
	str	r1, [r2, #732]
	b	.L150
.L58:
	add	r2, r2, #20
	cmp	r2, lr
	beq	.L108
.L60:
	ldrb	r1, [r2, #16]	@ zero_extendqisi2
	cmp	r1, #255
	beq	.L58
	ldr	r0, [r5, #716]
	ldr	r1, [r2, #8]
	cmp	r0, r1
	bcc	.L58
	ldr	ip, [r2, #12]
	add	ip, r1, ip
	cmp	r0, ip
	bcs	.L58
	str	r1, [r5, #716]
	mov	r1, #1
	ldr	r0, [r2, #4]
	str	r0, [r5, #720]
	ldr	r2, [r2, #12]
	str	r1, [r5, #728]
	str	r2, [r5, #724]
	b	.L108
.L179:
	ldr	r3, [r9, #3312]
	cmp	r3, #1
	beq	.L56
	cmp	r6, #0
	beq	.L180
	ldr	r3, [r9, #3292]
	add	r5, r4, #229376
	add	r2, r4, #228352
	cmp	r3, #0
	ldr	r10, [r5, #676]
	add	r3, r2, #888
	str	r3, [fp, #-72]
	beq	.L181
.L66:
	ldr	r3, .L184
	ldr	r7, .L184
	ldr	r3, [r3, r8, asl #2]
	add	r3, r3, #225280
	ldr	r2, [r3, #3296]
	cmp	r2, #30
	bgt	.L182
.L67:
	ldr	r3, [fp, #-84]
	mov	r0, #8
	str	r2, [r5, #284]
	ldr	r3, [r3, #12]
	blx	r3
	ldr	r3, .L184
	ldr	ip, [r3, r8, asl #2]
	add	r0, ip, #229376
	ldr	r3, [r0, #708]
	cmp	r3, #0
	beq	.L72
	ldr	r8, [r5, #668]
	add	ip, ip, #228352
	add	ip, ip, #256
	mov	r1, #0
	add	r2, r8, #28416
	add	lr, r8, #57344
	add	r2, r2, #240
	add	lr, lr, #31
	add	r8, r8, #1
	str	r4, [fp, #-76]
	add	r2, r4, r2, lsl #3
	add	lr, r4, lr, lsl #2
.L71:
	ldr	r3, [ip], #20
	add	r7, r8, r1
	mov	r4, #1
	str	r4, [r2, #4]
	add	r3, r3, #1020
	add	r1, r1, r4
	add	r3, r3, #3
	add	r2, r2, #8
	bic	r3, r3, #1020
	bic	r3, r3, #3
	str	r3, [r2, #-8]
	add	r3, r3, r10
	str	r3, [lr, #4]!
	str	r7, [r5, #668]
	ldr	r3, [r0, #708]
	cmp	r1, r3
	bcc	.L71
	ldr	r4, [fp, #-76]
.L72:
	ldr	lr, [r5, #664]
	cmp	lr, #0
	beq	.L70
	ldr	ip, [r5, #672]
	mov	r7, #1
	mov	r1, #0
	mov	r3, ip, asl #4
	sub	r3, r3, ip, asl #2
	add	ip, ip, r7
	add	r3, r3, #229376
	add	r3, r3, #420
	add	r4, r4, r3
.L73:
	ldr	r8, [r0, #780]
	add	r2, ip, r1
	ldr	r3, [r0, #680]
	mla	r3, r3, r1, r8
	add	r1, r1, #1
	cmp	r1, lr
	str	r3, [r4], #12
	ldr	r8, [r5, #672]
	mov	r3, r8, asl #4
	sub	r3, r3, r8, asl #2
	add	r3, r9, r3
	add	r3, r3, #4480
	str	r7, [r3, #40]
	str	r2, [r5, #672]
	bcc	.L73
.L70:
	ldr	r4, [fp, #-84]
	mov	r2, #812
	ldr	r1, [fp, #-72]
	mov	r0, r6
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r4, #16]
	mov	r0, #8
	blx	r3
	mov	r3, #0
	b	.L150
.L164:
	ldr	r1, .L184+4
	mov	r0, r4
	ldr	r3, .L184+40
	b	.L156
.L111:
	ldr	r3, [fp, #-84]
	mov	r0, #0
	ldr	r2, .L184+12
	ldr	r1, .L184+16
	ldr	r4, [r3, #68]
	ldr	r3, .L184+44
	blx	r4
	mvn	r3, #0
	b	.L150
.L172:
	ldr	r3, [fp, #-84]
	mov	r0, #0
	ldr	r2, .L184+12
	ldr	r1, .L184+16
	ldr	r4, [r3, #68]
	ldr	r3, .L184+48
	blx	r4
	mvn	r3, #0
	b	.L150
.L169:
	ldr	r3, [fp, #-84]
	mov	r0, #0
	ldr	r1, .L184+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L150
.L165:
	ldr	r1, .L184+4
	mov	r0, r6
	ldr	r3, .L184+56
	b	.L156
.L176:
	mul	r3, ip, r3
	add	r5, r7, #255
	bic	r5, r5, #255
	add	r3, r3, #127
	bic	r3, r3, #127
	str	r3, [fp, #-76]
	b	.L107
.L177:
	ldr	r3, [fp, #-96]
	add	r0, r0, #228352
	mov	r2, #820
	mov	r1, #0
	add	r0, r0, #888
	mul	ip, r5, r3
	ldr	r3, .L184+4
	str	r3, [fp, #-84]
	ldr	r3, [r3, #48]
	add	ip, ip, ip, lsl #1
	str	ip, [fp, #-80]
	blx	r3
	ldr	r3, .L184
	mov	r1, r5, asl #4
	ldr	r2, [r3, r8, asl #2]
	ldr	r3, [fp, #-76]
	add	r0, r2, #225280
	mov	ip, r3, asr #1
	add	r3, r2, #229376
	str	ip, [r3, #660]
	ldr	r2, [r2, #1412]
	ldr	ip, [r0, #3292]
	add	r2, ip, r2
	cmp	r2, #20
	str	ip, [fp, #-88]
	movge	r2, #20
	cmp	r10, #17
	str	r2, [r3, #664]
	str	r2, [fp, #-92]
	str	r1, [r0, #3960]
	beq	.L183
	ldr	r1, [fp, #-96]
	add	r5, r5, r9
	adds	r2, r1, #31
	addmi	r9, r1, #62
	movpl	r9, r2
	mov	r9, r9, asr #5
	mul	r9, r5, r9
	b	.L51
.L182:
	ldr	r3, [fp, #-84]
	mov	r0, #31
	ldr	r1, .L184+60
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r7, r8, asl #2]
	mov	r1, #30
	add	r3, r3, #225280
	mov	r2, r1
	str	r1, [r3, #3296]
	b	.L67
.L181:
	ldr	r3, [fp, #-84]
	mov	r0, #31
	ldr	r1, .L184+64
	ldr	r3, [r3, #68]
	blx	r3
	b	.L66
.L178:
	ldr	r3, [fp, #-72]
	add	r0, r0, #228352
	mov	r2, #820
	mov	r1, #0
	add	r0, r0, #888
	mul	r9, r5, r3
	ldr	r3, .L184+4
	mov	r5, r5, asl #4
	str	r3, [fp, #-84]
	ldr	r3, [r3, #48]
	add	ip, r9, r9, lsl #1
	mov	ip, ip, asr #1
	str	ip, [fp, #-80]
	blx	r3
	ldr	r3, .L184
	ldr	r2, [r3, r8, asl #2]
	ldr	r3, [fp, #-76]
	add	r0, r2, #225280
	mov	r1, r3, asr #1
	add	r3, r2, #229376
	str	r1, [r3, #660]
	ldr	r2, [r2, #1412]
	ldr	r1, [r0, #3292]
	add	r2, r1, r2
	cmp	r2, #20
	str	r1, [fp, #-88]
	movge	r2, #20
	str	r2, [r3, #664]
	str	r2, [fp, #-92]
	str	r5, [r0, #3960]
	b	.L155
.L183:
	ldr	r2, [fp, #-72]
	mul	r9, r5, r2
	b	.L155
.L180:
	ldr	r3, [fp, #-84]
	mov	r0, r6
	ldr	r2, .L184+68
	ldr	r1, .L184+16
	ldr	r4, [r3, #68]
	ldr	r3, .L184+72
	blx	r4
	mvn	r3, #0
	b	.L150
.L185:
	.align	2
.L184:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_not_direct_8x8_inference_flag
	.word	.LANCHOR0+88
	.word	.LC1
	.word	.LC21
	.word	.LANCHOR0+24
	.word	.LC11
	.word	.LC12
	.word	g_event_report
	.word	.LC16
	.word	.LC18
	.word	.LC20
	.word	.LC19
	.word	.LC17
	.word	.LC15
	.word	.LC14
	.word	.LANCHOR0+52
	.word	.LC13
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_ArrangeMem, .-VDMHAL_V300R001_ArrangeMem
	.align	2
	.global	VDMHAL_V300R001_ArrangeMem_BTL
	.type	VDMHAL_V300R001_ArrangeMem_BTL, %function
VDMHAL_V300R001_ArrangeMem_BTL:
	UNWIND(.fnstart)
	@ args = 28, pretend = 0, frame = 8
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
	str	r1, [fp, #-48]
	mov	r6, r3
	mov	r9, r2
	ldr	r8, [fp, #4]
	ldr	r7, [fp, #20]
	ldreq	r1, .L239
	ldreq	r3, .L239+4
	beq	.L231
	ldr	r3, [fp, #16]
	sub	r2, r2, #32
	cmp	r3, #1
	movw	r3, #8160
	beq	.L234
	cmp	r2, r3
	bhi	.L192
	sub	r2, r6, #32
	cmp	r2, r3
	bhi	.L192
.L191:
	cmp	r7, #0
	beq	.L235
	ldr	r5, .L239
	cmp	r8, #20
	mov	r2, #812
	mov	r1, #0
	mov	r0, r7
	movge	r8, #20
	ldr	r3, [r5, #48]
	add	r6, r6, #15
	blx	r3
	ldr	r1, .L239+8
	add	r2, r9, #15
	mov	r6, r6, asr #4
	mov	r3, r2, asr #4
	ldrb	ip, [r1]	@ zero_extendqisi2
	cmp	r3, #45
	cmple	r6, #36
	mov	lr, r6, asl #4
	mov	r0, r3, asl #4
	movle	r1, #64
	movgt	r1, #32
	cmp	ip, #1
	moveq	r1, #64
	mul	r3, r3, r1
	mul	r6, r6, r3
	ldr	r3, [fp, #-48]
	add	r6, r6, #127
	bic	r6, r6, #127
	mul	r10, r8, r6
	cmp	r10, r3
	bge	.L236
	add	r3, r4, #1020
	sub	r1, r0, #1
	add	ip, r0, #255
	add	r3, r3, #3
	cmp	r1, #2048
	bic	r3, r3, #1020
	bic	ip, ip, #255
	bic	r3, r3, #3
	rsb	r1, r4, r3
	str	r8, [r7, #800]
	str	r1, [fp, #-52]
	movcc	r0, #16
	mov	r1, ip, asl #4
	str	r1, [r7]
	mov	r1, r6, asr #1
	str	r1, [r7, #796]
	bcc	.L197
	sub	r1, r0, #2048
	sub	r1, r1, #1
	cmp	r1, #2048
	movcc	r0, #32
	bcc	.L197
	sub	r1, r0, #4096
	sub	r1, r1, #1
	cmp	r1, #2048
	movcc	r0, #48
	bcs	.L237
.L197:
	adds	r1, lr, #31
	ldr	r5, [fp, #28]
	addmi	r1, lr, #62
	cmp	r5, #0
	mov	r1, r1, asr #5
	ldreq	r2, [fp, #28]
	mul	r0, r1, r0
	mul	r1, ip, r1
	mov	ip, r0, asl #5
	add	r5, ip, r1, lsl #5
	str	r5, [r7, #408]
	beq	.L198
	add	r5, r2, #15
	cmp	r2, #0
	movlt	r2, r5
	mov	r5, r2, asr #4
	adds	r2, r5, #7
	addmi	r2, r5, #14
	mov	r2, r2, asr #3
	mov	r2, r2, asl #4
	mul	r2, lr, r2
	add	r5, r2, #7
	cmp	r2, #0
	movlt	r2, r5
	mov	r2, r2, asr #3
	add	r2, r2, r2, lsl #1
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
	adds	r5, r2, #127
	addmi	r5, r2, #254
	bic	r2, r5, #127
.L198:
	ldr	r5, [fp, #24]
	cmp	r5, #0
	bne	.L238
	ldr	lr, [fp, #12]
	cmp	lr, #0
	beq	.L214
	ldr	lr, [fp, #12]
	ldr	r5, [fp, #24]
	cmp	lr, #6
	movge	r9, lr
	movlt	r9, #6
	str	r9, [r7, #552]
.L203:
	add	r5, r2, r5
	cmp	r9, #0
	mulle	r5, r9, r5
	ble	.L201
	add	lr, r7, #420
	mov	r2, #0
.L204:
	add	r2, r2, #1
	str	r3, [lr, #4]!
	cmp	r2, r9
	add	r3, r3, r5
	bne	.L204
	mul	r5, r5, r2
.L201:
	ldr	r3, [fp, #8]
	cmp	r3, #0
	ldr	r3, [fp, #-52]
	add	r5, r3, r5
	bne	.L205
	ldr	r3, [fp, #8]
	mov	r9, r3
	str	r3, [r7, #420]
.L206:
	cmp	r8, #0
	add	r5, r5, r9
	add	r4, r5, r4
	movgt	r0, r7
	movgt	r1, #0
	ble	.L213
.L212:
	add	r1, r1, #1
	str	r4, [r0, #556]
	cmp	r1, r8
	add	r4, r4, r6
	add	r0, r0, #12
	bne	.L212
.L213:
	mov	r0, #0
	add	r5, r10, r5
	str	r5, [r7, #4]
.L228:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L238:
	adds	r5, r9, #127
	addmi	r5, r9, #254
	ldr	r9, [fp, #12]
	mov	r5, r5, asr #7
	cmp	r9, #0
	mov	r9, r5, asl #9
	sub	r5, r9, r5, asl #7
	mul	r5, lr, r5
	mov	r5, r5, asr #1
	beq	.L214
	ldr	lr, [fp, #12]
	str	lr, [r7, #552]
	mov	r9, lr
	b	.L203
.L205:
	ldr	r3, [fp, #24]
	rsb	r0, ip, r0, lsl #7
	cmp	r3, #0
	ldr	r3, [fp, #8]
	add	r9, r3, #2
	ldreq	r3, [fp, #12]
	addeq	r9, r9, r3
	mov	r3, r1, asl #6
	sub	r1, r3, r1, asl #4
	ldr	r3, [fp, #-48]
	rsb	r2, r10, r3
	add	r3, r1, r0, lsr #1
	ldr	r1, [fp, #-52]
	str	r3, [fp, #-48]
	rsb	r0, r1, r2
	mov	r1, r3
	rsb	r0, r5, r0
	bl	__aeabi_idiv
	ldr	r3, [fp, #-48]
	cmp	r0, #32
	movge	r0, #32
	cmp	r0, r9
	movge	r0, r9
	cmp	r0, #0
	str	r0, [r7, #420]
	addgt	r1, r5, r4
	addgt	lr, r0, #1
	movgt	r2, #1
	ble	.L230
.L210:
	str	r1, [r7, r2, asl #3]
	add	r2, r2, #1
	cmp	r2, lr
	add	r1, r1, r3
	bne	.L210
.L230:
	mul	r9, r0, r3
	b	.L206
.L214:
	mov	r5, #0
	str	r5, [r7, #552]
	b	.L201
.L234:
	cmp	r2, r3
	bhi	.L192
	sub	r2, r6, #32
	movw	r3, #16352
	cmp	r2, r3
	bls	.L191
.L192:
	ldr	r1, .L239
	mov	r0, #0
	ldr	r3, .L239+12
.L231:
	ldr	r4, [r1, #68]
	ldr	r2, .L239+16
	ldr	r1, .L239+20
	blx	r4
	mvn	r0, #0
	b	.L228
.L237:
	sub	r0, r0, #6144
	sub	r0, r0, #1
	cmp	r0, #2048
	movcs	r0, #16
	movcc	r0, #64
	b	.L197
.L236:
	ldr	r4, [r5, #68]
	mov	r0, #0
	ldr	r3, .L239+24
	ldr	r2, .L239+16
	ldr	r1, .L239+20
	blx	r4
	mvn	r0, #0
	b	.L228
.L235:
	ldr	r1, .L239
	mov	r0, r7
	ldr	r3, .L239+28
	b	.L231
.L240:
	.align	2
.L239:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC22
	.word	g_not_direct_8x8_inference_flag
	.word	.LC11
	.word	.LANCHOR0+116
	.word	.LC1
	.word	.LC18
	.word	.LC17
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_ArrangeMem_BTL, .-VDMHAL_V300R001_ArrangeMem_BTL
	.align	2
	.global	VDMHAL_V300R001_ResetVdm
	.type	VDMHAL_V300R001_ResetVdm, %function
VDMHAL_V300R001_ResetVdm:
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
	subs	r8, r0, #0
	beq	.L243
	cmp	r8, #1
	bne	.L262
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r2, .L265
	mov	r0, #0
	mov	r3, r8
	str	r0, [sp]
	ldr	r1, .L265+4
	ldr	r4, [r2, #68]
	ldr	r2, .L265+8
	blx	r4
.L241:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L262:
	ldr	r3, .L265
	mov	r0, #0
	ldr	r1, .L265+12
	ldr	r3, [r3, #68]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	r3
.L243:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L263
	ldr	r5, .L265+16
	ldr	r6, .L265+20
	ldr	r3, [r5]
	ldr	r1, [r6]
	ldr	r7, [r3, #36]
	ldr	r4, [r1, #120]
	tst	r4, #1
	beq	.L241
	orr	r4, r4, #64
	str	r4, [r1, #120]
	ldr	r3, [r1, #372]
	tst	r3, #4
	bne	.L248
	mov	r3, #1
	movw	r0, #10000
	b	.L250
.L264:
	add	r3, r3, #1
	cmp	r3, r0
	beq	.L251
.L250:
	ldr	r2, [r1, #372]
	tst	r2, #4
	beq	.L264
	movw	r2, #10000
	cmp	r3, r2
	beq	.L251
.L252:
	bfc	r4, #6, #1
	str	r4, [r1, #120]
.L253:
	ldr	r3, [r5]
	str	r7, [r3, #36]
	b	.L241
.L251:
	ldr	r3, .L265
	mov	r2, #0
	ldr	r1, .L265+24
	mov	r0, r2
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r6]
	b	.L252
.L263:
	ldr	r3, .L265
	ldr	r1, .L265+28
	ldr	r3, [r3, #68]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	r3
.L248:
	bfi	r4, r8, #6, #1
	str	r4, [r1, #120]
	b	.L253
.L266:
	.align	2
.L265:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	.word	.LANCHOR0+148
	.word	.LC23
	.word	g_HwMem
	.word	g_pstRegCrg
	.word	.LC25
	.word	.LC24
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_ResetVdm, .-VDMHAL_V300R001_ResetVdm
	.align	2
	.global	VDMHAL_V300R001_GlbReset
	.type	VDMHAL_V300R001_GlbReset, %function
VDMHAL_V300R001_GlbReset:
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
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L278
	ldr	r5, .L282
	ldr	r2, [r5]
	ldr	r4, [r2, #120]
	tst	r4, #1
	beq	.L279
	orr	r4, r4, #16
	str	r4, [r2, #120]
	ldr	r3, [r2, #372]
	tst	r3, #1
	bne	.L273
	movw	r0, #9999
	b	.L271
.L281:
	subs	r0, r0, #1
	beq	.L280
.L271:
	ldr	r3, [r2, #372]
	tst	r3, #1
	beq	.L281
.L273:
	bfc	r4, #4, #1
	str	r4, [r2, #120]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L279:
	ldr	r3, .L282+4
	mov	r0, #3
	ldr	r1, .L282+8
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L280:
	ldr	r3, .L282+4
	ldr	r1, .L282+12
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r2, [r5]
	b	.L273
.L278:
	ldr	r3, .L282+4
	ldr	r1, .L282+16
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L283:
	.align	2
.L282:
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC26
	.word	.LC27
	.word	.LC24
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_GlbReset, .-VDMHAL_V300R001_GlbReset
	.align	2
	.global	VDMHAL_V300R001_ClearIntState
	.type	VDMHAL_V300R001_ClearIntState, %function
VDMHAL_V300R001_ClearIntState:
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
	ldr	r7, .L305
	mov	r5, r0, asl #3
	mov	r6, r0, asl #6
	rsb	r3, r5, r6
	ldr	r2, .L305+4
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1232]
	moveq	r4, r3
	cmp	r0, #1
	bhi	.L301
	cmp	r0, #0
	bgt	.L302
	movw	r8, #1208
	ldr	r9, .L305+8
	mul	r8, r8, r0
	ldr	r3, [r9, r8]
	cmp	r3, #0
	beq	.L303
.L290:
	cmp	r4, #1
	beq	.L304
.L298:
	mvn	r2, #0
	str	r2, [r3, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L302:
	ldr	r1, .L305+12
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r2, .L305+16
	ldr	r4, [r1, #68]
	ldr	r1, .L305+20
	blx	r4
.L284:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L301:
	ldr	r3, .L305+12
	mov	r0, #0
	ldr	r1, .L305+24
.L299:
	ldr	r3, [r3, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L304:
	rsb	r5, r5, r6
	add	r7, r7, r5
	ldr	r2, [r7, #52]
	cmp	r2, #1
	beq	.L298
	cmp	r2, #2
	ldr	r1, [r3, #28]
	mvneq	r2, #11
	streq	r2, [r3, #32]
	beq	.L284
	cmp	r2, #3
	mvneq	r2, #14
	streq	r2, [r3, #32]
	b	.L284
.L303:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r9, r8]
	bne	.L290
.L291:
	ldr	r3, .L305+12
	ldr	r1, .L305+28
	b	.L299
.L306:
	.align	2
.L305:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+176
	.word	.LC5
	.word	.LC28
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_ClearIntState, .-VDMHAL_V300R001_ClearIntState
	.align	2
	.global	VDMHAL_V300R001_MaskInt
	.type	VDMHAL_V300R001_MaskInt, %function
VDMHAL_V300R001_MaskInt:
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
	cmp	r0, #1
	bhi	.L316
	cmp	r0, #0
	bgt	.L317
	movw	r4, #1208
	ldr	r5, .L319
	mul	r4, r4, r0
	ldr	r3, [r5, r4]
	cmp	r3, #0
	beq	.L318
.L312:
	mvn	r2, #0
	str	r2, [r3, #36]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L317:
	ldr	r1, .L319+4
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r2, .L319+8
	ldr	r4, [r1, #68]
	ldr	r1, .L319+12
	blx	r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L316:
	ldr	r3, .L319+4
	mov	r0, #0
	ldr	r1, .L319+16
.L315:
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L318:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r5, r4]
	bne	.L312
.L313:
	ldr	r3, .L319+4
	ldr	r1, .L319+20
	b	.L315
.L320:
	.align	2
.L319:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+208
	.word	.LC5
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_MaskInt, .-VDMHAL_V300R001_MaskInt
	.align	2
	.global	VDMHAL_V300R001_EnableInt
	.type	VDMHAL_V300R001_EnableInt, %function
VDMHAL_V300R001_EnableInt:
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
	ldr	r2, .L339
	mov	r3, r0, asl #6
	ldr	r1, .L339+4
	sub	r3, r3, r0, asl #3
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1232]
	moveq	r4, r3
	cmp	r0, #1
	bhi	.L336
	cmp	r0, #0
	bgt	.L337
	movw	r5, #1208
	ldr	r6, .L339+8
	mul	r5, r5, r0
	ldr	r3, [r6, r5]
	cmp	r3, #0
	beq	.L338
.L327:
	cmp	r4, #1
	mvnne	r2, #1
	strne	r2, [r3, #36]
	beq	.L335
.L321:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L337:
	ldr	r1, .L339+12
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r2, .L339+16
	ldr	r4, [r1, #68]
	ldr	r1, .L339+20
	blx	r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L336:
	ldr	r3, .L339+12
	mov	r0, #0
	ldr	r1, .L339+24
.L334:
	ldr	r3, [r3, #68]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	bx	r3
.L335:
	mvn	r2, #5
	str	r2, [r3, #36]
	b	.L321
.L338:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r6, r5]
	bne	.L327
.L328:
	ldr	r3, .L339+12
	ldr	r1, .L339+28
	b	.L334
.L340:
	.align	2
.L339:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+232
	.word	.LC5
	.word	.LC31
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_EnableInt, .-VDMHAL_V300R001_EnableInt
	.align	2
	.global	VDMHAL_V300R001_CheckReg
	.type	VDMHAL_V300R001_CheckReg, %function
VDMHAL_V300R001_CheckReg:
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
	bgt	.L355
	movw	r4, #1208
	ldr	r6, .L357
	mul	r4, r4, r5
	ldr	r3, [r6, r4]
	cmp	r3, #0
	beq	.L356
.L344:
	sub	r2, r7, #1
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L346
.L348:
	.word	.L352
	.word	.L349
	.word	.L350
	.word	.L353
.L353:
	mov	r3, #40
.L347:
	movw	r1, #1208
	mul	r5, r1, r5
	ldr	r2, [r6, r5]
	ldr	r0, [r2, r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L352:
	mov	r3, #28
	b	.L347
.L350:
	mov	r3, #36
	b	.L347
.L349:
	mov	r3, #32
	b	.L347
.L346:
	ldr	ip, .L357+4
	mov	r3, r7
	ldr	r2, .L357+8
	mov	r0, #0
	ldr	r1, .L357+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L356:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L345
	str	r8, [r6, r4]
	b	.L344
.L355:
	ldr	ip, .L357+4
	mov	r3, r5
	ldr	r2, .L357+8
	mov	r0, #0
	ldr	r1, .L357+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L345:
	ldr	r3, .L357+4
	ldr	r2, .L357+8
	ldr	r1, .L357+20
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L358:
	.align	2
.L357:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+260
	.word	.LC34
	.word	.LC32
	.word	.LC33
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_CheckReg, .-VDMHAL_V300R001_CheckReg
	.align	2
	.global	VDMHAL_V300R001_PrepareDec
	.type	VDMHAL_V300R001_PrepareDec, %function
VDMHAL_V300R001_PrepareDec:
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
	mov	r5, r0
	mov	r4, r2
	beq	.L360
	ldr	r6, .L387
	cmp	r0, #6
	moveq	r1, #1
	movne	r1, #0
	ldr	r0, [r6]
	bl	MEM_WritePhyWord
	cmp	r4, #0
	beq	.L364
	cmp	r4, #1
	bne	.L386
	ldr	r3, .L387+4
	mov	r1, r4
	ldr	r0, [r3]
	add	r0, r0, #8
	bl	MEM_WritePhyWord
.L367:
	ldr	r1, .L387+8
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L387+12
	ldr	r4, [r1, #68]
	ldr	r1, .L387+16
	blx	r4
.L360:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L386:
	cmp	r4, #0
	bgt	.L367
.L366:
	cmp	r5, #17
	ldrls	pc, [pc, r5, asl #2]
	b	.L360
.L369:
	.word	.L379
	.word	.L370
	.word	.L371
	.word	.L372
	.word	.L360
	.word	.L373
	.word	.L374
	.word	.L360
	.word	.L375
	.word	.L376
	.word	.L377
	.word	.L377
	.word	.L377
	.word	.L378
	.word	.L360
	.word	.L360
	.word	.L379
	.word	.L380
.L364:
	ldr	r0, [r6]
	mov	r1, #1
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	b	.L366
.L379:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264HAL_V300R001_StartDec
.L378:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP8HAL_V300R001_StartDec
.L377:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP6HAL_V300R001_StartDec
.L376:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV9HAL_V300R001_StartDec
.L375:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV8HAL_V300R001_StartDec
.L374:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVSHAL_V300R001_StartDec
.L373:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DIVX3HAL_V300R001_StartDec
.L372:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP2HAL_V300R001_StartDec
.L371:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP4HAL_V300R001_StartDec
.L370:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1HAL_V300R001_StartDec
.L380:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCHAL_V300R001_StartDec
.L388:
	.align	2
.L387:
	.word	s_RegPhyBaseAddr
	.word	s_RegPhyBaseAddr_1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+288
	.word	.LC5
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_PrepareDec, .-VDMHAL_V300R001_PrepareDec
	.align	2
	.global	VDMHAL_V300R001_IsVdmReady
	.type	VDMHAL_V300R001_IsVdmReady, %function
VDMHAL_V300R001_IsVdmReady:
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
	movw	r2, #1208
	mul	r2, r2, r0
	ldr	r3, .L396
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L394
	cmp	r0, #0
	ble	.L395
	ldr	r1, .L396+4
	mov	r3, r0
	ldr	r2, .L396+8
	mov	r0, #1
	str	r0, [sp]
	mov	r0, #32
	ldr	r4, [r1, #68]
	ldr	r1, .L396+12
	blx	r4
	mov	r0, #0
.L391:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L395:
	ldr	r0, [r3, #28]
	ubfx	r0, r0, #17, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L394:
	ldr	r1, .L396+4
	mov	r0, r3
	ldr	r2, .L396+8
	ldr	r3, .L396+16
	ldr	r4, [r1, #68]
	ldr	r1, .L396+20
	blx	r4
	mvn	r0, #0
	b	.L391
.L397:
	.align	2
.L396:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+316
	.word	.LC36
	.word	.LC35
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_IsVdmReady, .-VDMHAL_V300R001_IsVdmReady
	.align	2
	.global	VDMHAL_V300R001_IsVdmRun
	.type	VDMHAL_V300R001_IsVdmRun, %function
VDMHAL_V300R001_IsVdmRun:
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
	movw	r2, #1208
	mul	r2, r2, r0
	ldr	r3, .L405
	ldr	r4, [r3, r2]
	cmp	r4, #0
	beq	.L403
	cmp	r0, #0
	ble	.L404
	ldr	r1, .L405+4
	mov	r3, r0
	mov	r4, #1
	ldr	r2, .L405+8
	str	r4, [sp]
	mov	r0, #32
	ldr	r5, [r1, #68]
	ldr	r1, .L405+12
	blx	r5
	mov	r0, r4
.L400:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L404:
	ldr	r0, [r4, #40]
	subs	r0, r0, #1
	movne	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L403:
	ldr	r3, .L405+4
	mov	r0, r4
	ldr	r1, .L405+16
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	b	.L400
.L406:
	.align	2
.L405:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+344
	.word	.LC36
	.word	.LC37
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_IsVdmRun, .-VDMHAL_V300R001_IsVdmRun
	.align	2
	.global	VDMHAL_V300R001_BackupInfo
	.type	VDMHAL_V300R001_BackupInfo, %function
VDMHAL_V300R001_BackupInfo:
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
	subs	r2, r0, #0
	ldreq	r1, .L445
	ldreq	r3, .L445+4
	beq	.L438
	ldr	r3, [r2, #4]
	ldr	r5, [r2]
	cmp	r3, #1
	bhi	.L441
	cmp	r3, #0
	bne	.L412
	ldr	r3, .L445+8
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #60
	beq	.L429
.L415:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	beq	.L429
	cmp	r3, r1
	bne	.L415
	mov	r6, #0
.L413:
	ldr	r8, .L445+12
	ldr	lr, [r8]
	cmp	lr, #0
	beq	.L442
.L416:
	ldr	r7, [lr, #12]
	cmp	r6, #1
	ldr	r4, .L445+16
	str	r7, [r4]
	ldr	r3, [lr, #28]
	str	r3, [r4, #4]
	beq	.L443
	add	r3, lr, #4096
	movw	r2, #4116
	cmp	r6, #0
	ldr	r3, [r3]
	str	r3, [r4, #16]
	ldr	r3, [lr, r2]
	str	r3, [r4, #20]
	ldr	r8, [lr, #208]
	str	r8, [r4, #8]
	ldr	r9, [lr, #212]
	str	r9, [r4, #12]
	bne	.L420
	ldr	r3, [lr, #176]
	str	r3, [r4, #24]
	ldr	r3, [lr, #180]
	str	r3, [r4, #28]
	ldr	r3, [lr, #184]
	str	r3, [r4, #32]
	ldr	r3, [lr, #188]
	str	r3, [r4, #36]
	ldr	r3, [lr, #192]
	str	r3, [r4, #40]
.L420:
	rsb	r1, r4, #32768
	ldr	r3, .L445+20
	add	r1, r1, #208
	add	r1, r1, lr
	add	r0, r3, #128
.L421:
	ldr	r2, [r1, r3]
	ldr	ip, .L445+16
	str	r2, [r3, #4]!
	cmp	r3, r0
	bne	.L421
	cmp	r6, #0
	beq	.L426
.L427:
	and	r7, r7, #15
	cmp	r7, #5
	andeq	r9, r9, #1
	andne	r8, r8, #31
	moveq	r0, #0
	movne	r0, #0
	streq	r9, [r5]
	strne	r8, [r5]
.L433:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L426:
	movw	r2, #33152
	movw	r3, #33156
	ldr	r2, [lr, r2]
	str	r2, [ip, #48]
	ldr	r3, [lr, r3]
	str	r3, [ip, #44]
	b	.L427
.L429:
	mov	r6, r2
	b	.L413
.L443:
	ldr	r0, [r8, #32]
	ubfx	r7, r3, #0, #17
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L444
	sub	r3, r7, #1
	ldr	lr, [r8]
	cmp	r3, #199
	subls	r3, r7, #-1073741823
	ldr	r7, [r4]
	movhi	r3, #0
	movhi	r1, #8
	movls	r3, r3, asl #4
	addls	r1, r3, #8
	ldr	r3, [r2, r3]
	str	r3, [r4, #16]
	ldr	r3, [r2, r1]
	str	r3, [r4, #20]
	ldr	r8, [lr, #208]
	str	r8, [r4, #8]
	ldr	r9, [lr, #212]
	str	r9, [r4, #12]
	b	.L420
.L442:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	lr, r0, #0
	beq	.L417
	str	lr, [r8]
	b	.L416
.L412:
	ldr	r1, .L445
	mov	r0, #0
	ldr	r2, .L445+24
	str	r0, [sp]
	ldr	r4, [r1, #68]
	ldr	r1, .L445+28
	blx	r4
	mvn	r0, #0
	b	.L433
.L441:
	ldr	r3, .L445
	mov	r0, #0
	ldr	r1, .L445+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L433
.L444:
	ldr	r1, .L445
	ldr	r3, .L445+36
.L438:
	ldr	r4, [r1, #68]
	ldr	r2, .L445+24
	ldr	r1, .L445+40
	blx	r4
	mvn	r0, #0
	b	.L433
.L417:
	ldr	r3, .L445
	ldr	r1, .L445+44
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L433
.L446:
	.align	2
.L445:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC38
	.word	g_DSPState
	.word	g_HwMem
	.word	g_BackUp
	.word	g_BackUp+48
	.word	.LANCHOR0+372
	.word	.LC5
	.word	.LC39
	.word	.LC40
	.word	.LC1
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_BackupInfo, .-VDMHAL_V300R001_BackupInfo
	.align	2
	.global	VDMHAL_V300R001_ReadMsgSlot
	.type	VDMHAL_V300R001_ReadMsgSlot, %function
VDMHAL_V300R001_ReadMsgSlot:
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
	beq	.L451
	cmp	r2, #800
	ldr	r3, .L453
	bhi	.L452
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L452:
	mov	r0, r4
	ldr	r1, .L453+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L451:
	ldr	ip, .L453
	mov	r2, r0
	ldr	r1, .L453+8
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L454:
	.align	2
.L453:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC42
	.word	.LC41
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_ReadMsgSlot, .-VDMHAL_V300R001_ReadMsgSlot
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	VDMHAL_V300R001_CfgRpMsg
	.type	VDMHAL_V300R001_CfgRpMsg, %function
VDMHAL_V300R001_CfgRpMsg:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	str	r0, [fp, #-56]
	ldr	r0, [r1, #40]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-72]
	beq	.L489
	ldr	r3, [fp, #-56]
	ldr	r2, [r3, #840]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L490
	ldr	r3, [fp, #-56]
	ldr	r1, [r3, #24]
	ldr	r0, [r3, #864]
	ldr	ip, [r3]
	mov	r1, r1, asl r0
	ldr	r2, [r3, #28]
	add	r3, r1, #255
	cmp	ip, #17
	bic	lr, r3, #255
	mov	r3, r2, asl r0
	mov	r0, lr, asl #4
	beq	.L459
	adds	r2, r3, #31
	addmi	r2, r3, #62
	adds	ip, r1, #127
	addmi	r1, r1, #254
	movpl	r1, ip
	mov	ip, r2, asr #5
	mov	r1, r1, asr #7
	adds	r2, r1, #15
	addmi	r2, r1, #30
	mul	r3, lr, ip
	mov	r2, r2, asr #4
	mov	r2, r2, asl #9
	mul	r2, r2, ip
	add	r3, r2, r3, lsl #5
.L460:
	ldr	r4, [fp, #-56]
	mov	lr, #0	@ movhi
	ldr	r5, [fp, #-72]
	mov	ip, lr	@ movhi
	ldr	r1, [r4, #16]
	str	r1, [r5]
	ldr	r1, [r4, #16]
	add	r1, r3, r1
	str	r1, [r5, #4]
	ldr	r1, [r4, #4]
	str	r1, [r5, #8]
	ldr	r1, [r4, #4]
	add	r3, r3, r1
	str	r3, [r5, #12]
	str	r0, [r5, #16]
	str	r2, [r5, #20]
	ldr	r2, [r4, #24]
	ldr	r3, [r4, #28]
	sub	r2, r2, #1
	sub	r3, r3, #1
	bfi	lr, r2, #0, #9
	bfi	ip, r3, #0, #9
	strh	lr, [fp, #-48]	@ movhi
	strh	ip, [fp, #-46]	@ movhi
	ldr	r3, [fp, #-48]
	str	r3, [r5, #24]
	ldr	r3, [r4, #852]
	ldr	r2, [r4, #24]
	sub	r3, r3, #1
	cmp	r3, #1
	str	r2, [fp, #-60]
	movls	r3, r4
	ldrhi	r3, [fp, #-56]
	ldrls	r3, [r3, #28]
	ldrhi	r3, [r3, #28]
	addls	r3, r3, r3, lsr #31
	movls	r3, r3, asr #1
	str	r3, [fp, #-88]
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #864]
	cmp	r3, #6
	moveq	r4, #2
	beq	.L463
	cmp	r3, #5
	moveq	r4, #4
	beq	.L463
	cmp	r3, #4
	moveq	r4, #8
	beq	.L463
	ldr	r3, .L494
	mov	r0, #1
	ldr	r1, .L494+4
	mov	r4, r0
	ldr	r3, [r3, #68]
	blx	r3
.L463:
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #856]
	cmp	r3, #0
	bne	.L481
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #840]
	subs	r9, r2, #0
	ble	.L482
	ldr	r2, [fp, #-60]
	mov	r7, r3
	ldr	r1, [fp, #-88]
	sub	r8, r4, #1
	str	r3, [fp, #-64]
	str	r3, [fp, #-76]
	mul	r2, r2, r1
	sub	r3, r2, #1
	str	r3, [fp, #-84]
	str	r2, [fp, #-80]
	b	.L476
.L467:
	add	r7, r7, #1
	cmp	r9, r7
	ble	.L491
.L476:
	ldr	r3, [fp, #-56]
	mov	r1, r4
	add	r5, r3, r7, lsl #2
	ldrsh	r6, [r5, #42]
	ldrh	r3, [r5, #40]
	sub	r0, r6, #1
	add	r0, r0, r4
	str	r3, [fp, #-68]
	bl	__aeabi_uidiv
	cmp	r7, #0
	mul	r10, r4, r0
	ble	.L466
	ldrsh	r0, [r5, #38]
	mov	r1, r4
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r3, r4, r0
	cmp	r10, r3
	str	r3, [fp, #-76]
	bgt	.L468
	add	r7, r7, #1
	cmp	r9, r7
	bgt	.L476
.L491:
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #856]
	cmp	r3, #1
	bne	.L465
.L475:
	ldr	r3, [fp, #-60]
	mov	r0, #0	@ movhi
	sub	r2, r3, #1
	ldr	r3, [fp, #-88]
	sub	r1, r3, #1
	mov	r3, #0
	bfi	r0, r3, #0, #9
	strh	r0, [fp, #-48]	@ movhi
	mov	r0, #0	@ movhi
	bfi	r0, r3, #0, #9
	strh	r0, [fp, #-46]	@ movhi
	mov	r0, #0	@ movhi
	ldr	ip, [fp, #-48]
	bfi	r0, r2, #0, #9
	strh	r0, [fp, #-48]	@ movhi
	mov	r2, #0	@ movhi
	ldr	r0, [fp, #-56]
	bfi	r2, r1, #0, #9
	strh	r2, [fp, #-46]	@ movhi
	mov	r1, #1
	ldr	r2, [fp, #-48]
	str	r1, [r0, #840]
	ldr	r1, [fp, #-72]
	str	ip, [r1, #32]
	str	r2, [r1, #36]
	b	.L477
.L481:
	cmp	r3, #1
	mov	r2, #0
	str	r2, [fp, #-64]
	beq	.L475
.L465:
	ldr	r3, [fp, #-64]
	sub	r3, r3, #1
	uxth	r3, r3
.L477:
	ldr	lr, [fp, #-56]
	mov	r0, #0
	ldrb	r2, [fp, #-46]	@ zero_extendqisi2
	strh	r3, [fp, #-48]	@ movhi
	ldr	ip, [lr, #848]
	ldr	r1, [lr, #852]
	bfi	r2, ip, #0, #1
	ldr	ip, [lr, #864]
	and	r1, r1, #3
	ldrb	lr, [fp, #-45]	@ zero_extendqisi2
	bfi	r2, r1, #4, #2
	sub	ip, ip, #4
	bfi	lr, ip, #0, #2
	strb	lr, [fp, #-45]
	mov	r3, r2
	bfi	r3, r1, #6, #2
	strb	r3, [fp, #-46]
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-72]
	str	r3, [r2, #28]
.L487:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L469:
	bl	__aeabi_uidiv
	mov	r1, r4
	mul	r6, r4, r0
	ldrsh	r0, [r5, #44]
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r6, r0
	add	r3, r0, #1
	bhi	.L471
	cmp	r6, r3
	mov	r1, r4
	beq	.L471
	ldrsh	r0, [r5, #38]
	add	r0, r0, r8
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r6, r0
	bhi	.L492
.L471:
	ldrh	r6, [r5, #46]
	add	r5, r5, #4
	mov	r7, r10
	sxth	r6, r6
.L468:
	add	r10, r7, #1
	mov	r1, r4
	cmp	r10, r9
	add	r0, r8, r6
	blt	.L469
	bl	__aeabi_uidiv
	mul	r10, r4, r0
.L470:
	ldrsh	r0, [fp, #-68]
	mov	r1, r4
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-80]
	ldr	r3, [fp, #-84]
	cmp	r2, r10
	movls	r10, r3
	ldr	r3, [fp, #-64]
	add	r3, r3, #1
	str	r3, [fp, #-64]
	mul	r5, r4, r0
	cmp	r10, r5
	movlt	r5, #0
	cmp	r3, #252
	bgt	.L493
	mov	r0, r5
	ldr	r1, [fp, #-60]
	bl	__aeabi_uidivmod
	mov	r3, #0	@ movhi
	mov	r2, #0
	mov	r0, r5
	mov	r5, r3	@ movhi
	mov	r9, r2, lsr #16
	mov	r6, r9
	bfi	r3, r1, #0, #9
	ldr	r1, [fp, #-60]
	strh	r3, [fp, #-48]	@ movhi
	bl	__aeabi_uidiv
	mov	r2, r9	@ movhi
	ldr	r3, [fp, #-64]
	ldr	ip, [fp, #-72]
	add	r3, r3, #3
	ldr	r1, [fp, #-60]
	mov	r9, r3, asl #3
	add	r9, r9, #4
	bfi	r2, r0, #0, #9
	strh	r2, [fp, #-46]	@ movhi
	ldr	r2, [fp, #-48]
	mov	r0, r10
	str	r2, [ip, r3, asl #3]
	bl	__aeabi_uidivmod
	mov	r0, r10
	bfi	r5, r1, #0, #9
	ldr	r1, [fp, #-60]
	strh	r5, [fp, #-48]	@ movhi
	bl	__aeabi_uidiv
	ldr	ip, [fp, #-72]
	bfi	r6, r0, #0, #9
	strh	r6, [fp, #-46]	@ movhi
	ldr	r3, [fp, #-48]
	str	r3, [ip, r9]
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #840]
	mov	r9, r3
	b	.L467
.L466:
	ldr	r2, [fp, #-76]
	cmp	r10, r2
	movgt	r2, #0
	movle	r2, #1
	cmp	r7, #0
	moveq	r2, #0
	cmp	r2, #0
	bne	.L467
	b	.L470
.L492:
	mov	r10, r6
	b	.L470
.L459:
	mul	r3, r3, lr
	mov	r2, #0
	b	.L460
.L493:
	ldr	r2, [fp, #-56]
	mov	r3, #1
	str	r3, [r2, #856]
	b	.L475
.L482:
	str	r3, [fp, #-64]
	b	.L465
.L490:
	ldr	r3, .L494
	mov	r0, #0
	ldr	r1, .L494+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L487
.L489:
	ldr	r1, .L494
	ldr	r3, .L494+12
	ldr	r2, .L494+16
	ldr	r4, [r1, #68]
	ldr	r1, .L494+20
	blx	r4
	mvn	r0, #0
	b	.L487
.L495:
	.align	2
.L494:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC45
	.word	.LC44
	.word	.LC43
	.word	.LANCHOR0+400
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_CfgRpMsg, .-VDMHAL_V300R001_CfgRpMsg
	.align	2
	.global	VDMHAL_V300R001_CfgRpReg
	.type	VDMHAL_V300R001_CfgRpReg, %function
VDMHAL_V300R001_CfgRpReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r3, #1
	mov	r4, r3
	bhi	.L505
	cmp	r3, #0
	bgt	.L506
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L507
.L501:
	movw	r3, #1208
	ldr	r2, .L508
	mul	r3, r3, r4
	ldr	ip, [r1, #40]
	mov	r4, #7
	movw	lr, #49667
	bic	ip, ip, #15
	movt	lr, 8192
	movw	r1, #3075
	mov	r0, #0
	movt	r1, 48
	ldr	r5, [r2, r3]
	str	ip, [r5, #16]
	ldr	ip, [r2, r3]
	str	r4, [ip, #36]
	ldr	ip, [r2, r3]
	str	lr, [ip, #12]
	ldr	ip, [r2, r3]
	str	r1, [ip, #60]
	ldr	ip, [r2, r3]
	str	r1, [ip, #64]
	ldr	ip, [r2, r3]
	str	r1, [ip, #68]
	ldr	ip, [r2, r3]
	str	r1, [ip, #72]
	ldr	ip, [r2, r3]
	str	r1, [ip, #76]
	ldr	ip, [r2, r3]
	str	r1, [ip, #80]
	ldr	r3, [r2, r3]
	str	r1, [r3, #84]
.L504:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L507:
	mov	r0, #0
	str	r1, [fp, #-24]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L502
	ldr	r1, [fp, #-24]
	str	r3, [r1]
	b	.L501
.L506:
	ldr	r1, .L508+4
	mov	r2, #0
	mov	r0, r2
	str	r2, [sp]
	ldr	r2, .L508+8
	ldr	r4, [r1, #68]
	ldr	r1, .L508+12
	blx	r4
	mvn	r0, #0
	b	.L504
.L505:
	ldr	r3, .L508+4
	mov	r0, #0
	ldr	r1, .L508+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L504
.L502:
	ldr	r3, .L508+4
	ldr	r1, .L508+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L504
.L509:
	.align	2
.L508:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+428
	.word	.LC5
	.word	.LC46
	.word	.LC29
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_CfgRpReg, .-VDMHAL_V300R001_CfgRpReg
	.align	2
	.global	VDMHAL_V300R001_MakeDecReport
	.type	VDMHAL_V300R001_MakeDecReport, %function
VDMHAL_V300R001_MakeDecReport:
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
	ldreq	r1, .L543
	ldreq	r3, .L543+4
	beq	.L535
	ldr	r5, [r3, #4]
	ldr	r8, [r3]
	cmp	r5, #0
	ldr	r6, [r3, #8]
	beq	.L537
	movw	r3, #1208
	ldr	r4, .L543+8
	mul	r3, r3, r6
	ldr	r0, [r4, r3]
	cmp	r0, #0
	beq	.L514
	ldr	r3, .L543+12
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #60
	beq	.L529
.L517:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	beq	.L529
	cmp	r3, r1
	bne	.L517
	mov	r9, #0
.L515:
	ldr	r7, .L543
	mov	r2, #816
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r7, #48]
	blx	r3
	movw	r2, #1208
	mla	r2, r2, r6, r4
	ldr	r1, .L543+16
	mov	r3, #180
	mla	r3, r3, r6, r1
	ldr	r2, [r2, #24]
	str	r2, [r5, #4]
	ldr	r3, [r3, #4]
	mov	r3, r3, lsr #17
	and	r2, r3, #3
	cmp	r2, #1
	moveq	r3, #0
	beq	.L518
	eor	r3, r3, #1
	and	r3, r3, #1
	cmp	r8, #3
	orrne	r3, r3, #1
.L518:
	mov	r2, #180
	str	r3, [r5]
	mla	r3, r2, r6, r1
	bics	r8, r8, #16
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #0, #17
	str	r2, [r5, #8]
	beq	.L538
.L519:
	cmp	r2, #200
	bhi	.L539
.L521:
	movw	r3, #1208
	mla	r4, r3, r6, r4
	ldr	r9, [r4, #32]
	mov	r0, r9
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L540
	ldr	r8, .L543+20
	mov	r0, #3200
	ldr	r2, [r5, #8]
	mla	r4, r0, r6, r8
	mov	r2, r2, asl #2
	mov	r0, r4
	bl	VDMHAL_V300R001_ReadMsgSlot
	ldr	ip, [r5, #8]
	cmp	ip, #0
	movne	r0, r4
	movne	r3, r5
	movne	r2, #0
	beq	.L526
.L525:
	ldr	r1, [r0, #4]
	add	r2, r2, #1
	cmp	r2, ip
	add	r0, r0, #16
	add	r3, r3, #4
	strh	r1, [r3, #8]	@ movhi
	ldr	r1, [r0, #-8]
	strh	r1, [r3, #10]	@ movhi
	bne	.L525
.L526:
	mov	r0, #6
	bl	IsDprintTypeEnable
	cmp	r0, #0
	bne	.L541
.L512:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L538:
	cmp	r9, #1
	beq	.L542
	ldr	r1, .L543+24
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L519
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L519
	mov	r3, #1
	strh	r1, [r5, #12]	@ movhi
	mov	r0, r1
	strh	r1, [r5, #14]	@ movhi
	str	r3, [r5, #8]
	b	.L512
.L529:
	mov	r9, r2
	b	.L515
.L541:
	ldr	r3, [r7, #68]
	mov	r0, #6
	ldr	r2, [r5, #8]
	mov	r4, #0
	ldr	r1, .L543+28
	blx	r3
	ldr	r3, [r7, #68]
	mov	r2, r9
	mov	r0, #6
	ldr	r1, .L543+32
	blx	r3
	mov	r3, #3200
	mla	r6, r3, r6, r8
.L527:
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
	ldr	r8, [r7, #68]
	ldr	r1, .L543+36
	blx	r8
	ldr	r3, [r5, #8]
	ldr	r2, .L543
	mov	r3, r3, asl #2
	sub	r3, r3, #3
	cmp	r3, r4
	bhi	.L527
	ldr	r3, [r2, #68]
	mov	r0, #6
	ldr	r1, .L543+40
	blx	r3
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L539:
	mov	r3, #200
	ldr	r8, [r7, #68]
	ldr	r1, .L543+44
	mov	r0, #1
	blx	r8
	mov	r3, #0
	str	r3, [r5, #8]
	b	.L521
.L542:
	ldr	r3, [r3, #16]
	ubfx	r3, r3, #21, #2
	cmp	r3, #2
	bne	.L519
	str	r9, [r5, #8]
	mov	r0, r8
	strh	r8, [r5, #12]	@ movhi
	strh	r8, [r5, #14]	@ movhi
	b	.L512
.L537:
	ldr	r1, .L543
	mov	r0, r5
	ldr	r3, .L543+48
.L535:
	ldr	r4, [r1, #68]
	ldr	r2, .L543+52
	ldr	r1, .L543+56
	blx	r4
	mvn	r0, #0
	b	.L512
.L540:
	ldr	r4, [r7, #68]
	ldr	r3, .L543+60
	ldr	r2, .L543+52
	ldr	r1, .L543+56
	blx	r4
	mvn	r0, #0
	b	.L512
.L514:
	ldr	r1, .L543
	ldr	r3, .L543+64
	b	.L535
.L544:
	.align	2
.L543:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	g_HwMem
	.word	g_DSPState
	.word	g_BackUp
	.word	g_UpMsg
	.word	g_not_allow_H264FullPictureRepair_flag
	.word	.LC50
	.word	.LC51
	.word	.LC52
	.word	.LC53
	.word	.LC49
	.word	.LC48
	.word	.LANCHOR0+456
	.word	.LC1
	.word	.LC40
	.word	.LC35
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_MakeDecReport, .-VDMHAL_V300R001_MakeDecReport
	.align	2
	.global	VDMHAL_V300R001_PrepareRepair
	.type	VDMHAL_V300R001_PrepareRepair, %function
VDMHAL_V300R001_PrepareRepair:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	cmp	r3, #1
	mov	r4, r3
	mov	r7, r0
	mov	r8, r1
	bhi	.L561
	cmp	r3, #0
	bgt	.L562
	movw	r5, #1208
	ldr	r6, .L565
	mul	r5, r5, r3
	add	r9, r5, r6
	ldr	r3, [r5, r6]
	cmp	r3, #0
	beq	.L563
.L550:
	cmp	r2, #0
	bne	.L552
	ldr	r5, .L565+4
	mov	r3, #1744
	mla	r3, r3, r4, r5
	ldr	r1, [r3, #840]
	cmp	r1, #0
	ble	.L553
	cmp	r7, #6
	bne	.L554
	ldr	r1, [r8, #32]
	cmp	r1, #1
	moveq	r2, r1
	str	r2, [r3, #1724]
.L554:
	mov	r2, r8
	mov	r3, r4
	mov	r1, r9
	mov	r0, r7
	bl	VDMHAL_V300R001_CfgRpReg
	mov	r0, #1744
	mov	r1, r9
	mov	r2, r4
	mla	r0, r0, r4, r5
	bl	VDMHAL_V300R001_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L552:
	cmp	r2, #1
	movne	r0, #0
	beq	.L564
.L548:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L564:
	cmp	r7, #6
	bne	.L556
	ldr	r3, [r8, #32]
	cmp	r3, #1
	bne	.L556
	ldr	r5, .L565+4
	mov	r3, #1744
	mla	r3, r3, r4, r5
	ldr	r2, [r3, #1712]
	cmp	r2, #0
	ble	.L556
	ldr	r2, .L565+8
	mov	r1, #2
	str	r1, [r3, #1724]
	ldr	r3, [r2, #56]
	cmp	r3, #0
	beq	.L557
	mov	r0, r4
	blx	r3
.L558:
	mov	r2, r8
	mov	r3, r4
	mov	r1, r9
	mov	r0, #6
	bl	VDMHAL_V300R001_CfgRpReg
	mov	r0, #1744
	mla	r0, r0, r4, r5
	mov	r1, r9
	mov	r2, r4
	add	r0, r0, #872
	bl	VDMHAL_V300R001_CfgRpMsg
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L563:
	mov	r0, #0
	str	r2, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L551
	str	r3, [r5, r6]
	ldr	r2, [fp, #-40]
	b	.L550
.L562:
	ldr	r1, .L565+12
	mov	r2, #0
	mov	r0, r2
	str	r2, [sp]
	ldr	r2, .L565+16
	ldr	r4, [r1, #68]
	ldr	r1, .L565+20
	blx	r4
	mvn	r0, #0
	b	.L548
.L556:
	ldr	r3, .L565+12
	mov	r0, #0
	ldr	r1, .L565+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L548
.L557:
	ldr	ip, .L565+12
	mov	r0, r3
	movw	r2, #2823
	ldr	r1, .L565+28
	ldr	r3, [ip, #68]
	blx	r3
	b	.L558
.L561:
	ldr	r3, .L565+12
	mov	r0, #0
	ldr	r1, .L565+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L548
.L553:
	ldr	r3, .L565+12
	mov	r0, r2
	ldr	r1, .L565+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L548
.L551:
	ldr	r3, .L565+12
	ldr	r1, .L565+40
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L548
.L566:
	.align	2
.L565:
	.word	g_HwMem
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+488
	.word	.LC5
	.word	.LC57
	.word	.LC10
	.word	.LC54
	.word	.LC56
	.word	.LC55
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_PrepareRepair, .-VDMHAL_V300R001_PrepareRepair
	.align	2
	.global	VDMHAL_V300R001_StartHwRepair
	.type	VDMHAL_V300R001_StartHwRepair, %function
VDMHAL_V300R001_StartHwRepair:
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
	subs	r4, r0, #0
	ble	.L570
	ldr	r5, .L571
	mov	r6, #1
	mov	r3, r4
	ldr	r2, .L571+4
	str	r6, [sp]
	mov	r0, #32
	ldr	r7, [r5, #68]
	ldr	r1, .L571+8
	blx	r7
	movw	r0, #49156
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r3, .L571+12
	ldr	r3, [r3]
	uxth	r1, r0
	add	r0, r3, #4
	bl	MEM_WritePhyWord
	str	r6, [sp]
	mov	r3, r4
	ldr	r7, [r5, #68]
	ldr	r2, .L571+4
	mov	r0, #32
	ldr	r1, .L571+16
	blx	r7
	ldr	r3, [r5, #116]
	blx	r3
	str	r6, [sp]
	mov	r3, r4
	ldr	r7, [r5, #68]
	ldr	r2, .L571+4
	mov	r0, #32
	ldr	r1, .L571+16
	blx	r7
	str	r6, [sp]
	mov	r3, r4
	ldr	r7, [r5, #68]
	ldr	r2, .L571+4
	mov	r0, #32
	ldr	r1, .L571+16
	blx	r7
	str	r6, [sp]
	mov	r3, r4
	ldr	r5, [r5, #68]
	ldr	r2, .L571+4
	mov	r0, #32
	ldr	r1, .L571+16
	blx	r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L570:
	movw	r3, #1208
	ldr	r5, .L571+20
	mul	r4, r3, r4
	movw	r0, #49156
	movt	r0, 63683
	ldr	r3, [r5, r4]
	ldr	r6, [r3, #8]
	bl	MEM_ReadPhyWord
	ldr	r3, .L571+12
	orr	r6, r6, #67108864
	ldr	r3, [r3]
	uxth	r1, r0
	add	r0, r3, #4
	bl	MEM_WritePhyWord
	ldr	r2, [r5, r4]
	ldr	r3, .L571
	str	r6, [r2, #8]
	ldr	r3, [r3, #116]
	blx	r3
	ldr	r2, [r5, r4]
	mov	r3, #0
	mov	r1, #1
	str	r3, [r2]
	ldr	r2, [r5, r4]
	str	r1, [r2]
	ldr	r2, [r5, r4]
	str	r3, [r2]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L572:
	.align	2
.L571:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+520
	.word	.LC36
	.word	s_RegPhyBaseAddr
	.word	.LC58
	.word	g_HwMem
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_StartHwRepair, .-VDMHAL_V300R001_StartHwRepair
	.align	2
	.global	VDMHAL_V300R001_SetVdhClkSkip
	.type	VDMHAL_V300R001_SetVdhClkSkip, %function
VDMHAL_V300R001_SetVdhClkSkip:
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
	ldr	r9, .L602
	ldr	r4, [r9, #64]
	cmp	r4, #0
	blt	.L596
	movw	r10, #56367
	add	r6, r9, #64
	add	r9, r9, #124
	movt	r10, 1315
	mov	r8, #30
	mov	r7, #0
.L575:
	mov	r0, r4
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L578
	ldr	r3, .L602+4
	mov	r0, r4
	ldr	r2, .L602+8
	ldr	r3, [r3, r4, asl #2]
	ldr	ip, [r2, r4, asl #2]
	ldr	r1, [r3, #44]
	ldr	r2, [r3, #48]
	adds	r4, r1, #15
	ldr	r3, [ip, #1464]
	addmi	r4, r1, #30
	adds	r5, r2, #15
	addmi	r5, r2, #30
	cmp	r3, #30
	mov	r4, r4, asr #4
	movgt	r8, r3
	mov	r5, r5, asr #4
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L578
.L581:
	.word	.L590
	.word	.L590
	.word	.L590
	.word	.L590
	.word	.L578
	.word	.L590
	.word	.L590
	.word	.L578
	.word	.L590
	.word	.L590
	.word	.L590
	.word	.L590
	.word	.L590
	.word	.L590
	.word	.L578
	.word	.L578
	.word	.L591
	.word	.L590
.L590:
	mul	r4, r5, r4
	mul	r2, r8, r4
	ubfx	r2, r2, #1, #26
	umull	r2, r3, r2, r10
	add	r7, r7, r3, lsr #7
.L578:
	cmp	r6, r9
	beq	.L594
	ldr	r4, [r6, #4]!
	cmp	r4, #0
	bge	.L575
.L594:
	rsb	r7, r7, #32
	cmp	r7, #25
	movge	r7, #25
	cmp	r7, #0
	andgt	r7, r7, #31
	ble	.L601
.L574:
	ldr	r3, .L602+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfi	r3, r7, #12, #5
.L599:
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L591:
	mul	r4, r5, r4
	mul	r2, r8, r4
	bic	r2, r2, #-67108864
	umull	r2, r3, r2, r10
	add	r7, r7, r3, lsr #7
	b	.L578
.L601:
	ldr	r3, .L602+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	b	.L599
.L596:
	mov	r7, #25
	b	.L574
.L603:
	.align	2
.L602:
	.word	g_ChanCtx
	.word	s_pFspInst
	.word	s_pstVfmwChan
	.word	g_pstRegCrg
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_SetVdhClkSkip, .-VDMHAL_V300R001_SetVdhClkSkip
	.align	2
	.global	VDMHAL_V300R001_StartHwDecode
	.type	VDMHAL_V300R001_StartHwDecode, %function
VDMHAL_V300R001_StartHwDecode:
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
	bgt	.L625
	mov	r7, r4, asl #3
	mov	r6, r4, asl #6
	ldr	r5, .L627
	rsb	r3, r7, r6
	ldr	r8, .L627+4
	add	r3, r5, r3
	ldr	r10, .L627+8
	ldr	r2, [r3, #12]
	ldr	r1, [r8]
	cmp	r2, #0
	ldr	r2, [r3, #8]
	ldr	r3, [r1, #120]
	beq	.L626
.L607:
	bfc	r3, #8, #2
.L608:
	ldr	r9, .L627+12
	mov	r0, #30
	str	r3, [r1, #120]
	ldr	r3, [r9, #120]
	blx	r3
	rsb	r3, r7, r6
	add	r3, r5, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r10, r3, asl #2]
	ldr	r2, [r3, #1232]
	cmp	r2, #1
	beq	.L609
	ldr	r3, [r3, #1220]
	bics	r3, r3, #1024
	beq	.L610
.L609:
	ldr	r2, [r8]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
.L611:
	cmp	r4, #0
	beq	.L613
	cmp	r4, #1
	beq	.L614
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L627+16
	blx	r3
.L615:
	ldr	r3, [r9, #116]
	blx	r3
	movw	r3, #1208
	mul	r3, r3, r4
	ldr	r2, .L627+20
	mov	r1, #0
	ldr	r3, [r2, r3]
	str	r1, [r3]
.L616:
	movw	r3, #1208
	rsb	r6, r7, r6
	mul	r4, r3, r4
	mov	lr, #1
	add	r5, r5, r6
	mov	r0, #0
	ldr	r3, .L627+24
	mov	r1, #4
	ldr	ip, [r2, r4]
	str	lr, [ip]
	ldr	r2, [r2, r4]
	str	r0, [r2]
	ldr	r0, [r5, #8]
	ldr	r2, [r3, r0, asl #2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDEC_Lowdelay_Event_Time
.L626:
	ldr	r2, [r10, r2, asl #2]
	movw	r0, #8160
	add	r2, r2, #204800
	ldr	r9, [r2, #1516]
	ldr	lr, [r2, #1520]
	adds	ip, r9, #15
	addmi	ip, r9, #30
	adds	r2, lr, #15
	addmi	r2, lr, #30
	mov	ip, ip, asr #4
	mov	r2, r2, asr #4
	mul	r2, r2, ip
	cmp	r2, r0
	orrgt	r3, r3, #768
	bgt	.L608
	b	.L607
.L625:
	ldr	r1, .L627+12
	mov	r3, r4
	mov	r0, #0
	ldr	r2, .L627+28
	str	r0, [sp]
	ldr	r4, [r1, #68]
	ldr	r1, .L627+32
	blx	r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L614:
	ldr	r3, .L627+36
	mov	r1, #3
	ldr	r0, [r3]
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r3, [r9, #116]
	blx	r3
	str	r4, [sp]
	ldr	r2, .L627+28
	mov	r3, r4
	ldr	r8, [r9, #68]
	mov	r0, #32
	ldr	r1, .L627+40
	blx	r8
	ldr	r2, .L627+20
	b	.L616
.L613:
	ldr	r3, .L627+44
	mov	r1, #3
	ldr	r0, [r3]
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	b	.L615
.L610:
	mov	r0, r4
	bl	VDMHAL_V300R001_SetVdhClkSkip
	b	.L611
.L628:
	.align	2
.L627:
	.word	g_VdmDrvParam
	.word	g_pstRegCrg
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	.word	g_HwMem
	.word	g_LowDelaySeqIndex
	.word	.LANCHOR0+552
	.word	.LC5
	.word	s_RegPhyBaseAddr_1
	.word	.LC58
	.word	s_RegPhyBaseAddr
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_StartHwDecode, .-VDMHAL_V300R001_StartHwDecode
	.align	2
	.global	VDMHAL_V300R001_GetCharacter
	.type	VDMHAL_V300R001_GetCharacter, %function
VDMHAL_V300R001_GetCharacter:
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
	ldr	r1, .L630
	mov	r0, #15
	ldr	r3, .L630+4
	mov	r2, #4
	str	r0, [r1]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L631:
	.align	2
.L630:
	.word	g_VdmCharacter
	.word	g_eVdmVersion
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_GetCharacter, .-VDMHAL_V300R001_GetCharacter
	.align	2
	.global	VDMHAL_V300R001_WriteBigTitle1DYuv
	.type	VDMHAL_V300R001_WriteBigTitle1DYuv, %function
VDMHAL_V300R001_WriteBigTitle1DYuv:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #84)
	sub	sp, sp, #84
	mov	r6, r3
	ubfx	r3, r3, #29, #2
	mov	r4, #0
	cmp	r3, #1
	str	r0, [fp, #-92]
	mov	r8, r1
	mov	r7, r2
	str	r4, [fp, #-76]
	str	r4, [fp, #-72]
	str	r4, [fp, #-68]
	str	r4, [fp, #-64]
	str	r4, [fp, #-60]
	str	r4, [fp, #-56]
	str	r4, [fp, #-52]
	str	r4, [fp, #-48]
	beq	.L633
	cmp	r3, #2
	moveq	r4, #1
	movne	r4, #2
.L633:
	ldr	r3, [fp, #-92]
	cmp	r3, #0
	beq	.L632
	mov	r3, #0
	mov	r2, #4194304
	mov	r1, r3
	str	r3, [sp]
	ldr	r0, .L726
	sub	r3, fp, #76
	bl	MEM_AllocMemBlock
	subs	r1, r0, #0
	beq	.L722
.L719:
	ldr	r3, .L726+4
	mov	r0, #1
	ldr	r1, .L726+8
	ldr	r3, [r3, #68]
	blx	r3
.L632:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L722:
	str	r1, [sp]
	mov	r2, #4194304
	sub	r3, fp, #60
	ldr	r0, .L726+12
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L719
	add	r3, r6, #15
	add	r5, r7, #15
	bic	r3, r3, #15
	str	r3, [fp, #-84]
	bic	r5, r5, #15
	mov	ip, r6, lsr #1
	mov	r1, r3
	adds	r3, r3, #31
	addmi	r3, r1, #62
	add	r2, r5, #255
	bic	r2, r2, #255
	ldr	r1, [fp, #-56]
	mov	r3, r3, asr #5
	cmp	r4, #0
	cmpne	r4, #3
	str	ip, [fp, #-100]
	mov	ip, r7, lsr #1
	mla	r3, r3, r2, r8
	str	ip, [fp, #-104]
	str	r1, [fp, #-96]
	mov	ip, r2, asl #4
	ldr	r6, [fp, #-72]
	str	ip, [fp, #-88]
	str	r3, [fp, #-112]
	add	r3, r1, #2097152
	str	r3, [fp, #-108]
	bne	.L638
	ldr	r3, [fp, #-84]
	cmp	r3, #0
	movne	r10, r0
	ldrne	r7, .L726+4
	strne	r10, [fp, #-80]
	beq	.L723
.L639:
	cmp	r5, #0
	beq	.L643
	ldr	r2, [fp, #-80]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	ldr	r2, [fp, #-88]
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L641:
	mov	r1, r4, lsr #8
	add	r0, r10, r4
	add	r0, r6, r0
	add	r4, r4, #256
	add	r1, r9, r1, lsl #12
	ldr	r3, [r7, #52]
	add	r1, r8, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L641
.L643:
	ldr	r3, [fp, #-80]
	add	r10, r10, r5
	ldr	r2, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-80]
	cmp	r2, r3
	bne	.L639
	ldr	r4, [fp, #-84]
	mov	r0, r6
	ldr	r3, [r7, #44]
	ldr	r2, [fp, #-92]
	mul	r1, r4, r5
	blx	r3
	movs	r3, r4, lsr #1
	str	r3, [fp, #-84]
	beq	.L675
	ldr	r3, [fp, #-88]
	mov	r9, #0
	ldr	r10, [fp, #-112]
	str	r9, [fp, #-80]
	mov	r3, r3, asr #1
	str	r3, [fp, #-88]
.L645:
	cmp	r5, #0
	beq	.L647
	ldr	r2, [fp, #-80]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-88]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L646:
	mov	r1, r4, lsr #8
	add	r0, r9, r4
	add	r0, r6, r0
	add	r4, r4, #256
	add	r1, r8, r1, lsl #11
	ldr	r3, [r7, #52]
	add	r1, r10, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L646
.L647:
	ldr	r3, [fp, #-80]
	add	r9, r9, r5
	ldr	r2, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-80]
	cmp	r3, r2
	bne	.L645
.L675:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L724
	ldr	r3, [fp, #4]
	cmp	r3, #0
	beq	.L672
.L667:
	ldr	r3, [fp, #-100]
	ldr	r2, [fp, #-104]
	ldr	r4, [fp, #-92]
	ldr	r0, [fp, #-96]
	mul	r6, r3, r2
	ldr	r3, [r7, #44]
	mov	r2, r4
	mov	r1, r6
	blx	r3
	mov	r2, r4
	ldr	r3, [r7, #44]
	mov	r1, r6
	ldr	r0, [fp, #-108]
	blx	r3
	ldr	r1, [fp, #-72]
	ldr	r0, [fp, #-68]
	bl	MEM_ReleaseMemBlock
	ldr	r3, [r7, #48]
	mov	r2, #16
	sub	r0, fp, #76
	mov	r1, #0
	blx	r3
	ldr	r1, [fp, #-56]
	ldr	r0, [fp, #-52]
	bl	MEM_ReleaseMemBlock
	ldr	r3, [r7, #48]
	sub	r0, fp, #60
	mov	r2, #16
	mov	r1, #0
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L638:
	subs	r3, r4, #1
	ldr	r2, [fp, #-84]
	ldr	r7, .L726+4
	movne	r3, #1
	cmp	r2, r3
	str	r3, [fp, #-116]
	ldrhi	r3, [fp, #-116]
	strhi	r3, [fp, #-80]
	bls	.L657
.L659:
	cmp	r5, #0
	beq	.L660
	ldr	r2, [fp, #-80]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	mov	r10, r2, lsr #1
	ldr	r2, [fp, #-88]
	mul	r10, r5, r10
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L658:
	mov	r1, r4, lsr #8
	add	r0, r4, r10
	add	r0, r6, r0
	add	r4, r4, #256
	add	r1, r9, r1, lsl #12
	ldr	r3, [r7, #52]
	add	r1, r8, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L658
.L660:
	ldr	r3, [fp, #-80]
	ldr	r2, [fp, #-84]
	add	r3, r3, #2
	str	r3, [fp, #-80]
	cmp	r2, r3
	bhi	.L659
.L657:
	ldr	r4, [fp, #-84]
	mov	r0, r6
	ldr	r3, [r7, #44]
	ldr	r2, [fp, #-92]
	mul	r1, r4, r5
	mov	r1, r1, lsr #1
	blx	r3
	movs	r3, r4, lsr #1
	str	r3, [fp, #-84]
	beq	.L661
	ldr	r3, [fp, #-88]
	mov	r9, #0
	ldr	r10, [fp, #-112]
	str	r9, [fp, #-80]
	mov	r3, r3, asr #1
	str	r3, [fp, #-88]
.L662:
	cmp	r5, #0
	beq	.L664
	ldr	r2, [fp, #-80]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-88]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L663:
	mov	r1, r4, lsr #8
	add	r0, r9, r4
	add	r0, r6, r0
	add	r4, r4, #256
	add	r1, r8, r1, lsl #11
	ldr	r3, [r7, #52]
	add	r1, r10, r1
	mov	r2, #256
	blx	r3
	cmp	r5, r4
	bhi	.L663
.L664:
	ldr	r3, [fp, #-80]
	add	r9, r9, r5
	ldr	r2, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-80]
	cmp	r3, r2
	bne	.L662
.L661:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L725
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L667
	ldr	r2, [fp, #-100]
	ldr	r3, [fp, #-116]
	cmp	r2, r3
	bls	.L672
.L673:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L673
.L672:
	ldr	r3, [r7, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-108]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [fp, #-96]
	blx	r3
	b	.L667
.L725:
	ldr	r3, [fp, #-100]
	cmp	r3, #0
	beq	.L667
	ldr	r2, [fp, #-116]
	mov	lr, #0
	ldr	r0, [fp, #-104]
	ldr	ip, [fp, #-96]
	mla	r4, r5, r2, r6
	mov	r5, r5, asl #1
	mov	r6, r3
	add	r4, r4, #1
.L668:
	cmp	r0, #0
	beq	.L671
	mov	r3, lr, lsr #1
	mov	r2, r4
	mul	r3, r0, r3
	sub	r1, r3, #-67108863
	add	r9, r3, r0
	sub	r1, r1, #65011712
	add	r9, ip, r9
	add	r1, ip, r1
	add	r3, ip, r3
.L669:
	ldrb	r8, [r2, #-1]	@ zero_extendqisi2
	strb	r8, [r1, #1]!
	ldrb	r8, [r2], #2	@ zero_extendqisi2
	strb	r8, [r3], #1
	cmp	r3, r9
	bne	.L669
.L671:
	add	lr, lr, #2
	add	r4, r4, r5
	cmp	r6, lr
	bhi	.L668
	b	.L667
.L724:
	ldr	r8, [fp, #-100]
	cmp	r8, #0
	beq	.L667
	ldr	r3, [fp, #-96]
	add	r6, r6, #1
	ldr	r4, [fp, #-104]
	mov	lr, #0
.L651:
	cmp	r4, #0
	moveq	ip, r3
	beq	.L654
	sub	r1, r3, #-67108863
	add	ip, r3, r4
	sub	r1, r1, #65011712
	mov	r2, r6
.L652:
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	strb	r0, [r1, #1]!
	ldrb	r0, [r2], #2	@ zero_extendqisi2
	strb	r0, [r3], #1
	cmp	ip, r3
	bne	.L652
.L654:
	add	lr, lr, #1
	mov	r3, ip
	cmp	lr, r8
	add	r6, r6, r5
	bne	.L651
	b	.L667
.L723:
	ldr	r7, .L726+4
	mov	r0, r6
	ldr	r1, [fp, #-84]
	ldr	r2, [fp, #-92]
	ldr	r3, [r7, #44]
	blx	r3
	b	.L675
.L727:
	.align	2
.L726:
	.word	.LC60
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC61
	.word	.LC62
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_WriteBigTitle1DYuv, .-VDMHAL_V300R001_WriteBigTitle1DYuv
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.33315, %object
	.size	__func__.33315, 24
__func__.33315:
	.ascii	"VDMHAL_V300R001_OpenHAL\000"
	.type	__func__.33351, %object
	.size	__func__.33351, 27
__func__.33351:
	.ascii	"VDMHAL_V300R001_CalcFsSize\000"
	.space	1
	.type	__func__.33363, %object
	.size	__func__.33363, 35
__func__.33363:
	.ascii	"VDMHAL_V300R001_FillMemArrangeInfo\000"
	.space	1
	.type	__func__.33418, %object
	.size	__func__.33418, 27
__func__.33418:
	.ascii	"VDMHAL_V300R001_ArrangeMem\000"
	.space	1
	.type	__func__.33458, %object
	.size	__func__.33458, 31
__func__.33458:
	.ascii	"VDMHAL_V300R001_ArrangeMem_BTL\000"
	.space	1
	.type	__func__.33479, %object
	.size	__func__.33479, 25
__func__.33479:
	.ascii	"VDMHAL_V300R001_ResetVdm\000"
	.space	3
	.type	__func__.33506, %object
	.size	__func__.33506, 30
__func__.33506:
	.ascii	"VDMHAL_V300R001_ClearIntState\000"
	.space	2
	.type	__func__.33516, %object
	.size	__func__.33516, 24
__func__.33516:
	.ascii	"VDMHAL_V300R001_MaskInt\000"
	.type	__func__.33528, %object
	.size	__func__.33528, 26
__func__.33528:
	.ascii	"VDMHAL_V300R001_EnableInt\000"
	.space	2
	.type	__func__.33537, %object
	.size	__func__.33537, 25
__func__.33537:
	.ascii	"VDMHAL_V300R001_CheckReg\000"
	.space	3
	.type	__func__.33554, %object
	.size	__func__.33554, 27
__func__.33554:
	.ascii	"VDMHAL_V300R001_PrepareDec\000"
	.space	1
	.type	__func__.33575, %object
	.size	__func__.33575, 27
__func__.33575:
	.ascii	"VDMHAL_V300R001_IsVdmReady\000"
	.space	1
	.type	__func__.33580, %object
	.size	__func__.33580, 25
__func__.33580:
	.ascii	"VDMHAL_V300R001_IsVdmRun\000"
	.space	3
	.type	__func__.33594, %object
	.size	__func__.33594, 27
__func__.33594:
	.ascii	"VDMHAL_V300R001_BackupInfo\000"
	.space	1
	.type	__func__.33634, %object
	.size	__func__.33634, 25
__func__.33634:
	.ascii	"VDMHAL_V300R001_CfgRpMsg\000"
	.space	3
	.type	__func__.33655, %object
	.size	__func__.33655, 25
__func__.33655:
	.ascii	"VDMHAL_V300R001_CfgRpReg\000"
	.space	3
	.type	__func__.33668, %object
	.size	__func__.33668, 30
__func__.33668:
	.ascii	"VDMHAL_V300R001_MakeDecReport\000"
	.space	2
	.type	__func__.33693, %object
	.size	__func__.33693, 30
__func__.33693:
	.ascii	"VDMHAL_V300R001_PrepareRepair\000"
	.space	2
	.type	__func__.33701, %object
	.size	__func__.33701, 30
__func__.33701:
	.ascii	"VDMHAL_V300R001_StartHwRepair\000"
	.space	2
	.type	__func__.33747, %object
	.size	__func__.33747, 30
__func__.33747:
	.ascii	"VDMHAL_V300R001_StartHwDecode\000"
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
	ASCII(.ascii	"VDMHAL_V300R001_OpenHAL: Size error!\000" )
	.space	3
.LC4:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300R001_OpenHAL\012\000" )
	.space	3
.LC5:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC6:
	ASCII(.ascii	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"BPDRegVirAddr %p\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"!!!!!! HAL memory not enouph! need %d, have %d\012\000" )
.LC9:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300R001_CloseHAL\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"image size out of range\000" )
.LC12:
	ASCII(.ascii	"DFS, CurFsSize < 0, CurFsSize: %d\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"pVdmMemArrange is NULL\000" )
	.space	1
.LC14:
	ASCII(.ascii	"DFS, no ref frame!\012\000" )
.LC15:
	ASCII(.ascii	"DFS, Frame number = %d > 30, Then, Frame num = 30, " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"VDMHAL_V300R001_ArrangeMem Mem addr is NULL\000" )
.LC17:
	ASCII(.ascii	"'pVdmMemArrange' is NULL\000" )
	.space	3
.LC18:
	ASCII(.ascii	"MemSize not enough for pmv slot\000" )
.LC19:
	ASCII(.ascii	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight" )
	ASCII(.ascii	" failed!\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"ImgSlotLen > ChanSlotLen\000" )
	.space	3
.LC21:
	ASCII(.ascii	"cann't allocate img slot\000" )
	.space	3
.LC22:
	ASCII(.ascii	"Mem addr is 0\000" )
	.space	2
.LC23:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300R001_ResetVdm\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"VDMHAL_V300R001_ResetVdm: map vdm register fail, vi" )
	ASCII(.ascii	"r(reg) = (%p)\012\000" )
	.space	2
.LC25:
	ASCII(.ascii	"VDH: %d VDMHAL_V300R001_ResetVdm ERROR!!!\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"Ignore the reset request when the VDH clock is clos" )
	ASCII(.ascii	"ed.\012\000" )
.LC27:
	ASCII(.ascii	"GLB Reset failed!\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V200R003_ClearIntState\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC30:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V200_MaskInt\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V200R003_EnableInt\012\000" )
	.space	1
.LC32:
	ASCII(.ascii	"%s: VdhId(%d) Invalid!\012\000" )
.LC33:
	ASCII(.ascii	"%s: vdm register virtual address not mapped, reset " )
	ASCII(.ascii	"failed!\012\000" )
.LC34:
	ASCII(.ascii	"%s: unkown reg_id = %d\012\000" )
.LC35:
	ASCII(.ascii	"VDM register not mapped yet!\000" )
	.space	3
.LC36:
	ASCII(.ascii	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"VDM register not mapped yet!\012\000" )
	.space	2
.LC38:
	ASCII(.ascii	"pBackUpInfo = NULL!\000" )
.LC39:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300R001_BackupInfo\012\000" )
.LC40:
	ASCII(.ascii	"can NOT map vir addr for up-msg\000" )
.LC41:
	ASCII(.ascii	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"ReadUpMsgSlot error! upmsg_size(%d) > 512\012\000" )
	.space	1
.LC43:
	ASCII(.ascii	"can not map repair msg virtual address!\000" )
.LC44:
	ASCII(.ascii	"ValidGroupNum=%d out of range!\012\000" )
.LC45:
	ASCII(.ascii	"align_mb error\012\000" )
.LC46:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300_CfgRpReg\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"'pMakeDecReport' is NULL\000" )
	.space	3
.LC48:
	ASCII(.ascii	"'pDecReport' is NULL\000" )
	.space	3
.LC49:
	ASCII(.ascii	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full" )
	ASCII(.ascii	" repair.\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"\012***** UpMsg DecSliceNum=%d\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"\012***** Up Msg (phy addr: %#8x) *****\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"\012***** Up Msg print finished *****\012\000" )
.LC54:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V200R003_PrepareRepair\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"vdm register virtual address not mapped, VDMHAL_V20" )
	ASCII(.ascii	"0R003_PrepareRepair failed!\012\000" )
.LC56:
	ASCII(.ascii	"FIRST_REPAIR Parameter Error!\012\000" )
	.space	1
.LC57:
	ASCII(.ascii	"SECOND_REPAIR Parameter Error!\012\000" )
.LC58:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300R001_StartHwDecode\012\000" )
	.space	1
.LC60:
	ASCII(.ascii	"BigTile1d_y\000" )
.LC61:
	ASCII(.ascii	"failed mem_allocMemBlock BigTile_yuv save!\012\000" )
.LC62:
	ASCII(.ascii	"BigTile1d_uv\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
