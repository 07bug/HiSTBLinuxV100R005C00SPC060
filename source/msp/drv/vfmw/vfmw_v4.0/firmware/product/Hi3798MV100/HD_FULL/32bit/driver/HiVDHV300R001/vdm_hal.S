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
	@ args = 20, pretend = 0, frame = 48
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
	ldr	r8, [fp, #16]
	mov	r4, r0
	str	r1, [fp, #-68]
	cmn	r8, #2
	mov	r6, r2
	str	r3, [fp, #-64]
	ldr	r5, [fp, #4]
	ldr	r7, [fp, #20]
	beq	.L106
	cmp	r8, #0
	blt	.L107
	mov	r0, r8
	ldr	r10, .L172
	bl	VCTRL_GetVidStd
	mov	r9, r0
	ldr	r0, [r10, r8, asl #2]
	ldr	r3, [r0, #1404]
	cmp	r3, #1
	beq	.L150
.L37:
	cmp	r4, #0
	subne	r2, r6, #32
	movwne	r3, #8160
	beq	.L151
	cmp	r2, r3
	bhi	.L70
	ldr	r2, [fp, #-64]
	sub	r2, r2, #32
	cmp	r2, r3
	bhi	.L70
	cmp	r7, #0
	beq	.L152
	ldr	r3, .L172+4
	cmp	r5, #20
	mov	r2, #564
	mov	r1, #0
	mov	r0, r7
	movlt	r10, r5
	str	r3, [fp, #-76]
	movge	r10, #20
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [fp, #-64]
	add	r2, r6, #15
	add	r1, r3, #15
	ldr	r3, .L172+8
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
	cmp	r9, #17
	beq	.L76
	mul	r5, r2, ip
	mul	r5, r5, r1
	ldr	r1, [fp, #-68]
	add	r5, r5, #127
	bic	r5, r5, #127
	mul	r2, r10, r5
	cmp	r2, r1
	str	r2, [fp, #-72]
	bge	.L104
	add	r1, r0, #255
	mov	r2, r5, asr #1
	bic	r1, r1, #255
	str	r10, [r7, #552]
	str	r2, [r7, #548]
.L103:
	sub	r2, r0, #1
	mov	ip, r1, asl #4
	cmp	r2, #2048
	str	ip, [r7]
	movcc	r10, #16
	bcc	.L78
	sub	r2, r0, #2048
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r10, #32
	bcc	.L78
	sub	r2, r0, #4096
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r10, #48
	bcs	.L153
.L78:
	ldr	r2, [fp, #12]
	cmp	r2, #1
	beq	.L154
	cmp	r9, #17
	beq	.L155
	adds	r2, r3, #31
	addmi	r2, r3, #62
	cmp	r8, #0
	mov	r2, r2, asr #5
	mov	r0, r2
	mov	ip, r2, asl #7
	sub	ip, ip, r0, asl #5
	mul	r2, r1, r2
	mul	ip, r10, ip
	mov	r6, r2, asl #6
	sub	r6, r6, r2, asl #4
	add	r6, r6, ip, lsr #1
	blt	.L84
.L80:
	mov	r0, r8
	str	r3, [fp, #-88]
	str	r1, [fp, #-84]
	bl	VCTRL_GetChanWidth
	str	r0, [fp, #-80]
	mov	r0, r8
	bl	VCTRL_GetChanHeight
	ldr	r2, [fp, #-80]
	ldr	r1, [fp, #-84]
	ldr	r3, [fp, #-88]
	cmn	r0, #1
	cmnne	r2, #1
	beq	.L156
	add	r2, r2, #15
	add	r0, r0, #15
	bic	r2, r2, #15
	bic	r0, r0, #15
	sub	lr, r2, #1
	add	ip, r2, #255
	cmp	lr, #2048
	bic	ip, ip, #255
	movcc	lr, #16
	bcc	.L86
	sub	lr, r2, #2048
	sub	lr, lr, #1
	cmp	lr, #2048
	movcc	lr, #32
	bcs	.L157
.L86:
	ldr	r2, [fp, #12]
	cmp	r2, #1
	beq	.L158
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
.L88:
	cmp	ip, r6
	blt	.L159
	cmp	r9, #17
	beq	.L89
.L162:
	adds	r0, r3, #31
	addmi	r0, r3, #62
	mov	r0, r0, asr #5
	mul	r2, r0, r1
.L84:
	mov	r10, r10, asl #5
	mov	r2, r2, asl #5
	mla	r0, r0, r10, r2
	str	r0, [r7, #280]
.L90:
	ldr	r3, [fp, #8]
	cmp	r3, #0
	streq	r3, [r7, #292]
	bne	.L160
.L92:
	ldr	r3, [fp, #-76]
	mov	r0, #0
	ldr	r2, .L172+12
	ldr	r1, .L172+16
	ldr	r4, [r3, #68]
	ldr	r3, .L172+20
	blx	r4
	mvn	r3, #0
.L135:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L107:
	mov	r9, #20
	b	.L37
.L160:
	ldr	r3, [fp, #8]
	add	r8, r4, #1020
	ldr	r2, [fp, #-72]
	add	r8, r8, #3
	cmp	r3, #32
	ldr	r3, [fp, #-68]
	bic	r8, r8, #1020
	mov	r1, r6
	rsb	r0, r2, r3
	bic	r8, r8, #3
	ldr	r3, [fp, #8]
	rsb	r9, r4, r8
	rsb	r0, r9, r0
	movge	r10, #32
	movlt	r10, r3
	bl	__aeabi_idiv
	cmp	r10, r0
	movlt	r1, r10
	movge	r1, r0
	cmp	r1, #0
	str	r1, [r7, #292]
	beq	.L92
	addgt	r2, r7, #4
	movgt	r3, #0
	ble	.L161
.L95:
	add	r3, r3, #1
	str	r8, [r2, #4]!
	cmp	r3, r1
	add	r8, r8, r6
	bne	.L95
	mla	r6, r6, r1, r9
	add	r0, r7, #132
	mov	r2, #0
	add	r3, r6, r4
.L97:
	add	r2, r2, #1
	str	r3, [r0, #4]!
	cmp	r2, r1
	add	r3, r3, #32
	bne	.L97
.L102:
	ldr	r9, [r7, #552]
	add	r1, r6, r1, lsl #5
	add	r4, r1, r4
	cmp	r9, #0
	addgt	r2, r7, #424
	movgt	r3, #0
	ble	.L100
.L99:
	add	r3, r3, #1
	str	r4, [r2, #4]!
	cmp	r3, r9
	add	r4, r4, r5
	bne	.L99
.L100:
	mla	r1, r9, r5, r1
	mov	r3, #0
	mov	r0, r3
	str	r1, [r7, #4]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L106:
	mov	r9, #17
	b	.L37
.L76:
	mul	r5, r0, r1
	ldr	r1, [fp, #-68]
	add	r5, r5, #127
	bic	r5, r5, #127
	mul	r2, r10, r5
	cmp	r2, r1
	str	r2, [fp, #-72]
	bge	.L104
	add	r1, r6, #255
	mov	r2, r5, asr #1
	str	r10, [r7, #552]
	bic	r1, r1, #255
	str	r2, [r7, #548]
	b	.L103
.L154:
	mul	r6, r3, r1
	cmp	r8, #0
	add	r6, r6, r6, lsl #1
	bge	.L80
	cmp	r9, #17
	bne	.L162
.L89:
	ldr	r3, [fp, #-64]
	mul	r2, r3, r1
.L83:
	str	r2, [r7, #280]
	b	.L90
.L157:
	sub	lr, r2, #4096
	sub	lr, lr, #1
	cmp	lr, #2048
	movcc	lr, #48
	bcc	.L86
	sub	r2, r2, #6144
	sub	r2, r2, #1
	cmp	r2, #2048
	movcs	lr, #16
	movcc	lr, #64
	b	.L86
.L153:
	sub	r0, r0, #6144
	sub	r0, r0, #1
	cmp	r0, #2048
	movcs	r10, #16
	movcc	r10, #64
	b	.L78
.L155:
	ldr	r2, [fp, #-64]
	cmp	r8, #0
	mul	r2, r2, r1
	add	r6, r2, r2, lsl #1
	mov	r6, r6, asr #1
	bge	.L80
	b	.L83
.L158:
	mul	ip, r0, ip
	add	ip, ip, ip, lsl #1
	b	.L88
.L150:
	sub	r2, r6, #32
	movw	r3, #8160
	cmp	r2, r3
	add	r2, r0, #225280
	ldr	r5, [r2, #2872]
	bhi	.L38
	ldr	r2, [fp, #-64]
	sub	r2, r2, #32
	cmp	r2, r3
	bls	.L39
.L38:
	ldr	r3, .L172+4
	mov	r0, #0
	ldr	r2, .L172+24
	mvn	r4, #0
	mov	r1, r3
	str	r3, [fp, #-76]
	ldr	r5, [r1, #68]
	ldr	r3, .L172+28
	ldr	r1, .L172+16
	blx	r5
.L40:
	ldr	r3, [fp, #-76]
	mov	r2, r4
	ldr	r1, .L172+32
	mov	r0, #31
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L135
.L161:
	mla	r6, r6, r1, r9
	b	.L102
.L70:
	ldr	r1, .L172+4
	mov	r0, #0
	ldr	r3, .L172+28
.L142:
	ldr	r4, [r1, #68]
	ldr	r2, .L172+12
	ldr	r1, .L172+16
	blx	r4
	mvn	r3, #0
	b	.L135
.L39:
	ldr	r3, [fp, #-64]
	add	r2, r6, #15
	ldr	r1, .L172+8
	add	r3, r3, #15
	mov	r2, r2, asr #4
	mov	r3, r3, asr #4
	ldrb	lr, [r1]	@ zero_extendqisi2
	cmp	r2, #45
	cmple	r3, #36
	mov	ip, r2, asl #4
	mov	r4, r3, asl #4
	movle	r1, #64
	movgt	r1, #32
	cmp	lr, #1
	moveq	r1, #64
	cmp	r9, #17
	beq	.L163
	mul	r2, r1, r2
	add	r1, ip, #255
	bic	r1, r1, #255
	str	r1, [fp, #-68]
	mul	r3, r2, r3
	add	r3, r3, #127
	bic	r3, r3, #127
	str	r3, [fp, #-72]
.L101:
	sub	r2, ip, #1
	cmp	r2, #2048
	movcc	r3, #16
	bcc	.L45
	sub	r2, ip, #2048
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r3, #32
	bcc	.L45
	sub	r2, ip, #4096
	sub	r2, r2, #1
	cmp	r2, #2048
	movcc	r3, #48
	bcc	.L45
	sub	ip, ip, #6144
	sub	ip, ip, #1
	cmp	ip, #2048
	movcs	r3, #0
	movcc	r3, #64
.L45:
	ldr	r2, [fp, #12]
	cmp	r2, #1
	beq	.L164
	cmp	r9, #17
	beq	.L165
	adds	r2, r4, #31
	ldr	r1, [fp, #-68]
	addmi	r4, r4, #62
	movpl	r4, r2
	add	r0, r0, #228352
	add	ip, r1, r3
	ldr	r3, .L172+4
	mov	r4, r4, asr #5
	mov	r2, #572
	mov	r1, #0
	add	r0, r0, #472
	mul	r4, r4, ip
	ldr	r9, [r3, #48]
	str	r3, [fp, #-76]
	mov	ip, r4, asl #6
	sub	r3, ip, r4, asl #4
	str	r3, [fp, #-80]
	blx	r9
	ldr	r1, [fp, #-68]
	ldr	r2, [r10, r8, asl #2]
	ldr	r3, [fp, #-72]
	mov	ip, r1, asl #4
	add	r1, r2, #225280
	mov	r0, r3, asr #1
	str	ip, [r1, #3544]
	str	r0, [r1, #4092]
.L51:
	mov	r4, r4, asl #5
.L141:
	str	r4, [r1, #3824]
	add	r2, r2, #229376
	ldr	r3, [fp, #-72]
	ldr	r1, [fp, #-80]
	add	r4, r3, r1
	str	r3, [r2, #16]
	adds	r4, r4, #1056
	str	r1, [r2, #12]
	bmi	.L40
	cmp	r5, r4
	ldr	r5, [r10, r8, asl #2]
	add	r9, r5, #225280
	beq	.L166
.L56:
	ldr	r3, .L172+36
	str	r4, [r9, #2872]
	ldr	r5, [r9, #2876]
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L58
	ldr	r0, [fp, #-64]
	mov	r3, #16
	str	r5, [fp, #-60]
	sub	r2, fp, #60
	str	r4, [fp, #-56]
	mov	r1, #118
	str	r0, [fp, #-48]
	mov	r0, r8
	str	r6, [fp, #-52]
	blx	r7
.L58:
	ldr	ip, [r10, r8, asl #2]
	mov	r3, r5
	ldr	r5, [fp, #-76]
	mov	r2, r4
	add	ip, ip, #225280
	ldr	r1, .L172+40
	mov	r0, #31
	ldr	ip, [ip, #2896]
	ldr	r4, [r5, #68]
	str	ip, [sp]
	blx	r4
	ldr	r3, [r5]
	ldr	r4, [r10, r8, asl #2]
	blx	r3
	ldr	r2, [r10, r8, asl #2]
	mov	r1, #1
	add	r4, r4, #229376
	mov	r3, #2
	add	r2, r2, #225280
	str	r0, [r4, #20]
	str	r1, [r2, #2860]
	b	.L135
.L166:
	ldr	r3, [r9, #2896]
	cmp	r3, #1
	beq	.L56
	cmp	r7, #0
	beq	.L167
	add	r2, r5, #229376
	ldr	r3, [r9, #2876]
	str	r2, [fp, #-68]
	cmp	r3, #0
	ldr	r3, [r2, #12]
	ldr	r4, [r2, #16]
	str	r3, [fp, #-64]
	beq	.L168
.L60:
	ldr	r0, [r10, r8, asl #2]
	ldr	r6, .L172
	add	lr, r0, #225280
	ldr	ip, [lr, #2880]
	cmp	ip, #30
	bgt	.L169
.L61:
	cmp	ip, #0
	str	ip, [r9, #3836]
	addle	r10, r5, #228352
	ble	.L62
	ldr	r2, [lr, #2912]
	cmp	r2, #0
	beq	.L63
	add	r3, r2, #1020
	ldr	r1, [fp, #-64]
	add	r3, r3, #3
	bic	r3, r3, #1020
	bic	r3, r3, #3
	str	r3, [r9, #3552]
	rsb	r3, r2, r3
	add	r3, r1, r3
	add	r1, r3, #32
	add	r3, r3, r2
	str	r3, [r9, #3680]
	add	r3, r1, r2
	str	r3, [r9, #3972]
	add	r1, r4, r1
	ldr	r6, [lr, #2872]
	cmp	r1, r6
	bgt	.L113
	add	r10, r5, #228352
	add	r0, r0, #227328
	str	r7, [fp, #20]
	add	r0, r0, #884
	add	r5, r10, #480
	add	r8, r10, #608
	mov	r3, #0
	ldr	r7, [fp, #-64]
	b	.L65
.L67:
	ldr	r2, [r0]
	add	r0, r0, #20
	add	r6, r2, #1020
	cmp	r2, #0
	add	r6, r6, #3
	bic	r6, r6, #1020
	beq	.L170
	bic	r6, r6, #3
	str	r6, [r5, #4]!
	rsb	r6, r2, r6
	add	r6, r7, r6
	add	r1, r6, #32
	add	r6, r6, r2
	str	r6, [r8, #4]!
	add	r6, r1, r2
	str	r6, [r5, #420]
	add	r1, r4, r1
	ldr	r6, [lr, #2872]
	cmp	r1, r6
	bgt	.L64
.L65:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L67
	ldr	r7, [fp, #20]
.L62:
	ldr	r3, [lr, #2872]
	add	r1, r10, #472
	ldr	r2, [fp, #-76]
	mov	r0, r7
	mul	r3, ip, r3
	ldr	r4, [r2, #52]
	mov	r2, #564
	str	r3, [r9, #3548]
	ldr	r3, [fp, #-68]
	str	ip, [r3]
	blx	r4
	mov	r3, #0
	b	.L135
.L151:
	ldr	r1, .L172+4
	mov	r0, r4
	ldr	r3, .L172+44
	b	.L142
.L104:
	ldr	r3, [fp, #-76]
	mov	r0, #0
	ldr	r2, .L172+12
	ldr	r1, .L172+16
	ldr	r4, [r3, #68]
	ldr	r3, .L172+48
	blx	r4
	mvn	r3, #0
	b	.L135
.L170:
	ldr	r6, [lr, #2872]
.L64:
	str	r2, [sp, #8]
	mov	r0, #1
	ldr	r2, [fp, #-76]
	str	r1, [sp]
	str	r6, [sp, #4]
	ldr	r1, .L172+52
	ldr	r4, [r2, #68]
	ldr	r2, .L172+56
	blx	r4
	mvn	r3, #0
	b	.L135
.L159:
	ldr	r3, [fp, #-76]
	mov	r0, #0
	ldr	r2, .L172+12
	ldr	r1, .L172+16
	ldr	r4, [r3, #68]
	ldr	r3, .L172+60
	blx	r4
	mvn	r3, #0
	b	.L135
.L156:
	ldr	r3, [fp, #-76]
	mov	r0, #0
	ldr	r1, .L172+64
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L135
.L152:
	ldr	r1, .L172+4
	mov	r0, r7
	ldr	r3, .L172+68
	b	.L142
.L163:
	mul	r3, ip, r3
	add	r2, r6, #255
	bic	r2, r2, #255
	str	r2, [fp, #-68]
	add	r3, r3, #127
	bic	r3, r3, #127
	str	r3, [fp, #-72]
	b	.L101
.L164:
	str	r3, [fp, #-84]
	add	r0, r0, #228352
	ldr	r3, [fp, #-68]
	mov	r1, #0
	ldr	r2, .L172+4
	add	r0, r0, #472
	mul	ip, r3, r4
	mov	lr, r2
	ldr	lr, [lr, #48]
	str	r2, [fp, #-76]
	mov	r2, #572
	add	ip, ip, ip, lsl #1
	str	ip, [fp, #-80]
	mov	ip, lr
	blx	ip
	ldr	r1, [fp, #-72]
	ldr	r2, [r10, r8, asl #2]
	cmp	r9, #17
	ldr	r3, [fp, #-68]
	mov	ip, r1, asr #1
	add	r1, r2, #225280
	mov	r0, r3, asl #4
	str	ip, [r1, #4092]
	str	r0, [r1, #3544]
	ldr	r3, [fp, #-84]
	beq	.L171
	adds	r0, r4, #31
	ldr	ip, [fp, #-68]
	addmi	r0, r4, #62
	add	ip, ip, r3
	mov	r0, r0, asr #5
	mul	r4, r0, ip
	b	.L51
.L169:
	ldr	r3, [fp, #-76]
	mov	r2, ip
	ldr	r1, .L172+72
	mov	r0, #31
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [r6, r8, asl #2]
	mov	r2, #30
	add	r3, r0, #225280
	mov	ip, r2
	mov	lr, r3
	str	r2, [r3, #2880]
	b	.L61
.L168:
	ldr	r3, [fp, #-76]
	mov	r0, #31
	ldr	r1, .L172+76
	ldr	r3, [r3, #68]
	blx	r3
	b	.L60
.L165:
	ldr	r3, [fp, #-68]
	add	r0, r0, #228352
	ldr	r2, [fp, #-64]
	mov	r1, #0
	add	r0, r0, #472
	mul	r4, r3, r2
	ldr	r2, .L172+4
	mov	ip, r2
	str	r2, [fp, #-76]
	ldr	r9, [ip, #48]
	mov	r2, #572
	add	ip, r4, r4, lsl #1
	mov	ip, ip, asr #1
	str	ip, [fp, #-80]
	blx	r9
	ldr	r3, [fp, #-68]
	ldr	r2, [r10, r8, asl #2]
	mov	ip, r3, asl #4
	ldr	r3, [fp, #-72]
	add	r1, r2, #225280
	mov	r0, r3, asr #1
	str	ip, [r1, #3544]
	str	r0, [r1, #4092]
	b	.L141
.L171:
	ldr	r3, [fp, #-68]
	ldr	r0, [fp, #-64]
	mul	r4, r3, r0
	b	.L141
.L167:
	ldr	r3, [fp, #-76]
	mov	r0, r7
	ldr	r2, .L172+80
	ldr	r1, .L172+16
	ldr	r4, [r3, #68]
	ldr	r3, .L172+84
	blx	r4
	mvn	r3, #0
	b	.L135
.L113:
	mov	r3, #0
	b	.L64
.L63:
	ldr	r6, [lr, #2872]
	mov	r3, r2
	mov	r1, r2
	b	.L64
.L173:
	.align	2
.L172:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_not_direct_8x8_inference_flag
	.word	.LANCHOR0+88
	.word	.LC1
	.word	.LC22
	.word	.LANCHOR0+24
	.word	.LC11
	.word	.LC12
	.word	g_event_report
	.word	.LC13
	.word	.LC17
	.word	.LC19
	.word	.LC23
	.word	.LANCHOR0+116
	.word	.LC21
	.word	.LC20
	.word	.LC18
	.word	.LC16
	.word	.LC15
	.word	.LANCHOR0+52
	.word	.LC14
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
	ldr	r7, [fp, #4]
	ldr	r8, [fp, #20]
	ldreq	r1, .L226
	ldreq	r3, .L226+4
	beq	.L218
	ldr	r3, [fp, #16]
	sub	r2, r2, #32
	cmp	r3, #1
	movw	r3, #8160
	beq	.L221
	cmp	r2, r3
	bhi	.L180
	sub	r2, r6, #32
	cmp	r2, r3
	bhi	.L180
.L179:
	cmp	r8, #0
	beq	.L222
	ldr	r5, .L226
	cmp	r7, #20
	mov	r2, #564
	mov	r1, #0
	mov	r0, r8
	movge	r7, #20
	ldr	r3, [r5, #48]
	add	r6, r6, #15
	blx	r3
	ldr	r1, .L226+8
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
	mul	r10, r7, r6
	cmp	r10, r3
	bge	.L223
	add	r3, r4, #1020
	sub	r1, r0, #1
	add	ip, r0, #255
	add	r3, r3, #3
	cmp	r1, #2048
	bic	r3, r3, #1020
	bic	ip, ip, #255
	bic	r3, r3, #3
	rsb	r1, r4, r3
	str	r7, [r8, #552]
	str	r1, [fp, #-52]
	movcc	r0, #16
	mov	r1, ip, asl #4
	str	r1, [r8]
	mov	r1, r6, asr #1
	str	r1, [r8, #548]
	bcc	.L185
	sub	r1, r0, #2048
	sub	r1, r1, #1
	cmp	r1, #2048
	movcc	r0, #32
	bcc	.L185
	sub	r1, r0, #4096
	sub	r1, r1, #1
	cmp	r1, #2048
	movcc	r0, #48
	bcs	.L224
.L185:
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
	str	r5, [r8, #280]
	beq	.L186
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
.L186:
	ldr	r5, [fp, #24]
	cmp	r5, #0
	bne	.L225
	ldr	lr, [fp, #12]
	cmp	lr, #0
	beq	.L202
	ldr	lr, [fp, #12]
	ldr	r5, [fp, #24]
	cmp	lr, #6
	movge	r9, lr
	movlt	r9, #6
	str	r9, [r8, #424]
.L191:
	add	r5, r2, r5
	cmp	r9, #0
	mulle	r5, r9, r5
	ble	.L189
	add	lr, r8, #292
	mov	r2, #0
.L192:
	add	r2, r2, #1
	str	r3, [lr, #4]!
	cmp	r2, r9
	add	r3, r3, r5
	bne	.L192
	mul	r5, r5, r2
.L189:
	ldr	r3, [fp, #8]
	cmp	r3, #0
	ldr	r3, [fp, #-52]
	add	r5, r3, r5
	bne	.L193
	ldr	r3, [fp, #8]
	mov	r9, r3
	str	r3, [r8, #292]
.L194:
	cmp	r7, #0
	add	r9, r5, r9
	add	r4, r9, r4
	addgt	r0, r8, #424
	movgt	r1, #0
	ble	.L201
.L200:
	add	r1, r1, #1
	str	r4, [r0, #4]!
	cmp	r1, r7
	add	r4, r4, r6
	bne	.L200
.L201:
	mov	r0, #0
	add	r9, r10, r9
	str	r9, [r8, #4]
.L216:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L225:
	adds	r5, r9, #127
	addmi	r5, r9, #254
	ldr	r9, [fp, #12]
	mov	r5, r5, asr #7
	cmp	r9, #0
	mov	r9, r5, asl #9
	sub	r5, r9, r5, asl #7
	mul	r5, lr, r5
	mov	r5, r5, asr #1
	beq	.L202
	ldr	lr, [fp, #12]
	str	lr, [r8, #424]
	mov	r9, lr
	b	.L191
.L193:
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
	str	r0, [r8, #292]
	mulle	r9, r0, r3
	ble	.L194
	add	r2, r5, r4
	add	r1, r8, #4
	mov	r9, #0
.L198:
	add	r9, r9, #1
	str	r2, [r1, #4]!
	cmp	r9, r0
	add	r2, r2, r3
	bne	.L198
	mul	r9, r9, r3
	b	.L194
.L202:
	mov	r5, #0
	str	r5, [r8, #424]
	b	.L189
.L221:
	cmp	r2, r3
	bhi	.L180
	sub	r2, r6, #32
	movw	r3, #16352
	cmp	r2, r3
	bls	.L179
.L180:
	ldr	r1, .L226
	mov	r0, #0
	ldr	r3, .L226+12
.L218:
	ldr	r4, [r1, #68]
	ldr	r2, .L226+16
	ldr	r1, .L226+20
	blx	r4
	mvn	r0, #0
	b	.L216
.L224:
	sub	r0, r0, #6144
	sub	r0, r0, #1
	cmp	r0, #2048
	movcs	r0, #16
	movcc	r0, #64
	b	.L185
.L223:
	ldr	r4, [r5, #68]
	mov	r0, #0
	ldr	r3, .L226+24
	ldr	r2, .L226+16
	ldr	r1, .L226+20
	blx	r4
	mvn	r0, #0
	b	.L216
.L222:
	ldr	r1, .L226
	mov	r0, r8
	ldr	r3, .L226+28
	b	.L218
.L227:
	.align	2
.L226:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	.word	g_not_direct_8x8_inference_flag
	.word	.LC11
	.word	.LANCHOR0+152
	.word	.LC1
	.word	.LC19
	.word	.LC18
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
	beq	.L230
	cmp	r8, #1
	bne	.L249
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	ldr	r2, .L252
	mov	r0, #0
	mov	r3, r8
	str	r0, [sp]
	ldr	r1, .L252+4
	ldr	r4, [r2, #68]
	ldr	r2, .L252+8
	blx	r4
.L228:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L249:
	ldr	r3, .L252
	mov	r0, #0
	ldr	r1, .L252+12
	ldr	r3, [r3, #68]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	r3
.L230:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L250
	ldr	r5, .L252+16
	ldr	r6, .L252+20
	ldr	r3, [r5]
	ldr	r1, [r6]
	ldr	r7, [r3, #36]
	ldr	r4, [r1, #120]
	tst	r4, #1
	beq	.L228
	orr	r4, r4, #64
	str	r4, [r1, #120]
	ldr	r3, [r1, #372]
	tst	r3, #4
	bne	.L235
	mov	r3, #1
	movw	r0, #10000
	b	.L237
.L251:
	add	r3, r3, #1
	cmp	r3, r0
	beq	.L238
.L237:
	ldr	r2, [r1, #372]
	tst	r2, #4
	beq	.L251
	movw	r2, #10000
	cmp	r3, r2
	beq	.L238
.L239:
	bfc	r4, #6, #1
	str	r4, [r1, #120]
.L240:
	ldr	r3, [r5]
	str	r7, [r3, #36]
	b	.L228
.L238:
	ldr	r3, .L252
	mov	r2, #0
	ldr	r1, .L252+24
	mov	r0, r2
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r6]
	b	.L239
.L250:
	ldr	r3, .L252
	ldr	r1, .L252+28
	ldr	r3, [r3, #68]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	bx	r3
.L235:
	bfi	r4, r8, #6, #1
	str	r4, [r1, #120]
	b	.L240
.L253:
	.align	2
.L252:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	.word	.LANCHOR0+184
	.word	.LC25
	.word	g_HwMem
	.word	g_pstRegCrg
	.word	.LC27
	.word	.LC26
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
	beq	.L265
	ldr	r5, .L269
	ldr	r2, [r5]
	ldr	r4, [r2, #120]
	tst	r4, #1
	beq	.L266
	orr	r4, r4, #16
	str	r4, [r2, #120]
	ldr	r3, [r2, #372]
	tst	r3, #1
	bne	.L260
	movw	r0, #9999
	b	.L258
.L268:
	subs	r0, r0, #1
	beq	.L267
.L258:
	ldr	r3, [r2, #372]
	tst	r3, #1
	beq	.L268
.L260:
	bfc	r4, #4, #1
	str	r4, [r2, #120]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L266:
	ldr	r3, .L269+4
	mov	r0, #3
	ldr	r1, .L269+8
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L267:
	ldr	r3, .L269+4
	ldr	r1, .L269+12
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r2, [r5]
	b	.L260
.L265:
	ldr	r3, .L269+4
	ldr	r1, .L269+16
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L270:
	.align	2
.L269:
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	.word	.LC29
	.word	.LC26
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
	ldr	r7, .L292
	mov	r5, r0, asl #3
	mov	r6, r0, asl #6
	rsb	r3, r5, r6
	ldr	r2, .L292+4
	add	r3, r7, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1232]
	moveq	r4, r3
	cmp	r0, #1
	bhi	.L288
	cmp	r0, #0
	bgt	.L289
	movw	r8, #1208
	ldr	r9, .L292+8
	mul	r8, r8, r0
	ldr	r3, [r9, r8]
	cmp	r3, #0
	beq	.L290
.L277:
	cmp	r4, #1
	beq	.L291
.L285:
	mvn	r2, #0
	str	r2, [r3, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L289:
	ldr	r1, .L292+12
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r2, .L292+16
	ldr	r4, [r1, #68]
	ldr	r1, .L292+20
	blx	r4
.L271:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L288:
	ldr	r3, .L292+12
	mov	r0, #0
	ldr	r1, .L292+24
.L286:
	ldr	r3, [r3, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L291:
	rsb	r5, r5, r6
	add	r7, r7, r5
	ldr	r2, [r7, #52]
	cmp	r2, #1
	beq	.L285
	cmp	r2, #2
	ldr	r1, [r3, #28]
	mvneq	r2, #11
	streq	r2, [r3, #32]
	beq	.L271
	cmp	r2, #3
	mvneq	r2, #14
	streq	r2, [r3, #32]
	b	.L271
.L290:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r9, r8]
	bne	.L277
.L278:
	ldr	r3, .L292+12
	ldr	r1, .L292+28
	b	.L286
.L293:
	.align	2
.L292:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+212
	.word	.LC5
	.word	.LC30
	.word	.LC31
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
	bhi	.L303
	cmp	r0, #0
	bgt	.L304
	movw	r4, #1208
	ldr	r5, .L306
	mul	r4, r4, r0
	ldr	r3, [r5, r4]
	cmp	r3, #0
	beq	.L305
.L299:
	mvn	r2, #0
	str	r2, [r3, #36]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L304:
	ldr	r1, .L306+4
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r2, .L306+8
	ldr	r4, [r1, #68]
	ldr	r1, .L306+12
	blx	r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L303:
	ldr	r3, .L306+4
	mov	r0, #0
	ldr	r1, .L306+16
.L302:
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L305:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r5, r4]
	bne	.L299
.L300:
	ldr	r3, .L306+4
	ldr	r1, .L306+20
	b	.L302
.L307:
	.align	2
.L306:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+244
	.word	.LC5
	.word	.LC32
	.word	.LC31
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
	ldr	r2, .L326
	mov	r3, r0, asl #6
	ldr	r1, .L326+4
	sub	r3, r3, r0, asl #3
	add	r3, r2, r3
	ldr	r3, [r3, #8]
	ldr	r3, [r1, r3, asl #2]
	cmp	r3, #0
	ldrne	r4, [r3, #1232]
	moveq	r4, r3
	cmp	r0, #1
	bhi	.L323
	cmp	r0, #0
	bgt	.L324
	movw	r5, #1208
	ldr	r6, .L326+8
	mul	r5, r5, r0
	ldr	r3, [r6, r5]
	cmp	r3, #0
	beq	.L325
.L314:
	cmp	r4, #1
	mvnne	r2, #1
	strne	r2, [r3, #36]
	beq	.L322
.L308:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L324:
	ldr	r1, .L326+12
	mov	r2, #0
	mov	r3, r0
	str	r2, [sp]
	mov	r0, r2
	ldr	r2, .L326+16
	ldr	r4, [r1, #68]
	ldr	r1, .L326+20
	blx	r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L323:
	ldr	r3, .L326+12
	mov	r0, #0
	ldr	r1, .L326+24
.L321:
	ldr	r3, [r3, #68]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	bx	r3
.L322:
	mvn	r2, #5
	str	r2, [r3, #36]
	b	.L308
.L325:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	strne	r3, [r6, r5]
	bne	.L314
.L315:
	ldr	r3, .L326+12
	ldr	r1, .L326+28
	b	.L321
.L327:
	.align	2
.L326:
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+268
	.word	.LC5
	.word	.LC33
	.word	.LC31
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
	bgt	.L342
	movw	r4, #1208
	ldr	r6, .L344
	mul	r4, r4, r5
	ldr	r3, [r6, r4]
	cmp	r3, #0
	beq	.L343
.L331:
	sub	r2, r7, #1
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L333
.L335:
	.word	.L339
	.word	.L336
	.word	.L337
	.word	.L340
.L340:
	mov	r3, #40
.L334:
	movw	r1, #1208
	mul	r5, r1, r5
	ldr	r2, [r6, r5]
	ldr	r0, [r2, r3]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L339:
	mov	r3, #28
	b	.L334
.L337:
	mov	r3, #36
	b	.L334
.L336:
	mov	r3, #32
	b	.L334
.L333:
	ldr	ip, .L344+4
	mov	r3, r7
	ldr	r2, .L344+8
	mov	r0, #0
	ldr	r1, .L344+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L343:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r8, r0, #0
	beq	.L332
	str	r8, [r6, r4]
	b	.L331
.L342:
	ldr	ip, .L344+4
	mov	r3, r5
	ldr	r2, .L344+8
	mov	r0, #0
	ldr	r1, .L344+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L332:
	ldr	r3, .L344+4
	ldr	r2, .L344+8
	ldr	r1, .L344+20
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L345:
	.align	2
.L344:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+296
	.word	.LC36
	.word	.LC34
	.word	.LC35
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
	beq	.L347
	ldr	r6, .L374
	cmp	r0, #6
	moveq	r1, #1
	movne	r1, #0
	ldr	r0, [r6]
	bl	MEM_WritePhyWord
	cmp	r4, #0
	beq	.L351
	cmp	r4, #1
	bne	.L373
	ldr	r3, .L374+4
	mov	r1, r4
	ldr	r0, [r3]
	add	r0, r0, #8
	bl	MEM_WritePhyWord
.L354:
	ldr	r1, .L374+8
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L374+12
	ldr	r4, [r1, #68]
	ldr	r1, .L374+16
	blx	r4
.L347:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L373:
	cmp	r4, #0
	bgt	.L354
.L353:
	cmp	r5, #17
	ldrls	pc, [pc, r5, asl #2]
	b	.L347
.L356:
	.word	.L366
	.word	.L357
	.word	.L358
	.word	.L359
	.word	.L347
	.word	.L360
	.word	.L361
	.word	.L347
	.word	.L362
	.word	.L363
	.word	.L364
	.word	.L364
	.word	.L364
	.word	.L365
	.word	.L347
	.word	.L347
	.word	.L366
	.word	.L367
.L351:
	ldr	r0, [r6]
	mov	r1, #1
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	b	.L353
.L366:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	H264HAL_V300R001_StartDec
.L365:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP8HAL_V300R001_StartDec
.L364:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VP6HAL_V300R001_StartDec
.L363:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV9HAL_V300R001_StartDec
.L362:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	RV8HAL_V300R001_StartDec
.L361:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVSHAL_V300R001_StartDec
.L360:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DIVX3HAL_V300R001_StartDec
.L359:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP2HAL_V300R001_StartDec
.L358:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MP4HAL_V300R001_StartDec
.L357:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1HAL_V300R001_StartDec
.L367:
	mov	r1, r4
	mov	r0, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	HEVCHAL_V300R001_StartDec
.L375:
	.align	2
.L374:
	.word	s_RegPhyBaseAddr
	.word	s_RegPhyBaseAddr_1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+324
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
	ldr	r3, .L383
	ldr	r3, [r3, r2]
	cmp	r3, #0
	beq	.L381
	cmp	r0, #0
	ble	.L382
	ldr	r1, .L383+4
	mov	r3, r0
	ldr	r2, .L383+8
	mov	r0, #1
	str	r0, [sp]
	mov	r0, #32
	ldr	r4, [r1, #68]
	ldr	r1, .L383+12
	blx	r4
	mov	r0, #0
.L378:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L382:
	ldr	r0, [r3, #28]
	ubfx	r0, r0, #17, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L381:
	ldr	r1, .L383+4
	mov	r0, r3
	ldr	r2, .L383+8
	ldr	r3, .L383+16
	ldr	r4, [r1, #68]
	ldr	r1, .L383+20
	blx	r4
	mvn	r0, #0
	b	.L378
.L384:
	.align	2
.L383:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+352
	.word	.LC38
	.word	.LC37
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
	ldr	r3, .L392
	ldr	r4, [r3, r2]
	cmp	r4, #0
	beq	.L390
	cmp	r0, #0
	ble	.L391
	ldr	r1, .L392+4
	mov	r3, r0
	mov	r4, #1
	ldr	r2, .L392+8
	str	r4, [sp]
	mov	r0, #32
	ldr	r5, [r1, #68]
	ldr	r1, .L392+12
	blx	r5
	mov	r0, r4
.L387:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L391:
	ldr	r0, [r4, #40]
	subs	r0, r0, #1
	movne	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L390:
	ldr	r3, .L392+4
	mov	r0, r4
	ldr	r1, .L392+16
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	b	.L387
.L393:
	.align	2
.L392:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+380
	.word	.LC38
	.word	.LC39
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
	ldreq	r1, .L432
	ldreq	r3, .L432+4
	beq	.L425
	ldr	r3, [r2, #4]
	ldr	r5, [r2]
	cmp	r3, #1
	bhi	.L428
	cmp	r3, #0
	bne	.L399
	ldr	r3, .L432+8
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #60
	beq	.L416
.L402:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	beq	.L416
	cmp	r3, r1
	bne	.L402
	mov	r6, #0
.L400:
	ldr	r8, .L432+12
	ldr	lr, [r8]
	cmp	lr, #0
	beq	.L429
.L403:
	ldr	r7, [lr, #12]
	cmp	r6, #1
	ldr	r4, .L432+16
	str	r7, [r4]
	ldr	r3, [lr, #28]
	str	r3, [r4, #4]
	beq	.L430
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
	bne	.L407
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
.L407:
	rsb	r1, r4, #32768
	ldr	r3, .L432+20
	add	r1, r1, #208
	add	r1, r1, lr
	add	r0, r3, #128
.L408:
	ldr	r2, [r1, r3]
	ldr	ip, .L432+16
	str	r2, [r3, #4]!
	cmp	r3, r0
	bne	.L408
	cmp	r6, #0
	beq	.L413
.L414:
	and	r7, r7, #15
	cmp	r7, #5
	andeq	r9, r9, #1
	andne	r8, r8, #31
	moveq	r0, #0
	movne	r0, #0
	streq	r9, [r5]
	strne	r8, [r5]
.L420:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L413:
	movw	r2, #33152
	movw	r3, #33156
	ldr	r2, [lr, r2]
	str	r2, [ip, #48]
	ldr	r3, [lr, r3]
	str	r3, [ip, #44]
	b	.L414
.L416:
	mov	r6, r2
	b	.L400
.L430:
	ldr	r0, [r8, #32]
	ubfx	r7, r3, #0, #17
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L431
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
	b	.L407
.L429:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	lr, r0, #0
	beq	.L404
	str	lr, [r8]
	b	.L403
.L399:
	ldr	r1, .L432
	mov	r0, #0
	ldr	r2, .L432+24
	str	r0, [sp]
	ldr	r4, [r1, #68]
	ldr	r1, .L432+28
	blx	r4
	mvn	r0, #0
	b	.L420
.L428:
	ldr	r3, .L432
	mov	r0, #0
	ldr	r1, .L432+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L420
.L431:
	ldr	r1, .L432
	ldr	r3, .L432+36
.L425:
	ldr	r4, [r1, #68]
	ldr	r2, .L432+24
	ldr	r1, .L432+40
	blx	r4
	mvn	r0, #0
	b	.L420
.L404:
	ldr	r3, .L432
	ldr	r1, .L432+44
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L420
.L433:
	.align	2
.L432:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC40
	.word	g_DSPState
	.word	g_HwMem
	.word	g_BackUp
	.word	g_BackUp+48
	.word	.LANCHOR0+408
	.word	.LC5
	.word	.LC41
	.word	.LC42
	.word	.LC1
	.word	.LC31
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
	beq	.L438
	cmp	r2, #800
	ldr	r3, .L440
	bhi	.L439
	mov	r2, r2, asl #2
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L439:
	mov	r0, r4
	ldr	r1, .L440+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L438:
	ldr	ip, .L440
	mov	r2, r0
	ldr	r1, .L440+8
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L441:
	.align	2
.L440:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC44
	.word	.LC43
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
	beq	.L476
	ldr	r3, [fp, #-56]
	ldr	r2, [r3, #840]
	sub	r3, r2, #1
	cmp	r3, #199
	bhi	.L477
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
	beq	.L446
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
.L447:
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
	beq	.L450
	cmp	r3, #5
	moveq	r4, #4
	beq	.L450
	cmp	r3, #4
	moveq	r4, #8
	beq	.L450
	ldr	r3, .L481
	mov	r0, #1
	ldr	r1, .L481+4
	mov	r4, r0
	ldr	r3, [r3, #68]
	blx	r3
.L450:
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #856]
	cmp	r3, #0
	bne	.L468
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #840]
	subs	r9, r2, #0
	ble	.L469
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
	b	.L463
.L454:
	add	r7, r7, #1
	cmp	r9, r7
	ble	.L478
.L463:
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
	ble	.L453
	ldrsh	r0, [r5, #38]
	mov	r1, r4
	sub	r0, r0, #1
	add	r0, r0, r4
	bl	__aeabi_uidiv
	mul	r3, r4, r0
	cmp	r10, r3
	str	r3, [fp, #-76]
	bgt	.L455
	add	r7, r7, #1
	cmp	r9, r7
	bgt	.L463
.L478:
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #856]
	cmp	r3, #1
	bne	.L452
.L462:
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
	b	.L464
.L468:
	cmp	r3, #1
	mov	r2, #0
	str	r2, [fp, #-64]
	beq	.L462
.L452:
	ldr	r3, [fp, #-64]
	sub	r3, r3, #1
	uxth	r3, r3
.L464:
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
.L474:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L456:
	bl	__aeabi_uidiv
	mov	r1, r4
	mul	r6, r4, r0
	ldrsh	r0, [r5, #44]
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r6, r0
	add	r3, r0, #1
	bhi	.L458
	cmp	r6, r3
	mov	r1, r4
	beq	.L458
	ldrsh	r0, [r5, #38]
	add	r0, r0, r8
	bl	__aeabi_uidiv
	mul	r0, r4, r0
	cmp	r6, r0
	bhi	.L479
.L458:
	ldrh	r6, [r5, #46]
	add	r5, r5, #4
	mov	r7, r10
	sxth	r6, r6
.L455:
	add	r10, r7, #1
	mov	r1, r4
	cmp	r10, r9
	add	r0, r8, r6
	blt	.L456
	bl	__aeabi_uidiv
	mul	r10, r4, r0
.L457:
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
	bgt	.L480
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
	b	.L454
.L453:
	ldr	r2, [fp, #-76]
	cmp	r10, r2
	movgt	r2, #0
	movle	r2, #1
	cmp	r7, #0
	moveq	r2, #0
	cmp	r2, #0
	bne	.L454
	b	.L457
.L479:
	mov	r10, r6
	b	.L457
.L446:
	mul	r3, r3, lr
	mov	r2, #0
	b	.L447
.L480:
	ldr	r2, [fp, #-56]
	mov	r3, #1
	str	r3, [r2, #856]
	b	.L462
.L469:
	str	r3, [fp, #-64]
	b	.L452
.L477:
	ldr	r3, .L481
	mov	r0, #0
	ldr	r1, .L481+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L474
.L476:
	ldr	r1, .L481
	ldr	r3, .L481+12
	ldr	r2, .L481+16
	ldr	r4, [r1, #68]
	ldr	r1, .L481+20
	blx	r4
	mvn	r0, #0
	b	.L474
.L482:
	.align	2
.L481:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LC46
	.word	.LC45
	.word	.LANCHOR0+436
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
	bhi	.L492
	cmp	r3, #0
	bgt	.L493
	ldr	r3, [r1]
	cmp	r3, #0
	beq	.L494
.L488:
	movw	r3, #1208
	ldr	r2, .L495
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
.L491:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L494:
	mov	r0, #0
	str	r1, [fp, #-24]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L489
	ldr	r1, [fp, #-24]
	str	r3, [r1]
	b	.L488
.L493:
	ldr	r1, .L495+4
	mov	r2, #0
	mov	r0, r2
	str	r2, [sp]
	ldr	r2, .L495+8
	ldr	r4, [r1, #68]
	ldr	r1, .L495+12
	blx	r4
	mvn	r0, #0
	b	.L491
.L492:
	ldr	r3, .L495+4
	mov	r0, #0
	ldr	r1, .L495+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L491
.L489:
	ldr	r3, .L495+4
	ldr	r1, .L495+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L491
.L496:
	.align	2
.L495:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+464
	.word	.LC5
	.word	.LC48
	.word	.LC31
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
	ldreq	r1, .L530
	ldreq	r3, .L530+4
	beq	.L522
	ldr	r5, [r3, #4]
	ldr	r8, [r3]
	cmp	r5, #0
	ldr	r6, [r3, #8]
	beq	.L524
	movw	r3, #1208
	ldr	r4, .L530+8
	mul	r3, r3, r6
	ldr	r0, [r4, r3]
	cmp	r0, #0
	beq	.L501
	ldr	r3, .L530+12
	ldr	r2, [r3]
	cmp	r2, #1
	addne	r1, r3, #60
	beq	.L516
.L504:
	ldr	r2, [r3, #4]!
	cmp	r2, #1
	beq	.L516
	cmp	r3, r1
	bne	.L504
	mov	r9, #0
.L502:
	ldr	r7, .L530
	mov	r2, #816
	mov	r1, #0
	mov	r0, r5
	ldr	r3, [r7, #48]
	blx	r3
	movw	r2, #1208
	mla	r2, r2, r6, r4
	ldr	r1, .L530+16
	mov	r3, #180
	mla	r3, r3, r6, r1
	ldr	r2, [r2, #24]
	str	r2, [r5, #4]
	ldr	r3, [r3, #4]
	mov	r3, r3, lsr #17
	and	r2, r3, #3
	cmp	r2, #1
	moveq	r3, #0
	beq	.L505
	eor	r3, r3, #1
	and	r3, r3, #1
	cmp	r8, #3
	orrne	r3, r3, #1
.L505:
	mov	r2, #180
	str	r3, [r5]
	mla	r3, r2, r6, r1
	bics	r8, r8, #16
	ldr	r2, [r3, #4]
	ubfx	r2, r2, #0, #17
	str	r2, [r5, #8]
	beq	.L525
.L506:
	cmp	r2, #200
	bhi	.L526
.L508:
	movw	r3, #1208
	mla	r4, r3, r6, r4
	ldr	r9, [r4, #32]
	mov	r0, r9
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	beq	.L527
	ldr	r8, .L530+20
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
	beq	.L513
.L512:
	ldr	r1, [r0, #4]
	add	r2, r2, #1
	cmp	r2, ip
	add	r0, r0, #16
	add	r3, r3, #4
	strh	r1, [r3, #8]	@ movhi
	ldr	r1, [r0, #-8]
	strh	r1, [r3, #10]	@ movhi
	bne	.L512
.L513:
	mov	r0, #6
	bl	IsDprintTypeEnable
	cmp	r0, #0
	bne	.L528
.L499:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L525:
	cmp	r9, #1
	beq	.L529
	ldr	r1, .L530+24
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L506
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L506
	mov	r3, #1
	strh	r1, [r5, #12]	@ movhi
	mov	r0, r1
	strh	r1, [r5, #14]	@ movhi
	str	r3, [r5, #8]
	b	.L499
.L516:
	mov	r9, r2
	b	.L502
.L528:
	ldr	r3, [r7, #68]
	mov	r0, #6
	ldr	r2, [r5, #8]
	mov	r4, #0
	ldr	r1, .L530+28
	blx	r3
	ldr	r3, [r7, #68]
	mov	r2, r9
	mov	r0, #6
	ldr	r1, .L530+32
	blx	r3
	mov	r3, #3200
	mla	r6, r3, r6, r8
.L514:
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
	ldr	r1, .L530+36
	blx	r8
	ldr	r3, [r5, #8]
	ldr	r2, .L530
	mov	r3, r3, asl #2
	sub	r3, r3, #3
	cmp	r3, r4
	bhi	.L514
	ldr	r3, [r2, #68]
	mov	r0, #6
	ldr	r1, .L530+40
	blx	r3
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L526:
	mov	r3, #200
	ldr	r8, [r7, #68]
	ldr	r1, .L530+44
	mov	r0, #1
	blx	r8
	mov	r3, #0
	str	r3, [r5, #8]
	b	.L508
.L529:
	ldr	r3, [r3, #16]
	ubfx	r3, r3, #21, #2
	cmp	r3, #2
	bne	.L506
	str	r9, [r5, #8]
	mov	r0, r8
	strh	r8, [r5, #12]	@ movhi
	strh	r8, [r5, #14]	@ movhi
	b	.L499
.L524:
	ldr	r1, .L530
	mov	r0, r5
	ldr	r3, .L530+48
.L522:
	ldr	r4, [r1, #68]
	ldr	r2, .L530+52
	ldr	r1, .L530+56
	blx	r4
	mvn	r0, #0
	b	.L499
.L527:
	ldr	r4, [r7, #68]
	ldr	r3, .L530+60
	ldr	r2, .L530+52
	ldr	r1, .L530+56
	blx	r4
	mvn	r0, #0
	b	.L499
.L501:
	ldr	r1, .L530
	ldr	r3, .L530+64
	b	.L522
.L531:
	.align	2
.L530:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC49
	.word	g_HwMem
	.word	g_DSPState
	.word	g_BackUp
	.word	g_UpMsg
	.word	g_not_allow_H264FullPictureRepair_flag
	.word	.LC52
	.word	.LC53
	.word	.LC54
	.word	.LC55
	.word	.LC51
	.word	.LC50
	.word	.LANCHOR0+492
	.word	.LC1
	.word	.LC42
	.word	.LC37
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
	bhi	.L548
	cmp	r3, #0
	bgt	.L549
	movw	r5, #1208
	ldr	r6, .L552
	mul	r5, r5, r3
	add	r9, r5, r6
	ldr	r3, [r5, r6]
	cmp	r3, #0
	beq	.L550
.L537:
	cmp	r2, #0
	bne	.L539
	ldr	r5, .L552+4
	mov	r3, #1744
	mla	r3, r3, r4, r5
	ldr	r1, [r3, #840]
	cmp	r1, #0
	ble	.L540
	cmp	r7, #6
	bne	.L541
	ldr	r1, [r8, #32]
	cmp	r1, #1
	moveq	r2, r1
	str	r2, [r3, #1724]
.L541:
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
.L539:
	cmp	r2, #1
	movne	r0, #0
	beq	.L551
.L535:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L551:
	cmp	r7, #6
	bne	.L543
	ldr	r3, [r8, #32]
	cmp	r3, #1
	bne	.L543
	ldr	r5, .L552+4
	mov	r3, #1744
	mla	r3, r3, r4, r5
	ldr	r2, [r3, #1712]
	cmp	r2, #0
	ble	.L543
	ldr	r2, .L552+8
	mov	r1, #2
	str	r1, [r3, #1724]
	ldr	r3, [r2, #56]
	cmp	r3, #0
	beq	.L544
	mov	r0, r4
	blx	r3
.L545:
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
.L550:
	mov	r0, #0
	str	r2, [fp, #-40]
	movt	r0, 63683
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L538
	str	r3, [r5, r6]
	ldr	r2, [fp, #-40]
	b	.L537
.L549:
	ldr	r1, .L552+12
	mov	r2, #0
	mov	r0, r2
	str	r2, [sp]
	ldr	r2, .L552+16
	ldr	r4, [r1, #68]
	ldr	r1, .L552+20
	blx	r4
	mvn	r0, #0
	b	.L535
.L543:
	ldr	r3, .L552+12
	mov	r0, #0
	ldr	r1, .L552+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L535
.L544:
	ldr	ip, .L552+12
	mov	r0, r3
	movw	r2, #2823
	ldr	r1, .L552+28
	ldr	r3, [ip, #68]
	blx	r3
	b	.L545
.L548:
	ldr	r3, .L552+12
	mov	r0, #0
	ldr	r1, .L552+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L535
.L540:
	ldr	r3, .L552+12
	mov	r0, r2
	ldr	r1, .L552+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L535
.L538:
	ldr	r3, .L552+12
	ldr	r1, .L552+40
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L535
.L553:
	.align	2
.L552:
	.word	g_HwMem
	.word	g_RepairParam
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+524
	.word	.LC5
	.word	.LC59
	.word	.LC10
	.word	.LC56
	.word	.LC58
	.word	.LC57
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
	ble	.L557
	ldr	r5, .L558
	mov	r6, #1
	mov	r3, r4
	ldr	r2, .L558+4
	str	r6, [sp]
	mov	r0, #32
	ldr	r7, [r5, #68]
	ldr	r1, .L558+8
	blx	r7
	movw	r0, #49156
	movt	r0, 63683
	bl	MEM_ReadPhyWord
	ldr	r3, .L558+12
	ldr	r3, [r3]
	uxth	r1, r0
	add	r0, r3, #4
	bl	MEM_WritePhyWord
	str	r6, [sp]
	mov	r3, r4
	ldr	r7, [r5, #68]
	ldr	r2, .L558+4
	mov	r0, #32
	ldr	r1, .L558+16
	blx	r7
	ldr	r3, [r5, #116]
	blx	r3
	str	r6, [sp]
	mov	r3, r4
	ldr	r7, [r5, #68]
	ldr	r2, .L558+4
	mov	r0, #32
	ldr	r1, .L558+16
	blx	r7
	str	r6, [sp]
	mov	r3, r4
	ldr	r7, [r5, #68]
	ldr	r2, .L558+4
	mov	r0, #32
	ldr	r1, .L558+16
	blx	r7
	str	r6, [sp]
	mov	r3, r4
	ldr	r5, [r5, #68]
	ldr	r2, .L558+4
	mov	r0, #32
	ldr	r1, .L558+16
	blx	r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L557:
	movw	r3, #1208
	ldr	r5, .L558+20
	mul	r4, r3, r4
	movw	r0, #49156
	movt	r0, 63683
	ldr	r3, [r5, r4]
	ldr	r6, [r3, #8]
	bl	MEM_ReadPhyWord
	ldr	r3, .L558+12
	orr	r6, r6, #67108864
	ldr	r3, [r3]
	uxth	r1, r0
	add	r0, r3, #4
	bl	MEM_WritePhyWord
	ldr	r2, [r5, r4]
	ldr	r3, .L558
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
.L559:
	.align	2
.L558:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+556
	.word	.LC38
	.word	s_RegPhyBaseAddr
	.word	.LC60
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
	ldr	r9, .L589
	ldr	r4, [r9, #64]
	cmp	r4, #0
	blt	.L583
	movw	r10, #56367
	add	r6, r9, #64
	add	r9, r9, #124
	movt	r10, 1315
	mov	r8, #30
	mov	r7, #0
.L562:
	mov	r0, r4
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L565
	ldr	r3, .L589+4
	mov	r0, r4
	ldr	r2, .L589+8
	ldr	r3, [r3, r4, asl #2]
	ldr	ip, [r2, r4, asl #2]
	ldr	r1, [r3, #64]
	ldr	r2, [r3, #68]
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
	b	.L565
.L568:
	.word	.L577
	.word	.L577
	.word	.L577
	.word	.L577
	.word	.L565
	.word	.L577
	.word	.L577
	.word	.L565
	.word	.L577
	.word	.L577
	.word	.L577
	.word	.L577
	.word	.L577
	.word	.L577
	.word	.L565
	.word	.L565
	.word	.L578
	.word	.L577
.L577:
	mul	r4, r5, r4
	mul	r2, r8, r4
	ubfx	r2, r2, #1, #26
	umull	r2, r3, r2, r10
	add	r7, r7, r3, lsr #7
.L565:
	cmp	r6, r9
	beq	.L581
	ldr	r4, [r6, #4]!
	cmp	r4, #0
	bge	.L562
.L581:
	rsb	r7, r7, #32
	cmp	r7, #25
	movge	r7, #25
	cmp	r7, #0
	andgt	r7, r7, #31
	ble	.L588
.L561:
	ldr	r3, .L589+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfi	r3, r7, #12, #5
.L586:
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L578:
	mul	r4, r5, r4
	mul	r2, r8, r4
	bic	r2, r2, #-67108864
	umull	r2, r3, r2, r10
	add	r7, r7, r3, lsr #7
	b	.L565
.L588:
	ldr	r3, .L589+12
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	b	.L586
.L583:
	mov	r7, #25
	b	.L561
.L590:
	.align	2
.L589:
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
	bgt	.L614
	mov	r7, r4, asl #3
	mov	r6, r4, asl #6
	ldr	r5, .L616
	rsb	r3, r7, r6
	ldr	r8, .L616+4
	add	r3, r5, r3
	ldr	r10, .L616+8
	ldr	r2, [r3, #12]
	ldr	r1, [r8]
	cmp	r2, #0
	ldr	r2, [r3, #8]
	ldr	r3, [r1, #120]
	beq	.L615
.L594:
	bfc	r3, #8, #2
.L595:
	ldr	r9, .L616+12
	mov	r0, #30
	str	r3, [r1, #120]
	ldr	r3, [r9, #120]
	blx	r3
	rsb	r3, r7, r6
	add	r3, r5, r3
	ldr	r1, [r3, #8]
	ldr	r3, [r10, r1, asl #2]
	ldr	r2, [r3, #1232]
	cmp	r2, #1
	beq	.L596
	ldr	r3, [r3, #1220]
	bics	r3, r3, #1024
	beq	.L597
.L596:
	ldr	r2, [r8]
	ldr	r3, [r2, #120]
	bfc	r3, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	ldr	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
.L598:
	ldr	r3, [r10, r1, asl #2]
	ldr	r3, [r3, #528]
	cmp	r3, #17
	moveq	r1, #0
	movne	r1, #3
	cmp	r4, #0
	beq	.L601
	cmp	r4, #1
	beq	.L602
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L616+16
	blx	r3
.L603:
	ldr	r3, [r9, #116]
	blx	r3
	movw	r3, #1208
	mul	r3, r3, r4
	ldr	r2, .L616+20
	mov	r1, #0
	ldr	r3, [r2, r3]
	str	r1, [r3]
.L604:
	movw	r3, #1208
	rsb	r6, r7, r6
	mul	r4, r3, r4
	mov	lr, #1
	add	r5, r5, r6
	mov	r0, #0
	ldr	r3, .L616+24
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
.L615:
	ldr	r2, [r10, r2, asl #2]
	movw	r0, #8160
	add	r2, r2, #204800
	ldr	r9, [r2, #1536]
	ldr	lr, [r2, #1540]
	adds	ip, r9, #15
	addmi	ip, r9, #30
	adds	r2, lr, #15
	addmi	r2, lr, #30
	mov	ip, ip, asr #4
	mov	r2, r2, asr #4
	mul	r2, r2, ip
	cmp	r2, r0
	orrgt	r3, r3, #768
	bgt	.L595
	b	.L594
.L614:
	ldr	r1, .L616+12
	mov	r3, r4
	mov	r0, #0
	ldr	r2, .L616+28
	str	r0, [sp]
	ldr	r4, [r1, #68]
	ldr	r1, .L616+32
	blx	r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L602:
	ldr	r3, .L616+36
	ldr	r0, [r3]
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r3, [r9, #116]
	blx	r3
	str	r4, [sp]
	ldr	r2, .L616+28
	mov	r3, r4
	ldr	r8, [r9, #68]
	mov	r0, #32
	ldr	r1, .L616+40
	blx	r8
	ldr	r2, .L616+20
	b	.L604
.L601:
	ldr	r3, .L616+44
	ldr	r0, [r3]
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	b	.L603
.L597:
	mov	r0, r4
	str	r1, [fp, #-48]
	bl	VDMHAL_V300R001_SetVdhClkSkip
	ldr	r1, [fp, #-48]
	b	.L598
.L617:
	.align	2
.L616:
	.word	g_VdmDrvParam
	.word	g_pstRegCrg
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC61
	.word	g_HwMem
	.word	g_LowDelaySeqIndex
	.word	.LANCHOR0+588
	.word	.LC5
	.word	s_RegPhyBaseAddr_1
	.word	.LC60
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
	ldr	r1, .L619
	mov	r0, #15
	ldr	r3, .L619+4
	mov	r2, #4
	str	r0, [r1]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L620:
	.align	2
.L619:
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
	beq	.L622
	cmp	r3, #2
	moveq	r4, #1
	movne	r4, #2
.L622:
	ldr	r3, [fp, #-92]
	cmp	r3, #0
	beq	.L621
	mov	r3, #0
	mov	r2, #4194304
	mov	r1, r3
	str	r3, [sp]
	ldr	r0, .L715
	sub	r3, fp, #76
	bl	MEM_AllocMemBlock
	subs	r1, r0, #0
	beq	.L711
.L708:
	ldr	r3, .L715+4
	mov	r0, #1
	ldr	r1, .L715+8
	ldr	r3, [r3, #68]
	blx	r3
.L621:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L711:
	str	r1, [sp]
	mov	r2, #4194304
	sub	r3, fp, #60
	ldr	r0, .L715+12
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L708
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
	bne	.L627
	ldr	r3, [fp, #-84]
	cmp	r3, #0
	movne	r10, r0
	ldrne	r7, .L715+4
	strne	r10, [fp, #-80]
	beq	.L712
.L628:
	cmp	r5, #0
	beq	.L632
	ldr	r2, [fp, #-80]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	ldr	r2, [fp, #-88]
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L630:
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
	bhi	.L630
.L632:
	ldr	r3, [fp, #-80]
	add	r10, r10, r5
	ldr	r2, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-80]
	cmp	r2, r3
	bne	.L628
	ldr	r4, [fp, #-84]
	mov	r0, r6
	ldr	r3, [r7, #44]
	ldr	r2, [fp, #-92]
	mul	r1, r4, r5
	blx	r3
	movs	r3, r4, lsr #1
	str	r3, [fp, #-84]
	beq	.L664
	ldr	r3, [fp, #-88]
	mov	r9, #0
	ldr	r10, [fp, #-112]
	str	r9, [fp, #-80]
	mov	r3, r3, asr #1
	str	r3, [fp, #-88]
.L634:
	cmp	r5, #0
	beq	.L636
	ldr	r2, [fp, #-80]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-88]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L635:
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
	bhi	.L635
.L636:
	ldr	r3, [fp, #-80]
	add	r9, r9, r5
	ldr	r2, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-80]
	cmp	r3, r2
	bne	.L634
.L664:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L713
	ldr	r3, [fp, #4]
	cmp	r3, #0
	beq	.L661
.L656:
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
.L627:
	subs	r3, r4, #1
	ldr	r2, [fp, #-84]
	ldr	r7, .L715+4
	movne	r3, #1
	cmp	r2, r3
	str	r3, [fp, #-116]
	ldrhi	r3, [fp, #-116]
	strhi	r3, [fp, #-80]
	bls	.L646
.L648:
	cmp	r5, #0
	beq	.L649
	ldr	r2, [fp, #-80]
	mov	r4, #0
	and	r9, r2, #15
	mov	r3, r2, lsr #4
	mov	r10, r2, lsr #1
	ldr	r2, [fp, #-88]
	mul	r10, r5, r10
	mul	r3, r2, r3
	add	r9, r3, r9, lsl #8
.L647:
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
	bhi	.L647
.L649:
	ldr	r3, [fp, #-80]
	ldr	r2, [fp, #-84]
	add	r3, r3, #2
	str	r3, [fp, #-80]
	cmp	r2, r3
	bhi	.L648
.L646:
	ldr	r4, [fp, #-84]
	mov	r0, r6
	ldr	r3, [r7, #44]
	ldr	r2, [fp, #-92]
	mul	r1, r4, r5
	mov	r1, r1, lsr #1
	blx	r3
	movs	r3, r4, lsr #1
	str	r3, [fp, #-84]
	beq	.L650
	ldr	r3, [fp, #-88]
	mov	r9, #0
	ldr	r10, [fp, #-112]
	str	r9, [fp, #-80]
	mov	r3, r3, asr #1
	str	r3, [fp, #-88]
.L651:
	cmp	r5, #0
	beq	.L653
	ldr	r2, [fp, #-80]
	mov	r4, #0
	and	r8, r2, #7
	mov	r3, r2, lsr #3
	ldr	r2, [fp, #-88]
	mul	r3, r2, r3
	add	r8, r3, r8, lsl #8
.L652:
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
	bhi	.L652
.L653:
	ldr	r3, [fp, #-80]
	add	r9, r9, r5
	ldr	r2, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-80]
	cmp	r3, r2
	bne	.L651
.L650:
	ldr	r3, [fp, #4]
	cmp	r3, #1
	beq	.L714
	ldr	r3, [fp, #4]
	cmp	r3, #0
	bne	.L656
	ldr	r2, [fp, #-100]
	ldr	r3, [fp, #-116]
	cmp	r2, r3
	bls	.L661
.L662:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L662
.L661:
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
	b	.L656
.L714:
	ldr	r3, [fp, #-100]
	cmp	r3, #0
	beq	.L656
	ldr	r2, [fp, #-116]
	mov	lr, #0
	ldr	r0, [fp, #-104]
	ldr	ip, [fp, #-96]
	mla	r4, r5, r2, r6
	mov	r5, r5, asl #1
	mov	r6, r3
	add	r4, r4, #1
.L657:
	cmp	r0, #0
	beq	.L660
	mov	r3, lr, lsr #1
	mov	r2, r4
	mul	r3, r0, r3
	sub	r1, r3, #-67108863
	add	r9, r3, r0
	sub	r1, r1, #65011712
	add	r9, ip, r9
	add	r1, ip, r1
	add	r3, ip, r3
.L658:
	ldrb	r8, [r2, #-1]	@ zero_extendqisi2
	strb	r8, [r1, #1]!
	ldrb	r8, [r2], #2	@ zero_extendqisi2
	strb	r8, [r3], #1
	cmp	r3, r9
	bne	.L658
.L660:
	add	lr, lr, #2
	add	r4, r4, r5
	cmp	r6, lr
	bhi	.L657
	b	.L656
.L713:
	ldr	r8, [fp, #-100]
	cmp	r8, #0
	beq	.L656
	ldr	r3, [fp, #-96]
	add	r6, r6, #1
	ldr	r4, [fp, #-104]
	mov	lr, #0
.L640:
	cmp	r4, #0
	moveq	ip, r3
	beq	.L643
	sub	r1, r3, #-67108863
	add	ip, r3, r4
	sub	r1, r1, #65011712
	mov	r2, r6
.L641:
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	strb	r0, [r1, #1]!
	ldrb	r0, [r2], #2	@ zero_extendqisi2
	strb	r0, [r3], #1
	cmp	ip, r3
	bne	.L641
.L643:
	add	lr, lr, #1
	mov	r3, ip
	cmp	lr, r8
	add	r6, r6, r5
	bne	.L640
	b	.L656
.L712:
	ldr	r7, .L715+4
	mov	r0, r6
	ldr	r1, [fp, #-84]
	ldr	r2, [fp, #-92]
	ldr	r3, [r7, #44]
	blx	r3
	b	.L664
.L716:
	.align	2
.L715:
	.word	.LC62
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC63
	.word	.LC64
	UNWIND(.fnend)
	.size	VDMHAL_V300R001_WriteBigTitle1DYuv, .-VDMHAL_V300R001_WriteBigTitle1DYuv
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.27672, %object
	.size	__func__.27672, 24
__func__.27672:
	.ascii	"VDMHAL_V300R001_OpenHAL\000"
	.type	__func__.27708, %object
	.size	__func__.27708, 27
__func__.27708:
	.ascii	"VDMHAL_V300R001_CalcFsSize\000"
	.space	1
	.type	__func__.27721, %object
	.size	__func__.27721, 34
__func__.27721:
	.ascii	"VDMHAL_V300R001_FillVdmMemElement\000"
	.space	2
	.type	__func__.27766, %object
	.size	__func__.27766, 27
__func__.27766:
	.ascii	"VDMHAL_V300R001_ArrangeMem\000"
	.space	1
	.type	__FUNCTION__.27725, %object
	.size	__FUNCTION__.27725, 34
__FUNCTION__.27725:
	.ascii	"VDMHAL_V300R001_FillVdmMemElement\000"
	.space	2
	.type	__func__.27806, %object
	.size	__func__.27806, 31
__func__.27806:
	.ascii	"VDMHAL_V300R001_ArrangeMem_BTL\000"
	.space	1
	.type	__func__.27827, %object
	.size	__func__.27827, 25
__func__.27827:
	.ascii	"VDMHAL_V300R001_ResetVdm\000"
	.space	3
	.type	__func__.27854, %object
	.size	__func__.27854, 30
__func__.27854:
	.ascii	"VDMHAL_V300R001_ClearIntState\000"
	.space	2
	.type	__func__.27864, %object
	.size	__func__.27864, 24
__func__.27864:
	.ascii	"VDMHAL_V300R001_MaskInt\000"
	.type	__func__.27876, %object
	.size	__func__.27876, 26
__func__.27876:
	.ascii	"VDMHAL_V300R001_EnableInt\000"
	.space	2
	.type	__func__.27885, %object
	.size	__func__.27885, 25
__func__.27885:
	.ascii	"VDMHAL_V300R001_CheckReg\000"
	.space	3
	.type	__func__.27902, %object
	.size	__func__.27902, 27
__func__.27902:
	.ascii	"VDMHAL_V300R001_PrepareDec\000"
	.space	1
	.type	__func__.27923, %object
	.size	__func__.27923, 27
__func__.27923:
	.ascii	"VDMHAL_V300R001_IsVdmReady\000"
	.space	1
	.type	__func__.27928, %object
	.size	__func__.27928, 25
__func__.27928:
	.ascii	"VDMHAL_V300R001_IsVdmRun\000"
	.space	3
	.type	__func__.27942, %object
	.size	__func__.27942, 27
__func__.27942:
	.ascii	"VDMHAL_V300R001_BackupInfo\000"
	.space	1
	.type	__func__.27982, %object
	.size	__func__.27982, 25
__func__.27982:
	.ascii	"VDMHAL_V300R001_CfgRpMsg\000"
	.space	3
	.type	__func__.28003, %object
	.size	__func__.28003, 25
__func__.28003:
	.ascii	"VDMHAL_V300R001_CfgRpReg\000"
	.space	3
	.type	__func__.28016, %object
	.size	__func__.28016, 30
__func__.28016:
	.ascii	"VDMHAL_V300R001_MakeDecReport\000"
	.space	2
	.type	__func__.28041, %object
	.size	__func__.28041, 30
__func__.28041:
	.ascii	"VDMHAL_V300R001_PrepareRepair\000"
	.space	2
	.type	__func__.28049, %object
	.size	__func__.28049, 30
__func__.28049:
	.ascii	"VDMHAL_V300R001_StartHwRepair\000"
	.space	2
	.type	__func__.28095, %object
	.size	__func__.28095, 30
__func__.28095:
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
	ASCII(.ascii	"DFS, report event. Size: %#x, Num: %#x, RefChanged:" )
	ASCII(.ascii	" %#x\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"pVdmMemArrange is NULL\000" )
	.space	1
.LC15:
	ASCII(.ascii	"DFS, no ref frame!\012\000" )
.LC16:
	ASCII(.ascii	"DFS, Frame number = %d > 30, Then, Frame num = 30, " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"VDMHAL_V300R001_ArrangeMem Mem addr is NULL\000" )
.LC18:
	ASCII(.ascii	"'pVdmMemArrange' is NULL\000" )
	.space	3
.LC19:
	ASCII(.ascii	"MemSize not enough for pmv slot\000" )
.LC20:
	ASCII(.ascii	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight" )
	ASCII(.ascii	" failed!\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"ImgSlotLen > ChanSlotLen\000" )
	.space	3
.LC22:
	ASCII(.ascii	"cann't allocate img slot\000" )
	.space	3
.LC23:
	ASCII(.ascii	"%s, FrameStore %d over bountry, Offset: 0x%x, curFs" )
	ASCII(.ascii	"Size: 0x%x, phyadd: 0x%x\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"Mem addr is 0\000" )
	.space	2
.LC25:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300R001_ResetVdm\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"VDMHAL_V300R001_ResetVdm: map vdm register fail, vi" )
	ASCII(.ascii	"r(reg) = (%p)\012\000" )
	.space	2
.LC27:
	ASCII(.ascii	"VDH: %d VDMHAL_V300R001_ResetVdm ERROR!!!\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"Ignore the reset request when the VDH clock is clos" )
	ASCII(.ascii	"ed.\012\000" )
.LC29:
	ASCII(.ascii	"GLB Reset failed!\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V200R003_ClearIntState\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC32:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V200_MaskInt\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V200R003_EnableInt\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"%s: VdhId(%d) Invalid!\012\000" )
.LC35:
	ASCII(.ascii	"%s: vdm register virtual address not mapped, reset " )
	ASCII(.ascii	"failed!\012\000" )
.LC36:
	ASCII(.ascii	"%s: unkown reg_id = %d\012\000" )
.LC37:
	ASCII(.ascii	"VDM register not mapped yet!\000" )
	.space	3
.LC38:
	ASCII(.ascii	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"VDM register not mapped yet!\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"pBackUpInfo = NULL!\000" )
.LC41:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300R001_BackupInfo\012\000" )
.LC42:
	ASCII(.ascii	"can NOT map vir addr for up-msg\000" )
.LC43:
	ASCII(.ascii	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\012\000" )
	.space	1
.LC44:
	ASCII(.ascii	"ReadUpMsgSlot error! upmsg_size(%d) > 512\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"can not map repair msg virtual address!\000" )
.LC46:
	ASCII(.ascii	"ValidGroupNum=%d out of range!\012\000" )
.LC47:
	ASCII(.ascii	"align_mb error\012\000" )
.LC48:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300_CfgRpReg\012\000" )
	.space	2
.LC49:
	ASCII(.ascii	"'pMakeDecReport' is NULL\000" )
	.space	3
.LC50:
	ASCII(.ascii	"'pDecReport' is NULL\000" )
	.space	3
.LC51:
	ASCII(.ascii	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full" )
	ASCII(.ascii	" repair.\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"\012***** UpMsg DecSliceNum=%d\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"\012***** Up Msg (phy addr: %#8x) *****\012\000" )
	.space	2
.LC54:
	ASCII(.ascii	"\0120x%02x 0x%08x 0x%08x 0x%08x 0x%08x\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"\012***** Up Msg print finished *****\012\000" )
.LC56:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V200R003_PrepareRepair\012\000" )
	.space	1
.LC57:
	ASCII(.ascii	"vdm register virtual address not mapped, VDMHAL_V20" )
	ASCII(.ascii	"0R003_PrepareRepair failed!\012\000" )
.LC58:
	ASCII(.ascii	"FIRST_REPAIR Parameter Error!\012\000" )
	.space	1
.LC59:
	ASCII(.ascii	"SECOND_REPAIR Parameter Error!\012\000" )
.LC60:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"VdhId is wrong! VDMHAL_V300R001_StartHwDecode\012\000" )
	.space	1
.LC62:
	ASCII(.ascii	"BigTile1d_y\000" )
.LC63:
	ASCII(.ascii	"failed mem_allocMemBlock BigTile_yuv save!\012\000" )
.LC64:
	ASCII(.ascii	"BigTile1d_uv\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
