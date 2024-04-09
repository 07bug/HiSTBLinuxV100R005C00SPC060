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
	b	.L19
.L4:
	.word	.L18
	.word	.L5
	.word	.L6
	.word	.L7
	.word	.L19
	.word	.L8
	.word	.L9
	.word	.L19
	.word	.L10
	.word	.L11
	.word	.L12
	.word	.L12
	.word	.L12
	.word	.L13
	.word	.L19
	.word	.L14
	.word	.L15
	.word	.L16
	.word	.L17
	.word	.L19
	.word	.L18
.L18:
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
	add	r0, r0, #6144
	add	r0, r0, #48
	ldmfd	sp, {fp, sp, pc}
.L16:
	add	r0, r0, #274432
	add	r0, r0, #4032
	ldmfd	sp, {fp, sp, pc}
.L17:
	add	r0, r0, #18432
	add	r0, r0, #152
	ldmfd	sp, {fp, sp, pc}
.L19:
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
	beq	.L27
	ldrh	ip, [r5, #8]
	mov	r0, #1
	ldrh	r3, [r5, #4]
	ldrh	r2, [r5, #6]
	ldr	r1, .L28
	str	ip, [sp]
	bl	dprint_vfmw
	ldrh	r3, [r5, #4]
	ldrh	r2, [r5, #8]
	and	r4, r3, #63
	cmp	r2, r4
	bne	.L26
	b	.L25
.L24:
	add	r3, r5, r4, lsl #2
	ldr	r1, .L28+4
	mov	r0, #1
	ldr	r3, [r3, #12]
	ldr	r2, [r3, #148]
	bl	dprint_vfmw
	add	r3, r4, #1
	ldrh	r2, [r5, #8]
	and	r4, r3, #63
	cmp	r2, r4
	beq	.L25
.L26:
	tst	r3, #7
	bne	.L24
	ldr	r1, .L28+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L24
.L25:
	ldr	r1, .L28+8
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L27:
	mov	r3, #78
	ldr	r2, .L28+12
	ldr	r1, .L28+16
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L29:
	.align	2
.L28:
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
	beq	.L35
	ldr	r5, .L37
	mov	r0, #2
	ldr	r3, [r5, #12]
	blx	r3
	ldrh	r2, [r4, #6]
	ldrh	r3, [r4, #4]
	ldrh	r1, [r4, #8]
	cmp	r2, r3
	beq	.L36
.L33:
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L37+4
	bl	dprint_vfmw
.L34:
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
.L36:
	cmp	r2, r1
	bne	.L33
	b	.L34
.L35:
	mov	r3, #107
	ldr	r2, .L37+8
	ldr	r1, .L37+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L38:
	.align	2
.L37:
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
	beq	.L58
	cmp	r0, #20
	ldrls	pc, [pc, r0, asl #2]
	b	.L39
.L43:
	.word	.L42
	.word	.L44
	.word	.L45
	.word	.L46
	.word	.L39
	.word	.L47
	.word	.L48
	.word	.L39
	.word	.L49
	.word	.L50
	.word	.L51
	.word	.L51
	.word	.L51
	.word	.L52
	.word	.L39
	.word	.L53
	.word	.L54
	.word	.L55
	.word	.L56
	.word	.L39
	.word	.L57
.L58:
	mov	r3, #151
	ldr	r2, .L59
	ldr	r1, .L59+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L57:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	USERDEC_RecycleImage
.L56:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2DEC_RecycleImage
.L55:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_RecycleImage
.L54:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_DECRecycleImage
.L53:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_RecycleImage
.L52:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_RecycleImage
.L51:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_RecycleImage
.L50:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_RecycleImage
.L49:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_RecycleImage
.L48:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_RecycleImage
.L47:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_RecycleImage
.L46:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_RecycleImage
.L45:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_RecycleImage
.L44:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_RecycleImage
.L42:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_RecycleImage
.L39:
	ldmfd	sp, {fp, sp, pc}
.L60:
	.align	2
.L59:
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
	bhi	.L129
	cmp	r5, #0
	cmpne	r2, #0
	beq	.L131
	cmp	r4, #0
	beq	.L132
	ldr	r6, .L140
	mov	r0, #2
	ldr	r1, .L140+4
	bl	dprint_vfmw
	mov	r0, #2
	ldr	r3, [r6, #12]
	blx	r3
	ldrh	r9, [r5, #4]
	ldrh	r0, [r5, #8]
	and	r9, r9, #63
	cmp	r0, r9
	ldrne	r8, [fp, #-56]
	bne	.L71
	b	.L70
.L69:
	add	r9, r9, #1
	and	r9, r9, #63
	cmp	r0, r9
	beq	.L133
.L71:
	add	r3, r5, r9, lsl #2
	ldr	r1, [r4, #148]
	ldr	r3, [r3, #12]
	ldr	r2, [r3, #148]
	cmp	r2, r1
	bne	.L69
	ldr	r1, .L140+8
	mov	r0, #0
	bl	dprint_vfmw
	add	r9, r9, #1
	mov	r3, #1000
	str	r3, [r4, #152]
	ldrh	r0, [r5, #8]
	and	r9, r9, #63
	cmp	r0, r9
	bne	.L71
.L133:
	str	r8, [fp, #-56]
.L70:
	ldr	r2, [r4, #152]
	cmp	r2, #100
	bhi	.L134
	ldr	r3, [r4, #68]
	ldr	r1, [r4, #72]
	cmp	r3, #31
	bhi	.L135
.L72:
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L140+12
	bl	dprint_vfmw
	ldr	r3, [r4, #152]
	cmp	r3, #1000
	beq	.L75
	mov	r2, r4
	mov	r1, r10
	ldr	r0, [fp, #-56]
	bl	ReturnImageToSyntax
.L75:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, #1
.L63:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L135:
	cmp	r1, #31
	bls	.L72
	ldr	r8, [fp, #-56]
	add	r1, r4, #416
	mov	r0, r7
	str	r8, [r4, #216]
	bl	VCTRL_GetHDRConfigInfo
	ldr	r3, .L140+16
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
	beq	.L95
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
	beq	.L136
	cmp	r8, #1
	bls	.L78
	mov	r2, r0
	mov	r3, r1
	mvn	r0, #0
	mvn	r1, #0
	b	.L76
.L134:
	ldr	r3, [r4, #68]
	ldr	r1, [r4, #72]
	b	.L72
.L136:
	cmp	r8, #1
	bls	.L137
.L95:
	mov	r2, r0
	mov	r3, r1
.L76:
	ldrd	r8, [ip]
	strd	r0, [ip, #-8]
	strd	r0, [sp]
	mov	r0, #29
	strd	r8, [sp, #8]
	ldr	r1, .L140+20
	bl	dprint_vfmw
	ldr	r3, [r4, #76]
	cmp	r3, #0
	beq	.L79
	ldr	r3, [r4, #80]
	cmp	r3, #0
	ldrne	r2, [r4, #68]
	beq	.L79
.L80:
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
	ldreq	r3, .L140+24
	streq	r3, [fp, #-56]
	beq	.L82
	ldr	r1, .L140+24
	ldr	r8, [r1]
	str	r1, [fp, #-56]
	cmp	r8, #0
	beq	.L83
	strb	r3, [fp, #-52]
	mov	r1, #7
	strb	r2, [fp, #-51]
	mov	r3, #2
	sub	r2, fp, #52
	mov	r0, r7
	blx	r8
.L83:
	str	r10, [r5, #272]
.L82:
	ldr	r3, [r5, #276]
	ldr	r2, [fp, #-60]
	cmp	r2, r3
	beq	.L84
	ldr	r3, [fp, #-56]
	ldr	r8, [r3]
	cmp	r8, #0
	beq	.L85
	ldrb	r1, [fp, #-65]	@ zero_extendqisi2
	sub	r2, fp, #44
	mov	r3, #1
	mov	r0, r7
	strb	r1, [r2, #-8]!
	mov	r1, #4
	blx	r8
.L85:
	ldr	r3, [fp, #-60]
	str	r3, [r5, #276]
.L84:
	ldr	r3, [r5, #288]
	cmp	r9, r3
	beq	.L138
.L86:
	ldr	r3, [fp, #-56]
	str	r9, [r5, #288]
	ldr	r8, [r3]
	ldr	r3, [fp, #-64]
	cmp	r8, #0
	str	r3, [r5, #292]
	beq	.L87
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
.L87:
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
	ldr	r1, .L140+28
	bl	dprint_vfmw
	ldrh	r3, [r5, #8]
	ldr	r9, .L140+32
	mov	ip, #0
	mov	r1, #5
	add	r2, r5, r3, lsl #2
	add	r3, r3, #1
	and	r3, r3, #63
	str	r4, [r2, #12]
	rsb	r2, r10, r8
	strh	r3, [r5, #8]	@ movhi
	add	r2, r9, r2
	ldr	r3, .L140+16
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
	ldr	r1, .L140+36
	ldr	r3, [r4, #160]
	mov	r0, #2
	ldr	r2, [r6, #16]
	add	r3, r3, #1
	str	r3, [r1, r7, asl #2]
	blx	r2
	ldr	r3, [fp, #-56]
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L89
	mov	r2, r4
	mov	r3, #640
	mov	r1, #5
	mov	r0, r7
	blx	r5
.L89:
	mov	r0, #8
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L139
.L91:
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
	bcc	.L63
	ldr	r3, [r4, #4]
	cmp	r3, #0
	beq	.L93
	movw	r0, #10000
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	str	r0, [r4, #8]
.L93:
	rsb	r8, r10, r8
	mov	r2, #0
	add	r3, r9, r8
	mov	r0, #1
	str	r5, [r9, r8]
	str	r2, [r3, #4]
	b	.L63
.L79:
	ldr	r2, [r4, #68]
	ldr	r3, [r4, #72]
	mov	r1, r2, lsr #1
	str	r2, [r4, #76]
	str	r3, [r4, #80]
	mov	r3, r3, lsr #1
	str	r1, [r4, #84]
	str	r3, [r4, #88]
	b	.L80
.L137:
	ldrb	r3, [r4, #64]	@ zero_extendqisi2
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L95
.L78:
	mvn	r9, #0
	str	r9, [lr]
	mov	r2, r9
	mov	r0, r9
	mov	r3, r9
	str	r9, [lr, #4]
	mov	r1, r9
	b	.L76
.L131:
	movw	r3, #397
.L129:
	ldr	r2, .L140+40
	mov	r0, #1
	ldr	r1, .L140+44
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L63
.L139:
	ldr	r3, [r6]
	blx	r3
	ldr	r1, .L140+48
	ldr	r2, .L140+52
	ldr	r3, [r1, r7, asl #2]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	cmp	r3, r2
	bls	.L91
	mov	r2, r7, asl #24
	str	r0, [r1, r7, asl #2]
	add	r2, r2, #524288
	movw	r1, #515
	ldr	r0, .L140+56
	bl	DBG_AddTrace
	b	.L91
.L138:
	ldr	r3, [r5, #292]
	ldr	r2, [fp, #-64]
	cmp	r2, r3
	bne	.L86
	b	.L87
.L132:
	mov	r0, r4
	ldr	r1, .L140+60
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L63
.L141:
	.align	2
.L140:
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
	bne	.L149
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
.L149:
	mov	r3, #556
	ldr	r2, .L150
	ldr	r1, .L150+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L151:
	.align	2
.L150:
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
	beq	.L158
	bl	SYNTAX_GetVoQue
	subs	r4, r0, #0
	beq	.L159
	ldr	r9, .L160
	mov	r0, #2
	ldr	r3, [r9, #12]
	blx	r3
	ldrh	r3, [r4, #6]
	ldrh	r2, [r4, #8]
	cmp	r2, r3
	mvneq	r5, #2
	beq	.L156
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
	ldr	r1, .L160+4
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
.L156:
	ldr	r3, [r9, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r5
.L154:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L158:
	movw	r3, #671
	ldr	r2, .L160+8
	ldr	r1, .L160+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L154
.L159:
	ldr	r2, .L160+8
	mov	r0, #1
	ldr	r1, .L160+16
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L154
.L161:
	.align	2
.L160:
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
	beq	.L210
	bl	SYNTAX_GetVoQue
	subs	r5, r0, #0
	beq	.L211
	ldr	r8, .L212
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
	bne	.L198
	b	.L197
.L170:
	add	r4, r4, #1
	and	r4, r4, #63
	cmp	r2, r4
	beq	.L197
.L198:
	add	r10, r4, #2
	add	r3, r5, r10, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L168
	ldr	ip, [r3, #148]
	rsb	ip, ip, r9
	clz	ip, ip
	mov	ip, ip, lsr #5
	cmp	ip, #0
	beq	.L170
.L169:
	ldrh	r0, [r5, #4]
	b	.L172
.L200:
	mov	r4, r2
.L172:
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
	bne	.L200
	ldr	r3, [r6, #148]
	cmp	ip, #1
	ldr	r2, [r5, #344]
	rsb	r3, r2, r3
	str	r3, [r6, #148]
	ldrh	r2, [r5, #4]
	add	r2, r2, #1
	and	r2, r2, #63
	strh	r2, [r5, #4]	@ movhi
	beq	.L209
	ldrh	r2, [r5, #6]
	add	r4, r4, #1
	and	r4, r4, #63
	cmp	r2, r4
	bne	.L198
.L197:
	mov	r2, r9
	ldr	r1, .L212+4
	mov	r0, #1
	mvn	r4, #1
	bl	dprint_vfmw
.L167:
	ldr	r3, [r8, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r4
.L164:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L168:
	mov	r2, r4
	ldr	r1, .L212+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	ip, #2
	b	.L169
.L209:
	ldr	r1, [r6, #148]
	mov	r0, #12
	ldrh	r3, [r5, #6]
	str	r1, [sp, #4]
	ldrh	ip, [r5, #8]
	ldr	r1, .L212+12
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r7]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L202
.L175:
	.word	.L174
	.word	.L176
	.word	.L177
	.word	.L178
	.word	.L202
	.word	.L179
	.word	.L180
	.word	.L202
	.word	.L181
	.word	.L182
	.word	.L183
	.word	.L183
	.word	.L183
	.word	.L184
	.word	.L202
	.word	.L185
	.word	.L186
	.word	.L187
	.word	.L188
	.word	.L202
	.word	.L189
.L189:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	USERDEC_RecycleImage
	ldr	r3, [r7]
.L173:
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L190
.L192:
	.word	.L191
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L190
	.word	.L195
	.word	.L195
	.word	.L195
.L195:
	cmp	r0, #0
	mvnne	r4, #19
	moveq	r4, #1
	b	.L167
.L191:
	cmp	r0, #0
	moveq	r4, #1
	mvnne	r4, #19
	b	.L167
.L190:
	cmn	r0, #2
	beq	.L206
	cmp	r0, #1
	mvnne	r4, #19
	moveq	r4, #1
	b	.L167
.L174:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	H264DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L181:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	REAL8DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L182:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	REAL9DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L183:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	VP6DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L184:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	VP8DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L185:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	MVC_DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L186:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	HEVC_DECRecycleImage
	ldr	r3, [r7]
	b	.L173
.L187:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	VP9DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L188:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	AVS2DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L177:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	MPEG4DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L178:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	MPEG2DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L179:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	DIVX3DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L180:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	AVSDEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L176:
	ldr	r1, [r6, #148]
	add	r0, r7, #8
	bl	VC1DEC_RecycleImage
	ldr	r3, [r7]
	b	.L173
.L202:
	mvn	r0, #1
	b	.L173
.L210:
	ldr	r1, .L212+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L164
.L211:
	ldr	r2, .L212+20
	mov	r0, #1
	ldr	r1, .L212+24
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L164
.L206:
	mov	r4, r0
	b	.L167
.L213:
	.align	2
.L212:
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
	beq	.L235
	ldr	r3, [r0]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L234
.L218:
	.word	.L232
	.word	.L219
	.word	.L220
	.word	.L221
	.word	.L234
	.word	.L222
	.word	.L223
	.word	.L234
	.word	.L224
	.word	.L225
	.word	.L226
	.word	.L226
	.word	.L226
	.word	.L227
	.word	.L234
	.word	.L228
	.word	.L229
	.word	.L230
	.word	.L231
	.word	.L234
	.word	.L232
.L232:
	add	r4, r0, #16
.L233:
	ldr	r5, .L236
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
.L219:
	add	r4, r0, #49152
	add	r4, r4, #176
	b	.L233
.L220:
	add	r4, r0, #22528
	add	r4, r4, #104
	b	.L233
.L221:
	add	r4, r0, #88064
	add	r4, r4, #648
	b	.L233
.L222:
	add	r4, r0, #42496
	add	r4, r4, #40
	b	.L233
.L223:
	add	r4, r0, #16192
	add	r4, r4, #8
	b	.L233
.L224:
	add	r4, r0, #54784
	add	r4, r4, #80
	b	.L233
.L225:
	add	r4, r0, #54784
	add	r4, r4, #72
	b	.L233
.L226:
	add	r4, r0, #12672
	add	r4, r4, #24
	b	.L233
.L227:
	add	r4, r0, #8192
	add	r4, r4, #24
	b	.L233
.L228:
	add	r4, r0, #592
	b	.L233
.L229:
	add	r4, r0, #6144
	add	r4, r4, #48
	b	.L233
.L230:
	add	r4, r0, #274432
	add	r4, r4, #4032
	b	.L233
.L231:
	add	r4, r0, #18432
	add	r4, r4, #152
	b	.L233
.L234:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L235:
	mov	r3, #948
	ldr	r2, .L236+4
	ldr	r1, .L236+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L237:
	.align	2
.L236:
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
	beq	.L244
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
	beq	.L245
	strb	r6, [r4, #1]
	ldr	r2, .L247
	ldr	r1, [r3, #2688]
	ldr	r2, [r2, r1, asl #2]
	strb	r6, [r2, #1520]
.L242:
	ldr	r4, [r5, #360]
	cmp	r4, #0
	beq	.L246
.L238:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L244:
	movw	r3, #1051
	ldr	r2, .L247+4
	ldr	r1, .L247+8
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L245:
	mov	r2, #1
	ldr	r1, .L247
	strb	r2, [r4, #1]
	ldr	r0, [r3, #2688]
	ldr	r1, [r1, r0, asl #2]
	strb	r2, [r1, #1520]
	b	.L242
.L246:
	add	r5, r5, #12288
	ldrb	r2, [r5, #1272]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L238
	ldr	r0, [r3, #2688]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1272]
	b	.L238
.L248:
	.align	2
.L247:
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
	beq	.L259
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
	beq	.L252
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L252
	strb	r3, [r4, #1]
	ldr	r2, .L261
	ldr	r1, [r5, #276]
	ldr	r2, [r2, r1, asl #2]
	strb	r3, [r2, #1520]
.L254:
	ldr	r4, [r5, #2864]
	cmp	r4, #0
	beq	.L260
.L249:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L252:
	mov	r3, #1
	ldr	r2, .L261
	strb	r3, [r4, #1]
	ldr	r1, [r5, #276]
	ldr	r2, [r2, r1, asl #2]
	strb	r3, [r2, #1520]
	b	.L254
.L259:
	movw	r3, #1091
	ldr	r2, .L261+4
	ldr	r1, .L261+8
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L260:
	ldrb	r3, [r5, #11]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L249
	ldr	r0, [r5, #276]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #11]
	b	.L249
.L262:
	.align	2
.L261:
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
	beq	.L280
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L281
	ldr	r8, .L283
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	add	r6, r5, #311296
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
	ldr	r3, [r6, #2768]
	cmp	r3, #0
	bne	.L282
.L266:
	ldr	r3, [r6, #2764]
	cmp	r3, #0
	bne	.L267
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
	ldr	r0, [r6, #2860]
	bl	SM_ReleaseStreamSeg
	ldr	r2, .L283+4
	ldr	ip, [r2]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r6, #2860]
	mov	r3, r9
	mov	r2, r9
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L282:
	ldr	r2, [r6, #2808]
	ldr	r3, [r6, #2804]
	cmp	r2, r3
	beq	.L266
.L267:
	mov	r3, #1
	strb	r3, [r4, #1]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L280:
	movw	r3, #1127
	ldr	r2, .L283+8
	ldr	r1, .L283+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L281:
	add	r5, r1, #311296
	ldr	r0, [r5, #2860]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #2860]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L284:
	.align	2
.L283:
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
	beq	.L291
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
	beq	.L292
.L285:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L291:
	movw	r3, #1169
	ldr	r2, .L293
	ldr	r1, .L293+4
	mov	r0, #1
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L292:
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L285
	ldr	r0, [r5, #120]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1]
	b	.L285
.L294:
	.align	2
.L293:
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
	beq	.L309
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L310
	ldr	r7, .L312
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
	bhi	.L298
	ldr	r1, .L312+4
	add	r5, r5, #49152
.L308:
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r1, [r4, #108]
	ldr	r0, [r5, #520]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L312+8
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
.L298:
	add	r2, r5, #15808
	mov	r1, #16
	add	r2, r2, #24
	ldr	r0, [r4, #88]
	bl	Vc1SMPSeqHdr
	subs	r9, r0, #0
	beq	.L311
	add	r5, r5, #49152
	ldr	r1, .L312+12
	b	.L308
.L309:
	movw	r3, #1235
	ldr	r2, .L312+16
	ldr	r1, .L312+20
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L311:
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
.L310:
	add	r5, r1, #49152
	ldr	r0, [r5, #520]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #520]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L313:
	.align	2
.L312:
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
	beq	.L325
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L326
	ldr	r8, .L327
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
	ldr	r3, .L327+4
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
.L325:
	movw	r3, #1474
	ldr	r2, .L327+8
	ldr	r1, .L327+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L326:
	add	r5, r1, #53248
	ldr	r0, [r5, #1960]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1960]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L328:
	.align	2
.L327:
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
	beq	.L340
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L341
	ldr	r8, .L342
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
	ldr	r3, .L342+4
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
.L340:
	movw	r3, #1511
	ldr	r2, .L342+8
	ldr	r1, .L342+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L341:
	add	r5, r1, #53248
	ldr	r0, [r5, #1952]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1952]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L343:
	.align	2
.L342:
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
	beq	.L355
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L356
	ldr	r8, .L357
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
	ldr	r3, .L357+4
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
.L355:
	movw	r3, #1553
	ldr	r2, .L357+8
	ldr	r1, .L357+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L356:
	add	r5, r1, #40960
	ldr	r0, [r5, #1920]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1920]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L358:
	.align	2
.L357:
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
	beq	.L370
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L371
	ldr	r8, .L372
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
	ldr	r3, .L372+4
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
.L370:
	movw	r3, #1595
	ldr	r2, .L372+8
	ldr	r1, .L372+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L371:
	add	r5, r1, #8192
	ldr	r0, [r5, #368]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #368]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L373:
	.align	2
.L372:
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
	beq	.L385
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L386
	ldr	r8, .L387
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
	ldr	r3, .L387+4
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
.L385:
	movw	r3, #1636
	ldr	r2, .L387+8
	ldr	r1, .L387+12
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L386:
	add	r5, r1, #12288
	ldr	r0, [r5, #752]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #752]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L388:
	.align	2
.L387:
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
	bhi	.L411
	cmp	r1, #0
	beq	.L392
	ldr	r0, [r1, #8]
	cmp	r0, #0
	beq	.L392
	ldr	r3, .L416
	ldr	r3, [r3, r5, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	beq	.L412
.L394:
	ldrb	r6, [r4, #14]	@ zero_extendqisi2
	mov	r7, #0
	strb	r7, [r4, #408]
	cmp	r6, #1
	beq	.L413
	cmp	r6, #0
	beq	.L414
.L399:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L414:
	ldr	r9, .L416+4
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
	bls	.L399
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
	ldr	r1, .L416+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L416+12
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L398
	mov	r0, r5
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	r7
.L398:
	mov	r3, #0
	mvn	r0, #0
	strb	r3, [r4, #2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L412:
	ldr	r3, [r3, #1496]
	cmp	r3, #1
	bne	.L394
	ldrb	r3, [r1, #408]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L394
	mov	r2, #160
	add	r1, r1, #248
	add	r0, r4, #88
	bl	memcpy
	mov	r3, #0
	mov	r0, r3
	strb	r3, [r4, #408]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L413:
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cmp	r6, r7
	beq	.L415
	cmp	r6, #1
	bne	.L399
	ldr	r2, [r4, #104]
	cmp	r2, #1024
	bcs	.L400
	ldr	r8, .L416+4
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
.L401:
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
.L415:
	ldr	r5, .L416+4
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
.L400:
	ldr	r3, .L416+4
	mov	r2, #80
	add	r1, r4, #8
	add	r0, r4, #168
	ldr	r3, [r3, #52]
	blx	r3
	b	.L401
.L411:
	movw	r3, #1768
	ldr	r2, .L416+16
	ldr	r1, .L416+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L392:
	ldr	r1, .L416+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L417:
	.align	2
.L416:
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
	beq	.L424
	add	r6, r1, #49152
	mov	r0, r1
	ldr	r7, [r6, #520]
	bl	VC1_GetPacketState
	cmp	r0, #2
	beq	.L425
.L420:
	mov	r1, r5
	ldr	r0, [r6, #520]
	bl	SegMan
	subs	r7, r0, #0
	beq	.L426
.L422:
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
.L424:
	movw	r3, #1202
	ldr	r2, .L427
	ldr	r1, .L427+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L426:
	add	r5, r5, #88
	mov	r0, r4
	mov	r1, r5
	bl	VC1DEC_Decode
	ldr	r3, .L427+8
	mov	r0, r5
	mov	r1, r7
	mov	r2, #160
	ldr	r3, [r3, #48]
	blx	r3
	b	.L422
.L425:
	ldr	r3, .L427+12
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	bne	.L421
	ldr	r3, [r3, #1496]
	cmp	r3, #0
	bne	.L420
.L421:
	add	r1, r4, #12544
	mov	r0, r4
	add	r1, r1, #32
	bl	VC1DEC_Decode
	b	.L420
.L428:
	.align	2
.L427:
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
	beq	.L434
	ldrb	r2, [r0, #14]	@ zero_extendqisi2
	mov	r0, #22
	ldr	r1, .L438
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L438+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r4, #24]
	ldr	r1, .L438+8
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r5]
	ldr	r3, [r2, #564]
	cmp	r3, #1
	bhi	.L435
	ldr	r1, [r2, #568]
	cmp	r1, #8
	bgt	.L436
	add	r1, r5, #12288
	uxtb	r3, r3
	cmp	r3, #1
	mov	r0, r4
	strb	r3, [r1, #3544]
	ldr	r3, [r2, #568]
	strb	r3, [r1, #3546]
	mov	r1, r5
	beq	.L437
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DecodeStream_VC1_Smp
.L435:
	mov	r0, r6
	ldr	r1, .L438+12
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L434:
	movw	r3, #1286
	ldr	r2, .L438+16
	ldr	r1, .L438+20
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L436:
	mov	r0, r6
	ldr	r1, .L438+24
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L437:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	DecodeStream_VC1_Adv
.L439:
	.align	2
.L438:
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
	beq	.L447
	add	r5, r1, #86016
	mov	r0, r1
	ldr	r7, [r5, #3040]
	bl	MP2_GetPacketState
	cmp	r0, #2
	beq	.L448
.L442:
	mov	r1, r6
	ldr	r0, [r5, #3040]
	bl	SegMan
	cmp	r0, #0
	beq	.L449
.L444:
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
.L447:
	movw	r3, #1326
	ldr	r2, .L450
	ldr	r1, .L450+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L449:
	add	r1, r6, #88
	mov	r0, r4
	bl	MPEG2DEC_Decode
	ldrb	r3, [r5, #3057]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strb	r3, [r6, #1]
	b	.L444
.L448:
	ldr	r3, .L450+8
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	bne	.L443
	ldr	r3, [r3, #1496]
	cmp	r3, #0
	bne	.L442
.L443:
	add	r1, r4, #88064
	mov	r0, r4
	add	r1, r1, #80
	bl	MPEG2DEC_Decode
	b	.L442
.L451:
	.align	2
.L450:
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
	beq	.L458
	add	r5, r1, #20480
	mov	r0, r1
	ldr	r7, [r5, #2496]
	bl	MP4_GetPacketState
	cmp	r0, #3
	beq	.L459
.L454:
	mov	r1, r6
	ldr	r0, [r5, #2496]
	bl	SegMan
	cmp	r0, #0
	beq	.L460
.L456:
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
.L458:
	movw	r3, #1371
	ldr	r2, .L461
	ldr	r1, .L461+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L460:
	add	r1, r6, #88
	mov	r0, r4
	bl	MPEG4DEC_Decode
	b	.L456
.L459:
	ldr	r3, .L461+8
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	bne	.L455
	ldr	r3, [r3, #1496]
	cmp	r3, #0
	bne	.L454
.L455:
	add	r1, r4, #15680
	mov	r0, r4
	add	r1, r1, #32
	bl	MPEG4DEC_Decode
	b	.L454
.L462:
	.align	2
.L461:
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
	beq	.L469
	mov	r0, r1
	ldr	r6, [r1, #4]
	bl	AVS_GetPacketState
	cmp	r0, #0
	bne	.L465
	ldr	r3, .L472
	ldr	r3, [r3, r6, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	beq	.L470
.L466:
	add	r1, r4, #16384
	mov	r0, r4
	add	r1, r1, #168
	bl	AVSDEC_Decode
.L465:
	mov	r1, r5
	ldr	r0, [r4, #4]
	bl	SegMan
	cmp	r0, #0
	beq	.L471
.L467:
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
.L469:
	movw	r3, #1407
	ldr	r2, .L472+4
	ldr	r1, .L472+8
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L471:
	add	r1, r5, #88
	mov	r0, r4
	bl	AVSDEC_Decode
	b	.L467
.L470:
	ldr	r3, [r3, #1496]
	cmp	r3, #0
	bne	.L465
	b	.L466
.L473:
	.align	2
.L472:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+464
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_AVS, .-DecodeStream_AVS
	.align	2
	.global	DecodeStream_AVS2
	.type	DecodeStream_AVS2, %function
DecodeStream_AVS2:
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
	mov	r4, r1
	beq	.L481
	mov	r1, r0
	ldr	r0, [r4, #4]
	bl	SegMan
	cmp	r0, #0
	beq	.L482
.L476:
	ldr	r3, [r4, #8]
	cmp	r3, #1
	movne	r3, #0
	strb	r3, [r5, #1]
	ldr	r5, [r4, #40]
	cmp	r5, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #4]
	bl	VCTRL_OutputLastFrame
	strb	r5, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L481:
	movw	r3, #1442
	ldr	r2, .L483
	ldr	r1, .L483+4
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L482:
	add	r1, r5, #88
	mov	r0, r4
	bl	AVS2DEC_Decode
	b	.L476
.L484:
	.align	2
.L483:
	.word	.LANCHOR0+484
	.word	.LC0
	UNWIND(.fnend)
	.size	DecodeStream_AVS2, .-DecodeStream_AVS2
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
	beq	.L504
	mov	r0, #6
	bl	VCTRL_RecordPosTime
	cmp	r4, #18
	ldrls	pc, [pc, r4, asl #2]
	b	.L487
.L489:
	.word	.L488
	.word	.L490
	.word	.L491
	.word	.L492
	.word	.L487
	.word	.L493
	.word	.L494
	.word	.L487
	.word	.L495
	.word	.L496
	.word	.L497
	.word	.L497
	.word	.L497
	.word	.L498
	.word	.L487
	.word	.L499
	.word	.L500
	.word	.L501
	.word	.L502
.L504:
	movw	r3, #1676
	ldr	r2, .L505
	ldr	r1, .L505+4
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L502:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_AVS2
.L503:
	mov	r0, #7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_RecordPosTime
.L501:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP9
	b	.L503
.L500:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_HEVC
	b	.L503
.L499:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MVC
	b	.L503
.L498:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP8
	b	.L503
.L497:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP6x
	b	.L503
.L496:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_REAL9
	b	.L503
.L495:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_REAL8
	b	.L503
.L494:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_AVS
	b	.L503
.L493:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_DIVX3
	b	.L503
.L492:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MPEG2
	b	.L503
.L491:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MPEG4
	b	.L503
.L490:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VC1
	b	.L503
.L488:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_H264
	b	.L503
.L487:
	movw	r3, #1756
	ldr	r2, .L505
	ldr	r1, .L505+8
	mov	r0, #32
	bl	dprint_vfmw
	b	.L503
.L506:
	.align	2
.L505:
	.word	.LANCHOR0+504
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
	beq	.L532
	sub	r3, r0, #5
	cmp	r3, #12
	ldrls	pc, [pc, r3, asl #2]
	b	.L509
.L511:
	.word	.L510
	.word	.L509
	.word	.L509
	.word	.L512
	.word	.L513
	.word	.L514
	.word	.L514
	.word	.L514
	.word	.L515
	.word	.L509
	.word	.L509
	.word	.L509
	.word	.L516
.L516:
	ldr	r4, [r1]
	add	r1, r1, #311296
	ldr	r0, [r1, #2860]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L522
	ldr	r1, .L533
	mov	r0, #1
	bl	dprint_vfmw
.L522:
	ldr	r3, .L533+4
	add	r0, r4, #232
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L510:
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L522
	add	r3, r1, #40960
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1920]
	bl	SM_ReleaseStreamSeg
	b	.L522
.L512:
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L522
	add	r3, r1, #53248
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1960]
	bl	SM_ReleaseStreamSeg
	b	.L522
.L513:
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L522
	add	r3, r1, #53248
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1952]
	bl	SM_ReleaseStreamSeg
	b	.L522
.L514:
	ldr	r4, [r1]
	add	r1, r1, #12288
	ldr	r0, [r1, #752]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L522
	ldr	r1, .L533+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L522
.L515:
	ldr	r4, [r1]
	add	r1, r1, #8192
	ldr	r0, [r1, #368]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L522
	ldr	r1, .L533+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L522
.L509:
	mov	r2, r0
	ldr	r1, .L533+16
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L532:
	movw	r3, #1855
	ldr	r2, .L533+20
	ldr	r1, .L533+24
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L534:
	.align	2
.L533:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	.word	.LC27
	.word	.LC30
	.word	.LANCHOR0+520
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
	beq	.L554
	sub	r0, r0, #10
	cmp	r0, #7
	ldrls	pc, [pc, r0, asl #2]
	b	.L535
.L539:
	.word	.L538
	.word	.L538
	.word	.L538
	.word	.L540
	.word	.L535
	.word	.L535
	.word	.L535
	.word	.L541
.L541:
	ldr	r4, [r1]
	add	r1, r1, #311296
	ldr	r0, [r1, #2860]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L544
	ldr	r1, .L555
	mov	r0, #1
	bl	dprint_vfmw
.L544:
	ldr	r3, .L555+4
	add	r0, r4, #232
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L540:
	ldr	r4, [r1]
	add	r1, r1, #8192
	ldr	r0, [r1, #368]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L544
	ldr	r1, .L555+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L544
.L538:
	ldr	r4, [r1]
	add	r1, r1, #12288
	ldr	r0, [r1, #752]
	ldr	r1, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L544
	ldr	r1, .L555+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L544
.L535:
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L554:
	movw	r3, #1965
	ldr	r2, .L555+16
	ldr	r1, .L555+20
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L556:
	.align	2
.L555:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC28
	.word	.LANCHOR0+536
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
	beq	.L566
	cmp	r0, #8
	beq	.L560
	cmp	r0, #9
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L567
.L563:
	ldr	r3, .L568
	add	r0, r4, #232
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L560:
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L563
	add	r3, r1, #53248
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1960]
	bl	SM_ReleaseStreamSeg
	b	.L563
.L566:
	movw	r3, #2022
	ldr	r2, .L568+4
	ldr	r1, .L568+8
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L567:
	add	r3, r1, #53248
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1952]
	bl	SM_ReleaseStreamSeg
	b	.L563
.L569:
	.align	2
.L568:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+556
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
	beq	.L573
	ldr	r4, [r1]
	ldrb	r3, [r4, #238]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L574
.L572:
	ldr	r3, .L575
	add	r0, r4, #232
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L574:
	add	r3, r1, #40960
	ldr	r1, [r4, #252]
	ldr	r0, [r3, #1920]
	bl	SM_ReleaseStreamSeg
	b	.L572
.L573:
	mov	r3, #2064
	ldr	r2, .L575+4
	ldr	r1, .L575+8
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L576:
	.align	2
.L575:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+576
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
	beq	.L595
	cmp	r0, #18
	ldrls	pc, [pc, r0, asl #2]
	b	.L579
.L581:
	.word	.L580
	.word	.L582
	.word	.L583
	.word	.L584
	.word	.L579
	.word	.L585
	.word	.L586
	.word	.L579
	.word	.L587
	.word	.L588
	.word	.L589
	.word	.L589
	.word	.L589
	.word	.L590
	.word	.L579
	.word	.L591
	.word	.L592
	.word	.L593
	.word	.L594
.L594:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2DEC_ClearCurPic
.L580:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264_ClearCurrPic
.L582:
	add	r3, r1, #49152
	add	r0, r1, #12736
	ldr	r1, [r3, #520]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1_ClearCurPic
.L583:
	mov	r0, r1
	str	r1, [fp, #-16]
	bl	MP4_ClearCurPic
	ldr	r1, [fp, #-16]
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP4_Clean_HeadPacket
.L584:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP2_ClearCurPic
.L585:
	mov	r0, #5
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_DIVX3
.L586:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS_ClearCurPic
.L587:
	mov	r0, #8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_Realx
.L588:
	mov	r0, #9
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_Realx
.L589:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L590:
	mov	r0, #13
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L591:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_ClearCurrPic
.L592:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_ClearCurrPic
.L593:
	mov	r0, #17
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L579:
	mov	r2, r0
	ldr	r1, .L596
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L595:
	mov	r3, #2080
	ldr	r2, .L596+4
	ldr	r1, .L596+8
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L597:
	.align	2
.L596:
	.word	.LC30
	.word	.LANCHOR0+596
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
	beq	.L659
	cmp	r2, #2
	ldr	r1, [r3]
	movne	r3, ip
	beq	.L660
.L601:
	ldrb	ip, [r1]	@ zero_extendqisi2
	ldrb	r4, [r1, #1]	@ zero_extendqisi2
	cmp	ip, #0
	ldrb	r5, [r1, #2]	@ zero_extendqisi2
	bne	.L604
	cmp	r4, #0
	beq	.L661
.L604:
	str	r5, [sp]
	mov	r3, r4
	mov	r2, ip
	ldr	r1, .L663
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
.L649:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L661:
	cmp	r5, #1
	bne	.L604
	cmp	r2, #18
	ldrls	pc, [pc, r2, asl #2]
	b	.L626
.L608:
	.word	.L607
	.word	.L609
	.word	.L610
	.word	.L611
	.word	.L626
	.word	.L626
	.word	.L612
	.word	.L626
	.word	.L626
	.word	.L626
	.word	.L626
	.word	.L626
	.word	.L626
	.word	.L626
	.word	.L626
	.word	.L613
	.word	.L614
	.word	.L626
	.word	.L615
.L660:
	ldrb	ip, [r6, #72]	@ zero_extendqisi2
	ands	r3, ip, #1
	beq	.L601
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
	beq	.L619
.L624:
	ldr	r2, [lr]
	cmp	r2, #0
	beq	.L619
	b	.L618
.L615:
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	add	r3, r2, #80
	add	r4, r2, #74
	sub	ip, r2, #179
	uxtb	r0, r3
	clz	ip, ip
	uxtb	r3, r4
	cmp	r3, #1
	cmphi	r0, #1
	mov	ip, ip, lsr #5
	movls	r3, #1
	movhi	r3, #0
	orrs	r3, ip, r3
	beq	.L638
.L656:
	ldr	r3, [lr]
	cmp	r3, #0
	bne	.L638
	mov	r2, #1
	str	r2, [lr]
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	mov	r0, r3
	sub	ip, r2, #179
	clz	ip, ip
	mov	ip, ip, lsr #5
.L622:
	cmp	r2, #182
	movne	r2, ip
	orreq	r2, ip, #1
	cmp	r2, #0
	beq	.L649
.L652:
	mov	r3, #0
	str	r3, [lr]
	b	.L649
.L607:
	mov	r0, lr
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	H264_IsNewPicNal
.L611:
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
	bne	.L662
	ldr	r3, .L663+4
	mvn	r5, #0
	mvn	r4, #0
	ldr	r0, [r3, r0, asl #2]
	add	r0, r0, #656
	ldrd	r2, [r0, #-8]
	cmp	r3, r5
	cmpeq	r2, r4
	bne	.L630
	ldr	r3, [lr]
	cmp	r3, #0
	bne	.L630
	sub	r3, ip, #1
	uxtb	r3, r3
	cmp	r3, #174
	bhi	.L630
	ldrd	r4, [r6, #24]
	mvn	r3, #0
	strd	r4, [r0, #-8]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
.L617:
	cmp	ip, #0
	streq	ip, [lr]
	moveq	r0, r3
	movne	r0, r3
	b	.L649
.L612:
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
	bne	.L656
.L638:
	mvn	r0, #0
	b	.L622
.L609:
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	sub	r3, r2, #12
	cmp	r2, #10
	cmpne	r3, #3
	bhi	.L641
	ldr	r3, [lr]
	cmp	r3, #0
	bne	.L641
	mov	r0, r3
	mov	r3, #1
	str	r3, [lr]
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
.L623:
	cmp	r2, #13
	bne	.L649
	b	.L652
.L610:
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
	bne	.L624
.L618:
	cmp	r3, #1
	bne	.L632
.L619:
	mov	r3, #1
	str	r3, [lr]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	mov	r0, #0
.L620:
	cmp	ip, #182
	bne	.L649
	b	.L652
.L613:
	mov	r0, lr
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	MVC_IsNewPicNal
.L614:
	mov	r0, lr
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	HEVC_IsNewPicNal
.L626:
	mvn	r0, #0
	b	.L649
.L662:
	ldr	r0, [lr]
	cmp	r0, #0
	bne	.L630
	mov	r2, #1
	mov	r3, r0
	str	r2, [lr]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	b	.L617
.L630:
	mvn	r3, #0
	b	.L617
.L659:
	movw	r3, #2356
	ldr	r2, .L663+8
	ldr	r1, .L663+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L649
.L641:
	mvn	r0, #0
	b	.L623
.L632:
	mvn	r0, #0
	b	.L620
.L664:
	.align	2
.L663:
	.word	.LC31
	.word	s_pstVfmwChan
	.word	.LANCHOR0+612
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
	bhi	.L671
	ldr	r3, .L672
	add	r4, r3, r0, lsl #2
	ldr	r0, [r4, #128]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L672+4
	ldr	r3, [r3, #220]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #128]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L671:
	movw	r3, #2414
	ldr	r2, .L672+8
	ldr	r1, .L672+12
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L673:
	.align	2
.L672:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+624
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
	bhi	.L680
	ldr	r3, .L681
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #128]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r0, #128]
	ldmfd	sp, {fp, sp, pc}
.L680:
	movw	r3, #2446
	ldr	r2, .L681+4
	ldr	r1, .L681+8
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L682:
	.align	2
.L681:
	.word	.LANCHOR1
	.word	.LANCHOR0+640
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
	bhi	.L689
	ldr	r3, .L690
	add	r3, r3, r0, lsl #2
	ldr	r0, [r3, #128]
	cmp	r0, #0
	beq	.L687
	add	r1, r0, #203776
	mov	ip, #0
	add	r1, r1, #512
	mov	r3, r0
	mov	r2, ip
	str	ip, [r0]
.L686:
	str	r2, [r3, #1048]
	add	r3, r3, #1056
	str	r2, [r3, #-12]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L686
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L689:
	mov	r3, #2464
	ldr	r2, .L690+4
	ldr	r1, .L690+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L687:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L691:
	.align	2
.L690:
	.word	.LANCHOR1
	.word	.LANCHOR0+664
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
	bhi	.L697
	ldr	r4, .L699
	add	r4, r4, r0, lsl #2
	ldr	r3, [r4, #128]
	cmp	r3, #0
	beq	.L698
.L695:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	InitUsdPool
.L698:
	ldr	r3, .L699+4
	movw	r0, #7688
	movt	r0, 3
	ldr	r3, [r3, #216]
	blx	r3
	str	r0, [r4, #128]
	b	.L695
.L697:
	movw	r3, #2399
	ldr	r2, .L699+8
	ldr	r1, .L699+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L700:
	.align	2
.L699:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+676
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
	bhi	.L706
	cmp	r1, #0
	beq	.L707
	ldr	r3, .L708
	add	r3, r3, r0, lsl #2
	ldr	r2, [r3, #128]
	cmp	r2, #0
	streq	r1, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	InitUsdPool
.L706:
	movw	r3, #2431
	ldr	r2, .L708+4
	ldr	r1, .L708+8
	mov	r0, #1
	bl	dprint_vfmw
.L703:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L707:
	mov	r3, #2432
	ldr	r2, .L708+4
	ldr	r1, .L708+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L703
.L709:
	.align	2
.L708:
	.word	.LANCHOR1
	.word	.LANCHOR0+688
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
	bhi	.L718
	ldr	r3, .L719
	add	r0, r3, r0, lsl #2
	ldr	ip, [r0, #128]
	cmp	ip, #0
	beq	.L717
	mov	r3, ip
	mov	r2, #0
	b	.L714
.L713:
	add	r2, r2, #1
	add	r3, r3, #1056
	cmp	r2, #192
	add	r3, r3, #8
	beq	.L717
.L714:
	ldr	r1, [r3, #1048]
	cmp	r1, #0
	bne	.L713
	ldr	r1, [r3, #1044]
	cmp	r1, #0
	bne	.L713
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
.L718:
	movw	r3, #2494
	ldr	r2, .L719+4
	ldr	r1, .L719+8
	mov	r0, #1
	bl	dprint_vfmw
.L717:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L720:
	.align	2
.L719:
	.word	.LANCHOR1
	.word	.LANCHOR0+708
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
	ldr	r2, .L723
	ldr	r1, .L723+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L724:
	.align	2
.L723:
	.word	.LANCHOR0+716
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
	ldr	r2, .L727
	ldr	r1, .L727+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L728:
	.align	2
.L727:
	.word	.LANCHOR0+732
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
	ldr	r2, .L731
	ldr	r1, .L731+4
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L732:
	.align	2
.L731:
	.word	.LANCHOR0+748
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
	beq	.L745
	cmp	r1, #0
	beq	.L746
	ldrh	r3, [r0, #4]
	ldrh	lr, [r0, #8]
	and	r3, r3, #63
	cmp	lr, r3
	beq	.L739
.L738:
	add	r2, r0, r3, lsl #2
	add	r3, r3, #1
	and	r3, r3, #63
	ldr	r2, [r2, #12]
	cmp	r2, #0
	beq	.L737
	ldr	ip, [r2, #148]
	ldr	r2, [r1, #148]
	cmp	ip, r2
	beq	.L740
.L737:
	cmp	r3, lr
	bne	.L738
.L739:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L740:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L746:
	mov	r0, r1
	ldr	r1, .L747
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L745:
	movw	r3, #2558
	ldr	r2, .L747+4
	ldr	r1, .L747+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L748:
	.align	2
.L747:
	.word	.LC5
	.word	.LANCHOR0+764
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
	beq	.L753
	ldrh	r0, [r4, #8]
	ldrh	r3, [r4, #6]
	cmp	r0, r3
	ldreqh	r3, [r4, #4]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L753:
	ldr	r2, .L754
	ldr	r1, .L754+4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L755:
	.align	2
.L754:
	.word	.LANCHOR0+784
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
	beq	.L767
	cmp	r1, #5
	ldrls	pc, [pc, r1, asl #2]
	b	.L758
.L760:
	.word	.L759
	.word	.L761
	.word	.L762
	.word	.L763
	.word	.L764
	.word	.L765
.L765:
	mov	r1, #0
	mov	r2, #2
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L759:
	mov	r1, #0
	mov	r2, #1
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L761:
	mov	r1, #4
	mov	r2, #3
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L762:
	mov	r1, #16
	mov	r2, #9
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L763:
	mov	r1, #221
	mov	r2, #100
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L764:
	mov	r1, #235
	mov	r2, #100
	str	r1, [r3, #100]
	str	r2, [r3, #104]
	ldmfd	sp, {fp, sp, pc}
.L758:
	mov	r0, #1
	mov	r2, r1
	mov	ip, #0
	str	r0, [r3, #104]
	ldr	r1, .L768
	str	ip, [r3, #100]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L767:
	movw	r3, #2606
	ldr	r2, .L768+4
	ldr	r1, .L768+8
	mov	r0, #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L769:
	.align	2
.L768:
	.word	.LC33
	.word	.LANCHOR0+800
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
	beq	.L774
	ldr	r0, [r0, #296]
	cmp	r0, #1
	mvnls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L774:
	movw	r3, #2654
	ldr	r2, .L775
	ldr	r1, .L775+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L776:
	.align	2
.L775:
	.word	.LANCHOR0+816
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
	beq	.L785
	ldr	r3, [r4, #332]
	cmp	r3, #1
	beq	.L782
	ldr	r2, [r4, #336]
	cmp	r2, #1
	beq	.L782
	cmp	r3, #2
	ldr	r0, [r4, #340]
	moveq	r3, #1
	subne	r3, r0, #1
	clzne	r3, r3
	movne	r3, r3, lsr #5
.L780:
	cmp	r0, #1
	movne	r0, r3
	orreq	r0, r3, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L782:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L785:
	movw	r3, #2669
	ldr	r2, .L786
	ldr	r1, .L786+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L787:
	.align	2
.L786:
	.word	.LANCHOR0+836
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
	bhi	.L792
	ldr	r1, .L794
	ldr	r1, [r1, r0, asl #2]
	ldr	r1, [r1, #128]
	cmp	r1, #0
	ldrd	r0, [fp, #4]
	bne	.L793
	subs	r0, r2, r0
	sbc	r1, r3, r1
	cmp	r1, #0
	cmpeq	r0, #1000
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L793:
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
.L792:
	movw	r3, #2694
	ldr	r2, .L794+4
	ldr	r1, .L794+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L795:
	.align	2
.L794:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+852
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
	.type	__func__.14782, %object
	.size	__func__.14782, 13
__func__.14782:
	.ascii	"PrintVoQueue\000"
	.space	3
	.type	__func__.14788, %object
	.size	__func__.14788, 13
__func__.14788:
	.ascii	"ResetVoQueue\000"
	.space	3
	.type	__func__.14794, %object
	.size	__func__.14794, 20
__func__.14794:
	.ascii	"ReturnImageToSyntax\000"
	.type	__func__.14859, %object
	.size	__func__.14859, 19
__func__.14859:
	.ascii	"InsertImgToVoQueue\000"
	.space	1
	.type	__FUNCTION__.14862, %object
	.size	__FUNCTION__.14862, 19
__FUNCTION__.14862:
	.ascii	"InsertImgToVoQueue\000"
	.space	1
	.type	__func__.14870, %object
	.size	__func__.14870, 15
__func__.14870:
	.ascii	"GetQueueImgNum\000"
	.space	1
	.type	__func__.14900, %object
	.size	__func__.14900, 20
__func__.14900:
	.ascii	"SYNTAX_ReceiveImage\000"
	.type	__func__.14947, %object
	.size	__func__.14947, 20
__func__.14947:
	.ascii	"SYNTAX_ReleaseImage\000"
	.type	__func__.14956, %object
	.size	__func__.14956, 19
__func__.14956:
	.ascii	"SYNTAX_ReturnImage\000"
	.space	1
	.type	__func__.14982, %object
	.size	__func__.14982, 18
__func__.14982:
	.ascii	"DecodeStream_H264\000"
	.space	2
	.type	__func__.14989, %object
	.size	__func__.14989, 18
__func__.14989:
	.ascii	"DecodeStream_HEVC\000"
	.space	2
	.type	__func__.14994, %object
	.size	__func__.14994, 17
__func__.14994:
	.ascii	"DecodeStream_VP9\000"
	.space	3
	.type	__func__.15001, %object
	.size	__func__.15001, 17
__func__.15001:
	.ascii	"DecodeStream_MVC\000"
	.space	3
	.type	__func__.15014, %object
	.size	__func__.15014, 21
__func__.15014:
	.ascii	"DecodeStream_VC1_Smp\000"
	.space	3
	.type	__func__.15053, %object
	.size	__func__.15053, 19
__func__.15053:
	.ascii	"DecodeStream_REAL8\000"
	.space	1
	.type	__func__.15059, %object
	.size	__func__.15059, 19
__func__.15059:
	.ascii	"DecodeStream_REAL9\000"
	.space	1
	.type	__func__.15065, %object
	.size	__func__.15065, 19
__func__.15065:
	.ascii	"DecodeStream_DIVX3\000"
	.space	1
	.type	__func__.15071, %object
	.size	__func__.15071, 17
__func__.15071:
	.ascii	"DecodeStream_VP8\000"
	.space	3
	.type	__func__.15077, %object
	.size	__func__.15077, 18
__func__.15077:
	.ascii	"DecodeStream_VP6x\000"
	.space	2
	.type	__func__.15107, %object
	.size	__func__.15107, 7
__func__.15107:
	.ascii	"SegMan\000"
	.space	1
	.type	__func__.15008, %object
	.size	__func__.15008, 21
__func__.15008:
	.ascii	"DecodeStream_VC1_Adv\000"
	.space	3
	.type	__func__.15019, %object
	.size	__func__.15019, 17
__func__.15019:
	.ascii	"DecodeStream_VC1\000"
	.space	3
	.type	__func__.15026, %object
	.size	__func__.15026, 19
__func__.15026:
	.ascii	"DecodeStream_MPEG2\000"
	.space	1
	.type	__func__.15033, %object
	.size	__func__.15033, 19
__func__.15033:
	.ascii	"DecodeStream_MPEG4\000"
	.space	1
	.type	__func__.15040, %object
	.size	__func__.15040, 17
__func__.15040:
	.ascii	"DecodeStream_AVS\000"
	.space	3
	.type	__func__.15047, %object
	.size	__func__.15047, 18
__func__.15047:
	.ascii	"DecodeStream_AVS2\000"
	.space	2
	.type	__func__.15083, %object
	.size	__func__.15083, 13
__func__.15083:
	.ascii	"DecodeStream\000"
	.space	3
	.type	__func__.15113, %object
	.size	__func__.15113, 14
__func__.15113:
	.ascii	"ReleasePacket\000"
	.space	2
	.type	__func__.15129, %object
	.size	__func__.15129, 18
__func__.15129:
	.ascii	"ReleaseCurPic_VPx\000"
	.space	2
	.type	__func__.15142, %object
	.size	__func__.15142, 20
__func__.15142:
	.ascii	"ReleaseCurPic_Realx\000"
	.type	__func__.15152, %object
	.size	__func__.15152, 20
__func__.15152:
	.ascii	"ReleaseCurPic_DIVX3\000"
	.type	__func__.15157, %object
	.size	__func__.15157, 14
__func__.15157:
	.ascii	"ReleaseCurPic\000"
	.space	2
	.type	__func__.15237, %object
	.size	__func__.15237, 12
__func__.15237:
	.ascii	"IsNewpicSeg\000"
	.type	__func__.15247, %object
	.size	__func__.15247, 13
__func__.15247:
	.ascii	"CloseUsdPool\000"
	.space	3
	.type	__func__.15257, %object
	.size	__func__.15257, 21
__func__.15257:
	.ascii	"CloseUsdPool_WithMem\000"
	.space	3
	.type	__func__.15263, %object
	.size	__func__.15263, 12
__func__.15263:
	.ascii	"InitUsdPool\000"
	.type	__func__.15243, %object
	.size	__func__.15243, 12
__func__.15243:
	.ascii	"OpenUsdPool\000"
	.type	__func__.15253, %object
	.size	__func__.15253, 20
__func__.15253:
	.ascii	"OpenUsdPool_WithMem\000"
	.type	__func__.15273, %object
	.size	__func__.15273, 7
__func__.15273:
	.ascii	"GetUsd\000"
	.space	1
	.type	__func__.15281, %object
	.size	__func__.15281, 13
__func__.15281:
	.ascii	"FreeUsdByDec\000"
	.space	3
	.type	__func__.15286, %object
	.size	__func__.15286, 13
__func__.15286:
	.ascii	"MarkUsdByDnr\000"
	.space	3
	.type	__func__.15291, %object
	.size	__func__.15291, 15
__func__.15291:
	.ascii	"UnMarkUsdByDnr\000"
	.space	1
	.type	__func__.15297, %object
	.size	__func__.15297, 17
__func__.15297:
	.ascii	"IsImageInVoQueue\000"
	.space	3
	.type	__func__.15303, %object
	.size	__func__.15303, 15
__func__.15303:
	.ascii	"IsVoQueueEmpty\000"
	.space	1
	.type	__func__.15308, %object
	.size	__func__.15308, 15
__func__.15308:
	.ascii	"SetAspectRatio\000"
	.space	1
	.type	__func__.15321, %object
	.size	__func__.15321, 17
__func__.15321:
	.ascii	"GetVoLastImageID\000"
	.space	3
	.type	__func__.15326, %object
	.size	__func__.15326, 16
__func__.15326:
	.ascii	"IsMain10Profile\000"
	.type	__func__.15333, %object
	.size	__func__.15333, 12
__func__.15333:
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
	.type	last_rec_pos_time.14858, %object
	.size	last_rec_pos_time.14858, 128
last_rec_pos_time.14858:
	.space	128
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 128
pstVdecUsdPool:
	.space	128
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
