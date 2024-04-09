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
	.file	"h264.c"
	.text
	.align	2
	.global	IsSTRefFlg
	.type	IsSTRefFlg, %function
IsSTRefFlg:
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
	ldr	r0, [r0]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #65536
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsSTRefFlg, .-IsSTRefFlg
	.align	2
	.global	IsLTRefFlg
	.type	IsLTRefFlg, %function
IsLTRefFlg:
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
	ldr	r0, [r0]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #256
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsLTRefFlg, .-IsLTRefFlg
	.align	2
	.global	compare_pic_by_pic_num_desc
	.type	compare_pic_by_pic_num_desc, %function
compare_pic_by_pic_num_desc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #8]
	ldr	r3, [r3, #8]
	cmp	r2, r3
	blt	.L5
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L5:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_pic_num_desc, .-compare_pic_by_pic_num_desc
	.align	2
	.global	compare_pic_by_lt_pic_num_asc
	.type	compare_pic_by_lt_pic_num_asc, %function
compare_pic_by_lt_pic_num_asc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #4]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	blt	.L9
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L9:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_lt_pic_num_asc, .-compare_pic_by_lt_pic_num_asc
	.align	2
	.global	compare_fs_by_frame_num_desc
	.type	compare_fs_by_frame_num_desc, %function
compare_fs_by_frame_num_desc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #664]
	ldr	r3, [r3, #664]
	cmp	r2, r3
	blt	.L12
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L12:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_fs_by_frame_num_desc, .-compare_fs_by_frame_num_desc
	.align	2
	.global	compare_fs_by_lt_pic_idx_asc
	.type	compare_fs_by_lt_pic_idx_asc, %function
compare_fs_by_lt_pic_idx_asc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #668]
	ldr	r3, [r3, #668]
	cmp	r2, r3
	bcc	.L15
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L15:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_fs_by_lt_pic_idx_asc, .-compare_fs_by_lt_pic_idx_asc
	.align	2
	.global	compare_pic_by_poc_asc
	.type	compare_pic_by_poc_asc, %function
compare_pic_by_poc_asc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #12]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	blt	.L18
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L18:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_poc_asc, .-compare_pic_by_poc_asc
	.align	2
	.global	compare_pic_by_poc_desc
	.type	compare_pic_by_poc_desc, %function
compare_pic_by_poc_desc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #12]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	blt	.L21
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L21:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_poc_desc, .-compare_pic_by_poc_desc
	.align	2
	.global	compare_fs_by_poc_asc
	.type	compare_fs_by_poc_asc, %function
compare_fs_by_poc_asc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #672]
	ldr	r3, [r3, #672]
	cmp	r2, r3
	blt	.L24
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L24:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_fs_by_poc_asc, .-compare_fs_by_poc_asc
	.align	2
	.global	compare_fs_by_poc_desc
	.type	compare_fs_by_poc_desc, %function
compare_fs_by_poc_desc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #672]
	ldr	r3, [r3, #672]
	cmp	r2, r3
	blt	.L27
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_fs_by_poc_desc, .-compare_fs_by_poc_desc
	.align	2
	.type	SetFrmRepeatCount.part.7, %function
SetFrmRepeatCount.part.7:
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
	add	ip, r0, #61440
	add	r0, r0, #24576
	ldr	lr, [ip, #2700]
	ldr	r2, [r0, #2136]
	ldr	r3, [ip, #2696]
	add	r2, r2, lr, lsr #1
	add	r0, r2, #1
	mov	r3, r3, lsr #1
	cmp	r3, r0
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	r3, r3, #1
	rsb	r3, r2, r3
	cmp	r3, #1
	movhi	r3, #2
	movls	r3, #1
	strhi	r3, [r1, #16]
	strls	r3, [r1, #16]
	ldrhi	r3, [ip, #2700]
	ldrls	r3, [ip, #2700]
	addhi	r3, r3, #4
	addls	r3, r3, #2
	str	r3, [ip, #2700]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SetFrmRepeatCount.part.7, .-SetFrmRepeatCount.part.7
	.align	2
	.type	DumpList.part.10, %function
DumpList.part.10:
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
	add	r9, r0, #26880
	add	r9, r9, #240
	add	r7, r0, #20480
	add	r7, r7, #244
	mov	r8, r0
	mov	r6, #0
	mov	r10, r9
.L33:
	ldr	r3, [r7, #4]!
	cmp	r3, #0
	movne	r5, r10
	movne	r4, #0
	beq	.L36
.L34:
	ldr	ip, [r5, #4]!
	mov	r3, r4
	mov	r2, r6
	ldr	r1, .L64
	mov	r0, #13
	add	r4, r4, #1
	ldr	ip, [ip, #36]
	ldr	lr, [ip, #672]
	str	lr, [sp, #4]
	ldr	ip, [ip, #660]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r7]
	cmp	r4, r3
	bcc	.L34
.L36:
	add	r6, r6, #1
	add	r10, r10, #132
	cmp	r6, #2
	bne	.L33
	add	r5, r8, #20480
	ldr	r3, [r5, #248]
	cmp	r3, #0
	bne	.L60
.L37:
	ldr	r3, [r5, #252]
	cmp	r3, #0
	bne	.L61
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L61:
	ldr	r1, .L64+4
	mov	r0, #13
	bl	dprint_vfmw
	ldr	r3, [r5, #252]
	cmp	r3, #0
	addne	r8, r8, #27136
	movne	r4, #0
	addne	r8, r8, #116
	bne	.L50
	b	.L51
.L62:
	bcc	.L48
	cmp	r2, #2
	ldr	r1, .L64+8
	mov	r0, #13
	bne	.L46
	ldr	r3, [r3, #36]
	ldr	r2, [r3, #672]
	bl	dprint_vfmw
.L46:
	ldr	r3, [r5, #252]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L51
.L50:
	ldr	r3, [r8, #4]!
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L62
	ldr	r3, [r3, #36]
	mov	r0, #13
	ldr	r1, .L64+12
	add	r4, r4, #1
	ldr	r2, [r3, #672]
	bl	dprint_vfmw
	ldr	r3, [r5, #252]
	cmp	r4, r3
	bcc	.L50
.L51:
	ldr	r1, .L64+16
	mov	r0, #13
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L48:
	ldr	r3, [r3, #36]
	mov	r0, #13
	ldr	r1, .L64+20
	ldr	r2, [r3, #672]
	bl	dprint_vfmw
	b	.L46
.L60:
	ldr	r1, .L64+24
	mov	r0, #13
	bl	dprint_vfmw
	ldr	r3, [r5, #248]
	cmp	r3, #0
	movne	r4, #0
	bne	.L38
	b	.L43
.L63:
	bcc	.L41
	cmp	r2, #2
	ldr	r1, .L64+8
	mov	r0, #13
	bne	.L39
	ldr	r3, [r3, #36]
	ldr	r2, [r3, #796]
	bl	dprint_vfmw
.L39:
	ldr	r3, [r5, #248]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L43
.L38:
	ldr	r3, [r9, #4]!
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L63
	ldr	r3, [r3, #36]
	mov	r0, #13
	ldr	r1, .L64+12
	add	r4, r4, #1
	ldr	r2, [r3, #756]
	bl	dprint_vfmw
	ldr	r3, [r5, #248]
	cmp	r4, r3
	bcc	.L38
.L43:
	ldr	r1, .L64+16
	mov	r0, #13
	bl	dprint_vfmw
	b	.L37
.L41:
	ldr	r3, [r3, #36]
	mov	r0, #13
	ldr	r1, .L64+20
	ldr	r2, [r3, #672]
	bl	dprint_vfmw
	b	.L39
.L65:
	.align	2
.L64:
	.word	.LC0
	.word	.LC6
	.word	.LC5
	.word	.LC4
	.word	.LC2
	.word	.LC3
	.word	.LC1
	UNWIND(.fnend)
	.size	DumpList.part.10, .-DumpList.part.10
	.align	2
	.global	ue_v
	.type	ue_v, %function
ue_v:
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
	add	r7, r0, #13504
	mov	r8, r0
	add	r7, r7, #24
	mov	r6, r1
	mov	r1, #32
	mov	r0, r7
	bl	BsShow
	mov	r5, r0
	bl	ZerosMS_32
	cmp	r0, #15
	mov	r4, r0
	bls	.L70
	cmp	r0, #31
	bls	.L71
	add	r3, r8, #61440
	mvn	r5, #0
	mov	r7, #32
	mov	r2, #1
	str	r2, [r3, #2620]
.L68:
	ldr	ip, [r8, #368]
	mov	r2, r6
	mov	r3, r5
	ldr	r1, .L72
	mov	r0, #21
	ldr	r4, [ip, #64]
	add	r4, r4, r7
	str	r4, [ip, #64]
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L70:
	mov	r4, r0, asl #1
	mov	r0, r7
	add	r7, r4, #1
	rsb	r4, r4, #31
	mov	r4, r5, lsr r4
	mov	r1, r7
	sub	r5, r4, #1
	bl	BsSkip
	b	.L68
.L71:
	add	r5, r0, #1
	mov	r1, r0
	mov	r0, r7
	bl	BsSkip
	mov	r1, r5
	mov	r0, r7
	bl	BsShow
	mov	r1, r5
	sub	r5, r0, #1
	mov	r0, r7
	bl	BsSkip
	mov	r3, r4, asl #1
	add	r7, r3, #1
	b	.L68
.L73:
	.align	2
.L72:
	.word	.LC7
	UNWIND(.fnend)
	.size	ue_v, .-ue_v
	.align	2
	.global	se_v
	.type	se_v, %function
se_v:
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
	add	r6, r0, #13504
	mov	r8, r0
	add	r6, r6, #24
	mov	r7, r1
	mov	r1, #32
	mov	r0, r6
	bl	BsShow
	mov	r4, r0
	bl	ZerosMS_32
	cmp	r0, #15
	mov	r5, r0
	bhi	.L75
	mov	r5, r0, asl #1
	mov	r0, r6
	rsb	r3, r5, #31
	add	r5, r5, #1
	mov	r3, r4, lsr r3
	and	r2, r3, #1
	mov	r1, r5
	rsb	r4, r2, #0
	eor	r4, r4, r3, lsr #1
	add	r4, r4, r2
	bl	BsSkip
.L76:
	ldr	lr, [r8, #368]
	mov	r2, r7
	mov	r3, r4
	ldr	r1, .L79
	mov	r0, #21
	ldr	ip, [lr, #64]
	add	r5, ip, r5
	str	r5, [lr, #64]
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L75:
	cmp	r0, #31
	bls	.L78
	add	r3, r8, #61440
	mov	r2, #1
	mvn	r4, #-2147483648
	mov	r5, #32
	str	r2, [r3, #2620]
	b	.L76
.L78:
	mov	r1, r0
	mov	r0, r6
	bl	BsSkip
	mov	r1, r5
	mov	r0, r6
	mov	r5, r5, asl #1
	bl	BsGet
	mov	r1, #1
	add	r5, r5, #1
	mov	r9, r0
	mov	r0, r6
	bl	BsGet
	and	r0, r0, #1
	rsb	r4, r0, #0
	eor	r9, r9, r4
	add	r4, r9, r0
	b	.L76
.L80:
	.align	2
.L79:
	.word	.LC7
	UNWIND(.fnend)
	.size	se_v, .-se_v
	.align	2
	.global	u_v
	.type	u_v, %function
u_v:
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
	add	r0, r0, #13504
	add	r0, r0, #24
	mov	r6, r1
	mov	r7, r2
	bl	BsGet
	ldr	lr, [r5, #368]
	mov	r2, r7
	ldr	r1, .L82
	ldr	ip, [lr, #64]
	add	ip, ip, r6
	str	ip, [lr, #64]
	mov	r4, r0
	mov	r0, #21
	mov	r3, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L83:
	.align	2
.L82:
	.word	.LC7
	UNWIND(.fnend)
	.size	u_v, .-u_v
	.align	2
	.global	u_1
	.type	u_1, %function
u_1:
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
	add	r0, r0, #13504
	mov	r6, r1
	add	r0, r0, #24
	mov	r1, #1
	bl	BsGet
	ldr	lr, [r5, #368]
	mov	r2, r6
	ldr	r1, .L85
	ldr	ip, [lr, #64]
	add	ip, ip, #1
	str	ip, [lr, #64]
	mov	r4, r0
	mov	r3, r0
	mov	r0, #21
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L86:
	.align	2
.L85:
	.word	.LC7
	UNWIND(.fnend)
	.size	u_1, .-u_1
	.align	2
	.global	FrameStoreRefFlg
	.type	FrameStoreRefFlg, %function
FrameStoreRefFlg:
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
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	FrameStoreRefFlg, .-FrameStoreRefFlg
	.align	2
	.global	ReleaseNAL
	.type	ReleaseNAL, %function
ReleaseNAL:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L96
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	strb	r3, [r5, #1]
	strb	r3, [r5, #4]
.L91:
	ldr	r3, [r4, #8]
	mov	r0, r6
	cmp	r3, #0
	beq	.L90
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #8]
	mov	r0, #7
	ldr	r1, .L97
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #8]
	str	r3, [r4, #24]
	str	r3, [r4, #12]
.L90:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L91
	mov	r3, #0
	strb	r3, [r5]
	str	r3, [r5, #68]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L96:
	mov	r0, r5
	movw	r3, #422
	ldr	r2, .L97+4
	ldr	r1, .L97+8
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L98:
	.align	2
.L97:
	.word	.LC10
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	ReleaseNAL, .-ReleaseNAL
	.align	2
	.global	GetMinPOC
	.type	GetMinPOC, %function
GetMinPOC:
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
	add	r5, r0, #24576
	mov	ip, #0
	mvn	r3, #-2147483648
	str	ip, [r2]
	str	r3, [r1]
	ldr	r3, [r5, #2140]
	ldr	ip, [r5, #2136]
	cmp	r3, ip
	strhi	ip, [r5, #2140]
	movhi	r3, ip
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #26368
	mov	r3, #0
	add	r0, r0, #148
.L103:
	ldr	ip, [r0, #4]!
	ldr	r4, [r1]
	ldr	lr, [ip, #672]
	cmp	r4, lr
	ble	.L102
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	strne	lr, [r1]
	strne	r3, [r2]
.L102:
	ldr	ip, [r5, #2140]
	add	r3, r3, #1
	cmp	ip, r3
	bhi	.L103
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetMinPOC, .-GetMinPOC
	.align	2
	.global	RemoveFrameStoreOutDPB
	.type	RemoveFrameStoreOutDPB, %function
RemoveFrameStoreOutDPB:
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
	add	r7, r0, r1, lsl #2
	mov	r4, r1
	add	r7, r7, #24576
	mov	r5, r0
	ldr	r2, [r7, #1944]
	cmp	r2, #0
	beq	.L129
	ldr	r3, [r2, #696]
	add	r6, r0, #24576
	mov	r1, #0
	add	r8, r0, #61440
	add	r3, r3, #6656
	add	r3, r3, #26
	add	r3, r0, r3, lsl #2
	str	r1, [r3, #4]
	ldr	r3, [r6, #2416]
	cmp	r3, r1
	subne	r3, r3, #1
	str	r3, [r6, #2416]
	ldr	r1, [r2, #656]
	ldr	r0, [r8, #2680]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L112
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L113
	ldr	r3, [r7, #1944]
	mov	r2, #0
	ldr	r0, [r8, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetDisplay
.L113:
	ldr	r3, [r7, #1944]
	mov	r2, #0
	ldr	r0, [r8, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetRef
.L112:
	ldr	r1, [r7, #1944]
	mov	r3, #0
	mvn	r2, #0
	strb	r3, [r1, #1]
	ldr	r1, [r7, #1944]
	strb	r3, [r1, #4]
	ldr	r1, [r7, #1944]
	strb	r3, [r1, #2]
	ldr	r3, [r7, #1944]
	str	r2, [r3, #656]
	ldr	r1, [r6, #2140]
	add	r1, r1, r2
	cmp	r4, r1
	addcc	r2, r4, #6592
	addcc	r2, r2, #38
	addcc	r2, r5, r2, lsl #2
	bcs	.L117
.L116:
	add	r4, r4, #1
	ldr	r3, [r2, #4]!
	cmp	r4, r1
	str	r3, [r2, #-4]
	bne	.L116
.L117:
	add	r3, r1, #6592
	mov	r2, #0
	add	r3, r3, #38
	str	r2, [r5, r3, asl #2]
	str	r1, [r6, #2140]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L129:
	mov	r3, r1
	ldr	r2, .L130
	ldr	r1, .L130+4
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L131:
	.align	2
.L130:
	.word	.LANCHOR0
	.word	.LC11
	UNWIND(.fnend)
	.size	RemoveFrameStoreOutDPB, .-RemoveFrameStoreOutDPB
	.align	2
	.global	RemoveUnUsedFrameStore
	.type	RemoveUnUsedFrameStore, %function
RemoveUnUsedFrameStore:
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
	subs	r6, r0, #0
	beq	.L142
	add	r3, r6, #24576
	ldr	r7, [r3, #2140]
	cmp	r7, #0
	addne	r8, r6, #61440
	movne	r5, #0
	movne	r9, r5
	movne	r10, r5
	bne	.L140
	b	.L141
.L151:
	ldrb	r1, [r2, #4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L138
	ldr	r0, [r2, #824]
	cmp	r0, #1
	beq	.L138
	strb	r1, [r2, #1]
	mov	r0, r6
	mov	r1, r5
	add	r9, r9, #1
	bl	RemoveFrameStoreOutDPB
	cmp	r9, r7
	beq	.L141
.L140:
	add	r4, r6, r5, lsl #2
	ldr	r0, [r8, #2680]
	add	r4, r4, #24576
	ldr	r2, [r4, #1944]
	ldr	r1, [r2, #656]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L135
	ldrsh	r2, [r0]
	cmp	r2, #0
	bne	.L136
	ldr	r1, [r4, #1944]
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L137
	ldrsb	r0, [r0]
	cmp	r0, #0
	bne	.L150
.L137:
	mvn	r3, #0
	str	r3, [r1, #656]
	ldr	r2, [r4, #1944]
	strb	r10, [r2, #2]
.L135:
	ldr	r1, [r4, #1944]
	ldr	r2, [r1, #824]
	sub	r2, r2, #1
	clz	r2, r2
	mov	r2, r2, lsr #5
	strb	r2, [r1, #4]
.L136:
	ldr	r2, [r4, #1944]
	ldrb	r1, [r2, #2]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L151
.L138:
	add	r9, r9, #1
	add	r5, r5, #1
	cmp	r9, r7
	bne	.L140
.L141:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L150:
	ldr	r1, [r1, #656]
	ldr	r0, [r8, #2680]
	bl	FSP_SetRef
	ldr	r1, [r4, #1944]
	b	.L137
.L142:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	RemoveUnUsedFrameStore, .-RemoveUnUsedFrameStore
	.align	2
	.global	UnMarkFrameStoreRef
	.type	UnMarkFrameStoreRef, %function
UnMarkFrameStoreRef:
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
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L153
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r1, #745]
	and	r2, r2, #2
	strb	ip, [r1, #746]
	strb	r2, [r1, #2]
.L153:
	tst	r3, #2
	beq	.L154
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r1, #785]
	and	r2, r2, #1
	strb	ip, [r1, #786]
	strb	r2, [r1, #2]
.L154:
	cmp	r3, #3
	add	r0, r0, #61440
	moveq	r3, #0
	streqb	r3, [r1, #706]
	streqb	r3, [r1, #705]
	mov	r3, #0
	mov	r2, r3
	strb	r3, [r1, #2]
	ldr	r1, [r1, #656]
	ldr	r0, [r0, #2680]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetRef
	UNWIND(.fnend)
	.size	UnMarkFrameStoreRef, .-UnMarkFrameStoreRef
	.align	2
	.global	InitOldSlice
	.type	InitOldSlice, %function
InitOldSlice:
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
	add	r2, r0, #12288
	add	r0, r0, #20480
	movw	r3, #23352
	ldr	r1, [r2, #1292]
	movt	r3, 1
	mov	r2, #2
	str	r3, [r0, #1864]
	strb	r2, [r0, #1849]
	mov	r3, #32
	mov	r2, #7
	strb	r3, [r0, #1850]
	str	r2, [r0, #1860]
	mvn	r3, #0
	mov	r2, #3
	str	r3, [r0, #1876]
	str	r2, [r0, #1872]
	mov	r3, #0
	mov	r2, #262144
	str	r1, [r0, #1856]
	str	r2, [r0, #1888]
	strb	r3, [r0, #1848]
	str	r3, [r0, #1880]
	str	r3, [r0, #1884]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	InitOldSlice, .-InitOldSlice
	.align	2
	.global	ClearAllSlice
	.type	ClearAllSlice, %function
ClearAllSlice:
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
	add	r4, r0, #61952
	add	r5, r0, #62720
	add	r4, r4, #236
	add	r5, r5, #12
	add	r6, r0, #61440
	mov	r7, #0
.L165:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L164
	ldr	r0, [r6, #2680]
	bl	ReleaseNAL
	str	r7, [r4]
.L164:
	cmp	r4, r5
	bne	.L165
	mov	r0, #0
	str	r0, [r6, #2604]
	str	r0, [r6, #2664]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ClearAllSlice, .-ClearAllSlice
	.align	2
	.global	H264_IsEosNal
	.type	H264_IsEosNal, %function
H264_IsEosNal:
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
	add	r4, r0, #13504
	mov	r1, #32
	add	r4, r4, #24
	mov	r0, r4
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r4
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r5, r3
	moveq	r0, #1
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	H264_IsEosNal, .-H264_IsEosNal
	.align	2
	.global	ClearCurrNal
	.type	ClearCurrNal, %function
ClearCurrNal:
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
	ldr	r1, [r0, #368]
	mov	r4, r0
	cmp	r1, #0
	beq	.L172
	add	r3, r0, #61440
	ldr	r0, [r3, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #368]
.L172:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	ClearCurrNal, .-ClearCurrNal
	.align	2
	.global	ClearAllNal
	.type	ClearAllNal, %function
ClearAllNal:
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
	add	r5, r0, #13504
	add	r4, r0, #376
	add	r5, r5, #24
	add	r6, r0, #61440
	b	.L178
.L177:
	add	r4, r4, #96
	cmp	r4, r5
	beq	.L180
.L178:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L177
	mov	r1, r4
	ldr	r0, [r6, #2680]
	add	r4, r4, #96
	bl	ReleaseNAL
	cmp	r4, r5
	bne	.L178
.L180:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ClearAllNal, .-ClearAllNal
	.align	2
	.global	ClearCurrSlice
	.type	ClearCurrSlice, %function
ClearCurrSlice:
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
	ldr	r1, .L186
	mov	r5, r0
	mov	r0, #1
	add	r4, r5, #61440
	bl	dprint_vfmw
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L182
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r5, #368]
.L182:
	ldr	r3, [r4, #2636]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #2636]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L187:
	.align	2
.L186:
	.word	.LC12
	UNWIND(.fnend)
	.size	ClearCurrSlice, .-ClearCurrSlice
	.align	2
	.global	H264_ClearCurrPic
	.type	H264_ClearCurrPic, %function
H264_ClearCurrPic:
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
	beq	.L191
	bl	ClearAllSlice
	add	r1, r4, #12288
	add	r3, r4, #20480
	mov	r2, #0
	ldr	lr, [r1, #1292]
	movw	r1, #23352
	movt	r1, 1
	mov	ip, #2
	str	r1, [r3, #1864]
	mov	r0, r2
	mov	r1, #7
	strb	ip, [r3, #1849]
	str	r1, [r3, #1860]
	mov	ip, #32
	mov	r1, #3
	strb	ip, [r3, #1850]
	str	r1, [r3, #1872]
	mvn	ip, #0
	mov	r1, #262144
	str	lr, [r3, #1856]
	str	ip, [r3, #1876]
	str	r1, [r3, #1888]
	strb	r2, [r3, #1848]
	str	r2, [r3, #1880]
	str	r2, [r3, #1884]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L191:
	movw	r3, #737
	ldr	r2, .L192
	ldr	r1, .L192+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L193:
	.align	2
.L192:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264_ClearCurrPic, .-H264_ClearCurrPic
	.align	2
	.global	GetMinPOCInDPB
	.type	GetMinPOCInDPB, %function
GetMinPOCInDPB:
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
	add	r4, r0, #24576
	mov	ip, #0
	mvn	r3, #-2147483648
	str	ip, [r2]
	str	r3, [r1]
	ldr	r3, [r4, #2140]
	ldr	ip, [r4, #2136]
	cmp	r3, ip
	strhi	ip, [r4, #2140]
	movhi	r3, ip
	cmp	r3, #0
	ldmeqfd	sp, {r4, fp, sp, pc}
	add	r0, r0, #26368
	mov	r3, #0
	add	r0, r0, #148
.L198:
	ldr	ip, [r0, #4]!
	ldr	lr, [r1]
	ldr	ip, [ip, #672]
	cmp	lr, ip
	strgt	ip, [r1]
	strgt	r3, [r2]
	add	r3, r3, #1
	ldr	ip, [r4, #2140]
	cmp	ip, r3
	bhi	.L198
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetMinPOCInDPB, .-GetMinPOCInDPB
	.align	2
	.global	GetMaxPOC
	.type	GetMaxPOC, %function
GetMaxPOC:
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
	add	r5, r0, #24576
	mov	r3, #0
	str	r3, [r2]
	str	r3, [r1]
	ldr	r3, [r5, #2140]
	ldr	ip, [r5, #2136]
	cmp	r3, ip
	strhi	ip, [r5, #2140]
	movhi	r3, ip
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #26368
	mov	r3, #0
	add	r0, r0, #148
.L205:
	ldr	ip, [r0, #4]!
	ldr	r4, [r1]
	ldr	lr, [ip, #672]
	cmp	r4, lr
	bge	.L204
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	strne	lr, [r1]
	strne	r3, [r2]
.L204:
	ldr	ip, [r5, #2140]
	add	r3, r3, #1
	cmp	ip, r3
	bhi	.L205
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetMaxPOC, .-GetMaxPOC
	.align	2
	.global	ShortTermRefFlg
	.type	ShortTermRefFlg, %function
ShortTermRefFlg:
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
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L226
	tst	r3, #1
	bne	.L227
.L215:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L219
.L216:
	ldr	r0, [r0, #784]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #65536
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L219:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L227:
	ldr	r2, [r0, #744]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #65536
	bne	.L215
.L220:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L226:
	ldr	r3, [r0, #704]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L220
	ldr	r3, [r0, #744]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	bne	.L216
	b	.L220
	UNWIND(.fnend)
	.size	ShortTermRefFlg, .-ShortTermRefFlg
	.align	2
	.global	LongTermRefFlg
	.type	LongTermRefFlg, %function
LongTermRefFlg:
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
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L243
	tst	r3, #1
	bne	.L244
.L232:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L236
.L233:
	ldr	r0, [r0, #784]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #256
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L236:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L244:
	ldr	r2, [r0, #744]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #256
	bne	.L232
.L237:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L243:
	ldr	r3, [r0, #704]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L237
	ldr	r3, [r0, #744]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	bne	.L233
	b	.L237
	UNWIND(.fnend)
	.size	LongTermRefFlg, .-LongTermRefFlg
	.align	2
	.global	UpdateLTReflist
	.type	UpdateLTReflist, %function
UpdateLTReflist:
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
	add	r9, r0, #24576
	mov	r6, r0
	ldr	r8, [r9, #2140]
	cmp	r8, #0
	beq	.L252
	add	r10, r0, #26368
	mov	r4, #0
	add	r10, r10, #148
	mov	r5, r4
.L248:
	ldr	r7, [r10, #4]!
	add	r5, r5, #1
	mov	r0, r7
	bl	LongTermRefFlg
	add	r3, r4, #6656
	add	r3, r3, #6
	cmp	r0, #0
	strne	r7, [r6, r3, asl #2]
	addne	r4, r4, #1
	cmp	r5, r8
	bne	.L248
.L246:
	ldr	r3, [r9, #2136]
	str	r4, [r9, #2148]
	cmp	r3, r4
	ldmlsfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	add	r0, r4, #6656
	mov	r2, #0
	add	r0, r0, #5
	add	r0, r6, r0, lsl #2
.L250:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r3
	bne	.L250
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L252:
	mov	r4, r8
	b	.L246
	UNWIND(.fnend)
	.size	UpdateLTReflist, .-UpdateLTReflist
	.align	2
	.global	UpdateReflist
	.type	UpdateReflist, %function
UpdateReflist:
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
	add	r9, r0, #24576
	mov	r6, r0
	ldr	r8, [r9, #2140]
	cmp	r8, #0
	beq	.L265
	add	r10, r0, #26368
	mov	r4, #0
	add	r10, r10, #148
	mov	r5, r4
.L261:
	ldr	r7, [r10, #4]!
	add	r5, r5, #1
	mov	r0, r7
	bl	ShortTermRefFlg
	add	r3, r4, #6592
	add	r3, r3, #54
	cmp	r0, #0
	strne	r7, [r6, r3, asl #2]
	addne	r4, r4, #1
	cmp	r5, r8
	bne	.L261
.L259:
	ldr	r3, [r9, #2136]
	str	r4, [r9, #2144]
	cmp	r3, r4
	ldmlsfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	add	r0, r4, #6592
	mov	r2, #0
	add	r0, r0, #53
	add	r0, r6, r0, lsl #2
.L263:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r3
	bne	.L263
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L265:
	mov	r4, r8
	b	.L259
	UNWIND(.fnend)
	.size	UpdateReflist, .-UpdateReflist
	.align	2
	.type	SlidingWinMark.part.8, %function
SlidingWinMark.part.8:
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
	add	r3, r0, #24576
	mov	r8, r0
	ldr	r7, [r3, #2140]
	cmp	r7, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r6, r0, #26368
	mov	r4, #0
	add	r6, r6, #148
.L274:
	ldr	r5, [r6, #4]!
	add	r4, r4, #1
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	mov	r0, r5
	cmp	r3, #0
	beq	.L273
	bl	ShortTermRefFlg
	cmp	r0, #0
	bne	.L285
.L273:
	cmp	r4, r7
	bne	.L274
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L285:
	mov	r0, r8
	mov	r1, r5
	bl	UnMarkFrameStoreRef
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	UpdateReflist
	UNWIND(.fnend)
	.size	SlidingWinMark.part.8, .-SlidingWinMark.part.8
	.align	2
	.global	GetPicNumX
	.type	GetPicNumX, %function
GetPicNumX:
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
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r0, #664]
	mvn	r0, r1
	movne	r3, r3, asl #1
	addne	r3, r3, #1
	add	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetPicNumX, .-GetPicNumX
	.align	2
	.global	UnMarkLTFrmByFrmIdx
	.type	UnMarkLTFrmByFrmIdx, %function
UnMarkLTFrmByFrmIdx:
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
	add	r3, r0, #24576
	ldr	r4, [r3, #2148]
	cmp	r4, #0
	ldmeqfd	sp, {r4, fp, sp, pc}
	ldr	ip, [r3, #2072]
	ldr	r3, [ip, #668]
	cmp	r3, r1
	addne	r2, r0, #26624
	movne	r3, #0
	addne	r2, r2, #24
	bne	.L293
	b	.L291
.L294:
	ldr	ip, [r2, #4]!
	ldr	lr, [ip, #668]
	cmp	lr, r1
	beq	.L291
.L293:
	add	r3, r3, #1
	cmp	r3, r4
	bne	.L294
	ldmfd	sp, {r4, fp, sp, pc}
.L291:
	mov	r1, ip
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	UnMarkFrameStoreRef
	UNWIND(.fnend)
	.size	UnMarkLTFrmByFrmIdx, .-UnMarkLTFrmByFrmIdx
	.align	2
	.global	UnMarkLTFldByFrmIdx
	.type	UnMarkLTFldByFrmIdx, %function
UnMarkLTFldByFrmIdx:
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
	add	ip, r0, #24576
	ldr	r6, [ip, #2148]
	cmp	r6, #0
	ldmeqfd	sp, {r4, r5, r6, fp, sp, pc}
	add	r4, r0, #26624
	mov	ip, #0
	add	r4, r4, #20
	b	.L304
.L302:
	cmp	ip, r6
	beq	.L318
.L304:
	ldr	lr, [r4, #4]!
	add	ip, ip, #1
	ldr	r5, [lr, #668]
	cmp	r5, r3
	bne	.L302
	cmp	r2, #1
	ldreqb	r5, [lr, #785]	@ zero_extendqisi2
	beq	.L317
	cmp	r2, #2
	bne	.L302
	ldrb	r5, [lr, #745]	@ zero_extendqisi2
.L317:
	clz	r5, r5
	mov	r5, r5, lsr #5
	cmp	lr, r1
	orrne	r5, r5, #1
	cmp	r5, #0
	beq	.L302
	mov	r1, lr
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	UnMarkFrameStoreRef
.L318:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkLTFldByFrmIdx, .-UnMarkLTFldByFrmIdx
	.align	2
	.global	UnMarkSTRef
	.type	UnMarkSTRef, %function
UnMarkSTRef:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L320
	add	ip, r0, #24576
	ldr	r1, [r1, #664]
	ldr	r4, [ip, #2144]
	sub	r1, r1, #1
	rsb	r2, r2, r1
	cmp	r4, #0
	beq	.L349
	add	ip, r0, #26368
	add	ip, ip, #212
	b	.L326
.L325:
	cmp	r3, r4
	beq	.L350
.L326:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #712]
	cmp	lr, r2
	bne	.L325
	ldrb	lr, [r1, #2]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L325
	ldr	lr, [r1, #704]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L325
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	UnMarkFrameStoreRef
.L320:
	add	r3, r0, #24576
	ldr	r1, [r1, #664]
	ldr	r5, [r3, #2144]
	rsb	r2, r2, r1, lsl #1
	cmp	r5, #0
	beq	.L351
	add	r4, r0, #26368
	mov	ip, #0
	add	r4, r4, #212
	b	.L331
.L327:
	tst	r3, #2
	beq	.L329
	ldr	r3, [r1, #784]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L352
.L329:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L353
.L331:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L327
	ldr	lr, [r1, #744]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L327
	ldr	lr, [r1, #752]
	cmp	lr, r2
	bne	.L327
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #24576
	strb	r3, [r1, #2]
	mov	r1, #0
	ldr	r3, [r2, #2008]
	strb	r1, [r3, #746]
	ldr	r3, [r2, #2008]
	ldrb	ip, [r3, #704]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #706]
	ldreq	r3, [r2, #2008]
	streqb	r1, [r3, #705]
	ldreq	r3, [r2, #2008]
	ldrb	r1, [r3, #2]	@ zero_extendqisi2
	cmp	r1, #0
	ldmnefd	sp, {r4, r5, r6, fp, sp, pc}
	ldr	ip, [r3, #692]
	mov	r2, r1
	add	lr, r0, #61440
	add	ip, ip, #15680
	add	ip, ip, #4
	str	r1, [r0, ip, asl #2]
	ldr	r1, [r3, #656]
.L346:
	ldr	r0, [lr, #2680]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	FSP_SetRef
.L352:
	ldr	r3, [r1, #792]
	cmp	r3, r2
	bne	.L329
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #2]
	add	r3, r3, #24576
	mov	r2, #0
	ldr	r1, [r3, #2008]
	strb	r2, [r1, #786]
	ldr	r1, [r3, #2008]
	ldrb	ip, [r1, #704]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r2
	streqb	r2, [r1, #706]
	ldreq	r1, [r3, #2008]
	streqb	r2, [r1, #705]
	ldreq	r1, [r3, #2008]
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, fp, sp, pc}
	ldr	ip, [r1, #692]
	add	lr, r0, #61440
	mov	r2, r3
	add	ip, ip, #15680
	add	ip, ip, #4
	str	r3, [r0, ip, asl #2]
	ldr	r1, [r1, #656]
	b	.L346
.L353:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L350:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L349:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L351:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkSTRef, .-UnMarkSTRef
	.align	2
	.global	UnMarkLTRef
	.type	UnMarkLTRef, %function
UnMarkLTRef:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L355
	add	r3, r0, #24576
	ldr	r5, [r3, #2148]
	cmp	r5, #0
	beq	.L383
	add	r4, r0, #26624
	mov	ip, #0
	add	r4, r4, #20
	b	.L364
.L360:
	tst	r3, #2
	beq	.L362
	ldr	r3, [r1, #784]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L384
.L362:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L385
.L364:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L360
	ldr	lr, [r1, #744]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L360
	ldr	lr, [r1, #748]
	cmp	r2, lr
	bne	.L360
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #24576
	strb	r3, [r1, #2]
	mov	r1, #0
	ldr	r3, [r2, #2072]
	strb	r1, [r3, #745]
	ldr	r3, [r2, #2072]
	ldrb	ip, [r3, #704]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #706]
	ldreq	r3, [r2, #2072]
	streqb	r1, [r3, #705]
	ldreq	r3, [r2, #2072]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #0
	ldreq	r3, [r3, #692]
	addeq	r3, r3, #15680
	addeq	r3, r3, #4
	streq	r2, [r0, r3, asl #2]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L355:
	add	r1, r0, #24576
	ldr	r4, [r1, #2148]
	cmp	r4, #0
	beq	.L386
	add	ip, r0, #26624
	add	ip, ip, #20
	b	.L366
.L365:
	cmp	r3, r4
	beq	.L387
.L366:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #708]
	cmp	lr, r2
	bne	.L365
	ldrb	lr, [r1, #2]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L365
	ldr	lr, [r1, #704]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L365
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	UnMarkFrameStoreRef
.L384:
	ldr	r3, [r1, #788]
	cmp	r2, r3
	bne	.L362
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #2]
	add	r3, r3, #24576
	mov	r1, #0
	ldr	r2, [r3, #2072]
	strb	r1, [r2, #785]
	ldr	r2, [r3, #2072]
	ldrb	ip, [r2, #704]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r2, #706]
	ldreq	r2, [r3, #2072]
	streqb	r1, [r2, #705]
	ldreq	r2, [r3, #2072]
	ldrb	r1, [r2, #2]	@ zero_extendqisi2
	cmp	r1, #0
	ldreq	r3, [r2, #692]
	addeq	r3, r3, #15680
	addeq	r3, r3, #4
	streq	r1, [r0, r3, asl #2]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L387:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L385:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L386:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L383:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkLTRef, .-UnMarkLTRef
	.align	2
	.global	MarkPicLTRef
	.type	MarkPicLTRef, %function
MarkPicLTRef:
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
	ldrb	r5, [r3, #3]	@ zero_extendqisi2
	add	r3, r0, #24576
	cmp	r5, #0
	beq	.L389
	ldr	r7, [r3, #2144]
	cmp	r7, #0
	beq	.L418
	add	r6, r0, #26368
	mov	ip, #0
	add	r6, r6, #212
	b	.L403
.L395:
	tst	r4, #2
	beq	.L398
	ldr	lr, [r3, #784]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	beq	.L419
.L398:
	add	ip, ip, #1
	cmp	ip, r7
	beq	.L420
.L403:
	ldr	r3, [r6, #4]!
	ldrb	r4, [r3, #2]	@ zero_extendqisi2
	tst	r4, #1
	beq	.L395
	ldr	lr, [r3, #744]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L395
	ldr	lr, [r3, #752]
	cmp	lr, r2
	bne	.L395
	ldrb	lr, [r3, #785]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L399
	ldr	lr, [r3, #668]
	cmp	lr, r1
	bne	.L398
.L399:
	str	r1, [r3, #668]
	sub	r3, r5, #1
	add	r2, r0, ip, lsl #2
	clz	r3, r3
	add	r2, r2, #24576
	mov	ip, #1
	mov	r3, r3, lsr #5
	mov	r0, #0
	add	r1, r3, r1, lsl #1
	ldr	r3, [r2, #2008]
	str	r1, [r3, #748]
	ldr	r3, [r2, #2008]
	strb	ip, [r3, #745]
	ldr	r3, [r2, #2008]
	strb	r0, [r3, #746]
	ldr	r3, [r2, #2008]
	ldrb	r1, [r3, #704]	@ zero_extendqisi2
	cmp	r1, #3
	cmpne	r1, r0
	bne	.L421
	ldrb	r1, [r3, #785]	@ zero_extendqisi2
	ldrb	r0, [r3, #745]	@ zero_extendqisi2
	cmp	r1, r0
	streqb	r1, [r3, #705]
	ldreq	r3, [r2, #2008]
	ldreqb	r2, [r3, #746]	@ zero_extendqisi2
	streqb	r2, [r3, #706]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L389:
	ldr	r6, [r3, #2144]
	cmp	r6, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	lr, r0, #26368
	mov	r3, r5
	add	lr, lr, #212
	b	.L394
.L393:
	add	r3, r3, #1
	cmp	r3, r6
	beq	.L422
.L394:
	ldr	ip, [lr, #4]!
	ldrb	r4, [ip, #2]	@ zero_extendqisi2
	cmp	r4, #3
	bne	.L393
	ldr	r4, [ip, #704]
	bic	r4, r4, #-16777216
	bic	r4, r4, #255
	cmp	r4, #65536
	bne	.L393
	ldr	r4, [ip, #712]
	cmp	r4, r2
	bne	.L393
	add	r3, r0, r3, lsl #2
	str	r1, [ip, #668]
	add	r3, r3, #24576
	mov	r0, #1
	mov	r2, #0
	ldr	ip, [r3, #2008]
	str	r1, [ip, #708]
	ldr	r1, [r3, #2008]
	strb	r0, [r1, #705]
	ldr	r1, [r3, #2008]
	strb	r0, [r1, #745]
	ldr	r1, [r3, #2008]
	strb	r0, [r1, #785]
	ldr	r1, [r3, #2008]
	strb	r2, [r1, #706]
	ldr	r1, [r3, #2008]
	strb	r2, [r1, #746]
	ldr	r3, [r3, #2008]
	strb	r2, [r3, #786]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L419:
	ldr	lr, [r3, #792]
	cmp	lr, r2
	bne	.L398
	ldrb	lr, [r3, #745]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L402
	ldr	lr, [r3, #668]
	cmp	lr, r1
	bne	.L398
.L402:
	str	r1, [r3, #668]
	sub	r3, r5, #2
	add	r0, r0, ip, lsl #2
	clz	r3, r3
	add	r0, r0, #24576
	mov	ip, #1
	mov	r3, r3, lsr #5
	mov	r2, #0
	add	r1, r3, r1, lsl #1
	ldr	r3, [r0, #2008]
	str	r1, [r3, #788]
	ldr	r3, [r0, #2008]
	strb	ip, [r3, #785]
	ldr	r3, [r0, #2008]
	strb	r2, [r3, #786]
	ldr	r3, [r0, #2008]
	ldrb	r2, [r3, #704]	@ zero_extendqisi2
	cmp	r2, #3
	cmpne	r2, #0
	bne	.L423
	ldrb	r2, [r3, #785]	@ zero_extendqisi2
	ldrb	r1, [r3, #745]	@ zero_extendqisi2
	cmp	r2, r1
	streqb	r2, [r3, #705]
	ldreq	r3, [r0, #2008]
	ldreqb	r2, [r3, #786]	@ zero_extendqisi2
	streqb	r2, [r3, #706]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L420:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L422:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L421:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L423:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L418:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MarkPicLTRef, .-MarkPicLTRef
	.align	2
	.global	MarkSTToLTRef
	.type	MarkSTToLTRef, %function
MarkSTToLTRef:
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
	mov	r5, r1
	ldrb	r1, [r1, #3]	@ zero_extendqisi2
	mov	r7, r3
	mov	r6, r0
	cmp	r1, #0
	bne	.L425
	ldr	r4, [r5, #664]
	mov	r1, r3
	sub	r4, r4, #1
	rsb	r4, r2, r4
	bl	UnMarkLTFrmByFrmIdx
.L426:
	mov	r3, r5
	mov	r2, r4
	mov	r1, r7
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MarkPicLTRef
.L425:
	add	r3, r0, #24576
	ldr	r4, [r5, #664]
	ldr	lr, [r3, #2144]
	rsb	r4, r2, r4, lsl #1
	cmp	lr, #0
	beq	.L426
	add	ip, r0, #26368
	mov	r3, #0
	add	ip, ip, #212
	b	.L429
.L427:
	tst	r2, #2
	beq	.L428
	ldr	r2, [r1, #784]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #65536
	beq	.L440
.L428:
	cmp	r3, lr
	beq	.L426
.L429:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	tst	r2, #1
	beq	.L427
	ldr	r0, [r1, #744]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #65536
	bne	.L427
	ldr	r0, [r1, #752]
	cmp	r0, r4
	bne	.L427
	mov	r3, r7
	mov	r2, #1
	mov	r0, r6
	bl	UnMarkLTFldByFrmIdx
	b	.L426
.L440:
	ldr	r2, [r1, #792]
	cmp	r2, r4
	bne	.L428
	mov	r3, r7
	mov	r2, #2
	mov	r0, r6
	bl	UnMarkLTFldByFrmIdx
	b	.L426
	UNWIND(.fnend)
	.size	MarkSTToLTRef, .-MarkSTToLTRef
	.align	2
	.global	UpdateMaxLTFrmIdx
	.type	UpdateMaxLTFrmIdx, %function
UpdateMaxLTFrmIdx:
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
	add	r6, r0, #24576
	mov	r7, r0
	ldr	r3, [r6, #2148]
	str	r1, [r6, #2152]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #26624
	mov	r3, r1
	add	r5, r5, #20
	mov	r4, #0
	b	.L445
.L443:
	ldr	r3, [r6, #2148]
	cmp	r3, r4
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r6, #2152]
.L445:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	ldr	r2, [r1, #668]
	cmp	r2, r3
	bcc	.L443
	mov	r0, r7
	bl	UnMarkFrameStoreRef
	b	.L443
	UNWIND(.fnend)
	.size	UpdateMaxLTFrmIdx, .-UpdateMaxLTFrmIdx
	.align	2
	.global	UnMarkAllSTRef
	.type	UnMarkAllSTRef, %function
UnMarkAllSTRef:
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
	add	r7, r0, #24576
	mov	r6, r0
	ldr	r3, [r7, #2144]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #26368
	mov	r4, #0
	add	r5, r5, #212
.L448:
	ldr	r1, [r5, #4]!
	mov	r0, r6
	bl	UnMarkFrameStoreRef
	ldr	r3, [r7, #2144]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L448
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkAllSTRef, .-UnMarkAllSTRef
	.align	2
	.global	MarkCurrPicLT
	.type	MarkCurrPicLT, %function
MarkCurrPicLT:
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
	mov	r5, r2
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	mov	r4, r1
	cmp	r2, #0
	beq	.L454
	mov	r3, r5
	ldr	r1, [r1, #656]
	bl	UnMarkLTFldByFrmIdx
.L453:
	mov	r2, #1
	mov	r3, #0
	str	r5, [r4, #668]
	strb	r2, [r4, #4]
	strb	r3, [r4, #5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L454:
	mov	r1, r5
	bl	UnMarkLTFrmByFrmIdx
	b	.L453
	UNWIND(.fnend)
	.size	MarkCurrPicLT, .-MarkCurrPicLT
	.align	2
	.global	H264_Sei_Get_Dpb_Output_Time
	.type	H264_Sei_Get_Dpb_Output_Time, %function
H264_Sei_Get_Dpb_Output_Time:
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
	subs	r3, r0, #0
	beq	.L464
	add	r0, r3, #12288
	add	r1, r3, #20480
	mov	r4, #2208
	add	r3, r3, #24576
	ldr	lr, [r0, #1304]
	mov	r2, #4000
	ldr	r1, [r1, #216]
	ldr	r5, [r0, #1300]
	ldr	r0, [r3, #1864]
	mla	r4, r4, r1, lr
	ldr	r1, [r3, #1860]
	ldr	ip, [r3, #1848]
	add	r0, r0, #1
	add	r1, r1, #1
	ldr	lr, [r3, #1852]
	ldr	r4, [r4, #28]
	str	r0, [r3, #1864]
	subs	r0, r1, #1
	str	ip, [r3, #1868]
	mla	r2, r2, r4, r5
	movne	r0, #1
	cmp	ip, #0
	str	r1, [r3, #1860]
	str	lr, [r3, #1876]
	movne	r0, #0
	cmp	r0, #0
	ldr	r0, [r2, #3344]
	ldrne	ip, [r3, #1872]
	str	r0, [r3, #1912]
	addne	ip, ip, #2
	ldr	r0, [r2, #3348]
	strne	ip, [r3, #1868]
	cmp	r1, #1
	str	r0, [r3, #1916]
	beq	.L465
	ldrb	r1, [r3, #1936]	@ zero_extendqisi2
	add	r4, r3, #1856
	cmp	r1, #1
	ldrd	r0, [r4, #48]
	beq	.L466
	adds	r0, r0, ip
	adc	r1, r1, #0
	strd	r0, [r4, #40]
.L459:
	adds	r0, r0, lr
	mov	lr, #0
	adc	r1, r1, #0
	strb	lr, [r3, #1936]
	ldr	r4, [r2, #3368]
	movs	r1, r1, lsr #1
	mov	r0, r0, rrx
	ldr	r8, [r2, #3344]
	add	lr, r3, #1856
	subs	r6, r0, r4
	sbc	r7, r1, #0
	umull	r4, r5, r6, r8
	mla	r5, r8, r7, r5
	strd	r4, [lr, #24]
	ldr	r2, [r2, #3368]
	subs	r0, r0, r2
	sbc	r1, r1, #0
	strd	r0, [lr, #32]
	str	ip, [r3, #1872]
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L465:
	mov	r6, #0
	str	r6, [r3, #1896]
	mov	r0, r6
	mov	r1, r6
	str	r6, [r3, #1904]
	str	r6, [r3, #1900]
	str	r6, [r3, #1908]
	b	.L459
.L466:
	adds	r0, r0, ip
	adc	r1, r1, #0
	strd	r0, [r4, #40]
	strd	r0, [r4, #48]
	b	.L459
.L464:
	movw	r3, #1475
	ldr	r2, .L467
	ldr	r1, .L467+4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L468:
	.align	2
.L467:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264_Sei_Get_Dpb_Output_Time, .-H264_Sei_Get_Dpb_Output_Time
	.align	2
	.global	H264_Get_Last_IDR_Frame_Info
	.type	H264_Get_Last_IDR_Frame_Info, %function
H264_Get_Last_IDR_Frame_Info:
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
	subs	r3, r0, #0
	beq	.L472
	cmp	r1, #5
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, [r3]
	mvn	r5, #0
	mvn	r4, #0
	ldrd	r0, [r2, #64]
	cmp	r1, r5
	cmpeq	r0, r4
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	movw	ip, #26464
	add	r2, r3, #26368
	ldrd	r4, [r3, ip]
	movw	ip, #26496
	strd	r0, [r3, ip]
	strd	r4, [r2, #136]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L472:
	movw	r3, #1543
	ldr	r2, .L473
	ldr	r1, .L473+4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L474:
	.align	2
.L473:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264_Get_Last_IDR_Frame_Info, .-H264_Get_Last_IDR_Frame_Info
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.global	H264_Sei_Get_Frame_Pts
	.type	H264_Sei_Get_Frame_Pts, %function
H264_Sei_Get_Frame_Pts:
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
	subs	r4, r0, #0
	beq	.L481
	add	r2, r4, #26368
	add	r3, r4, #24576
	add	r2, r2, #144
	movw	r0, #26496
	ldr	r5, [r3, #1912]
	movw	r1, #26464
	ldr	r10, [r3, #1916]
	ldrd	r2, [r2, #-8]
	cmp	r5, #0
	ldrd	r6, [r4, r1]
	strd	r2, [fp, #-60]
	ldrd	r2, [r4, r0]
	strd	r2, [fp, #-52]
	beq	.L479
	mov	r9, r5
	mov	r0, r10
	b	.L478
.L480:
	mov	r9, r1
.L478:
	mov	r1, r9
	bl	__aeabi_uidivmod
	mov	r0, r9
	cmp	r1, #0
	bne	.L480
.L477:
	ldrd	r2, [fp, #-60]
	mov	r1, r9
	mov	r0, r5
	mov	r8, #1000
	subs	r2, r6, r2
	add	r4, r4, #61184
	mul	r6, r8, r2
	bl	__aeabi_uidiv
	mov	r1, r9
	mul	r6, r0, r6
	mov	r0, r10
	bl	__aeabi_uidiv
	mov	r1, r0
	mov	r0, r6
	bl	__aeabi_uidiv
	ldrd	r2, [fp, #-52]
	adds	r2, r2, r0
	adc	r3, r3, #0
	mov	r0, r2
	mov	r1, r3
	strd	r0, [r4, #88]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L479:
	mov	r9, r10
	b	.L477
.L481:
	movw	r3, #1565
	ldr	r2, .L482
	ldr	r1, .L482+4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L483:
	.align	2
.L482:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264_Sei_Get_Frame_Pts, .-H264_Sei_Get_Frame_Pts
	.align	2
	.global	CheckFrameStore
	.type	CheckFrameStore, %function
CheckFrameStore:
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
	add	r3, r0, #61440
	mov	r5, r0
	mov	r4, r1
	ldr	r2, [r3, #1380]
	cmp	r2, #0
	bne	.L485
	ldr	r2, [r1, #824]
	cmp	r2, #1
	beq	.L486
	ldr	r2, [r3, #2608]
	cmp	r2, #0
	beq	.L511
.L486:
	mov	r2, #1
	str	r2, [r3, #1380]
.L485:
	ldr	r0, [r3, #2680]
	ldr	r1, [r4, #656]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L488
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	cmpne	r3, #0
	beq	.L512
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L496
	cmp	r3, #1
	beq	.L496
	ldr	r3, [r4]
	mov	r1, #768
	movt	r1, 768
	bic	r3, r3, #16711680
	bic	r3, r3, #255
	cmp	r3, r1
	beq	.L513
	cmp	r2, #1
	beq	.L514
	cmp	r2, #2
	beq	.L515
.L494:
	ldr	r1, [r5]
	ldr	r2, [r0, #192]
	ldr	r3, [r1, #4]
	cmp	r2, r3
	bls	.L500
	ldr	r1, [r1, #644]
	cmp	r1, #0
	beq	.L516
.L500:
	mov	r0, #0
.L510:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L511:
	ldr	r2, [r0]
	ldr	r2, [r2, #24]
	cmp	r2, #0
	bne	.L486
	mvn	r0, #0
	b	.L510
.L512:
	ldr	r2, [r4, #656]
	mov	r0, #1
	ldr	r1, .L517
	bl	dprint_vfmw
.L490:
	ldr	r3, [r4, #824]
	cmp	r3, #1
	beq	.L497
	mvn	r0, #2
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L514:
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L494
	mov	r0, r2
	ldr	r1, .L517+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L510
.L515:
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	tst	r3, #2
	beq	.L494
	ldr	r1, .L517+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L510
.L497:
	mov	r3, #2
	mvn	r0, #2
	str	r3, [r4, #824]
	b	.L510
.L488:
	ldr	ip, [r4, #656]
	mov	r2, r4
	ldr	r3, [r4, #824]
	mov	r0, #1
	ldr	r1, .L517+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L490
.L496:
	ldr	r1, .L517+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L510
.L516:
	ldr	r1, .L517+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L510
.L513:
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	mov	r0, #1
	ldr	r1, .L517+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L510
.L518:
	.align	2
.L517:
	.word	.LC13
	.word	.LC17
	.word	.LC18
	.word	.LC14
	.word	.LC15
	.word	.LC19
	.word	.LC16
	UNWIND(.fnend)
	.size	CheckFrameStore, .-CheckFrameStore
	.align	2
	.global	GetImagePara
	.type	GetImagePara, %function
GetImagePara:
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
	add	r3, r0, #12288
	add	ip, r0, #20480
	mov	r4, r1
	ldr	r2, [r3, #1304]
	mov	r6, r0
	ldr	r1, [ip, #216]
	mov	r0, #2208
	ldrb	ip, [r4, #81]	@ zero_extendqisi2
	add	r7, r6, #61440
	ldr	r5, [r3, #1300]
	mov	r8, #4000
	mla	r2, r0, r1, r2
	ldrb	r1, [r4, #80]	@ zero_extendqisi2
	bfc	ip, #0, #2
	ldr	lr, [r4, #8]
	bfc	r1, #0, #2
	ldrb	r0, [r4, #82]	@ zero_extendqisi2
	ldr	r3, [r2, #28]
	strb	ip, [r4, #81]
	strb	r1, [r4, #80]
	ldr	r1, [r7, #1388]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	mla	r3, r8, r3, r5
	str	r1, [r4, #124]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	bfi	r0, r2, #1, #1
	str	lr, [r4, #136]
	strb	r0, [r4, #82]
	cmp	r1, #3
	ldrls	pc, [pc, r1, asl #2]
	b	.L565
.L522:
	.word	.L521
	.word	.L523
	.word	.L524
	.word	.L521
.L524:
	ldr	r0, [r4, #688]
	mov	ip, #3
	ldrb	r2, [r4, #81]	@ zero_extendqisi2
	add	r5, r6, #24576
	str	ip, [r4, #72]
	str	r0, [r4, #168]
	and	r2, r2, #240
	ldr	ip, [r4, #804]
	orr	r2, r2, #11
	ldr	r0, [r4, #820]
	strb	r2, [r4, #81]
	ldr	lr, [r4, #684]
	ldrb	r2, [r4, #80]	@ zero_extendqisi2
	str	ip, [r4, #76]
	bfi	r2, lr, #0, #2
	strb	r2, [r4, #80]
	ldr	r2, [r0, #700]
	str	r2, [r4, #736]
.L520:
	ldrb	r2, [r3, #18]	@ zero_extendqisi2
	str	r2, [r4, #412]
	str	r2, [r4, #416]
	ldrb	r2, [r3, #22]	@ zero_extendqisi2
	cmp	r2, #0
	ldrne	r2, [r3, #3332]
	mov	r3, #1
	str	r3, [r4, #420]
	str	r2, [r4, #424]
	ldr	r3, [r6]
	ldr	r3, [r3, #604]
	str	r3, [r4, #140]
	ldr	r3, [r6]
	ldr	r3, [r3, #608]
	str	r3, [r4, #144]
	ldr	r3, [r6]
	ldr	r3, [r3, #612]
	str	r3, [r4, #148]
	ldr	r3, [r6]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L541
	ldrb	r3, [r4, #704]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L541
	cmp	r1, #3
	ldreqb	r2, [r4, #81]	@ zero_extendqisi2
	bfieq	r2, r3, #0, #2
	streqb	r2, [r4, #81]
.L541:
	add	r9, r4, #608
	mvn	r1, #0
	mvn	r0, #0
	ldrd	r2, [r9, #-8]
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L543
	ldr	r3, [r5, #2140]
	cmp	r3, #0
	beq	.L543
	add	r8, r6, #26368
	mvn	r2, #1
	add	r8, r8, #148
	mvn	r3, #0
	str	r4, [fp, #-60]
	mov	r10, #0
	mov	r4, r8
	str	r9, [fp, #-52]
	mov	r8, r2
	mov	r9, r3
	mvn	r1, #0
	str	r1, [fp, #-48]
.L546:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L545
	ldr	r1, [r1, #656]
	ldr	r0, [r7, #2680]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L545
	ldrsb	r1, [r0, #1]
	cmp	r1, #3
	cmpne	r1, #0
	beq	.L545
	ldr	r1, [r4]
	add	r1, r1, #608
	ldrd	r0, [r1, #-8]
	cmp	r1, r9
	cmpeq	r0, r8
	strcc	r10, [fp, #-48]
	movcc	r8, r0
	movcc	r9, r1
.L545:
	ldr	r1, [r5, #2140]
	add	r10, r10, #1
	cmp	r10, r1
	bcc	.L546
	ldr	r3, [fp, #-48]
	mov	r1, r9
	mov	r0, r8
	ldr	r4, [fp, #-60]
	cmn	r3, #1
	strd	r0, [fp, #-68]
	ldr	r9, [fp, #-52]
	beq	.L543
	ldrd	r2, [r9, #-8]
	cmp	r3, r1
	cmpeq	r2, r8
	bhi	.L584
.L543:
	ldrb	r3, [r5, #1808]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L547
	ldr	r3, [r5, #1824]
	cmp	r3, #3
	moveq	r3, #1
	streq	r3, [r4, #292]
	beq	.L547
	cmp	r3, #4
	moveq	r3, #2
	streq	r3, [r4, #292]
	beq	.L547
	cmp	r3, #5
	moveq	r3, #3
	streq	r3, [r4, #292]
	beq	.L547
	mov	r0, #0
	ldr	r1, .L587
	str	r0, [r4, #292]
	ldr	r2, [r5, #1824]
	bl	dprint_vfmw
.L547:
	ldr	r0, [r7, #2680]
	ldr	r1, [r4, #656]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L519
	ldr	r3, .L587+4
	mov	r2, #640
	add	r1, r4, #16
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #296]
	mov	r2, #1
	ldrb	r3, [r4, #704]	@ zero_extendqisi2
	strb	r2, [r5, #291]
	cmp	r3, #0
	movne	r3, #4
	strb	r3, [r5, #284]
	ldr	r3, [r4, #728]
	strb	r2, [r5, #289]
	str	r3, [r5, #300]
	str	r3, [r5, #308]
	str	r3, [r5, #304]
	ldr	r3, [r4, #736]
	str	r3, [r5, #236]
.L519:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L523:
	ldr	r0, [r4, #688]
	mov	ip, #3
	ldrb	r2, [r4, #81]	@ zero_extendqisi2
	add	r5, r6, #24576
	str	ip, [r4, #76]
	str	r0, [r4, #168]
	and	r2, r2, #240
	ldr	ip, [r4, #764]
	orr	r2, r2, #7
	ldr	r0, [r4, #780]
	strb	r2, [r4, #81]
	ldr	lr, [r4, #684]
	ldrb	r2, [r4, #80]	@ zero_extendqisi2
	str	ip, [r4, #72]
	bfi	r2, lr, #0, #2
	strb	r2, [r4, #80]
	ldr	r2, [r0, #700]
	str	r2, [r4, #736]
	b	.L520
.L521:
	ldrb	r2, [r4, #704]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L525
	ldr	r0, [r4, #680]
	ldr	r2, [r4, #688]
	cmp	r0, #0
	ldr	ip, [r4, #684]
	ldreq	r9, [r4, #764]
	movne	lr, #3
	ldreq	r8, [r4, #804]
	moveq	lr, #2
	ldrne	r9, [r4, #764]
	moveq	r0, #3
	ldrne	r8, [r4, #804]
	movne	r0, lr
	str	r2, [r4, #168]
.L527:
	ldr	r5, [r4, #756]
	ldr	r2, [r4, #796]
	cmp	r5, r2
	beq	.L585
	movle	r10, #1
	movgt	r10, #0
.L538:
	add	r5, r6, #24576
	ldrb	r2, [r5, #1844]	@ zero_extendqisi2
	cmp	r2, #3
	moveq	r10, #1
	beq	.L539
	cmp	r2, #4
	moveq	r10, #0
.L539:
	ldrb	r2, [r4, #81]	@ zero_extendqisi2
	str	r9, [r4, #72]
	bfi	r2, r10, #4, #2
	ldrb	r9, [r4, #80]	@ zero_extendqisi2
	bfi	r2, r0, #2, #2
	str	r8, [r4, #76]
	bfi	r9, ip, #0, #2
	bfi	r2, lr, #0, #2
	strb	r9, [r4, #80]
	strb	r2, [r4, #81]
	b	.L520
.L584:
	ldr	ip, [r7, #2680]
	strd	r0, [sp]
	mov	r0, ip
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L543
	ldrd	r2, [r9, #-8]
	mov	r0, #29
	ldr	r1, .L587+8
	strd	r2, [fp, #-60]
	ldrd	r2, [fp, #-68]
	strd	r2, [sp]
	ldrd	r2, [fp, #-60]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	add	r8, r3, #6592
	ldrd	r2, [r9, #-8]
	add	r8, r8, #38
	ldr	r1, [r6, r8, asl #2]
	add	r1, r1, #608
	strd	r2, [r1, #-8]
	ldrd	r2, [fp, #-68]
	strd	r2, [r9, #-8]
	b	.L543
.L525:
	ldr	r8, [r4, #760]
	ldr	r2, [r7, #2676]
	ldr	r9, [r4, #800]
	cmp	r8, r2
	bhi	.L586
	cmp	r2, r9
	bcc	.L531
.L529:
	ldr	r2, [r4, #688]
	mov	r0, #3
	ldr	ip, [r4, #684]
	ldr	lr, [r4, #764]
	ldr	r5, [r4, #804]
	str	r2, [r4, #168]
.L532:
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	cmp	r2, #1
	streq	r9, [r4, #168]
	moveq	ip, r5
	moveq	r0, #2
	beq	.L534
	cmp	r2, #2
	streq	r8, [r4, #168]
	moveq	ip, lr
	moveq	r0, #1
.L534:
	ldr	r2, [r4, #776]
	mov	r9, lr
	ldr	r10, [r4, #816]
	mov	r8, r5
	str	lr, [r4, #72]
	mov	lr, #3
	add	r2, r2, r10
	str	r5, [r4, #76]
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
	str	r2, [r4, #736]
	b	.L527
.L531:
	ldr	ip, [r4, #764]
	mov	r0, #1
	ldr	r5, [r4, #804]
	str	r8, [r4, #168]
	mov	lr, ip
	b	.L532
.L585:
	ldr	r2, [r4, #84]
	cmp	r2, #720
	movne	r10, #1
	bne	.L538
	ldr	r10, [r4, #88]
	subs	r10, r10, #480
	movne	r10, #1
	b	.L538
.L586:
	cmp	r2, r9
	bcc	.L529
	ldr	ip, [r4, #804]
	mov	r0, #2
	str	r9, [r4, #168]
	ldr	lr, [r4, #764]
	mov	r5, ip
	b	.L532
.L565:
	add	r5, r6, #24576
	b	.L520
.L588:
	.align	2
.L587:
	.word	.LC21
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	UNWIND(.fnend)
	.size	GetImagePara, .-GetImagePara
	.align	2
	.global	SetFrmRepeatCount
	.type	SetFrmRepeatCount, %function
SetFrmRepeatCount:
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
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SetFrmRepeatCount.part.7
	UNWIND(.fnend)
	.size	SetFrmRepeatCount, .-SetFrmRepeatCount
	.align	2
	.global	SplitFrmToFlds
	.type	SplitFrmToFlds, %function
SplitFrmToFlds:
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
	ldrb	lr, [r0, #705]	@ zero_extendqisi2
	mov	r5, #1
	ldrb	ip, [r0, #706]	@ zero_extendqisi2
	mov	r4, #2
	ldr	r1, [r0, #720]
	ldr	r2, [r0, #724]
	ldr	r3, [r0, #740]
	strb	r5, [r0, #744]
	strb	r4, [r0, #784]
	strb	lr, [r0, #745]
	strb	lr, [r0, #785]
	strb	ip, [r0, #746]
	strb	ip, [r0, #786]
	str	r1, [r0, #760]
	str	r1, [r0, #800]
	str	r2, [r0, #764]
	str	r2, [r0, #804]
	str	r3, [r0, #780]
	str	r3, [r0, #820]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	SplitFrmToFlds, .-SplitFrmToFlds
	.align	2
	.global	CombineFldsToFrm
	.type	CombineFldsToFrm, %function
CombineFldsToFrm:
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
	ldr	r2, [r0, #796]
	mov	lr, #3
	ldr	r1, [r0, #756]
	ldr	r3, [r0, #800]
	cmp	r2, r1
	ldr	r5, [r0, #760]
	ldrb	r4, [r0, #785]	@ zero_extendqisi2
	ldr	ip, [r0, #780]
	movge	r2, r1
	add	r3, r3, r5
	cmp	r4, #0
	strb	lr, [r0, #704]
	mov	r3, r3, lsr #1
	str	ip, [r0, #740]
	str	r2, [r0, #716]
	str	r2, [r0, #672]
	str	r3, [r0, #720]
	beq	.L593
	ldrb	r2, [r0, #745]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L594
.L593:
	ldr	r2, [r0, #784]
	mov	r1, #0
	strb	r1, [r0, #705]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, r1
	beq	.L600
	ldr	r2, [r0, #744]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	movne	r1, #1
	beq	.L600
.L596:
	ldr	r2, [r0, #764]
	strb	r1, [r0, #706]
	cmp	r2, #0
	beq	.L598
	ldr	r1, [r0, #804]
	cmp	r1, #0
	moveq	r2, r1
	beq	.L598
	cmp	r2, r1
	movcc	r2, r1
.L598:
	str	r2, [r0, #724]
	str	r2, [r0, #684]
	str	r3, [r0, #688]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L594:
	mov	r1, #1
	strb	r1, [r0, #705]
.L600:
	mov	r1, #0
	b	.L596
	UNWIND(.fnend)
	.size	CombineFldsToFrm, .-CombineFldsToFrm
	.align	2
	.global	GetAPC
	.type	GetAPC, %function
GetAPC:
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
	subs	r7, r1, #0
	mov	r5, r0
	beq	.L634
	cmp	r2, #1
	beq	.L615
	cmp	r2, #2
	beq	.L616
	ldr	r8, [r7, #756]
	ldr	r9, [r7, #796]
.L617:
	add	r6, r5, #24576
	ldr	r1, [r6, #2412]
	cmp	r1, #0
	beq	.L626
	ldr	r4, [r6, #2156]
	cmp	r4, #0
	addne	r3, r5, #26624
	movne	r4, #0
	addne	r3, r3, #108
	bne	.L620
	b	.L618
.L624:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L618
.L620:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L624
.L626:
	mvn	r0, #0
.L630:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L616:
	ldr	r8, [r7, #796]
	mov	r9, r8
	b	.L617
.L618:
	add	r3, r5, #61440
	ldr	r1, [r7, #656]
	ldr	r0, [r3, #2680]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L621
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L621
	add	r5, r5, r4, lsl #2
	mov	r3, #1
	add	r5, r5, #24576
	ldr	r1, .L635
	str	r3, [r5, #2156]
	ldr	r3, [r0, #28]
	mov	r0, #13
	ldr	r3, [r3, #4]
	str	r8, [r5, #2284]
	str	r9, [r5, #2348]
	str	r3, [r5, #2220]
	ldr	r3, [r6, #2416]
	cmp	r3, #15
	addls	r3, r3, #1
	movhi	r3, #16
	str	r3, [r6, #2416]
	mov	r3, r4
	ldr	r2, [r7, #164]
	bl	dprint_vfmw
	mov	r0, #0
	str	r4, [r7, #696]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L615:
	ldr	r8, [r7, #756]
	mov	r9, r8
	b	.L617
.L621:
	mov	r1, #0
	ldr	r2, [r7, #656]
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	stmia	sp, {r0, r1}
	mov	r0, r1
	ldr	r1, .L635+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L630
.L634:
	mov	r0, r7
	movw	r3, #2539
	ldr	r2, .L635+8
	ldr	r1, .L635+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L630
.L636:
	.align	2
.L635:
	.word	.LC22
	.word	.LC23
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	GetAPC, .-GetAPC
	.align	2
	.global	SlidingWinMark
	.type	SlidingWinMark, %function
SlidingWinMark:
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
	add	r2, r0, #24576
	add	r3, r0, #16384
	ldr	r1, [r2, #2148]
	ldr	r3, [r3, #456]
	ldr	r2, [r2, #2144]
	rsb	r3, r1, r3
	cmp	r2, r3
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SlidingWinMark.part.8
	UNWIND(.fnend)
	.size	SlidingWinMark, .-SlidingWinMark
	.align	2
	.global	DumpDPB
	.type	DumpDPB, %function
DumpDPB:
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
	ldr	r3, .L649
	mov	r5, r0
	ldr	r3, [r3]
	tst	r3, #16384
	beq	.L639
	add	r6, r0, #24576
	ldr	r3, [r6, #2140]
	cmp	r3, #0
	addne	r7, r0, #26368
	movne	r4, #0
	addne	r7, r7, #148
	beq	.L645
.L644:
	ldr	ip, [r7, #4]!
	mov	r2, r4
	ldr	r1, .L649+4
	mov	r0, #14
	add	r4, r4, #1
	ldrb	lr, [ip, #2]	@ zero_extendqisi2
	ldr	r3, [ip, #660]
	str	lr, [sp, #4]
	ldr	ip, [ip, #672]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r6, #2140]
	cmp	r3, r4
	bhi	.L644
.L645:
	ldr	r1, .L649+8
	mov	r0, #14
	bl	dprint_vfmw
	ldr	r3, [r6, #2144]
	cmp	r3, #0
	addne	r5, r5, #26368
	movne	r4, #0
	addne	r5, r5, #212
	beq	.L643
.L646:
	ldr	ip, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L649+12
	mov	r0, #14
	ldrb	lr, [ip, #2]	@ zero_extendqisi2
	ldr	r3, [ip, #660]
	str	lr, [sp, #4]
	ldr	ip, [ip, #672]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5]
	mov	r2, r4
	ldr	r1, .L649+16
	mov	r0, #14
	add	r4, r4, #1
	ldr	r3, [r3, #716]
	bl	dprint_vfmw
	ldr	r3, [r6, #2144]
	cmp	r3, r4
	bhi	.L646
.L643:
	ldr	r1, .L649+8
	mov	r0, #14
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L639:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L650:
	.align	2
.L649:
	.word	g_PrintEnable
	.word	.LC24
	.word	.LC2
	.word	.LC25
	.word	.LC26
	UNWIND(.fnend)
	.size	DumpDPB, .-DumpDPB
	.align	2
	.global	UpdateCurrFrameInfo
	.type	UpdateCurrFrameInfo, %function
UpdateCurrFrameInfo:
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
	add	r3, r0, #57344
	ldrb	r2, [r3, #3330]	@ zero_extendqisi2
	ldr	r4, [r3, #3984]
	strb	r2, [r4]
	ldrb	r2, [r3, #3332]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
	bne	.L652
	ldrb	r2, [r3, #3333]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
.L652:
	strb	r2, [r4, #2]
	ldr	r2, [r3, #3992]
	str	r2, [r4, #660]
	ldr	r2, [r3, #4028]
	str	r2, [r4, #688]
	ldr	r2, [r3, #4020]
	str	r2, [r4, #684]
	ldr	r2, [r3, #4004]
	str	r2, [r4, #672]
	ldr	r2, [r3, #4052]
	str	r2, [r4, #692]
	ldr	r2, [r3, #3996]
	str	r2, [r4, #668]
	ldrb	r2, [r3, #3337]	@ zero_extendqisi2
	str	r2, [r4, #680]
	ldrb	r2, [r3, #3335]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r1, #3
	movne	r1, #0
	strb	r1, [r4, #3]
	ldrb	r2, [r3, #3331]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L655
	bcc	.L656
	cmp	r2, #2
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	str	r4, [r4, #820]
	mov	ip, #1
	strb	ip, [r4, #784]
	mov	r6, #0
	ldrb	ip, [r3, #3332]	@ zero_extendqisi2
	strb	ip, [r4, #785]
	ldrb	ip, [r3, #3333]	@ zero_extendqisi2
	strb	ip, [r4, #786]
	ldr	ip, [r3, #4012]
	str	ip, [r4, #796]
	ldr	ip, [r3, #4020]
	str	ip, [r4, #804]
	ldr	lr, [r3, #4028]
	str	r6, [r4, #680]
	str	lr, [r4, #800]
	ldrb	r5, [r3, #3329]	@ zero_extendqisi2
	cmp	r5, r6
	beq	.L673
	ldr	r2, [r4, #760]
	mov	r5, #3
	strb	r5, [r4, #1]
	add	r0, r0, #61184
	add	lr, lr, r2
	str	lr, [r4, #688]
	str	lr, [r4, #720]
	mvn	r7, #0
	ldrb	r2, [r3, #3335]	@ zero_extendqisi2
	cmp	r2, #1
	orreq	r6, r1, #2
	strb	r6, [r4, #3]
	ldrd	r8, [r0, #88]
	mvn	r6, #0
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L664
	add	r2, r4, #608
	ldrd	r0, [r2, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	beq	.L674
.L664:
	ldr	r2, [r4, #764]
.L671:
	cmp	r2, ip
	mov	r0, r4
	movcc	r2, ip
	str	r2, [r4, #684]
	ldr	r3, [r3, #4004]
	str	r3, [r4, #672]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	CombineFldsToFrm
.L656:
	str	r4, [r4, #740]
	mov	r1, #3
	mov	r2, #0
	strb	r1, [r4, #1]
	strb	r2, [r4, #704]
	add	r1, r3, #3344
	ldrb	r5, [r3, #3332]	@ zero_extendqisi2
	mov	r2, #640
	add	r0, r4, #16
	strb	r5, [r4, #705]
	ldrb	r6, [r3, #3333]	@ zero_extendqisi2
	strb	r6, [r4, #706]
	ldr	ip, [r3, #4008]
	str	ip, [r4, #716]
	ldr	r7, [r3, #4020]
	str	r7, [r4, #724]
	ldr	r8, [r3, #4028]
	str	r8, [r4, #720]
	ldr	ip, [r3, #4012]
	str	ip, [r4, #756]
	ldr	r3, [r3, #4016]
	str	r3, [r4, #796]
	bl	memcpy
	mov	r2, #1
	mov	r3, #2
	str	r8, [r4, #760]
	str	r8, [r4, #800]
	str	r7, [r4, #764]
	str	r7, [r4, #804]
	strb	r6, [r4, #746]
	strb	r6, [r4, #786]
	strb	r5, [r4, #745]
	strb	r5, [r4, #785]
	str	r4, [r4, #780]
	str	r4, [r4, #820]
	strb	r2, [r4, #744]
	strb	r3, [r4, #784]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L655:
	strb	r2, [r4, #744]
	mov	r5, #0
	str	r4, [r4, #780]
	ldrb	ip, [r3, #3332]	@ zero_extendqisi2
	strb	ip, [r4, #745]
	ldrb	ip, [r3, #3333]	@ zero_extendqisi2
	strb	ip, [r4, #746]
	ldr	ip, [r3, #4012]
	str	ip, [r4, #756]
	ldr	ip, [r3, #4020]
	str	ip, [r4, #764]
	ldr	lr, [r3, #4028]
	str	r5, [r4, #680]
	str	lr, [r4, #760]
	ldrb	r6, [r3, #3329]	@ zero_extendqisi2
	cmp	r6, r5
	beq	.L675
	ldr	r2, [r4, #800]
	mov	r6, #3
	strb	r6, [r4, #1]
	add	r0, r0, #61184
	add	lr, lr, r2
	str	lr, [r4, #688]
	str	lr, [r4, #720]
	mvn	r7, #0
	ldrb	r2, [r3, #3335]	@ zero_extendqisi2
	mvn	r6, #0
	cmp	r2, #1
	orreq	r5, r1, #1
	strb	r5, [r4, #3]
	ldrd	r8, [r0, #88]
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L660
	add	r2, r4, #608
	ldrd	r0, [r2, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	streqd	r8, [r2, #-8]
.L660:
	ldr	r2, [r4, #804]
	b	.L671
.L673:
	strb	r2, [r4, #1]
	add	r1, r3, #3344
	str	lr, [r4, #688]
	add	r0, r4, #16
	str	lr, [r4, #720]
	mov	r2, #640
	ldrb	r3, [r3, #3335]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r5, #2
	strb	r5, [r4, #3]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L675:
	strb	r2, [r4, #1]
	add	r1, r3, #3344
	str	lr, [r4, #688]
	add	r0, r4, #16
	str	lr, [r4, #720]
	mov	r2, #640
	ldrb	r3, [r3, #3335]	@ zero_extendqisi2
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r4, #3]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L674:
	strd	r8, [r2, #-8]
	b	.L664
	UNWIND(.fnend)
	.size	UpdateCurrFrameInfo, .-UpdateCurrFrameInfo
	.align	2
	.global	SimpleSlideDPB
	.type	SimpleSlideDPB, %function
SimpleSlideDPB:
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
	add	r3, r0, #24576
	mov	r4, r0
	ldr	r1, [r3, #2140]
	ldr	r2, [r3, #2136]
	cmp	r1, r2
	bcs	.L682
.L677:
	add	r0, r4, #57344
	mov	r2, #0
	ldr	r3, [r0, #4000]
	strb	r2, [r0, #3332]
	cmp	r3, r2
	movne	r3, #1
	strneb	r3, [r0, #3333]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L682:
	ldr	r1, [r3, #1944]
	bl	UnMarkFrameStoreRef
	mov	r1, #0
	mov	r0, r4
	bl	RemoveFrameStoreOutDPB
	b	.L677
	UNWIND(.fnend)
	.size	SimpleSlideDPB, .-SimpleSlideDPB
	.align	2
	.global	H264_ArrangeVahbMem
	.type	H264_ArrangeVahbMem, %function
H264_ArrangeVahbMem:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	mov	r5, r2
	sub	r2, r1, #32
	sub	r3, r5, #32
	mov	r4, r1
	movw	r1, #8160
	cmp	r3, r1
	cmpls	r2, r1
	mov	r6, r0
	movhi	r1, #1
	movls	r1, #0
	bhi	.L695
	ldr	r3, .L699
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6]
	str	r4, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r4, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L686
	add	r2, r6, #24576
	ldrb	r3, [fp, #4]	@ zero_extendqisi2
	mov	r1, #5
	strb	r1, [fp, #-46]
	ldr	r2, [r2, #2136]
	add	r2, r2, #1
	strb	r2, [fp, #-47]
.L692:
	cmp	r5, #63
	cmphi	r4, #63
	strb	r3, [fp, #-45]
	movls	r7, #1
	movhi	r7, #0
	bls	.L696
	add	r4, r6, #61440
	sub	r1, fp, #48
	ldr	r0, [r4, #2680]
	bl	FSP_ConfigInstance
	subs	r5, r0, #0
	bne	.L688
	ldr	r1, [r6]
	sub	r3, fp, #52
	ldr	r0, [r4, #2680]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L697
	cmp	r0, #0
	moveq	r0, #1
	bne	.L698
.L693:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L686:
	mov	r3, #1
	mov	r2, #5
	strb	r3, [fp, #-47]
	strb	r2, [fp, #-46]
	b	.L692
.L695:
	mov	r3, r5
	mov	r2, r4
	ldr	r1, .L699+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L696:
	mov	r3, r5
	mov	r2, r4
	ldr	r1, .L699+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L693
.L688:
	mov	r0, r7
	ldr	r1, .L699+12
	bl	dprint_vfmw
.L694:
	mvn	r0, #19
	b	.L693
.L698:
	mov	r0, r5
	ldr	r1, .L699+16
	bl	dprint_vfmw
	b	.L694
.L697:
	add	r0, r6, #8
	bl	ResetVoQueue
	b	.L694
.L700:
	.align	2
.L699:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC28
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	H264_ArrangeVahbMem, .-H264_ArrangeVahbMem
	.align	2
	.global	RepairList
	.type	RepairList, %function
RepairList:
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
	subs	r4, r0, #0
	beq	.L728
	add	r3, r4, #20480
	ldrb	r2, [r3, #208]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L705
	bcc	.L719
	cmp	r2, #2
	bne	.L729
.L720:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L729:
	ldr	r1, .L733
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L719:
	mov	r6, #1
.L706:
	add	lr, r4, #20480
	add	ip, r4, #26880
	add	lr, lr, #244
	mov	r5, #0
	add	ip, ip, #244
	add	r7, r4, #57344
	ldr	r3, [lr, #4]!
	mov	r2, r5
	mov	r8, #1
	cmp	r3, #0
	beq	.L707
.L731:
	ldr	r10, [ip]
	cmp	r10, #0
	bne	.L721
	mov	r0, ip
	mov	r1, r10
	b	.L709
.L710:
	ldr	r9, [r0, #4]!
	cmp	r9, #0
	bne	.L708
.L709:
	add	r1, r1, #1
	cmp	r1, r3
	bne	.L710
	ldr	r1, [r4]
	ldr	r1, [r1, #24]
	cmp	r1, #2
	bne	.L730
	ldr	r5, [r7, #3984]
	add	r5, r5, #704
.L712:
	mov	r9, r10
	mov	r0, ip
	mov	r1, #0
	b	.L718
.L714:
	ldr	r9, [r0, #4]!
.L718:
	add	r1, r1, #1
	cmp	r9, #0
	streq	r5, [r0]
	cmp	r1, r3
	bne	.L714
	add	r2, r2, #1
	add	ip, ip, #132
	cmp	r6, r2
	bls	.L720
.L727:
	ldr	r3, [lr, #4]!
	cmp	r3, #0
	bne	.L731
.L707:
	ldr	r1, [r4]
	ldr	r1, [r1, #24]
	cmp	r1, #2
	bne	.L732
	add	r2, r2, #1
	str	r8, [lr]
	cmp	r6, r2
	ldr	r3, [r7, #3984]
	add	ip, ip, #132
	add	r3, r3, #704
	str	r3, [ip, #-132]
	bhi	.L727
	b	.L720
.L721:
	mov	r9, r10
.L708:
	mov	r5, r9
	b	.L712
.L705:
	mov	r6, #2
	b	.L706
.L732:
	ldr	r1, .L733+4
.L725:
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L730:
	mov	r2, r5
	mov	r3, #0
	ldr	r1, .L733+8
	b	.L725
.L728:
	movw	r3, #4333
	ldr	r2, .L733+12
	ldr	r1, .L733+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L734:
	.align	2
.L733:
	.word	.LC31
	.word	.LC33
	.word	.LC32
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	RepairList, .-RepairList
	.align	2
	.global	GetShortTermPicPoint
	.type	GetShortTermPicPoint, %function
GetShortTermPicPoint:
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
	add	r3, r0, #20480
	ldrb	r4, [r3, #209]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L736
	ldrb	r3, [r3, #210]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r4, #2
	moveq	r4, #1
.L736:
	add	r3, r0, #24576
	ldr	r5, [r3, #2144]
	cmp	r5, #0
	beq	.L744
	add	r3, r0, #26368
	mov	r2, #0
	add	r3, r3, #216
	b	.L741
.L754:
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L752
.L739:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L753
.L741:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L754
	ldrb	lr, [r0, #2]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L740
	ldr	ip, [r0, #744]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	beq	.L755
.L740:
	tst	lr, #2
	beq	.L739
	ldr	ip, [r0, #784]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L739
	ldr	ip, [r0, #792]
	cmp	ip, r1
	bne	.L739
	add	r0, r0, #784
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L752:
	ldr	ip, [r0, #704]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L739
	ldr	ip, [r0, #712]
	cmp	ip, r1
	bne	.L739
	add	r0, r0, #704
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L755:
	ldr	ip, [r0, #752]
	cmp	ip, r1
	bne	.L740
	add	r0, r0, #744
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L753:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L744:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetShortTermPicPoint, .-GetShortTermPicPoint
	.align	2
	.global	GetLongTermPicPoint
	.type	GetLongTermPicPoint, %function
GetLongTermPicPoint:
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
	add	r3, r0, #20480
	ldrb	r4, [r3, #209]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L757
	ldrb	r3, [r3, #210]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r4, #2
	moveq	r4, #1
.L757:
	add	r3, r0, #24576
	ldr	r5, [r3, #2148]
	cmp	r5, #0
	beq	.L765
	add	r3, r0, #26624
	mov	r2, #0
	add	r3, r3, #24
	b	.L762
.L775:
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L773
.L760:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L774
.L762:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L775
	ldrb	lr, [r0, #2]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L761
	ldr	ip, [r0, #744]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	beq	.L776
.L761:
	tst	lr, #2
	beq	.L760
	ldr	ip, [r0, #784]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L760
	ldr	ip, [r0, #788]
	cmp	ip, r1
	bne	.L760
	add	r0, r0, #784
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L773:
	ldr	ip, [r0, #704]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L760
	ldr	ip, [r0, #708]
	cmp	ip, r1
	bne	.L760
	add	r0, r0, #704
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L776:
	ldr	ip, [r0, #748]
	cmp	ip, r1
	bne	.L761
	add	r0, r0, #744
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L774:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L765:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetLongTermPicPoint, .-GetLongTermPicPoint
	.align	2
	.global	ReorderSTList
	.type	ReorderSTList, %function
ReorderSTList:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, [fp, #4]
	mov	r4, r1
	mov	r1, r3
	mov	r7, r2
	mov	r5, r3
	bl	GetShortTermPicPoint
	ldr	lr, [r6]
	add	r2, r7, #1
	cmp	r2, lr
	ble	.L778
	add	ip, r4, r2, lsl #2
	mov	r1, r2
.L779:
	ldr	r3, [ip, #-4]!
	sub	r1, r1, #1
	str	r3, [ip, #4]
	ldr	lr, [r6]
	cmp	lr, r1
	blt	.L779
.L778:
	add	r3, lr, #1
	str	r3, [r6]
	str	r0, [r4, lr, asl #2]
	ldr	r0, [r6]
	cmp	r2, r0
	ldmltfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r2, r7, #2
	add	r3, r4, r0, lsl #2
	mov	ip, r0
.L783:
	ldr	r1, [r3], #4
	add	r0, r0, #1
	cmp	r1, #0
	beq	.L781
	ldrb	lr, [r1, #1]	@ zero_extendqisi2
	cmp	lr, #0
	bne	.L782
	ldr	lr, [r1, #8]
	cmp	lr, r5
	beq	.L781
.L782:
	str	r1, [r4, ip, asl #2]
	add	ip, ip, #1
.L781:
	cmp	r0, r2
	bne	.L783
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ReorderSTList, .-ReorderSTList
	.align	2
	.global	ReorderLTList
	.type	ReorderLTList, %function
ReorderLTList:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, [fp, #4]
	mov	r4, r1
	mov	r1, r3
	mov	r7, r2
	mov	r5, r3
	bl	GetLongTermPicPoint
	ldr	lr, [r6]
	add	r2, r7, #1
	cmp	r2, lr
	ble	.L791
	add	ip, r4, r2, lsl #2
	mov	r1, r2
.L792:
	ldr	r3, [ip, #-4]!
	sub	r1, r1, #1
	str	r3, [ip, #4]
	ldr	lr, [r6]
	cmp	lr, r1
	blt	.L792
.L791:
	add	r3, lr, #1
	str	r3, [r6]
	str	r0, [r4, lr, asl #2]
	ldr	r0, [r6]
	cmp	r2, r0
	ldmltfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r2, r7, #2
	add	r3, r4, r0, lsl #2
	mov	ip, r0
.L796:
	ldr	r1, [r3], #4
	add	r0, r0, #1
	cmp	r1, #0
	beq	.L794
	ldrb	lr, [r1, #1]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L795
	ldr	lr, [r1, #4]
	cmp	lr, r5
	beq	.L794
.L795:
	str	r1, [r4, ip, asl #2]
	add	ip, ip, #1
.L794:
	cmp	r0, r2
	bne	.L796
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ReorderLTList, .-ReorderLTList
	.align	2
	.global	ReorderRefPiclist
	.type	ReorderRefPiclist, %function
ReorderRefPiclist:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 24
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
	add	r2, r0, #20480
	str	r1, [fp, #-56]
	mov	r9, r3
	ldrb	r1, [r2, #209]	@ zero_extendqisi2
	mov	r3, #0
	mov	r8, r0
	str	r3, [fp, #-48]
	cmp	r1, r3
	ldr	r7, [fp, #4]
	add	r3, r0, #12288
	ldr	r1, [r2, #216]
	mov	lr, #2208
	beq	.L807
	ldr	r0, [r2, #224]
	mov	ip, #4000
	ldr	r2, [r3, #1304]
	ldr	r3, [r3, #1300]
	mov	r0, r0, asl #1
	mla	r2, lr, r1, r2
	mov	r1, #2
	add	r0, r0, #1
	str	r0, [fp, #-64]
	ldr	r2, [r2, #28]
	mla	r3, ip, r2, r3
	ldr	r3, [r3, #2196]
	add	r3, r3, #4
	mov	r3, r1, asl r3
	str	r3, [fp, #-60]
.L817:
	adds	r10, r9, #2
	beq	.L806
	ldr	r3, [r7]
	cmp	r3, #3
	beq	.L806
	ldr	r6, [fp, #8]
	mov	r4, #0
	ldr	r5, [fp, #-64]
	b	.L810
.L811:
	ldr	r3, [fp, #12]
	sub	r1, fp, #48
	mov	r2, r9
	mov	r0, r8
	ldr	r3, [r3, r4, asl #2]
	add	r4, r4, #1
	str	r1, [sp]
	ldr	r1, [fp, #-56]
	bl	ReorderLTList
	cmp	r4, r10
	beq	.L806
.L816:
	ldr	r3, [r7, #4]!
	add	r6, r6, #4
	cmp	r3, #3
	beq	.L806
.L810:
	cmp	r3, #1
	bhi	.L811
	cmp	r3, #0
	ldr	r3, [r6]
	bne	.L812
	mvn	r3, r3
	adds	r5, r5, r3
	ldrmi	r3, [fp, #-60]
	addmi	r5, r5, r3
.L813:
	ldr	r3, [fp, #-64]
	sub	r2, fp, #48
	ldr	r1, [fp, #-56]
	mov	r0, r8
	cmp	r3, r5
	str	r2, [sp]
	add	r4, r4, #1
	mov	r2, r9
	ldrlt	r3, [fp, #-60]
	movge	r3, r5
	rsblt	r3, r3, r5
	bl	ReorderSTList
	cmp	r4, r10
	bne	.L816
.L806:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L812:
	add	r3, r3, #1
	add	r5, r5, r3
	ldr	r3, [fp, #-60]
	cmp	r3, r5
	rsble	r5, r3, r5
	b	.L813
.L807:
	ldr	r2, [r2, #224]
	mov	ip, #4000
	mov	r0, #1
	str	r2, [fp, #-64]
	ldr	r2, [r3, #1304]
	ldr	r3, [r3, #1300]
	mla	r2, lr, r1, r2
	ldr	r2, [r2, #28]
	mla	r3, ip, r2, r3
	ldr	r3, [r3, #2196]
	add	r3, r3, #4
	mov	r3, r0, asl r3
	str	r3, [fp, #-60]
	b	.L817
	UNWIND(.fnend)
	.size	ReorderRefPiclist, .-ReorderRefPiclist
	.align	2
	.global	ReorderListX
	.type	ReorderListX, %function
ReorderListX:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r4, r0, #20480
	mov	r5, r0
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L825
	add	r6, r0, #16384
	ldrb	r2, [r6, #3512]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L837
.L828:
	cmp	r3, #1
	ldr	r3, [r4, #260]
	add	r3, r3, #1
	str	r3, [r4, #248]
	bne	.L825
	ldrb	r3, [r6, #3513]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L838
.L830:
	ldr	r3, [r4, #264]
	add	r3, r3, #1
	str	r3, [r4, #252]
.L825:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L837:
	add	r1, r0, #19968
	ldr	r3, [r4, #260]
	add	r2, r0, #20224
	add	ip, r0, #19712
	add	r1, r1, #196
	str	r1, [sp, #4]
	add	r1, r0, #26880
	add	r2, r2, #204
	add	ip, ip, #188
	str	r2, [sp, #8]
	str	ip, [sp]
	add	r2, r4, #248
	add	r1, r1, #244
	bl	ReorderRefPiclist
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	b	.L828
.L838:
	add	lr, r5, #20480
	add	ip, r5, #20224
	add	r0, r5, #19968
	add	r1, r5, #27136
	ldr	r3, [r4, #264]
	mov	r2, lr
	add	ip, ip, #72
	add	lr, lr, #76
	add	r0, r0, #64
	str	lr, [sp, #8]
	stmia	sp, {r0, ip}
	add	r2, r2, #252
	add	r1, r1, #120
	mov	r0, r5
	bl	ReorderRefPiclist
	b	.L830
	UNWIND(.fnend)
	.size	ReorderListX, .-ReorderListX
	.align	2
	.global	GenPiclistfromFrmlist
	.type	GenPiclistfromFrmlist, %function
GenPiclistfromFrmlist:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 8
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
	cmp	r2, #31
	ldr	r6, [fp, #8]
	mov	r7, r1
	ldr	lr, .L902
	movcc	r4, r2
	ldr	ip, .L902+4
	movcs	r4, #31
	cmp	r6, #0
	str	r3, [fp, #-52]
	movne	r6, lr
	moveq	r6, ip
	cmp	r0, #1
	moveq	r5, #0
	moveq	r10, r5
	beq	.L842
	cmp	r0, #2
	moveq	r5, #0
	moveq	r10, r5
	bne	.L850
.L851:
	cmp	r10, r4
	movcs	r3, #0
	movcc	r3, #1
	cmp	r5, r4
	str	r3, [fp, #-48]
	movcs	r2, #0
	movcc	r2, #1
	orrs	r3, r2, r3
	beq	.L850
	cmp	r2, #0
	beq	.L856
	add	r8, r7, r5, lsl #2
	b	.L855
.L852:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L856
.L855:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	tst	ip, #2
	beq	.L852
	add	r0, r0, #784
	blx	r6
	cmp	r0, #0
	beq	.L852
	ldr	r3, [fp, #4]
	add	r5, r5, #1
	ldr	r2, [r9]
	ldr	r0, [r3]
	add	r2, r2, #784
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L856:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r10, lsl #2
	bne	.L858
	b	.L851
.L857:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L851
.L858:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	tst	r1, #1
	beq	.L857
	add	r0, r0, #744
	blx	r6
	cmp	r0, #0
	beq	.L857
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r9]
	ldr	r1, [r3]
	add	r2, r2, #744
	ldr	r3, [fp, #-52]
	str	r2, [r3, r1, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
	b	.L851
.L901:
	add	r0, r0, #744
	blx	r6
	cmp	r0, #0
	beq	.L843
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r8]
	ldr	r0, [r3]
	add	r2, r2, #744
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L847:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r5, lsl #2
	bne	.L849
	b	.L842
.L848:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L842
.L849:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	tst	r1, #2
	beq	.L848
	add	r0, r0, #784
	blx	r6
	cmp	r0, #0
	beq	.L848
	ldr	r3, [fp, #4]
	add	r5, r5, #1
	ldr	r2, [r9]
	ldr	r1, [r3]
	add	r2, r2, #784
	ldr	r3, [fp, #-52]
	str	r2, [r3, r1, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L842:
	cmp	r10, r4
	movcs	r2, #0
	movcc	r2, #1
	cmp	r5, r4
	movcs	r3, #0
	movcc	r3, #1
	str	r3, [fp, #-48]
	orrs	r3, r3, r2
	beq	.L850
	cmp	r2, #0
	beq	.L847
	add	r9, r7, r10, lsl #2
	b	.L846
.L843:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L847
.L846:
	mov	r8, r9
	ldr	r0, [r9], #4
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	tst	ip, #1
	beq	.L843
	b	.L901
.L850:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L903:
	.align	2
.L902:
	.word	IsLTRefFlg
	.word	IsSTRefFlg
	UNWIND(.fnend)
	.size	GenPiclistfromFrmlist, .-GenPiclistfromFrmlist
	.align	2
	.global	InitListX
	.type	InitListX, %function
InitListX:
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
	subs	r4, r0, #0
	beq	.L1030
	add	r7, r4, #20480
	add	r9, r4, #57344
	ldrb	r3, [r7, #208]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1031
	ldrb	r5, [r9, #3331]	@ zero_extendqisi2
	add	r3, r4, #24576
	str	r3, [fp, #-240]
	cmp	r5, #0
	ldr	r10, [r3, #2144]
	beq	.L927
	cmp	r10, #0
	beq	.L1032
	add	r6, r4, #26368
	mov	r5, #0
	add	r6, r6, #212
	mov	r3, r5
	mov	r1, r6
.L946:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L945
	sub	r0, fp, #44
	ldr	ip, [r9, #4004]
	add	lr, r0, r5, lsl #2
	ldr	r0, [r2, #672]
	cmp	ip, r0
	strge	r2, [lr, #-192]
	addge	r5, r5, #1
.L945:
	cmp	r3, r10
	bne	.L946
	sub	r3, fp, #236
	mov	r2, #4
	str	r3, [fp, #-244]
	mov	r1, r5
	mov	r0, r3
	ldr	r3, .L1039
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r8, [r3, #2144]
	cmp	r8, #0
	beq	.L1027
.L971:
	mov	r10, r5
	mov	r3, #0
.L949:
	ldr	r2, [r6, #4]!
	add	r3, r3, #1
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L948
	sub	r1, fp, #44
	ldr	r0, [r9, #4004]
	add	ip, r1, r10, lsl #2
	ldr	r1, [r2, #672]
	cmp	r0, r1
	strlt	r2, [ip, #-192]
	addlt	r10, r10, #1
.L948:
	cmp	r3, r8
	bne	.L949
	ldr	r2, [fp, #-244]
	rsb	r8, r5, r10
	mov	r3, r5, asl #2
	str	r3, [fp, #-248]
	add	r0, r2, r3
	mov	r1, r8
	ldr	r3, .L1039+4
	mov	r2, #4
	bl	qsort
	cmp	r5, #0
	subeq	r6, fp, #172
	beq	.L950
.L968:
	sub	r6, fp, #172
	ldr	r2, [fp, #-244]
	add	r8, r6, r8, lsl #2
	mov	r3, #0
.L951:
	add	r3, r3, #1
	ldr	r1, [r2], #4
	cmp	r3, r5
	str	r1, [r8], #4
	bcc	.L951
.L950:
	cmp	r10, r5
	bls	.L952
	ldr	r3, [fp, #-244]
	ldr	r2, [fp, #-248]
	add	r2, r3, r2
	mov	r3, r6
.L953:
	add	r5, r5, #1
	ldr	r1, [r2], #4
	cmp	r5, r10
	str	r1, [r3], #4
	bne	.L953
.L952:
	add	r2, r4, #20480
	add	r3, r4, #26880
	add	r2, r2, #248
	mov	r5, #0
	add	r3, r3, #244
	str	r5, [r7, #248]
	str	r5, [r7, #252]
	mov	ip, r2
	ldrb	r0, [r9, #3331]	@ zero_extendqisi2
	add	r8, r4, #27136
	ldr	r1, [fp, #-244]
	add	r8, r8, #120
	str	r2, [fp, #-244]
	mov	r2, r10
	str	ip, [sp]
	str	r5, [sp, #4]
	str	r3, [fp, #-248]
	bl	GenPiclistfromFrmlist
	add	r3, r4, #20480
	ldrb	r0, [r9, #3331]	@ zero_extendqisi2
	mov	r2, r10
	mov	r1, r6
	mov	ip, r3
	str	r5, [sp, #4]
	add	ip, ip, #252
	mov	r3, r8
	str	ip, [sp]
	str	ip, [fp, #-252]
	bl	GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	ldr	r6, [r3, #2148]
	cmp	r6, r5
	subeq	r10, fp, #108
	beq	.L954
	add	r3, r4, #26624
	sub	r10, fp, #108
	add	r3, r3, #20
	mov	r2, r10
.L955:
	add	r5, r5, #1
	ldr	r1, [r3, #4]!
	cmp	r5, r6
	str	r1, [r2], #4
	bne	.L955
.L954:
	ldr	r3, .L1039+8
	mov	r2, #4
	mov	r1, r6
	mov	r0, r10
	bl	qsort
	ldr	r3, [fp, #-244]
	ldrb	r0, [r9, #3331]	@ zero_extendqisi2
	mov	r5, #1
	mov	r2, r6
	mov	r1, r10
	stmia	sp, {r3, r5}
	ldr	r3, [fp, #-248]
	bl	GenPiclistfromFrmlist
	ldr	r2, [fp, #-252]
	ldrb	r0, [r9, #3331]	@ zero_extendqisi2
	mov	r3, r8
	mov	r1, r10
	str	r5, [sp, #4]
	str	r2, [sp]
	mov	r2, r6
	bl	GenPiclistfromFrmlist
	ldr	r2, [r7, #248]
	ldr	r3, [r7, #252]
	rsb	r1, r3, r2
	clz	r1, r1
	mov	r1, r1, lsr #5
.L944:
	cmp	r2, #1
	movls	r1, #0
	andhi	r1, r1, #1
	cmp	r1, #0
	beq	.L956
	cmp	r2, #0
	ldr	r1, [fp, #-240]
	beq	.L957
	ldr	r6, [r1, #2548]
	ldr	r1, [r1, #2680]
	cmp	r6, r1
	bne	.L956
	add	r0, r4, #27136
	ldr	ip, [fp, #-248]
	add	r0, r0, #120
	mov	r1, #0
	b	.L958
.L959:
	ldr	r5, [ip, #4]!
	ldr	lr, [r0, #4]!
	cmp	r5, lr
	bne	.L956
.L958:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L959
.L960:
	ldr	r0, [fp, #-240]
	ldr	r1, [r0, #2684]
	str	r6, [r0, #2684]
	str	r1, [r0, #2680]
.L956:
	orrs	r1, r2, r3
	beq	.L1033
.L922:
	ldr	r0, [r7, #260]
	ldr	r1, [r7, #264]
	add	r0, r0, #1
	cmp	r2, r0
	add	r1, r1, #1
	movcs	r2, r0
	cmp	r3, r1
	str	r2, [r7, #248]
	movcs	r3, r1
	cmp	r2, #32
	str	r3, [r7, #252]
	bhi	.L965
	add	r2, r2, #6720
	add	r1, r4, #27136
	add	r2, r2, #60
	add	r1, r1, #116
	mov	r0, #0
	add	r2, r4, r2, lsl #2
.L964:
	str	r0, [r2, #4]!
	cmp	r2, r1
	bne	.L964
.L965:
	cmp	r3, #32
	bhi	.L963
	add	r3, r3, #6784
	add	r2, r4, #27136
	add	r3, r3, #29
	add	r2, r2, #248
	mov	r1, #0
	add	r4, r4, r3, lsl #2
.L966:
	str	r1, [r4, #4]!
	cmp	r4, r2
	bne	.L966
.L963:
	mov	r0, #0
.L1015:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1031:
	ldrb	r6, [r9, #3331]	@ zero_extendqisi2
	cmp	r6, #0
	beq	.L908
	add	r2, r4, #24576
	str	r2, [fp, #-240]
	ldr	lr, [r2, #2144]
	cmp	lr, #0
	moveq	r6, lr
	beq	.L910
	add	r1, r4, #26368
	mov	r6, r3
	add	r1, r1, #212
.L919:
	ldr	r2, [r1, #4]!
	sub	r0, fp, #44
	add	ip, r0, r6, lsl #2
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	strne	r2, [ip, #-192]
	addne	r6, r6, #1
	cmp	r3, lr
	bne	.L919
.L910:
	mov	r1, r6
	ldr	r3, .L1039+12
	mov	r2, #4
	sub	r0, fp, #236
	bl	qsort
	add	r8, r4, #20480
	add	r3, r4, #26880
	mov	r5, #0
	add	r3, r3, #244
	str	r5, [r7, #248]
	mov	r2, r6
	ldrb	r0, [r9, #3331]	@ zero_extendqisi2
	sub	r1, fp, #236
	str	r5, [sp, #4]
	add	r8, r8, #248
	str	r8, [sp]
	str	r3, [fp, #-244]
	bl	GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	ldr	r6, [r3, #2148]
	cmp	r6, r5
	subeq	r10, fp, #108
	beq	.L920
	add	r3, r4, #26624
	sub	r10, fp, #108
	add	r3, r3, #20
	mov	r2, r10
.L921:
	add	r5, r5, #1
	ldr	r1, [r3, #4]!
	cmp	r5, r6
	str	r1, [r2], #4
	bne	.L921
.L920:
	ldr	r3, .L1039+8
	mov	r2, #4
	mov	r1, r6
	mov	r0, r10
	bl	qsort
	ldrb	r0, [r9, #3331]	@ zero_extendqisi2
	mov	r2, r6
	mov	ip, #1
	ldr	r3, [fp, #-244]
	mov	r1, r10
	str	r8, [sp]
	str	ip, [sp, #4]
	bl	GenPiclistfromFrmlist
	ldr	r2, [r7, #248]
.L917:
	cmp	r2, #0
	mov	r3, #0
	str	r3, [r7, #252]
	bne	.L922
	ldr	r3, [r4]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L923
	ldrb	r3, [r9, #3331]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1034
	cmp	r3, #1
	ldr	r2, [fp, #-240]
	ldr	r3, [r9, #3984]
	addeq	r3, r3, #744
	addne	r3, r3, #784
	str	r3, [r2, #2548]
.L925:
	mov	r3, #0
	mov	r2, #1
	b	.L922
.L908:
	add	r3, r4, #24576
	str	r3, [fp, #-240]
	ldr	ip, [r3, #2144]
	cmp	ip, #0
	beq	.L973
	add	r1, r4, #26368
	mov	r3, r6
	add	r1, r1, #212
	b	.L913
.L912:
	cmp	r3, ip
	beq	.L911
.L913:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L912
	ldr	r0, [r2, #704]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #65536
	bne	.L912
	add	r0, r6, #6720
	cmp	r3, ip
	add	r0, r0, #60
	add	r2, r2, #704
	add	r6, r6, #1
	add	r0, r4, r0, lsl #2
	str	r2, [r0, #4]
	bne	.L913
.L911:
	add	r0, r4, #26880
	ldr	r3, .L1039+16
	mov	r1, r6
	add	r0, r0, #244
	mov	r2, #4
	bl	qsort
	ldr	r3, [fp, #-240]
	str	r6, [r7, #248]
	ldr	r1, [r3, #2148]
	cmp	r1, #0
	beq	.L974
	add	r0, r4, #26624
	mov	r5, r6
	add	r0, r0, #20
	mov	r3, #0
	b	.L916
.L915:
	cmp	r3, r1
	beq	.L1035
.L916:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #2]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L915
	ldr	ip, [r2, #704]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L915
	add	ip, r5, #6720
	cmp	r3, r1
	add	ip, ip, #60
	add	r2, r2, #704
	add	r5, r5, #1
	add	ip, r4, ip, lsl #2
	str	r2, [ip, #4]
	bne	.L916
.L1035:
	rsb	r1, r6, r5
.L914:
	add	r0, r4, r6, lsl #2
	mov	r2, #4
	add	r0, r0, #26880
	ldr	r3, .L1039+20
	add	r0, r0, #244
	bl	qsort
	str	r5, [r7, #248]
	mov	r2, r5
	b	.L917
.L927:
	cmp	r10, #0
	beq	.L930
	add	r6, r4, #26368
	mov	r3, r5
	add	r6, r6, #212
	mov	r1, r6
	b	.L932
.L931:
	cmp	r3, r10
	beq	.L1036
.L932:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L931
	add	r0, r5, #6720
	ldr	ip, [r2, #716]
	add	r0, r0, #60
	ldr	lr, [r9, #4008]
	add	r2, r2, #704
	add	r0, r4, r0, lsl #2
	cmp	lr, ip
	addge	r5, r5, #1
	strge	r2, [r0, #4]
	cmp	r3, r10
	bne	.L932
.L1036:
	add	r3, r4, #26880
	mov	r1, r5
	mov	r2, r3
	add	r2, r2, #244
	ldr	r3, .L1039+24
	mov	r0, r2
	str	r2, [fp, #-248]
	mov	r2, #4
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r8, [r3, #2144]
	cmp	r8, #0
	beq	.L1026
.L969:
	mov	r10, r5
	mov	r3, #0
	b	.L935
.L934:
	cmp	r3, r8
	beq	.L1037
.L935:
	ldr	r2, [r6, #4]!
	add	r3, r3, #1
	ldrb	r1, [r2, #2]	@ zero_extendqisi2
	cmp	r1, #3
	bne	.L934
	add	r1, r10, #6720
	ldr	r0, [r2, #716]
	add	r1, r1, #60
	ldr	ip, [r9, #4008]
	add	r2, r2, #704
	add	r1, r4, r1, lsl #2
	cmp	ip, r0
	addlt	r10, r10, #1
	strlt	r2, [r1, #4]
	cmp	r3, r8
	bne	.L935
.L1037:
	add	r6, r5, #6720
	rsb	r8, r5, r10
	add	r6, r6, #60
	mov	r2, #4
	ldr	r3, .L1039+28
	mov	r1, r8
	add	r0, r4, r6, lsl #2
	add	r9, r4, r10, lsl #2
	add	r0, r0, r2
	add	r9, r9, #26880
	bl	qsort
	cmp	r5, #0
	add	r9, r9, #244
	beq	.L937
.L967:
	add	r8, r8, #6784
	add	r2, r4, #26880
	add	r8, r8, #29
	add	r2, r2, #240
	mov	r3, #0
	add	r8, r4, r8, lsl #2
.L938:
	add	r3, r3, #1
	ldr	r1, [r2, #4]!
	cmp	r3, r5
	str	r1, [r8, #4]!
	bcc	.L938
.L937:
	cmp	r10, r5
	bls	.L939
	add	r3, r4, #27136
	add	r6, r4, r6, lsl #2
	add	r3, r3, #116
.L940:
	add	r5, r5, #1
	ldr	r2, [r6, #4]!
	cmp	r5, r10
	str	r2, [r3, #4]!
	bne	.L940
.L939:
	ldr	r3, [fp, #-240]
	str	r10, [r7, #252]
	str	r10, [r7, #248]
	ldr	r1, [r3, #2148]
	cmp	r1, #0
	beq	.L976
	add	r0, r4, #26624
	mov	r5, r10
	add	r0, r0, #20
	mov	r3, #0
	b	.L943
.L942:
	cmp	r3, r1
	beq	.L1038
.L943:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #1]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L942
	ldrb	ip, [r2, #705]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L942
	add	ip, r4, r5, lsl #2
	cmp	r3, r1
	add	ip, ip, #24576
	add	r2, r2, #704
	add	r5, r5, #1
	str	r2, [ip, #2548]
	str	r2, [ip, #2680]
	bne	.L943
.L1038:
	rsb	r1, r10, r5
.L941:
	mov	r0, r9
	ldr	r3, .L1039+20
	mov	r2, #4
	bl	qsort
	ldr	r0, [r7, #248]
	ldr	r3, .L1039+20
	mov	r2, #4
	rsb	r1, r0, r5
	add	r0, r4, r0, lsl #2
	add	r0, r0, #27136
	add	r0, r0, #120
	bl	qsort
	mov	r3, r5
	str	r5, [r7, #252]
	mov	r2, r5
	str	r5, [r7, #248]
	mov	r1, #1
	b	.L944
.L1034:
	ldr	r2, [fp, #-240]
	ldr	r3, [r9, #3984]
	add	r3, r3, #704
	str	r3, [r2, #2548]
	b	.L925
.L1033:
	ldr	r1, .L1039+32
.L1022:
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	b	.L1015
.L957:
	ldr	r6, [r1, #2680]
	b	.L960
.L973:
	mov	r6, ip
	b	.L911
.L1026:
	add	r6, r5, #6720
	mov	r2, #4
	add	r6, r6, #60
	ldr	r3, .L1039+28
	mov	r1, r8
	add	r9, r4, r6, lsl #2
	add	r9, r9, r2
	mov	r0, r9
	bl	qsort
	subs	r10, r5, #0
	bne	.L967
	b	.L939
.L976:
	mov	r5, r10
	b	.L941
.L1032:
	sub	r3, fp, #236
	mov	r2, #4
	str	r3, [fp, #-244]
	mov	r1, r10
	mov	r0, r3
	ldr	r3, .L1039
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r8, [r3, #2144]
	cmp	r8, #0
	addne	r6, r4, #26368
	movne	r5, r10
	addne	r6, r6, #212
	bne	.L971
	ldr	r3, .L1039+4
	mov	r2, #4
	mov	r1, r8
	ldr	r0, [fp, #-244]
	mov	r10, r8
	bl	qsort
.L1023:
	sub	r6, fp, #172
	b	.L952
.L1027:
	mov	r3, r5, asl #2
	ldr	r1, [fp, #-244]
	str	r3, [fp, #-248]
	mov	r2, r3
	ldr	r3, .L1039+4
	add	r0, r1, r2
	mov	r2, #4
	mov	r1, r8
	bl	qsort
	subs	r10, r5, #0
	bne	.L968
	b	.L1023
.L974:
	mov	r5, r6
	b	.L914
.L930:
	add	r3, r4, #26880
	mov	r1, r10
	mov	r2, r3
	add	r2, r2, #244
	ldr	r3, .L1039+24
	mov	r0, r2
	str	r2, [fp, #-248]
	mov	r2, #4
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r8, [r3, #2144]
	cmp	r8, #0
	addne	r6, r4, #26368
	movne	r5, r10
	addne	r6, r6, #212
	bne	.L969
	ldr	r9, [fp, #-248]
	mov	r2, #4
	ldr	r3, .L1039+28
	mov	r1, r8
	mov	r10, r8
	mov	r0, r9
	bl	qsort
	b	.L939
.L923:
	ldr	r1, .L1039+36
	b	.L1022
.L1030:
	movw	r3, #5091
	ldr	r2, .L1039+40
	ldr	r1, .L1039+44
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1015
.L1040:
	.align	2
.L1039:
	.word	compare_fs_by_poc_desc
	.word	compare_fs_by_poc_asc
	.word	compare_fs_by_lt_pic_idx_asc
	.word	compare_fs_by_frame_num_desc
	.word	compare_pic_by_pic_num_desc
	.word	compare_pic_by_lt_pic_num_asc
	.word	compare_pic_by_poc_desc
	.word	compare_pic_by_poc_asc
	.word	.LC35
	.word	.LC34
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	InitListX, .-InitListX
	.align	2
	.global	DumpList
	.type	DumpList, %function
DumpList:
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
	ldr	r3, .L1043
	ldr	r3, [r3]
	tst	r3, #8192
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DumpList.part.10
.L1044:
	.align	2
.L1043:
	.word	g_PrintEnable
	UNWIND(.fnend)
	.size	DumpList, .-DumpList
	.align	2
	.global	FindNearestPOCPicId
	.type	FindNearestPOCPicId, %function
FindNearestPOCPicId:
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
	add	r3, r0, #24576
	ldr	r4, [r3, #2140]
	cmp	r4, #0
	beq	.L1050
	ldr	r3, [r3, #1944]
	add	r2, r0, #57344
	ldr	r5, [r2, #4004]
	ldr	lr, [r3, #672]
	rsb	lr, lr, r5
	cmp	lr, #0
	rsblt	lr, lr, #0
	cmp	r4, #1
	bls	.L1051
	add	r1, r0, #26368
	mov	r2, #1
	add	r1, r1, #152
	mov	r0, #0
.L1049:
	ldr	ip, [r1, #4]!
	add	r2, r2, #1
	ldr	r3, [ip, #672]
	rsb	r3, r3, r5
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, lr
	ldrlt	r0, [ip, #164]
	movlt	lr, r3
	cmp	r2, r4
	bne	.L1049
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1051:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1050:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	FindNearestPOCPicId, .-FindNearestPOCPicId
	.align	2
	.global	FindMinRefIdx
	.type	FindMinRefIdx, %function
FindMinRefIdx:
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
	add	r3, r0, #20480
	ldrb	r2, [r3, #208]	@ zero_extendqisi2
	cmp	r2, #2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	add	r2, r0, #57344
	add	r5, r0, #26880
	ldrb	ip, [r2, #3331]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1083
	ldr	lr, [r3, #248]
	mov	r4, r5
	mov	r6, r5
	mov	r7, ip
	cmp	lr, #0
	add	r5, r5, #116
	add	r4, r4, #120
	add	r6, r6, #240
	beq	.L1061
.L1085:
	mov	r2, r6
	mov	r0, #32
	mov	r3, #0
	b	.L1059
.L1058:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1084
.L1059:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #696]
	cmp	r1, ip
	bne	.L1058
	cmp	r0, r3
	movcs	r0, r3
	add	r3, r3, #1
	cmp	r3, lr
	str	r0, [r4, #-4]
	str	r0, [r5, #4]
	bne	.L1059
.L1084:
	cmp	r0, #31
	bhi	.L1061
.L1060:
	add	ip, ip, #1
	add	r5, r5, #8
	cmp	ip, #16
	add	r4, r4, #8
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	lr, #0
	bne	.L1085
.L1061:
	str	r7, [r4, #-4]
	str	r7, [r5, #4]
	b	.L1060
.L1083:
	ldr	r4, [r3, #248]
	mov	ip, #0
	mov	r6, r5
	mov	r7, ip
	cmp	r4, #0
	add	r5, r5, #116
	add	r6, r6, #240
	beq	.L1065
.L1087:
	mov	r1, r6
	mov	lr, #32
	mov	r2, #0
	b	.L1063
.L1062:
	add	r2, r2, #1
	cmp	r2, r4
	beq	.L1086
.L1063:
	ldr	r3, [r1, #4]!
	ldr	r8, [r3, #36]
	ldrb	r0, [r3]	@ zero_extendqisi2
	ldr	r3, [r8, #696]
	mov	r3, r3, asl #1
	cmp	r0, #2
	orreq	r3, r3, #1
	cmp	r3, ip
	bne	.L1062
	cmp	lr, r2
	movcs	lr, r2
	add	r2, r2, #1
	cmp	r2, r4
	str	lr, [r5]
	bne	.L1063
.L1086:
	cmp	lr, #31
	bhi	.L1065
.L1064:
	add	ip, ip, #1
	add	r5, r5, #4
	cmp	ip, #32
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	r4, #0
	bne	.L1087
.L1065:
	str	r7, [r5]
	b	.L1064
	UNWIND(.fnend)
	.size	FindMinRefIdx, .-FindMinRefIdx
	.align	2
	.global	UvmosDeleteList
	.type	UvmosDeleteList, %function
UvmosDeleteList:
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
	add	r3, r0, #20480
	mov	r4, r0
	ldrb	r2, [r3, #208]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1090
	bcc	.L1097
	cmp	r2, #2
	bne	.L1107
.L1098:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1107:
	ldr	r1, .L1109
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1097:
	mov	r8, #1
.L1091:
	add	r6, r4, #20480
	add	r5, r4, #26880
	add	r6, r6, #244
	add	r5, r5, #240
	add	lr, r4, #61440
	mov	r7, #0
.L1095:
	ldr	ip, [r6, #4]!
	cmp	ip, #0
	movne	r1, r5
	movne	r3, #0
	beq	.L1096
.L1094:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	cmp	r2, #0
	beq	.L1093
	ldr	r0, [r2, #16]
	ldr	r2, [lr, #2672]
	cmp	r0, r2
	bls	.L1093
	ldr	r2, [r4]
	ldr	r2, [r2, #644]
	cmp	r2, #1
	beq	.L1108
.L1093:
	cmp	r3, ip
	bne	.L1094
.L1096:
	add	r7, r7, #1
	add	r5, r5, #132
	cmp	r7, r8
	bcc	.L1095
	b	.L1098
.L1108:
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1090:
	mov	r8, #2
	b	.L1091
.L1110:
	.align	2
.L1109:
	.word	.LC31
	UNWIND(.fnend)
	.size	UvmosDeleteList, .-UvmosDeleteList
	.align	2
	.global	DecList
	.type	DecList, %function
DecList:
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
	subs	r5, r0, #0
	beq	.L1128
	bl	FindNearestPOCPicId
	add	r6, r5, #20480
	mvn	r4, #0
	ldrb	r3, [r6, #208]	@ zero_extendqisi2
	str	r4, [r6, #1832]
	cmp	r3, #2
	str	r0, [r6, #1836]
	beq	.L1129
	mov	r0, r5
	bl	InitListX
	cmp	r0, #0
	bne	.L1130
	ldr	r4, .L1132
	mov	r0, #13
	ldr	r1, .L1132+4
	bl	dprint_vfmw
	ldr	r3, [r4]
	tst	r3, #8192
	bne	.L1131
.L1116:
	mov	r0, r5
	bl	ReorderListX
	mov	r0, r5
	bl	RepairList
	cmp	r0, #0
	bne	.L1121
	mov	r0, r5
	bl	FindMinRefIdx
	ldr	r3, [r5]
	ldr	r3, [r3, #644]
	cmp	r3, #1
	beq	.L1118
.L1122:
	add	r3, r5, #24576
	ldr	r3, [r3, #2548]
	cmp	r3, #0
	mvneq	r3, #0
	ldrne	r3, [r3, #36]
	ldrne	r3, [r3, #164]
.L1120:
	str	r3, [r6, #1832]
	mov	r0, #13
	ldr	r1, .L1132+8
	bl	dprint_vfmw
	ldr	r0, [r4]
	ands	r0, r0, #8192
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r5
	bl	DumpList.part.10
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1129:
	mov	r0, #0
	str	r0, [r6, #248]
	str	r0, [r6, #252]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1131:
	mov	r0, r5
	bl	DumpList.part.10
	b	.L1116
.L1118:
	mov	r0, r5
	bl	UvmosDeleteList
	cmp	r0, #0
	beq	.L1122
.L1121:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1130:
	ldr	r1, .L1132+12
	mov	r0, #13
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1128:
	movw	r3, #5609
	ldr	r2, .L1132+16
	ldr	r1, .L1132+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1133:
	.align	2
.L1132:
	.word	g_PrintEnable
	.word	.LC37
	.word	.LC38
	.word	.LC36
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	DecList, .-DecList
	.align	2
	.global	NoPicOut
	.type	NoPicOut, %function
NoPicOut:
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
	add	r4, r0, #61440
	ldr	ip, [r4, #1364]
	cmp	ip, #0
	addne	r3, r0, #27904
	movne	r2, #0
	addne	r3, r3, #164
	movne	lr, r2
	bne	.L1140
	b	.L1141
.L1149:
	ldrb	r1, [r3, #-672]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1138
	cmp	r2, ip
	add	r3, r3, #832
	beq	.L1141
.L1140:
	ldr	r1, [r3]
	add	r2, r2, #1
	cmp	r1, #1
	bne	.L1149
.L1138:
	cmp	r2, ip
	strb	lr, [r3, #-675]
	strb	lr, [r3, #-674]
	add	r3, r3, #832
	bne	.L1140
.L1141:
	ldr	r2, [r4, #1368]
	cmp	r2, #0
	beq	.L1150
	add	r0, r0, #62720
	mov	r3, #0
	add	r0, r0, #12
	mov	r1, r3
.L1142:
	add	r3, r3, #1
	str	r1, [r0, #4]!
	cmp	r3, r2
	bne	.L1142
	ldmfd	sp, {r4, fp, sp, pc}
.L1150:
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	NoPicOut, .-NoPicOut
	.align	2
	.global	GetBackPicFromVOQueue
	.type	GetBackPicFromVOQueue, %function
GetBackPicFromVOQueue:
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
	add	r5, r0, #61440
	mov	r9, r0
	ldr	r0, [r5, #2680]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L1168
.L1152:
	ldr	r3, [r5, #1364]
	cmp	r3, #0
	beq	.L1159
	add	r10, r9, #27904
	mov	r6, #0
	add	r10, r10, #72
	mov	r7, #0
	mov	r8, #0
.L1158:
	sub	r4, r10, #32
	mov	r3, #0
	strb	r3, [r10, #-583]
	strb	r3, [r10, #-582]
.L1157:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1156
	ldr	r0, [r5, #2680]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1156:
	cmp	r4, r10
	bne	.L1157
	ldr	r3, [r5, #1364]
	add	r8, r8, #1
	add	r10, r10, #832
	cmp	r3, r8
	bhi	.L1158
.L1159:
	ldr	r2, [r5, #1368]
	cmp	r2, #0
	beq	.L1169
	add	r9, r9, #62720
	mov	r3, #0
	add	r9, r9, #12
	mov	r1, r3
.L1160:
	add	r3, r3, #1
	str	r1, [r9, #4]!
	cmp	r3, r2
	bne	.L1160
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1168:
	add	r0, r9, #8
	bl	ResetVoQueue
	b	.L1152
.L1169:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetBackPicFromVOQueue, .-GetBackPicFromVOQueue
	.align	2
	.global	wait_vo
	.type	wait_vo, %function
wait_vo:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	wait_vo, .-wait_vo
	.align	2
	.global	GetReRangeFlag
	.type	GetReRangeFlag, %function
GetReRangeFlag:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	add	r6, r0, #12288
	add	r3, r0, #20480
	mov	r5, r0
	ldr	r0, [r6, #1304]
	mov	lr, #2208
	ldr	r3, [r3, #216]
	mov	r4, #4000
	ldr	r2, [r6, #1300]
	mov	r7, r1
	ldr	ip, [r6, #1276]
	mla	r3, lr, r3, r0
	ldr	r0, [r6, #1280]
	ldr	r3, [r3, #28]
	mla	r4, r4, r3, r2
	ldrb	r3, [r4, #18]	@ zero_extendqisi2
	ldr	r1, [r4, #3252]
	rsb	r3, r3, #2
	ldr	r2, [r4, #3248]
	mla	r3, r1, r3, r3
	add	r2, r2, #1
	cmp	r2, ip
	cmpeq	r3, r0
	movne	r1, #1
	moveq	r1, #0
	bne	.L1172
	add	lr, r5, #24576
	ldr	r8, [r4, #3272]
	ldr	lr, [lr, #2136]
	add	lr, lr, #1
	cmp	r8, lr
	moveq	r3, r1
	beq	.L1173
.L1172:
	ldr	r1, .L1177
	ldr	r8, [r1]
	cmp	r8, #0
	beq	.L1176
	add	r1, r5, #61440
	mov	r0, r0, asl #4
	mov	r2, r2, asl #4
	mov	r3, r3, asl #4
	mov	ip, ip, asl #4
	strh	r0, [fp, #-42]	@ movhi
	strh	r2, [fp, #-40]	@ movhi
	sub	r2, fp, #44
	strh	r3, [fp, #-38]	@ movhi
	mov	r3, #8
	ldr	r0, [r1, #2680]
	mov	r1, #2
	strh	ip, [fp, #-44]	@ movhi
	blx	r8
.L1176:
	ldr	lr, [r4, #3272]
	mov	r3, #1
.L1173:
	add	r5, r5, #16384
	ldr	r2, [r4, #36]
	ldr	ip, [r6, #1344]
	mov	r0, r3
	ldr	r1, [r5, #484]
	cmp	ip, r2
	cmpeq	r1, lr
	movne	r2, #1
	moveq	r2, #0
	orr	r3, r2, r3
	str	r3, [r7]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1178:
	.align	2
.L1177:
	.word	g_event_report
	UNWIND(.fnend)
	.size	GetReRangeFlag, .-GetReRangeFlag
	.align	2
	.global	DecPOC
	.type	DecPOC, %function
DecPOC:
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
	add	r2, r0, #12288
	add	r6, r0, #20480
	mov	r4, #2208
	mov	r5, #4000
	ldr	r1, [r6, #216]
	mov	ip, #1
	ldr	r3, [r2, #1304]
	ldr	lr, [r2, #1300]
	ldrb	r2, [r6, #211]	@ zero_extendqisi2
	mla	r3, r4, r1, r3
	sub	r2, r2, #5
	clz	r2, r2
	mov	r2, r2, lsr #5
	ldr	r3, [r3, #28]
	mla	r5, r5, r3, lr
	ldr	r1, [r5, #2200]
	ldr	r3, [r5, #2196]
	cmp	r1, ip
	ldr	lr, [r5, #2204]
	add	r3, r3, #4
	mov	r3, ip, asl r3
	beq	.L1181
	bcc	.L1182
	cmp	r1, #2
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r2, #0
	add	r4, r0, #16384
	bne	.L1237
	ldr	r1, [r4, #3444]
	cmp	r1, #0
	bne	.L1215
	ldr	r2, [r4, #3484]
	ldr	r0, [r4, #3480]
	ldr	r1, [r4, #3492]
	cmp	r2, r0
	addcc	r1, r1, r3
	strcc	r1, [r4, #3488]
	bcs	.L1217
.L1218:
	add	r3, r1, r2
	str	r3, [r4, #3476]
	ldr	r0, [r6, #236]
	mov	r3, r3, asl #1
	cmp	r0, #0
	subeq	r3, r3, #1
	str	r3, [r4, #3464]
	ldrb	r0, [r6, #209]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1221
	str	r3, [r4, #3460]
	str	r3, [r4, #3456]
	str	r3, [r4, #3452]
.L1214:
	str	r2, [r4, #3480]
	str	r1, [r4, #3492]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1182:
	cmp	r2, #0
	add	lr, lr, #4
	add	r4, r0, #16384
	mov	ip, ip, asl lr
	bne	.L1188
	ldr	r3, [r4, #3444]
	cmp	r3, #0
	bne	.L1186
	ldr	lr, [r4, #3428]
	ldr	r1, [r4, #3432]
	mov	r2, lr
.L1187:
	ldr	r0, [r4, #3420]
	cmp	r0, r1
	bcs	.L1185
	rsb	r3, r0, r1
	cmp	r3, ip, lsr #1
	addcs	r2, r2, ip
	strcs	r2, [r4, #3436]
	bcc	.L1185
.L1189:
	ldrb	r3, [r6, #209]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1191
.L1239:
	ldr	r3, [r4, #3424]
	add	r2, r2, r0
	str	r2, [r4, #3452]
	add	r3, r2, r3
	str	r3, [r4, #3456]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r4, #3464]
.L1192:
	ldr	r2, [r4, #3484]
	ldr	r1, [r4, #3480]
	str	r3, [r4, #3460]
	cmp	r2, r1
	strne	r2, [r4, #3480]
	ldr	r3, [r6, #236]
	cmp	r3, #0
	ldrne	r2, [r4, #3420]
	ldrne	r3, [r4, #3436]
	strne	r2, [r4, #3432]
	strne	r3, [r4, #3428]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1181:
	cmp	r2, #0
	add	r4, r0, #16384
	movne	r3, #0
	strne	r3, [r4, #3488]
	bne	.L1196
	ldr	r1, [r4, #3444]
	cmp	r1, #0
	beq	.L1197
	mov	r3, r2
	str	r2, [r4, #3492]
	str	r2, [r4, #3480]
.L1198:
	str	r3, [r4, #3488]
.L1196:
	ldr	r3, [r5, #2216]
	cmp	r3, #0
	beq	.L1200
	ldr	r3, [r4, #3484]
	ldr	r0, [r4, #3488]
	add	r0, r3, r0
	str	r0, [r4, #3476]
	ldr	r7, [r6, #236]
	cmp	r7, #0
	bne	.L1202
	cmp	r0, #0
	beq	.L1203
	sub	r0, r0, #1
	str	r0, [r4, #3476]
.L1202:
	mov	r3, #0
	str	r3, [r4, #3508]
	ldr	r1, [r5, #2216]
	cmp	r1, r3
	bgt	.L1223
	cmp	r0, #0
	beq	.L1206
.L1240:
	sub	r8, r0, #1
	mov	r0, r8
	bl	__aeabi_uidiv
	mov	r9, r0
	mov	r0, r8
	str	r9, [r4, #3500]
	ldr	r1, [r5, #2216]
	bl	__aeabi_uidivmod
	ldr	r0, [r4, #3508]
	mul	r0, r0, r9
	str	r0, [r4, #3504]
	cmp	r1, #0
	str	r1, [r4, #3496]
	blt	.L1207
	add	r2, r5, #2208
	add	r1, r1, #1
	add	r2, r2, #8
	mov	r3, #0
.L1208:
	add	r3, r3, #1
	ldr	ip, [r2, #4]!
	cmp	r3, r1
	add	r0, r0, ip
	str	r0, [r4, #3504]
	bne	.L1208
.L1207:
	cmp	r7, #0
	ldreq	r3, [r5, #2208]
	addeq	r0, r0, r3
	streq	r0, [r4, #3504]
	ldrb	r3, [r6, #209]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1210
	ldr	r2, [r4, #3468]
	ldr	r1, [r4, #3472]
	add	r2, r0, r2
	str	r2, [r4, #3452]
	ldr	r3, [r5, #2212]
	add	r3, r2, r3
	add	r0, r3, r1
	str	r0, [r4, #3456]
	cmp	r0, r2
	movge	r0, r2
	str	r0, [r4, #3464]
.L1211:
	ldr	r2, [r4, #3484]
	ldr	r3, [r4, #3488]
	str	r0, [r4, #3460]
	str	r2, [r4, #3480]
	str	r3, [r4, #3492]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1186:
	ldr	lr, [r4, #3448]
	cmp	lr, #0
	beq	.L1238
.L1188:
	ldr	r0, [r4, #3420]
	mov	r3, #0
	mov	lr, r3
	mov	r2, r1
	str	r3, [r4, #3428]
	str	r3, [r4, #3432]
.L1185:
	cmp	r0, r1
	bls	.L1190
	rsb	r1, r1, r0
	cmp	r1, ip, lsr #1
	rsbhi	r2, ip, r2
	strhi	r2, [r4, #3436]
	bhi	.L1189
.L1190:
	str	lr, [r4, #3436]
	ldrb	r3, [r6, #209]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1239
.L1191:
	ldrb	r3, [r6, #210]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r2, r0
	streq	r3, [r4, #3452]
	strne	r3, [r4, #3456]
	str	r3, [r4, #3464]
	b	.L1192
.L1237:
	mov	r3, #0
	ldr	r2, [r4, #3484]
	mov	r1, r3
	str	r3, [r4, #3488]
	str	r3, [r4, #3456]
	str	r3, [r4, #3452]
	str	r3, [r4, #3460]
	str	r3, [r4, #3464]
	b	.L1214
.L1200:
	str	r3, [r4, #3476]
	ldr	r7, [r6, #236]
.L1203:
	mov	r0, #0
	str	r0, [r4, #3508]
	ldr	r3, [r5, #2216]
	cmp	r3, r0
	ble	.L1206
.L1223:
	add	ip, r5, #2208
	mov	r3, #0
	add	ip, ip, #8
	mov	r2, r3
.L1205:
	ldr	r1, [ip, #4]!
	add	r2, r2, #1
	add	r3, r3, r1
	str	r3, [r4, #3508]
	ldr	r1, [r5, #2216]
	cmp	r1, r2
	bgt	.L1205
	cmp	r0, #0
	bne	.L1240
.L1206:
	mov	r0, #0
	str	r0, [r4, #3504]
	b	.L1207
.L1210:
	ldrb	r3, [r6, #210]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r2, [r5, #2212]
	ldreq	r3, [r4, #3468]
	ldrne	r3, [r4, #3468]
	addne	r0, r0, r2
	addeq	r0, r0, r3
	streq	r0, [r4, #3452]
	addne	r0, r0, r3
	strne	r0, [r4, #3456]
	str	r0, [r4, #3464]
	b	.L1211
.L1197:
	ldr	r1, [r4, #3484]
	ldr	r2, [r4, #3480]
	cmp	r1, r2
	bcs	.L1199
	ldr	r2, [r4, #3492]
	add	r3, r3, r2
	str	r3, [r4, #3488]
	b	.L1196
.L1221:
	ldrb	r0, [r6, #210]	@ zero_extendqisi2
	str	r3, [r4, #3460]
	cmp	r0, #0
	streq	r3, [r4, #3452]
	strne	r3, [r4, #3456]
	b	.L1214
.L1215:
	str	r2, [r4, #3480]
	mov	r1, r2
	str	r2, [r4, #3492]
	ldr	r2, [r4, #3484]
.L1217:
	str	r1, [r4, #3488]
	b	.L1218
.L1238:
	ldr	r3, [r4, #3452]
	mov	r2, r1
	str	lr, [r4, #3428]
	mov	r1, r3
	str	r3, [r4, #3432]
	b	.L1187
.L1199:
	ldr	r3, [r4, #3492]
	b	.L1198
	UNWIND(.fnend)
	.size	DecPOC, .-DecPOC
	.align	2
	.global	CalcPicNum
	.type	CalcPicNum, %function
CalcPicNum:
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
	add	r3, r0, #20480
	add	ip, r0, #12288
	mov	r4, #2208
	mov	lr, #4000
	ldr	r2, [r3, #216]
	add	r6, r0, #57344
	ldr	r1, [ip, #1304]
	mov	r7, #1
	ldr	r3, [ip, #1300]
	mla	r1, r4, r2, r1
	ldrb	r2, [r6, #3331]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r1, [r1, #28]
	mla	r3, lr, r1, r3
	ldr	r3, [r3, #2196]
	add	r3, r3, #4
	mov	r7, r7, asl r3
	add	r3, r0, #24576
	beq	.L1242
	sub	r5, r2, #1
	sub	r4, r2, #2
	ldr	r2, [r3, #2144]
	clz	r5, r5
	clz	r4, r4
	cmp	r2, #0
	mov	r5, r5, lsr #5
	addne	lr, r0, #26368
	mov	r4, r4, lsr #5
	movne	r1, #0
	addne	lr, lr, #212
	beq	.L1262
.L1261:
	ldr	ip, [lr, #4]!
	ldrb	r2, [ip, #2]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1256
	ldr	r2, [ip, #660]
	ldr	r8, [r6, #3992]
	cmp	r2, r8
	rsbhi	r2, r7, r2
	str	r2, [ip, #664]
	ldr	r2, [lr]
	ldrb	ip, [r2, #2]	@ zero_extendqisi2
	tst	ip, #1
	beq	.L1259
	ldr	r8, [r2, #744]
	bic	r8, r8, #-16777216
	bic	r8, r8, #255
	cmp	r8, #65536
	ldreq	ip, [r2, #664]
	addeq	ip, r5, ip, lsl #1
	streq	ip, [r2, #752]
	ldreq	r2, [lr]
	ldreqb	ip, [r2, #2]	@ zero_extendqisi2
.L1259:
	tst	ip, #2
	beq	.L1256
	ldr	ip, [r2, #784]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	ldreq	ip, [r2, #664]
	addeq	ip, r4, ip, lsl #1
	streq	ip, [r2, #792]
.L1256:
	ldr	r2, [r3, #2144]
	add	r1, r1, #1
	cmp	r2, r1
	bhi	.L1261
.L1262:
	ldr	r2, [r3, #2148]
	cmp	r2, #0
	beq	.L1286
	add	r0, r0, #26624
	mov	r2, #0
	add	r0, r0, #20
.L1267:
	ldr	ip, [r0, #4]!
	add	r2, r2, #1
	ldrb	r1, [ip, #2]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1264
	tst	r1, #1
	beq	.L1265
	ldr	lr, [ip, #744]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	ldreq	r1, [ip, #668]
	addeq	r1, r5, r1, lsl #1
	streq	r1, [ip, #748]
	ldreq	ip, [r0]
	ldreqb	r1, [ip, #2]	@ zero_extendqisi2
.L1265:
	tst	r1, #2
	beq	.L1264
	ldr	r1, [ip, #784]
	bic	r1, r1, #-16777216
	bic	r1, r1, #255
	cmp	r1, #256
	ldreq	r1, [ip, #668]
	addeq	r1, r4, r1, lsl #1
	streq	r1, [ip, #788]
.L1264:
	ldr	r1, [r3, #2148]
	cmp	r1, r2
	bhi	.L1267
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1242:
	ldr	r1, [r3, #2144]
	cmp	r1, #0
	addne	ip, r0, #26368
	addne	ip, ip, #212
	bne	.L1251
.L1252:
	ldr	r2, [r3, #2148]
	cmp	r2, #0
	beq	.L1287
	add	r0, r0, #26624
	mov	r2, #0
	add	r0, r0, #20
	b	.L1254
.L1253:
	ldr	r1, [r3, #2148]
	cmp	r1, r2
	bls	.L1288
.L1254:
	ldr	r1, [r0, #4]!
	add	r2, r2, #1
	ldrb	ip, [r1, #2]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1253
	ldr	ip, [r1, #704]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	ldreq	ip, [r1, #668]
	streq	ip, [r1, #708]
	ldr	r1, [r3, #2148]
	cmp	r1, r2
	bhi	.L1254
.L1288:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1289:
	ldr	lr, [r1, #704]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L1248
	ldr	lr, [r1, #660]
	ldr	r4, [r6, #3992]
	rsb	r5, r7, lr
	cmp	lr, r4
	strhi	r5, [r1, #664]
	strls	lr, [r1, #664]
	ldr	r1, [ip]
	ldr	lr, [r1, #664]
	str	lr, [r1, #712]
.L1248:
	ldr	r1, [r3, #2144]
	add	r2, r2, #1
	cmp	r1, r2
	bls	.L1252
.L1251:
	ldr	r1, [ip, #4]!
	ldrb	lr, [r1, #2]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L1248
	b	.L1289
.L1287:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1286:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	CalcPicNum, .-CalcPicNum
	.align	2
	.global	IsOutDPB
	.type	IsOutDPB, %function
IsOutDPB:
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
	beq	.L1295
	add	r3, r0, #24576
	ldr	ip, [r3, #2140]
	cmp	ip, #0
	beq	.L1295
	ldr	r3, [r3, #1944]
	cmp	r3, r1
	beq	.L1297
	add	r0, r0, #26368
	mov	r3, #0
	add	r0, r0, #152
	b	.L1292
.L1293:
	ldr	r2, [r0, #4]!
	cmp	r2, r1
	beq	.L1297
.L1292:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1293
.L1295:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1297:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsOutDPB, .-IsOutDPB
	.align	2
	.global	WritePicMsg
	.type	WritePicMsg, %function
WritePicMsg:
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
	beq	.L1333
	add	r9, r4, #57344
	add	lr, r4, #12288
	ldr	r1, .L1336
	mov	r0, #2
	ldr	ip, [r9, #4052]
	add	r5, r4, #61440
	ldrb	r3, [r9, #3331]	@ zero_extendqisi2
	mov	r6, lr
	ldr	r2, [r9, #4000]
	mov	r7, #0
	str	ip, [sp, #4]
	add	r8, r4, #16384
	ldr	ip, [r9, #3492]
	str	lr, [fp, #-52]
	str	ip, [sp]
	bl	dprint_vfmw
	add	r3, r4, #61184
	str	r7, [r5, #2604]
	movw	r2, #62880
	ldrd	r0, [r3, #88]
	strd	r0, [r4, r2]
	ldr	r3, [r5, #2600]
	str	r3, [r5, #2360]
	ldr	r3, [r9, #3456]
	str	r3, [r5, #2136]
	ldr	r3, [r9, #3460]
	str	r3, [r5, #2140]
	ldr	r3, [r9, #3480]
	str	r3, [r5, #2144]
	ldr	r3, [r9, #3484]
	str	r3, [r5, #2148]
	ldr	r3, [r9, #4000]
	str	r3, [r5, #1448]
	ldrb	r3, [r9, #3331]	@ zero_extendqisi2
	strb	r3, [r5, #1416]
	ldrb	r3, [r6, #1327]	@ zero_extendqisi2
	str	r3, [r5, #1464]
	ldr	r3, [r9, #4036]
	str	r3, [r5, #1452]
	ldr	r3, [r9, #4040]
	str	r3, [r5, #1456]
	ldr	r3, [r8, #460]
	add	r3, r3, #1
	str	r3, [r5, #1460]
	ldrb	r3, [r6, #1326]	@ zero_extendqisi2
	strb	r3, [r5, #1419]
	ldr	r3, [r8, #1272]
	str	r3, [r5, #1468]
	ldrb	r3, [r8, #1212]	@ zero_extendqisi2
	str	r3, [r5, #1472]
	ldr	r3, [r6, #1348]
	strb	r3, [r5, #1417]
	ldrb	r3, [r8, #1216]	@ zero_extendqisi2
	ldr	r0, [r5, #2680]
	str	r3, [r5, #1476]
	ldr	r3, [r8, #3464]
	str	r3, [r5, #1480]
	ldr	r3, [r8, #3452]
	str	r3, [r5, #1484]
	ldr	r3, [r8, #3456]
	str	r3, [r5, #1488]
	ldr	r3, [r9, #3984]
	ldr	r1, [r3, #656]
	bl	FSP_GetLogicFs
	subs	r10, r0, #0
	beq	.L1334
	ldr	r2, [r10, #28]
	ldr	r3, [r10, #32]
	cmp	r2, #0
	beq	.L1303
	cmp	r3, #0
	beq	.L1303
	add	r3, r4, #63232
	add	r2, r4, #62976
	add	r2, r2, #204
	ldr	r0, [r5, #2680]
	mov	r1, r3
	add	r3, r3, #76
	add	r1, r1, #204
	add	r6, r4, #24576
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r10, #28]
	add	r2, r4, #63232
	add	r1, r4, #63488
	add	r2, r2, #208
	add	r1, r1, #80
	ldr	r3, [r3, #4]
	ldr	r0, [r5, #2680]
	str	r3, [r5, #1724]
	bl	FSP_GetPmvAddrTab
	ldr	r3, [r9, #4052]
	str	r3, [r5, #1732]
	ldr	r3, [r10, #12]
	str	r3, [r5, #2132]
	ldr	r3, [r10, #32]
	ldr	r3, [r3, #8]
	str	r3, [r5, #1728]
	ldr	r3, [r10, #32]
	ldr	r3, [r3, #60]
	str	r3, [r5, #1736]
	ldr	r3, [r6, #2412]
	cmp	r3, #0
	str	r3, [fp, #-48]
	str	r3, [r5, #2352]
	beq	.L1309
	add	lr, r4, #63488
	add	r9, r4, #26624
	add	r1, r4, #26880
	ldr	r10, [fp, #-48]
	mov	ip, r9
	mov	r0, lr
	mov	r2, lr
	add	r9, r9, #168
	add	lr, lr, #108
	add	ip, ip, #232
	add	r0, r0, #172
	add	r1, r1, #40
	add	r2, r2, #236
	mov	r3, r7
.L1308:
	ldr	r7, [r9, #4]!
	add	r3, r3, #1
	cmp	r3, r10
	str	r7, [lr, #4]!
	ldr	r7, [ip, #4]!
	str	r7, [r0, #4]!
	ldr	r7, [r1, #4]!
	str	r7, [r2, #4]!
	bne	.L1308
.L1309:
	ldr	r3, [fp, #-52]
	ldrb	r3, [r3, #1333]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1335
	ldrb	r1, [r8, #1230]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1310
	add	ip, r4, #62720
	ldr	r0, .L1336+4
	add	ip, ip, #208
.L1311:
	and	r3, r1, #3
	add	r1, r1, #1
	cmp	r1, #24
	ldr	r3, [r0, r3, asl #2]
	bic	r2, r3, #16711680
	ubfx	lr, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, lr, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1311
	add	r7, r4, #62976
	mov	lr, #0
	add	r7, r7, #52
.L1312:
	add	r3, lr, #1
	and	r2, lr, #14
	and	r3, r3, #15
	add	lr, lr, #2
	add	r2, r0, r2, lsl #2
	cmp	lr, #32
	add	r3, r0, r3, lsl #2
	ldr	r1, [r2, #16]
	ldr	ip, [r3, #16]
	ubfx	r3, r1, #8, #8
	mov	r2, r1, lsr #24
	uxtb	r10, r1
	uxtb	r9, ip
	mov	r8, ip, lsr #16
	orr	r3, r3, r2, asl #8
	mov	r1, r1, lsr #8
	mov	r9, r9, asl #16
	and	r2, ip, #-16777216
	orr	r8, r9, r8, asl #24
	ubfx	ip, ip, #8, #8
	orr	r3, r3, r2
	orr	r8, r8, r10
	and	r1, r1, #65280
	orr	r3, r3, ip, asl #16
	orr	r2, r8, r1
	stmia	r7, {r2, r3}
	add	r7, r7, #8
	bne	.L1312
.L1317:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1314
	add	r9, r4, #63744
	add	r7, r4, #26624
	add	r7, r7, #172
	mov	r8, #0
	mov	r4, r9
	add	r9, r9, #160
	add	r4, r4, #224
.L1320:
	ldr	r2, [r7]
	mov	r1, #0
	ldr	r0, [r5, #2680]
	add	r8, r8, #1
	bl	FSP_GetStoreType
	adds	r0, r0, #0
	movne	r0, #1
	str	r0, [r9, #4]!
	ldr	r3, [r7], #4
	str	r3, [r4, #4]!
	ldr	r3, [r6, #2412]
	cmp	r3, r8
	bhi	.L1320
.L1314:
	mov	r0, #0
.L1330:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1335:
	ldrb	r1, [r8, #1230]	@ zero_extendqisi2
.L1310:
	cmp	r1, #1
	add	ip, r4, #62720
	mov	r0, #0
	add	ip, ip, #208
	beq	.L1315
.L1318:
	add	r3, r0, #3888
	add	r0, r0, #1
	add	r3, r3, #2
	cmp	r0, #24
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #8]
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1318
	add	r9, r4, #62976
	mov	r10, #1
	add	r9, r9, #52
	mov	r8, #0
.L1319:
	mov	r2, r8, lsr #3
	mov	r3, r8, asl #1
	and	r1, r10, #15
	and	r0, r3, #14
	mov	r3, r2, asl #4
	add	r8, r8, #1
	add	r2, r3, r1
	add	r3, r3, r0
	add	r2, r2, #3904
	add	r3, r3, #3904
	add	r2, r2, #10
	add	r3, r3, #10
	cmp	r8, #16
	add	r10, r10, #2
	add	r2, r4, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r1, [r2, #8]
	ldr	r3, [r3, #8]
	ubfx	r7, r1, #8, #8
	and	r0, r1, #-16777216
	mov	r2, r1, lsr #16
	uxtb	r1, r1
	mov	ip, r3, lsr #24
	uxtb	lr, r3
	mov	r2, r2, asl #24
	mov	ip, ip, asl #8
	orr	r2, r2, r1, asl #16
	orr	ip, ip, r7, asl #16
	mov	r1, r3, lsr #8
	orr	r2, r2, lr
	and	r1, r1, #65280
	ubfx	r3, r3, #8, #8
	orr	r0, ip, r0
	orr	r2, r2, r1
	orr	r3, r0, r3
	stmia	r9, {r2, r3}
	add	r9, r9, #8
	bne	.L1319
	b	.L1317
.L1315:
	add	r3, r0, #4864
	add	r0, r0, #1
	add	r3, r3, #30
	cmp	r0, #24
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1315
	add	ip, r4, #62976
	mov	lr, #1
	add	ip, ip, #52
	mov	r0, #0
.L1316:
	mov	r2, r0, lsr #3
	mov	r3, r0, asl #1
	and	r1, lr, #15
	and	r7, r3, #14
	mov	r3, r2, asl #4
	add	r0, r0, #1
	add	r2, r3, r1
	add	r3, r3, r7
	add	r2, r2, #4864
	add	r3, r3, #4864
	add	r2, r2, #54
	add	r3, r3, #54
	cmp	r0, #16
	add	lr, lr, #2
	add	r2, r4, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r2, [r2, #4]
	ldr	r3, [r3, #4]
	ubfx	r10, r2, #8, #8
	and	r1, r2, #-16777216
	mov	r8, r2, lsr #16
	uxtb	r2, r2
	mov	r7, r3, lsr #24
	uxtb	r9, r3
	mov	r8, r8, asl #24
	mov	r7, r7, asl #8
	orr	r8, r8, r2, asl #16
	orr	r7, r7, r10, asl #16
	mov	r2, r3, lsr #8
	orr	r8, r8, r9
	and	r2, r2, #65280
	ubfx	r3, r3, #8, #8
	orr	r1, r7, r1
	orr	r2, r8, r2
	orr	r3, r1, r3
	stmia	ip, {r2, r3}
	add	ip, ip, #8
	bne	.L1316
	b	.L1317
.L1303:
	ldr	r1, .L1336+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1330
.L1333:
	movw	r3, #6919
	ldr	r2, .L1336+12
	ldr	r1, .L1336+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1330
.L1334:
	ldr	r3, [r9, #3984]
	ldr	r1, .L1336+20
	ldr	r2, [r3, #656]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1330
.L1337:
	.align	2
.L1336:
	.word	.LC39
	.word	.LANCHOR1
	.word	.LC41
	.word	.LC8
	.word	.LC9
	.word	.LC40
	UNWIND(.fnend)
	.size	WritePicMsg, .-WritePicMsg
	.align	2
	.global	UpdatePicQpInf
	.type	UpdatePicQpInf, %function
UpdatePicQpInf:
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
	ldr	r2, [r1, #24]
	ldr	r3, [r1, #28]
	cmp	r2, r0
	movlt	r2, r0
	cmp	r3, r0
	str	r2, [r1, #24]
	movge	r3, r0
	str	r3, [r1, #28]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	UpdatePicQpInf, .-UpdatePicQpInf
	.align	2
	.global	WriteSliceMsg
	.type	WriteSliceMsg, %function
WriteSliceMsg:
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
	add	r8, r0, #61440
	add	lr, r0, #12288
	movw	r1, #4060
	ldr	r3, [r8, #2604]
	mov	r4, r0
	ldr	ip, [r8, #2600]
	mov	r2, r3
	str	r3, [fp, #-48]
	mul	r1, r1, r2
	add	r3, r3, #1
	str	r3, [r8, #2604]
	ldr	r3, [lr, #1284]
	add	r6, ip, r1
	sub	r3, r3, #1
	cmp	r2, r3
	addcc	r3, r1, #4048
	addcc	r3, r3, #12
	movcs	r3, #0
	addcc	r3, ip, r3
	str	r3, [r6, #4056]
	ldr	r2, [r0, #368]
	ldrb	r0, [r2]	@ zero_extendqisi2
	ldr	r3, [r2, #68]
	cmp	r0, #1
	cmpls	r0, r3
	bcs	.L1342
	add	r5, r0, #3
	add	r5, r6, r5, lsl #2
.L1343:
	mov	r3, r0, asl #5
	sub	r3, r3, r0, asl #2
	add	r0, r0, #1
	add	r2, r2, r3
	ldr	r2, [r2, #24]
	str	r2, [r5, #4]!
	ldr	r2, [r4, #368]
	add	r2, r2, r3
	ldr	r2, [r2, #20]
	str	r2, [r5, #-8]
	ldr	r2, [r4, #368]
	add	r3, r2, r3
	ldr	r3, [r3, #28]
	str	r3, [r5, #8]
	ldr	r2, [r4, #368]
	ldr	r3, [r2, #68]
	cmp	r3, r0
	movhi	r7, #1
	movls	r7, #0
	cmp	r0, #1
	movhi	r7, #0
	cmp	r7, #0
	bne	.L1343
.L1342:
	cmp	r3, #1
	bhi	.L1348
	add	r3, r3, #3
	add	r0, r6, #20
	mov	r2, #0
	add	r3, r6, r3, lsl #2
.L1347:
	str	r2, [r3, #4]!
	cmp	r3, r0
	str	r2, [r3, #-8]
	str	r2, [r3, #8]
	bne	.L1347
.L1348:
	add	r7, r4, #57344
	add	r9, r4, #16384
	add	r5, r4, #20480
	ldrb	r3, [r7, #3337]	@ zero_extendqisi2
	strb	r3, [r6, #1]
	ldr	r3, [r9, #1260]
	ldr	r0, [r5, #1816]
	add	r3, r3, #26
	add	r3, r3, r0
	str	r3, [r6, #32]
	ldr	r2, [r5, #1812]
	str	r2, [r6, #36]
	ldr	r2, [r5, #264]
	str	r2, [r6, #40]
	ldr	r2, [r5, #260]
	str	r2, [r6, #44]
	ldrb	r2, [r5, #208]	@ zero_extendqisi2
	strb	r2, [ip, r1]
	ldr	r2, [r5, #256]
	str	r2, [r6, #48]
	ldrb	r2, [r5, #214]	@ zero_extendqisi2
	strb	r2, [r6, #2]
	ldrb	r2, [lr, #1328]	@ zero_extendqisi2
	strb	r2, [r6, #3]
	ldr	r2, [r5, #248]
	str	r2, [r6, #52]
	ldr	r2, [r5, #252]
	str	r2, [r6, #56]
	ldrb	r2, [r5, #208]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1447
	cmp	r2, #0
	ldreqb	r2, [r9, #1214]	@ zero_extendqisi2
	movne	r2, #0
	strb	r2, [r6, #4]
.L1349:
	ldr	r2, [r9, #1264]
	str	r2, [r6, #60]
	ldr	r2, [r9, #1268]
	str	r2, [r6, #64]
	ldr	r2, [r5, #1824]
	str	r2, [r6, #68]
	ldr	r2, [r5, #1828]
	str	r2, [r6, #72]
	ldr	r2, [r5, #1820]
	str	r2, [r6, #76]
	ldrb	r2, [r5, #209]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1351
	ldr	r10, [r7, #3984]
	ldr	r2, [fp, #-48]
	ldr	r1, [r8, #2604]
	ldr	r0, [r10, #700]
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	str	r0, [r10, #736]
.L1352:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ldr	r3, [r7, #3984]
	bne	.L1354
	ldr	r2, [r6, #32]
	str	r2, [r3, #728]
	ldr	r3, [r7, #3984]
	ldr	r2, [r6, #32]
	str	r2, [r3, #732]
.L1355:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1393
	ldr	ip, [r5, #248]
	cmp	ip, #0
	beq	.L1396
	add	r3, r4, #24576
	ldr	r3, [r3, #2548]
	ldr	r1, [r3, #36]
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r2, r4, #26880
	movne	r3, #0
	addne	r2, r2, #244
	bne	.L1361
	b	.L1359
.L1363:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #36]
	ldrb	r0, [r1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1359
.L1361:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1363
	mov	r3, #0
	str	r3, [fp, #-52]
.L1358:
	ldr	ip, [r5, #252]
	cmp	ip, #0
	beq	.L1397
	add	r3, r4, #24576
	ldr	r3, [r3, #2680]
	ldr	r1, [r3, #36]
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r2, r4, #27136
	movne	r3, #0
	addne	r2, r2, #120
	bne	.L1367
	b	.L1365
.L1369:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #36]
	ldrb	r0, [r1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1365
.L1367:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1369
	mov	r3, #0
	str	r3, [fp, #-56]
.L1364:
	ldrb	r2, [r7, #3331]	@ zero_extendqisi2
	ldr	r3, [r5, #248]
	cmp	r2, #0
	beq	.L1370
	cmp	r3, #0
	beq	.L1385
	add	r7, r4, #26880
	mov	r3, #0
	mov	r10, r6
	str	r6, [fp, #-60]
	str	r4, [fp, #-64]
	mov	r6, r5
	add	r7, r7, #244
	ldr	r4, [fp, #-52]
	mov	r5, r3
	b	.L1384
.L1382:
	strb	r1, [r10, #1630]
	ldr	r1, [r7]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1631]
	ldr	r1, [r7]
	ldr	r1, [r1, #12]
	str	r1, [r10, #1656]
.L1383:
	ldr	r1, [r6, #248]
	add	r5, r5, #1
	add	r7, r7, #4
	add	r10, r10, #36
	cmp	r1, r5
	bls	.L1448
.L1384:
	ldr	r1, [r7]
	ldr	r0, [r8, #2680]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #656]
	bl	FSP_GetLogicFs
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #692]
	str	r1, [r10, #1636]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1625]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r4
	beq	.L1381
	cmp	r0, #0
	ldrne	r1, [r0, #28]
	ldrne	r0, [r1, #4]
.L1381:
	str	r0, [r10, #1640]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #696]
	str	r1, [r10, #1644]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #672]
	str	r1, [r10, #1632]
	ldr	r1, [r7]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r10, #1624]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #704]	@ zero_extendqisi2
	strb	r1, [r10, #1626]
	ldr	r1, [r7]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1382
	strb	r1, [r10, #1628]
	ldr	r1, [r7]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1629]
	ldr	r1, [r7]
	ldr	r1, [r1, #12]
	str	r1, [r10, #1652]
	b	.L1383
.L1448:
	mov	r5, r6
	ldr	r4, [fp, #-64]
	ldr	r6, [fp, #-60]
.L1385:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1449
.L1373:
	add	r2, r4, #26880
	add	r3, r6, #3920
	add	r0, r6, #4048
	add	r2, r2, #112
	add	r3, r3, #4
	add	r0, r0, #4
.L1390:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, r0
	bne	.L1390
	ldrb	r3, [r9, #1214]	@ zero_extendqisi2
	cmp	r3, #0
	str	r3, [r8, #1716]
	ldr	r3, [r9, #1256]
	str	r3, [r8, #1720]
	beq	.L1391
	ldrb	r2, [r5, #208]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1392
.L1391:
	cmp	r3, #1
	beq	.L1450
.L1393:
	ldr	r3, [fp, #-48]
	mov	r2, #0
	ldr	r1, [r4, #368]
	add	r3, r3, #15488
	add	r3, r3, #60
	str	r1, [r4, r3, asl #2]
	str	r2, [r4, #368]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1354:
	ldr	r1, [r6, #32]
	ldr	r0, [r3, #728]
	ldr	r2, [r3, #732]
	cmp	r0, r1
	movlt	r0, r1
	cmp	r2, r1
	str	r0, [r3, #728]
	movge	r2, r1
	str	r2, [r3, #732]
	b	.L1355
.L1351:
	ldr	r10, [r7, #3984]
	ldrb	r2, [r5, #210]	@ zero_extendqisi2
	ldr	r1, [r8, #2604]
	ldr	r0, [r10, #700]
	cmp	r2, #0
	ldr	r2, [fp, #-48]
	mla	r0, r0, r2, r3
	bne	.L1353
	bl	__aeabi_uidiv
	str	r0, [r10, #776]
	b	.L1352
.L1353:
	bl	__aeabi_uidiv
	str	r0, [r10, #816]
	b	.L1352
.L1359:
	ldr	r1, [r1, #656]
	ldr	r0, [r8, #2680]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	movweq	r2, #7282
	beq	.L1443
	ldr	r3, [r3, #28]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-52]
	b	.L1358
.L1450:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1393
.L1392:
	ldr	r3, [r5, #268]
	add	r9, r4, #20736
	add	lr, r4, #21504
	add	r7, r4, #20992
	add	r0, r4, #21760
	mov	r8, r9
	str	r3, [r6, #80]
	mov	ip, lr
	ldr	r10, [r5, #272]
	add	r9, r9, #16
	add	r8, r8, #144
	add	r7, r7, #16
	add	lr, lr, #16
	add	ip, ip, #144
	add	r0, r0, #16
	mov	r1, r6
	mov	r3, r6
	mov	r2, #0
	str	r6, [fp, #-52]
	str	r10, [r1, #84]!
.L1394:
	ldr	r10, [r9, #4]!
	add	r2, r2, #1
	add	r3, r3, #4
	str	r10, [r1, #4]!
	ldr	r10, [r8, #4]!
	str	r10, [r3, #212]
	ldr	r10, [r7, #4]!
	str	r10, [r3, #340]
	ldr	r10, [lr, #4]!
	str	r10, [r3, #852]
	ldr	r10, [ip, #4]!
	str	r10, [r3, #980]
	ldr	r10, [r0, #4]!
	str	r10, [r3, #1108]
	ldr	r10, [r5, #260]
	cmp	r10, r2
	bcs	.L1394
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1393
	add	lr, r4, #21248
	add	r1, r4, #22016
	add	r7, r4, #20992
	add	r0, r4, #21760
	ldr	r8, [fp, #-52]
	mov	ip, lr
	mov	r2, r1
	add	r6, r6, #468
	add	r7, r7, #144
	add	lr, lr, #16
	add	ip, ip, #144
	add	r0, r0, #144
	add	r1, r1, #16
	add	r2, r2, #144
	mov	r3, #0
.L1395:
	ldr	r9, [r7, #4]!
	add	r3, r3, #1
	add	r8, r8, #4
	str	r9, [r6, #4]!
	ldr	r9, [lr, #4]!
	str	r9, [r8, #596]
	ldr	r9, [ip, #4]!
	str	r9, [r8, #724]
	ldr	r9, [r0, #4]!
	str	r9, [r8, #1236]
	ldr	r9, [r1, #4]!
	str	r9, [r8, #1364]
	ldr	r9, [r2, #4]!
	str	r9, [r8, #1492]
	ldr	r9, [r5, #264]
	cmp	r9, r3
	bcs	.L1395
	b	.L1393
.L1370:
	cmp	r3, #0
	beq	.L1378
	add	r3, r4, #26880
	str	r4, [fp, #-64]
	add	r3, r3, #244
	ldr	r4, [fp, #-52]
	mov	r7, r6
	str	r6, [fp, #-60]
	mov	r10, r3
	mov	r6, r5
	mov	r5, r2
.L1377:
	ldr	r1, [r10]
	ldr	r0, [r8, #2680]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #656]
	bl	FSP_GetLogicFs
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #692]
	str	r1, [r7, #1636]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r7, #1625]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r4
	beq	.L1376
	cmp	r0, #0
	ldrne	r1, [r0, #28]
	ldrne	r0, [r1, #4]
.L1376:
	str	r0, [r7, #1640]
	mov	r3, #0
	ldr	r1, [r10]
	add	r5, r5, #1
	add	r7, r7, #36
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #696]
	str	r1, [r7, #1608]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #672]
	str	r1, [r7, #1596]
	ldr	r1, [r10]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r7, #1591]
	ldr	r1, [r10]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r7, #1590]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #716]
	str	r1, [r7, #1612]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #756]
	str	r1, [r7, #1616]
	ldr	r1, [r10], #4
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #796]
	strb	r3, [r7, #1588]
	str	r1, [r7, #1620]
	ldr	r1, [r6, #248]
	cmp	r1, r5
	bhi	.L1377
	mov	r5, r6
	ldr	r4, [fp, #-64]
	ldr	r6, [fp, #-60]
.L1378:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1373
	ldr	r3, [r5, #252]
	cmp	r3, #0
	beq	.L1373
	add	r3, r4, #27136
	str	r4, [fp, #-60]
	add	r3, r3, #120
	ldr	r4, [fp, #-56]
	mov	r10, #0
	mov	r7, r6
	str	r6, [fp, #-52]
	mov	r6, r5
	mov	r5, r10
	mov	r10, r3
.L1380:
	ldr	r1, [r10]
	ldr	r0, [r8, #2680]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #656]
	bl	FSP_GetLogicFs
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #692]
	str	r1, [r7, #2788]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r7, #2777]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r4
	beq	.L1379
	cmp	r0, #0
	ldrne	r1, [r0, #28]
	ldrne	r0, [r1, #4]
.L1379:
	str	r0, [r7, #1640]
	mov	r3, #0
	ldr	r1, [r10]
	add	r5, r5, #1
	add	r7, r7, #36
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #696]
	str	r1, [r7, #2760]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #672]
	str	r1, [r7, #2748]
	ldr	r1, [r10]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r7, #2743]
	ldr	r1, [r10]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r7, #2742]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #716]
	str	r1, [r7, #2764]
	ldr	r1, [r10]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #756]
	str	r1, [r7, #2768]
	ldr	r1, [r10], #4
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #796]
	strb	r3, [r7, #2740]
	str	r1, [r7, #2772]
	ldr	r1, [r6, #252]
	cmp	r1, r5
	bhi	.L1380
.L1442:
	mov	r5, r6
	ldr	r4, [fp, #-60]
	ldr	r6, [fp, #-52]
	b	.L1373
.L1365:
	ldr	r1, [r1, #656]
	ldr	r0, [r8, #2680]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1451
	ldr	r3, [r3, #28]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-56]
	b	.L1364
.L1447:
	ldr	r2, [r9, #1256]
	strb	r2, [r6, #4]
	b	.L1349
.L1449:
	ldr	r3, [r5, #252]
	cmp	r3, #0
	beq	.L1373
	add	r7, r4, #27136
	mov	r3, #0
	mov	r10, r6
	str	r6, [fp, #-52]
	str	r4, [fp, #-60]
	mov	r6, r5
	add	r7, r7, #120
	ldr	r4, [fp, #-56]
	mov	r5, r3
	b	.L1389
.L1387:
	strb	r1, [r10, #2782]
	ldr	r1, [r7]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2783]
	ldr	r1, [r7]
	ldr	r1, [r1, #12]
	str	r1, [r10, #2808]
.L1388:
	ldr	r1, [r6, #252]
	add	r5, r5, #1
	add	r7, r7, #4
	add	r10, r10, #36
	cmp	r1, r5
	bls	.L1442
.L1389:
	ldr	r1, [r7]
	ldr	r0, [r8, #2680]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #656]
	bl	FSP_GetLogicFs
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #692]
	str	r1, [r10, #2788]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2777]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r4
	beq	.L1386
	cmp	r0, #0
	ldrne	r1, [r0, #28]
	ldrne	r0, [r1, #4]
.L1386:
	str	r0, [r10, #2792]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #696]
	str	r1, [r10, #2796]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #672]
	str	r1, [r10, #2784]
	ldr	r1, [r7]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r10, #2776]
	ldr	r1, [r7]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #704]	@ zero_extendqisi2
	strb	r1, [r10, #2778]
	ldr	r1, [r7]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1387
	strb	r1, [r10, #2780]
	ldr	r1, [r7]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2781]
	ldr	r1, [r7]
	ldr	r1, [r1, #12]
	str	r1, [r10, #2804]
	b	.L1388
.L1451:
	movw	r2, #7303
.L1443:
	ldr	r1, .L1452
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L1396:
	str	ip, [fp, #-52]
	b	.L1358
.L1397:
	str	ip, [fp, #-56]
	b	.L1364
.L1453:
	.align	2
.L1452:
	.word	.LC42
	UNWIND(.fnend)
	.size	WriteSliceMsg, .-WriteSliceMsg
	.align	2
	.global	H264_GetPicStreamSize
	.type	H264_GetPicStreamSize, %function
H264_GetPicStreamSize:
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
	add	r0, r0, #61440
	ldr	r2, [r0, #2360]
	cmp	r2, #0
	beq	.L1457
	mov	r0, #0
.L1456:
	ldr	r3, [r2, #8]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L1456
	ldmfd	sp, {fp, sp, pc}
.L1457:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	H264_GetPicStreamSize, .-H264_GetPicStreamSize
	.align	2
	.global	SliceCheck
	.type	SliceCheck, %function
SliceCheck:
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
	ldr	r1, .L1470
	add	r4, r0, #20480
	add	r6, r0, #61440
	mov	r5, r0
	bl	ue_v
	str	r0, [r4, #256]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L1468
	cmp	r0, #262144
	bcs	.L1469
	add	r2, r5, #12288
	ldr	r1, [r2, #1276]
	ldr	r3, [r2, #1280]
	mul	r3, r3, r1
	sub	r3, r3, #1
	cmp	r0, r3
	bhi	.L1468
	mov	r0, r5
	ldr	r1, .L1470+4
	bl	ue_v
	ldr	r1, .L1470+8
	mov	r2, r0
	mov	r5, r0
	mov	r0, #19
	bl	dprint_vfmw
	ldr	r0, [r6, #2620]
	cmp	r0, #0
	bne	.L1468
	cmp	r5, #9
	bhi	.L1464
	mov	r1, #1
	movw	r3, #297
	mov	r2, r1, asl r5
	and	r3, r3, r2
	cmp	r3, #0
	bne	.L1465
	ands	r0, r2, #660
	bne	.L1466
	tst	r2, #66
	beq	.L1464
	strb	r1, [r4, #208]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1465:
	strb	r0, [r4, #208]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1464:
	mov	r2, r5
	ldr	r1, .L1470+12
	mov	r0, #1
	bl	dprint_vfmw
.L1468:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1466:
	mov	r0, r3
	mov	r3, #2
	strb	r3, [r4, #208]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1469:
	ldr	r1, .L1470+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1471:
	.align	2
.L1470:
	.word	.LC43
	.word	.LC45
	.word	.LC46
	.word	.LC47
	.word	.LC44
	UNWIND(.fnend)
	.size	SliceCheck, .-SliceCheck
	.align	2
	.global	PPSSPSCheck
	.type	PPSSPSCheck, %function
PPSSPSCheck:
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
	add	r5, r0, #20480
	mov	r4, r0
	add	r4, r4, #12288
	ldr	r1, .L1482
	ldr	r2, [r5, #216]
	mov	r0, #19
	bl	dprint_vfmw
	ldr	r2, [r5, #216]
	mov	r3, #2208
	ldr	r0, [r4, #1304]
	mlas	r0, r3, r2, r0
	beq	.L1478
	ldrb	r1, [r0, #19]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1479
	ldr	r2, [r0, #28]
	mov	r3, #4000
	ldr	r0, [r4, #1300]
	mlas	r0, r3, r2, r0
	beq	.L1480
	ldrb	r3, [r0, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1481
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1479:
	ldr	r1, .L1482+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1481:
	ldr	r1, .L1482+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1478:
	movw	r3, #7777
	ldr	r2, .L1482+12
	ldr	r1, .L1482+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1480:
	movw	r3, #7788
	ldr	r2, .L1482+12
	ldr	r1, .L1482+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1483:
	.align	2
.L1482:
	.word	.LC48
	.word	.LC49
	.word	.LC50
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	PPSSPSCheck, .-PPSSPSCheck
	.align	2
	.global	PPSSPSCheckTmpId
	.type	PPSSPSCheckTmpId, %function
PPSSPSCheckTmpId:
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
	mov	r2, r1
	mov	r5, r1
	mov	r0, #19
	ldr	r1, .L1494
	bl	dprint_vfmw
	cmp	r4, #0
	beq	.L1490
	add	r0, r4, #12288
	mov	r3, #2208
	ldr	r2, [r0, #1304]
	mla	r3, r3, r5, r2
	ldrb	r2, [r3, #19]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1491
	ldr	r1, [r0, #1288]
	ldr	r2, [r3, #28]
	sub	r3, r1, #1
	cmp	r2, r3
	bhi	.L1492
	ldr	r1, [r0, #1300]
	mov	r3, #4000
	mla	r3, r3, r2, r1
	ldrb	r3, [r3, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1493
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1491:
	mov	r2, r5
	ldr	r1, .L1494+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1492:
	ldr	r1, .L1494+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1493:
	ldr	r1, .L1494+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1490:
	mov	r0, r4
	movw	r3, #7816
	ldr	r2, .L1494+16
	ldr	r1, .L1494+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1495:
	.align	2
.L1494:
	.word	.LC51
	.word	.LC52
	.word	.LC53
	.word	.LC54
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	PPSSPSCheckTmpId, .-PPSSPSCheckTmpId
	.align	2
	.global	IsNewPic
	.type	IsNewPic, %function
IsNewPic:
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
	subs	ip, r0, #0
	beq	.L1509
	add	r3, ip, #20480
	add	lr, ip, #12288
	ldr	r0, [r3, #1852]
	ldr	r1, [lr, #1344]
	ldr	r2, [r3, #1856]
	ldr	r4, [r3, #216]
	ldr	r5, [r3, #1864]
	cmp	r2, r4
	cmpeq	r0, r1
	ldr	r2, [r3, #224]
	ldrb	r4, [r3, #1848]	@ zero_extendqisi2
	ldrb	r0, [r3, #209]	@ zero_extendqisi2
	movne	r1, #1
	moveq	r1, #0
	cmp	r5, r2
	moveq	r2, r1
	orrne	r2, r1, #1
	cmp	r4, r0
	orrne	r2, r2, #1
	cmp	r4, #0
	cmpne	r0, #0
	bne	.L1510
.L1500:
	ldr	r0, [r3, #1860]
	ldr	r1, [r3, #236]
	cmp	r0, r1
	moveq	r0, #0
	beq	.L1501
	cmp	r1, #0
	cmpne	r0, #0
	moveq	r0, #1
	movne	r0, #0
.L1501:
	ldrb	r1, [r3, #1850]	@ zero_extendqisi2
	ldrb	r4, [r3, #211]	@ zero_extendqisi2
	cmp	r1, r4
	orrne	r2, r2, #1
	cmp	r4, #5
	cmpeq	r1, #5
	orr	r2, r2, r0
	beq	.L1511
.L1502:
	ldr	r1, [lr, #3508]
	cmp	r1, #0
	beq	.L1512
	cmp	r1, #1
	bne	.L1504
	add	r1, ip, #16384
	ldr	r0, [r3, #1884]
	ldr	lr, [r3, #1880]
	ldr	r4, [r1, #3472]
	ldr	ip, [r1, #3468]
	cmp	lr, ip
	cmpeq	r0, r4
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
.L1504:
	ldr	r4, [r3, #256]
	mov	r0, #19
	ldr	r1, .L1513
	cmp	r4, #0
	movne	r4, r2
	orreq	r4, r2, #1
	mov	r2, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1512:
	add	ip, ip, #16384
	ldr	r1, [r3, #1872]
	ldr	r0, [r3, #1876]
	ldr	lr, [ip, #3424]
	ldr	ip, [ip, #3420]
	cmp	r1, ip
	cmpeq	r0, lr
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
	b	.L1504
.L1510:
	ldrb	r0, [r3, #1849]	@ zero_extendqisi2
	ldrb	r1, [r3, #210]	@ zero_extendqisi2
	cmp	r0, r1
	orrne	r2, r2, #1
	b	.L1500
.L1509:
	movw	r3, #7856
	ldr	r2, .L1513+4
	ldr	r1, .L1513+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1511:
	ldr	r0, [r3, #1868]
	ldr	r1, [r3, #244]
	cmp	r0, r1
	orrne	r2, r2, #1
	b	.L1502
.L1514:
	.align	2
.L1513:
	.word	.LC55
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	IsNewPic, .-IsNewPic
	.align	2
	.global	ref_pic_list_reordering
	.type	ref_pic_list_reordering, %function
ref_pic_list_reordering:
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
	add	r5, r0, #20480
	add	r3, r0, #12288
	mov	lr, #2208
	mov	ip, #4000
	ldr	r2, [r3, #1304]
	add	r8, r0, #16384
	ldr	r1, [r5, #216]
	mov	r4, r0
	ldr	r3, [r3, #1300]
	mov	r0, #0
	mov	r7, #1
	mla	r2, lr, r1, r2
	ldr	r2, [r2, #28]
	strb	r0, [r8, #3512]
	strb	r0, [r8, #3513]
	mla	r3, ip, r2, r3
	ldrb	r1, [r5, #209]	@ zero_extendqisi2
	cmp	r1, r0
	ldr	r3, [r3, #2196]
	addne	r3, r3, #5
	addeq	r3, r3, #4
	mov	r7, r7, asl r3
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	addhi	r6, r4, #61440
	bls	.L1569
.L1568:
	ldr	r3, [r6, #2620]
.L1534:
	adds	r3, r3, #0
	movne	r3, #1
	rsb	r0, r3, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1569:
	ldr	r1, .L1574
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r8, #3512]
	cmp	r0, #0
	beq	.L1567
	ldr	r3, [r5, #260]
	cmn	r3, #2
	beq	.L1548
	add	r10, r4, #19712
	add	r6, r4, #61440
	add	r10, r10, #184
	mov	r9, #0
	b	.L1531
.L1526:
	cmp	r0, #2
	beq	.L1570
.L1529:
	ldr	r3, [r5, #260]
	add	r3, r3, #2
	cmp	r3, r9
	bls	.L1571
.L1531:
	ldr	r1, .L1574+4
	mov	r0, r4
	bl	ue_v
	add	r9, r9, #1
	cmp	r0, #3
	str	r0, [r10, #4]!
	ldr	r3, [r6, #2620]
	bhi	.L1522
	cmp	r3, #0
	bne	.L1522
	cmp	r0, #3
	beq	.L1525
	cmp	r0, #1
	bhi	.L1526
	ldr	r1, .L1574+8
	mov	r0, r4
	bl	ue_v
	cmp	r7, r0
	str	r0, [r10, #264]
	ldr	r3, [r6, #2620]
	bls	.L1528
	cmp	r3, #0
	beq	.L1529
.L1528:
	mov	r2, r0
	ldr	r1, .L1574+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1570:
	ldr	r1, .L1574+16
	mov	r0, r4
	bl	ue_v
	str	r0, [r10, #528]
	b	.L1529
.L1567:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	add	r6, r4, #61440
.L1518:
	cmp	r3, #1
	bne	.L1568
	ldr	r1, .L1574+20
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r8, #3513]
	cmp	r0, #0
	beq	.L1568
	ldr	r3, [r5, #264]
	cmn	r3, #2
	beq	.L1568
	add	r9, r4, #19968
	mov	r8, #0
	add	r9, r9, #60
	b	.L1546
.L1545:
	add	r8, r8, #1
	cmp	r8, r3
	bcs	.L1568
.L1546:
	ldr	r1, .L1574+24
	mov	r0, r4
	bl	ue_v
	cmp	r0, #3
	str	r0, [r9, #4]!
	ldr	r3, [r6, #2620]
	bhi	.L1538
	cmp	r3, #0
	bne	.L1538
	cmp	r0, #3
	beq	.L1534
	cmp	r0, #1
	bls	.L1572
	cmp	r0, #2
	beq	.L1573
	ldr	r3, [r5, #264]
	add	r3, r3, #2
	cmp	r3, r8
	bne	.L1545
.L1547:
	ldr	r1, .L1574+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1572:
	ldr	r1, .L1574+32
	mov	r0, r4
	bl	ue_v
	cmp	r7, r0
	str	r0, [r9, #264]
	ldr	r3, [r6, #2620]
	bls	.L1542
	cmp	r3, #0
	bne	.L1542
.L1543:
	ldr	r3, [r5, #264]
	add	r3, r3, #2
	cmp	r3, r8
	bne	.L1545
	ldr	r2, [r9]
	cmp	r2, #3
	beq	.L1545
	b	.L1547
.L1573:
	ldr	r1, .L1574+36
	mov	r0, r4
	bl	ue_v
	str	r0, [r9, #524]
	b	.L1543
.L1525:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	b	.L1518
.L1522:
	mov	r2, r0
	ldr	r1, .L1574+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1538:
	mov	r2, r0
	ldr	r1, .L1574+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1571:
	cmp	r9, r3
	bne	.L1525
.L1520:
	add	r3, r3, #4928
	add	r3, r3, #46
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L1567
	ldr	r1, .L1574+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1542:
	mov	r2, r0
	ldr	r1, .L1574+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1548:
	mov	r3, #0
	b	.L1520
.L1575:
	.align	2
.L1574:
	.word	.LC56
	.word	.LC57
	.word	.LC59
	.word	.LC60
	.word	.LC61
	.word	.LC63
	.word	.LC64
	.word	.LC69
	.word	.LC66
	.word	.LC68
	.word	.LC58
	.word	.LC65
	.word	.LC62
	.word	.LC67
	UNWIND(.fnend)
	.size	ref_pic_list_reordering, .-ref_pic_list_reordering
	.align	2
	.global	pred_weight_table
	.type	pred_weight_table, %function
pred_weight_table:
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
	add	r3, r0, #12288
	add	r6, r0, #20480
	mov	r10, #2208
	ldr	r2, [r3, #1304]
	mov	r7, #4000
	ldr	r1, [r6, #216]
	mov	r5, r0
	ldr	r3, [r3, #1300]
	mov	r4, #1
	mla	r2, r10, r1, r2
	ldr	r1, .L1606
	str	r2, [fp, #-48]
	ldr	r2, [r2, #28]
	mla	r7, r7, r2, r3
	bl	ue_v
	str	r0, [r6, #268]
	mov	r8, r4, asl r0
	ldr	r9, [r7, #40]
	cmp	r9, #0
	bne	.L1600
.L1577:
	cmp	r0, #7
	bhi	.L1580
	ldr	r3, [r6, #272]
	cmp	r3, #7
	bhi	.L1580
	add	r3, r5, #61440
	str	r3, [fp, #-52]
	ldr	r2, [r3, #2620]
	cmp	r2, #0
	addeq	r10, r5, #20736
	moveq	r4, r2
	addeq	r10, r10, #148
	beq	.L1588
	b	.L1579
.L1584:
	ldr	r2, [r7, #40]
	cmp	r2, #0
	bne	.L1601
.L1585:
	str	r2, [r10]
	str	r2, [r10, #768]
	str	r2, [r10, #128]
	str	r2, [r10, #896]
.L1587:
	ldr	r2, [r6, #260]
	add	r4, r4, #1
	add	r10, r10, #4
	cmp	r2, r4
	bcc	.L1602
.L1588:
	ldr	r1, .L1606+4
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	streq	r8, [r10, #-128]
	streq	r0, [r10, #640]
	beq	.L1584
	ldr	r1, .L1606+8
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1606+12
	str	r0, [r10, #-128]
	mov	r0, r5
	bl	se_v
	str	r0, [r10, #640]
	ldr	r2, [r7, #40]
	cmp	r2, #0
	beq	.L1585
.L1601:
	ldr	r1, .L1606+16
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	bne	.L1603
	str	r9, [r10]
	str	r0, [r10, #768]
	str	r9, [r10, #128]
	str	r0, [r10, #896]
	b	.L1587
.L1602:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #44]
	cmp	r3, #1
	beq	.L1589
.L1590:
	ldr	r3, [fp, #-52]
	ldr	r0, [r3, #2620]
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L1582:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1603:
	ldr	r1, .L1606+20
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1606+24
	str	r0, [r10]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1606+20
	str	r0, [r10, #768]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1606+24
	str	r0, [r10, #128]
	mov	r0, r5
	bl	se_v
	str	r0, [r10, #896]
	b	.L1587
.L1600:
	ldr	r1, .L1606+28
	mov	r0, r5
	bl	ue_v
	mov	r3, r0
	ldr	r0, [r6, #268]
	mov	r9, r4, asl r3
	str	r3, [r6, #272]
	b	.L1577
.L1589:
	ldrb	r3, [r6, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1590
	add	r10, r5, #21248
	mov	r4, #0
	add	r10, r10, #20
	b	.L1596
.L1592:
	ldr	r3, [r7, #40]
	cmp	r3, #0
	bne	.L1604
.L1593:
	str	r3, [r10]
	str	r3, [r10, #768]
	str	r3, [r10, #128]
	str	r3, [r10, #896]
.L1595:
	ldr	r3, [r6, #264]
	add	r4, r4, #1
	add	r10, r10, #4
	cmp	r3, r4
	bcc	.L1590
.L1596:
	ldr	r1, .L1606+32
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	streq	r8, [r10, #-128]
	streq	r0, [r10, #640]
	beq	.L1592
	ldr	r1, .L1606+36
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1606+40
	str	r0, [r10, #-128]
	mov	r0, r5
	bl	se_v
	str	r0, [r10, #640]
	ldr	r3, [r7, #40]
	cmp	r3, #0
	beq	.L1593
.L1604:
	ldr	r1, .L1606+44
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	bne	.L1605
	str	r9, [r10]
	str	r0, [r10, #768]
	str	r9, [r10, #128]
	str	r0, [r10, #896]
	b	.L1595
.L1580:
	add	r5, r5, #61440
	ldr	r2, [r5, #2620]
.L1579:
	ldr	r1, .L1606+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1582
.L1605:
	ldr	r1, .L1606+52
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1606+56
	str	r0, [r10]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1606+52
	str	r0, [r10, #768]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1606+56
	str	r0, [r10, #128]
	mov	r0, r5
	bl	se_v
	str	r0, [r10, #896]
	b	.L1595
.L1607:
	.align	2
.L1606:
	.word	.LC70
	.word	.LC73
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC71
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC72
	.word	.LC83
	.word	.LC84
	UNWIND(.fnend)
	.size	pred_weight_table, .-pred_weight_table
	.align	2
	.global	DecMMCO
	.type	DecMMCO, %function
DecMMCO:
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
	mov	r9, r0
	moveq	r6, #100
	beq	.L1620
	add	r8, r0, #24576
	mov	r10, #0
	b	.L1611
.L1642:
	ldr	r1, .L1648
	mov	r0, r9
	bl	ue_v
	cmp	r4, #2
	beq	.L1640
.L1622:
	cmp	r4, #6
	orreq	r5, r5, #1
	cmp	r5, #0
	bne	.L1625
	cmp	r4, #4
	beq	.L1641
.L1626:
	cmp	r4, #6
	bhi	.L1618
.L1623:
	add	r3, r9, #61440
	ldr	r3, [r3, #2620]
	cmp	r3, #0
	bne	.L1618
	cmp	r4, #0
	beq	.L1628
.L1627:
	subs	r6, r6, #1
	beq	.L1629
.L1620:
	ldr	r1, .L1648+4
	mov	r0, r9
	bl	ue_v
	bic	r3, r0, #2
	sub	r5, r0, #3
	clz	r5, r5
	cmp	r3, #1
	mov	r4, r0
	mov	r5, r5, lsr #5
	beq	.L1642
	cmp	r4, #2
	bne	.L1622
.L1640:
	ldr	r1, .L1648+8
	mov	r0, r9
	bl	ue_v
	cmp	r5, #0
	beq	.L1623
.L1625:
	ldr	r1, .L1648+12
	mov	r0, r9
	bl	ue_v
	cmp	r4, #4
	bne	.L1626
.L1641:
	ldr	r1, .L1648+16
	mov	r0, r9
	bl	ue_v
	add	r3, r9, #61440
	ldr	r3, [r3, #2620]
	cmp	r3, #0
	beq	.L1627
.L1618:
	ldr	r1, .L1648+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1647:
	ldr	r1, .L1648
	mov	r0, r9
	bl	ue_v
	ldr	r2, [r4, #8]
	cmp	r2, #2
	str	r0, [r4, #12]
	beq	.L1643
.L1614:
	cmp	r2, #3
	cmpne	r2, #6
	beq	.L1644
.L1615:
	cmp	r2, #4
	beq	.L1645
.L1616:
	cmp	r2, #6
	bhi	.L1618
	add	r3, r9, #61440
	ldr	r3, [r3, #2620]
	cmp	r3, #0
	bne	.L1618
	cmp	r2, #0
	add	r10, r10, #1
	beq	.L1628
	cmp	r10, #100
	beq	.L1646
.L1611:
	ldr	r1, .L1648+4
	mov	r0, r9
	ldr	r5, [r8, #1804]
	bl	ue_v
	mov	r6, r10, asl #2
	mov	r7, r10, asl #4
	add	r4, r6, r7
	movw	r3, #2004
	mla	r4, r3, r5, r4
	add	r4, r9, r4
	add	r4, r4, #22272
	add	r4, r4, #96
	bic	r1, r0, #2
	str	r0, [r4, #8]
	cmp	r1, #1
	mov	r2, r0
	beq	.L1647
	cmp	r2, #2
	bne	.L1614
.L1643:
	ldr	r1, .L1648+8
	mov	r0, r9
	bl	ue_v
	add	r3, r6, r7
	movw	r2, #2004
	mla	r3, r2, r5, r3
	add	r3, r9, r3
	add	r2, r3, #22272
	str	r0, [r2, #112]
	ldr	r2, [r2, #104]
	cmp	r2, #3
	cmpne	r2, #6
	bne	.L1615
.L1644:
	ldr	r1, .L1648+12
	mov	r0, r9
	bl	ue_v
	add	r3, r6, r7
	movw	r2, #2004
	mla	r3, r2, r5, r3
	add	r3, r9, r3
	add	r2, r3, #22272
	str	r0, [r2, #116]
	ldr	r2, [r2, #104]
	cmp	r2, #4
	bne	.L1616
.L1645:
	ldr	r1, .L1648+16
	mov	r0, r9
	bl	ue_v
	add	r6, r6, r7
	movw	r7, #2004
	mla	r5, r7, r5, r6
	add	r5, r9, r5
	add	r3, r5, #22272
	add	r5, r3, #96
	ldr	r2, [r3, #104]
	str	r0, [r3, #120]
	b	.L1616
.L1628:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1646:
	ldr	r1, .L1648+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1629:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1649:
	.align	2
.L1648:
	.word	.LC87
	.word	.LC86
	.word	.LC88
	.word	.LC89
	.word	.LC90
	.word	.LC91
	.word	.LC85
	UNWIND(.fnend)
	.size	DecMMCO, .-DecMMCO
	.align	2
	.global	dec_ref_pic_marking
	.type	dec_ref_pic_marking, %function
dec_ref_pic_marking:
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
	add	r6, r0, #24576
	cmp	r0, #0
	mov	r5, r0
	ldr	r7, [r6, #1804]
	beq	.L1670
	add	r3, r0, #20480
	ldrb	r8, [r3, #213]	@ zero_extendqisi2
	cmp	r8, #0
	bne	.L1671
	movw	r4, #2004
	mla	r4, r4, r7, r0
	add	r4, r4, #22272
	add	r4, r4, #96
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1672
	ldrb	r3, [r3, #211]	@ zero_extendqisi2
	mov	r4, r7
	cmp	r3, #5
	beq	.L1673
.L1654:
	ldr	r1, .L1677
	mov	r0, r5
	bl	u_1
	movw	r1, #2004
	mla	r4, r1, r4, r5
	ldr	r1, .L1677+4
	add	r4, r4, #22272
	add	r4, r4, #96
	mov	r3, r0
	uxtb	r2, r0
	strb	r3, [r4, #7]
	mov	r0, #16
	bl	dprint_vfmw
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1655
.L1659:
	mov	r8, #0
.L1667:
	mov	r0, r8
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1671:
	clz	r4, r7
	mov	r4, r4, lsr #5
	str	r4, [r6, #1804]
	ldrb	r3, [r3, #211]	@ zero_extendqisi2
	cmp	r3, #5
	bne	.L1654
.L1673:
	ldr	r1, .L1677+8
	mov	r0, r5
	bl	u_1
	movw	r3, #2004
	mla	r4, r3, r4, r5
	ldr	r1, .L1677+12
	mov	r8, #0
	add	r4, r4, #22272
	strb	r0, [r4, #101]
	mov	r0, r5
	bl	u_1
	ldrb	r2, [r4, #101]	@ zero_extendqisi2
	ldr	r1, .L1677+16
	strb	r0, [r4, #102]
	mov	r0, #16
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1672:
	ldrb	r3, [r3, #211]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1674
	ldr	r1, .L1677
	ldrb	r6, [r4, #7]	@ zero_extendqisi2
	bl	u_1
	cmp	r6, r0
	bne	.L1675
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1659
	mov	r1, r8
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	DecMMCO
.L1655:
	mov	r0, r5
	mov	r1, #1
	bl	DecMMCO
	cmn	r0, #1
	mov	r8, r0
	movne	r3, #1
	movne	r8, #0
	strneb	r3, [r4, #4]
	bne	.L1667
	mov	r3, #0
	ldr	r1, .L1677+20
	strb	r3, [r4, #4]
	mov	r0, #1
	str	r7, [r6, #1804]
	bl	dprint_vfmw
	b	.L1667
.L1674:
	ldr	r1, .L1677+8
	ldrb	r6, [r4, #5]	@ zero_extendqisi2
	bl	u_1
	cmp	r6, r0
	bne	.L1676
	mov	r0, r5
	ldr	r1, .L1677+12
	ldrb	r4, [r4, #6]	@ zero_extendqisi2
	bl	u_1
	cmp	r4, r0
	beq	.L1659
	ldr	r1, .L1677+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1667
.L1675:
	add	r5, r5, #61440
	ldr	r1, .L1677+28
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	ldr	ip, [r5, #2624]
	ldr	r3, [r5, #2660]
	mov	r0, #1
	ldr	r2, [r5, #2644]
	ldr	r1, .L1677+32
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1667
.L1676:
	ldr	r1, .L1677+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1667
.L1670:
	movw	r3, #8284
	ldr	r2, .L1677+40
	ldr	r1, .L1677+44
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L1667
.L1678:
	.align	2
.L1677:
	.word	.LC95
	.word	.LC96
	.word	.LC92
	.word	.LC93
	.word	.LC94
	.word	.LC97
	.word	.LC99
	.word	.LC100
	.word	.LC101
	.word	.LC98
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	dec_ref_pic_marking, .-dec_ref_pic_marking
	.align	2
	.global	ProcessSliceHeaderFirstPart
	.type	ProcessSliceHeaderFirstPart, %function
ProcessSliceHeaderFirstPart:
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
	subs	r6, r0, #0
	beq	.L1745
	ldr	r1, .L1755
	add	r5, r6, #12288
	bl	ue_v
	ldr	r3, [r5, #1292]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r10, r0
	bhi	.L1682
	add	r8, r6, #61440
	ldr	r3, [r8, #2620]
	cmp	r3, #0
	bne	.L1682
	mov	r1, r0
	mov	r0, r6
	bl	PPSSPSCheckTmpId
	subs	r9, r0, #0
	bne	.L1746
	add	r4, r6, #20480
	mov	r7, #2208
	mov	r1, #4000
	str	r10, [r4, #216]
	ldr	r2, [r5, #1304]
	ldr	r3, [r5, #1300]
	mla	r7, r7, r10, r2
	ldrb	r2, [r4, #211]	@ zero_extendqisi2
	cmp	r2, #5
	ldr	r2, [r7, #28]
	mla	r5, r1, r2, r3
	beq	.L1685
	ldr	r3, [r5, #3244]
	cmp	r3, #0
	beq	.L1685
.L1686:
	ldr	r1, [r5, #2196]
	mov	r0, r6
	ldr	r2, .L1755+4
	add	r1, r1, #4
	bl	u_v
	str	r0, [r4, #224]
	ldr	r3, [r8, #2620]
	cmp	r3, #0
	bne	.L1743
	ldrb	r3, [r4, #211]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1747
.L1689:
	mov	r3, #0
	strb	r3, [r4, #209]
	strb	r3, [r4, #210]
	ldrb	r3, [r5, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1748
	ldr	r2, [r5, #3248]
	ldr	r1, [r5, #3252]
	add	r3, r2, #1
	mla	r3, r1, r3, r3
.L1713:
	ldrb	r2, [r5, #19]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1696
	strb	r2, [r4, #212]
.L1698:
	ldr	r2, [r4, #256]
	cmp	r2, r3
	bcs	.L1749
.L1699:
	ldrb	r3, [r4, #211]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1750
.L1701:
	add	r10, r6, #16384
	mov	r3, #0
	str	r3, [r10, #3420]
	str	r3, [r10, #3424]
	ldr	r3, [r5, #2200]
	cmp	r3, #0
	beq	.L1751
.L1705:
	mov	r3, #0
	str	r3, [r10, #3468]
	str	r3, [r10, #3472]
	ldr	r3, [r5, #2200]
	cmp	r3, #1
	beq	.L1752
.L1708:
	ldr	r3, [r8, #2620]
	cmp	r3, #0
	bne	.L1743
	ldrb	r3, [r7, #17]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1711
	ldr	r1, .L1755+8
	mov	r0, r6
	bl	ue_v
	cmp	r0, #0
	bne	.L1712
	ldr	r3, [r8, #2620]
	cmp	r3, #0
	bne	.L1712
.L1711:
	mov	r0, r6
	bl	IsNewPic
	uxtb	r0, r0
	strb	r0, [r4, #213]
	cmp	r0, #0
	bne	.L1725
	ldr	r2, [r4, #256]
	ldr	r3, [r4, #1888]
	cmp	r2, r3
	bls	.L1753
.L1725:
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1685:
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1686
	ldr	r1, .L1755+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r9, #0
	b	.L1725
.L1696:
	mov	r2, #1
	strb	r2, [r4, #212]
.L1716:
	ldr	r2, [r4, #256]
	cmp	r2, r3, lsr #1
	bcc	.L1699
	ldr	r1, .L1755+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r9, #0
	b	.L1725
.L1712:
	ldr	r1, .L1755+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L1755+24
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L1743
	mov	r3, #0
	ldr	r0, [r8, #2680]
	mov	r2, r3
	mov	r1, #102
	blx	r4
.L1743:
	mvn	r9, #0
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1748:
	ldr	r1, .L1755+28
	mov	r0, r6
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #209]
	cmp	r0, #0
	bne	.L1754
	ldr	r2, [r5, #3248]
	ldrb	ip, [r5, #18]	@ zero_extendqisi2
	ldr	r1, [r5, #3252]
	add	r3, r2, #1
	cmp	ip, #0
	mla	r3, r1, r3, r3
	bne	.L1715
	mov	r3, r3, asl #1
	b	.L1713
.L1751:
	ldr	r1, [r5, #2204]
	mov	r0, r6
	ldr	r2, .L1755+32
	add	r1, r1, #4
	bl	u_v
	str	r0, [r10, #3420]
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1705
	ldrb	r3, [r4, #209]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1705
	ldr	r1, .L1755+36
	mov	r0, r6
	bl	se_v
	str	r0, [r10, #3424]
	b	.L1705
.L1747:
	cmp	r0, #0
	str	r0, [r4, #220]
	beq	.L1689
	ldr	r1, .L1755+40
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1689
.L1752:
	ldrb	r3, [r5, #16]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1708
	ldr	r1, .L1755+44
	mov	r0, r6
	bl	se_v
	str	r0, [r10, #3468]
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1708
	ldrb	r3, [r4, #209]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1708
	ldr	r1, .L1755+48
	mov	r0, r6
	bl	se_v
	str	r0, [r10, #3472]
	b	.L1708
.L1754:
	ldr	r1, .L1755+52
	mov	r0, r6
	bl	u_1
	strb	r0, [r4, #210]
	ldr	r2, [r5, #3248]
	ldrb	r0, [r5, #18]	@ zero_extendqisi2
	ldr	r1, [r5, #3252]
	add	r3, r2, #1
	cmp	r0, #0
	ldrb	r0, [r4, #209]	@ zero_extendqisi2
	mla	r3, r1, r3, r3
	moveq	r2, #2
	beq	.L1694
.L1715:
	mov	r2, #1
.L1694:
	cmp	r0, #0
	mul	r3, r2, r3
	beq	.L1713
	cmp	r0, #1
	mov	r2, #0
	strb	r2, [r4, #212]
	bne	.L1698
	b	.L1716
.L1750:
	ldr	r1, .L1755+56
	mov	r0, r6
	bl	ue_v
	cmp	r0, #65536
	str	r0, [r4, #244]
	bcs	.L1702
	ldr	r3, [r8, #2620]
	cmp	r3, #0
	beq	.L1701
.L1702:
	ldr	r1, .L1755+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1701
.L1682:
	mov	r2, r10
	ldr	r1, .L1755+64
	mvn	r9, #0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1746:
	ldr	r1, .L1755+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r9, #0
	b	.L1725
.L1745:
	movw	r3, #8378
	ldr	r2, .L1755+72
	ldr	r1, .L1755+76
	mvn	r9, #0
	bl	dprint_vfmw
	b	.L1725
.L1749:
	ldr	r1, .L1755+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r9, #0
	b	.L1725
.L1753:
	ldr	r1, .L1755+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r9, #0
	b	.L1725
.L1756:
	.align	2
.L1755:
	.word	.LC102
	.word	.LC106
	.word	.LC118
	.word	.LC105
	.word	.LC110
	.word	.LC119
	.word	g_event_report
	.word	.LC108
	.word	.LC114
	.word	.LC115
	.word	.LC107
	.word	.LC116
	.word	.LC117
	.word	.LC109
	.word	.LC112
	.word	.LC113
	.word	.LC103
	.word	.LC104
	.word	.LC8
	.word	.LC9
	.word	.LC111
	.word	.LC120
	UNWIND(.fnend)
	.size	ProcessSliceHeaderFirstPart, .-ProcessSliceHeaderFirstPart
	.align	2
	.global	ProcessSliceHeaderSecondPart
	.type	ProcessSliceHeaderSecondPart, %function
ProcessSliceHeaderSecondPart:
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
	subs	r5, r0, #0
	beq	.L1842
	add	r7, r5, #12288
	add	r4, r5, #20480
	ldr	r3, [r7, #1292]
	ldr	r2, [r4, #216]
	sub	r3, r3, #1
	cmp	r3, r2
	bcc	.L1760
	add	r9, r5, #61440
	ldr	r3, [r9, #2620]
	cmp	r3, #0
	bne	.L1760
	bl	PPSSPSCheck
	cmp	r0, #0
	bne	.L1843
	ldr	r3, [r4, #216]
	mov	r6, #2208
	ldr	r8, [r7, #1304]
	mul	r6, r6, r3
	adds	r7, r8, r6
	beq	.L1844
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1845
.L1764:
	ldr	r2, [r7, #36]
	cmp	r3, #1
	str	r2, [r4, #260]
	ldr	r2, [r7, #40]
	str	r2, [r4, #264]
	bls	.L1846
	cmp	r3, #2
	beq	.L1791
.L1775:
	mov	r3, #32
	str	r3, [r4, #264]
.L1776:
	mov	r0, r5
	bl	ref_pic_list_reordering
	subs	r10, r0, #0
	bne	.L1847
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1778
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r2, #1
	moveq	r3, r2
	beq	.L1779
.L1778:
	ldr	r3, [r7, #44]
	cmp	r3, #1
	beq	.L1848
.L1795:
	mov	r2, #0
	mov	r3, r2
.L1779:
	strb	r3, [r4, #215]
	mov	r0, #19
	ldr	r1, .L1854
	bl	dprint_vfmw
	ldrb	r2, [r4, #215]	@ zero_extendqisi2
	mov	r3, #0
	str	r3, [r4, #268]
	cmp	r2, r3
	str	r3, [r4, #272]
	bne	.L1849
.L1780:
	ldr	r3, [r4, #236]
	cmp	r3, #0
	bne	.L1850
.L1781:
	mov	r3, #0
	str	r3, [r4, #1812]
	ldrb	r3, [r8, r6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1782
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L1851
.L1782:
	ldr	r1, .L1854+4
	mov	r0, r5
	bl	se_v
	mov	r3, #0
	str	r3, [r4, #1820]
	str	r3, [r4, #1824]
	str	r3, [r4, #1828]
	str	r0, [r4, #1816]
	ldrb	r3, [r7, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1852
.L1811:
	mov	r0, r10
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1791:
	mov	r3, #32
	str	r3, [r4, #260]
	b	.L1775
.L1852:
	ldr	r1, .L1854+8
	mov	r0, r5
	bl	ue_v
	cmp	r0, #2
	str	r0, [r4, #1820]
	bhi	.L1785
	ldr	r3, [r9, #2620]
	cmp	r3, #0
	bne	.L1785
	cmp	r0, #1
	beq	.L1811
	ldr	r1, .L1854+12
	mov	r0, r5
	bl	se_v
	add	r3, r0, #6
	str	r0, [r4, #1824]
	cmp	r3, #12
	bhi	.L1788
	ldr	r3, [r9, #2620]
	cmp	r3, #0
	bne	.L1788
	mov	r0, r5
	ldr	r1, .L1854+16
	bl	se_v
	add	r3, r0, #6
	str	r0, [r4, #1828]
	cmp	r3, #12
	bhi	.L1790
	ldr	r3, [r9, #2620]
	cmp	r3, #0
	beq	.L1811
.L1790:
	ldr	r1, .L1854+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1849:
	mov	r0, r5
	bl	pred_weight_table
	cmp	r0, #0
	beq	.L1780
	ldr	r1, .L1854+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1850:
	mov	r0, r5
	bl	dec_ref_pic_marking
	cmp	r0, #0
	beq	.L1781
	ldr	r1, .L1854+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1848:
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r2, r3
	bne	.L1795
	b	.L1779
.L1845:
	ldr	r1, .L1854+32
	mov	r0, r5
	bl	u_1
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	strb	r0, [r4, #214]
	b	.L1764
.L1846:
	ldr	r1, .L1854+36
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	bne	.L1766
	ldr	r3, [r4, #260]
.L1767:
	ldrb	r2, [r4, #209]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1768
	cmp	r3, #15
	bhi	.L1769
	ldr	r3, [r4, #264]
	cmp	r3, #15
	bhi	.L1853
.L1770:
	ldr	r3, [r9, #2620]
	cmp	r3, #0
	bne	.L1769
.L1771:
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1791
	cmp	r3, #1
	bne	.L1775
	b	.L1776
.L1760:
	ldr	r1, .L1854+40
	mvn	r10, #0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r10
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1851:
	ldr	r1, .L1854+44
	mov	r0, r5
	bl	ue_v
	cmp	r0, #2
	str	r0, [r4, #1812]
	bhi	.L1783
	ldr	r3, [r9, #2620]
	cmp	r3, #0
	beq	.L1782
.L1783:
	ldr	r1, .L1854+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1768:
	cmp	r3, #31
	bhi	.L1772
	ldr	r3, [r4, #264]
	cmp	r3, #31
	bls	.L1773
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1773
.L1772:
	ldr	r1, .L1854+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1773:
	ldr	r3, [r9, #2620]
	cmp	r3, #0
	beq	.L1771
	b	.L1772
.L1853:
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1770
.L1769:
	ldr	r1, .L1854+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1766:
	ldr	r1, .L1854+60
	mov	r0, r5
	bl	ue_v
	ldrb	r2, [r4, #208]	@ zero_extendqisi2
	cmp	r2, #1
	mov	r3, r0
	str	r0, [r4, #260]
	bne	.L1767
	ldr	r1, .L1854+64
	mov	r0, r5
	bl	ue_v
	ldr	r3, [r4, #260]
	str	r0, [r4, #264]
	b	.L1767
.L1788:
	ldr	r1, .L1854+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1785:
	ldr	r1, .L1854+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1843:
	ldr	r1, .L1854+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1847:
	ldr	r1, .L1854+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1811
.L1842:
	movw	r3, #8542
	ldr	r2, .L1854+84
	ldr	r1, .L1854+88
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L1811
.L1844:
	movw	r3, #8559
	ldr	r2, .L1854+84
	ldr	r1, .L1854+88
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L1811
.L1855:
	.align	2
.L1854:
	.word	.LC128
	.word	.LC133
	.word	.LC134
	.word	.LC136
	.word	.LC138
	.word	.LC139
	.word	.LC129
	.word	.LC130
	.word	.LC121
	.word	.LC122
	.word	.LC103
	.word	.LC131
	.word	.LC132
	.word	.LC126
	.word	.LC125
	.word	.LC123
	.word	.LC124
	.word	.LC137
	.word	.LC135
	.word	.LC104
	.word	.LC127
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	ProcessSliceHeaderSecondPart, .-ProcessSliceHeaderSecondPart
	.align	2
	.global	ExitSlice
	.type	ExitSlice, %function
ExitSlice:
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
	subs	r2, r0, #0
	beq	.L1865
	add	r3, r2, #20480
	add	r0, r2, #12288
	mov	ip, #2208
	mov	r7, #4000
	ldr	r1, [r0, #1304]
	ldr	r6, [r3, #216]
	ldr	r4, [r0, #1300]
	ldrb	r5, [r3, #209]	@ zero_extendqisi2
	mla	r0, ip, r6, r1
	cmp	r5, #0
	ldr	ip, [r3, #224]
	ldr	lr, [r3, #256]
	ldr	r1, [r0, #28]
	str	r6, [r3, #1856]
	mla	r1, r7, r1, r4
	ldr	r0, [r1, #36]
	str	ip, [r3, #1864]
	ldr	ip, [r3, #236]
	str	r0, [r3, #1852]
	ldrneb	r0, [r3, #210]	@ zero_extendqisi2
	str	lr, [r3, #1888]
	strb	r5, [r3, #1848]
	strneb	r0, [r3, #1849]
	ldrb	r0, [r3, #211]	@ zero_extendqisi2
	str	ip, [r3, #1860]
	cmp	r0, #5
	strb	r0, [r3, #1850]
	ldreq	r0, [r3, #244]
	streq	r0, [r3, #1868]
	ldr	r0, [r1, #2200]
	cmp	r0, #0
	bne	.L1860
	add	r0, r2, #16384
	ldr	ip, [r0, #3420]
	str	ip, [r3, #1872]
	ldr	r0, [r0, #3424]
	str	r0, [r3, #1876]
	ldr	r0, [r1, #2200]
.L1860:
	cmp	r0, #1
	addeq	r1, r2, #16384
	add	r2, r2, #61440
	ldreq	r0, [r1, #3468]
	streq	r0, [r3, #1880]
	ldreq	r1, [r1, #3472]
	streq	r1, [r3, #1884]
	ldr	r3, [r2, #2636]
	add	r3, r3, #1
	str	r3, [r2, #2636]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1865:
	movw	r3, #8730
	ldr	r2, .L1866
	ldr	r1, .L1866+4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1867:
	.align	2
.L1866:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	ExitSlice, .-ExitSlice
	.align	2
	.global	PicTypeStatistic
	.type	PicTypeStatistic, %function
PicTypeStatistic:
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
	beq	.L1881
	add	r1, r3, #20480
	ldrb	r2, [r1, #208]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1871
	bcc	.L1872
	cmp	r2, #2
	ldmnefd	sp, {fp, sp, pc}
	ldrb	r2, [r1, #211]	@ zero_extendqisi2
	add	r3, r3, #57344
	cmp	r2, #5
	bne	.L1874
	mov	r2, #1
	str	r2, [r3, #4024]
	ldmfd	sp, {fp, sp, pc}
.L1872:
	add	r3, r3, #57344
	ldr	r2, [r3, #4020]
	cmp	r2, #2
	movne	r2, #1
	strne	r2, [r3, #4020]
.L1874:
	mov	r2, #0
	str	r2, [r3, #4024]
	ldmfd	sp, {fp, sp, pc}
.L1871:
	add	r3, r3, #57344
	mov	r1, #2
	mov	r2, #0
	str	r1, [r3, #4020]
	str	r2, [r3, #4024]
	ldmfd	sp, {fp, sp, pc}
.L1881:
	movw	r3, #8781
	ldr	r2, .L1882
	ldr	r1, .L1882+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L1883:
	.align	2
.L1882:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	PicTypeStatistic, .-PicTypeStatistic
	.align	2
	.global	CalcStreamBits
	.type	CalcStreamBits, %function
CalcStreamBits:
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
	subs	r4, r0, #0
	beq	.L1907
	add	r3, r4, #16384
	ldrb	r3, [r3, #1212]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1908
.L1886:
	ldr	r0, [r4, #368]
	ldrb	r6, [r0]	@ zero_extendqisi2
	cmp	r6, #0
	beq	.L1897
	mov	r5, #0
	mov	r2, r0
	mov	r3, r5
.L1888:
	add	r3, r3, #1
	ldr	r1, [r2, #12]
	cmp	r3, r6
	add	r2, r2, #28
	add	r5, r5, r1
	bne	.L1888
.L1887:
	mov	r7, r6, asl #5
	ldr	ip, [r0, #72]
	sub	r7, r7, r6, asl #2
	ldr	r2, [r0, #64]
	add	r1, r0, r7
	mov	r3, r5
	str	ip, [sp, #4]
	mov	r0, #7
	ldr	ip, [r1, #12]
	ldr	r1, .L1910
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #368]
	mov	r2, r6
	mov	r0, #7
	ldr	r1, .L1910+4
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldr	ip, [r3, #64]
	mov	lr, r6, asl #5
	and	ip, ip, r0
	sub	lr, lr, r6, asl #2
	add	r3, r3, lr
	str	ip, [r3, #24]
	ldr	r3, [r4, #368]
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldr	r8, [r3, #64]
	mov	lr, r6, asl #5
	sub	lr, lr, r6, asl #2
	add	r3, r3, lr
	ldr	ip, [r3, #16]
	add	ip, ip, r8, lsr #3
	rsb	ip, r5, ip
	str	ip, [r3, #28]
	ldr	ip, [r4, #368]
	ldrb	r6, [ip]	@ zero_extendqisi2
	ldr	lr, [ip, #64]
	mov	r3, r6, asl #5
	sub	r3, r3, r6, asl #2
	add	ip, ip, r3
	ldr	r3, [ip, #12]
	add	r3, r5, r3
	rsb	r3, lr, r3, lsl #3
	str	r3, [ip, #20]
	ldr	ip, [r4, #368]
	ldrb	lr, [ip]	@ zero_extendqisi2
	mov	r3, lr, asl #5
	sub	r3, r3, lr, asl #2
	add	r3, ip, r3
	ldr	ip, [r3, #28]
	ldr	lr, [r3, #24]
	and	ip, ip, #3
	add	ip, lr, ip, lsl #3
	str	ip, [r3, #24]
	ldr	ip, [r4, #368]
	ldrb	lr, [ip]	@ zero_extendqisi2
	mov	r3, lr, asl #5
	sub	r3, r3, lr, asl #2
	add	r3, ip, r3
	ldr	ip, [r3, #28]
	bic	ip, ip, #3
	str	ip, [r3, #28]
	ldr	ip, [r4, #368]
	add	r7, ip, r7
	ldrb	r5, [ip]	@ zero_extendqisi2
	ldr	r3, [r7, #24]
	mov	lr, r5, asl #5
	sub	lr, lr, r5, asl #2
	add	ip, ip, lr
	ldr	ip, [ip, #28]
	str	ip, [sp, #4]
	ldr	ip, [r7, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r4, #368]
	ldr	r2, [ip, #68]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L1909
	ldrb	r5, [ip]	@ zero_extendqisi2
	add	r1, r5, #1
	cmp	r2, r1
	movhi	r2, #1
	movls	r2, #0
	cmp	r1, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L1890
	add	r5, r5, #2
	mov	r6, #0
.L1891:
	sub	r3, r5, #1
	ldr	r1, .L1910+8
	mov	r0, #7
	mov	lr, r3, asl #5
	mov	r2, r3
	sub	r3, lr, r3, asl #2
	add	ip, ip, r3
	str	r6, [ip, #24]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	lr, [ip, #16]
	str	lr, [ip, #28]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	lr, [ip, #12]
	mov	lr, lr, asl #3
	str	lr, [ip, #20]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	ldr	r7, [ip, #24]
	and	lr, lr, #3
	add	lr, r7, lr, lsl #3
	str	lr, [ip, #24]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	bic	lr, lr, #3
	str	lr, [ip, #28]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	r3, [ip, #24]
	ldr	ip, [ip, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r4, #368]
	ldr	r3, [ip, #68]
	cmp	r5, #1
	cmpls	r5, r3
	add	r5, r5, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L1891
	sub	r3, r3, #1
.L1890:
	mov	r2, r3, asl #5
	ldr	r1, [ip, #72]
	sub	r3, r2, r3, asl #2
	add	ip, ip, r3
	ldr	r3, [ip, #20]
	rsb	r3, r1, r3
	str	r3, [ip, #20]
	ldr	lr, [r4, #368]
	ldrb	r1, [lr]	@ zero_extendqisi2
	ldr	ip, [lr, #68]
	cmp	r1, ip
	bcs	.L1884
	sxth	r3, r1
	add	r4, r4, #57344
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, lr, r3
.L1895:
	ldr	r2, [r3, #28]
	add	r1, r1, #1
	ldr	r0, [r4, #4048]
	add	r3, r3, #28
	cmp	r2, r0
	strcc	r2, [r4, #4048]
	ldrcc	ip, [lr, #68]
	cmp	r1, ip
	bcc	.L1895
.L1884:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1908:
	ldr	r2, [r4, #368]
	ldr	r3, [r2, #64]
	add	r3, r3, #7
	bic	r3, r3, #7
	str	r3, [r2, #64]
	ldr	r2, [r4, #368]
	ldr	r3, [r2, #72]
	sub	r3, r3, #1
	str	r3, [r2, #72]
	b	.L1886
.L1909:
	ldr	r1, .L1910+12
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L1897:
	mov	r5, r6
	b	.L1887
.L1907:
	movw	r3, #8835
	ldr	r2, .L1910+16
	ldr	r1, .L1910+20
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L1911:
	.align	2
.L1910:
	.word	.LC140
	.word	.LC141
	.word	.LC143
	.word	.LC142
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	CalcStreamBits, .-CalcStreamBits
	.align	2
	.global	IsRefListWrong
	.type	IsRefListWrong, %function
IsRefListWrong:
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
	subs	r7, r0, #0
	beq	.L1941
	add	r6, r7, #20480
	ldr	r3, [r6, #248]
	cmp	r3, #0
	beq	.L1915
	add	r5, r7, #26880
	add	r8, r7, #61440
	add	r5, r5, #240
	mov	r4, #0
	b	.L1919
.L1916:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L1918
	ldr	r3, [r6, #248]
	cmp	r4, r3
	bcs	.L1942
.L1919:
	ldr	r3, [r5, #4]!
	add	r4, r4, #1
	ldr	r0, [r8, #2680]
	ldr	r3, [r3, #36]
	ldr	r1, [r3, #656]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L1916
.L1918:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1942:
	cmp	r3, #0
	beq	.L1915
	ldr	r3, [r6, #252]
	cmp	r3, #0
	addne	r7, r7, #27136
	movne	r4, #0
	addne	r7, r7, #116
	bne	.L1922
	b	.L1915
.L1943:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L1918
	ldr	r3, [r6, #252]
	cmp	r4, r3
	bcs	.L1915
.L1922:
	ldr	r3, [r7, #4]!
	add	r4, r4, #1
	ldr	r0, [r8, #2680]
	ldr	r3, [r3, #36]
	ldr	r1, [r3, #656]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L1943
	b	.L1918
.L1915:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1941:
	movw	r3, #8944
	ldr	r2, .L1944
	ldr	r1, .L1944+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1945:
	.align	2
.L1944:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	IsRefListWrong, .-IsRefListWrong
	.align	2
	.global	Scaling_List
	.type	Scaling_List, %function
Scaling_List:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
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
	subs	r7, r3, #0
	str	r0, [fp, #-52]
	mov	r6, r2
	ble	.L1946
	mov	r3, r7
	mov	r0, #8
	ldr	r9, .L1957
	mov	r5, r0
	mov	r4, #0
	mov	r10, #255
	mov	r7, r1
	mov	r8, r3
	b	.L1951
.L1950:
	mov	ip, r3, lsr #2
	and	lr, r3, #3
	str	r5, [r7, r3, asl #2]
	uxtb	r1, r5
	ldr	r3, [r6, ip, asl #2]
	mov	lr, lr, asl #3
	cmp	r4, r8
	bic	r3, r3, r10, asl lr
	orr	r1, r3, r1, asl lr
	str	r1, [r6, ip, asl #2]
	beq	.L1946
.L1951:
	cmp	r8, #16
	ldreq	r3, .L1957+4
	ldrneb	r3, [r4, r9]	@ zero_extendqisi2
	ldreqb	r3, [r4, r3]	@ zero_extendqisi2
	cmp	r0, #0
	add	r4, r4, #1
	beq	.L1950
	ldr	r1, .L1957+8
	ldr	r0, [fp, #-52]
	str	r3, [fp, #-48]
	bl	se_v
	ldr	r2, [fp, #4]
	ldr	r3, [fp, #-48]
	add	r0, r5, r0
	ands	r0, r0, #255
	moveq	r1, #1
	movne	r1, #0
	cmp	r1, #0
	moveq	r5, r0
	cmp	r3, #0
	movne	r1, #0
	andeq	r1, r1, #1
	str	r1, [r2]
	b	.L1950
.L1946:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1958:
	.align	2
.L1957:
	.word	.LANCHOR0+40
	.word	.LANCHOR0+24
	.word	.LC144
	UNWIND(.fnend)
	.size	Scaling_List, .-Scaling_List
	.align	2
	.global	ProcessPPS
	.type	ProcessPPS, %function
ProcessPPS:
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
	subs	r5, r0, #0
	mov	r4, r1
	beq	.L2011
	cmp	r1, #0
	beq	.L2012
	ldr	r1, .L2021
	add	r6, r5, #61440
	bl	u_1
	strb	r0, [r4]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2010
	ldr	r1, .L2021+4
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #1]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2010
	ldr	r1, .L2021+8
	mov	r0, r5
	bl	ue_v
	cmp	r0, #0
	str	r0, [r4, #32]
	bne	.L1965
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	beq	.L1966
.L1965:
	ldr	r1, .L2021+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2021+16
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2010
	mov	r3, #0
	ldr	r0, [r6, #2680]
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
.L1961:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1973:
	ldr	r1, .L2021+20
	mov	r0, r5
	bl	u_1
	ldr	r1, .L2021+24
	str	r0, [r4, #60]
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #1
	beq	.L1974
.L1992:
	mov	r0, r5
	ldr	r1, .L2021+28
	bl	se_v
	add	r3, r0, #12
	str	r0, [r4, #56]
	cmp	r3, #24
	bhi	.L1975
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	beq	.L1993
.L1975:
	ldr	r1, .L2021+32
	mov	r0, #1
	bl	dprint_vfmw
.L2010:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1966:
	ldr	r1, .L2021+36
	mov	r0, r5
	bl	ue_v
	cmp	r0, #31
	str	r0, [r4, #36]
	bhi	.L1967
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L1967
	ldr	r1, .L2021+40
	mov	r0, r5
	bl	ue_v
	cmp	r0, #31
	str	r0, [r4, #40]
	bhi	.L1969
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L1969
	ldr	r1, .L2021+44
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #2]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2010
	ldr	r2, .L2021+48
	mov	r1, #2
	mov	r0, r5
	bl	u_v
	cmp	r0, #2
	str	r0, [r4, #44]
	bhi	.L2013
	ldr	r1, .L2021+52
	mov	r0, r5
	bl	se_v
	ldr	r1, .L2021+56
	str	r0, [r4, #48]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L2021+60
	mov	r0, r5
	bl	se_v
	ldr	r1, .L2021+64
	str	r0, [r4, #52]
	mov	r0, r5
	bl	u_1
	ldr	r1, .L2021+68
	strb	r0, [r4, #3]
	mov	r0, r5
	bl	u_1
	ldr	r1, .L2021+72
	strb	r0, [r4, #4]
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #17]
	cmp	r0, #0
	bne	.L2014
.L1972:
	ldr	r3, [r4, #52]
	add	r0, r5, #13504
	mov	r7, #0
	add	r0, r0, #24
	str	r7, [r4, #60]
	str	r3, [r4, #56]
	strb	r7, [r4, #18]
	bl	BsResidBits
	ldr	r3, [r5, #368]
	ldr	r3, [r3, #72]
	add	r3, r3, #3
	cmp	r0, r3
	bcs	.L1973
.L1993:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2014:
	ldr	r1, .L2021+76
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1972
.L1967:
	ldr	r1, .L2021+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1961
.L1969:
	ldr	r1, .L2021+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1961
.L1974:
	add	r3, r4, #4
	str	r6, [fp, #-80]
	sub	r9, fp, #72
	add	r8, r4, #1984
	add	r10, r4, #64
	mov	r6, r3
	b	.L1983
.L2018:
	ldr	r3, [ip, #1300]
	ldr	ip, [r4, #28]
	mla	r3, lr, ip, r3
	ldrb	ip, [r3, #25]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L2015
	ldr	r3, .L2021+88
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2021+92
	ldr	r3, [r3, #52]
	blx	r3
.L1978:
	add	r7, r7, #1
	add	r8, r8, #16
	cmp	r7, #6
	add	r10, r10, #64
	beq	.L2016
.L1983:
	ldr	r1, .L2021+96
	mov	r0, r5
	bl	u_1
	clz	r1, r7
	add	ip, r5, #12288
	mov	lr, #4000
	mov	r2, #16
	mov	r1, r1, lsr #5
	cmp	r0, #1
	mov	r3, r0
	mov	r0, r8
	str	r3, [r9, #4]!
	strb	r3, [r6, #1]!
	beq	.L2017
	cmp	r7, #0
	cmpne	r7, #3
	beq	.L2018
	ldr	r3, .L2021+92
	mov	r2, #16
	sub	r1, r8, #16
	mov	r0, r8
	ldr	r3, [r3, #52]
	blx	r3
	b	.L1978
.L2016:
	ldr	r6, [fp, #-80]
	add	r3, r4, #448
	add	r2, r5, #12288
	add	r9, r4, #2080
	sub	r8, fp, #76
	add	r10, r4, #11
	str	r5, [fp, #-80]
	mov	r7, #0
	str	r6, [fp, #-84]
	mov	r5, r2
	mov	r6, r3
.L1991:
	ldr	r2, [r4, #60]
	mov	r3, #0
	cmp	r2, #1
	strne	r3, [r8]
	strneb	r3, [r10]
	beq	.L2019
.L1986:
	ldr	r1, [r4, #28]
	mov	ip, #4000
	ldr	r3, [r5, #1300]
	mov	r0, r9
	mov	r2, #64
	mla	r3, ip, r1, r3
	ldrb	r1, [r3, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L2020
	ldr	r1, .L2021+100
	cmp	r7, #0
	ldr	r3, .L2021+92
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L1987:
	add	r7, r7, #1
	add	r9, r9, #64
	cmp	r7, #2
	add	r6, r6, #256
	add	r8, r8, #4
	add	r10, r10, #1
	bne	.L1991
	ldr	r5, [fp, #-80]
	ldr	r6, [fp, #-84]
	b	.L1992
.L2017:
	mov	r3, r2
	str	r9, [sp]
	mov	r2, r8
	mov	r1, r10
	mov	r0, r5
	bl	Scaling_List
	ldr	r3, [r9]
	cmp	r3, #1
	bne	.L1978
	ldr	r1, .L2021+88
	mov	r2, #16
	ldr	r3, .L2021+92
	cmp	r7, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r8
	blx	r3
	b	.L1978
.L2012:
	mov	r0, r1
	movw	r3, #9224
	ldr	r2, .L2021+104
	ldr	r1, .L2021+108
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1961
.L2015:
	add	r1, r3, r7, lsl #4
	ldr	r3, .L2021+92
	add	r1, r1, #1968
	mov	r2, #16
	add	r1, r1, #4
	mov	r0, r8
	ldr	r3, [r3, #52]
	blx	r3
	b	.L1978
.L2013:
	ldr	r1, .L2021+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1961
.L2019:
	ldr	r1, .L2021+116
	ldr	r0, [fp, #-80]
	bl	u_1
	mov	r2, r9
	mov	r1, r6
	mov	r3, #64
	mov	ip, r0
	cmp	ip, #1
	ldr	r0, [fp, #-80]
	str	ip, [r8]
	strb	ip, [r10]
	bne	.L1986
	str	r8, [sp]
	bl	Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L1987
	ldr	r1, .L2021+100
	mov	r2, #64
	ldr	r3, .L2021+92
	cmp	r7, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r9
	blx	r3
	b	.L1987
.L2020:
	add	r1, r3, r7, lsl #6
	ldr	r3, .L2021+92
	add	r1, r1, #2064
	add	r1, r1, #4
	ldr	r3, [r3, #52]
	blx	r3
	b	.L1987
.L2011:
	movw	r3, #9223
	ldr	r2, .L2021+104
	ldr	r1, .L2021+108
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1961
.L2022:
	.align	2
.L2021:
	.word	.LC145
	.word	.LC146
	.word	.LC147
	.word	.LC148
	.word	g_event_report
	.word	.LC163
	.word	.LC164
	.word	.LC165
	.word	.LC168
	.word	.LC149
	.word	.LC151
	.word	.LC153
	.word	.LC154
	.word	.LC156
	.word	.LC157
	.word	.LC158
	.word	.LC159
	.word	.LC160
	.word	.LC161
	.word	.LC162
	.word	.LC150
	.word	.LC152
	.word	.LANCHOR1+80
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC166
	.word	.LANCHOR1+112
	.word	.LC8
	.word	.LC9
	.word	.LC155
	.word	.LC167
	UNWIND(.fnend)
	.size	ProcessPPS, .-ProcessPPS
	.align	2
	.global	PPSEqual
	.type	PPSEqual, %function
PPSEqual:
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
	subs	r7, r0, #0
	beq	.L2046
	cmp	r1, #0
	beq	.L2047
	ldr	ip, [r1, #28]
	ldr	r3, [r7, #28]
	ldr	r0, [r7, #24]
	ldr	lr, [r1, #24]
	ldrb	r4, [r7]	@ zero_extendqisi2
	cmp	r3, ip
	cmpeq	r0, lr
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldrb	lr, [r7, #1]	@ zero_extendqisi2
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	moveq	ip, #1
	movne	ip, #0
	cmp	r4, r2
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	r4, [r7, #36]
	cmp	lr, r3
	movne	r2, #0
	andeq	r2, r0, #1
	ldr	ip, [r1, #36]
	ldr	lr, [r7, #40]
	ldr	r0, [r1, #40]
	cmp	r4, ip
	movne	r3, #0
	andeq	r3, r2, #1
	ldrb	r4, [r7, #2]	@ zero_extendqisi2
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	lr, r0
	movne	ip, #0
	andeq	ip, r3, #1
	ldr	lr, [r7, #44]
	ldr	r3, [r1, #44]
	cmp	r4, r2
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	r4, [r7, #48]
	ldr	ip, [r1, #48]
	cmp	lr, r3
	movne	r2, #0
	andeq	r2, r0, #1
	ldr	lr, [r7, #52]
	ldr	r0, [r1, #52]
	cmp	r4, ip
	movne	r3, #0
	andeq	r3, r2, #1
	ldrb	r5, [r7, #3]	@ zero_extendqisi2
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	cmp	lr, r0
	movne	ip, #0
	andeq	ip, r3, #1
	ldrb	r4, [r7, #4]	@ zero_extendqisi2
	ldrb	lr, [r1, #4]	@ zero_extendqisi2
	cmp	r5, r2
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	r3, [r1, #60]
	ldr	ip, [r7, #60]
	cmp	r4, lr
	movne	r2, #0
	andeq	r2, r0, #1
	ldrb	r0, [r7, #18]	@ zero_extendqisi2
	ldrb	lr, [r1, #18]	@ zero_extendqisi2
	cmp	ip, r3
	movne	r3, #0
	andeq	r3, r2, #1
	cmp	lr, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #0
	beq	.L2027
	mov	ip, ip, asl #1
	adds	r2, ip, #6
	str	r2, [fp, #-52]
	beq	.L2027
	add	r2, r7, #4
	sub	r9, r7, #1088
	sub	r8, r1, #1088
	sub	r9, r9, #4
	mov	r0, r2
	sub	r8, r8, #4
	add	r2, r1, #4
	add	r10, r1, #64
	str	r2, [fp, #-48]
	sub	r2, r7, #836
	mov	r6, #0
	mov	r4, r7
	mov	r5, r0
	str	r7, [fp, #-56]
	str	r1, [fp, #-60]
.L2031:
	ldr	r0, [fp, #-48]
	ldrb	r1, [r5, #1]!	@ zero_extendqisi2
	ldrsb	ip, [r0, #1]!
	str	r0, [fp, #-48]
	sxtb	r0, r1
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r1, #0
	beq	.L2045
	cmp	r6, #5
	bhi	.L2032
	add	r7, r4, #64
	add	r4, r4, #128
	mov	r0, r10
	mov	r1, r7
.L2030:
	ldr	lr, [r1], #4
	ldr	ip, [r0], #4
	cmp	lr, ip
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r1, r4
	bne	.L2030
.L2028:
	ldr	r1, [fp, #-52]
	add	r6, r6, #1
	add	r9, r9, #256
	add	r8, r8, #256
	cmp	r6, r1
	add	r2, r2, #256
	mov	r4, r7
	add	r10, r10, #64
	bne	.L2031
	ldr	r7, [fp, #-56]
	ldr	r1, [fp, #-60]
.L2027:
	ldr	r0, [r7, #56]
	ldr	r2, [r1, #56]
	cmp	r0, r2
	movne	r0, #0
	andeq	r0, r3, #1
	eor	r0, r0, #1
	rsb	r0, r0, #0
.L2025:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2032:
	mov	r0, r8
	mov	r1, r9
.L2029:
	ldr	lr, [r1, #4]!
	ldr	ip, [r0, #4]!
	cmp	lr, ip
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r1
	bne	.L2029
.L2045:
	add	r7, r4, #64
	b	.L2028
.L2047:
	mov	r0, r1
	movw	r3, #9410
	ldr	r2, .L2048
	ldr	r1, .L2048+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2025
.L2046:
	movw	r3, #9409
	ldr	r2, .L2048
	ldr	r1, .L2048+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2025
.L2049:
	.align	2
.L2048:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	PPSEqual, .-PPSEqual
	.align	2
	.global	H264_DecPPS
	.type	H264_DecPPS, %function
H264_DecPPS:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r5, r0, #0
	beq	.L2064
	ldr	r1, .L2070
	add	r4, r5, #12288
	bl	ue_v
	ldr	r3, [r4, #1292]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r6, r0
	bhi	.L2065
	ldr	r1, .L2070+4
	mov	r0, r5
	bl	ue_v
	ldr	r3, [r4, #1288]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r2, r0
	bhi	.L2066
	ldr	r1, [r4, #1300]
	mov	r3, #4000
	mla	r3, r3, r0, r1
	ldrb	r3, [r3, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2067
	mov	r8, #2208
	ldr	r3, [r4, #1304]
	mul	r7, r8, r6
	add	r3, r3, r7
	ldrb	r9, [r3, #19]	@ zero_extendqisi2
	cmp	r9, #0
	beq	.L2056
	ldr	r9, .L2070+8
	mov	r0, r5
	mov	r1, r9
	str	r6, [r9, #24]
	str	r2, [r9, #28]
	bl	ProcessPPS
	subs	r5, r0, #0
	bne	.L2068
	ldr	r1, [r4, #1304]
	mov	r0, r9
	add	r1, r1, r7
	bl	PPSEqual
	cmp	r0, #0
	beq	.L2052
	ldr	ip, .L2070+12
	mov	r3, #1
	ldr	r0, [r4, #1304]
	mov	r2, r8
	strb	r3, [r9, #20]
	mov	r1, r9
	add	r0, r0, r7
	ldr	r4, [ip, #56]
	strb	r3, [r9, #19]
	blx	r4
	mov	r0, r5
	b	.L2052
.L2065:
	ldr	r1, .L2070+16
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #1292]
	sub	r2, r3, #1
	cmp	r6, r2
	bls	.L2060
	ldr	r2, .L2070+20
	ldr	r4, [r2]
	cmp	r4, #0
	beq	.L2060
	add	r5, r5, #61440
	str	r3, [fp, #-40]
	str	r6, [fp, #-44]
	mov	r3, #8
	ldr	r0, [r5, #2680]
	sub	r2, fp, #44
	mov	r1, #110
	blx	r4
	mvn	r0, #0
.L2052:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2056:
	str	r6, [r3, #24]
	mov	r0, r5
	ldr	r3, [r4, #1304]
	add	r3, r3, r7
	str	r2, [r3, #28]
	ldr	r1, [r4, #1304]
	add	r1, r1, r7
	bl	ProcessPPS
	cmp	r0, #0
	bne	.L2069
	ldr	r3, [r4, #1304]
	mov	r2, #1
	add	r3, r3, r7
	strb	r2, [r3, #20]
	ldr	r3, [r4, #1304]
	add	r7, r3, r7
	strb	r2, [r7, #19]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2060:
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2068:
	ldr	r2, .L2070+24
	mov	r0, #1
	ldr	r1, .L2070+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2052
.L2066:
	ldr	r1, .L2070+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2052
.L2067:
	ldr	r1, .L2070+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2052
.L2064:
	movw	r3, #9477
	ldr	r2, .L2070+40
	ldr	r1, .L2070+44
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2052
.L2069:
	ldr	r2, .L2070+24
	mov	r0, #1
	ldr	r1, .L2070+48
	bl	dprint_vfmw
	ldr	r3, [r4, #1304]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r7
	strb	r2, [r3, #20]
	ldr	r3, [r4, #1304]
	add	r7, r3, r7
	strb	r9, [r7, #19]
	b	.L2052
.L2071:
	.align	2
.L2070:
	.word	.LC169
	.word	.LC171
	.word	.LANCHOR2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC170
	.word	g_event_report
	.word	.LANCHOR0+104
	.word	.LC174
	.word	.LC172
	.word	.LC173
	.word	.LC8
	.word	.LC9
	.word	.LC175
	UNWIND(.fnend)
	.size	H264_DecPPS, .-H264_DecPPS
	.align	2
	.global	vui_parameters
	.type	vui_parameters, %function
vui_parameters:
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
	beq	.L2116
	ldr	r1, .L2123
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	streqb	r0, [r5, #15]
	bne	.L2117
.L2076:
	ldr	r1, .L2123+4
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	bne	.L2118
.L2077:
	ldr	r1, .L2123+8
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #3]
	cmp	r0, #0
	moveq	r3, #5
	streq	r3, [r5, #28]
	bne	.L2119
.L2079:
	ldr	r1, .L2123+12
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #6]
	cmp	r0, #0
	bne	.L2120
.L2080:
	ldr	r1, .L2123+16
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #8]
	cmp	r0, #0
	bne	.L2121
.L2082:
	ldr	r1, .L2123+20
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #7]
	cmp	r0, #0
	beq	.L2084
	ldr	r1, .L2123+24
	mov	r0, r4
	bl	ue_v
	ldr	r2, .L2123+28
	mov	r1, #4
	str	r0, [r5, #120]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+32
	mov	r1, #4
	strb	r0, [r5, #116]
	mov	r0, r4
	bl	u_v
	ldr	r3, [r5, #120]
	cmp	r3, #31
	strb	r0, [r5, #117]
	bhi	.L2086
	add	r9, r4, #61440
	ldr	r6, [r9, #2620]
	cmp	r6, #0
	bne	.L2086
	add	r7, r5, #120
	add	r8, r5, #83
.L2087:
	ldr	r1, .L2123+36
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #120]
	cmp	r3, r6
	bcs	.L2087
	ldr	r2, .L2123+48
	mov	r1, #5
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+52
	mov	r1, #5
	str	r0, [r5, #380]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+56
	mov	r1, #5
	str	r0, [r5, #384]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+60
	mov	r1, #5
	str	r0, [r5, #388]
	mov	r0, r4
	bl	u_v
	str	r0, [r5, #392]
.L2084:
	ldr	r1, .L2123+64
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #10]
	cmp	r0, #0
	bne	.L2122
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	add	r9, r4, #61440
	cmp	r3, #0
	bne	.L2092
.L2091:
	ldr	r1, .L2123+68
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2123+72
	strb	r0, [r5, #11]
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #12]
	cmp	r0, #0
	bne	.L2093
	ldr	r0, [r9, #2620]
.L2094:
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2122:
	ldr	r1, .L2123+24
	mov	r0, r4
	bl	ue_v
	ldr	r2, .L2123+28
	mov	r1, #4
	str	r0, [r5, #432]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+32
	mov	r1, #4
	strb	r0, [r5, #428]
	mov	r0, r4
	bl	u_v
	ldr	r3, [r5, #432]
	cmp	r3, #31
	strb	r0, [r5, #429]
	bhi	.L2086
	add	r9, r4, #61440
	ldr	r6, [r9, #2620]
	cmp	r6, #0
	bne	.L2086
	add	r8, r5, #392
	add	r7, r5, #432
	add	r8, r8, #3
.L2089:
	ldr	r1, .L2123+36
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #432]
	cmp	r3, r6
	bcs	.L2089
	ldr	r2, .L2123+48
	mov	r1, #5
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+52
	mov	r1, #5
	str	r0, [r5, #692]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+56
	mov	r1, #5
	str	r0, [r5, #696]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+60
	mov	r1, #5
	str	r0, [r5, #700]
	mov	r0, r4
	bl	u_v
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r5, #704]
	bne	.L2092
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2091
.L2092:
	ldr	r1, .L2123+76
	mov	r0, r4
	bl	u_1
	strb	r0, [r5, #14]
	b	.L2091
.L2121:
	ldr	r2, .L2123+80
	mov	r1, #32
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+84
	mov	r1, #32
	str	r0, [r5, #52]
	mov	r0, r4
	bl	u_v
	ldr	r1, .L2123+88
	str	r0, [r5, #56]
	mov	r0, r4
	bl	u_1
	ldr	r2, [r5, #52]
	cmp	r2, #0
	strb	r0, [r5, #9]
	beq	.L2082
	ldr	r0, [r5, #56]
	movw	r1, #10000
	ldr	r3, .L2123+92
	add	r9, r4, #61440
	umull	r0, r1, r0, r1
	ldr	r3, [r3, #244]
	movs	r1, r1, lsr #1
	mov	r0, r0, rrx
	blx	r3
	movw	r3, #52429
	movt	r3, 52428
	add	r0, r0, #5
	umull	r0, r1, r0, r3
	mov	r3, r1, lsr #3
	str	r3, [r9, #1388]
	b	.L2082
.L2120:
	ldr	r1, .L2123+96
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+100
	str	r0, [r5, #44]
	mov	r0, r4
	bl	ue_v
	str	r0, [r5, #48]
	b	.L2080
.L2119:
	ldr	r2, .L2123+104
	mov	r1, #3
	mov	r0, r4
	bl	u_v
	ldr	r1, .L2123+108
	str	r0, [r5, #28]
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2123+112
	strb	r0, [r5, #4]
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #5]
	cmp	r0, #0
	beq	.L2079
	ldr	r2, .L2123+116
	mov	r1, #8
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+120
	mov	r1, #8
	str	r0, [r5, #32]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+124
	mov	r1, #8
	str	r0, [r5, #36]
	mov	r0, r4
	bl	u_v
	str	r0, [r5, #40]
	b	.L2079
.L2118:
	ldr	r1, .L2123+128
	mov	r0, r4
	bl	u_1
	strb	r0, [r5, #2]
	b	.L2077
.L2117:
	ldr	r2, .L2123+132
	mov	r1, #8
	mov	r0, r4
	bl	u_v
	uxtb	r0, r0
	strb	r0, [r5, #15]
	cmp	r0, #255
	bne	.L2076
	ldr	r2, .L2123+136
	mov	r1, #16
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2123+140
	mov	r1, #16
	str	r0, [r5, #16]
	mov	r0, r4
	bl	u_v
	str	r0, [r5, #20]
	b	.L2076
.L2093:
	ldr	r1, .L2123+144
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2123+148
	strb	r0, [r5, #13]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+152
	str	r0, [r5, #60]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+156
	str	r0, [r5, #64]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+160
	str	r0, [r5, #72]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+164
	str	r0, [r5, #68]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L2123+168
	str	r0, [r5, #76]
	mov	r0, r4
	bl	ue_v
	str	r0, [r5, #80]
	ldr	r0, [r9, #2620]
	cmp	r0, #0
	beq	.L2094
.L2116:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2086:
	ldr	r1, .L2123+172
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2116
.L2124:
	.align	2
.L2123:
	.word	.LC176
	.word	.LC180
	.word	.LC182
	.word	.LC189
	.word	.LC192
	.word	.LC196
	.word	.LC197
	.word	.LC198
	.word	.LC199
	.word	.LC201
	.word	.LC202
	.word	.LC203
	.word	.LC204
	.word	.LC205
	.word	.LC206
	.word	.LC207
	.word	.LC208
	.word	.LC210
	.word	.LC211
	.word	.LC209
	.word	.LC193
	.word	.LC194
	.word	.LC195
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC190
	.word	.LC191
	.word	.LC183
	.word	.LC184
	.word	.LC185
	.word	.LC186
	.word	.LC187
	.word	.LC188
	.word	.LC181
	.word	.LC177
	.word	.LC178
	.word	.LC179
	.word	.LC212
	.word	.LC213
	.word	.LC214
	.word	.LC215
	.word	.LC216
	.word	.LC217
	.word	.LC218
	.word	.LC200
	UNWIND(.fnend)
	.size	vui_parameters, .-vui_parameters
	.align	2
	.global	SPSEqual
	.type	SPSEqual, %function
SPSEqual:
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
	subs	r6, r0, #0
	beq	.L2157
	cmp	r1, #0
	beq	.L2158
	ldrb	lr, [r1]	@ zero_extendqisi2
	ldrb	r3, [r6]	@ zero_extendqisi2
	ldr	ip, [r6, #28]
	ldr	r2, [r1, #28]
	ldrb	r0, [r6, #1]	@ zero_extendqisi2
	cmp	r3, lr
	cmpeq	ip, r2
	ldrb	r5, [r1, #1]	@ zero_extendqisi2
	ldrb	r2, [r6, #2]	@ zero_extendqisi2
	ldrb	r4, [r1, #2]	@ zero_extendqisi2
	moveq	lr, #1
	movne	lr, #0
	ldr	r3, [r6, #32]
	cmp	r0, r5
	movne	ip, #0
	andeq	ip, lr, #1
	ldr	r5, [r1, #32]
	cmp	r2, r4
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	lr, [r1, #36]
	ldr	r4, [r6, #36]
	cmp	r3, r5
	movne	r2, #0
	andeq	r2, r0, #1
	ldrb	ip, [r1, #25]	@ zero_extendqisi2
	ldrb	r0, [r6, #25]	@ zero_extendqisi2
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r2, #1
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #0
	beq	.L2129
	add	r2, r6, #3
	sub	r0, r1, #1104
	str	r2, [fp, #-48]
	add	r2, r1, #3
	add	r9, r1, #48
	sub	r10, r6, #1104
	sub	r4, r6, #848
	mov	r8, r6
	str	r6, [fp, #-52]
	mov	r7, #0
	mov	r5, r0
	mov	r6, r2
	str	r1, [fp, #-56]
.L2133:
	ldr	r1, [fp, #-48]
	ldrsb	r0, [r6, #1]!
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-48]
	sxtb	r1, r2
	cmp	r0, r1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, #0
	beq	.L2130
	cmp	r7, #5
	bhi	.L2140
	add	r2, r8, #48
	add	lr, r8, #112
	mov	r1, r9
.L2132:
	ldr	ip, [r2, #4]!
	ldr	r0, [r1, #4]!
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, lr
	bne	.L2132
.L2130:
	add	r7, r7, #1
	add	r10, r10, #256
	cmp	r7, #8
	add	r5, r5, #256
	add	r4, r4, #256
	add	r8, r8, #64
	add	r9, r9, #64
	bne	.L2133
	ldr	r6, [fp, #-52]
	ldr	r1, [fp, #-56]
.L2129:
	ldr	r2, [r1, #2196]
	ldr	ip, [r6, #2200]
	ldr	r0, [r1, #2200]
	ldr	lr, [r6, #2196]
	cmp	ip, r0
	cmpeq	lr, r2
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #0
	and	r3, r3, r2
	beq	.L2135
	cmp	ip, #1
	bne	.L2134
	ldr	r0, [r1, #2208]
	ldr	ip, [r6, #2208]
	ldrb	r2, [r6, #16]	@ zero_extendqisi2
	ldrb	r4, [r1, #16]	@ zero_extendqisi2
	ldr	lr, [r6, #2212]
	cmp	ip, r0
	cmpeq	r2, r4
	ldr	r2, [r1, #2212]
	ldr	r5, [r6, #2216]
	ldr	ip, [r1, #2216]
	moveq	r0, #1
	movne	r0, #0
	cmp	lr, r2
	movne	r2, #0
	andeq	r2, r0, #1
	cmp	r5, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r5, #0
	and	r3, r3, r2
	beq	.L2134
	add	ip, r6, #2208
	add	r0, r1, #2208
	add	ip, ip, #8
	add	r0, r0, #8
	mov	r2, #0
.L2137:
	ldr	r4, [ip, #4]!
	add	r2, r2, #1
	ldr	lr, [r0, #4]!
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r5
	bne	.L2137
.L2134:
	ldrb	lr, [r6, #17]	@ zero_extendqisi2
	ldrb	r0, [r1, #17]	@ zero_extendqisi2
	ldr	r2, [r6, #3244]
	ldr	r4, [r1, #3244]
	ldr	r7, [r6, #3248]
	cmp	lr, r0
	cmpeq	r2, r4
	ldr	r2, [r1, #3248]
	ldr	r5, [r6, #3252]
	ldr	r4, [r1, #3252]
	moveq	ip, #1
	movne	ip, #0
	ldrb	lr, [r1, #18]	@ zero_extendqisi2
	cmp	r7, r2
	movne	r0, #0
	andeq	r0, ip, #1
	ldrb	ip, [r6, #18]	@ zero_extendqisi2
	cmp	r5, r4
	movne	r2, #0
	andeq	r2, r0, #1
	cmp	lr, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	ip, #0
	and	r3, r3, r2
	bne	.L2138
	ldrb	r0, [r6, #19]	@ zero_extendqisi2
	ldrb	r2, [r1, #19]	@ zero_extendqisi2
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L2138:
	ldrb	r2, [r1, #20]	@ zero_extendqisi2
	ldrb	ip, [r6, #21]	@ zero_extendqisi2
	ldrb	r0, [r1, #21]	@ zero_extendqisi2
	ldrb	lr, [r6, #20]	@ zero_extendqisi2
	cmp	r0, ip
	cmpeq	lr, r2
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #0
	and	r3, r3, r2
	bne	.L2159
.L2139:
	ldrb	r2, [r6, #22]	@ zero_extendqisi2
	ldr	r0, [r6, #3316]
	ldr	ip, [r1, #3316]
	ldrb	r1, [r1, #22]	@ zero_extendqisi2
	cmp	r0, ip
	cmpeq	r2, r1
	moveq	r2, #1
	movne	r2, #0
	tst	r3, r2
	mvneq	r0, #0
	movne	r0, #0
.L2127:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2159:
	ldr	ip, [r1, #3260]
	ldr	lr, [r6, #3260]
	ldr	r0, [r6, #3256]
	ldr	r2, [r1, #3256]
	ldr	r5, [r6, #3264]
	cmp	lr, ip
	cmpeq	r0, r2
	ldr	r2, [r1, #3264]
	ldr	r4, [r6, #3268]
	ldr	lr, [r1, #3268]
	moveq	ip, #1
	movne	ip, #0
	cmp	r5, r2
	movne	r0, #0
	andeq	r0, ip, #1
	cmp	r4, lr
	movne	r2, #0
	andeq	r2, r0, #1
	and	r3, r3, r2
	b	.L2139
.L2140:
	mov	r1, r5
	mov	r2, r10
.L2131:
	ldr	ip, [r2, #4]!
	ldr	r0, [r1, #4]!
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r4
	bne	.L2131
	b	.L2130
.L2135:
	ldr	r0, [r6, #2204]
	ldr	r2, [r1, #2204]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
	b	.L2134
.L2158:
	mov	r0, r1
	movw	r3, #9737
	ldr	r2, .L2160
	ldr	r1, .L2160+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2127
.L2157:
	movw	r3, #9736
	ldr	r2, .L2160
	ldr	r1, .L2160+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2127
.L2161:
	.align	2
.L2160:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	SPSEqual, .-SPSEqual
	.global	__aeabi_idiv
	.align	2
	.global	H264GetDar
	.type	H264GetDar, %function
H264GetDar:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	mov	r5, r3
	mov	r0, r1
	beq	.L2190
	subs	r3, r4, #255
	movne	r3, #1
	cmp	r4, #16
	movle	r1, #0
	andgt	r1, r3, #1
	cmp	r1, #0
	movne	r4, #0
	movne	r2, r4
	bne	.L2163
	cmp	r2, #0
	cmpne	r0, #0
	moveq	ip, #1
	movne	ip, #0
	cmp	r4, #255
	movne	ip, #0
	andeq	ip, ip, #1
	cmp	ip, #0
	bne	.L2176
	cmp	r4, #1
	beq	.L2191
	cmp	r3, #0
	ldrne	r0, .L2194
	addne	r4, r0, r4, lsl #3
	ldrne	r2, [r4, #120]
	ldrne	r0, [r4, #116]
	mov	r1, r2
	mov	r0, r0, asl #10
	bl	__aeabi_idiv
	ldr	r1, [fp, #4]
	mov	r4, r0
	mov	r0, r5, asl #10
	bl	__aeabi_idiv
	movw	r3, #2405
	movw	r1, #2262
	mul	r0, r0, r4
	add	r2, r0, #1020
	cmp	r0, #0
	add	r2, r2, #3
	movlt	r0, r2
	mov	r2, r0, asr #10
	cmp	r2, r3
	rsble	r3, r2, #2400
	subgt	r3, r2, #2400
	addle	r3, r3, #6
	subgt	r3, r3, #6
	cmp	r2, r1
	ble	.L2192
	sub	r1, r2, #2256
	sub	r1, r1, #7
	cmp	r3, r1
	bge	.L2169
.L2182:
	mov	r4, #4
.L2163:
	mov	r3, r4
	ldr	r1, .L2194+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2176:
	mov	r4, r1
.L2190:
	mov	r2, r4
	b	.L2163
.L2192:
	rsb	r1, r2, #2256
	add	r1, r1, #7
	cmp	r3, r1
	blt	.L2182
.L2169:
	movw	r3, #1819
	cmp	r2, r3
	bgt	.L2170
	rsb	r3, r2, #1808
	add	r3, r3, #12
	cmp	r1, r3
	blt	.L2184
.L2171:
	movw	r1, #1364
	cmp	r2, r1
	rsble	r4, r2, #1360
	subgt	r4, r2, #1360
	addle	r4, r4, #5
	subgt	r4, r4, #5
	cmp	r3, r4
	movlt	r4, #2
	movge	r4, #1
	b	.L2163
.L2191:
	ldr	r3, [fp, #4]
	cmp	r5, #3840
	cmpeq	r3, #2160
	moveq	r2, #1
	movne	r2, #0
	moveq	r2, ip
	moveq	r4, #2
	beq	.L2163
	sub	r3, r3, #1072
	sub	r3, r3, #8
	bics	r3, r3, #8
	moveq	r1, #1
	movne	r1, #0
	cmp	r5, #1920
	movne	r1, #0
	andeq	r1, r1, #1
	cmp	r1, #0
	beq	.L2193
.L2189:
	mov	r4, #2
	b	.L2163
.L2170:
	sub	r3, r2, #1808
	sub	r3, r3, #12
	cmp	r1, r3
	bge	.L2171
.L2184:
	mov	r4, #3
	b	.L2163
.L2193:
	ldr	r3, [fp, #4]
	cmp	r5, #1280
	cmpeq	r3, #720
	moveq	r2, #1
	movne	r2, #0
	moveq	r2, r1
	beq	.L2189
	cmp	r5, #640
	cmpeq	r3, #480
	moveq	r4, #1
	movne	r4, #5
	b	.L2163
.L2195:
	.align	2
.L2194:
	.word	.LANCHOR0
	.word	.LC219
	UNWIND(.fnend)
	.size	H264GetDar, .-H264GetDar
	.align	2
	.global	ProcessSPS
	.type	ProcessSPS, %function
ProcessSPS:
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
	subs	r5, r0, #0
	mov	r4, r1
	beq	.L2315
	cmp	r1, #0
	beq	.L2317
	ldr	r2, [r1, #28]
	cmp	r2, #100
	cmpne	r2, #110
	moveq	r3, #1
	movne	r3, #0
	cmp	r2, #122
	orreq	r3, r3, #1
	cmp	r2, #144
	orreq	r3, r3, #1
	cmp	r2, #83
	orreq	r3, r3, #1
	cmp	r2, #86
	orreq	r3, r3, #1
	cmp	r3, #0
	streqb	r3, [r1, #25]
	moveq	r3, #1
	streq	r3, [r1, #40]
	bne	.L2318
.L2214:
	ldr	r1, .L2334
	mov	r0, r5
	bl	ue_v
	cmp	r0, #12
	str	r0, [r4, #2196]
	bhi	.L2227
	add	r6, r5, #61440
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2227
	ldr	r1, .L2334+4
	mov	r0, r5
	bl	ue_v
	cmp	r0, #2
	str	r0, [r4, #2200]
	bhi	.L2229
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2229
	cmp	r0, #0
	beq	.L2319
	cmp	r0, #1
	beq	.L2320
.L2234:
	ldr	r1, .L2334+8
	mov	r0, r5
	bl	ue_v
	str	r0, [r4, #3244]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	ldr	r1, .L2334+12
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #17]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	ldr	r1, .L2334+16
	mov	r0, r5
	bl	ue_v
	movw	r8, #509
	sub	r3, r0, #1
	str	r0, [r4, #3248]
	cmp	r3, r8
	bhi	.L2238
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2238
	ldr	r1, .L2334+20
	mov	r0, r5
	bl	ue_v
	str	r0, [r4, #3252]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	ldr	r1, .L2334+24
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #18]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	cmp	r0, #0
	bne	.L2321
	ldr	r1, .L2334+28
	mov	r0, r5
	bl	u_1
	ldr	r7, [r4, #3252]
	add	r7, r7, #1
	cmp	r7, #255
	strb	r0, [r4, #19]
	bhi	.L2273
	ldr	r3, [r4, #3248]
	add	r3, r3, #1
	cmp	r7, #1
	cmphi	r3, #3
	movhi	r9, #2
	bls	.L2273
.L2242:
	mul	r7, r7, r9
	mov	r10, r3, asl #4
	mov	r7, r7, asl #4
	mul	r1, r10, r7
	add	r1, r1, r1, lsr #1
	cmp	r1, #100663296
	bhi	.L2322
	ldr	r2, [r4, #32]
	sub	r3, r2, #10
	cmp	r3, #31
	ldrls	pc, [pc, r3, asl #2]
	b	.L2244
.L2246:
	.word	.L2245
	.word	.L2247
	.word	.L2280
	.word	.L2280
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2280
	.word	.L2249
	.word	.L2251
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2251
	.word	.L2252
	.word	.L2253
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2244
	.word	.L2255
	.word	.L2255
.L2318:
	ldr	r1, .L2334+32
	bl	ue_v
	cmp	r0, #1
	str	r0, [r4, #40]
	bls	.L2323
.L2201:
	mov	r2, r0
	ldr	r1, .L2334+36
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, .L2334+40
	mov	r0, r5
	bl	ue_v
	uxth	r0, r0
	add	r2, r0, #8
	str	r2, [r4, #44]
	cmp	r2, #8
	beq	.L2324
.L2203:
	ldr	r1, .L2334+44
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2334+48
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L2315
	ldr	r1, [r4, #44]
	add	r5, r5, #61440
	mov	ip, #0
	mov	r3, #8
	ldr	r0, [r5, #2680]
	sub	r2, fp, #68
	str	r1, [fp, #-64]
	mov	r1, #119
	str	ip, [fp, #-68]
	blx	r6
	mvn	r0, #0
.L2308:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2323:
	add	r6, r5, #61440
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2201
	ldr	r1, .L2334+40
	mov	r0, r5
	bl	ue_v
	uxth	r0, r0
	add	r2, r0, #8
	str	r2, [r4, #44]
	cmp	r2, #8
	bne	.L2205
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	beq	.L2206
.L2205:
	ldr	r1, .L2334+44
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2334+48
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L2206
	ldr	r0, [r4, #44]
	mov	r2, #0
	mov	r3, #8
	str	r2, [fp, #-68]
	mov	r1, #119
	sub	r2, fp, #68
	str	r0, [fp, #-64]
	ldr	r0, [r6, #2680]
	blx	r7
.L2206:
	ldr	r1, .L2334+52
	mov	r0, r5
	bl	ue_v
	uxth	r0, r0
	add	r2, r0, #8
	str	r2, [r4, #48]
	cmp	r2, #8
	bne	.L2208
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2208
.L2209:
	ldr	r1, .L2334+56
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	bne	.L2211
	ldr	r6, [r6, #2620]
	cmp	r6, #0
	bne	.L2211
	ldr	r1, .L2334+60
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #25]
	cmp	r0, #1
	bne	.L2214
	add	r7, r4, #1968
	sub	r8, fp, #72
	add	r7, r7, #4
	add	r10, r4, #3
	add	r9, r4, #52
	b	.L2220
.L2327:
	ldr	r3, .L2334+64
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2334+68
	ldr	r3, [r3, #52]
	blx	r3
.L2216:
	add	r6, r6, #1
	add	r7, r7, #16
	cmp	r6, #6
	add	r9, r9, #64
	beq	.L2325
.L2220:
	ldr	r1, .L2334+72
	mov	r0, r5
	bl	u_1
	clz	r1, r6
	mov	r2, #16
	mov	r1, r1, lsr #5
	cmp	r0, #1
	mov	r3, r0
	mov	r0, r7
	str	r3, [r8, #4]!
	strb	r3, [r10, #1]!
	beq	.L2326
	cmp	r6, #0
	cmpne	r6, #3
	beq	.L2327
	ldr	r3, .L2334+68
	mov	r2, #16
	sub	r1, r7, #16
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2216
.L2324:
	add	r3, r5, #61440
	ldr	r3, [r3, #2620]
	cmp	r3, #0
	bne	.L2203
.L2315:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2319:
	ldr	r1, .L2334+76
	mov	r0, r5
	bl	ue_v
	cmp	r0, #12
	str	r0, [r4, #2204]
	bhi	.L2232
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	beq	.L2234
.L2232:
	ldr	r1, .L2334+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2208:
	ldr	r1, .L2334+84
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2334+48
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L2209
	ldr	r0, [r4, #48]
	mov	r2, #0
	mov	r3, #8
	str	r2, [fp, #-68]
	mov	r1, #119
	sub	r2, fp, #68
	str	r0, [fp, #-64]
	ldr	r0, [r6, #2680]
	blx	r7
	b	.L2209
.L2321:
	ldr	r7, [r4, #3252]
	strb	r3, [r4, #19]
	sub	r3, r7, #1
	cmp	r3, r8
	bhi	.L2273
	ldr	r3, [r4, #3248]
	mov	r9, #1
	add	r7, r7, #1
	add	r3, r3, r9
	b	.L2242
.L2280:
	mov	r0, #60416
	movt	r0, 13
.L2248:
	bl	__aeabi_uidiv
	ldr	r1, .L2334+88
	cmp	r0, #16
	movcc	r8, r0
	movcs	r8, #16
	mov	r2, r8
	mov	r0, #21
	bl	dprint_vfmw
	ldr	r2, [r4, #3244]
	cmp	r2, r8
	bhi	.L2256
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	beq	.L2257
.L2256:
	mov	r3, r8
	ldr	r1, .L2334+92
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #3244]
	cmp	r3, #16
	bhi	.L2312
	cmp	r8, r3
	movcc	r8, r3
.L2312:
	str	r8, [r4, #3244]
.L2257:
	ldr	r1, .L2334+96
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #20]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	ldr	r1, .L2334+100
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #21]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	cmp	r0, #0
	bne	.L2328
.L2259:
	mov	r2, r10, lsr #1
	mov	r3, r7, lsr #1
	str	r10, [r4, #3276]
	str	r7, [r4, #3280]
	str	r2, [r4, #3284]
	str	r3, [r4, #3288]
.L2261:
	ldr	r1, .L2334+104
	mov	r0, r5
	bl	u_1
	uxtb	r3, r0
	strb	r3, [r4, #22]
	ldr	r2, [r6, #2620]
	cmp	r2, #0
	bne	.L2315
	cmp	r3, #0
	mov	r2, #2
	str	r2, [r4, #3332]
	bne	.L2329
	mov	r0, r3
	strb	r3, [r4, #3307]
	mov	r3, #5
	str	r3, [r4, #3320]
.L2264:
	ldr	r2, [r4, #3312]
	mov	r3, r10
	ldr	r1, [r4, #3308]
	str	r7, [sp]
	bl	H264GetDar
	ldr	r3, [r4, #3244]
	cmp	r3, #0
	str	r0, [r4, #3316]
	ldreq	r2, [r5]
	beq	.L2268
	ldr	r2, [r4, #3372]
	cmp	r3, r2
	ldr	r2, [r5]
	bhi	.L2270
	ldr	r1, [r2, #24]
	sub	r1, r1, #2
	cmp	r1, #1
	bls	.L2270
.L2268:
	cmp	r8, #16
	add	r5, r5, #12288
	movcs	r8, #16
	str	r8, [r5, #1296]
	ldr	r3, [r2, #28]
	cmp	r3, #25
	beq	.L2330
.L2271:
	add	r8, r8, #1
	mov	r0, #0
	str	r8, [r4, #3272]
	b	.L2308
.L2255:
	mov	r0, #12582912
	b	.L2248
.L2251:
	mov	r0, #30208
	movt	r0, 47
	b	.L2248
.L2247:
	mov	r0, #17920
	movt	r0, 5
	b	.L2248
.L2245:
	mov	r0, #20992
	movt	r0, 2
	b	.L2248
.L2253:
	mov	r0, #7864320
	b	.L2248
.L2252:
	mov	r0, #30720
	movt	r0, 105
	b	.L2248
.L2249:
	mov	r0, #55296
	movt	r0, 27
	b	.L2248
.L2244:
	ldr	r1, .L2334+108
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2227:
	ldr	r1, .L2334+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2273:
	ldr	r1, .L2334+116
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2270:
	cmp	r8, r3
	movcs	r8, r3
	b	.L2268
.L2328:
	ldr	r1, .L2334+120
	mov	r0, r5
	bl	ue_v
	ldr	r1, .L2334+124
	str	r0, [r4, #3256]
	mov	r0, r5
	bl	ue_v
	ldr	r1, .L2334+128
	str	r0, [r4, #3260]
	mov	r0, r5
	bl	ue_v
	ldr	r1, .L2334+132
	str	r0, [r4, #3264]
	mov	r0, r5
	bl	ue_v
	ldr	r3, [r4, #3264]
	ldr	r2, [r4, #3256]
	mov	r1, r9, asl #1
	ldr	ip, [r4, #3260]
	mov	r3, r3, asl #1
	mov	r2, r2, asl #1
	mul	r9, r9, r3
	rsb	r3, r2, r10
	sub	r3, r3, ip, asl #1
	rsb	ip, r9, r7
	str	r0, [r4, #3268]
	mls	r0, r0, r1, ip
	cmp	r3, #0
	cmpgt	r0, #0
	ble	.L2259
	add	r2, r2, r3, lsr #1
	add	r9, r9, r0, lsr #1
	str	r2, [r4, #3284]
	str	r9, [r4, #3288]
	str	r3, [r4, #3276]
	str	r0, [r4, #3280]
	b	.L2261
.L2329:
	add	r1, r4, #3280
	mov	r0, r5
	add	r1, r1, #12
	bl	vui_parameters
	cmp	r0, #0
	bne	.L2314
	ldrb	r3, [r4, #3304]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2314
	ldr	r2, [r4, #3372]
	clz	r3, r2
	mov	r3, r3, lsr #5
	cmp	r8, r2
	orrcc	r3, r3, #1
	cmp	r3, #0
	bne	.L2331
	ldr	r3, [r4, #3244]
	ldrb	r0, [r4, #3307]	@ zero_extendqisi2
	cmp	r2, r3
	movcs	r8, r2
	movcc	r8, r3
	b	.L2264
.L2330:
	ldr	r3, [r2, #732]
	cmp	r3, #0
	bne	.L2271
	ldr	r1, [r2, #716]
	ldr	ip, [r2, #692]
	cmp	r8, r1
	ldr	r0, [r2, #696]
	bls	.L2272
	ldr	r3, .L2334+48
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2315
	str	r1, [fp, #-72]
	mov	r3, #8
	str	r8, [fp, #-76]
	sub	r2, fp, #76
	ldr	r0, [r6, #2680]
	mov	r1, #106
	blx	r4
	mvn	r0, #0
	b	.L2308
.L2331:
	mov	r3, r8
	ldr	r1, .L2334+136
	mov	r0, #1
	bl	dprint_vfmw
.L2314:
	ldrb	r0, [r4, #3307]	@ zero_extendqisi2
	b	.L2264
.L2325:
	add	r6, r4, #2064
	sub	r8, fp, #88
	add	r6, r6, #4
	add	r10, r4, #9
	add	r9, r4, #436
	mov	r7, #0
.L2225:
	ldr	r1, .L2334+72
	mov	r0, r5
	bl	u_1
	mov	r2, #64
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r6
	str	r3, [r8, #4]!
	strb	r3, [r10, #1]!
	beq	.L2332
	ldr	r1, .L2334+140
	cmp	r7, #0
	ldr	r3, .L2334+68
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L2222:
	add	r7, r7, #1
	add	r6, r6, #64
	cmp	r7, #2
	add	r9, r9, #256
	bne	.L2225
	b	.L2214
.L2320:
	ldr	r1, .L2334+144
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #16]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	ldr	r1, .L2334+148
	mov	r0, r5
	bl	se_v
	str	r0, [r4, #2208]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	ldr	r1, .L2334+152
	mov	r0, r5
	bl	se_v
	str	r0, [r4, #2212]
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	bne	.L2315
	ldr	r1, .L2334+156
	mov	r0, r5
	bl	ue_v
	cmp	r0, #255
	str	r0, [r4, #2216]
	bhi	.L2235
	ldr	r7, [r6, #2620]
	cmp	r7, #0
	bne	.L2235
	cmp	r0, #0
	addne	r8, r4, #2208
	addne	r8, r8, #8
	bne	.L2237
	b	.L2234
.L2333:
	ldr	r3, [r4, #2216]
	cmp	r3, r7
	bls	.L2234
.L2237:
	ldr	r1, .L2334+160
	mov	r0, r5
	bl	se_v
	add	r7, r7, #1
	str	r0, [r8, #4]!
	ldr	r3, [r6, #2620]
	cmp	r3, #0
	beq	.L2333
	b	.L2315
.L2326:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r7
	mov	r1, r9
	mov	r0, r5
	bl	Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2216
	ldr	r1, .L2334+64
	mov	r2, #16
	ldr	r3, .L2334+68
	cmp	r6, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r7
	blx	r3
	b	.L2216
.L2238:
	mov	r2, r0
	ldr	r1, .L2334+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2229:
	ldr	r1, .L2334+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2211:
	ldr	r1, .L2334+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2332:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r6
	mov	r1, r9
	mov	r0, r5
	bl	Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2222
	ldr	r1, .L2334+140
	mov	r2, #64
	ldr	r3, .L2334+68
	cmp	r7, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r6
	blx	r3
	b	.L2222
.L2272:
	cmp	ip, r10
	cmpcs	r0, r7
	bcs	.L2271
	ldr	r3, .L2334+48
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2315
	strh	r0, [fp, #-70]	@ movhi
	mov	r3, #8
	strh	r10, [fp, #-76]	@ movhi
	sub	r2, fp, #76
	strh	r7, [fp, #-74]	@ movhi
	mov	r1, #107
	strh	ip, [fp, #-72]	@ movhi
	ldr	r0, [r6, #2680]
	blx	r4
	b	.L2315
.L2317:
	mov	r0, r1
	movw	r3, #9948
	ldr	r2, .L2334+176
	ldr	r1, .L2334+180
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2322:
	ldr	r1, .L2334+184
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2235:
	ldr	r1, .L2334+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2308
.L2335:
	.align	2
.L2334:
	.word	.LC229
	.word	.LC231
	.word	.LC234
	.word	.LC242
	.word	.LC243
	.word	.LC245
	.word	.LC246
	.word	.LC260
	.word	.LC220
	.word	.LC221
	.word	.LC222
	.word	.LC223
	.word	g_event_report
	.word	.LC224
	.word	.LC226
	.word	.LC228
	.word	.LANCHOR1+80
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC166
	.word	.LC233
	.word	.LC235
	.word	.LC225
	.word	.LC250
	.word	.LC251
	.word	.LC252
	.word	.LC253
	.word	.LC258
	.word	.LC249
	.word	.LC230
	.word	.LC247
	.word	.LC254
	.word	.LC255
	.word	.LC256
	.word	.LC257
	.word	.LC259
	.word	.LANCHOR1+112
	.word	.LC236
	.word	.LC237
	.word	.LC238
	.word	.LC239
	.word	.LC241
	.word	.LC244
	.word	.LC232
	.word	.LC227
	.word	.LC8
	.word	.LC9
	.word	.LC248
	.word	.LC240
	UNWIND(.fnend)
	.size	ProcessSPS, .-ProcessSPS
	.align	2
	.global	Sps_SvcExt
	.type	Sps_SvcExt, %function
Sps_SvcExt:
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
	add	r1, r0, #12288
	add	r2, r0, #20480
	mov	lr, #2208
	ldr	r3, [r1, #1304]
	mov	r4, r0
	ldr	r2, [r2, #216]
	add	r0, r0, #13504
	ldr	ip, [r1, #1300]
	mov	r5, #4000
	mov	r1, #32
	add	r0, r0, #24
	mla	r3, lr, r2, r3
	ldr	r3, [r3, #28]
	mla	r5, r5, r3, ip
	bl	BsGet
	ldr	r1, .L2350
	mov	r6, r0
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2350+4
	mov	r2, r0
	mov	r0, #17
	bl	dprint_vfmw
	mov	r0, r4
	ldr	r2, .L2350+8
	mov	r1, #2
	bl	u_v
	cmp	r0, #1
	beq	.L2346
	ldr	r3, [r5, #40]
	sub	r2, r3, #1
	cmp	r2, #1
	bls	.L2347
.L2339:
	cmp	r3, #1
	beq	.L2348
.L2340:
	ldr	r1, .L2350+12
	mov	r0, r4
	bl	u_1
	cmp	r0, #0
	bne	.L2349
.L2341:
	mov	r0, r4
	ldr	r1, .L2350+16
	bl	u_1
	cmp	r0, #1
	moveq	r0, #0
	beq	.L2338
	ldr	ip, [r5, #40]
	mov	r2, r0
	mov	r3, r6
	ldr	r1, .L2350+20
	mov	r0, #1
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, #0
.L2338:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2349:
	ldr	r1, .L2350+24
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2350+28
	mov	r2, r0
	mov	r0, #17
	bl	dprint_vfmw
	b	.L2341
.L2348:
	ldr	r2, .L2350+32
	mov	r1, #2
	mov	r0, r4
	bl	u_v
	ldr	r1, .L2350+36
	mov	r2, r0
	mov	r0, #17
	bl	dprint_vfmw
	b	.L2340
.L2347:
	ldr	r1, .L2350+40
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2350+44
	mov	r2, r0
	mov	r0, #17
	bl	dprint_vfmw
	ldr	r3, [r5, #40]
	b	.L2339
.L2346:
	ldr	r1, .L2350+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2338
.L2351:
	.align	2
.L2350:
	.word	.LC261
	.word	.LC262
	.word	.LC263
	.word	.LC269
	.word	.LC272
	.word	.LC273
	.word	.LC270
	.word	.LC271
	.word	.LC267
	.word	.LC268
	.word	.LC265
	.word	.LC266
	.word	.LC264
	UNWIND(.fnend)
	.size	Sps_SvcExt, .-Sps_SvcExt
	.align	2
	.global	H264_DecSPS
	.type	H264_DecSPS, %function
H264_DecSPS:
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
	subs	r4, r0, #0
	beq	.L2383
	ldr	r2, .L2389
	mov	r1, #8
	bl	u_v
	ldr	r1, .L2389+4
	add	r7, r4, #61440
	mov	r8, r0
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2389+8
	str	r0, [fp, #-56]
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2389+12
	str	r0, [fp, #-60]
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2389+16
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	u_1
	ldr	r2, .L2389+20
	mov	r1, #4
	str	r0, [fp, #-68]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2389+24
	mov	r1, #8
	mov	r0, r4
	bl	u_v
	ldr	r1, .L2389+28
	mov	r6, r0
	mov	r0, r4
	bl	ue_v
	ldr	r3, [r7, #2620]
	cmp	r3, #0
	mov	r9, r0
	bne	.L2382
	add	r5, r4, #12288
	ldr	r3, [r5, #1288]
	sub	r3, r3, #1
	cmp	r0, r3
	bhi	.L2384
	sub	r3, r8, #66
	mov	r10, r8
	cmp	r3, #78
	ldrls	pc, [pc, r3, asl #2]
	b	.L2358
.L2360:
	.word	.L2359
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2361
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2361
	.word	.L2358
	.word	.L2358
	.word	.L2361
	.word	.L2358
	.word	.L2362
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2361
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2363
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2363
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2358
	.word	.L2363
.L2359:
	ldr	r1, .L2389+32
	mov	r0, #1
	bl	dprint_vfmw
.L2361:
	cmp	r6, #9
	bls	.L2381
.L2388:
	cmp	r6, #41
	bhi	.L2381
.L2365:
	mov	r2, #4000
	ldr	r3, [r5, #1300]
	mul	r7, r2, r9
	add	r3, r3, r7
	ldrb	r8, [r3, #23]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L2366
	ldr	r3, .L2389+36
	mov	r1, #0
	ldr	r8, .L2389+40
	ldr	r3, [r3, #48]
	add	r0, r8, #2208
	blx	r3
	ldrb	r3, [fp, #-56]	@ zero_extendqisi2
	add	r1, r8, #2208
	mov	r0, r4
	str	r10, [r8, #2236]
	strb	r3, [r8, #2208]
	ldrb	r3, [fp, #-60]	@ zero_extendqisi2
	str	r6, [r8, #2240]
	str	r9, [r8, #2244]
	strb	r3, [r8, #2209]
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	strb	r3, [r8, #2210]
	ldrb	r3, [fp, #-68]	@ zero_extendqisi2
	strb	r3, [r8, #2211]
	bl	ProcessSPS
	cmp	r0, #0
	bne	.L2385
	ldr	r1, [r5, #1300]
	add	r0, r8, #2208
	add	r1, r1, r7
	bl	SPSEqual
	cmp	r0, #0
	bne	.L2386
.L2368:
	cmp	r10, #83
	cmpne	r10, #86
	beq	.L2370
.L2371:
	mov	r0, #0
.L2354:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2381:
	mov	r2, r6
	mov	r3, #41
	ldr	r1, .L2389+44
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #41
	b	.L2365
.L2366:
	str	r10, [r3, #28]
	mov	r0, r4
	ldr	r3, [r5, #1300]
	ldrb	r2, [fp, #-56]	@ zero_extendqisi2
	strb	r2, [r3, r7]
	ldr	r3, [r5, #1300]
	ldrb	r2, [fp, #-60]	@ zero_extendqisi2
	add	r3, r3, r7
	strb	r2, [r3, #1]
	ldr	r3, [r5, #1300]
	ldrb	r2, [fp, #-64]	@ zero_extendqisi2
	add	r3, r3, r7
	strb	r2, [r3, #2]
	ldr	r3, [r5, #1300]
	ldrb	r2, [fp, #-68]	@ zero_extendqisi2
	add	r3, r3, r7
	strb	r2, [r3, #3]
	ldr	r3, [r5, #1300]
	add	r3, r3, r7
	str	r6, [r3, #32]
	ldr	r3, [r5, #1300]
	add	r3, r3, r7
	str	r9, [r3, #36]
	ldr	r1, [r5, #1300]
	add	r1, r1, r7
	bl	ProcessSPS
	cmp	r0, #0
	bne	.L2387
	ldr	r3, [r5, #1300]
	mov	r2, #1
	cmp	r10, #83
	cmpne	r10, #86
	add	r3, r3, r7
	strb	r2, [r3, #24]
	ldr	r3, [r5, #1300]
	add	r7, r3, r7
	strb	r2, [r7, #23]
	bne	.L2371
.L2370:
	mov	r0, r4
	bl	Sps_SvcExt
	cmp	r0, #0
	beq	.L2371
	ldr	r1, .L2389+48
	mov	r0, #1
	bl	dprint_vfmw
.L2382:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2384:
	ldr	r1, .L2389+52
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #1288]
	sub	r3, r2, #1
	cmp	r9, r3
	bls	.L2382
	ldr	r3, .L2389+56
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2382
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r9, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r7, #2680]
	mov	r1, #109
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2363:
	ldr	r1, .L2389+60
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r6, #9
	bhi	.L2388
	b	.L2381
.L2362:
	ldr	r1, .L2389+64
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r6, #9
	bhi	.L2388
	b	.L2381
.L2358:
	mov	r2, r8
	ldr	r1, .L2389+68
	mov	r0, #1
	mov	r10, #100
	bl	dprint_vfmw
	cmp	r6, #9
	bhi	.L2388
	b	.L2381
.L2386:
	ldr	r3, .L2389+36
	mov	r2, #4000
	ldr	r0, [r5, #1300]
	add	r1, r8, #2208
	ldr	r5, [r3, #56]
	add	r0, r0, r7
	mov	r3, #1
	strb	r3, [r8, #2232]
	strb	r3, [r8, #2231]
	blx	r5
	b	.L2368
.L2385:
	mov	r3, r9
	movw	r2, #10566
	ldr	r1, .L2389+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2354
.L2383:
	movw	r3, #10479
	ldr	r2, .L2389+76
	ldr	r1, .L2389+80
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2354
.L2387:
	mov	r3, r9
	movw	r2, #10591
	ldr	r1, .L2389+72
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r5, #1300]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r7
	strb	r2, [r3, #24]
	ldr	r3, [r5, #1300]
	add	r7, r3, r7
	strb	r8, [r7, #23]
	b	.L2354
.L2390:
	.align	2
.L2389:
	.word	.LC274
	.word	.LC275
	.word	.LC276
	.word	.LC277
	.word	.LC278
	.word	.LC279
	.word	.LC280
	.word	.LC281
	.word	.LC282
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2
	.word	.LC286
	.word	.LC288
	.word	.LC172
	.word	g_event_report
	.word	.LC284
	.word	.LC283
	.word	.LC285
	.word	.LC287
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264_DecSPS, .-H264_DecSPS
	.align	2
	.global	PassBytes
	.type	PassBytes, %function
PassBytes:
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
	ldr	ip, [r0, #368]
	cmp	ip, #0
	cmpne	r1, #0
	beq	.L2400
	ldrb	r3, [ip]	@ zero_extendqisi2
	mov	r2, r3, asl #2
	mov	r5, r3, asl #5
	rsb	r4, r2, r5
	add	r4, ip, r4
	add	r6, r4, #8
	ldr	lr, [r4, #8]
	cmp	lr, #0
	beq	.L2400
	ldr	lr, [ip, #68]
	cmp	r3, #1
	cmpls	lr, #2
	bhi	.L2400
	cmp	lr, r3
	bls	.L2400
	ldr	lr, [r4, #12]
	mov	r6, r2
	ldr	r4, [r4, #24]
	mov	lr, lr, asl #3
	add	r1, r4, r1, lsl #3
	cmp	r1, lr
	bhi	.L2395
	b	.L2393
.L2396:
	ldr	r4, [r2, #24]
	ldr	r2, [r2, #12]
	rsb	lr, lr, r4
	add	r1, r1, lr
	mov	lr, r2, asl #3
	cmp	r1, lr
	bls	.L2393
.L2395:
	rsb	r2, r6, r5
	add	r3, r3, #1
	add	ip, ip, r2
	mov	r6, r3, asl #2
	mov	r5, r3, asl #5
	str	lr, [ip, #24]
	rsb	r2, r6, r5
	ldr	ip, [r0, #368]
	ldrb	r4, [ip]	@ zero_extendqisi2
	add	r4, r4, #1
	strb	r4, [ip]
	ldr	ip, [r0, #368]
	add	r2, ip, r2
	ldr	r4, [ip, #68]
	cmp	r4, r3
	bhi	.L2396
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2393:
	rsb	r2, r6, r5
	mov	r0, #1
	add	ip, ip, r2
	str	r1, [ip, #24]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2400:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	PassBytes, .-PassBytes
	.align	2
	.global	GetBytes
	.type	GetBytes, %function
GetBytes:
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
	cmp	r1, #0
	beq	.L2415
	ldr	r3, [r0, #368]
	cmp	r3, #0
	cmpne	r2, #0
	ble	.L2415
	ldrb	r7, [r3]	@ zero_extendqisi2
	mov	ip, r7, asl #5
	sub	ip, ip, r7, asl #2
	add	ip, r3, ip
	ldr	ip, [ip, #8]
	cmp	ip, #0
	beq	.L2415
	ldr	ip, [r3, #68]
	cmp	r7, #1
	cmpls	ip, #2
	movhi	lr, #1
	movls	lr, #0
	bhi	.L2415
	cmp	ip, r7
	bls	.L2415
.L2410:
	mov	r5, r7, asl #5
	sub	r5, r5, r7, asl #2
	add	ip, r3, r5
	ldr	r4, [ip, #24]
	ldr	r8, [ip, #8]
	ldr	r6, [ip, #12]
	add	r4, r4, #7
	add	r6, r8, r6
	add	ip, r8, r4, lsr #3
	cmp	ip, r6
	bcs	.L2406
	ldrb	r3, [r8, r4, lsr #3]	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	lr, r2
	add	r4, r1, #1
	add	ip, ip, #1
	strb	r3, [r1]
	b	.L2417
.L2408:
	cmp	ip, r6
	mov	r1, r4
	beq	.L2418
	ldrb	r3, [ip], #1	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	lr, r2
	strb	r3, [r4], #1
.L2417:
	ldr	r3, [r0, #368]
	add	r3, r3, r5
	ldr	r1, [r3, #24]
	add	r1, r1, #8
	str	r1, [r3, #24]
	bcc	.L2408
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2418:
	ldr	r3, [r0, #368]
.L2406:
	ldrb	ip, [r3]	@ zero_extendqisi2
	add	r7, r7, #1
	add	ip, ip, #1
	strb	ip, [r3]
	ldr	r3, [r0, #368]
	ldr	ip, [r3, #68]
	cmp	ip, r7
	bhi	.L2410
	mov	r0, lr
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2415:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetBytes, .-GetBytes
	.align	2
	.global	H264_DecFramePackingSEI
	.type	H264_DecFramePackingSEI, %function
H264_DecFramePackingSEI:
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
	ldr	r1, .L2426
	mov	r5, r0
	bl	ue_v
	add	r4, r5, #24576
	ldr	r2, .L2426+4
	mov	r1, #1
	str	r0, [r4, #1832]
	mov	r0, r5
	bl	u_v
	uxtb	r0, r0
	strb	r0, [r4, #1809]
	cmp	r0, #0
	beq	.L2425
.L2420:
	mov	r0, r5
	ldr	r2, .L2426+8
	mov	r1, #1
	bl	u_v
	mov	r3, #1
	strb	r3, [r4, #1808]
	strb	r0, [r4, #1810]
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2425:
	ldr	r2, .L2426+12
	mov	r1, #7
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+16
	mov	r1, #1
	str	r0, [r4, #1824]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+20
	mov	r1, #6
	strb	r0, [r4, #1811]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+24
	mov	r1, #1
	str	r0, [r4, #1828]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+28
	mov	r1, #1
	strb	r0, [r4, #1812]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+32
	mov	r1, #1
	strb	r0, [r4, #1813]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+36
	mov	r1, #1
	strb	r0, [r4, #1814]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+40
	mov	r1, #1
	strb	r0, [r4, #1815]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+44
	mov	r1, #1
	strb	r0, [r4, #1816]
	mov	r0, r5
	bl	u_v
	ldrb	r3, [r4, #1811]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #1817]
	bne	.L2421
	ldr	r3, [r4, #1824]
	cmp	r3, #5
	beq	.L2421
	ldr	r2, .L2426+48
	mov	r1, #1
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+52
	mov	r1, #1
	strb	r0, [r4, #1818]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+56
	mov	r1, #1
	strb	r0, [r4, #1819]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2426+60
	mov	r1, #1
	strb	r0, [r4, #1820]
	mov	r0, r5
	bl	u_v
	strb	r0, [r4, #1821]
.L2421:
	ldr	r2, .L2426+64
	mov	r1, #8
	mov	r0, r5
	bl	u_v
	ldr	r1, .L2426+68
	str	r0, [r4, #1836]
	mov	r0, r5
	bl	ue_v
	str	r0, [r4, #1840]
	b	.L2420
.L2427:
	.align	2
.L2426:
	.word	.LC289
	.word	.LC290
	.word	.LC306
	.word	.LC291
	.word	.LC292
	.word	.LC293
	.word	.LC294
	.word	.LC295
	.word	.LC296
	.word	.LC297
	.word	.LC298
	.word	.LC299
	.word	.LC300
	.word	.LC301
	.word	.LC302
	.word	.LC303
	.word	.LC304
	.word	.LC305
	UNWIND(.fnend)
	.size	H264_DecFramePackingSEI, .-H264_DecFramePackingSEI
	.align	2
	.global	H264_DecPicTimingSEI
	.type	H264_DecPicTimingSEI, %function
H264_DecPicTimingSEI:
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
	add	r2, r0, #12288
	mov	r4, #4000
	mov	r5, r0
	ldr	r1, [r2, #1344]
	ldr	r3, [r2, #1300]
	mla	r4, r4, r1, r3
	ldrb	r1, [r4, #23]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2429
	ldr	r0, [r2, #1288]
	cmp	r0, #0
	ble	.L2430
	ldrb	r2, [r3, #23]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #4000
	beq	.L2433
	b	.L2451
.L2434:
	ldrb	r1, [r3, #-3977]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2431
.L2433:
	add	r2, r2, #1
	mov	r4, r3
	cmp	r2, r0
	add	r3, r3, #4000
	bne	.L2434
.L2430:
	ldr	r1, .L2454
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
.L2435:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2451:
	mov	r4, r3
.L2431:
	cmp	r4, #0
	beq	.L2430
.L2429:
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2437
	ldrb	r3, [r4, #3299]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2452
	ldr	r1, [r4, #3676]
	ldr	r7, [r4, #3680]
	add	r1, r1, #1
	add	r7, r7, #1
.L2441:
	ldr	r2, .L2454+4
	mov	r0, r5
	bl	u_v
	add	r6, r5, #24576
	ldr	r2, .L2454+8
	mov	r1, r7
	str	r0, [r6, #1848]
	mov	r0, r5
	bl	u_v
	add	r3, r5, #61440
	ldr	r2, .L2454+12
	str	r0, [r6, #1852]
	ldr	r3, [r3, #2680]
	ldr	r3, [r2, r3, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L2453
.L2437:
	ldrb	r0, [r4, #3303]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	r3, r0
	beq	.L2435
	ldr	r2, .L2454+16
	mov	r1, #4
	mov	r0, r5
	add	r5, r5, #24576
	bl	u_v
	mov	r3, #0
	strb	r0, [r5, #1844]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2452:
	ldrb	r3, [r4, #3302]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2437
	ldr	r1, [r4, #3988]
	ldr	r7, [r4, #3992]
	add	r1, r1, #1
	add	r7, r7, #1
	b	.L2441
.L2453:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L2437
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L2437
	mov	r0, r5
	bl	H264_Sei_Get_Dpb_Output_Time
	b	.L2437
.L2455:
	.align	2
.L2454:
	.word	.LC307
	.word	.LC308
	.word	.LC309
	.word	s_pstVfmwChan
	.word	.LC310
	UNWIND(.fnend)
	.size	H264_DecPicTimingSEI, .-H264_DecPicTimingSEI
	.align	2
	.global	H264_DecSEI
	.type	H264_DecSEI, %function
H264_DecSEI:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
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
	subs	r7, r0, #0
	mov	r3, #0
	strb	r3, [fp, #-45]
	beq	.L2696
	add	r10, r7, #61440
	ldr	r3, .L2732
	ldr	r2, [r10, #2680]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L2697
.L2459:
	ldr	r3, [r7, #368]
	mov	r2, #32
	str	r2, [r3, #24]
.L2460:
	add	r6, r7, #13504
	add	r4, r7, #12288
	add	r6, r6, #24
	mov	r8, #0
	b	.L2463
.L2699:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2462
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2698
.L2463:
	mov	r2, #1
	sub	r1, fp, #45
	mov	r0, r7
	bl	GetBytes
	ldr	r3, [r4, #1264]
	ldr	ip, [r4, #1256]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r8, r8, r2
	mov	r5, r0
	mov	r0, r6
	bls	.L2699
.L2462:
	ldr	r1, .L2732+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2458
.L2698:
	mov	r3, #0
	str	r3, [fp, #-60]
.L2642:
	mov	r5, #0
	b	.L2468
.L2701:
	bl	BsSkip
	cmp	r9, #0
	ble	.L2466
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2700
.L2468:
	mov	r2, #1
	sub	r1, fp, #45
	mov	r0, r7
	bl	GetBytes
	ldr	r3, [r4, #1264]
	ldr	ip, [r4, #1256]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r5, r5, r2
	mov	r9, r0
	mov	r0, r6
	bls	.L2701
.L2466:
	ldr	r1, .L2732+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2458:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2700:
	cmp	r5, #409600
	bgt	.L2466
	ldr	r3, [r7, #368]
	ldr	r2, [r3, #68]
	cmp	r2, #2
	ldreq	r2, [r3, #52]
	ldreq	r3, [r3, #24]
	ldrne	r2, [r3, #24]
	addeq	r2, r2, r3
	moveq	r2, r2, lsr #3
	cmp	r8, #45
	ldrls	pc, [pc, r8, asl #2]
	b	.L2471
.L2473:
	.word	.L2472
	.word	.L2474
	.word	.L2475
	.word	.L2476
	.word	.L2477
	.word	.L2478
	.word	.L2479
	.word	.L2480
	.word	.L2481
	.word	.L2482
	.word	.L2483
	.word	.L2484
	.word	.L2485
	.word	.L2486
	.word	.L2487
	.word	.L2488
	.word	.L2489
	.word	.L2490
	.word	.L2491
	.word	.L2492
	.word	.L2493
	.word	.L2494
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2471
	.word	.L2495
.L2495:
	mov	r1, r5
	mov	r0, r7
	ldr	r8, [r4, #1264]
	bl	H264_DecFramePackingSEI
	ldr	r0, [r4, #1264]
	mov	r9, r5, asl #3
	rsb	r3, r8, r0
	cmp	r3, r9
	bge	.L2625
	rsb	r3, r3, r9
	str	r3, [fp, #-56]
	cmp	r3, #0
	add	r8, r3, #7
	movge	r8, r3
	ldr	r3, [r4, #1256]
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2627
	add	r2, r0, #8
	mov	r3, r3, asl #3
	cmp	r2, r3
	bhi	.L2627
	mov	r9, #0
	b	.L2628
.L2629:
	add	r2, r0, #8
	cmp	r2, r3
	bhi	.L2627
.L2628:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r9, r9, #1
	ldr	r3, [r4, #1256]
	cmp	r9, r8
	ldr	r0, [r4, #1264]
	mov	r3, r3, asl #3
	bne	.L2629
.L2627:
	ldr	r2, [fp, #-56]
	mov	r1, r2, asr #31
	mov	r1, r1, lsr #29
	add	r2, r2, r1
	and	r2, r2, #7
	rsb	r1, r1, r2
	add	r2, r0, r1
	cmp	r3, r2
	bcs	.L2702
.L2625:
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2703
.L2691:
	ldr	r3, [r10, #1392]
.L2498:
	cmp	r3, #3
	bhi	.L2704
.L2637:
	mov	r8, #0
	b	.L2641
.L2639:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2640
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2705
.L2641:
	mov	r2, #1
	sub	r1, fp, #45
	mov	r0, r7
	bl	GetBytes
	ldr	r3, [r4, #1264]
	ldr	ip, [r4, #1256]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r8, r8, r2
	mov	r5, r0
	mov	r0, r6
	bls	.L2639
.L2640:
	mov	r0, #0
.L2730:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2494:
	mov	r3, r5
	ldr	r1, .L2732+12
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2706
.L2619:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2622
.L2623:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2622:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2623
	b	.L2691
.L2493:
	mov	r3, r5
	ldr	r1, .L2732+16
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2707
.L2614:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2617
.L2618:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2617:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2618
	b	.L2691
.L2489:
	mov	r3, r5
	ldr	r1, .L2732+20
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2708
.L2594:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2597
.L2598:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2597:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2598
	b	.L2691
.L2488:
	mov	r3, r5
	ldr	r1, .L2732+24
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2709
.L2589:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2592
.L2593:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2592:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2593
	b	.L2691
.L2487:
	mov	r3, r5
	ldr	r1, .L2732+28
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2710
.L2584:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2587
.L2588:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2587:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2588
	b	.L2691
.L2486:
	mov	r3, r5
	ldr	r1, .L2732+32
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2711
.L2579:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2582
.L2583:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2582:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2583
	b	.L2691
.L2491:
	mov	r3, r5
	ldr	r1, .L2732+36
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2712
.L2604:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2607
.L2608:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2607:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2608
	b	.L2691
.L2490:
	mov	r3, r5
	ldr	r1, .L2732+40
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2713
.L2599:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2602
.L2603:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2602:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2603
	b	.L2691
.L2492:
	mov	r3, r5
	ldr	r1, .L2732+44
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2714
.L2609:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2612
.L2613:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2612:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2613
	b	.L2691
.L2485:
	mov	r3, r5
	ldr	r1, .L2732+48
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2715
.L2574:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2577
.L2578:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2577:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2578
	b	.L2691
.L2484:
	mov	r3, r5
	ldr	r1, .L2732+52
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2716
.L2569:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2572
.L2573:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2572:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2573
	b	.L2691
.L2483:
	mov	r3, r5
	ldr	r1, .L2732+56
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2717
.L2564:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2567
.L2568:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2567:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2568
	b	.L2691
.L2482:
	mov	r3, r5
	ldr	r1, .L2732+60
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2718
.L2559:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2562
.L2563:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2562:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2563
	b	.L2691
.L2481:
	mov	r3, r5
	ldr	r1, .L2732+64
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2719
.L2554:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2557
.L2558:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2557:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2558
	b	.L2691
.L2480:
	mov	r3, r5
	ldr	r1, .L2732+68
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2720
.L2549:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2552
.L2553:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2552:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2553
	b	.L2691
.L2479:
	mov	r3, r5
	ldr	r1, .L2732+72
	mov	r0, #20
	bl	dprint_vfmw
	cmp	r5, #0
	ble	.L2546
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2546
	mov	r8, #0
	b	.L2547
.L2548:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2546
.L2547:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2548
.L2546:
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	bge	.L2691
	movw	r3, #11265
	b	.L2692
.L2478:
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	bne	.L2477
	mov	r3, r5
	ldr	r1, .L2732+76
	mov	r0, #20
	bl	dprint_vfmw
	ldr	r8, [r10, #1392]
	cmp	r8, #3
	bhi	.L2721
.L2522:
	ldr	r0, [r10, #2680]
	bl	GetUsd
	add	r3, r8, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	str	r0, [r3, #4]
	ldr	r3, [r10, #1392]
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	ip, [r3, #4]
	cmp	ip, #0
	beq	.L2645
	ldr	r2, [r7, #368]
	cmp	r5, #1024
	movlt	r9, r5
	movge	r9, #1024
	ldrb	r0, [r2]	@ zero_extendqisi2
	ldr	lr, [r2, #68]
	cmp	r0, lr
	bcs	.L2646
	sxth	r3, r0
	mov	r8, #0
	mov	r1, r3, asl #5
	sub	r1, r1, r3, asl #2
	add	r1, r2, r1
.L2524:
	ldr	r3, [r1, #24]
	add	r0, r0, #1
	ldr	r2, [r1, #12]
	cmp	r0, lr
	add	r3, r3, #7
	add	r1, r1, #28
	sub	r3, r2, r3, lsr #3
	add	r8, r8, r3
	bne	.L2524
	mov	r3, r8
.L2523:
	cmp	r9, r3
	ldrsb	r2, [fp, #-60]
	movle	r8, r9
	cmp	r2, #1
	str	r2, [fp, #-64]
	movne	r3, #0
	strne	r3, [fp, #-56]
	beq	.L2722
.L2526:
	rsb	r2, r3, r8
	cmp	r2, #0
	ble	.L2723
	ldr	r3, [r10, #1392]
	mov	r0, r7
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	r1, [r3, #4]
	bl	GetBytes
	subs	r8, r0, #0
	ble	.L2724
	ldr	r3, [fp, #-56]
	rsb	r3, r3, r9
	cmp	r8, r3
	ldr	r3, [r10, #1392]
	bge	.L2532
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r8, [r3, #1052]
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2533
	mov	r5, #0
	b	.L2534
.L2536:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2533
.L2534:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2536
.L2533:
	ldr	r2, [fp, #-64]
	ldr	r3, [r10, #1392]
	cmp	r2, #1
	ldr	r1, [r7]
	add	r3, r3, #15680
	moveq	r2, #8
	movne	r2, #9
.L2694:
	add	r3, r3, #28
	ldrd	r0, [r1, #64]
	ldr	ip, .L2732+80
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	ldr	r5, [ip]
	add	r3, r3, #1056
	cmp	r5, #0
	strd	r0, [r3]
	ldr	r3, [r10, #1392]
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r2, [r3, #1040]
	ldr	r3, [r10, #1392]
	ldr	r2, [r10, #2640]
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r2, [r3, #1044]
	beq	.L2542
	ldr	r2, [r10, #1392]
	movw	r3, #1064
	mov	r1, #6
	ldr	r0, [r10, #2680]
	add	r2, r2, #15680
	add	r2, r2, #28
	add	r2, r7, r2, lsl #2
	ldr	r2, [r2, #4]
	blx	r5
.L2542:
	ldr	r3, [r10, #1392]
	add	r3, r3, #1
	str	r3, [r10, #1392]
	cmp	r3, #3
	bls	.L2637
.L2704:
	ldr	r1, .L2732+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2458
.L2476:
	mov	r3, r5
	ldr	r1, .L2732+88
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2725
.L2515:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2518
.L2519:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2518:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2519
	b	.L2691
.L2472:
	add	r1, r7, #24576
	mov	ip, #1
	mov	r3, #0
	ldr	r0, [r1, #1856]
	str	r3, [r1, #1864]
	mov	r3, r5
	add	r0, r0, ip
	strb	ip, [r1, #1936]
	str	r0, [r1, #1856]
	mov	r0, #20
	ldr	r1, .L2732+92
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2726
.L2496:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2500
.L2501:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2500:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2501
	b	.L2691
.L2475:
	mov	r3, r5
	ldr	r1, .L2732+96
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2727
.L2510:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2513
.L2514:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2513:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2514
	b	.L2691
.L2474:
	mov	r3, r5
	ldr	r1, .L2732+100
	mov	r0, #20
	mov	r9, r5, asl #3
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	ldr	r8, [r4, #1264]
	bl	H264_DecPicTimingSEI
	ldr	r0, [r4, #1264]
	rsb	r3, r8, r0
	cmp	r3, r9
	bge	.L2503
	rsb	r3, r3, r9
	str	r3, [fp, #-56]
	cmp	r3, #0
	add	r8, r3, #7
	movge	r8, r3
	ldr	r3, [r4, #1256]
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2505
	add	r2, r0, #8
	mov	r3, r3, asl #3
	cmp	r2, r3
	bhi	.L2505
	mov	r9, #0
	b	.L2506
.L2507:
	add	r2, r0, #8
	cmp	r2, r3
	bhi	.L2505
.L2506:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r9, r9, #1
	ldr	r3, [r4, #1256]
	cmp	r9, r8
	ldr	r0, [r4, #1264]
	mov	r3, r3, asl #3
	bne	.L2507
.L2505:
	ldr	r2, [fp, #-56]
	mov	r1, r2, asr #31
	mov	r1, r1, lsr #29
	add	r2, r2, r1
	and	r2, r2, #7
	rsb	r1, r1, r2
	add	r2, r0, r1
	cmp	r2, r3
	bls	.L2728
.L2503:
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	bge	.L2691
	movw	r3, #11022
.L2692:
	ldr	r2, .L2732+116
	mov	r0, #20
	ldr	r1, .L2732+120
	bl	dprint_vfmw
	ldr	r3, [r10, #1392]
	b	.L2498
.L2477:
	mov	r3, r5
	ldr	r1, .L2732+104
	mov	r0, #20
	bl	dprint_vfmw
	ldr	r8, [r10, #1392]
	mov	r3, #1
	str	r3, [fp, #-60]
	cmp	r8, #3
	bls	.L2522
.L2721:
	ldr	r1, [r10, #1396]
	ldr	r0, [r10, #2680]
	bl	FreeUsdByDec
	ldr	r1, [r10, #1400]
	ldr	r0, [r10, #2680]
	bl	FreeUsdByDec
	ldr	r1, [r10, #1404]
	ldr	r0, [r10, #2680]
	bl	FreeUsdByDec
	ldr	r1, [r10, #1408]
	ldr	r0, [r10, #2680]
	bl	FreeUsdByDec
	mov	r3, #0
	mov	r8, r3
	str	r3, [r10, #1396]
	str	r3, [r10, #1400]
	str	r3, [r10, #1404]
	str	r3, [r10, #1408]
	str	r3, [r10, #1392]
	b	.L2522
.L2733:
	.align	2
.L2732:
	.word	s_pstVfmwChan
	.word	.LC311
	.word	.LC312
	.word	.LC340
	.word	.LC339
	.word	.LC335
	.word	.LC334
	.word	.LC333
	.word	.LC332
	.word	.LC337
	.word	.LC336
	.word	.LC338
	.word	.LC331
	.word	.LC330
	.word	.LC329
	.word	.LC328
	.word	.LC327
	.word	.LC326
	.word	.LC325
	.word	.LC319
	.word	g_event_report
	.word	.LC341
	.word	.LC317
	.word	.LC313
	.word	.LC316
	.word	.LC315
	.word	.LC318
	.word	.LC320
	.word	.LC322
	.word	.LANCHOR0+252
	.word	.LC314
	.word	.LC324
	.word	.LC323
	.word	.LC321
	.word	.LC8
	.word	.LC9
.L2471:
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2729
.L2632:
	cmp	r5, #0
	ble	.L2691
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
	mov	r8, #0
	b	.L2635
.L2636:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2691
.L2635:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2636
	b	.L2691
.L2705:
	cmp	r3, #128
	bne	.L2642
	mov	r0, #0
	b	.L2730
.L2532:
	add	r3, r3, #15680
	ldr	r2, [fp, #-56]
	add	r3, r3, #28
	cmp	r9, r5
	rsb	r8, r2, r5
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r8, [r3, #1052]
	bcc	.L2731
.L2538:
	cmp	r8, #0
	ble	.L2533
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2533
	mov	r5, #0
	b	.L2540
.L2541:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2533
.L2540:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2541
	b	.L2533
.L2697:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L2459
	ldr	r2, [r3, #164]
	cmp	r2, #2
	bne	.L2459
	ldr	r3, [r3, #156]
	cmp	r3, #1
	bne	.L2459
	ldr	r3, [r7, #368]
	mov	r2, #48
	str	r2, [r3, #24]
	b	.L2460
.L2728:
	mov	r0, r6
	bl	BsSkip
	b	.L2503
.L2703:
	movw	r3, #11693
	b	.L2692
.L2702:
	mov	r0, r6
	bl	BsSkip
	b	.L2625
.L2722:
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	mov	r1, #8
	ldr	r2, .L2732+108
	mov	r0, r7
	strb	r3, [ip, #1026]
	ldr	r3, [r10, #1392]
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [fp, #-56]
	bl	u_v
	ldr	r3, [fp, #-56]
	strb	r0, [r3, #1027]
	ldr	r3, [r10, #1392]
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	ldrb	r2, [r3, #1027]	@ zero_extendqisi2
	mov	r1, r3
	str	r3, [fp, #-68]
	cmp	r2, #255
	beq	.L2527
	mov	r3, #3
	mov	r2, #0
	str	r3, [fp, #-56]
	strb	r2, [r1, #1028]
.L2528:
	ldr	ip, [r10, #1392]
	mov	r1, #16
	str	r3, [fp, #-72]
	mov	r0, r7
	add	ip, ip, #15680
	ldr	r2, .L2732+112
	add	ip, ip, #28
	add	ip, r7, ip, lsl #2
	ldr	r3, [ip, #4]
	str	r3, [fp, #-68]
	bl	u_v
	ldr	r3, [fp, #-72]
	mov	r1, r3
	ldr	r3, [fp, #-68]
	add	r2, r3, #1024
	strh	r0, [r2, #6]	@ movhi
	mov	r0, r7
	bl	PassBytes
	ldr	r3, [fp, #-72]
	cmp	r8, r3
	bne	.L2526
	ldr	r3, [r10, #1392]
	mov	r2, #8
	ldr	r1, [r7]
	add	r3, r3, #15680
	b	.L2694
.L2731:
	rsb	r1, r9, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	bge	.L2538
	movw	r3, #11215
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2538
.L2646:
	mov	r3, #0
	mov	r8, r3
	b	.L2523
.L2729:
	movw	r3, #11705
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2632
.L2727:
	movw	r3, #11034
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2510
.L2726:
	movw	r3, #10969
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2496
.L2725:
	movw	r3, #11060
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2515
.L2720:
	movw	r3, #11277
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2549
.L2719:
	movw	r3, #11303
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2554
.L2718:
	movw	r3, #11329
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2559
.L2717:
	movw	r3, #11355
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2564
.L2716:
	movw	r3, #11381
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2569
.L2715:
	movw	r3, #11407
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2574
.L2714:
	movw	r3, #11589
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2609
.L2713:
	movw	r3, #11537
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2599
.L2712:
	movw	r3, #11563
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2604
.L2711:
	movw	r3, #11433
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2579
.L2710:
	movw	r3, #11459
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2584
.L2709:
	movw	r3, #11485
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2589
.L2708:
	movw	r3, #11511
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2594
.L2707:
	movw	r3, #11615
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2614
.L2706:
	movw	r3, #11641
	ldr	r2, .L2732+116
	ldr	r1, .L2732+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2619
.L2724:
	ldr	r1, .L2732+124
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #1392]
	ldr	r0, [r10, #2680]
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	r1, [r3, #4]
	bl	FreeUsdByDec
	ldr	r3, [r10, #1392]
	mov	r2, #0
	mvn	r0, #0
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r7, r7, r3, lsl #2
	str	r2, [r7, #4]
	b	.L2458
.L2645:
	mvn	r0, #0
	b	.L2458
.L2723:
	ldr	r1, .L2732+128
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #1392]
	ldr	r0, [r10, #2680]
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	ldr	r1, [r3, #4]
	bl	FreeUsdByDec
	ldr	r3, [r10, #1392]
	mov	r2, #0
	mvn	r0, #0
	add	r3, r3, #15680
	add	r3, r3, #28
	add	r3, r7, r3, lsl #2
	str	r2, [r3, #4]
	b	.L2458
.L2527:
	ldr	r2, .L2732+132
	mov	r1, #8
	mov	r0, r7
	mov	r3, #4
	str	r3, [fp, #-56]
	bl	u_v
	ldr	r2, [fp, #-68]
	ldr	r3, [fp, #-56]
	strb	r0, [r2, #1028]
	b	.L2528
.L2696:
	movw	r3, #10873
	ldr	r2, .L2732+136
	ldr	r1, .L2732+140
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2458
	UNWIND(.fnend)
	.size	H264_DecSEI, .-H264_DecSEI
	.align	2
	.global	H264_IsNewPicNal
	.type	H264_IsNewPicNal, %function
H264_IsNewPicNal:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	mov	r5, r0
	and	r3, r3, #31
	sub	r3, r3, #1
	cmp	r3, #7
	ldrls	pc, [pc, r3, asl #2]
	b	.L2742
.L2737:
	.word	.L2736
	.word	.L2742
	.word	.L2742
	.word	.L2742
	.word	.L2736
	.word	.L2742
	.word	.L2738
	.word	.L2738
.L2738:
	ldr	r0, [r0]
	mov	r3, #1
	str	r3, [r5]
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2736:
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L2739
.L2741:
	mvn	r0, #0
.L2740:
	mov	r3, #0
	str	r3, [r5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2742:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2739:
	ldrb	r3, [r1, #5]	@ zero_extendqisi2
	ldrb	r0, [r1, #6]	@ zero_extendqisi2
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	ldrb	r4, [r1, #4]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r3, r3, r0, asl #8
	orr	r3, r3, r2
	orr	r4, r3, r4, asl #24
	mov	r0, r4
	bl	ZerosMS_32
	cmp	r0, #15
	bhi	.L2741
	mov	r0, r0, asl #1
	rsb	r0, r0, #31
	mov	r0, r4, lsr r0
	subs	r0, r0, #1
	mvnne	r0, #0
	b	.L2740
	UNWIND(.fnend)
	.size	H264_IsNewPicNal, .-H264_IsNewPicNal
	.align	2
	.global	FindZeroBitsInSeg
	.type	FindZeroBitsInSeg, %function
FindZeroBitsInSeg:
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
	cmp	r0, #0
	cmpne	r1, #0
	mov	r9, r0
	str	r1, [fp, #-48]
	movle	r4, #1
	movgt	r4, #0
	ble	.L2769
	ldr	r3, [fp, #-48]
	subs	r7, r3, #0
	add	r8, r3, #63
	movge	r8, r3
	ands	r3, r3, #63
	movne	r3, #1
	add	r8, r3, r8, asr #6
	cmp	r8, #0
	ble	.L2757
	ldr	r5, .L2770
	ldr	r10, .L2770+4
.L2755:
	cmp	r7, #64
	ldr	r3, [r10, #52]
	ldr	r0, .L2770
	movcc	r6, r7
	movcs	r6, #64
	mov	r2, r6
	rsb	r1, r6, r7
	sub	r6, r6, #1
	add	r1, r9, r1
	blx	r3
	add	r3, r5, r6
	ldrb	r2, [r5, r6]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2747
	ldr	r2, .L2770
	add	r4, r4, #1
	cmp	r3, r2
	bne	.L2750
	b	.L2748
.L2751:
	cmp	r3, r5
	add	r4, r4, #1
	beq	.L2748
.L2750:
	ldrb	r2, [r3, #-1]!	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2751
.L2747:
	mov	r0, r4, asl #3
.L2746:
	ldr	r3, [fp, #-48]
	cmp	r4, r3
	bge	.L2759
	sub	r3, r3, #1
	rsb	r4, r4, r3
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	tst	r2, #1
	moveq	r2, r2, lsr #1
	moveq	r3, #1
	bne	.L2759
.L2754:
	tst	r2, #1
	mov	r2, r2, lsr #1
	bne	.L2752
	add	r3, r3, #1
	cmp	r3, #8
	bne	.L2754
	b	.L2752
.L2748:
	subs	r8, r8, #1
	sub	r7, r7, #64
	bne	.L2755
	b	.L2747
.L2759:
	mov	r3, #0
.L2752:
	add	r0, r3, r0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2769:
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L2770+8
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2757:
	mov	r0, r4
	b	.L2746
.L2771:
	.align	2
.L2770:
	.word	.LANCHOR3-1976
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC342
	UNWIND(.fnend)
	.size	FindZeroBitsInSeg, .-FindZeroBitsInSeg
	.align	2
	.global	FindTrailZeros
	.type	FindTrailZeros, %function
FindTrailZeros:
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
	beq	.L2778
	ldr	r3, [r4, #368]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2777
	ldr	r1, [r3, #40]
	ldr	r0, [r3, #36]
	bl	FindZeroBitsInSeg
	ldr	r3, [r4, #368]
	ldr	r2, [r3, #40]
	cmp	r0, r2, asl #3
	bcs	.L2781
	cmn	r0, #1
	beq	.L2777
.L2776:
	add	r0, r0, #1
	str	r0, [r3, #72]
	ldr	r3, [r4, #368]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2780
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #72]
	cmp	r2, r1, asl #3
	bcs	.L2782
.L2780:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2782:
	add	r2, r4, #61440
	ldr	r1, [r3, #60]
	ldr	r0, [r2, #2680]
	bl	SM_ReleaseStreamSeg
	ldr	r2, [r4, #368]
	mov	r3, #0
	mov	r1, #1
	mov	r0, r3
	str	r3, [r2, #36]
	ldr	r2, [r4, #368]
	str	r1, [r2, #68]
	ldr	r2, [r4, #368]
	str	r3, [r2, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2781:
	add	r2, r4, #61440
	ldr	r1, [r3, #60]
	ldr	r0, [r2, #2680]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #368]
	mov	r1, #0
	mov	r2, #1
	str	r1, [r3, #36]
	ldr	r3, [r4, #368]
	str	r2, [r3, #68]
	ldr	r3, [r4, #368]
.L2777:
	ldr	r1, [r3, #12]
	ldr	r0, [r3, #8]
	bl	FindZeroBitsInSeg
	ldr	r3, [r4, #368]
	b	.L2776
.L2778:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	FindTrailZeros, .-FindTrailZeros
	.align	2
	.global	CombinePacket
	.type	CombinePacket, %function
CombinePacket:
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
	subs	r4, r0, #0
	beq	.L2783
	ldr	r3, [r4, #368]
	ldr	r3, [r3, #12]
	cmp	r3, #4096
	bcs	.L2783
	ldr	r1, .L2788
	mov	r0, #7
	bl	dprint_vfmw
	ldr	ip, [r4, #368]
	ldr	r1, .L2788+4
	mov	r0, #7
	mov	r5, #0
	ldr	lr, [ip, #40]
	ldr	r3, [ip, #44]
	ldr	r2, [ip, #16]
	str	lr, [sp, #4]
	ldr	ip, [ip, #12]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #368]
	ldr	ip, .L2788+8
	ldr	r2, [r3, #12]
	ldr	r0, [r3, #36]
	ldr	r1, [r3, #8]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #368]
	mov	ip, #1
	ldr	r1, .L2788+12
	mov	r0, #7
	ldr	r2, [r3, #60]
	ldr	r6, [r3, #32]
	str	r2, [r3, #32]
	ldr	r3, [r4, #368]
	str	r5, [r3, #24]
	ldr	r3, [r4, #368]
	ldr	lr, [r3, #12]
	ldr	r2, [r3, #36]
	rsb	r2, lr, r2
	str	r2, [r3, #8]
	ldr	r3, [r4, #368]
	ldr	lr, [r3, #12]
	ldr	r2, [r3, #44]
	rsb	r2, lr, r2
	str	r2, [r3, #16]
	ldr	r3, [r4, #368]
	ldr	r2, [r3, #12]
	ldr	lr, [r3, #40]
	add	r2, r2, lr
	str	r2, [r3, #12]
	ldr	r3, [r4, #368]
	str	ip, [r3, #68]
	ldr	r2, [r4, #368]
	ldr	r3, [r2, #12]
	ldr	r2, [r2, #16]
	bl	dprint_vfmw
	add	r3, r4, #61440
	mov	r1, r6
	ldr	r0, [r3, #2680]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #368]
	str	r5, [r3, #36]
	ldr	r3, [r4, #368]
	str	r5, [r3, #52]
	ldr	r3, [r4, #368]
	str	r5, [r3, #40]
.L2783:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2789:
	.align	2
.L2788:
	.word	.LC343
	.word	.LC344
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC345
	UNWIND(.fnend)
	.size	CombinePacket, .-CombinePacket
	.align	2
	.global	FindNaluArraySlot
	.type	FindNaluArraySlot, %function
FindNaluArraySlot:
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
	subs	ip, r0, #0
	beq	.L2795
	ldrb	r0, [ip, #377]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L2796
	mov	r2, ip
	mov	r3, #1
	b	.L2794
.L2793:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L2795
.L2794:
	ldrb	r1, [r2, #473]	@ zero_extendqisi2
	add	r2, r2, #96
	cmp	r1, #0
	bne	.L2793
	mov	r0, r3
.L2792:
	mov	r2, r3, asl #7
	mov	r1, #1
	sub	r3, r2, r3, asl #5
	add	ip, ip, r3
	strb	r1, [ip, #377]
	ldmfd	sp, {fp, sp, pc}
.L2795:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L2796:
	mov	r3, r0
	b	.L2792
	UNWIND(.fnend)
	.size	FindNaluArraySlot, .-FindNaluArraySlot
	.align	2
	.global	InquireSliceExtProperty
	.type	InquireSliceExtProperty, %function
InquireSliceExtProperty:
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
	add	r0, r0, #13504
	add	r0, r0, #24
	mov	r1, #24
	bl	BsGet
	ldr	r3, [r4, #368]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #3]
	ldr	r2, [r4, #368]
	ldrb	r3, [r2, #3]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r4, #61440
	ldreqb	r0, [r3, #740]	@ zero_extendqisi2
	beq	.L2801
	ubfx	lr, r0, #16, #6
	ubfx	ip, r0, #15, #1
	ubfx	r1, r0, #12, #3
	strb	lr, [r3, #741]
	strb	ip, [r3, #742]
	ubfx	lr, r0, #8, #4
	ubfx	ip, r0, #5, #3
	strb	r1, [r3, #743]
	strb	lr, [r3, #744]
	ubfx	r1, r0, #4, #1
	ubfx	lr, r0, #3, #1
	strb	ip, [r3, #745]
	strb	r1, [r3, #746]
	ubfx	ip, r0, #2, #1
	and	r1, r0, #3
	strb	lr, [r3, #747]
	ubfx	r0, r0, #22, #1
	strb	ip, [r3, #748]
	strb	r1, [r3, #749]
	strb	r0, [r3, #740]
.L2801:
	cmp	r0, #1
	mov	r0, #0
	moveq	r3, #5
	streqb	r3, [r2, #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	InquireSliceExtProperty, .-InquireSliceExtProperty
	.align	2
	.global	InquireSliceProperty
	.type	InquireSliceProperty, %function
InquireSliceProperty:
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
	add	r3, r0, #61440
	mov	r5, r2
	mov	r4, r0
	mov	r8, r1
	ldr	r2, [r3, #2624]
	mov	r0, #22
	ldr	r1, .L2812
	add	r6, r4, #20480
	sub	r2, r2, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5]
	mov	r0, r4
	str	r3, [r8]
	ldr	r3, [r4, #368]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	strb	r2, [r6, #211]
	ldr	r3, [r3, #76]
	str	r3, [r6, #236]
	bl	SliceCheck
	subs	r7, r0, #0
	bne	.L2807
	mov	r0, r4
	bl	ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L2811
	ldrb	r1, [r6, #213]	@ zero_extendqisi2
	add	r0, r4, #12288
	mov	ip, #2208
	mov	r3, #4000
	sub	r1, r1, #1
	add	r4, r4, #24576
	clz	r1, r1
	mov	r1, r1, lsr #5
	str	r1, [r8]
	ldr	r1, [r6, #216]
	ldr	r2, [r0, #1304]
	ldr	lr, [r0, #1300]
	mla	r2, ip, r1, r2
	ldr	ip, [r0, #1280]
	ldr	r0, [r0, #1276]
	ldr	r2, [r2, #28]
	mla	r3, r3, r2, lr
	ldrb	r1, [r3, #18]	@ zero_extendqisi2
	ldr	lr, [r3, #3252]
	rsb	r2, r1, #2
	ldr	r1, [r3, #3248]
	mla	r2, lr, r2, r2
	add	r1, r1, #1
	cmp	r0, r1
	cmpeq	ip, r2
	movne	r2, #1
	strne	r2, [r5]
	ldr	r2, [r3, #3272]
	ldr	r3, [r4, #2136]
	add	r3, r3, #1
	cmp	r2, r3
	movne	r3, #1
	strne	r3, [r5]
.L2804:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2807:
	mvn	r7, #0
	b	.L2804
.L2811:
	ldr	r1, .L2812+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2804
.L2813:
	.align	2
.L2812:
	.word	.LC346
	.word	.LC347
	UNWIND(.fnend)
	.size	InquireSliceProperty, .-InquireSliceProperty
	.align	2
	.global	HaveSliceToDec
	.type	HaveSliceToDec, %function
HaveSliceToDec:
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
	add	r0, r0, #61440
	ldr	r0, [r0, #2604]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HaveSliceToDec, .-HaveSliceToDec
	.align	2
	.global	H264DEC_Destroy
	.type	H264DEC_Destroy, %function
H264DEC_Destroy:
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
	subs	r9, r0, #0
	beq	.L2836
	add	r8, r9, #61440
	bl	H264_ClearCurrPic
	mov	r0, r9
	bl	ClearAllNal
	ldr	r3, [r8, #2616]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [r8, #2616]
	ldr	r3, [r8, #1392]
	cmp	r3, #0
	beq	.L2818
	add	r5, r9, #62720
	mov	r4, #0
	add	r5, r5, #112
	mov	r6, r4
.L2820:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L2819
	ldr	r0, [r8, #2680]
	bl	FreeUsdByDec
	str	r6, [r5]
.L2819:
	ldr	r3, [r8, #1392]
	cmp	r3, r4
	bhi	.L2820
.L2818:
	add	r5, r9, #27904
	add	r9, r9, #61184
	add	r5, r5, #72
	add	r9, r9, #72
	mov	r6, #0
	mov	r7, #0
.L2824:
	sub	r4, r5, #32
.L2822:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L2821
	ldr	r0, [r8, #2680]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L2821:
	cmp	r4, r5
	bne	.L2822
	add	r5, r4, #832
	cmp	r5, r9
	bne	.L2824
	ldr	r1, .L2837
	mov	r0, #2
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L2836:
	movw	r3, #12685
	ldr	r2, .L2837+4
	ldr	r1, .L2837+8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L2838:
	.align	2
.L2837:
	.word	.LC348
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264DEC_Destroy, .-H264DEC_Destroy
	.align	2
	.global	H264DEC_RecycleImage
	.type	H264DEC_RecycleImage, %function
H264DEC_RecycleImage:
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
	mov	r5, r0
	mov	r8, r1
	mov	r0, #2
	ldr	r1, .L2852
	bl	dprint_vfmw
	cmp	r5, #0
	beq	.L2850
	add	r5, r5, #61440
	mov	r1, r8
	ldr	r0, [r5, #2680]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L2845
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	beq	.L2845
	add	r4, r0, #576
	add	r9, r0, #608
	mov	r6, #0
	mov	r7, #0
.L2843:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L2851
.L2842:
	cmp	r4, r9
	bne	.L2843
	ldr	r0, [r5, #2680]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2851:
	mov	r1, r2
	ldr	r0, [r5, #2680]
	bl	FreeUsdByDec
	strd	r6, [r4]
	b	.L2842
.L2845:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2850:
	mov	r0, r5
	movw	r3, #13409
	ldr	r2, .L2852+4
	ldr	r1, .L2852+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2853:
	.align	2
.L2852:
	.word	.LC349
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264DEC_RecycleImage, .-H264DEC_RecycleImage
	.align	2
	.global	OutputFrmToVO
	.type	OutputFrmToVO, %function
OutputFrmToVO:
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
	mov	r7, r2
	mov	r4, r0
	moveq	r3, #1
	movne	r3, #0
	mov	r5, r1
	beq	.L2896
	ldr	r2, [r0]
	ldr	r2, [r2, #24]
	cmp	r2, #0
	beq	.L2857
	add	r2, r0, #61440
	ldr	r1, [r2, #2608]
	cmp	r1, #2
	beq	.L2857
	ldr	r1, [r2, #732]
	cmp	r1, #0
	strneb	r3, [r1, #1]
	movne	r0, #1
	strne	r3, [r2, #732]
	beq	.L2859
.L2856:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2857:
	mov	r1, r5
	mov	r0, r4
	bl	CheckFrameStore
	cmn	r0, #3
	beq	.L2859
	add	r6, r4, #61440
	ldr	r1, [r6, #732]
	cmp	r1, #0
	beq	.L2860
	mov	r0, r4
	bl	GetImagePara
	ldr	r1, [r6, #732]
	mov	r0, r4
	bl	CheckFrameStore
	subs	r3, r0, #0
	beq	.L2897
	cmn	r3, #3
	beq	.L2867
	ldr	r1, .L2905
	movw	r2, #2215
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #732]
	mov	r0, r4
	ldr	r1, [r3, #164]
	bl	H264DEC_RecycleImage
.L2867:
	ldr	r3, [r6, #732]
	mov	r0, #0
	strb	r0, [r3, #1]
	ldr	r3, [r6, #732]
	str	r0, [r6, #732]
	cmp	r5, r3
	beq	.L2856
.L2860:
	mov	r1, r5
	mov	r0, r4
	bl	GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	CheckFrameStore
	subs	r3, r0, #0
	beq	.L2898
	cmn	r3, #3
	beq	.L2859
	mov	r2, #2272
	ldr	r1, .L2905
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #164]
	mov	r0, r4
	bl	H264DEC_RecycleImage
	mov	r0, #2
	b	.L2856
.L2896:
	mov	r3, r1
	mov	r2, r0
	ldr	r1, .L2905+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #2
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2859:
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2898:
	mov	r2, #1
	ldr	r1, [r5, #656]
	ldr	r0, [r6, #2680]
	bl	FSP_SetDisplay
	ldr	r1, [r5, #656]
	ldr	r0, [r6, #2680]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L2899
	cmp	r7, #1
	add	r3, r4, #8
	streq	r7, [r8, #180]
	mov	r2, r4
	ldr	r0, [r6, #2680]
	mov	r1, #0
	str	r8, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L2900
	ldr	r3, [r4]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r8, #16]
	bcs	.L2901
.L2874:
	ldr	r2, [r6, #2708]
	mov	r0, #0
	ldr	r3, [r6, #2700]
	add	r2, r2, #1
	str	r2, [r6, #2708]
	add	r3, r3, #2
	str	r3, [r6, #2700]
	b	.L2856
.L2897:
	ldr	r3, [r6, #732]
	mov	r2, #1
	ldr	r0, [r6, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetDisplay
	ldr	r3, [r6, #732]
	ldr	r0, [r6, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L2902
	ldr	r3, [r6, #732]
	mov	r2, r4
	mov	r1, #0
	cmp	r5, r3
	cmpeq	r7, #1
	moveq	r3, #1
	streq	r3, [r8, #180]
	add	r3, r4, #8
	ldr	r0, [r6, #2680]
	str	r8, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L2903
	ldr	r3, [r4]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r8, #16]
	bcs	.L2904
.L2866:
	ldr	r2, [r6, #2708]
	ldr	r3, [r6, #2700]
	add	r2, r2, #1
	str	r2, [r6, #2708]
	add	r3, r3, #2
	str	r3, [r6, #2700]
	b	.L2867
.L2901:
	mov	r1, r8
	mov	r0, r4
	bl	SetFrmRepeatCount.part.7
	b	.L2874
.L2904:
	mov	r1, r8
	mov	r0, r4
	bl	SetFrmRepeatCount.part.7
	b	.L2866
.L2900:
	mov	r2, r0
	ldr	r1, .L2905+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r5, #656]
	ldr	r0, [r6, #2680]
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, r4
	mov	r1, #1
	bl	ClearAll
	mvn	r0, #0
	b	.L2856
.L2903:
	mov	r2, r0
	ldr	r1, .L2905+8
	mov	r0, #0
	mov	r5, r0
	bl	dprint_vfmw
	ldr	r3, [r6, #732]
	mov	r2, r5
	strb	r5, [r3, #1]
	ldr	r3, [r6, #732]
	ldr	r0, [r6, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetDisplay
	str	r5, [r6, #732]
	mov	r0, r4
	mov	r1, #1
	bl	ClearAll
	mvn	r0, #0
	b	.L2856
.L2899:
	movw	r2, #2242
	ldr	r1, .L2905+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2856
.L2902:
	movw	r2, #2186
	ldr	r1, .L2905+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2856
.L2906:
	.align	2
.L2905:
	.word	.LC353
	.word	.LC350
	.word	.LC352
	.word	.LC354
	.word	.LC351
	UNWIND(.fnend)
	.size	OutputFrmToVO, .-OutputFrmToVO
	.align	2
	.global	OutputFrmFromDPB
	.type	OutputFrmFromDPB, %function
OutputFrmFromDPB:
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
	subs	r6, r0, #0
	mov	r7, r1
	beq	.L2912
	add	r4, r6, r1, lsl #2
	add	r4, r4, #24576
	ldr	r3, [r4, #1944]
	cmp	r3, #0
	beq	.L2913
	mov	r2, #0
	strb	r2, [r3, #4]
	ldr	r1, [r4, #1944]
	bl	OutputFrmToVO
	ldr	r3, [r4, #1944]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r5, r0
	beq	.L2914
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2914:
	mov	r0, r6
	mov	r1, r7
	bl	RemoveFrameStoreOutDPB
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2913:
	mov	r0, r3
	ldr	r2, .L2915
	movw	r3, #2292
	ldr	r1, .L2915+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2912:
	movw	r3, #2291
	ldr	r2, .L2915
	ldr	r1, .L2915+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2916:
	.align	2
.L2915:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	OutputFrmFromDPB, .-OutputFrmFromDPB
	.align	2
	.global	FlushDPB
	.type	FlushDPB, %function
FlushDPB:
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
	subs	r4, r0, #0
	beq	.L2918
	add	r6, r4, #24576
	ldr	r3, [r6, #2140]
	cmp	r3, #0
	addne	r7, r4, #26368
	movne	r5, #0
	addne	r7, r7, #148
	bne	.L2923
	b	.L2920
.L2922:
	ldr	r3, [r6, #2140]
	cmp	r3, r5
	bls	.L2920
.L2923:
	ldr	r1, [r7, #4]!
	add	r5, r5, #1
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2922
	mov	r0, r4
	bl	UnMarkFrameStoreRef
	ldr	r3, [r6, #2140]
	cmp	r3, r5
	bhi	.L2923
.L2920:
	mov	r0, r4
	bl	RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L2925
	mov	r0, r4
	bl	RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L2920
	b	.L2925
.L2926:
	bl	GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	OutputFrmFromDPB
	cmn	r0, #1
	beq	.L2921
.L2925:
	ldr	r3, [r6, #2140]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L2926
	mov	r0, r3
.L2921:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2918:
	movw	r3, #2414
	ldr	r2, .L2934
	ldr	r1, .L2934+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2921
.L2935:
	.align	2
.L2934:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	FlushDPB, .-FlushDPB
	.align	2
	.global	AdaptiveMemMark
	.type	AdaptiveMemMark, %function
AdaptiveMemMark:
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
	add	r3, r0, #57344
	add	r8, r0, #60672
	add	r2, r0, #26368
	ldr	r4, [r3, #3988]
	mov	r6, r0
	str	r3, [fp, #-56]
	add	r1, r0, #16384
	add	r7, r4, #2000
	add	r4, r4, #4
	add	r7, r7, #4
	add	r3, r2, #212
	str	r1, [fp, #-48]
	str	r3, [fp, #-52]
.L2949:
	ldr	r3, [r4]
	cmp	r3, #6
	ldrls	pc, [pc, r3, asl #2]
	b	.L2937
.L2939:
	.word	.L2938
	.word	.L2940
	.word	.L2941
	.word	.L2942
	.word	.L2943
	.word	.L2944
	.word	.L2945
.L2945:
	ldr	r2, [r4, #12]
	mov	r1, r8
	mov	r0, r6
	bl	MarkCurrPicLT
.L2937:
	add	r4, r4, #20
	cmp	r4, r7
	bne	.L2949
.L2938:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #3444]
	cmp	r3, #1
	movne	r0, #0
	beq	.L2958
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2944:
	add	r9, r6, #24576
	ldr	r3, [r9, #2144]
	cmp	r3, #0
	ldrne	r10, [fp, #-52]
	movne	r5, #0
	beq	.L2948
.L2947:
	ldr	r1, [r10, #4]!
	mov	r0, r6
	bl	UnMarkFrameStoreRef
	ldr	r3, [r9, #2144]
	add	r5, r5, #1
	cmp	r5, r3
	bcc	.L2947
.L2948:
	mov	r0, r6
	bl	UpdateReflist
	mov	r1, #0
	mov	r0, r6
	bl	UpdateMaxLTFrmIdx
	mov	r0, r6
	bl	UpdateLTReflist
	ldr	r2, [fp, #-48]
	mov	r3, #1
	str	r3, [r2, #3444]
	b	.L2937
.L2943:
	mov	r0, r6
	ldr	r1, [r4, #16]
	bl	UpdateMaxLTFrmIdx
	mov	r0, r6
	bl	UpdateLTReflist
	b	.L2937
.L2942:
	ldr	r3, [r4, #12]
	mov	r1, r8
	ldr	r2, [r4, #4]
	mov	r0, r6
	bl	MarkSTToLTRef
	mov	r0, r6
	bl	UpdateReflist
	mov	r0, r6
	bl	UpdateLTReflist
	b	.L2937
.L2941:
	mov	r0, r6
	ldr	r2, [r4, #8]
	mov	r1, r8
	bl	UnMarkLTRef
	mov	r0, r6
	bl	UpdateLTReflist
	b	.L2937
.L2940:
	mov	r0, r6
	ldr	r2, [r4, #4]
	mov	r1, r8
	bl	UnMarkSTRef
	mov	r0, r6
	bl	UpdateReflist
	b	.L2937
.L2958:
	ldr	r1, [fp, #-56]
	mov	r3, #0
	ldrb	r2, [r1, #3331]	@ zero_extendqisi2
	str	r3, [r1, #3992]
	cmp	r2, #1
	beq	.L2952
	bcc	.L2953
	cmp	r2, #2
	bne	.L2951
	ldr	r2, [fp, #-56]
	str	r3, [r2, #4016]
	str	r3, [r2, #4004]
	ldr	r2, [fp, #-48]
	str	r3, [r2, #3456]
	str	r3, [r2, #3464]
.L2951:
	mov	r0, r6
	bl	FlushDPB
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2953:
	ldr	r0, [fp, #-56]
	ldr	r1, [r0, #4004]
	ldr	r2, [r0, #4012]
	ldr	r3, [r0, #4016]
	rsb	r2, r1, r2
	str	r2, [r0, #4012]
	rsb	r3, r1, r3
	str	r3, [r0, #4016]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r0, #4008]
	str	r3, [r0, #4004]
	ldr	r0, [fp, #-48]
	ldr	r1, [r0, #3464]
	ldr	r2, [r0, #3452]
	ldr	r3, [r0, #3456]
	rsb	r2, r1, r2
	str	r2, [r0, #3452]
	rsb	r3, r1, r3
	str	r3, [r0, #3456]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r0, #3460]
	str	r3, [r0, #3464]
	b	.L2951
.L2952:
	ldr	r2, [fp, #-56]
	str	r3, [r2, #4012]
	str	r3, [r2, #4004]
	ldr	r2, [fp, #-48]
	str	r3, [r2, #3452]
	str	r3, [r2, #3464]
	b	.L2951
	UNWIND(.fnend)
	.size	AdaptiveMemMark, .-AdaptiveMemMark
	.align	2
	.global	IDRMemMarking
	.type	IDRMemMarking, %function
IDRMemMarking:
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
	add	r3, r0, #57344
	str	r3, [fp, #-52]
	ldr	r3, [r3, #3988]
	str	r0, [fp, #-48]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2960
	add	r10, r0, #24576
	ldr	r3, [r10, #2140]
	cmp	r3, #0
	beq	.L2980
	ldr	r3, [fp, #-48]
	mov	r9, #0
	mov	r4, r9
	add	r5, r3, #26368
	add	r7, r3, #26624
	add	r7, r7, #20
	add	r6, r3, #61440
	mov	r8, r5
	add	r5, r5, #152
	add	r8, r8, #212
.L2966:
	ldr	r1, [r5]
	mov	r2, #0
	add	r9, r9, #1
	ldr	r0, [r1, #824]
	cmp	r0, #1
	streq	r0, [r6, #1380]
	strb	r4, [r1, #706]
	strb	r4, [r1, #705]
	ldr	r1, [r5]
	strb	r4, [r1, #746]
	strb	r4, [r1, #745]
	ldr	r1, [r5]
	strb	r4, [r1, #786]
	strb	r4, [r1, #785]
	ldr	r1, [r5]
	strb	r4, [r1, #2]
	ldr	r1, [r5]
	ldr	r0, [r6, #2680]
	ldr	r1, [r1, #656]
	bl	FSP_SetRef
	ldr	r2, [r5]
	mov	r3, #1
	strb	r4, [r2, #1]
	ldr	r2, [r5]
	strb	r4, [r2, #4]
	ldr	r2, [r5]
	str	r3, [r2, #676]
	ldr	r1, [r5]
	ldr	r3, [fp, #-48]
	ldr	r2, [r1, #696]
	add	r2, r2, #6656
	add	r2, r2, #26
	add	r2, r3, r2, lsl #2
	str	r4, [r2, #4]
	ldr	r1, [r1, #656]
	ldr	r0, [r6, #2680]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L2965
	ldr	r1, [r5]
	ldr	r0, [r6, #2680]
	ldr	r1, [r1, #656]
	bl	FSP_SetDisplay
.L2965:
	str	r4, [r5], #4
	str	r4, [r8, #4]!
	str	r4, [r7, #4]!
	ldr	r2, [r10, #2140]
	cmp	r2, r9
	bhi	.L2966
.L2967:
	mov	r3, #0
	str	r3, [r10, #2140]
	ldr	r1, [r6, #1368]
	cmp	r1, r3
	beq	.L2963
	ldr	r2, [fp, #-48]
	mov	r0, r3
	add	r2, r2, #62720
	add	r2, r2, #12
.L2970:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L2970
.L2963:
	ldr	r4, [fp, #-48]
	mov	r0, r4
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	ldr	r3, [fp, #-52]
	ldr	r3, [r3, #3988]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2981
	ldr	r2, [fp, #-52]
	mov	r0, r3
	str	r3, [r10, #2152]
	strb	r3, [r2, #3332]
	mov	r3, #1
	strb	r3, [r2, #3333]
.L2971:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2981:
	ldr	r1, [fp, #-52]
	mov	r3, #0
	mov	r2, #1
	mov	r0, r3
	str	r2, [r10, #2152]
	strb	r2, [r1, #3332]
	str	r3, [r1, #3996]
	strb	r3, [r1, #3333]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2960:
	bl	FlushDPB
	cmp	r0, #0
	bne	.L2972
	ldr	r3, [fp, #-48]
	add	r10, r3, #24576
	b	.L2963
.L2980:
	add	r6, r0, #61440
	b	.L2967
.L2972:
	mvn	r0, #0
	b	.L2971
	UNWIND(.fnend)
	.size	IDRMemMarking, .-IDRMemMarking
	.align	2
	.global	Marking
	.type	Marking, %function
Marking:
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
	add	r4, r0, #57344
	mov	r3, #0
	mov	r5, r0
	str	r3, [r6, #3444]
	ldrb	r3, [r4, #3331]	@ zero_extendqisi2
	sub	r3, r3, #2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r6, #3448]
	ldrb	r3, [r4, #3334]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L2983
	ldr	r3, [r4, #4020]
	cmp	r3, #0
	bne	.L2984
	ldr	r3, [r0]
	ldr	r2, [r3, #660]
	cmp	r2, #1
	beq	.L3008
.L2984:
	ldr	r3, [r4, #3988]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r4, #4000]
	beq	.L3009
	cmp	r3, #0
	bne	.L3010
.L2991:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3009:
	cmp	r3, #0
	beq	.L2991
.L2990:
	ldrb	r2, [r4, #3329]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2995
	add	r2, r5, #24576
	ldr	r1, [r6, #456]
	ldr	ip, [r2, #2148]
	ldr	r0, [r2, #2144]
	rsb	r2, ip, r1
	cmp	r0, r2
	beq	.L3011
.L2996:
	mov	r2, #0
	strb	r2, [r4, #3332]
.L2993:
	cmp	r3, #0
	beq	.L2991
.L2995:
	ldrb	r3, [r4, #3332]	@ zero_extendqisi2
	mov	r0, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r4, #3333]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3008:
	ldr	r2, [r3, #656]
	cmp	r2, #0
	bne	.L2984
	ldr	r2, [r3, #664]
	cmp	r2, #0
	bne	.L2984
	ldr	r3, [r3, #620]
	add	r3, r3, #1024
	cmp	r3, #2048
	bls	.L2984
.L2983:
	mov	r0, r5
	bl	IDRMemMarking
	cmp	r0, #0
	bne	.L2985
.L2992:
	ldrb	r3, [r4, #3334]	@ zero_extendqisi2
	cmp	r3, #5
	ldreq	r3, [r4, #4000]
	beq	.L2993
	ldr	r3, [r4, #4000]
	cmp	r3, #0
	beq	.L2991
	ldr	r2, [r4, #3988]
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2990
	b	.L2995
.L3010:
	mov	r0, r5
	bl	AdaptiveMemMark
	cmp	r0, #0
	beq	.L2992
.L2985:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3011:
	mov	r0, r5
	bl	SlidingWinMark.part.8
	ldr	r3, [r4, #4000]
	b	.L2996
	UNWIND(.fnend)
	.size	Marking, .-Marking
	.align	2
	.global	InitDPB
	.type	InitDPB, %function
InitDPB:
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
	subs	r7, r0, #0
	beq	.L3050
	bl	ClearAllSlice
	add	r6, r7, #26368
	add	r5, r7, #26624
	mov	r8, #0
	mov	r4, r6
	add	r5, r5, #24
	add	r6, r6, #152
	add	r4, r4, #216
	add	r10, r7, #61440
	mov	r9, r8
.L3018:
	ldr	r3, [r6]
	mov	r2, #1
	add	r8, r8, r2
	cmp	r3, #0
	beq	.L3015
	ldr	r1, [r3, #656]
	ldr	r0, [r10, #2680]
	bl	FSP_ClearLogicFs
.L3015:
	ldr	r3, [r4]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3016
	ldr	r1, [r3, #656]
	ldr	r0, [r10, #2680]
	bl	FSP_ClearLogicFs
.L3016:
	ldr	r3, [r5]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3017
	ldr	r1, [r3, #656]
	ldr	r0, [r10, #2680]
	bl	FSP_ClearLogicFs
.L3017:
	cmp	r8, #16
	str	r9, [r5], #4
	mov	r2, #0
	str	r9, [r4], #4
	str	r9, [r6], #4
	bne	.L3018
	add	r3, r7, #16384
	add	r4, r7, #24576
	ldr	r3, [r3, #484]
	str	r2, [r4, #2140]
	sub	r3, r3, #1
	str	r2, [r4, #2144]
	str	r3, [r4, #2136]
	str	r2, [r4, #2148]
	str	r2, [r4, #2152]
	ldr	r1, [r10, #732]
	cmp	r1, r2
	beq	.L3020
	ldr	r3, [r10, #2608]
	cmp	r3, #2
	beq	.L3051
.L3021:
	ldr	r1, [r1, #656]
	mov	r2, #1
	ldr	r0, [r10, #2680]
	bl	FSP_ClearLogicFs
	add	r3, r7, #57344
	ldr	r3, [r3, #3984]
	cmp	r3, #0
	beq	.L3024
	ldr	r2, [r10, #732]
	ldr	r1, [r3, #656]
	ldr	r3, [r2, #656]
	cmp	r3, r1
	beq	.L3024
	mov	r2, #1
	ldr	r0, [r10, #2680]
	bl	FSP_ClearLogicFs
.L3024:
	mov	r3, #0
	str	r3, [r10, #732]
.L3020:
	ldr	r3, .L3053
	add	r0, r7, #26624
	mov	r2, #392
	mov	r1, #0
	add	r0, r0, #108
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, [r4, #2136]
	add	r3, r7, #62720
	mov	r0, #0
	str	r0, [r4, #2416]
	mov	r2, r3
	add	r3, r3, #12
	add	r2, r2, #80
	str	r1, [r4, #2412]
	mov	r1, r0
.L3025:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L3025
	add	r2, r7, #26880
	add	r3, r7, #27136
	add	r2, r2, #240
	add	r3, r3, #116
	mov	r0, #0
.L3026:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L3026
	add	r2, r7, #27136
	add	r7, r7, #20480
	add	r2, r2, #248
	mov	r0, r1
	str	r1, [r7, #248]
.L3027:
	str	r0, [r3, #4]!
	cmp	r3, r2
	mov	r1, #0
	bne	.L3027
	mov	r0, r1
	str	r1, [r7, #252]
.L3014:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3051:
	mov	r0, r7
	bl	OutputFrmToVO
	cmp	r0, #0
	bne	.L3052
.L3022:
	ldr	r1, [r10, #732]
	cmp	r1, #0
	beq	.L3020
	b	.L3021
.L3052:
	str	r0, [sp]
	movw	r3, #2357
	ldr	r2, .L3053+4
	mov	r0, #22
	ldr	r1, .L3053+8
	bl	dprint_vfmw
	b	.L3022
.L3050:
	movw	r3, #2319
	ldr	r2, .L3053+12
	ldr	r1, .L3053+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3014
.L3054:
	.align	2
.L3053:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+264
	.word	.LC355
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	InitDPB, .-InitDPB
	.align	2
	.global	ClearAll
	.type	ClearAll, %function
ClearAll:
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
	mov	r5, r0
	str	r0, [fp, #-48]
	mov	r4, r1
	mov	r0, #22
	ldr	r1, .L3084
	bl	dprint_vfmw
	cmp	r5, #0
	beq	.L3083
	ldr	r5, [fp, #-48]
	mov	r0, r5
	bl	H264_ClearCurrPic
	mov	r0, r5
	bl	ClearAllNal
	mov	r0, r5
	bl	InitDPB
	ldr	r3, [fp, #-48]
	cmp	r4, #0
	add	r9, r3, #61440
	beq	.L3058
	add	r1, r3, #8
	ldr	r0, [r9, #2680]
	bl	FSP_ClearNotInVoQueue
.L3059:
	ldr	r3, [fp, #-48]
	mov	r8, #0
	mov	r6, #0
	mov	r7, #0
	add	r4, r3, #27904
	add	r4, r4, #72
.L3062:
	sub	r5, r4, #32
	mov	r3, #0
	sub	r2, r4, #584
	mov	r1, #1
	mvn	r10, #0
	mov	lr, #17
	mov	ip, #16
	mov	r0, #2
	str	r8, [r4, #-420]
	strb	r3, [r4, #-584]
	strb	r3, [r4, #-583]
	strb	r3, [r4, #-582]
	str	r3, [r4, #84]
	str	r3, [r4, #76]
	str	r3, [r4, #88]
	strb	r3, [r4, #-580]
	strb	r3, [r4, #120]
	str	r10, [r4, #80]
	str	r1, [r4, #92]
	strb	r1, [r4, #160]
	str	lr, [r4, #108]
	str	ip, [r4, #112]
	str	r2, [r4, #236]
	str	r2, [r4, #196]
	str	r2, [r4, #156]
	strb	r0, [r4, #200]
.L3061:
	ldr	r1, [r5, #8]!
	cmp	r1, #0
	beq	.L3060
	ldr	r0, [r9, #2680]
	bl	FreeUsdByDec
	strd	r6, [r5]
.L3060:
	cmp	r5, r4
	bne	.L3061
	add	r8, r8, #1
	add	r4, r5, #832
	cmp	r8, #40
	bne	.L3062
	ldr	r3, [fp, #-48]
	mov	r4, #0
	mov	r5, #0
	add	r6, r3, #61184
	mov	r7, r6
	add	r6, r6, #40
	add	r7, r7, #72
.L3064:
	ldr	r1, [r6, #8]!
	cmp	r1, #0
	beq	.L3063
	ldr	r0, [r9, #2680]
	bl	FreeUsdByDec
	strd	r4, [r6]
.L3063:
	cmp	r6, r7
	bne	.L3064
	ldr	r3, [r9, #1392]
	cmp	r3, #0
	beq	.L3068
	ldr	r3, [fp, #-48]
	mov	r4, #0
	mov	r6, r4
	add	r5, r3, #62720
	add	r5, r5, #112
.L3067:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3066
	ldr	r0, [r9, #2680]
	bl	FreeUsdByDec
	str	r6, [r5]
.L3066:
	ldr	r3, [r9, #1392]
	cmp	r3, r4
	bhi	.L3067
.L3068:
	ldr	r6, [fp, #-48]
	mov	r4, #0
	ldr	r3, .L3084+4
	mov	r1, r4
	add	r5, r6, #20480
	add	ip, r6, #24576
	str	r4, [r9, #1392]
	movw	r2, #1640
	str	r4, [r9, #2656]
	add	r0, r5, #208
	str	r4, [r9, #1372]
	str	r4, [r9, #2604]
	str	r4, [r9, #2664]
	str	r4, [r9, #2612]
	str	r4, [r9, #1380]
	str	r4, [r9, #2684]
	str	r4, [r9, #1384]
	ldr	r3, [r3, #48]
	str	r4, [r6, #368]
	str	r4, [ip, #1804]
	strb	r4, [r5, #3896]
	strb	r4, [r5, #1892]
	strb	r4, [r5, #3897]
	strb	r4, [r5, #1893]
	blx	r3
	add	r2, r6, #57344
	mov	r0, r4
	mov	r3, #1
	mov	r1, #2
	strb	r3, [r5, #213]
	strb	r1, [r5, #208]
	mov	r3, #256
	strb	r4, [r2, #3328]
	strb	r4, [r9, #704]
	str	r4, [r9, #708]
	str	r3, [r9, #712]
.L3082:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3058:
	add	r0, r3, #8
	bl	ResetVoQueue
	ldr	r0, [r9, #2680]
	bl	FSP_EmptyInstance
	b	.L3059
.L3083:
	ldr	r0, [fp, #-48]
	movw	r3, #2033
	ldr	r2, .L3084+8
	ldr	r1, .L3084+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3082
.L3085:
	.align	2
.L3084:
	.word	.LC356
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	ClearAll, .-ClearAll
	.align	2
	.global	AllocFrameStore
	.type	AllocFrameStore, %function
AllocFrameStore:
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
	add	r3, r0, #20480
	mov	r8, r0
	str	r1, [fp, #-60]
	ldrb	r0, [r3, #209]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L3087
	ldrb	r2, [r3, #210]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3151
	add	r2, r8, #12288
	ldr	r1, [r3, #216]
	str	r2, [fp, #-64]
	mov	r0, #2208
	mov	lr, r2
	ldr	r2, [r2, #1304]
	mov	ip, #4000
	add	r9, r8, #61440
	mla	r2, r0, r1, r2
	ldr	r0, [lr, #1300]
	ldr	r1, [r9, #2608]
	cmp	r1, #2
	ldr	r2, [r2, #28]
	mla	r2, ip, r2, r0
	str	r2, [fp, #-56]
	beq	.L3152
	add	r6, r8, #57344
	mov	r2, #0
	strb	r2, [r6, #3329]
	ldrb	r2, [r9, #704]	@ zero_extendqisi2
	cmp	r2, #1
	mov	r2, #2
	str	r2, [fp, #-52]
	bne	.L3117
.L3113:
	ldr	r1, [r9, #712]
	ldr	r2, [r3, #224]
	cmp	r1, r2
	bne	.L3117
	ldr	r2, [r3, #236]
	cmp	r2, #0
	ldr	r2, [r9, #708]
	beq	.L3153
	cmp	r2, #0
	beq	.L3117
.L3093:
	ldr	r2, [r9, #2692]
	ldr	r1, [r9, #2688]
	rsb	r2, r1, r2
	cmp	r2, #2
	bhi	.L3117
	ldr	r0, [r6, #3984]
	mov	r2, #1
	strb	r2, [r6, #3329]
	cmp	r0, #0
	beq	.L3095
	ldr	r2, [fp, #-52]
	cmp	r2, #2
	beq	.L3154
	ldr	r2, [fp, #-52]
	cmp	r2, #1
	beq	.L3155
.L3120:
	mov	ip, #0
	b	.L3099
.L3087:
	add	r2, r8, #12288
	ldr	r1, [r3, #216]
	str	r2, [fp, #-64]
	mov	lr, #2208
	mov	r4, r2
	ldr	r2, [r2, #1304]
	mov	ip, #4000
	add	r9, r8, #61440
	mla	r2, lr, r1, r2
	ldr	r1, [r4, #1300]
	ldr	lr, [r9, #2608]
	cmp	lr, #2
	streq	r0, [fp, #-52]
	ldr	r2, [r2, #28]
	mla	r2, ip, r2, r1
	str	r2, [fp, #-56]
	beq	.L3114
	add	r6, r8, #57344
	str	r0, [fp, #-52]
	strb	r0, [r6, #3329]
.L3117:
	mov	lr, #0
	strb	lr, [r6, #3328]
	ldr	r7, [r9, #1364]
	cmp	r7, lr
	addne	r5, r8, #26368
	addne	r4, r8, #27392
	addne	r5, r5, #152
	addne	r10, r8, #24576
	beq	.L3107
.L3106:
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3102
	cmp	r4, #0
	beq	.L3103
	ldr	r0, [r10, #2140]
	cmp	r0, #0
	beq	.L3103
	ldr	r1, [r10, #1944]
	cmp	r1, r4
	beq	.L3102
	mov	r1, r5
	b	.L3104
.L3105:
	ldr	ip, [r1, #4]!
	cmp	ip, r4
	beq	.L3102
.L3104:
	add	r2, r2, #1
	cmp	r2, r0
	bne	.L3105
.L3103:
	mov	r5, #832
	movw	r0, #28080
	mla	r5, r5, lr, r8
	mov	r7, #0
	mov	r10, #1
	str	r4, [r6, #3984]
	strb	r10, [r6, #3328]
	mov	ip, #101
	add	r1, r5, #27392
	mov	r2, #640
	add	r1, r1, #16
	str	r3, [fp, #-48]
	str	r7, [r5, r0]
	add	r5, r5, #27392
	add	r0, r6, #3344
	str	ip, [r6, #4028]
	bl	memcpy
	str	r7, [r6, #3496]
	strb	r7, [r5, #3]
	str	r7, [r4, #676]
	ldr	r2, [r6, #3984]
	ldr	r3, [fp, #-48]
	strb	r7, [r2, #2]
	ldr	r2, [r6, #3984]
	strb	r10, [r2, #4]
	ldr	r2, [r6, #3984]
	str	r7, [r2, #824]
	ldrb	r10, [r6, #3328]	@ zero_extendqisi2
	cmp	r10, #1
	bne	.L3107
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-60]
	ldr	r0, [r9, #2680]
	clz	r1, r3
	mov	r1, r1, lsr #5
	bl	FSP_NewLogicFs
	mov	r5, r0
	mov	r1, r0
	ldr	r0, [r9, #2680]
	bl	FSP_GetLogicFs
	mvn	r2, r5
	mov	r2, r2, lsr #31
	cmp	r0, #0
	mov	r4, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L3108
	ldr	r3, [fp, #-56]
	ldrb	r2, [r3, #3296]	@ zero_extendqisi2
	strb	r2, [r0, #480]
	ldr	r2, [r3, #3324]
	strb	r2, [r0, #481]
	ldr	r2, [r3, #3332]
	strb	r2, [r0, #482]
	ldr	r2, [r3, #3328]
	ldr	r3, [fp, #-48]
	str	r2, [r0, #484]
	ldr	r2, [r8]
	ldr	r2, [r2, #28]
	cmp	r2, #25
	beq	.L3156
.L3109:
	ldr	r7, .L3159
	mov	r2, #640
	ldr	r0, [r6, #3984]
	add	r1, r4, #40
	str	r3, [fp, #-48]
	ldr	r10, [r7, #52]
	add	r0, r0, #16
	blx	r10
	ldr	r1, [r6, #3984]
	add	r0, r8, #60672
	mov	r2, #640
	ldr	r7, [r7, #52]
	add	r0, r0, #16
	add	r1, r1, #16
	blx	r7
	ldr	r2, [r6, #3984]
	ldr	r3, [fp, #-48]
	mov	ip, r5
	str	r5, [r2, #656]
	ldrsb	r2, [r4, #4]
	ldr	r0, [r6, #3984]
	str	r2, [r6, #4052]
.L3099:
	ldrb	r1, [fp, #-52]	@ zero_extendqisi2
	strb	r1, [r6, #3331]
	ldrb	r2, [r3, #209]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
	strb	r2, [r0, #704]
	ldrb	r2, [r6, #3329]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3157
	ldr	r2, [fp, #-52]
	strb	r1, [r9, #704]
	ldr	r1, [r3, #224]
	cmp	r2, #0
	ldr	r2, [r9, #2692]
	ldreq	r0, [fp, #-52]
	movne	r0, #0
	str	r1, [r9, #712]
	ldr	r3, [r3, #236]
	str	ip, [r9, #724]
	str	r2, [r9, #720]
	str	r3, [r9, #708]
	movne	r3, #1
	moveq	r3, r0
	strb	r3, [r9, #705]
.L3142:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3102:
	add	lr, lr, #1
	add	r4, r4, #832
	cmp	lr, r7
	bne	.L3106
.L3107:
	ldr	r1, .L3159+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r8
	mov	r1, #1
	bl	ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3151:
	add	r1, r8, #12288
	ldr	r0, [r3, #216]
	str	r1, [fp, #-64]
	mov	lr, #2208
	mov	r4, r1
	ldr	r1, [r1, #1304]
	mov	ip, #4000
	add	r9, r8, #61440
	mla	r1, lr, r0, r1
	ldr	r0, [r4, #1300]
	ldr	lr, [r9, #2608]
	cmp	lr, #2
	ldr	r1, [r1, #28]
	mla	r1, ip, r1, r0
	str	r1, [fp, #-56]
	beq	.L3158
	add	r6, r8, #57344
	strb	r2, [r6, #3329]
	ldrb	r2, [r9, #704]	@ zero_extendqisi2
	cmp	r2, #2
	mov	r2, #1
	str	r2, [fp, #-52]
	bne	.L3117
	b	.L3113
.L3158:
	mov	r2, #1
	str	r2, [fp, #-52]
.L3114:
	add	r6, r8, #57344
	mov	r2, #0
	strb	r2, [r6, #3329]
	b	.L3117
.L3152:
	str	r1, [fp, #-52]
	b	.L3114
.L3156:
	ldr	r3, [fp, #-64]
	ldr	r10, [r0, #152]
	ldr	r2, [r3, #1280]
	ldr	r1, [r3, #1276]
	str	r7, [r0, #280]
	mov	r2, r2, asl #4
	str	r2, [r0, #112]
	mov	r1, r1, asl #4
	str	r7, [r0, #284]
	mul	r10, r10, r2
	ldr	r2, [r0, #76]
	str	r1, [r0, #108]
	str	r7, [r0, #288]
	add	r2, r10, r2
	str	r7, [r0, #292]
	str	r7, [r0, #296]
	mov	r0, r2
	str	r2, [r4, #80]
	bl	MEM_Phy2Vir
	ldr	r1, [r4, #60]
	ldr	r2, [r4, #156]
	add	r10, r10, r1
	str	r7, [r4, #556]
	str	r10, [r4, #64]
	add	r10, r10, r2
	ldr	r3, [fp, #-48]
	str	r10, [r4, #72]
	str	r0, [r4, #552]
	b	.L3109
.L3157:
	mov	r2, #0
	strb	r2, [r9, #704]
	ldr	lr, [r3, #224]
	mov	r0, r2
	ldr	r1, [r9, #2692]
	str	lr, [r9, #712]
	ldr	r3, [r3, #236]
	strb	r2, [r9, #705]
	str	ip, [r9, #724]
	str	r3, [r9, #708]
	str	r1, [r9, #720]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3153:
	cmp	r2, #0
	beq	.L3093
	b	.L3117
.L3108:
	ldr	r3, [r6, #3984]
	mov	r0, r2
	strb	r2, [r6, #3328]
	ldr	r1, .L3159+8
	strb	r2, [r3, #4]
	bl	dprint_vfmw
	mov	r1, r10
	mov	r0, r8
	bl	ClearAll
	mvn	r0, #0
	b	.L3142
.L3155:
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	cmp	r2, #2
	beq	.L3098
.L3146:
	mov	r2, #0
	strb	r2, [r6, #3329]
	b	.L3117
.L3154:
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L3146
.L3098:
	ldr	r0, [r6, #3984]
	cmp	r0, #0
	bne	.L3120
	b	.L3117
.L3095:
	strb	r0, [r6, #3329]
	b	.L3117
.L3160:
	.align	2
.L3159:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC357
	.word	.LC358
	UNWIND(.fnend)
	.size	AllocFrameStore, .-AllocFrameStore
	.align	2
	.global	H264DEC_Init
	.type	H264DEC_Init, %function
H264DEC_Init:
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
	subs	r5, r0, #0
	mov	r7, r1
	beq	.L3173
	cmp	r1, #0
	beq	.L3174
	ldr	r8, .L3178
	movw	r2, #64168
	ldr	r4, [r5, #352]
	mov	r1, #0
	ldr	r3, [r8, #48]
	blx	r3
	str	r4, [r5, #352]
	add	r0, r5, #8
	bl	ResetVoQueue
	mov	r3, #0
	str	r7, [r5]
	str	r3, [r5, #360]
	str	r3, [r5, #364]
	ldr	r3, [r7, #28]
	cmp	r3, #25
	beq	.L3175
	add	r6, r5, #12288
	mov	r1, #32
	mov	r2, #256
	mov	r3, #136
	str	r1, [r6, #1288]
	str	r2, [r6, #1292]
	str	r3, [r6, #1284]
.L3166:
	ldr	r0, [r7, #592]
	add	r4, r5, #61440
	bl	MEM_Phy2Vir
	ldr	lr, [r6, #1288]
	ldr	r3, [r5]
	mov	r2, #4000
	ldr	r1, [r6, #1292]
	mul	r2, r2, lr
	ldr	r3, [r3, #588]
	add	r3, r0, r3
	mov	r0, #2208
	add	ip, r3, r2
	str	r3, [r6, #1300]
	cmp	r3, #0
	cmpne	ip, #0
	str	ip, [r6, #1304]
	mla	r0, r0, r1, ip
	moveq	r9, #1
	movne	r9, #0
	cmp	r0, #0
	orreq	r9, r9, #1
	cmp	r9, #0
	str	r0, [r4, #2600]
	bne	.L3176
	ldr	r7, [r7, #624]
	mov	r10, r7
	adds	r7, r3, #0
	movne	r7, #1
	cmp	r10, #0
	movne	r7, #0
	cmp	ip, #0
	moveq	ip, #0
	andne	ip, r7, #1
	cmp	ip, #0
	beq	.L3168
	mov	r0, r3
	mov	r1, r9
	ldr	r3, [r8, #48]
	blx	r3
	ldr	r2, [r6, #1292]
	mov	ip, #2208
	mov	r1, r9
	ldr	r3, [r8, #48]
	ldr	r0, [r6, #1304]
	mul	r2, ip, r2
	blx	r3
	ldr	r1, [r6, #1292]
	ldr	lr, [r6, #1288]
	ldr	r0, [r4, #2600]
.L3168:
	add	ip, r5, #16384
	movw	r7, #4060
	ldr	r3, [r8, #48]
	str	r1, [ip, #1236]
	mov	r1, #0
	ldr	r2, [r6, #1284]
	str	lr, [r6, #1344]
	mov	r6, r1
	mul	r2, r7, r2
	blx	r3
	mov	r2, #40
	mov	r3, #17
	str	r6, [r4, #2624]
	str	r6, [r4, #2628]
	mov	r0, r5
	str	r6, [r4, #2632]
	str	r6, [r4, #2636]
	str	r6, [r4, #2640]
	str	r6, [r4, #2644]
	str	r6, [r4, #2648]
	str	r6, [r4, #2652]
	str	r6, [r4, #2616]
	str	r6, [r4, #1392]
	str	r6, [r4, #1396]
	str	r6, [r4, #1400]
	str	r6, [r4, #1404]
	str	r6, [r4, #1408]
	str	r6, [r4, #1372]
	str	r6, [r4, #1380]
	str	r6, [r4, #2684]
	str	r6, [r4, #1384]
	str	r6, [r4, #1388]
	str	r2, [r4, #1364]
	str	r3, [r4, #1368]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #2680]
	beq	.L3177
	mov	r1, r6
	mov	r0, r5
	bl	ClearAll
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3175:
	ldr	r3, [r7, #708]
	add	r6, r5, #12288
	str	r3, [r6, #1288]
	ldr	r3, [r7, #712]
	str	r3, [r6, #1292]
	ldr	r3, [r7, #700]
	str	r3, [r6, #1284]
	b	.L3166
.L3176:
	movw	r3, #12614
	ldr	r2, .L3178+4
	ldr	r1, .L3178+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3177:
	mov	r0, r6
	ldr	r1, .L3178+12
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3174:
	mov	r0, r1
	movw	r3, #12580
	ldr	r2, .L3178+16
	ldr	r1, .L3178+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3173:
	movw	r3, #12579
	ldr	r2, .L3178+16
	ldr	r1, .L3178+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3179:
	.align	2
.L3178:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+272
	.word	.LC359
	.word	.LC360
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264DEC_Init, .-H264DEC_Init
	.align	2
	.global	ClearDPB
	.type	ClearDPB, %function
ClearDPB:
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
	bl	FlushDPB
	subs	r3, r0, #0
	beq	.L3181
	movw	r2, #2449
	ldr	r1, .L3185
	mov	r0, #0
	bl	dprint_vfmw
.L3181:
	mov	r0, r4
	add	r4, r4, #61440
	bl	InitDPB
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #1380]
	str	r3, [r4, #2684]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3186:
	.align	2
.L3185:
	.word	.LC361
	UNWIND(.fnend)
	.size	ClearDPB, .-ClearDPB
	.align	2
	.global	InsertFrmInDPB
	.type	InsertFrmInDPB, %function
InsertFrmInDPB:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r1, #15
	mov	r5, r1
	str	r0, [fp, #-48]
	mov	r4, r2
	bhi	.L3283
	ldrb	r8, [r2, #3]	@ zero_extendqisi2
	cmp	r8, #1
	beq	.L3191
	bcc	.L3192
	cmp	r8, #2
	bne	.L3284
	ldr	r3, [r2, #656]
	mov	r2, #3
	strb	r2, [r3, #704]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r3, r1, asl #2
	beq	.L3212
	ldr	r2, [fp, #-48]
	add	r7, r2, r3
	add	r2, r7, #24576
	str	r2, [fp, #-60]
	ldr	r2, [r2, #1944]
	cmp	r2, #0
	beq	.L3212
	ldr	r0, [fp, #-60]
	strb	r8, [r2, #784]
	ldr	r2, [r4, #656]
	ldr	r3, [r0, #1944]
	str	r2, [r3, #820]
	ldr	r3, [r0, #1944]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #785]
	ldr	r3, [r0, #1944]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #786]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #688]
	str	r2, [r3, #796]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #692]
	str	r2, [r3, #804]
	ldr	r2, [r4, #656]
	ldr	r3, [r0, #1944]
	ldr	r2, [r2, #816]
	str	r2, [r3, #816]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #700]
	str	r2, [r3, #800]
	ldr	r3, [r0, #1944]
	ldr	r1, [r3, #760]
	ldr	r2, [r3, #800]
	add	r2, r2, r1
	str	r2, [r3, #720]
	str	r2, [r3, #688]
	add	r1, r4, #16
	ldr	r2, [r0, #1944]
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r3, [fp, #-60]
	ldr	r2, [r3, #1944]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #1]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [fp, #-60]
	ldr	r3, [r3, #1944]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	orreq	r2, r2, #2
	strb	r2, [r3, #3]
	mov	r2, #640
	ldr	r3, [fp, #-60]
	ldr	ip, [r3, #1944]
	add	r8, ip, #608
	add	lr, ip, #624
	ldr	r3, [ip, #16]
	add	r0, ip, #16
	ldrd	r6, [r8, #-8]
	ldrd	r8, [r8]
	str	r3, [fp, #-52]
	ldr	r10, [ip, #20]
	strd	r8, [fp, #-68]
	ldrd	r8, [lr, #-8]
	strd	r8, [fp, #-76]
	ldr	r9, [ip, #24]
	ldr	r8, [ip, #28]
	bl	memcpy
	mvn	r1, #0
	cmp	r7, r1
	mvn	r0, #0
	cmpeq	r6, r0
	ldr	r3, [fp, #-52]
	ldrne	r2, [fp, #-60]
	ldrne	r2, [r2, #1944]
	addne	r2, r2, #608
	strned	r6, [r2, #-8]
.L3221:
	add	r1, r4, #608
	ldr	r2, [fp, #-60]
	ldrd	r6, [fp, #-68]
	add	ip, r4, #624
	ldrd	r0, [r1]
	ldr	r2, [r2, #1944]
	cmp	r1, r7
	cmpeq	r0, r6
	add	r2, r2, #608
	movhi	r0, r6
	movhi	r1, r7
	strd	r0, [r2]
	ldr	r2, [fp, #-60]
	ldrd	r0, [ip, #-8]
	ldrd	r6, [fp, #-76]
	ldr	r2, [r2, #1944]
	cmp	r1, r7
	cmpeq	r0, r6
	add	r2, r2, #624
	movhi	r0, r6
	movhi	r1, r7
	strd	r0, [r2, #-8]
	ldr	r0, [fp, #-60]
	ldr	r2, [r4, #16]
	ldr	r1, [r0, #1944]
	cmp	r2, r3
	movcs	r2, r3
	str	r2, [r1, #16]
	ldr	r3, [r4, #20]
	ldr	r2, [r0, #1944]
	cmp	r3, r10
	movcs	r3, r10
	str	r3, [r2, #20]
	ldr	r3, [r4, #24]
	ldr	r2, [r0, #1944]
	cmp	r3, r9
	movcs	r3, r9
	str	r3, [r2, #24]
	ldr	r3, [r4, #28]
	ldr	r2, [r0, #1944]
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r2, #28]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3224
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3224
.L3225:
	ldr	r0, [fp, #-60]
	ldr	r2, [r0, #1944]
	ldr	r3, [r2, #804]
	ldr	r1, [r2, #764]
	cmp	r3, r1
	movcc	r3, r1
	str	r3, [r2, #684]
	ldr	r2, [r4, #676]
	mov	r4, r0
	ldr	r3, [r0, #1944]
	str	r2, [r3, #672]
	ldr	r0, [r0, #1944]
	bl	CombineFldsToFrm
	ldr	r2, [r4, #1944]
	ldr	r1, [fp, #-48]
	ldr	r3, [r2, #696]
	ldr	r2, [r2, #796]
	add	r3, r3, #6720
	add	r3, r3, #10
	add	r3, r1, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3211
.L3192:
	ldr	r3, [fp, #-48]
	ldr	r2, [r2, #656]
	add	r7, r3, r1, lsl #2
	mov	r3, #3
	add	r7, r7, #24576
	str	r2, [r7, #1944]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r2]
	ldr	r2, [r7, #1944]
	strb	r3, [r2, #1]
	ldr	r1, [r4, #656]
	ldr	r2, [r7, #1944]
	ldrb	r1, [r1, #4]	@ zero_extendqisi2
	strb	r1, [r2, #4]
	ldr	r1, [r4, #656]
	ldr	r2, [r7, #1944]
	ldr	r1, [r1, #676]
	str	r1, [r2, #676]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	ldr	r2, [r7, #1944]
	cmp	r1, #0
	beq	.L3285
.L3194:
	strb	r3, [r2, #2]
	add	r1, r4, #16
	ldr	r3, [r7, #1944]
	mov	r2, #640
	ldr	r0, [r4, #724]
	mov	r9, #0
	str	r0, [r3, #692]
	ldr	r0, [r7, #1944]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r7, #1944]
	ldr	r2, [r4, #700]
	mov	lr, #1
	mov	ip, #2
	str	r2, [r3, #720]
	str	r2, [r3, #688]
	mov	r2, r9
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #656]
	str	r1, [r3, #820]
	str	r1, [r3, #780]
	str	r1, [r3, #740]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #668]
	str	r1, [r3, #668]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #664]
	str	r1, [r3, #660]
	ldr	r3, [r7, #1944]
	strb	r9, [r3, #704]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	strb	r1, [r3, #705]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	strb	r1, [r3, #706]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #692]
	str	r1, [r3, #724]
	str	r1, [r3, #684]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	str	r1, [r3, #680]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #676]
	str	r1, [r3, #672]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #680]
	ldr	r0, [fp, #-48]
	str	r1, [r3, #716]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #684]
	str	r1, [r3, #756]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #688]
	str	r1, [r3, #796]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, lr
	ldr	r3, [r7, #1944]
	moveq	r8, #3
	strb	r8, [r3, #3]
	ldr	r1, [r4, #656]
	ldr	r3, [r7, #1944]
	ldr	r1, [r1, #736]
	str	r1, [r3, #736]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r3, #705]	@ zero_extendqisi2
	ldrb	r7, [r3, #706]	@ zero_extendqisi2
	strb	lr, [r3, #744]
	strb	ip, [r3, #784]
	ldr	lr, [r3, #720]
	ldr	ip, [r3, #724]
	strb	r1, [r3, #745]
	strb	r1, [r3, #785]
	ldr	r1, [r3, #740]
	strb	r7, [r3, #746]
	strb	r7, [r3, #786]
	str	lr, [r3, #760]
	str	lr, [r3, #800]
	str	ip, [r3, #764]
	str	r1, [r3, #780]
	str	ip, [r3, #804]
	str	r1, [r3, #820]
	ldr	r1, [r4, #656]
	bl	GetAPC
	cmp	r0, #0
	movne	r3, r0
	movwne	r2, #2652
	movne	r0, r9
	bne	.L3281
.L3211:
	ldr	r1, [fp, #-48]
	add	r5, r5, #6592
	add	r5, r5, #38
	mov	r2, #1
	add	r3, r1, #61440
	ldr	r0, [r3, #2680]
	ldr	r3, [r1, r5, asl #2]
	ldr	r1, [r3, #656]
	bl	FSP_SetRef
	mov	r0, #0
.L3189:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3284:
	mov	r2, r8
	ldr	r1, .L3286
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r0, [fp, #-48]
	mov	r1, #1
	bl	ClearAll
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3191:
	ldr	r3, [r2, #656]
	mov	r2, #3
	strb	r2, [r3, #704]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r3, r1, asl #2
	beq	.L3197
	ldr	r2, [fp, #-48]
	add	r7, r2, r3
	add	r7, r7, #24576
	ldr	r2, [r7, #1944]
	cmp	r2, #0
	beq	.L3197
	strb	r8, [r2, #744]
	ldr	r3, [r7, #1944]
	ldr	r2, [r4, #692]
	str	r2, [r3, #764]
	ldr	r3, [r7, #1944]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #745]
	ldr	r3, [r7, #1944]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #746]
	ldr	r3, [r7, #1944]
	ldr	r2, [r4, #684]
	str	r2, [r3, #756]
	ldr	r3, [r7, #1944]
	ldr	r2, [r4, #692]
	str	r2, [r3, #764]
	ldr	r2, [r4, #656]
	ldr	r3, [r7, #1944]
	ldr	r2, [r2, #776]
	str	r2, [r3, #776]
	ldr	r3, [r7, #1944]
	ldr	r2, [r4, #700]
	str	r2, [r3, #760]
	ldr	r3, [r7, #1944]
	ldr	r1, [r3, #760]
	ldr	r2, [r3, #800]
	add	r2, r2, r1
	str	r2, [r3, #720]
	str	r2, [r3, #688]
	add	r1, r4, #16
	ldr	r2, [r7, #1944]
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r2, [r7, #1944]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #1]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r7, #1944]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	orreq	r2, r2, #1
	strb	r2, [r3, #3]
	mov	r2, #640
	ldr	ip, [r7, #1944]
	add	r8, ip, #608
	add	lr, ip, #624
	ldr	r3, [ip, #16]
	add	r0, ip, #16
	ldrd	r8, [r8]
	ldr	r6, [ip, #600]
	str	r3, [fp, #-84]
	ldr	r3, [ip, #604]
	strd	r8, [fp, #-60]
	ldrd	r8, [lr, #-8]
	str	r3, [fp, #-80]
	ldr	r3, [ip, #24]
	ldr	r10, [ip, #20]
	strd	r8, [fp, #-68]
	str	r3, [fp, #-76]
	ldr	r3, [ip, #28]
	str	r3, [fp, #-52]
	bl	memcpy
	add	r2, r4, #608
	mov	lr, r6
	ldr	r6, [fp, #-80]
	ldmdb	r2, {r0, ip}
	and	r1, lr, r6
	ldrd	r8, [fp, #-60]
	adds	r1, r1, #1
	and	r0, r0, ip
	add	ip, r4, #624
	ldr	r3, [fp, #-84]
	movne	r1, #1
	cmn	r0, #1
	movne	r1, #0
	cmp	r1, #0
	ldrne	r1, [r7, #1944]
	strne	lr, [r1, #600]
	strne	r6, [r1, #604]
	ldrd	r0, [r2]
	ldr	r2, [r7, #1944]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r2, r2, #608
	movhi	r0, r8
	movhi	r1, r9
	ldrd	r8, [fp, #-68]
	strd	r0, [r2]
	ldrd	r0, [ip, #-8]
	ldr	r2, [r7, #1944]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r2, r2, #624
	movhi	r1, r9
	movhi	r0, r8
	strd	r0, [r2, #-8]
	ldr	r2, [r4, #16]
	ldr	r1, [r7, #1944]
	cmp	r2, r3
	movcs	r2, r3
	str	r2, [r1, #16]
	ldr	r3, [r4, #20]
	ldr	r2, [r7, #1944]
	cmp	r3, r10
	ldr	r1, [fp, #-76]
	movcs	r3, r10
	str	r3, [r2, #20]
	ldr	r3, [r4, #24]
	ldr	r2, [r7, #1944]
	cmp	r3, r1
	movcs	r3, r1
	ldr	r1, [fp, #-52]
	str	r3, [r2, #24]
	ldr	r3, [r4, #28]
	ldr	r2, [r7, #1944]
	cmp	r3, r1
	movcs	r3, r1
	str	r3, [r2, #28]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3208
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3208
.L3209:
	ldr	r2, [r7, #1944]
	ldr	r3, [r2, #804]
	ldr	r1, [r2, #764]
	cmp	r3, r1
	movcc	r3, r1
	str	r3, [r2, #684]
	ldr	r2, [r4, #676]
	ldr	r3, [r7, #1944]
	str	r2, [r3, #672]
	ldr	r0, [r7, #1944]
	bl	CombineFldsToFrm
	ldr	r2, [r7, #1944]
	ldr	r1, [fp, #-48]
	ldr	r3, [r2, #696]
	ldr	r2, [r2, #756]
	add	r3, r3, #6656
	add	r3, r3, #58
	add	r3, r1, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3211
.L3197:
	ldr	r2, [fp, #-48]
	add	r7, r2, r3
	ldr	r3, [r4, #656]
	add	r7, r7, #24576
	mov	r2, #1
	str	r3, [r7, #1944]
	strb	r2, [r3, #744]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #656]
	str	r1, [r3, #780]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	strb	r1, [r3, #745]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	strb	r1, [r3, #746]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #684]
	str	r1, [r3, #756]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #692]
	str	r1, [r3, #764]
	ldr	r1, [r4, #656]
	ldr	r3, [r7, #1944]
	ldr	r1, [r1, #776]
	str	r1, [r3, #776]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #700]
	str	r1, [r3, #760]
	ldr	r3, [r7, #1944]
	ldr	r1, [r3, #760]
	str	r1, [r3, #720]
	str	r1, [r3, #688]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r7, #1944]
	strb	r2, [r3, #1]
	ldr	r2, [r4, #656]
	ldr	r3, [r7, #1944]
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	strb	r2, [r3, #4]
	ldr	r2, [r4, #656]
	ldr	r3, [r7, #1944]
	ldr	r2, [r2, #676]
	str	r2, [r3, #676]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3199
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3199
.L3200:
	ldr	r3, [r7, #1944]
	mov	r8, #0
	mov	r2, #640
	add	r1, r4, #16
	str	r8, [r3, #680]
	ldr	r0, [r7, #1944]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #724]
	mov	r2, #1
	ldr	r0, [fp, #-48]
	str	r1, [r3, #692]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #664]
	str	r1, [r3, #660]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #676]
	str	r1, [r3, #672]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #692]
	str	r1, [r3, #684]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	ldr	r1, [r7, #1944]
	rsb	r3, r2, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r1, #3]
	ldr	r1, [r4, #656]
	bl	GetAPC
	cmp	r0, #0
	beq	.L3211
	mov	r3, r0
	movw	r2, #2707
	mov	r0, r8
.L3281:
	ldr	r1, .L3286+4
	bl	dprint_vfmw
	ldr	r0, [fp, #-48]
	bl	ClearDPB
	mvn	r0, #0
	b	.L3189
.L3212:
	ldr	r2, [fp, #-48]
	add	r7, r2, r3
	ldr	r3, [r4, #656]
	add	r7, r7, #24576
	mov	r2, #2
	str	r3, [r7, #1944]
	strb	r2, [r3, #784]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #656]
	str	r1, [r3, #820]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	strb	r1, [r3, #785]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	strb	r1, [r3, #786]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #688]
	str	r1, [r3, #796]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #692]
	str	r1, [r3, #804]
	ldr	r1, [r4, #656]
	ldr	r3, [r7, #1944]
	ldr	r1, [r1, #816]
	str	r1, [r3, #816]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #700]
	str	r1, [r3, #800]
	ldr	r3, [r7, #1944]
	ldr	r1, [r3, #760]
	str	r1, [r3, #720]
	str	r1, [r3, #688]
	ldr	r3, [r7, #1944]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r7, #1944]
	strb	r2, [r3, #1]
	ldr	r2, [r4, #656]
	ldr	r3, [r7, #1944]
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	strb	r2, [r3, #4]
	ldr	r2, [r4, #656]
	ldr	r3, [r7, #1944]
	ldr	r2, [r2, #676]
	str	r2, [r3, #676]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3214
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3214
.L3215:
	ldr	r3, [r7, #1944]
	mov	r9, #0
	mov	r2, #640
	add	r1, r4, #16
	str	r9, [r3, #680]
	ldr	r0, [r7, #1944]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #724]
	mov	r2, #2
	ldr	r0, [fp, #-48]
	str	r1, [r3, #692]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #664]
	str	r1, [r3, #660]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #676]
	str	r1, [r3, #672]
	ldr	r3, [r7, #1944]
	ldr	r1, [r4, #692]
	str	r1, [r3, #804]
	str	r1, [r3, #684]
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldr	r3, [r7, #1944]
	cmp	r1, #1
	moveq	r8, r2
	movne	r8, r9
	strb	r8, [r3, #3]
	ldr	r1, [r4, #656]
	bl	GetAPC
	cmp	r0, #0
	movne	r3, r0
	movwne	r2, #2830
	movne	r0, r9
	beq	.L3211
	b	.L3281
.L3285:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #3
	b	.L3194
.L3199:
	ldr	r3, [r7, #1944]
	mov	r2, #1
	strb	r2, [r3, #2]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, r2
	ldreq	r3, [r7, #1944]
	ldreq	r2, [r4, #668]
	streq	r2, [r3, #668]
	b	.L3200
.L3214:
	ldr	r3, [r7, #1944]
	mov	r2, #2
	strb	r2, [r3, #2]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r7, #1944]
	ldreq	r2, [r4, #668]
	streq	r2, [r3, #668]
	b	.L3215
.L3224:
	ldr	r1, [fp, #-60]
	ldr	r2, [r1, #1944]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r3, r1
	ldreq	r2, [r4, #668]
	ldreq	r3, [r3, #1944]
	streq	r2, [r3, #668]
	b	.L3225
.L3208:
	ldr	r2, [r7, #1944]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r7, #1944]
	ldreq	r2, [r4, #668]
	streq	r2, [r3, #668]
	b	.L3209
.L3283:
	mov	r3, r1
	movw	r2, #2613
	ldr	r1, .L3286+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3189
.L3287:
	.align	2
.L3286:
	.word	.LC364
	.word	.LC363
	.word	.LC362
	UNWIND(.fnend)
	.size	InsertFrmInDPB, .-InsertFrmInDPB
	.align	2
	.global	DecVDM
	.type	DecVDM, %function
DecVDM:
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
	subs	r7, r0, #0
	beq	.L3383
	add	r6, r7, #57344
	add	r4, r7, #61440
	ldrb	r3, [r6, #3331]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3384
.L3291:
	ldr	r3, [r4, #2704]
	ldr	r2, [r4, #2708]
	add	r3, r3, #1
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #2704]
	ldr	r1, [r7]
	rsb	r3, r2, r3
	str	r3, [r1, #584]
.L3292:
	ldr	r5, [r4, #2668]
	ldr	r3, [r4, #2608]
	ubfx	r5, r5, #16, #3
	cmp	r3, r5
	beq	.L3293
	subs	r2, r5, #2
	sub	r3, r3, #2
	movne	r2, #1
	cmp	r3, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L3293
	cmp	r5, #4
	cmpne	r5, #1
	bls	.L3385
.L3293:
	cmp	r5, #2
	str	r5, [r4, #2608]
	beq	.L3295
	cmp	r5, #3
	beq	.L3296
	cmp	r5, #1
	beq	.L3386
	ldr	r3, [r4, #2604]
	cmp	r3, #0
	beq	.L3299
	cmp	r5, #4
	ldr	r3, [r6, #4020]
	beq	.L3387
.L3306:
	cmp	r3, #2
	beq	.L3323
.L3310:
	cmp	r3, #1
	streq	r3, [r4, #1384]
.L3312:
	ldr	r2, [r4, #2644]
	mov	r0, #2
	ldrb	r3, [r6, #3331]	@ zero_extendqisi2
	sub	r2, r2, #1
	ldr	r1, .L3392
	bl	dprint_vfmw
	ldr	r0, [r6, #4044]
	ldr	r1, [r4, #2644]
	mov	r3, #1
	ldr	r2, [r4, #2604]
	str	r0, [r4, #2156]
	cmp	r1, #0
	strb	r3, [r4, #1418]
	ldr	r3, [r6, #4048]
	str	r2, [r4, #2356]
	str	r3, [r4, #2152]
	beq	.L3314
	ldr	r1, [r6, #4020]
	cmp	r1, #0
	beq	.L3388
	add	r3, r7, #24576
	ldr	r3, [r3, #2140]
	cmp	r3, #0
	bne	.L3316
	ldr	r2, [r7]
	ldr	r1, [r2, #24]
	cmp	r1, #2
	bne	.L3389
.L3319:
	add	r3, r7, #62720
	add	r3, r3, #136
	str	r3, [r7, #360]
	ldr	r1, [r2, #912]
	cmp	r1, #1
	beq	.L3390
	cmp	r1, #2
	bne	.L3322
	ldr	r1, [r2, #916]
	cmp	r3, #0
	cmpne	r1, #0
	ble	.L3322
	ldr	r3, [r6, #4020]
	cmp	r3, #2
	bne	.L3322
	mov	r2, #0
	str	r2, [r7, #360]
	ldr	r3, [r6, #3984]
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetDisplay
	ldr	r2, [r7]
	mov	r0, r7
	ldr	r3, [r2, #916]
	sub	r3, r3, #1
	str	r3, [r2, #916]
	bl	H264_ClearCurrPic
	mvn	r0, #0
	b	.L3375
.L3384:
	ldrb	r3, [r6, #3329]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3292
	b	.L3291
.L3385:
	mov	r2, r5
	ldr	r1, .L3392+4
	mov	r0, #2
	bl	dprint_vfmw
	str	r5, [r4, #2608]
.L3296:
	mov	r0, r7
	bl	H264_ClearCurrPic
	mov	r0, r7
	bl	ClearDPB
	mvn	r0, #0
.L3375:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3314:
	ldr	r2, [r7]
.L3322:
	ldr	r3, [r2, #600]
	mov	r0, #0
	strb	r3, [r4, #1420]
	ldr	r3, [r2, #608]
	str	r3, [r4, #1424]
	ldr	r3, [r2, #612]
	str	r3, [r4, #1428]
	ldr	r3, [r2, #604]
	strb	r3, [r4, #1421]
	ldr	r3, [r2, #652]
	strb	r3, [r4, #1432]
	ldr	ip, [r6, #4060]
	ldr	r1, [r6, #3984]
	ldr	r3, [r6, #4056]
	str	ip, [r6, #4056]
	ldr	r2, [r1, #256]
	rsb	r3, ip, r3
	add	r2, r2, r3
	str	r2, [r1, #256]
	ldr	r2, [r6, #3584]
	add	r3, r3, r2
	str	r3, [r6, #3584]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3295:
	ldr	r5, [r6, #4020]
	cmp	r5, #0
	bne	.L3302
	ldr	r3, [r4, #2604]
	cmp	r3, #0
	beq	.L3299
	ldr	r3, [r4, #2600]
	ldr	r3, [r3, #48]
	cmp	r3, #0
	beq	.L3312
	mov	r3, #1
	mov	r0, r7
	strb	r3, [r6, #3335]
	bl	H264_ClearCurrPic
	mov	r0, r5
	ldr	r1, .L3392+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3375
.L3386:
	ldr	r3, [r6, #4020]
	cmp	r3, #2
	beq	.L3391
	ldr	r2, [r4, #2604]
	cmp	r2, #0
	bne	.L3310
.L3299:
	mov	r0, r7
	bl	H264_ClearCurrPic
	ldr	r3, .L3392+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3379
	mov	r3, #0
	ldr	r0, [r4, #2680]
	mov	r2, r3
	mov	r1, #127
	blx	r5
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3388:
	ldr	r3, .L3392+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3316
	ldr	r2, [r4, #2360]
	cmp	r2, #0
	beq	.L3317
.L3318:
	ldr	r3, [r2, #8]
	ldr	r0, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3318
.L3317:
	sub	r2, fp, #28
	mov	r3, #4
	ldr	r0, [r4, #2680]
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	r5
	ldr	r2, [r7]
	b	.L3319
.L3391:
	ldr	r3, [r6, #4000]
	cmp	r3, #0
	beq	.L3302
	ldr	r3, [r4, #2604]
	cmp	r3, #0
	beq	.L3299
.L3323:
	ldr	r3, [r4, #1384]
	cmp	r3, #2
	bne	.L3312
	ldr	r3, [r7]
	ldr	r5, [r3, #24]
	cmp	r5, #0
	bne	.L3312
	ldr	r3, .L3392+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3312
	ldr	r3, [r6, #4000]
	mov	r0, #1
	ldr	r2, [r6, #4004]
	ldr	r1, .L3392+20
	bl	dprint_vfmw
	mov	r0, r7
	bl	H264_ClearCurrPic
	ldr	r3, .L3392+12
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L3313
	mov	r3, r5
	mov	r2, r5
	mov	r1, #127
	ldr	r0, [r4, #2680]
	blx	r7
.L3313:
	ldr	r3, [r6, #3984]
	mov	r2, #0
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L3375
.L3390:
	cmp	r3, #0
	beq	.L3322
	ldr	r3, [r6, #4020]
	cmp	r3, #2
	bne	.L3322
	mov	r2, #0
	str	r2, [r7, #360]
	ldr	r3, [r6, #3984]
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetDisplay
.L3378:
	mov	r0, r7
	bl	H264_ClearCurrPic
.L3379:
	mvn	r0, #0
	b	.L3375
.L3387:
	cmp	r3, #0
	bne	.L3306
	ldr	r3, [r4, #1384]
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r4, #1384]
	movne	r3, #1
	strne	r3, [r4, #1384]
	b	.L3312
.L3316:
	ldr	r2, [r7]
	b	.L3319
.L3389:
	ldr	r2, .L3392+12
	ldr	r5, [r2]
	cmp	r5, #0
	beq	.L3378
	ldr	r0, [r4, #2680]
	mov	r2, r3
	mov	r1, #127
	blx	r5
	b	.L3378
.L3302:
	mov	r3, #1
	mov	r0, r7
	strb	r3, [r6, #3335]
	bl	H264_ClearCurrPic
	mvn	r0, #0
	b	.L3375
.L3383:
	movw	r3, #7489
	ldr	r2, .L3392+24
	ldr	r1, .L3392+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3375
.L3393:
	.align	2
.L3392:
	.word	.LC368
	.word	.LC365
	.word	.LC366
	.word	g_event_report
	.word	g_allow_B_before_P
	.word	.LC367
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	DecVDM, .-DecVDM
	.align	2
	.global	H264_FlushDecoder
	.type	H264_FlushDecoder, %function
H264_FlushDecoder:
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
	subs	r3, r0, #0
	beq	.L3397
	add	r2, r3, #20480
	mov	r1, #0
	mov	r4, #1
	str	r1, [r2, #256]
	strb	r4, [r2, #213]
	str	r4, [r3, #364]
	bl	DecVDM
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r4
	ldr	r1, .L3398
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L3397:
	movw	r3, #11768
	ldr	r2, .L3398+4
	ldr	r1, .L3398+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L3399:
	.align	2
.L3398:
	.word	.LC369
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264_FlushDecoder, .-H264_FlushDecoder
	.align	2
	.global	H264_VES_Splitter
	.type	H264_VES_Splitter, %function
H264_VES_Splitter:
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
	add	r4, r0, #13504
	add	r4, r4, #24
	add	r8, r0, #57344
	mov	r7, r1
	mov	r6, r0
	mov	r1, #24
	mov	r0, r4
	mov	r9, r3
	mov	r5, #0
	mov	r10, r2
	str	r5, [fp, #-48]
	bl	BsSkip
	ldr	r3, [r8, #3776]
	cmp	r7, r5
	str	r3, [fp, #-48]
	beq	.L3402
	cmp	r7, #1
	bne	.L3506
	cmp	r10, #1
	mov	r1, #16
	mov	r0, r4
	beq	.L3507
	bl	BsGet
	mov	r1, #8
	mov	r7, r0
	mov	r0, r4
	bl	BsGet
	movw	r3, #31745
	cmp	r7, r3
	beq	.L3424
	mov	r1, #24
	mov	r0, r4
	bl	BsBack
	mov	r0, r4
	mov	r1, #24
	bl	BsBack
	movw	r3, #32257
	cmp	r7, r3
	beq	.L3508
.L3422:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3506:
	mov	r2, r7
	ldr	r1, .L3516
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
.L3487:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3402:
	cmp	r10, #1
	beq	.L3509
	mov	r0, r4
	mov	r1, #24
	bl	BsBack
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3424:
	and	r0, r0, #31
	cmp	r0, #25
	bne	.L3422
	ldr	r4, .L3516+4
	ldr	r7, [r4]
	cmp	r7, #0
	beq	.L3426
	add	r0, r6, #61440
	mov	r3, r5
	mov	r2, r5
	mov	r1, #112
	ldr	r0, [r0, #2680]
	blx	r7
.L3426:
	mov	r0, r6
	bl	DecVDM
	subs	r7, r0, #0
	beq	.L3427
.L3499:
	ldr	r4, [r4]
	cmp	r4, #0
	beq	.L3493
	add	r6, r6, #61440
	mov	r3, #0
	mov	r2, r3
	mov	r1, #113
	ldr	r0, [r6, #2680]
	blx	r4
	mvn	r0, #0
	b	.L3487
.L3509:
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	movw	r9, #31745
	mov	r5, r0
	mov	r0, r4
	bl	BsGet
	cmp	r5, r9
	beq	.L3405
	mov	r1, #24
	mov	r0, r4
	bl	BsBack
	bic	r5, r5, #512
	mov	r0, r4
	mov	r1, #24
	bl	BsBack
	cmp	r5, r9
	bne	.L3422
.L3423:
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L3493
	add	r3, r6, #61440
	ldr	r0, [r3, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r6, #368]
	b	.L3487
.L3427:
	ldr	ip, [r6, #368]
	add	r5, r6, #61440
	sub	r2, fp, #48
	ldr	r1, [r8, #3768]
	ldr	r0, [r5, #2680]
	ldr	r3, [ip, #12]
	ldr	ip, [ip, #40]
	add	r3, r3, ip
	sub	r3, r3, #1
	bl	MetadataMapToSec
	cmp	r0, #0
	bne	.L3510
	ldr	r4, .L3516+8
	mov	r2, #5
	ldr	r1, .L3516+12
	ldr	r0, [fp, #-48]
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r6, #368]
	ldr	r0, [fp, #-48]
	ldr	r7, [r4, #52]
	ldr	r2, [r3, #12]
	add	r0, r0, #5
	sub	r2, r2, #6
	str	r2, [r8, #3764]
	ldr	r1, [r3, #8]
	add	r1, r1, #6
	blx	r7
	ldr	r3, [r8, #3764]
	add	r3, r3, #5
	str	r3, [r8, #3764]
	ldr	r1, [r6, #368]
	ldr	r2, [r1, #40]
	cmp	r2, #0
	bne	.L3511
.L3429:
	ldr	r0, [r5, #2680]
	ldr	r7, .L3516+16
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L3430
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r5, #2680]
	ldr	r1, [r8, #3764]
	ldr	r3, [r4, #44]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r5, #2680]
.L3430:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r4, r0, #0
	beq	.L3431
	movw	r3, #12959
.L3492:
	ldr	r2, .L3516+20
	mov	r0, #0
	ldr	r1, .L3516+24
	bl	dprint_vfmw
.L3493:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3507:
	bl	BsGet
	mov	r1, #8
	mov	r7, r0
	mov	r0, r4
	bl	BsGet
	movw	r3, #31745
	cmp	r7, r3
	beq	.L3417
	mov	r1, #32
	mov	r0, r4
	bl	BsBack
	ldr	r3, [r6, #368]
	movw	r2, #32257
	cmp	r7, r2
	mov	r2, #16
	str	r2, [r3, #64]
	beq	.L3512
	mov	r1, #8
	mov	r0, r4
	bl	BsSkip
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	and	r0, r0, #31
	cmp	r0, #11
	bne	.L3423
	mov	r0, r6
	bl	H264_IsEosNal
	cmp	r0, #1
	bne	.L3423
	ldr	r3, [r6, #368]
	mov	r0, r4
	ldr	r2, [r3, #12]
	ldr	r1, [r3, #8]
	bl	BsInit
	mov	r0, #3
	b	.L3487
.L3405:
	and	r0, r0, #31
	cmp	r0, #25
	bne	.L3423
	ldr	r4, .L3516+4
	ldr	r5, [r4]
	cmp	r5, #0
	beq	.L3408
	add	r0, r6, #61440
	mov	r3, r7
	mov	r2, r7
	mov	r1, #112
	ldr	r0, [r0, #2680]
	blx	r5
.L3408:
	mov	r0, r6
	bl	DecVDM
	subs	r7, r0, #0
	bne	.L3499
	ldr	ip, [r6, #368]
	add	r5, r6, #61440
	sub	r2, fp, #48
	ldr	r1, [r8, #3768]
	ldr	r0, [r5, #2680]
	ldr	r3, [ip, #12]
	ldr	ip, [ip, #40]
	add	r3, r3, ip
	sub	r3, r3, #1
	bl	MetadataMapToSec
	cmp	r0, #0
	bne	.L3513
	ldr	r4, .L3516+8
	mov	r2, #5
	ldr	r1, .L3516+12
	ldr	r0, [fp, #-48]
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r6, #368]
	ldr	r0, [fp, #-48]
	ldr	r7, [r4, #52]
	ldr	r2, [r3, #12]
	add	r0, r0, #5
	sub	r2, r2, #6
	str	r2, [r8, #3764]
	ldr	r1, [r3, #8]
	add	r1, r1, #6
	blx	r7
	ldr	r3, [r8, #3764]
	add	r3, r3, #5
	str	r3, [r8, #3764]
	ldr	r1, [r6, #368]
	ldr	r2, [r1, #40]
	cmp	r2, #0
	bne	.L3514
.L3412:
	ldr	r0, [r5, #2680]
	ldr	r7, .L3516+16
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L3413
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r5, #2680]
	ldr	r1, [r8, #3764]
	ldr	r3, [r4, #44]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r5, #2680]
.L3413:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r4, r0, #0
	movwne	r3, #12802
	bne	.L3492
.L3431:
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L3493
	ldr	r0, [r5, #2680]
	bl	ReleaseNAL
	str	r4, [r6, #368]
	mvn	r0, #0
	b	.L3487
.L3417:
	and	r0, r0, #31
	cmp	r0, #25
	cmpeq	r9, #2
	moveq	r9, #1
	movne	r9, #0
	bne	.L3515
	ldr	r4, .L3516+4
	ldr	r7, [r4]
	cmp	r7, #0
	beq	.L3420
	add	r0, r6, #61440
	mov	r3, r5
	mov	r2, r5
	mov	r1, #112
	ldr	r0, [r0, #2680]
	blx	r7
.L3420:
	mov	r0, r6
	bl	DecVDM
	subs	r5, r0, #0
	bne	.L3499
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L3493
	add	r3, r6, #61440
	ldr	r0, [r3, #2680]
	bl	ReleaseNAL
	str	r5, [r6, #368]
	mvn	r0, #0
	b	.L3487
.L3508:
	ldr	r1, .L3516+28
	movw	r3, #12971
	ldr	r2, .L3516+20
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L3493
	add	r3, r6, #61440
	ldr	r0, [r3, #2680]
	bl	ReleaseNAL
	str	r5, [r6, #368]
	b	.L3493
.L3512:
	add	r8, r6, #61440
	ldr	r7, .L3516+32
	ldr	r3, [r8, #2680]
	ldr	r3, [r7, r3, asl #2]
	cmp	r3, #0
	beq	.L3422
	ldr	r4, .L3516+8
	mov	r0, r5
	ldr	r3, [r4, #16]
	blx	r3
	ldr	r3, [r6, #368]
	ldr	r2, [r8, #2680]
	ldr	r6, [r4, #44]
	ldr	r1, [r3, #12]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [r3, #8]
	blx	r6
	ldr	r3, [r4, #12]
	mov	r0, r5
	blx	r3
	mov	r0, r5
	b	.L3487
.L3515:
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L3493
	add	r3, r6, #61440
	ldr	r0, [r3, #2680]
	bl	ReleaseNAL
	str	r9, [r6, #368]
	mvn	r0, #0
	b	.L3487
.L3511:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #36]
	add	r0, r0, r3
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r6, #368]
	ldr	r2, [r8, #3764]
	ldr	r3, [r3, #40]
	add	r3, r3, r2
	str	r3, [r8, #3764]
	b	.L3429
.L3514:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #36]
	add	r0, r0, r3
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r6, #368]
	ldr	r2, [r8, #3764]
	ldr	r3, [r3, #40]
	add	r3, r3, r2
	str	r3, [r8, #3764]
	b	.L3412
.L3510:
	mov	r0, r7
	movw	r3, #12929
	ldr	r2, .L3516+20
	ldr	r1, .L3516+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3487
.L3513:
	mov	r0, r7
	movw	r3, #12768
	ldr	r2, .L3516+20
	ldr	r1, .L3516+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3487
.L3517:
	.align	2
.L3516:
	.word	.LC373
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_RpuStartCode
	.word	vfmw_save_metadata_file
	.word	.LANCHOR0+288
	.word	.LC371
	.word	.LC372
	.word	vfmw_save_el_file
	.word	.LC370
	UNWIND(.fnend)
	.size	H264_VES_Splitter, .-H264_VES_Splitter
	.align	2
	.global	ReceivePacket
	.type	ReceivePacket, %function
ReceivePacket:
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
	ldr	ip, [r1, #12]
	add	r6, r0, #61440
	ldr	r3, [r1, #8]
	ldr	r2, [r1, #4]
	mov	r4, r0
	mov	r5, r1
	mov	r0, #7
	ldr	r1, .L3584
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r6, #2712]
	ldr	r3, [r4]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L3580
.L3519:
	ldr	r3, [r4, #368]
	cmp	r3, #0
	beq	.L3542
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3581
.L3522:
	ldr	r1, .L3584+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #368]
	cmp	r1, #0
	beq	.L3542
	ldr	r0, [r6, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #368]
.L3542:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3526
	ldr	r3, [r5, #4]
	cmp	r3, #0
	beq	.L3526
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3526
	cmp	r4, #0
	beq	.L3533
	ldrb	r3, [r4, #377]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3544
	mov	r2, r4
	mov	r3, #1
	b	.L3532
.L3531:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L3533
.L3532:
	ldrb	r1, [r2, #473]	@ zero_extendqisi2
	add	r2, r2, #96
	cmp	r1, #0
	bne	.L3531
	mov	r2, r3
.L3530:
	mov	r1, r3, asl #7
	cmn	r2, #1
	sub	r3, r1, r3, asl #5
	mov	r1, #1
	add	r3, r4, r3
	strb	r1, [r3, #377]
	beq	.L3533
	mov	r3, r2, asl #7
	mov	r0, #0
	sub	r3, r3, r2, asl #5
	add	r2, r3, #376
	add	r3, r4, r3
	add	r2, r4, r2
	str	r2, [r4, #368]
	ldr	r2, [r5, #4]
	str	r2, [r3, #384]
	ldr	r2, [r5, #12]
	str	r2, [r3, #388]
	ldr	r2, [r5, #8]
	str	r2, [r3, #392]
	ldr	r3, [r4, #368]
	str	r0, [r3, #24]
	ldr	r3, [r4, #368]
	ldr	r2, [r5, #16]
	str	r2, [r3, #32]
	ldrd	r2, [r5, #24]
	ldr	ip, [r4, #368]
	strd	r2, [ip, #88]
	ldr	r3, [r4, #368]
	str	r1, [r3, #68]
	ldr	r3, [r4, #368]
	strb	r0, [r3]
	ldr	r3, [r4, #368]
	ldrb	r2, [r5]	@ zero_extendqisi2
	strb	r2, [r3, #4]
	ldr	r3, [r4]
	ldrb	r3, [r3, #944]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3536
	add	r3, r4, #57344
	ldr	r1, [r5, #12]
	ldr	r2, [r3, #4056]
	ldr	r0, [r3, #4060]
	add	r1, r1, r2
	str	r1, [r3, #4056]
	ldr	r2, [r5, #12]
	add	r2, r2, r0
	str	r2, [r3, #4060]
	b	.L3536
.L3581:
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bhi	.L3522
	ldrb	r1, [r3, #4]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L3523
	b	.L3522
.L3580:
	ldr	r3, [r3, #920]
	cmp	r3, #0
	beq	.L3519
	ldr	r3, [r4, #368]
	cmp	r3, #0
	ldrneb	r2, [r5]	@ zero_extendqisi2
	beq	.L3542
.L3523:
	strb	r2, [r3, #4]
	ldr	r3, [r4]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L3582
.L3537:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3539
	ldr	r2, [r5, #4]
	cmp	r2, #0
	beq	.L3539
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3539
	ldr	r3, [r4, #368]
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bls	.L3583
.L3540:
	mov	r2, #1
	strb	r2, [r3, #4]
	ldr	r1, [r5, #16]
	ldr	r0, [r6, #2680]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3584+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3536
	mov	r3, #0
	ldr	r0, [r6, #2680]
	mov	r2, r3
	mov	r1, #113
	blx	r5
.L3536:
	ldr	r3, [r4, #368]
	ldrb	r0, [r3, #4]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3526:
	ldr	r1, .L3584+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #16]
	ldr	r0, [r6, #2680]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3584+8
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L3579
.L3578:
	mov	r3, #0
	ldr	r0, [r6, #2680]
	mov	r2, r3
	mov	r1, #113
	blx	r4
.L3579:
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3539:
	ldr	r3, [r4, #368]
	b	.L3540
.L3582:
	ldr	r3, [r3, #920]
	cmp	r3, #0
	bne	.L3536
	b	.L3537
.L3583:
	mov	ip, r1, asl #5
	mov	r0, #0
	sub	r1, ip, r1, asl #2
	add	r3, r3, r1
	str	r2, [r3, #8]
	ldr	r3, [r4, #368]
	ldr	ip, [r5, #12]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #12]
	ldr	r3, [r4, #368]
	ldr	ip, [r5, #8]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #16]
	ldr	r3, [r4, #368]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r0, [r3, #24]
	ldr	r3, [r4, #368]
	ldr	r0, [r5, #16]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r0, [r3, #32]
	ldr	r2, [r4, #368]
	ldr	r3, [r2, #68]
	add	r3, r3, #1
	str	r3, [r2, #68]
	ldr	r3, [r4]
	ldrb	r3, [r3, #944]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3541
	add	r3, r4, #57344
	ldr	r1, [r5, #12]
	ldr	r2, [r3, #4056]
	ldr	r0, [r3, #4060]
	add	r1, r1, r2
	str	r1, [r3, #4056]
	ldr	r2, [r5, #12]
	add	r2, r2, r0
	str	r2, [r3, #4060]
.L3541:
	mov	r0, r4
	bl	CombinePacket
	mov	r3, #1
	str	r3, [r6, #2712]
	b	.L3536
.L3533:
	ldr	r1, .L3584+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearAllNal
	mov	r0, r4
	bl	H264_ClearCurrPic
	mov	r0, r4
	bl	ClearDPB
	ldr	r3, .L3584+8
	ldr	r4, [r3]
	cmp	r4, #0
	bne	.L3578
	b	.L3579
.L3544:
	mov	r2, r3
	b	.L3530
.L3585:
	.align	2
.L3584:
	.word	.LC374
	.word	.LC375
	.word	g_event_report
	.word	.LC377
	.word	.LC376
	UNWIND(.fnend)
	.size	ReceivePacket, .-ReceivePacket
	.align	2
	.global	DirectOutput
	.type	DirectOutput, %function
DirectOutput:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
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
	add	r5, r0, #57344
	mov	r6, r0
	ldrb	r7, [r5, #3331]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L3588
	bcc	.L3589
	cmp	r7, #2
	beq	.L3590
	mov	r7, #0
.L3587:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3590:
	ldr	r3, [r5, #3984]
	mov	r2, #3
	add	r4, r0, #61440
	strb	r2, [r3, #704]
	ldrb	r2, [r5, #3329]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3609
	ldr	r1, [r4, #732]
	cmp	r1, #0
	beq	.L3610
	bl	OutputFrmToVO
	subs	r7, r0, #0
	bne	.L3674
.L3611:
	ldr	r3, [r5, #3984]
	str	r3, [r4, #732]
	str	r3, [r3, #820]
.L3612:
	ldr	r3, [r4, #732]
	mov	r9, #2
	ldrb	r0, [r5, #3330]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #640
	add	r1, r5, #3344
	strb	r0, [r3]
	ldr	r3, [r4, #732]
	strb	r9, [r3, #1]
	ldr	r3, [r4, #732]
	strb	r8, [r3, #4]
	ldr	r3, [r4, #732]
	str	r8, [r3, #676]
	ldr	r3, [r4, #732]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #732]
	ldr	r0, [r5, #4020]
	str	r0, [r3, #684]
	ldr	r3, [r4, #732]
	str	r8, [r3, #680]
	ldr	r0, [r4, #732]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r4, #732]
	ldr	r2, [r5, #4028]
	str	r2, [r3, #800]
	ldr	r3, [r4, #732]
	ldr	r2, [r3, #800]
	str	r2, [r3, #720]
	str	r2, [r3, #688]
	ldr	r3, [r4, #732]
	strb	r9, [r3, #784]
	ldrb	r2, [r5, #3335]	@ zero_extendqisi2
	ldr	r3, [r4, #732]
	cmp	r2, #1
	moveq	r2, r9
	movne	r2, r8
	strb	r2, [r3, #3]
	ldr	r9, [r4, #2612]
	cmp	r9, #1
	bne	.L3587
.L3669:
	ldr	r3, [r4, #732]
	mov	r2, r8
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetRef
	mov	r2, r8
	mov	r0, r6
	ldr	r1, [r4, #732]
	bl	OutputFrmToVO
	ldr	r3, [r4, #732]
	cmp	r3, r8
	mov	r7, r0
	beq	.L3622
	ldr	r3, [r5, #3984]
	mov	r2, r9
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_ClearLogicFs
	b	.L3622
.L3589:
	ldr	r3, [r5, #3984]
	add	r4, r0, #61440
	mov	r2, #0
	strb	r2, [r3, #704]
	ldr	r1, [r4, #732]
	cmp	r1, r2
	beq	.L3591
	bl	OutputFrmToVO
	cmp	r0, #0
	bne	.L3675
.L3592:
	ldr	r3, [r4, #732]
	cmp	r3, #0
	beq	.L3591
	ldr	r3, [r5, #3984]
	mov	r2, #1
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_ClearLogicFs
.L3591:
	ldr	r3, [r5, #3984]
	mov	r0, #3
	mov	r8, #0
	mov	r2, #640
	add	r1, r5, #3344
	str	r3, [r4, #732]
	str	r3, [r3, #740]
	ldr	r3, [r4, #732]
	ldr	ip, [r5, #3984]
	str	ip, [r3, #780]
	ldr	r3, [r4, #732]
	ldr	ip, [r5, #3984]
	str	ip, [r3, #820]
	ldrb	ip, [r5, #3330]	@ zero_extendqisi2
	ldr	r3, [r4, #732]
	strb	ip, [r3]
	ldr	r3, [r4, #732]
	strb	r0, [r3, #1]
	ldr	r3, [r4, #732]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #732]
	strb	r8, [r3, #4]
	ldr	r3, [r4, #732]
	str	r8, [r3, #676]
	ldr	r0, [r4, #732]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r4, #732]
	ldr	r1, [r5, #4028]
	mov	r2, r8
	str	r1, [r3, #720]
	str	r1, [r3, #688]
	ldr	r3, [r4, #732]
	strb	r8, [r3, #704]
	ldr	r3, [r4, #732]
	ldr	r1, [r5, #4020]
	str	r1, [r3, #684]
	ldr	r3, [r4, #732]
	ldrb	r1, [r5, #3337]	@ zero_extendqisi2
	str	r1, [r3, #680]
	ldrb	r1, [r5, #3335]	@ zero_extendqisi2
	ldr	r3, [r4, #732]
	cmp	r1, #1
	moveq	r7, #3
	strb	r7, [r3, #3]
	ldr	r3, [r4, #732]
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetRef
	mov	r2, r8
	mov	r0, r6
	ldr	r1, [r4, #732]
	bl	OutputFrmToVO
	ldr	r3, [r4, #732]
	cmp	r3, r8
	mov	r7, r0
	beq	.L3622
.L3667:
	ldr	r3, [r5, #3984]
	mov	r2, #1
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_ClearLogicFs
.L3622:
	mov	r3, #0
	mov	r0, r7
	str	r3, [r4, #732]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3588:
	ldr	r3, [r5, #3984]
	mov	r2, #3
	add	r4, r0, #61440
	strb	r2, [r3, #704]
	ldrb	r2, [r5, #3329]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3596
	ldr	r1, [r4, #732]
	cmp	r1, #0
	beq	.L3597
	bl	OutputFrmToVO
	subs	r7, r0, #0
	bne	.L3676
.L3598:
	ldr	r3, [r5, #3984]
	str	r3, [r4, #732]
	str	r3, [r3, #780]
.L3599:
	ldr	r3, [r4, #732]
	mov	r9, #1
	ldrb	r0, [r5, #3330]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #640
	add	r1, r5, #3344
	strb	r0, [r3]
	ldr	r3, [r4, #732]
	strb	r9, [r3, #1]
	ldr	r3, [r4, #732]
	strb	r8, [r3, #4]
	ldr	r3, [r4, #732]
	str	r8, [r3, #676]
	ldr	r3, [r4, #732]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #732]
	ldr	r0, [r5, #4020]
	str	r0, [r3, #684]
	ldr	r3, [r4, #732]
	str	r8, [r3, #680]
	ldr	r0, [r4, #732]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r4, #732]
	ldr	r2, [r5, #4028]
	str	r2, [r3, #760]
	ldr	r3, [r4, #732]
	ldr	r2, [r3, #760]
	str	r2, [r3, #720]
	str	r2, [r3, #688]
	ldr	r3, [r4, #732]
	strb	r9, [r3, #744]
	ldrb	r3, [r5, #3335]	@ zero_extendqisi2
	ldr	r2, [r4, #732]
	rsb	r3, r9, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r2, #3]
	ldr	r9, [r4, #2612]
	cmp	r9, #1
	beq	.L3669
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3609:
	ldr	r3, [r4, #732]
	mov	r2, #640
	add	r1, r5, #3344
	cmp	r3, #0
	ldreq	r3, [r5, #3984]
	streq	r3, [r4, #732]
	streq	r3, [r3, #820]
	ldreq	r3, [r4, #732]
	add	ip, r3, #608
	add	lr, r3, #624
	add	r0, r3, #16
	ldr	r10, [r3, #16]
	ldrd	r8, [ip, #-8]
	ldr	r7, [r3, #28]
	strd	r8, [fp, #-68]
	ldrd	r8, [ip]
	strd	r8, [fp, #-52]
	ldrd	r8, [lr, #-8]
	strd	r8, [fp, #-60]
	ldr	r9, [r3, #20]
	ldr	r8, [r3, #24]
	bl	memcpy
	ldrd	r0, [fp, #-68]
	mvn	r3, #0
	mvn	r2, #0
	cmp	r1, r3
	cmpeq	r0, r2
	ldrne	r3, [r4, #732]
	addne	r3, r3, #608
	strned	r0, [r3, #-8]
.L3616:
	ldr	r3, [r4, #732]
	movw	r2, #61280
	ldrd	r0, [r6, r2]
	add	ip, r3, #608
	ldrd	r2, [fp, #-52]
	cmp	r1, r3
	cmpeq	r0, r2
	movhi	r0, r2
	movhi	r1, r3
	add	r2, r6, #61184
	strd	r0, [ip]
	ldr	r3, [r4, #732]
	ldrd	r0, [r2, #104]
	add	ip, r3, #624
	ldrd	r2, [fp, #-60]
	cmp	r1, r3
	cmpeq	r0, r2
	movhi	r0, r2
	movhi	r1, r3
	strd	r0, [ip, #-8]
	mov	ip, #2
	ldr	r3, [r5, #3344]
	mov	r0, #3
	ldr	r2, [r4, #732]
	cmp	r3, r10
	movcs	r3, r10
	str	r3, [r2, #16]
	ldr	r3, [r5, #3348]
	ldr	r2, [r4, #732]
	cmp	r3, r9
	movcs	r3, r9
	str	r3, [r2, #20]
	ldr	r3, [r5, #3352]
	ldr	r2, [r4, #732]
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r2, #24]
	ldr	r3, [r5, #3356]
	ldr	r2, [r4, #732]
	cmp	r3, r7
	movcs	r3, r7
	str	r3, [r2, #28]
	ldr	r2, [r4, #732]
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r5, #3330]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r2, [r4, #732]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #1]
	ldr	r2, [r4, #732]
	ldr	r1, [r5, #4020]
	ldr	r3, [r2, #684]
	cmp	r3, r1
	movcc	r3, r1
	str	r3, [r2, #684]
	ldr	r3, [r4, #732]
	strb	ip, [r3, #784]
	ldr	r3, [r4, #732]
	strb	r0, [r3, #704]
	ldr	r3, [r4, #732]
	ldr	r2, [r5, #4028]
	str	r2, [r3, #800]
	ldr	r2, [r4, #732]
	ldr	r3, [r2, #800]
	ldr	r1, [r2, #760]
	add	r3, r3, r1
	mov	r3, r3, lsr #1
	str	r3, [r2, #720]
	ldr	r3, [r4, #732]
	ldr	r2, [r3, #720]
	str	r2, [r3, #688]
	ldr	r3, [r4, #732]
	ldr	r2, [r3, #820]
	str	r2, [r3, #740]
	ldrb	r3, [r5, #3335]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #732]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	beq	.L3671
.L3621:
	strb	r2, [r3, #3]
	mov	r2, #0
	ldr	r3, [r4, #732]
	ldr	r0, [r4, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_SetRef
	mov	r0, r6
	mov	r2, #0
	ldr	r1, [r4, #732]
	bl	OutputFrmToVO
	ldr	r3, [r4, #732]
	cmp	r3, #0
	mov	r7, r0
	bne	.L3667
	b	.L3622
.L3596:
	ldr	ip, [r4, #732]
	mov	r2, #640
	add	r1, r5, #3344
	cmp	ip, #0
	ldreq	r3, [r5, #3984]
	streq	r3, [r4, #732]
	streq	r3, [r3, #780]
	ldreq	ip, [r4, #732]
	add	lr, ip, #608
	add	r7, ip, #624
	ldr	r3, [ip, #600]
	add	r0, ip, #16
	ldrd	r8, [lr]
	ldr	r10, [ip, #16]
	str	r3, [fp, #-72]
	strd	r8, [fp, #-52]
	ldr	r3, [ip, #604]
	ldrd	r8, [r7, #-8]
	ldr	r7, [ip, #28]
	str	r3, [fp, #-68]
	strd	r8, [fp, #-60]
	ldr	r9, [ip, #20]
	ldr	r8, [ip, #24]
	bl	memcpy
	add	r2, r6, #61184
	ldr	ip, [fp, #-68]
	add	r2, r2, #96
	ldr	r3, [fp, #-72]
	ldr	r0, [r2, #-8]
	ldr	r2, [r2, #-4]
	and	r1, r3, ip
	and	r0, r0, r2
	adds	r2, r1, #1
	movne	r2, #1
	cmn	r0, #1
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r4, #732]
	strne	ip, [r2, #604]
	strne	r3, [r2, #600]
	movw	r2, #61280
	ldr	r3, [r4, #732]
	ldrd	r0, [r6, r2]
	add	ip, r3, #608
	ldrd	r2, [fp, #-52]
	cmp	r1, r3
	cmpeq	r0, r2
	movhi	r0, r2
	movhi	r1, r3
	add	r2, r6, #61184
	strd	r0, [ip]
	ldr	r3, [r4, #732]
	ldrd	r0, [r2, #104]
	add	ip, r3, #624
	ldrd	r2, [fp, #-60]
	cmp	r1, r3
	cmpeq	r0, r2
	movhi	r0, r2
	movhi	r1, r3
	strd	r0, [ip, #-8]
	mov	ip, #1
	ldr	r3, [r5, #3344]
	mov	r0, #3
	ldr	r2, [r4, #732]
	cmp	r3, r10
	movcs	r3, r10
	str	r3, [r2, #16]
	ldr	r3, [r5, #3348]
	ldr	r2, [r4, #732]
	cmp	r3, r9
	movcs	r3, r9
	str	r3, [r2, #20]
	ldr	r3, [r5, #3352]
	ldr	r2, [r4, #732]
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r2, #24]
	ldr	r3, [r5, #3356]
	ldr	r2, [r4, #732]
	cmp	r3, r7
	movcs	r3, r7
	str	r3, [r2, #28]
	ldr	r2, [r4, #732]
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r5, #3330]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r2, [r4, #732]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #1]
	ldr	r2, [r4, #732]
	ldr	r1, [r5, #4020]
	ldr	r3, [r2, #684]
	cmp	r3, r1
	movcc	r3, r1
	str	r3, [r2, #684]
	ldr	r3, [r4, #732]
	strb	ip, [r3, #744]
	ldr	r3, [r4, #732]
	strb	r0, [r3, #704]
	ldr	r3, [r4, #732]
	ldr	r2, [r5, #4028]
	str	r2, [r3, #760]
	ldr	r2, [r4, #732]
	ldr	r3, [r2, #800]
	ldr	r1, [r2, #760]
	add	r3, r3, r1
	mov	r3, r3, lsr ip
	str	r3, [r2, #720]
	ldr	r3, [r4, #732]
	ldr	r2, [r3, #720]
	str	r2, [r3, #688]
	ldr	r3, [r4, #732]
	ldr	r2, [r3, #780]
	str	r2, [r3, #740]
	ldrb	r3, [r5, #3335]	@ zero_extendqisi2
	cmp	r3, ip
	ldr	r3, [r4, #732]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bne	.L3621
.L3671:
	orr	r2, r2, ip
	b	.L3621
.L3675:
	str	r0, [sp]
	movw	r3, #2961
	ldr	r2, .L3677
	mov	r0, #22
	ldr	r1, .L3677+4
	bl	dprint_vfmw
	b	.L3592
.L3610:
	ldr	r3, [r5, #3984]
	mov	r7, r1
	str	r3, [r4, #732]
	str	r3, [r3, #820]
	b	.L3612
.L3597:
	ldr	r3, [r5, #3984]
	mov	r7, r1
	str	r3, [r4, #732]
	str	r3, [r3, #780]
	b	.L3599
.L3674:
	str	r7, [sp]
	movw	r3, #3129
	ldr	r2, .L3677
	mov	r0, #22
	ldr	r1, .L3677+4
	bl	dprint_vfmw
	b	.L3611
.L3676:
	str	r7, [sp]
	movw	r3, #3013
	ldr	r2, .L3677
	mov	r0, #22
	ldr	r1, .L3677+4
	bl	dprint_vfmw
	b	.L3598
.L3678:
	.align	2
.L3677:
	.word	.LANCHOR0+308
	.word	.LC355
	UNWIND(.fnend)
	.size	DirectOutput, .-DirectOutput
	.align	2
	.global	StorePicInDPB
	.type	StorePicInDPB, %function
StorePicInDPB:
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
	subs	r4, r0, #0
	beq	.L3859
	add	r2, r4, #16384
	add	r5, r4, #57344
	mov	r3, #0
	str	r3, [r2, #3444]
	ldrb	r3, [r5, #3331]	@ zero_extendqisi2
	sub	r3, r3, #2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r2, #3448]
	ldrb	r3, [r5, #3328]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3860
	add	r6, r4, #61440
	ldr	r3, .L3884
	ldr	r1, [r6, #2680]
	ldr	r2, [r6, #2692]
	ldr	r3, [r3, r1, asl #2]
	str	r2, [r6, #2688]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L3861
.L3684:
	ldr	r0, [r6, #2608]
	cmp	r0, #2
	beq	.L3862
	ldr	r7, [r4]
	ldr	r3, [r7, #24]
	cmp	r3, #0
	bne	.L3689
	ldr	r2, [r6, #2684]
	cmp	r2, #2
	beq	.L3691
	ldrb	r2, [r5, #3330]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3691
.L3770:
	ldrb	r1, [r5, #3331]	@ zero_extendqisi2
	ldr	r9, [r5, #3984]
	sub	r2, r1, #1
	cmp	r2, #1
	movhi	r2, #0
	movls	r2, #1
	cmp	r1, #0
	beq	.L3693
	ldrb	r0, [r9, #1]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	ip, r2
	orrne	ip, r2, #1
	cmp	ip, #0
	beq	.L3692
	cmp	r2, #0
	beq	.L3863
.L3773:
	ldr	r2, [r6, #2684]
	cmp	r2, #0
	bne	.L3696
	mov	r3, #1
	mov	r2, #736
	str	r3, [r6, #2684]
	add	r1, r4, #60672
	add	r0, r5, #4064
	bl	memcpy
	ldr	r3, [r7, #24]
.L3692:
	cmp	r3, #2
	beq	.L3864
.L3691:
	ldr	r3, [r5, #4000]
	cmp	r3, #0
	beq	.L3727
	ldr	r3, [r6, #2672]
	ldr	r2, [r5, #4028]
	cmp	r3, r2
	bcs	.L3728
	ldrb	r1, [r5, #3330]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L3728
	ldr	r1, [r7, #644]
	cmp	r1, #0
	beq	.L3865
.L3728:
	mov	r0, r4
	bl	Marking
	subs	r2, r0, #0
	bne	.L3866
	mov	r0, r4
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	mov	r0, r4
	bl	RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L3867
.L3721:
	ldrb	r3, [r5, #3329]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3732
	add	r7, r4, #24576
.L3736:
	ldr	r3, [r5, #4000]
	cmp	r3, #0
	beq	.L3868
	ldr	r2, [r7, #2144]
	ldr	r3, [r7, #2148]
	ldr	ip, [r7, #2136]
	add	r1, r3, r2
	cmp	ip, r1
	bhi	.L3744
	ldr	r1, [r4]
	ldr	r1, [r1, #24]
	cmp	r1, #3
	beq	.L3745
	ldr	r1, .L3884+4
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L3745
	str	r3, [sp, #4]
	mov	r0, #1
	mov	r3, ip
	str	r2, [sp]
	ldr	r1, .L3884+8
	movw	r2, #4128
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearDPB
	movw	r3, #4130
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3689:
	ldrb	r2, [r5, #3330]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3692
	b	.L3770
.L3693:
	cmp	r2, #0
	bne	.L3773
.L3699:
	add	r8, r4, #60672
.L3702:
	cmp	r1, #0
	beq	.L3703
	ldrb	r3, [r8, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3869
.L3703:
	ldr	r3, [r8, #700]
	str	r3, [r9, #688]
.L3704:
	mov	r1, r9
	mov	r0, r4
	bl	GetImagePara
	ldr	r1, [r9, #656]
	ldr	r0, [r6, #2680]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L3870
	ldrb	r3, [r8, #3]	@ zero_extendqisi2
	add	ip, r8, #608
	cmp	r3, #0
	beq	.L3706
	ldrb	r3, [r8, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3871
.L3706:
	ldrd	r2, [ip, #-8]
	add	r1, r7, #592
.L3851:
	strd	r2, [r1, #-8]
.L3707:
	ldrd	r2, [ip]
	add	r0, r8, #624
	add	ip, r7, #608
	add	lr, r8, #448
	strd	r2, [r1]
	ldrd	r2, [r0, #-8]
	add	r0, r7, #432
	strd	r2, [ip, #-8]
	ldr	r3, [r8, #16]
	str	r3, [r7]
	ldr	r3, [r8, #20]
	str	r3, [r7, #4]
	ldr	r3, [r8, #24]
	str	r3, [r7, #8]
	ldr	r3, [r8, #28]
	str	r3, [r7, #12]
	ldr	r1, [r9, #688]
	cmp	r1, #0
	str	r1, [r7, #152]
	ldr	r3, [r8, #440]
	str	r3, [r7, #424]
	ldr	r3, [r8, #436]
	str	r3, [r7, #420]
	ldrd	r2, [lr]
	strd	r2, [r0]
	beq	.L3708
	ldrb	r3, [r7, #64]	@ zero_extendqisi2
	ands	r8, r3, #3
	beq	.L3872
.L3709:
	ldr	r3, [r4]
	ldr	r2, [r3, #4]
	cmp	r2, r1
	bcs	.L3708
	ldr	r3, [r3, #644]
	cmp	r3, #1
	beq	.L3708
	ldr	r3, .L3884+16
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L3719
	str	r1, [fp, #-52]
	mov	r3, #8
	str	r2, [fp, #-48]
	mov	r1, #104
	sub	r2, fp, #52
	ldr	r0, [r6, #2680]
	blx	r4
.L3719:
	ldr	r1, [r9, #656]
	mov	r2, #0
	ldr	r0, [r6, #2680]
	bl	FSP_SetDisplay
	movw	r3, #3972
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3860:
	mov	r0, r3
	ldr	r1, .L3884+20
	bl	dprint_vfmw
	mov	r3, #3808
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	add	r6, r4, #61440
	bl	dprint_vfmw
.L3772:
	ldr	r3, [r5, #3984]
	mov	r2, #1
	ldr	r0, [r6, #2680]
	mvn	r7, #0
	ldr	r1, [r3, #656]
	bl	FSP_ClearLogicFs
	mov	r3, r7
	movw	r2, #4228
	ldr	r1, .L3884+24
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #3984]
	mov	r3, #0
	strb	r3, [r2, #4]
	ldr	r2, [r5, #3984]
	strb	r3, [r2, #1]
.L3769:
	mov	r0, r7
	mov	r3, #0
	strb	r3, [r5, #3328]
.L3842:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3866:
	ldr	r1, .L3884+28
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #4049
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3872:
	movw	r2, #3947
	ldr	r1, .L3884+32
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3884+16
	ldr	r10, [r3]
	cmp	r10, #0
	beq	.L3852
	mov	r3, r8
	mov	r2, r8
	mov	r1, #111
	ldr	r0, [r6, #2680]
	blx	r10
.L3852:
	ldr	r1, [r7, #152]
	cmp	r1, #0
	bne	.L3709
.L3708:
	mov	r2, #1
	ldr	r1, [r9, #656]
	ldr	r0, [r6, #2680]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #2680]
	add	r3, r4, #8
	str	r7, [sp]
	mov	r2, r4
	mov	r1, #0
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L3713
	mov	r2, #0
	ldr	r1, [r9, #656]
	ldr	r0, [r6, #2680]
	bl	FSP_SetDisplay
.L3714:
	ldr	r3, [r4]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r7, #16]
	bcs	.L3873
.L3716:
	ldr	r2, [r6, #2684]
	ldr	r3, [r6, #2700]
	cmp	r2, #2
	add	r3, r3, #2
	str	r3, [r6, #2700]
	movne	r3, #1
	strne	r3, [r9, #824]
	mov	r3, #2
	str	r3, [r6, #2684]
	ldr	r7, [r4]
	ldr	r3, [r7, #24]
	b	.L3692
.L3863:
	cmp	r0, #0
	beq	.L3692
	b	.L3699
.L3745:
	ldr	r8, [r7, #2140]
	mov	r3, #0
	str	r3, [fp, #-52]
	mvn	r3, #-2147483648
	cmp	r8, ip
	strhi	ip, [r7, #2140]
	str	r3, [fp, #-56]
	movhi	r8, ip
	cmp	r8, #0
	beq	.L3778
	add	ip, r4, #26368
	ldr	r2, [fp, #-56]
	ldr	r1, [fp, #-52]
	add	ip, ip, #148
	mvn	lr, #-2147483648
	mov	r3, #0
.L3750:
	ldr	r0, [ip, #4]!
	ldr	r0, [r0, #672]
	cmp	r0, lr
	movlt	r1, r3
	add	r3, r3, #1
	movlt	r2, r0
	cmp	r3, r8
	mov	lr, r2
	bne	.L3750
	str	r2, [fp, #-56]
	str	r1, [fp, #-52]
.L3748:
	mov	r0, r4
	bl	RemoveFrameStoreOutDPB
	mov	r0, r4
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	ldr	ip, [r7, #2136]
.L3744:
	mvn	r10, #0
	mov	r9, r10
	b	.L3760
.L3761:
	bl	GetMinPOC
	ldr	r2, [r5, #4000]
	cmp	r2, #0
	bne	.L3751
	ldr	r1, [r5, #4004]
	ldr	r2, [fp, #-56]
	cmp	r1, r2
	blt	.L3752
.L3751:
	ldr	r2, [r7, #2136]
	cmp	r2, #0
	beq	.L3752
	ldr	r8, [r7, #2140]
	cmp	r8, r10
	ldrne	r9, [fp, #-52]
	bne	.L3758
	ldr	r3, [fp, #-52]
	cmp	r3, r9
	beq	.L3874
	mov	r9, r3
.L3758:
	mov	r1, r9
	mov	r0, r4
	bl	OutputFrmFromDPB
	mov	r10, r8
	cmn	r0, #1
	beq	.L3759
	ldr	ip, [r7, #2136]
.L3760:
	ldr	lr, [r7, #2140]
	sub	r2, fp, #52
	sub	r1, fp, #56
	mov	r0, r4
	cmp	lr, ip
	bcs	.L3761
	ldr	r3, [r5, #4000]
	cmp	r3, #0
	beq	.L3762
	ldrb	r3, [r5, #3332]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3762
	ldr	r2, [r7, #2144]
	cmp	r2, #0
	beq	.L3762
	add	r2, r4, #26368
	mov	lr, r3
	add	r2, r2, #212
	b	.L3767
.L3764:
	ldr	r1, [r7, #2144]
	cmp	r1, r3
	bls	.L3875
.L3767:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	ldr	r0, [r5, #3992]
	ldr	ip, [r1, #660]
	cmp	ip, r0
	bne	.L3764
	ldr	r0, [r1, #824]
	cmp	r0, #1
	beq	.L3764
	strb	lr, [r1, #2]
	ldr	r1, [r2]
	ldrb	r0, [r1, #4]	@ zero_extendqisi2
	cmp	r0, #1
	streq	r0, [r1, #676]
	ldreq	r1, [r2]
	streqb	lr, [r1, #4]
	ldreq	r1, [r2]
	ldr	r8, [r6, #1368]
	ldr	ip, [r1, #692]
	add	r0, ip, #15680
	cmp	ip, r8
	add	r0, r0, #4
	strne	lr, [r4, r0, asl #2]
	strne	r8, [r1, #692]
	b	.L3764
.L3875:
	ldr	lr, [r7, #2140]
.L3762:
	add	r2, r4, #60672
	mov	r1, lr
	mov	r0, r4
	bl	InsertFrmInDPB
	ldr	r2, [r7, #2140]
	str	r2, [r6, #728]
	subs	r3, r0, #0
	beq	.L3768
	movw	r2, #4214
	ldr	r1, .L3884+24
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #4215
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3861:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L3684
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L3684
	bl	H264_Sei_Get_Frame_Pts
	b	.L3684
.L3727:
	ldrb	r3, [r5, #3329]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3732
	add	r7, r4, #24576
	ldr	ip, [r7, #2136]
	b	.L3744
.L3864:
	ldr	r3, [r5, #4000]
	cmp	r3, #0
	beq	.L3721
	ldrb	r3, [r5, #3334]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L3722
.L3725:
	add	r7, r4, #24576
	mov	r0, r4
	bl	SimpleSlideDPB
	add	r2, r4, #60672
	ldr	r1, [r7, #2140]
	mov	r0, r4
	bl	InsertFrmInDPB
	subs	r8, r0, #0
	beq	.L3876
	mov	r3, r8
	movw	r2, #4015
	ldr	r1, .L3884+24
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #4016
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3868:
	ldr	ip, [r7, #2136]
	b	.L3744
.L3732:
	ldr	r3, [r6, #732]
	ldr	r0, [r5, #3984]
	cmp	r3, #0
	rsb	r1, r3, r0
	clz	r1, r1
	mov	r1, r1, lsr #5
	moveq	r1, #0
	cmp	r1, #0
	beq	.L3877
	mov	r0, r4
	bl	DirectOutput
	cmn	r0, #1
	mov	r7, r0
	beq	.L3878
	cmp	r0, #1
	ldreq	r2, [r5, #3984]
	moveq	r3, #0
	streqb	r3, [r2, #4]
	ldreq	r2, [r5, #3984]
	streqb	r3, [r2, #1]
.L3740:
	movw	r3, #4085
	mov	r2, r7
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3688
.L3752:
	ldr	r3, [r6, #2608]
	cmp	r3, #2
	beq	.L3879
.L3754:
	mov	r0, r4
	bl	DirectOutput
	cmn	r0, #1
	mov	r7, r0
	beq	.L3880
	cmp	r0, #1
	ldreq	r2, [r5, #3984]
	moveq	r3, #0
	streqb	r3, [r2, #4]
	ldreq	r2, [r5, #3984]
	streqb	r3, [r2, #1]
.L3756:
	movw	r3, #4159
	mov	r2, r7
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
.L3688:
	cmn	r7, #1
	bne	.L3769
	b	.L3772
.L3862:
	ldr	r1, .L3884+36
	bl	dprint_vfmw
	mov	r0, r4
	bl	DirectOutput
	ldr	r3, [r5, #4052]
	ldr	r2, [r6, #1368]
	cmp	r3, r2
	addne	r3, r3, #15680
	addne	r3, r3, #4
	movne	r1, #0
	strne	r1, [r4, r3, asl #2]
	mov	r7, r0
	strne	r2, [r5, #4052]
	cmp	r0, #1
	ldr	r1, .L3884+12
	ldreq	r2, [r5, #3984]
	moveq	r3, #0
	streqb	r3, [r2, #4]
	ldreq	r2, [r5, #3984]
	streqb	r3, [r2, #1]
	mov	r2, r0
	movw	r3, #3842
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3688
.L3877:
	add	r7, r4, #24576
	ldr	ip, [r7, #2140]
	cmp	ip, #0
	beq	.L3736
	ldr	r3, [r7, #1944]
	cmp	r0, r3
	addne	r3, r4, #26368
	addne	r3, r3, #152
	beq	.L3737
.L3741:
	add	r1, r1, #1
	cmp	r1, ip
	beq	.L3736
	ldr	r2, [r3, #4]!
	cmp	r0, r2
	bne	.L3741
.L3737:
	add	r2, r4, #60672
	mov	r0, r4
	bl	InsertFrmInDPB
	cmn	r0, #1
	mov	r7, r0
	beq	.L3881
	mov	r0, r4
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	movw	r3, #4105
	mov	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
.L3726:
	mov	r7, #0
	b	.L3769
.L3696:
	cmp	r2, #1
	beq	.L3882
	cmp	r1, #0
	beq	.L3699
	ldrb	r2, [r9, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3699
	b	.L3692
.L3759:
	mov	r4, r0
	mov	r3, r0
	movw	r2, #4177
	ldr	r1, .L3884+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, r4
	movw	r3, #4178
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3713:
	ldr	r3, [r6, #2708]
	add	r3, r3, #1
	str	r3, [r6, #2708]
	b	.L3714
.L3876:
	ldr	r3, [r7, #2140]
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r7, #2140]
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	mov	r2, r8
	movw	r3, #4024
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3726
.L3768:
	add	r2, r2, #1
	mov	r0, r4
	str	r2, [r7, #2140]
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	b	.L3726
.L3865:
	ldr	r1, .L3884+40
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3884+16
	ldr	r7, [r3]
	cmp	r7, #0
	beq	.L3729
	ldr	r0, [r6, #2672]
	mov	r3, #8
	ldr	ip, [r5, #4028]
	sub	r2, fp, #52
	mov	r1, #104
	str	r0, [fp, #-48]
	str	ip, [fp, #-52]
	ldr	r0, [r6, #2680]
	blx	r7
.L3729:
	mov	r0, r4
	bl	H264_ClearCurrPic
	mov	r0, r4
	bl	ClearDPB
	movw	r3, #4041
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3869:
	mov	r2, #3
	ldr	r3, [r9, #688]
	strb	r2, [r9, #1]
	ldr	r2, [r8, #700]
	add	r3, r3, r2
	str	r3, [r9, #688]
	b	.L3704
.L3871:
	ldrd	r0, [ip, #-8]
	mvn	r3, #0
	mvn	r2, #0
	cmp	r1, r3
	cmpeq	r0, r2
	addne	r1, r7, #592
	bne	.L3707
	add	r3, r4, #61952
	add	r3, r3, #64
	ldrd	r2, [r3, #-8]
	cmp	r3, r1
	add	r1, r7, #592
	cmpeq	r2, r0
	bne	.L3851
	b	.L3707
.L3878:
	mov	r3, r0
	movw	r2, #4075
	ldr	r1, .L3884+24
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3740
.L3874:
	mov	r3, r9
	ldr	r2, .L3884+44
	ldr	r1, .L3884+48
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #4166
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3867:
	ldr	r1, .L3884+52
	mov	r0, #22
	bl	dprint_vfmw
	b	.L3721
.L3879:
	ldrb	r3, [r5, #3331]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r3, [r5, #3984]
	strne	r3, [r6, #736]
	b	.L3754
.L3873:
	mov	r1, r7
	mov	r0, r4
	bl	SetFrmRepeatCount.part.7
	b	.L3716
.L3722:
	mov	r0, r4
	bl	IDRMemMarking
	cmp	r0, #0
	beq	.L3725
	mvn	r0, #0
	b	.L3842
.L3882:
	cmp	r1, #1
	add	r8, r4, #60672
	ldr	r9, [r6, #624]
	beq	.L3883
	cmp	r1, #2
	ldreq	r3, [r5, #4016]
	streq	r3, [r9, #796]
	ldreqb	r1, [r5, #3331]	@ zero_extendqisi2
	b	.L3702
.L3880:
	mov	r3, r0
	movw	r2, #4150
	ldr	r1, .L3884+24
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3756
.L3881:
	mov	r3, r0
	movw	r2, #4098
	ldr	r1, .L3884+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, r7
	movw	r3, #4099
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3870:
	movw	r2, #3915
	ldr	r1, .L3884+56
	bl	dprint_vfmw
	movw	r3, #3916
	mvn	r2, #0
	ldr	r1, .L3884+12
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3772
.L3883:
	ldr	r3, [r5, #4012]
	str	r3, [r9, #756]
	ldrb	r1, [r5, #3331]	@ zero_extendqisi2
	b	.L3702
.L3778:
	mov	r1, r8
	b	.L3748
.L3859:
	movw	r3, #3799
	ldr	r2, .L3884+60
	ldr	r1, .L3884+64
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3842
.L3885:
	.align	2
.L3884:
	.word	s_pstVfmwChan
	.word	g_apple_airplay_mirrorinig_flag
	.word	.LC387
	.word	.LC379
	.word	g_event_report
	.word	.LC378
	.word	.LC383
	.word	.LC385
	.word	.LC382
	.word	.LC380
	.word	.LC384
	.word	.LANCHOR0+324
	.word	.LC388
	.word	.LC386
	.word	.LC381
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	StorePicInDPB, .-StorePicInDPB
	.global	__aeabi_idivmod
	.align	2
	.global	DecGap
	.type	DecGap, %function
DecGap:
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
	add	r10, r0, #24576
	mov	r7, r0
	add	r2, r0, #12288
	ldr	r0, [r10, #1804]
	add	r1, r7, #20480
	movw	r3, #2004
	str	r1, [fp, #-76]
	mov	ip, r1
	ldrb	r1, [r2, #1325]	@ zero_extendqisi2
	mul	r3, r3, r0
	cmp	r1, #1
	mov	r6, #0
	mov	r1, ip
	moveq	r1, #2
	movne	r1, r6
	str	r1, [fp, #-68]
	add	r1, r7, r3
	add	r1, r1, #22272
	ldr	r0, [ip, #224]
	add	r9, r7, #16384
	add	r4, r7, #57344
	mov	r3, r1
	add	r1, r1, #96
	str	r2, [fp, #-72]
	add	r3, r3, #100
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	ldr	r2, [r2, #3504]
	str	r0, [fp, #-60]
	str	r1, [fp, #-92]
	ldr	r0, [ip, #220]
	ldr	r1, [r9, #3472]
	ldr	ip, [r9, #3468]
	str	r3, [r4, #3988]
	ldr	r5, [r10, #2140]
	str	ip, [fp, #-84]
	cmp	r5, r6
	str	r1, [fp, #-88]
	str	r6, [fp, #-52]
	str	r6, [fp, #-48]
	beq	.L3902
	add	r2, r2, #4
	mov	r8, #1
	mov	r3, r8, asl r2
	add	r0, r0, r8
	str	r3, [fp, #-80]
	mov	r1, r3
	bl	__aeabi_uidivmod
	str	r6, [r9, #3472]
	str	r6, [r9, #3468]
	mov	r0, #2
	mov	r5, r1
	ldr	r1, .L3905
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, [fp, #-60]
	mov	r0, #2
	ldr	r1, .L3905+4
	bl	dprint_vfmw
	sub	r2, fp, #52
	sub	r1, fp, #48
	mov	r0, r7
	bl	GetMaxPOC
	ldr	r3, [fp, #-60]
	cmp	r3, r5
	strne	r6, [fp, #-64]
	movne	r6, r8
	bne	.L3895
	b	.L3894
.L3892:
	mov	r1, r8
	mov	r0, r7
	strb	r8, [r4, #3332]
	bl	StorePicInDPB
	ldr	r1, [fp, #-80]
	subs	r3, r0, #0
	add	r0, r5, #1
	bne	.L3903
	ldr	r3, [fp, #-76]
	str	r5, [r3, #220]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-60]
	cmp	r3, r1
	mov	r5, r1
	beq	.L3894
	ldr	r3, [r10, #2140]
	ldr	r2, [fp, #-64]
	cmp	r2, r3
	bhi	.L3894
.L3895:
	mov	r1, #1
	mov	r0, r7
	bl	AllocFrameStore
	mov	r8, #0
	ldr	r1, .L3905+8
	subs	r3, r0, #0
	mov	r0, #2
	bne	.L3904
	str	r3, [fp, #-56]
	bl	dprint_vfmw
	ldr	r1, [r4, #3984]
	strb	r6, [r4, #3334]
	ldr	r3, [fp, #-68]
	str	r5, [r1, #660]
	ldr	r1, [r4, #3984]
	str	r5, [r4, #3992]
	str	r5, [r1, #712]
	str	r3, [r4, #4000]
	ldr	r1, [r4, #3984]
	ldr	r3, [fp, #-56]
	str	r3, [r1, #708]
	ldr	r1, [r4, #3984]
	str	r6, [r1, #676]
	ldr	r1, [r4, #3984]
	strb	r3, [r1, #4]
	ldr	r1, [r4, #3984]
	strb	r6, [r1]
	ldr	r1, [r4, #3988]
	strb	r6, [r4, #3330]
	strb	r3, [r1, #3]
	ldr	r3, [fp, #-72]
	ldr	r3, [r3, #3508]
	cmp	r3, #0
	beq	.L3892
	str	r5, [r9, #3484]
	mov	r0, r7
	bl	DecPOC
	ldr	r3, [r9, #3464]
	ldr	r1, [fp, #-48]
	str	r3, [r4, #4004]
	ldr	r3, [r9, #3460]
	str	r3, [r4, #4008]
	ldr	r3, [r9, #3452]
	cmp	r3, r1
	str	r3, [r4, #4012]
	ldr	r3, [r9, #3456]
	str	r3, [r4, #4016]
	bls	.L3892
	cmp	r1, r3
	ldrcc	r3, [fp, #-64]
	addcc	r3, r3, #1
	strcc	r3, [fp, #-64]
	b	.L3892
.L3902:
	ldr	r1, .L3905+12
	mov	r0, r5
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3894:
	ldr	r3, [fp, #-84]
	mov	r0, #0
	ldrb	r2, [fp, #-92]	@ zero_extendqisi2
	str	r3, [r9, #3468]
	ldr	r3, [fp, #-88]
	str	r3, [r9, #3472]
	ldr	r3, [r4, #3988]
	strb	r2, [r3, #3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3904:
	ldr	r3, [fp, #-84]
	mov	r0, r8
	ldrb	r2, [fp, #-92]	@ zero_extendqisi2
	ldr	r1, .L3905+16
	str	r3, [r9, #3468]
	ldr	r3, [fp, #-88]
	str	r3, [r9, #3472]
	ldr	r3, [r4, #3988]
	strb	r2, [r3, #3]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3903:
	ldr	r2, [fp, #-84]
	mov	r0, r8
	ldrb	lr, [fp, #-92]	@ zero_extendqisi2
	ldr	r1, .L3905+20
	str	r2, [r9, #3468]
	ldr	r2, [fp, #-88]
	str	r2, [r9, #3472]
	movw	r2, #6491
	ldr	ip, [r4, #3988]
	strb	lr, [ip, #3]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3906:
	.align	2
.L3905:
	.word	.LC390
	.word	.LC391
	.word	.LC393
	.word	.LC389
	.word	.LC392
	.word	.LC394
	UNWIND(.fnend)
	.size	DecGap, .-DecGap
	.align	2
	.global	InitPic
	.type	InitPic, %function
InitPic:
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
	subs	r5, r0, #0
	beq	.L4018
	add	r10, r5, #12288
	add	r8, r5, #20480
	mov	r9, #2208
	add	r4, r5, #57344
	ldr	r3, [r10, #1304]
	mov	r1, #4000
	ldr	r0, [r8, #216]
	ldrb	r2, [r4, #3328]	@ zero_extendqisi2
	mla	r9, r9, r0, r3
	cmp	r2, #0
	ldr	r3, [r10, #1300]
	addeq	r7, r5, #61440
	ldr	r2, [r9, #28]
	mla	r3, r1, r2, r3
	str	r3, [fp, #-56]
	bne	.L4019
.L3910:
	sub	r1, fp, #48
	mov	r0, r5
	bl	GetReRangeFlag
	ldr	r3, [fp, #-56]
	ldr	r2, [r10, #1344]
	ldr	r3, [r3, #36]
	cmp	r2, r3
	mov	r6, r0
	beq	.L4020
.L3913:
	ldr	r3, .L4033
	add	r0, r5, #13568
	ldr	r1, [fp, #-56]
	mov	r2, #0
	add	r0, r0, #28
	strb	r2, [r1, #24]
	mov	r2, #4000
	ldr	r3, [r3, #56]
	blx	r3
.L3914:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	bne	.L3915
	ldr	r3, [r5]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	beq	.L3915
.L4013:
	add	r6, r5, #16384
.L3916:
	ldr	r2, [r6, #1236]
	ldr	r3, [r9, #24]
	cmp	r2, r3
	bne	.L3924
	ldrb	r3, [r9, #20]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3924
.L3925:
	ldr	r3, [r6, #3444]
	ldr	r1, [r10, #3504]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r8, #220]
	strne	r3, [r7, #712]
	ldr	r3, [r7, #2608]
	cmp	r3, #2
	beq	.L3927
	ldr	r2, [r5]
	ldr	r3, [r2, #24]
	str	r2, [fp, #-60]
	sub	r3, r3, #2
	cmp	r3, #1
	bls	.L3927
	ldr	r3, [r8, #224]
	ldr	r9, [r8, #220]
	cmp	r3, r9
	str	r3, [fp, #-64]
	beq	.L3928
	add	r0, r1, #4
	mov	r1, #1
	mov	r3, r1, asl r0
	add	r0, r9, r1
	str	r3, [fp, #-68]
	mov	r1, r3
	bl	__aeabi_uidivmod
	ldr	r3, [fp, #-64]
	cmp	r3, r1
	beq	.L3964
	ldr	r2, [fp, #-60]
	ldr	r1, [r2, #616]
	cmp	r1, #0
	bne	.L3929
	ldr	r1, [r2, #660]
	cmp	r1, #1
	beq	.L4021
.L3930:
	cmp	r3, r9
	bls	.L3931
	ldr	r1, [r6, #484]
	rsb	r9, r9, r3
	cmp	r1, r9
	bcs	.L3929
	ldrb	r1, [r8, #208]	@ zero_extendqisi2
	cmp	r1, #2
	beq	.L3932
.L3937:
	ldr	r3, [r7, #2676]
	cmp	r3, #0
	bne	.L3929
	mov	r0, r5
	bl	H264_ClearCurrPic
	ldr	r3, .L4033+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4022
.L3938:
	ldr	lr, [r6, #484]
	movw	r2, #6703
	b	.L4014
.L3915:
	ldr	r3, [r7, #2640]
	cmp	r6, #0
	add	r3, r3, #1
	str	r3, [r7, #2640]
	bne	.L3917
	ldr	r3, [r5]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	beq	.L3918
	mov	r0, r5
	bl	FlushDPB
	cmp	r0, #0
	bne	.L4023
.L4012:
	mov	r0, r5
	bl	InitDPB
	cmp	r0, #0
	bne	.L3961
	ldr	r3, [r5]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L4013
.L3922:
	add	r6, r5, #16384
	add	r3, r5, #62720
	add	r3, r3, #84
	mov	r0, r5
	ldr	ip, [r6, #484]
	str	ip, [r7, #1368]
	ldr	r2, [r6, #464]
	ldrb	r1, [r10, #1326]	@ zero_extendqisi2
	add	r2, r2, #1
	ldr	lr, [r6, #460]
	rsb	r1, r1, #2
	str	ip, [sp]
	mov	r2, r2, asl #4
	add	ip, lr, #1
	mul	r2, r1, r2
	mov	r1, ip, asl #4
	str	r1, [fp, #-60]
	str	r2, [fp, #-64]
	bl	H264_ArrangeVahbMem
	cmp	r0, #1
	beq	.L4024
	ldr	r3, [r5]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	mvneq	r0, #1
	beq	.L4007
	mov	r4, #0
	ldr	r1, .L4033+8
	str	r4, [r10, #1276]
	mov	r0, r4
	str	r4, [r10, #1280]
	bl	dprint_vfmw
	mov	r1, r4
	mov	r0, r5
	bl	ClearAll
	mvn	r0, #0
.L4007:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4019:
	ldr	r3, [r4, #3984]
	cmp	r3, #0
	beq	.L3911
	ldrb	r6, [r3, #1]	@ zero_extendqisi2
	add	r7, r5, #61440
	cmp	r6, #0
	beq	.L4025
.L3912:
	mov	r3, #0
	strb	r3, [r4, #3328]
	b	.L3910
.L3924:
	ldr	r3, .L4033
	add	r0, r5, #17408
	mov	r2, #0
	mov	r1, r9
	strb	r2, [r9, #20]
	add	r0, r0, #188
	ldr	r3, [r3, #56]
	mov	r2, #2208
	blx	r3
	b	.L3925
.L3964:
	mov	r9, r3
.L3928:
	ldr	r3, [r8, #236]
	mov	r0, r5
	cmp	r3, #0
	strne	r9, [r8, #220]
	str	r9, [r6, #3484]
	bl	DecPOC
	mov	r1, #0
	mov	r0, r5
	bl	AllocFrameStore
	cmp	r0, #0
	bne	.L4026
	strb	r0, [r4, #3335]
	mov	r1, #1
	strb	r1, [r4, #3328]
	mvn	ip, #0
	ldrb	r3, [r8, #211]	@ zero_extendqisi2
	strb	r3, [r4, #3334]
	ldr	r3, [r8, #224]
	str	r3, [r4, #3992]
	str	r3, [fp, #-68]
	ldr	r3, [r8, #236]
	str	r3, [r4, #4000]
	ldr	lr, [r6, #3464]
	str	r3, [fp, #-60]
	str	lr, [r4, #4004]
	ldr	lr, [r6, #3460]
	str	lr, [r4, #4008]
	ldr	lr, [r6, #3452]
	str	lr, [r4, #4012]
	ldr	lr, [r6, #3456]
	str	ip, [r4, #4048]
	strb	r0, [r4, #3330]
	strb	r0, [r4, #3333]
	str	lr, [r4, #4016]
	strb	r0, [r4, #3332]
	ldrb	r2, [r8, #209]	@ zero_extendqisi2
	cmp	r2, #0
	strneb	r1, [r8, #209]
	ldrb	r9, [r10, #1326]	@ zero_extendqisi2
	ldr	r0, [r6, #464]
	movne	r2, r1
	rsb	r9, r9, #2
	movne	r1, #2
	str	r2, [fp, #-64]
	mla	r9, r0, r9, r9
	mov	r0, r9
	bl	__aeabi_uidiv
	str	r9, [r4, #4040]
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-60]
	cmp	r2, #0
	movne	r2, #0
	str	r0, [r4, #4036]
	ldr	ip, [r6, #460]
	add	r1, ip, #1
	str	r1, [r4, #4032]
	mul	r1, r1, r0
	str	r1, [r4, #4044]
	ldrb	r1, [r6, #1212]	@ zero_extendqisi2
	strb	r1, [r4, #3336]
	movne	r1, r2
	bne	.L3950
	ldrb	r1, [r10, #1327]	@ zero_extendqisi2
	cmp	r1, #0
	movne	r2, #1
	movne	r1, r2
.L3950:
	cmp	r3, #0
	strb	r1, [r4, #3337]
	add	r1, r5, #24576
	str	r2, [r7, #2596]
	ldrne	r3, [fp, #-68]
	movw	r0, #2004
	add	r2, r5, #61184
	movw	lr, #61280
	strne	r3, [r8, #220]
	mov	ip, r2
	ldr	r3, [r1, #1804]
	add	r2, r2, #96
	ldr	r1, .L4033+12
	mla	r3, r0, r3, r5
	mov	r0, #29
	add	r3, r3, #22272
	add	r3, r3, #100
	str	r3, [r4, #3988]
	ldr	r3, [r5]
	ldrd	r8, [r3, #64]
	strd	r8, [r2, #-8]
	ldrd	r8, [r3, #80]
	strd	r8, [r5, lr]
	ldrd	r8, [r3, #96]
	ldr	lr, [fp, #-56]
	strd	r8, [ip, #104]
	mvn	r8, #0
	ldr	ip, [r3, #112]
	mvn	r9, #0
	str	ip, [r4, #3344]
	ldr	ip, [r3, #116]
	str	ip, [r4, #3348]
	ldr	ip, [r3, #120]
	str	ip, [r4, #3352]
	ldr	ip, [r3, #136]
	str	ip, [r4, #3356]
	ldrb	ip, [r3, #56]	@ zero_extendqisi2
	strb	ip, [r4, #3976]
	ldr	ip, [lr, #44]
	str	ip, [r4, #3512]
	ldr	ip, [lr, #48]
	str	ip, [r4, #3516]
	strd	r8, [r3, #64]
	ldrd	r2, [r2, #-8]
	bl	dprint_vfmw
	movw	r3, #61280
	ldrd	r2, [r3, r5]
	mov	r0, #29
	ldr	r1, .L4033+16
	bl	dprint_vfmw
	ldr	r3, [r6, #460]
	mov	r2, #4
	ldr	r8, .L4033
	add	r3, r3, #1
	add	r0, r5, #60672
	mov	r1, #0
	add	r0, r0, #80
	mov	r3, r3, asl r2
	str	r3, [r4, #3412]
	ldrb	ip, [r10, #1326]	@ zero_extendqisi2
	ldr	lr, [r6, #464]
	rsb	r3, ip, #2
	ldr	r8, [r8, #48]
	mla	r3, lr, r3, r3
	mov	r3, r3, asl r2
	str	r3, [r4, #3416]
	ldr	r10, [r10, #1348]
	ldr	r9, [r6, #528]
	subs	r10, r10, #1
	and	r9, r9, #7
	movne	r10, #1
	blx	r8
	ldrb	r2, [r4, #3408]	@ zero_extendqisi2
	mov	ip, #2
	ldrb	r3, [r4, #3409]	@ zero_extendqisi2
	add	r0, r5, #60672
	and	r2, r2, #252
	mov	r1, r9
	bfi	r2, r10, #2, #3
	bfi	r3, ip, #0, #2
	strb	r2, [r4, #3408]
	and	r3, r3, #243
	ldr	lr, [r6, #532]
	uxtb	r2, r2
	bfi	r3, ip, #4, #2
	strb	r3, [r4, #3409]
	bfi	r2, lr, #5, #3
	strb	r2, [r4, #3408]
	ldr	r3, [r4, #3408]
	add	r0, r0, #16
	bfi	r3, r9, #14, #3
	str	r3, [r4, #3408]
	bl	SetAspectRatio
	ldrb	r3, [r4, #3331]	@ zero_extendqisi2
	ldr	r2, [r4, #3984]
	adds	r3, r3, #0
	ldr	r1, [r7, #2640]
	movne	r3, #1
	cmp	r2, #0
	str	r3, [r4, #3396]
	str	r1, [r4, #3500]
	beq	.L4027
	ldr	r3, [r4, #3408]
	ldr	r1, [fp, #-56]
	str	r3, [r2, #80]
	ldr	r3, [r4, #3984]
	ldr	r2, [r4, #3396]
	str	r2, [r3, #68]
	ldr	r3, [r4, #3984]
	ldr	r2, [r4, #3448]
	str	r2, [r3, #120]
	ldr	r3, [r4, #3984]
	ldr	r2, [r4, #3444]
	str	r2, [r3, #116]
	ldr	r3, [r4, #3984]
	ldr	r2, [r4, #3412]
	str	r2, [r3, #84]
	ldr	r3, [r4, #3984]
	ldr	r2, [r4, #3416]
	str	r2, [r3, #88]
	ldr	r3, [r1, #3284]
	ldr	r2, [r4, #3984]
	str	r3, [r2, #100]
	str	r3, [r4, #3428]
	ldr	r2, [r4, #3984]
	ldr	r3, [r1, #3288]
	str	r3, [r2, #104]
	str	r3, [r4, #3432]
	ldr	r2, [r4, #3984]
	ldr	r3, [r1, #3276]
	str	r3, [r2, #92]
	str	r3, [r4, #3420]
	ldr	r2, [r4, #3984]
	ldr	r3, [r1, #3280]
	str	r3, [r2, #96]
	str	r3, [r4, #3424]
	ldr	r3, [r4, #3984]
	ldr	r0, [r7, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L3953
	ldr	r3, [r4, #3396]
	mov	r1, #0
	ldr	r2, [r0, #4]
	subs	r3, r3, r1
	ldr	r0, [r7, #2680]
	movne	r3, #1
	bl	FSP_SetStoreType
.L3953:
	add	r2, r5, #61184
	add	lr, r5, #62720
	ldr	r8, [r7, #1392]
	add	lr, lr, #116
	mov	r0, r2
	add	r2, r2, #40
	add	r0, r0, #72
	mov	r6, #0
.L3957:
	ldr	r3, [r2, #8]!
	cmp	r3, #0
	beq	.L4028
.L3954:
	cmp	r2, r0
	bne	.L3957
	cmp	r8, #0
	beq	.L3959
	ble	.L3959
	add	r6, r8, #15680
	mov	r9, #0
	add	r6, r6, #29
	add	r6, r5, r6, lsl #2
.L3960:
	ldr	r1, [r6, #-4]!
	sub	r8, r8, #1
	ldr	r0, [r7, #2680]
	bl	FreeUsdByDec
	cmp	r8, #0
	str	r9, [r6]
	bne	.L3960
.L3959:
	mov	r0, r5
	mov	r5, #0
	str	r5, [r7, #1392]
	str	r5, [r4, #4020]
	bl	CalcPicNum
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3932:
	cmp	r3, #0
	mov	r0, r5
	ldreq	r3, [fp, #-68]
	sub	r3, r3, #1
	str	r3, [r8, #220]
	bl	FlushDPB
	subs	r3, r0, #0
	bne	.L4029
	ldrb	r3, [r8, #208]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3937
.L3929:
	mov	r0, r5
	bl	DecGap
	cmp	r0, #0
	bne	.L4030
.L3927:
	ldr	r9, [r8, #224]
	b	.L3928
.L4020:
	ldr	r3, [fp, #-56]
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3914
	b	.L3913
.L4028:
	cmp	r8, #0
	beq	.L3954
	ldr	r1, [r7, #1396]
	subs	r8, r8, #1
	stmia	r2, {r1, r3}
	beq	.L3955
	mov	r1, lr
.L3956:
	add	r3, r3, #1
	ldr	ip, [r1, #4]!
	cmp	r3, r8
	str	ip, [r1, #-4]
	bne	.L3956
.L3955:
	add	r3, r8, #15680
	add	r3, r3, #28
	add	r3, r5, r3, lsl #2
	str	r6, [r3, #4]
	str	r8, [r7, #1392]
	b	.L3954
.L3918:
	ldr	r1, .L4033+20
	mov	r0, #22
	bl	dprint_vfmw
	b	.L4012
.L3917:
	ldr	r1, .L4033+20
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	bl	InitDPB
	cmp	r0, #0
	beq	.L3922
.L3961:
	mov	r3, r0
	movw	r2, #6607
	ldr	r1, .L4033+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L4025:
	ldr	r1, [r3, #656]
	mov	r2, #1
	ldr	r0, [r7, #2680]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #3984]
	strb	r6, [r3, #1]
	ldr	r3, [r4, #3984]
	strb	r6, [r3, #4]
	b	.L3912
.L4024:
	ldr	r3, [fp, #-60]
	mov	r2, r3, lsr #4
	ldr	r3, [fp, #-64]
	str	r2, [r10, #1276]
	mov	r3, r3, lsr #4
	str	r3, [r10, #1280]
	b	.L3916
.L3931:
	ldr	r2, [fp, #-68]
	rsb	r1, r9, r3
	ldr	r0, [r6, #484]
	add	r1, r1, r2
	cmp	r0, r1
	bcs	.L3929
	ldrb	r1, [r8, #208]	@ zero_extendqisi2
	cmp	r1, #2
	beq	.L3939
.L3944:
	ldr	r3, [r7, #2676]
	cmp	r3, #0
	bne	.L3929
	mov	r0, r5
	bl	H264_ClearCurrPic
	ldr	r3, .L4033+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4031
.L3945:
	ldr	lr, [r6, #484]
	movw	r2, #6736
.L4014:
	ldr	ip, [r8, #224]
	mov	r0, #0
	ldr	r3, [r8, #220]
	ldr	r1, .L4033+28
	str	lr, [sp]
	rsb	r3, r3, ip
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L4030:
	movw	r2, #6746
	ldr	r1, .L4033+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L3911:
	movw	r3, #6570
	ldr	r2, .L4033+36
	ldr	r1, .L4033+40
	mov	r0, #22
	bl	dprint_vfmw
	add	r7, r5, #61440
	b	.L3912
.L4021:
	ldr	r1, [r2, #656]
	cmp	r1, #0
	bne	.L3930
	ldr	r1, [r2, #664]
	cmp	r1, #0
	bne	.L3930
	ldr	r1, [r2, #620]
	add	r1, r1, #1024
	cmp	r1, #2048
	bhi	.L3929
	b	.L3930
.L4026:
	movw	r2, #6765
	ldr	r1, .L4033+44
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L3939:
	cmp	r3, #0
	mov	r0, r5
	ldreq	r3, [fp, #-68]
	sub	r3, r3, #1
	str	r3, [r8, #220]
	bl	FlushDPB
	subs	r3, r0, #0
	bne	.L4032
	ldrb	r3, [r8, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3929
	b	.L3944
.L4027:
	movw	r3, #6843
	ldr	r2, .L4033+36
	ldr	r1, .L4033+48
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L4023:
	mov	r3, r0
	movw	r2, #6599
	mov	r0, r6
	ldr	r1, .L4033+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L4018:
	movw	r3, #6537
	ldr	r2, .L4033+56
	ldr	r1, .L4033+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L4029:
	movw	r2, #6687
	ldr	r1, .L4033+52
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L4031:
	mov	r0, r5
	bl	ClearDPB
	b	.L3945
.L4022:
	mov	r0, r5
	bl	ClearDPB
	b	.L3938
.L4032:
	mov	r2, #6720
	ldr	r1, .L4033+52
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4007
.L4034:
	.align	2
.L4033:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_apple_airplay_mirrorinig_flag
	.word	.LC397
	.word	.LC401
	.word	.LC402
	.word	.LC404
	.word	.LC396
	.word	.LC398
	.word	.LC399
	.word	.LANCHOR0+340
	.word	.LC395
	.word	.LC400
	.word	.LC403
	.word	.LC361
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	InitPic, .-InitPic
	.align	2
	.global	H264_DecSlice
	.type	H264_DecSlice, %function
H264_DecSlice:
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
	beq	.L4085
	add	r5, r4, #61440
	ldr	r1, .L4093
	mov	r0, #22
	add	r6, r4, #20480
	ldr	r2, [r5, #2624]
	sub	r2, r2, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #368]
	ldr	r2, .L4093+4
	ldrb	r1, [r3, #2]	@ zero_extendqisi2
	strb	r1, [r6, #211]
	ldr	r3, [r3, #76]
	str	r3, [r6, #236]
	ldr	r3, [r5, #2680]
	ldr	r3, [r2, r3, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L4086
.L4038:
	mov	r0, r4
	bl	ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L4084
	mov	r0, r4
	bl	ProcessSliceHeaderSecondPart
	cmp	r0, #0
	bne	.L4084
	ldr	r2, [r5, #2604]
	cmp	r2, #0
	moveq	r3, r2
	beq	.L4044
	add	r9, r4, #61952
	mov	r3, r0
	add	r9, r9, #236
	mov	r1, r0
	mov	r8, r0
	b	.L4052
.L4087:
	cmp	r7, r1
	add	r3, ip, r3
	rsbhi	r0, r0, r10
	rsbhi	r1, r1, r7
	addhi	r0, r1, r0
	movls	r0, r10
	add	r3, r3, r0
.L4050:
	cmp	lr, #0
	add	r8, r8, #1
	moveq	r1, r7
	moveq	r0, r10
	movne	r1, lr
	movne	r0, ip
	cmp	r8, r2
	beq	.L4044
.L4052:
	ldr	ip, [r9, #4]!
	ldr	r7, [ip, #8]
	ldr	lr, [ip, #36]
	cmp	r7, #0
	ldrne	r10, [ip, #12]
	moveq	r10, r7
	cmp	lr, #0
	ldrne	ip, [ip, #40]
	moveq	ip, lr
	cmp	r1, #0
	bne	.L4087
	add	r3, r10, r3
	add	r3, r3, ip
	b	.L4050
.L4044:
	add	r7, r4, #57344
	str	r3, [r5, #2664]
	movw	r0, #1620
	ldr	ip, [r7, #4036]
	ldr	r1, [r7, #4032]
	mul	r1, r1, ip
	cmp	r1, r0
	movgt	r1, r1, asl #8
	ble	.L4088
.L4054:
	add	r8, r4, #12288
	ldr	r0, [r8, #1284]
	cmp	r0, r2
	bls	.L4055
	cmp	r1, r3
	bcc	.L4055
	ldrb	r3, [r6, #213]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4089
.L4058:
	mov	r0, r4
	bl	PicTypeStatistic
	mov	r0, r4
	bl	DecList
	cmp	r0, #0
	bne	.L4090
	mov	r0, r4
	bl	IsRefListWrong
	subs	r6, r0, #0
	bne	.L4091
	mov	r0, r4
	bl	ExitSlice
	mov	r0, r4
	bl	CalcStreamBits
	mov	r0, r4
	bl	WriteSliceMsg
	ldr	r3, [r5, #2660]
	mov	r0, r6
	mov	r2, #1
	add	r3, r3, r2
	str	r2, [r5, #1372]
	str	r3, [r5, #2660]
.L4037:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4088:
	mov	r0, r1, asl #9
	sub	r1, r0, r1, asl #7
	cmp	r1, #16384
	movlt	r1, #16384
	b	.L4054
.L4089:
	ldr	r1, .L4093+8
	mov	r0, #2
	bl	dprint_vfmw
	ldrb	r3, [r6, #211]	@ zero_extendqisi2
	mov	r2, #0
	str	r2, [r5, #2660]
	cmp	r3, #5
	ldr	r3, [r5, #2644]
	mov	r0, r4
	streq	r3, [r5, #2656]
	add	r3, r3, #1
	str	r3, [r5, #2644]
	ldrb	r3, [r7, #3331]	@ zero_extendqisi2
	cmp	r3, r2
	ldreq	r3, [r5, #2648]
	ldrne	r3, [r5, #2652]
	addeq	r3, r3, #1
	addne	r3, r3, #1
	streq	r3, [r5, #2648]
	strne	r3, [r5, #2652]
	bl	InitPic
	cmn	r0, #2
	beq	.L4037
	cmp	r0, #0
	bne	.L4092
	mov	r0, r4
	bl	WritePicMsg
	b	.L4058
.L4086:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L4038
	ldr	r3, [r3, #164]
	cmp	r3, #2
	bne	.L4038
	mov	r0, r4
	bl	H264_Get_Last_IDR_Frame_Info
	b	.L4038
.L4084:
	ldr	r1, .L4093+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4093+16
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L4082
	sub	r2, fp, #44
	mvn	r1, #0
	ldr	r0, [r5, #2680]
	mov	r3, #4
	str	r1, [r2, #-8]!
	mov	r1, #100
	blx	r6
.L4082:
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	b	.L4037
.L4055:
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L4093+20
	bl	dprint_vfmw
	ldr	r2, [r8, #1284]
	ldr	r3, [r5, #2604]
	cmp	r3, r2
	bcc	.L4057
	ldr	r1, .L4093+16
	ldr	r6, [r1]
	cmp	r6, #0
	beq	.L4057
	str	r3, [fp, #-52]
	mov	r1, #108
	str	r2, [fp, #-48]
	mov	r3, #8
	sub	r2, fp, #52
	ldr	r0, [r5, #2680]
	blx	r6
.L4057:
	ldr	r1, .L4093+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	H264_ClearCurrPic
	mvn	r0, #0
	b	.L4037
.L4090:
	mov	r2, r0
	ldr	r1, .L4093+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4037
.L4091:
	ldr	r2, [r7, #4004]
	mov	r0, #1
	ldr	r1, .L4093+32
	bl	dprint_vfmw
	b	.L4082
.L4092:
	ldr	r1, .L4093+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4037
.L4085:
	movw	r3, #9000
	ldr	r2, .L4093+40
	ldr	r1, .L4093+44
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4037
.L4094:
	.align	2
.L4093:
	.word	.LC346
	.word	s_pstVfmwChan
	.word	.LC407
	.word	.LC347
	.word	g_event_report
	.word	.LC405
	.word	.LC406
	.word	.LC409
	.word	.LC410
	.word	.LC408
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264_DecSlice, .-H264_DecSlice
	.align	2
	.global	H264_DecOneNal
	.type	H264_DecOneNal, %function
H264_DecOneNal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r5, r0, #0
	mov	r6, r1
	beq	.L4231
	ldr	ip, [r5, #368]
	add	r4, r5, #61440
	ldr	r3, [ip, #68]
	cmp	r3, #0
	movne	r1, ip
	movne	r2, #0
	ldrne	r3, [r4, #2664]
	beq	.L4102
.L4101:
	ldr	r0, [r1, #12]
	add	r2, r2, #1
	add	r1, r1, #28
	add	r3, r3, r0
	str	r3, [r4, #2664]
	ldr	r0, [ip, #68]
	cmp	r0, r2
	bhi	.L4101
.L4102:
	mov	r2, #0
	ldr	r3, .L4254
	strb	r2, [ip]
	ldr	r2, [r4, #2680]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L4247
.L4100:
	add	r8, r5, #13504
	mov	r1, #32
	add	r8, r8, #24
	mov	r0, r8
	bl	BsGet
	ldr	r2, [r5, #368]
	ldr	r3, [r2, #64]
	add	r3, r3, #32
	str	r3, [r2, #64]
	mov	r7, r0
.L4103:
	ldr	r0, [r5, #368]
	and	r1, r7, #31
	ubfx	r2, r7, #5, #2
	ubfx	r3, r7, #7, #1
	mov	ip, #0
	strb	r1, [r0, #2]
	mov	r0, #22
	ldr	lr, [r5, #368]
	ldr	r1, .L4254+4
	str	r2, [lr, #76]
	ldr	r2, [r5, #368]
	str	r3, [r2, #80]
	str	ip, [r4, #2620]
	ldr	r3, [r5, #368]
	ldr	r2, [r4, #2624]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r3, [r4, #2624]
	movw	r2, #371
	cmp	r3, r2
	beq	.L4248
.L4104:
	add	r3, r3, #1
	str	r3, [r4, #2624]
	ldr	r3, [r5, #368]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #20
	beq	.L4249
.L4105:
	sub	r3, r2, #1
	cmp	r3, #29
	ldrls	pc, [pc, r3, asl #2]
	b	.L4112
.L4114:
	.word	.L4113
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4113
	.word	.L4115
	.word	.L4116
	.word	.L4117
	.word	.L4118
	.word	.L4119
	.word	.L4120
	.word	.L4121
	.word	.L4122
	.word	.L4112
	.word	.L4116
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4123
	.word	.L4113
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4112
	.word	.L4124
.L4247:
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L4100
	ldr	r2, [r3, #164]
	cmp	r2, #2
	bne	.L4100
	ldr	r3, [r3, #156]
	cmp	r6, #0
	cmpeq	r3, #1
	bne	.L4100
	add	r8, r5, #13504
	mov	r1, #40
	add	r8, r8, #24
	mov	r0, r8
	bl	BsSkip
	mov	r0, r8
	mov	r1, #8
	bl	BsGet
	ldr	r2, [r5, #368]
	ldr	r3, [r2, #64]
	add	r3, r3, #48
	str	r3, [r2, #64]
	mov	r7, r0
	b	.L4103
.L4113:
	ldr	r3, [r4, #2636]
	mov	r0, #22
	ldr	r1, .L4254+8
	bl	dprint_vfmw
	ldr	r2, [r5, #368]
	add	r3, r5, #20480
	mov	r0, r5
	ldrb	r1, [r2, #2]	@ zero_extendqisi2
	strb	r1, [r3, #211]
	ldr	r2, [r2, #76]
	str	r2, [r3, #236]
	bl	SliceCheck
	subs	r6, r0, #0
	bne	.L4250
	mov	r0, r5
	bl	H264_DecSlice
	cmn	r0, #2
	beq	.L4097
	cmp	r0, #0
	beq	.L4232
	ldr	r3, .L4254+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4231
	ldr	r0, [r4, #2680]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4097
.L4115:
	ldr	r1, .L4254+16
	mov	r2, #6
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	bl	H264_DecSEI
	ldr	r1, [r5, #368]
	cmp	r1, #0
	mov	r6, r0
	beq	.L4131
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r5, #368]
.L4131:
	cmp	r6, #0
	bne	.L4251
.L4232:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4116:
	ldr	r1, .L4254+20
	mov	r0, #22
	ldr	r3, [r4, #2628]
	bl	dprint_vfmw
	mov	r0, r5
	bl	H264_DecSPS
	ldr	r1, [r5, #368]
	cmp	r1, #0
	mov	r6, r0
	beq	.L4129
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r5, #368]
.L4129:
	cmp	r6, #0
	bne	.L4252
	ldr	r3, [r4, #2628]
	mov	r0, r6
	add	r3, r3, #1
	str	r3, [r4, #2628]
	b	.L4097
.L4118:
	ldr	r1, .L4254+24
	mov	r2, #9
.L4242:
	mov	r0, #22
	bl	dprint_vfmw
.L4240:
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L4232
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r5, #368]
.L4097:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4119:
	mov	r2, #10
	ldr	r1, .L4254+28
	b	.L4242
.L4117:
	ldr	r1, .L4254+32
	mov	r2, #8
	ldr	r3, [r4, #2632]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	bl	H264_DecPPS
	ldr	r1, [r5, #368]
	cmp	r1, #0
	mov	r6, r0
	beq	.L4127
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r5, #368]
.L4127:
	cmp	r6, #0
	bne	.L4253
	ldr	r3, [r4, #2632]
	mov	r0, r6
	add	r3, r3, #1
	str	r3, [r4, #2632]
	b	.L4097
.L4120:
	mov	r2, #11
	ldr	r1, .L4254+36
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	bl	H264_IsEosNal
	cmp	r0, #1
	bne	.L4240
	ldr	r6, .L4254+12
	add	r3, r5, #12288
	strb	r0, [r3, #1272]
	ldr	r7, [r6]
	cmp	r7, #0
	beq	.L4134
	mov	r3, #0
	mov	r1, #117
	mov	r2, r3
	ldr	r0, [r4, #2680]
	blx	r7
.L4134:
	mov	r7, #0
	mov	r0, r5
	str	r7, [r5, #364]
	bl	DecVDM
	cmp	r0, r7
	beq	.L4240
	ldr	r1, [r5, #368]
	cmp	r1, r7
	beq	.L4135
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	str	r7, [r5, #368]
.L4135:
	ldr	r5, [r6]
	cmp	r5, #0
	bne	.L4235
.L4231:
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4121:
	mov	r2, #12
	ldr	r1, .L4254+40
	b	.L4242
.L4122:
	mov	r2, #13
	ldr	r1, .L4254+44
	b	.L4242
.L4123:
	mov	r2, #19
	ldr	r1, .L4254+48
	b	.L4242
.L4124:
	mov	r2, #30
	ldr	r1, .L4254+52
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r6, #0
	bne	.L4136
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L4136
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	str	r6, [r5, #368]
.L4136:
	mov	r1, #32
	mov	r0, r8
	bl	BsGet
	mov	r1, #32
	mov	r6, r0
	mov	r0, r8
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r6, r3
	bne	.L4232
	ldr	r6, .L4254+12
	ldr	r7, [r6]
	cmp	r7, #0
	beq	.L4137
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #2680]
	blx	r7
.L4137:
	mov	r7, #0
	mov	r0, r5
	str	r7, [r5, #364]
	bl	DecVDM
	cmp	r0, r7
	beq	.L4232
	ldr	r5, [r6]
	cmp	r5, r7
	beq	.L4231
	ldr	r0, [r4, #2680]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #113
	blx	r5
	b	.L4231
.L4112:
	mov	r3, r7
	ldr	r1, .L4254+56
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r5, #368]
	ldr	r1, .L4254+60
	mov	r0, #0
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L4138
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r5, #368]
.L4138:
	ldr	r3, .L4254+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4232
.L4236:
	mov	r3, #0
	ldr	r0, [r4, #2680]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L4232
.L4248:
	ldr	r1, .L4254+64
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r4, #2624]
	b	.L4104
.L4249:
	mov	r1, #24
	mov	r0, r8
	bl	BsGet
	ldr	r3, [r5, #368]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #3]
	ldr	r1, [r5, #368]
	mov	r7, r0
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4106
	ldrb	r2, [r4, #744]	@ zero_extendqisi2
	ldrb	r3, [r4, #742]	@ zero_extendqisi2
.L4107:
	cmp	r2, #0
	bne	.L4108
	cmp	r3, #1
	beq	.L4109
.L4108:
	ldr	r1, .L4254+68
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L4231
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r5, #368]
	b	.L4097
.L4106:
	ubfx	r3, r0, #22, #1
	ubfx	r2, r0, #16, #6
	ubfx	ip, r7, #4, #1
	strb	r3, [r4, #740]
	strb	r2, [r4, #741]
	ubfx	r3, r0, #15, #1
	ubfx	r2, r7, #8, #4
	ubfx	r0, r0, #12, #3
	strb	ip, [r4, #746]
	ubfx	ip, r7, #2, #1
	strb	r0, [r4, #743]
	ubfx	r0, r7, #5, #3
	strb	r3, [r4, #742]
	strb	r0, [r4, #745]
	ubfx	r0, r7, #3, #1
	strb	r2, [r4, #744]
	strb	r0, [r4, #747]
	and	r0, r7, #3
	strb	ip, [r4, #748]
	strb	r0, [r4, #749]
	b	.L4107
.L4250:
	ldr	r1, .L4254+72
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	bl	ClearCurrSlice
	ldr	r3, .L4254+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4231
.L4235:
	mov	r3, #0
	ldr	r0, [r4, #2680]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4097
.L4253:
	ldr	r5, .L4254+12
	mov	r0, #1
	ldr	r2, .L4254+76
	ldr	r1, .L4254+80
	bl	dprint_vfmw
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4231
.L4238:
	sub	r2, fp, #36
	mvn	r7, #0
	mov	r3, #4
	mov	r1, #100
	str	r7, [r2, #-4]!
	ldr	r0, [r4, #2680]
	blx	r6
	ldr	r5, [r5]
	cmp	r5, #0
	bne	.L4235
	b	.L4231
.L4252:
	ldr	r5, .L4254+12
	mov	r0, #1
	ldr	r1, .L4254+84
	bl	dprint_vfmw
	ldr	r6, [r5]
	cmp	r6, #0
	bne	.L4238
	b	.L4231
.L4251:
	ldr	r1, .L4254+88
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4254+12
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L4236
	b	.L4232
.L4109:
	ldrb	r3, [r4, #740]	@ zero_extendqisi2
	mov	r0, #22
	cmp	r3, #1
	moveq	r3, #5
	streqb	r3, [r1, #2]
	ldrb	ip, [r4, #745]	@ zero_extendqisi2
	ldreqb	r2, [r4, #744]	@ zero_extendqisi2
	ldrb	r3, [r4, #743]	@ zero_extendqisi2
	ldr	r1, .L4254+92
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L4254+96
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r5, #368]
	ldr	r3, [r2, #64]
	add	r3, r3, #24
	str	r3, [r2, #64]
	ldr	r3, [r5, #368]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	b	.L4105
.L4255:
	.align	2
.L4254:
	.word	s_pstVfmwChan
	.word	.LC411
	.word	.LC416
	.word	g_event_report
	.word	.LC422
	.word	.LC420
	.word	.LC424
	.word	.LC425
	.word	.LC418
	.word	.LC427
	.word	.LC426
	.word	.LC428
	.word	.LC429
	.word	.LC430
	.word	.LC431
	.word	.LC432
	.word	.LC412
	.word	.LC413
	.word	.LC417
	.word	.LANCHOR0+348
	.word	.LC419
	.word	.LC421
	.word	.LC423
	.word	.LC414
	.word	.LC415
	UNWIND(.fnend)
	.size	H264_DecOneNal, .-H264_DecOneNal
	.align	2
	.global	H264DEC_DecodePacket
	.type	H264DEC_DecodePacket, %function
H264DEC_DecodePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r5, r0, #0
	mov	r2, #0
	str	r2, [fp, #-48]
	str	r2, [fp, #-52]
	str	r2, [fp, #-56]
	beq	.L4314
	cmp	r1, #0
	beq	.L4315
	ldr	r0, [r5]
	add	r4, r5, #61440
	ldr	ip, [r4, #1376]
	ldr	r3, [r0, #8]
	cmp	ip, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r4, #2668]
	ldr	r3, [r0]
	str	r3, [r4, #2672]
	ldr	r3, [r0, #4]
	str	r2, [r4, #2620]
	str	r3, [r4, #2676]
	beq	.L4260
	ldr	r3, [r0, #872]
	cmp	r3, #1
	beq	.L4316
.L4261:
	mov	r0, r5
	bl	ReceivePacket
	ldr	r3, [r5, #368]
	str	r3, [r4, #2716]
.L4263:
	cmp	r0, #0
	mov	r0, #0
	str	r0, [r4, #1376]
	beq	.L4317
.L4312:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4316:
	ldr	r3, [r0, #920]
	cmp	r3, #1
	bne	.L4261
	ldr	r3, [r4, #2712]
	cmp	r3, #1
	bne	.L4261
	ldr	r3, [r4, #2716]
	str	r3, [r5, #368]
	str	r2, [r4, #2712]
	str	r2, [r4, #1376]
	b	.L4262
.L4317:
	ldr	r3, [r5, #368]
.L4262:
	mov	r2, #0
	add	r6, r5, #13504
	str	r2, [r3, #64]
	add	r6, r6, #24
	ldr	r3, [r5, #368]
	mov	r0, r6
	ldr	r2, [r3, #12]
	ldr	r1, [r3, #8]
	bl	BsInit
	ldr	r3, .L4325
	ldr	r2, [r4, #2680]
	ldr	ip, [r3, r2, asl #2]
	ldrsb	r7, [ip, #44]
	cmp	r7, #1
	beq	.L4264
.L4266:
	mov	r7, #0
.L4265:
	mov	r1, #32
	mov	r0, r6
	bl	BsGet
	ldr	r2, [r5, #368]
	uxtb	r0, r0
	and	r3, r0, #31
	and	r1, r0, #27
	strb	r3, [r2, #2]
	sub	ip, r3, #20
	ldr	r2, [r5, #368]
	clz	ip, ip
	cmp	r3, #20
	cmpne	r1, #1
	ubfx	r0, r0, #5, #2
	mov	ip, ip, lsr #5
	str	r0, [r2, #76]
	beq	.L4318
.L4267:
	mov	r0, r5
	bl	FindTrailZeros
	subs	r3, r0, #0
	bne	.L4319
	ldr	r2, [r5, #368]
	mov	r0, r6
	str	r3, [r2, #64]
	ldr	r3, [r5, #368]
	ldr	r1, [r3, #8]
	ldr	r2, [r3, #12]
	bl	BsInit
	mov	r1, r7
	mov	r0, r5
	bl	H264_DecOneNal
	cmn	r0, #2
	mov	r3, r0
	beq	.L4312
	cmp	r3, #0
	addeq	r5, r5, #57344
	moveq	r0, r3
	streq	r3, [r5, #4060]
	beq	.L4312
	ldr	r1, .L4325+4
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4312
.L4260:
	ldr	r0, [r5, #368]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	b	.L4263
.L4318:
	cmp	ip, #0
	bne	.L4320
.L4268:
	sub	r2, fp, #40
	sub	r1, fp, #44
	mov	r0, r5
	bl	InquireSliceProperty
	cmp	r0, #0
	beq	.L4321
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L4279
	ldr	r0, [r4, #2680]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r5, #368]
.L4279:
	ldr	r3, .L4325+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4313
	mov	r3, #0
	ldr	r0, [r4, #2680]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4312
.L4321:
	ldr	r2, [fp, #-44]
	ldr	r1, [r4, #2692]
	sub	r3, r2, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	cmp	r3, #0
	add	r3, r3, r1
	str	r3, [r4, #2692]
	bne	.L4322
.L4270:
	ldr	r3, [fp, #-40]
	cmp	r3, #1
	bne	.L4267
	mov	r0, r5
	bl	FlushDPB
	subs	r3, r0, #0
	bne	.L4323
.L4277:
	ldr	r0, [r4, #2680]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L4267
	sub	r3, fp, #48
	sub	r2, fp, #52
	sub	r1, fp, #56
	ldr	r0, [r4, #2680]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r5]
	ldr	r3, [r3, #732]
	cmp	r3, #1
	bne	.L4267
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ble	.L4324
.L4274:
	mov	r3, #1
	mvn	r0, #1
	str	r3, [r4, #1376]
	b	.L4312
.L4264:
	ldr	r3, [ip, #164]
	mov	r0, r5
	ldr	r2, [ip, #160]
	ldr	r1, [ip, #156]
	bl	H264_VES_Splitter
	cmp	r0, #3
	beq	.L4265
	cmp	r0, #0
	bne	.L4312
	b	.L4266
.L4320:
	mov	r0, r5
	bl	InquireSliceExtProperty
	b	.L4268
.L4319:
	ldr	r1, .L4325+12
	mov	r0, #22
	bl	dprint_vfmw
.L4313:
	mvn	r0, #0
	b	.L4312
.L4322:
	add	r8, r5, #20480
	ldrb	r3, [r8, #209]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #2696]
	addeq	r3, r3, #1
	addne	r3, r3, #2
	str	r3, [r4, #2696]
	ldr	r3, [r4, #2604]
	cmp	r3, #0
	beq	.L4270
	ldr	r3, [r5, #368]
	mov	ip, #0
	mov	r0, r6
	mov	r2, #20
	ldr	r1, .L4325+16
	str	ip, [r3, #64]
	bl	BsInit
	mov	r0, r5
	mov	r1, #1
	bl	H264_DecOneNal
	ldrb	r3, [r8, #209]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #2696]
	subeq	r3, r3, #1
	subne	r3, r3, #2
	str	r3, [r4, #2696]
	b	.L4274
.L4323:
	movw	r2, #13318
	ldr	r1, .L4325+20
	mov	r0, #0
	bl	dprint_vfmw
	b	.L4277
.L4314:
	movw	r3, #13197
	ldr	r2, .L4325+24
	ldr	r1, .L4325+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4312
.L4315:
	mov	r0, r1
	movw	r3, #13198
	ldr	r2, .L4325+24
	ldr	r1, .L4325+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4312
.L4324:
	ldr	r3, [fp, #-52]
	cmp	r3, #32
	bgt	.L4274
	ldr	r3, [r5, #360]
	cmp	r3, #0
	bne	.L4274
	ldr	r3, [r4, #2644]
	cmp	r3, #0
	beq	.L4267
	add	r2, r5, #12288
	ldr	r3, [r2, #1276]
	cmp	r3, #0
	beq	.L4267
	ldr	r2, [r2, #1280]
	ldr	r1, [r4, #2720]
	cmp	r2, r1
	beq	.L4267
	ldr	r1, [r4, #2724]
	cmp	r3, r1
	beq	.L4267
	ldr	r1, .L4325+8
	str	r2, [r4, #2720]
	str	r3, [r4, #2724]
	ldr	r8, [r1]
	cmp	r8, #0
	beq	.L4267
	mov	r3, #0
	ldr	r0, [r4, #2680]
	mov	r2, r3
	mov	r1, #120
	blx	r8
	b	.L4267
.L4326:
	.align	2
.L4325:
	.word	s_pstVfmwChan
	.word	.LC434
	.word	g_event_report
	.word	.LC433
	.word	.LANCHOR1+432
	.word	.LC361
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264DEC_DecodePacket, .-H264DEC_DecodePacket
	.align	2
	.global	H264DEC_GetRemainImg
	.type	H264DEC_GetRemainImg, %function
H264DEC_GetRemainImg:
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
	subs	r4, r0, #0
	beq	.L4328
	add	r5, r4, #24576
	ldr	r3, [r5, #2140]
	cmp	r3, #0
	addne	r7, r4, #26368
	movne	r6, #0
	addne	r7, r7, #148
	bne	.L4333
	b	.L4330
.L4332:
	ldr	r3, [r5, #2140]
	cmp	r3, r6
	bls	.L4330
.L4333:
	ldr	r1, [r7, #4]!
	add	r6, r6, #1
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4332
	mov	r0, r4
	bl	UnMarkFrameStoreRef
	ldr	r3, [r5, #2140]
	cmp	r3, r6
	bhi	.L4333
.L4330:
	mov	r0, r4
	bl	RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L4330
	mvn	r6, #0
.L4335:
	ldr	r3, [r5, #2140]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	beq	.L4344
	bl	GetMinPOC
	ldr	r3, [fp, #-36]
	mov	r1, #0
	mov	r0, r4
	add	r3, r4, r3, lsl #2
	add	r3, r3, #24576
	ldr	r2, [r3, #1944]
	strb	r1, [r2, #4]
	ldr	r1, [r3, #1944]
	ldr	r2, [r5, #2140]
	bl	OutputFrmToVO
	ldr	r1, [fp, #-36]
	add	r3, r1, #6592
	add	r3, r3, #38
	ldr	r3, [r4, r3, asl #2]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r6, r0
	bne	.L4335
	mov	r0, r4
	bl	RemoveFrameStoreOutDPB
	b	.L4335
.L4344:
	cmp	r6, #0
	moveq	r0, r6
	bne	.L4345
.L4331:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4345:
	add	r0, r4, #8
	bl	GetVoLastImageID
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4328:
	movw	r3, #3256
	ldr	r2, .L4346
	ldr	r1, .L4346+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4331
.L4347:
	.align	2
.L4346:
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264DEC_GetRemainImg, .-H264DEC_GetRemainImg
	.align	2
	.global	H264DEC_VDMPostProc
	.type	H264DEC_VDMPostProc, %function
H264DEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 8
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
	mov	r9, r3
	beq	.L4380
	add	r6, r4, #57344
	ldr	r3, [r6, #3984]
	cmp	r3, #0
	beq	.L4381
	ldr	r2, [r4, #360]
	ldr	lr, [r4]
	ldrb	ip, [r2, #17]	@ zero_extendqisi2
	ldr	r5, [lr, #644]
	strb	ip, [r3, #5]
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	str	r2, [r3, #8]
	ldr	r7, [r4, #364]
	cmp	r7, #0
	bne	.L4352
	ldr	r3, [fp, #4]
	str	r1, [r6, #4028]
	cmp	r3, #0
	beq	.L4353
	ldr	r3, [fp, #8]
	ldr	r1, [fp, #8]
	ldr	r2, .L4386
	mov	r3, r3, asl #6
	sub	r3, r3, r1, asl #3
	add	r3, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L4382
	cmp	r3, #1
	beq	.L4353
	cmp	r5, #1
	beq	.L4383
.L4356:
	mov	r1, r9
	mov	r0, r4
	bl	StorePicInDPB
	cmp	r0, #1
	mov	r5, r0
	bls	.L4366
	ldr	r3, [r6, #3984]
	add	r1, r4, #61440
	mov	r2, #1
	mvn	r7, #0
	ldr	r0, [r1, #2680]
	ldr	r1, [r3, #656]
	bl	FSP_ClearLogicFs
	mov	r2, r5
	ldr	r1, .L4386+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	H264_ClearCurrPic
	mov	r0, r4
	bl	ClearDPB
	mov	r3, #0
	str	r3, [r6, #3984]
.L4350:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4353:
	mov	r0, r4
	bl	ClearAllSlice
	cmp	r5, #1
	bne	.L4356
.L4383:
	ldr	r5, [r4, #360]
	ldr	r3, [r5, #316]
	add	r3, r3, #146
	ldr	r8, [r5, r3, asl #2]
	mov	r0, r8
	bl	MEM_Phy2Vir
	ldr	r2, [r5, #36]
	mov	r1, r8
	ldr	r8, [r5, #44]
	ldr	r3, .L4386+8
	mul	r8, r8, r2
	ldr	r3, [r3, #140]
	mov	r2, r8, asl #2
	mov	r10, r0
	blx	r3
	cmp	r8, #0
	beq	.L4369
	mov	r0, #0
	sub	lr, r10, #4
	str	r7, [fp, #-48]
	mov	r3, r0
	mov	ip, r0
	mvn	r5, #-2147483648
	mov	r7, r0
.L4363:
	ldr	r2, [lr, #4]!
	add	ip, ip, #1
	ubfx	r10, r2, #0, #14
	tst	r2, #8192
	ubfx	r1, r2, #0, #13
	rsb	r10, r10, #0
	mov	r2, r2, asr #14
	ubfxne	r1, r10, #0, #13
	ubfx	r10, r2, #0, #12
	tst	r2, #2048
	rsb	r10, r10, #0
	ubfx	r2, r2, #0, #11
	ubfxne	r2, r10, #0, #11
	add	r2, r1, r2
	cmp	r5, r2
	add	r0, r0, r2
	movge	r5, r2
	cmp	r3, r2
	movlt	r3, r2
	cmp	r2, #0
	addeq	r7, r7, #1
	cmp	ip, r8
	bne	.L4363
	mov	r2, r7
	mov	r10, #100
	mul	r2, r10, r2
	ldr	r7, [fp, #-48]
	str	r2, [fp, #-48]
.L4357:
	mov	r1, r8
	str	r3, [fp, #-52]
	bl	__aeabi_uidiv
	mov	r1, r8
	mov	r10, r0
	ldr	r0, [fp, #-48]
	bl	__aeabi_uidiv
	ldr	ip, [r6, #3984]
	cmp	r0, #100
	moveq	r5, #0
	cmp	ip, #0
	beq	.L4365
	ldr	r1, [ip, #260]
	ldr	r3, [fp, #-52]
	cmp	r1, r3
	movcc	r1, r3
	str	r1, [ip, #260]
	ldr	r1, [r6, #3984]
	ldr	r3, [r1, #264]
	cmp	r3, r5
	movcc	r3, r5
	str	r3, [r1, #264]
	ldr	r3, [r6, #3984]
	str	r10, [r3, #268]
	ldr	r3, [r6, #3984]
	str	r0, [r3, #272]
	ldr	r3, [r6, #3984]
	ldr	r1, [r3, #260]
	str	r1, [r6, #3588]
	ldr	r1, [r3, #264]
	str	r10, [r6, #3596]
	str	r1, [r6, #3592]
	ldr	r3, [r3, #272]
	str	r3, [r6, #3600]
	b	.L4356
.L4352:
	str	r1, [r6, #4028]
	bl	ClearAllSlice
	mov	r1, r9
	mov	r0, r4
	bl	StorePicInDPB
	subs	r2, r0, #0
	bne	.L4384
.L4367:
	mov	r0, r4
	bl	FlushDPB
	subs	r2, r0, #0
	bne	.L4385
.L4368:
	add	r1, r4, #61440
	add	r2, r4, #12288
	mov	r3, #0
	add	r4, r4, #20480
	str	r3, [r1, #1372]
	mov	r7, r3
	ldr	r1, [r2, #1292]
	movw	r2, #23352
	strb	r3, [r4, #1848]
	movt	r2, 1
	str	r3, [r4, #1880]
	mov	lr, #2
	str	r1, [r4, #1856]
	mov	ip, #7
	str	r3, [r4, #1884]
	mov	r0, #32
	str	r2, [r4, #1864]
	mov	r1, #3
	mvn	r2, #0
	mov	r3, #262144
	strb	r0, [r4, #1850]
	mov	r0, r7
	strb	lr, [r4, #1849]
	str	ip, [r4, #1860]
	str	r1, [r4, #1872]
	str	r2, [r4, #1876]
	str	r3, [r4, #1888]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4385:
	ldr	r1, .L4386+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4368
.L4384:
	ldr	r1, .L4386+16
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4367
.L4366:
	add	r4, r4, #61440
	mov	r3, #1
	mov	r0, r7
	str	r3, [r4, #1372]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4380:
	movw	r3, #13467
	ldr	r2, .L4386+20
	ldr	r1, .L4386+24
	mvn	r7, #0
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4381:
	mov	r0, r3
	ldr	r2, .L4386+20
	movw	r3, #13468
	ldr	r1, .L4386+24
	bl	dprint_vfmw
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4382:
	bl	ClearAllSlice
	b	.L4350
.L4365:
	mov	r0, ip
	ldr	r1, .L4386+28
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L4350
.L4369:
	str	r8, [fp, #-48]
	mov	r0, r8
	mvn	r5, #-2147483648
	mov	r3, r8
	b	.L4357
.L4387:
	.align	2
.L4386:
	.word	g_VdmDrvParam+40
	.word	.LC436
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC438
	.word	.LC437
	.word	.LC8
	.word	.LC9
	.word	.LC435
	UNWIND(.fnend)
	.size	H264DEC_VDMPostProc, .-H264DEC_VDMPostProc
	.align	2
	.global	H264DEC_GetImageBuffer
	.type	H264DEC_GetImageBuffer, %function
H264DEC_GetImageBuffer:
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
	subs	r6, r0, #0
	beq	.L4430
	add	r5, r6, #61440
	ldr	r7, [r5, #1364]
	cmp	r7, #0
	beq	.L4392
	add	r3, r6, #57344
	ldrb	r3, [r3, #3328]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4392
	add	r4, r6, #27392
	add	r9, r6, #26368
	add	r9, r9, #152
	add	r8, r6, #24576
	mov	r0, r4
	mov	lr, #0
.L4398:
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4393
	cmp	r0, #0
	beq	.L4394
	ldr	ip, [r8, #2140]
	cmp	ip, #0
	beq	.L4394
	ldr	r2, [r8, #1944]
	cmp	r2, r0
	beq	.L4393
	mov	r2, r9
	b	.L4395
.L4396:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L4393
.L4395:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L4396
.L4394:
	ldr	r0, [r5, #2680]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L4392
	cmn	r0, #1
	beq	.L4431
.L4428:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4392:
	mov	r0, #1
.L4426:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4393:
	add	lr, lr, #1
	add	r0, r0, #832
	cmp	lr, r7
	bne	.L4398
	sub	r2, fp, #40
	sub	r1, fp, #44
	add	r0, r6, #8
	bl	GetQueueImgNum
	ldr	r1, .L4433
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, .L4433+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r5, #1364]
	cmp	r3, #0
	addne	r9, r6, #26368
	addne	r8, r6, #24576
	addne	r9, r9, #152
	movne	r7, #0
	beq	.L4432
.L4399:
	cmp	r4, #0
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	ldrb	lr, [r4, #4]	@ zero_extendqisi2
	beq	.L4409
	ldr	ip, [r8, #2140]
	cmp	ip, #0
	beq	.L4409
	ldr	r2, [r8, #1944]
	cmp	r4, r2
	beq	.L4411
	mov	r1, r9
	mov	r2, #0
	b	.L4403
.L4404:
	ldr	r0, [r1, #4]!
	cmp	r4, r0
	beq	.L4411
.L4403:
	add	r2, r2, #1
	cmp	r2, ip
	bne	.L4404
.L4409:
	mov	r2, #1
.L4402:
	str	r2, [sp, #4]
	mov	r0, #0
	mov	r2, r7
	str	lr, [sp]
	ldr	r1, .L4433+8
	add	r7, r7, #1
	bl	dprint_vfmw
	ldr	r3, [r5, #1364]
	add	r4, r4, #832
	cmp	r3, r7
	bhi	.L4399
.L4405:
	ldr	r3, [fp, #-40]
	mov	r0, #0
	ldr	r2, [fp, #-44]
	ldr	r1, .L4433+12
	bl	dprint_vfmw
	ldr	r3, [r5, #1364]
	ldr	r0, [r8, #2140]
	ldr	r2, [fp, #-44]
	sub	r3, r3, #2
	ldr	r1, [fp, #-40]
	rsb	r3, r0, r3
	add	r2, r2, r1
	cmp	r2, r3
	bge	.L4428
	ldr	r1, .L4433+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	mov	r1, #1
	bl	ClearAll
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4411:
	mov	r2, #0
	b	.L4402
.L4431:
	add	r1, r6, #8
	ldr	r0, [r5, #2680]
	bl	FSP_ClearNotInVoQueue
	b	.L4428
.L4432:
	add	r8, r6, #24576
	b	.L4405
.L4430:
	movw	r3, #13702
	ldr	r2, .L4433+20
	ldr	r1, .L4433+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4426
.L4434:
	.align	2
.L4433:
	.word	.LC439
	.word	.LC440
	.word	.LC442
	.word	.LC441
	.word	.LC443
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	H264DEC_GetImageBuffer, .-H264DEC_GetImageBuffer
	.global	TmpBuf
	.global	g_CabacMN
	.global	quant8_org
	.global	quant_org
	.global	quant8_inter_default
	.global	quant8_intra_default
	.global	quant_inter_default
	.global	quant_intra_default
	.global	g_ZZ_SCAN8
	.global	g_ZZ_SCAN
	.global	CalcZeroNum
	.global	g_AspecRatioIdc
	.global	g_NalTypeEOPIC
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.13630, %object
	.size	__func__.13630, 23
__func__.13630:
	.ascii	"RemoveFrameStoreOutDPB\000"
	.space	1
	.type	g_ZZ_SCAN, %object
	.size	g_ZZ_SCAN, 16
g_ZZ_SCAN:
	.byte	0
	.byte	1
	.byte	4
	.byte	8
	.byte	5
	.byte	2
	.byte	3
	.byte	6
	.byte	9
	.byte	12
	.byte	13
	.byte	10
	.byte	7
	.byte	11
	.byte	14
	.byte	15
	.type	g_ZZ_SCAN8, %object
	.size	g_ZZ_SCAN8, 64
g_ZZ_SCAN8:
	.byte	0
	.byte	1
	.byte	8
	.byte	16
	.byte	9
	.byte	2
	.byte	3
	.byte	10
	.byte	17
	.byte	24
	.byte	32
	.byte	25
	.byte	18
	.byte	11
	.byte	4
	.byte	5
	.byte	12
	.byte	19
	.byte	26
	.byte	33
	.byte	40
	.byte	48
	.byte	41
	.byte	34
	.byte	27
	.byte	20
	.byte	13
	.byte	6
	.byte	7
	.byte	14
	.byte	21
	.byte	28
	.byte	35
	.byte	42
	.byte	49
	.byte	56
	.byte	57
	.byte	50
	.byte	43
	.byte	36
	.byte	29
	.byte	22
	.byte	15
	.byte	23
	.byte	30
	.byte	37
	.byte	44
	.byte	51
	.byte	58
	.byte	59
	.byte	52
	.byte	45
	.byte	38
	.byte	31
	.byte	39
	.byte	46
	.byte	53
	.byte	60
	.byte	61
	.byte	54
	.byte	47
	.byte	55
	.byte	62
	.byte	63
	.type	__func__.14908, %object
	.size	__func__.14908, 12
__func__.14908:
	.ascii	"H264_DecPPS\000"
	.type	SarTable.14955, %object
	.size	SarTable.14955, 136
SarTable.14955:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	12
	.word	11
	.word	10
	.word	11
	.word	16
	.word	11
	.word	40
	.word	33
	.word	24
	.word	11
	.word	20
	.word	11
	.word	32
	.word	11
	.word	80
	.word	33
	.word	18
	.word	11
	.word	15
	.word	11
	.word	64
	.word	33
	.word	160
	.word	99
	.word	4
	.word	3
	.word	3
	.word	2
	.word	2
	.word	1
	.type	__func__.15108, %object
	.size	__func__.15108, 12
__func__.15108:
	.ascii	"H264_DecSEI\000"
	.type	__func__.13928, %object
	.size	__func__.13928, 8
__func__.13928:
	.ascii	"InitDPB\000"
	.type	__FUNCTION__.15331, %object
	.size	__FUNCTION__.15331, 13
__FUNCTION__.15331:
	.ascii	"H264DEC_Init\000"
	.space	3
	.type	__func__.15362, %object
	.size	__func__.15362, 18
__func__.15362:
	.ascii	"H264_VES_Splitter\000"
	.space	2
	.type	__func__.14011, %object
	.size	__func__.14011, 13
__func__.14011:
	.ascii	"DirectOutput\000"
	.space	3
	.type	__func__.14122, %object
	.size	__func__.14122, 14
__func__.14122:
	.ascii	"StorePicInDPB\000"
	.space	2
	.type	__FUNCTION__.14587, %object
	.size	__FUNCTION__.14587, 8
__FUNCTION__.14587:
	.ascii	"InitPic\000"
	.type	__func__.15248, %object
	.size	__func__.15248, 15
__func__.15248:
	.ascii	"H264_DecOneNal\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	quant_org, %object
	.size	quant_org, 16
quant_org:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	quant8_org, %object
	.size	quant8_org, 64
quant8_org:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	quant_intra_default, %object
	.size	quant_intra_default, 16
quant_intra_default:
	.word	471076102
	.word	538711053
	.word	622861332
	.word	707076124
	.type	quant_inter_default, %object
	.size	quant_inter_default, 16
quant_inter_default:
	.word	403967498
	.word	454562830
	.word	505092116
	.word	572398360
	.type	quant8_intra_default, %object
	.size	quant8_intra_default, 64
quant8_intra_default:
	.word	269289990
	.word	454629138
	.word	303041290
	.word	488315159
	.word	387059725
	.word	522001177
	.word	420942352
	.word	555687195
	.word	454629138
	.word	606150429
	.word	488315159
	.word	639901983
	.word	522001177
	.word	673588257
	.word	555687195
	.word	707274276
	.type	quant8_inter_default, %object
	.size	quant8_inter_default, 256
quant8_inter_default:
	.word	286199049
	.word	404100371
	.word	319884557
	.word	421008917
	.word	353571087
	.word	454629398
	.word	370479889
	.word	471537944
	.word	404100371
	.word	505158425
	.word	421008917
	.word	538844187
	.word	454629398
	.word	555752988
	.word	471537944
	.word	589373470
	.space	192
	.type	g_NalTypeEOPIC, %object
	.size	g_NalTypeEOPIC, 20
g_NalTypeEOPIC:
	.byte	0
	.byte	0
	.byte	1
	.byte	30
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	g_CabacMN, %object
	.size	g_CabacMN, 5120
g_CabacMN:
	.word	388044546
	.word	352326208
	.word	153820416
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	87683918
	.word	-180289218
	.word	17367089
	.word	-613020375
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	21230414
	.word	-180289218
	.word	440602714
	.word	157864575
	.word	-328728576
	.word	0
	.word	0
	.word	0
	.word	204602441
	.word	288553558
	.word	-278922691
	.word	154007875
	.word	-78971830
	.word	-78579384
	.word	20578304
	.word	0
	.word	-45745583
	.word	-178256329
	.word	121895766
	.word	39321658
	.word	-45287842
	.word	87426117
	.word	-45023144
	.word	0
	.word	370745856
	.word	268442146
	.word	320219136
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	37878343
	.word	-212925132
	.word	-32963543
	.word	-478802647
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-62064057
	.word	-212925132
	.word	956442916
	.word	440783743
	.word	-245039104
	.word	0
	.word	0
	.word	0
	.word	154336582
	.word	171312709
	.word	-212205516
	.word	137101122
	.word	-11730618
	.word	-27854008
	.word	3997696
	.word	0
	.word	-28968110
	.word	-161480133
	.word	38534487
	.word	-43777736
	.word	-45417899
	.word	3931473
	.word	-111740065
	.word	0
	.word	487594240
	.word	234886184
	.word	336207104
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	437320789
	.word	-395967175
	.word	-164364994
	.word	-446493399
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-28640171
	.word	-395967175
	.word	905979178
	.word	207741055
	.word	-361431040
	.word	0
	.word	0
	.word	0
	.word	104460105
	.word	238680669
	.word	-229049812
	.word	70714167
	.word	-61866421
	.word	-194905806
	.word	20709376
	.word	0
	.word	-178654873
	.word	-344714439
	.word	339346516
	.word	106955071
	.word	-78253206
	.word	88016459
	.word	-44368027
	.word	0
	.word	388044546
	.word	352326208
	.word	153820416
	.word	3013710
	.word	-44040151
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	203950899
	.word	238747648
	.word	0
	.word	0
	.word	87683918
	.word	-180289218
	.word	17367089
	.word	-613020375
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	21230414
	.word	-180289218
	.word	440602714
	.word	157864575
	.word	-328728576
	.word	0
	.word	0
	.word	0
	.word	204602441
	.word	288553558
	.word	-278922691
	.word	154007875
	.word	-78971830
	.word	-78579384
	.word	20578304
	.word	0
	.word	-45745583
	.word	-178256329
	.word	121895766
	.word	39321658
	.word	-45287842
	.word	87426117
	.word	-45023144
	.word	0
	.word	370745856
	.word	268442146
	.word	320219136
	.word	219088691
	.word	38797353
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	421532977
	.word	355860480
	.word	0
	.word	0
	.word	37878343
	.word	-212925132
	.word	-32963543
	.word	-478802647
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-62064057
	.word	-212925132
	.word	956442916
	.word	440783743
	.word	-245039104
	.word	0
	.word	0
	.word	0
	.word	154336582
	.word	171312709
	.word	-212205516
	.word	137101122
	.word	-11730618
	.word	-27854008
	.word	3997696
	.word	0
	.word	-28968110
	.word	-161480133
	.word	38534487
	.word	-43777736
	.word	-45417899
	.word	3931473
	.word	-111740065
	.word	0
	.word	487594240
	.word	234886184
	.word	336207104
	.word	119732056
	.word	-327221207
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	354489138
	.word	289210368
	.word	0
	.word	0
	.word	437320789
	.word	-395967175
	.word	-164364994
	.word	-446493399
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-28640171
	.word	-395967175
	.word	905979178
	.word	207741055
	.word	-361431040
	.word	0
	.word	0
	.word	0
	.word	104460105
	.word	238680669
	.word	-229049812
	.word	70714167
	.word	-61866421
	.word	-194905806
	.word	20709376
	.word	0
	.word	-178654873
	.word	-344714439
	.word	339346516
	.word	106955071
	.word	-78253206
	.word	88016459
	.word	-44368027
	.word	0
	.word	-276827290
	.word	5437770
	.word	-345250433
	.word	-511711105
	.word	-295705217
	.word	-344792449
	.word	0
	.word	0
	.word	-277089165
	.word	-260377229
	.word	-45614550
	.word	-80544458
	.word	-29491142
	.word	20971080
	.word	-11864229
	.word	0
	.word	-111282857
	.word	-45221049
	.word	-62915516
	.word	-195757762
	.word	-113178563
	.word	87621186
	.word	20971581
	.word	-28442624
	.word	402657033
	.word	135859474
	.word	252251411
	.word	170200082
	.word	102568993
	.word	253625389
	.word	20578366
	.word	121438208
	.word	-94504364
	.word	-129040318
	.word	-12124098
	.word	-29557189
	.word	-78906050
	.word	-63244478
	.word	-11599801
	.word	54788096
	.word	252053011
	.word	118492174
	.word	302845195
	.word	219090704
	.word	202837271
	.word	252972570
	.word	237769000
	.word	288292864
	.word	-197132732
	.word	-246090904
	.word	-79430885
	.word	-47710676
	.word	3076160
	.word	-129698226
	.word	-95553962
	.word	0
	.word	20055860
	.word	170065964
	.word	187040045
	.word	3015980
	.word	521208115
	.word	120724499
	.word	270601790
	.word	0
	.word	203819821
	.word	254217002
	.word	220991533
	.word	204016177
	.word	505549354
	.word	171381043
	.word	288227417
	.word	0
	.word	170719550
	.word	254021160
	.word	270208029
	.word	19665956
	.word	304088362
	.word	19925566
	.word	288229696
	.word	0
	.word	403772693
	.word	420880155
	.word	371004195
	.word	238160441
	.word	121634381
	.word	-61670050
	.word	155579501
	.word	0
	.word	-45680547
	.word	-161815937
	.word	-195235529
	.word	-163775938
	.word	-62786487
	.word	-129173168
	.word	-145166482
	.word	0
	.word	-210964124
	.word	-211422373
	.word	-195103144
	.word	-262867370
	.word	-111938729
	.word	-312606394
	.word	4782922
	.word	305856512
	.word	451745519
	.word	451878631
	.word	485237225
	.word	635773417
	.word	686040815
	.word	569714929
	.word	704259585
	.word	688979968
	.word	-194448031
	.word	-262080168
	.word	-128583339
	.word	-145362088
	.word	71499085
	.word	-45286836
	.word	171638604
	.word	-11337728
	.word	618472670
	.word	551953890
	.word	752886510
	.word	586230001
	.word	569975803
	.word	553657858
	.word	554506019
	.word	221904896
	.word	-11863455
	.word	-111416193
	.word	-178131884
	.word	-179307959
	.word	-62196906
	.word	-211749535
	.word	-311099392
	.word	0
	.word	-127471260
	.word	6225920
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	519707395
	.word	437649408
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-110890401
	.word	39780352
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	503126528
	.word	371064832
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-63374510
	.word	-112399747
	.word	-129041631
	.word	-63898059
	.word	-46206137
	.word	-162532266
	.word	-212143519
	.word	0
	.word	-62193080
	.word	-179569337
	.word	254735173
	.word	4063297
	.word	354808136
	.word	154734646
	.word	4066376
	.word	0
	.word	636494844
	.word	653797117
	.word	620963333
	.word	704652048
	.word	655756848
	.word	455415100
	.word	205783649
	.word	0
	.word	5045066
	.word	4650315
	.word	21233729
	.word	-230096066
	.word	71237444
	.word	-213185737
	.word	88083526
	.word	0
	.word	536421361
	.word	587014659
	.word	620700165
	.word	537600773
	.word	571221771
	.word	505225754
	.word	489100098
	.word	0
	.word	0
	.word	0
	.word	-45351145
	.word	19005739
	.word	3604023
	.word	3998016
	.word	4519772
	.word	0
	.word	-277287824
	.word	-294455979
	.word	-245566887
	.word	-431492783
	.word	-229638076
	.word	-230234056
	.word	-381360078
	.word	-179699712
	.word	401808115
	.word	686895602
	.word	738405638
	.word	740434230
	.word	324141056
	.word	0
	.word	0
	.word	0
	.word	-227871903
	.word	-245697446
	.word	-296159671
	.word	-145755562
	.word	-162924986
	.word	-163185854
	.word	-146736326
	.word	37421056
	.word	368449781
	.word	486022399
	.word	486743305
	.word	588520740
	.word	239271936
	.word	0
	.word	0
	.word	0
	.word	-444668830
	.word	-412751549
	.word	-464327586
	.word	-262935954
	.word	-346296730
	.word	-211950721
	.word	0
	.word	0
	.word	-111346855
	.word	-111086740
	.word	-95617492
	.word	2949172
	.word	-46072261
	.word	-62456757
	.word	-128782490
	.word	0
	.word	-27919794
	.word	-11798195
	.word	37094706
	.word	-45874894
	.word	103480401
	.word	20970566
	.word	4391481
	.word	-28573696
	.word	186384936
	.word	53215281
	.word	3015212
	.word	36896815
	.word	69665342
	.word	103678006
	.word	53871162
	.word	71237632
	.word	-211095446
	.word	-162010254
	.word	-294718878
	.word	-361829526
	.word	-295179413
	.word	-378739088
	.word	-161418145
	.word	-77922304
	.word	235604750
	.word	151720459
	.word	352917502
	.word	552673521
	.word	585836521
	.word	719268321
	.word	786704116
	.word	354222080
	.word	-47251647
	.word	-12978339
	.word	-145947880
	.word	2752560
	.word	3668539
	.word	-112724909
	.word	-178789769
	.word	0
	.word	186844224
	.word	20777763
	.word	303631384
	.word	220007716
	.word	-161613495
	.word	-28766930
	.word	154270052
	.word	0
	.word	104007225
	.word	120915508
	.word	104270637
	.word	237242421
	.word	-11401417
	.word	-45215954
	.word	371195732
	.word	0
	.word	-144840098
	.word	-78247613
	.word	-61802923
	.word	-12187844
	.word	154797373
	.word	204607282
	.word	305205558
	.word	0
	.word	770192851
	.word	820396501
	.word	736962550
	.word	503910938
	.word	337313849
	.word	-229442741
	.word	-312353411
	.word	0
	.word	-45418660
	.word	-128456322
	.word	20643101
	.word	-14417626
	.word	36436535
	.word	3801152
	.word	-45418918
	.word	0
	.word	154468917
	.word	87424573
	.word	3670072
	.word	-213910724
	.word	-12712903
	.word	-96140231
	.word	237438003
	.word	222560256
	.word	419897081
	.word	469965828
	.word	536879871
	.word	503717382
	.word	537468691
	.word	437983774
	.word	622074914
	.word	289800192
	.word	170460974
	.word	-13433039
	.word	137627945
	.word	103744055
	.word	220793388
	.word	103941429
	.word	221316159
	.word	104857600
	.word	452992000
	.word	536615686
	.word	570957322
	.word	404103443
	.word	371202591
	.word	355015212
	.word	388960321
	.word	239534080
	.word	87426620
	.word	104531525
	.word	4652061
	.word	85919530
	.word	20708922
	.word	-45548207
	.word	-178192384
	.word	0
	.word	54526269
	.word	155123712
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	21169467
	.word	155385856
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-28967365
	.word	105250816
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	138151487
	.word	289472512
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-13631420
	.word	-62523304
	.word	3803141
	.word	168693266
	.word	219873832
	.word	3865926
	.word	-95422379
	.word	0
	.word	120721447
	.word	86770740
	.word	187759420
	.word	-12910533
	.word	371262764
	.word	237764430
	.word	3934533
	.word	0
	.word	270406176
	.word	304289309
	.word	404690726
	.word	304813097
	.word	188680507
	.word	155254622
	.word	-27658388
	.word	0
	.word	170658079
	.word	204145461
	.word	237111846
	.word	-46920408
	.word	287311660
	.word	119934258
	.word	171514411
	.word	0
	.word	353900308
	.word	437721888
	.word	471276568
	.word	388503584
	.word	471668522
	.word	322508341
	.word	373099350
	.word	0
	.word	0
	.word	0
	.word	-96274141
	.word	-114624467
	.word	-80677832
	.word	-96666818
	.word	-129828788
	.word	0
	.word	-61867705
	.word	-79300794
	.word	-129829308
	.word	-313920443
	.word	-263786173
	.word	-331420346
	.word	-264050111
	.word	-331415552
	.word	167647991
	.word	569845753
	.word	704523523
	.word	822684955
	.word	607846400
	.word	0
	.word	0
	.word	0
	.word	-78251439
	.word	-162662063
	.word	-279908791
	.word	-62196141
	.word	-146278589
	.word	-12715966
	.word	-230555589
	.word	37421056
	.word	368255474
	.word	670641918
	.word	855784454
	.word	1024538402
	.word	708706304
	.word	0
	.word	0
	.word	0
	.word	-645927333
	.word	-278862255
	.word	-580720538
	.word	-379460233
	.word	-396104850
	.word	-295248769
	.word	0
	.word	0
	.word	5307225
	.word	-111215524
	.word	-378474169
	.word	-113442763
	.word	-79497907
	.word	-145688748
	.word	-162013569
	.word	0
	.word	-211291301
	.word	-145100196
	.word	-129174441
	.word	-378607511
	.word	-162599824
	.word	-278678913
	.word	-1166029185
	.word	-763428864
	.word	70060572
	.word	169812469
	.word	886379023
	.word	469771242
	.word	652681728
	.word	669917428
	.word	1721892864
	.word	955318272
	.word	-344004228
	.word	-328276354
	.word	-411242647
	.word	-444996235
	.word	-278469003
	.word	-445325446
	.word	-161484188
	.word	-127991808
	.word	335155962
	.word	234887924
	.word	535831015
	.word	568993252
	.word	669133538
	.word	802565596
	.word	836643311
	.word	537460736
	.word	2555969
	.word	-246096513
	.word	-345637593
	.word	-80348867
	.word	-179572403
	.word	-279189653
	.word	-412097414
	.word	0
	.word	-62719154
	.word	-62392248
	.word	37486391
	.word	-112788917
	.word	-128328073
	.word	-45408236
	.word	504812671
	.word	0
	.word	570170634
	.word	637219811
	.word	670512350
	.word	1170621377
	.word	754655239
	.word	937631745
	.word	6948
	.word	0
	.word	-277879694
	.word	-94765488
	.word	-61671595
	.word	-128843960
	.word	88080707
	.word	154665029
	.word	21301061
	.word	0
	.word	1169768385
	.word	1119899062
	.word	920204509
	.word	703996928
	.word	687808014
	.word	471471909
	.word	204933953
	.word	0
	.word	-28707736
	.word	-144973441
	.word	-179505620
	.word	-164301255
	.word	-147132344
	.word	-112853947
	.word	-78973098
	.word	0
	.word	3603261
	.word	3866428
	.word	-46270397
	.word	-413863350
	.word	-79624908
	.word	37290045
	.word	-146410170
	.word	305594368
	.word	568795874
	.word	618931940
	.word	652550894
	.word	602940146
	.word	553133562
	.word	587210250
	.word	470948377
	.word	489226240
	.word	-112854461
	.word	-263324096
	.word	37616195
	.word	-46136775
	.word	-46006974
	.word	4065587
	.word	-12386745
	.word	-28639232
	.word	635381724
	.word	685450978
	.word	786377442
	.word	686305763
	.word	653535478
	.word	654126843
	.word	521411870
	.word	422313984
	.word	53937976
	.word	121047101
	.word	37943074
	.word	18877215
	.word	87359031
	.word	-29163447
	.word	-128385024
	.word	0
	.word	-62455750
	.word	121438208
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	4915784
	.word	139264000
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-12126392
	.word	238813184
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	204475185
	.word	439156736
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-46858172
	.word	-112527528
	.word	53741316
	.word	168300808
	.word	269681445
	.word	-12715191
	.word	-12125106
	.word	0
	.word	153686553
	.word	153093419
	.word	154075180
	.word	3342894
	.word	321322050
	.word	254151722
	.word	153223257
	.word	0
	.word	237179423
	.word	287511838
	.word	288166954
	.word	304945946
	.word	271976258
	.word	272108361
	.word	172226164
	.word	0
	.word	270860335
	.word	304286501
	.word	204016169
	.word	36703273
	.word	220790843
	.word	53613352
	.word	54661682
	.word	0
	.word	370546454
	.word	454369556
	.word	438050328
	.word	455217706
	.word	421990962
	.word	205919542
	.word	239536979
	.word	0
	.word	0
	.word	0
	.word	-79233000
	.word	-14352854
	.word	-30083271
	.word	-96469951
	.word	-62654126
	.word	0
	.word	-78251439
	.word	-162662063
	.word	-279908791
	.word	-62196141
	.word	-146278589
	.word	-12715966
	.word	-230555589
	.word	37421056
	.word	301342963
	.word	720843259
	.word	889208835
	.word	1141522971
	.word	792264704
	.word	0
	.word	0
	.word	0
	.word	-44958388
	.word	-112657842
	.word	-196545980
	.word	-45680052
	.word	-79496386
	.word	3800125
	.word	-147062474
	.word	37355520
	.word	301342963
	.word	720843259
	.word	889208835
	.word	1141522971
	.word	792264704
	.word	0
	.word	0
	.word	0
	.word	-595595429
	.word	-228595884
	.word	-413731751
	.word	-279191169
	.word	-229839257
	.word	-212149377
	.word	0
	.word	0
	.word	189793612
	.word	39060814
	.word	-395056558
	.word	-146931659
	.word	3928661
	.word	-212208802
	.word	-178461825
	.word	0
	.word	-61410216
	.word	-78447288
	.word	-62654392
	.word	-262539451
	.word	-12909246
	.word	70908999
	.word	-28900806
	.word	-11927552
	.word	69664810
	.word	119671581
	.word	136250917
	.word	120193832
	.word	136383787
	.word	220464175
	.word	53936698
	.word	104595456
	.word	-360716417
	.word	-411507329
	.word	-311236235
	.word	-411638155
	.word	-395189130
	.word	-512173188
	.word	-161549978
	.word	-161284096
	.word	301142263
	.word	301210603
	.word	635578840
	.word	718745809
	.word	669003480
	.word	885862103
	.word	886647789
	.word	537591808
	.word	-97057731
	.word	-229385345
	.word	-345705927
	.word	-196872889
	.word	-162665643
	.word	-262608536
	.word	-245179521
	.word	0
	.word	-64159931
	.word	4127027
	.word	-63964630
	.word	-47580619
	.word	139261774
	.word	-179107532
	.word	4455258
	.word	0
	.word	137104172
	.word	237635376
	.word	70779956
	.word	220530993
	.word	322570800
	.word	204275781
	.word	337709119
	.word	0
	.word	-211104129
	.word	-77852359
	.word	-78187682
	.word	-195297715
	.word	4718409
	.word	71366993
	.word	88084281
	.word	0
	.word	1036597458
	.word	1053708733
	.word	770450430
	.word	470753793
	.word	654384657
	.word	338039341
	.word	255197263
	.word	0
	.word	-78645912
	.word	-178527617
	.word	-162334672
	.word	-130156478
	.word	-112790965
	.word	-162531501
	.word	-195236244
	.word	0
	.word	21229896
	.word	-78907312
	.word	-346821824
	.word	-216012992
	.word	-480376501
	.word	289405002
	.word	-81527269
	.word	224067584
	.word	602808807
	.word	486348810
	.word	452993778
	.word	886319080
	.word	319889177
	.word	605886497
	.word	571416084
	.word	373882880
	.word	21168196
	.word	-163380924
	.word	5046848
	.word	4520782
	.word	121046331
	.word	37817910
	.word	254543164
	.word	38141952
	.word	619718130
	.word	636428289
	.word	571415823
	.word	404300310
	.word	521151250
	.word	521937193
	.word	605821743
	.word	356384768
	.word	4324943
	.word	4783196
	.word	-61871547
	.word	-263455174
	.word	20640590
	.word	-145490863
	.word	-211615744
	.word	0
	.word	54655301
	.word	139264000
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	337777439
	.word	455868416
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-28512682
	.word	205914112
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	304026394
	.word	605552640
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-96992444
	.word	-129502366
	.word	-212731354
	.word	-213976518
	.word	-29626295
	.word	-162729130
	.word	-145492393
	.word	0
	.word	-163445954
	.word	-45814703
	.word	1966343
	.word	-48764086
	.word	272820604
	.word	287649006
	.word	853469823
	.word	0
	.word	319819556
	.word	254022940
	.word	420814356
	.word	520887056
	.word	405405789
	.word	238554937
	.word	438757503
	.word	0
	.word	88142918
	.word	188155192
	.word	4522561
	.word	-95812298
	.word	121043532
	.word	-179110323
	.word	-28501718
	.word	0
	.word	404167440
	.word	404627229
	.word	371791402
	.word	272371508
	.word	238814030
	.word	-260369099
	.word	372775229
	.word	0
	.word	0
	.word	0
	.word	-146278107
	.word	-131271375
	.word	-164039621
	.word	-130025661
	.word	-96143793
	.word	0
	.word	-45156278
	.word	-146213304
	.word	-297012153
	.word	-180356282
	.word	-280235448
	.word	-263981003
	.word	-230951116
	.word	-180092928
	.word	167649014
	.word	536617471
	.word	554114828
	.word	622272294
	.word	339738624
	.word	0
	.word	0
	.word	0
	.word	-45156278
	.word	-146213304
	.word	-297012153
	.word	-180356282
	.word	-280235448
	.word	-263981003
	.word	-230951116
	.word	-180092928
	.word	167649014
	.word	536617471
	.word	554114828
	.word	622272294
	.word	339738624
	.word	0
	.word	0
	.word	0
	.type	CalcZeroNum, %object
	.size	CalcZeroNum, 256
CalcZeroNum:
	.byte	8
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
	.type	g_AspecRatioIdc, %object
	.size	g_AspecRatioIdc, 112
g_AspecRatioIdc:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	12
	.word	11
	.word	10
	.word	11
	.word	16
	.word	11
	.word	40
	.word	33
	.word	24
	.word	11
	.word	20
	.word	11
	.word	32
	.word	11
	.word	80
	.word	33
	.word	18
	.word	11
	.word	15
	.word	11
	.word	64
	.word	33
	.word	160
	.word	99
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"list[%d][%d]: frame_num=%d, poc=%d\012\000" )
.LC1:
	ASCII(.ascii	"L0: \000" )
	.space	3
.LC2:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"%d \000" )
.LC4:
	ASCII(.ascii	"%dt \000" )
	.space	3
.LC5:
	ASCII(.ascii	"%db \000" )
	.space	3
.LC6:
	ASCII(.ascii	"L1:\000" )
.LC7:
	ASCII(.ascii	"%-50s%50d\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"../../core/syntax/h264.c\000" )
	.space	3
.LC9:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"\012 VFMW ** release streambuff=%p   bitstream_leng" )
	ASCII(.ascii	"th=%d\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"%s DPB.fs[%d] = NULL\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"clear curr slice.\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"frame %d, state=%d, is already output\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"plfs(fs=%p, eFoState=%d) is null, logic_fs_id = %d\012" )
	ASCII(.ascii	"\000" )
.LC15:
	ASCII(.ascii	"not used frame: (%d,%d)\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"frame skip: is_used=%d,skip=%d\012\000" )
.LC17:
	ASCII(.ascii	"topfield skip: is_used=%d,skip=%d\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"bottom field skip: is_used=%d,skip=%d\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC21:
	ASCII(.ascii	"stream frame packing type is %d! what can we do?\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC22:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(ref=%d,plfs=%" )
	ASCII(.ascii	"p, pdfs=%p)\012\000" )
.LC24:
	ASCII(.ascii	"pH264Ctx->DPB.fs[%d]: frame_num=%d poc=%d is_refere" )
	ASCII(.ascii	"nce=%d\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"pH264Ctx->DPB.fs_ref[%d]: frame_num=%d poc=%d is_re" )
	ASCII(.ascii	"ference=%d\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"pH264Ctx->DPB.fs_ref[%d]: frame.poc=%d \012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC28:
	ASCII(.ascii	"resolution error, ImageWidth=%d, ImageHeight=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC29:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"slice_type %d invalid, clear current slice.\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"pRepairPic(%p)/found(%d) = 0, clear current slice.\012" )
	ASCII(.ascii	"\000" )
.LC33:
	ASCII(.ascii	"listXsize[%d] = %d, clear current slice.\012\000" )
	.space	2
.LC34:
	ASCII(.ascii	"for P slice size of list equal 0.\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"for B slice size of two list all equal 0.\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"init list error.\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"L0: list after init.\012\000" )
	.space	2
.LC38:
	ASCII(.ascii	"L0: list after reorder.\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC40:
	ASCII(.ascii	"logic frame id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"line: %d pstLogicFs is null\012\000" )
	.space	3
.LC43:
	ASCII(.ascii	"SH: first_mb_in_slice\000" )
	.space	2
.LC44:
	ASCII(.ascii	"slicecheck first_mb_in_slice >= MAX_MB_NUM_IN_PIC e" )
	ASCII(.ascii	"rror.\012\000" )
	.space	2
.LC45:
	ASCII(.ascii	"SH: slice_type\000" )
	.space	1
.LC46:
	ASCII(.ascii	"slice type = %d\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"slice type = %d, err\012\000" )
	.space	2
.LC48:
	ASCII(.ascii	"slice  pps id = %d\012\000" )
.LC49:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't deco" )
	ASCII(.ascii	"de\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"sps with this pic_parameter_set_id = %d havn't deco" )
	ASCII(.ascii	"de\012\000" )
	.space	1
.LC51:
	ASCII(.ascii	"tmp slice  pps id = %d\012\000" )
.LC52:
	ASCII(.ascii	"PPSSPSCheckTmpId: pps with this pic_parameter_set_i" )
	ASCII(.ascii	"d = %d havn't decode\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"PPSSPSCheckTmpId: seq_parameter_set_id out of range" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC54:
	ASCII(.ascii	"PPSSPSCheckTmpId: sps with this pic_parameter_set_i" )
	ASCII(.ascii	"d = %d havn't decode\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"new pic flag = %d\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l0\000" )
.LC57:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l0\000" )
	.space	2
.LC58:
	ASCII(.ascii	"reorder idc l0 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l0\000" )
	.space	1
.LC60:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC61:
	ASCII(.ascii	"SH: long_term_pic_idx_l0\000" )
	.space	3
.LC62:
	ASCII(.ascii	"num of idc l0 exceed\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l1\000" )
.LC64:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l1\000" )
	.space	2
.LC65:
	ASCII(.ascii	"reorder idc l1 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l1\000" )
	.space	1
.LC67:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l1 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC68:
	ASCII(.ascii	"SH: long_term_pic_idx_l1\000" )
	.space	3
.LC69:
	ASCII(.ascii	"num of idc l1 exceed\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"SH: luma_log2_weight_denom\000" )
	.space	1
.LC71:
	ASCII(.ascii	"SH: chroma_log2_weight_denom\000" )
	.space	3
.LC72:
	ASCII(.ascii	"WP log2 exceed  and err flag = %d\012\000" )
	.space	1
.LC73:
	ASCII(.ascii	"SH: luma_weight_flag_l0\000" )
.LC74:
	ASCII(.ascii	"SH: luma_weight_l0\000" )
	.space	1
.LC75:
	ASCII(.ascii	"SH: luma_offset_l0\000" )
	.space	1
.LC76:
	ASCII(.ascii	"SH: chroma_weight_flag_l0\000" )
	.space	2
.LC77:
	ASCII(.ascii	"SH: chroma_weight_l0\000" )
	.space	3
.LC78:
	ASCII(.ascii	"SH: chroma_offset_l0\000" )
	.space	3
.LC79:
	ASCII(.ascii	"SH: luma_weight_flag_l1\000" )
.LC80:
	ASCII(.ascii	"SH: luma_weight_l1\000" )
	.space	1
.LC81:
	ASCII(.ascii	"SH: luma_offset_l1\000" )
	.space	1
.LC82:
	ASCII(.ascii	"SH: chroma_weight_flag_l1\000" )
	.space	2
.LC83:
	ASCII(.ascii	"SH: chroma_weight_l1\000" )
	.space	3
.LC84:
	ASCII(.ascii	"SH: chroma_offset_l1\000" )
	.space	3
.LC85:
	ASCII(.ascii	"overflow MAX_MMCO_LEN\012\000" )
	.space	1
.LC86:
	ASCII(.ascii	"SH: memory_management_control_operation\000" )
.LC87:
	ASCII(.ascii	"SH: difference_of_pic_nums_minus1\000" )
	.space	2
.LC88:
	ASCII(.ascii	"SH: long_term_pic_num\000" )
	.space	2
.LC89:
	ASCII(.ascii	"SH: long_term_frame_idx\000" )
.LC90:
	ASCII(.ascii	"SH: max_long_term_frame_idx_plus1\000" )
	.space	2
.LC91:
	ASCII(.ascii	"mmco exceed 6\012\000" )
	.space	1
.LC92:
	ASCII(.ascii	"SH: no_output_of_prior_pics_flag\000" )
	.space	3
.LC93:
	ASCII(.ascii	"SH: long_term_reference_flag\000" )
	.space	3
.LC94:
	ASCII(.ascii	"IDR and no_output_of_prior_pics_flag = %d\012\000" )
	.space	1
.LC95:
	ASCII(.ascii	"SH: adaptive_ref_pic_marking_mode_flag\000" )
	.space	1
.LC96:
	ASCII(.ascii	"adaptive_ref_pic_marking_mode_flag = %d\012\000" )
	.space	3
.LC97:
	ASCII(.ascii	"MMCO para would save dec err\012\000" )
	.space	2
.LC98:
	ASCII(.ascii	"mulitislice diff no_out_of_prior_pics_flag, used fi" )
	ASCII(.ascii	"rst.\012\000" )
	.space	3
.LC99:
	ASCII(.ascii	"mulitislice diff long_term_reference_flag, used fir" )
	ASCII(.ascii	"st.\012\000" )
.LC100:
	ASCII(.ascii	"mulitislice diff adaptive_ref_pic_marking_mode_flag" )
	ASCII(.ascii	", used first.\012\000" )
	.space	2
.LC101:
	ASCII(.ascii	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\012\000" )
	.space	1
.LC102:
	ASCII(.ascii	"SH: pic_parameter_set_id\000" )
	.space	3
.LC103:
	ASCII(.ascii	"pps id:%d in sliceheader err\012\000" )
	.space	2
.LC104:
	ASCII(.ascii	"PPS or SPS of this slice not valid\012\000" )
.LC105:
	ASCII(.ascii	"recover point but isn't I_SLICE.\012\000" )
	.space	2
.LC106:
	ASCII(.ascii	"SH: frame_num\000" )
	.space	2
.LC107:
	ASCII(.ascii	"IDR NAL but frame_num!=0.\012\000" )
	.space	1
.LC108:
	ASCII(.ascii	"SH: field_pic_flag\000" )
	.space	1
.LC109:
	ASCII(.ascii	"SH: bottom_field_flag\000" )
	.space	2
.LC110:
	ASCII(.ascii	"field first_mb_in_slice bigger than pic size\012\000" )
	.space	2
.LC111:
	ASCII(.ascii	"frame first_mb_in_slice bigger than pic size\012\000" )
	.space	2
.LC112:
	ASCII(.ascii	"SH: idr_pic_id\000" )
	.space	1
.LC113:
	ASCII(.ascii	"idr_pic_id bigger than 65535\012\000" )
	.space	2
.LC114:
	ASCII(.ascii	"SH: pic_order_cnt_lsb\000" )
	.space	2
.LC115:
	ASCII(.ascii	"SH: delta_pic_order_cnt_bottom\000" )
	.space	1
.LC116:
	ASCII(.ascii	"SH: delta_pic_order_cnt[0]\000" )
	.space	1
.LC117:
	ASCII(.ascii	"SH: delta_pic_order_cnt[1]\000" )
	.space	1
.LC118:
	ASCII(.ascii	"SH: redundant_pic_cnt\000" )
	.space	2
.LC119:
	ASCII(.ascii	"redundant pic not support.\012\000" )
.LC120:
	ASCII(.ascii	"first_mb_in_slice in currslice small than prevslice" )
	ASCII(.ascii	" in same pic\012\000" )
	.space	3
.LC121:
	ASCII(.ascii	"SH: direct_spatial_mv_pred_flag\000" )
.LC122:
	ASCII(.ascii	"SH: num_ref_idx_override_flag\000" )
	.space	2
.LC123:
	ASCII(.ascii	"SH: num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC124:
	ASCII(.ascii	"SH: num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC125:
	ASCII(.ascii	"frame num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC126:
	ASCII(.ascii	"field num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC127:
	ASCII(.ascii	"reordering para dec err\012\000" )
	.space	3
.LC128:
	ASCII(.ascii	"apply_weights_flag=%d\012\000" )
	.space	1
.LC129:
	ASCII(.ascii	"wpt dec err\012\000" )
	.space	3
.LC130:
	ASCII(.ascii	"mark para dec err\012\000" )
	.space	1
.LC131:
	ASCII(.ascii	"SH: cabac_init_idc\000" )
	.space	1
.LC132:
	ASCII(.ascii	"cabac_init_idc bigger than 3\012\000" )
	.space	2
.LC133:
	ASCII(.ascii	"SH: slice_qp_delta\000" )
	.space	1
.LC134:
	ASCII(.ascii	"SH: disable_deblocking_filter_idc\000" )
	.space	2
.LC135:
	ASCII(.ascii	"disable_deblocking_filter_idc dec err\012\000" )
	.space	1
.LC136:
	ASCII(.ascii	"SH: slice_alpha_c0_offset_div2\000" )
	.space	1
.LC137:
	ASCII(.ascii	"slice_alpha_c0_offset_div2 dec err\012\000" )
.LC138:
	ASCII(.ascii	"SH: slice_beta_offset_div2\000" )
	.space	1
.LC139:
	ASCII(.ascii	"slice_beta_offset_div2 dec err\012\000" )
.LC140:
	ASCII(.ascii	"pH264Ctx->pCurrNal->nal_bitoffset = %d; code_len_by" )
	ASCII(.ascii	"te = %d; bitstream_length = %d; pH264Ctx->pCurrNal-" )
	ASCII(.ascii	">nal_trail_zero_bit_num = %d\012\000" )
.LC141:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; byt" )
	ASCII(.ascii	"espos = %x\012\000" )
	.space	1
.LC142:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC143:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\012\000" )
.LC144:
	ASCII(.ascii	"   : delta_sl   \000" )
	.space	3
.LC145:
	ASCII(.ascii	"PPS: entropy_coding_mode_flag\000" )
	.space	2
.LC146:
	ASCII(.ascii	"PPS: pic_order_present_flag\000" )
.LC147:
	ASCII(.ascii	"PPS: num_slice_groups_minus1\000" )
	.space	3
.LC148:
	ASCII(.ascii	"Baseline stream with FMO, not support.\012\000" )
.LC149:
	ASCII(.ascii	"PPS: num_ref_idx_l0_active_minus1\000" )
	.space	2
.LC150:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1 out of range.\012\000" )
.LC151:
	ASCII(.ascii	"PPS: num_ref_idx_l1_active_minus1\000" )
	.space	2
.LC152:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1 out of range.\012\000" )
.LC153:
	ASCII(.ascii	"PPS: weighted prediction flag\000" )
	.space	2
.LC154:
	ASCII(.ascii	"PPS: weighted_bipred_idc\000" )
	.space	3
.LC155:
	ASCII(.ascii	"weighted_bipred_idc out of range\012\000" )
	.space	2
.LC156:
	ASCII(.ascii	"PPS: pic_init_qp_minus26\000" )
	.space	3
.LC157:
	ASCII(.ascii	"PPS: pic_init_qs_minus26\000" )
	.space	3
.LC158:
	ASCII(.ascii	"PPS: chroma_qp_index_offset\000" )
.LC159:
	ASCII(.ascii	"PPS: deblocking_filter_control_present_flag\000" )
.LC160:
	ASCII(.ascii	"PPS: constrained_intra_pred_flag\000" )
	.space	3
.LC161:
	ASCII(.ascii	"PPS: redundant_pic_cnt_present_flag\000" )
.LC162:
	ASCII(.ascii	"redundant pic not support when find redundant slice" )
	ASCII(.ascii	" later, exit\012\000" )
	.space	3
.LC163:
	ASCII(.ascii	"PPS: transform_8x8_mode_flag\000" )
	.space	3
.LC164:
	ASCII(.ascii	"PPS: pic_scaling_matrix_present_flag\000" )
	.space	3
.LC165:
	ASCII(.ascii	"PPS: second_chroma_qp_index_offset\000" )
	.space	1
.LC166:
	ASCII(.ascii	"SPS: seq_scaling_list_present_flag\000" )
	.space	1
.LC167:
	ASCII(.ascii	"PPS: pic_scaling_list_present_flag\000" )
	.space	1
.LC168:
	ASCII(.ascii	"second_chroma_qp_index_offset out of range.\012\000" )
	.space	3
.LC169:
	ASCII(.ascii	"PPS: pic_parameter_set_id\000" )
	.space	2
.LC170:
	ASCII(.ascii	"pic_parameter_set_id out of range.\012\000" )
.LC171:
	ASCII(.ascii	"PPS: seq_parameter_set_id\000" )
	.space	2
.LC172:
	ASCII(.ascii	"seq_parameter_set_id out of range.\012\000" )
.LC173:
	ASCII(.ascii	"SPS haven't decode.\012\000" )
	.space	3
.LC174:
	ASCII(.ascii	"%s: PPS decode error 1.\012\000" )
	.space	3
.LC175:
	ASCII(.ascii	"%s: PPS decode error 2.\012\000" )
	.space	3
.LC176:
	ASCII(.ascii	"VUI: aspect_ratio_info_present_flag\000" )
.LC177:
	ASCII(.ascii	"VUI: aspect_ratio_idc\000" )
	.space	2
.LC178:
	ASCII(.ascii	"VUI: sar_width\000" )
	.space	1
.LC179:
	ASCII(.ascii	"VUI: sar_height\000" )
.LC180:
	ASCII(.ascii	"VUI: overscan_info_present_flag\000" )
.LC181:
	ASCII(.ascii	"VUI: overscan_appropriate_flag\000" )
	.space	1
.LC182:
	ASCII(.ascii	"VUI: video_signal_type_present_flag\000" )
.LC183:
	ASCII(.ascii	"VUI: video_format\000" )
	.space	2
.LC184:
	ASCII(.ascii	"VUI: video_full_range_flag\000" )
	.space	1
.LC185:
	ASCII(.ascii	"VUI: color_description_present_flag\000" )
.LC186:
	ASCII(.ascii	"VUI: colour_primaries\000" )
	.space	2
.LC187:
	ASCII(.ascii	"VUI: transfer_characteristics\000" )
	.space	2
.LC188:
	ASCII(.ascii	"VUI: matrix_coefficients\000" )
	.space	3
.LC189:
	ASCII(.ascii	"VUI: chroma_loc_info_present_flag\000" )
	.space	2
.LC190:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_top_field\000" )
	.space	2
.LC191:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_bottom_field\000" )
	.space	3
.LC192:
	ASCII(.ascii	"VUI: timing_info_present_flag\000" )
	.space	2
.LC193:
	ASCII(.ascii	"VUI: num_units_in_tick\000" )
	.space	1
.LC194:
	ASCII(.ascii	"VUI: time_scale\000" )
.LC195:
	ASCII(.ascii	"VUI: fixed_frame_rate_flag\000" )
	.space	1
.LC196:
	ASCII(.ascii	"VUI: nal_hrd_parameters_present_flag\000" )
	.space	3
.LC197:
	ASCII(.ascii	"VUI: cpb_cnt_minus1\000" )
.LC198:
	ASCII(.ascii	"VUI: bit_rate_scale\000" )
.LC199:
	ASCII(.ascii	"VUI: cpb_size_scale\000" )
.LC200:
	ASCII(.ascii	"hrd->cpb_cnt_minus1 out of range\012\000" )
	.space	2
.LC201:
	ASCII(.ascii	"VUI: bit_rate_value_minus1\000" )
	.space	1
.LC202:
	ASCII(.ascii	"VUI: cpb_size_value_minus1\000" )
	.space	1
.LC203:
	ASCII(.ascii	"VUI: cbr_flag\000" )
	.space	2
.LC204:
	ASCII(.ascii	"VUI: initial_cpb_removal_delay_length_minus1\000" )
	.space	3
.LC205:
	ASCII(.ascii	"VUI: cpb_removal_delay_length_minus1\000" )
	.space	3
.LC206:
	ASCII(.ascii	"VUI: dpb_output_delay_length_minus1\000" )
.LC207:
	ASCII(.ascii	"VUI: time_offset_length\000" )
.LC208:
	ASCII(.ascii	"VUI: vcl_hrd_parameters_present_flag\000" )
	.space	3
.LC209:
	ASCII(.ascii	"VUI: low_delay_hrd_flag\000" )
.LC210:
	ASCII(.ascii	"VUI: pic_struct_present_flag\000" )
	.space	3
.LC211:
	ASCII(.ascii	"VUI: bitstream_restriction_flag\000" )
.LC212:
	ASCII(.ascii	"VUI: motion_vectors_over_pic_boundaries_flag\000" )
	.space	3
.LC213:
	ASCII(.ascii	"VUI: max_bytes_per_pic_denom\000" )
	.space	3
.LC214:
	ASCII(.ascii	"VUI: max_bits_per_mb_denom\000" )
	.space	1
.LC215:
	ASCII(.ascii	"VUI: log2_max_mv_length_horizontal\000" )
	.space	1
.LC216:
	ASCII(.ascii	"VUI: log2_max_mv_length_vertical\000" )
	.space	3
.LC217:
	ASCII(.ascii	"VUI: num_reorder_frames\000" )
.LC218:
	ASCII(.ascii	"VUI: max_dec_frame_buffering\000" )
	.space	3
.LC219:
	ASCII(.ascii	"dar=%d, final_dar=%d\012\000" )
	.space	2
.LC220:
	ASCII(.ascii	"SPS: chroma_format_idc\000" )
	.space	1
.LC221:
	ASCII(.ascii	"pSPS->chroma_format_idc = %d out of range.\012\000" )
.LC222:
	ASCII(.ascii	"SPS: bit_depth_luma_minus8\000" )
	.space	1
.LC223:
	ASCII(.ascii	"bit_depth_luma(%d) not equal 8.\012\000" )
	.space	3
.LC224:
	ASCII(.ascii	"SPS: bit_depth_chroma_minus8\000" )
	.space	3
.LC225:
	ASCII(.ascii	"bit_depth_chroma(%d) not equal 8.\012\000" )
	.space	1
.LC226:
	ASCII(.ascii	"SPS: qpprime_y_zero_trans_bypass_flag\000" )
	.space	2
.LC227:
	ASCII(.ascii	"qpprime_y_zero_trans_bypass_flag not equal 0.\012\000" )
	.space	1
.LC228:
	ASCII(.ascii	"SPS: seq_scaling_matrix_present_flag\000" )
	.space	3
.LC229:
	ASCII(.ascii	"SPS: log2_max_frame_num_minus4\000" )
	.space	1
.LC230:
	ASCII(.ascii	"pSPS->log2_max_frame_num_minus4 out of range.\012\000" )
	.space	1
.LC231:
	ASCII(.ascii	"SPS: pic_order_cnt_type\000" )
.LC232:
	ASCII(.ascii	"pSPS->pic_order_cnt_type out of range.\012\000" )
.LC233:
	ASCII(.ascii	"SPS: log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	1
.LC234:
	ASCII(.ascii	"SPS: num_ref_frames\000" )
.LC235:
	ASCII(.ascii	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of rang" )
	ASCII(.ascii	"e.\012\000" )
	.space	1
.LC236:
	ASCII(.ascii	"SPS: delta_pic_order_always_zero_flag\000" )
	.space	2
.LC237:
	ASCII(.ascii	"SPS: offset_for_non_ref_pic\000" )
.LC238:
	ASCII(.ascii	"SPS: offset_for_top_to_bottom_field\000" )
.LC239:
	ASCII(.ascii	"SPS: num_ref_frames_in_pic_order_cnt_cycle\000" )
	.space	1
.LC240:
	ASCII(.ascii	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of " )
	ASCII(.ascii	"range.\012\000" )
	.space	1
.LC241:
	ASCII(.ascii	"SPS: offset_for_ref_frame[i]\000" )
	.space	3
.LC242:
	ASCII(.ascii	"SPS: gaps_in_frame_num_value_allowed_flag\000" )
	.space	2
.LC243:
	ASCII(.ascii	"SPS: pic_width_in_mbs_minus1\000" )
	.space	3
.LC244:
	ASCII(.ascii	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC245:
	ASCII(.ascii	"SPS: pic_height_in_map_units_minus1\000" )
.LC246:
	ASCII(.ascii	"SPS: frame_mbs_only_flag\000" )
	.space	3
.LC247:
	ASCII(.ascii	"pSPS->pic_height_in_map_units_minus1 out of range.\012" )
	ASCII(.ascii	"\000" )
.LC248:
	ASCII(.ascii	"pic size too large.\012\000" )
	.space	3
.LC249:
	ASCII(.ascii	"level_idc %d not support.\012\000" )
	.space	1
.LC250:
	ASCII(.ascii	"dpb size according level : %d\012\000" )
	.space	1
.LC251:
	ASCII(.ascii	"pSPS->num_ref_frames(%d) > DPB size(%d), try to sel" )
	ASCII(.ascii	"ect the reasonable one.\012\000" )
.LC252:
	ASCII(.ascii	"SPS: direct_8x8_inference_flag\000" )
	.space	1
.LC253:
	ASCII(.ascii	"SPS: frame_cropping_flag\000" )
	.space	3
.LC254:
	ASCII(.ascii	"SPS: frame_cropping_rect_left_offset\000" )
	.space	3
.LC255:
	ASCII(.ascii	"SPS: frame_cropping_rect_right_offset\000" )
	.space	2
.LC256:
	ASCII(.ascii	"SPS: frame_cropping_rect_top_offset\000" )
.LC257:
	ASCII(.ascii	"SPS: frame_cropping_rect_bottom_offset\000" )
	.space	1
.LC258:
	ASCII(.ascii	"SPS: vui_parameters_present_flag\000" )
	.space	3
.LC259:
	ASCII(.ascii	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\012\000" )
	.space	2
.LC260:
	ASCII(.ascii	"SPS: mb_adaptive_frame_field_flag\000" )
	.space	2
.LC261:
	ASCII(.ascii	"SPS_SVC_EXT: inter_layer_deblocking_filter_control_" )
	ASCII(.ascii	"present_flag\000" )
.LC262:
	ASCII(.ascii	"inter_layer_present_flag:%d!\012\000" )
	.space	2
.LC263:
	ASCII(.ascii	"SPS_SVC_EXT: extended_spatial_scalability_idc\000" )
	.space	2
.LC264:
	ASCII(.ascii	"spatial scalability not support!!\012\000" )
	.space	1
.LC265:
	ASCII(.ascii	"SPS_SVC_EXT: chroma_phase_x_plus1_flag\000" )
	.space	1
.LC266:
	ASCII(.ascii	"chroma_phase_x_plus1_flag:%d!!\012\000" )
.LC267:
	ASCII(.ascii	"SPS_SVC_EXT: chroma_phase_y_plus1\000" )
	.space	2
.LC268:
	ASCII(.ascii	"chroma_phase_y_plus1:%d!\012\000" )
	.space	2
.LC269:
	ASCII(.ascii	"SPS_SVC_EXT: seq_tcoeff_level_prediction_flag\000" )
	.space	2
.LC270:
	ASCII(.ascii	"SPS_SVC_EXT: adaptive_tcoeff_level_prediction_flag\000" )
	.space	1
.LC271:
	ASCII(.ascii	"adaptive_tcoeff_level_prediction_flag:%d!\012\000" )
	.space	1
.LC272:
	ASCII(.ascii	"SPS_SVC_EXT: slice_header_restriction_flag\000" )
	.space	1
.LC273:
	ASCII(.ascii	"slice_header_restriction_flag error:%d,%x,%d\012\000" )
	.space	2
.LC274:
	ASCII(.ascii	"SPS: profile_idc\000" )
	.space	3
.LC275:
	ASCII(.ascii	"SPS: constrained_set0_flag\000" )
	.space	1
.LC276:
	ASCII(.ascii	"SPS: constrained_set1_flag\000" )
	.space	1
.LC277:
	ASCII(.ascii	"SPS: constrained_set2_flag\000" )
	.space	1
.LC278:
	ASCII(.ascii	"SPS: constrained_set3_flag\000" )
	.space	1
.LC279:
	ASCII(.ascii	"SPS: reserved_zero_4bits\000" )
	.space	3
.LC280:
	ASCII(.ascii	"SPS: level_idc\000" )
	.space	1
.LC281:
	ASCII(.ascii	"SPS: seq_parameter_set_id\000" )
	.space	2
.LC282:
	ASCII(.ascii	"Baseline stream, try to decode, exit when FMO occur" )
	ASCII(.ascii	"red.\012\000" )
	.space	3
.LC283:
	ASCII(.ascii	"EXTENDED stream, try to decode, exit when dataparti" )
	ASCII(.ascii	"tion occurred.\012\000" )
	.space	1
.LC284:
	ASCII(.ascii	"others High profile stream, try to decode, exit whe" )
	ASCII(.ascii	"n high profile not support occurred.\012\000" )
	.space	3
.LC285:
	ASCII(.ascii	"profile_idc = %5d error, try to decode as main prof" )
	ASCII(.ascii	"ile.\012\000" )
	.space	3
.LC286:
	ASCII(.ascii	"level_idc = %5d error, try to decode as level_idc %" )
	ASCII(.ascii	"d.\012\000" )
	.space	1
.LC287:
	ASCII(.ascii	"Line %d: SPS[%d] decode error.\012\000" )
.LC288:
	ASCII(.ascii	"svc ext error:\012\000" )
.LC289:
	ASCII(.ascii	"SEI: frame_packing_arrangement_id\000" )
	.space	2
.LC290:
	ASCII(.ascii	"SEI: frame_packing_arrangement_cancel_flag\000" )
	.space	1
.LC291:
	ASCII(.ascii	"SEI: frame_packing_arrangement_type\000" )
.LC292:
	ASCII(.ascii	"SEI: quincunx_sampling_flag\000" )
.LC293:
	ASCII(.ascii	"SEI: content_interpretation_type\000" )
	.space	3
.LC294:
	ASCII(.ascii	"SEI: spatial_flipping_flag\000" )
	.space	1
.LC295:
	ASCII(.ascii	"SEI: frame0_flipped_flag\000" )
	.space	3
.LC296:
	ASCII(.ascii	"SEI: field_views_flag\000" )
	.space	2
.LC297:
	ASCII(.ascii	"SEI: current_frame_is_frame0_flag\000" )
	.space	2
.LC298:
	ASCII(.ascii	"SEI: frame0_self_contained_flag\000" )
.LC299:
	ASCII(.ascii	"SEI: frame1_self_contained_flag\000" )
.LC300:
	ASCII(.ascii	"SEI: frame0_grid_position_x\000" )
.LC301:
	ASCII(.ascii	"SEI: frame0_grid_position_y\000" )
.LC302:
	ASCII(.ascii	"SEI: frame1_grid_position_x\000" )
.LC303:
	ASCII(.ascii	"SEI: frame1_grid_position_y\000" )
.LC304:
	ASCII(.ascii	"SEI: frame_packing_arrangement_reserved_byte\000" )
	.space	3
.LC305:
	ASCII(.ascii	"SEI: frame_packing_arrangement_repetition_period\000" )
	.space	3
.LC306:
	ASCII(.ascii	"SEI: frame_packing_arrangement_extension_flag\000" )
	.space	2
.LC307:
	ASCII(.ascii	"DecPicTimingSEI but SPS is invalid.\012\000" )
	.space	3
.LC308:
	ASCII(.ascii	"SEI: cpb_removal_delay\000" )
	.space	1
.LC309:
	ASCII(.ascii	"SEI: dpb_output_delay\000" )
	.space	2
.LC310:
	ASCII(.ascii	"pic_struct\000" )
	.space	1
.LC311:
	ASCII(.ascii	"SEI nal dec payload type err\012\000" )
	.space	2
.LC312:
	ASCII(.ascii	"SEI nal dec payloadSize err\012\000" )
	.space	3
.LC313:
	ASCII(.ascii	"SEI_BUFFERING_PERIOD,offset = %d,payload_size = %d " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC314:
	ASCII(.ascii	"PassBytes err [%s][%d]\012\000" )
.LC315:
	ASCII(.ascii	"SEI_PIC_TIMING,offset = %d,payload_size = %d \012\000" )
	.space	1
.LC316:
	ASCII(.ascii	"SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC317:
	ASCII(.ascii	"SEI_FILLER_PAYLOAD,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC318:
	ASCII(.ascii	"SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d, pa" )
	ASCII(.ascii	"yload_size = %d \012\000" )
	.space	3
.LC319:
	ASCII(.ascii	"SEI_USER_DATA_UNREGISTERED, offset = %d, payload_si" )
	ASCII(.ascii	"ze = %d \012\000" )
	.space	3
.LC320:
	ASCII(.ascii	"SEI: itu_t_t35_country_code\000" )
.LC321:
	ASCII(.ascii	"SEI: itu_t_t35_country_code_extension_byte\000" )
	.space	1
.LC322:
	ASCII(.ascii	"SEI: itu_t_t35_provider_code\000" )
	.space	3
.LC323:
	ASCII(.ascii	"len_tmp = %d cann't dec usrdata\012\000" )
	.space	3
.LC324:
	ASCII(.ascii	"cann't dec usrdata\012\000" )
.LC325:
	ASCII(.ascii	"SEI_RECOVERY_POINT,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC326:
	ASCII(.ascii	"SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d,payl" )
	ASCII(.ascii	"oad_size = %d \012\000" )
	.space	1
.LC327:
	ASCII(.ascii	"SEI_SPARE_PIC,offset = %d,payload_size = %d \012\000" )
	.space	2
.LC328:
	ASCII(.ascii	"SEI_SCENE_INFO,offset = %d,payload_size = %d \012\000" )
	.space	1
.LC329:
	ASCII(.ascii	"SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC330:
	ASCII(.ascii	"SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,paylo" )
	ASCII(.ascii	"ad_size = %d \012\000" )
	.space	2
.LC331:
	ASCII(.ascii	"SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload_siz" )
	ASCII(.ascii	"e = %d \012\000" )
.LC332:
	ASCII(.ascii	"SEI_FULL_FRAME_FREEZE,offset = %d,payload_size = %d" )
	ASCII(.ascii	" \012\000" )
	.space	2
.LC333:
	ASCII(.ascii	"SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,payload_s" )
	ASCII(.ascii	"ize = %d \012\000" )
	.space	2
.LC334:
	ASCII(.ascii	"SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_size = " )
	ASCII(.ascii	"%d \012\000" )
.LC335:
	ASCII(.ascii	"SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset = %" )
	ASCII(.ascii	"d,payload_size = %d \012\000" )
	.space	3
.LC336:
	ASCII(.ascii	"SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset = %d," )
	ASCII(.ascii	"payload_size = %d \012\000" )
	.space	1
.LC337:
	ASCII(.ascii	"SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset = %d," )
	ASCII(.ascii	"payload_size = %d \012\000" )
	.space	1
.LC338:
	ASCII(.ascii	"SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payload_" )
	ASCII(.ascii	"size = %d \012\000" )
	.space	1
.LC339:
	ASCII(.ascii	"SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset = %" )
	ASCII(.ascii	"d,payload_size = %d \012\000" )
	.space	3
.LC340:
	ASCII(.ascii	"SEI_STEREO_VIDEO_INFO,offset = %d,payload_size = %d" )
	ASCII(.ascii	" \012\000" )
	.space	2
.LC341:
	ASCII(.ascii	"too much usrdat, cann't dec SEI\012\000" )
	.space	3
.LC342:
	ASCII(.ascii	"\012the stream is error,len:%d\012\000" )
	.space	3
.LC343:
	ASCII(.ascii	"\012\012END of the bit buffer, copy the first packe" )
	ASCII(.ascii	"t!\012\012\000" )
	.space	2
.LC344:
	ASCII(.ascii	"0:phy:0x%x, 1:phy:0x%x; len0:%d len1:%d\012\000" )
	.space	3
.LC345:
	ASCII(.ascii	"0:phy:0x%x, len0:%d\012\000" )
	.space	3
.LC346:
	ASCII(.ascii	"\012Slice nal or IDR nal = %d\012\000" )
.LC347:
	ASCII(.ascii	"sliceheader dec err\012\000" )
	.space	3
.LC348:
	ASCII(.ascii	"H264Dec destroy\012\000" )
	.space	3
.LC349:
	ASCII(.ascii	"H264 recycle image\012\000" )
.LC350:
	ASCII(.ascii	"pH264Ctx is %p, pFrameStore is %p\012\000" )
	.space	1
.LC351:
	ASCII(.ascii	"line; %d pstLogicFsImage is NULL!\012\000" )
	.space	1
.LC352:
	ASCII(.ascii	"InsertVO err:%d, ClearAll\012\000" )
	.space	1
.LC353:
	ASCII(.ascii	"H264.c line %d: frame para err(ret=%d), recycle ima" )
	ASCII(.ascii	"ge self\012\000" )
.LC354:
	ASCII(.ascii	"line: %d pstLogicFsImage is NULL!\012\000" )
	.space	1
.LC355:
	ASCII(.ascii	"[%s][%d] OutputFrmToVO return %d\012\000" )
	.space	2
.LC356:
	ASCII(.ascii	"clear all dec para\012\000" )
.LC357:
	ASCII(.ascii	"FS_ALLOC_ERR, ClearAll\012\000" )
.LC358:
	ASCII(.ascii	"Can not new logic fs! ClearAll\012\000" )
.LC359:
	ASCII(.ascii	"%s %d unknow error!!\012\000" )
	.space	2
.LC360:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC361:
	ASCII(.ascii	"line %d: flush dpb return %d\012\000" )
	.space	2
.LC362:
	ASCII(.ascii	"[%s %d], pos is %d out of range\012\000" )
	.space	3
.LC363:
	ASCII(.ascii	"line %d, get APC error, ret %d\012\000" )
.LC364:
	ASCII(.ascii	"InserFrmInDPB: cur pic struct = %d!\012\000" )
	.space	3
.LC365:
	ASCII(.ascii	"----------------- Imode -> %d ------------------\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC366:
	ASCII(.ascii	"I_MODE but first_mb_in_slice != 0\012\000" )
	.space	1
.LC367:
	ASCII(.ascii	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\012\000" )
.LC368:
	ASCII(.ascii	"***** VDM start, TotalPicNum=%d, pH264Ctx->CurrPic." )
	ASCII(.ascii	"structure=%d.\012\000" )
	.space	2
.LC369:
	ASCII(.ascii	"DecVDM ERR\012\000" )
.LC370:
	ASCII(.ascii	"%s:%d Metadata map failed\012\000" )
	.space	1
.LC371:
	ASCII(.ascii	"%s:%d Metadata unmap failed\012\000" )
	.space	3
.LC372:
	ASCII(.ascii	"*****[%s][%d],EL Codec can only dec EL stream in DV" )
	ASCII(.ascii	"_DUAL_VES_IMP stream!!*****\012\000" )
.LC373:
	ASCII(.ascii	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC374:
	ASCII(.ascii	"\012 receive streambuff=%p; phy_addr=0x%x; bitstrea" )
	ASCII(.ascii	"m_length=%d\012\000" )
	.space	3
.LC375:
	ASCII(.ascii	"nal_release_err\012\000" )
	.space	3
.LC376:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC377:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC378:
	ASCII(.ascii	"CurrPic.state is 'EMPTY'\012\000" )
	.space	2
.LC379:
	ASCII(.ascii	"StorePicInDPB return(%d) from L%d\012\000" )
	.space	1
.LC380:
	ASCII(.ascii	"directoutput mode\012\000" )
	.space	1
.LC381:
	ASCII(.ascii	"line: %d pImg is NULL!\012\000" )
.LC382:
	ASCII(.ascii	"line %d, REPORT_IFRAME_ERR\012\000" )
.LC383:
	ASCII(.ascii	"line %d, return %d\012\000" )
.LC384:
	ASCII(.ascii	"err(%d) > ref_thr(%d)\012\000" )
	.space	1
.LC385:
	ASCII(.ascii	"marking return %d\012\000" )
	.space	1
.LC386:
	ASCII(.ascii	"return value is unexpeced!\012\000" )
.LC387:
	ASCII(.ascii	"line %d: pH264Ctx->DPB.size = %d, ref %d, ltref %d\012" )
	ASCII(.ascii	"\000" )
.LC388:
	ASCII(.ascii	"%s: pos(%d) = pre_pos, force return.\012\000" )
	.space	2
.LC389:
	ASCII(.ascii	"GAP found while DPB is empty!\012\000" )
	.space	1
.LC390:
	ASCII(.ascii	"frame num gap try to fill it \012\000" )
	.space	1
.LC391:
	ASCII(.ascii	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC392:
	ASCII(.ascii	"cann't allocate frame store when gap find\012\000" )
	.space	1
.LC393:
	ASCII(.ascii	"allocate frame store when gap find\012\000" )
.LC394:
	ASCII(.ascii	"line %d: store gap pic err, ret=%d\012\000" )
.LC395:
	ASCII(.ascii	"%s %d frame_store is null!!\012\000" )
	.space	3
.LC396:
	ASCII(.ascii	"line %d: init dpb return %d\012\000" )
	.space	3
.LC397:
	ASCII(.ascii	"mem arrange err, ClearAll\012\000" )
	.space	1
.LC398:
	ASCII(.ascii	"line %d: frame gap(=%d) > dpb size(=%d)\012\000" )
	.space	3
.LC399:
	ASCII(.ascii	"line %d: dec gap failed\012\000" )
	.space	3
.LC400:
	ASCII(.ascii	"line %d: alloc framestore failed\012\000" )
	.space	2
.LC401:
	ASCII(.ascii	"dec_pts: %lld\012\000" )
	.space	1
.LC402:
	ASCII(.ascii	"dec_usertag: %lld\012\000" )
	.space	1
.LC403:
	ASCII(.ascii	"%s %d NULL == pH264Ctx->CurrPic.frame_store!!\012\000" )
	.space	1
.LC404:
	ASCII(.ascii	"get back frm\012\000" )
	.space	2
.LC405:
	ASCII(.ascii	"Start Reason: SliceParaNum, MaxBytesReceived = %d, " )
	ASCII(.ascii	"%d(thr=%d)\012\000" )
	.space	1
.LC406:
	ASCII(.ascii	"Too many slice or bitstream, err!\012\000" )
	.space	1
.LC407:
	ASCII(.ascii	"Start Reason: new_pic_flag\012\000" )
.LC408:
	ASCII(.ascii	"init pic err, find next recover point or next valid" )
	ASCII(.ascii	" sps, pps, or exit\012\000" )
	.space	1
.LC409:
	ASCII(.ascii	"DecList error, ret=%d\012\000" )
	.space	1
.LC410:
	ASCII(.ascii	"dec list err, cur pic poc %d.\012\000" )
	.space	1
.LC411:
	ASCII(.ascii	"pH264Ctx->TotalNal = %d, type:%d\012\000" )
	.space	2
.LC412:
	ASCII(.ascii	"stop i want\012\000" )
	.space	3
.LC413:
	ASCII(.ascii	"svc_extension_flag error:priority_id:%d, pred_flag%" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC414:
	ASCII(.ascii	"%d,%d,%d\012\000" )
	.space	2
.LC415:
	ASCII(.ascii	"svc stream,nal_header:%x\012\000" )
	.space	2
.LC416:
	ASCII(.ascii	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC417:
	ASCII(.ascii	"SliceCheck failed, clear current slice.\012\000" )
	.space	3
.LC418:
	ASCII(.ascii	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\012\000" )
	.space	1
.LC419:
	ASCII(.ascii	"%s: PPS decode error.\012\000" )
	.space	1
.LC420:
	ASCII(.ascii	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\012\000" )
	.space	1
.LC421:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC422:
	ASCII(.ascii	"***** NAL: SEI, nal_unit_type=%d\012\000" )
	.space	2
.LC423:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC424:
	ASCII(.ascii	"***** NAL: AUD, nal_unit_type=%d\012\000" )
	.space	2
.LC425:
	ASCII(.ascii	"***** NAL: EOSEQ, nal_unit_type=%d\012\000" )
.LC426:
	ASCII(.ascii	"***** NAL: FILL, nal_unit_type=%d\012\000" )
	.space	1
.LC427:
	ASCII(.ascii	"***** NAL: EOSTREAM, nal_unit_type=%d\012\000" )
	.space	1
.LC428:
	ASCII(.ascii	"***** NAL: SPSEXT, nal_unit_type=%d\012\000" )
	.space	3
.LC429:
	ASCII(.ascii	"***** NAL: AUX, nal_unit_type=%d\012\000" )
	.space	2
.LC430:
	ASCII(.ascii	"***** NAL: EOPIC, nal_unit_type=%d\012\000" )
.LC431:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC432:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d\012\000" )
.LC433:
	ASCII(.ascii	"FindTrailZeros ERR\012\000" )
.LC434:
	ASCII(.ascii	"H264_DecOneNal ERR\012\000" )
.LC435:
	ASCII(.ascii	"pH264Ctx->CurrPic.frame_store is null pointer\012\000" )
	.space	1
.LC436:
	ASCII(.ascii	"store pic err, ret = %d\012\000" )
	.space	3
.LC437:
	ASCII(.ascii	"imode nal store pic err, ret = %d\012\000" )
	.space	1
.LC438:
	ASCII(.ascii	"imode nal flush dpb err, ret = %d\012\000" )
	.space	1
.LC439:
	ASCII(.ascii	"cann't find FrameStore\012\000" )
.LC440:
	ASCII(.ascii	"========== H264 FrameStore state(is_used, is_in_dpb" )
	ASCII(.ascii	", IsOutDPB) ========\012\000" )
	.space	3
.LC441:
	ASCII(.ascii	"ReadImgNum = %d, NewImgNum = %d\012\000" )
	.space	3
.LC442:
	ASCII(.ascii	"%02d: %d %d %d\012\000" )
.LC443:
	ASCII(.ascii	"FrameStore leak, ClearAll\012\000" )
	.bss
	.align	2
.LANCHOR2 = . + 0
.LANCHOR3 = . + 8184
	.type	pps_tmp.14904, %object
	.size	pps_tmp.14904, 2208
pps_tmp.14904:
	.space	2208
	.type	sps_tmp.15025, %object
	.size	sps_tmp.15025, 4000
sps_tmp.15025:
	.space	4000
	.type	TmpBuf, %object
	.size	TmpBuf, 68
TmpBuf:
	.space	68
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
