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
	.file	"syntax.c"
	.text
	.align	2
	.type	SYNTAX_GetVoQue, %function
SYNTAX_GetVoQue:
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
	ldr	r3, [r0]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L18
.L4:
	.word	.L17
	.word	.L5
	.word	.L6
	.word	.L7
	.word	.L18
	.word	.L8
	.word	.L9
	.word	.L18
	.word	.L10
	.word	.L11
	.word	.L12
	.word	.L12
	.word	.L12
	.word	.L13
	.word	.L18
	.word	.L14
	.word	.L15
	.word	.L16
	.word	.L18
	.word	.L18
	.word	.L17
.L17:
	add	r0, r0, #16
	ldmfd	sp, {fp, sp, pc}
.L5:
	add	r0, r0, #49152
	add	r0, r0, #176
	ldmfd	sp, {fp, sp, pc}
.L6:
	add	r0, r0, #22528
	add	r0, r0, #104
	ldmfd	sp, {fp, sp, pc}
.L7:
	add	r0, r0, #88064
	add	r0, r0, #648
	ldmfd	sp, {fp, sp, pc}
.L8:
	add	r0, r0, #42496
	add	r0, r0, #40
	ldmfd	sp, {fp, sp, pc}
.L9:
	add	r0, r0, #16192
	add	r0, r0, #8
	ldmfd	sp, {fp, sp, pc}
.L10:
	add	r0, r0, #54784
	add	r0, r0, #80
	ldmfd	sp, {fp, sp, pc}
.L11:
	add	r0, r0, #54784
	add	r0, r0, #72
	ldmfd	sp, {fp, sp, pc}
.L12:
	add	r0, r0, #12672
	add	r0, r0, #24
	ldmfd	sp, {fp, sp, pc}
.L13:
	add	r0, r0, #8192
	add	r0, r0, #24
	ldmfd	sp, {fp, sp, pc}
.L14:
	add	r0, r0, #592
	ldmfd	sp, {fp, sp, pc}
.L15:
	add	r0, r0, #5568
	add	r0, r0, #24
	ldmfd	sp, {fp, sp, pc}
.L16:
	add	r0, r0, #274432
	add	r0, r0, #1408
	ldmfd	sp, {fp, sp, pc}
.L18:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SYNTAX_GetVoQue, .-SYNTAX_GetVoQue
	.align	2
	.global	PrintVoQueue
	.type	PrintVoQueue, %function
PrintVoQueue:
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
	subs	r5, r0, #0
	beq	.L26
	ldrh	ip, [r5, #8]
	mov	r0, #1
	ldrh	r3, [r5, #4]
	ldrh	r2, [r5, #6]
	ldr	r1, .L27
	str	ip, [sp]
	bl	dprint_vfmw
	ldrh	r3, [r5, #4]
	ldrh	r2, [r5, #8]
	and	r4, r3, #63
	cmp	r2, r4
	bne	.L25
	b	.L24
.L23:
	add	r3, r5, r4, lsl #2
	ldr	r1, .L27+4
	mov	r0, #1
	ldr	r3, [r3, #12]
	ldr	r2, [r3, #148]
	bl	dprint_vfmw
	add	r3, r4, #1
	ldrh	r2, [r5, #8]
	and	r4, r3, #63
	cmp	r2, r4
	beq	.L24
.L25:
	tst	r3, #7
	bne	.L23
	ldr	r1, .L27+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L23
.L24:
	ldr	r1, .L27+8
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L26:
	mov	r3, #78
	ldr	r2, .L27+12
	ldr	r1, .L27+16
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L28:
	.align	2
.L27:
	.word	.LC1
	.word	.LC3
	.word	.LC2
	.word	.LANCHOR0
	.word	.LC0
	UNWIND(.fnend)
	.size	PrintVoQueue, .-PrintVoQueue
	.align	2
	.global	ResetVoQueue
	.type	ResetVoQueue, %function
ResetVoQueue:
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
	subs	r4, r0, #0
	beq	.L34
	ldr	r5, .L36
	mov	r0, #2
	ldr	r3, [r5, #12]
	blx	r3
	ldrh	r2, [r4, #6]
	ldrh	r3, [r4, #4]
	ldrh	r1, [r4, #8]
	cmp	r2, r3
	beq	.L35
.L32:
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L36+4
	bl	dprint_vfmw
.L33:
	ldr	r2, [r4, #344]
	add	r1, r4, #336
	mov	r3, #0
	mov	r0, #64
	strh	r3, [r4, #2]	@ movhi
	add	r2, r2, #100
	strh	r0, [r4]	@ movhi
	mvn	r6, #0
	str	r2, [r4, #344]
	mvn	r7, #0
	mvn	r2, #0
	strh	r3, [r4, #4]	@ movhi
	strh	r3, [r4, #6]	@ movhi
	mov	r8, #0
	strh	r3, [r4, #8]	@ movhi
	mov	r9, #0
	str	r3, [r4, #316]
	mov	r0, #2
	str	r2, [r4, #272]
	str	r2, [r4, #292]
	str	r2, [r4, #288]
	str	r2, [r4, #284]
	str	r2, [r4, #276]
	str	r2, [r4, #280]
	ldr	ip, [r5, #16]
	strd	r6, [r1, #-8]
	str	r3, [r4, #324]
	strd	r8, [r1]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L35:
	cmp	r2, r1
	bne	.L32
	b	.L33
.L34:
	mov	r3, #107
	ldr	r2, .L36+8
	ldr	r1, .L36+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L37:
	.align	2
.L36:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LANCHOR0+16
	.word	.LC0
	UNWIND(.fnend)
	.size	ResetVoQueue, .-ResetVoQueue
	.align	2
	.global	ReturnImageToSyntax
	.type	ReturnImageToSyntax, %function
ReturnImageToSyntax:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r3, r1
	beq	.L56
	cmp	r0, #20
	ldrls	pc, [pc, r0, asl #2]
	b	.L38
.L42:
	.word	.L41
	.word	.L43
	.word	.L44
	.word	.L45
	.word	.L38
	.word	.L46
	.word	.L47
	.word	.L38
	.word	.L48
	.word	.L49
	.word	.L50
	.word	.L50
	.word	.L50
	.word	.L51
	.word	.L38
	.word	.L52
	.word	.L53
	.word	.L54
	.word	.L38
	.word	.L38
	.word	.L55
.L56:
	mov	r3, #151
	ldr	r2, .L57
	ldr	r1, .L57+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L55:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	USERDEC_RecycleImage
.L41:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_RecycleImage
.L43:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_RecycleImage
.L44:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_RecycleImage
.L45:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_RecycleImage
.L46:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_RecycleImage
.L47:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_RecycleImage
.L48:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_RecycleImage
.L49:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_RecycleImage
.L50:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_RecycleImage
.L51:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_RecycleImage
.L52:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_RecycleImage
.L53:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_DECRecycleImage
.L54:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_RecycleImage
.L38:
	ldmfd	sp, {fp, sp, pc}
.L58:
	.align	2
.L57:
	.word	.LANCHOR0+32
	.word	.LC0
	UNWIND(.fnend)
	.size	ReturnImageToSyntax, .-ReturnImageToSyntax
	.global	__aeabi_uidiv
	.align	2
	.global	InsertImgToVoQueue
	.type	InsertImgToVoQueue, %function
InsertImgToVoQueue:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 24
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
	cmp	r0, #31
	mov	r5, r3
	mov	r7, r0
	str	r1, [fp, #-56]
	mov	r10, r2
	ldr	r4, [fp, #4]
	movhi	r3, #396
	bhi	.L127
	cmp	r5, #0
	cmpne	r2, #0
	beq	.L129
	cmp	r4, #0
	beq	.L130
	ldr	r6, .L138
	mov	r0, #2
	ldr	r1, .L138+4
	bl	dprint_vfmw
	mov	r0, #2
	ldr	r3, [r6, #12]
	blx	r3
	ldrh	r9, [r5, #4]
	ldrh	r0, [r5, #8]
	and	r9, r9, #63
	cmp	r0, r9
	ldrne	r8, [fp, #-56]
	bne	.L69
	b	.L68
.L67:
	add	r9, r9, #1
	and	r9, r9, #63
	cmp	r0, r9
	beq	.L131
.L69:
	add	r3, r5, r9, lsl #2
	ldr	r1, [r4, #148]
	ldr	r3, [r3, #12]
	ldr	r2, [r3, #148]
	cmp	r2, r1
	bne	.L67
	ldr	r1, .L138+8
	mov	r0, #0
	bl	dprint_vfmw
	add	r9, r9, #1
	mov	r3, #1000
	str	r3, [r4, #152]
	ldrh	r0, [r5, #8]
	and	r9, r9, #63
	cmp	r0, r9
	bne	.L69
.L131:
	str	r8, [fp, #-56]
.L68:
	ldr	r2, [r4, #152]
	cmp	r2, #100
	bhi	.L132
	ldr	r3, [r4, #68]
	ldr	r1, [r4, #72]
	cmp	r3, #31
	bhi	.L133
.L70:
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L138+12
	bl	dprint_vfmw
	ldr	r3, [r4, #152]
	cmp	r3, #1000
	beq	.L73
	mov	r2, r4
	mov	r1, r10
	ldr	r0, [fp, #-56]
	bl	ReturnImageToSyntax
.L73:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, #1
.L61:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L133:
	cmp	r1, #31
	bls	.L70
	ldr	r8, [fp, #-56]
	add	r1, r4, #416
	mov	r0, r7
	str	r8, [r4, #216]
	bl	VCTRL_GetHDRConfigInfo
	ldr	r3, .L138+16
	ldrb	r2, [r4, #66]	@ zero_extendqisi2
	add	ip, r4, #592
	add	lr, r4, #576
	cmp	r8, #20
	ldr	r3, [r3, r7, asl #2]
	ldr	r3, [r3, #128]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	bfi	r2, r3, #2, #1
	strb	r2, [r4, #66]
	ldrd	r0, [ip, #-8]
	strd	r0, [lr]
	beq	.L93
	add	r3, r5, #272
	ldrd	r2, [r3, #56]
	subs	r8, r0, r2
	sbc	r9, r1, r3
	and	r3, r3, r2
	cmp	r9, #0
	cmpeq	r8, #5
	movls	r2, #1
	movhi	r2, #0
	adds	r3, r3, #1
	movne	r3, #1
	tst	r2, r3
	ldr	r3, [fp, #-56]
	sub	r8, r3, #8
	beq	.L134
	cmp	r8, #1
	bls	.L76
	mov	r2, r0
	mov	r3, r1
	mvn	r0, #0
	mvn	r1, #0
	b	.L74
.L132:
	ldr	r3, [r4, #68]
	ldr	r1, [r4, #72]
	b	.L70
.L134:
	cmp	r8, #1
	bls	.L135
.L93:
	mov	r2, r0
	mov	r3, r1
.L74:
	ldrd	r8, [ip]
	strd	r0, [ip, #-8]
	strd	r0, [sp]
	mov	r0, #29
	strd	r8, [sp, #8]
	ldr	r1, .L138+20
	bl	dprint_vfmw
	ldr	r3, [r4, #76]
	cmp	r3, #0
	beq	.L77
	ldr	r3, [r4, #80]
	cmp	r3, #0
	ldrne	r2, [r4, #68]
	beq	.L77
.L78:
	str	r2, [r5, #300]
	ldr	r3, [r4, #72]
	ldr	r1, [r5, #280]
	str	r3, [r5, #304]
	ldrb	r3, [r4, #64]	@ zero_extendqisi2
	mov	r3, r3, lsr #5
	str	r3, [r5, #308]
	ldr	r3, [r4, #64]
	str	r3, [r5, #312]
	ldr	r3, [r4, #148]
	add	r3, r3, #2
	str	r3, [r5, #296]
	ldrb	r0, [r4, #65]	@ zero_extendqisi2
	ldr	r3, [r4, #156]
	ubfx	r0, r0, #0, #2
	ldr	r2, [r4, #64]
	cmp	r3, r1
	ldr	ip, [r4, #80]
	ldrh	r9, [r4, #76]
	mov	lr, r0
	ldrh	r1, [r4, #88]
	ubfx	r2, r2, #14, #3
	strb	r0, [fp, #-65]
	uxtb	lr, lr
	ldr	r0, [r4, #84]
	uxtb	r10, r2
	strne	r3, [r5, #320]
	orr	r9, r9, ip, asl #16
	ldr	r3, [r5, #316]
	orr	r1, r1, r0, asl #16
	str	r1, [fp, #-64]
	add	r1, r3, #1
	str	r1, [r5, #316]
	str	r3, [r4, #160]
	ldr	r3, [r5, #272]
	str	lr, [fp, #-60]
	cmp	r10, r3
	ldreq	r3, .L138+24
	streq	r3, [fp, #-56]
	beq	.L80
	ldr	r1, .L138+24
	ldr	r8, [r1]
	str	r1, [fp, #-56]
	cmp	r8, #0
	beq	.L81
	strb	r3, [fp, #-52]
	mov	r1, #7
	strb	r2, [fp, #-51]
	mov	r3, #2
	sub	r2, fp, #52
	mov	r0, r7
	blx	r8
.L81:
	str	r10, [r5, #272]
.L80:
	ldr	r3, [r5, #276]
	ldr	r2, [fp, #-60]
	cmp	r2, r3
	beq	.L82
	ldr	r3, [fp, #-56]
	ldr	r8, [r3]
	cmp	r8, #0
	beq	.L83
	ldrb	r1, [fp, #-65]	@ zero_extendqisi2
	sub	r2, fp, #44
	mov	r3, #1
	mov	r0, r7
	strb	r1, [r2, #-8]!
	mov	r1, #4
	blx	r8
.L83:
	ldr	r3, [fp, #-60]
	str	r3, [r5, #276]
.L82:
	ldr	r3, [r5, #288]
	cmp	r9, r3
	beq	.L136
.L84:
	ldr	r3, [fp, #-56]
	str	r9, [r5, #288]
	ldr	r8, [r3]
	ldr	r3, [fp, #-64]
	cmp	r8, #0
	str	r3, [r5, #292]
	beq	.L85
	ldr	r1, [r4, #80]
	mov	r3, #8
	ldr	r0, [r4, #84]
	sub	r2, fp, #52
	ldr	lr, [r4, #76]
	ldr	ip, [r4, #88]
	strh	r1, [fp, #-50]	@ movhi
	mov	r1, #1
	strh	r0, [fp, #-48]	@ movhi
	mov	r0, r7
	strh	lr, [fp, #-52]	@ movhi
	strh	ip, [fp, #-46]	@ movhi
	blx	r8
.L85:
	ldr	ip, [r4, #36]
	mov	r0, #12
	ldr	r1, [r4, #40]
	mov	r10, r7, asl #3
	ldr	r2, [r4, #112]
	mov	r8, r7, asl #5
	ldr	r3, [r4, #116]
	str	r1, [r4, #24]
	add	r2, r2, ip
	str	ip, [r4, #20]
	add	r3, r3, r1
	str	r2, [r4, #28]
	str	r3, [r4, #32]
	ldr	r1, [r4, #148]
	ldrh	ip, [r5, #8]
	ldrh	r3, [r5, #6]
	ldrh	r2, [r5, #4]
	str	ip, [sp]
	str	r1, [sp, #4]
	ldr	r1, .L138+28
	bl	dprint_vfmw
	ldrh	r3, [r5, #8]
	ldr	r9, .L138+32
	mov	ip, #0
	mov	r1, #5
	add	r2, r5, r3, lsl #2
	add	r3, r3, #1
	and	r3, r3, #63
	str	r4, [r2, #12]
	rsb	r2, r10, r8
	strh	r3, [r5, #8]	@ movhi
	add	r2, r9, r2
	ldr	r3, .L138+16
	ldr	r3, [r3, r7, asl #2]
	add	r3, r3, #475136
	ldr	r0, [r3, #1328]
	add	r0, r0, #1
	str	r0, [r3, #1328]
	ldr	r3, [r4, #52]
	mov	r0, r7
	str	ip, [r4, #264]
	str	r3, [r2, #20]
	ldr	r2, [r4, #160]
	bl	VDEC_Lowdelay_Event_Time
	ldr	r1, .L138+36
	ldr	r3, [r4, #160]
	mov	r0, #2
	ldr	r2, [r6, #16]
	add	r3, r3, #1
	str	r3, [r1, r7, asl #2]
	blx	r2
	ldr	r3, [fp, #-56]
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L87
	mov	r2, r4
	mov	r3, #640
	mov	r1, #5
	mov	r0, r7
	blx	r5
.L87:
	mov	r0, #8
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L137
.L89:
	rsb	r7, r10, r8
	ldr	r2, [r6]
	add	r4, r9, r7
	ldr	r3, [r4, #4]
	add	r3, r3, #1
	str	r3, [r4, #4]
	blx	r2
	ldr	r1, [r9, r7]
	rsb	r1, r1, r0
	mov	r5, r0
	cmp	r1, #300
	movcc	r0, #1
	bcc	.L61
	ldr	r3, [r4, #4]
	cmp	r3, #0
	beq	.L91
	movw	r0, #10000
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	str	r0, [r4, #8]
.L91:
	rsb	r8, r10, r8
	mov	r2, #0
	add	r3, r9, r8
	mov	r0, #1
	str	r5, [r9, r8]
	str	r2, [r3, #4]
	b	.L61
.L77:
	ldr	r2, [r4, #68]
	ldr	r3, [r4, #72]
	mov	r1, r2, lsr #1
	str	r2, [r4, #76]
	str	r3, [r4, #80]
	mov	r3, r3, lsr #1
	str	r1, [r4, #84]
	str	r3, [r4, #88]
	b	.L78
.L135:
	ldrb	r3, [r4, #64]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L93
.L76:
	mvn	r9, #0
	str	r9, [lr]
	mov	r2, r9
	mov	r0, r9
	mov	r3, r9
	str	r9, [lr, #4]
	mov	r1, r9
	b	.L74
.L129:
	movw	r3, #397
.L127:
	ldr	r2, .L138+40
	mov	r0, #1
	ldr	r1, .L138+44
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L61
.L137:
	ldr	r3, [r6]
	blx	r3
	ldr	r1, .L138+48
	ldr	r2, .L138+52
	ldr	r3, [r1, r7, asl #2]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	cmp	r3, r2
	bls	.L89
	mov	r2, r7, asl #24
	str	r0, [r1, r7, asl #2]
	add	r2, r2, #524288
	movw	r1, #515
	ldr	r0, .L138+56
	bl	DBG_AddTrace
	b	.L89
.L136:
	ldr	r3, [r5, #292]
	ldr	r2, [fp, #-64]
	cmp	r2, r3
	bne	.L84
	b	.L85
.L130:
	mov	r0, r4
	ldr	r1, .L138+60
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L61
.L139:
	.align	2
.L138:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	s_pstVfmwChan
	.word	.LC9
	.word	g_event_report
	.word	.LC10
	.word	g_VfmwChanStat
	.word	g_LowDelaySeqIndex
	.word	.LANCHOR0+52
	.word	.LC0
	.word	.LANCHOR1
	.word	g_TraceFramePeriod
	.word	.LANCHOR0+72
	.word	.LC5
	UNWIND(.fnend)
	.size	InsertImgToVoQueue, .-InsertImgToVoQueue
	.align	2
	.global	GetQueueImgNum
	.type	GetQueueImgNum, %function
GetQueueImgNum:
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
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L147
	ldrh	r3, [r0, #6]
	ldrh	ip, [r0, #4]
	ldrh	r0, [r0, #8]
	cmp	r3, ip
	addcc	lr, r3, #64
	rsbcs	ip, ip, r3
	rsbcc	ip, ip, lr
	cmp	r3, r0
	addhi	r0, r0, #64
	str	ip, [r1]
	rsb	r3, r3, r0
	str	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
.L147:
	mov	r3, #556
	ldr	r2, .L148
	ldr	r1, .L148+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L149:
	.align	2
.L148:
	.word	.LANCHOR0+92
	.word	.LC0
	UNWIND(.fnend)
	.size	GetQueueImgNum, .-GetQueueImgNum
	.align	2
	.global	SYNTAX_ReceiveImage
	.type	SYNTAX_ReceiveImage, %function
SYNTAX_ReceiveImage:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r8, r1
	beq	.L156
	bl	SYNTAX_GetVoQue
	subs	r4, r0, #0
	beq	.L157
	ldr	r9, .L158
	mov	r0, #2
	ldr	r3, [r9, #12]
	blx	r3
	ldrh	r3, [r4, #6]
	ldrh	r2, [r4, #8]
	cmp	r2, r3
	mvneq	r5, #2
	beq	.L154
	add	r10, r8, #496
	add	r3, r4, r3, lsl #2
	mov	r2, #640
	mov	r0, r8
	ldrd	r6, [r10]
	mov	r5, #1
	ldr	r1, [r3, #12]
	ldr	r3, [r9, #52]
	blx	r3
	strd	r6, [r10]
	ldr	ip, [r8, #148]
	mov	r0, #12
	ldrh	r3, [r4, #6]
	ldrh	r2, [r4, #4]
	str	ip, [sp, #4]
	ldrh	ip, [r4, #8]
	ldr	r1, .L158+4
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r8, #148]
	ldr	r2, [r4, #344]
	add	r3, r3, r2
	str	r3, [r8, #148]
	ldrh	r3, [r4, #6]
	add	r3, r3, r5
	and	r3, r3, #63
	strh	r3, [r4, #6]	@ movhi
.L154:
	ldr	r3, [r9, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r5
.L152:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L156:
	movw	r3, #671
	ldr	r2, .L158+8
	ldr	r1, .L158+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L152
.L157:
	ldr	r2, .L158+8
	mov	r0, #1
	ldr	r1, .L158+16
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L152
.L159:
	.align	2
.L158:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC12
	.word	.LANCHOR0+108
	.word	.LC0
	.word	.LC11
	UNWIND(.fnend)
	.size	SYNTAX_ReceiveImage, .-SYNTAX_ReceiveImage
	.align	2
	.global	SYNTAX_ReleaseImage
	.type	SYNTAX_ReleaseImage, %function
SYNTAX_ReleaseImage:
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
	cmp	r0, #0
	cmpne	r1, #0
	mov	r6, r1
	mov	r7, r0
	beq	.L207
	bl	SYNTAX_GetVoQue
	subs	r5, r0, #0
	beq	.L208
	ldr	r8, .L209
	mov	r0, #2
	ldr	r3, [r8, #12]
	blx	r3
	ldrh	r4, [r5, #4]
	ldrh	r2, [r5, #6]
	and	r4, r4, #63
	ldr	r9, [r6, #148]
	ldr	r3, [r5, #344]
	cmp	r2, r4
	rsb	r9, r3, r9
	bne	.L195
	b	.L194
.L168:
	add	r4, r4, #1
	and	r4, r4, #63
	cmp	r2, r4
	beq	.L194
.L195:
	add	r10, r4, #2
	add	r3, r5, r10, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L166
	ldr	ip, [r3, #148]
	rsb	ip, ip, r9
	clz	ip, ip
	mov	ip, ip, lsr #5
	cmp	ip, #0
	beq	.L168
.L167:
	ldrh	r0, [r5, #4]
	b	.L170
.L197:
	mov	r4, r2
.L170:
	cmp	r4, #0
	mov	r2, #63
	subne	r2, r4, #1
	add	r1, r5, r10, lsl #2
	add	r3, r2, #2
	cmp	r4, r0
	add	lr, r5, r3, lsl #2
	mov	r10, r3
	ldr	r3, [lr, #4]
	str	r3, [r1, #4]
	bne	.L197
	ldr	r3, [r6, #148]
	cmp	ip, #1
	ldr	r2, [r5, #344]
	rsb	r3, r2, r3
	str	r3, [r6, #148]
	ldrh	r2, [r5, #4]
	add	r2, r2, #1
	and	r2, r2, #63
	strh	r2, [r5, #4]	@ movhi
	beq	.L206
	ldrh	r2, [r5, #6]
	add	r4, r4, #1
	and	r4, r4, #63
	cmp	r2, r4
	bne	.L195
.L194:
	mov	r2, r9
	ldr	r1, .L209+4
	mov	r0, #1
	mvn	r4, #1
	bl	dprint_vfmw
.L165:
	ldr	r3, [r8, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r4
.L162:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L166:
	mov	r2, r4
	ldr	r1, .L209+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	ip, #2
	b	.L167
.L206:
	ldr	r1, [r6, #148]
	mov	r0, #12
	ldrh	r3, [r5, #6]
	str	r1, [sp, #4]
	ldrh	ip, [r5, #8]
	ldr	r1, .L209+12
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r7]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L199
.L173:
	.word	.L172
	.word	.L174
	.word	.L175
	.word	.L176
	.word	.L199
	.word	.L177
	.word	.L178
	.word	.L199
	.word	.L179
	.word	.L180
	.word	.L181
	.word	.L181
	.word	.L181
	.word	.L182
	.word	.L199
	.word	.L183
	.word	.L184
	.word	.L185
	.word	.L199
	.word	.L199
	.word	.L186
.L186:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	USERDEC_RecycleImage
	ldr	r3, [r7]
.L171:
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L187
.L189:
	.word	.L188
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L187
	.word	.L192
	.word	.L192
	.word	.L192
.L192:
	cmp	r0, #0
	mvnne	r4, #19
	moveq	r4, #1
	b	.L165
.L188:
	cmp	r0, #0
	moveq	r4, #1
	mvnne	r4, #19
	b	.L165
.L187:
	cmn	r0, #2
	beq	.L203
	cmp	r0, #1
	mvnne	r4, #19
	moveq	r4, #1
	b	.L165
.L172:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	H264DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L178:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	AVSDEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L179:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	REAL8DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L180:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	REAL9DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L181:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	VP6DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L182:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	VP8DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L183:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	MVC_DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L184:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	HEVC_DECRecycleImage
	ldr	r3, [r7]
	b	.L171
.L185:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	VP9DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L174:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	VC1DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L175:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	MPEG4DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L176:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	MPEG2DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L177:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	DIVX3DEC_RecycleImage
	ldr	r3, [r7]
	b	.L171
.L199:
	mvn	r0, #1
	b	.L171
.L207:
	ldr	r1, .L209+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L162
.L208:
	ldr	r2, .L209+20
	mov	r0, #1
	ldr	r1, .L209+24
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L162
.L203:
	mov	r4, r0
	b	.L165
.L210:
	.align	2
.L209:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC13
	.word	.LANCHOR0+128
	.word	.LC11
	UNWIND(.fnend)
	.size	SYNTAX_ReleaseImage, .-SYNTAX_ReleaseImage
	.align	2
	.global	SYNTAX_ReturnImage
	.type	SYNTAX_ReturnImage, %function
SYNTAX_ReturnImage:
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
	beq	.L231
	ldr	r3, [r0]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L230
.L215:
	.word	.L228
	.word	.L216
	.word	.L217
	.word	.L218
	.word	.L230
	.word	.L219
	.word	.L220
	.word	.L230
	.word	.L221
	.word	.L222
	.word	.L223
	.word	.L223
	.word	.L223
	.word	.L224
	.word	.L230
	.word	.L225
	.word	.L226
	.word	.L227
	.word	.L230
	.word	.L230
	.word	.L228
.L228:
	add	r4, r0, #16
.L229:
	ldr	r5, .L232
	mov	r0, #2
	ldr	r3, [r5, #12]
	blx	r3
	ldrh	r3, [r4, #6]
	mov	r0, #2
	sub	r3, r3, #1
	and	r3, r3, #63
	strh	r3, [r4, #6]	@ movhi
	ldr	r3, [r5, #16]
	blx	r3
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L216:
	add	r4, r0, #49152
	add	r4, r4, #176
	b	.L229
.L217:
	add	r4, r0, #22528
	add	r4, r4, #104
	b	.L229
.L218:
	add	r4, r0, #88064
	add	r4, r4, #648
	b	.L229
.L219:
	add	r4, r0, #42496
	add	r4, r4, #40
	b	.L229
.L220:
	add	r4, r0, #16192
	add	r4, r4, #8
	b	.L229
.L221:
	add	r4, r0, #54784
	add	r4, r4, #80
	b	.L229
.L222:
	add	r4, r0, #54784
	add	r4, r4, #72
	b	.L229
.L223:
	add	r4, r0, #12672
	add	r4, r4, #24
	b	.L229
.L224:
	add	r4, r0, #8192
	add	r4, r4, #24
	b	.L229
.L225:
	add	r4, r0, #592
	b	.L229
.L226:
	add	r4, r0, #5568
	add	r4, r4, #24
	b	.L229
.L227:
	add	r4, r0, #274432
	add	r4, r4, #1408
	b	.L229
.L230:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L231:
	mov	r3, #948
	ldr	r2, .L232+4
	ldr	r1, .L232+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L233:
	.align	2
.L232:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+148
	.word	.LC0
	UNWIND(.fnend)
	.size	SYNTAX_ReturnImage, .-SYNTAX_ReturnImage
	.align	2
	.global	DecodeStream_H264
	.type	DecodeStream_H264, %function
DecodeStream_H264:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r5, r1
	moveq	r6, #1
	movne	r6, #0
	beq	.L240
	ldrd	r2, [r0, #32]
	sub	r1, fp, #60
	ldr	ip, [r0, #8]
	mov	r0, r5
	ldr	r7, [r4, #20]
	strd	r2, [fp, #-36]
	ldr	r3, [r4, #24]
	ldrb	lr, [r4, #14]	@ zero_extendqisi2
	str	ip, [fp, #-56]
	ldrb	r2, [r4, #17]	@ zero_extendqisi2
	ldr	ip, [r4, #28]
	str	r3, [fp, #-48]
	ldrsb	r3, [r4, #13]
	str	r7, [fp, #-52]
	strb	lr, [fp, #-60]
	str	r3, [fp, #-40]
	str	ip, [fp, #-44]
	strb	r2, [fp, #-59]
	bl	H264DEC_DecodePacket
	add	r3, r5, #61440
	cmn	r0, #2
	beq	.L241
	strb	r6, [r4, #1]
	ldr	r2, .L243
	ldr	r1, [r3, #2688]
	ldr	r2, [r2, r1, asl #2]
	strb	r6, [r2, #1520]
.L238:
	ldr	r4, [r5, #360]
	cmp	r4, #0
	beq	.L242
.L234:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L240:
	movw	r3, #1051
	ldr	r2, .L243+4
	ldr	r1, .L243+8
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L241:
	mov	r2, #1
	ldr	r1, .L243
	strb	r2, [r4, #1]
	ldr	r0, [r3, #2688]
	ldr	r1, [r1, r0, asl #2]
	strb	r2, [r1, #1520]
	b	.L238
.L242:
	add	r5, r5, #12288
	ldrb	r2, [r5, #1272]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L234
	ldr	r0, [r3, #2688]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1272]
	b	.L234
.L244:
	.align	2
.L243:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+168
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_H264, .-DecodeStream_H264
	.align	2
	.global	DecodeStream_HEVC
	.type	DecodeStream_HEVC, %function
DecodeStream_HEVC:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
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
	cmpne	r0, #0
	mov	r4, r0
	mov	r5, r1
	beq	.L255
	ldr	r3, [r0, #8]
	sub	r1, fp, #52
	ldr	r6, [r0, #20]
	mov	r0, r5
	ldr	lr, [r4, #24]
	ldrb	ip, [r4, #14]	@ zero_extendqisi2
	ldr	r2, [r4, #28]
	str	r3, [fp, #-48]
	ldrsb	r3, [r4, #13]
	str	r6, [fp, #-44]
	str	lr, [fp, #-36]
	strb	ip, [fp, #-52]
	str	r2, [fp, #-32]
	str	r3, [fp, #-40]
	bl	HEVCDEC_DecodePacket
	cmn	r0, #2
	beq	.L248
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L248
	strb	r3, [r4, #1]
	ldr	r2, .L257
	ldr	r1, [r5, #252]
	ldr	r2, [r2, r1, asl #2]
	strb	r3, [r2, #1520]
.L250:
	ldr	r4, [r5, #2424]
	cmp	r4, #0
	beq	.L256
.L245:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L248:
	mov	r3, #1
	ldr	r2, .L257
	strb	r3, [r4, #1]
	ldr	r1, [r5, #252]
	ldr	r2, [r2, r1, asl #2]
	strb	r3, [r2, #1520]
	b	.L250
.L255:
	movw	r3, #1091
	ldr	r2, .L257+4
	ldr	r1, .L257+8
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L256:
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L245
	ldr	r0, [r5, #252]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #9]
	b	.L245
.L258:
	.align	2
.L257:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+188
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_HEVC, .-DecodeStream_HEVC
	.align	2
	.global	DecodeStream_VP9
	.type	DecodeStream_VP9, %function
DecodeStream_VP9:
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
	mov	r4, r0
	mov	r5, r1
	moveq	r9, #1
	movne	r9, #0
	beq	.L276
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L277
	ldr	r8, .L279
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	add	r6, r5, #294912
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r3, [r8, #48]
	mov	r1, r9
	mov	r2, #80
	add	r0, r4, #168
	blx	r3
	mov	r1, r7
	mov	r0, r5
	bl	VP9DEC_DecodePacket
	ldr	r3, [r6, #3424]
	cmp	r3, #0
	bne	.L278
.L262:
	ldr	r3, [r6, #3420]
	cmp	r3, #0
	bne	.L263
	strb	r3, [r4, #1]
	ldr	r3, [r5, #4]
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #262144
	ldrb	r9, [r5, #1036]	@ zero_extendqisi2
	cmp	r9, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r2, #160
	mov	r1, r9
	ldr	r5, [r8, #48]
	mov	r0, r7
	blx	r5
	ldr	r1, [r4, #28]
	ldr	r0, [r6, #3516]
	bl	SM_ReleaseStreamSeg
	ldr	r2, .L279+4
	ldr	ip, [r2]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r6, #3516]
	mov	r3, r9
	mov	r2, r9
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L278:
	ldr	r2, [r6, #3464]
	ldr	r3, [r6, #3460]
	cmp	r2, r3
	beq	.L262
.L263:
	mov	r3, #1
	strb	r3, [r4, #1]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L276:
	movw	r3, #1127
	ldr	r2, .L279+8
	ldr	r1, .L279+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L277:
	add	r5, r1, #294912
	ldr	r0, [r5, #3516]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #3516]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L280:
	.align	2
.L279:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LANCHOR0+208
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_VP9, .-DecodeStream_VP9
	.align	2
	.global	DecodeStream_MVC
	.type	DecodeStream_MVC, %function
DecodeStream_MVC:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r5, r1
	moveq	r6, #1
	movne	r6, #0
	beq	.L287
	ldrd	r2, [r0, #32]
	sub	r1, fp, #60
	ldr	r7, [r0, #8]
	mov	r0, r5
	ldr	lr, [r4, #20]
	strd	r2, [fp, #-36]
	ldr	ip, [r4, #24]
	ldr	r3, [r4, #28]
	ldrb	r2, [r4, #14]	@ zero_extendqisi2
	str	r7, [fp, #-56]
	str	r3, [fp, #-44]
	str	lr, [fp, #-52]
	str	ip, [fp, #-48]
	strb	r2, [fp, #-60]
	bl	MVC_DEC_DecodePacket
	cmn	r0, #2
	strneb	r6, [r4, #1]
	moveq	r3, #1
	streqb	r3, [r4, #1]
	ldr	r4, [r5, #228]
	cmp	r4, #0
	beq	.L288
.L281:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L287:
	movw	r3, #1169
	ldr	r2, .L289
	ldr	r1, .L289+4
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L288:
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L281
	ldr	r0, [r5, #120]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1]
	b	.L281
.L290:
	.align	2
.L289:
	.word	.LANCHOR0+228
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_MVC, .-DecodeStream_MVC
	.align	2
	.global	DecodeStream_VC1_Smp
	.type	DecodeStream_VC1_Smp, %function
DecodeStream_VC1_Smp:
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
	mov	r4, r0
	mov	r5, r1
	moveq	r6, #1
	movne	r6, #0
	beq	.L305
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L306
	ldr	r7, .L308
	add	r8, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r8
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, r6
	add	r0, r4, #168
	blx	r3
	ldr	r3, [r4, #104]
	cmp	r3, #15
	bhi	.L294
	ldr	r1, .L308+4
	add	r5, r5, #49152
.L304:
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r1, [r4, #108]
	ldr	r0, [r5, #520]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L308+8
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #520]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L294:
	add	r2, r5, #15808
	mov	r1, #16
	add	r2, r2, #24
	ldr	r0, [r4, #88]
	bl	Vc1SMPSeqHdr
	subs	r9, r0, #0
	beq	.L307
	add	r5, r5, #49152
	ldr	r1, .L308+12
	b	.L304
.L305:
	movw	r3, #1235
	ldr	r2, .L308+16
	ldr	r1, .L308+20
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L307:
	ldr	ip, [r4, #104]
	mov	r1, r8
	ldr	r2, [r4, #88]
	mov	r0, r5
	ldr	r3, [r4, #100]
	sub	ip, ip, #16
	add	r2, r2, #16
	str	ip, [r4, #104]
	str	r2, [r4, #88]
	add	r3, r3, #16
	str	r3, [r4, #100]
	bl	VC1DEC_Decode
	ldr	r3, [r7, #48]
	mov	r1, r9
	mov	r0, r8
	mov	r2, #160
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L306:
	add	r5, r1, #49152
	ldr	r0, [r5, #520]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #520]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L309:
	.align	2
.L308:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC17
	.word	g_event_report
	.word	.LC18
	.word	.LANCHOR0+248
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_VC1_Smp, .-DecodeStream_VC1_Smp
	.align	2
	.global	DecodeStream_REAL8
	.type	DecodeStream_REAL8, %function
DecodeStream_REAL8:
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
	mov	r4, r0
	mov	r5, r1
	moveq	r6, #1
	movne	r6, #0
	beq	.L321
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L322
	ldr	r8, .L323
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r3, [r8, #48]
	mov	r1, r6
	mov	r2, #80
	add	r0, r4, #168
	blx	r3
	mov	r1, r7
	mov	r0, r5
	bl	REAL8DEC_Decode
	cmn	r0, #2
	strneb	r6, [r4, #1]
	moveq	r3, #1
	streqb	r3, [r4, #1]
	ldr	r6, [r5, #4]
	cmp	r6, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #53248
	ldr	r3, [r8, #48]
	mov	r2, #160
	mov	r1, r6
	mov	r0, r7
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #1960]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L323+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #1960]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L321:
	movw	r3, #1474
	ldr	r2, .L323+8
	ldr	r1, .L323+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L322:
	add	r5, r1, #53248
	ldr	r0, [r5, #1960]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1960]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L324:
	.align	2
.L323:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LANCHOR0+272
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_REAL8, .-DecodeStream_REAL8
	.align	2
	.global	DecodeStream_REAL9
	.type	DecodeStream_REAL9, %function
DecodeStream_REAL9:
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
	mov	r4, r0
	mov	r5, r1
	moveq	r6, #1
	movne	r6, #0
	beq	.L336
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L337
	ldr	r8, .L338
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r3, [r8, #48]
	mov	r1, r6
	mov	r2, #80
	add	r0, r4, #168
	blx	r3
	mov	r1, r7
	mov	r0, r5
	bl	REAL9DEC_Decode
	cmn	r0, #2
	strneb	r6, [r4, #1]
	moveq	r3, #1
	streqb	r3, [r4, #1]
	ldr	r6, [r5, #4]
	cmp	r6, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #53248
	ldr	r3, [r8, #48]
	mov	r2, #160
	mov	r1, r6
	mov	r0, r7
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #1952]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L338+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #1952]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L336:
	movw	r3, #1511
	ldr	r2, .L338+8
	ldr	r1, .L338+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L337:
	add	r5, r1, #53248
	ldr	r0, [r5, #1952]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1952]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L339:
	.align	2
.L338:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LANCHOR0+292
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_REAL9, .-DecodeStream_REAL9
	.align	2
	.global	DecodeStream_DIVX3
	.type	DecodeStream_DIVX3, %function
DecodeStream_DIVX3:
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
	mov	r4, r0
	mov	r5, r1
	moveq	r6, #1
	movne	r6, #0
	beq	.L351
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L352
	ldr	r8, .L353
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r3, [r8, #48]
	mov	r1, r6
	mov	r2, #80
	add	r0, r4, #168
	blx	r3
	mov	r1, r7
	mov	r0, r5
	bl	DIVX3DEC_Decode
	cmn	r0, #2
	strneb	r6, [r4, #1]
	moveq	r3, #1
	streqb	r3, [r4, #1]
	ldr	r6, [r5, #4]
	cmp	r6, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #40960
	ldr	r3, [r8, #48]
	mov	r2, #160
	mov	r1, r6
	mov	r0, r7
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #1920]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L353+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #1920]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L351:
	movw	r3, #1553
	ldr	r2, .L353+8
	ldr	r1, .L353+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L352:
	add	r5, r1, #40960
	ldr	r0, [r5, #1920]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1920]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L354:
	.align	2
.L353:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LANCHOR0+312
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_DIVX3, .-DecodeStream_DIVX3
	.align	2
	.global	DecodeStream_VP8
	.type	DecodeStream_VP8, %function
DecodeStream_VP8:
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
	mov	r4, r0
	mov	r5, r1
	moveq	r6, #1
	movne	r6, #0
	beq	.L366
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L367
	ldr	r8, .L368
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r3, [r8, #48]
	mov	r1, r6
	mov	r2, #80
	add	r0, r4, #168
	blx	r3
	mov	r1, r7
	mov	r0, r5
	bl	VP8DEC_Decode
	cmn	r0, #2
	strneb	r6, [r4, #1]
	moveq	r3, #1
	streqb	r3, [r4, #1]
	ldr	r6, [r5, #4]
	cmp	r6, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #8192
	ldr	r3, [r8, #48]
	mov	r2, #160
	mov	r1, r6
	mov	r0, r7
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #368]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L368+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #368]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L366:
	movw	r3, #1595
	ldr	r2, .L368+8
	ldr	r1, .L368+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L367:
	add	r5, r1, #8192
	ldr	r0, [r5, #368]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #368]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L369:
	.align	2
.L368:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LANCHOR0+332
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_VP8, .-DecodeStream_VP8
	.align	2
	.global	DecodeStream_VP6x
	.type	DecodeStream_VP6x, %function
DecodeStream_VP6x:
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
	mov	r4, r0
	mov	r5, r1
	moveq	r6, #1
	movne	r6, #0
	beq	.L381
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L382
	ldr	r8, .L383
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r3, [r8, #48]
	mov	r1, r6
	mov	r2, #80
	add	r0, r4, #168
	blx	r3
	mov	r1, r7
	mov	r0, r5
	bl	VP6DEC_Decode
	cmn	r0, #2
	strneb	r6, [r4, #1]
	moveq	r3, #1
	streqb	r3, [r4, #1]
	ldr	r6, [r5, #4]
	cmp	r6, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #12288
	ldr	r3, [r8, #48]
	mov	r2, #160
	mov	r1, r6
	mov	r0, r7
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #752]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L383+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #752]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L381:
	movw	r3, #1636
	ldr	r2, .L383+8
	ldr	r1, .L383+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L382:
	add	r5, r1, #12288
	ldr	r0, [r5, #752]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #752]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L384:
	.align	2
.L383:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LANCHOR0+352
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_VP6x, .-DecodeStream_VP6x
	.align	2
	.global	SegMan
	.type	SegMan, %function
SegMan:
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
	cmp	r0, #31
	mov	r5, r0
	mov	r4, r1
	bhi	.L407
	cmp	r1, #0
	beq	.L388
	ldr	r0, [r1, #8]
	cmp	r0, #0
	beq	.L388
	ldr	r3, .L412
	ldr	r3, [r3, r5, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	beq	.L408
.L390:
	ldrb	r6, [r4, #14]	@ zero_extendqisi2
	mov	r7, #0
	strb	r7, [r4, #408]
	cmp	r6, #1
	beq	.L409
	cmp	r6, #0
	beq	.L410
.L395:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L410:
	ldr	r9, .L412+4
	add	r8, r4, #88
	add	r7, r4, #168
	mov	r2, #80
	add	r1, r4, #8
	mov	r0, r8
	ldr	r3, [r9, #52]
	blx	r3
	ldr	r3, [r9, #48]
	mov	r0, r7
	mov	r2, #80
	mov	r1, r6
	blx	r3
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	add	r3, r3, #1
	uxtb	r3, r3
	strb	r3, [r4, #2]
	cmp	r3, #1
	bls	.L395
	ldr	r1, [r4, #108]
	mov	r0, r5
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r4, #188]
	mov	r0, r5
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r9, #48]
	mov	r2, #80
	mov	r1, r6
	mov	r0, r8
	blx	r3
	ldr	r3, [r9, #48]
	mov	r0, r7
	mov	r2, #80
	mov	r1, r6
	blx	r3
	ldr	r1, .L412+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L412+12
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L394
	mov	r0, r5
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	r7
.L394:
	mov	r3, #0
	mvn	r0, #0
	strb	r3, [r4, #2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L408:
	ldr	r3, [r3, #1496]
	cmp	r3, #1
	bne	.L390
	ldrb	r3, [r1, #408]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L390
	mov	r2, #160
	add	r1, r1, #248
	add	r0, r4, #88
	bl	memcpy
	mov	r3, #0
	mov	r0, r3
	strb	r3, [r4, #408]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L409:
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cmp	r6, r7
	beq	.L411
	cmp	r6, #1
	bne	.L395
	ldr	r2, [r4, #104]
	cmp	r2, #1024
	bcs	.L396
	ldr	r8, .L412+4
	rsb	r0, r2, r0
	ldr	r1, [r4, #88]
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r1, [r4, #104]
	ldr	ip, [r4, #8]
	mov	r0, r5
	ldr	r2, [r4, #20]
	ldr	r3, [r4, #24]
	rsb	ip, r1, ip
	rsb	r2, r1, r2
	str	ip, [r4, #88]
	add	r3, r3, r1
	str	r2, [r4, #100]
	str	r3, [r4, #104]
	ldr	r1, [r4, #108]
	strb	r6, [r4, #94]
	bl	SM_ReleaseStreamSeg
	ldr	ip, [r4, #28]
	ldr	r3, [r8, #48]
	mov	r1, r7
	mov	r2, #80
	add	r0, r4, #168
	str	ip, [r4, #108]
	blx	r3
.L397:
	mov	r5, #0
	mov	r3, #1
	strb	r5, [r4, #2]
	mov	r2, #160
	strb	r3, [r4, #408]
	add	r1, r4, #88
	add	r0, r4, #248
	bl	memcpy
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L411:
	ldr	r5, .L412+4
	add	r1, r4, #8
	mov	r2, #80
	add	r0, r4, #88
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r5, #48]
	mov	r2, #80
	mov	r1, r6
	add	r0, r4, #168
	blx	r3
	strb	r6, [r4, #2]
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L396:
	ldr	r3, .L412+4
	mov	r2, #80
	add	r1, r4, #8
	add	r0, r4, #168
	ldr	r3, [r3, #52]
	blx	r3
	b	.L397
.L407:
	movw	r3, #1768
	ldr	r2, .L412+16
	ldr	r1, .L412+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L388:
	ldr	r1, .L412+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L413:
	.align	2
.L412:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	.word	g_event_report
	.word	.LANCHOR0+372
	.word	.LC0
	.word	.LC19
	UNWIND(.fnend)
	.size	SegMan, .-SegMan
	.align	2
	.global	DecodeStream_VC1_Adv
	.type	DecodeStream_VC1_Adv, %function
DecodeStream_VC1_Adv:
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
	mov	r5, r0
	mov	r4, r1
	beq	.L420
	add	r6, r1, #49152
	mov	r0, r1
	ldr	r7, [r6, #520]
	bl	VC1_GetPacketState
	cmp	r0, #2
	beq	.L421
.L416:
	mov	r1, r5
	ldr	r0, [r6, #520]
	bl	SegMan
	subs	r7, r0, #0
	beq	.L422
.L418:
	ldr	r5, [r4, #4]
	cmp	r5, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r4, r4, #12288
	ldrb	r3, [r4, #455]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r6, #520]
	bl	VCTRL_OutputLastFrame
	strb	r5, [r4, #455]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L420:
	movw	r3, #1202
	ldr	r2, .L423
	ldr	r1, .L423+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L422:
	add	r5, r5, #88
	mov	r0, r4
	mov	r1, r5
	bl	VC1DEC_Decode
	ldr	r3, .L423+8
	mov	r0, r5
	mov	r1, r7
	mov	r2, #160
	ldr	r3, [r3, #48]
	blx	r3
	b	.L418
.L421:
	ldr	r3, .L423+12
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	bne	.L417
	ldr	r3, [r3, #1496]
	cmp	r3, #0
	bne	.L416
.L417:
	add	r1, r4, #12544
	mov	r0, r4
	add	r1, r1, #32
	bl	VC1DEC_Decode
	b	.L416
.L424:
	.align	2
.L423:
	.word	.LANCHOR0+380
	.word	.LC0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_VC1_Adv, .-DecodeStream_VC1_Adv
	.align	2
	.global	DecodeStream_VC1
	.type	DecodeStream_VC1, %function
DecodeStream_VC1:
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
	moveq	r6, #1
	movne	r6, #0
	beq	.L430
	ldrb	r2, [r0, #14]	@ zero_extendqisi2
	mov	r0, #22
	ldr	r1, .L434
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L434+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r4, #24]
	ldr	r1, .L434+8
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r5]
	ldr	r3, [r2, #564]
	cmp	r3, #1
	bhi	.L431
	ldr	r1, [r2, #568]
	cmp	r1, #8
	bgt	.L432
	add	r1, r5, #12288
	uxtb	r3, r3
	cmp	r3, #1
	mov	r0, r4
	strb	r3, [r1, #3544]
	ldr	r3, [r2, #568]
	strb	r3, [r1, #3546]
	mov	r1, r5
	beq	.L433
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DecodeStream_VC1_Smp
.L431:
	mov	r0, r6
	ldr	r1, .L434+12
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L430:
	movw	r3, #1286
	ldr	r2, .L434+16
	ldr	r1, .L434+20
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L432:
	mov	r0, r6
	ldr	r1, .L434+24
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L433:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DecodeStream_VC1_Adv
.L435:
	.align	2
.L434:
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LANCHOR0+404
	.word	.LC0
	.word	.LC25
	UNWIND(.fnend)
	.size	DecodeStream_VC1, .-DecodeStream_VC1
	.align	2
	.global	DecodeStream_MPEG2
	.type	DecodeStream_MPEG2, %function
DecodeStream_MPEG2:
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
	mov	r6, r0
	mov	r4, r1
	beq	.L443
	add	r5, r1, #86016
	mov	r0, r1
	ldr	r7, [r5, #3040]
	bl	MP2_GetPacketState
	cmp	r0, #2
	beq	.L444
.L438:
	mov	r1, r6
	ldr	r0, [r5, #3040]
	bl	SegMan
	cmp	r0, #0
	beq	.L445
.L440:
	ldr	r4, [r4, #4]
	cmp	r4, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r5, #3058]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r5, #3040]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #3058]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L443:
	movw	r3, #1326
	ldr	r2, .L446
	ldr	r1, .L446+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L445:
	add	r1, r6, #88
	mov	r0, r4
	bl	MPEG2DEC_Decode
	ldrb	r3, [r5, #3057]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strb	r3, [r6, #1]
	b	.L440
.L444:
	ldr	r3, .L446+8
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	bne	.L439
	ldr	r3, [r3, #1496]
	cmp	r3, #0
	bne	.L438
.L439:
	add	r1, r4, #88064
	mov	r0, r4
	add	r1, r1, #80
	bl	MPEG2DEC_Decode
	b	.L438
.L447:
	.align	2
.L446:
	.word	.LANCHOR0+424
	.word	.LC0
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_MPEG2, .-DecodeStream_MPEG2
	.align	2
	.global	DecodeStream_MPEG4
	.type	DecodeStream_MPEG4, %function
DecodeStream_MPEG4:
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
	mov	r6, r0
	mov	r4, r1
	beq	.L454
	add	r5, r1, #20480
	mov	r0, r1
	ldr	r7, [r5, #2496]
	bl	MP4_GetPacketState
	cmp	r0, #3
	beq	.L455
.L450:
	mov	r1, r6
	ldr	r0, [r5, #2496]
	bl	SegMan
	cmp	r0, #0
	beq	.L456
.L452:
	ldr	r4, [r4, #1036]
	cmp	r4, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r5, #2532]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r5, #2496]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #2532]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L454:
	movw	r3, #1371
	ldr	r2, .L457
	ldr	r1, .L457+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L456:
	add	r1, r6, #88
	mov	r0, r4
	bl	MPEG4DEC_Decode
	b	.L452
.L455:
	ldr	r3, .L457+8
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	bne	.L451
	ldr	r3, [r3, #1496]
	cmp	r3, #0
	bne	.L450
.L451:
	add	r1, r4, #15680
	mov	r0, r4
	add	r1, r1, #32
	bl	MPEG4DEC_Decode
	b	.L450
.L458:
	.align	2
.L457:
	.word	.LANCHOR0+444
	.word	.LC0
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_MPEG4, .-DecodeStream_MPEG4
	.align	2
	.global	DecodeStream_AVS
	.type	DecodeStream_AVS, %function
DecodeStream_AVS:
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
	mov	r5, r0
	mov	r4, r1
	beq	.L465
	mov	r0, r1
	ldr	r6, [r1, #4]
	bl	AVS_GetPacketState
	cmp	r0, #0
	bne	.L461
	ldr	r3, .L468
	ldr	r3, [r3, r6, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	beq	.L466
.L462:
	add	r1, r4, #16384
	mov	r0, r4
	add	r1, r1, #168
	bl	AVSDEC_Decode
.L461:
	mov	r1, r5
	ldr	r0, [r4, #4]
	bl	SegMan
	cmp	r0, #0
	beq	.L467
.L463:
	ldr	r5, [r4, #16]
	cmp	r5, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #4]
	bl	VCTRL_OutputLastFrame
	strb	r5, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L465:
	movw	r3, #1407
	ldr	r2, .L468+4
	ldr	r1, .L468+8
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L467:
	add	r1, r5, #88
	mov	r0, r4
	bl	AVSDEC_Decode
	b	.L463
.L466:
	ldr	r3, [r3, #1496]
	cmp	r3, #0
	bne	.L461
	b	.L462
.L469:
	.align	2
.L468:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+464
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_AVS, .-DecodeStream_AVS
	.align	2
	.global	DecodeStream
	.type	DecodeStream, %function
DecodeStream:
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
	cmp	r2, #0
	cmpne	r0, #0
	mov	r4, r1
	mov	r5, r0
	mov	r6, r2
	beq	.L488
	mov	r0, #6
	bl	VCTRL_RecordPosTime
	cmp	r4, #17
	ldrls	pc, [pc, r4, asl #2]
	b	.L472
.L474:
	.word	.L473
	.word	.L475
	.word	.L476
	.word	.L477
	.word	.L472
	.word	.L478
	.word	.L479
	.word	.L472
	.word	.L480
	.word	.L481
	.word	.L482
	.word	.L482
	.word	.L482
	.word	.L483
	.word	.L472
	.word	.L484
	.word	.L485
	.word	.L486
.L488:
	movw	r3, #1676
	ldr	r2, .L489
	ldr	r1, .L489+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L486:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP9
.L487:
	mov	r0, #7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_RecordPosTime
.L485:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_HEVC
	b	.L487
.L484:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MVC
	b	.L487
.L483:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP8
	b	.L487
.L482:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP6x
	b	.L487
.L481:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_REAL9
	b	.L487
.L480:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_REAL8
	b	.L487
.L479:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_AVS
	b	.L487
.L478:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_DIVX3
	b	.L487
.L477:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MPEG2
	b	.L487
.L476:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MPEG4
	b	.L487
.L475:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VC1
	b	.L487
.L473:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_H264
	b	.L487
.L472:
	movw	r3, #1756
	ldr	r2, .L489
	ldr	r1, .L489+8
	mov	r0, #32
	bl	dprint_vfmw
	b	.L487
.L490:
	.align	2
.L489:
	.word	.LANCHOR0+484
	.word	.LC0
	.word	.LC26
	UNWIND(.fnend)
	.size	DecodeStream, .-DecodeStream
	.align	2
	.global	ReleasePacket
	.type	ReleasePacket, %function
ReleasePacket:
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
	beq	.L516
	sub	r3, r0, #5
	cmp	r3, #12
	ldrls	pc, [pc, r3, asl #2]
	b	.L493
.L495:
	.word	.L494
	.word	.L493
	.word	.L493
	.word	.L496
	.word	.L497
	.word	.L498
	.word	.L498
	.word	.L498
	.word	.L499
	.word	.L493
	.word	.L493
	.word	.L493
	.word	.L500
.L500:
	ldr	r4, [r1]
	add	r1, r1, #294912
	ldr	r0, [r1, #3516]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L506
	ldr	r1, .L517
	mov	r0, #1
	bl	dprint_vfmw
.L506:
	ldr	r3, .L517+4
	add	r0, r4, #232
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L494:
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L506
	add	r3, r1, #40960
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1920]
	bl	SM_ReleaseStreamSeg
	b	.L506
.L496:
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L506
	add	r3, r1, #53248
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1960]
	bl	SM_ReleaseStreamSeg
	b	.L506
.L497:
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L506
	add	r3, r1, #53248
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1952]
	bl	SM_ReleaseStreamSeg
	b	.L506
.L498:
	ldr	r4, [r1]
	add	r1, r1, #12288
	ldr	r0, [r1, #752]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L506
	ldr	r1, .L517+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L506
.L499:
	ldr	r4, [r1]
	add	r1, r1, #8192
	ldr	r0, [r1, #368]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L506
	ldr	r1, .L517+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L506
.L493:
	mov	r2, r0
	ldr	r1, .L517+16
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L516:
	movw	r3, #1855
	ldr	r2, .L517+20
	ldr	r1, .L517+24
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L518:
	.align	2
.L517:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	.word	.LC27
	.word	.LC30
	.word	.LANCHOR0+500
	.word	.LC0
	UNWIND(.fnend)
	.size	ReleasePacket, .-ReleasePacket
	.align	2
	.global	ReleaseCurPic_VPx
	.type	ReleaseCurPic_VPx, %function
ReleaseCurPic_VPx:
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
	beq	.L538
	sub	r0, r0, #10
	cmp	r0, #7
	ldrls	pc, [pc, r0, asl #2]
	b	.L519
.L523:
	.word	.L522
	.word	.L522
	.word	.L522
	.word	.L524
	.word	.L519
	.word	.L519
	.word	.L519
	.word	.L525
.L525:
	ldr	r4, [r1]
	add	r1, r1, #294912
	ldr	r0, [r1, #3516]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L528
	ldr	r1, .L539
	mov	r0, #1
	bl	dprint_vfmw
.L528:
	ldr	r3, .L539+4
	add	r0, r4, #232
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L524:
	ldr	r4, [r1]
	add	r1, r1, #8192
	ldr	r0, [r1, #368]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L528
	ldr	r1, .L539+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L528
.L522:
	ldr	r4, [r1]
	add	r1, r1, #12288
	ldr	r0, [r1, #752]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L528
	ldr	r1, .L539+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L528
.L519:
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L538:
	movw	r3, #1965
	ldr	r2, .L539+16
	ldr	r1, .L539+20
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L540:
	.align	2
.L539:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC28
	.word	.LANCHOR0+516
	.word	.LC0
	UNWIND(.fnend)
	.size	ReleaseCurPic_VPx, .-ReleaseCurPic_VPx
	.align	2
	.global	ReleaseCurPic_Realx
	.type	ReleaseCurPic_Realx, %function
ReleaseCurPic_Realx:
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
	beq	.L550
	cmp	r0, #8
	beq	.L544
	cmp	r0, #9
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L551
.L547:
	ldr	r3, .L552
	add	r0, r4, #232
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L544:
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L547
	add	r3, r1, #53248
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1960]
	bl	SM_ReleaseStreamSeg
	b	.L547
.L550:
	movw	r3, #2022
	ldr	r2, .L552+4
	ldr	r1, .L552+8
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L551:
	add	r3, r1, #53248
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1952]
	bl	SM_ReleaseStreamSeg
	b	.L547
.L553:
	.align	2
.L552:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+536
	.word	.LC0
	UNWIND(.fnend)
	.size	ReleaseCurPic_Realx, .-ReleaseCurPic_Realx
	.align	2
	.global	ReleaseCurPic_DIVX3
	.type	ReleaseCurPic_DIVX3, %function
ReleaseCurPic_DIVX3:
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
	beq	.L557
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L558
.L556:
	ldr	r3, .L559
	add	r0, r4, #232
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L558:
	add	r3, r1, #40960
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1920]
	bl	SM_ReleaseStreamSeg
	b	.L556
.L557:
	mov	r3, #2064
	ldr	r2, .L559+4
	ldr	r1, .L559+8
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L560:
	.align	2
.L559:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+556
	.word	.LC0
	UNWIND(.fnend)
	.size	ReleaseCurPic_DIVX3, .-ReleaseCurPic_DIVX3
	.align	2
	.global	ReleaseCurPic
	.type	ReleaseCurPic, %function
ReleaseCurPic:
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
	cmp	r1, #0
	beq	.L578
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L563
.L565:
	.word	.L564
	.word	.L566
	.word	.L567
	.word	.L568
	.word	.L563
	.word	.L569
	.word	.L570
	.word	.L563
	.word	.L571
	.word	.L572
	.word	.L573
	.word	.L573
	.word	.L573
	.word	.L574
	.word	.L563
	.word	.L575
	.word	.L576
	.word	.L577
.L577:
	mov	r0, #17
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L564:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264_ClearCurrPic
.L566:
	add	r3, r1, #49152
	add	r0, r1, #12736
	ldr	r1, [r3, #520]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1_ClearCurPic
.L567:
	mov	r0, r1
	str	r1, [fp, #-16]
	bl	MP4_ClearCurPic
	ldr	r1, [fp, #-16]
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP4_Clean_HeadPacket
.L568:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP2_ClearCurPic
.L569:
	mov	r0, #5
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_DIVX3
.L570:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS_ClearCurPic
.L571:
	mov	r0, #8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_Realx
.L572:
	mov	r0, #9
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_Realx
.L573:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L574:
	mov	r0, #13
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L575:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_ClearCurrPic
.L576:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_ClearCurrPic
.L563:
	mov	r2, r0
	ldr	r1, .L579
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L578:
	mov	r3, #2080
	ldr	r2, .L579+4
	ldr	r1, .L579+8
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L580:
	.align	2
.L579:
	.word	.LC30
	.word	.LANCHOR0+576
	.word	.LC0
	UNWIND(.fnend)
	.size	ReleaseCurPic, .-ReleaseCurPic
	.align	2
	.global	IsNewpicSeg
	.type	IsNewpicSeg, %function
IsNewpicSeg:
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
	cmp	r3, #0
	cmpne	r1, #0
	mov	lr, r1
	mov	r6, r3
	moveq	ip, #1
	movne	ip, #0
	beq	.L632
	cmp	r2, #2
	ldr	r1, [r3]
	movne	r3, ip
	beq	.L633
.L584:
	ldrb	ip, [r1]	@ zero_extendqisi2
	ldrb	r4, [r1, #1]	@ zero_extendqisi2
	cmp	ip, #0
	ldrb	r5, [r1, #2]	@ zero_extendqisi2
	bne	.L587
	cmp	r4, #0
	beq	.L634
.L587:
	str	r5, [sp]
	mov	r3, r4
	mov	r2, ip
	ldr	r1, .L636
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
.L627:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L634:
	cmp	r5, #1
	bne	.L587
	cmp	r2, #16
	ldrls	pc, [pc, r2, asl #2]
	b	.L607
.L591:
	.word	.L590
	.word	.L592
	.word	.L593
	.word	.L594
	.word	.L607
	.word	.L607
	.word	.L595
	.word	.L607
	.word	.L607
	.word	.L607
	.word	.L607
	.word	.L607
	.word	.L607
	.word	.L607
	.word	.L607
	.word	.L596
	.word	.L597
.L633:
	ldrb	ip, [r6, #72]	@ zero_extendqisi2
	ands	r3, ip, #1
	beq	.L584
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #179
	cmpne	ip, #176
	add	r4, ip, #75
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #254
	orreq	r2, r2, #1
	cmp	ip, #47
	movhi	r0, r2
	orrls	r0, r2, #1
	uxtb	r2, r4
	cmp	r2, #1
	movhi	r2, r0
	orrls	r2, r0, #1
	cmp	r2, #0
	beq	.L601
.L605:
	ldr	r2, [lr]
	cmp	r2, #0
	beq	.L601
	b	.L600
.L597:
	mov	r0, lr
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	HEVC_IsNewPicNal
.L590:
	mov	r0, lr
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	H264_IsNewPicNal
.L592:
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	sub	r3, r2, #12
	cmp	r2, #10
	cmpne	r3, #3
	bhi	.L619
	ldr	r3, [lr]
	cmp	r3, #0
	bne	.L619
	mov	r2, #1
	str	r2, [lr]
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
.L604:
	cmp	r2, #13
	mov	r0, r3
	bne	.L627
.L629:
	mov	r3, #0
	str	r3, [lr]
	b	.L627
.L593:
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #179
	cmpne	ip, #176
	add	r4, ip, #75
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #254
	orreq	r2, r2, #1
	cmp	ip, #47
	movhi	r0, r2
	orrls	r0, r2, #1
	uxtb	r2, r4
	cmp	r2, #1
	movhi	r2, r0
	orrls	r2, r0, #1
	cmp	r2, #0
	bne	.L605
.L600:
	cmp	r3, #1
	bne	.L613
.L601:
	mov	r3, #1
	str	r3, [lr]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	mov	r0, #0
.L602:
	cmp	ip, #182
	bne	.L627
	b	.L629
.L595:
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	sub	ip, r2, #179
	add	r3, r2, #74
	clz	ip, ip
	uxtb	r3, r3
	mov	ip, ip, lsr #5
	cmp	r2, #176
	movne	r0, ip
	orreq	r0, ip, #1
	cmp	r3, #1
	movhi	r3, r0
	orrls	r3, r0, #1
	cmp	r3, #0
	beq	.L616
	ldr	r3, [lr]
	cmp	r3, #0
	bne	.L616
	mov	r2, #1
	str	r2, [lr]
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	mov	r0, r3
	sub	ip, r2, #179
	clz	ip, ip
	mov	ip, ip, lsr #5
.L603:
	cmp	r2, #182
	movne	r2, ip
	orreq	r2, ip, #1
	cmp	r2, #0
	bne	.L629
	b	.L627
.L596:
	mov	r0, lr
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	MVC_IsNewPicNal
.L594:
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	add	r3, ip, #73
	cmp	ip, #0
	cmpne	ip, #179
	uxtb	r3, r3
	moveq	r2, #1
	movne	r2, #0
	cmp	r3, #1
	movhi	r3, r2
	orrls	r3, r2, #1
	cmp	r3, #0
	bne	.L635
	ldr	r3, .L636+4
	mvn	r5, #0
	mvn	r4, #0
	ldr	r0, [r3, r0, asl #2]
	add	r0, r0, #656
	ldrd	r2, [r0, #-8]
	cmp	r3, r5
	cmpeq	r2, r4
	bne	.L611
	ldr	r3, [lr]
	cmp	r3, #0
	bne	.L611
	sub	r3, ip, #1
	uxtb	r3, r3
	cmp	r3, #174
	bhi	.L611
	ldrd	r4, [r6, #24]
	mvn	r3, #0
	strd	r4, [r0, #-8]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
.L599:
	cmp	ip, #0
	streq	ip, [lr]
	moveq	r0, r3
	movne	r0, r3
	b	.L627
.L607:
	mvn	r0, #0
	b	.L627
.L635:
	ldr	r0, [lr]
	cmp	r0, #0
	bne	.L611
	mov	r2, #1
	mov	r3, r0
	str	r2, [lr]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	b	.L599
.L611:
	mvn	r3, #0
	b	.L599
.L632:
	movw	r3, #2356
	ldr	r2, .L636+8
	ldr	r1, .L636+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L627
.L619:
	mvn	r3, #0
	b	.L604
.L616:
	mvn	r0, #0
	b	.L603
.L613:
	mvn	r0, #0
	b	.L602
.L637:
	.align	2
.L636:
	.word	.LC31
	.word	s_pstVfmwChan
	.word	.LANCHOR0+592
	.word	.LC0
	UNWIND(.fnend)
	.size	IsNewpicSeg, .-IsNewpicSeg
	.align	2
	.global	CloseUsdPool
	.type	CloseUsdPool, %function
CloseUsdPool:
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
	cmp	r0, #31
	bhi	.L644
	ldr	r3, .L645
	add	r4, r3, r0, lsl #2
	ldr	r0, [r4, #128]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L645+4
	ldr	r3, [r3, #220]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #128]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L644:
	movw	r3, #2414
	ldr	r2, .L645+8
	ldr	r1, .L645+12
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L646:
	.align	2
.L645:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+604
	.word	.LC0
	UNWIND(.fnend)
	.size	CloseUsdPool, .-CloseUsdPool
	.align	2
	.global	CloseUsdPool_WithMem
	.type	CloseUsdPool_WithMem, %function
CloseUsdPool_WithMem:
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
	cmp	r0, #31
	bhi	.L653
	ldr	r3, .L654
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #128]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r0, #128]
	ldmfd	sp, {fp, sp, pc}
.L653:
	movw	r3, #2446
	ldr	r2, .L654+4
	ldr	r1, .L654+8
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L655:
	.align	2
.L654:
	.word	.LANCHOR1
	.word	.LANCHOR0+620
	.word	.LC0
	UNWIND(.fnend)
	.size	CloseUsdPool_WithMem, .-CloseUsdPool_WithMem
	.align	2
	.global	InitUsdPool
	.type	InitUsdPool, %function
InitUsdPool:
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
	cmp	r0, #31
	bhi	.L662
	ldr	r3, .L663
	add	r3, r3, r0, lsl #2
	ldr	r0, [r3, #128]
	cmp	r0, #0
	beq	.L660
	add	r1, r0, #203776
	mov	ip, #0
	add	r1, r1, #512
	mov	r3, r0
	mov	r2, ip
	str	ip, [r0]
.L659:
	str	r2, [r3, #1048]
	add	r3, r3, #1056
	str	r2, [r3, #-12]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L659
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L662:
	mov	r3, #2464
	ldr	r2, .L663+4
	ldr	r1, .L663+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L660:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L664:
	.align	2
.L663:
	.word	.LANCHOR1
	.word	.LANCHOR0+644
	.word	.LC0
	UNWIND(.fnend)
	.size	InitUsdPool, .-InitUsdPool
	.align	2
	.global	OpenUsdPool
	.type	OpenUsdPool, %function
OpenUsdPool:
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
	cmp	r0, #31
	mov	r5, r0
	bhi	.L670
	ldr	r4, .L672
	add	r4, r4, r0, lsl #2
	ldr	r3, [r4, #128]
	cmp	r3, #0
	beq	.L671
.L668:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	InitUsdPool
.L671:
	ldr	r3, .L672+4
	movw	r0, #7688
	movt	r0, 3
	ldr	r3, [r3, #216]
	blx	r3
	str	r0, [r4, #128]
	b	.L668
.L670:
	movw	r3, #2399
	ldr	r2, .L672+8
	ldr	r1, .L672+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L673:
	.align	2
.L672:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+656
	.word	.LC0
	UNWIND(.fnend)
	.size	OpenUsdPool, .-OpenUsdPool
	.align	2
	.global	OpenUsdPool_WithMem
	.type	OpenUsdPool_WithMem, %function
OpenUsdPool_WithMem:
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
	cmp	r0, #31
	bhi	.L679
	cmp	r1, #0
	beq	.L680
	ldr	r3, .L681
	add	r3, r3, r0, lsl #2
	ldr	r2, [r3, #128]
	cmp	r2, #0
	streq	r1, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	InitUsdPool
.L679:
	movw	r3, #2431
	ldr	r2, .L681+4
	ldr	r1, .L681+8
	mov	r0, #1
	bl	dprint_vfmw
.L676:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L680:
	mov	r3, #2432
	ldr	r2, .L681+4
	ldr	r1, .L681+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L676
.L682:
	.align	2
.L681:
	.word	.LANCHOR1
	.word	.LANCHOR0+668
	.word	.LC0
	UNWIND(.fnend)
	.size	OpenUsdPool_WithMem, .-OpenUsdPool_WithMem
	.align	2
	.global	GetUsd
	.type	GetUsd, %function
GetUsd:
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
	cmp	r0, #31
	bhi	.L691
	ldr	r3, .L692
	add	r0, r3, r0, lsl #2
	ldr	ip, [r0, #128]
	cmp	ip, #0
	beq	.L690
	mov	r3, ip
	mov	r2, #0
	b	.L687
.L686:
	add	r2, r2, #1
	add	r3, r3, #1056
	cmp	r2, #192
	add	r3, r3, #8
	beq	.L690
.L687:
	ldr	r1, [r3, #1048]
	cmp	r1, #0
	bne	.L686
	ldr	r1, [r3, #1044]
	cmp	r1, #0
	bne	.L686
	movw	r3, #1064
	mov	r4, #0
	mul	r0, r3, r2
	mov	r5, #0
	mla	r2, r2, r3, r3
	add	lr, ip, r0
	add	r0, r0, #8
	add	r3, lr, #1024
	add	r0, ip, r0
	str	r1, [lr, #1044]
	strd	r4, [ip, r2]
	str	r1, [lr, #1060]
	str	r1, [lr, #1056]
	str	r1, [lr, #1052]
	strb	r1, [lr, #1034]
	strb	r1, [lr, #1035]
	strb	r1, [lr, #1036]
	strh	r1, [r3, #14]	@ movhi
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L691:
	movw	r3, #2494
	ldr	r2, .L692+4
	ldr	r1, .L692+8
	mov	r0, #1
	bl	dprint_vfmw
.L690:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L693:
	.align	2
.L692:
	.word	.LANCHOR1
	.word	.LANCHOR0+688
	.word	.LC0
	UNWIND(.fnend)
	.size	GetUsd, .-GetUsd
	.align	2
	.global	FreeUsdByDec
	.type	FreeUsdByDec, %function
FreeUsdByDec:
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
	movne	r3, #0
	strne	r3, [r1, #1040]
	ldmnefd	sp, {fp, sp, pc}
	movw	r3, #2525
	ldr	r2, .L696
	ldr	r1, .L696+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L697:
	.align	2
.L696:
	.word	.LANCHOR0+696
	.word	.LC0
	UNWIND(.fnend)
	.size	FreeUsdByDec, .-FreeUsdByDec
	.align	2
	.global	MarkUsdByDnr
	.type	MarkUsdByDnr, %function
MarkUsdByDnr:
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
	movne	r3, #1
	strne	r3, [r1, #1036]
	ldmnefd	sp, {fp, sp, pc}
	movw	r3, #2536
	ldr	r2, .L700
	ldr	r1, .L700+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L701:
	.align	2
.L700:
	.word	.LANCHOR0+712
	.word	.LC0
	UNWIND(.fnend)
	.size	MarkUsdByDnr, .-MarkUsdByDnr
	.align	2
	.global	UnMarkUsdByDnr
	.type	UnMarkUsdByDnr, %function
UnMarkUsdByDnr:
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
	movne	r3, #0
	strne	r3, [r1, #1036]
	ldmnefd	sp, {fp, sp, pc}
	movw	r3, #2546
	ldr	r2, .L704
	ldr	r1, .L704+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L705:
	.align	2
.L704:
	.word	.LANCHOR0+728
	.word	.LC0
	UNWIND(.fnend)
	.size	UnMarkUsdByDnr, .-UnMarkUsdByDnr
	.align	2
	.global	IsImageInVoQueue
	.type	IsImageInVoQueue, %function
IsImageInVoQueue:
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
	cmp	r0, #0
	beq	.L718
	cmp	r1, #0
	beq	.L719
	ldrh	r3, [r0, #4]
	ldrh	lr, [r0, #8]
	and	r3, r3, #63
	cmp	lr, r3
	beq	.L712
.L711:
	add	r2, r0, r3, lsl #2
	add	r3, r3, #1
	and	r3, r3, #63
	ldr	r2, [r2, #12]
	cmp	r2, #0
	beq	.L710
	ldr	ip, [r2, #148]
	ldr	r2, [r1, #148]
	cmp	ip, r2
	beq	.L713
.L710:
	cmp	r3, lr
	bne	.L711
.L712:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L713:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L719:
	mov	r0, r1
	ldr	r1, .L720
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L718:
	movw	r3, #2558
	ldr	r2, .L720+4
	ldr	r1, .L720+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L721:
	.align	2
.L720:
	.word	.LC5
	.word	.LANCHOR0+744
	.word	.LC0
	UNWIND(.fnend)
	.size	IsImageInVoQueue, .-IsImageInVoQueue
	.align	2
	.global	IsVoQueueEmpty
	.type	IsVoQueueEmpty, %function
IsVoQueueEmpty:
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
	beq	.L726
	ldrh	r0, [r4, #8]
	ldrh	r3, [r4, #6]
	cmp	r0, r3
	ldreqh	r3, [r4, #4]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L726:
	ldr	r2, .L727
	ldr	r1, .L727+4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L728:
	.align	2
.L727:
	.word	.LANCHOR0+764
	.word	.LC32
	UNWIND(.fnend)
	.size	IsVoQueueEmpty, .-IsVoQueueEmpty
	.align	2
	.global	SetAspectRatio
	.type	SetAspectRatio, %function
SetAspectRatio:
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
	beq	.L740
	cmp	r1, #5
	ldrls	pc, [pc, r1, asl #2]
	b	.L731
.L733:
	.word	.L732
	.word	.L734
	.word	.L735
	.word	.L736
	.word	.L737
	.word	.L738
.L738:
	mov	r1, #0
	mov	r2, #2
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L732:
	mov	r1, #0
	mov	r2, #1
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L734:
	mov	r1, #4
	mov	r2, #3
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L735:
	mov	r1, #16
	mov	r2, #9
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L736:
	mov	r1, #221
	mov	r2, #100
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L737:
	mov	r1, #235
	mov	r2, #100
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L731:
	mov	r0, #1
	mov	r2, r1
	mov	ip, #0
	str	r0, [r3, #104]
	ldr	r1, .L741
	str	ip, [r3, #100]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L740:
	movw	r3, #2606
	ldr	r2, .L741+4
	ldr	r1, .L741+8
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L742:
	.align	2
.L741:
	.word	.LC33
	.word	.LANCHOR0+780
	.word	.LC0
	UNWIND(.fnend)
	.size	SetAspectRatio, .-SetAspectRatio
	.align	2
	.global	GetVoLastImageID
	.type	GetVoLastImageID, %function
GetVoLastImageID:
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
	cmp	r0, #0
	beq	.L747
	ldr	r0, [r0, #296]
	cmp	r0, #1
	mvnls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L747:
	movw	r3, #2654
	ldr	r2, .L748
	ldr	r1, .L748+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L749:
	.align	2
.L748:
	.word	.LANCHOR0+796
	.word	.LC0
	UNWIND(.fnend)
	.size	GetVoLastImageID, .-GetVoLastImageID
	.align	2
	.global	IsMain10Profile
	.type	IsMain10Profile, %function
IsMain10Profile:
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
	beq	.L758
	ldr	r3, [r4, #308]
	cmp	r3, #1
	beq	.L755
	ldr	r2, [r4, #312]
	cmp	r2, #1
	beq	.L755
	cmp	r3, #2
	ldr	r0, [r4, #316]
	moveq	r3, #1
	subne	r3, r0, #1
	clzne	r3, r3
	movne	r3, r3, lsr #5
.L753:
	cmp	r0, #1
	movne	r0, r3
	orreq	r0, r3, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L755:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L758:
	movw	r3, #2669
	ldr	r2, .L759
	ldr	r1, .L759+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L760:
	.align	2
.L759:
	.word	.LANCHOR0+816
	.word	.LC0
	UNWIND(.fnend)
	.size	IsMain10Profile, .-IsMain10Profile
	.align	2
	.global	IsPtsRewind
	.type	IsPtsRewind, %function
IsPtsRewind:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L765
	ldr	r1, .L767
	ldr	r1, [r1, r0, asl #2]
	ldr	r1, [r1, #128]
	cmp	r1, #0
	ldrd	r0, [fp, #4]
	bne	.L766
	subs	r0, r2, r0
	sbc	r1, r3, r1
	cmp	r1, #0
	cmpeq	r0, #1000
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L766:
	subs	r0, r2, r0
	sbc	r1, r3, r1
	mov	r2, r0
	movw	r0, #16960
	mov	r3, r1
	mov	r1, #0
	cmp	r3, r1
	movt	r0, 15
	cmpeq	r2, r0
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L765:
	movw	r3, #2694
	ldr	r2, .L767+4
	ldr	r1, .L767+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L768:
	.align	2
.L767:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+832
	.word	.LC0
	UNWIND(.fnend)
	.size	IsPtsRewind, .-IsPtsRewind
	.align	2
	.global	MetadataMapToSec
	.type	MetadataMapToSec, %function
MetadataMapToSec:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MetadataMapToSec, .-MetadataMapToSec
	.align	2
	.global	MetadataUnMapToSec
	.type	MetadataUnMapToSec, %function
MetadataUnMapToSec:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MetadataUnMapToSec, .-MetadataUnMapToSec
	.global	pstVdecUsdPool
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14273, %object
	.size	__func__.14273, 13
__func__.14273:
	.ascii	"PrintVoQueue\000"
	.space	3
	.type	__func__.14279, %object
	.size	__func__.14279, 13
__func__.14279:
	.ascii	"ResetVoQueue\000"
	.space	3
	.type	__func__.14285, %object
	.size	__func__.14285, 20
__func__.14285:
	.ascii	"ReturnImageToSyntax\000"
	.type	__func__.14349, %object
	.size	__func__.14349, 19
__func__.14349:
	.ascii	"InsertImgToVoQueue\000"
	.space	1
	.type	__FUNCTION__.14352, %object
	.size	__FUNCTION__.14352, 19
__FUNCTION__.14352:
	.ascii	"InsertImgToVoQueue\000"
	.space	1
	.type	__func__.14360, %object
	.size	__func__.14360, 15
__func__.14360:
	.ascii	"GetQueueImgNum\000"
	.space	1
	.type	__func__.14389, %object
	.size	__func__.14389, 20
__func__.14389:
	.ascii	"SYNTAX_ReceiveImage\000"
	.type	__func__.14435, %object
	.size	__func__.14435, 20
__func__.14435:
	.ascii	"SYNTAX_ReleaseImage\000"
	.type	__func__.14444, %object
	.size	__func__.14444, 19
__func__.14444:
	.ascii	"SYNTAX_ReturnImage\000"
	.space	1
	.type	__func__.14469, %object
	.size	__func__.14469, 18
__func__.14469:
	.ascii	"DecodeStream_H264\000"
	.space	2
	.type	__func__.14476, %object
	.size	__func__.14476, 18
__func__.14476:
	.ascii	"DecodeStream_HEVC\000"
	.space	2
	.type	__func__.14481, %object
	.size	__func__.14481, 17
__func__.14481:
	.ascii	"DecodeStream_VP9\000"
	.space	3
	.type	__func__.14488, %object
	.size	__func__.14488, 17
__func__.14488:
	.ascii	"DecodeStream_MVC\000"
	.space	3
	.type	__func__.14501, %object
	.size	__func__.14501, 21
__func__.14501:
	.ascii	"DecodeStream_VC1_Smp\000"
	.space	3
	.type	__func__.14533, %object
	.size	__func__.14533, 19
__func__.14533:
	.ascii	"DecodeStream_REAL8\000"
	.space	1
	.type	__func__.14539, %object
	.size	__func__.14539, 19
__func__.14539:
	.ascii	"DecodeStream_REAL9\000"
	.space	1
	.type	__func__.14545, %object
	.size	__func__.14545, 19
__func__.14545:
	.ascii	"DecodeStream_DIVX3\000"
	.space	1
	.type	__func__.14551, %object
	.size	__func__.14551, 17
__func__.14551:
	.ascii	"DecodeStream_VP8\000"
	.space	3
	.type	__func__.14557, %object
	.size	__func__.14557, 18
__func__.14557:
	.ascii	"DecodeStream_VP6x\000"
	.space	2
	.type	__func__.14586, %object
	.size	__func__.14586, 7
__func__.14586:
	.ascii	"SegMan\000"
	.space	1
	.type	__func__.14495, %object
	.size	__func__.14495, 21
__func__.14495:
	.ascii	"DecodeStream_VC1_Adv\000"
	.space	3
	.type	__func__.14506, %object
	.size	__func__.14506, 17
__func__.14506:
	.ascii	"DecodeStream_VC1\000"
	.space	3
	.type	__func__.14513, %object
	.size	__func__.14513, 19
__func__.14513:
	.ascii	"DecodeStream_MPEG2\000"
	.space	1
	.type	__func__.14520, %object
	.size	__func__.14520, 19
__func__.14520:
	.ascii	"DecodeStream_MPEG4\000"
	.space	1
	.type	__func__.14527, %object
	.size	__func__.14527, 17
__func__.14527:
	.ascii	"DecodeStream_AVS\000"
	.space	3
	.type	__func__.14563, %object
	.size	__func__.14563, 13
__func__.14563:
	.ascii	"DecodeStream\000"
	.space	3
	.type	__func__.14592, %object
	.size	__func__.14592, 14
__func__.14592:
	.ascii	"ReleasePacket\000"
	.space	2
	.type	__func__.14608, %object
	.size	__func__.14608, 18
__func__.14608:
	.ascii	"ReleaseCurPic_VPx\000"
	.space	2
	.type	__func__.14621, %object
	.size	__func__.14621, 20
__func__.14621:
	.ascii	"ReleaseCurPic_Realx\000"
	.type	__func__.14631, %object
	.size	__func__.14631, 20
__func__.14631:
	.ascii	"ReleaseCurPic_DIVX3\000"
	.type	__func__.14636, %object
	.size	__func__.14636, 14
__func__.14636:
	.ascii	"ReleaseCurPic\000"
	.space	2
	.type	__func__.14708, %object
	.size	__func__.14708, 12
__func__.14708:
	.ascii	"IsNewpicSeg\000"
	.type	__func__.14718, %object
	.size	__func__.14718, 13
__func__.14718:
	.ascii	"CloseUsdPool\000"
	.space	3
	.type	__func__.14728, %object
	.size	__func__.14728, 21
__func__.14728:
	.ascii	"CloseUsdPool_WithMem\000"
	.space	3
	.type	__func__.14734, %object
	.size	__func__.14734, 12
__func__.14734:
	.ascii	"InitUsdPool\000"
	.type	__func__.14714, %object
	.size	__func__.14714, 12
__func__.14714:
	.ascii	"OpenUsdPool\000"
	.type	__func__.14724, %object
	.size	__func__.14724, 20
__func__.14724:
	.ascii	"OpenUsdPool_WithMem\000"
	.type	__func__.14744, %object
	.size	__func__.14744, 7
__func__.14744:
	.ascii	"GetUsd\000"
	.space	1
	.type	__func__.14752, %object
	.size	__func__.14752, 13
__func__.14752:
	.ascii	"FreeUsdByDec\000"
	.space	3
	.type	__func__.14757, %object
	.size	__func__.14757, 13
__func__.14757:
	.ascii	"MarkUsdByDnr\000"
	.space	3
	.type	__func__.14762, %object
	.size	__func__.14762, 15
__func__.14762:
	.ascii	"UnMarkUsdByDnr\000"
	.space	1
	.type	__func__.14768, %object
	.size	__func__.14768, 17
__func__.14768:
	.ascii	"IsImageInVoQueue\000"
	.space	3
	.type	__func__.14774, %object
	.size	__func__.14774, 15
__func__.14774:
	.ascii	"IsVoQueueEmpty\000"
	.space	1
	.type	__func__.14779, %object
	.size	__func__.14779, 15
__func__.14779:
	.ascii	"SetAspectRatio\000"
	.space	1
	.type	__func__.14792, %object
	.size	__func__.14792, 17
__func__.14792:
	.ascii	"GetVoLastImageID\000"
	.space	3
	.type	__func__.14797, %object
	.size	__func__.14797, 16
__func__.14797:
	.ascii	"IsMain10Profile\000"
	.type	__func__.14804, %object
	.size	__func__.14804, 12
__func__.14804:
	.ascii	"IsPtsRewind\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"[%s %d]assert warning\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"VoQueue state: head(%d) history(%d) tail(%d)\000" )
	.space	3
.LC2:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"%d \000" )
.LC4:
	ASCII(.ascii	"ResetVoQueue but queue not empty: head(%d) history(" )
	ASCII(.ascii	"%d) tail(%d)\012\000" )
	.space	3
.LC5:
	ASCII(.ascii	"image point NULL\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"call InsertVOQueue\012\000" )
.LC7:
	ASCII(.ascii	"FATAL: p_image(id=%d) has already in the VoQueue!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC8:
	ASCII(.ascii	"error=%d,W=%d,H=%d,not acceptable!\012\000" )
.LC9:
	ASCII(.ascii	"out_pts: %lld -> %lld Usertag %lld\012\000" )
.LC10:
	ASCII(.ascii	"Queue=(%02d,%02d,%02d) + F%d\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"%s, pstVoQue is NULL!!!\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"Queue=(%02d,%02d,%02d) - F%d\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"SYNTAX_ReleaseImage p_image is null\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"Image %d not found in vo queue.\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"image[%d] null\012\000" )
.LC16:
	ASCII(.ascii	"Queue=(%02d,%02d,%02d) x F%d\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"LENTH ERROR: VC1 S/MP BS is wrong!\012\000" )
.LC18:
	ASCII(.ascii	"SYNTAX ERROR: VC1 S/MP BS is wrong!\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"pSegMan error!\012\000" )
.LC20:
	ASCII(.ascii	"More than two packet!!!ERROR!!!\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"pSegMan->CurrSeg.IsLastSeg=%d\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"pSegMan->CurrSeg.PhyAddr=%#x\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"pSegMan->CurrSeg.LenInByte=%#x\012\000" )
.LC24:
	ASCII(.ascii	"ERROR: Wrong PreParseInfo about Vc1 IsAdvProfile!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC25:
	ASCII(.ascii	"ERROR: Wrong PreParseInfo about Vc1 CodecVersion!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC26:
	ASCII(.ascii	"Func: %s, Line: %d\012\000" )
.LC27:
	ASCII(.ascii	"ERROR: VFMW_VP8 one packet stream, but IsLastSeg ==" )
	ASCII(.ascii	" 0\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"ERROR: VFMW_VP6 one packet stream, but IsLastSeg ==" )
	ASCII(.ascii	" 0\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"ERROR: VFMW_VP9 one packet stream, but IsLastSeg ==" )
	ASCII(.ascii	" 0\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"VidStd=%d Error!\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"pu8[0] = %x,pu8[1] = %x, pu8[2] = %x\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"%s pstVoQue NULL\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"WARNNING: aspect ration (%d) is not expected!\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	last_rec_pos_time.14348, %object
	.size	last_rec_pos_time.14348, 128
last_rec_pos_time.14348:
	.space	128
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 128
pstVdecUsdPool:
	.space	128
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
