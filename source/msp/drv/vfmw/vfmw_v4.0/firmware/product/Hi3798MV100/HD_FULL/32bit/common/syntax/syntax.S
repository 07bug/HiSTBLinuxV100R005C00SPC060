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
	.global	InitVoQueue
	.type	InitVoQueue, %function
InitVoQueue:
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
	ldr	r5, .L6
	mov	r4, r0
	ldr	r1, .L6+4
	mov	r0, #12
	ldr	r3, [r5, #68]
	blx	r3
	cmp	r4, #0
	beq	.L5
	mov	r2, #0
	mov	r3, #64
	mov	r0, #1
	strh	r3, [r4]	@ movhi
	strh	r2, [r4, #2]	@ movhi
	mvn	r3, #0
	strh	r2, [r4, #4]	@ movhi
	strh	r2, [r4, #6]	@ movhi
	strh	r2, [r4, #8]	@ movhi
	str	r2, [r4, #344]
	str	r2, [r4, #316]
	str	r3, [r4, #272]
	str	r3, [r4, #292]
	str	r3, [r4, #288]
	str	r3, [r4, #284]
	str	r3, [r4, #276]
	str	r3, [r4, #280]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5:
	ldr	r4, [r5, #68]
	mov	r3, #46
	ldr	r2, .L6+8
	mov	r0, #1
	ldr	r1, .L6+12
	blx	r4
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L7:
	.align	2
.L6:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LANCHOR0
	.word	.LC1
	UNWIND(.fnend)
	.size	InitVoQueue, .-InitVoQueue
	.align	2
	.global	PrintVoQueue
	.type	PrintVoQueue, %function
PrintVoQueue:
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
	subs	r5, r0, #0
	beq	.L14
	ldrh	ip, [r5, #8]
	mov	r0, #1
	ldr	r6, .L15
	ldrh	r3, [r5, #4]
	ldrh	r2, [r5, #6]
	ldr	r4, [r6, #68]
	ldr	r1, .L15+4
	str	ip, [sp]
	blx	r4
	ldrh	r3, [r5, #4]
	ldrh	r2, [r5, #8]
	and	r4, r3, #63
	cmp	r2, r4
	bne	.L13
	b	.L12
.L11:
	add	r2, r5, r4, lsl #2
	ldr	r3, [r6, #68]
	ldr	r1, .L15+8
	mov	r0, #1
	ldr	r2, [r2, #12]
	ldr	r2, [r2, #196]
	blx	r3
	add	r3, r4, #1
	ldrh	r2, [r5, #8]
	and	r4, r3, #63
	cmp	r2, r4
	beq	.L12
.L13:
	tst	r3, #7
	bne	.L11
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L15+12
	blx	r3
	b	.L11
.L12:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L15+12
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	bx	r3
.L14:
	ldr	ip, .L15
	mov	r3, #74
	ldr	r2, .L15+16
	mov	r0, #1
	ldr	r1, .L15+20
	ldr	ip, [ip, #68]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	bx	ip
.L16:
	.align	2
.L15:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC4
	.word	.LC3
	.word	.LANCHOR0+12
	.word	.LC1
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
	beq	.L22
	ldr	r5, .L24
	mov	r0, #2
	ldr	r3, [r5, #12]
	blx	r3
	ldrh	r2, [r4, #6]
	ldrh	r3, [r4, #4]
	ldrh	r1, [r4, #8]
	cmp	r2, r3
	beq	.L23
.L20:
	str	r1, [sp]
	mov	r0, #1
	ldr	r6, [r5, #68]
	ldr	r1, .L24+4
	blx	r6
.L21:
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
.L23:
	cmp	r2, r1
	bne	.L20
	b	.L21
.L22:
	ldr	ip, .L24
	mov	r3, #103
	ldr	r2, .L24+8
	mov	r0, #1
	ldr	r1, .L24+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L25:
	.align	2
.L24:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	.word	.LANCHOR0+28
	.word	.LC1
	UNWIND(.fnend)
	.size	ResetVoQueue, .-ResetVoQueue
	.global	__aeabi_uidiv
	.align	2
	.global	InsertImgToVoQueue
	.type	InsertImgToVoQueue, %function
InsertImgToVoQueue:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 16
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
	cmp	r0, #15
	mov	r5, r3
	mov	r7, r0
	str	r1, [fp, #-56]
	mov	r10, r2
	ldr	r4, [fp, #4]
	movwhi	r3, #365
	ldrhi	ip, .L130
	bhi	.L118
	cmp	r2, #0
	cmpne	r5, #0
	beq	.L120
	cmp	r4, #0
	beq	.L121
	ldr	r6, .L130
	mov	r0, #2
	ldr	r1, .L130+4
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r6, #12]
	mov	r0, #2
	blx	r3
	ldrh	r9, [r5, #4]
	ldrh	r1, [r5, #8]
	and	r9, r9, #63
	cmp	r1, r9
	ldrne	r8, [fp, #-56]
	bne	.L36
	b	.L35
.L34:
	add	r9, r9, #1
	and	r9, r9, #63
	cmp	r1, r9
	beq	.L122
.L36:
	add	r3, r5, r9, lsl #2
	ldr	r3, [r3, #12]
	cmp	r3, #0
	beq	.L34
	ldr	r2, [r3, #196]
	ldr	r3, [r4, #196]
	cmp	r2, r3
	bne	.L34
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L130+8
	add	r9, r9, #1
	blx	r3
	mov	r3, #1000
	str	r3, [r4, #200]
	and	r9, r9, #63
	ldrh	r1, [r5, #8]
	cmp	r1, r9
	bne	.L36
.L122:
	str	r8, [fp, #-56]
.L35:
	ldr	r2, [r4, #200]
	cmp	r2, #100
	bhi	.L123
	ldr	r3, [r4, #164]
	ldr	r1, [r4, #168]
	cmp	r3, #31
	bhi	.L124
.L37:
	str	r1, [sp]
	mov	r0, #0
	ldr	r5, [r6, #68]
	ldr	r1, .L130+12
	blx	r5
	ldr	r3, [r4, #200]
	cmp	r3, #1000
	beq	.L40
	ldr	r3, [fp, #-56]
	cmp	r3, #19
	ldrls	pc, [pc, r3, asl #2]
	b	.L40
.L42:
	.word	.L41
	.word	.L43
	.word	.L44
	.word	.L45
	.word	.L40
	.word	.L46
	.word	.L47
	.word	.L40
	.word	.L48
	.word	.L49
	.word	.L50
	.word	.L50
	.word	.L50
	.word	.L51
	.word	.L40
	.word	.L40
	.word	.L52
	.word	.L53
	.word	.L40
	.word	.L54
.L51:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	VP8DEC_RecycleImage
.L40:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, #1
.L28:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L124:
	cmp	r1, #31
	bls	.L37
	ldr	r3, [fp, #-56]
	ldrd	r0, [r4, #8]
	cmp	r3, #19
	strd	r0, [r4]
	beq	.L75
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
	sub	r3, r3, #8
	beq	.L125
	cmp	r3, #1
	bls	.L57
	mov	r2, r0
	mov	r3, r1
	mvn	r0, #0
	mvn	r1, #0
	b	.L55
.L123:
	ldr	r3, [r4, #164]
	ldr	r1, [r4, #168]
	b	.L37
.L125:
	cmp	r3, #1
	bls	.L126
.L75:
	mov	r2, r0
	mov	r3, r1
.L55:
	ldrd	r8, [r4, #16]
	strd	r0, [r4, #8]
	strd	r0, [sp]
	mov	r0, #29
	ldr	ip, [r6, #68]
	ldr	r1, .L130+16
	strd	r8, [sp, #8]
	blx	ip
	ldr	r3, [r4, #172]
	cmp	r3, #0
	beq	.L58
	ldr	r3, [r4, #176]
	cmp	r3, #0
	bne	.L127
.L58:
	ldr	r2, [r4, #164]
	ldr	r3, [r4, #168]
	mov	r1, r2, lsr #1
	str	r2, [r4, #172]
	str	r3, [r4, #176]
	mov	r3, r3, lsr #1
	str	r1, [r4, #180]
	str	r3, [r4, #184]
.L59:
	str	r2, [r5, #300]
	ldr	r3, [r4, #168]
	ldr	r1, [r5, #280]
	ldr	r8, .L130+20
	str	r3, [r5, #304]
	ldr	r3, [r4, #160]
	ubfx	r3, r3, #5, #3
	str	r3, [r5, #308]
	ldr	r3, [r4, #160]
	str	r3, [r5, #312]
	ldr	r3, [r4, #160]
	ldr	r2, [r4, #204]
	ubfx	r9, r3, #14, #3
	ubfx	r10, r3, #8, #2
	ldr	r3, [r5, #316]
	cmp	r2, r1
	ldr	lr, [r4, #176]
	ldr	r0, [r4, #180]
	ldrh	ip, [r4, #172]
	ldrh	r1, [r4, #184]
	strne	r2, [r5, #320]
	add	r2, r3, #1
	str	r2, [r5, #316]
	orr	ip, ip, lr, asl #16
	str	r3, [r4, #208]
	orr	r1, r1, r0, asl #16
	ldr	r3, [r5, #272]
	str	ip, [fp, #-56]
	cmp	r3, r9
	str	r1, [fp, #-60]
	beq	.L61
	ldr	r2, [r8]
	subs	ip, r2, #0
	beq	.L62
	strb	r3, [fp, #-52]
	sub	r2, fp, #52
	mov	r3, #2
	strb	r9, [fp, #-51]
	mov	r1, #7
	mov	r0, r7
	blx	ip
.L62:
	str	r9, [r5, #272]
.L61:
	ldr	r3, [r5, #276]
	cmp	r3, r10
	beq	.L63
	ldr	r9, [r8]
	cmp	r9, #0
	beq	.L64
	sub	r2, fp, #44
	mov	r3, #1
	mov	r1, #4
	mov	r0, r7
	strb	r10, [r2, #-8]!
	blx	r9
.L64:
	str	r10, [r5, #276]
.L63:
	ldr	r3, [r5, #288]
	ldr	r2, [fp, #-56]
	cmp	r3, r2
	beq	.L128
.L65:
	ldr	r3, [fp, #-56]
	ldr	r9, [r8]
	str	r3, [r5, #288]
	cmp	r9, #0
	ldr	r3, [fp, #-60]
	str	r3, [r5, #292]
	beq	.L66
	ldr	r1, [r4, #176]
	mov	r3, #8
	ldr	r0, [r4, #180]
	sub	r2, fp, #52
	ldr	lr, [r4, #172]
	ldr	ip, [r4, #184]
	strh	r1, [fp, #-50]	@ movhi
	mov	r1, #1
	strh	r0, [fp, #-48]	@ movhi
	mov	r0, r7
	strh	lr, [fp, #-52]	@ movhi
	strh	ip, [fp, #-46]	@ movhi
	blx	r9
.L66:
	ldr	r1, [r4, #108]
	mov	r0, #12
	ldr	r2, [r4, #104]
	ldr	r3, [r4, #192]
	str	r1, [r4, #92]
	str	r2, [r4, #88]
	add	r2, r3, r2
	ldr	ip, [r4, #196]
	add	r3, r1, r3
	str	r2, [r4, #96]
	str	r3, [r4, #100]
	ldrh	r1, [r5, #8]
	ldrh	r3, [r5, #6]
	ldrh	r2, [r5, #4]
	ldr	r9, .L130+24
	str	ip, [sp, #4]
	ldr	r10, [r6, #68]
	str	r1, [sp]
	ldr	r1, .L130+28
	blx	r10
	ldrh	r2, [r5, #8]
	mov	r10, #300
	ldr	r3, .L130+32
	mla	r10, r10, r7, r9
	add	r0, r5, r2, lsl #2
	add	r2, r2, #1
	mov	r1, #5
	str	r4, [r0, #12]
	and	r2, r2, #63
	strh	r2, [r5, #8]	@ movhi
	mov	r0, r7
	ldr	ip, [r4, #148]
	ldr	r2, [r3, r7, asl #2]
	str	r3, [fp, #-56]
	str	ip, [r10, #20]
	ldr	ip, [r4, #196]
	add	ip, ip, #2
	str	ip, [r5, #296]
	bl	VDEC_Lowdelay_Event_Time
	ldr	r3, [fp, #-56]
	ldr	r1, [r6, #16]
	mov	r0, #2
	ldr	r2, [r3, r7, asl #2]
	add	r2, r2, #1
	str	r2, [r3, r7, asl #2]
	blx	r1
	ldr	r3, .L130+36
	ldr	r3, [r3, r7, asl #2]
	ldr	r3, [r3, #128]
	cmp	r3, #0
	beq	.L68
	ldr	r3, [r10, #8]
	cmp	r3, #0
	movne	r2, #100
	mulne	r3, r2, r3
	strne	r3, [r4, #188]
.L68:
	ldr	r5, [r8]
	cmp	r5, #0
	beq	.L69
	mov	r2, r4
	mov	r3, #504
	mov	r1, #5
	mov	r0, r7
	blx	r5
.L69:
	mov	r0, #8
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L129
.L71:
	mov	r4, #300
	ldr	r2, [r6]
	mul	r4, r4, r7
	add	r5, r9, r4
	ldr	r3, [r5, #4]
	add	r3, r3, #1
	str	r3, [r5, #4]
	blx	r2
	ldr	r1, [r9, r4]
	rsb	r1, r1, r0
	mov	r6, r0
	cmp	r1, #300
	movcc	r0, #1
	bcc	.L28
	ldr	r3, [r5, #4]
	cmp	r3, #0
	beq	.L73
	movw	r0, #10000
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	str	r0, [r5, #8]
.L73:
	mov	r3, #300
	mov	r2, #0
	mul	r7, r3, r7
	mov	r0, #1
	add	r3, r9, r7
	str	r6, [r9, r7]
	str	r2, [r3, #4]
	b	.L28
.L41:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	H264DEC_RecycleImage
	b	.L40
.L46:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	DIVX3DEC_RecycleImage
	b	.L40
.L45:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	MPEG2DEC_RecycleImage
	b	.L40
.L44:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	MPEG4DEC_RecycleImage
	b	.L40
.L43:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	VC1DEC_RecycleImage
	b	.L40
.L54:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	USERDEC_RecycleImage
	b	.L40
.L53:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	HEVC_DECRecycleImage
	b	.L40
.L52:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	MVC_DEC_RecycleImage
	b	.L40
.L50:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	VP6DEC_RecycleImage
	b	.L40
.L49:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	REAL9DEC_RecycleImage
	b	.L40
.L48:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	REAL8DEC_RecycleImage
	b	.L40
.L47:
	ldr	r1, [r4, #196]
	mov	r0, r10
	bl	AVSDEC_RecycleImage
	b	.L40
.L127:
	ldr	r2, [fp, #-56]
	sub	r3, r2, #16
	cmp	r2, #0
	cmpne	r3, #1
	ldrls	r2, [r4, #164]
	bhi	.L58
	b	.L59
.L126:
	ldr	r3, [r4, #160]
	and	r3, r3, #3
	cmp	r3, #2
	bne	.L75
.L57:
	mvn	lr, #0
	str	lr, [r4]
	mov	r2, lr
	mov	r0, lr
	mov	r3, lr
	str	lr, [r4, #4]
	mov	r1, lr
	b	.L55
.L120:
	ldr	ip, .L130
	movw	r3, #366
.L118:
	ldr	r2, .L130+40
	mov	r0, #1
	ldr	r1, .L130+44
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #1
	b	.L28
.L129:
	ldr	r3, [r6]
	blx	r3
	ldr	ip, .L130+48
	ldr	r2, .L130+52
	ldr	r3, [ip, r7, asl #2]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	mov	lr, r0
	cmp	r3, r2
	bls	.L71
	mov	r2, r7, asl #24
	movw	r1, #583
	add	r2, r2, #524288
	ldr	r0, .L130+56
	str	lr, [ip, r7, asl #2]
	bl	DBG_AddTrace
	b	.L71
.L128:
	ldr	r3, [r5, #292]
	ldr	r2, [fp, #-60]
	cmp	r3, r2
	bne	.L65
	b	.L66
.L121:
	ldr	r3, .L130
	mov	r0, r4
	ldr	r1, .L130+60
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #1
	b	.L28
.L131:
	.align	2
.L130:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	g_event_report
	.word	g_VfmwChanStat
	.word	.LC11
	.word	g_LowDelaySeqIndex
	.word	s_pstVfmwChan
	.word	.LANCHOR0+44
	.word	.LC1
	.word	.LANCHOR1
	.word	g_TraceFramePeriod
	.word	.LANCHOR0+64
	.word	.LC6
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
	bne	.L139
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
.L139:
	ldr	ip, .L140
	mov	r3, #624
	ldr	r2, .L140+4
	mov	r0, #1
	ldr	r1, .L140+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L141:
	.align	2
.L140:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+84
	.word	.LC1
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r1
	beq	.L163
	ldr	r3, [r0]
	cmp	r3, #19
	ldrls	pc, [pc, r3, asl #2]
	b	.L161
.L146:
	.word	.L158
	.word	.L147
	.word	.L148
	.word	.L149
	.word	.L161
	.word	.L150
	.word	.L151
	.word	.L161
	.word	.L152
	.word	.L153
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L155
	.word	.L161
	.word	.L161
	.word	.L156
	.word	.L157
	.word	.L161
	.word	.L158
.L158:
	add	r4, r0, #16
.L159:
	ldr	r6, .L164
	mov	r0, #2
	ldr	r3, [r6, #12]
	blx	r3
	ldrh	r3, [r4, #6]
	ldrh	r2, [r4, #8]
	cmp	r2, r3
	mvneq	r5, #2
	beq	.L160
	add	r3, r4, r3, lsl #2
	ldr	r8, [r6, #52]
	mov	r2, #504
	mov	r0, r7
	ldr	r1, [r3, #12]
	mov	r5, #1
	blx	r8
	ldr	r1, [r7, #196]
	ldrh	r3, [r4, #6]
	mov	r0, #12
	ldrh	r2, [r4, #4]
	str	r1, [sp, #4]
	ldrh	r1, [r4, #8]
	ldr	r8, [r6, #68]
	str	r1, [sp]
	ldr	r1, .L164+4
	blx	r8
	ldr	r3, [r7, #196]
	ldr	r2, [r4, #344]
	add	r3, r3, r2
	str	r3, [r7, #196]
	ldrh	r3, [r4, #6]
	add	r3, r3, r5
	and	r3, r3, #63
	strh	r3, [r4, #6]	@ movhi
.L160:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r5
.L144:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L147:
	add	r4, r0, #48384
	add	r4, r4, #104
	b	.L159
.L148:
	add	r4, r0, #22528
	add	r4, r4, #88
	b	.L159
.L149:
	add	r4, r0, #79872
	add	r4, r4, #648
	b	.L159
.L150:
	add	r4, r0, #33792
	add	r4, r4, #24
	b	.L159
.L151:
	add	r4, r0, #16192
	add	r4, r4, #24
	b	.L159
.L152:
	add	r4, r0, #46080
	add	r4, r4, #64
	b	.L159
.L153:
	add	r4, r0, #46080
	add	r4, r4, #48
	b	.L159
.L154:
	add	r4, r0, #12608
	add	r4, r4, #48
	b	.L159
.L155:
	add	r4, r0, #8128
	add	r4, r4, #48
	b	.L159
.L156:
	add	r4, r0, #592
	b	.L159
.L157:
	add	r4, r0, #50944
	add	r4, r4, #64
	b	.L159
.L161:
	mvn	r0, #1
	b	.L144
.L163:
	ldr	ip, .L164
	movw	r3, #646
	ldr	r2, .L164+8
	mov	r0, #1
	ldr	r1, .L164+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #1
	b	.L144
.L165:
	.align	2
.L164:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC12
	.word	.LANCHOR0+100
	.word	.LC1
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r7, r0, #0
	mov	r5, r1
	beq	.L254
	cmp	r1, #0
	beq	.L255
	ldr	r3, [r7]
	cmp	r3, #19
	ldrls	pc, [pc, r3, asl #2]
	b	.L210
.L171:
	.word	.L183
	.word	.L172
	.word	.L173
	.word	.L174
	.word	.L210
	.word	.L175
	.word	.L176
	.word	.L210
	.word	.L177
	.word	.L178
	.word	.L179
	.word	.L179
	.word	.L179
	.word	.L180
	.word	.L210
	.word	.L210
	.word	.L181
	.word	.L182
	.word	.L210
	.word	.L183
.L183:
	add	r8, r7, #16
.L184:
	ldr	r6, .L257
	mov	r0, #2
	ldr	r3, [r6, #12]
	blx	r3
	ldr	r3, [r5, #196]
	ldr	r2, [r8, #344]
	rsb	r2, r2, r3
	str	r2, [r5, #196]
	ldrh	r4, [r8, #4]
	ldrh	r1, [r8, #6]
	and	r4, r4, #63
	cmp	r1, r4
	bne	.L208
	b	.L209
.L189:
	add	r4, r4, #1
	and	r4, r4, #63
	cmp	r1, r4
	beq	.L256
.L208:
	add	r9, r4, #2
	add	r3, r8, r9, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L187
	ldr	r3, [r3, #196]
	ldr	ip, [r5, #196]
	rsb	ip, r3, ip
	clz	ip, ip
	mov	ip, ip, lsr #5
	cmp	ip, #0
	beq	.L189
.L188:
	ldrh	r0, [r8, #4]
	b	.L191
.L212:
	mov	r4, r2
.L191:
	cmp	r4, #0
	mov	r2, #63
	subne	r2, r4, #1
	add	r1, r8, r9, lsl #2
	add	r3, r2, #2
	cmp	r4, r0
	add	lr, r8, r3, lsl #2
	mov	r9, r3
	ldr	r3, [lr, #4]
	str	r3, [r1, #4]
	bne	.L212
	cmp	ip, #1
	add	r2, r4, #1
	and	r2, r2, #63
	strh	r2, [r8, #4]	@ movhi
	beq	.L253
	ldrh	r1, [r8, #6]
	add	r4, r4, #1
	and	r4, r4, #63
	cmp	r1, r4
	bne	.L208
.L256:
	ldr	r2, [r5, #196]
.L209:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L257+4
	mvn	r4, #1
	blx	r3
.L186:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r4
.L168:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L172:
	add	r8, r7, #48384
	add	r8, r8, #104
	b	.L184
.L175:
	add	r8, r7, #33792
	add	r8, r8, #24
	b	.L184
.L176:
	add	r8, r7, #16192
	add	r8, r8, #24
	b	.L184
.L177:
	add	r8, r7, #46080
	add	r8, r8, #64
	b	.L184
.L178:
	add	r8, r7, #46080
	add	r8, r8, #48
	b	.L184
.L179:
	add	r8, r7, #12608
	add	r8, r8, #48
	b	.L184
.L180:
	add	r8, r7, #8128
	add	r8, r8, #48
	b	.L184
.L181:
	add	r8, r7, #592
	b	.L184
.L182:
	add	r8, r7, #50944
	add	r8, r8, #64
	b	.L184
.L173:
	add	r8, r7, #22528
	add	r8, r8, #88
	b	.L184
.L174:
	add	r8, r7, #79872
	add	r8, r8, #648
	b	.L184
.L187:
	ldr	r3, [r6, #68]
	mov	r2, r4
	ldr	r1, .L257+8
	mov	r0, #1
	blx	r3
	mov	ip, #2
	b	.L188
.L253:
	ldr	r1, [r5, #196]
	mov	r0, #12
	ldrh	r3, [r8, #6]
	ldr	r4, [r6, #68]
	str	r1, [sp, #4]
	ldrh	ip, [r8, #8]
	ldr	r1, .L257+12
	str	ip, [sp]
	blx	r4
	ldr	r3, [r7]
	cmp	r3, #19
	ldrls	pc, [pc, r3, asl #2]
	b	.L214
.L193:
	.word	.L192
	.word	.L194
	.word	.L195
	.word	.L196
	.word	.L214
	.word	.L197
	.word	.L198
	.word	.L214
	.word	.L199
	.word	.L200
	.word	.L201
	.word	.L201
	.word	.L201
	.word	.L202
	.word	.L214
	.word	.L214
	.word	.L203
	.word	.L204
	.word	.L214
	.word	.L205
.L210:
	mvn	r0, #1
	b	.L168
.L205:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	USERDEC_RecycleImage
	cmp	r0, #1
	beq	.L207
.L206:
	mvn	r4, #19
	b	.L186
.L204:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	HEVC_DECRecycleImage
	cmp	r0, #0
	bne	.L206
.L207:
	mov	r4, #1
	b	.L186
.L203:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	MVC_DEC_RecycleImage
	cmp	r0, #0
	beq	.L207
	b	.L206
.L202:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	VP8DEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L201:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	VP6DEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L200:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	REAL9DEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L199:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	REAL8DEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L198:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	AVSDEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L197:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	DIVX3DEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L196:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	MPEG2DEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L195:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	MPEG4DEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L194:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	VC1DEC_RecycleImage
	cmp	r0, #1
	bne	.L206
	b	.L207
.L192:
	ldr	r1, [r5, #196]
	add	r0, r7, #8
	bl	H264DEC_RecycleImage
	cmp	r0, #0
	bne	.L206
	b	.L207
.L214:
	mvn	r4, #1
	b	.L186
.L254:
	ldr	ip, .L257
	movw	r3, #775
	ldr	r2, .L257+16
	mov	r0, #1
	ldr	r1, .L257+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #1
	b	.L168
.L255:
	ldr	r3, .L257
	mov	r0, r1
	ldr	r1, .L257+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #1
	b	.L168
.L258:
	.align	2
.L257:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LANCHOR0+120
	.word	.LC1
	.word	.LC13
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
	beq	.L278
	ldr	r3, [r0]
	cmp	r3, #19
	ldrls	pc, [pc, r3, asl #2]
	b	.L277
.L263:
	.word	.L275
	.word	.L264
	.word	.L265
	.word	.L266
	.word	.L277
	.word	.L267
	.word	.L268
	.word	.L277
	.word	.L269
	.word	.L270
	.word	.L271
	.word	.L271
	.word	.L271
	.word	.L272
	.word	.L277
	.word	.L277
	.word	.L273
	.word	.L274
	.word	.L277
	.word	.L275
.L275:
	add	r4, r0, #16
.L276:
	ldr	r5, .L279
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
.L264:
	add	r4, r0, #48384
	add	r4, r4, #104
	b	.L276
.L265:
	add	r4, r0, #22528
	add	r4, r4, #88
	b	.L276
.L266:
	add	r4, r0, #79872
	add	r4, r4, #648
	b	.L276
.L267:
	add	r4, r0, #33792
	add	r4, r4, #24
	b	.L276
.L268:
	add	r4, r0, #16192
	add	r4, r4, #24
	b	.L276
.L269:
	add	r4, r0, #46080
	add	r4, r4, #64
	b	.L276
.L270:
	add	r4, r0, #46080
	add	r4, r4, #48
	b	.L276
.L271:
	add	r4, r0, #12608
	add	r4, r4, #48
	b	.L276
.L272:
	add	r4, r0, #8128
	add	r4, r4, #48
	b	.L276
.L273:
	add	r4, r0, #592
	b	.L276
.L274:
	add	r4, r0, #50944
	add	r4, r4, #64
	b	.L276
.L277:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L278:
	ldr	ip, .L279
	movw	r3, #1043
	ldr	r2, .L279+4
	mov	r0, #1
	ldr	r1, .L279+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L280:
	.align	2
.L279:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+140
	.word	.LC1
	UNWIND(.fnend)
	.size	SYNTAX_ReturnImage, .-SYNTAX_ReturnImage
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
	cmp	r0, #15
	mov	r5, r0
	mov	r4, r1
	bhi	.L305
	cmp	r1, #0
	beq	.L284
	ldr	r3, [r1, #8]
	cmp	r3, #0
	beq	.L284
	ldr	r3, .L310
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #1404]
	cmp	r2, #1
	beq	.L306
.L286:
	ldrb	r6, [r4, #13]	@ zero_extendqisi2
	mov	r7, #0
	strb	r7, [r4, #408]
	cmp	r6, #1
	beq	.L307
	cmp	r6, #0
	beq	.L308
.L291:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L308:
	ldr	r9, .L310+4
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
	bls	.L291
	ldr	r1, [r4, #104]
	mov	r0, r5
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r4, #184]
	mov	r0, r5
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r9, #48]
	mov	r2, #80
	mov	r1, r6
	mov	r0, r8
	blx	r3
	mov	r0, r7
	ldr	r3, [r9, #48]
	mov	r2, #80
	mov	r1, r6
	blx	r3
	ldr	r3, [r9, #68]
	ldr	r1, .L310+8
	mov	r0, #1
	blx	r3
	ldr	r3, .L310+12
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L290
	mov	r0, r5
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	r7
.L290:
	mov	r3, #0
	mvn	r0, #0
	strb	r3, [r4, #2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L306:
	ldr	r2, [r3, #1444]
	cmp	r2, #1
	bne	.L286
	ldrb	r2, [r1, #408]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L286
	mov	r2, #160
	add	r1, r1, #248
	add	r0, r4, #88
	bl	memcpy
	mov	r3, #0
	mov	r0, r3
	strb	r3, [r4, #408]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L307:
	ldrb	r6, [r4, #2]	@ zero_extendqisi2
	cmp	r6, r7
	beq	.L309
	cmp	r6, #1
	bne	.L291
	ldr	r1, [r3, #528]
	mov	r3, #64512
	ldr	r2, [r4, #100]
	movt	r3, 15
	cmp	r1, #6
	movne	r3, #1024
	cmp	r3, r2
	ble	.L293
	ldr	r8, .L310+4
	mov	r0, #22
	ldr	r1, .L310+16
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r2, [r4, #100]
	ldr	r0, [r4, #8]
	ldr	r3, [r8, #52]
	rsb	r0, r2, r0
	ldr	r1, [r4, #88]
	blx	r3
	ldr	r3, [r4, #100]
	ldr	ip, [r4, #20]
	mov	r0, r5
	ldr	r1, [r4, #8]
	ldr	r2, [r4, #16]
	rsb	r1, r3, r1
	strb	r6, [r4, #93]
	rsb	r2, r3, r2
	str	r1, [r4, #88]
	add	r3, r3, ip
	str	r2, [r4, #96]
	str	r3, [r4, #100]
	ldr	r1, [r4, #104]
	bl	SM_ReleaseStreamSeg
	ldr	ip, [r4, #24]
	ldr	r3, [r8, #48]
	mov	r1, r7
	mov	r2, #80
	add	r0, r4, #168
	str	ip, [r4, #104]
	blx	r3
.L294:
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
.L309:
	ldr	r5, .L310+4
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
.L293:
	ldr	r5, .L310+4
	mov	r0, #22
	ldr	r1, .L310+20
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r3, [r5, #52]
	mov	r2, #80
	add	r1, r4, #8
	add	r0, r4, #168
	blx	r3
	b	.L294
.L305:
	ldr	ip, .L310+4
	movw	r3, #1746
	ldr	r2, .L310+24
	mov	r0, #1
	ldr	r1, .L310+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L284:
	ldr	r3, .L310+4
	mov	r0, #1
	ldr	r1, .L310+32
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L311:
	.align	2
.L310:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC18
	.word	g_event_report
	.word	.LC19
	.word	.LC20
	.word	.LANCHOR0+160
	.word	.LC1
	.word	.LC17
	UNWIND(.fnend)
	.size	SegMan, .-SegMan
	.align	2
	.global	DecodeStream
	.type	DecodeStream, %function
DecodeStream:
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
	UNWIND(.pad #32)
	sub	sp, sp, #32
	cmp	r2, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r5, r2
	beq	.L384
	cmp	r1, #17
	ldrls	pc, [pc, r1, asl #2]
	b	.L312
.L316:
	.word	.L315
	.word	.L317
	.word	.L318
	.word	.L319
	.word	.L312
	.word	.L320
	.word	.L321
	.word	.L312
	.word	.L322
	.word	.L323
	.word	.L324
	.word	.L324
	.word	.L324
	.word	.L325
	.word	.L312
	.word	.L312
	.word	.L326
	.word	.L327
.L317:
	ldr	r6, .L402
	mov	r0, #22
	ldrb	r2, [r4, #13]	@ zero_extendqisi2
	ldr	r1, .L402+4
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r6, #68]
	ldr	r2, [r4, #16]
	mov	r0, #22
	ldr	r1, .L402+8
	blx	r3
	ldr	r3, [r6, #68]
	ldr	r2, [r4, #20]
	mov	r0, #22
	ldr	r1, .L402+12
	blx	r3
	ldr	r2, [r5]
	ldr	r3, [r2, #548]
	cmp	r3, #1
	bhi	.L385
	ldr	r1, [r2, #552]
	cmp	r1, #8
	bgt	.L386
	add	r7, r5, #12288
	uxtb	r3, r3
	cmp	r3, #1
	strb	r3, [r7, #3520]
	ldr	r3, [r2, #552]
	strb	r3, [r7, #3522]
	beq	.L387
	ldrb	r3, [r4, #14]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L388
	add	r7, r4, #88
	ldr	r3, [r6, #52]
	mov	r2, #80
	add	r1, r4, #8
	mov	r0, r7
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	ldr	r3, [r4, #100]
	cmp	r3, #15
	bgt	.L343
	ldr	r3, [r6, #68]
	add	r5, r5, #45056
	ldr	r1, .L402+16
.L383:
	mov	r0, #0
	blx	r3
	ldr	r1, [r4, #104]
	ldr	r0, [r5, #3776]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L402+20
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L312
	mov	r3, #0
	ldr	r0, [r5, #3776]
	mov	r2, r3
	mov	r1, #113
	blx	r4
.L312:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L384:
	ldr	ip, .L402
	movw	r3, #1162
	ldr	r2, .L402+24
	mov	r0, #1
	ldr	r1, .L402+28
	ldr	r4, [ip, #68]
	blx	r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L327:
	ldrd	r2, [r0, #32]
	sub	r1, fp, #68
	ldr	r7, [r0, #8]
	mov	r0, r5
	ldr	r6, [r4, #16]
	ldr	lr, [r4, #20]
	strd	r2, [fp, #-44]
	ldrb	ip, [r4, #13]	@ zero_extendqisi2
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	ldr	r2, [r4, #24]
	str	r7, [fp, #-64]
	strb	r3, [fp, #-67]
	str	r6, [fp, #-60]
	str	lr, [fp, #-56]
	strb	ip, [fp, #-68]
	str	r2, [fp, #-52]
	bl	HEVCDEC_DecodePacket
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r4, [r5, #2312]
	cmp	r4, #0
	bne	.L312
	ldrb	r3, [r5, #6]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L312
	ldr	r0, [r5, #244]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #6]
	b	.L312
.L315:
	ldrd	r2, [r0, #32]
	sub	r1, fp, #68
	ldr	r7, [r0, #8]
	mov	r0, r5
	ldr	r6, [r4, #16]
	ldr	lr, [r4, #20]
	strd	r2, [fp, #-44]
	ldrb	ip, [r4, #13]	@ zero_extendqisi2
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	ldr	r2, [r4, #24]
	str	r7, [fp, #-64]
	strb	r3, [fp, #-67]
	str	r6, [fp, #-60]
	str	lr, [fp, #-56]
	strb	ip, [fp, #-68]
	str	r2, [fp, #-52]
	bl	H264DEC_DecodePacket
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r4, [r5, #360]
	cmp	r4, #0
	bne	.L312
	add	r6, r5, #12288
	ldrb	r3, [r6, #1272]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L312
	add	r5, r5, #53248
	ldr	r0, [r5, #4056]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r6, #1272]
	b	.L312
.L318:
	add	r6, r2, #20480
	mov	r0, r2
	ldr	r7, [r6, #2480]
	bl	MP4_GetPacketState
	cmp	r0, #3
	beq	.L389
.L349:
	mov	r1, r4
	ldr	r0, [r6, #2480]
	bl	SegMan
	cmp	r0, #0
	beq	.L390
.L351:
	ldr	r4, [r5, #1036]
	cmp	r4, #0
	bne	.L312
	add	r5, r5, #53248
	ldrb	r3, [r5, #3560]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L312
	ldr	r0, [r6, #2480]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #3560]
	b	.L312
.L319:
	add	r6, r2, #110592
	mov	r0, r2
	ldr	r7, [r6, #4080]
	bl	MP2_GetPacketState
	cmp	r0, #2
	beq	.L391
.L345:
	mov	r1, r4
	ldr	r0, [r6, #4080]
	bl	SegMan
	cmp	r0, #0
	beq	.L392
.L347:
	ldr	r4, [r5, #4]
	cmp	r4, #0
	bne	.L312
	add	r5, r5, #114688
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L312
	ldr	r0, [r6, #4080]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #2]
	b	.L312
.L323:
	ldrb	r3, [r0, #14]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L393
	ldr	r7, .L402
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	REAL9DEC_Decode
	ldr	r8, [r5, #4]
	cmp	r8, #0
	bne	.L312
	add	r5, r5, #77824
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #24]
	ldr	r0, [r5, #2456]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L402+20
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L312
	ldr	r0, [r5, #2456]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	blx	r4
	b	.L312
.L321:
	add	r6, r2, #16384
	mov	r0, r2
	ldr	r7, [r6, #344]
	bl	AVS_GetPacketState
	cmp	r0, #0
	bne	.L352
	ldr	r3, .L402+32
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1404]
	cmp	r2, #1
	bne	.L353
	ldr	r3, [r3, #1444]
	cmp	r3, #0
	bne	.L352
.L353:
	add	r1, r5, #16384
	mov	r0, r5
	add	r1, r1, #184
	bl	AVSDEC_Decode
.L352:
	mov	r1, r4
	ldr	r0, [r6, #344]
	bl	SegMan
	cmp	r0, #0
	beq	.L394
.L354:
	ldr	r4, [r5, #4]
	cmp	r4, #0
	bne	.L312
	ldrb	r3, [r6, #860]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L312
	ldr	r0, [r6, #344]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r6, #860]
	b	.L312
.L322:
	ldrb	r3, [r0, #14]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L395
	ldr	r7, .L402
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	REAL8DEC_Decode
	ldr	r8, [r5, #4]
	cmp	r8, #0
	bne	.L312
	add	r5, r5, #77824
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #24]
	ldr	r0, [r5, #2472]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L402+20
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L312
	ldr	r0, [r5, #2472]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	blx	r4
	b	.L312
.L320:
	ldrb	r3, [r0, #14]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L396
	ldr	r7, .L402
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	DIVX3DEC_Decode
	ldr	r8, [r5, #4]
	cmp	r8, #0
	bne	.L312
	add	r5, r5, #65536
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #24]
	ldr	r0, [r5, #2432]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L402+20
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L312
	ldr	r0, [r5, #2432]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	blx	r4
	b	.L312
.L325:
	ldrb	r3, [r0, #14]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L397
	ldr	r7, .L402
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	VP8DEC_Decode
	ldr	r8, [r5, #4]
	cmp	r8, #0
	bne	.L312
	add	r5, r5, #8192
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #24]
	ldr	r0, [r5, #328]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L402+20
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L312
	ldr	r0, [r5, #328]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	blx	r4
	b	.L312
.L326:
	ldrd	r2, [r0, #32]
	sub	r1, fp, #68
	ldr	r6, [r0, #8]
	mov	r0, r5
	ldr	lr, [r4, #16]
	ldr	ip, [r4, #20]
	strd	r2, [fp, #-44]
	ldr	r3, [r4, #24]
	ldrb	r2, [r4, #13]	@ zero_extendqisi2
	str	r6, [fp, #-64]
	str	r3, [fp, #-52]
	str	lr, [fp, #-60]
	str	ip, [fp, #-56]
	strb	r2, [fp, #-68]
	bl	MVC_DEC_DecodePacket
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r4, [r5, #228]
	cmp	r4, #0
	bne	.L312
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L312
	ldr	r0, [r5, #120]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1]
	b	.L312
.L324:
	ldrb	r3, [r0, #14]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L398
	ldr	r7, .L402
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	VP6DEC_Decode
	ldr	r8, [r5, #4]
	cmp	r8, #0
	bne	.L312
	add	r5, r5, #12288
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #24]
	ldr	r0, [r5, #712]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L402+20
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L312
	ldr	r0, [r5, #712]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	blx	r4
	b	.L312
.L385:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L402+36
	blx	r3
	b	.L312
.L394:
	add	r1, r4, #88
	mov	r0, r5
	bl	AVSDEC_Decode
	b	.L354
.L390:
	add	r1, r4, #88
	mov	r0, r5
	bl	MPEG4DEC_Decode
	b	.L351
.L392:
	add	r1, r4, #88
	mov	r0, r5
	bl	MPEG2DEC_Decode
	add	r3, r5, #114688
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	b	.L347
.L391:
	ldr	r3, .L402+32
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1404]
	cmp	r2, #1
	bne	.L346
	ldr	r3, [r3, #1444]
	cmp	r3, #0
	bne	.L345
.L346:
	add	r1, r5, #79872
	mov	r0, r5
	add	r1, r1, #96
	bl	MPEG2DEC_Decode
	b	.L345
.L389:
	ldr	r3, .L402+32
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1404]
	cmp	r2, #1
	bne	.L350
	ldr	r3, [r3, #1444]
	cmp	r3, #0
	bne	.L349
.L350:
	add	r1, r5, #15680
	mov	r0, r5
	add	r1, r1, #24
	bl	MPEG4DEC_Decode
	b	.L349
.L398:
	add	r5, r2, #12288
	ldr	r0, [r5, #712]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #712]
	ldr	r1, [r4, #24]
	bl	SM_ReleaseStreamSeg
	b	.L312
.L395:
	add	r5, r2, #77824
	ldr	r0, [r5, #2472]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #2472]
	ldr	r1, [r4, #24]
	bl	SM_ReleaseStreamSeg
	b	.L312
.L393:
	add	r5, r2, #77824
	ldr	r0, [r5, #2456]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #2456]
	ldr	r1, [r4, #24]
	bl	SM_ReleaseStreamSeg
	b	.L312
.L397:
	add	r5, r2, #8192
	ldr	r0, [r5, #328]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #328]
	ldr	r1, [r4, #24]
	bl	SM_ReleaseStreamSeg
	b	.L312
.L396:
	add	r5, r2, #65536
	ldr	r0, [r5, #2432]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #2432]
	ldr	r1, [r4, #24]
	bl	SM_ReleaseStreamSeg
	b	.L312
.L343:
	add	r2, r5, #15808
	mov	r1, #16
	ldr	r0, [r4, #88]
	bl	Vc1SMPSeqHdr
	subs	r8, r0, #0
	beq	.L399
	add	r5, r5, #45056
	ldr	r3, [r6, #68]
	ldr	r1, .L402+40
	b	.L383
.L386:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L402+44
	blx	r3
	b	.L312
.L388:
	add	r5, r5, #45056
	ldr	r0, [r5, #3776]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #3776]
	ldr	r1, [r4, #24]
	bl	SM_ReleaseStreamSeg
	b	.L312
.L387:
	add	r8, r5, #45056
	mov	r0, r5
	ldr	r9, [r8, #3776]
	bl	VC1_GetPacketState
	cmp	r0, #2
	beq	.L400
.L339:
	mov	r1, r4
	ldr	r0, [r8, #3776]
	bl	SegMan
	subs	r9, r0, #0
	beq	.L401
.L341:
	ldr	r4, [r5, #4]
	cmp	r4, #0
	bne	.L312
	ldrb	r3, [r7, #431]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L312
	ldr	r0, [r8, #3776]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r7, #431]
	b	.L312
.L399:
	ldr	ip, [r4, #100]
	mov	r1, r7
	ldr	r2, [r4, #88]
	mov	r0, r5
	ldr	r3, [r4, #96]
	sub	ip, ip, #16
	add	r2, r2, #16
	str	ip, [r4, #100]
	str	r2, [r4, #88]
	add	r3, r3, #16
	str	r3, [r4, #96]
	bl	VC1DEC_Decode
	ldr	r3, [r6, #48]
	mov	r1, r8
	mov	r0, r7
	mov	r2, #160
	blx	r3
	b	.L312
.L401:
	add	r4, r4, #88
	mov	r0, r5
	mov	r1, r4
	bl	VC1DEC_Decode
	mov	r0, r4
	ldr	r3, [r6, #48]
	mov	r1, r9
	mov	r2, #160
	blx	r3
	b	.L341
.L400:
	ldr	r3, .L402+32
	ldr	r3, [r3, r9, asl #2]
	ldr	r2, [r3, #1404]
	cmp	r2, #1
	bne	.L340
	ldr	r3, [r3, #1444]
	cmp	r3, #0
	bne	.L339
.L340:
	add	r1, r5, #12544
	mov	r0, r5
	add	r1, r1, #8
	bl	VC1DEC_Decode
	b	.L339
.L403:
	.align	2
.L402:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC26
	.word	g_event_report
	.word	.LANCHOR0+168
	.word	.LC1
	.word	s_pstVfmwChan
	.word	.LC24
	.word	.LC27
	.word	.LC25
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
	beq	.L424
	sub	r3, r0, #5
	cmp	r3, #8
	ldrls	pc, [pc, r3, asl #2]
	b	.L406
.L408:
	.word	.L407
	.word	.L406
	.word	.L406
	.word	.L409
	.word	.L410
	.word	.L411
	.word	.L411
	.word	.L411
	.word	.L412
.L412:
	ldr	r5, [r1]
	add	r1, r1, #8192
	ldr	r4, .L426
	ldr	r0, [r1, #328]
	ldr	r1, [r5, #232]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r5, #221]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L417
	mov	r0, #1
	ldr	r1, .L426+4
	ldr	r3, [r4, #68]
	blx	r3
.L417:
	ldr	r3, [r4, #48]
	add	r0, r5, #216
	mov	r2, #160
	mov	r1, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L407:
	ldr	r4, [r1]
	ldrb	r3, [r4, #221]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L425
.L415:
	ldr	r3, .L426
	add	r0, r4, #216
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L409:
	ldr	r4, [r1]
	ldrb	r3, [r4, #221]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L415
	add	r3, r1, #77824
	ldr	r1, [r4, #232]
	ldr	r0, [r3, #2472]
	bl	SM_ReleaseStreamSeg
	b	.L415
.L410:
	ldr	r4, [r1]
	ldrb	r3, [r4, #221]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L415
	add	r3, r1, #77824
	ldr	r1, [r4, #232]
	ldr	r0, [r3, #2456]
	bl	SM_ReleaseStreamSeg
	b	.L415
.L411:
	ldr	r5, [r1]
	add	r1, r1, #12288
	ldr	r4, .L426
	ldr	r0, [r1, #712]
	ldr	r1, [r5, #232]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r5, #221]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L417
	ldr	r1, .L426+8
	mov	r0, #1
	ldr	r3, [r4, #68]
	blx	r3
	b	.L417
.L406:
	ldr	r3, .L426
	mov	r2, r0
	ldr	r1, .L426+12
	mov	r0, #0
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L424:
	ldr	ip, .L426
	movw	r3, #1885
	ldr	r2, .L426+16
	mov	r0, #1
	ldr	r1, .L426+20
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L425:
	add	r3, r1, #65536
	ldr	r1, [r4, #232]
	ldr	r0, [r3, #2432]
	bl	SM_ReleaseStreamSeg
	b	.L415
.L427:
	.align	2
.L426:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	.word	.LC29
	.word	.LC30
	.word	.LANCHOR0+184
	.word	.LC1
	UNWIND(.fnend)
	.size	ReleasePacket, .-ReleasePacket
	.align	2
	.global	ReleaseCurPic
	.type	ReleaseCurPic, %function
ReleaseCurPic:
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
	beq	.L455
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L430
.L432:
	.word	.L431
	.word	.L433
	.word	.L434
	.word	.L435
	.word	.L430
	.word	.L436
	.word	.L437
	.word	.L430
	.word	.L438
	.word	.L439
	.word	.L440
	.word	.L440
	.word	.L440
	.word	.L441
	.word	.L430
	.word	.L430
	.word	.L442
	.word	.L443
.L443:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HEVC_ClearCurrPic
.L431:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	H264_ClearCurrPic
.L433:
	add	r3, r4, #45056
	add	r0, r4, #12672
	add	r0, r0, #40
	ldr	r1, [r3, #3776]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VC1_ClearCurPic
.L434:
	mov	r0, r4
	bl	MP4_ClearCurPic
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MP4_Clean_HeadPacket
.L435:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MP2_ClearCurPic
.L436:
	ldr	r5, [r4]
	ldrb	r3, [r5, #221]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L456
.L446:
	ldr	r3, .L457
	add	r0, r5, #216
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L437:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVS_ClearCurPic
.L438:
	ldr	r5, [r4]
	ldrb	r3, [r5, #221]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L446
	add	r4, r4, #77824
	ldr	r1, [r5, #232]
	ldr	r0, [r4, #2472]
	bl	SM_ReleaseStreamSeg
	b	.L446
.L439:
	ldr	r5, [r4]
	ldrb	r3, [r5, #221]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L446
	add	r4, r4, #77824
	ldr	r1, [r5, #232]
	ldr	r0, [r4, #2456]
	bl	SM_ReleaseStreamSeg
	b	.L446
.L440:
	ldr	r5, [r4]
	add	r4, r4, #12288
	ldr	r0, [r4, #712]
	ldr	r1, [r5, #232]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r5, #221]	@ zero_extendqisi2
	ldr	r4, .L457
	cmp	r3, #1
	beq	.L448
	mov	r0, #1
	ldr	r1, .L457+4
	ldr	r3, [r4, #68]
	blx	r3
.L448:
	ldr	r3, [r4, #48]
	add	r0, r5, #216
	mov	r2, #160
	mov	r1, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L441:
	ldr	r5, [r4]
	add	r4, r4, #8192
	ldr	r0, [r4, #328]
	ldr	r1, [r5, #232]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r5, #221]	@ zero_extendqisi2
	ldr	r4, .L457
	cmp	r3, #1
	beq	.L448
	ldr	r1, .L457+8
	mov	r0, #1
	ldr	r3, [r4, #68]
	blx	r3
	b	.L448
.L442:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MVC_ClearCurrPic
.L430:
	ldr	r3, .L457
	mov	r2, r0
	ldr	r1, .L457+12
	mov	r0, #0
	ldr	r3, [r3, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L455:
	ldr	ip, .L457
	movw	r3, #2050
	ldr	r2, .L457+16
	mov	r0, #1
	ldr	r1, .L457+20
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L456:
	add	r4, r4, #65536
	ldr	r1, [r5, #232]
	ldr	r0, [r4, #2432]
	bl	SM_ReleaseStreamSeg
	b	.L446
.L458:
	.align	2
.L457:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC29
	.word	.LC28
	.word	.LC30
	.word	.LANCHOR0+200
	.word	.LC1
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
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r2, #0
	cmpne	r0, #0
	moveq	r3, #1
	movne	r3, #0
	beq	.L505
	cmp	r1, #2
	ldr	ip, [r2]
	movne	lr, r3
	beq	.L506
.L462:
	ldrb	r2, [ip]	@ zero_extendqisi2
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r2, #0
	ldrb	r4, [ip, #2]	@ zero_extendqisi2
	bne	.L465
	cmp	r3, #0
	beq	.L507
.L465:
	ldr	ip, .L511
	mov	r0, #22
	str	r4, [sp]
	ldr	r1, .L511+4
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r3, #0
.L502:
	mov	r0, r3
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L507:
	cmp	r4, #1
	bne	.L465
	cmp	r1, #17
	ldrls	pc, [pc, r1, asl #2]
	b	.L484
.L469:
	.word	.L468
	.word	.L470
	.word	.L471
	.word	.L472
	.word	.L484
	.word	.L484
	.word	.L473
	.word	.L484
	.word	.L484
	.word	.L484
	.word	.L484
	.word	.L484
	.word	.L484
	.word	.L484
	.word	.L484
	.word	.L484
	.word	.L474
	.word	.L475
.L506:
	ldrb	r3, [r2, #72]	@ zero_extendqisi2
	ands	lr, r3, #1
	beq	.L462
	ldrb	r1, [ip, #3]	@ zero_extendqisi2
	cmp	r1, #179
	cmpne	r1, #176
	add	r3, r1, #75
	moveq	r2, #1
	movne	r2, #0
	cmp	r1, #254
	orreq	r2, r2, #1
	uxtb	r3, r3
	cmp	r1, #47
	orrls	r2, r2, #1
	cmp	r3, #1
	movhi	r3, r2
	orrls	r3, r2, #1
	cmp	r3, #0
	beq	.L478
.L482:
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L478
.L477:
	cmp	lr, #1
	mvnne	r3, #0
	beq	.L478
.L479:
	cmp	r1, #182
	bne	.L502
.L504:
	mov	r2, #0
.L503:
	str	r2, [r0]
	b	.L502
.L478:
	mov	r2, #1
	mov	r3, #0
	str	r2, [r0]
	ldrb	r1, [ip, #3]	@ zero_extendqisi2
	b	.L479
.L475:
	mov	r1, ip
	bl	HEVC_IsNewPicNal
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r3, r0, #0
	b	.L502
.L468:
	mov	r1, ip
	bl	H264_IsNewPicNal
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r3, r0, #0
	b	.L502
.L474:
	mov	r1, ip
	bl	MVC_IsNewPicNal
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r3, r0, #0
	b	.L502
.L470:
	ldrb	r2, [ip, #3]	@ zero_extendqisi2
	sub	r3, r2, #12
	cmp	r2, #10
	cmpne	r3, #3
	bls	.L508
.L494:
	mvn	r3, #0
.L481:
	cmp	r2, #13
	bne	.L502
	b	.L504
.L471:
	ldrb	r1, [ip, #3]	@ zero_extendqisi2
	cmp	r1, #179
	cmpne	r1, #176
	add	r4, r1, #75
	moveq	r3, #1
	movne	r3, #0
	cmp	r1, #254
	orreq	r3, r3, #1
	cmp	r1, #47
	movhi	r2, r3
	orrls	r2, r3, #1
	uxtb	r3, r4
	cmp	r3, #1
	movhi	r3, r2
	orrls	r3, r2, #1
	cmp	r3, #0
	beq	.L477
	b	.L482
.L472:
	ldrb	r2, [ip, #3]	@ zero_extendqisi2
	add	r3, r2, #73
	cmp	r2, #0
	cmpne	r2, #179
	uxtb	r3, r3
	moveq	r1, #1
	movne	r1, #0
	cmp	r3, #1
	movhi	r3, r1
	orrls	r3, r1, #1
	cmp	r3, #0
	bne	.L509
.L486:
	mvn	r3, #0
.L476:
	cmp	r2, #0
	bne	.L502
	b	.L503
.L473:
	ldrb	r2, [ip, #3]	@ zero_extendqisi2
	sub	r1, r2, #179
	add	r3, r2, #74
	clz	r1, r1
	uxtb	r3, r3
	mov	r1, r1, lsr #5
	cmp	r2, #176
	movne	lr, r1
	orreq	lr, r1, #1
	cmp	r3, #1
	movhi	r3, lr
	orrls	r3, lr, #1
	cmp	r3, #0
	bne	.L510
.L491:
	mvn	r3, #0
.L480:
	cmp	r2, #182
	movne	r2, r1
	orreq	r2, r1, #1
	cmp	r2, #0
	beq	.L502
	b	.L504
.L484:
	mvn	r3, #0
	b	.L502
.L508:
	ldr	r3, [r0]
	cmp	r3, #0
	bne	.L494
	mov	r2, #1
	str	r2, [r0]
	ldrb	r2, [ip, #3]	@ zero_extendqisi2
	b	.L481
.L509:
	ldr	r3, [r0]
	cmp	r3, #0
	bne	.L486
	mov	r2, #1
	str	r2, [r0]
	ldrb	r2, [ip, #3]	@ zero_extendqisi2
	b	.L476
.L510:
	ldr	r3, [r0]
	cmp	r3, #0
	bne	.L491
	mov	r2, #1
	str	r2, [r0]
	ldrb	r2, [ip, #3]	@ zero_extendqisi2
	sub	r1, r2, #179
	clz	r1, r1
	mov	r1, r1, lsr #5
	b	.L480
.L505:
	ldr	ip, .L511
	movw	r3, #2201
	ldr	r2, .L511+8
	mov	r0, #1
	ldr	r1, .L511+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r3, #0
	b	.L502
.L512:
	.align	2
.L511:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LANCHOR0+216
	.word	.LC1
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
	cmp	r0, #15
	bhi	.L519
	ldr	r3, .L520
	add	r4, r3, r0, lsl #2
	ldr	r0, [r4, #64]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L520+4
	ldr	r3, [r3, #196]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #64]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L519:
	ldr	ip, .L520+4
	movw	r3, #2364
	ldr	r2, .L520+8
	mov	r0, #1
	ldr	r1, .L520+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L521:
	.align	2
.L520:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+228
	.word	.LC1
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
	cmp	r0, #15
	bhi	.L528
	ldr	r3, .L529
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #64]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r0, #64]
	ldmfd	sp, {fp, sp, pc}
.L528:
	ldr	ip, .L529+4
	movw	r3, #2396
	ldr	r2, .L529+8
	mov	r0, #1
	ldr	r1, .L529+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L530:
	.align	2
.L529:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+244
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L537
	ldr	r3, .L538
	add	r3, r3, r0, lsl #2
	ldr	r0, [r3, #64]
	cmp	r0, #0
	beq	.L535
	mov	ip, #0
	add	r1, r0, #205824
	mov	r3, r0
	mov	r2, ip
	str	ip, [r0]
.L534:
	str	r2, [r3, #1044]
	add	r3, r3, #1072
	str	r2, [r3, #-32]
	cmp	r3, r1
	bne	.L534
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L537:
	ldr	ip, .L538+4
	movw	r3, #2414
	ldr	r2, .L538+8
	mov	r0, #1
	ldr	r1, .L538+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L535:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L539:
	.align	2
.L538:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+268
	.word	.LC1
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
	cmp	r0, #15
	mov	r5, r0
	bhi	.L545
	ldr	r4, .L547
	add	r4, r4, r0, lsl #2
	ldr	r3, [r4, #64]
	cmp	r3, #0
	beq	.L546
.L543:
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	InitUsdPool
.L546:
	ldr	r3, .L547+4
	movw	r0, #9224
	movt	r0, 3
	ldr	r3, [r3, #192]
	blx	r3
	str	r0, [r4, #64]
	b	.L543
.L545:
	ldr	ip, .L547+4
	movw	r3, #2349
	ldr	r2, .L547+8
	mov	r0, #1
	ldr	r1, .L547+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L548:
	.align	2
.L547:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+280
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	ldrhi	ip, .L556
	movwhi	r3, #2381
	bhi	.L554
	cmp	r1, #0
	beq	.L555
	ldr	r3, .L556+4
	add	r3, r3, r0, lsl #2
	ldr	r2, [r3, #64]
	cmp	r2, #0
	streq	r1, [r3, #64]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	InitUsdPool
.L555:
	ldr	ip, .L556
	movw	r3, #2382
.L554:
	ldr	r2, .L556+8
	mov	r0, #1
	ldr	r1, .L556+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L557:
	.align	2
.L556:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LANCHOR0+292
	.word	.LC1
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
	cmp	r0, #15
	bhi	.L565
	ldr	r3, .L567
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #64]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r3, r0
	mov	r2, #0
	b	.L562
.L561:
	add	r2, r2, #1
	add	r3, r3, #1072
	cmp	r2, #192
	beq	.L566
.L562:
	ldr	r1, [r3, #1044]
	cmp	r1, #0
	bne	.L561
	ldr	r1, [r3, #1040]
	cmp	r1, #0
	bne	.L561
	mov	r3, #1072
	movw	lr, #1064
	mul	r2, r3, r2
	movw	ip, #1076
	mov	r4, #0
	mov	r5, #0
	add	r3, r0, r2
	add	r2, r2, #8
	add	r0, r0, r2
	str	r1, [r3, #1040]
	str	r1, [r3, #1056]
	str	r1, [r3, #1052]
	str	r1, [r3, #1048]
	strb	r1, [r3, #1072]
	strb	r1, [r3, #1073]
	strb	r1, [r3, #1074]
	strd	r4, [r3, lr]
	strh	r1, [r3, ip]	@ movhi
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L566:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L565:
	ldr	ip, .L567+4
	movw	r3, #2444
	ldr	r2, .L567+8
	mov	r0, #1
	ldr	r1, .L567+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L568:
	.align	2
.L567:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+312
	.word	.LC1
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
	strne	r3, [r1, #1036]
	ldmnefd	sp, {fp, sp, pc}
	ldr	ip, .L571
	movw	r3, #2475
	ldr	r2, .L571+4
	mov	r0, #1
	ldr	r1, .L571+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L572:
	.align	2
.L571:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+320
	.word	.LC1
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
	strne	r3, [r1, #1032]
	ldmnefd	sp, {fp, sp, pc}
	ldr	ip, .L575
	movw	r3, #2486
	ldr	r2, .L575+4
	mov	r0, #1
	ldr	r1, .L575+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L576:
	.align	2
.L575:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+336
	.word	.LC1
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
	strne	r3, [r1, #1032]
	ldmnefd	sp, {fp, sp, pc}
	ldr	ip, .L579
	mov	r3, #2496
	ldr	r2, .L579+4
	mov	r0, #1
	ldr	r1, .L579+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L580:
	.align	2
.L579:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+352
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	beq	.L593
	cmp	r1, #0
	beq	.L594
	ldrh	r3, [r0, #4]
	ldrh	lr, [r0, #8]
	and	r3, r3, #63
	cmp	lr, r3
	beq	.L587
.L586:
	add	r2, r0, r3, lsl #2
	add	r3, r3, #1
	and	r3, r3, #63
	ldr	r2, [r2, #12]
	cmp	r2, #0
	beq	.L585
	ldr	ip, [r2, #196]
	ldr	r2, [r1, #196]
	cmp	ip, r2
	beq	.L588
.L585:
	cmp	r3, lr
	bne	.L586
.L587:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L588:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L594:
	ldr	r3, .L595
	mov	r0, r1
	ldr	r1, .L595+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L593:
	ldr	ip, .L595
	movw	r3, #2508
	ldr	r2, .L595+8
	mov	r0, #1
	ldr	r1, .L595+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L596:
	.align	2
.L595:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LANCHOR0+368
	.word	.LC1
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
	beq	.L601
	ldrh	r0, [r4, #8]
	ldrh	r3, [r4, #6]
	cmp	r0, r3
	ldreqh	r3, [r4, #4]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L601:
	ldr	r3, .L602
	ldr	r2, .L602+4
	ldr	r1, .L602+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L603:
	.align	2
.L602:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+388
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
	beq	.L615
	cmp	r1, #5
	ldrls	pc, [pc, r1, asl #2]
	b	.L606
.L608:
	.word	.L607
	.word	.L609
	.word	.L610
	.word	.L611
	.word	.L612
	.word	.L613
.L613:
	mov	r1, #0
	mov	r2, #2
	str	r1, [r3, #60]
	str	r2, [r3, #64]
	ldmfd	sp, {fp, sp, pc}
.L607:
	mov	r1, #0
	mov	r2, #1
	str	r1, [r3, #60]
	str	r2, [r3, #64]
	ldmfd	sp, {fp, sp, pc}
.L609:
	mov	r1, #4
	mov	r2, #3
	str	r1, [r3, #60]
	str	r2, [r3, #64]
	ldmfd	sp, {fp, sp, pc}
.L610:
	mov	r1, #16
	mov	r2, #9
	str	r1, [r3, #60]
	str	r2, [r3, #64]
	ldmfd	sp, {fp, sp, pc}
.L611:
	mov	r1, #221
	mov	r2, #100
	str	r1, [r3, #60]
	str	r2, [r3, #64]
	ldmfd	sp, {fp, sp, pc}
.L612:
	mov	r1, #235
	mov	r2, #100
	str	r1, [r3, #60]
	str	r2, [r3, #64]
	ldmfd	sp, {fp, sp, pc}
.L606:
	ldr	ip, .L616
	mov	r0, #1
	mov	r2, r1
	str	r0, [r3, #64]
	mov	lr, #0
	ldr	r1, .L616+4
	str	lr, [r3, #60]
	ldr	r3, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L615:
	ldr	ip, .L616
	movw	r3, #2556
	ldr	r2, .L616+8
	mov	r0, #1
	ldr	r1, .L616+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L617:
	.align	2
.L616:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC33
	.word	.LANCHOR0+404
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #0
	beq	.L622
	ldr	r0, [r0, #296]
	cmp	r0, #1
	mvnls	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L622:
	ldr	ip, .L623
	movw	r3, #2604
	ldr	r2, .L623+4
	mov	r0, #1
	ldr	r1, .L623+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L624:
	.align	2
.L623:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+420
	.word	.LC1
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
	beq	.L633
	add	r3, r4, #69632
	ldr	r2, [r3, #2824]
	cmp	r2, #1
	beq	.L630
	ldr	r1, [r3, #2828]
	cmp	r1, #1
	beq	.L630
	cmp	r2, #2
	moveq	r2, #1
	ldrne	r0, [r3, #2832]
	subne	r2, r0, #1
	clzne	r2, r2
	movne	r2, r2, lsr #5
.L628:
	ldr	r0, [r3, #2832]
	cmp	r0, #1
	movne	r0, r2
	orreq	r0, r2, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L630:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L633:
	ldr	ip, .L634
	movw	r3, #2622
	ldr	r2, .L634+4
	mov	r0, #1
	ldr	r1, .L634+8
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L635:
	.align	2
.L634:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+440
	.word	.LC1
	UNWIND(.fnend)
	.size	IsMain10Profile, .-IsMain10Profile
	.global	pstVdecUsdPool
	.global	g_DnrEnable
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13788, %object
	.size	__func__.13788, 12
__func__.13788:
	.ascii	"InitVoQueue\000"
	.type	__func__.13793, %object
	.size	__func__.13793, 13
__func__.13793:
	.ascii	"PrintVoQueue\000"
	.space	3
	.type	__func__.13799, %object
	.size	__func__.13799, 13
__func__.13799:
	.ascii	"ResetVoQueue\000"
	.space	3
	.type	__func__.13848, %object
	.size	__func__.13848, 19
__func__.13848:
	.ascii	"InsertImgToVoQueue\000"
	.space	1
	.type	__FUNCTION__.13855, %object
	.size	__FUNCTION__.13855, 19
__FUNCTION__.13855:
	.ascii	"InsertImgToVoQueue\000"
	.space	1
	.type	__func__.13863, %object
	.size	__func__.13863, 15
__func__.13863:
	.ascii	"GetQueueImgNum\000"
	.space	1
	.type	__func__.13870, %object
	.size	__func__.13870, 20
__func__.13870:
	.ascii	"SYNTAX_ReceiveImage\000"
	.type	__func__.13897, %object
	.size	__func__.13897, 20
__func__.13897:
	.ascii	"SYNTAX_ReleaseImage\000"
	.type	__func__.13940, %object
	.size	__func__.13940, 19
__func__.13940:
	.ascii	"SYNTAX_ReturnImage\000"
	.space	1
	.type	__func__.13992, %object
	.size	__func__.13992, 7
__func__.13992:
	.ascii	"SegMan\000"
	.space	1
	.type	__func__.13969, %object
	.size	__func__.13969, 13
__func__.13969:
	.ascii	"DecodeStream\000"
	.space	3
	.type	__func__.13998, %object
	.size	__func__.13998, 14
__func__.13998:
	.ascii	"ReleasePacket\000"
	.space	2
	.type	__func__.14013, %object
	.size	__func__.14013, 14
__func__.14013:
	.ascii	"ReleaseCurPic\000"
	.space	2
	.type	__func__.14038, %object
	.size	__func__.14038, 12
__func__.14038:
	.ascii	"IsNewpicSeg\000"
	.type	__func__.14057, %object
	.size	__func__.14057, 13
__func__.14057:
	.ascii	"CloseUsdPool\000"
	.space	3
	.type	__func__.14067, %object
	.size	__func__.14067, 21
__func__.14067:
	.ascii	"CloseUsdPool_WithMem\000"
	.space	3
	.type	__func__.14073, %object
	.size	__func__.14073, 12
__func__.14073:
	.ascii	"InitUsdPool\000"
	.type	__func__.14053, %object
	.size	__func__.14053, 12
__func__.14053:
	.ascii	"OpenUsdPool\000"
	.type	__func__.14063, %object
	.size	__func__.14063, 20
__func__.14063:
	.ascii	"OpenUsdPool_WithMem\000"
	.type	__func__.14083, %object
	.size	__func__.14083, 7
__func__.14083:
	.ascii	"GetUsd\000"
	.space	1
	.type	__func__.14091, %object
	.size	__func__.14091, 13
__func__.14091:
	.ascii	"FreeUsdByDec\000"
	.space	3
	.type	__func__.14096, %object
	.size	__func__.14096, 13
__func__.14096:
	.ascii	"MarkUsdByDnr\000"
	.space	3
	.type	__func__.14101, %object
	.size	__func__.14101, 15
__func__.14101:
	.ascii	"UnMarkUsdByDnr\000"
	.space	1
	.type	__func__.14107, %object
	.size	__func__.14107, 17
__func__.14107:
	.ascii	"IsImageInVoQueue\000"
	.space	3
	.type	__func__.14113, %object
	.size	__func__.14113, 15
__func__.14113:
	.ascii	"IsVoQueueEmpty\000"
	.space	1
	.type	__func__.14118, %object
	.size	__func__.14118, 15
__func__.14118:
	.ascii	"SetAspectRatio\000"
	.space	1
	.type	__func__.14131, %object
	.size	__func__.14131, 17
__func__.14131:
	.ascii	"GetVoLastImageID\000"
	.space	3
	.type	__func__.14136, %object
	.size	__func__.14136, 16
__func__.14136:
	.ascii	"IsMain10Profile\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"Initializing VO queue\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"[%s %d]assert warning\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"VoQueue state: head(%d) history(%d) tail(%d)\000" )
	.space	3
.LC3:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"%d \000" )
.LC5:
	ASCII(.ascii	"ResetVoQueue but queue not empty: head(%d) history(" )
	ASCII(.ascii	"%d) tail(%d)\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"image point NULL\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"call InsertVOQueue\012\000" )
.LC8:
	ASCII(.ascii	"FATAL: p_image(id=%d) has already in the VoQueue!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC9:
	ASCII(.ascii	"error=%d,W=%d,H=%d,not acceptable!\012\000" )
.LC10:
	ASCII(.ascii	"out_pts: %lld -> %lld Usertag %lld\012\000" )
.LC11:
	ASCII(.ascii	"Queue=(%02d,%02d,%02d) + F%d\012\000" )
	.space	2
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
	ASCII(.ascii	"pSegMan error!\012\000" )
.LC18:
	ASCII(.ascii	"More than two packet!!!ERROR!!!\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"*****************copy packets tobe one*************" )
	ASCII(.ascii	"****\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"*****************two packet*****************\012\000" )
	.space	2
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
	ASCII(.ascii	"LENTH ERROR: VC1 S/MP BS is wrong!\012\000" )
.LC27:
	ASCII(.ascii	"SYNTAX ERROR: VC1 S/MP BS is wrong!\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"ERROR: VFMW_VP8 one packet stream, but IsLastSeg ==" )
	ASCII(.ascii	" 0\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"ERROR: VFMW_VP6 one packet stream, but IsLastSeg ==" )
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
	.type	last_rec_pos_time.13845, %object
	.size	last_rec_pos_time.13845, 64
last_rec_pos_time.13845:
	.space	64
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 64
pstVdecUsdPool:
	.space	64
	.type	g_DnrEnable, %object
	.size	g_DnrEnable, 4
g_DnrEnable:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
