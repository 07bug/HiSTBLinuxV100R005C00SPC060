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
	.type	MVC_SetFrmRepeatCount.part.2, %function
MVC_SetFrmRepeatCount.part.2:
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
	ldr	r2, [ip, #2920]
	mov	r3, r3, lsr #1
	add	r2, r2, lr, lsr #1
	add	ip, r2, #1
	cmp	r3, ip
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
	ldrhi	r3, [r0, #136]
	ldrls	r3, [r0, #136]
	addhi	r3, r3, #4
	addls	r3, r3, #2
	str	r3, [r0, #136]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MVC_SetFrmRepeatCount.part.2, .-MVC_SetFrmRepeatCount.part.2
	.align	2
	.type	MVC_CombinePacket.part.14, %function
MVC_CombinePacket.part.14:
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
	ldr	r1, .L33
	mov	r4, r0
	mov	r0, #7
	bl	dprint_vfmw
	ldr	ip, [r4, #232]
	ldr	r1, .L33+4
	mov	r0, #7
	mov	r5, #0
	ldr	lr, [ip, #40]
	ldr	r3, [ip, #44]
	ldr	r2, [ip, #16]
	str	lr, [sp, #4]
	ldr	ip, [ip, #12]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #232]
	ldr	ip, .L33+8
	ldr	r2, [r3, #12]
	ldr	r0, [r3, #36]
	ldr	r1, [r3, #8]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #232]
	mov	ip, #1
	ldr	r1, .L33+12
	mov	r0, #7
	ldr	r2, [r3, #60]
	ldr	r6, [r3, #32]
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
	ldr	r3, [r2, #12]
	ldr	r2, [r2, #16]
	bl	dprint_vfmw
	mov	r1, r6
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #232]
	str	r5, [r3, #36]
	ldr	r3, [r4, #232]
	str	r5, [r3, #52]
	ldr	r3, [r4, #232]
	str	r5, [r3, #40]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L34:
	.align	2
.L33:
	.word	.LC0
	.word	.LC1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	UNWIND(.fnend)
	.size	MVC_CombinePacket.part.14, .-MVC_CombinePacket.part.14
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
	mov	r3, r5
	ldr	r1, .L41
	mov	r0, #21
	ldr	ip, [lr, #64]
	add	r4, ip, r8
	str	r4, [lr, #64]
	bl	dprint_vfmw
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
	eor	r3, r4, r3, lsr #1
	add	r4, r3, r2
	bl	BsSkip
.L45:
	ldr	lr, [r6, #232]
	mov	r2, r7
	mov	r3, r4
	ldr	r1, .L48
	mov	r0, #21
	ldr	ip, [lr, #64]
	add	r5, ip, r5
	str	r5, [lr, #64]
	bl	dprint_vfmw
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
	mov	r2, r7
	ldr	r1, .L51
	ldr	ip, [lr, #64]
	add	ip, ip, r6
	str	ip, [lr, #64]
	mov	r4, r0
	mov	r3, r0
	mov	r0, #21
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L52:
	.align	2
.L51:
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
	mov	r2, r6
	ldr	r1, .L54
	ldr	ip, [lr, #64]
	add	ip, ip, #1
	str	ip, [lr, #64]
	mov	r4, r0
	mov	r3, r0
	mov	r0, #21
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L55:
	.align	2
.L54:
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
	add	r5, r0, #11075584
	add	r5, r5, #45056
	mov	r9, r3
	mov	r8, r2
	mvn	r3, #-2147483648
	mvn	r2, #0
	str	r2, [r9]
	str	r3, [r8]
	mov	r6, r0
	ldr	r3, [r5, #2920]
	mov	r7, r1
	ldr	r2, [r5, #2924]
	cmp	r2, r3
	strhi	r3, [r5, #2924]
	cmp	r3, #0
	beq	.L63
	movw	r10, #47780
	mvn	r3, #0
	movt	r10, 169
	str	r3, [fp, #-48]
	add	r10, r0, r10
	mov	r4, #0
	b	.L62
.L60:
	ldr	ip, [r8]
	ldr	r1, [r2, #32]
	cmp	ip, r1
	ble	.L59
	ldrb	ip, [r2, #5]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L59
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	sub	r0, r0, #1
	cmp	r0, #1
	bls	.L78
.L59:
	ldr	r2, [r5, #2920]
	add	r4, r4, #1
	cmp	r2, r4
	bls	.L63
.L62:
	ldr	r2, [r10, #4]!
	cmp	r2, #0
	beq	.L59
	ldrsb	r1, [r2, #6]
	ldr	r0, [r6, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L59
	cmn	r7, #1
	ldr	r2, [r10]
	bne	.L60
	ldrb	r1, [r2, #5]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L59
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	sub	r1, r1, #1
	cmp	r1, #1
	bhi	.L59
	ldr	r0, [r8]
	ldr	r1, [r2, #32]
	cmp	r0, r1
	ble	.L61
	str	r1, [r8]
	str	r4, [r9]
	add	r4, r4, #1
	ldr	r2, [r10]
	ldr	r3, [r2, #56]
	ldr	r2, [r5, #2920]
	cmp	r2, r4
	str	r3, [fp, #-48]
	bhi	.L62
.L63:
	ldr	r0, [r9]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L78:
	ldr	r2, [r2, #56]
	cmp	r7, r2
	streq	r1, [r8]
	streq	r4, [r9]
	b	.L59
.L61:
	bne	.L59
	ldr	r2, [r2, #56]
	ldr	r3, [fp, #-48]
	cmp	r2, r3
	strlt	r4, [r9]
	ldrlt	r2, [r10]
	ldrlt	r3, [r2, #56]
	strlt	r3, [fp, #-48]
	b	.L59
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
	beq	.L95
	tst	r3, #1
	bne	.L96
.L84:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L88
.L85:
	ldrb	r0, [r0, #785]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L88:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L96:
	ldrb	r2, [r0, #749]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L84
.L89:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L95:
	ldrb	r3, [r0, #713]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L89
	ldrb	r3, [r0, #749]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L85
	b	.L89
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
	beq	.L112
	tst	r3, #1
	bne	.L113
.L101:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L105
.L102:
	ldr	r0, [r0, #784]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #65536
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L105:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L113:
	ldr	r2, [r0, #748]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #65536
	bne	.L101
.L106:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L112:
	ldr	r3, [r0, #712]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L106
	ldr	r3, [r0, #748]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	bne	.L102
	b	.L106
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
	beq	.L129
	tst	r3, #1
	bne	.L130
.L118:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L122
.L119:
	ldr	r0, [r0, #784]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #256
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L122:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L130:
	ldr	r2, [r0, #748]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #256
	bne	.L118
.L123:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L129:
	ldr	r3, [r0, #712]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L123
	ldr	r3, [r0, #748]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	bne	.L119
	b	.L123
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
	ldr	r10, [r3, #2920]
	cmp	r10, #0
	beq	.L132
	movw	r8, #47780
	add	r9, r0, #11141120
	movt	r8, 169
	mov	r4, #0
	add	r9, r9, #16384
	add	r8, r0, r8
	mov	r6, r4
.L134:
	ldr	r5, [r8, #4]!
	add	r6, r6, #1
	cmp	r5, #0
	mov	r0, r5
	beq	.L133
	bl	MVC_LongTermRefFlg
	cmp	r0, #0
	beq	.L133
	ldr	r2, [r9, #120]
	ldr	r1, [r5, #56]
	cmp	r1, r2
	movweq	r2, #28362
	movteq	r2, 42
	addeq	r2, r4, r2
	addeq	r4, r4, #1
	streq	r5, [r7, r2, asl #2]
.L133:
	cmp	r6, r10
	bne	.L134
	ldr	r3, [fp, #-48]
	cmp	r4, r10
	str	r4, [r3, #2932]
	bcs	.L131
	movw	r0, #28361
	mov	r2, #0
	movt	r0, 42
	add	r0, r4, r0
	add	r0, r7, r0, lsl #2
.L137:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r10
	bne	.L137
.L131:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L132:
	ldr	r3, [fp, #-48]
	str	r10, [r3, #2932]
	b	.L131
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
	ldr	r10, [r3, #2920]
	cmp	r10, #0
	beq	.L148
	movw	r8, #47780
	add	r9, r0, #11141120
	movt	r8, 169
	mov	r4, #0
	add	r9, r9, #16384
	add	r8, r0, r8
	mov	r6, r4
.L150:
	ldr	r5, [r8, #4]!
	add	r6, r6, #1
	cmp	r5, #0
	mov	r0, r5
	beq	.L149
	bl	MVC_ShortTermRefFlg
	cmp	r0, #0
	beq	.L149
	ldr	r2, [r9, #120]
	ldr	r1, [r5, #56]
	cmp	r1, r2
	movweq	r2, #28346
	movteq	r2, 42
	addeq	r2, r4, r2
	addeq	r4, r4, #1
	streq	r5, [r7, r2, asl #2]
.L149:
	cmp	r6, r10
	bne	.L150
	ldr	r3, [fp, #-48]
	cmp	r4, r10
	str	r4, [r3, #2928]
	bcs	.L147
	movw	r0, #28345
	mov	r2, #0
	movt	r0, 42
	add	r0, r4, r0
	add	r0, r7, r0, lsl #2
.L153:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r10
	bne	.L153
.L147:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L148:
	ldr	r3, [fp, #-48]
	str	r10, [r3, #2928]
	b	.L147
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
	ldr	r3, [r0, #664]
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
	beq	.L167
	ldrb	r1, [r1, #3]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r3, #749]
	and	r1, r1, #2
	strb	ip, [r3, #750]
	strb	r1, [r3, #3]
.L167:
	tst	r2, #2
	beq	.L168
	ldrb	r1, [r3, #3]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r3, #785]
	and	r1, r1, #1
	strb	ip, [r3, #786]
	strb	r1, [r3, #3]
.L168:
	cmp	r2, #3
	ldrsb	r1, [r3, #6]
	moveq	r2, #0
	streqb	r2, [r3, #714]
	streqb	r2, [r3, #713]
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
	ldr	r4, [r3, #2932]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, fp, sp, pc}
	movw	ip, #47908
	add	r6, r0, #11141120
	movt	ip, 169
	add	r6, r6, #16384
	add	ip, r0, ip
	mov	r3, #0
	b	.L179
.L178:
	cmp	r3, r4
	beq	.L184
.L179:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r2, #28]
	cmp	lr, r1
	bne	.L178
	ldr	r5, [r2, #56]
	ldr	lr, [r6, #120]
	cmp	r5, lr
	bne	.L178
	mov	r1, r2
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L184:
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
	ldr	r6, [ip, #2932]
	cmp	r6, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	movw	r4, #47908
	add	r8, r0, #11141120
	movt	r4, 169
	add	r8, r8, #16384
	add	r4, r0, r4
	mov	ip, #0
	b	.L189
.L187:
	cmp	ip, r6
	beq	.L203
.L189:
	ldr	lr, [r4, #4]!
	add	ip, ip, #1
	ldr	r5, [lr, #28]
	cmp	r5, r3
	bne	.L187
	ldr	r7, [lr, #56]
	ldr	r5, [r8, #120]
	cmp	r7, r5
	bne	.L187
	cmp	r2, #1
	ldreqb	r5, [lr, #785]	@ zero_extendqisi2
	beq	.L202
	cmp	r2, #2
	bne	.L187
	ldrb	r5, [lr, #749]	@ zero_extendqisi2
.L202:
	clz	r5, r5
	mov	r5, r5, lsr #5
	cmp	lr, r1
	orrne	r5, r5, #1
	cmp	r5, #0
	beq	.L187
	mov	r1, lr
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L203:
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
	bne	.L205
	add	ip, r0, #11075584
	ldr	r1, [r1, #664]
	add	ip, ip, #45056
	sub	r1, r1, #1
	ldr	r4, [ip, #2928]
	rsb	r2, r2, r1
	cmp	r4, #0
	beq	.L234
	movw	ip, #47844
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #16384
	add	ip, r0, ip
	b	.L211
.L210:
	cmp	r3, r4
	beq	.L235
.L211:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #724]
	cmp	lr, r2
	bne	.L210
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L210
	ldr	lr, [r1, #712]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L210
	ldr	r6, [r1, #56]
	ldr	lr, [r5, #120]
	cmp	r6, lr
	bne	.L210
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L205:
	add	r3, r0, #11075584
	ldr	r1, [r1, #664]
	add	r3, r3, #45056
	ldr	r5, [r3, #2928]
	rsb	r2, r2, r1, lsl #1
	cmp	r5, #0
	beq	.L236
	movw	r4, #47844
	add	r7, r0, #11141120
	movt	r4, 169
	add	r7, r7, #16384
	add	r4, r0, r4
	mov	ip, #0
	b	.L216
.L212:
	tst	r3, #2
	beq	.L214
	ldr	r3, [r1, #784]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L237
.L214:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L238
.L216:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L212
	ldr	lr, [r1, #748]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L212
	ldr	r8, [r1, #56]
	ldr	lr, [r7, #120]
	cmp	r8, lr
	bne	.L212
	ldr	lr, [r1, #760]
	cmp	lr, r2
	bne	.L212
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #11075584
	strb	r3, [r1, #3]
	add	r2, r2, #45056
	mov	r1, #0
	ldr	r3, [r2, #2792]
	strb	r1, [r3, #750]
	ldr	r3, [r2, #2792]
	ldrb	ip, [r3, #712]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #714]
	ldreq	r3, [r2, #2792]
	streqb	r1, [r3, #713]
	ldreq	r3, [r2, #2792]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r1, [r3, #48]
	mov	r2, ip
	add	r1, r0, r1, lsl #2
	str	ip, [r1, #148]
	ldrsb	r1, [r3, #6]
	b	.L231
.L237:
	ldr	lr, [r1, #56]
	ldr	r3, [r7, #120]
	cmp	lr, r3
	bne	.L214
	ldr	r3, [r1, #796]
	cmp	r3, r2
	bne	.L214
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #3]
	add	r3, r3, #11075584
	mov	r2, #0
	add	r3, r3, #45056
	ldr	r1, [r3, #2792]
	strb	r2, [r1, #786]
	ldr	r1, [r3, #2792]
	ldrb	ip, [r1, #712]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r2
	streqb	r2, [r1, #714]
	ldreq	r1, [r3, #2792]
	streqb	r2, [r1, #713]
	ldreq	r1, [r3, #2792]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r3, [r1, #48]
	mov	r2, ip
	add	r3, r0, r3, lsl #2
	str	ip, [r3, #148]
	ldrsb	r1, [r1, #6]
.L231:
	ldr	r0, [r0, #120]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	FSP_SetRef
.L238:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L235:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L234:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L236:
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
	beq	.L240
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	r5, [r3, #2932]
	cmp	r5, #0
	beq	.L269
	movw	r4, #47908
	add	r7, r0, #11141120
	movt	r4, 169
	add	r7, r7, #16384
	add	r4, r0, r4
	mov	ip, #0
	b	.L249
.L245:
	tst	r3, #2
	beq	.L247
	ldr	r3, [r1, #784]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L270
.L247:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L271
.L249:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L245
	ldr	lr, [r1, #748]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L245
	ldr	r8, [r1, #56]
	ldr	lr, [r7, #120]
	cmp	r8, lr
	bne	.L245
	ldr	lr, [r1, #756]
	cmp	r2, lr
	bne	.L245
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #11075584
	strb	r3, [r1, #3]
	add	r2, r2, #45056
	mov	r1, #0
	ldr	r3, [r2, #2856]
	strb	r1, [r3, #749]
	ldr	r3, [r2, #2856]
	ldrb	ip, [r3, #712]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #714]
	ldreq	r3, [r2, #2856]
	streqb	r1, [r3, #713]
	ldreq	r3, [r2, #2856]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r1, [r3, #48]
	mov	r2, ip
	add	r1, r0, r1, lsl #2
	str	ip, [r1, #148]
	ldrsb	r1, [r3, #6]
	b	.L266
.L240:
	add	r1, r0, #11075584
	add	r1, r1, #45056
	ldr	r4, [r1, #2932]
	cmp	r4, #0
	beq	.L272
	movw	ip, #47908
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #16384
	add	ip, r0, ip
	b	.L251
.L250:
	cmp	r3, r4
	beq	.L273
.L251:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #720]
	cmp	lr, r2
	bne	.L250
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L250
	ldr	lr, [r1, #712]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L250
	ldr	r6, [r1, #56]
	ldr	lr, [r5, #120]
	cmp	r6, lr
	bne	.L250
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_UnMarkFrameStoreRef
.L270:
	ldr	lr, [r1, #56]
	ldr	r3, [r7, #120]
	cmp	lr, r3
	bne	.L247
	ldr	r3, [r1, #792]
	cmp	r2, r3
	bne	.L247
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #3]
	add	r3, r3, #11075584
	mov	r2, #0
	add	r3, r3, #45056
	ldr	r1, [r3, #2856]
	strb	r2, [r1, #785]
	ldr	r1, [r3, #2856]
	ldrb	ip, [r1, #712]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r2
	streqb	r2, [r1, #714]
	ldreq	r1, [r3, #2856]
	streqb	r2, [r1, #713]
	ldreq	r1, [r3, #2856]
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	ldr	r3, [r1, #48]
	mov	r2, ip
	add	r3, r0, r3, lsl #2
	str	ip, [r3, #148]
	ldrsb	r1, [r1, #6]
.L266:
	ldr	r0, [r0, #120]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	FSP_SetRef
.L273:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L271:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L272:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L269:
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
	beq	.L275
	ldr	r7, [r3, #2928]
	cmp	r7, #0
	beq	.L304
	movw	r5, #47844
	add	r8, r0, #11141120
	movt	r5, 169
	add	r8, r8, #16384
	add	r5, r0, r5
	mov	ip, #0
	b	.L289
.L281:
	tst	r4, #2
	beq	.L284
	ldr	lr, [r3, #784]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	beq	.L305
.L284:
	add	ip, ip, #1
	cmp	ip, r7
	beq	.L306
.L289:
	ldr	r3, [r5, #4]!
	ldrb	r4, [r3, #3]	@ zero_extendqisi2
	tst	r4, #1
	beq	.L281
	ldr	lr, [r3, #748]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L281
	ldr	lr, [r3, #760]
	cmp	lr, r2
	bne	.L281
	ldr	r9, [r3, #56]
	ldr	lr, [r8, #120]
	cmp	r9, lr
	bne	.L281
	ldrb	lr, [r3, #785]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L285
	ldr	lr, [r3, #28]
	cmp	lr, r1
	bne	.L284
.L285:
	add	r0, r0, ip, lsl #2
	str	r1, [r3, #28]
	add	r3, r0, #11075584
	sub	r6, r6, #1
	add	r3, r3, #45056
	clz	r6, r6
	mov	ip, #1
	mov	r0, #0
	ldr	r2, [r3, #2792]
	mov	r6, r6, lsr #5
	add	r1, r6, r1, lsl #1
	str	r1, [r2, #756]
	ldr	r2, [r3, #2792]
	strb	ip, [r2, #749]
	ldr	r2, [r3, #2792]
	strb	r0, [r2, #750]
	ldr	r2, [r3, #2792]
	ldrb	r1, [r2, #712]	@ zero_extendqisi2
	cmp	r1, #3
	cmpne	r1, r0
	bne	.L307
	ldrb	r1, [r2, #785]	@ zero_extendqisi2
	ldrb	r0, [r2, #749]	@ zero_extendqisi2
	cmp	r1, r0
	streqb	r1, [r2, #713]
	ldreq	r3, [r3, #2792]
	ldreqb	r2, [r3, #750]	@ zero_extendqisi2
	streqb	r2, [r3, #714]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L275:
	ldr	r4, [r3, #2928]
	cmp	r4, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	ip, #47844
	add	r5, r0, #11141120
	movt	ip, 169
	add	r5, r5, #16384
	add	ip, r0, ip
	b	.L280
.L279:
	add	r6, r6, #1
	cmp	r6, r4
	beq	.L308
.L280:
	ldr	r3, [ip, #4]!
	ldrb	lr, [r3, #3]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L279
	ldr	lr, [r3, #712]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L279
	ldr	lr, [r3, #724]
	cmp	lr, r2
	bne	.L279
	ldr	r7, [r3, #56]
	ldr	lr, [r5, #120]
	cmp	r7, lr
	bne	.L279
	add	r6, r0, r6, lsl #2
	str	r1, [r3, #28]
	add	r3, r6, #11075584
	mov	r0, #1
	add	r3, r3, #45056
	mov	r2, #0
	ldr	ip, [r3, #2792]
	str	r1, [ip, #720]
	ldr	r1, [r3, #2792]
	strb	r0, [r1, #713]
	ldr	r1, [r3, #2792]
	strb	r0, [r1, #749]
	ldr	r1, [r3, #2792]
	strb	r0, [r1, #785]
	ldr	r1, [r3, #2792]
	strb	r2, [r1, #714]
	ldr	r1, [r3, #2792]
	strb	r2, [r1, #750]
	ldr	r3, [r3, #2792]
	strb	r2, [r3, #786]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L305:
	ldr	lr, [r3, #796]
	cmp	lr, r2
	bne	.L284
	ldr	r4, [r3, #56]
	ldr	lr, [r8, #120]
	cmp	r4, lr
	bne	.L284
	ldrb	lr, [r3, #749]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L288
	ldr	lr, [r3, #28]
	cmp	lr, r1
	bne	.L284
.L288:
	add	r0, r0, ip, lsl #2
	str	r1, [r3, #28]
	add	r3, r0, #11075584
	sub	r6, r6, #2
	add	r3, r3, #45056
	clz	r6, r6
	mov	ip, #1
	mov	r0, #0
	ldr	r2, [r3, #2792]
	mov	r6, r6, lsr #5
	add	r1, r6, r1, lsl #1
	str	r1, [r2, #792]
	ldr	r2, [r3, #2792]
	strb	ip, [r2, #785]
	ldr	r2, [r3, #2792]
	strb	r0, [r2, #786]
	ldr	r2, [r3, #2792]
	ldrb	r1, [r2, #712]	@ zero_extendqisi2
	cmp	r1, #3
	cmpne	r1, r0
	bne	.L309
	ldrb	r1, [r2, #785]	@ zero_extendqisi2
	ldrb	r0, [r2, #749]	@ zero_extendqisi2
	cmp	r1, r0
	streqb	r1, [r2, #713]
	ldreq	r3, [r3, #2792]
	ldreqb	r2, [r3, #786]	@ zero_extendqisi2
	streqb	r2, [r3, #714]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L306:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L308:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L307:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L309:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L304:
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
	bne	.L311
	ldr	r4, [r5, #664]
	mov	r1, r3
	sub	r4, r4, #1
	rsb	r4, r2, r4
	bl	MVC_UnMarkLTFrmByFrmIdx
.L312:
	mov	r3, r5
	mov	r2, r4
	mov	r1, r7
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MVC_MarkPicLTRef
.L311:
	add	r3, r0, #11075584
	ldr	r4, [r5, #664]
	add	r3, r3, #45056
	ldr	lr, [r3, #2928]
	rsb	r4, r2, r4, lsl #1
	cmp	lr, #0
	beq	.L312
	movw	ip, #47844
	add	r8, r0, #11141120
	movt	ip, 169
	add	r8, r8, #16384
	add	ip, r0, ip
	mov	r3, #0
	b	.L315
.L313:
	tst	r2, #2
	beq	.L314
	ldr	r2, [r1, #784]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #65536
	beq	.L326
.L314:
	cmp	r3, lr
	beq	.L312
.L315:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	tst	r2, #1
	beq	.L313
	ldr	r0, [r1, #748]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #65536
	bne	.L313
	ldr	r0, [r1, #760]
	cmp	r0, r4
	bne	.L313
	ldr	r9, [r1, #56]
	ldr	r0, [r8, #120]
	cmp	r9, r0
	bne	.L313
	mov	r3, r7
	mov	r2, #1
	mov	r0, r6
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L312
.L326:
	ldr	r2, [r1, #796]
	cmp	r2, r4
	bne	.L314
	ldr	r0, [r1, #56]
	ldr	r2, [r8, #120]
	cmp	r0, r2
	bne	.L314
	mov	r3, r7
	mov	r2, #2
	mov	r0, r6
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L312
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
	ldr	r3, [r5, #2932]
	str	r1, [r5, #2936]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	r6, #47908
	add	r7, r0, #11141120
	movt	r6, 169
	add	r7, r7, #16384
	add	r6, r0, r6
	mov	r3, r1
	mov	r4, #0
	b	.L331
.L329:
	ldr	r3, [r5, #2932]
	cmp	r3, r4
	ldmlsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, [r5, #2936]
.L331:
	ldr	r1, [r6, #4]!
	add	r4, r4, #1
	ldr	r2, [r1, #28]
	cmp	r2, r3
	bcc	.L329
	ldr	r2, [r1, #56]
	ldr	r3, [r7, #120]
	cmp	r2, r3
	bne	.L329
	mov	r0, r8
	bl	MVC_UnMarkFrameStoreRef
	b	.L329
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
	ldr	r3, [r6, #2928]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	movw	r5, #47844
	add	r7, r0, #11141120
	movt	r5, 169
	add	r7, r7, #16384
	add	r5, r0, r5
	mov	r4, #0
	b	.L335
.L334:
	ldr	r3, [r6, #2928]
	cmp	r3, r4
	bls	.L338
.L335:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	ldr	r3, [r7, #120]
	ldr	r2, [r1, #56]
	cmp	r2, r3
	bne	.L334
	mov	r0, r8
	bl	MVC_UnMarkFrameStoreRef
	ldr	r3, [r6, #2928]
	cmp	r3, r4
	bhi	.L335
.L338:
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
	beq	.L342
	mov	r3, r5
	ldr	r1, [r1, #656]
	bl	MVC_UnMarkLTFldByFrmIdx
.L341:
	mov	r2, #1
	mov	r3, #0
	str	r5, [r4, #668]
	strb	r2, [r4, #4]
	strb	r3, [r4, #5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L342:
	mov	r1, r5
	bl	MVC_UnMarkLTFrmByFrmIdx
	b	.L341
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
	ldr	r2, [r7, #2728]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r2, #52]
	movw	r3, #47992
	add	r6, r0, #11075584
	movt	r3, 169
	add	r1, r0, r1
	add	r0, r6, #45056
	add	r3, r1, r3
	mov	r1, #0
	strb	r1, [r3, #4]
	ldr	r3, [r0, #3152]
	cmp	r3, r1
	subne	r3, r3, #1
	str	r3, [r0, #3152]
	ldrsb	r1, [r2, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L346
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L347
	ldr	r3, [r7, #2728]
	mov	r2, #0
	ldr	r0, [r5, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
.L347:
	ldr	r3, [r7, #2728]
	mov	r2, #0
	ldr	r0, [r5, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
.L346:
	add	r1, r4, #45056
	mov	r3, #0
	add	r6, r6, #45056
	ldr	r2, [r1, #2728]
	strb	r3, [r2, #2]
	ldr	r2, [r1, #2728]
	strb	r3, [r2, #5]
	ldr	r2, [r1, #2728]
	strb	r3, [r2, #3]
	str	r3, [r1, #2728]
	ldr	r3, [r6, #2924]
	sub	r3, r3, #1
	str	r3, [r6, #2924]
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
	ldr	r6, [r3, #2920]
	cmp	r6, #0
	beq	.L375
	movw	r5, #47780
	mov	r4, #0
	movt	r5, 169
	add	r5, r0, r5
.L363:
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L362
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L362
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L362
	ldr	r1, [r3, #56]
	cmn	r7, #1
	cmpne	r1, r7
	beq	.L376
.L362:
	add	r4, r4, #1
	cmp	r4, r6
	bne	.L363
.L375:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L376:
	ldr	ip, [r3, #16]
	mov	r1, r4
	mov	r0, r8
	cmp	ip, #1
	beq	.L362
	strb	r2, [r3, #2]
	bl	MVC_RemoveFrameStoreOutDPB
	b	.L362
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
	bne	.L378
	ldrsb	r3, [r1, #8]
	cmp	r3, #1
	bne	.L390
	strb	r3, [r0, #6]
.L378:
	ldrsb	r1, [r4, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L380
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	cmpne	r3, #0
	beq	.L400
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L389
	cmp	r3, #1
	beq	.L389
	cmp	r2, #3
	beq	.L401
	cmp	r2, #1
	beq	.L402
	cmp	r2, #2
	beq	.L403
.L385:
	ldr	r3, [r5, #224]
	ldr	r2, [r0, #192]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	movls	r0, #0
	bhi	.L404
.L398:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L400:
	ldrsb	r2, [r4, #6]
	mov	r0, #1
	ldr	r1, .L405
	bl	dprint_vfmw
.L382:
	ldr	r3, [r4, #16]
	cmp	r3, #1
	mvnne	r0, #2
	moveq	r3, #2
	mvneq	r0, #2
	streq	r3, [r4, #16]
	b	.L398
.L401:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L385
	mov	r2, r3
	ldr	r1, .L405+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L402:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L385
	mov	r0, r2
	ldr	r1, .L405+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L403:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	tst	r3, #2
	beq	.L385
	ldr	r1, .L405+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L390:
	mvn	r0, #0
	b	.L398
.L380:
	ldrsb	ip, [r4, #6]
	mov	r2, r4
	ldr	r3, [r4, #16]
	mov	r0, #1
	ldr	r1, .L405+16
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L382
.L389:
	ldr	r1, .L405+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L404:
	ldr	r1, .L405+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L398
.L406:
	.align	2
.L405:
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
	add	r8, r1, #656
	mvn	r7, #0
	mvn	r6, #0
	ldrd	r2, [r8]
	mov	r5, r0
	cmp	r3, r7
	cmpeq	r2, r6
	beq	.L407
	add	r9, r0, #11075584
	add	r9, r9, #45056
	ldr	r3, [r9, #2920]
	cmp	r3, #0
	beq	.L407
	movw	r10, #47780
	mvn	r6, #1
	movt	r10, 169
	add	r10, r0, r10
	mvn	r7, #0
	mov	r4, #0
	mvn	r3, #0
	str	r3, [fp, #-48]
.L412:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L411
	ldrsb	r1, [r3, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L411
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	cmpne	r3, #0
	beq	.L411
	ldr	r3, [r10]
	add	r3, r3, #656
	ldrd	r0, [r3]
	cmp	r1, r7
	cmpeq	r0, r6
	strcc	r4, [fp, #-48]
	movcc	r6, r0
	movcc	r7, r1
.L411:
	ldr	r3, [r9, #2920]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L412
	ldr	r3, [fp, #-48]
	cmn	r3, #1
	beq	.L407
	ldrd	r2, [r8]
	cmp	r3, r7
	cmpeq	r2, r6
	bhi	.L426
.L407:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L426:
	strd	r6, [sp]
	mov	r0, #29
	ldr	r1, .L427
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	movw	r1, #28330
	movt	r1, 42
	add	r1, r3, r1
	ldrd	r2, [r8]
	ldr	r1, [r5, r1, asl #2]
	add	r1, r1, #656
	strd	r2, [r1]
	strd	r6, [r8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L428:
	.align	2
.L427:
	.word	.LC11
	UNWIND(.fnend)
	.size	MVC_ExchangePts, .-MVC_ExchangePts
	.align	2
	.global	MVC_GetImagePara
	.type	MVC_GetImagePara, %function
MVC_GetImagePara:
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
	mov	r4, r1
	add	ip, r3, #40960
	ldr	r2, [r0, #252]
	mov	r5, r0
	mov	r0, #2240
	ldr	r1, [ip, #1080]
	movw	r8, #3992
	ldrb	r9, [r4, #15]	@ zero_extendqisi2
	ldrb	r6, [r4, #137]	@ zero_extendqisi2
	mla	r1, r0, r1, r2
	ldrb	lr, [r4, #136]	@ zero_extendqisi2
	ldrb	r0, [r4, #138]	@ zero_extendqisi2
	bfc	r6, #0, #2
	ldr	r7, [r5, #248]
	bfc	lr, #0, #2
	ldr	r2, [r1, #28]
	ldrb	r1, [r4, #14]	@ zero_extendqisi2
	strb	r6, [r4, #137]
	bfi	r0, r1, #1, #1
	strb	lr, [r4, #136]
	strb	r0, [r4, #138]
	str	r9, [r4, #192]
	ldr	r1, [r5, #56]
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	mla	r2, r8, r2, r7
	str	r1, [r4, #180]
	cmp	r0, #3
	ldrls	pc, [pc, r0, asl #2]
	b	.L468
.L432:
	.word	.L431
	.word	.L433
	.word	.L434
	.word	.L431
.L434:
	ldrb	r1, [r4, #137]	@ zero_extendqisi2
	add	r3, r5, #11075584
	ldr	r6, [r4, #44]
	add	r3, r3, #45056
	and	r1, r1, #240
	ldrb	lr, [r4, #136]	@ zero_extendqisi2
	orr	r1, r1, #11
	strb	r1, [r4, #137]
	ldrb	r1, [r4]	@ zero_extendqisi2
	str	r6, [r4, #224]
	bfi	lr, r1, #0, #2
	strb	lr, [r4, #136]
.L430:
	ldrb	r1, [r2, #20]	@ zero_extendqisi2
	str	r1, [r4, #468]
	str	r1, [r4, #472]
	ldrb	r1, [r2, #24]	@ zero_extendqisi2
	cmp	r1, #0
	ldrne	r1, [r2, #68]
	mov	r2, #1
	str	r2, [r4, #476]
	str	r1, [r4, #480]
	ldrb	r2, [ip, #1075]	@ zero_extendqisi2
	cmp	r2, #1
	movne	r2, #0
	str	r2, [r4, #264]
	ldr	r2, [r5, #224]
	ldr	r2, [r2, #24]
	cmp	r2, #0
	beq	.L452
	ldrb	r2, [r4, #712]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L452
	cmp	r0, #3
	ldreqb	r1, [r4, #137]	@ zero_extendqisi2
	bfieq	r1, r2, #0, #2
	streqb	r1, [r4, #137]
.L452:
	ldrb	r2, [r3, #2680]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L453
	ldr	r2, [r3, #2696]
	cmp	r2, #3
	moveq	r3, #1
	streq	r3, [r4, #348]
	beq	.L453
	cmp	r2, #4
	moveq	r3, #2
	streq	r3, [r4, #348]
	beq	.L453
	cmp	r2, #5
	moveq	r3, #3
	streq	r3, [r4, #348]
	beq	.L453
	mov	r0, #0
	ldr	r1, .L482
	str	r0, [r4, #348]
	ldr	r2, [r3, #2696]
	bl	dprint_vfmw
.L453:
	ldr	r0, [r5, #120]
	ldrsb	r1, [r4, #6]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, .L482+4
	mov	r2, #640
	add	r1, r4, #72
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #15
	str	r3, [r5, #296]
	mov	r2, #1
	ldrb	r3, [r4, #712]	@ zero_extendqisi2
	strb	r2, [r5, #291]
	cmp	r3, #0
	movne	r3, #4
	strb	r3, [r5, #284]
	ldr	r3, [r4, #740]
	strb	r2, [r5, #289]
	str	r3, [r5, #300]
	str	r3, [r5, #308]
	str	r3, [r5, #304]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L433:
	ldrb	r1, [r4, #137]	@ zero_extendqisi2
	add	r3, r5, #11075584
	ldr	r6, [r4, #44]
	add	r3, r3, #45056
	ldrb	lr, [r4, #136]	@ zero_extendqisi2
	orr	r1, r1, #3
	strb	r1, [r4, #137]
	ldrb	r1, [r4]	@ zero_extendqisi2
	str	r6, [r4, #224]
	bfi	lr, r1, #0, #2
	strb	lr, [r4, #136]
	b	.L430
.L431:
	ldrb	r1, [r4, #712]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L435
	ldr	lr, [r4, #40]
	ldr	r1, [r4, #44]
	cmp	lr, #0
	ldrb	r8, [r4]	@ zero_extendqisi2
	movne	r6, #3
	str	r1, [r4, #224]
	movne	r7, r6
	moveq	r6, #2
	moveq	r7, #3
.L436:
	ldr	lr, [r4, #764]
	ldr	r1, [r4, #800]
	cmp	lr, r1
	beq	.L480
	movle	lr, #1
	movgt	lr, #0
.L447:
	add	r3, r3, #45056
	ldrb	r1, [r3, #2716]	@ zero_extendqisi2
	cmp	r1, #3
	moveq	lr, #1
	beq	.L448
	cmp	r1, #4
	moveq	lr, #0
.L448:
	ldrb	r1, [r4, #137]	@ zero_extendqisi2
	ldrb	r9, [r4, #136]	@ zero_extendqisi2
	bfi	r1, lr, #4, #2
	bfi	r1, r7, #2, #2
	bfi	r9, r8, #0, #2
	bfi	r1, r6, #0, #2
	strb	r9, [r4, #136]
	strb	r1, [r4, #137]
	b	.L430
.L435:
	ldr	lr, [r4, #772]
	ldr	r1, [r5, #116]
	ldr	r10, [r4, #808]
	cmp	lr, r1
	bhi	.L481
	cmp	r1, r10
	bcc	.L440
.L438:
	ldr	r1, [r4, #44]
	mov	r7, #3
	ldrb	r8, [r4]	@ zero_extendqisi2
	ldrb	r6, [r4, #751]	@ zero_extendqisi2
	ldrb	r9, [r4, #787]	@ zero_extendqisi2
	str	r1, [r4, #224]
.L441:
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	cmp	r1, #1
	streq	r10, [r4, #224]
	moveq	r8, r9
	moveq	r7, #2
	beq	.L443
	cmp	r1, #2
	streq	lr, [r4, #224]
	moveq	r8, r6
	moveq	r7, #1
.L443:
	str	r6, [r4, #128]
	mov	r6, #3
	str	r9, [r4, #132]
	b	.L436
.L440:
	ldrb	r8, [r4, #751]	@ zero_extendqisi2
	mov	r7, #1
	ldrb	r9, [r4, #787]	@ zero_extendqisi2
	str	lr, [r4, #224]
	mov	r6, r8
	b	.L441
.L480:
	ldr	r1, [r4, #140]
	cmp	r1, #720
	movne	lr, #1
	bne	.L447
	ldr	lr, [r4, #144]
	subs	lr, lr, #480
	movne	lr, #1
	b	.L447
.L481:
	cmp	r1, r10
	bcc	.L438
	ldrb	r8, [r4, #787]	@ zero_extendqisi2
	mov	r7, #2
	str	r10, [r4, #224]
	ldrb	r6, [r4, #751]	@ zero_extendqisi2
	mov	r9, r8
	b	.L441
.L468:
	add	r3, r5, #11075584
	add	r3, r3, #45056
	b	.L430
.L483:
	.align	2
.L482:
	.word	.LC12
	.word	vfmw_Osal_Func_Ptr_S
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
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_SetFrmRepeatCount.part.2
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
	ldrb	lr, [r0, #713]	@ zero_extendqisi2
	mov	r5, #1
	ldrb	ip, [r0, #714]	@ zero_extendqisi2
	mov	r4, #2
	ldr	r1, [r0, #736]
	ldrb	r2, [r0, #715]	@ zero_extendqisi2
	ldr	r3, [r0, #716]
	strb	r5, [r0, #748]
	strb	r4, [r0, #784]
	strb	lr, [r0, #749]
	strb	lr, [r0, #785]
	strb	ip, [r0, #750]
	strb	ip, [r0, #786]
	str	r1, [r0, #772]
	str	r1, [r0, #808]
	strb	r2, [r0, #751]
	strb	r2, [r0, #787]
	str	r3, [r0, #752]
	str	r3, [r0, #788]
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
	ldr	r2, [r0, #800]
	mov	lr, #3
	ldr	r1, [r0, #764]
	ldr	r3, [r0, #808]
	cmp	r2, r1
	ldr	r5, [r0, #772]
	ldrb	r4, [r0, #785]	@ zero_extendqisi2
	ldr	ip, [r0, #752]
	movge	r2, r1
	add	r3, r3, r5
	cmp	r4, #0
	strb	lr, [r0, #712]
	mov	r3, r3, lsr #1
	str	ip, [r0, #716]
	str	r2, [r0, #728]
	str	r2, [r0, #32]
	str	r3, [r0, #736]
	beq	.L488
	ldrb	r2, [r0, #749]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L489
.L488:
	ldr	r2, [r0, #784]
	mov	r1, #0
	strb	r1, [r0, #713]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, r1
	beq	.L493
	ldr	r2, [r0, #748]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	movne	ip, #1
	bne	.L491
.L493:
	mov	ip, #0
.L491:
	ldrb	r2, [r0, #787]	@ zero_extendqisi2
	ldrb	r1, [r0, #751]	@ zero_extendqisi2
	str	r3, [r0, #44]
	cmp	r2, r1
	strb	ip, [r0, #714]
	movcs	r3, r2
	movcc	r3, r1
	strb	r3, [r0, #715]
	strb	r3, [r0]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L489:
	mov	r1, #1
	strb	r1, [r0, #713]
	b	.L493
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
	beq	.L524
	cmp	r2, #1
	beq	.L505
	cmp	r2, #2
	beq	.L506
	ldr	r9, [r6, #764]
	ldr	r10, [r6, #800]
.L507:
	add	r8, r5, #11075584
	add	r7, r8, #45056
	ldr	r1, [r7, #3148]
	cmp	r1, #0
	beq	.L516
	ldrb	r4, [r7, #2940]	@ zero_extendqisi2
	cmp	r4, #0
	movwne	r3, #47996
	movne	r4, #0
	movtne	r3, 169
	addne	r3, r5, r3
	bne	.L510
	b	.L508
.L514:
	ldrb	r2, [r3, #1]!	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L508
.L510:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L514
.L516:
	mvn	r0, #0
.L520:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L506:
	ldr	r9, [r6, #800]
	mov	r10, r9
	b	.L507
.L508:
	ldrsb	r1, [r6, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L511
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L511
	add	r2, r5, r4
	movw	r3, #47992
	movt	r3, 169
	add	r3, r2, r3
	mov	r2, #1
	add	r5, r5, r4, lsl #2
	strb	r2, [r3, #4]
	add	r5, r5, #11075584
	ldr	r3, [r0, #28]
	add	r5, r5, #45056
	add	r8, r8, #45056
	ldr	r1, .L525
	mov	r0, #13
	ldr	r3, [r3, #4]
	str	r9, [r5, #3020]
	str	r10, [r5, #3084]
	str	r3, [r5, #2956]
	ldr	r3, [r7, #3152]
	cmp	r3, #15
	addls	r2, r3, r2
	mov	r3, r4
	movhi	r2, #16
	str	r2, [r8, #3152]
	ldr	r2, [r6, #220]
	bl	dprint_vfmw
	mov	r0, #0
	str	r4, [r6, #52]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L505:
	ldr	r9, [r6, #764]
	mov	r10, r9
	b	.L507
.L511:
	mov	r1, #0
	ldrsb	r2, [r6, #6]
	ldrb	r3, [r6, #3]	@ zero_extendqisi2
	stmia	sp, {r0, r1}
	mov	r0, r1
	ldr	r1, .L525+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L520
.L524:
	mov	r0, r6
	movw	r3, #2023
	ldr	r2, .L525+8
	ldr	r1, .L525+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L520
.L526:
	.align	2
.L525:
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
	add	r3, r0, #11075584
	ldr	r2, [r0, #236]
	add	r3, r3, #45056
	mov	r10, r0
	ldr	r0, [r3, #2932]
	ldr	r2, [r2, #3944]
	ldr	r1, [r3, #2928]
	rsb	r2, r0, r2
	cmp	r1, r2
	beq	.L552
.L527:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L552:
	ldr	r8, [r3, #2920]
	cmp	r8, #0
	beq	.L532
	movw	r6, #47780
	add	r1, r10, #11141120
	movt	r6, 169
	mov	r2, #0
	add	r1, r1, #16384
	add	r6, r10, r6
	mov	r5, r2
	mvn	r9, #-2147483648
.L531:
	ldr	r4, [r6, #4]!
	cmp	r4, #0
	beq	.L530
	ldr	r7, [r4, #64]
	cmp	r9, r7
	bls	.L530
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	mov	r0, r4
	cmp	r3, #0
	beq	.L530
	str	r1, [fp, #-52]
	str	r2, [fp, #-48]
	bl	MVC_NonLongTermRefFlg
	ldr	r2, [fp, #-48]
	ldr	r1, [fp, #-52]
	cmp	r0, #0
	beq	.L530
	ldr	r0, [r4, #56]
	ldr	r3, [r1, #120]
	cmp	r0, r3
	moveq	r9, r7
	moveq	r2, r5
.L530:
	add	r5, r5, #1
	cmp	r5, r8
	bne	.L531
.L529:
	movw	r3, #28330
	movt	r3, 42
	add	r3, r2, r3
	ldr	r4, [r10, r3, asl #2]
	cmp	r4, #0
	beq	.L527
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L527
	mov	r0, r4
	bl	MVC_NonLongTermRefFlg
	cmp	r0, #0
	beq	.L527
	add	r3, r10, #11141120
	ldr	r2, [r4, #56]
	add	r3, r3, #16384
	ldr	r3, [r3, #120]
	cmp	r2, r3
	bne	.L527
	mov	r0, r10
	mov	r1, r4
	bl	MVC_UnMarkFrameStoreRef
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	MVC_UpdateReflist
.L532:
	mov	r2, r8
	b	.L529
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, .L563
	mov	r7, r0
	ldr	r3, [r3]
	tst	r3, #16384
	beq	.L553
	add	r6, r0, #11075584
	add	r6, r6, #45056
	ldr	r3, [r6, #2924]
	cmp	r3, #0
	movwne	r5, #47780
	movne	r4, #0
	movtne	r5, 169
	addne	r5, r0, r5
	beq	.L559
.L558:
	ldr	ip, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L563+4
	mov	r0, #14
	add	r4, r4, #1
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	ldr	r3, [ip, #20]
	str	lr, [sp, #4]
	ldr	ip, [ip, #32]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r6, #2924]
	cmp	r3, r4
	bhi	.L558
.L559:
	ldr	r1, .L563+8
	mov	r0, #14
	bl	dprint_vfmw
	ldr	r3, [r6, #2928]
	cmp	r3, #0
	movwne	r5, #47844
	movne	r4, #0
	movtne	r5, 169
	addne	r5, r7, r5
	beq	.L557
.L560:
	ldr	ip, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L563+12
	mov	r0, #14
	ldrb	lr, [ip, #3]	@ zero_extendqisi2
	ldr	r3, [ip, #20]
	str	lr, [sp, #4]
	ldr	ip, [ip, #32]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5]
	mov	r2, r4
	ldr	r1, .L563+16
	mov	r0, #14
	add	r4, r4, #1
	ldr	r3, [r3, #728]
	bl	dprint_vfmw
	ldr	r3, [r6, #2928]
	cmp	r3, r4
	bhi	.L560
.L557:
	ldr	r1, .L563+8
	mov	r0, #14
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L553:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L564:
	.align	2
.L563:
	.word	g_PrintEnable
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
	add	r3, r0, #12288
	add	r1, r0, #16384
	ldrb	r2, [r3, #3482]	@ zero_extendqisi2
	ldr	r4, [r1, #40]
	strb	r2, [r4, #1]
	ldrb	r2, [r3, #3484]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
	bne	.L566
	ldrb	r2, [r3, #3485]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
.L566:
	add	ip, r0, #16384
	strb	r2, [r4, #3]
	ldr	r2, [ip, #48]
	str	r2, [r4, #20]
	ldr	r2, [ip, #92]
	str	r2, [r4, #44]
	ldrb	r2, [r3, #3492]	@ zero_extendqisi2
	strb	r2, [r4]
	ldr	r2, [ip, #60]
	str	r2, [r4, #32]
	ldr	r2, [ip, #116]
	str	r2, [r4, #48]
	ldr	r2, [ip, #52]
	str	r2, [r4, #28]
	ldrb	r2, [r3, #3489]	@ zero_extendqisi2
	str	r2, [r4, #40]
	ldrb	r2, [r3, #3487]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r1, #3
	movne	r1, #0
	strb	r1, [r4, #4]
	ldrb	r2, [r3, #3483]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L569
	bcc	.L570
	cmp	r2, #2
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	str	r4, [r4, #788]
	mov	lr, #1
	strb	lr, [r4, #784]
	mov	r6, #0
	ldrb	lr, [r3, #3484]	@ zero_extendqisi2
	strb	lr, [r4, #785]
	ldrb	lr, [r3, #3485]	@ zero_extendqisi2
	strb	lr, [r4, #786]
	ldr	lr, [ip, #68]
	str	lr, [r4, #800]
	ldrb	lr, [r3, #3492]	@ zero_extendqisi2
	strb	lr, [r4, #787]
	ldr	ip, [ip, #92]
	str	r6, [r4, #40]
	str	ip, [r4, #808]
	ldrb	r5, [r3, #3481]	@ zero_extendqisi2
	cmp	r5, r6
	beq	.L587
	ldr	r2, [r4, #772]
	mov	r5, #3
	strb	r5, [r4, #2]
	add	r3, r3, #4080
	add	ip, ip, r2
	str	ip, [r4, #44]
	str	ip, [r4, #736]
	mvn	r7, #0
	ldrb	r2, [r3, #-593]	@ zero_extendqisi2
	cmp	r2, #1
	orreq	r6, r1, #2
	strb	r6, [r4, #4]
	ldrd	r8, [r3]
	mvn	r6, #0
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L578
	add	r1, r4, #656
	ldrd	r2, [r1]
	cmp	r3, r7
	cmpeq	r2, r6
	beq	.L588
.L578:
	ldrb	r3, [r4, #751]	@ zero_extendqisi2
.L585:
	add	r1, r0, #16384
	cmp	r3, lr
	mov	r0, r4
	movcc	r3, lr
	strb	r3, [r4]
	ldr	r3, [r1, #60]
	str	r3, [r4, #32]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MVC_CombineFldsToFrm
.L570:
	str	r4, [r4, #716]
	mov	r1, #3
	mov	r2, #0
	strb	r1, [r4, #2]
	strb	r2, [r4, #712]
	add	r1, r3, #3488
	ldrb	r5, [r3, #3484]	@ zero_extendqisi2
	mov	r2, #640
	add	r1, r1, #8
	add	r0, r4, #72
	strb	r5, [r4, #713]
	ldrb	r6, [r3, #3485]	@ zero_extendqisi2
	strb	r6, [r4, #714]
	ldr	lr, [ip, #64]
	str	lr, [r4, #728]
	ldrb	r7, [r3, #3492]	@ zero_extendqisi2
	strb	r7, [r4, #715]
	ldr	r8, [ip, #92]
	str	r8, [r4, #736]
	ldr	r3, [ip, #68]
	str	r3, [r4, #764]
	ldr	r3, [ip, #72]
	str	r3, [r4, #800]
	bl	memcpy
	mov	r2, #1
	mov	r3, #2
	str	r8, [r4, #772]
	str	r8, [r4, #808]
	strb	r7, [r4, #751]
	strb	r7, [r4, #787]
	strb	r6, [r4, #750]
	strb	r6, [r4, #786]
	strb	r5, [r4, #749]
	strb	r5, [r4, #785]
	str	r4, [r4, #752]
	str	r4, [r4, #788]
	strb	r2, [r4, #748]
	strb	r3, [r4, #784]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L569:
	strb	r2, [r4, #748]
	mov	r5, #0
	str	r4, [r4, #752]
	ldrb	lr, [r3, #3484]	@ zero_extendqisi2
	strb	lr, [r4, #749]
	ldrb	lr, [r3, #3485]	@ zero_extendqisi2
	strb	lr, [r4, #750]
	ldr	lr, [ip, #68]
	str	lr, [r4, #764]
	ldrb	lr, [r3, #3492]	@ zero_extendqisi2
	strb	lr, [r4, #751]
	ldr	ip, [ip, #92]
	str	r5, [r4, #40]
	str	ip, [r4, #772]
	ldrb	r6, [r3, #3481]	@ zero_extendqisi2
	cmp	r6, r5
	beq	.L589
	ldr	r2, [r4, #808]
	mov	r6, #3
	strb	r6, [r4, #2]
	add	r3, r3, #4080
	add	ip, ip, r2
	str	ip, [r4, #44]
	str	ip, [r4, #736]
	mvn	r7, #0
	ldrb	r2, [r3, #-593]	@ zero_extendqisi2
	mvn	r6, #0
	cmp	r2, #1
	orreq	r5, r1, #1
	strb	r5, [r4, #4]
	ldrd	r8, [r3]
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L574
	add	r1, r4, #656
	ldrd	r2, [r1]
	cmp	r3, r7
	cmpeq	r2, r6
	streqd	r8, [r1]
.L574:
	ldrb	r3, [r4, #787]	@ zero_extendqisi2
	b	.L585
.L587:
	strb	r2, [r4, #2]
	add	r1, r0, #15744
	str	ip, [r4, #44]
	add	r1, r1, #40
	str	ip, [r4, #736]
	add	r0, r4, #72
	ldrb	r3, [r3, #3487]	@ zero_extendqisi2
	mov	r2, #640
	cmp	r3, #1
	moveq	r5, #2
	strb	r5, [r4, #4]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L589:
	strb	r2, [r4, #2]
	add	r1, r3, #3488
	str	ip, [r4, #44]
	add	r1, r1, #8
	str	ip, [r4, #736]
	add	r0, r4, #72
	ldrb	r3, [r3, #3487]	@ zero_extendqisi2
	mov	r2, #640
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r4, #4]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L588:
	strd	r8, [r1]
	b	.L578
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	mov	r6, r0
	add	r3, r3, #45056
	ldr	r4, [r3, #2920]
	ldr	r3, [r3, #2924]
	cmp	r3, r4
	addcc	r5, r0, #11141120
	bcc	.L591
	cmp	r4, #0
	beq	.L596
	movw	r1, #47780
	add	r5, r0, #11141120
	movt	r1, 169
	mov	lr, #0
	add	r8, r5, #16384
	add	r1, r0, r1
	mov	r3, lr
	mvn	ip, #-2147483648
.L594:
	ldr	r2, [r1, #4]!
	cmp	r2, #0
	beq	.L593
	ldr	r0, [r2, #64]
	cmp	ip, r0
	bls	.L593
	ldr	r7, [r2, #56]
	ldr	r2, [r8, #120]
	cmp	r7, r2
	moveq	ip, r0
	moveq	lr, r3
.L593:
	add	r3, r3, #1
	cmp	r3, r4
	bne	.L594
	mov	r4, lr
.L592:
	movw	r3, #28330
	mov	r0, r6
	movt	r3, 42
	add	r3, lr, r3
	ldr	r1, [r6, r3, asl #2]
	bl	MVC_UnMarkFrameStoreRef
	mov	r1, r4
	mov	r0, r6
	bl	MVC_RemoveFrameStoreOutDPB
.L591:
	add	r3, r5, #12288
	add	r5, r5, #16384
	mov	r2, #0
	strb	r2, [r3, #3484]
	ldr	r2, [r5, #56]
	cmp	r2, #0
	movne	r2, #1
	strneb	r2, [r3, #3485]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L596:
	add	r5, r0, #11141120
	mov	lr, r4
	b	.L592
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L614
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	strb	r3, [r5, #1]
	strb	r3, [r5, #3]
.L609:
	ldr	r3, [r4, #8]
	mov	r0, r6
	cmp	r3, #0
	beq	.L608
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #8]
	mov	r0, #7
	ldr	r1, .L615
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #8]
	str	r3, [r4, #24]
	str	r3, [r4, #12]
.L608:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L609
	mov	r3, #0
	strb	r3, [r5]
	str	r3, [r5, #68]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L614:
	mov	r0, r5
	movw	r3, #3891
	ldr	r2, .L615+4
	ldr	r1, .L615+8
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L616:
	.align	2
.L615:
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
	beq	.L618
	ldr	r0, [r0, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L618:
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
	ldr	r1, .L627
	mov	r4, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L623
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L623:
	ldr	r3, [r4, #80]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #80]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L628:
	.align	2
.L627:
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
	b	.L631
.L630:
	add	r4, r4, #88
	cmp	r4, r5
	beq	.L633
.L631:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L630
	mov	r1, r4
	ldr	r0, [r6, #120]
	add	r4, r4, #88
	bl	MVC_ReleaseNAL
	cmp	r4, r5
	bne	.L631
.L633:
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
	movw	r4, #17280
	movw	r5, #17824
	movt	r4, 170
	movt	r5, 170
	add	r4, r0, r4
	add	r5, r0, r5
	mov	r6, r0
	mov	r7, #0
.L636:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L635
	ldr	r0, [r6, #120]
	bl	MVC_ReleaseNAL
	str	r7, [r4]
.L635:
	cmp	r4, r5
	bne	.L636
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
	subs	r4, r0, #0
	beq	.L644
	bl	MVC_ClearAllSlice
	ldr	ip, [r4, #40]
	add	r3, r4, #11075584
	mov	r2, #0
	add	r3, r3, #40960
	movw	r1, #23352
	movt	r1, 1
	mov	r0, r2
	str	ip, [r3, #2732]
	mov	ip, #2
	str	r1, [r3, #2736]
	mov	r1, #7
	strb	ip, [r3, #2721]
	mov	ip, #32
	strb	r1, [r3, #2723]
	mov	r1, #3
	strb	ip, [r3, #2722]
	mvn	ip, #0
	str	r1, [r3, #2744]
	mov	r1, #262144
	str	ip, [r3, #2748]
	str	r1, [r3, #2760]
	strb	r2, [r3, #2720]
	str	r2, [r3, #2752]
	str	r2, [r3, #2756]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L644:
	ldr	r3, .L645
	mov	r2, #300
	ldr	r1, .L645+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L646:
	.align	2
.L645:
	.word	.LC23
	.word	.LC24
	UNWIND(.fnend)
	.size	MVC_ClearCurrPic, .-MVC_ClearCurrPic
	.align	2
	.global	MVC_ArrangeVahbMem
	.type	MVC_ArrangeVahbMem, %function
MVC_ArrangeVahbMem:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 24
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
	mov	r5, r2
	sub	r2, r1, #32
	sub	r3, r5, #32
	mov	r6, r1
	movw	r1, #8160
	cmp	r3, r1
	cmpls	r2, r1
	mov	r4, r0
	movhi	r1, #1
	movls	r1, #0
	bhi	.L657
	ldr	r3, .L659
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #224]
	str	r6, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r6, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L650
	add	r2, r4, #11075584
	ldrb	r3, [fp, #4]	@ zero_extendqisi2
	add	r2, r2, #45056
	mov	r1, #5
	strb	r1, [fp, #-46]
	ldr	r2, [r2, #2920]
	add	r2, r2, #3
	strb	r2, [fp, #-47]
.L655:
	sub	r1, fp, #48
	ldr	r0, [r4, #120]
	strb	r3, [fp, #-45]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L651
	ldr	r1, [r4, #224]
	sub	r3, fp, #52
	ldr	r0, [r4, #120]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L658
	cmp	r0, #0
	moveq	r0, #1
	bne	.L653
.L656:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L650:
	mov	r3, #1
	mov	r2, #5
	strb	r3, [fp, #-47]
	strb	r2, [fp, #-46]
	b	.L655
.L658:
	add	r0, r4, #584
	bl	ResetVoQueue
.L653:
	ldr	r1, .L659+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L656
.L657:
	mov	r3, r5
	mov	r2, r6
	ldr	r1, .L659+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L651:
	ldr	r1, .L659+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L656
.L660:
	.align	2
.L659:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC26
	.word	.LC25
	.word	.LC27
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
	ldrb	r3, [r3, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L663
	bcc	.L678
	cmp	r3, #2
	bne	.L684
.L679:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L675:
	mov	r0, r6
.L684:
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L663:
	mov	r7, #2
.L664:
	movw	r5, #42068
	add	r8, r6, #11141120
	movt	r5, 169
	add	r5, r6, r5
	add	r8, r8, #16384
	add	r4, r6, #256
	ldr	r2, [r5, #4]!
	mov	ip, r6
	mov	lr, #0
	mov	r9, #1
	cmp	r2, #0
	beq	.L666
.L686:
	ldr	r10, [ip, #256]
	cmp	r10, #0
	bne	.L680
	mov	r0, r4
	mov	r3, r10
	b	.L668
.L669:
	ldr	r1, [r0, #4]!
	cmp	r1, #0
	bne	.L671
.L668:
	add	r3, r3, #1
	cmp	r3, r2
	bne	.L669
	ldr	r3, [r6, #224]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L675
	ldr	r1, [r8, #40]
	add	r1, r1, #712
.L671:
	mov	r0, r4
	mov	r3, #0
	b	.L677
.L673:
	ldr	r10, [r0, #4]!
.L677:
	add	r3, r3, #1
	cmp	r10, #0
	streq	r1, [r0]
	cmp	r3, r2
	bne	.L673
.L674:
	add	lr, lr, #1
	add	r4, r4, #132
	cmp	r7, lr
	add	ip, ip, #132
	bls	.L679
	ldr	r2, [r5, #4]!
	cmp	r2, #0
	bne	.L686
.L666:
	ldr	r3, [r6, #224]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L675
	str	r9, [r5]
	ldr	r3, [r8, #40]
	add	r3, r3, #712
	str	r3, [ip, #256]
	b	.L674
.L680:
	mov	r1, r10
	b	.L671
.L678:
	mov	r7, #1
	b	.L664
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
	ldrb	r4, [r2, #1065]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L688
	ldrb	r2, [r2, #1066]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r4, #2
	moveq	r4, #1
.L688:
	add	r3, r3, #45056
	ldr	r5, [r3, #2928]
	cmp	r5, #0
	beq	.L696
	movw	r3, #47848
	mov	r2, #0
	movt	r3, 169
	add	r3, r0, r3
	b	.L693
.L706:
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L704
.L691:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L705
.L693:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L706
	ldrb	lr, [r0, #3]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L692
	ldr	ip, [r0, #748]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	beq	.L707
.L692:
	tst	lr, #2
	beq	.L691
	ldr	ip, [r0, #784]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L691
	ldr	ip, [r0, #796]
	cmp	ip, r1
	bne	.L691
	add	r0, r0, #784
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L704:
	ldr	ip, [r0, #712]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L691
	ldr	ip, [r0, #724]
	cmp	ip, r1
	bne	.L691
	add	r0, r0, #712
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L707:
	ldr	ip, [r0, #760]
	cmp	ip, r1
	bne	.L692
	add	r0, r0, #748
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L705:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L696:
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
	ldrb	r4, [r2, #1065]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L709
	ldrb	r2, [r2, #1066]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r4, #2
	moveq	r4, #1
.L709:
	add	r3, r3, #45056
	ldr	r5, [r3, #2932]
	cmp	r5, #0
	beq	.L717
	movw	r3, #47912
	mov	r2, #0
	movt	r3, 169
	add	r3, r0, r3
	b	.L714
.L727:
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L725
.L712:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L726
.L714:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L727
	ldrb	lr, [r0, #3]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L713
	ldr	ip, [r0, #748]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	beq	.L728
.L713:
	tst	lr, #2
	beq	.L712
	ldr	ip, [r0, #784]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L712
	ldr	ip, [r0, #792]
	cmp	ip, r1
	bne	.L712
	add	r0, r0, #784
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L725:
	ldr	ip, [r0, #712]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L712
	ldr	ip, [r0, #720]
	cmp	ip, r1
	bne	.L712
	add	r0, r0, #712
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L728:
	ldr	ip, [r0, #756]
	cmp	ip, r1
	bne	.L713
	add	r0, r0, #748
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L726:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L717:
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
	ble	.L730
	add	ip, r5, r2, lsl #2
	mov	r1, r2
.L731:
	ldr	r3, [ip, #-4]!
	sub	r1, r1, #1
	str	r3, [ip, #4]
	ldr	lr, [r6]
	cmp	lr, r1
	blt	.L731
.L730:
	add	r3, lr, #1
	str	r3, [r6]
	str	r0, [r5, lr, asl #2]
	ldr	r0, [r6]
	cmp	r2, r0
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r7, r7, #2
	add	lr, r5, r0, lsl #2
	mov	ip, r0
	b	.L735
.L734:
	str	r1, [r5, ip, asl #2]
	add	ip, ip, #1
.L733:
	cmp	r0, r7
	beq	.L743
.L735:
	ldr	r1, [lr], #4
	add	r0, r0, #1
	cmp	r1, #0
	beq	.L733
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L734
	ldr	r3, [r1, #12]
	cmp	r3, r4
	bne	.L734
	ldr	r3, [r1, #4]
	ldr	r3, [r3, #56]
	cmp	r3, r8
	bne	.L734
	cmp	r0, r7
	bne	.L735
.L743:
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
	ble	.L745
	add	ip, r5, r2, lsl #2
	mov	r1, r2
.L746:
	ldr	r3, [ip, #-4]!
	sub	r1, r1, #1
	str	r3, [ip, #4]
	ldr	lr, [r6]
	cmp	lr, r1
	blt	.L746
.L745:
	add	r3, lr, #1
	str	r3, [r6]
	str	r0, [r5, lr, asl #2]
	ldr	r0, [r6]
	cmp	r2, r0
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r7, r7, #2
	add	lr, r5, r0, lsl #2
	mov	ip, r0
	b	.L750
.L749:
	str	r1, [r5, ip, asl #2]
	add	ip, ip, #1
.L748:
	cmp	r0, r7
	beq	.L761
.L750:
	ldr	r1, [lr], #4
	add	r0, r0, #1
	cmp	r1, #0
	beq	.L748
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L749
	ldr	r3, [r1, #8]
	cmp	r3, r4
	bne	.L749
	ldr	r3, [r1, #4]
	ldr	r3, [r3, #56]
	cmp	r3, r8
	bne	.L749
	cmp	r0, r7
	bne	.L750
.L761:
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
	beq	.L769
	ldr	ip, [ip, #2388]
	cmp	r1, ip
	beq	.L770
	mov	r6, r5
	mov	ip, #0
	b	.L764
.L766:
	ldr	r4, [lr, #4]!
	cmp	r1, r4
	beq	.L772
.L764:
	add	ip, ip, #1
	cmp	ip, r5
	bne	.L766
	cmp	r6, #0
	blt	.L773
.L763:
	cmp	r2, #0
	add	r6, r6, r3, lsl #1
	movwne	r3, #5718
	movweq	r3, #5726
	movt	r3, 41
	add	r3, r6, r3
	add	r0, r0, r3, lsl #2
	ldr	r0, [r0, #4]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L772:
	mov	r6, ip
	cmp	r6, #0
	bge	.L763
.L773:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L769:
	mov	r6, r5
	b	.L763
.L770:
	mov	r6, #0
	b	.L763
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
	movw	ip, #27302
	mov	r4, #1648
	movt	ip, 42
	add	ip, r3, ip
	mla	r3, r4, r3, r0
	ldr	lr, [r0, ip, asl #2]
	movw	ip, #31360
	cmp	lr, #0
	movt	ip, 169
	add	ip, r3, ip
	beq	.L780
	add	r4, r0, #11141120
	mov	r3, #0
	mov	r0, ip
	add	r4, r4, #12288
	b	.L779
.L776:
	cmp	r3, lr
	add	r0, r0, #824
	beq	.L782
.L779:
	ldr	ip, [r0, #56]
	add	r3, r3, #1
	cmp	ip, r1
	bne	.L776
	ldrb	ip, [r4, #3483]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L777
	ldr	ip, [r0, #732]
	cmp	ip, r2
	bne	.L776
	add	r0, r0, #712
	ldmfd	sp, {r4, fp, sp, pc}
.L777:
	cmp	ip, #1
	beq	.L783
	cmp	ip, #2
	bne	.L776
	ldr	ip, [r0, #804]
	cmp	ip, r2
	bne	.L776
	add	r0, r0, #784
	ldmfd	sp, {r4, fp, sp, pc}
.L783:
	ldr	ip, [r0, #768]
	cmp	ip, r2
	bne	.L776
	add	r0, r0, #748
	ldmfd	sp, {r4, fp, sp, pc}
.L782:
	mov	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L780:
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
	bls	.L786
	add	r2, r4, r1, lsl #2
	mov	r3, r1
.L787:
	ldr	ip, [r2, #-4]!
	sub	r3, r3, #1
	str	ip, [r2, #4]
	ldr	ip, [r7]
	cmp	ip, r3
	bcc	.L787
.L786:
	add	r3, ip, #1
	str	r3, [r7]
	str	r0, [r4, ip, asl #2]
	ldr	r2, [r7]
	cmp	r1, r2
	ldmccfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	ip, r4, r2, lsl #2
	mov	r0, r2
	b	.L791
.L789:
	cmp	r1, r2
	str	r3, [r4, r0, asl #2]
	add	r0, r0, #1
	bcc	.L798
.L791:
	ldr	r3, [ip], #4
	add	r2, r2, #1
	cmp	r3, #0
	beq	.L789
	ldr	lr, [r3, #4]
	ldr	lr, [lr, #56]
	cmp	lr, r5
	bne	.L789
	ldr	lr, [r3, #20]
	cmp	lr, r6
	bne	.L789
	cmp	r1, r2
	bcs	.L791
.L798:
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
	add	r9, r0, #11075584
	add	r9, r9, #40960
	str	r2, [fp, #-64]
	mov	r2, #0
	mov	r5, r0
	ldrb	r3, [r9, #1065]	@ zero_extendqisi2
	mov	r10, r1
	str	r2, [fp, #-48]
	cmp	r3, r2
	beq	.L800
	ldrb	r3, [r9, #1066]	@ zero_extendqisi2
	cmp	r3, r2
	movne	r3, #2
	moveq	r3, #1
.L800:
	cmp	r10, #1
	bls	.L849
.L799:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L849:
	ldr	r0, [r5, #236]
	cmp	r10, #0
	movweq	r1, #40976
	movweq	r8, #41240
	movweq	r2, #41504
	movweq	r7, #41760
	movwne	r1, #41108
	movwne	r8, #41372
	movwne	r2, #41632
	movwne	r7, #41892
	cmp	r3, #0
	ldr	r3, [r0, #2896]
	movt	r2, 169
	add	r2, r5, r2
	add	r3, r3, #4
	str	r2, [fp, #-100]
	mov	r2, #1
	movt	r1, 169
	mov	r3, r2, asl r3
	str	r3, [fp, #-88]
	ldr	r3, [r9, #1092]
	movt	r8, 169
	ldrne	r2, [fp, #-88]
	movt	r7, 169
	add	r1, r5, r1
	add	r8, r5, r8
	movne	r3, r3, asl #1
	add	r7, r5, r7
	addne	r3, r3, #1
	str	r3, [fp, #-92]
	ldr	r3, [fp, #-64]
	movne	r2, r2, asl #1
	strne	r2, [fp, #-88]
	adds	r3, r3, #2
	str	r3, [fp, #-72]
	beq	.L799
	ldr	r2, [r1]
	cmp	r2, #3
	beq	.L799
	movw	r3, #22868
	str	r9, [fp, #-68]
	mov	r0, r3
	mov	r3, #0
	mov	r4, r3
	str	r3, [fp, #-76]
	str	r3, [fp, #-80]
	mov	r6, r3
	ldr	r3, [fp, #-92]
	movt	r0, 164
	mov	r9, r1
	add	r0, r5, r0
	str	r0, [fp, #-96]
	str	r3, [fp, #-60]
	mov	r3, #1
	str	r3, [fp, #-84]
	b	.L807
.L808:
	cmp	r2, #2
	beq	.L850
	ldr	r3, [fp, #-84]
	cmp	r3, #1
	beq	.L814
	ldr	r3, [fp, #-68]
	ldrb	r3, [r3, #1073]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	mov	r3, r10, asl #1
.L815:
	cmp	r2, #4
	ldr	r2, [r7]
	beq	.L851
	add	r2, r2, #1
	add	r4, r2, r4
	ldr	r2, [fp, #-76]
	cmp	r2, r4
	rsble	r4, r2, r4
.L825:
	ldr	r2, [fp, #-56]
	add	r0, r5, #11141120
	add	r0, r0, #16384
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
	ldr	ip, [r0, #60]
	mov	r0, r5
	str	ip, [sp]
	bl	mvc_reorder_interview
.L812:
	ldr	r3, [fp, #-72]
	add	r6, r6, #1
	cmp	r6, r3
	beq	.L799
	ldr	r2, [r9, #4]!
	add	r7, r7, #4
	add	r8, r8, #4
	cmp	r2, #3
	beq	.L799
.L807:
	cmp	r2, #1
	bhi	.L808
	cmp	r2, #0
	ldr	r3, [r8]
	bne	.L809
	ldr	r2, [fp, #-60]
	mvn	r3, r3
	adds	r3, r2, r3
	str	r3, [fp, #-60]
	bmi	.L852
.L810:
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
	ldr	ip, [r2, #2704]
	sub	r2, fp, #48
	str	r2, [sp]
	ldr	r2, [fp, #-64]
	str	ip, [sp, #4]
	bl	MVC_ReorderSTList
	b	.L812
.L851:
	mvn	r2, r2
	adds	r4, r2, r4
	ldrmi	r2, [fp, #-76]
	addmi	r4, r4, r2
	b	.L825
.L814:
	ldr	r1, [fp, #-68]
	add	r3, r5, #10747904
	add	r3, r3, #20480
	ldr	r0, [r1, #2704]
	ldr	r1, [r3, #2384]
	adds	r1, r1, #1
	beq	.L816
	ldr	r3, [r3, #2388]
	cmp	r0, r3
	beq	.L817
	ldr	ip, [fp, #-96]
	mov	r3, #0
	str	r1, [fp, #-80]
	b	.L818
.L820:
	ldr	lr, [ip, #4]!
	cmp	r0, lr
	beq	.L834
.L818:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L820
.L819:
	ldr	r3, [fp, #-68]
	mov	r4, r1
	ldr	ip, [fp, #-96]
	ldrb	r3, [r3, #1073]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	mov	r3, #0
	b	.L830
.L822:
	ldr	lr, [ip, #4]!
	cmp	r0, lr
	beq	.L835
.L830:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L822
	cmp	r4, #0
	blt	.L836
.L829:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	mov	r3, r10, asl #1
	beq	.L823
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
	b	.L815
.L809:
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	add	r3, r2, r3
	ldr	r2, [fp, #-88]
	str	r3, [fp, #-60]
	cmp	r2, r3
	rsble	r3, r2, r3
	strle	r3, [fp, #-60]
	b	.L810
.L850:
	ldr	r1, [fp, #-68]
	sub	r0, fp, #48
	ldr	r3, [fp, #-100]
	ldr	r2, [fp, #-64]
	ldr	ip, [r1, #2704]
	mov	r1, r10
	ldr	r3, [r3, r6, asl #2]
	str	r0, [sp]
	mov	r0, r5
	str	ip, [sp, #4]
	bl	MVC_ReorderLTList
	b	.L812
.L834:
	str	r3, [fp, #-80]
	b	.L819
.L835:
	mov	r4, r3
	cmp	r4, #0
	bge	.L829
.L836:
	mov	r3, #0
	mvn	r4, #0
	mov	r1, r3
	str	r3, [fp, #-84]
	str	r1, [fp, #-76]
	mov	r3, r10, asl #1
	b	.L815
.L823:
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
	b	.L815
.L852:
	ldr	r2, [fp, #-88]
	add	r3, r3, r2
	str	r3, [fp, #-60]
	b	.L810
.L816:
	ldr	r3, [fp, #-68]
	mov	r4, r1
	str	r1, [fp, #-80]
	ldrb	r3, [r3, #1073]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	b	.L829
.L817:
	ldr	r1, [fp, #-68]
	mov	r3, #0
	mov	r4, r3
	str	r3, [fp, #-80]
	ldrb	r1, [r1, #1073]	@ zero_extendqisi2
	str	r1, [fp, #-56]
	b	.L829
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
	add	r5, r0, #11075584
	mov	r6, r0
	add	r4, r5, #40960
	ldrb	r1, [r4, #1064]	@ zero_extendqisi2
	cmp	r1, #2
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r4, #12]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L865
.L856:
	ldr	r3, [r4, #1124]
	cmp	r1, #1
	add	r3, r3, #1
	str	r3, [r4, #1112]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L866
.L858:
	add	r5, r5, #40960
	ldr	r3, [r5, #1128]
	add	r3, r3, #1
	str	r3, [r5, #1116]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L865:
	mov	r1, #0
	ldr	r2, [r4, #1124]
	bl	MVC_ReorderRefPiclist
	ldrb	r1, [r4, #1064]	@ zero_extendqisi2
	b	.L856
.L866:
	ldr	r2, [r4, #1128]
	mov	r0, r6
	bl	MVC_ReorderRefPiclist
	b	.L858
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
	ldr	lr, .L930
	movcc	r4, r2
	ldr	ip, .L930+4
	movcs	r4, #31
	cmp	r6, #0
	str	r3, [fp, #-52]
	movne	r6, lr
	moveq	r6, ip
	cmp	r0, #1
	moveq	r5, #0
	moveq	r10, r5
	beq	.L870
	cmp	r0, #2
	moveq	r5, #0
	moveq	r10, r5
	bne	.L878
.L879:
	cmp	r10, r4
	movcs	r3, #0
	movcc	r3, #1
	cmp	r5, r4
	str	r3, [fp, #-48]
	movcs	r2, #0
	movcc	r2, #1
	orrs	r3, r2, r3
	beq	.L878
	cmp	r2, #0
	beq	.L884
	add	r8, r7, r5, lsl #2
	b	.L883
.L880:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L884
.L883:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	tst	ip, #2
	beq	.L880
	add	r0, r0, #784
	blx	r6
	cmp	r0, #0
	beq	.L880
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
.L884:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r10, lsl #2
	bne	.L886
	b	.L879
.L885:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L879
.L886:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	tst	r1, #1
	beq	.L885
	add	r0, r0, #748
	blx	r6
	cmp	r0, #0
	beq	.L885
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r9]
	ldr	r1, [r3]
	add	r2, r2, #748
	ldr	r3, [fp, #-52]
	str	r2, [r3, r1, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
	b	.L879
.L929:
	add	r0, r0, #748
	blx	r6
	cmp	r0, #0
	beq	.L871
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r8]
	ldr	r0, [r3]
	add	r2, r2, #748
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L875:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r5, lsl #2
	bne	.L877
	b	.L870
.L876:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L870
.L877:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	tst	r1, #2
	beq	.L876
	add	r0, r0, #784
	blx	r6
	cmp	r0, #0
	beq	.L876
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
.L870:
	cmp	r10, r4
	movcs	r2, #0
	movcc	r2, #1
	cmp	r5, r4
	movcs	r3, #0
	movcc	r3, #1
	str	r3, [fp, #-48]
	orrs	r3, r3, r2
	beq	.L878
	cmp	r2, #0
	beq	.L875
	add	r9, r7, r10, lsl #2
	b	.L874
.L871:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L875
.L874:
	mov	r8, r9
	ldr	r0, [r9], #4
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	tst	ip, #1
	beq	.L871
	b	.L929
.L878:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L931:
	.align	2
.L930:
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
.L935:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L933
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L943
.L933:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L935
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L943:
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
	beq	.L948
	ldr	r3, [r0]
	cmp	r3, r2
	beq	.L949
	mov	ip, r0
	mov	r3, #0
	mov	r0, r1
	b	.L946
.L947:
	ldr	lr, [ip, #4]!
	cmp	lr, r2
	beq	.L950
.L946:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L947
	ldmfd	sp, {fp, sp, pc}
.L950:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L948:
	mov	r0, r1
	ldmfd	sp, {fp, sp, pc}
.L949:
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
	beq	.L955
	ldr	r3, [r1]
	cmp	r3, r0
	beq	.L956
	mov	r3, #0
	b	.L953
.L954:
	ldr	ip, [r1, #4]!
	cmp	ip, r0
	beq	.L952
.L953:
	add	r3, r3, #1
	cmp	r3, r2
	mov	lr, r3
	bne	.L954
.L952:
	cmp	r2, #0
	cmpne	r2, lr
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L955:
	mov	lr, r2
	b	.L952
.L956:
	mov	lr, #0
	b	.L952
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
	beq	.L973
	cmp	r0, #2
	ldmnefd	sp, {fp, sp, pc}
	cmp	r2, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r0, [ip]
	add	r1, r1, #784
	mov	lr, #0
.L964:
	add	lr, lr, #1
	str	r1, [r3, r0, asl #2]
	cmp	lr, r2
	ldr	r0, [ip]
	add	r1, r1, #824
	add	r0, r0, #1
	str	r0, [ip]
	bne	.L964
	ldmfd	sp, {fp, sp, pc}
.L973:
	cmp	r2, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r0, [ip]
	add	r1, r1, #748
	mov	lr, #0
.L960:
	add	lr, lr, #1
	str	r1, [r3, r0, asl #2]
	cmp	lr, r2
	ldr	r0, [ip]
	add	r1, r1, #824
	add	r0, r0, #1
	str	r0, [ip]
	bne	.L960
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
	mov	r10, r0
	ldr	r5, [lr, #2384]
	movw	r0, #22868
	movt	r0, 164
	str	r2, [fp, #-48]
	adds	r5, r5, #1
	str	r3, [fp, #-52]
	ldr	r6, [r4, #2704]
	add	r0, r10, r0
	beq	.L993
	ldr	r3, [lr, #2388]
	cmp	r6, r3
	beq	.L994
	mov	r2, r0
	mov	r3, #0
	b	.L976
.L977:
	ldr	r0, [r2, #4]!
	cmp	r6, r0
	beq	.L975
.L976:
	add	r3, r3, #1
	cmp	r3, r5
	mov	lr, r3
	bne	.L977
.L975:
	ldrb	r3, [r4, #1073]	@ zero_extendqisi2
	add	lr, lr, r1, lsl #1
	add	r8, r10, #11141120
	add	ip, ip, #45056
	cmp	r3, #0
	add	r6, r8, #12288
	movwne	r3, #5718
	movweq	r3, #5726
	movtne	r3, 41
	movteq	r3, 41
	addne	r3, lr, r3
	addeq	r3, lr, r3
	ldrb	r2, [r6, #3483]	@ zero_extendqisi2
	addne	lr, r10, lr, lsl #2
	add	r3, r10, r3, lsl #2
	movwne	r9, #22892
	sub	r2, r2, #2
	addeq	lr, r10, lr, lsl #2
	ldr	r7, [r3, #4]
	movweq	r9, #22924
	ldr	r3, [ip, #2920]
	clz	r2, r2
	movt	r9, 164
	add	r9, lr, r9
	subs	r4, r3, #1
	mov	r2, r2, lsr #5
	bmi	.L974
	movw	r5, #28330
	str	r10, [fp, #-56]
	movt	r5, 42
	add	r5, r3, r5
	add	r8, r8, #16384
	add	r5, r10, r5, lsl #2
	mov	r10, r2
	b	.L991
.L1017:
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r3, #3
	ldreq	r2, [r1, #732]
	bne	.L981
.L983:
	add	r3, r1, r10
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L981
	ldr	r3, [r8, #60]
	cmp	r3, r2
	beq	.L1016
.L981:
	subs	r4, r4, #1
	bmi	.L974
.L991:
	ldr	r1, [r5, #-4]!
	cmp	r1, #0
	beq	.L981
	ldrb	r3, [r6, #3483]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1017
	cmp	r3, #1
	beq	.L1018
	cmp	r3, #2
	bne	.L981
	ldrb	r2, [r6, #3481]	@ zero_extendqisi2
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	ubfx	r3, r3, #1, #1
	beq	.L986
	ldr	r2, [r8, #40]
	ldr	r0, [r1, #768]
	ldr	r2, [r2, #768]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L986:
	cmp	r3, #0
	ldrne	r2, [r1, #804]
	bne	.L983
	subs	r4, r4, #1
	bpl	.L991
.L974:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1018:
	ldrb	r2, [r6, #3481]	@ zero_extendqisi2
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	and	r3, r3, #1
	beq	.L985
	ldr	r2, [r8, #40]
	ldr	r0, [r1, #804]
	ldr	r2, [r2, #804]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L985:
	cmp	r3, #0
	ldrne	r2, [r1, #768]
	bne	.L983
	b	.L981
.L1016:
	cmp	r7, #0
	ldr	ip, [r1, #56]
	beq	.L981
	ldr	r3, [r9]
	cmp	ip, r3
	beq	.L987
	mov	r2, r9
	mov	r3, #0
.L988:
	add	r3, r3, #1
	cmp	r3, r7
	beq	.L981
	ldr	r0, [r2, #4]!
	cmp	ip, r0
	bne	.L988
.L987:
	ldr	r3, [fp, #-52]
	mov	r2, #824
	ldr	ip, .L1019
	ldr	r0, [r3]
	ldr	r3, [ip, #52]
	ldr	ip, [fp, #-48]
	mla	r0, r2, r0, ip
	blx	r3
	ldr	r0, [fp, #-52]
	ldr	ip, [fp, #-48]
	mov	r2, #824
	ldr	r3, [r0]
	mla	r3, r2, r3, ip
	ldr	r2, [fp, #-56]
	str	r3, [r3, #788]
	str	r3, [r3, #752]
	str	r3, [r3, #716]
	ldr	r3, [r0]
	ldr	r1, [r2, #52]
	mov	r2, #824
	mla	r2, r2, r3, ip
	sub	r3, r1, #1
	str	r3, [r2, #48]
	ldr	r3, [r0]
	cmp	r3, r7
	beq	.L974
	add	r3, r3, #1
	mov	r2, r0
	str	r3, [r0]
	b	.L981
.L993:
	mov	lr, r5
	b	.L975
.L994:
	mov	lr, #0
	b	.L975
.L1020:
	.align	2
.L1019:
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
	mov	r5, r0
	add	r9, r0, #11141120
	ldrb	r7, [r4, #1064]	@ zero_extendqisi2
	str	r3, [r4, #2716]
	cmp	r7, r3
	str	r3, [r4, #2712]
	bne	.L1022
	add	r3, r9, #12288
	str	r3, [fp, #-240]
	ldrb	r6, [r3, #3483]	@ zero_extendqisi2
	add	r3, r2, #45056
	str	r3, [fp, #-244]
	cmp	r6, #0
	bne	.L1180
	ldr	ip, [r3, #2928]
	cmp	ip, #0
	beq	.L1106
	movw	r1, #47844
	mov	r3, r6
	movt	r1, 169
	add	r1, r0, r1
	b	.L1028
.L1027:
	cmp	r3, ip
	beq	.L1026
.L1028:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1027
	ldr	r0, [r2, #712]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #65536
	addeq	r0, r6, #64
	addeq	r2, r2, #712
	addeq	r6, r6, #1
	streq	r2, [r5, r0, asl #2]
	cmp	r3, ip
	bne	.L1028
.L1026:
	add	r3, r5, #256
	mov	r1, r6
	str	r3, [fp, #-248]
	mov	r2, #4
	mov	r0, r3
	ldr	r3, .L1190
	bl	qsort
	ldr	r3, [fp, #-244]
	str	r6, [r4, #1112]
	ldr	r1, [r3, #2932]
	cmp	r1, #0
	beq	.L1107
	movw	r0, #47908
	mov	r7, r6
	movt	r0, 169
	mov	r3, #0
	add	r0, r5, r0
	b	.L1031
.L1030:
	cmp	r3, r1
	beq	.L1181
.L1031:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #3]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1030
	ldr	ip, [r2, #712]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	addeq	ip, r7, #64
	addeq	r2, r2, #712
	addeq	r7, r7, #1
	streq	r2, [r5, ip, asl #2]
	cmp	r3, r1
	bne	.L1031
.L1181:
	rsb	r1, r6, r7
.L1029:
	add	r0, r6, #64
	ldr	r3, .L1190+4
	mov	r2, #4
	add	r0, r5, r0, lsl #2
	bl	qsort
	str	r7, [r4, #1112]
	b	.L1032
.L1022:
	add	r1, r9, #12288
	str	r1, [fp, #-240]
	ldrb	r6, [r1, #3483]	@ zero_extendqisi2
	cmp	r6, #0
	beq	.L1049
	add	r2, r2, #45056
	str	r2, [fp, #-244]
	ldr	r10, [r2, #2928]
	cmp	r10, #0
	beq	.L1182
	movw	r7, #47844
	add	r8, r9, #16384
	movt	r7, 169
	add	r7, r0, r7
	mov	r6, r3
	mov	r1, r7
.L1068:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1067
	sub	r0, fp, #44
	ldr	ip, [r8, #60]
	add	lr, r0, r6, lsl #2
	ldr	r0, [r2, #32]
	cmp	ip, r0
	strge	r2, [lr, #-192]
	addge	r6, r6, #1
.L1067:
	cmp	r3, r10
	bne	.L1068
	sub	r3, fp, #236
	mov	r2, #4
	str	r3, [fp, #-252]
	mov	r1, r6
	mov	r0, r3
	ldr	r3, .L1190+8
	bl	qsort
	ldr	r3, [fp, #-244]
	ldr	r8, [r3, #2928]
	cmp	r8, #0
	beq	.L1177
.L1104:
	add	r9, r9, #16384
	mov	r3, r7
	mov	r2, #0
	mov	r7, r6
.L1071:
	ldr	r1, [r3, #4]!
	add	r2, r2, #1
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1070
	sub	r0, fp, #44
	ldr	ip, [r9, #60]
	add	lr, r0, r7, lsl #2
	ldr	r0, [r1, #32]
	cmp	ip, r0
	strlt	r1, [lr, #-192]
	addlt	r7, r7, #1
.L1070:
	cmp	r2, r8
	bne	.L1071
	ldr	r3, [fp, #-252]
	rsb	r8, r6, r7
	mov	r9, r6, asl #2
	mov	r2, #4
	add	r0, r3, r9
	mov	r1, r8
	ldr	r3, .L1190+12
	bl	qsort
	cmp	r6, #0
	subeq	r10, fp, #172
	beq	.L1072
.L1099:
	sub	r10, fp, #172
	ldr	r2, [fp, #-252]
	add	r8, r10, r8, lsl #2
	mov	r3, #0
.L1073:
	add	r3, r3, #1
	ldr	r1, [r2], #4
	cmp	r3, r6
	str	r1, [r8], #4
	bcc	.L1073
.L1072:
	cmp	r7, r6
	bls	.L1074
	ldr	r3, [fp, #-252]
	add	r9, r3, r9
	mov	r3, r10
.L1075:
	add	r6, r6, #1
	ldr	r2, [r9], #4
	cmp	r6, r7
	str	r2, [r3], #4
	bne	.L1075
.L1074:
	ldr	r8, [fp, #-240]
	movw	r9, #42072
	mov	r6, #0
	add	r3, r5, #256
	str	r6, [r4, #1112]
	mov	r2, r7
	str	r6, [r4, #1116]
	movt	r9, 169
	ldrb	r0, [r8, #3483]	@ zero_extendqisi2
	add	r9, r5, r9
	ldr	r1, [fp, #-252]
	str	r6, [sp, #4]
	str	r9, [sp]
	str	r3, [fp, #-248]
	bl	MVC_GenPiclistfromFrmlist
	ldrb	r0, [r8, #3483]	@ zero_extendqisi2
	movw	r8, #42076
	add	r3, r5, #388
	mov	r2, r7
	mov	r1, r10
	str	r6, [sp, #4]
	movt	r8, 169
	add	r8, r5, r8
	str	r8, [sp]
	str	r3, [fp, #-252]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r3, [fp, #-244]
	ldr	r7, [r3, #2932]
	cmp	r7, r6
	subeq	r10, fp, #108
	beq	.L1076
	movw	r3, #47908
	sub	r10, fp, #108
	movt	r3, 169
	add	r3, r5, r3
	mov	r2, r10
.L1077:
	add	r6, r6, #1
	ldr	r1, [r3, #4]!
	cmp	r6, r7
	str	r1, [r2], #4
	bne	.L1077
.L1076:
	ldr	r3, .L1190+16
	mov	r2, #4
	mov	r1, r7
	mov	r0, r10
	bl	qsort
	ldr	r3, [fp, #-240]
	mov	r6, #1
	mov	r2, r7
	mov	r1, r10
	ldrb	r0, [r3, #3483]	@ zero_extendqisi2
	ldr	r3, [fp, #-248]
	str	r6, [sp, #4]
	str	r9, [sp]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	mov	r2, r7
	mov	r1, r10
	ldrb	r0, [r3, #3483]	@ zero_extendqisi2
	str	r6, [sp, #4]
	ldr	r3, [fp, #-252]
	str	r8, [sp]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r6, [r4, #1112]
	ldr	r3, [r4, #1116]
	rsb	r3, r3, r6
	clz	r3, r3
	mov	r3, r3, lsr #5
.L1066:
	cmp	r6, #1
	movls	r3, #0
	andhi	r3, r3, #1
	cmp	r3, #0
	beq	.L1078
	cmp	r6, #0
	beq	.L1079
	ldr	lr, [r5, #256]
	ldr	r3, [r5, #388]
	cmp	lr, r3
	bne	.L1078
	ldr	r1, [fp, #-248]
	add	r2, r5, #388
	mov	r3, #0
	b	.L1080
.L1081:
	ldr	ip, [r1, #4]!
	ldr	r0, [r2, #4]!
	cmp	ip, r0
	bne	.L1078
.L1080:
	add	r3, r3, #1
	cmp	r3, r6
	bne	.L1081
.L1082:
	ldr	r3, [r5, #392]
	str	lr, [r5, #392]
	str	r3, [r5, #388]
	ldrb	r3, [r4, #1076]	@ zero_extendqisi2
.L1100:
	cmp	r3, #0
	bne	.L1169
.L1083:
	movw	r6, #31360
	movw	r3, #43672
	movt	r6, 169
	add	r6, r5, r6
	mov	r0, r5
	movt	r3, 169
	mov	r1, #0
	add	r3, r5, r3
	mov	r2, r6
	bl	mvc_append_interview_list
	ldr	r3, [fp, #-240]
	ldrb	r0, [r3, #3483]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1183
	ldr	r1, [r4, #2712]
	ldr	ip, [r4, #1112]
	cmp	r1, #0
	beq	.L1085
	add	r2, ip, #63
	movw	r3, #32072
	movt	r3, 169
	add	r3, r5, r3
	add	r2, r5, r2, lsl #2
.L1086:
	add	r0, r0, #1
	str	r3, [r2, #4]!
	cmp	r0, r1
	add	r3, r3, #824
	bne	.L1086
	add	ip, ip, r0
.L1085:
	str	ip, [r4, #1112]
.L1087:
	ldrb	r1, [r4, #1064]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1184
.L1170:
	ldr	r0, [r4, #1112]
.L1084:
	cmp	r1, #0
	bne	.L1042
	cmp	r0, #0
	ldreq	r1, .L1190+20
	beq	.L1171
.L1041:
	ldr	r2, [r4, #1124]
	ldr	r3, [r4, #1128]
	add	r2, r2, #1
	ldr	r1, [r4, #1116]
	cmp	r0, r2
	add	r3, r3, #1
	movcc	r2, r0
	cmp	r3, r1
	str	r2, [r4, #1112]
	movcs	r3, r1
	cmp	r2, #32
	str	r3, [r4, #1116]
	bhi	.L1093
.L1101:
	add	r1, r2, #63
	mov	r0, #0
	add	r1, r5, r1, lsl #2
.L1094:
	add	r2, r2, #1
	str	r0, [r1, #4]!
	cmp	r2, #32
	bls	.L1094
.L1093:
	cmp	r3, #32
	bhi	.L1097
	add	r3, r3, #96
	add	r1, r5, #516
	mov	r2, #0
	add	r5, r5, r3, lsl #2
.L1096:
	str	r2, [r5, #4]!
	cmp	r5, r1
	bne	.L1096
.L1097:
	mov	r0, #0
.L1163:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1049:
	add	r3, r2, #45056
	str	r3, [fp, #-244]
	ldr	r10, [r3, #2928]
	cmp	r10, #0
	beq	.L1052
	movw	r7, #47844
	add	lr, r9, #16384
	movt	r7, 169
	add	r7, r0, r7
	mov	r3, r6
	mov	r1, r7
	b	.L1054
.L1053:
	cmp	r3, r10
	beq	.L1185
.L1054:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1053
	ldr	r0, [r2, #728]
	add	r8, r6, #64
	ldr	ip, [lr, #64]
	add	r2, r2, #712
	cmp	ip, r0
	strge	r2, [r5, r8, asl #2]
	addge	r6, r6, #1
	cmp	r3, r10
	bne	.L1054
.L1185:
	add	r3, r5, #256
	mov	r2, #4
	str	r3, [fp, #-248]
	mov	r1, r6
	mov	r0, r3
	ldr	r3, .L1190+24
	bl	qsort
	ldr	r3, [fp, #-244]
	ldr	r8, [r3, #2928]
	cmp	r8, #0
	beq	.L1176
.L1102:
	add	r9, r9, #16384
	mov	r10, r6
	mov	r3, #0
	b	.L1057
.L1056:
	cmp	r3, r8
	beq	.L1186
.L1057:
	ldr	r2, [r7, #4]!
	add	r3, r3, #1
	ldrb	r1, [r2, #3]	@ zero_extendqisi2
	cmp	r1, #3
	bne	.L1056
	ldr	r1, [r2, #728]
	add	ip, r10, #64
	ldr	r0, [r9, #64]
	add	r2, r2, #712
	cmp	r0, r1
	strlt	r2, [r5, ip, asl #2]
	addlt	r10, r10, #1
	cmp	r3, r8
	bne	.L1057
.L1186:
	rsb	r8, r6, r10
	add	r0, r6, #64
	ldr	r3, .L1190+28
	mov	r2, #4
	mov	r1, r8
	add	r0, r5, r0, lsl #2
	bl	qsort
	add	r7, r10, #64
	cmp	r6, #0
	add	r7, r5, r7, lsl #2
	beq	.L1059
.L1098:
	add	r8, r8, #96
	add	r2, r5, #252
	mov	r3, #0
	add	r8, r5, r8, lsl #2
.L1060:
	add	r3, r3, #1
	ldr	r1, [r2, #4]!
	cmp	r3, r6
	str	r1, [r8, #4]!
	bcc	.L1060
.L1059:
	cmp	r10, r6
	bls	.L1061
	add	r3, r6, #63
	add	r2, r5, #384
	add	r3, r5, r3, lsl #2
.L1062:
	add	r6, r6, #1
	ldr	r1, [r3, #4]!
	cmp	r6, r10
	str	r1, [r2, #4]!
	bne	.L1062
.L1061:
	ldr	r3, [fp, #-244]
	str	r10, [r4, #1116]
	str	r10, [r4, #1112]
	ldr	r1, [r3, #2932]
	cmp	r1, #0
	beq	.L1108
	movw	r0, #47908
	mov	r6, r10
	movt	r0, 169
	mov	r3, #0
	add	r0, r5, r0
	b	.L1065
.L1064:
	cmp	r3, r1
	beq	.L1187
.L1065:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #2]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1064
	ldrb	ip, [r2, #713]	@ zero_extendqisi2
	cmp	ip, #1
	addeq	ip, r5, r6, lsl #2
	addeq	r2, r2, #712
	addeq	r6, r6, #1
	streq	r2, [ip, #256]
	streq	r2, [ip, #388]
	cmp	r3, r1
	bne	.L1065
.L1187:
	rsb	r1, r10, r6
.L1063:
	mov	r0, r7
	ldr	r3, .L1190+4
	mov	r2, #4
	bl	qsort
	ldr	r1, [r4, #1112]
	ldr	r3, .L1190+4
	mov	r2, #4
	add	r0, r1, #97
	rsb	r1, r1, r6
	add	r0, r5, r0, lsl #2
	bl	qsort
	str	r6, [r4, #1116]
	str	r6, [r4, #1112]
	mov	r3, #1
	b	.L1066
.L1180:
	ldr	lr, [r3, #2928]
	cmp	lr, #0
	moveq	r7, lr
	beq	.L1025
	movw	r1, #47844
	mov	r3, r7
	movt	r1, 169
	add	r1, r0, r1
.L1034:
	ldr	r2, [r1, #4]!
	sub	r0, fp, #44
	add	ip, r0, r7, lsl #2
	add	r3, r3, #1
	ldrb	r0, [r2, #3]	@ zero_extendqisi2
	cmp	r0, #0
	strne	r2, [ip, #-192]
	addne	r7, r7, #1
	cmp	r3, lr
	bne	.L1034
.L1025:
	mov	r1, r7
	ldr	r3, .L1190+32
	mov	r2, #4
	sub	r0, fp, #236
	bl	qsort
	ldr	r3, [fp, #-240]
	movw	r8, #42072
	mov	r6, #0
	mov	r2, r7
	str	r6, [r4, #1112]
	sub	r1, fp, #236
	ldrb	r0, [r3, #3483]	@ zero_extendqisi2
	movt	r8, 169
	add	r3, r5, #256
	str	r6, [sp, #4]
	add	r8, r5, r8
	str	r8, [sp]
	str	r3, [fp, #-248]
	bl	MVC_GenPiclistfromFrmlist
	ldr	r3, [fp, #-244]
	ldr	r7, [r3, #2932]
	cmp	r7, r6
	subeq	r10, fp, #108
	beq	.L1035
	movw	r3, #47908
	sub	r10, fp, #108
	movt	r3, 169
	add	r3, r5, r3
	mov	r2, r10
.L1036:
	add	r6, r6, #1
	ldr	r1, [r3, #4]!
	cmp	r6, r7
	str	r1, [r2], #4
	bne	.L1036
.L1035:
	ldr	r3, .L1190+16
	mov	r2, #4
	mov	r1, r7
	mov	r0, r10
	bl	qsort
	ldr	r3, [fp, #-240]
	mov	r2, r7
	mov	r1, r10
	ldrb	r0, [r3, #3483]	@ zero_extendqisi2
	mov	r3, #1
	str	r8, [sp]
	str	r3, [sp, #4]
	ldr	r3, [fp, #-248]
	bl	MVC_GenPiclistfromFrmlist
.L1032:
	ldrb	r3, [r4, #1076]	@ zero_extendqisi2
	mov	r2, #0
	str	r2, [r4, #1116]
	cmp	r3, r2
	beq	.L1083
	ldr	r0, [r4, #1112]
	cmp	r0, #0
	bne	.L1188
	ldr	r3, [r5, #224]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L1043
	ldr	r3, [fp, #-240]
	add	r9, r9, #16384
	ldrb	r3, [r3, #3483]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1044
	ldr	r3, [r9, #40]
	add	r3, r3, #712
	str	r3, [r5, #256]
.L1045:
	mov	r3, #1
	str	r3, [r4, #1112]
.L1169:
	ldrb	r1, [r4, #1064]	@ zero_extendqisi2
	b	.L1170
.L1188:
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1041
.L1042:
	cmp	r0, #0
	bne	.L1041
	ldr	r1, [r4, #1116]
	cmp	r1, #0
	beq	.L1189
	ldr	r3, [r4, #1128]
	mov	r2, r0
	str	r0, [r4, #1112]
	add	r3, r3, #1
	cmp	r3, r1
	movcs	r3, r1
	str	r3, [r4, #1116]
	b	.L1101
.L1078:
	ldrb	r3, [r4, #1076]	@ zero_extendqisi2
	b	.L1100
.L1183:
	movw	ip, #42072
	ldr	r2, [r4, #2712]
	ldr	r3, [fp, #-248]
	mov	r1, r6
	movt	ip, 169
	add	ip, r5, ip
	str	ip, [sp]
	bl	MVC_GenPiclistfromFrmlist_Interview
	b	.L1087
.L1044:
	cmp	r3, #1
	ldr	r3, [r9, #40]
	addeq	r3, r3, #748
	addne	r3, r3, #784
	str	r3, [r5, #256]
	b	.L1045
.L1079:
	ldr	lr, [r5, #388]
	b	.L1082
.L1184:
	movw	r6, #33008
	movw	r3, #43676
	movt	r6, 169
	add	r6, r5, r6
	mov	r0, r5
	movt	r3, 169
	mov	r2, r6
	add	r3, r5, r3
	bl	mvc_append_interview_list
	ldr	r3, [fp, #-240]
	ldrb	r0, [r3, #3483]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1089
	ldr	r1, [r4, #2716]
	ldr	ip, [r4, #1116]
	cmp	r1, #0
	beq	.L1090
	add	r2, ip, #96
	movw	r3, #33720
	movt	r3, 169
	add	r3, r5, r3
	add	r2, r5, r2, lsl #2
.L1091:
	add	r0, r0, #1
	str	r3, [r2, #4]!
	cmp	r0, r1
	add	r3, r3, #824
	bne	.L1091
	add	ip, ip, r0
.L1090:
	str	ip, [r4, #1116]
	ldrb	r1, [r4, #1064]	@ zero_extendqisi2
	ldr	r0, [r4, #1112]
	b	.L1084
.L1177:
	ldr	r2, [fp, #-252]
	mov	r9, r6, asl #2
	ldr	r3, .L1190+12
	mov	r1, r8
	add	r0, r2, r9
	mov	r2, #4
	bl	qsort
	subs	r7, r6, #0
	bne	.L1099
.L1172:
	sub	r10, fp, #172
	b	.L1074
.L1176:
	add	r7, r6, #64
	ldr	r3, .L1190+28
	mov	r2, #4
	mov	r1, r8
	add	r7, r5, r7, lsl #2
	mov	r0, r7
	bl	qsort
	subs	r10, r6, #0
	bne	.L1098
	b	.L1061
.L1106:
	mov	r6, ip
	b	.L1026
.L1107:
	mov	r7, r6
	b	.L1029
.L1108:
	mov	r6, r10
	b	.L1063
.L1182:
	sub	r3, fp, #236
	mov	r2, #4
	str	r3, [fp, #-252]
	mov	r1, r10
	mov	r0, r3
	ldr	r3, .L1190+8
	bl	qsort
	ldr	r3, [fp, #-244]
	ldr	r8, [r3, #2928]
	cmp	r8, #0
	movwne	r7, #47844
	movne	r6, r10
	movtne	r7, 169
	addne	r7, r5, r7
	bne	.L1104
	ldr	r3, .L1190+12
	mov	r2, #4
	mov	r1, r8
	ldr	r0, [fp, #-252]
	mov	r7, r8
	bl	qsort
	b	.L1172
.L1052:
	add	r3, r0, #256
	mov	r2, #4
	str	r3, [fp, #-248]
	mov	r1, r10
	mov	r0, r3
	ldr	r3, .L1190+24
	bl	qsort
	ldr	r3, [fp, #-244]
	ldr	r8, [r3, #2928]
	cmp	r8, #0
	movwne	r7, #47844
	movne	r6, r10
	movtne	r7, 169
	addne	r7, r5, r7
	bne	.L1102
	ldr	r7, [fp, #-248]
	mov	r2, #4
	ldr	r3, .L1190+28
	mov	r1, r8
	mov	r10, r8
	mov	r0, r7
	bl	qsort
	b	.L1061
.L1189:
	ldr	r1, .L1190+36
.L1171:
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	b	.L1163
.L1089:
	movw	ip, #42076
	ldr	r2, [r4, #2716]
	mov	r1, r6
	movt	ip, 169
	add	r3, r5, #388
	add	ip, r5, ip
	str	ip, [sp]
	bl	MVC_GenPiclistfromFrmlist_Interview
	b	.L1169
.L1043:
	ldr	r1, .L1190+40
	b	.L1171
.L1191:
	.align	2
.L1190:
	.word	MVC_compare_pic_by_pic_num_desc
	.word	MVC_compare_pic_by_lt_pic_num_asc
	.word	MVC_compare_fs_by_poc_desc
	.word	MVC_compare_fs_by_poc_asc
	.word	MVC_compare_fs_by_lt_pic_idx_asc
	.word	.LC29
	.word	MVC_compare_pic_by_poc_desc
	.word	MVC_compare_pic_by_poc_asc
	.word	MVC_compare_fs_by_frame_num_desc
	.word	.LC30
	.word	.LC28
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, .L1205
	ldr	r3, [r3]
	tst	r3, #8192
	beq	.L1192
	movw	r6, #42068
	add	r8, r0, #252
	movt	r6, 169
	add	r6, r0, r6
	mov	r7, #0
.L1194:
	ldr	r3, [r6, #4]!
	cmp	r3, #0
	movne	r5, r8
	movne	r4, #0
	beq	.L1196
.L1195:
	ldr	ip, [r5, #4]!
	mov	r3, r4
	mov	r2, r7
	ldr	r1, .L1205+4
	mov	r0, #13
	add	r4, r4, #1
	ldr	ip, [ip, #4]
	ldr	lr, [ip, #32]
	str	lr, [sp, #4]
	ldr	ip, [ip, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r6]
	cmp	r3, r4
	bhi	.L1195
.L1196:
	add	r7, r7, #1
	add	r8, r8, #132
	cmp	r7, #2
	bne	.L1194
.L1192:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1206:
	.align	2
.L1205:
	.word	g_PrintEnable
	.word	.LC31
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
	ldr	r2, [r3, #2924]
	cmp	r2, #0
	beq	.L1212
	ldr	r4, [r3, #2920]
	add	r3, r0, #11141120
	add	r3, r3, #16384
	cmp	r4, #0
	ldr	r5, [r3, #60]
	beq	.L1213
	movw	ip, #47780
	mov	r6, #0
	movt	ip, 169
	add	ip, r0, ip
	mov	r1, r6
	mvn	lr, #-2147483648
.L1211:
	ldr	r2, [ip, #4]!
	add	r1, r1, #1
	cmp	r2, #0
	beq	.L1210
	ldr	r3, [r2, #32]
	rsb	r3, r3, r5
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, lr
	ldrlt	r6, [r2, #220]
	movlt	lr, r3
.L1210:
	cmp	r1, r4
	bne	.L1211
.L1209:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1213:
	mov	r6, r4
	b	.L1209
.L1212:
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
	ldrb	r2, [r3, #1064]	@ zero_extendqisi2
	cmp	r2, #2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	add	r2, r0, #11141120
	movw	r6, #48212
	add	r2, r2, #12288
	ldrb	lr, [r2, #3483]	@ zero_extendqisi2
	cmp	lr, #0
	bne	.L1248
	ldr	r4, [r3, #1112]
	movw	r5, #48216
	movt	r6, 169
	movt	r5, 169
	cmp	r4, #0
	add	r6, r0, r6
	add	r5, r0, r5
	mov	r7, lr
	beq	.L1226
.L1250:
	add	r2, r0, #252
	mov	ip, #32
	mov	r3, #0
	b	.L1224
.L1223:
	add	r3, r3, #1
	cmp	r3, r4
	beq	.L1249
.L1224:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #4]
	ldr	r1, [r1, #52]
	cmp	r1, lr
	bne	.L1223
	cmp	ip, r3
	movcs	ip, r3
	add	r3, r3, #1
	cmp	r3, r4
	str	ip, [r5, #-4]
	str	ip, [r6, #4]
	bne	.L1224
.L1249:
	cmp	ip, #31
	bhi	.L1226
.L1225:
	add	lr, lr, #1
	add	r6, r6, #8
	cmp	lr, #16
	add	r5, r5, #8
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	r4, #0
	bne	.L1250
.L1226:
	str	r7, [r5, #-4]
	str	r7, [r6, #4]
	b	.L1225
.L1248:
	ldr	r5, [r3, #1112]
	mov	lr, #0
	movt	r6, 169
	mov	r7, lr
	cmp	r5, #0
	add	r6, r0, r6
	beq	.L1230
.L1252:
	add	r1, r0, #252
	mov	r4, #32
	mov	r2, #0
	b	.L1228
.L1227:
	add	r2, r2, #1
	cmp	r2, r5
	beq	.L1251
.L1228:
	ldr	r3, [r1, #4]!
	ldr	r8, [r3, #4]
	ldrb	ip, [r3]	@ zero_extendqisi2
	ldr	r3, [r8, #52]
	mov	r3, r3, asl #1
	cmp	ip, #2
	orreq	r3, r3, #1
	cmp	r3, lr
	bne	.L1227
	cmp	r4, r2
	movcs	r4, r2
	add	r2, r2, #1
	cmp	r2, r5
	str	r4, [r6]
	bne	.L1228
.L1251:
	cmp	r4, #31
	bhi	.L1230
.L1229:
	add	lr, lr, #1
	add	r6, r6, #4
	cmp	lr, #32
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	r5, #0
	bne	.L1252
.L1230:
	str	r7, [r6]
	b	.L1229
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
	mov	r4, r0
	bl	MVC_FindNearestPOCPicId
	add	r5, r4, #11075584
	mvn	r6, #0
	add	r3, r5, #40960
	ldrb	r2, [r3, #1064]	@ zero_extendqisi2
	str	r6, [r3, #2696]
	cmp	r2, #2
	str	r0, [r3, #2700]
	beq	.L1260
	mov	r0, r4
	bl	MVC_InitListX
	cmp	r0, #0
	bne	.L1261
	mov	r0, r4
	bl	MVC_ReorderListX
	mov	r0, r4
	bl	MVC_RepairList
	cmp	r0, #0
	bne	.L1258
	mov	r0, r4
	add	r5, r5, #40960
	bl	MVC_FindMinRefIdx
	ldr	r3, [r4, #256]
	mov	r0, #0
	cmp	r3, #0
	ldrne	r3, [r3, #4]
	ldrne	r6, [r3, #220]
	str	r6, [r5, #2696]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1260:
	mov	r0, #0
	str	r0, [r3, #1112]
	str	r0, [r3, #1116]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1258:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1261:
	ldr	r1, .L1262
	mov	r0, #13
	bl	dprint_vfmw
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1263:
	.align	2
.L1262:
	.word	.LC32
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
	beq	.L1271
	movw	r3, #48351
	mov	r2, #0
	movt	r3, 169
	mov	lr, r2
	add	r3, r0, r3
	b	.L1270
.L1279:
	ldrb	r1, [r3, #-2]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1268
	cmp	r2, ip
	add	r3, r3, #824
	beq	.L1271
.L1270:
	ldrb	r1, [r3]	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r1, #1
	bne	.L1279
.L1268:
	cmp	r2, ip
	strb	lr, [r3, #-5]
	strb	lr, [r3, #-4]
	add	r3, r3, #824
	bne	.L1270
.L1271:
	ldr	r2, [r0, #52]
	cmp	r2, #0
	beq	.L1280
	mov	r3, #0
	add	r0, r0, #144
	mov	r1, r3
.L1272:
	add	r3, r3, #1
	str	r1, [r0, #4]!
	cmp	r3, r2
	bne	.L1272
	ldmfd	sp, {fp, sp, pc}
.L1280:
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
	mov	r8, r0
	ldr	r0, [r0, #120]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L1298
.L1282:
	ldr	r3, [r8, #48]
	cmp	r3, #0
	beq	.L1289
	movw	r5, #48984
	mov	r6, #0
	movt	r5, 169
	add	r5, r8, r5
	mov	r7, #0
	mov	r9, #0
.L1288:
	sub	r4, r5, #32
	mov	r3, #0
	strb	r3, [r5, #-638]
	strb	r3, [r5, #-637]
.L1287:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L1299
.L1286:
	cmp	r4, r5
	bne	.L1287
	ldr	r3, [r8, #48]
	add	r9, r9, #1
	add	r5, r5, #824
	cmp	r3, r9
	bhi	.L1288
.L1289:
	ldr	r2, [r8, #52]
	cmp	r2, #0
	beq	.L1300
	mov	r3, #0
	add	r8, r8, #144
	mov	r1, r3
.L1290:
	add	r3, r3, #1
	str	r1, [r8, #4]!
	cmp	r3, r2
	bne	.L1290
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1299:
	mov	r1, r2
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	strd	r6, [r4]
	b	.L1286
.L1298:
	add	r0, r8, #584
	bl	ResetVoQueue
	b	.L1282
.L1300:
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
.L1303:
	add	r3, r3, #1
	cmp	r0, r2, asl r3
	bge	.L1303
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
	mov	r4, r0
	add	r0, r0, #11075584
	mov	r5, r1
	add	r7, r0, #40960
	ldr	ip, [r4, #252]
	mov	lr, #2240
	ldrb	r1, [r7, #1076]	@ zero_extendqisi2
	ldr	r3, [r7, #1080]
	sxtb	r2, r1
	cmn	r2, #1
	mla	r3, lr, r3, ip
	beq	.L1322
	cmp	r1, #0
	bne	.L1308
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r3, [r3, #28]
	cmp	r2, #1
	beq	.L1323
	ldr	r2, [r4, #28]
	cmp	r2, r3
	beq	.L1310
	ldr	r1, .L1325
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1308:
	ldr	r1, .L1325+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1322:
	ldr	r2, [r3, #28]
	movw	r6, #3992
	ldr	r3, [r4, #248]
	mla	r6, r6, r2, r3
.L1307:
	ldrb	r3, [r6, #20]	@ zero_extendqisi2
	ldr	r1, [r6, #3952]
	rsb	r3, r3, #2
	ldr	r2, [r6, #3948]
	ldr	lr, [r4, #12]
	mla	r3, r1, r3, r3
	ldr	ip, [r4, #16]
	add	r2, r2, #1
	cmp	r2, lr
	cmpeq	r3, ip
	movne	r8, #1
	moveq	r8, #0
	bne	.L1312
	add	r1, r0, #45056
	ldr	r0, [r6, #3972]
	ldr	r1, [r1, #2920]
	add	r1, r1, #1
	cmp	r0, r1
	movls	ip, r8
	bls	.L1313
.L1312:
	ldr	r1, .L1325+8
	ldr	r8, [r1]
	cmp	r8, #0
	moveq	ip, #1
	beq	.L1313
	mov	ip, ip, asl #4
	mov	r1, r3, asl #4
	mov	lr, lr, asl #4
	mov	r2, r2, asl #4
	strh	ip, [fp, #-42]	@ movhi
	mov	r3, #8
	strh	r2, [fp, #-40]	@ movhi
	sub	r2, fp, #44
	strh	r1, [fp, #-38]	@ movhi
	mov	r1, #2
	strh	lr, [fp, #-44]	@ movhi
	ldr	r0, [r4, #120]
	blx	r8
	mov	ip, #1
.L1313:
	ldrb	r3, [r7, #1075]	@ zero_extendqisi2
	cmp	r3, #1
	ldrne	r1, [r6, #3972]
	subne	r1, r1, #1
	beq	.L1324
.L1316:
	ldr	r3, [r4, #44]
	mov	r0, ip
	cmp	r3, r1
	orrne	ip, ip, #1
	str	ip, [r5]
	str	r1, [r4, #44]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1310:
	movw	r6, #35364
	movt	r6, 168
	add	r6, r4, r6
	b	.L1307
.L1324:
	movw	r0, #39336
	add	r3, r4, #290816
	movt	r0, 168
	add	r3, r3, #808
	add	r0, r4, r0
	mov	r1, #0
.L1315:
	ldr	r2, [r3]
	add	r3, r3, #335872
	add	r3, r3, #308
	cmp	r2, r1
	subhi	r1, r2, #1
	cmp	r3, r0
	bne	.L1315
	add	r1, r1, #1
	mov	r1, r1, asl #1
	cmp	r1, #16
	movcs	r1, #16
	b	.L1316
.L1323:
	movw	r6, #8500
	movt	r6, 5
	mla	r6, r6, r3, r4
	add	r6, r6, #286720
	add	r6, r6, #932
	b	.L1307
.L1326:
	.align	2
.L1325:
	.word	.LC33
	.word	.LC34
	.word	g_event_report
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
	add	r7, r0, #11075584
	ldr	r6, [r0, #236]
	add	r5, r7, #40960
	mov	r2, #1
	ldrb	r1, [r5, #1067]	@ zero_extendqisi2
	ldr	ip, [r6, #2900]
	ldr	r3, [r6, #2896]
	sub	r1, r1, #5
	clz	r1, r1
	cmp	ip, r2
	add	r3, r3, #4
	ldr	lr, [r6, #2904]
	mov	r1, r1, lsr #5
	mov	r3, r2, asl r3
	beq	.L1329
	bcc	.L1330
	cmp	ip, #2
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	cmp	r1, #0
	bne	.L1385
	add	r4, r7, #36864
	ldrb	r2, [r4, #4024]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1363
	ldr	r1, [r4, #4080]
	ldr	r0, [r4, #4076]
	ldr	r2, [r4, #4088]
	cmp	r1, r0
	addcc	r2, r2, r3
	strcc	r2, [r4, #4084]
	bcs	.L1365
.L1366:
	add	r3, r2, r1
	str	r3, [r4, #4072]
	ldrb	r0, [r5, #1072]	@ zero_extendqisi2
	mov	r3, r3, asl #1
	cmp	r0, #0
	subeq	r3, r3, #1
	str	r3, [r4, #4060]
	ldrb	r0, [r5, #1065]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1369
	str	r3, [r4, #4056]
	str	r3, [r4, #4052]
	str	r3, [r4, #4048]
.L1362:
	add	r7, r7, #36864
	str	r1, [r7, #4076]
	str	r2, [r7, #4088]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1330:
	cmp	r1, #0
	add	lr, lr, #4
	mov	r2, r2, asl lr
	bne	.L1386
	add	r4, r7, #36864
	ldrb	r3, [r4, #4024]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1334
	ldr	lr, [r4, #4036]
	ldr	ip, [r4, #4040]
	mov	r1, lr
.L1335:
	ldr	r0, [r4, #4028]
	cmp	r0, ip
	bcs	.L1333
	rsb	r3, r0, ip
	cmp	r3, r2, lsr #1
	addcs	r1, r1, r2
	strcs	r1, [r4, #4044]
	bcs	.L1337
.L1333:
	cmp	r0, ip
	bls	.L1338
	rsb	r3, ip, r0
	cmp	r3, r2, lsr #1
	rsbhi	r1, r2, r1
	strhi	r1, [r4, #4044]
	bls	.L1338
.L1337:
	ldrb	r3, [r5, #1065]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1339
.L1388:
	ldr	r3, [r4, #4032]
	add	r1, r1, r0
	str	r1, [r4, #4048]
	add	r3, r1, r3
	str	r3, [r4, #4052]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r4, #4060]
.L1340:
	ldr	r2, [r4, #4080]
	str	r3, [r4, #4056]
	add	r3, r7, #40960
	ldr	r1, [r4, #4076]
	cmp	r2, r1
	strne	r2, [r4, #4076]
	ldrb	r3, [r3, #1072]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r7, #36864
	ldrne	r2, [r7, #4028]
	ldrne	r3, [r7, #4044]
	strne	r2, [r7, #4040]
	strne	r3, [r7, #4036]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1329:
	cmp	r1, #0
	add	r4, r7, #36864
	movne	r3, #0
	strne	r3, [r4, #4084]
	bne	.L1344
	ldrb	r2, [r4, #4024]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1345
	mov	r3, r1
	str	r1, [r4, #4088]
	str	r1, [r4, #4076]
.L1346:
	str	r3, [r4, #4084]
.L1344:
	ldr	r3, [r6, #2916]
	cmp	r3, #0
	beq	.L1348
	ldr	r3, [r4, #4080]
	ldr	r0, [r4, #4084]
	add	r0, r3, r0
	str	r0, [r4, #4072]
	ldrb	r8, [r5, #1072]	@ zero_extendqisi2
	cmp	r8, #0
	bne	.L1350
	cmp	r0, #0
	beq	.L1351
	sub	r0, r0, #1
	str	r0, [r4, #4072]
.L1350:
	mov	r3, #0
	str	r3, [r5, #8]
	ldr	r1, [r6, #2916]
	cmp	r1, r3
	bgt	.L1371
	cmp	r0, #0
	beq	.L1354
.L1387:
	sub	r9, r0, #1
	mov	r0, r9
	bl	__aeabi_uidiv
	mov	r10, r0
	mov	r0, r9
	str	r10, [r5]
	ldr	r1, [r6, #2916]
	bl	__aeabi_uidivmod
	str	r1, [r4, #4092]
	cmp	r1, #0
	ldr	r0, [r5, #8]
	mul	r0, r0, r10
	str	r0, [r5, #4]
	blt	.L1355
	add	r2, r6, #2912
	add	r1, r1, #1
	add	r2, r2, #4
	mov	r3, #0
.L1356:
	add	r3, r3, #1
	ldr	ip, [r2, #4]!
	cmp	r3, r1
	add	r0, r0, ip
	str	r0, [r5, #4]
	bne	.L1356
.L1355:
	cmp	r8, #0
	ldreq	r3, [r6, #2908]
	addeq	r0, r0, r3
	ldrb	r3, [r5, #1065]	@ zero_extendqisi2
	streq	r0, [r5, #4]
	cmp	r3, #0
	bne	.L1358
	ldr	r2, [r4, #4064]
	ldr	r1, [r4, #4068]
	add	r2, r0, r2
	str	r2, [r4, #4048]
	ldr	r3, [r6, #2912]
	add	r3, r2, r3
	add	r0, r3, r1
	str	r0, [r4, #4052]
	cmp	r0, r2
	movge	r0, r2
	str	r0, [r4, #4060]
.L1359:
	add	r7, r7, #36864
	ldr	r2, [r7, #4080]
	ldr	r3, [r7, #4084]
	str	r0, [r7, #4056]
	str	r2, [r7, #4076]
	str	r3, [r7, #4088]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1348:
	str	r3, [r4, #4072]
	ldrb	r8, [r5, #1072]	@ zero_extendqisi2
.L1351:
	mov	r0, #0
	str	r0, [r5, #8]
	ldr	r3, [r6, #2916]
	cmp	r3, r0
	ble	.L1354
.L1371:
	add	ip, r6, #2912
	mov	r3, #0
	add	ip, ip, #4
	mov	r2, r3
.L1353:
	ldr	r1, [ip, #4]!
	add	r2, r2, #1
	add	r3, r3, r1
	str	r3, [r5, #8]
	ldr	r1, [r6, #2916]
	cmp	r1, r2
	bgt	.L1353
	cmp	r0, #0
	bne	.L1387
.L1354:
	mov	r0, #0
	str	r0, [r5, #4]
	b	.L1355
.L1386:
	add	r4, r0, #11075584
	add	r4, r4, #36864
.L1336:
	mov	r3, #0
	ldr	r0, [r4, #4028]
	str	r3, [r4, #4036]
	mov	lr, r3
	str	r3, [r4, #4040]
	mov	r1, ip
	b	.L1333
.L1385:
	add	r3, r7, #36864
	mov	r1, #0
	mov	r2, r1
	str	r1, [r3, #4084]
	str	r1, [r3, #4052]
	str	r1, [r3, #4048]
	str	r1, [r3, #4056]
	str	r1, [r3, #4060]
	ldr	r1, [r3, #4080]
	b	.L1362
.L1338:
	str	lr, [r4, #4044]
	ldrb	r3, [r5, #1065]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1388
.L1339:
	ldrb	r3, [r5, #1066]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r1, r0
	streq	r3, [r4, #4048]
	strne	r3, [r4, #4052]
	str	r3, [r4, #4060]
	b	.L1340
.L1358:
	ldrb	r3, [r5, #1066]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r2, [r6, #2912]
	ldreq	r3, [r4, #4064]
	ldrne	r3, [r4, #4064]
	addne	r0, r0, r2
	addeq	r0, r0, r3
	streq	r0, [r4, #4048]
	addne	r0, r0, r3
	strne	r0, [r4, #4052]
	str	r0, [r4, #4060]
	b	.L1359
.L1334:
	movw	r3, #4025
	ldrsb	r3, [r4, r3]
	cmp	r3, #0
	bne	.L1336
	ldr	r0, [r4, #4048]
	mov	r1, ip
	mov	lr, r3
	str	r3, [r4, #4036]
	mov	ip, r0
	str	r0, [r4, #4040]
	b	.L1335
.L1345:
	ldr	r1, [r4, #4080]
	ldr	r2, [r4, #4076]
	cmp	r1, r2
	bcs	.L1347
	ldr	r2, [r4, #4088]
	add	r3, r3, r2
	str	r3, [r4, #4084]
	b	.L1344
.L1369:
	ldrb	r0, [r5, #1066]	@ zero_extendqisi2
	str	r3, [r4, #4056]
	cmp	r0, #0
	streq	r3, [r4, #4048]
	strne	r3, [r4, #4052]
	b	.L1362
.L1363:
	str	r1, [r4, #4076]
	mov	r2, r1
	str	r1, [r4, #4088]
	ldr	r1, [r4, #4080]
.L1365:
	str	r2, [r4, #4084]
	b	.L1366
.L1347:
	ldr	r3, [r4, #4088]
	b	.L1346
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
	add	r7, r0, #11141120
	ldr	r3, [r0, #236]
	add	r2, r7, #12288
	mov	r5, #1
	ldrb	r2, [r2, #3483]	@ zero_extendqisi2
	ldr	r3, [r3, #2896]
	cmp	r2, #0
	add	r3, r3, #4
	mov	r5, r5, asl r3
	add	r3, r0, #11075584
	beq	.L1390
	add	r3, r3, #45056
	sub	r6, r2, #1
	sub	r2, r2, #2
	clz	r6, r6
	ldr	r1, [r3, #2928]
	clz	r2, r2
	mov	r6, r6, lsr #5
	cmp	r1, #0
	mov	r2, r2, lsr #5
	beq	.L1410
	movw	lr, #47844
	add	r7, r7, #16384
	movt	lr, 169
	add	lr, r0, lr
	mov	r1, #0
.L1409:
	ldr	ip, [lr, #4]!
	ldrb	r4, [ip, #3]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L1404
	ldr	r4, [ip, #20]
	ldr	r8, [r7, #48]
	cmp	r4, r8
	rsbhi	r4, r5, r4
	str	r4, [ip, #24]
	ldr	ip, [lr]
	ldrb	r4, [ip, #3]	@ zero_extendqisi2
	tst	r4, #1
	beq	.L1407
	ldr	r8, [ip, #748]
	bic	r8, r8, #-16777216
	bic	r8, r8, #255
	cmp	r8, #65536
	ldreq	r4, [ip, #24]
	addeq	r4, r6, r4, lsl #1
	streq	r4, [ip, #760]
	ldreq	ip, [lr]
	ldreqb	r4, [ip, #3]	@ zero_extendqisi2
.L1407:
	tst	r4, #2
	beq	.L1404
	ldr	r4, [ip, #784]
	bic	r4, r4, #-16777216
	bic	r4, r4, #255
	cmp	r4, #65536
	ldreq	r4, [ip, #24]
	addeq	r4, r2, r4, lsl #1
	streq	r4, [ip, #796]
.L1404:
	ldr	ip, [r3, #2928]
	add	r1, r1, #1
	cmp	ip, r1
	bhi	.L1409
.L1410:
	ldr	r1, [r3, #2932]
	cmp	r1, #0
	beq	.L1434
	movw	r4, #47908
	mov	ip, #0
	movt	r4, 169
	add	r4, r0, r4
.L1415:
	ldr	lr, [r4, #4]!
	add	ip, ip, #1
	ldrb	r1, [lr, #3]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1412
	tst	r1, #1
	beq	.L1413
	ldr	r0, [lr, #748]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #256
	ldreq	r1, [lr, #28]
	addeq	r1, r6, r1, lsl #1
	streq	r1, [lr, #756]
	ldreq	lr, [r4]
	ldreqb	r1, [lr, #3]	@ zero_extendqisi2
.L1413:
	tst	r1, #2
	beq	.L1412
	ldr	r1, [lr, #784]
	bic	r1, r1, #-16777216
	bic	r1, r1, #255
	cmp	r1, #256
	ldreq	r1, [lr, #28]
	addeq	r1, r2, r1, lsl #1
	streq	r1, [lr, #792]
.L1412:
	ldr	r1, [r3, #2932]
	cmp	r1, ip
	bhi	.L1415
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1390:
	add	r3, r3, #45056
	ldr	r1, [r3, #2928]
	cmp	r1, #0
	addne	r7, r7, #16384
	movwne	lr, #47844
	movtne	lr, 169
	addne	lr, r0, lr
	bne	.L1399
.L1400:
	ldr	r2, [r3, #2932]
	cmp	r2, #0
	beq	.L1435
	movw	ip, #47908
	mov	r2, #0
	movt	ip, 169
	add	ip, r0, ip
	b	.L1402
.L1401:
	ldr	r1, [r3, #2932]
	cmp	r1, r2
	bls	.L1436
.L1402:
	ldr	r1, [ip, #4]!
	add	r2, r2, #1
	ldrb	r0, [r1, #3]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L1401
	ldr	r0, [r1, #712]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #256
	ldreq	r0, [r1, #28]
	streq	r0, [r1, #720]
	ldr	r1, [r3, #2932]
	cmp	r1, r2
	bhi	.L1402
.L1436:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1437:
	ldr	ip, [r1, #712]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L1396
	ldr	ip, [r1, #20]
	ldr	r4, [r7, #48]
	rsb	r6, r5, ip
	cmp	ip, r4
	strhi	r6, [r1, #24]
	strls	ip, [r1, #24]
	ldr	r1, [lr]
	ldr	ip, [r1, #24]
	str	ip, [r1, #724]
.L1396:
	ldr	r1, [r3, #2928]
	add	r2, r2, #1
	cmp	r1, r2
	bls	.L1400
.L1399:
	ldr	r1, [lr, #4]!
	ldrb	ip, [r1, #3]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1396
	b	.L1437
.L1434:
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
	beq	.L1443
	add	r3, r0, #11075584
	add	r3, r3, #45056
	ldr	lr, [r3, #2920]
	cmp	lr, #0
	beq	.L1443
	ldr	r2, [r3, #2728]
	rsb	r3, r2, r1
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L1445
	movw	ip, #47784
	movt	ip, 169
	add	ip, r0, ip
	b	.L1440
.L1441:
	ldr	r2, [ip, #4]!
	rsb	r0, r2, r1
	cmp	r2, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L1445
.L1440:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L1441
.L1443:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1445:
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
	ldr	r6, .L1453
	mov	lr, #0
	mov	r5, #255
	sub	r7, r6, #16
.L1450:
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
	bne	.L1450
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1454:
	.align	2
.L1453:
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
	beq	.L1486
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1487
	ldr	r3, [fp, #-48]
	ldrb	r3, [r3, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1475
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
	ldr	r10, .L1492
	b	.L1460
.L1490:
	cmp	r4, #0
	beq	.L1488
	cmp	r4, #3
	beq	.L1489
	ldr	r3, [r10, #52]
	mov	r2, #16
	sub	r1, r6, #16
	mov	r0, r6
	blx	r3
.L1468:
	add	r4, r4, #1
	cmp	r4, #7
	bhi	.L1475
.L1474:
	add	r8, r8, #64
	add	r9, r9, #64
	add	r6, r6, #16
	add	r7, r7, #4
	add	r5, r5, #1
.L1460:
	cmp	r4, #5
	ldrsb	r3, [r5]
	bhi	.L1461
	cmp	r3, #0
	beq	.L1490
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L1468
	ldr	r1, .L1492+4
	cmp	r4, #2
	mov	r2, #16
	ldr	r3, [r10, #52]
	add	r0, r1, r2
	add	r4, r4, #1
	movhi	r1, r0
	mov	r0, r6
	blx	r3
	cmp	r4, #7
	bls	.L1474
.L1475:
	mov	r0, #0
.L1457:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1461:
	cmp	r3, #0
	bne	.L1470
	ldr	r3, [fp, #-52]
	mov	r2, #64
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r10, #52]
	bne	.L1491
.L1485:
	ldr	r1, .L1492+8
	cmp	r4, #6
	add	r0, r1, r2
	movne	r1, r0
	mov	r0, r8
	blx	r3
	b	.L1468
.L1470:
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L1468
	ldr	r3, [r10, #52]
	mov	r2, #64
	b	.L1485
.L1491:
	mov	r1, r9
	mov	r0, r8
	blx	r3
	b	.L1468
.L1486:
	movw	r3, #6713
	ldr	r2, .L1492+12
	ldr	r1, .L1492+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1457
.L1487:
	mov	r0, r3
	ldr	r2, .L1492+12
	movw	r3, #6714
	ldr	r1, .L1492+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1457
.L1489:
	ldr	r3, [fp, #-52]
	mov	r2, #16
	ldr	r0, [fp, #-48]
	mov	r4, #4
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	add	r0, r0, #2064
	cmp	r3, #0
	ldr	r3, [r10, #52]
	ldrne	r1, [fp, #-52]
	ldreq	r1, .L1492+20
	addne	r1, r1, #2720
	blx	r3
	b	.L1474
.L1488:
	ldr	r3, [fp, #-52]
	mov	r2, #16
	ldr	r0, [fp, #-56]
	mov	r4, #1
	ldrb	r3, [r3, #27]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r10, #52]
	ldrne	r1, [fp, #-52]
	ldreq	r1, .L1492+4
	addne	r1, r1, #2672
	blx	r3
	b	.L1474
.L1493:
	.align	2
.L1492:
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	add	r4, r0, #11141120
	add	r2, r4, #12288
	add	r3, r4, #16384
	add	r4, r4, #16384
	ldr	r1, .L1497
	ldrb	r5, [r2, #3483]	@ zero_extendqisi2
	mov	r0, #2
	ldr	r3, [r3, #40]
	mov	r2, r5
	ldr	r3, [r3, #220]
	bl	dprint_vfmw
	ldr	ip, [r4, #100]
	cmp	r5, #3
	cmpne	r5, #0
	ldr	r3, [r4, #96]
	addne	r2, r5, #1
	ldr	r1, .L1497+4
	moveq	r2, #1
	str	ip, [sp]
	mov	r0, #22
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1498:
	.align	2
.L1497:
	.word	.LC35
	.word	.LC36
	UNWIND(.fnend)
	.size	MVC_WriteCurrPicYUV, .-MVC_WriteCurrPicYUV
	.align	2
	.global	MVC_WritePicMsg
	.type	MVC_WritePicMsg, %function
MVC_WritePicMsg:
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
	add	r3, r0, #11141120
	add	r6, r3, #16384
	add	r10, r3, #12288
	mov	r4, r0
	str	r3, [fp, #-48]
	ldr	lr, [r10, #3644]
	mov	r0, #2
	ldr	ip, [r6, #116]
	mov	r9, #0
	ldrb	r3, [r10, #3483]	@ zero_extendqisi2
	add	r5, r4, #11075584
	ldr	r2, [r6, #56]
	add	r8, r5, #32768
	ldr	r1, .L1535
	add	r7, r5, #36864
	str	lr, [sp]
	str	ip, [sp, #4]
	bl	dprint_vfmw
	movw	r3, #16368
	movt	r3, 170
	str	r9, [r4, #64]
	ldrd	r0, [r4, r3]
	movw	r3, #17856
	movt	r3, 170
	strd	r0, [r4, r3]
	ldr	r3, [r4, #544]
	ldr	r2, [r6, #56]
	ldr	r0, [r6, #100]
	str	r3, [r6, #2392]
	ldr	r3, [r10, #3608]
	ldr	r1, [r6, #104]
	str	r3, [r6, #2168]
	ldr	r3, [r10, #3612]
	str	r3, [r6, #2172]
	ldr	r3, [r10, #3632]
	str	r3, [r6, #2176]
	ldr	r3, [r10, #3636]
	str	r2, [r6, #1480]
	str	r3, [r6, #2180]
	ldrb	r3, [r10, #3483]	@ zero_extendqisi2
	strb	r3, [r6, #1448]
	ldr	r3, [r4, #236]
	ldrb	r2, [r3, #21]	@ zero_extendqisi2
	str	r0, [r6, #1484]
	str	r1, [r6, #1488]
	str	r2, [r6, #1496]
	ldr	r2, [r3, #3948]
	add	r2, r2, #1
	str	r2, [r6, #1492]
	ldrb	r2, [r8, #1908]	@ zero_extendqisi2
	strb	r2, [r6, #1451]
	ldr	r2, [r7, #1844]
	str	r2, [r6, #1500]
	ldrb	r2, [r7, #1784]	@ zero_extendqisi2
	str	r2, [r6, #1504]
	ldr	r2, [r3, #748]
	ldr	r3, [r6, #40]
	strb	r2, [r6, #1449]
	ldrb	r2, [r7, #1788]	@ zero_extendqisi2
	str	r2, [r6, #1508]
	ldr	r2, [r7, #4060]
	str	r2, [r6, #1512]
	ldr	r2, [r7, #4048]
	str	r2, [r6, #1516]
	ldr	r2, [r7, #4052]
	str	r2, [r6, #1520]
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetLogicFs
	subs	r10, r0, #0
	beq	.L1533
	ldr	r2, [r10, #28]
	ldr	r3, [r10, #32]
	cmp	r2, #0
	beq	.L1503
	cmp	r3, #0
	beq	.L1503
	movw	r3, #18284
	movw	r2, #18156
	movw	r1, #18412
	ldr	r0, [r4, #120]
	movt	r3, 170
	movt	r2, 170
	add	r3, r4, r3
	add	r2, r4, r2
	movt	r1, 170
	add	r1, r4, r1
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r10, #28]
	movw	r2, #18416
	movw	r1, #18544
	movt	r2, 170
	movt	r1, 170
	ldr	r3, [r3, #4]
	add	r2, r4, r2
	add	r1, r4, r1
	add	r5, r5, #45056
	str	r3, [r6, #1756]
	ldr	r0, [r4, #120]
	bl	FSP_GetPmvAddrTab
	ldr	r3, [r6, #116]
	str	r3, [r6, #1764]
	ldr	r3, [r10, #12]
	str	r3, [r6, #2164]
	ldr	r3, [r10, #32]
	ldr	r3, [r3, #8]
	str	r3, [r6, #1760]
	ldr	r3, [r10, #32]
	ldr	r3, [r3, #60]
	str	r3, [r6, #1768]
	ldr	r10, [r5, #3148]
	cmp	r10, #0
	str	r10, [r6, #2384]
	beq	.L1509
	movw	r6, #48008
	movw	lr, #18572
	movw	ip, #48072
	movw	r0, #18636
	movw	r1, #48136
	movw	r2, #18700
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
	mov	r3, r9
.L1508:
	ldr	r9, [r6, #4]!
	add	r3, r3, #1
	cmp	r3, r10
	str	r9, [lr, #4]!
	ldr	r9, [ip, #4]!
	str	r9, [r0, #4]!
	ldr	r9, [r1, #4]!
	str	r9, [r2, #4]!
	bne	.L1508
.L1509:
	ldrb	r3, [r8, #1915]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1534
	ldrb	r1, [r7, #1802]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1510
	movw	ip, #17904
	ldr	r0, .L1535+4
	movt	ip, 170
	add	ip, r4, ip
.L1511:
	and	r3, r1, #3
	add	r1, r1, #1
	cmp	r1, #24
	add	r3, r0, r3, lsl #2
	ldr	r3, [r3, #352]
	bic	r2, r3, #16711680
	ubfx	lr, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, lr, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1511
	movw	r6, #18004
	mov	lr, #0
	movt	r6, 170
	add	r6, r4, r6
.L1512:
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
	bne	.L1512
.L1517:
	cmp	r10, #0
	beq	.L1514
	ldr	r3, [fp, #-48]
	movw	r6, #48012
	movw	r8, #18880
	movt	r6, 169
	movt	r8, 170
	add	r9, r3, #18944
	add	r6, r4, r6
	add	r8, r4, r8
	mov	r7, #0
.L1520:
	ldr	r2, [r6]
	mov	r1, #0
	ldr	r0, [r4, #120]
	add	r7, r7, #1
	bl	FSP_GetStoreType
	adds	r0, r0, #0
	movne	r0, #1
	str	r0, [r8, #4]!
	ldr	r3, [r6], #4
	str	r3, [r9, #4]!
	ldr	r3, [r5, #3148]
	cmp	r3, r7
	bhi	.L1520
.L1514:
	mov	r0, #0
.L1530:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1534:
	ldrb	r1, [r7, #1802]	@ zero_extendqisi2
.L1510:
	cmp	r1, #1
	movw	ip, #17904
	movt	ip, 170
	mov	r0, #0
	add	ip, r4, ip
	beq	.L1515
.L1518:
	movw	r3, #25716
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
	bne	.L1518
	movw	r8, #18004
	mov	r9, #1
	movt	r8, 170
	add	r8, r4, r8
	mov	r7, #0
.L1519:
	mov	r2, r7, lsr #3
	mov	r3, r7, asl #1
	and	ip, r3, #14
	and	r0, r9, #15
	mov	r3, r2, asl #4
	movw	r1, #25740
	add	r0, r3, r0
	mov	r2, r1
	add	r3, r3, ip
	movt	r1, 42
	movt	r2, 42
	add	r1, r0, r1
	add	r2, r3, r2
	add	r7, r7, #1
	ldr	r1, [r4, r1, asl #2]
	cmp	r7, #16
	ldr	r3, [r4, r2, asl #2]
	add	r9, r9, #2
	ubfx	r6, r1, #8, #8
	and	r0, r1, #-16777216
	mov	r2, r1, lsr #16
	uxtb	r1, r1
	mov	ip, r3, lsr #24
	uxtb	lr, r3
	mov	r2, r2, asl #24
	mov	ip, ip, asl #8
	orr	r2, r2, r1, asl #16
	orr	ip, ip, r6, asl #16
	mov	r1, r3, lsr #8
	orr	r2, r2, lr
	and	r1, r1, #65280
	ubfx	r3, r3, #8, #8
	orr	r0, ip, r0
	orr	r2, r2, r1
	orr	r3, r0, r3
	stmia	r8, {r2, r3}
	add	r8, r8, #8
	bne	.L1519
	b	.L1517
.L1515:
	movw	r3, #26550
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
	bne	.L1515
	movw	ip, #18004
	mov	lr, #1
	movt	ip, 170
	add	ip, r4, ip
	mov	r0, #0
.L1516:
	mov	r2, r0, lsr #3
	mov	r3, r0, asl #1
	and	r1, r3, #14
	and	r6, lr, #15
	mov	r3, r2, asl #4
	movw	r2, #26574
	add	r6, r3, r6
	add	r3, r3, r1
	mov	r1, r2
	movt	r2, 42
	movt	r1, 42
	add	r2, r6, r2
	add	r1, r3, r1
	add	r0, r0, #1
	ldr	r2, [r4, r2, asl #2]
	cmp	r0, #16
	ldr	r3, [r4, r1, asl #2]
	add	lr, lr, #2
	ubfx	r9, r2, #8, #8
	and	r1, r2, #-16777216
	mov	r7, r2, lsr #16
	uxtb	r2, r2
	mov	r6, r3, lsr #24
	uxtb	r8, r3
	mov	r7, r7, asl #24
	mov	r6, r6, asl #8
	orr	r7, r7, r2, asl #16
	orr	r6, r6, r9, asl #16
	mov	r2, r3, lsr #8
	orr	r7, r7, r8
	and	r2, r2, #65280
	ubfx	r3, r3, #8, #8
	orr	r1, r6, r1
	orr	r2, r7, r2
	orr	r3, r1, r3
	stmia	ip, {r2, r3}
	add	ip, ip, #8
	bne	.L1516
	b	.L1517
.L1503:
	ldr	r1, .L1535+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1530
.L1533:
	ldr	r3, [r6, #40]
	ldr	r1, .L1535+12
	ldrsb	r2, [r3, #6]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1530
.L1536:
	.align	2
.L1535:
	.word	.LC37
	.word	.LANCHOR1
	.word	.LC39
	.word	.LC38
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
	bcs	.L1541
	add	lr, ip, #3
	add	lr, r6, lr, lsl #2
.L1542:
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
	bne	.L1542
.L1541:
	cmp	r3, #1
	bhi	.L1547
	add	r3, r3, #3
	add	ip, r6, #20
	mov	r2, #0
	add	r3, r6, r3, lsl #2
.L1546:
	str	r2, [r3, #4]!
	cmp	r3, ip
	str	r2, [r3, #-8]
	str	r2, [r3, #8]
	bne	.L1546
.L1547:
	add	r8, r4, #11141120
	ldr	r3, [fp, #-48]
	add	r7, r8, #12288
	add	r5, r4, #11075584
	cmp	r3, #0
	add	r9, r5, #36864
	ldrb	r3, [r7, #3489]	@ zero_extendqisi2
	add	r5, r5, #40960
	strb	r3, [r6, #1]
	ldr	r3, [r9, #1832]
	ldr	r2, [r5, #2680]
	add	r3, r3, #26
	add	r3, r3, r2
	str	r3, [r6, #32]
	bne	.L1643
	add	r2, r8, #16384
	str	r2, [fp, #-52]
	mov	ip, r2
	ldr	r2, [r2, #40]
	str	r3, [r2, #740]
	ldr	r3, [ip, #40]
	ldr	r2, [r6, #32]
	str	r2, [r3, #744]
.L1548:
	ldr	r3, [r5, #2676]
	str	r3, [r6, #36]
	ldr	r3, [r5, #1128]
	str	r3, [r6, #40]
	ldr	r3, [r5, #1124]
	str	r3, [r6, #44]
	ldrb	r3, [r5, #1064]	@ zero_extendqisi2
	strb	r3, [r0, r1]
	ldr	r3, [r5, #1120]
	str	r3, [r6, #48]
	ldrb	r3, [r5, #1070]	@ zero_extendqisi2
	strb	r3, [r6, #2]
	ldr	r3, [r4, #236]
	ldrb	r3, [r3, #22]	@ zero_extendqisi2
	strb	r3, [r6, #3]
	ldr	r3, [r5, #1112]
	str	r3, [r6, #52]
	ldr	r3, [r5, #1116]
	str	r3, [r6, #56]
	ldrb	r3, [r5, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r9, #1828]
	streqb	r3, [r6, #4]
	beq	.L1550
	cmp	r3, #0
	ldreqb	r3, [r9, #1786]	@ zero_extendqisi2
	movne	r3, #0
	strb	r3, [r6, #4]
.L1550:
	ldr	r3, [r9, #1836]
	str	r3, [r6, #60]
	ldr	r3, [r9, #1840]
	str	r3, [r6, #64]
	ldr	r3, [r5, #2688]
	str	r3, [r6, #68]
	ldr	r3, [r5, #2692]
	str	r3, [r6, #72]
	ldr	r3, [r5, #2684]
	str	r3, [r6, #76]
	ldrb	r3, [r5, #1064]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1589
	ldr	ip, [r5, #1112]
	cmp	ip, #0
	beq	.L1592
	ldr	r3, [r4, #256]
	ldr	r2, [r3, #4]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r1, r4, #256
	movne	r3, #0
	bne	.L1557
	b	.L1555
.L1559:
	ldr	r2, [r1, #4]!
	ldr	r2, [r2, #4]
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1555
.L1557:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1559
	mov	r3, #0
	str	r3, [fp, #-56]
.L1554:
	ldr	ip, [r5, #1116]
	cmp	ip, #0
	beq	.L1593
	ldr	r3, [r4, #388]
	ldr	r2, [r3, #4]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r1, r4, #388
	movne	r3, #0
	bne	.L1563
	b	.L1561
.L1565:
	ldr	r2, [r1, #4]!
	ldr	r2, [r2, #4]
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1561
.L1563:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1565
	mov	r3, #0
	str	r3, [fp, #-60]
.L1560:
	ldrb	r2, [r7, #3483]	@ zero_extendqisi2
	ldr	r3, [r5, #1112]
	cmp	r2, #0
	beq	.L1566
	cmp	r3, #0
	beq	.L1581
	mov	r8, #0
	mov	r10, r6
	str	r6, [fp, #-64]
	add	r7, r4, #256
	mov	r6, r5
	mov	r5, r8
	ldr	r8, [fp, #-56]
	b	.L1580
.L1578:
	strb	r2, [r10, #1630]
	ldr	r2, [r7]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r10, #1631]
	ldr	r2, [r7]
	ldr	r2, [r2, #16]
	str	r2, [r10, #1656]
.L1579:
	ldr	r2, [r6, #1112]
	add	r5, r5, #1
	add	r7, r7, #4
	add	r10, r10, #36
	cmp	r2, r5
	bls	.L1644
.L1580:
	ldr	r2, [r7]
	ldr	r0, [r4, #120]
	ldr	r2, [r2, #4]
	ldrsb	r1, [r2, #6]
	bl	FSP_GetLogicFs
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #48]
	str	r2, [r10, #1636]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	strb	r2, [r10, #1625]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r0, r8
	beq	.L1577
	cmp	r0, #0
	ldrne	r2, [r0, #28]
	ldrne	r0, [r2, #4]
.L1577:
	str	r0, [r10, #1640]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #52]
	str	r2, [r10, #1644]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #32]
	str	r2, [r10, #1632]
	ldr	r2, [r7]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r10, #1624]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #712]	@ zero_extendqisi2
	strb	r2, [r10, #1626]
	ldr	r2, [r7]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1578
	strb	r2, [r10, #1628]
	ldr	r2, [r7]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r10, #1629]
	ldr	r2, [r7]
	ldr	r2, [r2, #16]
	str	r2, [r10, #1652]
	b	.L1579
.L1644:
	mov	r5, r6
	ldr	r6, [fp, #-64]
.L1581:
	ldrb	r3, [r5, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1645
.L1569:
	movw	r2, #48208
	add	r3, r6, #3920
	add	r0, r6, #4048
	movt	r2, 169
	add	r3, r3, #4
	add	r2, r4, r2
	add	r0, r0, #4
.L1586:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, r0
	bne	.L1586
	ldrb	r3, [r9, #1786]	@ zero_extendqisi2
	ldr	r2, [fp, #-52]
	cmp	r3, #0
	str	r3, [r2, #1748]
	ldr	r3, [r9, #1828]
	str	r3, [r2, #1752]
	beq	.L1587
	ldrb	r2, [r5, #1064]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1588
.L1587:
	cmp	r3, #1
	beq	.L1646
.L1589:
	ldr	r2, [fp, #-48]
	movw	r3, #37088
	movt	r3, 42
	ldr	r1, [r4, #232]
	add	r3, r2, r3
	mov	r2, #0
	add	r3, r4, r3, lsl #2
	str	r1, [r3, #4]
	str	r2, [r4, #232]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1643:
	add	r2, r8, #16384
	str	r2, [fp, #-52]
	ldr	r2, [r2, #40]
	ldr	lr, [r2, #740]
	ldr	ip, [r2, #744]
	cmp	lr, r3
	movlt	lr, r3
	cmp	ip, r3
	str	lr, [r2, #740]
	movge	ip, r3
	str	ip, [r2, #744]
	b	.L1548
.L1555:
	ldrsb	r1, [r2, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	movweq	r3, #7724
	beq	.L1639
	ldr	r3, [r3, #28]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-56]
	b	.L1554
.L1646:
	ldrb	r3, [r5, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1589
.L1588:
	ldr	r3, [r5, #1132]
	movw	r8, #42096
	movw	r7, #42224
	movw	lr, #42352
	movw	ip, #42864
	movw	r0, #42992
	str	r3, [r6, #80]
	movw	r1, #43120
	ldr	r10, [r5, #1136]
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
.L1590:
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
	ldr	r10, [r5, #1124]
	cmp	r10, r2
	bcs	.L1590
	ldrb	r3, [r5, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1589
	movw	r7, #42480
	movw	lr, #42608
	movw	ip, #42736
	movw	r0, #43248
	movw	r1, #43376
	movw	r2, #43504
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
.L1591:
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
	ldr	r9, [r5, #1128]
	cmp	r9, r3
	bcs	.L1591
	b	.L1589
.L1566:
	cmp	r3, #0
	beq	.L1574
	ldr	r8, [fp, #-56]
	add	r10, r4, #256
	mov	r7, r6
	str	r6, [fp, #-64]
	mov	r6, r5
	mov	r5, r2
.L1573:
	ldr	r2, [r10]
	ldr	r0, [r4, #120]
	ldr	r2, [r2, #4]
	ldrsb	r1, [r2, #6]
	bl	FSP_GetLogicFs
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #48]
	str	r2, [r7, #1636]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	strb	r2, [r7, #1625]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r0, r8
	beq	.L1572
	cmp	r0, #0
	ldrne	r2, [r0, #28]
	ldrne	r0, [r2, #4]
.L1572:
	str	r0, [r7, #1640]
	mov	r3, #0
	ldr	r2, [r10]
	add	r5, r5, #1
	add	r7, r7, #36
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #52]
	str	r2, [r7, #1608]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #32]
	str	r2, [r7, #1596]
	ldr	r2, [r10]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r7, #1591]
	ldr	r2, [r10]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r7, #1590]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #728]
	str	r2, [r7, #1612]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #764]
	str	r2, [r7, #1616]
	ldr	r2, [r10], #4
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #800]
	strb	r3, [r7, #1588]
	str	r2, [r7, #1620]
	ldr	r2, [r6, #1112]
	cmp	r2, r5
	bhi	.L1573
	mov	r5, r6
	ldr	r6, [fp, #-64]
.L1574:
	ldrb	r3, [r5, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1569
	ldr	r3, [r5, #1116]
	cmp	r3, #0
	beq	.L1569
	mov	r8, #0
	mov	r7, r6
	str	r6, [fp, #-56]
	mov	r6, r5
	mov	r5, r8
	ldr	r8, [fp, #-60]
	add	r10, r4, #388
.L1576:
	ldr	r2, [r10]
	ldr	r0, [r4, #120]
	ldr	r2, [r2, #4]
	ldrsb	r1, [r2, #6]
	bl	FSP_GetLogicFs
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #48]
	str	r2, [r7, #2788]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	strb	r2, [r7, #2777]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r0, r8
	beq	.L1575
	cmp	r0, #0
	ldrne	r2, [r0, #28]
	ldrne	r0, [r2, #4]
.L1575:
	str	r0, [r7, #1640]
	mov	r3, #0
	ldr	r2, [r10]
	add	r5, r5, #1
	add	r7, r7, #36
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #52]
	str	r2, [r7, #2760]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #32]
	str	r2, [r7, #2748]
	ldr	r2, [r10]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r7, #2743]
	ldr	r2, [r10]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r7, #2742]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #728]
	str	r2, [r7, #2764]
	ldr	r2, [r10]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #764]
	str	r2, [r7, #2768]
	ldr	r2, [r10], #4
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #800]
	strb	r3, [r7, #2740]
	str	r2, [r7, #2772]
	ldr	r2, [r6, #1116]
	cmp	r2, r5
	bhi	.L1576
.L1638:
	mov	r5, r6
	ldr	r6, [fp, #-56]
	b	.L1569
.L1561:
	ldrsb	r1, [r2, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1647
	ldr	r3, [r3, #28]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-60]
	b	.L1560
.L1645:
	ldr	r3, [r5, #1116]
	cmp	r3, #0
	beq	.L1569
	mov	r3, #0
	mov	r10, r6
	str	r6, [fp, #-56]
	add	r7, r4, #388
	mov	r6, r5
	ldr	r8, [fp, #-60]
	mov	r5, r3
	b	.L1585
.L1583:
	strb	r2, [r10, #2782]
	ldr	r2, [r7]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r10, #2783]
	ldr	r2, [r7]
	ldr	r2, [r2, #16]
	str	r2, [r10, #2808]
.L1584:
	ldr	r2, [r6, #1116]
	add	r5, r5, #1
	add	r7, r7, #4
	add	r10, r10, #36
	cmp	r2, r5
	bls	.L1638
.L1585:
	ldr	r2, [r7]
	ldr	r0, [r4, #120]
	ldr	r2, [r2, #4]
	ldrsb	r1, [r2, #6]
	bl	FSP_GetLogicFs
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #48]
	str	r2, [r10, #2788]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	strb	r2, [r10, #2777]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r0, r8
	beq	.L1582
	cmp	r0, #0
	ldrne	r2, [r0, #28]
	ldrne	r0, [r2, #4]
.L1582:
	str	r0, [r10, #2792]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #52]
	str	r2, [r10, #2796]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldr	r2, [r2, #32]
	str	r2, [r10, #2784]
	ldr	r2, [r7]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r10, #2776]
	ldr	r2, [r7]
	ldr	r2, [r2, #4]
	ldrb	r2, [r2, #712]	@ zero_extendqisi2
	strb	r2, [r10, #2778]
	ldr	r2, [r7]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1583
	strb	r2, [r10, #2780]
	ldr	r2, [r7]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r10, #2781]
	ldr	r2, [r7]
	ldr	r2, [r2, #16]
	str	r2, [r10, #2804]
	b	.L1584
.L1647:
	movw	r3, #7745
.L1639:
	ldr	r2, .L1648
	ldr	r1, .L1648+4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L1592:
	str	ip, [fp, #-56]
	b	.L1554
.L1593:
	str	ip, [fp, #-60]
	b	.L1560
.L1649:
	.align	2
.L1648:
	.word	.LANCHOR0+80
	.word	.LC40
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
	add	r0, r0, #16384
	ldr	r2, [r0, #2392]
	cmp	r2, #0
	beq	.L1653
	mov	r0, #0
.L1652:
	ldr	r3, [r2, #8]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L1652
	ldmfd	sp, {fp, sp, pc}
.L1653:
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
	ldr	r1, .L1666
	mov	r4, r0
	add	r5, r0, #11075584
	bl	mvc_ue_v
	add	r5, r5, #40960
	str	r0, [r5, #1120]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1664
	cmp	r0, #262144
	bcs	.L1665
	ldr	r2, [r4, #12]
	ldr	r3, [r4, #16]
	mul	r3, r3, r2
	sub	r3, r3, #1
	cmp	r0, r3
	bhi	.L1664
	ldr	r1, .L1666+4
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L1666+8
	mov	r2, r0
	mov	r6, r0
	mov	r0, #19
	bl	dprint_vfmw
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1664
	cmp	r6, #9
	bhi	.L1660
	mov	r1, #1
	movw	r3, #297
	mov	r2, r1, asl r6
	and	r3, r3, r2
	cmp	r3, #0
	bne	.L1661
	ands	r0, r2, #660
	bne	.L1662
	tst	r2, #66
	beq	.L1660
	strb	r1, [r5, #1064]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1661:
	strb	r0, [r5, #1064]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1660:
	mov	r2, r6
	ldr	r1, .L1666+12
	mov	r0, #1
	bl	dprint_vfmw
.L1664:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1662:
	mov	r0, r3
	mov	r3, #2
	strb	r3, [r5, #1064]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1665:
	ldr	r1, .L1666+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1667:
	.align	2
.L1666:
	.word	.LC41
	.word	.LC43
	.word	.LC44
	.word	.LC45
	.word	.LC42
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #11075584
	mov	r4, r0
	add	r5, r5, #40960
	ldr	r1, .L1680
	mov	r0, #19
	ldr	r2, [r5, #1080]
	bl	dprint_vfmw
	ldr	r3, [r4, #252]
	ldr	r2, [r5, #1080]
	mov	r1, #2240
	mla	r1, r1, r2, r3
	ldrb	r3, [r1, #19]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1678
	ldrb	r3, [r5, #1076]	@ zero_extendqisi2
	sxtb	r5, r3
	cmn	r5, #1
	beq	.L1679
	cmp	r3, #0
	bne	.L1673
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
	beq	.L1674
	add	r0, r0, #286720
	ldrb	r0, [r0, #957]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1674
.L1672:
	mov	r0, #0
	str	r1, [r4, #244]
	str	r3, [r4, #240]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1679:
	ldr	r0, [r4, #248]
	movw	r3, #3992
	ldr	r2, [r1, #28]
	mla	r3, r3, r2, r0
	ldrb	r0, [r3, #25]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1672
	ldr	r1, .L1680+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1674:
	ldr	r1, .L1680+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1678:
	ldr	r1, .L1680+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1673:
	mov	r2, r5
	ldr	r1, .L1680+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1681:
	.align	2
.L1680:
	.word	.LC46
	.word	.LC48
	.word	.LC49
	.word	.LC47
	.word	.LC34
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r2, r1
	mov	r5, r1
	mov	r4, r0
	ldr	r1, .L1691
	mov	r0, #19
	bl	dprint_vfmw
	ldr	r2, [r4, #252]
	mov	r3, #2240
	mla	r3, r3, r5, r2
	ldrb	r2, [r3, #19]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1688
	ldr	r1, [r4, #36]
	ldr	r2, [r3, #28]
	sub	r3, r1, #1
	cmp	r2, r3
	bhi	.L1689
	add	r3, r4, #11075584
	movw	r1, #1076
	add	r3, r3, #40960
	ldrsb	r5, [r3, r1]
	cmn	r5, #1
	beq	.L1690
.L1687:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1690:
	ldr	r1, [r4, #248]
	movw	r3, #3992
	mla	r3, r3, r2, r1
	ldrb	r3, [r3, #25]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1687
	ldr	r1, .L1691+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1688:
	mov	r2, r5
	ldr	r1, .L1691+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1689:
	ldr	r1, .L1691+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1692:
	.align	2
.L1691:
	.word	.LC50
	.word	.LC53
	.word	.LC51
	.word	.LC52
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
	ldr	r0, [r3, #2728]
	ldr	r2, [r3, #2732]
	ldr	r4, [r3, #1080]
	ldr	r5, [r3, #2736]
	cmp	r2, r4
	cmpeq	r0, r1
	ldr	r2, [r3, #1092]
	ldrb	r4, [r3, #2720]	@ zero_extendqisi2
	ldrb	r0, [r3, #1065]	@ zero_extendqisi2
	movne	r1, #1
	moveq	r1, #0
	cmp	r5, r2
	moveq	r2, r1
	orrne	r2, r1, #1
	cmp	r4, r0
	orrne	r2, r2, #1
	cmp	r4, #0
	cmpne	r0, #0
	beq	.L1695
	ldrb	r0, [r3, #2721]	@ zero_extendqisi2
	ldrb	r1, [r3, #1066]	@ zero_extendqisi2
	cmp	r0, r1
	orrne	r2, r2, #1
.L1695:
	ldrb	r1, [r3, #2723]	@ zero_extendqisi2
	ldrb	r0, [r3, #1072]	@ zero_extendqisi2
	cmp	r1, r0
	moveq	r1, #0
	beq	.L1696
	cmp	r0, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
.L1696:
	ldrb	r0, [r3, #2722]	@ zero_extendqisi2
	ldrb	r4, [r3, #1067]	@ zero_extendqisi2
	cmp	r0, r4
	orrne	r2, r2, #1
	cmp	r4, #5
	cmpeq	r0, #5
	orr	r2, r2, r1
	beq	.L1708
.L1697:
	ldr	r1, [lr, #2900]
	cmp	r1, #0
	bne	.L1698
	add	r1, ip, #36864
	ldr	r0, [r3, #2748]
	ldr	r4, [r3, #2744]
	ldr	r5, [r1, #4032]
	ldr	lr, [r1, #4028]
	cmp	r4, lr
	cmpeq	r0, r5
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
.L1699:
	ldrb	r1, [r3, #1075]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1700
	ldr	r1, [r3, #2764]
	ldrb	r0, [r3, #2724]	@ zero_extendqisi2
	ldrb	r6, [r3, #1073]	@ zero_extendqisi2
	ldr	r5, [r3, #2704]
	ldrb	r4, [r3, #2725]	@ zero_extendqisi2
	cmp	r1, r5
	cmpeq	r0, r6
	ldrb	lr, [r3, #1074]	@ zero_extendqisi2
	movne	r1, #1
	moveq	r1, #0
	cmp	r4, lr
	moveq	r3, r1
	orrne	r3, r1, #1
	orr	r2, r2, r3
.L1700:
	add	r3, ip, #40960
	ldr	r1, .L1709
	mov	r0, #19
	ldr	r4, [r3, #1120]
	cmp	r4, #0
	movne	r4, r2
	orreq	r4, r2, #1
	mov	r2, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1698:
	cmp	r1, #1
	bne	.L1699
	add	r1, ip, #36864
	ldr	r0, [r3, #2756]
	ldr	r4, [r3, #2752]
	ldr	r5, [r1, #4068]
	ldr	lr, [r1, #4064]
	cmp	r4, lr
	cmpeq	r0, r5
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
	b	.L1699
.L1708:
	ldr	r0, [r3, #2740]
	ldr	r1, [r3, #1108]
	cmp	r0, r1
	orrne	r2, r2, #1
	b	.L1697
.L1710:
	.align	2
.L1709:
	.word	.LC54
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r4, r0, #11075584
	ldr	r2, [r0, #240]
	add	r4, r4, #40960
	mov	r5, r0
	mov	r3, #0
	mov	r6, #1
	ldrb	r0, [r4, #1075]	@ zero_extendqisi2
	ldrb	r1, [r4, #1065]	@ zero_extendqisi2
	cmp	r0, r3
	strb	r3, [r4, #12]
	strb	r3, [r4, #13]
	movne	r7, #5
	moveq	r7, #3
	cmp	r1, r3
	ldr	r3, [r2, #2896]
	addne	r3, r3, #5
	addeq	r3, r3, #4
	mov	r6, r6, asl r3
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L1766
.L1765:
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
.L1732:
	adds	r3, r3, #0
	movne	r3, #1
	rsb	r0, r3, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1766:
	ldr	r1, .L1773
	mov	r0, r5
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r4, #12]
	cmp	r0, #0
	beq	.L1722
	ldr	r3, [r4, #1124]
	cmn	r3, #2
	beq	.L1748
	movw	r9, #40972
	mov	r8, #0
	movt	r9, 169
	add	r9, r5, r9
	b	.L1729
.L1723:
	cmp	r0, #2
	beq	.L1767
	sub	r0, r0, #4
	cmp	r0, #1
	bls	.L1768
.L1726:
	ldr	r3, [r4, #1124]
	add	r8, r8, #1
	add	r3, r3, #2
	cmp	r3, r8
	bls	.L1769
.L1729:
	ldr	r1, .L1773+4
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r7, r0
	str	r0, [r9, #4]!
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	bcc	.L1719
	cmp	r3, #0
	bne	.L1719
	cmp	r0, #3
	beq	.L1722
	cmp	r0, #1
	bhi	.L1723
	ldr	r1, .L1773+8
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r6, r0
	str	r0, [r9, #264]
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	bls	.L1725
	cmp	r3, #0
	beq	.L1726
.L1725:
	mov	r2, r0
	ldr	r1, .L1773+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1722:
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1765
	ldr	r1, .L1773+16
	mov	r0, r5
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r4, #13]
	cmp	r0, #0
	beq	.L1765
	ldr	r3, [r4, #1128]
	cmn	r3, #2
	beq	.L1765
	movw	r9, #41104
	mov	r8, #0
	movt	r9, 169
	add	r9, r5, r9
	b	.L1745
.L1744:
	add	r8, r8, #1
	cmp	r8, r3
	bcs	.L1765
.L1745:
	ldr	r1, .L1773+20
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r7, r0
	str	r0, [r9, #4]!
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	bcc	.L1736
	cmp	r3, #0
	bne	.L1736
	cmp	r0, #3
	beq	.L1732
	cmp	r0, #1
	bls	.L1770
	cmp	r0, #2
	beq	.L1771
	sub	r0, r0, #4
	cmp	r0, #1
	bls	.L1772
	ldr	r3, [r4, #1128]
	add	r3, r3, #2
	cmp	r3, r8
	bne	.L1744
.L1746:
	ldr	r1, .L1773+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1770:
	ldr	r1, .L1773+28
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r6, r0
	str	r0, [r9, #264]
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	bls	.L1740
	cmp	r3, #0
	bne	.L1740
.L1741:
	ldr	r3, [r4, #1128]
	add	r3, r3, #2
	cmp	r3, r8
	bne	.L1744
	ldr	r2, [r9]
	cmp	r2, #3
	beq	.L1744
	b	.L1746
.L1767:
	ldr	r1, .L1773+32
	mov	r0, r5
	bl	mvc_ue_v
	str	r0, [r9, #528]
	b	.L1726
.L1771:
	ldr	r1, .L1773+36
	mov	r0, r5
	bl	mvc_ue_v
	str	r0, [r9, #524]
	b	.L1741
.L1768:
	ldr	r1, .L1773+40
	mov	r0, r5
	bl	mvc_ue_v
	str	r0, [r9, #784]
	b	.L1726
.L1772:
	ldr	r1, .L1773+44
	mov	r0, r5
	bl	mvc_ue_v
	str	r0, [r9, #784]
	b	.L1741
.L1719:
	mov	r2, r0
	ldr	r1, .L1773+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1736:
	mov	r2, r0
	ldr	r1, .L1773+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1769:
	cmp	r8, r3
	bne	.L1722
.L1717:
	movw	r2, #26626
	movt	r2, 42
	add	r2, r3, r2
	add	r2, r5, r2, lsl #2
	ldr	r3, [r2, #8]
	cmp	r3, #3
	beq	.L1722
	ldr	r1, .L1773+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1740:
	mov	r2, r0
	ldr	r1, .L1773+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1748:
	mov	r3, #0
	b	.L1717
.L1774:
	.align	2
.L1773:
	.word	.LC55
	.word	.LC56
	.word	.LC58
	.word	.LC59
	.word	.LC63
	.word	.LC64
	.word	.LC70
	.word	.LC66
	.word	.LC60
	.word	.LC68
	.word	.LC61
	.word	.LC69
	.word	.LC57
	.word	.LC65
	.word	.LC62
	.word	.LC67
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
	ldr	r1, .L1805
	add	r6, r0, #11075584
	ldr	r7, [r0, #240]
	mov	r5, r0
	str	r3, [fp, #-48]
	bl	mvc_ue_v
	add	r6, r6, #40960
	mov	r4, #1
	str	r0, [r6, #1132]
	mov	r8, r4, asl r0
	ldr	r9, [r7, #748]
	cmp	r9, #0
	bne	.L1799
.L1776:
	cmp	r0, #7
	bhi	.L1779
	ldr	r3, [r6, #1136]
	cmp	r3, #7
	bhi	.L1779
	ldrb	r2, [r5, #10]	@ zero_extendqisi2
	cmp	r2, #0
	movweq	r10, #42228
	moveq	r4, r2
	movteq	r10, 169
	addeq	r10, r5, r10
	beq	.L1787
	b	.L1778
.L1783:
	ldr	r2, [r7, #748]
	cmp	r2, #0
	bne	.L1800
.L1784:
	str	r2, [r10]
	str	r2, [r10, #768]
	str	r2, [r10, #128]
	str	r2, [r10, #896]
.L1786:
	ldr	r2, [r6, #1124]
	add	r4, r4, #1
	add	r10, r10, #4
	cmp	r2, r4
	bcc	.L1801
.L1787:
	ldr	r1, .L1805+4
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	streq	r8, [r10, #-128]
	streq	r0, [r10, #640]
	beq	.L1783
	ldr	r1, .L1805+8
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1805+12
	str	r0, [r10, #-128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r10, #640]
	ldr	r2, [r7, #748]
	cmp	r2, #0
	beq	.L1784
.L1800:
	ldr	r1, .L1805+16
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1802
	str	r9, [r10]
	str	r0, [r10, #768]
	str	r9, [r10, #128]
	str	r0, [r10, #896]
	b	.L1786
.L1801:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #44]
	cmp	r3, #1
	beq	.L1788
.L1789:
	ldrb	r0, [r5, #10]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L1781:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1802:
	ldr	r1, .L1805+20
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1805+24
	str	r0, [r10]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1805+20
	str	r0, [r10, #768]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1805+24
	str	r0, [r10, #128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r10, #896]
	b	.L1786
.L1799:
	ldr	r1, .L1805+28
	mov	r0, r5
	bl	mvc_ue_v
	mov	r3, r0
	ldr	r0, [r6, #1132]
	mov	r9, r4, asl r3
	str	r3, [r6, #1136]
	b	.L1776
.L1788:
	ldrb	r3, [r6, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1789
	movw	r4, #42612
	mov	r10, #0
	movt	r4, 169
	add	r4, r5, r4
	b	.L1795
.L1791:
	ldr	r3, [r7, #748]
	cmp	r3, #0
	bne	.L1803
.L1792:
	str	r3, [r4]
	str	r3, [r4, #768]
	str	r3, [r4, #128]
	str	r3, [r4, #896]
.L1794:
	ldr	r3, [r6, #1128]
	add	r10, r10, #1
	add	r4, r4, #4
	cmp	r3, r10
	bcc	.L1789
.L1795:
	ldr	r1, .L1805+32
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	streq	r8, [r4, #-128]
	streq	r0, [r4, #640]
	beq	.L1791
	ldr	r1, .L1805+36
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1805+40
	str	r0, [r4, #-128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r4, #640]
	ldr	r3, [r7, #748]
	cmp	r3, #0
	beq	.L1792
.L1803:
	ldr	r1, .L1805+44
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1804
	str	r9, [r4]
	str	r0, [r4, #768]
	str	r9, [r4, #128]
	str	r0, [r4, #896]
	b	.L1794
.L1779:
	ldrb	r2, [r5, #10]	@ zero_extendqisi2
.L1778:
	ldr	r1, .L1805+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1781
.L1804:
	ldr	r1, .L1805+52
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1805+56
	str	r0, [r4]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1805+52
	str	r0, [r4, #768]
	mov	r0, r5
	bl	mvc_se_v
	ldr	r1, .L1805+56
	str	r0, [r4, #128]
	mov	r0, r5
	bl	mvc_se_v
	str	r0, [r4, #896]
	b	.L1794
.L1806:
	.align	2
.L1805:
	.word	.LC71
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC72
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC73
	.word	.LC84
	.word	.LC85
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
	beq	.L1819
	mov	r9, #0
	b	.L1810
.L1841:
	ldr	r1, .L1847
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r5, #2
	beq	.L1839
.L1821:
	cmp	r5, #6
	orreq	r6, r6, #1
	cmp	r6, #0
	bne	.L1824
	cmp	r5, #4
	beq	.L1840
.L1825:
	cmp	r5, #6
	bhi	.L1817
.L1822:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1817
	cmp	r5, #0
	beq	.L1827
.L1826:
	subs	r7, r7, #1
	beq	.L1828
.L1819:
	ldr	r1, .L1847+4
	mov	r0, r4
	bl	mvc_ue_v
	bic	r3, r0, #2
	sub	r6, r0, #3
	clz	r6, r6
	cmp	r3, #1
	mov	r5, r0
	mov	r6, r6, lsr #5
	beq	.L1841
	cmp	r5, #2
	bne	.L1821
.L1839:
	ldr	r1, .L1847+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r6, #0
	beq	.L1822
.L1824:
	ldr	r1, .L1847+12
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r5, #4
	bne	.L1825
.L1840:
	ldr	r1, .L1847+16
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1826
.L1817:
	ldr	r1, .L1847+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1846:
	ldr	r1, .L1847
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r8, #4]
	cmp	r3, #2
	str	r0, [r8, #8]
	beq	.L1842
.L1813:
	cmp	r3, #3
	cmpne	r3, #6
	beq	.L1843
.L1814:
	cmp	r3, #4
	beq	.L1844
.L1815:
	cmp	r3, #6
	bhi	.L1817
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1817
	cmp	r3, #0
	add	r9, r9, #1
	beq	.L1827
	cmp	r9, #100
	beq	.L1845
.L1810:
	ldr	r1, .L1847+4
	mov	r0, r4
	ldrb	r5, [r4, #3]	@ zero_extendqisi2
	bl	mvc_ue_v
	mov	r6, r9, asl #2
	mov	r7, r9, asl #4
	add	r1, r6, r7
	movw	r2, #2004
	movw	r8, #43728
	mla	r2, r2, r5, r1
	movt	r8, 169
	add	r2, r4, r2
	add	r8, r2, r8
	mov	r3, r0
	bic	r0, r0, #2
	cmp	r0, #1
	str	r3, [r8, #4]
	beq	.L1846
	cmp	r3, #2
	bne	.L1813
.L1842:
	ldr	r1, .L1847+8
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r6, r7
	movw	r2, #2004
	movw	r1, #43736
	mla	r3, r2, r5, r3
	movw	r2, #43728
	movt	r1, 169
	movt	r2, 169
	add	r3, r4, r3
	add	r1, r3, r1
	add	r2, r3, r2
	str	r0, [r1, #4]
	ldr	r3, [r2, #4]
	cmp	r3, #3
	cmpne	r3, #6
	bne	.L1814
.L1843:
	ldr	r1, .L1847+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r6, r7
	movw	r2, #2004
	movw	r1, #43736
	mla	r3, r2, r5, r3
	movw	r2, #43728
	movt	r1, 169
	movt	r2, 169
	add	r3, r4, r3
	add	r1, r3, r1
	add	r2, r3, r2
	str	r0, [r1, #8]
	ldr	r3, [r2, #4]
	cmp	r3, #4
	bne	.L1815
.L1844:
	ldr	r1, .L1847+16
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, r7
	movw	r7, #2004
	movw	r2, #43744
	mla	r5, r7, r5, r6
	movw	r3, #43728
	movt	r2, 169
	movt	r3, 169
	add	r5, r4, r5
	add	r2, r5, r2
	add	r3, r5, r3
	str	r0, [r2, #4]
	ldr	r3, [r3, #4]
	b	.L1815
.L1827:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1845:
	ldr	r1, .L1847+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1828:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1848:
	.align	2
.L1847:
	.word	.LC88
	.word	.LC87
	.word	.LC89
	.word	.LC90
	.word	.LC91
	.word	.LC92
	.word	.LC86
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #11075584
	add	r3, r3, #40960
	mov	r4, r0
	ldrb	r7, [r0, #3]	@ zero_extendqisi2
	ldrb	r8, [r3, #1069]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L1850
	clz	r2, r7
	mov	r2, r2, lsr #5
	strb	r2, [r0, #3]
	mov	r6, r2
.L1859:
	ldrb	r3, [r3, #1067]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1870
	ldr	r1, .L1874
	mov	r0, r4
	bl	mvc_u_1
	movw	r2, #2004
	mla	r6, r2, r6, r4
	movw	r5, #43728
	movt	r5, 169
	ldr	r1, .L1874+4
	add	r5, r6, r5
	mov	r3, r0
	uxtb	r2, r0
	strb	r3, [r5, #3]
	mov	r0, #16
	bl	dprint_vfmw
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1853
.L1857:
	mov	r8, #0
.L1867:
	mov	r0, r8
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1850:
	movw	r2, #2004
	movw	r1, #43728
	mla	r2, r2, r7, r0
	movt	r1, 169
	movw	r5, #43728
	mov	r6, r7
	movt	r5, 169
	add	r5, r2, r5
	ldrb	r2, [r2, r1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1859
	ldrb	r3, [r3, #1067]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1871
	ldr	r1, .L1874
	ldrb	r6, [r5, #3]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r6, r0
	bne	.L1872
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1857
	mov	r1, r8
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	MVC_DecMMCO
.L1853:
	mov	r1, #1
	mov	r0, r4
	bl	MVC_DecMMCO
	cmn	r0, #1
	mov	r8, r0
	movne	r3, #1
	movne	r8, #0
	strneb	r3, [r5]
	bne	.L1867
	mov	r3, #0
	ldr	r1, .L1874+8
	strb	r3, [r5]
	mov	r0, #1
	strb	r7, [r4, #3]
	bl	dprint_vfmw
	b	.L1867
.L1871:
	ldr	r1, .L1874+12
	ldrb	r6, [r5, #1]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r6, r0
	bne	.L1873
	mov	r0, r4
	ldr	r1, .L1874+16
	ldrb	r4, [r5, #2]	@ zero_extendqisi2
	bl	mvc_u_1
	cmp	r4, r0
	beq	.L1857
	ldr	r1, .L1874+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1867
.L1870:
	ldr	r1, .L1874+12
	mov	r0, r4
	bl	mvc_u_1
	movw	r2, #2004
	mla	r2, r2, r6, r4
	movw	r5, #43728
	movt	r5, 169
	ldr	r1, .L1874+16
	mov	r8, #0
	add	r5, r2, r5
	strb	r0, [r5, #1]
	mov	r0, r4
	bl	mvc_u_1
	ldrb	r2, [r5, #1]	@ zero_extendqisi2
	ldr	r1, .L1874+24
	strb	r0, [r5, #2]
	mov	r0, #16
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1872:
	ldr	r1, .L1874+28
	mov	r0, #1
	bl	dprint_vfmw
	ldr	ip, [r4, #68]
	ldr	r3, [r4, #100]
	mov	r0, #1
	ldr	r2, [r4, #88]
	mvn	r8, #0
	ldr	r1, .L1874+32
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1867
.L1873:
	ldr	r1, .L1874+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1867
.L1875:
	.align	2
.L1874:
	.word	.LC96
	.word	.LC97
	.word	.LC98
	.word	.LC93
	.word	.LC94
	.word	.LC100
	.word	.LC95
	.word	.LC101
	.word	.LC102
	.word	.LC99
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
	ldr	r1, .L1941
	mov	r4, r0
	bl	mvc_ue_v
	ldr	r3, [r4, #40]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r6, r0
	bhi	.L1877
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1877
	mov	r1, r0
	mov	r0, r4
	bl	MVC_PPSSPSCheckTmpId
	cmp	r0, #0
	bne	.L1932
	add	r7, r4, #11075584
	mov	r0, r4
	add	r5, r7, #40960
	str	r6, [r5, #1080]
	bl	MVC_PPSSPSCheck
	subs	r8, r0, #0
	bne	.L1933
	ldr	r6, [r4, #240]
	mov	r0, r4
	ldr	r2, .L1941+4
	ldr	r9, [r4, #244]
	ldr	r1, [r6, #2896]
	add	r1, r1, #4
	bl	mvc_u_v
	str	r0, [r5, #1092]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1930
	adds	r0, r0, #0
	ldrb	r3, [r5, #1067]	@ zero_extendqisi2
	movne	r0, #1
	cmp	r3, #5
	movne	r0, #0
	cmp	r0, #0
	bne	.L1934
.L1883:
	mov	r3, #0
	strb	r3, [r5, #1065]
	strb	r3, [r5, #1066]
	ldrb	r3, [r6, #20]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1935
	ldr	r2, [r6, #3948]
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	mla	r3, r1, r3, r3
.L1906:
	ldrb	r2, [r6, #21]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1889
	strb	r2, [r5, #1068]
.L1891:
	ldr	r2, [r5, #1120]
	cmp	r2, r3
	bcs	.L1936
.L1892:
	ldrb	r3, [r5, #1067]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1937
.L1894:
	add	r10, r7, #36864
	mov	r3, #0
	str	r3, [r10, #4028]
	str	r3, [r10, #4032]
	ldr	r3, [r6, #2900]
	cmp	r3, #0
	beq	.L1938
.L1898:
	mov	r3, #0
	str	r3, [r10, #4064]
	str	r3, [r10, #4068]
	ldr	r3, [r6, #2900]
	cmp	r3, #1
	beq	.L1939
.L1901:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1930
	ldrb	r3, [r9, #17]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1904
	ldr	r1, .L1941+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L1905
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1904
.L1905:
	ldr	r1, .L1941+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L1941+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L1930
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #102
	blx	r5
.L1930:
	mvn	r8, #0
.L1916:
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1935:
	ldr	r1, .L1941+20
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #1065]
	cmp	r0, #0
	bne	.L1940
	ldr	r2, [r6, #3948]
	ldrb	ip, [r6, #20]	@ zero_extendqisi2
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	cmp	ip, #0
	mla	r3, r1, r3, r3
	bne	.L1908
	mov	r3, r3, asl #1
	b	.L1906
.L1889:
	mov	r2, #1
	strb	r2, [r5, #1068]
.L1909:
	ldr	r2, [r5, #1120]
	cmp	r2, r3, lsr #1
	bcc	.L1892
	ldr	r1, .L1941+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1916
.L1940:
	ldr	r1, .L1941+28
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #1066]
	ldr	r2, [r6, #3948]
	ldrb	r0, [r6, #20]	@ zero_extendqisi2
	ldr	r1, [r6, #3952]
	add	r3, r2, #1
	cmp	r0, #0
	ldrb	r0, [r5, #1065]	@ zero_extendqisi2
	mla	r3, r1, r3, r3
	moveq	r2, #2
	beq	.L1887
.L1908:
	mov	r2, #1
.L1887:
	cmp	r0, #0
	mul	r3, r2, r3
	beq	.L1906
	cmp	r0, #1
	mov	r2, #0
	strb	r2, [r5, #1068]
	bne	.L1891
	b	.L1909
.L1904:
	mov	r0, r4
	add	r7, r7, #40960
	bl	MVC_IsNewPic
	uxtb	r0, r0
	strb	r0, [r7, #1069]
	cmp	r0, #0
	bne	.L1916
	ldr	r2, [r7, #1120]
	ldr	r3, [r7, #2760]
	cmp	r2, r3
	bhi	.L1916
	ldr	r1, .L1941+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1916
.L1938:
	ldr	r1, [r6, #2904]
	mov	r0, r4
	ldr	r2, .L1941+36
	add	r1, r1, #4
	bl	mvc_u_v
	str	r0, [r10, #4028]
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1898
	ldrb	r3, [r5, #1065]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1898
	ldr	r1, .L1941+40
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #4032]
	b	.L1898
.L1939:
	ldrb	r3, [r6, #18]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1901
	ldr	r1, .L1941+44
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #4064]
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1901
	ldrb	r3, [r5, #1065]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1901
	ldr	r1, .L1941+48
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r10, #4068]
	b	.L1901
.L1877:
	mov	r2, r6
	ldr	r1, .L1941+52
	mvn	r8, #0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1937:
	ldr	r1, .L1941+56
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #65536
	str	r0, [r5, #1108]
	bcs	.L1895
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1894
.L1895:
	ldr	r1, .L1941+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1894
.L1932:
	ldr	r1, .L1941+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1916
.L1933:
	ldr	r1, .L1941+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1916
.L1934:
	ldr	r3, [r5, #2704]
	cmp	r3, #0
	bgt	.L1883
	ldr	r1, .L1941+72
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1883
.L1936:
	ldr	r1, .L1941+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1916
.L1942:
	.align	2
.L1941:
	.word	.LC103
	.word	.LC107
	.word	.LC119
	.word	.LC120
	.word	g_event_report
	.word	.LC109
	.word	.LC111
	.word	.LC110
	.word	.LC121
	.word	.LC115
	.word	.LC116
	.word	.LC117
	.word	.LC118
	.word	.LC104
	.word	.LC113
	.word	.LC114
	.word	.LC105
	.word	.LC106
	.word	.LC108
	.word	.LC112
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
	ldr	r2, [r4, #1080]
	cmp	r3, r2
	bcc	.L1944
	ldrb	r7, [r0, #10]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L1944
	bl	MVC_PPSSPSCheck
	cmp	r0, #0
	bne	.L2026
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L2027
.L1948:
	ldr	r2, [r6, #36]
	cmp	r3, #1
	str	r2, [r4, #1124]
	ldr	r2, [r6, #40]
	str	r2, [r4, #1128]
	bls	.L2028
	cmp	r3, #2
	beq	.L1975
.L1959:
	mov	r3, #32
	str	r3, [r4, #1128]
.L1960:
	mov	r0, r5
	bl	mvc_ref_pic_list_reordering
	subs	r8, r0, #0
	bne	.L2029
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1962
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r7, #1
	moveq	r2, r7
	beq	.L1963
.L1962:
	ldr	r3, [r6, #44]
	cmp	r3, #1
	beq	.L2030
.L1979:
	mov	r2, #0
.L1963:
	strb	r7, [r4, #1071]
	mov	r0, #19
	ldr	r1, .L2036
	bl	dprint_vfmw
	ldrb	r2, [r4, #1071]	@ zero_extendqisi2
	mov	r3, #0
	str	r3, [r4, #1132]
	cmp	r2, r3
	str	r3, [r4, #1136]
	bne	.L2031
.L1964:
	ldrb	r3, [r4, #1072]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2032
.L1965:
	mov	r3, #0
	str	r3, [r4, #2676]
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1966
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L2033
.L1966:
	ldr	r1, .L2036+4
	mov	r0, r5
	bl	mvc_se_v
	mov	r3, #0
	str	r3, [r4, #2684]
	str	r3, [r4, #2688]
	str	r3, [r4, #2692]
	str	r0, [r4, #2680]
	ldrb	r3, [r6, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2034
.L1995:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1975:
	mov	r3, #32
	str	r3, [r4, #1124]
	b	.L1959
.L2034:
	ldr	r1, .L2036+8
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r4, #2684]
	bhi	.L1969
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1969
	cmp	r0, #1
	beq	.L1995
	ldr	r1, .L2036+12
	mov	r0, r5
	bl	mvc_se_v
	add	r3, r0, #6
	str	r0, [r4, #2688]
	cmp	r3, #12
	bhi	.L1972
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1972
	ldr	r1, .L2036+16
	mov	r0, r5
	bl	mvc_se_v
	add	r3, r0, #6
	str	r0, [r4, #2692]
	cmp	r3, #12
	bhi	.L1974
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1995
.L1974:
	ldr	r1, .L2036+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L2031:
	mov	r0, r5
	bl	mvc_pred_weight_table
	cmp	r0, #0
	beq	.L1964
	ldr	r1, .L2036+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L2032:
	mov	r0, r5
	bl	mvc_dec_ref_pic_marking
	cmp	r0, #0
	beq	.L1965
	ldr	r1, .L2036+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L2030:
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r7, r3
	moveq	r2, r7
	bne	.L1979
	b	.L1963
.L2027:
	ldr	r1, .L2036+32
	mov	r0, r5
	bl	mvc_u_1
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	strb	r0, [r4, #1070]
	b	.L1948
.L2028:
	ldr	r1, .L2036+36
	mov	r0, r5
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L1950
	ldr	r3, [r4, #1124]
.L1951:
	ldrb	r2, [r4, #1065]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1952
	cmp	r3, #15
	bhi	.L1953
	ldr	r3, [r4, #1128]
	cmp	r3, #15
	bhi	.L2035
.L1954:
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1953
.L1955:
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1975
	cmp	r3, #1
	bne	.L1959
	b	.L1960
.L1944:
	ldr	r1, .L2036+40
	mvn	r8, #0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2033:
	ldr	r1, .L2036+44
	mov	r0, r5
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r4, #2676]
	bhi	.L1967
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1966
.L1967:
	ldr	r1, .L2036+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L1952:
	cmp	r3, #31
	bhi	.L1956
	ldr	r3, [r4, #1128]
	cmp	r3, #31
	bls	.L1957
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1957
.L1956:
	ldr	r1, .L2036+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L1957:
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1955
	b	.L1956
.L2035:
	ldrb	r3, [r4, #1064]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1954
.L1953:
	ldr	r1, .L2036+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L1950:
	ldr	r1, .L2036+60
	mov	r0, r5
	bl	mvc_ue_v
	ldrb	r2, [r4, #1064]	@ zero_extendqisi2
	cmp	r2, #1
	mov	r3, r0
	str	r0, [r4, #1124]
	bne	.L1951
	ldr	r1, .L2036+64
	mov	r0, r5
	bl	mvc_ue_v
	ldr	r3, [r4, #1124]
	str	r0, [r4, #1128]
	b	.L1951
.L1972:
	ldr	r1, .L2036+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L1969:
	ldr	r1, .L2036+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L2026:
	ldr	r1, .L2036+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L2029:
	ldr	r1, .L2036+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1995
.L2037:
	.align	2
.L2036:
	.word	.LC129
	.word	.LC134
	.word	.LC135
	.word	.LC137
	.word	.LC139
	.word	.LC140
	.word	.LC130
	.word	.LC131
	.word	.LC122
	.word	.LC123
	.word	.LC104
	.word	.LC132
	.word	.LC133
	.word	.LC127
	.word	.LC126
	.word	.LC124
	.word	.LC125
	.word	.LC138
	.word	.LC136
	.word	.LC105
	.word	.LC128
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
	ldrb	r1, [r3, #1065]	@ zero_extendqisi2
	ldr	lr, [r3, #1080]
	cmp	r1, #0
	ldr	r5, [r3, #1120]
	str	lr, [r3, #2732]
	ldr	r4, [ip, #744]
	strb	r1, [r3, #2720]
	ldrneb	r1, [r3, #1066]	@ zero_extendqisi2
	ldr	lr, [r3, #1092]
	str	r5, [r3, #2760]
	strneb	r1, [r3, #2721]
	ldrb	r1, [r3, #1067]	@ zero_extendqisi2
	str	lr, [r3, #2736]
	cmp	r1, #5
	ldrb	lr, [r3, #1072]	@ zero_extendqisi2
	strb	r1, [r3, #2722]
	ldreq	r1, [r3, #1108]
	str	r4, [r3, #2728]
	strb	lr, [r3, #2723]
	streq	r1, [r3, #2740]
	ldr	r1, [ip, #2900]
	cmp	r1, #0
	bne	.L2041
	add	r1, r2, #36864
	ldr	lr, [r1, #4028]
	str	lr, [r3, #2744]
	ldr	r1, [r1, #4032]
	str	r1, [r3, #2748]
	ldr	r1, [ip, #2900]
.L2041:
	cmp	r1, #1
	addeq	r2, r2, #36864
	ldreq	r1, [r2, #4064]
	streq	r1, [r3, #2752]
	ldreq	r2, [r2, #4068]
	streq	r2, [r3, #2756]
	ldrb	r2, [r3, #1075]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L2043
	ldr	ip, [r3, #2704]
	ldrb	r1, [r3, #1073]	@ zero_extendqisi2
	ldrb	r2, [r3, #1074]	@ zero_extendqisi2
	str	ip, [r3, #2764]
	strb	r1, [r3, #2724]
	strb	r2, [r3, #2725]
.L2043:
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
	ldrb	r2, [r3, #1064]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L2049
	bcc	.L2050
	cmp	r2, #2
	ldmnefd	sp, {fp, sp, pc}
	ldrb	r3, [r3, #1067]	@ zero_extendqisi2
	add	r0, r0, #11141120
	cmp	r3, #5
	beq	.L2059
.L2052:
	add	r0, r0, #12288
	mov	r3, #0
	strb	r3, [r0, #3493]
	ldmfd	sp, {fp, sp, pc}
.L2050:
	add	r0, r0, #11141120
	add	r3, r0, #12288
	ldrb	r2, [r3, #3492]	@ zero_extendqisi2
	cmp	r2, #2
	movne	r2, #1
	strneb	r2, [r3, #3492]
	b	.L2052
.L2049:
	add	r0, r0, #11141120
	mov	r2, #2
	add	r0, r0, #12288
	mov	r3, #0
	strb	r2, [r0, #3492]
	strb	r3, [r0, #3493]
	ldmfd	sp, {fp, sp, pc}
.L2059:
	add	r0, r0, #12288
	mov	r3, #1
	strb	r3, [r0, #3493]
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #11075584
	add	r3, r3, #36864
	mov	r4, r0
	ldrb	r3, [r3, #1784]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2061
	ldr	r2, [r0, #232]
	ldr	r3, [r2, #64]
	add	r3, r3, #7
	bic	r3, r3, #7
	str	r3, [r2, #64]
	ldr	r2, [r0, #232]
	ldr	r3, [r2, #72]
	sub	r3, r3, #1
	str	r3, [r2, #72]
.L2061:
	ldr	r0, [r4, #232]
	ldrb	r6, [r0]	@ zero_extendqisi2
	cmp	r6, #0
	beq	.L2072
	mov	r3, #0
	mov	r2, r0
	mov	r5, r3
.L2063:
	add	r3, r3, #1
	ldr	r1, [r2, #12]
	cmp	r3, r6
	add	r2, r2, #28
	add	r5, r5, r1
	bne	.L2063
.L2062:
	mov	r7, r6, asl #5
	ldr	ip, [r0, #72]
	sub	r7, r7, r6, asl #2
	ldr	r2, [r0, #64]
	add	r1, r0, r7
	mov	r3, r5
	str	ip, [sp, #4]
	mov	r0, #7
	ldr	ip, [r1, #12]
	ldr	r1, .L2083
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #232]
	mov	r2, r6
	mov	r0, #7
	ldr	r1, .L2083+4
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldr	ip, [r3, #64]
	mov	lr, r6, asl #5
	and	ip, ip, r0
	sub	lr, lr, r6, asl #2
	add	r3, r3, lr
	str	ip, [r3, #24]
	ldr	r3, [r4, #232]
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldr	r8, [r3, #64]
	mov	lr, r6, asl #5
	sub	lr, lr, r6, asl #2
	add	r3, r3, lr
	ldr	ip, [r3, #16]
	add	ip, ip, r8, lsr #3
	rsb	ip, r5, ip
	str	ip, [r3, #28]
	ldr	ip, [r4, #232]
	ldrb	r6, [ip]	@ zero_extendqisi2
	ldr	lr, [ip, #64]
	mov	r3, r6, asl #5
	sub	r3, r3, r6, asl #2
	add	ip, ip, r3
	ldr	r3, [ip, #12]
	add	r3, r5, r3
	rsb	r3, lr, r3, lsl #3
	str	r3, [ip, #20]
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
	ldr	ip, [r4, #232]
	ldr	r2, [ip, #68]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L2082
	ldrb	r5, [ip]	@ zero_extendqisi2
	add	r1, r5, #1
	cmp	r2, r1
	movhi	r2, #1
	movls	r2, #0
	cmp	r1, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L2065
	add	r5, r5, #2
	mov	r6, #0
.L2066:
	sub	r3, r5, #1
	ldr	r1, .L2083+8
	mov	r0, #7
	mov	lr, r3, asl #5
	mov	r2, r3
	sub	r3, lr, r3, asl #2
	add	ip, ip, r3
	str	r6, [ip, #24]
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
	ldr	r7, [ip, #24]
	and	lr, lr, #3
	add	lr, r7, lr, lsl #3
	str	lr, [ip, #24]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	bic	lr, lr, #3
	str	lr, [ip, #28]
	ldr	ip, [r4, #232]
	add	ip, ip, r3
	ldr	r3, [ip, #24]
	ldr	ip, [ip, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r4, #232]
	ldr	r3, [ip, #68]
	cmp	r5, #1
	cmpls	r5, r3
	add	r5, r5, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L2066
	sub	r3, r3, #1
.L2065:
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
	bcs	.L2060
	sxth	r3, r1
	add	r4, r4, #11141120
	add	r4, r4, #16384
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, lr, r3
.L2070:
	ldr	r2, [r3, #28]
	add	r1, r1, #1
	ldr	r0, [r4, #112]
	add	r3, r3, #28
	cmp	r2, r0
	strcc	r2, [r4, #112]
	ldrcc	ip, [lr, #68]
	cmp	ip, r1
	bhi	.L2070
.L2060:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2082:
	ldr	r1, .L2083+12
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L2072:
	mov	r5, r6
	b	.L2062
.L2084:
	.align	2
.L2083:
	.word	.LC141
	.word	.LC142
	.word	.LC144
	.word	.LC143
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
	ble	.L2085
	mov	r3, r7
	mov	r0, #8
	ldr	r9, .L2096
	mov	r5, r0
	mov	r4, #0
	mov	r10, #255
	mov	r7, r1
	mov	r8, r3
	b	.L2090
.L2089:
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
	beq	.L2085
.L2090:
	cmp	r8, #16
	ldreq	r3, .L2096+4
	ldrneb	r3, [r4, r9]	@ zero_extendqisi2
	ldreqb	r3, [r4, r3]	@ zero_extendqisi2
	cmp	r0, #0
	add	r4, r4, #1
	beq	.L2089
	ldr	r1, .L2096+8
	ldr	r0, [fp, #-52]
	str	r3, [fp, #-48]
	bl	mvc_se_v
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
	b	.L2089
.L2085:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2097:
	.align	2
.L2096:
	.word	.LANCHOR0+16
	.word	.LANCHOR0
	.word	.LC145
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
	ldr	r1, .L2156
	mov	r4, r0
	bl	mvc_u_1
	strb	r0, [r5]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2147
	ldr	r1, .L2156+4
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #1]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2147
	ldr	r1, .L2156+8
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	str	r0, [r5, #32]
	bne	.L2102
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2103
.L2102:
	ldr	r1, .L2156+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2156+16
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2147
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #102
	blx	r5
	mvn	r0, #0
.L2100:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2110:
	ldr	r1, .L2156+20
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2156+24
	str	r0, [r5, #60]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #18]
	cmp	r0, #1
	beq	.L2111
.L2129:
	ldr	r1, .L2156+28
	mov	r0, r4
	bl	mvc_se_v
	add	r3, r0, #12
	str	r0, [r5, #56]
	cmp	r3, #24
	bhi	.L2112
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2130
.L2112:
	ldr	r1, .L2156+32
	mov	r0, #1
	bl	dprint_vfmw
.L2147:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2103:
	ldr	r1, .L2156+36
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #31
	str	r0, [r5, #36]
	bhi	.L2104
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2104
	ldr	r1, .L2156+40
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #31
	str	r0, [r5, #40]
	bhi	.L2106
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2106
	ldr	r1, .L2156+44
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #2]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2147
	ldr	r2, .L2156+48
	mov	r1, #2
	mov	r0, r4
	bl	mvc_u_v
	cmp	r0, #2
	str	r0, [r5, #44]
	bhi	.L2148
	ldr	r1, .L2156+52
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2156+56
	str	r0, [r5, #48]
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2156+60
	mov	r0, r4
	bl	mvc_se_v
	ldr	r1, .L2156+64
	str	r0, [r5, #52]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2156+68
	strb	r0, [r5, #3]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2156+72
	strb	r0, [r5, #4]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #17]
	cmp	r0, #0
	bne	.L2149
.L2109:
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
	bcs	.L2110
.L2130:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2149:
	ldr	r1, .L2156+76
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2109
.L2104:
	ldr	r1, .L2156+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2100
.L2106:
	ldr	r1, .L2156+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2100
.L2111:
	sub	r8, fp, #72
	add	r10, r5, #4
	add	r7, r5, #2016
	add	r9, r5, #64
	b	.L2120
.L2153:
	ldr	r3, [r4, #248]
	ldr	ip, [r5, #28]
	mla	ip, lr, ip, r3
	ldrb	r3, [ip, #27]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L2150
	ldr	r3, .L2156+88
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2156+92
	ldr	r3, [r3, #52]
	blx	r3
.L2115:
	add	r6, r6, #1
	add	r7, r7, #16
	cmp	r6, #6
	add	r9, r9, #64
	beq	.L2151
.L2120:
	ldr	r1, .L2156+96
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
	beq	.L2152
	cmp	r6, #0
	cmpne	r6, #3
	mov	r1, r1, lsr #5
	beq	.L2153
	ldr	r3, .L2156+92
	mov	r2, #16
	sub	r1, r7, #16
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2115
.L2151:
	add	r8, r5, #2112
	add	r10, r5, #448
	sub	r7, fp, #76
	add	r9, r5, #11
	mov	r6, #0
.L2128:
	ldr	r2, [r5, #60]
	mov	r3, #0
	cmp	r2, #1
	strne	r3, [r7]
	strneb	r3, [r9]
	beq	.L2154
.L2123:
	ldr	r1, [r4, #248]
	movw	ip, #3992
	ldr	r3, [r5, #28]
	mov	r0, r8
	mov	r2, #64
	mla	r3, ip, r3, r1
	ldrb	r1, [r3, #27]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L2155
	ldr	r1, .L2156+100
	cmp	r6, #0
	ldr	r3, .L2156+92
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L2124:
	add	r6, r6, #1
	add	r8, r8, #64
	cmp	r6, #2
	add	r10, r10, #256
	add	r7, r7, #4
	add	r9, r9, #1
	bne	.L2128
	b	.L2129
.L2152:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r7
	mov	r1, r9
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2115
	ldr	r1, .L2156+88
	mov	r2, #16
	ldr	r3, .L2156+92
	cmp	r6, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r7
	blx	r3
	b	.L2115
.L2150:
	ldr	r3, .L2156+92
	add	r1, r6, #167
	mov	r2, #16
	mov	r0, r7
	add	r1, ip, r1, lsl #4
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2115
.L2148:
	ldr	r1, .L2156+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2100
.L2154:
	ldr	r1, .L2156+108
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
	bne	.L2123
	str	r7, [sp]
	bl	MVC_Scaling_List
	ldr	r3, [r7]
	cmp	r3, #1
	bne	.L2124
	ldr	r1, .L2156+100
	mov	r2, #64
	ldr	r3, .L2156+92
	cmp	r6, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r8
	blx	r3
	b	.L2124
.L2155:
	add	r1, r3, r6, lsl #6
	ldr	r3, .L2156+92
	add	r1, r1, #2768
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2124
.L2157:
	.align	2
.L2156:
	.word	.LC146
	.word	.LC147
	.word	.LC148
	.word	.LC149
	.word	g_event_report
	.word	.LC164
	.word	.LC165
	.word	.LC166
	.word	.LC169
	.word	.LC150
	.word	.LC152
	.word	.LC154
	.word	.LC155
	.word	.LC157
	.word	.LC158
	.word	.LC159
	.word	.LC160
	.word	.LC161
	.word	.LC162
	.word	.LC163
	.word	.LC151
	.word	.LC153
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC167
	.word	.LANCHOR1+32
	.word	.LC156
	.word	.LC168
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
	beq	.L2185
	cmp	r1, #0
	beq	.L2186
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
	beq	.L2162
	mov	ip, ip, asl #1
	adds	r2, ip, #6
	str	r2, [fp, #-60]
	beq	.L2162
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
.L2167:
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
	beq	.L2184
	ldr	r1, [r9]
	ldr	r0, [r8]
	cmp	r1, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r6, #5
	bhi	.L2164
	cmp	r1, #0
	add	r7, ip, #64
	bne	.L2163
	add	r0, ip, #128
	mov	r1, r7
	mov	ip, r5
.L2165:
	ldr	r4, [r1], #4
	ldr	lr, [ip], #4
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r1, r0
	bne	.L2165
.L2163:
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
	bne	.L2167
	ldr	r7, [fp, #-64]
	ldr	r1, [fp, #-68]
.L2162:
	ldr	r0, [r7, #56]
	ldr	r2, [r1, #56]
	cmp	r0, r2
	movne	r0, #0
	andeq	r0, r3, #1
	eor	r0, r0, #1
	rsb	r0, r0, #0
.L2160:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2164:
	cmp	r1, #0
	bne	.L2184
	ldr	r1, [fp, #-48]
	mov	lr, r10
.L2166:
	ldr	r4, [r1, #4]!
	ldr	r0, [lr, #4]!
	cmp	r4, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r1
	bne	.L2166
.L2184:
	add	r7, ip, #64
	b	.L2163
.L2186:
	mov	r0, r1
	movw	r3, #9880
	ldr	r2, .L2187
	ldr	r1, .L2187+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2160
.L2185:
	movw	r3, #9879
	ldr	r2, .L2187
	ldr	r1, .L2187+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2160
.L2188:
	.align	2
.L2187:
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
	ldr	r1, .L2204
	mov	r4, r0
	bl	mvc_ue_v
	ldr	r3, [r4, #40]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r5, r0
	bls	.L2190
	mov	r2, r0
	ldr	r1, .L2204+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #40]
	sub	r3, r2, #1
	cmp	r5, r3
	bls	.L2197
	ldr	r3, .L2204+8
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L2197
	str	r2, [fp, #-40]
	mov	r3, #8
	str	r5, [fp, #-44]
	sub	r2, fp, #44
	ldr	r0, [r4, #120]
	mov	r1, #110
	blx	r6
	mvn	r0, #0
.L2191:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2190:
	ldr	r1, .L2204+12
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r4, #36]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	ip, r0
	bhi	.L2201
	mov	r8, #2240
	ldr	r3, [r4, #252]
	mul	r6, r8, r5
	add	r3, r3, r6
	ldrb	r7, [r3, #19]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L2193
	ldr	r7, .L2204+16
	mov	r0, r4
	mov	r1, r7
	str	r5, [r7, #24]
	str	ip, [r7, #28]
	bl	MVC_ProcessPPS
	subs	r5, r0, #0
	bne	.L2202
	ldr	r1, [r4, #252]
	mov	r0, r7
	add	r1, r1, r6
	bl	MVC_PPSEqual
	cmp	r0, #0
	beq	.L2191
	ldr	ip, .L2204+20
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
	b	.L2191
.L2193:
	str	r5, [r3, #24]
	mov	r0, r4
	ldr	r3, [r4, #252]
	add	r3, r3, r6
	str	ip, [r3, #28]
	ldr	r1, [r4, #252]
	add	r1, r1, r6
	bl	MVC_ProcessPPS
	cmp	r0, #0
	bne	.L2203
	ldr	r3, [r4, #252]
	mov	r2, #1
	add	r3, r3, r6
	strb	r2, [r3, #20]
	ldr	r3, [r4, #252]
	add	r6, r3, r6
	strb	r2, [r6, #19]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2197:
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2201:
	ldr	r1, .L2204+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2191
.L2202:
	movw	r2, #9644
	ldr	r1, .L2204+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2191
.L2203:
	movw	r2, #9663
	ldr	r1, .L2204+28
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #252]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r6
	strb	r2, [r3, #20]
	ldr	r3, [r4, #252]
	add	r6, r3, r6
	strb	r7, [r6, #19]
	b	.L2191
.L2205:
	.align	2
.L2204:
	.word	.LC170
	.word	.LC171
	.word	g_event_report
	.word	.LC172
	.word	.LANCHOR2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC173
	.word	.LC174
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
	ldr	r1, .L2254
	mov	r4, r0
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	streqb	r0, [r5, #15]
	bne	.L2248
.L2208:
	ldr	r1, .L2254+4
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	bne	.L2249
.L2209:
	ldr	r1, .L2254+8
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #3]
	cmp	r0, #0
	moveq	r3, #5
	streq	r3, [r5, #28]
	bne	.L2250
.L2211:
	ldr	r1, .L2254+12
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #6]
	cmp	r0, #0
	bne	.L2251
.L2212:
	ldr	r1, .L2254+16
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #8]
	cmp	r0, #0
	bne	.L2252
.L2214:
	ldr	r1, .L2254+20
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #7]
	cmp	r0, #0
	beq	.L2216
	ldr	r1, .L2254+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r2, .L2254+28
	mov	r1, #4
	str	r0, [r5, #96]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+32
	mov	r1, #4
	strb	r0, [r5, #92]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [r5, #96]
	cmp	r3, #31
	strb	r0, [r5, #93]
	bhi	.L2219
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2219
	add	r7, r5, #96
	add	r8, r5, #59
.L2220:
	ldr	r1, .L2254+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #96]
	cmp	r3, r6
	bcs	.L2220
	ldr	r2, .L2254+48
	mov	r1, #5
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+52
	mov	r1, #5
	str	r0, [r5, #356]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+56
	mov	r1, #5
	str	r0, [r5, #360]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+60
	mov	r1, #5
	str	r0, [r5, #364]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #368]
.L2216:
	ldr	r1, .L2254+64
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #10]
	cmp	r0, #0
	bne	.L2253
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2225
.L2224:
	ldr	r1, .L2254+68
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2254+72
	strb	r0, [r5, #11]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #12]
	cmp	r0, #0
	bne	.L2226
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
.L2227:
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2253:
	ldr	r1, .L2254+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r2, .L2254+28
	mov	r1, #4
	str	r0, [r5, #408]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+32
	mov	r1, #4
	strb	r0, [r5, #404]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [r5, #408]
	cmp	r3, #31
	strb	r0, [r5, #405]
	bhi	.L2219
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2219
	add	r8, r5, #368
	add	r7, r5, #408
	add	r8, r8, #3
.L2222:
	ldr	r1, .L2254+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #408]
	cmp	r3, r6
	bcs	.L2222
	ldr	r2, .L2254+48
	mov	r1, #5
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+52
	mov	r1, #5
	str	r0, [r5, #668]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+56
	mov	r1, #5
	str	r0, [r5, #672]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+60
	mov	r1, #5
	str	r0, [r5, #676]
	mov	r0, r4
	bl	mvc_u_v
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r5, #680]
	bne	.L2225
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2224
.L2225:
	ldr	r1, .L2254+76
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #14]
	b	.L2224
.L2252:
	ldr	r2, .L2254+80
	mov	r1, #32
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+84
	mov	r1, #32
	str	r0, [r5, #52]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2254+88
	str	r0, [r5, #56]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, [r5, #52]
	cmp	r1, #0
	strb	r0, [r5, #9]
	beq	.L2214
	ldr	r3, [r5, #56]
	mov	r0, #1000
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	mov	r0, r0, lsr #1
	str	r0, [r4, #56]
	b	.L2214
.L2251:
	ldr	r1, .L2254+92
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+96
	str	r0, [r5, #44]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #48]
	b	.L2212
.L2250:
	ldr	r2, .L2254+100
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2254+104
	str	r0, [r5, #28]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2254+108
	strb	r0, [r5, #4]
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #5]
	cmp	r0, #0
	beq	.L2211
	ldr	r2, .L2254+112
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+116
	mov	r1, #8
	str	r0, [r5, #32]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+120
	mov	r1, #8
	str	r0, [r5, #36]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #40]
	b	.L2211
.L2249:
	ldr	r1, .L2254+124
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #2]
	b	.L2209
.L2248:
	ldr	r2, .L2254+128
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	uxtb	r0, r0
	strb	r0, [r5, #15]
	cmp	r0, #255
	bne	.L2208
	ldr	r2, .L2254+132
	mov	r1, #16
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2254+136
	mov	r1, #16
	str	r0, [r5, #16]
	mov	r0, r4
	bl	mvc_u_v
	str	r0, [r5, #20]
	b	.L2208
.L2226:
	ldr	r1, .L2254+140
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2254+144
	strb	r0, [r5, #13]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+148
	str	r0, [r5, #684]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+152
	str	r0, [r5, #688]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+156
	str	r0, [r5, #696]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+160
	str	r0, [r5, #692]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2254+164
	str	r0, [r5, #700]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #704]
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L2227
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2219:
	ldr	r1, .L2254+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2255:
	.align	2
.L2254:
	.word	.LC175
	.word	.LC179
	.word	.LC181
	.word	.LC188
	.word	.LC191
	.word	.LC195
	.word	.LC196
	.word	.LC197
	.word	.LC198
	.word	.LC200
	.word	.LC201
	.word	.LC202
	.word	.LC203
	.word	.LC204
	.word	.LC205
	.word	.LC206
	.word	.LC207
	.word	.LC209
	.word	.LC210
	.word	.LC208
	.word	.LC192
	.word	.LC193
	.word	.LC194
	.word	.LC189
	.word	.LC190
	.word	.LC182
	.word	.LC183
	.word	.LC184
	.word	.LC185
	.word	.LC186
	.word	.LC187
	.word	.LC180
	.word	.LC176
	.word	.LC177
	.word	.LC178
	.word	.LC211
	.word	.LC212
	.word	.LC213
	.word	.LC214
	.word	.LC215
	.word	.LC216
	.word	.LC217
	.word	.LC199
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
	beq	.L2288
	cmp	r1, #0
	beq	.L2289
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
	beq	.L2260
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
.L2264:
	ldr	r1, [fp, #-48]
	ldrsb	r0, [r6, #1]!
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-48]
	sxtb	r1, r2
	cmp	r0, r1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, #0
	beq	.L2261
	cmp	r7, #5
	bhi	.L2271
	add	r2, r8, #748
	add	lr, r8, #812
	mov	r1, r9
.L2263:
	ldr	ip, [r2, #4]!
	ldr	r0, [r1, #4]!
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, lr
	bne	.L2263
.L2261:
	add	r7, r7, #1
	add	r10, r10, #256
	cmp	r7, #8
	add	r5, r5, #256
	add	r4, r4, #256
	add	r8, r8, #64
	add	r9, r9, #64
	bne	.L2264
	ldr	r6, [fp, #-52]
	ldr	r1, [fp, #-56]
.L2260:
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
	beq	.L2266
	cmp	ip, #1
	bne	.L2265
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
	beq	.L2265
	add	ip, r6, #2912
	add	r0, r1, #2912
	add	ip, ip, #4
	add	r0, r0, #4
	mov	r2, #0
.L2268:
	ldr	r4, [ip, #4]!
	add	r2, r2, #1
	ldr	lr, [r0, #4]!
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r5
	bne	.L2268
.L2265:
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
	bne	.L2269
	ldrb	r0, [r6, #21]	@ zero_extendqisi2
	ldrb	r2, [r1, #21]	@ zero_extendqisi2
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L2269:
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
	bne	.L2290
.L2270:
	ldrb	r2, [r6, #24]	@ zero_extendqisi2
	ldr	r0, [r6, #52]
	ldr	ip, [r1, #52]
	ldrb	r1, [r1, #24]	@ zero_extendqisi2
	cmp	r0, ip
	cmpeq	r2, r1
	moveq	r2, #1
	movne	r2, #0
	tst	r3, r2
	mvneq	r0, #0
	movne	r0, #0
.L2258:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2290:
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
	b	.L2270
.L2271:
	mov	r1, r5
	mov	r2, r10
.L2262:
	ldr	ip, [r2, #4]!
	ldr	r0, [r1, #4]!
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r4
	bne	.L2262
	b	.L2261
.L2266:
	ldr	r0, [r6, #2904]
	ldr	r2, [r1, #2904]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
	b	.L2265
.L2289:
	mov	r0, r1
	movw	r3, #10123
	ldr	r2, .L2291
	ldr	r1, .L2291+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2258
.L2288:
	movw	r3, #10122
	ldr	r2, .L2291
	ldr	r1, .L2291+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2258
.L2292:
	.align	2
.L2291:
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
	subs	r4, r0, #0
	beq	.L2316
	subs	ip, r4, #255
	movne	ip, #1
	cmp	r4, #16
	movle	lr, #0
	andgt	lr, ip, #1
	cmp	lr, #0
	bne	.L2305
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r0, #1
	movne	r0, #0
	cmp	r4, #255
	movne	r0, #0
	andeq	r0, r0, #1
	cmp	r0, #0
	bne	.L2306
	cmp	r4, #1
	moveq	r2, r0
	moveq	r4, #5
	beq	.L2294
	cmp	ip, #0
	ldrne	r0, .L2317
	addne	r4, r0, r4, lsl #3
	ldrne	r1, [r4, #100]
	ldrne	r2, [r4, #104]
	mul	r0, r3, r1
	ldr	r3, [fp, #4]
	mul	r1, r3, r2
	mov	r0, r0, asl #10
	bl	__aeabi_idiv
	movw	r3, #2405
	movw	r1, #2262
	cmp	r0, r3
	mov	r2, r0
	rsble	r3, r0, #2400
	subgt	r3, r0, #2400
	addle	r3, r3, #6
	subgt	r3, r3, #6
	cmp	r0, r1
	bgt	.L2298
	rsb	r1, r0, #2256
	add	r1, r1, #7
	cmp	r3, r1
	bge	.L2299
.L2309:
	mov	r4, #4
	b	.L2294
.L2305:
	mov	r4, #0
.L2316:
	mov	r2, r4
.L2294:
	mov	r3, r4
	ldr	r1, .L2317+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2298:
	sub	r1, r0, #2256
	sub	r1, r1, #7
	cmp	r3, r1
	blt	.L2309
.L2299:
	movw	r3, #1819
	cmp	r2, r3
	bgt	.L2300
	rsb	r3, r2, #1808
	add	r3, r3, #12
	cmp	r1, r3
	blt	.L2311
.L2301:
	movw	r1, #1364
	cmp	r2, r1
	rsble	r4, r2, #1360
	subgt	r4, r2, #1360
	addle	r4, r4, #5
	subgt	r4, r4, #5
	cmp	r3, r4
	movlt	r4, #2
	movge	r4, #1
	b	.L2294
.L2306:
	mov	r4, lr
	mov	r2, lr
	b	.L2294
.L2300:
	sub	r3, r2, #1808
	sub	r3, r3, #12
	cmp	r1, r3
	bge	.L2301
.L2311:
	mov	r4, #3
	b	.L2294
.L2318:
	.align	2
.L2317:
	.word	.LANCHOR0
	.word	.LC218
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
	beq	.L2432
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
	bne	.L2433
.L2332:
	ldr	r1, .L2447
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #12
	str	r0, [r5, #2896]
	bhi	.L2345
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2345
	ldr	r1, .L2447+4
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #2
	str	r0, [r5, #2900]
	bhi	.L2347
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2347
	cmp	r0, #0
	beq	.L2434
	cmp	r0, #1
	beq	.L2435
.L2353:
	ldr	r1, .L2447+8
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #3944]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	ldr	r1, .L2447+12
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #19]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	ldr	r1, .L2447+16
	mov	r0, r4
	bl	mvc_ue_v
	movw	r7, #509
	sub	r3, r0, #1
	str	r0, [r5, #3948]
	cmp	r3, r7
	bhi	.L2358
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2358
	ldr	r1, .L2447+20
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #3952]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	ldr	r1, .L2447+24
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #20]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	cmp	r0, #0
	bne	.L2436
	ldr	r1, .L2447+28
	mov	r0, r4
	bl	mvc_u_1
	ldr	r6, [r5, #3952]
	add	r6, r6, #1
	cmp	r6, #255
	strb	r0, [r5, #21]
	bhi	.L2391
	ldr	r3, [r5, #3948]
	add	r3, r3, #1
	cmp	r6, #1
	cmphi	r3, #3
	movhi	r8, #2
	bhi	.L2362
.L2391:
	ldr	r1, .L2447+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2433:
	ldr	r1, .L2447+36
	bl	mvc_ue_v
	cmp	r0, #1
	str	r0, [r5, #748]
	bhi	.L2323
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2323
	ldr	r1, .L2447+40
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L2325
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2326
.L2325:
	ldr	r1, .L2447+44
	mov	r0, #1
	bl	dprint_vfmw
.L2326:
	ldr	r1, .L2447+48
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #0
	bne	.L2327
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2328
.L2327:
	ldr	r1, .L2447+52
	mov	r0, #1
	bl	dprint_vfmw
.L2328:
	ldr	r1, .L2447+56
	mov	r0, r4
	bl	mvc_u_1
	cmp	r0, #0
	bne	.L2329
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2329
	ldr	r1, .L2447+60
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #27]
	cmp	r0, #1
	bne	.L2332
	sub	r8, fp, #72
	add	r10, r5, #5
	add	r7, r5, #2672
	add	r9, r5, #752
	b	.L2338
.L2439:
	ldr	r3, .L2447+64
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2447+68
	ldr	r3, [r3, #52]
	blx	r3
.L2334:
	add	r6, r6, #1
	add	r7, r7, #16
	cmp	r6, #6
	add	r9, r9, #64
	beq	.L2437
.L2338:
	ldr	r1, .L2447+72
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
	beq	.L2438
	cmp	r6, #0
	cmpne	r6, #3
	beq	.L2439
	ldr	r3, .L2447+68
	mov	r2, #16
	sub	r1, r7, #16
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2334
.L2389:
	cmp	r1, r9
	cmpcs	r0, r6
	bcs	.L2388
	ldr	r3, .L2447+76
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2430
	strh	r1, [fp, #-72]	@ movhi
	mov	r3, #8
	strh	r0, [fp, #-70]	@ movhi
	sub	r2, fp, #76
	strh	r9, [fp, #-76]	@ movhi
	mov	r1, #107
	strh	r6, [fp, #-74]	@ movhi
	ldr	r0, [r4, #120]
	blx	r5
.L2430:
	mvn	r0, #0
.L2423:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2436:
	ldr	r6, [r5, #3952]
	strb	r3, [r5, #21]
	sub	r3, r6, #1
	cmp	r3, r7
	bhi	.L2391
	ldr	r3, [r5, #3948]
	mov	r8, #1
	add	r6, r6, #1
	add	r3, r3, r8
.L2362:
	mul	r6, r6, r8
	mov	r9, r3, asl #4
	mov	r6, r6, asl #4
	mul	r1, r9, r6
	add	r1, r1, r1, lsr #1
	cmp	r1, #100663296
	bhi	.L2440
	ldr	r2, [r5, #740]
	sub	r3, r2, #10
	cmp	r3, #31
	ldrls	pc, [pc, r3, asl #2]
	b	.L2364
.L2366:
	.word	.L2365
	.word	.L2367
	.word	.L2398
	.word	.L2398
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2398
	.word	.L2369
	.word	.L2371
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2371
	.word	.L2372
	.word	.L2373
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2364
	.word	.L2375
	.word	.L2375
.L2434:
	ldr	r1, .L2447+80
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #12
	str	r0, [r5, #2904]
	bhi	.L2350
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2353
.L2350:
	ldr	r1, .L2447+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2398:
	mov	r0, #60416
	movt	r0, 13
.L2368:
	bl	__aeabi_uidiv
	ldr	r1, .L2447+88
	cmp	r0, #16
	movcc	r7, r0
	movcs	r7, #16
	mov	r2, r7
	mov	r0, #21
	bl	dprint_vfmw
	ldr	r2, [r5, #3944]
	cmp	r2, r7
	bhi	.L2376
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2377
.L2376:
	mov	r3, r7
	ldr	r1, .L2447+92
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r5, #3944]
	cmp	r3, #16
	bhi	.L2427
	cmp	r7, r3
	movcc	r7, r3
.L2427:
	str	r7, [r5, #3944]
.L2377:
	ldr	r1, .L2447+96
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #22]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	ldr	r1, .L2447+100
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r0, r0
	strb	r0, [r5, #23]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	cmp	r0, #0
	bne	.L2441
.L2379:
	mov	r2, r9, lsr #1
	mov	r3, r6, lsr #1
	str	r9, [r5, #3976]
	str	r6, [r5, #3980]
	str	r2, [r5, #3984]
	str	r3, [r5, #3988]
.L2381:
	ldr	r1, .L2447+104
	mov	r0, r4
	bl	mvc_u_1
	uxtb	r3, r0
	strb	r3, [r5, #24]
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2430
	cmp	r3, #0
	mov	r2, #2
	str	r2, [r5, #68]
	bne	.L2442
	mov	r0, r3
	strb	r3, [r5, #43]
	mov	r3, #5
	str	r3, [r5, #56]
.L2384:
	ldr	r2, [r5, #48]
	mov	r3, r9
	ldr	r1, [r5, #44]
	str	r6, [sp]
	bl	MVC_GetDar
	ldr	r3, [r5, #3944]
	cmp	r3, #0
	str	r0, [r5, #52]
	beq	.L2387
	cmp	r7, r3
	movcs	r7, r3
.L2387:
	ldr	r3, [r4, #224]
	cmp	r7, #16
	movcs	r7, #16
	ldr	r2, [r3, #28]
	cmp	r2, #25
	beq	.L2443
.L2388:
	cmp	r6, #1920
	bcc	.L2390
	cmp	r7, #4
	movcs	r7, #4
.L2390:
	add	r7, r7, #1
	mov	r0, #0
	str	r7, [r5, #3972]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2375:
	mov	r0, #12582912
	b	.L2368
.L2371:
	mov	r0, #30208
	movt	r0, 47
	b	.L2368
.L2437:
	sub	r8, fp, #88
	add	r10, r5, #11
	add	r7, r5, #2768
	add	r9, r5, #1136
	mov	r6, #0
.L2343:
	ldr	r1, .L2447+72
	mov	r0, r4
	bl	mvc_u_1
	mov	r2, #64
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r7
	str	r3, [r8, #4]!
	strb	r3, [r10, #1]!
	beq	.L2444
	ldr	r1, .L2447+108
	cmp	r6, #0
	ldr	r3, .L2447+68
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L2340:
	add	r6, r6, #1
	add	r7, r7, #64
	cmp	r6, #2
	add	r9, r9, #256
	bne	.L2343
	b	.L2332
.L2438:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r7
	mov	r1, r9
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2334
	ldr	r1, .L2447+64
	mov	r2, #16
	ldr	r3, .L2447+68
	cmp	r6, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r7
	blx	r3
	b	.L2334
.L2323:
	ldr	r1, .L2447+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2345:
	ldr	r1, .L2447+116
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2441:
	ldr	r1, .L2447+120
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2447+124
	str	r0, [r5, #3956]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2447+128
	str	r0, [r5, #3960]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2447+132
	str	r0, [r5, #3964]
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r3, [r5, #3964]
	ldr	r2, [r5, #3956]
	mov	r1, r8, asl #1
	ldr	ip, [r5, #3960]
	mov	r3, r3, asl #1
	mov	r2, r2, asl #1
	mul	r8, r8, r3
	rsb	r3, r2, r9
	sub	r3, r3, ip, asl #1
	rsb	ip, r8, r6
	str	r0, [r5, #3968]
	mls	r0, r0, r1, ip
	cmp	r3, #0
	cmpgt	r0, #0
	ble	.L2379
	add	r2, r2, r3, lsr #1
	add	r8, r8, r0, lsr #1
	str	r2, [r5, #3984]
	str	r8, [r5, #3988]
	str	r3, [r5, #3976]
	str	r0, [r5, #3980]
	b	.L2381
.L2442:
	add	r1, r5, #28
	mov	r0, r4
	bl	mvc_vui_parameters
	cmp	r0, #0
	bne	.L2429
	ldrb	r3, [r5, #40]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2429
	ldr	r2, [r5, #732]
	clz	r3, r2
	mov	r3, r3, lsr #5
	cmp	r7, r2
	orrcc	r3, r3, #1
	cmp	r3, #0
	bne	.L2445
	ldr	r3, [r5, #3944]
	ldrb	r0, [r5, #43]	@ zero_extendqisi2
	cmp	r2, r3
	movcs	r7, r2
	movcc	r7, r3
	b	.L2384
.L2445:
	mov	r3, r7
	ldr	r1, .L2447+136
	mov	r0, #1
	bl	dprint_vfmw
.L2429:
	ldrb	r0, [r5, #43]	@ zero_extendqisi2
	b	.L2384
.L2443:
	ldr	r2, [r3, #732]
	cmp	r2, #0
	bne	.L2388
	ldr	r2, [r3, #716]
	ldr	r1, [r3, #692]
	cmp	r7, r2
	ldr	r0, [r3, #696]
	bls	.L2389
	ldr	r3, .L2447+76
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2430
	str	r2, [fp, #-72]
	mov	r3, #8
	str	r7, [fp, #-76]
	sub	r2, fp, #76
	ldr	r0, [r4, #120]
	mov	r1, #106
	blx	r5
	mvn	r0, #0
	b	.L2423
.L2329:
	ldr	r1, .L2447+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2435:
	ldr	r1, .L2447+144
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r5, #18]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	ldr	r1, .L2447+148
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r5, #2908]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	ldr	r1, .L2447+152
	mov	r0, r4
	bl	mvc_se_v
	str	r0, [r5, #2912]
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2430
	ldr	r1, .L2447+156
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #255
	str	r0, [r5, #2916]
	bhi	.L2355
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2355
	cmp	r0, #0
	addne	r7, r5, #2912
	addne	r7, r7, #4
	bne	.L2357
	b	.L2353
.L2446:
	ldr	r3, [r5, #2916]
	cmp	r3, r6
	bls	.L2353
.L2357:
	ldr	r1, .L2447+160
	mov	r0, r4
	bl	mvc_se_v
	add	r6, r6, #1
	str	r0, [r7, #4]!
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2446
	b	.L2430
.L2358:
	mov	r2, r0
	ldr	r1, .L2447+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2372:
	mov	r0, #30720
	movt	r0, 105
	b	.L2368
.L2369:
	mov	r0, #55296
	movt	r0, 27
	b	.L2368
.L2373:
	mov	r0, #7864320
	b	.L2368
.L2367:
	mov	r0, #17920
	movt	r0, 5
	b	.L2368
.L2365:
	mov	r0, #20992
	movt	r0, 2
	b	.L2368
.L2364:
	ldr	r1, .L2447+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2355:
	ldr	r1, .L2447+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2444:
	mov	r3, r2
	str	r8, [sp]
	mov	r2, r7
	mov	r1, r9
	mov	r0, r4
	bl	MVC_Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L2340
	ldr	r1, .L2447+108
	mov	r2, #64
	ldr	r3, .L2447+68
	cmp	r6, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r7
	blx	r3
	b	.L2340
.L2347:
	ldr	r1, .L2447+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2440:
	ldr	r1, .L2447+180
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2432:
	mov	r0, r5
	movw	r3, #10311
	ldr	r2, .L2447+184
	ldr	r1, .L2447+188
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2423
.L2448:
	.align	2
.L2447:
	.word	.LC228
	.word	.LC230
	.word	.LC233
	.word	.LC241
	.word	.LC242
	.word	.LC244
	.word	.LC245
	.word	.LC259
	.word	.LC246
	.word	.LC219
	.word	.LC221
	.word	.LC222
	.word	.LC223
	.word	.LC224
	.word	.LC225
	.word	.LC227
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC167
	.word	g_event_report
	.word	.LC232
	.word	.LC234
	.word	.LC249
	.word	.LC250
	.word	.LC251
	.word	.LC252
	.word	.LC257
	.word	.LANCHOR1+32
	.word	.LC220
	.word	.LC229
	.word	.LC253
	.word	.LC254
	.word	.LC255
	.word	.LC256
	.word	.LC258
	.word	.LC226
	.word	.LC235
	.word	.LC236
	.word	.LC237
	.word	.LC238
	.word	.LC240
	.word	.LC243
	.word	.LC248
	.word	.LC239
	.word	.LC231
	.word	.LC247
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
	ldr	r2, .L2494
	mov	r1, #8
	mov	r4, r0
	bl	mvc_u_v
	ldr	r1, .L2494+4
	mov	r10, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2494+8
	mov	r9, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2494+12
	mov	r8, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2494+16
	str	r0, [fp, #-56]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2494+20
	str	r0, [fp, #-60]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2494+24
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r2, .L2494+28
	mov	r1, #2
	str	r0, [fp, #-68]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2494+32
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2494+36
	mov	r5, r0
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r6, r0
	bne	.L2487
	ldr	r3, [r4, #36]
	sub	r3, r3, #1
	cmp	r0, r3
	bhi	.L2489
	cmp	r10, #100
	mov	r7, r10
	beq	.L2455
	bhi	.L2456
	cmp	r10, #77
	beq	.L2455
	cmp	r10, #88
	beq	.L2457
	cmp	r10, #66
	bne	.L2454
	ldr	r1, .L2494+40
	mov	r0, #1
	bl	dprint_vfmw
.L2455:
	cmp	r5, #9
	mov	r2, r5
	bls	.L2486
.L2492:
	cmp	r5, #41
	bhi	.L2486
.L2461:
	movw	r3, #3992
	ldr	r1, [r4, #248]
	mul	r5, r3, r6
	add	r1, r1, r5
	ldrb	r10, [r1, #25]	@ zero_extendqisi2
	cmp	r10, #0
	beq	.L2462
	ldr	r10, .L2494+44
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
	bne	.L2490
	ldr	r1, [r4, #248]
	add	r0, r10, #2240
	str	r3, [fp, #-56]
	add	r1, r1, r5
	bl	MVC_SPSEqual
	ldr	r3, [fp, #-56]
	cmp	r0, #0
	bne	.L2491
.L2451:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2456:
	cmp	r10, #122
	beq	.L2459
	cmp	r10, #144
	beq	.L2459
	cmp	r10, #110
	beq	.L2459
.L2454:
	mov	r2, r10
	ldr	r1, .L2494+48
	mov	r0, #1
	mov	r7, #100
	bl	dprint_vfmw
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2492
.L2486:
	mov	r3, #41
	ldr	r1, .L2494+52
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, #41
	b	.L2461
.L2462:
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
	bne	.L2493
	ldr	r3, [r4, #248]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #26]
	ldr	r3, [r4, #248]
	add	r5, r3, r5
	strb	r2, [r5, #25]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2489:
	ldr	r1, .L2494+56
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #36]
	sub	r3, r2, #1
	cmp	r6, r3
	bls	.L2487
	ldr	r3, .L2494+60
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L2487
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r6, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r4, #120]
	mov	r1, #109
	blx	r5
.L2487:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2459:
	ldr	r1, .L2494+64
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2492
	b	.L2486
.L2457:
	ldr	r1, .L2494+68
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r5, #9
	mov	r2, r5
	bhi	.L2492
	b	.L2486
.L2491:
	ldr	ip, .L2494+72
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
	b	.L2451
.L2490:
	mov	r3, r6
	movw	r2, #10841
	ldr	r1, .L2494+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2451
.L2493:
	mov	r3, r6
	movw	r2, #10868
	ldr	r1, .L2494+76
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #248]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r5
	strb	r2, [r3, #26]
	ldr	r3, [r4, #248]
	add	r5, r3, r5
	strb	r10, [r5, #25]
	b	.L2451
.L2495:
	.align	2
.L2494:
	.word	.LC260
	.word	.LC261
	.word	.LC262
	.word	.LC263
	.word	.LC264
	.word	.LC265
	.word	.LC266
	.word	.LC267
	.word	.LC268
	.word	.LC269
	.word	.LC270
	.word	.LANCHOR2
	.word	.LC273
	.word	.LC274
	.word	.LC173
	.word	g_event_report
	.word	.LC272
	.word	.LC271
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC275
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
	beq	.L2560
	ldr	r1, .L2561
	bl	mvc_ue_v
	cmp	r0, #1
	str	r0, [r5, #4]
	bhi	.L2501
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	addeq	r7, r5, #4
	bne	.L2501
.L2503:
	ldr	r1, .L2561+4
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r7, #4]!
	ldr	r3, [r5, #4]
	cmp	r3, r6
	bcs	.L2503
	cmp	r3, #0
	mov	r2, #0
	str	r2, [r5, #16]
	str	r2, [r5, #24]
	beq	.L2504
	add	r8, r5, #16
	mov	r7, #1
.L2514:
	ldr	r1, .L2561+8
	mov	r0, r4
	bl	mvc_ue_v
	add	r9, r8, #4
	str	r0, [r8, #4]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcs	r3, #15
	cmp	r0, r3
	bhi	.L2505
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2505
	cmp	r0, #0
	addne	r10, r8, #16
	beq	.L2510
.L2509:
	ldr	r1, .L2561+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r10, #4]!
	ldr	r3, [r9]
	cmp	r6, r3
	bcc	.L2509
.L2510:
	ldr	r1, .L2561+16
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #8]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcc	r2, r3
	movcs	r2, #15
	cmp	r0, r2
	bhi	.L2507
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2507
	cmp	r0, #0
	addne	r8, r8, #24
	beq	.L2512
.L2513:
	ldr	r1, .L2561+20
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r8, #4]!
	ldr	r3, [r9, #8]
	cmp	r6, r3
	bcc	.L2513
	ldr	r3, [r5, #4]
.L2512:
	add	r7, r7, #1
	mov	r8, r9
	cmp	r7, r3
	bls	.L2514
	cmp	r3, #0
	mov	r3, #0
	addne	r8, r5, #48
	str	r3, [r5, #48]
	str	r3, [r5, #56]
	movne	r7, #1
	beq	.L2528
.L2527:
	ldr	r1, .L2561+24
	mov	r0, r4
	bl	mvc_ue_v
	add	r9, r8, #4
	str	r0, [r8, #4]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcs	r3, #15
	cmp	r0, r3
	bhi	.L2518
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2518
	cmp	r0, #0
	addne	r10, r8, #16
	beq	.L2523
.L2522:
	ldr	r1, .L2561+28
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r10, #4]!
	ldr	r3, [r9]
	cmp	r6, r3
	bcc	.L2522
.L2523:
	ldr	r1, .L2561+32
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r9, #8]
	ldr	r3, [r5, #4]
	cmp	r3, #15
	movcc	r2, r3
	movcs	r2, #15
	cmp	r0, r2
	bhi	.L2520
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L2520
	cmp	r0, #0
	addne	r8, r8, #24
	beq	.L2525
.L2526:
	ldr	r1, .L2561+36
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r6, #1
	str	r0, [r8, #4]!
	ldr	r3, [r9, #8]
	cmp	r6, r3
	bcc	.L2526
	ldr	r3, [r5, #4]
.L2525:
	add	r7, r7, #1
	mov	r8, r9
	cmp	r7, r3
	bls	.L2527
.L2528:
	ldr	r1, .L2561+40
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r0, #1
	str	r0, [r5, #80]
	cmp	r3, #16
	str	r3, [fp, #-60]
	bhi	.L2516
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2516
	ldr	r2, [fp, #-60]
	cmp	r2, #0
	beq	.L2533
	add	r2, r5, #8384
	add	r1, r5, #80
	add	r2, r2, #16
	str	r1, [fp, #-72]
	str	r2, [fp, #-68]
	add	r2, r5, #212
	str	r3, [fp, #-56]
	str	r2, [fp, #-64]
	str	r5, [fp, #-76]
.L2532:
	ldr	r2, .L2561+44
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-72]
	ldr	r1, .L2561+48
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
	bhi	.L2530
	ldrb	r7, [r4, #10]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L2530
	cmp	r2, #0
	beq	.L2540
	ldr	r3, [fp, #-64]
	movw	r10, #8188
	ldr	r2, [fp, #-68]
	movt	r10, 4
	add	r10, r3, r10
	mov	r8, r3
	str	r2, [fp, #-48]
.L2539:
	ldr	r2, .L2561+52
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2561+56
	str	r0, [r8], #4
	mov	r0, r4
	bl	mvc_ue_v
	add	r6, r0, #1
	str	r0, [r8, #4092]
	cmp	r6, #64
	bhi	.L2534
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2534
	cmp	r6, #0
	movne	r5, r3
	ldrne	r9, [fp, #-48]
	beq	.L2538
.L2535:
	ldr	r1, .L2561+60
	mov	r0, r4
	bl	mvc_ue_v
	add	r5, r5, #1
	cmp	r6, r5
	str	r0, [r9, #4]!
	bne	.L2535
.L2538:
	ldr	r1, .L2561+64
	mov	r0, r4
	bl	mvc_ue_v
	cmp	r0, #1024
	str	r0, [r10, #4]!
	bcs	.L2536
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2536
	ldr	r3, [fp, #-48]
	add	r7, r7, #1
	add	r3, r3, #256
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	cmp	r3, r7
	bne	.L2539
.L2540:
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
	bne	.L2532
.L2533:
	mov	r0, #0
	b	.L2552
.L2505:
	mov	r2, r0
	ldr	r1, .L2561+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2552:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2507:
	mov	r2, r0
	ldr	r1, .L2561+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2520:
	mov	r2, r0
	ldr	r1, .L2561+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2552
.L2518:
	mov	r2, r0
	ldr	r1, .L2561+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2552
.L2501:
	mov	r2, r0
	movw	r3, #65534
	ldr	r1, .L2561+84
	mov	r0, #1
	str	r3, [r5, #80]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2552
.L2504:
	str	r3, [r5, #48]
	str	r3, [r5, #56]
	b	.L2528
.L2536:
	mov	r2, r0
	ldr	r1, .L2561+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2552
.L2534:
	ldr	r3, [fp, #-56]
	movw	ip, #65534
	ldr	r5, [fp, #-76]
	mov	r2, r6
	ldr	r1, .L2561+92
	mov	r0, #1
	add	r3, r7, r3, lsl #6
	add	r3, r3, #1072
	add	r3, r3, #4
	add	r3, r5, r3, lsl #2
	str	ip, [r3, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2552
.L2560:
	mov	r0, r5
	movw	r3, #10931
	ldr	r2, .L2561+96
	ldr	r1, .L2561+100
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2552
.L2516:
	movw	r3, #65534
	ldr	r2, [fp, #-60]
	ldr	r1, .L2561+104
	mov	r0, #1
	str	r3, [r5, #80]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2552
.L2530:
	ldr	r3, [fp, #-56]
	mov	r0, #1
	ldr	r5, [fp, #-76]
	ldr	r2, [fp, #-52]
	add	r5, r5, r3, lsl #2
	ldr	r1, .L2561+108
	movw	r3, #65534
	str	r3, [r5, #148]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2552
.L2562:
	.align	2
.L2561:
	.word	.LC276
	.word	.LC278
	.word	.LC279
	.word	.LC282
	.word	.LC280
	.word	.LC284
	.word	.LC286
	.word	.LC289
	.word	.LC287
	.word	.LC291
	.word	.LC285
	.word	.LC293
	.word	.LC294
	.word	.LC296
	.word	.LC297
	.word	.LC300
	.word	.LC298
	.word	.LC281
	.word	.LC283
	.word	.LC290
	.word	.LC288
	.word	.LC277
	.word	.LC301
	.word	.LC299
	.word	.LC13
	.word	.LC14
	.word	.LC292
	.word	.LC295
	UNWIND(.fnend)
	.size	MVC_ProcessSUBSPSMvcExt, .-MVC_ProcessSUBSPSMvcExt
	.align	2
	.global	MVC_ProcessSUBSPSMvcVuiExt
	.type	MVC_ProcessSUBSPSMvcVuiExt, %function
MVC_ProcessSUBSPSMvcVuiExt:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	mov	r5, r1
	ldr	r1, .L2598
	mov	r4, r0
	bl	mvc_ue_v
	add	r3, r5, #278528
	cmp	r0, #1024
	str	r0, [r3, #560]
	bcs	.L2594
	adds	r6, r0, #1
	mov	r1, #0
	adc	r7, r1, #0
	strd	r6, [fp, #-116]
	orrs	r2, r6, r7
	beq	.L2582
	add	r1, r5, #294912
	add	r9, r5, #315392
	add	r9, r9, #856
	movw	r2, #16687
	mov	ip, r1
	movw	r6, #34136
	movw	r1, #16751
	movw	r0, #33844
	mov	r8, r5
	movt	r2, 4
	add	ip, ip, #820
	add	r2, r5, r2
	movt	r6, 4
	str	r2, [fp, #-104]
	movt	r1, 4
	add	r6, r5, r6
	add	r2, r5, r1
	movt	r0, 4
	str	r2, [fp, #-96]
	add	r2, r3, #111
	str	ip, [fp, #-76]
	str	r2, [fp, #-88]
	add	r2, r5, r0
	str	r6, [fp, #-48]
	str	r2, [fp, #-80]
	add	r2, r3, #560
	str	r2, [fp, #-92]
	add	r2, r3, #176
	str	r2, [fp, #-72]
	add	r2, r3, #432
	str	r2, [fp, #-52]
	add	r2, r3, #496
	str	r2, [fp, #-56]
	add	r2, r3, #240
	add	r3, r3, #816
	str	r2, [fp, #-84]
	str	r3, [fp, #-60]
	mov	r2, #1
	mov	r3, #0
	strd	r2, [fp, #-68]
	mov	r3, #0
	str	r3, [fp, #-100]
.L2581:
	ldr	r2, .L2598+4
	mov	r1, #3
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-88]
	ldr	r1, .L2598+8
	strb	r0, [r3, #1]!
	mov	r0, r4
	str	r3, [fp, #-88]
	bl	mvc_ue_v
	ldr	r3, [fp, #-92]
	cmp	r0, #1024
	str	r0, [r3, #4]!
	str	r3, [fp, #-92]
	bcs	.L2595
	adds	r5, r0, #1
	beq	.L2571
	ldr	r10, [fp, #-60]
	mov	r7, #0
	ldr	r6, [fp, #-48]
.L2568:
	ldr	r1, .L2598+12
	mov	r0, r4
	bl	mvc_ue_v
	add	r7, r7, #1
	cmp	r5, r7
	str	r0, [r10, #4]!
	bne	.L2568
	str	r6, [fp, #-48]
.L2571:
	ldr	r1, .L2598+16
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-96]
	uxtb	r0, r0
	strb	r0, [r3, #1]!
	cmp	r0, #0
	str	r3, [fp, #-96]
	bne	.L2596
.L2570:
	ldr	r1, .L2598+20
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-52]
	uxtb	r0, r0
	strb	r0, [r3]
	cmp	r0, #0
	beq	.L2572
	ldr	r1, .L2598+24
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r5, [fp, #-48]
	ldr	r2, .L2598+28
	mov	r1, #4
	str	r0, [r5]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34132
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2598+32
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
	bhi	.L2574
	ldrb	r5, [r4, #10]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L2574
	ldr	r6, [fp, #-48]
	movw	r10, #34099
	movt	r10, 4
	add	r10, r8, r10
	mov	r7, r6
.L2575:
	ldr	r1, .L2598+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2598+40
	add	r5, r5, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2598+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r10, #1]!
	ldr	r3, [r6]
	cmp	r3, r5
	bcs	.L2575
	ldr	r2, .L2598+48
	mov	r1, #5
	mov	r0, r4
	str	r6, [fp, #-48]
	bl	mvc_u_v
	movw	r3, #34396
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2598+52
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	add	r3, r8, #294912
	ldr	r2, .L2598+56
	mov	r1, #5
	str	r0, [r3, #1632]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34404
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2598+60
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #34408
	movt	r3, 4
	add	r3, r8, r3
	str	r0, [r3]
.L2572:
	ldr	r1, .L2598+64
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-56]
	uxtb	r0, r0
	strb	r0, [r3]
	cmp	r0, #0
	bne	.L2597
	ldr	r3, [fp, #-52]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2580
.L2579:
	ldr	r1, .L2598+68
	mov	r0, r4
	bl	mvc_u_1
	ldrd	r2, [fp, #-68]
	ldrd	r6, [fp, #-116]
	add	r8, r8, #312
	add	r9, r9, #312
	cmp	r7, r3
	ldr	r3, [fp, #-100]
	cmpeq	r6, r2
	add	r1, r3, #1
	ldr	r3, [fp, #-72]
	str	r1, [fp, #-100]
	add	r3, r3, #1
	str	r3, [fp, #-72]
	movhi	r3, #1
	movls	r3, #0
	cmp	r1, #63
	movhi	r1, #0
	andls	r1, r3, #1
	ldrd	r2, [fp, #-68]
	adds	r6, r2, #1
	adc	r7, r3, #0
	ldr	r3, [fp, #-52]
	cmp	r1, #0
	strd	r6, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-48]
	add	r3, r3, #312
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-76]
	add	r3, r3, #4
	str	r3, [fp, #-76]
	ldr	r3, [fp, #-80]
	add	r3, r3, #4
	str	r3, [fp, #-80]
	ldr	r3, [fp, #-84]
	add	r3, r3, #1
	str	r3, [fp, #-84]
	ldr	r3, [fp, #-60]
	add	r3, r3, #256
	str	r3, [fp, #-60]
	ldr	r3, [fp, #-104]
	strb	r0, [r3, #1]!
	str	r3, [fp, #-104]
	bne	.L2581
.L2582:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2597:
	ldr	r1, .L2598+24
	mov	r0, r4
	bl	mvc_ue_v
	add	r3, r8, #315392
	ldr	r2, .L2598+28
	mov	r1, #4
	mov	r5, r3
	str	r3, [fp, #-108]
	str	r0, [r9]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2598+32
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
	bhi	.L2574
	ldrb	r5, [r4, #10]	@ zero_extendqisi2
	cmp	r5, #0
	bne	.L2574
	movw	r10, #54067
	ldr	r6, [fp, #-48]
	movt	r10, 4
	add	r10, r8, r10
	mov	r7, r9
.L2577:
	ldr	r1, .L2598+36
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2598+40
	add	r5, r5, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	mvc_ue_v
	ldr	r1, .L2598+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	mvc_u_1
	strb	r0, [r10, #1]!
	ldr	r3, [r9]
	cmp	r3, r5
	bcs	.L2577
	ldr	r2, .L2598+48
	mov	r1, #5
	mov	r0, r4
	str	r6, [fp, #-48]
	bl	mvc_u_v
	movw	r3, #54364
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2598+52
	mov	r1, #5
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-108]
	ldr	r2, .L2598+56
	mov	r1, #5
	str	r0, [r3, #1120]
	mov	r0, r4
	bl	mvc_u_v
	movw	r3, #54372
	movt	r3, 4
	add	r3, r8, r3
	ldr	r2, .L2598+60
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
	bne	.L2580
	ldr	r3, [fp, #-56]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2579
.L2580:
	ldr	r1, .L2598+72
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-72]
	strb	r0, [r3]
	b	.L2579
.L2596:
	ldr	r2, .L2598+76
	mov	r1, #32
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-76]
	ldr	r2, .L2598+80
	mov	r1, #32
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r3, [fp, #-80]
	ldr	r1, .L2598+84
	str	r0, [r3]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r3, [fp, #-84]
	strb	r0, [r3]
	b	.L2570
.L2574:
	ldr	r1, .L2598+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2592:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2595:
	mov	r2, r0
	ldr	r1, .L2598+92
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2594:
	mov	r2, r0
	ldr	r1, .L2598+96
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2592
.L2599:
	.align	2
.L2598:
	.word	.LC302
	.word	.LC304
	.word	.LC305
	.word	.LC308
	.word	.LC307
	.word	.LC312
	.word	.LC313
	.word	.LC314
	.word	.LC315
	.word	.LC316
	.word	.LC317
	.word	.LC318
	.word	.LC319
	.word	.LC320
	.word	.LC321
	.word	.LC322
	.word	.LC323
	.word	.LC325
	.word	.LC324
	.word	.LC309
	.word	.LC310
	.word	.LC311
	.word	.LC199
	.word	.LC306
	.word	.LC303
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
	ldr	r2, .L2628
	mov	r1, #8
	mov	r4, r0
	bl	mvc_u_v
	ldr	r1, .L2628+4
	mov	r7, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2628+8
	str	r0, [fp, #-48]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2628+12
	mov	r9, r0
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2628+16
	str	r0, [fp, #-52]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2628+20
	str	r0, [fp, #-56]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r1, .L2628+24
	str	r0, [fp, #-60]
	mov	r0, r4
	bl	mvc_u_1
	ldr	r2, .L2628+28
	mov	r1, #2
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2628+32
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2628+36
	mov	r8, r0
	mov	r0, r4
	bl	mvc_ue_v
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r5, r0
	bne	.L2613
	cmp	r0, #31
	bhi	.L2623
	sub	r3, r7, #66
	cmp	r3, #78
	ldrls	pc, [pc, r3, asl #2]
	b	.L2603
.L2605:
	.word	.L2604
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2606
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2607
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2606
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2608
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2606
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2608
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2606
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2603
	.word	.L2608
.L2604:
	ldr	r1, .L2628+40
	mov	r0, #1
	bl	dprint_vfmw
.L2606:
	cmp	r8, #41
	bhi	.L2624
.L2609:
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
	bne	.L2625
	cmp	r7, #118
	cmpne	r7, #128
	mov	r9, #1
	strb	r9, [r6, #957]
	beq	.L2626
.L2611:
	movw	r3, #8500
	mov	r2, #1
	movt	r3, 5
	mla	r4, r3, r5, r4
	add	r4, r4, #12992
	strb	r2, [r4, #12]
.L2601:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2624:
	mov	r2, r8
	ldr	r1, .L2628+44
	mov	r0, #1
	mov	r8, #41
	bl	dprint_vfmw
	b	.L2609
.L2626:
	ldr	r1, .L2628+48
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
	bne	.L2627
	ldr	r1, .L2628+52
	mov	r0, r4
	bl	mvc_u_1
	cmp	r0, #0
	str	r0, [r6, #928]
	beq	.L2611
	mov	r1, r7
	mov	r0, r4
	bl	MVC_ProcessSUBSPSMvcVuiExt
	cmp	r0, #0
	beq	.L2611
	mov	r0, r9
	ldr	r1, .L2628+56
	bl	dprint_vfmw
	strb	r8, [r10, #4]
	mvn	r8, #0
	b	.L2601
.L2608:
	ldr	r1, .L2628+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2606
.L2607:
	ldr	r1, .L2628+64
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2606
.L2603:
	mov	r2, r7
	ldr	r1, .L2628+68
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2613:
	mvn	r8, #0
	b	.L2601
.L2623:
	ldr	r1, .L2628+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2601
.L2625:
	ldr	r1, .L2628+76
	mov	r0, #1
	bl	dprint_vfmw
	add	r2, r10, #12992
	mov	r3, #0
	mvn	r8, #0
	strb	r3, [r2, #12]
	strb	r3, [r6, #957]
	b	.L2601
.L2627:
	mov	r0, r9
	ldr	r1, .L2628+80
	bl	dprint_vfmw
	strb	r8, [r10, #4]
	mvn	r8, #0
	b	.L2601
.L2629:
	.align	2
.L2628:
	.word	.LC326
	.word	.LC327
	.word	.LC328
	.word	.LC329
	.word	.LC330
	.word	.LC331
	.word	.LC332
	.word	.LC333
	.word	.LC334
	.word	.LC335
	.word	.LC270
	.word	.LC337
	.word	.LC339
	.word	.LC341
	.word	.LC342
	.word	.LC272
	.word	.LC271
	.word	.LC336
	.word	.LC173
	.word	.LC338
	.word	.LC340
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
	beq	.L2639
	ldrb	r3, [ip]	@ zero_extendqisi2
	mov	r2, r3, asl #2
	mov	r5, r3, asl #5
	rsb	r4, r2, r5
	add	r4, ip, r4
	add	r6, r4, #8
	ldr	lr, [r4, #8]
	cmp	lr, #0
	beq	.L2639
	ldr	lr, [ip, #68]
	cmp	r3, #1
	cmpls	lr, #2
	bhi	.L2639
	cmp	lr, r3
	bls	.L2639
	ldr	lr, [r4, #12]
	mov	r6, r2
	ldr	r4, [r4, #24]
	mov	lr, lr, asl #3
	add	r1, r4, r1, lsl #3
	cmp	r1, lr
	bhi	.L2634
	b	.L2632
.L2635:
	ldr	r4, [r2, #24]
	ldr	r2, [r2, #12]
	rsb	lr, lr, r4
	add	r1, r1, lr
	mov	lr, r2, asl #3
	cmp	r1, lr
	bls	.L2632
.L2634:
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
	bhi	.L2635
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2632:
	rsb	r2, r6, r5
	mov	r0, #1
	add	ip, ip, r2
	str	r1, [ip, #24]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2639:
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
	beq	.L2655
	ldr	r3, [r0, #232]
	cmp	r3, #0
	cmpne	r2, #0
	beq	.L2655
	ldrb	r7, [r3]	@ zero_extendqisi2
	mov	ip, r7, asl #5
	sub	ip, ip, r7, asl #2
	add	ip, r3, ip
	ldr	ip, [ip, #8]
	cmp	ip, #0
	beq	.L2655
	ldr	ip, [r3, #68]
	cmp	r7, #1
	cmpls	ip, #2
	movhi	lr, #1
	movls	lr, #0
	bhi	.L2655
	cmp	ip, r7
	bls	.L2655
.L2650:
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
	bcs	.L2645
	ldrb	r3, [r8, r4, lsr #3]	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	r2, lr
	add	r4, r1, #1
	add	ip, ip, #1
	strb	r3, [r1]
	b	.L2657
.L2648:
	cmp	ip, r6
	mov	r1, r4
	beq	.L2658
	ldrb	r3, [ip], #1	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	r2, lr
	strb	r3, [r4], #1
.L2657:
	ldr	r3, [r0, #232]
	add	r3, r3, r5
	ldr	r1, [r3, #24]
	add	r1, r1, #8
	str	r1, [r3, #24]
	bhi	.L2648
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2658:
	ldr	r3, [r0, #232]
.L2645:
	ldrb	ip, [r3]	@ zero_extendqisi2
	add	r7, r7, #1
	add	ip, ip, #1
	strb	ip, [r3]
	ldr	r3, [r0, #232]
	ldr	ip, [r3, #68]
	cmp	ip, r7
	bhi	.L2650
	mov	r0, lr
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2655:
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
	ldr	r1, .L2666
	mov	r4, r0
	bl	mvc_ue_v
	add	r6, r4, #11075584
	add	r5, r6, #45056
	ldr	r2, .L2666+4
	mov	r1, #1
	str	r0, [r5, #2704]
	mov	r0, r4
	bl	mvc_u_v
	uxtb	r0, r0
	strb	r0, [r5, #2681]
	cmp	r0, #0
	beq	.L2665
.L2660:
	mov	r0, r4
	ldr	r2, .L2666+8
	mov	r1, #1
	add	r6, r6, #45056
	bl	mvc_u_v
	mov	r3, #1
	strb	r3, [r6, #2680]
	strb	r0, [r6, #2682]
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2665:
	ldr	r2, .L2666+12
	mov	r1, #7
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+16
	mov	r1, #1
	str	r0, [r5, #2696]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+20
	mov	r1, #6
	strb	r0, [r5, #2683]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+24
	mov	r1, #1
	str	r0, [r5, #2700]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+28
	mov	r1, #1
	strb	r0, [r5, #2684]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+32
	mov	r1, #1
	strb	r0, [r5, #2685]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+36
	mov	r1, #1
	strb	r0, [r5, #2686]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+40
	mov	r1, #1
	strb	r0, [r5, #2687]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+44
	mov	r1, #1
	strb	r0, [r5, #2688]
	mov	r0, r4
	bl	mvc_u_v
	ldrb	r3, [r5, #2683]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r5, #2689]
	bne	.L2661
	ldr	r3, [r5, #2696]
	cmp	r3, #5
	beq	.L2661
	ldr	r2, .L2666+48
	mov	r1, #1
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+52
	mov	r1, #1
	strb	r0, [r5, #2690]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+56
	mov	r1, #1
	strb	r0, [r5, #2691]
	mov	r0, r4
	bl	mvc_u_v
	ldr	r2, .L2666+60
	mov	r1, #1
	strb	r0, [r5, #2692]
	mov	r0, r4
	bl	mvc_u_v
	strb	r0, [r5, #2693]
.L2661:
	ldr	r2, .L2666+64
	mov	r1, #8
	mov	r0, r4
	bl	mvc_u_v
	ldr	r1, .L2666+68
	str	r0, [r5, #2708]
	mov	r0, r4
	bl	mvc_ue_v
	str	r0, [r5, #2712]
	b	.L2660
.L2667:
	.align	2
.L2666:
	.word	.LC343
	.word	.LC344
	.word	.LC360
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
	.word	.LC356
	.word	.LC357
	.word	.LC358
	.word	.LC359
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
	ldr	r2, [r2, #2632]
	mla	r4, r4, r2, r3
	ldrb	r2, [r4, #25]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2669
	ldr	r0, [r0, #36]
	cmp	r0, #0
	ble	.L2670
	ldrb	r2, [r3, #25]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #3984
	addeq	r3, r3, #8
	beq	.L2673
	b	.L2692
.L2674:
	ldrb	r1, [r3, #-3967]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2671
.L2673:
	add	r2, r2, #1
	mov	r4, r3
	cmp	r2, r0
	add	r3, r3, #3984
	add	r3, r3, #8
	bne	.L2674
.L2670:
	ldr	r1, .L2694
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
.L2675:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2692:
	mov	r4, r3
.L2671:
	cmp	r4, #0
	beq	.L2670
.L2669:
	ldrb	r3, [r4, #24]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2676
	ldrb	r3, [r4, #35]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2693
	ldr	r1, [r4, #388]
	ldr	r8, [r4, #392]
	add	r1, r1, #1
	add	r8, r8, #1
.L2679:
	ldr	r2, .L2694+4
	mov	r0, r5
	bl	mvc_u_v
	add	r7, r6, #45056
	mov	r1, r8
	ldr	r2, .L2694+8
	str	r0, [r7, #2720]
	mov	r0, r5
	bl	mvc_u_v
	str	r0, [r7, #2724]
.L2676:
	ldrb	r0, [r4, #39]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	r3, r0
	beq	.L2675
	mov	r0, r5
	ldr	r2, .L2694+12
	mov	r1, #4
	add	r6, r6, #45056
	bl	mvc_u_v
	mov	r3, #0
	strb	r0, [r6, #2716]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2693:
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2676
	ldr	r1, [r4, #700]
	ldr	r8, [r4, #704]
	add	r1, r1, #1
	add	r8, r8, #1
	b	.L2679
.L2695:
	.align	2
.L2694:
	.word	.LC361
	.word	.LC362
	.word	.LC363
	.word	.LC364
	UNWIND(.fnend)
	.size	MVC_DecPicTimingSEI, .-MVC_DecPicTimingSEI
	.align	2
	.global	MVC_DecSEI
	.type	MVC_DecSEI, %function
MVC_DecSEI:
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
	ldr	r2, [r0, #232]
	sub	r7, fp, #44
	mov	r3, #0
	mov	r1, #32
	mov	r4, r0
	add	r6, r0, #548
	mov	r8, r3
	strb	r3, [r7, #-1]!
	str	r1, [r2, #24]
	b	.L2699
.L2887:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2698
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2886
.L2699:
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
	bls	.L2887
.L2698:
	ldr	r1, .L2918
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2701
.L2886:
	mov	r3, #0
	str	r3, [fp, #-60]
.L2835:
	mov	r5, #0
	b	.L2705
.L2889:
	bl	BsSkip
	cmp	r9, #0
	ble	.L2703
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2888
.L2705:
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
	bls	.L2889
.L2703:
	ldr	r1, .L2918+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2888:
	cmp	r5, #409600
	bgt	.L2703
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
	b	.L2708
.L2710:
	.word	.L2709
	.word	.L2711
	.word	.L2712
	.word	.L2713
	.word	.L2714
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
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2708
	.word	.L2732
.L2732:
	mov	r1, r5
	mov	r0, r4
	ldr	r8, [r4, #572]
	bl	MVC_DecFramePackingSEI
	ldr	r2, [r4, #572]
	mov	r9, r5, asl #3
	rsb	r3, r8, r2
	cmp	r3, r9
	bge	.L2821
	rsb	r9, r3, r9
	ldr	r3, [r4, #564]
	cmp	r9, #0
	add	r8, r9, #7
	movge	r8, r9
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2823
	add	r1, r2, #8
	mov	r3, r3, asl #3
	cmp	r1, r3
	bhi	.L2823
	mov	r10, #0
	b	.L2824
.L2825:
	add	r1, r2, #8
	cmp	r1, r3
	bhi	.L2823
.L2824:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r10, r10, #1
	ldr	r3, [r4, #564]
	cmp	r10, r8
	ldr	r2, [r4, #572]
	mov	r3, r3, asl #3
	bne	.L2825
.L2823:
	mov	r1, r9, asr #31
	mov	r0, r1, lsr #29
	add	r1, r9, r0
	and	r1, r1, #7
	rsb	r1, r0, r1
	add	r2, r2, r1
	cmp	r3, r2
	bcs	.L2890
.L2821:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2891
.L2734:
	ldr	r3, [r4, #60]
	cmp	r3, #3
	bhi	.L2892
.L2830:
	mov	r8, #0
	b	.L2834
.L2832:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2833
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2893
.L2834:
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
	bls	.L2832
.L2833:
	mov	r0, #0
.L2701:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2731:
	mov	r3, r5
	ldr	r1, .L2918+8
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2894
.L2817:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2818
.L2819:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2818:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2819
	ldr	r3, [r4, #60]
	cmp	r3, #3
	bls	.L2830
.L2892:
	ldr	r1, .L2918+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2730:
	mov	r3, r5
	ldr	r1, .L2918+16
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2895
.L2814:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2815
.L2816:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2815:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2816
	b	.L2734
.L2729:
	mov	r3, r5
	ldr	r1, .L2918+20
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2896
.L2811:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2812
.L2813:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2812:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2813
	b	.L2734
.L2727:
	mov	r3, r5
	ldr	r1, .L2918+24
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2897
.L2805:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2806
.L2807:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2806:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2807
	b	.L2734
.L2728:
	mov	r3, r5
	ldr	r1, .L2918+28
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2898
.L2808:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2809
.L2810:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2809:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2810
	b	.L2734
.L2726:
	mov	r3, r5
	ldr	r1, .L2918+32
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2899
.L2802:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2803
.L2804:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2803:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2804
	b	.L2734
.L2725:
	mov	r3, r5
	ldr	r1, .L2918+36
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2900
.L2799:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2800
.L2801:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2800:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2801
	b	.L2734
.L2717:
	mov	r3, r5
	ldr	r1, .L2918+40
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2901
.L2775:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2776
.L2777:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2776:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2777
	b	.L2734
.L2721:
	mov	r3, r5
	ldr	r1, .L2918+44
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2902
.L2787:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2788
.L2789:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2788:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2789
	b	.L2734
.L2712:
	mov	r3, r5
	ldr	r1, .L2918+48
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2903
.L2744:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2745
.L2746:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2745:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2746
	b	.L2734
.L2723:
	mov	r3, r5
	ldr	r1, .L2918+52
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2904
.L2793:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2794
.L2795:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2794:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2795
	b	.L2734
.L2715:
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	bne	.L2714
	mov	r3, r5
	ldr	r1, .L2918+56
	mov	r0, #20
	bl	dprint_vfmw
.L2751:
	ldr	r0, [r4, #120]
	ldr	r8, [r4, #60]
	bl	GetUsd
	add	r8, r8, #132
	str	r0, [r4, r8, asl #2]
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	ldr	r1, [r4, r3, asl #2]
	cmp	r1, #0
	beq	.L2838
	ldr	r2, [r4, #232]
	cmp	r5, #1024
	movlt	r9, r5
	movge	r9, #1024
	ldrb	r0, [r2]	@ zero_extendqisi2
	ldr	ip, [r2, #68]
	cmp	r0, ip
	bcs	.L2839
	sxth	r3, r0
	mov	r8, #0
	mov	lr, r3, asl #5
	sub	r3, lr, r3, asl #2
	add	r2, r2, r3
.L2753:
	ldr	r3, [r2, #24]
	add	r0, r0, #1
	ldr	lr, [r2, #12]
	cmp	r0, ip
	add	r3, r3, #7
	add	r2, r2, #28
	sub	r3, lr, r3, lsr #3
	add	r8, r8, r3
	bne	.L2753
	mov	r3, r8
.L2752:
	ldrsb	r2, [fp, #-60]
	cmp	r3, r9
	movge	r8, r9
	cmp	r2, #1
	str	r2, [fp, #-64]
	movne	r10, #0
	strne	r10, [fp, #-56]
	beq	.L2905
.L2755:
	rsb	r2, r10, r8
	mov	r0, r4
	bl	MVC_GetBytes
	subs	r8, r0, #0
	ble	.L2906
	ldr	r3, [fp, #-56]
	rsb	r3, r3, r9
	cmp	r8, r3
	ldr	r3, [r4, #60]
	blt	.L2907
	add	r3, r3, #132
	ldr	r2, [fp, #-56]
	cmp	r9, r5
	ldr	r3, [r4, r3, asl #2]
	rsb	r8, r2, r5
	str	r8, [r3, #1052]
	bcc	.L2908
.L2766:
	cmp	r8, #0
	ble	.L2761
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2761
	mov	r5, #0
	b	.L2768
.L2769:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2761
.L2768:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2769
.L2761:
	ldr	r3, [r4, #60]
	ldr	r1, [r4, #224]
	add	r3, r3, #132
	ldr	ip, .L2918+116
	ldr	r2, [fp, #-64]
	ldr	r3, [r4, r3, asl #2]
	ldrd	r0, [r1, #64]
	cmp	r2, #1
	add	r3, r3, #1056
	ldr	r5, [ip]
	moveq	r2, #8
	movne	r2, #9
	strd	r0, [r3]
	cmp	r5, #0
	ldr	r3, [r4, #60]
	add	r3, r3, #132
.L2884:
	ldr	r3, [r4, r3, asl #2]
	str	r2, [r3, #1040]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #84]
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r2, [r3, #1044]
	beq	.L2734
	ldr	r2, [r4, #60]
	movw	r3, #1064
	mov	r1, #6
	ldr	r0, [r4, #120]
	add	r2, r2, #132
	ldr	r2, [r4, r2, asl #2]
	blx	r5
	b	.L2734
.L2719:
	mov	r3, r5
	ldr	r1, .L2918+60
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2909
.L2781:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2782
.L2783:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2782:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2783
	b	.L2734
.L2718:
	mov	r3, r5
	ldr	r1, .L2918+64
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2910
.L2778:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2779
.L2780:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2779:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2780
	b	.L2734
.L2720:
	mov	r3, r5
	ldr	r1, .L2918+68
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2911
.L2784:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2785
.L2786:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2785:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2786
	b	.L2734
.L2709:
	mov	r3, r5
	ldr	r1, .L2918+72
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2912
.L2733:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2735
.L2736:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2735:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2736
	b	.L2734
.L2724:
	mov	r3, r5
	ldr	r1, .L2918+76
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2913
.L2796:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2797
.L2798:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2797:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2798
	b	.L2734
.L2716:
	mov	r3, r5
	ldr	r1, .L2918+80
	mov	r0, #20
	bl	dprint_vfmw
	cmp	r5, #0
	ble	.L2772
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2772
	mov	r8, #0
	b	.L2773
.L2774:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2772
.L2773:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2774
.L2772:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2734
	movw	r3, #11938
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2734
.L2722:
	mov	r3, r5
	ldr	r1, .L2918+84
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2914
.L2790:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2791
.L2792:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2791:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2792
	b	.L2734
.L2711:
	mov	r3, r5
	ldr	r1, .L2918+88
	mov	r0, #20
	mov	r9, r5, asl #3
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	ldr	r8, [r4, #572]
	bl	MVC_DecPicTimingSEI
	ldr	r2, [r4, #572]
	rsb	r3, r8, r2
	cmp	r3, r9
	bge	.L2738
	rsb	r9, r3, r9
	ldr	r3, [r4, #564]
	cmp	r9, #0
	add	r8, r9, #7
	movge	r8, r9
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2740
	add	r1, r2, #8
	mov	r3, r3, asl #3
	cmp	r1, r3
	bhi	.L2740
	mov	r10, #0
	b	.L2741
.L2742:
	add	r1, r2, #8
	cmp	r1, r3
	bhi	.L2740
.L2741:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r10, r10, #1
	ldr	r3, [r4, #564]
	cmp	r10, r8
	ldr	r2, [r4, #572]
	mov	r3, r3, asl #3
	bne	.L2742
.L2740:
	mov	r1, r9, asr #31
	mov	r0, r1, lsr #29
	add	r1, r9, r0
	and	r1, r1, #7
	rsb	r1, r0, r1
	add	r2, r2, r1
	cmp	r3, r2
	bcs	.L2915
.L2738:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2734
	movw	r3, #11721
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2734
.L2713:
	mov	r3, r5
	ldr	r1, .L2918+92
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2916
.L2747:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2748
.L2749:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2748:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2749
	b	.L2734
.L2708:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	blt	.L2917
.L2827:
	cmp	r5, #0
	ble	.L2734
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
	mov	r8, #0
	b	.L2828
.L2829:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2734
.L2828:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2829
	b	.L2734
.L2893:
	cmp	r3, #128
	bne	.L2835
	b	.L2833
.L2714:
	mov	r3, r5
	ldr	r1, .L2918+96
	mov	r0, #20
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [fp, #-60]
	b	.L2751
.L2907:
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r8, [r3, #1052]
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2761
	mov	r5, #0
	b	.L2762
.L2764:
	ldr	r3, [r4, #572]
	ldr	r2, [r4, #564]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2761
.L2762:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2764
	b	.L2761
.L2919:
	.align	2
.L2918:
	.word	.LC365
	.word	.LC366
	.word	.LC393
	.word	.LC394
	.word	.LC392
	.word	.LC391
	.word	.LC389
	.word	.LC390
	.word	.LC388
	.word	.LC387
	.word	.LC379
	.word	.LC383
	.word	.LC370
	.word	.LC385
	.word	.LC373
	.word	.LC381
	.word	.LC380
	.word	.LC382
	.word	.LC367
	.word	.LC386
	.word	.LC378
	.word	.LC384
	.word	.LC369
	.word	.LC371
	.word	.LC372
	.word	.LC374
	.word	.LC376
	.word	.LANCHOR0+236
	.word	.LC368
	.word	g_event_report
	.word	.LC375
	.word	.LC377
.L2905:
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	mov	r0, r4
	ldr	r2, .L2918+100
	strb	r3, [r1, #1026]
	mov	r1, #8
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	ldr	r10, [r4, r3, asl #2]
	bl	mvc_u_v
	strb	r0, [r10, #1027]
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	ldrb	r2, [r3, #1027]	@ zero_extendqisi2
	cmp	r2, #255
	beq	.L2756
	mov	r10, #3
	mov	r2, #0
	str	r10, [fp, #-56]
	strb	r2, [r3, #1028]
.L2757:
	ldr	r3, [r4, #60]
	mov	r1, #16
	ldr	r2, .L2918+104
	mov	r0, r4
	add	r3, r3, #132
	ldr	r3, [r4, r3, asl #2]
	str	r3, [fp, #-68]
	bl	mvc_u_v
	ldr	r3, [fp, #-68]
	mov	r1, r10
	add	r3, r3, #1024
	strh	r0, [r3, #6]	@ movhi
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r8, r10
	ldr	r3, [r4, #60]
	beq	.L2758
	add	r3, r3, #132
	ldr	r1, [r4, r3, asl #2]
	b	.L2755
.L2900:
	movw	r3, #12158
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2799
.L2901:
	movw	r3, #11950
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2775
.L2902:
	movw	r3, #12054
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2787
.L2903:
	movw	r3, #11733
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2744
.L2904:
	movw	r3, #12106
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2793
.L2896:
	movw	r3, #12262
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2811
.L2897:
	movw	r3, #12210
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2805
.L2898:
	movw	r3, #12236
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2808
.L2899:
	movw	r3, #12184
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2802
.L2894:
	movw	r3, #12314
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2817
.L2895:
	mov	r3, #12288
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2814
.L2910:
	movw	r3, #11976
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2778
.L2911:
	movw	r3, #12028
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2784
.L2912:
	movw	r3, #11668
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2733
.L2913:
	movw	r3, #12132
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2796
.L2909:
	movw	r3, #12002
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2781
.L2914:
	movw	r3, #12080
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2790
.L2916:
	movw	r3, #11759
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2747
.L2891:
	movw	r3, #12366
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2734
.L2917:
	movw	r3, #12376
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2827
.L2915:
	mov	r0, r6
	bl	BsSkip
	b	.L2738
.L2890:
	mov	r0, r6
	bl	BsSkip
	b	.L2821
.L2908:
	rsb	r1, r9, r5
	mov	r0, r4
	bl	MVC_PassBytes
	cmp	r0, #0
	bge	.L2766
	movw	r3, #11891
	ldr	r2, .L2918+108
	ldr	r1, .L2918+112
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2766
.L2839:
	mov	r3, #0
	mov	r8, r3
	b	.L2752
.L2758:
	ldr	r1, [r4, #224]
	add	r3, r3, #132
	ldr	ip, .L2918+116
	mov	r2, #8
	ldr	r3, [r4, r3, asl #2]
	ldrd	r0, [r1, #64]
	add	r3, r3, #1056
	ldr	r5, [ip]
	strd	r0, [r3]
	cmp	r5, #0
	ldr	r3, [r4, #60]
	add	r3, r3, #132
	b	.L2884
.L2756:
	ldr	r2, .L2918+120
	mov	r1, #8
	mov	r0, r4
	str	r3, [fp, #-68]
	bl	mvc_u_v
	ldr	r3, [fp, #-68]
	mov	r10, #4
	str	r10, [fp, #-56]
	strb	r0, [r3, #1028]
	b	.L2757
.L2906:
	ldr	r1, .L2918+124
	mov	r0, #1
	bl	dprint_vfmw
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
	b	.L2701
.L2838:
	mvn	r0, #0
	b	.L2701
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
	str	r1, [r3, #2732]
	mov	r1, #7
	str	r2, [r3, #2736]
	mov	r2, #32
	strb	r1, [r3, #2723]
	mov	r1, #3
	strb	r2, [r3, #2722]
	mvn	r2, #0
	str	r1, [r3, #2744]
	mov	r1, #262144
	str	r2, [r3, #2748]
	mov	r2, #0
	strb	r0, [r3, #2721]
	str	r1, [r3, #2760]
	strb	r2, [r3, #2720]
	str	r2, [r3, #2752]
	str	r2, [r3, #2756]
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
	subs	r5, r0, #0
	beq	.L2932
	cmp	r1, #0
	beq	.L2933
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	and	r3, r3, #31
	sub	r3, r3, #1
	cmp	r3, #7
	ldrls	pc, [pc, r3, asl #2]
	b	.L2931
.L2926:
	.word	.L2925
	.word	.L2931
	.word	.L2931
	.word	.L2931
	.word	.L2925
	.word	.L2931
	.word	.L2927
	.word	.L2927
.L2927:
	ldr	r0, [r5]
	mov	r3, #1
	str	r3, [r5]
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2925:
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L2928
.L2930:
	mvn	r0, #0
.L2929:
	mov	r3, #0
	str	r3, [r5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2931:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2928:
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
	bhi	.L2930
	mov	r0, r0, asl #1
	rsb	r0, r0, #31
	mov	r0, r4, lsr r0
	subs	r0, r0, #1
	mvnne	r0, #0
	b	.L2929
.L2933:
	mov	r0, r1
	ldr	r3, .L2934
	movw	r2, #12504
	ldr	r1, .L2934+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2932:
	ldr	r3, .L2934+8
	movw	r2, #12503
	ldr	r1, .L2934+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2935:
	.align	2
.L2934:
	.word	.LC396
	.word	.LC24
	.word	.LC395
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
	ble	.L2962
	ldr	r3, [fp, #-48]
	subs	r7, r3, #0
	add	r8, r3, #63
	movge	r8, r3
	ands	r3, r3, #63
	movne	r3, #1
	add	r8, r3, r8, asr #6
	cmp	r8, #0
	ble	.L2950
	ldr	r5, .L2963
	ldr	r10, .L2963+4
.L2948:
	cmp	r7, #64
	ldr	r3, [r10, #52]
	ldr	r0, .L2963
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
	bne	.L2940
	ldr	r2, .L2963
	add	r4, r4, #1
	cmp	r3, r2
	bne	.L2943
	b	.L2941
.L2944:
	cmp	r3, r5
	add	r4, r4, #1
	beq	.L2941
.L2943:
	ldrb	r2, [r3, #-1]!	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2944
.L2940:
	mov	r0, r4, asl #3
.L2939:
	ldr	r3, [fp, #-48]
	cmp	r4, r3
	bge	.L2952
	sub	r3, r3, #1
	rsb	r4, r4, r3
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	tst	r2, #1
	moveq	r2, r2, lsr #1
	moveq	r3, #1
	bne	.L2952
.L2947:
	tst	r2, #1
	mov	r2, r2, lsr #1
	bne	.L2945
	add	r3, r3, #1
	cmp	r3, #8
	bne	.L2947
	b	.L2945
.L2941:
	subs	r8, r8, #1
	sub	r7, r7, #64
	bne	.L2948
	b	.L2940
.L2952:
	mov	r3, #0
.L2945:
	add	r0, r3, r0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2962:
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L2963+8
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2950:
	mov	r0, r4
	b	.L2939
.L2964:
	.align	2
.L2963:
	.word	.LANCHOR3-1952
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC397
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
	beq	.L2971
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2970
	ldr	r1, [r3, #40]
	ldr	r0, [r3, #36]
	bl	MVC_FindZeroBitsInSeg
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #40]
	cmp	r0, r2, asl #3
	bcs	.L2974
	cmn	r0, #1
	beq	.L2970
.L2969:
	add	r0, r0, #1
	str	r0, [r3, #72]
	ldr	r3, [r4, #232]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2973
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #72]
	cmp	r2, r1, asl #3
	bcs	.L2975
.L2973:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2975:
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
.L2974:
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
.L2970:
	ldr	r1, [r3, #12]
	ldr	r0, [r3, #8]
	bl	MVC_FindZeroBitsInSeg
	ldr	r3, [r4, #232]
	b	.L2969
.L2971:
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
	b	MVC_CombinePacket.part.14
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
	beq	.L2983
	mov	r2, r0
	mov	r3, #1
	b	.L2981
.L2980:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L2986
.L2981:
	ldrb	r1, [r2, #1025]	@ zero_extendqisi2
	add	r2, r2, #88
	cmp	r1, #0
	bne	.L2980
	mov	r2, r3
.L2979:
	mov	ip, #88
	mov	r1, #1
	mla	r3, ip, r3, r0
	mov	r0, r2
	strb	r1, [r3, #937]
	ldmfd	sp, {fp, sp, pc}
.L2986:
	mvn	r2, #0
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L2983:
	mov	r3, r2
	b	.L2979
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #68]
	mov	r4, r0
	mov	r9, r1
	mov	r7, r2
	ldr	r1, .L3030
	sub	r2, r3, #1
	mov	r0, #22
	add	r6, r4, #11075584
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r7]
	add	r5, r6, #40960
	str	r3, [r9]
	add	r1, r4, #12288
	ldr	r2, [r4, #232]
	mvn	ip, #0
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	strb	r0, [r5, #1067]
	ldrb	lr, [r2, #4]	@ zero_extendqisi2
	strb	lr, [r5, #1072]
	ldrb	r2, [r2, #5]	@ zero_extendqisi2
	strb	r3, [r5, #1075]
	str	ip, [r5, #2704]
	strb	r2, [r5, #1076]
	ldrb	r3, [r1, #704]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3023
	cmp	r2, #255
	beq	.L3024
.L2989:
	mov	r0, r4
	bl	MVC_SliceCheck
	subs	r8, r0, #0
	bne	.L3005
	mov	r0, r4
	bl	MVC_ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L3025
	ldrb	r3, [r5, #1069]	@ zero_extendqisi2
	mov	ip, #2240
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r9]
	ldrb	r1, [r5, #1076]	@ zero_extendqisi2
	ldr	r3, [r5, #1080]
	ldr	r0, [r4, #252]
	sxtb	r2, r1
	cmn	r2, #1
	mla	r3, ip, r3, r0
	beq	.L3026
	cmp	r1, #0
	bne	.L3001
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r3, [r3, #28]
	cmp	r2, #1
	beq	.L3027
	ldr	r2, [r4, #28]
	cmp	r2, r3
	movweq	r3, #35364
	movteq	r3, 168
	addeq	r3, r4, r3
	bne	.L3028
.L3000:
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
	ldr	r3, [r6, #2920]
	add	r3, r3, #1
	cmp	r2, r3
	movhi	r3, #1
	strhi	r3, [r7]
.L2997:
	mov	r0, r8
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3023:
	strb	r3, [r5, #1075]
	ldr	r3, [r1, #712]
	str	r3, [r5, #2704]
	ldrb	r3, [r1, #708]	@ zero_extendqisi2
	strb	r3, [r5, #1073]
	ldrb	r3, [r1, #709]	@ zero_extendqisi2
	strb	r3, [r5, #1074]
	b	.L2989
.L3026:
	ldr	r3, [r3, #28]
	movw	r1, #3992
	ldr	r2, [r4, #248]
	mla	r3, r1, r3, r2
	b	.L3000
.L3024:
	ldr	r3, [r4, #20]
	cmp	r3, #0
	beq	.L2989
	add	r3, r4, #10747904
	add	r3, r3, #20480
	ldr	r2, [r3, #2384]
	cmp	r2, #0
	bne	.L2992
	ldrb	r2, [r3, #2380]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2992
	add	r3, r4, #12992
	add	r3, r3, #16
.L2995:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L2993
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L3029
.L2993:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L2995
	mvn	r3, #0
	b	.L3022
.L3027:
	movw	r2, #8500
	movt	r2, 5
	mla	r3, r2, r3, r4
	add	r3, r3, #286720
	add	r3, r3, #932
	b	.L3000
.L2992:
	ldr	r3, [r3, #2388]
.L3022:
	cmn	r3, #1
	str	r3, [r5, #2704]
	beq	.L2989
	sub	r0, r0, #5
	mov	r3, #1
	clz	r0, r0
	strb	r3, [r5, #1075]
	strb	r3, [r5, #1074]
	mov	r0, r0, lsr #5
	strb	r0, [r5, #1073]
	b	.L2989
.L3005:
	mvn	r8, #0
	b	.L2997
.L3028:
	ldr	r1, .L3030+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2997
.L3025:
	ldr	r1, .L3030+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2997
.L3001:
	ldr	r1, .L3030+12
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L2997
.L3029:
	movw	r3, #8500
	movt	r3, 5
	mla	r3, r3, r2, r4
	add	r3, r3, #12992
	add	r3, r3, #16
	ldr	r3, [r3, #4]
	b	.L3022
.L3031:
	.align	2
.L3030:
	.word	.LC398
	.word	.LC33
	.word	.LC399
	.word	.LC400
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
	ldr	r3, [r5, #1112]
	cmp	r3, #0
	beq	.L3034
	add	r6, r0, #252
	mov	r4, #0
	b	.L3038
.L3035:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L3037
	ldr	r3, [r5, #1112]
	cmp	r4, r3
	bcs	.L3060
.L3038:
	ldr	r3, [r6, #4]!
	add	r4, r4, #1
	ldr	r0, [r7, #120]
	ldr	r3, [r3, #4]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L3035
.L3037:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3060:
	cmp	r3, #0
	beq	.L3034
	ldr	r3, [r5, #1116]
	cmp	r3, #0
	addne	r6, r7, #384
	movne	r4, #0
	bne	.L3041
	b	.L3034
.L3061:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L3037
	ldr	r3, [r5, #1116]
	cmp	r4, r3
	bcs	.L3034
.L3041:
	ldr	r3, [r6, #4]!
	add	r4, r4, #1
	ldr	r0, [r7, #120]
	ldr	r3, [r3, #4]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L3061
	b	.L3037
.L3034:
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
	subs	r5, r0, #0
	beq	.L3082
	bl	MVC_ClearCurrPic
	mov	r0, r5
	bl	MVC_ClearAllNal
	ldr	r3, [r5, #60]
	cmp	r3, #0
	beq	.L3064
	mov	r4, #0
	add	r6, r5, #524
	mov	r7, r4
.L3066:
	ldr	r1, [r6, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3065
	ldr	r0, [r5, #120]
	bl	FreeUsdByDec
	str	r7, [r6]
	ldr	r3, [r5, #60]
.L3065:
	cmp	r3, r4
	bhi	.L3066
.L3064:
	movw	r9, #48984
	movw	r8, #16408
	movt	r9, 169
	movt	r8, 170
	add	r9, r5, r9
	add	r8, r5, r8
	mov	r6, #0
	mov	r7, #0
.L3070:
	sub	r4, r9, #32
.L3068:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L3083
.L3067:
	cmp	r4, r9
	bne	.L3068
	add	r9, r4, #824
	cmp	r9, r8
	bne	.L3070
	ldr	r1, .L3084
	mov	r0, #2
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L3083:
	mov	r1, r2
	ldr	r0, [r5, #120]
	bl	FreeUsdByDec
	strd	r6, [r4]
	b	.L3067
.L3082:
	movw	r2, #13501
	ldr	r1, .L3084+4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L3085:
	.align	2
.L3084:
	.word	.LC402
	.word	.LC401
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
	subs	r5, r0, #0
	mov	r8, r1
	beq	.L3098
	cmp	r1, #31
	bhi	.L3099
	ldr	r1, .L3101
	mov	r0, #2
	bl	dprint_vfmw
	mov	r1, r8
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L3093
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	beq	.L3093
	add	r4, r0, #576
	add	r9, r0, #608
	mov	r6, #0
	mov	r7, #0
.L3091:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L3100
.L3090:
	cmp	r4, r9
	bne	.L3091
	ldr	r0, [r5, #120]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3100:
	mov	r1, r2
	ldr	r0, [r5, #120]
	bl	FreeUsdByDec
	strd	r6, [r4]
	b	.L3090
.L3093:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3099:
	ldr	r3, .L3101+4
	movw	r2, #13763
	ldr	r1, .L3101+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3098:
	ldr	r3, .L3101+12
	movw	r2, #13762
	ldr	r1, .L3101+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3102:
	.align	2
.L3101:
	.word	.LC404
	.word	.LC403
	.word	.LC24
	.word	.LC23
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r2
	mov	r4, r0
	moveq	r3, #1
	movne	r3, #0
	mov	r5, r1
	beq	.L3144
	ldr	r2, [r0, #224]
	ldr	r2, [r2, #24]
	cmp	r2, #0
	beq	.L3106
	ldrb	r2, [r0, #8]	@ zero_extendqisi2
	cmp	r2, #2
	beq	.L3106
	ldr	r2, [r0, #520]
	cmp	r2, #0
	strneb	r3, [r2, #2]
	movne	r0, #1
	strne	r3, [r4, #520]
	beq	.L3108
.L3143:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3106:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_CheckFrameStore
	cmn	r0, #3
	beq	.L3108
	ldr	r1, [r4, #520]
	cmp	r1, #0
	beq	.L3109
	mov	r0, r4
	bl	MVC_GetImagePara
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_CheckFrameStore
	subs	r7, r0, #0
	beq	.L3145
	cmn	r7, #3
	beq	.L3117
	mov	r3, r7
	movw	r2, #1844
	ldr	r1, .L3153
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #520]
	mov	r0, r4
	sub	r7, r7, #1
	clz	r7, r7
	ldr	r1, [r3, #220]
	bl	MVC_DEC_RecycleImage
	mov	r7, r7, lsr #5
.L3116:
	ldr	r3, [r4, #520]
	mov	r0, #0
	strb	r0, [r3, #2]
	ldr	r3, [r4, #520]
	cmp	r5, r3
	movne	r7, #0
	andeq	r7, r7, #1
	cmp	r7, r0
	strne	r0, [r4, #520]
	bne	.L3143
.L3118:
	mov	r3, #0
	str	r3, [r4, #520]
.L3109:
	mov	r1, r5
	mov	r0, r4
	bl	MVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	MVC_CheckFrameStore
	subs	r3, r0, #0
	beq	.L3146
	movw	r2, #1897
	ldr	r1, .L3153
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #220]
	mov	r0, r4
	bl	MVC_DEC_RecycleImage
	mov	r0, #2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3144:
	mov	r3, r1
	mov	r2, r0
	ldr	r1, .L3153+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3146:
	mov	r2, #1
	ldrsb	r1, [r5, #6]
	ldr	r0, [r4, #120]
	bl	FSP_SetDisplay
	ldrsb	r1, [r5, #6]
	ldr	r0, [r4, #120]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L3147
	cmp	r6, #1
	add	r3, r4, #584
	streq	r6, [r7, #180]
	mov	r2, r4
	ldr	r0, [r4, #120]
	mov	r1, #15
	str	r7, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L3148
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r7, #16]
	bcs	.L3149
.L3124:
	ldr	r2, [r4, #144]
	mov	r0, #0
	ldr	r3, [r4, #136]
	add	r2, r2, #1
	str	r2, [r4, #144]
	add	r3, r3, #2
	str	r3, [r4, #136]
	b	.L3143
.L3108:
	mov	r0, #1
	b	.L3143
.L3117:
	ldr	r3, [r4, #520]
	mov	r2, #0
	strb	r2, [r3, #2]
	b	.L3118
.L3145:
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
	beq	.L3150
	ldr	r3, [r4, #520]
	mov	r2, r4
	mov	r1, #15
	cmp	r5, r3
	cmpeq	r6, #1
	moveq	r3, #1
	streq	r3, [r7, #180]
	add	r3, r4, #584
	ldr	r0, [r4, #120]
	str	r7, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L3151
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r7, #16]
	bcs	.L3152
.L3115:
	ldr	r2, [r4, #144]
	mov	r7, #1
	ldr	r3, [r4, #136]
	add	r2, r2, r7
	str	r2, [r4, #144]
	add	r3, r3, #2
	str	r3, [r4, #136]
	b	.L3116
.L3149:
	mov	r1, r7
	mov	r0, r4
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3124
.L3152:
	mov	r1, r7
	mov	r0, r4
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3115
.L3148:
	mov	r2, r0
	ldr	r1, .L3153+8
	mov	r0, #0
	bl	dprint_vfmw
	ldrsb	r1, [r5, #6]
	mov	r2, #0
	ldr	r0, [r4, #120]
	bl	FSP_SetDisplay
	mov	r0, r4
	mov	r1, #1
	bl	MVC_ClearAll
	mvn	r0, #0
	b	.L3143
.L3151:
	mov	r2, r0
	ldr	r1, .L3153+8
	mov	r0, #0
	mov	r5, r0
	bl	dprint_vfmw
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
	b	.L3143
.L3147:
	movw	r2, #1871
	ldr	r1, .L3153+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3143
.L3150:
	movw	r2, #1815
	ldr	r1, .L3153+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3143
.L3154:
	.align	2
.L3153:
	.word	.LC408
	.word	.LC405
	.word	.LC407
	.word	.LC406
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
	ldr	r3, [r4, #2728]
	cmp	r3, #0
	moveq	r4, r3
	beq	.L3156
	mov	r2, #0
	strb	r2, [r3, #5]
	ldr	r1, [r4, #2728]
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #2728]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	cmp	r3, #0
	rsb	r4, r0, #0
	beq	.L3158
.L3156:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3158:
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
	beq	.L3178
	add	r8, r5, #11075584
	add	r8, r8, #45056
	ldr	r3, [r8, #2920]
	cmp	r3, #0
	movwne	r7, #47780
	movne	r6, #0
	movtne	r7, 169
	addne	r7, r5, r7
	beq	.L3166
.L3165:
	ldr	r1, [r7, #4]!
	add	r6, r6, #1
	cmp	r1, #0
	beq	.L3164
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3164
	ldr	r3, [r1, #56]
	cmn	r4, #1
	cmpne	r3, r4
	bne	.L3164
	mov	r0, r5
	bl	MVC_UnMarkFrameStoreRef
.L3164:
	ldr	r3, [r8, #2920]
	cmp	r3, r6
	bhi	.L3165
.L3166:
	mov	r1, r4
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
	ldr	r0, [r8, #2920]
	cmp	r0, #0
	beq	.L3163
	movw	r1, #47780
	mov	r7, #0
	movt	r1, 169
	add	r1, r5, r1
	mov	r2, r7
	mvn	r6, #0
.L3170:
	ldr	r3, [r1, #4]!
	add	r2, r2, #1
	cmp	r3, #0
	beq	.L3168
	ldr	r3, [r3, #56]
	cmn	r4, #1
	cmpne	r4, r3
	addeq	r7, r7, #1
	cmp	r4, r3
	cmnne	r4, #1
	movne	r6, r3
.L3168:
	cmp	r2, r0
	bne	.L3170
	cmp	r7, #0
	beq	.L3163
	adds	r8, r6, #1
	movne	r8, #1
	cmp	r4, r6
	movle	r9, #0
	andgt	r9, r8, #1
	b	.L3176
.L3177:
	subs	r7, r7, #1
	beq	.L3163
.L3176:
	cmp	r9, #0
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r1, r6
	mov	r0, r5
	beq	.L3173
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3163
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L3178
.L3173:
	mov	r1, r4
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3163
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	bne	.L3178
	cmp	r4, r6
	movge	r3, #0
	andlt	r3, r8, #1
	cmp	r3, #0
	beq	.L3177
	mov	r1, r6
	sub	r3, fp, #44
	sub	r2, fp, #40
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	mov	r0, r5
	cmn	r1, #1
	beq	.L3163
	bl	MVC_OutputFrmFromDPB
	cmp	r0, #0
	beq	.L3177
.L3178:
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3163:
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
	add	r10, r0, #11141120
	add	r9, r10, #16384
	add	r8, r0, #11075584
	movw	r7, #15768
	add	r8, r8, #36864
	ldr	r4, [r9, #44]
	movt	r7, 170
	add	r7, r0, r7
	mov	r5, r0
	add	r6, r4, #2000
	add	r4, r4, #4
	add	r6, r6, #4
	add	r3, r0, #11075584
	str	r3, [fp, #-48]
.L3225:
	ldr	r3, [r4]
	cmp	r3, #6
	ldrls	pc, [pc, r3, asl #2]
	b	.L3216
.L3218:
	.word	.L3217
	.word	.L3219
	.word	.L3220
	.word	.L3221
	.word	.L3222
	.word	.L3223
	.word	.L3224
.L3224:
	ldr	r2, [r4, #12]
	mov	r1, r7
	mov	r0, r5
	bl	MVC_MarkCurrPicLT
.L3216:
	add	r4, r4, #20
	cmp	r4, r6
	bne	.L3225
.L3217:
	ldrb	r3, [r8, #4024]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r0, #0
	beq	.L3233
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3223:
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
	strb	r3, [r8, #4024]
	b	.L3216
.L3222:
	mov	r0, r5
	ldr	r1, [r4, #16]
	bl	MVC_UpdateMaxLTFrmIdx
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	b	.L3216
.L3221:
	ldr	r3, [r4, #12]
	mov	r1, r7
	ldr	r2, [r4, #4]
	mov	r0, r5
	bl	MVC_MarkSTToLTRef
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	b	.L3216
.L3220:
	mov	r0, r5
	ldr	r2, [r4, #8]
	mov	r1, r7
	bl	MVC_UnMarkLTRef
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	b	.L3216
.L3219:
	mov	r0, r5
	ldr	r2, [r4, #4]
	mov	r1, r7
	bl	MVC_UnMarkSTRef
	mov	r0, r5
	bl	MVC_UpdateReflist
	b	.L3216
.L3233:
	ldr	r3, [fp, #-48]
	mov	r2, #0
	str	r2, [r9, #48]
	add	r10, r10, #12288
	add	r1, r3, #40960
	movw	r3, #26894
	movt	r3, 42
	ldr	r1, [r1, #2708]
	add	r3, r1, r3
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	str	r2, [r9, #880]
	ldrb	r3, [r10, #3483]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3228
	bcc	.L3229
	cmp	r3, #2
	streq	r2, [r9, #72]
	streq	r2, [r9, #60]
	streq	r2, [r8, #4052]
	streq	r2, [r8, #4060]
.L3227:
	ldr	r1, [r9, #120]
	mov	r0, r5
	bl	MVC_FlushDPB
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3229:
	ldr	r1, [r9, #60]
	ldr	r2, [r9, #68]
	ldr	r3, [r9, #72]
	rsb	r2, r1, r2
	str	r2, [r9, #68]
	rsb	r3, r1, r3
	str	r3, [r9, #72]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r9, #64]
	str	r3, [r9, #60]
	ldr	r1, [r8, #4060]
	ldr	r2, [r8, #4048]
	ldr	r3, [r8, #4052]
	rsb	r2, r1, r2
	str	r2, [r8, #4048]
	rsb	r3, r1, r3
	str	r3, [r8, #4052]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r8, #4056]
	str	r3, [r8, #4060]
	b	.L3227
.L3228:
	str	r2, [r9, #68]
	str	r2, [r9, #60]
	str	r2, [r8, #4048]
	str	r2, [r8, #4060]
	b	.L3227
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
	add	r10, r0, #11141120
	add	r6, r10, #16384
	mov	r7, r0
	ldr	r3, [r6, #44]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3235
	ldr	lr, [r0, #52]
	cmp	lr, #0
	beq	.L3244
	movw	r1, #47780
	mov	r2, #0
	movt	r1, 169
	add	r0, r0, #148
	add	r1, r7, r1
	mov	r4, r2
.L3243:
	ldr	r3, [r1, #4]!
	add	r2, r2, #1
	cmp	r3, #0
	beq	.L3240
	ldr	ip, [r3, #16]
	cmp	ip, #1
	streqb	ip, [r7, #6]
	ldr	ip, [r3, #56]
	ldr	r3, [r6, #120]
	cmp	ip, r3
	streq	r4, [r0]
.L3240:
	cmp	r2, lr
	add	r0, r0, #4
	bne	.L3243
.L3244:
	add	r3, r7, #11075584
	str	r3, [fp, #-48]
	add	r3, r3, #45056
	ldr	r9, [r3, #2920]
	cmp	r9, #0
	beq	.L3238
	movw	r4, #47780
	mov	r5, #0
	movt	r4, 169
	str	r10, [fp, #-52]
	add	r4, r7, r4
	mov	r8, r5
	mov	r10, r3
	b	.L3249
.L3247:
	cmp	r5, r9
	beq	.L3262
.L3249:
	ldr	r1, [r4, #4]!
	add	r5, r5, #1
	cmp	r1, #0
	beq	.L3247
	ldr	r0, [r1, #56]
	ldr	r2, [r6, #120]
	cmp	r0, r2
	bne	.L3247
	strb	r8, [r1, #714]
	mov	r2, #0
	strb	r8, [r1, #713]
	ldr	r1, [r4]
	strb	r8, [r1, #750]
	strb	r8, [r1, #749]
	ldr	r1, [r4]
	strb	r8, [r1, #786]
	strb	r8, [r1, #785]
	ldr	r1, [r4]
	strb	r8, [r1, #3]
	ldr	r1, [r4]
	ldr	r0, [r7, #120]
	ldrsb	r1, [r1, #6]
	bl	FSP_SetRef
	ldr	r1, [r4]
	mov	r3, #1
	movw	r2, #47992
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
	beq	.L3248
	ldr	r1, [r4]
	ldr	r0, [r7, #120]
	ldrsb	r1, [r1, #6]
	bl	FSP_SetDisplay
.L3248:
	str	r8, [r4]
	cmp	r5, r9
	str	r8, [r4, #64]
	str	r8, [r4, #128]
	ldr	r2, [r10, #2924]
	sub	r2, r2, #1
	str	r2, [r10, #2924]
	bne	.L3249
.L3262:
	ldr	r10, [fp, #-52]
.L3238:
	mov	r0, r7
	bl	MVC_UpdateReflist
	mov	r0, r7
	bl	MVC_UpdateLTReflist
	ldr	r3, [r6, #44]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3263
	ldr	r3, [fp, #-48]
	add	r10, r10, #12288
	mov	r0, r2
	mov	r1, #1
	add	r3, r3, #45056
	str	r2, [r3, #2936]
	strb	r2, [r10, #3484]
	strb	r1, [r10, #3485]
.L3250:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3263:
	ldr	r3, [fp, #-48]
	add	r10, r10, #12288
	mov	r2, #1
	add	r1, r3, #45056
	mov	r3, #0
	mov	r0, r3
	str	r2, [r1, #2936]
	str	r3, [r6, #52]
	strb	r2, [r10, #3484]
	strb	r3, [r10, #3485]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3235:
	ldr	r1, [r6, #120]
	bl	MVC_FlushDPB
	cmp	r0, #0
	addeq	r3, r7, #11075584
	streq	r3, [fp, #-48]
	beq	.L3238
.L3251:
	mvn	r0, #0
	b	.L3250
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #11075584
	add	r4, r0, #11141120
	add	r3, r3, #36864
	add	r6, r4, #12288
	mov	r2, #0
	mov	r7, r0
	strb	r2, [r3, #4024]
	ldrb	r2, [r6, #3483]	@ zero_extendqisi2
	sub	r2, r2, #2
	clz	r2, r2
	mov	r2, r2, lsr #5
	strb	r2, [r3, #4025]
	ldrb	r3, [r6, #3486]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L3265
	ldrb	r3, [r6, #3492]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3266
	ldr	r3, [r0, #224]
	ldr	r2, [r3, #660]
	cmp	r2, #1
	beq	.L3287
.L3266:
	add	r5, r4, #16384
	ldr	r3, [r5, #44]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r5, #56]
	beq	.L3288
	cmp	r3, #0
	bne	.L3289
.L3273:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3288:
	cmp	r3, #0
	beq	.L3273
.L3272:
	ldrb	r8, [r6, #3481]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L3290
.L3276:
	add	r4, r4, #12288
	mov	r0, #0
	ldrb	r3, [r4, #3484]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r4, #3485]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3287:
	ldr	r2, [r3, #656]
	cmp	r2, #0
	bne	.L3266
	ldr	r2, [r3, #664]
	cmp	r2, #0
	bne	.L3266
	ldr	r3, [r3, #620]
	add	r3, r3, #1024
	cmp	r3, #2048
	bls	.L3266
.L3265:
	mov	r0, r7
	bl	MVC_IDRMemMarking
	cmp	r0, #0
	bne	.L3267
	add	r5, r7, #11141120
	add	r5, r5, #16384
.L3274:
	ldrb	r3, [r6, #3486]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L3269
	ldr	r3, [r5, #56]
	cmp	r3, #0
	beq	.L3273
	ldr	r3, [r5, #44]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3272
	b	.L3276
.L3290:
	mov	r0, r7
	bl	MVC_SlidingWinMark
	ldr	r3, [r5, #44]
	strb	r8, [r3]
	strb	r8, [r6, #3484]
.L3269:
	ldr	r3, [r5, #56]
	cmp	r3, #0
	bne	.L3276
	b	.L3273
.L3289:
	mov	r0, r7
	bl	MVC_AdaptiveMemMark
	ldr	r3, [r5, #44]
	mov	r2, #0
	strb	r2, [r3]
	cmp	r0, r2
	beq	.L3274
.L3267:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
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
	add	r6, r5, #12288
	mov	r4, r0
	ldrb	r7, [r6, #3483]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L3293
	bcc	.L3294
	cmp	r7, #2
	beq	.L3295
	mov	r7, #0
.L3292:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3295:
	add	r5, r5, #16384
	mov	r2, #3
	ldr	r3, [r5, #40]
	strb	r2, [r3, #712]
	ldrb	r2, [r6, #3481]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3374
	ldr	r3, [r0, #520]
	add	r1, r6, #3488
	add	r1, r1, #8
	mov	r2, #640
	cmp	r3, #0
	ldreq	r3, [r5, #40]
	streq	r3, [r0, #520]
	streq	r3, [r3, #788]
	ldreq	r3, [r0, #520]
	add	ip, r3, #672
	add	r0, r3, #72
	ldr	r10, [r3, #656]
	ldrd	r8, [ip, #-8]
	ldr	r7, [r3, #660]
	strd	r8, [fp, #-52]
	ldrd	r8, [ip]
	bl	memcpy
	movw	r3, #16368
	and	r2, r10, r7
	mov	r1, r3
	movt	r3, 170
	add	r3, r4, r3
	movt	r1, 170
	ldr	r1, [r4, r1]
	ldr	r3, [r3, #4]
	and	r1, r1, r3
	adds	r3, r2, #1
	movne	r3, #1
	cmn	r1, #1
	movne	r3, #0
	cmp	r3, #0
	ldrne	r3, [r4, #520]
	strne	r10, [r3, #656]
	strne	r7, [r3, #660]
	ldrd	r2, [fp, #-52]
	ldrd	r0, [r5, #-8]
	ldr	ip, [r4, #520]
	cmp	r1, r3
	cmpeq	r0, r2
	add	r3, ip, #672
	ldrhid	r0, [fp, #-52]
.L3320:
	strd	r0, [r3, #-8]
	mov	ip, #2
	ldrd	r0, [r5]
	ldr	r3, [r4, #520]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r3, r3, #672
	movhi	r0, r8
	movhi	r1, r9
	strd	r0, [r3]
	mov	r0, #3
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r6, #3482]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #2]
	ldr	r2, [r4, #520]
	ldrb	r1, [r6, #3492]	@ zero_extendqisi2
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r4, #520]
	strb	ip, [r3, #784]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #712]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #92]
	str	r2, [r3, #808]
	ldr	r2, [r4, #520]
	ldr	r3, [r2, #808]
	ldr	r1, [r2, #772]
	add	r3, r3, r1
	mov	r3, r3, lsr #1
	str	r3, [r2, #736]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #736]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #788]
	str	r2, [r3, #716]
	ldrb	r3, [r6, #3487]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #520]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	beq	.L3371
.L3324:
	strb	r2, [r3, #4]
	mov	r2, #0
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #60]
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
	mov	r7, r0
	beq	.L3325
.L3367:
	ldr	r3, [r5, #40]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
.L3325:
	mov	r3, #0
	mov	r0, r7
	str	r3, [r4, #520]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3294:
	add	r5, r5, #16384
	mov	r2, #0
	ldr	r3, [r5, #40]
	strb	r2, [r3, #712]
	ldr	r1, [r0, #520]
	cmp	r1, r2
	beq	.L3296
	bl	MVC_OutputFrmToVO
	cmp	r0, #0
	bne	.L3375
.L3297:
	ldr	r3, [r4, #520]
	cmp	r3, #0
	beq	.L3296
	ldr	r3, [r5, #40]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
.L3296:
	ldr	r3, [r5, #40]
	mov	r0, #3
	mov	r8, #0
	add	r1, r6, #3488
	add	r1, r1, #8
	mov	r2, #640
	str	r3, [r4, #520]
	str	r3, [r3, #716]
	ldr	r3, [r4, #520]
	ldr	ip, [r5, #40]
	str	ip, [r3, #752]
	ldr	r3, [r4, #520]
	ldr	ip, [r5, #40]
	str	ip, [r3, #788]
	ldrb	ip, [r6, #3482]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	strb	ip, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #3]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #7]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #92]
	mov	r2, r8
	str	r1, [r3, #736]
	str	r1, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #712]
	ldr	r3, [r4, #520]
	ldrb	r1, [r6, #3492]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r4, #520]
	ldrb	r1, [r6, #3489]	@ zero_extendqisi2
	str	r1, [r3, #40]
	ldrb	r1, [r6, #3487]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	cmp	r1, #1
	moveq	r7, #3
	strb	r7, [r3, #4]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #60]
	str	r1, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #120]
	str	r1, [r3, #56]
	ldr	r3, [r4, #520]
	ldr	r1, [r5, #124]
	str	r1, [r3, #60]
	ldr	r3, [r4, #520]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r2, r8
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #520]
	cmp	r3, r8
	mov	r7, r0
	bne	.L3367
	b	.L3325
.L3293:
	add	r5, r5, #16384
	mov	r2, #3
	ldr	r3, [r5, #40]
	strb	r2, [r3, #712]
	ldrb	r2, [r6, #3481]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3301
	ldr	r1, [r0, #520]
	cmp	r1, #0
	beq	.L3302
	bl	MVC_OutputFrmToVO
	ldr	r3, [r5, #40]
	str	r3, [r4, #520]
	str	r3, [r3, #752]
	mov	r7, r0
.L3303:
	ldrb	r0, [r6, #3482]	@ zero_extendqisi2
	mov	r9, #1
	ldr	r3, [r4, #520]
	mov	r8, #0
	add	r1, r6, #3488
	mov	r2, #640
	add	r1, r1, #8
	strb	r0, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r9, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #7]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #3]
	ldrb	r0, [r6, #3492]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	strb	r0, [r3]
	ldr	r3, [r4, #520]
	str	r8, [r3, #40]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #92]
	str	r2, [r3, #772]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #772]
	str	r2, [r3, #736]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r9, [r3, #748]
	ldrb	r3, [r6, #3487]	@ zero_extendqisi2
	ldr	r2, [r4, #520]
	rsb	r3, r9, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r2, #4]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #60]
	str	r2, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #120]
	str	r2, [r3, #56]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #124]
	str	r2, [r3, #60]
	ldrb	r6, [r4, #9]	@ zero_extendqisi2
	cmp	r6, r9
	bne	.L3292
.L3369:
	ldr	r3, [r4, #520]
	mov	r2, r8
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r2, r8
	ldr	r1, [r4, #520]
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	ldr	r3, [r4, #520]
	cmp	r3, r8
	mov	r7, r0
	beq	.L3325
	ldr	r3, [r5, #40]
	mov	r2, r6
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	b	.L3325
.L3301:
	ldr	r3, [r0, #520]
	add	r1, r6, #3488
	add	r1, r1, #8
	mov	r2, #640
	cmp	r3, #0
	ldreq	r3, [r5, #40]
	streq	r3, [r0, #520]
	streq	r3, [r3, #752]
	ldreq	r3, [r0, #520]
	add	ip, r3, #672
	add	r0, r3, #72
	ldr	r10, [r3, #656]
	ldrd	r8, [ip, #-8]
	ldr	r7, [r3, #660]
	strd	r8, [fp, #-52]
	ldrd	r8, [ip]
	bl	memcpy
	movw	r3, #16368
	and	r2, r10, r7
	mov	r1, r3
	movt	r3, 170
	add	r3, r4, r3
	movt	r1, 170
	ldr	r1, [r4, r1]
	ldr	r3, [r3, #4]
	and	r1, r1, r3
	adds	r3, r2, #1
	movne	r3, #1
	cmn	r1, #1
	movne	r3, #0
	cmp	r3, #0
	ldrne	r3, [r4, #520]
	strne	r10, [r3, #656]
	strne	r7, [r3, #660]
	ldrd	r2, [fp, #-52]
	ldrd	r0, [r5, #-8]
	ldr	ip, [r4, #520]
	cmp	r1, r3
	cmpeq	r0, r2
	add	r3, ip, #672
	ldrhid	r0, [fp, #-52]
.L3307:
	strd	r0, [r3, #-8]
	mov	ip, #1
	ldrd	r0, [r5]
	ldr	r3, [r4, #520]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r3, r3, #672
	movhi	r0, r8
	movhi	r1, r9
	strd	r0, [r3]
	mov	r0, #3
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r6, #3482]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r4, #520]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #2]
	ldr	r2, [r4, #520]
	ldrb	r1, [r6, #3492]	@ zero_extendqisi2
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r4, #520]
	strb	ip, [r3, #748]
	ldr	r3, [r4, #520]
	strb	r0, [r3, #712]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #92]
	str	r2, [r3, #772]
	ldr	r2, [r4, #520]
	ldr	r3, [r2, #808]
	ldr	r1, [r2, #772]
	add	r3, r3, r1
	mov	r3, r3, lsr ip
	str	r3, [r2, #736]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #736]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #752]
	str	r2, [r3, #716]
	ldrb	r3, [r6, #3487]	@ zero_extendqisi2
	cmp	r3, ip
	ldr	r3, [r4, #520]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	bne	.L3324
.L3371:
	orr	r2, r2, ip
	b	.L3324
.L3374:
	ldr	r1, [r0, #520]
	cmp	r1, #0
	beq	.L3314
	bl	MVC_OutputFrmToVO
	ldr	r3, [r5, #40]
	str	r3, [r4, #520]
	str	r3, [r3, #788]
	mov	r7, r0
.L3315:
	ldrb	r0, [r6, #3482]	@ zero_extendqisi2
	mov	r9, #2
	ldr	r3, [r4, #520]
	mov	r8, #0
	add	r1, r6, #3488
	mov	r2, #640
	add	r1, r1, #8
	strb	r0, [r3, #1]
	ldr	r3, [r4, #520]
	strb	r9, [r3, #2]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #5]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #7]
	ldr	r3, [r4, #520]
	strb	r8, [r3, #3]
	ldrb	r0, [r6, #3492]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	strb	r0, [r3]
	ldr	r3, [r4, #520]
	str	r8, [r3, #40]
	ldr	r0, [r4, #520]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #92]
	str	r2, [r3, #808]
	ldr	r3, [r4, #520]
	ldr	r2, [r3, #808]
	str	r2, [r3, #736]
	str	r2, [r3, #44]
	ldr	r3, [r4, #520]
	strb	r9, [r3, #784]
	ldrb	r2, [r6, #3487]	@ zero_extendqisi2
	ldr	r3, [r4, #520]
	cmp	r2, #1
	movne	r2, r8
	moveq	r2, r9
	strb	r2, [r3, #4]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #60]
	str	r2, [r3, #32]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #120]
	str	r2, [r3, #56]
	ldr	r3, [r4, #520]
	ldr	r2, [r5, #124]
	str	r2, [r3, #60]
	ldrb	r6, [r4, #9]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L3369
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3375:
	str	r0, [sp]
	movw	r3, #2446
	ldr	r2, .L3376
	mov	r0, #22
	ldr	r1, .L3376+4
	bl	dprint_vfmw
	b	.L3297
.L3314:
	ldr	r3, [r5, #40]
	mov	r7, r1
	str	r3, [r0, #520]
	str	r3, [r3, #788]
	b	.L3315
.L3302:
	ldr	r3, [r5, #40]
	mov	r7, r1
	str	r3, [r0, #520]
	str	r3, [r3, #752]
	b	.L3303
.L3377:
	.align	2
.L3376:
	.word	.LANCHOR0+248
	.word	.LC409
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
	subs	r5, r0, #0
	beq	.L3379
	add	r6, r5, #11075584
	add	r6, r6, #45056
	ldr	r3, [r6, #2920]
	cmp	r3, #0
	mvneq	r7, #0
	beq	.L3381
	movw	r8, #47780
	mov	r4, #0
	movt	r8, 169
	add	r8, r5, r8
	mov	r7, r4
	mov	r9, r8
	b	.L3384
.L3383:
	ldr	r3, [r6, #2920]
	cmp	r3, r7
	bls	.L3419
.L3384:
	ldr	r3, [r9, #4]!
	add	r7, r7, #1
	cmp	r3, #0
	beq	.L3383
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3383
	ldrsb	r1, [r3, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L3383
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	sub	r3, r3, #1
	cmp	r3, #1
	ldr	r3, [r6, #2920]
	addls	r4, r4, #1
	cmp	r3, r7
	bhi	.L3384
.L3419:
	cmp	r4, #0
	beq	.L3385
	mvn	r7, #0
	b	.L3388
.L3386:
	ldr	r1, [r5, r3, asl #2]
	bl	MVC_OutputFrmToVO
	subs	r4, r4, #1
	mov	r7, r0
	beq	.L3416
.L3388:
	sub	r3, fp, #44
	sub	r2, fp, #40
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_GetMinPOC
	ldr	r1, [fp, #-44]
	movw	r3, #28330
	mov	r2, r4
	cmn	r1, #1
	movt	r3, 42
	mov	r0, r5
	add	r3, r1, r3
	bne	.L3386
.L3416:
	ldr	r3, [r6, #2920]
	cmp	r3, #0
	beq	.L3381
.L3387:
	mov	r4, #0
	b	.L3391
.L3390:
	ldr	r3, [r6, #2920]
	cmp	r3, r4
	bls	.L3381
.L3391:
	ldr	r1, [r8, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3390
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3390
	mov	r0, r5
	bl	MVC_UnMarkFrameStoreRef
	ldr	r3, [r6, #2920]
	cmp	r3, r4
	bhi	.L3391
.L3381:
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
	cmp	r7, #0
	moveq	r0, r7
	bne	.L3392
.L3414:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3385:
	cmp	r3, #0
	mvnne	r7, #0
	bne	.L3387
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
.L3392:
	add	r0, r5, #584
	bl	GetVoLastImageID
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3379:
	ldr	r3, .L3420
	movw	r2, #2838
	ldr	r1, .L3420+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3414
.L3421:
	.align	2
.L3420:
	.word	.LC23
	.word	.LC24
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
	beq	.L3439
	bl	MVC_ClearAllSlice
	movw	r7, #47784
	movw	r6, #47912
	movw	r5, #47848
	movt	r7, 169
	movt	r6, 169
	movt	r5, 169
	mov	r8, #0
	add	r7, r4, r7
	add	r6, r4, r6
	add	r5, r4, r5
	mov	r9, r8
.L3427:
	ldr	r3, [r7]
	mov	r2, #1
	add	r8, r8, r2
	cmp	r3, #0
	beq	.L3424
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3424:
	ldr	r3, [r5]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3425
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3425:
	ldr	r3, [r6]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3426
	ldrsb	r1, [r3, #6]
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3426:
	cmp	r8, #16
	str	r9, [r6], #4
	mov	r2, #0
	str	r9, [r5], #4
	str	r9, [r7], #4
	bne	.L3427
	ldr	r3, [r4, #44]
	add	r5, r4, #11075584
	add	r6, r5, #45056
	str	r3, [r6, #2920]
	str	r2, [r6, #2924]
	str	r2, [r6, #2928]
	str	r2, [r6, #2932]
	str	r2, [r6, #2936]
	ldr	r1, [r4, #520]
	cmp	r1, r2
	beq	.L3429
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3430
.L3434:
	add	r3, r4, #11141120
	add	r3, r3, #16384
	ldr	r3, [r3, #40]
	cmp	r3, #0
	beq	.L3432
	ldrsb	r1, [r3, #6]
	mov	r2, #1
	ldr	r0, [r4, #120]
	bl	FSP_ClearLogicFs
.L3432:
	mov	r3, #0
	str	r3, [r4, #520]
.L3429:
	ldr	r3, .L3457
	movw	r0, #47996
	mov	r2, #344
	mov	r1, #0
	movt	r0, 169
	add	r0, r4, r0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	ip, [r6, #2920]
	mov	r0, #0
	add	r3, r4, #144
	add	r1, r4, #216
	mov	r2, r0
	str	ip, [r6, #3148]
	str	r0, [r6, #3152]
.L3436:
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L3436
	add	r2, r4, #252
	add	r3, r4, #384
	mov	r0, #0
.L3437:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L3437
	add	r2, r5, #40960
	add	r4, r4, #516
	mov	r0, r1
	str	r1, [r2, #1112]
.L3438:
	str	r0, [r3, #4]!
	cmp	r3, r4
	mov	r2, #0
	bne	.L3438
	add	r5, r5, #40960
	mov	r0, r2
	str	r2, [r5, #1116]
.L3423:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3430:
	mov	r0, r4
	bl	MVC_OutputFrmToVO
	cmp	r0, #0
	bne	.L3456
.L3433:
	ldr	r3, [r4, #520]
	cmp	r3, #0
	bne	.L3434
	b	.L3429
.L3456:
	str	r0, [sp]
	movw	r3, #5724
	ldr	r2, .L3457+4
	mov	r0, #22
	ldr	r1, .L3457+8
	bl	dprint_vfmw
	b	.L3433
.L3439:
	mvn	r0, #0
	b	.L3423
.L3458:
	.align	2
.L3457:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+268
	.word	.LC410
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
	bne	.L3468
.L3460:
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L3461
	movw	r3, #318
	ldr	r2, .L3469
	ldr	r1, .L3469+4
	mov	r0, #22
	bl	dprint_vfmw
.L3461:
	mov	r0, #0
	strb	r0, [r4, #6]
	str	r0, [r4, #220]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3468:
	movw	r3, #313
	ldr	r2, .L3469
	ldr	r1, .L3469+8
	mov	r0, #22
	bl	dprint_vfmw
	b	.L3460
.L3470:
	.align	2
.L3469:
	.word	.LANCHOR0+280
	.word	.LC412
	.word	.LC411
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r5, r0, #11141120
	add	r6, r5, #12288
	mov	r4, r0
	ldrb	r3, [r6, #3483]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3472
	ldrb	r3, [r6, #3481]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3472
.L3473:
	ldr	r3, [r4, #108]
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ubfx	r7, r3, #16, #2
	cmp	r7, r2
	beq	.L3474
	sub	r2, r2, #2
	cmp	r2, #1
	cmpls	r7, #1
	bls	.L3539
.L3474:
	uxtb	r3, r7
	strb	r3, [r4, #8]
	cmp	r3, #2
	beq	.L3477
	cmp	r3, #3
	beq	.L3478
	cmp	r3, #1
	beq	.L3540
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3541
.L3485:
	ldr	r3, [r4, #64]
.L3481:
	ldrb	r2, [r6, #3493]	@ zero_extendqisi2
	strb	r2, [r4, #11]
.L3486:
	cmp	r3, #0
	beq	.L3537
	ldrb	r3, [r6, #3492]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3542
	cmp	r3, #1
	beq	.L3534
.L3536:
	add	r7, r4, #11141120
	add	r7, r7, #16384
.L3489:
	ldr	r2, [r4, #88]
	mov	r0, #2
	ldrb	r3, [r6, #3483]	@ zero_extendqisi2
	sub	r2, r2, #1
	ldr	r1, .L3545
	bl	dprint_vfmw
	ldr	r3, [r7, #112]
	ldr	r2, [r7, #108]
	mov	r1, #1
	strb	r1, [r7, #1450]
	str	r3, [r7, #2184]
	str	r2, [r7, #2188]
	ldr	r3, [r4, #64]
	str	r3, [r7, #2388]
	ldr	r3, [r4, #88]
	cmp	r3, #0
	beq	.L3490
	ldrb	r1, [r6, #3492]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L3543
	add	r3, r4, #11075584
	add	r3, r3, #45056
	ldr	r3, [r3, #2924]
	cmp	r3, #0
	bne	.L3492
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #24]
	cmp	r2, #2
	bne	.L3537
.L3495:
	movw	r2, #17832
	movt	r2, 170
	add	r2, r4, r2
	str	r2, [r4, #228]
	ldr	r1, [r3, #912]
	cmp	r1, #1
	beq	.L3544
	cmp	r1, #2
	bne	.L3498
	ldr	r1, [r3, #916]
	cmp	r2, #0
	cmpne	r1, #0
	ble	.L3498
	ldrb	r2, [r6, #3492]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L3498
	mov	r2, #0
	str	r2, [r4, #228]
	ldr	r3, [r7, #40]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	ldr	r2, [r4, #224]
	mov	r0, r4
	ldr	r3, [r2, #916]
	sub	r3, r3, #1
	str	r3, [r2, #916]
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3529
.L3472:
	ldr	r3, [r4, #140]
	ldr	r2, [r4, #144]
	add	r3, r3, #1
	ldr	r1, [r4, #224]
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #140]
	rsb	r3, r2, r3
	str	r3, [r1, #584]
	b	.L3473
.L3539:
	mov	r2, r7
	ldr	r1, .L3545+4
	mov	r0, #2
	bl	dprint_vfmw
	strb	r7, [r4, #8]
.L3478:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mov	r0, r4
	mvn	r1, #0
	bl	MVC_ClearDPB
	mvn	r0, #0
.L3529:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3490:
	ldr	r3, [r4, #224]
.L3498:
	ldr	r2, [r3, #600]
	add	r5, r5, #16384
	mov	r0, #0
	strb	r2, [r5, #1452]
	ldr	r2, [r3, #604]
	strb	r2, [r5, #1453]
	ldr	r2, [r3, #608]
	str	r2, [r5, #1456]
	ldr	r2, [r3, #612]
	str	r2, [r5, #1460]
	ldr	r3, [r3, #652]
	strb	r3, [r5, #1464]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L3540:
	ldrb	r3, [r6, #3492]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3485
	add	r7, r5, #16384
	ldr	r3, [r7, #56]
	cmp	r3, #0
	beq	.L3482
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3485
.L3499:
	ldrb	r2, [r6, #3493]	@ zero_extendqisi2
	ldr	r3, [r4, #64]
	strb	r2, [r4, #11]
	b	.L3486
.L3477:
	ldrb	r3, [r6, #3492]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3482
	ldr	r3, [r4, #64]
	cmp	r3, #0
	beq	.L3481
	ldr	r2, [r4, #544]
	ldr	r2, [r2, #48]
	cmp	r2, #0
	beq	.L3481
.L3482:
	mov	r3, #1
	mov	r0, r4
	strb	r3, [r6, #3487]
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3529
.L3541:
	ldrb	r3, [r6, #3492]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3485
	b	.L3499
.L3542:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3536
	ldr	r3, [r4, #224]
	ldr	r7, [r3, #24]
	cmp	r7, #0
	bne	.L3536
	add	r5, r5, #16384
	ldr	r1, .L3545+8
	mov	r0, #1
	ldr	r3, [r5, #56]
	ldr	r2, [r5, #60]
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_ClearCurrPic
	ldr	r3, [r5, #40]
	ldr	r0, [r4, #120]
	mov	r2, r7
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L3529
.L3534:
	add	r7, r5, #16384
	ldr	r2, [r7, #120]
	cmp	r2, #0
	streqb	r3, [r4, #7]
	b	.L3489
.L3543:
	ldr	r3, .L3545+12
	ldr	r8, [r3]
	cmp	r8, #0
	beq	.L3492
	ldr	r2, [r7, #2392]
	cmp	r2, #0
	beq	.L3500
.L3494:
	ldr	r3, [r2, #8]
	ldr	r0, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3494
.L3493:
	sub	r2, fp, #36
	mov	r3, #4
	ldr	r0, [r4, #120]
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	r8
	ldr	r3, [r4, #224]
	b	.L3495
.L3492:
	ldr	r3, [r4, #224]
	b	.L3495
.L3544:
	cmp	r2, #0
	beq	.L3498
	ldrb	r2, [r6, #3492]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L3498
	mov	r2, #0
	str	r2, [r4, #228]
	ldr	r3, [r7, #40]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_SetDisplay
.L3537:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L3529
.L3500:
	mov	r1, r2
	b	.L3493
.L3546:
	.align	2
.L3545:
	.word	.LC415
	.word	.LC413
	.word	.LC414
	.word	g_event_report
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
	subs	r2, r0, #0
	beq	.L3550
	add	r3, r2, #11075584
	mov	r1, #1
	add	r3, r3, #40960
	mov	ip, #0
	strb	r1, [r3, #1069]
	str	ip, [r3, #1120]
	strb	r1, [r2]
	bl	MVC_DecVDM
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	mov	r3, #12480
	ldr	r2, .L3551
	ldr	r1, .L3551+4
	mov	r0, #22
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L3550:
	movw	r2, #12468
	ldr	r1, .L3551+8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L3552:
	.align	2
.L3551:
	.word	.LANCHOR0+296
	.word	.LC416
	.word	.LC401
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
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	ip, [r1, #12]
	ldr	r3, [r1, #8]
	mov	r4, r0
	ldr	r2, [r1, #4]
	mov	r5, r1
	mov	r0, #7
	add	r6, r4, #11141120
	ldr	r1, .L3616
	str	ip, [sp]
	bl	dprint_vfmw
	add	r3, r6, #16384
	mov	r2, #0
	str	r2, [r3, #2632]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L3611
.L3554:
	ldr	r3, [r4, #232]
	cmp	r3, #0
	beq	.L3574
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3612
.L3557:
	ldr	r1, .L3616+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L3574
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L3574:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3561
	ldr	r3, [r5, #4]
	cmp	r3, #0
	beq	.L3561
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3561
	ldrb	r3, [r4, #937]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3577
	mov	r2, r4
	mov	r3, #1
	b	.L3564
.L3563:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L3575
.L3564:
	ldrb	r1, [r2, #1025]	@ zero_extendqisi2
	add	r2, r2, #88
	cmp	r1, #0
	bne	.L3563
	mov	r1, r3
.L3562:
	mov	r2, #88
	cmn	r1, #1
	mla	r3, r2, r3, r4
	mov	r0, #1
	strb	r0, [r3, #937]
	beq	.L3575
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
	b	.L3567
.L3612:
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bhi	.L3557
	ldrb	r1, [r3, #3]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L3558
	b	.L3557
.L3611:
	ldr	r3, [r3, #920]
	cmp	r3, #0
	beq	.L3554
	ldr	r3, [r4, #232]
	cmp	r3, #0
	ldrneb	r2, [r5]	@ zero_extendqisi2
	beq	.L3574
.L3558:
	strb	r2, [r3, #3]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #872]
	cmp	r2, #1
	beq	.L3613
.L3569:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3570
	ldr	r2, [r5, #4]
	cmp	r2, #0
	beq	.L3570
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3570
	ldr	r3, [r4, #232]
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bls	.L3614
.L3571:
	mov	r2, #1
	strb	r2, [r3, #3]
	ldr	r1, [r5, #16]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3616+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3608
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	r5
.L3608:
	ldr	r3, [r4, #232]
.L3567:
	ldrb	r0, [r3, #3]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3561:
	ldr	r1, .L3616+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #16]
	ldr	r0, [r4, #120]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3616+8
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L3610
.L3609:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	r5
.L3610:
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3570:
	ldr	r3, [r4, #232]
	b	.L3571
.L3613:
	ldr	r3, [r3, #920]
	cmp	r3, #0
	bne	.L3608
	b	.L3569
.L3614:
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
	bcc	.L3615
.L3572:
	add	r6, r6, #16384
	mov	r2, #1
	str	r2, [r6, #2632]
	b	.L3567
.L3615:
	mov	r0, r4
	bl	MVC_CombinePacket.part.14
	ldr	r3, [r4, #232]
	b	.L3572
.L3575:
	ldr	r1, .L3616+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_ClearAllNal
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r3, .L3616+8
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L3609
	b	.L3610
.L3577:
	mov	r1, r3
	b	.L3562
.L3617:
	.align	2
.L3616:
	.word	.LC417
	.word	.LC418
	.word	g_event_report
	.word	.LC420
	.word	.LC419
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
	mov	r8, r0
	mov	r4, r1
	mov	r0, #22
	ldr	r1, .L3651
	bl	dprint_vfmw
	mov	r0, r8
	bl	MVC_ClearCurrPic
	mov	r0, r8
	bl	MVC_ClearAllNal
	mov	r0, r8
	bl	MVC_InitDPB
	cmp	r0, #0
	bne	.L3648
.L3619:
	cmp	r4, #0
	beq	.L3620
	add	r1, r8, #584
	ldr	r0, [r8, #120]
	bl	FSP_ClearNotInVoQueue
.L3621:
	movw	r4, #48344
	mov	r10, #0
	movt	r4, 169
	add	r4, r8, r4
	mov	r6, #0
	mov	r7, #0
.L3624:
	add	r5, r4, #608
	add	r9, r4, #640
	mov	r3, #0
	mov	r2, #1
	mvn	lr, #0
	mov	ip, #18
	mov	r0, #16
	mov	r1, #2
	str	r10, [r4, #220]
	str	r4, [r4, #788]
	str	r4, [r4, #752]
	str	r4, [r4, #716]
	strb	r3, [r4, #1]
	strb	r3, [r4, #2]
	strb	r3, [r4, #3]
	str	r3, [r4, #28]
	str	r3, [r4, #20]
	str	r3, [r4, #32]
	strb	r3, [r4, #5]
	strb	r3, [r4, #712]
	str	lr, [r4, #24]
	strb	r2, [r4, #7]
	strb	r2, [r4, #748]
	str	ip, [r4, #48]
	str	r0, [r4, #52]
	strb	r1, [r4, #784]
.L3623:
	ldrd	r2, [r5, #8]!
	orrs	r1, r2, r3
	bne	.L3649
.L3622:
	cmp	r5, r9
	bne	.L3623
	add	r10, r10, #1
	add	r4, r4, #824
	cmp	r10, #40
	bne	.L3624
	movw	r9, #16352
	add	r6, r8, #11141120
	movt	r9, 170
	add	r7, r6, #16320
	add	r9, r8, r9
	mov	r4, #0
	mov	r5, #0
.L3626:
	ldrd	r2, [r7, #8]!
	orrs	r1, r2, r3
	bne	.L3650
.L3625:
	cmp	r7, r9
	bne	.L3626
	ldr	r3, [r8, #60]
	cmp	r3, #0
	beq	.L3630
	mov	r4, #0
	add	r5, r8, #524
	mov	r7, r4
.L3629:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3628
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	str	r7, [r5]
	ldr	r3, [r8, #60]
.L3628:
	cmp	r3, r4
	bhi	.L3629
.L3630:
	add	r5, r8, #11075584
	ldr	ip, .L3651+4
	add	r3, r5, #45056
	add	r5, r5, #40960
	mov	r4, #0
	movw	r0, #42024
	strb	r4, [r8, #4]
	mov	r1, r4
	strb	r4, [r8, #9]
	movw	r2, #1656
	strb	r4, [r8, #6]
	movt	r0, 169
	strb	r4, [r8, #7]
	add	r0, r8, r0
	strb	r4, [r8, #3]
	str	r4, [r8, #60]
	str	r4, [r8, #64]
	str	r4, [r8, #104]
	str	r4, [r8, #220]
	str	r4, [r8, #232]
	ldr	r7, [ip, #48]
	strb	r4, [r3, #676]
	strb	r4, [r5, #2768]
	strb	r4, [r3, #677]
	strb	r4, [r5, #2769]
	blx	r7
	add	r2, r6, #12288
	add	r6, r6, #16384
	mov	r1, #2
	mov	r3, #1
	strb	r1, [r5, #1064]
	strb	r3, [r5, #1069]
	mov	r0, r4
	strb	r4, [r2, #3480]
	mov	r3, #256
	strb	r4, [r6, #872]
	str	r4, [r6, #876]
	str	r3, [r6, #880]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3649:
	mov	r1, r2
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	strd	r6, [r5]
	b	.L3622
.L3650:
	mov	r1, r2
	ldr	r0, [r8, #120]
	bl	FreeUsdByDec
	strd	r4, [r7]
	b	.L3625
.L3620:
	add	r0, r8, #584
	bl	ResetVoQueue
	ldr	r0, [r8, #120]
	bl	FSP_EmptyInstance
	b	.L3621
.L3648:
	movw	r3, #343
	ldr	r2, .L3651+8
	ldr	r1, .L3651+12
	mov	r0, #22
	bl	dprint_vfmw
	b	.L3619
.L3652:
	.align	2
.L3651:
	.word	.LC421
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+316
	.word	.LC412
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
	ldr	r3, [r3, #2924]
	mov	r6, r1
	cmp	r3, #0
	ldreq	r2, .L3754
	streq	r3, [r2, #-1884]
	cmp	r9, #1
	beq	.L3656
	bcc	.L3657
	cmp	r9, #2
	beq	.L3658
	mov	r2, r9
	ldr	r1, .L3754+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	mov	r1, #1
	bl	MVC_ClearAll
	mov	r0, #0
.L3662:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3658:
	ldr	r3, [r4, #656]
	mov	r2, #3
	strb	r2, [r3, #712]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r3, r1, asl #2
	beq	.L3678
	add	r8, r0, r3
	add	r2, r8, #11075584
	str	r2, [fp, #-64]
	add	r7, r2, #45056
	ldr	r2, [r7, #2728]
	cmp	r2, #0
	beq	.L3678
	strb	r9, [r2, #784]
	ldr	r3, [r7, #2728]
	ldr	r2, [r4, #656]
	str	r2, [r3, #788]
	ldr	r3, [r7, #2728]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #785]
	ldr	r3, [r7, #2728]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #786]
	ldr	r3, [r7, #2728]
	ldr	r2, [r4, #688]
	str	r2, [r3, #800]
	ldr	r3, [r7, #2728]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #787]
	ldr	r3, [r7, #2728]
	ldr	r2, [r4, #708]
	str	r2, [r3, #808]
	ldr	r3, [r7, #2728]
	ldr	r1, [r3, #772]
	ldr	r2, [r3, #808]
	add	r2, r2, r1
	str	r2, [r3, #736]
	str	r2, [r3, #44]
	add	r1, r4, #16
	ldr	r2, [r7, #2728]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r7, #2728]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r7, #2728]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	orreq	r2, r2, #2
	strb	r2, [r3, #4]
	mov	r2, #640
	ldr	r3, [r7, #2728]
	add	ip, r3, #672
	add	r0, r3, #72
	ldr	r10, [r3, #656]
	ldrd	r8, [ip, #-8]
	strd	r8, [fp, #-52]
	ldrd	r8, [ip]
	strd	r8, [fp, #-60]
	ldr	r9, [r3, #660]
	bl	memcpy
	add	r3, r4, #608
	and	r2, r10, r9
	ldmdb	r3, {r0, r1}
	adds	r2, r2, #1
	and	r1, r1, r0
	movne	r2, #1
	cmn	r1, #1
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r7, #2728]
	strne	r9, [r2, #660]
	strne	r10, [r2, #656]
	add	r2, r4, #624
	ldrd	r0, [r3]
	ldrd	r8, [fp, #-52]
	ldr	r3, [r7, #2728]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r3, r3, #672
	movhi	r0, r8
	movhi	r1, r9
	ldrd	r8, [fp, #-60]
	strd	r0, [r3, #-8]
	ldrd	r0, [r2, #-8]
	ldr	r3, [r7, #2728]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r3, r3, #672
	movhi	r0, r8
	movhi	r1, r9
	strd	r0, [r3]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3690
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3690
.L3691:
	ldr	r3, [fp, #-64]
	add	r8, r3, #45056
	ldr	r2, [r8, #2728]
	ldrb	r3, [r2, #787]	@ zero_extendqisi2
	ldrb	r1, [r2, #751]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r8, #2728]
	ldr	r2, [r4, #704]
	str	r2, [r3, #804]
	ldr	r2, [r8, #2728]
	ldr	r3, [r2, #804]
	ldr	r1, [r2, #768]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r2, #36]
	ldr	r0, [r8, #2728]
	bl	MVC_CombineFldsToFrm
	ldr	r2, [r8, #2728]
	ldrb	r1, [r4, #11]	@ zero_extendqisi2
	movw	r3, #28418
	movt	r3, 42
	strb	r1, [r2, #13]
	ldrb	r1, [r4, #10]	@ zero_extendqisi2
	ldr	r2, [r8, #2728]
	strb	r1, [r2, #11]
	ldr	r2, [r8, #2728]
	ldr	r1, [r2, #52]
	ldr	r2, [r2, #800]
	add	r3, r1, r3
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3677
.L3657:
	add	r3, r0, r1, lsl #2
	ldr	r2, [r4, #656]
	add	r10, r3, #11075584
	mov	r3, #3
	add	r7, r10, #45056
	str	r2, [r7, #2728]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r2, #1]
	ldr	r2, [r7, #2728]
	strb	r3, [r2, #2]
	ldr	r1, [r4, #656]
	ldr	r2, [r7, #2728]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #656]
	ldr	r2, [r7, #2728]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	ldr	r2, [r7, #2728]
	cmp	r1, #0
	beq	.L3753
.L3659:
	strb	r3, [r2, #3]
	add	r1, r4, #16
	ldr	r3, [r7, #2728]
	mov	r2, #640
	ldr	r0, [r4, #732]
	mov	r8, #0
	str	r0, [r3, #48]
	ldr	r0, [r7, #2728]
	add	r0, r0, #72
	bl	memcpy
	ldr	r2, [r7, #2728]
	ldr	r0, [r4, #708]
	add	r3, r10, #45056
	mov	lr, #1
	ldr	r1, .L3754
	mov	ip, #2
	str	r0, [r2, #736]
	str	r0, [r2, #44]
	ldr	r2, [r7, #2728]
	ldr	r0, [r4, #656]
	str	r0, [r2, #788]
	str	r0, [r2, #752]
	str	r0, [r2, #716]
	ldr	r2, [r7, #2728]
	ldr	r0, [r4, #668]
	str	r0, [r2, #28]
	ldr	r2, [r7, #2728]
	ldr	r0, [r4, #664]
	str	r0, [r2, #20]
	ldr	r2, [r7, #2728]
	strb	r8, [r2, #712]
	ldr	r2, [r7, #2728]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	strb	r0, [r2, #713]
	ldr	r2, [r7, #2728]
	ldrb	r0, [r4, #5]	@ zero_extendqisi2
	strb	r0, [r2, #714]
	ldr	r2, [r7, #2728]
	ldrb	r0, [r4, #12]	@ zero_extendqisi2
	strb	r0, [r2, #715]
	strb	r0, [r2]
	ldr	r2, [r7, #2728]
	ldrb	r0, [r4, #9]	@ zero_extendqisi2
	str	r0, [r2, #40]
	ldr	r2, [r7, #2728]
	ldr	r0, [r4, #676]
	str	r0, [r2, #32]
	ldr	r0, [r4, #680]
	ldr	r2, [r7, #2728]
	str	r0, [r2, #728]
	ldr	r0, [r4, #684]
	ldr	r2, [r7, #2728]
	str	r0, [r2, #764]
	ldr	r0, [r4, #688]
	ldr	r2, [r7, #2728]
	str	r0, [r2, #800]
	ldr	r0, [r4, #692]
	ldr	r2, [r7, #2728]
	str	r0, [r2, #36]
	ldr	r0, [r4, #696]
	ldr	r2, [r7, #2728]
	str	r0, [r2, #732]
	ldr	r0, [r4, #700]
	ldr	r2, [r7, #2728]
	str	r0, [r2, #768]
	ldr	r0, [r4, #704]
	ldr	r2, [r7, #2728]
	str	r0, [r2, #804]
	ldrb	r2, [r4, #7]	@ zero_extendqisi2
	ldr	r0, [r7, #2728]
	cmp	r2, lr
	mov	r2, r8
	moveq	r9, #3
	strb	r9, [r0, #4]
	ldr	r7, [r3, #2728]
	mov	r0, r5
	ldr	r9, [r4, #736]
	str	r9, [r7, #56]
	ldr	r7, [r3, #2728]
	ldr	r9, [r4, #740]
	str	r9, [r7, #60]
	ldr	r7, [r3, #2728]
	ldrb	r9, [r4, #11]	@ zero_extendqisi2
	strb	r9, [r7, #13]
	strb	r9, [r7, #12]
	ldrb	r10, [r4, #10]	@ zero_extendqisi2
	ldr	r9, [r3, #2728]
	ldr	r7, [r1, #-1884]
	strb	r10, [r9, #11]
	strb	r10, [r9, #10]
	ldr	r9, [r3, #2728]
	str	r7, [r9, #64]
	add	r7, r7, lr
	ldr	r3, [r3, #2728]
	str	r7, [r1, #-1884]
	ldrb	r9, [r3, #713]	@ zero_extendqisi2
	ldr	r1, [r3, #716]
	ldrb	r7, [r3, #714]	@ zero_extendqisi2
	strb	lr, [r3, #748]
	strb	ip, [r3, #784]
	ldr	lr, [r3, #736]
	ldrb	ip, [r3, #715]	@ zero_extendqisi2
	strb	r9, [r3, #749]
	strb	r9, [r3, #785]
	strb	r7, [r3, #750]
	strb	r7, [r3, #786]
	str	lr, [r3, #772]
	str	lr, [r3, #808]
	strb	ip, [r3, #751]
	strb	ip, [r3, #787]
	str	r1, [r3, #752]
	str	r1, [r3, #788]
	ldr	r1, [r4, #656]
	bl	MVC_GetAPC
	cmp	r0, #0
	movne	r3, r0
	movwne	r2, #2143
	movne	r0, r8
	bne	.L3751
.L3677:
	movw	r3, #28330
	movt	r3, 42
	add	r3, r6, r3
	ldr	r3, [r5, r3, asl #2]
	ldrb	r0, [r3, #3]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L3662
	ldr	r0, [r5, #120]
	mov	r2, #1
	ldrsb	r1, [r3, #6]
	bl	FSP_SetRef
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3656:
	ldr	r3, [r4, #656]
	mov	r2, #3
	strb	r2, [r3, #712]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r3, r1, asl #2
	beq	.L3663
	add	r8, r0, r3
	add	r2, r8, #11075584
	str	r2, [fp, #-64]
	add	r7, r2, #45056
	ldr	r2, [r7, #2728]
	cmp	r2, #0
	beq	.L3663
	strb	r9, [r2, #748]
	ldr	r3, [r7, #2728]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #751]
	ldr	r3, [r7, #2728]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #749]
	ldr	r3, [r7, #2728]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #750]
	ldr	r3, [r7, #2728]
	ldr	r2, [r4, #684]
	str	r2, [r3, #764]
	ldr	r3, [r7, #2728]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strb	r2, [r3, #751]
	ldr	r3, [r7, #2728]
	ldr	r2, [r4, #708]
	str	r2, [r3, #772]
	ldr	r3, [r7, #2728]
	ldr	r1, [r3, #772]
	ldr	r2, [r3, #808]
	add	r2, r2, r1
	str	r2, [r3, #736]
	str	r2, [r3, #44]
	add	r1, r4, #16
	ldr	r2, [r7, #2728]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2, #1]
	ldr	r2, [r7, #2728]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r7, #2728]
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	orreq	r2, r2, #1
	strb	r2, [r3, #4]
	mov	r2, #640
	ldr	r3, [r7, #2728]
	add	ip, r3, #672
	add	r0, r3, #72
	ldr	r10, [r3, #656]
	ldrd	r8, [ip, #-8]
	strd	r8, [fp, #-52]
	ldrd	r8, [ip]
	strd	r8, [fp, #-60]
	ldr	r9, [r3, #660]
	bl	memcpy
	add	r3, r4, #608
	and	r2, r10, r9
	ldmdb	r3, {r0, r1}
	adds	r2, r2, #1
	and	r1, r1, r0
	movne	r2, #1
	cmn	r1, #1
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r7, #2728]
	strne	r9, [r2, #660]
	strne	r10, [r2, #656]
	add	r2, r4, #624
	ldrd	r0, [r3]
	ldrd	r8, [fp, #-52]
	ldr	r3, [r7, #2728]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r3, r3, #672
	movhi	r0, r8
	movhi	r1, r9
	ldrd	r8, [fp, #-60]
	strd	r0, [r3, #-8]
	ldrd	r0, [r2, #-8]
	ldr	r3, [r7, #2728]
	cmp	r1, r9
	cmpeq	r0, r8
	add	r3, r3, #672
	movhi	r0, r8
	movhi	r1, r9
	strd	r0, [r3]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3674
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3674
.L3675:
	ldr	r3, [fp, #-64]
	add	r8, r3, #45056
	ldr	r2, [r8, #2728]
	ldrb	r3, [r2, #787]	@ zero_extendqisi2
	ldrb	r1, [r2, #751]	@ zero_extendqisi2
	cmp	r3, r1
	movcc	r3, r1
	strb	r3, [r2]
	ldr	r3, [r8, #2728]
	ldr	r2, [r4, #700]
	str	r2, [r3, #768]
	ldr	r2, [r8, #2728]
	ldr	r3, [r2, #804]
	ldr	r1, [r2, #768]
	cmp	r3, r1
	movge	r3, r1
	str	r3, [r2, #36]
	ldr	r3, [r8, #2728]
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	strb	r2, [r3, #12]
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	ldr	r3, [r8, #2728]
	strb	r2, [r3, #10]
	ldr	r0, [r8, #2728]
	bl	MVC_CombineFldsToFrm
	ldr	r2, [r8, #2728]
	movw	r3, #28402
	movt	r3, 42
	ldr	r1, [r2, #52]
	ldr	r2, [r2, #764]
	add	r3, r1, r3
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3677
.L3663:
	add	r7, r5, r3
	ldr	r2, [r4, #656]
	add	r7, r7, #11075584
	mov	r1, #1
	add	r3, r7, #45056
	str	r2, [r3, #2728]
	strb	r1, [r2, #748]
	ldr	r2, [r3, #2728]
	ldr	r0, [r4, #656]
	str	r0, [r2, #752]
	ldr	r2, [r3, #2728]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	strb	r0, [r2, #749]
	ldr	r2, [r3, #2728]
	ldrb	r0, [r4, #5]	@ zero_extendqisi2
	strb	r0, [r2, #750]
	ldr	r2, [r3, #2728]
	ldr	r0, [r4, #684]
	str	r0, [r2, #764]
	ldr	r2, [r3, #2728]
	ldrb	r0, [r4, #12]	@ zero_extendqisi2
	strb	r0, [r2, #751]
	ldr	r2, [r3, #2728]
	ldr	r0, [r4, #708]
	str	r0, [r2, #772]
	ldr	r2, [r3, #2728]
	ldr	r0, [r2, #772]
	str	r0, [r2, #736]
	str	r0, [r2, #44]
	ldr	r2, [r3, #2728]
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	strb	r0, [r2, #1]
	ldr	r2, [r3, #2728]
	strb	r1, [r2, #2]
	ldr	r1, [r4, #656]
	ldr	r2, [r3, #2728]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #656]
	ldr	r2, [r3, #2728]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3665
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3665
.L3666:
	add	r7, r7, #45056
	mov	r8, #0
	mov	r2, #640
	add	r1, r4, #16
	ldr	r3, [r7, #2728]
	str	r8, [r3, #40]
	ldr	r0, [r7, #2728]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r7, #2728]
	ldr	r1, [r4, #732]
	mov	r2, #1
	ldr	ip, .L3754
	mov	r0, r5
	str	r1, [r3, #48]
	ldr	r3, [r7, #2728]
	ldr	r1, [r4, #664]
	str	r1, [r3, #20]
	ldr	r3, [r7, #2728]
	ldr	r1, [r4, #676]
	str	r1, [r3, #32]
	ldr	r3, [r7, #2728]
	ldr	r1, [r4, #692]
	str	r1, [r3, #36]
	ldr	r3, [r7, #2728]
	ldrb	r1, [r4, #12]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r7, #2728]
	ldr	r1, [r4, #700]
	str	r1, [r3, #768]
	ldr	r3, [r7, #2728]
	ldr	r1, [r4, #736]
	str	r1, [r3, #56]
	ldr	r3, [r7, #2728]
	ldr	r1, [r4, #740]
	str	r1, [r3, #60]
	ldr	r3, [r7, #2728]
	ldrb	r1, [r4, #11]	@ zero_extendqisi2
	strb	r1, [r3, #12]
	ldr	r3, [r7, #2728]
	ldrb	r1, [r4, #10]	@ zero_extendqisi2
	strb	r1, [r3, #10]
	ldr	r3, [ip, #-1884]
	ldr	r1, [r7, #2728]
	str	r3, [r1, #64]
	add	r3, r3, r2
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldr	lr, [r7, #2728]
	str	r3, [ip, #-1884]
	rsb	r3, r2, r1
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [lr, #4]
	ldr	r1, [r4, #656]
	bl	MVC_GetAPC
	cmp	r0, #0
	beq	.L3677
	mov	r3, r0
	movw	r2, #2206
	mov	r0, r8
.L3751:
	ldr	r1, .L3754+8
	bl	dprint_vfmw
	mov	r0, r5
	mvn	r1, #0
	bl	MVC_ClearDPB
	mvn	r0, #0
	b	.L3662
.L3678:
	add	r7, r5, r3
	ldr	r2, [r4, #656]
	add	r7, r7, #11075584
	mov	r1, #2
	add	r3, r7, #45056
	str	r2, [r3, #2728]
	strb	r1, [r2, #784]
	ldr	r2, [r3, #2728]
	ldr	r0, [r4, #656]
	str	r0, [r2, #788]
	ldr	r2, [r3, #2728]
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	strb	r0, [r2, #785]
	ldr	r2, [r3, #2728]
	ldrb	r0, [r4, #5]	@ zero_extendqisi2
	strb	r0, [r2, #786]
	ldr	r2, [r3, #2728]
	ldr	r0, [r4, #688]
	str	r0, [r2, #800]
	ldr	r2, [r3, #2728]
	ldrb	r0, [r4, #12]	@ zero_extendqisi2
	strb	r0, [r2, #787]
	ldr	r2, [r3, #2728]
	ldr	r0, [r4, #708]
	str	r0, [r2, #808]
	ldr	r2, [r3, #2728]
	ldr	r0, [r2, #772]
	str	r0, [r2, #736]
	str	r0, [r2, #44]
	ldr	r2, [r3, #2728]
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	strb	r0, [r2, #1]
	ldr	r2, [r3, #2728]
	strb	r1, [r2, #2]
	ldr	r1, [r4, #656]
	ldr	r2, [r3, #2728]
	ldrb	r1, [r1, #5]	@ zero_extendqisi2
	strb	r1, [r2, #5]
	ldr	r1, [r4, #656]
	ldr	r2, [r3, #2728]
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	strb	r1, [r2, #7]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3680
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3680
.L3681:
	add	r7, r7, #45056
	mov	r8, #0
	mov	r2, #640
	add	r1, r4, #16
	ldr	r3, [r7, #2728]
	str	r8, [r3, #40]
	ldr	r0, [r7, #2728]
	add	r0, r0, #72
	bl	memcpy
	ldr	r3, [r7, #2728]
	ldr	ip, [r4, #732]
	mov	r2, #2
	ldr	r1, .L3754
	mov	r0, r5
	str	ip, [r3, #48]
	ldr	r3, [r7, #2728]
	ldr	ip, [r4, #664]
	str	ip, [r3, #20]
	ldr	r3, [r7, #2728]
	ldr	ip, [r4, #676]
	str	ip, [r3, #32]
	ldr	r3, [r7, #2728]
	ldr	ip, [r4, #692]
	str	ip, [r3, #36]
	ldr	r3, [r7, #2728]
	ldrb	ip, [r4, #12]	@ zero_extendqisi2
	strb	ip, [r3, #787]
	strb	ip, [r3]
	ldr	r3, [r7, #2728]
	ldr	ip, [r4, #704]
	str	ip, [r3, #804]
	ldr	r3, [r7, #2728]
	ldr	ip, [r4, #736]
	str	ip, [r3, #56]
	ldr	r3, [r7, #2728]
	ldr	ip, [r4, #740]
	str	ip, [r3, #60]
	ldr	r3, [r7, #2728]
	ldrb	ip, [r4, #11]	@ zero_extendqisi2
	strb	ip, [r3, #13]
	ldrb	ip, [r4, #10]	@ zero_extendqisi2
	ldr	r3, [r7, #2728]
	strb	ip, [r3, #11]
	ldr	ip, [r7, #2728]
	ldr	r3, [r1, #-1884]
	str	r3, [ip, #64]
	add	r3, r3, #1
	ldrb	lr, [r4, #7]	@ zero_extendqisi2
	ldr	ip, [r7, #2728]
	cmp	lr, #1
	str	r3, [r1, #-1884]
	moveq	r9, r2
	movne	r9, r8
	strb	r9, [ip, #4]
	ldr	r1, [r4, #656]
	bl	MVC_GetAPC
	cmp	r0, #0
	movne	r3, r0
	movwne	r2, #2331
	movne	r0, r8
	beq	.L3677
	b	.L3751
.L3753:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #3
	b	.L3659
.L3680:
	ldr	r2, [r3, #2728]
	mov	r1, #2
	strb	r1, [r2, #3]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #1
	ldreq	r3, [r3, #2728]
	ldreq	r2, [r4, #668]
	streq	r2, [r3, #28]
	b	.L3681
.L3665:
	ldr	r2, [r3, #2728]
	mov	r1, #1
	strb	r1, [r2, #3]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, r1
	ldreq	r3, [r3, #2728]
	ldreq	r2, [r4, #668]
	streq	r2, [r3, #28]
	b	.L3666
.L3674:
	ldr	r2, [r7, #2728]
	ldrb	r3, [r2, #3]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #3]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r7, #2728]
	ldreq	r2, [r4, #668]
	streq	r2, [r3, #28]
	b	.L3675
.L3690:
	ldr	r2, [r7, #2728]
	ldrb	r3, [r2, #3]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #3]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r7, #2728]
	ldreq	r2, [r4, #668]
	streq	r2, [r3, #28]
	b	.L3691
.L3755:
	.align	2
.L3754:
	.word	.LANCHOR3
	.word	.LC423
	.word	.LC422
	UNWIND(.fnend)
	.size	MVC_InsertFrmInDPB, .-MVC_InsertFrmInDPB
	.align	2
	.global	MVC_AllocFrameStore
	.type	MVC_AllocFrameStore, %function
MVC_AllocFrameStore:
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
	add	r3, r0, #11075584
	add	r2, r3, #40960
	mov	r10, r0
	str	r2, [fp, #-56]
	ldrb	r8, [r2, #1065]	@ zero_extendqisi2
	str	r1, [fp, #-52]
	cmp	r8, #0
	beq	.L3757
	ldrb	r2, [r2, #1066]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r8, #2
	moveq	r8, #1
.L3757:
	ldr	r2, [fp, #-52]
	cmp	r2, #1
	ldrb	r2, [r10, #8]	@ zero_extendqisi2
	beq	.L3758
	cmp	r2, #2
	beq	.L3840
	add	r2, r10, #11141120
	str	r2, [fp, #-48]
	mov	r1, r2
	sub	r2, r8, #1
	add	r9, r1, #12288
	cmp	r2, #1
	mov	r2, #0
	strb	r2, [r9, #3481]
	bls	.L3841
.L3780:
	mov	lr, #0
	strb	lr, [r9, #3480]
	ldr	r7, [r10, #48]
	cmp	r7, lr
	beq	.L3787
	movw	r4, #48344
	movw	r5, #47784
	movt	r4, 169
	movt	r5, 169
	add	r6, r3, #45056
	add	r4, r10, r4
	add	r5, r10, r5
.L3786:
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3782
	cmp	r4, #0
	beq	.L3783
	ldr	r0, [r6, #2920]
	cmp	r0, #0
	beq	.L3783
	ldr	r2, [r6, #2728]
	rsb	r3, r4, r2
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L3782
	mov	r1, r5
	b	.L3784
.L3785:
	ldr	r2, [r1, #4]!
	rsb	ip, r4, r2
	cmp	r2, #0
	clz	ip, ip
	mov	ip, ip, lsr #5
	moveq	ip, #0
	cmp	ip, #0
	bne	.L3782
.L3784:
	add	r3, r3, #1
	cmp	r3, r0
	bne	.L3785
.L3783:
	mov	r5, #824
	ldr	r3, [fp, #-48]
	mla	r5, r5, lr, r10
	add	r6, r3, #16384
	movw	r1, #48416
	add	r0, r9, #3488
	mov	r7, #0
	mov	r3, #1
	add	r2, r5, #11075584
	strb	r3, [r9, #3480]
	add	r2, r2, #48384
	str	r4, [r6, #40]
	movt	r1, 169
	add	r0, r0, #8
	str	r7, [r2, #4]
	add	r1, r5, r1
	mov	r2, #101
	str	r2, [r6, #92]
	mov	r2, #640
	str	r3, [fp, #-48]
	bl	memcpy
	movw	r2, #48344
	movt	r2, 169
	add	r2, r5, r2
	str	r7, [r9, #3648]
	strb	r7, [r2, #4]
	strb	r7, [r4, #7]
	ldr	r2, [r6, #40]
	ldr	r3, [fp, #-48]
	strb	r7, [r2, #3]
	ldr	r2, [r6, #40]
	strb	r3, [r2, #5]
	ldr	r3, [r6, #40]
	str	r7, [r3, #16]
	ldrb	r3, [r9, #3480]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3787
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	ldr	r0, [r10, #120]
	clz	r1, r3
	mov	r1, r1, lsr #5
	bl	FSP_NewLogicFs
	mov	r4, r0
	mov	r1, r0
	ldr	r0, [r10, #120]
	bl	FSP_GetLogicFs
	mvn	r2, r4
	mov	r2, r2, lsr #31
	ldr	r3, [fp, #-48]
	cmp	r0, #0
	mov	r5, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L3788
	ldr	r3, [r10, #224]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L3842
.L3789:
	ldr	r7, .L3849
	mov	r2, #640
	ldr	r0, [r6, #40]
	add	r1, r5, #40
	ldr	r3, [r7, #52]
	add	r0, r0, #72
	blx	r3
	ldr	r1, [r6, #40]
	movw	r0, #15784
	ldr	r3, [r7, #52]
	movt	r0, 170
	add	r1, r1, #72
	add	r0, r10, r0
	mov	r2, #640
	blx	r3
	ldr	r3, [r6, #40]
	strb	r4, [r3, #6]
	ldrsb	r3, [r5, #4]
	str	r3, [r6, #116]
.L3779:
	ldr	r3, [fp, #-52]
	uxtb	r2, r8
	strb	r2, [r9, #3483]
	cmp	r3, #1
	moveq	r0, #0
	beq	.L3833
	ldr	r3, [fp, #-56]
	ldr	r1, [r6, #40]
	ldrb	r3, [r3, #1065]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #3
	strb	r3, [r1, #712]
	ldrb	r3, [r9, #3481]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3843
	strb	r2, [r6, #872]
	cmp	r8, #0
	ldr	r2, [fp, #-56]
	movne	r0, #0
	moveq	r0, r8
	ldr	r3, [r2, #1092]
	str	r3, [r6, #880]
	ldrb	r3, [r2, #1072]	@ zero_extendqisi2
	str	r3, [r6, #876]
	ldr	r3, [r10, #128]
	str	r3, [r6, #884]
	ldr	r3, [r2, #2704]
	str	r4, [r6, #888]
	streqb	r8, [r6, #873]
	str	r3, [r6, #896]
	movne	r3, #1
	strneb	r3, [r6, #873]
.L3833:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3782:
	add	lr, lr, #1
	add	r4, r4, #824
	cmp	lr, r7
	bne	.L3786
.L3787:
	ldr	r1, .L3849+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r10
	mov	r1, #1
	bl	MVC_ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3840:
	add	r9, r10, #11141120
	str	r9, [fp, #-48]
	add	r9, r9, #12288
.L3777:
	mov	r2, #0
	strb	r2, [r9, #3481]
	b	.L3780
.L3758:
	cmp	r2, #2
	beq	.L3844
	add	r2, r10, #11141120
	str	r2, [fp, #-48]
	mov	r1, r2
	add	r9, r1, #12288
	mov	r2, #0
	mov	r8, r2
	strb	r2, [r9, #3481]
	b	.L3780
.L3842:
	ldr	r3, [r10, #16]
	ldr	r1, [r0, #152]
	ldr	r2, [r10, #12]
	mov	r3, r3, asl #4
	str	r3, [r0, #112]
	ldr	r0, [r0, #76]
	mul	r3, r1, r3
	mov	r2, r2, asl #4
	str	r2, [r5, #108]
	add	r0, r3, r0
	str	r0, [r5, #80]
	str	r3, [fp, #-48]
	bl	MEM_Phy2Vir
	ldr	r1, [r5, #60]
	ldr	r3, [fp, #-48]
	ldr	r2, [r5, #156]
	add	r3, r3, r1
	str	r7, [r5, #556]
	str	r3, [r5, #64]
	add	r3, r3, r2
	str	r3, [r5, #72]
	str	r0, [r5, #552]
	b	.L3789
.L3841:
	add	r6, r1, #16384
	ldrb	r2, [r6, #872]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3761
	ldr	r1, [fp, #-56]
	ldr	r0, [r6, #896]
	ldr	r1, [r1, #2704]
	cmp	r0, r1
	beq	.L3762
.L3761:
	add	r2, r3, #45056
	ldr	r0, [r2, #2920]
	subs	r2, r0, #1
	bmi	.L3780
	movw	r1, #28330
	ldr	lr, [fp, #-56]
	movt	r1, 42
	add	r1, r0, r1
	add	r1, r10, r1, lsl #2
	b	.L3773
.L3764:
	cmp	r8, #2
	beq	.L3845
.L3763:
	subs	r2, r2, #1
	bmi	.L3780
.L3773:
	ldr	r4, [r1, #-4]!
	cmp	r4, #0
	beq	.L3763
	cmp	r8, #1
	bne	.L3764
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	cmp	r0, #2
	bne	.L3763
.L3765:
	ldr	ip, [lr, #1092]
	ldr	r0, [r4, #20]
	cmp	ip, r0
	bne	.L3763
	ldr	ip, [lr, #2704]
	ldr	r0, [r4, #56]
	cmp	ip, r0
	bne	.L3763
	ldrb	r0, [lr, #1072]	@ zero_extendqisi2
	cmp	r0, #0
	ldrb	r0, [r4, #3]	@ zero_extendqisi2
	beq	.L3846
	cmp	r0, #0
	beq	.L3763
.L3769:
	add	r0, r9, #3488
	mov	r2, #1
	add	r1, r4, #72
	strb	r2, [r9, #3481]
	add	r0, r0, #8
	mov	r2, #640
	str	r4, [r6, #40]
	str	r3, [fp, #-60]
	bl	memcpy
	ldrsb	r1, [r4, #6]
	ldr	r0, [r10, #120]
	bl	FSP_GetLogicFs
	ldr	r3, [fp, #-60]
	subs	r2, r0, #0
	beq	.L3847
	ldrsb	r2, [r2, #4]
	str	r2, [r6, #116]
	ldrb	r2, [r9, #3481]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3780
	ldr	r2, [r6, #40]
	cmp	r2, #0
	beq	.L3780
.L3837:
	mov	r4, #0
	b	.L3779
.L3845:
	ldrb	r0, [r4, #2]	@ zero_extendqisi2
	cmp	r0, #1
	bne	.L3763
	b	.L3765
.L3843:
	ldr	r1, [fp, #-56]
	mov	r3, #0
	strb	r3, [r6, #872]
	mov	r0, r3
	ldr	r2, [r1, #1092]
	str	r2, [r6, #880]
	ldrb	r2, [r1, #1072]	@ zero_extendqisi2
	str	r2, [r6, #876]
	ldr	r2, [r10, #128]
	strb	r3, [r6, #873]
	str	r4, [r6, #888]
	str	r2, [r6, #884]
	ldr	r3, [r1, #2704]
	str	r3, [r6, #896]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3844:
	add	r9, r10, #11141120
	mov	r8, #0
	str	r9, [fp, #-48]
	add	r9, r9, #12288
	b	.L3777
.L3846:
	cmp	r0, #0
	bne	.L3763
	b	.L3769
.L3762:
	sub	r4, r8, #2
	cmp	r2, #1
	cmpeq	r8, #2
	clz	r4, r4
	mov	r4, r4, lsr #5
	beq	.L3774
	cmp	r8, #1
	cmpeq	r2, #2
	bne	.L3780
.L3774:
	ldr	r2, [fp, #-56]
	ldr	r1, [r6, #880]
	ldr	r2, [r2, #1092]
	cmp	r1, r2
	bne	.L3780
	ldr	r2, [fp, #-56]
	ldrb	r2, [r2, #1072]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [r6, #876]
	bne	.L3775
	cmp	r2, #0
	bne	.L3780
.L3776:
	ldr	r2, [r10, #128]
	ldr	r1, [r10, #124]
	rsb	r2, r1, r2
	cmp	r2, #2
	bhi	.L3780
	mov	r2, #1
	strb	r2, [r9, #3481]
	ldr	r2, [r6, #40]
	cmp	r2, #0
	beq	.L3777
	cmp	r4, #0
	bne	.L3848
	cmp	r8, #1
	bne	.L3779
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L3777
	b	.L3779
.L3788:
	strb	r2, [r9, #3480]
	mov	r0, r2
	ldr	ip, [r6, #40]
	ldr	r1, .L3849+8
	str	r3, [fp, #-48]
	strb	r2, [ip, #5]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	mov	r0, r10
	mov	r1, r3
	bl	MVC_ClearAll
	mvn	r0, #0
	b	.L3833
.L3847:
	movw	r2, #6386
	ldr	r1, .L3849+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3833
.L3848:
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L3777
	b	.L3837
.L3775:
	cmp	r2, #0
	beq	.L3780
	b	.L3776
.L3850:
	.align	2
.L3849:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC425
	.word	.LC426
	.word	.LC424
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r1
	mov	r6, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L3861
	ldr	r8, .L3865
	movw	r2, #19032
	ldr	r7, [r0, #928]
	movt	r2, 170
	mov	r1, r4
	ldr	r3, [r8, #48]
	blx	r3
	add	r0, r6, #584
	str	r7, [r6, #928]
	bl	ResetVoQueue
	str	r4, [r6, #228]
	strb	r4, [r6]
	mov	r4, #2240
	str	r5, [r6, #224]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	ldreq	r3, [r5, #708]
	movne	r3, #32
	movne	r2, #256
	strne	r3, [r6, #36]
	movne	r3, #136
	streq	r3, [r6, #36]
	ldreq	r3, [r5, #712]
	streq	r3, [r6, #40]
	ldreq	r3, [r5, #700]
	str	r3, [r6, #32]
	strne	r2, [r6, #40]
	ldr	r0, [r5, #592]
	bl	MEM_Phy2Vir
	ldr	ip, [r6, #36]
	ldr	r3, [r6, #224]
	movw	r2, #3992
	ldr	r1, [r6, #40]
	mul	r2, r2, ip
	ldr	r3, [r3, #588]
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
	bne	.L3862
	ldr	r5, [r5, #624]
	cmp	r5, #0
	beq	.L3863
.L3857:
	add	r3, r6, #11075584
	movw	r2, #4060
	add	lr, r3, #36864
	add	r3, r3, #32768
	ldr	r9, [r8, #48]
	add	r4, r6, #12992
	str	r1, [lr, #1808]
	mov	r1, #0
	str	ip, [r3, #2632]
	mov	r5, r1
	ldr	r3, [r6, #32]
	add	r4, r4, #12
	movw	r7, #22860
	movt	r7, 164
	add	r7, r6, r7
	mul	r2, r2, r3
	blx	r9
	ldr	r3, [r6, #108]
	mov	r2, #9856
	mov	ip, #40
	strb	r5, [r6, #4]
	ubfx	r3, r3, #16, #2
	str	ip, [r6, #48]
	mov	r1, r5
	strb	r3, [r6, #8]
	movt	r2, 164
	strb	r5, [r6, #6]
	mov	r3, #18
	strb	r5, [r6, #7]
	mov	r0, r4
	str	r3, [r6, #52]
	str	r5, [r6, #68]
	ldr	r3, [r8, #48]
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
	str	r5, [r6, #56]
	blx	r3
	movw	r2, #8500
	ldr	r3, [r8, #48]
	mov	r0, r7
	mov	r1, r5
	movt	r2, 5
	blx	r3
	mov	r0, r4
	mov	r3, r5
.L3858:
	strb	r3, [r0]
	add	r2, r0, #274432
	add	r0, r0, #335872
	mov	r4, #0
	add	r0, r0, #308
	strb	r3, [r2, #241]
	cmp	r0, r7
	bne	.L3858
	add	r2, r6, #12288
	movw	r3, #34656
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
	beq	.L3864
	mov	r1, r4
	mov	r0, r6
	bl	MVC_ClearAll
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3863:
	mov	r0, r3
	mov	r1, r5
	ldr	r3, [r8, #48]
	blx	r3
	ldr	r2, [r6, #40]
	mov	r1, r5
	ldr	r3, [r8, #48]
	ldr	r0, [r6, #252]
	mul	r2, r4, r2
	blx	r3
	ldr	r1, [r6, #40]
	ldr	ip, [r6, #36]
	ldr	r0, [r6, #544]
	b	.L3857
.L3861:
	movw	r2, #13380
	ldr	r1, .L3865+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3862:
	movw	r3, #13416
	ldr	r2, .L3865+8
	ldr	r1, .L3865+12
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3864:
	mov	r0, r4
	ldr	r1, .L3865+16
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3866:
	.align	2
.L3865:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC427
	.word	.LANCHOR0+332
	.word	.LC428
	.word	.LC429
	UNWIND(.fnend)
	.size	MVC_DEC_Init, .-MVC_DEC_Init
	.align	2
	.global	MVC_StorePicInDpb
	.type	MVC_StorePicInDpb, %function
MVC_StorePicInDpb:
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
	add	r3, r0, #11141120
	add	r4, r0, #11075584
	add	r10, r3, #12288
	add	r2, r4, #36864
	mov	r7, #0
	str	r3, [fp, #-64]
	mov	r5, r0
	strb	r7, [r2, #4024]
	ldrb	r3, [r10, #3483]	@ zero_extendqisi2
	sub	r3, r3, #2
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r2, #4025]
	ldrb	r3, [r10, #3480]	@ zero_extendqisi2
	cmp	r3, r7
	beq	.L4035
	ldr	r3, [r0, #128]
	str	r3, [r0, #124]
	ldrb	r3, [r10, #3493]	@ zero_extendqisi2
	cmp	r3, #0
	addeq	r6, r0, #11141120
	addeq	r6, r6, #16384
	bne	.L4036
.L3870:
	ldrb	r0, [r5, #8]	@ zero_extendqisi2
	cmp	r0, #2
	beq	.L4037
	ldr	r8, [r5, #224]
	ldr	r3, [r8, #24]
	cmp	r3, #0
	bne	.L3875
	ldr	r2, [r5, #220]
	cmp	r2, #2
	beq	.L3877
	ldrb	r2, [r10, #3482]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3877
.L3947:
	ldrb	r1, [r10, #3483]	@ zero_extendqisi2
	ldr	r7, [r6, #40]
	sub	r2, r1, #1
	cmp	r2, #1
	movhi	r2, #0
	movls	r2, #1
	cmp	r1, #0
	beq	.L3879
	ldrb	r0, [r7, #2]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	ip, r2
	orrne	ip, r2, #1
	cmp	ip, #0
	beq	.L3878
	cmp	r2, #0
	beq	.L4038
.L3952:
	ldr	r2, [r5, #220]
	cmp	r2, #0
	bne	.L3882
	add	r1, r10, #3472
	mov	r3, #1
	add	r1, r1, #8
	str	r3, [r5, #220]
	mov	r2, #744
	add	r0, r6, #128
	bl	memcpy
	ldr	r3, [r8, #24]
.L3878:
	cmp	r3, #2
	beq	.L4039
.L3877:
	ldr	r3, [r6, #56]
	cmp	r3, #0
	beq	.L3909
	ldr	r3, [r5, #112]
	ldr	r2, [r6, #92]
	cmp	r3, r2
	bcs	.L3910
	ldrb	r1, [r10, #3482]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L4040
.L3910:
	mov	r0, r5
	bl	MVC_Marking
	cmp	r0, #0
	bne	.L4041
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	ldr	r1, [r6, #120]
	mov	r0, r5
	bl	MVC_RemoveUnUsedFrameStore
.L3903:
	ldrb	r3, [r10, #3481]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3913
	add	r4, r4, #45056
	ldr	ip, [r4, #2920]
.L3914:
	ldr	r3, [r6, #56]
	cmp	r3, #0
	beq	.L3923
	ldr	r2, [r4, #2928]
	ldr	r3, [r4, #2932]
	add	r1, r3, r2
	cmp	r1, ip
	bcs	.L3949
.L3923:
	mvn	r8, #0
	mov	r7, r8
	b	.L3932
.L3927:
	ldr	r2, [r6, #56]
	mov	r1, r7
	mov	r0, r5
	mov	r8, r3
	cmp	r2, #0
	bne	.L3928
	ldr	r2, [r6, #60]
	ldr	r3, [fp, #-56]
	cmp	r2, r3
	blt	.L4042
.L3928:
	bl	MVC_OutputFrmFromDPB
	cmn	r0, #1
	beq	.L3931
	ldr	ip, [r4, #2920]
.L3932:
	ldr	lr, [r4, #2924]
	sub	r3, fp, #52
	sub	r2, fp, #56
	mvn	r1, #0
	cmp	lr, ip
	mov	r0, r5
	bcc	.L3925
	bl	MVC_GetMinPOC
	cmp	r0, #0
	blt	.L4043
	ldr	r3, [r4, #2924]
	cmp	r3, r8
	ldrne	r7, [fp, #-52]
	bne	.L3927
	ldr	r2, [fp, #-52]
	cmp	r2, r7
	beq	.L4044
	mov	r7, r2
	b	.L3927
.L3875:
	ldrb	r2, [r10, #3482]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3878
	b	.L3947
.L4036:
	ldr	r3, [fp, #-64]
	add	r6, r3, #16384
	ldr	r3, [r6, #44]
	ldrb	r8, [r3, #1]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L3871
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L3870
	mov	r0, r7
	ldr	r1, .L4058
	bl	dprint_vfmw
	movw	r3, #3491
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L3909:
	ldrb	r3, [r10, #3481]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3913
	add	r4, r4, #45056
	ldr	ip, [r4, #2920]
	b	.L3923
.L4039:
	ldr	r3, [r6, #56]
	cmp	r3, #0
	beq	.L3903
	add	r4, r4, #45056
	mov	r0, r5
	bl	MVC_SimpleSlideDPB
	ldr	r1, [r4, #2920]
	cmp	r1, #0
	beq	.L3904
	ldr	r3, [r4, #2728]
	cmp	r3, #0
	beq	.L3957
	movw	r2, #47784
	mov	r3, #0
	movt	r2, 169
	add	r2, r5, r2
	b	.L3905
.L3906:
	ldr	r0, [r2, #4]!
	cmp	r0, #0
	beq	.L3957
.L3905:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3906
.L3904:
	movw	r2, #15768
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	subs	r7, r0, #0
	bne	.L4045
	ldr	r1, [r4, #2924]
	mov	r0, r5
	add	r1, r1, #1
	str	r1, [r4, #2924]
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	mov	r2, r7
	movw	r3, #3668
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3908
.L3879:
	cmp	r2, #0
	bne	.L3952
.L3885:
	cmp	r3, #0
	beq	.L3955
	movw	r8, #15768
	mov	r9, r7
	movt	r8, 170
	add	r8, r5, r8
.L3888:
	cmp	r1, #0
	bne	.L4046
.L3890:
	ldr	r3, [r8, #708]
	str	r3, [r9, #44]
.L3891:
	mov	r1, r9
	mov	r0, r5
	bl	MVC_GetImagePara
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	str	r3, [fp, #-68]
	beq	.L4047
	add	r0, r8, #608
	ldr	lr, [fp, #-68]
	add	r8, r8, #624
	ldrd	r2, [r0, #-8]
	add	r1, lr, #592
	add	ip, lr, #608
	strd	r2, [r1, #-8]
	ldrd	r2, [r0]
	strd	r2, [r1]
	ldrd	r2, [r8, #-8]
	strd	r2, [ip, #-8]
	ldr	r2, [r9, #44]
	cmp	r2, #0
	str	r2, [lr, #152]
	bne	.L3893
.L3898:
	mov	r2, #1
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
	ldr	r3, [fp, #-68]
	ldr	r0, [r5, #120]
	mov	r2, r5
	mov	r1, #15
	str	r3, [sp]
	add	r3, r5, #584
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L3895
	mov	r2, #0
	ldrsb	r1, [r9, #6]
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
.L3895:
	ldr	r3, [r5, #224]
	ldr	r3, [r3, #620]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	bcs	.L4048
	ldr	r2, [fp, #-68]
	mov	r3, #0
	str	r3, [r2, #16]
.L3901:
	ldr	r3, [r5, #136]
	add	r3, r3, #2
	str	r3, [r5, #136]
.L3889:
	ldr	r3, [r5, #220]
	cmp	r3, #2
	beq	.L3902
.L3887:
	mov	r3, #1
	str	r3, [r9, #16]
	strb	r3, [r7, #8]
.L3902:
	ldr	r3, [r5, #224]
	mov	r2, #2
	str	r2, [r5, #220]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L3877
	b	.L4039
.L3913:
	ldr	r3, [r5, #520]
	ldr	lr, [r6, #40]
	cmp	r3, #0
	rsb	r2, r3, lr
	clz	r2, r2
	mov	r2, r2, lsr #5
	moveq	r2, #0
	cmp	r2, #0
	beq	.L4049
	mov	r0, r5
	bl	MVC_DirectOutput
	cmn	r0, #1
	mov	r4, r0
	beq	.L4050
.L3919:
	movw	r3, #3720
	mov	r2, r4
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3874
.L4043:
	ldr	r1, .L4058+8
	movw	r2, #3769
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
.L3925:
	ldr	r3, [r6, #56]
	cmp	r3, #0
	beq	.L3937
	ldrb	r3, [r10, #3484]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3937
	ldr	r2, [r4, #2928]
	cmp	r2, #0
	beq	.L3937
	movw	ip, #47844
	mov	lr, r3
	movt	ip, 169
	add	ip, r5, ip
	b	.L3942
.L3939:
	ldr	r2, [r4, #2928]
	cmp	r2, r3
	bls	.L3937
.L3942:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	ldr	r1, [r6, #48]
	ldr	r0, [r2, #20]
	cmp	r0, r1
	bne	.L3939
	ldr	r0, [r2, #56]
	ldr	r1, [r6, #120]
	cmp	r0, r1
	bne	.L3939
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
	b	.L3939
.L3937:
	ldr	r1, [r4, #2920]
	cmp	r1, #0
	beq	.L3936
	ldr	r3, [r4, #2728]
	cmp	r3, #0
	beq	.L3961
	movw	r2, #47784
	mov	r3, #0
	movt	r2, 169
	add	r2, r5, r2
	b	.L3943
.L3944:
	ldr	r0, [r2, #4]!
	cmp	r0, #0
	beq	.L3961
.L3943:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3944
.L3936:
	movw	r2, #15768
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L4051
	ldr	r3, [r4, #2924]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #2924]
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
.L3908:
	mov	r4, #0
.L3946:
	ldr	r3, [fp, #-64]
	mov	r2, #0
	mov	r0, r4
	add	r3, r3, #12288
	strb	r2, [r3, #3480]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3871:
	mvn	r1, #0
	bl	MVC_FlushDPB
	cmp	r0, #0
	beq	.L3870
	mov	r0, r8
	ldr	r1, .L4058+12
	bl	dprint_vfmw
	movw	r3, #3501
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4049:
	add	r4, r4, #45056
	ldr	ip, [r4, #2920]
	cmp	ip, #0
	beq	.L3916
	ldr	r3, [r4, #2728]
	adds	r1, r3, #0
	movne	r1, #1
	cmp	lr, r3
	movne	r1, #0
	cmp	r1, #0
	movweq	r2, #47784
	movteq	r2, 169
	addeq	r2, r5, r2
	bne	.L4052
.L3920:
	add	r1, r1, #1
	cmp	r1, ip
	beq	.L3914
	ldr	r3, [r2, #4]!
	adds	r0, r3, #0
	movne	r0, #1
	cmp	lr, r3
	movne	r0, #0
	cmp	r0, #0
	beq	.L3920
.L3917:
	movw	r2, #15768
	mov	r0, r5
	movt	r2, 170
	add	r2, r5, r2
	bl	MVC_InsertFrmInDPB
	cmn	r0, #1
	mov	r4, r0
	beq	.L4053
	mov	r0, r5
	bl	MVC_UpdateReflist
	mov	r0, r5
	bl	MVC_UpdateLTReflist
	movw	r3, #3746
	mov	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3908
.L4038:
	cmp	r0, #0
	beq	.L3878
	b	.L3885
.L3961:
	mov	r1, r3
	b	.L3936
.L3931:
	mov	r3, r0
	mov	r9, r0
	movw	r2, #3809
	ldr	r1, .L4058+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, r9
	movw	r3, #3810
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
.L3951:
	ldr	r3, [r6, #40]
	mov	r2, #1
	ldr	r0, [r5, #120]
	mvn	r4, #0
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	mov	r3, r4
	movw	r2, #3867
	ldr	r1, .L4058+16
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #40]
	mov	r3, #0
	strb	r3, [r2, #5]
	ldr	r2, [r6, #40]
	strb	r3, [r2, #2]
	b	.L3946
.L4037:
	ldr	r1, .L4058+20
	bl	dprint_vfmw
	mov	r0, r5
	bl	MVC_DirectOutput
	ldr	r3, [r6, #116]
	ldr	r2, [r5, #52]
	cmp	r3, r2
	addne	r3, r3, #36
	movne	r1, #0
	addne	r3, r5, r3, lsl #2
	mov	r4, r0
	strne	r1, [r3, #4]
	strne	r2, [r6, #116]
	movw	r3, #3519
	mov	r2, r0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
.L3874:
	cmn	r4, #1
	bne	.L3946
	b	.L3951
.L3882:
	cmp	r2, #1
	beq	.L4054
	cmp	r1, #0
	beq	.L3885
	ldrb	r2, [r7, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3885
	b	.L3878
.L4042:
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4055
.L3929:
	mov	r0, r5
	bl	MVC_DirectOutput
	cmn	r0, #1
	mov	r4, r0
	beq	.L4056
.L3930:
	movw	r3, #3801
	mov	r2, r4
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3874
.L3955:
	mov	r9, r7
	b	.L3889
.L4046:
	ldrb	r3, [r8, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3890
	mov	r2, #3
	ldr	r3, [r9, #44]
	strb	r2, [r9, #2]
	ldr	r2, [r8, #708]
	add	r3, r3, r2
	str	r3, [r9, #44]
	b	.L3891
.L3893:
	ldr	r3, [fp, #-68]
	ldrb	r3, [r3, #64]	@ zero_extendqisi2
	ands	r3, r3, #3
	beq	.L4057
.L3896:
	ldr	r3, [r5, #224]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	bcs	.L3898
	ldrsb	r1, [r9, #6]
	mov	r2, #0
	ldr	r0, [r5, #120]
	bl	FSP_SetDisplay
	movw	r3, #3619
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4044:
	mov	r3, r7
	ldr	r2, .L4058+24
	ldr	r1, .L4058+28
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3778
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L3957:
	mov	r1, r3
	b	.L3904
.L4055:
	ldrb	r3, [r10, #3483]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r3, [r6, #40]
	strne	r3, [r5, #524]
	b	.L3929
.L4054:
	cmp	r3, #0
	ldr	r9, [r6, #784]
	beq	.L3887
	movw	r8, #16512
	ldrb	r1, [r6, #131]	@ zero_extendqisi2
	movt	r8, 170
	add	r8, r5, r8
	b	.L3888
.L4048:
	ldr	r1, [fp, #-68]
	mov	r0, r5
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3901
.L4035:
	mov	r0, r3
	ldr	r1, .L4058+32
	bl	dprint_vfmw
	add	r6, r5, #11141120
	movw	r3, #3477
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	add	r6, r6, #16384
	b	.L3951
.L4056:
	mov	r3, r0
	movw	r2, #3798
	ldr	r1, .L4058+16
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3930
.L4041:
	mov	r2, r0
	ldr	r1, .L4058+36
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3693
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4057:
	mov	r2, #3600
	ldr	r1, .L4058+40
	mov	r0, #1
	str	r3, [fp, #-72]
	bl	dprint_vfmw
	ldr	r2, .L4058+44
	ldr	r8, [r2]
	cmp	r8, #0
	beq	.L3897
	ldr	r3, [fp, #-72]
	mov	r1, #111
	ldr	r0, [r5, #120]
	mov	r2, r3
	blx	r8
.L3897:
	ldr	r3, [fp, #-68]
	ldr	r2, [r3, #152]
	cmp	r2, #0
	bne	.L3896
	b	.L3898
.L4051:
	mov	r3, r0
	movw	r2, #3853
	ldr	r1, .L4058+16
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3854
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4052:
	mov	r1, r2
	b	.L3917
.L3916:
	ldr	r3, [r6, #56]
	cmp	r3, #0
	beq	.L3923
	ldr	r2, [r4, #2928]
	ldr	r3, [r4, #2932]
.L3949:
	str	r3, [sp, #4]
	mov	r0, #1
	mov	r3, ip
	str	r2, [sp]
	ldr	r1, .L4058+48
	movw	r2, #3759
	bl	dprint_vfmw
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
	movw	r3, #3761
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4040:
	ldr	r1, .L4058+52
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4058+44
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L3911
	ldr	r0, [r5, #112]
	mov	r3, #8
	ldr	ip, [r6, #92]
	sub	r2, fp, #52
	mov	r1, #104
	str	r0, [fp, #-48]
	str	ip, [fp, #-52]
	ldr	r0, [r5, #120]
	blx	r4
.L3911:
	mov	r0, r5
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r5
	bl	MVC_ClearDPB
	movw	r3, #3684
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4050:
	mov	r3, r0
	movw	r2, #3716
	ldr	r1, .L4058+16
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3919
.L4045:
	mov	r3, r7
	movw	r2, #3659
	ldr	r1, .L4058+16
	mov	r0, #0
	bl	dprint_vfmw
	movw	r3, #3660
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4053:
	mov	r3, r0
	movw	r2, #3739
	ldr	r1, .L4058+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, r4
	movw	r3, #3740
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4047:
	movw	r3, #3589
	mvn	r2, #0
	ldr	r1, .L4058+4
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3951
.L4059:
	.align	2
.L4058:
	.word	.LC432
	.word	.LC431
	.word	.LC440
	.word	.LC433
	.word	.LC436
	.word	.LC434
	.word	.LANCHOR0+348
	.word	.LC441
	.word	.LC430
	.word	.LC438
	.word	.LC435
	.word	g_event_report
	.word	.LC439
	.word	.LC437
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
	ldr	r2, [r8, #2708]
	mov	r4, r3
	str	r3, [fp, #-80]
	movw	r3, #26894
	ldr	ip, [r6, #236]
	add	lr, r6, r1
	movt	r3, 42
	add	r3, r2, r3
	movw	r2, #43728
	movt	r2, 169
	add	r2, lr, r2
	add	r9, r4, #36864
	ldrb	r5, [ip, #19]	@ zero_extendqisi2
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	add	r0, r6, #11141120
	cmp	r5, #1
	mov	lr, r4
	mov	r7, r0
	str	r0, [fp, #-52]
	str	r2, [fp, #-76]
	add	r0, r6, r3, lsl #2
	ldr	r2, [r8, #1092]
	movw	r3, #43728
	add	r4, r7, #16384
	add	lr, lr, #45056
	movt	r3, 169
	add	r3, r1, r3
	str	r2, [fp, #-56]
	add	r3, r6, r3
	ldr	r2, [r9, #4064]
	ldr	r0, [r0, #4]
	str	r2, [fp, #-68]
	moveq	r2, #2
	movne	r2, #0
	str	r2, [fp, #-60]
	ldr	r2, [r9, #4068]
	str	r2, [fp, #-72]
	ldr	r2, [ip, #2896]
	str	r3, [r4, #44]
	ldr	r5, [lr, #2924]
	cmp	r5, #0
	beq	.L4075
	add	r2, r2, #4
	mov	r7, #1
	mov	r3, r7, asl r2
	add	r0, r0, r7
	str	r3, [fp, #-64]
	mov	r1, r3
	bl	__aeabi_uidivmod
	mov	r3, #0
	mov	r0, #2
	str	r3, [r9, #4068]
	str	r3, [r9, #4064]
	mov	r5, r1
	ldr	r1, .L4078
	bl	dprint_vfmw
	ldr	r10, [fp, #-56]
	mov	r3, r5
	ldr	r1, .L4078+4
	mov	r0, #2
	mov	r2, r10
	bl	dprint_vfmw
	cmp	r10, r5
	bgt	.L4068
	b	.L4069
.L4066:
	mov	r3, #0
	mov	r0, r6
	strb	r3, [r10, #3484]
	bl	MVC_StorePicInDpb
	movw	r2, #26894
	movt	r2, 42
	ldr	r1, [fp, #-64]
	subs	r3, r0, #0
	add	r0, r5, #1
	bne	.L4076
	ldr	r3, [r8, #2708]
	add	r2, r3, r2
	add	r2, r6, r2, lsl #2
	str	r5, [r2, #4]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-56]
	cmp	r3, r1
	mov	r5, r1
	ble	.L4069
.L4068:
	mov	r1, #1
	mov	r0, r6
	bl	MVC_AllocFrameStore
	ldr	r3, [fp, #-52]
	ldr	r1, .L4078+8
	add	r10, r3, #12288
	subs	r2, r0, #0
	mov	r0, #2
	bne	.L4077
	str	r2, [fp, #-48]
	bl	dprint_vfmw
	strb	r7, [r10, #3486]
	ldr	r1, [r4, #40]
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-60]
	str	r5, [r1, #20]
	ldr	r1, [r4, #40]
	str	r5, [r4, #48]
	str	r5, [r1, #724]
	ldr	r1, [r4, #40]
	str	r3, [r4, #56]
	str	r2, [r1, #720]
	ldr	r1, [r4, #40]
	strb	r7, [r1, #7]
	ldr	r1, [r4, #40]
	strb	r2, [r1, #5]
	ldr	r1, [r4, #40]
	strb	r7, [r1, #1]
	strb	r7, [r10, #3482]
	ldr	r0, [r8, #2704]
	ldr	r1, [r4, #44]
	str	r0, [r4, #120]
	strb	r2, [r1, #3]
	ldr	r2, [r6, #236]
	ldr	r2, [r2, #2900]
	cmp	r2, #0
	beq	.L4066
	str	r5, [r9, #4080]
	mov	r0, r6
	bl	MVC_DecPOC
	ldr	r2, [r9, #4060]
	str	r2, [r4, #60]
	ldr	r2, [r9, #4056]
	str	r2, [r4, #64]
	ldr	r2, [r9, #4048]
	str	r2, [r4, #68]
	ldr	r2, [r9, #4052]
	str	r2, [r4, #72]
	b	.L4066
.L4075:
	ldr	r1, .L4078+12
	mov	r0, r5
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4069:
	ldr	r2, [fp, #-68]
	mov	r0, #0
	ldr	r3, [fp, #-52]
	str	r2, [r9, #4064]
	add	r3, r3, #16384
	ldr	r2, [fp, #-72]
	str	r2, [r9, #4068]
	ldrb	r2, [fp, #-76]	@ zero_extendqisi2
	ldr	r3, [r3, #44]
	strb	r2, [r3, #3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4077:
	ldr	r2, [fp, #-68]
	add	r3, r3, #16384
	ldr	r1, .L4078+16
	mov	r0, #0
	str	r2, [r9, #4064]
	ldr	r2, [fp, #-72]
	str	r2, [r9, #4068]
	ldrb	r2, [fp, #-76]	@ zero_extendqisi2
	ldr	r3, [r3, #44]
	strb	r2, [r3, #3]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4076:
	ldr	r2, [fp, #-80]
	mov	r0, #0
	ldr	lr, [fp, #-72]
	add	r1, r2, #36864
	ldr	r2, [fp, #-52]
	add	ip, r2, #16384
	ldr	r2, [fp, #-68]
	str	lr, [r1, #4068]
	ldrb	lr, [fp, #-76]	@ zero_extendqisi2
	str	r2, [r1, #4064]
	movw	r2, #6654
	ldr	ip, [ip, #44]
	ldr	r1, .L4078+20
	strb	lr, [ip, #3]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4079:
	.align	2
.L4078:
	.word	.LC443
	.word	.LC444
	.word	.LC446
	.word	.LC442
	.word	.LC445
	.word	.LC447
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
	add	r3, r0, #11141120
	add	r5, r3, #12288
	str	r3, [fp, #-60]
	add	r3, r0, #11075584
	str	r3, [fp, #-56]
	add	r6, r3, #40960
	ldrb	r1, [r5, #3480]	@ zero_extendqisi2
	ldr	r3, [r0, #252]
	mov	r7, #2240
	ldr	r2, [r6, #1080]
	cmp	r1, #0
	mov	r4, r0
	mov	r1, #0
	str	r1, [fp, #-48]
	mla	r7, r7, r2, r3
	beq	.L4081
	ldr	r3, [fp, #-60]
	add	r8, r3, #16384
	ldr	r3, [r8, #40]
	cmp	r3, r1
	beq	.L4082
	ldrb	r9, [r3, #2]	@ zero_extendqisi2
	cmp	r9, r1
	beq	.L4240
.L4082:
	mov	r3, #0
	strb	r3, [r5, #3480]
.L4081:
	sub	r1, fp, #48
	mov	r0, r4
	bl	MVC_GetReRangeFlag
	ldrb	r3, [r6, #1076]	@ zero_extendqisi2
	cmp	r3, #255
	mov	r9, r0
	beq	.L4241
.L4083:
	cmp	r3, #0
	bne	.L4086
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L4242
	ldr	r3, [r7, #28]
	ldr	r2, [r4, #28]
	cmp	r2, r3
	movweq	r3, #35364
	movteq	r3, 168
	addeq	r3, r4, r3
	streq	r3, [r4, #236]
	bne	.L4243
.L4086:
	ldr	r3, [fp, #-56]
	add	r8, r3, #36864
	ldr	r3, [r7, #24]
	ldr	r2, [r8, #1808]
	cmp	r2, r3
	beq	.L4244
.L4090:
	mov	r3, #0
	mov	r1, r7
	strb	r3, [r7, #20]
	ldr	r0, [r4, #236]
	bl	mvc_assign_quant_params
	ldr	r3, .L4258
	movw	r0, #38648
	mov	r2, #2240
	movt	r0, 169
	mov	r1, r7
	add	r0, r4, r0
	ldr	r3, [r3, #56]
	blx	r3
.L4091:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ldr	r3, [r4, #224]
	bne	.L4245
	ldr	r2, [r3, #920]
	cmp	r2, #1
	beq	.L4093
.L4102:
	ldr	r2, [r8, #1808]
	ldr	r3, [r7, #24]
	cmp	r2, r3
	bne	.L4111
	ldrb	r3, [r7, #20]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4111
.L4112:
	ldrb	r3, [r6, #1076]	@ zero_extendqisi2
	cmp	r3, #255
	moveq	r3, #0
	streq	r3, [r6, #2708]
	beq	.L4114
	cmp	r3, #0
	bne	.L4114
	add	r1, r4, #10747904
	movw	r2, #22868
	add	r1, r1, #20480
	movt	r2, 164
	ldr	ip, [r6, #2704]
	add	r2, r4, r2
	ldr	r0, [r1, #2384]
	adds	r0, r0, #1
	beq	.L4115
	ldr	r1, [r1, #2388]
	cmp	ip, r1
	beq	.L4156
	mov	lr, r0
	b	.L4116
.L4117:
	ldr	r1, [r2, #4]!
	cmp	ip, r1
	beq	.L4115
.L4116:
	add	r3, r3, #1
	cmp	r3, lr
	mov	r0, r3
	bne	.L4117
.L4115:
	str	r0, [r6, #2708]
.L4114:
	ldrb	r2, [r6, #1067]	@ zero_extendqisi2
	ldr	r3, [r4, #236]
	cmp	r2, #5
	ldreq	r2, [r6, #2708]
	ldr	r9, [r3, #2896]
	movweq	r3, #26894
	movteq	r3, 42
	addeq	r3, r2, r3
	ldreq	r7, [r6, #1092]
	addeq	r3, r4, r3, lsl #2
	ldrne	r7, [r6, #1092]
	streq	r7, [r3, #4]
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4120
	ldr	r10, [r4, #224]
	ldr	r3, [r10, #24]
	cmp	r3, #2
	beq	.L4120
	ldr	r2, [r6, #2708]
	movw	r3, #26894
	movt	r3, 42
	add	r3, r2, r3
	add	r3, r4, r3, lsl #2
	ldr	r0, [r3, #4]
	cmp	r0, r7
	beq	.L4120
	mov	r3, #1
	add	r9, r9, #4
	mov	r9, r3, asl r9
	add	r0, r0, r3
	str	r3, [fp, #-64]
	mov	r1, r9
	bl	__aeabi_uidivmod
	cmp	r1, r7
	beq	.L4120
	ldr	r3, [fp, #-64]
	str	r3, [r10, #616]
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #616]
	cmp	r2, #0
	beq	.L4246
.L4121:
	ldr	r3, [fp, #-56]
	add	r3, r3, #32768
	ldrb	r3, [r3, #1907]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4130
	ldr	r1, .L4258+4
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #620]
	bics	r3, r3, #1024
	bne	.L4237
	ldr	r10, [r6, #2704]
	cmp	r10, #0
	bne	.L4237
	ldr	r2, [r6, #2708]
	movw	r3, #26894
	movt	r3, 42
	mov	r1, r9
	add	r3, r2, r3
	ldr	r7, [r6, #1092]
	add	r3, r4, r3, lsl #2
	ldr	r0, [r3, #4]
	add	r0, r0, #1
	bl	__aeabi_uidivmod
	cmp	r7, r1
	bcs	.L4120
	ldrb	r3, [r6, #1064]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4120
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r3, [r6, #2708]
	movw	r2, #26894
	mov	r1, r9
	movt	r2, 42
	add	r2, r3, r2
	ldr	r5, [r6, #1092]
	add	r2, r4, r2, lsl #2
	ldr	r0, [r2, #4]
	add	r0, r0, #1
	bl	__aeabi_uidivmod
	mov	r3, r5
	mov	r0, r10
	movw	r2, #7166
	str	r1, [sp]
	ldr	r1, .L4258+8
	bl	dprint_vfmw
	mvn	r0, #0
.L4228:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4245:
	ldr	r10, [r3, #732]
	cmp	r10, #0
	bne	.L4093
	ldr	r2, [r3, #28]
	cmp	r2, #25
	beq	.L4247
.L4093:
	ldr	r2, [r4, #84]
	cmp	r9, #0
	add	r2, r2, #1
	str	r2, [r4, #84]
	bne	.L4103
	ldr	r3, [r3, #920]
	cmp	r3, #1
	beq	.L4104
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	cmp	r0, #0
	bne	.L4248
.L4236:
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	bne	.L4154
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	bne	.L4102
.L4108:
	ldr	r1, [r8, #1764]
	mov	r0, r4
	ldr	r3, [fp, #-56]
	mov	r1, r1, asl #1
	add	ip, r3, #32768
	str	r1, [r4, #52]
	add	r3, r4, #48
	ldr	r2, [r8, #1744]
	ldrb	r9, [ip, #1908]	@ zero_extendqisi2
	add	r2, r2, #1
	ldr	r10, [r8, #1740]
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
	beq	.L4249
.L4234:
	ldr	r3, [r4, #224]
	ldr	r3, [r3, #920]
	cmp	r3, #1
	mvneq	r0, #1
	beq	.L4228
	mov	r5, #0
	ldr	r1, .L4258+12
	str	r5, [r4, #12]
	mov	r0, r5
	str	r5, [r4, #16]
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r4
	bl	MVC_ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4111:
	ldr	r3, .L4258
	movw	r0, #38648
	mov	r2, #0
	movt	r0, 169
	strb	r2, [r7, #20]
	add	r0, r4, r0
	mov	r1, r7
	ldr	r3, [r3, #56]
	mov	r2, #2240
	blx	r3
	b	.L4112
.L4130:
	mov	r0, r4
	bl	MVC_DecGap
	cmp	r0, #0
	bne	.L4133
.L4237:
	ldr	r7, [r6, #1092]
.L4120:
	ldrb	r3, [r6, #1072]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4134
	ldr	r2, [r6, #2708]
	movw	r3, #26894
	movt	r3, 42
	add	r3, r2, r3
	add	r3, r4, r3, lsl #2
	str	r7, [r3, #4]
.L4134:
	mov	r0, r4
	str	r7, [r8, #4080]
	bl	MVC_DecPOC
	mov	r1, #0
	mov	r0, r4
	bl	MVC_AllocFrameStore
	cmp	r0, #0
	bne	.L4250
	ldr	r3, [fp, #-60]
	mov	r1, #1
	strb	r0, [r5, #3487]
	mvn	r9, #0
	strb	r1, [r5, #3480]
	add	r7, r3, #16384
	ldrb	r3, [r6, #1067]	@ zero_extendqisi2
	strb	r3, [r5, #3486]
	ldr	r3, [r6, #1092]
	str	r3, [r7, #48]
	str	r3, [fp, #-68]
	ldrb	r3, [r6, #1072]	@ zero_extendqisi2
	str	r3, [r7, #56]
	ldr	lr, [r8, #4060]
	str	r3, [fp, #-64]
	str	lr, [r7, #60]
	ldr	r2, [r8, #4056]
	str	r2, [r7, #64]
	ldr	ip, [r8, #4048]
	str	ip, [r7, #68]
	ldr	r10, [r8, #4052]
	str	ip, [r7, #84]
	str	lr, [r7, #76]
	str	r10, [r7, #72]
	str	r10, [r7, #88]
	str	r2, [r7, #80]
	strb	r0, [r5, #3482]
	strb	r0, [r5, #3485]
	strb	r0, [r5, #3484]
	str	r9, [r7, #112]
	ldrb	r10, [r6, #1065]	@ zero_extendqisi2
	cmp	r10, #0
	strneb	r1, [r6, #1065]
	ldr	r9, [r4, #236]
	movne	r10, r1
	movne	r1, #2
	ldrb	r0, [r9, #20]	@ zero_extendqisi2
	ldr	r2, [r9, #3952]
	rsb	r0, r0, #2
	mla	r0, r2, r0, r0
	bl	__aeabi_uidiv
	cmp	r10, #0
	ldr	r3, [fp, #-64]
	str	r0, [r7, #100]
	ldrb	r2, [r9, #20]	@ zero_extendqisi2
	ldr	ip, [r9, #3952]
	rsb	r1, r2, #2
	mla	r1, ip, r1, r1
	str	r1, [r7, #104]
	ldr	r1, [r9, #3948]
	add	r2, r1, #1
	str	r2, [r7, #96]
	mul	r2, r2, r0
	str	r2, [r7, #108]
	ldrb	r2, [r8, #1784]	@ zero_extendqisi2
	strb	r2, [r5, #3488]
	movne	r2, #0
	bne	.L4137
	ldrb	r2, [r9, #21]	@ zero_extendqisi2
	adds	r2, r2, #0
	movne	r2, #1
.L4137:
	cmp	r3, #0
	strb	r2, [r5, #3489]
	beq	.L4138
	ldr	r2, [r6, #2708]
	movw	r3, #26894
	movt	r3, 42
	add	r3, r2, r3
	ldr	r2, [fp, #-68]
	add	r3, r4, r3, lsl #2
	str	r2, [r3, #4]
.L4138:
	ldr	r3, [r7, #40]
	cmp	r3, #0
	ldrneb	r2, [r6, #1076]	@ zero_extendqisi2
	strneb	r2, [r3, #9]
	mvn	r3, #0
	str	r3, [r7, #120]
	ldrb	r3, [r6, #1075]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4140
	ldr	r3, [r6, #2704]
	str	r3, [r7, #120]
	ldrb	r3, [r6, #1073]	@ zero_extendqisi2
	strb	r3, [r5, #3490]
	ldrb	r3, [r6, #1074]	@ zero_extendqisi2
	strb	r3, [r5, #3491]
.L4140:
	ldr	r3, [r6, #2708]
	movw	r8, #2004
	movw	ip, #43728
	movw	lr, #16368
	movt	ip, 169
	movt	lr, 170
	str	r3, [r7, #124]
	mvn	r2, #0
	ldrb	r1, [r4, #3]	@ zero_extendqisi2
	mvn	r3, #0
	mov	r0, #29
	mla	r8, r8, r1, r4
	ldr	r1, .L4258+16
	add	ip, r8, ip
	str	ip, [r7, #44]
	ldr	ip, [r4, #224]
	ldrd	r8, [ip, #64]
	strd	r8, [r4, lr]
	ldrd	r8, [ip, #80]
	strd	r8, [r7, #-8]
	ldrd	r8, [ip, #96]
	strd	r8, [r7]
	strd	r2, [ip, #64]
	ldrd	r2, [r4, lr]
	bl	dprint_vfmw
	ldrd	r2, [r7, #-8]
	ldr	r1, .L4258+20
	mov	r0, #29
	bl	dprint_vfmw
	ldr	ip, [r4, #236]
	ldr	r3, [fp, #-56]
	mov	r2, #4
	ldr	r1, .L4258
	movw	r0, #15848
	add	lr, r3, #32768
	ldr	r3, [ip, #3948]
	movt	r0, 170
	add	r0, r4, r0
	add	r3, r3, #1
	ldr	r8, [r1, #48]
	mov	r1, #0
	mov	r3, r3, asl r2
	str	r3, [r5, #3564]
	ldrb	r3, [ip, #20]	@ zero_extendqisi2
	ldr	r9, [ip, #3952]
	rsb	r3, r3, #2
	mla	r3, r9, r3, r3
	mov	r3, r3, asl r2
	str	r3, [r5, #3568]
	ldr	r9, [ip, #748]
	ldr	r10, [lr, #1940]
	subs	r9, r9, #1
	and	r10, r10, #7
	movne	r9, #1
	blx	r8
	ldrb	r2, [r5, #3560]	@ zero_extendqisi2
	mov	ip, #2
	ldrb	r3, [r5, #3561]	@ zero_extendqisi2
	movw	r0, #15784
	and	r2, r2, #252
	mov	r1, r10
	bfi	r2, r9, #2, #3
	strb	r2, [r5, #3560]
	ldr	r2, [r4, #236]
	bfi	r3, ip, #0, #2
	and	r3, r3, #243
	ldrb	lr, [r5, #3560]	@ zero_extendqisi2
	bfi	r3, ip, #4, #2
	movt	r0, 170
	ldr	ip, [r2, #56]
	add	r0, r4, r0
	strb	r3, [r5, #3561]
	bfi	lr, ip, #5, #3
	strb	lr, [r5, #3560]
	ldr	r2, [r2, #52]
	ldr	r3, [r5, #3560]
	bfi	r3, r2, #14, #3
	str	r3, [r5, #3560]
	bl	SetAspectRatio
	ldr	r3, [r4, #84]
	str	r3, [r5, #3652]
	ldr	r0, [r7, #40]
	cmp	r0, #0
	beq	.L4251
	ldr	r3, [r4, #236]
	ldr	r3, [r3, #3984]
	str	r3, [r0, #156]
	str	r3, [r5, #3580]
	ldr	r3, [r4, #236]
	ldr	r2, [r7, #40]
	ldr	r3, [r3, #3988]
	str	r3, [r2, #160]
	str	r3, [r5, #3584]
	ldr	r3, [r4, #236]
	ldr	r2, [r7, #40]
	ldr	r3, [r3, #3976]
	str	r3, [r2, #148]
	str	r3, [r5, #3572]
	ldr	r2, [r4, #236]
	ldr	r3, [r7, #40]
	ldr	r2, [r2, #3980]
	str	r2, [r3, #152]
	ldrb	r3, [r5, #3483]	@ zero_extendqisi2
	str	r2, [r5, #3576]
	adds	r3, r3, #0
	ldr	r2, [r5, #3560]
	movne	r3, #1
	str	r3, [r5, #3548]
	ldr	r3, [r7, #40]
	str	r2, [r3, #136]
	ldr	r3, [r7, #40]
	ldr	r2, [r5, #3548]
	str	r2, [r3, #124]
	ldr	r3, [r6, #1092]
	str	r3, [r5, #3672]
	ldr	r2, [r6, #2704]
	str	r2, [r5, #3680]
	ldr	r2, [r7, #40]
	str	r3, [r2, #248]
	ldr	r3, [r7, #40]
	ldr	r2, [r6, #2704]
	str	r2, [r3, #256]
	ldr	r3, [r7, #40]
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L4142
	ldr	r3, [r5, #3548]
	mov	r1, #0
	ldr	r2, [r0, #4]
	subs	r3, r3, r1
	ldr	r0, [r4, #120]
	movne	r3, #1
	bl	FSP_SetStoreType
.L4142:
	ldr	r3, [fp, #-60]
	movw	lr, #16352
	movt	lr, 170
	add	lr, r4, lr
	add	ip, r3, #16320
	ldr	r3, [r4, #60]
	mov	r6, #0
.L4146:
	ldrd	r0, [ip, #8]!
	orrs	r2, r0, r1
	bne	.L4143
	cmp	r3, #0
	beq	.L4143
	ldr	r2, [r4, #528]
	subs	r3, r3, #1
	stmia	ip, {r2, r6}
	beq	.L4144
	add	r1, r4, #528
	mov	r2, #0
.L4145:
	add	r2, r2, #1
	ldr	r0, [r1, #4]!
	cmp	r2, r3
	str	r0, [r1, #-4]
	bne	.L4145
.L4144:
	add	r2, r3, #132
	str	r6, [r4, r2, asl #2]
	str	r3, [r4, #60]
.L4143:
	cmp	ip, lr
	bne	.L4146
	cmp	r3, #0
	beq	.L4148
	mov	r6, r3
	ble	.L4148
	add	r7, r3, #132
	mov	r8, #0
	add	r7, r4, r7, lsl #2
.L4149:
	ldr	r1, [r7, #-4]!
	sub	r6, r6, #1
	ldr	r0, [r4, #120]
	bl	FreeUsdByDec
	cmp	r6, #0
	str	r8, [r7]
	bne	.L4149
.L4148:
	mov	r6, #0
	mov	r0, r4
	str	r6, [r4, #60]
	strb	r6, [r5, #3492]
	bl	MVC_UpdateReflist
	mov	r0, r4
	bl	MVC_UpdateLTReflist
	mov	r0, r4
	bl	MVC_CalcPicNum
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4244:
	ldrb	r3, [r7, #20]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4091
	b	.L4090
.L4241:
	mov	r2, #1
	strb	r2, [r4, #2]
	ldr	r1, [r7, #28]
	movw	ip, #3992
	ldr	r0, [r4, #248]
	movw	r8, #34656
	ldr	r2, [fp, #-56]
	str	r1, [r4, #24]
	ldr	r1, [r7, #28]
	add	r2, r2, #32768
	ldr	r2, [r2, #2632]
	mla	r1, ip, r1, r0
	ldr	r0, [r1, #744]
	cmp	r2, r0
	beq	.L4252
.L4084:
	ldr	r2, .L4258
	movt	r8, 169
	ldr	r3, [r4, #84]
	add	r8, r4, r8
	mov	ip, #0
	add	r3, r3, #1
	mov	r0, r8
	str	r3, [r4, #84]
	strb	ip, [r1, #26]
	ldr	r3, [r2, #56]
	movw	r2, #3992
	blx	r3
	ldrb	r3, [r6, #1076]	@ zero_extendqisi2
.L4085:
	str	r8, [r4, #236]
	b	.L4083
.L4104:
	ldr	r1, .L4258+24
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_GetBackPicFromVOQueue
	b	.L4236
.L4252:
	ldrb	r2, [r1, #26]	@ zero_extendqisi2
	cmp	r2, #0
	movteq	r8, 169
	addeq	r8, r4, r8
	beq	.L4085
	b	.L4084
.L4240:
	ldrsb	r1, [r3, #6]
	mov	r2, #1
	ldr	r0, [r0, #120]
	bl	FSP_ClearLogicFs
	ldr	r3, [r8, #40]
	strb	r9, [r3, #2]
	ldr	r3, [r8, #40]
	strb	r9, [r3, #5]
	b	.L4082
.L4246:
	ldr	r2, [r3, #660]
	cmp	r2, #1
	beq	.L4253
.L4122:
	ldr	r3, [r6, #2708]
	ldr	r1, [r6, #1092]
	add	r3, r4, r3, lsl #2
	add	r3, r3, #11075584
	add	r2, r3, #40960
	ldr	r2, [r2, #1084]
	cmp	r1, r2
	bls	.L4123
	ldr	ip, [r8, #1764]
	rsb	r0, r2, r1
	cmp	r2, #0
	cmpne	ip, r0
	bcs	.L4121
	ldrb	r2, [r6, #1064]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L4254
	add	r3, r3, #40960
	cmp	r1, #0
	subne	r2, r1, #1
	subeq	r2, r9, #1
	mvn	r1, #0
	str	r2, [r3, #1084]
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r3, r0, #0
	beq	.L4121
	movw	r2, #7116
	ldr	r1, .L4258+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4247:
	ldr	r3, [r4, #84]
	cmp	r9, #0
	add	r3, r3, #1
	str	r3, [r4, #84]
	beq	.L4094
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r3, r0, #0
	bne	.L4255
	mov	r0, r4
	bl	MVC_InitDPB
	subs	r3, r0, #0
	bne	.L4151
	ldr	r2, [fp, #-56]
	ldr	r3, [r8, #1744]
	add	r2, r2, #32768
	ldr	r9, [r8, #1740]
	add	r3, r3, #1
	ldrb	r10, [r2, #1908]	@ zero_extendqisi2
	add	r9, r9, #1
	ldr	r2, [r4, #12]
	mov	r3, r3, asl #4
	rsb	r10, r10, #2
	mov	r9, r9, asl #4
	cmp	r2, #0
	mul	r10, r10, r3
	bne	.L4100
	ldr	r3, [r8, #1764]
	ldr	r0, [r4, #224]
	mov	r3, r3, asl #1
	str	r3, [r4, #52]
	ldr	r1, [r0, #692]
	cmp	r1, r9
	bcc	.L4096
	ldr	r2, [r0, #696]
	cmp	r2, r10
	bcc	.L4096
	ldr	ip, [fp, #-56]
	ldr	lr, [r0, #716]
	add	ip, ip, #45056
	ldr	ip, [ip, #2920]
	cmp	lr, ip
	bcc	.L4256
	ldr	ip, [r0, #720]
	cmp	ip, #0
	moveq	r3, #1
	streq	r3, [r4, #52]
	ldreq	r1, [r0, #692]
	ldreq	r2, [r0, #696]
	mov	r0, r4
	str	r3, [sp]
	add	r3, r4, #48
	bl	MVC_ArrangeVahbMem
	cmp	r0, #1
	bne	.L4234
	b	.L4100
.L4242:
	strb	r3, [r4, #2]
	movw	r2, #8500
	ldr	r1, [r7, #28]
	movt	r2, 5
	ldr	r3, .L4258
	movw	r0, #22860
	movt	r0, 164
	add	r0, r4, r0
	mla	r1, r2, r1, r4
	ldr	r3, [r3, #56]
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
	b	.L4086
.L4103:
	ldr	r1, .L4258+24
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_GetBackPicFromVOQueue
	mov	r0, r4
	bl	MVC_InitDPB
	cmp	r0, #0
	beq	.L4108
.L4154:
	mov	r3, r0
	movw	r2, #7015
	ldr	r1, .L4258+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4249:
	mov	r10, r10, lsr #4
	mov	r9, r9, lsr #4
	str	r10, [r4, #12]
	str	r9, [r4, #16]
	b	.L4102
.L4123:
	rsb	r0, r2, r1
	ldr	ip, [r8, #1764]
	add	r0, r0, r9
	cmp	r2, #0
	cmpne	ip, r0
	bcs	.L4121
	ldrb	r2, [r6, #1064]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L4257
	add	r3, r3, #40960
	cmp	r1, #0
	subne	r2, r1, #1
	subeq	r2, r9, #1
	mvn	r1, #0
	str	r2, [r3, #1084]
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r3, r0, #0
	beq	.L4121
	movw	r2, #7143
	ldr	r1, .L4258+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4094:
	mov	r0, r4
	bl	MVC_InitDPB
	subs	r3, r0, #0
	bne	.L4151
	ldr	r2, [fp, #-56]
	ldr	r3, [r8, #1744]
	add	r2, r2, #32768
	ldr	r9, [r8, #1740]
	add	r3, r3, #1
	ldrb	r10, [r2, #1908]	@ zero_extendqisi2
	add	r9, r9, #1
	mov	r3, r3, asl #4
	rsb	r10, r10, #2
	mov	r9, r9, asl #4
	mul	r10, r10, r3
.L4100:
	mov	r9, r9, lsr #4
	mov	r10, r10, lsr #4
	str	r9, [r4, #12]
	str	r10, [r4, #16]
	b	.L4102
.L4243:
	ldr	r1, .L4258+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4133:
	movw	r2, #7178
	ldr	r1, .L4258+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4253:
	ldr	r2, [r3, #656]
	cmp	r2, #0
	bne	.L4122
	ldr	r2, [r3, #664]
	cmp	r2, #0
	bne	.L4122
	ldr	r3, [r3, #620]
	add	r3, r3, #1024
	cmp	r3, #2048
	bhi	.L4121
	b	.L4122
.L4156:
	mov	r0, r3
	b	.L4115
.L4250:
	movw	r2, #7198
	ldr	r1, .L4258+44
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4251:
	movw	r2, #7293
	ldr	r1, .L4258+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4248:
	mov	r3, r0
	movw	r2, #7006
	mov	r0, r9
	ldr	r1, .L4258+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4254:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r2, [r6, #2708]
	ldr	r3, [r8, #1764]
	movw	r1, #26894
	ldr	ip, [r6, #1092]
	movt	r1, 42
	add	r1, r2, r1
	movw	r2, #7105
.L4238:
	add	r4, r4, r1, lsl #2
	str	r3, [sp]
	ldr	r1, .L4258+52
	mov	r0, #0
	ldr	r3, [r4, #4]
	rsb	r3, r3, ip
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4151:
	movw	r2, #6931
	ldr	r1, .L4258+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4257:
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_ClearDPB
	ldr	r2, [r6, #2708]
	movw	r1, #26894
	ldr	r3, [r8, #1764]
	movt	r1, 42
	ldr	ip, [r6, #1092]
	add	r1, r2, r1
	movw	r2, #7132
	b	.L4238
.L4096:
	ldr	r1, .L4258+56
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4255:
	mov	r0, r10
	movw	r2, #6922
	ldr	r1, .L4258+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4256:
	ldr	r1, .L4258+60
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4228
.L4259:
	.align	2
.L4258:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC454
	.word	.LC455
	.word	.LC452
	.word	.LC458
	.word	.LC459
	.word	.LC461
	.word	.LC448
	.word	.LC449
	.word	.LC33
	.word	.LC456
	.word	.LC457
	.word	.LC460
	.word	.LC453
	.word	.LC450
	.word	.LC451
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r2, [r0, #68]
	mov	r4, r0
	ldr	r1, .L4312
	sub	r2, r2, #1
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r4, #232]
	add	r5, r4, #11075584
	mov	r0, r4
	add	r5, r5, #40960
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	strb	r2, [r5, #1067]
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	strb	r3, [r5, #1072]
	bl	MVC_ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L4305
	mov	r0, r4
	bl	MVC_ProcessSliceHeaderSecondPart
	cmp	r0, #0
	bne	.L4305
	ldr	r2, [r4, #64]
	cmp	r2, #0
	moveq	r3, r2
	beq	.L4267
	movw	r7, #17280
	mov	r9, r0
	movt	r7, 170
	mov	r3, r0
	add	r7, r4, r7
	mov	lr, r0
	b	.L4275
.L4306:
	cmp	ip, r0
	add	r3, r6, r3
	rsbhi	r0, r0, ip
	rsbhi	r9, r9, r8
	addhi	r0, r0, r9
	movls	r0, r8
	add	r3, r3, r0
.L4273:
	cmp	r1, #0
	add	lr, lr, #1
	movne	r0, r1
	movne	r9, r6
	moveq	r0, ip
	moveq	r9, r8
	cmp	lr, r2
	beq	.L4267
.L4275:
	ldr	r6, [r7, #4]!
	ldr	ip, [r6, #8]
	ldr	r1, [r6, #36]
	cmp	ip, #0
	ldrne	r8, [r6, #12]
	moveq	r8, ip
	cmp	r1, #0
	ldrne	r6, [r6, #40]
	moveq	r6, r1
	cmp	r0, #0
	bne	.L4306
	add	r3, r8, r3
	add	r3, r3, r6
	b	.L4273
.L4267:
	add	r6, r4, #11141120
	str	r3, [r4, #104]
	add	r0, r6, #16384
	movw	ip, #1620
	ldr	lr, [r0, #100]
	ldr	r1, [r0, #96]
	mul	r1, r1, lr
	cmp	r1, ip
	movgt	r1, r1, asl #7
	ble	.L4307
.L4277:
	ldr	r0, [r4, #32]
	cmp	r0, r2
	bls	.L4278
	cmp	r1, r3
	bcc	.L4278
	ldrb	r3, [r5, #1069]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4308
.L4281:
	mov	r0, r4
	bl	MVC_PicTypeStatistic
	mov	r0, r4
	bl	MVC_DecList
	cmp	r0, #0
	bne	.L4309
	mov	r0, r4
	bl	MVC_IsRefListWrong
	subs	r5, r0, #0
	bne	.L4310
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
.L4264:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4307:
	mov	r0, r1, asl #9
	sub	r1, r0, r1, asl #7
	cmp	r1, #16384
	movlt	r1, #16384
	b	.L4277
.L4308:
	ldr	r1, .L4312+4
	mov	r0, #2
	bl	dprint_vfmw
	add	r6, r6, #12288
	ldr	r3, [r4, #88]
	mov	r2, #0
	str	r2, [r4, #100]
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r4, #88]
	ldrb	r3, [r6, #3483]	@ zero_extendqisi2
	cmp	r3, r2
	ldreq	r3, [r4, #92]
	ldrne	r3, [r4, #96]
	addeq	r3, r3, #1
	addne	r3, r3, #1
	streq	r3, [r4, #92]
	strne	r3, [r4, #96]
	bl	MVC_InitPic
	cmn	r0, #2
	beq	.L4264
	cmp	r0, #0
	bne	.L4311
	mov	r0, r4
	bl	MVC_WritePicMsg
	b	.L4281
.L4305:
	ldr	r1, .L4312+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4312+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4303
	sub	r2, fp, #36
	mvn	r1, #0
	mov	r3, #4
	str	r1, [r2, #-8]!
	mov	r1, #100
	ldr	r0, [r4, #120]
	blx	r5
.L4303:
	mov	r0, r4
	bl	MVC_ClearCurrSlice
	mvn	r0, #0
	b	.L4264
.L4278:
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L4312+16
	bl	dprint_vfmw
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #32]
	cmp	r3, r2
	bcc	.L4280
	ldr	r1, .L4312+12
	ldr	r5, [r1]
	cmp	r5, #0
	beq	.L4280
	str	r3, [fp, #-44]
	mov	r1, #108
	str	r2, [fp, #-40]
	mov	r3, #8
	sub	r2, fp, #44
	ldr	r0, [r4, #120]
	blx	r5
.L4280:
	ldr	r1, .L4312+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mvn	r0, #0
	b	.L4264
.L4309:
	mov	r2, r0
	ldr	r1, .L4312+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4264
.L4310:
	ldr	r1, .L4312+28
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4303
.L4311:
	ldr	r1, .L4312+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4264
.L4313:
	.align	2
.L4312:
	.word	.LC398
	.word	.LC464
	.word	.LC399
	.word	g_event_report
	.word	.LC462
	.word	.LC463
	.word	.LC466
	.word	.LC467
	.word	.LC465
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	ip, [r0, #232]
	mov	r5, r1
	mov	r4, r0
	ldr	r3, [ip, #68]
	cmp	r3, #0
	ldrne	r1, [r0, #104]
	movne	r2, ip
	movne	r3, #0
	beq	.L4319
.L4318:
	ldr	r0, [r2, #12]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, r0
	str	r1, [r4, #104]
	ldr	r0, [ip, #68]
	cmp	r0, r3
	bhi	.L4318
.L4319:
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
	cmp	r3, #20
	beq	.L4500
.L4317:
	ldr	r2, [r4, #68]
	mov	r0, #22
	ldr	r1, .L4511
	bl	dprint_vfmw
	ldr	r3, [r4, #68]
	movw	r2, #371
	cmp	r3, r2
	beq	.L4501
.L4322:
	ldr	r2, [r4, #232]
	add	r3, r3, #1
	str	r3, [r4, #68]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	sub	r3, r2, #1
	cmp	r3, #29
	ldrls	pc, [pc, r3, asl #2]
	b	.L4323
.L4325:
	.word	.L4324
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4324
	.word	.L4326
	.word	.L4327
	.word	.L4328
	.word	.L4329
	.word	.L4330
	.word	.L4331
	.word	.L4332
	.word	.L4333
	.word	.L4334
	.word	.L4335
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4336
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4323
	.word	.L4337
.L4337:
	mov	r2, #30
	ldr	r1, .L4511+4
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r5, #0
	bne	.L4363
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4363
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	str	r5, [r4, #232]
.L4363:
	mov	r1, #32
	mov	r0, r7
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r7
	bl	BsGet
	ldr	r3, .L4511+8
	rev	r5, r5
	ldr	r2, [r3, #440]
	ldr	r3, [r3, #436]
	rev	r0, r0
	cmp	r0, r2
	cmpeq	r5, r3
	bne	.L4481
	ldr	r5, .L4511+12
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4364
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	r6
.L4364:
	mov	r6, #0
	mov	r0, r4
	strb	r6, [r4]
	bl	MVC_DecVDM
	cmp	r0, r6
	beq	.L4481
.L4496:
	ldr	r5, [r5]
	cmp	r5, r6
	beq	.L4480
	ldr	r0, [r4, #120]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4350
.L4324:
	ldr	r3, [r4, #80]
	mov	r0, #22
	ldr	r1, .L4511+16
	bl	dprint_vfmw
	ldr	r3, [r4, #232]
	add	r0, r4, #11075584
	add	r2, r4, #12288
	add	r0, r0, #40960
	mvn	lr, #0
	ldrb	ip, [r3, #2]	@ zero_extendqisi2
	mov	r1, #0
	strb	ip, [r0, #1067]
	ldrb	r5, [r3, #4]	@ zero_extendqisi2
	strb	r5, [r0, #1072]
	ldrb	r3, [r3, #5]	@ zero_extendqisi2
	str	lr, [r0, #2704]
	strb	r1, [r0, #1075]
	strb	r3, [r0, #1076]
	ldrb	lr, [r2, #704]	@ zero_extendqisi2
	cmp	lr, #1
	beq	.L4502
	cmp	r3, #255
	beq	.L4503
.L4339:
	ldr	r2, [r4, #88]
	mov	r0, #21
	ldr	r1, .L4511+20
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_SliceCheck
	subs	r5, r0, #0
	mov	r0, r4
	bne	.L4504
	bl	MVC_DecSlice
	cmn	r0, #2
	beq	.L4350
	cmp	r0, #0
	beq	.L4481
	ldr	r3, .L4511+12
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L4480
	ldr	r0, [r4, #120]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r6
.L4480:
	mvn	r0, #0
	b	.L4350
.L4327:
	ldr	r1, .L4511+24
	mov	r2, #7
	ldr	r3, [r4, #72]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_DecSPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4355
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4355:
	cmp	r5, #0
	bne	.L4505
	ldr	r3, [r4, #72]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #72]
	b	.L4350
.L4326:
	ldr	r1, .L4511+28
	mov	r2, #6
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_DecSEI
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4357
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4357:
	cmp	r5, #0
	bne	.L4506
.L4481:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4328:
	ldr	r1, .L4511+32
	mov	r2, #8
	ldr	r3, [r4, #76]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_DecPPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4353
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4353:
	cmp	r5, #0
	bne	.L4507
	ldr	r3, [r4, #76]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #76]
	b	.L4350
.L4329:
	ldr	r1, .L4511+36
	mov	r2, #9
.L4488:
	mov	r0, #22
	bl	dprint_vfmw
.L4493:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4481
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #232]
.L4350:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4330:
	mov	r2, #10
	ldr	r1, .L4511+40
	b	.L4488
.L4331:
	mov	r2, #11
	ldr	r1, .L4511+44
	mov	r0, #22
	bl	dprint_vfmw
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
	bne	.L4493
	ldr	r5, .L4511+12
	mov	r3, #1
	strb	r3, [r4, #1]
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4360
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	r6
.L4360:
	mov	r6, #0
	mov	r0, r4
	strb	r6, [r4]
	bl	MVC_DecVDM
	cmp	r0, r6
	beq	.L4493
	b	.L4496
.L4332:
	mov	r2, #12
	ldr	r1, .L4511+48
	b	.L4488
.L4333:
	mov	r2, #13
	ldr	r1, .L4511+52
	b	.L4488
.L4334:
	mov	r2, #14
	ldr	r1, .L4511+56
	b	.L4488
.L4335:
	ldr	r1, .L4511+60
	mov	r2, #15
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_DecSubSPS
	ldr	r1, [r4, #232]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4361
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4361:
	cmp	r5, #0
	bne	.L4508
	ldr	r3, [r4, #20]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #20]
	b	.L4350
.L4336:
	mov	r2, #19
	ldr	r1, .L4511+64
	b	.L4488
.L4323:
	mov	r3, r6
	ldr	r1, .L4511+68
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r6, #256
	beq	.L4365
	ldr	r1, .L4511+72
	mov	r0, #1
	bl	dprint_vfmw
.L4365:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4366
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4366:
	ldr	r3, .L4511+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4481
.L4485:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	b	.L4481
.L4501:
	ldr	r1, .L4511+76
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r4, #68]
	b	.L4322
.L4500:
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
	bne	.L4320
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
	beq	.L4509
.L4320:
	ldr	r2, [r3, #64]
	add	r2, r2, #24
	str	r2, [r3, #64]
	ldr	r3, [r4, #232]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	b	.L4317
.L4504:
	bl	MVC_ClearCurrSlice
	ldr	r3, .L4511+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4480
.L4349:
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4350
.L4508:
	ldr	r1, .L4511+80
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4511+12
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4480
	sub	r2, fp, #36
	ldr	r0, [r4, #120]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	r5
	mov	r0, r4
	b	.L4350
.L4505:
	ldr	r5, .L4511+12
	mov	r0, #1
	ldr	r1, .L4511+84
	bl	dprint_vfmw
	ldr	r6, [r5]
	cmp	r6, #0
	beq	.L4480
.L4498:
	sub	r2, fp, #36
	mvn	r7, #0
	mov	r3, #4
	mov	r1, #100
	str	r7, [r2, #-4]!
	ldr	r0, [r4, #120]
	blx	r6
	ldr	r5, [r5]
	cmp	r5, #0
	bne	.L4349
	b	.L4480
.L4507:
	ldr	r5, .L4511+12
	mov	r0, #1
	ldr	r1, .L4511+88
	bl	dprint_vfmw
	ldr	r6, [r5]
	cmp	r6, #0
	bne	.L4498
	b	.L4480
.L4506:
	ldr	r1, .L4511+92
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4511+12
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L4485
	b	.L4481
.L4503:
	ldr	r3, [r4, #20]
	cmp	r3, #0
	beq	.L4339
	add	r3, r4, #10747904
	add	r3, r3, #20480
	ldr	r2, [r3, #2384]
	cmp	r2, #0
	beq	.L4342
	ldrb	r2, [r3, #2380]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L4343
.L4342:
	add	r3, r4, #12992
	mov	r2, #0
	add	r3, r3, #16
.L4346:
	ldr	r1, [r3]
	cmp	r1, #0
	beq	.L4344
	ldrb	r1, [r3, #-4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L4510
.L4344:
	add	r2, r2, #1
	add	r3, r3, #335872
	cmp	r2, #32
	add	r3, r3, #308
	bne	.L4346
	mvn	r3, #0
.L4479:
	cmn	r3, #1
	str	r3, [r0, #2704]
	beq	.L4339
	sub	ip, ip, #5
	mov	r3, #1
	clz	ip, ip
	strb	r3, [r0, #1075]
	strb	r3, [r0, #1074]
	mov	ip, ip, lsr #5
	strb	ip, [r0, #1073]
	b	.L4339
.L4502:
	strb	lr, [r0, #1075]
	ldr	r3, [r2, #712]
	str	r3, [r0, #2704]
	ldrb	r3, [r2, #708]	@ zero_extendqisi2
	strb	r3, [r0, #1073]
	ldrb	r3, [r2, #709]	@ zero_extendqisi2
	strb	r3, [r0, #1074]
	strb	r1, [r2, #704]
	b	.L4339
.L4509:
	cmp	r0, #0
	movne	r2, #1
	moveq	r2, #5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #232]
	b	.L4320
.L4510:
	movw	r3, #8500
	movt	r3, 5
	mla	r3, r3, r2, r4
	add	r3, r3, #12992
	add	r3, r3, #16
	ldr	r3, [r3, #4]
	b	.L4479
.L4343:
	ldr	r3, [r3, #2388]
	b	.L4479
.L4512:
	.align	2
.L4511:
	.word	.LC468
	.word	.LC486
	.word	.LANCHOR1
	.word	g_event_report
	.word	.LC470
	.word	.LC471
	.word	.LC474
	.word	.LC476
	.word	.LC472
	.word	.LC478
	.word	.LC479
	.word	.LC481
	.word	.LC480
	.word	.LC482
	.word	.LC483
	.word	.LC484
	.word	.LC485
	.word	.LC487
	.word	.LC488
	.word	.LC469
	.word	.LC338
	.word	.LC475
	.word	.LC473
	.word	.LC477
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	subs	r4, r0, #0
	mov	r2, #0
	str	r2, [fp, #-40]
	str	r2, [fp, #-44]
	str	r2, [fp, #-48]
	beq	.L4577
	cmp	r1, #0
	beq	.L4578
	ldr	r0, [r4, #224]
	ldrb	ip, [r4, #5]	@ zero_extendqisi2
	ldr	r3, [r0, #8]
	cmp	ip, #1
	mov	r3, r3, asl #16
	and	r3, r3, #196608
	str	r3, [r4, #108]
	ldr	r3, [r0]
	str	r3, [r4, #112]
	ldr	r3, [r0, #4]
	strb	r2, [r4, #10]
	str	r3, [r4, #116]
	beq	.L4517
	ldr	r3, [r0, #872]
	cmp	r3, #1
	addne	r5, r4, #11141120
	addne	r5, r5, #16384
	beq	.L4579
.L4518:
	mov	r0, r4
	bl	MVC_ReceivePacket
	ldr	r3, [r4, #232]
	str	r3, [r5, #2636]
.L4520:
	cmp	r0, #0
	mov	r3, #0
	strb	r3, [r4, #5]
	beq	.L4521
.L4540:
	mov	r0, #0
.L4572:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4579:
	ldr	r3, [r0, #920]
	add	r5, r4, #11141120
	add	r5, r5, #16384
	cmp	r3, #1
	bne	.L4518
	ldr	r3, [r5, #2632]
	cmp	r3, #1
	bne	.L4518
	ldr	r3, [r5, #2636]
	str	r3, [r4, #232]
	str	r2, [r5, #2632]
	strb	r2, [r4, #5]
	b	.L4519
.L4521:
	ldr	r3, [r4, #232]
.L4519:
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
	beq	.L4580
.L4575:
	and	r5, r5, #27
	mov	r3, #0
	cmp	r5, #1
	strb	r3, [r4, #10]
	beq	.L4526
.L4527:
	mov	r0, r4
	bl	MVC_FindTrailZeros
	cmp	r0, #0
	bne	.L4581
.L4539:
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
	beq	.L4572
	cmp	r0, r5
	beq	.L4540
	ldr	r3, .L4585
	ldr	r6, [r3]
	cmp	r6, r5
	beq	.L4576
	ldr	r0, [r4, #120]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	r6
.L4576:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4517:
	ldr	r0, [r4, #232]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	b	.L4520
.L4580:
	mov	r1, #24
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r4, #232]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #5]
	ldr	r1, [r4, #232]
	ldrsb	r2, [r1, #5]
	cmp	r2, #0
	bne	.L4575
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
.L4526:
	sub	r2, fp, #32
	sub	r1, fp, #36
	mov	r0, r4
	bl	MVC_InquireSliceProperty
	cmp	r0, #0
	bne	.L4528
	ldr	r3, [fp, #-36]
	ldr	r2, [r4, #128]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	cmp	r3, #0
	add	r3, r2, r3
	str	r3, [r4, #128]
	bne	.L4582
.L4529:
	ldr	r3, [fp, #-32]
	cmp	r3, #1
	bne	.L4527
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	cmp	r0, #0
	bne	.L4583
.L4536:
	ldr	r0, [r4, #120]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L4527
	sub	r3, fp, #40
	sub	r2, fp, #44
	sub	r1, fp, #48
	ldr	r0, [r4, #120]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #224]
	ldr	r2, [r3, #732]
	cmp	r2, #1
	bne	.L4527
	ldr	r3, [fp, #-40]
	cmp	r3, #0
	ble	.L4584
.L4533:
	mov	r3, #1
	mvn	r0, #1
	strb	r3, [r4, #5]
	b	.L4572
.L4581:
	ldr	r1, .L4585+4
	mov	r0, #22
	bl	dprint_vfmw
	b	.L4539
.L4528:
	ldr	r1, [r4, #232]
	cmp	r1, #0
	beq	.L4538
	ldr	r0, [r4, #120]
	bl	MVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #232]
.L4538:
	ldr	r3, .L4585
	ldr	r5, [r3]
	cmp	r5, #0
	beq	.L4576
	mov	r3, #0
	ldr	r0, [r4, #120]
	mov	r2, r3
	mov	r1, #113
	blx	r5
	mvn	r0, #0
	b	.L4572
.L4582:
	add	r5, r4, #11075584
	add	r5, r5, #40960
	ldrb	r3, [r5, #1065]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #132]
	addeq	r3, r3, #1
	addne	r3, r3, #2
	str	r3, [r4, #132]
	ldr	r3, [r4, #64]
	cmp	r3, #0
	beq	.L4529
	ldr	r3, [r4, #232]
	mov	ip, #0
	mov	r0, r6
	mov	r2, #12
	ldr	r1, .L4585+8
	str	ip, [r3, #64]
	bl	BsInit
	mov	r1, #1
	mov	r0, r4
	bl	MVC_DecOneNal
	ldrb	r3, [r5, #1065]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #132]
	subeq	r3, r3, #1
	subne	r3, r3, #2
	str	r3, [r4, #132]
	b	.L4533
.L4583:
	mov	r3, #0
	movw	r2, #13671
	ldr	r1, .L4585+12
	mov	r0, #22
	bl	dprint_vfmw
	b	.L4536
.L4578:
	mov	r0, r1
	ldr	r3, .L4585+16
	movw	r2, #13553
	ldr	r1, .L4585+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4572
.L4577:
	ldr	r3, .L4585+24
	movw	r2, #13552
	ldr	r1, .L4585+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4572
.L4584:
	ldr	r3, [fp, #-44]
	cmp	r3, #32
	bgt	.L4533
	ldr	r3, [r4, #228]
	cmp	r3, #0
	bne	.L4533
	ldr	r3, [r4, #88]
	cmp	r3, #0
	beq	.L4527
	ldr	r1, [r4, #12]
	cmp	r1, #0
	beq	.L4527
	add	r5, r4, #11141120
	ldr	lr, [r4, #16]
	add	r5, r5, #16384
	ldr	r0, [r5, #2640]
	cmp	lr, r0
	beq	.L4527
	ldr	ip, [r5, #2644]
	cmp	r1, ip
	beq	.L4527
	stmib	sp, {r0, r1, lr}
	mov	r0, r2
	str	ip, [sp]
	ldr	r1, .L4585+28
	bl	dprint_vfmw
	ldr	r2, .L4585
	ldr	r3, [r4, #16]
	ldr	r7, [r2]
	str	r3, [r5, #2640]
	ldr	r3, [r4, #12]
	cmp	r7, #0
	str	r3, [r5, #2644]
	beq	.L4527
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #120]
	blx	r7
	b	.L4527
.L4586:
	.align	2
.L4585:
	.word	g_event_report
	.word	.LC491
	.word	.LANCHOR1+432
	.word	.LC448
	.word	.LC489
	.word	.LC24
	.word	.LC23
	.word	.LC490
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
	subs	r4, r0, #0
	beq	.L4600
	ldr	r2, [r4, #228]
	add	r5, r4, #11141120
	add	r5, r5, #16384
	ldrb	ip, [r2, #17]	@ zero_extendqisi2
	ldr	r3, [r5, #40]
	strb	ip, [r3, #14]
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	strb	r2, [r3, #15]
	ldrb	r7, [r4]	@ zero_extendqisi2
	str	r1, [r5, #92]
	cmp	r7, #0
	beq	.L4601
	bl	MVC_ClearAllSlice
	mov	r0, r4
	bl	MVC_StorePicInDpb
	subs	r2, r0, #0
	bne	.L4602
.L4592:
	mvn	r1, #0
	mov	r0, r4
	bl	MVC_FlushDPB
	subs	r2, r0, #0
	bne	.L4603
.L4593:
	ldr	ip, [r4, #40]
	add	r3, r4, #11075584
	add	r3, r3, #40960
	mov	r2, #0
	movw	r1, #23352
	strb	r2, [r4, #4]
	mov	r0, r2
	movt	r1, 1
	str	ip, [r3, #2732]
	mov	r5, #2
	strb	r2, [r3, #2720]
	mov	r4, #7
	str	r2, [r3, #2752]
	mov	lr, #32
	str	r2, [r3, #2756]
	mov	ip, #3
	str	r1, [r3, #2736]
	mov	r2, #262144
	mvn	r1, #0
	strb	r5, [r3, #2721]
	strb	r4, [r3, #2723]
	strb	lr, [r3, #2722]
	str	ip, [r3, #2744]
	str	r1, [r3, #2748]
	str	r2, [r3, #2760]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4601:
	bl	MVC_ClearAllSlice
	mov	r0, r4
	bl	MVC_StorePicInDpb
	subs	r6, r0, #0
	bne	.L4604
	mov	r3, #1
	mov	r0, r6
	strb	r3, [r4, #4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4604:
	ldr	r3, [r5, #40]
	mov	r2, #1
	ldr	r0, [r4, #120]
	ldrsb	r1, [r3, #6]
	bl	FSP_ClearLogicFs
	mov	r2, r6
	ldr	r1, .L4605
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	MVC_ClearCurrPic
	mov	r0, r4
	mvn	r1, #0
	bl	MVC_ClearDPB
	str	r7, [r5, #40]
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4600:
	ldr	r3, .L4605+4
	movw	r2, #13800
	ldr	r1, .L4605+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4603:
	ldr	r1, .L4605+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4593
.L4602:
	ldr	r1, .L4605+16
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4592
.L4606:
	.align	2
.L4605:
	.word	.LC492
	.word	.LC23
	.word	.LC24
	.word	.LC494
	.word	.LC493
	UNWIND(.fnend)
	.size	MVC_DEC_VDMPostProc, .-MVC_DEC_VDMPostProc
	.align	2
	.global	MVC_DEC_GetImageBuffer
	.type	MVC_DEC_GetImageBuffer, %function
MVC_DEC_GetImageBuffer:
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
	subs	r5, r0, #0
	beq	.L4646
	ldr	r7, [r5, #48]
	cmp	r7, #0
	beq	.L4624
	movw	r4, #48344
	movw	r9, #47784
	movt	r4, 169
	add	r8, r5, #11075584
	add	r4, r5, r4
	movt	r9, 169
	add	r8, r8, #45056
	add	r9, r5, r9
	mov	ip, r4
	mov	r6, #0
.L4616:
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4611
	cmp	ip, #0
	beq	.L4612
	ldr	lr, [r8, #2920]
	cmp	lr, #0
	beq	.L4612
	ldr	r2, [r8, #2728]
	rsb	r3, ip, r2
	cmp	r2, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	moveq	r3, #0
	cmp	r3, #0
	bne	.L4611
	mov	r1, r9
	b	.L4613
.L4614:
	ldr	r2, [r1, #4]!
	rsb	r0, ip, r2
	cmp	r2, #0
	clz	r0, r0
	mov	r0, r0, lsr #5
	moveq	r0, #0
	cmp	r0, #0
	bne	.L4611
.L4613:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L4614
.L4612:
	ldr	r0, [r5, #120]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L4624
	ldr	r0, [r5, #120]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	bne	.L4644
	add	r1, r5, #584
	ldr	r0, [r5, #120]
	bl	FSP_ClearNotInVoQueue
	b	.L4644
.L4611:
	add	r6, r6, #1
	add	ip, ip, #824
	cmp	r6, r7
	bne	.L4616
	sub	r2, fp, #40
	sub	r1, fp, #44
	add	r0, r5, #584
	bl	GetQueueImgNum
	ldr	r1, .L4649
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, .L4649+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	cmp	r3, #0
	beq	.L4647
	movw	r8, #47784
	add	r7, r5, #11075584
	movt	r8, 169
	add	r7, r7, #45056
	add	r8, r5, r8
	mov	r6, #0
.L4617:
	cmp	r4, #0
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	ldrb	r9, [r4, #5]	@ zero_extendqisi2
	beq	.L4628
	ldr	lr, [r7, #2920]
	cmp	lr, #0
	beq	.L4628
	ldr	r1, [r7, #2728]
	rsb	r2, r4, r1
	cmp	r1, #0
	clz	r2, r2
	mov	r2, r2, lsr #5
	moveq	r2, #0
	cmp	r2, #0
	bne	.L4630
	mov	r0, r8
	b	.L4621
.L4622:
	ldr	r1, [r0, #4]!
	rsb	ip, r4, r1
	cmp	r1, #0
	clz	ip, ip
	mov	ip, ip, lsr #5
	moveq	ip, #0
	cmp	ip, #0
	bne	.L4630
.L4621:
	add	r2, r2, #1
	cmp	r2, lr
	bne	.L4622
.L4628:
	mov	r2, #1
.L4620:
	str	r2, [sp, #4]
	mov	r0, #0
	mov	r2, r6
	str	r9, [sp]
	ldr	r1, .L4649+8
	add	r6, r6, #1
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	add	r4, r4, #824
	cmp	r3, r6
	bhi	.L4617
.L4623:
	ldr	r3, [fp, #-40]
	mov	r0, #0
	ldr	r2, [fp, #-44]
	ldr	r1, .L4649+12
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	ldr	r0, [r7, #2924]
	ldr	r2, [fp, #-44]
	sub	r3, r3, #2
	ldr	r1, [fp, #-40]
	rsb	r3, r0, r3
	add	r2, r2, r1
	cmp	r2, r3
	blt	.L4648
.L4644:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4624:
	mov	r0, #1
.L4642:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4630:
	mov	r2, #0
	b	.L4620
.L4648:
	ldr	r1, .L4649+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	mov	r1, #1
	bl	MVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4647:
	add	r7, r5, #11075584
	add	r7, r7, #45056
	b	.L4623
.L4646:
	ldr	r3, .L4649+20
	movw	r2, #13855
	ldr	r1, .L4649+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4642
.L4650:
	.align	2
.L4649:
	.word	.LC495
	.word	.LC496
	.word	.LC498
	.word	.LC497
	.word	.LC499
	.word	.LC23
	.word	.LC24
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
	.type	__FUNCTION__.14752, %object
	.size	__FUNCTION__.14752, 18
__FUNCTION__.14752:
	.ascii	"MVC_WriteSliceMsg\000"
	.space	2
	.type	MVC_SarTable.15042, %object
	.size	MVC_SarTable.15042, 136
MVC_SarTable.15042:
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
	.type	__func__.15276, %object
	.size	__func__.15276, 11
__func__.15276:
	.ascii	"MVC_DecSEI\000"
	.space	1
	.type	__func__.13932, %object
	.size	__func__.13932, 17
__func__.13932:
	.ascii	"MVC_DirectOutput\000"
	.space	3
	.type	__func__.14512, %object
	.size	__func__.14512, 12
__func__.14512:
	.ascii	"MVC_InitDPB\000"
	.type	__FUNCTION__.13652, %object
	.size	__FUNCTION__.13652, 13
__FUNCTION__.13652:
	.ascii	"MVC_ClearDPB\000"
	.space	3
	.type	__func__.15387, %object
	.size	__func__.15387, 17
__func__.15387:
	.ascii	"MVC_FlushDecoder\000"
	.space	3
	.type	__FUNCTION__.13660, %object
	.size	__FUNCTION__.13660, 13
__FUNCTION__.13660:
	.ascii	"MVC_ClearAll\000"
	.space	3
	.type	__FUNCTION__.15514, %object
	.size	__FUNCTION__.15514, 13
__FUNCTION__.15514:
	.ascii	"MVC_DEC_Init\000"
	.space	3
	.type	__func__.14082, %object
	.size	__func__.14082, 18
__func__.14082:
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
	ASCII(.ascii	"../../core/syntax/mvc.c\000" )
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
	ASCII(.ascii	"\012 VFMW ** release streambuff=%p   bitstream_leng" )
	ASCII(.ascii	"th=%d\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"clear curr slice.\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"pMvcCtx = NULL\000" )
	.space	1
.LC24:
	ASCII(.ascii	"mvc.c,L%d: %s\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC26:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"for P slice size of list equal 0(1st).\012\000" )
.LC29:
	ASCII(.ascii	"for P slice size of list equal 0(2nd).\012\000" )
.LC30:
	ASCII(.ascii	"for B slice size of two list all equal 0.\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"list[%d][%d]: frame_num=%d, poc=%d\012\000" )
.LC32:
	ASCII(.ascii	"init list error.\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"In one access unit,all non-base view should have th" )
	ASCII(.ascii	"e same subsps!\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"sps but mvc flag %d is wrong\012\000" )
	.space	2
.LC35:
	ASCII(.ascii	"save pic yuv :  structure = %d;  idc = %d\012\000" )
	.space	1
.LC36:
	ASCII(.ascii	"structure = %d pMvcCtx->CurrPic.pic_width_in_mb = %" )
	ASCII(.ascii	"d pMvcCtx->CurrPic.pic_height_in_mb = %d\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"logic MVC_FRAME id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"fuction return value is null,%s %d unknow error!!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC41:
	ASCII(.ascii	"SH: first_mb_in_slice\000" )
	.space	2
.LC42:
	ASCII(.ascii	"MVC_SliceCheck first_mb_in_slice >= MAX_MB_NUM_IN_P" )
	ASCII(.ascii	"IC error.\012\000" )
	.space	2
.LC43:
	ASCII(.ascii	"SH: slice_type\000" )
	.space	1
.LC44:
	ASCII(.ascii	"slice type = %d\012\000" )
	.space	3
.LC45:
	ASCII(.ascii	"slice type = %d, err\012\000" )
	.space	2
.LC46:
	ASCII(.ascii	"slice  pps id = %d\012\000" )
.LC47:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't deco" )
	ASCII(.ascii	"de\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"sps with this pic_parameter_set_id havn't decode\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC49:
	ASCII(.ascii	"subsps with this seq_parameter_set_id = %d havn't d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"tmp slice  pps id = %d\012\000" )
.LC51:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: pps with this pic_parameter_s" )
	ASCII(.ascii	"et_id = %d havn't decode\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: seq_parameter_set_id out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"MVC_PPSSPSCheckTmpId: sps with this pic_parameter_s" )
	ASCII(.ascii	"et_id = %d havn't decode\012\000" )
	.space	3
.LC54:
	ASCII(.ascii	"new pic flag = %d\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l0\000" )
.LC56:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l0\000" )
	.space	2
.LC57:
	ASCII(.ascii	"reorder idc l0 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l0\000" )
	.space	1
.LC59:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC60:
	ASCII(.ascii	"SH: long_term_pic_idx_l0\000" )
	.space	3
.LC61:
	ASCII(.ascii	"SH: abs_diff_view_idx_minus1_l0\000" )
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
	ASCII(.ascii	"SH: abs_diff_view_idx_minus1_l1\000" )
.LC70:
	ASCII(.ascii	"num of idc l1 exceed\012\000" )
	.space	2
.LC71:
	ASCII(.ascii	"SH: luma_log2_weight_denom\000" )
	.space	1
.LC72:
	ASCII(.ascii	"SH: chroma_log2_weight_denom\000" )
	.space	3
.LC73:
	ASCII(.ascii	"WP log2 exceed  and err flag = %d\012\000" )
	.space	1
.LC74:
	ASCII(.ascii	"SH: luma_weight_flag_l0\000" )
.LC75:
	ASCII(.ascii	"SH: luma_weight_l0\000" )
	.space	1
.LC76:
	ASCII(.ascii	"SH: luma_offset_l0\000" )
	.space	1
.LC77:
	ASCII(.ascii	"SH: chroma_weight_flag_l0\000" )
	.space	2
.LC78:
	ASCII(.ascii	"SH: chroma_weight_l0\000" )
	.space	3
.LC79:
	ASCII(.ascii	"SH: chroma_offset_l0\000" )
	.space	3
.LC80:
	ASCII(.ascii	"SH: luma_weight_flag_l1\000" )
.LC81:
	ASCII(.ascii	"SH: luma_weight_l1\000" )
	.space	1
.LC82:
	ASCII(.ascii	"SH: luma_offset_l1\000" )
	.space	1
.LC83:
	ASCII(.ascii	"SH: chroma_weight_flag_l1\000" )
	.space	2
.LC84:
	ASCII(.ascii	"SH: chroma_weight_l1\000" )
	.space	3
.LC85:
	ASCII(.ascii	"SH: chroma_offset_l1\000" )
	.space	3
.LC86:
	ASCII(.ascii	"overflow MVC_MAX_MMCO_LEN\012\000" )
	.space	1
.LC87:
	ASCII(.ascii	"SH: memory_management_control_operation\000" )
.LC88:
	ASCII(.ascii	"SH: difference_of_pic_nums_minus1\000" )
	.space	2
.LC89:
	ASCII(.ascii	"SH: long_term_pic_num\000" )
	.space	2
.LC90:
	ASCII(.ascii	"SH: long_term_frame_idx\000" )
.LC91:
	ASCII(.ascii	"SH: max_long_term_frame_idx_plus1\000" )
	.space	2
.LC92:
	ASCII(.ascii	"mmco exceed 6\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"SH: no_output_of_prior_pics_flag\000" )
	.space	3
.LC94:
	ASCII(.ascii	"SH: long_term_reference_flag\000" )
	.space	3
.LC95:
	ASCII(.ascii	"IDR and no_output_of_prior_pics_flag = %d\012\000" )
	.space	1
.LC96:
	ASCII(.ascii	"SH: adaptive_ref_pic_marking_mode_flag\000" )
	.space	1
.LC97:
	ASCII(.ascii	"adaptive_ref_pic_marking_mode_flag = %d\012\000" )
	.space	3
.LC98:
	ASCII(.ascii	"MMCO para would save dec err\012\000" )
	.space	2
.LC99:
	ASCII(.ascii	"mulitislice diff no_out_of_prior_pics_flag, used fi" )
	ASCII(.ascii	"rst.\012\000" )
	.space	3
.LC100:
	ASCII(.ascii	"mulitislice diff long_term_reference_flag, used fir" )
	ASCII(.ascii	"st.\012\000" )
.LC101:
	ASCII(.ascii	"mulitislice diff adaptive_ref_pic_marking_mode_flag" )
	ASCII(.ascii	", used first.\012\000" )
	.space	2
.LC102:
	ASCII(.ascii	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\012\000" )
	.space	1
.LC103:
	ASCII(.ascii	"SH: pic_parameter_set_id\000" )
	.space	3
.LC104:
	ASCII(.ascii	"pps id:%d in sliceheader err\012\000" )
	.space	2
.LC105:
	ASCII(.ascii	"PPS or SPS of this slice not valid\012\000" )
.LC106:
	ASCII(.ascii	"MVC_PPSSPSCheck failed, PPS or SPS of this slice no" )
	ASCII(.ascii	"t valid\012\000" )
.LC107:
	ASCII(.ascii	"SH: frame_num\000" )
	.space	2
.LC108:
	ASCII(.ascii	"IDR NAL but frame_num!=0.\012\000" )
	.space	1
.LC109:
	ASCII(.ascii	"SH: field_pic_flag\000" )
	.space	1
.LC110:
	ASCII(.ascii	"SH: bottom_field_flag\000" )
	.space	2
.LC111:
	ASCII(.ascii	"field first_mb_in_slice bigger than pic size\012\000" )
	.space	2
.LC112:
	ASCII(.ascii	"MVC_FRAME first_mb_in_slice bigger than pic size\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC113:
	ASCII(.ascii	"SH: idr_pic_id\000" )
	.space	1
.LC114:
	ASCII(.ascii	"idr_pic_id bigger than 65535\012\000" )
	.space	2
.LC115:
	ASCII(.ascii	"SH: pic_order_cnt_lsb\000" )
	.space	2
.LC116:
	ASCII(.ascii	"SH: delta_pic_order_cnt_bottom\000" )
	.space	1
.LC117:
	ASCII(.ascii	"SH: delta_pic_order_cnt[0]\000" )
	.space	1
.LC118:
	ASCII(.ascii	"SH: delta_pic_order_cnt[1]\000" )
	.space	1
.LC119:
	ASCII(.ascii	"SH: redundant_pic_cnt\000" )
	.space	2
.LC120:
	ASCII(.ascii	"redundant pic not support.\012\000" )
.LC121:
	ASCII(.ascii	"first_mb_in_slice in currslice small than prevslice" )
	ASCII(.ascii	" in same pic\012\000" )
	.space	3
.LC122:
	ASCII(.ascii	"SH: direct_spatial_mv_pred_flag\000" )
.LC123:
	ASCII(.ascii	"SH: num_ref_idx_override_flag\000" )
	.space	2
.LC124:
	ASCII(.ascii	"SH: num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC125:
	ASCII(.ascii	"SH: num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC126:
	ASCII(.ascii	"MVC_FRAME num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC127:
	ASCII(.ascii	"field num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC128:
	ASCII(.ascii	"reordering para dec err\012\000" )
	.space	3
.LC129:
	ASCII(.ascii	"apply_weights_flag=%d\012\000" )
	.space	1
.LC130:
	ASCII(.ascii	"wpt dec err\012\000" )
	.space	3
.LC131:
	ASCII(.ascii	"mark para dec err\012\000" )
	.space	1
.LC132:
	ASCII(.ascii	"SH: cabac_init_idc\000" )
	.space	1
.LC133:
	ASCII(.ascii	"cabac_init_idc bigger than 3\012\000" )
	.space	2
.LC134:
	ASCII(.ascii	"SH: slice_qp_delta\000" )
	.space	1
.LC135:
	ASCII(.ascii	"SH: disable_deblocking_filter_idc\000" )
	.space	2
.LC136:
	ASCII(.ascii	"disable_deblocking_filter_idc dec err\012\000" )
	.space	1
.LC137:
	ASCII(.ascii	"SH: slice_alpha_c0_offset_div2\000" )
	.space	1
.LC138:
	ASCII(.ascii	"slice_alpha_c0_offset_div2 dec err\012\000" )
.LC139:
	ASCII(.ascii	"SH: slice_beta_offset_div2\000" )
	.space	1
.LC140:
	ASCII(.ascii	"slice_beta_offset_div2 dec err\012\000" )
.LC141:
	ASCII(.ascii	"pMvcCtx->pCurrNal->nal_bitoffset = %d; code_len_byt" )
	ASCII(.ascii	"e = %d; bitstream_length = %d; pMvcCtx->pCurrNal->n" )
	ASCII(.ascii	"al_trail_zero_bit_num = %d\012\000" )
	.space	2
.LC142:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; byt" )
	ASCII(.ascii	"espos = %x\012\000" )
	.space	1
.LC143:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC144:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\012\000" )
.LC145:
	ASCII(.ascii	"   : delta_sl   \000" )
	.space	3
.LC146:
	ASCII(.ascii	"PPS: entropy_coding_mode_flag\000" )
	.space	2
.LC147:
	ASCII(.ascii	"PPS: pic_order_present_flag\000" )
.LC148:
	ASCII(.ascii	"PPS: num_slice_groups_minus1\000" )
	.space	3
.LC149:
	ASCII(.ascii	"MVC_BASELINE stream with FMO, not support.\012\000" )
.LC150:
	ASCII(.ascii	"PPS: num_ref_idx_l0_active_minus1\000" )
	.space	2
.LC151:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1 out of range.\012\000" )
.LC152:
	ASCII(.ascii	"PPS: num_ref_idx_l1_active_minus1\000" )
	.space	2
.LC153:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1 out of range.\012\000" )
.LC154:
	ASCII(.ascii	"PPS: weighted prediction flag\000" )
	.space	2
.LC155:
	ASCII(.ascii	"PPS: weighted_bipred_idc\000" )
	.space	3
.LC156:
	ASCII(.ascii	"weighted_bipred_idc out of range\012\000" )
	.space	2
.LC157:
	ASCII(.ascii	"PPS: pic_init_qp_minus26\000" )
	.space	3
.LC158:
	ASCII(.ascii	"PPS: pic_init_qs_minus26\000" )
	.space	3
.LC159:
	ASCII(.ascii	"PPS: chroma_qp_index_offset\000" )
.LC160:
	ASCII(.ascii	"PPS: deblocking_filter_control_present_flag\000" )
.LC161:
	ASCII(.ascii	"PPS: constrained_intra_pred_flag\000" )
	.space	3
.LC162:
	ASCII(.ascii	"PPS: redundant_pic_cnt_present_flag\000" )
.LC163:
	ASCII(.ascii	"redundant pic not support when find redundant slice" )
	ASCII(.ascii	" later, exit\012\000" )
	.space	3
.LC164:
	ASCII(.ascii	"PPS: transform_8x8_mode_flag\000" )
	.space	3
.LC165:
	ASCII(.ascii	"PPS: pic_scaling_matrix_present_flag\000" )
	.space	3
.LC166:
	ASCII(.ascii	"PPS: second_chroma_qp_index_offset\000" )
	.space	1
.LC167:
	ASCII(.ascii	"SPS: seq_scaling_list_present_flag\000" )
	.space	1
.LC168:
	ASCII(.ascii	"PPS: pic_scaling_list_present_flag\000" )
	.space	1
.LC169:
	ASCII(.ascii	"second_chroma_qp_index_offset out of range.\012\000" )
	.space	3
.LC170:
	ASCII(.ascii	"PPS: pic_parameter_set_id\000" )
	.space	2
.LC171:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range.\012\000" )
.LC172:
	ASCII(.ascii	"PPS: seq_parameter_set_id\000" )
	.space	2
.LC173:
	ASCII(.ascii	"seq_parameter_set_id out of range.\012\000" )
.LC174:
	ASCII(.ascii	"PPS decode error line: %d.\012\000" )
.LC175:
	ASCII(.ascii	"VUI: aspect_ratio_info_present_flag\000" )
.LC176:
	ASCII(.ascii	"VUI: aspect_ratio_idc\000" )
	.space	2
.LC177:
	ASCII(.ascii	"VUI: sar_width\000" )
	.space	1
.LC178:
	ASCII(.ascii	"VUI: sar_height\000" )
.LC179:
	ASCII(.ascii	"VUI: overscan_info_present_flag\000" )
.LC180:
	ASCII(.ascii	"VUI: overscan_appropriate_flag\000" )
	.space	1
.LC181:
	ASCII(.ascii	"VUI: video_signal_type_present_flag\000" )
.LC182:
	ASCII(.ascii	"VUI: video_format\000" )
	.space	2
.LC183:
	ASCII(.ascii	"VUI: video_full_range_flag\000" )
	.space	1
.LC184:
	ASCII(.ascii	"VUI: color_description_present_flag\000" )
.LC185:
	ASCII(.ascii	"VUI: colour_primaries\000" )
	.space	2
.LC186:
	ASCII(.ascii	"VUI: transfer_characteristics\000" )
	.space	2
.LC187:
	ASCII(.ascii	"VUI: matrix_coefficients\000" )
	.space	3
.LC188:
	ASCII(.ascii	"VUI: chroma_loc_info_present_flag\000" )
	.space	2
.LC189:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_top_field\000" )
	.space	2
.LC190:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_bottom_field\000" )
	.space	3
.LC191:
	ASCII(.ascii	"VUI: timing_info_present_flag\000" )
	.space	2
.LC192:
	ASCII(.ascii	"VUI: num_units_in_tick\000" )
	.space	1
.LC193:
	ASCII(.ascii	"VUI: time_scale\000" )
.LC194:
	ASCII(.ascii	"VUI: fixed_frame_rate_flag\000" )
	.space	1
.LC195:
	ASCII(.ascii	"VUI: nal_hrd_parameters_present_flag\000" )
	.space	3
.LC196:
	ASCII(.ascii	"VUI: cpb_cnt_minus1\000" )
.LC197:
	ASCII(.ascii	"VUI: bit_rate_scale\000" )
.LC198:
	ASCII(.ascii	"VUI: cpb_size_scale\000" )
.LC199:
	ASCII(.ascii	"hrd->cpb_cnt_minus1 out of range\012\000" )
	.space	2
.LC200:
	ASCII(.ascii	"VUI: bit_rate_value_minus1\000" )
	.space	1
.LC201:
	ASCII(.ascii	"VUI: cpb_size_value_minus1\000" )
	.space	1
.LC202:
	ASCII(.ascii	"VUI: cbr_flag\000" )
	.space	2
.LC203:
	ASCII(.ascii	"VUI: initial_cpb_removal_delay_length_minus1\000" )
	.space	3
.LC204:
	ASCII(.ascii	"VUI: cpb_removal_delay_length_minus1\000" )
	.space	3
.LC205:
	ASCII(.ascii	"VUI: dpb_output_delay_length_minus1\000" )
.LC206:
	ASCII(.ascii	"VUI: time_offset_length\000" )
.LC207:
	ASCII(.ascii	"VUI: vcl_hrd_parameters_present_flag\000" )
	.space	3
.LC208:
	ASCII(.ascii	"VUI: low_delay_hrd_flag\000" )
.LC209:
	ASCII(.ascii	"VUI: pic_struct_present_flag\000" )
	.space	3
.LC210:
	ASCII(.ascii	"VUI: bitstream_restriction_flag\000" )
.LC211:
	ASCII(.ascii	"VUI: motion_vectors_over_pic_boundaries_flag\000" )
	.space	3
.LC212:
	ASCII(.ascii	"VUI: max_bytes_per_pic_denom\000" )
	.space	3
.LC213:
	ASCII(.ascii	"VUI: max_bits_per_mb_denom\000" )
	.space	1
.LC214:
	ASCII(.ascii	"VUI: log2_max_mv_length_horizontal\000" )
	.space	1
.LC215:
	ASCII(.ascii	"VUI: log2_max_mv_length_vertical\000" )
	.space	3
.LC216:
	ASCII(.ascii	"VUI: num_reorder_frames\000" )
.LC217:
	ASCII(.ascii	"VUI: max_dec_frame_buffering\000" )
	.space	3
.LC218:
	ASCII(.ascii	"dar=%d, final_dar=%d\012\000" )
	.space	2
.LC219:
	ASCII(.ascii	"SPS: chroma_format_idc\000" )
	.space	1
.LC220:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range.\012\000" )
	.space	1
.LC221:
	ASCII(.ascii	"SPS: bit_depth_luma_minus8\000" )
	.space	1
.LC222:
	ASCII(.ascii	"bit_depth_luma_minus8 not equal 0.\012\000" )
.LC223:
	ASCII(.ascii	"SPS: bit_depth_chroma_minus8\000" )
	.space	3
.LC224:
	ASCII(.ascii	"bit_depth_chroma_minus8 not equal 0.\012\000" )
	.space	2
.LC225:
	ASCII(.ascii	"SPS: qpprime_y_zero_trans_bypass_flag\000" )
	.space	2
.LC226:
	ASCII(.ascii	"qpprime_y_zero_trans_bypass_flag not equal 0.\012\000" )
	.space	1
.LC227:
	ASCII(.ascii	"SPS: seq_scaling_matrix_present_flag\000" )
	.space	3
.LC228:
	ASCII(.ascii	"SPS: log2_max_frame_num_minus4\000" )
	.space	1
.LC229:
	ASCII(.ascii	"pSPS->log2_max_frame_num_minus4 out of range.\012\000" )
	.space	1
.LC230:
	ASCII(.ascii	"SPS: pic_order_cnt_type\000" )
.LC231:
	ASCII(.ascii	"pSPS->pic_order_cnt_type out of range.\012\000" )
.LC232:
	ASCII(.ascii	"SPS: log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	1
.LC233:
	ASCII(.ascii	"SPS: num_ref_frames\000" )
.LC234:
	ASCII(.ascii	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of rang" )
	ASCII(.ascii	"e.\012\000" )
	.space	1
.LC235:
	ASCII(.ascii	"SPS: delta_pic_order_always_zero_flag\000" )
	.space	2
.LC236:
	ASCII(.ascii	"SPS: offset_for_non_ref_pic\000" )
.LC237:
	ASCII(.ascii	"SPS: offset_for_top_to_bottom_field\000" )
.LC238:
	ASCII(.ascii	"SPS: num_ref_frames_in_pic_order_cnt_cycle\000" )
	.space	1
.LC239:
	ASCII(.ascii	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of " )
	ASCII(.ascii	"range.\012\000" )
	.space	1
.LC240:
	ASCII(.ascii	"SPS: offset_for_ref_frame[i]\000" )
	.space	3
.LC241:
	ASCII(.ascii	"SPS: gaps_in_frame_num_value_allowed_flag\000" )
	.space	2
.LC242:
	ASCII(.ascii	"SPS: pic_width_in_mbs_minus1\000" )
	.space	3
.LC243:
	ASCII(.ascii	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC244:
	ASCII(.ascii	"SPS: pic_height_in_map_units_minus1\000" )
.LC245:
	ASCII(.ascii	"SPS: frame_mbs_only_flag\000" )
	.space	3
.LC246:
	ASCII(.ascii	"pSPS->pic_height_in_map_units_minus1 out of range.\012" )
	ASCII(.ascii	"\000" )
.LC247:
	ASCII(.ascii	"pic size too large.\012\000" )
	.space	3
.LC248:
	ASCII(.ascii	"level_idc %d not support.\012\000" )
	.space	1
.LC249:
	ASCII(.ascii	"dpb size according level : %d\012\000" )
	.space	1
.LC250:
	ASCII(.ascii	"pSPS->num_ref_frames(%d) > DPB size(%d), try to sel" )
	ASCII(.ascii	"ect the reasonable one.\012\000" )
.LC251:
	ASCII(.ascii	"SPS: direct_8x8_inference_flag\000" )
	.space	1
.LC252:
	ASCII(.ascii	"SPS: frame_cropping_flag\000" )
	.space	3
.LC253:
	ASCII(.ascii	"SPS: frame_cropping_rect_left_offset\000" )
	.space	3
.LC254:
	ASCII(.ascii	"SPS: frame_cropping_rect_right_offset\000" )
	.space	2
.LC255:
	ASCII(.ascii	"SPS: frame_cropping_rect_top_offset\000" )
.LC256:
	ASCII(.ascii	"SPS: frame_cropping_rect_bottom_offset\000" )
	.space	1
.LC257:
	ASCII(.ascii	"SPS: vui_parameters_present_flag\000" )
	.space	3
.LC258:
	ASCII(.ascii	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\012\000" )
	.space	2
.LC259:
	ASCII(.ascii	"SPS: mb_adaptive_frame_field_flag\000" )
	.space	2
.LC260:
	ASCII(.ascii	"SPS: profile_idc\000" )
	.space	3
.LC261:
	ASCII(.ascii	"SPS: constrained_set0_flag\000" )
	.space	1
.LC262:
	ASCII(.ascii	"SPS: constrained_set1_flag\000" )
	.space	1
.LC263:
	ASCII(.ascii	"SPS: constrained_set2_flag\000" )
	.space	1
.LC264:
	ASCII(.ascii	"SPS: constrained_set3_flag\000" )
	.space	1
.LC265:
	ASCII(.ascii	"SPS: constrained_set4_flag\000" )
	.space	1
.LC266:
	ASCII(.ascii	"SPS: constrained_set5_flag\000" )
	.space	1
.LC267:
	ASCII(.ascii	"SPS: reserved_zero_2bits\000" )
	.space	3
.LC268:
	ASCII(.ascii	"SPS: level_idc\000" )
	.space	1
.LC269:
	ASCII(.ascii	"SPS: seq_parameter_set_id\000" )
	.space	2
.LC270:
	ASCII(.ascii	"MVC_BASELINE stream, try to decode, exit when FMO o" )
	ASCII(.ascii	"ccurred.\012\000" )
	.space	3
.LC271:
	ASCII(.ascii	"MVC_EXTENDED stream, try to decode, exit when datap" )
	ASCII(.ascii	"artition occurred.\012\000" )
	.space	1
.LC272:
	ASCII(.ascii	"others High profile stream, try to decode, exit whe" )
	ASCII(.ascii	"n high profile not support occurred.\012\000" )
	.space	3
.LC273:
	ASCII(.ascii	"profile_idc = %5d error, try to decode as main prof" )
	ASCII(.ascii	"ile.\012\000" )
	.space	3
.LC274:
	ASCII(.ascii	"level_idc = %5d error, try to decode as level_idc %" )
	ASCII(.ascii	"d.\012\000" )
	.space	1
.LC275:
	ASCII(.ascii	"Line %d: SPS[%d] decode error.\012\000" )
.LC276:
	ASCII(.ascii	"SUBSPS: num_views_minus1\000" )
	.space	3
.LC277:
	ASCII(.ascii	"pSubsps->num_views_minus1(%d) out of range.\012\000" )
	.space	3
.LC278:
	ASCII(.ascii	"SUBSPS: view_id[]\000" )
	.space	2
.LC279:
	ASCII(.ascii	"SUBSPS: num_anchor_refs_l0[]\000" )
	.space	3
.LC280:
	ASCII(.ascii	"SUBSPS: num_anchor_refs_l1[]\000" )
	.space	3
.LC281:
	ASCII(.ascii	"pSubsps->num_anchor_refs_l0(%d) out of range.\012\000" )
	.space	1
.LC282:
	ASCII(.ascii	"SUBSPS: anchor_ref_l0[][]\000" )
	.space	2
.LC283:
	ASCII(.ascii	"pSubsps->num_anchor_refs_l1(%d) out of range.\012\000" )
	.space	1
.LC284:
	ASCII(.ascii	"SUBSPS: anchor_ref_l1[][]\000" )
	.space	2
.LC285:
	ASCII(.ascii	"SUBSPS: num_level_values_signalled_minus1\000" )
	.space	2
.LC286:
	ASCII(.ascii	"SUBSPS: num_non_anchor_refs_l0[]\000" )
	.space	3
.LC287:
	ASCII(.ascii	"SUBSPS: num_non_anchor_refs_l1[]\000" )
	.space	3
.LC288:
	ASCII(.ascii	"pSubsps->num_non_anchor_refs_l0(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC289:
	ASCII(.ascii	"SUBSPS: non_anchor_ref_l0[][]\000" )
	.space	2
.LC290:
	ASCII(.ascii	"pSubsps->num_non_anchor_refs_l1(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC291:
	ASCII(.ascii	"SUBSPS: non_anchor_ref_l1[][]\000" )
	.space	2
.LC292:
	ASCII(.ascii	"num_level(%d) out of range.\012\000" )
	.space	3
.LC293:
	ASCII(.ascii	"SUBSPS: level_idc[]\000" )
.LC294:
	ASCII(.ascii	"SUBSPS: num_applicable_ops_minus1\000" )
	.space	2
.LC295:
	ASCII(.ascii	"num_ops(%d) out of range.\012\000" )
	.space	1
.LC296:
	ASCII(.ascii	"SUBSPS: applicable_op_temporal_id[][]\000" )
	.space	2
.LC297:
	ASCII(.ascii	"SUBSPS: applicable_op_num_target_views_minus1[][]\000" )
	.space	2
.LC298:
	ASCII(.ascii	"SUBSPS: applicable_op_num_views_minus1\000" )
	.space	1
.LC299:
	ASCII(.ascii	"applicable_op_num_target_views(%d) out of range.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC300:
	ASCII(.ascii	"SUBSPS: applicable_op_target_view_id[][][]\000" )
	.space	1
.LC301:
	ASCII(.ascii	"pSubsps->applicable_op_num_views_minus1(%d) out of " )
	ASCII(.ascii	"range.\012\000" )
	.space	1
.LC302:
	ASCII(.ascii	"MVC VUI: vui_mvc_num_ops_minus1\000" )
.LC303:
	ASCII(.ascii	"vui_mvc_num_ops_minus1 %d out of range\012\000" )
.LC304:
	ASCII(.ascii	"MVC VUI: vui_mvc_temporal_id[]\000" )
	.space	1
.LC305:
	ASCII(.ascii	"SUBSPS VUI: vui_mvc_num_target_output_views_minus1[" )
	ASCII(.ascii	"]\000" )
	.space	3
.LC306:
	ASCII(.ascii	"vui_mvc_num_target_output_views_minus1 %d out of ra" )
	ASCII(.ascii	"nge\012\000" )
.LC307:
	ASCII(.ascii	"MVC VUI: vui_mvc_timing_info_present_flag\000" )
	.space	2
.LC308:
	ASCII(.ascii	"MVC VUI: vui_mvc_view_id[][]\000" )
	.space	3
.LC309:
	ASCII(.ascii	"MVC VUI: vui_mvc_num_units_in_tick\000" )
	.space	1
.LC310:
	ASCII(.ascii	"MVC VUI: vui_mvc_time_scale[]\000" )
	.space	2
.LC311:
	ASCII(.ascii	"MVC VUI: vui_mvc_fixed_frame_rate_flag\000" )
	.space	1
.LC312:
	ASCII(.ascii	"MVC VUI: vui_mvc_nal_hrd_parameters_present_flag[]\000" )
	.space	1
.LC313:
	ASCII(.ascii	"MVC VUI: cpb_cnt_minus1\000" )
.LC314:
	ASCII(.ascii	"MVC VUI: bit_rate_scale\000" )
.LC315:
	ASCII(.ascii	"MVC VUI: cpb_size_scale\000" )
.LC316:
	ASCII(.ascii	"MVC VUI: bit_rate_value_minus1\000" )
	.space	1
.LC317:
	ASCII(.ascii	"MVC VUI: cpb_size_value_minus1\000" )
	.space	1
.LC318:
	ASCII(.ascii	"MVC VUI: cbr_flag\000" )
	.space	2
.LC319:
	ASCII(.ascii	"MVC VUI: initial_cpb_removal_delay_length_minus1\000" )
	.space	3
.LC320:
	ASCII(.ascii	"MVC VUI: cpb_removal_delay_length_minus1\000" )
	.space	3
.LC321:
	ASCII(.ascii	"MVC VUI: dpb_output_delay_length_minus1\000" )
.LC322:
	ASCII(.ascii	"MVC VUI: time_offset_length\000" )
.LC323:
	ASCII(.ascii	"MVC VUI: vui_mvc_vcl_hrd_parameters_present_flag[]\000" )
	.space	1
.LC324:
	ASCII(.ascii	"MVC VUI: vui_mvc_low_delay_hrd_flag[]\000" )
	.space	2
.LC325:
	ASCII(.ascii	"MVC VUI: vui_mvc_pic_struct_present_flag[]\000" )
	.space	1
.LC326:
	ASCII(.ascii	"SUBSPS: profile_idc\000" )
.LC327:
	ASCII(.ascii	"SUBSPS: constrained_set0_flag\000" )
	.space	2
.LC328:
	ASCII(.ascii	"SUBSPS: constrained_set1_flag\000" )
	.space	2
.LC329:
	ASCII(.ascii	"SUBSPS: constrained_set2_flag\000" )
	.space	2
.LC330:
	ASCII(.ascii	"SUBSPS: constrained_set3_flag\000" )
	.space	2
.LC331:
	ASCII(.ascii	"SUBSPS: constrained_set4_flag\000" )
	.space	2
.LC332:
	ASCII(.ascii	"SUBSPS: constrained_set5_flag\000" )
	.space	2
.LC333:
	ASCII(.ascii	"SUBSPS: reserved_zero_2bits\000" )
.LC334:
	ASCII(.ascii	"SUBSPS: level_idc\000" )
	.space	2
.LC335:
	ASCII(.ascii	"SUBSPS: seq_parameter_set_id\000" )
	.space	3
.LC336:
	ASCII(.ascii	"profile_idc = %5d error\012\000" )
	.space	3
.LC337:
	ASCII(.ascii	"level_idc = %5d error, try to decode as level_idc 4" )
	ASCII(.ascii	"1.\012\000" )
	.space	1
.LC338:
	ASCII(.ascii	"SUBSPS decode error.\012\000" )
	.space	2
.LC339:
	ASCII(.ascii	"SUBSPS: bit_equal_to_one\000" )
	.space	3
.LC340:
	ASCII(.ascii	"SUBSPS Mvc Ext decode error.\012\000" )
	.space	2
.LC341:
	ASCII(.ascii	"SUBSPS: mvc_vui_parameters_present_flag\000" )
.LC342:
	ASCII(.ascii	"SUBSPS Mvc Vui Ext decode error.\012\000" )
	.space	2
.LC343:
	ASCII(.ascii	"SEI: frame_packing_arrangement_id\000" )
	.space	2
.LC344:
	ASCII(.ascii	"SEI: frame_packing_arrangement_cancel_flag\000" )
	.space	1
.LC345:
	ASCII(.ascii	"SEI: frame_packing_arrangement_type\000" )
.LC346:
	ASCII(.ascii	"SEI: quincunx_sampling_flag\000" )
.LC347:
	ASCII(.ascii	"SEI: content_interpretation_type\000" )
	.space	3
.LC348:
	ASCII(.ascii	"SEI: spatial_flipping_flag\000" )
	.space	1
.LC349:
	ASCII(.ascii	"SEI: frame0_flipped_flag\000" )
	.space	3
.LC350:
	ASCII(.ascii	"SEI: field_views_flag\000" )
	.space	2
.LC351:
	ASCII(.ascii	"SEI: current_frame_is_frame0_flag\000" )
	.space	2
.LC352:
	ASCII(.ascii	"SEI: frame0_self_contained_flag\000" )
.LC353:
	ASCII(.ascii	"SEI: frame1_self_contained_flag\000" )
.LC354:
	ASCII(.ascii	"SEI: frame0_grid_position_x\000" )
.LC355:
	ASCII(.ascii	"SEI: frame0_grid_position_y\000" )
.LC356:
	ASCII(.ascii	"SEI: frame1_grid_position_x\000" )
.LC357:
	ASCII(.ascii	"SEI: frame1_grid_position_y\000" )
.LC358:
	ASCII(.ascii	"SEI: frame_packing_arrangement_reserved_byte\000" )
	.space	3
.LC359:
	ASCII(.ascii	"SEI: frame_packing_arrangement_repetition_period\000" )
	.space	3
.LC360:
	ASCII(.ascii	"SEI: frame_packing_arrangement_extension_flag\000" )
	.space	2
.LC361:
	ASCII(.ascii	"DecPicTimingSEI but SPS is invalid.\012\000" )
	.space	3
.LC362:
	ASCII(.ascii	"SEI: cpb_removal_delay\000" )
	.space	1
.LC363:
	ASCII(.ascii	"SEI: dpb_output_delay\000" )
	.space	2
.LC364:
	ASCII(.ascii	"pic_struct\000" )
	.space	1
.LC365:
	ASCII(.ascii	"SEI nal dec payload type err\012\000" )
	.space	2
.LC366:
	ASCII(.ascii	"SEI nal dec payloadSize err\012\000" )
	.space	3
.LC367:
	ASCII(.ascii	"MVC_SEI_BUFFERING_PERIOD,offset = %d,payload_size =" )
	ASCII(.ascii	" %d \012\000" )
	.space	3
.LC368:
	ASCII(.ascii	"MVC_PassBytes err [%s][%d]\012\000" )
.LC369:
	ASCII(.ascii	"MVC_SEI_PIC_TIMING,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC370:
	ASCII(.ascii	"MVC_SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d" )
	ASCII(.ascii	" \012\000" )
	.space	2
.LC371:
	ASCII(.ascii	"MVC_SEI_FILLER_PAYLOAD,offset = %d,payload_size = %" )
	ASCII(.ascii	"d \012\000" )
	.space	1
.LC372:
	ASCII(.ascii	"MVC_SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d" )
	ASCII(.ascii	", payload_size = %d \012\000" )
	.space	3
.LC373:
	ASCII(.ascii	"MVC_SEI_USER_DATA_UNREGISTERED, offset = %d, payloa" )
	ASCII(.ascii	"d_size = %d \012\000" )
	.space	3
.LC374:
	ASCII(.ascii	"SEI: itu_t_t35_country_code\000" )
.LC375:
	ASCII(.ascii	"SEI: itu_t_t35_country_code_extension_byte\000" )
	.space	1
.LC376:
	ASCII(.ascii	"SEI: itu_t_t35_provider_code\000" )
	.space	3
.LC377:
	ASCII(.ascii	"cann't dec usrdata\012\000" )
.LC378:
	ASCII(.ascii	"MVC_SEI_RECOVERY_POINT,offset = %d,payload_size = %" )
	ASCII(.ascii	"d \012\000" )
	.space	1
.LC379:
	ASCII(.ascii	"MVC_SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d," )
	ASCII(.ascii	"payload_size = %d \012\000" )
	.space	1
.LC380:
	ASCII(.ascii	"MVC_SEI_SPARE_PIC,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC381:
	ASCII(.ascii	"MVC_SEI_SCENE_INFO,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC382:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC383:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,p" )
	ASCII(.ascii	"ayload_size = %d \012\000" )
	.space	2
.LC384:
	ASCII(.ascii	"MVC_SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload" )
	ASCII(.ascii	"_size = %d \012\000" )
.LC385:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_FREEZE,offset = %d,payload_size " )
	ASCII(.ascii	"= %d \012\000" )
	.space	2
.LC386:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,paylo" )
	ASCII(.ascii	"ad_size = %d \012\000" )
	.space	2
.LC387:
	ASCII(.ascii	"MVC_SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_siz" )
	ASCII(.ascii	"e = %d \012\000" )
.LC388:
	ASCII(.ascii	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset" )
	ASCII(.ascii	" = %d,payload_size = %d \012\000" )
	.space	3
.LC389:
	ASCII(.ascii	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset =" )
	ASCII(.ascii	" %d,payload_size = %d \012\000" )
	.space	1
.LC390:
	ASCII(.ascii	"MVC_SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset =" )
	ASCII(.ascii	" %d,payload_size = %d \012\000" )
	.space	1
.LC391:
	ASCII(.ascii	"MVC_SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payl" )
	ASCII(.ascii	"oad_size = %d \012\000" )
	.space	1
.LC392:
	ASCII(.ascii	"MVC_SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset" )
	ASCII(.ascii	" = %d,payload_size = %d \012\000" )
	.space	3
.LC393:
	ASCII(.ascii	"MVC_SEI_STEREO_VIDEO_INFO,offset = %d,payload_size " )
	ASCII(.ascii	"= %d \012\000" )
	.space	2
.LC394:
	ASCII(.ascii	"too much usrdat, cann't dec SEI\012\000" )
	.space	3
.LC395:
	ASCII(.ascii	"pNewPicDetector = NULL\000" )
	.space	1
.LC396:
	ASCII(.ascii	"pu8 = NULL\000" )
	.space	1
.LC397:
	ASCII(.ascii	"\012 mvc the stream is error,len:%d\012\000" )
	.space	2
.LC398:
	ASCII(.ascii	"\012Slice nal or IDR nal = %d\012\000" )
.LC399:
	ASCII(.ascii	"sliceheader dec err\012\000" )
	.space	3
.LC400:
	ASCII(.ascii	"MVC_InquireSliceProperty mvc flag %d is wrong\012\000" )
	.space	1
.LC401:
	ASCII(.ascii	"mvc.c,L%d: pMvcCtx is NULL\012\000" )
.LC402:
	ASCII(.ascii	"MvcDec destroy\012\000" )
.LC403:
	ASCII(.ascii	"PicID is out of range\000" )
	.space	2
.LC404:
	ASCII(.ascii	"MVC recycle image\012\000" )
	.space	1
.LC405:
	ASCII(.ascii	"pH264Ctx is %#x, pFrameStore is %#x\012\000" )
	.space	3
.LC406:
	ASCII(.ascii	"line: %d, pstLogicFsImage is NULL\012\000" )
	.space	1
.LC407:
	ASCII(.ascii	"InsertVO err:%d, MVC_ClearAll\012\000" )
	.space	1
.LC408:
	ASCII(.ascii	"mvc.c line %d: MVC_FRAME para err(ret=%d), recycle " )
	ASCII(.ascii	"image self\012\000" )
	.space	1
.LC409:
	ASCII(.ascii	"[%s][%d] MVC_OutputFrmToVO return %d !\012\000" )
.LC410:
	ASCII(.ascii	"[%s][%d] MVC_OutputFrmToVO return %d\012\000" )
	.space	2
.LC411:
	ASCII(.ascii	"%s %d MVC_OK != MVC_FlushDPB!!\012\000" )
.LC412:
	ASCII(.ascii	"%s %d MVC_OK != MVC_InitDPB!!\012\000" )
	.space	1
.LC413:
	ASCII(.ascii	"----------------- MVC_IMODE -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC414:
	ASCII(.ascii	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\012\000" )
.LC415:
	ASCII(.ascii	"***** VDM start, TotalPicNum=%d, pMvcCtx->CurrPic.s" )
	ASCII(.ascii	"tructure=%d.\012\000" )
	.space	3
.LC416:
	ASCII(.ascii	"MVC_DecVDM fail [%s][%d]\012\000" )
	.space	2
.LC417:
	ASCII(.ascii	"\012 receive streambuff=%p; phy_addr=0x%x; bitstrea" )
	ASCII(.ascii	"m_length=%d\012\000" )
	.space	3
.LC418:
	ASCII(.ascii	"nal_releaMVC_SE_ERR\012\000" )
	.space	3
.LC419:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC420:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC421:
	ASCII(.ascii	"clear all dec para\012\000" )
.LC422:
	ASCII(.ascii	"line %d, get APC error, ret %d\012\000" )
.LC423:
	ASCII(.ascii	"InserFrmInDPB: cur pic struct = %d!\012\000" )
	.space	3
.LC424:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC425:
	ASCII(.ascii	"FS_ALLOC_ERR, MVC_ClearAll\012\000" )
.LC426:
	ASCII(.ascii	"Can not new logic fs! MVC_ClearAll\012\000" )
.LC427:
	ASCII(.ascii	"mvc.c,L%d: pMvcCtx or pstExtraData is NULL\012\000" )
.LC428:
	ASCII(.ascii	"%s %d NULL== pMvcCtx->SPS || NULL == pMvcCtx->PPS |" )
	ASCII(.ascii	"| NULL == pMvcCtx->DecSlicePara!!\012\000" )
	.space	2
.LC429:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC430:
	ASCII(.ascii	"CurrPic.state is 'MVC_EMPTY'\012\000" )
	.space	2
.LC431:
	ASCII(.ascii	"MVC_StorePicInDpb return(%d) from L%d\012\000" )
	.space	1
.LC432:
	ASCII(.ascii	"Is IDR, but init DPB failed!\012\000" )
	.space	2
.LC433:
	ASCII(.ascii	"Is IDR, but FlushDPB failed!\012\000" )
	.space	2
.LC434:
	ASCII(.ascii	"MVC_DirectOutput mode\012\000" )
	.space	1
.LC435:
	ASCII(.ascii	"line %d, REPORT_IFRAME_ERR\012\000" )
.LC436:
	ASCII(.ascii	"line %d, return %d\012\000" )
.LC437:
	ASCII(.ascii	"err(%d) > ref_thr(%d)\012\000" )
	.space	1
.LC438:
	ASCII(.ascii	"MVC_Marking return %d\012\000" )
	.space	1
.LC439:
	ASCII(.ascii	"line %d: pMvcCtx->DPB.size = %d, ref %d, ltref %d\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC440:
	ASCII(.ascii	"line %d, MVC_GetMinPOC failed\012\000" )
	.space	1
.LC441:
	ASCII(.ascii	"%s: pos(%d) = pre_pos, force return.\012\000" )
	.space	2
.LC442:
	ASCII(.ascii	"GAP found while DPB is MVC_EMPTY!\012\000" )
	.space	1
.LC443:
	ASCII(.ascii	"MVC_FRAME num gap try to fill it \012\000" )
	.space	1
.LC444:
	ASCII(.ascii	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC445:
	ASCII(.ascii	"cann't allocate MVC_FRAME store when gap find\012\000" )
	.space	1
.LC446:
	ASCII(.ascii	"allocate MVC_FRAME store when gap find\012\000" )
.LC447:
	ASCII(.ascii	"line %d: store gap pic err, ret=%d\012\000" )
.LC448:
	ASCII(.ascii	"line %d: flush dpb return %d\012\000" )
	.space	2
.LC449:
	ASCII(.ascii	"line %d: init dpb return %d\012\000" )
	.space	3
.LC450:
	ASCII(.ascii	"resolution error, the CAP_LEVEL_USER_DEFINE_WITH_OP" )
	ASCII(.ascii	"TION channel with s32ReRangeEn == 0 can't support s" )
	ASCII(.ascii	"uch bitstream.\012\000" )
	.space	2
.LC451:
	ASCII(.ascii	"s32MaxRefFrameNum < pMvcCtx->DPB.size, the CAP_LEVE" )
	ASCII(.ascii	"L_USER_DEFINE_WITH_OPTION channel can't support suc" )
	ASCII(.ascii	"h bitstream.\012\000" )
.LC452:
	ASCII(.ascii	"mem arrange err, MVC_ClearAll\012\000" )
	.space	1
.LC453:
	ASCII(.ascii	"line %d: MVC_FRAME gap(=%d) > dpb size(=%d)\012\000" )
	.space	3
.LC454:
	ASCII(.ascii	"MVC_FRAME num gap don't allowed but gap find\012\000" )
	.space	2
.LC455:
	ASCII(.ascii	"line %d: frame num(%d/%d) find gap in NON-I slice b" )
	ASCII(.ascii	"ut here gap is not allowed\012\000" )
	.space	1
.LC456:
	ASCII(.ascii	"line %d: dec gap failed\012\000" )
	.space	3
.LC457:
	ASCII(.ascii	"line %d: alloc framestore failed\012\000" )
	.space	2
.LC458:
	ASCII(.ascii	"dec_pts: %lld\012\000" )
	.space	1
.LC459:
	ASCII(.ascii	"dec_usertag: %lld\012\000" )
	.space	1
.LC460:
	ASCII(.ascii	"line %d: CurrPic.frame_store is NULL\012\000" )
	.space	2
.LC461:
	ASCII(.ascii	"get back frm\012\000" )
	.space	2
.LC462:
	ASCII(.ascii	"Start Reason: SliceParaNum, MaxBytesReceived = %d, " )
	ASCII(.ascii	"%d(thr=%d)\012\000" )
	.space	1
.LC463:
	ASCII(.ascii	"Too many slice or bitstream, err!\012\000" )
	.space	1
.LC464:
	ASCII(.ascii	"Start Reason: new_pic_flag\012\000" )
.LC465:
	ASCII(.ascii	"init pic err, find next recover point or next valid" )
	ASCII(.ascii	" sps, pps, or exit\012\000" )
	.space	1
.LC466:
	ASCII(.ascii	"MVC_DecList error, ret=%d\012\000" )
	.space	1
.LC467:
	ASCII(.ascii	"dec list err.\012\000" )
	.space	1
.LC468:
	ASCII(.ascii	"pMvcCtx->TotalNal = %d, type:%d\012\000" )
	.space	3
.LC469:
	ASCII(.ascii	"stop i want\012\000" )
	.space	3
.LC470:
	ASCII(.ascii	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC471:
	ASCII(.ascii	"*******TotalPicNum=%d********\012\000" )
	.space	1
.LC472:
	ASCII(.ascii	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\012\000" )
	.space	1
.LC473:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC474:
	ASCII(.ascii	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\012\000" )
	.space	1
.LC475:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC476:
	ASCII(.ascii	"***** NAL: SEI, nal_unit_type=%d\012\000" )
	.space	2
.LC477:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC478:
	ASCII(.ascii	"***** NAL: AUD, nal_unit_type=%d\012\000" )
	.space	2
.LC479:
	ASCII(.ascii	"***** NAL: EOSEQ, nal_unit_type=%d\012\000" )
.LC480:
	ASCII(.ascii	"***** NAL: FILL, nal_unit_type=%d\012\000" )
	.space	1
.LC481:
	ASCII(.ascii	"***** NAL: EOSTREAM, nal_unit_type=%d\012\000" )
	.space	1
.LC482:
	ASCII(.ascii	"***** NAL: SPSEXT, nal_unit_type=%d\012\000" )
	.space	3
.LC483:
	ASCII(.ascii	"***** NAL: PREFIX, nal_unit_type=%d\012\000" )
	.space	3
.LC484:
	ASCII(.ascii	"***** NAL: SUBSPS, nal_unit_type=%d\012\000" )
	.space	3
.LC485:
	ASCII(.ascii	"***** NAL: AUX, nal_unit_type=%d\012\000" )
	.space	2
.LC486:
	ASCII(.ascii	"***** NAL: EOPIC, nal_unit_type=%d\012\000" )
.LC487:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC488:
	ASCII(.ascii	"nal_header != 0x00000100 not support.\012\000" )
	.space	1
.LC489:
	ASCII(.ascii	"pPacket= NULL\000" )
	.space	2
.LC490:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC491:
	ASCII(.ascii	"MVC_FindTrailZeros ERR\012\000" )
.LC492:
	ASCII(.ascii	"store pic err, ret = %d\012\000" )
	.space	3
.LC493:
	ASCII(.ascii	"MVC_IMODE nal store pic err, ret = %d\012\000" )
	.space	1
.LC494:
	ASCII(.ascii	"MVC_IMODE nal flush dpb err, ret = %d\012\000" )
	.space	1
.LC495:
	ASCII(.ascii	"cann't find FrameStore\012\000" )
.LC496:
	ASCII(.ascii	"========== MVC FrameStore state(is_used, is_in_dpb," )
	ASCII(.ascii	" MVC_IsOutDPB) ========\012\000" )
.LC497:
	ASCII(.ascii	"ReadImgNum = %d, NewImgNum = %d\012\000" )
	.space	3
.LC498:
	ASCII(.ascii	"%02d: %d %d %d\012\000" )
.LC499:
	ASCII(.ascii	"FrameStore leak, MVC_ClearAll\012\000" )
	.bss
	.align	2
.LANCHOR2 = . + 0
.LANCHOR3 = . + 8184
	.type	pps_tmp.14962, %object
	.size	pps_tmp.14962, 2240
pps_tmp.14962:
	.space	2240
	.type	sps_tmp.15098, %object
	.size	sps_tmp.15098, 3992
sps_tmp.15098:
	.space	3992
	.type	MvcTmpBuf, %object
	.size	MvcTmpBuf, 68
MvcTmpBuf:
	.space	68
	.type	cnt.13918, %object
	.size	cnt.13918, 4
cnt.13918:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
