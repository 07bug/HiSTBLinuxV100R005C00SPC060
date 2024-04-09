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
	.file	"mvc.c"
	.text
	.align	2
	.global	MVC_IsSTRefFlg
	.type	MVC_IsSTRefFlg, %function
MVC_IsSTRefFlg:
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
	.size	MVC_IsSTRefFlg, .-MVC_IsSTRefFlg
	.align	2
	.global	MVC_IsLTRefFlg
	.type	MVC_IsLTRefFlg, %function
MVC_IsLTRefFlg:
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
	.size	MVC_IsLTRefFlg, .-MVC_IsLTRefFlg
	.align	2
	.global	MVC_compare_pic_by_pic_num_desc
	.type	MVC_compare_pic_by_pic_num_desc, %function
MVC_compare_pic_by_pic_num_desc:
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
	blt	.L5
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L5:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_pic_by_pic_num_desc, .-MVC_compare_pic_by_pic_num_desc
	.align	2
	.global	MVC_compare_pic_by_lt_pic_num_asc
	.type	MVC_compare_pic_by_lt_pic_num_asc, %function
MVC_compare_pic_by_lt_pic_num_asc:
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
	blt	.L9
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L9:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_pic_by_lt_pic_num_asc, .-MVC_compare_pic_by_lt_pic_num_asc
	.align	2
	.global	MVC_compare_fs_by_frame_num_desc
	.type	MVC_compare_fs_by_frame_num_desc, %function
MVC_compare_fs_by_frame_num_desc:
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
	ldr	r2, [r2, #24]
	ldr	r3, [r3, #24]
	cmp	r2, r3
	blt	.L12
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L12:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_fs_by_frame_num_desc, .-MVC_compare_fs_by_frame_num_desc
	.align	2
	.global	MVC_compare_fs_by_lt_pic_idx_asc
	.type	MVC_compare_fs_by_lt_pic_idx_asc, %function
MVC_compare_fs_by_lt_pic_idx_asc:
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
	ldr	r2, [r2, #28]
	ldr	r3, [r3, #28]
	cmp	r2, r3
	bcc	.L15
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L15:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_fs_by_lt_pic_idx_asc, .-MVC_compare_fs_by_lt_pic_idx_asc
	.align	2
	.global	MVC_compare_pic_by_poc_asc
	.type	MVC_compare_pic_by_poc_asc, %function
MVC_compare_pic_by_poc_asc:
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
	ldr	r2, [r2, #16]
	ldr	r3, [r3, #16]
	cmp	r2, r3
	blt	.L18
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L18:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_pic_by_poc_asc, .-MVC_compare_pic_by_poc_asc
	.align	2
	.global	MVC_compare_pic_by_poc_desc
	.type	MVC_compare_pic_by_poc_desc, %function
MVC_compare_pic_by_poc_desc:
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
	ldr	r2, [r2, #16]
	ldr	r3, [r3, #16]
	cmp	r2, r3
	blt	.L21
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L21:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_pic_by_poc_desc, .-MVC_compare_pic_by_poc_desc
	.align	2
	.global	MVC_compare_fs_by_poc_asc
	.type	MVC_compare_fs_by_poc_asc, %function
MVC_compare_fs_by_poc_asc:
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
	ldr	r2, [r2, #32]
	ldr	r3, [r3, #32]
	cmp	r2, r3
	blt	.L24
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L24:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_fs_by_poc_asc, .-MVC_compare_fs_by_poc_asc
	.align	2
	.global	MVC_compare_fs_by_poc_desc
	.type	MVC_compare_fs_by_poc_desc, %function
MVC_compare_fs_by_poc_desc:
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
	ldr	r2, [r2, #32]
	ldr	r3, [r3, #32]
	cmp	r2, r3
	blt	.L27
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_compare_fs_by_poc_desc, .-MVC_compare_fs_by_poc_desc
	.align	2
	.type	MVC_SetFrmRepeatCount.part.1, %function
MVC_SetFrmRepeatCount.part.1:
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
	add	ip, r0, #11075584
	ldr	lr, [r0, #136]
	add	ip, ip, #45056
	ldr	r3, [r0, #132]
	ldr	r2, [ip, #2376]
	mov	r3, r3, lsr #1
	add	r2, r2, lr, lsr #1
	add	ip, r2, #1
	cmp	r3, ip
	movcc	r3, #0
	strcc	r3, [r1, #84]
	ldmccfd	sp, {fp, sp, pc}
	sub	r3, r3, #1
	rsb	r3, r2, r3
	cmp	r3, #1
	movhi	r3, #2
	movls	r3, #1
	strhi	r3, [r1, #84]
	strls	r3, [r1, #84]
	ldrhi	r3, [r0, #136]
	ldrls	r3, [r0, #136]
	addhi	r3, r3, #4
	addls	r3, r3, #2
	str	r3, [r0, #136]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_SetFrmRepeatCount.part.1, .-MVC_SetFrmRepeatCount.part.1
	.align	2
	.type	MVC_CombinePacket.part.10, %function
MVC_CombinePacket.part.10:
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
	ldr	r6, .L33
	mov	r4, r0
	ldr	r1, .L33+4
	mov	r0, #7
	mov	r5, #0
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r1, [r4, #232]
	ldr	r7, [r6, #68]
	mov	r0, #7
	ldr	ip, [r1, #40]
	ldr	r3, [r1, #44]
	ldr	r2, [r1, #16]
	str	ip, [sp, #4]
	ldr	ip, [r1, #12]
	ldr	r1, .L33+8
	str	ip, [sp]
	blx	r7
	ldr	r3, [r4, #232]
	ldr	r7, [r6, #52]
	ldr	r2, [r3, #12]
	ldr	r0, [r3, #36]
	ldr	r1, [r3, #8]
	rsb	r0, r2, r0
	blx	r7
	ldr	r3, [r4, #232]
	mov	ip, #1
	ldr	r1, .L33+12
	mov	r0, #7
	ldr	r2, [r3, #60]
	ldr	r7, [r3, #32]
	str	r2, [r3, #32]
	ldr	r3, [r4, #232]
	str	r5, [r3, #24]
	ldr	r3, [r4, #232]
	ldr	lr, [r3, #12]
	ldr	r2, [r3, #36]
	rsb	r2, lr, r2
	str	r2, [r3, #8]
	ldr	r3, [r4, #232]
	ldr	lr, [r3, #12]
	ldr	r2, [r3, #44]
	rsb	r2, lr, r2
	str	r2, [r3, #16]
	ldr	r3, [r4, #232]
	ldr	lr, [r3, #40]
	ldr	r2, [r3, #12]
	add	r2, r2, lr
	str	r2, [r3, #12]
	ldr	r3, [r4, #232]
	str	ip, [r3, #68]
	ldr	r2, [r4, #232]
	ldr	r6, [r6, #68]
	ldr	r3, [r2, #12]
	ldr	r2, [r2, #16]
	blx	r6
	mov	r1, r7
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #232]
	str	r5, [r3, #36]
	ldr	r3, [r4, #232]
	str	r5, [r3, #52]
	ldr	r3, [r4, #232]
	str	r5, [r3, #40]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L34:
	.align	2
.L33:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	MVC_CombinePacket.part.10, .-MVC_CombinePacket.part.10
	.align	2
	.global	mvc_ue_v
	.type	mvc_ue_v, %function
mvc_ue_v:
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
	add	r8, r0, #548
	mov	r6, r0
	mov	r7, r1
	mov	r1, #32
	mov	r0, r8
	bl	BsShow
	mov	r5, r0
	bl	ZerosMS_32
	cmp	r0, #15
	mov	r4, r0
	bls	.L39
	cmp	r0, #31
	bls	.L40
	mvn	r5, #0
	mov	r8, #32
	mov	r3, #1
	strb	r3, [r6, #10]
.L37:
	ldr	lr, [r6, #232]
	mov	r2, r7
	ldr	r6, .L41
	mov	r3, r5
	ldr	r1, .L41+4
	mov	r0, #21
	ldr	ip, [lr, #64]
	add	r4, ip, r8
	str	r4, [lr, #64]
	ldr	r4, [r6, #68]
	blx	r4
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L39:
	mov	r4, r0, asl #1
	mov	r0, r8
	add	r8, r4, #1
	rsb	r4, r4, #31
	mov	r4, r5, lsr r4
	mov	r1, r8
	sub	r5, r4, #1
	bl	BsSkip
	b	.L37
.L40:
	add	r5, r0, #1
	mov	r1, r0
	mov	r0, r8
	bl	BsSkip
	mov	r1, r5
	mov	r0, r8
	bl	BsShow
	mov	r1, r5
	sub	r5, r0, #1
	mov	r0, r8
	bl	BsSkip
	mov	r3, r4, asl #1
	add	r8, r3, #1
	b	.L37
.L42:
	.align	2
.L41:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	UNWIND(.fnend)
	.size	mvc_ue_v, .-mvc_ue_v
	.align	2
	.global	mvc_se_v
	.type	mvc_se_v, %function
mvc_se_v:
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
	add	r8, r0, #548
	mov	r6, r0
	mov	r7, r1
	mov	r1, #32
	mov	r0, r8
	bl	BsShow
	mov	r4, r0
	bl	ZerosMS_32
	cmp	r0, #15
	mov	r5, r0
	bhi	.L44
	mov	r5, r0, asl #1
	mov	r0, r8
	rsb	r3, r5, #31
	add	r5, r5, #1
	mov	r3, r4, lsr r3
	and	r2, r3, #1
	mov	r1, r5
	rsb	r4, r2, #0
	eor	r4, r4, r3, lsr #1
	add	r4, r4, r2
	bl	BsSkip
.L45:
	ldr	lr, [r6, #232]
	mov	r2, r7
	ldr	r6, .L48
	mov	r3, r4
	ldr	r1, .L48+4
	mov	r0, #21
	ldr	ip, [lr, #64]
	add	r5, ip, r5
	str	r5, [lr, #64]
	ldr	r5, [r6, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L44:
	cmp	r0, #31
	bls	.L47
	mov	r3, #1
	mvn	r4, #-2147483648
	mov	r5, #32
	strb	r3, [r6, #10]
	b	.L45
.L47:
	mov	r1, r0
	mov	r0, r8
	bl	BsSkip
	mov	r1, r5
	mov	r0, r8
	mov	r5, r5, asl #1
	bl	BsGet
	mov	r1, #1
	add	r5, r5, #1
	mov	r9, r0
	mov	r0, r8
	bl	BsGet
	and	r0, r0, #1
	rsb	r4, r0, #0
	eor	r9, r9, r4
	add	r4, r9, r0
	b	.L45
.L49:
	.align	2
.L48:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	UNWIND(.fnend)
	.size	mvc_se_v, .-mvc_se_v
	.align	2
	.global	mvc_u_v
	.type	mvc_u_v, %function
mvc_u_v:
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
	add	r0, r0, #548
	mov	r6, r1
	mov	r7, r2
	bl	BsGet
	ldr	lr, [r5, #232]
	ldr	r5, .L51
	mov	r2, r7
	ldr	r1, .L51+4
	ldr	ip, [lr, #64]
	add	ip, ip, r6
	str	ip, [lr, #64]
	ldr	r5, [r5, #68]
	mov	r4, r0
	mov	r3, r0
	mov	r0, #21
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L52:
	.align	2
.L51:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	UNWIND(.fnend)
	.size	mvc_u_v, .-mvc_u_v
	.align	2
	.global	mvc_u_1
	.type	mvc_u_1, %function
mvc_u_1:
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
	mov	r6, r1
	add	r0, r0, #548
	mov	r1, #1
	bl	BsGet
	ldr	lr, [r5, #232]
	ldr	r5, .L54
	mov	r2, r6
	ldr	r1, .L54+4
	ldr	ip, [lr, #64]
	add	ip, ip, #1
	str	ip, [lr, #64]
	ldr	r5, [r5, #68]
	mov	r4, r0
	mov	r3, r0
	mov	r0, #21
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L55:
	.align	2
.L54:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	UNWIND(.fnend)
	.size	mvc_u_1, .-mvc_u_1
	.align	2
	.global	MVC_GetMinPOC
	.type	MVC_GetMinPOC, %function
MVC_GetMinPOC:
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
	add	r4, r0, #11075584
	add	r4, r4, #45056
	mov	r8, r3
	mov	r7, r2
	mvn	r3, #-2147483648
	mvn	r2, #0
	str	r2, [r8]
	str	r3, [r7]
	mov	r5, r0
	ldr	r3, [r4, #2376]
	mov	r6, r1
	ldr	r2, [r4, #2380]
	cmp	r2, r3
	strhi	r3, [r4, #2380]
	cmp	r3, #0
	beq	.L63
	movw	r9, #47236
	mvn	r3, #0
	movt	r9, 169
	str	r3, [fp, #-48]
	add	r9, r0, r9
	mov	r10, #0
	b	.L62
.L60:
	ldr	lr, [r7]
	ldr	ip, [r1, #32]
	cmp	lr, ip
	ble	.L59
	ldrb	ip, [r1, #5]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L59
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	sub	r0, r0, #1
	cmp	r0, #1
	bls	.L78
.L59:
	ldr	r1, [r4, #2376]
	add	r10, r10, #1
	cmp	r1, r10
	bls	.L63
.L62:
	ldr	r1, [r9, #4]!
	cmp	r1, #0
	beq	.L59
	ldrsb	r1, [r1, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L59
	cmn	r6, #1
	ldr	r1, [r9]
	bne	.L60
	ldrb	ip, [r1, #5]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L59
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	sub	r0, r0, #1
	cmp	r0, #1
	bhi	.L59
	ldr	ip, [r7]
	ldr	r0, [r1, #32]
	cmp	ip, r0
	bgt	.L79
	bne	.L59
	ldr	r1, [r1, #56]
	ldr	r3, [fp, #-48]
	cmp	r1, r3
	strlt	r10, [r8]
	ldrlt	r1, [r9]
	ldrlt	r3, [r1, #56]
	strlt	r3, [fp, #-48]
	b	.L59
.L63:
	ldr	r0, [r8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L78:
	ldr	r1, [r1, #56]
	cmp	r6, r1
	bne	.L59
	ldr	r3, .L80
	ldr	r1, [r3, #112]
	blx	r1
	ldr	r1, [r9]
	ldr	r1, [r1, #32]
	str	r1, [r7]
	str	r10, [r8]
	b	.L59
.L79:
	ldr	r3, .L80
	ldr	r1, [r3, #112]
	blx	r1
	ldr	r1, [r9]
	ldr	r1, [r1, #32]
	str	r1, [r7]
	str	r10, [r8]
	ldr	r1, [r9]
	ldr	r3, [r1, #56]
	str	r3, [fp, #-48]
	b	.L59
.L81:
	.align	2
.L80:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MVC_GetMinPOC, .-MVC_GetMinPOC
	.align	2
	.global	MVC_FrameStoreRefFlg
	.type	MVC_FrameStoreRefFlg, %function
MVC_FrameStoreRefFlg:
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
	ldrb	r0, [r0, #3]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FrameStoreRefFlg, .-MVC_FrameStoreRefFlg
	.align	2
	.global	MVC_NonLongTermRefFlg
	.type	MVC_NonLongTermRefFlg, %function
MVC_NonLongTermRefFlg:
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
	cmp	r3, #3
	beq	.L98
	tst	r3, #1
	bne	.L99
.L87:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L91
.L88:
	ldrb	r0, [r0, #649]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L91:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L99:
	ldrb	r2, [r0, #613]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L87
.L92:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L98:
	ldrb	r3, [r0, #577]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L92
	ldrb	r3, [r0, #613]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L88
	b	.L92
	UNWIND(.fnend)
	.size	MVC_NonLongTermRefFlg, .-MVC_NonLongTermRefFlg
	.align	2
	.global	MVC_ShortTermRefFlg
	.type	MVC_ShortTermRefFlg, %function
MVC_ShortTermRefFlg:
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
	cmp	r3, #3
	beq	.L115
	tst	r3, #1
	bne	.L116
.L104:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L108
.L105:
	ldr	r0, [r0, #648]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #65536
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L108:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L116:
	ldr	r2, [r0, #612]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #65536
	bne	.L104
.L109:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L115:
	ldr	r3, [r0, #576]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L109
	ldr	r3, [r0, #612]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	bne	.L105
	b	.L109
	UNWIND(.fnend)
	.size	MVC_ShortTermRefFlg, .-MVC_ShortTermRefFlg
	.align	2
	.global	MVC_LongTermRefFlg
	.type	MVC_LongTermRefFlg, %function
MVC_LongTermRefFlg:
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
	cmp	r3, #3
	beq	.L132
	tst	r3, #1
	bne	.L133
.L121:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L125
.L122:
	ldr	r0, [r0, #648]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #256
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L125:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L133:
	ldr	r2, [r0, #612]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #256
	bne	.L121
.L126:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L132:
	ldr	r3, [r0, #576]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L126
	ldr	r3, [r0, #612]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	bne	.L122
	b	.L126
	UNWIND(.fnend)
	.size	MVC_LongTermRefFlg, .-MVC_LongTermRefFlg
	.align	2
	.global	MVC_UpdateLTReflist
	.type	MVC_UpdateLTReflist, %function
MVC_UpdateLTReflist:
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
	add	r3, r0, #11075584
	add	r3, r3, #45056
	mov	r7, r0
	str	r3, [fp, #-48]
	ldr	r10, [r3, #2376]
	cmp	r10, #0
	beq	.L135
	movw	r8, #47236
	add	r9, r0, #11141120
	movt	r8, 169
	mov	r4, #0
	add	r9, r9, #8192
	add	r8, r0, r8
	mov	r6, r4
.L137:
	ldr	r5, [r8, #4]!
	add	r6, r6, #1
	cmp	r5, #0
	mov	r0, r5
	beq	.L136
	bl	MVC_LongTermRefFlg
	cmp	r0, #0
	beq	.L136
	ldr	r2, [r9, #2192]
	ldr	r1, [r5, #56]
	cmp	r1, r2
	movweq	r2, #28226
	movteq	r2, 42
	addeq	r2, r4, r2
	addeq	r4, r4, #1
	streq	r5, [r7, r2, asl #2]
.L136:
	cmp	r6, r10
	bne	.L137
	ldr	r3, [fp, #-48]
	cmp	r4, r10
	str	r4, [r3, #2388]
	bcs	.L134
	movw	r0, #28225
	mov	r2, #0
	movt	r0, 42
	add	r0, r4, r0
	add	r0, r7, r0, lsl #2
.L140:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r10
	bne	.L140
.L134:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L135:
	ldr	r3, [fp, #-48]
	str	r10, [r3, #2388]
	b	.L134
	UNWIND(.fnend)
	.size	MVC_UpdateLTReflist, .-MVC_UpdateLTReflist
	.align	2
	.global	MVC_UpdateReflist
	.type	MVC_UpdateReflist, %function
MVC_UpdateReflist:
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
	add	r3, r0, #11075584
	add	r3, r3, #45056
	mov	r7, r0
	str	r3, [fp, #-48]
	ldr	r10, [r3, #2376]
	cmp	r10, #0
	beq	.L151
	movw	r8, #47236
	add	r9, r0, #11141120
	movt	r8, 169
	mov	r4, #0
	add	r9, r9, #8192
	add	r8, r0, r8
	mov	r6, r4
.L153:
	ldr	r5, [r8, #4]!
	add	r6, r6, #1
	cmp	r5, #0
	mov	r0, r5
	beq	.L152
	bl	MVC_ShortTermRefFlg
	cmp	r0, #0
	beq	.L152
	ldr	r2, [r9, #2192]
	ldr	r1, [r5, #56]
	cmp	r1, r2
	movweq	r2, #28210
	movteq	r2, 42
	addeq	r2, r4, r2
	addeq	r4, r4, #1
	streq	r5, [r7, r2, asl #2]
.L152:
	cmp	r6, r10
	bne	.L153
	ldr	r3, [fp, #-48]
	cmp	r4, r10
	str	r4, [r3, #2384]
	bcs	.L150
	movw	r0, #28209
	mov	r2, #0
	movt	r0, 42
	add	r0, r4, r0
	add	r0, r7, r0, lsl #2
.L156:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r10
	bne	.L156
.L150:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L151:
	ldr	r3, [fp, #-48]
	str	r10, [r3, #2384]
	b	.L150
	UNWIND(.fnend)
	.size	MVC_UpdateReflist, .-MVC_UpdateReflist
	.align	2
	.global	MVC_GetPicNumX
	.type	MVC_GetPicNumX, %function
MVC_GetPicNumX:
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
	ldr	r3, [r0, #528]
	mvn	r0, r1
	movne	r3, r3, asl #1
	addne	r3, r3, #1
	add	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetPicNumX, .-MVC_GetPicNumX
	.align	2
	.global	MVC_UnMarkFrameStoreRef
	.type	MVC_UnMarkFrameStoreRef, %function
MVC_UnMarkFrameStoreRef:
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
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	mov	r3, r1
	tst	r2, #1
	beq	.L170
	ldrb	r1, [r1, #3]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r3, #613]
	and	r1, r1, #2
	strb	ip, [r3, #614]
	strb	r1, [r3, #3]
.L170:
	tst	r2, #2
	beq	.L171
	ldrb	r1, [r3, #3]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r3, #649]
	and	r1, r1, #1
	strb	ip, [r3, #650]
	strb	r1, [r3, #3]
.L171:
	cmp	r2, #3
	ldrsb	r1, [r3, #6]
	moveq	r2, #0
	streqb	r2, [r3, #578]
	streqb	r2, [r3, #577]
	mov	r2, #0
	strb	r2, [r3, #3]
	ldr	r0, [r0, #120]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetRef
	UNWIND(.fnend)
	.size	MVC_UnMarkFrameStoreRef, .-MVC_UnMarkFrameStoreRef
	.align	2
	.global	MVC_UnMarkLTFrmByFrmIdx
	.type	MVC_UnMarkLTFrmByFrmIdx, %function
MVC_UnMarkLTFrmByFrmIdx:
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
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	r4, [r3, #2388]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, fp, sp, pc}
	movw	ip, #47364
	add	r6, r0, #11141120
	movt	ip, 169
	add	r6, r6, #8192
	add	ip, r0, ip
	mov	r3, #0
	b	.L182
.L181:
	cmp	r3, r4
	beq	.L187
.L182:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r2, #28]
	cmp	lr, r1
	bne	.L181
	ldr	r5, [r2, #56]
	ldr	lr, [r6, #2192]
	cmp	r5, lr
	bne	.L181
	mov	r1, r2
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L187:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkLTFrmByFrmIdx, .-MVC_UnMarkLTFrmByFrmIdx
	.align	2
	.global	MVC_UnMarkLTFldByFrmIdx
	.type	MVC_UnMarkLTFldByFrmIdx, %function
MVC_UnMarkLTFldByFrmIdx:
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
	add	ip, r0, #11075584
	add	ip, ip, #45056
	ldr	r6, [ip, #2388]
	cmp	r6, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	movw	r4, #47364
	add	r8, r0, #11141120
	movt	r4, 169
	add	r8, r8, #8192
	add	r4, r0, r4
	mov	ip, #0
	b	.L192
.L190:
	cmp	ip, r6
	beq	.L206
.L192:
	ldr	lr, [r4, #4]!
	add	ip, ip, #1
	ldr	r5, [lr, #28]
	cmp	r5, r3
	bne	.L190
	ldr	r7, [lr, #56]
	ldr	r5, [r8, #2192]
	cmp	r7, r5
	bne	.L190
	cmp	r2, #1
	ldreqb	r5, [lr, #649]	@ zero_extendqisi2
	beq	.L205
	cmp	r2, #2
	bne	.L190
	ldrb	r5, [lr, #613]	@ zero_extendqisi2
.L205:
	clz	r5, r5
	mov	r5, r5, lsr #5
	cmp	lr, r1
	orrne	r5, r5, #1
	cmp	r5, #0
	beq	.L190
	mov	r1, lr
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L206:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkLTFldByFrmIdx, .-MVC_UnMarkLTFldByFrmIdx
	.align	2
	.global	MVC_UnMarkSTRef
	.type	MVC_UnMarkSTRef, %function
MVC_UnMarkSTRef:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L208
	add	ip, r0, #11075584
	ldr	r1, [r1, #528]
	add	ip, ip, #45056
	sub	r1, r1, #1
	ldr	r4, [ip, #2384]
	rsb	r2, r2, r1
	cmp	r4, #0
	beq	.L237
	movw	ip, #47300
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #8192
	add	ip, r0, ip
	b	.L214
.L213:
	cmp	r3, r4
	beq	.L238
.L214:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #588]
	cmp	lr, r2
	bne	.L213
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L213
	ldr	lr, [r1, #576]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L213
	ldr	r6, [r1, #56]
	ldr	lr, [r5, #2192]
	cmp	r6, lr
	bne	.L213
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L208:
	add	r3, r0, #11075584
	ldr	r1, [r1, #528]
	add	r3, r3, #45056
	ldr	r5, [r3, #2384]
	rsb	r2, r2, r1, lsl #1
	cmp	r5, #0
	beq	.L239
	movw	r4, #47300
	add	r7, r0, #11141120
	movt	r4, 169
	add	r7, r7, #8192
	add	r4, r0, r4
	mov	ip, #0
	b	.L219
.L215:
	tst	r3, #2
	beq	.L217
	ldr	r3, [r1, #648]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L240
.L217:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L241
.L219:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L215
	ldr	lr, [r1, #612]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L215
	ldr	r8, [r1, #56]
	ldr	lr, [r7, #2192]
	cmp	r8, lr
	bne	.L215
	ldr	lr, [r1, #624]
	cmp	lr, r2
	bne	.L215
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #11075584
	strb	r3, [r1, #3]
	add	r2, r2, #45056
	mov	r1, #0
	ldr	r3, [r2, #2248]
	strb	r1, [r3, #614]
	ldr	r3, [r2, #2248]
	ldrb	ip, [r3, #576]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #578]
	ldreq	r3, [r2, #2248]
	streqb	r1, [r3, #577]
	ldreq	r3, [r2, #2248]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r1, [r3, #48]
	mov	r2, ip
	add	r1, r0, r1, lsl #2
	str	ip, [r1, #148]
	ldrsb	r1, [r3, #6]
	b	.L234
.L240:
	ldr	lr, [r1, #56]
	ldr	r3, [r7, #2192]
	cmp	lr, r3
	bne	.L217
	ldr	r3, [r1, #660]
	cmp	r3, r2
	bne	.L217
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #3]
	add	r3, r3, #11075584
	mov	r2, #0
	add	r3, r3, #45056
	ldr	r1, [r3, #2248]
	strb	r2, [r1, #650]
	ldr	r1, [r3, #2248]
	ldrb	ip, [r1, #576]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r2
	streqb	r2, [r1, #578]
	ldreq	r1, [r3, #2248]
	streqb	r2, [r1, #577]
	ldreq	r1, [r3, #2248]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r3, [r1, #48]
	mov	r2, ip
	add	r3, r0, r3, lsl #2
	str	ip, [r3, #148]
	ldrsb	r1, [r1, #6]
.L234:
	ldr	r0, [r0, #120]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	FSP_SetRef
.L241:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L238:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L237:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L239:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkSTRef, .-MVC_UnMarkSTRef
	.align	2
	.global	MVC_UnMarkLTRef
	.type	MVC_UnMarkLTRef, %function
MVC_UnMarkLTRef:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L243
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	r5, [r3, #2388]
	cmp	r5, #0
	beq	.L272
	movw	r4, #47364
	add	r7, r0, #11141120
	movt	r4, 169
	add	r7, r7, #8192
	add	r4, r0, r4
	mov	ip, #0
	b	.L252
.L248:
	tst	r3, #2
	beq	.L250
	ldr	r3, [r1, #648]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L273
.L250:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L274
.L252:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L248
	ldr	lr, [r1, #612]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L248
	ldr	r8, [r1, #56]
	ldr	lr, [r7, #2192]
	cmp	r8, lr
	bne	.L248
	ldr	lr, [r1, #620]
	cmp	r2, lr
	bne	.L248
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #11075584
	strb	r3, [r1, #3]
	add	r2, r2, #45056
	mov	r1, #0
	ldr	r3, [r2, #2312]
	strb	r1, [r3, #613]
	ldr	r3, [r2, #2312]
	ldrb	ip, [r3, #576]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #578]
	ldreq	r3, [r2, #2312]
	streqb	r1, [r3, #577]
	ldreq	r3, [r2, #2312]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r1, [r3, #48]
	mov	r2, ip
	add	r1, r0, r1, lsl #2
	str	ip, [r1, #148]
	ldrsb	r1, [r3, #6]
	b	.L269
.L243:
	add	r1, r0, #11075584
	add	r1, r1, #45056
	ldr	r4, [r1, #2388]
	cmp	r4, #0
	beq	.L275
	movw	ip, #47364
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #8192
	add	ip, r0, ip
	b	.L254
.L253:
	cmp	r3, r4
	beq	.L276
.L254:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #584]
	cmp	lr, r2
	bne	.L253
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L253
	ldr	lr, [r1, #576]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L253
	ldr	r6, [r1, #56]
	ldr	lr, [r5, #2192]
	cmp	r6, lr
	bne	.L253
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L273:
	ldr	lr, [r1, #56]
	ldr	r3, [r7, #2192]
	cmp	lr, r3
	bne	.L250
	ldr	r3, [r1, #656]
	cmp	r2, r3
	bne	.L250
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #3]
	add	r3, r3, #11075584
	mov	r2, #0
	add	r3, r3, #45056
	ldr	r1, [r3, #2312]
	strb	r2, [r1, #649]
	ldr	r1, [r3, #2312]
	ldrb	ip, [r1, #576]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r2
	streqb	r2, [r1, #578]
	ldreq	r1, [r3, #2312]
	streqb	r2, [r1, #577]
	ldreq	r1, [r3, #2312]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r3, [r1, #48]
	mov	r2, ip
	add	r3, r0, r3, lsl #2
	str	ip, [r3, #148]
	ldrsb	r1, [r1, #6]
.L269:
	ldr	r0, [r0, #120]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	FSP_SetRef
.L276:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L274:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L275:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L272:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkLTRef, .-MVC_UnMarkLTRef
	.align	2
	.global	MVC_MarkPicLTRef
	.type	MVC_MarkPicLTRef, %function
MVC_MarkPicLTRef:
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
	ldrb	r6, [r3, #3]	@ zero_extendqisi2
	add	r3, r0, #11075584
	add	r3, r3, #45056
	cmp	r6, #0
	beq	.L278
	ldr	r7, [r3, #2384]
	cmp	r7, #0
	beq	.L307
	movw	r5, #47300
	add	r8, r0, #11141120
	movt	r5, 169
	add	r8, r8, #8192
	add	r5, r0, r5
	mov	ip, #0
	b	.L292
.L284:
	tst	r4, #2
	beq	.L287
	ldr	lr, [r3, #648]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	beq	.L308
.L287:
	add	ip, ip, #1
	cmp	ip, r7
	beq	.L309
.L292:
	ldr	r3, [r5, #4]!
	ldrb	r4, [r3, #3]	@ zero_extendqisi2
	tst	r4, #1
	beq	.L284
	ldr	lr, [r3, #612]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L284
	ldr	lr, [r3, #624]
	cmp	lr, r2
	bne	.L284
	ldr	r9, [r3, #56]
	ldr	lr, [r8, #2192]
	cmp	r9, lr
	bne	.L284
	ldrb	lr, [r3, #649]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L288
	ldr	lr, [r3, #28]
	cmp	lr, r1
	bne	.L287
.L288:
	add	r0, r0, ip, lsl #2
	str	r1, [r3, #28]
	add	r3, r0, #11075584
	sub	r6, r6, #1
	add	r3, r3, #45056
	clz	r6, r6
	mov	ip, #1
	mov	r0, #0
	ldr	r2, [r3, #2248]
	mov	r6, r6, lsr #5
	add	r1, r6, r1, lsl #1
	str	r1, [r2, #620]
	ldr	r2, [r3, #2248]
	strb	ip, [r2, #613]
	ldr	r2, [r3, #2248]
	strb	r0, [r2, #614]
	ldr	r2, [r3, #2248]
	ldrb	r1, [r2, #576]	@ zero_extendqisi2
	cmp	r1, #3
	cmpne	r1, r0
	bne	.L310
	ldrb	r1, [r2, #649]	@ zero_extendqisi2
	ldrb	r0, [r2, #613]	@ zero_extendqisi2
	cmp	r1, r0
	streqb	r1, [r2, #577]
	ldreq	r3, [r3, #2248]
	ldreqb	r2, [r3, #614]	@ zero_extendqisi2
	streqb	r2, [r3, #578]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L278:
	ldr	r4, [r3, #2384]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	ip, #47300
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #8192
	add	ip, r0, ip
	b	.L283
.L282:
	add	r6, r6, #1
	cmp	r6, r4
	beq	.L311
.L283:
	ldr	r3, [ip, #4]!
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L282
	ldr	lr, [r3, #576]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L282
	ldr	lr, [r3, #588]
	cmp	lr, r2
	bne	.L282
	ldr	r7, [r3, #56]
	ldr	lr, [r5, #2192]
	cmp	r7, lr
	bne	.L282
	add	r6, r0, r6, lsl #2
	str	r1, [r3, #28]
	add	r3, r6, #11075584
	mov	r0, #1
	add	r3, r3, #45056
	mov	r2, #0
	ldr	ip, [r3, #2248]
	str	r1, [ip, #584]
	ldr	r1, [r3, #2248]
	strb	r0, [r1, #577]
	ldr	r1, [r3, #2248]
	strb	r0, [r1, #613]
	ldr	r1, [r3, #2248]
	strb	r0, [r1, #649]
	ldr	r1, [r3, #2248]
	strb	r2, [r1, #578]
	ldr	r1, [r3, #2248]
	strb	r2, [r1, #614]
	ldr	r3, [r3, #2248]
	strb	r2, [r3, #650]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L308:
	ldr	lr, [r3, #660]
	cmp	lr, r2
	bne	.L287
	ldr	r4, [r3, #56]
	ldr	lr, [r8, #2192]
	cmp	r4, lr
	bne	.L287
	ldrb	lr, [r3, #613]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L291
	ldr	lr, [r3, #28]
	cmp	lr, r1
	bne	.L287
.L291:
	add	r0, r0, ip, lsl #2
	str	r1, [r3, #28]
	add	r3, r0, #11075584
	sub	r6, r6, #2
	add	r3, r3, #45056
	clz	r6, r6
	mov	ip, #1
	mov	r0, #0
	ldr	r2, [r3, #2248]
	mov	r6, r6, lsr #5
	add	r1, r6, r1, lsl #1
	str	r1, [r2, #656]
	ldr	r2, [r3, #2248]
	strb	ip, [r2, #649]
	ldr	r2, [r3, #2248]
	strb	r0, [r2, #650]
	ldr	r2, [r3, #2248]
	ldrb	r1, [r2, #576]	@ zero_extendqisi2
	cmp	r1, #3
	cmpne	r1, r0
	bne	.L312
	ldrb	r1, [r2, #649]	@ zero_extendqisi2
	ldrb	r0, [r2, #613]	@ zero_extendqisi2
	cmp	r1, r0
	streqb	r1, [r2, #577]
	ldreq	r3, [r3, #2248]
	ldreqb	r2, [r3, #650]	@ zero_extendqisi2
	streqb	r2, [r3, #578]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L309:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L311:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L310:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L312:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L307:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_MarkPicLTRef, .-MVC_MarkPicLTRef
	.align	2
	.global	MVC_MarkSTToLTRef
	.type	MVC_MarkSTToLTRef, %function
MVC_MarkSTToLTRef:
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
	mov	r5, r1
	ldrb	r1, [r1, #3]	@ zero_extendqisi2
	mov	r7, r3
	mov	r6, r0
	cmp	r1, #0
	bne	.L314
	ldr	r4, [r5, #528]
	mov	r1, r3
	sub	r4, r4, #1
	rsb	r4, r2, r4
	bl	MVC_UnMarkLTFrmByFrmIdx
.L315:
	mov	r3, r5
	mov	r2, r4
	mov	r1, r7
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MVC_MarkPicLTRef
.L314:
	add	r3, r0, #11075584
	ldr	r4, [r5, #528]
	add	r3, r3, #45056
	ldr	lr, [r3, #2384]
	rsb	r4, r2, r4, lsl #1
	cmp	lr, #0
	beq	.L315
	movw	ip, #47300
	add	r8, r0, #11141120
	movt	ip, 169
	add	r8, r8, #8192
	add	ip, r0, ip
	mov	r3, #0
	b	.L318
.L316:
	tst	r2, #2
	beq	.L317
	ldr	r2, [r1, #648]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #65536
	beq	.L329
.L317:
	cmp	r3, lr
	beq	.L315
.L318:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	tst	r2, #1
	beq	.L316
	ldr	r0, [r1, #612]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #65536
	bne	.L316
	ldr	r0, [r1, #624]
	cmp	r0, r4
	bne	.L316
	ldr	r9, [r1, #56]
	ldr	r0, [r8, #2192]
	cmp	r9, r0
	bne	.L316
	mov	r3, r7
	mov	r2, #1
	mov	r0, r6
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L315
.L329:
	ldr	r2, [r1, #660]
	cmp	r2, r4
	bne	.L317
	ldr	r0, [r1, #56]
	ldr	r2, [r8, #2192]
	cmp	r0, r2
	bne	.L317
	mov	r3, r7
	mov	r2, #2
	mov	r0, r6
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L315
	UNWIND(.fnend)
	.size	MVC_MarkSTToLTRef, .-MVC_MarkSTToLTRef
	.align	2
	.global	MVC_UpdateMaxLTFrmIdx
	.type	MVC_UpdateMaxLTFrmIdx, %function
MVC_UpdateMaxLTFrmIdx:
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
	add	r5, r0, #11075584
	mov	r8, r0
	add	r5, r5, #45056
	ldr	r3, [r5, #2388]
	str	r1, [r5, #2392]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	r6, #47364
	add	r7, r0, #11141120
	movt	r6, 169
	add	r7, r7, #8192
	add	r6, r0, r6
	mov	r3, r1
	mov	r4, #0
	b	.L334
.L332:
	ldr	r3, [r5, #2388]
	cmp	r3, r4
	ldmlsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, [r5, #2392]
.L334:
	ldr	r1, [r6, #4]!
	add	r4, r4, #1
	ldr	r2, [r1, #28]
	cmp	r2, r3
	bcc	.L332
	ldr	r2, [r1, #56]
	ldr	r3, [r7, #2192]
	cmp	r2, r3
	bne	.L332
	mov	r0, r8
	bl	MVC_UnMarkFrameStoreRef
	b	.L332
	UNWIND(.fnend)
	.size	MVC_UpdateMaxLTFrmIdx, .-MVC_UpdateMaxLTFrmIdx
	.align	2
	.global	MVC_UnMarkAllSTRef
	.type	MVC_UnMarkAllSTRef, %function
MVC_UnMarkAllSTRef:
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
	add	r6, r0, #11075584
	mov	r8, r0
	add	r6, r6, #45056
	ldr	r3, [r6, #2384]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	r5, #47300
	add	r7, r0, #11141120
	movt	r5, 169
	add	r7, r7, #8192
	add	r5, r0, r5
	mov	r4, #0
	b	.L338
.L337:
	ldr	r3, [r6, #2384]
	cmp	r3, r4
	bls	.L341
.L338:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	ldr	r3, [r7, #2192]
	ldr	r2, [r1, #56]
	cmp	r2, r3
	bne	.L337
	mov	r0, r8
	bl	MVC_UnMarkFrameStoreRef
	ldr	r3, [r6, #2384]
	cmp	r3, r4
	bhi	.L338
.L341:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UnMarkAllSTRef, .-MVC_UnMarkAllSTRef
	.align	2
	.global	MVC_MarkCurrPicLT
	.type	MVC_MarkCurrPicLT, %function
MVC_MarkCurrPicLT:
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
	beq	.L345
	mov	r3, r5
	ldr	r1, [r1, #520]
	bl	MVC_UnMarkLTFldByFrmIdx
.L344:
	mov	r2, #1
	mov	r3, #0
	str	r5, [r4, #532]
	strb	r2, [r4, #4]
	strb	r3, [r4, #5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L345:
	mov	r1, r5
	bl	MVC_UnMarkLTFrmByFrmIdx
	b	.L344
	UNWIND(.fnend)
	.size	MVC_MarkCurrPicLT, .-MVC_MarkCurrPicLT
	.align	2
	.global	MVC_RemoveFrameStoreOutDPB
	.type	MVC_RemoveFrameStoreOutDPB, %function
MVC_RemoveFrameStoreOutDPB:
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
	add	r1, r0, r1, lsl #2
	mov	r5, r0
	add	r4, r1, #11075584
	add	r7, r4, #45056
	ldr	r2, [r7, #2184]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r2, #52]
	movw	r3, #47448
	add	r6, r0, #11075584
	movt	r3, 169
	add	r1, r0, r1
	add	r0, r6, #45056
	add	r3, r1, r3
	mov	r1, #0
	strb	r1, [r3, #4]
	ldr	r3, [r0, #2608]
	cmp	r3, r1
	subne	r3, r3, #1
	str	r3, [r0, #2608]
	ldrsb	r1, [r2, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L349
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L350
	ldr	r3, [r7, #2184]
	mov	r2, #0
	ldr	r0, [r5, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
.L350:
	ldr	r3, [r7, #2184]
	mov	r2, #0
	ldr	r0, [r5, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
.L349:
	add	r1, r4, #45056
	mov	r3, #0
	add	r6, r6, #45056
	ldr	r2, [r1, #2184]
	strb	r3, [r2, #2]
	ldr	r2, [r1, #2184]
	strb	r3, [r2, #5]
	ldr	r2, [r1, #2184]
	strb	r3, [r2, #3]
	str	r3, [r1, #2184]
	ldr	r3, [r6, #2380]
	sub	r3, r3, #1
	str	r3, [r6, #2380]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_RemoveFrameStoreOutDPB, .-MVC_RemoveFrameStoreOutDPB
	.align	2
	.global	MVC_RemoveUnUsedFrameStore
	.type	MVC_RemoveUnUsedFrameStore, %function
MVC_RemoveUnUsedFrameStore:
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
	add	r3, r0, #11075584
	mov	r8, r0
	add	r3, r3, #45056
	mov	r7, r1
	ldr	r6, [r3, #2376]
	cmp	r6, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	r5, #47236
	mov	r4, #0
	movt	r5, 169
	add	r5, r0, r5
.L366:
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L365
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L365
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L365
	ldr	r1, [r3, #56]
	cmn	r7, #1
	cmpne	r1, r7
	beq	.L378
.L365:
	add	r4, r4, #1
	cmp	r4, r6
	bne	.L366
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L378:
	ldr	ip, [r3, #16]
	mov	r1, r4
	mov	r0, r8
	cmp	ip, #1
	beq	.L365
	strb	r2, [r3, #2]
	bl	MVC_RemoveFrameStoreOutDPB
	b	.L365
	UNWIND(.fnend)
	.size	MVC_RemoveUnUsedFrameStore, .-MVC_RemoveUnUsedFrameStore
	.align	2
	.global	MVC_CheckFrameStore
	.type	MVC_CheckFrameStore, %function
MVC_CheckFrameStore:
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
	ldrb	r3, [r0, #6]	@ zero_extendqisi2
	mov	r5, r0
	mov	r4, r1
	cmp	r3, #0
	bne	.L380
	ldrsb	r3, [r1, #8]
	cmp	r3, #1
	bne	.L392
	strb	r3, [r0, #6]
.L380:
	ldrsb	r1, [r4, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L382
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	cmpne	r3, #0
	beq	.L402
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L391
	cmp	r3, #1
	beq	.L391
	cmp	r2, #3
	beq	.L403
	cmp	r2, #1
	beq	.L404
	cmp	r2, #2
	beq	.L405
.L387:
	ldr	r3, [r5, #224]
	ldr	r2, [r0, #208]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	movls	r0, #0
	bhi	.L406
.L400:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L402:
	ldr	ip, .L407
	mov	r0, #1
	ldrsb	r2, [r4, #6]
	ldr	r1, .L407+4
	ldr	r5, [ip, #68]
	blx	r5
.L384:
	ldr	r3, [r4, #16]
	cmp	r3, #1
	mvnne	r0, #2
	moveq	r3, #2
	mvneq	r0, #2
	streq	r3, [r4, #16]
	b	.L400
.L403:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L387
	ldr	ip, .L407
	mov	r2, r3
	ldr	r1, .L407+8
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L400
.L404:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L387
	ldr	ip, .L407
	mov	r0, r2
	ldr	r1, .L407+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L400
.L405:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	tst	r3, #2
	beq	.L387
	ldr	ip, .L407
	mov	r0, #1
	ldr	r1, .L407+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L400
.L392:
	mvn	r0, #0
	b	.L400
.L382:
	ldr	lr, .L407
	mov	r2, r4
	ldrsb	ip, [r4, #6]
	mov	r0, #1
	ldr	r3, [r4, #16]
	ldr	r5, [lr, #68]
	ldr	r1, .L407+20
	str	ip, [sp]
	blx	r5
	b	.L384
.L391:
	ldr	ip, .L407
	mov	r0, #1
	ldr	r1, .L407+24
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L400
.L406:
	ldr	ip, .L407
	mov	r0, #1
	ldr	r1, .L407+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L400
.L408:
	.align	2
.L407:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC5
	.word	.LC6
	.word	.LC10
	UNWIND(.fnend)
	.size	MVC_CheckFrameStore, .-MVC_CheckFrameStore
	.align	2
	.global	MVC_ExchangePts
	.type	MVC_ExchangePts, %function
MVC_ExchangePts:
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
	ldrd	r2, [r1, #80]
	mvn	r7, #0
	mvn	r6, #0
	cmp	r3, r7
	mov	r8, r1
	cmpeq	r2, r6
	mov	r5, r0
	beq	.L409
	add	r9, r0, #11075584
	add	r9, r9, #45056
	ldr	r3, [r9, #2376]
	cmp	r3, #0
	beq	.L409
	movw	r10, #47236
	mvn	r6, #1
	movt	r10, 169
	add	r10, r0, r10
	mvn	r7, #0
	mov	r4, #0
	mvn	r3, #0
	str	r3, [fp, #-48]
.L414:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L413
	ldrsb	r1, [r3, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L413
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	cmpne	r3, #0
	beq	.L413
	ldr	r3, [r10]
	ldrd	r0, [r3, #80]
	cmp	r1, r7
	cmpeq	r0, r6
	strcc	r4, [fp, #-48]
	movcc	r6, r0
	movcc	r7, r1
.L413:
	ldr	r3, [r9, #2376]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L414
	ldr	r3, [fp, #-48]
	cmn	r3, #1
	beq	.L409
	ldrd	r2, [r8, #80]
	cmp	r3, r7
	cmpeq	r2, r6
	bhi	.L428
.L409:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L428:
	ldr	ip, .L429
	mov	r0, #29
	strd	r6, [sp]
	ldr	r1, .L429+4
	ldr	r4, [ip, #68]
	blx	r4
	ldr	r3, [fp, #-48]
	movw	r1, #28194
	movt	r1, 42
	add	r1, r3, r1
	ldrd	r2, [r8, #80]
	ldr	r1, [r5, r1, asl #2]
	strd	r2, [r1, #80]
	strd	r6, [r8, #80]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L430:
	.align	2
.L429:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	UNWIND(.fnend)
	.size	MVC_ExchangePts, .-MVC_ExchangePts
	.align	2
	.global	MVC_GetImagePara
	.type	MVC_GetImagePara, %function
MVC_GetImagePara:
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
	add	r3, r0, #11075584
	add	ip, r3, #40960
	ldr	r2, [r0, #252]
	mov	r5, r0
	mov	r6, #2240
	ldr	r0, [ip, #536]
	mov	r4, r1
	ldr	r1, [r1, #232]
	movw	r8, #3992
	ldr	r7, [r5, #248]
	mla	r6, r6, r0, r2
	bic	lr, r1, #768
	bic	lr, lr, #3
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	ldr	r2, [r6, #28]
	str	lr, [r4, #232]
	ldr	r6, [r5, #56]
	mla	r2, r8, r2, r7
	mov	r6, r6, asl #10
	str	r6, [r4, #260]
	cmp	r0, #3
	ldrls	pc, [pc, r0, asl #2]
	b	.L469
.L434:
	.word	.L433
	.word	.L435
	.word	.L436
	.word	.L433
.L436:
	ldrb	r1, [r4]	@ zero_extendqisi2
	add	r3, r5, #11075584
	ldr	r6, [r4, #44]
	add	r3, r3, #45056
	orr	lr, lr, #2816
	and	r1, r1, #3
	orr	lr, lr, r1
	str	lr, [r4, #232]
	str	r6, [r4, #272]
.L432:
	ldrb	r1, [r2, #20]	@ zero_extendqisi2
	str	r1, [r4, #556]
	str	r1, [r4, #560]
	ldrb	r1, [r2, #24]	@ zero_extendqisi2
	cmp	r1, #0
	ldrne	r1, [r2, #68]
	mov	r2, #1
	str	r2, [r4, #564]
	str	r1, [r4, #568]
	ldrb	r2, [ip, #531]	@ zero_extendqisi2
	cmp	r2, #1
	movne	r2, #0
	str	r2, [r4, #328]
	ldr	r2, [r5, #224]
	ldr	r2, [r2, #12]
	cmp	r2, #0
	ble	.L454
	ldrb	r2, [r4, #576]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L454
	cmp	r0, #3
	ldreq	r2, [r4, #232]
	biceq	r2, r2, #768
	streq	r2, [r4, #232]
.L454:
	ldrb	r2, [r3, #2136]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L455
	ldr	r2, [r3, #2152]
	cmp	r2, #3
	moveq	r3, #1
	streq	r3, [r4, #436]
	beq	.L455
	cmp	r2, #4
	moveq	r3, #2
	streq	r3, [r4, #436]
	beq	.L455
	cmp	r2, #5
	moveq	r3, #3
	streq	r3, [r4, #436]
	beq	.L455
	ldr	ip, .L480
	mov	r2, #0
	mov	r0, r2
	str	r2, [r4, #436]
	ldr	r1, .L480+4
	ldr	r2, [r3, #2152]
	ldr	r3, [ip, #68]
	blx	r3
.L455:
	ldr	r0, [r5, #120]
	ldrsb	r1, [r4, #6]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L431
	ldr	r3, .L480
	mov	r2, #504
	add	r1, r4, #72
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #16
	str	r3, [r5, #384]
	mov	r2, #1
	ldrb	r3, [r4, #576]	@ zero_extendqisi2
	strb	r2, [r5, #379]
	cmp	r3, #0
	movne	r3, #4
	strb	r3, [r5, #372]
	ldr	r3, [r4, #604]
	strb	r2, [r5, #377]
	str	r3, [r5, #388]
	str	r3, [r5, #396]
	str	r3, [r5, #392]
.L431:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L435:
	ldrb	r1, [r4]	@ zero_extendqisi2
	add	r3, r5, #11075584
	ldr	r6, [r4, #44]
	orr	lr, lr, #1792
	and	r1, r1, #3
	add	r3, r3, #45056
	orr	lr, lr, r1
	str	lr, [r4, #232]
	str	r6, [r4, #272]
	b	.L432
.L433:
	ldrb	lr, [r4, #576]	@ zero_extendqisi2
	cmp	lr, #0
	bne	.L437
	ldr	lr, [r4, #40]
	mov	r6, #3072
	ldr	r8, [r4, #44]
	cmp	lr, #0
	ldrb	lr, [r4]	@ zero_extendqisi2
	moveq	r7, #512
	movne	r7, #768
	str	r8, [r4, #272]
.L438:
	ldr	r9, [r4, #628]
	ldr	r8, [r4, #664]
	cmp	r9, r8
	beq	.L478
	movle	r8, #1
	movgt	r8, #0
.L449:
	add	r3, r3, #45056
	ldrb	r9, [r3, #2172]	@ zero_extendqisi2
	cmp	r9, #3
	moveq	r8, #4096
	beq	.L450
	cmp	r9, #4
	movne	r8, r8, asl #12
	moveq	r8, #0
.L450:
	bic	r1, r1, #13056
	orr	r6, r6, r7
	bic	r1, r1, #3
	and	lr, lr, #3
	orr	r1, r6, r1
	orr	r1, r1, lr
	orr	r1, r1, r8
	str	r1, [r4, #232]
	b	.L432
.L437:
	ldr	r7, [r4, #636]
	ldr	lr, [r5, #116]
	ldr	r10, [r4, #672]
	cmp	r7, lr
	bhi	.L479
	cmp	lr, r10
	bcc	.L442
.L440:
	mov	lr, #3
	ldr	r6, [r4, #44]
	str	lr, [fp, #-48]
	ldrb	r9, [r4, #615]	@ zero_extendqisi2
	ldrb	lr, [r4]	@ zero_extendqisi2
	ldrb	r8, [r4, #651]	@ zero_extendqisi2
	str	r6, [r4, #272]
.L443:
	ldrb	r6, [r4, #4]	@ zero_extendqisi2
	cmp	r6, #1
	streq	r10, [r4, #272]
	moveq	lr, r8
	moveq	r6, #2048
	beq	.L445
	cmp	r6, #2
	streq	r7, [r4, #272]
	ldrne	r6, [fp, #-48]
	moveq	lr, r9
	moveq	r6, #1024
	movne	r6, r6, asl #10
.L445:
	mov	r7, #768
	str	r9, [r4, #224]
	str	r8, [r4, #228]
	b	.L438
.L442:
	ldrb	lr, [r4, #615]	@ zero_extendqisi2
	mov	r6, #1
	ldrb	r8, [r4, #651]	@ zero_extendqisi2
	str	r6, [fp, #-48]
	str	r7, [r4, #272]
	mov	r9, lr
	b	.L443
.L478:
	ldr	r8, [r4, #236]
	cmp	r8, #720
	movne	r8, #1
	bne	.L449
	ldr	r8, [r4, #240]
	subs	r8, r8, #480
	movne	r8, #1
	b	.L449
.L479:
	cmp	lr, r10
	bcc	.L440
	ldrb	lr, [r4, #651]	@ zero_extendqisi2
	mov	r6, #2
	str	r10, [r4, #272]
	str	r6, [fp, #-48]
	ldrb	r9, [r4, #615]	@ zero_extendqisi2
	mov	r8, lr
	b	.L443
.L469:
	add	r3, r5, #11075584
	add	r3, r3, #45056
	b	.L432
.L481:
	.align	2
.L480:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC12
	UNWIND(.fnend)
	.size	MVC_GetImagePara, .-MVC_GetImagePara
	.align	2
	.global	MVC_SetFrmRepeatCount
	.type	MVC_SetFrmRepeatCount, %function
MVC_SetFrmRepeatCount:
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
	ldr	r3, [r0, #224]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #84]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_SetFrmRepeatCount.part.1
	UNWIND(.fnend)
	.size	MVC_SetFrmRepeatCount, .-MVC_SetFrmRepeatCount
	.align	2
	.global	MVC_SplitFrmToFlds
	.type	MVC_SplitFrmToFlds, %function
MVC_SplitFrmToFlds:
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
	ldrb	lr, [r0, #577]	@ zero_extendqisi2
	mov	r5, #1
	ldrb	ip, [r0, #578]	@ zero_extendqisi2
	mov	r4, #2
	ldr	r1, [r0, #600]
	ldrb	r2, [r0, #579]	@ zero_extendqisi2
	ldr	r3, [r0, #580]
	strb	r5, [r0, #612]
	strb	r4, [r0, #648]
	strb	lr, [r0, #613]
	strb	lr, [r0, #649]
	strb	ip, [r0, #614]
	strb	ip, [r0, #650]
	str	r1, [r0, #636]
	str	r1, [r0, #672]
	strb	r2, [r0, #615]
	strb	r2, [r0, #651]
	str	r3, [r0, #616]
	str	r3, [r0, #652]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_SplitFrmToFlds, .-MVC_SplitFrmToFlds
	.align	2
	.global	MVC_CombineFldsToFrm
	.type	MVC_CombineFldsToFrm, %function
MVC_CombineFldsToFrm:
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
	ldr	r2, [r0, #664]
	mov	lr, #3
	ldr	r1, [r0, #628]
	ldr	r3, [r0, #672]
	cmp	r2, r1
	ldr	r5, [r0, #636]
	ldrb	r4, [r0, #649]	@ zero_extendqisi2
	ldr	ip, [r0, #616]
	movge	r2, r1
	add	r3, r3, r5
	cmp	r4, #0
	strb	lr, [r0, #576]
	mov	r3, r3, lsr #1
	str	ip, [r0, #580]
	str	r2, [r0, #592]
	str	r2, [r0, #32]
	str	r3, [r0, #600]
	beq	.L486
	ldrb	r2, [r0, #613]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L487
.L486:
	ldr	r2, [r0, #648]
	mov	r1, #0
	strb	r1, [r0, #577]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, r1
	beq	.L491
	ldr	r2, [r0, #612]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	movne	ip, #1
	bne	.L489
.L491:
	mov	ip, #0
.L489:
	ldrb	r2, [r0, #651]	@ zero_extendqisi2
	ldrb	r1, [r0, #615]	@ zero_extendqisi2
	str	r3, [r0, #44]
	cmp	r2, r1
	strb	ip, [r0, #578]
	movcs	r3, r2
	movcc	r3, r1
	strb	r3, [r0, #579]
	strb	r3, [r0]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L487:
	mov	r1, #1
	strb	r1, [r0, #577]
	b	.L491
	UNWIND(.fnend)
	.size	MVC_CombineFldsToFrm, .-MVC_CombineFldsToFrm
	.align	2
	.global	MVC_GetAPC
	.type	MVC_GetAPC, %function
MVC_GetAPC:
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
	subs	r6, r1, #0
	mov	r5, r0
	beq	.L522
	cmp	r2, #1
	beq	.L503
	cmp	r2, #2
	beq	.L504
	ldr	r9, [r6, #628]
	ldr	r10, [r6, #664]
.L505:
	add	r8, r5, #11075584
	add	r7, r8, #45056
	ldr	r1, [r7, #2604]
	cmp	r1, #0
	beq	.L514
	ldrb	r4, [r7, #2396]	@ zero_extendqisi2
	cmp	r4, #0
	movwne	r3, #47452
	movne	r4, #0
	movtne	r3, 169
	addne	r3, r5, r3
	bne	.L508
	b	.L506
.L512:
	ldrb	r2, [r3, #1]!	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L506
.L508:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L512
.L514:
	mvn	r0, #0
.L518:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L504:
	ldr	r9, [r6, #664]
	mov	r10, r9
	b	.L505
.L506:
	ldrsb	r1, [r6, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L509
	ldr	r3, [r0, #520]
	cmp	r3, #0
	beq	.L509
	add	r2, r5, r4
	movw	r3, #47448
	movt	r3, 169
	add	r3, r2, r3
	mov	r2, #1
	add	r5, r5, r4, lsl #2
	strb	r2, [r3, #4]
	add	r5, r5, #11075584
	ldr	r3, [r0, #520]
	add	r5, r5, #45056
	ldr	ip, .L523
	add	r8, r8, #45056
	ldr	r1, .L523+4
	mov	r0, #13
	ldr	r3, [r3, #4]
	str	r9, [r5, #2476]
	str	r10, [r5, #2540]
	str	r3, [r5, #2412]
	ldr	r3, [r7, #2608]
	ldr	r5, [ip, #68]
	cmp	r3, #15
	addls	r2, r3, r2
	mov	r3, r4
	movhi	r2, #16
	str	r2, [r8, #2608]
	ldr	r2, [r6, #268]
	blx	r5
	mov	r0, #0
	str	r4, [r6, #52]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L503:
	ldr	r9, [r6, #628]
	mov	r10, r9
	b	.L505
.L509:
	ldr	r1, .L523
	ldrsb	r2, [r6, #6]
	ldrb	r3, [r6, #3]	@ zero_extendqisi2
	ldr	r4, [r1, #68]
	mov	r1, #0
	stmia	sp, {r0, r1}
	mov	r0, r1
	ldr	r1, .L523+8
	blx	r4
	mvn	r0, #0
	b	.L518
.L522:
	ldr	ip, .L523
	mov	r0, r6
	movw	r3, #2129
	ldr	r2, .L523+12
	ldr	r1, .L523+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L518
.L524:
	.align	2
.L523:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC15
	.word	.LC16
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_GetAPC, .-MVC_GetAPC
	.align	2
	.global	MVC_SlidingWinMark
	.type	MVC_SlidingWinMark, %function
MVC_SlidingWinMark:
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
	add	r6, r0, #11075584
	ldr	r3, [r0, #236]
	add	r6, r6, #45056
	mov	r10, r0
	ldr	r1, [r6, #2388]
	ldr	r3, [r3, #3944]
	ldr	r2, [r6, #2384]
	rsb	r3, r1, r3
	cmp	r2, r3
	beq	.L552
.L525:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L552:
	ldr	r8, [r6, #2376]
	cmp	r8, #0
	beq	.L532
	movw	r7, #47236
	add	r8, r0, #11141120
	mov	r3, #0
	movt	r7, 169
	add	r8, r8, #8192
	add	r7, r0, r7
	mvn	r9, #-2147483648
	mov	r5, r3
	str	r3, [fp, #-48]
.L530:
	ldr	r4, [r7, #4]!
	cmp	r4, #0
	beq	.L529
	ldr	r3, [r4, #64]
	cmp	r9, r3
	bls	.L529
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	mov	r0, r4
	cmp	r3, #0
	beq	.L529
	bl	MVC_NonLongTermRefFlg
	cmp	r0, #0
	beq	.L529
	ldr	r0, [r4, #56]
	ldr	r3, [r8, #2192]
	cmp	r0, r3
	beq	.L553
.L529:
	ldr	r3, [r6, #2376]
	add	r5, r5, #1
	cmp	r5, r3
	bcc	.L530
.L528:
	ldr	r2, [fp, #-48]
	movw	r3, #28194
	movt	r3, 42
	add	r3, r2, r3
	ldr	r4, [r10, r3, asl #2]
	cmp	r4, #0
	beq	.L525
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L525
	mov	r0, r4
	bl	MVC_NonLongTermRefFlg
	cmp	r0, #0
	beq	.L525
	add	r3, r10, #11141120
	ldr	r2, [r4, #56]
	add	r3, r3, #8192
	ldr	r3, [r3, #2192]
	cmp	r2, r3
	bne	.L525
	mov	r0, r10
	mov	r1, r4
	bl	MVC_UnMarkFrameStoreRef
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MVC_UpdateReflist
.L553:
	ldr	r3, .L554
	str	r5, [fp, #-48]
	ldr	r3, [r3, #112]
	blx	r3
	ldr	r3, [r7]
	ldr	r9, [r3, #64]
	b	.L529
.L532:
	str	r8, [fp, #-48]
	b	.L528
.L555:
	.align	2
.L554:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MVC_SlidingWinMark, .-MVC_SlidingWinMark
	.align	2
	.global	MVC_DumpDPB
	.type	MVC_DumpDPB, %function
MVC_DumpDPB:
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
	ldr	r3, .L567
	mov	r8, r0
	ldr	r3, [r3]
	tst	r3, #16384
	beq	.L556
	add	r7, r0, #11075584
	add	r7, r7, #45056
	ldr	r3, [r7, #2380]
	cmp	r3, #0
	beq	.L566
	movw	r5, #47236
	ldr	r6, .L567+4
	movt	r5, 169
	add	r5, r0, r5
	mov	r4, #0
.L561:
	ldr	ip, [r5, #4]!
	mov	r2, r4
	ldr	r9, [r6, #68]
	mov	r0, #14
	ldr	r1, .L567+8
	add	r4, r4, #1
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	ldr	r3, [ip, #20]
	str	lr, [sp, #4]
	ldr	ip, [ip, #32]
	str	ip, [sp]
	blx	r9
	ldr	r3, [r7, #2380]
	cmp	r3, r4
	bhi	.L561
.L562:
	ldr	r3, [r6, #68]
	mov	r0, #14
	ldr	r1, .L567+12
	blx	r3
	ldr	r3, [r7, #2384]
	cmp	r3, #0
	movwne	r5, #47300
	movne	r4, #0
	movtne	r5, 169
	addne	r5, r8, r5
	beq	.L560
.L563:
	ldr	ip, [r5, #4]!
	mov	r2, r4
	ldr	r8, [r6, #68]
	mov	r0, #14
	ldr	r1, .L567+16
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	ldr	r3, [ip, #20]
	str	lr, [sp, #4]
	ldr	ip, [ip, #32]
	str	ip, [sp]
	blx	r8
	ldr	r3, [r5]
	mov	r2, r4
	ldr	r8, [r6, #68]
	ldr	r1, .L567+20
	mov	r0, #14
	ldr	r3, [r3, #592]
	add	r4, r4, #1
	blx	r8
	ldr	r3, [r7, #2384]
	cmp	r3, r4
	bhi	.L563
.L560:
	ldr	r3, [r6, #68]
	mov	r0, #14
	ldr	r1, .L567+12
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L556:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L566:
	ldr	r6, .L567+4
	b	.L562
.L568:
	.align	2
.L567:
	.word	g_PrintEnable
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC18
	.word	.LC17
	.word	.LC19
	.word	.LC20
	UNWIND(.fnend)
	.size	MVC_DumpDPB, .-MVC_DumpDPB
	.align	2
	.global	MVC_UpdateCurrFrameInfo
	.type	MVC_UpdateCurrFrameInfo, %function
MVC_UpdateCurrFrameInfo:
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
	add	r0, r0, #11141120
	add	r3, r0, #8192
	ldrb	r2, [r3, #1594]	@ zero_extendqisi2
	ldr	r4, [r3, #2112]
	strb	r2, [r4, #1]
	ldrb	r2, [r3, #1596]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
	bne	.L570
	ldrb	r2, [r3, #1597]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
.L570:
	strb	r2, [r4, #3]
	ldr	r2, [r3, #2120]
	str	r2, [r4, #20]
	ldr	r2, [r3, #2164]
	str	r2, [r4, #44]
	ldrb	r2, [r3, #1604]	@ zero_extendqisi2
	strb	r2, [r4]
	ldr	r2, [r3, #2132]
	str	r2, [r4, #32]
	ldr	r2, [r3, #2188]
	str	r2, [r4, #48]
	ldr	r2, [r3, #2124]
	str	r2, [r4, #28]
	ldrb	r2, [r3, #1601]	@ zero_extendqisi2
	str	r2, [r4, #40]
	ldrb	r2, [r3, #1599]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r1, #3
	movne	r1, #0
	strb	r1, [r4, #4]
	ldrb	r2, [r3, #1595]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L573
	bcc	.L574
	cmp	r2, #2
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	str	r4, [r4, #652]
	mov	ip, #1
	strb	ip, [r4, #648]
	mov	r6, #0
	ldrb	ip, [r3, #1596]	@ zero_extendqisi2
	strb	ip, [r4, #649]
	ldrb	ip, [r3, #1597]	@ zero_extendqisi2
	strb	ip, [r4, #650]
	ldr	ip, [r3, #2140]
	str	ip, [r4, #664]
	ldrb	ip, [r3, #1604]	@ zero_extendqisi2
	strb	ip, [r4, #651]
	ldr	lr, [r3, #2164]
	str	r6, [r4, #40]
	str	lr, [r4, #672]
	ldrb	r5, [r3, #1593]	@ zero_extendqisi2
	cmp	r5, r6
	beq	.L591
	ldr	r2, [r4, #636]
	mov	r5, #3
	strb	r5, [r4, #2]
	mvn	r7, #0
	add	lr, lr, r2
	str	lr, [r4, #44]
	str	lr, [r4, #600]
	ldrb	r3, [r3, #1599]	@ zero_extendqisi2
	cmp	r3, #1
	add	r3, r0, #9792
	orreq	r6, r1, #2
	strb	r6, [r4, #4]
	ldrd	r8, [r3, #16]
	mvn	r6, #0
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L582
	ldrd	r2, [r4, #80]
	cmp	r3, r7
	cmpeq	r2, r6
	beq	.L592
.L582:
	ldrb	r3, [r4, #615]	@ zero_extendqisi2
.L589:
	add	r1, r0, #8192
	cmp	r3, ip
	mov	r0, r4
	movcc	r3, ip
	strb	r3, [r4]
	ldr	r3, [r1, #2132]
	str	r3, [r4, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MVC_CombineFldsToFrm
.L574:
	str	r4, [r4, #580]
	mov	r1, #3
	mov	r2, #0
	strb	r1, [r4, #2]
	strb	r2, [r4, #576]
	add	r1, r3, #1600
	ldrb	r5, [r3, #1596]	@ zero_extendqisi2
	mov	r2, #504
	add	r1, r1, #8
	add	r0, r4, #72
	strb	r5, [r4, #577]
	ldrb	r6, [r3, #1597]	@ zero_extendqisi2
	strb	r6, [r4, #578]
	ldr	ip, [r3, #2136]
	str	ip, [r4, #592]
	ldrb	r7, [r3, #1604]	@ zero_extendqisi2
	strb	r7, [r4, #579]
	ldr	r8, [r3, #2164]
	str	r8, [r4, #600]
	ldr	ip, [r3, #2140]
	str	ip, [r4, #628]
	ldr	r3, [r3, #2144]
	str	r3, [r4, #664]
	bl	memcpy
	mov	r2, #1
	mov	r3, #2
	str	r8, [r4, #636]
	str	r8, [r4, #672]
	strb	r7, [r4, #615]
	strb	r7, [r4, #651]
	strb	r6, [r4, #614]
	strb	r6, [r4, #650]
	strb	r5, [r4, #613]
	strb	r5, [r4, #649]
	str	r4, [r4, #616]
	str	r4, [r4, #652]
	strb	r2, [r4, #612]
	strb	r3, [r4, #648]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L573:
	strb	r2, [r4, #612]
	mov	r5, #0
	str	r4, [r4, #616]
	ldrb	ip, [r3, #1596]	@ zero_extendqisi2
	strb	ip, [r4, #613]
	ldrb	ip, [r3, #1597]	@ zero_extendqisi2
	strb	ip, [r4, #614]
	ldr	ip, [r3, #2140]
	str	ip, [r4, #628]
	ldrb	ip, [r3, #1604]	@ zero_extendqisi2
	strb	ip, [r4, #615]
	ldr	lr, [r3, #2164]
	str	r5, [r4, #40]
	str	lr, [r4, #636]
	ldrb	r6, [r3, #1593]	@ zero_extendqisi2
	cmp	r6, r5
	beq	.L593
	ldr	r2, [r4, #672]
	mov	r6, #3
	strb	r6, [r4, #2]
	mvn	r7, #0
	add	lr, lr, r2
	str	lr, [r4, #44]
	str	lr, [r4, #600]
	mvn	r6, #0
	ldrb	r3, [r3, #1599]	@ zero_extendqisi2
	cmp	r3, #1
	add	r3, r0, #9792
	orreq	r5, r1, #1
	strb	r5, [r4, #4]
	ldrd	r8, [r3, #16]
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L578
	ldrd	r2, [r4, #80]
	cmp	r3, r7
	cmpeq	r2, r6
	streqd	r8, [r4, #80]
.L578:
	ldrb	r3, [r4, #651]	@ zero_extendqisi2
	b	.L589
.L591:
	strb	r2, [r4, #2]
	add	r1, r0, #9792
	str	lr, [r4, #44]
	add	r1, r1, #8
	str	lr, [r4, #600]
	add	r0, r4, #72
	ldrb	r3, [r3, #1599]	@ zero_extendqisi2
	mov	r2, #504
	cmp	r3, #1
	moveq	r5, #2
	strb	r5, [r4, #4]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L593:
	strb	r2, [r4, #2]
	add	r1, r3, #1600
	str	lr, [r4, #44]
	add	r1, r1, #8
	str	lr, [r4, #600]
	add	r0, r4, #72
	ldrb	r3, [r3, #1599]	@ zero_extendqisi2
	mov	r2, #504
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r4, #4]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L592:
	strd	r8, [r4, #80]
	b	.L582
	UNWIND(.fnend)
	.size	MVC_UpdateCurrFrameInfo, .-MVC_UpdateCurrFrameInfo
	.align	2
	.global	MVC_SimpleSlideDPB
	.type	MVC_SimpleSlideDPB, %function
MVC_SimpleSlideDPB:
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
	add	r6, r0, #11075584
	mov	r8, r0
	add	r6, r6, #45056
	ldr	r4, [r6, #2376]
	ldr	r3, [r6, #2380]
	cmp	r3, r4
	addcc	r7, r0, #11141120
	bcc	.L595
	cmp	r4, #0
	beq	.L600
	movw	r5, #47236
	add	r7, r0, #11141120
	ldr	r10, .L611
	movt	r5, 169
	mov	ip, #0
	add	r9, r7, #8192
	add	r5, r0, r5
	mvn	r1, #-2147483648
	mov	r4, ip
.L598:
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L597
	ldr	r2, [r3, #64]
	cmp	r1, r2
	bls	.L597
	ldr	r2, [r3, #56]
	ldr	r3, [r9, #2192]
	cmp	r2, r3
	beq	.L610
.L597:
	ldr	r3, [r6, #2376]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L598
	mov	r4, ip
.L596:
	movw	r3, #28194
	mov	r0, r8
	movt	r3, 42
	add	r3, ip, r3
	ldr	r1, [r8, r3, asl #2]
	bl	MVC_UnMarkFrameStoreRef
	mov	r1, r4
	mov	r0, r8
	bl	MVC_RemoveFrameStoreOutDPB
.L595:
	add	r3, r7, #8192
	mov	r1, #0
	ldr	r2, [r3, #2128]
	strb	r1, [r3, #1596]
	cmp	r2, r1
	movne	r2, #1
	strneb	r2, [r3, #1597]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L610:
	ldr	r3, [r10, #112]
	blx	r3
	ldr	r3, [r5]
	mov	ip, r4
	ldr	r1, [r3, #64]
	b	.L597
.L600:
	add	r7, r0, #11141120
	mov	ip, r4
	b	.L596
.L612:
	.align	2
.L611:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MVC_SimpleSlideDPB, .-MVC_SimpleSlideDPB
	.align	2
	.global	MVC_ReleaseNAL
	.type	MVC_ReleaseNAL, %function
MVC_ReleaseNAL:
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
	mov	r6, r0
	beq	.L621
	ldr	r8, .L622
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	strb	r3, [r5, #1]
	strb	r3, [r5, #3]
.L616:
	ldr	r3, [r4, #8]
	mov	r0, r6
	cmp	r3, #0
	beq	.L615
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #12]
	ldr	r9, [r8, #68]
	mov	r0, #7
	ldr	r2, [r4, #8]
	ldr	r1, .L622+4
	blx	r9
	mov	r3, #0
	str	r3, [r4, #8]
	str	r3, [r4, #24]
	str	r3, [r4, #12]
.L615:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L616
	mov	r3, #0
	strb	r3, [r5]
	str	r3, [r5, #68]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L621:
	ldr	ip, .L622
	mov	r0, r5
	movw	r3, #4046
	ldr	r2, .L622+8
	ldr	r1, .L622+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L623:
	.align	2
.L622:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC21
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_ReleaseNAL, .-MVC_ReleaseNAL
	.align	2
	.global	MVC_ClearCurrNal
	.type	MVC_ClearCurrNal, %function
MVC_ClearCurrNal:
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
	ldr	r1, [r0, #232]
	mov	r4, r0
	cmp	r1, #0
	beq	.L625
	ldr	r0, [r0, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L625:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ClearCurrNal, .-MVC_ClearCurrNal
	.align	2
	.global	MVC_ClearCurrSlice
	.type	MVC_ClearCurrSlice, %function
MVC_ClearCurrSlice:
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
	ldr	r3, .L634
	mov	r4, r0
	ldr	r1, .L634+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L630
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L630:
	ldr	r3, [r4, #80]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #80]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L635:
	.align	2
.L634:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC22
	UNWIND(.fnend)
	.size	MVC_ClearCurrSlice, .-MVC_ClearCurrSlice
	.align	2
	.global	MVC_ClearAllNal
	.type	MVC_ClearAllNal, %function
MVC_ClearAllNal:
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
	mov	r6, r0
	add	r4, r0, #936
	add	r5, r0, #12992
	b	.L638
.L637:
	add	r4, r4, #88
	cmp	r4, r5
	beq	.L640
.L638:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L637
	mov	r1, r4
	ldr	r0, [r6, #120]
	add	r4, r4, #88
	bl	MVC_ReleaseNAL
	cmp	r4, r5
	bne	.L638
.L640:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ClearAllNal, .-MVC_ClearAllNal
	.align	2
	.global	MVC_ClearAllSlice
	.type	MVC_ClearAllSlice, %function
MVC_ClearAllSlice:
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
	movw	r4, #11024
	movw	r5, #11568
	movt	r4, 170
	movt	r5, 170
	add	r4, r0, r4
	add	r5, r0, r5
	mov	r6, r0
	mov	r7, #0
.L643:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L642
	ldr	r0, [r6, #120]
	bl	MVC_ReleaseNAL
	str	r7, [r4]
.L642:
	cmp	r4, r5
	bne	.L643
	mov	r0, #0
	str	r0, [r6, #64]
	str	r0, [r6, #104]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ClearAllSlice, .-MVC_ClearAllSlice
	.align	2
	.global	MVC_ClearCurrPic
	.type	MVC_ClearCurrPic, %function
MVC_ClearCurrPic:
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
	bl	MVC_ClearAllSlice
	ldr	r0, [r4, #40]
	add	r3, r4, #11075584
	add	r3, r3, #40960
	mov	r2, #0
	movw	r1, #23352
	movt	r1, 1
	str	r0, [r3, #2188]
	str	r1, [r3, #2192]
	mov	r0, #2
	mov	r1, #7
	strb	r0, [r3, #2177]
	strb	r1, [r3, #2179]
	mov	r0, #32
	mov	r1, #3
	strb	r0, [r3, #2178]
	str	r1, [r3, #2200]
	mvn	r0, #0
	mov	r1, #262144
	str	r0, [r3, #2204]
	str	r1, [r3, #2216]
	mov	r0, r2
	strb	r2, [r3, #2176]
	str	r2, [r3, #2208]
	str	r2, [r3, #2212]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ClearCurrPic, .-MVC_ClearCurrPic
	.align	2
	.global	MVC_ArrangeVahbMem
	.type	MVC_ArrangeVahbMem, %function
MVC_ArrangeVahbMem:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldr	r6, .L657
	mov	r5, r1
	mov	r7, r2
	mov	r4, r0
	mov	r2, #32
	ldr	r3, [r6, #48]
	sub	r0, fp, #68
	mov	r1, #0
	blx	r3
	ldr	r3, [r4, #224]
	str	r7, [fp, #-40]
	mov	r2, #0
	str	r5, [fp, #-60]
	ldr	r3, [r3, #28]
	str	r7, [fp, #-56]
	cmp	r3, #24
	str	r5, [fp, #-52]
	str	r7, [fp, #-48]
	str	r5, [fp, #-44]
	strb	r2, [fp, #-68]
	strb	r2, [fp, #-67]
	beq	.L650
	add	r1, r4, #11075584
	ldrb	r3, [fp, #4]	@ zero_extendqisi2
	add	r1, r1, #45056
	strb	r2, [fp, #-63]
	mov	r2, #5
	strb	r2, [fp, #-62]
	ldr	r2, [r1, #2376]
	add	r2, r2, #3
	strb	r2, [fp, #-64]
.L654:
	sub	r1, fp, #68
	ldr	r0, [r4, #120]
	strb	r3, [fp, #-61]
	mov	r7, #0
	mov	r5, #1
	strb	r7, [fp, #-65]
	strb	r5, [fp, #-66]
	bl	FSP_ConfigInstance
	subs	r8, r0, #0
	bne	.L651
	ldr	r1, [r4, #224]
	sub	r3, fp, #72
	ldr	r0, [r4, #120]
	ldr	r2, [r1, #24]
	ldr	r1, [r1, #20]
	bl	FSP_PartitionFsMemory
	cmp	r0, r7
	moveq	r0, r5
	bne	.L656
.L655:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L650:
	mov	r3, #1
	strb	r2, [fp, #-63]
	strb	r3, [fp, #-64]
	mov	r2, #5
	strb	r2, [fp, #-62]
	b	.L654
.L651:
	ldr	r3, [r6, #68]
	mov	r0, r7
	ldr	r1, .L657+4
	blx	r3
	mvn	r0, #19
	b	.L655
.L656:
	ldr	r3, [r6, #68]
	mov	r0, r8
	ldr	r1, .L657+8
	blx	r3
	mvn	r0, #19
	b	.L655
.L658:
	.align	2
.L657:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC24
	.word	.LC23
	UNWIND(.fnend)
	.size	MVC_ArrangeVahbMem, .-MVC_ArrangeVahbMem
	.align	2
	.global	MVC_RepairList
	.type	MVC_RepairList, %function
MVC_RepairList:
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
	add	r3, r0, #11075584
	mov	r6, r0
	add	r3, r3, #40960
	ldrb	r3, [r3, #520]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L661
	bcc	.L676
	cmp	r3, #2
	bne	.L682
.L677:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L673:
	mov	r0, r6
.L682:
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L661:
	mov	r7, #2
.L662:
	movw	r5, #41524
	add	r8, r6, #11141120
	movt	r5, 169
	add	r5, r6, r5
	add	r8, r8, #8192
	add	r4, r6, #256
	ldr	r2, [r5, #4]!
	mov	ip, r6
	mov	lr, #0
	mov	r9, #1
	cmp	r2, #0
	beq	.L664
.L684:
	ldr	r10, [ip, #256]
	cmp	r10, #0
	bne	.L678
	mov	r0, r4
	mov	r3, r10
	b	.L666
.L667:
	ldr	r1, [r0, #4]!
	cmp	r1, #0
	bne	.L669
.L666:
	add	r3, r3, #1
	cmp	r3, r2
	bne	.L667
	ldr	r3, [r6, #224]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	bne	.L673
	ldr	r1, [r8, #2112]
	add	r1, r1, #576
.L669:
	mov	r0, r4
	mov	r3, #0
	b	.L675
.L671:
	ldr	r10, [r0, #4]!
.L675:
	add	r3, r3, #1
	cmp	r10, #0
	streq	r1, [r0]
	cmp	r3, r2
	bne	.L671
.L672:
	add	lr, lr, #1
	add	r4, r4, #132
	cmp	r7, lr
	add	ip, ip, #132
	bls	.L677
	ldr	r2, [r5, #4]!
	cmp	r2, #0
	bne	.L684
.L664:
	ldr	r3, [r6, #224]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	bne	.L673
	str	r9, [r5]
	ldr	r3, [r8, #2112]
	add	r3, r3, #576
	str	r3, [ip, #256]
	b	.L672
.L678:
	mov	r1, r10
	b	.L669
.L676:
	mov	r7, #1
	b	.L662
	UNWIND(.fnend)
	.size	MVC_RepairList, .-MVC_RepairList
	.align	2
	.global	MVC_GetShortTermPicPoint
	.type	MVC_GetShortTermPicPoint, %function
MVC_GetShortTermPicPoint:
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
	add	r3, r0, #11075584
	add	r2, r3, #40960
	ldrb	r4, [r2, #521]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L686
	ldrb	r2, [r2, #522]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r4, #2
	moveq	r4, #1
.L686:
	add	r3, r3, #45056
	ldr	r5, [r3, #2384]
	cmp	r5, #0
	beq	.L694
	movw	r3, #47304
	mov	r2, #0
	movt	r3, 169
	add	r3, r0, r3
	b	.L691
.L704:
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L702
.L689:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L703
.L691:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L704
	ldrb	lr, [r0, #3]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L690
	ldr	ip, [r0, #612]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	beq	.L705
.L690:
	tst	lr, #2
	beq	.L689
	ldr	ip, [r0, #648]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L689
	ldr	ip, [r0, #660]
	cmp	ip, r1
	bne	.L689
	add	r0, r0, #648
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L702:
	ldr	ip, [r0, #576]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L689
	ldr	ip, [r0, #588]
	cmp	ip, r1
	bne	.L689
	add	r0, r0, #576
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L705:
	ldr	ip, [r0, #624]
	cmp	ip, r1
	bne	.L690
	add	r0, r0, #612
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L703:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L694:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetShortTermPicPoint, .-MVC_GetShortTermPicPoint
	.align	2
	.global	MVC_GetLongTermPicPoint
	.type	MVC_GetLongTermPicPoint, %function
MVC_GetLongTermPicPoint:
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
	add	r3, r0, #11075584
	add	r2, r3, #40960
	ldrb	r4, [r2, #521]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L707
	ldrb	r2, [r2, #522]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r4, #2
	moveq	r4, #1
.L707:
	add	r3, r3, #45056
	ldr	r5, [r3, #2388]
	cmp	r5, #0
	beq	.L715
	movw	r3, #47368
	mov	r2, #0
	movt	r3, 169
	add	r3, r0, r3
	b	.L712
.L725:
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L723
.L710:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L724
.L712:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L725
	ldrb	lr, [r0, #3]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L711
	ldr	ip, [r0, #612]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	beq	.L726
.L711:
	tst	lr, #2
	beq	.L710
	ldr	ip, [r0, #648]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L710
	ldr	ip, [r0, #656]
	cmp	ip, r1
	bne	.L710
	add	r0, r0, #648
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L723:
	ldr	ip, [r0, #576]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L710
	ldr	ip, [r0, #584]
	cmp	ip, r1
	bne	.L710
	add	r0, r0, #576
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L726:
	ldr	ip, [r0, #620]
	cmp	ip, r1
	bne	.L711
	add	r0, r0, #612
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L724:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L715:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetLongTermPicPoint, .-MVC_GetLongTermPicPoint
	.align	2
	.global	MVC_ReorderSTList
	.type	MVC_ReorderSTList, %function
MVC_ReorderSTList:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	ip, r1, asl #7
	ldr	r6, [fp, #4]
	add	r5, ip, r1, lsl #2
	mov	r1, r3
	add	r5, r5, #256
	mov	r7, r2
	mov	r4, r3
	add	r5, r0, r5
	bl	MVC_GetShortTermPicPoint
	ldr	lr, [r6]
	add	r2, r7, #1
	ldr	r8, [fp, #8]
	cmp	r2, lr
	ble	.L728
	add	ip, r5, r2, lsl #2
	mov	r1, r2
.L729:
	ldr	r3, [ip, #-4]!
	sub	r1, r1, #1
	str	r3, [ip, #4]
	ldr	lr, [r6]
	cmp	lr, r1
	blt	.L729
.L728:
	add	r3, lr, #1
	str	r3, [r6]
	str	r0, [r5, lr, asl #2]
	ldr	r0, [r6]
	cmp	r2, r0
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r7, r7, #2
	add	lr, r5, r0, lsl #2
	mov	ip, r0
	b	.L733
.L732:
	str	r1, [r5, ip, asl #2]
	add	ip, ip, #1
.L731:
	cmp	r0, r7
	beq	.L741
.L733:
	ldr	r1, [lr], #4
	add	r0, r0, #1
	cmp	r1, #0
	beq	.L731
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L732
	ldr	r3, [r1, #12]
	cmp	r3, r4
	bne	.L732
	ldr	r3, [r1, #4]
	ldr	r3, [r3, #56]
	cmp	r3, r8
	bne	.L732
	cmp	r0, r7
	bne	.L733
.L741:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ReorderSTList, .-MVC_ReorderSTList
	.align	2
	.global	MVC_ReorderLTList
	.type	MVC_ReorderLTList, %function
MVC_ReorderLTList:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	ip, r1, asl #7
	ldr	r6, [fp, #4]
	add	r5, ip, r1, lsl #2
	mov	r1, r3
	add	r5, r5, #256
	mov	r7, r2
	mov	r4, r3
	add	r5, r0, r5
	bl	MVC_GetLongTermPicPoint
	ldr	lr, [r6]
	add	r2, r7, #1
	ldr	r8, [fp, #8]
	cmp	r2, lr
	ble	.L743
	add	ip, r5, r2, lsl #2
	mov	r1, r2
.L744:
	ldr	r3, [ip, #-4]!
	sub	r1, r1, #1
	str	r3, [ip, #4]
	ldr	lr, [r6]
	cmp	lr, r1
	blt	.L744
.L743:
	add	r3, lr, #1
	str	r3, [r6]
	str	r0, [r5, lr, asl #2]
	ldr	r0, [r6]
	cmp	r2, r0
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r7, r7, #2
	add	lr, r5, r0, lsl #2
	mov	ip, r0
	b	.L748
.L747:
	str	r1, [r5, ip, asl #2]
	add	ip, ip, #1
.L746:
	cmp	r0, r7
	beq	.L759
.L748:
	ldr	r1, [lr], #4
	add	r0, r0, #1
	cmp	r1, #0
	beq	.L746
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L747
	ldr	r3, [r1, #8]
	cmp	r3, r4
	bne	.L747
	ldr	r3, [r1, #4]
	ldr	r3, [r3, #56]
	cmp	r3, r8
	bne	.L747
	cmp	r0, r7
	bne	.L748
.L759:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ReorderLTList, .-MVC_ReorderLTList
	.align	2
	.global	MVC_GetMaxViewIdx
	.type	MVC_GetMaxViewIdx, %function
MVC_GetMaxViewIdx:
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
	add	ip, r0, #10747904
	movw	lr, #22868
	add	ip, ip, #20480
	movt	lr, 164
	add	lr, r0, lr
	ldr	r5, [ip, #2384]
	adds	r5, r5, #1
	beq	.L767
	ldr	ip, [ip, #2388]
	cmp	r1, ip
	beq	.L768
	mov	r6, r5
	mov	ip, #0
	b	.L762
.L764:
	ldr	r4, [lr, #4]!
	cmp	r1, r4
	beq	.L770
.L762:
	add	ip, ip, #1
	cmp	ip, r5
	bne	.L764
	cmp	r6, #0
	blt	.L771
.L761:
	cmp	r2, #0
	add	r6, r6, r3, lsl #1
	movwne	r3, #5718
	movweq	r3, #5726
	movt	r3, 41
	add	r3, r6, r3
	add	r0, r0, r3, lsl #2
	ldr	r0, [r0, #4]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L770:
	mov	r6, ip
	cmp	r6, #0
	bge	.L761
.L771:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L767:
	mov	r6, r5
	b	.L761
.L768:
	mov	r6, #0
	b	.L761
	UNWIND(.fnend)
	.size	MVC_GetMaxViewIdx, .-MVC_GetMaxViewIdx
	.align	2
	.global	mvc_get_inter_view_pic
	.type	mvc_get_inter_view_pic, %function
mvc_get_inter_view_pic:
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
	movw	ip, #27166
	mov	r4, #1376
	movt	ip, 42
	add	ip, r3, ip
	mla	r3, r4, r3, r0
	ldr	lr, [r0, ip, asl #2]
	movw	ip, #31360
	cmp	lr, #0
	movt	ip, 169
	add	ip, r3, ip
	beq	.L778
	add	r4, r0, #11141120
	mov	r3, #0
	mov	r0, ip
	add	r4, r4, #8192
	b	.L777
.L774:
	cmp	r3, lr
	add	r0, r0, #688
	beq	.L780
.L777:
	ldr	ip, [r0, #56]
	add	r3, r3, #1
	cmp	ip, r1
	bne	.L774
	ldrb	ip, [r4, #1595]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L775
	ldr	ip, [r0, #596]
	cmp	ip, r2
	bne	.L774
	add	r0, r0, #576
	ldmfd	sp, {r4, fp, sp, pc}
.L775:
	cmp	ip, #1
	beq	.L781
	cmp	ip, #2
	bne	.L774
	ldr	ip, [r0, #668]
	cmp	ip, r2
	bne	.L774
	add	r0, r0, #648
	ldmfd	sp, {r4, fp, sp, pc}
.L781:
	ldr	ip, [r0, #632]
	cmp	ip, r2
	bne	.L774
	add	r0, r0, #612
	ldmfd	sp, {r4, fp, sp, pc}
.L780:
	mov	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L778:
	mov	r0, lr
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	mvc_get_inter_view_pic, .-mvc_get_inter_view_pic
	.align	2
	.global	mvc_reorder_interview
	.type	mvc_reorder_interview, %function
mvc_reorder_interview:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [fp, #8]
	mov	r7, r2
	ldr	r6, [fp, #4]
	mov	r5, r3
	mov	r8, r1
	mov	r1, r3
	mov	r2, r4, asl #7
	mov	r3, r4
	add	r4, r2, r4, lsl #2
	mov	r2, r6
	add	r4, r4, #256
	add	r4, r0, r4
	bl	mvc_get_inter_view_pic
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	ip, [r7]
	add	r1, r8, #1
	cmp	r1, ip
	bls	.L784
	add	r2, r4, r1, lsl #2
	mov	r3, r1
.L785:
	ldr	ip, [r2, #-4]!
	sub	r3, r3, #1
	str	ip, [r2, #4]
	ldr	ip, [r7]
	cmp	ip, r3
	bcc	.L785
.L784:
	add	r3, ip, #1
	str	r3, [r7]
	str	r0, [r4, ip, asl #2]
	ldr	r2, [r7]
	cmp	r1, r2
	ldmccfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	ip, r4, r2, lsl #2
	mov	r0, r2
	b	.L789
.L787:
	cmp	r1, r2
	str	r3, [r4, r0, asl #2]
	add	r0, r0, #1
	bcc	.L796
.L789:
	ldr	r3, [ip], #4
	add	r2, r2, #1
	cmp	r3, #0
	beq	.L787
	ldr	lr, [r3, #4]
	ldr	lr, [lr, #56]
	cmp	lr, r5
	bne	.L787
	ldr	lr, [r3, #20]
	cmp	lr, r6
	bne	.L787
	cmp	r1, r2
	bcs	.L789
.L796:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	mvc_reorder_interview, .-mvc_reorder_interview
	.align	2
	.global	MVC_ReorderRefPiclist
	.type	MVC_ReorderRefPiclist, %function
MVC_ReorderRefPiclist:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
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
	add	r6, r0, #11075584
	add	r9, r6, #40960
	str	r2, [fp, #-64]
	mov	r2, #0
	mov	r5, r0
	ldrb	r3, [r9, #521]	@ zero_extendqisi2
	mov	r10, r1
	str	r2, [fp, #-48]
	cmp	r3, r2
	beq	.L798
	ldrb	r3, [r9, #522]	@ zero_extendqisi2
	cmp	r3, r2
	movne	r3, #2
	moveq	r3, #1
.L798:
	cmp	r10, #1
	bls	.L846
.L797:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L846:
	cmp	r10, #0
	beq	.L847
	movw	r1, #40564
	movw	r8, #40828
	movw	r6, #41348
	movt	r1, 169
	movt	r8, 169
	movt	r6, 169
	add	r1, r5, r1
	add	r8, r5, r8
	add	r6, r5, r6
	movw	r2, #41088
	movt	r2, 169
	add	r2, r5, r2
	str	r2, [fp, #-100]
.L801:
	ldr	r0, [r5, #236]
	cmp	r3, #0
	mov	r2, #1
	ldr	r3, [r0, #2896]
	add	r3, r3, #4
	mov	r3, r2, asl r3
	str	r3, [fp, #-88]
	ldr	r3, [r9, #548]
	ldrne	r2, [fp, #-88]
	movne	r3, r3, asl #1
	addne	r3, r3, #1
	str	r3, [fp, #-92]
	ldr	r3, [fp, #-64]
	movne	r2, r2, asl #1
	strne	r2, [fp, #-88]
	adds	r3, r3, #2
	str	r3, [fp, #-72]
	beq	.L797
	ldr	r2, [r1]
	cmp	r2, #3
	beq	.L797
	movw	r3, #22868
	str	r9, [fp, #-68]
	mov	r0, r3
	mov	r3, #0
	mov	r4, r3
	str	r3, [fp, #-76]
	str	r3, [fp, #-80]
	mov	r7, r3
	ldr	r3, [fp, #-92]
	movt	r0, 164
	mov	r9, r1
	add	r0, r5, r0
	str	r0, [fp, #-96]
	str	r3, [fp, #-60]
	mov	r3, #1
	str	r3, [fp, #-84]
	b	.L805
.L806:
	cmp	r2, #2
	beq	.L848
	ldr	r3, [fp, #-84]
	cmp	r3, #1
	beq	.L812
	ldr	r3, [fp, #-68]
	ldrb	r3, [r3, #529]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	mov	r3, r10, asl #1
.L813:
	cmp	r2, #4
	ldr	r2, [r6]
	beq	.L849
	add	r2, r2, #1
	add	r4, r2, r4
	ldr	r2, [fp, #-76]
	cmp	r2, r4
	rsble	r4, r2, r4
.L823:
	ldr	r2, [fp, #-56]
	add	r0, r5, #11141120
	add	r0, r0, #8192
	ldr	r1, [fp, #-64]
	cmp	r2, #0
	ldr	r2, [fp, #-80]
	add	r3, r3, r2
	movwne	r2, #5722
	add	r3, r3, r4
	movweq	r2, #5730
	movt	r2, 41
	add	r2, r3, r2
	add	r2, r5, r2, lsl #2
	ldr	r3, [r2, #4]
	sub	r2, fp, #48
	str	r10, [sp, #4]
	ldr	ip, [r0, #2132]
	mov	r0, r5
	str	ip, [sp]
	bl	mvc_reorder_interview
.L810:
	ldr	r3, [fp, #-72]
	add	r7, r7, #1
	cmp	r7, r3
	beq	.L797
	ldr	r2, [r9, #4]!
	add	r6, r6, #4
	add	r8, r8, #4
	cmp	r2, #3
	beq	.L797
.L805:
	cmp	r2, #1
	bhi	.L806
	cmp	r2, #0
	ldr	r3, [r8]
	bne	.L807
	ldr	r2, [fp, #-60]
	mvn	r3, r3
	adds	r3, r2, r3
	str	r3, [fp, #-60]
	bmi	.L850
.L808:
	ldr	r2, [fp, #-60]
	mov	r1, r10
	ldr	r3, [fp, #-92]
	mov	r0, r5
	cmp	r3, r2
	movlt	r3, r2
	ldrlt	r2, [fp, #-88]
	ldrge	r3, [fp, #-60]
	rsblt	r3, r2, r3
	ldr	r2, [fp, #-68]
	ldr	ip, [r2, #2160]
	sub	r2, fp, #48
	str	r2, [sp]
	ldr	r2, [fp, #-64]
	str	ip, [sp, #4]
	bl	MVC_ReorderSTList
	b	.L810
.L847:
	movw	r1, #40432
	movw	r8, #40696
	movt	r1, 169
	movt	r8, 169
	add	r6, r6, #41216
	add	r1, r5, r1
	add	r8, r5, r8
	str	r9, [fp, #-100]
	b	.L801
.L849:
	mvn	r2, r2
	adds	r4, r2, r4
	ldrmi	r2, [fp, #-76]
	addmi	r4, r4, r2
	b	.L823
.L812:
	ldr	r1, [fp, #-68]
	add	r3, r5, #10747904
	add	r3, r3, #20480
	ldr	r0, [r1, #2160]
	ldr	r1, [r3, #2384]
	adds	r1, r1, #1
	beq	.L814
	ldr	r3, [r3, #2388]
	cmp	r0, r3
	beq	.L815
	ldr	ip, [fp, #-96]
	mov	r3, #0
	str	r1, [fp, #-80]
	b	.L816
.L818:
	ldr	lr, [ip, #4]!
	cmp	r0, lr
	beq	.L832
.L816:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L818
.L817:
	ldr	r3, [fp, #-68]
	mov	r4, r1
	ldr	ip, [fp, #-96]
	ldrb	r3, [r3, #529]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	mov	r3, #0
	b	.L828
.L820:
	ldr	lr, [ip, #4]!
	cmp	r0, lr
	beq	.L833
.L828:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L820
	cmp	r4, #0
	blt	.L834
.L827:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	mov	r3, r10, asl #1
	beq	.L821
	add	r4, r3, r4
	movw	r1, #5718
	movt	r1, 41
	add	r1, r4, r1
	mov	r0, #0
	str	r0, [fp, #-84]
	add	r1, r5, r1, lsl #2
	mvn	r4, #0
	ldr	r1, [r1, #4]
	str	r1, [fp, #-76]
	b	.L813
.L807:
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	add	r3, r2, r3
	ldr	r2, [fp, #-88]
	str	r3, [fp, #-60]
	cmp	r2, r3
	rsble	r3, r2, r3
	strle	r3, [fp, #-60]
	b	.L808
.L848:
	ldr	r1, [fp, #-68]
	sub	r0, fp, #48
	ldr	r3, [fp, #-100]
	ldr	r2, [fp, #-64]
	ldr	ip, [r1, #2160]
	mov	r1, r10
	ldr	r3, [r3, r7, asl #2]
	str	r0, [sp]
	mov	r0, r5
	str	ip, [sp, #4]
	bl	MVC_ReorderLTList
	b	.L810
.L832:
	str	r3, [fp, #-80]
	b	.L817
.L833:
	mov	r4, r3
	cmp	r4, #0
	bge	.L827
.L834:
	mov	r3, #0
	mvn	r4, #0
	mov	r1, r3
	str	r3, [fp, #-84]
	str	r1, [fp, #-76]
	mov	r3, r10, asl #1
	b	.L813
.L821:
	add	r4, r3, r4
	movw	r1, #5726
	movt	r1, 41
	add	r1, r4, r1
	ldr	r0, [fp, #-56]
	mvn	r4, #0
	add	r1, r5, r1, lsl #2
	str	r0, [fp, #-84]
	ldr	r1, [r1, #4]
	str	r1, [fp, #-76]
	b	.L813
.L850:
	ldr	r2, [fp, #-88]
	add	r3, r3, r2
	str	r3, [fp, #-60]
	b	.L808
.L814:
	ldr	r3, [fp, #-68]
	mov	r4, r1
	str	r1, [fp, #-80]
	ldrb	r3, [r3, #529]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	b	.L827
.L815:
	ldr	r1, [fp, #-68]
	mov	r3, #0
	mov	r4, r3
	str	r3, [fp, #-80]
	ldrb	r1, [r1, #529]	@ zero_extendqisi2
	str	r1, [fp, #-56]
	b	.L827
	UNWIND(.fnend)
	.size	MVC_ReorderRefPiclist, .-MVC_ReorderRefPiclist
	.align	2
	.global	MVC_ReorderListX
	.type	MVC_ReorderListX, %function
MVC_ReorderListX:
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
	add	r4, r0, #11075584
	mov	r6, r0
	add	r5, r4, #40960
	ldrb	r1, [r5, #520]	@ zero_extendqisi2
	cmp	r1, #2
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r7, r4, #36864
	ldrb	r3, [r7, #3564]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L863
.L854:
	ldr	r3, [r5, #580]
	cmp	r1, #1
	add	r3, r3, #1
	str	r3, [r5, #568]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r7, #3565]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L864
.L856:
	add	r4, r4, #40960
	ldr	r3, [r4, #584]
	add	r3, r3, #1
	str	r3, [r4, #572]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L863:
	mov	r1, #0
	ldr	r2, [r5, #580]
	bl	MVC_ReorderRefPiclist
	ldrb	r1, [r5, #520]	@ zero_extendqisi2
	b	.L854
.L864:
	ldr	r2, [r5, #584]
	mov	r0, r6
	bl	MVC_ReorderRefPiclist
	b	.L856
	UNWIND(.fnend)
	.size	MVC_ReorderListX, .-MVC_ReorderListX
	.align	2
	.global	MVC_GenPiclistfromFrmlist
	.type	MVC_GenPiclistfromFrmlist, %function
MVC_GenPiclistfromFrmlist:
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
	ldr	lr, .L928
	movcc	r4, r2
	ldr	ip, .L928+4
	movcs	r4, #31
	cmp	r6, #0
	str	r3, [fp, #-52]
	movne	r6, lr
	moveq	r6, ip
	cmp	r0, #1
	moveq	r5, #0
	moveq	r10, r5
	beq	.L868
	cmp	r0, #2
	moveq	r5, #0
	moveq	r10, r5
	bne	.L876
.L877:
	cmp	r10, r4
	movcs	r3, #0
	movcc	r3, #1
	cmp	r5, r4
	str	r3, [fp, #-48]
	movcs	r2, #0
	movcc	r2, #1
	orrs	r3, r2, r3
	beq	.L876
	cmp	r2, #0
	beq	.L882
	add	r8, r7, r5, lsl #2
	b	.L881
.L878:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L882
.L881:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	tst	ip, #2
	beq	.L878
	add	r0, r0, #648
	blx	r6
	cmp	r0, #0
	beq	.L878
	ldr	r3, [fp, #4]
	add	r5, r5, #1
	ldr	r2, [r9]
	ldr	r0, [r3]
	add	r2, r2, #648
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L882:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r10, lsl #2
	bne	.L884
	b	.L877
.L883:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L877
.L884:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	tst	r1, #1
	beq	.L883
	add	r0, r0, #612
	blx	r6
	cmp	r0, #0
	beq	.L883
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r9]
	ldr	r1, [r3]
	add	r2, r2, #612
	ldr	r3, [fp, #-52]
	str	r2, [r3, r1, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
	b	.L877
.L927:
	add	r0, r0, #612
	blx	r6
	cmp	r0, #0
	beq	.L869
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r8]
	ldr	r0, [r3]
	add	r2, r2, #612
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L873:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r5, lsl #2
	bne	.L875
	b	.L868
.L874:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L868
.L875:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	tst	r1, #2
	beq	.L874
	add	r0, r0, #648
	blx	r6
	cmp	r0, #0
	beq	.L874
	ldr	r3, [fp, #4]
	add	r5, r5, #1
	ldr	r2, [r9]
	ldr	r1, [r3]
	add	r2, r2, #648
	ldr	r3, [fp, #-52]
	str	r2, [r3, r1, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L868:
	cmp	r10, r4
	movcs	r2, #0
	movcc	r2, #1
	cmp	r5, r4
	movcs	r3, #0
	movcc	r3, #1
	str	r3, [fp, #-48]
	orrs	r3, r3, r2
	beq	.L876
	cmp	r2, #0
	beq	.L873
	add	r9, r7, r10, lsl #2
	b	.L872
.L869:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L873
.L872:
	mov	r8, r9
	ldr	r0, [r9], #4
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	tst	ip, #1
	beq	.L869
	b	.L927
.L876:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L929:
	.align	2
.L928:
	.word	MVC_IsLTRefFlg
	.word	MVC_IsSTRefFlg
	UNWIND(.fnend)
	.size	MVC_GenPiclistfromFrmlist, .-MVC_GenPiclistfromFrmlist
	.align	2
	.global	MVC_GetBaseViewId
	.type	MVC_GetBaseViewId, %function
MVC_GetBaseViewId:
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
	add	r3, r0, #12992
	mov	r2, #0
	add	r3, r3, #16
.L933:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L931
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L941
.L931:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L933
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L941:
	movw	r3, #8500
	movt	r3, 5
	mla	r2, r3, r2, r0
	add	r2, r2, #12992
	ldr	r0, [r2, #20]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetBaseViewId, .-MVC_GetBaseViewId
	.align	2
	.global	MVC_GetVOIdx
	.type	MVC_GetVOIdx, %function
MVC_GetVOIdx:
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
	beq	.L946
	ldr	r3, [r0]
	cmp	r3, r2
	beq	.L947
	mov	ip, r0
	mov	r3, #0
	mov	r0, r1
	b	.L944
.L945:
	ldr	lr, [ip, #4]!
	cmp	lr, r2
	beq	.L948
.L944:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L945
	ldmfd	sp, {fp, sp, pc}
.L948:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L946:
	mov	r0, r1
	ldmfd	sp, {fp, sp, pc}
.L947:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetVOIdx, .-MVC_GetVOIdx
	.align	2
	.global	MVC_is_view_id_in_ref_view_list
	.type	MVC_is_view_id_in_ref_view_list, %function
MVC_is_view_id_in_ref_view_list:
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
	beq	.L953
	ldr	r3, [r1]
	cmp	r3, r0
	beq	.L954
	mov	r3, #0
	b	.L951
.L952:
	ldr	ip, [r1, #4]!
	cmp	ip, r0
	beq	.L950
.L951:
	add	r3, r3, #1
	cmp	r3, r2
	mov	lr, r3
	bne	.L952
.L950:
	cmp	r2, #0
	cmpne	r2, lr
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L953:
	mov	lr, r2
	b	.L950
.L954:
	mov	lr, #0
	b	.L950
	UNWIND(.fnend)
	.size	MVC_is_view_id_in_ref_view_list, .-MVC_is_view_id_in_ref_view_list
	.align	2
	.global	MVC_GenPiclistfromFrmlist_Interview
	.type	MVC_GenPiclistfromFrmlist_Interview, %function
MVC_GenPiclistfromFrmlist_Interview:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #1
	ldr	ip, [fp, #4]
	beq	.L971
	cmp	r0, #2
	ldmnefd	sp, {fp, sp, pc}
	cmp	r2, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r0, [ip]
	add	r1, r1, #648
	mov	lr, #0
.L962:
	add	lr, lr, #1
	str	r1, [r3, r0, asl #2]
	cmp	lr, r2
	ldr	r0, [ip]
	add	r1, r1, #688
	add	r0, r0, #1
	str	r0, [ip]
	bne	.L962
	ldmfd	sp, {fp, sp, pc}
.L971:
	cmp	r2, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r0, [ip]
	add	r1, r1, #612
	mov	lr, #0
.L958:
	add	lr, lr, #1
	str	r1, [r3, r0, asl #2]
	cmp	lr, r2
	ldr	r0, [ip]
	add	r1, r1, #688
	add	r0, r0, #1
	str	r0, [ip]
	bne	.L958
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GenPiclistfromFrmlist_Interview, .-MVC_GenPiclistfromFrmlist_Interview
	.align	2
	.global	mvc_append_interview_list
	.type	mvc_append_interview_list, %function
mvc_append_interview_list:
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
	add	lr, r0, #10747904
	add	lr, lr, #20480
	add	ip, r0, #11075584
	add	r4, ip, #40960
	mov	r9, r0
	ldr	r5, [lr, #2384]
	movw	r0, #22868
	movt	r0, 164
	str	r2, [fp, #-52]
	adds	r5, r5, #1
	str	r3, [fp, #-48]
	ldr	r6, [r4, #2160]
	add	r0, r9, r0
	beq	.L991
	ldr	r3, [lr, #2388]
	cmp	r6, r3
	beq	.L992
	mov	r2, r0
	mov	r3, #0
	b	.L974
.L975:
	ldr	r0, [r2, #4]!
	cmp	r6, r0
	beq	.L973
.L974:
	add	r3, r3, #1
	cmp	r3, r5
	mov	lr, r3
	bne	.L975
.L973:
	ldrb	r3, [r4, #529]	@ zero_extendqisi2
	add	lr, lr, r1, lsl #1
	add	r6, r9, #11141120
	add	ip, ip, #45056
	cmp	r3, #0
	add	r6, r6, #8192
	movwne	r3, #5718
	movweq	r3, #5726
	movtne	r3, 41
	movteq	r3, 41
	addne	r3, lr, r3
	addeq	r3, lr, r3
	ldrb	r8, [r6, #1595]	@ zero_extendqisi2
	addne	lr, r9, lr, lsl #2
	add	r3, r9, r3, lsl #2
	movwne	r10, #22892
	sub	r8, r8, #2
	addeq	lr, r9, lr, lsl #2
	ldr	r7, [r3, #4]
	movweq	r10, #22924
	ldr	r3, [ip, #2376]
	clz	r8, r8
	movt	r10, 164
	add	r10, lr, r10
	subs	r4, r3, #1
	mov	r8, r8, lsr #5
	bmi	.L972
	movw	r5, #28194
	str	r9, [fp, #-56]
	movt	r5, 42
	add	r5, r3, r5
	add	r5, r9, r5, lsl #2
	ldr	r9, [fp, #-48]
	b	.L989
.L1015:
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r3, #3
	ldreq	r2, [r1, #596]
	bne	.L979
.L981:
	add	r3, r1, r8
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L979
	ldr	r3, [r6, #2132]
	cmp	r3, r2
	beq	.L1014
.L979:
	subs	r4, r4, #1
	bmi	.L972
.L989:
	ldr	r1, [r5, #-4]!
	cmp	r1, #0
	beq	.L979
	ldrb	r3, [r6, #1595]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1015
	cmp	r3, #1
	beq	.L1016
	cmp	r3, #2
	bne	.L979
	ldrb	r2, [r6, #1593]	@ zero_extendqisi2
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	ubfx	r3, r3, #1, #1
	beq	.L984
	ldr	r2, [r6, #2112]
	ldr	r0, [r1, #632]
	ldr	r2, [r2, #632]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L984:
	cmp	r3, #0
	ldrne	r2, [r1, #668]
	bne	.L981
	subs	r4, r4, #1
	bpl	.L989
.L972:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1016:
	ldrb	r2, [r6, #1593]	@ zero_extendqisi2
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	and	r3, r3, #1
	beq	.L983
	ldr	r2, [r6, #2112]
	ldr	r0, [r1, #668]
	ldr	r2, [r2, #668]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L983:
	cmp	r3, #0
	ldrne	r2, [r1, #632]
	bne	.L981
	b	.L979
.L1014:
	cmp	r7, #0
	ldr	ip, [r1, #56]
	beq	.L979
	ldr	r3, [r10]
	cmp	ip, r3
	beq	.L985
	mov	r2, r10
	mov	r3, #0
.L986:
	add	r3, r3, #1
	cmp	r3, r7
	beq	.L979
	ldr	r0, [r2, #4]!
	cmp	ip, r0
	bne	.L986
.L985:
	ldr	ip, [fp, #-52]
	mov	r2, #688
	ldr	r0, [r9]
	ldr	r3, .L1017
	mla	r0, r2, r0, ip
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [r9]
	ldr	ip, [fp, #-52]
	mov	r2, #688
	mov	r1, #688
	mla	r3, r2, r3, ip
	ldr	r2, [fp, #-56]
	str	r3, [r3, #652]
	str	r3, [r3, #616]
	str	r3, [r3, #580]
	ldr	r3, [r9]
	ldr	r2, [r2, #52]
	mla	r3, r1, r3, ip
	sub	r2, r2, #1
	str	r2, [r3, #48]
	ldr	r3, [r9]
	cmp	r3, r7
	beq	.L972
	add	r3, r3, #1
	str	r3, [r9]
	b	.L979
.L991:
	mov	lr, r5
	b	.L973
.L992:
	mov	lr, #0
	b	.L973
.L1018:
	.align	2
.L1017:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	mvc_append_interview_list, .-mvc_append_interview_list
	.align	2
	.global	MVC_InitListX
	.type	MVC_InitListX, %function
MVC_InitListX:
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
	add	r2, r0, #11075584
	add	r4, r2, #40960
	mov	r3, #0
	add	r6, r0, #11141120
	mov	r5, r0
	ldrb	r9, [r4, #520]	@ zero_extendqisi2
	add	r6, r6, #8192
	str	r3, [r4, #2172]
	cmp	r9, r3
	str	r3, [r4, #2168]
	bne	.L1020
	ldrb	r7, [r6, #1595]	@ zero_extendqisi2
	cmp	r7, r3
	add	r3, r2, #45056
	str	r3, [fp, #-240]
	bne	.L1178
	ldr	ip, [r3, #2384]
	cmp	ip, #0
	beq	.L1104
	movw	r1, #47300
	mov	r3, r7
	movt	r1, 169
	add	r1, r0, r1
	b	.L1026
.L1025:
	cmp	r3, ip
	beq	.L1024
.L1026:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1025
	ldr	r0, [r2, #576]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #65536
	addeq	r0, r7, #64
	addeq	r2, r2, #576
	addeq	r7, r7, #1
	streq	r2, [r5, r0, asl #2]
	cmp	r3, ip
	bne	.L1026
.L1024:
	add	r3, r5, #256
	mov	r1, r7
	str	r3, [fp, #-244]
	mov	r2, #4
	mov	r0, r3
	ldr	r3, .L1189
	bl	qsort
	ldr	r3, [fp, #-240]
	str	r7, [r4, #568]
	ldr	r1, [r3, #2388]
	cmp	r1, #0
	beq	.L1105
	movw	r0, #47364
	mov	r8, r7
	movt	r0, 169
	mov	r3, #0
	add	r0, r5, r0
	b	.L1029
.L1028:
	cmp	r3, r1
	beq	.L1179
.L1029:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #3]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1028
	ldr	ip, [r2, #576]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	addeq	ip, r8, #64
	addeq	r2, r2, #576
	addeq	r8, r8, #1
	streq	r2, [r5, ip, asl #2]
	cmp	r3, r1
	bne	.L1029
.L1179:
	rsb	r1, r7, r8
.L1027:
	add	r0, r7, #64
	ldr	r3, .L1189+4
	mov	r2, #4
	add	r0, r5, r0, lsl #2
	bl	qsort
	str	r8, [r4, #568]
	b	.L1030
.L1020:
	ldrb	r8, [r6, #1595]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L1047
	add	r2, r2, #45056
	str	r2, [fp, #-240]
	ldr	r10, [r2, #2384]
	cmp	r10, #0
	beq	.L1180
	movw	r7, #47300
	mov	r8, r3
	movt	r7, 169
	add	r7, r0, r7
	mov	r1, r7
.L1066:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1065
	sub	r0, fp, #44
	ldr	ip, [r6, #2132]
	add	lr, r0, r8, lsl #2
	ldr	r0, [r2, #32]
	cmp	ip, r0
	strge	r2, [lr, #-192]
	addge	r8, r8, #1
.L1065:
	cmp	r3, r10
	bne	.L1066
	sub	r3, fp, #236
	mov	r2, #4
	str	r3, [fp, #-248]
	mov	r1, r8
	mov	r0, r3
	ldr	r3, .L1189+8
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r9, [r3, #2384]
	cmp	r9, #0
	beq	.L1175
.L1102:
	mov	r1, r7
	mov	r3, #0
	mov	r7, r8
.L1069:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1068
	sub	r0, fp, #44
	ldr	ip, [r6, #2132]
	add	lr, r0, r7, lsl #2
	ldr	r0, [r2, #32]
	cmp	ip, r0
	strlt	r2, [lr, #-192]
	addlt	r7, r7, #1
.L1068:
	cmp	r3, r9
	bne	.L1069
	ldr	r2, [fp, #-248]
	rsb	r9, r8, r7
	mov	r3, r8, asl #2
	str	r3, [fp, #-244]
	add	r0, r2, r3
	mov	r1, r9
	ldr	r3, .L1189+12
	mov	r2, #4
	bl	qsort
	cmp	r8, #0
	subeq	r10, fp, #172
	beq	.L1070
.L1097:
	sub	r10, fp, #172
	ldr	r2, [fp, #-248]
	add	r9, r10, r9, lsl #2
	mov	r3, #0
.L1071:
	add	r3, r3, #1
	ldr	r1, [r2], #4
	cmp	r3, r8
	str	r1, [r9], #4
	bcc	.L1071
.L1070:
	cmp	r7, r8
	bls	.L1072
	ldr	r3, [fp, #-248]
	ldr	r2, [fp, #-244]
	add	r2, r3, r2
	mov	r3, r10
.L1073:
	add	r8, r8, #1
	ldr	r1, [r2], #4
	cmp	r8, r7
	str	r1, [r3], #4
	bne	.L1073
.L1072:
	movw	r9, #41528
	mov	r3, #0
	ldr	r1, [fp, #-248]
	mov	r2, #0
	str	r3, [r4, #568]
	movt	r9, 169
	str	r3, [r4, #572]
	add	r9, r5, r9
	add	r3, r5, #256
	ldrb	r0, [r6, #1595]	@ zero_extendqisi2
	movw	r8, #41532
	str	r2, [sp, #4]
	str	r9, [sp]
	mov	r2, r7
	str	r3, [fp, #-244]
	movt	r8, 169
	bl	MVC_GenPiclistfromFrmlist
	add	r8, r5, r8
	ldrb	r0, [r6, #1595]	@ zero_extendqisi2
	add	r3, r5, #388
	mov	r2, #0
	mov	r1, r10
	str	r2, [sp, #4]
	mov	r2, r7
	str	r8, [sp]
	str	r3, [fp, #-248]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	ldr	r7, [r3, #2388]
	cmp	r7, #0
	subeq	r10, fp, #108
	beq	.L1074
	movw	r2, #47364
	sub	r10, fp, #108
	movt	r2, 169
	add	r2, r5, r2
	mov	r3, #0
	mov	r1, r10
.L1075:
	add	r3, r3, #1
	ldr	r0, [r2, #4]!
	cmp	r3, r7
	str	r0, [r1], #4
	bne	.L1075
.L1074:
	ldr	r3, .L1189+16
	mov	r2, #4
	mov	r1, r7
	mov	r0, r10
	bl	qsort
	ldrb	r0, [r6, #1595]	@ zero_extendqisi2
	ldr	r3, [fp, #-244]
	mov	r2, r7
	str	r9, [sp]
	mov	r1, r10
	mov	r9, #1
	str	r9, [sp, #4]
	bl	MVC_GenPiclistfromFrmlist
	ldrb	r0, [r6, #1595]	@ zero_extendqisi2
	ldr	r3, [fp, #-248]
	mov	r2, r7
	str	r8, [sp]
	mov	r1, r10
	str	r9, [sp, #4]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r8, [r4, #568]
	ldr	r3, [r4, #572]
	rsb	r3, r3, r8
	clz	r3, r3
	mov	r3, r3, lsr #5
.L1064:
	cmp	r8, #1
	movls	r3, #0
	andhi	r3, r3, #1
	cmp	r3, #0
	beq	.L1076
	cmp	r8, #0
	beq	.L1077
	ldr	lr, [r5, #256]
	ldr	r3, [r5, #388]
	cmp	lr, r3
	bne	.L1076
	ldr	r1, [fp, #-244]
	add	r2, r5, #388
	mov	r3, #0
	b	.L1078
.L1079:
	ldr	ip, [r1, #4]!
	ldr	r0, [r2, #4]!
	cmp	ip, r0
	bne	.L1076
.L1078:
	add	r3, r3, #1
	cmp	r3, r8
	bne	.L1079
.L1080:
	ldr	r3, [r5, #392]
	str	lr, [r5, #392]
	str	r3, [r5, #388]
	ldrb	r3, [r4, #532]	@ zero_extendqisi2
.L1098:
	cmp	r3, #0
	bne	.L1167
.L1081:
	movw	r7, #31360
	movw	r3, #43128
	movt	r7, 169
	add	r7, r5, r7
	mov	r0, r5
	movt	r3, 169
	mov	r1, #0
	mov	r2, r7
	add	r3, r5, r3
	bl	mvc_append_interview_list
	ldrb	r0, [r6, #1595]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1181
	ldr	r1, [r4, #2168]
	ldr	ip, [r4, #568]
	cmp	r1, #0
	beq	.L1083
	add	r2, ip, #63
	movw	r3, #31936
	movt	r3, 169
	add	r3, r5, r3
	add	r2, r5, r2, lsl #2
.L1084:
	add	r0, r0, #1
	str	r3, [r2, #4]!
	cmp	r0, r1
	add	r3, r3, #688
	bne	.L1084
	add	ip, ip, r0
.L1083:
	str	ip, [r4, #568]
.L1085:
	ldrb	r1, [r4, #520]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1182
.L1168:
	ldr	r0, [r4, #568]
.L1082:
	cmp	r1, #0
	bne	.L1040
	cmp	r0, #0
	beq	.L1183
.L1039:
	ldr	r2, [r4, #580]
	ldr	r3, [r4, #584]
	add	r2, r2, #1
	ldr	r1, [r4, #572]
	cmp	r0, r2
	add	r3, r3, #1
	movcc	r2, r0
	cmp	r3, r1
	str	r2, [r4, #568]
	movcs	r3, r1
	cmp	r2, #32
	str	r3, [r4, #572]
	bhi	.L1091
.L1099:
	add	r1, r2, #63
	mov	r0, #0
	add	r1, r5, r1, lsl #2
.L1092:
	add	r2, r2, #1
	str	r0, [r1, #4]!
	cmp	r2, #32
	bls	.L1092
.L1091:
	cmp	r3, #32
	bhi	.L1095
	add	r3, r3, #96
	add	r1, r5, #516
	mov	r2, #0
	add	r5, r5, r3, lsl #2
.L1094:
	str	r2, [r5, #4]!
	cmp	r5, r1
	bne	.L1094
.L1095:
	mov	r0, #0
.L1161:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1047:
	add	r3, r2, #45056
	str	r3, [fp, #-240]
	ldr	r10, [r3, #2384]
	cmp	r10, #0
	beq	.L1050
	movw	r7, #47300
	mov	r3, r8
	movt	r7, 169
	add	r7, r0, r7
	mov	r1, r7
	b	.L1052
.L1051:
	cmp	r3, r10
	beq	.L1184
.L1052:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1051
	ldr	r0, [r2, #592]
	add	lr, r8, #64
	ldr	ip, [r6, #2136]
	add	r2, r2, #576
	cmp	ip, r0
	strge	r2, [r5, lr, asl #2]
	addge	r8, r8, #1
	cmp	r3, r10
	bne	.L1052
.L1184:
	add	r3, r5, #256
	mov	r2, #4
	str	r3, [fp, #-244]
	mov	r1, r8
	mov	r0, r3
	ldr	r3, .L1189+20
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r9, [r3, #2384]
	cmp	r9, #0
	beq	.L1174
.L1100:
	mov	r10, r8
	mov	r3, #0
	b	.L1055
.L1054:
	cmp	r3, r9
	beq	.L1185
.L1055:
	ldr	r2, [r7, #4]!
	add	r3, r3, #1
	ldrb	r1, [r2, #3]	@ zero_extendqisi2
	cmp	r1, #3
	bne	.L1054
	ldr	r1, [r2, #592]
	add	ip, r10, #64
	ldr	r0, [r6, #2136]
	add	r2, r2, #576
	cmp	r0, r1
	strlt	r2, [r5, ip, asl #2]
	addlt	r10, r10, #1
	cmp	r3, r9
	bne	.L1055
.L1185:
	rsb	r9, r8, r10
	add	r0, r8, #64
	ldr	r3, .L1189+24
	mov	r2, #4
	mov	r1, r9
	add	r0, r5, r0, lsl #2
	bl	qsort
	add	r7, r10, #64
	cmp	r8, #0
	add	r7, r5, r7, lsl #2
	beq	.L1057
.L1096:
	add	r9, r9, #96
	add	r2, r5, #252
	mov	r3, #0
	add	r9, r5, r9, lsl #2
.L1058:
	add	r3, r3, #1
	ldr	r1, [r2, #4]!
	cmp	r3, r8
	str	r1, [r9, #4]!
	bcc	.L1058
.L1057:
	cmp	r10, r8
	bls	.L1059
	add	r3, r8, #63
	add	r2, r5, #384
	add	r3, r5, r3, lsl #2
.L1060:
	add	r8, r8, #1
	ldr	r1, [r3, #4]!
	cmp	r8, r10
	str	r1, [r2, #4]!
	bne	.L1060
.L1059:
	ldr	r3, [fp, #-240]
	str	r10, [r4, #572]
	str	r10, [r4, #568]
	ldr	r1, [r3, #2388]
	cmp	r1, #0
	beq	.L1106
	movw	r0, #47364
	mov	r8, r10
	movt	r0, 169
	mov	r3, #0
	add	r0, r5, r0
	b	.L1063
.L1062:
	cmp	r3, r1
	beq	.L1186
.L1063:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #2]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1062
	ldrb	ip, [r2, #577]	@ zero_extendqisi2
	cmp	ip, #1
	addeq	ip, r5, r8, lsl #2
	addeq	r2, r2, #576
	addeq	r8, r8, #1
	streq	r2, [ip, #256]
	streq	r2, [ip, #388]
	cmp	r3, r1
	bne	.L1063
.L1186:
	rsb	r1, r10, r8
.L1061:
	mov	r0, r7
	ldr	r3, .L1189+4
	mov	r2, #4
	bl	qsort
	ldr	r1, [r4, #568]
	ldr	r3, .L1189+4
	mov	r2, #4
	add	r0, r1, #97
	rsb	r1, r1, r8
	add	r0, r5, r0, lsl #2
	bl	qsort
	str	r8, [r4, #572]
	str	r8, [r4, #568]
	mov	r3, #1
	b	.L1064
.L1178:
	ldr	lr, [r3, #2384]
	cmp	lr, #0
	moveq	r9, lr
	beq	.L1023
	movw	r1, #47300
	mov	r3, r9
	movt	r1, 169
	add	r1, r0, r1
.L1032:
	ldr	r2, [r1, #4]!
	sub	r0, fp, #44
	add	ip, r0, r9, lsl #2
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #0
	strne	r2, [ip, #-192]
	addne	r9, r9, #1
	cmp	r3, lr
	bne	.L1032
.L1023:
	mov	r1, r9
	ldr	r3, .L1189+28
	mov	r2, #4
	sub	r0, fp, #236
	movw	r8, #41528
	bl	qsort
	mov	r7, #0
	add	r3, r5, #256
	str	r7, [r4, #568]
	mov	r2, r9
	ldrb	r0, [r6, #1595]	@ zero_extendqisi2
	sub	r1, fp, #236
	str	r7, [sp, #4]
	movt	r8, 169
	add	r8, r5, r8
	str	r8, [sp]
	str	r3, [fp, #-244]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	ldr	r9, [r3, #2388]
	cmp	r9, r7
	subeq	r10, fp, #108
	beq	.L1033
	movw	r3, #47364
	sub	r10, fp, #108
	movt	r3, 169
	add	r3, r5, r3
	mov	r2, r10
.L1034:
	add	r7, r7, #1
	ldr	r1, [r3, #4]!
	cmp	r7, r9
	str	r1, [r2], #4
	bne	.L1034
.L1033:
	ldr	r3, .L1189+16
	mov	r2, #4
	mov	r1, r9
	mov	r0, r10
	bl	qsort
	ldrb	r0, [r6, #1595]	@ zero_extendqisi2
	mov	r3, #1
	str	r8, [sp]
	str	r3, [sp, #4]
	mov	r2, r9
	mov	r1, r10
	ldr	r3, [fp, #-244]
	bl	MVC_GenPiclistfromFrmlist
.L1030:
	ldrb	r3, [r4, #532]	@ zero_extendqisi2
	mov	r2, #0
	str	r2, [r4, #572]
	cmp	r3, r2
	beq	.L1081
	ldr	r0, [r4, #568]
	cmp	r0, #0
	bne	.L1187
	ldr	r3, [r5, #224]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	bne	.L1041
	ldrb	r3, [r6, #1595]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1042
	ldr	r3, [r6, #2112]
	add	r3, r3, #576
	str	r3, [r5, #256]
.L1043:
	mov	r3, #1
	str	r3, [r4, #568]
.L1167:
	ldrb	r1, [r4, #520]	@ zero_extendqisi2
	b	.L1168
.L1187:
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1039
.L1040:
	cmp	r0, #0
	bne	.L1039
	ldr	r1, [r4, #572]
	cmp	r1, #0
	beq	.L1188
	ldr	r3, [r4, #584]
	mov	r2, r0
	str	r0, [r4, #568]
	add	r3, r3, #1
	cmp	r3, r1
	movcs	r3, r1
	str	r3, [r4, #572]
	b	.L1099
.L1076:
	ldrb	r3, [r4, #532]	@ zero_extendqisi2
	b	.L1098
.L1181:
	movw	ip, #41528
	ldr	r2, [r4, #2168]
	ldr	r3, [fp, #-244]
	mov	r1, r7
	movt	ip, 169
	add	ip, r5, ip
	str	ip, [sp]
	bl	MVC_GenPiclistfromFrmlist_Interview
	b	.L1085
.L1042:
	cmp	r3, #1
	ldr	r3, [r6, #2112]
	addeq	r3, r3, #612
	addne	r3, r3, #648
	str	r3, [r5, #256]
	b	.L1043
.L1077:
	ldr	lr, [r5, #388]
	b	.L1080
.L1182:
	movw	r7, #32736
	movw	r3, #43132
	movt	r7, 169
	add	r7, r5, r7
	mov	r0, r5
	movt	r3, 169
	mov	r2, r7
	add	r3, r5, r3
	bl	mvc_append_interview_list
	ldrb	r0, [r6, #1595]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1087
	ldr	r1, [r4, #2172]
	ldr	ip, [r4, #572]
	cmp	r1, #0
	beq	.L1088
	add	r2, ip, #96
	movw	r3, #33312
	movt	r3, 169
	add	r3, r5, r3
	add	r2, r5, r2, lsl #2
.L1089:
	add	r0, r0, #1
	str	r3, [r2, #4]!
	cmp	r0, r1
	add	r3, r3, #688
	bne	.L1089
	add	ip, ip, r0
.L1088:
	str	ip, [r4, #572]
	ldrb	r1, [r4, #520]	@ zero_extendqisi2
	ldr	r0, [r4, #568]
	b	.L1082
.L1175:
	mov	r3, r8, asl #2
	ldr	r1, [fp, #-248]
	str	r3, [fp, #-244]
	mov	r2, r3
	ldr	r3, .L1189+12
	add	r0, r1, r2
	mov	r2, #4
	mov	r1, r9
	bl	qsort
	subs	r7, r8, #0
	bne	.L1097
.L1170:
	sub	r10, fp, #172
	b	.L1072
.L1174:
	add	r7, r8, #64
	ldr	r3, .L1189+24
	mov	r2, #4
	mov	r1, r9
	add	r7, r5, r7, lsl #2
	mov	r0, r7
	bl	qsort
	subs	r10, r8, #0
	bne	.L1096
	b	.L1059
.L1104:
	mov	r7, ip
	b	.L1024
.L1105:
	mov	r8, r7
	b	.L1027
.L1106:
	mov	r8, r10
	b	.L1061
.L1180:
	sub	r3, fp, #236
	mov	r2, #4
	str	r3, [fp, #-248]
	mov	r1, r10
	mov	r0, r3
	ldr	r3, .L1189+8
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r9, [r3, #2384]
	cmp	r9, #0
	movwne	r7, #47300
	movne	r8, r10
	movtne	r7, 169
	addne	r7, r5, r7
	bne	.L1102
	ldr	r3, .L1189+12
	mov	r2, #4
	mov	r1, r9
	ldr	r0, [fp, #-248]
	mov	r7, r9
	bl	qsort
	b	.L1170
.L1050:
	add	r3, r0, #256
	mov	r2, #4
	str	r3, [fp, #-244]
	mov	r1, r10
	mov	r0, r3
	ldr	r3, .L1189+20
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r9, [r3, #2384]
	cmp	r9, #0
	movwne	r7, #47300
	movne	r8, r10
	movtne	r7, 169
	addne	r7, r5, r7
	bne	.L1100
	ldr	r7, [fp, #-244]
	mov	r2, #4
	ldr	r3, .L1189+24
	mov	r1, r9
	mov	r10, r9
	mov	r0, r7
	bl	qsort
	b	.L1059
.L1087:
	movw	ip, #41532
	ldr	r2, [r4, #2172]
	mov	r1, r7
	movt	ip, 169
	add	r3, r5, #388
	add	ip, r5, ip
	str	ip, [sp]
	bl	MVC_GenPiclistfromFrmlist_Interview
	b	.L1167
.L1183:
	ldr	r3, .L1189+32
	mov	r0, #1
	ldr	r1, .L1189+36
.L1169:
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	b	.L1161
.L1041:
	ldr	r3, .L1189+32
	mov	r0, #1
	ldr	r1, .L1189+40
	b	.L1169
.L1188:
	ldr	r3, .L1189+32
	mov	r0, #1
	ldr	r1, .L1189+44
	b	.L1169
.L1190:
	.align	2
.L1189:
	.word	MVC_compare_pic_by_pic_num_desc
	.word	MVC_compare_pic_by_lt_pic_num_asc
	.word	MVC_compare_fs_by_poc_desc
	.word	MVC_compare_fs_by_poc_asc
	.word	MVC_compare_fs_by_lt_pic_idx_asc
	.word	MVC_compare_pic_by_poc_desc
	.word	MVC_compare_pic_by_poc_asc
	.word	MVC_compare_fs_by_frame_num_desc
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC26
	.word	.LC25
	.word	.LC27
	UNWIND(.fnend)
	.size	MVC_InitListX, .-MVC_InitListX
	.align	2
	.global	MVC_DumpList
	.type	MVC_DumpList, %function
MVC_DumpList:
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
	ldr	r3, .L1204
	ldr	r3, [r3]
	tst	r3, #8192
	beq	.L1191
	movw	r7, #41524
	ldr	r9, .L1204+4
	movt	r7, 169
	add	r10, r0, #252
	add	r7, r0, r7
	mov	r8, #0
.L1193:
	ldr	r3, [r7, #4]!
	cmp	r3, #0
	movne	r5, r10
	movne	r4, #0
	beq	.L1195
.L1194:
	ldr	ip, [r5, #4]!
	mov	r3, r4
	ldr	r6, [r9, #68]
	mov	r2, r8
	ldr	r1, .L1204+8
	mov	r0, #13
	ldr	ip, [ip, #4]
	add	r4, r4, #1
	ldr	lr, [ip, #32]
	str	lr, [sp, #4]
	ldr	ip, [ip, #20]
	str	ip, [sp]
	blx	r6
	ldr	r3, [r7]
	cmp	r3, r4
	bhi	.L1194
.L1195:
	add	r8, r8, #1
	add	r10, r10, #132
	cmp	r8, #2
	bne	.L1193
.L1191:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1205:
	.align	2
.L1204:
	.word	g_PrintEnable
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	UNWIND(.fnend)
	.size	MVC_DumpList, .-MVC_DumpList
	.align	2
	.global	MVC_FindNearestPOCPicId
	.type	MVC_FindNearestPOCPicId, %function
MVC_FindNearestPOCPicId:
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
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	r2, [r3, #2380]
	cmp	r2, #0
	beq	.L1211
	ldr	r4, [r3, #2376]
	add	r3, r0, #11141120
	add	r3, r3, #8192
	cmp	r4, #0
	ldr	r5, [r3, #2132]
	beq	.L1212
	movw	ip, #47236
	mov	r6, #0
	movt	ip, 169
	add	ip, r0, ip
	mov	r1, r6
	mvn	lr, #-2147483648
.L1210:
	ldr	r2, [ip, #4]!
	add	r1, r1, #1
	cmp	r2, #0
	beq	.L1209
	ldr	r3, [r2, #32]
	rsb	r3, r3, r5
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, lr
	ldrlt	r6, [r2, #268]
	movlt	lr, r3
.L1209:
	cmp	r1, r4
	bne	.L1210
.L1208:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1212:
	mov	r6, r4
	b	.L1208
.L1211:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FindNearestPOCPicId, .-MVC_FindNearestPOCPicId
	.align	2
	.global	MVC_FindMinRefIdx
	.type	MVC_FindMinRefIdx, %function
MVC_FindMinRefIdx:
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
	add	r3, r0, #11075584
	add	r3, r3, #40960
	ldrb	r2, [r3, #520]	@ zero_extendqisi2
	cmp	r2, #2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	add	r2, r0, #11141120
	movw	r6, #47668
	add	r2, r2, #8192
	ldrb	lr, [r2, #1595]	@ zero_extendqisi2
	cmp	lr, #0
	bne	.L1247
	ldr	r4, [r3, #568]
	movw	r5, #47672
	movt	r6, 169
	movt	r5, 169
	cmp	r4, #0
	add	r6, r0, r6
	add	r5, r0, r5
	mov	r7, lr
	beq	.L1225
.L1249:
	add	r2, r0, #252
	mov	ip, #32
	mov	r3, #0
	b	.L1223
.L1222:
	add	r3, r3, #1
	cmp	r3, r4
	beq	.L1248
.L1223:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #52]
	cmp	r1, lr
	bne	.L1222
	cmp	ip, r3
	movcs	ip, r3
	add	r3, r3, #1
	cmp	r3, r4
	str	ip, [r5, #-4]
	str	ip, [r6, #4]
	bne	.L1223
.L1248:
	cmp	ip, #31
	bhi	.L1225
.L1224:
	add	lr, lr, #1
	add	r6, r6, #8
	cmp	lr, #16
	add	r5, r5, #8
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	r4, #0
	bne	.L1249
.L1225:
	str	r7, [r5, #-4]
	str	r7, [r6, #4]
	b	.L1224
.L1247:
	ldr	r5, [r3, #568]
	mov	lr, #0
	movt	r6, 169
	mov	r7, lr
	cmp	r5, #0
	add	r6, r0, r6
	beq	.L1229
.L1251:
	add	r1, r0, #252
	mov	r4, #32
	mov	r2, #0
	b	.L1227
.L1226:
	add	r2, r2, #1
	cmp	r2, r5
	beq	.L1250
.L1227:
	ldr	r3, [r1, #4]!
	ldr	r8, [r3, #4]
	ldrb	ip, [r3]	@ zero_extendqisi2
	ldr	r3, [r8, #52]
	mov	r3, r3, asl #1
	cmp	ip, #2
	orreq	r3, r3, #1
	cmp	r3, lr
	bne	.L1226
	cmp	r4, r2
	movcs	r4, r2
	add	r2, r2, #1
	cmp	r2, r5
	str	r4, [r6]
	bne	.L1227
.L1250:
	cmp	r4, #31
	bhi	.L1229
.L1228:
	add	lr, lr, #1
	add	r6, r6, #4
	cmp	lr, #32
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	r5, #0
	bne	.L1251
.L1229:
	str	r7, [r6]
	b	.L1228
	UNWIND(.fnend)
	.size	MVC_FindMinRefIdx, .-MVC_FindMinRefIdx
	.align	2
	.global	MVC_DecList
	.type	MVC_DecList, %function
MVC_DecList:
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
	bl	MVC_FindNearestPOCPicId
	add	r6, r5, #11075584
	mvn	r4, #0
	add	r3, r6, #40960
	ldrb	r2, [r3, #520]	@ zero_extendqisi2
	str	r4, [r3, #2152]
	cmp	r2, #2
	str	r0, [r3, #2156]
	beq	.L1259
	mov	r0, r5
	bl	MVC_InitListX
	cmp	r0, #0
	bne	.L1260
	mov	r0, r5
	bl	MVC_ReorderListX
	mov	r0, r5
	bl	MVC_RepairList
	cmp	r0, #0
	bne	.L1257
	mov	r0, r5
	add	r6, r6, #40960
	bl	MVC_FindMinRefIdx
	ldr	r3, [r5, #256]
	mov	r0, #0
	cmp	r3, #0
	ldrne	r3, [r3, #4]
	ldrne	r4, [r3, #268]
	str	r4, [r6, #2152]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1259:
	mov	r4, #0
	str	r4, [r3, #568]
	str	r4, [r3, #572]
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1257:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1260:
	ldr	r3, .L1261
	mov	r0, #13
	ldr	r1, .L1261+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1262:
	.align	2
.L1261:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC29
	UNWIND(.fnend)
	.size	MVC_DecList, .-MVC_DecList
	.align	2
	.global	MVC_NoPicOut
	.type	MVC_NoPicOut, %function
MVC_NoPicOut:
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
	ldr	ip, [r0, #48]
	cmp	ip, #0
	beq	.L1270
	movw	r3, #47807
	mov	r2, #0
	movt	r3, 169
	mov	lr, r2
	add	r3, r0, r3
	b	.L1269
.L1278:
	ldrb	r1, [r3, #-2]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1267
	cmp	r2, ip
	add	r3, r3, #688
	beq	.L1270
.L1269:
	ldrb	r1, [r3]	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r1, #1
	bne	.L1278
.L1267:
	cmp	r2, ip
	strb	lr, [r3, #-5]
	strb	lr, [r3, #-4]
	add	r3, r3, #688
	bne	.L1269
.L1270:
	ldr	r2, [r0, #52]
	cmp	r2, #0
	beq	.L1279
	mov	r3, #0
	add	r0, r0, #144
	mov	r1, r3
.L1271:
	add	r3, r3, #1
	str	r1, [r0, #4]!
	cmp	r3, r2
	bne	.L1271
	ldmfd	sp, {fp, sp, pc}
.L1279:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_NoPicOut, .-MVC_NoPicOut
	.align	2
	.global	MVC_GetBackPicFromVOQueue
	.type	MVC_GetBackPicFromVOQueue, %function
MVC_GetBackPicFromVOQueue:
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
	mov	r6, r0
	ldr	r0, [r0, #120]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L1297
.L1281:
	ldr	r3, [r6, #48]
	cmp	r3, #0
	beq	.L1288
	movw	r5, #48096
	mov	r8, #0
	movt	r5, 169
	add	r5, r6, r5
	mov	r7, r8
.L1287:
	sub	r4, r5, #16
	strb	r7, [r5, #-294]
	strb	r7, [r5, #-293]
.L1286:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L1285
	ldr	r0, [r6, #120]
	bl	FreeUsdByDec
	str	r7, [r4]
.L1285:
	cmp	r4, r5
	bne	.L1286
	ldr	r3, [r6, #48]
	add	r8, r8, #1
	add	r5, r5, #688
	cmp	r3, r8
	bhi	.L1287
.L1288:
	ldr	r2, [r6, #52]
	cmp	r2, #0
	beq	.L1298
	mov	r3, #0
	add	r6, r6, #144
	mov	r1, r3
.L1289:
	add	r3, r3, #1
	str	r1, [r6, #4]!
	cmp	r3, r2
	bne	.L1289
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1297:
	add	r0, r6, #584
	bl	ResetVoQueue
	b	.L1281
.L1298:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetBackPicFromVOQueue, .-MVC_GetBackPicFromVOQueue
	.align	2
	.global	mvc_wait_vo
	.type	mvc_wait_vo, %function
mvc_wait_vo:
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
	.size	mvc_wait_vo, .-mvc_wait_vo
	.align	2
	.global	MVC_RoundLog2
	.type	MVC_RoundLog2, %function
MVC_RoundLog2:
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
	mul	r0, r0, r0
	mov	r3, #0
	mov	r2, #1
.L1301:
	add	r3, r3, #1
	cmp	r0, r2, asl r3
	bge	.L1301
	mov	r0, r3, asr #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_RoundLog2, .-MVC_RoundLog2
	.align	2
	.global	MVC_GetReRangeFlag
	.type	MVC_GetReRangeFlag, %function
MVC_GetReRangeFlag:
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
	add	ip, r0, #11075584
	add	r7, ip, #40960
	mov	r5, r1
	mov	r4, r0
	ldr	r0, [r0, #252]
	ldrb	r1, [r7, #532]	@ zero_extendqisi2
	mov	lr, #2240
	ldr	r3, [r7, #536]
	sxtb	r2, r1
	cmn	r2, #1
	mla	r3, lr, r3, r0
	beq	.L1321
	cmp	r1, #0
	bne	.L1306
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r3, [r3, #28]
	cmp	r2, #1
	beq	.L1322
	ldr	r2, [r4, #28]
	cmp	r2, r3
	movweq	r6, #35364
	movteq	r6, 168
	addeq	r6, r4, r6
	bne	.L1323
.L1305:
	ldrb	r3, [r6, #20]	@ zero_extendqisi2
	ldr	r1, [r6, #3952]
	rsb	r3, r3, #2
	ldr	r2, [r6, #3948]
	ldr	r0, [r4, #12]
	mla	r3, r1, r3, r3
	ldr	r1, [r4, #16]
	add	r2, r2, #1
	cmp	r2, r0
	cmpeq	r3, r1
	movne	lr, #1
	moveq	lr, #0
	beq	.L1324
.L1310:
	ldr	ip, .L1326
	ldr	r8, [ip]
	cmp	r8, #0
	beq	.L1317
	mov	r0, r0, asl #4
	mov	r1, r1, asl #4
	strh	r0, [fp, #-44]	@ movhi
	mov	r2, r2, asl #4
	strh	r1, [fp, #-42]	@ movhi
	mov	r1, r3, asl #4
	strh	r2, [fp, #-40]	@ movhi
	mov	r3, #8
	strh	r1, [fp, #-38]	@ movhi
	sub	r2, fp, #44
	mov	r1, #2
	ldr	r0, [r4, #120]
	blx	r8
	mov	lr, #1
	mov	r0, lr
.L1311:
	ldrb	r3, [r7, #531]	@ zero_extendqisi2
	cmp	r3, #1
	ldrne	r1, [r6, #3972]
	subne	r1, r1, #1
	beq	.L1325
.L1314:
	ldr	r3, [r4, #44]
	cmp	r3, r1
	orrne	lr, lr, #1
	str	lr, [r5]
	str	r1, [r4, #44]
.L1319:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1324:
	add	ip, ip, #45056
	ldr	r8, [r6, #3972]
	ldr	ip, [ip, #2376]
	add	ip, ip, #1
	cmp	r8, ip
	bhi	.L1310
.L1320:
	mov	r0, lr
	b	.L1311
.L1321:
	ldr	r2, [r3, #28]
	movw	r6, #3992
	ldr	r3, [r4, #248]
	mla	r6, r6, r2, r3
	b	.L1305
.L1325:
	movw	ip, #39336
	add	r3, r4, #290816
	movt	ip, 168
	add	r3, r3, #808
	add	ip, r4, ip
	mov	r1, #0
.L1313:
	ldr	r2, [r3]
	add	r3, r3, #335872
	add	r3, r3, #308
	cmp	r2, r1
	subhi	r1, r2, #1
	cmp	r3, ip
	bne	.L1313
	add	r1, r1, #1
	mov	r1, r1, asl #1
	cmp	r1, #16
	movcs	r1, #16
	b	.L1314
.L1317:
	mov	lr, #1
	b	.L1320
.L1322:
	movw	r6, #8500
	movt	r6, 5
	mla	r6, r6, r3, r4
	add	r6, r6, #286720
	add	r6, r6, #932
	b	.L1305
.L1323:
	ldr	r3, .L1326+4
	mov	r0, #1
	ldr	r1, .L1326+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1319
.L1306:
	ldr	r3, .L1326+4
	mov	r0, #1
	ldr	r1, .L1326+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1319
.L1327:
	.align	2
.L1326:
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC30
	.word	.LC31
	UNWIND(.fnend)
	.size	MVC_GetReRangeFlag, .-MVC_GetReRangeFlag
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	MVC_DecPOC
	.type	MVC_DecPOC, %function
MVC_DecPOC:
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
	add	r6, r0, #11075584
	ldr	r5, [r0, #236]
	add	r7, r6, #40960
	mov	r2, #1
	ldrb	r1, [r7, #523]	@ zero_extendqisi2
	ldr	ip, [r5, #2900]
	ldr	r3, [r5, #2896]
	sub	r1, r1, #5
	clz	r1, r1
	cmp	ip, r2
	add	r3, r3, #4
	ldr	lr, [r5, #2904]
	mov	r1, r1, lsr #5
	mov	r3, r2, asl r3
	beq	.L1330
	bcc	.L1331
	cmp	ip, #2
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	cmp	r1, #0
	bne	.L1386
	add	r4, r6, #36864
	ldrb	r2, [r4, #3480]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1364
	ldr	r1, [r4, #3536]
	ldr	r0, [r4, #3532]
	ldr	r2, [r4, #3544]
	cmp	r1, r0
	addcc	r2, r2, r3
	strcc	r2, [r4, #3540]
	bcs	.L1366
.L1367:
	add	r3, r2, r1
	str	r3, [r4, #3528]
	ldrb	r0, [r7, #528]	@ zero_extendqisi2
	mov	r3, r3, asl #1
	cmp	r0, #0
	subeq	r3, r3, #1
	str	r3, [r4, #3516]
	ldrb	r0, [r7, #521]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1370
	str	r3, [r4, #3512]
	str	r3, [r4, #3508]
	str	r3, [r4, #3504]
.L1363:
	add	r6, r6, #36864
	str	r1, [r6, #3532]
	str	r2, [r6, #3544]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1331:
	cmp	r1, #0
	add	lr, lr, #4
	mov	r2, r2, asl lr
	bne	.L1387
	add	r4, r6, #36864
	ldrb	r3, [r4, #3480]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1335
	ldr	lr, [r4, #3492]
	ldr	ip, [r4, #3496]
	mov	r1, lr
.L1336:
	ldr	r0, [r4, #3484]
	cmp	r0, ip
	bcs	.L1334
	rsb	r3, r0, ip
	cmp	r3, r2, lsr #1
	addcs	r1, r1, r2
	strcs	r1, [r4, #3500]
	bcs	.L1338
.L1334:
	cmp	r0, ip
	bls	.L1339
	rsb	r3, ip, r0
	cmp	r3, r2, lsr #1
	rsbhi	r1, r2, r1
	strhi	r1, [r4, #3500]
	bls	.L1339
.L1338:
	ldrb	r3, [r7, #521]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1340
.L1389:
	ldr	r3, [r4, #3488]
	add	r1, r1, r0
	str	r1, [r4, #3504]
	add	r3, r1, r3
	str	r3, [r4, #3508]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r4, #3516]
.L1341:
	ldr	r2, [r4, #3536]
	str	r3, [r4, #3512]
	add	r3, r6, #40960
	ldr	r1, [r4, #3532]
	cmp	r2, r1
	strne	r2, [r4, #3532]
	ldrb	r3, [r3, #528]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r6, r6, #36864
	ldrne	r2, [r6, #3484]
	ldrne	r3, [r6, #3500]
	strne	r2, [r6, #3496]
	strne	r3, [r6, #3492]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1330:
	cmp	r1, #0
	add	r4, r6, #36864
	movne	r3, #0
	strne	r3, [r4, #3540]
	bne	.L1345
	ldrb	r2, [r4, #3480]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1346
	mov	r3, r1
	str	r1, [r4, #3544]
	str	r1, [r4, #3532]
.L1347:
	str	r3, [r4, #3540]
.L1345:
	ldr	r3, [r5, #2916]
	cmp	r3, #0
	beq	.L1349
	ldr	r3, [r4, #3536]
	ldr	r0, [r4, #3540]
	add	r0, r3, r0
	str	r0, [r4, #3528]
	ldrb	r8, [r7, #528]	@ zero_extendqisi2
	cmp	r8, #0
	bne	.L1351
	cmp	r0, #0
	beq	.L1352
	sub	r0, r0, #1
	str	r0, [r4, #3528]
.L1351:
	mov	r3, #0
	str	r3, [r4, #3560]
	ldr	r1, [r5, #2916]
	cmp	r1, r3
	bgt	.L1372
	cmp	r0, #0
	beq	.L1355
.L1388:
	sub	r9, r0, #1
	mov	r0, r9
	bl	__aeabi_uidiv
	mov	r10, r0
	mov	r0, r9
	str	r10, [r4, #3552]
	ldr	r1, [r5, #2916]
	bl	__aeabi_uidivmod
	ldr	r0, [r4, #3560]
	mul	r0, r0, r10
	str	r0, [r4, #3556]
	cmp	r1, #0
	str	r1, [r4, #3548]
	blt	.L1356
	add	r2, r5, #2912
	add	r1, r1, #1
	add	r2, r2, #4
	mov	r3, #0
.L1357:
	add	r3, r3, #1
	ldr	ip, [r2, #4]!
	cmp	r3, r1
	add	r0, r0, ip
	str	r0, [r4, #3556]
	bne	.L1357
.L1356:
	cmp	r8, #0
	ldreq	r3, [r5, #2908]
	addeq	r0, r0, r3
	streq	r0, [r4, #3556]
	ldrb	r3, [r7, #521]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1359
	ldr	r2, [r4, #3520]
	ldr	r1, [r4, #3524]
	add	r2, r0, r2
	str	r2, [r4, #3504]
	ldr	r3, [r5, #2912]
	add	r3, r2, r3
	add	r0, r3, r1
	str	r0, [r4, #3508]
	cmp	r0, r2
	movge	r0, r2
	str	r0, [r4, #3516]
.L1360:
	add	r6, r6, #36864
	ldr	r2, [r6, #3536]
	ldr	r3, [r6, #3540]
	str	r0, [r6, #3512]
	str	r2, [r6, #3532]
	str	r3, [r6, #3544]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1349:
	str	r3, [r4, #3528]
	ldrb	r8, [r7, #528]	@ zero_extendqisi2
.L1352:
	mov	r0, #0
	str	r0, [r4, #3560]
	ldr	r3, [r5, #2916]
	cmp	r3, r0
	ble	.L1355
.L1372:
	add	ip, r5, #2912
	mov	r3, #0
	add	ip, ip, #4
	mov	r2, r3
.L1354:
	ldr	r1, [ip, #4]!
	add	r2, r2, #1
	add	r3, r3, r1
	str	r3, [r4, #3560]
	ldr	r1, [r5, #2916]
	cmp	r1, r2
	bgt	.L1354
	cmp	r0, #0
	bne	.L1388
.L1355:
	mov	r0, #0
	str	r0, [r4, #3556]
	b	.L1356
.L1387:
	add	r4, r0, #11075584
	add	r4, r4, #36864
.L1337:
	mov	r3, #0
	ldr	r0, [r4, #3484]
	str	r3, [r4, #3492]
	mov	lr, r3
	str	r3, [r4, #3496]
	mov	r1, ip
	b	.L1334
.L1386:
	add	r3, r6, #36864
	mov	r1, #0
	mov	r2, r1
	str	r1, [r3, #3540]
	str	r1, [r3, #3508]
	str	r1, [r3, #3504]
	str	r1, [r3, #3512]
	str	r1, [r3, #3516]
	ldr	r1, [r3, #3536]
	b	.L1363
.L1339:
	str	lr, [r4, #3500]
	ldrb	r3, [r7, #521]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1389
.L1340:
	ldrb	r3, [r7, #522]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r1, r0
	streq	r3, [r4, #3504]
	strne	r3, [r4, #3508]
	str	r3, [r4, #3516]
	b	.L1341
.L1359:
	ldrb	r3, [r7, #522]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r2, [r5, #2912]
	ldreq	r3, [r4, #3520]
	ldrne	r3, [r4, #3520]
	addne	r0, r0, r2
	addeq	r0, r0, r3
	streq	r0, [r4, #3504]
	addne	r0, r0, r3
	strne	r0, [r4, #3508]
	str	r0, [r4, #3516]
	b	.L1360
.L1335:
	movw	r3, #3481
	ldrsb	r3, [r4, r3]
	cmp	r3, #0
	bne	.L1337
	ldr	r0, [r4, #3504]
	mov	r1, ip
	mov	lr, r3
	str	r3, [r4, #3492]
	mov	ip, r0
	str	r0, [r4, #3496]
	b	.L1336
.L1346:
	ldr	r1, [r4, #3536]
	ldr	r2, [r4, #3532]
	cmp	r1, r2
	bcs	.L1348
	ldr	r2, [r4, #3544]
	add	r3, r3, r2
	str	r3, [r4, #3540]
	b	.L1345
.L1370:
	ldrb	r0, [r7, #522]	@ zero_extendqisi2
	str	r3, [r4, #3512]
	cmp	r0, #0
	streq	r3, [r4, #3504]
	strne	r3, [r4, #3508]
	b	.L1363
.L1364:
	str	r1, [r4, #3532]
	mov	r2, r1
	str	r1, [r4, #3544]
	ldr	r1, [r4, #3536]
.L1366:
	str	r2, [r4, #3540]
	b	.L1367
.L1348:
	ldr	r3, [r4, #3544]
	b	.L1347
	UNWIND(.fnend)
	.size	MVC_DecPOC, .-MVC_DecPOC
	.align	2
	.global	MVC_CalcPicNum
	.type	MVC_CalcPicNum, %function
MVC_CalcPicNum:
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
	add	r5, r0, #11141120
	ldr	r3, [r0, #236]
	add	r5, r5, #8192
	mov	r6, #1
	ldrb	r2, [r5, #1595]	@ zero_extendqisi2
	ldr	r3, [r3, #2896]
	cmp	r2, #0
	add	r3, r3, #4
	mov	r6, r6, asl r3
	add	r3, r0, #11075584
	beq	.L1391
	add	r3, r3, #45056
	sub	r7, r2, #1
	sub	r2, r2, #2
	clz	r7, r7
	ldr	r1, [r3, #2384]
	clz	r2, r2
	mov	r7, r7, lsr #5
	cmp	r1, #0
	mov	r2, r2, lsr #5
	movwne	lr, #47300
	movne	r1, #0
	movtne	lr, 169
	addne	lr, r0, lr
	beq	.L1411
.L1410:
	ldr	ip, [lr, #4]!
	ldrb	r4, [ip, #3]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L1405
	ldr	r4, [ip, #20]
	ldr	r8, [r5, #2120]
	cmp	r4, r8
	rsbhi	r4, r6, r4
	str	r4, [ip, #24]
	ldr	ip, [lr]
	ldrb	r4, [ip, #3]	@ zero_extendqisi2
	tst	r4, #1
	beq	.L1408
	ldr	r8, [ip, #612]
	bic	r8, r8, #-16777216
	bic	r8, r8, #255
	cmp	r8, #65536
	ldreq	r4, [ip, #24]
	addeq	r4, r7, r4, lsl #1
	streq	r4, [ip, #624]
	ldreq	ip, [lr]
	ldreqb	r4, [ip, #3]	@ zero_extendqisi2
.L1408:
	tst	r4, #2
	beq	.L1405
	ldr	r4, [ip, #648]
	bic	r4, r4, #-16777216
	bic	r4, r4, #255
	cmp	r4, #65536
	ldreq	r4, [ip, #24]
	addeq	r4, r2, r4, lsl #1
	streq	r4, [ip, #660]
.L1405:
	ldr	ip, [r3, #2384]
	add	r1, r1, #1
	cmp	ip, r1
	bhi	.L1410
.L1411:
	ldr	r1, [r3, #2388]
	cmp	r1, #0
	beq	.L1435
	movw	r4, #47364
	mov	ip, #0
	movt	r4, 169
	add	r4, r0, r4
.L1416:
	ldr	lr, [r4, #4]!
	add	ip, ip, #1
	ldrb	r1, [lr, #3]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1413
	tst	r1, #1
	beq	.L1414
	ldr	r0, [lr, #612]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #256
	ldreq	r1, [lr, #28]
	addeq	r1, r7, r1, lsl #1
	streq	r1, [lr, #620]
	ldreq	lr, [r4]
	ldreqb	r1, [lr, #3]	@ zero_extendqisi2
.L1414:
	tst	r1, #2
	beq	.L1413
	ldr	r1, [lr, #648]
	bic	r1, r1, #-16777216
	bic	r1, r1, #255
	cmp	r1, #256
	ldreq	r1, [lr, #28]
	addeq	r1, r2, r1, lsl #1
	streq	r1, [lr, #656]
.L1413:
	ldr	r1, [r3, #2388]
	cmp	r1, ip
	bhi	.L1416
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1391:
	add	r3, r3, #45056
	ldr	r1, [r3, #2384]
	cmp	r1, #0
	movwne	lr, #47300
	movtne	lr, 169
	addne	lr, r0, lr
	bne	.L1400
.L1401:
	ldr	r2, [r3, #2388]
	cmp	r2, #0
	beq	.L1436
	movw	ip, #47364
	mov	r2, #0
	movt	ip, 169
	add	ip, r0, ip
	b	.L1403
.L1402:
	ldr	r1, [r3, #2388]
	cmp	r1, r2
	bls	.L1437
.L1403:
	ldr	r1, [ip, #4]!
	add	r2, r2, #1
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1402
	ldr	r0, [r1, #576]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #256
	ldreq	r0, [r1, #28]
	streq	r0, [r1, #584]
	ldr	r1, [r3, #2388]
	cmp	r1, r2
	bhi	.L1403
.L1437:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1438:
	ldr	ip, [r1, #576]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L1397
	ldr	ip, [r1, #20]
	ldr	r4, [r5, #2120]
	rsb	r7, r6, ip
	cmp	ip, r4
	strhi	r7, [r1, #24]
	strls	ip, [r1, #24]
	ldr	r1, [lr]
	ldr	ip, [r1, #24]
	str	ip, [r1, #588]
.L1397:
	ldr	r1, [r3, #2384]
	add	r2, r2, #1
	cmp	r1, r2
	bls	.L1401
.L1400:
	ldr	r1, [lr, #4]!
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1397
	b	.L1438
.L1436:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1435:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_CalcPicNum, .-MVC_CalcPicNum
	.align	2
	.global	MVC_IsOutDPB
	.type	MVC_IsOutDPB, %function
MVC_IsOutDPB:
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
	beq	.L1444
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	lr, [r3, #2376]
	cmp	lr, #0
	beq	.L1444
	ldr	r2, [r3, #2184]
	rsb	r3, r2, r1
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L1446
	movw	ip, #47240
	movt	ip, 169
	add	ip, r0, ip
	b	.L1441
.L1442:
	ldr	r2, [ip, #4]!
	rsb	r0, r2, r1
	cmp	r2, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L1446
.L1441:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L1442
.L1444:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1446:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_IsOutDPB, .-MVC_IsOutDPB
	.align	2
	.global	mvc_combine_scalinglist
	.type	mvc_combine_scalinglist, %function
mvc_combine_scalinglist:
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
	cmp	r2, #0
	ldmlefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r6, .L1454
	mov	lr, #0
	mov	r5, #255
	sub	r7, r6, #16
.L1451:
	cmp	r2, #16
	ldreqb	ip, [lr, r7]	@ zero_extendqisi2
	ldrneb	ip, [lr, r6]	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	lr, r2
	and	r3, ip, #3
	mov	r4, ip, lsr #2
	ldrb	r8, [r0, ip, asl #2]	@ zero_extendqisi2
	mov	r3, r3, asl #3
	ldr	ip, [r1, r4, asl #2]
	bic	ip, ip, r5, asl r3
	orr	r3, ip, r8, asl r3
	str	r3, [r1, r4, asl #2]
	bne	.L1451
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1455:
	.align	2
.L1454:
	.word	.LANCHOR0+16
	UNWIND(.fnend)
	.size	mvc_combine_scalinglist, .-mvc_combine_scalinglist
	.align	2
	.global	mvc_assign_quant_params
	.type	mvc_assign_quant_params, %function
mvc_assign_quant_params:
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
	subs	r3, r0, #0
	str	r1, [fp, #-48]
	str	r3, [fp, #-52]
	movweq	r3, #6999
	ldreq	ip, .L1493
	beq	.L1487
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1488
	ldr	r3, [fp, #-48]
	ldrb	r3, [r3, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1476
	ldr	r3, [fp, #-48]
	mov	r4, #0
	ldr	r1, [fp, #-52]
	add	r2, r3, #2016
	add	r8, r3, #1728
	str	r2, [fp, #-56]
	add	r9, r1, #2384
	mov	r6, r2
	add	r7, r3, #1984
	add	r5, r3, #5
	ldr	r10, .L1493
	b	.L1461
.L1491:
	cmp	r4, #0
	beq	.L1489
	cmp	r4, #3
	beq	.L1490
	ldr	r3, [r10, #52]
	mov	r2, #16
	sub	r1, r6, #16
	mov	r0, r6
	blx	r3
.L1469:
	add	r4, r4, #1
	cmp	r4, #7
	bhi	.L1476
.L1475:
	add	r8, r8, #64
	add	r9, r9, #64
	add	r6, r6, #16
	add	r7, r7, #4
	add	r5, r5, #1
.L1461:
	cmp	r4, #5
	ldrsb	r3, [r5]
	bhi	.L1462
	cmp	r3, #0
	beq	.L1491
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L1469
	ldr	r1, .L1493+4
	cmp	r4, #2
	mov	r2, #16
	ldr	r3, [r10, #52]
	add	r0, r1, r2
	add	r4, r4, #1
	movhi	r1, r0
	mov	r0, r6
	blx	r3
	cmp	r4, #7
	bls	.L1475
.L1476:
	mov	r0, #0
.L1458:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1462:
	cmp	r3, #0
	bne	.L1471
	ldr	r3, [fp, #-52]
	mov	r2, #64
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r10, #52]
	bne	.L1492
.L1486:
	ldr	r1, .L1493+8
	cmp	r4, #6
	add	r0, r1, r2
	movne	r1, r0
	mov	r0, r8
	blx	r3
	b	.L1469
.L1471:
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L1469
	ldr	r3, [r10, #52]
	mov	r2, #64
	b	.L1486
.L1492:
	mov	r1, r9
	mov	r0, r8
	blx	r3
	b	.L1469
.L1488:
	ldr	ip, .L1493
	mov	r0, r3
	movw	r3, #7000
.L1487:
	ldr	r2, .L1493+12
	ldr	r1, .L1493+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1458
.L1490:
	ldr	r3, [fp, #-52]
	mov	r2, #16
	ldr	r0, [fp, #-48]
	mov	r4, #4
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	add	r0, r0, #2064
	cmp	r3, #0
	ldr	r3, [r10, #52]
	ldrne	r1, [fp, #-52]
	ldreq	r1, .L1493+20
	addne	r1, r1, #2720
	blx	r3
	b	.L1475
.L1489:
	ldr	r3, [fp, #-52]
	mov	r2, #16
	ldr	r0, [fp, #-56]
	mov	r4, #1
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r10, #52]
	ldrne	r1, [fp, #-52]
	ldreq	r1, .L1493+4
	addne	r1, r1, #2672
	blx	r3
	b	.L1475
.L1494:
	.align	2
.L1493:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LANCHOR1+32
	.word	.LC13
	.word	.LC14
	.word	.LANCHOR1+16
	UNWIND(.fnend)
	.size	mvc_assign_quant_params, .-mvc_assign_quant_params
	.align	2
	.global	MVC_WriteCurrPicYUV
	.type	MVC_WriteCurrPicYUV, %function
MVC_WriteCurrPicYUV:
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
	add	r5, r0, #11141120
	add	r3, r5, #8192
	ldr	r6, .L1498
	add	r5, r5, #8192
	ldr	r1, .L1498+4
	ldrb	r4, [r3, #1595]	@ zero_extendqisi2
	mov	r0, #2
	ldr	r3, [r3, #2112]
	ldr	r7, [r6, #68]
	mov	r2, r4
	ldr	r3, [r3, #268]
	blx	r7
	ldr	ip, [r5, #2172]
	cmp	r4, #3
	cmpne	r4, #0
	ldr	r3, [r5, #2168]
	addne	r2, r4, #1
	ldr	r1, .L1498+8
	moveq	r2, #1
	ldr	r4, [r6, #68]
	str	ip, [sp]
	mov	r0, #22
	blx	r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1499:
	.align	2
.L1498:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC32
	.word	.LC33
	UNWIND(.fnend)
	.size	MVC_WriteCurrPicYUV, .-MVC_WriteCurrPicYUV
	.align	2
	.global	MVC_WritePicMsg
	.type	MVC_WritePicMsg, %function
MVC_WritePicMsg:
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
	add	r5, r0, #11141120
	add	r6, r5, #8192
	add	ip, r5, #12288
	ldr	r10, .L1536
	mov	r4, r0
	mov	r8, ip
	ldr	lr, [r6, #2188]
	str	ip, [fp, #-52]
	mov	r0, #2
	ldr	ip, [r6, #1804]
	add	r9, r4, #11075584
	ldrb	r3, [r6, #1595]	@ zero_extendqisi2
	ldr	r2, [r6, #2128]
	ldr	r1, .L1536+4
	stmia	sp, {ip, lr}
	ldr	r7, [r10, #68]
	blx	r7
	movw	r3, #9808
	movt	r3, 170
	mov	r2, #0
	str	r2, [r4, #64]
	add	r2, r9, #32768
	ldrd	r0, [r4, r3]
	add	r3, r5, #11584
	mov	lr, r2
	str	r2, [fp, #-56]
	add	r7, r9, #36864
	strd	r0, [r3]
	ldr	r3, [r4, #544]
	str	r3, [r8, #156]
	ldr	r1, [r6, #1800]
	ldr	r2, [r6, #2128]
	ldrb	r3, [r6, #1595]	@ zero_extendqisi2
	str	r1, [r6, #4040]
	str	r2, [r6, #3400]
	strb	r3, [r6, #3384]
	ldr	r3, [r4, #236]
	ldr	r0, [r6, #2172]
	ldr	r1, [r6, #2176]
	ldrb	r2, [r3, #21]	@ zero_extendqisi2
	str	r0, [r6, #3404]
	str	r1, [r6, #3408]
	str	r2, [r6, #3416]
	ldr	r2, [r3, #3948]
	add	r2, r2, #1
	str	r2, [r6, #3412]
	ldrb	r2, [lr, #1364]	@ zero_extendqisi2
	strb	r2, [r6, #3387]
	ldr	r2, [r7, #1300]
	str	r2, [r6, #3420]
	ldrb	r2, [r7, #1240]	@ zero_extendqisi2
	str	r2, [r6, #3424]
	ldr	r3, [r3, #748]
	strb	r3, [r6, #3385]
	ldrb	r3, [r7, #1244]	@ zero_extendqisi2
	str	r3, [r6, #3428]
	ldr	r3, [r7, #3516]
	str	r3, [r6, #3432]
	ldr	r2, [r7, #3504]
	ldr	r3, [r6, #2112]
	str	r2, [r6, #3436]
	ldr	r2, [r7, #3508]
	str	r2, [r6, #3440]
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetLogicFs
	subs	r8, r0, #0
	beq	.L1534
	ldr	r2, [r8, #520]
	ldr	r3, [r8, #524]
	cmp	r2, #0
	beq	.L1504
	cmp	r3, #0
	beq	.L1504
	movw	r3, #12012
	movw	r2, #11884
	movw	r1, #12140
	ldr	r0, [r4, #120]
	movt	r3, 170
	movt	r2, 170
	add	r3, r4, r3
	add	r2, r4, r2
	movt	r1, 170
	add	r1, r4, r1
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r8, #520]
	movw	r2, #12144
	add	r1, r5, #12224
	movt	r2, 170
	add	r2, r4, r2
	ldr	r3, [r3, #4]
	add	r5, r9, #45056
	str	r3, [r6, #3676]
	ldr	r0, [r4, #120]
	bl	FSP_GetPmvAddrTab
	ldr	r3, [r6, #2188]
	ldr	r2, [fp, #-52]
	str	r3, [r6, #3684]
	ldr	r3, [r8, #536]
	str	r3, [r6, #4036]
	ldr	r3, [r8, #524]
	ldr	r3, [r3, #12]
	str	r3, [r6, #3680]
	ldr	r3, [r5, #2604]
	cmp	r3, #0
	str	r3, [fp, #-48]
	str	r3, [r2, #148]
	beq	.L1510
	movw	r6, #47464
	movw	lr, #12240
	movw	ip, #47528
	movw	r0, #12304
	movw	r1, #47592
	movw	r2, #12368
	ldr	r9, [fp, #-48]
	movt	r6, 169
	movt	lr, 170
	movt	ip, 169
	movt	r0, 170
	movt	r1, 169
	movt	r2, 170
	add	r6, r4, r6
	add	lr, r4, lr
	add	ip, r4, ip
	add	r0, r4, r0
	add	r1, r4, r1
	add	r2, r4, r2
	mov	r3, #0
.L1509:
	ldr	r8, [r6, #4]!
	add	r3, r3, #1
	cmp	r3, r9
	str	r8, [lr, #4]!
	ldr	r8, [ip, #4]!
	str	r8, [r0, #4]!
	ldr	r8, [r1, #4]!
	str	r8, [r2, #4]!
	bne	.L1509
.L1510:
	ldr	r3, [fp, #-56]
	ldrb	r3, [r3, #1371]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1535
	ldrb	ip, [r7, #1258]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1511
	movw	lr, #11632
	ldr	r0, .L1536+8
	movt	lr, 170
	add	lr, r4, lr
.L1512:
	and	r3, ip, #3
	add	ip, ip, #1
	cmp	ip, #24
	add	r3, r0, r3, lsl #2
	ldr	r3, [r3, #352]
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [lr, #4]!
	bne	.L1512
	movw	r6, #11732
	mov	lr, #0
	movt	r6, 170
	add	r6, r4, r6
.L1513:
	add	r3, lr, #1
	and	r2, lr, #14
	and	r3, r3, #15
	add	lr, lr, #2
	add	r2, r0, r2, lsl #2
	cmp	lr, #32
	add	r3, r0, r3, lsl #2
	ldr	r1, [r2, #368]
	ldr	ip, [r3, #368]
	ubfx	r3, r1, #8, #8
	mov	r2, r1, lsr #24
	uxtb	r9, r1
	uxtb	r8, ip
	mov	r7, ip, lsr #16
	orr	r3, r3, r2, asl #8
	mov	r1, r1, lsr #8
	mov	r8, r8, asl #16
	and	r2, ip, #-16777216
	orr	r7, r8, r7, asl #24
	ubfx	ip, ip, #8, #8
	orr	r3, r3, r2
	orr	r7, r7, r9
	and	r1, r1, #65280
	orr	r3, r3, ip, asl #16
	orr	r2, r7, r1
	stmia	r6, {r2, r3}
	add	r6, r6, #8
	bne	.L1513
.L1518:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1515
	movw	r6, #47468
	movw	r9, #12572
	movw	r8, #12636
	movt	r6, 169
	movt	r9, 170
	movt	r8, 170
	add	r6, r4, r6
	add	r9, r4, r9
	add	r8, r4, r8
	mov	r7, #0
.L1521:
	ldr	r2, [r6]
	mov	r1, #0
	ldr	r0, [r4, #120]
	add	r7, r7, #1
	bl	FSP_GetStoreType
	adds	r0, r0, #0
	movne	r0, #1
	str	r0, [r9, #4]!
	ldr	r3, [r6], #4
	str	r3, [r8, #4]!
	ldr	r3, [r5, #2604]
	cmp	r3, r7
	bhi	.L1521
.L1515:
	mov	r0, #0
.L1531:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1535:
	ldrb	ip, [r7, #1258]	@ zero_extendqisi2
.L1511:
	cmp	ip, #1
	movw	ip, #11632
	movt	ip, 170
	mov	r0, #0
	add	ip, r4, ip
	beq	.L1516
.L1519:
	movw	r3, #25580
	movt	r3, 42
	add	r3, r0, r3
	add	r0, r0, #1
	ldr	r3, [r4, r3, asl #2]
	cmp	r0, #24
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1519
	movw	r9, #11732
	mov	r10, #1
	movt	r9, 170
	add	r9, r4, r9
	mov	r8, #0
.L1520:
	mov	r3, r8, lsr #3
	and	r2, r10, #15
	mov	r0, r8, asl #1
	movw	r1, #25604
	mov	r3, r3, asl #4
	and	r0, r0, #14
	add	r2, r3, r2
	movt	r1, 42
	add	r3, r3, r0
	add	r1, r2, r1
	movw	r2, #25604
	add	r8, r8, #1
	movt	r2, 42
	add	r2, r3, r2
	ldr	r1, [r4, r1, asl #2]
	cmp	r8, #16
	ldr	r3, [r4, r2, asl #2]
	add	r10, r10, #2
	and	ip, r1, #-16777216
	ubfx	r0, r1, #8, #8
	uxtb	r7, r1
	mov	r1, r1, lsr #16
	mov	r6, r3, lsr #24
	ubfx	r2, r3, #8, #8
	mov	r7, r7, asl #16
	uxtb	lr, r3
	orr	r1, r7, r1, asl #24
	mov	r3, r3, lsr #8
	orr	r2, r2, r6, asl #8
	orr	r1, r1, lr
	and	r3, r3, #65280
	orr	r2, r2, ip
	orr	r3, r1, r3
	orr	r2, r2, r0, asl #16
	str	r3, [r9]
	add	r9, r9, #8
	str	r2, [r9, #-4]
	bne	.L1520
	b	.L1518
.L1516:
	movw	r3, #26414
	movt	r3, 42
	add	r3, r0, r3
	add	r0, r0, #1
	ldr	r3, [r4, r3, asl #2]
	cmp	r0, #24
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1516
	movw	r6, #11732
	mov	r7, #1
	movt	r6, 170
	add	r6, r4, r6
	mov	lr, #0
.L1517:
	mov	r3, lr, lsr #3
	and	r1, r7, #15
	mov	r0, lr, asl #1
	movw	r2, #26438
	mov	r3, r3, asl #4
	and	r0, r0, #14
	add	r1, r3, r1
	movt	r2, 42
	add	r3, r3, r0
	add	r2, r1, r2
	movw	r1, #26438
	add	lr, lr, #1
	movt	r1, 42
	add	r1, r3, r1
	ldr	r2, [r4, r2, asl #2]
	cmp	lr, #16
	ldr	r3, [r4, r1, asl #2]
	add	r7, r7, #2
	and	ip, r2, #-16777216
	ubfx	r0, r2, #8, #8
	uxtb	r9, r2
	mov	r2, r2, lsr #16
	mov	r8, r3, lsr #24
	ubfx	r1, r3, #8, #8
	mov	r9, r9, asl #16
	add	r6, r6, #8
	orr	r2, r9, r2, asl #24
	orr	r1, r1, r8, asl #8
	uxtb	r9, r3
	mov	r3, r3, lsr #8
	orr	r2, r2, r9
	and	r3, r3, #65280
	orr	r1, r1, ip
	orr	r2, r2, r3
	orr	r1, r1, r0, asl #16
	str	r2, [r6, #-8]
	str	r1, [r6, #-4]
	bne	.L1517
	b	.L1518
.L1504:
	ldr	r4, [r10, #68]
	mov	r0, #0
	ldr	r1, .L1536+12
	blx	r4
	mvn	r0, #0
	b	.L1531
.L1534:
	ldr	r2, [r6, #2112]
	ldr	r3, [r10, #68]
	ldr	r1, .L1536+16
	ldrsb	r2, [r2, #6]
	blx	r3
	mvn	r0, #0
	b	.L1531
.L1537:
	.align	2
.L1536:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC34
	.word	.LANCHOR1
	.word	.LC36
	.word	.LC35
	UNWIND(.fnend)
	.size	MVC_WritePicMsg, .-MVC_WritePicMsg
	.align	2
	.global	MVC_UpdatePicQpInf
	.type	MVC_UpdatePicQpInf, %function
MVC_UpdatePicQpInf:
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
	ldr	r2, [r1, #28]
	ldr	r3, [r1, #32]
	cmp	r2, r0
	movlt	r2, r0
	cmp	r3, r0
	str	r2, [r1, #28]
	movge	r3, r0
	str	r3, [r1, #32]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_UpdatePicQpInf, .-MVC_UpdatePicQpInf
	.align	2
	.global	MVC_WriteSliceMsg
	.type	MVC_WriteSliceMsg, %function
MVC_WriteSliceMsg:
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
	ldr	r3, [r0, #64]
	movw	r1, #4060
	mov	r4, r0
	mov	ip, r3
	str	r3, [fp, #-48]
	mul	r1, r1, ip
	ldr	r3, [r0, #32]
	ldr	r0, [r0, #544]
	add	r2, ip, #1
	sub	r3, r3, #1
	str	r2, [r4, #64]
	cmp	ip, r3
	add	r6, r0, r1
	addcc	r3, r1, #4048
	addcc	r3, r3, #12
	movcs	r3, #0
	addcc	r3, r0, r3
	str	r3, [r6, #4056]
	ldr	r2, [r4, #232]
	ldrb	ip, [r2]	@ zero_extendqisi2
	ldr	r3, [r2, #68]
	cmp	ip, #1
	cmpls	ip, r3
	bcs	.L1542
	add	lr, ip, #3
	add	lr, r6, lr, lsl #2
.L1543:
	mov	r3, ip, asl #5
	sub	r3, r3, ip, asl #2
	add	ip, ip, #1
	add	r2, r2, r3
	ldr	r2, [r2, #24]
	str	r2, [lr, #4]!
	ldr	r2, [r4, #232]
	add	r2, r2, r3
	ldr	r2, [r2, #20]
	str	r2, [lr, #-8]
	ldr	r2, [r4, #232]
	add	r3, r2, r3
	ldr	r3, [r3, #28]
	str	r3, [lr, #8]
	ldr	r2, [r4, #232]
	ldr	r3, [r2, #68]
	cmp	r3, ip
	movhi	r5, #1
	movls	r5, #0
	cmp	ip, #1
	movhi	r5, #0
	cmp	r5, #0
	bne	.L1543
.L1542:
	cmp	r3, #1
	bhi	.L1548
	add	r3, r3, #3
	add	ip, r6, #20
	mov	r2, #0
	add	r3, r6, r3, lsl #2
.L1547:
	str	r2, [r3, #4]!
	cmp	r3, ip
	str	r2, [r3, #-8]
	str	r2, [r3, #8]
	bne	.L1547
.L1548:
	add	r8, r4, #11141120
	ldr	r3, [fp, #-48]
	add	r8, r8, #8192
	add	r5, r4, #11075584
	cmp	r3, #0
	add	r9, r5, #36864
	ldrb	r3, [r8, #1601]	@ zero_extendqisi2
	add	r5, r5, #40960
	strb	r3, [r6, #1]
	ldr	r3, [r9, #1288]
	ldr	r2, [r5, #2136]
	add	r3, r3, #26
	add	r3, r3, r2
	str	r3, [r6, #32]
	bne	.L1644
	ldr	r2, [r8, #2112]
	str	r3, [r2, #604]
	ldr	r3, [r8, #2112]
	ldr	r2, [r6, #32]
	str	r2, [r3, #608]
.L1549:
	ldr	r3, [r5, #2132]
	str	r3, [r6, #36]
	ldr	r3, [r5, #584]
	str	r3, [r6, #40]
	ldr	r3, [r5, #580]
	str	r3, [r6, #44]
	ldrb	r3, [r5, #520]	@ zero_extendqisi2
	strb	r3, [r0, r1]
	ldr	r3, [r5, #576]
	str	r3, [r6, #48]
	ldrb	r3, [r5, #526]	@ zero_extendqisi2
	strb	r3, [r6, #2]
	ldr	r3, [r4, #236]
	ldrb	r3, [r3, #22]	@ zero_extendqisi2
	strb	r3, [r6, #3]
	ldr	r3, [r5, #568]
	str	r3, [r6, #52]
	ldr	r3, [r5, #572]
	str	r3, [r6, #56]
	ldrb	r3, [r5, #520]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r9, #1284]
	streqb	r3, [r6, #4]
	beq	.L1551
	cmp	r3, #0
	ldreqb	r3, [r9, #1242]	@ zero_extendqisi2
	movne	r3, #0
	strb	r3, [r6, #4]
.L1551:
	ldr	r3, [r9, #1292]
	str	r3, [r6, #60]
	ldr	r3, [r9, #1296]
	str	r3, [r6, #64]
	ldr	r3, [r5, #2144]
	str	r3, [r6, #68]
	ldr	r3, [r5, #2148]
	str	r3, [r6, #72]
	ldr	r3, [r5, #2140]
	str	r3, [r6, #76]
	ldrb	r3, [r5, #520]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1590
	ldr	ip, [r5, #568]
	cmp	ip, #0
	beq	.L1593
	ldr	r3, [r4, #256]
	ldr	r2, [r3, #4]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r1, r4, #256
	movne	r3, #0
	bne	.L1558
	b	.L1556
.L1560:
	ldr	r2, [r1, #4]!
	ldr	r2, [r2, #4]
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1556
.L1558:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1560
	mov	r3, #0
	str	r3, [fp, #-52]
.L1555:
	ldr	ip, [r5, #572]
	cmp	ip, #0
	beq	.L1594
	ldr	r3, [r4, #388]
	ldr	r2, [r3, #4]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r1, r4, #388
	movne	r3, #0
	bne	.L1564
	b	.L1562
.L1566:
	ldr	r2, [r1, #4]!
	ldr	r2, [r2, #4]
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1562
.L1564:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1566
	mov	r3, #0
	str	r3, [fp, #-56]
.L1561:
	ldrb	r2, [r8, #1595]	@ zero_extendqisi2
	ldr	r3, [r5, #568]
	cmp	r2, #0
	beq	.L1567
	cmp	r3, #0
	beq	.L1582
	mov	r3, #0
	mov	r10, r6
	str	r6, [fp, #-60]
	add	r7, r4, #256
	str	r8, [fp, #-64]
	mov	r6, r3
	mov	r8, r5
	ldr	r5, [fp, #-52]
	b	.L1581
.L1579:
	strb	r1, [r10, #1630]
	ldr	r1, [r7]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1631]
	ldr	r1, [r7]
	ldr	r1, [r1, #16]
	str	r1, [r10, #1656]
.L1580:
	ldr	r1, [r8, #568]
	add	r6, r6, #1
	add	r7, r7, #4
	add	r10, r10, #36
	cmp	r1, r6
	bls	.L1645
.L1581:
	ldr	r1, [r7]
	ldr	r0, [r4, #120]
	ldr	r1, [r1, #4]
	ldrsb	r1, [r1, #6]
	bl	FSP_GetLogicFs
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #48]
	str	r1, [r10, #1636]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	strb	r1, [r10, #1625]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r5
	beq	.L1578
	cmp	r0, #0
	ldrne	r1, [r0, #520]
	ldrne	r0, [r1, #4]
.L1578:
	str	r0, [r10, #1640]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #52]
	str	r1, [r10, #1644]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #32]
	str	r1, [r10, #1632]
	ldr	r1, [r7]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r10, #1624]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #576]	@ zero_extendqisi2
	strb	r1, [r10, #1626]
	ldr	r1, [r7]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1579
	strb	r1, [r10, #1628]
	ldr	r1, [r7]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1629]
	ldr	r1, [r7]
	ldr	r1, [r1, #16]
	str	r1, [r10, #1652]
	b	.L1580
.L1645:
	mov	r5, r8
	ldr	r6, [fp, #-60]
	ldr	r8, [fp, #-64]
.L1582:
	ldrb	r3, [r5, #520]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1646
.L1570:
	movw	r2, #47664
	add	r3, r6, #3920
	add	r0, r6, #4048
	movt	r2, 169
	add	r3, r3, #4
	add	r2, r4, r2
	add	r0, r0, #4
.L1587:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, r0
	bne	.L1587
	ldrb	r3, [r9, #1242]	@ zero_extendqisi2
	cmp	r3, #0
	str	r3, [r8, #3668]
	ldr	r3, [r9, #1284]
	str	r3, [r8, #3672]
	beq	.L1588
	ldrb	r2, [r5, #520]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1589
.L1588:
	cmp	r3, #1
	beq	.L1647
.L1590:
	ldr	r2, [fp, #-48]
	movw	r3, #35524
	movt	r3, 42
	ldr	r1, [r4, #232]
	add	r3, r2, r3
	mov	r2, #0
	add	r3, r4, r3, lsl #2
	str	r1, [r3, #4]
	str	r2, [r4, #232]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1644:
	ldr	r2, [r8, #2112]
	ldr	lr, [r2, #604]
	ldr	ip, [r2, #608]
	cmp	lr, r3
	movlt	lr, r3
	cmp	ip, r3
	str	lr, [r2, #604]
	movge	ip, r3
	str	ip, [r2, #608]
	b	.L1549
.L1556:
	ldrsb	r1, [r2, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	ldreq	ip, .L1649
	movweq	r3, #8058
	beq	.L1640
	ldr	r3, [r3, #520]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-52]
	b	.L1555
.L1647:
	ldrb	r3, [r5, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1590
.L1589:
	ldr	r3, [r5, #588]
	movw	r8, #41552
	movw	r7, #41680
	movw	lr, #41808
	movw	ip, #42320
	movw	r0, #42448
	str	r3, [r6, #80]
	movw	r1, #42576
	ldr	r10, [r5, #592]
	movt	r8, 169
	movt	r7, 169
	movt	lr, 169
	movt	ip, 169
	movt	r0, 169
	movt	r1, 169
	add	r8, r4, r8
	add	r7, r4, r7
	add	lr, r4, lr
	add	ip, r4, ip
	add	r0, r4, r0
	add	r1, r4, r1
	mov	r9, r6
	mov	r3, r6
	mov	r2, #0
	str	r6, [fp, #-52]
	str	r10, [r9, #84]!
.L1591:
	ldr	r10, [r8, #4]!
	add	r2, r2, #1
	add	r3, r3, #4
	str	r10, [r9, #4]!
	ldr	r10, [r7, #4]!
	str	r10, [r3, #212]
	ldr	r10, [lr, #4]!
	str	r10, [r3, #340]
	ldr	r10, [ip, #4]!
	str	r10, [r3, #852]
	ldr	r10, [r0, #4]!
	str	r10, [r3, #980]
	ldr	r10, [r1, #4]!
	str	r10, [r3, #1108]
	ldr	r10, [r5, #580]
	cmp	r10, r2
	bcs	.L1591
	ldrb	r3, [r5, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1590
	movw	r7, #41936
	movw	lr, #42064
	movw	ip, #42192
	movw	r0, #42704
	movw	r1, #42832
	movw	r2, #42960
	ldr	r8, [fp, #-52]
	movt	r7, 169
	movt	lr, 169
	movt	ip, 169
	movt	r0, 169
	movt	r1, 169
	movt	r2, 169
	add	r6, r6, #468
	add	r7, r4, r7
	add	lr, r4, lr
	add	ip, r4, ip
	add	r0, r4, r0
	add	r1, r4, r1
	add	r2, r4, r2
	mov	r3, #0
.L1592:
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
	ldr	r9, [r5, #584]
	cmp	r9, r3
	bcs	.L1592
	b	.L1590
.L1567:
	cmp	r3, #0
	beq	.L1575
	add	r3, r4, #256
	str	r8, [fp, #-64]
	mov	r8, r5
	ldr	r5, [fp, #-52]
	mov	r7, r6
	str	r6, [fp, #-60]
	mov	r10, r3
	mov	r6, r2
.L1574:
	ldr	r1, [r10]
	ldr	r0, [r4, #120]
	ldr	r1, [r1, #4]
	ldrsb	r1, [r1, #6]
	bl	FSP_GetLogicFs
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #48]
	str	r1, [r7, #1636]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	strb	r1, [r7, #1625]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r5
	beq	.L1573
	cmp	r0, #0
	ldrne	r1, [r0, #520]
	ldrne	r0, [r1, #4]
.L1573:
	str	r0, [r7, #1640]
	mov	r3, #0
	ldr	r1, [r10]
	add	r6, r6, #1
	add	r7, r7, #36
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #52]
	str	r1, [r7, #1608]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #32]
	str	r1, [r7, #1596]
	ldr	r1, [r10]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r7, #1591]
	ldr	r1, [r10]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r7, #1590]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #592]
	str	r1, [r7, #1612]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #628]
	str	r1, [r7, #1616]
	ldr	r1, [r10], #4
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #664]
	strb	r3, [r7, #1588]
	str	r1, [r7, #1620]
	ldr	r1, [r8, #568]
	cmp	r1, r6
	bhi	.L1574
	mov	r5, r8
	ldr	r6, [fp, #-60]
	ldr	r8, [fp, #-64]
.L1575:
	ldrb	r3, [r5, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1570
	ldr	r3, [r5, #572]
	cmp	r3, #0
	beq	.L1570
	add	r3, r4, #388
	str	r8, [fp, #-60]
	mov	r8, r5
	ldr	r5, [fp, #-56]
	mov	r10, #0
	mov	r7, r6
	str	r6, [fp, #-52]
	mov	r6, r10
	mov	r10, r3
.L1577:
	ldr	r1, [r10]
	ldr	r0, [r4, #120]
	ldr	r1, [r1, #4]
	ldrsb	r1, [r1, #6]
	bl	FSP_GetLogicFs
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #48]
	str	r1, [r7, #2788]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	strb	r1, [r7, #2777]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r5
	beq	.L1576
	cmp	r0, #0
	ldrne	r1, [r0, #520]
	ldrne	r0, [r1, #4]
.L1576:
	str	r0, [r7, #1640]
	mov	r3, #0
	ldr	r1, [r10]
	add	r6, r6, #1
	add	r7, r7, #36
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #52]
	str	r1, [r7, #2760]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #32]
	str	r1, [r7, #2748]
	ldr	r1, [r10]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r7, #2743]
	ldr	r1, [r10]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r7, #2742]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #592]
	str	r1, [r7, #2764]
	ldr	r1, [r10]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #628]
	str	r1, [r7, #2768]
	ldr	r1, [r10], #4
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #664]
	strb	r3, [r7, #2740]
	str	r1, [r7, #2772]
	ldr	r1, [r8, #572]
	cmp	r1, r6
	bhi	.L1577
.L1639:
	mov	r5, r8
	ldr	r6, [fp, #-52]
	ldr	r8, [fp, #-60]
	b	.L1570
.L1562:
	ldrsb	r1, [r2, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1648
	ldr	r3, [r3, #520]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-56]
	b	.L1561
.L1646:
	ldr	r3, [r5, #572]
	cmp	r3, #0
	beq	.L1570
	mov	r3, #0
	mov	r10, r6
	str	r6, [fp, #-52]
	add	r7, r4, #388
	str	r8, [fp, #-60]
	mov	r6, r3
	mov	r8, r5
	ldr	r5, [fp, #-56]
	b	.L1586
.L1584:
	strb	r1, [r10, #2782]
	ldr	r1, [r7]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2783]
	ldr	r1, [r7]
	ldr	r1, [r1, #16]
	str	r1, [r10, #2808]
.L1585:
	ldr	r1, [r8, #572]
	add	r6, r6, #1
	add	r7, r7, #4
	add	r10, r10, #36
	cmp	r1, r6
	bls	.L1639
.L1586:
	ldr	r1, [r7]
	ldr	r0, [r4, #120]
	ldr	r1, [r1, #4]
	ldrsb	r1, [r1, #6]
	bl	FSP_GetLogicFs
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #48]
	str	r1, [r10, #2788]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	strb	r1, [r10, #2777]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r5
	beq	.L1583
	cmp	r0, #0
	ldrne	r1, [r0, #520]
	ldrne	r0, [r1, #4]
.L1583:
	str	r0, [r10, #2792]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #52]
	str	r1, [r10, #2796]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #32]
	str	r1, [r10, #2784]
	ldr	r1, [r7]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r10, #2776]
	ldr	r1, [r7]
	ldr	r1, [r1, #4]
	ldrb	r1, [r1, #576]	@ zero_extendqisi2
	strb	r1, [r10, #2778]
	ldr	r1, [r7]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1584
	strb	r1, [r10, #2780]
	ldr	r1, [r7]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2781]
	ldr	r1, [r7]
	ldr	r1, [r1, #16]
	str	r1, [r10, #2804]
	b	.L1585
.L1648:
	ldr	ip, .L1649
	movw	r3, #8079
.L1640:
	ldr	r2, .L1649+4
	ldr	r1, .L1649+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L1593:
	str	ip, [fp, #-52]
	b	.L1555
.L1594:
	str	ip, [fp, #-56]
	b	.L1561
.L1650:
	.align	2
.L1649:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+80
	.word	.LC37
	UNWIND(.fnend)
	.size	MVC_WriteSliceMsg, .-MVC_WriteSliceMsg
	.align	2
	.global	MVC_GetPicStreamSize
	.type	MVC_GetPicStreamSize, %function
MVC_GetPicStreamSize:
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
	add	r0, r0, #11141120
	add	r0, r0, #12288
	ldr	r2, [r0, #156]
	cmp	r2, #0
	beq	.L1654
	mov	r0, #0
.L1653:
	ldr	r3, [r2, #8]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L1653
	ldmfd	sp, {fp, sp, pc}
.L1654:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetPicStreamSize, .-MVC_GetPicStreamSize
	.align	2
	.global	MVC_SliceCheck
	.type	MVC_SliceCheck, %function
MVC_SliceCheck:
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
	ldr	r1, .L1667
	mov	r4, r0
	add	r5, r0, #11075584
	bl	mvc_ue_v
	add	r5, r5, #40960
	str	r0, [r5, #576]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1665
	cmp	r0, #262144
	bcs	.L1666
	ldr	r2, [r4, #12]
	ldr	r3, [r4, #16]
	mul	r3, r3, r2
	sub	r3, r3, #1
	cmp	r0, r3
	bhi	.L1665
	ldr	r1, .L1667+4
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r7, .L1667+8
	ldr	r1, .L1667+12
	ldr	r3, [r7, #68]
	mov	r2, r0
	mov	r6, r0
	mov	r0, #19
	blx	r3
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1665
	cmp	r6, #9
	bhi	.L1661
	mov	r1, #1
	movw	r3, #297
	mov	r2, r1, asl r6
	and	r3, r3, r2
	cmp	r3, #0
	bne	.L1662
	ands	r0, r2, #660
	bne	.L1663
	tst	r2, #66
	beq	.L1661
	strb	r1, [r5, #520]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1662:
	strb	r0, [r5, #520]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1661:
	ldr	r3, [r7, #68]
	mov	r2, r6
	ldr	r1, .L1667+16
	mov	r0, #1
	blx	r3
.L1665:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1663:
	mov	r0, r3
	mov	r3, #2
	strb	r3, [r5, #520]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1666:
	ldr	r3, .L1667+8
	mov	r0, #1
	ldr	r1, .L1667+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1668:
	.align	2
.L1667:
	.word	.LC38
	.word	.LC40
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC41
	.word	.LC42
	.word	.LC39
	UNWIND(.fnend)
	.size	MVC_SliceCheck, .-MVC_SliceCheck
	.align	2
	.global	MVC_PPSSPSCheck
	.type	MVC_PPSSPSCheck, %function
MVC_PPSSPSCheck:
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
	ldr	r6, .L1681
	add	r5, r0, #11075584
	add	r5, r5, #40960
	mov	r4, r0
	ldr	r1, .L1681+4
	mov	r0, #19
	ldr	r3, [r6, #68]
	ldr	r2, [r5, #536]
	blx	r3
	ldr	r3, [r4, #252]
	ldr	r2, [r5, #536]
	mov	r1, #2240
	mla	r1, r1, r2, r3
	ldrb	r3, [r1, #19]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1679
	ldrb	r3, [r5, #532]	@ zero_extendqisi2
	sxtb	r5, r3
	cmn	r5, #1
	beq	.L1680
	cmp	r3, #0
	bne	.L1674
	ldr	r2, [r1, #28]
	movw	r3, #8500
	movt	r3, 5
	mul	r3, r3, r2
	add	r0, r4, r3
	add	ip, r0, #12992
	add	r3, r0, #286720
	add	ip, ip, #8
	add	r3, r3, #932
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1675
	add	r0, r0, #286720
	ldrb	r0, [r0, #957]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1675
.L1673:
	mov	r0, #0
	str	r1, [r4, #244]
	str	r3, [r4, #240]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1680:
	ldr	r2, [r1, #28]
	movw	r0, #3992
	ldr	r3, [r4, #248]
	mla	r3, r0, r2, r3
	ldrb	r0, [r3, #25]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1673
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L1681+8
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1675:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L1681+12
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1679:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L1681+16
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1674:
	ldr	r3, [r6, #68]
	mov	r2, r5
	ldr	r1, .L1681+20
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1682:
	.align	2
.L1681:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC43
	.word	.LC45
	.word	.LC46
	.word	.LC44
	.word	.LC31
	UNWIND(.fnend)
	.size	MVC_PPSSPSCheck, .-MVC_PPSSPSCheck
	.align	2
	.global	MVC_PPSSPSCheckTmpId
	.type	MVC_PPSSPSCheckTmpId, %function
MVC_PPSSPSCheckTmpId:
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
	ldr	r6, .L1692
	mov	r2, r1
	mov	r5, r1
	mov	r4, r0
	ldr	r1, .L1692+4
	mov	r0, #19
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r2, [r4, #252]
	mov	r3, #2240
	mla	r3, r3, r5, r2
	ldrb	r2, [r3, #19]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1689
	ldr	r1, [r4, #36]
	ldr	r2, [r3, #28]
	sub	r3, r1, #1
	cmp	r2, r3
	bhi	.L1690
	movw	r3, #41492
	movt	r3, 169
	add	r3, r4, r3
	ldrsb	r5, [r3]
	cmn	r5, #1
	beq	.L1691
.L1688:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1691:
	ldr	r1, [r4, #248]
	movw	r3, #3992
	mla	r3, r3, r2, r1
	ldrb	r3, [r3, #25]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1688
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L1692+8
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1689:
	ldr	r3, [r6, #68]
	mov	r2, r5
	ldr	r1, .L1692+12
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1690:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L1692+16
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1693:
	.align	2
.L1692:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LC50
	.word	.LC48
	.word	.LC49
	UNWIND(.fnend)
	.size	MVC_PPSSPSCheckTmpId, .-MVC_PPSSPSCheckTmpId
	.align	2
	.global	MVC_IsNewPic
	.type	MVC_IsNewPic, %function
MVC_IsNewPic:
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
	add	ip, r0, #11075584
	ldr	lr, [r0, #236]
	add	r3, ip, #40960
	ldr	r1, [lr, #744]
	ldr	r0, [r3, #2184]
	ldr	r2, [r3, #2188]
	ldr	r4, [r3, #536]
	ldr	r5, [r3, #2192]
	cmp	r2, r4
	cmpeq	r0, r1
	ldr	r2, [r3, #548]
	ldrb	r4, [r3, #2176]	@ zero_extendqisi2
	ldrb	r0, [r3, #521]	@ zero_extendqisi2
	movne	r1, #1
	moveq	r1, #0
	cmp	r5, r2
	moveq	r2, r1
	orrne	r2, r1, #1
	cmp	r4, r0
	orrne	r2, r2, #1
	cmp	r4, #0
	cmpne	r0, #0
	beq	.L1696
	ldrb	r0, [r3, #2177]	@ zero_extendqisi2
	ldrb	r1, [r3, #522]	@ zero_extendqisi2
	cmp	r0, r1
	orrne	r2, r2, #1
.L1696:
	ldrb	r1, [r3, #2179]	@ zero_extendqisi2
	ldrb	r0, [r3, #528]	@ zero_extendqisi2
	cmp	r1, r0
	moveq	r1, #0
	beq	.L1697
	cmp	r0, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
.L1697:
	ldrb	r0, [r3, #2178]	@ zero_extendqisi2
	ldrb	r4, [r3, #523]	@ zero_extendqisi2
	cmp	r0, r4
	orrne	r2, r2, #1
	cmp	r4, #5
	cmpeq	r0, #5
	orr	r2, r2, r1
	beq	.L1709
.L1698:
	ldr	r1, [lr, #2900]
	cmp	r1, #0
	bne	.L1699
	add	r1, ip, #36864
	ldr	r0, [r3, #2204]
	ldr	r4, [r3, #2200]
	ldr	r5, [r1, #3488]
	ldr	lr, [r1, #3484]
	cmp	r4, lr
	cmpeq	r0, r5
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
.L1700:
	ldrb	r1, [r3, #531]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1701
	ldr	r1, [r3, #2220]
	ldrb	r0, [r3, #2180]	@ zero_extendqisi2
	ldrb	r6, [r3, #529]	@ zero_extendqisi2
	ldr	r5, [r3, #2160]
	ldrb	r4, [r3, #2181]	@ zero_extendqisi2
	cmp	r1, r5
	cmpeq	r0, r6
	ldrb	lr, [r3, #530]	@ zero_extendqisi2
	movne	r1, #1
	moveq	r1, #0
	cmp	r4, lr
	moveq	r3, r1
	orrne	r3, r1, #1
	orr	r2, r2, r3
.L1701:
	add	r3, ip, #40960
	ldr	ip, .L1710
	ldr	r1, .L1710+4
	mov	r0, #19
	ldr	r4, [r3, #576]
	ldr	r3, [ip, #68]
	cmp	r4, #0
	movne	r4, r2
	orreq	r4, r2, #1
	mov	r2, r4
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1699:
	cmp	r1, #1
	bne	.L1700
	add	r1, ip, #36864
	ldr	r0, [r3, #2212]
	ldr	r4, [r3, #2208]
	ldr	r5, [r1, #3524]
	ldr	lr, [r1, #3520]
	cmp	r4, lr
	cmpeq	r0, r5
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
	b	.L1700
.L1709:
	ldr	r0, [r3, #2196]
	ldr	r1, [r3, #564]
	cmp	r0, r1
	orrne	r2, r2, #1
	b	.L1698
.L1711:
	.align	2
.L1710:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC51
	UNWIND(.fnend)
	.size	MVC_IsNewPic, .-MVC_IsNewPic
	.align	2
	.global	mvc_ref_pic_list_reordering
	.type	mvc_ref_pic_list_reordering, %function
mvc_ref_pic_list_reordering:
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
	add	r5, r0, #11075584
	ldr	r2, [r0, #240]
	add	r8, r5, #40960
	add	r5, r5, #36864
	mov	r3, #0
	mov	r6, #1
	ldrb	r1, [r8, #531]	@ zero_extendqisi2
	mov	r4, r0
	strb	r3, [r5, #3564]
	cmp	r1, r3
	strb	r3, [r5, #3565]
	ldrb	r3, [r8, #521]	@ zero_extendqisi2
	movne	r7, #5
	moveq	r7, #3
	cmp	r3, #0
	ldr	r3, [r2, #2896]
	addne	r3, r3, #5
	addeq	r3, r3, #4
	mov	r6, r6, asl r3
	ldrb	r3, [r8, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L1767
.L1766:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
.L1733:
	adds	r3, r3, #0
	movne	r3, #1
	rsb	r0, r3, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1767:
	ldr	r1, .L1774
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #3564]
	cmp	r0, #0
	beq	.L1723
	ldr	r3, [r8, #580]
	cmn	r3, #2
	beq	.L1749
	movw	r10, #40428
	mov	r9, #0
	movt	r10, 169
	add	r10, r4, r10
	b	.L1730
.L1724:
	cmp	r0, #2
	beq	.L1768
	sub	r0, r0, #4
	cmp	r0, #1
	bls	.L1769
.L1727:
	ldr	r3, [r8, #580]
	add	r9, r9, #1
	add	r3, r3, #2
	cmp	r3, r9
	bls	.L1770
.L1730:
	ldr	r1, .L1774+4
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r7, r0
	str	r0, [r10, #4]!
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	bcc	.L1720
	cmp	r3, #0
	bne	.L1720
	cmp	r0, #3
	beq	.L1723
	cmp	r0, #1
	bhi	.L1724
	ldr	r1, .L1774+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r6, r0
	str	r0, [r10, #264]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	bls	.L1726
	cmp	r3, #0
	beq	.L1727
.L1726:
	ldr	ip, .L1774+12
	mov	r2, r0
	ldr	r1, .L1774+16
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1723:
	ldrb	r3, [r8, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1766
	ldr	r1, .L1774+20
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #3565]
	cmp	r0, #0
	beq	.L1766
	ldr	r3, [r8, #584]
	cmn	r3, #2
	beq	.L1766
	movw	r9, #40560
	mov	r5, #0
	movt	r9, 169
	add	r9, r4, r9
	b	.L1746
.L1745:
	add	r5, r5, #1
	cmp	r5, r3
	bcs	.L1766
.L1746:
	ldr	r1, .L1774+24
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r7, r0
	str	r0, [r9, #4]!
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	bcc	.L1737
	cmp	r3, #0
	bne	.L1737
	cmp	r0, #3
	beq	.L1733
	cmp	r0, #1
	bls	.L1771
	cmp	r0, #2
	beq	.L1772
	sub	r0, r0, #4
	cmp	r0, #1
	bls	.L1773
	ldr	r3, [r8, #584]
	add	r3, r3, #2
	cmp	r3, r5
	bne	.L1745
.L1747:
	ldr	r3, .L1774+12
	mov	r0, #1
	ldr	r1, .L1774+28
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1771:
	ldr	r1, .L1774+32
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r6, r0
	str	r0, [r9, #264]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	bls	.L1741
	cmp	r3, #0
	bne	.L1741
.L1742:
	ldr	r3, [r8, #584]
	add	r3, r3, #2
	cmp	r3, r5
	bne	.L1745
	ldr	r2, [r9]
	cmp	r2, #3
	beq	.L1745
	b	.L1747
.L1768:
	ldr	r1, .L1774+36
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r10, #528]
	b	.L1727
.L1772:
	ldr	r1, .L1774+40
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #524]
	b	.L1742
.L1769:
	ldr	r1, .L1774+44
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r10, #784]
	b	.L1727
.L1773:
	ldr	r1, .L1774+48
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #784]
	b	.L1742
.L1720:
	ldr	ip, .L1774+12
	mov	r2, r0
	ldr	r1, .L1774+52
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1737:
	ldr	ip, .L1774+12
	mov	r2, r0
	ldr	r1, .L1774+56
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1770:
	cmp	r9, r3
	bne	.L1723
.L1718:
	movw	r2, #26490
	movt	r2, 42
	add	r2, r3, r2
	add	r2, r4, r2, lsl #2
	ldr	r3, [r2, #8]
	cmp	r3, #3
	beq	.L1723
	ldr	r3, .L1774+12
	mov	r0, #1
	ldr	r1, .L1774+60
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1741:
	ldr	ip, .L1774+12
	mov	r2, r0
	ldr	r1, .L1774+64
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1749:
	mov	r3, #0
	b	.L1718
.L1775:
	.align	2
.L1774:
	.word	.LC52
	.word	.LC53
	.word	.LC55
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC56
	.word	.LC60
	.word	.LC61
	.word	.LC67
	.word	.LC63
	.word	.LC57
	.word	.LC65
	.word	.LC58
	.word	.LC66
	.word	.LC54
	.word	.LC62
	.word	.LC59
	.word	.LC64
	UNWIND(.fnend)
	.size	mvc_ref_pic_list_reordering, .-mvc_ref_pic_list_reordering
	.align	2
	.global	mvc_pred_weight_table
	.type	mvc_pred_weight_table, %function
mvc_pred_weight_table:
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
	ldr	r3, [r0, #244]
	ldr	r1, .L1806
	add	r6, r0, #11075584
	ldr	r7, [r0, #240]
	mov	r5, r0
	str	r3, [fp, #-48]
	bl	mvc_ue_v
	add	r6, r6, #40960
	mov	r4, #1
	str	r0, [r6, #588]
	mov	r8, r4, asl r0
	ldr	r9, [r7, #748]
	cmp	r9, #0
	bne	.L1800
.L1777:
	cmp	r0, #7
	bhi	.L1780
	ldr	r3, [r6, #592]
	cmp	r3, #7
	bhi	.L1780
	ldrb	r2, [r5, #10]	@ zero_extendqisi2
	cmp	r2, #0
	movweq	r10, #41684
	moveq	r4, r2
	movteq	r10, 169
	addeq	r10, r5, r10
	beq	.L1788
	b	.L1779
.L1784:
	ldr	r2, [r7, #748]
	cmp	r2, #0
	bne	.L1801
.L1785:
	str	r2, [r10]
	str	r2, [r10, #768]
	str	r2, [r10, #128]
	str	r2, [r10, #896]
.L1787:
	ldr	r2, [r6, #580]
	add	r4, r4, #1
	add	r10, r10, #4
	cmp	r2, r4
	bcc	.L1802
.L1788:
	ldr	r1, .L1806+4
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	streq	r8, [r10, #-128]
	streq	r0, [r10, #640]
	beq	.L1784
	ldr	r1, .L1806+8
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1806+12
	str	r0, [r10, #-128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r10, #640]
	ldr	r2, [r7, #748]
	cmp	r2, #0
	beq	.L1785
.L1801:
	ldr	r1, .L1806+16
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1803
	str	r9, [r10]
	str	r0, [r10, #768]
	str	r9, [r10, #128]
	str	r0, [r10, #896]
	b	.L1787
.L1802:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #44]
	cmp	r3, #1
	beq	.L1789
.L1790:
	ldrb	r0, [r5, #10]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L1782:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1803:
	ldr	r1, .L1806+20
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1806+24
	str	r0, [r10]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1806+20
	str	r0, [r10, #768]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1806+24
	str	r0, [r10, #128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r10, #896]
	b	.L1787
.L1800:
	ldr	r1, .L1806+28
	mov	r0, r5
	bl	mvc_ue_v
	mov	r3, r0
	ldr	r0, [r6, #588]
	mov	r9, r4, asl r3
	str	r3, [r6, #592]
	b	.L1777
.L1789:
	ldrb	r3, [r6, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1790
	movw	r4, #42068
	mov	r10, #0
	movt	r4, 169
	add	r4, r5, r4
	b	.L1796
.L1792:
	ldr	r3, [r7, #748]
	cmp	r3, #0
	bne	.L1804
.L1793:
	str	r3, [r4]
	str	r3, [r4, #768]
	str	r3, [r4, #128]
	str	r3, [r4, #896]
.L1795:
	ldr	r3, [r6, #584]
	add	r10, r10, #1
	add	r4, r4, #4
	cmp	r3, r10
	bcc	.L1790
.L1796:
	ldr	r1, .L1806+32
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	streq	r8, [r4, #-128]
	streq	r0, [r4, #640]
	beq	.L1792
	ldr	r1, .L1806+36
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1806+40
	str	r0, [r4, #-128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r4, #640]
	ldr	r3, [r7, #748]
	cmp	r3, #0
	beq	.L1793
.L1804:
	ldr	r1, .L1806+44
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1805
	str	r9, [r4]
	str	r0, [r4, #768]
	str	r9, [r4, #128]
	str	r0, [r4, #896]
	b	.L1795
.L1780:
	ldrb	r2, [r5, #10]	@ zero_extendqisi2
.L1779:
	ldr	r3, .L1806+48
	mov	r0, #1
	ldr	r1, .L1806+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1782
.L1805:
	ldr	r1, .L1806+56
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1806+60
	str	r0, [r4]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1806+56
	str	r0, [r4, #768]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1806+60
	str	r0, [r4, #128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r4, #896]
	b	.L1795
.L1807:
	.align	2
.L1806:
	.word	.LC68
	.word	.LC71
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC69
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC70
	.word	.LC81
	.word	.LC82
	UNWIND(.fnend)
	.size	mvc_pred_weight_table, .-mvc_pred_weight_table
	.align	2
	.global	MVC_DecMMCO
	.type	MVC_DecMMCO, %function
MVC_DecMMCO:
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
	mov	r4, r0
	moveq	r7, #100
	beq	.L1820
	mov	r9, #0
	b	.L1811
.L1843:
	ldr	r1, .L1849
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r5, #2
	beq	.L1841
.L1822:
	cmp	r5, #6
	orreq	r6, r6, #1
	cmp	r6, #0
	bne	.L1825
	cmp	r5, #4
	beq	.L1842
.L1826:
	cmp	r5, #6
	bhi	.L1827
.L1823:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1827
	cmp	r5, #0
	beq	.L1829
.L1828:
	subs	r7, r7, #1
	beq	.L1830
.L1820:
	ldr	r1, .L1849+4
	mov	r0, r4
	bl	mvc_ue_v
	bic	r3, r0, #2
	sub	r6, r0, #3
	clz	r6, r6
	cmp	r3, #1
	mov	r5, r0
	mov	r6, r6, lsr #5
	beq	.L1843
	cmp	r5, #2
	bne	.L1822
.L1841:
	ldr	r1, .L1849+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r6, #0
	beq	.L1823
.L1825:
	ldr	r1, .L1849+12
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r5, #4
	bne	.L1826
.L1842:
	ldr	r1, .L1849+16
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1828
.L1827:
	ldr	r3, .L1849+20
	mov	r0, #1
	ldr	r1, .L1849+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1848:
	ldr	r1, .L1849
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r8, #4]
	cmp	r3, #2
	str	r0, [r8, #8]
	beq	.L1844
.L1814:
	cmp	r3, #3
	cmpne	r3, #6
	beq	.L1845
.L1815:
	cmp	r3, #4
	beq	.L1846
.L1816:
	cmp	r3, #6
	bhi	.L1827
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1827
	cmp	r3, #0
	add	r9, r9, #1
	beq	.L1829
	cmp	r9, #100
	beq	.L1847
.L1811:
	ldr	r1, .L1849+4
	mov	r0, r4
	ldrb	r5, [r4, #3]	@ zero_extendqisi2
	bl	mvc_ue_v
	mov	r6, r9, asl #2
	mov	r7, r9, asl #4
	add	r1, r6, r7
	movw	r2, #2004
	movw	r8, #43184
	mla	r2, r2, r5, r1
	movt	r8, 169
	add	r2, r4, r2
	add	r8, r2, r8
	mov	r3, r0
	bic	r0, r0, #2
	cmp	r0, #1
	str	r3, [r8, #4]
	beq	.L1848
	cmp	r3, #2
	bne	.L1814
.L1844:
	ldr	r1, .L1849+8
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r6, r7
	movw	r2, #2004
	movw	r1, #43192
	mla	r3, r2, r5, r3
	movw	r2, #43184
	movt	r1, 169
	movt	r2, 169
	add	r3, r4, r3
	add	r1, r3, r1
	add	r2, r3, r2
	str	r0, [r1, #4]
	ldr	r3, [r2, #4]
	cmp	r3, #3
	cmpne	r3, #6
	bne	.L1815
.L1845:
	ldr	r1, .L1849+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r6, r7
	movw	r2, #2004
	movw	r1, #43192
	mla	r3, r2, r5, r3
	movw	r2, #43184
	movt	r1, 169
	movt	r2, 169
	add	r3, r4, r3
	add	r1, r3, r1
	add	r2, r3, r2
	str	r0, [r1, #8]
	ldr	r3, [r2, #4]
	cmp	r3, #4
	bne	.L1816
.L1846:
	ldr	r1, .L1849+16
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, r7
	movw	r7, #2004
	movw	r2, #43200
	mla	r5, r7, r5, r6
	movw	r3, #43184
	movt	r2, 169
	movt	r3, 169
	add	r5, r4, r5
	add	r2, r5, r2
	add	r3, r5, r3
	str	r0, [r2, #4]
	ldr	r3, [r3, #4]
	b	.L1816
.L1829:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1847:
	ldr	r3, .L1849+20
	mov	r0, #1
	ldr	r1, .L1849+28
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1830:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1850:
	.align	2
.L1849:
	.word	.LC85
	.word	.LC84
	.word	.LC86
	.word	.LC87
	.word	.LC88
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC89
	.word	.LC83
	UNWIND(.fnend)
	.size	MVC_DecMMCO, .-MVC_DecMMCO
	.align	2
	.global	mvc_dec_ref_pic_marking
	.type	mvc_dec_ref_pic_marking, %function
mvc_dec_ref_pic_marking:
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
	add	r3, r0, #11075584
	add	r3, r3, #40960
	mov	r4, r0
	ldrb	r7, [r0, #3]	@ zero_extendqisi2
	ldrb	r8, [r3, #525]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L1852
	clz	r2, r7
	mov	r2, r2, lsr #5
	strb	r2, [r0, #3]
	mov	r6, r2
.L1861:
	ldrb	r3, [r3, #523]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1872
	ldr	r1, .L1876
	mov	r0, r4
	bl	mvc_u_1
	movw	r2, #2004
	mla	r6, r2, r6, r4
	movw	r5, #43184
	ldr	r9, .L1876+4
	movt	r5, 169
	ldr	r1, .L1876+8
	add	r5, r6, r5
	ldr	r6, [r9, #68]
	mov	r3, r0
	uxtb	r2, r0
	strb	r3, [r5, #3]
	mov	r0, #16
	blx	r6
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1855
.L1859:
	mov	r8, #0
.L1869:
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1852:
	movw	r2, #2004
	movw	r1, #43184
	mla	r2, r2, r7, r0
	movt	r1, 169
	movw	r5, #43184
	mov	r6, r7
	movt	r5, 169
	add	r5, r2, r5
	ldrb	r2, [r2, r1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1861
	ldrb	r3, [r3, #523]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1873
	ldr	r1, .L1876
	ldrb	r6, [r5, #3]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r6, r0
	bne	.L1874
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1859
	mov	r1, r8
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MVC_DecMMCO
.L1855:
	mov	r1, #1
	mov	r0, r4
	bl	MVC_DecMMCO
	cmn	r0, #1
	mov	r8, r0
	movne	r3, #1
	movne	r8, #0
	strneb	r3, [r5]
	bne	.L1869
	mov	r3, #0
	ldr	r1, .L1876+12
	strb	r3, [r5]
	mov	r0, #1
	strb	r7, [r4, #3]
	ldr	r3, [r9, #68]
	blx	r3
	b	.L1869
.L1873:
	ldr	r1, .L1876+16
	ldrb	r6, [r5, #1]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r6, r0
	bne	.L1875
	mov	r0, r4
	ldr	r1, .L1876+20
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r4, r0
	beq	.L1859
	ldr	r3, .L1876+4
	mov	r0, #1
	ldr	r1, .L1876+24
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1869
.L1872:
	ldr	r1, .L1876+16
	mov	r0, r4
	bl	mvc_u_1
	movw	r2, #2004
	mla	r2, r2, r6, r4
	movw	r5, #43184
	movt	r5, 169
	ldr	r1, .L1876+20
	mov	r8, #0
	add	r5, r2, r5
	strb	r0, [r5, #1]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, .L1876+4
	ldrb	r2, [r5, #1]	@ zero_extendqisi2
	ldr	r1, .L1876+28
	ldr	r3, [r3, #68]
	strb	r0, [r5, #2]
	mov	r0, #16
	blx	r3
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1874:
	ldr	r5, .L1876+4
	mov	r0, #1
	ldr	r1, .L1876+32
	mvn	r8, #0
	ldr	r3, [r5, #68]
	blx	r3
	ldr	ip, [r4, #68]
	ldr	r3, [r4, #100]
	mov	r0, #1
	ldr	r2, [r4, #88]
	ldr	r1, .L1876+36
	ldr	r4, [r5, #68]
	str	ip, [sp]
	blx	r4
	b	.L1869
.L1875:
	ldr	r3, .L1876+4
	mov	r0, #1
	ldr	r1, .L1876+40
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1869
.L1877:
	.align	2
.L1876:
	.word	.LC93
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC94
	.word	.LC95
	.word	.LC90
	.word	.LC91
	.word	.LC97
	.word	.LC92
	.word	.LC98
	.word	.LC99
	.word	.LC96
	UNWIND(.fnend)
	.size	mvc_dec_ref_pic_marking, .-mvc_dec_ref_pic_marking
	.align	2
	.global	MVC_ProcessSliceHeaderFirstPart
	.type	MVC_ProcessSliceHeaderFirstPart, %function
MVC_ProcessSliceHeaderFirstPart:
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
	ldr	r1, .L1943
	mov	r4, r0
	bl	mvc_ue_v
	ldr	r3, [r4, #40]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r6, r0
	bhi	.L1879
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1879
	mov	r1, r0
	mov	r0, r4
	bl	MVC_PPSSPSCheckTmpId
	cmp	r0, #0
	bne	.L1934
	add	r7, r4, #11075584
	mov	r0, r4
	add	r5, r7, #40960
	str	r6, [r5, #536]
	bl	MVC_PPSSPSCheck
	subs	r8, r0, #0
	bne	.L1935
	ldr	r6, [r4, #240]
	mov	r0, r4
	ldr	r2, .L1943+4
	ldr	r9, [r4, #244]
	ldr	r1, [r6, #2896]
	add	r1, r1, #4
	bl	mvc_u_v
	str	r0, [r5, #548]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1932
	adds	r0, r0, #0
	ldrb	r3, [r5, #523]	@ zero_extendqisi2
	movne	r0, #1
	cmp	r3, #5
	movne	r0, #0
	cmp	r0, #0
	bne	.L1936
.L1885:
	mov	r3, #0
	strb	r3, [r5, #521]
	strb	r3, [r5, #522]
	ldrb	r3, [r6, #20]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1937
	ldr	r2, [r6, #3948]
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	mla	r3, r1, r3, r3
.L1908:
	ldrb	r2, [r6, #21]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1891
	strb	r2, [r5, #524]
.L1893:
	ldr	r2, [r5, #576]
	cmp	r2, r3
	bcs	.L1938
.L1894:
	ldrb	r3, [r5, #523]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1939
.L1896:
	add	r10, r7, #36864
	mov	r3, #0
	str	r3, [r10, #3484]
	str	r3, [r10, #3488]
	ldr	r3, [r6, #2900]
	cmp	r3, #0
	beq	.L1940
.L1900:
	mov	r3, #0
	str	r3, [r10, #3520]
	str	r3, [r10, #3524]
	ldr	r3, [r6, #2900]
	cmp	r3, #1
	beq	.L1941
.L1903:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1932
	ldrb	r3, [r9, #17]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1906
	ldr	r1, .L1943+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L1907
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1906
.L1907:
	ldr	r3, .L1943+12
	mov	r0, #1
	ldr	r1, .L1943+16
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, .L1943+20
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L1932
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #102
	blx	r5
.L1932:
	mvn	r8, #0
.L1918:
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1937:
	ldr	r1, .L1943+24
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #521]
	cmp	r0, #0
	bne	.L1942
	ldr	r2, [r6, #3948]
	ldrb	ip, [r6, #20]	@ zero_extendqisi2
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	cmp	ip, #0
	mla	r3, r1, r3, r3
	bne	.L1910
	mov	r3, r3, asl #1
	b	.L1908
.L1891:
	mov	r2, #1
	strb	r2, [r5, #524]
.L1911:
	ldr	r2, [r5, #576]
	cmp	r2, r3, lsr #1
	bcc	.L1894
	ldr	r3, .L1943+12
	mov	r0, #1
	ldr	r1, .L1943+28
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1918
.L1942:
	ldr	r1, .L1943+32
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #522]
	ldr	r2, [r6, #3948]
	ldrb	r0, [r6, #20]	@ zero_extendqisi2
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	cmp	r0, #0
	ldrb	r0, [r5, #521]	@ zero_extendqisi2
	mla	r3, r1, r3, r3
	moveq	r2, #2
	beq	.L1889
.L1910:
	mov	r2, #1
.L1889:
	cmp	r0, #0
	mul	r3, r2, r3
	beq	.L1908
	cmp	r0, #1
	mov	r2, #0
	strb	r2, [r5, #524]
	bne	.L1893
	b	.L1911
.L1906:
	mov	r0, r4
	add	r7, r7, #40960
	bl	MVC_IsNewPic
	uxtb	r0, r0
	strb	r0, [r7, #525]
	cmp	r0, #0
	bne	.L1918
	ldr	r2, [r7, #576]
	ldr	r3, [r7, #2216]
	cmp	r2, r3
	bhi	.L1918
	ldr	r3, .L1943+12
	mov	r0, #1
	ldr	r1, .L1943+36
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1918
.L1940:
	ldr	r1, [r6, #2904]
	mov	r0, r4
	ldr	r2, .L1943+40
	add	r1, r1, #4
	bl	mvc_u_v
	str	r0, [r10, #3484]
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1900
	ldrb	r3, [r5, #521]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1900
	ldr	r1, .L1943+44
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #3488]
	b	.L1900
.L1941:
	ldrb	r3, [r6, #18]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1903
	ldr	r1, .L1943+48
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #3520]
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1903
	ldrb	r3, [r5, #521]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1903
	ldr	r1, .L1943+52
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #3524]
	b	.L1903
.L1879:
	ldr	r3, .L1943+12
	mov	r2, r6
	ldr	r1, .L1943+56
	mvn	r8, #0
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1939:
	ldr	r1, .L1943+60
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #65536
	str	r0, [r5, #564]
	bcs	.L1897
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1896
.L1897:
	ldr	r3, .L1943+12
	mov	r0, #1
	ldr	r1, .L1943+64
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1896
.L1934:
	ldr	r3, .L1943+12
	mov	r0, #1
	ldr	r1, .L1943+68
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1918
.L1935:
	ldr	r3, .L1943+12
	mov	r0, #1
	ldr	r1, .L1943+72
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1918
.L1936:
	ldr	r3, [r5, #2160]
	cmp	r3, #0
	bgt	.L1885
	ldr	r3, .L1943+12
	mov	r0, #1
	ldr	r1, .L1943+76
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1885
.L1938:
	ldr	r3, .L1943+12
	mov	r0, #1
	ldr	r1, .L1943+80
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1918
.L1944:
	.align	2
.L1943:
	.word	.LC100
	.word	.LC104
	.word	.LC116
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC117
	.word	g_event_report
	.word	.LC106
	.word	.LC108
	.word	.LC107
	.word	.LC118
	.word	.LC112
	.word	.LC113
	.word	.LC114
	.word	.LC115
	.word	.LC101
	.word	.LC110
	.word	.LC111
	.word	.LC102
	.word	.LC103
	.word	.LC105
	.word	.LC109
	UNWIND(.fnend)
	.size	MVC_ProcessSliceHeaderFirstPart, .-MVC_ProcessSliceHeaderFirstPart
	.align	2
	.global	MVC_ProcessSliceHeaderSecondPart
	.type	MVC_ProcessSliceHeaderSecondPart, %function
MVC_ProcessSliceHeaderSecondPart:
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
	add	r4, r0, #11075584
	ldr	r3, [r0, #40]
	add	r4, r4, #40960
	mov	r5, r0
	sub	r3, r3, #1
	ldr	r6, [r0, #244]
	ldr	r2, [r4, #536]
	cmp	r3, r2
	bcc	.L1946
	ldrb	r7, [r0, #10]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L1946
	bl	MVC_PPSSPSCheck
	cmp	r0, #0
	bne	.L2028
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L2029
.L1950:
	ldr	r2, [r6, #36]
	cmp	r3, #1
	str	r2, [r4, #580]
	ldr	r2, [r6, #40]
	str	r2, [r4, #584]
	bls	.L2030
	cmp	r3, #2
	beq	.L1977
.L1961:
	mov	r3, #32
	str	r3, [r4, #584]
.L1962:
	mov	r0, r5
	bl	mvc_ref_pic_list_reordering
	subs	r8, r0, #0
	bne	.L2031
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1964
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r7, #1
	moveq	r2, r7
	beq	.L1965
.L1964:
	ldr	r3, [r6, #44]
	cmp	r3, #1
	beq	.L2032
.L1981:
	mov	r2, #0
.L1965:
	ldr	r9, .L2038
	mov	r0, #19
	strb	r7, [r4, #527]
	ldr	r1, .L2038+4
	ldr	r3, [r9, #68]
	blx	r3
	ldrb	r2, [r4, #527]	@ zero_extendqisi2
	mov	r3, #0
	str	r3, [r4, #588]
	cmp	r2, r3
	str	r3, [r4, #592]
	bne	.L2033
.L1966:
	ldrb	r3, [r4, #528]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2034
.L1967:
	mov	r3, #0
	str	r3, [r4, #2132]
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1968
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L2035
.L1968:
	ldr	r1, .L2038+8
	mov	r0, r5
	bl	mvc_se_v
	mov	r3, #0
	str	r3, [r4, #2140]
	str	r3, [r4, #2144]
	str	r3, [r4, #2148]
	str	r0, [r4, #2136]
	ldrb	r3, [r6, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2036
.L1997:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1977:
	mov	r3, #32
	str	r3, [r4, #580]
	b	.L1961
.L2036:
	ldr	r1, .L2038+12
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r4, #2140]
	bhi	.L1971
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1971
	cmp	r0, #1
	beq	.L1997
	ldr	r1, .L2038+16
	mov	r0, r5
	bl	mvc_se_v
	add	r3, r0, #6
	str	r0, [r4, #2144]
	cmp	r3, #12
	bhi	.L1974
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1974
	ldr	r1, .L2038+20
	mov	r0, r5
	bl	mvc_se_v
	add	r3, r0, #6
	str	r0, [r4, #2148]
	cmp	r3, #12
	bhi	.L1976
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1997
.L1976:
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L2038+24
	mvn	r8, #0
	blx	r3
	b	.L1997
.L2033:
	mov	r0, r5
	bl	mvc_pred_weight_table
	cmp	r0, #0
	beq	.L1966
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L2038+28
	mvn	r8, #0
	blx	r3
	b	.L1997
.L2034:
	mov	r0, r5
	bl	mvc_dec_ref_pic_marking
	cmp	r0, #0
	beq	.L1967
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L2038+32
	mvn	r8, #0
	blx	r3
	b	.L1997
.L2032:
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r7, r3
	moveq	r2, r7
	bne	.L1981
	b	.L1965
.L2029:
	ldr	r1, .L2038+36
	mov	r0, r5
	bl	mvc_u_1
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	strb	r0, [r4, #526]
	b	.L1950
.L2030:
	ldr	r1, .L2038+40
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1952
	ldr	r3, [r4, #580]
.L1953:
	ldrb	r2, [r4, #521]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1954
	cmp	r3, #15
	bhi	.L1955
	ldr	r3, [r4, #584]
	cmp	r3, #15
	bhi	.L2037
.L1956:
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1955
.L1957:
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1977
	cmp	r3, #1
	bne	.L1961
	b	.L1962
.L1946:
	ldr	r3, .L2038
	mvn	r8, #0
	ldr	r1, .L2038+44
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2035:
	ldr	r1, .L2038+48
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r4, #2132]
	bhi	.L1969
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1968
.L1969:
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L2038+52
	mvn	r8, #0
	blx	r3
	b	.L1997
.L1954:
	cmp	r3, #31
	bhi	.L1958
	ldr	r3, [r4, #584]
	cmp	r3, #31
	bls	.L1959
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1959
.L1958:
	ldr	r3, .L2038
	mov	r0, #1
	ldr	r1, .L2038+56
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1997
.L1959:
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1957
	b	.L1958
.L2037:
	ldrb	r3, [r4, #520]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1956
.L1955:
	ldr	r3, .L2038
	mov	r0, #1
	ldr	r1, .L2038+60
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1997
.L1952:
	ldr	r1, .L2038+64
	mov	r0, r5
	bl	mvc_ue_v
	ldrb	r2, [r4, #520]	@ zero_extendqisi2
	cmp	r2, #1
	mov	r3, r0
	str	r0, [r4, #580]
	bne	.L1953
	ldr	r1, .L2038+68
	mov	r0, r5
	bl	mvc_ue_v
	ldr	r3, [r4, #580]
	str	r0, [r4, #584]
	b	.L1953
.L1974:
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L2038+72
	mvn	r8, #0
	blx	r3
	b	.L1997
.L1971:
	ldr	r3, [r9, #68]
	mov	r0, #1
	ldr	r1, .L2038+76
	mvn	r8, #0
	blx	r3
	b	.L1997
.L2028:
	ldr	r3, .L2038
	mov	r0, #1
	ldr	r1, .L2038+80
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1997
.L2031:
	ldr	r3, .L2038
	mov	r0, #1
	ldr	r1, .L2038+84
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1997
.L2039:
	.align	2
.L2038:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC126
	.word	.LC131
	.word	.LC132
	.word	.LC134
	.word	.LC136
	.word	.LC137
	.word	.LC127
	.word	.LC128
	.word	.LC119
	.word	.LC120
	.word	.LC101
	.word	.LC129
	.word	.LC130
	.word	.LC124
	.word	.LC123
	.word	.LC121
	.word	.LC122
	.word	.LC135
	.word	.LC133
	.word	.LC102
	.word	.LC125
	UNWIND(.fnend)
	.size	MVC_ProcessSliceHeaderSecondPart, .-MVC_ProcessSliceHeaderSecondPart
	.align	2
	.global	MVC_ExitSlice
	.type	MVC_ExitSlice, %function
MVC_ExitSlice:
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
	add	r2, r0, #11075584
	ldr	ip, [r0, #236]
	add	r3, r2, #40960
	ldrb	r1, [r3, #521]	@ zero_extendqisi2
	ldr	lr, [r3, #536]
	cmp	r1, #0
	ldr	r5, [r3, #576]
	str	lr, [r3, #2188]
	ldr	r4, [ip, #744]
	strb	r1, [r3, #2176]
	ldrneb	r1, [r3, #522]	@ zero_extendqisi2
	ldr	lr, [r3, #548]
	str	r5, [r3, #2216]
	strneb	r1, [r3, #2177]
	ldrb	r1, [r3, #523]	@ zero_extendqisi2
	str	lr, [r3, #2192]
	cmp	r1, #5
	ldrb	lr, [r3, #528]	@ zero_extendqisi2
	strb	r1, [r3, #2178]
	ldreq	r1, [r3, #564]
	str	r4, [r3, #2184]
	strb	lr, [r3, #2179]
	streq	r1, [r3, #2196]
	ldr	r1, [ip, #2900]
	cmp	r1, #0
	bne	.L2043
	add	r1, r2, #36864
	ldr	lr, [r1, #3484]
	str	lr, [r3, #2200]
	ldr	r1, [r1, #3488]
	str	r1, [r3, #2204]
	ldr	r1, [ip, #2900]
.L2043:
	cmp	r1, #1
	addeq	r2, r2, #36864
	ldreq	r1, [r2, #3520]
	streq	r1, [r3, #2208]
	ldreq	r2, [r2, #3524]
	streq	r2, [r3, #2212]
	ldrb	r2, [r3, #531]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L2045
	ldr	ip, [r3, #2160]
	ldrb	r1, [r3, #529]	@ zero_extendqisi2
	ldrb	r2, [r3, #530]	@ zero_extendqisi2
	str	ip, [r3, #2220]
	strb	r1, [r3, #2180]
	strb	r2, [r3, #2181]
.L2045:
	ldr	r3, [r0, #80]
	add	r3, r3, #1
	str	r3, [r0, #80]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_ExitSlice, .-MVC_ExitSlice
	.align	2
	.global	MVC_PicTypeStatistic
	.type	MVC_PicTypeStatistic, %function
MVC_PicTypeStatistic:
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
	add	r3, r0, #11075584
	add	r3, r3, #40960
	ldrb	r2, [r3, #520]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L2051
	bcc	.L2052
	cmp	r2, #2
	ldmnefd	sp, {fp, sp, pc}
	ldrb	r3, [r3, #523]	@ zero_extendqisi2
	add	r0, r0, #11141120
	cmp	r3, #5
	beq	.L2061
.L2054:
	add	r0, r0, #8192
	mov	r3, #0
	strb	r3, [r0, #1605]
	ldmfd	sp, {fp, sp, pc}
.L2052:
	add	r0, r0, #11141120
	add	r3, r0, #8192
	ldrb	r2, [r3, #1604]	@ zero_extendqisi2
	cmp	r2, #2
	movne	r2, #1
	strneb	r2, [r3, #1604]
	b	.L2054
.L2051:
	add	r0, r0, #11141120
	mov	r2, #2
	add	r0, r0, #8192
	mov	r3, #0
	strb	r2, [r0, #1604]
	strb	r3, [r0, #1605]
	ldmfd	sp, {fp, sp, pc}
.L2061:
	add	r0, r0, #8192
	mov	r3, #1
	strb	r3, [r0, #1605]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_PicTypeStatistic, .-MVC_PicTypeStatistic
	.align	2
	.global	MVC_CalcStreamBits
	.type	MVC_CalcStreamBits, %function
MVC_CalcStreamBits:
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
	add	r3, r0, #11075584
	add	r3, r3, #36864
	mov	r4, r0
	ldrb	r3, [r3, #1240]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2063
	ldr	r2, [r0, #232]
	ldr	r3, [r2, #64]
	add	r3, r3, #7
	bic	r3, r3, #7
	str	r3, [r2, #64]
	ldr	r2, [r0, #232]
	ldr	r3, [r2, #72]
	sub	r3, r3, #1
	str	r3, [r2, #72]
.L2063:
	ldr	r0, [r4, #232]
	ldrb	r7, [r0]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L2074
	mov	r3, #0
	mov	r2, r0
	mov	r5, r3
.L2065:
	add	r3, r3, #1
	ldr	r1, [r2, #12]
	cmp	r3, r7
	add	r2, r2, #28
	add	r5, r5, r1
	bne	.L2065
.L2064:
	mov	r8, r7, asl #5
	ldr	r3, [r0, #72]
	sub	r8, r8, r7, asl #2
	ldr	r2, [r0, #64]
	add	r0, r0, r8
	ldr	r6, .L2085
	str	r3, [sp, #4]
	mov	r3, r5
	ldr	ip, [r0, #12]
	mov	r0, #7
	ldr	r1, .L2085+4
	ldr	r9, [r6, #68]
	str	ip, [sp]
	blx	r9
	ldr	r3, [r4, #232]
	mov	r2, r7
	mov	r0, #7
	ldr	r1, .L2085+8
	ldrb	r7, [r3]	@ zero_extendqisi2
	ldr	ip, [r3, #64]
	mov	lr, r7, asl #5
	and	ip, ip, r0
	sub	lr, lr, r7, asl #2
	add	r3, r3, lr
	str	ip, [r3, #24]
	ldr	r3, [r4, #232]
	ldrb	ip, [r3]	@ zero_extendqisi2
	ldr	r7, [r3, #64]
	mov	lr, ip, asl #5
	sub	lr, lr, ip, asl #2
	add	r3, r3, lr
	ldr	ip, [r3, #16]
	add	ip, ip, r7, lsr #3
	rsb	ip, r5, ip
	str	ip, [r3, #28]
	ldr	r3, [r4, #232]
	ldrb	r7, [r3]	@ zero_extendqisi2
	ldr	ip, [r3, #64]
	mov	lr, r7, asl #5
	sub	lr, lr, r7, asl #2
	add	r3, r3, lr
	ldr	lr, [r3, #12]
	add	r5, r5, lr
	rsb	r5, ip, r5, lsl #3
	str	r5, [r3, #20]
	ldr	ip, [r4, #232]
	ldrb	lr, [ip]	@ zero_extendqisi2
	mov	r3, lr, asl #5
	sub	r3, r3, lr, asl #2
	add	r3, ip, r3
	ldr	ip, [r3, #28]
	ldr	lr, [r3, #24]
	and	ip, ip, #3
	add	ip, lr, ip, lsl #3
	str	ip, [r3, #24]
	ldr	ip, [r4, #232]
	ldrb	lr, [ip]	@ zero_extendqisi2
	mov	r3, lr, asl #5
	sub	r3, r3, lr, asl #2
	add	r3, ip, r3
	ldr	ip, [r3, #28]
	bic	ip, ip, #3
	str	ip, [r3, #28]
	ldr	ip, [r4, #232]
	ldr	r5, [r6, #68]
	add	r8, ip, r8
	ldrb	r7, [ip]	@ zero_extendqisi2
	ldr	r3, [r8, #24]
	mov	lr, r7, asl #5
	sub	lr, lr, r7, asl #2
	add	ip, ip, lr
	ldr	ip, [ip, #28]
	str	ip, [sp, #4]
	ldr	ip, [r8, #20]
	str	ip, [sp]
	blx	r5
	ldr	ip, [r4, #232]
	ldr	r2, [ip, #68]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L2084
	ldrb	r5, [ip]	@ zero_extendqisi2
	add	r1, r5, #1
	cmp	r2, r1
	movhi	r2, #1
	movls	r2, #0
	cmp	r1, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L2067
	add	r5, r5, #2
	mov	r7, #0
.L2068:
	sub	r3, r5, #1
	ldr	r1, .L2085+12
	mov	r0, #7
	mov	lr, r3, asl #5
	mov	r2, r3
	sub	r3, lr, r3, asl #2
	add	ip, ip, r3
	str	r7, [ip, #24]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #16]
	str	lr, [ip, #28]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #12]
	mov	lr, lr, asl #3
	str	lr, [ip, #20]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	ldr	r8, [ip, #24]
	and	lr, lr, #3
	add	lr, r8, lr, lsl #3
	str	lr, [ip, #24]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	bic	lr, lr, #3
	str	lr, [ip, #28]
	ldr	ip, [r4, #232]
	ldr	r8, [r6, #68]
	add	ip, ip, r3
	ldr	r3, [ip, #24]
	ldr	ip, [ip, #20]
	str	ip, [sp]
	blx	r8
	ldr	ip, [r4, #232]
	ldr	r3, [ip, #68]
	cmp	r5, #1
	cmpls	r5, r3
	add	r5, r5, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L2068
	sub	r3, r3, #1
.L2067:
	mov	r2, r3, asl #5
	ldr	r1, [ip, #72]
	sub	r3, r2, r3, asl #2
	add	ip, ip, r3
	ldr	r3, [ip, #20]
	rsb	r3, r1, r3
	str	r3, [ip, #20]
	ldr	lr, [r4, #232]
	ldrb	r1, [lr]	@ zero_extendqisi2
	ldr	ip, [lr, #68]
	cmp	r1, ip
	bcs	.L2062
	sxth	r3, r1
	add	r4, r4, #11141120
	add	r4, r4, #8192
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, lr, r3
.L2072:
	ldr	r2, [r3, #28]
	add	r1, r1, #1
	ldr	r0, [r4, #2184]
	add	r3, r3, #28
	cmp	r2, r0
	strcc	r2, [r4, #2184]
	ldrcc	ip, [lr, #68]
	cmp	ip, r1
	bhi	.L2072
.L2062:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2084:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L2085+16
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L2074:
	mov	r5, r7
	b	.L2064
.L2086:
	.align	2
.L2085:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC138
	.word	.LC139
	.word	.LC141
	.word	.LC140
	UNWIND(.fnend)
	.size	MVC_CalcStreamBits, .-MVC_CalcStreamBits
	.align	2
	.global	MVC_Scaling_List
	.type	MVC_Scaling_List, %function
MVC_Scaling_List:
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
	ble	.L2087
	mov	r3, r7
	mov	ip, #8
	ldr	r9, .L2098
	mov	r5, ip
	mov	r4, #0
	mov	r10, #255
	mov	r7, r1
	mov	r8, r3
	b	.L2092
.L2091:
	mov	r0, r3, lsr #2
	and	lr, r3, #3
	str	r5, [r7, r3, asl #2]
	uxtb	r1, r5
	ldr	r3, [r6, r0, asl #2]
	mov	lr, lr, asl #3
	cmp	r4, r8
	bic	r3, r3, r10, asl lr
	orr	r1, r3, r1, asl lr
	str	r1, [r6, r0, asl #2]
	beq	.L2087
.L2092:
	cmp	r8, #16
	ldreq	r3, .L2098+4
	ldrneb	r3, [r4, r9]	@ zero_extendqisi2
	ldreqb	r3, [r4, r3]	@ zero_extendqisi2
	cmp	ip, #0
	add	r4, r4, #1
	beq	.L2091
	ldr	r1, .L2098+8
	ldr	r0, [fp, #-52]
	str	r3, [fp, #-48]
	bl	mvc_se_v
	ldr	r2, [fp, #4]
	ldr	r3, [fp, #-48]
	add	r0, r5, r0
	add	r0, r0, #256
	mov	ip, r0, asr #31
	mov	ip, ip, lsr #24
	add	r0, r0, ip
	uxtb	r0, r0
	rsb	r1, ip, r0
	rsb	ip, ip, r0
	clz	r1, r1
	mov	r1, r1, lsr #5
	cmp	r1, #0
	moveq	r5, ip
	cmp	r3, #0
	movne	r1, #0
	andeq	r1, r1, #1
	str	r1, [r2]
	b	.L2091
.L2087:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2099:
	.align	2
.L2098:
	.word	.LANCHOR0+16
	.word	.LANCHOR0
	.word	.LC142
	UNWIND(.fnend)
	.size	MVC_Scaling_List, .-MVC_Scaling_List
	.align	2
	.global	MVC_ProcessPPS
	.type	MVC_ProcessPPS, %function
MVC_ProcessPPS:
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
	mov	r5, r1
	ldr	r1, .L2158
	mov	r4, r0
	bl	mvc_u_1
	strb	r0, [r5]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2149
	ldr	r1, .L2158+4
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #1]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2149
	ldr	r1, .L2158+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	str	r0, [r5, #32]
	bne	.L2104
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2105
.L2104:
	ldr	r3, .L2158+12
	mov	r0, #1
	ldr	r1, .L2158+16
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, .L2158+20
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2149
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #102
	blx	r5
	mvn	r0, #0
.L2102:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2112:
	ldr	r1, .L2158+24
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2158+28
	str	r0, [r5, #60]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #18]
	cmp	r0, #1
	beq	.L2113
.L2131:
	ldr	r1, .L2158+32
	mov	r0, r4
	bl	mvc_se_v
	add	r3, r0, #12
	str	r0, [r5, #56]
	cmp	r3, #24
	bhi	.L2114
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2132
.L2114:
	ldr	r3, .L2158+12
	mov	r0, #1
	ldr	r1, .L2158+36
	ldr	r3, [r3, #68]
	blx	r3
.L2149:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2105:
	ldr	r1, .L2158+40
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #31
	str	r0, [r5, #36]
	bhi	.L2106
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2106
	ldr	r1, .L2158+44
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #31
	str	r0, [r5, #40]
	bhi	.L2108
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2108
	ldr	r1, .L2158+48
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #2]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2149
	ldr	r2, .L2158+52
	mov	r1, #2
	mov	r0, r4
	bl	mvc_u_v
	cmp	r0, #2
	str	r0, [r5, #44]
	bhi	.L2150
	ldr	r1, .L2158+56
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2158+60
	str	r0, [r5, #48]
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2158+64
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2158+68
	str	r0, [r5, #52]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2158+72
	strb	r0, [r5, #3]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2158+76
	strb	r0, [r5, #4]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #17]
	cmp	r0, #0
	bne	.L2151
.L2111:
	ldr	r3, [r5, #52]
	mov	r6, #0
	add	r0, r4, #548
	str	r6, [r5, #60]
	strb	r6, [r5, #18]
	str	r3, [r5, #56]
	bl	BsResidBits
	ldr	r3, [r4, #232]
	ldr	r3, [r3, #72]
	add	r3, r3, #3
	cmp	r0, r3
	bcs	.L2112
.L2132:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2151:
	ldr	r3, .L2158+12
	mov	r0, #1
	ldr	r1, .L2158+80
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2111
.L2106:
	ldr	r3, .L2158+12
	mov	r0, #1
	ldr	r1, .L2158+84
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2102
.L2108:
	ldr	r3, .L2158+12
	mov	r0, #1
	ldr	r1, .L2158+88
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2102
.L2113:
	sub	r8, fp, #72
	add	r10, r5, #4
	add	r7, r5, #2016
	add	r9, r5, #64
	b	.L2122
.L2155:
	ldr	r3, [r4, #248]
	ldr	ip, [r5, #28]
	mla	ip, lr, ip, r3
	ldrb	r3, [ip, #27]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L2152
	ldr	r3, .L2158+92
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2158+12
	ldr	r3, [r3, #52]
	blx	r3
.L2117:
	add	r6, r6, #1
	add	r7, r7, #16
	cmp	r6, #6
	add	r9, r9, #64
	beq	.L2153
.L2122:
	ldr	r1, .L2158+96
	mov	r0, r4
	bl	mvc_u_1
	movw	lr, #3992
	clz	r1, r6
	mov	r2, #16
	cmp	r0, #1
	mov	r3, r0
	mov	r0, r7
	str	r3, [r8, #4]!
	strb	r3, [r10, #1]!
	beq	.L2154
	cmp	r6, #0
	cmpne	r6, #3
	mov	r1, r1, lsr #5
	beq	.L2155
	ldr	r3, .L2158+12
	mov	r2, #16
	sub	r1, r7, #16
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2117
.L2153:
	add	r8, r5, #2112
	add	r10, r5, #448
	sub	r7, fp, #76
	add	r9, r5, #11
	mov	r6, #0
.L2130:
	ldr	r2, [r5, #60]
	mov	r3, #0
	cmp	r2, #1
	strne	r3, [r7]
	strneb	r3, [r9]
	beq	.L2156
.L2125:
	ldr	r1, [r4, #248]
	movw	ip, #3992
	ldr	r3, [r5, #28]
	mov	r0, r8
	mov	r2, #64
	mla	r3, ip, r3, r1
	ldrb	r1, [r3, #27]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L2157
	ldr	r1, .L2158+100
	cmp	r6, #0
	ldr	r3, .L2158+12
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L2126:
	add	r6, r6, #1
	add	r8, r8, #64
	cmp	r6, #2
	add	r10, r10, #256
	add	r7, r7, #4
	add	r9, r9, #1
	bne	.L2130
	b	.L2131
.L2154:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r7
	mov	r1, r9
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2117
	ldr	r1, .L2158+92
	mov	r2, #16
	ldr	r3, .L2158+12
	cmp	r6, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r7
	blx	r3
	b	.L2117
.L2152:
	ldr	r3, .L2158+12
	add	r1, r6, #167
	mov	r2, #16
	mov	r0, r7
	add	r1, ip, r1, lsl #4
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2117
.L2150:
	ldr	r3, .L2158+12
	mov	r0, #1
	ldr	r1, .L2158+104
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2102
.L2156:
	ldr	r1, .L2158+108
	mov	r0, r4
	bl	mvc_u_1
	mov	r2, r8
	mov	r1, r10
	mov	r3, #64
	mov	ip, r0
	cmp	ip, #1
	mov	r0, r4
	str	ip, [r7]
	strb	ip, [r9]
	bne	.L2125
	str	r7, [sp]
	bl	MVC_Scaling_List
	ldr	r3, [r7]
	cmp	r3, #1
	bne	.L2126
	ldr	r1, .L2158+100
	mov	r2, #64
	ldr	r3, .L2158+12
	cmp	r6, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r8
	blx	r3
	b	.L2126
.L2157:
	add	r1, r3, r6, lsl #6
	ldr	r3, .L2158+12
	add	r1, r1, #2768
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2126
.L2159:
	.align	2
.L2158:
	.word	.LC143
	.word	.LC144
	.word	.LC145
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC146
	.word	g_event_report
	.word	.LC161
	.word	.LC162
	.word	.LC163
	.word	.LC166
	.word	.LC147
	.word	.LC149
	.word	.LC151
	.word	.LC152
	.word	.LC154
	.word	.LC155
	.word	.LC156
	.word	.LC157
	.word	.LC158
	.word	.LC159
	.word	.LC160
	.word	.LC148
	.word	.LC150
	.word	.LANCHOR1
	.word	.LC164
	.word	.LANCHOR1+32
	.word	.LC153
	.word	.LC165
	UNWIND(.fnend)
	.size	MVC_ProcessPPS, .-MVC_ProcessPPS
	.align	2
	.global	MVC_PPSEqual
	.type	MVC_PPSEqual, %function
MVC_PPSEqual:
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
	subs	r7, r0, #0
	ldreq	ip, .L2189
	movweq	r3, #10214
	beq	.L2187
	cmp	r1, #0
	beq	.L2188
	ldr	r2, [r1, #28]
	ldr	r0, [r7, #28]
	ldr	r3, [r7, #24]
	ldr	ip, [r1, #24]
	ldrb	lr, [r7]	@ zero_extendqisi2
	cmp	r0, r2
	cmpeq	r3, ip
	ldrb	r4, [r1]	@ zero_extendqisi2
	ldrb	ip, [r7, #1]	@ zero_extendqisi2
	ldrb	r5, [r1, #1]	@ zero_extendqisi2
	moveq	r2, #1
	movne	r2, #0
	ldr	r0, [r7, #36]
	cmp	lr, r4
	movne	r3, #0
	andeq	r3, r2, #1
	ldr	r4, [r1, #36]
	cmp	ip, r5
	movne	lr, #0
	andeq	lr, r3, #1
	ldr	r2, [r7, #40]
	ldr	r5, [r1, #40]
	cmp	r0, r4
	movne	ip, #0
	andeq	ip, lr, #1
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	ldrb	r4, [r1, #2]	@ zero_extendqisi2
	cmp	r2, r5
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	lr, [r7, #44]
	ldr	r5, [r1, #44]
	cmp	r3, r4
	movne	r2, #0
	andeq	r2, r0, #1
	ldr	ip, [r7, #48]
	ldr	r4, [r1, #48]
	cmp	lr, r5
	movne	r3, #0
	andeq	r3, r2, #1
	ldr	r0, [r7, #52]
	ldr	r5, [r1, #52]
	cmp	ip, r4
	movne	lr, #0
	andeq	lr, r3, #1
	ldrb	r2, [r7, #3]	@ zero_extendqisi2
	ldrb	r4, [r1, #3]	@ zero_extendqisi2
	cmp	r0, r5
	movne	ip, #0
	andeq	ip, lr, #1
	ldrb	r3, [r7, #4]	@ zero_extendqisi2
	ldrb	lr, [r1, #4]	@ zero_extendqisi2
	cmp	r2, r4
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	ip, [r7, #60]
	ldr	r4, [r1, #60]
	cmp	r3, lr
	movne	r2, #0
	andeq	r2, r0, #1
	ldrb	r0, [r7, #18]	@ zero_extendqisi2
	ldrb	lr, [r1, #18]	@ zero_extendqisi2
	cmp	ip, r4
	movne	r3, #0
	andeq	r3, r2, #1
	cmp	lr, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #0
	beq	.L2164
	mov	ip, ip, asl #1
	adds	r2, ip, #6
	str	r2, [fp, #-60]
	beq	.L2164
	sub	r2, r7, #1088
	sub	r10, r1, #1088
	add	r0, r1, #64
	sub	r2, r2, #4
	sub	r10, r10, #4
	str	r2, [fp, #-48]
	add	r9, r7, #1984
	add	r2, r7, #4
	add	r8, r1, #1984
	str	r2, [fp, #-56]
	add	r2, r1, #4
	str	r2, [fp, #-52]
	sub	r2, r7, #836
	mov	ip, r7
	mov	r6, #0
	mov	r5, r0
	str	r7, [fp, #-64]
	str	r1, [fp, #-68]
.L2169:
	ldr	r0, [fp, #-56]
	ldrb	r1, [r0, #1]!	@ zero_extendqisi2
	str	r0, [fp, #-56]
	ldr	r0, [fp, #-52]
	ldrsb	lr, [r0, #1]!
	str	r0, [fp, #-52]
	sxtb	r0, r1
	cmp	lr, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r1, #0
	beq	.L2186
	ldr	r1, [r9]
	ldr	r0, [r8]
	cmp	r1, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r6, #5
	bhi	.L2166
	cmp	r1, #0
	add	r7, ip, #64
	bne	.L2165
	add	r0, ip, #128
	mov	r1, r7
	mov	ip, r5
.L2167:
	ldr	r4, [r1], #4
	ldr	lr, [ip], #4
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r1, r0
	bne	.L2167
.L2165:
	ldr	r1, [fp, #-60]
	add	r6, r6, #1
	add	r9, r9, #4
	add	r8, r8, #4
	cmp	r6, r1
	ldr	r1, [fp, #-48]
	add	r10, r10, #256
	add	r2, r2, #256
	add	r1, r1, #256
	mov	ip, r7
	str	r1, [fp, #-48]
	add	r5, r5, #64
	bne	.L2169
	ldr	r7, [fp, #-64]
	ldr	r1, [fp, #-68]
.L2164:
	ldr	r0, [r7, #56]
	ldr	r2, [r1, #56]
	cmp	r0, r2
	movne	r0, #0
	andeq	r0, r3, #1
	eor	r0, r0, #1
	rsb	r0, r0, #0
.L2162:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2166:
	cmp	r1, #0
	bne	.L2186
	ldr	r1, [fp, #-48]
	mov	lr, r10
.L2168:
	ldr	r4, [r1, #4]!
	ldr	r0, [lr, #4]!
	cmp	r4, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r1
	bne	.L2168
.L2186:
	add	r7, ip, #64
	b	.L2165
.L2188:
	ldr	ip, .L2189
	mov	r0, r1
	movw	r3, #10215
.L2187:
	ldr	r2, .L2189+4
	ldr	r1, .L2189+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2162
.L2190:
	.align	2
.L2189:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_PPSEqual, .-MVC_PPSEqual
	.align	2
	.global	MVC_DecPPS
	.type	MVC_DecPPS, %function
MVC_DecPPS:
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
	ldr	r1, .L2206
	mov	r4, r0
	bl	mvc_ue_v
	ldr	r3, [r4, #40]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r5, r0
	bls	.L2192
	ldr	r3, .L2206+4
	mov	r2, r0
	ldr	r1, .L2206+8
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r2, [r4, #40]
	sub	r3, r2, #1
	cmp	r5, r3
	bls	.L2199
	ldr	r3, .L2206+12
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L2199
	str	r2, [fp, #-40]
	mov	r3, #8
	str	r5, [fp, #-44]
	sub	r2, fp, #44
	ldr	r0, [r4, #120]
	mov	r1, #110
	blx	r6
	mvn	r0, #0
.L2193:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2192:
	ldr	r1, .L2206+16
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r4, #36]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	ip, r0
	bhi	.L2203
	mov	r8, #2240
	ldr	r3, [r4, #252]
	mul	r6, r8, r5
	add	r3, r3, r6
	ldrb	r7, [r3, #19]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L2195
	ldr	r7, .L2206+20
	mov	r0, r4
	mov	r1, r7
	str	r5, [r7, #24]
	str	ip, [r7, #28]
	bl	MVC_ProcessPPS
	subs	r5, r0, #0
	bne	.L2204
	ldr	r1, [r4, #252]
	mov	r0, r7
	add	r1, r1, r6
	bl	MVC_PPSEqual
	cmp	r0, #0
	beq	.L2193
	ldr	ip, .L2206+4
	mov	r3, #1
	ldr	r0, [r4, #252]
	mov	r2, r8
	strb	r3, [r7, #20]
	mov	r1, r7
	add	r0, r0, r6
	ldr	r4, [ip, #56]
	strb	r3, [r7, #19]
	blx	r4
	mov	r0, r5
	b	.L2193
.L2195:
	str	r5, [r3, #24]
	mov	r0, r4
	ldr	r3, [r4, #252]
	add	r3, r3, r6
	str	ip, [r3, #28]
	ldr	r1, [r4, #252]
	add	r1, r1, r6
	bl	MVC_ProcessPPS
	cmp	r0, #0
	bne	.L2205
	ldr	r3, [r4, #252]
	mov	r2, #1
	add	r3, r3, r6
	strb	r2, [r3, #20]
	ldr	r3, [r4, #252]
	add	r6, r3, r6
	strb	r2, [r6, #19]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2199:
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2203:
	ldr	r3, .L2206+4
	mov	r0, #1
	ldr	r1, .L2206+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2193
.L2204:
	ldr	r3, .L2206+4
	movw	r2, #9978
	ldr	r1, .L2206+28
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2193
.L2205:
	ldr	r3, .L2206+4
	movw	r2, #9998
	ldr	r1, .L2206+28
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #252]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r6
	strb	r2, [r3, #20]
	ldr	r3, [r4, #252]
	add	r6, r3, r6
	strb	r7, [r6, #19]
	b	.L2193
.L2207:
	.align	2
.L2206:
	.word	.LC167
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC168
	.word	g_event_report
	.word	.LC169
	.word	.LANCHOR2
	.word	.LC170
	.word	.LC171
	UNWIND(.fnend)
	.size	MVC_DecPPS, .-MVC_DecPPS
	.align	2
	.global	mvc_vui_parameters
	.type	mvc_vui_parameters, %function
mvc_vui_parameters:
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
	mov	r5, r1
	ldr	r1, .L2258
	mov	r4, r0
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	streqb	r0, [r5, #15]
	bne	.L2252
.L2210:
	ldr	r1, .L2258+4
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	bne	.L2253
.L2211:
	ldr	r1, .L2258+8
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #3]
	cmp	r0, #0
	moveq	r3, #5
	streq	r3, [r5, #28]
	bne	.L2254
.L2213:
	ldr	r1, .L2258+12
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #6]
	cmp	r0, #0
	bne	.L2255
.L2214:
	ldr	r1, .L2258+16
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #8]
	cmp	r0, #0
	bne	.L2256
.L2216:
	ldr	r1, .L2258+20
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #7]
	cmp	r0, #0
	beq	.L2218
	ldr	r1, .L2258+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r2, .L2258+28
	mov	r1, #4
	str	r0, [r5, #96]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+32
	mov	r1, #4
	strb	r0, [r5, #92]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [r5, #96]
	cmp	r3, #31
	strb	r0, [r5, #93]
	bhi	.L2224
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	addeq	r7, r5, #96
	addeq	r8, r5, #59
	bne	.L2224
.L2222:
	ldr	r1, .L2258+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #96]
	cmp	r3, r6
	bcs	.L2222
	ldr	r2, .L2258+48
	mov	r1, #5
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+52
	mov	r1, #5
	str	r0, [r5, #356]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+56
	mov	r1, #5
	str	r0, [r5, #360]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+60
	mov	r1, #5
	str	r0, [r5, #364]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #368]
.L2218:
	ldr	r1, .L2258+64
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #10]
	cmp	r0, #0
	bne	.L2257
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2229
.L2228:
	ldr	r1, .L2258+68
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2258+72
	strb	r0, [r5, #11]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #12]
	cmp	r0, #0
	bne	.L2230
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
.L2231:
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2257:
	ldr	r1, .L2258+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r2, .L2258+28
	mov	r1, #4
	str	r0, [r5, #408]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+32
	mov	r1, #4
	strb	r0, [r5, #404]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [r5, #408]
	cmp	r3, #31
	strb	r0, [r5, #405]
	bhi	.L2224
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	addeq	r8, r5, #368
	addeq	r7, r5, #408
	addeq	r8, r8, #3
	bne	.L2224
.L2226:
	ldr	r1, .L2258+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #408]
	cmp	r3, r6
	bcs	.L2226
	ldr	r2, .L2258+48
	mov	r1, #5
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+52
	mov	r1, #5
	str	r0, [r5, #668]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+56
	mov	r1, #5
	str	r0, [r5, #672]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+60
	mov	r1, #5
	str	r0, [r5, #676]
	mov	r0, r4
	bl	mvc_u_v
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r5, #680]
	bne	.L2229
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2228
.L2229:
	ldr	r1, .L2258+76
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #14]
	b	.L2228
.L2256:
	ldr	r2, .L2258+80
	mov	r1, #32
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+84
	mov	r1, #32
	str	r0, [r5, #52]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2258+88
	str	r0, [r5, #56]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #9]
	cmp	r0, #1
	bne	.L2216
	ldr	r1, [r5, #52]
	cmp	r1, #0
	beq	.L2216
	ldr	r0, [r5, #56]
	bl	__aeabi_uidiv
	mov	r0, r0, lsr #1
	str	r0, [r4, #56]
	b	.L2216
.L2255:
	ldr	r1, .L2258+92
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+96
	str	r0, [r5, #44]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #48]
	b	.L2214
.L2254:
	ldr	r2, .L2258+100
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2258+104
	str	r0, [r5, #28]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2258+108
	strb	r0, [r5, #4]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #5]
	cmp	r0, #0
	beq	.L2213
	ldr	r2, .L2258+112
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+116
	mov	r1, #8
	str	r0, [r5, #32]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+120
	mov	r1, #8
	str	r0, [r5, #36]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #40]
	b	.L2213
.L2253:
	ldr	r1, .L2258+124
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #2]
	b	.L2211
.L2252:
	ldr	r2, .L2258+128
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	uxtb	r0, r0
	strb	r0, [r5, #15]
	cmp	r0, #255
	bne	.L2210
	ldr	r2, .L2258+132
	mov	r1, #16
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2258+136
	mov	r1, #16
	str	r0, [r5, #16]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #20]
	b	.L2210
.L2230:
	ldr	r1, .L2258+140
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2258+144
	strb	r0, [r5, #13]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+148
	str	r0, [r5, #684]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+152
	str	r0, [r5, #688]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+156
	str	r0, [r5, #696]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+160
	str	r0, [r5, #692]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2258+164
	str	r0, [r5, #700]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #704]
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L2231
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2224:
	ldr	r3, .L2258+168
	mov	r0, #1
	ldr	r1, .L2258+172
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2259:
	.align	2
.L2258:
	.word	.LC172
	.word	.LC176
	.word	.LC178
	.word	.LC185
	.word	.LC188
	.word	.LC192
	.word	.LC193
	.word	.LC194
	.word	.LC195
	.word	.LC197
	.word	.LC198
	.word	.LC199
	.word	.LC200
	.word	.LC201
	.word	.LC202
	.word	.LC203
	.word	.LC204
	.word	.LC206
	.word	.LC207
	.word	.LC205
	.word	.LC189
	.word	.LC190
	.word	.LC191
	.word	.LC186
	.word	.LC187
	.word	.LC179
	.word	.LC180
	.word	.LC181
	.word	.LC182
	.word	.LC183
	.word	.LC184
	.word	.LC177
	.word	.LC173
	.word	.LC174
	.word	.LC175
	.word	.LC208
	.word	.LC209
	.word	.LC210
	.word	.LC211
	.word	.LC212
	.word	.LC213
	.word	.LC214
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC196
	UNWIND(.fnend)
	.size	mvc_vui_parameters, .-mvc_vui_parameters
	.align	2
	.global	MVC_SPSEqual
	.type	MVC_SPSEqual, %function
MVC_SPSEqual:
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
	ldreq	ip, .L2295
	movweq	r3, #10458
	beq	.L2292
	cmp	r1, #0
	beq	.L2293
	ldrb	lr, [r1]	@ zero_extendqisi2
	ldrb	r3, [r6]	@ zero_extendqisi2
	ldr	ip, [r6, #736]
	ldr	r2, [r1, #736]
	ldrb	r0, [r6, #1]	@ zero_extendqisi2
	cmp	r3, lr
	cmpeq	ip, r2
	ldrb	r5, [r1, #1]	@ zero_extendqisi2
	ldrb	r2, [r6, #2]	@ zero_extendqisi2
	ldrb	r4, [r1, #2]	@ zero_extendqisi2
	moveq	lr, #1
	movne	lr, #0
	ldr	r3, [r6, #740]
	cmp	r0, r5
	movne	ip, #0
	andeq	ip, lr, #1
	ldr	r5, [r1, #740]
	cmp	r2, r4
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	lr, [r1, #744]
	ldr	r4, [r6, #744]
	cmp	r3, r5
	movne	r2, #0
	andeq	r2, r0, #1
	ldrb	ip, [r1, #27]	@ zero_extendqisi2
	ldrb	r0, [r6, #27]	@ zero_extendqisi2
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r2, #1
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #0
	beq	.L2264
	add	r2, r6, #5
	sub	r0, r1, #404
	str	r2, [fp, #-48]
	add	r2, r1, #5
	add	r9, r1, #748
	sub	r10, r6, #404
	sub	r4, r6, #148
	mov	r8, r6
	str	r6, [fp, #-52]
	mov	r7, #0
	mov	r5, r0
	mov	r6, r2
	str	r1, [fp, #-56]
.L2268:
	ldr	r1, [fp, #-48]
	ldrsb	r0, [r6, #1]!
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-48]
	sxtb	r1, r2
	cmp	r0, r1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, #0
	beq	.L2265
	cmp	r7, #5
	bhi	.L2275
	add	r2, r8, #748
	add	lr, r8, #812
	mov	r1, r9
.L2267:
	ldr	ip, [r2, #4]!
	ldr	r0, [r1, #4]!
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, lr
	bne	.L2267
.L2265:
	add	r7, r7, #1
	add	r10, r10, #256
	cmp	r7, #8
	add	r5, r5, #256
	add	r4, r4, #256
	add	r8, r8, #64
	add	r9, r9, #64
	bne	.L2268
	ldr	r6, [fp, #-52]
	ldr	r1, [fp, #-56]
.L2264:
	ldr	r2, [r1, #2896]
	ldr	ip, [r6, #2900]
	ldr	r0, [r1, #2900]
	ldr	lr, [r6, #2896]
	cmp	ip, r0
	cmpeq	lr, r2
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #0
	and	r3, r3, r2
	beq	.L2270
	cmp	ip, #1
	bne	.L2269
	ldr	r0, [r1, #2908]
	ldr	ip, [r6, #2908]
	ldrb	r2, [r6, #18]	@ zero_extendqisi2
	ldrb	r4, [r1, #18]	@ zero_extendqisi2
	ldr	lr, [r6, #2912]
	cmp	ip, r0
	cmpeq	r2, r4
	ldr	r2, [r1, #2912]
	ldr	r5, [r6, #2916]
	ldr	ip, [r1, #2916]
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
	beq	.L2269
	add	ip, r6, #2912
	add	r0, r1, #2912
	add	ip, ip, #4
	add	r0, r0, #4
	mov	r2, #0
.L2272:
	ldr	r4, [ip, #4]!
	add	r2, r2, #1
	ldr	lr, [r0, #4]!
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r5
	bne	.L2272
.L2269:
	ldrb	lr, [r6, #19]	@ zero_extendqisi2
	ldrb	r0, [r1, #19]	@ zero_extendqisi2
	ldr	r2, [r6, #3944]
	ldr	r4, [r1, #3944]
	ldr	r7, [r6, #3948]
	cmp	lr, r0
	cmpeq	r2, r4
	ldr	r2, [r1, #3948]
	ldr	r5, [r6, #3952]
	ldr	r4, [r1, #3952]
	moveq	ip, #1
	movne	ip, #0
	ldrb	lr, [r1, #20]	@ zero_extendqisi2
	cmp	r7, r2
	movne	r0, #0
	andeq	r0, ip, #1
	ldrb	ip, [r6, #20]	@ zero_extendqisi2
	cmp	r5, r4
	movne	r2, #0
	andeq	r2, r0, #1
	cmp	lr, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	ip, #0
	and	r3, r3, r2
	bne	.L2273
	ldrb	r0, [r6, #21]	@ zero_extendqisi2
	ldrb	r2, [r1, #21]	@ zero_extendqisi2
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L2273:
	ldrb	r2, [r1, #22]	@ zero_extendqisi2
	ldrb	ip, [r6, #23]	@ zero_extendqisi2
	ldrb	r0, [r1, #23]	@ zero_extendqisi2
	ldrb	lr, [r6, #22]	@ zero_extendqisi2
	cmp	r0, ip
	cmpeq	lr, r2
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #0
	and	r3, r3, r2
	bne	.L2294
.L2274:
	ldrb	r0, [r6, #24]	@ zero_extendqisi2
	ldrb	r2, [r1, #24]	@ zero_extendqisi2
	cmp	r0, r2
	movne	r0, #0
	andeq	r0, r3, #1
	eor	r0, r0, #1
	rsb	r0, r0, #0
.L2262:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2294:
	ldr	ip, [r1, #3960]
	ldr	lr, [r6, #3960]
	ldr	r0, [r6, #3956]
	ldr	r2, [r1, #3956]
	ldr	r5, [r6, #3964]
	cmp	lr, ip
	cmpeq	r0, r2
	ldr	r2, [r1, #3964]
	ldr	r4, [r6, #3968]
	ldr	lr, [r1, #3968]
	moveq	ip, #1
	movne	ip, #0
	cmp	r5, r2
	movne	r0, #0
	andeq	r0, ip, #1
	cmp	r4, lr
	movne	r2, #0
	andeq	r2, r0, #1
	and	r3, r3, r2
	b	.L2274
.L2275:
	mov	r1, r5
	mov	r2, r10
.L2266:
	ldr	ip, [r2, #4]!
	ldr	r0, [r1, #4]!
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r4
	bne	.L2266
	b	.L2265
.L2270:
	ldr	r0, [r6, #2904]
	ldr	r2, [r1, #2904]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
	b	.L2269
.L2293:
	ldr	ip, .L2295
	mov	r0, r1
	movw	r3, #10459
.L2292:
	ldr	r2, .L2295+4
	ldr	r1, .L2295+8
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2262
.L2296:
	.align	2
.L2295:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_SPSEqual, .-MVC_SPSEqual
	.global	__aeabi_idiv
	.align	2
	.global	MVC_GetDar
	.type	MVC_GetDar, %function
MVC_GetDar:
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
	cmp	r0, #0
	moveq	r4, r0
	beq	.L2298
	subs	lr, r0, #255
	movne	lr, #1
	cmp	r0, #16
	movle	r4, #0
	andgt	r4, lr, #1
	cmp	r4, #0
	movne	r4, #0
	bne	.L2298
	cmp	r2, #0
	cmpne	r1, #0
	moveq	ip, #1
	movne	ip, #0
	cmp	r0, #255
	movne	ip, #0
	andeq	ip, ip, #1
	cmp	ip, #0
	bne	.L2298
	cmp	r0, #1
	moveq	r4, #5
	beq	.L2298
	cmp	lr, #0
	ldrne	r2, .L2320
	addne	r0, r2, r0, lsl #3
	ldrne	r1, [r0, #100]
	ldrne	r2, [r0, #104]
	mul	r0, r3, r1
	ldr	r3, [fp, #4]
	mul	r1, r3, r2
	mov	r0, r0, asl #10
	bl	__aeabi_idiv
	movw	r3, #2405
	movw	r2, #2262
	cmp	r0, r3
	rsble	r3, r0, #2400
	subgt	r3, r0, #2400
	addle	r3, r3, #6
	subgt	r3, r3, #6
	cmp	r0, r2
	bgt	.L2302
	rsb	r2, r0, #2256
	add	r2, r2, #7
	cmp	r3, r2
	bge	.L2303
.L2313:
	mov	r4, #4
.L2298:
	ldr	r3, .L2320+4
	mov	r2, r4
	ldr	r1, .L2320+8
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2302:
	sub	r2, r0, #2256
	sub	r2, r2, #7
	cmp	r3, r2
	blt	.L2313
.L2303:
	movw	r3, #1819
	cmp	r0, r3
	bgt	.L2304
	rsb	r3, r0, #1808
	add	r3, r3, #12
	cmp	r2, r3
	blt	.L2315
.L2305:
	movw	r2, #1364
	cmp	r0, r2
	rsble	r0, r0, #1360
	subgt	r0, r0, #1360
	addle	r0, r0, #5
	subgt	r0, r0, #5
	cmp	r3, r0
	movlt	r4, #2
	movge	r4, #1
	b	.L2298
.L2304:
	sub	r3, r0, #1808
	sub	r3, r3, #12
	cmp	r2, r3
	bge	.L2305
.L2315:
	mov	r4, #3
	b	.L2298
.L2321:
	.align	2
.L2320:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC215
	UNWIND(.fnend)
	.size	MVC_GetDar, .-MVC_GetDar
	.align	2
	.global	MVC_ProcessSPS
	.type	MVC_ProcessSPS, %function
MVC_ProcessSPS:
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
	subs	r5, r1, #0
	mov	r4, r0
	beq	.L2436
	ldr	r3, [r5, #736]
	cmp	r3, #100
	cmpne	r3, #122
	bic	r1, r3, #16
	sub	r3, r3, #110
	moveq	r2, #1
	movne	r2, #0
	cmp	r1, #128
	orreq	r2, r2, #1
	bics	r3, r3, #8
	orreq	r3, r2, #1
	movne	r3, r2
	cmp	r3, #0
	streqb	r3, [r5, #27]
	moveq	r3, #1
	streq	r3, [r5, #748]
	bne	.L2437
.L2335:
	ldr	r1, .L2451
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #12
	str	r0, [r5, #2896]
	bhi	.L2348
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2348
	ldr	r1, .L2451+4
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r5, #2900]
	bhi	.L2350
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2350
	cmp	r0, #0
	beq	.L2438
	cmp	r0, #1
	beq	.L2439
.L2356:
	ldr	r1, .L2451+8
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #3944]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	ldr	r1, .L2451+12
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #19]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	ldr	r1, .L2451+16
	mov	r0, r4
	bl	mvc_ue_v
	movw	r7, #509
	sub	r3, r0, #1
	str	r0, [r5, #3948]
	cmp	r3, r7
	bhi	.L2361
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2361
	ldr	r1, .L2451+20
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #3952]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	ldr	r1, .L2451+24
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #20]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	cmp	r0, #0
	bne	.L2440
	ldr	r1, .L2451+28
	mov	r0, r4
	bl	mvc_u_1
	ldr	r6, [r5, #3952]
	add	r6, r6, #1
	cmp	r6, #255
	strb	r0, [r5, #21]
	bhi	.L2394
	ldr	r8, [r5, #3948]
	add	r8, r8, #1
	cmp	r6, #1
	cmphi	r8, #3
	movhi	r10, #2
	bhi	.L2365
.L2394:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2437:
	ldr	r1, .L2451+40
	bl	mvc_ue_v
	cmp	r0, #1
	str	r0, [r5, #748]
	bhi	.L2326
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2326
	ldr	r1, .L2451+44
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L2328
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2329
.L2328:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+48
	ldr	r3, [r3, #68]
	blx	r3
.L2329:
	ldr	r1, .L2451+52
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L2330
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2331
.L2330:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+56
	ldr	r3, [r3, #68]
	blx	r3
.L2331:
	ldr	r1, .L2451+60
	mov	r0, r4
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L2332
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2332
	ldr	r1, .L2451+64
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #27]
	cmp	r0, #1
	bne	.L2335
	sub	r8, fp, #72
	add	r10, r5, #5
	add	r7, r5, #2672
	add	r9, r5, #752
	b	.L2341
.L2443:
	ldr	r3, .L2451+68
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2451+32
	ldr	r3, [r3, #52]
	blx	r3
.L2337:
	add	r6, r6, #1
	add	r7, r7, #16
	cmp	r6, #6
	add	r9, r9, #64
	beq	.L2441
.L2341:
	ldr	r1, .L2451+72
	mov	r0, r4
	bl	mvc_u_1
	clz	r1, r6
	mov	r2, #16
	mov	r1, r1, lsr #5
	cmp	r0, #1
	mov	r3, r0
	mov	r0, r7
	str	r3, [r8, #4]!
	strb	r3, [r10, #1]!
	beq	.L2442
	cmp	r6, #0
	cmpne	r6, #3
	beq	.L2443
	ldr	r3, .L2451+32
	mov	r2, #16
	sub	r1, r7, #16
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2337
.L2392:
	cmp	r1, r8
	cmpcs	r0, r6
	bcs	.L2391
	ldr	r3, .L2451+76
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2434
	strh	r1, [fp, #-72]	@ movhi
	mov	r3, #8
	strh	r0, [fp, #-70]	@ movhi
	sub	r2, fp, #76
	strh	r8, [fp, #-76]	@ movhi
	mov	r1, #107
	strh	r6, [fp, #-74]	@ movhi
	ldr	r0, [r4, #120]
	blx	r5
.L2434:
	mvn	r0, #0
.L2427:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2440:
	ldr	r6, [r5, #3952]
	strb	r3, [r5, #21]
	sub	r3, r6, #1
	cmp	r3, r7
	bhi	.L2394
	ldr	r8, [r5, #3948]
	mov	r10, #1
	add	r6, r6, #1
	add	r8, r8, r10
.L2365:
	mul	r6, r6, r10
	mov	r8, r8, asl #4
	mov	r6, r6, asl #4
	mul	r1, r8, r6
	add	r1, r1, r1, lsr #1
	cmp	r1, #100663296
	bhi	.L2444
	ldr	r2, [r5, #740]
	sub	r3, r2, #10
	cmp	r3, #31
	ldrls	pc, [pc, r3, asl #2]
	b	.L2367
.L2369:
	.word	.L2368
	.word	.L2370
	.word	.L2402
	.word	.L2402
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2402
	.word	.L2372
	.word	.L2374
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2374
	.word	.L2375
	.word	.L2376
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2367
	.word	.L2378
	.word	.L2378
.L2438:
	ldr	r1, .L2451+80
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #12
	str	r0, [r5, #2904]
	bhi	.L2353
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2356
.L2353:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+84
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2402:
	mov	r0, #60416
	movt	r0, 13
.L2371:
	bl	__aeabi_uidiv
	ldr	r9, .L2451+32
	ldr	r1, .L2451+88
	ldr	r3, [r9, #68]
	cmp	r0, #16
	movcc	r7, r0
	movcs	r7, #16
	mov	r2, r7
	mov	r0, #21
	blx	r3
	ldr	r2, [r5, #3944]
	cmp	r2, r7
	bhi	.L2379
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2380
.L2379:
	mov	r3, r7
	ldr	r1, .L2451+92
	mov	r0, #0
	ldr	ip, [r9, #68]
	blx	ip
	ldr	r3, [r5, #3944]
	cmp	r3, #16
	bhi	.L2431
	cmp	r7, r3
	movcc	r7, r3
.L2431:
	str	r7, [r5, #3944]
.L2380:
	ldr	r1, .L2451+96
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #22]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	ldr	r1, .L2451+100
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #23]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	cmp	r0, #0
	bne	.L2445
.L2382:
	mov	r2, r8, lsr #1
	mov	r3, r6, lsr #1
	str	r8, [r5, #3976]
	str	r6, [r5, #3980]
	str	r2, [r5, #3984]
	str	r3, [r5, #3988]
.L2384:
	ldr	r1, .L2451+104
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r3, r0
	strb	r3, [r5, #24]
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2434
	cmp	r3, #0
	mov	r2, #2
	str	r2, [r5, #68]
	bne	.L2446
	mov	r0, r3
	strb	r3, [r5, #43]
	mov	r3, #5
	str	r3, [r5, #56]
.L2387:
	ldr	r2, [r5, #48]
	mov	r3, r8
	ldr	r1, [r5, #44]
	str	r6, [sp]
	bl	MVC_GetDar
	ldr	r3, [r5, #3944]
	cmp	r3, #0
	str	r0, [r5, #52]
	beq	.L2390
	cmp	r7, r3
	movcs	r7, r3
.L2390:
	ldr	r3, [r4, #224]
	cmp	r7, #16
	movcs	r7, #16
	ldr	r2, [r3, #28]
	cmp	r2, #25
	beq	.L2447
.L2391:
	cmp	r6, #1920
	bcc	.L2393
	cmp	r7, #4
	movcs	r7, #4
.L2393:
	add	r7, r7, #1
	mov	r0, #0
	str	r7, [r5, #3972]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2378:
	mov	r0, #12582912
	b	.L2371
.L2374:
	mov	r0, #30208
	movt	r0, 47
	b	.L2371
.L2441:
	sub	r8, fp, #88
	add	r10, r5, #11
	add	r7, r5, #2768
	add	r9, r5, #1136
	mov	r6, #0
.L2346:
	ldr	r1, .L2451+72
	mov	r0, r4
	bl	mvc_u_1
	mov	r2, #64
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r7
	str	r3, [r8, #4]!
	strb	r3, [r10, #1]!
	beq	.L2448
	ldr	r1, .L2451+108
	cmp	r6, #0
	ldr	r3, .L2451+32
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L2343:
	add	r6, r6, #1
	add	r7, r7, #64
	cmp	r6, #2
	add	r9, r9, #256
	bne	.L2346
	b	.L2335
.L2442:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r7
	mov	r1, r9
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2337
	ldr	r1, .L2451+68
	mov	r2, #16
	ldr	r3, .L2451+32
	cmp	r6, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r7
	blx	r3
	b	.L2337
.L2326:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+112
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2348:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+116
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2445:
	ldr	r1, .L2451+120
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2451+124
	str	r0, [r5, #3956]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2451+128
	str	r0, [r5, #3960]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2451+132
	str	r0, [r5, #3964]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r5, #3964]
	ldr	r2, [r5, #3956]
	mov	r1, r10, asl #1
	ldr	ip, [r5, #3960]
	mov	r3, r3, asl #1
	mov	r2, r2, asl #1
	mul	r3, r10, r3
	rsb	lr, r2, r8
	sub	ip, lr, ip, asl #1
	rsb	lr, r3, r6
	str	r0, [r5, #3968]
	mls	r0, r0, r1, lr
	cmp	ip, #0
	cmpgt	r0, #0
	ble	.L2382
	add	r2, r2, ip, lsr #1
	add	r3, r3, r0, lsr #1
	str	r2, [r5, #3984]
	str	r3, [r5, #3988]
	str	ip, [r5, #3976]
	str	r0, [r5, #3980]
	b	.L2384
.L2446:
	add	r1, r5, #28
	mov	r0, r4
	bl	mvc_vui_parameters
	cmp	r0, #0
	bne	.L2433
	ldrb	r3, [r5, #40]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2433
	ldr	r2, [r5, #732]
	clz	r3, r2
	mov	r3, r3, lsr #5
	cmp	r7, r2
	orrcc	r3, r3, #1
	cmp	r3, #0
	bne	.L2449
	ldr	r3, [r5, #3944]
	ldrb	r0, [r5, #43]	@ zero_extendqisi2
	cmp	r2, r3
	movcs	r7, r2
	movcc	r7, r3
	b	.L2387
.L2449:
	ldr	r9, [r9, #68]
	mov	r3, r7
	ldr	r1, .L2451+136
	mov	r0, #1
	blx	r9
.L2433:
	ldrb	r0, [r5, #43]	@ zero_extendqisi2
	b	.L2387
.L2447:
	ldr	r2, [r3, #776]
	cmp	r2, #0
	bne	.L2391
	ldr	r2, [r3, #760]
	ldr	r1, [r3, #736]
	cmp	r7, r2
	ldr	r0, [r3, #740]
	bls	.L2392
	ldr	r3, .L2451+76
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2434
	str	r2, [fp, #-72]
	mov	r3, #8
	str	r7, [fp, #-76]
	sub	r2, fp, #76
	ldr	r0, [r4, #120]
	mov	r1, #106
	blx	r5
	mvn	r0, #0
	b	.L2427
.L2332:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+140
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2439:
	ldr	r1, .L2451+144
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #18]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	ldr	r1, .L2451+148
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r5, #2908]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	ldr	r1, .L2451+152
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r5, #2912]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2434
	ldr	r1, .L2451+156
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #255
	str	r0, [r5, #2916]
	bhi	.L2358
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2358
	cmp	r0, #0
	addne	r7, r5, #2912
	addne	r7, r7, #4
	bne	.L2360
	b	.L2356
.L2450:
	ldr	r3, [r5, #2916]
	cmp	r3, r6
	bls	.L2356
.L2360:
	ldr	r1, .L2451+160
	mov	r0, r4
	bl	mvc_se_v
	add	r6, r6, #1
	str	r0, [r7, #4]!
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2450
	b	.L2434
.L2361:
	ldr	r3, .L2451+32
	mov	r2, r0
	ldr	r1, .L2451+164
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2375:
	mov	r0, #30720
	movt	r0, 105
	b	.L2371
.L2372:
	mov	r0, #55296
	movt	r0, 27
	b	.L2371
.L2376:
	mov	r0, #7864320
	b	.L2371
.L2370:
	mov	r0, #17920
	movt	r0, 5
	b	.L2371
.L2368:
	mov	r0, #20992
	movt	r0, 2
	b	.L2371
.L2367:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+168
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2358:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+172
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2448:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r7
	mov	r1, r9
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2343
	ldr	r1, .L2451+108
	mov	r2, #64
	ldr	r3, .L2451+32
	cmp	r6, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r7
	blx	r3
	b	.L2343
.L2350:
	ldr	r3, .L2451+32
	mov	r0, #1
	ldr	r1, .L2451+176
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2444:
	ldr	r3, .L2451+32
	mov	r0, #0
	ldr	r1, .L2451+180
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2427
.L2436:
	ldr	ip, .L2451+32
	mov	r0, r5
	movw	r3, #10648
	ldr	r2, .L2451+184
	ldr	r1, .L2451+188
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2427
.L2452:
	.align	2
.L2451:
	.word	.LC225
	.word	.LC227
	.word	.LC230
	.word	.LC238
	.word	.LC239
	.word	.LC241
	.word	.LC242
	.word	.LC256
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC243
	.word	.LC216
	.word	.LC218
	.word	.LC219
	.word	.LC220
	.word	.LC221
	.word	.LC222
	.word	.LC224
	.word	.LANCHOR1
	.word	.LC164
	.word	g_event_report
	.word	.LC229
	.word	.LC231
	.word	.LC246
	.word	.LC247
	.word	.LC248
	.word	.LC249
	.word	.LC254
	.word	.LANCHOR1+32
	.word	.LC217
	.word	.LC226
	.word	.LC250
	.word	.LC251
	.word	.LC252
	.word	.LC253
	.word	.LC255
	.word	.LC223
	.word	.LC232
	.word	.LC233
	.word	.LC234
	.word	.LC235
	.word	.LC237
	.word	.LC240
	.word	.LC245
	.word	.LC236
	.word	.LC228
	.word	.LC244
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_ProcessSPS, .-MVC_ProcessSPS
	.align	2
	.global	MVC_DecSPS
	.type	MVC_DecSPS, %function
MVC_DecSPS:
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
	ldr	r2, .L2498
	mov	r1, #8
	mov	r4, r0
	bl	mvc_u_v
	ldr	r1, .L2498+4
	mov	r10, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2498+8
	mov	r9, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2498+12
	mov	r8, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2498+16
	str	r0, [fp, #-56]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2498+20
	str	r0, [fp, #-60]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2498+24
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r2, .L2498+28
	mov	r1, #2
	str	r0, [fp, #-68]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2498+32
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2498+36
	mov	r5, r0
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r6, r0
	bne	.L2491
	ldr	r3, [r4, #36]
	sub	r3, r3, #1
	cmp	r0, r3
	bhi	.L2493
	cmp	r10, #100
	mov	r7, r10
	beq	.L2459
	bhi	.L2460
	cmp	r10, #77
	beq	.L2459
	cmp	r10, #88
	beq	.L2461
	cmp	r10, #66
	bne	.L2458
	ldr	r3, .L2498+40
	mov	r0, #1
	ldr	r1, .L2498+44
	ldr	r3, [r3, #68]
	blx	r3
.L2459:
	cmp	r5, #9
	mov	r2, r5
	bls	.L2490
.L2496:
	cmp	r5, #41
	bhi	.L2490
.L2465:
	movw	r3, #3992
	ldr	r1, [r4, #248]
	mul	r5, r3, r6
	add	r1, r1, r5
	ldrb	r10, [r1, #25]	@ zero_extendqisi2
	cmp	r10, #0
	beq	.L2466
	ldr	r10, .L2498+48
	mov	r0, r4
	str	r3, [fp, #-72]
	ldrb	r3, [fp, #-56]	@ zero_extendqisi2
	add	r1, r10, #2240
	str	r7, [r10, #2976]
	strb	r9, [r10, #2240]
	strb	r3, [r10, #2242]
	ldrb	r3, [fp, #-60]	@ zero_extendqisi2
	strb	r8, [r10, #2241]
	str	r2, [r10, #2980]
	strb	r3, [r10, #2243]
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	str	r6, [r10, #2984]
	strb	r3, [r10, #2244]
	ldrb	r3, [fp, #-68]	@ zero_extendqisi2
	strb	r3, [r10, #2245]
	bl	MVC_ProcessSPS
	ldr	r3, [fp, #-72]
	subs	r7, r0, #0
	bne	.L2494
	ldr	r1, [r4, #248]
	add	r0, r10, #2240
	str	r3, [fp, #-56]
	add	r1, r1, r5
	bl	MVC_SPSEqual
	ldr	r3, [fp, #-56]
	cmp	r0, #0
	bne	.L2495
.L2455:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2460:
	cmp	r10, #122
	beq	.L2463
	cmp	r10, #144
	beq	.L2463
	cmp	r10, #110
	beq	.L2463
.L2458:
	ldr	r3, .L2498+40
	mov	r2, r10
	ldr	r1, .L2498+52
	mov	r0, #1
	mov	r7, #100
	ldr	r3, [r3, #68]
	blx	r3
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2496
.L2490:
	ldr	ip, .L2498+40
	mov	r3, #41
	ldr	r1, .L2498+56
	mov	r0, #1
	ldr	r5, [ip, #68]
	blx	r5
	mov	r2, #41
	b	.L2465
.L2466:
	str	r7, [r1, #736]
	mov	r0, r4
	ldr	r3, [r4, #248]
	ldrb	r1, [fp, #-56]	@ zero_extendqisi2
	strb	r9, [r3, r5]
	ldr	r3, [r4, #248]
	add	r3, r3, r5
	strb	r8, [r3, #1]
	ldr	r3, [r4, #248]
	add	r3, r3, r5
	strb	r1, [r3, #2]
	ldr	r3, [r4, #248]
	ldrb	r1, [fp, #-60]	@ zero_extendqisi2
	add	r3, r3, r5
	strb	r1, [r3, #3]
	ldr	r3, [r4, #248]
	ldrb	r1, [fp, #-64]	@ zero_extendqisi2
	add	r3, r3, r5
	strb	r1, [r3, #4]
	ldr	r3, [r4, #248]
	ldrb	r1, [fp, #-68]	@ zero_extendqisi2
	add	r3, r3, r5
	strb	r1, [r3, #5]
	ldr	r3, [r4, #248]
	add	r3, r3, r5
	str	r2, [r3, #740]
	ldr	r3, [r4, #248]
	add	r3, r3, r5
	str	r6, [r3, #744]
	ldr	r1, [r4, #248]
	add	r1, r1, r5
	bl	MVC_ProcessSPS
	cmp	r0, #0
	bne	.L2497
	ldr	r3, [r4, #248]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #26]
	ldr	r3, [r4, #248]
	add	r5, r3, r5
	strb	r2, [r5, #25]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2493:
	ldr	r3, .L2498+40
	mov	r0, #1
	ldr	r1, .L2498+60
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r2, [r4, #36]
	sub	r3, r2, #1
	cmp	r6, r3
	bls	.L2491
	ldr	r3, .L2498+64
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2491
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r6, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r4, #120]
	mov	r1, #109
	blx	r5
.L2491:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2463:
	ldr	r3, .L2498+40
	mov	r0, #1
	ldr	r1, .L2498+68
	ldr	r3, [r3, #68]
	blx	r3
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2496
	b	.L2490
.L2461:
	ldr	r3, .L2498+40
	mov	r0, #1
	ldr	r1, .L2498+72
	ldr	r3, [r3, #68]
	blx	r3
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2496
	b	.L2490
.L2495:
	ldr	ip, .L2498+40
	mov	r2, r3
	ldr	r0, [r4, #248]
	mov	r3, #1
	add	r1, r10, #2240
	strb	r3, [r10, #2266]
	add	r0, r0, r5
	ldr	r4, [ip, #56]
	strb	r3, [r10, #2265]
	blx	r4
	mov	r0, r7
	b	.L2455
.L2494:
	ldr	ip, .L2498+40
	mov	r3, r6
	movw	r2, #11192
	ldr	r1, .L2498+76
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2455
.L2497:
	ldr	ip, .L2498+40
	mov	r3, r6
	movw	r2, #11219
	ldr	r1, .L2498+76
	mov	r0, #1
	ldr	r6, [ip, #68]
	blx	r6
	ldr	r3, [r4, #248]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r5
	strb	r2, [r3, #26]
	ldr	r3, [r4, #248]
	add	r5, r3, r5
	strb	r10, [r5, #25]
	b	.L2455
.L2499:
	.align	2
.L2498:
	.word	.LC257
	.word	.LC258
	.word	.LC259
	.word	.LC260
	.word	.LC261
	.word	.LC262
	.word	.LC263
	.word	.LC264
	.word	.LC265
	.word	.LC266
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC267
	.word	.LANCHOR2
	.word	.LC270
	.word	.LC271
	.word	.LC170
	.word	g_event_report
	.word	.LC269
	.word	.LC268
	.word	.LC272
	UNWIND(.fnend)
	.size	MVC_DecSPS, .-MVC_DecSPS
	.align	2
	.global	MVC_FreeMvcExtMem
	.type	MVC_FreeMvcExtMem, %function
MVC_FreeMvcExtMem:
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
	.size	MVC_FreeMvcExtMem, .-MVC_FreeMvcExtMem
	.align	2
	.global	MVC_FreeMvcVuiExtMem
	.type	MVC_FreeMvcVuiExtMem, %function
MVC_FreeMvcVuiExtMem:
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
	.size	MVC_FreeMvcVuiExtMem, .-MVC_FreeMvcVuiExtMem
	.align	2
	.global	MVC_ProcessSUBSPSMvcExt
	.type	MVC_ProcessSUBSPSMvcExt, %function
MVC_ProcessSUBSPSMvcExt:
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
	subs	r5, r1, #0
	mov	r4, r0
	beq	.L2565
	ldr	r1, .L2566
	bl	mvc_ue_v
	cmp	r0, #1
	str	r0, [r5, #4]
	bhi	.L2505
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	addeq	r7, r5, #4
	bne	.L2505
.L2507:
	ldr	r1, .L2566+4
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r7, #4]!
	ldr	r3, [r5, #4]
	cmp	r3, r6
	bcs	.L2507
	cmp	r3, #0
	mov	r2, #0
	str	r2, [r5, #16]
	str	r2, [r5, #24]
	beq	.L2508
	add	r8, r5, #16
	mov	r7, #1
.L2518:
	ldr	r1, .L2566+8
	mov	r0, r4
	bl	mvc_ue_v
	add	r9, r8, #4
	str	r0, [r8, #4]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcs	r3, #15
	cmp	r0, r3
	bhi	.L2509
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2509
	cmp	r0, #0
	addne	r10, r8, #16
	beq	.L2514
.L2513:
	ldr	r1, .L2566+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r10, #4]!
	ldr	r3, [r9]
	cmp	r3, r6
	bhi	.L2513
.L2514:
	ldr	r1, .L2566+16
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #8]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcc	r2, r3
	movcs	r2, #15
	cmp	r0, r2
	bhi	.L2511
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2511
	cmp	r0, #0
	addne	r8, r8, #24
	beq	.L2516
.L2517:
	ldr	r1, .L2566+20
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r8, #4]!
	ldr	r3, [r9, #8]
	cmp	r3, r6
	bhi	.L2517
	ldr	r3, [r5, #4]
.L2516:
	add	r7, r7, #1
	mov	r8, r9
	cmp	r7, r3
	bls	.L2518
	cmp	r3, #0
	mov	r3, #0
	addne	r8, r5, #48
	str	r3, [r5, #48]
	str	r3, [r5, #56]
	movne	r7, #1
	beq	.L2532
.L2531:
	ldr	r1, .L2566+24
	mov	r0, r4
	bl	mvc_ue_v
	add	r9, r8, #4
	str	r0, [r8, #4]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcs	r3, #15
	cmp	r0, r3
	bhi	.L2522
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2522
	cmp	r0, #0
	addne	r10, r8, #16
	beq	.L2527
.L2526:
	ldr	r1, .L2566+28
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r10, #4]!
	ldr	r3, [r9]
	cmp	r3, r6
	bhi	.L2526
.L2527:
	ldr	r1, .L2566+32
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #8]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcc	r2, r3
	movcs	r2, #15
	cmp	r0, r2
	bhi	.L2524
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2524
	cmp	r0, #0
	addne	r8, r8, #24
	beq	.L2529
.L2530:
	ldr	r1, .L2566+36
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r8, #4]!
	ldr	r3, [r9, #8]
	cmp	r3, r6
	bhi	.L2530
	ldr	r3, [r5, #4]
.L2529:
	add	r7, r7, #1
	mov	r8, r9
	cmp	r7, r3
	bls	.L2531
.L2532:
	ldr	r1, .L2566+40
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r0, #1
	str	r0, [r5, #80]
	cmp	r3, #16
	str	r3, [fp, #-60]
	bhi	.L2520
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2520
	ldr	r2, [fp, #-60]
	cmp	r2, #0
	beq	.L2537
	add	r2, r5, #8384
	add	r1, r5, #80
	add	r2, r2, #16
	str	r1, [fp, #-72]
	str	r2, [fp, #-68]
	add	r2, r5, #212
	str	r3, [fp, #-56]
	str	r2, [fp, #-64]
	str	r5, [fp, #-76]
.L2536:
	ldr	r2, .L2566+44
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-72]
	ldr	r1, .L2566+48
	str	r0, [r3, #4]!
	mov	r0, r4
	mov	r5, r3
	str	r3, [fp, #-72]
	bl	mvc_ue_v
	add	r3, r0, #1
	str	r0, [r5, #64]
	str	r3, [fp, #-52]
	mov	r2, r3
	cmp	r2, #64
	bhi	.L2534
	ldrb	r7, [r4, #10]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L2534
	cmp	r2, #0
	beq	.L2544
	ldr	r3, [fp, #-64]
	movw	r10, #8188
	ldr	r2, [fp, #-68]
	movt	r10, 4
	add	r10, r3, r10
	mov	r8, r3
	str	r2, [fp, #-48]
.L2543:
	ldr	r2, .L2566+52
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2566+56
	str	r0, [r8], #4
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r0, #1
	str	r0, [r8, #4092]
	cmp	r6, #64
	bhi	.L2538
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2538
	cmp	r6, #0
	movne	r5, r3
	ldrne	r9, [fp, #-48]
	beq	.L2542
.L2539:
	ldr	r1, .L2566+60
	mov	r0, r4
	bl	mvc_ue_v
	add	r5, r5, #1
	cmp	r6, r5
	str	r0, [r9, #4]!
	bne	.L2539
.L2542:
	ldr	r1, .L2566+64
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #1024
	str	r0, [r10, #4]!
	bcs	.L2540
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2540
	ldr	r3, [fp, #-48]
	add	r7, r7, #1
	add	r3, r3, #256
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	cmp	r3, r7
	bne	.L2543
.L2544:
	ldr	r2, [fp, #-64]
	ldr	r3, [fp, #-56]
	add	r2, r2, #256
	str	r2, [fp, #-64]
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r2, r3
	ldr	r3, [fp, #-68]
	add	r3, r3, #16384
	str	r3, [fp, #-68]
	bne	.L2536
.L2537:
	mov	r0, #0
	b	.L2556
.L2509:
	ldr	r3, .L2566+68
	mov	r2, r0
	ldr	r1, .L2566+72
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L2556:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2511:
	ldr	r3, .L2566+68
	mov	r2, r0
	ldr	r1, .L2566+76
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2524:
	ldr	r3, .L2566+68
	mov	r2, r0
	ldr	r1, .L2566+80
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2556
.L2522:
	ldr	r3, .L2566+68
	mov	r2, r0
	ldr	r1, .L2566+84
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2556
.L2505:
	ldr	r3, .L2566+68
	mov	r2, r0
	ldr	r1, .L2566+88
	movw	r0, #65534
.L2564:
	str	r0, [r5, #80]
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2556
.L2508:
	str	r3, [r5, #48]
	str	r3, [r5, #56]
	b	.L2532
.L2540:
	ldr	r3, .L2566+68
	mov	r2, r0
	ldr	r1, .L2566+92
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2556
.L2538:
	ldr	r3, [fp, #-56]
	movw	ip, #65534
	ldr	r5, [fp, #-76]
	mov	r2, r6
	ldr	r1, .L2566+68
	mov	r0, #1
	add	r3, r7, r3, lsl #6
	add	r3, r3, #1072
	add	r3, r3, #4
	ldr	r4, [r1, #68]
	ldr	r1, .L2566+96
	add	r3, r5, r3, lsl #2
	str	ip, [r3, #4]
	blx	r4
	mvn	r0, #0
	b	.L2556
.L2565:
	ldr	ip, .L2566+68
	mov	r0, r5
	movw	r3, #11282
	ldr	r2, .L2566+100
	ldr	r1, .L2566+104
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L2556
.L2520:
	ldr	r3, .L2566+68
	movw	r0, #65534
	ldr	r2, [fp, #-60]
	ldr	r1, .L2566+108
	b	.L2564
.L2534:
	ldr	r2, [fp, #-56]
	movw	ip, #65534
	ldr	r5, [fp, #-76]
	mov	r0, #1
	ldr	r3, .L2566+68
	add	r5, r5, r2, lsl #2
	ldr	r1, .L2566+112
	ldr	r2, [fp, #-52]
	str	ip, [r5, #148]
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2556
.L2567:
	.align	2
.L2566:
	.word	.LC273
	.word	.LC275
	.word	.LC276
	.word	.LC279
	.word	.LC277
	.word	.LC281
	.word	.LC283
	.word	.LC286
	.word	.LC284
	.word	.LC288
	.word	.LC282
	.word	.LC290
	.word	.LC291
	.word	.LC293
	.word	.LC294
	.word	.LC297
	.word	.LC295
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC278
	.word	.LC280
	.word	.LC287
	.word	.LC285
	.word	.LC274
	.word	.LC298
	.word	.LC296
	.word	.LC13
	.word	.LC14
	.word	.LC289
	.word	.LC292
	UNWIND(.fnend)
	.size	MVC_ProcessSUBSPSMvcExt, .-MVC_ProcessSUBSPSMvcExt
	.align	2
	.global	MVC_ProcessSUBSPSMvcVuiExt
	.type	MVC_ProcessSUBSPSMvcVuiExt, %function
MVC_ProcessSUBSPSMvcVuiExt:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
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
	mov	r5, r1
	ldr	r1, .L2602
	mov	r4, r0
	bl	mvc_ue_v
	mov	r3, #0
	adds	r6, r0, #1
	adc	r7, r3, #0
	add	r3, r5, #278528
	cmp	r7, #0
	strd	r6, [fp, #-108]
	cmpeq	r6, #64
	str	r0, [r3, #560]
	bhi	.L2569
	orrs	r2, r6, r7
	beq	.L2588
	add	r1, r5, #294912
	add	r9, r5, #315392
	add	r9, r9, #856
	movw	r2, #16687
	mov	ip, r1
	movw	r7, #34136
	movw	r1, #16751
	movw	r0, #33844
	mov	r8, r5
	movt	r2, 4
	add	ip, ip, #820
	add	r2, r5, r2
	movt	r7, 4
	str	r2, [fp, #-96]
	movt	r1, 4
	add	r7, r5, r7
	add	r2, r5, r1
	movt	r0, 4
	str	r2, [fp, #-88]
	add	r2, r3, #111
	str	ip, [fp, #-68]
	str	r2, [fp, #-80]
	add	r2, r5, r0
	str	r7, [fp, #-48]
	str	r2, [fp, #-72]
	add	r2, r3, #560
	str	r2, [fp, #-84]
	add	r2, r3, #176
	str	r2, [fp, #-64]
	add	r2, r3, #432
	str	r2, [fp, #-52]
	add	r2, r3, #496
	str	r2, [fp, #-56]
	add	r2, r3, #240
	add	r3, r3, #816
	str	r2, [fp, #-76]
	str	r3, [fp, #-60]
	mov	r3, #0
	str	r3, [fp, #-92]
.L2587:
	ldr	r2, .L2602+4
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-80]
	ldr	r1, .L2602+8
	strb	r0, [r3, #1]!
	mov	r0, r4
	str	r3, [fp, #-80]
	bl	mvc_ue_v
	ldr	r3, [fp, #-84]
	adds	r5, r0, #1
	str	r0, [r3, #4]!
	str	r3, [fp, #-84]
	beq	.L2575
	ldr	r10, [fp, #-60]
	mov	r6, #0
	ldr	r7, [fp, #-48]
.L2572:
	ldr	r1, .L2602+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	cmp	r5, r6
	str	r0, [r10, #4]!
	bne	.L2572
	str	r7, [fp, #-48]
.L2575:
	ldr	r1, .L2602+16
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-88]
	uxtb	r0, r0
	strb	r0, [r3, #1]!
	cmp	r0, #0
	str	r3, [fp, #-88]
	bne	.L2600
.L2574:
	ldr	r1, .L2602+20
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-52]
	uxtb	r0, r0
	strb	r0, [r3]
	cmp	r0, #0
	beq	.L2576
	ldr	r1, .L2602+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r5, [fp, #-48]
	ldr	r2, .L2602+28
	mov	r1, #4
	str	r0, [r5]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34132
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2602+32
	mov	r1, #4
	strb	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34133
	movt	r3, 4
	add	r3, r8, r3
	strb	r0, [r3]
	ldr	r3, [r5]
	cmp	r3, #31
	bhi	.L2581
	ldrb	r5, [r4, #10]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L2581
	ldr	r7, [fp, #-48]
	movw	r10, #34099
	movt	r10, 4
	add	r10, r8, r10
	mov	r6, r7
.L2579:
	ldr	r1, .L2602+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2602+40
	add	r5, r5, #1
	str	r0, [r6, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2602+44
	str	r0, [r6, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r10, #1]!
	ldr	r3, [r7]
	cmp	r3, r5
	bcs	.L2579
	ldr	r2, .L2602+48
	mov	r1, #5
	mov	r0, r4
	str	r7, [fp, #-48]
	bl	mvc_u_v
	movw	r3, #34396
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2602+52
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	add	r3, r8, #294912
	ldr	r2, .L2602+56
	mov	r1, #5
	str	r0, [r3, #1632]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34404
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2602+60
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34408
	movt	r3, 4
	add	r3, r8, r3
	str	r0, [r3]
.L2576:
	ldr	r1, .L2602+64
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-56]
	uxtb	r0, r0
	strb	r0, [r3]
	cmp	r0, #0
	bne	.L2601
	ldr	r3, [fp, #-52]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2586
.L2585:
	ldr	r1, .L2602+68
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-92]
	ldrd	r6, [fp, #-108]
	add	r8, r8, #312
	add	r1, r3, #1
	mov	r3, #0
	cmp	r7, r3
	ldr	r3, [fp, #-52]
	mov	r2, r1
	str	r1, [fp, #-92]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-56]
	cmpeq	r6, r2
	ldr	r1, [fp, #-64]
	add	r9, r9, #312
	add	r3, r3, #1
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-48]
	add	r1, r1, #1
	str	r1, [fp, #-64]
	add	r3, r3, #312
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-68]
	add	r3, r3, #4
	str	r3, [fp, #-68]
	ldr	r3, [fp, #-72]
	add	r3, r3, #4
	str	r3, [fp, #-72]
	ldr	r3, [fp, #-76]
	add	r3, r3, #1
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-60]
	add	r3, r3, #256
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-96]
	strb	r0, [r3, #1]!
	str	r3, [fp, #-96]
	bhi	.L2587
.L2588:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2601:
	ldr	r1, .L2602+24
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r8, #315392
	ldr	r2, .L2602+28
	mov	r1, #4
	mov	r5, r3
	str	r3, [fp, #-100]
	str	r0, [r9]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2602+32
	mov	r1, #4
	strb	r0, [r5, #852]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #54101
	movt	r3, 4
	add	r3, r8, r3
	strb	r0, [r3]
	ldr	r3, [r9]
	cmp	r3, #31
	bhi	.L2581
	ldrb	r5, [r4, #10]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L2581
	movw	r10, #54067
	ldr	r7, [fp, #-48]
	movt	r10, 4
	add	r10, r8, r10
	mov	r6, r9
.L2583:
	ldr	r1, .L2602+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2602+40
	add	r5, r5, #1
	str	r0, [r6, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2602+44
	str	r0, [r6, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r10, #1]!
	ldr	r3, [r9]
	cmp	r3, r5
	bcs	.L2583
	ldr	r2, .L2602+48
	mov	r1, #5
	mov	r0, r4
	str	r7, [fp, #-48]
	bl	mvc_u_v
	movw	r3, #54364
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2602+52
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-100]
	ldr	r2, .L2602+56
	mov	r1, #5
	str	r0, [r3, #1120]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #54372
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2602+60
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #54376
	movt	r3, 4
	add	r3, r8, r3
	str	r0, [r3]
	ldr	r3, [fp, #-52]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2586
	ldr	r3, [fp, #-56]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2585
.L2586:
	ldr	r1, .L2602+72
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-64]
	strb	r0, [r3]
	b	.L2585
.L2600:
	ldr	r2, .L2602+76
	mov	r1, #32
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-68]
	ldr	r2, .L2602+80
	mov	r1, #32
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-72]
	ldr	r1, .L2602+84
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-76]
	strb	r0, [r3]
	b	.L2574
.L2581:
	ldr	r3, .L2602+88
	mov	r0, #1
	ldr	r1, .L2602+92
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
.L2598:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2569:
	ldr	r3, .L2602+88
	mov	r0, #1
	ldr	r1, .L2602+96
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2598
.L2603:
	.align	2
.L2602:
	.word	.LC299
	.word	.LC301
	.word	.LC302
	.word	.LC304
	.word	.LC303
	.word	.LC308
	.word	.LC309
	.word	.LC310
	.word	.LC311
	.word	.LC312
	.word	.LC313
	.word	.LC314
	.word	.LC315
	.word	.LC316
	.word	.LC317
	.word	.LC318
	.word	.LC319
	.word	.LC321
	.word	.LC320
	.word	.LC305
	.word	.LC306
	.word	.LC307
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC196
	.word	.LC300
	UNWIND(.fnend)
	.size	MVC_ProcessSUBSPSMvcVuiExt, .-MVC_ProcessSUBSPSMvcVuiExt
	.align	2
	.global	MVC_DecSubSPS
	.type	MVC_DecSubSPS, %function
MVC_DecSubSPS:
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
	ldr	r2, .L2632
	mov	r1, #8
	mov	r4, r0
	bl	mvc_u_v
	ldr	r1, .L2632+4
	mov	r7, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2632+8
	str	r0, [fp, #-48]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2632+12
	mov	r9, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2632+16
	str	r0, [fp, #-52]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2632+20
	str	r0, [fp, #-56]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2632+24
	str	r0, [fp, #-60]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r2, .L2632+28
	mov	r1, #2
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2632+32
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2632+36
	mov	r8, r0
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r5, r0
	bne	.L2617
	cmp	r0, #31
	bhi	.L2627
	sub	r3, r7, #66
	cmp	r3, #78
	ldrls	pc, [pc, r3, asl #2]
	b	.L2607
.L2609:
	.word	.L2608
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2610
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2611
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2610
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2612
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2610
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2612
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2610
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2607
	.word	.L2612
.L2608:
	ldr	r3, .L2632+40
	mov	r0, #1
	ldr	r1, .L2632+44
	ldr	r3, [r3, #68]
	blx	r3
.L2610:
	cmp	r8, #41
	bhi	.L2628
.L2613:
	movw	r3, #8500
	movw	ip, #26248
	movt	r3, 5
	movt	ip, 4
	mul	r3, r3, r5
	mov	r0, r4
	add	r10, r4, r3
	add	r6, r10, #286720
	add	ip, r10, ip
	str	r3, [fp, #-68]
	add	r1, r6, #932
	ldrb	r3, [fp, #-48]	@ zero_extendqisi2
	str	r8, [r6, #1672]
	str	r7, [r6, #1668]
	strb	r3, [r6, #932]
	ldrb	r3, [fp, #-52]	@ zero_extendqisi2
	strb	r9, [r6, #933]
	strb	r3, [r6, #934]
	ldrb	r3, [fp, #-56]	@ zero_extendqisi2
	strb	r3, [r6, #935]
	ldrb	r3, [fp, #-60]	@ zero_extendqisi2
	strb	r3, [r6, #936]
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	strb	r3, [r6, #937]
	str	r5, [ip, #4]
	bl	MVC_ProcessSPS
	ldr	r3, [fp, #-68]
	subs	r8, r0, #0
	bne	.L2629
	cmp	r7, #118
	cmpne	r7, #128
	mov	r9, #1
	strb	r9, [r6, #957]
	beq	.L2630
.L2615:
	movw	r3, #8500
	mov	r2, #1
	movt	r3, 5
	mla	r4, r3, r5, r4
	add	r4, r4, #12992
	strb	r2, [r4, #12]
.L2605:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2628:
	ldr	r3, .L2632+40
	mov	r2, r8
	ldr	r1, .L2632+48
	mov	r0, #1
	mov	r8, #41
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2613
.L2630:
	ldr	r1, .L2632+52
	mov	r0, r4
	str	r3, [fp, #-48]
	bl	mvc_u_1
	ldr	r3, [fp, #-48]
	add	r10, r10, #12992
	add	r10, r10, #8
	add	r3, r4, r3
	add	r7, r3, #12992
	add	r7, r7, #12
	mov	r1, r7
	strb	r0, [r10, #5]
	mov	r0, r4
	bl	MVC_ProcessSUBSPSMvcExt
	cmp	r0, #0
	bne	.L2631
	ldr	r1, .L2632+56
	mov	r0, r4
	bl	mvc_u_1
	cmp	r0, #0
	str	r0, [r6, #928]
	beq	.L2615
	mov	r1, r7
	mov	r0, r4
	bl	MVC_ProcessSUBSPSMvcVuiExt
	cmp	r0, #0
	beq	.L2615
	ldr	r3, .L2632+40
	mov	r0, r9
	ldr	r1, .L2632+60
	ldr	r3, [r3, #68]
	blx	r3
	strb	r8, [r10, #4]
	mvn	r8, #0
	b	.L2605
.L2612:
	ldr	r3, .L2632+40
	mov	r0, #1
	ldr	r1, .L2632+64
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2610
.L2611:
	ldr	r3, .L2632+40
	mov	r0, #1
	ldr	r1, .L2632+68
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2610
.L2607:
	ldr	r3, .L2632+40
	mov	r2, r7
	ldr	r1, .L2632+72
	mov	r0, #1
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2617:
	mvn	r8, #0
	b	.L2605
.L2627:
	ldr	r3, .L2632+40
	mov	r0, #1
	ldr	r1, .L2632+76
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L2605
.L2629:
	ldr	r3, .L2632+40
	mov	r0, #1
	ldr	r1, .L2632+80
	mvn	r8, #0
	ldr	r3, [r3, #68]
	blx	r3
	add	r2, r10, #12992
	mov	r3, #0
	strb	r3, [r2, #12]
	strb	r3, [r6, #957]
	b	.L2605
.L2631:
	ldr	r3, .L2632+40
	mov	r0, r9
	ldr	r1, .L2632+84
	ldr	r3, [r3, #68]
	blx	r3
	strb	r8, [r10, #4]
	mvn	r8, #0
	b	.L2605
.L2633:
	.align	2
.L2632:
	.word	.LC322
	.word	.LC323
	.word	.LC324
	.word	.LC325
	.word	.LC326
	.word	.LC327
	.word	.LC328
	.word	.LC329
	.word	.LC330
	.word	.LC331
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC267
	.word	.LC333
	.word	.LC335
	.word	.LC337
	.word	.LC338
	.word	.LC269
	.word	.LC268
	.word	.LC332
	.word	.LC170
	.word	.LC334
	.word	.LC336
	UNWIND(.fnend)
	.size	MVC_DecSubSPS, .-MVC_DecSubSPS
	.align	2
	.global	MVC_PassBytes
	.type	MVC_PassBytes, %function
MVC_PassBytes:
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
	ldr	ip, [r0, #232]
	cmp	ip, #0
	cmpne	r1, #0
	beq	.L2643
	ldrb	r3, [ip]	@ zero_extendqisi2
	mov	r2, r3, asl #2
	mov	r5, r3, asl #5
	rsb	r4, r2, r5
	add	r4, ip, r4
	add	r6, r4, #8
	ldr	lr, [r4, #8]
	cmp	lr, #0
	beq	.L2643
	ldr	lr, [ip, #68]
	cmp	r3, #1
	cmpls	lr, #2
	bhi	.L2643
	cmp	lr, r3
	bls	.L2643
	ldr	lr, [r4, #12]
	mov	r6, r2
	ldr	r4, [r4, #24]
	mov	lr, lr, asl #3
	add	r1, r4, r1, lsl #3
	cmp	r1, lr
	bhi	.L2638
	b	.L2636
.L2639:
	ldr	r4, [r2, #24]
	ldr	r2, [r2, #12]
	rsb	lr, lr, r4
	add	r1, r1, lr
	mov	lr, r2, asl #3
	cmp	r1, lr
	bls	.L2636
.L2638:
	rsb	r2, r6, r5
	add	r3, r3, #1
	add	ip, ip, r2
	mov	r6, r3, asl #2
	mov	r5, r3, asl #5
	str	lr, [ip, #24]
	rsb	r2, r6, r5
	ldr	ip, [r0, #232]
	ldrb	r4, [ip]	@ zero_extendqisi2
	add	r4, r4, #1
	strb	r4, [ip]
	ldr	ip, [r0, #232]
	add	r2, ip, r2
	ldr	r4, [ip, #68]
	cmp	r4, r3
	bhi	.L2639
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2636:
	rsb	r2, r6, r5
	mov	r0, #1
	add	ip, ip, r2
	str	r1, [ip, #24]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2643:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_PassBytes, .-MVC_PassBytes
	.align	2
	.global	MVC_GetBytes
	.type	MVC_GetBytes, %function
MVC_GetBytes:
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
	beq	.L2659
	ldr	r3, [r0, #232]
	cmp	r3, #0
	cmpne	r2, #0
	beq	.L2659
	ldrb	r7, [r3]	@ zero_extendqisi2
	mov	ip, r7, asl #5
	sub	ip, ip, r7, asl #2
	add	ip, r3, ip
	ldr	ip, [ip, #8]
	cmp	ip, #0
	beq	.L2659
	ldr	ip, [r3, #68]
	cmp	r7, #1
	cmpls	ip, #2
	movhi	lr, #1
	movls	lr, #0
	bhi	.L2659
	cmp	ip, r7
	bls	.L2659
.L2654:
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
	bcs	.L2649
	ldrb	r3, [r8, r4, lsr #3]	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	r2, lr
	add	r4, r1, #1
	add	ip, ip, #1
	strb	r3, [r1]
	b	.L2661
.L2652:
	cmp	ip, r6
	mov	r1, r4
	beq	.L2662
	ldrb	r3, [ip], #1	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	r2, lr
	strb	r3, [r4], #1
.L2661:
	ldr	r3, [r0, #232]
	add	r3, r3, r5
	ldr	r1, [r3, #24]
	add	r1, r1, #8
	str	r1, [r3, #24]
	bhi	.L2652
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2662:
	ldr	r3, [r0, #232]
.L2649:
	ldrb	ip, [r3]	@ zero_extendqisi2
	add	r7, r7, #1
	add	ip, ip, #1
	strb	ip, [r3]
	ldr	r3, [r0, #232]
	ldr	ip, [r3, #68]
	cmp	ip, r7
	bhi	.L2654
	mov	r0, lr
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2659:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_GetBytes, .-MVC_GetBytes
	.align	2
	.global	MVC_DecFramePackingSEI
	.type	MVC_DecFramePackingSEI, %function
MVC_DecFramePackingSEI:
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
	ldr	r1, .L2670
	mov	r4, r0
	bl	mvc_ue_v
	add	r6, r4, #11075584
	add	r5, r6, #45056
	ldr	r2, .L2670+4
	mov	r1, #1
	str	r0, [r5, #2160]
	mov	r0, r4
	bl	mvc_u_v
	uxtb	r0, r0
	strb	r0, [r5, #2137]
	cmp	r0, #0
	beq	.L2669
.L2664:
	mov	r0, r4
	ldr	r2, .L2670+8
	mov	r1, #1
	add	r6, r6, #45056
	bl	mvc_u_v
	mov	r3, #1
	strb	r3, [r6, #2136]
	strb	r0, [r6, #2138]
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2669:
	ldr	r2, .L2670+12
	mov	r1, #7
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+16
	mov	r1, #1
	str	r0, [r5, #2152]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+20
	mov	r1, #6
	strb	r0, [r5, #2139]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+24
	mov	r1, #1
	str	r0, [r5, #2156]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+28
	mov	r1, #1
	strb	r0, [r5, #2140]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+32
	mov	r1, #1
	strb	r0, [r5, #2141]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+36
	mov	r1, #1
	strb	r0, [r5, #2142]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+40
	mov	r1, #1
	strb	r0, [r5, #2143]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+44
	mov	r1, #1
	strb	r0, [r5, #2144]
	mov	r0, r4
	bl	mvc_u_v
	ldrb	r3, [r5, #2139]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r5, #2145]
	bne	.L2665
	ldr	r3, [r5, #2152]
	cmp	r3, #5
	beq	.L2665
	ldr	r2, .L2670+48
	mov	r1, #1
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+52
	mov	r1, #1
	strb	r0, [r5, #2146]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+56
	mov	r1, #1
	strb	r0, [r5, #2147]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2670+60
	mov	r1, #1
	strb	r0, [r5, #2148]
	mov	r0, r4
	bl	mvc_u_v
	strb	r0, [r5, #2149]
.L2665:
	ldr	r2, .L2670+64
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2670+68
	str	r0, [r5, #2164]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #2168]
	b	.L2664
.L2671:
	.align	2
.L2670:
	.word	.LC339
	.word	.LC340
	.word	.LC356
	.word	.LC341
	.word	.LC342
	.word	.LC343
	.word	.LC344
	.word	.LC345
	.word	.LC346
	.word	.LC347
	.word	.LC348
	.word	.LC349
	.word	.LC350
	.word	.LC351
	.word	.LC352
	.word	.LC353
	.word	.LC354
	.word	.LC355
	UNWIND(.fnend)
	.size	MVC_DecFramePackingSEI, .-MVC_DecFramePackingSEI
	.align	2
	.global	MVC_DecPicTimingSEI
	.type	MVC_DecPicTimingSEI, %function
MVC_DecPicTimingSEI:
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
	add	r6, r0, #11075584
	ldr	r3, [r0, #248]
	add	r2, r6, #32768
	movw	r4, #3992
	mov	r5, r0
	ldr	r2, [r2, #2088]
	mla	r4, r4, r2, r3
	ldrb	r2, [r4, #25]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2673
	ldr	r0, [r0, #36]
	cmp	r0, #0
	ble	.L2674
	ldrb	r2, [r3, #25]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #3984
	addeq	r3, r3, #8
	beq	.L2677
	b	.L2696
.L2678:
	ldrb	r1, [r3, #-3967]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2675
.L2677:
	add	r2, r2, #1
	mov	r4, r3
	cmp	r2, r0
	add	r3, r3, #3984
	add	r3, r3, #8
	bne	.L2678
.L2674:
	ldr	r3, .L2698
	mov	r0, #1
	ldr	r1, .L2698+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
.L2679:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2696:
	mov	r4, r3
.L2675:
	cmp	r4, #0
	beq	.L2674
.L2673:
	ldrb	r3, [r4, #24]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2680
	ldrb	r3, [r4, #35]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2697
	ldr	r1, [r4, #388]
	ldr	r8, [r4, #392]
	add	r1, r1, #1
	add	r8, r8, #1
.L2683:
	ldr	r2, .L2698+8
	mov	r0, r5
	bl	mvc_u_v
	add	r7, r6, #45056
	mov	r1, r8
	ldr	r2, .L2698+12
	str	r0, [r7, #2176]
	mov	r0, r5
	bl	mvc_u_v
	str	r0, [r7, #2180]
.L2680:
	ldrb	r0, [r4, #39]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	r3, r0
	beq	.L2679
	mov	r0, r5
	ldr	r2, .L2698+16
	mov	r1, #4
	add	r6, r6, #45056
	bl	mvc_u_v
	mov	r3, #0
	strb	r0, [r6, #2172]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2697:
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2680
	ldr	r1, [r4, #700]
	ldr	r8, [r4, #704]
	add	r1, r1, #1
	add	r8, r8, #1
	b	.L2683
.L2699:
	.align	2
.L2698:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC357
	.word	.LC358
	.word	.LC359
	.word	.LC360
	UNWIND(.fnend)
	.size	MVC_DecPicTimingSEI, .-MVC_DecPicTimingSEI
	.align	2
	.global	MVC_DecSEI
	.type	MVC_DecSEI, %function
MVC_DecSEI:
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
	ldr	r2, [r0, #232]
	sub	r7, fp, #44
	mov	r3, #0
	mov	r1, #32
	mov	r4, r0
	add	r6, r0, #548
	mov	r8, r3
	strb	r3, [r7, #-1]!
	str	r1, [r2, #24]
	b	.L2703
.L2886:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2702
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2885
.L2703:
	mov	r2, #1
	mov	r1, r7
	mov	r0, r4
	bl	MVC_GetBytes
	ldr	r3, [r4, #572]
	ldr	ip, [r4, #564]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r8, r8, r2
	mov	r5, r0
	mov	r0, r6
	ble	.L2886
.L2702:
	ldr	r3, .L2917
	mov	r0, #1
	ldr	r1, .L2917+4
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L2705
.L2885:
	ldr	r10, .L2917
	mov	r3, #0
	str	r3, [fp, #-64]
.L2839:
	mov	r5, #0
	b	.L2709
.L2888:
	bl	BsSkip
	cmp	r9, #0
	ble	.L2707
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2887
.L2709:
	mov	r2, #1
	mov	r1, r7
	mov	r0, r4
	bl	MVC_GetBytes
	ldr	r3, [r4, #572]
	ldr	ip, [r4, #564]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r5, r5, r2
	mov	r9, r0
	mov	r0, r6
	ble	.L2888
.L2707:
	ldr	r3, .L2917
	mov	r0, #1
	ldr	r1, .L2917+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2887:
	cmp	r5, #409600
	bgt	.L2707
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #68]
	cmp	r2, #2
	ldreq	r2, [r3, #52]
	ldreq	r3, [r3, #24]
	ldrne	r2, [r3, #24]
	addeq	r2, r2, r3
	moveq	r2, r2, lsr #3
	cmp	r8, #45
	ldrls	pc, [pc, r8, asl #2]
	b	.L2712
.L2714:
	.word	.L2713
	.word	.L2715
	.word	.L2716
	.word	.L2717
	.word	.L2718
	.word	.L2719
	.word	.L2720
	.word	.L2721
	.word	.L2722
	.word	.L2723
	.word	.L2724
	.word	.L2725
	.word	.L2726
	.word	.L2727
	.word	.L2728
	.word	.L2729
	.word	.L2730
	.word	.L2731
	.word	.L2732
	.word	.L2733
	.word	.L2734
	.word	.L2735
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2712
	.word	.L2736
.L2736:
	mov	r1, r5
	mov	r0, r4
	ldr	r8, [r4, #572]
	bl	MVC_DecFramePackingSEI
	ldr	r0, [r4, #572]
	mov	r9, r5, asl #3
	rsb	r3, r8, r0
	cmp	r3, r9
	bge	.L2825
	rsb	r3, r3, r9
	str	r3, [fp, #-56]
	cmp	r3, #0
	add	r8, r3, #7
	movge	r8, r3
	ldr	r3, [r4, #564]
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2827
	add	r2, r0, #8
	mov	r3, r3, asl #3
	cmp	r2, r3
	bgt	.L2827
	mov	r9, #0
	b	.L2828
.L2829:
	add	r2, r0, #8
	cmp	r2, r3
	bgt	.L2827
.L2828:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r9, r9, #1
	ldr	r3, [r4, #564]
	cmp	r9, r8
	ldr	r0, [r4, #572]
	mov	r3, r3, asl #3
	bne	.L2829
.L2827:
	ldr	r2, [fp, #-56]
	mov	r1, r2, asr #31
	mov	r1, r1, lsr #29
	add	r2, r2, r1
	and	r2, r2, #7
	rsb	r1, r1, r2
	add	r2, r1, r0
	cmp	r2, r3
	ble	.L2889
.L2825:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2890
.L2738:
	ldr	r3, [r4, #60]
	cmp	r3, #3
	bhi	.L2891
.L2834:
	mov	r8, #0
	b	.L2838
.L2836:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2837
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2892
.L2838:
	mov	r2, #1
	mov	r1, r7
	mov	r0, r4
	bl	MVC_GetBytes
	ldr	r3, [r4, #572]
	ldr	ip, [r4, #564]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r8, r8, r2
	mov	r5, r0
	mov	r0, r6
	ble	.L2836
.L2837:
	mov	r0, #0
.L2705:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2735:
	mov	r3, r5
	ldr	r1, .L2917+12
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2893
.L2821:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2822
.L2823:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2822:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2823
	ldr	r3, [r4, #60]
	cmp	r3, #3
	bls	.L2834
.L2891:
	ldr	r3, .L2917
	mov	r0, #1
	ldr	r1, .L2917+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2734:
	mov	r3, r5
	ldr	r1, .L2917+20
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2894
.L2818:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2819
.L2820:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2819:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2820
	b	.L2738
.L2733:
	mov	r3, r5
	ldr	r1, .L2917+24
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2895
.L2815:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2816
.L2817:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2816:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2817
	b	.L2738
.L2731:
	mov	r3, r5
	ldr	r1, .L2917+28
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2896
.L2809:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2810
.L2811:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2810:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2811
	b	.L2738
.L2732:
	mov	r3, r5
	ldr	r1, .L2917+32
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2897
.L2812:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2813
.L2814:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2813:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2814
	b	.L2738
.L2730:
	mov	r3, r5
	ldr	r1, .L2917+36
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2898
.L2806:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2807
.L2808:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2807:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2808
	b	.L2738
.L2729:
	mov	r3, r5
	ldr	r1, .L2917+40
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2899
.L2803:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2804
.L2805:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2804:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2805
	b	.L2738
.L2721:
	mov	r3, r5
	ldr	r1, .L2917+44
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2900
.L2779:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2780
.L2781:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2780:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2781
	b	.L2738
.L2725:
	mov	r3, r5
	ldr	r1, .L2917+48
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2901
.L2791:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2792
.L2793:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2792:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2793
	b	.L2738
.L2716:
	mov	r3, r5
	ldr	r1, .L2917+52
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2902
.L2748:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2749
.L2750:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2749:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2750
	b	.L2738
.L2727:
	mov	r3, r5
	ldr	r1, .L2917+56
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2903
.L2797:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2798
.L2799:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2798:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2799
	b	.L2738
.L2719:
	ldr	r3, [fp, #-64]
	cmp	r3, #0
	bne	.L2718
	ldr	ip, .L2917
	mov	r3, r5
	ldr	r8, [r10, #68]
	mov	r0, #20
	ldr	r1, .L2917+60
	str	ip, [fp, #-68]
	blx	r8
.L2755:
	ldr	r0, [r4, #120]
	ldr	r8, [r4, #60]
	bl	GetUsd
	add	r8, r8, #132
	str	r0, [r4, r8, asl #2]
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	ldr	r1, [r4, r3, asl #2]
	cmp	r1, #0
	beq	.L2842
	ldr	r2, [r4, #232]
	cmp	r5, #1024
	movlt	r9, r5
	movge	r9, #1024
	ldrb	ip, [r2]	@ zero_extendqisi2
	ldr	lr, [r2, #68]
	cmp	ip, lr
	bcs	.L2843
	sxth	r3, ip
	mov	r8, #0
	mov	r0, r3, asl #5
	sub	r0, r0, r3, asl #2
	add	r0, r2, r0
.L2757:
	ldr	r3, [r0, #24]
	add	ip, ip, #1
	ldr	r2, [r0, #12]
	cmp	ip, lr
	add	r3, r3, #7
	add	r0, r0, #28
	sub	r3, r2, r3, lsr #3
	add	r8, r8, r3
	bne	.L2757
	mov	r2, r8
.L2756:
	ldrsb	r3, [fp, #-64]
	cmp	r9, r2
	movle	r8, r9
	cmp	r3, #1
	movne	r3, #0
	strne	r3, [fp, #-56]
	strne	r3, [fp, #-60]
	beq	.L2904
.L2759:
	ldr	r3, [fp, #-56]
	mov	r0, r4
	rsb	r2, r3, r8
	bl	MVC_GetBytes
	subs	r8, r0, #0
	ble	.L2905
	ldr	r3, [fp, #-60]
	rsb	r3, r3, r9
	cmp	r8, r3
	ldr	r3, [r4, #60]
	blt	.L2906
	add	r3, r3, #132
	ldr	r2, [fp, #-60]
	cmp	r9, r5
	ldr	r3, [r4, r3, asl #2]
	rsb	r8, r2, r5
	str	r8, [r3, #1048]
	bcc	.L2907
.L2770:
	cmp	r8, #0
	ble	.L2765
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2765
	mov	r5, #0
	b	.L2772
.L2773:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2765
.L2772:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2773
.L2765:
	ldr	r3, [r4, #60]
.L2883:
	ldr	r1, [r4, #224]
	add	r3, r3, #132
	ldr	ip, .L2917+64
	mov	r2, #8
	ldr	r3, [r4, r3, asl #2]
	ldrd	r0, [r1, #48]
	add	r3, r3, #1056
	ldr	r5, [ip]
	strd	r0, [r3]
	cmp	r5, #0
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r2, [r3, #1036]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #84]
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r2, [r3, #1040]
	beq	.L2738
	ldr	r2, [r4, #60]
	mov	r3, #1072
	mov	r1, #6
	ldr	r0, [r4, #120]
	add	r2, r2, #132
	ldr	r2, [r4, r2, asl #2]
	blx	r5
	b	.L2738
.L2723:
	mov	r3, r5
	ldr	r1, .L2917+68
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2908
.L2785:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2786
.L2787:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2786:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2787
	b	.L2738
.L2722:
	mov	r3, r5
	ldr	r1, .L2917+72
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2909
.L2782:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2783
.L2784:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2783:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2784
	b	.L2738
.L2724:
	mov	r3, r5
	ldr	r1, .L2917+76
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2910
.L2788:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2789
.L2790:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2789:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2790
	b	.L2738
.L2713:
	mov	r3, r5
	ldr	r1, .L2917+80
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2911
.L2737:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2739
.L2740:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2739:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2740
	b	.L2738
.L2728:
	mov	r3, r5
	ldr	r1, .L2917+84
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2912
.L2800:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2801
.L2802:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2801:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2802
	b	.L2738
.L2720:
	ldr	r8, [r10, #68]
	mov	r3, r5
	ldr	r1, .L2917+88
	mov	r0, #20
	blx	r8
	cmp	r5, #0
	ble	.L2776
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2776
	mov	r8, #0
	b	.L2777
.L2778:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2776
.L2777:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2778
.L2776:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2738
	ldr	r5, [r10, #68]
	movw	r3, #12297
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r5
	b	.L2738
.L2726:
	mov	r3, r5
	ldr	r1, .L2917+92
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2913
.L2794:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2795
.L2796:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2795:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2796
	b	.L2738
.L2715:
	mov	r3, r5
	ldr	r8, [r10, #68]
	ldr	r1, .L2917+96
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	ldr	r8, [r4, #572]
	bl	MVC_DecPicTimingSEI
	ldr	r0, [r4, #572]
	mov	r9, r5, asl #3
	rsb	r3, r8, r0
	cmp	r3, r9
	bge	.L2742
	rsb	r3, r3, r9
	str	r3, [fp, #-56]
	cmp	r3, #0
	add	r8, r3, #7
	movge	r8, r3
	ldr	r3, [r4, #564]
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2744
	add	r2, r0, #8
	mov	r3, r3, asl #3
	cmp	r2, r3
	bgt	.L2744
	mov	r9, #0
	b	.L2745
.L2746:
	add	r2, r0, #8
	cmp	r2, r3
	bgt	.L2744
.L2745:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r9, r9, #1
	ldr	r3, [r4, #564]
	cmp	r9, r8
	ldr	r0, [r4, #572]
	mov	r3, r3, asl #3
	bne	.L2746
.L2744:
	ldr	r2, [fp, #-56]
	mov	r1, r2, asr #31
	mov	r1, r1, lsr #29
	add	r2, r2, r1
	and	r2, r2, #7
	rsb	r1, r1, r2
	add	r2, r0, r1
	cmp	r3, r2
	bge	.L2914
.L2742:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2738
	ldr	r5, [r10, #68]
	movw	r3, #12071
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r5
	b	.L2738
.L2717:
	mov	r3, r5
	ldr	r1, .L2917+100
	ldr	r8, [r10, #68]
	mov	r0, #20
	blx	r8
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2915
.L2751:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2752
.L2753:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2752:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2753
	b	.L2738
.L2712:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2916
.L2831:
	cmp	r5, #0
	ble	.L2738
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
	mov	r8, #0
	b	.L2832
.L2833:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2738
.L2832:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2833
	b	.L2738
.L2892:
	cmp	r3, #128
	bne	.L2839
	b	.L2837
.L2718:
	ldr	ip, .L2917
	mov	r3, r5
	ldr	r8, [r10, #68]
	mov	r0, #20
	ldr	r1, .L2917+104
	str	ip, [fp, #-68]
	blx	r8
	mov	r3, #1
	str	r3, [fp, #-64]
	b	.L2755
.L2906:
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r8, [r3, #1048]
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2765
	mov	r5, #0
	b	.L2766
.L2918:
	.align	2
.L2917:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC361
	.word	.LC362
	.word	.LC389
	.word	.LC390
	.word	.LC388
	.word	.LC387
	.word	.LC385
	.word	.LC386
	.word	.LC384
	.word	.LC383
	.word	.LC375
	.word	.LC379
	.word	.LC366
	.word	.LC381
	.word	.LC369
	.word	g_event_report
	.word	.LC377
	.word	.LC376
	.word	.LC378
	.word	.LC363
	.word	.LC382
	.word	.LC374
	.word	.LC380
	.word	.LC365
	.word	.LC367
	.word	.LC368
	.word	.LC370
	.word	.LC372
	.word	.LANCHOR0+236
	.word	.LC364
	.word	.LC371
	.word	.LC373
.L2768:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bgt	.L2765
.L2766:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2768
	b	.L2765
.L2904:
	strb	r3, [r1, #1064]
	mov	r0, r4
	ldr	r3, [r4, #60]
	mov	r1, #8
	ldr	r2, .L2917+108
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r3, [fp, #-56]
	bl	mvc_u_v
	ldr	r3, [fp, #-56]
	strb	r0, [r3, #1065]
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	ldrb	r2, [r3, #1065]	@ zero_extendqisi2
	cmp	r2, #255
	beq	.L2760
	mov	r2, #3
	str	r2, [fp, #-56]
	mov	r1, r2
	mov	r2, #0
	str	r1, [fp, #-60]
	strb	r2, [r3, #1066]
.L2761:
	ldr	r3, [r4, #60]
	mov	r1, #16
	ldr	r2, .L2917+112
	mov	r0, r4
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r3, [fp, #-72]
	bl	mvc_u_v
	ldr	r3, [fp, #-72]
	ldr	r1, [fp, #-56]
	add	r3, r3, #1056
	strh	r0, [r3, #12]	@ movhi
	mov	r0, r4
	bl	MVC_PassBytes
	ldr	r3, [fp, #-56]
	cmp	r8, r3
	ldr	r3, [r4, #60]
	beq	.L2883
	add	r3, r3, #132
	ldr	r1, [r4, r3, asl #2]
	b	.L2759
.L2899:
	ldr	r8, [r10, #68]
	movw	r3, #12517
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2803
.L2900:
	ldr	r8, [r10, #68]
	movw	r3, #12309
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2779
.L2901:
	ldr	r8, [r10, #68]
	movw	r3, #12413
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2791
.L2902:
	ldr	r8, [r10, #68]
	movw	r3, #12083
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2748
.L2903:
	ldr	r8, [r10, #68]
	movw	r3, #12465
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2797
.L2895:
	ldr	r8, [r10, #68]
	movw	r3, #12621
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2815
.L2896:
	ldr	r8, [r10, #68]
	movw	r3, #12569
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2809
.L2897:
	ldr	r8, [r10, #68]
	movw	r3, #12595
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2812
.L2898:
	ldr	r8, [r10, #68]
	movw	r3, #12543
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2806
.L2893:
	ldr	r8, [r10, #68]
	movw	r3, #12673
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2821
.L2894:
	ldr	r8, [r10, #68]
	movw	r3, #12647
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2818
.L2909:
	ldr	r8, [r10, #68]
	movw	r3, #12335
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2782
.L2910:
	ldr	r8, [r10, #68]
	movw	r3, #12387
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2788
.L2911:
	ldr	r8, [r10, #68]
	movw	r3, #12018
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2737
.L2912:
	ldr	r8, [r10, #68]
	movw	r3, #12491
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2800
.L2908:
	ldr	r8, [r10, #68]
	movw	r3, #12361
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2785
.L2913:
	ldr	r8, [r10, #68]
	movw	r3, #12439
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2794
.L2915:
	ldr	r8, [r10, #68]
	movw	r3, #12109
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2751
.L2890:
	ldr	r5, [r10, #68]
	movw	r3, #12725
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r5
	b	.L2738
.L2916:
	ldr	r8, [r10, #68]
	movw	r3, #12737
	ldr	r2, .L2917+116
	mov	r0, #20
	ldr	r1, .L2917+120
	blx	r8
	b	.L2831
.L2914:
	mov	r0, r6
	bl	BsSkip
	b	.L2742
.L2889:
	mov	r0, r6
	bl	BsSkip
	b	.L2825
.L2907:
	rsb	r1, r9, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2770
	ldr	r3, [fp, #-68]
	mov	r0, #20
	ldr	r2, .L2917+116
	ldr	r1, .L2917+120
	ldr	r5, [r3, #68]
	movw	r3, #12245
	blx	r5
	b	.L2770
.L2843:
	mov	r2, #0
	mov	r8, r2
	b	.L2756
.L2760:
	ldr	r2, .L2917+124
	mov	r1, #8
	mov	r0, r4
	str	r3, [fp, #-72]
	mov	r3, #4
	str	r3, [fp, #-56]
	bl	mvc_u_v
	ldr	r3, [fp, #-56]
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-72]
	strb	r0, [r3, #1066]
	b	.L2761
.L2842:
	mvn	r0, #0
	b	.L2705
.L2905:
	ldr	r3, [fp, #-68]
	mov	r0, #1
	ldr	r1, .L2917+128
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #60]
	ldr	r0, [r4, #120]
	add	r3, r3, #132
	ldr	r1, [r4, r3, asl #2]
	bl	FreeUsdByDec
	ldr	r3, [r4, #60]
	mov	r2, #0
	mvn	r0, #0
	add	r3, r3, #132
	str	r2, [r4, r3, asl #2]
	b	.L2705
	UNWIND(.fnend)
	.size	MVC_DecSEI, .-MVC_DecSEI
	.align	2
	.global	MVC_InitOldSlice
	.type	MVC_InitOldSlice, %function
MVC_InitOldSlice:
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
	ldr	r1, [r0, #40]
	add	r3, r0, #11075584
	add	r3, r3, #40960
	movw	r2, #23352
	movt	r2, 1
	mov	r0, #2
	str	r1, [r3, #2188]
	mov	r1, #7
	str	r2, [r3, #2192]
	mov	r2, #32
	strb	r1, [r3, #2179]
	mov	r1, #3
	strb	r2, [r3, #2178]
	mvn	r2, #0
	str	r1, [r3, #2200]
	mov	r1, #262144
	str	r2, [r3, #2204]
	mov	r2, #0
	strb	r0, [r3, #2177]
	str	r1, [r3, #2216]
	strb	r2, [r3, #2176]
	str	r2, [r3, #2208]
	str	r2, [r3, #2212]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_InitOldSlice, .-MVC_InitOldSlice
	.align	2
	.global	MVC_IsNewPicNal
	.type	MVC_IsNewPicNal, %function
MVC_IsNewPicNal:
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
	beq	.L2929
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	and	r3, r3, #31
	sub	r3, r3, #1
	cmp	r3, #7
	ldrls	pc, [pc, r3, asl #2]
	b	.L2929
.L2923:
	.word	.L2922
	.word	.L2929
	.word	.L2929
	.word	.L2929
	.word	.L2922
	.word	.L2929
	.word	.L2924
	.word	.L2924
.L2924:
	ldr	r0, [r0]
	mov	r3, #1
	str	r3, [r5]
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2922:
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L2925
.L2927:
	mvn	r0, #0
.L2926:
	mov	r3, #0
	str	r3, [r5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2929:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2925:
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
	bhi	.L2927
	mov	r0, r0, asl #1
	rsb	r0, r0, #31
	mov	r0, r4, lsr r0
	subs	r0, r0, #1
	mvnne	r0, #0
	b	.L2926
	UNWIND(.fnend)
	.size	MVC_IsNewPicNal, .-MVC_IsNewPicNal
	.align	2
	.global	MVC_FindZeroBitsInSeg
	.type	MVC_FindZeroBitsInSeg, %function
MVC_FindZeroBitsInSeg:
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
	ble	.L2956
	ldr	r3, [fp, #-48]
	subs	r7, r3, #0
	add	r8, r3, #63
	movge	r8, r3
	ands	r3, r3, #63
	movne	r3, #1
	add	r8, r3, r8, asr #6
	cmp	r8, #0
	ble	.L2944
	ldr	r5, .L2957
	ldr	r10, .L2957+4
.L2942:
	cmp	r7, #64
	ldr	r3, [r10, #52]
	ldr	r0, .L2957
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
	bne	.L2934
	ldr	r2, .L2957
	add	r4, r4, #1
	cmp	r3, r2
	bne	.L2937
	b	.L2935
.L2938:
	cmp	r3, r5
	add	r4, r4, #1
	beq	.L2935
.L2937:
	ldrb	r2, [r3, #-1]!	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2938
.L2934:
	mov	r0, r4, asl #3
.L2933:
	ldr	r3, [fp, #-48]
	cmp	r4, r3
	bge	.L2946
	sub	r3, r3, #1
	rsb	r4, r4, r3
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	tst	r2, #1
	moveq	r2, r2, lsr #1
	moveq	r3, #1
	bne	.L2946
.L2941:
	tst	r2, #1
	mov	r2, r2, lsr #1
	bne	.L2939
	add	r3, r3, #1
	cmp	r3, #8
	bne	.L2941
	b	.L2939
.L2935:
	subs	r8, r8, #1
	sub	r7, r7, #64
	bne	.L2942
	b	.L2934
.L2946:
	mov	r3, #0
.L2939:
	add	r0, r3, r0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2956:
	ldr	r3, .L2957+4
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L2957+8
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2944:
	mov	r0, r4
	b	.L2933
.L2958:
	.align	2
.L2957:
	.word	.LANCHOR3-1952
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC391
	UNWIND(.fnend)
	.size	MVC_FindZeroBitsInSeg, .-MVC_FindZeroBitsInSeg
	.align	2
	.global	MVC_FindTrailZeros
	.type	MVC_FindTrailZeros, %function
MVC_FindTrailZeros:
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
	beq	.L2965
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2964
	ldr	r1, [r3, #40]
	ldr	r0, [r3, #36]
	bl	MVC_FindZeroBitsInSeg
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #40]
	cmp	r0, r2, asl #3
	bcs	.L2968
	cmn	r0, #1
	beq	.L2964
.L2963:
	add	r0, r0, #1
	str	r0, [r3, #72]
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2967
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #72]
	cmp	r2, r1, asl #3
	bcs	.L2969
.L2967:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2969:
	ldr	r1, [r3, #60]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r2, [r4, #232]
	mov	r3, #0
	mov	r1, #1
	mov	r0, r3
	str	r3, [r2, #36]
	ldr	r2, [r4, #232]
	str	r1, [r2, #68]
	ldr	r2, [r4, #232]
	str	r3, [r2, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2968:
	ldr	r1, [r3, #60]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #232]
	mov	r1, #0
	mov	r2, #1
	str	r1, [r3, #36]
	ldr	r3, [r4, #232]
	str	r2, [r3, #68]
	ldr	r3, [r4, #232]
.L2964:
	ldr	r1, [r3, #12]
	ldr	r0, [r3, #8]
	bl	MVC_FindZeroBitsInSeg
	ldr	r3, [r4, #232]
	b	.L2963
.L2965:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FindTrailZeros, .-MVC_FindTrailZeros
	.align	2
	.global	MVC_CombinePacket
	.type	MVC_CombinePacket, %function
MVC_CombinePacket:
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
	ldr	r3, [r0, #232]
	ldr	r3, [r3, #12]
	cmp	r3, #4096
	ldmcsfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_CombinePacket.part.10
	UNWIND(.fnend)
	.size	MVC_CombinePacket, .-MVC_CombinePacket
	.align	2
	.global	MVC_FindNaluArraySlot
	.type	MVC_FindNaluArraySlot, %function
MVC_FindNaluArraySlot:
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
	ldrb	r2, [r0, #937]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2977
	mov	r2, r0
	mov	r3, #1
	b	.L2975
.L2974:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L2980
.L2975:
	ldrb	r1, [r2, #1025]	@ zero_extendqisi2
	add	r2, r2, #88
	cmp	r1, #0
	bne	.L2974
	mov	r2, r3
.L2973:
	mov	ip, #88
	mov	r1, #1
	mla	r3, ip, r3, r0
	mov	r0, r2
	strb	r1, [r3, #937]
	ldmfd	sp, {fp, sp, pc}
.L2980:
	mvn	r2, #0
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L2977:
	mov	r3, r2
	b	.L2973
	UNWIND(.fnend)
	.size	MVC_FindNaluArraySlot, .-MVC_FindNaluArraySlot
	.align	2
	.global	MVC_InquireSliceProperty
	.type	MVC_InquireSliceProperty, %function
MVC_InquireSliceProperty:
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
	ldr	r10, .L3024
	mov	r4, r0
	ldr	r3, [r0, #68]
	mov	r9, r1
	mov	r7, r2
	ldr	r1, .L3024+4
	sub	r2, r3, #1
	mov	r0, #22
	ldr	r3, [r10, #68]
	add	r6, r4, #11075584
	blx	r3
	mov	r3, #0
	str	r3, [r7]
	add	r5, r6, #40960
	str	r3, [r9]
	add	r1, r4, #12288
	ldr	r2, [r4, #232]
	mvn	ip, #0
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	strb	r0, [r5, #523]
	ldrb	lr, [r2, #4]	@ zero_extendqisi2
	strb	lr, [r5, #528]
	ldrb	r2, [r2, #5]	@ zero_extendqisi2
	strb	r3, [r5, #531]
	str	ip, [r5, #2160]
	strb	r2, [r5, #532]
	ldrb	r3, [r1, #704]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3017
	cmp	r2, #255
	beq	.L3018
.L2983:
	mov	r0, r4
	bl	MVC_SliceCheck
	subs	r8, r0, #0
	bne	.L2999
	mov	r0, r4
	bl	MVC_ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L3019
	ldrb	r3, [r5, #525]	@ zero_extendqisi2
	mov	r0, #2240
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r9]
	ldrb	r1, [r5, #532]	@ zero_extendqisi2
	ldr	r3, [r5, #536]
	ldr	ip, [r4, #252]
	sxtb	r2, r1
	cmn	r2, #1
	mla	r3, r0, r3, ip
	beq	.L3020
	cmp	r1, #0
	bne	.L2995
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r3, [r3, #28]
	cmp	r2, #1
	beq	.L3021
	ldr	r2, [r4, #28]
	cmp	r2, r3
	movweq	r3, #35364
	movteq	r3, 168
	addeq	r3, r4, r3
	bne	.L3022
.L2994:
	ldrb	r1, [r3, #20]	@ zero_extendqisi2
	add	r6, r6, #45056
	ldr	r0, [r3, #3952]
	rsb	r2, r1, #2
	ldr	r1, [r3, #3948]
	ldr	ip, [r4, #16]
	mla	r2, r0, r2, r2
	ldr	r0, [r4, #12]
	add	r1, r1, #1
	cmp	r0, r1
	cmpeq	ip, r2
	movne	r2, #1
	strne	r2, [r7]
	ldr	r2, [r3, #3972]
	ldr	r3, [r6, #2376]
	add	r3, r3, #1
	cmp	r2, r3
	movhi	r3, #1
	strhi	r3, [r7]
.L2991:
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3017:
	strb	r3, [r5, #531]
	ldr	r3, [r1, #712]
	str	r3, [r5, #2160]
	ldrb	r3, [r1, #708]	@ zero_extendqisi2
	strb	r3, [r5, #529]
	ldrb	r3, [r1, #709]	@ zero_extendqisi2
	strb	r3, [r5, #530]
	b	.L2983
.L3020:
	ldr	r3, [r3, #28]
	movw	r1, #3992
	ldr	r2, [r4, #248]
	mla	r3, r1, r3, r2
	b	.L2994
.L3018:
	ldr	r3, [r4, #20]
	cmp	r3, #0
	beq	.L2983
	add	r3, r4, #10747904
	add	r3, r3, #20480
	ldr	r2, [r3, #2384]
	cmp	r2, #0
	bne	.L2986
	ldrb	r2, [r3, #2380]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2986
	add	r3, r4, #12992
	add	r3, r3, #16
.L2989:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L2987
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L3023
.L2987:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L2989
	mvn	r3, #0
	b	.L3016
.L3021:
	movw	r2, #8500
	movt	r2, 5
	mla	r3, r2, r3, r4
	add	r3, r3, #286720
	add	r3, r3, #932
	b	.L2994
.L2986:
	ldr	r3, [r3, #2388]
.L3016:
	cmn	r3, #1
	str	r3, [r5, #2160]
	beq	.L2983
	sub	r0, r0, #5
	mov	r3, #1
	clz	r0, r0
	strb	r3, [r5, #531]
	strb	r3, [r5, #530]
	mov	r0, r0, lsr #5
	strb	r0, [r5, #529]
	b	.L2983
.L2999:
	mvn	r8, #0
	b	.L2991
.L3022:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L3024+8
	mvn	r8, #0
	blx	r3
	b	.L2991
.L3019:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L3024+12
	mvn	r8, #0
	blx	r3
	b	.L2991
.L2995:
	ldr	r3, [r10, #68]
	mov	r0, #1
	ldr	r1, .L3024+16
	mvn	r8, #0
	blx	r3
	b	.L2991
.L3023:
	movw	r3, #8500
	movt	r3, 5
	mla	r3, r3, r2, r4
	add	r3, r3, #12992
	add	r3, r3, #16
	ldr	r3, [r3, #4]
	b	.L3016
.L3025:
	.align	2
.L3024:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC392
	.word	.LC30
	.word	.LC393
	.word	.LC394
	UNWIND(.fnend)
	.size	MVC_InquireSliceProperty, .-MVC_InquireSliceProperty
	.align	2
	.global	MVC_HaveSliceToDec
	.type	MVC_HaveSliceToDec, %function
MVC_HaveSliceToDec:
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
	ldr	r0, [r0, #64]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_HaveSliceToDec, .-MVC_HaveSliceToDec
	.align	2
	.global	MVC_IsRefListWrong
	.type	MVC_IsRefListWrong, %function
MVC_IsRefListWrong:
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
	add	r5, r0, #11075584
	mov	r7, r0
	add	r5, r5, #40960
	ldr	r3, [r5, #568]
	cmp	r3, #0
	beq	.L3028
	add	r6, r0, #252
	mov	r4, #0
	b	.L3032
.L3029:
	ldr	r3, [r0, #520]
	cmp	r3, #0
	beq	.L3031
	ldr	r3, [r5, #568]
	cmp	r4, r3
	bcs	.L3054
.L3032:
	ldr	r3, [r6, #4]!
	add	r4, r4, #1
	ldr	r0, [r7, #120]
	ldr	r3, [r3, #4]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L3029
.L3031:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3054:
	cmp	r3, #0
	beq	.L3028
	ldr	r3, [r5, #572]
	cmp	r3, #0
	addne	r6, r7, #384
	movne	r4, #0
	bne	.L3035
	b	.L3028
.L3055:
	ldr	r3, [r0, #520]
	cmp	r3, #0
	beq	.L3031
	ldr	r3, [r5, #572]
	cmp	r4, r3
	bcs	.L3028
.L3035:
	ldr	r3, [r6, #4]!
	add	r4, r4, #1
	ldr	r0, [r7, #120]
	ldr	r3, [r3, #4]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L3055
	b	.L3031
.L3028:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_IsRefListWrong, .-MVC_IsRefListWrong
	.align	2
	.global	MVC_DEC_Destroy
	.type	MVC_DEC_Destroy, %function
MVC_DEC_Destroy:
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
	mov	r6, r0
	bl	MVC_ClearCurrPic
	mov	r0, r6
	bl	MVC_ClearAllNal
	ldr	r3, [r6, #60]
	cmp	r3, #0
	beq	.L3057
	mov	r4, #0
	add	r5, r6, #524
	mov	r7, r4
.L3059:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3058
	ldr	r0, [r6, #120]
	bl	FreeUsdByDec
	str	r7, [r5]
	ldr	r3, [r6, #60]
.L3058:
	cmp	r3, r4
	bhi	.L3059
.L3057:
	movw	r5, #48096
	movw	r8, #10080
	movt	r5, 169
	movt	r8, 170
	add	r5, r6, r5
	add	r8, r6, r8
	mov	r7, #0
.L3063:
	sub	r4, r5, #16
.L3061:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L3060
	ldr	r0, [r6, #120]
	bl	FreeUsdByDec
	str	r7, [r4]
.L3060:
	cmp	r4, r5
	bne	.L3061
	add	r5, r4, #688
	cmp	r5, r8
	bne	.L3063
	ldr	r3, .L3075
	mov	r0, #2
	ldr	r1, .L3075+4
	ldr	r3, [r3, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L3076:
	.align	2
.L3075:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC395
	UNWIND(.fnend)
	.size	MVC_DEC_Destroy, .-MVC_DEC_Destroy
	.align	2
	.global	MVC_DEC_RecycleImage
	.type	MVC_DEC_RecycleImage, %function
MVC_DEC_RecycleImage:
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
	ldr	r3, .L3087
	mov	r6, r0
	mov	r8, r1
	mov	r0, #2
	ldr	r1, .L3087+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r1, r8
	ldr	r0, [r6, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L3082
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	beq	.L3082
	add	r4, r0, #216
	add	r5, r0, #232
	mov	r7, #0
.L3080:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L3079
	ldr	r0, [r6, #120]
	bl	FreeUsdByDec
	str	r7, [r4]
.L3079:
	cmp	r4, r5
	bne	.L3080
	ldr	r0, [r6, #120]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3082:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3088:
	.align	2
.L3087:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC396
	UNWIND(.fnend)
	.size	MVC_DEC_RecycleImage, .-MVC_DEC_RecycleImage
	.align	2
	.global	MVC_OutputFrmToVO
	.type	MVC_OutputFrmToVO, %function
MVC_OutputFrmToVO:
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
	mov	r6, r2
	mov	r4, r0
	moveq	r3, #1
	movne	r3, #0
	mov	r5, r1
	beq	.L3127
	ldr	r2, [r0, #224]
	ldr	r2, [r2, #12]
	cmp	r2, #0
	ble	.L3092
	ldrb	r2, [r0, #8]	@ zero_extendqisi2
	cmp	r2, #2
	beq	.L3092
	ldr	r2, [r0, #520]
	cmp	r2, #0
	strneb	r3, [r2, #2]
	movne	r0, #1
	strne	r3, [r4, #520]
	beq	.L3094
.L3126:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3092:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_CheckFrameStore
	cmn	r0, #3
	beq	.L3094
	ldr	r1, [r4, #520]
	cmp	r1, #0
	beq	.L3095
	mov	r0, r4
	bl	MVC_GetImagePara
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_CheckFrameStore
	subs	r7, r0, #0
	beq	.L3128
	cmn	r7, #3
	beq	.L3103
	ldr	ip, .L3136
	mov	r3, r7
	movw	r2, #1950
	ldr	r1, .L3136+4
	mov	r0, #1
	sub	r7, r7, #1
	ldr	r8, [ip, #68]
	clz	r7, r7
	blx	r8
	ldr	r3, [r4, #520]
	mov	r0, r4
	mov	r7, r7, lsr #5
	ldr	r1, [r3, #268]
	bl	MVC_DEC_RecycleImage
.L3102:
	ldr	r3, [r4, #520]
	mov	r0, #0
	strb	r0, [r3, #2]
	ldr	r3, [r4, #520]
	cmp	r5, r3
	movne	r7, #0
	andeq	r7, r7, #1
	cmp	r7, r0
	strne	r0, [r4, #520]
	bne	.L3126
.L3104:
	mov	r3, #0
	str	r3, [r4, #520]
.L3095:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	MVC_CheckFrameStore
	subs	r3, r0, #0
	beq	.L3129
	ldr	ip, .L3136
	movw	r2, #2003
	ldr	r1, .L3136+4
	mov	r0, #1
	ldr	r6, [ip, #68]
	blx	r6
	ldr	r1, [r5, #268]
	mov	r0, r4
	bl	MVC_DEC_RecycleImage
	mov	r0, #2
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3127:
	ldr	ip, .L3136
	mov	r3, r1
	mov	r2, r0
	ldr	r1, .L3136+8
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #2
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3094:
	mov	r0, #1
	b	.L3126
.L3129:
	mov	r2, #1
	ldrsb	r1, [r5, #6]
	ldr	r0, [r4, #120]
	bl	FSP_SetDisplay
	ldrsb	r1, [r5, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L3130
	cmp	r6, #1
	add	r3, r4, #584
	streq	r6, [r7, #244]
	mov	r2, r4
	ldr	r0, [r4, #120]
	mov	r1, #16
	str	r7, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L3131
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r7, #84]
	bcs	.L3132
.L3110:
	ldr	r2, [r4, #144]
	mov	r0, #0
	ldr	r3, [r4, #136]
	add	r2, r2, #1
	str	r2, [r4, #144]
	add	r3, r3, #2
	str	r3, [r4, #136]
	b	.L3126
.L3131:
	ldr	r3, .L3136
	mov	r2, r0
	ldr	r1, .L3136+12
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	ldrsb	r1, [r5, #6]
	mov	r2, #0
	ldr	r0, [r4, #120]
	bl	FSP_SetDisplay
	mov	r0, r4
	mov	r1, #1
	bl	MVC_ClearAll
	mvn	r0, #0
	b	.L3126
.L3103:
	ldr	r3, [r4, #520]
	mov	r2, #0
	strb	r2, [r3, #2]
	b	.L3104
.L3128:
	ldr	r3, [r4, #520]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L3133
	ldr	r3, [r4, #520]
	mov	r2, r4
	mov	r1, #16
	cmp	r5, r3
	cmpeq	r6, #1
	moveq	r3, #1
	streq	r3, [r7, #244]
	add	r3, r4, #584
	ldr	r0, [r4, #120]
	str	r7, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L3134
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r7, #84]
	bcs	.L3135
.L3101:
	ldr	r2, [r4, #144]
	mov	r7, #1
	ldr	r3, [r4, #136]
	add	r2, r2, r7
	str	r2, [r4, #144]
	add	r3, r3, #2
	str	r3, [r4, #136]
	b	.L3102
.L3132:
	mov	r1, r7
	mov	r0, r4
	bl	MVC_SetFrmRepeatCount.part.1
	b	.L3110
.L3135:
	mov	r1, r7
	mov	r0, r4
	bl	MVC_SetFrmRepeatCount.part.1
	b	.L3101
.L3134:
	ldr	r3, .L3136
	mov	r2, r0
	ldr	r1, .L3136+12
	mov	r0, #0
	mov	r5, r0
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #520]
	mov	r2, r5
	strb	r5, [r3, #2]
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	str	r5, [r4, #520]
	mov	r0, r4
	mov	r1, #1
	bl	MVC_ClearAll
	mvn	r0, #0
	b	.L3126
.L3130:
	ldr	r3, .L3136
	movw	r2, #1977
	ldr	r1, .L3136+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3126
.L3133:
	ldr	r3, .L3136
	movw	r2, #1921
	ldr	r1, .L3136+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3126
.L3137:
	.align	2
.L3136:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC400
	.word	.LC397
	.word	.LC399
	.word	.LC398
	UNWIND(.fnend)
	.size	MVC_OutputFrmToVO, .-MVC_OutputFrmToVO
	.align	2
	.global	MVC_OutputFrmFromDPB
	.type	MVC_OutputFrmFromDPB, %function
MVC_OutputFrmFromDPB:
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
	add	r4, r0, r1, lsl #2
	mov	r6, r1
	add	r4, r4, #11075584
	mov	r5, r0
	add	r4, r4, #45056
	ldr	r3, [r4, #2184]
	cmp	r3, #0
	moveq	r4, r3
	beq	.L3139
	mov	r2, #0
	strb	r2, [r3, #5]
	ldr	r1, [r4, #2184]
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #2184]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	cmp	r3, #0
	rsb	r4, r0, #0
	beq	.L3141
.L3139:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3141:
	mov	r0, r5
	mov	r1, r6
	bl	MVC_RemoveFrameStoreOutDPB
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_OutputFrmFromDPB, .-MVC_OutputFrmFromDPB
	.align	2
	.global	MVC_FlushDPB
	.type	MVC_FlushDPB, %function
MVC_FlushDPB:
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
	mov	r4, r1
	beq	.L3161
	add	r8, r5, #11075584
	add	r8, r8, #45056
	ldr	r3, [r8, #2376]
	cmp	r3, #0
	movwne	r7, #47236
	movne	r6, #0
	movtne	r7, 169
	addne	r7, r5, r7
	beq	.L3149
.L3148:
	ldr	r1, [r7, #4]!
	add	r6, r6, #1
	cmp	r1, #0
	beq	.L3147
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3147
	ldr	r3, [r1, #56]
	cmn	r4, #1
	cmpne	r3, r4
	bne	.L3147
	mov	r0, r5
	bl	MVC_UnMarkFrameStoreRef
.L3147:
	ldr	r3, [r8, #2376]
	cmp	r3, r6
	bhi	.L3148
.L3149:
	mov	r0, r5
	mov	r1, r4
	bl	MVC_RemoveUnUsedFrameStore
	ldr	r0, [r8, #2376]
	cmp	r0, #0
	beq	.L3146
	movw	r1, #47236
	mov	r7, #0
	movt	r1, 169
	add	r1, r5, r1
	mov	r2, r7
	mvn	r6, #0
.L3153:
	ldr	r3, [r1, #4]!
	add	r2, r2, #1
	cmp	r3, #0
	beq	.L3151
	ldr	r3, [r3, #56]
	cmn	r4, #1
	cmpne	r4, r3
	addeq	r7, r7, #1
	cmp	r4, r3
	cmnne	r4, #1
	movne	r6, r3
.L3151:
	cmp	r2, r0
	bne	.L3153
	cmp	r7, #0
	beq	.L3146
	adds	r8, r6, #1
	movne	r8, #1
	cmp	r4, r6
	movle	r9, #0
	andgt	r9, r8, #1
	b	.L3159
.L3160:
	subs	r7, r7, #1
	beq	.L3146
.L3159:
	cmp	r9, #0
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r1, r6
	mov	r0, r5
	beq	.L3156
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3146
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L3161
.L3156:
	mov	r1, r4
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3146
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L3161
	cmp	r4, r6
	movge	r3, #0
	andlt	r3, r8, #1
	cmp	r3, #0
	beq	.L3160
	mov	r1, r6
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3146
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	beq	.L3160
.L3161:
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3146:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_FlushDPB, .-MVC_FlushDPB
	.align	2
	.global	MVC_AdaptiveMemMark
	.type	MVC_AdaptiveMemMark, %function
MVC_AdaptiveMemMark:
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
	add	r9, r0, #11141120
	add	r8, r0, #11075584
	add	r9, r9, #8192
	movw	r7, #9784
	movt	r7, 170
	add	r8, r8, #36864
	ldr	r4, [r9, #2116]
	add	r10, r0, #11075584
	add	r7, r0, r7
	mov	r5, r0
	add	r6, r4, #2000
	add	r4, r4, #4
	add	r6, r6, #4
.L3208:
	ldr	r3, [r4]
	cmp	r3, #6
	ldrls	pc, [pc, r3, asl #2]
	b	.L3199
.L3201:
	.word	.L3200
	.word	.L3202
	.word	.L3203
	.word	.L3204
	.word	.L3205
	.word	.L3206
	.word	.L3207
.L3207:
	ldr	r2, [r4, #12]
	mov	r1, r7
	mov	r0, r5
	bl	MVC_MarkCurrPicLT
.L3199:
	add	r4, r4, #20
	cmp	r4, r6
	bne	.L3208
.L3200:
	ldrb	r3, [r8, #3480]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3216
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3206:
	mov	r0, r5
	bl	MVC_UnMarkAllSTRef
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r1, #0
	mov	r0, r5
	bl	MVC_UpdateMaxLTFrmIdx
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	mov	r3, #1
	strb	r3, [r8, #3480]
	b	.L3199
.L3205:
	mov	r0, r5
	ldr	r1, [r4, #16]
	bl	MVC_UpdateMaxLTFrmIdx
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	b	.L3199
.L3204:
	ldr	r3, [r4, #12]
	mov	r1, r7
	ldr	r2, [r4, #4]
	mov	r0, r5
	bl	MVC_MarkSTToLTRef
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	b	.L3199
.L3203:
	mov	r0, r5
	ldr	r2, [r4, #8]
	mov	r1, r7
	bl	MVC_UnMarkLTRef
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	b	.L3199
.L3202:
	mov	r0, r5
	ldr	r2, [r4, #4]
	mov	r1, r7
	bl	MVC_UnMarkSTRef
	mov	r0, r5
	bl	MVC_UpdateReflist
	b	.L3199
.L3216:
	add	r10, r10, #40960
	mov	r2, #0
	str	r2, [r9, #2120]
	movw	r3, #26758
	ldr	r1, [r10, #2164]
	movt	r3, 42
	add	r3, r1, r3
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	ldrb	r3, [r9, #1595]	@ zero_extendqisi2
	str	r2, [r9, #2816]
	cmp	r3, #1
	beq	.L3211
	bcc	.L3212
	cmp	r3, #2
	streq	r2, [r9, #2144]
	streq	r2, [r9, #2132]
	streq	r2, [r8, #3508]
	streq	r2, [r8, #3516]
.L3210:
	ldr	r1, [r9, #2192]
	mov	r0, r5
	bl	MVC_FlushDPB
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3212:
	ldr	r1, [r9, #2132]
	ldr	r2, [r9, #2140]
	ldr	r3, [r9, #2144]
	rsb	r2, r1, r2
	str	r2, [r9, #2140]
	rsb	r3, r1, r3
	str	r3, [r9, #2144]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r9, #2136]
	str	r3, [r9, #2132]
	ldr	r1, [r8, #3516]
	ldr	r2, [r8, #3504]
	ldr	r3, [r8, #3508]
	rsb	r2, r1, r2
	str	r2, [r8, #3504]
	rsb	r3, r1, r3
	str	r3, [r8, #3508]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r8, #3512]
	str	r3, [r8, #3516]
	b	.L3210
.L3211:
	str	r2, [r9, #2140]
	str	r2, [r9, #2132]
	str	r2, [r8, #3504]
	str	r2, [r8, #3516]
	b	.L3210
	UNWIND(.fnend)
	.size	MVC_AdaptiveMemMark, .-MVC_AdaptiveMemMark
	.align	2
	.global	MVC_IDRMemMarking
	.type	MVC_IDRMemMarking, %function
MVC_IDRMemMarking:
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
	add	r6, r0, #11141120
	add	r6, r6, #8192
	mov	r7, r0
	ldr	r3, [r6, #2116]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3218
	ldr	lr, [r0, #52]
	cmp	lr, #0
	beq	.L3227
	movw	r1, #47236
	mov	r2, #0
	movt	r1, 169
	add	r0, r0, #148
	add	r1, r7, r1
	mov	r4, r2
.L3226:
	ldr	r3, [r1, #4]!
	add	r2, r2, #1
	cmp	r3, #0
	beq	.L3223
	ldr	ip, [r3, #16]
	cmp	ip, #1
	streqb	ip, [r7, #6]
	ldr	ip, [r3, #56]
	ldr	r3, [r6, #2192]
	cmp	ip, r3
	streq	r4, [r0]
.L3223:
	cmp	r2, lr
	add	r0, r0, #4
	bne	.L3226
.L3227:
	add	r10, r7, #11075584
	add	r3, r10, #45056
	ldr	r9, [r3, #2376]
	cmp	r9, #0
	beq	.L3221
	movw	r4, #47236
	mov	r5, #0
	movt	r4, 169
	str	r10, [fp, #-48]
	add	r4, r7, r4
	mov	r8, r5
	mov	r10, r3
	b	.L3232
.L3230:
	cmp	r5, r9
	beq	.L3245
.L3232:
	ldr	r1, [r4, #4]!
	add	r5, r5, #1
	cmp	r1, #0
	beq	.L3230
	ldr	r0, [r1, #56]
	ldr	r2, [r6, #2192]
	cmp	r0, r2
	bne	.L3230
	strb	r8, [r1, #578]
	mov	r2, #0
	strb	r8, [r1, #577]
	ldr	r1, [r4]
	strb	r8, [r1, #614]
	strb	r8, [r1, #613]
	ldr	r1, [r4]
	strb	r8, [r1, #650]
	strb	r8, [r1, #649]
	ldr	r1, [r4]
	strb	r8, [r1, #3]
	ldr	r1, [r4]
	ldr	r0, [r7, #120]
	ldrsb	r1, [r1, #6]
	bl	FSP_SetRef
	ldr	r1, [r4]
	mov	r3, #1
	movw	r2, #47448
	movt	r2, 169
	strb	r8, [r1, #2]
	ldr	r1, [r4]
	strb	r8, [r1, #5]
	ldr	r1, [r4]
	strb	r3, [r1, #7]
	ldr	r0, [r4]
	ldr	r1, [r0, #52]
	add	r1, r7, r1
	add	r2, r1, r2
	strb	r8, [r2, #4]
	ldrsb	r1, [r0, #6]
	ldr	r0, [r7, #120]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L3231
	ldr	r1, [r4]
	ldr	r0, [r7, #120]
	ldrsb	r1, [r1, #6]
	bl	FSP_SetDisplay
.L3231:
	str	r8, [r4]
	cmp	r5, r9
	str	r8, [r4, #64]
	str	r8, [r4, #128]
	ldr	r2, [r10, #2380]
	sub	r2, r2, #1
	str	r2, [r10, #2380]
	bne	.L3232
.L3245:
	ldr	r10, [fp, #-48]
.L3221:
	mov	r0, r7
	bl	MVC_UpdateReflist
	mov	r0, r7
	bl	MVC_UpdateLTReflist
	ldr	r3, [r6, #2116]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3246
	add	r10, r10, #45056
	mov	r0, r3
	mov	r2, #1
	str	r3, [r10, #2392]
	strb	r3, [r6, #1596]
	strb	r2, [r6, #1597]
.L3233:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3246:
	add	r10, r10, #45056
	mov	r3, #0
	mov	r2, #1
	mov	r0, r3
	str	r2, [r10, #2392]
	strb	r2, [r6, #1596]
	str	r3, [r6, #2124]
	strb	r3, [r6, #1597]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3218:
	ldr	r1, [r6, #2192]
	bl	MVC_FlushDPB
	cmp	r0, #0
	addeq	r10, r7, #11075584
	beq	.L3221
.L3234:
	mvn	r0, #0
	b	.L3233
	UNWIND(.fnend)
	.size	MVC_IDRMemMarking, .-MVC_IDRMemMarking
	.align	2
	.global	MVC_Marking
	.type	MVC_Marking, %function
MVC_Marking:
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
	add	r3, r0, #11075584
	add	r5, r0, #11141120
	add	r3, r3, #36864
	add	r4, r5, #8192
	mov	r2, #0
	mov	r6, r0
	strb	r2, [r3, #3480]
	ldrb	r2, [r4, #1595]	@ zero_extendqisi2
	sub	r2, r2, #2
	clz	r2, r2
	mov	r2, r2, lsr #5
	strb	r2, [r3, #3481]
	ldrb	r3, [r4, #1598]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L3248
	ldrb	r3, [r4, #1604]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3249
	ldr	r3, [r0, #224]
	ldr	r2, [r3, #708]
	cmp	r2, #1
	beq	.L3270
.L3249:
	ldr	r3, [r4, #2116]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r4, #2128]
	beq	.L3271
	cmp	r3, #0
	bne	.L3272
.L3256:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3271:
	cmp	r3, #0
	beq	.L3256
.L3255:
	ldrb	r7, [r4, #1593]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L3273
.L3259:
	add	r5, r5, #8192
	mov	r0, #0
	ldrb	r3, [r5, #1596]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r5, #1597]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3270:
	ldr	r2, [r3, #704]
	cmp	r2, #0
	bne	.L3249
	ldr	r2, [r3, #712]
	cmp	r2, #0
	bne	.L3249
	ldr	r3, [r3, #684]
	add	r3, r3, #1024
	cmp	r3, #2048
	bls	.L3249
.L3248:
	mov	r0, r6
	bl	MVC_IDRMemMarking
	cmp	r0, #0
	bne	.L3250
.L3257:
	ldrb	r3, [r4, #1598]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L3252
	ldr	r3, [r4, #2128]
	cmp	r3, #0
	beq	.L3256
	ldr	r3, [r4, #2116]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3255
	b	.L3259
.L3273:
	mov	r0, r6
	bl	MVC_SlidingWinMark
	ldr	r3, [r4, #2116]
	strb	r7, [r3]
	strb	r7, [r4, #1596]
.L3252:
	ldr	r3, [r4, #2128]
	cmp	r3, #0
	bne	.L3259
	b	.L3256
.L3272:
	mov	r0, r6
	bl	MVC_AdaptiveMemMark
	ldr	r3, [r4, #2116]
	mov	r2, #0
	strb	r2, [r3]
	cmp	r0, r2
	beq	.L3257
.L3250:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_Marking, .-MVC_Marking
	.align	2
	.global	MVC_DirectOutput
	.type	MVC_DirectOutput, %function
MVC_DirectOutput:
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
	add	r5, r0, #11141120
	add	r5, r5, #8192
	mov	r4, r0
	ldrb	r6, [r5, #1595]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L3276
	bcc	.L3277
	cmp	r6, #2
	beq	.L3278
	mov	r6, #0
.L3275:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3278:
	ldr	r3, [r5, #2112]
	mov	r2, #3
	strb	r2, [r3, #576]
	ldrb	r2, [r5, #1593]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3296
	ldr	r1, [r0, #520]
	cmp	r1, #0
	beq	.L3297
	bl	MVC_OutputFrmToVO
	ldr	r3, [r5, #2112]
	str	r3, [r4, #520]
	str	r3, [r3, #652]
	mov	r6, r0
.L3298:
	ldr	r3, [r4, #520]
	mov	r8, #2
	ldrb	r0, [r5, #1594]	@ zero_extendqisi2
	mov	r7, #0
	add	r1, r5, #1600
	mov	r2, #504
	add	r1, r1, #8
	strb	r0, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #7]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #3]
	ldr	r3, [r4, #520]
	ldrb	r0, [r5, #1604]	@ zero_extendqisi2
	strb	r0, [r3]
	ldr	r3, [r4, #520]
	str	r7, [r3, #40]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #2164]
	str	r2, [r3, #672]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #672]
	str	r2, [r3, #600]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #648]
	ldrb	r2, [r5, #1599]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	cmp	r2, #1
	movne	r2, r7
	moveq	r2, r8
	strb	r2, [r3, #4]
.L3355:
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #2132]
	str	r2, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #2192]
	str	r2, [r3, #56]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #2196]
	str	r2, [r3, #60]
	ldrb	r8, [r4, #9]	@ zero_extendqisi2
	cmp	r8, #1
	bne	.L3275
	ldr	r3, [r4, #520]
	mov	r2, r7
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r2, r7
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #520]
	cmp	r3, r7
	mov	r6, r0
	beq	.L3308
	ldr	r3, [r5, #2112]
	mov	r2, r8
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	b	.L3308
.L3277:
	ldr	r3, [r5, #2112]
	mov	r2, #0
	strb	r2, [r3, #576]
	ldr	r1, [r0, #520]
	cmp	r1, r2
	beq	.L3279
	bl	MVC_OutputFrmToVO
	cmp	r0, #0
	bne	.L3358
.L3280:
	ldr	r3, [r4, #520]
	cmp	r3, #0
	beq	.L3279
	ldr	r3, [r5, #2112]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
.L3279:
	ldr	r3, [r5, #2112]
	mov	r0, #3
	mov	r7, #0
	add	r1, r5, #1600
	add	r1, r1, #8
	mov	r2, #504
	str	r3, [r4, #520]
	str	r3, [r3, #580]
	ldr	r3, [r4, #520]
	ldr	ip, [r5, #2112]
	str	ip, [r3, #616]
	ldr	r3, [r4, #520]
	ldr	ip, [r5, #2112]
	str	ip, [r3, #652]
	ldrb	ip, [r5, #1594]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	strb	ip, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #3]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #7]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #2164]
	mov	r2, r7
	str	r1, [r3, #600]
	str	r1, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #576]
	ldr	r3, [r4, #520]
	ldrb	r1, [r5, #1604]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r4, #520]
	ldrb	r1, [r5, #1601]	@ zero_extendqisi2
	str	r1, [r3, #40]
	ldrb	r1, [r5, #1599]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	cmp	r1, #1
	moveq	r6, #3
	strb	r6, [r3, #4]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #2132]
	str	r1, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #2192]
	str	r1, [r3, #56]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #2196]
	str	r1, [r3, #60]
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r2, r7
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #520]
	cmp	r3, r7
	mov	r6, r0
	beq	.L3308
.L3350:
	ldr	r3, [r5, #2112]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
.L3308:
	mov	r3, #0
	mov	r0, r6
	str	r3, [r4, #520]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3276:
	ldr	r3, [r5, #2112]
	mov	r2, #3
	strb	r2, [r3, #576]
	ldrb	r2, [r5, #1593]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3284
	ldr	r1, [r0, #520]
	cmp	r1, #0
	beq	.L3285
	bl	MVC_OutputFrmToVO
	ldr	r3, [r5, #2112]
	str	r3, [r4, #520]
	str	r3, [r3, #616]
	mov	r6, r0
.L3286:
	ldr	r3, [r4, #520]
	mov	r8, #1
	ldrb	r0, [r5, #1594]	@ zero_extendqisi2
	mov	r7, #0
	add	r1, r5, #1600
	mov	r2, #504
	add	r1, r1, #8
	strb	r0, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #7]
	ldr	r3, [r4, #520]
	strb	r7, [r3, #3]
	ldr	r3, [r4, #520]
	ldrb	r0, [r5, #1604]	@ zero_extendqisi2
	strb	r0, [r3]
	ldr	r3, [r4, #520]
	str	r7, [r3, #40]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #2164]
	str	r2, [r3, #636]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #636]
	str	r2, [r3, #600]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #612]
	ldrb	r3, [r5, #1599]	@ zero_extendqisi2
	ldr	r2, [r4, #520]
	rsb	r3, r8, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r2, #4]
	b	.L3355
.L3296:
	ldr	ip, [r0, #520]
	add	r1, r5, #1600
	mov	r2, #504
	add	r1, r1, #8
	cmp	ip, #0
	ldreq	r3, [r5, #2112]
	streq	r3, [r0, #520]
	streq	r3, [r3, #652]
	ldreq	ip, [r0, #520]
	add	r0, ip, #72
	ldr	r3, [ip, #80]
	ldrd	r6, [ip, #88]
	ldrd	r8, [ip, #96]
	ldr	r10, [ip, #84]
	str	r3, [fp, #-48]
	bl	memcpy
	movw	r2, #9808
	ldr	r3, [fp, #-48]
	mov	r0, r2
	movt	r2, 170
	add	r2, r4, r2
	movt	r0, 170
	ldr	r0, [r4, r0]
	and	r1, r3, r10
	ldr	r2, [r2, #4]
	mov	ip, #2
	and	r0, r0, r2
	adds	r2, r1, #1
	movw	r1, #9824
	movne	r2, #1
	cmn	r0, #1
	movt	r1, 170
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r4, #520]
	strne	r3, [r2, #80]
	movw	r3, #9824
	movt	r3, 170
	add	r3, r4, r3
	strne	r10, [r2, #84]
	ldrd	r2, [r3, #-8]
	ldr	r0, [r4, #520]
	cmp	r3, r7
	cmpeq	r2, r6
	movhi	r2, r6
	movhi	r3, r7
	strd	r2, [r0, #88]
	ldrd	r2, [r4, r1]
	ldr	r0, [r4, #520]
	cmp	r3, r9
	cmpeq	r2, r8
	movhi	r2, r8
	movhi	r3, r9
	strd	r2, [r0, #96]
	mov	r0, #3
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r5, #1594]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #2]
	ldr	r2, [r4, #520]
	ldrb	r1, [r5, #1604]	@ zero_extendqisi2
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r4, #520]
	strb	ip, [r3, #648]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #576]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #2164]
	str	r2, [r3, #672]
	ldr	r2, [r4, #520]
	ldr	r3, [r2, #672]
	ldr	r1, [r2, #636]
	add	r3, r3, r1
	mov	r3, r3, lsr #1
	str	r3, [r2, #600]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #600]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #652]
	str	r2, [r3, #580]
	ldrb	r3, [r5, #1599]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #520]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	beq	.L3356
.L3307:
	strb	r2, [r3, #4]
	mov	r2, #0
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #2132]
	str	r1, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r2, #0
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #520]
	cmp	r3, #0
	mov	r6, r0
	bne	.L3350
	b	.L3308
.L3284:
	ldr	ip, [r0, #520]
	add	r1, r5, #1600
	mov	r2, #504
	add	r1, r1, #8
	cmp	ip, #0
	ldreq	r3, [r5, #2112]
	streq	r3, [r0, #520]
	streq	r3, [r3, #616]
	ldreq	ip, [r0, #520]
	add	r0, ip, #72
	ldr	r3, [ip, #80]
	ldrd	r8, [ip, #88]
	ldrd	r6, [ip, #96]
	ldr	r10, [ip, #84]
	str	r3, [fp, #-48]
	bl	memcpy
	movw	r2, #9808
	ldr	r3, [fp, #-48]
	mov	r0, r2
	movt	r2, 170
	add	r2, r4, r2
	movt	r0, 170
	ldr	r0, [r4, r0]
	and	r1, r3, r10
	ldr	r2, [r2, #4]
	mov	ip, #1
	and	r0, r0, r2
	adds	r2, r1, #1
	movw	r1, #9824
	movne	r2, #1
	cmn	r0, #1
	movt	r1, 170
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r4, #520]
	strne	r3, [r2, #80]
	movw	r3, #9824
	movt	r3, 170
	add	r3, r4, r3
	strne	r10, [r2, #84]
	ldrd	r2, [r3, #-8]
	ldr	r0, [r4, #520]
	cmp	r3, r9
	cmpeq	r2, r8
	movhi	r2, r8
	movhi	r3, r9
	strd	r2, [r0, #88]
	ldrd	r2, [r4, r1]
	ldr	r0, [r4, #520]
	cmp	r3, r7
	cmpeq	r2, r6
	movhi	r2, r6
	movhi	r3, r7
	strd	r2, [r0, #96]
	mov	r0, #3
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r5, #1594]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #2]
	ldr	r2, [r4, #520]
	ldrb	r1, [r5, #1604]	@ zero_extendqisi2
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r4, #520]
	strb	ip, [r3, #612]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #576]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #2164]
	str	r2, [r3, #636]
	ldr	r2, [r4, #520]
	ldr	r3, [r2, #672]
	ldr	r1, [r2, #636]
	add	r3, r3, r1
	mov	r3, r3, lsr ip
	str	r3, [r2, #600]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #600]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #616]
	str	r2, [r3, #580]
	ldrb	r3, [r5, #1599]	@ zero_extendqisi2
	cmp	r3, ip
	ldr	r3, [r4, #520]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	bne	.L3307
.L3356:
	orr	r2, r2, ip
	b	.L3307
.L3358:
	ldr	r1, .L3359
	movw	r3, #2554
	str	r0, [sp]
	mov	r0, #22
	ldr	r2, .L3359+4
	ldr	r7, [r1, #68]
	ldr	r1, .L3359+8
	blx	r7
	b	.L3280
.L3297:
	ldr	r3, [r5, #2112]
	mov	r6, r1
	str	r3, [r0, #520]
	str	r3, [r3, #652]
	b	.L3298
.L3285:
	ldr	r3, [r5, #2112]
	mov	r6, r1
	str	r3, [r0, #520]
	str	r3, [r3, #616]
	b	.L3286
.L3360:
	.align	2
.L3359:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+248
	.word	.LC401
	UNWIND(.fnend)
	.size	MVC_DirectOutput, .-MVC_DirectOutput
	.align	2
	.global	MVC_DEC_GetRemainImg
	.type	MVC_DEC_GetRemainImg, %function
MVC_DEC_GetRemainImg:
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
	add	r6, r0, #11075584
	add	r6, r6, #45056
	mov	r5, r0
	ldr	r3, [r6, #2376]
	cmp	r3, #0
	beq	.L3375
	movw	r8, #47236
	mov	r4, #0
	movt	r8, 169
	add	r8, r0, r8
	mov	r7, r4
	mov	r9, r8
	b	.L3364
.L3363:
	ldr	r3, [r6, #2376]
	cmp	r3, r7
	bls	.L3402
.L3364:
	ldr	r3, [r9, #4]!
	add	r7, r7, #1
	cmp	r3, #0
	beq	.L3363
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3363
	ldrsb	r1, [r3, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L3363
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	sub	r3, r3, #1
	cmp	r3, #1
	ldr	r3, [r6, #2376]
	addls	r4, r4, #1
	cmp	r3, r7
	bhi	.L3364
.L3402:
	cmp	r4, #0
	beq	.L3365
	mvn	r7, #0
	b	.L3368
.L3366:
	ldr	r1, [r5, r3, asl #2]
	bl	MVC_OutputFrmToVO
	subs	r4, r4, #1
	mov	r7, r0
	beq	.L3400
.L3368:
	sub	r3, fp, #44
	sub	r2, fp, #40
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	movw	r3, #28194
	mov	r2, r4
	cmn	r1, #1
	movt	r3, 42
	mov	r0, r5
	add	r3, r1, r3
	bne	.L3366
.L3400:
	ldr	r3, [r6, #2376]
	cmp	r3, #0
	beq	.L3362
.L3367:
	mov	r4, #0
	b	.L3371
.L3370:
	ldr	r3, [r6, #2376]
	cmp	r3, r4
	bls	.L3362
.L3371:
	ldr	r1, [r8, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3370
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3370
	mov	r0, r5
	bl	MVC_UnMarkFrameStoreRef
	ldr	r3, [r6, #2376]
	cmp	r3, r4
	bhi	.L3371
.L3362:
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
	cmp	r7, #0
	bne	.L3373
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3365:
	cmp	r3, #0
	mvnne	r7, #0
	bne	.L3367
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
.L3373:
	add	r0, r5, #584
	bl	GetVoLastImageID
	mov	r7, r0
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3375:
	mvn	r7, #0
	b	.L3362
	UNWIND(.fnend)
	.size	MVC_DEC_GetRemainImg, .-MVC_DEC_GetRemainImg
	.align	2
	.global	MVC_InitDPB
	.type	MVC_InitDPB, %function
MVC_InitDPB:
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
	beq	.L3420
	bl	MVC_ClearAllSlice
	movw	r7, #47240
	movw	r6, #47368
	movw	r5, #47304
	movt	r7, 169
	movt	r6, 169
	movt	r5, 169
	mov	r8, #0
	add	r7, r4, r7
	add	r6, r4, r6
	add	r5, r4, r5
	mov	r9, r8
.L3408:
	ldr	r3, [r7]
	mov	r2, #1
	add	r8, r8, r2
	cmp	r3, #0
	beq	.L3405
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3405:
	ldr	r3, [r5]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3406
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3406:
	ldr	r3, [r6]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3407
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3407:
	cmp	r8, #16
	str	r9, [r6], #4
	mov	r2, #0
	str	r9, [r5], #4
	str	r9, [r7], #4
	bne	.L3408
	ldr	r3, [r4, #44]
	add	r5, r4, #11075584
	add	r6, r5, #45056
	str	r3, [r6, #2376]
	str	r2, [r6, #2380]
	str	r2, [r6, #2384]
	str	r2, [r6, #2388]
	str	r2, [r6, #2392]
	ldr	r1, [r4, #520]
	cmp	r1, r2
	ldreq	r7, .L3438
	beq	.L3410
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3411
	ldr	r7, .L3438
.L3415:
	add	r3, r4, #11141120
	add	r3, r3, #8192
	ldr	r3, [r3, #2112]
	cmp	r3, #0
	beq	.L3413
	ldrsb	r1, [r3, #6]
	mov	r2, #1
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3413:
	mov	r3, #0
	str	r3, [r4, #520]
.L3410:
	movw	r0, #47452
	ldr	r3, [r7, #48]
	mov	r2, #344
	mov	r1, #0
	movt	r0, 169
	add	r0, r4, r0
	blx	r3
	ldr	ip, [r6, #2376]
	mov	r0, #0
	add	r3, r4, #144
	add	r1, r4, #216
	mov	r2, r0
	str	ip, [r6, #2604]
	str	r0, [r6, #2608]
.L3417:
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L3417
	add	r2, r4, #252
	add	r3, r4, #384
	mov	r0, #0
.L3418:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L3418
	add	r2, r5, #40960
	add	r4, r4, #516
	mov	r0, r1
	str	r1, [r2, #568]
.L3419:
	str	r0, [r3, #4]!
	cmp	r3, r4
	mov	r2, #0
	bne	.L3419
	add	r5, r5, #40960
	mov	r0, r2
	str	r2, [r5, #572]
.L3404:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3411:
	mov	r0, r4
	ldr	r7, .L3438
	bl	MVC_OutputFrmToVO
	cmp	r0, #0
	bne	.L3437
.L3414:
	ldr	r3, [r4, #520]
	cmp	r3, #0
	bne	.L3415
	b	.L3410
.L3437:
	str	r0, [sp]
	movw	r3, #5969
	ldr	r2, .L3438+4
	mov	r0, #22
	ldr	r8, [r7, #68]
	ldr	r1, .L3438+8
	blx	r8
	b	.L3414
.L3420:
	mvn	r0, #0
	b	.L3404
.L3439:
	.align	2
.L3438:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+268
	.word	.LC402
	UNWIND(.fnend)
	.size	MVC_InitDPB, .-MVC_InitDPB
	.align	2
	.global	MVC_ClearDPB
	.type	MVC_ClearDPB, %function
MVC_ClearDPB:
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
	bl	MVC_FlushDPB
	cmp	r0, #0
	bne	.L3449
.L3441:
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L3442
	ldr	ip, .L3450
	movw	r3, #397
	ldr	r2, .L3450+4
	mov	r0, #22
	ldr	r1, .L3450+8
	ldr	r5, [ip, #68]
	blx	r5
.L3442:
	mov	r0, #0
	strb	r0, [r4, #6]
	str	r0, [r4, #220]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3449:
	ldr	ip, .L3450
	mov	r3, #392
	ldr	r2, .L3450+4
	mov	r0, #22
	ldr	r1, .L3450+12
	ldr	r5, [ip, #68]
	blx	r5
	b	.L3441
.L3451:
	.align	2
.L3450:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+280
	.word	.LC404
	.word	.LC403
	UNWIND(.fnend)
	.size	MVC_ClearDPB, .-MVC_ClearDPB
	.align	2
	.global	MVC_DecVDM
	.type	MVC_DecVDM, %function
MVC_DecVDM:
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
	add	r6, r0, #11141120
	add	r5, r6, #8192
	mov	r4, r0
	ldrb	r3, [r5, #1595]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3453
	ldrb	r3, [r5, #1593]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3453
.L3454:
	ldr	r3, [r4, #108]
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ubfx	r7, r3, #16, #2
	cmp	r7, r2
	beq	.L3455
	sub	r2, r2, #2
	cmp	r2, #1
	cmpls	r7, #1
	bls	.L3512
.L3455:
	uxtb	r3, r7
	strb	r3, [r4, #8]
	cmp	r3, #2
	beq	.L3458
	cmp	r3, #3
	beq	.L3459
	cmp	r3, #1
	beq	.L3513
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3514
.L3466:
	ldr	r3, [r4, #64]
.L3462:
	ldrb	r2, [r5, #1605]	@ zero_extendqisi2
	strb	r2, [r4, #11]
.L3467:
	cmp	r3, #0
	beq	.L3510
	ldrb	r3, [r5, #1604]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3515
	cmp	r3, #1
	bne	.L3470
	ldr	r2, [r5, #2192]
	cmp	r2, #0
	streqb	r3, [r4, #7]
.L3470:
	ldr	r1, .L3518
	mov	r0, #2
	ldr	r2, [r4, #88]
	ldrb	r3, [r5, #1595]	@ zero_extendqisi2
	ldr	r7, [r1, #68]
	sub	r2, r2, #1
	ldr	r1, .L3518+4
	blx	r7
	ldr	r2, [r5, #2184]
	ldr	r1, [r5, #2180]
	mov	r3, #1
	strb	r3, [r5, #3386]
	add	r3, r6, #12288
	str	r2, [r5, #4044]
	str	r1, [r5, #4048]
	ldr	r2, [r4, #64]
	str	r2, [r3, #152]
	ldr	r0, [r4, #88]
	cmp	r0, #0
	beq	.L3507
	ldrb	r1, [r5, #1604]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L3471
	ldr	r2, .L3518+8
	ldr	r7, [r2]
	cmp	r7, #0
	beq	.L3472
	ldr	r2, [r3, #156]
	cmp	r2, #0
	beq	.L3481
.L3474:
	ldr	r3, [r2, #8]
	ldr	r0, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3474
.L3473:
	sub	r2, fp, #28
	mov	r3, #4
	ldr	r0, [r4, #120]
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	r7
	ldr	r2, [r4, #224]
.L3475:
	movw	r3, #11576
	movt	r3, 170
	add	r3, r4, r3
	str	r3, [r4, #228]
	ldr	r1, [r2, #900]
	cmp	r1, #1
	beq	.L3516
	cmp	r1, #2
	beq	.L3517
.L3478:
	ldr	r3, [r2, #676]
	add	r6, r6, #12288
	mov	r0, #0
	str	r3, [r6, #416]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3453:
	ldr	r3, [r4, #140]
	ldr	r1, [r4, #144]
	add	r3, r3, #1
	ldr	r2, [r4, #224]
	cmp	r3, r1
	movlt	r3, r1
	str	r3, [r4, #140]
	str	r3, [r2, #600]
	ldr	r3, [r4, #140]
	ldr	r1, [r4, #144]
	rsb	r3, r1, r3
	str	r3, [r2, #604]
	b	.L3454
.L3512:
	ldr	ip, .L3518
	mov	r2, r7
	ldr	r1, .L3518+12
	mov	r0, #2
	ldr	r5, [ip, #68]
	blx	r5
	strb	r7, [r4, #8]
.L3459:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mov	r0, r4
	mvn	r1, #0
	bl	MVC_ClearDPB
	mvn	r0, #0
.L3507:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3513:
	ldrb	r3, [r5, #1604]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3466
	ldr	r3, [r5, #2128]
	cmp	r3, #0
	beq	.L3463
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3466
.L3479:
	ldrb	r2, [r5, #1605]	@ zero_extendqisi2
	ldr	r3, [r4, #64]
	strb	r2, [r4, #11]
	b	.L3467
.L3458:
	ldrb	r3, [r5, #1604]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3463
	ldr	r3, [r4, #64]
	cmp	r3, #0
	beq	.L3462
	ldr	r2, [r4, #544]
	ldr	r2, [r2, #48]
	cmp	r2, #0
	beq	.L3462
.L3463:
	mov	r3, #1
	mov	r0, r4
	strb	r3, [r5, #1599]
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3507
.L3471:
	add	r3, r4, #11075584
	add	r3, r3, #45056
	ldr	r3, [r3, #2380]
	cmp	r3, #0
	bne	.L3472
	ldr	r2, [r4, #224]
	ldr	r3, [r2, #12]
	cmp	r3, #2
	beq	.L3475
.L3510:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3507
.L3514:
	ldrb	r3, [r5, #1604]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3466
	b	.L3479
.L3515:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3470
	ldr	r3, [r4, #224]
	ldr	r7, [r3, #12]
	cmp	r7, #0
	bne	.L3470
	ldr	r1, .L3518
	mov	r0, #1
	ldr	r3, [r5, #2128]
	ldr	r2, [r5, #2132]
	ldr	r6, [r1, #68]
	ldr	r1, .L3518+16
	blx	r6
	mov	r0, r4
	bl	MVC_ClearCurrPic
	ldr	r3, [r5, #2112]
	ldr	r0, [r4, #120]
	mov	r2, r7
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L3507
.L3472:
	ldr	r2, [r4, #224]
	b	.L3475
.L3516:
	cmp	r3, #0
	beq	.L3478
	ldrb	r3, [r5, #1604]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3478
	mov	r2, #0
	str	r2, [r4, #228]
	ldr	r3, [r5, #2112]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	b	.L3510
.L3517:
	ldr	r1, [r2, #904]
	cmp	r3, #0
	cmpne	r1, #0
	ble	.L3478
	ldrb	r3, [r5, #1604]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3478
	mov	r2, #0
	str	r2, [r4, #228]
	ldr	r3, [r5, #2112]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	ldr	r2, [r4, #224]
	mov	r0, r4
	ldr	r3, [r2, #904]
	sub	r3, r3, #1
	str	r3, [r2, #904]
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3507
.L3481:
	mov	r1, r2
	b	.L3473
.L3519:
	.align	2
.L3518:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC407
	.word	g_event_report
	.word	.LC405
	.word	.LC406
	UNWIND(.fnend)
	.size	MVC_DecVDM, .-MVC_DecVDM
	.align	2
	.global	MVC_FlushDecoder
	.type	MVC_FlushDecoder, %function
MVC_FlushDecoder:
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
	add	r3, r0, #11075584
	mov	r1, #1
	add	r3, r3, #40960
	mov	ip, #0
	strb	r1, [r3, #525]
	str	ip, [r3, #576]
	strb	r1, [r0]
	bl	MVC_DecVDM
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	ip, .L3522
	movw	r3, #12836
	ldr	r2, .L3522+4
	mov	r0, #22
	ldr	r1, .L3522+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L3523:
	.align	2
.L3522:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+296
	.word	.LC408
	UNWIND(.fnend)
	.size	MVC_FlushDecoder, .-MVC_FlushDecoder
	.align	2
	.global	MVC_ReceivePacket
	.type	MVC_ReceivePacket, %function
MVC_ReceivePacket:
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
	ldr	r6, .L3587
	ldr	r3, [r1, #8]
	mov	r5, r1
	ldr	r2, [r1, #4]
	mov	r4, r0
	ldr	r1, [r1, #12]
	mov	r0, #7
	add	r7, r4, #11141120
	ldr	r8, [r6, #68]
	str	r1, [sp]
	ldr	r1, .L3587+4
	blx	r8
	add	r3, r7, #12288
	mov	r2, #0
	str	r2, [r3, #424]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #868]
	cmp	r2, #1
	beq	.L3582
.L3525:
	ldr	r3, [r4, #232]
	cmp	r3, #0
	beq	.L3545
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3583
.L3528:
	ldr	r1, .L3587+8
	mov	r0, #1
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L3545
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L3545:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3532
	ldr	r3, [r5, #4]
	cmp	r3, #0
	beq	.L3532
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3532
	ldrb	r3, [r4, #937]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3548
	mov	r2, r4
	mov	r3, #1
	b	.L3535
.L3534:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L3546
.L3535:
	ldrb	r1, [r2, #1025]	@ zero_extendqisi2
	add	r2, r2, #88
	cmp	r1, #0
	bne	.L3534
	mov	r1, r3
.L3533:
	mov	r2, #88
	cmn	r1, #1
	mla	r3, r2, r3, r4
	mov	r0, #1
	strb	r0, [r3, #937]
	beq	.L3546
	mul	r3, r2, r1
	mov	r1, #0
	add	r2, r3, #936
	add	r3, r4, r3
	add	r2, r4, r2
	str	r2, [r4, #232]
	ldr	r2, [r5, #4]
	str	r2, [r3, #944]
	ldr	r2, [r5, #12]
	str	r2, [r3, #948]
	ldr	r2, [r5, #8]
	str	r2, [r3, #952]
	ldr	r3, [r4, #232]
	str	r1, [r3, #24]
	ldr	r3, [r4, #232]
	ldr	r2, [r5, #16]
	str	r2, [r3, #32]
	ldrd	r2, [r5, #24]
	ldr	ip, [r4, #232]
	strd	r2, [ip, #80]
	ldr	r3, [r4, #232]
	str	r0, [r3, #68]
	ldr	r3, [r4, #232]
	strb	r1, [r3]
	ldr	r3, [r4, #232]
	ldrb	r2, [r5]	@ zero_extendqisi2
	strb	r2, [r3, #3]
	ldr	r3, [r4, #232]
	b	.L3538
.L3583:
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bhi	.L3528
	ldrb	r1, [r3, #3]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L3529
	b	.L3528
.L3582:
	ldr	r3, [r3, #908]
	cmp	r3, #0
	beq	.L3525
	ldr	r3, [r4, #232]
	cmp	r3, #0
	ldrneb	r2, [r5]	@ zero_extendqisi2
	beq	.L3545
.L3529:
	strb	r2, [r3, #3]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #868]
	cmp	r2, #1
	beq	.L3584
.L3540:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3541
	ldr	r2, [r5, #4]
	cmp	r2, #0
	beq	.L3541
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3541
	ldr	r3, [r4, #232]
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bls	.L3585
.L3542:
	mov	r2, #1
	strb	r2, [r3, #3]
	ldr	r1, [r5, #16]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3587+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3579
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	r5
.L3579:
	ldr	r3, [r4, #232]
.L3538:
	ldrb	r0, [r3, #3]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3532:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L3587+16
	blx	r3
	ldr	r1, [r5, #16]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3587+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3581
.L3580:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	r5
.L3581:
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3541:
	ldr	r3, [r4, #232]
	b	.L3542
.L3584:
	ldr	r3, [r3, #908]
	cmp	r3, #0
	bne	.L3579
	b	.L3540
.L3585:
	mov	ip, r1, asl #5
	mov	r0, #0
	sub	r1, ip, r1, asl #2
	add	r3, r3, r1
	str	r2, [r3, #8]
	ldr	r3, [r4, #232]
	ldr	ip, [r5, #12]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #12]
	ldr	r3, [r4, #232]
	ldr	ip, [r5, #8]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #16]
	ldr	r3, [r4, #232]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r0, [r3, #24]
	ldr	r3, [r4, #232]
	ldr	r0, [r5, #16]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r0, [r3, #32]
	ldr	r2, [r4, #232]
	ldr	r3, [r2, #68]
	add	r3, r3, #1
	str	r3, [r2, #68]
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #12]
	cmp	r2, #4096
	bcc	.L3586
.L3543:
	add	r7, r7, #12288
	mov	r2, #1
	str	r2, [r7, #424]
	b	.L3538
.L3586:
	mov	r0, r4
	bl	MVC_CombinePacket.part.10
	ldr	r3, [r4, #232]
	b	.L3543
.L3546:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L3587+20
	blx	r3
	mov	r0, r4
	bl	MVC_ClearAllNal
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r3, .L3587+12
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L3580
	b	.L3581
.L3548:
	mov	r1, r3
	b	.L3533
.L3588:
	.align	2
.L3587:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC409
	.word	.LC410
	.word	g_event_report
	.word	.LC412
	.word	.LC411
	UNWIND(.fnend)
	.size	MVC_ReceivePacket, .-MVC_ReceivePacket
	.align	2
	.global	MVC_ClearAll
	.type	MVC_ClearAll, %function
MVC_ClearAll:
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
	ldr	r9, .L3620
	mov	r8, r0
	mov	r4, r1
	mov	r0, #22
	ldr	r1, .L3620+4
	ldr	r3, [r9, #68]
	blx	r3
	mov	r0, r8
	bl	MVC_ClearCurrPic
	mov	r0, r8
	bl	MVC_ClearAllNal
	mov	r0, r8
	bl	MVC_InitDPB
	cmp	r0, #0
	bne	.L3619
.L3590:
	cmp	r4, #0
	beq	.L3591
	add	r1, r8, #584
	ldr	r0, [r8, #120]
	bl	FSP_ClearNotInVoQueue
.L3592:
	movw	r4, #47800
	mov	r7, #0
	movt	r4, 169
	add	r4, r8, r4
	mov	r10, r7
.L3595:
	add	r5, r4, #280
	add	r6, r4, #296
	mov	r3, #1
	mvn	ip, #0
	mov	r0, #18
	mov	r1, #16
	mov	r2, #2
	strb	r10, [r4, #1]
	strb	r10, [r4, #2]
	strb	r10, [r4, #3]
	str	r10, [r4, #28]
	str	r10, [r4, #20]
	str	r10, [r4, #32]
	strb	r10, [r4, #5]
	str	r7, [r4, #268]
	str	r4, [r4, #652]
	str	r4, [r4, #616]
	str	r4, [r4, #580]
	strb	r10, [r4, #576]
	str	ip, [r4, #24]
	strb	r3, [r4, #7]
	strb	r3, [r4, #612]
	str	r0, [r4, #48]
	str	r1, [r4, #52]
	strb	r2, [r4, #648]
.L3594:
	ldr	r1, [r5, #4]!
	cmp	r1, #0
	beq	.L3593
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	str	r10, [r5]
.L3593:
	cmp	r5, r6
	bne	.L3594
	add	r7, r7, #1
	add	r4, r4, #688
	cmp	r7, #40
	bne	.L3595
	movw	r4, #10008
	movw	r5, #10024
	movt	r4, 170
	movt	r5, 170
	add	r4, r8, r4
	add	r5, r8, r5
	mov	r6, #0
.L3597:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L3596
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	str	r6, [r4]
.L3596:
	cmp	r4, r5
	bne	.L3597
	ldr	r3, [r8, #60]
	cmp	r3, #0
	beq	.L3601
	mov	r4, #0
	add	r5, r8, #524
	mov	r6, r4
.L3600:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3599
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	str	r6, [r5]
	ldr	r3, [r8, #60]
.L3599:
	cmp	r3, r4
	bhi	.L3600
.L3601:
	add	r5, r8, #11075584
	movw	r0, #41480
	mov	r4, #0
	add	r3, r5, #45056
	strb	r4, [r8, #4]
	add	r5, r5, #40960
	strb	r4, [r8, #9]
	movt	r0, 169
	strb	r4, [r8, #6]
	add	r0, r8, r0
	strb	r4, [r8, #7]
	mov	r1, r4
	strb	r4, [r8, #3]
	movw	r2, #1656
	str	r4, [r8, #60]
	str	r4, [r8, #64]
	str	r4, [r8, #104]
	str	r4, [r8, #220]
	str	r4, [r8, #232]
	add	r8, r8, #11141120
	add	r8, r8, #8192
	strb	r4, [r3, #132]
	ldr	r6, [r9, #48]
	strb	r4, [r5, #2224]
	strb	r4, [r3, #133]
	strb	r4, [r5, #2225]
	blx	r6
	mov	r2, #2
	mov	r3, #1
	strb	r2, [r5, #520]
	strb	r3, [r5, #525]
	mov	r0, r4
	mov	r3, #256
	strb	r4, [r8, #1592]
	strb	r4, [r8, #2808]
	str	r4, [r8, #2812]
	str	r3, [r8, #2816]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3591:
	add	r0, r8, #584
	bl	ResetVoQueue
	ldr	r0, [r8, #120]
	bl	FSP_EmptyInstance
	b	.L3592
.L3619:
	ldr	r5, [r9, #68]
	movw	r3, #422
	ldr	r2, .L3620+8
	mov	r0, #22
	ldr	r1, .L3620+12
	blx	r5
	b	.L3590
.L3621:
	.align	2
.L3620:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC413
	.word	.LANCHOR0+316
	.word	.LC404
	UNWIND(.fnend)
	.size	MVC_ClearAll, .-MVC_ClearAll
	.align	2
	.global	MVC_InsertFrmInDPB
	.type	MVC_InsertFrmInDPB, %function
MVC_InsertFrmInDPB:
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
	add	r3, r0, #11075584
	add	r3, r3, #45056
	mov	r4, r2
	ldrb	r9, [r4, #3]	@ zero_extendqisi2
	mov	r5, r0
	ldr	r3, [r3, #2380]
	mov	r6, r1
	cmp	r3, #0
	ldreq	r2, .L3724
	streq	r3, [r2, #-1884]
	cmp	r9, #1
	beq	.L3625
	bcc	.L3626
	cmp	r9, #2
	beq	.L3627
	ldr	r3, .L3724+4
	mov	r2, r9
	ldr	r1, .L3724+8
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	mov	r1, #1
	bl	MVC_ClearAll
	mov	r0, #0
.L3631:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3627:
	ldr	r3, [r4, #520]
	mov	r2, #3
	strb	r2, [r3, #576]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r3, r1, asl #2
	beq	.L3647
	add	r8, r0, r3
	add	r2, r8, #11075584
	str	r2, [fp, #-64]
	add	r7, r2, #45056
	ldr	r2, [r7, #2184]
	cmp	r2, #0
	beq	.L3647
	strb	r9, [r2, #648]
	ldr	r3, [r7, #2184]
	ldr	r2, [r4, #520]
	str	r2, [r3, #652]
	ldr	r3, [r7, #2184]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #649]
	ldr	r3, [r7, #2184]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #650]
	ldr	r3, [r7, #2184]
	ldr	r2, [r4, #552]
	str	r2, [r3, #664]
	ldr	r3, [r7, #2184]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #651]
	ldr	r3, [r7, #2184]
	ldr	r2, [r4, #572]
	str	r2, [r3, #672]
	ldr	r3, [r7, #2184]
	ldr	r1, [r3, #636]
	ldr	r2, [r3, #672]
	add	r2, r2, r1
	str	r2, [r3, #600]
	str	r2, [r3, #44]
	add	r1, r4, #16
	ldr	r2, [r7, #2184]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r7, #2184]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r7, #2184]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	orreq	r2, r2, #2
	strb	r2, [r3, #4]
	mov	r2, #504
	ldr	r3, [r7, #2184]
	add	r0, r3, #72
	ldrd	r8, [r3, #88]
	ldr	ip, [r3, #84]
	ldr	r10, [r3, #80]
	strd	r8, [fp, #-52]
	ldrd	r8, [r3, #96]
	str	ip, [fp, #-68]
	strd	r8, [fp, #-60]
	bl	memcpy
	ldr	ip, [fp, #-68]
	ldr	r1, [r4, #24]
	ldr	r2, [r4, #28]
	and	r3, r10, ip
	adds	r3, r3, #1
	ldrd	r8, [fp, #-52]
	and	r2, r2, r1
	movne	r3, #1
	cmn	r2, #1
	movne	r3, #0
	cmp	r3, #0
	ldrne	r3, [r7, #2184]
	movne	r2, ip
	strne	r10, [r3, #80]
	strne	r2, [r3, #84]
	ldrd	r2, [r4, #32]
	ldr	r1, [r7, #2184]
	cmp	r3, r9
	cmpeq	r2, r8
	movhi	r2, r8
	movhi	r3, r9
	ldrd	r8, [fp, #-60]
	strd	r2, [r1, #88]
	ldrd	r2, [r4, #40]
	ldr	r1, [r7, #2184]
	cmp	r3, r9
	cmpeq	r2, r8
	movhi	r3, r9
	movhi	r2, r8
	strd	r2, [r1, #96]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3659
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3659
.L3660:
	ldr	r3, [fp, #-64]
	add	r8, r3, #45056
	ldr	r2, [r8, #2184]
	ldrb	r3, [r2, #651]	@ zero_extendqisi2
	ldrb	r1, [r2, #615]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r8, #2184]
	ldr	r2, [r4, #568]
	str	r2, [r3, #668]
	ldr	r2, [r8, #2184]
	ldr	r3, [r2, #668]
	ldr	r1, [r2, #632]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r2, #36]
	ldr	r0, [r8, #2184]
	bl	MVC_CombineFldsToFrm
	ldr	r2, [r8, #2184]
	ldrb	r1, [r4, #11]	@ zero_extendqisi2
	movw	r3, #28282
	movt	r3, 42
	strb	r1, [r2, #13]
	ldrb	r1, [r4, #10]	@ zero_extendqisi2
	ldr	r2, [r8, #2184]
	strb	r1, [r2, #11]
	ldr	r2, [r8, #2184]
	ldr	r1, [r2, #52]
	ldr	r2, [r2, #664]
	add	r3, r1, r3
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3646
.L3626:
	add	r3, r0, r1, lsl #2
	ldr	r2, [r4, #520]
	add	r10, r3, #11075584
	mov	r3, #3
	add	r7, r10, #45056
	str	r2, [r7, #2184]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r2, #1]
	ldr	r2, [r7, #2184]
	strb	r3, [r2, #2]
	ldr	r1, [r4, #520]
	ldr	r2, [r7, #2184]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #520]
	ldr	r2, [r7, #2184]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	ldr	r2, [r7, #2184]
	cmp	r1, #0
	beq	.L3722
.L3628:
	strb	r3, [r2, #3]
	add	r1, r4, #16
	ldr	r3, [r7, #2184]
	mov	r2, #504
	ldr	r0, [r4, #596]
	mov	r8, #0
	str	r0, [r3, #48]
	ldr	r0, [r7, #2184]
	add	r0, r0, #72
	bl	memcpy
	ldr	r2, [r7, #2184]
	ldr	r0, [r4, #572]
	add	r3, r10, #45056
	mov	lr, #1
	ldr	r1, .L3724
	mov	ip, #2
	str	r0, [r2, #600]
	str	r0, [r2, #44]
	ldr	r2, [r7, #2184]
	ldr	r0, [r4, #520]
	str	r0, [r2, #652]
	str	r0, [r2, #616]
	str	r0, [r2, #580]
	ldr	r2, [r7, #2184]
	ldr	r0, [r4, #532]
	str	r0, [r2, #28]
	ldr	r2, [r7, #2184]
	ldr	r0, [r4, #528]
	str	r0, [r2, #20]
	ldr	r2, [r7, #2184]
	strb	r8, [r2, #576]
	ldr	r2, [r7, #2184]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	strb	r0, [r2, #577]
	ldr	r2, [r7, #2184]
	ldrb	r0, [r4, #5]	@ zero_extendqisi2
	strb	r0, [r2, #578]
	ldr	r2, [r7, #2184]
	ldrb	r0, [r4, #12]	@ zero_extendqisi2
	strb	r0, [r2, #579]
	strb	r0, [r2]
	ldr	r2, [r7, #2184]
	ldrb	r0, [r4, #9]	@ zero_extendqisi2
	str	r0, [r2, #40]
	ldr	r2, [r7, #2184]
	ldr	r0, [r4, #540]
	str	r0, [r2, #32]
	ldr	r0, [r4, #544]
	ldr	r2, [r7, #2184]
	str	r0, [r2, #592]
	ldr	r0, [r4, #548]
	ldr	r2, [r7, #2184]
	str	r0, [r2, #628]
	ldr	r0, [r4, #552]
	ldr	r2, [r7, #2184]
	str	r0, [r2, #664]
	ldr	r0, [r4, #556]
	ldr	r2, [r7, #2184]
	str	r0, [r2, #36]
	ldr	r0, [r4, #560]
	ldr	r2, [r7, #2184]
	str	r0, [r2, #596]
	ldr	r0, [r4, #564]
	ldr	r2, [r7, #2184]
	str	r0, [r2, #632]
	ldr	r0, [r4, #568]
	ldr	r2, [r7, #2184]
	str	r0, [r2, #668]
	ldrb	r2, [r4, #7]	@ zero_extendqisi2
	ldr	r0, [r7, #2184]
	cmp	r2, lr
	mov	r2, r8
	moveq	r9, #3
	strb	r9, [r0, #4]
	ldr	r7, [r3, #2184]
	mov	r0, r5
	ldr	r9, [r4, #600]
	str	r9, [r7, #56]
	ldr	r7, [r3, #2184]
	ldr	r9, [r4, #604]
	str	r9, [r7, #60]
	ldr	r7, [r3, #2184]
	ldrb	r9, [r4, #11]	@ zero_extendqisi2
	strb	r9, [r7, #13]
	strb	r9, [r7, #12]
	ldrb	r10, [r4, #10]	@ zero_extendqisi2
	ldr	r9, [r3, #2184]
	ldr	r7, [r1, #-1884]
	strb	r10, [r9, #11]
	strb	r10, [r9, #10]
	ldr	r9, [r3, #2184]
	str	r7, [r9, #64]
	add	r7, r7, lr
	ldr	r3, [r3, #2184]
	str	r7, [r1, #-1884]
	ldrb	r9, [r3, #577]	@ zero_extendqisi2
	ldr	r1, [r3, #580]
	ldrb	r7, [r3, #578]	@ zero_extendqisi2
	strb	lr, [r3, #612]
	strb	ip, [r3, #648]
	ldr	lr, [r3, #600]
	ldrb	ip, [r3, #579]	@ zero_extendqisi2
	strb	r9, [r3, #613]
	strb	r9, [r3, #649]
	strb	r7, [r3, #614]
	strb	r7, [r3, #650]
	str	lr, [r3, #636]
	str	lr, [r3, #672]
	strb	ip, [r3, #615]
	strb	ip, [r3, #651]
	str	r1, [r3, #616]
	str	r1, [r3, #652]
	ldr	r1, [r4, #520]
	bl	MVC_GetAPC
	cmp	r0, #0
	bne	.L3723
.L3646:
	movw	r3, #28194
	movt	r3, 42
	add	r3, r6, r3
	ldr	r3, [r5, r3, asl #2]
	ldrb	r0, [r3, #3]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L3631
	ldr	r0, [r5, #120]
	mov	r2, #1
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3625:
	ldr	r3, [r4, #520]
	mov	r2, #3
	strb	r2, [r3, #576]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r3, r1, asl #2
	beq	.L3632
	add	r8, r0, r3
	add	r2, r8, #11075584
	str	r2, [fp, #-64]
	add	r7, r2, #45056
	ldr	r2, [r7, #2184]
	cmp	r2, #0
	beq	.L3632
	strb	r9, [r2, #612]
	ldr	r3, [r7, #2184]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #615]
	ldr	r3, [r7, #2184]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #613]
	ldr	r3, [r7, #2184]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #614]
	ldr	r3, [r7, #2184]
	ldr	r2, [r4, #548]
	str	r2, [r3, #628]
	ldr	r3, [r7, #2184]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #615]
	ldr	r3, [r7, #2184]
	ldr	r2, [r4, #572]
	str	r2, [r3, #636]
	ldr	r3, [r7, #2184]
	ldr	r1, [r3, #636]
	ldr	r2, [r3, #672]
	add	r2, r2, r1
	str	r2, [r3, #600]
	str	r2, [r3, #44]
	add	r1, r4, #16
	ldr	r2, [r7, #2184]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r7, #2184]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r7, #2184]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	orreq	r2, r2, #1
	strb	r2, [r3, #4]
	mov	r2, #504
	ldr	r3, [r7, #2184]
	add	r0, r3, #72
	ldrd	r8, [r3, #88]
	ldr	ip, [r3, #84]
	ldr	r10, [r3, #80]
	strd	r8, [fp, #-52]
	ldrd	r8, [r3, #96]
	str	ip, [fp, #-68]
	strd	r8, [fp, #-60]
	bl	memcpy
	ldr	ip, [fp, #-68]
	ldr	r1, [r4, #24]
	ldr	r2, [r4, #28]
	and	r3, r10, ip
	adds	r3, r3, #1
	ldrd	r8, [fp, #-52]
	and	r2, r2, r1
	movne	r3, #1
	cmn	r2, #1
	movne	r3, #0
	cmp	r3, #0
	ldrne	r3, [r7, #2184]
	movne	r2, ip
	strne	r10, [r3, #80]
	strne	r2, [r3, #84]
	ldrd	r2, [r4, #32]
	ldr	r1, [r7, #2184]
	cmp	r3, r9
	cmpeq	r2, r8
	movhi	r2, r8
	movhi	r3, r9
	ldrd	r8, [fp, #-60]
	strd	r2, [r1, #88]
	ldrd	r2, [r4, #40]
	ldr	r1, [r7, #2184]
	cmp	r3, r9
	cmpeq	r2, r8
	movhi	r3, r9
	movhi	r2, r8
	strd	r2, [r1, #96]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3643
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3643
.L3644:
	ldr	r3, [fp, #-64]
	add	r8, r3, #45056
	ldr	r2, [r8, #2184]
	ldrb	r3, [r2, #651]	@ zero_extendqisi2
	ldrb	r1, [r2, #615]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r8, #2184]
	ldr	r2, [r4, #564]
	str	r2, [r3, #632]
	ldr	r2, [r8, #2184]
	ldr	r3, [r2, #668]
	ldr	r1, [r2, #632]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r2, #36]
	ldr	r3, [r8, #2184]
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	strb	r2, [r3, #12]
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	ldr	r3, [r8, #2184]
	strb	r2, [r3, #10]
	ldr	r0, [r8, #2184]
	bl	MVC_CombineFldsToFrm
	ldr	r2, [r8, #2184]
	movw	r3, #28266
	movt	r3, 42
	ldr	r1, [r2, #52]
	ldr	r2, [r2, #628]
	add	r3, r1, r3
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3646
.L3632:
	add	r7, r5, r3
	ldr	r2, [r4, #520]
	add	r7, r7, #11075584
	mov	r1, #1
	add	r3, r7, #45056
	str	r2, [r3, #2184]
	strb	r1, [r2, #612]
	ldr	r2, [r3, #2184]
	ldr	r0, [r4, #520]
	str	r0, [r2, #616]
	ldr	r2, [r3, #2184]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	strb	r0, [r2, #613]
	ldr	r2, [r3, #2184]
	ldrb	r0, [r4, #5]	@ zero_extendqisi2
	strb	r0, [r2, #614]
	ldr	r2, [r3, #2184]
	ldr	r0, [r4, #548]
	str	r0, [r2, #628]
	ldr	r2, [r3, #2184]
	ldrb	r0, [r4, #12]	@ zero_extendqisi2
	strb	r0, [r2, #615]
	ldr	r2, [r3, #2184]
	ldr	r0, [r4, #572]
	str	r0, [r2, #636]
	ldr	r2, [r3, #2184]
	ldr	r0, [r2, #636]
	str	r0, [r2, #600]
	str	r0, [r2, #44]
	ldr	r2, [r3, #2184]
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	strb	r0, [r2, #1]
	ldr	r2, [r3, #2184]
	strb	r1, [r2, #2]
	ldr	r1, [r4, #520]
	ldr	r2, [r3, #2184]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #520]
	ldr	r2, [r3, #2184]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3634
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3634
.L3635:
	add	r7, r7, #45056
	mov	r8, #0
	mov	r2, #504
	add	r1, r4, #16
	ldr	r3, [r7, #2184]
	str	r8, [r3, #40]
	ldr	r0, [r7, #2184]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r7, #2184]
	ldr	r1, [r4, #596]
	mov	r2, #1
	ldr	ip, .L3724
	mov	r0, r5
	str	r1, [r3, #48]
	ldr	r3, [r7, #2184]
	ldr	r1, [r4, #528]
	str	r1, [r3, #20]
	ldr	r3, [r7, #2184]
	ldr	r1, [r4, #540]
	str	r1, [r3, #32]
	ldr	r3, [r7, #2184]
	ldr	r1, [r4, #556]
	str	r1, [r3, #36]
	ldr	r3, [r7, #2184]
	ldrb	r1, [r4, #12]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r7, #2184]
	ldr	r1, [r4, #564]
	str	r1, [r3, #632]
	ldr	r3, [r7, #2184]
	ldr	r1, [r4, #600]
	str	r1, [r3, #56]
	ldr	r3, [r7, #2184]
	ldr	r1, [r4, #604]
	str	r1, [r3, #60]
	ldr	r3, [r7, #2184]
	ldrb	r1, [r4, #11]	@ zero_extendqisi2
	strb	r1, [r3, #12]
	ldr	r3, [r7, #2184]
	ldrb	r1, [r4, #10]	@ zero_extendqisi2
	strb	r1, [r3, #10]
	ldr	r3, [ip, #-1884]
	ldr	r1, [r7, #2184]
	str	r3, [r1, #64]
	add	r3, r3, r2
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldr	lr, [r7, #2184]
	str	r3, [ip, #-1884]
	rsb	r3, r2, r1
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [lr, #4]
	ldr	r1, [r4, #520]
	bl	MVC_GetAPC
	cmp	r0, #0
	beq	.L3646
	mov	r3, r0
	ldr	ip, .L3724+4
	mov	r0, r8
	movw	r2, #2312
	b	.L3720
.L3647:
	add	r7, r5, r3
	ldr	r2, [r4, #520]
	add	r7, r7, #11075584
	mov	r1, #2
	add	r3, r7, #45056
	str	r2, [r3, #2184]
	strb	r1, [r2, #648]
	ldr	r2, [r3, #2184]
	ldr	r0, [r4, #520]
	str	r0, [r2, #652]
	ldr	r2, [r3, #2184]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	strb	r0, [r2, #649]
	ldr	r2, [r3, #2184]
	ldrb	r0, [r4, #5]	@ zero_extendqisi2
	strb	r0, [r2, #650]
	ldr	r2, [r3, #2184]
	ldr	r0, [r4, #552]
	str	r0, [r2, #664]
	ldr	r2, [r3, #2184]
	ldrb	r0, [r4, #12]	@ zero_extendqisi2
	strb	r0, [r2, #651]
	ldr	r2, [r3, #2184]
	ldr	r0, [r4, #572]
	str	r0, [r2, #672]
	ldr	r2, [r3, #2184]
	ldr	r0, [r2, #636]
	str	r0, [r2, #600]
	str	r0, [r2, #44]
	ldr	r2, [r3, #2184]
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	strb	r0, [r2, #1]
	ldr	r2, [r3, #2184]
	strb	r1, [r2, #2]
	ldr	r1, [r4, #520]
	ldr	r2, [r3, #2184]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #520]
	ldr	r2, [r3, #2184]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3649
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3649
.L3650:
	add	r7, r7, #45056
	mov	r8, #0
	mov	r2, #504
	add	r1, r4, #16
	ldr	r3, [r7, #2184]
	str	r8, [r3, #40]
	ldr	r0, [r7, #2184]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r7, #2184]
	ldr	ip, [r4, #596]
	mov	r2, #2
	ldr	r1, .L3724
	mov	r0, r5
	str	ip, [r3, #48]
	ldr	r3, [r7, #2184]
	ldr	ip, [r4, #528]
	str	ip, [r3, #20]
	ldr	r3, [r7, #2184]
	ldr	ip, [r4, #540]
	str	ip, [r3, #32]
	ldr	r3, [r7, #2184]
	ldr	ip, [r4, #556]
	str	ip, [r3, #36]
	ldr	r3, [r7, #2184]
	ldrb	ip, [r4, #12]	@ zero_extendqisi2
	strb	ip, [r3, #651]
	strb	ip, [r3]
	ldr	r3, [r7, #2184]
	ldr	ip, [r4, #568]
	str	ip, [r3, #668]
	ldr	r3, [r7, #2184]
	ldr	ip, [r4, #600]
	str	ip, [r3, #56]
	ldr	r3, [r7, #2184]
	ldr	ip, [r4, #604]
	str	ip, [r3, #60]
	ldr	r3, [r7, #2184]
	ldrb	ip, [r4, #11]	@ zero_extendqisi2
	strb	ip, [r3, #13]
	ldrb	ip, [r4, #10]	@ zero_extendqisi2
	ldr	r3, [r7, #2184]
	strb	ip, [r3, #11]
	ldr	ip, [r7, #2184]
	ldr	r3, [r1, #-1884]
	str	r3, [ip, #64]
	add	r3, r3, #1
	ldrb	lr, [r4, #7]	@ zero_extendqisi2
	ldr	ip, [r7, #2184]
	cmp	lr, #1
	str	r3, [r1, #-1884]
	moveq	r9, r2
	movne	r9, r8
	strb	r9, [ip, #4]
	ldr	r1, [r4, #520]
	bl	MVC_GetAPC
	cmp	r0, #0
	beq	.L3646
	ldr	ip, .L3724+4
	mov	r3, r0
	movw	r2, #2437
	mov	r0, r8
.L3720:
	ldr	r1, .L3724+12
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, r5
	mvn	r1, #0
	bl	MVC_ClearDPB
	mvn	r0, #0
	b	.L3631
.L3722:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #3
	b	.L3628
.L3634:
	ldr	r2, [r3, #2184]
	mov	r1, #1
	strb	r1, [r2, #3]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, r1
	ldreq	r3, [r3, #2184]
	ldreq	r2, [r4, #532]
	streq	r2, [r3, #28]
	b	.L3635
.L3649:
	ldr	r2, [r3, #2184]
	mov	r1, #2
	strb	r1, [r2, #3]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	ldreq	r3, [r3, #2184]
	ldreq	r2, [r4, #532]
	streq	r2, [r3, #28]
	b	.L3650
.L3643:
	ldr	r2, [r7, #2184]
	ldrb	r3, [r2, #3]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #3]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r7, #2184]
	ldreq	r2, [r4, #532]
	streq	r2, [r3, #28]
	b	.L3644
.L3659:
	ldr	r2, [r7, #2184]
	ldrb	r3, [r2, #3]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #3]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r7, #2184]
	ldreq	r2, [r4, #532]
	streq	r2, [r3, #28]
	b	.L3660
.L3723:
	mov	r3, r0
	ldr	ip, .L3724+4
	mov	r0, r8
	movw	r2, #2249
	b	.L3720
.L3725:
	.align	2
.L3724:
	.word	.LANCHOR3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC415
	.word	.LC414
	UNWIND(.fnend)
	.size	MVC_InsertFrmInDPB, .-MVC_InsertFrmInDPB
	.align	2
	.global	MVC_AllocFrameStore
	.type	MVC_AllocFrameStore, %function
MVC_AllocFrameStore:
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
	add	r9, r0, #11075584
	add	r7, r9, #40960
	mov	r6, r0
	str	r1, [fp, #-52]
	ldrb	r5, [r7, #521]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L3727
	ldrb	r3, [r7, #522]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r5, #2
	moveq	r5, #1
.L3727:
	ldr	r3, [fp, #-52]
	cmp	r3, #1
	ldrb	r3, [r6, #8]	@ zero_extendqisi2
	beq	.L3728
	cmp	r3, #2
	add	r4, r6, #11141120
	beq	.L3807
	sub	r3, r5, #1
	add	r4, r4, #8192
	cmp	r3, #1
	mov	r3, #0
	strb	r3, [r4, #1593]
	bls	.L3811
.L3750:
	mov	r8, #0
	strb	r8, [r4, #1592]
	ldr	r10, [r6, #48]
	cmp	r10, r8
	beq	.L3757
	movw	ip, #47800
	add	r9, r9, #45056
	movt	ip, 169
	add	ip, r6, ip
	movw	r3, #47240
	movt	r3, 169
	add	r3, r6, r3
	str	r3, [fp, #-48]
.L3756:
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3752
	cmp	ip, #0
	beq	.L3769
	ldr	lr, [r9, #2376]
	cmp	lr, #0
	beq	.L3769
	ldr	r2, [r9, #2184]
	rsb	r3, ip, r2
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L3752
	ldr	r1, [fp, #-48]
	b	.L3754
.L3755:
	ldr	r2, [r1, #4]!
	rsb	r0, ip, r2
	cmp	r2, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L3752
.L3754:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L3755
.L3769:
	mov	r3, #688
	movw	r2, #47840
	mla	r8, r3, r8, r6
	movt	r2, 169
	add	r0, r4, #1600
	mov	r9, #0
	mov	r3, #1
	str	ip, [r4, #2112]
	add	r2, r8, r2
	add	r1, r8, #11075584
	strb	r3, [r4, #1592]
	add	r1, r1, #47872
	str	r9, [r2, #4]
	add	r0, r0, #8
	mov	r2, #101
	str	r2, [r4, #2164]
	mov	r2, #504
	mov	r10, ip
	str	r3, [fp, #-48]
	bl	memcpy
	movw	r2, #47800
	str	r9, [r4, #1808]
	movt	r2, 169
	add	r2, r8, r2
	ldr	r3, [fp, #-48]
	strb	r9, [r2, #4]
	strb	r9, [r10, #7]
	ldr	r2, [r4, #2112]
	strb	r9, [r2, #3]
	ldr	r2, [r4, #2112]
	strb	r3, [r2, #5]
	ldr	r3, [r4, #2112]
	str	r9, [r3, #16]
	ldrb	r10, [r4, #1592]	@ zero_extendqisi2
	cmp	r10, #1
	bne	.L3757
	ldr	r3, [fp, #-52]
	ldr	r0, [r6, #120]
	clz	r1, r3
	mov	r1, r1, lsr #5
	bl	FSP_NewLogicFs
	mov	r8, r0
	mov	r1, r0
	ldr	r0, [r6, #120]
	bl	FSP_GetLogicFs
	mvn	r3, r8
	mov	r3, r3, lsr #31
	cmp	r0, #0
	mov	r9, r0
	moveq	r3, #0
	cmp	r3, #0
	beq	.L3758
	ldr	r3, [r6, #224]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L3812
.L3759:
	ldr	r10, .L3819
	mov	r2, #504
	ldr	r0, [r4, #2112]
	add	r1, r9, #8
	ldr	r3, [r10, #52]
	add	r0, r0, #72
	blx	r3
	ldr	r1, [r4, #2112]
	movw	r0, #9800
	ldr	r3, [r10, #52]
	movt	r0, 170
	add	r1, r1, #72
	add	r0, r6, r0
	mov	r2, #504
	blx	r3
	ldr	r3, [r4, #2112]
	strb	r8, [r3, #6]
	ldrsb	r3, [r9, #4]
	str	r3, [r4, #2188]
.L3749:
	ldr	r3, [fp, #-52]
	uxtb	r2, r5
	strb	r2, [r4, #1595]
	cmp	r3, #1
	moveq	r0, #0
	beq	.L3803
	ldrb	r3, [r7, #521]	@ zero_extendqisi2
	ldr	r1, [r4, #2112]
	cmp	r3, #0
	movne	r3, #3
	strb	r3, [r1, #576]
	ldrb	r3, [r4, #1593]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3813
	strb	r2, [r4, #2808]
	cmp	r5, #0
	ldr	r3, [r7, #548]
	movne	r0, #0
	moveq	r0, r5
	str	r3, [r4, #2816]
	ldrb	r3, [r7, #528]	@ zero_extendqisi2
	str	r3, [r4, #2812]
	ldr	r3, [r6, #128]
	str	r3, [r4, #2820]
	ldr	r3, [r7, #2160]
	str	r8, [r4, #2824]
	streqb	r5, [r4, #2809]
	str	r3, [r4, #2832]
	movne	r3, #1
	strneb	r3, [r4, #2809]
.L3803:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3752:
	add	r8, r8, #1
	add	ip, ip, #688
	cmp	r8, r10
	bne	.L3756
.L3757:
	ldr	r3, .L3819
	mov	r0, #0
	ldr	r1, .L3819+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r6
	mov	r1, #1
	bl	MVC_ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3814:
	add	r4, r6, #11141120
	mov	r5, #0
.L3807:
	add	r4, r4, #8192
.L3747:
	mov	r3, #0
	strb	r3, [r4, #1593]
	b	.L3750
.L3728:
	cmp	r3, #2
	beq	.L3814
	add	r4, r6, #11141120
	mov	r3, #0
	add	r4, r4, #8192
	mov	r5, r3
	strb	r3, [r4, #1593]
	b	.L3750
.L3812:
	ldr	r3, [r6, #16]
	ldr	r10, [r0, #200]
	ldr	r2, [r6, #12]
	mov	r3, r3, asl #4
	str	r3, [r0, #176]
	ldr	r0, [r0, #112]
	mul	r10, r10, r3
	mov	r3, r2, asl #4
	str	r3, [r9, #172]
	add	r0, r10, r0
	str	r0, [r9, #116]
	bl	MEM_Phy2Vir
	ldr	r2, [r9, #96]
	ldr	r3, [r9, #128]
	add	r3, r10, r3
	add	r10, r10, r2
	ldr	r2, [r9, #200]
	str	r10, [r9, #100]
	str	r3, [r9, #132]
	add	r10, r10, r2
	str	r10, [r9, #108]
	str	r0, [r9, #44]
	mov	r0, r3
	bl	MEM_Phy2Vir
	str	r0, [r9, #60]
	b	.L3759
.L3811:
	ldrb	r3, [r4, #2808]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3731
	ldr	r1, [r4, #2832]
	ldr	r2, [r7, #2160]
	cmp	r1, r2
	beq	.L3732
.L3731:
	add	r3, r9, #45056
	ldr	r1, [r3, #2376]
	subs	r3, r1, #1
	bmi	.L3750
	movw	r2, #28194
	movt	r2, 42
	add	r2, r1, r2
	add	r2, r6, r2, lsl #2
	b	.L3743
.L3734:
	cmp	r5, #2
	beq	.L3815
.L3733:
	subs	r3, r3, #1
	bmi	.L3750
.L3743:
	ldr	r8, [r2, #-4]!
	cmp	r8, #0
	beq	.L3733
	cmp	r5, #1
	bne	.L3734
	ldrb	r1, [r8, #2]	@ zero_extendqisi2
	cmp	r1, #2
	bne	.L3733
.L3735:
	ldr	r0, [r7, #548]
	ldr	r1, [r8, #20]
	cmp	r0, r1
	bne	.L3733
	ldr	r0, [r7, #2160]
	ldr	r1, [r8, #56]
	cmp	r0, r1
	bne	.L3733
	ldrb	r1, [r7, #528]	@ zero_extendqisi2
	cmp	r1, #0
	ldrb	r1, [r8, #3]	@ zero_extendqisi2
	beq	.L3816
	cmp	r1, #0
	beq	.L3733
.L3739:
	add	r0, r4, #1600
	mov	r3, #1
	mov	r2, #504
	strb	r3, [r4, #1593]
	add	r1, r8, #72
	str	r8, [r4, #2112]
	add	r0, r0, #8
	bl	memcpy
	ldrsb	r1, [r8, #6]
	ldr	r0, [r6, #120]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L3817
	ldrb	r2, [r4, #1593]	@ zero_extendqisi2
	ldrsb	r3, [r3, #4]
	cmp	r2, #0
	str	r3, [r4, #2188]
	beq	.L3750
	ldr	r3, [r4, #2112]
	cmp	r3, #0
	beq	.L3750
.L3808:
	mov	r8, #0
	b	.L3749
.L3815:
	ldrb	r1, [r8, #2]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L3733
	b	.L3735
.L3813:
	mov	r3, #0
	strb	r3, [r4, #2808]
	ldr	r2, [r7, #548]
	mov	r0, r3
	str	r2, [r4, #2816]
	ldrb	r2, [r7, #528]	@ zero_extendqisi2
	str	r2, [r4, #2812]
	ldr	r2, [r6, #128]
	strb	r3, [r4, #2809]
	str	r8, [r4, #2824]
	str	r2, [r4, #2820]
	ldr	r3, [r7, #2160]
	str	r3, [r4, #2832]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3816:
	cmp	r1, #0
	bne	.L3733
	b	.L3739
.L3732:
	sub	r8, r5, #2
	cmp	r3, #1
	cmpeq	r5, #2
	clz	r8, r8
	mov	r8, r8, lsr #5
	beq	.L3744
	cmp	r5, #1
	cmpeq	r3, #2
	bne	.L3750
.L3744:
	ldr	r2, [r4, #2816]
	ldr	r3, [r7, #548]
	cmp	r2, r3
	bne	.L3750
	ldrb	r3, [r7, #528]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r4, #2812]
	bne	.L3745
	cmp	r3, #0
	bne	.L3750
.L3746:
	ldr	r3, [r6, #128]
	ldr	r2, [r6, #124]
	rsb	r3, r2, r3
	cmp	r3, #2
	bhi	.L3750
	ldr	r3, [r4, #2112]
	mov	r2, #1
	strb	r2, [r4, #1593]
	cmp	r3, #0
	beq	.L3747
	cmp	r8, #0
	bne	.L3818
	cmp	r5, #1
	bne	.L3749
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3747
	b	.L3749
.L3758:
	ldr	ip, [r4, #2112]
	mov	r0, r3
	ldr	r2, .L3819
	strb	r3, [r4, #1592]
	ldr	r1, .L3819+8
	strb	r3, [ip, #5]
	ldr	r3, [r2, #68]
	blx	r3
	mov	r1, r10
	mov	r0, r6
	bl	MVC_ClearAll
	mvn	r0, #0
	b	.L3803
.L3817:
	ldr	r3, .L3819
	movw	r2, #6640
	ldr	r1, .L3819+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L3803
.L3818:
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, r2
	bne	.L3747
	b	.L3808
.L3745:
	cmp	r3, #0
	beq	.L3750
	b	.L3746
.L3820:
	.align	2
.L3819:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC417
	.word	.LC418
	.word	.LC416
	UNWIND(.fnend)
	.size	MVC_AllocFrameStore, .-MVC_AllocFrameStore
	.align	2
	.global	MVC_DEC_Init
	.type	MVC_DEC_Init, %function
MVC_DEC_Init:
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
	ldr	r7, .L3833
	movw	r2, #12720
	ldr	r4, [r0, #928]
	mov	r6, r0
	mov	r5, r1
	movt	r2, 170
	mov	r1, #0
	ldr	r3, [r7, #48]
	blx	r3
	str	r4, [r6, #928]
	add	r0, r6, #584
	mov	r4, #2240
	bl	ResetVoQueue
	str	r5, [r6, #224]
	mov	r3, #0
	str	r3, [r6, #228]
	strb	r3, [r6]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	ldreq	r3, [r5, #752]
	movne	r3, #32
	movne	r2, #256
	strne	r3, [r6, #36]
	movne	r3, #136
	streq	r3, [r6, #36]
	ldreq	r3, [r5, #756]
	streq	r3, [r6, #40]
	ldreq	r3, [r5, #744]
	str	r3, [r6, #32]
	strne	r2, [r6, #40]
	ldr	r0, [r5, #668]
	bl	MEM_Phy2Vir
	ldr	ip, [r6, #36]
	ldr	r3, [r6, #224]
	movw	r2, #3992
	ldr	r1, [r6, #40]
	mul	r2, r2, ip
	ldr	r3, [r3, #664]
	add	r3, r0, r3
	str	r3, [r6, #248]
	add	r0, r3, r2
	str	r0, [r6, #252]
	cmp	r3, #0
	cmpne	r0, #0
	mla	r0, r4, r1, r0
	moveq	lr, #1
	movne	lr, #0
	cmp	r0, #0
	orreq	lr, lr, #1
	cmp	lr, #0
	str	r0, [r6, #544]
	bne	.L3830
	ldr	r5, [r5, #688]
	cmp	r5, #0
	beq	.L3831
.L3826:
	add	r3, r6, #11075584
	movw	r2, #4060
	add	lr, r3, #36864
	add	r3, r3, #32768
	ldr	r9, [r7, #48]
	add	r4, r6, #12992
	str	r1, [lr, #1264]
	mov	r1, #0
	str	ip, [r3, #2088]
	mov	r5, r1
	ldr	r3, [r6, #32]
	add	r4, r4, #12
	movw	r8, #22860
	movt	r8, 164
	add	r8, r6, r8
	mul	r2, r2, r3
	blx	r9
	ldr	r3, [r6, #108]
	mov	r2, #9856
	mov	lr, #18
	mov	ip, #25
	strb	r5, [r6, #4]
	ubfx	r3, r3, #16, #2
	strb	r5, [r6, #6]
	strb	r3, [r6, #8]
	mov	r1, r5
	mov	r3, #40
	strb	r5, [r6, #7]
	movt	r2, 164
	str	r3, [r6, #48]
	str	lr, [r6, #52]
	mov	r0, r4
	ldr	r3, [r7, #48]
	str	ip, [r6, #56]
	str	r5, [r6, #68]
	str	r5, [r6, #72]
	str	r5, [r6, #76]
	str	r5, [r6, #80]
	str	r5, [r6, #84]
	str	r5, [r6, #88]
	str	r5, [r6, #92]
	str	r5, [r6, #96]
	str	r5, [r6, #60]
	str	r5, [r6, #528]
	str	r5, [r6, #532]
	str	r5, [r6, #536]
	str	r5, [r6, #540]
	str	r5, [r6, #220]
	blx	r3
	movw	r2, #8500
	ldr	r3, [r7, #48]
	mov	r0, r8
	mov	r1, r5
	movt	r2, 5
	blx	r3
	mov	r0, r4
	mov	r3, r5
.L3827:
	strb	r3, [r0]
	add	r2, r0, #274432
	add	r0, r0, #335872
	mov	r4, #0
	add	r0, r0, #308
	strb	r3, [r2, #241]
	cmp	r0, r8
	bne	.L3827
	add	r2, r6, #12288
	movw	r3, #34112
	mov	r1, #32
	movt	r3, 169
	strb	r4, [r2, #704]
	add	r3, r6, r3
	mov	r0, r6
	str	r3, [r6, #236]
	str	r4, [r6, #20]
	strb	r4, [r6, #2]
	str	r1, [r6, #24]
	str	r1, [r6, #28]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r6, #120]
	beq	.L3832
	mov	r1, r4
	mov	r0, r6
	bl	MVC_ClearAll
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3831:
	mov	r0, r3
	mov	r1, r5
	ldr	r3, [r7, #48]
	blx	r3
	ldr	r2, [r6, #40]
	mov	r1, r5
	ldr	r3, [r7, #48]
	ldr	r0, [r6, #252]
	mul	r2, r4, r2
	blx	r3
	ldr	r1, [r6, #40]
	ldr	ip, [r6, #36]
	ldr	r0, [r6, #544]
	b	.L3826
.L3830:
	ldr	r4, [r7, #68]
	movw	r3, #13772
	ldr	r2, .L3833+4
	mov	r0, #22
	ldr	r1, .L3833+8
	blx	r4
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3832:
	ldr	r3, [r7, #68]
	mov	r0, r4
	ldr	r1, .L3833+12
	blx	r3
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3834:
	.align	2
.L3833:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+332
	.word	.LC419
	.word	.LC420
	UNWIND(.fnend)
	.size	MVC_DEC_Init, .-MVC_DEC_Init
	.align	2
	.global	MVC_StorePicInDpb
	.type	MVC_StorePicInDpb, %function
MVC_StorePicInDpb:
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
	add	r4, r0, #11075584
	add	r7, r0, #11141120
	add	r2, r4, #36864
	add	r6, r7, #8192
	mov	r9, #0
	strb	r9, [r2, #3480]
	mov	r5, r0
	ldrb	r3, [r6, #1595]	@ zero_extendqisi2
	sub	r3, r3, #2
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r2, #3481]
	ldrb	r3, [r6, #1592]	@ zero_extendqisi2
	cmp	r3, r9
	beq	.L4002
	ldr	r3, [r0, #128]
	str	r3, [r0, #124]
	ldrb	r3, [r6, #1605]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4003
.L3838:
	ldrb	r0, [r5, #8]	@ zero_extendqisi2
	cmp	r0, #2
	beq	.L4004
	ldr	r8, [r5, #224]
	ldr	r3, [r8, #12]
	cmp	r3, #0
	ble	.L4005
.L3843:
	ldrb	r2, [r6, #1594]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L4006
.L3844:
	cmp	r3, #2
	ldr	r3, [r6, #2128]
	beq	.L4007
.L3869:
	cmp	r3, #0
	bne	.L4008
	ldrb	r3, [r6, #1593]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3880
	add	r4, r4, #45056
	ldr	ip, [r4, #2376]
.L3890:
	mvn	r8, #0
	mov	r9, r8
	b	.L3899
.L3894:
	ldr	r2, [r6, #2128]
	mov	r1, r9
	mov	r0, r5
	mov	r8, r3
	cmp	r2, #0
	bne	.L3895
	ldr	r2, [r6, #2132]
	ldr	r3, [fp, #-56]
	cmp	r2, r3
	blt	.L4009
.L3895:
	bl	MVC_OutputFrmFromDPB
	cmn	r0, #1
	beq	.L3898
	ldr	ip, [r4, #2376]
.L3899:
	ldr	lr, [r4, #2380]
	sub	r3, fp, #52
	sub	r2, fp, #56
	mvn	r1, #0
	cmp	lr, ip
	mov	r0, r5
	bcc	.L3892
	bl	MVC_GetMinPOC
	cmp	r0, #0
	blt	.L4010
	ldr	r3, [r4, #2380]
	cmp	r3, r8
	ldrne	r9, [fp, #-52]
	bne	.L3894
	ldr	r2, [fp, #-52]
	cmp	r2, r9
	beq	.L4011
	mov	r9, r2
	b	.L3894
.L4003:
	ldr	r3, [r6, #2116]
	ldrb	r10, [r3, #1]	@ zero_extendqisi2
	cmp	r10, #0
	beq	.L3839
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L3838
	ldr	r8, .L4028
	mov	r0, r9
	ldr	r1, .L4028+4
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r4, [r8, #68]
	movw	r3, #3638
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4006:
	ldr	r2, [r6, #2112]
	ldrb	r1, [r6, #1595]	@ zero_extendqisi2
	str	r2, [fp, #-64]
	sub	r2, r1, #1
	cmp	r2, #1
	movhi	r2, #0
	movls	r2, #1
	cmp	r1, #0
	beq	.L3845
	ldr	r0, [fp, #-64]
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	ip, r2
	orrne	ip, r2, #1
	cmp	ip, #0
	beq	.L3844
	cmp	r2, #0
	bne	.L3918
	cmp	r0, #0
	beq	.L3844
.L3851:
	cmp	r3, #0
	ble	.L3921
	movw	r8, #9784
	ldr	r9, [fp, #-64]
	movt	r8, 170
	add	r8, r5, r8
.L3854:
	cmp	r1, #0
	beq	.L3856
	ldrb	r3, [r8, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4012
.L3856:
	ldr	r3, [r8, #572]
	str	r3, [r9, #44]
.L3857:
	mov	r1, r9
	mov	r0, r5
	bl	MVC_GetImagePara
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetFsImagePtr
	subs	r10, r0, #0
	beq	.L4013
	ldrd	r2, [r8, #24]
	strd	r2, [r10, #8]
	ldrd	r2, [r8, #32]
	strd	r2, [r10, #16]
	ldrd	r2, [r8, #40]
	strd	r2, [r10, #24]
	ldr	r3, [r9, #44]
	cmp	r3, #0
	str	r3, [r10, #200]
	beq	.L3864
	ldr	r2, [r10, #160]
	ands	r2, r2, #3
	str	r2, [fp, #-68]
	beq	.L4014
.L3862:
	ldr	r2, [r5, #224]
	ldr	r2, [r2, #4]
	cmp	r2, r3
	bcc	.L4015
.L3864:
	mov	r2, #1
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
	ldr	r0, [r5, #120]
	add	r3, r5, #584
	str	r10, [sp]
	mov	r2, r5
	mov	r1, #16
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L3861
	mov	r2, #0
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
.L3861:
	ldr	r3, [r5, #224]
	ldr	r3, [r3, #684]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r10, #84]
	bcs	.L4016
.L3867:
	ldr	r3, [r5, #136]
	add	r3, r3, #2
	str	r3, [r5, #136]
.L3855:
	ldr	r3, [r5, #220]
	cmp	r3, #2
	beq	.L3868
.L3853:
	ldr	r2, [fp, #-64]
	mov	r3, #1
	str	r3, [r9, #16]
	strb	r3, [r2, #8]
.L3868:
	ldr	r3, [r5, #224]
	mov	r2, #2
	str	r2, [r5, #220]
	ldr	r3, [r3, #12]
	cmp	r3, #2
	ldr	r3, [r6, #2128]
	bne	.L3869
.L4007:
	cmp	r3, #0
	beq	.L3870
	add	r4, r4, #45056
	mov	r0, r5
	bl	MVC_SimpleSlideDPB
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3871
	ldr	r3, [r4, #2184]
	cmp	r3, #0
	beq	.L3923
	movw	r2, #47240
	mov	r3, #0
	movt	r2, 169
	add	r2, r5, r2
	b	.L3872
.L3873:
	ldr	r0, [r2, #4]!
	cmp	r0, #0
	beq	.L3923
.L3872:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3873
.L3871:
	movw	r2, #9784
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	subs	r9, r0, #0
	bne	.L4017
	ldr	r1, [r4, #2380]
	mov	r0, r5
	add	r1, r1, #1
	str	r1, [r4, #2380]
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	ldr	ip, .L4028
	mov	r2, r9
	movw	r3, #3819
	ldr	r1, .L4028+8
	mov	r0, #14
	ldr	r4, [ip, #68]
	blx	r4
	b	.L3875
.L4008:
	ldr	r8, .L4028
	ldr	r3, [r8, #112]
	blx	r3
	ldr	r2, [r5, #112]
	ldr	r3, [r6, #2164]
	cmp	r2, r3
	bcs	.L3877
	ldrb	r3, [r6, #1594]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4018
.L3877:
	mov	r0, r5
	bl	MVC_Marking
	cmp	r0, #0
	bne	.L4019
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	ldr	r1, [r6, #2192]
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
.L3870:
	ldrb	r3, [r6, #1593]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3880
	add	r4, r4, #45056
	ldr	ip, [r4, #2376]
.L3881:
	ldr	r3, [r6, #2128]
	cmp	r3, #0
	beq	.L3890
	ldr	r1, [r4, #2384]
	ldr	r2, [r4, #2388]
	add	r3, r2, r1
	cmp	r3, ip
	bcc	.L3890
.L3915:
	ldr	r8, .L4028
	mov	r3, ip
	str	r2, [sp, #4]
	mov	r0, #1
	str	r1, [sp]
	movw	r2, #3912
	ldr	r4, [r8, #68]
	ldr	r1, .L4028+12
	blx	r4
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
	ldr	r4, [r8, #68]
	movw	r3, #3915
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L3845:
	cmp	r2, #0
	beq	.L3851
.L3918:
	ldr	r2, [r5, #220]
	cmp	r2, #0
	bne	.L3848
	add	r1, r6, #1584
	add	r0, r6, #2192
	mov	r3, #1
	add	r1, r1, #8
	str	r3, [r5, #220]
	add	r0, r0, #8
	mov	r2, #608
	bl	memcpy
	ldr	r3, [r8, #12]
	b	.L3844
.L4010:
	ldr	r3, .L4028
	movw	r2, #3923
	ldr	r1, .L4028+16
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
.L3892:
	ldr	r3, [r6, #2128]
	cmp	r3, #0
	beq	.L3904
	ldrb	r3, [r6, #1596]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3904
	ldr	r2, [r4, #2384]
	cmp	r2, #0
	beq	.L3904
	movw	ip, #47300
	mov	lr, r3
	movt	ip, 169
	add	ip, r5, ip
	b	.L3909
.L3906:
	ldr	r2, [r4, #2384]
	cmp	r2, r3
	bls	.L3904
.L3909:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	ldr	r1, [r6, #2120]
	ldr	r0, [r2, #20]
	cmp	r0, r1
	bne	.L3906
	ldr	r0, [r2, #56]
	ldr	r1, [r6, #2192]
	cmp	r0, r1
	bne	.L3906
	strb	lr, [r2, #3]
	ldr	r1, [ip]
	ldrb	r2, [r1, #5]	@ zero_extendqisi2
	cmp	r2, #1
	streqb	r2, [r1, #7]
	ldreq	r2, [ip]
	streqb	lr, [r2, #5]
	ldreq	r1, [ip]
	ldr	r0, [r5, #52]
	ldr	r2, [r1, #48]
	cmp	r2, r0
	add	r2, r5, r2, lsl #2
	strne	lr, [r2, #148]
	strne	r0, [r1, #48]
	b	.L3906
.L3904:
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3903
	ldr	r3, [r4, #2184]
	cmp	r3, #0
	beq	.L3927
	movw	r2, #47240
	mov	r3, #0
	movt	r2, 169
	add	r2, r5, r2
	b	.L3910
.L3911:
	ldr	r0, [r2, #4]!
	cmp	r0, #0
	beq	.L3927
.L3910:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3911
.L3903:
	movw	r2, #9784
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L4020
	ldr	r3, [r4, #2380]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #2380]
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
.L3875:
	mov	r4, #0
.L3913:
	add	r7, r7, #8192
	mov	r3, #0
	mov	r0, r4
	strb	r3, [r7, #1592]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3880:
	ldr	r3, [r5, #520]
	ldr	lr, [r6, #2112]
	cmp	r3, #0
	rsb	r2, r3, lr
	clz	r2, r2
	mov	r2, r2, lsr #5
	moveq	r2, #0
	cmp	r2, #0
	beq	.L4021
	mov	r0, r5
	ldr	r8, .L4028
	bl	MVC_DirectOutput
	cmn	r0, #1
	mov	r4, r0
	beq	.L4022
.L3886:
	ldr	r9, [r8, #68]
	movw	r3, #3873
	mov	r2, r4
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r9
	b	.L3842
.L3839:
	mvn	r1, #0
	bl	MVC_FlushDPB
	cmp	r0, #0
	beq	.L3838
	ldr	r8, .L4028
	mov	r0, r10
	ldr	r1, .L4028+20
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r4, [r8, #68]
	mov	r3, #3648
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4005:
	ldr	r2, [r5, #220]
	cmp	r2, #2
	bne	.L3843
	b	.L3844
.L4021:
	add	r4, r4, #45056
	ldr	ip, [r4, #2376]
	cmp	ip, #0
	beq	.L3883
	ldr	r3, [r4, #2184]
	adds	r1, r3, #0
	movne	r1, #1
	cmp	lr, r3
	movne	r1, #0
	cmp	r1, #0
	movweq	r2, #47240
	movteq	r2, 169
	addeq	r2, r5, r2
	bne	.L4023
.L3887:
	add	r1, r1, #1
	cmp	r1, ip
	beq	.L3881
	ldr	r3, [r2, #4]!
	adds	r0, r3, #0
	movne	r0, #1
	cmp	lr, r3
	movne	r0, #0
	cmp	r0, #0
	beq	.L3887
.L3884:
	movw	r2, #9784
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	cmn	r0, #1
	mov	r4, r0
	beq	.L4024
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	ldr	ip, .L4028
	movw	r3, #3899
	mov	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	ldr	r4, [ip, #68]
	blx	r4
	b	.L3875
.L3927:
	mov	r1, r3
	b	.L3903
.L3898:
	ldr	r8, .L4028
	mov	r3, r0
	mov	r10, r0
	movw	r2, #3963
	ldr	r1, .L4028+24
	mov	r0, #1
	ldr	r4, [r8, #68]
	blx	r4
	mov	r2, r10
	ldr	r4, [r8, #68]
	movw	r3, #3964
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
.L3917:
	ldr	r3, [r6, #2112]
	mov	r2, #1
	ldr	r0, [r5, #120]
	mvn	r4, #0
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	mov	r3, r4
	movw	r2, #4022
	ldr	r5, [r8, #68]
	ldr	r1, .L4028+24
	mov	r0, #1
	blx	r5
	ldr	r2, [r6, #2112]
	mov	r3, #0
	strb	r3, [r2, #5]
	ldr	r2, [r6, #2112]
	strb	r3, [r2, #2]
	b	.L3913
.L4004:
	ldr	r8, .L4028
	ldr	r1, .L4028+28
	ldr	r3, [r8, #68]
	blx	r3
	mov	r0, r5
	bl	MVC_DirectOutput
	ldr	r3, [r6, #2188]
	ldr	r2, [r5, #52]
	ldr	r9, [r8, #68]
	cmp	r3, r2
	addne	r3, r3, #36
	movne	r1, #0
	addne	r3, r5, r3, lsl #2
	mov	r4, r0
	strne	r1, [r3, #4]
	strne	r2, [r6, #2188]
	movw	r3, #3667
	mov	r2, r0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r9
.L3842:
	cmn	r4, #1
	bne	.L3913
	b	.L3917
.L3848:
	cmp	r2, #1
	beq	.L4025
	cmp	r1, #0
	beq	.L3851
	ldr	r2, [fp, #-64]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3851
	b	.L3844
.L4009:
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4026
.L3896:
	mov	r0, r5
	ldr	r8, .L4028
	bl	MVC_DirectOutput
	cmn	r0, #1
	mov	r4, r0
	beq	.L4027
.L3897:
	ldr	r9, [r8, #68]
	movw	r3, #3955
	mov	r2, r4
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r9
	b	.L3842
.L4022:
	mov	r3, r0
	movw	r2, #3869
	ldr	r1, .L4028+24
	mov	r0, #1
	ldr	r9, [r8, #68]
	blx	r9
	b	.L3886
.L4018:
	ldr	r3, [r8, #112]
	blx	r3
	ldr	r4, [r8, #68]
	ldr	r3, [r5, #112]
	mov	r0, #1
	ldr	r2, [r6, #2164]
	ldr	r1, .L4028+32
	blx	r4
	ldr	r3, .L4028+36
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L3878
	ldr	r0, [r5, #112]
	mov	r3, #8
	ldr	ip, [r6, #2164]
	sub	r2, fp, #52
	mov	r1, #104
	str	r0, [fp, #-48]
	str	ip, [fp, #-52]
	ldr	r0, [r5, #120]
	blx	r4
.L3878:
	mov	r0, r5
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
	ldr	r4, [r8, #68]
	movw	r3, #3837
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L3921:
	ldr	r9, [fp, #-64]
	b	.L3855
.L4011:
	ldr	r8, .L4028
	mov	r3, r9
	ldr	r2, .L4028+40
	mov	r0, #1
	ldr	r1, .L4028+44
	ldr	r4, [r8, #68]
	blx	r4
	ldr	r4, [r8, #68]
	movw	r3, #3932
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4016:
	mov	r1, r10
	mov	r0, r5
	bl	MVC_SetFrmRepeatCount.part.1
	b	.L3867
.L3923:
	mov	r1, r3
	b	.L3871
.L4026:
	ldrb	r3, [r6, #1595]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r3, [r6, #2112]
	strne	r3, [r5, #524]
	b	.L3896
.L4025:
	cmp	r3, #0
	ldr	r9, [r6, #2720]
	ble	.L3853
	movw	r8, #10392
	ldrb	r1, [r6, #2203]	@ zero_extendqisi2
	movt	r8, 170
	add	r8, r5, r8
	b	.L3854
.L4014:
	ldr	r8, .L4028
	movw	r2, #3748
	ldr	r1, .L4028+48
	mov	r0, #1
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r3, .L4028+36
	ldr	r8, [r3]
	cmp	r8, #0
	beq	.L3863
	ldr	r3, [fp, #-68]
	mov	r1, #111
	ldr	r0, [r5, #120]
	mov	r2, r3
	blx	r8
.L3863:
	ldr	r3, [r10, #200]
	cmp	r3, #0
	bne	.L3862
	b	.L3864
.L4012:
	mov	r2, #3
	ldr	r3, [r9, #44]
	strb	r2, [r9, #2]
	ldr	r2, [r8, #572]
	add	r3, r3, r2
	str	r3, [r9, #44]
	b	.L3857
.L4002:
	ldr	r8, .L4028
	mov	r0, r3
	ldr	r1, .L4028+52
	ldr	r3, [r8, #68]
	blx	r3
	ldr	r4, [r8, #68]
	movw	r3, #3624
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4027:
	mov	r3, r0
	mov	r2, #3952
	ldr	r1, .L4028+24
	mov	r0, #1
	ldr	r9, [r8, #68]
	blx	r9
	b	.L3897
.L4020:
	ldr	r8, .L4028
	mov	r3, r0
	movw	r2, #4008
	ldr	r1, .L4028+24
	mov	r0, #1
	ldr	r4, [r8, #68]
	blx	r4
	ldr	r4, [r8, #68]
	movw	r3, #4009
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4019:
	mov	r2, r0
	ldr	r3, [r8, #68]
	ldr	r1, .L4028+56
	mov	r0, #1
	blx	r3
	ldr	r4, [r8, #68]
	movw	r3, #3846
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4023:
	mov	r1, r2
	b	.L3884
.L3883:
	ldr	r3, [r6, #2128]
	cmp	r3, #0
	beq	.L3890
	ldr	r1, [r4, #2384]
	ldr	r2, [r4, #2388]
	b	.L3915
.L4017:
	ldr	r8, .L4028
	mov	r3, r9
	movw	r2, #3810
	ldr	r1, .L4028+24
	mov	r0, #0
	ldr	r4, [r8, #68]
	blx	r4
	ldr	r4, [r8, #68]
	movw	r3, #3811
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4015:
	ldr	r8, .L4028
	mov	r2, #0
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
	ldr	r4, [r8, #68]
	movw	r3, #3767
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4024:
	ldr	r8, .L4028
	mov	r3, r0
	movw	r2, #3892
	ldr	r1, .L4028+24
	mov	r0, #1
	ldr	r9, [r8, #68]
	blx	r9
	mov	r2, r4
	movw	r3, #3893
	ldr	r4, [r8, #68]
	ldr	r1, .L4028+8
	mov	r0, #14
	blx	r4
	b	.L3917
.L4013:
	ldr	r8, .L4028
	movw	r3, #3737
	mvn	r2, #0
	ldr	r1, .L4028+8
	mov	r0, #14
	ldr	r4, [r8, #68]
	blx	r4
	b	.L3917
.L4029:
	.align	2
.L4028:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC423
	.word	.LC422
	.word	.LC430
	.word	.LC431
	.word	.LC424
	.word	.LC427
	.word	.LC425
	.word	.LC428
	.word	g_event_report
	.word	.LANCHOR0+348
	.word	.LC432
	.word	.LC426
	.word	.LC421
	.word	.LC429
	UNWIND(.fnend)
	.size	MVC_StorePicInDpb, .-MVC_StorePicInDpb
	.global	__aeabi_idivmod
	.align	2
	.global	MVC_DecGap
	.type	MVC_DecGap, %function
MVC_DecGap:
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
	ldrb	r1, [r0, #3]	@ zero_extendqisi2
	mov	r6, r0
	add	r3, r0, #11075584
	movw	r0, #2004
	add	r8, r3, #40960
	mul	r1, r0, r1
	ldr	r2, [r8, #2164]
	mov	r4, r3
	str	r3, [fp, #-80]
	movw	r3, #26758
	ldr	ip, [r6, #236]
	add	lr, r6, r1
	movt	r3, 42
	add	r3, r2, r3
	movw	r2, #43184
	movt	r2, 169
	add	r2, lr, r2
	add	r9, r4, #36864
	ldrb	r5, [ip, #19]	@ zero_extendqisi2
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	add	r0, r6, #11141120
	cmp	r5, #1
	mov	lr, r4
	mov	r7, r0
	str	r0, [fp, #-76]
	str	r2, [fp, #-72]
	add	r0, r6, r3, lsl #2
	ldr	r2, [r8, #548]
	movw	r3, #43184
	add	r4, r7, #8192
	add	lr, lr, #45056
	movt	r3, 169
	add	r3, r1, r3
	str	r2, [fp, #-52]
	add	r3, r6, r3
	ldr	r2, [r9, #3520]
	ldr	r0, [r0, #4]
	str	r2, [fp, #-64]
	moveq	r2, #2
	movne	r2, #0
	str	r2, [fp, #-56]
	ldr	r2, [r9, #3524]
	str	r2, [fp, #-68]
	ldr	r2, [ip, #2896]
	str	r3, [r4, #2116]
	ldr	r5, [lr, #2380]
	cmp	r5, #0
	beq	.L4045
	add	r2, r2, #4
	mov	r7, #1
	mov	r3, r7, asl r2
	add	r0, r0, r7
	str	r3, [fp, #-60]
	mov	r1, r3
	ldr	r10, .L4048
	bl	__aeabi_uidivmod
	mov	r3, #0
	mov	r0, #2
	str	r3, [r9, #3524]
	ldr	r2, [r10, #68]
	str	r3, [r9, #3520]
	mov	r5, r1
	ldr	r1, .L4048+4
	blx	r2
	mov	r3, r5
	ldr	r2, [fp, #-52]
	mov	r0, #2
	ldr	r1, .L4048+8
	ldr	ip, [r10, #68]
	blx	ip
	ldr	r3, [fp, #-52]
	cmp	r3, r5
	bgt	.L4038
	b	.L4039
.L4036:
	mov	r3, #0
	mov	r0, r6
	strb	r3, [r4, #1596]
	bl	MVC_StorePicInDpb
	movw	r2, #26758
	movt	r2, 42
	ldr	r1, [fp, #-60]
	subs	r3, r0, #0
	add	r0, r5, #1
	bne	.L4046
	ldr	r3, [r8, #2164]
	add	r2, r3, r2
	add	r2, r6, r2, lsl #2
	str	r5, [r2, #4]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-52]
	cmp	r3, r1
	mov	r5, r1
	ble	.L4039
.L4038:
	mov	r1, #1
	mov	r0, r6
	bl	MVC_AllocFrameStore
	ldr	r1, .L4048+12
	subs	r3, r0, #0
	mov	r0, #2
	bne	.L4047
	ldr	r2, [r10, #68]
	str	r3, [fp, #-48]
	blx	r2
	ldr	r2, [r4, #2112]
	strb	r7, [r4, #1598]
	ldr	r3, [fp, #-56]
	str	r5, [r2, #20]
	ldr	r2, [r4, #2112]
	str	r5, [r4, #2120]
	str	r5, [r2, #588]
	str	r3, [r4, #2128]
	ldr	r2, [r4, #2112]
	ldr	r3, [fp, #-48]
	str	r3, [r2, #584]
	ldr	r2, [r4, #2112]
	strb	r7, [r2, #7]
	ldr	r2, [r4, #2112]
	strb	r3, [r2, #5]
	ldr	r2, [r4, #2112]
	strb	r7, [r2, #1]
	strb	r7, [r4, #1594]
	ldr	r2, [r4, #2116]
	ldr	r1, [r8, #2160]
	str	r1, [r4, #2192]
	strb	r3, [r2, #3]
	ldr	r3, [r6, #236]
	ldr	r3, [r3, #2900]
	cmp	r3, #0
	beq	.L4036
	str	r5, [r9, #3536]
	mov	r0, r6
	bl	MVC_DecPOC
	ldr	r3, [r9, #3516]
	str	r3, [r4, #2132]
	ldr	r3, [r9, #3512]
	str	r3, [r4, #2136]
	ldr	r3, [r9, #3504]
	str	r3, [r4, #2140]
	ldr	r3, [r9, #3508]
	str	r3, [r4, #2144]
	b	.L4036
.L4045:
	ldr	r3, .L4048
	mov	r0, r5
	ldr	r1, .L4048+16
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4039:
	ldr	r2, [fp, #-64]
	mov	r0, #0
	ldr	r3, [fp, #-76]
	str	r2, [r9, #3520]
	add	r3, r3, #8192
	ldr	r2, [fp, #-68]
	str	r2, [r9, #3524]
	ldrb	r2, [fp, #-72]	@ zero_extendqisi2
	ldr	r3, [r3, #2116]
	strb	r2, [r3, #3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4047:
	ldr	r2, [fp, #-64]
	mov	r0, #0
	ldr	r3, [fp, #-76]
	ldr	r1, .L4048+20
	str	r2, [r9, #3520]
	add	r3, r3, #8192
	ldr	r2, [fp, #-68]
	str	r2, [r9, #3524]
	ldrb	r2, [fp, #-72]	@ zero_extendqisi2
	ldr	r3, [r3, #2116]
	strb	r2, [r3, #3]
	ldr	r3, [r10, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4046:
	ldr	r2, [fp, #-80]
	mov	r0, #0
	ldr	ip, [fp, #-64]
	add	r1, r2, #36864
	ldrb	lr, [fp, #-72]	@ zero_extendqisi2
	movw	r2, #6940
	str	ip, [r1, #3520]
	ldr	ip, [fp, #-68]
	str	ip, [r1, #3524]
	ldr	ip, [r4, #2116]
	ldr	r1, .L4048+24
	strb	lr, [ip, #3]
	ldr	r4, [r10, #68]
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4049:
	.align	2
.L4048:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC434
	.word	.LC435
	.word	.LC437
	.word	.LC433
	.word	.LC436
	.word	.LC438
	UNWIND(.fnend)
	.size	MVC_DecGap, .-MVC_DecGap
	.align	2
	.global	MVC_InitPic
	.type	MVC_InitPic, %function
MVC_InitPic:
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
	add	r5, r0, #11141120
	add	r3, r0, #11075584
	add	r5, r5, #8192
	add	r6, r3, #40960
	str	r3, [fp, #-56]
	ldrb	r1, [r5, #1592]	@ zero_extendqisi2
	mov	r7, #2240
	ldr	r3, [r0, #252]
	mov	r4, r0
	ldr	r2, [r6, #536]
	cmp	r1, #0
	mov	r1, #0
	str	r1, [fp, #-48]
	mla	r7, r7, r2, r3
	beq	.L4051
	ldr	r3, [r5, #2112]
	cmp	r3, r1
	beq	.L4052
	ldrb	r8, [r3, #2]	@ zero_extendqisi2
	cmp	r8, r1
	beq	.L4215
.L4052:
	mov	r3, #0
	strb	r3, [r5, #1592]
.L4051:
	sub	r1, fp, #48
	mov	r0, r4
	bl	MVC_GetReRangeFlag
	ldrb	r3, [r6, #532]	@ zero_extendqisi2
	cmp	r3, #255
	mov	r10, r0
	beq	.L4216
.L4053:
	cmp	r3, #0
	bne	.L4056
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L4217
	ldr	r3, [r7, #28]
	ldr	r2, [r4, #28]
	cmp	r2, r3
	movweq	r3, #35364
	movteq	r3, 168
	addeq	r3, r4, r3
	streq	r3, [r4, #236]
	bne	.L4218
.L4056:
	ldr	r3, [fp, #-56]
	add	r8, r3, #36864
	ldr	r3, [r7, #24]
	ldr	r2, [r8, #1264]
	cmp	r2, r3
	beq	.L4219
.L4060:
	ldr	r9, .L4234
	mov	r3, #0
	mov	r1, r7
	strb	r3, [r7, #20]
	ldr	r0, [r4, #236]
	bl	mvc_assign_quant_params
	movw	r0, #38104
	movt	r0, 169
	ldr	r3, [r9, #56]
	add	r0, r4, r0
	mov	r2, #2240
	mov	r1, r7
	blx	r3
.L4061:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ldr	r3, [r4, #224]
	bne	.L4220
	ldr	r2, [r3, #908]
	cmp	r2, #1
	beq	.L4063
.L4072:
	ldr	r2, [r8, #1264]
	ldr	r3, [r7, #24]
	ldr	r9, .L4234
	cmp	r2, r3
	bne	.L4081
	ldrb	r3, [r7, #20]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4081
.L4082:
	ldrb	r3, [r6, #532]	@ zero_extendqisi2
	cmp	r3, #255
	moveq	r3, #0
	streq	r3, [r6, #2164]
	beq	.L4084
	cmp	r3, #0
	bne	.L4084
	add	r1, r4, #10747904
	movw	r2, #22868
	add	r1, r1, #20480
	movt	r2, 164
	ldr	ip, [r6, #2160]
	add	r2, r4, r2
	ldr	r0, [r1, #2384]
	adds	r0, r0, #1
	beq	.L4085
	ldr	r1, [r1, #2388]
	cmp	ip, r1
	beq	.L4122
	mov	lr, r0
	b	.L4086
.L4087:
	ldr	r1, [r2, #4]!
	cmp	ip, r1
	beq	.L4085
.L4086:
	add	r3, r3, #1
	cmp	r3, lr
	mov	r0, r3
	bne	.L4087
.L4085:
	str	r0, [r6, #2164]
.L4084:
	ldrb	r2, [r6, #523]	@ zero_extendqisi2
	ldr	r3, [r4, #236]
	cmp	r2, #5
	ldreq	r1, [r6, #2164]
	ldr	r2, [r3, #2896]
	movweq	r3, #26758
	movteq	r3, 42
	addeq	r3, r1, r3
	ldreq	r7, [r6, #548]
	addeq	r3, r4, r3, lsl #2
	ldrne	r7, [r6, #548]
	streq	r7, [r3, #4]
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4090
	ldr	r10, [r4, #224]
	ldr	r3, [r10, #12]
	cmp	r3, #2
	beq	.L4090
	ldr	r1, [r6, #2164]
	movw	r3, #26758
	movt	r3, 42
	add	r3, r1, r3
	add	r3, r4, r3, lsl #2
	ldr	r0, [r3, #4]
	cmp	r0, r7
	beq	.L4090
	mov	r3, #1
	add	r2, r2, #4
	mov	r2, r3, asl r2
	add	r0, r0, r3
	str	r3, [fp, #-60]
	mov	r1, r2
	str	r2, [fp, #-64]
	bl	__aeabi_uidivmod
	cmp	r1, r7
	beq	.L4090
	ldr	r3, [fp, #-60]
	str	r3, [r10, #680]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #680]
	cmp	r2, #0
	beq	.L4221
.L4091:
	ldr	r3, [fp, #-56]
	add	r3, r3, #32768
	ldrb	r3, [r3, #1363]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4100
	ldr	r3, [r9, #68]
	mov	r0, #2
	ldr	r1, .L4234+4
	blx	r3
	ldr	r3, [r4, #224]
	ldr	r10, .L4234
	ldr	r3, [r3, #684]
	bics	r3, r3, #1024
	bne	.L4209
	ldr	r2, [r6, #2160]
	cmp	r2, #0
	bne	.L4209
	ldr	r0, [r6, #2164]
	movw	r3, #26758
	movt	r3, 42
	ldr	r1, [fp, #-64]
	add	r3, r0, r3
	str	r2, [fp, #-60]
	ldr	r7, [r6, #548]
	add	r3, r4, r3, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #1
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-60]
	cmp	r7, r1
	bcs	.L4090
	ldrb	r3, [r6, #520]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4090
	mov	r0, r4
	str	r2, [fp, #-56]
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r0, [r6, #2164]
	movw	r3, #26758
	ldr	r1, [fp, #-64]
	movt	r3, 42
	add	r3, r0, r3
	add	r3, r4, r3, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #1
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-56]
	ldr	r4, [r10, #68]
	ldr	r3, [r6, #548]
	mov	r0, r2
	movw	r2, #7466
	str	r1, [sp]
	ldr	r1, .L4234+8
	blx	r4
	mvn	r0, #0
.L4206:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4220:
	ldr	r9, [r3, #776]
	cmp	r9, #0
	bne	.L4063
	ldr	r2, [r3, #28]
	cmp	r2, #25
	beq	.L4222
.L4063:
	ldr	r2, [r4, #84]
	cmp	r10, #0
	add	r2, r2, #1
	str	r2, [r4, #84]
	bne	.L4073
	ldr	r3, [r3, #908]
	cmp	r3, #1
	beq	.L4074
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	cmp	r0, #0
	bne	.L4223
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	ldrne	r9, .L4234
	bne	.L4120
.L4121:
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #908]
	cmp	r3, #1
	bne	.L4072
.L4078:
	ldr	r1, [r8, #1220]
	mov	r0, r4
	ldr	r3, [fp, #-56]
	mov	r1, r1, asl #1
	add	ip, r3, #32768
	str	r1, [r4, #52]
	add	r3, r4, #48
	ldr	r2, [r8, #1200]
	ldrb	r9, [ip, #1364]	@ zero_extendqisi2
	add	r2, r2, #1
	ldr	r10, [r8, #1196]
	rsb	r9, r9, #2
	str	r1, [sp]
	mov	r2, r2, asl #4
	add	r10, r10, #1
	mul	r9, r9, r2
	mov	r10, r10, asl #4
	mov	r1, r10
	mov	r2, r9
	bl	MVC_ArrangeVahbMem
	cmp	r0, #1
	beq	.L4224
.L4212:
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #908]
	cmp	r3, #1
	mvneq	r0, #1
	beq	.L4206
	ldr	r3, .L4234
	mov	r5, #0
	mov	r0, r5
	str	r5, [r4, #12]
	str	r5, [r4, #16]
	ldr	r1, .L4234+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r1, r5
	mov	r0, r4
	bl	MVC_ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4081:
	movw	r0, #38104
	mov	r3, #0
	movt	r0, 169
	strb	r3, [r7, #20]
	add	r0, r4, r0
	mov	r1, r7
	ldr	r3, [r9, #56]
	mov	r2, #2240
	blx	r3
	b	.L4082
.L4100:
	mov	r0, r4
	bl	MVC_DecGap
	cmp	r0, #0
	bne	.L4103
.L4209:
	ldr	r7, [r6, #548]
.L4090:
	ldrb	r3, [r6, #528]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4104
	ldr	r2, [r6, #2164]
	movw	r3, #26758
	movt	r3, 42
	add	r3, r2, r3
	add	r3, r4, r3, lsl #2
	str	r7, [r3, #4]
.L4104:
	mov	r0, r4
	str	r7, [r8, #3536]
	bl	MVC_DecPOC
	mov	r1, #0
	mov	r0, r4
	bl	MVC_AllocFrameStore
	cmp	r0, #0
	bne	.L4225
	strb	r0, [r5, #1599]
	mov	r1, #1
	strb	r1, [r5, #1592]
	mvn	r10, #0
	ldrb	r3, [r6, #523]	@ zero_extendqisi2
	strb	r3, [r5, #1598]
	ldr	r3, [r6, #548]
	str	r3, [r5, #2120]
	str	r3, [fp, #-64]
	ldrb	r3, [r6, #528]	@ zero_extendqisi2
	str	r3, [r5, #2128]
	ldr	r7, [r8, #3516]
	str	r3, [fp, #-60]
	str	r7, [r5, #2132]
	ldr	ip, [r8, #3512]
	str	ip, [r5, #2136]
	ldr	lr, [r8, #3504]
	str	lr, [r5, #2140]
	ldr	r2, [r8, #3508]
	str	lr, [r5, #2156]
	str	r7, [r5, #2148]
	str	r2, [r5, #2144]
	str	r2, [r5, #2160]
	str	ip, [r5, #2152]
	strb	r0, [r5, #1594]
	strb	r0, [r5, #1597]
	strb	r0, [r5, #1596]
	str	r10, [r5, #2184]
	ldrb	r10, [r6, #521]	@ zero_extendqisi2
	cmp	r10, #0
	strneb	r1, [r6, #521]
	ldr	r7, [r4, #236]
	movne	r10, r1
	movne	r1, #2
	ldrb	r0, [r7, #20]	@ zero_extendqisi2
	ldr	ip, [r7, #3952]
	rsb	r0, r0, #2
	mla	r0, ip, r0, r0
	bl	__aeabi_uidiv
	cmp	r10, #0
	ldr	r3, [fp, #-60]
	str	r0, [r5, #2172]
	ldrb	r1, [r7, #20]	@ zero_extendqisi2
	ldr	lr, [r7, #3952]
	rsb	ip, r1, #2
	mla	ip, lr, ip, ip
	str	ip, [r5, #2176]
	ldr	ip, [r7, #3948]
	add	r1, ip, #1
	str	r1, [r5, #2168]
	mul	r1, r1, r0
	str	r1, [r5, #2180]
	ldrb	r1, [r8, #1240]	@ zero_extendqisi2
	strb	r1, [r5, #1600]
	movne	r1, #0
	bne	.L4107
	ldrb	r1, [r7, #21]	@ zero_extendqisi2
	adds	r1, r1, #0
	movne	r1, #1
.L4107:
	cmp	r3, #0
	strb	r1, [r5, #1601]
	beq	.L4108
	ldr	r1, [r6, #2164]
	movw	r3, #26758
	movt	r3, 42
	ldr	r2, [fp, #-64]
	add	r3, r1, r3
	add	r3, r4, r3, lsl #2
	str	r2, [r3, #4]
.L4108:
	ldr	r3, [r5, #2112]
	cmp	r3, #0
	ldrneb	r2, [r6, #532]	@ zero_extendqisi2
	strneb	r2, [r3, #9]
	mvn	r3, #0
	str	r3, [r5, #2192]
	ldrb	r3, [r6, #531]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4110
	ldr	r3, [r6, #2160]
	str	r3, [r5, #2192]
	ldrb	r3, [r6, #529]	@ zero_extendqisi2
	strb	r3, [r5, #1602]
	ldrb	r3, [r6, #530]	@ zero_extendqisi2
	strb	r3, [r5, #1603]
.L4110:
	ldr	r2, [r6, #2164]
	movw	r0, #2004
	movw	r3, #43184
	movw	lr, #9808
	movt	r3, 169
	movt	lr, 170
	str	r2, [r5, #2196]
	movw	r7, #9824
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	movt	r7, 170
	add	r7, r4, r7
	movw	r8, #9824
	movt	r8, 170
	ldr	r1, .L4234+16
	mla	r2, r0, r2, r4
	mov	r0, #29
	add	r3, r2, r3
	str	r3, [r5, #2116]
	ldr	ip, [r4, #224]
	ldrd	r2, [ip, #48]
	strd	r2, [r4, lr]
	ldrd	r2, [ip, #64]
	strd	r2, [r7, #-8]
	ldrd	r2, [ip, #80]
	strd	r2, [r4, r8]
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [ip, #48]
	ldrd	r2, [r4, lr]
	ldr	r8, [r9, #68]
	blx	r8
	ldrd	r2, [r7, #-8]
	ldr	r8, [r9, #68]
	mov	r0, #29
	ldr	r1, .L4234+20
	blx	r8
	ldr	ip, [r4, #236]
	ldr	r3, [fp, #-56]
	movw	lr, #8864
	movw	r0, #9800
	ldr	r7, .L4234
	add	r1, r3, #32768
	ldr	r3, [ip, #3948]
	movt	r0, 170
	add	r0, r4, r0
	add	r3, r3, #1
	mov	r3, r3, asl #4
	str	r3, [r5, #1772]
	ldrb	r2, [ip, #20]	@ zero_extendqisi2
	ldr	r8, [ip, #3952]
	rsb	r3, r2, #2
	mla	r3, r8, r3, r3
	mov	r3, r3, asl #4
	str	r3, [r5, #1776]
	ldr	r1, [r1, #1396]
	str	lr, [r5, #1768]
	ldr	r2, [ip, #56]
	and	r1, r1, #7
	ldrb	r3, [ip, #52]	@ zero_extendqisi2
	ldr	ip, [ip, #748]
	mov	r2, r2, asl #5
	subs	ip, ip, #1
	uxtb	r2, r2
	movne	ip, #1
	orr	r3, r2, r3, asl #14
	orr	r3, r3, ip, asl #2
	str	r3, [r5, #1768]
	bl	SetAspectRatio
	ldr	r0, [r5, #2112]
	ldr	r3, [r4, #84]
	cmp	r0, #0
	str	r3, [r5, #1812]
	beq	.L4226
	ldr	r3, [r4, #236]
	ldr	r3, [r3, #3984]
	str	r3, [r0, #252]
	str	r3, [r5, #1788]
	ldr	r3, [r4, #236]
	ldr	r2, [r5, #2112]
	ldr	r3, [r3, #3988]
	str	r3, [r2, #256]
	str	r3, [r5, #1792]
	ldr	r3, [r4, #236]
	ldr	r2, [r5, #2112]
	ldr	r3, [r3, #3976]
	str	r3, [r2, #244]
	str	r3, [r5, #1780]
	ldr	r2, [r4, #236]
	ldr	r3, [r5, #2112]
	ldr	r2, [r2, #3980]
	str	r2, [r3, #248]
	ldrb	r3, [r5, #1595]	@ zero_extendqisi2
	ldr	r1, [r5, #2112]
	ldr	r0, [r5, #1768]
	adds	r3, r3, #0
	str	r2, [r5, #1784]
	movne	r3, #1
	str	r3, [r5, #1756]
	str	r0, [r1, #232]
	ldr	r2, [r5, #1756]
	ldr	r3, [r5, #2112]
	str	r2, [r3, #220]
	ldr	r3, [r6, #548]
	ldr	r2, [r5, #2112]
	str	r3, [r5, #1848]
	ldr	r1, [r6, #2160]
	str	r1, [r5, #1856]
	str	r3, [r2, #312]
	ldr	r3, [r5, #2112]
	ldr	r2, [r6, #2160]
	str	r2, [r3, #320]
	ldr	r3, [r5, #2112]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L4112
	ldr	r3, [r5, #1756]
	mov	r1, #0
	ldr	r2, [r0, #4]
	subs	r3, r3, r1
	ldr	r0, [r4, #120]
	movne	r3, #1
	bl	FSP_SetStoreType
.L4112:
	movw	r2, #10008
	movw	r0, #10024
	ldr	r6, [r4, #60]
	movt	r2, 170
	movt	r0, 170
	add	r2, r4, r2
	add	r0, r4, r0
	mov	lr, #0
.L4116:
	ldr	r3, [r2, #4]!
	cmp	r3, #0
	beq	.L4227
.L4113:
	cmp	r2, r0
	bne	.L4116
	cmp	r6, #0
	beq	.L4118
	ble	.L4118
	add	r7, r6, #132
	mov	r8, #0
	add	r7, r4, r7, lsl #2
.L4119:
	ldr	r1, [r7, #-4]!
	sub	r6, r6, #1
	ldr	r0, [r4, #120]
	bl	FreeUsdByDec
	cmp	r6, #0
	str	r8, [r7]
	bne	.L4119
.L4118:
	mov	r6, #0
	mov	r0, r4
	str	r6, [r4, #60]
	strb	r6, [r5, #1604]
	bl	MVC_UpdateReflist
	mov	r0, r4
	bl	MVC_UpdateLTReflist
	mov	r0, r4
	bl	MVC_CalcPicNum
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4219:
	ldrb	r3, [r7, #20]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4061
	b	.L4060
.L4227:
	cmp	r6, #0
	beq	.L4113
	ldr	r1, [r4, #528]
	subs	r6, r6, #1
	str	r1, [r2]
	beq	.L4114
	add	r1, r4, #528
.L4115:
	add	r3, r3, #1
	ldr	ip, [r1, #4]!
	cmp	r3, r6
	str	ip, [r1, #-4]
	bne	.L4115
.L4114:
	add	r3, r6, #132
	str	lr, [r4, r3, asl #2]
	str	r6, [r4, #60]
	b	.L4113
.L4216:
	mov	r2, #1
	strb	r2, [r4, #2]
	ldr	r1, [r7, #28]
	movw	lr, #3992
	ldr	ip, [r4, #248]
	movw	r8, #34112
	ldr	r2, [fp, #-56]
	str	r1, [r4, #24]
	ldr	r1, [r7, #28]
	add	r2, r2, #32768
	ldr	r0, [r2, #2088]
	mla	r1, lr, r1, ip
	ldr	r2, [r1, #744]
	cmp	r0, r2
	beq	.L4228
.L4054:
	ldr	r9, .L4234
	movt	r8, 169
	ldr	r3, [r4, #84]
	add	r8, r4, r8
	mov	r2, #0
	add	r3, r3, #1
	mov	r0, r8
	str	r3, [r4, #84]
	strb	r2, [r1, #26]
	movw	r2, #3992
	ldr	r3, [r9, #56]
	blx	r3
	ldrb	r3, [r6, #532]	@ zero_extendqisi2
.L4055:
	str	r8, [r4, #236]
	b	.L4053
.L4074:
	ldr	r9, .L4234
	mov	r0, #22
	ldr	r1, .L4234+24
	ldr	r3, [r9, #68]
	blx	r3
	mov	r0, r4
	bl	MVC_GetBackPicFromVOQueue
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L4121
.L4120:
	mov	r3, r0
	ldr	r4, [r9, #68]
	movw	r2, #7301
	ldr	r1, .L4234+28
	mov	r0, #0
	blx	r4
	mvn	r0, #0
	b	.L4206
.L4228:
	ldrb	r2, [r1, #26]	@ zero_extendqisi2
	cmp	r2, #0
	movteq	r8, 169
	addeq	r8, r4, r8
	beq	.L4055
	b	.L4054
.L4215:
	ldrsb	r1, [r3, #6]
	mov	r2, #1
	ldr	r0, [r0, #120]
	bl	FSP_ClearLogicFs
	ldr	r3, [r5, #2112]
	strb	r8, [r3, #2]
	ldr	r3, [r5, #2112]
	strb	r8, [r3, #5]
	b	.L4052
.L4221:
	ldr	r2, [r3, #708]
	cmp	r2, #1
	beq	.L4229
.L4092:
	ldr	r3, [r6, #2164]
	ldr	r1, [r6, #548]
	add	r3, r4, r3, lsl #2
	add	r3, r3, #11075584
	add	r2, r3, #40960
	ldr	r2, [r2, #540]
	cmp	r1, r2
	bls	.L4093
	ldr	ip, [r8, #1220]
	rsb	r0, r2, r1
	cmp	r2, #0
	cmpne	ip, r0
	bcs	.L4091
	ldrb	r2, [r6, #520]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L4230
	cmp	r1, #0
	add	r3, r3, #40960
	subne	r2, r1, #1
	mov	r0, r4
	ldreq	r2, [fp, #-64]
	mvn	r1, #0
	subeq	r2, r2, #1
	str	r2, [r3, #540]
	bl	MVC_FlushDPB
	subs	r3, r0, #0
	beq	.L4091
	ldr	r4, [r9, #68]
	movw	r2, #7412
	ldr	r1, .L4234+32
	mov	r0, #0
	blx	r4
	mvn	r0, #0
	b	.L4206
.L4217:
	strb	r3, [r4, #2]
	movw	r2, #8500
	ldr	r1, [r7, #28]
	movt	r2, 5
	ldr	r9, .L4234
	movw	r0, #22860
	movt	r0, 164
	add	r0, r4, r0
	mla	r1, r2, r1, r4
	ldr	r3, [r9, #56]
	add	r1, r1, #12992
	add	r1, r1, #12
	blx	r3
	add	r2, r4, #11010048
	add	r2, r2, #32768
	movw	r3, #35364
	movt	r3, 168
	add	r3, r4, r3
	str	r3, [r4, #236]
	ldr	r3, [r2, #3340]
	str	r3, [r4, #28]
	b	.L4056
.L4222:
	ldr	r3, [r4, #84]
	cmp	r10, #0
	add	r3, r3, #1
	str	r3, [r4, #84]
	beq	.L4064
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r3, r0, #0
	beq	.L4064
	ldr	ip, .L4234
	mov	r0, r9
	movw	r2, #7208
	ldr	r1, .L4234+32
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L4206
.L4064:
	mov	r0, r4
	bl	MVC_InitDPB
	subs	r3, r0, #0
	bne	.L4231
	ldr	r2, [fp, #-56]
	cmp	r10, #0
	ldr	r3, [r8, #1200]
	add	r2, r2, #32768
	ldr	r9, [r8, #1196]
	add	r3, r3, #1
	ldrb	r10, [r2, #1364]	@ zero_extendqisi2
	add	r9, r9, #1
	mov	r3, r3, asl #4
	rsb	r10, r10, #2
	mov	r9, r9, asl #4
	mul	r10, r10, r3
	beq	.L4066
	ldr	r3, [r4, #12]
	cmp	r3, #0
	bne	.L4066
	ldr	r3, [r8, #1220]
	ldr	ip, [r4, #224]
	mov	r3, r3, asl #1
	str	r3, [r4, #52]
	ldr	r1, [ip, #736]
	str	r3, [fp, #-60]
	cmp	r9, r1
	bhi	.L4067
	ldr	r2, [ip, #740]
	cmp	r10, r2
	bhi	.L4067
	ldr	lr, [fp, #-56]
	ldr	r3, [ip, #760]
	add	lr, lr, #45056
	ldr	lr, [lr, #2376]
	cmp	r3, lr
	bcc	.L4232
	ldr	r0, [ip, #764]
	cmp	r0, #0
	mov	r0, r4
	moveq	r3, #1
	streq	r3, [r4, #52]
	streq	r3, [fp, #-60]
	ldr	r3, [fp, #-60]
	ldreq	r1, [ip, #736]
	ldreq	r2, [ip, #740]
	str	r3, [sp]
	add	r3, r4, #48
	bl	MVC_ArrangeVahbMem
	cmp	r0, #1
	bne	.L4212
.L4066:
	mov	r9, r9, lsr #4
	mov	r10, r10, lsr #4
	str	r9, [r4, #12]
	str	r10, [r4, #16]
	b	.L4072
.L4073:
	ldr	r9, .L4234
	mov	r0, #22
	ldr	r1, .L4234+24
	ldr	r3, [r9, #68]
	blx	r3
	mov	r0, r4
	bl	MVC_GetBackPicFromVOQueue
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L4078
	b	.L4120
.L4224:
	mov	r10, r10, lsr #4
	mov	r9, r9, lsr #4
	str	r10, [r4, #12]
	str	r9, [r4, #16]
	b	.L4072
.L4093:
	ldr	lr, [fp, #-64]
	rsb	r0, r2, r1
	ldr	ip, [r8, #1220]
	add	r0, r0, lr
	cmp	r2, #0
	cmpne	ip, r0
	bcs	.L4091
	ldrb	r2, [r6, #520]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L4233
	cmp	r1, #0
	add	r3, r3, #40960
	subne	r2, r1, #1
	mov	r0, r4
	ldreq	r2, [fp, #-64]
	mvn	r1, #0
	subeq	r2, r2, #1
	str	r2, [r3, #540]
	bl	MVC_FlushDPB
	subs	r3, r0, #0
	beq	.L4091
	ldr	r4, [r9, #68]
	movw	r2, #7439
	ldr	r1, .L4234+32
	mov	r0, #0
	blx	r4
	mvn	r0, #0
	b	.L4206
.L4218:
	ldr	r3, .L4234
	mov	r0, #1
	ldr	r1, .L4234+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L4206
.L4103:
	ldr	r3, [r9, #68]
	movw	r2, #7493
	ldr	r1, .L4234+40
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	b	.L4206
.L4229:
	ldr	r2, [r3, #704]
	cmp	r2, #0
	bne	.L4092
	ldr	r2, [r3, #712]
	cmp	r2, #0
	bne	.L4092
	ldr	r3, [r3, #684]
	add	r3, r3, #1024
	cmp	r3, #2048
	bhi	.L4091
	b	.L4092
.L4122:
	mov	r0, r3
	b	.L4085
.L4225:
	ldr	r3, [r9, #68]
	movw	r2, #7513
	ldr	r1, .L4234+44
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	b	.L4206
.L4226:
	ldr	r3, [r7, #68]
	movw	r2, #7621
	ldr	r1, .L4234+48
	blx	r3
	mvn	r0, #0
	b	.L4206
.L4223:
	ldr	ip, .L4234
	mov	r3, r0
	movw	r2, #7292
	mov	r0, r10
	ldr	r1, .L4234+32
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L4206
.L4231:
	ldr	ip, .L4234
	movw	r2, #7217
	ldr	r1, .L4234+28
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L4206
.L4067:
	ldr	r3, .L4234
	mov	r0, #0
	ldr	r1, .L4234+52
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L4206
.L4232:
	ldr	r3, .L4234
	ldr	r1, .L4234+56
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L4206
.L4233:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r2, [r6, #2164]
	ldr	r3, [r8, #1220]
	movw	r1, #26758
	ldr	ip, [r6, #548]
	movt	r1, 42
	add	r1, r2, r1
	movw	r2, #7428
.L4211:
	add	r1, r4, r1, lsl #2
	str	r3, [sp]
	mov	r0, #0
	ldr	r4, [r9, #68]
	ldr	r3, [r1, #4]
	ldr	r1, .L4234+60
	rsb	r3, r3, ip
	blx	r4
	mvn	r0, #0
	b	.L4206
.L4230:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r2, [r6, #2164]
	movw	r1, #26758
	ldr	r3, [r8, #1220]
	movt	r1, 42
	ldr	ip, [r6, #548]
	add	r1, r2, r1
	movw	r2, #7401
	b	.L4211
.L4235:
	.align	2
.L4234:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC445
	.word	.LC446
	.word	.LC443
	.word	.LC449
	.word	.LC450
	.word	.LC452
	.word	.LC440
	.word	.LC439
	.word	.LC30
	.word	.LC447
	.word	.LC448
	.word	.LC451
	.word	.LC441
	.word	.LC442
	.word	.LC444
	UNWIND(.fnend)
	.size	MVC_InitPic, .-MVC_InitPic
	.align	2
	.global	MVC_DecSlice
	.type	MVC_DecSlice, %function
MVC_DecSlice:
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
	ldr	r6, .L4287
	ldr	r2, [r0, #68]
	mov	r4, r0
	ldr	r1, .L4287+4
	mov	r0, #22
	sub	r2, r2, #1
	ldr	r3, [r6, #68]
	blx	r3
	ldr	r3, [r4, #232]
	add	r5, r4, #11075584
	mov	r0, r4
	add	r5, r5, #40960
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	strb	r2, [r5, #523]
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	strb	r3, [r5, #528]
	bl	MVC_ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L4281
	mov	r0, r4
	bl	MVC_ProcessSliceHeaderSecondPart
	cmp	r0, #0
	bne	.L4281
	ldr	r2, [r4, #64]
	cmp	r2, #0
	moveq	r3, r2
	beq	.L4243
	movw	r10, #11024
	mov	r3, r0
	movt	r10, 170
	add	r10, r4, r10
	mov	r8, r0
	mov	r7, r0
.L4251:
	ldr	ip, [r10, #4]!
	ldr	lr, [ip, #8]
	ldr	r1, [ip, #36]
	cmp	lr, #0
	ldrne	r9, [ip, #12]
	moveq	r9, lr
	cmp	r1, #0
	moveq	ip, r1
	ldrne	ip, [ip, #40]
	cmp	r8, #0
	addeq	r3, r9, r3
	addeq	r3, r3, ip
	beq	.L4249
	cmp	lr, r8
	add	r3, ip, r3
	addhi	r0, r8, r0
	rsbhi	r0, r0, lr
	movls	r0, r9
	addhi	r0, r0, r9
	add	r3, r3, r0
.L4249:
	cmp	r1, #0
	add	r7, r7, #1
	movne	r8, r1
	movne	r0, ip
	moveq	r8, lr
	moveq	r0, r9
	cmp	r7, r2
	bne	.L4251
.L4243:
	add	r7, r4, #11141120
	str	r3, [r4, #104]
	add	r7, r7, #8192
	movw	r0, #1620
	ldr	ip, [r7, #2172]
	ldr	r1, [r7, #2168]
	mul	r1, r1, ip
	cmp	r1, r0
	movgt	r1, r1, asl #7
	ble	.L4282
.L4253:
	ldr	r0, [r4, #32]
	cmp	r0, r2
	bls	.L4254
	cmp	r1, r3
	bcc	.L4254
	ldrb	r3, [r5, #525]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4283
.L4257:
	mov	r0, r4
	bl	MVC_PicTypeStatistic
	mov	r0, r4
	bl	MVC_DecList
	cmp	r0, #0
	bne	.L4284
	mov	r0, r4
	bl	MVC_IsRefListWrong
	subs	r5, r0, #0
	bne	.L4285
	mov	r0, r4
	bl	MVC_CalcStreamBits
	mov	r0, r4
	bl	MVC_WriteSliceMsg
	mov	r0, r4
	bl	MVC_ExitSlice
	ldr	r3, [r4, #100]
	mov	r0, r5
	mov	r2, #1
	add	r3, r3, r2
	strb	r2, [r4, #4]
	str	r3, [r4, #100]
.L4240:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4282:
	mov	r0, r1, asl #9
	sub	r1, r0, r1, asl #7
	cmp	r1, #16384
	movlt	r1, #16384
	b	.L4253
.L4283:
	ldr	r3, [r6, #68]
	mov	r0, #2
	ldr	r1, .L4287+8
	blx	r3
	ldr	r3, [r4, #88]
	mov	r2, #0
	str	r2, [r4, #100]
	add	r3, r3, #1
	str	r3, [r4, #88]
	ldrb	r3, [r7, #1595]	@ zero_extendqisi2
	mov	r0, r4
	cmp	r3, r2
	ldreq	r3, [r4, #92]
	ldrne	r3, [r4, #96]
	addeq	r3, r3, #1
	addne	r3, r3, #1
	streq	r3, [r4, #92]
	strne	r3, [r4, #96]
	bl	MVC_InitPic
	cmn	r0, #2
	beq	.L4240
	cmp	r0, #0
	bne	.L4286
	mov	r0, r4
	bl	MVC_WritePicMsg
	b	.L4257
.L4281:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L4287+12
	blx	r3
	ldr	r3, .L4287+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4279
	sub	r2, fp, #44
	mvn	r1, #0
	mov	r3, #4
	str	r1, [r2, #-8]!
	mov	r1, #100
	ldr	r0, [r4, #120]
	blx	r5
.L4279:
	mov	r0, r4
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	b	.L4240
.L4254:
	str	r1, [sp]
	mov	r0, #0
	ldr	r5, [r6, #68]
	ldr	r1, .L4287+20
	blx	r5
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #32]
	cmp	r3, r2
	bcc	.L4256
	ldr	r1, .L4287+16
	ldr	r5, [r1]
	cmp	r5, #0
	beq	.L4256
	str	r3, [fp, #-52]
	mov	r1, #108
	str	r2, [fp, #-48]
	mov	r3, #8
	sub	r2, fp, #52
	ldr	r0, [r4, #120]
	blx	r5
.L4256:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L4287+24
	blx	r3
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L4240
.L4284:
	mov	r2, r0
	ldr	r3, [r6, #68]
	ldr	r1, .L4287+28
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	b	.L4240
.L4285:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L4287+32
	blx	r3
	b	.L4279
.L4286:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L4287+36
	blx	r3
	mvn	r0, #0
	b	.L4240
.L4288:
	.align	2
.L4287:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC392
	.word	.LC455
	.word	.LC393
	.word	g_event_report
	.word	.LC453
	.word	.LC454
	.word	.LC457
	.word	.LC458
	.word	.LC456
	UNWIND(.fnend)
	.size	MVC_DecSlice, .-MVC_DecSlice
	.align	2
	.global	MVC_DecOneNal
	.type	MVC_DecOneNal, %function
MVC_DecOneNal:
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
	ldr	ip, [r0, #232]
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [ip, #68]
	cmp	r3, #0
	ldrne	r1, [r0, #104]
	movne	r2, ip
	movne	r3, #0
	beq	.L4294
.L4293:
	ldr	r0, [r2, #12]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, r0
	str	r1, [r4, #104]
	ldr	r0, [ip, #68]
	cmp	r0, r3
	bhi	.L4293
.L4294:
	add	r7, r4, #548
	mov	r8, #0
	mov	r1, #32
	strb	r8, [ip]
	mov	r0, r7
	bl	BsGet
	ldr	r3, [r4, #232]
	and	r1, r0, #31
	strb	r1, [r3, #2]
	ldr	r3, [r4, #232]
	mov	r6, r0
	ubfx	r0, r0, #5, #2
	ubfx	r2, r6, #7, #1
	mvn	r1, #0
	strb	r0, [r3, #4]
	ldr	r3, [r4, #232]
	str	r2, [r3, #76]
	ldr	r2, [r4, #232]
	ldr	r3, [r2, #64]
	add	r3, r3, #32
	str	r3, [r2, #64]
	ldr	r3, [r4, #232]
	strb	r8, [r4, #10]
	strb	r1, [r3, #5]
	ldr	r3, [r4, #232]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #14
	cmpne	r3, #20
	beq	.L4475
.L4292:
	ldr	r8, .L4486
	mov	r0, #22
	ldr	r2, [r4, #68]
	ldr	r1, .L4486+4
	ldr	r9, [r8, #68]
	blx	r9
	ldr	r3, [r4, #68]
	movw	r2, #371
	cmp	r3, r2
	beq	.L4476
.L4297:
	ldr	r2, [r4, #232]
	add	r3, r3, #1
	str	r3, [r4, #68]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	sub	r3, r2, #1
	cmp	r3, #29
	ldrls	pc, [pc, r3, asl #2]
	b	.L4298
.L4300:
	.word	.L4299
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4299
	.word	.L4301
	.word	.L4302
	.word	.L4303
	.word	.L4304
	.word	.L4305
	.word	.L4306
	.word	.L4307
	.word	.L4308
	.word	.L4309
	.word	.L4310
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4311
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4298
	.word	.L4312
.L4475:
	mov	r1, #24
	mov	r0, r7
	bl	BsGet
	ldr	r3, [r4, #232]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #5]
	ldr	r3, [r4, #232]
	mov	r6, r0
	ldrsb	r2, [r3, #5]
	cmp	r2, #0
	bne	.L4295
	add	r2, r4, #12288
	mov	r0, #1
	ubfx	r1, r6, #16, #6
	ubfx	ip, r6, #6, #10
	strb	r0, [r2, #704]
	ubfx	r0, r6, #3, #3
	strb	r1, [r2, #706]
	ubfx	r1, r6, #2, #1
	strb	r0, [r2, #707]
	ubfx	r0, r6, #1, #1
	strb	r1, [r2, #708]
	and	r1, r6, #1
	strb	r0, [r2, #709]
	ubfx	r0, r6, #22, #1
	str	ip, [r2, #712]
	strb	r1, [r2, #710]
	strb	r0, [r2, #705]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #20
	beq	.L4477
.L4295:
	ldr	r2, [r3, #64]
	add	r2, r2, #24
	str	r2, [r3, #64]
	ldr	r3, [r4, #232]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	b	.L4292
.L4299:
	ldr	r5, [r8, #68]
	mov	r0, #22
	ldr	r3, [r4, #80]
	ldr	r1, .L4486+8
	blx	r5
	ldr	r3, [r4, #232]
	add	r0, r4, #11075584
	add	r2, r4, #12288
	add	r0, r0, #40960
	mvn	lr, #0
	ldrb	ip, [r3, #2]	@ zero_extendqisi2
	mov	r1, #0
	strb	ip, [r0, #523]
	ldrb	r5, [r3, #4]	@ zero_extendqisi2
	strb	r5, [r0, #528]
	ldrb	r3, [r3, #5]	@ zero_extendqisi2
	str	lr, [r0, #2160]
	strb	r1, [r0, #531]
	strb	r3, [r0, #532]
	ldrb	lr, [r2, #704]	@ zero_extendqisi2
	cmp	lr, #1
	beq	.L4478
	cmp	r3, #255
	beq	.L4479
.L4314:
	ldr	r3, [r8, #68]
	mov	r0, #21
	ldr	r2, [r4, #88]
	ldr	r1, .L4486+12
	blx	r3
	mov	r0, r4
	bl	MVC_SliceCheck
	subs	r5, r0, #0
	mov	r0, r4
	bne	.L4480
	bl	MVC_DecSlice
	cmn	r0, #2
	beq	.L4325
	cmp	r0, #0
	beq	.L4456
	ldr	r3, .L4486+16
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L4455
	ldr	r0, [r4, #120]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r6
.L4455:
	mvn	r0, #0
	b	.L4325
.L4301:
	ldr	r1, .L4486+20
	mov	r2, #6
	ldr	r3, [r8, #68]
	mov	r0, #22
	blx	r3
	mov	r0, r4
	bl	MVC_DecSEI
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4332
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4332:
	cmp	r5, #0
	bne	.L4481
.L4456:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4302:
	ldr	r1, .L4486+24
	mov	r2, #7
	ldr	r5, [r8, #68]
	mov	r0, #22
	ldr	r3, [r4, #72]
	blx	r5
	mov	r0, r4
	bl	MVC_DecSPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4330
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4330:
	cmp	r5, #0
	bne	.L4482
	ldr	r3, [r4, #72]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #72]
	b	.L4325
.L4304:
	ldr	r3, [r8, #68]
	mov	r2, #9
	ldr	r1, .L4486+28
.L4463:
	mov	r0, #22
	blx	r3
.L4468:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4456
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #232]
.L4325:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4305:
	ldr	r3, [r8, #68]
	mov	r2, #10
	ldr	r1, .L4486+32
	b	.L4463
.L4303:
	ldr	r1, .L4486+36
	mov	r2, #8
	ldr	r5, [r8, #68]
	mov	r0, #22
	ldr	r3, [r4, #76]
	blx	r5
	mov	r0, r4
	bl	MVC_DecPPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4328
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4328:
	cmp	r5, #0
	bne	.L4483
	ldr	r3, [r4, #76]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #76]
	b	.L4325
.L4306:
	ldr	r3, [r8, #68]
	mov	r2, #11
	ldr	r1, .L4486+40
	mov	r0, #22
	blx	r3
	mov	r1, #32
	mov	r0, r7
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r7
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r5, r3
	bne	.L4468
	ldr	r5, .L4486+16
	mov	r3, #1
	strb	r3, [r4, #1]
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4335
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	r6
.L4335:
	mov	r6, #0
	mov	r0, r4
	strb	r6, [r4]
	bl	MVC_DecVDM
	cmp	r0, r6
	beq	.L4468
	b	.L4471
.L4307:
	ldr	r3, [r8, #68]
	mov	r2, #12
	ldr	r1, .L4486+44
	b	.L4463
.L4308:
	ldr	r3, [r8, #68]
	mov	r2, #13
	ldr	r1, .L4486+48
	b	.L4463
.L4309:
	ldr	r3, [r8, #68]
	mov	r2, #14
	ldr	r1, .L4486+52
	b	.L4463
.L4310:
	ldr	r1, .L4486+56
	mov	r2, #15
	ldr	r3, [r8, #68]
	mov	r0, #22
	blx	r3
	mov	r0, r4
	bl	MVC_DecSubSPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4336
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4336:
	cmp	r5, #0
	bne	.L4484
	ldr	r3, [r4, #20]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #20]
	b	.L4325
.L4311:
	ldr	r3, [r8, #68]
	mov	r2, #19
	ldr	r1, .L4486+60
	b	.L4463
.L4312:
	ldr	r3, [r8, #68]
	mov	r2, #30
	ldr	r1, .L4486+64
	mov	r0, #22
	blx	r3
	cmp	r5, #0
	bne	.L4338
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4338
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	str	r5, [r4, #232]
.L4338:
	mov	r1, #32
	mov	r0, r7
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r7
	bl	BsGet
	ldr	r3, .L4486+68
	rev	r5, r5
	ldr	r2, [r3, #440]
	ldr	r3, [r3, #436]
	rev	r0, r0
	cmp	r0, r2
	cmpeq	r5, r3
	bne	.L4456
	ldr	r5, .L4486+16
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4339
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	r6
.L4339:
	mov	r6, #0
	mov	r0, r4
	strb	r6, [r4]
	bl	MVC_DecVDM
	cmp	r0, r6
	beq	.L4456
.L4471:
	ldr	r5, [r5]
	cmp	r5, r6
	beq	.L4455
	ldr	r0, [r4, #120]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4325
.L4298:
	ldr	r5, [r8, #68]
	mov	r3, r6
	ldr	r1, .L4486+72
	mov	r0, #22
	blx	r5
	cmp	r6, #256
	ldr	r7, .L4486
	beq	.L4340
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L4486+76
	blx	r3
.L4340:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4341
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4341:
	ldr	r3, .L4486+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4456
.L4460:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L4456
.L4476:
	ldr	r3, [r8, #68]
	mov	r0, #22
	ldr	r1, .L4486+80
	blx	r3
	ldr	r3, [r4, #68]
	b	.L4297
.L4477:
	cmp	r0, #0
	movne	r2, #1
	moveq	r2, #5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #232]
	b	.L4295
.L4480:
	bl	MVC_ClearCurrSlice
	ldr	r3, .L4486+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4455
.L4324:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4325
.L4483:
	ldr	r5, .L4486+16
	mov	r0, #1
	ldr	r3, [r8, #68]
	ldr	r1, .L4486+84
	blx	r3
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4455
.L4473:
	sub	r2, fp, #36
	mvn	r7, #0
	mov	r3, #4
	mov	r1, #100
	str	r7, [r2, #-4]!
	ldr	r0, [r4, #120]
	blx	r6
	ldr	r5, [r5]
	cmp	r5, #0
	bne	.L4324
	b	.L4455
.L4484:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L4486+88
	blx	r3
	ldr	r3, .L4486+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4455
	sub	r2, fp, #36
	ldr	r0, [r4, #120]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	r5
	mov	r0, r4
	b	.L4325
.L4482:
	ldr	r5, .L4486+16
	mov	r0, #1
	ldr	r3, [r8, #68]
	ldr	r1, .L4486+92
	blx	r3
	ldr	r6, [r5]
	cmp	r6, #0
	bne	.L4473
	b	.L4455
.L4481:
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L4486+96
	blx	r3
	ldr	r3, .L4486+16
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L4460
	b	.L4456
.L4479:
	ldr	r3, [r4, #20]
	cmp	r3, #0
	beq	.L4314
	add	r3, r4, #10747904
	add	r3, r3, #20480
	ldr	r2, [r3, #2384]
	cmp	r2, #0
	beq	.L4317
	ldrb	r2, [r3, #2380]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L4318
.L4317:
	add	r3, r4, #12992
	mov	r2, #0
	add	r3, r3, #16
.L4321:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L4319
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L4485
.L4319:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L4321
	mvn	r3, #0
.L4454:
	cmn	r3, #1
	str	r3, [r0, #2160]
	beq	.L4314
	sub	ip, ip, #5
	mov	r3, #1
	clz	ip, ip
	strb	r3, [r0, #531]
	strb	r3, [r0, #530]
	mov	ip, ip, lsr #5
	strb	ip, [r0, #529]
	b	.L4314
.L4478:
	strb	lr, [r0, #531]
	ldr	r3, [r2, #712]
	str	r3, [r0, #2160]
	ldrb	r3, [r2, #708]	@ zero_extendqisi2
	strb	r3, [r0, #529]
	ldrb	r3, [r2, #709]	@ zero_extendqisi2
	strb	r3, [r0, #530]
	strb	r1, [r2, #704]
	b	.L4314
.L4485:
	movw	r3, #8500
	movt	r3, 5
	mla	r3, r3, r2, r4
	add	r3, r3, #12992
	add	r3, r3, #16
	ldr	r3, [r3, #4]
	b	.L4454
.L4318:
	ldr	r3, [r3, #2388]
	b	.L4454
.L4487:
	.align	2
.L4486:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC459
	.word	.LC461
	.word	.LC462
	.word	g_event_report
	.word	.LC467
	.word	.LC465
	.word	.LC469
	.word	.LC470
	.word	.LC463
	.word	.LC472
	.word	.LC471
	.word	.LC473
	.word	.LC474
	.word	.LC475
	.word	.LC476
	.word	.LC477
	.word	.LANCHOR1
	.word	.LC478
	.word	.LC479
	.word	.LC460
	.word	.LC464
	.word	.LC334
	.word	.LC466
	.word	.LC468
	UNWIND(.fnend)
	.size	MVC_DecOneNal, .-MVC_DecOneNal
	.align	2
	.global	MVC_DEC_DecodePacket
	.type	MVC_DEC_DecodePacket, %function
MVC_DEC_DecodePacket:
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
	mov	r4, r0
	mov	r0, #0
	str	r0, [fp, #-40]
	str	r0, [fp, #-44]
	str	r0, [fp, #-48]
	beq	.L4542
	ldr	r2, [r4, #224]
	ldrb	ip, [r4, #5]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	cmp	ip, #1
	mov	r3, r3, asl #16
	and	r3, r3, #196608
	str	r3, [r4, #108]
	ldr	r3, [r2]
	str	r3, [r4, #112]
	ldr	r3, [r2, #4]
	strb	r0, [r4, #10]
	str	r3, [r4, #116]
	beq	.L4491
	ldr	r3, [r2, #868]
	cmp	r3, #1
	addne	r5, r4, #11141120
	addne	r5, r5, #12288
	beq	.L4543
.L4492:
	mov	r0, r4
	bl	MVC_ReceivePacket
	ldr	r3, [r4, #232]
	str	r3, [r5, #428]
.L4494:
	cmp	r0, #0
	mov	r3, #0
	strb	r3, [r4, #5]
	beq	.L4495
.L4514:
	mov	r0, #0
.L4537:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4543:
	ldr	r3, [r2, #908]
	add	r5, r4, #11141120
	add	r5, r5, #12288
	cmp	r3, #1
	bne	.L4492
	ldr	r3, [r5, #424]
	cmp	r3, #1
	bne	.L4492
	ldr	r3, [r5, #428]
	str	r3, [r4, #232]
	str	r0, [r5, #424]
	strb	r0, [r4, #5]
	b	.L4493
.L4495:
	ldr	r3, [r4, #232]
.L4493:
	mov	r2, #0
	str	r2, [r3, #64]
	ldr	r3, [r4, #232]
	add	r6, r4, #548
	mov	r0, r6
	ldr	r2, [r3, #12]
	ldr	r1, [r3, #8]
	bl	BsInit
	mov	r1, #32
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r4, #232]
	mvn	r2, #0
	mov	r5, r0
	and	r0, r0, #31
	strb	r0, [r3, #2]
	ubfx	r1, r5, #5, #2
	ldr	r3, [r4, #232]
	strb	r1, [r3, #4]
	ldr	r3, [r4, #232]
	strb	r2, [r3, #5]
	ldr	r3, [r4, #232]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #20
	beq	.L4544
.L4540:
	and	r5, r5, #27
	mov	r3, #0
	cmp	r5, #1
	strb	r3, [r4, #10]
	beq	.L4500
.L4501:
	mov	r0, r4
	bl	MVC_FindTrailZeros
	cmp	r0, #0
	bne	.L4545
.L4513:
	ldr	r3, [r4, #232]
	mov	r5, #0
	mov	r0, r6
	str	r5, [r3, #64]
	ldr	r3, [r4, #232]
	ldr	r1, [r3, #8]
	ldr	r2, [r3, #12]
	bl	BsInit
	mov	r1, r5
	mov	r0, r4
	bl	MVC_DecOneNal
	cmn	r0, #2
	beq	.L4537
	cmp	r0, r5
	beq	.L4514
	ldr	r3, .L4548
	ldr	r6, [r3]
	cmp	r6, r5
	beq	.L4541
	ldr	r0, [r4, #120]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r6
.L4541:
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4491:
	ldr	r0, [r4, #232]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	b	.L4494
.L4544:
	mov	r1, #24
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r4, #232]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #5]
	ldr	r1, [r4, #232]
	ldrsb	r2, [r1, #5]
	cmp	r2, #0
	bne	.L4540
	ubfx	ip, r0, #22, #1
	add	r3, r4, #12288
	cmp	ip, #0
	mov	r5, #1
	strb	ip, [r3, #705]
	ubfx	lr, r0, #6, #10
	ubfx	ip, r0, #2, #1
	strb	r5, [r3, #704]
	strb	ip, [r3, #708]
	ubfx	r0, r0, #1, #1
	str	lr, [r3, #712]
	movne	ip, r5
	strb	r0, [r3, #709]
	moveq	ip, #5
	strb	ip, [r1, #2]
	strb	r2, [r4, #10]
.L4500:
	sub	r2, fp, #32
	sub	r1, fp, #36
	mov	r0, r4
	bl	MVC_InquireSliceProperty
	cmp	r0, #0
	bne	.L4502
	ldr	r3, [fp, #-36]
	ldr	r2, [r4, #128]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	cmp	r3, #0
	add	r3, r2, r3
	str	r3, [r4, #128]
	bne	.L4546
.L4503:
	ldr	r3, [fp, #-32]
	cmp	r3, #1
	bne	.L4501
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	cmp	r0, #0
	bne	.L4547
.L4510:
	ldr	r0, [r4, #120]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L4501
	sub	r3, fp, #40
	sub	r2, fp, #44
	sub	r1, fp, #48
	ldr	r0, [r4, #120]
	bl	VCTRL_GetChanImgNum
	b	.L4501
.L4502:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4512
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4512:
	ldr	r3, .L4548
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4541
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4537
.L4545:
	ldr	r3, .L4548+4
	mov	r0, #22
	ldr	r1, .L4548+8
	ldr	r3, [r3, #68]
	blx	r3
	b	.L4513
.L4546:
	add	r5, r4, #11075584
	add	r5, r5, #40960
	ldrb	r3, [r5, #521]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #132]
	addeq	r3, r3, #1
	addne	r3, r3, #2
	str	r3, [r4, #132]
	ldr	r3, [r4, #64]
	cmp	r3, #0
	beq	.L4503
	ldr	r3, [r4, #232]
	mov	ip, #0
	mov	r0, r6
	mov	r2, #12
	ldr	r1, .L4548+12
	str	ip, [r3, #64]
	bl	BsInit
	mov	r1, #1
	mov	r0, r4
	bl	MVC_DecOneNal
	ldrb	r3, [r5, #521]	@ zero_extendqisi2
	mvn	r0, #1
	cmp	r3, #1
	ldr	r3, [r4, #132]
	subeq	r3, r3, #1
	subne	r3, r3, #2
	str	r3, [r4, #132]
	mov	r3, #1
	strb	r3, [r4, #5]
	b	.L4537
.L4547:
	ldr	ip, .L4548+4
	mov	r3, #0
	movw	r2, #14029
	ldr	r1, .L4548+16
	mov	r0, #22
	ldr	r5, [ip, #68]
	blx	r5
	b	.L4510
.L4542:
	ldr	ip, .L4548+4
	mov	r0, r1
	movw	r3, #13912
	ldr	r2, .L4548+20
	ldr	r1, .L4548+24
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L4537
.L4549:
	.align	2
.L4548:
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC480
	.word	.LANCHOR1+432
	.word	.LC439
	.word	.LC13
	.word	.LC14
	UNWIND(.fnend)
	.size	MVC_DEC_DecodePacket, .-MVC_DEC_DecodePacket
	.align	2
	.global	MVC_DEC_VDMPostProc
	.type	MVC_DEC_VDMPostProc, %function
MVC_DEC_VDMPostProc:
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
	ldrb	r7, [r0]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r7, #0
	bne	.L4551
	add	r6, r0, #11141120
	add	r6, r6, #8192
	str	r1, [r6, #2164]
	bl	MVC_ClearAllSlice
	mov	r0, r4
	bl	MVC_StorePicInDpb
	subs	r5, r0, #0
	bne	.L4562
	mov	r3, #1
	mov	r0, r5
	strb	r3, [r4, #4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4551:
	add	r3, r0, #11141120
	add	r3, r3, #8192
	str	r1, [r3, #2164]
	bl	MVC_ClearAllSlice
	mov	r0, r4
	bl	MVC_StorePicInDpb
	subs	r2, r0, #0
	bne	.L4563
.L4554:
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r2, r0, #0
	bne	.L4564
.L4555:
	ldr	ip, [r4, #40]
	add	r3, r4, #11075584
	add	r3, r3, #40960
	mov	r1, #0
	movw	r2, #23352
	strb	r1, [r4, #4]
	mov	r0, r1
	movt	r2, 1
	str	ip, [r3, #2188]
	mov	r5, #2
	strb	r1, [r3, #2176]
	mov	r4, #7
	str	r1, [r3, #2208]
	mov	lr, #32
	str	r1, [r3, #2212]
	mov	ip, #3
	str	r2, [r3, #2192]
	mvn	r1, #0
	mov	r2, #262144
	strb	r5, [r3, #2177]
	strb	r4, [r3, #2179]
	strb	lr, [r3, #2178]
	str	ip, [r3, #2200]
	str	r1, [r3, #2204]
	str	r2, [r3, #2216]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4562:
	ldr	r3, [r6, #2112]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	ldr	r3, .L4565
	mov	r2, r5
	ldr	r1, .L4565+4
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mov	r0, r4
	mvn	r1, #0
	bl	MVC_ClearDPB
	str	r7, [r6, #2112]
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4564:
	ldr	r3, .L4565
	mov	r0, #1
	ldr	r1, .L4565+8
	ldr	r3, [r3, #68]
	blx	r3
	b	.L4555
.L4563:
	ldr	r3, .L4565
	mov	r0, #1
	ldr	r1, .L4565+12
	ldr	r3, [r3, #68]
	blx	r3
	b	.L4554
.L4566:
	.align	2
.L4565:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC481
	.word	.LC483
	.word	.LC482
	UNWIND(.fnend)
	.size	MVC_DEC_VDMPostProc, .-MVC_DEC_VDMPostProc
	.align	2
	.global	MVC_DEC_GetImageBuffer
	.type	MVC_DEC_GetImageBuffer, %function
MVC_DEC_GetImageBuffer:
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
	ldr	r7, [r0, #48]
	mov	r5, #0
	mov	r6, r0
	cmp	r7, r5
	str	r5, [fp, #-52]
	str	r5, [fp, #-48]
	beq	.L4583
	movw	r4, #47800
	movw	r9, #47240
	movt	r4, 169
	add	r8, r0, #11075584
	add	r4, r0, r4
	movt	r9, 169
	add	r8, r8, #45056
	add	r9, r0, r9
	mov	ip, r4
.L4575:
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4570
	cmp	ip, #0
	beq	.L4571
	ldr	lr, [r8, #2376]
	cmp	lr, #0
	beq	.L4571
	ldr	r2, [r8, #2184]
	rsb	r3, ip, r2
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L4570
	mov	r1, r9
	b	.L4572
.L4573:
	ldr	r2, [r1, #4]!
	rsb	r0, ip, r2
	cmp	r2, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L4570
.L4572:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L4573
.L4571:
	ldr	r0, [r6, #120]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L4583
	ldr	r0, [r6, #120]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	bne	.L4605
	add	r1, r6, #584
	ldr	r0, [r6, #120]
	bl	FSP_ClearNotInVoQueue
	b	.L4605
.L4570:
	add	r5, r5, #1
	add	ip, ip, #688
	cmp	r5, r7
	bne	.L4575
	ldr	r9, .L4609
	sub	r2, fp, #48
	sub	r1, fp, #52
	add	r0, r6, #584
	bl	GetQueueImgNum
	ldr	r1, .L4609+4
	ldr	r3, [r9, #68]
	mov	r0, #0
	blx	r3
	ldr	r3, [r9, #68]
	ldr	r1, .L4609+8
	mov	r0, #0
	blx	r3
	ldr	r3, [r6, #48]
	cmp	r3, #0
	beq	.L4607
	add	r7, r6, #11075584
	movw	r3, #47240
	add	r7, r7, #45056
	mov	r5, #0
	movt	r3, 169
	add	r3, r6, r3
	str	r3, [fp, #-56]
.L4576:
	cmp	r4, #0
	ldr	r8, [r9, #68]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	ldrb	r10, [r4, #5]	@ zero_extendqisi2
	beq	.L4587
	ldr	lr, [r7, #2376]
	cmp	lr, #0
	beq	.L4587
	ldr	r1, [r7, #2184]
	rsb	r2, r4, r1
	cmp	r1, #0
	clz	r2, r2
	mov	r2, r2, lsr #5
	moveq	r2, #0
	cmp	r2, #0
	bne	.L4589
	ldr	r0, [fp, #-56]
	b	.L4580
.L4581:
	ldr	r1, [r0, #4]!
	rsb	ip, r4, r1
	cmp	r1, #0
	clz	ip, ip
	mov	ip, ip, lsr #5
	moveq	ip, #0
	cmp	ip, #0
	bne	.L4589
.L4580:
	add	r2, r2, #1
	cmp	r2, lr
	bne	.L4581
.L4587:
	mov	r2, #1
.L4579:
	str	r2, [sp, #4]
	mov	r0, #0
	mov	r2, r5
	str	r10, [sp]
	ldr	r1, .L4609+12
	add	r5, r5, #1
	blx	r8
	ldr	r3, [r6, #48]
	add	r4, r4, #688
	cmp	r3, r5
	bhi	.L4576
.L4582:
	ldr	r3, [fp, #-48]
	mov	r0, #0
	ldr	r2, [fp, #-52]
	ldr	r1, .L4609+16
	ldr	r4, [r9, #68]
	blx	r4
	ldr	r3, [r6, #48]
	ldr	r0, [r7, #2380]
	ldr	r2, [fp, #-52]
	sub	r3, r3, #2
	ldr	r1, [fp, #-48]
	rsb	r3, r0, r3
	ldr	r0, .L4609
	add	r2, r2, r1
	cmp	r2, r3
	blt	.L4608
.L4605:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4583:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4589:
	mov	r2, #0
	b	.L4579
.L4608:
	ldr	r3, [r0, #68]
	mov	r0, #0
	ldr	r1, .L4609+20
	blx	r3
	mov	r0, r6
	mov	r1, #1
	bl	MVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4607:
	add	r7, r6, #11075584
	add	r7, r7, #45056
	b	.L4582
.L4610:
	.align	2
.L4609:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC484
	.word	.LC485
	.word	.LC487
	.word	.LC486
	.word	.LC488
	UNWIND(.fnend)
	.size	MVC_DEC_GetImageBuffer, .-MVC_DEC_GetImageBuffer
	.global	MvcTmpBuf
	.global	MVC_quant8_org
	.global	MVC_quant_org
	.global	MVC_quant8_inter_default
	.global	MVC_quant8_intra_default
	.global	MVC_quant_inter_default
	.global	MVC_quant_intra_default
	.global	MVC_g_ZZ_SCAN8
	.global	MVC_g_ZZ_SCAN
	.global	MVC_CalcZeroNum
	.global	MVC_g_AspecRatioIdc
	.global	MVC_g_NalTypeEOPIC
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	MVC_g_ZZ_SCAN, %object
	.size	MVC_g_ZZ_SCAN, 16
MVC_g_ZZ_SCAN:
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
	.type	MVC_g_ZZ_SCAN8, %object
	.size	MVC_g_ZZ_SCAN8, 64
MVC_g_ZZ_SCAN8:
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
	.type	__FUNCTION__.14499, %object
	.size	__FUNCTION__.14499, 18
__FUNCTION__.14499:
	.ascii	"MVC_WriteSliceMsg\000"
	.space	2
	.type	MVC_SarTable.14790, %object
	.size	MVC_SarTable.14790, 136
MVC_SarTable.14790:
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
	.type	__func__.15024, %object
	.size	__func__.15024, 11
__func__.15024:
	.ascii	"MVC_DecSEI\000"
	.space	1
	.type	__func__.13679, %object
	.size	__func__.13679, 17
__func__.13679:
	.ascii	"MVC_DirectOutput\000"
	.space	3
	.type	__func__.14259, %object
	.size	__func__.14259, 12
__func__.14259:
	.ascii	"MVC_InitDPB\000"
	.type	__FUNCTION__.13399, %object
	.size	__FUNCTION__.13399, 13
__FUNCTION__.13399:
	.ascii	"MVC_ClearDPB\000"
	.space	3
	.type	__func__.15135, %object
	.size	__func__.15135, 17
__func__.15135:
	.ascii	"MVC_FlushDecoder\000"
	.space	3
	.type	__FUNCTION__.13407, %object
	.size	__FUNCTION__.13407, 13
__FUNCTION__.13407:
	.ascii	"MVC_ClearAll\000"
	.space	3
	.type	__FUNCTION__.15262, %object
	.size	__FUNCTION__.15262, 13
__FUNCTION__.15262:
	.ascii	"MVC_DEC_Init\000"
	.space	3
	.type	__func__.13829, %object
	.size	__func__.13829, 18
__func__.13829:
	.ascii	"MVC_StorePicInDpb\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	MVC_quant_intra_default, %object
	.size	MVC_quant_intra_default, 16
MVC_quant_intra_default:
	.word	471076102
	.word	538711053
	.word	622861332
	.word	707076124
	.type	MVC_quant_inter_default, %object
	.size	MVC_quant_inter_default, 16
MVC_quant_inter_default:
	.word	403967498
	.word	454562830
	.word	505092116
	.word	572398360
	.type	MVC_quant8_intra_default, %object
	.size	MVC_quant8_intra_default, 64
MVC_quant8_intra_default:
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
	.type	MVC_quant8_inter_default, %object
	.size	MVC_quant8_inter_default, 256
MVC_quant8_inter_default:
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
	.type	MVC_quant_org, %object
	.size	MVC_quant_org, 16
MVC_quant_org:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	MVC_quant8_org, %object
	.size	MVC_quant8_org, 64
MVC_quant8_org:
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
	.type	MVC_g_NalTypeEOPIC, %object
	.size	MVC_g_NalTypeEOPIC, 12
MVC_g_NalTypeEOPIC:
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
	.type	MVC_CalcZeroNum, %object
	.size	MVC_CalcZeroNum, 256
MVC_CalcZeroNum:
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
	.type	MVC_g_AspecRatioIdc, %object
	.size	MVC_g_AspecRatioIdc, 112
MVC_g_AspecRatioIdc:
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
	ASCII(.ascii	"\012\012END of the bit buffer, copy the first packe" )
	ASCII(.ascii	"t!\012\012\000" )
	.space	2
.LC1:
	ASCII(.ascii	"0:phy:0x%x, 1:phy:0x%x; len0:%d len1:%d\012\000" )
	.space	3
.LC2:
	ASCII(.ascii	"0:phy:0x%x, len0:%d\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"%-50s%50d\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"MVC_FRAME %d, state=%d, is already output\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"plfs(fs=%p, eFoState=%d) is null, logic_fs_id = %d\012" )
	ASCII(.ascii	"\000" )
.LC6:
	ASCII(.ascii	"not used MVC_FRAME: (%d,%d)\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"MVC_FRAME skip: is_used=%d,skip=%d\012\000" )
.LC8:
	ASCII(.ascii	"topfield skip\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"bottom field skip\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC12:
	ASCII(.ascii	"stream MVC_FRAME packing type is %d! what can we do" )
	ASCII(.ascii	"?\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"firmware/common/syntax/mvc.c\000" )
	.space	3
.LC14:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(ref=%d,plfs=%" )
	ASCII(.ascii	"p, pdfs=%p)\012\000" )
.LC17:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"pMvcCtx->DPB.fs[%d]: frame_num=%d poc=%d is_referen" )
	ASCII(.ascii	"ce=%d\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"pMvcCtx->DPB.fs_ref[%d]: frame_num=%d poc=%d is_ref" )
	ASCII(.ascii	"erence=%d\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"pMvcCtx->DPB.fs_ref[%d]: MVC_FRAME.poc=%d \012\000" )
.LC21:
	ASCII(.ascii	"\012 VFMW ** release streambuff=%08x   bitstream_le" )
	ASCII(.ascii	"ngth=%d\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"clear curr slice.\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC25:
	ASCII(.ascii	"for P slice size of list equal 0(1st).\012\000" )
.LC26:
	ASCII(.ascii	"for P slice size of list equal 0(2nd).\012\000" )
.LC27:
	ASCII(.ascii	"for B slice size of two list all equal 0.\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"list[%d][%d]: frame_num=%d, poc=%d\012\000" )
.LC29:
	ASCII(.ascii	"init list error.\012\000" )
	.space	2
.LC30:
	ASCII(.ascii	"In one access unit,all non-base view should have th" )
	ASCII(.ascii	"e same subsps!\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"sps but mvc flag %d is wrong\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"save pic yuv :  structure = %d;  idc = %d\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"structure = %d pMvcCtx->CurrPic.pic_width_in_mb = %" )
	ASCII(.ascii	"d pMvcCtx->CurrPic.pic_height_in_mb = %d\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"logic MVC_FRAME id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"fuction return value is null,%s %d unknow error!!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC38:
	ASCII(.ascii	"SH: first_mb_in_slice\000" )
	.space	2
.LC39:
	ASCII(.ascii	"MVC_SliceCheck first_mb_in_slice >= MAX_MB_NUM_IN_P" )
	ASCII(.ascii	"IC error.\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"SH: slice_type\000" )
	.space	1
.LC41:
	ASCII(.ascii	"slice type = %d\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"slice type = %d, err\012\000" )
	.space	2
.LC43:
	ASCII(.ascii	"slice  pps id = %d\012\000" )
.LC44:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't deco" )
	ASCII(.ascii	"de\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"sps with this pic_parameter_set_id havn't decode\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC46:
	ASCII(.ascii	"subsps with this seq_parameter_set_id = %d havn't d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC47:
	ASCII(.ascii	"tmp slice  pps id = %d\012\000" )
.LC48:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: pps with this pic_parameter_s" )
	ASCII(.ascii	"et_id = %d havn't decode\012\000" )
	.space	3
.LC49:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: seq_parameter_set_id out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: sps with this pic_parameter_s" )
	ASCII(.ascii	"et_id = %d havn't decode\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"new pic flag = %d\012\000" )
	.space	1
.LC52:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l0\000" )
.LC53:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l0\000" )
	.space	2
.LC54:
	ASCII(.ascii	"reorder idc l0 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l0\000" )
	.space	1
.LC56:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC57:
	ASCII(.ascii	"SH: long_term_pic_idx_l0\000" )
	.space	3
.LC58:
	ASCII(.ascii	"SH: abs_diff_view_idx_minus1_l0\000" )
.LC59:
	ASCII(.ascii	"num of idc l0 exceed\012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l1\000" )
.LC61:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l1\000" )
	.space	2
.LC62:
	ASCII(.ascii	"reorder idc l1 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l1\000" )
	.space	1
.LC64:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l1 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC65:
	ASCII(.ascii	"SH: long_term_pic_idx_l1\000" )
	.space	3
.LC66:
	ASCII(.ascii	"SH: abs_diff_view_idx_minus1_l1\000" )
.LC67:
	ASCII(.ascii	"num of idc l1 exceed\012\000" )
	.space	2
.LC68:
	ASCII(.ascii	"SH: luma_log2_weight_denom\000" )
	.space	1
.LC69:
	ASCII(.ascii	"SH: chroma_log2_weight_denom\000" )
	.space	3
.LC70:
	ASCII(.ascii	"WP log2 exceed  and err flag = %d\012\000" )
	.space	1
.LC71:
	ASCII(.ascii	"SH: luma_weight_flag_l0\000" )
.LC72:
	ASCII(.ascii	"SH: luma_weight_l0\000" )
	.space	1
.LC73:
	ASCII(.ascii	"SH: luma_offset_l0\000" )
	.space	1
.LC74:
	ASCII(.ascii	"SH: chroma_weight_flag_l0\000" )
	.space	2
.LC75:
	ASCII(.ascii	"SH: chroma_weight_l0\000" )
	.space	3
.LC76:
	ASCII(.ascii	"SH: chroma_offset_l0\000" )
	.space	3
.LC77:
	ASCII(.ascii	"SH: luma_weight_flag_l1\000" )
.LC78:
	ASCII(.ascii	"SH: luma_weight_l1\000" )
	.space	1
.LC79:
	ASCII(.ascii	"SH: luma_offset_l1\000" )
	.space	1
.LC80:
	ASCII(.ascii	"SH: chroma_weight_flag_l1\000" )
	.space	2
.LC81:
	ASCII(.ascii	"SH: chroma_weight_l1\000" )
	.space	3
.LC82:
	ASCII(.ascii	"SH: chroma_offset_l1\000" )
	.space	3
.LC83:
	ASCII(.ascii	"overflow MVC_MAX_MMCO_LEN\012\000" )
	.space	1
.LC84:
	ASCII(.ascii	"SH: memory_management_control_operation\000" )
.LC85:
	ASCII(.ascii	"SH: difference_of_pic_nums_minus1\000" )
	.space	2
.LC86:
	ASCII(.ascii	"SH: long_term_pic_num\000" )
	.space	2
.LC87:
	ASCII(.ascii	"SH: long_term_frame_idx\000" )
.LC88:
	ASCII(.ascii	"SH: max_long_term_frame_idx_plus1\000" )
	.space	2
.LC89:
	ASCII(.ascii	"mmco exceed 6\012\000" )
	.space	1
.LC90:
	ASCII(.ascii	"SH: no_output_of_prior_pics_flag\000" )
	.space	3
.LC91:
	ASCII(.ascii	"SH: long_term_reference_flag\000" )
	.space	3
.LC92:
	ASCII(.ascii	"IDR and no_output_of_prior_pics_flag = %d\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"SH: adaptive_ref_pic_marking_mode_flag\000" )
	.space	1
.LC94:
	ASCII(.ascii	"adaptive_ref_pic_marking_mode_flag = %d\012\000" )
	.space	3
.LC95:
	ASCII(.ascii	"MMCO para would save dec err\012\000" )
	.space	2
.LC96:
	ASCII(.ascii	"mulitislice diff no_out_of_prior_pics_flag, used fi" )
	ASCII(.ascii	"rst.\012\000" )
	.space	3
.LC97:
	ASCII(.ascii	"mulitislice diff long_term_reference_flag, used fir" )
	ASCII(.ascii	"st.\012\000" )
.LC98:
	ASCII(.ascii	"mulitislice diff adaptive_ref_pic_marking_mode_flag" )
	ASCII(.ascii	", used first.\012\000" )
	.space	2
.LC99:
	ASCII(.ascii	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\012\000" )
	.space	1
.LC100:
	ASCII(.ascii	"SH: pic_parameter_set_id\000" )
	.space	3
.LC101:
	ASCII(.ascii	"pps id:%d in sliceheader err\012\000" )
	.space	2
.LC102:
	ASCII(.ascii	"PPS or SPS of this slice not valid\012\000" )
.LC103:
	ASCII(.ascii	"MVC_PPSSPSCheck failed, PPS or SPS of this slice no" )
	ASCII(.ascii	"t valid\012\000" )
.LC104:
	ASCII(.ascii	"SH: frame_num\000" )
	.space	2
.LC105:
	ASCII(.ascii	"IDR NAL but frame_num!=0.\012\000" )
	.space	1
.LC106:
	ASCII(.ascii	"SH: field_pic_flag\000" )
	.space	1
.LC107:
	ASCII(.ascii	"SH: bottom_field_flag\000" )
	.space	2
.LC108:
	ASCII(.ascii	"field first_mb_in_slice bigger than pic size\012\000" )
	.space	2
.LC109:
	ASCII(.ascii	"MVC_FRAME first_mb_in_slice bigger than pic size\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC110:
	ASCII(.ascii	"SH: idr_pic_id\000" )
	.space	1
.LC111:
	ASCII(.ascii	"idr_pic_id bigger than 65535\012\000" )
	.space	2
.LC112:
	ASCII(.ascii	"SH: pic_order_cnt_lsb\000" )
	.space	2
.LC113:
	ASCII(.ascii	"SH: delta_pic_order_cnt_bottom\000" )
	.space	1
.LC114:
	ASCII(.ascii	"SH: delta_pic_order_cnt[0]\000" )
	.space	1
.LC115:
	ASCII(.ascii	"SH: delta_pic_order_cnt[1]\000" )
	.space	1
.LC116:
	ASCII(.ascii	"SH: redundant_pic_cnt\000" )
	.space	2
.LC117:
	ASCII(.ascii	"redundant pic not support.\012\000" )
.LC118:
	ASCII(.ascii	"first_mb_in_slice in currslice small than prevslice" )
	ASCII(.ascii	" in same pic\012\000" )
	.space	3
.LC119:
	ASCII(.ascii	"SH: direct_spatial_mv_pred_flag\000" )
.LC120:
	ASCII(.ascii	"SH: num_ref_idx_override_flag\000" )
	.space	2
.LC121:
	ASCII(.ascii	"SH: num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC122:
	ASCII(.ascii	"SH: num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC123:
	ASCII(.ascii	"MVC_FRAME num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC124:
	ASCII(.ascii	"field num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC125:
	ASCII(.ascii	"reordering para dec err\012\000" )
	.space	3
.LC126:
	ASCII(.ascii	"apply_weights_flag=%d\012\000" )
	.space	1
.LC127:
	ASCII(.ascii	"wpt dec err\012\000" )
	.space	3
.LC128:
	ASCII(.ascii	"mark para dec err\012\000" )
	.space	1
.LC129:
	ASCII(.ascii	"SH: cabac_init_idc\000" )
	.space	1
.LC130:
	ASCII(.ascii	"cabac_init_idc bigger than 3\012\000" )
	.space	2
.LC131:
	ASCII(.ascii	"SH: slice_qp_delta\000" )
	.space	1
.LC132:
	ASCII(.ascii	"SH: disable_deblocking_filter_idc\000" )
	.space	2
.LC133:
	ASCII(.ascii	"disable_deblocking_filter_idc dec err\012\000" )
	.space	1
.LC134:
	ASCII(.ascii	"SH: slice_alpha_c0_offset_div2\000" )
	.space	1
.LC135:
	ASCII(.ascii	"slice_alpha_c0_offset_div2 dec err\012\000" )
.LC136:
	ASCII(.ascii	"SH: slice_beta_offset_div2\000" )
	.space	1
.LC137:
	ASCII(.ascii	"slice_beta_offset_div2 dec err\012\000" )
.LC138:
	ASCII(.ascii	"pMvcCtx->pCurrNal->nal_bitoffset = %d; code_len_byt" )
	ASCII(.ascii	"e = %d; bitstream_length = %d; pMvcCtx->pCurrNal->n" )
	ASCII(.ascii	"al_trail_zero_bit_num = %d\012\000" )
	.space	2
.LC139:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; byt" )
	ASCII(.ascii	"espos = %x\012\000" )
	.space	1
.LC140:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC141:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\012\000" )
.LC142:
	ASCII(.ascii	"   : delta_sl   \000" )
	.space	3
.LC143:
	ASCII(.ascii	"PPS: entropy_coding_mode_flag\000" )
	.space	2
.LC144:
	ASCII(.ascii	"PPS: pic_order_present_flag\000" )
.LC145:
	ASCII(.ascii	"PPS: num_slice_groups_minus1\000" )
	.space	3
.LC146:
	ASCII(.ascii	"MVC_BASELINE stream with FMO, not support.\012\000" )
.LC147:
	ASCII(.ascii	"PPS: num_ref_idx_l0_active_minus1\000" )
	.space	2
.LC148:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1 out of range.\012\000" )
.LC149:
	ASCII(.ascii	"PPS: num_ref_idx_l1_active_minus1\000" )
	.space	2
.LC150:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1 out of range.\012\000" )
.LC151:
	ASCII(.ascii	"PPS: weighted prediction flag\000" )
	.space	2
.LC152:
	ASCII(.ascii	"PPS: weighted_bipred_idc\000" )
	.space	3
.LC153:
	ASCII(.ascii	"weighted_bipred_idc out of range\012\000" )
	.space	2
.LC154:
	ASCII(.ascii	"PPS: pic_init_qp_minus26\000" )
	.space	3
.LC155:
	ASCII(.ascii	"PPS: pic_init_qs_minus26\000" )
	.space	3
.LC156:
	ASCII(.ascii	"PPS: chroma_qp_index_offset\000" )
.LC157:
	ASCII(.ascii	"PPS: deblocking_filter_control_present_flag\000" )
.LC158:
	ASCII(.ascii	"PPS: constrained_intra_pred_flag\000" )
	.space	3
.LC159:
	ASCII(.ascii	"PPS: redundant_pic_cnt_present_flag\000" )
.LC160:
	ASCII(.ascii	"redundant pic not support when find redundant slice" )
	ASCII(.ascii	" later, exit\012\000" )
	.space	3
.LC161:
	ASCII(.ascii	"PPS: transform_8x8_mode_flag\000" )
	.space	3
.LC162:
	ASCII(.ascii	"PPS: pic_scaling_matrix_present_flag\000" )
	.space	3
.LC163:
	ASCII(.ascii	"PPS: second_chroma_qp_index_offset\000" )
	.space	1
.LC164:
	ASCII(.ascii	"SPS: seq_scaling_list_present_flag\000" )
	.space	1
.LC165:
	ASCII(.ascii	"PPS: pic_scaling_list_present_flag\000" )
	.space	1
.LC166:
	ASCII(.ascii	"second_chroma_qp_index_offset out of range.\012\000" )
	.space	3
.LC167:
	ASCII(.ascii	"PPS: pic_parameter_set_id\000" )
	.space	2
.LC168:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range.\012\000" )
.LC169:
	ASCII(.ascii	"PPS: seq_parameter_set_id\000" )
	.space	2
.LC170:
	ASCII(.ascii	"seq_parameter_set_id out of range.\012\000" )
.LC171:
	ASCII(.ascii	"PPS decode error line: %d.\012\000" )
.LC172:
	ASCII(.ascii	"VUI: aspect_ratio_info_present_flag\000" )
.LC173:
	ASCII(.ascii	"VUI: aspect_ratio_idc\000" )
	.space	2
.LC174:
	ASCII(.ascii	"VUI: sar_width\000" )
	.space	1
.LC175:
	ASCII(.ascii	"VUI: sar_height\000" )
.LC176:
	ASCII(.ascii	"VUI: overscan_info_present_flag\000" )
.LC177:
	ASCII(.ascii	"VUI: overscan_appropriate_flag\000" )
	.space	1
.LC178:
	ASCII(.ascii	"VUI: video_signal_type_present_flag\000" )
.LC179:
	ASCII(.ascii	"VUI: video_format\000" )
	.space	2
.LC180:
	ASCII(.ascii	"VUI: video_full_range_flag\000" )
	.space	1
.LC181:
	ASCII(.ascii	"VUI: color_description_present_flag\000" )
.LC182:
	ASCII(.ascii	"VUI: colour_primaries\000" )
	.space	2
.LC183:
	ASCII(.ascii	"VUI: transfer_characteristics\000" )
	.space	2
.LC184:
	ASCII(.ascii	"VUI: matrix_coefficients\000" )
	.space	3
.LC185:
	ASCII(.ascii	"VUI: chroma_loc_info_present_flag\000" )
	.space	2
.LC186:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_top_field\000" )
	.space	2
.LC187:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_bottom_field\000" )
	.space	3
.LC188:
	ASCII(.ascii	"VUI: timing_info_present_flag\000" )
	.space	2
.LC189:
	ASCII(.ascii	"VUI: num_units_in_tick\000" )
	.space	1
.LC190:
	ASCII(.ascii	"VUI: time_scale\000" )
.LC191:
	ASCII(.ascii	"VUI: fixed_frame_rate_flag\000" )
	.space	1
.LC192:
	ASCII(.ascii	"VUI: nal_hrd_parameters_present_flag\000" )
	.space	3
.LC193:
	ASCII(.ascii	"VUI: cpb_cnt_minus1\000" )
.LC194:
	ASCII(.ascii	"VUI: bit_rate_scale\000" )
.LC195:
	ASCII(.ascii	"VUI: cpb_size_scale\000" )
.LC196:
	ASCII(.ascii	"hrd->cpb_cnt_minus1 out of range\012\000" )
	.space	2
.LC197:
	ASCII(.ascii	"VUI: bit_rate_value_minus1\000" )
	.space	1
.LC198:
	ASCII(.ascii	"VUI: cpb_size_value_minus1\000" )
	.space	1
.LC199:
	ASCII(.ascii	"VUI: cbr_flag\000" )
	.space	2
.LC200:
	ASCII(.ascii	"VUI: initial_cpb_removal_delay_length_minus1\000" )
	.space	3
.LC201:
	ASCII(.ascii	"VUI: cpb_removal_delay_length_minus1\000" )
	.space	3
.LC202:
	ASCII(.ascii	"VUI: dpb_output_delay_length_minus1\000" )
.LC203:
	ASCII(.ascii	"VUI: time_offset_length\000" )
.LC204:
	ASCII(.ascii	"VUI: vcl_hrd_parameters_present_flag\000" )
	.space	3
.LC205:
	ASCII(.ascii	"VUI: low_delay_hrd_flag\000" )
.LC206:
	ASCII(.ascii	"VUI: pic_struct_present_flag\000" )
	.space	3
.LC207:
	ASCII(.ascii	"VUI: bitstream_restriction_flag\000" )
.LC208:
	ASCII(.ascii	"VUI: motion_vectors_over_pic_boundaries_flag\000" )
	.space	3
.LC209:
	ASCII(.ascii	"VUI: max_bytes_per_pic_denom\000" )
	.space	3
.LC210:
	ASCII(.ascii	"VUI: max_bits_per_mb_denom\000" )
	.space	1
.LC211:
	ASCII(.ascii	"VUI: log2_max_mv_length_horizontal\000" )
	.space	1
.LC212:
	ASCII(.ascii	"VUI: log2_max_mv_length_vertical\000" )
	.space	3
.LC213:
	ASCII(.ascii	"VUI: num_reorder_frames\000" )
.LC214:
	ASCII(.ascii	"VUI: max_dec_frame_buffering\000" )
	.space	3
.LC215:
	ASCII(.ascii	"dar=%d\012\000" )
.LC216:
	ASCII(.ascii	"SPS: chroma_format_idc\000" )
	.space	1
.LC217:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range.\012\000" )
	.space	1
.LC218:
	ASCII(.ascii	"SPS: bit_depth_luma_minus8\000" )
	.space	1
.LC219:
	ASCII(.ascii	"bit_depth_luma_minus8 not equal 0.\012\000" )
.LC220:
	ASCII(.ascii	"SPS: bit_depth_chroma_minus8\000" )
	.space	3
.LC221:
	ASCII(.ascii	"bit_depth_chroma_minus8 not equal 0.\012\000" )
	.space	2
.LC222:
	ASCII(.ascii	"SPS: qpprime_y_zero_trans_bypass_flag\000" )
	.space	2
.LC223:
	ASCII(.ascii	"qpprime_y_zero_trans_bypass_flag not equal 0.\012\000" )
	.space	1
.LC224:
	ASCII(.ascii	"SPS: seq_scaling_matrix_present_flag\000" )
	.space	3
.LC225:
	ASCII(.ascii	"SPS: log2_max_frame_num_minus4\000" )
	.space	1
.LC226:
	ASCII(.ascii	"pSPS->log2_max_frame_num_minus4 out of range.\012\000" )
	.space	1
.LC227:
	ASCII(.ascii	"SPS: pic_order_cnt_type\000" )
.LC228:
	ASCII(.ascii	"pSPS->pic_order_cnt_type out of range.\012\000" )
.LC229:
	ASCII(.ascii	"SPS: log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	1
.LC230:
	ASCII(.ascii	"SPS: num_ref_frames\000" )
.LC231:
	ASCII(.ascii	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of rang" )
	ASCII(.ascii	"e.\012\000" )
	.space	1
.LC232:
	ASCII(.ascii	"SPS: delta_pic_order_always_zero_flag\000" )
	.space	2
.LC233:
	ASCII(.ascii	"SPS: offset_for_non_ref_pic\000" )
.LC234:
	ASCII(.ascii	"SPS: offset_for_top_to_bottom_field\000" )
.LC235:
	ASCII(.ascii	"SPS: num_ref_frames_in_pic_order_cnt_cycle\000" )
	.space	1
.LC236:
	ASCII(.ascii	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of " )
	ASCII(.ascii	"range.\012\000" )
	.space	1
.LC237:
	ASCII(.ascii	"SPS: offset_for_ref_frame[i]\000" )
	.space	3
.LC238:
	ASCII(.ascii	"SPS: gaps_in_frame_num_value_allowed_flag\000" )
	.space	2
.LC239:
	ASCII(.ascii	"SPS: pic_width_in_mbs_minus1\000" )
	.space	3
.LC240:
	ASCII(.ascii	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC241:
	ASCII(.ascii	"SPS: pic_height_in_map_units_minus1\000" )
.LC242:
	ASCII(.ascii	"SPS: frame_mbs_only_flag\000" )
	.space	3
.LC243:
	ASCII(.ascii	"pSPS->pic_height_in_map_units_minus1 out of range.\012" )
	ASCII(.ascii	"\000" )
.LC244:
	ASCII(.ascii	"pic size too large.\012\000" )
	.space	3
.LC245:
	ASCII(.ascii	"level_idc %d not support.\012\000" )
	.space	1
.LC246:
	ASCII(.ascii	"dpb size according level : %d\012\000" )
	.space	1
.LC247:
	ASCII(.ascii	"pSPS->num_ref_frames(%d) > DPB size(%d), try to sel" )
	ASCII(.ascii	"ect the reasonable one.\012\000" )
.LC248:
	ASCII(.ascii	"SPS: direct_8x8_inference_flag\000" )
	.space	1
.LC249:
	ASCII(.ascii	"SPS: frame_cropping_flag\000" )
	.space	3
.LC250:
	ASCII(.ascii	"SPS: frame_cropping_rect_left_offset\000" )
	.space	3
.LC251:
	ASCII(.ascii	"SPS: frame_cropping_rect_right_offset\000" )
	.space	2
.LC252:
	ASCII(.ascii	"SPS: frame_cropping_rect_top_offset\000" )
.LC253:
	ASCII(.ascii	"SPS: frame_cropping_rect_bottom_offset\000" )
	.space	1
.LC254:
	ASCII(.ascii	"SPS: vui_parameters_present_flag\000" )
	.space	3
.LC255:
	ASCII(.ascii	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\012\000" )
	.space	2
.LC256:
	ASCII(.ascii	"SPS: mb_adaptive_frame_field_flag\000" )
	.space	2
.LC257:
	ASCII(.ascii	"SPS: profile_idc\000" )
	.space	3
.LC258:
	ASCII(.ascii	"SPS: constrained_set0_flag\000" )
	.space	1
.LC259:
	ASCII(.ascii	"SPS: constrained_set1_flag\000" )
	.space	1
.LC260:
	ASCII(.ascii	"SPS: constrained_set2_flag\000" )
	.space	1
.LC261:
	ASCII(.ascii	"SPS: constrained_set3_flag\000" )
	.space	1
.LC262:
	ASCII(.ascii	"SPS: constrained_set4_flag\000" )
	.space	1
.LC263:
	ASCII(.ascii	"SPS: constrained_set5_flag\000" )
	.space	1
.LC264:
	ASCII(.ascii	"SPS: reserved_zero_2bits\000" )
	.space	3
.LC265:
	ASCII(.ascii	"SPS: level_idc\000" )
	.space	1
.LC266:
	ASCII(.ascii	"SPS: seq_parameter_set_id\000" )
	.space	2
.LC267:
	ASCII(.ascii	"MVC_BASELINE stream, try to decode, exit when FMO o" )
	ASCII(.ascii	"ccurred.\012\000" )
	.space	3
.LC268:
	ASCII(.ascii	"MVC_EXTENDED stream, try to decode, exit when datap" )
	ASCII(.ascii	"artition occurred.\012\000" )
	.space	1
.LC269:
	ASCII(.ascii	"others High profile stream, try to decode, exit whe" )
	ASCII(.ascii	"n high profile not support occurred.\012\000" )
	.space	3
.LC270:
	ASCII(.ascii	"profile_idc = %5d error, try to decode as main prof" )
	ASCII(.ascii	"ile.\012\000" )
	.space	3
.LC271:
	ASCII(.ascii	"level_idc = %5d error, try to decode as level_idc %" )
	ASCII(.ascii	"d.\012\000" )
	.space	1
.LC272:
	ASCII(.ascii	"Line %d: SPS[%d] decode error.\012\000" )
.LC273:
	ASCII(.ascii	"SUBSPS: num_views_minus1\000" )
	.space	3
.LC274:
	ASCII(.ascii	"pSubsps->num_views_minus1(%d) out of range.\012\000" )
	.space	3
.LC275:
	ASCII(.ascii	"SUBSPS: view_id[]\000" )
	.space	2
.LC276:
	ASCII(.ascii	"SUBSPS: num_anchor_refs_l0[]\000" )
	.space	3
.LC277:
	ASCII(.ascii	"SUBSPS: num_anchor_refs_l1[]\000" )
	.space	3
.LC278:
	ASCII(.ascii	"pSubsps->num_anchor_refs_l0(%d) out of range.\012\000" )
	.space	1
.LC279:
	ASCII(.ascii	"SUBSPS: anchor_ref_l0[][]\000" )
	.space	2
.LC280:
	ASCII(.ascii	"pSubsps->num_anchor_refs_l1(%d) out of range.\012\000" )
	.space	1
.LC281:
	ASCII(.ascii	"SUBSPS: anchor_ref_l1[][]\000" )
	.space	2
.LC282:
	ASCII(.ascii	"SUBSPS: num_level_values_signalled_minus1\000" )
	.space	2
.LC283:
	ASCII(.ascii	"SUBSPS: num_non_anchor_refs_l0[]\000" )
	.space	3
.LC284:
	ASCII(.ascii	"SUBSPS: num_non_anchor_refs_l1[]\000" )
	.space	3
.LC285:
	ASCII(.ascii	"pSubsps->num_non_anchor_refs_l0(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC286:
	ASCII(.ascii	"SUBSPS: non_anchor_ref_l0[][]\000" )
	.space	2
.LC287:
	ASCII(.ascii	"pSubsps->num_non_anchor_refs_l1(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC288:
	ASCII(.ascii	"SUBSPS: non_anchor_ref_l1[][]\000" )
	.space	2
.LC289:
	ASCII(.ascii	"num_level(%d) out of range.\012\000" )
	.space	3
.LC290:
	ASCII(.ascii	"SUBSPS: level_idc[]\000" )
.LC291:
	ASCII(.ascii	"SUBSPS: num_applicable_ops_minus1\000" )
	.space	2
.LC292:
	ASCII(.ascii	"num_ops(%d) out of range.\012\000" )
	.space	1
.LC293:
	ASCII(.ascii	"SUBSPS: applicable_op_temporal_id[][]\000" )
	.space	2
.LC294:
	ASCII(.ascii	"SUBSPS: applicable_op_num_target_views_minus1[][]\000" )
	.space	2
.LC295:
	ASCII(.ascii	"SUBSPS: applicable_op_num_views_minus1\000" )
	.space	1
.LC296:
	ASCII(.ascii	"applicable_op_num_target_views(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC297:
	ASCII(.ascii	"SUBSPS: applicable_op_target_view_id[][][]\000" )
	.space	1
.LC298:
	ASCII(.ascii	"pSubsps->applicable_op_num_views_minus1(%d) out of " )
	ASCII(.ascii	"range.\012\000" )
	.space	1
.LC299:
	ASCII(.ascii	"MVC VUI: vui_mvc_num_ops_minus1\000" )
.LC300:
	ASCII(.ascii	"num_ops out of range\012\000" )
	.space	2
.LC301:
	ASCII(.ascii	"MVC VUI: vui_mvc_temporal_id[]\000" )
	.space	1
.LC302:
	ASCII(.ascii	"SUBSPS VUI: vui_mvc_num_target_output_views_minus1[" )
	ASCII(.ascii	"]\000" )
	.space	3
.LC303:
	ASCII(.ascii	"MVC VUI: vui_mvc_timing_info_present_flag\000" )
	.space	2
.LC304:
	ASCII(.ascii	"MVC VUI: vui_mvc_view_id[][]\000" )
	.space	3
.LC305:
	ASCII(.ascii	"MVC VUI: vui_mvc_num_units_in_tick\000" )
	.space	1
.LC306:
	ASCII(.ascii	"MVC VUI: vui_mvc_time_scale[]\000" )
	.space	2
.LC307:
	ASCII(.ascii	"MVC VUI: vui_mvc_fixed_frame_rate_flag\000" )
	.space	1
.LC308:
	ASCII(.ascii	"MVC VUI: vui_mvc_nal_hrd_parameters_present_flag[]\000" )
	.space	1
.LC309:
	ASCII(.ascii	"MVC VUI: cpb_cnt_minus1\000" )
.LC310:
	ASCII(.ascii	"MVC VUI: bit_rate_scale\000" )
.LC311:
	ASCII(.ascii	"MVC VUI: cpb_size_scale\000" )
.LC312:
	ASCII(.ascii	"MVC VUI: bit_rate_value_minus1\000" )
	.space	1
.LC313:
	ASCII(.ascii	"MVC VUI: cpb_size_value_minus1\000" )
	.space	1
.LC314:
	ASCII(.ascii	"MVC VUI: cbr_flag\000" )
	.space	2
.LC315:
	ASCII(.ascii	"MVC VUI: initial_cpb_removal_delay_length_minus1\000" )
	.space	3
.LC316:
	ASCII(.ascii	"MVC VUI: cpb_removal_delay_length_minus1\000" )
	.space	3
.LC317:
	ASCII(.ascii	"MVC VUI: dpb_output_delay_length_minus1\000" )
.LC318:
	ASCII(.ascii	"MVC VUI: time_offset_length\000" )
.LC319:
	ASCII(.ascii	"MVC VUI: vui_mvc_vcl_hrd_parameters_present_flag[]\000" )
	.space	1
.LC320:
	ASCII(.ascii	"MVC VUI: vui_mvc_low_delay_hrd_flag[]\000" )
	.space	2
.LC321:
	ASCII(.ascii	"MVC VUI: vui_mvc_pic_struct_present_flag[]\000" )
	.space	1
.LC322:
	ASCII(.ascii	"SUBSPS: profile_idc\000" )
.LC323:
	ASCII(.ascii	"SUBSPS: constrained_set0_flag\000" )
	.space	2
.LC324:
	ASCII(.ascii	"SUBSPS: constrained_set1_flag\000" )
	.space	2
.LC325:
	ASCII(.ascii	"SUBSPS: constrained_set2_flag\000" )
	.space	2
.LC326:
	ASCII(.ascii	"SUBSPS: constrained_set3_flag\000" )
	.space	2
.LC327:
	ASCII(.ascii	"SUBSPS: constrained_set4_flag\000" )
	.space	2
.LC328:
	ASCII(.ascii	"SUBSPS: constrained_set5_flag\000" )
	.space	2
.LC329:
	ASCII(.ascii	"SUBSPS: reserved_zero_2bits\000" )
.LC330:
	ASCII(.ascii	"SUBSPS: level_idc\000" )
	.space	2
.LC331:
	ASCII(.ascii	"SUBSPS: seq_parameter_set_id\000" )
	.space	3
.LC332:
	ASCII(.ascii	"profile_idc = %5d error\012\000" )
	.space	3
.LC333:
	ASCII(.ascii	"level_idc = %5d error, try to decode as level_idc 4" )
	ASCII(.ascii	"1.\012\000" )
	.space	1
.LC334:
	ASCII(.ascii	"SUBSPS decode error.\012\000" )
	.space	2
.LC335:
	ASCII(.ascii	"SUBSPS: bit_equal_to_one\000" )
	.space	3
.LC336:
	ASCII(.ascii	"SUBSPS Mvc Ext decode error.\012\000" )
	.space	2
.LC337:
	ASCII(.ascii	"SUBSPS: mvc_vui_parameters_present_flag\000" )
.LC338:
	ASCII(.ascii	"SUBSPS Mvc Vui Ext decode error.\012\000" )
	.space	2
.LC339:
	ASCII(.ascii	"SEI: frame_packing_arrangement_id\000" )
	.space	2
.LC340:
	ASCII(.ascii	"SEI: frame_packing_arrangement_cancel_flag\000" )
	.space	1
.LC341:
	ASCII(.ascii	"SEI: frame_packing_arrangement_type\000" )
.LC342:
	ASCII(.ascii	"SEI: quincunx_sampling_flag\000" )
.LC343:
	ASCII(.ascii	"SEI: content_interpretation_type\000" )
	.space	3
.LC344:
	ASCII(.ascii	"SEI: spatial_flipping_flag\000" )
	.space	1
.LC345:
	ASCII(.ascii	"SEI: frame0_flipped_flag\000" )
	.space	3
.LC346:
	ASCII(.ascii	"SEI: field_views_flag\000" )
	.space	2
.LC347:
	ASCII(.ascii	"SEI: current_frame_is_frame0_flag\000" )
	.space	2
.LC348:
	ASCII(.ascii	"SEI: frame0_self_contained_flag\000" )
.LC349:
	ASCII(.ascii	"SEI: frame1_self_contained_flag\000" )
.LC350:
	ASCII(.ascii	"SEI: frame0_grid_position_x\000" )
.LC351:
	ASCII(.ascii	"SEI: frame0_grid_position_y\000" )
.LC352:
	ASCII(.ascii	"SEI: frame1_grid_position_x\000" )
.LC353:
	ASCII(.ascii	"SEI: frame1_grid_position_y\000" )
.LC354:
	ASCII(.ascii	"SEI: frame_packing_arrangement_reserved_byte\000" )
	.space	3
.LC355:
	ASCII(.ascii	"SEI: frame_packing_arrangement_repetition_period\000" )
	.space	3
.LC356:
	ASCII(.ascii	"SEI: frame_packing_arrangement_extension_flag\000" )
	.space	2
.LC357:
	ASCII(.ascii	"DecPicTimingSEI but SPS is invalid.\012\000" )
	.space	3
.LC358:
	ASCII(.ascii	"SEI: cpb_removal_delay\000" )
	.space	1
.LC359:
	ASCII(.ascii	"SEI: dpb_output_delay\000" )
	.space	2
.LC360:
	ASCII(.ascii	"pic_struct\000" )
	.space	1
.LC361:
	ASCII(.ascii	"SEI nal dec payload type err\012\000" )
	.space	2
.LC362:
	ASCII(.ascii	"SEI nal dec payloadSize err\012\000" )
	.space	3
.LC363:
	ASCII(.ascii	"MVC_SEI_BUFFERING_PERIOD,offset = %d,payload_size =" )
	ASCII(.ascii	" %d \012\000" )
	.space	3
.LC364:
	ASCII(.ascii	"MVC_PassBytes err [%s][%d]\012\000" )
.LC365:
	ASCII(.ascii	"MVC_SEI_PIC_TIMING,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC366:
	ASCII(.ascii	"MVC_SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d" )
	ASCII(.ascii	" \012\000" )
	.space	2
.LC367:
	ASCII(.ascii	"MVC_SEI_FILLER_PAYLOAD,offset = %d,payload_size = %" )
	ASCII(.ascii	"d \012\000" )
	.space	1
.LC368:
	ASCII(.ascii	"MVC_SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d" )
	ASCII(.ascii	", payload_size = %d \012\000" )
	.space	3
.LC369:
	ASCII(.ascii	"MVC_SEI_USER_DATA_UNREGISTERED, offset = %d, payloa" )
	ASCII(.ascii	"d_size = %d \012\000" )
	.space	3
.LC370:
	ASCII(.ascii	"SEI: itu_t_t35_country_code\000" )
.LC371:
	ASCII(.ascii	"SEI: itu_t_t35_country_code_extension_byte\000" )
	.space	1
.LC372:
	ASCII(.ascii	"SEI: itu_t_t35_provider_code\000" )
	.space	3
.LC373:
	ASCII(.ascii	"cann't dec usrdata\012\000" )
.LC374:
	ASCII(.ascii	"MVC_SEI_RECOVERY_POINT,offset = %d,payload_size = %" )
	ASCII(.ascii	"d \012\000" )
	.space	1
.LC375:
	ASCII(.ascii	"MVC_SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d," )
	ASCII(.ascii	"payload_size = %d \012\000" )
	.space	1
.LC376:
	ASCII(.ascii	"MVC_SEI_SPARE_PIC,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC377:
	ASCII(.ascii	"MVC_SEI_SCENE_INFO,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC378:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC379:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,p" )
	ASCII(.ascii	"ayload_size = %d \012\000" )
	.space	2
.LC380:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload" )
	ASCII(.ascii	"_size = %d \012\000" )
.LC381:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_FREEZE,offset = %d,payload_size " )
	ASCII(.ascii	"= %d \012\000" )
	.space	2
.LC382:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,paylo" )
	ASCII(.ascii	"ad_size = %d \012\000" )
	.space	2
.LC383:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_siz" )
	ASCII(.ascii	"e = %d \012\000" )
.LC384:
	ASCII(.ascii	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset" )
	ASCII(.ascii	" = %d,payload_size = %d \012\000" )
	.space	3
.LC385:
	ASCII(.ascii	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset =" )
	ASCII(.ascii	" %d,payload_size = %d \012\000" )
	.space	1
.LC386:
	ASCII(.ascii	"MVC_SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset =" )
	ASCII(.ascii	" %d,payload_size = %d \012\000" )
	.space	1
.LC387:
	ASCII(.ascii	"MVC_SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payl" )
	ASCII(.ascii	"oad_size = %d \012\000" )
	.space	1
.LC388:
	ASCII(.ascii	"MVC_SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset" )
	ASCII(.ascii	" = %d,payload_size = %d \012\000" )
	.space	3
.LC389:
	ASCII(.ascii	"MVC_SEI_STEREO_VIDEO_INFO,offset = %d,payload_size " )
	ASCII(.ascii	"= %d \012\000" )
	.space	2
.LC390:
	ASCII(.ascii	"too much usrdat, cann't dec SEI\012\000" )
	.space	3
.LC391:
	ASCII(.ascii	"\012 mvc the stream is error,len:%d\012\000" )
	.space	2
.LC392:
	ASCII(.ascii	"\012Slice nal or IDR nal = %d\012\000" )
.LC393:
	ASCII(.ascii	"sliceheader dec err\012\000" )
	.space	3
.LC394:
	ASCII(.ascii	"MVC_InquireSliceProperty mvc flag %d is wrong\012\000" )
	.space	1
.LC395:
	ASCII(.ascii	"MvcDec destroy\012\000" )
.LC396:
	ASCII(.ascii	"MVC recycle image\012\000" )
	.space	1
.LC397:
	ASCII(.ascii	"pH264Ctx is %#x, pFrameStore is %#x\012\000" )
	.space	3
.LC398:
	ASCII(.ascii	"line: %d, pstLogicFsImage is NULL\012\000" )
	.space	1
.LC399:
	ASCII(.ascii	"InsertVO err:%d, MVC_ClearAll\012\000" )
	.space	1
.LC400:
	ASCII(.ascii	"mvc.c line %d: MVC_FRAME para err(ret=%d), recycle " )
	ASCII(.ascii	"image self\012\000" )
	.space	1
.LC401:
	ASCII(.ascii	"[%s][%d] MVC_OutputFrmToVO return %d !\012\000" )
.LC402:
	ASCII(.ascii	"[%s][%d] MVC_OutputFrmToVO return %d\012\000" )
	.space	2
.LC403:
	ASCII(.ascii	"%s %d MVC_OK != MVC_FlushDPB!!\012\000" )
.LC404:
	ASCII(.ascii	"%s %d MVC_OK != MVC_InitDPB!!\012\000" )
	.space	1
.LC405:
	ASCII(.ascii	"----------------- MVC_IMODE -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC406:
	ASCII(.ascii	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\012\000" )
.LC407:
	ASCII(.ascii	"***** VDM start, TotalPicNum=%d, pMvcCtx->CurrPic.s" )
	ASCII(.ascii	"tructure=%d.\012\000" )
	.space	3
.LC408:
	ASCII(.ascii	"MVC_DecVDM fail [%s][%d]\012\000" )
	.space	2
.LC409:
	ASCII(.ascii	"\012 receive streambuff=0x%08x; phy_addr=0x%x; bits" )
	ASCII(.ascii	"tream_length=%d\012\000" )
	.space	3
.LC410:
	ASCII(.ascii	"nal_releaMVC_SE_ERR\012\000" )
	.space	3
.LC411:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC412:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC413:
	ASCII(.ascii	"clear all dec para\012\000" )
.LC414:
	ASCII(.ascii	"line %d, get APC error, ret %d\012\000" )
.LC415:
	ASCII(.ascii	"InserFrmInDPB: cur pic struct = %d!\012\000" )
	.space	3
.LC416:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC417:
	ASCII(.ascii	"FS_ALLOC_ERR, MVC_ClearAll\012\000" )
.LC418:
	ASCII(.ascii	"Can not new logic fs! MVC_ClearAll\012\000" )
.LC419:
	ASCII(.ascii	"%s %d NULL== pMvcCtx->SPS || NULL == pMvcCtx->PPS |" )
	ASCII(.ascii	"| NULL == pMvcCtx->DecSlicePara!!\012\000" )
	.space	2
.LC420:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC421:
	ASCII(.ascii	"CurrPic.state is 'MVC_EMPTY'\012\000" )
	.space	2
.LC422:
	ASCII(.ascii	"MVC_StorePicInDpb return(%d) from L%d\012\000" )
	.space	1
.LC423:
	ASCII(.ascii	"Is IDR, but init DPB failed!\012\000" )
	.space	2
.LC424:
	ASCII(.ascii	"Is IDR, but FlushDPB failed!\012\000" )
	.space	2
.LC425:
	ASCII(.ascii	"MVC_DirectOutput mode\012\000" )
	.space	1
.LC426:
	ASCII(.ascii	"line %d, REPORT_IFRAME_ERR\012\000" )
.LC427:
	ASCII(.ascii	"line %d, return %d\012\000" )
.LC428:
	ASCII(.ascii	"err(%d) > ref_thr(%d)\012\000" )
	.space	1
.LC429:
	ASCII(.ascii	"MVC_Marking return %d\012\000" )
	.space	1
.LC430:
	ASCII(.ascii	"line %d: pMvcCtx->DPB.size = %d, ref %d, ltref %d\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC431:
	ASCII(.ascii	"line %d, MVC_GetMinPOC failed\012\000" )
	.space	1
.LC432:
	ASCII(.ascii	"%s: pos(%d) = pre_pos, force return.\012\000" )
	.space	2
.LC433:
	ASCII(.ascii	"GAP found while DPB is MVC_EMPTY!\012\000" )
	.space	1
.LC434:
	ASCII(.ascii	"MVC_FRAME num gap try to fill it \012\000" )
	.space	1
.LC435:
	ASCII(.ascii	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC436:
	ASCII(.ascii	"cann't allocate MVC_FRAME store when gap find\012\000" )
	.space	1
.LC437:
	ASCII(.ascii	"allocate MVC_FRAME store when gap find\012\000" )
.LC438:
	ASCII(.ascii	"line %d: store gap pic err, ret=%d\012\000" )
.LC439:
	ASCII(.ascii	"line %d: flush dpb return %d\012\000" )
	.space	2
.LC440:
	ASCII(.ascii	"line %d: init dpb return %d\012\000" )
	.space	3
.LC441:
	ASCII(.ascii	"resolution error, the CAP_LEVEL_USER_DEFINE_WITH_OP" )
	ASCII(.ascii	"TION channel with s32ReRangeEn == 0 can't support s" )
	ASCII(.ascii	"uch bitstream.\012\000" )
	.space	2
.LC442:
	ASCII(.ascii	"s32MaxRefFrameNum < pMvcCtx->DPB.size, the CAP_LEVE" )
	ASCII(.ascii	"L_USER_DEFINE_WITH_OPTION channel can't support suc" )
	ASCII(.ascii	"h bitstream.\012\000" )
.LC443:
	ASCII(.ascii	"mem arrange err, MVC_ClearAll\012\000" )
	.space	1
.LC444:
	ASCII(.ascii	"line %d: MVC_FRAME gap(=%d) > dpb size(=%d)\012\000" )
	.space	3
.LC445:
	ASCII(.ascii	"MVC_FRAME num gap don't allowed but gap find\012\000" )
	.space	2
.LC446:
	ASCII(.ascii	"line %d: frame num(%d/%d) find gap in NON-I slice b" )
	ASCII(.ascii	"ut here gap is not allowed\012\000" )
	.space	1
.LC447:
	ASCII(.ascii	"line %d: dec gap failed\012\000" )
	.space	3
.LC448:
	ASCII(.ascii	"line %d: alloc framestore failed\012\000" )
	.space	2
.LC449:
	ASCII(.ascii	"dec_pts: %lld\012\000" )
	.space	1
.LC450:
	ASCII(.ascii	"dec_usertag: %lld\012\000" )
	.space	1
.LC451:
	ASCII(.ascii	"line %d: CurrPic.frame_store is NULL\012\000" )
	.space	2
.LC452:
	ASCII(.ascii	"get back frm\012\000" )
	.space	2
.LC453:
	ASCII(.ascii	"Start Reason: SliceParaNum, MaxBytesReceived = %d, " )
	ASCII(.ascii	"%d(thr=%d)\012\000" )
	.space	1
.LC454:
	ASCII(.ascii	"Too many slice or bitstream, err!\012\000" )
	.space	1
.LC455:
	ASCII(.ascii	"Start Reason: new_pic_flag\012\000" )
.LC456:
	ASCII(.ascii	"init pic err, find next recover point or next valid" )
	ASCII(.ascii	" sps, pps, or exit\012\000" )
	.space	1
.LC457:
	ASCII(.ascii	"MVC_DecList error, ret=%d\012\000" )
	.space	1
.LC458:
	ASCII(.ascii	"dec list err.\012\000" )
	.space	1
.LC459:
	ASCII(.ascii	"pMvcCtx->TotalNal = %d, type:%d\012\000" )
	.space	3
.LC460:
	ASCII(.ascii	"stop i want\012\000" )
	.space	3
.LC461:
	ASCII(.ascii	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC462:
	ASCII(.ascii	"*******TotalPicNum=%d********\012\000" )
	.space	1
.LC463:
	ASCII(.ascii	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\012\000" )
	.space	1
.LC464:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC465:
	ASCII(.ascii	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\012\000" )
	.space	1
.LC466:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC467:
	ASCII(.ascii	"***** NAL: SEI, nal_unit_type=%d\012\000" )
	.space	2
.LC468:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC469:
	ASCII(.ascii	"***** NAL: AUD, nal_unit_type=%d\012\000" )
	.space	2
.LC470:
	ASCII(.ascii	"***** NAL: EOSEQ, nal_unit_type=%d\012\000" )
.LC471:
	ASCII(.ascii	"***** NAL: FILL, nal_unit_type=%d\012\000" )
	.space	1
.LC472:
	ASCII(.ascii	"***** NAL: EOSTREAM, nal_unit_type=%d\012\000" )
	.space	1
.LC473:
	ASCII(.ascii	"***** NAL: SPSEXT, nal_unit_type=%d\012\000" )
	.space	3
.LC474:
	ASCII(.ascii	"***** NAL: PREFIX, nal_unit_type=%d\012\000" )
	.space	3
.LC475:
	ASCII(.ascii	"***** NAL: SUBSPS, nal_unit_type=%d\012\000" )
	.space	3
.LC476:
	ASCII(.ascii	"***** NAL: AUX, nal_unit_type=%d\012\000" )
	.space	2
.LC477:
	ASCII(.ascii	"***** NAL: EOPIC, nal_unit_type=%d\012\000" )
.LC478:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC479:
	ASCII(.ascii	"nal_header != 0x00000100 not support.\012\000" )
	.space	1
.LC480:
	ASCII(.ascii	"MVC_FindTrailZeros ERR\012\000" )
.LC481:
	ASCII(.ascii	"store pic err, ret = %d\012\000" )
	.space	3
.LC482:
	ASCII(.ascii	"MVC_IMODE nal store pic err, ret = %d\012\000" )
	.space	1
.LC483:
	ASCII(.ascii	"MVC_IMODE nal flush dpb err, ret = %d\012\000" )
	.space	1
.LC484:
	ASCII(.ascii	"cann't find FrameStore\012\000" )
.LC485:
	ASCII(.ascii	"========== MVC FrameStore state(is_used, is_in_dpb," )
	ASCII(.ascii	" MVC_IsOutDPB) ========\012\000" )
.LC486:
	ASCII(.ascii	"ReadImgNum = %d, NewImgNum = %d\012\000" )
	.space	3
.LC487:
	ASCII(.ascii	"%02d: %d %d %d\012\000" )
.LC488:
	ASCII(.ascii	"FrameStore leak, MVC_ClearAll\012\000" )
	.bss
	.align	2
.LANCHOR2 = . + 0
.LANCHOR3 = . + 8184
	.type	pps_tmp.14710, %object
	.size	pps_tmp.14710, 2240
pps_tmp.14710:
	.space	2240
	.type	sps_tmp.14846, %object
	.size	sps_tmp.14846, 3992
sps_tmp.14846:
	.space	3992
	.type	MvcTmpBuf, %object
	.size	MvcTmpBuf, 68
MvcTmpBuf:
	.space	68
	.type	cnt.13665, %object
	.size	cnt.13665, 4
cnt.13665:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
