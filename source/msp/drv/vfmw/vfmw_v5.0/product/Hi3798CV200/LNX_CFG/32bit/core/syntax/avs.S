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
	.file	"avs.c"
	.text
	.align	2
	.global	avs_u_v
	.type	avs_u_v, %function
avs_u_v:
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
	mov	r6, r1
	mov	r5, r2
	bl	BsGet
	str	r6, [sp]
	mov	r2, r5
	ldr	r1, .L2
	mov	r4, r0
	mov	r3, r0
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	.LC0
	UNWIND(.fnend)
	.size	avs_u_v, .-avs_u_v
	.align	2
	.global	avs_f_v
	.type	avs_f_v, %function
avs_f_v:
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
	mov	r6, r1
	mov	r5, r2
	bl	BsGet
	str	r6, [sp]
	mov	r2, r5
	ldr	r1, .L5
	mov	r4, r0
	mov	r3, r0
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	.LC0
	UNWIND(.fnend)
	.size	avs_f_v, .-avs_f_v
	.align	2
	.global	avs_ue_v
	.type	avs_ue_v, %function
avs_ue_v:
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
	mov	r6, r1
	mov	r1, #32
	mov	r7, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	mov	r4, r0
	mvnhi	r5, #0
	movhi	r4, #32
	bls	.L11
.L8:
	str	r4, [sp]
	mov	r2, r6
	mov	r3, r5
	ldr	r1, .L12
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L11:
	add	r5, r4, #1
	mov	r1, r4
	mov	r0, r7
	mov	r4, r4, asl #1
	bl	BsSkip
	mov	r1, r5
	mov	r0, r7
	add	r4, r4, #1
	bl	BsShow
	mov	r1, r5
	sub	r5, r0, #1
	mov	r0, r7
	bl	BsSkip
	b	.L8
.L13:
	.align	2
.L12:
	.word	.LC0
	UNWIND(.fnend)
	.size	avs_ue_v, .-avs_ue_v
	.align	2
	.global	avs_se_v
	.type	avs_se_v, %function
avs_se_v:
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
	mov	r6, r1
	mov	r1, #32
	mov	r7, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	mov	r4, r0
	mvnhi	r5, #-2147483648
	movhi	r4, #32
	bls	.L19
.L15:
	str	r4, [sp]
	mov	r2, r6
	mov	r3, r5
	ldr	r1, .L20
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L19:
	add	r8, r4, #1
	mov	r1, r4
	mov	r0, r7
	mov	r4, r4, asl #1
	bl	BsSkip
	mov	r1, r8
	mov	r0, r7
	add	r4, r4, #1
	bl	BsShow
	mov	r1, r8
	sub	r0, r0, #1
	tst	r0, #1
	mov	r0, r0, asr #1
	addne	r5, r0, #1
	rsbeq	r5, r0, #0
	mov	r0, r7
	bl	BsSkip
	b	.L15
.L21:
	.align	2
.L20:
	.word	.LC0
	UNWIND(.fnend)
	.size	avs_se_v, .-avs_se_v
	.align	2
	.global	AVS_next_start_code
	.type	AVS_next_start_code, %function
AVS_next_start_code:
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
	bgt	.L25
	b	.L26
.L31:
	bl	BsSkip
	cmp	r4, r6
	beq	.L26
.L25:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L31
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L26:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_next_start_code, .-AVS_next_start_code
	.align	2
	.global	AVS_sequence_header
	.type	AVS_sequence_header, %function
AVS_sequence_header:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	add	r6, r0, #12288
	mov	r4, r1
	ldr	r2, .L42
	ldr	r5, [r6, #3176]
	mov	r1, #32
	ldr	r3, [r6, #2784]
	mov	r7, r0
	bic	r3, r3, #65536
	mov	r0, r5
	str	r3, [r6, #2784]
	bl	avs_f_v
	ldr	r2, .L42+4
	mov	r1, #8
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+8
	mov	r1, #8
	str	r0, [r4, #16]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+12
	mov	r1, #1
	str	r0, [r4, #20]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+16
	mov	r1, #14
	strb	r0, [r4, #15]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+20
	mov	r1, #14
	str	r0, [r4, #24]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+24
	mov	r1, #2
	str	r0, [r4, #28]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+28
	mov	r1, #3
	strb	r0, [r4, #11]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+32
	mov	r1, #4
	strb	r0, [r4, #12]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+36
	mov	r1, #4
	strb	r0, [r4, #13]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+40
	mov	r1, #18
	strb	r0, [r4, #14]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+44
	mov	r1, #1
	str	r0, [r4, #32]
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L42+48
	mov	r1, #12
	strb	r0, [r4, #10]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+52
	mov	r1, #1
	str	r0, [r4, #36]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+44
	mov	r1, #1
	strb	r0, [r4, #9]
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L42+56
	mov	r1, #18
	strb	r0, [r4, #10]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+60
	mov	r1, #3
	str	r0, [r4, #40]
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #14]	@ zero_extendqisi2
	cmp	r3, #15
	ldrls	r2, .L42+64
	mvnhi	r3, #0
	ldrls	r3, [r2, r3, asl #2]
	strb	r0, [r4, #8]
	str	r3, [r4, #44]
	ldr	r3, [r4, #24]
	ldr	r2, [r6, #2824]
	cmp	r3, r2
	beq	.L41
.L35:
	ldr	r3, .L42+68
	mov	r1, #1
	str	r1, [r6, #2796]
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L36
	ldr	r1, [r4, #24]
	mov	r3, #8
	ldr	lr, [r6, #2828]
	ldr	ip, [r4, #28]
	strh	r2, [fp, #-36]	@ movhi
	sub	r2, fp, #36
	strh	r1, [fp, #-32]	@ movhi
	mov	r1, #2
	ldr	r0, [r7, #4]
	strh	lr, [fp, #-34]	@ movhi
	strh	ip, [fp, #-30]	@ movhi
	blx	r5
.L36:
	mov	r1, r4
	mov	r2, #376
	add	r0, r6, #2800
	bl	memcpy
	ldr	r2, [r6, #2792]
	ldr	r3, [r6, #2784]
	mov	r0, #1
	add	r2, r2, r0
	str	r0, [r6, #2788]
	orr	r3, r3, #65536
	str	r2, [r6, #2792]
	str	r3, [r6, #2784]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L41:
	ldr	r1, [r4, #28]
	ldr	r3, [r6, #2828]
	cmp	r1, r3
	bne	.L35
	b	.L36
.L43:
	.align	2
.L42:
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LANCHOR0
	.word	g_event_report
	UNWIND(.fnend)
	.size	AVS_sequence_header, .-AVS_sequence_header
	.align	2
	.global	AVS_i_picture_header
	.type	AVS_i_picture_header, %function
AVS_i_picture_header:
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
	ldr	r3, .L83
	mov	r6, r0
	ldr	r5, [r0, #544]
	mov	r4, r1
	add	r0, r1, #80
	mov	r2, #272
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r6, #152]
	ldr	r2, .L83+4
	mov	r1, #32
	bic	r3, r3, #262144
	mov	r0, r5
	str	r3, [r6, #152]
	bl	avs_f_v
	mov	r0, r5
	ldr	r2, .L83+8
	mov	r1, #16
	bl	avs_u_v
	ldr	r3, [r4, #16]
	cmp	r3, #72
	str	r0, [r4, #96]
	beq	.L75
.L45:
	ldr	r2, .L83+12
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #90]
	cmp	r0, #1
	beq	.L76
.L46:
	ldr	r2, .L83+16
	mov	r1, #1
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L83+20
	mov	r1, #8
	str	r0, [r4, #108]
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	cmp	r3, #1
	str	r0, [r4, #112]
	beq	.L77
.L47:
	ldr	r2, .L83+24
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #1
	uxtb	r0, r0
	strb	r0, [r4, #80]
	streqb	r3, [r4, #80]
	beq	.L49
	cmp	r0, #0
	beq	.L78
.L49:
	mov	r3, #1
	strb	r3, [r4, #81]
.L50:
	ldr	r2, .L83+28
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+32
	mov	r1, #1
	strb	r0, [r4, #82]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+36
	mov	r1, #1
	strb	r0, [r4, #83]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+40
	mov	r1, #6
	strb	r0, [r4, #84]
	mov	r0, r5
	bl	avs_u_v
	ldrh	r3, [r4, #80]
	cmp	r3, #0
	strb	r0, [r4, #85]
	beq	.L79
.L51:
	ldr	r2, .L83+44
	mov	r1, #4
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+48
	mov	r1, #1
	strb	r0, [r4, #87]
	mov	r0, r5
	bl	avs_u_v
	mov	r3, #0
	str	r3, [r4, #120]
	str	r3, [r4, #124]
	uxtb	r0, r0
	strb	r0, [r4, #88]
	cmp	r0, r3
	beq	.L80
.L53:
	ldr	r3, [r4, #16]
	cmp	r3, #72
	beq	.L81
.L55:
	mov	r0, #1
	mov	r3, #0
	strb	r0, [r4, #93]
	str	r3, [r4, #348]
	ldr	r3, [r6, #152]
	orr	r3, r3, #262144
	str	r3, [r6, #152]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L78:
	ldr	r2, .L83+52
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	strb	r0, [r4, #81]
	b	.L50
.L80:
	ldr	r2, .L83+56
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #89]
	cmp	r0, #0
	beq	.L53
	ldr	r1, .L83+60
	mov	r0, r5
	bl	avs_se_v
	ldr	r1, .L83+64
	str	r0, [r4, #120]
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r4, #124]
	b	.L53
.L79:
	ldr	r2, .L83+68
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	strb	r0, [r4, #86]
	b	.L51
.L81:
	ldr	r2, .L83+72
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	cmp	r0, #0
	str	r0, [r4, #128]
	bne	.L56
.L65:
	mov	r0, r5
	ldr	r2, .L83+76
	mov	r1, #1
	bl	avs_u_v
	str	r0, [r4, #332]
	b	.L55
.L75:
	ldr	r2, .L83+16
	mov	r1, #1
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L83+80
	mov	r1, #7
	str	r0, [r4, #108]
	mov	r0, r5
	bl	avs_u_v
	ldr	r3, [r4, #96]
	mov	r2, #1
	strb	r2, [r4]
	str	r0, [r4, #100]
	orr	r0, r0, r3, asl #7
	str	r0, [r4, #96]
	b	.L45
.L76:
	ldr	r2, .L83+84
	mov	r1, #24
	mov	r0, r5
	bl	avs_u_v
	str	r0, [r4, #104]
	b	.L46
.L77:
	ldr	r1, .L83+88
	mov	r0, r5
	bl	avs_ue_v
	str	r0, [r4, #116]
	b	.L47
.L56:
	ldr	r2, .L83+92
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+96
	mov	r1, #1
	str	r0, [r4, #132]
	mov	r0, r5
	bl	avs_u_v
	cmp	r0, #0
	str	r0, [r4, #136]
	beq	.L82
.L57:
	ldr	r2, .L83+100
	mov	r1, #2
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+104
	mov	r1, #2
	str	r0, [r4, #148]
	mov	r0, r5
	bl	avs_u_v
	ldr	r3, [r4, #148]
	cmp	r3, #1
	str	r0, [r4, #152]
	beq	.L60
	ldr	r2, [r4, #132]
	cmp	r2, #0
	cmpeq	r3, #3
	beq	.L60
	cmp	r3, #2
	addeq	r7, r4, #176
	bne	.L65
.L64:
	add	r8, r4, #200
.L63:
	ldr	r1, .L83+108
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r7, #4]!
	cmp	r7, r8
	bne	.L63
	b	.L65
.L82:
	ldr	r1, .L83+112
	mov	r0, r5
	bl	avs_se_v
	ldr	r1, .L83+116
	str	r0, [r4, #140]
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r4, #144]
	b	.L57
.L60:
	add	r8, r4, #152
	add	r7, r4, #176
.L59:
	ldr	r1, .L83+120
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r8, #4]!
	cmp	r8, r7
	bne	.L59
	ldr	r3, [r4, #148]
	cmp	r3, #2
	beq	.L64
	ldr	r2, [r4, #132]
	cmp	r2, #0
	cmpeq	r3, #3
	bne	.L65
	b	.L64
.L84:
	.align	2
.L83:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC17
	.word	.LC18
	.word	.LC20
	.word	.LC12
	.word	.LC22
	.word	.LC24
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC16
	.word	.LC31
	.word	.LC25
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC30
	.word	.LC35
	.word	.LC36
	.word	.LC19
	.word	.LC21
	.word	.LC23
	.word	.LC37
	.word	.LC38
	.word	.LC41
	.word	.LC42
	.word	.LC44
	.word	.LC39
	.word	.LC40
	.word	.LC43
	UNWIND(.fnend)
	.size	AVS_i_picture_header, .-AVS_i_picture_header
	.align	2
	.global	AVS_pb_picture_header
	.type	AVS_pb_picture_header, %function
AVS_pb_picture_header:
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
	ldr	r3, .L137
	mov	r6, r0
	ldr	r5, [r0, #544]
	mov	r4, r1
	add	r0, r1, #80
	mov	r2, #272
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r6, #152]
	ldr	r2, .L137+4
	mov	r1, #32
	bic	r3, r3, #262144
	mov	r0, r5
	str	r3, [r6, #152]
	bl	avs_f_v
	mov	r0, r5
	ldr	r2, .L137+8
	mov	r1, #16
	bl	avs_u_v
	ldr	r3, [r4, #16]
	cmp	r3, #72
	str	r0, [r4, #96]
	beq	.L129
.L86:
	ldr	r2, .L137+12
	mov	r1, #2
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+16
	mov	r1, #8
	strb	r0, [r4, #91]
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	cmp	r3, #1
	str	r0, [r4, #112]
	beq	.L130
.L87:
	ldr	r2, .L137+20
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #80]
	cmp	r0, #0
	movne	r3, #1
	strneb	r3, [r4, #81]
	beq	.L131
.L89:
	ldr	r2, .L137+24
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+28
	mov	r1, #1
	strb	r0, [r4, #82]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+32
	mov	r1, #1
	strb	r0, [r4, #83]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+36
	mov	r1, #6
	strb	r0, [r4, #84]
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #91]	@ zero_extendqisi2
	cmp	r3, #2
	strb	r0, [r4, #85]
	beq	.L132
.L90:
	ldr	r2, .L137+40
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	strb	r0, [r4, #93]
.L92:
	ldr	r2, .L137+44
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldrb	r2, [r4, #91]	@ zero_extendqisi2
	mov	r3, #0
	str	r3, [r4, #340]
	cmp	r2, #2
	str	r3, [r4, #344]
	strb	r0, [r4, #94]
	beq	.L133
	ldr	r2, .L137+48
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	str	r0, [r4, #340]
.L94:
	ldrb	r3, [r4, #81]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L95
	ldr	r3, [r4, #16]
	cmp	r3, #72
	beq	.L96
.L95:
	mov	r3, #0
	str	r3, [r4, #340]
	str	r3, [r4, #344]
.L96:
	ldr	r2, .L137+52
	mov	r1, #2
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+56
	mov	r1, #1
	strb	r0, [r4, #87]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+60
	mov	r1, #1
	strb	r0, [r4, #86]
	mov	r0, r5
	bl	avs_u_v
	mov	r3, #0
	str	r3, [r4, #120]
	str	r3, [r4, #124]
	uxtb	r0, r0
	strb	r0, [r4, #88]
	cmp	r0, r3
	beq	.L134
.L98:
	ldr	r3, [r4, #16]
	cmp	r3, #72
	beq	.L135
.L100:
	ldrb	r3, [r4, #91]	@ zero_extendqisi2
	mov	r0, #1
	cmp	r3, #1
	movne	r3, #2
	str	r3, [r4, #348]
	ldr	r3, [r6, #152]
	orr	r3, r3, #262144
	str	r3, [r6, #152]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L132:
	ldrb	r3, [r4, #81]	@ zero_extendqisi2
	cmp	r3, #1
	streqb	r3, [r4, #93]
	bne	.L90
	b	.L92
.L131:
	ldr	r2, .L137+64
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #81]
	cmp	r0, #0
	bne	.L89
	ldr	r2, .L137+68
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	strb	r0, [r4, #92]
	b	.L89
.L134:
	ldr	r2, .L137+72
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #89]
	cmp	r0, #0
	beq	.L98
	ldr	r1, .L137+76
	mov	r0, r5
	bl	avs_se_v
	ldr	r1, .L137+80
	str	r0, [r4, #120]
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r4, #124]
	b	.L98
.L133:
	ldr	r2, .L137+84
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	str	r0, [r4, #344]
	b	.L94
.L135:
	ldr	r2, .L137+88
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	cmp	r0, #1
	mov	r7, r0
	str	r0, [r4, #128]
	beq	.L101
.L110:
	mov	r0, r5
	ldr	r2, .L137+92
	mov	r1, #1
	bl	avs_u_v
	str	r0, [r4, #332]
	b	.L100
.L129:
	ldr	r2, .L137+96
	mov	r1, #1
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L137+100
	mov	r1, #7
	str	r0, [r4, #108]
	mov	r0, r5
	bl	avs_u_v
	ldr	r3, [r4, #96]
	mov	r2, #1
	strb	r2, [r4]
	str	r0, [r4, #100]
	orr	r0, r0, r3, asl #7
	str	r0, [r4, #96]
	b	.L86
.L130:
	ldr	r1, .L137+104
	mov	r0, r5
	bl	avs_ue_v
	str	r0, [r4, #116]
	b	.L87
.L101:
	mov	r1, r0
	ldr	r2, .L137+108
	mov	r0, r5
	bl	avs_u_v
	mov	r1, r7
	ldr	r2, .L137+112
	str	r0, [r4, #132]
	mov	r0, r5
	bl	avs_u_v
	cmp	r0, #0
	str	r0, [r4, #136]
	beq	.L136
.L102:
	ldr	r2, .L137+116
	mov	r1, #2
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+120
	mov	r1, #2
	str	r0, [r4, #148]
	mov	r0, r5
	bl	avs_u_v
	ldr	r3, [r4, #148]
	cmp	r3, #1
	str	r0, [r4, #152]
	beq	.L105
	ldr	r2, [r4, #132]
	cmp	r2, #0
	cmpeq	r3, #3
	beq	.L105
	cmp	r3, #2
	addeq	r7, r4, #176
	bne	.L110
.L109:
	add	r8, r4, #200
.L108:
	ldr	r1, .L137+124
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r7, #4]!
	cmp	r7, r8
	bne	.L108
	b	.L110
.L105:
	add	r8, r4, #152
	add	r7, r4, #176
.L104:
	ldr	r1, .L137+128
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r8, #4]!
	cmp	r8, r7
	bne	.L104
	ldr	r3, [r4, #148]
	cmp	r3, #2
	beq	.L109
	ldr	r2, [r4, #132]
	cmp	r2, #0
	cmpeq	r3, #3
	bne	.L110
	b	.L109
.L136:
	ldr	r1, .L137+132
	mov	r0, r5
	bl	avs_se_v
	ldr	r1, .L137+136
	str	r0, [r4, #140]
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r4, #144]
	b	.L102
.L138:
	.align	2
.L137:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC45
	.word	.LC18
	.word	.LC46
	.word	.LC22
	.word	.LC24
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC48
	.word	.LC49
	.word	.LC51
	.word	.LC16
	.word	.LC30
	.word	.LC31
	.word	.LC25
	.word	.LC47
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC50
	.word	.LC35
	.word	.LC36
	.word	.LC12
	.word	.LC19
	.word	.LC23
	.word	.LC37
	.word	.LC38
	.word	.LC41
	.word	.LC42
	.word	.LC44
	.word	.LC43
	.word	.LC39
	.word	.LC40
	UNWIND(.fnend)
	.size	AVS_pb_picture_header, .-AVS_pb_picture_header
	.align	2
	.global	AVS_user_data
	.type	AVS_user_data, %function
AVS_user_data:
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
	add	r4, r0, #12288
	mov	r6, r1
	mov	r5, r0
	ldr	r2, .L172
	ldr	r0, [r4, #3176]
	mov	r1, #32
	bl	avs_f_v
	ldr	r3, [r4, #2784]
	cmp	r6, #0
	orr	r3, r3, #1048576
	str	r3, [r4, #2784]
	bne	.L140
	ldr	r1, [r4, #3468]
	cmp	r1, #0
	beq	.L141
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	str	r6, [r4, #3468]
.L141:
	ldr	r0, [r5, #4]
	bl	GetUsd
	cmp	r0, #0
	str	r0, [r4, #3468]
	beq	.L151
	ldr	r3, [r5, #12]
	add	r0, r0, #1056
	mov	r1, #10
	add	r6, r5, #16384
	ldr	r7, .L172+4
	ldrd	r2, [r3, #64]
	strd	r2, [r0]
	ldr	r3, [r4, #3468]
	str	r1, [r3, #1040]
	ldr	r3, [r4, #3468]
	ldr	r2, [r4, #2792]
	str	r2, [r3, #1044]
	ldr	r2, [r4, #3468]
	ldr	r3, [r6, #184]
	sub	r3, r3, #4
	str	r3, [r2, #1052]
	ldr	r0, [r4, #3468]
	ldr	r2, [r0, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r0, #1052]
	ldrgt	r0, [r4, #3468]
	ldr	r1, [r6, #168]
	ldr	r3, [r7, #52]
	ldrgt	r2, [r0, #1052]
	add	r1, r1, #4
	blx	r3
	ldrb	r3, [r6, #173]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L146
	ldr	r2, [r4, #3468]
	ldr	r1, [r6, #264]
	ldr	r3, [r2, #1052]
	add	r3, r3, r1
	str	r3, [r2, #1052]
	ldr	r1, [r4, #3468]
	ldr	r2, [r1, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r1, #1052]
	ldrgt	r1, [r4, #3468]
	ldr	r0, [r6, #184]
	ldrgt	r2, [r1, #1052]
	rsb	r3, r0, #4
	add	r2, r3, r2
	cmp	r2, #0
	ble	.L146
	sub	r0, r0, #4
	ldr	r3, [r7, #52]
	add	r0, r1, r0
	ldr	r1, [r6, #248]
	blx	r3
.L146:
	ldr	r3, .L172+8
	ldr	r6, [r3]
	cmp	r6, #0
	ldrne	r2, [r4, #3468]
	bne	.L171
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L140:
	ldr	r1, [r4, #3472]
	cmp	r1, #0
	beq	.L150
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r3, #0
	str	r3, [r4, #3472]
.L150:
	ldr	r0, [r5, #4]
	bl	GetUsd
	cmp	r0, #0
	str	r0, [r4, #3472]
	beq	.L151
	ldr	r3, [r5, #12]
	add	r0, r0, #1056
	mov	r1, #11
	add	r6, r5, #16384
	ldr	r7, .L172+4
	ldrd	r2, [r3, #64]
	strd	r2, [r0]
	ldr	r3, [r4, #3472]
	str	r1, [r3, #1040]
	ldr	r3, [r4, #3472]
	ldr	r2, [r4, #2792]
	str	r2, [r3, #1044]
	ldr	r2, [r4, #3472]
	ldr	r3, [r6, #184]
	sub	r3, r3, #4
	str	r3, [r2, #1052]
	ldr	r0, [r4, #3472]
	ldr	r2, [r0, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r0, #1052]
	ldrgt	r0, [r4, #3472]
	ldr	r1, [r6, #168]
	ldr	r3, [r7, #52]
	ldrgt	r2, [r0, #1052]
	add	r1, r1, #4
	blx	r3
	ldrb	r3, [r6, #173]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L154
	ldr	r2, [r4, #3472]
	ldr	r1, [r6, #264]
	ldr	r3, [r2, #1052]
	add	r3, r3, r1
	str	r3, [r2, #1052]
	ldr	r1, [r4, #3472]
	ldr	r2, [r1, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r1, #1052]
	ldrgt	r1, [r4, #3472]
	ldr	r0, [r6, #184]
	ldrgt	r2, [r1, #1052]
	rsb	r3, r0, #4
	add	r2, r3, r2
	cmp	r2, #0
	ble	.L154
	sub	r0, r0, #4
	ldr	r3, [r7, #52]
	add	r0, r1, r0
	ldr	r1, [r6, #248]
	blx	r3
.L154:
	ldr	r3, .L172+8
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L170
	ldr	r2, [r4, #3472]
.L171:
	movw	r3, #1064
	ldr	r0, [r5, #4]
	mov	r1, #6
	blx	r6
.L170:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L151:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L173:
	.align	2
.L172:
	.word	.LC52
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	UNWIND(.fnend)
	.size	AVS_user_data, .-AVS_user_data
	.align	2
	.global	AVS_sequence_display_extension
	.type	AVS_sequence_display_extension, %function
AVS_sequence_display_extension:
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
	ldr	r4, [r0, #544]
	mov	r5, r1
	ldr	r2, .L177
	mov	r1, #4
	mov	r6, r0
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+4
	mov	r1, #3
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+8
	mov	r1, #1
	strb	r0, [r5, #50]
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+12
	mov	r1, #1
	strb	r0, [r5, #51]
	mov	r0, r4
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r5, #52]
	cmp	r0, #1
	beq	.L176
.L175:
	ldr	r2, .L177+16
	mov	r1, #14
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+20
	mov	r1, #1
	str	r0, [r5, #68]
	mov	r0, r4
	bl	avs_f_v
	ldr	r2, .L177+24
	mov	r1, #14
	strb	r0, [r5, #49]
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+28
	mov	r1, #2
	str	r0, [r5, #72]
	mov	r0, r4
	bl	avs_u_v
	strb	r0, [r5, #48]
	mov	r0, r4
	bl	AVS_next_start_code
	ldr	r3, [r6, #152]
	mov	r0, #1
	orr	r3, r3, #131072
	str	r3, [r6, #152]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L176:
	ldr	r2, .L177+32
	mov	r1, #8
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+36
	mov	r1, #8
	str	r0, [r5, #56]
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+40
	mov	r1, #8
	str	r0, [r5, #60]
	mov	r0, r4
	bl	avs_u_v
	str	r0, [r5, #64]
	b	.L175
.L178:
	.align	2
.L177:
	.word	.LC53
	.word	.LC54
	.word	.LC55
	.word	.LC56
	.word	.LC60
	.word	.LC12
	.word	.LC61
	.word	.LC16
	.word	.LC57
	.word	.LC58
	.word	.LC59
	UNWIND(.fnend)
	.size	AVS_sequence_display_extension, .-AVS_sequence_display_extension
	.align	2
	.global	AVS_copyright_extension
	.type	AVS_copyright_extension, %function
AVS_copyright_extension:
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
	ldr	r4, [r0, #544]
	mov	r5, r0
	ldr	r2, .L180
	mov	r1, #4
	ldr	r6, .L180+4
	mov	r0, r4
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L180+8
	mov	r1, #1
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L180+12
	mov	r1, #8
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L180+16
	mov	r1, #1
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L180+20
	mov	r1, #7
	bl	avs_u_v
	mov	r2, r6
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L180+24
	mov	r1, #20
	bl	avs_u_v
	mov	r2, r6
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L180+28
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r6
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	ldr	r2, .L180+32
	mov	r1, #22
	mov	r0, r4
	bl	avs_u_v
	mov	r0, r4
	bl	AVS_next_start_code
	ldr	r3, [r5, #152]
	mov	r0, #1
	orr	r3, r3, #2097152
	str	r3, [r5, #152]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L181:
	.align	2
.L180:
	.word	.LC53
	.word	.LC12
	.word	.LC62
	.word	.LC63
	.word	.LC64
	.word	.LC16
	.word	.LC65
	.word	.LC66
	.word	.LC67
	UNWIND(.fnend)
	.size	AVS_copyright_extension, .-AVS_copyright_extension
	.align	2
	.global	AVS_camera_parameters_extension
	.type	AVS_camera_parameters_extension, %function
AVS_camera_parameters_extension:
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
	ldr	r4, [r0, #544]
	mov	r6, r0
	ldr	r7, .L183
	mov	r1, #4
	ldr	r5, .L183+4
	ldr	r2, .L183+8
	mov	r0, r4
	bl	avs_u_v
	mov	r2, r7
	mov	r0, r4
	mov	r1, #1
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L183+12
	mov	r1, #7
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+16
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+20
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+24
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+28
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+32
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+36
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+40
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+44
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+48
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+52
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+56
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+60
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+64
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+68
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+72
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+76
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r2, r7
	mov	r1, #32
	mov	r0, r4
	bl	avs_u_v
	mov	r0, r4
	bl	AVS_next_start_code
	ldr	r3, [r6, #152]
	mov	r0, #1
	orr	r3, r3, #4194304
	str	r3, [r6, #152]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L184:
	.align	2
.L183:
	.word	.LC16
	.word	.LC12
	.word	.LC53
	.word	.LC68
	.word	.LC69
	.word	.LC70
	.word	.LC71
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC84
	UNWIND(.fnend)
	.size	AVS_camera_parameters_extension, .-AVS_camera_parameters_extension
	.align	2
	.global	AVS_picture_display_extension
	.type	AVS_picture_display_extension, %function
AVS_picture_display_extension:
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
	ldr	r4, [r0, #544]
	mov	r7, r1
	mov	r8, r0
	mov	r1, #4
	ldr	r2, .L204
	mov	r0, r4
	bl	avs_u_v
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L202
	ldrb	r3, [r7, #81]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L203
.L187:
	mov	r3, #1
	str	r3, [r7, #4]
.L189:
	add	r6, r7, #348
	mov	r5, #0
.L191:
	ldr	r2, .L204+4
	mov	r1, #16
	mov	r0, r4
	add	r5, r5, #1
	bl	avs_u_v
	ldr	r2, .L204+8
	mov	r1, #1
	str	r0, [r6, #4]!
	mov	r0, r4
	bl	avs_f_v
	ldr	r2, .L204+12
	mov	r1, #16
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L204+8
	mov	r1, #1
	str	r0, [r6, #12]
	mov	r0, r4
	bl	avs_f_v
	ldr	r3, [r7, #4]
	cmp	r3, r5
	bgt	.L191
	mov	r0, r4
	bl	AVS_next_start_code
	ldr	r3, [r8, #152]
	mov	r0, #1
	orr	r3, r3, #524288
	str	r3, [r8, #152]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L203:
	ldrb	r3, [r7, #83]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L190
.L188:
	mov	r3, #2
	str	r3, [r7, #4]
	b	.L189
.L202:
	ldrb	r3, [r7, #83]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L187
	ldrb	r3, [r7, #82]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L188
.L190:
	mov	r3, #3
	str	r3, [r7, #4]
	b	.L189
.L205:
	.align	2
.L204:
	.word	.LC53
	.word	.LC85
	.word	.LC12
	.word	.LC86
	UNWIND(.fnend)
	.size	AVS_picture_display_extension, .-AVS_picture_display_extension
	.align	2
	.global	AVS_extension
	.type	AVS_extension, %function
AVS_extension:
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
	ldr	r4, [r0, #544]
	mov	r5, r0
	ldr	r2, .L213
	mov	r6, r1
	mov	r1, #32
	mov	r0, r4
	bl	avs_f_v
	mov	r0, r4
	mov	r1, #4
	bl	BsShow
	sub	r0, r0, #2
	cmp	r0, #9
	ldrls	pc, [pc, r0, asl #2]
	b	.L207
.L209:
	.word	.L208
	.word	.L207
	.word	.L210
	.word	.L207
	.word	.L207
	.word	.L211
	.word	.L207
	.word	.L207
	.word	.L207
	.word	.L212
.L212:
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS_camera_parameters_extension
.L211:
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS_picture_display_extension
.L210:
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS_copyright_extension
.L208:
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS_sequence_display_extension
.L207:
	mov	r0, r4
	mov	r1, #4
	bl	BsSkip
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L214:
	.align	2
.L213:
	.word	.LC87
	UNWIND(.fnend)
	.size	AVS_extension, .-AVS_extension
	.align	2
	.global	AVS_extension_and_userdata
	.type	AVS_extension_and_userdata, %function
AVS_extension_and_userdata:
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
	add	r3, r0, #12288
	add	r6, r0, #14912
	add	r5, r0, #15808
	mov	r7, r0
	mov	r8, r1
	ldr	r4, [r3, #3176]
	add	r6, r6, #8
	add	r5, r5, #4
	b	.L219
.L218:
	mov	r1, #32
	mov	r0, r4
	bl	BsShow
	uxtb	r0, r0
	cmp	r0, #178
	beq	.L223
.L219:
	mov	r0, r4
	bl	BsResidBits
	cmp	r0, #40
	mov	r0, r4
	ble	.L224
	bl	AVS_next_start_code
	mov	r1, #32
	mov	r0, r4
	bl	BsShow
	uxtb	r0, r0
	cmp	r0, #178
	cmpne	r0, #181
	bne	.L221
	cmp	r0, #181
	bne	.L218
	mov	r1, r5
	mov	r0, r6
	bl	AVS_extension
	b	.L218
.L224:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L221:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L223:
	mov	r1, r8
	mov	r0, r7
	bl	AVS_user_data
	b	.L219
	UNWIND(.fnend)
	.size	AVS_extension_and_userdata, .-AVS_extension_and_userdata
	.align	2
	.global	AVS_AllocateVHB
	.type	AVS_AllocateVHB, %function
AVS_AllocateVHB:
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
	add	r3, r0, #12288
	movw	r2, #8160
	mov	r5, r0
	ldr	r4, [r3, #2824]
	ldr	r3, [r3, #2828]
	sub	r1, r4, #32
	cmp	r1, r2
	bhi	.L226
	sub	r1, r3, #32
	cmp	r1, r2
	bhi	.L226
	ldr	r2, [r0, #12]
	ldr	r6, [r2, #732]
	ldr	r1, [r2, #28]
	cmp	r6, #0
	bne	.L229
	cmp	r1, #25
	beq	.L258
.L248:
	mov	r6, #4
	mov	r8, #5
	mov	r7, r6
.L230:
	ldr	ip, .L260
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #56
	str	r3, [fp, #-64]
	ldr	r9, [ip, #48]
	blx	r9
	ldr	r2, [r5, #12]
	ldr	r3, [fp, #-64]
	str	r4, [fp, #-52]
	ldr	r2, [r2, #28]
	str	r3, [fp, #-48]
	cmp	r2, #24
	str	r4, [fp, #-44]
	str	r3, [fp, #-40]
	beq	.L239
	uxtb	r6, r6
	strb	r7, [fp, #-55]
	strb	r8, [fp, #-54]
.L243:
	sub	r1, fp, #56
	ldr	r0, [r5, #4]
	strb	r6, [fp, #-53]
	bl	FSP_ConfigInstance
	subs	r6, r0, #0
	bne	.L240
	ldr	r1, [r5, #12]
	sub	r3, fp, #60
	ldr	r0, [r5, #4]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L259
	cmp	r0, #0
	moveq	r6, #1
	streq	r6, [r5, #8]
	beq	.L251
	ldr	r1, .L260+4
	mov	r0, r6
	bl	dprint_vfmw
	b	.L251
.L226:
	mov	r2, r4
	ldr	r1, .L260+8
	mov	r0, #0
	mov	r6, #0
	bl	dprint_vfmw
.L251:
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L229:
	cmp	r1, #25
	bne	.L248
	ldr	r1, [r2, #692]
	ldr	r0, [r2, #696]
	cmp	r1, r4
	bcc	.L236
	cmp	r0, r3
	bcc	.L236
.L237:
	ldr	r0, [r2, #720]
	ldr	r1, [r2, #716]
	cmp	r0, #0
	add	r7, r1, #2
	moveq	r6, #1
	beq	.L238
	add	r6, r1, #1
	cmp	r6, #17
	movge	r6, #17
.L238:
	ldrb	r8, [r2, #740]	@ zero_extendqisi2
	b	.L230
.L240:
	ldr	r1, .L260+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r6, #0
	b	.L251
.L239:
	mov	r6, #1
	strb	r8, [fp, #-54]
	strb	r6, [fp, #-55]
	b	.L243
.L258:
	ldr	r1, [r2, #692]
	ldr	r0, [r2, #696]
	cmp	r1, r4
	bcc	.L232
	cmp	r0, r3
	bcc	.L232
	ldr	r6, [r5, #8]
	cmp	r6, #1
	bne	.L237
	b	.L251
.L236:
	str	r0, [sp, #4]
	mov	r2, r4
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L260+16
	mov	r6, #0
	bl	dprint_vfmw
	b	.L251
.L232:
	str	r0, [sp, #4]
	mov	r2, r4
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L260+16
	bl	dprint_vfmw
	b	.L251
.L259:
	add	r0, r5, #16192
	mov	r6, #3
	bl	ResetVoQueue
	b	.L251
.L261:
	.align	2
.L260:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC90
	.word	.LC88
	.word	.LC91
	.word	.LC89
	UNWIND(.fnend)
	.size	AVS_AllocateVHB, .-AVS_AllocateVHB
	.align	2
	.global	AVS_StartDecode
	.type	AVS_StartDecode, %function
AVS_StartDecode:
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
	add	r6, r0, #16384
	add	r5, r0, #12288
	mov	r4, r0
	ldr	r3, [r6, #328]
	strb	r3, [r0, #20]
	ldr	r3, [r6, #332]
	strb	r3, [r0, #21]
	ldr	r3, [r6, #336]
	strb	r3, [r0, #22]
	ldr	r3, [r6, #340]
	strb	r3, [r0, #23]
	ldr	r3, [r6, #344]
	strb	r3, [r0, #24]
	ldr	r3, [r6, #356]
	str	r3, [r0, #28]
	ldr	r3, [r6, #360]
	str	r3, [r0, #84]
	ldr	r3, [r6, #380]
	str	r3, [r0, #32]
	ldr	r3, [r6, #508]
	str	r3, [r0, #96]
	ldr	r3, [r6, #520]
	str	r3, [r0, #100]
	ldr	r3, [r6, #512]
	str	r3, [r0, #104]
	ldr	r3, [r6, #524]
	str	r3, [r0, #108]
	ldr	r3, [r6, #516]
	str	r3, [r0, #112]
	ldr	r3, [r6, #528]
	str	r3, [r0, #116]
	ldr	r3, [r6, #388]
	strh	r3, [r0, #80]	@ movhi
	ldr	r3, [r6, #384]
	strh	r3, [r0, #82]	@ movhi
	ldr	r3, [r6, #392]
	strb	r3, [r0, #59]
	ldr	r3, [r6, #396]
	strb	r3, [r0, #60]
	ldr	r3, [r6, #432]
	strb	r3, [r0, #36]
	ldr	r3, [r6, #436]
	strb	r3, [r0, #37]
	ldr	r3, [r6, #400]
	strb	r3, [r0, #38]
	ldr	r3, [r6, #404]
	strb	r3, [r0, #39]
	ldr	r3, [r6, #412]
	strb	r3, [r0, #40]
	ldr	r3, [r6, #416]
	strb	r3, [r0, #41]
	ldr	r3, [r6, #420]
	strb	r3, [r0, #42]
	ldr	r3, [r6, #424]
	strb	r3, [r0, #43]
	ldr	r3, [r6, #428]
	strb	r3, [r0, #44]
	ldr	r3, [r6, #440]
	strb	r3, [r0, #45]
	ldr	r3, [r6, #444]
	strb	r3, [r0, #46]
	ldr	r3, [r6, #448]
	strb	r3, [r0, #47]
	ldr	r3, [r6, #452]
	strb	r3, [r0, #48]
	ldr	r3, [r6, #456]
	strb	r3, [r0, #49]
	ldr	r3, [r6, #500]
	strb	r3, [r0, #50]
	ldr	r3, [r6, #408]
	strb	r3, [r0, #51]
	ldr	r3, [r6, #464]
	strb	r3, [r0, #52]
	ldr	r3, [r6, #460]
	strb	r3, [r0, #53]
	ldr	r3, [r6, #480]
	strb	r3, [r0, #54]
	ldr	r3, [r6, #476]
	strb	r3, [r0, #55]
	ldr	r3, [r6, #472]
	strb	r3, [r0, #56]
	ldr	r3, [r6, #468]
	strb	r3, [r0, #57]
	ldr	r3, [r6, #504]
	strb	r3, [r0, #58]
	ldr	r2, [r6, #484]
	ldr	r3, [r5, #2756]
	str	r2, [r5, #2172]
	ldr	r2, [r6, #488]
	str	r2, [r5, #2176]
	ldr	r2, [r6, #492]
	str	r2, [r5, #2180]
	ldr	r2, [r6, #560]
	str	r2, [r5, #2188]
	ldr	r2, [r6, #572]
	str	r2, [r5, #2192]
	ldr	r1, [r3, #12]
	ldr	r0, [r0, #4]
	bl	FSP_GetLogicFs
	subs	r7, r0, #0
	beq	.L277
	ldr	r2, [r7, #32]
	add	ip, r4, #14592
	add	ip, ip, #24
	add	r3, r4, #16896
	add	r0, r4, #17152
	add	r3, r3, #194
	ldr	r1, [r2, #24]
	add	r0, r0, #66
	mov	r2, ip
	str	r1, [r5, #2588]
	ldr	r1, [r7, #32]
	ldr	r1, [r1, #60]
	str	r1, [r5, #2596]
	ldr	r1, [r7, #32]
	ldr	r1, [r1, #44]
	str	r1, [r5, #2600]
	ldr	r1, [r7, #32]
	ldr	r1, [r1, #48]
	str	r1, [r5, #2604]
	ldr	r1, [r6, #380]
	str	r1, [r5, #2184]
	ldr	r1, [r6, #496]
	str	r1, [r5, #2196]
	ldr	r1, [r6, #704]
	str	r1, [r5, #2200]
	ldr	r1, [r6, #532]
	strb	r1, [r4, #61]
	ldr	r1, [r6, #536]
	strb	r1, [r4, #62]
	ldr	r1, [r6, #544]
	strb	r1, [r4, #63]
	ldr	r1, [r6, #540]
	strb	r1, [r4, #64]
	ldr	r1, [r6, #548]
	strb	r1, [r4, #65]
	ldr	r1, [r6, #552]
	strb	r1, [r4, #66]
	ldr	r1, [r6, #556]
	strb	r1, [r4, #67]
.L265:
	ldrsh	r1, [r3, #2]!
	cmp	r3, r0
	str	r1, [r2, #4]!
	bne	.L265
	ldr	r1, [r6, #364]
	add	r2, r4, #16896
	add	r3, r4, #14464
	add	r2, r2, #60
	add	r3, r3, #24
	str	r1, [r5, #2608]
	ldr	r1, [r6, #368]
	str	r1, [r5, #2612]
	ldr	r1, [r6, #372]
	str	r1, [r5, #2616]
	ldr	r1, [r6, #376]
	str	r1, [r5, #2620]
.L266:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, ip
	bne	.L266
	ldr	r3, [r5, #3464]
	add	r1, r4, #20
	add	r3, r3, #1
	str	r3, [r5, #3464]
	ldr	r3, [r4, #12]
	str	r1, [r4, #16]
	ldr	r2, [r3, #912]
	cmp	r2, #1
	beq	.L278
	cmp	r2, #2
	beq	.L279
.L268:
	ldr	r2, [r3, #600]
	mov	r0, #1
	str	r2, [r5, #2624]
	ldr	r3, [r3, #652]
	str	r3, [r5, #2628]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L278:
	cmp	r1, #0
	beq	.L268
	ldr	r1, [r5, #2756]
	ldrb	r2, [r1, #9]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L268
	mov	r7, #0
	ldr	r0, [r4, #4]
	str	r7, [r4, #16]
	mov	r2, r7
	ldr	r1, [r1, #12]
	bl	FSP_SetDisplay
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L279:
	ldr	r2, [r3, #916]
	cmp	r1, #0
	cmpne	r2, #0
	ble	.L268
	ldr	r1, [r5, #2756]
	ldrb	r2, [r1, #9]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L268
	mov	r7, #0
	ldr	r0, [r4, #4]
	str	r7, [r4, #16]
	mov	r2, r7
	ldr	r1, [r1, #12]
	bl	FSP_SetDisplay
	ldr	r2, [r4, #12]
	mov	r0, r7
	ldr	r3, [r2, #916]
	sub	r3, r3, #1
	str	r3, [r2, #916]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L277:
	movw	r2, #2162
	ldr	r1, .L280
	bl	dprint_vfmw
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L281:
	.align	2
.L280:
	.word	.LC92
	UNWIND(.fnend)
	.size	AVS_StartDecode, .-AVS_StartDecode
	.align	2
	.global	AVS_SetImgFormat
	.type	AVS_SetImgFormat, %function
AVS_SetImgFormat:
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
	add	r5, r0, #12288
	mov	r6, r0
	ldrb	r3, [r5, #2815]	@ zero_extendqisi2
	ldr	r7, [r5, #3148]
	cmp	r3, #1
	ldrb	r3, [r5, #2850]	@ zero_extendqisi2
	moveq	r10, #0
	str	r3, [fp, #-48]
	beq	.L283
	ldrb	r10, [r5, #2880]	@ zero_extendqisi2
	subs	r10, r10, #1
	movne	r10, #1
.L283:
	ldrb	r3, [r5, #2813]	@ zero_extendqisi2
	ldr	r0, [r6, #4]
	sub	r3, r3, #1
	ldrb	r9, [r5, #2882]	@ zero_extendqisi2
	uxtb	r3, r3
	cmp	r3, #3
	ldrls	r2, .L293
	movhi	r8, #0
	addls	r3, r2, r3, lsl #2
	ldrls	r8, [r3, #64]
	ldr	r3, [r5, #2756]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L291
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	mov	r1, r8
	ldrb	ip, [r4, #64]	@ zero_extendqisi2
	bfi	r3, r10, #0, #2
	ldr	r2, [fp, #-48]
	bfi	ip, r7, #0, #2
	uxtb	r3, r3
	and	ip, ip, #227
	orr	r3, r3, #12
	bfi	ip, r2, #5, #3
	bfi	r3, r9, #4, #2
	strb	ip, [r4, #64]
	strb	r3, [r4, #65]
	ldr	r3, [r4, #64]
	bfi	r3, r8, #14, #3
	str	r3, [r4, #64]
	ldr	r2, [r5, #2756]
	ldrb	r3, [r4, #66]	@ zero_extendqisi2
	ldrb	r2, [r2]	@ zero_extendqisi2
	bfi	r3, r2, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r5, #2756]
	ldr	r3, [r3, #4]
	str	r3, [r4, #120]
	ldr	r3, [r5, #3456]
	str	r7, [r4, #56]
	str	r7, [r4, #60]
	str	r3, [r4, #152]
	bl	SetAspectRatio
	ldr	r3, [r5, #2824]
	str	r3, [r4, #68]
	ldr	r3, [r5, #2828]
	str	r3, [r4, #72]
	ldr	r2, [r5, #2844]
	str	r2, [r4, #108]
	ldr	r2, [r6, #12]
	ldr	r2, [r2, #28]
	cmp	r2, #25
	beq	.L292
.L286:
	mov	r3, #6
	str	r3, [r4, #296]
	ldrb	r1, [r5, #2881]	@ zero_extendqisi2
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
.L292:
	ldr	r0, [r4, #112]
	add	r3, r3, #15
	ldr	ip, [r4, #36]
	add	lr, r4, #512
	mov	r3, r3, lsr #4
	mov	r1, r0, asl #4
	add	r6, ip, r0
	mul	r1, r3, r1
	add	r7, r1, ip
	str	r7, [r4, #40]
	ldrd	r2, [lr, #-8]
	add	r0, r7, r0
	adds	r2, r2, r1
	adc	r3, r3, r1, asr #31
	strd	r2, [lr]
	str	r7, [r4, #24]
	str	r0, [r4, #32]
	str	r6, [r4, #28]
	str	ip, [r4, #20]
	b	.L286
.L291:
	mov	r2, #2272
	ldr	r1, .L293+4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L294:
	.align	2
.L293:
	.word	.LANCHOR0
	.word	.LC93
	UNWIND(.fnend)
	.size	AVS_SetImgFormat, .-AVS_SetImgFormat
	.align	2
	.global	AVS_GetImageBuffer
	.type	AVS_GetImageBuffer, %function
AVS_GetImageBuffer:
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
	add	r4, r0, #12288
	mov	r5, r0
	ldr	r3, [r4, #3872]
	cmp	r3, #2
	beq	.L296
	ldr	r6, [r4, #3188]
	add	r7, r0, #14912
	add	r7, r7, #8
	add	r2, r6, #1
	mov	r3, r6, asl #4
	mov	r1, r2, asr #31
	add	r6, r3, r6, lsl #2
	add	r6, r6, #24
	mov	r3, r1, lsr #30
	add	r6, r7, r6
	add	r2, r2, r3
	str	r6, [r4, #2756]
	and	r2, r2, #3
	rsb	r2, r3, r2
	str	r2, [r4, #3188]
.L297:
	mov	r1, #1
	ldr	r0, [r5, #4]
	bl	FSP_NewLogicFs
	str	r0, [r6, #12]
	ldr	r3, [r4, #2756]
	ldr	r1, [r3, #12]
	cmp	r1, #0
	blt	.L312
	ldr	r0, [r5, #4]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L313
	ldr	r3, [r4, #2756]
	mov	r0, #18
	ldr	r1, .L314
	ldr	r2, [r3, #12]
	bl	dprint_vfmw
	ldr	r2, [r5, #28]
	cmp	r2, #0
	beq	.L302
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L302
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L314+4
	bl	dprint_vfmw
.L302:
	mov	r3, #0
	mov	r0, #1
	str	r3, [r5, #192]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L296:
	add	r7, r0, #14912
	add	r6, r7, #112
	add	r7, r7, #8
	str	r6, [r4, #2756]
	b	.L297
.L312:
	ldr	r1, .L314+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r10, r0, #0
	beq	.L299
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r8, r10, #560
	add	r6, r10, #576
	add	r9, r10, #544
	ldr	r1, [r3, #12]
	add	r7, r7, #4
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2760]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2764]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2768]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r1, [r10, #544]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r10, #552]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r10, #560]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r10, #568]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r9]
	strd	r2, [r8, #-8]
	strd	r2, [r8]
	strd	r2, [r6, #-8]
	str	r7, [r4, #2756]
	str	r7, [r4, #2768]
	str	r7, [r4, #2764]
	str	r7, [r4, #2760]
	ldr	r0, [r5, #4]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2648]
.L299:
	mov	r6, #0
	add	r1, r5, #16192
	str	r6, [r4, #3452]
	ldr	r0, [r5, #4]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L313:
	movw	r2, #2377
	ldr	r1, .L314+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L315:
	.align	2
.L314:
	.word	.LC95
	.word	.LC96
	.word	.LC94
	.word	.LC92
	UNWIND(.fnend)
	.size	AVS_GetImageBuffer, .-AVS_GetImageBuffer
	.align	2
	.global	AVS_OutputOneFrame
	.type	AVS_OutputOneFrame, %function
AVS_OutputOneFrame:
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
	mov	r6, r0
	mov	r4, r1
	ldr	r0, [r1, #4]
	ldr	r1, [r6, #12]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L322
	mov	r2, #1
	ldr	r1, [r6, #12]
	ldr	r0, [r4, #4]
	bl	FSP_SetDisplay
	ldr	r0, [r4, #4]
	add	r3, r4, #16192
	str	r5, [sp]
	mov	r2, r4
	mov	r1, #6
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L318
	ldr	r0, [r4, #4]
	mov	r2, #0
	ldr	r1, [r6, #12]
	bl	FSP_SetDisplay
	ldr	r2, [r6, #12]
	ldr	r1, .L323
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
.L318:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L322:
	movw	r2, #2418
	ldr	r1, .L323+4
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L324:
	.align	2
.L323:
	.word	.LC98
	.word	.LC97
	UNWIND(.fnend)
	.size	AVS_OutputOneFrame, .-AVS_OutputOneFrame
	.align	2
	.global	AVS_UpdateTableIdx2Dist
	.type	AVS_UpdateTableIdx2Dist, %function
AVS_UpdateTableIdx2Dist:
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
	ldrb	r3, [r0, #249]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r0, #516]
	beq	.L339
	cmp	r3, #0
	beq	.L340
	cmp	r3, #1
	bne	.L334
	ldr	r3, [r0, #132]
	add	r2, r0, #4
	ldr	r1, [r0, #124]
	cmp	r3, r2
	ldrne	r2, [r3, #16]
	ldr	r3, [r0, #128]
	ldreq	r2, [r0, #588]
	movne	r2, r2, asl #1
	strne	r2, [r0, #588]
	add	r2, r2, #1
	str	r2, [r0, #584]
	ldr	r3, [r3, #16]
	str	r2, [r0, #604]
	mov	r3, r3, asl #1
	str	r3, [r0, #580]
	str	r3, [r0, #600]
	add	r3, r3, #1
	str	r3, [r0, #576]
	str	r3, [r0, #596]
	ldr	r3, [r1, #16]
	mov	r3, r3, asl #1
	str	r3, [r0, #592]
.L330:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L340:
	ldr	r3, [r0, #128]
	ldr	r3, [r3, #16]
	mov	r3, r3, asl #1
	str	r3, [r0, #592]
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L339:
	cmp	r3, #1
	beq	.L341
	cmp	r3, #2
	bne	.L330
	ldr	r3, [r0, #132]
	add	r2, r0, #4
	cmp	r3, r2
	ldrne	r3, [r3, #16]
	movne	r3, r3, asl #1
	strne	r3, [r0, #576]
	ldr	r3, [r0, #128]
	ldr	r3, [r3, #16]
	mov	r3, r3, asl #1
	str	r3, [r0, #584]
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L334:
	cmp	r3, #2
	bne	.L330
	ldr	r3, [r0, #132]
	add	r2, r0, #4
	cmp	r3, r2
	ldrne	r2, [r3, #16]
	ldr	r3, [r0, #128]
	ldreq	r2, [r0, #580]
	movne	r2, r2, asl #1
	strne	r2, [r0, #580]
	add	r1, r2, #1
	str	r1, [r0, #576]
	ldr	r3, [r3, #16]
	str	r1, [r0, #592]
	str	r2, [r0, #596]
	mov	r3, r3, asl #1
	str	r3, [r0, #584]
	str	r3, [r0, #600]
	add	r3, r3, #1
	str	r3, [r0, #588]
	str	r3, [r0, #604]
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L341:
	ldr	r3, [r0, #128]
	add	r2, r0, #4
	ldr	r1, [r0, #132]
	ldr	r3, [r3, #16]
	cmp	r1, r2
	mov	r3, r3, asl #1
	str	r3, [r0, #576]
	ldrne	r3, [r1, #16]
	movne	r3, r3, asl #1
	strne	r3, [r0, #580]
	b	.L330
	UNWIND(.fnend)
	.size	AVS_UpdateTableIdx2Dist, .-AVS_UpdateTableIdx2Dist
	.global	__aeabi_idiv
	.align	2
	.global	AVS_UpdateTableMvEScale
	.type	AVS_UpdateTableMvEScale, %function
AVS_UpdateTableMvEScale:
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
	mov	r5, r0
	ldrb	r0, [r0, #249]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L393
	ldr	r3, [r5, #516]
	cmp	r3, #0
	moveq	r3, #512
	streq	r3, [r5, #672]
	beq	.L379
	cmp	r3, #1
	bne	.L369
	ldr	r3, [r5, #124]
	add	r10, r5, #588
	str	r3, [fp, #-60]
	add	r3, r5, #572
	str	r3, [fp, #-48]
	add	r3, r5, #604
	str	r3, [fp, #-52]
	mov	r3, #0
	str	r3, [fp, #-56]
.L358:
	ldr	r3, [fp, #-60]
	ldr	r2, [fp, #-56]
	ldr	r8, [fp, #-52]
	ldr	r3, [r3, #16]
	ldr	r7, [fp, #-48]
	add	r9, r2, r3, lsl #1
	mov	r3, r10
	mov	r10, r9
	mov	r9, r3
.L354:
	ldr	r5, [r7, #4]!
	mov	r6, r8
	ldr	r4, [fp, #-48]
	rsb	r5, r5, r10
	ubfx	r5, r5, #0, #9
.L356:
	ldr	r1, [r4, #4]!
	mov	r0, #512
	mov	r3, #1
	rsb	r1, r1, r10
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	beq	.L355
	bl	__aeabi_idiv
	mov	r3, r0
.L355:
	mul	r3, r3, r5
	cmp	r9, r4
	str	r3, [r6, #4]!
	bne	.L356
	cmp	r9, r7
	add	r8, r8, #16
	bne	.L354
	ldr	r3, [fp, #-56]
	add	r10, r9, #16
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r3, #2
	ldr	r3, [fp, #-48]
	add	r3, r3, #16
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	add	r3, r3, #64
	str	r3, [fp, #-52]
	bne	.L358
.L379:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L393:
	ldr	r2, [r5, #124]
	ldr	r3, [r5, #516]
	ldr	r6, [r2, #16]
	cmp	r3, #1
	addeq	r9, r5, #572
	addeq	r7, r5, #32
	moveq	r8, r5
	mov	r6, r6, asl #1
	beq	.L345
	cmp	r3, #2
	bne	.L379
	ldr	r3, [r5, #576]
	rsb	r3, r3, r6
	ubfx	r4, r3, #0, #9
	cmp	r4, #0
	beq	.L351
	mov	r1, r4
	mov	r0, #512
	bl	__aeabi_idiv
.L351:
	mul	r3, r0, r4
	ldr	r4, [r5, #584]
	rsb	r4, r6, r4
	ubfx	r4, r4, #0, #9
	cmp	r4, #0
	str	r3, [r5, #608]
	moveq	r0, #1
	beq	.L352
	mov	r1, r4
	mov	r0, #512
	bl	__aeabi_idiv
.L352:
	mul	r4, r0, r4
	mov	r0, #1
	str	r4, [r5, #624]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L345:
	ldr	r1, [r5, #576]
	mov	r0, #512
	ldr	r4, [r9, #4]!
	mov	r3, #1
	rsb	r1, r1, r6
	ubfx	r1, r1, #0, #9
	rsb	r4, r4, r6
	cmp	r1, #0
	ubfx	r4, r4, #0, #9
	beq	.L347
	bl	__aeabi_idiv
	mov	r3, r0
.L347:
	mul	r3, r3, r4
	mov	r0, #1
	str	r3, [r8, #608]
	ldr	r1, [r5, #580]
	rsb	r1, r1, r6
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	beq	.L348
	mov	r0, #512
	bl	__aeabi_idiv
.L348:
	mul	r0, r0, r4
	add	r8, r8, #16
	str	r0, [r8, #596]
	cmp	r8, r7
	bne	.L345
	b	.L379
.L369:
	cmp	r3, #2
	bne	.L379
	ldr	r3, [r5, #124]
	mov	r7, r5
	add	r5, r5, #16
	add	r10, r7, #572
	mov	r8, #0
	str	r3, [fp, #-52]
.L368:
	ldr	r3, [fp, #-52]
	mov	r9, r10
	ldr	r4, [r3, #16]
	mov	r3, r7
	add	r4, r8, r4, lsl #1
.L359:
	ldr	r1, [r10, #4]
	mov	r0, #512
	ldr	r6, [r9, #4]!
	mov	ip, #1
	rsb	r1, r1, r4
	ubfx	r1, r1, #0, #9
	rsb	r6, r6, r4
	cmp	r1, #0
	ubfx	r6, r6, #0, #9
	beq	.L361
	str	r3, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-48]
	mov	ip, r0
.L361:
	mul	ip, ip, r6
	mov	r0, #1
	str	ip, [r3, #608]
	ldr	r1, [r10, #8]
	rsb	r1, r1, r4
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	beq	.L362
	mov	r0, #512
	str	r3, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-48]
.L362:
	mul	r0, r0, r6
	add	r3, r3, #8
	str	r0, [r3, #604]
	cmp	r3, r5
	bne	.L359
	add	r2, r10, #8
	mov	r9, r7
.L360:
	ldr	r1, [r10, #12]
	mov	r0, #512
	ldr	r6, [r2, #4]!
	mov	ip, #1
	rsb	r1, r4, r1
	ubfx	r1, r1, #0, #9
	rsb	r6, r4, r6
	cmp	r1, #0
	ubfx	r6, r6, #0, #9
	beq	.L365
	str	r2, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-48]
	mov	ip, r0
.L365:
	mul	ip, ip, r6
	mov	r0, #1
	str	ip, [r9, #624]
	ldr	r1, [r10, #16]
	rsb	r1, r4, r1
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	beq	.L366
	mov	r0, #512
	str	r2, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-48]
.L366:
	mul	r0, r0, r6
	add	r9, r9, #8
	str	r0, [r9, #620]
	cmp	r5, r9
	bne	.L360
	add	r8, r8, #1
	add	r5, r5, #32
	cmp	r8, #2
	add	r7, r7, #32
	add	r10, r10, #16
	bne	.L368
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdateTableMvEScale, .-AVS_UpdateTableMvEScale
	.align	2
	.global	AVS_UpdateTableDirectScale
	.type	AVS_UpdateTableDirectScale, %function
AVS_UpdateTableDirectScale:
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
	ldrb	r3, [r0, #249]	@ zero_extendqisi2
	mov	r6, r0
	cmp	r3, #1
	beq	.L417
	ldr	r9, [r0, #128]
	mov	r5, #1
	add	r8, r0, #4
	add	r7, r0, #736
	mov	r4, #0
	ldr	r10, [r9, #16]
	mov	r10, r10, asl r5
.L401:
	sub	r3, r5, #1
	mov	r0, #16384
	and	r1, r5, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	add	r3, r3, #33
	ldr	r3, [r6, r3, asl #2]
	cmp	r8, r3
	beq	.L399
	ldr	r4, [r3, #16]
	add	r4, r1, r4, lsl #1
	rsb	r1, r4, r10
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	moveq	r3, #32
	streq	r3, [r7]
	beq	.L399
	bl	__aeabi_idiv
	str	r0, [r7]
.L399:
	add	r5, r5, #1
	add	r7, r7, #4
	cmp	r5, #5
	bne	.L401
	ldr	r2, [r9, #16]
	add	r9, r6, #752
	ldr	r3, [r6, #852]
	mov	r5, #1
	mov	r7, #0
	cmp	r3, #0
	moveq	r2, r2, asl #1
	movne	r10, r2, asl #1
	addeq	r10, r2, #1
.L411:
	cmp	r3, #0
	beq	.L404
	add	r1, r7, r7, lsr #31
	mov	r1, r1, asr #1
	add	r1, r1, #33
	ldr	r1, [r6, r1, asl #2]
	cmp	r8, r1
	beq	.L405
	ldr	r4, [r1, #16]
	and	r1, r5, #1
	add	r4, r1, r4, lsl #1
	rsb	r0, r4, r10
	add	r0, r0, #512
	mov	r1, r0, asr #31
	mov	ip, r1, lsr #23
	add	r0, r0, ip
	ubfx	r1, r0, #0, #9
	subs	r1, r1, ip
	moveq	r2, #32
	streq	r2, [r9, #-16]
	beq	.L407
	mov	r0, #16384
	str	r3, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-48]
	str	r0, [r9, #-16]
.L408:
	str	r0, [r9]
.L410:
	add	r5, r5, #1
	add	r7, r7, #1
	cmp	r5, #5
	add	r9, r9, #4
	bne	.L411
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L404:
	add	r1, r5, r5, lsr #31
	mov	r1, r1, asr #1
	add	r1, r1, #32
	ldr	r1, [r6, r1, asl #2]
	cmp	r8, r1
	ldrne	r4, [r1, #16]
	andne	r1, r7, #1
	addne	r4, r1, r4, lsl #1
.L405:
	rsb	r0, r4, r10
	add	r0, r0, #512
	mov	r1, r0, asr #31
	mov	ip, r1, lsr #23
	add	r0, r0, ip
	ubfx	r1, r0, #0, #9
	subs	r1, r1, ip
	beq	.L407
	mov	r0, #16384
	str	r3, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-48]
	b	.L408
.L407:
	mov	r2, #32
	str	r2, [r9]
	b	.L410
.L417:
	ldr	r3, [r0, #128]
	add	r7, r0, #4
	add	r4, r0, #128
	add	r6, r0, #136
	mov	r8, #32
	ldr	r5, [r3, #16]
	mov	r5, r5, asl #1
.L398:
	ldr	r3, [r4, #4]!
	mov	r0, #16384
	cmp	r3, r7
	beq	.L396
	ldr	r1, [r3, #16]
	sub	r1, r5, r1, asl #1
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	streq	r8, [r4, #604]
	beq	.L396
	bl	__aeabi_idiv
	str	r0, [r4, #604]
.L396:
	cmp	r4, r6
	bne	.L398
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdateTableDirectScale, .-AVS_UpdateTableDirectScale
	.align	2
	.global	AVS_UpdateTableSymScale
	.type	AVS_UpdateTableSymScale, %function
AVS_UpdateTableSymScale:
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
	ldr	r3, [r0, #132]
	add	r2, r0, #4
	mov	r5, r0
	cmp	r3, r2
	beq	.L425
	ldrb	r0, [r0, #249]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L420
	ldr	r3, [r5, #124]
	add	r2, r5, #572
	add	r5, r5, #764
	mov	r1, r5
	str	r3, [fp, #-56]
	mov	r5, r2
	mov	r3, #0
	mov	r2, r1
.L423:
	ldr	r1, [fp, #-56]
	add	r10, r5, #20
	mov	r8, r5
	str	r5, [fp, #-48]
	mov	r9, r2
	mov	r5, r10
	ldr	r6, [r1, #16]
	mov	r7, #2
	mov	r10, r2
	str	r3, [fp, #-52]
	add	r6, r3, r6, lsl #1
.L422:
	ldr	r1, [r8, #4]!
	mov	r0, #512
	ldr	r4, [r5, #-4]!
	mov	ip, #1
	rsb	r1, r1, r6
	ubfx	r1, r1, #0, #9
	rsb	r4, r6, r4
	cmp	r1, #0
	ubfx	r4, r4, #0, #9
	beq	.L421
	bl	__aeabi_idiv
	mov	ip, r0
.L421:
	mul	r4, ip, r4
	subs	r7, r7, #1
	str	r4, [r9, #4]!
	bne	.L422
	ldr	r3, [fp, #-52]
	add	r2, r10, #8
	ldr	r5, [fp, #-48]
	add	r3, r3, #1
	cmp	r3, #2
	add	r5, r5, #16
	bne	.L423
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L420:
	ldr	r2, [r5, #124]
	ldr	r1, [r3, #16]
	ldr	r3, [r5, #128]
	ldr	r2, [r2, #16]
	ldr	r4, [r3, #16]
	mov	r3, r2, asl #1
	sub	r1, r3, r1, asl #1
	ubfx	r1, r1, #0, #9
	rsb	r3, r3, r4, lsl #1
	cmp	r1, #0
	ubfx	r4, r3, #0, #9
	bne	.L430
.L424:
	mul	r3, r0, r4
	mov	r0, #1
	str	r3, [r5, #768]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L430:
	mov	r0, #512
	bl	__aeabi_idiv
	b	.L424
.L425:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdateTableSymScale, .-AVS_UpdateTableSymScale
	.align	2
	.global	AVS_UpdateTabBBlkDist
	.type	AVS_UpdateTabBBlkDist, %function
AVS_UpdateTabBBlkDist:
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
	ldr	r2, [r0, #132]
	add	r1, r0, #4
	mov	r3, r0
	cmp	r2, r1
	beq	.L434
	ldrb	r0, [r0, #249]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L435
	ldr	r4, [r3, #124]
	mov	r0, #1
	ldr	r1, [r3, #588]
	ldr	r5, [r3, #576]
	ldr	r2, [r4, #16]
	ldr	lr, [r3, #584]
	ldr	ip, [r3, #580]
	mov	r2, r2, asl r0
	rsb	r5, r5, r2
	rsb	ip, ip, r2
	rsb	lr, r2, lr
	rsb	r2, r2, r1
	ubfx	lr, lr, #0, #9
	ubfx	r1, r5, #0, #9
	str	lr, [r3, #792]
	ubfx	r2, r2, #0, #9
	str	r1, [r3, #784]
	ubfx	r1, ip, #0, #9
	str	r2, [r3, #796]
	str	r1, [r3, #788]
	ldr	r2, [r4, #16]
	ldr	r1, [r3, #604]
	ldr	r4, [r3, #592]
	ldr	lr, [r3, #600]
	mov	r2, r2, asl r0
	ldr	ip, [r3, #596]
	add	r2, r2, r0
	rsb	r4, r4, r2
	rsb	lr, r2, lr
	rsb	ip, ip, r2
	rsb	r2, r2, r1
	ubfx	lr, lr, #0, #9
	ubfx	r1, r4, #0, #9
	ubfx	r2, r2, #0, #9
	str	r1, [r3, #800]
	str	lr, [r3, #808]
	ubfx	r1, ip, #0, #9
	str	r2, [r3, #812]
	str	r1, [r3, #804]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L435:
	ldr	r1, [r3, #124]
	ldr	lr, [r3, #128]
	ldr	ip, [r2, #16]
	ldr	r1, [r1, #16]
	ldr	lr, [lr, #16]
	mov	r2, r1, asl #1
	sub	r1, r2, ip, asl #1
	rsb	r2, r2, lr, lsl #1
	ubfx	r1, r1, #0, #9
	ubfx	r2, r2, #0, #9
	str	r1, [r3, #784]
	str	r2, [r3, #792]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L434:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdateTabBBlkDist, .-AVS_UpdateTabBBlkDist
	.align	2
	.global	AVS_UpdatePmvTable
	.type	AVS_UpdatePmvTable, %function
AVS_UpdatePmvTable:
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
	ldr	r4, [r0, #516]
	mov	r5, r0
	cmp	r4, #1
	beq	.L445
	bcc	.L439
	cmp	r4, #2
	bne	.L447
	bl	AVS_UpdateTableIdx2Dist
	mov	r0, r5
	bl	AVS_UpdateTableMvEScale
	mov	r0, r5
	bl	AVS_UpdateTableDirectScale
	mov	r0, r5
	bl	AVS_UpdateTabBBlkDist
	mov	r0, r5
	bl	AVS_UpdateTableSymScale
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L447:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L439:
	ldrb	r4, [r0, #249]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L444
.L445:
	bl	AVS_UpdateTableIdx2Dist
	mov	r0, r5
	bl	AVS_UpdateTableMvEScale
.L444:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdatePmvTable, .-AVS_UpdatePmvTable
	.align	2
	.global	AVS_GetStreamInf
	.type	AVS_GetStreamInf, %function
AVS_GetStreamInf:
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
	add	r4, r0, #12288
	mov	r5, r0
	ldr	r2, [r4, #2796]
	ldrb	r3, [r4, #2812]	@ zero_extendqisi2
	cmp	r2, #1
	str	r3, [r4, #3480]
	beq	.L449
	ldr	r3, [r0, #8]
	cmp	r3, #1
	beq	.L450
.L449:
	ldr	r1, .L557
	mov	r0, #22
	bl	dprint_vfmw
	sub	r3, fp, #36
	mov	ip, #0
	sub	r2, fp, #44
	str	ip, [r3, #-4]!
	sub	r1, fp, #48
	ldr	r0, [r5, #4]
	str	ip, [fp, #-48]
	str	ip, [fp, #-44]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r5, #12]
	ldr	r2, [r3, #732]
	cmp	r2, #1
	beq	.L542
.L452:
	ldrb	r3, [r4, #2815]	@ zero_extendqisi2
	ldr	r2, [r4, #2824]
	cmp	r3, #1
	ldr	r3, [r4, #2828]
	add	r2, r2, #15
	addne	r3, r3, #31
	addeq	r3, r3, #15
	mov	r2, r2, lsr #4
	str	r2, [r4, #2776]
	movne	r3, r3, lsr #5
	moveq	r3, r3, lsr #4
	movne	r3, r3, asl #1
	cmp	r2, #512
	str	r3, [r4, #2780]
	bgt	.L459
	cmp	r3, #512
	ble	.L460
.L459:
	ldr	r1, .L557+4
	mov	r0, #18
	bl	dprint_vfmw
	mov	r7, #0
.L455:
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L460:
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	addeq	r6, r5, #14912
	addeq	r6, r6, #12
	beq	.L462
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r7, r6, #576
	add	r8, r6, #560
	add	r9, r6, #544
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2760]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2764]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2768]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r1, [r6, #544]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r6, #552]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r6, #560]
	ldr	r0, [r5, #4]
	add	r6, r5, #14912
	bl	FreeUsdByDec
	ldr	r1, [r7, #-8]
	ldr	r0, [r5, #4]
	add	r6, r6, #12
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r9]
	strd	r2, [r8, #-8]
	strd	r2, [r8]
	strd	r2, [r7, #-8]
	str	r6, [r4, #2756]
	str	r6, [r4, #2768]
	str	r6, [r4, #2764]
	str	r6, [r4, #2760]
	ldr	r0, [r5, #4]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2648]
.L462:
	add	r7, r5, #16192
	mov	r3, #0
	str	r3, [r4, #3452]
	mov	r1, r7
	ldr	r0, [r5, #4]
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r5, #12]
	ldr	r2, [r3, #732]
	cmp	r2, #0
	bne	.L463
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L543
.L463:
	ldr	r0, [r5, #4]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L539
.L465:
	str	r6, [r4, #2756]
	mov	r8, #0
	str	r6, [r4, #2768]
	mov	r0, r5
	str	r6, [r4, #2764]
	str	r6, [r4, #2760]
	str	r8, [r4, #2796]
	bl	AVS_AllocateVHB
	cmp	r0, #3
	mov	r7, r0
	beq	.L455
	cmp	r0, r8
	strne	r8, [r4, #2796]
	beq	.L544
.L450:
	ldrb	r1, [r4, #2811]	@ zero_extendqisi2
	mov	r0, r5
	ldr	r3, [r4, #2756]
	ldrb	r2, [r4, #2881]	@ zero_extendqisi2
	str	r1, [r4, #3476]
	strb	r2, [r3, #8]
	bl	AVS_GetImageBuffer
	subs	r7, r0, #0
	beq	.L545
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L546
	ldr	r3, [r5, #12]
	add	ip, r7, #592
	add	lr, r7, #608
	ldr	r1, .L557+8
	mov	r0, #29
	ldrd	r2, [r3, #64]
	strd	r2, [ip, #-8]
	ldr	r3, [r5, #12]
	ldrd	r2, [r3, #80]
	strd	r2, [ip]
	ldr	r3, [r5, #12]
	ldrd	r2, [r3, #96]
	strd	r2, [lr, #-8]
	mvn	r2, #0
	ldr	lr, [r5, #12]
	mvn	r3, #0
	ldr	lr, [lr, #112]
	str	lr, [r7]
	ldr	lr, [r5, #12]
	ldr	lr, [lr, #116]
	str	lr, [r7, #4]
	ldr	lr, [r5, #12]
	ldr	lr, [lr, #120]
	str	lr, [r7, #8]
	ldr	lr, [r5, #12]
	ldr	lr, [lr, #136]
	str	lr, [r7, #12]
	ldrb	lr, [r4, #2881]	@ zero_extendqisi2
	clz	lr, lr
	mov	lr, lr, lsr #5
	str	lr, [r7, #52]
	ldr	lr, [r5, #12]
	strd	r2, [lr, #64]
	ldrd	r6, [ip]
	ldrd	r2, [ip, #-8]
	strd	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #2756]
	ldr	r2, [r4, #2912]
	str	r2, [r3, #16]
	ldr	r3, [r4, #2756]
	ldrb	r2, [r4, #2881]	@ zero_extendqisi2
	strb	r2, [r3, #8]
	ldr	r3, [r4, #2756]
	ldr	r2, [r4, #3148]
	strb	r2, [r3, #9]
	ldrb	r2, [r4, #2881]	@ zero_extendqisi2
	ldr	r3, [r4, #2756]
	cmp	r2, #0
	ldrneb	r2, [r4, #2882]	@ zero_extendqisi2
	moveq	r2, #1
	strb	r2, [r3, #10]
	ldrb	r3, [r4, #2881]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L540
	ldr	r7, [r4, #3148]
	cmp	r7, #0
	beq	.L537
.L540:
	add	r6, r5, #14912
	add	r6, r6, #8
.L471:
	ldr	r3, [r4, #3144]
	mov	r0, r6
	add	r6, r5, #16384
	str	r3, [r4, #3484]
	bl	AVS_UpdatePmvTable
	ldr	ip, [r4, #2776]
	ldr	r0, [r4, #2780]
	mov	r3, #0
	str	r3, [r6, #332]
	mov	r3, #1
	str	r3, [r6, #336]
	mov	lr, #6
	mul	r1, r0, ip
	add	r3, r5, #15232
	add	r2, r5, #16896
	add	r3, r3, #58
	add	r2, r2, #194
	sub	r1, r1, #1
	str	r1, [r6, #328]
	ldr	r1, [r4, #3200]
	str	ip, [r6, #388]
	cmp	r1, #0
	add	ip, r1, #63
	str	r0, [r6, #384]
	add	r0, r5, #15360
	movlt	r1, ip
	str	lr, [r6, #344]
	mov	r1, r1, asr lr
	str	r1, [r6, #340]
	ldr	r1, [r4, #3480]
	add	r0, r0, #58
	str	r1, [r6, #392]
	ldr	r1, [r4, #3476]
	str	r1, [r6, #396]
	ldrb	r1, [r4, #2894]	@ zero_extendqisi2
	str	r1, [r6, #400]
	ldrb	r1, [r4, #2893]	@ zero_extendqisi2
	str	r1, [r6, #404]
	ldrb	r1, [r4, #2892]	@ zero_extendqisi2
	str	r1, [r6, #408]
	ldrb	r1, [r4, #2886]	@ zero_extendqisi2
	str	r1, [r6, #412]
	ldrb	r1, [r4, #2885]	@ zero_extendqisi2
	str	r1, [r6, #416]
	ldrb	r1, [r4, #2884]	@ zero_extendqisi2
	str	r1, [r6, #420]
	ldrb	r1, [r4, #2883]	@ zero_extendqisi2
	str	r1, [r6, #424]
	ldrb	r1, [r4, #2882]	@ zero_extendqisi2
	str	r1, [r6, #428]
	ldr	r1, [r4, #3148]
	str	r1, [r6, #432]
	ldrb	r1, [r4, #2881]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r1, #1
	movne	r1, #3
	str	r1, [r6, #436]
	ldrb	r1, [r4, #2880]	@ zero_extendqisi2
	str	r1, [r6, #440]
	ldr	r1, [r4, #2924]
	str	r1, [r6, #444]
	ldr	r1, [r4, #2920]
	str	r1, [r6, #448]
	ldrb	r1, [r4, #2889]	@ zero_extendqisi2
	str	r1, [r6, #452]
	ldrb	r1, [r4, #2888]	@ zero_extendqisi2
	str	r1, [r6, #456]
	ldr	r1, [r4, #2928]
	str	r1, [r6, #532]
	ldr	r1, [r4, #2936]
	str	r1, [r6, #536]
	ldr	r1, [r4, #2940]
	str	r1, [r6, #544]
	ldr	r1, [r4, #2944]
	str	r1, [r6, #540]
.L474:
	ldrh	r1, [r3, #2]!
	cmp	r3, r0
	strh	r1, [r2, #2]!	@ movhi
	bne	.L474
	ldr	r3, [r4, #3132]
	str	r3, [r6, #548]
	ldr	r3, [r4, #3144]
	str	r3, [r6, #556]
	ldr	r3, [r4, #3140]
	str	r3, [r6, #552]
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #2
	ldr	r3, [r4, #2760]
	ldr	r1, [r3, #12]
	beq	.L547
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L548
	ldr	r3, [r4, #2760]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #460]
	ldrsb	r2, [r3, #10]
	str	r2, [r6, #464]
	ldr	r2, [r7, #36]
	str	r2, [r6, #484]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #476]
	ldrsb	r3, [r3, #10]
	str	r3, [r6, #480]
	ldr	r3, [r7, #36]
	str	r3, [r6, #488]
	ldr	r3, [r4, #2764]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	ldrne	r3, [r4, #2764]
	beq	.L549
.L541:
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #468]
	ldrsb	r3, [r3, #10]
	str	r3, [r6, #472]
	ldr	r3, [r7, #36]
	str	r3, [r6, #492]
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L550
	ldr	r3, [r7, #52]
	str	r3, [r6, #364]
	ldr	r3, [r4, #2764]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L551
	ldr	r3, [r7, #52]
	str	r3, [r6, #368]
	ldr	r3, [r4, #2768]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L552
	ldr	r3, [r7, #52]
	str	r3, [r6, #372]
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L553
	ldr	r3, [r7, #52]
	str	r3, [r6, #376]
	ldr	r3, [r7, #36]
	str	r3, [r6, #380]
	ldr	r3, [r7, #20]
	str	r3, [r6, #496]
	ldr	r3, [r4, #2760]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #500]
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	adds	r3, r3, #0
	movne	r3, #1
	str	r3, [r6, #504]
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetPmvAddr
	str	r0, [r6, #560]
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetPmvAddr
	add	ip, r5, #15488
	add	ip, ip, #36
	mov	r2, #0
	str	r0, [r6, #572]
	add	r0, r5, #16896
	ldr	r3, [r4, #3148]
	add	r0, r0, #60
	cmp	r3, #2
	movne	r1, #0
	moveq	r1, #4
	moveq	lr, #8
	moveq	r7, #16
	movne	r7, #32
	movne	lr, r1
.L495:
	add	r2, r2, #1
	ldr	r3, [ip, #4]!
	cmp	r2, r7
	ubfx	r3, r3, #0, #18
	str	r3, [r0, #4]!
	blt	.L495
	cmp	lr, #0
	ble	.L500
	add	ip, r5, #15616
	add	r0, r5, #16896
	add	ip, ip, #36
	add	r0, r0, #124
	mov	r2, #0
.L499:
	add	r2, r2, #1
	ldr	r3, [ip, #4]!
	cmp	r2, lr
	ubfx	r3, r3, #0, #15
	str	r3, [r0, #4]!
	bne	.L499
.L500:
	cmp	r1, #0
	ble	.L498
	add	r0, r5, #15680
	add	lr, r5, #16896
	add	r0, r0, #24
	add	lr, lr, #156
	mov	ip, #0
.L501:
	ldr	r2, [r0, #4]
	add	ip, ip, #1
	ldr	r3, [r0], #8
	cmp	ip, r1
	ubfx	r2, r2, #0, #9
	ubfx	r3, r3, #0, #9
	orr	r3, r3, r2, asl #9
	str	r3, [lr, #4]!
	bne	.L501
	add	r0, r5, #15680
	add	r5, r5, #16896
	add	r0, r0, #4
	add	r5, r5, #172
	mov	r2, #0
.L502:
	add	r2, r2, #1
	ldr	r3, [r0, #4]!
	cmp	r2, r1
	ubfx	r3, r3, #0, #18
	str	r3, [r5, #4]!
	bne	.L502
.L498:
	ldr	r3, [r4, #3196]
	mov	r7, #1
	mov	r0, r7
	str	r3, [r6, #704]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L542:
	ldr	r3, [fp, #-40]
	cmp	r3, #0
	ble	.L554
.L453:
	mov	r7, #3
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L545:
	ldr	r1, .L557+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L543:
	ldr	r3, [r5, #8]
	cmp	r3, #0
	bne	.L465
.L539:
	mov	r0, r7
	bl	ResetVoQueue
	b	.L465
.L554:
	ldr	r3, [fp, #-44]
	cmp	r3, #32
	bgt	.L453
	ldr	r8, [r5, #16]
	cmp	r8, #0
	bne	.L453
	ldr	r3, [r4, #2792]
	cmp	r3, #0
	beq	.L452
	ldr	r1, [r4, #3548]
	cmp	r1, #0
	beq	.L452
	add	r6, r5, #16384
	ldr	r0, [r6, #836]
	cmp	r1, r0
	beq	.L452
	ldr	lr, [r4, #3552]
	ldr	ip, [r6, #840]
	cmp	lr, ip
	beq	.L452
	str	r1, [sp, #12]
	stmib	sp, {r0, lr}
	mov	r0, r2
	str	ip, [sp]
	ldr	r1, .L557+16
	bl	dprint_vfmw
	ldr	r2, .L557+20
	ldr	r3, [r4, #3548]
	ldr	r7, [r2]
	str	r3, [r6, #836]
	ldr	r3, [r4, #3552]
	cmp	r7, #0
	str	r3, [r6, #840]
	beq	.L452
	mov	r3, r8
	mov	r2, r8
	mov	r1, #120
	ldr	r0, [r5, #4]
	blx	r7
	b	.L452
.L544:
	ldr	r1, .L557+24
	mov	r0, #1
	bl	dprint_vfmw
	b	.L455
.L547:
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L555
	ldr	r3, [r4, #2760]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #460]
	ldrsb	r3, [r3, #10]
	str	r3, [r6, #464]
	ldr	r3, [r7, #36]
	str	r3, [r6, #484]
	ldr	r3, [r4, #2764]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L556
	ldr	r3, [r4, #2764]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #476]
	ldrsb	r3, [r3, #10]
	str	r3, [r6, #480]
	ldr	r3, [r7, #36]
	str	r3, [r6, #488]
	ldr	r3, [r4, #2768]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	ldrne	r3, [r4, #2768]
	bne	.L541
	movw	r2, #1946
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L537:
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r6, r5, #14912
	add	r6, r6, #8
	ldr	r1, [r3, #12]
	bl	FSP_SetRef
	ldr	r3, [r4, #2768]
	add	r2, r6, #4
	cmp	r3, r2
	beq	.L472
	mov	r2, r7
	ldr	r1, [r3, #12]
	ldr	r0, [r5, #4]
	bl	FSP_SetRef
.L472:
	ldr	r1, [r4, #2764]
	ldr	r2, [r4, #2760]
	ldr	r3, [r4, #2756]
	str	r1, [r4, #2768]
	str	r2, [r4, #2764]
	str	r3, [r4, #2760]
	b	.L471
.L546:
	movw	r2, #1845
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L550:
	movw	r2, #1970
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L551:
	movw	r2, #1974
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L552:
	movw	r2, #1978
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L549:
	movw	r2, #1963
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L548:
	movw	r2, #1954
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L553:
	movw	r2, #1982
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L556:
	movw	r2, #1940
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L555:
	movw	r2, #1934
	ldr	r1, .L557+28
	bl	dprint_vfmw
	b	.L455
.L558:
	.align	2
.L557:
	.word	.LC99
	.word	.LC101
	.word	.LC104
	.word	.LC103
	.word	.LC100
	.word	g_event_report
	.word	.LC102
	.word	.LC97
	UNWIND(.fnend)
	.size	AVS_GetStreamInf, .-AVS_GetStreamInf
	.align	2
	.global	AVS_PrepareDecode
	.type	AVS_PrepareDecode, %function
AVS_PrepareDecode:
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
	bl	AVS_GetStreamInf
	cmp	r0, #3
	ldmeqfd	sp, {fp, sp, pc}
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_PrepareDecode, .-AVS_PrepareDecode
	.align	2
	.global	AVS_VerifyMemPara
	.type	AVS_VerifyMemPara, %function
AVS_VerifyMemPara:
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
	.size	AVS_VerifyMemPara, .-AVS_VerifyMemPara
	.align	2
	.global	AVSDEC_Init
	.type	AVSDEC_Init, %function
AVSDEC_Init:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r8, r1
	mov	r4, r0
	moveq	r6, #1
	movne	r6, #0
	beq	.L567
	add	r5, r0, #16384
	ldr	r9, .L569
	add	r7, r0, #16192
	movw	r2, #17232
	ldr	r10, [r5, #152]
	mov	r1, r6
	ldr	r3, [r9, #48]
	blx	r3
	mov	r0, r7
	str	r10, [r5, #152]
	add	r5, r4, #14912
	bl	ResetVoQueue
	str	r8, [r4, #12]
	mov	r0, r4
	add	r8, r4, #15744
	bl	VCTRL_GetChanIDByCtx
	add	r5, r5, #8
	add	r8, r8, #36
	cmn	r0, #1
	str	r0, [r4, #4]
	beq	.L568
	ldr	r3, [r9, #48]
	mov	r2, #860
	mov	r1, r6
	mov	r0, r5
	blx	r3
	add	r3, r4, #12288
	add	r5, r5, #4
	mov	r2, #1024
	str	r5, [r3, #2756]
	mov	r0, #1
	str	r8, [r3, #3176]
	str	r5, [r3, #2768]
	str	r5, [r3, #2764]
	str	r5, [r3, #2760]
	str	r7, [r3, #3204]
	str	r2, [r3, #3200]
	ldr	r3, [r4, #12]
	str	r6, [r3, #920]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L567:
	movw	r2, #2927
	ldr	r1, .L569+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L568:
	mov	r0, r6
	ldr	r1, .L569+8
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L570:
	.align	2
.L569:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC97
	.word	.LC105
	UNWIND(.fnend)
	.size	AVSDEC_Init, .-AVSDEC_Init
	.align	2
	.global	AVSDEC_Destroy
	.type	AVSDEC_Destroy, %function
AVSDEC_Destroy:
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
	beq	.L574
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L574:
	movw	r2, #2991
	ldr	r1, .L575
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L576:
	.align	2
.L575:
	.word	.LC97
	UNWIND(.fnend)
	.size	AVSDEC_Destroy, .-AVSDEC_Destroy
	.align	2
	.global	AVSDEC_RecycleImage
	.type	AVSDEC_RecycleImage, %function
AVSDEC_RecycleImage:
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
	beq	.L579
	mov	r2, #0
	ldr	r0, [r4, #4]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #4]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L580
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
.L579:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L580:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVSDEC_RecycleImage, .-AVSDEC_RecycleImage
	.align	2
	.global	AVSDEC_GetRemainImg
	.type	AVSDEC_GetRemainImg, %function
AVSDEC_GetRemainImg:
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
	beq	.L597
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L589
	add	r4, r5, #15040
	mov	r6, #0
	add	r4, r4, #20
	mov	r7, #0
	mov	r8, #3
	mvn	r9, #0
.L588:
	ldr	r3, [r4, #-4]!
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r10, r0, #0
	beq	.L585
	ldr	r3, [r4]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetDisplay
	cmp	r0, #2
	movne	r9, #1
	beq	.L598
.L585:
	subs	r8, r8, #1
	bne	.L588
	cmp	r9, #0
	bne	.L589
.L583:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L589:
	add	r0, r5, #16192
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	GetVoLastImageID
.L598:
	mov	r0, r5
	bl	AVS_SetImgFormat
	cmp	r8, #1
	streq	r8, [r10, #180]
	mov	r2, #1
	ldr	r3, [r4]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_SetDisplay
	ldr	r0, [r5, #4]
	add	r3, r5, #16192
	str	r10, [sp]
	mov	r2, r5
	mov	r1, #6
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L587
	ldr	r1, [r10, #148]
	add	r9, r10, #544
	mov	r0, r5
	add	r10, r10, #560
	bl	AVSDEC_RecycleImage
	ldr	r1, [r10, #-16]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	strd	r6, [r9]
	ldr	r1, [r10, #-8]
	mvn	r9, #0
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	strd	r6, [r10, #-8]
	b	.L585
.L587:
	ldr	r3, [r10, #152]
	cmp	r3, #100
	bhi	.L592
	ldr	r3, [r10, #68]
	cmp	r3, #31
	bls	.L592
	ldr	r9, [r10, #72]
	cmp	r9, #31
	movhi	r9, #0
	mvnls	r9, #0
	b	.L585
.L592:
	mvn	r9, #0
	b	.L585
.L597:
	movw	r2, #3123
	ldr	r1, .L599
	bl	dprint_vfmw
	b	.L583
.L600:
	.align	2
.L599:
	.word	.LC97
	UNWIND(.fnend)
	.size	AVSDEC_GetRemainImg, .-AVSDEC_GetRemainImg
	.align	2
	.global	AVSDEC_GetImageBuffer
	.type	AVSDEC_GetImageBuffer, %function
AVSDEC_GetImageBuffer:
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
	beq	.L608
	ldr	r0, [r4, #4]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #4]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L609
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L609:
	add	r1, r4, #16192
	ldr	r0, [r4, #4]
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L608:
	movw	r2, #3320
	ldr	r1, .L610
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L611:
	.align	2
.L610:
	.word	.LC97
	UNWIND(.fnend)
	.size	AVSDEC_GetImageBuffer, .-AVSDEC_GetImageBuffer
	.align	2
	.global	ClearSlice
	.type	ClearSlice, %function
ClearSlice:
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
	add	r4, r1, #4
	add	r8, r1, #12
	mov	r7, r1
	mov	r9, r0
	mov	r6, r1
	mov	r5, #0
.L614:
	ldr	r3, [r4, #4]!
	cmp	r3, #0
	ble	.L613
	ldr	r3, [r6]
	cmp	r3, #0
	bne	.L619
.L613:
	cmp	r4, r8
	str	r5, [r4]
	str	r5, [r6], #4
	str	r5, [r7, #16]
	bne	.L614
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L619:
	ldr	r1, [r4, #12]
	mov	r0, r9
	bl	SM_ReleaseStreamSeg
	b	.L613
	UNWIND(.fnend)
	.size	ClearSlice, .-ClearSlice
	.align	2
	.global	AVS_ClearCurPic
	.type	AVS_ClearCurPic, %function
AVS_ClearCurPic:
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
	cmn	r0, #20
	cmpne	r0, #0
	mov	r6, r0
	moveq	r0, #1
	movne	r0, #0
	beq	.L621
	add	r7, r6, #12288
	ldr	r3, [r7, #2168]
	cmp	r3, #0
	addgt	r5, r6, #120
	movgt	r4, r0
	ble	.L625
.L624:
	mov	r1, r5
	ldr	r0, [r6, #4]
	bl	ClearSlice
	ldr	r3, [r7, #2168]
	add	r4, r4, #1
	add	r5, r5, #28
	cmp	r3, r4
	bgt	.L624
.L625:
	mov	r3, #0
	mov	r0, #1
	str	r3, [r7, #2168]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L621:
	mov	r2, #3360
	ldr	r1, .L627
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L628:
	.align	2
.L627:
	.word	.LC97
	UNWIND(.fnend)
	.size	AVS_ClearCurPic, .-AVS_ClearCurPic
	.align	2
	.type	AVS_DecodeArbiter.part.5, %function
AVS_DecodeArbiter.part.5:
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
	ldr	r3, [r0, #12]
	mov	r6, r0
	add	r4, r0, #12288
	ldr	r3, [r3, #8]
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L644
.L632:
	.word	.L631
	.word	.L633
	.word	.L634
	.word	.L644
	.word	.L631
.L634:
	ldr	r5, [r4, #3872]
	clz	r5, r5
	mov	r5, r5, lsr #5
.L630:
	cmp	r5, #0
	str	r3, [r4, #3448]
	beq	.L650
.L637:
	ldr	r3, [r4, #3872]
	cmp	r3, #1
	beq	.L651
.L640:
	cmp	r3, #2
	bne	.L642
	ldr	r3, [r4, #3452]
	cmp	r3, #1
	ble	.L641
.L642:
	add	r1, r4, #3520
	mov	r2, #376
	add	r1, r1, #4
	add	r0, r4, #2800
	bl	memcpy
	ldrb	ip, [r4, #2881]	@ zero_extendqisi2
	ldr	r3, [r4, #3148]
	mov	r0, #18
	ldr	r2, [r4, #3464]
	ldr	r1, .L652
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #2784]
	mov	r0, #1
	bic	r3, r3, #311296
	str	r3, [r4, #2784]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L633:
	ldr	r2, [r4, #3448]
	ldr	r5, [r4, #3872]
	cmp	r2, #2
	str	r3, [r4, #3448]
	moveq	r2, #0
	streq	r2, [r4, #3452]
	subs	r5, r5, #2
	movne	r5, #1
	cmp	r5, #0
	bne	.L637
.L650:
	mov	r0, r6
	bl	AVS_ClearCurPic
	ldr	r2, .L652+4
	ldr	r3, [r4, #2784]
	ldr	r7, [r2]
	bic	r3, r3, #311296
	str	r3, [r4, #2784]
	cmp	r7, #0
	beq	.L649
	ldr	r0, [r6, #4]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r7
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L631:
	ldr	r2, [r4, #3448]
	str	r3, [r4, #3448]
	cmp	r2, #2
	ldr	r3, [r4, #3872]
	moveq	r2, #0
	streq	r2, [r4, #3452]
	cmp	r3, #1
	bne	.L640
.L651:
	ldr	r3, [r4, #3452]
	cmp	r3, #0
	bgt	.L642
.L641:
	mov	r0, r6
	bl	AVS_ClearCurPic
	ldr	r2, .L652+4
	ldr	r3, [r4, #2784]
	ldr	r5, [r2]
	bic	r3, r3, #311296
	str	r3, [r4, #2784]
	cmp	r5, #0
	beq	.L649
	mov	r3, #0
	ldr	r0, [r6, #4]
	mov	r2, r3
	mov	r1, #113
	blx	r5
.L649:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L644:
	mov	r5, #1
	b	.L630
.L653:
	.align	2
.L652:
	.word	.LC106
	.word	g_event_report
	UNWIND(.fnend)
	.size	AVS_DecodeArbiter.part.5, .-AVS_DecodeArbiter.part.5
	.align	2
	.global	AVS_DecodeArbiter
	.type	AVS_DecodeArbiter, %function
AVS_DecodeArbiter:
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
	ldr	r3, [r3, #2784]
	and	r3, r3, #376832
	cmp	r3, #376832
	beq	.L656
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L656:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS_DecodeArbiter.part.5
	UNWIND(.fnend)
	.size	AVS_DecodeArbiter, .-AVS_DecodeArbiter
	.align	2
	.global	AVSDEC_VDMPostProc
	.type	AVSDEC_VDMPostProc, %function
AVSDEC_VDMPostProc:
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
	subs	r5, r0, #0
	mov	r6, r1
	beq	.L708
	ldr	r2, [r5, #16]
	add	r4, r5, #12288
	add	r1, r2, #12288
	ldr	r3, [r4, #2756]
	ldrb	r2, [r2, #48]	@ zero_extendqisi2
	strb	r2, [r3]
	ldr	r2, [r1, #2604]
	str	r2, [r3, #4]
	bl	AVS_ClearCurPic
	ldr	r3, .L718
	movw	r2, #14900
	mov	r1, #0
	add	r0, r5, #20
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #3148]
	cmp	r3, #0
	bne	.L660
	str	r6, [r4, #3456]
	ldr	r3, [r5, #12]
	ldr	r2, [r4, #3456]
	ldr	r3, [r3]
	cmp	r3, r2
	blt	.L709
.L664:
	mov	r0, r5
	bl	AVS_SetImgFormat
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L710
	ldr	r1, [r4, #3468]
	mov	r2, #0
	cmp	r1, #0
	strne	r1, [r3, #544]
	movne	r1, #0
	strne	r1, [r3, #548]
	ldr	r1, [r4, #3472]
	str	r2, [r4, #3468]
	cmp	r1, r2
	strne	r2, [r3, #556]
	strne	r1, [r3, #552]
	mov	r2, #0
	ldr	r3, [r4, #3148]
	str	r2, [r4, #3472]
	cmp	r3, #1
	bls	.L711
.L669:
	ldr	r7, [r4, #2756]
.L674:
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #4]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L712
	add	r3, r5, #14912
	add	r3, r3, #12
	cmp	r7, r3
	beq	.L679
	ldr	r3, [r5, #12]
	ldr	r2, [r4, #3456]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	bge	.L677
	ldr	r1, .L718+4
	mov	r0, #1
	add	r4, r6, #544
	bl	dprint_vfmw
	ldr	r1, [r7, #12]
	mov	r2, #0
	ldr	r0, [r5, #4]
	bl	FSP_SetDisplay
	ldrd	r2, [r4]
	orrs	r1, r2, r3
	bne	.L713
.L678:
	add	r6, r6, #560
	ldrd	r2, [r6, #-8]
	orrs	r1, r2, r3
	bne	.L714
.L679:
	mov	r4, #1
.L659:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L677:
	mov	r0, r7
	mov	r1, r5
	bl	AVS_OutputOneFrame
	subs	r4, r0, #0
	bne	.L679
	add	r7, r6, #544
	ldrd	r2, [r7]
	orrs	r1, r2, r3
	bne	.L715
.L680:
	add	r6, r6, #560
	ldrd	r2, [r6, #-8]
	orrs	r1, r2, r3
	beq	.L659
	mov	r1, r2
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r6, #-8]
	b	.L659
.L660:
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L716
	ldr	r2, [r4, #2764]
	ldr	r0, [r5, #4]
	ldr	r7, [r3, #152]
	ldr	r1, [r2, #12]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L717
	ldr	r3, [r3, #152]
	ldr	r2, [r4, #3148]
	add	r3, r7, r3
	add	r6, r6, r3
	cmp	r6, #100
	movge	r6, #100
	str	r6, [r4, #3456]
	ldr	r3, [r5, #12]
	cmp	r2, #2
	ldr	r3, [r3]
	beq	.L664
	ldr	r2, [r4, #3456]
	cmp	r3, r2
	bge	.L664
.L709:
	ldr	r1, .L718+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #2760]
	mov	r2, #0
	str	r2, [r4, #3452]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L665
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r8, r6, #560
	add	r7, r6, #576
	add	r9, r6, #544
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2760]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2764]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2768]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r1, [r6, #544]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r6, #552]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r6, #560]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r6, #568]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	add	r3, r5, #14912
	mov	r0, #0
	mov	r1, #0
	add	r3, r3, #12
	strd	r0, [r9]
	strd	r0, [r8, #-8]
	strd	r0, [r8]
	strd	r0, [r7, #-8]
	str	r3, [r4, #2756]
	str	r3, [r4, #2768]
	str	r3, [r4, #2764]
	str	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2648]
.L665:
	mov	r3, #0
	str	r3, [r4, #3452]
	mov	r4, r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L711:
	ldr	r2, [r4, #3452]
	ldrb	r1, [r4, #2881]	@ zero_extendqisi2
	cmp	r2, #1
	addle	r2, r2, #1
	adds	r3, r3, #0
	str	r2, [r4, #3452]
	movne	r3, #1
	cmp	r1, #1
	orreq	r3, r3, #1
	cmp	r3, #0
	beq	.L671
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_SetRef
	add	r3, r5, #14912
	ldr	r2, [r4, #2768]
	add	r3, r3, #12
	cmp	r2, r3
	beq	.L672
	ldr	r1, [r2, #12]
	mov	r2, #0
	ldr	r0, [r5, #4]
	bl	FSP_SetRef
.L672:
	ldr	r1, [r4, #2764]
	ldr	r2, [r4, #2760]
	ldr	r3, [r4, #2756]
	str	r1, [r4, #2768]
	str	r2, [r4, #2764]
	str	r3, [r4, #2760]
.L671:
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	ldreq	r7, [r4, #2764]
	beq	.L674
	b	.L669
.L714:
	mov	r1, r2
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r4, #1
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r6, #-8]
	b	.L659
.L713:
	mov	r1, r2
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r4]
	b	.L678
.L708:
	movw	r2, #3194
	ldr	r1, .L718+12
	mov	r4, r5
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L715:
	mov	r1, r2
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r7]
	b	.L680
.L710:
	movw	r2, #3237
	ldr	r1, .L718+12
	mov	r4, r3
	bl	dprint_vfmw
	b	.L659
.L712:
	movw	r2, #3274
	ldr	r1, .L718+12
	mov	r4, r6
	bl	dprint_vfmw
	b	.L659
.L716:
	movw	r2, #3212
	ldr	r1, .L718+12
	mov	r4, r3
	bl	dprint_vfmw
	b	.L659
.L717:
	mov	r2, #3216
	ldr	r1, .L718+12
	mov	r4, r3
	bl	dprint_vfmw
	b	.L659
.L719:
	.align	2
.L718:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC108
	.word	.LC107
	.word	.LC97
	UNWIND(.fnend)
	.size	AVSDEC_VDMPostProc, .-AVSDEC_VDMPostProc
	.align	2
	.global	ClearPacket
	.type	ClearPacket, %function
ClearPacket:
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
	ldr	r1, [r4, #188]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #173]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L721
	ldrb	r3, [r4, #253]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L725
.L721:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L725:
	ldr	r3, [r4, #260]
	cmp	r3, #0
	beq	.L721
	ldr	r1, [r4, #268]
	ldr	r0, [r5, #4]
	bl	SM_ReleaseStreamSeg
	b	.L721
	UNWIND(.fnend)
	.size	ClearPacket, .-ClearPacket
	.align	2
	.global	WriteAvsSliceMsg
	.type	WriteAvsSliceMsg, %function
WriteAvsSliceMsg:
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
	add	ip, r0, #12288
	mov	r4, r0
	ldr	r2, [ip, #2168]
	cmp	r2, #512
	bge	.L737
	cmp	r2, #0
	add	r1, r0, #16384
	ble	.L729
	sub	r3, r2, #1
	ldr	r0, [ip, #3548]
	ldr	r5, [r1, #168]
	mov	lr, r3, asl #5
	add	r0, r0, #15
	sub	r3, lr, r3, asl #2
	ldrb	lr, [r5, #3]	@ zero_extendqisi2
	mov	r0, r0, lsr #4
	add	r3, r4, r3
	mul	r0, lr, r0
	ldr	r3, [r3, #136]
	cmp	r0, r3
	bls	.L738
.L729:
	mov	lr, r2, asl #2
	mov	r5, r2, asl #5
	ldr	r6, [r1, #180]
	rsb	r3, lr, r5
	add	r3, r4, r3
	cmp	r2, #0
	add	r0, r3, #132
	str	r6, [r3, #120]
	ldr	r6, [r1, #188]
	str	r6, [r0, #8]
	ldr	r6, [r1, #184]
	str	r6, [r3, #128]
	streq	r2, [r4, #136]
	bne	.L739
.L731:
	ldrb	r3, [r1, #173]	@ zero_extendqisi2
	rsb	lr, lr, r5
	cmp	r3, #1
	beq	.L740
	ldr	r3, [r1, #260]
	add	r4, r4, lr
	str	r3, [r4, #124]
	ldr	r3, [r1, #268]
	str	r3, [r4, #144]
	ldr	r3, [r1, #264]
	str	r3, [r4, #132]
.L733:
	add	r2, r2, #1
	mov	r0, #1
	str	r2, [ip, #2168]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L739:
	ldr	r6, [r1, #168]
	ldr	r3, [ip, #3548]
	add	r3, r3, #15
	ldrb	r7, [r6, #3]	@ zero_extendqisi2
	mov	r3, r3, lsr #4
	mul	r7, r7, r3
	str	r7, [r0, #4]
	ldr	r3, [ip, #2824]
	ldr	r6, [ip, #2828]
	add	r0, r3, #15
	add	r6, r6, #15
	mov	r3, r0, lsr #4
	mov	r6, r6, lsr #4
	mul	r3, r3, r6
	sub	r3, r3, #1
	cmp	r7, r3
	bls	.L731
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L737:
	mov	r3, #512
	ldr	r1, .L741
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L738:
	mov	r2, r0
	ldr	r1, .L741+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L740:
	add	r4, r4, lr
	mov	r3, #0
	add	r4, r4, #128
	str	r3, [r4, #-4]
	str	r3, [r4, #16]
	str	r3, [r4, #4]
	b	.L733
.L742:
	.align	2
.L741:
	.word	.LC109
	.word	.LC110
	UNWIND(.fnend)
	.size	WriteAvsSliceMsg, .-WriteAvsSliceMsg
	.align	2
	.global	AVS_GetPacketState
	.type	AVS_GetPacketState, %function
AVS_GetPacketState:
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
	beq	.L746
	add	r4, r4, #16384
	ldr	r0, [r4, #160]
	subs	r0, r0, #1
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L746:
	movw	r2, #3460
	ldr	r1, .L747
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L748:
	.align	2
.L747:
	.word	.LC97
	UNWIND(.fnend)
	.size	AVS_GetPacketState, .-AVS_GetPacketState
	.align	2
	.global	Avs_Vfmw_WQMatrix
	.type	Avs_Vfmw_WQMatrix, %function
Avs_Vfmw_WQMatrix:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 304
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #304)
	sub	sp, sp, #304
	ldr	r7, [r0, #148]
	mov	r3, #0
	ldr	lr, [r0, #132]
	cmp	r7, #1
	str	r3, [fp, #-340]
	str	r3, [fp, #-336]
	str	r3, [fp, #-332]
	str	r3, [fp, #-328]
	str	r3, [fp, #-324]
	str	r3, [fp, #-320]
	beq	.L752
	clz	r3, lr
	cmp	r7, #3
	cmpeq	lr, #0
	mov	r3, r3, lsr #5
	beq	.L752
	cmp	r7, #2
	addeq	r3, r0, #176
	beq	.L754
	cmp	r3, #0
	bne	.L786
.L787:
	sub	lr, fp, #316
	cmp	r7, #0
	mov	r3, #128
	strh	r3, [lr]	@ movhi
	strh	r3, [lr, #2]	@ movhi
	strh	r3, [lr, #4]	@ movhi
	strh	r3, [lr, #6]	@ movhi
	strh	r3, [lr, #8]	@ movhi
	strh	r3, [lr, #10]	@ movhi
	strh	r3, [lr, #12]	@ movhi
	strh	r3, [lr, #14]	@ movhi
	strh	r3, [lr, #16]	@ movhi
	strh	r3, [lr, #18]	@ movhi
	strh	r3, [lr, #20]	@ movhi
	strh	r3, [lr, #22]	@ movhi
	bne	.L836
	ldr	r3, .L842
	add	r2, lr, #10
	add	ip, r3, #12
.L768:
	ldrh	r1, [r3, #2]!
	cmp	r3, ip
	strh	r1, [r2, #2]!	@ movhi
	bne	.L768
.L761:
	add	ip, r0, #202
	add	r2, r0, #328
	add	r2, r2, #2
	mov	r1, #128
	mov	r3, ip
.L772:
	strh	r1, [r3, #2]!	@ movhi
	cmp	r3, r2
	bne	.L772
	ldr	r3, [r0, #128]
	cmp	r3, #0
	beq	.L789
	ldr	r9, [r0, #152]
	mov	r8, #0
	ldr	r3, .L842+4
	mov	r9, r9, asl #6
	add	r6, r9, #64
	add	r9, r3, r9
	add	r6, r3, r6
.L790:
	sub	r3, fp, #292
	mov	r4, r8, asl #3
	add	r5, r3, r8, lsl #7
	sub	r4, r4, r8, asl #1
	sub	r5, r5, #2
	mov	r2, r9
.L780:
	add	r0, r2, #8
	mov	r1, r5
.L778:
	ldrb	r3, [r2], #1	@ zero_extendqisi2
	add	r3, r4, r3
	cmp	r0, r2
	mov	r3, r3, asl #1
	ldrh	r3, [lr, r3]
	strh	r3, [r1, #2]!	@ movhi
	bne	.L778
	cmp	r0, r6
	add	r5, r5, #16
	mov	r2, r0
	bne	.L780
	add	r8, r8, #1
	cmp	r8, #2
	bne	.L790
.L776:
	cmp	r7, #0
	subeq	r3, fp, #166
	subeq	r1, fp, #38
	beq	.L781
	cmp	r7, #1
	beq	.L837
	cmp	r7, #2
	beq	.L838
.L749:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L752:
	ldr	r4, .L842+8
	add	r1, r0, #152
	sub	ip, fp, #340
	add	r3, r0, #176
.L751:
	ldr	r5, [r1, #4]!
	ldrh	r2, [r4], #2
	cmp	r1, r3
	add	r2, r2, r5
	strh	r2, [ip], #2	@ movhi
	bne	.L751
	cmp	r7, #2
	beq	.L754
	cmp	lr, #0
	cmpeq	r7, #3
	bne	.L755
.L754:
	ldr	ip, .L842
	sub	r1, fp, #328
	add	r5, r0, #200
.L756:
	ldr	r4, [r3, #4]!
	ldrh	r2, [ip, #2]!
	cmp	r3, r5
	add	r2, r2, r4
	strh	r2, [r1], #2	@ movhi
	bne	.L756
.L755:
	cmp	lr, #0
	bne	.L787
.L786:
	ldr	r3, .L842+8
	sub	lr, fp, #316
	add	ip, r3, #12
	mov	r5, lr
	mov	r2, lr
.L759:
	ldrh	r1, [r3], #2
	cmp	r3, ip
	strh	r1, [r2], #2	@ movhi
	bne	.L759
	ldr	r3, .L842
	add	r4, lr, #10
	add	ip, r3, #12
	mov	r2, r4
.L760:
	ldrh	r1, [r3, #2]!
	cmp	r3, ip
	strh	r1, [r2, #2]!	@ movhi
	bne	.L760
	cmp	r7, #0
	beq	.L761
	cmp	r7, #1
	beq	.L839
	cmp	r7, #2
	beq	.L840
	cmp	r7, #3
	bne	.L761
	sub	r3, fp, #340
	sub	r1, fp, #328
.L766:
	ldrh	r2, [r3], #2
	cmp	r3, r1
	strh	r2, [r5], #2	@ movhi
	bne	.L766
	add	r1, lr, #22
.L767:
	ldrh	r2, [r3], #2
	strh	r2, [r4, #2]!	@ movhi
	cmp	r4, r1
	bne	.L767
	b	.L761
.L781:
	ldrh	r2, [r3, #2]!
	cmp	r3, r1
	strh	r2, [ip, #2]!	@ movhi
	beq	.L749
	ldrh	r2, [r3, #2]!
	cmp	r3, r1
	strh	r2, [ip, #2]!	@ movhi
	bne	.L781
	b	.L749
.L789:
	sub	r0, fp, #166
	add	lr, fp, #90
	mov	r1, #128
.L791:
	sub	r3, r0, #128
.L777:
	add	r2, r3, #16
.L774:
	strh	r1, [r3, #2]!	@ movhi
	cmp	r2, r3
	bne	.L774
	cmp	r2, r0
	mov	r3, r2
	bne	.L777
	add	r0, r0, #128
	cmp	r0, lr
	bne	.L791
	b	.L776
.L836:
	cmp	r7, #1
	beq	.L841
	cmp	r7, #2
	bne	.L761
	sub	r2, fp, #328
	add	r3, lr, #10
	add	ip, lr, #22
.L771:
	ldrh	r1, [r2], #2
	strh	r1, [r3, #2]!	@ movhi
	cmp	r3, ip
	bne	.L771
	b	.L761
.L841:
	sub	r3, fp, #340
	sub	ip, fp, #328
	mov	r2, lr
.L770:
	ldrh	r1, [r3], #2
	cmp	r3, ip
	strh	r1, [r2], #2	@ movhi
	bne	.L770
	b	.L761
.L839:
	sub	r3, fp, #340
	sub	r1, fp, #328
.L763:
	ldrh	r2, [r3], #2
	cmp	r3, r1
	strh	r2, [r5], #2	@ movhi
	bne	.L763
	b	.L761
.L838:
	sub	r3, fp, #166
	sub	r1, fp, #38
.L785:
	ldrh	r2, [r3, #2]!
	cmp	r3, r1
	strh	r2, [ip, #2]!	@ movhi
	bne	.L785
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L837:
	sub	r3, fp, #292
	sub	r1, fp, #166
	sub	r3, r3, #2
.L783:
	ldrh	r2, [r3, #2]!
	cmp	r3, r1
	strh	r2, [ip, #2]!	@ movhi
	bne	.L783
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L840:
	sub	r3, fp, #328
	add	r1, lr, #22
.L765:
	ldrh	r2, [r3], #2
	strh	r2, [r4, #2]!	@ movhi
	cmp	r4, r1
	bne	.L765
	b	.L761
.L843:
	.align	2
.L842:
	.word	.LANCHOR1+10
	.word	.LANCHOR0+80
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	Avs_Vfmw_WQMatrix, .-Avs_Vfmw_WQMatrix
	.align	2
	.global	AVS_ParseHeader
	.type	AVS_ParseHeader, %function
AVS_ParseHeader:
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
	add	r7, r0, #12288
	add	r8, r0, #16384
	mov	r3, #0
	add	r9, r0, #14912
	ldr	r6, [r7, #3176]
	add	r5, r0, #15808
	str	r3, [r8, #160]
	mov	r4, r0
	mov	r1, #32
	add	r9, r9, #8
	mov	r0, r6
	add	r5, r5, #4
	bl	BsShow
	uxtb	r0, r0
	sub	r3, r0, #176
	cmp	r3, #78
	ldrls	pc, [pc, r3, asl #2]
	b	.L845
.L847:
	.word	.L846
	.word	.L848
	.word	.L849
	.word	.L850
	.word	.L851
	.word	.L852
	.word	.L853
	.word	.L854
	.word	.L851
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L845
	.word	.L855
.L845:
	cmp	r0, #175
	bhi	.L851
	ldr	r3, [r7, #2784]
	and	r2, r3, #327680
	cmp	r2, #327680
	beq	.L892
.L851:
	mov	r0, r4
	bl	ClearPacket
.L888:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L850:
	ldr	r3, [r7, #2784]
	ands	r6, r3, #32768
	bne	.L886
	tst	r3, #262144
	beq	.L860
	bic	r3, r3, #311296
	mov	r0, r9
	str	r3, [r7, #2784]
	mov	r1, r5
	bl	AVS_i_picture_header
	b	.L890
.L852:
	ldr	r3, [r7, #2784]
	tst	r3, #327680
	beq	.L864
	mov	r1, r5
	mov	r0, r9
	bl	AVS_extension
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L853:
	ldr	r3, [r7, #2784]
	ands	r6, r3, #32768
	bne	.L886
	tst	r3, #262144
	beq	.L862
	bic	r3, r3, #311296
	mov	r0, r9
	str	r3, [r7, #2784]
	mov	r1, r5
	bl	AVS_pb_picture_header
.L890:
	mov	r0, r5
	bl	Avs_Vfmw_WQMatrix
	mov	r0, r4
	bl	ClearPacket
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L854:
	ldr	r3, [r7, #2784]
	ands	r5, r3, #32768
	bne	.L885
	tst	r3, #327680
	beq	.L888
.L891:
	bic	r3, r3, #311296
	mov	r0, r4
	str	r3, [r7, #2784]
	bl	ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L855:
	mov	r1, #32
	mov	r0, r6
	bl	BsSkip
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
	bne	.L864
	mov	r5, #1
	strb	r5, [r4]
	str	r5, [r8, #160]
	mov	r0, r4
	ldr	r3, [r7, #2784]
	orr	r3, r3, #16384
	str	r3, [r7, #2784]
	bl	ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L848:
	ldr	r3, [r7, #2784]
	ands	r5, r3, #32768
	bne	.L885
	tst	r3, #327680
	beq	.L851
	b	.L891
.L849:
	ldr	r3, [r7, #2784]
	ands	r1, r3, #262144
	movne	r1, #1
	bne	.L887
	tst	r3, #65536
	beq	.L864
.L887:
	mov	r0, r4
	bl	AVS_user_data
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L846:
	ldr	r3, [r7, #2784]
	ands	r6, r3, #32768
	bne	.L885
	tst	r3, #65536
	beq	.L858
	bic	r3, r3, #311296
	mov	r1, r5
	str	r3, [r7, #2784]
	mov	r0, r4
	bl	AVS_sequence_header
	mov	r0, r4
	bl	ClearPacket
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L892:
	orr	r3, r3, #32768
	mov	r0, r4
	str	r3, [r7, #2784]
	bl	WriteAvsSliceMsg
	cmp	r0, #0
	bne	.L888
.L864:
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L885:
	mov	r0, #1
	orr	r3, r3, #16384
	str	r0, [r8, #160]
	str	r3, [r7, #2784]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L862:
	mov	r0, r9
	mov	r1, r5
	bl	AVS_pb_picture_header
.L889:
	mov	r0, r5
	bl	Avs_Vfmw_WQMatrix
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L860:
	mov	r0, r9
	mov	r1, r5
	bl	AVS_i_picture_header
	b	.L889
.L858:
	mov	r1, r5
	mov	r0, r4
	bl	AVS_sequence_header
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L886:
	orr	r3, r3, #16384
	mov	r0, r5
	mov	r4, #1
	str	r4, [r8, #160]
	str	r3, [r7, #2784]
	bl	Avs_Vfmw_WQMatrix
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_ParseHeader, .-AVS_ParseHeader
	.align	2
	.global	AVSDEC_Decode
	.type	AVSDEC_Decode, %function
AVSDEC_Decode:
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
	mov	r5, r1
	beq	.L907
	add	r0, r0, #15744
	ldr	r2, [r1, #16]
	add	r0, r0, #36
	ldr	r1, [r1]
	bl	BsInit
	ldr	r3, .L910
	add	r6, r4, #12288
	add	r0, r4, #16384
	mov	r1, r5
	mov	r2, #160
	ldr	r3, [r3, #52]
	add	r0, r0, #168
	blx	r3
	ldr	r3, [r6, #2784]
	mov	r0, r4
	str	r3, [r6, #3488]
	bl	AVS_ParseHeader
	subs	r5, r0, #0
	beq	.L908
	ldr	r3, [r6, #2784]
	and	r3, r3, #376832
	cmp	r3, #376832
	beq	.L897
.L898:
	mov	r5, #0
.L895:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L907:
	mov	r0, #0
	movw	r2, #3019
	mov	r5, r0
	ldr	r1, .L910+4
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L908:
	ldr	r1, .L910+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	AVS_ClearCurPic
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L897:
	mov	r0, r4
	bl	AVS_DecodeArbiter.part.5
	cmp	r0, #0
	beq	.L898
	mov	r0, r4
	bl	AVS_GetStreamInf
	cmp	r0, #3
	beq	.L899
	adds	r5, r0, #0
	movne	r5, #1
	cmp	r5, #0
	beq	.L909
	mov	r0, r4
	bl	AVS_StartDecode
	subs	r6, r0, #0
	bne	.L895
	ldr	r1, .L910+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	AVS_ClearCurPic
	mov	r5, r6
	b	.L895
.L909:
	ldr	r1, .L910+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	AVS_ClearCurPic
	b	.L895
.L899:
	ldr	r3, [r6, #3488]
	mov	r5, r0
	str	r3, [r6, #2784]
	b	.L895
.L911:
	.align	2
.L910:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC97
	.word	.LC111
	.word	.LC113
	.word	.LC112
	UNWIND(.fnend)
	.size	AVSDEC_Decode, .-AVSDEC_Decode
	.global	g_tmp
	.global	wq_param_default
	.global	g_AvsCfg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	frame_rate_Table, %object
	.size	frame_rate_Table, 64
frame_rate_Table:
	.word	0
	.word	24551
	.word	24576
	.word	25600
	.word	30689
	.word	30720
	.word	51200
	.word	61378
	.word	61440
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.type	CSWTCH.56, %object
	.size	CSWTCH.56, 16
CSWTCH.56:
	.word	5
	.word	1
	.word	2
	.word	3
	.type	WeightQuantModel, %object
	.size	WeightQuantModel, 256
WeightQuantModel:
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
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	3
	.byte	2
	.byte	1
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
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	5
	.byte	5
	.byte	5
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	1
	.byte	1
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
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	wq_param_default, %object
	.size	wq_param_default, 24
wq_param_default:
	.short	135
	.short	143
	.short	143
	.short	160
	.short	160
	.short	213
	.short	128
	.short	98
	.short	106
	.short	116
	.short	116
	.short	128
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%-40s     %#-8x(%db)\012\000" )
	.space	2
.LC1:
	ASCII(.ascii	"video_sequence_start_code\000" )
	.space	2
.LC2:
	ASCII(.ascii	"profile_id\000" )
	.space	1
.LC3:
	ASCII(.ascii	"level_id\000" )
	.space	3
.LC4:
	ASCII(.ascii	"progressive_sequence\000" )
	.space	3
.LC5:
	ASCII(.ascii	"horizontal_size\000" )
.LC6:
	ASCII(.ascii	"vertical_size\000" )
	.space	2
.LC7:
	ASCII(.ascii	"chroma_format\000" )
	.space	2
.LC8:
	ASCII(.ascii	"sample_precision\000" )
	.space	3
.LC9:
	ASCII(.ascii	"aspect_ratio\000" )
	.space	3
.LC10:
	ASCII(.ascii	"frame_rate_code\000" )
.LC11:
	ASCII(.ascii	"bit_rate_lower\000" )
	.space	1
.LC12:
	ASCII(.ascii	"marker_bit\000" )
	.space	1
.LC13:
	ASCII(.ascii	"bit_rate_upper\000" )
	.space	1
.LC14:
	ASCII(.ascii	"low_delay\000" )
	.space	2
.LC15:
	ASCII(.ascii	"bbv_buffer_size\000" )
.LC16:
	ASCII(.ascii	"reserved_bits\000" )
	.space	2
.LC17:
	ASCII(.ascii	"i_picture_start_code\000" )
	.space	3
.LC18:
	ASCII(.ascii	"bbv_delay\000" )
	.space	2
.LC19:
	ASCII(.ascii	"bbv_delay_extension\000" )
.LC20:
	ASCII(.ascii	"time_code_flag\000" )
	.space	1
.LC21:
	ASCII(.ascii	"time_code\000" )
	.space	2
.LC22:
	ASCII(.ascii	"picture_distance\000" )
	.space	3
.LC23:
	ASCII(.ascii	"bbv_check_times\000" )
.LC24:
	ASCII(.ascii	"progressive_frame\000" )
	.space	2
.LC25:
	ASCII(.ascii	"picture_structure\000" )
	.space	2
.LC26:
	ASCII(.ascii	"top_field_first\000" )
.LC27:
	ASCII(.ascii	"repeat_first_field\000" )
	.space	1
.LC28:
	ASCII(.ascii	"fixed_picture_qp\000" )
	.space	3
.LC29:
	ASCII(.ascii	"picture_qp\000" )
	.space	1
.LC30:
	ASCII(.ascii	"skip_mode_flag\000" )
	.space	1
.LC31:
	ASCII(.ascii	"loop_filter_disable\000" )
.LC32:
	ASCII(.ascii	"loop_filter_parameter_flag\000" )
	.space	1
.LC33:
	ASCII(.ascii	"alpha_c_offset\000" )
	.space	1
.LC34:
	ASCII(.ascii	"beta_offset\000" )
.LC35:
	ASCII(.ascii	"weighting_quant_flag\000" )
	.space	3
.LC36:
	ASCII(.ascii	"aec_enable\000" )
	.space	1
.LC37:
	ASCII(.ascii	"mb_adapt_weighting_quant_disable\000" )
	.space	3
.LC38:
	ASCII(.ascii	"chroma_quant_param_disable\000" )
	.space	1
.LC39:
	ASCII(.ascii	"chroma_quant_param_delta_u\000" )
	.space	1
.LC40:
	ASCII(.ascii	"chroma_quant_param_delta_v\000" )
	.space	1
.LC41:
	ASCII(.ascii	"weighting_quant_param_index\000" )
.LC42:
	ASCII(.ascii	"weighting_quant_model\000" )
	.space	2
.LC43:
	ASCII(.ascii	"weighting_quant_param_deltal1\000" )
	.space	2
.LC44:
	ASCII(.ascii	"weighting_quant_param_deltal2\000" )
	.space	2
.LC45:
	ASCII(.ascii	"pb_picture_start_code\000" )
	.space	2
.LC46:
	ASCII(.ascii	"picture_coding_type\000" )
.LC47:
	ASCII(.ascii	"advanced_pred_mode_disable\000" )
	.space	1
.LC48:
	ASCII(.ascii	"picture_reference_flag\000" )
	.space	1
.LC49:
	ASCII(.ascii	"no_forward_reference_flag\000" )
	.space	2
.LC50:
	ASCII(.ascii	"b_filed_enhanced_flag\000" )
	.space	2
.LC51:
	ASCII(.ascii	"p_filed_enhanced_flag\000" )
	.space	2
.LC52:
	ASCII(.ascii	"user_data_start_code\000" )
	.space	3
.LC53:
	ASCII(.ascii	"extension_ID\000" )
	.space	3
.LC54:
	ASCII(.ascii	"video_format\000" )
	.space	3
.LC55:
	ASCII(.ascii	"sample_range\000" )
	.space	3
.LC56:
	ASCII(.ascii	"colour_description\000" )
	.space	1
.LC57:
	ASCII(.ascii	"colour_primaries\000" )
	.space	3
.LC58:
	ASCII(.ascii	"transfer_characteristics\000" )
	.space	3
.LC59:
	ASCII(.ascii	"matrix_coefficients\000" )
.LC60:
	ASCII(.ascii	"display_horizontal_size\000" )
.LC61:
	ASCII(.ascii	"display_vertical_size\000" )
	.space	2
.LC62:
	ASCII(.ascii	"copyright_flag\000" )
	.space	1
.LC63:
	ASCII(.ascii	"copyright_id\000" )
	.space	3
.LC64:
	ASCII(.ascii	"original_or_copy\000" )
	.space	3
.LC65:
	ASCII(.ascii	"copyright_number_1\000" )
	.space	1
.LC66:
	ASCII(.ascii	"copyright_number_2\000" )
	.space	1
.LC67:
	ASCII(.ascii	"copyright_number_3\000" )
	.space	1
.LC68:
	ASCII(.ascii	"camera_id\000" )
	.space	2
.LC69:
	ASCII(.ascii	"height_of_image_device\000" )
	.space	1
.LC70:
	ASCII(.ascii	"focal_length\000" )
	.space	3
.LC71:
	ASCII(.ascii	"f_number\000" )
	.space	3
.LC72:
	ASCII(.ascii	"vertical_angle_of_view\000" )
	.space	1
.LC73:
	ASCII(.ascii	"camera_position_x_upper\000" )
.LC74:
	ASCII(.ascii	"camera_position_x_lower\000" )
.LC75:
	ASCII(.ascii	"camera_position_y_upper\000" )
.LC76:
	ASCII(.ascii	"camera_position_y_lower\000" )
.LC77:
	ASCII(.ascii	"camera_position_z_upper\000" )
.LC78:
	ASCII(.ascii	"camera_position_z_lower\000" )
.LC79:
	ASCII(.ascii	"camera_direction_x\000" )
	.space	1
.LC80:
	ASCII(.ascii	"camera_direction_y\000" )
	.space	1
.LC81:
	ASCII(.ascii	"camera_direction_z\000" )
	.space	1
.LC82:
	ASCII(.ascii	"image_plane_vertical_x\000" )
	.space	1
.LC83:
	ASCII(.ascii	"image_plane_vertical_y\000" )
	.space	1
.LC84:
	ASCII(.ascii	"image_plane_vertical_z\000" )
	.space	1
.LC85:
	ASCII(.ascii	"frame_centre_horizontal_offset\000" )
	.space	1
.LC86:
	ASCII(.ascii	"frame_centre_vertical_offset\000" )
	.space	3
.LC87:
	ASCII(.ascii	"extension_start_code\000" )
	.space	3
.LC88:
	ASCII(.ascii	"ERROR: image size abnormal(%dx%d)\012\000" )
	.space	1
.LC89:
	ASCII(.ascii	"avs actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC90:
	ASCII(.ascii	"ERROR: partition fs memory fail!\012\000" )
	.space	2
.LC91:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC92:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"line: %d pImage is null\012\000" )
	.space	3
.LC94:
	ASCII(.ascii	"ERROR: get frame store fail!\012\000" )
	.space	2
.LC95:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC96:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC97:
	ASCII(.ascii	"line: %d\012\000" )
	.space	2
.LC98:
	ASCII(.ascii	"ERROR: AVS_OutputOneFrame is err(%d)\012\000" )
	.space	2
.LC99:
	ASCII(.ascii	"size change\012\000" )
	.space	3
.LC100:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC101:
	ASCII(.ascii	"MbWidth = %d, MbHeight = %d, don't support!\012\000" )
	.space	3
.LC102:
	ASCII(.ascii	"ERROR: allocate vhb\012\000" )
	.space	3
.LC103:
	ASCII(.ascii	"ERROR: get img buf err\012\000" )
.LC104:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC105:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC106:
	ASCII(.ascii	"-----Pic %5d, type %d, struct %d-----\012\000" )
	.space	1
.LC107:
	ASCII(.ascii	"ERROR: err_level(%d) over ref_thr(%d)\012\000" )
	.space	1
.LC108:
	ASCII(.ascii	"ERROR: err_level(%d) over out_thr(%d)\012\000" )
	.space	1
.LC109:
	ASCII(.ascii	"SlcNum %d > %d Write slice msg failed\012\000" )
	.space	1
.LC110:
	ASCII(.ascii	"This slice's start mbn %d <= LastSliceFirstMb %d, W" )
	ASCII(.ascii	"rite slice msg failed\012\000" )
	.space	2
.LC111:
	ASCII(.ascii	"ERROR: paseHeader err\012\000" )
	.space	1
.LC112:
	ASCII(.ascii	"ERROR: AVS_PrepareDecode err\012\000" )
	.space	2
.LC113:
	ASCII(.ascii	"ERROR: AVS_StartDecode err\012\000" )
	.bss
	.align	2
	.type	g_tmp, %object
	.size	g_tmp, 1024
g_tmp:
	.space	1024
	.type	g_AvsCfg, %object
	.size	g_AvsCfg, 508
g_AvsCfg:
	.space	508
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
