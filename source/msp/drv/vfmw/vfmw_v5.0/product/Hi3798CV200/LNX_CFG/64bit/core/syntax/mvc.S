#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"mvc.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	MVC_IsSTRefFlg
	.type	MVC_IsSTRefFlg, %function
MVC_IsSTRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 65536
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_IsSTRefFlg, .-MVC_IsSTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsLTRefFlg
	.type	MVC_IsLTRefFlg, %function
MVC_IsLTRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 256
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_IsLTRefFlg, .-MVC_IsLTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_pic_by_pic_num_desc
	.type	MVC_compare_pic_by_pic_num_desc, %function
MVC_compare_pic_by_pic_num_desc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, 1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 20]
	ldr	w2, [x2, 20]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_pic_by_pic_num_desc, .-MVC_compare_pic_by_pic_num_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_pic_by_lt_pic_num_asc
	.type	MVC_compare_pic_by_lt_pic_num_asc, %function
MVC_compare_pic_by_lt_pic_num_asc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, -1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 16]
	ldr	w2, [x2, 16]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_pic_by_lt_pic_num_asc, .-MVC_compare_pic_by_lt_pic_num_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_fs_by_frame_num_desc
	.type	MVC_compare_fs_by_frame_num_desc, %function
MVC_compare_fs_by_frame_num_desc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, 1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 24]
	ldr	w2, [x2, 24]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_fs_by_frame_num_desc, .-MVC_compare_fs_by_frame_num_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_fs_by_lt_pic_idx_asc
	.type	MVC_compare_fs_by_lt_pic_idx_asc, %function
MVC_compare_fs_by_lt_pic_idx_asc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, -1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 28]
	ldr	w2, [x2, 28]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, hi
	csel	w0, w0, w3, cs
	ret
	.size	MVC_compare_fs_by_lt_pic_idx_asc, .-MVC_compare_fs_by_lt_pic_idx_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_pic_by_poc_asc
	.type	MVC_compare_pic_by_poc_asc, %function
MVC_compare_pic_by_poc_asc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, -1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 24]
	ldr	w2, [x2, 24]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_pic_by_poc_asc, .-MVC_compare_pic_by_poc_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_pic_by_poc_desc
	.type	MVC_compare_pic_by_poc_desc, %function
MVC_compare_pic_by_poc_desc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, 1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 24]
	ldr	w2, [x2, 24]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_pic_by_poc_desc, .-MVC_compare_pic_by_poc_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_fs_by_poc_asc
	.type	MVC_compare_fs_by_poc_asc, %function
MVC_compare_fs_by_poc_asc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, -1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 32]
	ldr	w2, [x2, 32]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_fs_by_poc_asc, .-MVC_compare_fs_by_poc_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_compare_fs_by_poc_desc
	.type	MVC_compare_fs_by_poc_desc, %function
MVC_compare_fs_by_poc_desc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19]
	mov	w3, 1
	ldr	x2, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 32]
	ldr	w2, [x2, 32]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	MVC_compare_fs_by_poc_desc, .-MVC_compare_fs_by_poc_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	MVC_SetFrmRepeatCount.part.2, %function
MVC_SetFrmRepeatCount.part.2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x3, x19, 11124736
	ldp	w0, w2, [x19, 132]
	ldr	w3, [x3, 824]
	lsr	w0, w0, 1
	add	w2, w3, w2, lsr 1
	add	w3, w2, 1
	cmp	w0, w3
	bcc	.L28
	sub	w0, w0, #1
	sub	w0, w0, w2
	cmp	w0, 1
	bls	.L29
	mov	w0, 2
	str	w0, [x20, 16]
	ldr	w0, [x19, 136]
	add	w0, w0, 4
	str	w0, [x19, 136]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L28:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L29:
	mov	w0, 1
	str	w0, [x20, 16]
	ldr	w0, [x19, 136]
	add	w0, w0, 2
	str	w0, [x19, 136]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_SetFrmRepeatCount.part.2, .-MVC_SetFrmRepeatCount.part.2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	MVC_CombinePacket.part.14, %function
MVC_CombinePacket.part.14:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC1
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x2, [x19, 240]
	mov	w0, 7
	ldr	x1, .LC3
	ldp	w5, w3, [x2, 48]
	ldr	w4, [x2, 16]
	ldr	w2, [x2, 20]
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	ldr	x3, .LC4
	ldr	w2, [x1, 16]
	ldr	x0, [x1, 40]
	ldr	x3, [x3, 104]
	ldr	x1, [x1, 8]
	sub	x0, x0, x2
	blr	x3
	ldr	x2, [x19, 240]
	mov	w4, 1
	ldr	x1, .LC6
	mov	w0, 7
	ldr	w3, [x2, 68]
	ldr	w20, [x2, 36]
	str	w3, [x2, 36]
	ldr	x2, [x19, 240]
	str	wzr, [x2, 28]
	ldr	x2, [x19, 240]
	ldr	w5, [x2, 16]
	ldr	x3, [x2, 40]
	sub	x3, x3, x5
	str	x3, [x2, 8]
	ldr	x2, [x19, 240]
	ldr	w5, [x2, 16]
	ldr	w3, [x2, 52]
	sub	w3, w3, w5
	str	w3, [x2, 20]
	ldr	x2, [x19, 240]
	ldr	w5, [x2, 16]
	ldr	w3, [x2, 48]
	add	w3, w5, w3
	str	w3, [x2, 16]
	ldr	x2, [x19, 240]
	str	w4, [x2, 76]
	ldr	x2, [x19, 240]
	ldp	w3, w2, [x2, 16]
	bl	dprint_vfmw
	ldr	w0, [x19, 120]
	mov	w1, w20
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 240]
	str	xzr, [x0, 40]
	ldr	x0, [x19, 240]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 240]
	str	wzr, [x0, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_CombinePacket.part.14, .-MVC_CombinePacket.part.14
	.align	3
.LC1:
	.xword	.LC0
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC6:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_ue_v
	.type	mvc_ue_v, %function
mvc_ue_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	add	x23, x21, 872
	bl	_mcount
	mov	w1, 32
	mov	x0, x23
	bl	BsShow
	mov	w20, w0
	bl	ZerosMS_32
	cmp	w0, 15
	mov	w19, w0
	bls	.L37
	cmp	w0, 31
	bls	.L38
	mov	w0, 1
	mov	w20, -1
	strb	w0, [x21, 10]
	mov	w19, 32
.L35:
	ldr	x4, [x21, 240]
	mov	w3, w20
	ldr	x1, .LC8
	mov	x2, x22
	mov	w0, 21
	ldr	w5, [x4, 72]
	add	w19, w5, w19
	str	w19, [x4, 72]
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L37:
	lsl	w19, w0, 1
	mov	w2, 32
	add	w19, w19, 1
	mov	x0, x23
	sub	w2, w2, w19
	mov	w1, w19
	lsr	w20, w20, w2
	sub	w20, w20, #1
	bl	BsSkip
	b	.L35
	.p2align 3
.L38:
	mov	w1, w0
	mov	x0, x23
	add	w24, w19, 1
	lsl	w19, w19, 1
	bl	BsSkip
	add	w19, w19, 1
	mov	w1, w24
	mov	x0, x23
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w24
	mov	x0, x23
	bl	BsSkip
	b	.L35
	.size	mvc_ue_v, .-mvc_ue_v
	.align	3
.LC8:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_se_v
	.type	mvc_se_v, %function
mvc_se_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	add	x23, x21, 872
	bl	_mcount
	mov	w1, 32
	mov	x0, x23
	bl	BsShow
	mov	w20, w0
	bl	ZerosMS_32
	cmp	w0, 15
	mov	w19, w0
	bhi	.L40
	lsl	w19, w0, 1
	mov	w2, 32
	add	w19, w19, 1
	mov	x0, x23
	sub	w2, w2, w19
	mov	w1, w19
	lsr	w20, w20, w2
	and	w2, w20, 1
	lsr	w20, w20, 1
	cmp	w2, wzr
	csneg	w20, w20, w20, eq
	bl	BsSkip
.L42:
	ldr	x4, [x21, 240]
	mov	w3, w20
	ldr	x1, .LC9
	mov	x2, x22
	mov	w0, 21
	ldr	w5, [x4, 72]
	add	w19, w5, w19
	str	w19, [x4, 72]
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L40:
	cmp	w0, 31
	bls	.L49
	mov	w0, 1
	mov	w20, 2147483647
	strb	w0, [x21, 10]
	mov	w19, 32
	b	.L42
	.p2align 3
.L49:
	mov	w1, w0
	mov	x0, x23
	bl	BsSkip
	mov	w1, w19
	mov	x0, x23
	lsl	w19, w19, 1
	bl	BsGet
	mov	w20, w0
	mov	w1, 1
	mov	x0, x23
	add	w19, w19, 1
	bl	BsGet
	and	w0, w0, 1
	cmp	w0, wzr
	csneg	w20, w20, w20, eq
	b	.L42
	.size	mvc_se_v, .-mvc_se_v
	.align	3
.LC9:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_u_v
	.type	mvc_u_v, %function
mvc_u_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x2
	mov	w19, w1
	bl	_mcount
	mov	w1, w19
	add	x0, x21, 872
	bl	BsGet
	mov	w20, w0
	ldr	x4, [x21, 240]
	mov	w3, w0
	ldr	x1, .LC10
	mov	x2, x22
	mov	w0, 21
	ldr	w5, [x4, 72]
	add	w19, w5, w19
	str	w19, [x4, 72]
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	mvc_u_v, .-mvc_u_v
	.align	3
.LC10:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_u_1
	.type	mvc_u_1, %function
mvc_u_1:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	mov	w1, 1
	add	x0, x20, 872
	bl	BsGet
	mov	w19, w0
	ldr	x5, [x20, 240]
	mov	w3, w0
	ldr	x1, .LC11
	mov	x2, x21
	mov	w0, 21
	ldr	w4, [x5, 72]
	add	w4, w4, 1
	str	w4, [x5, 72]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	mvc_u_1, .-mvc_u_1
	.align	3
.LC11:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetMinPOC
	.type	MVC_GetMinPOC, %function
MVC_GetMinPOC:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x24, x3
	mov	x21, x0
	mov	x0, x30
	mov	x23, x2
	mov	w22, w1
	add	x26, x21, 11124736
	bl	_mcount
	mov	w0, -1
	str	w0, [x24]
	mov	w0, 2147483647
	str	w0, [x23]
	ldr	w0, [x26, 824]
	ldr	w1, [x26, 828]
	cmp	w1, w0
	bls	.L53
	str	w0, [x26, 828]
.L53:
	mov	w25, -1
	mov	w20, 0
	cbnz	w0, .L68
	b	.L59
	.p2align 3
.L56:
	ldr	w2, [x1, 32]
	ldr	w3, [x23]
	cmp	w3, w2
	ble	.L55
	ldrb	w3, [x1, 5]
	cbz	w3, .L55
	ldrb	w0, [x0, 1]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L75
	.p2align 2
.L55:
	ldr	w0, [x26, 824]
	add	w20, w20, 1
	cmp	w0, w20
	bls	.L59
.L68:
	add	x19, x21, x20, uxtw 3
	add	x19, x19, 11124736
	ldr	x0, [x19, 440]
	cbz	x0, .L55
	ldrsb	w1, [x0, 6]
	ldr	w0, [x21, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L55
	cmn	w22, #1
	ldr	x1, [x19, 440]
	bne	.L56
	ldrb	w2, [x1, 5]
	cbz	w2, .L55
	ldrb	w0, [x0, 1]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 1
	bhi	.L55
	ldr	w0, [x1, 32]
	ldr	w2, [x23]
	cmp	w2, w0
	ble	.L57
	str	w0, [x23]
	str	w20, [x24]
	add	w20, w20, 1
	ldr	x0, [x19, 440]
	ldr	w25, [x0, 56]
	ldr	w0, [x26, 824]
	cmp	w0, w20
	bhi	.L68
.L59:
	ldr	w0, [x24]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x25, x26, [sp, 64]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L75:
	ldr	w0, [x1, 56]
	cmp	w22, w0
	bne	.L55
	str	w2, [x23]
	str	w20, [x24]
	b	.L55
	.p2align 3
.L57:
	bne	.L55
	ldr	w0, [x1, 56]
	cmp	w0, w25
	bge	.L55
	str	w20, [x24]
	ldr	x0, [x19, 440]
	ldr	w25, [x0, 56]
	b	.L55
	.size	MVC_GetMinPOC, .-MVC_GetMinPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FrameStoreRefFlg
	.type	MVC_FrameStoreRefFlg, %function
MVC_FrameStoreRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 3]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_FrameStoreRefFlg, .-MVC_FrameStoreRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_NonLongTermRefFlg
	.type	MVC_NonLongTermRefFlg, %function
MVC_NonLongTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 3]
	cmp	w1, 3
	beq	.L96
	tbnz	x1, 0, .L97
	mov	w0, 0
	tbnz	x1, 1, .L82
.L89:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L97:
	ldrb	w2, [x19, 761]
	mov	w0, 1
	cbz	w2, .L89
	mov	w0, 0
	tbz	x1, 1, .L89
	b	.L82
	.p2align 3
.L96:
	ldrb	w1, [x19, 713]
	mov	w0, 1
	cbz	w1, .L89
	ldrb	w1, [x19, 761]
	cbz	w1, .L89
.L82:
	ldrb	w0, [x19, 809]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_NonLongTermRefFlg, .-MVC_NonLongTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ShortTermRefFlg
	.type	MVC_ShortTermRefFlg, %function
MVC_ShortTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 3]
	cmp	w1, 3
	beq	.L114
	tbnz	x1, 0, .L115
.L102:
	mov	w0, 0
	tbnz	x1, 1, .L103
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L115:
	ldr	w0, [x19, 760]
	and	w0, w0, 16776960
	cmp	w0, 65536
	bne	.L102
.L107:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L114:
	ldr	w0, [x19, 712]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L107
	ldr	w0, [x19, 760]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L107
.L103:
	ldr	w0, [x19, 808]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 65536
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ShortTermRefFlg, .-MVC_ShortTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_LongTermRefFlg
	.type	MVC_LongTermRefFlg, %function
MVC_LongTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 3]
	cmp	w1, 3
	beq	.L132
	tbnz	x1, 0, .L133
.L120:
	mov	w0, 0
	tbnz	x1, 1, .L121
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L133:
	ldr	w0, [x19, 760]
	and	w0, w0, 16776960
	cmp	w0, 256
	bne	.L120
.L125:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L132:
	ldr	w0, [x19, 712]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L125
	ldr	w0, [x19, 760]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L125
.L121:
	ldr	w0, [x19, 808]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 256
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_LongTermRefFlg, .-MVC_LongTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdateLTReflist
	.type	MVC_UpdateLTReflist, %function
MVC_UpdateLTReflist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	add	x26, x23, 11124736
	bl	_mcount
	ldr	w24, [x26, 824]
	cbz	w24, .L135
	sub	w22, w24, #1
	add	x20, x26, 440
	add	x22, x22, 1388544
	mov	w19, 0
	add	x22, x22, 2104
	add	x25, x23, 11157504
	add	x22, x23, x22, lsl 3
	b	.L137
	.p2align 3
.L136:
	cmp	x22, x20
	beq	.L151
.L137:
	ldr	x21, [x20]
	add	x20, x20, 8
	mov	x0, x21
	cbz	x21, .L136
	bl	MVC_LongTermRefFlg
	cbz	w0, .L136
	ldr	w1, [x21, 56]
	ldr	w0, [x25, 3408]
	cmp	w1, w0
	bne	.L136
	uxtw	x0, w19
	cmp	x22, x20
	add	x0, x0, 1388544
	add	w19, w19, 1
	add	x0, x23, x0, lsl 3
	str	x21, [x0, 17080]
	bne	.L137
	.p2align 2
.L151:
	cmp	w19, w24
	str	w19, [x26, 836]
	bcs	.L134
	.p2align 2
.L146:
	uxtw	x0, w19
	add	w19, w19, 1
	add	x0, x0, 1388544
	cmp	w19, w24
	add	x0, x23, x0, lsl 3
	str	xzr, [x0, 17080]
	bne	.L146
.L134:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L135:
	str	wzr, [x26, 836]
	b	.L134
	.size	MVC_UpdateLTReflist, .-MVC_UpdateLTReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdateReflist
	.type	MVC_UpdateReflist, %function
MVC_UpdateReflist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	add	x26, x23, 11124736
	bl	_mcount
	ldr	w24, [x26, 824]
	cbz	w24, .L153
	sub	w22, w24, #1
	add	x20, x26, 440
	add	x22, x22, 1388544
	mov	w19, 0
	add	x22, x22, 2104
	add	x25, x23, 11157504
	add	x22, x23, x22, lsl 3
	b	.L155
	.p2align 3
.L154:
	cmp	x22, x20
	beq	.L169
.L155:
	ldr	x21, [x20]
	add	x20, x20, 8
	mov	x0, x21
	cbz	x21, .L154
	bl	MVC_ShortTermRefFlg
	cbz	w0, .L154
	ldr	w1, [x21, 56]
	ldr	w0, [x25, 3408]
	cmp	w1, w0
	bne	.L154
	uxtw	x0, w19
	cmp	x22, x20
	add	x0, x0, 1388544
	add	w19, w19, 1
	add	x0, x23, x0, lsl 3
	str	x21, [x0, 16952]
	bne	.L155
	.p2align 2
.L169:
	cmp	w19, w24
	str	w19, [x26, 832]
	bcs	.L152
	.p2align 2
.L164:
	uxtw	x0, w19
	add	w19, w19, 1
	add	x0, x0, 1388544
	cmp	w19, w24
	add	x0, x23, x0, lsl 3
	str	xzr, [x0, 16952]
	bne	.L164
.L152:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L153:
	str	wzr, [x26, 832]
	b	.L152
	.size	MVC_UpdateReflist, .-MVC_UpdateReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetPicNumX
	.type	MVC_GetPicNumX, %function
MVC_GetPicNumX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldrb	w0, [x20, 3]
	ldr	w2, [x20, 672]
	cbz	w0, .L172
	lsl	w2, w2, 1
	add	w2, w2, 1
.L172:
	mvn	w0, w19
	add	w0, w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_GetPicNumX, .-MVC_GetPicNumX
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkFrameStoreRef
	.type	MVC_UnMarkFrameStoreRef, %function
MVC_UnMarkFrameStoreRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 2]
	tbz	x0, 0, .L174
	ldrb	w1, [x19, 3]
	strb	wzr, [x19, 761]
	and	w1, w1, 2
	strb	wzr, [x19, 762]
	strb	w1, [x19, 3]
.L174:
	tbz	x0, 1, .L175
	ldrb	w1, [x19, 3]
	strb	wzr, [x19, 809]
	and	w1, w1, 1
	strb	wzr, [x19, 810]
	strb	w1, [x19, 3]
.L175:
	cmp	w0, 3
	bne	.L176
	strb	wzr, [x19, 714]
	strb	wzr, [x19, 713]
.L176:
	strb	wzr, [x19, 3]
	mov	w2, 0
	ldrsb	w1, [x19, 6]
	ldr	w0, [x20, 120]
	bl	FSP_SetRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_UnMarkFrameStoreRef, .-MVC_UnMarkFrameStoreRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	MVC_SlidingWinMark.part.3, %function
MVC_SlidingWinMark.part.3:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11124736
	ldr	w5, [x1, 824]
	cbz	w5, .L200
	add	x1, x1, 440
	mov	w7, 0
	mov	w6, 2147483647
	mov	w2, 0
	add	x8, x19, 11157504
	.p2align 2
.L190:
	ldr	x0, [x1]
	cbz	x0, .L185
	ldr	w3, [x0, 64]
	cmp	w3, w6
	bcs	.L185
	ldrb	w4, [x0, 3]
	cbz	w4, .L185
	cmp	w4, 3
	beq	.L256
	tbnz	x4, 0, .L257
.L189:
	tbnz	x4, 1, .L198
	.p2align 2
.L185:
	add	w2, w2, 1
	add	x1, x1, 8
	cmp	w2, w5
	bne	.L190
.L184:
	sxtw	x0, w7
	add	x0, x0, 1388544
	add	x0, x19, x0, lsl 3
	ldr	x1, [x0, 16824]
	cbz	x1, .L183
	ldrb	w0, [x1, 3]
	cbz	w0, .L183
	cmp	w0, 3
	beq	.L258
	tbnz	x0, 0, .L259
.L195:
	tbnz	x0, 1, .L199
.L183:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L257:
	ldrb	w9, [x0, 761]
	cbnz	w9, .L189
.L187:
	ldr	w4, [x0, 56]
	ldr	w0, [x8, 3408]
	cmp	w4, w0
	csel	w6, w6, w3, ne
	csel	w7, w7, w2, ne
	b	.L185
	.p2align 3
.L256:
	ldrb	w4, [x0, 713]
	cbz	w4, .L187
	ldrb	w4, [x0, 761]
	cbz	w4, .L187
.L198:
	ldrb	w4, [x0, 809]
	cbnz	w4, .L185
	ldr	w4, [x0, 56]
	ldr	w0, [x8, 3408]
	cmp	w4, w0
	csel	w6, w6, w3, ne
	csel	w7, w7, w2, ne
	b	.L185
	.p2align 3
.L259:
	ldrb	w2, [x1, 761]
	cbnz	w2, .L195
.L193:
	add	x0, x19, 11157504
	ldr	w2, [x1, 56]
	ldr	w0, [x0, 3408]
	cmp	w2, w0
	bne	.L183
	mov	x0, x19
	bl	MVC_UnMarkFrameStoreRef
	mov	x0, x19
	bl	MVC_UpdateReflist
	b	.L183
	.p2align 3
.L258:
	ldrb	w0, [x1, 713]
	cbz	w0, .L193
	ldrb	w0, [x1, 761]
	cbz	w0, .L193
.L199:
	ldrb	w0, [x1, 809]
	cbz	w0, .L193
	b	.L183
.L200:
	mov	w7, 0
	b	.L184
	.size	MVC_SlidingWinMark.part.3, .-MVC_SlidingWinMark.part.3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkLTFrmByFrmIdx
	.type	MVC_UnMarkLTFrmByFrmIdx, %function
MVC_UnMarkLTFrmByFrmIdx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 11124736
	ldr	w2, [x0, 836]
	cbz	w2, .L260
	sub	w4, w2, #1
	add	x0, x0, 696
	add	x4, x4, 1388544
	add	x5, x20, 11157504
	add	x4, x4, 2136
	add	x4, x20, x4, lsl 3
	b	.L263
	.p2align 3
.L262:
	cmp	x0, x4
	beq	.L260
.L263:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 28]
	cmp	w3, w19
	bne	.L262
	ldr	w3, [x1, 56]
	ldr	w2, [x5, 3408]
	cmp	w3, w2
	bne	.L262
	mov	x0, x20
	bl	MVC_UnMarkFrameStoreRef
.L260:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_UnMarkLTFrmByFrmIdx, .-MVC_UnMarkLTFrmByFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkLTFldByFrmIdx
	.type	MVC_UnMarkLTFldByFrmIdx, %function
MVC_UnMarkLTFldByFrmIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x1
	mov	w20, w2
	mov	w19, w3
	bl	_mcount
	add	x0, x21, 11124736
	ldr	w4, [x0, 836]
	cbz	w4, .L268
	sub	w6, w4, #1
	add	x0, x0, 696
	add	x6, x6, 1388544
	add	x7, x21, 11157504
	add	x6, x6, 2136
	add	x6, x21, x6, lsl 3
	b	.L272
	.p2align 3
.L270:
	cmp	x0, x6
	beq	.L268
.L272:
	ldr	x4, [x0]
	add	x0, x0, 8
	ldr	w5, [x4, 28]
	cmp	w5, w19
	bne	.L270
	ldr	w5, [x4, 56]
	ldr	w3, [x7, 3408]
	cmp	w5, w3
	bne	.L270
	cmp	w20, 1
	beq	.L284
	cmp	w20, 2
	bne	.L270
	ldrb	w1, [x4, 761]
	cmp	w1, wzr
	ccmp	x4, x22, 0, ne
	beq	.L270
.L283:
	mov	x1, x4
	mov	x0, x21
	bl	MVC_UnMarkFrameStoreRef
.L268:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L284:
	ldrb	w1, [x4, 809]
	cmp	w1, wzr
	ccmp	x4, x22, 0, ne
	beq	.L270
	b	.L283
	.size	MVC_UnMarkLTFldByFrmIdx, .-MVC_UnMarkLTFldByFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkSTRef
	.type	MVC_UnMarkSTRef, %function
MVC_UnMarkSTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	bl	_mcount
	ldrb	w0, [x20, 3]
	cbnz	w0, .L286
	add	x0, x19, 11124736
	ldr	w3, [x20, 672]
	sub	w3, w3, #1
	ldr	w1, [x0, 832]
	sub	w2, w3, w21
	cbz	w1, .L285
	sub	w4, w1, #1
	add	x0, x0, 568
	add	x4, x4, 1388544
	add	x5, x19, 11157504
	add	x4, x4, 2120
	add	x4, x19, x4, lsl 3
	b	.L292
	.p2align 3
.L291:
	cmp	x0, x4
	beq	.L285
.L292:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 732]
	cmp	w3, w2
	bne	.L291
	ldrb	w3, [x1, 3]
	cmp	w3, 3
	bne	.L291
	ldr	w3, [x1, 712]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L291
	ldr	w6, [x1, 56]
	ldr	w3, [x5, 3408]
	cmp	w6, w3
	bne	.L291
	mov	x0, x19
	bl	MVC_UnMarkFrameStoreRef
.L285:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L286:
	add	x1, x19, 11124736
	ldr	w0, [x20, 672]
	add	x4, x1, 568
	mov	w3, 0
	lsl	w0, w0, 1
	add	x8, x19, 11157504
	ldr	w6, [x1, 832]
	sub	w2, w0, w21
	cbz	w6, .L285
	.p2align 2
.L306:
	ldr	x1, [x4]
	add	x4, x4, 8
	ldrb	w0, [x1, 3]
	and	w7, w0, 1
	tbz	x0, 0, .L293
	ldr	w5, [x1, 760]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L313
.L293:
	tbz	x0, 1, .L295
	ldr	w0, [x1, 808]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L314
.L295:
	add	w3, w3, 1
	cmp	w3, w6
	bne	.L306
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L313:
	ldr	w9, [x1, 56]
	ldr	w5, [x8, 3408]
	cmp	w9, w5
	bne	.L293
	ldr	w5, [x1, 780]
	cmp	w5, w2
	bne	.L293
	add	x2, x19, x3, uxtw 3
	and	w0, w0, 2
	add	x2, x2, 11124736
	strb	w0, [x1, 3]
	ldr	x0, [x2, 568]
	strb	wzr, [x0, 762]
	ldr	x0, [x2, 568]
	ldrb	w1, [x0, 712]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L294
	strb	wzr, [x0, 714]
	ldr	x0, [x2, 568]
	strb	wzr, [x0, 713]
	ldr	x0, [x2, 568]
.L294:
	ldrb	w1, [x0, 3]
	cbnz	w1, .L285
	ldr	w1, [x0, 48]
	mov	w2, 0
	add	x1, x19, x1, lsl 2
	str	wzr, [x1, 148]
	ldrsb	w1, [x0, 6]
	ldr	w0, [x19, 120]
	bl	FSP_SetRef
	b	.L285
	.p2align 3
.L314:
	ldr	w5, [x1, 56]
	ldr	w0, [x8, 3408]
	cmp	w5, w0
	bne	.L295
	ldr	w0, [x1, 828]
	cmp	w0, w2
	bne	.L295
	add	x0, x19, x3, uxtw 3
	strb	w7, [x1, 3]
	add	x0, x0, 11124736
	ldr	x1, [x0, 568]
	strb	wzr, [x1, 810]
	ldr	x1, [x0, 568]
	ldrb	w2, [x1, 712]
	cmp	w2, 3
	ccmp	w2, wzr, 4, ne
	bne	.L296
	strb	wzr, [x1, 714]
	ldr	x1, [x0, 568]
	strb	wzr, [x1, 713]
	ldr	x1, [x0, 568]
.L296:
	ldrb	w0, [x1, 3]
	cbnz	w0, .L285
	ldr	w0, [x1, 48]
	mov	w2, 0
	add	x0, x19, x0, lsl 2
	str	wzr, [x0, 148]
	ldrsb	w1, [x1, 6]
	ldr	w0, [x19, 120]
	bl	FSP_SetRef
	b	.L285
	.size	MVC_UnMarkSTRef, .-MVC_UnMarkSTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkLTRef
	.type	MVC_UnMarkLTRef, %function
MVC_UnMarkLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x1
	mov	x19, x0
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	ldrb	w0, [x21, 3]
	cbz	w0, .L316
	add	x0, x19, 11124736
	mov	w3, 0
	add	x4, x0, 696
	add	x2, x19, 11157504
	ldr	w6, [x0, 836]
	cbz	w6, .L315
	.p2align 2
.L336:
	ldr	x1, [x4]
	add	x4, x4, 8
	ldrb	w0, [x1, 3]
	and	w7, w0, 1
	tbz	x0, 0, .L321
	ldr	w5, [x1, 760]
	and	w5, w5, 16776960
	cmp	w5, 256
	beq	.L343
.L321:
	tbz	x0, 1, .L323
	ldr	w0, [x1, 808]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L344
.L323:
	add	w3, w3, 1
	cmp	w3, w6
	bne	.L336
.L315:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L343:
	ldr	w8, [x1, 56]
	ldr	w5, [x2, 3408]
	cmp	w8, w5
	bne	.L321
	ldr	w5, [x1, 776]
	cmp	w20, w5
	bne	.L321
	add	x2, x19, x3, uxtw 3
	and	w0, w0, 2
	add	x2, x2, 11124736
	strb	w0, [x1, 3]
	ldr	x0, [x2, 696]
	strb	wzr, [x0, 761]
	ldr	x0, [x2, 696]
	ldrb	w1, [x0, 712]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L322
	strb	wzr, [x0, 714]
	ldr	x0, [x2, 696]
	strb	wzr, [x0, 713]
	ldr	x0, [x2, 696]
.L322:
	ldrb	w1, [x0, 3]
	cbnz	w1, .L315
	ldr	w1, [x0, 48]
	mov	w2, 0
	add	x1, x19, x1, lsl 2
	str	wzr, [x1, 148]
	ldrsb	w1, [x0, 6]
	ldr	w0, [x19, 120]
	bl	FSP_SetRef
	b	.L315
	.p2align 3
.L344:
	ldr	w5, [x1, 56]
	ldr	w0, [x2, 3408]
	cmp	w5, w0
	bne	.L323
	ldr	w0, [x1, 824]
	cmp	w20, w0
	bne	.L323
	add	x0, x19, x3, uxtw 3
	strb	w7, [x1, 3]
	add	x0, x0, 11124736
	ldr	x1, [x0, 696]
	strb	wzr, [x1, 809]
	ldr	x1, [x0, 696]
	ldrb	w2, [x1, 712]
	cmp	w2, 3
	ccmp	w2, wzr, 4, ne
	bne	.L324
	strb	wzr, [x1, 714]
	ldr	x1, [x0, 696]
	strb	wzr, [x1, 713]
	ldr	x1, [x0, 696]
.L324:
	ldrb	w0, [x1, 3]
	cbnz	w0, .L315
	ldr	w0, [x1, 48]
	mov	w2, 0
	add	x0, x19, x0, lsl 2
	str	wzr, [x0, 148]
	ldrsb	w1, [x1, 6]
	ldr	w0, [x19, 120]
	bl	FSP_SetRef
	b	.L315
	.p2align 3
.L316:
	add	x0, x19, 11124736
	ldr	w1, [x0, 836]
	cbz	w1, .L315
	sub	w4, w1, #1
	add	x0, x0, 696
	add	x4, x4, 1388544
	add	x5, x19, 11157504
	add	x4, x4, 2136
	add	x4, x19, x4, lsl 3
	b	.L327
	.p2align 3
.L326:
	cmp	x0, x4
	beq	.L315
.L327:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 728]
	cmp	w3, w20
	bne	.L326
	ldrb	w2, [x1, 3]
	cmp	w2, 3
	bne	.L326
	ldr	w2, [x1, 712]
	and	w2, w2, 16776960
	cmp	w2, 256
	bne	.L326
	ldr	w3, [x1, 56]
	ldr	w2, [x5, 3408]
	cmp	w3, w2
	bne	.L326
	mov	x0, x19
	bl	MVC_UnMarkFrameStoreRef
	b	.L315
	.size	MVC_UnMarkLTRef, .-MVC_UnMarkLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_MarkPicLTRef
	.type	MVC_MarkPicLTRef, %function
MVC_MarkPicLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x3
	mov	x21, x0
	mov	x0, x30
	mov	w20, w2
	mov	w19, w1
	bl	_mcount
	ldrb	w2, [x22, 3]
	add	x0, x21, 11124736
	cbz	w2, .L346
	ldr	w7, [x0, 832]
	mov	w3, 0
	add	x4, x0, 568
	add	x8, x21, 11157504
	cbz	w7, .L345
	.p2align 2
.L367:
	ldr	x0, [x4]
	ldrb	w5, [x0, 3]
	tbz	x5, 0, .L352
	ldr	w6, [x0, 760]
	and	w6, w6, 16776960
	cmp	w6, 65536
	beq	.L373
.L352:
	tbz	x5, 1, .L355
	ldr	w1, [x0, 808]
	and	w1, w1, 16776960
	cmp	w1, 65536
	beq	.L374
.L355:
	add	w3, w3, 1
	add	x4, x4, 8
	cmp	w3, w7
	bne	.L367
.L345:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L373:
	ldr	w1, [x0, 780]
	cmp	w20, w1
	bne	.L352
	ldr	w6, [x0, 56]
	ldr	w1, [x8, 3408]
	cmp	w6, w1
	bne	.L352
	ldrb	w1, [x0, 809]
	cmp	w1, 1
	bne	.L356
	ldr	w1, [x0, 28]
	cmp	w19, w1
	bne	.L355
.L356:
	add	x3, x21, x3, uxtw 3
	str	w19, [x0, 28]
	add	x0, x3, 11124736
	cmp	w2, 1
	lsl	w1, w19, 1
	mov	w2, 1
	csinc	w1, w1, w1, ne
	ldr	x3, [x0, 568]
	str	w1, [x3, 776]
	ldr	x1, [x0, 568]
	strb	w2, [x1, 761]
	ldr	x1, [x0, 568]
	strb	wzr, [x1, 762]
	ldr	x1, [x0, 568]
	ldrb	w2, [x1, 712]
	cmp	w2, 3
	ccmp	w2, wzr, 4, ne
	bne	.L345
	ldrb	w3, [x1, 761]
	ldrb	w2, [x1, 809]
	cmp	w2, w3
	bne	.L345
	strb	w2, [x1, 713]
	ldr	x0, [x0, 568]
	ldrb	w1, [x0, 762]
	strb	w1, [x0, 714]
	b	.L345
	.p2align 3
.L374:
	ldr	w1, [x0, 828]
	cmp	w1, w20
	bne	.L355
	ldr	w5, [x0, 56]
	ldr	w1, [x8, 3408]
	cmp	w5, w1
	bne	.L355
	ldrb	w1, [x0, 761]
	cmp	w1, 1
	bne	.L359
	ldr	w1, [x0, 28]
	cmp	w1, w19
	bne	.L355
.L359:
	add	x3, x21, x3, uxtw 3
	str	w19, [x0, 28]
	add	x0, x3, 11124736
	cmp	w2, 2
	lsl	w1, w19, 1
	mov	w2, 1
	csinc	w1, w1, w1, ne
	ldr	x3, [x0, 568]
	str	w1, [x3, 824]
	ldr	x1, [x0, 568]
	strb	w2, [x1, 809]
	ldr	x1, [x0, 568]
	strb	wzr, [x1, 810]
	ldr	x1, [x0, 568]
	ldrb	w2, [x1, 712]
	cmp	w2, 3
	ccmp	w2, wzr, 4, ne
	bne	.L345
	ldrb	w3, [x1, 761]
	ldrb	w2, [x1, 809]
	cmp	w2, w3
	bne	.L345
	strb	w2, [x1, 713]
	ldr	x0, [x0, 568]
	ldrb	w1, [x0, 810]
	strb	w1, [x0, 714]
	b	.L345
	.p2align 3
.L346:
	ldr	w6, [x0, 832]
	cbz	w6, .L345
	add	x0, x0, 568
	mov	w1, 0
	add	x3, x21, 11157504
	b	.L351
	.p2align 3
.L350:
	add	w1, w1, 1
	cmp	w1, w6
	beq	.L345
.L351:
	ldr	x4, [x0]
	add	x0, x0, 8
	ldrb	w5, [x4, 3]
	cmp	w5, 3
	bne	.L350
	ldr	w5, [x4, 712]
	and	w5, w5, 16776960
	cmp	w5, 65536
	bne	.L350
	ldr	w2, [x4, 732]
	cmp	w20, w2
	bne	.L350
	ldr	w2, [x3, 3408]
	ldr	w5, [x4, 56]
	cmp	w5, w2
	bne	.L350
	add	x0, x21, x1, uxtw 3
	str	w19, [x4, 28]
	add	x0, x0, 11124736
	mov	w1, 1
	ldr	x2, [x0, 568]
	str	w19, [x2, 728]
	ldr	x2, [x0, 568]
	strb	w1, [x2, 713]
	ldr	x2, [x0, 568]
	strb	w1, [x2, 761]
	ldr	x2, [x0, 568]
	strb	w1, [x2, 809]
	ldr	x1, [x0, 568]
	strb	wzr, [x1, 714]
	ldr	x1, [x0, 568]
	strb	wzr, [x1, 762]
	ldr	x0, [x0, 568]
	strb	wzr, [x0, 810]
	b	.L345
	.size	MVC_MarkPicLTRef, .-MVC_MarkPicLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_MarkSTToLTRef
	.type	MVC_MarkSTToLTRef, %function
MVC_MarkSTToLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x21, x0
	mov	x0, x30
	mov	w20, w2
	mov	w19, w3
	bl	_mcount
	ldrb	w0, [x22, 3]
	cbnz	w0, .L376
	ldr	w2, [x22, 672]
	mov	w1, w19
	mov	x0, x21
	sub	w2, w2, #1
	sub	w20, w2, w20
	bl	MVC_UnMarkLTFrmByFrmIdx
.L377:
	mov	x3, x22
	mov	w2, w20
	mov	w1, w19
	mov	x0, x21
	bl	MVC_MarkPicLTRef
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L376:
	add	x0, x21, 11124736
	ldr	w3, [x22, 672]
	lsl	w3, w3, 1
	ldr	w1, [x0, 832]
	sub	w20, w3, w20
	cbz	w1, .L377
	sub	w5, w1, #1
	add	x0, x0, 568
	add	x5, x5, 1388544
	add	x6, x21, 11157504
	add	x5, x5, 2120
	add	x5, x21, x5, lsl 3
	.p2align 2
.L380:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 3]
	tbz	x3, 0, .L378
	ldr	w4, [x1, 760]
	and	w4, w4, 16776960
	cmp	w4, 65536
	beq	.L391
.L378:
	tbz	x3, 1, .L379
	ldr	w3, [x1, 808]
	and	w3, w3, 16776960
	cmp	w3, 65536
	beq	.L392
.L379:
	cmp	x0, x5
	bne	.L380
	b	.L377
	.p2align 3
.L391:
	ldr	w2, [x1, 780]
	cmp	w2, w20
	bne	.L378
	ldr	w4, [x1, 56]
	ldr	w2, [x6, 3408]
	cmp	w4, w2
	bne	.L378
	mov	w3, w19
	mov	w2, 1
	mov	x0, x21
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L377
	.p2align 3
.L392:
	ldr	w2, [x1, 828]
	cmp	w2, w20
	bne	.L379
	ldr	w3, [x1, 56]
	ldr	w2, [x6, 3408]
	cmp	w3, w2
	bne	.L379
	mov	w3, w19
	mov	w2, 2
	mov	x0, x21
	bl	MVC_UnMarkLTFldByFrmIdx
	b	.L377
	.size	MVC_MarkSTToLTRef, .-MVC_MarkSTToLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdateMaxLTFrmIdx
	.type	MVC_UpdateMaxLTFrmIdx, %function
MVC_UpdateMaxLTFrmIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 11124736
	mov	w20, w1
	bl	_mcount
	ldr	w0, [x21, 836]
	str	w20, [x21, 840]
	cbz	w0, .L393
	mov	w2, w20
	mov	w19, 0
	add	x20, x22, 11157504
	b	.L395
	.p2align 3
.L401:
	ldr	w2, [x21, 840]
.L395:
	uxtw	x0, w19
	add	w19, w19, 1
	add	x0, x0, 1388544
	add	x0, x22, x0, lsl 3
	ldr	x1, [x0, 17080]
	ldr	w0, [x1, 28]
	cmp	w0, w2
	bcc	.L396
	ldr	w2, [x1, 56]
	ldr	w0, [x20, 3408]
	cmp	w2, w0
	beq	.L400
.L396:
	ldr	w0, [x21, 836]
	cmp	w0, w19
	bhi	.L401
.L393:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L400:
	mov	x0, x22
	bl	MVC_UnMarkFrameStoreRef
	b	.L396
	.size	MVC_UpdateMaxLTFrmIdx, .-MVC_UpdateMaxLTFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UnMarkAllSTRef
	.type	MVC_UnMarkAllSTRef, %function
MVC_UnMarkAllSTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 11124736
	mov	w19, 0
	bl	_mcount
	add	x22, x20, 11157504
	ldr	w0, [x21, 832]
	cbnz	w0, .L407
	b	.L402
	.p2align 3
.L404:
	ldr	w0, [x21, 832]
	cmp	w0, w19
	bls	.L402
.L407:
	uxtw	x0, w19
	ldr	w2, [x22, 3408]
	add	x0, x0, 1388544
	add	w19, w19, 1
	add	x0, x20, x0, lsl 3
	ldr	x1, [x0, 16952]
	ldr	w0, [x1, 56]
	cmp	w0, w2
	bne	.L404
	mov	x0, x20
	bl	MVC_UnMarkFrameStoreRef
	ldr	w0, [x21, 832]
	cmp	w0, w19
	bhi	.L407
.L402:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_UnMarkAllSTRef, .-MVC_UnMarkAllSTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_MarkCurrPicLT
	.type	MVC_MarkCurrPicLT, %function
MVC_MarkCurrPicLT:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x21, x0
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	ldrb	w2, [x19, 3]
	cbz	w2, .L412
	ldr	x1, [x19, 656]
	mov	w3, w20
	mov	x0, x21
	bl	MVC_UnMarkLTFldByFrmIdx
	strb	wzr, [x19, 5]
	str	w20, [x19, 676]
	mov	w0, 1
	strb	w0, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L412:
	mov	w1, w20
	mov	x0, x21
	bl	MVC_UnMarkLTFrmByFrmIdx
	strb	wzr, [x19, 5]
	str	w20, [x19, 676]
	mov	w0, 1
	strb	w0, [x19, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_MarkCurrPicLT, .-MVC_MarkCurrPicLT
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_RemoveFrameStoreOutDPB
	.type	MVC_RemoveFrameStoreOutDPB, %function
MVC_RemoveFrameStoreOutDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w1
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, x19, uxtw 3
	add	x19, x19, 11124736
	bl	_mcount
	ldr	x1, [x19, 440]
	cbz	x1, .L413
	ldr	w0, [x1, 52]
	add	x21, x20, 11124736
	add	x0, x20, x0
	add	x0, x0, 11124736
	strb	wzr, [x0, 848]
	ldr	w0, [x21, 1060]
	cmp	w0, wzr
	cset	w2, ne
	sub	w0, w0, w2
	str	w0, [x21, 1060]
	ldrsb	w1, [x1, 6]
	ldr	w0, [x20, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L416
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L417
	ldr	x1, [x19, 440]
	mov	w2, 0
	ldr	w0, [x20, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
.L417:
	ldr	x1, [x19, 440]
	mov	w2, 0
	ldr	w0, [x20, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetRef
.L416:
	ldr	x0, [x19, 440]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 440]
	strb	wzr, [x0, 5]
	ldr	x0, [x19, 440]
	strb	wzr, [x0, 3]
	str	xzr, [x19, 440]
	ldr	w0, [x21, 828]
	sub	w0, w0, #1
	str	w0, [x21, 828]
.L413:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_RemoveFrameStoreOutDPB, .-MVC_RemoveFrameStoreOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_RemoveUnUsedFrameStore
	.type	MVC_RemoveUnUsedFrameStore, %function
MVC_RemoveUnUsedFrameStore:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w22, w1
	mov	w19, 0
	bl	_mcount
	add	x0, x23, 11124736
	add	x20, x0, 440
	ldr	w21, [x0, 824]
	cbz	w21, .L445
	.p2align 2
.L440:
	ldr	x2, [x20]
	add	x20, x20, 8
	cbz	x2, .L431
	ldrb	w0, [x2, 3]
	cbnz	w0, .L431
	ldrb	w0, [x2, 5]
	cbnz	w0, .L431
	ldr	w0, [x2, 56]
	cmp	w0, w22
	ccmn	w22, #1, 4, ne
	beq	.L446
	.p2align 2
.L431:
	add	w19, w19, 1
	cmp	w21, w19
	bne	.L440
.L445:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L446:
	ldr	w3, [x2, 16]
	mov	w1, w19
	mov	x0, x23
	cmp	w3, 1
	beq	.L431
	strb	wzr, [x2, 2]
	bl	MVC_RemoveFrameStoreOutDPB
	b	.L431
	.size	MVC_RemoveUnUsedFrameStore, .-MVC_RemoveUnUsedFrameStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CheckFrameStore
	.type	MVC_CheckFrameStore, %function
MVC_CheckFrameStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldrb	w0, [x20, 6]
	cbnz	w0, .L448
	ldrsb	w0, [x19, 8]
	cmp	w0, 1
	bne	.L460
	strb	w0, [x20, 6]
.L448:
	ldrsb	w1, [x19, 6]
	ldr	w0, [x20, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L450
	ldrsb	w3, [x0, 1]
	cmp	w3, 3
	ccmp	w3, wzr, 4, ne
	beq	.L469
	ldrb	w2, [x19, 2]
	ldrb	w3, [x19, 1]
	cbz	w2, .L459
	cmp	w3, 1
	beq	.L459
	mov	x1, 16711680
	ldr	x4, [x19]
	movk	x1, 0xff, lsl 32
	mov	x3, 196608
	movk	x3, 0x3, lsl 32
	and	x1, x4, x1
	cmp	x1, x3
	beq	.L470
	cmp	w2, 1
	beq	.L471
	cmp	w2, 2
	beq	.L472
.L456:
	ldr	x1, [x20, 224]
	ldr	w2, [x0, 200]
	mov	w0, 0
	ldr	w3, [x1, 4]
	cmp	w2, w3
	bhi	.L473
.L466:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L469:
	ldrsb	w2, [x19, 6]
	mov	w0, 1
	ldr	x1, .LC15
	bl	dprint_vfmw
.L452:
	ldr	w0, [x19, 16]
	cmp	w0, 1
	beq	.L457
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L471:
	ldrb	w3, [x19, 4]
	tbz	x3, 0, .L456
	ldr	x1, .LC23
	mov	w0, w2
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
	.p2align 3
.L472:
	ldrb	w3, [x19, 4]
	tbz	x3, 1, .L456
	ldr	x1, .LC25
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
	.p2align 3
.L457:
	mov	w1, 2
	mov	w0, -3
	str	w1, [x19, 16]
	b	.L466
	.p2align 3
.L460:
	mov	w0, -1
	b	.L466
	.p2align 3
.L450:
	ldrsb	w4, [x19, 6]
	mov	x2, x19
	ldr	x1, .LC17
	mov	w0, 1
	ldr	w3, [x19, 16]
	bl	dprint_vfmw
	b	.L452
	.p2align 3
.L459:
	ldr	x1, .LC19
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
	.p2align 3
.L473:
	ldr	x1, .LC27
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
.L470:
	ldrb	w3, [x19, 4]
	mov	w0, 1
	ldr	x1, .LC21
	bl	dprint_vfmw
	mov	w0, -1
	b	.L466
	.size	MVC_CheckFrameStore, .-MVC_CheckFrameStore
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
	.align	3
.LC21:
	.xword	.LC20
	.align	3
.LC23:
	.xword	.LC22
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ExchangePts
	.type	MVC_ExchangePts, %function
MVC_ExchangePts:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x24, x1
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x24, 656]
	cmn	x0, #1
	beq	.L474
	add	x25, x21, 11124736
	ldr	w0, [x25, 824]
	cbz	w0, .L474
	mov	w23, -1
	mov	w20, 0
	mov	x22, -2
	.p2align 2
.L479:
	add	x19, x21, x20, sxtw 3
	add	x19, x19, 11124736
	ldr	x0, [x19, 440]
	cbz	x0, .L478
	ldrsb	w1, [x0, 6]
	ldr	w0, [x21, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L478
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	ccmp	w0, wzr, 4, ne
	beq	.L478
	ldr	x0, [x19, 440]
	ldr	x0, [x0, 656]
	cmp	x0, x22
	bcs	.L478
	mov	w23, w20
	mov	x22, x0
	.p2align 2
.L478:
	ldr	w0, [x25, 824]
	add	w20, w20, 1
	cmp	w0, w20
	bhi	.L479
	cmn	w23, #1
	beq	.L474
	ldr	x2, [x24, 656]
	cmp	x22, x2
	bcc	.L493
.L474:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L493:
	ldr	x1, .LC29
	mov	x3, x22
	mov	w0, 29
	bl	dprint_vfmw
	sxtw	x0, w23
	ldr	x1, [x24, 656]
	add	x0, x0, 1388544
	add	x21, x21, x0, lsl 3
	ldr	x0, [x21, 16824]
	str	x1, [x0, 656]
	str	x22, [x24, 656]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	MVC_ExchangePts, .-MVC_ExchangePts
	.align	3
.LC29:
	.xword	.LC28
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetImagePara
	.type	MVC_GetImagePara, %function
MVC_GetImagePara:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x5, x20, 11116544
	mov	w2, 2240
	ldp	x7, x1, [x20, 272]
	ldrb	w6, [x19, 138]
	ldr	w3, [x5, 2888]
	ldrb	w8, [x19, 14]
	ldrb	w4, [x19, 137]
	umull	x2, w3, w2
	ldrb	w0, [x19, 136]
	bfi	w6, w8, 1, 1
	add	x2, x1, x2
	and	w3, w4, -4
	and	w0, w0, -4
	mov	w1, 3992
	mov	w4, w3
	ldr	w2, [x2, 28]
	strb	w6, [x19, 138]
	ldrb	w6, [x19, 15]
	strb	w3, [x19, 137]
	str	w6, [x19, 192]
	add	x6, x20, 11124736
	strb	w0, [x19, 136]
	ldrb	w3, [x19, 2]
	umull	x1, w2, w1
	ldr	w2, [x20, 56]
	cmp	w3, 3
	str	w2, [x19, 180]
	add	x1, x7, x1
	bhi	.L495
	ldr	x2, .LC30
	ldrb	w2, [x2,w3,uxtw]
	adr	x6, .Lrtx497
	add	x2, x6, w2, sxtb #2
	br	x2
.Lrtx497:
	.section	.rodata
	.align	0
	.align	2
.L497:
	.byte	(.L496 - .Lrtx497) / 4
	.byte	(.L498 - .Lrtx497) / 4
	.byte	(.L499 - .Lrtx497) / 4
	.byte	(.L496 - .Lrtx497) / 4
	.text
	.p2align 3
.L499:
	mov	w2, 2
	bfi	w4, w2, 2, 2
.L498:
	ldrb	w7, [x19]
	orr	w2, w4, 3
	ldr	w6, [x19, 44]
	mov	w4, w2
	bfi	w0, w7, 0, 2
	str	w6, [x19, 224]
	strb	w2, [x19, 137]
	add	x6, x20, 11124736
	strb	w0, [x19, 136]
.L495:
	ldrb	w2, [x1, 20]
	mov	w0, 0
	str	w2, [x19, 468]
	str	w2, [x19, 472]
	ldrb	w2, [x1, 24]
	cbz	w2, .L514
	ldr	w0, [x1, 68]
.L514:
	str	w0, [x19, 480]
	mov	w0, 1
	str	w0, [x19, 476]
	ldrb	w0, [x5, 2883]
	cmp	w0, 1
	csel	w0, w0, wzr, eq
	str	w0, [x19, 264]
	ldr	x0, [x20, 224]
	ldr	w0, [x0, 24]
	cbz	w0, .L517
	ldrb	w0, [x19, 712]
	cbz	w0, .L543
.L517:
	ldrsb	w0, [x6, 392]
	cbz	w0, .L518
	ldr	w0, [x6, 408]
	cmp	w0, 3
	beq	.L544
	cmp	w0, 4
	beq	.L545
	cmp	w0, 5
	beq	.L546
	str	wzr, [x19, 348]
	mov	w0, 0
	ldr	x1, .LC32
	ldr	w2, [x6, 408]
	bl	dprint_vfmw
	.p2align 2
.L518:
	ldr	w0, [x20, 120]
	ldrsb	w1, [x19, 6]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L494
	ldr	x3, .LC33
	mov	x2, 640
	add	x1, x19, 72
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 15
	str	w0, [x20, 296]
	mov	w2, 4
	mov	w1, 1
	ldrb	w0, [x19, 712]
	strb	w1, [x20, 291]
	cmp	w0, wzr
	csel	w0, w0, w2, eq
	strb	w0, [x20, 284]
	ldr	w0, [x19, 748]
	str	w0, [x20, 300]
	strb	w1, [x20, 289]
	str	w0, [x20, 304]
	str	w0, [x20, 308]
.L494:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L543:
	cmp	w3, 3
	bne	.L517
	and	w0, w4, -4
	strb	w0, [x19, 137]
	b	.L517
	.p2align 3
.L496:
	ldrb	w2, [x19, 712]
	cbnz	w2, .L500
	ldp	w2, w6, [x19, 40]
	str	w6, [x19, 224]
	ldrb	w9, [x19]
	cbnz	w2, .L524
	mov	w10, 2
	mov	w7, 3
.L501:
	ldr	w6, [x19, 784]
	ldr	w2, [x19, 832]
	cmp	w6, w2
	beq	.L547
	cset	w2, le
.L512:
	add	x6, x20, 11124736
	ldrb	w8, [x6, 428]
	cmp	w8, 3
	beq	.L526
	cmp	w8, 4
	mov	w8, 0
	csel	w2, w2, w8, ne
.L513:
	bfi	w4, w2, 4, 2
	bfi	w0, w9, 0, 2
	bfi	w4, w7, 2, 2
	strb	w0, [x19, 136]
	mov	w0, w4
	bfi	w0, w10, 0, 2
	strb	w0, [x19, 137]
	mov	w4, w0
	b	.L495
	.p2align 3
.L544:
	mov	w0, 1
	str	w0, [x19, 348]
	b	.L518
	.p2align 3
.L546:
	mov	w0, 3
	str	w0, [x19, 348]
	b	.L518
	.p2align 3
.L500:
	ldr	w6, [x19, 792]
	ldr	w2, [x20, 116]
	ldr	w11, [x19, 840]
	cmp	w6, w2
	bhi	.L548
	cmp	w2, w11
	bcc	.L505
.L503:
	ldr	w2, [x19, 44]
	mov	w7, 3
	ldrb	w9, [x19]
	ldrb	w8, [x19, 811]
	ldrb	w10, [x19, 763]
	str	w2, [x19, 224]
.L506:
	ldrb	w2, [x19, 4]
	cmp	w2, 1
	beq	.L549
	cmp	w2, 2
	beq	.L550
.L508:
	stp	w10, w8, [x19, 128]
	mov	w10, 3
	b	.L501
	.p2align 3
.L505:
	ldrb	w9, [x19, 763]
	mov	w7, 1
	ldrb	w8, [x19, 811]
	mov	w10, w9
	str	w6, [x19, 224]
	b	.L506
	.p2align 3
.L545:
	mov	w0, 2
	str	w0, [x19, 348]
	b	.L518
	.p2align 3
.L526:
	mov	w2, 1
	b	.L513
	.p2align 3
.L547:
	ldr	w2, [x19, 140]
	cmp	w2, 720
	mov	w2, 1
	bne	.L512
	ldr	w2, [x19, 144]
	cmp	w2, 480
	cset	w2, ne
	b	.L512
	.p2align 3
.L548:
	cmp	w2, w11
	bcc	.L503
	ldrb	w9, [x19, 811]
	mov	w7, 2
	ldrb	w10, [x19, 763]
	mov	w8, w9
	str	w11, [x19, 224]
	b	.L506
	.p2align 3
.L524:
	mov	w10, 3
	mov	w7, w10
	b	.L501
	.p2align 3
.L549:
	mov	w9, w8
	mov	w7, 2
	str	w11, [x19, 224]
	b	.L508
	.p2align 3
.L550:
	mov	w9, w10
	mov	w7, 1
	str	w6, [x19, 224]
	b	.L508
	.size	MVC_GetImagePara, .-MVC_GetImagePara
	.align	3
.LC30:
	.xword	.L497
	.align	3
.LC32:
	.xword	.LC31
	.align	3
.LC33:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SetFrmRepeatCount
	.type	MVC_SetFrmRepeatCount, %function
MVC_SetFrmRepeatCount:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bls	.L552
	mov	x1, x20
	mov	x0, x19
	bl	MVC_SetFrmRepeatCount.part.2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L552:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_SetFrmRepeatCount, .-MVC_SetFrmRepeatCount
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SplitFrmToFlds
	.type	MVC_SplitFrmToFlds, %function
MVC_SplitFrmToFlds:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w4, [x19, 713]
	mov	w6, 1
	ldrb	w3, [x19, 714]
	mov	w5, 2
	ldrb	w1, [x19, 715]
	ldr	w2, [x19, 744]
	ldr	x0, [x19, 720]
	strb	w4, [x19, 761]
	strb	w3, [x19, 762]
	strb	w6, [x19, 760]
	strb	w1, [x19, 763]
	strb	w4, [x19, 809]
	strb	w3, [x19, 810]
	strb	w5, [x19, 808]
	strb	w1, [x19, 811]
	str	x0, [x19, 768]
	str	w2, [x19, 792]
	str	x0, [x19, 816]
	str	w2, [x19, 840]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_SplitFrmToFlds, .-MVC_SplitFrmToFlds
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CombineFldsToFrm
	.type	MVC_CombineFldsToFrm, %function
MVC_CombineFldsToFrm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 784]
	mov	w5, 3
	ldr	w3, [x19, 792]
	ldr	w2, [x19, 832]
	ldr	w0, [x19, 840]
	cmp	w1, w2
	ldr	x4, [x19, 768]
	add	w0, w3, w0
	ldrb	w3, [x19, 809]
	csel	w1, w1, w2, le
	lsr	w0, w0, 1
	strb	w5, [x19, 712]
	str	w1, [x19, 32]
	str	x4, [x19, 720]
	str	w1, [x19, 736]
	str	w0, [x19, 744]
	cbz	w3, .L556
	ldrb	w1, [x19, 761]
	cbz	w1, .L556
	mov	w1, 1
	strb	w1, [x19, 713]
.L558:
	mov	w3, 0
.L559:
	ldrb	w2, [x19, 811]
	ldrb	w1, [x19, 763]
	str	w0, [x19, 44]
	cmp	w1, w2, uxtb
	strb	w3, [x19, 714]
	csel	w0, w1, w2, cs
	strb	w0, [x19, 715]
	strb	w0, [x19]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L556:
	ldr	w1, [x19, 808]
	strb	wzr, [x19, 713]
	tst	w1, 16776960
	beq	.L558
	ldr	w1, [x19, 760]
	mov	w3, 1
	tst	w1, 16776960
	bne	.L559
	b	.L558
	.size	MVC_CombineFldsToFrm, .-MVC_CombineFldsToFrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetAPC
	.type	MVC_GetAPC, %function
MVC_GetAPC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x21, x1
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	cbz	x21, .L592
	cmp	w19, 1
	beq	.L572
	cmp	w19, 2
	beq	.L573
	ldr	w23, [x21, 784]
	ldr	w24, [x21, 832]
.L574:
	add	x20, x22, 11124736
	ldr	w2, [x20, 1056]
	cbz	w2, .L583
	ldrb	w0, [x20, 848]
	cbz	w0, .L593
	add	x0, x20, 849
	mov	w19, 0
	b	.L577
	.p2align 3
.L581:
	ldrb	w1, [x0], 1
	cbz	w1, .L575
.L577:
	add	w19, w19, 1
	cmp	w19, w2
	bne	.L581
.L583:
	mov	w0, -1
.L587:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L573:
	ldr	w23, [x21, 832]
	mov	w24, w23
	b	.L574
.L593:
	mov	w19, 0
	.p2align 2
.L575:
	ldrsb	w1, [x21, 6]
	ldr	w0, [x22, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L578
	ldr	x1, [x0, 32]
	cbz	x1, .L578
	uxtw	x1, w19
	mov	w2, 1
	add	x3, x22, x1
	mov	w4, 16
	add	x3, x3, 11124736
	add	x1, x22, x1, lsl 2
	add	x1, x1, 11124736
	strb	w2, [x3, 848]
	mov	w3, w19
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x1, 864]
	mov	w0, 13
	str	w23, [x1, 928]
	str	w24, [x1, 992]
	ldr	x1, .LC41
	ldr	w2, [x20, 1060]
	cmp	w2, 15
	csinc	w2, w4, w2, hi
	str	w2, [x20, 1060]
	ldr	w2, [x21, 220]
	bl	dprint_vfmw
	str	w19, [x21, 52]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L572:
	ldr	w23, [x21, 784]
	mov	w24, w23
	b	.L574
.L578:
	ldrsb	w2, [x21, 6]
	mov	x4, x0
	ldrb	w3, [x21, 3]
	mov	x5, 0
	ldr	x1, .LC43
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L587
.L592:
	ldr	x2, .LC37
	mov	w3, 2023
	ldr	x1, .LC39
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L587
	.size	MVC_GetAPC, .-MVC_GetAPC
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC43:
	.xword	.LC42
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SlidingWinMark
	.type	MVC_SlidingWinMark, %function
MVC_SlidingWinMark:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11124736
	ldr	x0, [x19, 248]
	ldr	w2, [x1, 836]
	ldr	w0, [x0, 3944]
	ldr	w1, [x1, 832]
	sub	w0, w0, w2
	cmp	w1, w0
	bne	.L594
	mov	x0, x19
	bl	MVC_SlidingWinMark.part.3
.L594:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_SlidingWinMark, .-MVC_SlidingWinMark
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DumpDPB
	.type	MVC_DumpDPB, %function
MVC_DumpDPB:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC44
	ldr	w0, [x0]
	tbz	x0, 14, .L596
	add	x22, x21, 11124736
	ldr	w0, [x22, 828]
	cbz	w0, .L602
	ldr	x20, .LC48
	mov	w19, 0
	.p2align 2
.L601:
	uxtw	x3, w19
	mov	w2, w19
	add	x3, x3, 1388544
	mov	x1, x20
	mov	w0, 14
	add	w19, w19, 1
	add	x3, x21, x3, lsl 3
	ldr	x3, [x3, 16824]
	ldrb	w5, [x3, 3]
	ldr	w4, [x3, 32]
	ldr	w3, [x3, 20]
	bl	dprint_vfmw
	ldr	w0, [x22, 828]
	cmp	w0, w19
	bhi	.L601
.L602:
	ldr	x25, .LC46
	mov	w0, 14
	mov	x1, x25
	bl	dprint_vfmw
	ldr	w0, [x22, 832]
	cbz	w0, .L600
	ldr	x24, .LC50
	mov	w19, 0
	ldr	x23, .LC52
	.p2align 2
.L603:
	add	x20, x21, x19, uxtw 3
	mov	w2, w19
	add	x20, x20, 11124736
	mov	x1, x24
	mov	w0, 14
	ldr	x3, [x20, 568]
	ldrb	w5, [x3, 3]
	ldr	w4, [x3, 32]
	ldr	w3, [x3, 20]
	bl	dprint_vfmw
	ldr	x3, [x20, 568]
	mov	w2, w19
	mov	x1, x23
	mov	w0, 14
	add	w19, w19, 1
	ldr	w3, [x3, 736]
	bl	dprint_vfmw
	ldr	w0, [x22, 832]
	cmp	w0, w19
	bhi	.L603
.L600:
	mov	x1, x25
	mov	w0, 14
	bl	dprint_vfmw
.L596:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	MVC_DumpDPB, .-MVC_DumpDPB
	.align	3
.LC44:
	.xword	g_PrintEnable
	.align	3
.LC46:
	.xword	.LC45
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC50:
	.xword	.LC49
	.align	3
.LC52:
	.xword	.LC51
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdateCurrFrameInfo
	.type	MVC_UpdateCurrFrameInfo, %function
MVC_UpdateCurrFrameInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11157504
	mov	w2, 3
	ldr	x19, [x1, 3320]
	ldrb	w3, [x1, 2666]
	strb	w3, [x19, 1]
	ldrb	w3, [x1, 2668]
	cbnz	w3, .L610
	ldrb	w2, [x1, 2669]
	mov	w0, 3
	cmp	w2, wzr
	csel	w2, w2, w0, eq
.L610:
	add	x3, x1, 2664
	strb	w2, [x19, 3]
	mov	w2, 3
	ldr	w0, [x3, 672]
	str	w0, [x19, 20]
	ldr	w0, [x3, 716]
	str	w0, [x19, 44]
	ldrb	w0, [x3, 12]
	strb	w0, [x19]
	ldr	w0, [x3, 684]
	str	w0, [x19, 32]
	ldr	w0, [x3, 740]
	str	w0, [x19, 48]
	ldr	w0, [x3, 676]
	str	w0, [x19, 28]
	ldrb	w0, [x3, 9]
	str	w0, [x19, 40]
	ldrb	w0, [x3, 7]
	cmp	w0, 1
	csel	w0, w2, wzr, eq
	strb	w0, [x19, 4]
	ldrb	w4, [x3, 3]
	cmp	w4, 1
	beq	.L613
	cbz	w4, .L614
	cmp	w4, 2
	bne	.L609
	str	x19, [x19, 816]
	mov	w5, 1
	strb	w5, [x19, 808]
	ldrb	w5, [x3, 4]
	strb	w5, [x19, 809]
	ldrb	w5, [x3, 5]
	strb	w5, [x19, 810]
	ldr	w5, [x3, 692]
	str	w5, [x19, 832]
	ldrb	w6, [x3, 12]
	strb	w6, [x19, 811]
	ldr	w5, [x3, 716]
	str	w5, [x19, 840]
	str	wzr, [x19, 40]
	ldrb	w7, [x3, 1]
	cbz	w7, .L636
	ldr	w4, [x19, 792]
	orr	w0, w0, 2
	strb	w2, [x19, 2]
	mov	w2, 0
	add	w5, w5, w4
	str	w5, [x19, 44]
	str	w5, [x19, 744]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w0, w0, w2, eq
	strb	w0, [x19, 4]
	ldr	x0, [x1, 3264]
	cmn	x0, #1
	beq	.L622
	ldr	x2, [x19, 656]
	cmn	x2, #1
	beq	.L637
.L622:
	ldrb	w2, [x19, 763]
.L640:
	cmp	w2, w6
	mov	x0, x19
	csel	w6, w2, w6, cs
	strb	w6, [x19]
	ldr	w1, [x1, 3348]
	str	w1, [x19, 32]
	bl	MVC_CombineFldsToFrm
.L609:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L614:
	strb	w2, [x19, 2]
	add	x1, x1, 2680
	strb	wzr, [x19, 712]
	mov	x2, 640
	str	x19, [x19, 720]
	add	x0, x19, 72
	ldrb	w23, [x3, 4]
	strb	w23, [x19, 713]
	ldrb	w22, [x3, 5]
	strb	w22, [x19, 714]
	ldr	w4, [x3, 688]
	str	w4, [x19, 736]
	ldrb	w20, [x3, 12]
	strb	w20, [x19, 715]
	ldr	w21, [x3, 716]
	str	w21, [x19, 744]
	ldr	w4, [x3, 692]
	str	w4, [x19, 784]
	ldr	w3, [x3, 696]
	str	w3, [x19, 832]
	bl	memcpy
	strb	w23, [x19, 761]
	strb	w22, [x19, 762]
	mov	w1, 1
	strb	w20, [x19, 763]
	mov	w0, 2
	strb	w1, [x19, 760]
	strb	w23, [x19, 809]
	strb	w22, [x19, 810]
	strb	w0, [x19, 808]
	strb	w20, [x19, 811]
	str	x19, [x19, 768]
	str	w21, [x19, 792]
	str	x19, [x19, 816]
	str	w21, [x19, 840]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L613:
	strb	w4, [x19, 760]
	str	x19, [x19, 768]
	ldrb	w5, [x3, 4]
	strb	w5, [x19, 761]
	ldrb	w5, [x3, 5]
	strb	w5, [x19, 762]
	ldr	w5, [x3, 692]
	str	w5, [x19, 784]
	ldrb	w6, [x3, 12]
	strb	w6, [x19, 763]
	ldr	w5, [x3, 716]
	str	w5, [x19, 792]
	str	wzr, [x19, 40]
	ldrb	w7, [x3, 1]
	cbz	w7, .L638
	ldr	w4, [x19, 840]
	orr	w0, w0, 1
	strb	w2, [x19, 2]
	mov	w2, 0
	add	w5, w5, w4
	str	w5, [x19, 44]
	str	w5, [x19, 744]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w0, w0, w2, eq
	strb	w0, [x19, 4]
	ldr	x0, [x1, 3264]
	cmn	x0, #1
	beq	.L618
	ldr	x2, [x19, 656]
	cmn	x2, #1
	beq	.L639
.L618:
	ldrb	w2, [x19, 811]
	mov	x0, x19
	cmp	w2, w6
	csel	w6, w2, w6, cs
	strb	w6, [x19]
	ldr	w1, [x1, 3348]
	str	w1, [x19, 32]
	bl	MVC_CombineFldsToFrm
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L636:
	strb	w4, [x19, 2]
	mov	x2, 640
	str	w5, [x19, 44]
	add	x1, x1, 2680
	str	w5, [x19, 744]
	add	x0, x19, 72
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w7, wzr, w4, ne
	strb	w7, [x19, 4]
	bl	memcpy
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L638:
	strb	w4, [x19, 2]
	mov	x2, 640
	str	w5, [x19, 44]
	add	x1, x1, 2680
	str	w5, [x19, 744]
	add	x0, x19, 72
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	cset	w3, eq
	strb	w3, [x19, 4]
	bl	memcpy
	b	.L609
	.p2align 3
.L639:
	str	x0, [x19, 656]
	b	.L618
	.p2align 3
.L637:
	str	x0, [x19, 656]
	ldrb	w2, [x19, 763]
	b	.L640
	.size	MVC_UpdateCurrFrameInfo, .-MVC_UpdateCurrFrameInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SimpleSlideDPB
	.type	MVC_SimpleSlideDPB, %function
MVC_SimpleSlideDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 11157504
	bl	_mcount
	add	x0, x21, 11124736
	ldr	w19, [x0, 824]
	ldr	w1, [x0, 828]
	cmp	w1, w19
	bcc	.L642
	cbz	w19, .L647
	add	x0, x0, 440
	mov	w5, 0
	mov	w4, 2147483647
	mov	w1, 0
	.p2align 2
.L645:
	ldr	x2, [x0]
	add	x0, x0, 8
	cbz	x2, .L644
	ldr	w3, [x2, 64]
	cmp	w3, w4
	bcs	.L644
	ldr	w6, [x2, 56]
	ldr	w2, [x20, 3408]
	cmp	w6, w2
	csel	w4, w4, w3, ne
	csel	w5, w5, w1, ne
.L644:
	add	w1, w1, 1
	cmp	w19, w1
	bne	.L645
	mov	w19, w5
.L643:
	sxtw	x1, w5
	mov	x0, x21
	add	x1, x1, 1388544
	add	x1, x21, x1, lsl 3
	ldr	x1, [x1, 16824]
	bl	MVC_UnMarkFrameStoreRef
	mov	w1, w19
	mov	x0, x21
	bl	MVC_RemoveFrameStoreOutDPB
.L642:
	ldr	w0, [x20, 3344]
	strb	wzr, [x20, 2668]
	cbz	w0, .L641
	mov	w0, 1
	strb	w0, [x20, 2669]
.L641:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L647:
	mov	w5, 0
	b	.L643
	.size	MVC_SimpleSlideDPB, .-MVC_SimpleSlideDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReleaseNAL
	.type	MVC_ReleaseNAL, %function
MVC_ReleaseNAL:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L665
	ldr	x23, .LC58
	add	x19, x20, 8
	strb	wzr, [x20, 1]
	add	x22, x20, 72
	strb	wzr, [x20, 3]
.L660:
	ldr	x1, [x19]
	mov	w0, w21
	cbz	x1, .L659
	ldr	w1, [x19, 28]
	bl	SM_ReleaseStreamSeg
	ldr	w3, [x19, 8]
	mov	x1, x23
	ldr	x2, [x19]
	mov	w0, 7
	bl	dprint_vfmw
	str	xzr, [x19]
	str	wzr, [x19, 8]
	str	wzr, [x19, 20]
.L659:
	add	x19, x19, 32
	cmp	x19, x22
	bne	.L660
	strb	wzr, [x20]
	str	wzr, [x20, 76]
.L656:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L665:
	ldr	x2, .LC55
	mov	w3, 3891
	ldr	x1, .LC56
	mov	w0, 0
	bl	dprint_vfmw
	b	.L656
	.size	MVC_ReleaseNAL, .-MVC_ReleaseNAL
	.align	3
.LC55:
	.xword	.LC36
	.align	3
.LC56:
	.xword	.LC38
	.align	3
.LC58:
	.xword	.LC57
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearCurrNal
	.type	MVC_ClearCurrNal, %function
MVC_ClearCurrNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 240]
	cbz	x1, .L667
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L667:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ClearCurrNal, .-MVC_ClearCurrNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearCurrSlice
	.type	MVC_ClearCurrSlice, %function
MVC_ClearCurrSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC60
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbz	x1, .L672
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L672:
	ldr	w1, [x19, 80]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 80]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ClearCurrSlice, .-MVC_ClearCurrSlice
	.align	3
.LC60:
	.xword	.LC59
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearAllNal
	.type	MVC_ClearAllNal, %function
MVC_ClearAllNal:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 12288
	add	x19, x21, 1520
	bl	_mcount
	add	x20, x20, 2384
	b	.L678
	.p2align 3
.L677:
	add	x19, x19, 96
	cmp	x19, x20
	beq	.L680
.L678:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L677
	ldr	w0, [x21, 120]
	mov	x1, x19
	add	x19, x19, 96
	bl	MVC_ReleaseNAL
	cmp	x19, x20
	bne	.L678
.L680:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_ClearAllNal, .-MVC_ClearAllNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearAllSlice
	.type	MVC_ClearAllSlice, %function
MVC_ClearAllSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 11161600
	add	x19, x20, 104
	add	x20, x20, 1192
	bl	_mcount
	.p2align 2
.L683:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L682
	ldr	w0, [x21, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19]
.L682:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L683
	str	wzr, [x21, 64]
	mov	w0, 0
	str	wzr, [x21, 104]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_ClearAllSlice, .-MVC_ClearAllSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearCurrPic
	.type	MVC_ClearCurrPic, %function
MVC_ClearCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L691
	mov	x0, x19
	bl	MVC_ClearAllSlice
	add	x0, x19, 11120640
	mov	w4, 32
	ldr	w8, [x19, 40]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x0, 434]
	add	x4, x0, 256
	strb	wzr, [x0, 432]
	mov	w5, 7
	strb	w6, [x0, 433]
	mov	w3, 3
	strb	w5, [x0, 435]
	mov	w2, -1
	str	w8, [x0, 444]
	mov	w1, 262144
	str	w7, [x0, 448]
	stp	w3, w2, [x4, 200]
	stp	wzr, wzr, [x4, 208]
	str	w1, [x0, 472]
	mov	w0, 0
.L690:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L691:
	ldr	x3, .LC62
	mov	w2, 300
	ldr	x1, .LC64
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L690
	.size	MVC_ClearCurrPic, .-MVC_ClearCurrPic
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ArrangeVahbMem
	.type	MVC_ArrangeVahbMem, %function
MVC_ArrangeVahbMem:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w2
	mov	w20, w1
	mov	w22, w4
	bl	_mcount
	mov	w0, 8160
	sub	w2, w21, #32
	sub	w1, w20, #32
	cmp	w2, w0
	ccmp	w1, w0, 2, ls
	bhi	.L693
	ldr	x3, .LC65
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x19, 224]
	stp	w20, w21, [x29, 60]
	stp	w20, w21, [x29, 68]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L706
	add	x0, x19, 11124736
	mov	w1, 5
	sxtb	w4, w22
	strb	w1, [x29, 58]
	ldr	w0, [x0, 824]
	add	w0, w0, 3
	strb	w0, [x29, 57]
.L701:
	ldr	w0, [x19, 120]
	add	x1, x29, 56
	strb	w4, [x29, 59]
	bl	FSP_ConfigInstance
	cbnz	w0, .L697
	ldr	x1, [x19, 224]
	add	x3, x29, 52
	ldr	w0, [x19, 120]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	mov	w1, w0
	beq	.L707
	mov	w0, 1
	cbnz	w1, .L699
.L702:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L706:
	mov	w1, 1
	mov	w0, 5
	strb	w1, [x29, 57]
	mov	w4, 1
	strb	w0, [x29, 58]
	b	.L701
	.p2align 3
.L707:
	add	x0, x19, 912
	bl	ResetVoQueue
.L699:
	ldr	x1, .LC69
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L702
	.p2align 3
.L693:
	ldr	x1, .LC67
	mov	w3, w21
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L697:
	ldr	x1, .LC71
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L702
	.size	MVC_ArrangeVahbMem, .-MVC_ArrangeVahbMem
	.align	3
.LC65:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC71:
	.xword	.LC70
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_RepairList
	.type	MVC_RepairList, %function
MVC_RepairList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x6, x19, 11116544
	ldrb	w0, [x6, 2872]
	cmp	w0, 1
	beq	.L726
	cbz	w0, .L711
	cmp	w0, 2
	mov	w0, 0
	bne	.L722
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L722:
	mov	x0, x19
	bl	MVC_ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L726:
	mov	w10, 2
.L710:
	add	x6, x6, 2920
	add	x5, x19, 288
	mov	x8, 0
	mov	w7, 0
	mov	w12, 1
	add	x11, x19, 11157504
	.p2align 2
.L723:
	ldr	w0, [x6]
	cbz	w0, .L713
	ldr	x1, [x5]
	cbnz	x1, .L737
	sub	w3, w0, #1
	add	x9, x8, 37
	add	x0, x5, 8
	add	x4, x9, x3, uxtw
	add	x4, x19, x4, lsl 3
	b	.L716
	.p2align 3
.L717:
	ldr	x2, [x0], 8
	cbnz	x2, .L724
.L716:
	cmp	x0, x4
	bne	.L717
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L722
	ldr	x2, [x11, 3320]
	add	x2, x2, 712
.L724:
	add	x3, x9, x3, uxtw
	mov	x0, x5
	add	x3, x19, x3, lsl 3
	cbz	x1, .L738
	.p2align 2
.L719:
	add	x0, x0, 8
	cmp	x3, x0
	beq	.L720
.L739:
	ldr	x1, [x0]
	cbnz	x1, .L719
.L738:
	str	x2, [x0]
	add	x0, x0, 8
	cmp	x3, x0
	bne	.L739
	.p2align 2
.L720:
	add	w7, w7, 1
	add	x6, x6, 4
	cmp	w7, w10
	add	x5, x5, 264
	add	x8, x8, 33
	bcc	.L723
.L740:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L713:
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L722
	str	w12, [x6]
	add	w7, w7, 1
	cmp	w7, w10
	add	x6, x6, 4
	ldr	x0, [x11, 3320]
	add	x8, x8, 33
	add	x0, x0, 712
	str	x0, [x5]
	add	x5, x5, 264
	bcc	.L723
	b	.L740
.L737:
	sub	w3, w0, #1
	mov	x2, x1
	add	x9, x8, 37
	b	.L724
.L711:
	mov	w10, 1
	b	.L710
	.size	MVC_RepairList, .-MVC_RepairList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetShortTermPicPoint
	.type	MVC_GetShortTermPicPoint, %function
MVC_GetShortTermPicPoint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 11116544
	mov	w5, 0
	ldrb	w1, [x0, 2873]
	cbz	w1, .L742
	ldrb	w0, [x0, 2874]
	mov	w5, 2
	cmp	w0, wzr
	csinc	w5, w5, wzr, ne
.L742:
	add	x0, x20, 11124736
	ldr	w2, [x0, 832]
	cbz	w2, .L750
	sub	w2, w2, #1
	add	x0, x0, 568
	add	x2, x2, 1388544
	add	x2, x2, 2120
	add	x4, x20, x2, lsl 3
	b	.L747
	.p2align 3
.L760:
	cmp	w3, 3
	beq	.L759
.L745:
	add	x0, x0, 8
	cmp	x0, x4
	beq	.L750
.L747:
	ldr	x2, [x0]
	ldrb	w3, [x2, 3]
	cbz	w5, .L760
	tbz	x3, 0, .L746
	ldr	w6, [x2, 760]
	and	w6, w6, 16776960
	cmp	w6, 65536
	beq	.L761
.L746:
	tbz	x3, 1, .L745
	ldr	w3, [x2, 808]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L745
	ldr	w1, [x2, 828]
	cmp	w19, w1
	bne	.L745
	add	x0, x2, 808
	b	.L743
	.p2align 3
.L761:
	ldr	w1, [x2, 780]
	cmp	w1, w19
	bne	.L746
	add	x0, x2, 760
	b	.L743
	.p2align 3
.L759:
	ldr	w3, [x2, 712]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L745
	ldr	w1, [x2, 732]
	cmp	w19, w1
	bne	.L745
	add	x0, x2, 712
	b	.L743
	.p2align 3
.L750:
	mov	x0, 0
.L743:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_GetShortTermPicPoint, .-MVC_GetShortTermPicPoint
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetLongTermPicPoint
	.type	MVC_GetLongTermPicPoint, %function
MVC_GetLongTermPicPoint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 11116544
	mov	w5, 0
	ldrb	w1, [x0, 2873]
	cbz	w1, .L763
	ldrb	w0, [x0, 2874]
	mov	w5, 2
	cmp	w0, wzr
	csinc	w5, w5, wzr, ne
.L763:
	add	x0, x20, 11124736
	ldr	w2, [x0, 836]
	cbz	w2, .L771
	sub	w2, w2, #1
	add	x0, x0, 696
	add	x2, x2, 1388544
	add	x2, x2, 2136
	add	x4, x20, x2, lsl 3
	b	.L768
	.p2align 3
.L781:
	cmp	w3, 3
	beq	.L780
.L766:
	add	x0, x0, 8
	cmp	x0, x4
	beq	.L771
.L768:
	ldr	x2, [x0]
	ldrb	w3, [x2, 3]
	cbz	w5, .L781
	tbz	x3, 0, .L767
	ldr	w6, [x2, 760]
	and	w6, w6, 16776960
	cmp	w6, 256
	beq	.L782
.L767:
	tbz	x3, 1, .L766
	ldr	w3, [x2, 808]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L766
	ldr	w1, [x2, 824]
	cmp	w19, w1
	bne	.L766
	add	x0, x2, 808
	b	.L764
	.p2align 3
.L782:
	ldr	w1, [x2, 776]
	cmp	w1, w19
	bne	.L767
	add	x0, x2, 760
	b	.L764
	.p2align 3
.L780:
	ldr	w3, [x2, 712]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L766
	ldr	w1, [x2, 728]
	cmp	w19, w1
	bne	.L766
	add	x0, x2, 712
	b	.L764
	.p2align 3
.L771:
	mov	x0, 0
.L764:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_GetLongTermPicPoint, .-MVC_GetLongTermPicPoint
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReorderSTList
	.type	MVC_ReorderSTList, %function
MVC_ReorderSTList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	w23, w3
	mov	x22, x4
	mov	w24, w5
	bl	_mcount
	uxtw	x6, w20
	mov	x0, x19
	lsl	x2, x6, 8
	mov	w1, w23
	add	x6, x2, x6, lsl 3
	add	x6, x6, 288
	add	x19, x19, x6
	bl	MVC_GetShortTermPicPoint
	ldr	w6, [x22]
	add	w2, w21, 1
	cmp	w2, w6
	ble	.L784
	mov	w1, w2
	.p2align 2
.L785:
	add	x6, x19, x1, sxtw 3
	ldr	x6, [x6, -8]
	str	x6, [x19, w1, sxtw 3]
	sub	w1, w1, #1
	ldr	w6, [x22]
	cmp	w6, w1
	blt	.L785
.L784:
	add	w1, w6, 1
	str	w1, [x22]
	str	x0, [x19, w6, sxtw 3]
	ldr	w0, [x22]
	cmp	w2, w0
	mov	w4, w0
	bge	.L793
	b	.L783
	.p2align 3
.L788:
	str	x1, [x19, w4, sxtw 3]
	add	w4, w4, 1
.L787:
	cmp	w2, w0
	blt	.L783
.L793:
	ldr	x1, [x19, w0, sxtw 3]
	add	w0, w0, 1
	cbz	x1, .L787
	ldrb	w6, [x1, 1]
	cbnz	w6, .L788
	ldr	w6, [x1, 20]
	cmp	w23, w6
	bne	.L788
	ldr	x3, [x1, 8]
	ldr	w3, [x3, 56]
	cmp	w3, w24
	bne	.L788
	cmp	w2, w0
	bge	.L793
.L783:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MVC_ReorderSTList, .-MVC_ReorderSTList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReorderLTList
	.type	MVC_ReorderLTList, %function
MVC_ReorderLTList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	mov	w23, w3
	mov	x22, x4
	mov	w24, w5
	bl	_mcount
	uxtw	x6, w20
	mov	x0, x19
	lsl	x2, x6, 8
	mov	w1, w23
	add	x6, x2, x6, lsl 3
	add	x6, x6, 288
	add	x19, x19, x6
	bl	MVC_GetLongTermPicPoint
	ldr	w6, [x22]
	add	w2, w21, 1
	cmp	w2, w6
	ble	.L799
	mov	w1, w2
	.p2align 2
.L800:
	add	x6, x19, x1, sxtw 3
	ldr	x6, [x6, -8]
	str	x6, [x19, w1, sxtw 3]
	sub	w1, w1, #1
	ldr	w6, [x22]
	cmp	w6, w1
	blt	.L800
.L799:
	add	w1, w6, 1
	str	w1, [x22]
	str	x0, [x19, w6, sxtw 3]
	ldr	w0, [x22]
	cmp	w2, w0
	mov	w4, w0
	bge	.L810
	b	.L798
	.p2align 3
.L803:
	str	x1, [x19, w4, sxtw 3]
	add	w4, w4, 1
.L802:
	cmp	w2, w0
	blt	.L798
.L810:
	ldr	x1, [x19, w0, sxtw 3]
	add	w0, w0, 1
	cbz	x1, .L802
	ldrb	w6, [x1, 1]
	cbz	w6, .L803
	ldr	w6, [x1, 16]
	cmp	w23, w6
	bne	.L803
	ldr	x3, [x1, 8]
	ldr	w3, [x3, 56]
	cmp	w3, w24
	bne	.L803
	cmp	w2, w0
	bge	.L810
.L798:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MVC_ReorderLTList, .-MVC_ReorderLTList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetMaxViewIdx
	.type	MVC_GetMaxViewIdx, %function
MVC_GetMaxViewIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w1
	mov	w22, w2
	mov	w20, w3
	bl	_mcount
	add	x0, x21, 10768384
	add	x1, x0, 4068
	ldr	w5, [x0, 4064]
	adds	w5, w5, 1
	beq	.L824
	ldr	w0, [x0, 4068]
	cmp	w19, w0
	beq	.L824
	mov	w6, w5
	mov	w0, 0
	b	.L818
	.p2align 3
.L820:
	ldr	w4, [x1, w0, sxtw 2]
	cmp	w19, w4
	beq	.L826
.L818:
	add	w0, w0, 1
	cmp	w0, w5
	bne	.L820
.L821:
	mov	w0, 0
	tbnz	w6, #31, .L819
.L817:
	sbfiz	x0, x20, 1, 32
	add	x0, x0, x6, sxtw
	cbnz	w22, .L827
	add	x0, x21, x0, lsl 2
	add	x0, x0, 10772480
	ldr	w0, [x0, 12]
.L819:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L827:
	add	x0, x0, 2691072
	ldp	x19, x20, [sp, 16]
	add	x0, x21, x0, lsl 2
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ldr	w0, [x0, 8172]
	ret
	.p2align 3
.L826:
	mov	w6, w0
	b	.L821
.L824:
	mov	w6, 0
	b	.L817
	.size	MVC_GetMaxViewIdx, .-MVC_GetMaxViewIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_get_inter_view_pic
	.type	mvc_get_inter_view_pic, %function
mvc_get_inter_view_pic:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w3
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	uxtw	x1, w22
	lsl	x0, x1, 3
	add	x2, x1, 2777088
	sub	x0, x0, x1
	lsl	x0, x0, 2
	add	x2, x20, x2, lsl 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	ldr	w1, [x2, 12712]
	lsl	x0, x0, 4
	add	x0, x0, 11108352
	add	x0, x0, 272
	add	x0, x20, x0
	cbz	w1, .L834
	sub	w4, w1, #1
	add	x5, x20, 11157504
	add	x4, x4, 1
	lsl	x3, x4, 3
	sub	x3, x3, x4
	lsl	x3, x3, 2
	sub	x3, x3, x4
	lsl	x3, x3, 2
	sub	x4, x3, x4
	add	x4, x0, x4, lsl 3
	b	.L833
	.p2align 3
.L830:
	add	x0, x0, 856
	cmp	x0, x4
	beq	.L834
.L833:
	ldr	w3, [x0, 56]
	cmp	w3, w19
	bne	.L830
	ldrb	w1, [x5, 2667]
	cmp	w1, 1
	cbnz	w1, .L831
	ldr	w1, [x0, 740]
	cmp	w21, w1
	bne	.L830
	add	x0, x0, 712
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L831:
	bne	.L832
	ldr	w1, [x0, 788]
	cmp	w1, w21
	bne	.L830
	add	x0, x0, 760
	b	.L829
	.p2align 3
.L832:
	cmp	w1, 2
	bne	.L830
	ldr	w1, [x0, 836]
	cmp	w21, w1
	bne	.L830
	add	x0, x0, 808
	b	.L829
	.p2align 3
.L834:
	mov	x0, 0
.L829:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	mvc_get_inter_view_pic, .-mvc_get_inter_view_pic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_reorder_interview
	.type	mvc_reorder_interview, %function
mvc_reorder_interview:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	w24, w5
	mov	w22, w3
	mov	w23, w4
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	uxtw	x0, w24
	mov	w3, w24
	lsl	x5, x0, 8
	mov	w2, w23
	add	x5, x5, x0, lsl 3
	mov	w1, w22
	mov	x0, x19
	add	x5, x5, 288
	add	x19, x19, x5
	bl	mvc_get_inter_view_pic
	cbz	x0, .L836
	ldr	w3, [x21]
	add	w1, w20, 1
	cmp	w1, w3
	bls	.L838
	mov	w2, w1
	uxtw	x5, w1
	.p2align 2
.L839:
	sub	w2, w2, #1
	lsl	x3, x5, 3
	uxtw	x5, w2
	ldr	x6, [x19, w2, uxtw 3]
	str	x6, [x19, x3]
	ldr	w3, [x21]
	cmp	w3, w2
	bcc	.L839
.L838:
	add	w2, w3, 1
	str	w2, [x21]
	str	x0, [x19, w3, uxtw 3]
	ldr	w0, [x21]
	cmp	w1, w0
	bcc	.L836
	mov	w3, w0
	b	.L843
	.p2align 3
.L841:
	str	x2, [x19, w3, uxtw 3]
	cmp	w1, w0
	add	w3, w3, 1
	bcc	.L836
.L843:
	ldr	x2, [x19, w0, uxtw 3]
	add	w0, w0, 1
	cbz	x2, .L841
	ldr	x5, [x2, 8]
	ldr	w5, [x5, 56]
	cmp	w22, w5
	bne	.L841
	ldr	w5, [x2, 28]
	cmp	w23, w5
	bne	.L841
	cmp	w1, w0
	bcs	.L843
.L836:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	mvc_reorder_interview, .-mvc_reorder_interview
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReorderRefPiclist
	.type	MVC_ReorderRefPiclist, %function
MVC_ReorderRefPiclist:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	add	x20, x27, 11116544
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	str	wzr, [x29, 188]
	mov	w0, 0
	ldrb	w1, [x20, 2873]
	cbz	w1, .L851
	ldrb	w1, [x20, 2874]
	mov	w0, 2
	cmp	w1, wzr
	csinc	w0, w0, wzr, ne
.L851:
	cmp	w19, 1
	bls	.L907
.L850:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L907:
	cbz	w19, .L908
	add	x1, x20, 1956
	str	x1, [x29, 168]
	add	x1, x20, 2220
	str	x1, [x29, 120]
	add	x1, x20, 2480
	str	x1, [x29, 104]
	ldr	x1, [x27, 248]
	add	x28, x20, 2740
	ldr	w25, [x1, 2896]
	add	w1, w25, 4
	mov	w25, 1
	lsl	w1, w25, w1
	str	w1, [x29, 148]
	cbnz	w0, .L855
.L913:
	ldr	w0, [x20, 2900]
	str	w0, [x29, 144]
.L856:
	cmn	w21, #2
	beq	.L850
	ldr	x0, [x29, 168]
	ldr	w1, [x0]
	cmp	w1, 3
	beq	.L850
	add	w23, w21, 1
	mov	w2, 1
	lsl	x0, x23, 2
	str	x0, [x29, 160]
	stp	w2, wzr, [x29, 152]
	add	x0, x27, 10768384
	add	x2, x27, 11157504
	mov	x23, 0
	str	x2, [x29, 136]
	mov	w22, 0
	ubfiz	x2, x19, 1, 32
	mov	w26, 0
	ldr	w24, [x29, 144]
	add	x25, x0, 4068
	str	x0, [x29, 112]
	str	x2, [x29, 128]
	b	.L859
	.p2align 3
.L912:
	ldr	w3, [x0, 8188]
.L882:
	ldr	x0, [x29, 136]
	mov	w5, w19
	add	x2, x29, 188
	mov	w1, w21
	ldr	w4, [x0, 3348]
	mov	x0, x27
	bl	mvc_reorder_interview
.L864:
	ldr	x0, [x29, 160]
	cmp	x0, x23
	beq	.L850
	add	x23, x23, 4
	ldr	x0, [x29, 168]
	ldr	w1, [x0, x23]
	cmp	w1, 3
	beq	.L850
.L859:
	cmp	w1, 1
	bls	.L909
	cmp	w1, 2
	beq	.L910
	ldr	w0, [x29, 152]
	cbnz	w0, .L866
	ldrb	w5, [x20, 2881]
	mov	w6, w26
.L867:
	cmp	w1, 4
	ldr	w0, [x28, x23]
	beq	.L911
	add	w0, w0, 1
	add	w26, w0, w6
	cmp	w22, w26
	sub	w0, w26, w22
	csel	w26, w0, w26, le
.L880:
	ldr	w1, [x29, 156]
	ldr	x0, [x29, 128]
	add	x0, x0, x26, sxtw
	add	x0, x0, x1, sxtw
	add	x0, x0, 2691072
	add	x0, x27, x0, lsl 2
	cbnz	w5, .L912
	ldr	w3, [x0, 8220]
	b	.L882
	.p2align 3
.L908:
	add	x1, x20, 1824
	str	x1, [x29, 168]
	add	x1, x20, 2088
	str	x1, [x29, 120]
	add	x1, x20, 2352
	str	x1, [x29, 104]
	ldr	x1, [x27, 248]
	add	x28, x20, 2608
	ldr	w25, [x1, 2896]
	add	w1, w25, 4
	mov	w25, 1
	lsl	w1, w25, w1
	str	w1, [x29, 148]
	cbz	w0, .L913
.L855:
	ldr	w0, [x20, 2900]
	ldr	w1, [x29, 148]
	lsl	w0, w0, 1
	add	w0, w0, 1
	lsl	w1, w1, 1
	stp	w0, w1, [x29, 144]
	b	.L856
	.p2align 3
.L909:
	ldr	x0, [x29, 120]
	ldr	w0, [x0, x23]
	cbnz	w1, .L861
	mvn	w0, w0
	add	w24, w24, w0
	ldr	w0, [x29, 148]
	cmp	w24, wzr
	add	w0, w24, w0
	csel	w24, w0, w24, lt
.L862:
	ldr	w0, [x29, 144]
	add	x4, x29, 188
	mov	w2, w21
	mov	w1, w19
	cmp	w0, w24
	add	x0, x27, 11120640
	ldr	w5, [x0, 416]
	ldr	w0, [x29, 148]
	sub	w3, w24, w0
	mov	x0, x27
	csel	w3, w3, w24, lt
	bl	MVC_ReorderSTList
	b	.L864
	.p2align 3
.L911:
	mvn	w0, w0
	add	w26, w0, w6
	cmp	w26, wzr
	add	w0, w26, w22
	csel	w26, w0, w26, lt
	b	.L880
	.p2align 3
.L866:
	ldr	x4, [x29, 112]
	add	x0, x27, 11120640
	ldr	w2, [x4, 4064]
	ldr	w3, [x0, 416]
	adds	w2, w2, 1
	beq	.L869
	ldr	w0, [x4, 4068]
	cmp	w3, w0
	beq	.L869
	mov	w0, 0
	str	w2, [x29, 156]
	b	.L872
	.p2align 3
.L873:
	ldr	w4, [x25, w0, sxtw 2]
	cmp	w3, w4
	beq	.L914
.L872:
	add	w0, w0, 1
	cmp	w2, w0
	bne	.L873
.L904:
	ldrb	w5, [x20, 2881]
	mov	w6, w2
	mov	w0, 0
	b	.L876
	.p2align 3
.L877:
	ldr	w4, [x25, w0, sxtw 2]
	cmp	w3, w4
	beq	.L906
.L876:
	add	w0, w0, 1
	cmp	w0, w2
	bne	.L877
	tbnz	w6, #31, .L890
.L884:
	sbfiz	x0, x19, 1, 32
	add	x0, x0, x6, sxtw
	cbz	w5, .L878
	add	x0, x0, 2691072
	mov	w6, -1
	str	wzr, [x29, 152]
	add	x0, x27, x0, lsl 2
	ldr	w22, [x0, 8172]
	b	.L867
	.p2align 3
.L861:
	add	w0, w0, 1
	add	w24, w24, w0
	ldr	w0, [x29, 148]
	cmp	w0, w24
	sub	w0, w24, w0
	csel	w24, w0, w24, le
	b	.L862
	.p2align 3
.L910:
	add	x0, x27, 11120640
	add	x4, x29, 188
	mov	w2, w21
	mov	w1, w19
	ldr	w5, [x0, 416]
	ldr	x0, [x29, 104]
	ldr	w3, [x0, x23]
	mov	x0, x27
	bl	MVC_ReorderLTList
	b	.L864
	.p2align 3
.L906:
	mov	w6, w0
	tbz	w6, #31, .L884
.L890:
	mov	w6, -1
	mov	w22, 0
	str	wzr, [x29, 152]
	b	.L867
	.p2align 3
.L914:
	str	w0, [x29, 156]
	b	.L904
	.p2align 3
.L878:
	add	x0, x27, x0, lsl 2
	mov	w6, -1
	add	x0, x0, 10772480
	str	wzr, [x29, 152]
	ldr	w22, [x0, 12]
	b	.L867
.L869:
	ldrb	w5, [x20, 2881]
	mov	w6, 0
	str	wzr, [x29, 156]
	b	.L884
	.size	MVC_ReorderRefPiclist, .-MVC_ReorderRefPiclist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReorderListX
	.type	MVC_ReorderListX, %function
MVC_ReorderListX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11116544
	bl	_mcount
	ldrb	w1, [x19, 2872]
	cmp	w1, 2
	beq	.L915
	ldrb	w0, [x19, 1820]
	cbnz	w0, .L927
.L918:
	ldr	w0, [x19, 2932]
	cmp	w1, 1
	add	w0, w0, 1
	str	w0, [x19, 2920]
	bne	.L915
	ldrb	w0, [x19, 1821]
	cbnz	w0, .L928
.L920:
	ldr	w0, [x19, 2936]
	add	w0, w0, 1
	str	w0, [x19, 2924]
.L915:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L927:
	ldr	w2, [x19, 2932]
	mov	w1, 0
	mov	x0, x20
	bl	MVC_ReorderRefPiclist
	ldrb	w1, [x19, 2872]
	b	.L918
	.p2align 3
.L928:
	ldr	w2, [x19, 2936]
	mov	x0, x20
	bl	MVC_ReorderRefPiclist
	b	.L920
	.size	MVC_ReorderListX, .-MVC_ReorderListX
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GenPiclistfromFrmlist
	.type	MVC_GenPiclistfromFrmlist, %function
MVC_GenPiclistfromFrmlist:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w2
	mov	x19, x1
	mov	x25, x3
	mov	x24, x4
	mov	w23, w5
	bl	_mcount
	cmp	w20, 31
	mov	w22, 31
	csel	w22, w20, w22, ls
	cbnz	w23, .L951
	cmp	w21, 1
	ldr	x23, .LC73
	beq	.L991
.L931:
	cmp	w21, 2
	bne	.L940
	mov	w21, 0
	mov	w20, 0
	.p2align 2
.L942:
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	bcs	.L940
.L992:
	cmp	w21, w22
	bcc	.L975
	b	.L947
	.p2align 3
.L943:
	add	w21, w21, 1
	cmp	w22, w21
	bls	.L947
.L975:
	ldr	x0, [x19, w21, uxtw 3]
	add	x26, x19, x21, uxtw 3
	ldrb	w1, [x0, 2]
	tbz	x1, 1, .L943
	add	x0, x0, 808
	blr	x23
	cbz	w0, .L943
	ldr	w1, [x24]
	add	w21, w21, 1
	ldr	x0, [x26]
	add	x0, x0, 808
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
.L947:
	cmp	w20, w22
	bcc	.L974
	b	.L942
	.p2align 3
.L948:
	add	w20, w20, 1
	cmp	w22, w20
	bls	.L942
.L974:
	ldr	x0, [x19, w20, uxtw 3]
	add	x26, x19, x20, uxtw 3
	ldrb	w1, [x0, 2]
	tbz	x1, 0, .L948
	add	x0, x0, 760
	blr	x23
	cbz	w0, .L948
	ldr	w1, [x24]
	add	w20, w20, 1
	ldr	x0, [x26]
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	add	x0, x0, 760
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	bcc	.L992
.L940:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L951:
	cmp	w21, 1
	ldr	x23, .LC72
	bne	.L931
.L991:
	mov	w21, 0
	mov	w20, 0
	.p2align 2
.L932:
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	bcs	.L940
	cmp	w20, w22
	bcc	.L973
	b	.L990
	.p2align 3
.L933:
	add	w20, w20, 1
	cmp	w20, w22
	bcs	.L990
.L973:
	ldr	x0, [x19, w20, uxtw 3]
	add	x26, x19, x20, uxtw 3
	ldrb	w1, [x0, 2]
	tbz	x1, 0, .L933
	add	x0, x0, 760
	blr	x23
	cbz	w0, .L933
	ldr	w1, [x24]
	add	w20, w20, 1
	ldr	x0, [x26]
	add	x0, x0, 760
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	.p2align 2
.L990:
	cmp	w21, w22
	bcs	.L932
	ldr	x0, [x19, w21, uxtw 3]
	add	x26, x19, x21, uxtw 3
	ldrb	w1, [x0, 2]
	tbnz	x1, 1, .L993
.L938:
	add	w21, w21, 1
	b	.L990
	.p2align 3
.L993:
	add	x0, x0, 808
	blr	x23
	cbz	w0, .L938
	ldr	w1, [x24]
	add	w21, w21, 1
	ldr	x0, [x26]
	add	x0, x0, 808
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	b	.L932
	.size	MVC_GenPiclistfromFrmlist, .-MVC_GenPiclistfromFrmlist
	.align	3
.LC72:
	.xword	MVC_IsLTRefFlg
	.align	3
.LC73:
	.xword	MVC_IsSTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetBaseViewId
	.type	MVC_GetBaseViewId, %function
MVC_GetBaseViewId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 12288
	mov	x1, 0
	add	x0, x0, 2400
	.p2align 2
.L997:
	ldr	w2, [x0]
	add	x3, x0, 335872
	cbz	w2, .L995
	ldrb	w0, [x0, -4]
	cbnz	w0, .L1005
.L995:
	add	w1, w1, 1
	add	x0, x3, 308
	cmp	w1, 32
	bne	.L997
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1005:
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x1, x0, x1
	lsl	x0, x1, 2
	sub	x1, x0, x1
	lsl	x0, x1, 6
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 14692]
	ret
	.size	MVC_GetBaseViewId, .-MVC_GetBaseViewId
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetVOIdx
	.type	MVC_GetVOIdx, %function
MVC_GetVOIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	w19, w1
	mov	x0, x30
	mov	w21, w2
	bl	_mcount
	cbz	w19, .L1011
	ldr	w0, [x20]
	cmp	w21, w0
	beq	.L1011
	mov	w0, w19
	mov	w3, 0
	b	.L1008
	.p2align 3
.L1009:
	ldr	w4, [x20, w3, sxtw 2]
	cmp	w4, w21
	beq	.L1012
.L1008:
	add	w3, w3, 1
	cmp	w3, w19
	bne	.L1009
.L1007:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1012:
	mov	w0, w3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1011:
	mov	w0, 0
	b	.L1007
	.size	MVC_GetVOIdx, .-MVC_GetVOIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_is_view_id_in_ref_view_list
	.type	MVC_is_view_id_in_ref_view_list, %function
MVC_is_view_id_in_ref_view_list:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	w19, w2
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cbz	w19, .L1018
	ldr	w0, [x21]
	cmp	w20, w0
	beq	.L1018
	mov	w0, 0
	b	.L1015
	.p2align 3
.L1016:
	ldr	w3, [x21, w0, sxtw 2]
	cmp	w3, w20
	beq	.L1014
.L1015:
	add	w0, w0, 1
	cmp	w0, w19
	mov	w1, w0
	bne	.L1016
.L1014:
	cmp	w19, wzr
	ldr	x21, [sp, 32]
	ccmp	w19, w1, 0, ne
	cset	w0, hi
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1018:
	mov	w1, 0
	b	.L1014
	.size	MVC_is_view_id_in_ref_view_list, .-MVC_is_view_id_in_ref_view_list
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GenPiclistfromFrmlist_Interview
	.type	MVC_GenPiclistfromFrmlist_Interview, %function
MVC_GenPiclistfromFrmlist_Interview:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	x23, x1
	mov	w20, w2
	mov	x21, x3
	mov	x19, x4
	bl	_mcount
	cmp	w22, 1
	beq	.L1033
	cmp	w22, 2
	bne	.L1019
	cbz	w20, .L1019
	sub	w2, w20, #1
	mov	x1, 1664
	mov	w20, 856
	ldr	w0, [x19]
	add	x5, x23, 808
	umaddl	x20, w2, w20, x1
	add	x1, x23, x20
	.p2align 2
.L1024:
	str	x5, [x21, w0, uxtw 3]
	add	x5, x5, 856
	cmp	x5, x1
	ldr	w0, [x19]
	add	w0, w0, 1
	str	w0, [x19]
	bne	.L1024
.L1019:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1033:
	cbz	w20, .L1019
	sub	w2, w20, #1
	mov	x1, 1616
	mov	w20, 856
	ldr	w0, [x19]
	add	x4, x23, 760
	umaddl	x20, w2, w20, x1
	add	x1, x23, x20
	.p2align 2
.L1022:
	str	x4, [x21, w0, uxtw 3]
	add	x4, x4, 856
	cmp	x1, x4
	ldr	w0, [x19]
	add	w0, w0, 1
	str	w0, [x19]
	bne	.L1022
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MVC_GenPiclistfromFrmlist_Interview, .-MVC_GenPiclistfromFrmlist_Interview
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_append_interview_list
	.type	mvc_append_interview_list, %function
mvc_append_interview_list:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	mov	x24, x3
	bl	_mcount
	add	x0, x22, 10768384
	add	x1, x22, 11120640
	add	x6, x0, 4068
	ldr	w2, [x0, 4064]
	ldr	w3, [x1, 416]
	adds	w2, w2, 1
	beq	.L1035
	ldr	w0, [x0, 4068]
	cmp	w3, w0
	beq	.L1053
	mov	w5, w2
	mov	w0, 0
	b	.L1036
	.p2align 3
.L1037:
	ldr	w4, [x6, w0, sxtw 2]
	cmp	w3, w4
	beq	.L1035
.L1036:
	add	w0, w0, 1
	cmp	w0, w5
	mov	w2, w0
	bne	.L1037
.L1035:
	add	x0, x22, 11116544
	ldrb	w0, [x0, 2881]
	cbz	w0, .L1038
	ubfiz	x0, x19, 1, 32
	add	x0, x0, x2, uxtw
	add	x0, x0, 2691072
	add	x23, x0, 2044
	add	x0, x22, x0, lsl 2
	add	x23, x22, x23, lsl 2
	add	x23, x23, 12
	ldr	w25, [x0, 8172]
.L1039:
	add	x20, x22, 11157504
	add	x0, x22, 11124736
	ldrb	w1, [x20, 2667]
	ldr	w19, [x0, 824]
	cmp	w1, 2
	cset	w26, eq
	subs	w19, w19, #1
	bmi	.L1034
	ldr	x28, .LC74
	mov	w27, 856
	b	.L1070
	.p2align 3
.L1081:
	ldrb	w0, [x1, 2]
	cmp	w0, 3
	beq	.L1080
.L1041:
	subs	w19, w19, #1
	bmi	.L1034
.L1070:
	sxtw	x0, w19
	add	x0, x0, 1388544
	add	x0, x22, x0, lsl 3
	ldr	x1, [x0, 16824]
	cbz	x1, .L1041
	ldrb	w0, [x20, 2667]
	cbz	w0, .L1081
	cmp	w0, 1
	beq	.L1082
	cmp	w0, 2
	bne	.L1041
	ldrb	w2, [x20, 2665]
	ldrb	w0, [x1, 2]
	ubfx	x0, x0, 1, 1
	cbz	w2, .L1047
	ldr	x2, [x20, 3320]
	ldr	w3, [x2, 788]
	ldr	w2, [x1, 788]
	cmp	w3, w2
	cset	w2, eq
	and	w0, w0, w2
.L1047:
	cbz	w0, .L1041
	ldr	w2, [x1, 836]
	.p2align 2
.L1043:
	add	x0, x1, x26
	ldrb	w0, [x0, 12]
	cbz	w0, .L1041
	ldr	w0, [x20, 3348]
	cmp	w0, w2
	bne	.L1041
	ldr	w3, [x1, 56]
	cbz	w25, .L1041
	ldr	w0, [x23]
	cmp	w3, w0
	beq	.L1048
	mov	w0, 0
	.p2align 2
.L1049:
	add	w0, w0, 1
	cmp	w25, w0
	beq	.L1041
	ldr	w2, [x23, w0, sxtw 2]
	cmp	w3, w2
	bne	.L1049
.L1048:
	ldr	w0, [x24]
	mov	x2, 856
	ldr	x3, [x28, 104]
	umull	x0, w0, w27
	add	x0, x21, x0
	blr	x3
	ldr	w0, [x24]
	umull	x0, w0, w27
	add	x0, x21, x0
	str	x0, [x0, 720]
	str	x0, [x0, 768]
	str	x0, [x0, 816]
	ldr	w0, [x24]
	ldr	w1, [x22, 52]
	umull	x0, w0, w27
	sub	w1, w1, #1
	add	x0, x21, x0
	str	w1, [x0, 48]
	ldr	w0, [x24]
	cmp	w25, w0
	beq	.L1034
	add	w0, w0, 1
	subs	w19, w19, #1
	str	w0, [x24]
	bpl	.L1070
.L1034:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1082:
	ldrb	w2, [x20, 2665]
	ldrb	w0, [x1, 2]
	and	w0, w0, 1
	cbz	w2, .L1045
	ldr	x3, [x20, 3320]
	ldr	w2, [x1, 836]
	ldr	w3, [x3, 836]
	cmp	w3, w2
	cset	w2, eq
	and	w0, w0, w2
.L1045:
	cbz	w0, .L1041
	ldr	w2, [x1, 788]
	b	.L1043
	.p2align 3
.L1080:
	ldr	w2, [x1, 740]
	b	.L1043
	.p2align 3
.L1038:
	ubfiz	x0, x19, 1, 32
	add	x0, x0, x2, uxtw
	add	x0, x0, 2691072
	add	x23, x0, 2052
	add	x0, x22, x0, lsl 2
	add	x23, x22, x23, lsl 2
	add	x23, x23, 12
	ldr	w25, [x0, 8204]
	b	.L1039
.L1053:
	mov	w2, 0
	b	.L1035
	.size	mvc_append_interview_list, .-mvc_append_interview_list
	.align	3
.LC74:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InitListX
	.type	MVC_InitListX, %function
MVC_InitListX:
	stp	x29, x30, [sp, -480]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11120640
	add	x20, x19, 11116544
	bl	_mcount
	add	x26, x19, 11157504
	str	wzr, [x21, 424]
	str	wzr, [x21, 428]
	ldrb	w0, [x20, 2872]
	cbnz	w0, .L1084
	ldrb	w0, [x26, 2667]
	add	x27, x19, 11124736
	cbnz	w0, .L1227
	ldr	w0, [x27, 832]
	cbz	w0, .L1164
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 1388544
	add	x0, x27, 568
	add	x3, x3, 2120
	add	x3, x19, x3, lsl 3
	b	.L1090
	.p2align 3
.L1089:
	cmp	x0, x3
	beq	.L1088
.L1090:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 3]
	cmp	w2, 3
	bne	.L1089
	ldr	w2, [x1, 712]
	and	w2, w2, 16776960
	cmp	w2, 65536
	bne	.L1089
	add	x2, x19, x23, uxtw 3
	add	x1, x1, 712
	cmp	x0, x3
	add	w23, w23, 1
	str	x1, [x2, 288]
	bne	.L1090
	.p2align 2
.L1088:
	add	x22, x19, 288
	ldr	x3, .LC75
	mov	w1, w23
	mov	w2, 8
	mov	x0, x22
	bl	qsort
	str	w23, [x20, 2920]
	ldr	w1, [x27, 836]
	cbz	w1, .L1165
	sub	w2, w1, #1
	add	x0, x27, 696
	add	x2, x2, 1388544
	mov	w24, w23
	add	x2, x2, 2136
	add	x2, x19, x2, lsl 3
	b	.L1093
	.p2align 3
.L1092:
	cmp	x2, x0
	beq	.L1228
.L1093:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 3]
	cmp	w3, 3
	bne	.L1092
	ldr	w3, [x1, 712]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L1092
	add	x3, x19, x24, uxtw 3
	add	x1, x1, 712
	cmp	x2, x0
	add	w24, w24, 1
	str	x1, [x3, 288]
	bne	.L1093
	.p2align 2
.L1228:
	sub	w1, w24, w23
.L1091:
	uxtw	x0, w23
	ldr	x3, .LC76
	add	x0, x0, 36
	mov	w2, 8
	add	x0, x19, x0, lsl 3
	bl	qsort
	str	w24, [x20, 2920]
	ldrsb	w0, [x20, 2884]
	str	wzr, [x20, 2924]
	cbnz	w0, .L1099
.L1143:
	add	x23, x19, 11108352
	mov	x0, x19
	add	x24, x23, 272
	add	x3, x21, 424
	mov	w1, 0
	mov	x2, x24
	bl	mvc_append_interview_list
	ldrb	w0, [x26, 2667]
	cbnz	w0, .L1229
	ldr	w3, [x21, 424]
	ldr	w0, [x20, 2920]
	cbz	w3, .L1168
	add	x1, x23, 984
	add	w3, w0, w3
	.p2align 2
.L1146:
	add	x2, x19, x0, uxtw 3
	add	w0, w0, 1
	cmp	w3, w0
	str	x1, [x2, 288]
	add	x1, x1, 856
	bne	.L1146
.L1145:
	str	w3, [x20, 2920]
.L1147:
	ldrb	w1, [x20, 2872]
	cmp	w1, 1
	beq	.L1230
.L1144:
	cbnz	w1, .L1151
.L1233:
	ldr	w2, [x20, 2920]
	cbz	w2, .L1231
.L1152:
	ldr	w1, [x20, 2932]
	ldr	w0, [x20, 2936]
	ldr	w3, [x20, 2924]
	add	w1, w1, 1
	add	w0, w0, 1
	cmp	w1, w2
	csel	w1, w1, w2, ls
	cmp	w0, w3
	csel	w0, w0, w3, ls
	str	w1, [x20, 2920]
	cmp	w1, 32
	str	w0, [x20, 2924]
	bhi	.L1158
	.p2align 2
.L1190:
	add	x2, x19, x1, uxtw 3
	add	w1, w1, 1
	cmp	w1, 33
	str	xzr, [x2, 288]
	bne	.L1190
.L1158:
	cmp	w0, 32
	bhi	.L1156
	.p2align 2
.L1189:
	add	x1, x19, x0, uxtw 3
	add	w0, w0, 1
	cmp	w0, 33
	str	xzr, [x1, 552]
	bne	.L1189
.L1156:
	mov	w0, 0
.L1217:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 480
	ret
	.p2align 3
.L1084:
	ldrb	w0, [x26, 2667]
	add	x27, x19, 11124736
	cbz	w0, .L1108
	ldr	w0, [x27, 832]
	cbz	w0, .L1232
	sub	w3, w0, #1
	mov	w22, 0
	add	x3, x3, 1388544
	add	x0, x27, 568
	add	x3, x3, 2120
	add	x3, x19, x3, lsl 3
	.p2align 2
.L1127:
	ldr	x2, [x0]
	add	x0, x0, 8
	ldrb	w1, [x2, 2]
	cbz	w1, .L1126
	ldr	w4, [x2, 32]
	add	x1, x29, 480
	ldr	w5, [x26, 3348]
	add	x1, x1, x22, uxtw 3
	sub	x1, x1, #4096
	cmp	w5, w4
	blt	.L1126
	add	w22, w22, 1
	str	x2, [x1, 3712]
.L1126:
	cmp	x0, x3
	bne	.L1127
	add	x24, x29, 96
	ldr	x3, .LC83
	mov	w2, 8
	mov	w1, w22
	mov	x0, x24
	bl	qsort
	ldr	w23, [x27, 832]
	cbz	w23, .L1128
.L1162:
	sub	w1, w23, #1
	add	x0, x27, 568
	add	x1, x1, 1388544
	mov	w28, w22
	add	x1, x1, 2120
	add	x1, x19, x1, lsl 3
	.p2align 2
.L1130:
	ldr	x3, [x0]
	add	x0, x0, 8
	ldrb	w2, [x3, 2]
	cbz	w2, .L1129
	ldr	w4, [x3, 32]
	add	x2, x29, 480
	ldr	w5, [x26, 3348]
	add	x2, x2, x28, uxtw 3
	sub	x2, x2, #4096
	cmp	w5, w4
	bge	.L1129
	add	w28, w28, 1
	str	x3, [x2, 3712]
.L1129:
	cmp	x0, x1
	bne	.L1130
	sub	w23, w28, w22
	ldr	x3, .LC84
	mov	w2, 8
	mov	w1, w23
	add	x0, x24, x22, uxtw 3
	bl	qsort
	cbz	w22, .L1131
.L1161:
	mov	x0, 0
	.p2align 2
.L1132:
	add	w1, w23, w0
	add	x3, x29, 480
	ldr	x2, [x24, x0, lsl 3]
	add	x0, x0, 1
	add	x1, x3, x1, lsl 3
	cmp	w22, w0
	str	x2, [x1, -256]
	bhi	.L1132
.L1131:
	cmp	w28, w22
	bls	.L1133
	mov	w0, w22
	.p2align 2
.L1134:
	add	x2, x29, 480
	sub	w1, w0, w22
	add	x2, x2, x0, uxtw 3
	add	x3, x29, 480
	sub	x2, x2, #4096
	add	x1, x3, x1, lsl 3
	add	w0, w0, 1
	cmp	w28, w0
	ldr	x2, [x2, 3712]
	str	x2, [x1, -256]
	bne	.L1134
.L1133:
	str	wzr, [x20, 2920]
	add	x22, x19, 288
	str	wzr, [x20, 2924]
	add	x25, x20, 2920
	mov	x1, x24
	mov	w2, w28
	ldrb	w0, [x26, 2667]
	mov	w5, 0
	mov	x4, x25
	mov	x3, x22
	add	x23, x19, 552
	add	x24, x20, 2924
	bl	MVC_GenPiclistfromFrmlist
	ldrb	w0, [x26, 2667]
	mov	w2, w28
	mov	w5, 0
	mov	x4, x24
	mov	x3, x23
	add	x1, x29, 224
	bl	MVC_GenPiclistfromFrmlist
	ldr	w28, [x27, 836]
	add	x27, x29, 352
	cbz	w28, .L1135
	mov	x1, 0
	add	x27, x29, 352
	.p2align 2
.L1136:
	lsl	x0, x1, 3
	add	x0, x0, 11124736
	add	x0, x0, 696
	ldr	x0, [x19, x0]
	str	x0, [x27, x1, lsl 3]
	add	x1, x1, 1
	cmp	w28, w1
	bhi	.L1136
.L1135:
	ldr	x3, .LC78
	mov	w2, 8
	mov	w1, w28
	mov	x0, x27
	bl	qsort
	ldrb	w0, [x26, 2667]
	mov	x4, x25
	mov	w5, 1
	mov	x3, x22
	mov	w2, w28
	mov	x1, x27
	bl	MVC_GenPiclistfromFrmlist
	ldrb	w0, [x26, 2667]
	mov	x3, x23
	mov	x1, x27
	mov	w5, 1
	mov	x4, x24
	mov	w2, w28
	bl	MVC_GenPiclistfromFrmlist
	ldr	w23, [x20, 2920]
	ldr	w0, [x20, 2924]
	cmp	w0, w23
	cset	w1, eq
.L1125:
	cmp	w23, 1
	cset	w0, hi
	tst	w1, w0
	beq	.L1137
	cbz	w23, .L1138
	ldr	x4, [x19, 288]
	ldr	x0, [x19, 552]
	cmp	x4, x0
	bne	.L1137
	sub	w23, w23, #1
	mov	x1, x19
	add	x0, x19, x23, lsl 3
.L1140:
	cmp	x0, x1
	beq	.L1142
	ldr	x3, [x1, 296]
	add	x1, x1, 8
	ldr	x2, [x1, 552]
	cmp	x3, x2
	beq	.L1140
	.p2align 2
.L1137:
	ldrsb	w0, [x20, 2884]
	cbz	w0, .L1143
.L1222:
	ldrb	w1, [x20, 2872]
.L1236:
	cbz	w1, .L1233
.L1151:
	ldr	x0, [x20, 2920]
	cbz	x0, .L1153
	ldr	w2, [x20, 2920]
	b	.L1152
	.p2align 3
.L1108:
	ldr	w0, [x27, 832]
	cbz	w0, .L1166
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 1388544
	add	x0, x27, 568
	add	x3, x3, 2120
	add	x3, x19, x3, lsl 3
	b	.L1113
	.p2align 3
.L1112:
	cmp	x0, x3
	beq	.L1111
.L1113:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 3]
	cmp	w2, 3
	bne	.L1112
	ldr	w2, [x1, 736]
	add	x5, x19, x23, uxtw 3
	ldr	w4, [x26, 3352]
	add	x1, x1, 712
	cmp	w4, w2
	blt	.L1112
	str	x1, [x5, 288]
	cmp	x0, x3
	add	w23, w23, 1
	bne	.L1113
	.p2align 2
.L1111:
	add	x22, x19, 288
	ldr	x3, .LC81
	mov	w2, 8
	mov	w1, w23
	mov	x0, x22
	bl	qsort
	ldr	w24, [x27, 832]
	cbz	w24, .L1114
	sub	w1, w24, #1
	add	x0, x27, 568
	add	x1, x1, 1388544
	mov	w25, w23
	add	x1, x1, 2120
	add	x1, x19, x1, lsl 3
	b	.L1116
	.p2align 3
.L1115:
	cmp	x0, x1
	beq	.L1234
.L1116:
	ldr	x2, [x0]
	add	x0, x0, 8
	ldrb	w3, [x2, 3]
	cmp	w3, 3
	bne	.L1115
	ldr	w3, [x2, 736]
	add	x5, x19, x25, uxtw 3
	ldr	w4, [x26, 3352]
	add	x2, x2, 712
	cmp	w4, w3
	bge	.L1115
	str	x2, [x5, 288]
	cmp	x0, x1
	add	w25, w25, 1
	bne	.L1116
	.p2align 2
.L1234:
	uxtw	x0, w23
	sub	w24, w25, w23
	add	x0, x0, 36
	ldr	x3, .LC82
	uxtw	x28, w25
	mov	w2, 8
	add	x0, x19, x0, lsl 3
	mov	w1, w24
	add	x28, x28, 36
	bl	qsort
	add	x28, x19, x28, lsl 3
	cbz	w23, .L1118
.L1160:
	mov	x2, x22
	mov	w0, 0
	.p2align 2
.L1119:
	add	w1, w24, w0
	ldr	x3, [x2], 8
	add	x1, x1, 69
	add	w0, w0, 1
	cmp	w0, w23
	str	x3, [x19, x1, lsl 3]
	bcc	.L1119
.L1118:
	cmp	w25, w23
	bls	.L1120
	mov	w0, w23
	.p2align 2
.L1121:
	sub	w1, w0, w23
	add	x2, x19, x0, uxtw 3
	add	x1, x1, 69
	add	w0, w0, 1
	cmp	w0, w25
	ldr	x2, [x2, 288]
	str	x2, [x19, x1, lsl 3]
	bne	.L1121
.L1120:
	str	w25, [x20, 2920]
	str	w25, [x20, 2924]
	ldr	w1, [x27, 836]
	cbz	w1, .L1167
	sub	w2, w1, #1
	add	x0, x27, 696
	add	x2, x2, 1388544
	mov	w23, w25
	add	x2, x2, 2136
	add	x2, x19, x2, lsl 3
	b	.L1124
	.p2align 3
.L1123:
	cmp	x0, x2
	beq	.L1235
.L1124:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 2]
	cmp	w3, 3
	bne	.L1123
	ldrb	w3, [x1, 713]
	cmp	w3, 1
	bne	.L1123
	add	x3, x19, x23, uxtw 3
	add	x1, x1, 712
	cmp	x0, x2
	add	w23, w23, 1
	str	x1, [x3, 288]
	str	x1, [x3, 552]
	bne	.L1124
	.p2align 2
.L1235:
	sub	w1, w23, w25
.L1122:
	ldr	x24, .LC76
	mov	x0, x28
	mov	w2, 8
	mov	x3, x24
	bl	qsort
	ldr	w0, [x20, 2920]
	mov	x3, x24
	mov	w2, 8
	sub	w1, w23, w0
	uxtw	x0, w0
	add	x0, x0, 69
	add	x0, x19, x0, lsl 3
	bl	qsort
	str	w23, [x20, 2920]
	mov	w1, 1
	str	w23, [x20, 2924]
	b	.L1125
	.p2align 3
.L1227:
	ldr	w0, [x27, 832]
	mov	w24, 0
	cbz	w0, .L1087
	sub	w4, w0, #1
	mov	w24, 0
	add	x4, x4, 1388544
	add	x0, x27, 568
	add	x4, x4, 2120
	add	x4, x19, x4, lsl 3
	.p2align 2
.L1096:
	ldr	x2, [x0]
	add	x1, x29, 480
	add	x1, x1, x24, uxtw 3
	add	x0, x0, 8
	sub	x1, x1, #4096
	cmp	x4, x0
	ldrb	w3, [x2, 3]
	cbz	w3, .L1095
	add	w24, w24, 1
	str	x2, [x1, 3712]
.L1095:
	bne	.L1096
.L1087:
	ldr	x3, .LC77
	mov	w1, w24
	mov	w2, 8
	add	x0, x29, 96
	add	x22, x19, 288
	add	x23, x20, 2920
	bl	qsort
	str	wzr, [x20, 2920]
	mov	w2, w24
	mov	w5, 0
	ldrb	w0, [x26, 2667]
	add	x1, x29, 96
	mov	x4, x23
	mov	x3, x22
	bl	MVC_GenPiclistfromFrmlist
	ldr	w24, [x27, 836]
	add	x27, x29, 352
	cbz	w24, .L1097
	mov	x1, 0
	add	x27, x29, 352
	.p2align 2
.L1098:
	lsl	x0, x1, 3
	add	x0, x0, 11124736
	add	x0, x0, 696
	ldr	x0, [x19, x0]
	str	x0, [x27, x1, lsl 3]
	add	x1, x1, 1
	cmp	w24, w1
	bhi	.L1098
.L1097:
	ldr	x3, .LC78
	mov	w2, 8
	mov	w1, w24
	mov	x0, x27
	bl	qsort
	ldrb	w0, [x26, 2667]
	mov	w5, 1
	mov	x4, x23
	mov	x3, x22
	mov	w2, w24
	mov	x1, x27
	bl	MVC_GenPiclistfromFrmlist
	str	wzr, [x20, 2924]
	ldrsb	w0, [x20, 2884]
	cbz	w0, .L1143
.L1099:
	ldr	w0, [x20, 2920]
	cbnz	w0, .L1222
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L1103
	ldrb	w0, [x26, 2667]
	cbnz	w0, .L1104
	ldr	x0, [x26, 3320]
	add	x0, x0, 712
	str	x0, [x19, 288]
.L1105:
	mov	w0, 1
	ldrb	w1, [x20, 2872]
	str	w0, [x20, 2920]
	b	.L1236
.L1229:
	ldr	w2, [x21, 424]
	add	x4, x20, 2920
	mov	x3, x22
	mov	x1, x24
	bl	MVC_GenPiclistfromFrmlist_Interview
	b	.L1147
.L1138:
	ldr	x4, [x19, 552]
.L1142:
	ldr	x0, [x19, 560]
	str	x0, [x19, 552]
	str	x4, [x19, 560]
	b	.L1137
.L1104:
	cmp	w0, 1
	ldr	x0, [x26, 3320]
	beq	.L1237
	add	x0, x0, 808
	str	x0, [x19, 288]
	b	.L1105
.L1230:
	add	x22, x23, 1984
	mov	x0, x19
	add	x3, x21, 428
	mov	x2, x22
	bl	mvc_append_interview_list
	ldrb	w0, [x26, 2667]
	cbnz	w0, .L1148
	ldr	w3, [x21, 428]
	ldr	w1, [x20, 2924]
	cbz	w3, .L1169
	add	x0, x23, 2696
	add	w3, w3, w1
	.p2align 2
.L1150:
	add	x2, x19, x1, uxtw 3
	add	w1, w1, 1
	cmp	w3, w1
	str	x0, [x2, 552]
	add	x0, x0, 856
	bne	.L1150
.L1149:
	ldrb	w1, [x20, 2872]
	str	w3, [x20, 2924]
	b	.L1144
.L1168:
	mov	w3, w0
	b	.L1145
.L1237:
	add	x0, x0, 760
	str	x0, [x19, 288]
	b	.L1105
.L1165:
	mov	w24, w23
	b	.L1091
.L1114:
	uxtw	x28, w23
	ldr	x3, .LC82
	add	x28, x28, 36
	mov	w2, 8
	mov	w1, 0
	mov	w25, w23
	add	x28, x19, x28, lsl 3
	mov	x0, x28
	bl	qsort
	cbnz	w23, .L1160
	b	.L1120
	.p2align 3
.L1167:
	mov	w23, w25
	b	.L1122
.L1164:
	mov	w23, 0
	b	.L1088
.L1232:
	add	x24, x29, 96
	ldr	x3, .LC83
	mov	w2, 8
	mov	w1, 0
	mov	x0, x24
	mov	w22, 0
	bl	qsort
	ldr	w23, [x27, 832]
	cbnz	w23, .L1162
	ldr	x3, .LC84
	mov	w2, 8
	mov	w1, 0
	mov	x0, x24
	mov	w28, 0
	bl	qsort
	b	.L1133
	.p2align 3
.L1166:
	mov	w23, 0
	b	.L1111
.L1128:
	ldr	x3, .LC84
	mov	w2, 8
	mov	w1, 0
	add	x0, x24, x22, uxtw 3
	mov	w28, w22
	bl	qsort
	cbnz	w22, .L1161
	b	.L1133
	.p2align 3
.L1148:
	ldr	w2, [x21, 428]
	mov	x1, x22
	add	x4, x20, 2924
	add	x3, x19, 552
	bl	MVC_GenPiclistfromFrmlist_Interview
	ldrb	w1, [x20, 2872]
	b	.L1236
.L1153:
	ldr	x1, .LC88
.L1223:
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_ClearCurrSlice
	mov	w0, -1
	b	.L1217
.L1231:
	ldr	x1, .LC86
	b	.L1223
.L1103:
	ldr	x1, .LC80
	b	.L1223
.L1169:
	mov	w3, w1
	b	.L1149
	.size	MVC_InitListX, .-MVC_InitListX
	.align	3
.LC75:
	.xword	MVC_compare_pic_by_pic_num_desc
	.align	3
.LC76:
	.xword	MVC_compare_pic_by_lt_pic_num_asc
	.align	3
.LC77:
	.xword	MVC_compare_fs_by_frame_num_desc
	.align	3
.LC78:
	.xword	MVC_compare_fs_by_lt_pic_idx_asc
	.align	3
.LC80:
	.xword	.LC79
	.align	3
.LC81:
	.xword	MVC_compare_pic_by_poc_desc
	.align	3
.LC82:
	.xword	MVC_compare_pic_by_poc_asc
	.align	3
.LC83:
	.xword	MVC_compare_fs_by_poc_desc
	.align	3
.LC84:
	.xword	MVC_compare_fs_by_poc_asc
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC88:
	.xword	.LC87
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DumpList
	.type	MVC_DumpList, %function
MVC_DumpList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC89
	ldr	w0, [x0]
	tbz	x0, 13, .L1238
	add	x24, x22, 11116544
	ldr	x23, .LC91
	mov	w20, 0
	add	x24, x24, 2920
.L1240:
	ldr	w0, [x24]
	cbz	w0, .L1243
	uxtw	x0, w20
	mov	w19, 0
	lsl	x21, x0, 5
	add	x21, x21, x0
	.p2align 2
.L1241:
	add	x4, x21, x19, uxtw
	mov	w3, w19
	add	x4, x4, 36
	mov	w2, w20
	mov	x1, x23
	mov	w0, 13
	add	w19, w19, 1
	ldr	x4, [x22, x4, lsl 3]
	ldr	x4, [x4, 8]
	ldr	w5, [x4, 32]
	ldr	w4, [x4, 20]
	bl	dprint_vfmw
	ldr	w0, [x24]
	cmp	w0, w19
	bhi	.L1241
.L1243:
	add	w20, w20, 1
	add	x24, x24, 4
	cmp	w20, 2
	bne	.L1240
.L1238:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	MVC_DumpList, .-MVC_DumpList
	.align	3
.LC89:
	.xword	g_PrintEnable
	.align	3
.LC91:
	.xword	.LC90
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindNearestPOCPicId
	.type	MVC_FindNearestPOCPicId, %function
MVC_FindNearestPOCPicId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 11124736
	ldr	w0, [x2, 828]
	cbz	w0, .L1255
	add	x1, x19, 11157504
	ldr	w0, [x2, 824]
	ldr	w7, [x1, 3348]
	cbz	w0, .L1256
	sub	w1, w0, #1
	add	x2, x2, 440
	add	x1, x1, 1388544
	mov	w6, 2147483647
	add	x1, x1, 2104
	mov	w0, 0
	add	x5, x19, x1, lsl 3
	.p2align 2
.L1254:
	ldr	x3, [x2]
	add	x2, x2, 8
	cbz	x3, .L1253
	ldr	w1, [x3, 32]
	sub	w1, w7, w1
	sxtw	x1, w1
	eor	x4, x1, x1, asr 63
	sub	x4, x4, x1, asr 63
	cmp	w4, w6
	bge	.L1253
	ldr	w0, [x3, 220]
	mov	w6, w4
.L1253:
	cmp	x2, x5
	bne	.L1254
.L1252:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1256:
	mov	w0, 0
	b	.L1252
.L1255:
	mov	w0, -1
	b	.L1252
	.size	MVC_FindNearestPOCPicId, .-MVC_FindNearestPOCPicId
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindMinRefIdx
	.type	MVC_FindMinRefIdx, %function
MVC_FindMinRefIdx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 11116544
	ldrb	w1, [x0, 2872]
	cmp	w1, 2
	beq	.L1261
	add	x1, x19, 11157504
	ldrb	w1, [x1, 2667]
	cbnz	w1, .L1291
	add	x6, x19, 11124736
	ldr	w5, [x0, 2920]
	add	x6, x6, 1064
	mov	w4, 0
	.p2align 2
.L1265:
	cbz	w5, .L1269
	add	x1, x19, 288
	mov	w3, 32
	mov	w0, 0
	b	.L1267
	.p2align 3
.L1266:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L1292
.L1267:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	x2, [x2, 8]
	ldr	w2, [x2, 52]
	cmp	w2, w4
	bne	.L1266
	cmp	w3, w0
	csel	w3, w3, w0, ls
	add	w0, w0, 1
	stp	w3, w3, [x6]
	cmp	w0, w5
	bne	.L1267
.L1292:
	cmp	w3, 31
	bhi	.L1269
.L1268:
	add	w4, w4, 1
	add	x6, x6, 8
	cmp	w4, 16
	bne	.L1265
.L1261:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1291:
	ldr	w6, [x0, 2920]
	add	x7, x19, 11124736
	add	x7, x7, 1064
	mov	w4, 0
	cbz	w6, .L1273
	.p2align 2
.L1294:
	add	x2, x19, 288
	mov	w5, 32
	mov	w1, 0
	b	.L1271
	.p2align 3
.L1270:
	add	w1, w1, 1
	cmp	w1, w6
	beq	.L1293
.L1271:
	ldr	x0, [x2]
	add	x2, x2, 8
	ldr	x3, [x0, 8]
	ldrb	w0, [x0]
	cmp	w0, 2
	ldr	w0, [x3, 52]
	cset	w3, eq
	orr	w0, w3, w0, lsl 1
	cmp	w0, w4
	bne	.L1270
	cmp	w5, w1
	csel	w5, w5, w1, ls
	add	w1, w1, 1
	str	w5, [x7]
	cmp	w1, w6
	bne	.L1271
.L1293:
	cmp	w5, 31
	bhi	.L1273
.L1272:
	add	w4, w4, 1
	add	x7, x7, 4
	cmp	w4, 32
	beq	.L1261
	cbnz	w6, .L1294
	.p2align 2
.L1273:
	str	wzr, [x7]
	b	.L1272
	.p2align 3
.L1269:
	stp	wzr, wzr, [x6]
	b	.L1268
	.size	MVC_FindMinRefIdx, .-MVC_FindMinRefIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecList
	.type	MVC_DecList, %function
MVC_DecList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11124736
	mov	w6, -1
	ldr	w0, [x1, 828]
	cbz	w0, .L1296
	add	x2, x19, 11157504
	ldr	w0, [x1, 824]
	ldr	w7, [x2, 3348]
	cbz	w0, .L1304
	add	w4, w0, w6
	add	x1, x1, 440
	add	x4, x4, 1388544
	mov	w6, 0
	add	x4, x4, 2104
	mov	w5, 2147483647
	add	x4, x19, x4, lsl 3
	.p2align 2
.L1298:
	ldr	x2, [x1]
	add	x1, x1, 8
	cbz	x2, .L1297
	ldr	w0, [x2, 32]
	sub	w0, w7, w0
	sxtw	x0, w0
	eor	x3, x0, x0, asr 63
	sub	x3, x3, x0, asr 63
	cmp	w3, w5
	bge	.L1297
	ldr	w6, [x2, 220]
	mov	w5, w3
.L1297:
	cmp	x1, x4
	bne	.L1298
.L1296:
	add	x21, x19, 11120640
	add	x0, x19, 11116544
	mov	w20, -1
	str	w6, [x21, 412]
	str	w20, [x21, 408]
	ldrb	w1, [x0, 2872]
	cmp	w1, 2
	beq	.L1312
	mov	x0, x19
	bl	MVC_InitListX
	cbnz	w0, .L1313
	mov	x0, x19
	bl	MVC_ReorderListX
	mov	x0, x19
	bl	MVC_RepairList
	cbnz	w0, .L1305
	mov	x0, x19
	bl	MVC_FindMinRefIdx
	ldr	x0, [x19, 288]
	cbz	x0, .L1302
	ldr	x0, [x0, 8]
	ldr	w20, [x0, 220]
.L1302:
	mov	w0, 0
	str	w20, [x21, 408]
.L1300:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1312:
	str	wzr, [x0, 2920]
	str	wzr, [x0, 2924]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1305:
	mov	w0, w20
	b	.L1300
.L1304:
	mov	w6, 0
	b	.L1296
.L1313:
	ldr	x1, .LC93
	mov	w0, 13
	bl	dprint_vfmw
	mov	w0, w20
	b	.L1300
	.size	MVC_DecList, .-MVC_DecList
	.align	3
.LC93:
	.xword	.LC92
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_NoPicOut
	.type	MVC_NoPicOut, %function
MVC_NoPicOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 48]
	cbz	w0, .L1321
	mov	x1, 51207
	sub	w3, w0, #1
	mov	w2, 856
	movk	x1, 0xa9, lsl 16
	add	x0, x19, 11124736
	umaddl	x2, w3, w2, x1
	add	x0, x0, 1199
	add	x2, x19, x2
	b	.L1320
	.p2align 3
.L1328:
	ldrb	w3, [x0, -2]
	cmp	w3, 1
	beq	.L1318
	add	x0, x0, 856
	cmp	x0, x2
	beq	.L1321
.L1320:
	ldrb	w1, [x0]
	cmp	w1, 1
	bne	.L1328
.L1318:
	strb	wzr, [x0, -5]
	strb	wzr, [x0, -4]
	add	x0, x0, 856
	cmp	x0, x2
	bne	.L1320
.L1321:
	ldr	w0, [x19, 52]
	cbz	w0, .L1314
	sub	w1, w0, #1
	add	x0, x19, 148
	add	x1, x1, 38
	add	x1, x19, x1, lsl 2
	.p2align 2
.L1322:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L1322
.L1314:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_NoPicOut, .-MVC_NoPicOut
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetBackPicFromVOQueue
	.type	MVC_GetBackPicFromVOQueue, %function
MVC_GetBackPicFromVOQueue:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x22, 120]
	bl	FSP_GetFspType
	cbz	w0, .L1346
.L1330:
	ldr	w0, [x22, 48]
	mov	w23, 0
	mov	w20, 856
	cbz	w0, .L1337
	.p2align 2
.L1341:
	uxtw	x1, w23
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	umull	x21, w23, w20
	add	x0, x22, x0, lsl 3
	add	x0, x0, 11124736
	add	x21, x21, 11124736
	add	x19, x21, 1808
	add	x21, x21, 1840
	add	x19, x22, x19
	add	x21, x22, x21
	strb	wzr, [x0, 1194]
	strb	wzr, [x0, 1195]
.L1335:
	ldr	x1, [x19]
	cbnz	x1, .L1347
.L1334:
	add	x19, x19, 8
	cmp	x19, x21
	bne	.L1335
	ldr	w0, [x22, 48]
	add	w23, w23, 1
	cmp	w0, w23
	bhi	.L1341
.L1337:
	ldr	w0, [x22, 52]
	cbz	w0, .L1329
	sub	w1, w0, #1
	add	x0, x22, 148
	add	x1, x1, 38
	add	x22, x22, x1, lsl 2
	.p2align 2
.L1338:
	str	wzr, [x0], 4
	cmp	x0, x22
	bne	.L1338
.L1329:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1347:
	ldr	w0, [x22, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L1334
.L1346:
	add	x0, x22, 912
	bl	ResetVoQueue
	b	.L1330
	.size	MVC_GetBackPicFromVOQueue, .-MVC_GetBackPicFromVOQueue
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_wait_vo
	.type	mvc_wait_vo, %function
mvc_wait_vo:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	mvc_wait_vo, .-mvc_wait_vo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_RoundLog2
	.type	MVC_RoundLog2, %function
MVC_RoundLog2:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mul	w2, w19, w19
	mov	w0, 0
	mov	w3, 1
	.p2align 2
.L1350:
	add	w0, w0, 1
	lsl	w1, w3, w0
	cmp	w2, w1
	bge	.L1350
	asr	w0, w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_RoundLog2, .-MVC_RoundLog2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetReRangeFlag
	.type	MVC_GetReRangeFlag, %function
MVC_GetReRangeFlag:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 11116544
	mov	x19, x1
	bl	_mcount
	mov	w0, 2240
	ldr	x3, [x20, 280]
	ldr	w1, [x22, 2888]
	ldrsb	w2, [x22, 2884]
	umull	x0, w1, w0
	cmn	w2, #1
	add	x0, x3, x0
	beq	.L1369
	cbnz	w2, .L1355
	ldrb	w1, [x20, 2]
	cmp	w1, 1
	beq	.L1370
	ldr	w0, [x0, 28]
	ldr	w1, [x20, 28]
	cmp	w1, w0
	beq	.L1357
	ldr	x1, .LC95
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1355:
	ldr	x1, .LC97
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1369:
	ldr	w0, [x0, 28]
	mov	w21, 3992
	ldr	x1, [x20, 272]
	umull	x0, w0, w21
	add	x21, x1, x0
.L1354:
	ldrb	w0, [x21, 20]
	mov	w2, 2
	ldr	w1, [x21, 3952]
	sub	w0, w2, w0
	ldr	w3, [x21, 3948]
	ldp	w6, w5, [x20, 12]
	madd	w1, w1, w0, w0
	add	w2, w3, 1
	cmp	w6, w2
	ccmp	w5, w1, 0, eq
	bne	.L1359
	add	x0, x20, 11124736
	ldr	w3, [x21, 3972]
	mov	w4, 0
	ldr	w0, [x0, 824]
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L1359
.L1360:
	ldrb	w0, [x22, 2883]
	cmp	w0, 1
	beq	.L1371
.L1364:
	ldr	w1, [x21, 3972]
	sub	w1, w1, #1
.L1363:
	ldr	w2, [x20, 44]
	mov	w0, w4
	cmp	w2, w1
	cset	w2, ne
	orr	w4, w2, w4
	str	w4, [x19]
	str	w1, [x20, 44]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1359:
	ldr	x0, .LC98
	ldr	x4, [x0]
	cbz	x4, .L1366
	ubfiz	w2, w2, 4, 12
	ubfiz	w1, w1, 4, 12
	ldr	w0, [x20, 120]
	ubfiz	w6, w6, 4, 12
	ubfiz	w5, w5, 4, 12
	strh	w2, [x29, 60]
	strh	w1, [x29, 62]
	mov	w3, 8
	strh	w6, [x29, 56]
	add	x2, x29, 56
	strh	w5, [x29, 58]
	mov	w1, 2
	blr	x4
	ldrb	w0, [x22, 2883]
	mov	w4, 1
	cmp	w0, 1
	bne	.L1364
.L1371:
	add	x0, x20, 290816
	add	x3, x20, 11051008
	add	x0, x0, 2488
	add	x3, x3, 56
	mov	w2, 0
	.p2align 2
.L1362:
	ldr	w1, [x0]
	add	x0, x0, 335872
	add	x0, x0, 308
	cmp	w1, w2
	sub	w1, w1, #1
	csel	w2, w1, w2, hi
	cmp	x0, x3
	bne	.L1362
	add	w0, w2, 1
	mov	w1, 16
	lsl	w0, w0, 1
	cmp	w0, w1
	csel	w1, w0, w1, cc
	b	.L1363
	.p2align 3
.L1357:
	add	x21, x20, 11046912
	add	x21, x21, 180
	b	.L1354
	.p2align 3
.L1370:
	ldr	w1, [x0, 28]
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x0, x0, x1
	lsl	x21, x0, 2
	sub	x21, x21, x0
	lsl	x1, x21, 6
	add	x21, x21, x1
	add	x21, x20, x21, lsl 2
	add	x21, x21, 286720
	add	x21, x21, 2612
	b	.L1354
	.p2align 3
.L1366:
	mov	w4, 1
	b	.L1360
	.size	MVC_GetReRangeFlag, .-MVC_GetReRangeFlag
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC98:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecPOC
	.type	MVC_DecPOC, %function
MVC_DecPOC:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, [x19, 248]
	mov	w4, 1
	add	x0, x19, 11116544
	ldr	w3, [x2, 2900]
	ldr	w1, [x2, 2896]
	cmp	w3, w4
	ldrb	w5, [x0, 2875]
	add	w1, w1, 4
	lsl	w1, w4, w1
	beq	.L1374
	cbz	w3, .L1375
	cmp	w3, 2
	bne	.L1372
	cmp	w5, 5
	beq	.L1429
	ldrsb	w2, [x0, 1736]
	cbz	w2, .L1408
	ldr	w3, [x0, 1792]
	mov	w2, 0
	mov	w1, 0
	str	wzr, [x0, 1788]
	str	wzr, [x0, 1800]
.L1409:
	str	w1, [x0, 1796]
.L1411:
	ldrb	w4, [x0, 2880]
	add	w1, w3, w1
	str	w1, [x0, 1784]
	lsl	w1, w1, 1
	cbnz	w4, .L1412
	sub	w1, w1, #1
	str	w1, [x0, 1772]
.L1413:
	ldrb	w3, [x0, 2873]
	cbnz	w3, .L1414
	str	w1, [x0, 1760]
	str	w1, [x0, 1764]
	str	w1, [x0, 1768]
.L1407:
	ldr	w1, [x0, 1792]
	str	w1, [x0, 1788]
	str	w2, [x0, 1800]
.L1372:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1375:
	ldr	w1, [x2, 2904]
	cmp	w5, 5
	add	w1, w1, 4
	lsl	w4, w4, w1
	beq	.L1381
	ldrsb	w1, [x0, 1736]
	cbnz	w1, .L1379
	ldr	w5, [x0, 1748]
	ldr	w3, [x0, 1752]
	mov	w2, w5
.L1380:
	ldr	w1, [x0, 1740]
	cmp	w1, w3
	bcs	.L1378
	sub	w6, w3, w1
	cmp	w6, w4, lsr 1
	bcc	.L1378
	add	w2, w2, w4
	str	w2, [x0, 1756]
.L1382:
	ldrb	w3, [x0, 2873]
	cbnz	w3, .L1384
.L1432:
	ldr	w3, [x0, 1744]
	add	w1, w1, w2
	str	w1, [x0, 1760]
	add	w2, w1, w3
	str	w2, [x0, 1764]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x0, 1772]
.L1385:
	ldr	w3, [x0, 1788]
	ldr	w2, [x0, 1792]
	str	w1, [x0, 1768]
	cmp	w2, w3
	beq	.L1387
	str	w2, [x0, 1788]
.L1387:
	ldrb	w1, [x0, 2880]
	cbz	w1, .L1372
	ldr	w2, [x0, 1740]
	ldr	w1, [x0, 1756]
	str	w1, [x0, 1748]
	str	w2, [x0, 1752]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1374:
	cmp	w5, 5
	beq	.L1430
	ldrsb	w3, [x0, 1736]
	cbz	w3, .L1390
	mov	w1, 0
	str	wzr, [x0, 1788]
	str	wzr, [x0, 1800]
.L1391:
	str	w1, [x0, 1796]
.L1389:
	ldr	w1, [x2, 2916]
	cbz	w1, .L1393
	ldr	w1, [x0, 1792]
	ldr	w5, [x0, 1796]
	ldrb	w6, [x0, 2880]
	add	w5, w5, w1
	str	w5, [x0, 1784]
	cbnz	w6, .L1395
	cbz	w5, .L1396
	sub	w5, w5, #1
	str	w5, [x0, 1784]
.L1395:
	str	wzr, [x0, 1816]
	ldr	w1, [x2, 2916]
	cmp	w1, wzr
	ble	.L1397
.L1416:
	mov	w4, 0
	mov	w3, 0
	.p2align 2
.L1398:
	add	x1, x2, x3, sxtw 2
	add	w3, w3, 1
	ldr	w1, [x1, 2920]
	add	w4, w4, w1
	str	w4, [x0, 1816]
	ldr	w1, [x2, 2916]
	cmp	w1, w3
	bgt	.L1398
.L1397:
	cbz	w5, .L1399
	sub	w5, w5, #1
	ldr	w7, [x0, 1816]
	udiv	w1, w5, w1
	str	w1, [x0, 1808]
	ldr	w4, [x2, 2916]
	udiv	w3, w5, w4
	mul	w1, w1, w7
	str	w1, [x0, 1812]
	msub	w5, w3, w4, w5
	str	w5, [x0, 1804]
	tbnz	w5, #31, .L1400
	mov	w3, 0
	.p2align 2
.L1401:
	add	x4, x2, x3, sxtw 2
	add	w3, w3, 1
	cmp	w5, w3
	ldr	w4, [x4, 2920]
	add	w1, w1, w4
	str	w1, [x0, 1812]
	bge	.L1401
.L1400:
	cbnz	w6, .L1402
	ldr	w3, [x2, 2908]
	add	w1, w1, w3
	str	w1, [x0, 1812]
.L1402:
	ldrb	w3, [x0, 2873]
	cbnz	w3, .L1403
	ldr	w3, [x0, 1776]
	ldr	w4, [x0, 1780]
	add	w1, w1, w3
	str	w1, [x0, 1760]
	ldr	w2, [x2, 2912]
	add	w2, w1, w2
	add	w2, w2, w4
	str	w2, [x0, 1764]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x0, 1772]
.L1404:
	ldr	w3, [x0, 1792]
	ldr	w2, [x0, 1796]
	str	w1, [x0, 1768]
	str	w3, [x0, 1788]
	str	w2, [x0, 1800]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1379:
	ldrsb	w1, [x0, 1737]
	cbz	w1, .L1431
.L1381:
	ldr	w1, [x0, 1740]
	mov	w2, 0
	mov	w5, 0
	str	wzr, [x0, 1748]
	str	wzr, [x0, 1752]
.L1378:
	cmp	w1, w3
	bls	.L1383
	sub	w3, w1, w3
	cmp	w3, w4, lsr 1
	bls	.L1383
	sub	w2, w2, w4
	str	w2, [x0, 1756]
	b	.L1382
	.p2align 3
.L1429:
	add	x1, x0, 1536
	mov	w2, 0
	stp	wzr, wzr, [x1, 224]
	stp	wzr, wzr, [x1, 232]
	str	wzr, [x0, 1796]
	b	.L1407
	.p2align 3
.L1430:
	str	wzr, [x0, 1796]
	b	.L1389
	.p2align 3
.L1383:
	ldrb	w3, [x0, 2873]
	str	w5, [x0, 1756]
	cbz	w3, .L1432
.L1384:
	ldrb	w3, [x0, 2874]
	add	w1, w1, w2
	cbnz	w3, .L1386
	str	w1, [x0, 1760]
	str	w1, [x0, 1772]
	b	.L1385
	.p2align 3
.L1393:
	ldrb	w6, [x0, 2880]
	str	wzr, [x0, 1784]
.L1396:
	str	wzr, [x0, 1816]
	mov	w5, 0
	ldr	w1, [x2, 2916]
	cmp	w1, wzr
	bgt	.L1416
	.p2align 2
.L1399:
	mov	w1, 0
	str	wzr, [x0, 1812]
	b	.L1400
	.p2align 3
.L1403:
	ldrb	w3, [x0, 2874]
	cbnz	w3, .L1405
	ldr	w2, [x0, 1776]
	add	w1, w1, w2
	str	w1, [x0, 1760]
	str	w1, [x0, 1772]
	b	.L1404
	.p2align 3
.L1408:
	ldr	w2, [x0, 1788]
	ldr	w3, [x0, 1792]
	cmp	w3, w2
	ldr	w2, [x0, 1800]
	bcs	.L1410
	add	w1, w1, w2
	str	w1, [x0, 1796]
	mov	w2, w1
	b	.L1411
	.p2align 3
.L1390:
	ldr	w3, [x0, 1788]
	ldr	w4, [x0, 1792]
	cmp	w4, w3
	bcs	.L1392
	ldr	w3, [x0, 1800]
	add	w1, w3, w1
	str	w1, [x0, 1796]
	b	.L1389
	.p2align 3
.L1414:
	ldrb	w3, [x0, 2874]
	str	w1, [x0, 1768]
	cbnz	w3, .L1415
	str	w1, [x0, 1760]
	b	.L1407
	.p2align 3
.L1412:
	str	w1, [x0, 1772]
	b	.L1413
	.p2align 3
.L1386:
	str	w1, [x0, 1764]
	str	w1, [x0, 1772]
	b	.L1385
	.p2align 3
.L1405:
	ldr	w3, [x2, 2912]
	ldr	w2, [x0, 1776]
	add	w1, w1, w3
	add	w1, w1, w2
	str	w1, [x0, 1764]
	str	w1, [x0, 1772]
	b	.L1404
	.p2align 3
.L1431:
	ldr	w3, [x0, 1760]
	mov	w2, 0
	mov	w5, 0
	str	wzr, [x0, 1748]
	str	w3, [x0, 1752]
	b	.L1380
	.p2align 3
.L1415:
	str	w1, [x0, 1764]
	b	.L1407
.L1392:
	ldr	w1, [x0, 1800]
	b	.L1391
.L1410:
	mov	w1, w2
	b	.L1409
	.size	MVC_DecPOC, .-MVC_DecPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CalcPicNum
	.type	MVC_CalcPicNum, %function
MVC_CalcPicNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x8, x19, 11157504
	ldr	x0, [x19, 248]
	mov	w9, 1
	add	x1, x19, 11124736
	ldr	w0, [x0, 2896]
	ldrb	w2, [x8, 2667]
	add	w0, w0, 4
	lsl	w9, w9, w0
	cbz	w2, .L1434
	ldr	w0, [x1, 832]
	cmp	w2, 1
	cset	w6, eq
	cmp	w2, 2
	cset	w7, eq
	mov	w2, 0
	cbz	w0, .L1454
	.p2align 2
.L1471:
	add	x0, x19, x2, uxtw 3
	add	x0, x0, 11124736
	ldr	x3, [x0, 568]
	ldrb	w4, [x3, 3]
	cbz	w4, .L1448
	ldr	w4, [x3, 20]
	ldr	w5, [x8, 3336]
	cmp	w4, w5
	bls	.L1449
	sub	w4, w4, w9
	str	w4, [x3, 24]
.L1450:
	ldr	x3, [x0, 568]
	ldrb	w4, [x3, 3]
	tbz	x4, 0, .L1451
	ldr	w5, [x3, 760]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L1481
.L1451:
	tbz	x4, 1, .L1448
	ldr	w0, [x3, 808]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L1482
	.p2align 2
.L1448:
	ldr	w0, [x1, 832]
	add	w2, w2, 1
	cmp	w0, w2
	bhi	.L1471
.L1454:
	ldr	w0, [x1, 836]
	mov	w2, 0
	cbz	w0, .L1433
	.p2align 2
.L1470:
	add	x0, x19, x2, uxtw 3
	add	w2, w2, 1
	add	x0, x0, 11124736
	ldr	x4, [x0, 696]
	ldrb	w3, [x4, 3]
	cbz	w3, .L1456
	tbz	x3, 0, .L1457
	ldr	w5, [x4, 760]
	and	w5, w5, 16776960
	cmp	w5, 256
	beq	.L1483
.L1457:
	tbz	x3, 1, .L1456
	ldr	w0, [x4, 808]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L1484
	.p2align 2
.L1456:
	ldr	w0, [x1, 836]
	cmp	w0, w2
	bhi	.L1470
.L1433:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1449:
	str	w4, [x3, 24]
	b	.L1450
	.p2align 3
.L1434:
	ldr	w2, [x1, 832]
	mov	w0, 0
	cbnz	w2, .L1469
	.p2align 2
.L1444:
	ldr	w0, [x1, 836]
	mov	w2, 0
	cbz	w0, .L1433
	uxtw	x0, w2
	add	w2, w2, 1
	add	x0, x0, 1388544
	add	x0, x19, x0, lsl 3
	ldr	x0, [x0, 17080]
	ldrb	w3, [x0, 3]
	cmp	w3, 3
	beq	.L1485
	.p2align 2
.L1445:
	ldr	w0, [x1, 836]
	cmp	w0, w2
	bls	.L1433
	uxtw	x0, w2
	add	w2, w2, 1
	add	x0, x0, 1388544
	add	x0, x19, x0, lsl 3
	ldr	x0, [x0, 17080]
	ldrb	w3, [x0, 3]
	cmp	w3, 3
	bne	.L1445
.L1485:
	ldr	w3, [x0, 712]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L1445
	ldr	w3, [x0, 28]
	str	w3, [x0, 728]
	b	.L1445
	.p2align 3
.L1487:
	ldr	w4, [x3, 712]
	and	w4, w4, 16776960
	cmp	w4, 65536
	bne	.L1440
	ldr	w4, [x3, 20]
	ldr	w5, [x8, 3336]
	cmp	w4, w5
	sub	w5, w4, w9
	bhi	.L1486
	str	w4, [x3, 24]
.L1442:
	ldr	x2, [x2, 568]
	ldr	w3, [x2, 24]
	str	w3, [x2, 732]
	.p2align 2
.L1440:
	ldr	w2, [x1, 832]
	add	w0, w0, 1
	cmp	w2, w0
	bls	.L1444
.L1469:
	add	x2, x19, x0, uxtw 3
	add	x2, x2, 11124736
	ldr	x3, [x2, 568]
	ldrb	w4, [x3, 3]
	cmp	w4, 3
	bne	.L1440
	b	.L1487
	.p2align 3
.L1483:
	ldr	w3, [x4, 28]
	add	w3, w6, w3, lsl 1
	str	w3, [x4, 776]
	ldr	x4, [x0, 696]
	ldrb	w3, [x4, 3]
	b	.L1457
	.p2align 3
.L1481:
	ldr	w4, [x3, 24]
	add	w4, w6, w4, lsl 1
	str	w4, [x3, 780]
	ldr	x3, [x0, 568]
	ldrb	w4, [x3, 3]
	b	.L1451
	.p2align 3
.L1484:
	ldr	w0, [x4, 28]
	add	w0, w7, w0, lsl 1
	str	w0, [x4, 824]
	b	.L1456
	.p2align 3
.L1482:
	ldr	w0, [x3, 24]
	add	w0, w7, w0, lsl 1
	str	w0, [x3, 828]
	b	.L1448
	.p2align 3
.L1486:
	str	w5, [x3, 24]
	b	.L1442
	.size	MVC_CalcPicNum, .-MVC_CalcPicNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsOutDPB
	.type	MVC_IsOutDPB, %function
MVC_IsOutDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1493
	add	x2, x20, 11124736
	ldr	w0, [x2, 824]
	cbz	w0, .L1493
	ldr	x1, [x2, 440]
	cmp	x19, x1
	ccmp	x1, xzr, 4, eq
	bne	.L1495
	sub	w0, w0, #1
	add	x2, x2, 448
	add	x0, x0, 1388544
	add	x0, x0, 2104
	add	x0, x20, x0, lsl 3
	b	.L1490
	.p2align 3
.L1491:
	ldr	x3, [x2], 8
	cmp	x19, x3
	ccmp	x3, xzr, 4, eq
	bne	.L1495
.L1490:
	cmp	x2, x0
	bne	.L1491
.L1493:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1495:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_IsOutDPB, .-MVC_IsOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_combine_scalinglist
	.type	mvc_combine_scalinglist, %function
mvc_combine_scalinglist:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	x20, x1
	bl	_mcount
	cmp	w19, wzr
	ble	.L1496
	ldr	x1, .LC101
	mov	x5, 0
	mov	w2, 255
	b	.L1500
	.p2align 3
.L1498:
	ldrb	w3, [x5, x0]
.L1499:
	lsr	w6, w3, 2
	ldr	w4, [x21, w3, uxtw 2]
	ubfiz	w7, w3, 3, 2
	add	x5, x5, 1
	lsl	w3, w2, w7
	and	w4, w4, 255
	ldr	w0, [x20, w6, uxtw 2]
	lsl	w4, w4, w7
	cmp	w19, w5
	bic	w0, w0, w3
	orr	w0, w4, w0
	str	w0, [x20, w6, uxtw 2]
	ble	.L1496
.L1500:
	cmp	w19, 16
	add	x0, x1, 16
	bne	.L1498
	ldrb	w3, [x1, x5]
	b	.L1499
	.p2align 3
.L1496:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	mvc_combine_scalinglist, .-mvc_combine_scalinglist
	.align	3
.LC101:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_assign_quant_params
	.type	mvc_assign_quant_params, %function
mvc_assign_quant_params:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cbz	x20, .L1534
	cbz	x19, .L1535
	ldrb	w0, [x19, 18]
	cbz	w0, .L1523
	ldr	x21, .LC106
	add	x0, x19, 2016
	ldr	x22, .LC103
	add	x24, x19, 5
	mov	x26, x0
	add	x25, x19, 1984
	mov	w27, 1
	mov	w28, 0
	mov	x23, x21
	str	x0, [x29, 104]
	b	.L1508
	.p2align 3
.L1538:
	cbz	w28, .L1536
	cmp	w28, 3
	beq	.L1537
	ldr	x8, .LC106
	sub	w1, w28, #1
	add	x1, x1, 126
	mov	x2, 16
	mov	x0, x26
	ldr	x8, [x8, 104]
	add	x1, x19, x1, lsl 4
	blr	x8
.L1516:
	cmp	w27, 7
	bhi	.L1523
.L1522:
	add	w28, w28, 1
	add	w27, w27, 1
	add	x24, x24, 1
	add	x26, x26, 16
	add	x25, x25, 4
.L1508:
	cmp	w28, 5
	ldrsb	w0, [x24]
	bhi	.L1509
	cbz	w0, .L1538
	ldr	w0, [x25]
	cbz	w0, .L1516
	cmp	w28, 2
	ldr	x1, .LC103
	ldr	x8, [x23, 104]
	bls	.L1517
	add	x1, x1, 16
.L1517:
	mov	x2, 16
	mov	x0, x26
	blr	x8
	cmp	w27, 7
	bls	.L1522
	.p2align 2
.L1523:
	mov	w0, 0
.L1505:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1509:
	cbnz	w0, .L1518
	ldrb	w0, [x20, 27]
	cbnz	w0, .L1519
	ldr	x1, .LC106
	sub	w0, w28, #6
	add	x0, x0, 33
	cmp	w28, 6
	ldr	x8, [x1, 104]
	add	x0, x19, x0, lsl 6
	ldr	x1, .LC103
	beq	.L1533
	add	x1, x1, 96
.L1521:
	mov	x2, 64
	blr	x8
	b	.L1516
	.p2align 3
.L1518:
	sub	w0, w28, #6
	add	x1, x19, x0, lsl 2
	ldr	w1, [x1, 2008]
	cbz	w1, .L1516
	add	x0, x0, 33
	cmp	w28, 6
	ldr	x8, [x21, 104]
	add	x0, x19, x0, lsl 6
	beq	.L1526
	add	x1, x22, 96
	b	.L1521
	.p2align 3
.L1519:
	ldr	x0, .LC106
	sub	w1, w28, #6
	mov	x2, 64
	ldr	x8, [x0, 104]
	add	x0, x1, 33
	add	x1, x20, x1, lsl 6
	add	x1, x1, 2768
	add	x0, x19, x0, lsl 6
	blr	x8
	b	.L1516
.L1534:
	ldr	x2, .LC104
	mov	w3, 6713
	ldr	x1, .LC105
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1505
.L1535:
	ldr	x2, .LC104
	mov	w3, 6714
	ldr	x1, .LC105
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1505
.L1536:
	ldrb	w0, [x20, 27]
	cbnz	w0, .L1512
	ldr	x0, .LC106
	mov	x2, 16
	ldr	x1, .LC103
	ldr	x8, [x0, 104]
	ldr	x0, [x29, 104]
	blr	x8
	b	.L1522
.L1537:
	ldrb	w0, [x20, 27]
	cbnz	w0, .L1515
	ldr	x0, .LC106
	mov	x2, 16
	ldr	x1, .LC107
	ldr	x8, [x0, 104]
	add	x0, x19, 2064
	blr	x8
	b	.L1522
.L1512:
	ldr	x0, .LC106
	mov	x2, 16
	add	x1, x20, 2672
	ldr	x8, [x0, 104]
	ldr	x0, [x29, 104]
	blr	x8
	b	.L1522
.L1515:
	ldr	x0, .LC106
	mov	x2, 16
	add	x1, x20, 2720
	ldr	x8, [x0, 104]
	add	x0, x19, 2064
	blr	x8
	b	.L1522
.L1526:
	ldr	x1, .LC103
.L1533:
	add	x1, x1, 32
	b	.L1521
	.size	mvc_assign_quant_params, .-mvc_assign_quant_params
	.align	3
.LC103:
	.xword	.LANCHOR1
	.align	3
.LC104:
	.xword	.LC36
	.align	3
.LC105:
	.xword	.LC38
	.align	3
.LC106:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC107:
	.xword	.LANCHOR1+16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_WriteCurrPicYUV
	.type	MVC_WriteCurrPicYUV, %function
MVC_WriteCurrPicYUV:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 11157504
	bl	_mcount
	ldr	x1, .LC109
	mov	w0, 2
	ldr	x3, [x19, 3320]
	ldrb	w20, [x19, 2667]
	ldr	w3, [x3, 220]
	mov	w2, w20
	bl	dprint_vfmw
	cmp	w20, 3
	ldr	w3, [x19, 3384]
	ccmp	w20, wzr, 4, ne
	ldr	w4, [x19, 3388]
	cset	w0, eq
	ldr	x1, .LC111
	cmp	w0, wzr
	mov	w2, 1
	csinc	w2, w2, w20, ne
	mov	w0, 22
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_WriteCurrPicYUV, .-MVC_WriteCurrPicYUV
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_WritePicMsg
	.type	MVC_WritePicMsg, %function
MVC_WritePicMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x23, x20, 11157504
	add	x19, x20, 11161600
	bl	_mcount
	add	x22, x20, 11108352
	ldr	x1, .LC113
	mov	w0, 2
	ldrb	w3, [x23, 2667]
	add	x25, x20, 11112448
	ldr	w4, [x23, 2828]
	ldr	w2, [x23, 3344]
	ldr	w5, [x23, 3404]
	bl	dprint_vfmw
	str	wzr, [x20, 64]
	add	x0, x20, 11116544
	ldr	x1, [x23, 3264]
	str	x1, [x19, 1216]
	ldr	x1, [x20, 864]
	str	x1, [x19, 2136]
	ldr	w1, [x23, 2792]
	str	w1, [x19, 1912]
	ldr	w1, [x23, 2796]
	str	w1, [x19, 1916]
	ldr	w1, [x23, 2816]
	str	w1, [x19, 1920]
	ldr	w1, [x23, 2820]
	str	w1, [x19, 1924]
	ldr	w1, [x23, 3344]
	str	w1, [x19, 1224]
	ldrb	w1, [x23, 2667]
	strb	w1, [x19, 1192]
	ldr	x1, [x20, 248]
	ldrb	w2, [x1, 21]
	str	w2, [x19, 1240]
	ldr	w2, [x23, 3388]
	str	w2, [x19, 1228]
	ldr	w2, [x23, 3392]
	str	w2, [x19, 1232]
	ldr	w2, [x1, 3948]
	add	w2, w2, 1
	str	w2, [x19, 1236]
	ldrb	w2, [x22, 3716]
	strb	w2, [x19, 1195]
	ldr	w2, [x25, 3652]
	str	w2, [x19, 1244]
	ldrb	w2, [x25, 3592]
	str	w2, [x19, 1248]
	ldr	w1, [x1, 748]
	strb	w1, [x19, 1193]
	ldrb	w1, [x25, 3596]
	str	w1, [x19, 1252]
	ldr	w1, [x0, 1772]
	str	w1, [x19, 1256]
	ldr	w1, [x0, 1760]
	str	w1, [x19, 1260]
	ldr	w0, [x0, 1764]
	str	w0, [x19, 1264]
	ldr	x1, [x23, 3320]
	ldr	w0, [x20, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	mov	x24, x0
	cbz	x0, .L1576
	ldp	x2, x3, [x0, 32]
	cbz	x2, .L1546
	cbz	x3, .L1546
	ldr	w0, [x20, 120]
	add	x3, x19, 1644
	add	x2, x19, 1516
	add	x1, x19, 1772
	add	x21, x20, 11124736
	bl	FSP_GetDecFsAddrTab
	ldr	x0, [x24, 32]
	add	x2, x19, 1776
	add	x1, x19, 1904
	ldr	w0, [x0, 4]
	str	w0, [x19, 1500]
	ldr	w0, [x20, 120]
	bl	FSP_GetPmvAddrTab
	ldr	w0, [x23, 3404]
	str	w0, [x19, 1508]
	ldr	w0, [x24, 12]
	str	w0, [x19, 1908]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 8]
	str	w0, [x19, 1504]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 60]
	str	w0, [x19, 1512]
	ldr	w4, [x21, 1056]
	str	w4, [x19, 2128]
	cbz	w4, .L1552
	sub	w3, w4, #1
	add	x0, x21, 864
	add	x3, x3, 2781184
	add	x1, x19, 1936
	add	x3, x3, 217
	add	x3, x20, x3, lsl 2
	.p2align 2
.L1551:
	ldr	w2, [x0]
	add	x0, x0, 4
	str	w2, [x1]
	add	x1, x1, 4
	cmp	x3, x0
	ldr	w2, [x0, 60]
	str	w2, [x1, 60]
	ldr	w2, [x0, 124]
	str	w2, [x1, 124]
	bne	.L1551
.L1552:
	ldrb	w0, [x22, 3723]
	cbnz	w0, .L1577
	ldrb	w0, [x25, 3610]
	cbnz	w0, .L1553
	ldr	x9, .LC118
	add	x5, x19, 1268
	mov	w1, 0
	.p2align 2
.L1554:
	and	w2, w1, 3
	add	x0, x9, 352
	add	w1, w1, 1
	cmp	w1, 24
	ldr	w0, [x0, w2, uxtw 2]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1554
	add	x19, x19, 1364
	mov	w5, 0
	.p2align 2
.L1555:
	add	w0, w5, 1
	and	w2, w5, 14
	add	x1, x9, 368
	and	w0, w0, 15
	add	x19, x19, 8
	add	w5, w5, 2
	cmp	w5, 32
	ldr	w0, [x1, w0, uxtw 2]
	ldr	w1, [x1, w2, uxtw 2]
	lsr	w7, w0, 16
	ubfx	x2, x0, 8, 8
	lsr	w3, w1, 16
	lsr	w6, w1, 24
	ubfiz	w10, w0, 16, 8
	ubfiz	w8, w3, 8, 8
	and	w0, w0, -16777216
	and	w3, w1, 255
	ubfx	x1, x1, 8, 8
	orr	w0, w0, w2, lsl 16
	orr	w7, w10, w7, lsl 24
	orr	w3, w8, w3
	orr	w1, w1, w6, lsl 8
	orr	w2, w7, w3
	orr	w0, w1, w0
	stp	w2, w0, [x19, -8]
	bne	.L1555
.L1561:
	mov	w22, 0
	cbz	w4, .L1557
	.p2align 2
.L1565:
	add	x19, x20, x22, uxtw 2
	ldr	w0, [x20, 120]
	add	x23, x19, 11124736
	mov	w1, 0
	add	x19, x19, 11161600
	add	w22, w22, 1
	ldr	w2, [x23, 864]
	bl	FSP_GetStoreType
	cmp	w0, wzr
	cset	w0, ne
	str	w0, [x19, 2248]
	ldr	w0, [x23, 864]
	str	w0, [x19, 2312]
	ldr	w0, [x21, 1056]
	cmp	w0, w22
	bhi	.L1565
.L1557:
	mov	w0, 0
.L1544:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1577:
	ldrb	w0, [x25, 3610]
.L1553:
	cmp	w0, 1
	add	x5, x19, 1268
	mov	w1, 0
	beq	.L1559
	.p2align 2
.L1562:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 2777088
	cmp	w1, 24
	add	x0, x0, 1592
	ldr	w0, [x20, x0, lsl 2]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1562
	add	x19, x19, 1364
	mov	w9, 1
	mov	w5, 0
	.p2align 2
.L1563:
	ubfx	x1, x5, 3, 29
	ubfiz	x0, x5, 1, 3
	and	x2, x9, 15
	lsl	x1, x1, 4
	add	x2, x1, x2
	add	x1, x1, x0
	add	x1, x1, 2777088
	add	x0, x2, 2777088
	add	x0, x0, 1616
	add	x1, x1, 1616
	add	x19, x19, 8
	add	w5, w5, 1
	cmp	w5, 16
	add	w9, w9, 2
	ldr	w0, [x20, x0, lsl 2]
	ldr	w1, [x20, x1, lsl 2]
	lsr	w3, w0, 16
	ubfx	x7, x0, 8, 8
	lsr	w8, w1, 16
	lsr	w6, w1, 24
	ubfiz	w10, w8, 8, 8
	ubfiz	w11, w0, 16, 8
	and	w8, w1, 255
	ubfx	x2, x1, 8, 8
	lsl	w6, w6, 8
	and	w1, w0, -16777216
	orr	w0, w2, w1
	orr	w8, w10, w8
	orr	w3, w11, w3, lsl 24
	orr	w6, w6, w7, lsl 16
	orr	w1, w8, w3
	orr	w0, w6, w0
	stp	w1, w0, [x19, -8]
	bne	.L1563
	b	.L1561
	.p2align 3
.L1559:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 2777088
	cmp	w1, 24
	add	x0, x20, x0, lsl 2
	ldr	w0, [x0, 9704]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1559
	add	x19, x19, 1364
	mov	w9, 1
	mov	w5, 0
	.p2align 2
.L1560:
	ubfx	x1, x5, 3, 29
	ubfiz	x0, x5, 1, 3
	and	x2, x9, 15
	lsl	x1, x1, 4
	add	x2, x1, x2
	add	x1, x1, x0
	add	x1, x1, 2777088
	add	x0, x2, 2777088
	add	x19, x19, 8
	add	w5, w5, 1
	add	x0, x20, x0, lsl 2
	add	x1, x20, x1, lsl 2
	cmp	w5, 16
	add	w9, w9, 2
	ldr	w0, [x0, 9800]
	ldr	w1, [x1, 9800]
	lsr	w8, w0, 16
	ubfx	x7, x0, 8, 8
	lsr	w3, w1, 16
	lsr	w6, w1, 24
	ubfiz	w11, w0, 16, 8
	ubfiz	w10, w3, 8, 8
	ubfx	x2, x1, 8, 8
	and	w3, w1, 255
	lsl	w6, w6, 8
	and	w1, w0, -16777216
	orr	w0, w2, w1
	orr	w8, w11, w8, lsl 24
	orr	w3, w10, w3
	orr	w6, w6, w7, lsl 16
	orr	w1, w8, w3
	orr	w0, w6, w0
	stp	w1, w0, [x19, -8]
	bne	.L1560
	b	.L1561
.L1546:
	ldr	x1, .LC117
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1544
.L1576:
	ldr	x2, [x23, 3320]
	mov	w0, 0
	ldr	x1, .LC115
	ldrsb	w2, [x2, 6]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1544
	.size	MVC_WritePicMsg, .-MVC_WritePicMsg
	.align	3
.LC113:
	.xword	.LC112
	.align	3
.LC115:
	.xword	.LC114
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC118:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_UpdatePicQpInf
	.type	MVC_UpdatePicQpInf, %function
MVC_UpdatePicQpInf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldp	w1, w0, [x19, 36]
	cmp	w1, w20
	csel	w1, w1, w20, ge
	cmp	w0, w20
	csel	w0, w0, w20, le
	stp	w1, w0, [x19, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_UpdatePicQpInf, .-MVC_UpdatePicQpInf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_WriteSliceMsg
	.type	MVC_WriteSliceMsg, %function
MVC_WriteSliceMsg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w5, [x19, 64]
	ldr	w1, [x19, 32]
	add	w0, w5, 1
	ldr	x6, [x19, 864]
	uxtw	x21, w5
	sub	w1, w1, #1
	lsl	x4, x21, 7
	cmp	w5, w1
	sub	x4, x4, x21
	str	w0, [x19, 64]
	lsl	x4, x4, 5
	add	x22, x6, x4
	bcs	.L1580
	lsl	x1, x0, 7
	sub	x0, x1, x0
	add	x0, x6, x0, lsl 5
	str	x0, [x22, 4056]
.L1581:
	ldr	x3, [x19, 240]
	ldrb	w2, [x3]
	ldr	w0, [x3, 76]
	cmp	w2, 1
	ccmp	w2, w0, 2, ls
	bcs	.L1582
	.p2align 2
.L1583:
	uxtw	x0, w2
	add	w2, w2, 1
	lsl	x1, x0, 5
	add	x3, x3, x1
	add	x0, x22, x0, lsl 2
	ldr	w3, [x3, 28]
	str	w3, [x0, 16]
	ldr	x3, [x19, 240]
	add	x3, x3, x1
	ldr	w3, [x3, 24]
	str	w3, [x0, 8]
	ldr	x3, [x19, 240]
	add	x1, x3, x1
	ldr	w1, [x1, 32]
	str	w1, [x0, 24]
	ldr	x3, [x19, 240]
	ldr	w0, [x3, 76]
	cmp	w0, w2
	ccmp	w2, 1, 2, hi
	bls	.L1583
.L1582:
	cmp	w0, 1
	bhi	.L1588
	.p2align 2
.L1659:
	add	x1, x22, x0, uxtw 2
	add	w0, w0, 1
	cmp	w0, 2
	str	wzr, [x1, 8]
	str	wzr, [x1, 16]
	str	wzr, [x1, 24]
	bne	.L1659
.L1588:
	add	x20, x19, 11157504
	add	x23, x19, 11112448
	add	x1, x19, 11120640
	ldrb	w0, [x20, 2673]
	strb	w0, [x22, 1]
	ldr	w0, [x23, 3640]
	add	w2, w0, 26
	ldr	w0, [x1, 392]
	add	w0, w2, w0
	str	w0, [x22, 32]
	cbnz	w5, .L1684
	ldr	x2, [x20, 3320]
	str	w0, [x2, 748]
	ldr	x0, [x20, 3320]
	ldr	w2, [x22, 32]
	str	w2, [x0, 752]
.L1589:
	ldr	w0, [x1, 388]
	add	x27, x19, 11116544
	str	w0, [x22, 36]
	ldr	w0, [x27, 2936]
	str	w0, [x22, 40]
	ldr	w0, [x27, 2932]
	str	w0, [x22, 44]
	ldrb	w0, [x27, 2872]
	strb	w0, [x6, x4]
	ldr	w0, [x27, 2928]
	str	w0, [x22, 48]
	ldrb	w0, [x27, 2878]
	strb	w0, [x22, 2]
	ldr	x0, [x19, 248]
	ldrb	w0, [x0, 22]
	strb	w0, [x22, 3]
	ldr	w0, [x27, 2920]
	str	w0, [x22, 52]
	ldr	w0, [x27, 2924]
	str	w0, [x22, 56]
	ldrb	w0, [x27, 2872]
	cmp	w0, 1
	beq	.L1685
	cbz	w0, .L1686
	strb	wzr, [x22, 4]
.L1591:
	ldr	w0, [x23, 3644]
	str	w0, [x22, 60]
	ldr	w0, [x23, 3648]
	str	w0, [x22, 64]
	ldr	w0, [x1, 400]
	str	w0, [x22, 68]
	ldr	w0, [x1, 404]
	str	w0, [x22, 72]
	ldr	w0, [x1, 396]
	str	w0, [x22, 76]
	ldrb	w0, [x27, 2872]
	cmp	w0, 2
	beq	.L1630
	ldr	w0, [x27, 2920]
	cbz	w0, .L1633
	ldr	x1, [x19, 288]
	ldr	x1, [x1, 8]
	ldrb	w2, [x1, 1]
	cbz	w2, .L1596
	sub	w3, w0, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1598
	.p2align 3
.L1600:
	ldr	x1, [x0, 296]
	add	x0, x0, 8
	ldr	x1, [x1, 8]
	ldrb	w2, [x1, 1]
	cbz	w2, .L1596
.L1598:
	cmp	x3, x0
	bne	.L1600
.L1633:
	mov	w24, 0
.L1595:
	ldr	w0, [x27, 2924]
	cbz	w0, .L1634
	ldr	x1, [x19, 552]
	ldr	x1, [x1, 8]
	ldrb	w2, [x1, 1]
	cbz	w2, .L1602
	sub	w3, w0, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1604
	.p2align 3
.L1606:
	ldr	x1, [x0, 560]
	add	x0, x0, 8
	ldr	x1, [x1, 8]
	ldrb	w2, [x1, 1]
	cbz	w2, .L1602
.L1604:
	cmp	x3, x0
	bne	.L1606
.L1634:
	mov	w25, 0
.L1601:
	ldrb	w0, [x20, 2667]
	cbz	w0, .L1607
	ldr	w0, [x27, 2920]
	mov	w28, 0
	cbnz	w0, .L1658
	b	.L1623
	.p2align 3
.L1688:
	cbz	x0, .L1640
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1619:
	lsl	x0, x20, 5
	add	x0, x0, x20, lsl 2
	add	x0, x22, x0
	str	w1, [x0, 1640]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 52]
	str	w1, [x0, 1644]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 32]
	str	w1, [x0, 1632]
	ldr	x1, [x26, 288]
	ldrb	w1, [x1]
	strb	w1, [x0, 1624]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 712]
	strb	w1, [x0, 1626]
	ldr	x1, [x26, 288]
	ldrb	w1, [x1]
	cmp	w1, 1
	beq	.L1687
	strb	w1, [x0, 1630]
	add	w28, w28, 1
	ldr	x1, [x26, 288]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1631]
	ldr	x1, [x26, 288]
	ldr	w1, [x1, 24]
	str	w1, [x0, 1656]
	ldr	w0, [x27, 2920]
	cmp	w0, w28
	bls	.L1623
.L1658:
	uxtw	x20, w28
	ldr	w0, [x19, 120]
	add	x26, x19, x20, lsl 3
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	ldr	x2, [x26, 288]
	lsl	x1, x20, 5
	add	x1, x1, x20, lsl 2
	add	x1, x22, x1
	ldr	x2, [x2, 8]
	ldr	w2, [x2, 48]
	str	w2, [x1, 1636]
	ldr	x2, [x26, 288]
	ldr	x2, [x2, 8]
	ldrb	w2, [x2, 2]
	strb	w2, [x1, 1625]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 1]
	cmp	w1, 1
	bne	.L1688
	mov	w1, w24
	b	.L1619
	.p2align 3
.L1580:
	str	xzr, [x22, 4056]
	b	.L1581
	.p2align 3
.L1684:
	ldr	x2, [x20, 3320]
	ldr	w3, [x2, 748]
	cmp	w3, w0
	csel	w3, w3, w0, ge
	str	w3, [x2, 748]
	ldr	w3, [x2, 752]
	cmp	w3, w0
	csel	w0, w3, w0, le
	str	w0, [x2, 752]
	b	.L1589
	.p2align 3
.L1686:
	ldrb	w0, [x23, 3594]
	strb	w0, [x22, 4]
	b	.L1591
	.p2align 3
.L1687:
	strb	w1, [x0, 1628]
	add	w28, w28, 1
	ldr	x1, [x26, 288]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1629]
	ldr	x1, [x26, 288]
	ldr	w1, [x1, 24]
	str	w1, [x0, 1652]
	ldr	w0, [x27, 2920]
	cmp	w0, w28
	bhi	.L1658
.L1623:
	ldrb	w0, [x27, 2872]
	cmp	w0, 1
	beq	.L1689
.L1610:
	add	x1, x19, 11124736
	add	x0, x22, 3928
	add	x1, x1, 1064
	add	x3, x22, 4056
	.p2align 2
.L1616:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L1616
	add	x0, x19, 11161600
	ldrb	w1, [x23, 3594]
	str	w1, [x0, 1492]
	ldr	w2, [x23, 3636]
	str	w2, [x0, 1496]
	cbz	w1, .L1628
	ldrb	w0, [x27, 2872]
	cbnz	w0, .L1628
.L1629:
	ldr	w0, [x27, 2940]
	mov	w2, 0
	str	w0, [x22, 80]
	ldr	w0, [x27, 2944]
	str	w0, [x22, 84]
	.p2align 2
.L1631:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x19, x0
	add	x0, x22, x0
	add	x1, x1, 11116544
	ldr	w3, [x1, 2948]
	str	w3, [x0, 88]
	ldr	w3, [x1, 3076]
	str	w3, [x0, 216]
	ldr	w3, [x1, 3204]
	str	w3, [x0, 344]
	ldr	w3, [x1, 3716]
	str	w3, [x0, 856]
	ldr	w3, [x1, 3844]
	str	w3, [x0, 984]
	ldr	w1, [x1, 3972]
	str	w1, [x0, 1112]
	ldr	w0, [x27, 2932]
	cmp	w0, w2
	bcs	.L1631
	ldrb	w0, [x27, 2872]
	cmp	w0, 1
	beq	.L1690
	.p2align 2
.L1630:
	add	x21, x21, 1392640
	ldr	x0, [x19, 240]
	add	x21, x19, x21, lsl 3
	str	x0, [x21, 20584]
	str	xzr, [x19, 240]
.L1579:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1640:
	mov	w1, 0
	b	.L1619
	.p2align 3
.L1596:
	ldrsb	w1, [x1, 6]
	ldr	w0, [x19, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L1691
	ldr	x0, [x0, 32]
	ldr	w24, [x0, 4]
	b	.L1595
	.p2align 3
.L1628:
	cmp	w2, 1
	bne	.L1630
	ldrb	w0, [x27, 2872]
	cmp	w0, 1
	bne	.L1630
	b	.L1629
	.p2align 3
.L1607:
	ldr	w0, [x27, 2920]
	mov	w28, 0
	cbnz	w0, .L1657
	b	.L1615
	.p2align 3
.L1692:
	cbz	x0, .L1636
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1613:
	lsl	x0, x20, 5
	add	w28, w28, 1
	add	x0, x0, x20, lsl 2
	add	x0, x22, x0
	str	w1, [x0, 1640]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 52]
	str	w1, [x0, 1644]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 32]
	str	w1, [x0, 1632]
	ldr	x1, [x26, 288]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1627]
	ldr	x1, [x26, 288]
	ldrb	w1, [x1]
	strb	w1, [x0, 1626]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 736]
	str	w1, [x0, 1648]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 784]
	str	w1, [x0, 1652]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 832]
	str	w1, [x0, 1656]
	strb	wzr, [x0, 1624]
	ldr	w0, [x27, 2920]
	cmp	w0, w28
	bls	.L1615
.L1657:
	uxtw	x20, w28
	ldr	w0, [x19, 120]
	add	x26, x19, x20, lsl 3
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	ldr	x2, [x26, 288]
	lsl	x1, x20, 5
	add	x1, x1, x20, lsl 2
	add	x1, x22, x1
	ldr	x2, [x2, 8]
	ldr	w2, [x2, 48]
	str	w2, [x1, 1636]
	ldr	x2, [x26, 288]
	ldr	x2, [x2, 8]
	ldrb	w2, [x2, 2]
	strb	w2, [x1, 1625]
	ldr	x1, [x26, 288]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 1]
	cmp	w1, 1
	bne	.L1692
	mov	w1, w24
	b	.L1613
	.p2align 3
.L1636:
	mov	w1, 0
	b	.L1613
	.p2align 3
.L1615:
	ldrb	w0, [x27, 2872]
	cmp	w0, 1
	bne	.L1610
	ldr	w0, [x27, 2924]
	cbz	w0, .L1610
	mov	w26, 0
	b	.L1618
	.p2align 3
.L1693:
	cbz	x0, .L1638
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1617:
	lsl	x0, x20, 5
	add	w26, w26, 1
	add	x0, x0, x20, lsl 2
	add	x0, x22, x0
	str	w1, [x0, 1640]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 52]
	str	w1, [x0, 2796]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 32]
	str	w1, [x0, 2784]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2779]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1]
	strb	w1, [x0, 2778]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 736]
	str	w1, [x0, 2800]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 784]
	str	w1, [x0, 2804]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 832]
	str	w1, [x0, 2808]
	strb	wzr, [x0, 2776]
	ldr	w0, [x27, 2924]
	cmp	w0, w26
	bls	.L1610
.L1618:
	uxtw	x20, w26
	ldr	w0, [x19, 120]
	add	x24, x19, x20, lsl 3
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w2, [x1, 48]
	lsl	x1, x20, 5
	add	x1, x1, x20, lsl 2
	add	x1, x22, x1
	str	w2, [x1, 2788]
	ldr	x2, [x24, 552]
	ldr	x2, [x2, 8]
	ldrb	w2, [x2, 2]
	strb	w2, [x1, 2777]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 1]
	cmp	w1, 1
	bne	.L1693
	mov	w1, w25
	b	.L1617
	.p2align 3
.L1602:
	ldrsb	w1, [x1, 6]
	ldr	w0, [x19, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L1694
	ldr	x0, [x0, 32]
	ldr	w25, [x0, 4]
	b	.L1601
	.p2align 3
.L1685:
	ldr	w0, [x23, 3636]
	strb	w0, [x22, 4]
	b	.L1591
.L1690:
	mov	w2, 0
	.p2align 2
.L1632:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x19, x0
	add	x0, x22, x0
	add	x3, x1, 11116544
	add	x1, x1, 11120640
	ldr	w4, [x3, 3332]
	str	w4, [x0, 472]
	ldr	w4, [x3, 3460]
	str	w4, [x0, 600]
	ldr	w3, [x3, 3588]
	str	w3, [x0, 728]
	ldr	w3, [x1, 4]
	str	w3, [x0, 1240]
	ldr	w3, [x1, 132]
	str	w3, [x0, 1368]
	ldr	w1, [x1, 260]
	str	w1, [x0, 1496]
	ldr	w0, [x27, 2936]
	cmp	w0, w2
	bcs	.L1632
	b	.L1630
.L1638:
	mov	w1, 0
	b	.L1617
.L1689:
	ldr	w0, [x27, 2924]
	cbz	w0, .L1610
	mov	w26, 0
	b	.L1627
	.p2align 3
.L1696:
	cbz	x0, .L1642
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1624:
	lsl	x0, x20, 5
	add	x0, x0, x20, lsl 2
	add	x0, x22, x0
	str	w1, [x0, 2792]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 52]
	str	w1, [x0, 2796]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldr	w1, [x1, 32]
	str	w1, [x0, 2784]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1]
	strb	w1, [x0, 2776]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 712]
	strb	w1, [x0, 2778]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1]
	cmp	w1, 1
	beq	.L1695
	strb	w1, [x0, 2782]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2783]
	ldr	x1, [x24, 552]
	ldr	w1, [x1, 24]
	str	w1, [x0, 2808]
.L1626:
	ldr	w0, [x27, 2924]
	add	w26, w26, 1
	cmp	w0, w26
	bls	.L1610
.L1627:
	uxtw	x20, w26
	ldr	w0, [x19, 120]
	add	x24, x19, x20, lsl 3
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	ldr	x2, [x24, 552]
	lsl	x1, x20, 5
	add	x1, x1, x20, lsl 2
	add	x1, x22, x1
	ldr	x2, [x2, 8]
	ldr	w2, [x2, 48]
	str	w2, [x1, 2788]
	ldr	x2, [x24, 552]
	ldr	x2, [x2, 8]
	ldrb	w2, [x2, 2]
	strb	w2, [x1, 2777]
	ldr	x1, [x24, 552]
	ldr	x1, [x1, 8]
	ldrb	w1, [x1, 1]
	cmp	w1, 1
	bne	.L1696
	mov	w1, w25
	b	.L1624
	.p2align 3
.L1695:
	strb	w1, [x0, 2780]
	ldr	x1, [x24, 552]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2781]
	ldr	x1, [x24, 552]
	ldr	w1, [x1, 24]
	str	w1, [x0, 2804]
	b	.L1626
.L1642:
	mov	w1, 0
	b	.L1624
.L1691:
	ldr	x2, .LC121
	mov	w3, 7724
	ldr	x1, .LC123
	add	x2, x2, 80
	bl	dprint_vfmw
	b	.L1579
.L1694:
	ldr	x2, .LC121
	mov	w3, 7745
	ldr	x1, .LC123
	add	x2, x2, 80
	bl	dprint_vfmw
	b	.L1579
	.size	MVC_WriteSliceMsg, .-MVC_WriteSliceMsg
	.align	3
.LC121:
	.xword	.LANCHOR0
	.align	3
.LC123:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetPicStreamSize
	.type	MVC_GetPicStreamSize, %function
MVC_GetPicStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 11161600
	bl	_mcount
	mov	w0, 0
	ldr	x2, [x19, 2136]
	cbz	x2, .L1698
	.p2align 2
.L1699:
	ldp	w3, w1, [x2, 8]
	ldr	x2, [x2, 4056]
	add	w1, w3, w1
	add	w1, w1, 7
	add	w0, w0, w1, lsr 3
	cbnz	x2, .L1699
.L1698:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_GetPicStreamSize, .-MVC_GetPicStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SliceCheck
	.type	MVC_SliceCheck, %function
MVC_SliceCheck:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11116544
	bl	_mcount
	ldr	x1, .LC125
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x21, 2928]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L1712
	mov	w1, 262143
	cmp	w0, w1
	bhi	.L1713
	ldp	w1, w2, [x19, 12]
	mul	w1, w1, w2
	sub	w1, w1, #1
	cmp	w0, w1
	bhi	.L1712
	ldr	x1, .LC129
	mov	x0, x19
	bl	mvc_ue_v
	mov	w2, w0
	ldr	x1, .LC131
	mov	w20, w0
	mov	w0, 19
	bl	dprint_vfmw
	ldrb	w0, [x19, 10]
	cbnz	w0, .L1712
	cmp	w20, 9
	bls	.L1714
	ldr	x1, .LC134
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
.L1712:
	mov	w0, -1
.L1704:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1714:
	ldr	x0, .LC132
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx1709
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1709:
	.section	.rodata
	.align	0
	.align	2
.L1709:
	.byte	(.L1708 - .Lrtx1709) / 4
	.byte	(.L1710 - .Lrtx1709) / 4
	.byte	(.L1711 - .Lrtx1709) / 4
	.byte	(.L1708 - .Lrtx1709) / 4
	.byte	(.L1711 - .Lrtx1709) / 4
	.byte	(.L1708 - .Lrtx1709) / 4
	.byte	(.L1710 - .Lrtx1709) / 4
	.byte	(.L1711 - .Lrtx1709) / 4
	.byte	(.L1708 - .Lrtx1709) / 4
	.byte	(.L1711 - .Lrtx1709) / 4
	.text
	.p2align 3
.L1708:
	strb	wzr, [x21, 2872]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1711:
	mov	w1, 2
	strb	w1, [x21, 2872]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1710:
	mov	w1, 1
	strb	w1, [x21, 2872]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1713:
	ldr	x1, .LC127
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1704
	.size	MVC_SliceCheck, .-MVC_SliceCheck
	.align	3
.LC125:
	.xword	.LC124
	.align	3
.LC127:
	.xword	.LC126
	.align	3
.LC129:
	.xword	.LC128
	.align	3
.LC131:
	.xword	.LC130
	.align	3
.LC132:
	.xword	.L1709
	.align	3
.LC134:
	.xword	.LC133
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PPSSPSCheck
	.type	MVC_PPSSPSCheck, %function
MVC_PPSSPSCheck:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11116544
	bl	_mcount
	ldr	x1, .LC136
	mov	w0, 19
	ldr	w2, [x19, 2888]
	bl	dprint_vfmw
	ldr	w2, [x19, 2888]
	mov	w0, 2240
	ldr	x3, [x20, 280]
	umull	x0, w2, w0
	add	x3, x3, x0
	ldrb	w0, [x3, 19]
	cbz	w0, .L1725
	ldrsb	w19, [x19, 2884]
	cmn	w19, #1
	beq	.L1726
	cbnz	w19, .L1720
	ldr	w2, [x3, 28]
	uxtw	x1, w2
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x0, x0, x1
	lsl	x1, x0, 2
	sub	x1, x1, x0
	lsl	x0, x1, 6
	add	x1, x1, x0
	lsl	x1, x1, 2
	add	x0, x20, x1
	add	x1, x1, 286720
	add	x4, x0, 12288
	add	x1, x20, x1
	add	x1, x1, 2612
	ldrb	w4, [x4, 2396]
	cbz	w4, .L1721
	add	x0, x0, 286720
	ldrb	w0, [x0, 2637]
	cbz	w0, .L1721
.L1719:
	mov	w0, 0
	stp	x1, x3, [x20, 256]
.L1717:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1726:
	ldr	w2, [x3, 28]
	mov	w1, 3992
	ldr	x0, [x20, 272]
	umull	x1, w2, w1
	add	x1, x0, x1
	ldrb	w0, [x1, 25]
	cbnz	w0, .L1719
	ldr	x1, .LC140
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w19
	b	.L1717
	.p2align 3
.L1721:
	ldr	x1, .LC142
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1717
	.p2align 3
.L1725:
	ldr	x1, .LC138
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1717
	.p2align 3
.L1720:
	ldr	x1, .LC143
	mov	w2, w19
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1717
	.size	MVC_PPSSPSCheck, .-MVC_PPSSPSCheck
	.align	3
.LC136:
	.xword	.LC135
	.align	3
.LC138:
	.xword	.LC137
	.align	3
.LC140:
	.xword	.LC139
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC143:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PPSSPSCheckTmpId
	.type	MVC_PPSSPSCheckTmpId, %function
MVC_PPSSPSCheckTmpId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x1, .LC145
	mov	w2, w20
	mov	w0, 19
	bl	dprint_vfmw
	mov	w0, 2240
	ldr	x1, [x19, 280]
	umull	x0, w20, w0
	add	x0, x1, x0
	ldrb	w1, [x0, 19]
	cbz	w1, .L1733
	ldr	w1, [x19, 36]
	ldr	w2, [x0, 28]
	sub	w0, w1, #1
	cmp	w2, w0
	bhi	.L1734
	add	x1, x19, 11116544
	mov	w0, 0
	ldrsb	w20, [x1, 2884]
	cmn	w20, #1
	beq	.L1735
.L1729:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1735:
	mov	w1, 3992
	ldr	x3, [x19, 272]
	umull	x1, w2, w1
	add	x1, x3, x1
	ldrb	w1, [x1, 25]
	cbnz	w1, .L1729
	ldr	x1, .LC151
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w20
	b	.L1729
	.p2align 3
.L1733:
	ldr	x1, .LC147
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1729
	.p2align 3
.L1734:
	ldr	x1, .LC149
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1729
	.size	MVC_PPSSPSCheckTmpId, .-MVC_PPSSPSCheckTmpId
	.align	3
.LC145:
	.xword	.LC144
	.align	3
.LC147:
	.xword	.LC146
	.align	3
.LC149:
	.xword	.LC148
	.align	3
.LC151:
	.xword	.LC150
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsNewPic
	.type	MVC_IsNewPic, %function
MVC_IsNewPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11120640
	add	x3, x19, 11116544
	ldr	x4, [x19, 248]
	ldr	w5, [x3, 2888]
	ldr	w8, [x1, 444]
	ldr	w6, [x1, 440]
	ldr	w2, [x4, 744]
	cmp	w8, w5
	ldr	w0, [x3, 2900]
	ldr	w7, [x1, 448]
	ccmp	w6, w2, 0, eq
	ldrb	w5, [x1, 432]
	cset	w2, ne
	ldrb	w6, [x3, 2873]
	cmp	w7, w0
	ccmp	w5, w6, 0, eq
	cset	w0, ne
	cmp	w6, wzr
	ccmp	w5, wzr, 4, ne
	orr	w0, w2, w0
	beq	.L1738
	ldrb	w2, [x3, 2874]
	ldrb	w5, [x1, 433]
	cmp	w5, w2
	cset	w2, ne
	orr	w0, w0, w2
.L1738:
	ldrb	w2, [x1, 435]
	ldrb	w5, [x3, 2880]
	cmp	w2, w5
	beq	.L1744
	cmp	w5, wzr
	ccmp	w2, wzr, 4, ne
	cset	w7, eq
.L1739:
	ldrb	w6, [x1, 434]
	ldrb	w5, [x3, 2875]
	cmp	w6, w5
	cset	w2, ne
	cmp	w6, 5
	ccmp	w5, 5, 0, eq
	orr	w0, w2, w0
	orr	w2, w0, w7
	beq	.L1751
.L1740:
	ldr	w0, [x4, 2900]
	cbnz	w0, .L1741
	ldr	w6, [x1, 456]
	ldr	w5, [x3, 1740]
	ldr	w0, [x3, 1744]
	ldr	w4, [x1, 460]
	cmp	w6, w5
	ccmp	w4, w0, 0, eq
	cset	w0, ne
	orr	w2, w2, w0
.L1742:
	ldrb	w0, [x3, 2883]
	cbz	w0, .L1743
	ldr	w4, [x1, 416]
	ldr	w5, [x1, 476]
	ldrb	w6, [x1, 436]
	ldrb	w0, [x3, 2881]
	cmp	w5, w4
	ldrb	w5, [x1, 437]
	cset	w1, ne
	ldrb	w4, [x3, 2882]
	cmp	w6, w0
	cset	w0, ne
	cmp	w5, w4
	orr	w0, w1, w0
	cset	w1, ne
	orr	w0, w1, w0
	orr	w2, w2, w0
.L1743:
	ldr	w3, [x3, 2928]
	mov	w0, 19
	ldr	x1, .LC153
	cmp	w3, wzr
	cset	w19, eq
	orr	w19, w19, w2
	mov	w2, w19
	bl	dprint_vfmw
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1741:
	cmp	w0, 1
	bne	.L1742
	ldr	w6, [x1, 464]
	ldr	w5, [x3, 1776]
	ldr	w0, [x3, 1780]
	ldr	w4, [x1, 468]
	cmp	w6, w5
	ccmp	w4, w0, 0, eq
	cset	w0, ne
	orr	w2, w2, w0
	b	.L1742
	.p2align 3
.L1744:
	mov	w7, 0
	b	.L1739
	.p2align 3
.L1751:
	ldr	w0, [x3, 2916]
	ldr	w5, [x1, 452]
	cmp	w5, w0
	cset	w0, ne
	orr	w2, w2, w0
	b	.L1740
	.size	MVC_IsNewPic, .-MVC_IsNewPic
	.align	3
.LC153:
	.xword	.LC152
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_ref_pic_list_reordering
	.type	mvc_ref_pic_list_reordering, %function
mvc_ref_pic_list_reordering:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 11116544
	mov	w21, 3
	bl	_mcount
	mov	w22, 1
	ldr	x0, [x19, 256]
	mov	w2, 5
	ldrb	w3, [x20, 2883]
	ldrb	w1, [x20, 2873]
	strb	wzr, [x20, 1820]
	cmp	w3, wzr
	strb	wzr, [x20, 1821]
	csel	w21, w21, w2, eq
	ldr	w0, [x0, 2896]
	cbz	w1, .L1754
	add	w0, w0, w2
	lsl	w22, w22, w0
	ldrb	w0, [x20, 2872]
	cmp	w0, 1
	bls	.L1807
.L1806:
	ldrb	w3, [x19, 10]
.L1773:
	cmp	w3, wzr
	csetm	w0, ne
.L1805:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1754:
	add	w0, w0, 4
	lsl	w22, w22, w0
	ldrb	w0, [x20, 2872]
	cmp	w0, 1
	bhi	.L1806
.L1807:
	ldr	x1, .LC155
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 1820]
	cbz	w0, .L1763
	ldr	w0, [x20, 2932]
	cmn	w0, #2
	beq	.L1789
	ldr	x23, .LC157
	mov	w28, 0
	ldr	x26, .LC167
	ldr	x25, .LC165
	ldr	x24, .LC161
	b	.L1770
	.p2align 3
.L1764:
	cmp	w0, 2
	beq	.L1808
	sub	w0, w0, #4
	cmp	w0, 1
	bls	.L1809
.L1767:
	ldr	w0, [x20, 2932]
	add	w28, w28, 1
	add	w0, w0, 2
	cmp	w0, w28
	bls	.L1810
.L1770:
	add	x27, x19, x28, uxtw 2
	mov	x1, x23
	add	x27, x27, 11116544
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w21, w0
	str	w0, [x27, 1824]
	ldrb	w3, [x19, 10]
	bcc	.L1760
	cbnz	w3, .L1760
	cmp	w0, 3
	beq	.L1763
	cmp	w0, 1
	bhi	.L1764
	mov	x1, x24
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x27, 2088]
	cmp	w22, w0
	ldrb	w3, [x19, 10]
	bls	.L1766
	cbz	w3, .L1767
.L1766:
	ldr	x1, .LC163
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1805
	.p2align 3
.L1763:
	ldrb	w0, [x20, 2872]
	cmp	w0, 1
	bne	.L1806
	ldr	x1, .LC171
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 1821]
	cbz	w0, .L1806
	ldr	w0, [x20, 2936]
	cmn	w0, #2
	beq	.L1806
	ldr	x23, .LC173
	mov	w27, 0
	ldr	x26, .LC183
	ldr	x25, .LC181
	ldr	x24, .LC177
	b	.L1786
	.p2align 3
.L1779:
	cmp	w0, 2
	beq	.L1811
	sub	w0, w0, #4
	cmp	w0, 1
	bls	.L1812
	ldr	w0, [x20, 2936]
	add	w0, w0, 2
	cmp	w27, w0
	beq	.L1787
.L1785:
	add	w27, w27, 1
	cmp	w27, w0
	bcs	.L1806
.L1786:
	add	x28, x19, x27, uxtw 2
	mov	x1, x23
	add	x28, x28, 11116544
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w21, w0
	str	w0, [x28, 1956]
	ldrb	w3, [x19, 10]
	bcc	.L1777
	cbnz	w3, .L1777
	cmp	w0, 3
	beq	.L1773
	cmp	w0, 1
	bhi	.L1779
	mov	x1, x24
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x28, 2220]
	cmp	w22, w0
	ldrb	w3, [x19, 10]
	bls	.L1781
	cbnz	w3, .L1781
.L1782:
	ldr	w0, [x20, 2936]
	add	w0, w0, 2
	cmp	w0, w27
	bne	.L1785
	ldr	w1, [x28, 1956]
	cmp	w1, 3
	beq	.L1785
.L1787:
	ldr	x1, .LC185
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1805
	.p2align 3
.L1808:
	mov	x1, x25
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x27, 2352]
	b	.L1767
	.p2align 3
.L1811:
	mov	x1, x25
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x28, 2480]
	b	.L1782
	.p2align 3
.L1809:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x27, 2608]
	b	.L1767
	.p2align 3
.L1812:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x28, 2740]
	b	.L1782
	.p2align 3
.L1760:
	ldr	x1, .LC159
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1805
	.p2align 3
.L1777:
	ldr	x1, .LC175
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1805
	.p2align 3
.L1810:
	bne	.L1763
.L1758:
	uxtw	x0, w28
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 10016]
	cmp	w0, 3
	beq	.L1763
	ldr	x1, .LC169
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1805
.L1781:
	ldr	x1, .LC179
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1805
.L1789:
	mov	w28, 0
	b	.L1758
	.size	mvc_ref_pic_list_reordering, .-mvc_ref_pic_list_reordering
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC157:
	.xword	.LC156
	.align	3
.LC159:
	.xword	.LC158
	.align	3
.LC161:
	.xword	.LC160
	.align	3
.LC163:
	.xword	.LC162
	.align	3
.LC165:
	.xword	.LC164
	.align	3
.LC167:
	.xword	.LC166
	.align	3
.LC169:
	.xword	.LC168
	.align	3
.LC171:
	.xword	.LC170
	.align	3
.LC173:
	.xword	.LC172
	.align	3
.LC175:
	.xword	.LC174
	.align	3
.LC177:
	.xword	.LC176
	.align	3
.LC179:
	.xword	.LC178
	.align	3
.LC181:
	.xword	.LC180
	.align	3
.LC183:
	.xword	.LC182
	.align	3
.LC185:
	.xword	.LC184
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_pred_weight_table
	.type	mvc_pred_weight_table, %function
mvc_pred_weight_table:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	add	x20, x28, 11116544
	mov	w19, 1
	bl	_mcount
	mov	w24, 0
	ldp	x21, x2, [x28, 256]
	ldr	x1, .LC187
	mov	x0, x28
	str	x2, [x29, 104]
	bl	mvc_ue_v
	str	w0, [x20, 2940]
	lsl	w23, w19, w0
	ldr	w1, [x21, 748]
	cbnz	w1, .L1838
.L1814:
	cmp	w0, 7
	bhi	.L1817
	ldr	w0, [x20, 2944]
	cmp	w0, 7
	bhi	.L1817
	ldrb	w2, [x28, 10]
	cbnz	w2, .L1816
	ldr	x22, .LC193
	mov	w25, 0
	ldr	x27, .LC195
	b	.L1825
	.p2align 3
.L1820:
	str	w23, [x1, 2948]
	add	x0, x28, x19, lsl 2
	str	wzr, [x1, 3716]
	add	x0, x0, 11116544
	ldr	w1, [x21, 748]
	cbnz	w1, .L1839
.L1822:
	str	wzr, [x0, 3076]
	str	wzr, [x0, 3204]
	str	wzr, [x0, 3844]
	str	wzr, [x0, 3972]
.L1824:
	ldr	w0, [x20, 2932]
	add	w25, w25, 1
	cmp	w0, w25
	bcc	.L1840
.L1825:
	mov	x1, x22
	mov	x0, x28
	uxtw	x19, w25
	bl	mvc_u_1
	add	x1, x28, x19, lsl 2
	add	x1, x1, 11116544
	cbz	w0, .L1820
	mov	x1, x27
	mov	x0, x28
	bl	mvc_se_v
	add	x4, x28, x19, lsl 2
	ldr	x1, .LC197
	add	x26, x4, 11116544
	str	w0, [x26, 2948]
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x26, 3716]
	add	x0, x28, x19, lsl 2
	ldr	w1, [x21, 748]
	add	x0, x0, 11116544
	cbz	w1, .L1822
.L1839:
	ldr	x1, .LC199
	mov	x0, x28
	bl	mvc_u_1
	add	x1, x28, x19, lsl 2
	add	x1, x1, 11116544
	cbnz	w0, .L1841
	str	w24, [x1, 3076]
	add	w25, w25, 1
	str	w24, [x1, 3204]
	str	wzr, [x1, 3844]
	str	wzr, [x1, 3972]
	ldr	w0, [x20, 2932]
	cmp	w0, w25
	bcs	.L1825
.L1840:
	ldr	x0, [x29, 104]
	ldr	w0, [x0, 44]
	cmp	w0, 1
	beq	.L1826
.L1827:
	ldrb	w0, [x28, 10]
	cmp	w0, wzr
	csetm	w0, ne
.L1819:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1841:
	ldr	x1, .LC201
	mov	x0, x28
	add	x19, x28, x19, lsl 2
	add	x19, x19, 11116544
	bl	mvc_se_v
	ldr	x1, .LC203
	str	w0, [x19, 3076]
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 3844]
	ldr	x1, .LC201
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 3204]
	ldr	x1, .LC203
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 3972]
	b	.L1824
	.p2align 3
.L1838:
	ldr	x1, .LC189
	mov	x0, x28
	bl	mvc_ue_v
	mov	w24, w0
	ldr	w0, [x20, 2940]
	str	w24, [x20, 2944]
	lsl	w24, w19, w24
	b	.L1814
	.p2align 3
.L1826:
	ldrb	w0, [x20, 2872]
	cmp	w0, 1
	bne	.L1827
	ldr	x22, .LC205
	mov	w25, 0
	ldr	x27, .LC207
	b	.L1833
	.p2align 3
.L1828:
	add	x0, x28, x19, lsl 2
	add	x1, x0, 11116544
	add	x0, x0, 11120640
	str	w23, [x1, 3332]
	str	wzr, [x0, 4]
	add	x0, x28, x19, lsl 2
	ldr	w1, [x21, 748]
	cbnz	w1, .L1842
.L1830:
	add	x1, x0, 11116544
	add	x0, x0, 11120640
	str	wzr, [x1, 3460]
	str	wzr, [x0, 132]
	str	wzr, [x1, 3588]
	str	wzr, [x0, 260]
.L1832:
	ldr	w0, [x20, 2936]
	add	w25, w25, 1
	cmp	w0, w25
	bcc	.L1827
.L1833:
	mov	x1, x22
	mov	x0, x28
	uxtw	x19, w25
	bl	mvc_u_1
	cbz	w0, .L1828
	mov	x1, x27
	mov	x0, x28
	add	x26, x28, x19, lsl 2
	bl	mvc_se_v
	add	x1, x26, 11116544
	str	w0, [x1, 3332]
	mov	x0, x28
	ldr	x1, .LC209
	bl	mvc_se_v
	add	x4, x26, 11120640
	str	w0, [x4, 4]
	add	x0, x28, x19, lsl 2
	ldr	w1, [x21, 748]
	cbz	w1, .L1830
.L1842:
	ldr	x1, .LC211
	mov	x0, x28
	bl	mvc_u_1
	cbnz	w0, .L1843
	add	x0, x28, x19, lsl 2
	add	x1, x0, 11116544
	add	x0, x0, 11120640
	str	w24, [x1, 3460]
	str	wzr, [x0, 132]
	str	w24, [x1, 3588]
	str	wzr, [x0, 260]
	b	.L1832
.L1817:
	ldrb	w2, [x28, 10]
.L1816:
	ldr	x1, .LC191
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1819
.L1843:
	add	x19, x28, x19, lsl 2
	ldr	x1, .LC213
	add	x0, x19, 11116544
	add	x19, x19, 11120640
	mov	x26, x0
	mov	x0, x28
	bl	mvc_se_v
	ldr	x1, .LC215
	str	w0, [x26, 3460]
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 132]
	ldr	x1, .LC213
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x26, 3588]
	ldr	x1, .LC215
	mov	x0, x28
	bl	mvc_se_v
	str	w0, [x19, 260]
	b	.L1832
	.size	mvc_pred_weight_table, .-mvc_pred_weight_table
	.align	3
.LC187:
	.xword	.LC186
	.align	3
.LC189:
	.xword	.LC188
	.align	3
.LC191:
	.xword	.LC190
	.align	3
.LC193:
	.xword	.LC192
	.align	3
.LC195:
	.xword	.LC194
	.align	3
.LC197:
	.xword	.LC196
	.align	3
.LC199:
	.xword	.LC198
	.align	3
.LC201:
	.xword	.LC200
	.align	3
.LC203:
	.xword	.LC202
	.align	3
.LC205:
	.xword	.LC204
	.align	3
.LC207:
	.xword	.LC206
	.align	3
.LC209:
	.xword	.LC208
	.align	3
.LC211:
	.xword	.LC210
	.align	3
.LC213:
	.xword	.LC212
	.align	3
.LC215:
	.xword	.LC214
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecMMCO
	.type	MVC_DecMMCO, %function
MVC_DecMMCO:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	w19, w1
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L1845
	mov	w21, 100
	ldr	x20, .LC219
	ldr	x23, .LC221
	ldr	x25, .LC227
	ldr	x22, .LC225
	ldr	x24, .LC223
	b	.L1856
	.p2align 3
.L1857:
	cmp	w19, 2
	beq	.L1870
.L1858:
	cmp	w19, 6
	cset	w0, eq
	orr	w0, w27, w0
	cbnz	w0, .L1861
	cmp	w19, 4
	beq	.L1871
.L1862:
	cmp	w19, 6
	bhi	.L1854
	ldrb	w0, [x26, 10]
	cbnz	w0, .L1854
.L1872:
	cbz	w19, .L1864
.L1863:
	subs	w21, w21, #1
	beq	.L1865
.L1856:
	mov	x1, x20
	mov	x0, x26
	bl	mvc_ue_v
	cmp	w0, 3
	mov	w19, w0
	and	w0, w0, -3
	cset	w27, eq
	cmp	w0, 1
	bne	.L1857
	mov	x1, x23
	mov	x0, x26
	bl	mvc_ue_v
	cmp	w19, 2
	bne	.L1858
.L1870:
	mov	x1, x24
	mov	x0, x26
	bl	mvc_ue_v
	ldrb	w0, [x26, 10]
	cbz	w0, .L1872
	.p2align 2
.L1854:
	ldr	x1, .LC229
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L1848:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1861:
	mov	x1, x22
	mov	x0, x26
	bl	mvc_ue_v
	cmp	w19, 4
	bne	.L1862
.L1871:
	mov	x1, x25
	mov	x0, x26
	bl	mvc_ue_v
	ldrb	w0, [x26, 10]
	cbz	w0, .L1863
	b	.L1854
	.p2align 3
.L1845:
	ldr	x20, .LC219
	mov	w28, 0
	ldr	x22, .LC221
	ldr	x24, .LC223
	ldr	x21, .LC225
	ldr	x23, .LC227
	b	.L1847
	.p2align 3
.L1849:
	cmp	w1, 2
	beq	.L1873
.L1850:
	cmp	w1, 3
	ccmp	w1, 6, 4, ne
	beq	.L1874
.L1851:
	cmp	w1, 4
	beq	.L1875
.L1852:
	cmp	w1, 6
	bhi	.L1854
	ldrb	w0, [x26, 10]
	cbnz	w0, .L1854
	add	w28, w28, 1
	cbz	w1, .L1864
	cmp	w28, 100
	beq	.L1876
.L1847:
	mov	x1, x20
	mov	x0, x26
	ldrb	w25, [x26, 3]
	uxtw	x27, w28
	bl	mvc_ue_v
	mov	w1, w0
	lsl	x0, x25, 6
	lsl	x19, x27, 4
	sub	x0, x0, x25
	add	x19, x19, x27, lsl 2
	lsl	x0, x0, 2
	and	w2, w1, -3
	sub	x0, x0, x25
	cmp	w2, 1
	lsl	x0, x0, 1
	sub	x0, x0, x25
	add	x19, x19, x0, lsl 2
	add	x19, x26, x19
	add	x19, x19, 11120640
	str	w1, [x19, 484]
	bne	.L1849
	mov	x1, x22
	mov	x0, x26
	bl	mvc_ue_v
	str	w0, [x19, 488]
	ldr	w1, [x19, 484]
	cmp	w1, 2
	bne	.L1850
.L1873:
	mov	x1, x24
	mov	x0, x26
	bl	mvc_ue_v
	lsl	x1, x25, 6
	sub	x1, x1, x25
	lsl	x1, x1, 2
	sub	x1, x1, x25
	lsl	x1, x1, 1
	sub	x2, x1, x25
	lsl	x1, x27, 4
	add	x1, x1, x27, lsl 2
	add	x1, x1, x2, lsl 2
	add	x1, x26, x1
	add	x1, x1, 11120640
	str	w0, [x1, 492]
	ldr	w1, [x1, 484]
	cmp	w1, 3
	ccmp	w1, 6, 4, ne
	bne	.L1851
	.p2align 2
.L1874:
	mov	x1, x21
	mov	x0, x26
	bl	mvc_ue_v
	lsl	x1, x25, 6
	lsl	x2, x27, 4
	sub	x1, x1, x25
	add	x2, x2, x27, lsl 2
	lsl	x1, x1, 2
	sub	x1, x1, x25
	lsl	x1, x1, 1
	sub	x1, x1, x25
	add	x2, x2, x1, lsl 2
	add	x2, x26, x2
	add	x2, x2, 11120640
	ldr	w1, [x2, 484]
	str	w0, [x2, 496]
	cmp	w1, 4
	bne	.L1852
.L1875:
	mov	x1, x23
	mov	x0, x26
	bl	mvc_ue_v
	lsl	x1, x25, 6
	sub	x1, x1, x25
	lsl	x1, x1, 2
	sub	x1, x1, x25
	lsl	x1, x1, 1
	sub	x25, x1, x25
	lsl	x1, x27, 4
	add	x27, x1, x27, lsl 2
	add	x27, x27, x25, lsl 2
	add	x27, x26, x27
	add	x27, x27, 11120640
	ldr	w1, [x27, 484]
	str	w0, [x27, 500]
	b	.L1852
	.p2align 3
.L1864:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1876:
	ldr	x1, .LC217
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1848
.L1865:
	mov	w0, -1
	b	.L1848
	.size	MVC_DecMMCO, .-MVC_DecMMCO
	.align	3
.LC217:
	.xword	.LC216
	.align	3
.LC219:
	.xword	.LC218
	.align	3
.LC221:
	.xword	.LC220
	.align	3
.LC223:
	.xword	.LC222
	.align	3
.LC225:
	.xword	.LC224
	.align	3
.LC227:
	.xword	.LC226
	.align	3
.LC229:
	.xword	.LC228
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_dec_ref_pic_marking
	.type	mvc_dec_ref_pic_marking, %function
mvc_dec_ref_pic_marking:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x21, 11116544
	ldrb	w22, [x21, 3]
	ldrb	w0, [x1, 2877]
	cbz	w0, .L1878
	cmp	w22, wzr
	cset	w19, eq
	strb	w19, [x21, 3]
.L1887:
	ldrb	w0, [x1, 2875]
	cmp	w0, 5
	beq	.L1898
	ldr	x1, .LC237
	mov	x0, x21
	sxtw	x19, w19
	bl	mvc_u_1
	mov	w4, w0
	lsl	x3, x19, 6
	ldr	x1, .LC239
	sub	x3, x3, x19
	uxtb	w2, w0
	lsl	x3, x3, 2
	mov	w0, 16
	sub	x3, x3, x19
	lsl	x3, x3, 1
	sub	x19, x3, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 11120640
	strb	w4, [x19, 483]
	bl	dprint_vfmw
	ldrb	w0, [x19, 483]
	cbnz	w0, .L1881
.L1885:
	mov	w20, 0
.L1895:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1878:
	sxtw	x20, w22
	mov	w19, w22
	lsl	x0, x20, 6
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x0, x0, x20
	lsl	x0, x0, 1
	sub	x20, x0, x20
	add	x20, x21, x20, lsl 2
	add	x20, x20, 11120640
	ldrb	w0, [x20, 480]
	cbz	w0, .L1887
	ldrb	w0, [x1, 2875]
	cmp	w0, 5
	beq	.L1899
	ldr	x1, .LC237
	mov	x0, x21
	ldrb	w19, [x20, 483]
	bl	mvc_u_1
	cmp	w19, w0
	bne	.L1900
	ldrb	w0, [x20, 483]
	cbz	w0, .L1885
	mov	w1, 0
	mov	x0, x21
	bl	MVC_DecMMCO
	mov	w20, w0
	b	.L1895
	.p2align 3
.L1881:
	mov	w1, 1
	mov	x0, x21
	bl	MVC_DecMMCO
	cmn	w0, #1
	mov	w20, w0
	beq	.L1901
	mov	w0, 1
	strb	w0, [x19, 480]
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1899:
	ldr	x1, .LC231
	mov	x0, x21
	ldrb	w19, [x20, 481]
	bl	mvc_u_1
	cmp	w19, w0
	bne	.L1902
	ldr	x1, .LC233
	mov	x0, x21
	ldrb	w19, [x20, 482]
	bl	mvc_u_1
	cmp	w19, w0
	beq	.L1885
	ldr	x1, .LC245
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1895
	.p2align 3
.L1898:
	ldr	x1, .LC231
	mov	x0, x21
	sxtw	x19, w19
	mov	w20, 0
	bl	mvc_u_1
	lsl	x2, x19, 6
	ldr	x1, .LC233
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x2, x2, x19
	lsl	x2, x2, 1
	sub	x19, x2, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 11120640
	strb	w0, [x19, 481]
	mov	x0, x21
	bl	mvc_u_1
	strb	w0, [x19, 482]
	ldrb	w2, [x19, 481]
	mov	w0, 16
	ldr	x1, .LC235
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1900:
	ldr	x1, .LC247
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	ldr	x1, .LC249
	mov	w0, 1
	ldr	w4, [x21, 68]
	ldr	w2, [x21, 88]
	ldr	w3, [x21, 100]
	bl	dprint_vfmw
	b	.L1895
.L1902:
	ldr	x1, .LC243
	mov	w0, 1
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1895
.L1901:
	strb	wzr, [x19, 480]
	mov	w0, 1
	ldr	x1, .LC241
	strb	w22, [x21, 3]
	bl	dprint_vfmw
	b	.L1895
	.size	mvc_dec_ref_pic_marking, .-mvc_dec_ref_pic_marking
	.align	3
.LC231:
	.xword	.LC230
	.align	3
.LC233:
	.xword	.LC232
	.align	3
.LC235:
	.xword	.LC234
	.align	3
.LC237:
	.xword	.LC236
	.align	3
.LC239:
	.xword	.LC238
	.align	3
.LC241:
	.xword	.LC240
	.align	3
.LC243:
	.xword	.LC242
	.align	3
.LC245:
	.xword	.LC244
	.align	3
.LC247:
	.xword	.LC246
	.align	3
.LC249:
	.xword	.LC248
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSliceHeaderFirstPart
	.type	MVC_ProcessSliceHeaderFirstPart, %function
MVC_ProcessSliceHeaderFirstPart:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC251
	mov	x0, x19
	bl	mvc_ue_v
	mov	w21, w0
	ldr	w0, [x19, 40]
	sub	w0, w0, #1
	cmp	w21, w0
	bhi	.L1904
	ldrb	w0, [x19, 10]
	cbnz	w0, .L1904
	mov	w1, w21
	mov	x0, x19
	bl	MVC_PPSSPSCheckTmpId
	cbnz	w0, .L1958
	add	x20, x19, 11116544
	mov	x0, x19
	str	w21, [x20, 2888]
	bl	MVC_PPSSPSCheck
	mov	w22, w0
	cbnz	w0, .L1959
	ldp	x21, x23, [x19, 256]
	ldr	x2, .LC259
	mov	x0, x19
	ldr	w1, [x21, 2896]
	add	w1, w1, 4
	bl	mvc_u_v
	str	w0, [x20, 2900]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L1930
	ldrb	w1, [x20, 2875]
	cmp	w1, 5
	ccmp	w0, wzr, 4, eq
	bne	.L1960
.L1910:
	strb	wzr, [x20, 2873]
	strb	wzr, [x20, 2874]
	ldrb	w0, [x21, 20]
	cbz	w0, .L1961
	ldr	w1, [x21, 3952]
	ldr	w2, [x21, 3948]
	add	w0, w1, 1
	madd	w0, w2, w0, w0
.L1933:
	ldrb	w1, [x21, 21]
	cbnz	w1, .L1916
	strb	wzr, [x20, 2876]
.L1918:
	ldr	w1, [x20, 2928]
	cmp	w1, w0
	bcs	.L1962
.L1919:
	ldrb	w0, [x20, 2875]
	cmp	w0, 5
	beq	.L1963
.L1921:
	str	wzr, [x20, 1740]
	str	wzr, [x20, 1744]
	ldr	w0, [x21, 2900]
	cbz	w0, .L1964
.L1925:
	str	wzr, [x20, 1776]
	str	wzr, [x20, 1780]
	ldr	w0, [x21, 2900]
	cmp	w0, 1
	beq	.L1965
.L1928:
	ldrb	w0, [x19, 10]
	cbnz	w0, .L1930
	ldrb	w0, [x23, 17]
	cbz	w0, .L1931
	ldr	x1, .LC283
	mov	x0, x19
	bl	mvc_ue_v
	cbnz	w0, .L1932
	ldrb	w0, [x19, 10]
	cbz	w0, .L1931
.L1932:
	ldr	x1, .LC285
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC286
	ldr	x4, [x0]
	cbz	x4, .L1930
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w22, -1
	blr	x4
.L1942:
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1961:
	ldr	x1, .LC263
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 2873]
	cbnz	w0, .L1966
	ldr	w2, [x21, 3952]
	ldr	w1, [x21, 3948]
	add	w0, w2, 1
	ldrb	w3, [x21, 20]
	madd	w1, w1, w0, w0
	lsl	w0, w1, 1
	cbz	w3, .L1933
.L1913:
	ldrb	w2, [x20, 2873]
	mov	w0, 1
	b	.L1914
	.p2align 3
.L1916:
	mov	w1, 1
	strb	w1, [x20, 2876]
.L1935:
	ldr	w1, [x20, 2928]
	cmp	w1, w0, lsr 1
	bcc	.L1919
	ldr	x1, .LC267
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1942
	.p2align 3
.L1966:
	ldr	x1, .LC265
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 2874]
	ldr	w0, [x21, 3952]
	ldr	w1, [x21, 3948]
	ldrb	w2, [x21, 20]
	add	w0, w0, 1
	madd	w1, w1, w0, w0
	cbnz	w2, .L1913
	ldrb	w2, [x20, 2873]
	mov	w0, 2
.L1914:
	mul	w0, w0, w1
	cbz	w2, .L1933
	strb	wzr, [x20, 2876]
	cmp	w2, 1
	bne	.L1918
	b	.L1935
	.p2align 3
.L1931:
	mov	x0, x19
	bl	MVC_IsNewPic
	uxtb	w0, w0
	strb	w0, [x20, 2877]
	cbnz	w0, .L1942
	add	x19, x19, 11120640
	ldr	w1, [x20, 2928]
	ldr	w0, [x19, 472]
	cmp	w1, w0
	bhi	.L1942
	ldr	x1, .LC288
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1942
	.p2align 3
.L1964:
	ldr	w1, [x21, 2904]
	mov	x0, x19
	ldr	x2, .LC275
	add	w1, w1, 4
	bl	mvc_u_v
	str	w0, [x20, 1740]
	ldrb	w0, [x23, 1]
	cbz	w0, .L1925
	ldrb	w0, [x20, 2873]
	cbnz	w0, .L1925
	ldr	x1, .LC277
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 1744]
	b	.L1925
	.p2align 3
.L1965:
	ldrb	w0, [x21, 18]
	cbnz	w0, .L1928
	ldr	x1, .LC279
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 1776]
	ldrb	w0, [x23, 1]
	cmp	w0, 1
	bne	.L1928
	ldrb	w0, [x20, 2873]
	cbnz	w0, .L1928
	ldr	x1, .LC281
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 1780]
	b	.L1928
	.p2align 3
.L1930:
	mov	w22, -1
	ldr	x23, [sp, 48]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1904:
	ldr	x1, .LC253
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1963:
	ldr	x1, .LC271
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 2916]
	mov	w1, 65535
	cmp	w0, w1
	bhi	.L1922
	ldrb	w0, [x19, 10]
	cbz	w0, .L1921
.L1922:
	ldr	x1, .LC273
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1921
	.p2align 3
.L1958:
	ldr	x1, .LC255
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1942
	.p2align 3
.L1959:
	ldr	x1, .LC257
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1942
	.p2align 3
.L1960:
	add	x0, x19, 11120640
	ldr	w0, [x0, 416]
	cmp	w0, wzr
	bgt	.L1910
	ldr	x1, .LC261
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1910
.L1962:
	ldr	x1, .LC269
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1942
	.size	MVC_ProcessSliceHeaderFirstPart, .-MVC_ProcessSliceHeaderFirstPart
	.align	3
.LC251:
	.xword	.LC250
	.align	3
.LC253:
	.xword	.LC252
	.align	3
.LC255:
	.xword	.LC254
	.align	3
.LC257:
	.xword	.LC256
	.align	3
.LC259:
	.xword	.LC258
	.align	3
.LC261:
	.xword	.LC260
	.align	3
.LC263:
	.xword	.LC262
	.align	3
.LC265:
	.xword	.LC264
	.align	3
.LC267:
	.xword	.LC266
	.align	3
.LC269:
	.xword	.LC268
	.align	3
.LC271:
	.xword	.LC270
	.align	3
.LC273:
	.xword	.LC272
	.align	3
.LC275:
	.xword	.LC274
	.align	3
.LC277:
	.xword	.LC276
	.align	3
.LC279:
	.xword	.LC278
	.align	3
.LC281:
	.xword	.LC280
	.align	3
.LC283:
	.xword	.LC282
	.align	3
.LC285:
	.xword	.LC284
	.align	3
.LC286:
	.xword	g_event_report
	.align	3
.LC288:
	.xword	.LC287
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSliceHeaderSecondPart
	.type	MVC_ProcessSliceHeaderSecondPart, %function
MVC_ProcessSliceHeaderSecondPart:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11116544
	bl	_mcount
	ldr	w0, [x20, 40]
	ldr	w2, [x19, 2888]
	sub	w0, w0, #1
	ldr	x21, [x20, 264]
	cmp	w0, w2
	bcc	.L1968
	ldrb	w22, [x20, 10]
	cbnz	w22, .L1968
	mov	x0, x20
	bl	MVC_PPSSPSCheck
	cbnz	w0, .L2050
	ldrb	w1, [x19, 2872]
	cmp	w1, 1
	beq	.L2051
	ldr	w0, [x21, 36]
	cmp	w1, 1
	str	w0, [x19, 2932]
	ldr	w0, [x21, 40]
	str	w0, [x19, 2936]
	bls	.L2052
.L1973:
	cmp	w1, 2
	beq	.L1999
.L1983:
	mov	w0, 32
	str	w0, [x19, 2936]
.L1984:
	mov	x0, x20
	bl	mvc_ref_pic_list_reordering
	mov	w23, w0
	cbnz	w0, .L2053
	ldrb	w0, [x21, 2]
	cbz	w0, .L1986
	ldrb	w0, [x19, 2872]
	cbnz	w0, .L1986
	mov	w22, 1
	mov	w2, w22
.L1987:
	ldr	x1, .LC306
	mov	w0, 19
	strb	w22, [x19, 2879]
	bl	dprint_vfmw
	str	wzr, [x19, 2940]
	ldrb	w0, [x19, 2879]
	str	wzr, [x19, 2944]
	cbnz	w0, .L2054
.L1988:
	ldrb	w0, [x19, 2880]
	cbnz	w0, .L2055
.L1989:
	add	x22, x20, 11120640
	str	wzr, [x22, 388]
	ldrb	w0, [x21]
	cbz	w0, .L1990
	ldrb	w0, [x19, 2872]
	cmp	w0, 1
	bls	.L2056
.L1990:
	ldr	x1, .LC316
	mov	x0, x20
	bl	mvc_se_v
	add	x1, x22, 256
	stp	w0, wzr, [x1, 136]
	stp	wzr, wzr, [x1, 144]
	ldrb	w0, [x21, 3]
	cbnz	w0, .L2057
.L2019:
	mov	w0, w23
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1986:
	ldr	w0, [x21, 44]
	mov	w2, 0
	cmp	w0, 1
	bne	.L1987
	ldrb	w0, [x19, 2872]
	cmp	w0, 1
	bne	.L1987
	mov	w22, w0
	mov	w2, w0
	b	.L1987
	.p2align 3
.L2057:
	ldr	x1, .LC318
	mov	x0, x20
	bl	mvc_ue_v
	cmp	w0, 2
	str	w0, [x22, 396]
	bhi	.L1993
	ldrb	w1, [x20, 10]
	cbnz	w1, .L1993
	cmp	w0, 1
	beq	.L2019
	ldr	x1, .LC322
	mov	x0, x20
	bl	mvc_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x22, 400]
	bhi	.L1996
	ldrb	w0, [x20, 10]
	cbnz	w0, .L1996
	ldr	x1, .LC326
	mov	x0, x20
	bl	mvc_se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x22, 404]
	bhi	.L1998
	ldrb	w0, [x20, 10]
	cbz	w0, .L2019
.L1998:
	ldr	x1, .LC328
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L2054:
	mov	x0, x20
	bl	mvc_pred_weight_table
	cbz	w0, .L1988
	ldr	x1, .LC308
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L2055:
	mov	x0, x20
	bl	mvc_dec_ref_pic_marking
	cbz	w0, .L1989
	ldr	x1, .LC310
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L1999:
	mov	w0, 32
	str	w0, [x19, 2932]
	b	.L1983
	.p2align 3
.L2051:
	ldr	x1, .LC292
	mov	x0, x20
	bl	mvc_u_1
	strb	w0, [x19, 2878]
	ldrb	w1, [x19, 2872]
	ldr	w0, [x21, 36]
	str	w0, [x19, 2932]
	cmp	w1, 1
	ldr	w0, [x21, 40]
	str	w0, [x19, 2936]
	bhi	.L1973
	.p2align 2
.L2052:
	ldr	x1, .LC294
	mov	x0, x20
	bl	mvc_u_1
	cbnz	w0, .L1974
	ldr	w1, [x19, 2932]
.L1975:
	ldrb	w0, [x19, 2873]
	cbnz	w0, .L1976
	cmp	w1, 15
	bhi	.L1977
	ldr	w0, [x19, 2936]
	cmp	w0, 15
	bhi	.L2058
.L1978:
	ldrb	w0, [x20, 10]
	cbnz	w0, .L1977
.L1979:
	ldrb	w0, [x19, 2872]
	cmp	w0, 2
	beq	.L1999
	cmp	w0, 1
	beq	.L1984
	b	.L1983
	.p2align 3
.L1968:
	ldr	x1, .LC289
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	mov	w0, w23
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2056:
	ldr	x1, .LC312
	mov	x0, x20
	bl	mvc_ue_v
	cmp	w0, 2
	str	w0, [x22, 388]
	bhi	.L1991
	ldrb	w0, [x20, 10]
	cbz	w0, .L1990
.L1991:
	ldr	x1, .LC314
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L1976:
	cmp	w1, 31
	bhi	.L1980
	ldr	w0, [x19, 2936]
	cmp	w0, 31
	bls	.L1981
	ldrb	w0, [x19, 2872]
	cmp	w0, 1
	bne	.L1981
.L1980:
	ldr	x1, .LC302
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L1981:
	ldrb	w0, [x20, 10]
	cbz	w0, .L1979
	b	.L1980
	.p2align 3
.L2058:
	ldrb	w0, [x19, 2872]
	cmp	w0, 1
	bne	.L1978
.L1977:
	ldr	x1, .LC300
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L1974:
	ldr	x1, .LC296
	mov	x0, x20
	bl	mvc_ue_v
	mov	w1, w0
	ldrb	w0, [x19, 2872]
	str	w1, [x19, 2932]
	cmp	w0, 1
	bne	.L1975
	ldr	x1, .LC298
	mov	x0, x20
	bl	mvc_ue_v
	str	w0, [x19, 2936]
	ldr	w1, [x19, 2932]
	b	.L1975
	.p2align 3
.L1996:
	ldr	x1, .LC324
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L1993:
	ldr	x1, .LC320
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L2050:
	ldr	x1, .LC290
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.p2align 3
.L2053:
	ldr	x1, .LC304
	mov	w0, 1
	mov	w23, -1
	bl	dprint_vfmw
	b	.L2019
	.size	MVC_ProcessSliceHeaderSecondPart, .-MVC_ProcessSliceHeaderSecondPart
	.align	3
.LC289:
	.xword	.LC252
	.align	3
.LC290:
	.xword	.LC254
	.align	3
.LC292:
	.xword	.LC291
	.align	3
.LC294:
	.xword	.LC293
	.align	3
.LC296:
	.xword	.LC295
	.align	3
.LC298:
	.xword	.LC297
	.align	3
.LC300:
	.xword	.LC299
	.align	3
.LC302:
	.xword	.LC301
	.align	3
.LC304:
	.xword	.LC303
	.align	3
.LC306:
	.xword	.LC305
	.align	3
.LC308:
	.xword	.LC307
	.align	3
.LC310:
	.xword	.LC309
	.align	3
.LC312:
	.xword	.LC311
	.align	3
.LC314:
	.xword	.LC313
	.align	3
.LC316:
	.xword	.LC315
	.align	3
.LC318:
	.xword	.LC317
	.align	3
.LC320:
	.xword	.LC319
	.align	3
.LC322:
	.xword	.LC321
	.align	3
.LC324:
	.xword	.LC323
	.align	3
.LC326:
	.xword	.LC325
	.align	3
.LC328:
	.xword	.LC327
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ExitSlice
	.type	MVC_ExitSlice, %function
MVC_ExitSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11116544
	add	x0, x19, 11120640
	ldr	x3, [x19, 248]
	ldr	w2, [x1, 2888]
	str	w2, [x0, 444]
	ldr	w2, [x3, 744]
	str	w2, [x0, 440]
	ldr	w2, [x1, 2928]
	str	w2, [x0, 472]
	ldr	w2, [x1, 2900]
	str	w2, [x0, 448]
	ldrb	w2, [x1, 2873]
	strb	w2, [x0, 432]
	cbz	w2, .L2060
	ldrb	w2, [x1, 2874]
	strb	w2, [x0, 433]
.L2060:
	ldrb	w2, [x1, 2880]
	strb	w2, [x0, 435]
	ldrb	w2, [x1, 2875]
	strb	w2, [x0, 434]
	cmp	w2, 5
	beq	.L2068
.L2061:
	ldr	w2, [x3, 2900]
	cbnz	w2, .L2062
	ldr	w2, [x1, 1740]
	str	w2, [x0, 456]
	ldr	w2, [x1, 1744]
	str	w2, [x0, 460]
	ldr	w2, [x3, 2900]
.L2062:
	cmp	w2, 1
	beq	.L2069
.L2063:
	ldrb	w2, [x1, 2883]
	cmp	w2, 1
	bne	.L2064
	ldr	w2, [x0, 416]
	str	w2, [x0, 476]
	ldrb	w2, [x1, 2881]
	strb	w2, [x0, 436]
	ldrb	w1, [x1, 2882]
	strb	w1, [x0, 437]
.L2064:
	ldr	w0, [x19, 80]
	add	w0, w0, 1
	str	w0, [x19, 80]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2069:
	ldr	w2, [x1, 1776]
	str	w2, [x0, 464]
	ldr	w2, [x1, 1780]
	str	w2, [x0, 468]
	b	.L2063
	.p2align 3
.L2068:
	ldr	w2, [x1, 2916]
	str	w2, [x0, 452]
	b	.L2061
	.size	MVC_ExitSlice, .-MVC_ExitSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PicTypeStatistic
	.type	MVC_PicTypeStatistic, %function
MVC_PicTypeStatistic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 11116544
	ldrb	w0, [x1, 2872]
	cmp	w0, 1
	beq	.L2072
	cbz	w0, .L2073
	cmp	w0, 2
	bne	.L2070
	ldrb	w0, [x1, 2875]
	add	x19, x19, 11157504
	cmp	w0, 5
	beq	.L2080
.L2075:
	strb	wzr, [x19, 2677]
.L2070:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2073:
	add	x19, x19, 11157504
	ldrb	w0, [x19, 2676]
	cmp	w0, 2
	beq	.L2075
	mov	w0, 1
	strb	wzr, [x19, 2677]
	strb	w0, [x19, 2676]
	b	.L2070
	.p2align 3
.L2072:
	add	x19, x19, 11157504
	mov	w0, 2
	strb	wzr, [x19, 2677]
	strb	w0, [x19, 2676]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2080:
	mov	w0, 1
	strb	w0, [x19, 2677]
	b	.L2070
	.size	MVC_PicTypeStatistic, .-MVC_PicTypeStatistic
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CalcStreamBits
	.type	MVC_CalcStreamBits, %function
MVC_CalcStreamBits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 11112448
	ldrb	w0, [x0, 3592]
	cbz	w0, .L2082
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 72]
	add	w0, w0, 7
	and	w0, w0, -8
	str	w0, [x1, 72]
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 80]
	sub	w0, w0, #1
	str	w0, [x1, 80]
.L2082:
	ldr	x3, [x19, 240]
	ldrb	w21, [x3]
	cbz	w21, .L2093
	sub	w1, w21, #1
	mov	w4, 32
	mov	x2, 48
	add	x0, x3, 16
	mov	w20, 0
	umaddl	x2, w1, w4, x2
	add	x2, x3, x2
	.p2align 2
.L2084:
	ldr	w1, [x0], 32
	cmp	x0, x2
	add	w20, w20, w1
	bne	.L2084
.L2083:
	sbfiz	x4, x21, 5, 32
	ldr	w2, [x3, 72]
	add	x4, x3, x4
	ldr	w5, [x3, 80]
	ldr	x1, .LC330
	mov	w3, w20
	mov	w0, 7
	ldr	w4, [x4, 16]
	bl	dprint_vfmw
	ldr	x2, [x19, 240]
	ubfiz	x3, x21, 5, 8
	ldrb	w0, [x2]
	ldr	w1, [x2, 72]
	add	x0, x2, x0, lsl 5
	and	w1, w1, 7
	str	w1, [x0, 28]
	ldr	x2, [x19, 240]
	ldrb	w1, [x2]
	ldr	w0, [x2, 72]
	add	x1, x2, x1, lsl 5
	ldr	w2, [x1, 20]
	add	w0, w2, w0, lsr 3
	mov	w2, w21
	sub	w0, w0, w20
	str	w0, [x1, 32]
	ldr	x4, [x19, 240]
	ldrb	w1, [x4]
	ldr	w0, [x4, 72]
	add	x4, x4, x1, lsl 5
	ldr	w1, [x4, 16]
	add	w20, w20, w1
	lsl	w20, w20, 3
	sub	w0, w20, w0
	str	w0, [x4, 24]
	ldr	x1, [x19, 240]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldp	w4, w1, [x0, 28]
	ubfiz	w1, w1, 3, 2
	add	w1, w1, w4
	str	w1, [x0, 28]
	ldr	x1, .LC332
	ldr	x4, [x19, 240]
	ldrb	w0, [x4]
	add	x4, x4, x0, lsl 5
	mov	w0, 7
	ldr	w5, [x4, 32]
	and	w5, w5, -4
	str	w5, [x4, 32]
	ldr	x6, [x19, 240]
	add	x3, x6, x3
	ldrb	w5, [x6]
	ldp	w4, w3, [x3, 24]
	add	x5, x6, x5, lsl 5
	ldr	w5, [x5, 32]
	bl	dprint_vfmw
	ldr	x0, [x19, 240]
	ldr	w2, [x0, 76]
	sub	w1, w2, #1
	cmp	w1, 1
	bhi	.L2104
	ldrb	w20, [x0]
	add	w3, w20, 1
	cmp	w3, 1
	ccmp	w2, w3, 0, ls
	bls	.L2087
	ldr	x21, .LC336
	add	w20, w20, 2
	.p2align 2
.L2088:
	sub	w2, w20, #1
	mov	x1, x21
	ubfiz	x3, x2, 5, 32
	add	x4, x0, x3
	mov	w0, 7
	str	wzr, [x4, 28]
	ldr	x4, [x19, 240]
	add	x4, x4, x3
	ldr	w5, [x4, 20]
	str	w5, [x4, 32]
	ldr	x4, [x19, 240]
	add	x4, x4, x3
	ldr	w5, [x4, 16]
	lsl	w5, w5, 3
	str	w5, [x4, 24]
	ldr	x4, [x19, 240]
	add	x4, x4, x3
	ldp	w6, w5, [x4, 28]
	ubfiz	w5, w5, 3, 2
	add	w5, w5, w6
	str	w5, [x4, 28]
	ldr	x4, [x19, 240]
	add	x4, x4, x3
	ldr	w5, [x4, 32]
	and	w5, w5, -4
	str	w5, [x4, 32]
	ldr	x4, [x19, 240]
	add	x3, x4, x3
	ldp	w4, w3, [x3, 24]
	bl	dprint_vfmw
	ldr	x0, [x19, 240]
	cmp	w20, 1
	cset	w3, ls
	ldr	w1, [x0, 76]
	cmp	w1, w20
	add	w20, w20, 1
	cset	w2, hi
	tst	w3, w2
	bne	.L2088
	sub	w1, w1, #1
.L2087:
	ubfiz	x1, x1, 5, 32
	ldr	w2, [x0, 80]
	add	x0, x0, x1
	add	x5, x19, 11157504
	ldr	w1, [x0, 24]
	sub	w1, w1, w2
	str	w1, [x0, 24]
	ldr	x3, [x19, 240]
	ldrb	w0, [x3]
	ldr	w4, [x3, 76]
	cmp	w0, w4
	bcs	.L2081
	.p2align 2
.L2098:
	ubfiz	x1, x0, 5, 32
	ldr	w2, [x5, 3400]
	add	x1, x3, x1
	add	w0, w0, 1
	ldr	w1, [x1, 32]
	cmp	w1, w2
	bcs	.L2090
	str	w1, [x5, 3400]
	ldr	w4, [x3, 76]
.L2090:
	cmp	w4, w0
	bhi	.L2098
.L2081:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2104:
	ldr	x1, .LC334
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2093:
	mov	w20, 0
	b	.L2083
	.size	MVC_CalcStreamBits, .-MVC_CalcStreamBits
	.align	3
.LC330:
	.xword	.LC329
	.align	3
.LC332:
	.xword	.LC331
	.align	3
.LC334:
	.xword	.LC333
	.align	3
.LC336:
	.xword	.LC335
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_Scaling_List
	.type	MVC_Scaling_List, %function
MVC_Scaling_List:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 104]
	mov	x0, x30
	mov	w27, w3
	mov	x28, x1
	mov	x25, x2
	mov	x22, x4
	bl	_mcount
	cmp	w27, wzr
	ble	.L2105
	sub	w26, w27, #1
	mov	w0, 8
	ldr	x21, .LC337
	add	x26, x26, 1
	mov	x20, 0
	mov	w24, w0
	mov	w23, 255
	b	.L2110
	.p2align 3
.L2109:
	lsr	w6, w19, 2
	str	w24, [x28, w19, uxtw 2]
	ubfiz	w1, w19, 3, 2
	and	w4, w24, 255
	lsl	w5, w23, w1
	lsl	w4, w4, w1
	ldr	w1, [x25, w6, sxtw 2]
	cmp	x26, x20
	bic	w1, w1, w5
	orr	w1, w1, w4
	str	w1, [x25, w6, sxtw 2]
	beq	.L2105
.L2110:
	cmp	w27, 16
	add	x1, x21, 16
	beq	.L2118
	ldrb	w19, [x20, x1]
.L2108:
	add	x20, x20, 1
	cbz	w0, .L2109
	ldr	x1, .LC339
	ldr	x0, [x29, 104]
	bl	mvc_se_v
	add	w0, w0, w24
	and	w0, w0, 255
	cmp	w19, wzr
	ccmp	w0, wzr, 0, eq
	cset	w1, eq
	cmp	w0, wzr
	csel	w24, w24, w0, eq
	str	w1, [x22]
	b	.L2109
	.p2align 3
.L2118:
	ldrb	w19, [x21, x20]
	b	.L2108
	.p2align 3
.L2105:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	MVC_Scaling_List, .-MVC_Scaling_List
	.align	3
.LC337:
	.xword	.LANCHOR0
	.align	3
.LC339:
	.xword	.LC338
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessPPS
	.type	MVC_ProcessPPS, %function
MVC_ProcessPPS:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC343
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2168
	ldr	x1, .LC345
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 1]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2168
	ldr	x1, .LC347
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 32]
	cbnz	w0, .L2123
	ldrb	w0, [x19, 10]
	cbz	w0, .L2124
.L2123:
	ldr	x1, .LC349
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC350
	ldr	x4, [x0]
	cbz	x4, .L2168
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L2121:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2124:
	ldr	x1, .LC352
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 31
	str	w0, [x20, 36]
	bhi	.L2125
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2125
	ldr	x1, .LC356
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 31
	str	w0, [x20, 40]
	bhi	.L2127
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2127
	ldr	x1, .LC360
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 2]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2168
	ldr	x2, .LC362
	mov	w1, 2
	mov	x0, x19
	bl	mvc_u_v
	cmp	w0, 2
	str	w0, [x20, 44]
	bhi	.L2169
	ldr	x1, .LC366
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 48]
	ldr	x1, .LC368
	mov	x0, x19
	bl	mvc_se_v
	ldr	x1, .LC370
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 52]
	ldr	x1, .LC372
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 3]
	ldr	x1, .LC374
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 4]
	ldr	x1, .LC376
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 17]
	cbnz	w0, .L2170
.L2130:
	ldr	w0, [x20, 52]
	stp	w0, wzr, [x20, 56]
	strb	wzr, [x20, 18]
	add	x0, x19, 872
	bl	BsResidBits
	ldr	x1, [x19, 240]
	ldr	w1, [x1, 80]
	add	w1, w1, 3
	cmp	w0, w1
	bcc	.L2151
	ldr	x1, .LC380
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x20, 60]
	ldr	x1, .LC382
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 18]
	beq	.L2132
.L2150:
	ldr	x1, .LC384
	mov	x0, x19
	bl	mvc_se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x20, 56]
	bhi	.L2133
	ldrb	w0, [x19, 10]
	cbz	w0, .L2151
.L2133:
	ldr	x1, .LC391
	mov	w0, 1
	bl	dprint_vfmw
.L2168:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2151:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2170:
	ldr	x1, .LC378
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2130
	.p2align 3
.L2125:
	ldr	x1, .LC354
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2121
	.p2align 3
.L2127:
	ldr	x1, .LC358
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2121
	.p2align 3
.L2132:
	ldr	x27, .LC387
	add	x21, x29, 120
	ldr	x25, .LC386
	add	x23, x20, 5
	add	x22, x20, 2016
	add	x24, x20, 64
	mov	w26, 0
	mov	x28, x27
	b	.L2141
	.p2align 3
.L2174:
	ldr	w0, [x20, 28]
	mov	x2, 16
	umull	x0, w0, w3
	ldr	x3, [x19, 272]
	add	x3, x3, x0
	ldr	x0, .LC341
	add	x1, x0, 16
	mov	x0, x22
	ldrb	w4, [x3, 27]
	cmp	w4, 1
	beq	.L2171
	ldr	x4, .LC341
	cmp	w26, wzr
	ldr	x3, [x28, 104]
	csel	x1, x1, x4, ne
	blr	x3
.L2136:
	add	w26, w26, 1
	add	x21, x21, 4
	cmp	w26, 6
	add	x23, x23, 1
	add	x22, x22, 16
	add	x24, x24, 64
	beq	.L2172
.L2141:
	mov	x1, x25
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x23]
	cmp	w0, 1
	str	w0, [x21]
	mov	w3, 3992
	beq	.L2173
	cmp	w26, wzr
	ccmp	w26, 3, 4, ne
	beq	.L2174
	sub	w1, w26, #1
	ldr	x3, [x27, 104]
	add	x1, x1, 126
	mov	x0, x22
	mov	x2, 16
	add	x1, x20, x1, lsl 4
	blr	x3
	b	.L2136
	.p2align 3
.L2172:
	ldr	x21, .LC387
	add	x26, x20, 2112
	ldr	x23, .LC341
	add	x28, x20, 448
	mov	x27, 0
	add	x22, x29, 112
	mov	w24, 3992
	mov	x25, x21
.L2149:
	ldr	w0, [x20, 60]
	mov	w8, w27
	cmp	w0, 1
	beq	.L2175
	add	x0, x20, x27
	str	wzr, [x22, x27, lsl 2]
	strb	wzr, [x0, 11]
.L2144:
	ldr	w0, [x20, 28]
	ldr	x1, [x19, 272]
	umull	x0, w0, w24
	add	x0, x1, x0
	ldrb	w1, [x0, 27]
	cmp	w1, 1
	beq	.L2176
	add	x1, x23, 96
	ldr	x3, [x21, 104]
	cbz	w8, .L2177
.L2148:
	mov	x2, 64
	mov	x0, x26
	blr	x3
.L2145:
	add	x27, x27, 1
	add	x26, x26, 64
	cmp	x27, 2
	add	x28, x28, 256
	bne	.L2149
	b	.L2150
	.p2align 3
.L2173:
	mov	x0, x19
	mov	x4, x21
	mov	x2, x22
	mov	x1, x24
	mov	w3, 16
	bl	MVC_Scaling_List
	ldr	w0, [x21]
	cmp	w0, 1
	bne	.L2136
	ldr	x0, .LC341
	cmp	w26, 2
	mov	x2, 16
	add	x1, x0, 16
	csel	x1, x0, x1, ls
	ldr	x0, .LC387
	ldr	x3, [x0, 104]
	mov	x0, x22
	blr	x3
	b	.L2136
.L2171:
	uxtw	x1, w26
	ldr	x0, .LC387
	add	x1, x1, 167
	add	x1, x3, x1, lsl 4
	ldr	x3, [x0, 104]
	mov	x0, x22
	blr	x3
	b	.L2136
.L2169:
	ldr	x1, .LC364
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2121
.L2175:
	ldr	x1, .LC389
	mov	x0, x19
	str	w27, [x29, 108]
	bl	mvc_u_1
	cmp	w0, 1
	add	x1, x20, x27
	str	w0, [x22, x27, lsl 2]
	ldr	w8, [x29, 108]
	strb	w0, [x1, 11]
	bne	.L2144
	mov	x0, x19
	add	x4, x22, x27, lsl 2
	mov	w3, 64
	mov	x2, x26
	mov	x1, x28
	str	w8, [x29, 108]
	bl	MVC_Scaling_List
	ldr	w0, [x22, x27, lsl 2]
	ldr	w8, [x29, 108]
	cmp	w0, 1
	bne	.L2145
	ldr	x0, .LC387
	ldr	x3, [x0, 104]
	ldr	x0, .LC341
	add	x1, x0, 96
	cbnz	w8, .L2148
	add	x1, x0, 32
	b	.L2148
	.p2align 3
.L2176:
	ubfiz	x1, x8, 6, 32
	ldr	x3, [x25, 104]
	add	x1, x1, 2768
	mov	x2, 64
	add	x1, x0, x1
	mov	x0, x26
	blr	x3
	b	.L2145
.L2177:
	ldr	x1, .LC341
	add	x1, x1, 32
	b	.L2148
	.size	MVC_ProcessPPS, .-MVC_ProcessPPS
	.align	3
.LC341:
	.xword	.LANCHOR1
	.align	3
.LC343:
	.xword	.LC342
	.align	3
.LC345:
	.xword	.LC344
	.align	3
.LC347:
	.xword	.LC346
	.align	3
.LC349:
	.xword	.LC348
	.align	3
.LC350:
	.xword	g_event_report
	.align	3
.LC352:
	.xword	.LC351
	.align	3
.LC354:
	.xword	.LC353
	.align	3
.LC356:
	.xword	.LC355
	.align	3
.LC358:
	.xword	.LC357
	.align	3
.LC360:
	.xword	.LC359
	.align	3
.LC362:
	.xword	.LC361
	.align	3
.LC364:
	.xword	.LC363
	.align	3
.LC366:
	.xword	.LC365
	.align	3
.LC368:
	.xword	.LC367
	.align	3
.LC370:
	.xword	.LC369
	.align	3
.LC372:
	.xword	.LC371
	.align	3
.LC374:
	.xword	.LC373
	.align	3
.LC376:
	.xword	.LC375
	.align	3
.LC378:
	.xword	.LC377
	.align	3
.LC380:
	.xword	.LC379
	.align	3
.LC382:
	.xword	.LC381
	.align	3
.LC384:
	.xword	.LC383
	.align	3
.LC386:
	.xword	.LC385
	.align	3
.LC387:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC389:
	.xword	.LC388
	.align	3
.LC391:
	.xword	.LC390
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PPSEqual
	.type	MVC_PPSEqual, %function
MVC_PPSEqual:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L2200
	cbz	x20, .L2201
	ldrb	w3, [x19]
	ldrb	w2, [x20]
	ldrb	w1, [x19, 1]
	ldrb	w0, [x20, 1]
	cmp	w3, w2
	ldp	w4, w2, [x19, 24]
	ccmp	w1, w0, 0, eq
	ldr	w5, [x19, 36]
	ldp	w3, w0, [x20, 24]
	cset	w1, eq
	ldrb	w7, [x19, 2]
	cmp	w4, w3
	ldr	w3, [x19, 40]
	ccmp	w2, w0, 0, eq
	ldr	w6, [x19, 48]
	ldp	w4, w0, [x20, 36]
	cset	w2, eq
	ldr	w12, [x19, 60]
	cmp	w5, w4
	ldrb	w5, [x20, 2]
	ccmp	w3, w0, 0, eq
	ldr	w3, [x19, 44]
	cset	w4, eq
	cmp	w7, w5
	ldp	w0, w5, [x20, 44]
	ldr	w7, [x19, 52]
	and	w1, w1, w2
	ccmp	w3, w0, 0, eq
	ldr	w3, [x20, 52]
	cset	w0, eq
	cmp	w6, w5
	ldrb	w5, [x20, 3]
	and	w1, w4, w1
	ldrb	w6, [x19, 3]
	ccmp	w7, w3, 0, eq
	cset	w3, eq
	and	w0, w0, w1
	cmp	w6, w5
	ldrb	w1, [x20, 4]
	ldrb	w5, [x19, 4]
	and	w0, w3, w0
	ldr	w4, [x20, 60]
	ccmp	w5, w1, 0, eq
	ldrb	w2, [x19, 18]
	ldrb	w3, [x20, 18]
	cset	w1, eq
	cmp	w4, w12
	and	w0, w1, w0
	ccmp	w3, w2, 0, eq
	cset	w1, eq
	and	w0, w1, w0
	cbz	w2, .L2182
	lsl	w12, w12, 1
	cmn	w12, #6
	beq	.L2182
	add	x10, x19, 1984
	add	x9, x20, 1984
	mov	x11, x20
	add	x7, x19, 64
	mov	w8, -6
	mov	x1, 0
	.p2align 2
.L2187:
	add	x3, x19, x1
	add	x2, x20, x1
	ldrsb	w3, [x3, 5]
	ldrsb	w2, [x2, 5]
	cmp	w2, w3
	cset	w2, eq
	and	w0, w0, w2
	cbz	w3, .L2183
	cmp	w1, 5
	bhi	.L2184
	ldr	w3, [x9]
	ldr	w2, [x10]
	cmp	w3, w2
	cset	w3, eq
	and	w0, w0, w3
	cbnz	w2, .L2183
	sub	x2, x7, #64
	mov	x3, x11
	.p2align 2
.L2185:
	ldr	w5, [x2, 64]
	add	x2, x2, 4
	ldr	w4, [x3, 64]
	add	x3, x3, 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x7, x2
	and	w0, w0, w4
	bne	.L2185
	.p2align 2
.L2183:
	add	w8, w8, 1
	add	x1, x1, 1
	cmp	w8, w12
	add	x10, x10, 4
	add	x9, x9, 4
	add	x11, x11, 64
	add	x7, x7, 64
	bne	.L2187
.L2182:
	ldr	w1, [x20, 56]
	ldr	w2, [x19, 56]
	cmp	w2, w1
	cset	w1, eq
	tst	w1, w0
	csetm	w0, eq
.L2180:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2184:
	uxtw	x2, w8
	add	x3, x2, 500
	lsl	x3, x3, 2
	add	x4, x19, x3
	add	x3, x20, x3
	ldr	w4, [x4, 8]
	ldr	w3, [x3, 8]
	cmp	w3, w4
	cset	w3, eq
	and	w0, w0, w3
	cbnz	w4, .L2183
	lsl	x2, x2, 8
	add	x3, x2, 448
	add	x2, x2, 704
	add	x6, x19, x2
	add	x2, x19, x3
	add	x3, x20, x3
	.p2align 2
.L2186:
	ldr	w5, [x2], 4
	ldr	w4, [x3], 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x6, x2
	and	w0, w0, w4
	bne	.L2186
	add	w8, w8, 1
	add	x1, x1, 1
	cmp	w8, w12
	add	x10, x10, 4
	add	x9, x9, 4
	add	x11, x11, 64
	add	x7, x7, 64
	bne	.L2187
	b	.L2182
.L2201:
	ldr	x2, .LC392
	mov	w3, 9880
	ldr	x1, .LC393
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2180
.L2200:
	ldr	x2, .LC392
	mov	w3, 9879
	ldr	x1, .LC393
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2180
	.size	MVC_PPSEqual, .-MVC_PPSEqual
	.align	3
.LC392:
	.xword	.LC36
	.align	3
.LC393:
	.xword	.LC38
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecPPS
	.type	MVC_DecPPS, %function
MVC_DecPPS:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC395
	mov	x0, x19
	bl	mvc_ue_v
	mov	w20, w0
	ldr	w0, [x19, 40]
	sub	w0, w0, #1
	cmp	w20, w0
	bls	.L2203
	ldr	x1, .LC397
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 40]
	sub	w0, w1, #1
	cmp	w20, w0
	bls	.L2210
	ldr	x0, .LC398
	ldr	x4, [x0]
	cbz	x4, .L2210
	ldr	w0, [x19, 120]
	mov	w3, 8
	stp	w20, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 110
	blr	x4
	mov	w0, -1
.L2204:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2203:
	ldr	x1, .LC400
	mov	x0, x19
	bl	mvc_ue_v
	mov	w2, w0
	ldr	w0, [x19, 36]
	sub	w0, w0, #1
	cmp	w2, w0
	bhi	.L2214
	mov	w21, 2240
	ldr	x0, [x19, 280]
	umull	x21, w20, w21
	add	x0, x0, x21
	ldrb	w1, [x0, 19]
	cbz	w1, .L2206
	ldr	x22, .LC403
	mov	x0, x19
	mov	x1, x22
	stp	w20, w2, [x22, 24]
	bl	MVC_ProcessPPS
	cbnz	w0, .L2215
	ldr	x1, [x19, 280]
	mov	x0, x22
	add	x1, x1, x21
	bl	MVC_PPSEqual
	cbz	w0, .L2204
	ldr	x3, .LC406
	mov	w1, 1
	ldr	x0, [x19, 280]
	mov	x2, 2240
	strb	w1, [x22, 20]
	ldr	x3, [x3, 112]
	add	x0, x0, x21
	strb	w1, [x22, 19]
	mov	x1, x22
	blr	x3
	mov	w0, 0
	b	.L2204
	.p2align 3
.L2206:
	str	w20, [x0, 24]
	mov	x0, x19
	ldr	x1, [x19, 280]
	add	x1, x1, x21
	str	w2, [x1, 28]
	ldr	x1, [x19, 280]
	add	x1, x1, x21
	bl	MVC_ProcessPPS
	cbnz	w0, .L2216
	ldr	x1, [x19, 280]
	mov	w2, 1
	add	x1, x1, x21
	strb	w2, [x1, 20]
	ldr	x1, [x19, 280]
	add	x21, x1, x21
	strb	w2, [x21, 19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2210:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 64
	ret
.L2214:
	ldr	x1, .LC402
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2204
.L2215:
	ldr	x1, .LC405
	mov	w2, 9644
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2204
.L2216:
	ldr	x1, .LC405
	mov	w2, 9663
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 280]
	mov	w2, 1
	mov	w0, -1
	add	x1, x1, x21
	strb	w2, [x1, 20]
	ldr	x1, [x19, 280]
	add	x21, x1, x21
	strb	wzr, [x21, 19]
	b	.L2204
	.size	MVC_DecPPS, .-MVC_DecPPS
	.align	3
.LC395:
	.xword	.LC394
	.align	3
.LC397:
	.xword	.LC396
	.align	3
.LC398:
	.xword	g_event_report
	.align	3
.LC400:
	.xword	.LC399
	.align	3
.LC402:
	.xword	.LC401
	.align	3
.LC403:
	.xword	.LANCHOR2
	.align	3
.LC405:
	.xword	.LC404
	.align	3
.LC406:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	mvc_vui_parameters
	.type	mvc_vui_parameters, %function
mvc_vui_parameters:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x1, .LC408
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20]
	cbnz	w0, .L2259
	strb	wzr, [x20, 15]
.L2219:
	ldr	x1, .LC416
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 1]
	cbnz	w0, .L2260
.L2220:
	ldr	x1, .LC420
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 3]
	cbnz	w0, .L2261
	mov	w0, 5
	str	w0, [x20, 28]
.L2222:
	ldr	x1, .LC434
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 6]
	cbnz	w0, .L2262
.L2223:
	ldr	x1, .LC440
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 8]
	cbnz	w0, .L2263
.L2225:
	ldr	x1, .LC448
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 7]
	cbz	w0, .L2227
	ldr	x1, .LC450
	mov	x0, x19
	add	x24, x20, 60
	bl	mvc_ue_v
	ldr	x2, .LC452
	mov	w1, 4
	str	w0, [x24, 36]
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x24, 32]
	ldr	x2, .LC454
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x24, 33]
	ldr	w1, [x24, 36]
	cmp	w1, 31
	bhi	.L2230
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2230
	ldr	x27, .LC458
	mov	w21, 0
	ldr	x26, .LC460
	ldr	x25, .LC462
	.p2align 2
.L2231:
	uxtw	x22, w21
	mov	x1, x27
	mov	x0, x19
	add	w21, w21, 1
	add	x23, x20, x22, lsl 2
	bl	mvc_ue_v
	mov	x1, x26
	str	w0, [x23, 100]
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x23, 228]
	mov	x1, x25
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x24, x22]
	ldr	w0, [x24, 36]
	cmp	w0, w21
	bcs	.L2231
	ldr	x2, .LC464
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 296]
	ldr	x2, .LC466
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 300]
	ldr	x2, .LC468
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 304]
	ldr	x2, .LC470
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 308]
.L2227:
	ldr	x1, .LC472
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 10]
	cbnz	w0, .L2264
	ldrb	w0, [x20, 7]
	cbz	w0, .L2235
.L2236:
	ldr	x1, .LC474
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 14]
.L2235:
	ldr	x1, .LC476
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 11]
	ldr	x1, .LC478
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 12]
	cbnz	w0, .L2237
	ldrb	w0, [x19, 10]
.L2238:
	cmp	w0, wzr
	csetm	w0, ne
.L2258:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2263:
	ldr	x2, .LC442
	mov	w1, 32
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 52]
	ldr	x2, .LC444
	mov	w1, 32
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 56]
	ldr	x1, .LC446
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 9]
	ldr	w1, [x20, 52]
	cbz	w1, .L2225
	ldr	w2, [x20, 56]
	lsl	w0, w2, 6
	sub	w0, w0, w2
	lsl	w0, w0, 1
	sub	w0, w0, w2
	lsl	w0, w0, 3
	udiv	w0, w0, w1
	lsr	w0, w0, 1
	str	w0, [x19, 56]
	b	.L2225
	.p2align 3
.L2262:
	ldr	x1, .LC436
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 44]
	ldr	x1, .LC438
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 48]
	b	.L2223
	.p2align 3
.L2261:
	ldr	x2, .LC422
	mov	w1, 3
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 28]
	ldr	x1, .LC424
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 4]
	ldr	x1, .LC426
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 5]
	cbz	w0, .L2222
	ldr	x2, .LC428
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 32]
	ldr	x2, .LC430
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 36]
	ldr	x2, .LC432
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 40]
	b	.L2222
	.p2align 3
.L2260:
	ldr	x1, .LC418
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 2]
	b	.L2220
	.p2align 3
.L2259:
	ldr	x2, .LC410
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	uxtb	w0, w0
	cmp	w0, 255
	strb	w0, [x20, 15]
	bne	.L2219
	ldr	x2, .LC412
	mov	w1, 16
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 16]
	ldr	x2, .LC414
	mov	w1, 16
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 20]
	b	.L2219
	.p2align 3
.L2264:
	ldr	x1, .LC450
	mov	x0, x19
	add	x24, x20, 372
	bl	mvc_ue_v
	ldr	x2, .LC452
	mov	w1, 4
	str	w0, [x24, 36]
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x24, 32]
	ldr	x2, .LC454
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x24, 33]
	ldr	w1, [x24, 36]
	cmp	w1, 31
	bhi	.L2230
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2230
	ldr	x27, .LC458
	mov	w21, 0
	ldr	x26, .LC460
	ldr	x25, .LC462
	.p2align 2
.L2233:
	uxtw	x22, w21
	mov	x1, x27
	mov	x0, x19
	add	w21, w21, 1
	add	x23, x20, x22, lsl 2
	bl	mvc_ue_v
	mov	x1, x26
	str	w0, [x23, 412]
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x23, 540]
	mov	x1, x25
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x24, x22]
	ldr	w0, [x24, 36]
	cmp	w0, w21
	bcs	.L2233
	ldr	x2, .LC464
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 296]
	ldr	x2, .LC466
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 300]
	ldr	x2, .LC468
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 304]
	ldr	x2, .LC470
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x24, 308]
	ldrb	w0, [x20, 7]
	cbnz	w0, .L2236
	ldrb	w0, [x20, 10]
	cbnz	w0, .L2236
	b	.L2235
	.p2align 3
.L2237:
	ldr	x1, .LC480
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 13]
	ldr	x1, .LC482
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 684]
	ldr	x1, .LC484
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 688]
	ldr	x1, .LC486
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 696]
	ldr	x1, .LC488
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 692]
	ldr	x1, .LC490
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 700]
	ldr	x1, .LC492
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 704]
	ldrb	w0, [x19, 10]
	cbz	w0, .L2238
	mov	w0, -1
	b	.L2258
.L2230:
	ldr	x1, .LC456
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2258
	.size	mvc_vui_parameters, .-mvc_vui_parameters
	.align	3
.LC408:
	.xword	.LC407
	.align	3
.LC410:
	.xword	.LC409
	.align	3
.LC412:
	.xword	.LC411
	.align	3
.LC414:
	.xword	.LC413
	.align	3
.LC416:
	.xword	.LC415
	.align	3
.LC418:
	.xword	.LC417
	.align	3
.LC420:
	.xword	.LC419
	.align	3
.LC422:
	.xword	.LC421
	.align	3
.LC424:
	.xword	.LC423
	.align	3
.LC426:
	.xword	.LC425
	.align	3
.LC428:
	.xword	.LC427
	.align	3
.LC430:
	.xword	.LC429
	.align	3
.LC432:
	.xword	.LC431
	.align	3
.LC434:
	.xword	.LC433
	.align	3
.LC436:
	.xword	.LC435
	.align	3
.LC438:
	.xword	.LC437
	.align	3
.LC440:
	.xword	.LC439
	.align	3
.LC442:
	.xword	.LC441
	.align	3
.LC444:
	.xword	.LC443
	.align	3
.LC446:
	.xword	.LC445
	.align	3
.LC448:
	.xword	.LC447
	.align	3
.LC450:
	.xword	.LC449
	.align	3
.LC452:
	.xword	.LC451
	.align	3
.LC454:
	.xword	.LC453
	.align	3
.LC456:
	.xword	.LC455
	.align	3
.LC458:
	.xword	.LC457
	.align	3
.LC460:
	.xword	.LC459
	.align	3
.LC462:
	.xword	.LC461
	.align	3
.LC464:
	.xword	.LC463
	.align	3
.LC466:
	.xword	.LC465
	.align	3
.LC468:
	.xword	.LC467
	.align	3
.LC470:
	.xword	.LC469
	.align	3
.LC472:
	.xword	.LC471
	.align	3
.LC474:
	.xword	.LC473
	.align	3
.LC476:
	.xword	.LC475
	.align	3
.LC478:
	.xword	.LC477
	.align	3
.LC480:
	.xword	.LC479
	.align	3
.LC482:
	.xword	.LC481
	.align	3
.LC484:
	.xword	.LC483
	.align	3
.LC486:
	.xword	.LC485
	.align	3
.LC488:
	.xword	.LC487
	.align	3
.LC490:
	.xword	.LC489
	.align	3
.LC492:
	.xword	.LC491
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_SPSEqual
	.type	MVC_SPSEqual, %function
MVC_SPSEqual:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L2297
	cbz	x20, .L2298
	ldr	w3, [x19, 736]
	ldr	w2, [x20, 736]
	ldrb	w1, [x19]
	ldrb	w0, [x20]
	cmp	w3, w2
	ldrb	w4, [x19, 1]
	ldrb	w2, [x20, 1]
	ccmp	w1, w0, 0, eq
	ldrb	w1, [x19, 2]
	cset	w3, eq
	ldrb	w0, [x20, 2]
	cmp	w4, w2
	ldr	w6, [x19, 740]
	ccmp	w1, w0, 0, eq
	ldr	w5, [x20, 740]
	cset	w0, eq
	ldr	w2, [x20, 744]
	ldr	w4, [x19, 744]
	and	w0, w3, w0
	ldrb	w1, [x19, 27]
	cmp	w6, w5
	ldrb	w3, [x20, 27]
	ccmp	w4, w2, 0, eq
	cset	w2, eq
	cmp	w3, w1
	and	w0, w2, w0
	cset	w2, eq
	and	w0, w2, w0
	cbz	w1, .L2269
	mov	x2, x19
	mov	x8, x20
	mov	w9, -6
	mov	x1, 0
	.p2align 2
.L2274:
	add	x4, x19, x1
	add	x3, x20, x1
	add	x6, x2, 64
	ldrsb	w3, [x3, 6]
	ldrsb	w4, [x4, 6]
	cmp	w3, w4
	cset	w3, eq
	and	w0, w0, w3
	cbz	w4, .L2270
	cmp	w1, 5
	bhi	.L2271
	mov	x3, x8
	.p2align 2
.L2272:
	ldr	w5, [x2, 752]
	add	x2, x2, 4
	ldr	w4, [x3, 752]
	add	x3, x3, 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x2, x6
	and	w0, w0, w4
	bne	.L2272
.L2270:
	add	x1, x1, 1
	add	w9, w9, 1
	cmp	x1, 8
	mov	x2, x6
	add	x8, x8, 64
	bne	.L2274
.L2269:
	ldr	w4, [x19, 2896]
	ldr	w3, [x20, 2896]
	ldr	w2, [x20, 2900]
	ldr	w1, [x19, 2900]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w0, w2, w0
	cbz	w1, .L2276
	cmp	w1, 1
	bne	.L2275
	ldrb	w4, [x19, 18]
	ldrb	w3, [x20, 18]
	ldr	w2, [x19, 2908]
	ldr	w1, [x20, 2908]
	cmp	w4, w3
	ldr	w5, [x19, 2912]
	ldr	w4, [x20, 2912]
	ccmp	w2, w1, 0, eq
	ldr	w2, [x20, 2916]
	cset	w3, eq
	ldr	w1, [x19, 2916]
	cmp	w5, w4
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w2, w3, w2
	and	w0, w0, w2
	cbz	w1, .L2275
	sub	w5, w1, #1
	add	x2, x20, 2920
	add	x5, x5, 731
	add	x1, x19, 2920
	add	x5, x19, x5, lsl 2
	.p2align 2
.L2278:
	ldr	w4, [x1], 4
	ldr	w3, [x2], 4
	cmp	w4, w3
	cset	w3, eq
	cmp	x1, x5
	and	w0, w0, w3
	bne	.L2278
.L2275:
	ldr	w4, [x19, 3944]
	ldr	w3, [x20, 3944]
	ldrb	w2, [x19, 19]
	ldrb	w1, [x20, 19]
	cmp	w4, w3
	ldr	w6, [x19, 3948]
	ldr	w4, [x20, 3948]
	ccmp	w2, w1, 0, eq
	ldr	w5, [x19, 3952]
	cset	w2, eq
	ldr	w1, [x20, 3952]
	cmp	w6, w4
	ldrb	w3, [x19, 20]
	ldrb	w4, [x20, 20]
	ccmp	w5, w1, 0, eq
	cset	w1, eq
	cmp	w4, w3
	and	w2, w2, w1
	cset	w1, eq
	and	w1, w2, w1
	and	w0, w1, w0
	cbnz	w3, .L2279
	ldrb	w1, [x20, 21]
	ldrb	w2, [x19, 21]
	cmp	w2, w1
	cset	w1, eq
	and	w0, w0, w1
.L2279:
	ldrb	w4, [x19, 22]
	ldrb	w3, [x20, 22]
	ldrb	w2, [x20, 23]
	ldrb	w1, [x19, 23]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w0, w2, w0
	cbnz	w1, .L2299
.L2280:
	ldrb	w4, [x19, 24]
	ldrb	w3, [x20, 24]
	ldr	w1, [x20, 52]
	ldr	w2, [x19, 52]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w1, eq
	tst	w1, w0
	csetm	w0, eq
.L2267:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2299:
	ldr	w4, [x19, 3964]
	ldr	w3, [x20, 3964]
	ldr	w2, [x19, 3968]
	ldr	w1, [x20, 3968]
	cmp	w4, w3
	ldr	w5, [x19, 3956]
	ldr	w4, [x20, 3956]
	ccmp	w2, w1, 0, eq
	ldr	w3, [x19, 3960]
	cset	w2, eq
	ldr	w1, [x20, 3960]
	cmp	w5, w4
	ccmp	w3, w1, 0, eq
	cset	w1, eq
	and	w1, w2, w1
	and	w0, w0, w1
	b	.L2280
	.p2align 3
.L2271:
	ubfiz	x3, x9, 8, 32
	add	x4, x3, 1136
	add	x7, x3, 1392
	add	x7, x19, x7
	add	x3, x19, x4
	add	x4, x20, x4
	.p2align 2
.L2273:
	ldr	w6, [x3], 4
	ldr	w5, [x4], 4
	cmp	w6, w5
	cset	w5, eq
	cmp	x3, x7
	and	w0, w0, w5
	bne	.L2273
	add	x1, x1, 1
	add	x6, x2, 64
	cmp	x1, 8
	add	w9, w9, 1
	mov	x2, x6
	add	x8, x8, 64
	bne	.L2274
	b	.L2269
	.p2align 3
.L2276:
	ldr	w1, [x20, 2904]
	ldr	w2, [x19, 2904]
	cmp	w2, w1
	cset	w1, eq
	and	w0, w0, w1
	b	.L2275
.L2298:
	ldr	x2, .LC493
	mov	w3, 10123
	ldr	x1, .LC494
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2267
.L2297:
	ldr	x2, .LC493
	mov	w3, 10122
	ldr	x1, .LC494
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2267
	.size	MVC_SPSEqual, .-MVC_SPSEqual
	.align	3
.LC493:
	.xword	.LC36
	.align	3
.LC494:
	.xword	.LC38
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetDar
	.type	MVC_GetDar, %function
MVC_GetDar:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	mov	w23, w3
	mov	w22, w4
	bl	_mcount
	cbz	w20, .L2311
	mov	w0, 255
	cmp	w20, 16
	ccmp	w20, w0, 4, gt
	bne	.L2311
	cmp	w19, wzr
	ccmp	w21, wzr, 4, ne
	ccmp	w20, w0, 0, eq
	beq	.L2311
	cmp	w20, 1
	beq	.L2312
	cmp	w20, w0
	beq	.L2302
	ldr	x0, .LC495
	sbfiz	x20, x20, 3, 32
	add	x0, x0, 104
	add	x1, x0, x20
	ldr	w19, [x0, x20]
	ldr	w21, [x1, 4]
.L2302:
	mul	w19, w19, w23
	mul	w2, w21, w22
	lsl	w19, w19, 10
	sdiv	w2, w19, w2
	subs	w1, w2, #2406
	bmi	.L2322
.L2303:
	subs	w0, w2, #2263
	bmi	.L2323
	cmp	w1, w0
	mov	w19, 4
	blt	.L2301
.L2307:
	subs	w1, w2, #1820
	bmi	.L2324
	cmp	w0, w1
	mov	w19, 3
	blt	.L2301
.L2308:
	subs	w0, w2, #1365
	bmi	.L2325
.L2306:
	mov	w19, 2
	cmp	w1, w0
	csinc	w19, w19, wzr, lt
	b	.L2301
	.p2align 3
.L2311:
	mov	w19, 0
	mov	w2, 0
.L2301:
	ldr	x1, .LC497
	mov	w3, w19
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2312:
	mov	w19, 5
	mov	w2, 0
	b	.L2301
	.p2align 3
.L2323:
	mov	w0, 2263
	mov	w19, 4
	sub	w0, w0, w2
	cmp	w1, w0
	blt	.L2301
	b	.L2307
	.p2align 3
.L2322:
	mov	w1, 2406
	sub	w1, w1, w2
	b	.L2303
	.p2align 3
.L2324:
	mov	w1, 1820
	mov	w19, 3
	sub	w1, w1, w2
	cmp	w0, w1
	blt	.L2301
	b	.L2308
.L2325:
	mov	w0, 1365
	sub	w0, w0, w2
	b	.L2306
	.size	MVC_GetDar, .-MVC_GetDar
	.align	3
.LC495:
	.xword	.LANCHOR0
	.align	3
.LC497:
	.xword	.LC496
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSPS
	.type	MVC_ProcessSPS, %function
MVC_ProcessSPS:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L2445
	ldr	w0, [x20, 736]
	mov	w3, 128
	mov	w2, 100
	sub	w1, w0, #110
	and	w4, w0, -17
	and	w1, w1, -9
	cmp	w1, wzr
	ccmp	w4, w3, 4, ne
	cset	w1, eq
	cmp	w0, 122
	ccmp	w0, w2, 4, ne
	cset	w0, eq
	orr	w0, w1, w0
	cbnz	w0, .L2446
	mov	w0, 1
	strb	wzr, [x20, 27]
	str	w0, [x20, 748]
.L2339:
	ldr	x1, .LC523
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 12
	str	w0, [x20, 2896]
	bhi	.L2352
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2352
	ldr	x1, .LC527
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 2
	str	w0, [x20, 2900]
	bhi	.L2354
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2354
	cbz	w0, .L2447
	cmp	w0, 1
	beq	.L2448
.L2358:
	ldr	x1, .LC585
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3944]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2443
	ldr	x1, .LC547
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 19]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2443
	ldr	x1, .LC549
	mov	x0, x19
	bl	mvc_ue_v
	sub	w1, w0, #1
	cmp	w1, 509
	str	w0, [x20, 3948]
	bhi	.L2365
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2365
	ldr	x1, .LC553
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3952]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2443
	ldr	x1, .LC555
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 20]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2443
	cbnz	w0, .L2449
	ldr	x1, .LC587
	mov	x0, x19
	bl	mvc_u_1
	ldr	w22, [x20, 3952]
	strb	w0, [x20, 21]
	add	w22, w22, 1
	cmp	w22, 255
	bhi	.L2399
	ldr	w3, [x20, 3948]
	cmp	w22, 1
	mov	w23, 2
	add	w3, w3, 1
	ccmp	w3, 3, 0, hi
	cset	w0, ls
	cbz	w0, .L2369
.L2399:
	ldr	x1, .LC557
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
	.p2align 3
.L2446:
	ldr	x1, .LC503
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 1
	str	w0, [x20, 748]
	bhi	.L2330
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2330
	ldr	x1, .LC507
	mov	x0, x19
	bl	mvc_ue_v
	cbnz	w0, .L2332
	ldrb	w0, [x19, 10]
	cbz	w0, .L2333
.L2332:
	ldr	x1, .LC509
	mov	w0, 1
	bl	dprint_vfmw
.L2333:
	ldr	x1, .LC511
	mov	x0, x19
	bl	mvc_ue_v
	cbnz	w0, .L2334
	ldrb	w0, [x19, 10]
	cbz	w0, .L2335
.L2334:
	ldr	x1, .LC513
	mov	w0, 1
	bl	dprint_vfmw
.L2335:
	ldr	x1, .LC515
	mov	x0, x19
	bl	mvc_u_1
	cbnz	w0, .L2336
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2336
	ldr	x1, .LC519
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 27]
	bne	.L2339
	ldr	x25, .LC499
	add	x21, x29, 120
	ldr	x26, .LC520
	add	x23, x20, 6
	add	x22, x20, 2672
	add	x24, x20, 752
	mov	w28, 0
	ldr	x27, .LC521
	b	.L2345
	.p2align 3
.L2452:
	ldr	x0, .LC499
	cmp	w28, wzr
	ldr	x3, [x27, 104]
	mov	x2, 16
	csel	x1, x0, x1, eq
	mov	x0, x22
	blr	x3
.L2341:
	add	w28, w28, 1
	add	x21, x21, 4
	cmp	w28, 6
	add	x23, x23, 1
	add	x22, x22, 16
	add	x24, x24, 64
	beq	.L2450
.L2345:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x23]
	cmp	w0, 1
	str	w0, [x21]
	add	x1, x25, 16
	beq	.L2451
	cmp	w28, wzr
	ccmp	w28, 3, 4, ne
	beq	.L2452
	ldr	x0, .LC521
	sub	w1, w28, #1
	add	x1, x1, 167
	mov	x2, 16
	add	w28, w28, 1
	add	x21, x21, 4
	ldr	x3, [x0, 104]
	add	x1, x20, x1, lsl 4
	mov	x0, x22
	add	x23, x23, 1
	add	x22, x22, 16
	add	x24, x24, 64
	blr	x3
	cmp	w28, 6
	bne	.L2345
.L2450:
	ldr	x24, .LC521
	add	x21, x20, 2768
	ldr	x23, .LC499
	add	x22, x20, 1136
	mov	x27, 0
	add	x25, x29, 104
	mov	x28, x24
.L2350:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_u_1
	cmp	w0, 1
	add	x2, x20, x27
	str	w0, [x25, x27, lsl 2]
	add	x1, x23, 96
	strb	w0, [x2, 12]
	beq	.L2453
	ldr	x3, [x24, 104]
	cbz	w27, .L2454
.L2349:
	mov	x0, x21
	mov	x2, 64
.L2439:
	blr	x3
.L2347:
	add	x27, x27, 1
	add	x21, x21, 64
	cmp	x27, 2
	add	x22, x22, 256
	bne	.L2350
	b	.L2339
	.p2align 3
.L2396:
	ldr	w2, [x0, 732]
	ldr	w1, [x0, 736]
	cmp	w24, w2
	ccmp	w22, w1, 2, ls
	bls	.L2395
	ldr	x0, .LC583
	ldr	x4, [x0]
	cbz	x4, .L2443
	ldr	w0, [x19, 120]
	mov	w3, 8
	strh	w2, [x29, 116]
	add	x2, x29, 112
	strh	w1, [x29, 118]
	mov	w1, 107
	strh	w24, [x29, 112]
	strh	w22, [x29, 114]
	blr	x4
	.p2align 2
.L2443:
	mov	w0, -1
.L2435:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2449:
	ldr	w22, [x20, 3952]
	strb	wzr, [x20, 21]
	sub	w0, w22, #1
	cmp	w0, 509
	bhi	.L2399
	ldr	w3, [x20, 3948]
	mov	w23, 1
	add	w22, w22, 1
	add	w3, w3, w23
.L2369:
	mul	w22, w23, w22
	lsl	w24, w3, 4
	mov	w1, 100663296
	lsl	w22, w22, 4
	mul	w0, w24, w22
	lsr	w0, w0, 1
	lsl	w21, w0, 2
	sub	w0, w21, w0
	cmp	w0, w1
	bhi	.L2455
	ldr	w2, [x20, 740]
	sub	w1, w2, #10
	cmp	w1, 31
	bls	.L2456
.L2371:
	ldr	x1, .LC562
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
	.p2align 3
.L2447:
	ldr	x1, .LC531
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 12
	str	w0, [x20, 2904]
	bhi	.L2357
	ldrb	w0, [x19, 10]
	cbz	w0, .L2358
.L2357:
	ldr	x1, .LC533
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
	.p2align 3
.L2456:
	ldr	x3, .LC560
	ldrh	w1, [x3,w1,uxtw #1]
	adr	x3, .Lrtx2373
	add	x1, x3, w1, sxth #2
	br	x1
.Lrtx2373:
	.section	.rodata
	.align	0
	.align	2
.L2373:
	.2byte	(.L2372 - .Lrtx2373) / 4
	.2byte	(.L2406 - .Lrtx2373) / 4
	.2byte	(.L2375 - .Lrtx2373) / 4
	.2byte	(.L2375 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2375 - .Lrtx2373) / 4
	.2byte	(.L2376 - .Lrtx2373) / 4
	.2byte	(.L2378 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2378 - .Lrtx2373) / 4
	.2byte	(.L2379 - .Lrtx2373) / 4
	.2byte	(.L2380 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2371 - .Lrtx2373) / 4
	.2byte	(.L2382 - .Lrtx2373) / 4
	.2byte	(.L2382 - .Lrtx2373) / 4
	.text
	.p2align 3
.L2375:
	mov	w21, 60416
	movk	w21, 0xd, lsl 16
.L2374:
	udiv	w21, w21, w0
	mov	w2, 16
	ldr	x1, .LC564
	mov	w0, 21
	cmp	w21, w2
	csel	w21, w21, w2, ls
	mov	w2, w21
	bl	dprint_vfmw
	ldr	w2, [x20, 3944]
	cmp	w2, w21
	bhi	.L2383
	ldrb	w0, [x19, 10]
	cbz	w0, .L2384
.L2383:
	ldr	x1, .LC566
	mov	w3, w21
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x20, 3944]
	cmp	w0, 16
	bhi	.L2440
	cmp	w21, w0
	csel	w21, w21, w0, cs
.L2440:
	str	w21, [x20, 3944]
.L2384:
	ldr	x1, .LC568
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 22]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2443
	ldr	x1, .LC570
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 23]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2443
	cbnz	w0, .L2457
.L2386:
	add	x2, x20, 3840
	lsr	w1, w24, 1
	lsr	w0, w22, 1
	stp	w24, w22, [x2, 136]
	stp	w1, w0, [x2, 144]
.L2388:
	ldr	x1, .LC580
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 24]
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2443
	mov	w1, 2
	str	w1, [x20, 68]
	cbnz	w0, .L2458
	mov	w0, 5
	strb	wzr, [x20, 43]
	str	w0, [x20, 56]
	mov	w0, 0
.L2391:
	ldp	w1, w2, [x20, 44]
	mov	w4, w22
	mov	w3, w24
	bl	MVC_GetDar
	str	w0, [x20, 52]
	ldr	w1, [x20, 3944]
	cbz	w1, .L2394
	cmp	w21, w1
	csel	w21, w21, w1, ls
.L2394:
	ldr	x0, [x19, 224]
	cmp	w21, 16
	mov	w1, 16
	csel	w21, w21, w1, ls
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L2459
.L2395:
	cmp	w22, 1919
	bls	.L2397
	mov	w0, 4
	cmp	w21, w0
	csel	w21, w21, w0, ls
.L2397:
	add	w21, w21, 1
	str	w21, [x20, 3972]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2382:
	mov	w21, 12582912
	b	.L2374
	.p2align 3
.L2378:
	mov	w21, 30208
	movk	w21, 0x2f, lsl 16
	b	.L2374
	.p2align 3
.L2451:
	mov	x0, x19
	mov	x4, x21
	mov	x2, x22
	mov	x1, x24
	mov	w3, 16
	bl	MVC_Scaling_List
	ldr	w0, [x21]
	cmp	w0, 1
	bne	.L2341
	ldr	x0, .LC499
	cmp	w28, 2
	mov	x2, 16
	add	x1, x0, 16
	csel	x1, x0, x1, ls
	ldr	x0, .LC521
	ldr	x3, [x0, 104]
	mov	x0, x22
	blr	x3
	b	.L2341
	.p2align 3
.L2330:
	ldr	x1, .LC505
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2352:
	ldr	x1, .LC525
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
	.p2align 3
.L2457:
	ldr	x1, .LC572
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3956]
	ldr	x1, .LC574
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3960]
	ldr	x1, .LC576
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3964]
	ldr	x1, .LC578
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 3968]
	ldr	w1, [x20, 3964]
	ldr	w2, [x20, 3956]
	lsl	w1, w1, 1
	ldr	w3, [x20, 3960]
	lsl	w2, w2, 1
	mul	w1, w1, w23
	sub	w4, w24, w2
	lsl	w23, w23, 1
	sub	w3, w4, w3, lsl 1
	sub	w4, w22, w1
	cmp	w3, wzr
	msub	w0, w23, w0, w4
	ccmp	w0, wzr, 4, gt
	ble	.L2386
	add	x4, x20, 3840
	add	w2, w2, w3, lsr 1
	add	w1, w1, w0, lsr 1
	stp	w3, w0, [x4, 136]
	stp	w2, w1, [x4, 144]
	b	.L2388
	.p2align 3
.L2458:
	add	x1, x20, 28
	mov	x0, x19
	bl	mvc_vui_parameters
	cbnz	w0, .L2442
	ldrb	w0, [x20, 40]
	cbz	w0, .L2442
	ldr	w2, [x20, 732]
	cmp	w2, wzr
	ccmp	w21, w2, 0, ne
	bcc	.L2460
	ldr	w21, [x20, 3944]
	ldrb	w0, [x20, 43]
	cmp	w21, w2
	csel	w21, w21, w2, cs
	b	.L2391
.L2460:
	ldr	x1, .LC582
	mov	w3, w21
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L2442:
	ldrb	w0, [x20, 43]
	b	.L2391
	.p2align 3
.L2459:
	ldr	w1, [x0, 772]
	cbnz	w1, .L2395
	ldr	w1, [x0, 756]
	cmp	w21, w1
	bls	.L2396
	ldr	x0, .LC583
	ldr	x4, [x0]
	cbz	x4, .L2443
	ldr	w0, [x19, 120]
	mov	w3, 8
	stp	w21, w1, [x29, 112]
	add	x2, x29, 112
	mov	w1, 106
	blr	x4
	mov	w0, -1
	b	.L2435
	.p2align 3
.L2336:
	ldr	x1, .LC517
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
	.p2align 3
.L2448:
	ldr	x1, .LC535
	mov	x0, x19
	bl	mvc_u_1
	strb	w0, [x20, 18]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2443
	ldr	x1, .LC537
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 2908]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2443
	ldr	x1, .LC539
	mov	x0, x19
	bl	mvc_se_v
	str	w0, [x20, 2912]
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2443
	ldr	x1, .LC541
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 255
	str	w0, [x20, 2916]
	bhi	.L2361
	ldrb	w1, [x19, 10]
	cbnz	w1, .L2361
	cbz	w0, .L2358
	ldr	x22, .LC545
	mov	w21, 0
	b	.L2364
	.p2align 3
.L2461:
	ldr	w0, [x20, 2916]
	cmp	w0, w21
	bls	.L2358
.L2364:
	mov	x1, x22
	mov	x0, x19
	bl	mvc_se_v
	add	x1, x20, x21, uxtw 2
	add	w21, w21, 1
	str	w0, [x1, 2920]
	ldrb	w0, [x19, 10]
	cbz	w0, .L2461
	b	.L2443
	.p2align 3
.L2365:
	ldr	x1, .LC551
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
	.p2align 3
.L2406:
	mov	w21, 17920
	movk	w21, 0x5, lsl 16
	b	.L2374
	.p2align 3
.L2379:
	mov	w21, 30720
	movk	w21, 0x69, lsl 16
	b	.L2374
	.p2align 3
.L2376:
	mov	w21, 55296
	movk	w21, 0x1b, lsl 16
	b	.L2374
	.p2align 3
.L2372:
	mov	w21, 20992
	movk	w21, 0x2, lsl 16
	b	.L2374
	.p2align 3
.L2380:
	mov	w21, 7864320
	b	.L2374
.L2361:
	ldr	x1, .LC543
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
	.p2align 3
.L2453:
	mov	x0, x19
	add	x4, x25, x27, lsl 2
	mov	x2, x21
	mov	x1, x22
	mov	w3, 64
	bl	MVC_Scaling_List
	ldr	w0, [x25, x27, lsl 2]
	cmp	w0, 1
	bne	.L2347
	ldr	x1, .LC499
	mov	x2, 64
	mov	x0, x21
	ldr	x3, [x28, 104]
	add	x1, x1, 96
	cbnz	w27, .L2439
	ldr	x1, .LC499
	add	x1, x1, 32
	b	.L2439
	.p2align 3
.L2354:
	ldr	x1, .LC529
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
.L2455:
	ldr	x1, .LC559
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
.L2445:
	ldr	x2, .LC500
	mov	w3, 10311
	ldr	x1, .LC501
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2435
.L2454:
	ldr	x1, .LC499
	add	x1, x1, 32
	b	.L2349
	.size	MVC_ProcessSPS, .-MVC_ProcessSPS
	.align	3
.LC499:
	.xword	.LANCHOR1
	.align	3
.LC500:
	.xword	.LC36
	.align	3
.LC501:
	.xword	.LC38
	.align	3
.LC503:
	.xword	.LC502
	.align	3
.LC505:
	.xword	.LC504
	.align	3
.LC507:
	.xword	.LC506
	.align	3
.LC509:
	.xword	.LC508
	.align	3
.LC511:
	.xword	.LC510
	.align	3
.LC513:
	.xword	.LC512
	.align	3
.LC515:
	.xword	.LC514
	.align	3
.LC517:
	.xword	.LC516
	.align	3
.LC519:
	.xword	.LC518
	.align	3
.LC520:
	.xword	.LC385
	.align	3
.LC521:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC523:
	.xword	.LC522
	.align	3
.LC525:
	.xword	.LC524
	.align	3
.LC527:
	.xword	.LC526
	.align	3
.LC529:
	.xword	.LC528
	.align	3
.LC531:
	.xword	.LC530
	.align	3
.LC533:
	.xword	.LC532
	.align	3
.LC535:
	.xword	.LC534
	.align	3
.LC537:
	.xword	.LC536
	.align	3
.LC539:
	.xword	.LC538
	.align	3
.LC541:
	.xword	.LC540
	.align	3
.LC543:
	.xword	.LC542
	.align	3
.LC545:
	.xword	.LC544
	.align	3
.LC547:
	.xword	.LC546
	.align	3
.LC549:
	.xword	.LC548
	.align	3
.LC551:
	.xword	.LC550
	.align	3
.LC553:
	.xword	.LC552
	.align	3
.LC555:
	.xword	.LC554
	.align	3
.LC557:
	.xword	.LC556
	.align	3
.LC559:
	.xword	.LC558
	.align	3
.LC560:
	.xword	.L2373
	.align	3
.LC562:
	.xword	.LC561
	.align	3
.LC564:
	.xword	.LC563
	.align	3
.LC566:
	.xword	.LC565
	.align	3
.LC568:
	.xword	.LC567
	.align	3
.LC570:
	.xword	.LC569
	.align	3
.LC572:
	.xword	.LC571
	.align	3
.LC574:
	.xword	.LC573
	.align	3
.LC576:
	.xword	.LC575
	.align	3
.LC578:
	.xword	.LC577
	.align	3
.LC580:
	.xword	.LC579
	.align	3
.LC582:
	.xword	.LC581
	.align	3
.LC583:
	.xword	g_event_report
	.align	3
.LC585:
	.xword	.LC584
	.align	3
.LC587:
	.xword	.LC586
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecSPS
	.type	MVC_DecSPS, %function
MVC_DecSPS:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC589
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	mov	w21, w0
	ldr	x1, .LC591
	mov	x0, x19
	bl	mvc_u_1
	mov	w27, w0
	ldr	x1, .LC593
	mov	x0, x19
	bl	mvc_u_1
	mov	w26, w0
	ldr	x1, .LC595
	mov	x0, x19
	bl	mvc_u_1
	mov	w25, w0
	ldr	x1, .LC597
	mov	x0, x19
	bl	mvc_u_1
	mov	w24, w0
	ldr	x1, .LC599
	mov	x0, x19
	bl	mvc_u_1
	mov	w23, w0
	ldr	x1, .LC601
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x29, 108]
	ldr	x2, .LC603
	mov	w1, 2
	mov	x0, x19
	bl	mvc_u_v
	ldr	x2, .LC605
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	mov	w20, w0
	ldr	x1, .LC607
	mov	x0, x19
	bl	mvc_ue_v
	mov	w22, w0
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2500
	ldr	w0, [x19, 36]
	sub	w0, w0, #1
	cmp	w22, w0
	bhi	.L2502
	cmp	w21, 100
	mov	w28, w21
	beq	.L2468
	bgt	.L2469
	cmp	w21, 77
	beq	.L2468
	cmp	w21, 88
	beq	.L2470
	cmp	w21, 66
	bne	.L2467
	ldr	x1, .LC611
	mov	w0, 1
	bl	dprint_vfmw
.L2468:
	cmp	w20, 9
	mov	w2, w20
	bls	.L2499
.L2505:
	cmp	w20, 41
	bhi	.L2499
	mov	w20, 3992
	ldr	x0, [x19, 272]
	umull	x20, w22, w20
	add	x0, x0, x20
	ldrb	w1, [x0, 25]
	cbz	w1, .L2475
.L2506:
	ldr	x21, .LC620
	mov	x0, x19
	ldrb	w3, [x29, 108]
	add	x21, x21, 2240
	strb	w27, [x21]
	str	w28, [x21, 736]
	mov	x1, x21
	strb	w26, [x21, 1]
	strb	w25, [x21, 2]
	strb	w24, [x21, 3]
	strb	w23, [x21, 4]
	strb	w3, [x21, 5]
	str	w2, [x21, 740]
	str	w22, [x21, 744]
	bl	MVC_ProcessSPS
	cbnz	w0, .L2503
	ldr	x1, [x19, 272]
	mov	x0, x21
	add	x1, x1, x20
	bl	MVC_SPSEqual
	cbnz	w0, .L2504
.L2464:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2469:
	cmp	w21, 122
	beq	.L2472
	cmp	w21, 144
	beq	.L2472
	cmp	w21, 110
	beq	.L2472
.L2467:
	ldr	x1, .LC617
	mov	w2, w21
	mov	w0, 1
	mov	w28, 100
	bl	dprint_vfmw
	cmp	w20, 9
	mov	w2, w20
	bhi	.L2505
	.p2align 2
.L2499:
	ldr	x1, .LC619
	mov	w3, 41
	mov	w0, 1
	mov	w20, 3992
	bl	dprint_vfmw
	umull	x20, w22, w20
	ldr	x0, [x19, 272]
	mov	w2, 41
	add	x0, x0, x20
	ldrb	w1, [x0, 25]
	cbnz	w1, .L2506
.L2475:
	str	w28, [x0, 736]
	mov	x0, x19
	ldrb	w3, [x29, 108]
	ldr	x1, [x19, 272]
	strb	w27, [x1, x20]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w26, [x1, 1]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w25, [x1, 2]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w24, [x1, 3]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w23, [x1, 4]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	strb	w3, [x1, 5]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	str	w2, [x1, 740]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	str	w22, [x1, 744]
	ldr	x1, [x19, 272]
	add	x1, x1, x20
	bl	MVC_ProcessSPS
	cbnz	w0, .L2507
	ldr	x1, [x19, 272]
	mov	w2, 1
	add	x1, x1, x20
	strb	w2, [x1, 26]
	ldr	x1, [x19, 272]
	add	x20, x1, x20
	strb	w2, [x20, 25]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2502:
	ldr	x1, .LC608
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 36]
	sub	w0, w1, #1
	cmp	w22, w0
	bls	.L2500
	ldr	x0, .LC609
	ldr	x5, [x0]
	cbz	x5, .L2500
	ldr	w0, [x19, 120]
	mov	w3, 8
	stp	w22, w1, [x29, 120]
	add	x2, x29, 120
	mov	w1, 109
	blr	x5
.L2500:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2472:
	ldr	x1, .LC615
	mov	w0, 1
	bl	dprint_vfmw
	cmp	w20, 9
	mov	w2, w20
	bhi	.L2505
	b	.L2499
	.p2align 3
.L2470:
	ldr	x1, .LC613
	mov	w0, 1
	bl	dprint_vfmw
	cmp	w20, 9
	mov	w2, w20
	bhi	.L2505
	b	.L2499
	.p2align 3
.L2504:
	ldr	x3, .LC623
	mov	w1, 1
	ldr	x0, [x19, 272]
	mov	x2, 3992
	strb	w1, [x21, 26]
	ldr	x3, [x3, 112]
	add	x0, x0, x20
	strb	w1, [x21, 25]
	mov	x1, x21
	blr	x3
	mov	w0, 0
	b	.L2464
	.p2align 3
.L2503:
	ldr	x1, .LC622
	mov	w3, w22
	mov	w2, 10841
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2464
.L2507:
	ldr	x1, .LC622
	mov	w2, 10868
	mov	w3, w22
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 272]
	mov	w2, 1
	mov	w0, -1
	add	x1, x1, x20
	strb	w2, [x1, 26]
	ldr	x1, [x19, 272]
	add	x20, x1, x20
	strb	wzr, [x20, 25]
	b	.L2464
	.size	MVC_DecSPS, .-MVC_DecSPS
	.align	3
.LC589:
	.xword	.LC588
	.align	3
.LC591:
	.xword	.LC590
	.align	3
.LC593:
	.xword	.LC592
	.align	3
.LC595:
	.xword	.LC594
	.align	3
.LC597:
	.xword	.LC596
	.align	3
.LC599:
	.xword	.LC598
	.align	3
.LC601:
	.xword	.LC600
	.align	3
.LC603:
	.xword	.LC602
	.align	3
.LC605:
	.xword	.LC604
	.align	3
.LC607:
	.xword	.LC606
	.align	3
.LC608:
	.xword	.LC401
	.align	3
.LC609:
	.xword	g_event_report
	.align	3
.LC611:
	.xword	.LC610
	.align	3
.LC613:
	.xword	.LC612
	.align	3
.LC615:
	.xword	.LC614
	.align	3
.LC617:
	.xword	.LC616
	.align	3
.LC619:
	.xword	.LC618
	.align	3
.LC620:
	.xword	.LANCHOR2
	.align	3
.LC622:
	.xword	.LC621
	.align	3
.LC623:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FreeMvcExtMem
	.type	MVC_FreeMvcExtMem, %function
MVC_FreeMvcExtMem:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MVC_FreeMvcExtMem, .-MVC_FreeMvcExtMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FreeMvcVuiExtMem
	.type	MVC_FreeMvcVuiExtMem, %function
MVC_FreeMvcVuiExtMem:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	MVC_FreeMvcVuiExtMem, .-MVC_FreeMvcVuiExtMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSUBSPSMvcExt
	.type	MVC_ProcessSUBSPSMvcExt, %function
MVC_ProcessSUBSPSMvcExt:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2570
	ldr	x1, .LC628
	mov	x0, x20
	bl	mvc_ue_v
	cmp	w0, 1
	str	w0, [x19, 4]
	bhi	.L2513
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2513
	ldr	x22, .LC632
	mov	w21, 0
	.p2align 2
.L2515:
	mov	x1, x22
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x19, x21, uxtw 2
	add	w21, w21, 1
	str	w0, [x1, 8]
	ldr	w0, [x19, 4]
	cmp	w0, w21
	bcs	.L2515
	str	wzr, [x19, 16]
	str	wzr, [x19, 24]
	cbz	w0, .L2516
	ldr	x27, .LC634
	mov	w25, 1
	ldr	x23, .LC640
	mov	w26, 15
	ldr	x24, .LC644
	.p2align 2
.L2526:
	uxtw	x22, w25
	mov	x1, x27
	mov	x0, x20
	add	x21, x19, x22, lsl 2
	bl	mvc_ue_v
	str	w0, [x21, 16]
	ldr	w1, [x19, 4]
	cmp	w1, 15
	csel	w1, w1, w26, ls
	cmp	w0, w1
	bhi	.L2517
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2517
	mov	w28, 0
	cbz	w0, .L2522
	.p2align 2
.L2521:
	mov	x1, x23
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x22, x28, uxtw
	add	w28, w28, 1
	add	x1, x1, 8
	str	w0, [x19, x1, lsl 2]
	ldr	w0, [x21, 16]
	cmp	w28, w0
	bcc	.L2521
.L2522:
	ldr	x1, .LC636
	mov	x0, x20
	bl	mvc_ue_v
	str	w0, [x21, 24]
	ldr	w1, [x19, 4]
	cmp	w1, 15
	csel	w2, w1, w26, ls
	cmp	w0, w2
	bhi	.L2519
	ldrb	w2, [x20, 10]
	cbnz	w2, .L2519
	mov	w28, 0
	cbz	w0, .L2524
	.p2align 2
.L2525:
	mov	x1, x24
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x22, x28, uxtw
	add	w28, w28, 1
	add	x1, x1, 10
	str	w0, [x19, x1, lsl 2]
	ldr	w0, [x21, 24]
	cmp	w28, w0
	bcc	.L2525
	ldr	w1, [x19, 4]
.L2524:
	add	w25, w25, 1
	cmp	w1, w25
	bcs	.L2526
	str	wzr, [x19, 48]
	str	wzr, [x19, 56]
	cbz	w1, .L2540
	ldr	x27, .LC648
	mov	w25, 1
	ldr	x23, .LC654
	mov	w26, 15
	ldr	x24, .LC658
	.p2align 2
.L2539:
	uxtw	x22, w25
	mov	x1, x27
	mov	x0, x20
	add	x21, x19, x22, lsl 2
	bl	mvc_ue_v
	str	w0, [x21, 48]
	ldr	w1, [x19, 4]
	cmp	w1, 15
	csel	w1, w1, w26, ls
	cmp	w0, w1
	bhi	.L2530
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2530
	mov	w28, 0
	cbz	w0, .L2535
	.p2align 2
.L2534:
	mov	x1, x23
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x22, x28, uxtw
	add	w28, w28, 1
	add	x1, x1, 16
	str	w0, [x19, x1, lsl 2]
	ldr	w0, [x21, 48]
	cmp	w28, w0
	bcc	.L2534
.L2535:
	ldr	x1, .LC650
	mov	x0, x20
	bl	mvc_ue_v
	str	w0, [x21, 56]
	ldr	w1, [x19, 4]
	cmp	w1, 15
	csel	w2, w1, w26, ls
	cmp	w0, w2
	bhi	.L2532
	ldrb	w2, [x20, 10]
	cbnz	w2, .L2532
	mov	w28, 0
	cbz	w0, .L2537
	.p2align 2
.L2538:
	mov	x1, x24
	mov	x0, x20
	bl	mvc_ue_v
	add	x1, x22, x28, uxtw
	add	w28, w28, 1
	add	x1, x1, 18
	str	w0, [x19, x1, lsl 2]
	ldr	w0, [x21, 56]
	cmp	w28, w0
	bcc	.L2538
	ldr	w1, [x19, 4]
.L2537:
	add	w25, w25, 1
	cmp	w25, w1
	bls	.L2539
.L2540:
	ldr	x1, .LC646
	mov	x0, x20
	bl	mvc_ue_v
	add	w1, w0, 1
	cmp	w1, 16
	str	w0, [x19, 80]
	str	w1, [x29, 140]
	bhi	.L2528
	ldrb	w0, [x20, 10]
	cbnz	w0, .L2528
	ldr	w0, [x29, 140]
	cbz	w0, .L2545
	add	x0, x19, 8192
	ldr	x22, .LC676
	add	x1, x19, 84
	add	x0, x0, 212
	stp	x1, x19, [x29, 120]
	stp	xzr, x0, [x29, 104]
	str	wzr, [x29, 144]
.L2544:
	ldr	x2, .LC662
	mov	w1, 8
	mov	x0, x20
	bl	mvc_u_v
	ldr	x21, [x29, 120]
	ldr	x1, .LC664
	str	w0, [x21]
	mov	x0, x20
	bl	mvc_ue_v
	add	w27, w0, 1
	cmp	w27, 64
	str	w0, [x21, 64]
	bhi	.L2542
	ldrb	w0, [x20, 10]
	cbnz	w0, .L2542
	cbz	w27, .L2553
	ldp	x26, x25, [x29, 104]
	ldr	x23, [x29, 128]
	mov	w24, 0
.L2543:
	ldr	x2, .LC668
	mov	w1, 3
	mov	x0, x20
	bl	mvc_u_v
	str	w0, [x23, 212]
	ldr	x1, .LC670
	mov	x0, x20
	bl	mvc_ue_v
	add	w2, w0, 1
	cmp	w2, 64
	str	w0, [x23, 4308]
	bhi	.L2546
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2546
	cbz	w2, .L2551
	add	x21, x26, x0, uxtw
	mov	x28, x25
	add	x21, x21, 2102
	add	x21, x19, x21, lsl 2
	.p2align 2
.L2550:
	mov	x1, x22
	mov	x0, x20
	bl	mvc_ue_v
	str	w0, [x28], 4
	cmp	x28, x21
	bne	.L2550
.L2551:
	ldr	x1, .LC672
	mov	x0, x20
	bl	mvc_ue_v
	cmp	w0, 1023
	add	x1, x23, 270336
	str	w0, [x1, 212]
	bhi	.L2548
	ldrb	w1, [x20, 10]
	cbnz	w1, .L2548
	add	w24, w24, 1
	add	x23, x23, 4
	cmp	w27, w24
	add	x25, x25, 256
	add	x26, x26, 64
	bne	.L2543
.L2553:
	ldr	x1, [x29, 120]
	ldr	w0, [x29, 144]
	add	x1, x1, 4
	str	x1, [x29, 120]
	ldr	w1, [x29, 140]
	add	w0, w0, 1
	str	w0, [x29, 144]
	cmp	w1, w0
	ldr	x0, [x29, 128]
	add	x0, x0, 256
	str	x0, [x29, 128]
	ldr	x0, [x29, 112]
	add	x0, x0, 16384
	str	x0, [x29, 112]
	ldr	x0, [x29, 104]
	add	x0, x0, 4096
	str	x0, [x29, 104]
	bne	.L2544
.L2545:
	mov	w0, 0
	b	.L2565
	.p2align 3
.L2517:
	ldr	x1, .LC638
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2565:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2519:
	ldr	x1, .LC642
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2530:
	ldr	x1, .LC652
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2565
.L2513:
	ldr	x1, .LC630
	mov	w3, 65534
	mov	w2, w0
	str	w3, [x19, 80]
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2565
.L2532:
	ldr	x1, .LC656
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2565
.L2516:
	str	wzr, [x19, 48]
	str	wzr, [x19, 56]
	b	.L2540
.L2548:
	ldr	x1, .LC678
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2565
.L2546:
	ldr	x0, [x29, 144]
	mov	w3, 65534
	ldr	x1, .LC674
	ubfiz	x28, x0, 6, 32
	mov	w0, 1
	add	x24, x28, x24, uxtw
	add	x19, x19, x24, lsl 2
	str	w3, [x19, 4308]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2565
.L2570:
	ldr	x2, .LC625
	mov	w3, 10931
	ldr	x1, .LC626
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2565
.L2528:
	mov	w0, 65534
	ldr	x1, .LC660
	ldr	w2, [x29, 140]
	str	w0, [x19, 80]
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2565
.L2542:
	ldr	x0, [x29, 144]
	mov	w3, 65534
	ldr	x1, .LC666
	mov	w2, w27
	add	x19, x19, x0, uxtw 2
	mov	w0, 1
	str	w3, [x19, 148]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2565
	.size	MVC_ProcessSUBSPSMvcExt, .-MVC_ProcessSUBSPSMvcExt
	.align	3
.LC625:
	.xword	.LC36
	.align	3
.LC626:
	.xword	.LC38
	.align	3
.LC628:
	.xword	.LC627
	.align	3
.LC630:
	.xword	.LC629
	.align	3
.LC632:
	.xword	.LC631
	.align	3
.LC634:
	.xword	.LC633
	.align	3
.LC636:
	.xword	.LC635
	.align	3
.LC638:
	.xword	.LC637
	.align	3
.LC640:
	.xword	.LC639
	.align	3
.LC642:
	.xword	.LC641
	.align	3
.LC644:
	.xword	.LC643
	.align	3
.LC646:
	.xword	.LC645
	.align	3
.LC648:
	.xword	.LC647
	.align	3
.LC650:
	.xword	.LC649
	.align	3
.LC652:
	.xword	.LC651
	.align	3
.LC654:
	.xword	.LC653
	.align	3
.LC656:
	.xword	.LC655
	.align	3
.LC658:
	.xword	.LC657
	.align	3
.LC660:
	.xword	.LC659
	.align	3
.LC662:
	.xword	.LC661
	.align	3
.LC664:
	.xword	.LC663
	.align	3
.LC666:
	.xword	.LC665
	.align	3
.LC668:
	.xword	.LC667
	.align	3
.LC670:
	.xword	.LC669
	.align	3
.LC672:
	.xword	.LC671
	.align	3
.LC674:
	.xword	.LC673
	.align	3
.LC676:
	.xword	.LC675
	.align	3
.LC678:
	.xword	.LC677
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ProcessSUBSPSMvcVuiExt
	.type	MVC_ProcessSUBSPSMvcVuiExt, %function
MVC_ProcessSUBSPSMvcVuiExt:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	x27, x1
	bl	_mcount
	add	x0, x27, 278528
	ldr	x1, .LC680
	mov	x20, x0
	mov	x0, x19
	str	x20, [x29, 120]
	bl	mvc_ue_v
	cmp	w0, 1023
	str	w0, [x20, 560]
	bhi	.L2604
	ldr	x2, [x29, 120]
	uxtw	x0, w0
	add	x0, x0, 1
	add	x1, x27, 294912
	str	x0, [x29, 128]
	add	x0, x2, 432
	ldr	x26, .LC692
	add	x25, x1, 1368
	str	x0, [x29, 184]
	add	x0, x2, 820
	str	x27, [x29, 152]
	stp	x27, x27, [x29, 168]
	str	xzr, [x29, 192]
	str	x0, [x29, 160]
	.p2align 2
.L2590:
	ldr	x3, [x29, 168]
	mov	w1, 3
	ldr	x2, .LC684
	mov	x0, x19
	add	x3, x3, 278528
	mov	x20, x3
	ldr	w3, [x29, 192]
	str	w3, [x29, 148]
	str	x20, [x29, 200]
	bl	mvc_u_v
	strb	w0, [x20, 112]
	ldr	x1, .LC686
	mov	x0, x19
	bl	mvc_ue_v
	cmp	w0, 1023
	ldr	x1, [x29, 176]
	add	x1, x1, 278528
	str	w0, [x1, 564]
	bhi	.L2605
	cmn	w0, #1
	beq	.L2580
	uxtw	x20, w0
	ldr	x0, [x29, 192]
	ldr	x21, [x29, 160]
	add	x20, x20, x0, lsl 6
	add	x20, x20, 69632
	add	x20, x20, 206
	add	x20, x27, x20, lsl 2
	.p2align 2
.L2579:
	mov	x1, x26
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x21], 4
	cmp	x20, x21
	bne	.L2579
.L2580:
	ldr	x1, .LC690
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	ldr	x1, [x29, 200]
	strb	w0, [x1, 368]
	cbnz	w0, .L2606
.L2578:
	ldr	x1, .LC700
	mov	x0, x19
	bl	mvc_u_1
	uxtb	w0, w0
	ldr	x1, [x29, 184]
	strb	w0, [x1]
	cbz	w0, .L2581
	ldr	x2, [x29, 152]
	mov	x0, x19
	ldr	x1, .LC702
	add	x2, x2, 294912
	str	x2, [x29, 136]
	mov	x20, x2
	bl	mvc_ue_v
	str	w0, [x25]
	ldr	x2, .LC704
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 1364]
	ldr	x2, .LC706
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 1365]
	ldr	w0, [x25]
	cmp	w0, 31
	bhi	.L2583
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2583
	ldr	x0, [x29, 192]
	mov	w28, 0
	ldr	w23, [x29, 148]
	and	x24, x0, 4294967295
	ldr	x22, .LC709
	lsl	x1, x24, 3
	lsl	x0, x23, 3
	sub	x1, x1, x24
	sub	x0, x0, x23
	lsl	x1, x1, 1
	lsl	x0, x0, 1
	sub	x1, x1, x24
	sub	x0, x0, x23
	lsl	x24, x1, 2
	lsl	x23, x0, 2
	sub	x24, x24, x1
	sub	x0, x23, x0
	lsl	x1, x24, 1
	str	x1, [x29, 216]
	ldr	x1, [x29, 120]
	mov	w24, w28
	ldr	x21, .LC711
	mov	x28, x25
	add	x23, x1, 112
	ldr	x20, .LC713
	add	x0, x23, x0, lsl 3
	str	x0, [x29, 208]
	.p2align 2
.L2584:
	mov	x1, x22
	mov	x0, x19
	uxtw	x23, w24
	add	w24, w24, 1
	bl	mvc_ue_v
	ldr	x1, [x29, 216]
	add	x1, x1, x23
	add	x1, x27, x1, lsl 2
	add	x25, x1, 294912
	mov	x1, x21
	str	w0, [x25, 1372]
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x25, 1500]
	mov	x1, x20
	mov	x0, x19
	bl	mvc_u_1
	ldr	x1, [x29, 208]
	add	x23, x1, x23
	add	x23, x23, 16384
	strb	w0, [x23, 1220]
	ldr	w0, [x28]
	cmp	w0, w24
	bcs	.L2584
	ldr	x2, .LC715
	mov	w1, 5
	mov	x0, x19
	mov	x25, x28
	bl	mvc_u_v
	ldr	x20, [x29, 136]
	ldr	x2, .LC717
	mov	w1, 5
	str	w0, [x20, 1628]
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1632]
	ldr	x2, .LC719
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1636]
	ldr	x2, .LC721
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1640]
.L2581:
	ldr	x20, [x29, 200]
	mov	x0, x19
	ldr	x1, .LC723
	add	x2, x20, 496
	str	x2, [x29, 136]
	bl	mvc_u_1
	uxtb	w0, w0
	strb	w0, [x20, 496]
	cbnz	w0, .L2607
	ldr	x0, [x29, 184]
	ldrb	w0, [x0]
	cbz	w0, .L2588
.L2589:
	ldr	x1, .LC725
	mov	x0, x19
	bl	mvc_u_1
	ldr	x1, [x29, 200]
	strb	w0, [x1, 176]
.L2588:
	ldr	x2, [x29, 192]
	mov	x0, x19
	ldr	x1, .LC727
	add	x25, x25, 312
	add	x2, x2, 1
	mov	x20, x2
	ldr	x2, [x29, 168]
	str	x20, [x29, 192]
	add	x2, x2, 1
	str	x2, [x29, 168]
	ldr	x2, [x29, 176]
	add	x2, x2, 4
	str	x2, [x29, 176]
	ldr	x2, [x29, 152]
	add	x2, x2, 312
	str	x2, [x29, 152]
	bl	mvc_u_1
	ldr	w1, [x29, 148]
	add	w1, w1, 1
	cmp	w1, 63
	ldr	x1, [x29, 200]
	strb	w0, [x1, 304]
	ldr	x0, [x29, 128]
	ccmp	x0, x20, 0, ls
	ldr	x0, [x29, 184]
	add	x0, x0, 1
	str	x0, [x29, 184]
	ldr	x0, [x29, 160]
	add	x0, x0, 256
	str	x0, [x29, 160]
	bhi	.L2590
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 224
	ret
	.p2align 3
.L2606:
	ldr	x0, [x29, 176]
	mov	w1, 32
	ldr	x2, .LC694
	add	x20, x0, 294912
	mov	x0, x19
	bl	mvc_u_v
	ldr	x2, .LC696
	mov	w1, 32
	str	w0, [x20, 820]
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1076]
	ldr	x1, .LC698
	mov	x0, x19
	bl	mvc_u_1
	ldr	x1, [x29, 200]
	strb	w0, [x1, 240]
	b	.L2578
	.p2align 3
.L2607:
	ldr	x1, .LC702
	mov	x0, x19
	bl	mvc_ue_v
	ldr	x1, [x29, 152]
	ldr	x2, .LC704
	add	x1, x1, 315392
	mov	x20, x1
	str	x20, [x29, 112]
	str	w0, [x1, 856]
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 852]
	ldr	x2, .LC706
	mov	w1, 4
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 853]
	ldr	w0, [x20, 856]
	add	x5, x20, 856
	cmp	w0, 31
	bhi	.L2583
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2583
	ldr	x0, [x29, 192]
	ldr	w23, [x29, 148]
	and	x24, x0, 4294967295
	ldr	x22, .LC709
	lsl	x1, x24, 3
	lsl	x0, x23, 3
	sub	x1, x1, x24
	sub	x0, x0, x23
	lsl	x1, x1, 1
	lsl	x0, x0, 1
	sub	x1, x1, x24
	sub	x0, x0, x23
	lsl	x24, x1, 2
	lsl	x23, x0, 2
	sub	x24, x24, x1
	sub	x0, x23, x0
	lsl	x1, x24, 1
	str	x1, [x29, 216]
	ldr	x1, [x29, 120]
	ldr	x21, .LC711
	add	x23, x1, 112
	ldr	x20, .LC713
	add	x0, x23, x0, lsl 3
	mov	w23, 0
	str	x25, [x29, 104]
	mov	w25, w23
	str	x0, [x29, 208]
	mov	x23, x5
	.p2align 2
.L2586:
	mov	x1, x22
	mov	x0, x19
	uxtw	x24, w25
	add	w25, w25, 1
	bl	mvc_ue_v
	ldr	x1, [x29, 216]
	add	x2, x1, x24
	mov	x1, x21
	add	x2, x27, x2, lsl 2
	add	x28, x2, 315392
	str	w0, [x28, 860]
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x28, 988]
	mov	x1, x20
	mov	x0, x19
	bl	mvc_u_1
	ldr	x1, [x29, 208]
	add	x24, x1, x24
	add	x24, x24, 36864
	strb	w0, [x24, 708]
	ldr	w0, [x23]
	cmp	w0, w25
	bcs	.L2586
	ldr	x2, .LC715
	mov	w1, 5
	mov	x0, x19
	ldr	x25, [x29, 104]
	bl	mvc_u_v
	ldr	x20, [x29, 112]
	ldr	x2, .LC717
	mov	w1, 5
	str	w0, [x20, 1116]
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1120]
	ldr	x2, .LC719
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1124]
	ldr	x2, .LC721
	mov	w1, 5
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 1128]
	ldr	x0, [x29, 184]
	ldrb	w0, [x0]
	cbnz	w0, .L2589
	ldr	x0, [x29, 136]
	ldrb	w0, [x0]
	cbnz	w0, .L2589
	b	.L2588
	.p2align 3
.L2583:
	ldr	x1, .LC707
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2600:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L2605:
	ldr	x1, .LC688
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L2604:
	ldr	x1, .LC682
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2600
	.size	MVC_ProcessSUBSPSMvcVuiExt, .-MVC_ProcessSUBSPSMvcVuiExt
	.align	3
.LC680:
	.xword	.LC679
	.align	3
.LC682:
	.xword	.LC681
	.align	3
.LC684:
	.xword	.LC683
	.align	3
.LC686:
	.xword	.LC685
	.align	3
.LC688:
	.xword	.LC687
	.align	3
.LC690:
	.xword	.LC689
	.align	3
.LC692:
	.xword	.LC691
	.align	3
.LC694:
	.xword	.LC693
	.align	3
.LC696:
	.xword	.LC695
	.align	3
.LC698:
	.xword	.LC697
	.align	3
.LC700:
	.xword	.LC699
	.align	3
.LC702:
	.xword	.LC701
	.align	3
.LC704:
	.xword	.LC703
	.align	3
.LC706:
	.xword	.LC705
	.align	3
.LC707:
	.xword	.LC455
	.align	3
.LC709:
	.xword	.LC708
	.align	3
.LC711:
	.xword	.LC710
	.align	3
.LC713:
	.xword	.LC712
	.align	3
.LC715:
	.xword	.LC714
	.align	3
.LC717:
	.xword	.LC716
	.align	3
.LC719:
	.xword	.LC718
	.align	3
.LC721:
	.xword	.LC720
	.align	3
.LC723:
	.xword	.LC722
	.align	3
.LC725:
	.xword	.LC724
	.align	3
.LC727:
	.xword	.LC726
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecSubSPS
	.type	MVC_DecSubSPS, %function
MVC_DecSubSPS:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC729
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	mov	w20, w0
	ldr	x1, .LC731
	mov	x0, x19
	bl	mvc_u_1
	mov	w27, w0
	ldr	x1, .LC733
	mov	x0, x19
	bl	mvc_u_1
	mov	w26, w0
	ldr	x1, .LC735
	mov	x0, x19
	bl	mvc_u_1
	mov	w25, w0
	ldr	x1, .LC737
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x29, 120]
	ldr	x1, .LC739
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x29, 116]
	ldr	x1, .LC741
	mov	x0, x19
	bl	mvc_u_1
	mov	w22, w0
	ldr	x2, .LC743
	mov	w1, 2
	mov	x0, x19
	bl	mvc_u_v
	ldr	x2, .LC745
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	mov	w21, w0
	ldr	x1, .LC747
	mov	x0, x19
	bl	mvc_ue_v
	mov	w4, w0
	ldrb	w0, [x19, 10]
	cbnz	w0, .L2621
	cmp	w4, 31
	bhi	.L2631
	sub	w0, w20, #66
	cmp	w0, 78
	bls	.L2632
.L2611:
	ldr	x1, .LC754
	mov	w2, w20
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2632:
	ldr	x1, .LC749
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx2613
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2613:
	.section	.rodata
	.align	0
	.align	2
.L2613:
	.byte	(.L2612 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2614 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2615 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2614 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2616 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2614 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2616 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2614 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2611 - .Lrtx2613) / 4
	.byte	(.L2616 - .Lrtx2613) / 4
	.text
	.p2align 3
.L2612:
	ldr	x1, .LC750
	mov	w0, 1
	str	w4, [x29, 104]
	bl	dprint_vfmw
	ldr	w4, [x29, 104]
.L2614:
	cmp	w21, 41
	bhi	.L2633
.L2617:
	uxtw	x23, w4
	mov	x0, x19
	lsl	x1, x23, 3
	sub	x1, x1, x23
	lsl	x1, x1, 2
	sub	x1, x1, x23
	lsl	x1, x1, 4
	sub	x1, x1, x23
	lsl	x2, x1, 2
	sub	x1, x2, x1
	lsl	x2, x1, 6
	add	x2, x1, x2
	lsl	x24, x2, 2
	ldrb	w2, [x29, 120]
	add	x5, x19, x24
	add	x1, x24, 286720
	add	x28, x5, 286720
	add	x1, x19, x1
	add	x1, x1, 2612
	str	x5, [x29, 104]
	strb	w2, [x28, 2615]
	ldrb	w2, [x29, 116]
	str	w21, [x28, 3352]
	strb	w27, [x28, 2612]
	strb	w26, [x28, 2613]
	strb	w25, [x28, 2614]
	strb	w2, [x28, 2616]
	strb	w22, [x28, 2617]
	str	w20, [x28, 3348]
	str	w4, [x28, 3356]
	bl	MVC_ProcessSPS
	mov	w21, w0
	ldr	x5, [x29, 104]
	cbnz	w0, .L2634
	mov	w1, 128
	cmp	w20, 118
	mov	w0, 1
	ccmp	w20, w1, 4, ne
	strb	w0, [x28, 2637]
	beq	.L2635
.L2619:
	lsl	x0, x23, 3
	mov	w2, 1
	sub	x0, x0, x23
	lsl	x0, x0, 2
	sub	x0, x0, x23
	lsl	x0, x0, 4
	sub	x0, x0, x23
	lsl	x1, x0, 2
	sub	x0, x1, x0
	lsl	x1, x0, 6
	add	x0, x0, x1
	add	x19, x19, x0, lsl 2
	add	x19, x19, 12288
	strb	w2, [x19, 2396]
.L2609:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2633:
	ldr	x1, .LC756
	mov	w2, w21
	mov	w0, 1
	str	w4, [x29, 104]
	mov	w21, 41
	bl	dprint_vfmw
	ldr	w4, [x29, 104]
	b	.L2617
	.p2align 3
.L2635:
	ldr	x1, .LC760
	add	x22, x5, 12288
	mov	x0, x19
	add	x20, x24, 12288
	add	x20, x19, x20
	bl	mvc_u_1
	add	x20, x20, 2396
	strb	w0, [x22, 2397]
	mov	x1, x20
	mov	x0, x19
	bl	MVC_ProcessSUBSPSMvcExt
	cbnz	w0, .L2636
	ldr	x1, .LC764
	mov	x0, x19
	bl	mvc_u_1
	str	w0, [x28, 2608]
	cbz	w0, .L2619
	mov	x1, x20
	mov	x0, x19
	bl	MVC_ProcessSUBSPSMvcVuiExt
	cbz	w0, .L2619
	ldr	x1, .LC766
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	strb	wzr, [x22, 2396]
	b	.L2609
	.p2align 3
.L2616:
	ldr	x1, .LC752
	mov	w0, 1
	str	w4, [x29, 104]
	bl	dprint_vfmw
	ldr	w4, [x29, 104]
	b	.L2614
	.p2align 3
.L2615:
	ldr	x1, .LC751
	mov	w0, 1
	str	w4, [x29, 104]
	bl	dprint_vfmw
	ldr	w4, [x29, 104]
	b	.L2614
	.p2align 3
.L2621:
	mov	w21, -1
	b	.L2609
	.p2align 3
.L2631:
	ldr	x1, .LC748
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	b	.L2609
	.p2align 3
.L2634:
	ldr	x1, .LC758
	mov	w0, 1
	str	x5, [x29, 120]
	mov	w21, -1
	bl	dprint_vfmw
	ldr	x5, [x29, 120]
	add	x5, x5, 12288
	strb	wzr, [x5, 2396]
	strb	wzr, [x28, 2637]
	b	.L2609
.L2636:
	ldr	x1, .LC762
	mov	w0, 1
	mov	w21, -1
	bl	dprint_vfmw
	strb	wzr, [x22, 2396]
	b	.L2609
	.size	MVC_DecSubSPS, .-MVC_DecSubSPS
	.align	3
.LC729:
	.xword	.LC728
	.align	3
.LC731:
	.xword	.LC730
	.align	3
.LC733:
	.xword	.LC732
	.align	3
.LC735:
	.xword	.LC734
	.align	3
.LC737:
	.xword	.LC736
	.align	3
.LC739:
	.xword	.LC738
	.align	3
.LC741:
	.xword	.LC740
	.align	3
.LC743:
	.xword	.LC742
	.align	3
.LC745:
	.xword	.LC744
	.align	3
.LC747:
	.xword	.LC746
	.align	3
.LC748:
	.xword	.LC401
	.align	3
.LC749:
	.xword	.L2613
	.align	3
.LC750:
	.xword	.LC610
	.align	3
.LC751:
	.xword	.LC612
	.align	3
.LC752:
	.xword	.LC614
	.align	3
.LC754:
	.xword	.LC753
	.align	3
.LC756:
	.xword	.LC755
	.align	3
.LC758:
	.xword	.LC757
	.align	3
.LC760:
	.xword	.LC759
	.align	3
.LC762:
	.xword	.LC761
	.align	3
.LC764:
	.xword	.LC763
	.align	3
.LC766:
	.xword	.LC765
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_PassBytes
	.type	MVC_PassBytes, %function
MVC_PassBytes:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x0, [x20, 240]
	cmp	w19, wzr
	ccmp	x0, xzr, 4, ne
	beq	.L2646
	ldrb	w2, [x0]
	sbfiz	x1, x2, 5, 32
	add	x1, x0, x1
	ldr	x1, [x1, 8]
	cbz	x1, .L2646
	ldr	w1, [x0, 76]
	cmp	w2, 1
	ccmp	w1, 2, 2, ls
	bhi	.L2646
	cmp	w1, w2
	bls	.L2646
	uxtw	x5, w2
	add	x3, x0, x5, lsl 5
	ldr	w1, [x3, 28]
	ldr	w3, [x3, 16]
	add	w1, w1, w19, lsl 3
	lsl	w3, w3, 3
	cmp	w1, w3
	bhi	.L2641
	b	.L2639
	.p2align 3
.L2642:
	ldr	w4, [x6, 28]
	ldr	w6, [x6, 16]
	sub	w4, w4, w3
	add	w1, w1, w4
	lsl	w3, w6, 3
	cmp	w1, w3
	bls	.L2639
.L2641:
	add	x0, x0, x5, lsl 5
	add	w5, w2, 1
	mov	x2, x5
	str	w3, [x0, 28]
	ldr	x0, [x20, 240]
	ldrb	w4, [x0]
	add	w4, w4, 1
	strb	w4, [x0]
	ldr	x0, [x20, 240]
	add	x6, x0, x5, lsl 5
	ldr	w4, [x0, 76]
	cmp	w4, w5
	bhi	.L2642
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2639:
	add	x5, x0, x5, lsl 5
	mov	w0, 1
	str	w1, [x5, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2646:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_PassBytes, .-MVC_PassBytes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_GetBytes
	.type	MVC_GetBytes, %function
MVC_GetBytes:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x19, x1
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	cbz	x19, .L2662
	ldr	x1, [x21, 240]
	cmp	x1, xzr
	ccmp	w20, wzr, 4, ne
	beq	.L2662
	ldrb	w2, [x1]
	sbfiz	x0, x2, 5, 32
	add	x0, x1, x0
	ldr	x0, [x0, 8]
	cbz	x0, .L2662
	ldr	w0, [x1, 76]
	cmp	w2, 1
	ccmp	w0, 2, 2, ls
	bhi	.L2662
	cmp	w0, w2
	bls	.L2662
	mov	w6, 0
.L2657:
	ubfiz	x7, x2, 5, 32
	add	x3, x1, x7
	ldr	w0, [x3, 28]
	ldr	x4, [x3, 8]
	ldr	w8, [x3, 16]
	add	w0, w0, 7
	ubfx	x0, x0, 3, 29
	add	x8, x4, x8
	add	x5, x4, x0
	cmp	x5, x8
	bcs	.L2652
	ldrb	w0, [x4, x0]
	add	w6, w6, 1
	strb	w0, [x19]
	cmp	w20, w6
	add	x19, x19, 1
	add	x5, x5, 1
	ldr	x0, [x21, 240]
	add	x0, x0, x7
	ldr	w3, [x0, 28]
	add	w3, w3, 8
	str	w3, [x0, 28]
	bhi	.L2655
	b	.L2654
	.p2align 3
.L2656:
	ldrb	w1, [x5], 1
	add	w6, w6, 1
	strb	w1, [x19], 1
	cmp	w20, w6
	ldr	x3, [x21, 240]
	add	x3, x3, x7
	ldr	w4, [x3, 28]
	add	w4, w4, 8
	str	w4, [x3, 28]
	bls	.L2654
.L2655:
	cmp	x8, x5
	bne	.L2656
	ldr	x1, [x21, 240]
.L2652:
	ldrb	w0, [x1]
	add	w2, w2, 1
	add	w0, w0, 1
	strb	w0, [x1]
	ldr	x1, [x21, 240]
	ldr	w0, [x1, 76]
	cmp	w0, w2
	bhi	.L2657
	mov	w0, w6
	b	.L2651
	.p2align 3
.L2654:
	mov	w0, w20
.L2651:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2662:
	mov	w0, -1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_GetBytes, .-MVC_GetBytes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecFramePackingSEI
	.type	MVC_DecFramePackingSEI, %function
MVC_DecFramePackingSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11124736
	bl	_mcount
	add	x20, x21, 392
	ldr	x1, .LC768
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x20, 24]
	ldr	x2, .LC770
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	sxtb	w0, w0
	strb	w0, [x20, 1]
	cbz	w0, .L2670
.L2665:
	ldr	x2, .LC802
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x21, 394]
	mov	w1, 1
	strb	w1, [x21, 392]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2670:
	ldr	x2, .LC772
	mov	w1, 7
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 16]
	ldr	x2, .LC774
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 3]
	ldr	x2, .LC776
	mov	w1, 6
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x20, 20]
	ldr	x2, .LC778
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 4]
	ldr	x2, .LC780
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 5]
	ldr	x2, .LC782
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 6]
	ldr	x2, .LC784
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 7]
	ldr	x2, .LC786
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 8]
	ldr	x2, .LC788
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 9]
	ldrsb	w1, [x20, 3]
	cbnz	w1, .L2666
	ldr	w0, [x20, 16]
	cmp	w0, 5
	beq	.L2666
	ldr	x2, .LC790
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 10]
	ldr	x2, .LC792
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 11]
	ldr	x2, .LC794
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 12]
	ldr	x2, .LC796
	mov	w1, 1
	mov	x0, x19
	bl	mvc_u_v
	strb	w0, [x20, 13]
.L2666:
	ldr	x2, .LC798
	mov	w1, 8
	mov	x0, x19
	bl	mvc_u_v
	str	w0, [x21, 420]
	ldr	x1, .LC800
	mov	x0, x19
	bl	mvc_ue_v
	str	w0, [x21, 424]
	b	.L2665
	.size	MVC_DecFramePackingSEI, .-MVC_DecFramePackingSEI
	.align	3
.LC768:
	.xword	.LC767
	.align	3
.LC770:
	.xword	.LC769
	.align	3
.LC772:
	.xword	.LC771
	.align	3
.LC774:
	.xword	.LC773
	.align	3
.LC776:
	.xword	.LC775
	.align	3
.LC778:
	.xword	.LC777
	.align	3
.LC780:
	.xword	.LC779
	.align	3
.LC782:
	.xword	.LC781
	.align	3
.LC784:
	.xword	.LC783
	.align	3
.LC786:
	.xword	.LC785
	.align	3
.LC788:
	.xword	.LC787
	.align	3
.LC790:
	.xword	.LC789
	.align	3
.LC792:
	.xword	.LC791
	.align	3
.LC794:
	.xword	.LC793
	.align	3
.LC796:
	.xword	.LC795
	.align	3
.LC798:
	.xword	.LC797
	.align	3
.LC800:
	.xword	.LC799
	.align	3
.LC802:
	.xword	.LC801
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecPicTimingSEI
	.type	MVC_DecPicTimingSEI, %function
MVC_DecPicTimingSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 3992
	bl	_mcount
	add	x0, x20, 11112448
	ldr	x3, [x20, 272]
	ldr	w0, [x0, 344]
	umull	x19, w0, w19
	add	x19, x3, x19
	ldrb	w0, [x19, 25]
	cbnz	w0, .L2672
	ldr	w0, [x20, 36]
	cmp	w0, wzr
	ble	.L2673
	ldrb	w1, [x3, 25]
	cbnz	w1, .L2691
	sub	w1, w0, #1
	add	x0, x3, 3992
	add	x1, x1, 1
	lsl	x2, x1, 6
	sub	x2, x2, x1
	lsl	x2, x2, 1
	sub	x2, x2, x1
	lsl	x2, x2, 2
	sub	x1, x2, x1
	add	x1, x3, x1, lsl 3
	b	.L2676
	.p2align 3
.L2677:
	ldrb	w2, [x2]
	cbnz	w2, .L2674
.L2676:
	cmp	x0, x1
	mov	x19, x0
	add	x0, x0, 3992
	sub	x2, x0, #3967
	bne	.L2677
.L2673:
	ldr	x1, .LC804
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
.L2678:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2691:
	mov	x19, x3
	.p2align 2
.L2674:
	cbz	x19, .L2673
.L2672:
	ldrb	w0, [x19, 24]
	cbz	w0, .L2679
	ldrb	w0, [x19, 35]
	cbz	w0, .L2692
	ldr	w1, [x19, 388]
	ldr	w22, [x19, 392]
	add	w1, w1, 1
	add	w22, w22, 1
.L2682:
	ldr	x2, .LC806
	mov	x0, x20
	add	x21, x20, 11124736
	bl	mvc_u_v
	ldr	x2, .LC808
	mov	w1, w22
	str	w0, [x21, 432]
	mov	x0, x20
	bl	mvc_u_v
	str	w0, [x21, 436]
.L2679:
	ldrb	w0, [x19, 39]
	mov	w19, 0
	cbz	w0, .L2678
	ldr	x2, .LC810
	mov	x0, x20
	add	x20, x20, 11124736
	mov	w1, 4
	bl	mvc_u_v
	strb	w0, [x20, 428]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2692:
	ldrb	w0, [x19, 38]
	cbz	w0, .L2679
	ldr	w1, [x19, 700]
	ldr	w22, [x19, 704]
	add	w1, w1, 1
	add	w22, w22, 1
	b	.L2682
	.size	MVC_DecPicTimingSEI, .-MVC_DecPicTimingSEI
	.align	3
.LC804:
	.xword	.LC803
	.align	3
.LC806:
	.xword	.LC805
	.align	3
.LC808:
	.xword	.LC807
	.align	3
.LC810:
	.xword	.LC809
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecSEI
	.type	MVC_DecSEI, %function
MVC_DecSEI:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	add	x21, x29, 128
	mov	w23, 0
	bl	_mcount
	add	x20, x26, 872
	ldr	x0, [x26, 240]
	mov	w1, 32
	strb	wzr, [x21, -1]!
	str	w1, [x0, 28]
	b	.L2696
	.p2align 3
.L2860:
	mov	w1, 8
	mov	x0, x20
	bl	BsSkip
	cmp	w19, wzr
	ble	.L2695
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2859
.L2696:
	mov	w2, 1
	mov	x1, x21
	mov	x0, x26
	bl	MVC_GetBytes
	mov	w19, w0
	ldr	w2, [x26, 896]
	ldr	w0, [x26, 904]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w23, w23, w1
	bls	.L2860
.L2695:
	ldr	x1, .LC812
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2698
	.p2align 3
.L2859:
	ldr	x25, .LC818
	mov	w24, 0
	ldr	x22, .LC815
	add	x0, x25, 240
	str	x0, [x29, 104]
	.p2align 2
.L2833:
	mov	w19, 0
	b	.L2702
	.p2align 3
.L2862:
	mov	w1, 8
	mov	x0, x20
	bl	BsSkip
	cmp	w28, wzr
	ble	.L2700
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2861
.L2702:
	mov	w2, 1
	mov	x1, x21
	mov	x0, x26
	bl	MVC_GetBytes
	mov	w28, w0
	ldr	w2, [x26, 896]
	ldr	w0, [x26, 904]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w19, w19, w1
	bls	.L2862
.L2700:
	ldr	x1, .LC814
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2861:
	cmp	w19, 409600
	bgt	.L2700
	ldr	x0, [x26, 240]
	ldr	w1, [x0, 76]
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L2863
.L2704:
	cmp	w23, 45
	bls	.L2864
.L2705:
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2865
.L2825:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2826
	.p2align 3
.L2827:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2826:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2827
	.p2align 2
.L2731:
	ldr	w0, [x26, 60]
	cmp	w0, 3
	bhi	.L2866
.L2828:
	mov	w23, 0
	b	.L2832
	.p2align 3
.L2830:
	mov	w1, 8
	mov	x0, x20
	bl	BsSkip
	cmp	w19, wzr
	ble	.L2831
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2867
.L2832:
	mov	w2, 1
	mov	x1, x21
	mov	x0, x26
	bl	MVC_GetBytes
	mov	w19, w0
	ldr	w2, [x26, 896]
	ldr	w0, [x26, 904]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w23, w23, w1
	bls	.L2830
.L2831:
	mov	w0, 0
.L2698:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2867:
	cmp	w0, 128
	bne	.L2833
	b	.L2831
	.p2align 3
.L2864:
	ldrh	w0, [x22,w23,uxtw #1]
	adr	x1, .Lrtx2707
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx2707:
	.section	.rodata
	.align	0
	.align	2
.L2707:
	.2byte	(.L2706 - .Lrtx2707) / 4
	.2byte	(.L2708 - .Lrtx2707) / 4
	.2byte	(.L2709 - .Lrtx2707) / 4
	.2byte	(.L2710 - .Lrtx2707) / 4
	.2byte	(.L2711 - .Lrtx2707) / 4
	.2byte	(.L2712 - .Lrtx2707) / 4
	.2byte	(.L2713 - .Lrtx2707) / 4
	.2byte	(.L2714 - .Lrtx2707) / 4
	.2byte	(.L2715 - .Lrtx2707) / 4
	.2byte	(.L2716 - .Lrtx2707) / 4
	.2byte	(.L2717 - .Lrtx2707) / 4
	.2byte	(.L2718 - .Lrtx2707) / 4
	.2byte	(.L2719 - .Lrtx2707) / 4
	.2byte	(.L2720 - .Lrtx2707) / 4
	.2byte	(.L2721 - .Lrtx2707) / 4
	.2byte	(.L2722 - .Lrtx2707) / 4
	.2byte	(.L2723 - .Lrtx2707) / 4
	.2byte	(.L2724 - .Lrtx2707) / 4
	.2byte	(.L2725 - .Lrtx2707) / 4
	.2byte	(.L2726 - .Lrtx2707) / 4
	.2byte	(.L2727 - .Lrtx2707) / 4
	.2byte	(.L2728 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2705 - .Lrtx2707) / 4
	.2byte	(.L2729 - .Lrtx2707) / 4
	.text
.L2729:
	mov	w1, w19
	mov	x0, x26
	ldr	w28, [x26, 904]
	bl	MVC_DecFramePackingSEI
	ldr	w3, [x26, 904]
	sub	w0, w3, w28
	lsl	w28, w19, 3
	cmp	w0, w28
	bge	.L2819
	sub	w28, w28, w0
	ldr	w0, [x26, 896]
	cmp	w28, wzr
	add	w23, w28, 7
	csel	w23, w23, w28, lt
	lsl	w0, w0, 3
	asr	w23, w23, 3
	cmp	w23, wzr
	ble	.L2821
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2821
	mov	w27, 0
	b	.L2822
	.p2align 3
.L2823:
	ldr	w0, [x26, 896]
	ldr	w3, [x26, 904]
	lsl	w0, w0, 3
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2821
.L2822:
	mov	w1, 8
	mov	x0, x20
	add	w27, w27, 1
	bl	BsSkip
	cmp	w27, w23
	bne	.L2823
	ldr	w0, [x26, 896]
	ldr	w3, [x26, 904]
	lsl	w0, w0, 3
.L2821:
	asr	w1, w28, 31
	lsr	w2, w1, 29
	add	w1, w28, w2
	and	w1, w1, 7
	sub	w1, w1, w2
	add	w3, w1, w3
	cmp	w3, w0
	bls	.L2868
.L2819:
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbz	w0, #31, .L2731
	ldr	x1, .LC820
	mov	w3, 12366
	ldr	x2, .LC874
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2731
.L2728:
	ldr	x1, .LC871
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2869
.L2815:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2816
	.p2align 3
.L2817:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2816:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2817
	ldr	w0, [x26, 60]
	cmp	w0, 3
	bls	.L2828
.L2866:
	ldr	x1, .LC873
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L2727:
	ldr	x1, .LC869
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2870
.L2812:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2813
	.p2align 3
.L2814:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2813:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2814
	b	.L2731
.L2726:
	ldr	x1, .LC867
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2871
.L2809:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2810
	.p2align 3
.L2811:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2810:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2811
	b	.L2731
.L2725:
	ldr	x1, .LC865
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2872
.L2806:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2807
	.p2align 3
.L2808:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2807:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2808
	b	.L2731
.L2724:
	ldr	x1, .LC863
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2873
.L2803:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2804
	.p2align 3
.L2805:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2804:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2805
	b	.L2731
.L2723:
	ldr	x1, .LC861
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2874
.L2800:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2801
	.p2align 3
.L2802:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2801:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2802
	b	.L2731
.L2722:
	ldr	x1, .LC859
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2875
.L2797:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2798
	.p2align 3
.L2799:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2798:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2799
	b	.L2731
.L2721:
	ldr	x1, .LC857
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2876
.L2794:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2795
	.p2align 3
.L2796:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2795:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2796
	b	.L2731
.L2720:
	ldr	x1, .LC855
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2877
.L2791:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2792
	.p2align 3
.L2793:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2792:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2793
	b	.L2731
.L2719:
	ldr	x1, .LC853
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2878
.L2788:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2789
	.p2align 3
.L2790:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2789:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2790
	b	.L2731
.L2718:
	ldr	x1, .LC851
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2879
.L2785:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2786
	.p2align 3
.L2787:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2786:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2787
	b	.L2731
.L2717:
	ldr	x1, .LC849
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2880
.L2782:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2783
	.p2align 3
.L2784:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2783:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2784
	b	.L2731
.L2716:
	ldr	x1, .LC847
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2881
.L2779:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2780
	.p2align 3
.L2781:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2780:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2781
	b	.L2731
.L2715:
	ldr	x1, .LC845
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2882
.L2776:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2777
	.p2align 3
.L2778:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2777:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2778
	b	.L2731
.L2714:
	ldr	x1, .LC843
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2883
.L2773:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2774
	.p2align 3
.L2775:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2774:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2775
	b	.L2731
.L2713:
	ldr	x1, .LC841
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	cmp	w19, wzr
	ble	.L2770
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2770
	mov	w23, 0
	b	.L2771
	.p2align 3
.L2772:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2770
.L2771:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2772
.L2770:
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbz	w0, #31, .L2731
	ldr	x2, .LC818
	mov	w3, 11938
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2731
.L2712:
	cbnz	w24, .L2711
	ldr	x1, .LC830
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
.L2748:
	ldr	w23, [x26, 60]
	ldr	w0, [x26, 120]
	add	x23, x26, x23, uxtw 3
	bl	GetUsd
	str	x0, [x23, 832]
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x1, [x26, x0, lsl 3]
	cbz	x1, .L2836
	ldr	x5, [x26, 240]
	cmp	w19, 1024
	mov	w7, 1024
	csel	w27, w19, w7, le
	ldrb	w3, [x5]
	ldr	w6, [x5, 76]
	cmp	w3, w6
	bcs	.L2837
	mov	w28, 0
	.p2align 2
.L2750:
	ubfiz	x2, x3, 5, 32
	add	w3, w3, 1
	add	x2, x5, x2
	cmp	w3, w6
	ldr	w0, [x2, 28]
	ldr	w2, [x2, 16]
	add	w0, w0, 7
	sub	w0, w2, w0, lsr 3
	add	w28, w28, w0
	bne	.L2750
	mov	w0, w28
.L2749:
	cmp	w27, w0
	csel	w28, w28, w27, gt
	cbnz	w24, .L2884
	mov	w23, 0
	mov	w25, 0
.L2752:
	sub	w2, w28, w23
	mov	x0, x26
	bl	MVC_GetBytes
	cmp	w0, wzr
	mov	w28, w0
	ble	.L2885
	sub	w0, w27, w25
	cmp	w28, w0
	blt	.L2886
	ldr	w0, [x26, 60]
	sub	w23, w19, w25
	cmp	w27, w19
	add	x0, x0, 104
	ldr	x0, [x26, x0, lsl 3]
	str	w23, [x0, 1052]
	bcc	.L2887
.L2764:
	cmp	w23, wzr
	ble	.L2758
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2758
	mov	w19, 0
	b	.L2766
	.p2align 3
.L2767:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2758
.L2766:
	mov	w1, 8
	mov	x0, x20
	add	w19, w19, 1
	bl	BsSkip
	cmp	w23, w19
	bne	.L2767
.L2758:
	ldr	w0, [x26, 60]
	cmp	w24, 1
	ldr	x1, [x26, 224]
	mov	w2, 9
	add	x0, x0, 104
	ldr	x1, [x1, 64]
	ldr	x0, [x26, x0, lsl 3]
	str	x1, [x0, 1056]
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x1, [x26, x0, lsl 3]
	mov	w0, 8
	csel	w0, w0, w2, eq
	str	w0, [x1, 1040]
.L2857:
	ldr	w0, [x26, 60]
	ldr	x1, .LC837
	add	x0, x0, 104
	ldr	x5, [x1]
	ldr	x0, [x26, x0, lsl 3]
	ldr	w1, [x26, 84]
	str	w1, [x0, 1044]
	cbz	x5, .L2731
	ldr	w0, [x26, 60]
	mov	w3, 1064
	mov	w1, 6
	add	x0, x0, 104
	ldr	x2, [x26, x0, lsl 3]
	ldr	w0, [x26, 120]
	blr	x5
	b	.L2731
.L2710:
	ldr	x1, .LC826
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2888
.L2744:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2745
	.p2align 3
.L2746:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2745:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2746
	b	.L2731
.L2709:
	ldr	x1, .LC824
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2889
.L2741:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2742
	.p2align 3
.L2743:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2742:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2743
	b	.L2731
.L2708:
	ldr	x1, .LC822
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	ldr	w28, [x26, 904]
	mov	w1, w19
	mov	x0, x26
	bl	MVC_DecPicTimingSEI
	ldr	w3, [x26, 904]
	sub	w0, w3, w28
	lsl	w28, w19, 3
	cmp	w0, w28
	bge	.L2735
	sub	w28, w28, w0
	ldr	w0, [x26, 896]
	cmp	w28, wzr
	add	w23, w28, 7
	csel	w23, w23, w28, lt
	lsl	w0, w0, 3
	asr	w23, w23, 3
	cmp	w23, wzr
	ble	.L2737
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2737
	mov	w25, 0
	b	.L2738
	.p2align 3
.L2739:
	ldr	w0, [x26, 896]
	ldr	w3, [x26, 904]
	lsl	w0, w0, 3
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2737
.L2738:
	mov	w1, 8
	mov	x0, x20
	add	w25, w25, 1
	bl	BsSkip
	cmp	w25, w23
	bne	.L2739
	ldr	w0, [x26, 896]
	ldr	w3, [x26, 904]
	lsl	w0, w0, 3
.L2737:
	asr	w1, w28, 31
	lsr	w2, w1, 29
	add	w1, w28, w2
	and	w1, w1, 7
	sub	w1, w1, w2
	add	w3, w1, w3
	cmp	w3, w0
	bls	.L2890
.L2735:
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbz	w0, #31, .L2731
	ldr	x2, .LC818
	mov	w3, 11721
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2731
.L2706:
	ldr	x1, .LC817
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x26
	bl	MVC_PassBytes
	tbnz	w0, #31, .L2891
.L2730:
	cmp	w19, wzr
	ble	.L2731
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
	mov	w23, 0
	b	.L2732
	.p2align 3
.L2733:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2731
.L2732:
	mov	w1, 8
	mov	x0, x20
	add	w23, w23, 1
	bl	BsSkip
	cmp	w19, w23
	bne	.L2733
	b	.L2731
	.p2align 3
.L2863:
	ldr	w0, [x0, 60]
	add	w2, w2, w0
	lsr	w2, w2, 3
	b	.L2704
.L2886:
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x0, [x26, x0, lsl 3]
	str	w28, [x0, 1052]
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2758
	mov	w19, 0
	b	.L2759
	.p2align 3
.L2762:
	ldr	w1, [x26, 896]
	ldr	w0, [x26, 904]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2758
.L2759:
	mov	w1, 8
	mov	x0, x20
	add	w19, w19, 1
	bl	BsSkip
	cmp	w28, w19
	bne	.L2762
	b	.L2758
.L2711:
	ldr	x1, .LC828
	mov	w3, w19
	mov	w0, 20
	mov	w24, 1
	bl	dprint_vfmw
	b	.L2748
.L2884:
	strb	w24, [x1, 1026]
	mov	x0, x26
	ldr	x2, .LC832
	mov	w1, 8
	ldr	w3, [x26, 60]
	add	x3, x3, 104
	ldr	x23, [x26, x3, lsl 3]
	bl	mvc_u_v
	strb	w0, [x23, 1027]
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x23, [x26, x0, lsl 3]
	ldrb	w0, [x23, 1027]
	cmp	w0, 255
	beq	.L2753
	strb	wzr, [x23, 1028]
	mov	w23, 3
	mov	w25, w23
.L2754:
	ldr	w0, [x26, 60]
	mov	w1, 16
	ldr	x2, .LC836
	add	x0, x0, 104
	ldr	x5, [x26, x0, lsl 3]
	mov	x0, x26
	str	x5, [x29, 96]
	bl	mvc_u_v
	ldr	x5, [x29, 96]
	mov	w1, w23
	strh	w0, [x5, 1030]
	mov	x0, x26
	bl	MVC_PassBytes
	ldr	w0, [x26, 60]
	cmp	w28, w23
	add	x0, x0, 104
	beq	.L2755
	ldr	x1, [x26, x0, lsl 3]
	b	.L2752
.L2881:
	ldr	x2, .LC818
	mov	w3, 12002
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2779
.L2889:
	ldr	x2, .LC818
	mov	w3, 11733
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2741
.L2891:
	ldr	x2, .LC818
	mov	w3, 11668
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2730
.L2873:
	ldr	x2, .LC818
	mov	w3, 12210
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2803
.L2878:
	ldr	x2, .LC818
	mov	w3, 12080
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2788
.L2879:
	ldr	x2, .LC818
	mov	w3, 12054
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2785
.L2876:
	ldr	x2, .LC818
	mov	w3, 12132
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2794
.L2877:
	ldr	x2, .LC818
	mov	w3, 12106
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2791
.L2882:
	ldr	x2, .LC818
	mov	w3, 11976
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2776
.L2883:
	ldr	x2, .LC818
	mov	w3, 11950
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2773
.L2880:
	ldr	x2, .LC818
	mov	w3, 12028
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2782
.L2868:
	mov	x0, x20
	bl	BsSkip
	b	.L2819
.L2890:
	mov	x0, x20
	bl	BsSkip
	b	.L2735
.L2870:
	ldr	x2, .LC818
	mov	w3, 12288
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2812
.L2871:
	ldr	x2, .LC818
	mov	w3, 12262
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2809
.L2865:
	ldr	x1, .LC820
	mov	w3, 12376
	ldr	x2, [x29, 104]
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2825
.L2869:
	ldr	x1, .LC820
	mov	w3, 12314
	ldr	x2, .LC874
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2815
.L2888:
	ldr	x2, .LC818
	mov	w3, 11759
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2744
.L2874:
	ldr	x2, .LC818
	mov	w3, 12184
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2800
.L2875:
	ldr	x2, .LC818
	mov	w3, 12158
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2797
.L2872:
	ldr	x2, .LC818
	mov	w3, 12236
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2806
.L2887:
	sub	w1, w19, w27
	mov	x0, x26
	bl	MVC_PassBytes
	tbz	w0, #31, .L2764
	ldr	x2, .LC818
	mov	w3, 11891
	ldr	x1, .LC820
	mov	w0, 20
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L2764
.L2837:
	mov	w0, 0
	mov	w28, 0
	b	.L2749
.L2755:
	ldr	x1, [x26, 224]
	ldr	x0, [x26, x0, lsl 3]
	ldr	x1, [x1, 64]
	str	x1, [x0, 1056]
	mov	w1, 8
	ldr	w0, [x26, 60]
	add	x0, x0, 104
	ldr	x0, [x26, x0, lsl 3]
	str	w1, [x0, 1040]
	b	.L2857
.L2753:
	ldr	x2, .LC834
	mov	w1, 8
	mov	x0, x26
	bl	mvc_u_v
	strb	w0, [x23, 1028]
	mov	w23, 4
	mov	w25, w23
	b	.L2754
.L2836:
	mov	w0, -1
	b	.L2698
.L2885:
	ldr	x1, .LC839
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x26, 60]
	ldr	w0, [x26, 120]
	add	x1, x1, 104
	ldr	x1, [x26, x1, lsl 3]
	bl	FreeUsdByDec
	ldr	w1, [x26, 60]
	mov	w0, -1
	add	x1, x1, 104
	str	xzr, [x26, x1, lsl 3]
	b	.L2698
	.size	MVC_DecSEI, .-MVC_DecSEI
	.align	3
.LC812:
	.xword	.LC811
	.align	3
.LC814:
	.xword	.LC813
	.align	3
.LC815:
	.xword	.L2707
	.align	3
.LC817:
	.xword	.LC816
	.align	3
.LC818:
	.xword	.LANCHOR0
	.align	3
.LC820:
	.xword	.LC819
	.align	3
.LC822:
	.xword	.LC821
	.align	3
.LC824:
	.xword	.LC823
	.align	3
.LC826:
	.xword	.LC825
	.align	3
.LC828:
	.xword	.LC827
	.align	3
.LC830:
	.xword	.LC829
	.align	3
.LC832:
	.xword	.LC831
	.align	3
.LC834:
	.xword	.LC833
	.align	3
.LC836:
	.xword	.LC835
	.align	3
.LC837:
	.xword	g_event_report
	.align	3
.LC839:
	.xword	.LC838
	.align	3
.LC841:
	.xword	.LC840
	.align	3
.LC843:
	.xword	.LC842
	.align	3
.LC845:
	.xword	.LC844
	.align	3
.LC847:
	.xword	.LC846
	.align	3
.LC849:
	.xword	.LC848
	.align	3
.LC851:
	.xword	.LC850
	.align	3
.LC853:
	.xword	.LC852
	.align	3
.LC855:
	.xword	.LC854
	.align	3
.LC857:
	.xword	.LC856
	.align	3
.LC859:
	.xword	.LC858
	.align	3
.LC861:
	.xword	.LC860
	.align	3
.LC863:
	.xword	.LC862
	.align	3
.LC865:
	.xword	.LC864
	.align	3
.LC867:
	.xword	.LC866
	.align	3
.LC869:
	.xword	.LC868
	.align	3
.LC871:
	.xword	.LC870
	.align	3
.LC873:
	.xword	.LC872
	.align	3
.LC874:
	.xword	.LANCHOR0+240
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InitOldSlice
	.type	MVC_InitOldSlice, %function
MVC_InitOldSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 11120640
	mov	w4, 32
	ldr	w8, [x19, 40]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x0, 434]
	add	x4, x0, 256
	strb	wzr, [x0, 432]
	mov	w5, 7
	strb	w6, [x0, 433]
	mov	w3, 3
	strb	w5, [x0, 435]
	mov	w2, -1
	str	w8, [x0, 444]
	mov	w1, 262144
	str	w7, [x0, 448]
	stp	w3, w2, [x4, 200]
	stp	wzr, wzr, [x4, 208]
	str	w1, [x0, 472]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_InitOldSlice, .-MVC_InitOldSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsNewPicNal
	.type	MVC_IsNewPicNal, %function
MVC_IsNewPicNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L2904
	cbz	x20, .L2905
	ldrb	w0, [x20, 3]
	and	w0, w0, 31
	sub	w0, w0, #1
	cmp	w0, 7
	bls	.L2906
.L2903:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2906:
	ldr	x1, .LC880
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx2898
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2898:
	.section	.rodata
	.align	0
	.align	2
.L2898:
	.byte	(.L2897 - .Lrtx2898) / 4
	.byte	(.L2903 - .Lrtx2898) / 4
	.byte	(.L2903 - .Lrtx2898) / 4
	.byte	(.L2903 - .Lrtx2898) / 4
	.byte	(.L2897 - .Lrtx2898) / 4
	.byte	(.L2903 - .Lrtx2898) / 4
	.byte	(.L2899 - .Lrtx2898) / 4
	.byte	(.L2899 - .Lrtx2898) / 4
	.text
	.p2align 3
.L2899:
	ldr	w0, [x19]
	mov	w1, 1
	str	w1, [x19]
	cmp	w0, wzr
	csetm	w0, ne
.L2895:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2897:
	ldr	w0, [x19]
	cbz	w0, .L2900
.L2902:
	mov	w0, -1
	str	wzr, [x19]
.L2907:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2900:
	ldr	w20, [x20, 4]
	rev	w20, w20
	mov	w0, w20
	bl	ZerosMS_32
	cmp	w0, 15
	bhi	.L2902
	mov	w1, 31
	str	wzr, [x19]
	sub	w0, w1, w0, lsl 1
	lsr	w20, w20, w0
	cmp	w20, 1
	csetm	w0, ne
	b	.L2907
.L2904:
	ldr	x3, .LC876
	mov	w2, 12503
	ldr	x1, .LC877
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2895
.L2905:
	ldr	x3, .LC879
	mov	w2, 12504
	ldr	x1, .LC877
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2895
	.size	MVC_IsNewPicNal, .-MVC_IsNewPicNal
	.align	3
.LC876:
	.xword	.LC875
	.align	3
.LC877:
	.xword	.LC63
	.align	3
.LC879:
	.xword	.LC878
	.align	3
.LC880:
	.xword	.L2898
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindZeroBitsInSeg
	.type	MVC_FindZeroBitsInSeg, %function
MVC_FindZeroBitsInSeg:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x22, x0
	mov	x0, x30
	mov	w23, w1
	bl	_mcount
	cmp	x22, xzr
	ccmp	w23, wzr, 4, ne
	ble	.L2928
	and	w1, w23, 63
	add	w0, w23, 63
	cmp	w1, wzr
	cset	w26, ne
	cmp	w23, wzr
	csel	w0, w0, w23, lt
	add	w26, w26, w0, asr 6
	cmp	w26, wzr
	ble	.L2921
	ldr	x20, .LC884
	mov	w25, w23
	ldr	x27, .LC883
	mov	w19, 0
	mov	w24, 64
	add	x20, x20, 1880
	.p2align 2
.L2920:
	cmp	w25, 64
	uxtw	x1, w25
	csel	w21, w25, w24, ls
	ldr	x3, [x27, 104]
	sub	x1, x1, x21
	mov	x2, x21
	add	x1, x22, x1
	sub	x21, x21, #1
	mov	x0, x20
	blr	x3
	ldrb	w1, [x20, x21]
	add	x0, x20, x21
	cbnz	w1, .L2912
	cmp	x0, x20
	add	w19, w19, 1
	bne	.L2915
	b	.L2913
	.p2align 3
.L2916:
	add	w19, w19, 1
	beq	.L2913
.L2915:
	ldrb	w1, [x0, -1]!
	cmp	x0, x20
	cbz	w1, .L2916
.L2912:
	lsl	w0, w19, 3
.L2911:
	cmp	w19, w23
	mov	w1, 0
	bge	.L2917
	sxtw	x2, w23
	sub	x2, x2, #1
	sub	x19, x2, x19, sxtw
	ldrb	w2, [x22, x19]
	tbnz	x2, 0, .L2917
	lsr	w2, w2, 1
	mov	w1, 1
	.p2align 2
.L2919:
	tbnz	x2, 0, .L2917
	add	w1, w1, 1
	lsr	w2, w2, 1
	cmp	w1, 8
	bne	.L2919
.L2917:
	add	w0, w1, w0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2913:
	subs	w26, w26, #1
	sub	w25, w25, #64
	bne	.L2920
	b	.L2912
.L2928:
	ldr	x1, .LC882
	mov	w2, w23
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L2921:
	mov	w0, 0
	mov	w19, 0
	b	.L2911
	.size	MVC_FindZeroBitsInSeg, .-MVC_FindZeroBitsInSeg
	.align	3
.LC882:
	.xword	.LC881
	.align	3
.LC883:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC884:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindTrailZeros
	.type	MVC_FindTrailZeros, %function
MVC_FindTrailZeros:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2935
	ldr	x2, [x19, 240]
	ldr	w0, [x2, 76]
	cmp	w0, 1
	bls	.L2934
	ldr	w1, [x2, 48]
	ldr	x0, [x2, 40]
	bl	MVC_FindZeroBitsInSeg
	ldr	x2, [x19, 240]
	ldr	w1, [x2, 48]
	cmp	w0, w1, lsl 3
	bcs	.L2938
	cmn	w0, #1
	beq	.L2934
	add	w0, w0, 1
	str	w0, [x2, 80]
	ldr	x0, [x19, 240]
	ldr	w1, [x0, 76]
	cmp	w1, 1
	bls	.L2936
.L2939:
	ldr	w2, [x0, 48]
	mov	w20, 0
	ldr	w1, [x0, 80]
	cmp	w1, w2, lsl 3
	bcc	.L2930
	ldr	w1, [x0, 68]
	ldr	w0, [x19, 120]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 240]
	mov	w1, 1
	str	xzr, [x0, 40]
	ldr	x0, [x19, 240]
	str	w1, [x0, 76]
	ldr	x0, [x19, 240]
	str	wzr, [x0, 80]
.L2930:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2938:
	ldr	w1, [x2, 68]
	ldr	w0, [x19, 120]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 240]
	mov	w1, 1
	str	xzr, [x0, 40]
	ldr	x0, [x19, 240]
	str	w1, [x0, 76]
	ldr	x2, [x19, 240]
.L2934:
	ldr	w1, [x2, 16]
	ldr	x0, [x2, 8]
	bl	MVC_FindZeroBitsInSeg
	add	w0, w0, 1
	ldr	x2, [x19, 240]
	str	w0, [x2, 80]
	ldr	x0, [x19, 240]
	ldr	w1, [x0, 76]
	cmp	w1, 1
	bhi	.L2939
.L2936:
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2935:
	mov	w20, -1
	b	.L2930
	.size	MVC_FindTrailZeros, .-MVC_FindTrailZeros
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_CombinePacket
	.type	MVC_CombinePacket, %function
MVC_CombinePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x19, 240]
	ldr	w0, [x0, 16]
	cmp	w0, 4095
	bhi	.L2940
	mov	x0, x19
	bl	MVC_CombinePacket.part.14
.L2940:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_CombinePacket, .-MVC_CombinePacket
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FindNaluArraySlot
	.type	MVC_FindNaluArraySlot, %function
MVC_FindNaluArraySlot:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1521]
	cbz	w0, .L2947
	add	x0, x19, 1617
	mov	x1, 1
	b	.L2945
	.p2align 3
.L2944:
	add	w1, w1, 1
	cmp	w1, 137
	beq	.L2950
.L2945:
	ldrb	w2, [x0]
	add	x0, x0, 96
	cbnz	w2, .L2944
	mov	w0, w1
.L2943:
	lsl	x2, x1, 2
	mov	w3, 1
	sub	x1, x2, x1
	add	x1, x19, x1, lsl 5
	strb	w3, [x1, 1521]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2950:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2947:
	mov	w0, 0
	mov	x1, 0
	b	.L2943
	.size	MVC_FindNaluArraySlot, .-MVC_FindNaluArraySlot
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InquireSliceProperty
	.type	MVC_InquireSliceProperty, %function
MVC_InquireSliceProperty:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x21, x2
	bl	_mcount
	add	x20, x19, 11116544
	ldr	w2, [x19, 68]
	mov	w0, 22
	ldr	x1, .LC887
	sub	w2, w2, #1
	bl	dprint_vfmw
	str	wzr, [x21]
	str	wzr, [x23]
	add	x2, x19, 11120640
	add	x0, x19, 12288
	mov	w3, -1
	ldr	x1, [x19, 240]
	ldrb	w4, [x1, 2]
	strb	w4, [x20, 2875]
	ldrb	w5, [x1, 4]
	strb	w5, [x20, 2880]
	ldrsb	w1, [x1, 5]
	strb	w1, [x20, 2884]
	strb	wzr, [x20, 2883]
	str	w3, [x2, 416]
	ldrb	w3, [x0, 2384]
	cmp	w3, 1
	beq	.L2987
	cmn	w1, #1
	beq	.L2988
.L2953:
	mov	x0, x19
	bl	MVC_SliceCheck
	mov	w22, w0
	cbnz	w0, .L2969
	mov	x0, x19
	bl	MVC_ProcessSliceHeaderFirstPart
	cbnz	w0, .L2989
	ldrb	w1, [x20, 2877]
	mov	w0, 2240
	cmp	w1, 1
	cset	w1, eq
	str	w1, [x23]
	ldr	w1, [x20, 2888]
	ldrsb	w2, [x20, 2884]
	ldr	x3, [x19, 280]
	umull	x0, w1, w0
	cmn	w2, #1
	add	x0, x3, x0
	beq	.L2990
	cbnz	w2, .L2965
	ldrb	w1, [x19, 2]
	cmp	w1, 1
	beq	.L2991
	ldr	w1, [x0, 28]
	add	x0, x19, 11046912
	ldr	w2, [x19, 28]
	add	x0, x0, 180
	cmp	w2, w1
	bne	.L2992
.L2964:
	ldrb	w1, [x0, 20]
	mov	w2, 2
	ldr	w5, [x0, 3952]
	sub	w1, w2, w1
	ldr	w2, [x0, 3948]
	ldp	w3, w4, [x19, 12]
	madd	w1, w5, w1, w1
	add	w2, w2, 1
	cmp	w1, w4
	ccmp	w2, w3, 0, eq
	beq	.L2968
	mov	w1, 1
	str	w1, [x21]
.L2968:
	add	x19, x19, 11124736
	ldr	w1, [x0, 3972]
	ldr	w0, [x19, 824]
	add	w0, w0, 1
	cmp	w1, w0
	bls	.L2961
	mov	w0, 1
	str	w0, [x21]
.L2961:
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2987:
	strb	w3, [x20, 2883]
	ldr	w1, [x19, 14680]
	str	w1, [x2, 416]
	ldrb	w1, [x0, 2388]
	strb	w1, [x20, 2881]
	ldrb	w0, [x0, 2389]
	strb	w0, [x20, 2882]
	b	.L2953
	.p2align 3
.L2990:
	ldr	w1, [x0, 28]
	mov	w0, 3992
	ldr	x2, [x19, 272]
	umull	x0, w1, w0
	add	x0, x2, x0
	b	.L2964
	.p2align 3
.L2988:
	ldr	w1, [x19, 20]
	cbz	w1, .L2953
	add	x1, x19, 10768384
	ldr	w3, [x1, 4064]
	cbnz	w3, .L2956
	ldrb	w3, [x1, 4060]
	cbnz	w3, .L2956
	add	x0, x0, 2400
	mov	x1, 0
	.p2align 2
.L2959:
	ldr	w3, [x0]
	add	x5, x0, 335872
	cbz	w3, .L2957
	ldrb	w0, [x0, -4]
	cbnz	w0, .L2993
.L2957:
	add	w1, w1, 1
	add	x0, x5, 308
	cmp	w1, 32
	bne	.L2959
	mov	w0, -1
	b	.L2986
	.p2align 3
.L2991:
	ldr	w1, [x0, 28]
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x0, x0, x1
	lsl	x1, x0, 2
	sub	x1, x1, x0
	lsl	x0, x1, 6
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	add	x0, x0, 286720
	add	x0, x0, 2612
	b	.L2964
	.p2align 3
.L2956:
	ldr	w0, [x1, 4068]
.L2986:
	cmn	w0, #1
	str	w0, [x2, 416]
	beq	.L2953
	cmp	w4, 5
	mov	w0, 1
	cset	w1, eq
	strb	w0, [x20, 2883]
	strb	w0, [x20, 2882]
	strb	w1, [x20, 2881]
	b	.L2953
	.p2align 3
.L2969:
	mov	w22, -1
	b	.L2961
	.p2align 3
.L2992:
	ldr	x1, .LC890
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2961
	.p2align 3
.L2989:
	ldr	x1, .LC889
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2961
	.p2align 3
.L2965:
	ldr	x1, .LC892
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2961
	.p2align 3
.L2993:
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x1, x0, x1
	lsl	x0, x1, 2
	sub	x1, x0, x1
	lsl	x0, x1, 6
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14692]
	b	.L2986
	.size	MVC_InquireSliceProperty, .-MVC_InquireSliceProperty
	.align	3
.LC887:
	.xword	.LC886
	.align	3
.LC889:
	.xword	.LC888
	.align	3
.LC890:
	.xword	.LC94
	.align	3
.LC892:
	.xword	.LC891
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_HaveSliceToDec
	.type	MVC_HaveSliceToDec, %function
MVC_HaveSliceToDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 64]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	csetm	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_HaveSliceToDec, .-MVC_HaveSliceToDec
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IsRefListWrong
	.type	MVC_IsRefListWrong, %function
MVC_IsRefListWrong:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 11116544
	bl	_mcount
	ldr	w0, [x21, 2920]
	cbz	w0, .L2996
	mov	w19, 0
	b	.L3000
	.p2align 3
.L2997:
	ldr	x0, [x0, 32]
	cbz	x0, .L2999
	ldr	w0, [x21, 2920]
	cmp	w0, w19
	bls	.L3024
.L3000:
	add	x1, x20, x19, sxtw 3
	ldr	w0, [x20, 120]
	add	w19, w19, 1
	ldr	x1, [x1, 288]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	cbnz	x0, .L2997
.L2999:
	mov	w0, -1
.L3026:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2996:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3024:
	cbz	w0, .L2996
	ldr	w0, [x21, 2924]
	mov	w19, 0
	cbnz	w0, .L3013
	b	.L2996
	.p2align 3
.L3025:
	ldr	x0, [x0, 32]
	cbz	x0, .L2999
	ldr	w0, [x21, 2924]
	cmp	w0, w19
	bls	.L2996
.L3013:
	add	x1, x20, x19, sxtw 3
	ldr	w0, [x20, 120]
	add	w19, w19, 1
	ldr	x1, [x1, 552]
	ldr	x1, [x1, 8]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetLogicFs
	cbnz	x0, .L3025
	mov	w0, -1
	b	.L3026
	.size	MVC_IsRefListWrong, .-MVC_IsRefListWrong
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_Destroy
	.type	MVC_DEC_Destroy, %function
MVC_DEC_Destroy:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L3050
	mov	x0, x21
	add	x20, x21, 12288
	add	x19, x21, 1520
	add	x20, x20, 2384
	bl	MVC_ClearCurrPic
	b	.L3031
	.p2align 3
.L3030:
	add	x19, x19, 96
	cmp	x20, x19
	beq	.L3051
.L3031:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L3030
	ldr	w0, [x21, 120]
	mov	x1, x19
	add	x19, x19, 96
	bl	MVC_ReleaseNAL
	cmp	x20, x19
	bne	.L3031
.L3051:
	ldr	w2, [x21, 60]
	mov	w19, 0
	cbz	w2, .L3036
	.p2align 2
.L3044:
	add	x20, x21, x19, uxtw 3
	add	w19, w19, 1
	ldr	x0, [x20, 832]
	mov	x1, x0
	cbz	x0, .L3034
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x20, 832]
	ldr	w2, [x21, 60]
.L3034:
	cmp	w2, w19
	bhi	.L3044
.L3036:
	add	x20, x21, 11124736
	add	x22, x21, 11157504
	add	x20, x20, 1840
	add	x22, x22, 3312
	.p2align 2
.L3033:
	sub	x19, x20, #32
.L3038:
	ldr	x1, [x19]
	cbnz	x1, .L3052
.L3037:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L3038
	add	x20, x19, 856
	cmp	x20, x22
	bne	.L3033
	ldr	x1, .LC896
	mov	w0, 2
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3052:
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L3037
.L3050:
	ldr	x1, .LC894
	mov	w2, 13501
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_DEC_Destroy, .-MVC_DEC_Destroy
	.align	3
.LC894:
	.xword	.LC893
	.align	3
.LC896:
	.xword	.LC895
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_RecycleImage
	.type	MVC_DEC_RecycleImage, %function
MVC_DEC_RecycleImage:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cbz	x21, .L3065
	cmp	w22, 31
	bhi	.L3066
	ldr	x1, .LC902
	mov	w0, 2
	bl	dprint_vfmw
	ldr	w0, [x21, 120]
	mov	w1, w22
	bl	FSP_GetLogicFs
	cbz	x0, .L3060
	ldrsb	w1, [x0, 1]
	cbz	w1, .L3060
	add	x19, x0, 592
	add	x20, x0, 624
.L3058:
	ldr	x1, [x19]
	cbnz	x1, .L3067
.L3057:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L3058
	ldr	w0, [x21, 120]
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, 0
.L3055:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3067:
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L3057
	.p2align 3
.L3060:
	mov	w0, -1
	b	.L3055
	.p2align 3
.L3066:
	ldr	x3, .LC900
	mov	w2, 13763
	ldr	x1, .LC898
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3055
.L3065:
	ldr	x3, .LC897
	mov	w2, 13762
	ldr	x1, .LC898
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3055
	.size	MVC_DEC_RecycleImage, .-MVC_DEC_RecycleImage
	.align	3
.LC897:
	.xword	.LC61
	.align	3
.LC898:
	.xword	.LC63
	.align	3
.LC900:
	.xword	.LC899
	.align	3
.LC902:
	.xword	.LC901
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_OutputFrmToVO
	.type	MVC_OutputFrmToVO, %function
MVC_OutputFrmToVO:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L3109
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cbz	w0, .L3071
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	beq	.L3071
	ldr	x0, [x19, 816]
	cbz	x0, .L3073
	strb	wzr, [x0, 2]
	mov	w0, 1
	str	xzr, [x19, 816]
.L3108:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3071:
	mov	x1, x20
	mov	x0, x19
	bl	MVC_CheckFrameStore
	cmn	w0, #3
	beq	.L3073
	ldr	x1, [x19, 816]
	cbz	x1, .L3074
	mov	x0, x19
	bl	MVC_GetImagePara
	ldr	x1, [x19, 816]
	mov	x0, x19
	bl	MVC_CheckFrameStore
	mov	w22, w0
	cbz	w0, .L3110
	cmn	w0, #3
	beq	.L3082
	ldr	x1, .LC910
	mov	w3, w0
	mov	w2, 1844
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 816]
	mov	x0, x19
	ldr	w1, [x1, 220]
	bl	MVC_DEC_RecycleImage
	cmp	w22, 1
	cset	w1, eq
.L3081:
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 816]
	cmp	x0, x20
	cset	w0, eq
	tst	w1, w0
	bne	.L3111
	str	xzr, [x19, 816]
.L3074:
	mov	x1, x20
	mov	x0, x19
	bl	MVC_GetImagePara
	mov	x1, x20
	mov	x0, x19
	bl	MVC_CheckFrameStore
	cbz	w0, .L3112
	ldr	x1, .LC910
	mov	w3, w0
	mov	w2, 1897
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x20, 220]
	mov	x0, x19
	bl	MVC_DEC_RecycleImage
	mov	w0, 2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3109:
	ldr	x1, .LC904
	mov	x3, x20
	mov	x2, x19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3112:
	ldrsb	w1, [x20, 6]
	mov	w2, 1
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
	ldrsb	w1, [x20, 6]
	ldr	w0, [x19, 120]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L3113
	cmp	w21, 1
	beq	.L3114
.L3086:
	ldr	w0, [x19, 120]
	mov	x4, x22
	add	x3, x19, 912
	mov	x2, x19
	mov	w1, 15
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L3115
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L3116
	str	wzr, [x22, 16]
.L3089:
	ldr	w1, [x19, 136]
	mov	w0, 0
	ldr	w2, [x19, 144]
	add	w1, w1, 2
	str	w1, [x19, 136]
	add	w2, w2, 1
	str	w2, [x19, 144]
	b	.L3108
	.p2align 3
.L3073:
	mov	w0, 1
	b	.L3108
	.p2align 3
.L3082:
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 2]
	str	xzr, [x19, 816]
	b	.L3074
	.p2align 3
.L3110:
	ldr	x1, [x19, 816]
	mov	w2, 1
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	ldr	x1, [x19, 816]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L3117
	ldr	x0, [x19, 816]
	cmp	x0, x20
	ccmp	w21, 1, 0, eq
	beq	.L3118
.L3077:
	ldr	w0, [x19, 120]
	mov	x4, x22
	add	x3, x19, 912
	mov	x2, x19
	mov	w1, 15
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L3119
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L3120
	str	wzr, [x22, 16]
.L3080:
	ldr	w0, [x19, 136]
	mov	w1, 1
	ldr	w2, [x19, 144]
	add	w0, w0, 2
	str	w0, [x19, 136]
	add	w2, w2, w1
	str	w2, [x19, 144]
	b	.L3081
	.p2align 3
.L3111:
	mov	w0, 0
	str	xzr, [x19, 816]
	b	.L3108
	.p2align 3
.L3114:
	str	w21, [x0, 180]
	b	.L3086
	.p2align 3
.L3116:
	mov	x1, x22
	mov	x0, x19
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3089
	.p2align 3
.L3120:
	mov	x1, x22
	mov	x0, x19
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3080
	.p2align 3
.L3118:
	mov	w0, 1
	str	w0, [x22, 180]
	b	.L3077
.L3115:
	ldr	x1, .LC908
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	ldrsb	w1, [x20, 6]
	mov	w2, 0
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
	mov	w1, 1
	mov	x0, x19
	bl	MVC_ClearAll
	mov	w0, -1
	b	.L3108
.L3119:
	ldr	x1, .LC908
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x19, 816]
	mov	w2, 0
	strb	wzr, [x0, 2]
	ldr	x1, [x19, 816]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	str	xzr, [x19, 816]
	mov	w1, 1
	mov	x0, x19
	bl	MVC_ClearAll
	mov	w0, -1
	b	.L3108
.L3113:
	ldr	x1, .LC906
	mov	w2, 1871
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3108
.L3117:
	ldr	x1, .LC906
	mov	w2, 1815
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3108
	.size	MVC_OutputFrmToVO, .-MVC_OutputFrmToVO
	.align	3
.LC904:
	.xword	.LC903
	.align	3
.LC906:
	.xword	.LC905
	.align	3
.LC908:
	.xword	.LC907
	.align	3
.LC910:
	.xword	.LC909
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_OutputFrmFromDPB
	.type	MVC_OutputFrmFromDPB, %function
MVC_OutputFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w1
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, x21, uxtw 3
	add	x19, x19, 11124736
	bl	_mcount
	ldr	x0, [x19, 440]
	cbz	x0, .L3123
	strb	wzr, [x0, 5]
	mov	w2, 0
	mov	x0, x20
	ldr	x1, [x19, 440]
	bl	MVC_OutputFrmToVO
	cmn	w0, #1
	ldr	x1, [x19, 440]
	csetm	w19, eq
	ldrb	w0, [x1, 3]
	cbz	w0, .L3124
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3124:
	mov	w1, w21
	mov	x0, x20
	bl	MVC_RemoveFrameStoreOutDPB
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3123:
	mov	w19, 0
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MVC_OutputFrmFromDPB, .-MVC_OutputFrmFromDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FlushDPB
	.type	MVC_FlushDPB, %function
MVC_FlushDPB:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cbz	x20, .L3144
	add	x21, x20, 11124736
	mov	w22, 0
	ldr	w0, [x21, 824]
	cbz	w0, .L3132
	.p2align 2
.L3166:
	uxtw	x0, w22
	add	w22, w22, 1
	add	x0, x0, 1388544
	add	x0, x20, x0, lsl 3
	ldr	x1, [x0, 16824]
	cbz	x1, .L3130
	ldrb	w0, [x1, 3]
	cbz	w0, .L3130
	ldr	w0, [x1, 56]
	cmp	w0, w19
	ccmn	w19, #1, 4, ne
	bne	.L3130
	mov	x0, x20
	bl	MVC_UnMarkFrameStoreRef
	.p2align 2
.L3130:
	ldr	w0, [x21, 824]
	cmp	w0, w22
	bhi	.L3166
.L3132:
	mov	w1, w19
	mov	x0, x20
	bl	MVC_RemoveUnUsedFrameStore
	ldr	w0, [x21, 824]
	cbz	w0, .L3129
	sub	w2, w0, #1
	mov	w22, -1
	add	x2, x2, 1388544
	add	x0, x21, 440
	add	x2, x2, 2104
	mov	w21, 0
	add	x2, x20, x2, lsl 3
	.p2align 2
.L3136:
	ldr	x1, [x0]
	cmn	w19, #1
	add	x0, x0, 8
	cbz	x1, .L3134
	ldr	w1, [x1, 56]
	ccmp	w19, w1, 4, ne
	csinc	w21, w21, w21, ne
	cmp	w19, w1
	ccmn	w19, #1, 4, ne
	csel	w22, w22, w1, eq
.L3134:
	cmp	x2, x0
	bne	.L3136
	cbz	w21, .L3129
	cmn	w22, #1
	cset	w24, ne
	cmp	w19, w22
	cset	w23, gt
	and	w23, w24, w23
	b	.L3142
	.p2align 3
.L3143:
	subs	w21, w21, #1
	beq	.L3129
.L3142:
	add	x3, x29, 72
	add	x2, x29, 76
	mov	w1, w22
	mov	x0, x20
	cbz	w23, .L3139
	bl	MVC_GetMinPOC
	ldr	w1, [x29, 72]
	mov	x0, x20
	cmn	w1, #1
	beq	.L3129
	bl	MVC_OutputFrmFromDPB
	cbnz	w0, .L3144
.L3139:
	mov	w1, w19
	add	x3, x29, 72
	add	x2, x29, 76
	mov	x0, x20
	bl	MVC_GetMinPOC
	ldr	w1, [x29, 72]
	mov	x0, x20
	cmn	w1, #1
	beq	.L3129
	bl	MVC_OutputFrmFromDPB
	cbnz	w0, .L3144
	cmp	w19, w22
	cset	w0, lt
	tst	w24, w0
	beq	.L3143
	mov	w1, w22
	add	x3, x29, 72
	add	x2, x29, 76
	mov	x0, x20
	bl	MVC_GetMinPOC
	ldr	w1, [x29, 72]
	mov	x0, x20
	cmn	w1, #1
	beq	.L3129
	bl	MVC_OutputFrmFromDPB
	cbz	w0, .L3143
.L3144:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3129:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.size	MVC_FlushDPB, .-MVC_FlushDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_AdaptiveMemMark
	.type	MVC_AdaptiveMemMark, %function
MVC_AdaptiveMemMark:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x25, x20, 11157504
	add	x24, x20, 11116544
	bl	_mcount
	ldr	x22, .LC911
	add	x23, x25, 2664
	mov	w26, 1
	ldr	x21, [x25, 3328]
	add	x19, x21, 8
	add	x21, x21, 2008
	.p2align 2
.L3190:
	ldr	w0, [x19, -4]
	cmp	w0, 6
	bhi	.L3181
	ldrb	w0, [x22,w0,uxtw]
	adr	x1, .Lrtx3183
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx3183:
	.section	.rodata
	.align	0
	.align	2
.L3183:
	.byte	(.L3182 - .Lrtx3183) / 4
	.byte	(.L3184 - .Lrtx3183) / 4
	.byte	(.L3185 - .Lrtx3183) / 4
	.byte	(.L3186 - .Lrtx3183) / 4
	.byte	(.L3187 - .Lrtx3183) / 4
	.byte	(.L3188 - .Lrtx3183) / 4
	.byte	(.L3189 - .Lrtx3183) / 4
	.text
	.p2align 3
.L3188:
	mov	x0, x20
	bl	MVC_UnMarkAllSTRef
	mov	x0, x20
	bl	MVC_UpdateReflist
	mov	w1, 0
	mov	x0, x20
	bl	MVC_UpdateMaxLTFrmIdx
	mov	x0, x20
	bl	MVC_UpdateLTReflist
	strb	w26, [x24, 1736]
	.p2align 2
.L3181:
	add	x19, x19, 20
	cmp	x19, x21
	bne	.L3190
	.p2align 2
.L3182:
	ldrsb	w1, [x24, 1736]
	mov	w0, 0
	cmp	w1, 1
	beq	.L3198
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3187:
	ldr	w1, [x19, 12]
	mov	x0, x20
	bl	MVC_UpdateMaxLTFrmIdx
	mov	x0, x20
	bl	MVC_UpdateLTReflist
	b	.L3181
	.p2align 3
.L3186:
	ldr	w2, [x19]
	mov	x1, x23
	ldr	w3, [x19, 8]
	mov	x0, x20
	bl	MVC_MarkSTToLTRef
	mov	x0, x20
	bl	MVC_UpdateReflist
	mov	x0, x20
	bl	MVC_UpdateLTReflist
	b	.L3181
	.p2align 3
.L3185:
	ldr	w2, [x19, 4]
	mov	x0, x20
	mov	x1, x23
	bl	MVC_UnMarkLTRef
	mov	x0, x20
	bl	MVC_UpdateLTReflist
	b	.L3181
	.p2align 3
.L3184:
	ldr	w2, [x19]
	mov	x0, x20
	mov	x1, x23
	bl	MVC_UnMarkSTRef
	mov	x0, x20
	bl	MVC_UpdateReflist
	b	.L3181
	.p2align 3
.L3189:
	ldr	w2, [x19, 8]
	mov	x1, x23
	mov	x0, x20
	bl	MVC_MarkCurrPicLT
	b	.L3181
	.p2align 3
.L3198:
	add	x0, x20, 11120640
	str	wzr, [x25, 3336]
	add	x1, x20, 11161600
	ldr	w0, [x0, 420]
	add	x0, x0, 2777088
	add	x0, x20, x0, lsl 2
	str	wzr, [x0, 11084]
	str	wzr, [x1, 80]
	ldrb	w0, [x25, 2667]
	cmp	w0, 1
	beq	.L3193
	cbz	w0, .L3194
	cmp	w0, 2
	bne	.L3192
	str	wzr, [x25, 3348]
	str	wzr, [x25, 3360]
	str	wzr, [x24, 1764]
	str	wzr, [x24, 1772]
.L3192:
	ldr	w1, [x25, 3408]
	mov	x0, x20
	bl	MVC_FlushDPB
	cmp	w0, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L3194:
	ldr	w2, [x25, 3348]
	ldr	w0, [x25, 3356]
	ldr	w1, [x25, 3360]
	sub	w0, w0, w2
	str	w0, [x25, 3356]
	sub	w1, w1, w2
	str	w1, [x25, 3360]
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x25, 3348]
	str	w0, [x25, 3352]
	ldr	w2, [x24, 1772]
	ldr	w0, [x24, 1760]
	ldr	w1, [x24, 1764]
	sub	w0, w0, w2
	str	w0, [x24, 1760]
	sub	w1, w1, w2
	str	w1, [x24, 1764]
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x24, 1768]
	str	w0, [x24, 1772]
	b	.L3192
.L3193:
	str	wzr, [x25, 3348]
	str	wzr, [x25, 3356]
	str	wzr, [x24, 1760]
	str	wzr, [x24, 1772]
	b	.L3192
	.size	MVC_AdaptiveMemMark, .-MVC_AdaptiveMemMark
	.align	3
.LC911:
	.xword	.L3183
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_IDRMemMarking
	.type	MVC_IDRMemMarking, %function
MVC_IDRMemMarking:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 11157504
	bl	_mcount
	ldr	x0, [x20, 3328]
	ldrb	w0, [x0, 1]
	cbz	w0, .L3200
	ldr	w0, [x22, 52]
	cbz	w0, .L3227
	sub	w4, w0, #1
	add	x24, x22, 11124736
	add	x4, x4, 38
	add	x2, x24, 440
	add	x1, x22, 148
	add	x4, x22, x4, lsl 2
	b	.L3208
	.p2align 3
.L3206:
	ldr	w3, [x0, 56]
	ldr	w0, [x20, 3408]
	cmp	w3, w0
	beq	.L3228
.L3205:
	add	x1, x1, 4
	cmp	x1, x4
	beq	.L3209
.L3208:
	ldr	x0, [x2]
	add	x2, x2, 8
	cbz	x0, .L3205
	ldr	w3, [x0, 16]
	cmp	w3, 1
	bne	.L3206
	strb	w3, [x22, 6]
	ldr	w3, [x0, 56]
	ldr	w0, [x20, 3408]
	cmp	w3, w0
	bne	.L3205
.L3228:
	str	wzr, [x1]
	add	x1, x1, 4
	cmp	x1, x4
	bne	.L3208
.L3209:
	ldr	w0, [x24, 824]
	cbz	w0, .L3203
	sub	w21, w0, #1
	add	x19, x24, 440
	add	x21, x21, 1388544
	mov	w23, 1
	add	x21, x21, 2104
	add	x21, x22, x21, lsl 3
	b	.L3214
	.p2align 3
.L3212:
	add	x19, x19, 8
	cmp	x19, x21
	beq	.L3203
.L3214:
	ldr	x0, [x19]
	cbz	x0, .L3212
	ldr	w2, [x0, 56]
	ldr	w1, [x20, 3408]
	cmp	w2, w1
	bne	.L3212
	strb	wzr, [x0, 714]
	mov	w2, 0
	strb	wzr, [x0, 713]
	ldr	x0, [x19]
	strb	wzr, [x0, 762]
	strb	wzr, [x0, 761]
	ldr	x0, [x19]
	strb	wzr, [x0, 810]
	strb	wzr, [x0, 809]
	ldr	x0, [x19]
	strb	wzr, [x0, 3]
	ldr	x1, [x19]
	ldr	w0, [x22, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetRef
	ldr	x0, [x19]
	strb	wzr, [x0, 2]
	ldr	x0, [x19]
	strb	wzr, [x0, 5]
	ldr	x0, [x19]
	strb	w23, [x0, 7]
	ldr	x1, [x19]
	ldr	w0, [x1, 52]
	add	x0, x22, x0
	add	x0, x0, 11124736
	strb	wzr, [x0, 848]
	ldrsb	w1, [x1, 6]
	ldr	w0, [x22, 120]
	bl	FSP_GetDisplay
	cmp	w0, 3
	mov	w2, 0
	beq	.L3213
	ldr	x1, [x19]
	ldr	w0, [x22, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
.L3213:
	str	xzr, [x19]
	add	x19, x19, 8
	str	xzr, [x19, 120]
	str	xzr, [x19, 248]
	cmp	x19, x21
	ldr	w0, [x24, 828]
	sub	w0, w0, #1
	str	w0, [x24, 828]
	bne	.L3214
	.p2align 2
.L3203:
	mov	x0, x22
	bl	MVC_UpdateReflist
	mov	x0, x22
	bl	MVC_UpdateLTReflist
	ldr	x0, [x20, 3328]
	ldrb	w0, [x0, 2]
	cbnz	w0, .L3229
	mov	w0, 1
	str	wzr, [x24, 840]
	strb	w0, [x20, 2669]
	mov	w0, 0
	strb	wzr, [x20, 2668]
.L3215:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3229:
	mov	w0, 1
	str	w0, [x24, 840]
	strb	w0, [x20, 2668]
	mov	w0, 0
	strb	wzr, [x20, 2669]
	str	wzr, [x20, 3340]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3200:
	ldr	w1, [x20, 3408]
	mov	x0, x22
	bl	MVC_FlushDPB
	cbnz	w0, .L3216
	add	x24, x22, 11124736
	b	.L3203
.L3227:
	add	x24, x22, 11124736
	b	.L3209
.L3216:
	mov	w0, -1
	b	.L3215
	.size	MVC_IDRMemMarking, .-MVC_IDRMemMarking
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_Marking
	.type	MVC_Marking, %function
MVC_Marking:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11157504
	bl	_mcount
	add	x0, x20, 11116544
	strb	wzr, [x0, 1736]
	ldrb	w1, [x19, 2667]
	cmp	w1, 2
	cset	w1, eq
	strb	w1, [x0, 1737]
	ldrb	w0, [x19, 2670]
	cmp	w0, 5
	beq	.L3231
	ldrb	w0, [x19, 2676]
	cbnz	w0, .L3232
	ldr	x0, [x20, 224]
	mov	x1, 4294967296
	ldr	x2, [x0, 696]
	cmp	x2, x1
	beq	.L3256
.L3232:
	ldr	x0, [x19, 3328]
	ldrb	w1, [x0, 3]
	cbz	w1, .L3257
	ldr	w0, [x19, 3344]
	cbnz	w0, .L3258
.L3239:
	mov	w0, 0
.L3254:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3257:
	ldr	w1, [x19, 3344]
	cbz	w1, .L3239
.L3242:
	ldrb	w1, [x19, 2665]
	cbnz	w1, .L3243
	add	x1, x20, 11124736
	ldr	x2, [x20, 248]
	ldr	w4, [x1, 836]
	ldr	w2, [x2, 3944]
	ldr	w3, [x1, 832]
	sub	w1, w2, w4
	cmp	w3, w1
	beq	.L3259
.L3244:
	strb	wzr, [x0]
	strb	wzr, [x19, 2668]
.L3235:
	ldr	w0, [x19, 3344]
	cbz	w0, .L3239
.L3243:
	ldrb	w1, [x19, 2668]
	mov	w0, 0
	cmp	w1, wzr
	cset	w1, eq
	strb	w1, [x19, 2669]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3256:
	ldr	w1, [x0, 704]
	cbnz	w1, .L3232
	ldr	w0, [x0, 660]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L3232
	.p2align 2
.L3231:
	mov	x0, x20
	bl	MVC_IDRMemMarking
	cbz	w0, .L3240
.L3233:
	mov	w0, -1
	b	.L3254
	.p2align 3
.L3258:
	mov	x0, x20
	bl	MVC_AdaptiveMemMark
	ldr	x1, [x19, 3328]
	strb	wzr, [x1]
	cbnz	w0, .L3233
.L3240:
	ldrb	w0, [x19, 2670]
	cmp	w0, 5
	beq	.L3235
	ldr	w0, [x19, 3344]
	cbz	w0, .L3239
	ldr	x0, [x19, 3328]
	ldrb	w1, [x0, 3]
	cbnz	w1, .L3243
	b	.L3242
	.p2align 3
.L3259:
	mov	x0, x20
	bl	MVC_SlidingWinMark.part.3
	ldr	x0, [x19, 3328]
	b	.L3244
	.size	MVC_Marking, .-MVC_Marking
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DirectOutput
	.type	MVC_DirectOutput, %function
MVC_DirectOutput:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 11157504
	bl	_mcount
	ldrb	w0, [x20, 2667]
	cmp	w0, 1
	beq	.L3262
	cbz	w0, .L3263
	cmp	w0, 2
	beq	.L3264
	mov	w21, 0
.L3261:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3264:
	ldr	x0, [x20, 3320]
	mov	w1, 3
	strb	w1, [x0, 712]
	ldrb	w0, [x20, 2665]
	cbnz	w0, .L3279
	ldr	x1, [x19, 816]
	cbz	x1, .L3280
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x20, 3320]
	str	x0, [x19, 816]
	str	x0, [x0, 816]
.L3281:
	ldr	x0, [x19, 816]
	mov	w22, 2
	ldrb	w3, [x20, 2666]
	mov	x2, 640
	add	x1, x20, 2680
	strb	w3, [x0, 1]
	ldr	x0, [x19, 816]
	strb	w22, [x0, 2]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 5]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 7]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 3]
	ldr	x0, [x19, 816]
	ldrb	w3, [x20, 2676]
	strb	w3, [x0]
	ldr	x0, [x19, 816]
	str	wzr, [x0, 40]
	ldr	x0, [x19, 816]
	add	x0, x0, 72
	bl	memcpy
	ldr	x1, [x19, 816]
	mov	w0, 2
	ldr	w2, [x20, 3380]
	str	w2, [x1, 840]
	ldr	x1, [x19, 816]
	ldr	w2, [x1, 840]
	str	w2, [x1, 44]
	str	w2, [x1, 744]
	ldr	x1, [x19, 816]
	strb	w22, [x1, 808]
	ldrb	w2, [x20, 2671]
	ldr	x1, [x19, 816]
	cmp	w2, 1
	csel	w0, wzr, w0, ne
	strb	w0, [x1, 4]
.L3336:
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3348]
	str	w1, [x0, 32]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3408]
	str	w1, [x0, 56]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3412]
	str	w1, [x0, 60]
	ldrb	w22, [x19, 9]
	cmp	w22, 1
	bne	.L3261
	ldr	x1, [x19, 816]
	mov	w2, 0
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetRef
	ldr	x1, [x19, 816]
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x19, 816]
	cbz	x0, .L3289
	ldr	x1, [x20, 3320]
	mov	w2, w22
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
.L3289:
	str	xzr, [x19, 816]
.L3339:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3263:
	ldr	x0, [x20, 3320]
	strb	wzr, [x0, 712]
	ldr	x1, [x19, 816]
	cbz	x1, .L3265
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	cbnz	w0, .L3338
.L3266:
	ldr	x0, [x19, 816]
	cbz	x0, .L3265
	ldr	x1, [x20, 3320]
	mov	w2, 1
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
.L3265:
	ldr	x0, [x20, 3320]
	mov	w3, 3
	str	x0, [x19, 816]
	mov	x2, 640
	add	x1, x20, 2680
	str	x0, [x0, 720]
	ldr	x0, [x19, 816]
	ldr	x4, [x20, 3320]
	str	x4, [x0, 768]
	ldr	x0, [x19, 816]
	ldr	x4, [x20, 3320]
	str	x4, [x0, 816]
	ldr	x0, [x19, 816]
	ldrb	w4, [x20, 2666]
	strb	w4, [x0, 1]
	ldr	x0, [x19, 816]
	strb	w3, [x0, 2]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 3]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 5]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 7]
	ldr	x0, [x19, 816]
	add	x0, x0, 72
	bl	memcpy
	ldr	x1, [x19, 816]
	mov	w0, 3
	ldr	w3, [x20, 3380]
	mov	w2, 0
	str	w3, [x1, 44]
	str	w3, [x1, 744]
	ldr	x1, [x19, 816]
	strb	wzr, [x1, 712]
	ldr	x1, [x19, 816]
	ldrb	w3, [x20, 2676]
	strb	w3, [x1]
	ldr	x1, [x19, 816]
	ldrb	w3, [x20, 2673]
	str	w3, [x1, 40]
	ldrb	w3, [x20, 2671]
	ldr	x1, [x19, 816]
	cmp	w3, 1
	csel	w0, wzr, w0, ne
	strb	w0, [x1, 4]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3348]
	str	w1, [x0, 32]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3408]
	str	w1, [x0, 56]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3412]
	str	w1, [x0, 60]
.L3334:
	ldr	x1, [x19, 816]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetRef
	ldr	x1, [x19, 816]
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x19, 816]
	cbz	x0, .L3289
	ldr	x1, [x20, 3320]
	mov	w2, 1
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
	str	xzr, [x19, 816]
	b	.L3339
	.p2align 3
.L3262:
	ldr	x0, [x20, 3320]
	mov	w1, 3
	strb	w1, [x0, 712]
	ldrb	w0, [x20, 2665]
	cbnz	w0, .L3269
	ldr	x1, [x19, 816]
	cbz	x1, .L3270
	mov	w2, 0
	mov	x0, x19
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x20, 3320]
	str	x0, [x19, 816]
	str	x0, [x0, 768]
.L3271:
	ldr	x0, [x19, 816]
	mov	w22, 1
	ldrb	w3, [x20, 2666]
	add	x1, x20, 2680
	mov	x2, 640
	strb	w3, [x0, 1]
	ldr	x0, [x19, 816]
	strb	w22, [x0, 2]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 5]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 7]
	ldr	x0, [x19, 816]
	strb	wzr, [x0, 3]
	ldr	x0, [x19, 816]
	ldrb	w3, [x20, 2676]
	strb	w3, [x0]
	ldr	x0, [x19, 816]
	str	wzr, [x0, 40]
	ldr	x0, [x19, 816]
	add	x0, x0, 72
	bl	memcpy
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3380]
	str	w1, [x0, 792]
	ldr	x0, [x19, 816]
	ldr	w1, [x0, 792]
	str	w1, [x0, 44]
	str	w1, [x0, 744]
	ldr	x0, [x19, 816]
	strb	w22, [x0, 760]
	ldrb	w1, [x20, 2671]
	ldr	x0, [x19, 816]
	cmp	w1, 1
	cset	w1, eq
	strb	w1, [x0, 4]
	b	.L3336
	.p2align 3
.L3279:
	ldr	x3, [x19, 816]
	cbz	x3, .L3340
.L3284:
	mov	x2, 640
	add	x1, x20, 2680
	add	x0, x3, 72
	ldr	x23, [x3, 656]
	ldr	x22, [x3, 664]
	ldr	x21, [x3, 672]
	bl	memcpy
	ldr	x0, [x20, 3264]
	cmn	x0, #1
	ccmn	x23, #1, 4, eq
	beq	.L3285
	ldr	x0, [x19, 816]
	str	x23, [x0, 656]
.L3285:
	ldr	x0, [x20, 3272]
	ldr	x1, [x19, 816]
	cmp	x0, x22
	csel	x0, x0, x22, ls
	str	x0, [x1, 664]
	ldr	x0, [x20, 3280]
	ldr	x1, [x19, 816]
	cmp	x0, x21
	csel	x0, x0, x21, ls
	str	x0, [x1, 672]
	ldr	x1, [x19, 816]
	ldrb	w0, [x1, 1]
	cbz	w0, .L3286
	ldrb	w0, [x20, 2666]
.L3286:
	strb	w0, [x1, 1]
	mov	w4, 2
	mov	w3, 3
	ldr	x1, [x19, 816]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 2
	strb	w0, [x1, 2]
	ldr	x1, [x19, 816]
	ldrb	w0, [x20, 2676]
	ldrb	w2, [x1]
	cmp	w0, w2, uxtb
	csel	w0, w0, w2, cs
	strb	w0, [x1]
	ldr	x0, [x19, 816]
	strb	w4, [x0, 808]
	ldr	x0, [x19, 816]
	strb	w3, [x0, 712]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3380]
	str	w1, [x0, 840]
	ldr	x1, [x19, 816]
	ldr	w2, [x1, 792]
	ldr	w0, [x1, 840]
	add	w0, w2, w0
	lsr	w0, w0, 1
	str	w0, [x1, 744]
	ldr	x0, [x19, 816]
	ldr	w1, [x0, 744]
	str	w1, [x0, 44]
	ldr	x0, [x19, 816]
	ldr	x1, [x0, 816]
	str	x1, [x0, 720]
	ldrb	w0, [x20, 2671]
	ldr	x1, [x19, 816]
	cmp	w0, 1
	beq	.L3341
.L3287:
	ldrb	w0, [x1, 4]
.L3288:
	strb	w0, [x1, 4]
	mov	w2, 0
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3348]
	str	w1, [x0, 32]
	b	.L3334
	.p2align 3
.L3269:
	ldr	x3, [x19, 816]
	cbz	x3, .L3342
.L3273:
	mov	x2, 640
	add	x1, x20, 2680
	add	x0, x3, 72
	ldr	x23, [x3, 656]
	ldr	x22, [x3, 664]
	ldr	x21, [x3, 672]
	bl	memcpy
	ldr	x0, [x20, 3264]
	cmn	x0, #1
	ccmn	x23, #1, 4, eq
	beq	.L3274
	ldr	x0, [x19, 816]
	str	x23, [x0, 656]
.L3274:
	ldr	x0, [x20, 3272]
	ldr	x1, [x19, 816]
	cmp	x0, x22
	csel	x0, x0, x22, ls
	str	x0, [x1, 664]
	ldr	x0, [x20, 3280]
	ldr	x1, [x19, 816]
	cmp	x0, x21
	csel	x0, x0, x21, ls
	str	x0, [x1, 672]
	ldr	x1, [x19, 816]
	ldrb	w0, [x1, 1]
	cbz	w0, .L3275
	ldrb	w0, [x20, 2666]
.L3275:
	strb	w0, [x1, 1]
	mov	w4, 1
	mov	w3, 3
	ldr	x1, [x19, 816]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 1
	strb	w0, [x1, 2]
	ldr	x1, [x19, 816]
	ldrb	w0, [x20, 2676]
	ldrb	w2, [x1]
	cmp	w0, w2, uxtb
	csel	w0, w0, w2, cs
	strb	w0, [x1]
	ldr	x0, [x19, 816]
	strb	w4, [x0, 760]
	ldr	x0, [x19, 816]
	strb	w3, [x0, 712]
	ldr	x0, [x19, 816]
	ldr	w1, [x20, 3380]
	str	w1, [x0, 792]
	ldr	x1, [x19, 816]
	ldr	w2, [x1, 792]
	ldr	w0, [x1, 840]
	add	w0, w2, w0
	lsr	w0, w0, w4
	str	w0, [x1, 744]
	ldr	x0, [x19, 816]
	ldr	w1, [x0, 744]
	str	w1, [x0, 44]
	ldr	x0, [x19, 816]
	ldr	x1, [x0, 768]
	str	x1, [x0, 720]
	ldrb	w0, [x20, 2671]
	ldr	x1, [x19, 816]
	cmp	w0, 1
	bne	.L3287
	ldrb	w0, [x1, 4]
	orr	w0, w0, 1
	uxtb	w0, w0
	b	.L3288
	.p2align 3
.L3338:
	ldr	x2, .LC912
	mov	w4, w0
	ldr	x1, .LC914
	mov	w3, 2446
	add	x2, x2, 256
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3266
	.p2align 3
.L3341:
	ldrb	w0, [x1, 4]
	orr	w0, w0, 2
	uxtb	w0, w0
	b	.L3288
	.p2align 3
.L3270:
	ldr	x0, [x20, 3320]
	mov	w21, 0
	str	x0, [x19, 816]
	str	x0, [x0, 768]
	b	.L3271
	.p2align 3
.L3280:
	ldr	x0, [x20, 3320]
	mov	w21, 0
	str	x0, [x19, 816]
	str	x0, [x0, 816]
	b	.L3281
	.p2align 3
.L3340:
	ldr	x0, [x20, 3320]
	str	x0, [x19, 816]
	str	x0, [x0, 816]
	ldr	x3, [x19, 816]
	b	.L3284
	.p2align 3
.L3342:
	ldr	x0, [x20, 3320]
	str	x0, [x19, 816]
	str	x0, [x0, 768]
	ldr	x3, [x19, 816]
	b	.L3273
	.size	MVC_DirectOutput, .-MVC_DirectOutput
	.align	3
.LC912:
	.xword	.LANCHOR0
	.align	3
.LC914:
	.xword	.LC913
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_GetRemainImg
	.type	MVC_DEC_GetRemainImg, %function
MVC_DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	cbz	x22, .L3344
	add	x19, x22, 11124736
	mov	w20, 0
	mov	w21, 0
	ldr	w0, [x19, 824]
	cbnz	w0, .L3372
	b	.L3385
	.p2align 3
.L3348:
	ldr	w0, [x19, 824]
	cmp	w0, w21
	bls	.L3386
.L3372:
	uxtw	x0, w21
	add	w21, w21, 1
	add	x0, x0, 1388544
	add	x0, x22, x0, lsl 3
	ldr	x0, [x0, 16824]
	cbz	x0, .L3348
	ldrb	w1, [x0, 5]
	cbz	w1, .L3348
	ldrsb	w1, [x0, 6]
	ldr	w0, [x22, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L3348
	ldrb	w0, [x0, 1]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 1
	ldr	w0, [x19, 824]
	csinc	w20, w20, w20, hi
	cmp	w0, w21
	bhi	.L3372
.L3386:
	mov	w21, -1
	cbnz	w20, .L3353
	b	.L3350
	.p2align 3
.L3351:
	add	x1, x22, x1, lsl 3
	ldr	x1, [x1, 16824]
	bl	MVC_OutputFrmToVO
	mov	w21, w0
	subs	w20, w20, #1
	beq	.L3383
.L3353:
	add	x2, x29, 60
	mov	w1, -1
	add	x3, x29, 56
	mov	x0, x22
	bl	MVC_GetMinPOC
	ldr	w1, [x29, 56]
	mov	w2, w20
	mov	x0, x22
	cmn	w1, #1
	uxtw	x1, w1
	add	x1, x1, 1388544
	bne	.L3351
.L3383:
	ldr	w0, [x19, 824]
	cbz	w0, .L3346
.L3352:
	mov	w20, 0
	b	.L3356
	.p2align 3
.L3355:
	ldr	w0, [x19, 824]
	cmp	w0, w20
	bls	.L3346
.L3356:
	uxtw	x0, w20
	add	w20, w20, 1
	add	x0, x0, 1388544
	add	x0, x22, x0, lsl 3
	ldr	x1, [x0, 16824]
	cbz	x1, .L3355
	ldrb	w0, [x1, 3]
	cbz	w0, .L3355
	mov	x0, x22
	bl	MVC_UnMarkFrameStoreRef
	ldr	w0, [x19, 824]
	cmp	w0, w20
	bhi	.L3356
.L3346:
	mov	w1, -1
	mov	x0, x22
	bl	MVC_RemoveUnUsedFrameStore
	mov	w0, 0
	cbnz	w21, .L3357
.L3371:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3350:
	cbnz	w0, .L3352
	mov	w1, w21
	mov	x0, x22
	bl	MVC_RemoveUnUsedFrameStore
.L3357:
	add	x0, x22, 912
	bl	GetVoLastImageID
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L3385:
	mov	w21, -1
	b	.L3346
.L3344:
	ldr	x3, .LC915
	mov	w2, 2838
	ldr	x1, .LC916
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3371
	.size	MVC_DEC_GetRemainImg, .-MVC_DEC_GetRemainImg
	.align	3
.LC915:
	.xword	.LC61
	.align	3
.LC916:
	.xword	.LC63
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	MVC_InitDPB.part.17, %function
MVC_InitDPB.part.17:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x22, x20, 11124736
	add	x19, x22, 440
	add	x21, x22, 568
	bl	_mcount
	.p2align 2
.L3391:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L3388
	ldrsb	w1, [x0, 6]
	ldr	w0, [x20, 120]
	bl	FSP_ClearLogicFs
.L3388:
	ldr	x0, [x19, 128]
	mov	w2, 1
	cbz	x0, .L3389
	ldrsb	w1, [x0, 6]
	ldr	w0, [x20, 120]
	bl	FSP_ClearLogicFs
.L3389:
	ldr	x0, [x19, 256]
	mov	w2, 1
	cbz	x0, .L3390
	ldrsb	w1, [x0, 6]
	ldr	w0, [x20, 120]
	bl	FSP_ClearLogicFs
.L3390:
	str	xzr, [x19, 128]
	str	xzr, [x19, 256]
	str	xzr, [x19], 8
	cmp	x19, x21
	bne	.L3391
	add	x1, x22, 768
	ldr	w0, [x20, 44]
	stp	w0, wzr, [x1, 56]
	stp	wzr, wzr, [x1, 64]
	str	wzr, [x22, 840]
	ldr	x1, [x20, 816]
	cbz	x1, .L3393
	ldrb	w0, [x20, 8]
	cmp	w0, 2
	beq	.L3394
.L3398:
	add	x0, x20, 11157504
	ldr	x0, [x0, 3320]
	cbz	x0, .L3396
	ldrsb	w1, [x0, 6]
	mov	w2, 1
	ldr	w0, [x20, 120]
	bl	FSP_ClearLogicFs
.L3396:
	str	xzr, [x20, 816]
.L3393:
	ldr	x3, .LC920
	mov	w1, 0
	mov	x2, 344
	add	x0, x22, 848
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x22, 1060]
	ldr	w0, [x22, 824]
	add	x1, x20, 220
	str	w0, [x22, 1056]
	add	x0, x20, 148
	.p2align 2
.L3400:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L3400
	add	x1, x20, 288
	add	x0, x20, 552
	.p2align 2
.L3401:
	str	xzr, [x1], 8
	cmp	x1, x0
	bne	.L3401
	add	x1, x20, 11116544
	add	x20, x20, 816
	str	wzr, [x1, 2920]
	.p2align 2
.L3402:
	str	xzr, [x0], 8
	cmp	x20, x0
	bne	.L3402
	str	wzr, [x1, 2924]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L3394:
	mov	w2, 0
	mov	x0, x20
	bl	MVC_OutputFrmToVO
	cbnz	w0, .L3419
.L3397:
	ldr	x0, [x20, 816]
	cbnz	x0, .L3398
	b	.L3393
	.p2align 3
.L3419:
	ldr	x2, .LC917
	mov	w4, w0
	ldr	x1, .LC919
	mov	w3, 5724
	add	x2, x2, 280
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3397
	.size	MVC_InitDPB.part.17, .-MVC_InitDPB.part.17
	.align	3
.LC917:
	.xword	.LANCHOR0
	.align	3
.LC919:
	.xword	.LC918
	.align	3
.LC920:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InitDPB
	.type	MVC_InitDPB, %function
MVC_InitDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L3422
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.17
.L3421:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3422:
	mov	w0, -1
	b	.L3421
	.size	MVC_InitDPB, .-MVC_InitDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearDPB
	.type	MVC_ClearDPB, %function
MVC_ClearDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	MVC_FlushDPB
	cbnz	w0, .L3431
	cbz	x19, .L3427
.L3425:
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.17
	cbnz	w0, .L3427
	strb	wzr, [x19, 6]
	mov	w0, 0
	str	wzr, [x19, 220]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3431:
	ldr	x2, .LC921
	mov	w3, 313
	ldr	x1, .LC923
	mov	w0, 22
	add	x2, x2, 296
	bl	dprint_vfmw
	cbnz	x19, .L3425
.L3427:
	ldr	x2, .LC921
	mov	w3, 318
	ldr	x1, .LC925
	mov	w0, 22
	add	x2, x2, 296
	bl	dprint_vfmw
	strb	wzr, [x19, 6]
	str	wzr, [x19, 220]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_ClearDPB, .-MVC_ClearDPB
	.align	3
.LC921:
	.xword	.LANCHOR0
	.align	3
.LC923:
	.xword	.LC922
	.align	3
.LC925:
	.xword	.LC924
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecVDM
	.type	MVC_DecVDM, %function
MVC_DecVDM:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11157504
	bl	_mcount
	ldrb	w0, [x21, 2667]
	cbz	w0, .L3433
	ldrb	w0, [x21, 2665]
	cmp	w0, 1
	beq	.L3433
.L3434:
	ldr	w0, [x19, 108]
	ldrb	w1, [x19, 8]
	ubfx	x20, x0, 16, 2
	cmp	w20, w1
	beq	.L3435
	sub	w1, w1, #2
	uxtb	w1, w1
	cmp	w1, 1
	ccmp	w20, 1, 2, ls
	bls	.L3506
.L3435:
	uxtb	w0, w20
	strb	w0, [x19, 8]
	cmp	w0, 2
	beq	.L3438
	cmp	w0, 3
	beq	.L3439
	cmp	w0, 1
	beq	.L3507
	ldrb	w0, [x19, 11]
	cmp	w0, 1
	beq	.L3508
.L3448:
	ldrb	w0, [x21, 2677]
	ldr	w1, [x19, 64]
	strb	w0, [x19, 11]
	cbz	w1, .L3503
.L3453:
	ldrb	w0, [x21, 2676]
	cmp	w0, 2
	beq	.L3454
	cmp	w0, 1
	beq	.L3509
.L3456:
	ldr	w2, [x19, 88]
	mov	w0, 2
	ldrb	w3, [x21, 2667]
	add	x20, x19, 11161600
	ldr	x1, .LC931
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	w0, [x21, 3396]
	str	w0, [x20, 1932]
	mov	w0, 1
	strb	w0, [x20, 1194]
	ldr	w0, [x21, 3400]
	str	w0, [x20, 1928]
	ldr	w0, [x19, 64]
	str	w0, [x20, 2132]
	ldr	w0, [x19, 88]
	cbz	w0, .L3457
	ldrb	w0, [x21, 2676]
	cbz	w0, .L3510
	add	x0, x19, 11124736
	ldr	w0, [x0, 828]
	cbnz	w0, .L3459
	ldr	x1, [x19, 224]
	ldr	w0, [x1, 24]
	cmp	w0, 2
	bne	.L3503
.L3462:
	add	x2, x20, 1192
	str	x2, [x19, 232]
	ldr	w0, [x1, 952]
	cmp	w0, 1
	beq	.L3511
.L3463:
	cmp	w0, 2
	bne	.L3464
	ldr	w0, [x1, 956]
	cmp	w0, wzr
	ccmp	x2, xzr, 4, gt
	beq	.L3464
	ldrb	w0, [x21, 2676]
	cmp	w0, 2
	bne	.L3464
	str	xzr, [x19, 232]
	mov	w2, 0
	ldr	w0, [x19, 120]
	ldr	x1, [x21, 3320]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	ldr	x2, [x19, 224]
	mov	x0, x19
	ldr	w1, [x2, 956]
	sub	w1, w1, #1
	str	w1, [x2, 956]
	bl	MVC_ClearCurrPic
	mov	w0, -1
	b	.L3498
	.p2align 3
.L3433:
	ldp	w0, w1, [x19, 140]
	ldr	x2, [x19, 224]
	add	w0, w0, 1
	cmp	w0, w1
	csel	w0, w0, w1, ge
	str	w0, [x19, 140]
	sub	w0, w0, w1
	str	w0, [x2, 624]
	b	.L3434
.L3506:
	ldr	x1, .LC927
	mov	w2, w20
	mov	w0, 2
	bl	dprint_vfmw
	strb	w20, [x19, 8]
	.p2align 2
.L3439:
	mov	x0, x19
	bl	MVC_ClearCurrPic
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	mov	w0, -1
.L3498:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3457:
	ldr	x1, [x19, 224]
.L3464:
	ldr	w2, [x1, 640]
	mov	w0, 0
	strb	w2, [x20, 1196]
	ldr	w2, [x1, 644]
	strb	w2, [x20, 1197]
	ldr	w2, [x1, 648]
	str	w2, [x20, 1200]
	ldr	w2, [x1, 652]
	str	w2, [x20, 1204]
	ldr	w1, [x1, 692]
	strb	w1, [x20, 1208]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3507:
	ldrb	w0, [x21, 2676]
	cmp	w0, 2
	bne	.L3448
	ldr	w0, [x21, 3344]
	cbz	w0, .L3443
	ldrb	w0, [x19, 11]
	cmp	w0, 1
	bne	.L3448
.L3465:
	ldrb	w1, [x21, 2677]
	ldr	w0, [x19, 64]
	strb	w1, [x19, 11]
	cbz	w0, .L3503
.L3454:
	ldrb	w0, [x19, 7]
	cmp	w0, 2
	bne	.L3456
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 24]
	cbnz	w0, .L3456
	ldr	x1, .LC929
	mov	w0, 1
	ldr	w3, [x21, 3344]
	ldr	w2, [x21, 3348]
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_ClearCurrPic
	ldr	x1, [x21, 3320]
	mov	w2, 0
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	mov	w0, -1
	b	.L3498
	.p2align 3
.L3438:
	ldrb	w0, [x21, 2676]
	cbnz	w0, .L3443
	ldr	w0, [x19, 64]
	cbz	w0, .L3442
	ldr	x0, [x19, 864]
	ldr	w0, [x0, 48]
	cbnz	w0, .L3443
	ldrb	w0, [x21, 2677]
	strb	w0, [x19, 11]
	b	.L3453
	.p2align 3
.L3509:
	ldr	w1, [x21, 3408]
	cbnz	w1, .L3456
	strb	w0, [x19, 7]
	b	.L3456
	.p2align 3
.L3510:
	ldr	x0, .LC932
	ldr	x5, [x0]
	cbz	x5, .L3459
	ldr	x1, [x20, 2136]
	cbz	x1, .L3466
	mov	w2, 0
	.p2align 2
.L3461:
	ldp	w3, w0, [x1, 8]
	ldr	x1, [x1, 4056]
	add	w0, w3, w0
	add	w0, w0, 7
	add	w2, w2, w0, lsr 3
	mov	w4, w2
	cbnz	x1, .L3461
.L3460:
	add	x2, x29, 64
	ldr	w0, [x19, 120]
	mov	w1, 20
	mov	w3, 4
	str	w4, [x2, -8]!
	blr	x5
	ldr	x1, [x19, 224]
	add	x2, x20, 1192
	str	x2, [x19, 232]
	ldr	w0, [x1, 952]
	cmp	w0, 1
	bne	.L3463
.L3511:
	cbz	x2, .L3464
	ldrb	w0, [x21, 2676]
	cmp	w0, 2
	bne	.L3464
	str	xzr, [x19, 232]
	mov	w2, 0
	ldr	w0, [x19, 120]
	ldr	x1, [x21, 3320]
	ldrsb	w1, [x1, 6]
	bl	FSP_SetDisplay
	b	.L3503
	.p2align 3
.L3508:
	ldrb	w0, [x21, 2676]
	cmp	w0, 2
	beq	.L3465
	b	.L3448
	.p2align 3
.L3459:
	ldr	x1, [x19, 224]
	b	.L3462
	.p2align 3
.L3442:
	ldrb	w0, [x21, 2677]
	strb	w0, [x19, 11]
.L3503:
	mov	x0, x19
	bl	MVC_ClearCurrPic
	mov	w0, -1
	b	.L3498
.L3466:
	mov	w4, 0
	b	.L3460
.L3443:
	mov	w1, 1
	mov	x0, x19
	strb	w1, [x21, 2671]
	bl	MVC_ClearCurrPic
	mov	w0, -1
	b	.L3498
	.size	MVC_DecVDM, .-MVC_DecVDM
	.align	3
.LC927:
	.xword	.LC926
	.align	3
.LC929:
	.xword	.LC928
	.align	3
.LC931:
	.xword	.LC930
	.align	3
.LC932:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_FlushDecoder
	.type	MVC_FlushDecoder, %function
MVC_FlushDecoder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L3518
	add	x2, x19, 11116544
	mov	w1, 1
	mov	x0, x19
	strb	w1, [x2, 2877]
	str	wzr, [x2, 2928]
	strb	w1, [x19]
	bl	MVC_DecVDM
	cbz	w0, .L3512
	ldr	x2, .LC934
	mov	w3, 12480
	ldr	x1, .LC936
	mov	w0, 22
	add	x2, x2, 312
	bl	dprint_vfmw
.L3512:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3518:
	ldr	x1, .LC933
	mov	w2, 12468
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	MVC_FlushDecoder, .-MVC_FlushDecoder
	.align	3
.LC933:
	.xword	.LC893
	.align	3
.LC934:
	.xword	.LANCHOR0
	.align	3
.LC936:
	.xword	.LC935
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ReceivePacket
	.type	MVC_ReceivePacket, %function
MVC_ReceivePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11161600
	bl	_mcount
	ldr	x1, .LC938
	mov	w0, 7
	ldp	w3, w4, [x20, 16]
	ldr	x2, [x20, 8]
	bl	dprint_vfmw
	str	wzr, [x21, 2384]
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 912]
	cmp	w1, 1
	beq	.L3584
.L3520:
	ldr	x0, [x19, 240]
	cbz	x0, .L3525
	ldrb	w1, [x20]
	cmp	w1, 1
	beq	.L3585
.L3523:
	ldr	x1, .LC940
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbz	x1, .L3525
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L3525:
	ldr	w0, [x20, 20]
	cmp	w0, wzr
	ble	.L3527
	ldr	x0, [x20, 8]
	cbz	x0, .L3527
	ldr	w0, [x20, 16]
	cbz	w0, .L3527
	ldrb	w0, [x19, 1521]
	cbz	w0, .L3545
	add	x1, x19, 1617
	mov	x0, 1
	b	.L3530
	.p2align 3
.L3529:
	add	w0, w0, 1
	cmp	w0, 137
	beq	.L3543
.L3530:
	ldrb	w2, [x1]
	add	x1, x1, 96
	cbnz	w2, .L3529
	sxtw	x1, w0
.L3528:
	lsl	x2, x0, 2
	mov	w3, 1
	sub	x0, x2, x0
	cmn	w1, #1
	add	x0, x19, x0, lsl 5
	strb	w3, [x0, 1521]
	beq	.L3543
	lsl	x0, x1, 2
	mov	w2, 1
	sub	x0, x0, x1
	lsl	x0, x0, 5
	add	x1, x0, 1520
	add	x0, x19, x0
	add	x1, x19, x1
	str	x1, [x19, 240]
	ldr	x1, [x20, 8]
	str	x1, [x0, 1528]
	ldr	w1, [x20, 20]
	str	w1, [x0, 1536]
	ldr	w1, [x20, 16]
	str	w1, [x0, 1540]
	ldr	x0, [x19, 240]
	str	wzr, [x0, 28]
	ldr	x0, [x19, 240]
	ldr	w1, [x20, 24]
	str	w1, [x0, 36]
	ldr	x0, [x19, 240]
	ldr	x1, [x20, 32]
	str	x1, [x0, 88]
	ldr	x0, [x19, 240]
	str	w2, [x0, 76]
	ldr	x0, [x19, 240]
	strb	wzr, [x0]
	ldr	x0, [x19, 240]
	ldrb	w1, [x20]
	strb	w1, [x0, 3]
	ldr	x0, [x19, 240]
	b	.L3535
	.p2align 3
.L3585:
	ldr	w2, [x0, 76]
	cmp	w2, 1
	bhi	.L3523
	ldrb	w2, [x0, 3]
	cmp	w2, 1
	bne	.L3524
	b	.L3523
	.p2align 3
.L3584:
	ldr	w0, [x0, 960]
	cbz	w0, .L3520
	ldr	x0, [x19, 240]
	cbz	x0, .L3525
	ldrb	w1, [x20]
.L3524:
	strb	w1, [x0, 3]
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 912]
	cmp	w1, 1
	beq	.L3586
.L3537:
	ldr	w0, [x20, 20]
	cmp	w0, wzr
	ble	.L3538
	ldr	x1, [x20, 8]
	cbz	x1, .L3538
	ldr	w0, [x20, 16]
	cbz	w0, .L3538
	ldr	x0, [x19, 240]
	ldr	w2, [x0, 76]
	cmp	w2, 1
	bls	.L3587
.L3539:
	mov	w1, 1
	strb	w1, [x0, 3]
	ldr	w0, [x19, 120]
	ldr	w1, [x20, 24]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC943
	ldr	x4, [x0]
	cbz	x4, .L3581
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3581:
	ldr	x0, [x19, 240]
.L3535:
	ldrb	w0, [x0, 3]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	ldr	x21, [sp, 32]
	csetm	w0, eq
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3527:
	ldr	x1, .LC945
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 120]
	ldr	w1, [x20, 24]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC943
	ldr	x4, [x0]
	cbz	x4, .L3583
.L3582:
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3583:
	mov	w0, -1
.L3590:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3538:
	ldr	x0, [x19, 240]
	b	.L3539
	.p2align 3
.L3586:
	ldr	w0, [x0, 960]
	cbnz	w0, .L3581
	b	.L3537
	.p2align 3
.L3587:
	ubfiz	x2, x2, 5, 32
	add	x0, x0, x2
	str	x1, [x0, 8]
	ldr	x1, [x19, 240]
	ldr	w2, [x20, 20]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 16]
	ldr	x1, [x19, 240]
	ldr	w2, [x20, 16]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 20]
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	wzr, [x0, 28]
	ldr	x1, [x19, 240]
	ldr	w2, [x20, 24]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 36]
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 76]
	add	w0, w0, 1
	str	w0, [x1, 76]
	ldr	x0, [x19, 240]
	ldr	w1, [x0, 16]
	cmp	w1, 4095
	bls	.L3588
.L3540:
	mov	w1, 1
	str	w1, [x21, 2384]
	b	.L3535
	.p2align 3
.L3588:
	mov	x0, x19
	bl	MVC_CombinePacket.part.14
	ldr	x0, [x19, 240]
	b	.L3540
.L3543:
	ldr	x1, .LC942
	mov	w0, 0
	add	x21, x19, 12288
	add	x20, x19, 1520
	add	x21, x21, 2384
	bl	dprint_vfmw
	b	.L3532
	.p2align 3
.L3531:
	add	x20, x20, 96
	cmp	x21, x20
	beq	.L3589
.L3532:
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	bne	.L3531
	ldr	w0, [x19, 120]
	mov	x1, x20
	bl	MVC_ReleaseNAL
	b	.L3531
.L3589:
	mov	x0, x19
	bl	MVC_ClearCurrPic
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	x0, .LC943
	ldr	x4, [x0]
	cbnz	x4, .L3582
	mov	w0, -1
	b	.L3590
.L3545:
	mov	x1, 0
	mov	x0, 0
	b	.L3528
	.size	MVC_ReceivePacket, .-MVC_ReceivePacket
	.align	3
.LC938:
	.xword	.LC937
	.align	3
.LC940:
	.xword	.LC939
	.align	3
.LC942:
	.xword	.LC941
	.align	3
.LC943:
	.xword	g_event_report
	.align	3
.LC945:
	.xword	.LC944
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_ClearAll
	.type	MVC_ClearAll, %function
MVC_ClearAll:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	add	x20, x21, 12288
	bl	_mcount
	add	x19, x21, 1520
	ldr	x1, .LC947
	mov	w0, 22
	add	x20, x20, 2384
	bl	dprint_vfmw
	mov	x0, x21
	bl	MVC_ClearCurrPic
	b	.L3593
	.p2align 3
.L3592:
	add	x19, x19, 96
	cmp	x19, x20
	beq	.L3624
.L3593:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L3592
	ldr	w0, [x21, 120]
	mov	x1, x19
	add	x19, x19, 96
	bl	MVC_ReleaseNAL
	cmp	x19, x20
	bne	.L3593
.L3624:
	cbz	x21, .L3596
	mov	x0, x21
	bl	MVC_ClearAllSlice
	mov	x0, x21
	bl	MVC_InitDPB.part.17
	cbnz	w0, .L3596
.L3595:
	cbz	w22, .L3597
	ldr	w0, [x21, 120]
	add	x1, x21, 912
	bl	FSP_ClearNotInVoQueue
.L3598:
	mov	x28, x21
	mov	w27, 0
	mov	w26, -1
	mov	w22, 1
	mov	w25, 18
	mov	w24, 16
	mov	w23, 2
	.p2align 2
.L3601:
	add	x0, x28, 11124736
	add	x2, x0, 1024
	add	x1, x0, 1192
	add	x19, x0, 1808
	add	x20, x0, 1840
	strb	wzr, [x0, 1193]
	strb	wzr, [x0, 1194]
	strb	wzr, [x0, 1195]
	strb	wzr, [x0, 1197]
	strb	w22, [x0, 1199]
	strb	wzr, [x0, 1904]
	strb	w22, [x0, 1952]
	strb	w23, [x0, 2000]
	stp	wzr, w26, [x2, 188]
	stp	wzr, wzr, [x2, 196]
	str	w25, [x0, 1240]
	str	w24, [x0, 1244]
	str	w27, [x0, 1412]
	str	x1, [x0, 1912]
	str	x1, [x0, 1960]
	str	x1, [x0, 2008]
.L3600:
	ldr	x1, [x19]
	cbnz	x1, .L3625
.L3599:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L3600
	add	w27, w27, 1
	add	x28, x28, 856
	cmp	w27, 40
	bne	.L3601
	add	x22, x21, 11157504
	add	x19, x22, 3224
	add	x20, x22, 3256
.L3603:
	ldr	x1, [x19]
	cbnz	x1, .L3626
.L3602:
	add	x19, x19, 8
	cmp	x20, x19
	bne	.L3603
	ldr	w2, [x21, 60]
	mov	w19, 0
	cbz	w2, .L3607
	.p2align 2
.L3614:
	add	x20, x21, x19, uxtw 3
	add	w19, w19, 1
	ldr	x0, [x20, 832]
	mov	x1, x0
	cbz	x0, .L3605
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x20, 832]
	ldr	w2, [x21, 60]
.L3605:
	cmp	w2, w19
	bhi	.L3614
.L3607:
	ldr	x1, .LC950
	add	x0, x21, 11120640
	strb	wzr, [x21, 4]
	add	x19, x21, 11116544
	strb	wzr, [x21, 9]
	mov	x2, 1656
	strb	wzr, [x21, 6]
	strb	wzr, [x21, 7]
	strb	wzr, [x21, 3]
	stp	wzr, wzr, [x21, 60]
	str	wzr, [x21, 104]
	str	wzr, [x21, 220]
	str	xzr, [x21, 240]
	add	x21, x21, 11161600
	ldr	x3, [x1, 96]
	mov	w1, 0
	strb	wzr, [x0, 2484]
	strb	wzr, [x0, 480]
	strb	wzr, [x0, 2485]
	strb	wzr, [x0, 481]
	add	x0, x19, 2872
	blr	x3
	mov	w1, 2
	mov	w0, 1
	strb	w1, [x19, 2872]
	strb	w0, [x19, 2877]
	mov	w0, 256
	strb	wzr, [x22, 2664]
	stp	wzr, w0, [x21, 76]
	strb	wzr, [x21, 72]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3625:
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L3599
.L3626:
	ldr	w0, [x21, 120]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L3602
.L3597:
	add	x0, x21, 912
	bl	ResetVoQueue
	ldr	w0, [x21, 120]
	bl	FSP_EmptyInstance
	b	.L3598
.L3596:
	ldr	x2, .LC948
	mov	w3, 343
	ldr	x1, .LC949
	mov	w0, 22
	add	x2, x2, 336
	bl	dprint_vfmw
	b	.L3595
	.size	MVC_ClearAll, .-MVC_ClearAll
	.align	3
.LC947:
	.xword	.LC946
	.align	3
.LC948:
	.xword	.LANCHOR0
	.align	3
.LC949:
	.xword	.LC924
	.align	3
.LC950:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InsertFrmInDPB
	.type	MVC_InsertFrmInDPB, %function
MVC_InsertFrmInDPB:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	uxtw	x21, w1
	mov	x19, x2
	bl	_mcount
	add	x0, x23, 11124736
	ldr	w0, [x0, 828]
	cbnz	w0, .L3628
	ldr	x0, .LC951
	str	wzr, [x0, 1948]
.L3628:
	ldrb	w22, [x19, 3]
	cmp	w22, 1
	beq	.L3630
	cbz	w22, .L3631
	cmp	w22, 2
	beq	.L3632
	ldr	x1, .LC955
	mov	w2, w22
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x23
	bl	MVC_ClearAll
.L3636:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3632:
	ldr	x0, [x19, 656]
	mov	w1, 3
	strb	w1, [x0, 712]
	ldrb	w0, [x19, 1]
	cbz	w0, .L3650
	add	x20, x23, x21, lsl 3
	add	x20, x20, 11124736
	ldr	x0, [x20, 440]
	cbz	x0, .L3650
	strb	w22, [x0, 808]
	ldr	x0, [x20, 440]
	ldr	x1, [x19, 656]
	str	x1, [x0, 816]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 809]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 810]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 696]
	str	w1, [x0, 832]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 811]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 716]
	str	w1, [x0, 840]
	ldr	x0, [x20, 440]
	ldr	w2, [x0, 792]
	ldr	w1, [x0, 840]
	add	w1, w2, w1
	str	w1, [x0, 44]
	str	w1, [x0, 744]
	ldr	x1, [x20, 440]
	ldrb	w0, [x1, 1]
	cbz	w0, .L3656
	ldrb	w0, [x19, 2]
.L3656:
	strb	w0, [x1, 1]
	ldr	x1, [x20, 440]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 2
	strb	w0, [x1, 2]
	ldrb	w0, [x19, 7]
	ldr	x1, [x20, 440]
	cmp	w0, 1
	beq	.L3724
	ldrb	w0, [x1, 4]
.L3658:
	strb	w0, [x1, 4]
	mov	x2, 640
	add	x1, x19, 16
	ldr	x0, [x20, 440]
	add	x0, x0, 72
	ldr	x25, [x0, 584]
	ldr	x24, [x0, 592]
	ldr	x22, [x0, 600]
	bl	memcpy
	ldr	x0, [x19, 600]
	cmn	x0, #1
	ccmn	x25, #1, 4, eq
	beq	.L3659
	ldr	x0, [x20, 440]
	str	x25, [x0, 656]
.L3659:
	ldr	x0, [x19, 608]
	ldr	x1, [x20, 440]
	cmp	x0, x24
	csel	x0, x0, x24, ls
	str	x0, [x1, 664]
	ldr	x0, [x19, 616]
	ldr	x1, [x20, 440]
	cmp	x0, x22
	csel	x0, x0, x22, ls
	str	x0, [x1, 672]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3660
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3660
.L3661:
	ldr	x1, [x20, 440]
	ldrb	w2, [x1, 811]
	ldrb	w0, [x1, 763]
	cmp	w0, w2, uxtb
	csel	w0, w0, w2, cs
	strb	w0, [x1]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 712]
	str	w1, [x0, 836]
	ldr	x1, [x20, 440]
	ldr	w0, [x1, 788]
	ldr	w2, [x1, 836]
	cmp	w0, w2
	csel	w0, w0, w2, le
	str	w0, [x1, 36]
	ldr	x0, [x20, 440]
	bl	MVC_CombineFldsToFrm
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 11]
	strb	w1, [x0, 13]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 10]
	strb	w1, [x0, 11]
	ldr	x1, [x20, 440]
	ldr	w0, [x1, 52]
	ldr	w1, [x1, 832]
	add	x0, x0, 2781184
	add	x0, x0, 248
	str	w1, [x23, x0, lsl 2]
	b	.L3649
	.p2align 3
.L3631:
	add	x20, x23, x21, lsl 3
	ldr	x1, [x19, 656]
	add	x20, x20, 11124736
	mov	w2, 3
	mov	w0, 3
	str	x1, [x20, 440]
	ldrb	w3, [x19, 2]
	strb	w3, [x1, 1]
	ldr	x1, [x20, 440]
	strb	w2, [x1, 2]
	ldr	x2, [x19, 656]
	ldr	x1, [x20, 440]
	ldrb	w2, [x2, 5]
	strb	w2, [x1, 5]
	ldr	x2, [x19, 656]
	ldr	x1, [x20, 440]
	ldrb	w2, [x2, 7]
	strb	w2, [x1, 7]
	ldrb	w2, [x19, 4]
	ldr	x1, [x20, 440]
	cbz	w2, .L3725
.L3633:
	strb	w0, [x1, 3]
	mov	x2, 640
	add	x1, x19, 16
	mov	w22, 3
	ldr	x0, [x20, 440]
	ldr	w3, [x19, 740]
	str	w3, [x0, 48]
	ldr	x0, [x20, 440]
	add	x0, x0, 72
	bl	memcpy
	ldr	x0, [x20, 440]
	mov	w6, 1
	ldr	w1, [x19, 716]
	str	w1, [x0, 44]
	str	w1, [x0, 744]
	ldr	x0, [x20, 440]
	ldr	x1, [x19, 656]
	str	x1, [x0, 720]
	str	x1, [x0, 768]
	str	x1, [x0, 816]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 676]
	str	w1, [x0, 28]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 672]
	str	w1, [x0, 20]
	ldr	x0, [x20, 440]
	strb	wzr, [x0, 712]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 713]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 714]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 715]
	strb	w1, [x0]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 9]
	str	w1, [x0, 40]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 684]
	str	w1, [x0, 32]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 688]
	str	w1, [x0, 736]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 692]
	str	w1, [x0, 784]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 696]
	str	w1, [x0, 832]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 700]
	str	w1, [x0, 36]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 704]
	str	w1, [x0, 740]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 708]
	str	w1, [x0, 788]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 712]
	str	w1, [x0, 836]
	ldrb	w1, [x19, 7]
	ldr	x0, [x20, 440]
	cmp	w1, 1
	csel	w22, wzr, w22, ne
	strb	w22, [x0, 4]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 744]
	str	w1, [x0, 56]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 748]
	str	w1, [x0, 60]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 11]
	strb	w1, [x0, 13]
	strb	w1, [x0, 12]
	ldr	x1, .LC951
	ldr	x2, [x20, 440]
	ldrb	w3, [x19, 10]
	ldr	w0, [x1, 1948]
	strb	w3, [x2, 11]
	strb	w3, [x2, 10]
	add	w2, w0, 1
	str	w2, [x1, 1948]
	ldr	x1, [x20, 440]
	str	w0, [x1, 64]
	ldr	x0, [x20, 440]
	ldrb	w2, [x0, 715]
	ldr	x1, [x0, 720]
	ldrb	w4, [x0, 713]
	ldrb	w3, [x0, 714]
	ldr	w5, [x0, 744]
	strb	w2, [x0, 763]
	strb	w2, [x0, 811]
	mov	w2, 0
	str	x1, [x0, 768]
	str	x1, [x0, 816]
	mov	w1, 2
	strb	w4, [x0, 761]
	strb	w3, [x0, 762]
	strb	w6, [x0, 760]
	strb	w4, [x0, 809]
	strb	w3, [x0, 810]
	str	w5, [x0, 792]
	str	w5, [x0, 840]
	strb	w1, [x0, 808]
	mov	x0, x23
	ldr	x1, [x19, 656]
	bl	MVC_GetAPC
	cbnz	w0, .L3726
.L3649:
	add	x21, x21, 1388544
	mov	w19, 0
	add	x21, x23, x21, lsl 3
	ldr	x0, [x21, 16824]
	ldrb	w1, [x0, 3]
	cbz	w1, .L3636
	ldrsb	w1, [x0, 6]
	mov	w2, 1
	ldr	w0, [x23, 120]
	bl	FSP_SetRef
	ldr	x25, [sp, 64]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3630:
	ldr	x0, [x19, 656]
	mov	w1, 3
	strb	w1, [x0, 712]
	ldrb	w0, [x19, 1]
	cbz	w0, .L3637
	add	x20, x23, x21, lsl 3
	add	x20, x20, 11124736
	ldr	x0, [x20, 440]
	cbz	x0, .L3637
	strb	w22, [x0, 760]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 763]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 761]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 762]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 692]
	str	w1, [x0, 784]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 763]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 716]
	str	w1, [x0, 792]
	ldr	x0, [x20, 440]
	ldr	w2, [x0, 792]
	ldr	w1, [x0, 840]
	add	w1, w2, w1
	str	w1, [x0, 44]
	str	w1, [x0, 744]
	ldr	x1, [x20, 440]
	ldrb	w0, [x1, 1]
	cbz	w0, .L3642
	ldrb	w0, [x19, 2]
.L3642:
	strb	w0, [x1, 1]
	ldr	x1, [x20, 440]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 1
	strb	w0, [x1, 2]
	ldrb	w0, [x19, 7]
	ldr	x1, [x20, 440]
	cmp	w0, 1
	beq	.L3727
	ldrb	w0, [x1, 4]
.L3644:
	strb	w0, [x1, 4]
	mov	x2, 640
	add	x1, x19, 16
	ldr	x0, [x20, 440]
	add	x0, x0, 72
	ldr	x25, [x0, 584]
	ldr	x24, [x0, 592]
	ldr	x22, [x0, 600]
	bl	memcpy
	ldr	x0, [x19, 600]
	cmn	x0, #1
	ccmn	x25, #1, 4, eq
	beq	.L3645
	ldr	x0, [x20, 440]
	str	x25, [x0, 656]
.L3645:
	ldr	x0, [x19, 608]
	ldr	x1, [x20, 440]
	cmp	x0, x24
	csel	x0, x0, x24, ls
	str	x0, [x1, 664]
	ldr	x0, [x19, 616]
	ldr	x1, [x20, 440]
	cmp	x0, x22
	csel	x0, x0, x22, ls
	str	x0, [x1, 672]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3646
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3646
.L3647:
	ldr	x1, [x20, 440]
	ldrb	w2, [x1, 811]
	ldrb	w0, [x1, 763]
	cmp	w0, w2, uxtb
	csel	w0, w0, w2, cs
	strb	w0, [x1]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 708]
	str	w1, [x0, 788]
	ldr	x1, [x20, 440]
	ldr	w0, [x1, 788]
	ldr	w2, [x1, 836]
	cmp	w0, w2
	csel	w0, w0, w2, le
	str	w0, [x1, 36]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 11]
	strb	w1, [x0, 12]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 10]
	strb	w1, [x0, 10]
	ldr	x0, [x20, 440]
	bl	MVC_CombineFldsToFrm
	ldr	x1, [x20, 440]
	ldr	w0, [x1, 52]
	ldr	w1, [x1, 784]
	add	x0, x0, 2781184
	add	x0, x0, 232
	str	w1, [x23, x0, lsl 2]
	b	.L3649
	.p2align 3
.L3637:
	add	x20, x23, x21, lsl 3
	ldr	x0, [x19, 656]
	add	x20, x20, 11124736
	mov	w1, 1
	str	x0, [x20, 440]
	strb	w1, [x0, 760]
	ldr	x0, [x20, 440]
	ldr	x2, [x19, 656]
	str	x2, [x0, 768]
	ldr	x0, [x20, 440]
	ldrb	w2, [x19, 4]
	strb	w2, [x0, 761]
	ldr	x0, [x20, 440]
	ldrb	w2, [x19, 5]
	strb	w2, [x0, 762]
	ldr	x0, [x20, 440]
	ldr	w2, [x19, 692]
	str	w2, [x0, 784]
	ldr	x0, [x20, 440]
	ldrb	w2, [x19, 12]
	strb	w2, [x0, 763]
	ldr	x0, [x20, 440]
	ldr	w2, [x19, 716]
	str	w2, [x0, 792]
	ldr	x0, [x20, 440]
	ldr	w2, [x0, 792]
	str	w2, [x0, 44]
	str	w2, [x0, 744]
	ldr	x0, [x20, 440]
	ldrb	w2, [x19, 2]
	strb	w2, [x0, 1]
	ldr	x0, [x20, 440]
	strb	w1, [x0, 2]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 440]
	ldrb	w1, [x1, 5]
	strb	w1, [x0, 5]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 440]
	ldrb	w1, [x1, 7]
	strb	w1, [x0, 7]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3639
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3639
.L3640:
	ldr	x0, [x20, 440]
	mov	x2, 640
	add	x1, x19, 16
	str	wzr, [x0, 40]
	ldr	x0, [x20, 440]
	add	x0, x0, 72
	bl	memcpy
	ldr	x0, [x20, 440]
	mov	w2, 1
	ldr	w1, [x19, 740]
	ldr	x3, .LC951
	str	w1, [x0, 48]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 672]
	str	w1, [x0, 20]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 684]
	str	w1, [x0, 32]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 700]
	str	w1, [x0, 36]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 12]
	strb	w1, [x0]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 708]
	str	w1, [x0, 788]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 744]
	str	w1, [x0, 56]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 748]
	str	w1, [x0, 60]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 11]
	strb	w1, [x0, 12]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 10]
	strb	w1, [x0, 10]
	mov	x0, x23
	ldr	x4, [x20, 440]
	ldr	w1, [x3, 1948]
	str	w1, [x4, 64]
	add	w5, w1, w2
	str	w5, [x3, 1948]
	ldr	x1, [x20, 440]
	ldrb	w3, [x19, 7]
	cmp	w3, w2
	cset	w3, eq
	strb	w3, [x1, 4]
	ldr	x1, [x19, 656]
	bl	MVC_GetAPC
	cbz	w0, .L3649
	ldr	x1, .LC953
	mov	w3, w0
	mov	w2, 2206
	b	.L3722
	.p2align 3
.L3650:
	add	x20, x23, x21, lsl 3
	ldr	x0, [x19, 656]
	add	x20, x20, 11124736
	mov	w1, 2
	str	x0, [x20, 440]
	strb	w1, [x0, 808]
	ldr	x0, [x20, 440]
	ldr	x2, [x19, 656]
	str	x2, [x0, 816]
	ldr	x0, [x20, 440]
	ldrb	w2, [x19, 4]
	strb	w2, [x0, 809]
	ldr	x0, [x20, 440]
	ldrb	w2, [x19, 5]
	strb	w2, [x0, 810]
	ldr	x0, [x20, 440]
	ldr	w2, [x19, 696]
	str	w2, [x0, 832]
	ldr	x0, [x20, 440]
	ldrb	w2, [x19, 12]
	strb	w2, [x0, 811]
	ldr	x0, [x20, 440]
	ldr	w2, [x19, 716]
	str	w2, [x0, 840]
	ldr	x0, [x20, 440]
	ldr	w2, [x0, 792]
	str	w2, [x0, 44]
	str	w2, [x0, 744]
	ldr	x0, [x20, 440]
	ldrb	w2, [x19, 2]
	strb	w2, [x0, 1]
	ldr	x0, [x20, 440]
	strb	w1, [x0, 2]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 440]
	ldrb	w1, [x1, 5]
	strb	w1, [x0, 5]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 440]
	ldrb	w1, [x1, 7]
	strb	w1, [x0, 7]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3652
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3652
.L3653:
	ldr	x0, [x20, 440]
	mov	x2, 640
	add	x1, x19, 16
	str	wzr, [x0, 40]
	ldr	x0, [x20, 440]
	add	x0, x0, 72
	bl	memcpy
	ldr	x0, [x20, 440]
	mov	w2, 2
	ldr	w1, [x19, 740]
	str	w1, [x0, 48]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 672]
	str	w1, [x0, 20]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 684]
	str	w1, [x0, 32]
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 700]
	str	w1, [x0, 36]
	ldr	x0, [x20, 440]
	ldrb	w1, [x19, 12]
	strb	w1, [x0, 811]
	strb	w1, [x0]
	mov	x0, x23
	ldr	x1, [x20, 440]
	ldr	w3, [x19, 712]
	str	w3, [x1, 836]
	ldr	x1, [x20, 440]
	ldr	w3, [x19, 744]
	str	w3, [x1, 56]
	ldr	x1, [x20, 440]
	ldr	w3, [x19, 748]
	str	w3, [x1, 60]
	ldr	x1, [x20, 440]
	ldrb	w3, [x19, 11]
	strb	w3, [x1, 13]
	ldr	x1, [x20, 440]
	ldrb	w3, [x19, 10]
	strb	w3, [x1, 11]
	ldr	x4, [x20, 440]
	ldr	x3, .LC951
	ldr	w1, [x3, 1948]
	str	w1, [x4, 64]
	add	w1, w1, 1
	str	w1, [x3, 1948]
	ldrb	w3, [x19, 7]
	ldr	x1, [x20, 440]
	cmp	w3, 1
	csel	w22, w22, wzr, eq
	strb	w22, [x1, 4]
	ldr	x1, [x19, 656]
	bl	MVC_GetAPC
	cbz	w0, .L3649
	ldr	x1, .LC953
	mov	w3, w0
	mov	w2, 2331
.L3722:
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x23
	bl	MVC_ClearDPB
	b	.L3636
	.p2align 3
.L3725:
	ldrb	w0, [x19, 5]
	mov	w2, 3
	cmp	w0, wzr
	csel	w0, w0, w2, eq
	b	.L3633
	.p2align 3
.L3639:
	ldr	x0, [x20, 440]
	mov	w1, 1
	strb	w1, [x0, 3]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3640
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 676]
	str	w1, [x0, 28]
	b	.L3640
	.p2align 3
.L3652:
	ldr	x0, [x20, 440]
	mov	w1, 2
	strb	w1, [x0, 3]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3653
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 676]
	str	w1, [x0, 28]
	b	.L3653
	.p2align 3
.L3660:
	ldr	x1, [x20, 440]
	ldrb	w0, [x1, 3]
	orr	w0, w0, 2
	strb	w0, [x1, 3]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3661
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 676]
	str	w1, [x0, 28]
	b	.L3661
	.p2align 3
.L3646:
	ldr	x1, [x20, 440]
	ldrb	w0, [x1, 3]
	orr	w0, w0, 1
	strb	w0, [x1, 3]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3647
	ldr	x0, [x20, 440]
	ldr	w1, [x19, 676]
	str	w1, [x0, 28]
	b	.L3647
	.p2align 3
.L3724:
	ldrb	w0, [x1, 4]
	orr	w0, w0, 2
	uxtb	w0, w0
	b	.L3658
	.p2align 3
.L3727:
	ldrb	w0, [x1, 4]
	orr	w0, w0, 1
	uxtb	w0, w0
	b	.L3644
.L3726:
	ldr	x1, .LC953
	mov	w3, w0
	mov	w2, 2143
	b	.L3722
	.size	MVC_InsertFrmInDPB, .-MVC_InsertFrmInDPB
	.align	3
.LC951:
	.xword	.LANCHOR3
	.align	3
.LC953:
	.xword	.LC952
	.align	3
.LC955:
	.xword	.LC954
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_AllocFrameStore
	.type	MVC_AllocFrameStore, %function
MVC_AllocFrameStore:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x24, x0
	mov	x0, x30
	add	x20, x24, 11116544
	mov	w21, w1
	bl	_mcount
	mov	w25, 0
	ldrb	w0, [x20, 2873]
	cbz	w0, .L3729
	ldrb	w0, [x20, 2874]
	mov	w25, 2
	cmp	w0, wzr
	csinc	w25, w25, wzr, ne
.L3729:
	cmp	w21, 1
	ldrb	w0, [x24, 8]
	beq	.L3730
	cmp	w0, 2
	add	x23, x24, 11157504
	beq	.L3820
	sub	w0, w25, #1
	strb	wzr, [x23, 2665]
	cmp	w0, 1
	bls	.L3824
.L3732:
	strb	wzr, [x23, 2664]
	ldr	w4, [x24, 48]
	cbz	w4, .L3756
	add	x3, x24, 11124736
	mov	x22, 0
	add	x19, x3, 1192
	.p2align 2
.L3755:
	ldrb	w0, [x19, 2]
	cbnz	w0, .L3750
	cbz	x19, .L3751
	ldr	w0, [x3, 824]
	cbz	w0, .L3751
	ldr	x1, [x3, 440]
	cmp	x1, x19
	ccmp	x1, xzr, 4, eq
	bne	.L3750
	sub	w2, w0, #1
	add	x0, x3, 448
	add	x2, x2, 1388544
	add	x2, x2, 2104
	add	x2, x24, x2, lsl 3
	b	.L3753
	.p2align 3
.L3754:
	ldr	x1, [x0], 8
	cmp	x1, x19
	ccmp	x1, xzr, 4, eq
	bne	.L3750
.L3753:
	cmp	x2, x0
	bne	.L3754
.L3751:
	lsl	x1, x22, 3
	str	x19, [x23, 3320]
	sub	x1, x1, x22
	mov	w26, 1
	lsl	x1, x1, 2
	strb	w26, [x23, 2664]
	sub	x1, x1, x22
	mov	w3, 101
	lsl	x1, x1, 2
	mov	x2, 640
	sub	x22, x1, x22
	add	x0, x23, 2680
	add	x22, x24, x22, lsl 3
	add	x22, x22, 11124736
	add	x1, x22, 1264
	str	wzr, [x22, 1236]
	str	w3, [x23, 3380]
	bl	memcpy
	str	wzr, [x23, 2832]
	strb	wzr, [x22, 1196]
	strb	wzr, [x19, 7]
	ldr	x0, [x23, 3320]
	strb	wzr, [x0, 3]
	ldr	x0, [x23, 3320]
	strb	w26, [x0, 5]
	ldr	x0, [x23, 3320]
	str	wzr, [x0, 16]
	ldrb	w19, [x23, 2664]
	cmp	w19, 1
	bne	.L3756
	cmp	w21, wzr
	ldr	w0, [x24, 120]
	cset	w1, eq
	bl	FSP_NewLogicFs
	mov	w22, w0
	mov	w1, w0
	ldr	w0, [x24, 120]
	bl	FSP_GetLogicFs
	mov	x26, x0
	cmp	w22, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L3757
	add	x1, x0, 48
	ldr	x0, [x24, 224]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L3825
.L3758:
	ldr	x19, .LC960
	mov	x2, 640
	ldr	x0, [x23, 3320]
	ldr	x3, [x19, 104]
	add	x0, x0, 72
	blr	x3
	ldr	x1, [x23, 3320]
	mov	x2, 640
	ldr	x3, [x19, 104]
	add	x0, x23, 2680
	add	x1, x1, 72
	blr	x3
	ldr	x0, [x23, 3320]
	strb	w22, [x0, 6]
	ldrsb	w0, [x26, 4]
	str	w0, [x23, 3404]
.L3749:
	uxtb	w2, w25
	cmp	w21, 1
	strb	w2, [x23, 2667]
	beq	.L3768
.L3832:
	ldrb	w0, [x20, 2873]
	mov	w3, 3
	ldr	x1, [x23, 3320]
	cmp	w0, wzr
	csel	w0, w0, w3, eq
	strb	w0, [x1, 712]
	add	x1, x24, 11161600
	ldrb	w0, [x23, 2665]
	cmp	w0, 1
	beq	.L3826
	strb	w2, [x1, 72]
	add	x0, x24, 11120640
	ldr	w2, [x20, 2900]
	str	w2, [x1, 80]
	ldrb	w2, [x20, 2880]
	str	w2, [x1, 76]
	ldr	w2, [x24, 128]
	str	w2, [x1, 84]
	ldr	w0, [x0, 416]
	str	w0, [x1, 96]
	str	w22, [x1, 88]
	cbnz	w25, .L3827
	strb	wzr, [x1, 73]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3750:
	add	w22, w22, 1
	add	x19, x19, 856
	cmp	w22, w4
	bne	.L3755
.L3756:
	ldr	x1, .LC959
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x24
	bl	MVC_ClearAll
	mov	w0, -1
.L3815:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3827:
	mov	w2, 1
	strb	w2, [x1, 73]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3730:
	cmp	w0, 2
	beq	.L3828
	add	x23, x24, 11157504
	mov	w25, 0
.L3820:
	strb	wzr, [x23, 2665]
	b	.L3732
.L3824:
	add	x0, x24, 11161600
	ldrb	w1, [x0, 72]
	cbz	w1, .L3733
	add	x2, x24, 11120640
	ldr	w3, [x0, 96]
	ldr	w2, [x2, 416]
	cmp	w3, w2
	beq	.L3734
.L3733:
	add	x0, x24, 11124736
	ldr	w1, [x0, 824]
	subs	w1, w1, #1
	bmi	.L3732
	add	x3, x24, 11120640
	b	.L3743
	.p2align 3
.L3736:
	cmp	w25, 2
	beq	.L3829
.L3735:
	subs	w1, w1, #1
	bmi	.L3732
.L3743:
	sxtw	x0, w1
	add	x0, x0, 1388544
	add	x0, x24, x0, lsl 3
	ldr	x19, [x0, 16824]
	cbz	x19, .L3735
	cmp	w25, 1
	bne	.L3736
	ldrb	w0, [x19, 2]
	cmp	w0, 2
	bne	.L3735
.L3737:
	ldr	w0, [x19, 20]
	ldr	w2, [x20, 2900]
	cmp	w2, w0
	bne	.L3735
	ldr	w2, [x3, 416]
	ldr	w0, [x19, 56]
	cmp	w2, w0
	bne	.L3735
	ldrb	w0, [x20, 2880]
	cbz	w0, .L3830
	ldrb	w0, [x19, 3]
	cbz	w0, .L3735
.L3739:
	mov	w0, 1
	add	x1, x19, 72
	strb	w0, [x23, 2665]
	mov	x2, 640
	add	x0, x23, 2680
	str	x19, [x23, 3320]
	bl	memcpy
	ldrsb	w1, [x19, 6]
	ldr	w0, [x24, 120]
	bl	FSP_GetLogicFs
	cbz	x0, .L3831
	ldrsb	w1, [x0, 4]
	ldrb	w0, [x23, 2665]
	str	w1, [x23, 3404]
	cbz	w0, .L3732
	ldr	x0, [x23, 3320]
	cbz	x0, .L3732
.L3819:
	uxtb	w2, w25
	cmp	w21, 1
	strb	w2, [x23, 2667]
	mov	w22, 0
	bne	.L3832
.L3768:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 96
	ret
.L3825:
	ldp	w3, w2, [x24, 12]
	ldr	w0, [x1, 112]
	lsl	w2, w2, 4
	str	w2, [x1, 72]
	str	x1, [x29, 88]
	mul	w19, w2, w0
	ldr	w0, [x1, 36]
	lsl	w2, w3, 4
	str	w2, [x1, 68]
	add	w0, w19, w0
	str	w0, [x1, 40]
	bl	MEM_Phy2Vir
	ldr	x1, [x29, 88]
	str	x0, [x1, 512]
	ldr	w0, [x1, 20]
	ldr	w2, [x1, 116]
	add	w0, w19, w0
	str	w0, [x1, 24]
	add	w0, w2, w0
	str	w0, [x1, 32]
	b	.L3758
	.p2align 3
.L3829:
	ldrb	w0, [x19, 2]
	cmp	w0, 1
	bne	.L3735
	b	.L3737
.L3826:
	strb	wzr, [x1, 72]
	add	x2, x24, 11120640
	mov	w0, 0
	ldr	w3, [x20, 2900]
	str	w3, [x1, 80]
	ldrb	w3, [x20, 2880]
	str	w3, [x1, 76]
	ldr	w3, [x24, 128]
	stp	w3, w22, [x1, 84]
	strb	wzr, [x1, 73]
	ldr	w2, [x2, 416]
	str	w2, [x1, 96]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3828:
	add	x23, x24, 11157504
	mov	w25, 0
	strb	wzr, [x23, 2665]
	b	.L3732
.L3830:
	ldrb	w0, [x19, 3]
	cbnz	w0, .L3735
	b	.L3739
	.p2align 3
.L3734:
	cmp	w1, 1
	ccmp	w25, 2, 0, eq
	beq	.L3744
	cmp	w1, 2
	ccmp	w25, 1, 0, eq
	bne	.L3732
.L3744:
	ldr	w2, [x0, 80]
	ldr	w1, [x20, 2900]
	cmp	w2, w1
	bne	.L3732
	ldrb	w1, [x20, 2880]
	ldr	w0, [x0, 76]
	cbnz	w1, .L3745
	cbnz	w0, .L3732
.L3746:
	ldp	w1, w0, [x24, 124]
	sub	w0, w0, w1
	cmp	w0, 2
	bhi	.L3732
	ldr	x0, [x23, 3320]
	mov	w1, 1
	strb	w1, [x23, 2665]
	cbz	x0, .L3820
	cmp	w25, 2
	beq	.L3833
	cmp	w25, 1
	mov	w22, 0
	bne	.L3749
	ldrb	w0, [x0, 2]
	cmp	w0, 2
	beq	.L3749
	strb	wzr, [x23, 2665]
	b	.L3732
	.p2align 3
.L3757:
	ldr	x2, [x23, 3320]
	mov	w0, 0
	strb	wzr, [x23, 2664]
	ldr	x1, .LC962
	strb	wzr, [x2, 5]
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x24
	bl	MVC_ClearAll
	mov	w0, -1
	b	.L3815
.L3831:
	ldr	x1, .LC957
	mov	w2, 6386
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3815
.L3833:
	ldrb	w0, [x0, 2]
	cmp	w0, 1
	beq	.L3819
	strb	wzr, [x23, 2665]
	b	.L3732
.L3745:
	cbz	w0, .L3732
	b	.L3746
	.size	MVC_AllocFrameStore, .-MVC_AllocFrameStore
	.align	3
.LC957:
	.xword	.LC956
	.align	3
.LC959:
	.xword	.LC958
	.align	3
.LC960:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC962:
	.xword	.LC961
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_Init
	.type	MVC_DEC_Init, %function
MVC_DEC_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L3844
	ldr	x22, .LC965
	mov	x2, 22888
	movk	x2, 0xaa, lsl 16
	mov	w1, 0
	mov	x0, x20
	ldr	w21, [x20, 1512]
	ldr	x3, [x22, 96]
	blr	x3
	str	w21, [x20, 1512]
	add	x0, x20, 912
	bl	ResetVoQueue
	strb	wzr, [x20]
	stp	x19, xzr, [x20, 224]
	ldr	w0, [x19, 28]
	cmp	w0, 25
	beq	.L3845
	mov	w2, 32
	mov	w1, 256
	mov	w0, 136
	str	w1, [x20, 40]
	stp	w0, w2, [x20, 32]
.L3838:
	ldr	w0, [x19, 632]
	mov	w21, 2240
	bl	MEM_Phy2Vir
	ldr	x1, [x20, 224]
	mov	w2, 3992
	ldp	w4, w5, [x20, 36]
	ldrsw	x3, [x1, 628]
	smull	x2, w4, w2
	add	x3, x0, x3
	add	x1, x3, x2
	cmp	x1, xzr
	smaddl	x0, w5, w21, x1
	ccmp	x3, xzr, 4, ne
	str	x0, [x20, 864]
	ccmp	x0, xzr, 4, ne
	stp	x3, x1, [x20, 272]
	beq	.L3846
	ldr	w1, [x19, 664]
	cbz	w1, .L3847
.L3840:
	add	x2, x20, 11112448
	ldr	x6, [x22, 96]
	mov	w1, 0
	add	x23, x20, 12288
	add	x19, x23, 2396
	add	x21, x20, 10768384
	str	w4, [x2, 344]
	add	x21, x21, 4060
	str	w5, [x2, 3616]
	ldrsw	x3, [x20, 32]
	lsl	x2, x3, 7
	sub	x2, x2, x3
	lsl	x2, x2, 5
	blr	x6
	strb	wzr, [x20, 4]
	ldr	w0, [x20, 108]
	mov	w1, 40
	strb	wzr, [x20, 6]
	mov	x2, 9856
	ubfx	x0, x0, 16, 2
	strb	w0, [x20, 8]
	mov	w0, 18
	strb	wzr, [x20, 7]
	stp	w1, w0, [x20, 48]
	add	x0, x20, 512
	str	wzr, [x20, 220]
	stp	wzr, wzr, [x20, 56]
	stp	wzr, wzr, [x20, 68]
	stp	wzr, wzr, [x20, 76]
	stp	wzr, wzr, [x20, 84]
	stp	wzr, wzr, [x20, 92]
	stp	xzr, xzr, [x0, 320]
	stp	xzr, xzr, [x0, 336]
	movk	x2, 0xa4, lsl 16
	mov	w1, 0
	ldr	x3, [x22, 96]
	mov	x0, x19
	blr	x3
	mov	x2, 8500
	ldr	x3, [x22, 96]
	mov	w1, 0
	movk	x2, 0x5, lsl 16
	mov	x0, x21
	blr	x3
	mov	x0, x19
	.p2align 2
.L3841:
	add	x1, x0, 274432
	add	x2, x0, 335872
	strb	wzr, [x0]
	add	x0, x2, 308
	cmp	x21, x0
	strb	wzr, [x1, 241]
	bne	.L3841
	add	x0, x20, 11108352
	strb	wzr, [x23, 2384]
	add	x0, x0, 3696
	mov	w1, 32
	str	x0, [x20, 248]
	mov	x0, x20
	strb	wzr, [x20, 2]
	stp	wzr, w1, [x20, 20]
	str	w1, [x20, 28]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x20, 120]
	beq	.L3848
	mov	w1, 0
	mov	x0, x20
	bl	MVC_ClearAll
	mov	w0, 1
.L3836:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L3847:
	ldr	x4, [x22, 96]
	mov	x0, x3
	blr	x4
	ldr	w2, [x20, 40]
	mov	w1, 0
	ldr	x0, [x20, 280]
	ldr	x3, [x22, 96]
	smull	x2, w2, w21
	blr	x3
	ldp	w4, w5, [x20, 36]
	ldr	x0, [x20, 864]
	b	.L3840
.L3845:
	ldr	w0, [x19, 748]
	str	w0, [x20, 36]
	ldr	w0, [x19, 752]
	str	w0, [x20, 40]
	ldr	w0, [x19, 740]
	str	w0, [x20, 32]
	b	.L3838
.L3844:
	ldr	x1, .LC964
	mov	w2, 13380
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L3836
.L3846:
	ldr	x2, .LC966
	mov	w3, 13416
	ldr	x1, .LC968
	mov	w0, 22
	add	x2, x2, 352
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3836
.L3848:
	ldr	x1, .LC970
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3836
	.size	MVC_DEC_Init, .-MVC_DEC_Init
	.align	3
.LC964:
	.xword	.LC963
	.align	3
.LC965:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC966:
	.xword	.LANCHOR0
	.align	3
.LC968:
	.xword	.LC967
	.align	3
.LC970:
	.xword	.LC969
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_StorePicInDpb
	.type	MVC_StorePicInDpb, %function
MVC_StorePicInDpb:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11157504
	bl	_mcount
	add	x0, x19, 11116544
	strb	wzr, [x0, 1736]
	ldrb	w1, [x21, 2667]
	cmp	w1, 2
	cset	w1, eq
	strb	w1, [x0, 1737]
	ldrb	w0, [x21, 2664]
	cbz	w0, .L4024
	ldr	w0, [x19, 128]
	str	w0, [x19, 124]
	ldrb	w0, [x21, 2677]
	cbz	w0, .L3852
	ldr	x0, [x21, 3328]
	ldrb	w0, [x0, 1]
	cbz	w0, .L3853
	cbz	x19, .L3855
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.17
	cbnz	w0, .L3855
.L3852:
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	beq	.L4025
	ldr	x20, [x19, 224]
	ldr	w0, [x20, 24]
	cbz	w0, .L4026
	ldrb	w1, [x21, 2666]
	cbnz	w1, .L3862
.L3932:
	ldrb	w2, [x21, 2667]
	ldr	x22, [x21, 3320]
	sub	w1, w2, #1
	uxtb	w1, w1
	cbnz	w2, .L4027
.L3863:
	cmp	w1, 1
	bls	.L4028
.L4008:
	cbnz	w2, .L4029
.L3868:
	cbz	w0, .L3938
	add	x24, x21, 2664
	mov	x20, x22
.L3871:
	cbz	w2, .L3873
	ldrb	w0, [x24, 1]
	cmp	w0, 1
	beq	.L4030
.L3873:
	ldr	w0, [x24, 716]
	str	w0, [x20, 44]
.L3874:
	mov	x1, x20
	mov	x0, x19
	bl	MVC_GetImagePara
	ldrsb	w1, [x20, 6]
	ldr	w0, [x19, 120]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L4031
	ldr	x0, [x24, 600]
	str	x0, [x23, 584]
	ldr	x0, [x24, 608]
	str	x0, [x23, 592]
	ldr	x0, [x24, 616]
	str	x0, [x23, 600]
	ldr	w0, [x20, 44]
	str	w0, [x23, 152]
	cbz	w0, .L3881
	ldrb	w1, [x23, 64]
	and	w1, w1, 3
	cbz	w1, .L4032
.L3879:
	ldr	x1, [x19, 224]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	bcc	.L4033
.L3881:
	ldrsb	w1, [x20, 6]
	mov	w2, 1
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 120]
	mov	x4, x23
	add	x3, x19, 912
	mov	x2, x19
	mov	w1, 15
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L3878
	ldrsb	w1, [x20, 6]
	mov	w2, 0
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
.L3878:
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L4034
	str	wzr, [x23, 16]
.L3884:
	ldr	w0, [x19, 136]
	add	w0, w0, 2
	str	w0, [x19, 136]
.L3872:
	ldr	w0, [x19, 220]
	cmp	w0, 2
	beq	.L3885
.L3870:
	mov	w0, 1
	str	w0, [x20, 16]
	strb	w0, [x22, 8]
.L3885:
	ldr	x0, [x19, 224]
	mov	w1, 2
	str	w1, [x19, 220]
	ldr	w0, [x0, 24]
.L3862:
	cmp	w0, 2
	bne	.L3861
	ldr	w0, [x21, 3344]
	cbz	w0, .L3886
	add	x20, x19, 11124736
	mov	x0, x19
	bl	MVC_SimpleSlideDPB
	ldr	w1, [x20, 824]
	cbz	w1, .L3887
	ldr	x0, [x20, 440]
	cbz	x0, .L4035
	add	x2, x20, 448
	mov	w0, 0
	b	.L3889
	.p2align 3
.L3890:
	ldr	x3, [x2], 8
	cbz	x3, .L4036
.L3889:
	add	w0, w0, 1
	cmp	w0, w1
	bne	.L3890
.L3887:
	add	x2, x21, 2664
	mov	x0, x19
	bl	MVC_InsertFrmInDPB
	cbnz	w0, .L4037
	ldr	w1, [x20, 828]
	mov	x0, x19
	add	w1, w1, 1
	str	w1, [x20, 828]
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	ldr	x1, .LC974
	mov	w3, 3668
	mov	w2, 0
	mov	w0, 14
	bl	dprint_vfmw
	.p2align 2
.L3892:
	mov	w20, 0
.L3931:
	strb	wzr, [x21, 2664]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4026:
	ldr	w1, [x19, 220]
	cmp	w1, 2
	beq	.L3861
	ldrb	w1, [x21, 2666]
	cbz	w1, .L3932
.L3861:
	ldr	w0, [x21, 3344]
	cbz	w0, .L3893
	ldr	w3, [x19, 112]
	ldr	w2, [x21, 3380]
	cmp	w3, w2
	bcs	.L3894
	ldrb	w0, [x21, 2666]
	cbz	w0, .L4038
.L3894:
	mov	x0, x19
	bl	MVC_Marking
	cbnz	w0, .L4039
	mov	x0, x19
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	ldr	w1, [x21, 3408]
	mov	x0, x19
	bl	MVC_RemoveUnUsedFrameStore
.L3886:
	ldrb	w0, [x21, 2665]
	cmp	w0, 1
	beq	.L3897
	add	x20, x19, 11124736
	ldr	w0, [x20, 824]
.L3898:
	ldr	w1, [x21, 3344]
	cbz	w1, .L3907
	ldr	w4, [x20, 832]
	ldr	w5, [x20, 836]
	add	w1, w4, w5
	cmp	w1, w0
	bcs	.L3934
.L3907:
	mov	w23, -1
	mov	w22, w23
	b	.L3916
	.p2align 3
.L3910:
	ldr	w22, [x29, 72]
.L3911:
	ldr	w3, [x21, 3344]
	mov	w1, w22
	mov	x0, x19
	mov	w23, w2
	cbnz	w3, .L3912
	ldr	w3, [x21, 3348]
	ldr	w2, [x29, 68]
	cmp	w3, w2
	blt	.L4040
.L3912:
	bl	MVC_OutputFrmFromDPB
	cmn	w0, #1
	mov	w24, w0
	beq	.L3915
	ldr	w0, [x20, 824]
.L3916:
	ldr	w4, [x20, 828]
	add	x3, x29, 72
	add	x2, x29, 68
	mov	w1, -1
	cmp	w4, w0
	mov	x0, x19
	bcc	.L3909
	bl	MVC_GetMinPOC
	tbnz	w0, #31, .L4041
	ldr	w2, [x20, 828]
	cmp	w23, w2
	bne	.L3910
	ldr	w0, [x29, 72]
	cmp	w22, w0
	beq	.L4042
	mov	w22, w0
	b	.L3911
	.p2align 3
.L4041:
	ldr	x1, .LC993
	mov	w2, 3769
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
.L3909:
	ldr	w0, [x21, 3344]
	cbz	w0, .L3921
	ldrb	w0, [x21, 2668]
	cbnz	w0, .L3921
	ldr	w0, [x20, 832]
	cbz	w0, .L3921
	mov	w1, 0
	b	.L3926
	.p2align 3
.L3923:
	ldr	w0, [x20, 832]
	cmp	w0, w1
	bls	.L3921
.L3926:
	add	x0, x19, x1, uxtw 3
	ldr	w3, [x21, 3336]
	add	x0, x0, 11124736
	add	w1, w1, 1
	ldr	x2, [x0, 568]
	ldr	w4, [x2, 20]
	cmp	w4, w3
	bne	.L3923
	ldr	w4, [x2, 56]
	ldr	w3, [x21, 3408]
	cmp	w4, w3
	bne	.L3923
	strb	wzr, [x2, 3]
	ldr	x2, [x0, 568]
	ldrb	w3, [x2, 5]
	cmp	w3, 1
	beq	.L4043
.L3925:
	ldr	w0, [x2, 48]
	ldr	w3, [x19, 52]
	cmp	w0, w3
	add	x0, x19, x0, uxtw 2
	beq	.L3923
	str	wzr, [x0, 148]
	str	w3, [x2, 48]
	b	.L3923
	.p2align 3
.L3921:
	ldr	w1, [x20, 824]
	cbz	w1, .L3920
	ldr	x0, [x20, 440]
	cbz	x0, .L4044
	add	x2, x20, 448
	mov	w0, 0
	b	.L3928
	.p2align 3
.L3929:
	ldr	x3, [x2], 8
	cbz	x3, .L4045
.L3928:
	add	w0, w0, 1
	cmp	w0, w1
	bne	.L3929
.L3920:
	add	x2, x21, 2664
	mov	x0, x19
	bl	MVC_InsertFrmInDPB
	cbnz	w0, .L4046
	ldr	w1, [x20, 828]
	mov	x0, x19
	add	w1, w1, 1
	str	w1, [x20, 828]
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	b	.L3892
	.p2align 3
.L3893:
	ldrb	w0, [x21, 2665]
	cmp	w0, 1
	beq	.L3897
	add	x20, x19, 11124736
	ldr	w0, [x20, 824]
	b	.L3907
	.p2align 3
.L3897:
	ldr	x0, [x19, 816]
	ldr	x4, [x21, 3320]
	cmp	x0, xzr
	ccmp	x4, x0, 0, ne
	bne	.L4047
	mov	x0, x19
	bl	MVC_DirectOutput
	cmn	w0, #1
	mov	w20, w0
	beq	.L4048
.L3903:
	ldr	x1, .LC974
	mov	w3, 3720
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3858
	.p2align 3
.L4027:
	ldrb	w3, [x22, 2]
	cmp	w3, wzr
	ccmp	w1, 1, 0, eq
	bhi	.L3862
	b	.L3863
	.p2align 3
.L4029:
	ldrb	w1, [x22, 2]
	cbz	w1, .L3862
	b	.L3868
.L4028:
	ldr	w1, [x19, 220]
	cbnz	w1, .L3865
	mov	w0, 1
	mov	x2, 752
	str	w0, [x19, 220]
	add	x1, x21, 2664
	add	x0, x21, 3416
	bl	memcpy
	ldr	w0, [x20, 24]
	b	.L3862
.L4047:
	add	x20, x19, 11124736
	ldr	w0, [x20, 824]
	cbz	w0, .L3900
	ldr	x1, [x20, 440]
	add	x3, x20, 448
	cmp	x4, x1
	ccmp	x1, xzr, 4, eq
	mov	w1, 0
	bne	.L4049
	.p2align 2
.L3904:
	add	w1, w1, 1
	cmp	w1, w0
	beq	.L3898
	ldr	x2, [x3], 8
	cmp	x4, x2
	ccmp	x2, xzr, 4, eq
	beq	.L3904
.L3901:
	add	x2, x21, 2664
	mov	x0, x19
	bl	MVC_InsertFrmInDPB
	cmn	w0, #1
	mov	w20, w0
	beq	.L4050
	mov	x0, x19
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	ldr	x1, .LC974
	mov	w3, 3746
	mov	w2, 0
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3892
.L3865:
	cmp	w1, 1
	bne	.L4008
	ldr	x20, [x21, 4072]
	cbz	w0, .L3870
	add	x24, x21, 3416
	ldrb	w2, [x24, 3]
	b	.L3871
	.p2align 3
.L3915:
	ldr	x22, .LC985
	mov	w3, w0
	mov	w2, 3809
	mov	w0, 1
	mov	x1, x22
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3810
	mov	w2, w24
	mov	w0, 14
	bl	dprint_vfmw
.L3936:
	ldr	x1, [x21, 3320]
	mov	w2, 1
	ldr	w0, [x19, 120]
	mov	w20, -1
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
	mov	w3, w20
	mov	x1, x22
	mov	w2, 3867
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, [x21, 3320]
	strb	wzr, [x0, 5]
	ldr	x0, [x21, 3320]
	strb	wzr, [x0, 2]
	mov	w0, w20
	strb	wzr, [x21, 2664]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4045:
	mov	w1, w0
	b	.L3920
	.p2align 3
.L3853:
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L3852
	ldr	x1, .LC978
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3501
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
	.p2align 3
.L4025:
	ldr	x1, .LC980
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DirectOutput
	mov	w20, w0
	ldr	w1, [x19, 52]
	ldr	w0, [x21, 3404]
	cmp	w0, w1
	beq	.L3857
	add	x0, x19, x0, uxtw 2
	str	wzr, [x0, 148]
	str	w1, [x21, 3404]
.L3857:
	ldr	x1, .LC974
	mov	w3, 3519
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
.L3858:
	cmn	w20, #1
	bne	.L3931
	ldr	x22, .LC985
	b	.L3936
	.p2align 3
.L4040:
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	beq	.L4051
.L3913:
	mov	x0, x19
	bl	MVC_DirectOutput
	cmn	w0, #1
	mov	w20, w0
	beq	.L4052
.L3914:
	ldr	x1, .LC974
	mov	w3, 3801
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3858
	.p2align 3
.L3855:
	ldr	x1, .LC976
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3491
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
	.p2align 3
.L3938:
	mov	x20, x22
	b	.L3872
.L4043:
	strb	w3, [x2, 7]
	ldr	x2, [x0, 568]
	strb	wzr, [x2, 5]
	ldr	x2, [x0, 568]
	b	.L3925
.L4030:
	mov	w0, 3
	strb	w0, [x20, 2]
	ldr	w1, [x20, 44]
	ldr	w0, [x24, 716]
	add	w0, w1, w0
	str	w0, [x20, 44]
	b	.L3874
.L4032:
	ldr	x1, .LC982
	mov	w2, 3600
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC983
	ldr	x4, [x0]
	cbz	x4, .L3880
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 111
	blr	x4
.L3880:
	ldr	w0, [x23, 152]
	cbnz	w0, .L3879
	b	.L3881
	.p2align 3
.L4042:
	ldr	x2, .LC994
	mov	w3, w22
	ldr	x1, .LC996
	mov	w0, 1
	add	x2, x2, 368
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3778
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
.L4051:
	ldrb	w0, [x21, 2667]
	cbz	w0, .L3913
	ldr	x0, [x21, 3320]
	str	x0, [x19, 824]
	b	.L3913
.L4036:
	mov	w1, w0
	b	.L3887
.L4034:
	mov	x1, x23
	mov	x0, x19
	bl	MVC_SetFrmRepeatCount.part.2
	b	.L3884
.L4024:
	ldr	x1, .LC972
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3477
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
.L4052:
	ldr	x1, .LC985
	mov	w3, w0
	mov	w2, 3798
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3914
.L4039:
	ldr	x1, .LC989
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3693
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
.L4044:
	mov	w1, 0
	b	.L3920
.L4046:
	ldr	x22, .LC985
	mov	w3, w0
	mov	w2, 3853
	mov	w0, 1
	mov	x1, x22
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3854
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3936
.L3900:
	ldr	w1, [x21, 3344]
	cbz	w1, .L3907
	ldr	w4, [x20, 832]
	ldr	w5, [x20, 836]
.L3934:
	ldr	x1, .LC991
	mov	w3, w0
	mov	w2, 3759
	mov	w0, 1
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	x1, .LC974
	mov	w3, 3761
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
.L4038:
	ldr	x1, .LC987
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC983
	ldr	x4, [x0]
	cbz	x4, .L3895
	ldr	w1, [x19, 112]
	mov	w3, 8
	ldr	w2, [x21, 3380]
	ldr	w0, [x19, 120]
	stp	w2, w1, [x29, 72]
	add	x2, x29, 72
	mov	w1, 104
	blr	x4
.L3895:
	mov	x0, x19
	bl	MVC_ClearCurrPic
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	x1, .LC974
	mov	w3, 3684
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
.L4035:
	mov	w1, 0
	b	.L3887
.L4048:
	ldr	x1, .LC985
	mov	w3, w0
	mov	w2, 3716
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3903
.L4049:
	mov	w1, 0
	b	.L3901
.L4037:
	ldr	x22, .LC985
	mov	w3, w0
	mov	w2, 3659
	mov	w0, 0
	mov	x1, x22
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3660
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3936
.L4050:
	ldr	x22, .LC985
	mov	w3, w0
	mov	w2, 3739
	mov	w0, 1
	mov	x1, x22
	bl	dprint_vfmw
	ldr	x1, .LC974
	mov	w3, 3740
	mov	w2, w20
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3936
.L4033:
	ldrsb	w1, [x20, 6]
	mov	w2, 0
	ldr	w0, [x19, 120]
	bl	FSP_SetDisplay
	ldr	x1, .LC974
	mov	w3, 3619
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
.L4031:
	ldr	x1, .LC974
	mov	w3, 3589
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x22, .LC985
	b	.L3936
	.size	MVC_StorePicInDpb, .-MVC_StorePicInDpb
	.align	3
.LC972:
	.xword	.LC971
	.align	3
.LC974:
	.xword	.LC973
	.align	3
.LC976:
	.xword	.LC975
	.align	3
.LC978:
	.xword	.LC977
	.align	3
.LC980:
	.xword	.LC979
	.align	3
.LC982:
	.xword	.LC981
	.align	3
.LC983:
	.xword	g_event_report
	.align	3
.LC985:
	.xword	.LC984
	.align	3
.LC987:
	.xword	.LC986
	.align	3
.LC989:
	.xword	.LC988
	.align	3
.LC991:
	.xword	.LC990
	.align	3
.LC993:
	.xword	.LC992
	.align	3
.LC994:
	.xword	.LANCHOR0
	.align	3
.LC996:
	.xword	.LC995
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecGap
	.type	MVC_DecGap, %function
MVC_DecGap:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x22, x19, 11116544
	add	x23, x19, 11120640
	bl	_mcount
	add	x27, x19, 11157504
	ldrb	w2, [x19, 3]
	mov	w26, 2
	ldr	w0, [x22, 1776]
	str	w0, [x29, 108]
	lsl	x0, x2, 6
	sub	x0, x0, x2
	ldr	x3, [x19, 248]
	lsl	x0, x0, 2
	ldr	w1, [x23, 420]
	sub	x0, x0, x2
	ldr	w24, [x22, 2900]
	lsl	x0, x0, 1
	add	x1, x1, 2777088
	sub	x0, x0, x2
	ldrb	w2, [x3, 19]
	lsl	x0, x0, 2
	add	x1, x19, x1, lsl 2
	cmp	w2, 1
	add	x2, x19, x0
	add	x2, x2, 11120640
	add	x0, x0, 11120640
	ldr	w5, [x1, 11084]
	add	x0, x0, 480
	add	x0, x19, x0
	ldr	w21, [x3, 2896]
	ldrb	w1, [x2, 483]
	csel	w25, w26, wzr, eq
	ldr	w2, [x22, 1780]
	stp	w1, w2, [x29, 100]
	add	x1, x19, 11124736
	str	x0, [x27, 3328]
	ldr	w0, [x1, 828]
	cbz	w0, .L4069
	add	w21, w21, 4
	mov	w20, 1
	add	w2, w5, 1
	lsl	w21, w20, w21
	ldr	x1, .LC1000
	mov	w0, w26
	udiv	w5, w2, w21
	str	wzr, [x22, 1776]
	str	wzr, [x22, 1780]
	msub	w28, w5, w21, w2
	bl	dprint_vfmw
	ldr	x1, .LC1002
	mov	w3, w28
	mov	w2, w24
	mov	w0, w26
	bl	dprint_vfmw
	cmp	w24, w28
	ble	.L4062
	ldr	x26, .LC1006
	b	.L4066
	.p2align 3
.L4059:
	strb	wzr, [x27, 2668]
	mov	x0, x19
	bl	MVC_StorePicInDpb
	add	w1, w28, 1
	cbnz	w0, .L4070
.L4060:
	sdiv	w2, w1, w21
	ldr	w0, [x23, 420]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	str	w28, [x0, 11084]
	msub	w28, w2, w21, w1
	cmp	w24, w28
	ble	.L4062
.L4066:
	mov	w1, 1
	mov	x0, x19
	bl	MVC_AllocFrameStore
	cbnz	w0, .L4071
	mov	x1, x26
	mov	w0, 2
	bl	dprint_vfmw
	strb	w20, [x27, 2670]
	ldr	x0, [x27, 3320]
	str	w28, [x0, 20]
	str	w28, [x27, 3336]
	ldr	x0, [x27, 3320]
	str	w28, [x0, 732]
	str	w25, [x27, 3344]
	ldr	x0, [x27, 3320]
	str	wzr, [x0, 728]
	ldr	x0, [x27, 3320]
	strb	w20, [x0, 7]
	ldr	x0, [x27, 3320]
	strb	wzr, [x0, 5]
	ldr	x0, [x27, 3320]
	strb	w20, [x0, 1]
	strb	w20, [x27, 2666]
	ldr	x0, [x27, 3328]
	ldr	w1, [x23, 416]
	str	w1, [x27, 3408]
	strb	wzr, [x0, 3]
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 2900]
	cbz	w0, .L4059
	mov	x0, x19
	str	w28, [x22, 1792]
	bl	MVC_DecPOC
	ldr	w0, [x22, 1772]
	str	w0, [x27, 3348]
	ldr	w0, [x22, 1768]
	str	w0, [x27, 3352]
	ldr	w0, [x22, 1760]
	str	w0, [x27, 3356]
	ldr	w0, [x22, 1764]
	str	w0, [x27, 3360]
	mov	x0, x19
	strb	wzr, [x27, 2668]
	bl	MVC_StorePicInDpb
	add	w1, w28, 1
	cbz	w0, .L4060
.L4070:
	ldr	w1, [x29, 108]
	mov	w3, w0
	str	w1, [x22, 1776]
	mov	w2, 6654
	ldr	w1, [x29, 104]
	mov	w0, 0
	str	w1, [x22, 1780]
	ldrb	w5, [x29, 100]
	ldr	x4, [x27, 3328]
	ldr	x1, .LC1008
	strb	w5, [x4, 3]
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4069:
	ldr	x1, .LC998
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4062:
	ldr	w0, [x29, 108]
	str	w0, [x22, 1776]
	ldr	w0, [x29, 104]
	str	w0, [x22, 1780]
	mov	w0, 0
	ldrb	w2, [x29, 100]
	ldr	x1, [x27, 3328]
	strb	w2, [x1, 3]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4071:
	ldr	w0, [x29, 108]
	str	w0, [x22, 1776]
	ldr	w0, [x29, 104]
	str	w0, [x22, 1780]
	mov	w0, 0
	ldrb	w3, [x29, 100]
	ldr	x2, [x27, 3328]
	ldr	x1, .LC1004
	strb	w3, [x2, 3]
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	MVC_DecGap, .-MVC_DecGap
	.align	3
.LC998:
	.xword	.LC997
	.align	3
.LC1000:
	.xword	.LC999
	.align	3
.LC1002:
	.xword	.LC1001
	.align	3
.LC1004:
	.xword	.LC1003
	.align	3
.LC1006:
	.xword	.LC1005
	.align	3
.LC1008:
	.xword	.LC1007
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_InitPic
	.type	MVC_InitPic, %function
MVC_InitPic:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 11116544
	add	x20, x19, 11157504
	bl	_mcount
	mov	w22, 2240
	ldr	x2, [x19, 280]
	ldr	w0, [x21, 2888]
	ldrb	w1, [x20, 2664]
	str	wzr, [x29, 92]
	umull	x0, w0, w22
	add	x22, x2, x0
	cbz	w1, .L4073
	ldr	x0, [x20, 3320]
	cbz	x0, .L4074
	ldrb	w1, [x0, 2]
	cbz	w1, .L4235
.L4074:
	strb	wzr, [x20, 2664]
.L4073:
	add	x1, x29, 92
	mov	x0, x19
	bl	MVC_GetReRangeFlag
	mov	w23, w0
	ldrsb	w0, [x21, 2884]
	cmn	w0, #1
	beq	.L4236
.L4075:
	cbnz	w0, .L4078
	ldrb	w0, [x19, 2]
	cmp	w0, 1
	beq	.L4237
	ldr	w1, [x19, 28]
	ldr	w0, [x22, 28]
	cmp	w1, w0
	bne	.L4238
	add	x0, x19, 11046912
	add	x0, x0, 180
	str	x0, [x19, 248]
.L4078:
	add	x24, x19, 11112448
	ldr	w0, [x22, 24]
	ldr	w1, [x24, 3616]
	cmp	w1, w0
	beq	.L4239
.L4082:
	strb	wzr, [x22, 20]
	mov	x1, x22
	ldr	x0, [x19, 248]
	bl	mvc_assign_quant_params
	ldr	x3, .LC1009
	mov	x2, 2240
	mov	x1, x22
	add	x0, x24, 3592
	ldr	x3, [x3, 112]
	blr	x3
.L4083:
	ldr	w0, [x29, 92]
	cbnz	w0, .L4240
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 960]
	cmp	w1, 1
	beq	.L4085
.L4095:
	ldr	w0, [x22, 24]
	ldr	w1, [x24, 3616]
	cmp	w1, w0
	bne	.L4105
	ldrb	w0, [x22, 20]
	cbnz	w0, .L4105
	ldrsb	w0, [x21, 2884]
	cmn	w0, #1
	beq	.L4241
.L4107:
	cbnz	w0, .L4108
	add	x0, x19, 10768384
	add	x23, x19, 11120640
	add	x5, x0, 4068
	ldr	w2, [x0, 4064]
	ldr	w3, [x23, 416]
	adds	w2, w2, 1
	beq	.L4109
	ldr	w0, [x0, 4068]
	cmp	w3, w0
	beq	.L4242
	mov	w4, w2
	mov	w0, 0
	b	.L4111
	.p2align 3
.L4112:
	ldr	w1, [x5, w0, sxtw 2]
	cmp	w3, w1
	beq	.L4109
.L4111:
	add	w0, w0, 1
	cmp	w0, w4
	mov	w2, w0
	bne	.L4112
.L4109:
	str	w2, [x23, 420]
.L4108:
	ldrb	w1, [x21, 2875]
	ldr	x0, [x19, 248]
	cmp	w1, 5
	ldr	w2, [x0, 2896]
	beq	.L4113
.L4250:
	ldrb	w0, [x19, 8]
	ldr	w1, [x21, 2900]
	cmp	w0, 2
	beq	.L4115
.L4251:
	ldr	x3, [x19, 224]
	ldr	w0, [x3, 24]
	cmp	w0, 2
	beq	.L4115
	add	x23, x19, 11120640
	ldr	w0, [x23, 420]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 11084]
	cmp	w0, w1
	beq	.L4115
	add	w2, w2, 4
	mov	w4, 1
	lsl	w22, w4, w2
	add	w0, w0, w4
	udiv	w2, w0, w22
	msub	w0, w2, w22, w0
	cmp	w0, w1
	beq	.L4115
	str	w4, [x3, 656]
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 656]
	cbnz	w1, .L4116
	ldr	x2, [x0, 696]
	mov	x1, 4294967296
	cmp	x2, x1
	beq	.L4243
.L4117:
	ldr	w0, [x23, 420]
	ldr	w1, [x21, 2900]
	add	x0, x19, x0, lsl 2
	add	x0, x0, 11116544
	ldr	w2, [x0, 2892]
	cmp	w1, w2
	sub	w3, w1, w2
	bls	.L4118
	ldr	w4, [x24, 3572]
	cmp	w4, w3
	ccmp	w2, wzr, 4, cc
	beq	.L4116
	ldrb	w2, [x21, 2872]
	cmp	w2, 2
	bne	.L4244
	cbnz	w1, .L4120
	sub	w1, w22, #1
.L4121:
	str	w1, [x0, 2892]
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L4116
	ldr	x1, .LC1012
	mov	w3, w0
	mov	w2, 7116
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
	.p2align 3
.L4240:
	ldr	x0, [x19, 224]
	ldr	w1, [x0, 772]
	cbnz	w1, .L4085
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L4245
.L4085:
	ldr	w1, [x19, 84]
	add	w1, w1, 1
	str	w1, [x19, 84]
	cbnz	w23, .L4096
	ldr	w0, [x0, 960]
	cmp	w0, 1
	beq	.L4096
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbnz	w0, .L4246
	cbz	x19, .L4146
.L4254:
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.17
	cbnz	w0, .L4099
	cbnz	w23, .L4101
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 960]
	cmp	w0, 1
	bne	.L4095
.L4101:
	ldr	w4, [x24, 3572]
	add	x2, x19, 11108352
	mov	w1, 2
	add	x3, x19, 48
	lsl	w4, w4, 1
	str	w4, [x19, 52]
	ldr	w0, [x24, 3552]
	ldrb	w23, [x2, 3716]
	add	w0, w0, 1
	ldr	w25, [x24, 3548]
	sub	w23, w1, w23
	lsl	w0, w0, 4
	add	w25, w25, 1
	mul	w23, w0, w23
	lsl	w25, w25, 4
	mov	x0, x19
	mov	w2, w23
	mov	w1, w25
	bl	MVC_ArrangeVahbMem
	cmp	w0, 1
	beq	.L4247
.L4231:
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 960]
	cmp	w0, 1
	beq	.L4248
	ldr	x1, .LC1020
	mov	w0, 0
	stp	wzr, wzr, [x19, 12]
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x19
	bl	MVC_ClearAll
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4236:
	mov	w1, 1
	strb	w1, [x19, 2]
	mov	w1, 3992
	ldr	x4, [x19, 272]
	ldr	w2, [x22, 28]
	add	x3, x19, 11112448
	str	w2, [x19, 24]
	ldr	w2, [x22, 28]
	ldr	w3, [x3, 344]
	umull	x1, w2, w1
	add	x1, x4, x1
	ldr	w2, [x1, 744]
	cmp	w3, w2
	beq	.L4249
.L4076:
	ldr	w0, [x19, 84]
	add	x24, x19, 11108352
	ldr	x3, .LC1009
	add	x24, x24, 3696
	add	w0, w0, 1
	str	w0, [x19, 84]
	strb	wzr, [x1, 26]
	mov	x2, 3992
	mov	x0, x24
	ldr	x3, [x3, 112]
	blr	x3
	ldrsb	w0, [x21, 2884]
	str	x24, [x19, 248]
	b	.L4075
	.p2align 3
.L4105:
	ldr	x3, .LC1009
	mov	x2, 2240
	strb	wzr, [x22, 20]
	mov	x1, x22
	add	x0, x24, 3592
	ldr	x3, [x3, 112]
	blr	x3
	ldrsb	w0, [x21, 2884]
	cmn	w0, #1
	bne	.L4107
.L4241:
	add	x23, x19, 11120640
	str	wzr, [x23, 420]
	ldrb	w1, [x21, 2875]
	ldr	x0, [x19, 248]
	cmp	w1, 5
	ldr	w2, [x0, 2896]
	bne	.L4250
.L4113:
	add	x23, x19, 11120640
	ldr	w1, [x21, 2900]
	ldr	w0, [x23, 420]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	str	w1, [x0, 11084]
	ldrb	w0, [x19, 8]
	cmp	w0, 2
	bne	.L4251
	.p2align 2
.L4115:
	ldrb	w0, [x21, 2880]
	cbz	w0, .L4129
	add	x23, x19, 11120640
	ldr	w0, [x23, 420]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	str	w1, [x0, 11084]
.L4129:
	mov	x0, x19
	str	w1, [x21, 1792]
	bl	MVC_DecPOC
	mov	w1, 0
	mov	x0, x19
	bl	MVC_AllocFrameStore
	cbnz	w0, .L4252
	strb	wzr, [x20, 2671]
	mov	w0, 1
	strb	w0, [x20, 2664]
	add	x4, x20, 3328
	mov	w6, 1
	ldrb	w0, [x21, 2875]
	strb	w0, [x20, 2670]
	ldr	w8, [x21, 2900]
	str	w8, [x20, 3336]
	ldrb	w7, [x21, 2880]
	str	w7, [x20, 3344]
	ldr	w3, [x21, 1772]
	str	w3, [x20, 3348]
	ldr	w2, [x21, 1768]
	str	w2, [x20, 3352]
	ldr	w1, [x21, 1760]
	str	w1, [x20, 3356]
	ldr	w0, [x21, 1764]
	strb	wzr, [x20, 2666]
	strb	wzr, [x20, 2669]
	strb	wzr, [x20, 2668]
	stp	w0, w3, [x4, 32]
	stp	w2, w1, [x4, 40]
	str	w0, [x20, 3376]
	mov	w0, -1
	str	w0, [x20, 3400]
	ldrb	w5, [x21, 2873]
	cbz	w5, .L4131
	strb	w6, [x21, 2873]
	mov	w5, w6
	mov	w6, 2
.L4131:
	ldr	x4, [x19, 248]
	mov	w3, 2
	ldrb	w2, [x4, 20]
	ldr	w0, [x4, 3952]
	sub	w1, w3, w2
	mov	w2, 0
	madd	w1, w0, w1, w1
	udiv	w0, w1, w6
	str	w0, [x20, 3388]
	ldrb	w1, [x4, 20]
	sub	w1, w3, w1
	ldr	w3, [x4, 3952]
	madd	w1, w3, w1, w1
	str	w1, [x20, 3392]
	ldr	w1, [x4, 3948]
	add	w1, w1, 1
	str	w1, [x20, 3384]
	mul	w0, w0, w1
	str	w0, [x20, 3396]
	ldrb	w0, [x24, 3592]
	strb	w0, [x20, 2672]
	cbnz	w5, .L4132
	ldrb	w0, [x4, 21]
	cmp	w0, wzr
	cset	w2, ne
.L4132:
	strb	w2, [x20, 2673]
	add	x23, x19, 11120640
	cbz	w7, .L4133
	ldr	w0, [x23, 420]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	str	w8, [x0, 11084]
.L4133:
	ldr	x0, [x20, 3320]
	cbz	x0, .L4134
	ldrsb	w1, [x21, 2884]
	strb	w1, [x0, 9]
.L4134:
	mov	w0, -1
	str	w0, [x20, 3408]
	ldrb	w0, [x21, 2883]
	cbz	w0, .L4135
	ldr	w0, [x23, 416]
	str	w0, [x20, 3408]
	ldrb	w0, [x21, 2881]
	strb	w0, [x20, 2674]
	ldrb	w0, [x21, 2882]
	strb	w0, [x20, 2675]
.L4135:
	ldr	w0, [x23, 420]
	mov	x22, -1
	str	w0, [x20, 3412]
	mov	w0, 29
	ldr	x1, .LC1034
	mov	w24, 2
	ldrb	w3, [x19, 3]
	lsl	x2, x3, 6
	sub	x2, x2, x3
	lsl	x2, x2, 2
	sub	x2, x2, x3
	lsl	x2, x2, 1
	sub	x2, x2, x3
	lsl	x2, x2, 2
	add	x2, x2, 11120640
	add	x2, x2, 480
	add	x2, x19, x2
	str	x2, [x20, 3328]
	ldr	x2, [x19, 224]
	ldr	x3, [x2, 64]
	str	x3, [x20, 3264]
	ldr	x3, [x2, 80]
	str	x3, [x20, 3272]
	ldr	x3, [x2, 96]
	str	x3, [x20, 3280]
	str	x22, [x2, 64]
	ldr	x2, [x20, 3264]
	bl	dprint_vfmw
	ldr	x1, .LC1036
	mov	w0, 29
	ldr	x2, [x20, 3272]
	bl	dprint_vfmw
	ldr	x4, [x19, 248]
	add	x5, x19, 11108352
	ldr	x1, .LC1009
	mov	x2, 4
	ldr	w0, [x4, 3948]
	ldr	x6, [x1, 96]
	mov	w1, 0
	add	w0, w0, 1
	lsl	w0, w0, 4
	str	w0, [x20, 2748]
	add	x0, x20, 2744
	ldrb	w3, [x4, 20]
	ldr	w7, [x4, 3952]
	sub	w3, w24, w3
	madd	w3, w7, w3, w3
	lsl	w3, w3, 4
	str	w3, [x20, 2752]
	ldr	w3, [x4, 748]
	ldr	w25, [x5, 3748]
	cmp	w3, 1
	cset	w26, ne
	and	w25, w25, 7
	blr	x6
	ldrb	w0, [x20, 2744]
	mov	w1, w25
	and	w0, w0, 252
	bfi	w0, w26, 2, 3
	strb	w0, [x20, 2744]
	ldr	x3, [x19, 248]
	ldr	w2, [x3, 56]
	bfi	w0, w2, 5, 3
	ldrb	w2, [x20, 2745]
	strb	w0, [x20, 2744]
	bfi	w2, w24, 0, 2
	and	w0, w2, -13
	bfi	w0, w24, 4, 2
	strb	w0, [x20, 2745]
	add	x0, x20, 2680
	ldr	w3, [x3, 52]
	ldr	w2, [x20, 2744]
	bfi	w2, w3, 14, 3
	str	w2, [x20, 2744]
	bl	SetAspectRatio
	ldr	w0, [x19, 84]
	ldr	x1, [x20, 3320]
	str	w0, [x20, 2836]
	cbz	x1, .L4253
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 3984]
	str	w0, [x1, 156]
	str	w0, [x20, 2764]
	ldr	x1, [x20, 3320]
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 3988]
	str	w0, [x1, 160]
	str	w0, [x20, 2768]
	ldr	x1, [x20, 3320]
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 3976]
	str	w0, [x1, 148]
	str	w0, [x20, 2756]
	ldr	x1, [x20, 3320]
	ldr	x0, [x19, 248]
	ldr	w0, [x0, 3980]
	str	w0, [x1, 152]
	str	w0, [x20, 2760]
	ldrb	w2, [x20, 2667]
	ldr	x0, [x20, 3320]
	cmp	w2, wzr
	ldr	w1, [x20, 2744]
	cset	w2, ne
	str	w2, [x20, 2732]
	str	w1, [x0, 136]
	ldr	x0, [x20, 3320]
	ldr	w1, [x20, 2732]
	str	w1, [x0, 124]
	ldr	w0, [x21, 2900]
	str	w0, [x20, 2856]
	ldr	x1, [x20, 3320]
	ldr	w2, [x23, 416]
	str	w2, [x20, 2864]
	str	w0, [x1, 248]
	ldr	x0, [x20, 3320]
	ldr	w1, [x23, 416]
	str	w1, [x0, 256]
	ldr	x1, [x20, 3320]
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_GetDispPhyFs
	cbz	x0, .L4137
	ldr	w3, [x20, 2732]
	mov	w1, 0
	ldr	w2, [x0, 4]
	cmp	w3, wzr
	ldr	w0, [x19, 120]
	cset	w3, ne
	bl	FSP_SetStoreType
.L4137:
	ldr	w1, [x19, 60]
	add	x4, x20, 3224
	add	x5, x20, 3256
.L4141:
	ldr	x0, [x4]
	cbnz	x0, .L4138
	cbz	w1, .L4138
	ldr	x0, [x19, 832]
	subs	w1, w1, #1
	str	x0, [x4]
	beq	.L4139
	add	x2, x19, 832
	mov	w0, 0
	.p2align 2
.L4140:
	add	w0, w0, 1
	cmp	w0, w1
	add	x3, x19, x0, uxtw 3
	ldr	x3, [x3, 832]
	str	x3, [x2], 8
	bne	.L4140
.L4139:
	add	x0, x19, x1, uxtw 3
	str	xzr, [x0, 832]
	str	w1, [x19, 60]
.L4138:
	add	x4, x4, 8
	cmp	x5, x4
	bne	.L4141
	cbz	w1, .L4143
	cmp	w1, wzr
	ble	.L4143
	.p2align 2
.L4144:
	add	x22, x19, x1, sxtw 3
	sub	w21, w1, #1
	ldr	w0, [x19, 120]
	ldr	x1, [x22, 824]
	bl	FreeUsdByDec
	str	xzr, [x22, 824]
	mov	w1, w21
	cbnz	w21, .L4144
.L4143:
	str	wzr, [x19, 60]
	mov	x0, x19
	strb	wzr, [x20, 2676]
	bl	MVC_UpdateReflist
	mov	x0, x19
	bl	MVC_UpdateLTReflist
	mov	x0, x19
	bl	MVC_CalcPicNum
	mov	w0, 0
.L4081:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L4243:
	ldr	w1, [x0, 704]
	cbnz	w1, .L4117
	ldr	w0, [x0, 660]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L4117
	.p2align 2
.L4116:
	add	x0, x19, 11108352
	ldrb	w0, [x0, 3715]
	cbnz	w0, .L4125
	ldr	x1, .LC1026
	mov	w0, 2
	bl	dprint_vfmw
	ldr	x0, [x19, 224]
	ldr	w0, [x0, 660]
	tst	w0, -1025
	bne	.L4232
	ldr	w0, [x23, 416]
	cbnz	w0, .L4232
	ldr	w0, [x23, 420]
	ldr	w1, [x21, 2900]
	add	x0, x0, 2777088
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 11084]
	add	w0, w0, 1
	udiv	w2, w0, w22
	msub	w0, w2, w22, w0
	cmp	w1, w0
	bcs	.L4115
	ldrb	w0, [x21, 2872]
	cmp	w0, 2
	beq	.L4115
	mov	x0, x19
	bl	MVC_ClearCurrPic
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	w4, [x23, 420]
	mov	w2, 7166
	ldr	x1, .LC1028
	mov	w0, 0
	add	x4, x4, 2777088
	ldr	w3, [x21, 2900]
	add	x19, x19, x4, lsl 2
	ldr	w4, [x19, 11084]
	add	w4, w4, 1
	udiv	w5, w4, w22
	msub	w4, w5, w22, w4
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
	.p2align 3
.L4239:
	ldrb	w0, [x22, 20]
	cbz	w0, .L4083
	b	.L4082
	.p2align 3
.L4096:
	ldr	x1, .LC1022
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_GetBackPicFromVOQueue
	cbnz	x19, .L4254
.L4146:
	mov	w0, -1
.L4099:
	ldr	x1, .LC1014
	mov	w3, w0
	mov	w2, 7015
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
	.p2align 3
.L4249:
	ldrb	w2, [x1, 26]
	cbnz	w2, .L4076
	add	x24, x19, 11108352
	add	x24, x24, 3696
	str	x24, [x19, 248]
	b	.L4075
	.p2align 3
.L4235:
	ldrsb	w1, [x0, 6]
	mov	w2, 1
	ldr	w0, [x19, 120]
	bl	FSP_ClearLogicFs
	ldr	x0, [x20, 3320]
	strb	wzr, [x0, 2]
	ldr	x0, [x20, 3320]
	strb	wzr, [x0, 5]
	b	.L4074
	.p2align 3
.L4248:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -2
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4125:
	mov	x0, x19
	bl	MVC_DecGap
	cbnz	w0, .L4128
.L4232:
	ldr	w1, [x21, 2900]
	b	.L4115
.L4245:
	ldr	w0, [x19, 84]
	add	w0, w0, 1
	str	w0, [x19, 84]
	cbnz	w23, .L4255
.L4086:
	cbz	x19, .L4145
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_InitDPB.part.17
	mov	w3, w0
	cbnz	w0, .L4087
	add	x2, x19, 11108352
	ldr	w1, [x24, 3552]
	ldr	w26, [x24, 3548]
	add	w1, w1, 1
	ldrb	w25, [x2, 3716]
	mov	w2, 2
	lsl	w1, w1, 4
	add	w26, w26, 1
	sub	w25, w2, w25
	lsl	w26, w26, 4
	mul	w25, w1, w25
	cbz	w23, .L4089
	ldr	w1, [x19, 12]
	cbnz	w1, .L4089
	ldr	w4, [x24, 3572]
	ldr	x3, [x19, 224]
	lsl	w4, w4, 1
	str	w4, [x19, 52]
	ldr	w1, [x3, 732]
	cmp	w26, w1
	bhi	.L4090
	ldr	w2, [x3, 736]
	cmp	w25, w2
	bhi	.L4090
	add	x5, x19, 11124736
	ldr	w6, [x3, 756]
	ldr	w5, [x5, 824]
	cmp	w6, w5
	bcc	.L4256
	ldr	w0, [x3, 760]
	cbnz	w0, .L4093
	mov	w4, 1
	str	w4, [x19, 52]
	ldr	w1, [x3, 732]
	ldr	w2, [x3, 736]
.L4093:
	add	x3, x19, 48
	mov	x0, x19
	bl	MVC_ArrangeVahbMem
	cmp	w0, 1
	bne	.L4231
.L4089:
	lsr	w26, w26, 4
	lsr	w25, w25, 4
	stp	w26, w25, [x19, 12]
	b	.L4095
.L4237:
	strb	wzr, [x19, 2]
	ldr	x0, .LC1009
	ldr	w1, [x22, 28]
	ldr	x3, [x0, 112]
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x1, x0, x1
	add	x0, x19, 10768384
	lsl	x2, x1, 2
	add	x0, x0, 4060
	sub	x1, x2, x1
	lsl	x2, x1, 6
	add	x1, x1, x2
	mov	x2, 8500
	movk	x2, 0x5, lsl 16
	add	x1, x19, x1, lsl 2
	add	x1, x1, 12288
	add	x1, x1, 2396
	blr	x3
	add	x0, x19, 11046912
	add	x0, x0, 180
	str	x0, [x19, 248]
	ldr	w0, [x0, 744]
	str	w0, [x19, 28]
	b	.L4078
	.p2align 3
.L4247:
	lsr	w25, w25, 4
	lsr	w23, w23, 4
	stp	w25, w23, [x19, 12]
	b	.L4095
.L4118:
	ldr	w4, [x24, 3572]
	add	w3, w3, w22
	cmp	w4, w3
	ccmp	w2, wzr, 4, cc
	beq	.L4116
	ldrb	w2, [x21, 2872]
	cmp	w2, 2
	bne	.L4257
	cbnz	w1, .L4123
	sub	w1, w22, #1
.L4124:
	str	w1, [x0, 2892]
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L4116
	ldr	x1, .LC1012
	mov	w3, w0
	mov	w2, 7143
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
	.p2align 3
.L4145:
	mov	w3, -1
.L4087:
	ldr	x1, .LC1014
	mov	w2, 6931
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
	.p2align 3
.L4255:
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbz	w0, .L4086
	ldr	x1, .LC1012
	mov	w3, w0
	mov	w2, 6922
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
	.p2align 3
.L4246:
	ldr	x1, .LC1012
	mov	w3, w0
	mov	w2, 7006
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
.L4128:
	ldr	x1, .LC1030
	mov	w2, 7178
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
	.p2align 3
.L4238:
	ldr	x1, .LC1010
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
.L4242:
	mov	w2, 0
	b	.L4109
.L4252:
	ldr	x1, .LC1032
	mov	w2, 7198
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
.L4253:
	ldr	x1, .LC1038
	mov	w2, 7293
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w22
	b	.L4081
.L4120:
	sub	w1, w1, #1
	b	.L4121
.L4123:
	sub	w1, w1, #1
	b	.L4124
.L4244:
	mov	x0, x19
	bl	MVC_ClearCurrPic
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	w5, [x23, 420]
	mov	w2, 7105
	ldr	x1, .LC1024
	ldr	w6, [x21, 2900]
	add	x5, x5, 2777088
	ldr	w4, [x24, 3572]
.L4233:
	add	x19, x19, x5, lsl 2
	mov	w0, 0
	ldr	w3, [x19, 11084]
	sub	w3, w6, w3
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
.L4257:
	mov	x0, x19
	bl	MVC_ClearCurrPic
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	ldr	w5, [x23, 420]
	mov	w2, 7132
	ldr	x1, .LC1024
	ldr	w6, [x21, 2900]
	add	x5, x5, 2777088
	ldr	w4, [x24, 3572]
	b	.L4233
.L4090:
	ldr	x1, .LC1016
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
.L4256:
	ldr	x1, .LC1018
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4081
	.size	MVC_InitPic, .-MVC_InitPic
	.align	3
.LC1009:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1010:
	.xword	.LC94
	.align	3
.LC1012:
	.xword	.LC1011
	.align	3
.LC1014:
	.xword	.LC1013
	.align	3
.LC1016:
	.xword	.LC1015
	.align	3
.LC1018:
	.xword	.LC1017
	.align	3
.LC1020:
	.xword	.LC1019
	.align	3
.LC1022:
	.xword	.LC1021
	.align	3
.LC1024:
	.xword	.LC1023
	.align	3
.LC1026:
	.xword	.LC1025
	.align	3
.LC1028:
	.xword	.LC1027
	.align	3
.LC1030:
	.xword	.LC1029
	.align	3
.LC1032:
	.xword	.LC1031
	.align	3
.LC1034:
	.xword	.LC1033
	.align	3
.LC1036:
	.xword	.LC1035
	.align	3
.LC1038:
	.xword	.LC1037
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecSlice
	.type	MVC_DecSlice, %function
MVC_DecSlice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 11116544
	bl	_mcount
	ldr	w2, [x20, 68]
	mov	w0, 22
	ldr	x1, .LC1039
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	x1, [x20, 240]
	mov	x0, x20
	ldrb	w2, [x1, 2]
	strb	w2, [x19, 2875]
	ldrb	w1, [x1, 4]
	strb	w1, [x19, 2880]
	bl	MVC_ProcessSliceHeaderFirstPart
	cbnz	w0, .L4304
	mov	x0, x20
	bl	MVC_ProcessSliceHeaderSecondPart
	cbnz	w0, .L4304
	ldr	w2, [x20, 64]
	mov	w3, 0
	cbz	w2, .L4265
	sub	w9, w2, #1
	add	x4, x20, 11161600
	add	x9, x9, 1392640
	add	x4, x4, 104
	add	x9, x9, 2574
	mov	x0, 0
	mov	w10, 0
	mov	w3, 0
	add	x9, x20, x9, lsl 3
	.p2align 2
.L4273:
	ldr	x1, [x4]
	ldr	x6, [x1, 8]
	cbz	x6, .L4285
	ldr	x5, [x1, 40]
	ldr	w7, [x1, 16]
	cbz	x5, .L4286
.L4309:
	ldr	w1, [x1, 48]
.L4268:
	cbz	x0, .L4269
	cmp	x6, x0
	mov	w8, w7
	bls	.L4270
	sub	x0, x6, x0
	sub	w0, w0, w10
	add	w8, w0, w7
.L4270:
	add	w3, w1, w3
	add	w3, w8, w3
.L4271:
	cbz	x5, .L4288
	mov	x0, x5
	mov	w10, w1
.L4272:
	add	x4, x4, 8
	cmp	x9, x4
	bne	.L4273
.L4265:
	add	x21, x20, 11157504
	str	w3, [x20, 104]
	ldr	w0, [x21, 3384]
	ldr	w4, [x21, 3388]
	mul	w4, w0, w4
	cmp	w4, 1620
	bgt	.L4305
	lsl	w1, w4, 2
	mov	w5, 32769
	sub	w1, w1, w4
	mov	w4, 16384
	lsl	w1, w1, 8
	asr	w0, w1, 1
	cmp	w1, w5
	csel	w4, w0, w4, gt
.L4275:
	ldr	w0, [x20, 32]
	cmp	w0, w2
	bls	.L4276
	cmp	w4, w3
	bcc	.L4276
	ldrb	w0, [x19, 2877]
	cbz	w0, .L4279
	ldr	x1, .LC1047
	mov	w0, 2
	bl	dprint_vfmw
	str	wzr, [x20, 100]
	ldr	w0, [x20, 88]
	add	w0, w0, 1
	str	w0, [x20, 88]
	ldrb	w0, [x21, 2667]
	cbnz	w0, .L4280
	ldr	w0, [x20, 92]
	add	w0, w0, 1
	str	w0, [x20, 92]
.L4281:
	mov	x0, x20
	bl	MVC_InitPic
	cmn	w0, #2
	beq	.L4262
	cbnz	w0, .L4306
	mov	x0, x20
	bl	MVC_WritePicMsg
.L4279:
	mov	x0, x20
	bl	MVC_PicTypeStatistic
	mov	x0, x20
	bl	MVC_DecList
	cbnz	w0, .L4307
	mov	x0, x20
	bl	MVC_IsRefListWrong
	cbnz	w0, .L4308
	mov	x0, x20
	bl	MVC_CalcStreamBits
	mov	x0, x20
	bl	MVC_WriteSliceMsg
	mov	x0, x20
	bl	MVC_ExitSlice
	ldr	w1, [x20, 100]
	mov	w2, 1
	mov	w0, 0
	strb	w2, [x20, 4]
	add	w1, w1, 1
	str	w1, [x20, 100]
.L4262:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4288:
	mov	x0, x6
	mov	w10, w7
	b	.L4272
	.p2align 3
.L4269:
	add	w3, w7, w3
	add	w3, w3, w1
	b	.L4271
	.p2align 3
.L4285:
	ldr	x5, [x1, 40]
	mov	w7, 0
	cbnz	x5, .L4309
	.p2align 2
.L4286:
	mov	w1, 0
	b	.L4268
	.p2align 3
.L4305:
	lsl	w4, w4, 7
	b	.L4275
	.p2align 3
.L4280:
	ldr	w0, [x20, 96]
	add	w0, w0, 1
	str	w0, [x20, 96]
	b	.L4281
.L4304:
	ldr	x1, .LC1040
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1041
	ldr	x4, [x0]
	cbz	x4, .L4302
	add	x2, x29, 64
	ldr	w0, [x20, 120]
	mov	w5, -1
	mov	w3, 4
	mov	w1, 100
	str	w5, [x2, -8]!
	blr	x4
.L4302:
	mov	x0, x20
	bl	MVC_ClearCurrSlice
	mov	w0, -1
	b	.L4262
.L4276:
	ldr	x1, .LC1043
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 32]
	ldr	w2, [x20, 64]
	cmp	w2, w1
	bcc	.L4278
	ldr	x0, .LC1041
	ldr	x4, [x0]
	cbz	x4, .L4278
	ldr	w0, [x20, 120]
	mov	w3, 8
	stp	w2, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 108
	blr	x4
.L4278:
	ldr	x1, .LC1045
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x20
	bl	MVC_ClearCurrPic
	mov	w0, -1
	b	.L4262
.L4307:
	ldr	x1, .LC1051
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4262
.L4308:
	ldr	x1, .LC1053
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4302
.L4306:
	ldr	x1, .LC1049
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4262
	.size	MVC_DecSlice, .-MVC_DecSlice
	.align	3
.LC1039:
	.xword	.LC886
	.align	3
.LC1040:
	.xword	.LC888
	.align	3
.LC1041:
	.xword	g_event_report
	.align	3
.LC1043:
	.xword	.LC1042
	.align	3
.LC1045:
	.xword	.LC1044
	.align	3
.LC1047:
	.xword	.LC1046
	.align	3
.LC1049:
	.xword	.LC1048
	.align	3
.LC1051:
	.xword	.LC1050
	.align	3
.LC1053:
	.xword	.LC1052
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DecOneNal
	.type	MVC_DecOneNal, %function
MVC_DecOneNal:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x3, [x19, 240]
	ldr	w0, [x3, 76]
	cbz	w0, .L4315
	ldr	w2, [x19, 104]
	mov	w0, 0
	.p2align 2
.L4314:
	ubfiz	x1, x0, 5, 32
	add	w0, w0, 1
	add	x1, x3, x1
	ldr	w1, [x1, 16]
	add	w2, w2, w1
	str	w2, [x19, 104]
	ldr	w1, [x3, 76]
	cmp	w1, w0
	bhi	.L4314
.L4315:
	add	x22, x19, 872
	strb	wzr, [x3]
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w21, w0
	and	w4, w0, 31
	ldr	x0, [x19, 240]
	ubfx	x3, x21, 5, 2
	ubfx	x1, x21, 7, 1
	mov	w2, -1
	strb	w4, [x0, 2]
	ldr	x0, [x19, 240]
	strb	w3, [x0, 4]
	ldr	x0, [x19, 240]
	str	w1, [x0, 84]
	ldr	x1, [x19, 240]
	ldr	w0, [x1, 72]
	add	w0, w0, 32
	str	w0, [x1, 72]
	strb	wzr, [x19, 10]
	ldr	x0, [x19, 240]
	strb	w2, [x0, 5]
	ldr	x0, [x19, 240]
	ldrb	w3, [x0, 2]
	cmp	w3, 20
	beq	.L4494
	ldr	x1, .LC1055
	mov	w0, 22
	ldr	w2, [x19, 68]
	bl	dprint_vfmw
	ldr	w0, [x19, 68]
	cmp	w0, 371
	beq	.L4495
.L4318:
	ldr	x1, [x19, 240]
	add	w0, w0, 1
	str	w0, [x19, 68]
	ldrb	w2, [x1, 2]
	sub	w0, w2, #1
	cmp	w0, 29
	bls	.L4496
.L4319:
	ldr	x1, .LC1097
	mov	w3, w21
	mov	w0, 22
	bl	dprint_vfmw
	cmp	w21, 256
	beq	.L4361
	ldr	x1, .LC1099
	mov	w0, 1
	bl	dprint_vfmw
.L4361:
	ldr	x1, [x19, 240]
	cbz	x1, .L4362
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4362:
	ldr	x0, .LC1063
	ldr	x4, [x0]
	cbz	x4, .L4477
.L4481:
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4477:
	mov	w0, 0
.L4501:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4496:
	ldr	x1, .LC1058
	ldrh	w0, [x1,w0,uxtw #1]
	adr	x1, .Lrtx4321
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx4321:
	.section	.rodata
	.align	0
	.align	2
.L4321:
	.2byte	(.L4320 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4320 - .Lrtx4321) / 4
	.2byte	(.L4322 - .Lrtx4321) / 4
	.2byte	(.L4323 - .Lrtx4321) / 4
	.2byte	(.L4324 - .Lrtx4321) / 4
	.2byte	(.L4325 - .Lrtx4321) / 4
	.2byte	(.L4326 - .Lrtx4321) / 4
	.2byte	(.L4327 - .Lrtx4321) / 4
	.2byte	(.L4328 - .Lrtx4321) / 4
	.2byte	(.L4329 - .Lrtx4321) / 4
	.2byte	(.L4330 - .Lrtx4321) / 4
	.2byte	(.L4331 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4332 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4319 - .Lrtx4321) / 4
	.2byte	(.L4333 - .Lrtx4321) / 4
	.text
.L4333:
	ldr	x1, .LC1094
	mov	w2, 30
	mov	w0, 22
	bl	dprint_vfmw
	cbnz	w20, .L4359
	ldr	x1, [x19, 240]
	cbz	x1, .L4359
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4359:
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w20, w0
	mov	w1, 32
	mov	x0, x22
	rev	w20, w20
	bl	BsGet
	rev	w0, w0
	ldr	x1, .LC1095
	add	x1, x1, 432
	ldr	w2, [x1, 4]
	ldr	w1, [x1, 8]
	cmp	w2, w20
	ccmp	w1, w0, 0, eq
	bne	.L4477
	ldr	x20, .LC1063
	ldr	x4, [x20]
	cbz	x4, .L4360
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4360:
	strb	wzr, [x19]
	mov	x0, x19
	bl	MVC_DecVDM
	cbz	w0, .L4477
.L4488:
	ldr	x4, [x20]
	cbz	x4, .L4476
.L4478:
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4476:
	mov	w0, -1
.L4500:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L4320:
	ldr	x1, .LC1060
	mov	w0, 22
	ldr	w3, [x19, 80]
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	add	x2, x19, 11116544
	add	x5, x19, 11120640
	add	x0, x19, 12288
	mov	w3, -1
	ldrb	w6, [x1, 2]
	strb	w6, [x2, 2875]
	ldrb	w4, [x1, 4]
	strb	w4, [x2, 2880]
	ldrsb	w1, [x1, 5]
	strb	w1, [x2, 2884]
	strb	wzr, [x2, 2883]
	str	w3, [x5, 416]
	ldrb	w3, [x0, 2384]
	cmp	w3, 1
	beq	.L4497
	cmn	w1, #1
	beq	.L4498
.L4335:
	ldr	x1, .LC1062
	mov	w0, 21
	ldr	w2, [x19, 88]
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_SliceCheck
	cbnz	w0, .L4499
	mov	x0, x19
	bl	MVC_DecSlice
	cmn	w0, #2
	beq	.L4346
	cbz	w0, .L4477
	ldr	x0, .LC1063
	ldr	x4, [x0]
	cbnz	x4, .L4478
	mov	w0, -1
	b	.L4500
	.p2align 3
.L4325:
	ldr	x1, .LC1077
	mov	w2, 9
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbz	x1, .L4477
	.p2align 2
.L4480:
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
	mov	w0, 0
.L4346:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L4326:
	ldr	x1, .LC1079
	mov	w2, 10
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbnz	x1, .L4480
	mov	w0, 0
	b	.L4501
.L4327:
	ldr	x1, .LC1083
	mov	w2, 11
	mov	w0, 22
	bl	dprint_vfmw
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w20, w0
	mov	w1, 32
	mov	x0, x22
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w20, w2
	ccmp	w0, w1, 0, eq
	bne	.L4486
	ldr	x20, .LC1063
	mov	w0, 1
	strb	w0, [x19, 1]
	ldr	x4, [x20]
	cbz	x4, .L4356
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4356:
	strb	wzr, [x19]
	mov	x0, x19
	bl	MVC_DecVDM
	cbz	w0, .L4486
	b	.L4488
.L4328:
	ldr	x1, .LC1081
	mov	w2, 12
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbnz	x1, .L4480
	mov	w0, 0
	b	.L4501
.L4329:
	ldr	x1, .LC1085
	mov	w2, 13
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbnz	x1, .L4480
	mov	w0, 0
	b	.L4501
.L4330:
	ldr	x1, .LC1087
	mov	w2, 14
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x19, 240]
	cbnz	x1, .L4480
	mov	w0, 0
	b	.L4501
.L4331:
	ldr	x1, .LC1089
	mov	w2, 15
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DecSubSPS
	mov	w20, w0
	ldr	x1, [x19, 240]
	cbz	x1, .L4357
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4357:
	cbnz	w20, .L4502
	ldr	w1, [x19, 20]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 20]
	b	.L4346
.L4332:
	ldr	x1, .LC1092
	mov	w2, 19
	mov	w0, 22
	bl	dprint_vfmw
.L4486:
	ldr	x1, [x19, 240]
	cbnz	x1, .L4480
	mov	w0, 0
	b	.L4501
.L4323:
	ldr	x1, .LC1069
	mov	w2, 7
	ldr	w3, [x19, 72]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DecSPS
	mov	w20, w0
	ldr	x1, [x19, 240]
	cbz	x1, .L4351
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4351:
	cbnz	w20, .L4503
	ldr	w1, [x19, 72]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 72]
	b	.L4346
.L4324:
	ldr	x1, .LC1065
	mov	w2, 8
	ldr	w3, [x19, 76]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DecPPS
	mov	w20, w0
	ldr	x1, [x19, 240]
	cbz	x1, .L4349
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4349:
	cbnz	w20, .L4504
	ldr	w1, [x19, 76]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 76]
	b	.L4346
.L4322:
	ldr	x1, .LC1073
	mov	w2, 6
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_DecSEI
	mov	w20, w0
	ldr	x1, [x19, 240]
	cbz	x1, .L4353
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
.L4353:
	cbz	w20, .L4477
	ldr	x1, .LC1075
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1063
	ldr	x4, [x0]
	cbnz	x4, .L4481
	mov	w0, 0
	b	.L4501
	.p2align 3
.L4494:
	mov	w1, 24
	mov	x0, x22
	bl	BsGet
	mov	w21, w0
	ldr	x0, [x19, 240]
	ubfx	x1, x21, 23, 1
	strb	w1, [x0, 5]
	ldr	x1, [x19, 240]
	ldrsb	w0, [x1, 5]
	cbnz	w0, .L4316
	add	x0, x19, 12288
	ubfx	x4, x21, 16, 6
	ubfx	x2, x21, 6, 10
	mov	w5, 1
	ubfx	x3, x21, 22, 1
	strb	w4, [x0, 2386]
	ubfx	x4, x21, 3, 3
	strb	w5, [x0, 2384]
	strb	w3, [x0, 2385]
	str	w2, [x19, 14680]
	ubfx	x2, x21, 2, 1
	strb	w4, [x0, 2387]
	ubfx	x4, x21, 1, 1
	strb	w2, [x0, 2388]
	and	w2, w21, 1
	strb	w4, [x0, 2389]
	strb	w2, [x0, 2390]
	ldrb	w0, [x1, 2]
	cmp	w0, 20
	beq	.L4505
.L4316:
	ldr	w0, [x1, 72]
	add	w0, w0, 24
	str	w0, [x1, 72]
	ldr	x1, .LC1055
	ldr	x0, [x19, 240]
	ldr	w2, [x19, 68]
	ldrb	w3, [x0, 2]
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x19, 68]
	cmp	w0, 371
	bne	.L4318
	.p2align 2
.L4495:
	ldr	x1, .LC1057
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x19, 68]
	b	.L4318
.L4499:
	mov	x0, x19
	bl	MVC_ClearCurrSlice
	ldr	x0, .LC1063
	ldr	x4, [x0]
	cbnz	x4, .L4478
	mov	w0, -1
	b	.L4500
.L4504:
	ldr	x1, .LC1067
.L4490:
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, .LC1063
	ldr	x4, [x21]
	cbz	x4, .L4476
	add	x2, x29, 64
	ldr	w0, [x19, 120]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x4, [x21]
	cbz	x4, .L4476
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, w20
	b	.L4346
.L4503:
	ldr	x1, .LC1071
	b	.L4490
.L4502:
	ldr	x1, .LC1090
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1063
	ldr	x4, [x0]
	cbz	x4, .L4476
	add	x2, x29, 64
	ldr	w0, [x19, 120]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	mov	w0, w20
	b	.L4346
.L4498:
	ldr	w1, [x19, 20]
	cbz	w1, .L4335
	add	x1, x19, 10768384
	ldr	w3, [x1, 4064]
	cbz	w3, .L4338
	ldrb	w3, [x1, 4060]
	cmp	w3, 1
	beq	.L4339
.L4338:
	add	x0, x0, 2400
	mov	x1, 0
	.p2align 2
.L4342:
	ldr	w4, [x0]
	add	x3, x0, 335872
	cbz	w4, .L4340
	ldrb	w0, [x0, -4]
	cbnz	w0, .L4506
.L4340:
	add	w1, w1, 1
	add	x0, x3, 308
	cmp	w1, 32
	bne	.L4342
	mov	w0, -1
.L4475:
	cmn	w0, #1
	str	w0, [x5, 416]
	beq	.L4335
	cmp	w6, 5
	mov	w0, 1
	cset	w1, eq
	strb	w0, [x2, 2883]
	strb	w0, [x2, 2882]
	strb	w1, [x2, 2881]
	b	.L4335
.L4497:
	strb	w3, [x2, 2883]
	ldr	w1, [x19, 14680]
	str	w1, [x5, 416]
	ldrb	w1, [x0, 2388]
	strb	w1, [x2, 2881]
	ldrb	w1, [x0, 2389]
	strb	w1, [x2, 2882]
	strb	wzr, [x0, 2384]
	b	.L4335
.L4505:
	mov	w0, 5
	cmp	w3, wzr
	csinc	w0, w0, wzr, eq
	strb	w0, [x1, 2]
	ldr	x1, [x19, 240]
	b	.L4316
.L4506:
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 4
	sub	x1, x0, x1
	lsl	x0, x1, 2
	sub	x1, x0, x1
	lsl	x0, x1, 6
	add	x0, x1, x0
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 14692]
	b	.L4475
.L4339:
	ldr	w0, [x1, 4068]
	b	.L4475
	.size	MVC_DecOneNal, .-MVC_DecOneNal
	.align	3
.LC1055:
	.xword	.LC1054
	.align	3
.LC1057:
	.xword	.LC1056
	.align	3
.LC1058:
	.xword	.L4321
	.align	3
.LC1060:
	.xword	.LC1059
	.align	3
.LC1062:
	.xword	.LC1061
	.align	3
.LC1063:
	.xword	g_event_report
	.align	3
.LC1065:
	.xword	.LC1064
	.align	3
.LC1067:
	.xword	.LC1066
	.align	3
.LC1069:
	.xword	.LC1068
	.align	3
.LC1071:
	.xword	.LC1070
	.align	3
.LC1073:
	.xword	.LC1072
	.align	3
.LC1075:
	.xword	.LC1074
	.align	3
.LC1077:
	.xword	.LC1076
	.align	3
.LC1079:
	.xword	.LC1078
	.align	3
.LC1081:
	.xword	.LC1080
	.align	3
.LC1083:
	.xword	.LC1082
	.align	3
.LC1085:
	.xword	.LC1084
	.align	3
.LC1087:
	.xword	.LC1086
	.align	3
.LC1089:
	.xword	.LC1088
	.align	3
.LC1090:
	.xword	.LC757
	.align	3
.LC1092:
	.xword	.LC1091
	.align	3
.LC1094:
	.xword	.LC1093
	.align	3
.LC1095:
	.xword	.LANCHOR1
	.align	3
.LC1097:
	.xword	.LC1096
	.align	3
.LC1099:
	.xword	.LC1098
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_DecodePacket
	.type	MVC_DEC_DecodePacket, %function
MVC_DEC_DecodePacket:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	str	wzr, [x29, 68]
	stp	wzr, wzr, [x29, 60]
	cbz	x19, .L4570
	cbz	x20, .L4571
	ldr	x0, [x19, 224]
	ldrb	w1, [x19, 5]
	ldr	w2, [x0, 8]
	cmp	w1, 1
	ubfiz	w2, w2, 16, 2
	str	w2, [x19, 108]
	ldr	w1, [x0]
	str	w1, [x19, 112]
	ldr	w1, [x0, 4]
	str	w1, [x19, 116]
	strb	wzr, [x19, 10]
	beq	.L4511
	ldr	w1, [x0, 912]
	add	x21, x19, 11161600
	cmp	w1, 1
	beq	.L4572
.L4512:
	mov	x1, x20
	mov	x0, x19
	bl	MVC_ReceivePacket
	ldr	x1, [x19, 240]
	str	x1, [x21, 2392]
.L4514:
	strb	wzr, [x19, 5]
	cbz	w0, .L4515
.L4534:
	mov	w0, 0
.L4563:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4515:
	ldr	x0, [x19, 240]
.L4513:
	str	wzr, [x0, 72]
	add	x21, x19, 872
	mov	x0, x21
	ldr	x1, [x19, 240]
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	mov	w1, 32
	mov	x0, x21
	bl	BsGet
	mov	w20, w0
	and	w3, w0, 31
	ldr	x0, [x19, 240]
	ubfx	x2, x20, 5, 2
	mov	w1, -1
	strb	w3, [x0, 2]
	ldr	x0, [x19, 240]
	strb	w2, [x0, 4]
	ldr	x0, [x19, 240]
	strb	w1, [x0, 5]
	ldr	x0, [x19, 240]
	ldrb	w0, [x0, 2]
	cmp	w0, 20
	beq	.L4573
.L4564:
	mov	w0, 27
	strb	wzr, [x19, 10]
	and	w20, w20, w0
	cmp	w20, 1
	beq	.L4520
.L4521:
	mov	x0, x19
	bl	MVC_FindTrailZeros
	cbnz	w0, .L4574
.L4533:
	ldr	x1, [x19, 240]
	mov	x0, x21
	str	wzr, [x1, 72]
	ldr	x1, [x19, 240]
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	mov	w1, 0
	mov	x0, x19
	bl	MVC_DecOneNal
	cmn	w0, #2
	beq	.L4563
	cbz	w0, .L4534
.L4568:
	ldr	x0, .LC1109
	ldr	x4, [x0]
	cbz	x4, .L4566
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4566:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4572:
	ldr	w0, [x0, 960]
	cmp	w0, 1
	bne	.L4512
	ldr	w0, [x21, 2384]
	cmp	w0, 1
	bne	.L4512
	ldr	x0, [x21, 2392]
	str	x0, [x19, 240]
	str	wzr, [x21, 2384]
	strb	wzr, [x19, 5]
	b	.L4513
	.p2align 3
.L4511:
	ldr	x0, [x19, 240]
	cmp	x0, xzr
	csetm	w0, eq
	b	.L4514
	.p2align 3
.L4573:
	mov	w1, 24
	mov	x0, x21
	bl	BsGet
	ubfx	x2, x0, 23, 1
	ldr	x1, [x19, 240]
	strb	w2, [x1, 5]
	ldr	x2, [x19, 240]
	ldrsb	w1, [x2, 5]
	cbnz	w1, .L4564
	add	x1, x19, 12288
	ubfx	x4, x0, 22, 1
	mov	w6, 1
	ubfx	x3, x0, 6, 10
	ubfx	x5, x0, 2, 1
	cmp	w4, wzr
	strb	w6, [x1, 2384]
	ubfx	x0, x0, 1, 1
	strb	w4, [x1, 2385]
	str	w3, [x19, 14680]
	mov	w3, 5
	strb	w0, [x1, 2389]
	csinc	w0, w3, wzr, eq
	strb	w5, [x1, 2388]
	strb	w0, [x2, 2]
	strb	wzr, [x19, 10]
	.p2align 2
.L4520:
	add	x2, x29, 76
	add	x1, x29, 72
	mov	x0, x19
	bl	MVC_InquireSliceProperty
	cbnz	w0, .L4522
	ldr	w1, [x29, 72]
	ldr	w0, [x19, 128]
	cmp	w1, 1
	csinc	w0, w0, w0, ne
	str	w0, [x19, 128]
	beq	.L4575
.L4523:
	ldr	w0, [x29, 76]
	cmp	w0, 1
	bne	.L4521
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbnz	w0, .L4576
.L4530:
	ldr	w0, [x19, 120]
	bl	FSP_GetFspType
	cbnz	w0, .L4521
	ldr	w0, [x19, 120]
	add	x2, x29, 64
	add	x3, x29, 68
	add	x1, x29, 60
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 224]
	ldr	w2, [x0, 772]
	cmp	w2, 1
	bne	.L4521
	ldr	w0, [x29, 68]
	cmp	w0, wzr
	ble	.L4577
.L4527:
	mov	w1, 1
	mov	w0, -2
	strb	w1, [x19, 5]
	b	.L4563
	.p2align 3
.L4574:
	ldr	x1, .LC1111
	mov	w0, 22
	bl	dprint_vfmw
	b	.L4533
	.p2align 3
.L4522:
	ldr	x1, [x19, 240]
	cbz	x1, .L4568
	ldr	w0, [x19, 120]
	bl	MVC_ReleaseNAL
	str	xzr, [x19, 240]
	b	.L4568
	.p2align 3
.L4575:
	add	x20, x19, 11116544
	ldrb	w0, [x20, 2873]
	cmp	w0, 1
	ldr	w0, [x19, 132]
	beq	.L4578
	add	w0, w0, 2
	str	w0, [x19, 132]
.L4525:
	ldr	w0, [x19, 64]
	cbz	w0, .L4523
	ldr	x3, [x19, 240]
	mov	w2, 12
	ldr	x1, .LC1105
	mov	x0, x21
	add	x1, x1, 432
	str	wzr, [x3, 72]
	bl	BsInit
	mov	w1, 1
	mov	x0, x19
	bl	MVC_DecOneNal
	ldrb	w0, [x20, 2873]
	cmp	w0, 1
	ldr	w0, [x19, 132]
	beq	.L4579
	sub	w0, w0, #2
	str	w0, [x19, 132]
	b	.L4527
.L4578:
	add	w0, w0, 1
	str	w0, [x19, 132]
	b	.L4525
.L4576:
	ldr	x1, .LC1106
	mov	w3, 0
	mov	w2, 13671
	mov	w0, 22
	bl	dprint_vfmw
	b	.L4530
.L4571:
	ldr	x3, .LC1104
	mov	w2, 13553
	ldr	x1, .LC1102
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4563
.L4570:
	ldr	x3, .LC1101
	mov	w2, 13552
	ldr	x1, .LC1102
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4563
.L4579:
	sub	w0, w0, #1
	str	w0, [x19, 132]
	b	.L4527
.L4577:
	ldr	w0, [x29, 64]
	cmp	w0, 32
	bgt	.L4527
	ldr	x0, [x19, 232]
	cbnz	x0, .L4527
	ldr	w3, [x19, 88]
	cbz	w3, .L4521
	ldr	w6, [x19, 12]
	cbz	w6, .L4521
	add	x20, x19, 11161600
	ldr	w7, [x19, 16]
	ldr	w5, [x20, 2400]
	cmp	w7, w5
	beq	.L4521
	ldr	w4, [x20, 2404]
	cmp	w6, w4
	beq	.L4521
	ldr	x1, .LC1108
	mov	w0, w2
	bl	dprint_vfmw
	ldr	w0, [x19, 16]
	ldr	x1, .LC1109
	str	w0, [x20, 2400]
	ldr	x4, [x1]
	ldr	w0, [x19, 12]
	str	w0, [x20, 2404]
	cbz	x4, .L4521
	ldr	w0, [x19, 120]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L4521
	.size	MVC_DEC_DecodePacket, .-MVC_DEC_DecodePacket
	.align	3
.LC1101:
	.xword	.LC61
	.align	3
.LC1102:
	.xword	.LC63
	.align	3
.LC1104:
	.xword	.LC1103
	.align	3
.LC1105:
	.xword	.LANCHOR1
	.align	3
.LC1106:
	.xword	.LC1011
	.align	3
.LC1108:
	.xword	.LC1107
	.align	3
.LC1109:
	.xword	g_event_report
	.align	3
.LC1111:
	.xword	.LC1110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_VDMPostProc
	.type	MVC_DEC_VDMPostProc, %function
MVC_DEC_VDMPostProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L4593
	add	x20, x19, 11157504
	ldr	x2, [x19, 232]
	ldr	x0, [x20, 3320]
	ldrb	w1, [x2, 17]
	strb	w1, [x0, 14]
	ldrb	w1, [x2, 4]
	strb	w1, [x0, 15]
	ldrb	w0, [x19]
	str	w21, [x20, 3380]
	cbz	w0, .L4594
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_StorePicInDpb
	cbnz	w0, .L4595
.L4585:
	mov	w1, -1
	mov	x0, x19
	bl	MVC_FlushDPB
	cbnz	w0, .L4596
.L4586:
	add	x0, x19, 11120640
	strb	wzr, [x19, 4]
	mov	w4, 32
	ldr	w8, [x19, 40]
	mov	w7, 23352
	mov	w6, 2
	strb	w4, [x0, 434]
	add	x4, x0, 256
	strb	wzr, [x0, 432]
	movk	w7, 0x1, lsl 16
	strb	w6, [x0, 433]
	mov	w5, 7
	str	w8, [x0, 444]
	mov	w3, 3
	strb	w5, [x0, 435]
	mov	w2, -1
	str	w7, [x0, 448]
	mov	w1, 262144
	stp	w3, w2, [x4, 200]
	stp	wzr, wzr, [x4, 208]
	str	w1, [x0, 472]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4594:
	mov	x0, x19
	bl	MVC_ClearAllSlice
	mov	x0, x19
	bl	MVC_StorePicInDpb
	mov	w21, w0
	cbnz	w0, .L4597
	mov	w1, 1
	strb	w1, [x19, 4]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4597:
	ldr	x1, [x20, 3320]
	mov	w2, 1
	ldr	w0, [x19, 120]
	ldrsb	w1, [x1, 6]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC1115
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	MVC_ClearCurrPic
	mov	w1, -1
	mov	x0, x19
	bl	MVC_ClearDPB
	str	xzr, [x20, 3320]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4593:
	ldr	x3, .LC1112
	mov	w2, 13800
	ldr	x1, .LC1113
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L4596:
	ldr	x1, .LC1119
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4586
	.p2align 3
.L4595:
	ldr	x1, .LC1117
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4585
	.size	MVC_DEC_VDMPostProc, .-MVC_DEC_VDMPostProc
	.align	3
.LC1112:
	.xword	.LC61
	.align	3
.LC1113:
	.xword	.LC63
	.align	3
.LC1115:
	.xword	.LC1114
	.align	3
.LC1117:
	.xword	.LC1116
	.align	3
.LC1119:
	.xword	.LC1118
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MVC_DEC_GetImageBuffer
	.type	MVC_DEC_GetImageBuffer, %function
MVC_DEC_GetImageBuffer:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L4637
	ldr	w0, [x20, 48]
	cbz	w0, .L4616
	mov	x1, 51200
	sub	w0, w0, #1
	mov	w4, 856
	movk	x1, 0xa9, lsl 16
	add	x21, x20, 11124736
	umaddl	x4, w0, w4, x1
	add	x2, x21, 1192
	add	x4, x20, x4
	.p2align 2
.L4607:
	ldrb	w0, [x2, 2]
	cbnz	w0, .L4602
	cbz	x2, .L4603
	ldr	w0, [x21, 824]
	cbz	w0, .L4603
	ldr	x1, [x21, 440]
	cmp	x1, x2
	ccmp	x1, xzr, 4, eq
	bne	.L4602
	sub	w3, w0, #1
	add	x0, x21, 448
	add	x3, x3, 1388544
	add	x3, x3, 2104
	add	x3, x20, x3, lsl 3
	b	.L4604
	.p2align 3
.L4605:
	ldr	x1, [x0], 8
	cmp	x1, xzr
	ccmp	x1, x2, 0, ne
	beq	.L4602
.L4604:
	cmp	x0, x3
	bne	.L4605
.L4603:
	ldr	w0, [x20, 120]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L4616
	ldr	w0, [x20, 120]
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L4638
.L4635:
	mov	w0, 0
.L4639:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4602:
	add	x2, x2, 856
	cmp	x2, x4
	bne	.L4607
	add	x2, x29, 60
	add	x1, x29, 56
	add	x0, x20, 912
	bl	GetQueueImgNum
	ldr	x1, .LC1123
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC1125
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	cbz	w0, .L4615
	ldr	x19, .LC1129
	mov	w22, 0
	.p2align 2
.L4614:
	uxtw	x1, w22
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 3
	add	x1, x20, x0
	add	x0, x0, 11124736
	add	x1, x1, 11124736
	add	x0, x20, x0
	adds	x0, x0, 1192
	ldrb	w3, [x1, 1194]
	ldrb	w4, [x1, 1197]
	beq	.L4619
	ldr	w1, [x21, 824]
	cbz	w1, .L4619
	ldr	x2, [x21, 440]
	cmp	x0, x2
	ccmp	x2, xzr, 4, eq
	bne	.L4621
	sub	w5, w1, #1
	add	x1, x21, 448
	add	x5, x5, 1388544
	add	x5, x5, 2104
	add	x5, x20, x5, lsl 3
	b	.L4612
	.p2align 3
.L4613:
	ldr	x2, [x1], 8
	cmp	x0, x2
	ccmp	x2, xzr, 4, eq
	bne	.L4621
.L4612:
	cmp	x5, x1
	bne	.L4613
.L4619:
	mov	w5, 1
.L4611:
	mov	w2, w22
	mov	x1, x19
	mov	w0, 0
	add	w22, w22, 1
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	cmp	w0, w22
	bhi	.L4614
.L4615:
	ldp	w2, w3, [x29, 56]
	ldr	x1, .LC1127
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x20, 48]
	ldr	w2, [x21, 828]
	ldp	w3, w1, [x29, 56]
	sub	w0, w0, #2
	sub	w0, w0, w2
	add	w1, w3, w1
	cmp	w1, w0
	bge	.L4635
	ldr	x1, .LC1131
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x20
	bl	MVC_ClearAll
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4616:
	mov	w0, 1
.L4633:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4621:
	mov	w5, 0
	b	.L4611
.L4638:
	ldr	w0, [x20, 120]
	add	x1, x20, 912
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	b	.L4639
.L4637:
	ldr	x3, .LC1120
	mov	w2, 13855
	ldr	x1, .LC1121
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4633
	.size	MVC_DEC_GetImageBuffer, .-MVC_DEC_GetImageBuffer
	.align	3
.LC1120:
	.xword	.LC61
	.align	3
.LC1121:
	.xword	.LC63
	.align	3
.LC1123:
	.xword	.LC1122
	.align	3
.LC1125:
	.xword	.LC1124
	.align	3
.LC1127:
	.xword	.LC1126
	.align	3
.LC1129:
	.xword	.LC1128
	.align	3
.LC1131:
	.xword	.LC1130
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
	.align	3
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
	.type	__FUNCTION__.12083, %object
	.size	__FUNCTION__.12083, 18
__FUNCTION__.12083:
	.string	"MVC_WriteSliceMsg"
	.zero	6
	.type	MVC_SarTable.12373, %object
	.size	MVC_SarTable.12373, 136
MVC_SarTable.12373:
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
	.type	__func__.12607, %object
	.size	__func__.12607, 11
__func__.12607:
	.string	"MVC_DecSEI"
	.zero	5
	.type	__func__.11263, %object
	.size	__func__.11263, 17
__func__.11263:
	.string	"MVC_DirectOutput"
	.zero	7
	.type	__func__.11843, %object
	.size	__func__.11843, 12
__func__.11843:
	.string	"MVC_InitDPB"
	.zero	4
	.type	__FUNCTION__.10983, %object
	.size	__FUNCTION__.10983, 13
__FUNCTION__.10983:
	.string	"MVC_ClearDPB"
	.zero	3
	.type	__func__.12718, %object
	.size	__func__.12718, 17
__func__.12718:
	.string	"MVC_FlushDecoder"
	.zero	7
	.type	__FUNCTION__.10991, %object
	.size	__FUNCTION__.10991, 13
__FUNCTION__.10991:
	.string	"MVC_ClearAll"
	.zero	3
	.type	__FUNCTION__.12845, %object
	.size	__FUNCTION__.12845, 13
__FUNCTION__.12845:
	.string	"MVC_DEC_Init"
	.zero	3
	.type	__func__.11413, %object
	.size	__func__.11413, 18
__func__.11413:
	.string	"MVC_StorePicInDpb"
	.data
	.align	3
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
	.zero	192
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
	.zero	4
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
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"\n\nEND of the bit buffer, copy the first packet!\n\n" )
	.zero	6
.LC2:
	ASCII(.string	"0:phy:0x%x, 1:phy:0x%x; len0:%d len1:%d\n" )
	.zero	7
.LC5:
	ASCII(.string	"0:phy:0x%x, len0:%d\n" )
	.zero	3
.LC7:
	ASCII(.string	"%-50s%50d\n" )
	.zero	5
.LC14:
	ASCII(.string	"MVC_FRAME %d, state=%d, is already output\n" )
	.zero	5
.LC16:
	ASCII(.string	"plfs(fs=%p, eFoState=%d) is null, logic_fs_id = %d\n" )
	.zero	4
.LC18:
	ASCII(.string	"not used MVC_FRAME: (%d,%d)\n" )
	.zero	3
.LC20:
	ASCII(.string	"MVC_FRAME skip: is_used=%d,skip=%d\n" )
	.zero	4
.LC22:
	ASCII(.string	"topfield skip\n" )
	.zero	1
.LC24:
	ASCII(.string	"bottom field skip\n" )
	.zero	5
.LC26:
	ASCII(.string	"err(%d) > out_thr(%d)\n" )
	.zero	1
.LC28:
	ASCII(.string	"exg_pts: %lld <-> %lld\n" )
.LC31:
	ASCII(.string	"stream MVC_FRAME packing type is %d! what can we do?\n" )
	.zero	2
.LC36:
	ASCII(.string	"../../core/syntax/mvc.c" )
.LC38:
	ASCII(.string	"NULL pointer: %s, L%d\n" )
	.zero	1
.LC40:
	ASCII(.string	"framestore %d allocate apc %d\n" )
	.zero	1
.LC42:
	ASCII(.string	"find APC, but logic_fs_id %d abnormal(ref=%d,plfs=%p, pdfs=%p)\n" )
.LC45:
	ASCII(.string	"\n" )
	.zero	6
.LC47:
	ASCII(.string	"pMvcCtx->DPB.fs[%d]: frame_num=%d poc=%d is_reference=%d\n" )
	.zero	6
.LC49:
	ASCII(.string	"pMvcCtx->DPB.fs_ref[%d]: frame_num=%d poc=%d is_reference=%d\n" )
	.zero	2
.LC51:
	ASCII(.string	"pMvcCtx->DPB.fs_ref[%d]: MVC_FRAME.poc=%d \n" )
	.zero	4
.LC57:
	ASCII(.string	"\n VFMW ** release streambuff=%p   bitstream_length=%d\n" )
	.zero	1
.LC59:
	ASCII(.string	"clear curr slice.\n" )
	.zero	5
.LC61:
	ASCII(.string	"pMvcCtx = NULL" )
	.zero	1
.LC63:
	ASCII(.string	"mvc.c,L%d: %s\n" )
	.zero	1
.LC66:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC68:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC70:
	ASCII(.string	"ERROR: FSP_ConfigInstance fail!\n" )
	.zero	7
.LC79:
	ASCII(.string	"for P slice size of list equal 0(1st).\n" )
.LC85:
	ASCII(.string	"for P slice size of list equal 0(2nd).\n" )
.LC87:
	ASCII(.string	"for B slice size of two list all equal 0.\n" )
	.zero	5
.LC90:
	ASCII(.string	"list[%d][%d]: frame_num=%d, poc=%d\n" )
	.zero	4
.LC92:
	ASCII(.string	"init list error.\n" )
	.zero	6
.LC94:
	ASCII(.string	"In one access unit,all non-base view should have the same subsps!\n" )
	.zero	5
.LC96:
	ASCII(.string	"sps but mvc flag %d is wrong\n" )
	.zero	2
.LC108:
	ASCII(.string	"save pic yuv :  structure = %d;  idc = %d\n" )
	.zero	5
.LC110:
	ASCII(.string	"structure = %d pMvcCtx->CurrPic.pic_width_in_mb = %d pMvcCtx->CurrPic.pic_height_in_mb = %d\n" )
	.zero	3
.LC112:
	ASCII(.string	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=%d\n" )
	.zero	1
.LC114:
	ASCII(.string	"logic MVC_FRAME id(=%d): get LogicFs error!\n" )
	.zero	3
.LC116:
	ASCII(.string	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p\n" )
	.zero	3
.LC122:
	ASCII(.string	"fuction return value is null,%s %d unknow error!!\n" )
	.zero	5
.LC124:
	ASCII(.string	"SH: first_mb_in_slice" )
	.zero	2
.LC126:
	ASCII(.string	"MVC_SliceCheck first_mb_in_slice >= MAX_MB_NUM_IN_PIC error.\n" )
	.zero	2
.LC128:
	ASCII(.string	"SH: slice_type" )
	.zero	1
.LC130:
	ASCII(.string	"slice type = %d\n" )
	.zero	7
.LC133:
	ASCII(.string	"slice type = %d, err\n" )
	.zero	2
.LC135:
	ASCII(.string	"slice  pps id = %d\n" )
	.zero	4
.LC137:
	ASCII(.string	"pps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	1
.LC139:
	ASCII(.string	"sps with this pic_parameter_set_id havn't decode\n" )
	.zero	6
.LC141:
	ASCII(.string	"subsps with this seq_parameter_set_id = %d havn't decoded\n" )
	.zero	5
.LC144:
	ASCII(.string	"tmp slice  pps id = %d\n" )
.LC146:
	ASCII(.string	"MVC_PPSSPSCheckTmpId: pps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	3
.LC148:
	ASCII(.string	"MVC_PPSSPSCheckTmpId: seq_parameter_set_id out of range.\n" )
	.zero	6
.LC150:
	ASCII(.string	"MVC_PPSSPSCheckTmpId: sps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	3
.LC152:
	ASCII(.string	"new pic flag = %d\n" )
	.zero	5
.LC154:
	ASCII(.string	"SH: ref_pic_list_reordering_flag_l0" )
	.zero	4
.LC156:
	ASCII(.string	"SH: reordering_of_pic_nums_idc_l0" )
	.zero	6
.LC158:
	ASCII(.string	"reorder idc l0 = %d, g_SeErrFlag=%d\n" )
	.zero	3
.LC160:
	ASCII(.string	"SH: abs_diff_pic_num_minus1_l0" )
	.zero	1
.LC162:
	ASCII(.string	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\n" )
	.zero	7
.LC164:
	ASCII(.string	"SH: long_term_pic_idx_l0" )
	.zero	7
.LC166:
	ASCII(.string	"SH: abs_diff_view_idx_minus1_l0" )
.LC168:
	ASCII(.string	"num of idc l0 exceed\n" )
	.zero	2
.LC170:
	ASCII(.string	"SH: ref_pic_list_reordering_flag_l1" )
	.zero	4
.LC172:
	ASCII(.string	"SH: reordering_of_pic_nums_idc_l1" )
	.zero	6
.LC174:
	ASCII(.string	"reorder idc l1 = %d, g_SeErrFlag=%d\n" )
	.zero	3
.LC176:
	ASCII(.string	"SH: abs_diff_pic_num_minus1_l1" )
	.zero	1
.LC178:
	ASCII(.string	"abs_diff_pic_num_minus1_l1 = %d, g_SeErrFlag=%d\n" )
	.zero	7
.LC180:
	ASCII(.string	"SH: long_term_pic_idx_l1" )
	.zero	7
.LC182:
	ASCII(.string	"SH: abs_diff_view_idx_minus1_l1" )
.LC184:
	ASCII(.string	"num of idc l1 exceed\n" )
	.zero	2
.LC186:
	ASCII(.string	"SH: luma_log2_weight_denom" )
	.zero	5
.LC188:
	ASCII(.string	"SH: chroma_log2_weight_denom" )
	.zero	3
.LC190:
	ASCII(.string	"WP log2 exceed  and err flag = %d\n" )
	.zero	5
.LC192:
	ASCII(.string	"SH: luma_weight_flag_l0" )
.LC194:
	ASCII(.string	"SH: luma_weight_l0" )
	.zero	5
.LC196:
	ASCII(.string	"SH: luma_offset_l0" )
	.zero	5
.LC198:
	ASCII(.string	"SH: chroma_weight_flag_l0" )
	.zero	6
.LC200:
	ASCII(.string	"SH: chroma_weight_l0" )
	.zero	3
.LC202:
	ASCII(.string	"SH: chroma_offset_l0" )
	.zero	3
.LC204:
	ASCII(.string	"SH: luma_weight_flag_l1" )
.LC206:
	ASCII(.string	"SH: luma_weight_l1" )
	.zero	5
.LC208:
	ASCII(.string	"SH: luma_offset_l1" )
	.zero	5
.LC210:
	ASCII(.string	"SH: chroma_weight_flag_l1" )
	.zero	6
.LC212:
	ASCII(.string	"SH: chroma_weight_l1" )
	.zero	3
.LC214:
	ASCII(.string	"SH: chroma_offset_l1" )
	.zero	3
.LC216:
	ASCII(.string	"overflow MVC_MAX_MMCO_LEN\n" )
	.zero	5
.LC218:
	ASCII(.string	"SH: memory_management_control_operation" )
.LC220:
	ASCII(.string	"SH: difference_of_pic_nums_minus1" )
	.zero	6
.LC222:
	ASCII(.string	"SH: long_term_pic_num" )
	.zero	2
.LC224:
	ASCII(.string	"SH: long_term_frame_idx" )
.LC226:
	ASCII(.string	"SH: max_long_term_frame_idx_plus1" )
	.zero	6
.LC228:
	ASCII(.string	"mmco exceed 6\n" )
	.zero	1
.LC230:
	ASCII(.string	"SH: no_output_of_prior_pics_flag" )
	.zero	7
.LC232:
	ASCII(.string	"SH: long_term_reference_flag" )
	.zero	3
.LC234:
	ASCII(.string	"IDR and no_output_of_prior_pics_flag = %d\n" )
	.zero	5
.LC236:
	ASCII(.string	"SH: adaptive_ref_pic_marking_mode_flag" )
	.zero	1
.LC238:
	ASCII(.string	"adaptive_ref_pic_marking_mode_flag = %d\n" )
	.zero	7
.LC240:
	ASCII(.string	"MMCO para would save dec err\n" )
	.zero	2
.LC242:
	ASCII(.string	"mulitislice diff no_out_of_prior_pics_flag, used first.\n" )
	.zero	7
.LC244:
	ASCII(.string	"mulitislice diff long_term_reference_flag, used first.\n" )
.LC246:
	ASCII(.string	"mulitislice diff adaptive_ref_pic_marking_mode_flag, used first.\n" )
	.zero	6
.LC248:
	ASCII(.string	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\n" )
	.zero	1
.LC250:
	ASCII(.string	"SH: pic_parameter_set_id" )
	.zero	7
.LC252:
	ASCII(.string	"pps id:%d in sliceheader err\n" )
	.zero	2
.LC254:
	ASCII(.string	"PPS or SPS of this slice not valid\n" )
	.zero	4
.LC256:
	ASCII(.string	"MVC_PPSSPSCheck failed, PPS or SPS of this slice not valid\n" )
	.zero	4
.LC258:
	ASCII(.string	"SH: frame_num" )
	.zero	2
.LC260:
	ASCII(.string	"IDR NAL but frame_num!=0.\n" )
	.zero	5
.LC262:
	ASCII(.string	"SH: field_pic_flag" )
	.zero	5
.LC264:
	ASCII(.string	"SH: bottom_field_flag" )
	.zero	2
.LC266:
	ASCII(.string	"field first_mb_in_slice bigger than pic size\n" )
	.zero	2
.LC268:
	ASCII(.string	"MVC_FRAME first_mb_in_slice bigger than pic size\n" )
	.zero	6
.LC270:
	ASCII(.string	"SH: idr_pic_id" )
	.zero	1
.LC272:
	ASCII(.string	"idr_pic_id bigger than 65535\n" )
	.zero	2
.LC274:
	ASCII(.string	"SH: pic_order_cnt_lsb" )
	.zero	2
.LC276:
	ASCII(.string	"SH: delta_pic_order_cnt_bottom" )
	.zero	1
.LC278:
	ASCII(.string	"SH: delta_pic_order_cnt[0]" )
	.zero	5
.LC280:
	ASCII(.string	"SH: delta_pic_order_cnt[1]" )
	.zero	5
.LC282:
	ASCII(.string	"SH: redundant_pic_cnt" )
	.zero	2
.LC284:
	ASCII(.string	"redundant pic not support.\n" )
	.zero	4
.LC287:
	ASCII(.string	"first_mb_in_slice in currslice small than prevslice in same pic\n" )
	.zero	7
.LC291:
	ASCII(.string	"SH: direct_spatial_mv_pred_flag" )
.LC293:
	ASCII(.string	"SH: num_ref_idx_override_flag" )
	.zero	2
.LC295:
	ASCII(.string	"SH: num_ref_idx_l0_active_minus1" )
	.zero	7
.LC297:
	ASCII(.string	"SH: num_ref_idx_l1_active_minus1" )
	.zero	7
.LC299:
	ASCII(.string	"MVC_FRAME num_ref_idx_lx_active_minus1 exceed\n" )
	.zero	1
.LC301:
	ASCII(.string	"field num_ref_idx_lx_active_minus1 exceed\n" )
	.zero	5
.LC303:
	ASCII(.string	"reordering para dec err\n" )
	.zero	7
.LC305:
	ASCII(.string	"apply_weights_flag=%d\n" )
	.zero	1
.LC307:
	ASCII(.string	"wpt dec err\n" )
	.zero	3
.LC309:
	ASCII(.string	"mark para dec err\n" )
	.zero	5
.LC311:
	ASCII(.string	"SH: cabac_init_idc" )
	.zero	5
.LC313:
	ASCII(.string	"cabac_init_idc bigger than 3\n" )
	.zero	2
.LC315:
	ASCII(.string	"SH: slice_qp_delta" )
	.zero	5
.LC317:
	ASCII(.string	"SH: disable_deblocking_filter_idc" )
	.zero	6
.LC319:
	ASCII(.string	"disable_deblocking_filter_idc dec err\n" )
	.zero	1
.LC321:
	ASCII(.string	"SH: slice_alpha_c0_offset_div2" )
	.zero	1
.LC323:
	ASCII(.string	"slice_alpha_c0_offset_div2 dec err\n" )
	.zero	4
.LC325:
	ASCII(.string	"SH: slice_beta_offset_div2" )
	.zero	5
.LC327:
	ASCII(.string	"slice_beta_offset_div2 dec err\n" )
.LC329:
	ASCII(.string	"pMvcCtx->pCurrNal->nal_bitoffset = %d; code_len_byte = %d; bitstream_length = %d; pMvcCtx->pCurrNal->nal_trail_zero_bit_num = %d\n" )
	.zero	6
.LC331:
	ASCII(.string	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; bytespos = %x\n" )
	.zero	1
.LC333:
	ASCII(.string	"nal_segment = %d is not expected value\n" )
.LC335:
	ASCII(.string	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\n" )
.LC338:
	ASCII(.string	"   : delta_sl   " )
	.zero	7
.LC342:
	ASCII(.string	"PPS: entropy_coding_mode_flag" )
	.zero	2
.LC344:
	ASCII(.string	"PPS: pic_order_present_flag" )
	.zero	4
.LC346:
	ASCII(.string	"PPS: num_slice_groups_minus1" )
	.zero	3
.LC348:
	ASCII(.string	"MVC_BASELINE stream with FMO, not support.\n" )
	.zero	4
.LC351:
	ASCII(.string	"PPS: num_ref_idx_l0_active_minus1" )
	.zero	6
.LC353:
	ASCII(.string	"num_ref_idx_l0_active_minus1 out of range.\n" )
	.zero	4
.LC355:
	ASCII(.string	"PPS: num_ref_idx_l1_active_minus1" )
	.zero	6
.LC357:
	ASCII(.string	"num_ref_idx_l1_active_minus1 out of range.\n" )
	.zero	4
.LC359:
	ASCII(.string	"PPS: weighted prediction flag" )
	.zero	2
.LC361:
	ASCII(.string	"PPS: weighted_bipred_idc" )
	.zero	7
.LC363:
	ASCII(.string	"weighted_bipred_idc out of range\n" )
	.zero	6
.LC365:
	ASCII(.string	"PPS: pic_init_qp_minus26" )
	.zero	7
.LC367:
	ASCII(.string	"PPS: pic_init_qs_minus26" )
	.zero	7
.LC369:
	ASCII(.string	"PPS: chroma_qp_index_offset" )
	.zero	4
.LC371:
	ASCII(.string	"PPS: deblocking_filter_control_present_flag" )
	.zero	4
.LC373:
	ASCII(.string	"PPS: constrained_intra_pred_flag" )
	.zero	7
.LC375:
	ASCII(.string	"PPS: redundant_pic_cnt_present_flag" )
	.zero	4
.LC377:
	ASCII(.string	"redundant pic not support when find redundant slice later, exit\n" )
	.zero	7
.LC379:
	ASCII(.string	"PPS: transform_8x8_mode_flag" )
	.zero	3
.LC381:
	ASCII(.string	"PPS: pic_scaling_matrix_present_flag" )
	.zero	3
.LC383:
	ASCII(.string	"PPS: second_chroma_qp_index_offset" )
	.zero	5
.LC385:
	ASCII(.string	"SPS: seq_scaling_list_present_flag" )
	.zero	5
.LC388:
	ASCII(.string	"PPS: pic_scaling_list_present_flag" )
	.zero	5
.LC390:
	ASCII(.string	"second_chroma_qp_index_offset out of range.\n" )
	.zero	3
.LC394:
	ASCII(.string	"PPS: pic_parameter_set_id" )
	.zero	6
.LC396:
	ASCII(.string	"pic_parameter_set_id(%d) out of range.\n" )
.LC399:
	ASCII(.string	"PPS: seq_parameter_set_id" )
	.zero	6
.LC401:
	ASCII(.string	"seq_parameter_set_id out of range.\n" )
	.zero	4
.LC404:
	ASCII(.string	"PPS decode error line: %d.\n" )
	.zero	4
.LC407:
	ASCII(.string	"VUI: aspect_ratio_info_present_flag" )
	.zero	4
.LC409:
	ASCII(.string	"VUI: aspect_ratio_idc" )
	.zero	2
.LC411:
	ASCII(.string	"VUI: sar_width" )
	.zero	1
.LC413:
	ASCII(.string	"VUI: sar_height" )
.LC415:
	ASCII(.string	"VUI: overscan_info_present_flag" )
.LC417:
	ASCII(.string	"VUI: overscan_appropriate_flag" )
	.zero	1
.LC419:
	ASCII(.string	"VUI: video_signal_type_present_flag" )
	.zero	4
.LC421:
	ASCII(.string	"VUI: video_format" )
	.zero	6
.LC423:
	ASCII(.string	"VUI: video_full_range_flag" )
	.zero	5
.LC425:
	ASCII(.string	"VUI: color_description_present_flag" )
	.zero	4
.LC427:
	ASCII(.string	"VUI: colour_primaries" )
	.zero	2
.LC429:
	ASCII(.string	"VUI: transfer_characteristics" )
	.zero	2
.LC431:
	ASCII(.string	"VUI: matrix_coefficients" )
	.zero	7
.LC433:
	ASCII(.string	"VUI: chroma_loc_info_present_flag" )
	.zero	6
.LC435:
	ASCII(.string	"VUI: chroma_sample_loc_type_top_field" )
	.zero	2
.LC437:
	ASCII(.string	"VUI: chroma_sample_loc_type_bottom_field" )
	.zero	7
.LC439:
	ASCII(.string	"VUI: timing_info_present_flag" )
	.zero	2
.LC441:
	ASCII(.string	"VUI: num_units_in_tick" )
	.zero	1
.LC443:
	ASCII(.string	"VUI: time_scale" )
.LC445:
	ASCII(.string	"VUI: fixed_frame_rate_flag" )
	.zero	5
.LC447:
	ASCII(.string	"VUI: nal_hrd_parameters_present_flag" )
	.zero	3
.LC449:
	ASCII(.string	"VUI: cpb_cnt_minus1" )
	.zero	4
.LC451:
	ASCII(.string	"VUI: bit_rate_scale" )
	.zero	4
.LC453:
	ASCII(.string	"VUI: cpb_size_scale" )
	.zero	4
.LC455:
	ASCII(.string	"hrd->cpb_cnt_minus1 out of range\n" )
	.zero	6
.LC457:
	ASCII(.string	"VUI: bit_rate_value_minus1" )
	.zero	5
.LC459:
	ASCII(.string	"VUI: cpb_size_value_minus1" )
	.zero	5
.LC461:
	ASCII(.string	"VUI: cbr_flag" )
	.zero	2
.LC463:
	ASCII(.string	"VUI: initial_cpb_removal_delay_length_minus1" )
	.zero	3
.LC465:
	ASCII(.string	"VUI: cpb_removal_delay_length_minus1" )
	.zero	3
.LC467:
	ASCII(.string	"VUI: dpb_output_delay_length_minus1" )
	.zero	4
.LC469:
	ASCII(.string	"VUI: time_offset_length" )
.LC471:
	ASCII(.string	"VUI: vcl_hrd_parameters_present_flag" )
	.zero	3
.LC473:
	ASCII(.string	"VUI: low_delay_hrd_flag" )
.LC475:
	ASCII(.string	"VUI: pic_struct_present_flag" )
	.zero	3
.LC477:
	ASCII(.string	"VUI: bitstream_restriction_flag" )
.LC479:
	ASCII(.string	"VUI: motion_vectors_over_pic_boundaries_flag" )
	.zero	3
.LC481:
	ASCII(.string	"VUI: max_bytes_per_pic_denom" )
	.zero	3
.LC483:
	ASCII(.string	"VUI: max_bits_per_mb_denom" )
	.zero	5
.LC485:
	ASCII(.string	"VUI: log2_max_mv_length_horizontal" )
	.zero	5
.LC487:
	ASCII(.string	"VUI: log2_max_mv_length_vertical" )
	.zero	7
.LC489:
	ASCII(.string	"VUI: num_reorder_frames" )
.LC491:
	ASCII(.string	"VUI: max_dec_frame_buffering" )
	.zero	3
.LC496:
	ASCII(.string	"dar=%d, final_dar=%d\n" )
	.zero	2
.LC502:
	ASCII(.string	"SPS: chroma_format_idc" )
	.zero	1
.LC504:
	ASCII(.string	"pSPS->chroma_format_idc out of range.\n" )
	.zero	1
.LC506:
	ASCII(.string	"SPS: bit_depth_luma_minus8" )
	.zero	5
.LC508:
	ASCII(.string	"bit_depth_luma_minus8 not equal 0.\n" )
	.zero	4
.LC510:
	ASCII(.string	"SPS: bit_depth_chroma_minus8" )
	.zero	3
.LC512:
	ASCII(.string	"bit_depth_chroma_minus8 not equal 0.\n" )
	.zero	2
.LC514:
	ASCII(.string	"SPS: qpprime_y_zero_trans_bypass_flag" )
	.zero	2
.LC516:
	ASCII(.string	"qpprime_y_zero_trans_bypass_flag not equal 0.\n" )
	.zero	1
.LC518:
	ASCII(.string	"SPS: seq_scaling_matrix_present_flag" )
	.zero	3
.LC522:
	ASCII(.string	"SPS: log2_max_frame_num_minus4" )
	.zero	1
.LC524:
	ASCII(.string	"pSPS->log2_max_frame_num_minus4 out of range.\n" )
	.zero	1
.LC526:
	ASCII(.string	"SPS: pic_order_cnt_type" )
.LC528:
	ASCII(.string	"pSPS->pic_order_cnt_type out of range.\n" )
.LC530:
	ASCII(.string	"SPS: log2_max_pic_order_cnt_lsb_minus4" )
	.zero	1
.LC532:
	ASCII(.string	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of range.\n" )
	.zero	1
.LC534:
	ASCII(.string	"SPS: delta_pic_order_always_zero_flag" )
	.zero	2
.LC536:
	ASCII(.string	"SPS: offset_for_non_ref_pic" )
	.zero	4
.LC538:
	ASCII(.string	"SPS: offset_for_top_to_bottom_field" )
	.zero	4
.LC540:
	ASCII(.string	"SPS: num_ref_frames_in_pic_order_cnt_cycle" )
	.zero	5
.LC542:
	ASCII(.string	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of range.\n" )
	.zero	5
.LC544:
	ASCII(.string	"SPS: offset_for_ref_frame[i]" )
	.zero	3
.LC546:
	ASCII(.string	"SPS: gaps_in_frame_num_value_allowed_flag" )
	.zero	6
.LC548:
	ASCII(.string	"SPS: pic_width_in_mbs_minus1" )
	.zero	3
.LC550:
	ASCII(.string	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\n" )
	.zero	6
.LC552:
	ASCII(.string	"SPS: pic_height_in_map_units_minus1" )
	.zero	4
.LC554:
	ASCII(.string	"SPS: frame_mbs_only_flag" )
	.zero	7
.LC556:
	ASCII(.string	"pSPS->pic_height_in_map_units_minus1 out of range.\n" )
	.zero	4
.LC558:
	ASCII(.string	"pic size too large.\n" )
	.zero	3
.LC561:
	ASCII(.string	"level_idc %d not support.\n" )
	.zero	5
.LC563:
	ASCII(.string	"dpb size according level : %d\n" )
	.zero	1
.LC565:
	ASCII(.string	"pSPS->num_ref_frames(%d) > DPB size(%d), try to select the reasonable one.\n" )
	.zero	4
.LC567:
	ASCII(.string	"SPS: direct_8x8_inference_flag" )
	.zero	1
.LC569:
	ASCII(.string	"SPS: frame_cropping_flag" )
	.zero	7
.LC571:
	ASCII(.string	"SPS: frame_cropping_rect_left_offset" )
	.zero	3
.LC573:
	ASCII(.string	"SPS: frame_cropping_rect_right_offset" )
	.zero	2
.LC575:
	ASCII(.string	"SPS: frame_cropping_rect_top_offset" )
	.zero	4
.LC577:
	ASCII(.string	"SPS: frame_cropping_rect_bottom_offset" )
	.zero	1
.LC579:
	ASCII(.string	"SPS: vui_parameters_present_flag" )
	.zero	7
.LC581:
	ASCII(.string	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\n" )
	.zero	2
.LC584:
	ASCII(.string	"SPS: num_ref_frames" )
	.zero	4
.LC586:
	ASCII(.string	"SPS: mb_adaptive_frame_field_flag" )
	.zero	6
.LC588:
	ASCII(.string	"SPS: profile_idc" )
	.zero	7
.LC590:
	ASCII(.string	"SPS: constrained_set0_flag" )
	.zero	5
.LC592:
	ASCII(.string	"SPS: constrained_set1_flag" )
	.zero	5
.LC594:
	ASCII(.string	"SPS: constrained_set2_flag" )
	.zero	5
.LC596:
	ASCII(.string	"SPS: constrained_set3_flag" )
	.zero	5
.LC598:
	ASCII(.string	"SPS: constrained_set4_flag" )
	.zero	5
.LC600:
	ASCII(.string	"SPS: constrained_set5_flag" )
	.zero	5
.LC602:
	ASCII(.string	"SPS: reserved_zero_2bits" )
	.zero	7
.LC604:
	ASCII(.string	"SPS: level_idc" )
	.zero	1
.LC606:
	ASCII(.string	"SPS: seq_parameter_set_id" )
	.zero	6
.LC610:
	ASCII(.string	"MVC_BASELINE stream, try to decode, exit when FMO occurred.\n" )
	.zero	3
.LC612:
	ASCII(.string	"MVC_EXTENDED stream, try to decode, exit when datapartition occurred.\n" )
	.zero	1
.LC614:
	ASCII(.string	"others High profile stream, try to decode, exit when high profile not support occurred.\n" )
	.zero	7
.LC616:
	ASCII(.string	"profile_idc = %5d error, try to decode as main profile.\n" )
	.zero	7
.LC618:
	ASCII(.string	"level_idc = %5d error, try to decode as level_idc %d.\n" )
	.zero	1
.LC621:
	ASCII(.string	"Line %d: SPS[%d] decode error.\n" )
.LC627:
	ASCII(.string	"SUBSPS: num_views_minus1" )
	.zero	7
.LC629:
	ASCII(.string	"pSubsps->num_views_minus1(%d) out of range.\n" )
	.zero	3
.LC631:
	ASCII(.string	"SUBSPS: view_id[]" )
	.zero	6
.LC633:
	ASCII(.string	"SUBSPS: num_anchor_refs_l0[]" )
	.zero	3
.LC635:
	ASCII(.string	"SUBSPS: num_anchor_refs_l1[]" )
	.zero	3
.LC637:
	ASCII(.string	"pSubsps->num_anchor_refs_l0(%d) out of range.\n" )
	.zero	1
.LC639:
	ASCII(.string	"SUBSPS: anchor_ref_l0[][]" )
	.zero	6
.LC641:
	ASCII(.string	"pSubsps->num_anchor_refs_l1(%d) out of range.\n" )
	.zero	1
.LC643:
	ASCII(.string	"SUBSPS: anchor_ref_l1[][]" )
	.zero	6
.LC645:
	ASCII(.string	"SUBSPS: num_level_values_signalled_minus1" )
	.zero	6
.LC647:
	ASCII(.string	"SUBSPS: num_non_anchor_refs_l0[]" )
	.zero	7
.LC649:
	ASCII(.string	"SUBSPS: num_non_anchor_refs_l1[]" )
	.zero	7
.LC651:
	ASCII(.string	"pSubsps->num_non_anchor_refs_l0(%d) out of range.\n" )
	.zero	5
.LC653:
	ASCII(.string	"SUBSPS: non_anchor_ref_l0[][]" )
	.zero	2
.LC655:
	ASCII(.string	"pSubsps->num_non_anchor_refs_l1(%d) out of range.\n" )
	.zero	5
.LC657:
	ASCII(.string	"SUBSPS: non_anchor_ref_l1[][]" )
	.zero	2
.LC659:
	ASCII(.string	"num_level(%d) out of range.\n" )
	.zero	3
.LC661:
	ASCII(.string	"SUBSPS: level_idc[]" )
	.zero	4
.LC663:
	ASCII(.string	"SUBSPS: num_applicable_ops_minus1" )
	.zero	6
.LC665:
	ASCII(.string	"num_ops(%d) out of range.\n" )
	.zero	5
.LC667:
	ASCII(.string	"SUBSPS: applicable_op_temporal_id[][]" )
	.zero	2
.LC669:
	ASCII(.string	"SUBSPS: applicable_op_num_target_views_minus1[][]" )
	.zero	6
.LC671:
	ASCII(.string	"SUBSPS: applicable_op_num_views_minus1" )
	.zero	1
.LC673:
	ASCII(.string	"applicable_op_num_target_views(%d) out of range.\n" )
	.zero	6
.LC675:
	ASCII(.string	"SUBSPS: applicable_op_target_view_id[][][]" )
	.zero	5
.LC677:
	ASCII(.string	"pSubsps->applicable_op_num_views_minus1(%d) out of range.\n" )
	.zero	5
.LC679:
	ASCII(.string	"MVC VUI: vui_mvc_num_ops_minus1" )
.LC681:
	ASCII(.string	"vui_mvc_num_ops_minus1 %d out of range\n" )
.LC683:
	ASCII(.string	"MVC VUI: vui_mvc_temporal_id[]" )
	.zero	1
.LC685:
	ASCII(.string	"SUBSPS VUI: vui_mvc_num_target_output_views_minus1[]" )
	.zero	3
.LC687:
	ASCII(.string	"vui_mvc_num_target_output_views_minus1 %d out of range\n" )
.LC689:
	ASCII(.string	"MVC VUI: vui_mvc_timing_info_present_flag" )
	.zero	6
.LC691:
	ASCII(.string	"MVC VUI: vui_mvc_view_id[][]" )
	.zero	3
.LC693:
	ASCII(.string	"MVC VUI: vui_mvc_num_units_in_tick" )
	.zero	5
.LC695:
	ASCII(.string	"MVC VUI: vui_mvc_time_scale[]" )
	.zero	2
.LC697:
	ASCII(.string	"MVC VUI: vui_mvc_fixed_frame_rate_flag" )
	.zero	1
.LC699:
	ASCII(.string	"MVC VUI: vui_mvc_nal_hrd_parameters_present_flag[]" )
	.zero	5
.LC701:
	ASCII(.string	"MVC VUI: cpb_cnt_minus1" )
.LC703:
	ASCII(.string	"MVC VUI: bit_rate_scale" )
.LC705:
	ASCII(.string	"MVC VUI: cpb_size_scale" )
.LC708:
	ASCII(.string	"MVC VUI: bit_rate_value_minus1" )
	.zero	1
.LC710:
	ASCII(.string	"MVC VUI: cpb_size_value_minus1" )
	.zero	1
.LC712:
	ASCII(.string	"MVC VUI: cbr_flag" )
	.zero	6
.LC714:
	ASCII(.string	"MVC VUI: initial_cpb_removal_delay_length_minus1" )
	.zero	7
.LC716:
	ASCII(.string	"MVC VUI: cpb_removal_delay_length_minus1" )
	.zero	7
.LC718:
	ASCII(.string	"MVC VUI: dpb_output_delay_length_minus1" )
.LC720:
	ASCII(.string	"MVC VUI: time_offset_length" )
	.zero	4
.LC722:
	ASCII(.string	"MVC VUI: vui_mvc_vcl_hrd_parameters_present_flag[]" )
	.zero	5
.LC724:
	ASCII(.string	"MVC VUI: vui_mvc_low_delay_hrd_flag[]" )
	.zero	2
.LC726:
	ASCII(.string	"MVC VUI: vui_mvc_pic_struct_present_flag[]" )
	.zero	5
.LC728:
	ASCII(.string	"SUBSPS: profile_idc" )
	.zero	4
.LC730:
	ASCII(.string	"SUBSPS: constrained_set0_flag" )
	.zero	2
.LC732:
	ASCII(.string	"SUBSPS: constrained_set1_flag" )
	.zero	2
.LC734:
	ASCII(.string	"SUBSPS: constrained_set2_flag" )
	.zero	2
.LC736:
	ASCII(.string	"SUBSPS: constrained_set3_flag" )
	.zero	2
.LC738:
	ASCII(.string	"SUBSPS: constrained_set4_flag" )
	.zero	2
.LC740:
	ASCII(.string	"SUBSPS: constrained_set5_flag" )
	.zero	2
.LC742:
	ASCII(.string	"SUBSPS: reserved_zero_2bits" )
	.zero	4
.LC744:
	ASCII(.string	"SUBSPS: level_idc" )
	.zero	6
.LC746:
	ASCII(.string	"SUBSPS: seq_parameter_set_id" )
	.zero	3
.LC753:
	ASCII(.string	"profile_idc = %5d error\n" )
	.zero	7
.LC755:
	ASCII(.string	"level_idc = %5d error, try to decode as level_idc 41.\n" )
	.zero	1
.LC757:
	ASCII(.string	"SUBSPS decode error.\n" )
	.zero	2
.LC759:
	ASCII(.string	"SUBSPS: bit_equal_to_one" )
	.zero	7
.LC761:
	ASCII(.string	"SUBSPS Mvc Ext decode error.\n" )
	.zero	2
.LC763:
	ASCII(.string	"SUBSPS: mvc_vui_parameters_present_flag" )
.LC765:
	ASCII(.string	"SUBSPS Mvc Vui Ext decode error.\n" )
	.zero	6
.LC767:
	ASCII(.string	"SEI: frame_packing_arrangement_id" )
	.zero	6
.LC769:
	ASCII(.string	"SEI: frame_packing_arrangement_cancel_flag" )
	.zero	5
.LC771:
	ASCII(.string	"SEI: frame_packing_arrangement_type" )
	.zero	4
.LC773:
	ASCII(.string	"SEI: quincunx_sampling_flag" )
	.zero	4
.LC775:
	ASCII(.string	"SEI: content_interpretation_type" )
	.zero	7
.LC777:
	ASCII(.string	"SEI: spatial_flipping_flag" )
	.zero	5
.LC779:
	ASCII(.string	"SEI: frame0_flipped_flag" )
	.zero	7
.LC781:
	ASCII(.string	"SEI: field_views_flag" )
	.zero	2
.LC783:
	ASCII(.string	"SEI: current_frame_is_frame0_flag" )
	.zero	6
.LC785:
	ASCII(.string	"SEI: frame0_self_contained_flag" )
.LC787:
	ASCII(.string	"SEI: frame1_self_contained_flag" )
.LC789:
	ASCII(.string	"SEI: frame0_grid_position_x" )
	.zero	4
.LC791:
	ASCII(.string	"SEI: frame0_grid_position_y" )
	.zero	4
.LC793:
	ASCII(.string	"SEI: frame1_grid_position_x" )
	.zero	4
.LC795:
	ASCII(.string	"SEI: frame1_grid_position_y" )
	.zero	4
.LC797:
	ASCII(.string	"SEI: frame_packing_arrangement_reserved_byte" )
	.zero	3
.LC799:
	ASCII(.string	"SEI: frame_packing_arrangement_repetition_period" )
	.zero	7
.LC801:
	ASCII(.string	"SEI: frame_packing_arrangement_extension_flag" )
	.zero	2
.LC803:
	ASCII(.string	"DecPicTimingSEI but SPS is invalid.\n" )
	.zero	3
.LC805:
	ASCII(.string	"SEI: cpb_removal_delay" )
	.zero	1
.LC807:
	ASCII(.string	"SEI: dpb_output_delay" )
	.zero	2
.LC809:
	ASCII(.string	"pic_struct" )
	.zero	5
.LC811:
	ASCII(.string	"SEI nal dec payload type err\n" )
	.zero	2
.LC813:
	ASCII(.string	"SEI nal dec payloadSize err\n" )
	.zero	3
.LC816:
	ASCII(.string	"MVC_SEI_BUFFERING_PERIOD,offset = %d,payload_size = %d \n" )
	.zero	7
.LC819:
	ASCII(.string	"MVC_PassBytes err [%s][%d]\n" )
	.zero	4
.LC821:
	ASCII(.string	"MVC_SEI_PIC_TIMING,offset = %d,payload_size = %d \n" )
	.zero	5
.LC823:
	ASCII(.string	"MVC_SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d \n" )
	.zero	2
.LC825:
	ASCII(.string	"MVC_SEI_FILLER_PAYLOAD,offset = %d,payload_size = %d \n" )
	.zero	1
.LC827:
	ASCII(.string	"MVC_SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d, payload_size = %d \n" )
	.zero	7
.LC829:
	ASCII(.string	"MVC_SEI_USER_DATA_UNREGISTERED, offset = %d, payload_size = %d \n" )
	.zero	7
.LC831:
	ASCII(.string	"SEI: itu_t_t35_country_code" )
	.zero	4
.LC833:
	ASCII(.string	"SEI: itu_t_t35_country_code_extension_byte" )
	.zero	5
.LC835:
	ASCII(.string	"SEI: itu_t_t35_provider_code" )
	.zero	3
.LC838:
	ASCII(.string	"cann't dec usrdata\n" )
	.zero	4
.LC840:
	ASCII(.string	"MVC_SEI_RECOVERY_POINT,offset = %d,payload_size = %d \n" )
	.zero	1
.LC842:
	ASCII(.string	"MVC_SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d,payload_size = %d \n" )
	.zero	1
.LC844:
	ASCII(.string	"MVC_SEI_SPARE_PIC,offset = %d,payload_size = %d \n" )
	.zero	6
.LC846:
	ASCII(.string	"MVC_SEI_SCENE_INFO,offset = %d,payload_size = %d \n" )
	.zero	5
.LC848:
	ASCII(.string	"MVC_SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d \n" )
	.zero	3
.LC850:
	ASCII(.string	"MVC_SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	2
.LC852:
	ASCII(.string	"MVC_SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
.LC854:
	ASCII(.string	"MVC_SEI_FULL_FRAME_FREEZE,offset = %d,payload_size = %d \n" )
	.zero	6
.LC856:
	ASCII(.string	"MVC_SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,payload_size = %d \n" )
	.zero	6
.LC858:
	ASCII(.string	"MVC_SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_size = %d \n" )
	.zero	4
.LC860:
	ASCII(.string	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset = %d,payload_size = %d \n" )
	.zero	3
.LC862:
	ASCII(.string	"MVC_SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset = %d,payload_size = %d \n" )
	.zero	5
.LC864:
	ASCII(.string	"MVC_SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset = %d,payload_size = %d \n" )
	.zero	5
.LC866:
	ASCII(.string	"MVC_SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	5
.LC868:
	ASCII(.string	"MVC_SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset = %d,payload_size = %d \n" )
	.zero	3
.LC870:
	ASCII(.string	"MVC_SEI_STEREO_VIDEO_INFO,offset = %d,payload_size = %d \n" )
	.zero	6
.LC872:
	ASCII(.string	"too much usrdat, cann't dec SEI\n" )
	.zero	7
.LC875:
	ASCII(.string	"pNewPicDetector = NULL" )
	.zero	1
.LC878:
	ASCII(.string	"pu8 = NULL" )
	.zero	5
.LC881:
	ASCII(.string	"\n mvc the stream is error,len:%d\n" )
	.zero	6
.LC886:
	ASCII(.string	"\nSlice nal or IDR nal = %d\n" )
	.zero	4
.LC888:
	ASCII(.string	"sliceheader dec err\n" )
	.zero	3
.LC891:
	ASCII(.string	"MVC_InquireSliceProperty mvc flag %d is wrong\n" )
	.zero	1
.LC893:
	ASCII(.string	"mvc.c,L%d: pMvcCtx is NULL\n" )
	.zero	4
.LC895:
	ASCII(.string	"MvcDec destroy\n" )
.LC899:
	ASCII(.string	"PicID is out of range" )
	.zero	2
.LC901:
	ASCII(.string	"MVC recycle image\n" )
	.zero	5
.LC903:
	ASCII(.string	"pH264Ctx is %#x, pFrameStore is %#x\n" )
	.zero	3
.LC905:
	ASCII(.string	"line: %d, pstLogicFsImage is NULL\n" )
	.zero	5
.LC907:
	ASCII(.string	"InsertVO err:%d, MVC_ClearAll\n" )
	.zero	1
.LC909:
	ASCII(.string	"mvc.c line %d: MVC_FRAME para err(ret=%d), recycle image self\n" )
	.zero	1
.LC913:
	ASCII(.string	"[%s][%d] MVC_OutputFrmToVO return %d !\n" )
.LC918:
	ASCII(.string	"[%s][%d] MVC_OutputFrmToVO return %d\n" )
	.zero	2
.LC922:
	ASCII(.string	"%s %d MVC_OK != MVC_FlushDPB!!\n" )
.LC924:
	ASCII(.string	"%s %d MVC_OK != MVC_InitDPB!!\n" )
	.zero	1
.LC926:
	ASCII(.string	"----------------- MVC_IMODE -> %d ------------------\n" )
	.zero	2
.LC928:
	ASCII(.string	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\n" )
.LC930:
	ASCII(.string	"***** VDM start, TotalPicNum=%d, pMvcCtx->CurrPic.structure=%d.\n" )
	.zero	7
.LC935:
	ASCII(.string	"MVC_DecVDM fail [%s][%d]\n" )
	.zero	6
.LC937:
	ASCII(.string	"\n receive streambuff=%p; phy_addr=0x%x; bitstream_length=%d\n" )
	.zero	3
.LC939:
	ASCII(.string	"nal_releaMVC_SE_ERR\n" )
	.zero	3
.LC941:
	ASCII(.string	"cann't find slot for current nal\n" )
	.zero	6
.LC944:
	ASCII(.string	"receive a zero packet\n" )
	.zero	1
.LC946:
	ASCII(.string	"clear all dec para\n" )
	.zero	4
.LC952:
	ASCII(.string	"line %d, get APC error, ret %d\n" )
.LC954:
	ASCII(.string	"InserFrmInDPB: cur pic struct = %d!\n" )
	.zero	3
.LC956:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC958:
	ASCII(.string	"FS_ALLOC_ERR, MVC_ClearAll\n" )
	.zero	4
.LC961:
	ASCII(.string	"Can not new logic fs! MVC_ClearAll\n" )
	.zero	4
.LC963:
	ASCII(.string	"mvc.c,L%d: pMvcCtx or pstExtraData is NULL\n" )
	.zero	4
.LC967:
	ASCII(.string	"%s %d NULL== pMvcCtx->SPS || NULL == pMvcCtx->PPS || NULL == pMvcCtx->DecSlicePara!!\n" )
	.zero	2
.LC969:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC971:
	ASCII(.string	"CurrPic.state is 'MVC_EMPTY'\n" )
	.zero	2
.LC973:
	ASCII(.string	"MVC_StorePicInDpb return(%d) from L%d\n" )
	.zero	1
.LC975:
	ASCII(.string	"Is IDR, but init DPB failed!\n" )
	.zero	2
.LC977:
	ASCII(.string	"Is IDR, but FlushDPB failed!\n" )
	.zero	2
.LC979:
	ASCII(.string	"MVC_DirectOutput mode\n" )
	.zero	1
.LC981:
	ASCII(.string	"line %d, REPORT_IFRAME_ERR\n" )
	.zero	4
.LC984:
	ASCII(.string	"line %d, return %d\n" )
	.zero	4
.LC986:
	ASCII(.string	"err(%d) > ref_thr(%d)\n" )
	.zero	1
.LC988:
	ASCII(.string	"MVC_Marking return %d\n" )
	.zero	1
.LC990:
	ASCII(.string	"line %d: pMvcCtx->DPB.size = %d, ref %d, ltref %d\n" )
	.zero	5
.LC992:
	ASCII(.string	"line %d, MVC_GetMinPOC failed\n" )
	.zero	1
.LC995:
	ASCII(.string	"%s: pos(%d) = pre_pos, force return.\n" )
	.zero	2
.LC997:
	ASCII(.string	"GAP found while DPB is MVC_EMPTY!\n" )
	.zero	5
.LC999:
	ASCII(.string	"MVC_FRAME num gap try to fill it \n" )
	.zero	5
.LC1001:
	ASCII(.string	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\n" )
	.zero	7
.LC1003:
	ASCII(.string	"cann't allocate MVC_FRAME store when gap find\n" )
	.zero	1
.LC1005:
	ASCII(.string	"allocate MVC_FRAME store when gap find\n" )
.LC1007:
	ASCII(.string	"line %d: store gap pic err, ret=%d\n" )
	.zero	4
.LC1011:
	ASCII(.string	"line %d: flush dpb return %d\n" )
	.zero	2
.LC1013:
	ASCII(.string	"line %d: init dpb return %d\n" )
	.zero	3
.LC1015:
	ASCII(.string	"resolution error, the CAP_LEVEL_USER_DEFINE_WITH_OPTION channel with s32ReRangeEn == 0 can't support such bitstream.\n" )
	.zero	2
.LC1017:
	ASCII(.string	"s32MaxRefFrameNum < pMvcCtx->DPB.size, the CAP_LEVEL_USER_DEFINE_WITH_OPTION channel can't support such bitstream.\n" )
	.zero	4
.LC1019:
	ASCII(.string	"mem arrange err, MVC_ClearAll\n" )
	.zero	1
.LC1021:
	ASCII(.string	"get back frm\n" )
	.zero	2
.LC1023:
	ASCII(.string	"line %d: MVC_FRAME gap(=%d) > dpb size(=%d)\n" )
	.zero	3
.LC1025:
	ASCII(.string	"MVC_FRAME num gap don't allowed but gap find\n" )
	.zero	2
.LC1027:
	ASCII(.string	"line %d: frame num(%d/%d) find gap in NON-I slice but here gap is not allowed\n" )
	.zero	1
.LC1029:
	ASCII(.string	"line %d: dec gap failed\n" )
	.zero	7
.LC1031:
	ASCII(.string	"line %d: alloc framestore failed\n" )
	.zero	6
.LC1033:
	ASCII(.string	"dec_pts: %lld\n" )
	.zero	1
.LC1035:
	ASCII(.string	"dec_usertag: %lld\n" )
	.zero	5
.LC1037:
	ASCII(.string	"line %d: CurrPic.frame_store is NULL\n" )
	.zero	2
.LC1042:
	ASCII(.string	"Start Reason: SliceParaNum, MaxBytesReceived = %d, %d(thr=%d)\n" )
	.zero	1
.LC1044:
	ASCII(.string	"Too many slice or bitstream, err!\n" )
	.zero	5
.LC1046:
	ASCII(.string	"Start Reason: new_pic_flag\n" )
	.zero	4
.LC1048:
	ASCII(.string	"init pic err, find next recover point or next valid sps, pps, or exit\n" )
	.zero	1
.LC1050:
	ASCII(.string	"MVC_DecList error, ret=%d\n" )
	.zero	5
.LC1052:
	ASCII(.string	"dec list err.\n" )
	.zero	1
.LC1054:
	ASCII(.string	"pMvcCtx->TotalNal = %d, type:%d\n" )
	.zero	7
.LC1056:
	ASCII(.string	"stop i want\n" )
	.zero	3
.LC1059:
	ASCII(.string	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=%d\n" )
	.zero	1
.LC1061:
	ASCII(.string	"*******TotalPicNum=%d********\n" )
	.zero	1
.LC1064:
	ASCII(.string	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\n" )
	.zero	1
.LC1066:
	ASCII(.string	"PPS decode error.\n" )
	.zero	5
.LC1068:
	ASCII(.string	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\n" )
	.zero	1
.LC1070:
	ASCII(.string	"SPS decode error.\n" )
	.zero	5
.LC1072:
	ASCII(.string	"***** NAL: SEI, nal_unit_type=%d\n" )
	.zero	6
.LC1074:
	ASCII(.string	"SEI decode error.\n" )
	.zero	5
.LC1076:
	ASCII(.string	"***** NAL: AUD, nal_unit_type=%d\n" )
	.zero	6
.LC1078:
	ASCII(.string	"***** NAL: EOSEQ, nal_unit_type=%d\n" )
	.zero	4
.LC1080:
	ASCII(.string	"***** NAL: FILL, nal_unit_type=%d\n" )
	.zero	5
.LC1082:
	ASCII(.string	"***** NAL: EOSTREAM, nal_unit_type=%d\n" )
	.zero	1
.LC1084:
	ASCII(.string	"***** NAL: SPSEXT, nal_unit_type=%d\n" )
	.zero	3
.LC1086:
	ASCII(.string	"***** NAL: PREFIX, nal_unit_type=%d\n" )
	.zero	3
.LC1088:
	ASCII(.string	"***** NAL: SUBSPS, nal_unit_type=%d\n" )
	.zero	3
.LC1091:
	ASCII(.string	"***** NAL: AUX, nal_unit_type=%d\n" )
	.zero	6
.LC1093:
	ASCII(.string	"***** NAL: EOPIC, nal_unit_type=%d\n" )
	.zero	4
.LC1096:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:%x\n" )
	.zero	1
.LC1098:
	ASCII(.string	"nal_header != 0x00000100 not support.\n" )
	.zero	1
.LC1103:
	ASCII(.string	"pPacket= NULL" )
	.zero	2
.LC1107:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC1110:
	ASCII(.string	"MVC_FindTrailZeros ERR\n" )
.LC1114:
	ASCII(.string	"store pic err, ret = %d\n" )
	.zero	7
.LC1116:
	ASCII(.string	"MVC_IMODE nal store pic err, ret = %d\n" )
	.zero	1
.LC1118:
	ASCII(.string	"MVC_IMODE nal flush dpb err, ret = %d\n" )
	.zero	1
.LC1122:
	ASCII(.string	"cann't find FrameStore\n" )
.LC1124:
	ASCII(.string	"========== MVC FrameStore state(is_used, is_in_dpb, MVC_IsOutDPB) ========\n" )
	.zero	4
.LC1126:
	ASCII(.string	"ReadImgNum = %d, NewImgNum = %d\n" )
	.zero	7
.LC1128:
	ASCII(.string	"%02d: %d %d %d\n" )
.LC1130:
	ASCII(.string	"FrameStore leak, MVC_ClearAll\n" )
	.bss
	.align	3
.LANCHOR2 = . + 0
.LANCHOR3 = . + 4352
	.type	pps_tmp.12293, %object
	.size	pps_tmp.12293, 2240
pps_tmp.12293:
	.zero	2240
	.type	sps_tmp.12429, %object
	.size	sps_tmp.12429, 3992
sps_tmp.12429:
	.zero	3992
	.type	MvcTmpBuf, %object
	.size	MvcTmpBuf, 68
MvcTmpBuf:
	.zero	68
	.type	cnt.11249, %object
	.size	cnt.11249, 4
cnt.11249:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
