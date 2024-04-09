#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"h264.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	IsSTRefFlg
	.type	IsSTRefFlg, %function
IsSTRefFlg:
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
	.size	IsSTRefFlg, .-IsSTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsLTRefFlg
	.type	IsLTRefFlg, %function
IsLTRefFlg:
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
	.size	IsLTRefFlg, .-IsLTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_pic_by_pic_num_desc
	.type	compare_pic_by_pic_num_desc, %function
compare_pic_by_pic_num_desc:
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
	ldr	w1, [x0, 8]
	ldr	w2, [x2, 8]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_pic_by_pic_num_desc, .-compare_pic_by_pic_num_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_pic_by_lt_pic_num_asc
	.type	compare_pic_by_lt_pic_num_asc, %function
compare_pic_by_lt_pic_num_asc:
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
	ldr	w1, [x0, 4]
	ldr	w2, [x2, 4]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_pic_by_lt_pic_num_asc, .-compare_pic_by_lt_pic_num_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_fs_by_frame_num_desc
	.type	compare_fs_by_frame_num_desc, %function
compare_fs_by_frame_num_desc:
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
	ldr	w1, [x0, 664]
	ldr	w2, [x2, 664]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_fs_by_frame_num_desc, .-compare_fs_by_frame_num_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_fs_by_lt_pic_idx_asc
	.type	compare_fs_by_lt_pic_idx_asc, %function
compare_fs_by_lt_pic_idx_asc:
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
	ldr	w1, [x0, 668]
	ldr	w2, [x2, 668]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, hi
	csel	w0, w0, w3, cs
	ret
	.size	compare_fs_by_lt_pic_idx_asc, .-compare_fs_by_lt_pic_idx_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_pic_by_poc_asc
	.type	compare_pic_by_poc_asc, %function
compare_pic_by_poc_asc:
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
	ldr	w1, [x0, 12]
	ldr	w2, [x2, 12]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_pic_by_poc_asc, .-compare_pic_by_poc_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_pic_by_poc_desc
	.type	compare_pic_by_poc_desc, %function
compare_pic_by_poc_desc:
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
	ldr	w1, [x0, 12]
	ldr	w2, [x2, 12]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_pic_by_poc_desc, .-compare_pic_by_poc_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_fs_by_poc_asc
	.type	compare_fs_by_poc_asc, %function
compare_fs_by_poc_asc:
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
	ldr	w1, [x0, 672]
	ldr	w2, [x2, 672]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	cset	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_fs_by_poc_asc, .-compare_fs_by_poc_asc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	compare_fs_by_poc_desc
	.type	compare_fs_by_poc_desc, %function
compare_fs_by_poc_desc:
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
	ldr	w1, [x0, 672]
	ldr	w2, [x2, 672]
	ldp	x29, x30, [sp], 32
	cmp	w2, w1
	csetm	w0, gt
	csel	w0, w0, w3, ge
	ret
	.size	compare_fs_by_poc_desc, .-compare_fs_by_poc_desc
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SetFrmRepeatCount.part.7, %function
SetFrmRepeatCount.part.7:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x3, x19, 65536
	add	x19, x19, 24576
	ldr	w2, [x3, 2000]
	ldr	w1, [x19, 3704]
	ldr	w0, [x3, 1996]
	add	w2, w1, w2, lsr 1
	lsr	w0, w0, 1
	add	w4, w2, 1
	cmp	w0, w4
	bcc	.L28
	sub	w0, w0, #1
	sub	w0, w0, w2
	cmp	w0, 1
	bls	.L29
	mov	w0, 2
	str	w0, [x20, 16]
	ldr	w0, [x3, 2000]
	add	w0, w0, 4
	str	w0, [x3, 2000]
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
	ldr	w0, [x3, 2000]
	add	w0, w0, 2
	str	w0, [x3, 2000]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SetFrmRepeatCount.part.7, .-SetFrmRepeatCount.part.7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	DumpList.part.10, %function
DumpList.part.10:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x24, x20, 20480
	mov	w21, 0
	bl	_mcount
	ldr	x23, .LC3
	add	x25, x24, 1624
.L33:
	ldr	w0, [x25]
	cbz	w0, .L37
	uxtw	x0, w21
	mov	w19, 0
	lsl	x22, x0, 5
	add	x22, x22, x0
	.p2align 2
.L34:
	add	x4, x22, x19, uxtw
	mov	w3, w19
	mov	w2, w21
	mov	x1, x23
	add	x4, x20, x4, lsl 3
	mov	w0, 13
	add	w19, w19, 1
	ldr	x4, [x4, 28696]
	ldr	x4, [x4, 40]
	ldr	w5, [x4, 672]
	ldr	w4, [x4, 660]
	bl	dprint_vfmw
	ldr	w0, [x25]
	cmp	w19, w0
	bcc	.L34
.L37:
	add	w21, w21, 1
	add	x25, x25, 4
	cmp	w21, 2
	bne	.L33
	ldr	w0, [x24, 1624]
	cbnz	w0, .L65
.L38:
	ldr	w0, [x24, 1628]
	cbnz	w0, .L66
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L66:
	ldr	x1, .LC15
	mov	w0, 13
	mov	w19, 0
	bl	dprint_vfmw
	ldr	w0, [x24, 1628]
	cbz	w0, .L53
	ldr	x23, .LC9
	ldr	x21, .LC13
	ldr	x22, .LC11
	b	.L58
	.p2align 3
.L67:
	cmp	w0, 2
	cbz	w0, .L50
	mov	x1, x21
	mov	w0, 13
	bne	.L48
	ldr	x2, [x2, 40]
	ldr	w2, [x2, 672]
	bl	dprint_vfmw
.L48:
	ldr	w0, [x24, 1628]
	add	w19, w19, 1
	cmp	w19, w0
	bcs	.L53
.L58:
	add	x0, x20, x19, uxtw 3
	ldr	x2, [x0, 28960]
	ldrb	w0, [x2]
	cmp	w0, 1
	bne	.L67
	ldr	x2, [x2, 40]
	mov	x1, x22
	mov	w0, 13
	add	w19, w19, 1
	ldr	w2, [x2, 672]
	bl	dprint_vfmw
	ldr	w0, [x24, 1628]
	cmp	w19, w0
	bcc	.L58
.L53:
	ldr	x1, .LC7
	mov	w0, 13
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L50:
	ldr	x2, [x2, 40]
	mov	x1, x23
	mov	w0, 13
	ldr	w2, [x2, 672]
	bl	dprint_vfmw
	b	.L48
	.p2align 3
.L65:
	ldr	x1, .LC5
	mov	w0, 13
	mov	w19, 0
	bl	dprint_vfmw
	ldr	w0, [x24, 1624]
	cbz	w0, .L45
	ldr	x23, .LC9
	ldr	x21, .LC13
	ldr	x22, .LC11
	b	.L59
	.p2align 3
.L68:
	cmp	w0, 2
	cbz	w0, .L42
	mov	x1, x21
	mov	w0, 13
	bne	.L40
	ldr	x2, [x2, 40]
	ldr	w2, [x2, 812]
	bl	dprint_vfmw
.L40:
	ldr	w0, [x24, 1624]
	add	w19, w19, 1
	cmp	w19, w0
	bcs	.L45
.L59:
	add	x0, x20, x19, uxtw 3
	ldr	x2, [x0, 28696]
	ldrb	w0, [x2]
	cmp	w0, 1
	bne	.L68
	ldr	x2, [x2, 40]
	mov	x1, x22
	mov	w0, 13
	add	w19, w19, 1
	ldr	w2, [x2, 764]
	bl	dprint_vfmw
	ldr	w0, [x24, 1624]
	cmp	w19, w0
	bcc	.L59
.L45:
	ldr	x1, .LC7
	mov	w0, 13
	bl	dprint_vfmw
	b	.L38
	.p2align 3
.L42:
	ldr	x2, [x2, 40]
	mov	x1, x23
	mov	w0, 13
	ldr	w2, [x2, 672]
	bl	dprint_vfmw
	b	.L40
	.size	DumpList.part.10, .-DumpList.part.10
	.align	3
.LC3:
	.xword	.LC2
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC9:
	.xword	.LC8
	.align	3
.LC11:
	.xword	.LC10
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC15:
	.xword	.LC14
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	CombinePacket.part.17, %function
CombinePacket.part.17:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC17
	mov	w0, 7
	bl	dprint_vfmw
	ldr	x2, [x19, 632]
	mov	w0, 7
	ldr	x1, .LC19
	ldp	w5, w3, [x2, 48]
	ldr	w4, [x2, 16]
	ldr	w2, [x2, 20]
	bl	dprint_vfmw
	ldr	x1, [x19, 632]
	ldr	x3, .LC20
	ldr	w2, [x1, 16]
	ldr	x0, [x1, 40]
	ldr	x3, [x3, 104]
	ldr	x1, [x1, 8]
	sub	x0, x0, x2
	blr	x3
	ldr	x2, [x19, 632]
	mov	w4, 1
	ldr	x1, .LC22
	mov	w0, 7
	ldr	w3, [x2, 68]
	ldr	w20, [x2, 36]
	str	w3, [x2, 36]
	ldr	x2, [x19, 632]
	str	wzr, [x2, 28]
	ldr	x2, [x19, 632]
	ldr	w5, [x2, 16]
	ldr	x3, [x2, 40]
	sub	x3, x3, x5
	str	x3, [x2, 8]
	ldr	x2, [x19, 632]
	ldr	w5, [x2, 16]
	ldr	w3, [x2, 52]
	sub	w3, w3, w5
	str	w3, [x2, 20]
	ldr	x2, [x19, 632]
	ldr	w5, [x2, 16]
	ldr	w3, [x2, 48]
	add	w3, w5, w3
	str	w3, [x2, 16]
	ldr	x2, [x19, 632]
	str	w4, [x2, 76]
	ldr	x2, [x19, 632]
	ldp	w3, w2, [x2, 16]
	bl	dprint_vfmw
	add	x0, x19, 65536
	mov	w1, w20
	ldr	w0, [x0, 1980]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 632]
	str	xzr, [x0, 40]
	ldr	x0, [x19, 632]
	str	wzr, [x0, 60]
	ldr	x0, [x19, 632]
	str	wzr, [x0, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CombinePacket.part.17, .-CombinePacket.part.17
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
	.align	3
.LC20:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ue_v
	.type	ue_v, %function
ue_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 12288
	mov	x23, x1
	add	x21, x21, 2600
	bl	_mcount
	mov	w1, 32
	mov	x0, x21
	bl	BsShow
	mov	w20, w0
	bl	ZerosMS_32
	cmp	w0, 15
	mov	w19, w0
	bls	.L74
	cmp	w0, 31
	bls	.L75
	add	x0, x22, 65536
	mov	w1, 1
	mov	w20, -1
	mov	w19, 32
	str	w1, [x0, 1920]
.L72:
	ldr	x4, [x22, 632]
	mov	w3, w20
	ldr	x1, .LC24
	mov	x2, x23
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
.L74:
	lsl	w19, w0, 1
	mov	w2, 32
	add	w19, w19, 1
	mov	x0, x21
	sub	w2, w2, w19
	mov	w1, w19
	lsr	w20, w20, w2
	sub	w20, w20, #1
	bl	BsSkip
	b	.L72
	.p2align 3
.L75:
	mov	w1, w0
	mov	x0, x21
	add	w24, w19, 1
	lsl	w19, w19, 1
	bl	BsSkip
	add	w19, w19, 1
	mov	w1, w24
	mov	x0, x21
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w24
	mov	x0, x21
	bl	BsSkip
	b	.L72
	.size	ue_v, .-ue_v
	.align	3
.LC24:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	se_v
	.type	se_v, %function
se_v:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 12288
	mov	x23, x1
	add	x21, x21, 2600
	bl	_mcount
	mov	w1, 32
	mov	x0, x21
	bl	BsShow
	mov	w20, w0
	bl	ZerosMS_32
	cmp	w0, 15
	mov	w19, w0
	bhi	.L77
	lsl	w19, w0, 1
	mov	w2, 32
	add	w19, w19, 1
	mov	x0, x21
	sub	w2, w2, w19
	mov	w1, w19
	lsr	w20, w20, w2
	and	w2, w20, 1
	lsr	w20, w20, 1
	cmp	w2, wzr
	csneg	w20, w20, w20, eq
	bl	BsSkip
.L79:
	ldr	x4, [x22, 632]
	mov	w3, w20
	ldr	x1, .LC25
	mov	x2, x23
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
.L77:
	cmp	w0, 31
	bls	.L86
	add	x0, x22, 65536
	mov	w1, 1
	mov	w20, 2147483647
	mov	w19, 32
	str	w1, [x0, 1920]
	b	.L79
	.p2align 3
.L86:
	mov	w1, w0
	mov	x0, x21
	bl	BsSkip
	mov	w1, w19
	mov	x0, x21
	lsl	w19, w19, 1
	bl	BsGet
	mov	w20, w0
	mov	w1, 1
	mov	x0, x21
	add	w19, w19, 1
	bl	BsGet
	and	w0, w0, 1
	cmp	w0, wzr
	csneg	w20, w20, w20, eq
	b	.L79
	.size	se_v, .-se_v
	.align	3
.LC25:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	u_v
	.type	u_v, %function
u_v:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x22, x2
	mov	w19, w1
	bl	_mcount
	add	x0, x21, 12288
	mov	w1, w19
	add	x0, x0, 2600
	bl	BsGet
	mov	w20, w0
	ldr	x4, [x21, 632]
	mov	w3, w0
	ldr	x1, .LC26
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
	.size	u_v, .-u_v
	.align	3
.LC26:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	u_1
	.type	u_1, %function
u_1:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	add	x0, x20, 12288
	mov	w1, 1
	add	x0, x0, 2600
	bl	BsGet
	mov	w19, w0
	ldr	x5, [x20, 632]
	mov	w3, w0
	ldr	x1, .LC27
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
	.size	u_1, .-u_1
	.align	3
.LC27:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FrameStoreRefFlg
	.type	FrameStoreRefFlg, %function
FrameStoreRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 2]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	FrameStoreRefFlg, .-FrameStoreRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseNAL
	.type	ReleaseNAL, %function
ReleaseNAL:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L99
	ldr	x23, .LC35
	add	x19, x20, 8
	strb	wzr, [x20, 1]
	add	x22, x20, 72
	strb	wzr, [x20, 4]
.L94:
	ldr	x1, [x19]
	mov	w0, w21
	cbz	x1, .L93
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
.L93:
	add	x19, x19, 32
	cmp	x19, x22
	bne	.L94
	strb	wzr, [x20]
	str	wzr, [x20, 76]
.L90:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L99:
	ldr	x2, .LC31
	mov	w3, 422
	ldr	x1, .LC33
	mov	w0, 0
	bl	dprint_vfmw
	b	.L90
	.size	ReleaseNAL, .-ReleaseNAL
	.align	3
.LC31:
	.xword	.LC30
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC35:
	.xword	.LC34
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetMinPOC
	.type	GetMinPOC, %function
GetMinPOC:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x21]
	add	x1, x20, 24576
	mov	w0, 2147483647
	str	w0, [x19]
	ldr	w0, [x1, 3704]
	ldr	w2, [x1, 3708]
	cmp	w2, w0
	bls	.L101
	mov	w2, w0
	str	w0, [x1, 3708]
.L101:
	mov	w0, 0
	cbz	w2, .L100
	.p2align 2
.L108:
	add	x3, x20, x0, uxtw 3
	ldr	w5, [x19]
	ldr	x3, [x3, 27896]
	ldr	w4, [x3, 672]
	cmp	w5, w4
	ble	.L103
	ldrb	w3, [x3, 4]
	cbz	w3, .L103
	str	w4, [x19]
	str	w0, [x21]
.L103:
	ldr	w3, [x1, 3708]
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L108
.L100:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetMinPOC, .-GetMinPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RemoveFrameStoreOutDPB
	.type	RemoveFrameStoreOutDPB, %function
RemoveFrameStoreOutDPB:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	uxtw	x21, w1
	mov	x20, x0
	mov	x0, x30
	mov	x19, x21
	add	x22, x20, x21, lsl 3
	bl	_mcount
	ldr	x1, [x22, 27896]
	cbz	x1, .L129
	ldr	w0, [x1, 696]
	add	x23, x20, 24576
	add	x24, x20, 65536
	add	x0, x0, 4096
	add	x0, x0, 2980
	str	wzr, [x20, x0, lsl 2]
	ldr	w0, [x23, 3988]
	cmp	w0, wzr
	cset	w2, ne
	sub	w0, w0, w2
	str	w0, [x23, 3988]
	ldr	w1, [x1, 656]
	ldr	w0, [x24, 1980]
	bl	FSP_GetLogicFs
	cbz	x0, .L115
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	beq	.L116
	ldr	x1, [x22, 27896]
	mov	w2, 0
	ldr	w0, [x24, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetDisplay
.L116:
	ldr	x1, [x22, 27896]
	mov	w2, 0
	ldr	w0, [x24, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetRef
.L115:
	ldr	x0, [x22, 27896]
	mov	w1, -1
	strb	wzr, [x0, 1]
	ldr	x0, [x22, 27896]
	strb	wzr, [x0, 4]
	ldr	x0, [x22, 27896]
	strb	wzr, [x0, 2]
	ldr	x0, [x22, 27896]
	str	w1, [x0, 656]
	ldr	w2, [x23, 3708]
	add	w2, w2, w1
	cmp	w19, w2
	bcs	.L118
	.p2align 2
.L126:
	add	w0, w19, 1
	add	x1, x20, x21, lsl 3
	mov	w19, w0
	cmp	w0, w2
	mov	x21, x0
	add	x0, x20, x0, lsl 3
	ldr	x0, [x0, 27896]
	str	x0, [x1, 27896]
	bne	.L126
.L118:
	add	x20, x20, x2, uxtw 3
	str	xzr, [x20, 27896]
	str	w2, [x23, 3708]
.L111:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L129:
	ldr	x2, .LC36
	mov	w3, w21
	ldr	x1, .LC38
	mov	w0, 1
	bl	dprint_vfmw
	b	.L111
	.size	RemoveFrameStoreOutDPB, .-RemoveFrameStoreOutDPB
	.align	3
.LC36:
	.xword	.LANCHOR0
	.align	3
.LC38:
	.xword	.LC37
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RemoveUnUsedFrameStore
	.type	RemoveUnUsedFrameStore, %function
RemoveUnUsedFrameStore:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	cbz	x22, .L140
	add	x0, x22, 24576
	ldr	w23, [x0, 3708]
	cbz	w23, .L139
	mov	w21, 0
	mov	w20, 0
	add	x24, x22, 65536
	mov	w25, -1
	b	.L138
	.p2align 3
.L149:
	ldrb	w1, [x0, 4]
	cbnz	w1, .L136
	ldr	w1, [x0, 848]
	cmp	w1, 1
	beq	.L136
	strb	wzr, [x0, 1]
	mov	w1, w21
	mov	x0, x22
	add	w20, w20, 1
	bl	RemoveFrameStoreOutDPB
	cmp	w23, w20
	beq	.L139
	.p2align 2
.L138:
	add	x19, x22, x21, uxtw 3
	ldr	w0, [x24, 1980]
	ldr	x1, [x19, 27896]
	ldr	w1, [x1, 656]
	bl	FSP_GetLogicFs
	cbz	x0, .L133
	ldrsh	w1, [x0]
	cbnz	w1, .L134
	ldr	x1, [x19, 27896]
	ldrb	w2, [x1, 2]
	cbnz	w2, .L135
	ldrsb	w0, [x0]
	cbnz	w0, .L148
.L135:
	str	w25, [x1, 656]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 2]
.L133:
	ldr	x0, [x19, 27896]
	ldr	w1, [x0, 848]
	cmp	w1, 1
	cset	w1, eq
	strb	w1, [x0, 4]
.L134:
	ldr	x0, [x19, 27896]
	ldrb	w1, [x0, 2]
	cbz	w1, .L149
.L136:
	add	w20, w20, 1
	add	w21, w21, 1
	cmp	w23, w20
	bne	.L138
.L139:
	mov	w0, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L148:
	ldr	w1, [x1, 656]
	ldr	w0, [x24, 1980]
	bl	FSP_SetRef
	ldr	x1, [x19, 27896]
	b	.L135
	.p2align 3
.L140:
	mov	w0, -1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	RemoveUnUsedFrameStore, .-RemoveUnUsedFrameStore
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkFrameStoreRef
	.type	UnMarkFrameStoreRef, %function
UnMarkFrameStoreRef:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x19, 1]
	tbz	x0, 0, .L151
	ldrb	w1, [x19, 2]
	strb	wzr, [x19, 753]
	and	w1, w1, 2
	strb	wzr, [x19, 754]
	strb	w1, [x19, 2]
.L151:
	tbz	x0, 1, .L152
	ldrb	w1, [x19, 2]
	strb	wzr, [x19, 801]
	and	w1, w1, 1
	strb	wzr, [x19, 802]
	strb	w1, [x19, 2]
.L152:
	cmp	w0, 3
	bne	.L153
	strb	wzr, [x19, 706]
	strb	wzr, [x19, 705]
.L153:
	add	x20, x20, 65536
	strb	wzr, [x19, 2]
	ldr	w1, [x19, 656]
	mov	w2, 0
	ldr	w0, [x20, 1980]
	bl	FSP_SetRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	UnMarkFrameStoreRef, .-UnMarkFrameStoreRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitOldSlice
	.type	InitOldSlice, %function
InitOldSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	mov	w4, 32
	ldr	w8, [x19, 14948]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x0, 3226]
	add	x4, x0, 3072
	strb	wzr, [x0, 3224]
	mov	w5, 7
	strb	w6, [x0, 3225]
	mov	w3, 3
	str	w8, [x0, 3232]
	mov	w2, -1
	str	w5, [x0, 3236]
	mov	w1, 262144
	str	w7, [x0, 3240]
	stp	w3, w2, [x4, 176]
	stp	wzr, wzr, [x4, 184]
	str	w1, [x0, 3264]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	InitOldSlice, .-InitOldSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearAllSlice
	.type	ClearAllSlice, %function
ClearAllSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 65536
	add	x19, x19, 61440
	add	x19, x19, 3576
	add	x20, x21, 568
	bl	_mcount
	.p2align 2
.L163:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L162
	ldr	w0, [x21, 1980]
	bl	ReleaseNAL
	str	xzr, [x19]
.L162:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L163
	str	wzr, [x21, 1904]
	mov	w0, 0
	str	wzr, [x21, 1964]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	ClearAllSlice, .-ClearAllSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_IsEosNal
	.type	H264_IsEosNal, %function
H264_IsEosNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 12288
	bl	_mcount
	add	x19, x19, 2600
	mov	w1, 32
	mov	x0, x19
	bl	BsGet
	mov	w20, w0
	mov	w1, 32
	mov	x0, x19
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w20, w2
	ccmp	w0, w1, 0, eq
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	H264_IsEosNal, .-H264_IsEosNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearCurrNal
	.type	ClearCurrNal, %function
ClearCurrNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 632]
	cbz	x1, .L170
	add	x0, x19, 65536
	ldr	w0, [x0, 1980]
	bl	ReleaseNAL
	str	xzr, [x19, 632]
.L170:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ClearCurrNal, .-ClearCurrNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearAllNal
	.type	ClearAllNal, %function
ClearAllNal:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 640
	add	x21, x20, 65536
	add	x20, x20, 12288
	bl	_mcount
	add	x20, x20, 2600
	b	.L176
	.p2align 3
.L175:
	add	x19, x19, 104
	cmp	x19, x20
	beq	.L178
.L176:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L175
	ldr	w0, [x21, 1980]
	mov	x1, x19
	add	x19, x19, 104
	bl	ReleaseNAL
	cmp	x19, x20
	bne	.L176
.L178:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	ClearAllNal, .-ClearAllNal
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearCurrSlice
	.type	ClearCurrSlice, %function
ClearCurrSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 65536
	bl	_mcount
	ldr	x1, .LC42
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L180
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L180:
	ldr	w1, [x19, 1936]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 1936]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ClearCurrSlice, .-ClearCurrSlice
	.align	3
.LC42:
	.xword	.LC41
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_ClearCurrPic
	.type	H264_ClearCurrPic, %function
H264_ClearCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L187
	mov	x0, x19
	bl	ClearAllSlice
	add	x0, x19, 20480
	mov	w4, 32
	ldr	w8, [x19, 14948]
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	strb	w4, [x0, 3226]
	add	x4, x0, 3072
	strb	wzr, [x0, 3224]
	mov	w5, 7
	strb	w6, [x0, 3225]
	mov	w3, 3
	str	w8, [x0, 3232]
	mov	w2, -1
	str	w5, [x0, 3236]
	mov	w1, 262144
	str	w7, [x0, 3240]
	stp	w3, w2, [x4, 176]
	stp	wzr, wzr, [x4, 184]
	str	w1, [x0, 3264]
	mov	w0, 0
.L186:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L187:
	ldr	x2, .LC43
	mov	w3, 737
	ldr	x1, .LC44
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L186
	.size	H264_ClearCurrPic, .-H264_ClearCurrPic
	.align	3
.LC43:
	.xword	.LC30
	.align	3
.LC44:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetMinPOCInDPB
	.type	GetMinPOCInDPB, %function
GetMinPOCInDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x21]
	add	x1, x20, 24576
	mov	w0, 2147483647
	str	w0, [x19]
	ldr	w0, [x1, 3704]
	ldr	w2, [x1, 3708]
	cmp	w2, w0
	bls	.L189
	mov	w2, w0
	str	w0, [x1, 3708]
.L189:
	mov	w0, 0
	cbz	w2, .L188
	.p2align 2
.L194:
	add	x3, x20, x0, uxtw 3
	ldr	w4, [x19]
	ldr	x3, [x3, 27896]
	ldr	w3, [x3, 672]
	cmp	w4, w3
	ble	.L191
	str	w3, [x19]
	str	w0, [x21]
.L191:
	ldr	w3, [x1, 3708]
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L194
.L188:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetMinPOCInDPB, .-GetMinPOCInDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetMaxPOC
	.type	GetMaxPOC, %function
GetMaxPOC:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x2
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	str	wzr, [x21]
	add	x1, x20, 24576
	str	wzr, [x19]
	ldr	w0, [x1, 3704]
	ldr	w2, [x1, 3708]
	cmp	w2, w0
	bls	.L197
	mov	w2, w0
	str	w0, [x1, 3708]
.L197:
	mov	w0, 0
	cbz	w2, .L196
	.p2align 2
.L204:
	add	x3, x20, x0, uxtw 3
	ldr	w5, [x19]
	ldr	x3, [x3, 27896]
	ldr	w4, [x3, 672]
	cmp	w5, w4
	bge	.L199
	ldrb	w3, [x3, 4]
	cbz	w3, .L199
	str	w4, [x19]
	str	w0, [x21]
.L199:
	ldr	w3, [x1, 3708]
	add	w0, w0, 1
	cmp	w3, w0
	bhi	.L204
.L196:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetMaxPOC, .-GetMaxPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ShortTermRefFlg
	.type	ShortTermRefFlg, %function
ShortTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 2]
	cmp	w1, 3
	beq	.L223
	tbnz	x1, 0, .L224
.L211:
	mov	w0, 0
	tbnz	x1, 1, .L212
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L224:
	ldr	w0, [x19, 752]
	and	w0, w0, 16776960
	cmp	w0, 65536
	bne	.L211
.L216:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L223:
	ldr	w0, [x19, 704]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L216
	ldr	w0, [x19, 752]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L216
.L212:
	ldr	w0, [x19, 800]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 65536
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	ShortTermRefFlg, .-ShortTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	LongTermRefFlg
	.type	LongTermRefFlg, %function
LongTermRefFlg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19, 2]
	cmp	w1, 3
	beq	.L241
	tbnz	x1, 0, .L242
.L229:
	mov	w0, 0
	tbnz	x1, 1, .L230
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L242:
	ldr	w0, [x19, 752]
	and	w0, w0, 16776960
	cmp	w0, 256
	bne	.L229
.L234:
	mov	w0, 1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L241:
	ldr	w0, [x19, 704]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L234
	ldr	w0, [x19, 752]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L234
.L230:
	ldr	w0, [x19, 800]
	ldr	x19, [sp, 16]
	and	w0, w0, 16776960
	cmp	w0, 256
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	LongTermRefFlg, .-LongTermRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdateLTReflist
	.type	UpdateLTReflist, %function
UpdateLTReflist:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x24, x22, 24576
	bl	_mcount
	ldr	w0, [x24, 3708]
	cbz	w0, .L250
	sub	w23, w0, #1
	add	x20, x24, 3320
	add	x23, x23, 3488
	mov	w19, 0
	add	x23, x22, x23, lsl 3
	.p2align 2
.L246:
	ldr	x21, [x20]
	add	x20, x20, 8
	mov	x0, x21
	bl	LongTermRefFlg
	add	x1, x22, x19, uxtw 3
	cmp	x20, x23
	cbz	w0, .L245
	add	w19, w19, 1
	str	x21, [x1, 28152]
.L245:
	bne	.L246
.L244:
	ldr	w1, [x24, 3704]
	str	w19, [x24, 3716]
	cmp	w1, w19
	bls	.L243
	.p2align 2
.L253:
	add	x0, x22, x19, uxtw 3
	add	w19, w19, 1
	cmp	w19, w1
	str	xzr, [x0, 28152]
	bne	.L253
.L243:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L250:
	mov	w19, 0
	b	.L244
	.size	UpdateLTReflist, .-UpdateLTReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdateReflist
	.type	UpdateReflist, %function
UpdateReflist:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x24, x22, 24576
	bl	_mcount
	ldr	w0, [x24, 3708]
	cbz	w0, .L264
	sub	w23, w0, #1
	add	x20, x24, 3320
	add	x23, x23, 3488
	mov	w19, 0
	add	x23, x22, x23, lsl 3
	.p2align 2
.L260:
	ldr	x21, [x20]
	add	x20, x20, 8
	mov	x0, x21
	bl	ShortTermRefFlg
	add	x1, x22, x19, uxtw 3
	cmp	x20, x23
	cbz	w0, .L259
	add	w19, w19, 1
	str	x21, [x1, 28024]
.L259:
	bne	.L260
.L258:
	ldr	w1, [x24, 3704]
	str	w19, [x24, 3712]
	cmp	w1, w19
	bls	.L257
	.p2align 2
.L267:
	add	x0, x22, x19, uxtw 3
	add	w19, w19, 1
	cmp	w19, w1
	str	xzr, [x0, 28024]
	bne	.L267
.L257:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L264:
	mov	w19, 0
	b	.L258
	.size	UpdateReflist, .-UpdateReflist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SlidingWinMark.part.8, %function
SlidingWinMark.part.8:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x19, x22, 24576
	bl	_mcount
	ldr	w0, [x19, 3708]
	cbz	w0, .L271
	sub	w21, w0, #1
	add	x19, x19, 3320
	add	x21, x21, 3488
	add	x21, x22, x21, lsl 3
	.p2align 2
.L274:
	ldr	x20, [x19]
	add	x19, x19, 8
	mov	x0, x20
	ldrb	w1, [x20, 2]
	cbz	w1, .L273
	bl	ShortTermRefFlg
	cbnz	w0, .L285
.L273:
	cmp	x19, x21
	bne	.L274
.L271:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L285:
	mov	x1, x20
	mov	x0, x22
	bl	UnMarkFrameStoreRef
	mov	x0, x22
	bl	UpdateReflist
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	SlidingWinMark.part.8, .-SlidingWinMark.part.8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetPicNumX
	.type	GetPicNumX, %function
GetPicNumX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldrb	w0, [x20, 3]
	ldr	w2, [x20, 672]
	cbz	w0, .L288
	lsl	w2, w2, 1
	add	w2, w2, 1
.L288:
	mvn	w0, w19
	add	w0, w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetPicNumX, .-GetPicNumX
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkLTFrmByFrmIdx
	.type	UnMarkLTFrmByFrmIdx, %function
UnMarkLTFrmByFrmIdx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 24576
	ldr	w4, [x0, 3716]
	cbz	w4, .L289
	ldr	x1, [x20, 28152]
	ldr	w0, [x1, 668]
	cmp	w19, w0
	beq	.L291
	sub	w4, w4, #1
	mov	x0, x20
	add	x4, x20, x4, lsl 3
	b	.L293
	.p2align 3
.L294:
	ldr	x1, [x0, 28160]
	add	x0, x0, 8
	ldr	w3, [x1, 668]
	cmp	w3, w19
	beq	.L291
.L293:
	cmp	x0, x4
	bne	.L294
.L289:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L291:
	mov	x0, x20
	bl	UnMarkFrameStoreRef
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	UnMarkLTFrmByFrmIdx, .-UnMarkLTFrmByFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkLTFldByFrmIdx
	.type	UnMarkLTFldByFrmIdx, %function
UnMarkLTFldByFrmIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	mov	w20, w2
	mov	w19, w3
	bl	_mcount
	add	x0, x22, 24576
	ldr	w4, [x0, 3716]
	cbz	w4, .L300
	sub	w6, w4, #1
	add	x0, x0, 3576
	add	x6, x6, 3520
	add	x6, x22, x6, lsl 3
	b	.L304
	.p2align 3
.L302:
	cmp	x0, x6
	beq	.L300
.L304:
	ldr	x4, [x0]
	add	x0, x0, 8
	ldr	w5, [x4, 668]
	cmp	w5, w19
	bne	.L302
	cmp	w20, 1
	beq	.L316
	cmp	w20, 2
	bne	.L302
	ldrb	w1, [x4, 753]
	cmp	w1, wzr
	ccmp	x4, x21, 0, ne
	beq	.L302
.L315:
	mov	x1, x4
	mov	x0, x22
	bl	UnMarkFrameStoreRef
.L300:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L316:
	ldrb	w1, [x4, 801]
	cmp	w1, wzr
	ccmp	x4, x21, 0, ne
	beq	.L302
	b	.L315
	.size	UnMarkLTFldByFrmIdx, .-UnMarkLTFldByFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkSTRef
	.type	UnMarkSTRef, %function
UnMarkSTRef:
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
	cbnz	w0, .L318
	add	x0, x19, 24576
	ldr	w3, [x20, 672]
	sub	w3, w3, #1
	ldr	w1, [x0, 3712]
	sub	w2, w3, w21
	cbz	w1, .L317
	sub	w4, w1, #1
	add	x0, x0, 3448
	add	x4, x4, 3504
	add	x4, x19, x4, lsl 3
	b	.L324
	.p2align 3
.L323:
	cmp	x0, x4
	beq	.L317
.L324:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 712]
	cmp	w3, w2
	bne	.L323
	ldrb	w3, [x1, 2]
	cmp	w3, 3
	bne	.L323
	ldr	w3, [x1, 704]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L323
	mov	x0, x19
	bl	UnMarkFrameStoreRef
.L317:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L318:
	add	x1, x19, 24576
	ldr	w0, [x20, 672]
	add	x4, x1, 3448
	mov	w3, 0
	lsl	w0, w0, 1
	ldr	w6, [x1, 3712]
	sub	w2, w0, w21
	cbz	w6, .L317
	.p2align 2
.L338:
	ldr	x1, [x4]
	add	x4, x4, 8
	ldrb	w0, [x1, 2]
	and	w7, w0, 1
	tbz	x0, 0, .L325
	ldr	w5, [x1, 752]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L350
.L325:
	tbz	x0, 1, .L327
	ldr	w0, [x1, 800]
	and	w0, w0, 16776960
	cmp	w0, 65536
	beq	.L351
.L327:
	add	w3, w3, 1
	cmp	w3, w6
	bne	.L338
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L350:
	ldr	w5, [x1, 760]
	cmp	w5, w2
	bne	.L325
	add	x3, x19, x3, uxtw 3
	and	w0, w0, 2
	strb	w0, [x1, 2]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 754]
	b	.L349
	.p2align 3
.L351:
	ldr	w0, [x1, 808]
	cmp	w0, w2
	bne	.L327
	add	x3, x19, x3, uxtw 3
	strb	w7, [x1, 2]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 802]
.L349:
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 704]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L328
	strb	wzr, [x0, 706]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 705]
	ldr	x0, [x3, 28024]
.L328:
	ldrb	w1, [x0, 2]
	cbnz	w1, .L317
	ldr	w1, [x0, 692]
	add	x3, x19, 65536
	mov	w2, 0
	add	x1, x1, 16384
	add	x19, x19, x1, lsl 2
	str	wzr, [x19, 568]
	ldr	w1, [x0, 656]
	ldr	w0, [x3, 1980]
	bl	FSP_SetRef
	b	.L317
	.size	UnMarkSTRef, .-UnMarkSTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkLTRef
	.type	UnMarkLTRef, %function
UnMarkLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x1
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	ldrb	w0, [x21, 3]
	cbz	w0, .L353
	add	x0, x20, 24576
	mov	w3, 0
	add	x4, x0, 3576
	ldr	w2, [x0, 3716]
	cbz	w2, .L352
	.p2align 2
.L373:
	ldr	x1, [x4]
	add	x4, x4, 8
	ldrb	w0, [x1, 2]
	and	w6, w0, 1
	tbz	x0, 0, .L358
	ldr	w5, [x1, 752]
	and	w5, w5, 16776960
	cmp	w5, 256
	beq	.L385
.L358:
	tbz	x0, 1, .L360
	ldr	w0, [x1, 800]
	and	w0, w0, 16776960
	cmp	w0, 256
	beq	.L386
.L360:
	add	w3, w3, 1
	cmp	w3, w2
	bne	.L373
.L352:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L385:
	ldr	w5, [x1, 756]
	cmp	w19, w5
	bne	.L358
	add	x3, x20, x3, uxtw 3
	and	w0, w0, 2
	strb	w0, [x1, 2]
	ldr	x0, [x3, 28152]
	strb	wzr, [x0, 753]
	b	.L384
	.p2align 3
.L386:
	ldr	w0, [x1, 804]
	cmp	w19, w0
	bne	.L360
	add	x3, x20, x3, uxtw 3
	strb	w6, [x1, 2]
	ldr	x0, [x3, 28152]
	strb	wzr, [x0, 801]
.L384:
	ldr	x0, [x3, 28152]
	ldrb	w1, [x0, 704]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L361
	strb	wzr, [x0, 706]
	ldr	x0, [x3, 28152]
	strb	wzr, [x0, 705]
	ldr	x0, [x3, 28152]
.L361:
	ldrb	w1, [x0, 2]
	cbnz	w1, .L352
	ldr	w0, [x0, 692]
	add	x0, x0, 16384
	add	x20, x20, x0, lsl 2
	str	wzr, [x20, 568]
	b	.L352
	.p2align 3
.L353:
	add	x0, x20, 24576
	ldr	w1, [x0, 3716]
	cbz	w1, .L352
	sub	w2, w1, #1
	add	x0, x0, 3576
	add	x2, x2, 3520
	add	x2, x20, x2, lsl 3
	b	.L364
	.p2align 3
.L363:
	cmp	x0, x2
	beq	.L352
.L364:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldr	w3, [x1, 708]
	cmp	w3, w19
	bne	.L363
	ldrb	w3, [x1, 2]
	cmp	w3, 3
	bne	.L363
	ldr	w3, [x1, 704]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L363
	mov	x0, x20
	bl	UnMarkFrameStoreRef
	b	.L352
	.size	UnMarkLTRef, .-UnMarkLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MarkPicLTRef
	.type	MarkPicLTRef, %function
MarkPicLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x3
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	w20, w1
	bl	_mcount
	ldrb	w2, [x22, 3]
	add	x0, x21, 24576
	cbz	w2, .L388
	ldr	w7, [x0, 3712]
	mov	w3, 0
	add	x4, x0, 3448
	cbz	w7, .L387
	.p2align 2
.L409:
	ldr	x0, [x4]
	ldrb	w5, [x0, 2]
	tbz	x5, 0, .L394
	ldr	w6, [x0, 752]
	and	w6, w6, 16776960
	cmp	w6, 65536
	beq	.L415
.L394:
	tbz	x5, 1, .L397
	ldr	w5, [x0, 800]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L416
.L397:
	add	w3, w3, 1
	add	x4, x4, 8
	cmp	w3, w7
	bne	.L409
.L387:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L415:
	ldr	w1, [x0, 760]
	cmp	w19, w1
	bne	.L394
	ldrb	w1, [x0, 801]
	cmp	w1, 1
	bne	.L398
	ldr	w1, [x0, 668]
	cmp	w20, w1
	bne	.L397
.L398:
	add	x3, x21, x3, uxtw 3
	str	w20, [x0, 668]
	cmp	w2, 1
	lsl	w0, w20, 1
	csinc	w0, w0, w0, ne
	mov	w1, 1
	ldr	x2, [x3, 28024]
	str	w0, [x2, 756]
	ldr	x0, [x3, 28024]
	strb	w1, [x0, 753]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 754]
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 704]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L387
	ldrb	w2, [x0, 753]
	ldrb	w1, [x0, 801]
	cmp	w1, w2
	bne	.L387
	strb	w1, [x0, 705]
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 754]
	strb	w1, [x0, 706]
	b	.L387
	.p2align 3
.L416:
	ldr	w1, [x0, 808]
	cmp	w1, w19
	bne	.L397
	ldrb	w1, [x0, 753]
	cmp	w1, 1
	bne	.L401
	ldr	w1, [x0, 668]
	cmp	w1, w20
	bne	.L397
.L401:
	add	x3, x21, x3, uxtw 3
	str	w20, [x0, 668]
	cmp	w2, 2
	lsl	w0, w20, 1
	csinc	w0, w0, w0, ne
	mov	w1, 1
	ldr	x2, [x3, 28024]
	str	w0, [x2, 804]
	ldr	x0, [x3, 28024]
	strb	w1, [x0, 801]
	ldr	x0, [x3, 28024]
	strb	wzr, [x0, 802]
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 704]
	cmp	w1, 3
	ccmp	w1, wzr, 4, ne
	bne	.L387
	ldrb	w2, [x0, 753]
	ldrb	w1, [x0, 801]
	cmp	w1, w2
	bne	.L387
	strb	w1, [x0, 705]
	ldr	x0, [x3, 28024]
	ldrb	w1, [x0, 802]
	strb	w1, [x0, 706]
	b	.L387
	.p2align 3
.L388:
	ldr	w7, [x0, 3712]
	cbz	w7, .L387
	add	x0, x0, 3448
	mov	w4, 0
	b	.L393
	.p2align 3
.L392:
	add	w4, w4, 1
	cmp	w4, w7
	beq	.L387
.L393:
	ldr	x5, [x0]
	add	x0, x0, 8
	ldrb	w6, [x5, 2]
	cmp	w6, 3
	bne	.L392
	ldr	w6, [x5, 704]
	and	w6, w6, 16776960
	cmp	w6, 65536
	bne	.L392
	ldr	w1, [x5, 712]
	cmp	w19, w1
	bne	.L392
	add	x4, x21, x4, uxtw 3
	str	w20, [x5, 668]
	mov	w0, 1
	ldr	x1, [x4, 28024]
	str	w20, [x1, 708]
	ldr	x1, [x4, 28024]
	strb	w0, [x1, 705]
	ldr	x1, [x4, 28024]
	strb	w0, [x1, 753]
	ldr	x1, [x4, 28024]
	strb	w0, [x1, 801]
	ldr	x0, [x4, 28024]
	strb	wzr, [x0, 706]
	ldr	x0, [x4, 28024]
	strb	wzr, [x0, 754]
	ldr	x0, [x4, 28024]
	strb	wzr, [x0, 802]
	b	.L387
	.size	MarkPicLTRef, .-MarkPicLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MarkSTToLTRef
	.type	MarkSTToLTRef, %function
MarkSTToLTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	w20, w3
	bl	_mcount
	ldrb	w0, [x22, 3]
	cbnz	w0, .L418
	add	x0, x21, 24576
	ldr	w2, [x22, 672]
	sub	w2, w2, #1
	ldr	w4, [x0, 3716]
	sub	w19, w2, w19
	cbz	w4, .L420
	ldr	x1, [x21, 28152]
	ldr	w0, [x1, 668]
	cmp	w20, w0
	beq	.L422
	sub	w4, w4, #1
	mov	x0, x21
	add	x4, x21, x4, lsl 3
	b	.L424
	.p2align 3
.L425:
	ldr	x1, [x0, 28160]
	add	x0, x0, 8
	ldr	w3, [x1, 668]
	cmp	w20, w3
	beq	.L422
.L424:
	cmp	x4, x0
	bne	.L425
.L420:
	mov	x3, x22
	mov	w2, w19
	mov	w1, w20
	mov	x0, x21
	bl	MarkPicLTRef
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L418:
	add	x0, x21, 24576
	ldr	w2, [x22, 672]
	lsl	w2, w2, 1
	ldr	w1, [x0, 3712]
	sub	w19, w2, w19
	cbz	w1, .L420
	sub	w5, w1, #1
	add	x0, x0, 3448
	add	x5, x5, 3504
	add	x5, x21, x5, lsl 3
	.p2align 2
.L428:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w3, [x1, 2]
	tbz	x3, 0, .L426
	ldr	w4, [x1, 752]
	and	w4, w4, 16776960
	cmp	w4, 65536
	beq	.L438
.L426:
	tbz	x3, 1, .L427
	ldr	w3, [x1, 800]
	and	w3, w3, 16776960
	cmp	w3, 65536
	beq	.L439
.L427:
	cmp	x0, x5
	bne	.L428
	b	.L420
	.p2align 3
.L438:
	ldr	w2, [x1, 760]
	cmp	w2, w19
	bne	.L426
	mov	w3, w20
	mov	w2, 1
	mov	x0, x21
	bl	UnMarkLTFldByFrmIdx
	b	.L420
	.p2align 3
.L439:
	ldr	w2, [x1, 808]
	cmp	w2, w19
	bne	.L427
	mov	w3, w20
	mov	w2, 2
	mov	x0, x21
	bl	UnMarkLTFldByFrmIdx
	b	.L420
	.p2align 3
.L422:
	mov	x0, x21
	bl	UnMarkFrameStoreRef
	b	.L420
	.size	MarkSTToLTRef, .-MarkSTToLTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdateMaxLTFrmIdx
	.type	UpdateMaxLTFrmIdx, %function
UpdateMaxLTFrmIdx:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x21, x22, 24576
	mov	w20, w1
	bl	_mcount
	ldr	w0, [x21, 3716]
	str	w20, [x21, 3720]
	cbz	w0, .L440
	mov	w19, 0
	mov	w2, w20
	b	.L442
	.p2align 3
.L443:
	ldr	w0, [x21, 3716]
	cmp	w0, w19
	bls	.L440
.L447:
	ldr	w2, [x21, 3720]
.L442:
	add	x0, x22, x19, uxtw 3
	add	w19, w19, 1
	ldr	x1, [x0, 28152]
	ldr	w0, [x1, 668]
	cmp	w0, w2
	bcc	.L443
	mov	x0, x22
	bl	UnMarkFrameStoreRef
	ldr	w0, [x21, 3716]
	cmp	w0, w19
	bhi	.L447
.L440:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	UpdateMaxLTFrmIdx, .-UpdateMaxLTFrmIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UnMarkAllSTRef
	.type	UnMarkAllSTRef, %function
UnMarkAllSTRef:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 24576
	mov	w19, 0
	bl	_mcount
	ldr	w0, [x21, 3712]
	cbz	w0, .L448
	.p2align 2
.L452:
	add	x1, x20, x19, uxtw 3
	mov	x0, x20
	add	w19, w19, 1
	ldr	x1, [x1, 28024]
	bl	UnMarkFrameStoreRef
	ldr	w0, [x21, 3712]
	cmp	w0, w19
	bhi	.L452
.L448:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	UnMarkAllSTRef, .-UnMarkAllSTRef
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MarkCurrPicLT
	.type	MarkCurrPicLT, %function
MarkCurrPicLT:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	ldrb	w2, [x20, 3]
	cbnz	w2, .L455
	add	x0, x21, 24576
	ldr	w3, [x0, 3716]
	cbz	w3, .L456
	ldr	x1, [x21, 28152]
	ldr	w0, [x1, 668]
	cmp	w19, w0
	beq	.L457
	sub	w3, w3, #1
	mov	x0, x21
	add	x3, x21, x3, lsl 3
	b	.L459
	.p2align 3
.L460:
	ldr	x1, [x0, 28160]
	add	x0, x0, 8
	ldr	w2, [x1, 668]
	cmp	w19, w2
	beq	.L457
.L459:
	cmp	x0, x3
	bne	.L460
.L456:
	strb	wzr, [x20, 5]
	mov	w0, 1
	str	w19, [x20, 676]
	strb	w0, [x20, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L457:
	mov	x0, x21
	bl	UnMarkFrameStoreRef
	strb	wzr, [x20, 5]
	str	w19, [x20, 676]
	mov	w0, 1
	strb	w0, [x20, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L455:
	ldr	x1, [x20, 656]
	mov	w3, w19
	mov	x0, x21
	bl	UnMarkLTFldByFrmIdx
	strb	wzr, [x20, 5]
	str	w19, [x20, 676]
	mov	w0, 1
	strb	w0, [x20, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MarkCurrPicLT, .-MarkCurrPicLT
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_Sei_Get_Dpb_Output_Time
	.type	H264_Sei_Get_Dpb_Output_Time, %function
H264_Sei_Get_Dpb_Output_Time:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L476
	add	x0, x19, 20480
	mov	w1, 2208
	ldr	x9, [x19, 14968]
	add	x2, x19, 24576
	ldr	x8, [x19, 14960]
	ldr	w3, [x0, 1592]
	mov	w0, 4000
	ldr	w5, [x2, 3240]
	ldr	w6, [x2, 3236]
	umull	x1, w3, w1
	add	w3, w5, 1
	ldr	w5, [x2, 3224]
	add	x1, x9, x1
	add	w6, w6, 1
	cmp	w6, 1
	ccmp	w5, wzr, 0, ne
	ldr	w1, [x1, 28]
	str	w3, [x2, 3240]
	ldr	w3, [x2, 3228]
	umull	x0, w1, w0
	str	w6, [x2, 3236]
	add	x0, x8, x0
	str	w5, [x2, 3244]
	add	x0, x0, 3292
	str	w3, [x2, 3252]
	ldr	w1, [x0, 52]
	str	w1, [x2, 3288]
	ldr	w1, [x0, 56]
	str	w1, [x2, 3292]
	bne	.L469
	ldr	w5, [x2, 3248]
	add	w5, w5, 2
	str	w5, [x2, 3244]
.L469:
	cmp	w6, 1
	add	x1, x2, 3232
	beq	.L477
	ldrb	w4, [x1, 80]
	cmp	w4, 1
	ldr	x4, [x1, 48]
	add	x4, x4, x5, uxtw
	str	x4, [x1, 40]
	beq	.L478
.L471:
	strb	wzr, [x2, 3312]
	add	x1, x2, 3232
	add	x2, x4, x3, uxtw
	ldr	w3, [x0, 76]
	lsr	x2, x2, 1
	ldr	w4, [x0, 52]
	sub	x3, x2, x3
	mul	x3, x3, x4
	str	x3, [x1, 24]
	ldr	w0, [x0, 76]
	str	w5, [x1, 16]
	sub	x2, x2, x0
	str	x2, [x1, 32]
.L466:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L477:
	mov	x4, 0
	str	xzr, [x2, 3272]
	str	xzr, [x2, 3280]
	b	.L471
	.p2align 3
.L478:
	str	x4, [x1, 48]
	b	.L471
	.p2align 3
.L476:
	ldr	x2, .LC45
	mov	w3, 1475
	ldr	x1, .LC46
	mov	w0, 0
	bl	dprint_vfmw
	b	.L466
	.size	H264_Sei_Get_Dpb_Output_Time, .-H264_Sei_Get_Dpb_Output_Time
	.align	3
.LC45:
	.xword	.LC30
	.align	3
.LC46:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_Get_Last_IDR_Frame_Info
	.type	H264_Get_Last_IDR_Frame_Info, %function
H264_Get_Last_IDR_Frame_Info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L485
	cmp	w20, 5
	beq	.L486
.L479:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L486:
	ldr	x0, [x19]
	ldr	x0, [x0, 64]
	cmn	x0, #1
	beq	.L479
	ldr	x1, [x19, 27840]
	str	x0, [x19, 27872]
	str	x1, [x19, 27880]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L485:
	ldr	x2, .LC47
	mov	w3, 1543
	ldr	x1, .LC48
	mov	w0, 0
	bl	dprint_vfmw
	b	.L479
	.size	H264_Get_Last_IDR_Frame_Info, .-H264_Get_Last_IDR_Frame_Info
	.align	3
.LC47:
	.xword	.LC30
	.align	3
.LC48:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_Sei_Get_Frame_Pts
	.type	H264_Sei_Get_Frame_Pts, %function
H264_Sei_Get_Frame_Pts:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L494
	add	x2, x19, 24576
	ldr	x3, [x19, 27840]
	ldr	x6, [x19, 27872]
	ldr	x7, [x19, 27880]
	ldr	w4, [x2, 3288]
	ldr	w5, [x2, 3292]
	cbz	w4, .L492
	mov	w1, w4
	mov	w2, w5
	b	.L491
	.p2align 3
.L493:
	mov	w1, w0
.L491:
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	mov	w2, w1
	cbnz	w0, .L493
.L490:
	udiv	w4, w4, w1
	sub	x0, x3, x7
	lsl	w2, w0, 6
	add	x19, x19, 61440
	sub	w2, w2, w0
	lsl	w2, w2, 1
	sub	w0, w2, w0
	lsl	w0, w0, 3
	udiv	w1, w5, w1
	mul	w0, w0, w4
	udiv	w1, w0, w1
	add	x1, x1, x6
	str	x1, [x19, 2624]
.L487:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L492:
	mov	w1, w5
	b	.L490
.L494:
	ldr	x2, .LC49
	mov	w3, 1565
	ldr	x1, .LC50
	mov	w0, 0
	bl	dprint_vfmw
	b	.L487
	.size	H264_Sei_Get_Frame_Pts, .-H264_Sei_Get_Frame_Pts
	.align	3
.LC49:
	.xword	.LC30
	.align	3
.LC50:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckFrameStore
	.type	CheckFrameStore, %function
CheckFrameStore:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x20, 65536
	ldr	w1, [x0, 652]
	cbnz	w1, .L496
	ldr	w1, [x19, 848]
	cmp	w1, 1
	beq	.L497
	ldr	w1, [x0, 1908]
	cbz	w1, .L522
.L497:
	mov	w1, 1
	str	w1, [x0, 652]
.L496:
	ldr	w0, [x0, 1980]
	ldr	w1, [x19, 656]
	bl	FSP_GetLogicFs
	cbz	x0, .L499
	ldrsb	w3, [x0, 1]
	cmp	w3, 3
	ccmp	w3, wzr, 4, ne
	beq	.L523
	ldrb	w2, [x19, 1]
	ldrb	w3, [x19]
	cbz	w2, .L507
	cmp	w3, 1
	beq	.L507
	ldr	w1, [x19]
	mov	w3, 50332416
	and	w1, w1, -16711936
	cmp	w1, w3
	beq	.L524
	cmp	w2, 1
	beq	.L525
	cmp	w2, 2
	beq	.L526
.L505:
	ldr	x1, [x20]
	ldr	w2, [x0, 200]
	mov	w0, 0
	ldr	w3, [x1, 4]
	cmp	w2, w3
	bls	.L518
	ldr	w1, [x1, 684]
	cbz	w1, .L527
.L518:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L522:
	ldr	x1, [x20]
	ldr	w1, [x1, 24]
	cbnz	w1, .L497
	mov	w0, -1
	b	.L518
	.p2align 3
.L523:
	ldr	x1, .LC52
	mov	w0, 1
	ldr	w2, [x19, 656]
	bl	dprint_vfmw
.L501:
	ldr	w0, [x19, 848]
	cmp	w0, 1
	beq	.L508
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L525:
	ldrb	w3, [x19, 3]
	tbz	x3, 0, .L505
	ldr	x1, .LC60
	mov	w0, w2
	bl	dprint_vfmw
	mov	w0, -1
	b	.L518
	.p2align 3
.L526:
	ldrb	w3, [x19, 3]
	tbz	x3, 1, .L505
	ldr	x1, .LC62
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L518
	.p2align 3
.L508:
	mov	w1, 2
	mov	w0, -3
	str	w1, [x19, 848]
	b	.L518
	.p2align 3
.L499:
	ldr	x1, .LC54
	mov	x2, x19
	ldr	w4, [x19, 656]
	mov	w0, 1
	ldr	w3, [x19, 848]
	bl	dprint_vfmw
	b	.L501
	.p2align 3
.L507:
	ldr	x1, .LC56
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L518
.L527:
	ldr	x1, .LC64
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L518
.L524:
	ldrb	w3, [x19, 3]
	mov	w0, 1
	ldr	x1, .LC58
	bl	dprint_vfmw
	mov	w0, -1
	b	.L518
	.size	CheckFrameStore, .-CheckFrameStore
	.align	3
.LC52:
	.xword	.LC51
	.align	3
.LC54:
	.xword	.LC53
	.align	3
.LC56:
	.xword	.LC55
	.align	3
.LC58:
	.xword	.LC57
	.align	3
.LC60:
	.xword	.LC59
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetImagePara
	.type	GetImagePara, %function
GetImagePara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	add	x23, x21, 65536
	bl	_mcount
	add	x26, x21, 24576
	add	x2, x21, 20480
	mov	w3, 2208
	ldr	x7, [x21, 14968]
	ldrb	w0, [x19, 81]
	ldr	w4, [x2, 1592]
	mov	w2, 4000
	ldrb	w1, [x19, 80]
	and	w5, w0, -4
	ldr	x6, [x21, 14960]
	mov	w0, w5
	umull	x3, w4, w3
	ldrb	w4, [x19, 82]
	and	w1, w1, -4
	add	x3, x7, x3
	ldrb	w7, [x19, 5]
	bfi	w4, w7, 1, 1
	ldr	w3, [x3, 28]
	strb	w5, [x19, 81]
	strb	w1, [x19, 80]
	umull	x2, w3, w2
	ldrb	w3, [x19, 1]
	ldr	w5, [x23, 660]
	add	x2, x6, x2
	strb	w4, [x19, 82]
	cmp	w3, 3
	ldr	w4, [x19, 8]
	str	w5, [x19, 124]
	str	w4, [x19, 136]
	bhi	.L529
	ldr	x4, .LC65
	ldrh	w4, [x4,w3,uxtw #1]
	adr	x5, .Lrtx531
	add	x4, x5, w4, sxth #2
	br	x4
.Lrtx531:
	.section	.rodata
	.align	0
	.align	2
.L531:
	.2byte	(.L530 - .Lrtx531) / 4
	.2byte	(.L532 - .Lrtx531) / 4
	.2byte	(.L533 - .Lrtx531) / 4
	.2byte	(.L530 - .Lrtx531) / 4
	.text
	.p2align 3
.L530:
	ldrb	w4, [x19, 704]
	cbnz	w4, .L534
	ldr	w5, [x19, 688]
	ldr	w4, [x19, 680]
	str	w5, [x19, 168]
	ldr	w9, [x19, 684]
	ldr	w6, [x19, 772]
	ldr	w5, [x19, 820]
	cbnz	w4, .L535
	mov	w10, 2
	mov	w8, 3
.L536:
	ldr	w7, [x19, 764]
	ldr	w4, [x19, 812]
	cmp	w7, w4
	beq	.L594
	cset	w4, le
.L547:
	add	x26, x21, 24576
	ldrb	w7, [x26, 3220]
	cmp	w7, 3
	beq	.L563
	cmp	w7, 4
	mov	w7, 0
	csel	w4, w4, w7, ne
.L548:
	bfi	w0, w4, 4, 2
	bfi	w1, w9, 0, 2
	bfi	w0, w8, 2, 2
	strb	w1, [x19, 80]
	bfi	w0, w10, 0, 2
	strb	w0, [x19, 81]
	stp	w6, w5, [x19, 72]
.L529:
	ldrb	w1, [x2, 18]
	mov	w4, 0
	str	w1, [x19, 412]
	str	w1, [x19, 416]
	ldrb	w1, [x2, 22]
	cbz	w1, .L549
	ldr	w4, [x2, 3332]
.L549:
	str	w4, [x19, 424]
	mov	w1, 1
	str	w1, [x19, 420]
	ldr	x1, [x21]
	ldr	w1, [x1, 644]
	str	w1, [x19, 140]
	ldr	x1, [x21]
	ldr	w1, [x1, 648]
	str	w1, [x19, 144]
	ldr	x1, [x21]
	ldr	w1, [x1, 652]
	str	w1, [x19, 148]
	ldr	x1, [x21]
	ldr	w1, [x1, 24]
	cbz	w1, .L550
	ldrb	w1, [x19, 704]
	cbz	w1, .L595
.L550:
	ldr	x0, [x19, 600]
	cmn	x0, #1
	beq	.L552
	ldr	w0, [x26, 3708]
	cbz	w0, .L552
	mov	w25, -1
	mov	x24, -2
	mov	w20, 0
	.p2align 2
.L555:
	add	x22, x21, x20, sxtw 3
	ldr	x0, [x22, 27896]
	cbz	x0, .L554
	ldr	w1, [x0, 656]
	ldr	w0, [x23, 1980]
	bl	FSP_GetLogicFs
	cbz	x0, .L554
	ldrsb	w0, [x0, 1]
	cmp	w0, 3
	ccmp	w0, wzr, 4, ne
	beq	.L554
	ldr	x0, [x22, 27896]
	ldr	x0, [x0, 600]
	cmp	x0, x24
	bcs	.L554
	mov	w25, w20
	mov	x24, x0
	.p2align 2
.L554:
	ldr	w0, [x26, 3708]
	add	w20, w20, 1
	cmp	w0, w20
	bhi	.L555
	cmn	w25, #1
	beq	.L552
	ldr	x1, [x19, 600]
	cmp	x1, x24
	bhi	.L596
.L552:
	ldrsb	w0, [x26, 3184]
	cbz	w0, .L556
	ldr	w0, [x26, 3200]
	cmp	w0, 3
	beq	.L597
	cmp	w0, 4
	beq	.L598
	cmp	w0, 5
	beq	.L599
	str	wzr, [x19, 292]
	mov	w0, 0
	ldr	x1, .LC69
	ldr	w2, [x26, 3200]
	bl	dprint_vfmw
	.p2align 2
.L556:
	ldr	w1, [x19, 656]
	ldr	w0, [x23, 1980]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L528
	ldr	x3, .LC70
	mov	x2, 640
	add	x1, x19, 16
	ldr	x3, [x3, 104]
	blr	x3
	str	wzr, [x20, 296]
	mov	w2, 4
	mov	w1, 1
	ldrb	w0, [x19, 704]
	strb	w1, [x20, 291]
	cmp	w0, wzr
	csel	w0, w0, w2, eq
	strb	w0, [x20, 284]
	ldr	w0, [x19, 728]
	str	w0, [x20, 300]
	strb	w1, [x20, 289]
	str	w0, [x20, 304]
	str	w0, [x20, 308]
	ldr	w0, [x19, 736]
	str	w0, [x20, 236]
.L528:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L596:
	ldr	w0, [x23, 1980]
	mov	x2, x24
	bl	IsPtsRewind
	cbnz	w0, .L552
	ldr	x1, .LC67
	mov	x3, x24
	ldr	x2, [x19, 600]
	mov	w0, 29
	add	x21, x21, x25, sxtw 3
	bl	dprint_vfmw
	ldr	x0, [x21, 27896]
	ldr	x1, [x19, 600]
	str	x1, [x0, 600]
	str	x24, [x19, 600]
	b	.L552
	.p2align 3
.L595:
	cmp	w3, 3
	bne	.L550
	and	w0, w0, -4
	strb	w0, [x19, 81]
	b	.L550
	.p2align 3
.L532:
	ldr	w6, [x19, 684]
	mov	w4, 1
	bfi	w0, w4, 2, 2
	ldr	w5, [x19, 688]
	bfi	w1, w6, 0, 2
	ldr	w4, [x19, 772]
	strb	w1, [x19, 80]
	orr	w0, w0, 3
	ldr	x1, [x19, 792]
	add	x26, x21, 24576
	str	w4, [x19, 72]
	mov	w4, 3
	strb	w0, [x19, 81]
	str	w5, [x19, 168]
	str	w4, [x19, 76]
	ldr	w1, [x1, 700]
	str	w1, [x19, 736]
	b	.L529
	.p2align 3
.L533:
	ldr	w6, [x19, 684]
	mov	w4, 2
	bfi	w0, w4, 2, 2
	ldr	w5, [x19, 820]
	bfi	w1, w6, 0, 2
	ldr	w4, [x19, 688]
	strb	w1, [x19, 80]
	orr	w0, w0, 3
	ldr	x1, [x19, 840]
	add	x26, x21, 24576
	str	w4, [x19, 168]
	mov	w4, 3
	strb	w0, [x19, 81]
	str	w5, [x19, 76]
	str	w4, [x19, 72]
	ldr	w1, [x1, 700]
	str	w1, [x19, 736]
	b	.L529
	.p2align 3
.L597:
	mov	w0, 1
	str	w0, [x19, 292]
	b	.L556
	.p2align 3
.L599:
	mov	w0, 3
	str	w0, [x19, 292]
	b	.L556
	.p2align 3
.L534:
	ldr	w7, [x19, 768]
	ldr	w4, [x23, 1976]
	ldr	w10, [x19, 816]
	cmp	w7, w4
	bhi	.L600
	cmp	w4, w10
	bcc	.L540
.L538:
	ldr	w4, [x19, 688]
	mov	w8, 3
	ldr	w9, [x19, 684]
	ldr	w6, [x19, 772]
	ldr	w5, [x19, 820]
	str	w4, [x19, 168]
.L541:
	ldrb	w4, [x19, 3]
	cmp	w4, 1
	beq	.L601
	cmp	w4, 2
	beq	.L602
.L543:
	ldr	w7, [x19, 784]
	mov	w10, 3
	ldr	w4, [x19, 832]
	stp	w6, w5, [x19, 72]
	add	w4, w7, w4
	add	w4, w4, w4, lsr 31
	asr	w4, w4, 1
	str	w4, [x19, 736]
	b	.L536
.L540:
	ldr	w9, [x19, 772]
	mov	w8, 1
	ldr	w5, [x19, 820]
	mov	w6, w9
	str	w7, [x19, 168]
	b	.L541
	.p2align 3
.L598:
	mov	w0, 2
	str	w0, [x19, 292]
	b	.L556
.L563:
	mov	w4, 1
	b	.L548
.L594:
	ldr	w4, [x19, 84]
	cmp	w4, 720
	mov	w4, 1
	bne	.L547
	ldr	w4, [x19, 88]
	cmp	w4, 480
	cset	w4, ne
	b	.L547
.L600:
	cmp	w4, w10
	bcc	.L538
	ldr	w9, [x19, 820]
	mov	w8, 2
	ldr	w6, [x19, 772]
	mov	w5, w9
	str	w10, [x19, 168]
	b	.L541
.L535:
	mov	w10, 3
	mov	w8, w10
	b	.L536
.L601:
	mov	w9, w5
	mov	w8, 2
	str	w10, [x19, 168]
	b	.L543
.L602:
	mov	w9, w6
	mov	w8, 1
	str	w7, [x19, 168]
	b	.L543
	.size	GetImagePara, .-GetImagePara
	.align	3
.LC65:
	.xword	.L531
	.align	3
.LC67:
	.xword	.LC66
	.align	3
.LC69:
	.xword	.LC68
	.align	3
.LC70:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetFrmRepeatCount
	.type	SetFrmRepeatCount, %function
SetFrmRepeatCount:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, [x19]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bls	.L604
	mov	x1, x20
	mov	x0, x19
	bl	SetFrmRepeatCount.part.7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L604:
	str	wzr, [x20, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SetFrmRepeatCount, .-SetFrmRepeatCount
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SplitFrmToFlds
	.type	SplitFrmToFlds, %function
SplitFrmToFlds:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w4, [x19, 705]
	mov	w6, 1
	ldrb	w3, [x19, 706]
	mov	w5, 2
	ldr	w2, [x19, 720]
	ldr	w1, [x19, 724]
	ldr	x0, [x19, 744]
	strb	w4, [x19, 753]
	strb	w3, [x19, 754]
	strb	w6, [x19, 752]
	strb	w4, [x19, 801]
	strb	w3, [x19, 802]
	strb	w5, [x19, 800]
	str	w2, [x19, 768]
	str	w1, [x19, 772]
	str	x0, [x19, 792]
	str	w2, [x19, 816]
	str	w1, [x19, 820]
	str	x0, [x19, 840]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SplitFrmToFlds, .-SplitFrmToFlds
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CombineFldsToFrm
	.type	CombineFldsToFrm, %function
CombineFldsToFrm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 764]
	mov	w5, 3
	ldr	w3, [x19, 768]
	ldr	w2, [x19, 812]
	ldr	w0, [x19, 816]
	cmp	w1, w2
	ldr	x4, [x19, 792]
	add	w0, w3, w0
	ldrb	w3, [x19, 801]
	csel	w1, w1, w2, le
	lsr	w0, w0, 1
	strb	w5, [x19, 704]
	str	w1, [x19, 672]
	str	w1, [x19, 716]
	str	w0, [x19, 720]
	str	x4, [x19, 744]
	cbz	w3, .L608
	ldrb	w1, [x19, 753]
	cbz	w1, .L608
	mov	w1, 1
	strb	w1, [x19, 705]
.L610:
	mov	w2, 0
.L611:
	ldr	w1, [x19, 772]
	strb	w2, [x19, 706]
	cbz	w1, .L612
	ldr	w2, [x19, 820]
	cbz	w2, .L614
	cmp	w1, w2
	csel	w1, w1, w2, cs
.L612:
	str	w1, [x19, 684]
	str	w0, [x19, 688]
	str	w1, [x19, 724]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L608:
	ldr	w1, [x19, 800]
	strb	wzr, [x19, 705]
	tst	w1, 16776960
	beq	.L610
	ldr	w1, [x19, 752]
	mov	w2, 1
	tst	w1, 16776960
	bne	.L611
	b	.L610
	.p2align 3
.L614:
	mov	w1, 0
	str	w0, [x19, 688]
	str	w1, [x19, 684]
	str	w1, [x19, 724]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CombineFldsToFrm, .-CombineFldsToFrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetAPC
	.type	GetAPC, %function
GetAPC:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x22, x1
	mov	x0, x30
	mov	w19, w2
	bl	_mcount
	cbz	x22, .L649
	cmp	w19, 1
	beq	.L629
	cmp	w19, 2
	beq	.L630
	ldr	w23, [x22, 764]
	ldr	w24, [x22, 812]
.L631:
	add	x21, x20, 24576
	ldr	w2, [x21, 3984]
	cbz	w2, .L640
	ldr	w0, [x21, 3728]
	cbz	w0, .L650
	add	x0, x21, 3732
	mov	w19, 0
	b	.L634
	.p2align 3
.L638:
	ldr	w1, [x0], 4
	cbz	w1, .L632
.L634:
	add	w19, w19, 1
	cmp	w19, w2
	bne	.L638
.L640:
	mov	w0, -1
.L644:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L630:
	ldr	w23, [x22, 812]
	mov	w24, w23
	b	.L631
.L650:
	mov	w19, 0
	.p2align 2
.L632:
	add	x0, x20, 65536
	ldr	w1, [x22, 656]
	ldr	w0, [x0, 1980]
	bl	FSP_GetLogicFs
	cbz	x0, .L635
	ldr	x1, [x0, 32]
	cbz	x1, .L635
	add	x20, x20, x19, uxtw 2
	mov	w1, 1
	add	x20, x20, 24576
	mov	w4, 16
	mov	w3, w19
	str	w1, [x20, 3728]
	ldr	x1, .LC74
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x20, 3792]
	mov	w0, 13
	str	w23, [x20, 3856]
	str	w24, [x20, 3920]
	ldr	w2, [x21, 3988]
	cmp	w2, 15
	csinc	w2, w4, w2, hi
	str	w2, [x21, 3988]
	ldr	w2, [x22, 164]
	bl	dprint_vfmw
	str	w19, [x22, 696]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L629:
	ldr	w23, [x22, 764]
	mov	w24, w23
	b	.L631
.L635:
	ldrb	w3, [x22, 2]
	mov	x4, x0
	ldr	x1, .LC76
	mov	x5, 0
	ldr	w2, [x22, 656]
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L644
.L649:
	ldr	x2, .LC71
	mov	w3, 2539
	ldr	x1, .LC72
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L644
	.size	GetAPC, .-GetAPC
	.align	3
.LC71:
	.xword	.LC30
	.align	3
.LC72:
	.xword	.LC32
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SlidingWinMark
	.type	SlidingWinMark, %function
SlidingWinMark:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 24576
	add	x0, x19, 16384
	ldr	w2, [x1, 3716]
	ldr	w0, [x0, 1836]
	ldr	w1, [x1, 3712]
	sub	w0, w0, w2
	cmp	w1, w0
	bne	.L651
	mov	x0, x19
	bl	SlidingWinMark.part.8
.L651:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SlidingWinMark, .-SlidingWinMark
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DumpDPB
	.type	DumpDPB, %function
DumpDPB:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC77
	ldr	w0, [x0]
	tbz	x0, 14, .L653
	add	x21, x22, 24576
	ldr	w0, [x21, 3708]
	cbz	w0, .L659
	ldr	x20, .LC80
	mov	w19, 0
	.p2align 2
.L658:
	add	x3, x22, x19, uxtw 3
	mov	w2, w19
	mov	x1, x20
	mov	w0, 14
	add	w19, w19, 1
	ldr	x3, [x3, 27896]
	ldrb	w5, [x3, 2]
	ldr	w4, [x3, 672]
	ldr	w3, [x3, 660]
	bl	dprint_vfmw
	ldr	w0, [x21, 3708]
	cmp	w0, w19
	bhi	.L658
.L659:
	ldr	x25, .LC78
	mov	w0, 14
	mov	x1, x25
	bl	dprint_vfmw
	ldr	w0, [x21, 3712]
	cbz	w0, .L657
	ldr	x24, .LC82
	mov	w19, 0
	ldr	x23, .LC84
	.p2align 2
.L660:
	add	x20, x22, x19, uxtw 3
	mov	w2, w19
	mov	x1, x24
	mov	w0, 14
	ldr	x3, [x20, 28024]
	ldrb	w5, [x3, 2]
	ldr	w4, [x3, 672]
	ldr	w3, [x3, 660]
	bl	dprint_vfmw
	ldr	x3, [x20, 28024]
	mov	w2, w19
	mov	x1, x23
	mov	w0, 14
	add	w19, w19, 1
	ldr	w3, [x3, 716]
	bl	dprint_vfmw
	ldr	w0, [x21, 3712]
	cmp	w0, w19
	bhi	.L660
.L657:
	mov	x1, x25
	mov	w0, 14
	bl	dprint_vfmw
.L653:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	DumpDPB, .-DumpDPB
	.align	3
.LC77:
	.xword	g_PrintEnable
	.align	3
.LC78:
	.xword	.LC6
	.align	3
.LC80:
	.xword	.LC79
	.align	3
.LC82:
	.xword	.LC81
	.align	3
.LC84:
	.xword	.LC83
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdateCurrFrameInfo
	.type	UpdateCurrFrameInfo, %function
UpdateCurrFrameInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 61440
	mov	w2, 3
	ldr	x19, [x1, 2680]
	ldrb	w3, [x1, 2026]
	strb	w3, [x19]
	ldrb	w3, [x1, 2028]
	cbnz	w3, .L667
	ldrb	w2, [x1, 2029]
	mov	w0, 3
	cmp	w2, wzr
	csel	w2, w2, w0, eq
.L667:
	add	x3, x1, 2024
	strb	w2, [x19, 2]
	mov	w2, 3
	ldr	w0, [x3, 672]
	str	w0, [x19, 660]
	ldr	w0, [x3, 708]
	str	w0, [x19, 688]
	ldr	w0, [x3, 700]
	str	w0, [x19, 684]
	ldr	w0, [x3, 684]
	str	w0, [x19, 672]
	ldr	w0, [x3, 732]
	str	w0, [x19, 692]
	ldr	w0, [x3, 676]
	str	w0, [x19, 668]
	ldrb	w0, [x3, 9]
	str	w0, [x19, 680]
	ldrb	w0, [x3, 7]
	cmp	w0, 1
	csel	w0, w2, wzr, eq
	strb	w0, [x19, 3]
	ldrb	w4, [x3, 3]
	cmp	w4, 1
	beq	.L670
	cbz	w4, .L671
	cmp	w4, 2
	bne	.L666
	str	x19, [x19, 840]
	mov	w5, 1
	strb	w5, [x19, 800]
	ldrb	w5, [x3, 4]
	strb	w5, [x19, 801]
	ldrb	w5, [x3, 5]
	strb	w5, [x19, 802]
	ldr	w5, [x3, 692]
	str	w5, [x19, 812]
	ldr	w6, [x3, 700]
	str	w6, [x19, 820]
	ldr	w5, [x3, 708]
	str	w5, [x19, 816]
	str	wzr, [x19, 680]
	ldrb	w7, [x3, 1]
	cbz	w7, .L693
	ldr	w4, [x19, 768]
	orr	w0, w0, 2
	strb	w2, [x19, 1]
	mov	w2, 0
	add	w5, w5, w4
	str	w5, [x19, 688]
	str	w5, [x19, 720]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w0, w0, w2, eq
	strb	w0, [x19, 3]
	ldr	x0, [x1, 2624]
	cmn	x0, #1
	beq	.L679
	ldr	x2, [x19, 600]
	cmn	x2, #1
	beq	.L694
.L679:
	ldr	w2, [x19, 772]
.L697:
	cmp	w2, w6
	mov	x0, x19
	csel	w6, w2, w6, cs
	str	w6, [x19, 684]
	ldr	w1, [x1, 2708]
	str	w1, [x19, 672]
	bl	CombineFldsToFrm
.L666:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L671:
	strb	w2, [x19, 1]
	add	x1, x1, 2040
	strb	wzr, [x19, 704]
	mov	x2, 640
	str	x19, [x19, 744]
	add	x0, x19, 16
	ldrb	w23, [x3, 4]
	strb	w23, [x19, 705]
	ldrb	w22, [x3, 5]
	strb	w22, [x19, 706]
	ldr	w4, [x3, 688]
	str	w4, [x19, 716]
	ldr	w20, [x3, 700]
	str	w20, [x19, 724]
	ldr	w21, [x3, 708]
	str	w21, [x19, 720]
	ldr	w4, [x3, 692]
	str	w4, [x19, 764]
	ldr	w3, [x3, 696]
	str	w3, [x19, 812]
	bl	memcpy
	strb	w23, [x19, 753]
	strb	w22, [x19, 754]
	mov	w1, 1
	strb	w23, [x19, 801]
	mov	w0, 2
	strb	w1, [x19, 752]
	strb	w22, [x19, 802]
	strb	w0, [x19, 800]
	str	w21, [x19, 768]
	str	w20, [x19, 772]
	str	x19, [x19, 792]
	str	w21, [x19, 816]
	str	w20, [x19, 820]
	str	x19, [x19, 840]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L670:
	strb	w4, [x19, 752]
	str	x19, [x19, 792]
	ldrb	w5, [x3, 4]
	strb	w5, [x19, 753]
	ldrb	w5, [x3, 5]
	strb	w5, [x19, 754]
	ldr	w5, [x3, 692]
	str	w5, [x19, 764]
	ldr	w6, [x3, 700]
	str	w6, [x19, 772]
	ldr	w5, [x3, 708]
	str	w5, [x19, 768]
	str	wzr, [x19, 680]
	ldrb	w7, [x3, 1]
	cbz	w7, .L695
	ldr	w4, [x19, 816]
	orr	w0, w0, 1
	strb	w2, [x19, 1]
	mov	w2, 0
	add	w5, w5, w4
	str	w5, [x19, 688]
	str	w5, [x19, 720]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w0, w0, w2, eq
	strb	w0, [x19, 3]
	ldr	x0, [x1, 2624]
	cmn	x0, #1
	beq	.L675
	ldr	x2, [x19, 600]
	cmn	x2, #1
	beq	.L696
.L675:
	ldr	w2, [x19, 820]
	mov	x0, x19
	cmp	w2, w6
	csel	w6, w2, w6, cs
	str	w6, [x19, 684]
	ldr	w1, [x1, 2708]
	str	w1, [x19, 672]
	bl	CombineFldsToFrm
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L693:
	strb	w4, [x19, 1]
	mov	x2, 640
	str	w5, [x19, 688]
	add	x1, x1, 2040
	str	w5, [x19, 720]
	add	x0, x19, 16
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	csel	w7, wzr, w4, ne
	strb	w7, [x19, 3]
	bl	memcpy
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L695:
	strb	w4, [x19, 1]
	mov	x2, 640
	str	w5, [x19, 688]
	add	x1, x1, 2040
	str	w5, [x19, 720]
	add	x0, x19, 16
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	cset	w3, eq
	strb	w3, [x19, 3]
	bl	memcpy
	b	.L666
	.p2align 3
.L696:
	str	x0, [x19, 600]
	b	.L675
	.p2align 3
.L694:
	str	x0, [x19, 600]
	ldr	w2, [x19, 772]
	b	.L697
	.size	UpdateCurrFrameInfo, .-UpdateCurrFrameInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SimpleSlideDPB
	.type	SimpleSlideDPB, %function
SimpleSlideDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 24576
	ldr	w1, [x0, 3708]
	ldr	w0, [x0, 3704]
	cmp	w1, w0
	bcs	.L704
.L699:
	add	x19, x19, 61440
	ldr	w0, [x19, 2704]
	strb	wzr, [x19, 2028]
	cbz	w0, .L698
	mov	w0, 1
	strb	w0, [x19, 2029]
.L698:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L704:
	ldr	x1, [x19, 27896]
	mov	x0, x19
	bl	UnMarkFrameStoreRef
	mov	w1, 0
	mov	x0, x19
	bl	RemoveFrameStoreOutDPB
	b	.L699
	.size	SimpleSlideDPB, .-SimpleSlideDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_ArrangeVahbMem
	.type	H264_ArrangeVahbMem, %function
H264_ArrangeVahbMem:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w20, w2
	mov	w19, w1
	mov	w22, w4
	bl	_mcount
	mov	w0, 8160
	sub	w2, w20, #32
	sub	w1, w19, #32
	cmp	w2, w0
	ccmp	w1, w0, 2, ls
	bhi	.L706
	ldr	x3, .LC85
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, [x21]
	stp	w19, w20, [x29, 60]
	stp	w19, w20, [x29, 68]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L722
	add	x0, x21, 24576
	mov	w1, 5
	sxtb	w4, w22
	strb	w1, [x29, 58]
	ldr	w0, [x0, 3704]
	add	w0, w0, 1
	strb	w0, [x29, 57]
.L715:
	mov	w0, 63
	strb	w4, [x29, 59]
	cmp	w19, w0
	ccmp	w20, w0, 0, hi
	bls	.L723
	add	x19, x21, 65536
	add	x1, x29, 56
	ldr	w0, [x19, 1980]
	bl	FSP_ConfigInstance
	cbnz	w0, .L711
	ldr	x1, [x21]
	add	x3, x29, 52
	ldr	w0, [x19, 1980]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	mov	w1, w0
	beq	.L724
	mov	w0, 1
	cbnz	w1, .L725
.L716:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L722:
	mov	w1, 1
	mov	w0, 5
	strb	w1, [x29, 57]
	mov	w4, 1
	strb	w0, [x29, 58]
	b	.L715
	.p2align 3
.L706:
	ldr	x1, .LC87
.L719:
	mov	w3, w20
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
.L726:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L723:
	ldr	x1, .LC89
	b	.L719
	.p2align 3
.L711:
	ldr	x1, .LC93
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L716
	.p2align 3
.L725:
	ldr	x1, .LC91
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L726
.L724:
	add	x0, x21, 8
	bl	ResetVoQueue
	mov	w0, -20
	b	.L726
	.size	H264_ArrangeVahbMem, .-H264_ArrangeVahbMem
	.align	3
.LC85:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC91:
	.xword	.LC90
	.align	3
.LC93:
	.xword	.LC92
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RepairList
	.type	RepairList, %function
RepairList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L759
	add	x7, x19, 20480
	ldrb	w2, [x7, 1584]
	cmp	w2, 1
	beq	.L747
	cbz	w2, .L732
	cmp	w2, 2
	mov	w0, 0
	bne	.L760
.L750:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L760:
	ldr	x1, .LC97
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L732:
	mov	w11, 1
.L731:
	add	x6, x19, 28672
	add	x7, x7, 1624
	add	x6, x6, 24
	mov	x8, 0
	mov	x9, 0
	mov	w2, 0
	mov	w13, 1
	add	x12, x19, 61440
	.p2align 2
.L743:
	ldr	w0, [x7]
	cbz	w0, .L733
	ldr	x1, [x6]
	cbnz	x1, .L761
	sub	w3, w0, #1
	add	x10, x8, 3588
	add	x0, x6, 8
	add	x5, x10, x3, uxtw
	add	x5, x19, x5, lsl 3
	b	.L736
	.p2align 3
.L737:
	ldr	x4, [x0], 8
	cbnz	x4, .L734
.L736:
	cmp	x0, x5
	bne	.L737
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L762
	ldr	x9, [x12, 2680]
	add	x9, x9, 704
.L746:
	add	x3, x10, x3, uxtw
	mov	x0, x6
	add	x3, x19, x3, lsl 3
	cbz	x1, .L763
	.p2align 2
.L739:
	add	x0, x0, 8
	cmp	x0, x3
	beq	.L740
.L764:
	ldr	x1, [x0]
	cbnz	x1, .L739
.L763:
	str	x9, [x0]
	add	x0, x0, 8
	cmp	x0, x3
	bne	.L764
	.p2align 2
.L740:
	add	w2, w2, 1
	add	x7, x7, 4
	cmp	w2, w11
	add	x6, x6, 264
	add	x8, x8, 33
	bcc	.L743
.L766:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L733:
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L765
	str	w13, [x7]
	add	w2, w2, 1
	cmp	w2, w11
	add	x7, x7, 4
	ldr	x0, [x12, 2680]
	add	x8, x8, 33
	add	x0, x0, 704
	str	x0, [x6]
	add	x6, x6, 264
	bcc	.L743
	b	.L766
.L761:
	sub	w3, w0, #1
	mov	x4, x1
	add	x10, x8, 3588
	.p2align 2
.L734:
	mov	x9, x4
	b	.L746
.L747:
	mov	w11, 2
	b	.L731
.L765:
	ldr	x1, .LC101
	mov	w3, 0
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L762:
	ldr	x1, .LC99
	mov	w3, 0
	mov	x2, x9
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L759:
	ldr	x2, .LC94
	mov	w3, 4333
	ldr	x1, .LC95
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L750
	.size	RepairList, .-RepairList
	.align	3
.LC94:
	.xword	.LC30
	.align	3
.LC95:
	.xword	.LC32
	.align	3
.LC97:
	.xword	.LC96
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC101:
	.xword	.LC100
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetShortTermPicPoint
	.type	GetShortTermPicPoint, %function
GetShortTermPicPoint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 20480
	mov	w5, 0
	ldrb	w1, [x0, 1585]
	cbz	w1, .L768
	ldrb	w0, [x0, 1586]
	mov	w5, 2
	cmp	w0, wzr
	csinc	w5, w5, wzr, ne
.L768:
	add	x0, x20, 24576
	ldr	w2, [x0, 3712]
	cbz	w2, .L776
	sub	w2, w2, #1
	add	x0, x0, 3448
	add	x2, x2, 3504
	add	x4, x20, x2, lsl 3
	b	.L773
	.p2align 3
.L786:
	cmp	w3, 3
	beq	.L785
.L771:
	add	x0, x0, 8
	cmp	x0, x4
	beq	.L776
.L773:
	ldr	x2, [x0]
	ldrb	w3, [x2, 2]
	cbz	w5, .L786
	tbz	x3, 0, .L772
	ldr	w6, [x2, 752]
	and	w6, w6, 16776960
	cmp	w6, 65536
	beq	.L787
.L772:
	tbz	x3, 1, .L771
	ldr	w3, [x2, 800]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L771
	ldr	w1, [x2, 808]
	cmp	w19, w1
	bne	.L771
	add	x0, x2, 800
	b	.L769
	.p2align 3
.L787:
	ldr	w1, [x2, 760]
	cmp	w1, w19
	bne	.L772
	add	x0, x2, 752
	b	.L769
	.p2align 3
.L785:
	ldr	w3, [x2, 704]
	and	w3, w3, 16776960
	cmp	w3, 65536
	bne	.L771
	ldr	w1, [x2, 712]
	cmp	w19, w1
	bne	.L771
	add	x0, x2, 704
	b	.L769
	.p2align 3
.L776:
	mov	x0, 0
.L769:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetShortTermPicPoint, .-GetShortTermPicPoint
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetLongTermPicPoint
	.type	GetLongTermPicPoint, %function
GetLongTermPicPoint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	add	x0, x20, 20480
	mov	w5, 0
	ldrb	w1, [x0, 1585]
	cbz	w1, .L789
	ldrb	w0, [x0, 1586]
	mov	w5, 2
	cmp	w0, wzr
	csinc	w5, w5, wzr, ne
.L789:
	add	x0, x20, 24576
	ldr	w2, [x0, 3716]
	cbz	w2, .L797
	sub	w2, w2, #1
	add	x0, x0, 3576
	add	x2, x2, 3520
	add	x4, x20, x2, lsl 3
	b	.L794
	.p2align 3
.L807:
	cmp	w3, 3
	beq	.L806
.L792:
	add	x0, x0, 8
	cmp	x0, x4
	beq	.L797
.L794:
	ldr	x2, [x0]
	ldrb	w3, [x2, 2]
	cbz	w5, .L807
	tbz	x3, 0, .L793
	ldr	w6, [x2, 752]
	and	w6, w6, 16776960
	cmp	w6, 256
	beq	.L808
.L793:
	tbz	x3, 1, .L792
	ldr	w3, [x2, 800]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L792
	ldr	w1, [x2, 804]
	cmp	w19, w1
	bne	.L792
	add	x0, x2, 800
	b	.L790
	.p2align 3
.L808:
	ldr	w1, [x2, 756]
	cmp	w1, w19
	bne	.L793
	add	x0, x2, 752
	b	.L790
	.p2align 3
.L806:
	ldr	w3, [x2, 704]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L792
	ldr	w1, [x2, 708]
	cmp	w19, w1
	bne	.L792
	add	x0, x2, 704
	b	.L790
	.p2align 3
.L797:
	mov	x0, 0
.L790:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetLongTermPicPoint, .-GetLongTermPicPoint
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReorderSTList
	.type	ReorderSTList, %function
ReorderSTList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w22, w3
	mov	x21, x4
	mov	w20, w2
	mov	x19, x1
	bl	_mcount
	mov	w1, w22
	mov	x0, x23
	bl	GetShortTermPicPoint
	ldr	w5, [x21]
	add	w2, w20, 1
	cmp	w2, w5
	ble	.L810
	mov	w1, w2
	.p2align 2
.L811:
	add	x5, x19, x1, sxtw 3
	ldr	x5, [x5, -8]
	str	x5, [x19, w1, sxtw 3]
	sub	w1, w1, #1
	ldr	w5, [x21]
	cmp	w5, w1
	blt	.L811
.L810:
	add	w1, w5, 1
	str	w1, [x21]
	str	x0, [x19, w5, sxtw 3]
	ldr	w0, [x21]
	cmp	w2, w0
	mov	w4, w0
	blt	.L809
	.p2align 2
.L819:
	ldr	x1, [x19, w0, sxtw 3]
	add	w0, w0, 1
	cbz	x1, .L813
	ldrb	w5, [x1, 1]
	cbnz	w5, .L814
	ldr	w5, [x1, 8]
	cmp	w22, w5
	beq	.L813
.L814:
	str	x1, [x19, w4, sxtw 3]
	add	w4, w4, 1
.L813:
	cmp	w2, w0
	bge	.L819
.L809:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ReorderSTList, .-ReorderSTList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReorderLTList
	.type	ReorderLTList, %function
ReorderLTList:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	w22, w3
	mov	x21, x4
	mov	w20, w2
	mov	x19, x1
	bl	_mcount
	mov	w1, w22
	mov	x0, x23
	bl	GetLongTermPicPoint
	ldr	w5, [x21]
	add	w2, w20, 1
	cmp	w2, w5
	ble	.L824
	mov	w1, w2
	.p2align 2
.L825:
	add	x5, x19, x1, sxtw 3
	ldr	x5, [x5, -8]
	str	x5, [x19, w1, sxtw 3]
	sub	w1, w1, #1
	ldr	w5, [x21]
	cmp	w5, w1
	blt	.L825
.L824:
	add	w1, w5, 1
	str	w1, [x21]
	str	x0, [x19, w5, sxtw 3]
	ldr	w0, [x21]
	cmp	w2, w0
	mov	w4, w0
	blt	.L823
	.p2align 2
.L835:
	ldr	x1, [x19, w0, sxtw 3]
	add	w0, w0, 1
	cbz	x1, .L827
	ldrb	w5, [x1, 1]
	cbz	w5, .L828
	ldr	w5, [x1, 4]
	cmp	w22, w5
	beq	.L827
.L828:
	str	x1, [x19, w4, sxtw 3]
	add	w4, w4, 1
.L827:
	cmp	w2, w0
	bge	.L835
.L823:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ReorderLTList, .-ReorderLTList
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReorderRefPiclist
	.type	ReorderRefPiclist, %function
ReorderRefPiclist:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	mov	w21, w3
	mov	x25, x4
	mov	x28, x5
	str	x6, [x29, 104]
	bl	_mcount
	add	x0, x20, 20480
	str	wzr, [x29, 124]
	ldrb	w1, [x0, 1585]
	ldr	w2, [x0, 1592]
	cbz	w1, .L841
	mov	w1, 2208
	ldr	w26, [x0, 1600]
	ldr	x3, [x20, 14968]
	mov	w23, 2
	umull	x0, w2, w1
	ldr	x2, [x20, 14960]
	lsl	w26, w26, 1
	add	x1, x3, x0
	mov	w0, 4000
	add	w26, w26, 1
	ldr	w1, [x1, 28]
	umull	x0, w1, w0
	add	x0, x2, x0
	ldr	w0, [x0, 2196]
	add	w0, w0, 4
	lsl	w23, w23, w0
.L851:
	cmn	w21, #2
	beq	.L840
	ldr	w3, [x25]
	cmp	w3, 3
	beq	.L840
	add	w24, w21, 1
	mov	w27, w26
	lsl	x24, x24, 2
	mov	x19, 0
	b	.L844
	.p2align 3
.L845:
	ldr	x3, [x29, 104]
	ldr	w3, [x3, x19]
	bl	ReorderLTList
	cmp	x24, x19
	add	x19, x19, 4
	beq	.L840
.L850:
	ldr	w3, [x25, x19]
	cmp	w3, 3
	beq	.L840
.L844:
	cmp	w3, 1
	add	x4, x29, 124
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	bhi	.L845
	ldr	w0, [x28, x19]
	cbnz	w3, .L846
	mvn	w0, w0
	add	w27, w27, w0
	add	w0, w27, w23
	cmp	w27, wzr
	csel	w27, w0, w27, lt
.L847:
	cmp	w26, w27
	sub	w3, w27, w23
	csel	w3, w3, w27, lt
	add	x4, x29, 124
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	bl	ReorderSTList
	cmp	x24, x19
	add	x19, x19, 4
	bne	.L850
.L840:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L846:
	add	w0, w0, 1
	add	w27, w27, w0
	cmp	w23, w27
	sub	w0, w27, w23
	csel	w27, w0, w27, le
	b	.L847
	.p2align 3
.L841:
	mov	w1, 2208
	ldr	w26, [x0, 1600]
	ldr	x3, [x20, 14968]
	mov	w23, 1
	umull	x0, w2, w1
	ldr	x2, [x20, 14960]
	add	x1, x3, x0
	mov	w0, 4000
	ldr	w1, [x1, 28]
	umull	x0, w1, w0
	add	x0, x2, x0
	ldr	w0, [x0, 2196]
	add	w0, w0, 4
	lsl	w23, w23, w0
	b	.L851
	.size	ReorderRefPiclist, .-ReorderRefPiclist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReorderListX
	.type	ReorderListX, %function
ReorderListX:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 20480
	bl	_mcount
	ldrb	w0, [x19, 1584]
	cmp	w0, 2
	beq	.L859
	ldrb	w1, [x19, 796]
	cbnz	w1, .L871
.L862:
	ldr	w1, [x19, 1636]
	cmp	w0, 1
	add	w0, w1, 1
	str	w0, [x19, 1624]
	bne	.L859
	ldrb	w0, [x19, 797]
	cbnz	w0, .L872
.L864:
	ldr	w0, [x19, 1640]
	add	w0, w0, 1
	str	w0, [x19, 1628]
.L859:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L871:
	add	x1, x20, 28672
	ldr	w3, [x19, 1636]
	mov	x0, x20
	add	x6, x19, 1328
	add	x5, x19, 1064
	add	x4, x19, 800
	add	x2, x19, 1624
	add	x1, x1, 24
	bl	ReorderRefPiclist
	ldrb	w0, [x19, 1584]
	b	.L862
	.p2align 3
.L872:
	add	x1, x20, 28672
	ldr	w3, [x19, 1640]
	add	x6, x19, 1456
	add	x5, x19, 1196
	add	x4, x19, 932
	add	x2, x19, 1628
	add	x1, x1, 288
	mov	x0, x20
	bl	ReorderRefPiclist
	b	.L864
	.size	ReorderListX, .-ReorderListX
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GenPiclistfromFrmlist
	.type	GenPiclistfromFrmlist, %function
GenPiclistfromFrmlist:
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
	cbnz	w23, .L895
	cmp	w21, 1
	ldr	x23, .LC103
	beq	.L935
.L875:
	cmp	w21, 2
	bne	.L884
	mov	w21, 0
	mov	w20, 0
	.p2align 2
.L886:
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	bcs	.L884
.L936:
	cmp	w21, w22
	bcc	.L919
	b	.L891
	.p2align 3
.L887:
	add	w21, w21, 1
	cmp	w22, w21
	bls	.L891
.L919:
	ldr	x0, [x19, w21, uxtw 3]
	add	x26, x19, x21, uxtw 3
	ldrb	w1, [x0, 1]
	tbz	x1, 1, .L887
	add	x0, x0, 800
	blr	x23
	cbz	w0, .L887
	ldr	w1, [x24]
	add	w21, w21, 1
	ldr	x0, [x26]
	add	x0, x0, 800
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
.L891:
	cmp	w20, w22
	bcc	.L918
	b	.L886
	.p2align 3
.L892:
	add	w20, w20, 1
	cmp	w22, w20
	bls	.L886
.L918:
	ldr	x0, [x19, w20, uxtw 3]
	add	x26, x19, x20, uxtw 3
	ldrb	w1, [x0, 1]
	tbz	x1, 0, .L892
	add	x0, x0, 752
	blr	x23
	cbz	w0, .L892
	ldr	w1, [x24]
	add	w20, w20, 1
	ldr	x0, [x26]
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	add	x0, x0, 752
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	bcc	.L936
.L884:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L895:
	cmp	w21, 1
	ldr	x23, .LC102
	bne	.L875
.L935:
	mov	w21, 0
	mov	w20, 0
	.p2align 2
.L876:
	cmp	w20, w22
	ccmp	w21, w22, 0, cs
	bcs	.L884
	cmp	w20, w22
	bcc	.L917
	b	.L934
	.p2align 3
.L877:
	add	w20, w20, 1
	cmp	w20, w22
	bcs	.L934
.L917:
	ldr	x0, [x19, w20, uxtw 3]
	add	x26, x19, x20, uxtw 3
	ldrb	w1, [x0, 1]
	tbz	x1, 0, .L877
	add	x0, x0, 752
	blr	x23
	cbz	w0, .L877
	ldr	w1, [x24]
	add	w20, w20, 1
	ldr	x0, [x26]
	add	x0, x0, 752
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	.p2align 2
.L934:
	cmp	w21, w22
	bcs	.L876
	ldr	x0, [x19, w21, uxtw 3]
	add	x26, x19, x21, uxtw 3
	ldrb	w1, [x0, 1]
	tbnz	x1, 1, .L937
.L882:
	add	w21, w21, 1
	b	.L934
	.p2align 3
.L937:
	add	x0, x0, 800
	blr	x23
	cbz	w0, .L882
	ldr	w1, [x24]
	add	w21, w21, 1
	ldr	x0, [x26]
	add	x0, x0, 800
	str	x0, [x25, w1, uxtw 3]
	ldr	w0, [x24]
	add	w0, w0, 1
	str	w0, [x24]
	b	.L876
	.size	GenPiclistfromFrmlist, .-GenPiclistfromFrmlist
	.align	3
.LC102:
	.xword	IsLTRefFlg
	.align	3
.LC103:
	.xword	IsSTRefFlg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitListX
	.type	InitListX, %function
InitListX:
	stp	x29, x30, [sp, -480]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1059
	add	x20, x19, 20480
	add	x22, x19, 61440
	ldrb	w0, [x20, 1584]
	cbz	w0, .L1060
	ldrb	w0, [x22, 2027]
	add	x21, x19, 24576
	cbz	w0, .L961
	ldr	w0, [x21, 3712]
	cbz	w0, .L1061
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 3504
	add	x0, x21, 3448
	add	x3, x19, x3, lsl 3
	.p2align 2
.L980:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cbz	w2, .L979
	ldr	w4, [x1, 672]
	add	x2, x29, 480
	ldr	w5, [x22, 2708]
	add	x2, x2, x23, uxtw 3
	sub	x2, x2, #4096
	cmp	w5, w4
	blt	.L979
	add	w23, w23, 1
	str	x1, [x2, 3712]
.L979:
	cmp	x0, x3
	bne	.L980
	add	x26, x29, 96
	ldr	x3, .LC114
	mov	w2, 8
	mov	w1, w23
	mov	x0, x26
	bl	qsort
	ldr	w24, [x21, 3712]
	cbz	w24, .L981
.L1005:
	sub	w1, w24, #1
	add	x0, x21, 3448
	add	x1, x1, 3504
	mov	w25, w23
	add	x1, x19, x1, lsl 3
	.p2align 2
.L983:
	ldr	x2, [x0]
	add	x0, x0, 8
	ldrb	w3, [x2, 1]
	cbz	w3, .L982
	ldr	w4, [x2, 672]
	add	x3, x29, 480
	ldr	w5, [x22, 2708]
	add	x3, x3, x25, uxtw 3
	sub	x3, x3, #4096
	cmp	w5, w4
	bge	.L982
	add	w25, w25, 1
	str	x2, [x3, 3712]
.L982:
	cmp	x0, x1
	bne	.L983
	sub	w24, w25, w23
	ldr	x3, .LC115
	mov	w2, 8
	mov	w1, w24
	add	x0, x26, x23, uxtw 3
	bl	qsort
	cbz	w23, .L984
.L1004:
	mov	x0, 0
	.p2align 2
.L985:
	add	w1, w24, w0
	add	x3, x29, 480
	ldr	x2, [x26, x0, lsl 3]
	add	x0, x0, 1
	add	x1, x3, x1, lsl 3
	cmp	w23, w0
	str	x2, [x1, -256]
	bhi	.L985
.L984:
	cmp	w25, w23
	bls	.L986
	mov	w0, w23
	.p2align 2
.L987:
	add	x2, x29, 480
	sub	w1, w0, w23
	add	x2, x2, x0, uxtw 3
	add	x3, x29, 480
	sub	x2, x2, #4096
	add	x1, x3, x1, lsl 3
	add	w0, w0, 1
	cmp	w25, w0
	ldr	x2, [x2, 3712]
	str	x2, [x1, -256]
	bne	.L987
.L986:
	str	wzr, [x20, 1624]
	add	x23, x19, 28672
	str	wzr, [x20, 1628]
	add	x24, x23, 24
	add	x27, x20, 1624
	mov	x1, x26
	ldrb	w0, [x22, 2027]
	mov	w2, w25
	mov	w5, 0
	mov	x4, x27
	mov	x3, x24
	add	x23, x23, 288
	add	x26, x20, 1628
	bl	GenPiclistfromFrmlist
	ldrb	w0, [x22, 2027]
	mov	w2, w25
	mov	w5, 0
	mov	x4, x26
	mov	x3, x23
	add	x1, x29, 224
	add	x25, x29, 352
	bl	GenPiclistfromFrmlist
	ldr	w28, [x21, 3716]
	cbz	w28, .L988
	add	x21, x21, 3576
	mov	x0, 0
	add	x25, x29, 352
	.p2align 2
.L989:
	ldr	x1, [x21], 8
	str	x1, [x25, x0, lsl 3]
	add	x0, x0, 1
	cmp	w28, w0
	bhi	.L989
.L988:
	ldr	x3, .LC109
	mov	w2, 8
	mov	w1, w28
	mov	x0, x25
	bl	qsort
	ldrb	w0, [x22, 2027]
	mov	w5, 1
	mov	x4, x27
	mov	x3, x24
	mov	w2, w28
	mov	x1, x25
	bl	GenPiclistfromFrmlist
	ldrb	w0, [x22, 2027]
	mov	x4, x26
	mov	x3, x23
	mov	x1, x25
	mov	w5, 1
	mov	w2, w28
	bl	GenPiclistfromFrmlist
	ldr	w3, [x20, 1624]
	ldr	w4, [x20, 1628]
	cmp	w4, w3
	cset	w1, eq
.L978:
	cmp	w3, 1
	cset	w0, hi
	tst	w1, w0
	beq	.L990
	cbz	w3, .L991
	ldr	x6, [x19, 28696]
	ldr	x0, [x19, 28960]
	cmp	x6, x0
	bne	.L990
	sub	w0, w3, #1
	mov	x2, x19
	add	x0, x19, x0, lsl 3
.L993:
	cmp	x0, x2
	beq	.L995
	ldr	x5, [x2, 28704]
	add	x2, x2, 8
	ldr	x1, [x2, 28960]
	cmp	x5, x1
	beq	.L993
	.p2align 2
.L990:
	ldr	x0, [x19, 22104]
	cbz	x0, .L1062
	ldr	w0, [x20, 1636]
	ldr	w1, [x20, 1640]
	add	w0, w0, 1
	add	w1, w1, 1
	cmp	w0, w3
	csel	w0, w0, w3, ls
	cmp	w1, w4
	csel	w1, w1, w4, ls
	str	w0, [x20, 1624]
	cmp	w0, 32
	str	w1, [x20, 1628]
	bhi	.L1001
	.p2align 2
.L1000:
	add	x2, x19, x0, uxtw 3
	add	w0, w0, 1
	cmp	w0, 33
	str	xzr, [x2, 28696]
	bne	.L1000
.L1001:
	cmp	w1, 32
	bhi	.L999
	.p2align 2
.L1002:
	add	x0, x19, x1, uxtw 3
	add	w1, w1, 1
	cmp	w1, 33
	str	xzr, [x0, 28960]
	bne	.L1002
.L999:
	mov	w0, 0
.L1050:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 480
	ret
	.p2align 3
.L1060:
	ldrb	w0, [x22, 2027]
	add	x21, x19, 24576
	cbz	w0, .L942
	ldr	w0, [x21, 3712]
	mov	w23, 0
	cbz	w0, .L944
	sub	w4, w0, #1
	mov	w23, 0
	add	x4, x4, 3504
	add	x0, x21, 3448
	add	x4, x19, x4, lsl 3
	.p2align 2
.L953:
	ldr	x2, [x0]
	add	x1, x29, 480
	add	x1, x1, x23, uxtw 3
	add	x0, x0, 8
	sub	x1, x1, #4096
	cmp	x4, x0
	ldrb	w3, [x2, 2]
	cbz	w3, .L952
	add	w23, w23, 1
	str	x2, [x1, 3712]
.L952:
	bne	.L953
.L944:
	ldr	x3, .LC108
	mov	w1, w23
	mov	w2, 8
	add	x0, x29, 96
	add	x24, x19, 28672
	add	x26, x20, 1624
	bl	qsort
	str	wzr, [x20, 1624]
	add	x24, x24, 24
	mov	w2, w23
	ldrb	w0, [x22, 2027]
	mov	w5, 0
	mov	x4, x26
	add	x1, x29, 96
	mov	x3, x24
	add	x25, x29, 352
	bl	GenPiclistfromFrmlist
	ldr	w23, [x21, 3716]
	cbz	w23, .L954
	add	x21, x21, 3576
	mov	x0, 0
	add	x25, x29, 352
	.p2align 2
.L955:
	ldr	x1, [x21], 8
	str	x1, [x25, x0, lsl 3]
	add	x0, x0, 1
	cmp	w23, w0
	bhi	.L955
.L954:
	ldr	x3, .LC109
	mov	w2, 8
	mov	w1, w23
	mov	x0, x25
	bl	qsort
	ldrb	w0, [x22, 2027]
	mov	w2, w23
	mov	w5, 1
	mov	x4, x26
	mov	x3, x24
	mov	x1, x25
	bl	GenPiclistfromFrmlist
	ldr	w2, [x20, 1624]
.L951:
	str	wzr, [x20, 1628]
	cbnz	w2, .L956
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cmp	w0, 2
	bne	.L957
	ldrb	w0, [x22, 2027]
	cbz	w0, .L1063
	cmp	w0, 1
	ldr	x0, [x22, 2680]
	beq	.L1064
	add	x0, x0, 800
	mov	w2, 1
	str	x0, [x19, 28696]
	.p2align 2
.L956:
	ldr	w0, [x20, 1636]
	mov	w1, 0
	str	wzr, [x20, 1628]
	add	w0, w0, 1
	cmp	w0, w2
	csel	w0, w0, w2, ls
	str	w0, [x20, 1624]
	cmp	w0, 32
	bls	.L1000
	b	.L1002
	.p2align 3
.L942:
	ldr	w0, [x21, 3712]
	cbz	w0, .L1007
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 3504
	add	x0, x21, 3448
	add	x3, x19, x3, lsl 3
	b	.L947
	.p2align 3
.L946:
	cmp	x3, x0
	beq	.L945
.L947:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cmp	w2, 3
	bne	.L946
	ldr	w2, [x1, 704]
	and	w2, w2, 16776960
	cmp	w2, 65536
	bne	.L946
	add	x2, x19, x23, uxtw 3
	add	x1, x1, 704
	cmp	x3, x0
	add	w23, w23, 1
	str	x1, [x2, 28696]
	bne	.L947
	.p2align 2
.L945:
	add	x0, x19, 28672
	ldr	x3, .LC106
	mov	w1, w23
	mov	w2, 8
	add	x0, x0, 24
	bl	qsort
	str	w23, [x20, 1624]
	ldr	w1, [x21, 3716]
	cbz	w1, .L1008
	sub	w3, w1, #1
	add	x0, x21, 3576
	add	x3, x3, 3520
	mov	w21, w23
	add	x3, x19, x3, lsl 3
	b	.L950
	.p2align 3
.L949:
	cmp	x0, x3
	beq	.L1065
.L950:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cmp	w2, 3
	bne	.L949
	ldr	w2, [x1, 704]
	and	w2, w2, 16776960
	cmp	w2, 256
	bne	.L949
	add	x2, x19, x21, uxtw 3
	add	x1, x1, 704
	cmp	x0, x3
	add	w21, w21, 1
	str	x1, [x2, 28696]
	bne	.L950
	.p2align 2
.L1065:
	sub	w1, w21, w23
.L948:
	uxtw	x0, w23
	ldr	x3, .LC107
	add	x0, x0, 3586
	mov	w2, 8
	add	x0, x19, x0, lsl 3
	add	x0, x0, 8
	bl	qsort
	str	w21, [x20, 1624]
	mov	w2, w21
	b	.L951
	.p2align 3
.L961:
	ldr	w0, [x21, 3712]
	cbz	w0, .L1009
	sub	w3, w0, #1
	mov	w23, 0
	add	x3, x3, 3504
	add	x0, x21, 3448
	add	x3, x19, x3, lsl 3
	b	.L966
	.p2align 3
.L965:
	cmp	x0, x3
	beq	.L964
.L966:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cmp	w2, 3
	bne	.L965
	ldr	w2, [x1, 716]
	add	x5, x19, x23, uxtw 3
	ldr	w4, [x22, 2712]
	add	x1, x1, 704
	cmp	w4, w2
	blt	.L965
	str	x1, [x5, 28696]
	cmp	x0, x3
	add	w23, w23, 1
	bne	.L966
	.p2align 2
.L964:
	add	x25, x19, 28672
	ldr	x3, .LC112
	mov	w2, 8
	mov	w1, w23
	add	x0, x25, 24
	bl	qsort
	ldr	w24, [x21, 3712]
	cbz	w24, .L967
	sub	w3, w24, #1
	add	x0, x21, 3448
	add	x3, x3, 3504
	mov	w26, w23
	add	x3, x19, x3, lsl 3
	b	.L969
	.p2align 3
.L968:
	cmp	x0, x3
	beq	.L1066
.L969:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 2]
	cmp	w2, 3
	bne	.L968
	ldr	w2, [x1, 716]
	add	x5, x19, x26, uxtw 3
	ldr	w4, [x22, 2712]
	add	x1, x1, 704
	cmp	w4, w2
	bge	.L968
	str	x1, [x5, 28696]
	cmp	x0, x3
	add	w26, w26, 1
	bne	.L969
	.p2align 2
.L1066:
	uxtw	x0, w23
	uxtw	x22, w26
	add	x0, x0, 3586
	sub	w24, w26, w23
	ldr	x3, .LC113
	add	x22, x22, 3586
	add	x0, x19, x0, lsl 3
	mov	w2, 8
	add	x0, x0, 8
	mov	w1, w24
	add	x22, x19, x22, lsl 3
	bl	qsort
	add	x22, x22, 8
	cbz	w23, .L971
.L1003:
	add	x25, x25, 24
	mov	w0, 0
	.p2align 2
.L972:
	add	w1, w24, w0
	ldr	x2, [x25], 8
	add	w0, w0, 1
	add	x1, x19, x1, lsl 3
	cmp	w0, w23
	str	x2, [x1, 28960]
	bcc	.L972
.L971:
	cmp	w26, w23
	bls	.L973
	mov	w0, w23
	.p2align 2
.L974:
	sub	w1, w0, w23
	add	x2, x19, x0, uxtw 3
	add	w0, w0, 1
	add	x1, x19, x1, lsl 3
	cmp	w0, w26
	ldr	x2, [x2, 28696]
	str	x2, [x1, 28960]
	bne	.L974
.L973:
	str	w26, [x20, 1624]
	str	w26, [x20, 1628]
	ldr	w1, [x21, 3716]
	cbz	w1, .L1010
	sub	w3, w1, #1
	add	x0, x21, 3576
	add	x3, x3, 3520
	mov	w21, w26
	add	x3, x19, x3, lsl 3
	b	.L977
	.p2align 3
.L976:
	cmp	x3, x0
	beq	.L1067
.L977:
	ldr	x1, [x0]
	add	x0, x0, 8
	ldrb	w2, [x1, 1]
	cmp	w2, 3
	bne	.L976
	ldrb	w2, [x1, 705]
	cmp	w2, 1
	bne	.L976
	add	x2, x19, x21, uxtw 3
	add	x1, x1, 704
	cmp	x3, x0
	add	w21, w21, 1
	str	x1, [x2, 28696]
	str	x1, [x2, 28960]
	bne	.L977
	.p2align 2
.L1067:
	sub	w1, w21, w26
.L975:
	ldr	x23, .LC107
	mov	w2, 8
	mov	x0, x22
	mov	x3, x23
	bl	qsort
	ldr	w0, [x20, 1624]
	mov	x3, x23
	mov	w2, 8
	sub	w1, w21, w0
	uxtw	x0, w0
	add	x0, x0, 3619
	add	x0, x19, x0, lsl 3
	add	x0, x0, 8
	bl	qsort
	str	w21, [x20, 1624]
	mov	w4, w21
	mov	w3, w21
	mov	w1, 1
	str	w21, [x20, 1628]
	b	.L978
	.p2align 3
.L1063:
	ldr	x0, [x22, 2680]
	mov	w2, 1
	add	x0, x0, 704
	str	x0, [x19, 28696]
	b	.L956
.L991:
	ldr	x6, [x19, 28960]
.L995:
	ldr	x0, [x19, 28968]
	str	x0, [x19, 28960]
	str	x6, [x19, 28968]
	b	.L990
.L1064:
	add	x0, x0, 752
	mov	w2, 1
	str	x0, [x19, 28696]
	b	.L956
.L1061:
	add	x26, x29, 96
	ldr	x3, .LC114
	mov	w2, 8
	mov	w1, 0
	mov	x0, x26
	mov	w23, 0
	bl	qsort
	ldr	w24, [x21, 3712]
	cbnz	w24, .L1005
	ldr	x3, .LC115
	mov	w2, 8
	mov	w1, 0
	mov	x0, x26
	mov	w25, 0
	bl	qsort
	b	.L986
	.p2align 3
.L1007:
	mov	w23, 0
	b	.L945
.L1009:
	mov	w23, 0
	b	.L964
.L1010:
	mov	w21, w26
	b	.L975
.L967:
	uxtw	x22, w23
	ldr	x3, .LC113
	add	x22, x22, 3586
	mov	w2, 8
	mov	w1, 0
	mov	w26, w23
	add	x22, x19, x22, lsl 3
	add	x22, x22, 8
	mov	x0, x22
	bl	qsort
	cbnz	w23, .L1003
	b	.L973
	.p2align 3
.L1008:
	mov	w21, w23
	b	.L948
.L981:
	ldr	x3, .LC115
	mov	w2, 8
	mov	w1, 0
	add	x0, x26, x23, uxtw 3
	mov	w25, w23
	bl	qsort
	cbnz	w23, .L1004
	b	.L986
	.p2align 3
.L957:
	ldr	x1, .LC111
.L1056:
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	mov	w0, -1
	b	.L1050
.L1062:
	ldr	x1, .LC117
	b	.L1056
.L1059:
	ldr	x2, .LC104
	mov	w3, 5091
	ldr	x1, .LC105
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1050
	.size	InitListX, .-InitListX
	.align	3
.LC104:
	.xword	.LC30
	.align	3
.LC105:
	.xword	.LC32
	.align	3
.LC106:
	.xword	compare_pic_by_pic_num_desc
	.align	3
.LC107:
	.xword	compare_pic_by_lt_pic_num_asc
	.align	3
.LC108:
	.xword	compare_fs_by_frame_num_desc
	.align	3
.LC109:
	.xword	compare_fs_by_lt_pic_idx_asc
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC112:
	.xword	compare_pic_by_poc_desc
	.align	3
.LC113:
	.xword	compare_pic_by_poc_asc
	.align	3
.LC114:
	.xword	compare_fs_by_poc_desc
	.align	3
.LC115:
	.xword	compare_fs_by_poc_asc
	.align	3
.LC117:
	.xword	.LC116
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DumpList
	.type	DumpList, %function
DumpList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC118
	ldr	w0, [x0]
	tbz	x0, 13, .L1068
	mov	x0, x19
	bl	DumpList.part.10
.L1068:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DumpList, .-DumpList
	.align	3
.LC118:
	.xword	g_PrintEnable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindNearestPOCPicId
	.type	FindNearestPOCPicId, %function
FindNearestPOCPicId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 24576
	ldr	w0, [x2, 3708]
	cbz	w0, .L1077
	add	x1, x19, 61440
	ldr	x3, [x19, 27896]
	cmp	w0, 1
	ldr	w7, [x1, 2708]
	ldr	w1, [x3, 672]
	sub	w1, w7, w1
	sxtw	x1, w1
	eor	x6, x1, x1, asr 63
	sub	x6, x6, x1, asr 63
	bls	.L1078
	sub	w0, w0, #2
	add	x2, x2, 3328
	add	x1, x0, 3489
	mov	w0, 0
	add	x5, x19, x1, lsl 3
	.p2align 2
.L1076:
	ldr	x4, [x2]
	add	x2, x2, 8
	ldr	w1, [x4, 672]
	sub	w1, w7, w1
	sxtw	x1, w1
	eor	x3, x1, x1, asr 63
	sub	x3, x3, x1, asr 63
	cmp	w3, w6
	bge	.L1075
	ldr	w0, [x4, 164]
	mov	w6, w3
.L1075:
	cmp	x2, x5
	bne	.L1076
.L1074:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1078:
	mov	w0, 0
	b	.L1074
.L1077:
	mov	w0, -1
	b	.L1074
	.size	FindNearestPOCPicId, .-FindNearestPOCPicId
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindMinRefIdx
	.type	FindMinRefIdx, %function
FindMinRefIdx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	ldrb	w1, [x0, 1584]
	cmp	w1, 2
	beq	.L1080
	add	x1, x19, 61440
	ldrb	w1, [x1, 2027]
	cbnz	w1, .L1110
	add	x6, x19, 24576
	ldr	w5, [x0, 1624]
	add	x6, x6, 3992
	mov	w4, 0
	add	x7, x19, 28672
	.p2align 2
.L1084:
	cbz	w5, .L1088
	add	x1, x7, 24
	mov	w3, 32
	mov	w0, 0
	b	.L1086
	.p2align 3
.L1085:
	add	w0, w0, 1
	cmp	w0, w5
	beq	.L1111
.L1086:
	ldr	x2, [x1]
	add	x1, x1, 8
	ldr	x2, [x2, 40]
	ldr	w2, [x2, 696]
	cmp	w2, w4
	bne	.L1085
	cmp	w3, w0
	csel	w3, w3, w0, ls
	add	w0, w0, 1
	stp	w3, w3, [x6]
	cmp	w0, w5
	bne	.L1086
.L1111:
	cmp	w3, 31
	bhi	.L1088
.L1087:
	add	w4, w4, 1
	add	x6, x6, 8
	cmp	w4, 16
	bne	.L1084
.L1080:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1110:
	ldr	w6, [x0, 1624]
	add	x7, x19, 24576
	add	x7, x7, 3992
	mov	w4, 0
	add	x8, x19, 28672
	cbz	w6, .L1092
	.p2align 2
.L1113:
	add	x2, x8, 24
	mov	w5, 32
	mov	w1, 0
	b	.L1090
	.p2align 3
.L1089:
	add	w1, w1, 1
	cmp	w1, w6
	beq	.L1112
.L1090:
	ldr	x0, [x2]
	add	x2, x2, 8
	ldr	x3, [x0, 40]
	ldrb	w0, [x0]
	cmp	w0, 2
	ldr	w0, [x3, 696]
	cset	w3, eq
	orr	w0, w3, w0, lsl 1
	cmp	w0, w4
	bne	.L1089
	cmp	w5, w1
	csel	w5, w5, w1, ls
	add	w1, w1, 1
	str	w5, [x7]
	cmp	w1, w6
	bne	.L1090
.L1112:
	cmp	w5, 31
	bhi	.L1092
.L1091:
	add	w4, w4, 1
	add	x7, x7, 4
	cmp	w4, 32
	beq	.L1080
	cbnz	w6, .L1113
	.p2align 2
.L1092:
	str	wzr, [x7]
	b	.L1091
	.p2align 3
.L1088:
	stp	wzr, wzr, [x6]
	b	.L1087
	.size	FindMinRefIdx, .-FindMinRefIdx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UvmosDeleteList
	.type	UvmosDeleteList, %function
UvmosDeleteList:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x6, x19, 20480
	ldrb	w2, [x6, 1584]
	cmp	w2, 1
	beq	.L1116
	cbz	w2, .L1123
	cmp	w2, 2
	mov	w0, 0
	bne	.L1136
.L1118:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1136:
	ldr	x1, .LC119
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L1123:
	mov	w9, 1
.L1117:
	add	x5, x19, 28672
	add	x6, x6, 1624
	add	x5, x5, 24
	mov	x7, 0
	mov	w8, 0
	add	x4, x19, 65536
.L1121:
	ldr	w0, [x6]
	cbz	w0, .L1122
	sub	w0, w0, #1
	add	x3, x7, 3588
	add	x3, x3, x0
	mov	x0, x5
	add	x3, x19, x3, lsl 3
	.p2align 2
.L1120:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L1119
	ldr	w2, [x1, 16]
	ldr	w1, [x4, 1972]
	cmp	w2, w1
	bls	.L1119
	ldr	x1, [x19]
	ldr	w1, [x1, 684]
	cmp	w1, 1
	beq	.L1137
.L1119:
	cmp	x0, x3
	bne	.L1120
.L1122:
	add	w8, w8, 1
	add	x6, x6, 4
	cmp	w8, w9
	add	x5, x5, 264
	add	x7, x7, 33
	bcc	.L1121
	mov	w0, 0
	b	.L1118
	.p2align 3
.L1137:
	mov	x0, x19
	bl	ClearCurrSlice
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
.L1116:
	mov	w9, 2
	b	.L1117
	.size	UvmosDeleteList, .-UvmosDeleteList
	.align	3
.LC119:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecList
	.type	DecList, %function
DecList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1162
	add	x1, x19, 24576
	mov	w7, -1
	ldr	w0, [x1, 3708]
	cbz	w0, .L1141
	add	x2, x19, 61440
	ldr	x3, [x19, 27896]
	cmp	w0, 1
	ldr	w6, [x2, 2708]
	ldr	w2, [x3, 672]
	sub	w2, w6, w2
	sxtw	x2, w2
	eor	x5, x2, x2, asr 63
	sub	x5, x5, x2, asr 63
	bls	.L1154
	sub	w4, w0, #2
	add	x1, x1, 3328
	add	x4, x4, 3489
	mov	w7, 0
	add	x4, x19, x4, lsl 3
	.p2align 2
.L1143:
	ldr	x3, [x1]
	add	x1, x1, 8
	ldr	w0, [x3, 672]
	sub	w0, w6, w0
	sxtw	x0, w0
	eor	x2, x0, x0, asr 63
	sub	x2, x2, x0, asr 63
	cmp	w2, w5
	bge	.L1142
	ldr	w7, [x3, 164]
	mov	w5, w2
.L1142:
	cmp	x1, x4
	bne	.L1143
.L1141:
	add	x20, x19, 20480
	mov	w21, -1
	ldrb	w0, [x20, 1584]
	str	w21, [x20, 3208]
	cmp	w0, 2
	str	w7, [x20, 3212]
	beq	.L1163
	mov	x0, x19
	bl	InitListX
	cbnz	w0, .L1164
	ldr	x1, .LC125
	mov	w0, 13
	bl	dprint_vfmw
	ldr	x22, .LC126
	ldr	w0, [x22]
	tbnz	x0, 13, .L1165
.L1146:
	mov	x0, x19
	bl	ReorderListX
	mov	x0, x19
	bl	RepairList
	cbnz	w0, .L1151
	mov	x0, x19
	bl	FindMinRefIdx
	ldr	x0, [x19]
	ldr	w0, [x0, 684]
	cmp	w0, 1
	beq	.L1148
.L1152:
	ldr	x0, [x19, 28696]
	cbz	x0, .L1166
	ldr	x0, [x0, 40]
	ldr	w0, [x0, 164]
.L1150:
	ldr	x1, .LC128
	mov	w21, 0
	str	w0, [x20, 3208]
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w0, [x22]
	tbz	x0, 13, .L1140
	mov	x0, x19
	bl	DumpList.part.10
.L1140:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1163:
	str	wzr, [x20, 1624]
	mov	w21, 0
	str	wzr, [x20, 1628]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1165:
	mov	x0, x19
	bl	DumpList.part.10
	b	.L1146
	.p2align 3
.L1166:
	mov	w0, -1
	b	.L1150
	.p2align 3
.L1148:
	mov	x0, x19
	bl	UvmosDeleteList
	cbz	w0, .L1152
	.p2align 2
.L1151:
	mov	w21, -1
	b	.L1140
.L1154:
	mov	w7, 0
	b	.L1141
.L1164:
	ldr	x1, .LC123
	mov	w0, 13
	bl	dprint_vfmw
	b	.L1140
.L1162:
	ldr	x2, .LC120
	mov	w3, 5609
	ldr	x1, .LC121
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1140
	.size	DecList, .-DecList
	.align	3
.LC120:
	.xword	.LC30
	.align	3
.LC121:
	.xword	.LC32
	.align	3
.LC123:
	.xword	.LC122
	.align	3
.LC125:
	.xword	.LC124
	.align	3
.LC126:
	.xword	g_PrintEnable
	.align	3
.LC128:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	NoPicOut
	.type	NoPicOut, %function
NoPicOut:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 65536
	ldr	w0, [x1, 636]
	cbz	w0, .L1174
	sub	w2, w0, #1
	mov	w4, 856
	mov	x3, 30084
	add	x0, x19, 28672
	add	x0, x0, 556
	umaddl	x3, w2, w4, x3
	add	x3, x19, x3
	b	.L1173
	.p2align 3
.L1181:
	ldrb	w2, [x0]
	cmp	w2, 1
	beq	.L1171
	add	x0, x0, 856
	cmp	x0, x3
	beq	.L1174
.L1173:
	ldr	w2, [x0, 672]
	cmp	w2, 1
	bne	.L1181
.L1171:
	strb	wzr, [x0, -3]
	strb	wzr, [x0, -2]
	add	x0, x0, 856
	cmp	x0, x3
	bne	.L1173
.L1174:
	ldr	w0, [x1, 640]
	cbz	w0, .L1167
	sub	w0, w0, #1
	add	x1, x1, 568
	add	x0, x0, 16384
	add	x0, x0, 143
	add	x0, x19, x0, lsl 2
	.p2align 2
.L1175:
	str	wzr, [x1], 4
	cmp	x1, x0
	bne	.L1175
.L1167:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	NoPicOut, .-NoPicOut
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetBackPicFromVOQueue
	.type	GetBackPicFromVOQueue, %function
GetBackPicFromVOQueue:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 65536
	bl	_mcount
	ldr	w0, [x20, 1980]
	bl	FSP_GetFspType
	cbz	w0, .L1199
.L1183:
	ldr	w0, [x20, 636]
	mov	w21, 0
	mov	w23, 856
	cbz	w0, .L1190
	.p2align 2
.L1194:
	uxtw	x1, w21
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	umull	x24, w21, w23
	add	x0, x22, x0, lsl 3
	add	x0, x0, 28672
	add	x24, x24, 28672
	add	x19, x24, 1112
	add	x24, x24, 1144
	add	x19, x22, x19
	add	x24, x22, x24
	strb	wzr, [x0, 553]
	strb	wzr, [x0, 554]
.L1188:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L1187
	ldr	w0, [x20, 1980]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L1187:
	add	x19, x19, 8
	cmp	x19, x24
	bne	.L1188
	ldr	w0, [x20, 636]
	add	w21, w21, 1
	cmp	w0, w21
	bhi	.L1194
.L1190:
	ldr	w0, [x20, 640]
	cbz	w0, .L1182
	sub	w0, w0, #1
	add	x20, x20, 568
	add	x0, x0, 16384
	add	x0, x0, 143
	add	x22, x22, x0, lsl 2
	.p2align 2
.L1191:
	str	wzr, [x20], 4
	cmp	x20, x22
	bne	.L1191
.L1182:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1199:
	add	x0, x22, 8
	bl	ResetVoQueue
	b	.L1183
	.size	GetBackPicFromVOQueue, .-GetBackPicFromVOQueue
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	wait_vo
	.type	wait_vo, %function
wait_vo:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	wait_vo, .-wait_vo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetReRangeFlag
	.type	GetReRangeFlag, %function
GetReRangeFlag:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	mov	w19, 4000
	bl	_mcount
	add	x1, x21, 20480
	mov	w0, 2208
	ldr	x5, [x21, 14968]
	ldr	x2, [x21, 14960]
	ldr	w1, [x1, 1592]
	ldr	w4, [x21, 14932]
	ldr	w3, [x21, 14936]
	umull	x0, w1, w0
	mov	w1, 2
	add	x0, x5, x0
	ldr	w0, [x0, 28]
	umull	x0, w0, w19
	add	x19, x2, x0
	ldrb	w0, [x19, 18]
	ldr	w5, [x19, 3252]
	sub	w0, w1, w0
	ldr	w2, [x19, 3248]
	madd	w0, w5, w0, w0
	add	w1, w2, 1
	cmp	w4, w1
	ccmp	w3, w0, 0, eq
	bne	.L1202
	add	x2, x21, 24576
	ldr	w5, [x19, 3272]
	ldr	w2, [x2, 3704]
	add	w2, w2, 1
	cmp	w5, w2
	beq	.L1205
.L1202:
	ldr	x2, .LC129
	ldr	x6, [x2]
	cbz	x6, .L1206
	add	x5, x21, 65536
	ubfiz	w2, w1, 4, 12
	ubfiz	w3, w3, 4, 12
	ubfiz	w1, w0, 4, 12
	ubfiz	w4, w4, 4, 12
	strh	w3, [x29, 58]
	ldr	w0, [x5, 1980]
	mov	w3, 8
	strh	w2, [x29, 60]
	add	x2, x29, 56
	strh	w1, [x29, 62]
	mov	w1, 2
	strh	w4, [x29, 56]
	blr	x6
.L1206:
	ldr	w2, [x19, 3272]
	mov	w3, 1
.L1203:
	add	x1, x21, 16384
	ldr	w4, [x19, 36]
	ldr	w5, [x21, 15012]
	mov	w0, w3
	ldr	w1, [x1, 1864]
	cmp	w5, w4
	ccmp	w1, w2, 0, eq
	cset	w1, ne
	orr	w1, w3, w1
	str	w1, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1205:
	mov	w3, 0
	b	.L1203
	.size	GetReRangeFlag, .-GetReRangeFlag
	.align	3
.LC129:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecPOC
	.type	DecPOC, %function
DecPOC:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	mov	w2, 2208
	ldr	x6, [x19, 14968]
	mov	w1, 4000
	ldr	x5, [x19, 14960]
	mov	w4, 1
	ldr	w3, [x0, 1592]
	ldrb	w7, [x0, 1587]
	umull	x2, w3, w2
	add	x2, x6, x2
	ldr	w2, [x2, 28]
	umull	x1, w2, w1
	add	x1, x5, x1
	ldr	w3, [x1, 2200]
	ldr	w2, [x1, 2196]
	cmp	w3, w4
	add	w2, w2, 4
	lsl	w2, w4, w2
	beq	.L1209
	cbz	w3, .L1210
	cmp	w3, 2
	bne	.L1207
	cmp	w7, 5
	beq	.L1264
	ldr	w1, [x0, 728]
	cbz	w1, .L1243
	ldr	w1, [x0, 768]
	mov	w3, 0
	mov	w2, 0
	str	wzr, [x0, 764]
	str	wzr, [x0, 776]
.L1244:
	str	w2, [x0, 772]
.L1246:
	ldr	w4, [x0, 1612]
	add	w2, w1, w2
	str	w2, [x0, 760]
	lsl	w1, w2, 1
	cbnz	w4, .L1247
	sub	w1, w1, #1
	str	w1, [x0, 748]
.L1248:
	ldrb	w2, [x0, 1585]
	cbnz	w2, .L1249
	str	w1, [x0, 736]
	str	w1, [x0, 740]
	str	w1, [x0, 744]
.L1242:
	ldr	w1, [x0, 768]
	str	w1, [x0, 764]
	str	w3, [x0, 776]
.L1207:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1210:
	ldr	w1, [x1, 2204]
	cmp	w7, 5
	add	w1, w1, 4
	lsl	w4, w4, w1
	beq	.L1216
	ldr	w1, [x0, 728]
	cbnz	w1, .L1214
	ldr	w5, [x0, 712]
	ldr	w3, [x0, 716]
	mov	w2, w5
.L1215:
	ldr	w1, [x0, 704]
	cmp	w1, w3
	bcs	.L1213
	sub	w6, w3, w1
	cmp	w6, w4, lsr 1
	bcc	.L1213
	add	w2, w2, w4
	str	w2, [x0, 720]
.L1217:
	ldrb	w3, [x0, 1585]
	cbnz	w3, .L1219
.L1267:
	ldr	w3, [x0, 708]
	add	w1, w1, w2
	str	w1, [x0, 736]
	add	w2, w1, w3
	str	w2, [x0, 740]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x0, 748]
.L1220:
	ldr	w3, [x0, 764]
	ldr	w2, [x0, 768]
	str	w1, [x0, 744]
	cmp	w2, w3
	beq	.L1222
	str	w2, [x0, 764]
.L1222:
	ldr	w1, [x0, 1612]
	cbz	w1, .L1207
	ldr	w2, [x0, 704]
	ldr	w1, [x0, 720]
	str	w1, [x0, 712]
	str	w2, [x0, 716]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1209:
	cmp	w7, 5
	beq	.L1265
	ldr	w3, [x0, 728]
	cbz	w3, .L1225
	mov	w2, 0
	str	wzr, [x0, 764]
	str	wzr, [x0, 776]
.L1226:
	str	w2, [x0, 772]
.L1224:
	ldr	w2, [x1, 2216]
	cbz	w2, .L1228
	ldr	w2, [x0, 768]
	ldr	w5, [x0, 772]
	ldr	w6, [x0, 1612]
	add	w5, w5, w2
	str	w5, [x0, 760]
	cbnz	w6, .L1230
	cbz	w5, .L1231
	sub	w5, w5, #1
	str	w5, [x0, 760]
.L1230:
	str	wzr, [x0, 792]
	ldr	w2, [x1, 2216]
	cmp	w2, wzr
	ble	.L1232
.L1251:
	mov	w4, 0
	mov	w3, 0
	.p2align 2
.L1233:
	add	x2, x1, x3, sxtw 2
	add	w3, w3, 1
	ldr	w2, [x2, 2220]
	add	w4, w4, w2
	str	w4, [x0, 792]
	ldr	w2, [x1, 2216]
	cmp	w2, w3
	bgt	.L1233
.L1232:
	cbz	w5, .L1234
	sub	w5, w5, #1
	ldr	w7, [x0, 792]
	udiv	w2, w5, w2
	str	w2, [x0, 784]
	ldr	w4, [x1, 2216]
	udiv	w3, w5, w4
	mul	w2, w2, w7
	str	w2, [x0, 788]
	msub	w5, w3, w4, w5
	str	w5, [x0, 780]
	tbnz	w5, #31, .L1235
	mov	w3, 0
	.p2align 2
.L1236:
	add	x4, x1, x3, sxtw 2
	add	w3, w3, 1
	cmp	w5, w3
	ldr	w4, [x4, 2220]
	add	w2, w2, w4
	str	w2, [x0, 788]
	bge	.L1236
.L1235:
	cbnz	w6, .L1237
	ldr	w3, [x1, 2208]
	add	w2, w2, w3
	str	w2, [x0, 788]
.L1237:
	ldrb	w3, [x0, 1585]
	cbnz	w3, .L1238
	ldr	w3, [x0, 752]
	ldr	w4, [x0, 756]
	add	w2, w2, w3
	str	w2, [x0, 736]
	ldr	w1, [x1, 2212]
	add	w1, w2, w1
	add	w1, w1, w4
	str	w1, [x0, 740]
	cmp	w2, w1
	csel	w2, w2, w1, le
	str	w2, [x0, 748]
.L1239:
	ldr	w3, [x0, 768]
	ldr	w1, [x0, 772]
	str	w2, [x0, 744]
	str	w3, [x0, 764]
	str	w1, [x0, 776]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1214:
	ldr	w5, [x0, 732]
	cbz	w5, .L1266
.L1216:
	ldr	w1, [x0, 704]
	mov	w2, 0
	mov	w5, 0
	str	wzr, [x0, 712]
	str	wzr, [x0, 716]
.L1213:
	cmp	w1, w3
	bls	.L1218
	sub	w3, w1, w3
	cmp	w3, w4, lsr 1
	bls	.L1218
	sub	w2, w2, w4
	str	w2, [x0, 720]
	b	.L1217
	.p2align 3
.L1264:
	add	x1, x0, 512
	mov	w3, 0
	stp	wzr, wzr, [x1, 224]
	stp	wzr, wzr, [x1, 232]
	str	wzr, [x0, 772]
	b	.L1242
	.p2align 3
.L1265:
	str	wzr, [x0, 772]
	b	.L1224
	.p2align 3
.L1218:
	ldrb	w3, [x0, 1585]
	str	w5, [x0, 720]
	cbz	w3, .L1267
.L1219:
	ldrb	w3, [x0, 1586]
	add	w1, w1, w2
	cbnz	w3, .L1221
	str	w1, [x0, 736]
	str	w1, [x0, 748]
	b	.L1220
	.p2align 3
.L1228:
	ldr	w6, [x0, 1612]
	str	wzr, [x0, 760]
.L1231:
	str	wzr, [x0, 792]
	mov	w5, 0
	ldr	w2, [x1, 2216]
	cmp	w2, wzr
	bgt	.L1251
	.p2align 2
.L1234:
	mov	w2, 0
	str	wzr, [x0, 788]
	b	.L1235
	.p2align 3
.L1238:
	ldrb	w3, [x0, 1586]
	cbnz	w3, .L1240
	ldr	w1, [x0, 752]
	add	w2, w2, w1
	str	w2, [x0, 736]
	str	w2, [x0, 748]
	b	.L1239
	.p2align 3
.L1243:
	ldr	w3, [x0, 764]
	ldr	w1, [x0, 768]
	cmp	w1, w3
	ldr	w3, [x0, 776]
	bcs	.L1245
	add	w2, w2, w3
	str	w2, [x0, 772]
	mov	w3, w2
	b	.L1246
	.p2align 3
.L1225:
	ldr	w3, [x0, 764]
	ldr	w4, [x0, 768]
	cmp	w4, w3
	bcs	.L1227
	ldr	w3, [x0, 776]
	add	w2, w3, w2
	str	w2, [x0, 772]
	b	.L1224
	.p2align 3
.L1249:
	ldrb	w2, [x0, 1586]
	str	w1, [x0, 744]
	cbnz	w2, .L1250
	str	w1, [x0, 736]
	b	.L1242
	.p2align 3
.L1247:
	str	w1, [x0, 748]
	b	.L1248
	.p2align 3
.L1221:
	str	w1, [x0, 740]
	str	w1, [x0, 748]
	b	.L1220
	.p2align 3
.L1240:
	ldr	w3, [x1, 2212]
	ldr	w1, [x0, 752]
	add	w2, w2, w3
	add	w2, w2, w1
	str	w2, [x0, 740]
	str	w2, [x0, 748]
	b	.L1239
	.p2align 3
.L1266:
	ldr	w3, [x0, 736]
	mov	w2, 0
	str	wzr, [x0, 712]
	str	w3, [x0, 716]
	b	.L1215
	.p2align 3
.L1250:
	str	w1, [x0, 740]
	b	.L1242
.L1227:
	ldr	w2, [x0, 776]
	b	.L1226
.L1245:
	mov	w2, w3
	b	.L1244
	.size	DecPOC, .-DecPOC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CalcPicNum
	.type	CalcPicNum, %function
CalcPicNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 20480
	mov	w1, 2208
	ldr	x4, [x19, 14968]
	mov	w0, 4000
	ldr	x3, [x19, 14960]
	add	x6, x19, 61440
	ldr	w2, [x2, 1592]
	mov	w7, 1
	umull	x1, w2, w1
	ldrb	w2, [x6, 2027]
	add	x1, x4, x1
	ldr	w1, [x1, 28]
	umull	x0, w1, w0
	add	x0, x3, x0
	ldr	w0, [x0, 2196]
	add	w0, w0, 4
	lsl	w7, w7, w0
	add	x0, x19, 24576
	cbz	w2, .L1269
	cmp	w2, 1
	mov	w1, 0
	cset	w8, eq
	cmp	w2, 2
	ldr	w2, [x0, 3712]
	cset	w9, eq
	cbz	w2, .L1289
	.p2align 2
.L1306:
	add	x3, x19, x1, uxtw 3
	ldr	x2, [x3, 28024]
	ldrb	w4, [x2, 2]
	cbz	w4, .L1283
	ldr	w4, [x2, 660]
	ldr	w5, [x6, 2696]
	cmp	w4, w5
	bls	.L1284
	sub	w4, w4, w7
	str	w4, [x2, 664]
.L1285:
	ldr	x2, [x3, 28024]
	ldrb	w4, [x2, 2]
	tbz	x4, 0, .L1286
	ldr	w5, [x2, 752]
	and	w5, w5, 16776960
	cmp	w5, 65536
	beq	.L1316
.L1286:
	tbz	x4, 1, .L1283
	ldr	w3, [x2, 800]
	and	w3, w3, 16776960
	cmp	w3, 65536
	beq	.L1317
	.p2align 2
.L1283:
	ldr	w2, [x0, 3712]
	add	w1, w1, 1
	cmp	w2, w1
	bhi	.L1306
.L1289:
	ldr	w2, [x0, 3716]
	mov	w1, 0
	cbz	w2, .L1268
	.p2align 2
.L1305:
	add	x4, x19, x1, uxtw 3
	add	w1, w1, 1
	ldr	x3, [x4, 28152]
	ldrb	w2, [x3, 2]
	cbz	w2, .L1291
	tbz	x2, 0, .L1292
	ldr	w5, [x3, 752]
	and	w5, w5, 16776960
	cmp	w5, 256
	beq	.L1318
.L1292:
	tbz	x2, 1, .L1291
	ldr	w2, [x3, 800]
	and	w2, w2, 16776960
	cmp	w2, 256
	beq	.L1319
	.p2align 2
.L1291:
	ldr	w2, [x0, 3716]
	cmp	w2, w1
	bhi	.L1305
.L1268:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1284:
	str	w4, [x2, 664]
	b	.L1285
	.p2align 3
.L1269:
	ldr	w2, [x0, 3712]
	mov	w1, 0
	cbnz	w2, .L1304
	.p2align 2
.L1279:
	ldr	w2, [x0, 3716]
	mov	w1, 0
	cbz	w2, .L1268
	add	x2, x19, x1, uxtw 3
	add	w1, w1, 1
	ldr	x2, [x2, 28152]
	ldrb	w3, [x2, 2]
	cmp	w3, 3
	beq	.L1320
	.p2align 2
.L1280:
	ldr	w2, [x0, 3716]
	cmp	w2, w1
	bls	.L1268
	add	x2, x19, x1, uxtw 3
	add	w1, w1, 1
	ldr	x2, [x2, 28152]
	ldrb	w3, [x2, 2]
	cmp	w3, 3
	bne	.L1280
.L1320:
	ldr	w3, [x2, 704]
	and	w3, w3, 16776960
	cmp	w3, 256
	bne	.L1280
	ldr	w3, [x2, 668]
	str	w3, [x2, 708]
	b	.L1280
	.p2align 3
.L1322:
	ldr	w4, [x2, 704]
	and	w4, w4, 16776960
	cmp	w4, 65536
	bne	.L1275
	ldr	w4, [x2, 660]
	ldr	w5, [x6, 2696]
	cmp	w4, w5
	sub	w5, w4, w7
	bhi	.L1321
	str	w4, [x2, 664]
.L1277:
	ldr	x2, [x3, 28024]
	ldr	w3, [x2, 664]
	str	w3, [x2, 712]
	.p2align 2
.L1275:
	ldr	w2, [x0, 3712]
	add	w1, w1, 1
	cmp	w2, w1
	bls	.L1279
.L1304:
	add	x3, x19, x1, uxtw 3
	ldr	x2, [x3, 28024]
	ldrb	w4, [x2, 2]
	cmp	w4, 3
	bne	.L1275
	b	.L1322
	.p2align 3
.L1318:
	ldr	w2, [x3, 668]
	add	w2, w8, w2, lsl 1
	str	w2, [x3, 756]
	ldr	x3, [x4, 28152]
	ldrb	w2, [x3, 2]
	b	.L1292
	.p2align 3
.L1316:
	ldr	w4, [x2, 664]
	add	w4, w8, w4, lsl 1
	str	w4, [x2, 760]
	ldr	x2, [x3, 28024]
	ldrb	w4, [x2, 2]
	b	.L1286
	.p2align 3
.L1319:
	ldr	w2, [x3, 668]
	add	w2, w9, w2, lsl 1
	str	w2, [x3, 804]
	b	.L1291
	.p2align 3
.L1317:
	ldr	w3, [x2, 664]
	add	w3, w9, w3, lsl 1
	str	w3, [x2, 808]
	b	.L1283
	.p2align 3
.L1321:
	str	w5, [x2, 664]
	b	.L1277
	.size	CalcPicNum, .-CalcPicNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsOutDPB
	.type	IsOutDPB, %function
IsOutDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1328
	add	x0, x19, 24576
	ldr	w3, [x0, 3708]
	cbz	w3, .L1328
	ldr	x0, [x19, 27896]
	cmp	x20, x0
	beq	.L1330
	sub	w3, w3, #1
	mov	x0, x19
	add	x3, x19, x3, lsl 3
	b	.L1325
	.p2align 3
.L1326:
	ldr	x2, [x0, 27896]
	cmp	x20, x2
	beq	.L1330
.L1325:
	cmp	x0, x3
	add	x0, x0, 8
	bne	.L1326
.L1328:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1330:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	IsOutDPB, .-IsOutDPB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WritePicMsg
	.type	WritePicMsg, %function
WritePicMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1366
	add	x22, x19, 61440
	add	x20, x19, 65536
	ldr	x1, .LC133
	mov	w0, 2
	add	x23, x19, 12288
	add	x21, x19, 16384
	ldrb	w3, [x22, 2027]
	ldr	w4, [x22, 2188]
	ldr	w2, [x22, 2704]
	ldr	w5, [x22, 2756]
	bl	dprint_vfmw
	str	wzr, [x20, 1904]
	ldr	x2, [x20, 1896]
	ldr	x1, [x22, 2624]
	str	x1, [x20, 728]
	add	x1, x19, 20480
	str	x2, [x20, 1648]
	ldr	w2, [x22, 2152]
	str	w2, [x20, 1424]
	ldr	w2, [x22, 2156]
	str	w2, [x20, 1428]
	ldr	w2, [x22, 2176]
	str	w2, [x20, 1432]
	ldr	w2, [x22, 2180]
	str	w2, [x20, 1436]
	ldr	w2, [x22, 2704]
	str	w2, [x20, 736]
	ldrb	w2, [x22, 2027]
	strb	w2, [x20, 704]
	ldrb	w2, [x23, 2707]
	str	w2, [x20, 752]
	ldr	w2, [x22, 2740]
	str	w2, [x20, 740]
	ldr	w2, [x22, 2744]
	str	w2, [x20, 744]
	ldr	w2, [x23, 5936]
	add	w2, w2, 1
	str	w2, [x20, 748]
	ldrb	w2, [x23, 2706]
	strb	w2, [x20, 707]
	ldr	w2, [x21, 2652]
	str	w2, [x20, 756]
	ldrb	w2, [x21, 2592]
	str	w2, [x20, 760]
	ldr	w0, [x23, 2728]
	strb	w0, [x20, 705]
	ldrb	w0, [x21, 2596]
	str	w0, [x20, 764]
	ldr	w0, [x20, 1980]
	ldr	w2, [x1, 748]
	str	w2, [x20, 768]
	ldr	w2, [x1, 736]
	str	w2, [x20, 772]
	ldr	w1, [x1, 740]
	str	w1, [x20, 776]
	ldr	x1, [x22, 2680]
	ldr	w1, [x1, 656]
	bl	FSP_GetLogicFs
	mov	x24, x0
	cbz	x0, .L1367
	ldp	x2, x3, [x0, 32]
	cbz	x2, .L1336
	cbz	x3, .L1336
	ldr	w0, [x20, 1980]
	add	x3, x20, 1156
	add	x2, x20, 1028
	add	x1, x20, 1284
	bl	FSP_GetDecFsAddrTab
	ldr	x3, [x24, 32]
	add	x2, x20, 1288
	ldr	w0, [x20, 1980]
	add	x1, x20, 1416
	ldr	w3, [x3, 4]
	str	w3, [x20, 1012]
	bl	FSP_GetPmvAddrTab
	ldr	w0, [x22, 2756]
	add	x22, x19, 24576
	str	w0, [x20, 1020]
	ldr	w0, [x24, 12]
	str	w0, [x20, 1420]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 8]
	str	w0, [x20, 1016]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 60]
	str	w0, [x20, 1024]
	ldr	w4, [x22, 3984]
	str	w4, [x20, 1640]
	cbz	w4, .L1342
	sub	w3, w4, #1
	add	x0, x22, 3792
	add	x3, x3, 4096
	add	x1, x20, 1448
	add	x3, x3, 2997
	add	x3, x19, x3, lsl 2
	.p2align 2
.L1341:
	ldr	w2, [x0]
	add	x0, x0, 4
	str	w2, [x1]
	add	x1, x1, 4
	cmp	x3, x0
	ldr	w2, [x0, 60]
	str	w2, [x1, 60]
	ldr	w2, [x0, 124]
	str	w2, [x1, 124]
	bne	.L1341
.L1342:
	ldrb	w0, [x23, 2713]
	cbnz	w0, .L1368
	ldrb	w0, [x21, 2610]
	cbnz	w0, .L1343
	ldr	x10, .LC138
	add	x5, x20, 780
	mov	w1, 0
	.p2align 2
.L1344:
	and	w0, w1, 3
	add	w1, w1, 1
	cmp	w1, 24
	ldr	w0, [x10, w0, uxtw 2]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1344
	add	x6, x20, 876
	mov	w5, 0
	.p2align 2
.L1345:
	add	w0, w5, 1
	and	w2, w5, 14
	add	x1, x10, 16
	and	w0, w0, 15
	add	x6, x6, 8
	add	w5, w5, 2
	cmp	w5, 32
	ldr	w0, [x1, w0, uxtw 2]
	ldr	w1, [x1, w2, uxtw 2]
	lsr	w8, w0, 16
	ubfx	x2, x0, 8, 8
	lsr	w3, w1, 16
	lsr	w7, w1, 24
	ubfiz	w11, w0, 16, 8
	ubfiz	w9, w3, 8, 8
	and	w0, w0, -16777216
	and	w3, w1, 255
	ubfx	x1, x1, 8, 8
	orr	w0, w0, w2, lsl 16
	orr	w8, w11, w8, lsl 24
	orr	w3, w9, w3
	orr	w1, w1, w7, lsl 8
	orr	w2, w8, w3
	orr	w0, w1, w0
	stp	w2, w0, [x6, -8]
	bne	.L1345
.L1351:
	mov	w23, 0
	cbz	w4, .L1347
	.p2align 2
.L1355:
	add	x21, x19, x23, uxtw 2
	ldr	w0, [x20, 1980]
	add	x24, x21, 24576
	mov	w1, 0
	add	x21, x21, 65536
	add	w23, w23, 1
	ldr	w2, [x24, 3792]
	bl	FSP_GetStoreType
	cmp	w0, wzr
	cset	w0, ne
	str	w0, [x21, 1760]
	ldr	w0, [x24, 3792]
	str	w0, [x21, 1824]
	ldr	w0, [x22, 3984]
	cmp	w0, w23
	bhi	.L1355
.L1347:
	mov	w0, 0
.L1333:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1368:
	ldrb	w0, [x21, 2610]
.L1343:
	cmp	w0, 1
	add	x5, x20, 780
	mov	w1, 0
	beq	.L1349
	.p2align 2
.L1352:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 4096
	cmp	w1, 24
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 564]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1352
	add	x6, x20, 876
	mov	w10, 1
	mov	w5, 0
	.p2align 2
.L1353:
	ubfx	x1, x5, 3, 29
	ubfiz	x0, x5, 1, 3
	and	x2, x10, 15
	lsl	x1, x1, 4
	add	x2, x1, x2
	add	x1, x1, x0
	add	x1, x1, 4096
	add	x0, x2, 4096
	add	x6, x6, 8
	add	w5, w5, 1
	add	x0, x19, x0, lsl 2
	add	x1, x19, x1, lsl 2
	cmp	w5, 16
	add	w10, w10, 2
	ldr	w0, [x0, 660]
	ldr	w1, [x1, 660]
	lsr	w3, w0, 16
	ubfx	x8, x0, 8, 8
	lsr	w9, w1, 16
	lsr	w7, w1, 24
	ubfiz	w12, w0, 16, 8
	ubfiz	w11, w9, 8, 8
	ubfx	x2, x1, 8, 8
	and	w9, w1, 255
	lsl	w7, w7, 8
	and	w1, w0, -16777216
	orr	w0, w2, w1
	orr	w3, w12, w3, lsl 24
	orr	w9, w11, w9
	orr	w7, w7, w8, lsl 16
	orr	w1, w9, w3
	orr	w0, w7, w0
	stp	w1, w0, [x6, -8]
	bne	.L1353
	b	.L1351
	.p2align 3
.L1349:
	uxtw	x0, w1
	add	w1, w1, 1
	add	x0, x0, 4096
	cmp	w1, 24
	add	x0, x0, 1144
	ldr	w0, [x19, x0, lsl 2]
	ubfx	x3, x0, 8, 8
	lsr	w2, w0, 16
	ubfiz	w2, w2, 8, 8
	and	w0, w0, -16776961
	orr	w2, w2, w3, lsl 16
	orr	w0, w2, w0
	str	w0, [x5], 4
	bne	.L1349
	add	x6, x20, 876
	mov	w10, 1
	mov	w5, 0
	.p2align 2
.L1350:
	ubfx	x1, x5, 3, 29
	ubfiz	x0, x5, 1, 3
	and	x2, x10, 15
	lsl	x1, x1, 4
	add	x2, x1, x2
	add	x1, x1, x0
	add	x1, x1, 4096
	add	x0, x2, 4096
	add	x0, x0, 1168
	add	x1, x1, 1168
	add	x6, x6, 8
	add	w5, w5, 1
	cmp	w5, 16
	add	w10, w10, 2
	ldr	w0, [x19, x0, lsl 2]
	ldr	w1, [x19, x1, lsl 2]
	lsr	w9, w0, 16
	ubfx	x8, x0, 8, 8
	lsr	w3, w1, 16
	lsr	w7, w1, 24
	ubfiz	w12, w0, 16, 8
	ubfiz	w11, w3, 8, 8
	ubfx	x2, x1, 8, 8
	and	w3, w1, 255
	lsl	w7, w7, 8
	and	w1, w0, -16777216
	orr	w0, w2, w1
	orr	w9, w12, w9, lsl 24
	orr	w3, w11, w3
	orr	w7, w7, w8, lsl 16
	orr	w1, w9, w3
	orr	w0, w7, w0
	stp	w1, w0, [x6, -8]
	bne	.L1350
	b	.L1351
.L1336:
	ldr	x1, .LC137
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1333
.L1366:
	ldr	x2, .LC130
	mov	w3, 6919
	ldr	x1, .LC131
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1333
.L1367:
	ldr	x2, [x22, 2680]
	mov	w0, 0
	ldr	x1, .LC135
	ldr	w2, [x2, 656]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1333
	.size	WritePicMsg, .-WritePicMsg
	.align	3
.LC130:
	.xword	.LC30
	.align	3
.LC131:
	.xword	.LC32
	.align	3
.LC133:
	.xword	.LC132
	.align	3
.LC135:
	.xword	.LC134
	.align	3
.LC137:
	.xword	.LC136
	.align	3
.LC138:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	UpdatePicQpInf
	.type	UpdatePicQpInf, %function
UpdatePicQpInf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldp	w1, w0, [x19, 24]
	cmp	w1, w20
	csel	w1, w1, w20, ge
	cmp	w0, w20
	csel	w0, w0, w20, le
	stp	w1, w0, [x19, 24]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	UpdatePicQpInf, .-UpdatePicQpInf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteSliceMsg
	.type	WriteSliceMsg, %function
WriteSliceMsg:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	add	x21, x23, 65536
	bl	_mcount
	ldr	w5, [x21, 1904]
	ldr	x6, [x21, 1896]
	add	w0, w5, 1
	str	w0, [x21, 1904]
	uxtw	x22, w5
	ldr	w1, [x23, 14940]
	lsl	x4, x22, 7
	sub	x4, x4, x22
	sub	w1, w1, #1
	lsl	x4, x4, 5
	cmp	w5, w1
	add	x20, x6, x4
	bcs	.L1371
	lsl	x1, x0, 7
	sub	x0, x1, x0
	add	x0, x6, x0, lsl 5
	str	x0, [x20, 4056]
.L1372:
	ldr	x3, [x23, 632]
	ldrb	w2, [x3]
	ldr	w0, [x3, 76]
	cmp	w2, 1
	ccmp	w2, w0, 2, ls
	bcs	.L1373
	.p2align 2
.L1374:
	uxtw	x0, w2
	add	w2, w2, 1
	lsl	x1, x0, 5
	add	x3, x3, x1
	add	x0, x20, x0, lsl 2
	ldr	w3, [x3, 28]
	str	w3, [x0, 16]
	ldr	x3, [x23, 632]
	add	x3, x3, x1
	ldr	w3, [x3, 24]
	str	w3, [x0, 8]
	ldr	x3, [x23, 632]
	add	x1, x3, x1
	ldr	w1, [x1, 32]
	str	w1, [x0, 24]
	ldr	x3, [x23, 632]
	ldr	w0, [x3, 76]
	cmp	w0, w2
	ccmp	w2, 1, 2, hi
	bls	.L1374
.L1373:
	cmp	w0, 1
	bhi	.L1379
	.p2align 2
.L1453:
	add	x1, x20, x0, uxtw 2
	add	w0, w0, 1
	cmp	w0, 2
	str	wzr, [x1, 8]
	str	wzr, [x1, 16]
	str	wzr, [x1, 24]
	bne	.L1453
.L1379:
	add	x19, x23, 61440
	add	x24, x23, 16384
	add	x2, x24, 2592
	add	x28, x23, 20480
	add	x1, x23, 12288
	ldrb	w0, [x19, 2033]
	strb	w0, [x20, 1]
	ldr	w0, [x2, 48]
	ldr	w3, [x28, 3192]
	add	w0, w0, 26
	add	w0, w0, w3
	str	w0, [x20, 32]
	ldr	w3, [x28, 3188]
	str	w3, [x20, 36]
	ldr	w3, [x28, 1640]
	str	w3, [x20, 40]
	ldr	w3, [x28, 1636]
	str	w3, [x20, 44]
	ldrb	w3, [x28, 1584]
	strb	w3, [x6, x4]
	ldr	w3, [x28, 1632]
	str	w3, [x20, 48]
	ldrb	w3, [x28, 1590]
	strb	w3, [x20, 2]
	ldrb	w1, [x1, 2708]
	strb	w1, [x20, 3]
	ldr	w1, [x28, 1624]
	str	w1, [x20, 52]
	ldr	w1, [x28, 1628]
	str	w1, [x20, 56]
	ldrb	w1, [x28, 1584]
	cmp	w1, 1
	beq	.L1478
	cbz	w1, .L1479
	strb	wzr, [x20, 4]
.L1380:
	ldr	w2, [x24, 2644]
	str	w2, [x20, 60]
	ldr	w1, [x24, 2648]
	str	w1, [x20, 64]
	ldr	w1, [x28, 3200]
	str	w1, [x20, 68]
	ldr	w1, [x28, 3204]
	str	w1, [x20, 72]
	ldr	w1, [x28, 3196]
	str	w1, [x20, 76]
	ldrb	w1, [x28, 1585]
	cbnz	w1, .L1382
	ldr	x2, [x19, 2680]
	ldr	w3, [x21, 1904]
	ldr	w1, [x2, 700]
	madd	w0, w5, w1, w0
	udiv	w0, w0, w3
	str	w0, [x2, 736]
.L1383:
	ldr	x0, [x19, 2680]
	cbnz	w5, .L1385
	ldr	w1, [x20, 32]
	str	w1, [x0, 728]
	ldr	x0, [x19, 2680]
	ldr	w1, [x20, 32]
	str	w1, [x0, 732]
.L1386:
	ldrb	w0, [x28, 1584]
	cmp	w0, 2
	beq	.L1424
	ldr	w0, [x28, 1624]
	cbz	w0, .L1427
	ldr	x1, [x23, 28696]
	ldr	x1, [x1, 40]
	ldrb	w2, [x1]
	cbz	w2, .L1390
	sub	w3, w0, #1
	mov	x0, x23
	add	x3, x23, x3, lsl 3
	b	.L1392
	.p2align 3
.L1394:
	ldr	x1, [x0, 28704]
	add	x0, x0, 8
	ldr	x1, [x1, 40]
	ldrb	w2, [x1]
	cbz	w2, .L1390
.L1392:
	cmp	x3, x0
	bne	.L1394
.L1427:
	mov	w25, 0
.L1389:
	ldr	w0, [x28, 1628]
	cbz	w0, .L1428
	ldr	x1, [x23, 28960]
	ldr	x1, [x1, 40]
	ldrb	w2, [x1]
	cbz	w2, .L1396
	sub	w3, w0, #1
	mov	x0, x23
	add	x3, x23, x3, lsl 3
	b	.L1398
	.p2align 3
.L1400:
	ldr	x1, [x0, 28968]
	add	x0, x0, 8
	ldr	x1, [x1, 40]
	ldrb	w2, [x1]
	cbz	w2, .L1396
.L1398:
	cmp	x3, x0
	bne	.L1400
.L1428:
	str	wzr, [x29, 108]
.L1395:
	ldrb	w0, [x19, 2027]
	cbz	w0, .L1401
	ldr	w0, [x28, 1624]
	mov	w26, 0
	cbnz	w0, .L1452
	b	.L1417
	.p2align 3
.L1481:
	cbz	x0, .L1434
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1413:
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 2
	add	x0, x20, x0
	str	w1, [x0, 1640]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 696]
	str	w1, [x0, 1644]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 672]
	str	w1, [x0, 1632]
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1]
	strb	w1, [x0, 1624]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1, 704]
	strb	w1, [x0, 1626]
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1]
	cmp	w1, 1
	beq	.L1480
	strb	w1, [x0, 1630]
	add	w26, w26, 1
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1631]
	ldr	x1, [x27, 28696]
	ldr	w1, [x1, 12]
	str	w1, [x0, 1656]
	ldr	w0, [x28, 1624]
	cmp	w0, w26
	bls	.L1417
.L1452:
	uxtw	x19, w26
	ldr	w0, [x21, 1980]
	add	x27, x23, x19, lsl 3
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 656]
	bl	FSP_GetLogicFs
	ldr	x3, [x27, 28696]
	lsl	x1, x19, 5
	add	x1, x1, x19, lsl 2
	add	x1, x20, x1
	ldr	x3, [x3, 40]
	ldr	w3, [x3, 692]
	str	w3, [x1, 1636]
	ldr	x3, [x27, 28696]
	ldr	x3, [x3, 40]
	ldrb	w3, [x3, 1]
	strb	w3, [x1, 1625]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1]
	cmp	w1, 1
	bne	.L1481
	mov	w1, w25
	b	.L1413
	.p2align 3
.L1371:
	str	xzr, [x20, 4056]
	b	.L1372
	.p2align 3
.L1479:
	ldrb	w1, [x2, 2]
	strb	w1, [x20, 4]
	b	.L1380
	.p2align 3
.L1480:
	strb	w1, [x0, 1628]
	add	w26, w26, 1
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1629]
	ldr	x1, [x27, 28696]
	ldr	w1, [x1, 12]
	str	w1, [x0, 1652]
	ldr	w0, [x28, 1624]
	cmp	w0, w26
	bhi	.L1452
.L1417:
	ldrb	w0, [x28, 1584]
	cmp	w0, 1
	beq	.L1482
.L1404:
	add	x1, x23, 24576
	add	x0, x20, 3928
	add	x1, x1, 3992
	add	x3, x20, 4056
	.p2align 2
.L1410:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L1410
	ldrb	w0, [x24, 2594]
	str	w0, [x21, 1004]
	ldr	w1, [x24, 2636]
	str	w1, [x21, 1008]
	cbz	w0, .L1422
	ldrb	w0, [x28, 1584]
	cbnz	w0, .L1422
.L1423:
	ldr	w0, [x28, 1644]
	mov	w2, 0
	str	w0, [x20, 80]
	ldr	w0, [x28, 1648]
	str	w0, [x20, 84]
	.p2align 2
.L1425:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x23, x0
	add	x0, x20, x0
	add	x1, x1, 20480
	ldr	w3, [x1, 1652]
	str	w3, [x0, 88]
	ldr	w3, [x1, 1780]
	str	w3, [x0, 216]
	ldr	w3, [x1, 1908]
	str	w3, [x0, 344]
	ldr	w3, [x1, 2420]
	str	w3, [x0, 856]
	ldr	w3, [x1, 2548]
	str	w3, [x0, 984]
	ldr	w1, [x1, 2676]
	str	w1, [x0, 1112]
	ldr	w0, [x28, 1636]
	cmp	w0, w2
	bcs	.L1425
	ldrb	w0, [x28, 1584]
	cmp	w0, 1
	beq	.L1483
	.p2align 2
.L1424:
	add	x22, x22, 4096
	ldr	x0, [x23, 632]
	add	x22, x23, x22, lsl 3
	str	x0, [x22, 32248]
	str	xzr, [x23, 632]
.L1370:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1385:
	ldr	w2, [x20, 32]
	ldr	w1, [x0, 728]
	cmp	w1, w2
	csel	w1, w1, w2, ge
	str	w1, [x0, 728]
	ldr	w1, [x0, 732]
	cmp	w1, w2
	csel	w1, w1, w2, le
	str	w1, [x0, 732]
	b	.L1386
	.p2align 3
.L1382:
	ldrb	w1, [x28, 1586]
	ldr	w3, [x21, 1904]
	ldr	x2, [x19, 2680]
	cbnz	w1, .L1384
	ldr	w1, [x2, 700]
	madd	w0, w5, w1, w0
	udiv	w0, w0, w3
	str	w0, [x2, 784]
	b	.L1383
	.p2align 3
.L1434:
	mov	w1, 0
	b	.L1413
	.p2align 3
.L1390:
	ldr	w1, [x1, 656]
	ldr	w0, [x21, 1980]
	bl	FSP_GetLogicFs
	cbz	x0, .L1484
	ldr	x0, [x0, 32]
	ldr	w25, [x0, 4]
	b	.L1389
	.p2align 3
.L1422:
	cmp	w1, 1
	bne	.L1424
	ldrb	w0, [x28, 1584]
	cmp	w0, 1
	bne	.L1424
	b	.L1423
	.p2align 3
.L1401:
	ldr	w0, [x28, 1624]
	mov	w26, 0
	cbnz	w0, .L1451
	b	.L1409
	.p2align 3
.L1485:
	cbz	x0, .L1430
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1407:
	lsl	x0, x19, 5
	add	w26, w26, 1
	add	x0, x0, x19, lsl 2
	add	x0, x20, x0
	str	w1, [x0, 1640]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 696]
	str	w1, [x0, 1644]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 672]
	str	w1, [x0, 1632]
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 1627]
	ldr	x1, [x27, 28696]
	ldrb	w1, [x1]
	strb	w1, [x0, 1626]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 716]
	str	w1, [x0, 1648]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 764]
	str	w1, [x0, 1652]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 812]
	str	w1, [x0, 1656]
	strb	wzr, [x0, 1624]
	ldr	w0, [x28, 1624]
	cmp	w0, w26
	bls	.L1409
.L1451:
	uxtw	x19, w26
	ldr	w0, [x21, 1980]
	add	x27, x23, x19, lsl 3
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 656]
	bl	FSP_GetLogicFs
	ldr	x3, [x27, 28696]
	lsl	x1, x19, 5
	add	x1, x1, x19, lsl 2
	add	x1, x20, x1
	ldr	x3, [x3, 40]
	ldr	w3, [x3, 692]
	str	w3, [x1, 1636]
	ldr	x3, [x27, 28696]
	ldr	x3, [x3, 40]
	ldrb	w3, [x3, 1]
	strb	w3, [x1, 1625]
	ldr	x1, [x27, 28696]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1]
	cmp	w1, 1
	bne	.L1485
	mov	w1, w25
	b	.L1407
	.p2align 3
.L1430:
	mov	w1, 0
	b	.L1407
	.p2align 3
.L1409:
	ldrb	w0, [x28, 1584]
	cmp	w0, 1
	bne	.L1404
	ldr	w0, [x28, 1628]
	cbz	w0, .L1404
	mov	w27, 0
	b	.L1412
	.p2align 3
.L1486:
	cbz	x0, .L1432
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1411:
	lsl	x0, x19, 5
	add	w27, w27, 1
	add	x0, x0, x19, lsl 2
	add	x0, x20, x0
	str	w1, [x0, 1640]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 696]
	str	w1, [x0, 2796]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 672]
	str	w1, [x0, 2784]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2779]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1]
	strb	w1, [x0, 2778]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 716]
	str	w1, [x0, 2800]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 764]
	str	w1, [x0, 2804]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 812]
	str	w1, [x0, 2808]
	strb	wzr, [x0, 2776]
	ldr	w0, [x28, 1628]
	cmp	w0, w27
	bls	.L1404
.L1412:
	uxtw	x19, w27
	ldr	w0, [x21, 1980]
	add	x25, x23, x19, lsl 3
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 656]
	bl	FSP_GetLogicFs
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w2, [x1, 692]
	lsl	x1, x19, 5
	add	x1, x1, x19, lsl 2
	add	x1, x20, x1
	str	w2, [x1, 2788]
	ldr	x2, [x25, 28960]
	ldr	x2, [x2, 40]
	ldrb	w2, [x2, 1]
	strb	w2, [x1, 2777]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1]
	cmp	w1, 1
	bne	.L1486
	ldr	w1, [x29, 108]
	b	.L1411
	.p2align 3
.L1396:
	ldr	w1, [x1, 656]
	ldr	w0, [x21, 1980]
	bl	FSP_GetLogicFs
	cbz	x0, .L1487
	ldr	x0, [x0, 32]
	ldr	w0, [x0, 4]
	str	w0, [x29, 108]
	b	.L1395
	.p2align 3
.L1478:
	ldr	w1, [x2, 44]
	strb	w1, [x20, 4]
	b	.L1380
	.p2align 3
.L1384:
	ldr	w1, [x2, 700]
	madd	w0, w5, w1, w0
	udiv	w0, w0, w3
	str	w0, [x2, 832]
	b	.L1383
.L1483:
	mov	w2, 0
	.p2align 2
.L1426:
	ubfiz	x0, x2, 2, 32
	add	w2, w2, 1
	add	x1, x23, x0
	add	x0, x20, x0
	add	x1, x1, 20480
	ldr	w3, [x1, 2036]
	str	w3, [x0, 472]
	ldr	w3, [x1, 2164]
	str	w3, [x0, 600]
	ldr	w3, [x1, 2292]
	str	w3, [x0, 728]
	ldr	w3, [x1, 2804]
	str	w3, [x0, 1240]
	ldr	w3, [x1, 2932]
	str	w3, [x0, 1368]
	ldr	w1, [x1, 3060]
	str	w1, [x0, 1496]
	ldr	w0, [x28, 1640]
	cmp	w0, w2
	bcs	.L1426
	b	.L1424
.L1432:
	mov	w1, 0
	b	.L1411
.L1482:
	ldr	w0, [x28, 1628]
	cbz	w0, .L1404
	mov	w27, 0
	b	.L1421
	.p2align 3
.L1489:
	cbz	x0, .L1436
	ldr	x0, [x0, 32]
	ldr	w1, [x0, 4]
.L1418:
	lsl	x0, x19, 5
	add	x0, x0, x19, lsl 2
	add	x0, x20, x0
	str	w1, [x0, 2792]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 696]
	str	w1, [x0, 2796]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 672]
	str	w1, [x0, 2784]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1]
	strb	w1, [x0, 2776]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1, 704]
	strb	w1, [x0, 2778]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1]
	cmp	w1, 1
	beq	.L1488
	strb	w1, [x0, 2782]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2783]
	ldr	x1, [x25, 28960]
	ldr	w1, [x1, 12]
	str	w1, [x0, 2808]
.L1420:
	ldr	w0, [x28, 1628]
	add	w27, w27, 1
	cmp	w0, w27
	bls	.L1404
.L1421:
	uxtw	x19, w27
	ldr	w0, [x21, 1980]
	add	x25, x23, x19, lsl 3
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 656]
	bl	FSP_GetLogicFs
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldr	w2, [x1, 692]
	lsl	x1, x19, 5
	add	x1, x1, x19, lsl 2
	add	x1, x20, x1
	str	w2, [x1, 2788]
	ldr	x2, [x25, 28960]
	ldr	x2, [x2, 40]
	ldrb	w2, [x2, 1]
	strb	w2, [x1, 2777]
	ldr	x1, [x25, 28960]
	ldr	x1, [x1, 40]
	ldrb	w1, [x1]
	cmp	w1, 1
	bne	.L1489
	ldr	w1, [x29, 108]
	b	.L1418
	.p2align 3
.L1488:
	strb	w1, [x0, 2780]
	ldr	x1, [x25, 28960]
	ldrb	w1, [x1, 1]
	strb	w1, [x0, 2781]
	ldr	x1, [x25, 28960]
	ldr	w1, [x1, 12]
	str	w1, [x0, 2804]
	b	.L1420
.L1436:
	mov	w1, 0
	b	.L1418
.L1484:
	ldr	x1, .LC141
	mov	w2, 7282
	bl	dprint_vfmw
	b	.L1370
.L1487:
	ldr	x1, .LC141
	mov	w2, 7303
	bl	dprint_vfmw
	b	.L1370
	.size	WriteSliceMsg, .-WriteSliceMsg
	.align	3
.LC141:
	.xword	.LC140
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_GetPicStreamSize
	.type	H264_GetPicStreamSize, %function
H264_GetPicStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 65536
	bl	_mcount
	mov	w0, 0
	ldr	x2, [x19, 1648]
	cbz	x2, .L1491
	.p2align 2
.L1492:
	ldp	w3, w1, [x2, 8]
	ldr	x2, [x2, 4056]
	add	w1, w3, w1
	add	w1, w1, 7
	add	w0, w0, w1, lsr 3
	cbnz	x2, .L1492
.L1491:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	H264_GetPicStreamSize, .-H264_GetPicStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SliceCheck
	.type	SliceCheck, %function
SliceCheck:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 20480
	add	x20, x19, 65536
	bl	_mcount
	ldr	x1, .LC143
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1632]
	ldr	w1, [x20, 1920]
	cbnz	w1, .L1505
	mov	w1, 262143
	cmp	w0, w1
	bhi	.L1506
	ldr	w1, [x19, 14932]
	ldr	w2, [x19, 14936]
	mul	w1, w1, w2
	sub	w1, w1, #1
	cmp	w0, w1
	bhi	.L1505
	ldr	x1, .LC147
	mov	x0, x19
	bl	ue_v
	mov	w2, w0
	ldr	x1, .LC149
	mov	w19, w0
	mov	w0, 19
	bl	dprint_vfmw
	ldr	w0, [x20, 1920]
	cbnz	w0, .L1505
	cmp	w19, 9
	bls	.L1507
	ldr	x1, .LC152
	mov	w2, w19
	mov	w0, 1
	bl	dprint_vfmw
.L1505:
	mov	w0, -1
.L1497:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1507:
	ldr	x0, .LC150
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1502
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1502:
	.section	.rodata
	.align	0
	.align	2
.L1502:
	.byte	(.L1501 - .Lrtx1502) / 4
	.byte	(.L1503 - .Lrtx1502) / 4
	.byte	(.L1504 - .Lrtx1502) / 4
	.byte	(.L1501 - .Lrtx1502) / 4
	.byte	(.L1504 - .Lrtx1502) / 4
	.byte	(.L1501 - .Lrtx1502) / 4
	.byte	(.L1503 - .Lrtx1502) / 4
	.byte	(.L1504 - .Lrtx1502) / 4
	.byte	(.L1501 - .Lrtx1502) / 4
	.byte	(.L1504 - .Lrtx1502) / 4
	.text
	.p2align 3
.L1501:
	strb	wzr, [x21, 1584]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1504:
	mov	w1, 2
	strb	w1, [x21, 1584]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1503:
	mov	w1, 1
	strb	w1, [x21, 1584]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1506:
	ldr	x1, .LC145
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1497
	.size	SliceCheck, .-SliceCheck
	.align	3
.LC143:
	.xword	.LC142
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
.LC150:
	.xword	.L1502
	.align	3
.LC152:
	.xword	.LC151
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PPSSPSCheck
	.type	PPSSPSCheck, %function
PPSSPSCheck:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 20480
	bl	_mcount
	ldr	x1, .LC154
	mov	w0, 19
	ldr	w2, [x20, 1592]
	bl	dprint_vfmw
	ldr	w2, [x20, 1592]
	mov	w1, 2208
	ldr	x3, [x19, 14968]
	umull	x0, w2, w1
	adds	x0, x3, x0
	beq	.L1514
	ldrb	w1, [x0, 19]
	cbz	w1, .L1515
	ldr	w2, [x0, 28]
	mov	w0, 4000
	ldr	x1, [x19, 14960]
	umull	x0, w2, w0
	adds	x0, x1, x0
	beq	.L1516
	ldrb	w1, [x0, 23]
	mov	w0, 0
	cbz	w1, .L1517
.L1510:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1515:
	ldr	x1, .LC158
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1510
	.p2align 3
.L1517:
	ldr	x1, .LC160
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1510
.L1514:
	ldr	x2, .LC155
	mov	w3, 7777
	ldr	x1, .LC156
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1510
.L1516:
	ldr	x2, .LC155
	mov	w3, 7788
	ldr	x1, .LC156
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1510
	.size	PPSSPSCheck, .-PPSSPSCheck
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC155:
	.xword	.LC30
	.align	3
.LC156:
	.xword	.LC32
	.align	3
.LC158:
	.xword	.LC157
	.align	3
.LC160:
	.xword	.LC159
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PPSSPSCheckTmpId
	.type	PPSSPSCheckTmpId, %function
PPSSPSCheckTmpId:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x1, .LC162
	mov	w2, w20
	mov	w0, 19
	bl	dprint_vfmw
	cbz	x19, .L1524
	mov	w0, 2208
	ldr	x1, [x19, 14968]
	umull	x0, w20, w0
	add	x0, x1, x0
	ldrb	w1, [x0, 19]
	cbz	w1, .L1525
	ldr	w1, [x19, 14944]
	ldr	w2, [x0, 28]
	sub	w0, w1, #1
	cmp	w2, w0
	bhi	.L1526
	mov	w1, 4000
	ldr	x3, [x19, 14960]
	mov	w0, 0
	umull	x1, w2, w1
	add	x1, x3, x1
	ldrb	w1, [x1, 23]
	cbz	w1, .L1527
.L1520:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1525:
	ldr	x1, .LC166
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
	.p2align 3
.L1526:
	ldr	x1, .LC168
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
	.p2align 3
.L1527:
	ldr	x1, .LC170
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
.L1524:
	ldr	x2, .LC163
	mov	w3, 7816
	ldr	x1, .LC164
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1520
	.size	PPSSPSCheckTmpId, .-PPSSPSCheckTmpId
	.align	3
.LC162:
	.xword	.LC161
	.align	3
.LC163:
	.xword	.LC30
	.align	3
.LC164:
	.xword	.LC32
	.align	3
.LC166:
	.xword	.LC165
	.align	3
.LC168:
	.xword	.LC167
	.align	3
.LC170:
	.xword	.LC169
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsNewPic
	.type	IsNewPic, %function
IsNewPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1541
	add	x1, x19, 20480
	ldr	w2, [x19, 15012]
	ldr	w0, [x1, 1592]
	ldr	w3, [x1, 3232]
	ldr	w6, [x1, 3228]
	cmp	w3, w0
	ldr	w5, [x1, 3240]
	ldr	w0, [x1, 1600]
	ccmp	w6, w2, 0, eq
	ldrb	w4, [x1, 1585]
	cset	w2, ne
	ldrb	w3, [x1, 3224]
	cmp	w5, w0
	ccmp	w3, w4, 0, eq
	cset	w0, ne
	cmp	w4, wzr
	ccmp	w3, wzr, 4, ne
	orr	w2, w2, w0
	mov	w0, w2
	bne	.L1542
	ldr	w3, [x1, 1612]
	ldr	w2, [x1, 3236]
	cmp	w2, w3
	beq	.L1537
.L1545:
	cmp	w3, wzr
	ccmp	w2, wzr, 4, ne
	cset	w3, eq
.L1533:
	ldrb	w5, [x1, 3226]
	ldrb	w4, [x1, 1587]
	cmp	w5, w4
	cset	w2, ne
	cmp	w5, 5
	ccmp	w4, 5, 0, eq
	orr	w2, w2, w0
	orr	w2, w2, w3
	beq	.L1543
.L1534:
	add	x19, x19, 16384
	ldr	w0, [x19, 792]
	cbz	w0, .L1544
	cmp	w0, 1
	bne	.L1536
	ldr	w4, [x1, 752]
	ldr	w5, [x1, 3256]
	ldr	w0, [x1, 756]
	ldr	w3, [x1, 3260]
	cmp	w5, w4
	ccmp	w3, w0, 0, eq
	cset	w0, ne
	orr	w2, w2, w0
.L1536:
	ldr	w3, [x1, 1632]
	mov	w0, 19
	ldr	x1, .LC174
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
.L1544:
	ldr	w4, [x1, 704]
	ldr	w5, [x1, 3248]
	ldr	w0, [x1, 708]
	ldr	w3, [x1, 3252]
	cmp	w5, w4
	ccmp	w3, w0, 0, eq
	cset	w0, ne
	orr	w2, w2, w0
	b	.L1536
	.p2align 3
.L1542:
	ldrb	w3, [x1, 3225]
	ldrb	w0, [x1, 1586]
	cmp	w3, w0
	ldr	w3, [x1, 1612]
	cset	w0, ne
	orr	w0, w2, w0
	ldr	w2, [x1, 3236]
	cmp	w2, w3
	bne	.L1545
.L1537:
	mov	w3, 0
	b	.L1533
	.p2align 3
.L1541:
	ldr	x2, .LC171
	mov	w3, 7856
	ldr	x1, .LC172
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1543:
	ldr	w0, [x1, 1620]
	ldr	w3, [x1, 3244]
	cmp	w3, w0
	cset	w0, ne
	orr	w2, w2, w0
	b	.L1534
	.size	IsNewPic, .-IsNewPic
	.align	3
.LC171:
	.xword	.LC30
	.align	3
.LC172:
	.xword	.LC32
	.align	3
.LC174:
	.xword	.LC173
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ref_pic_list_reordering
	.type	ref_pic_list_reordering, %function
ref_pic_list_reordering:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 20480
	mov	w23, 1
	bl	_mcount
	mov	w1, 2208
	ldr	x5, [x19, 14968]
	ldr	w2, [x20, 1592]
	mov	w0, 4000
	ldr	x4, [x19, 14960]
	ldrb	w3, [x20, 1585]
	umull	x1, w2, w1
	add	x1, x5, x1
	ldr	w1, [x1, 28]
	strb	wzr, [x20, 796]
	strb	wzr, [x20, 797]
	umull	x0, w1, w0
	add	x0, x4, x0
	ldr	w0, [x0, 2196]
	cbz	w3, .L1547
	add	w0, w0, 5
	add	x22, x19, 65536
	lsl	w23, w23, w0
	ldrb	w0, [x20, 1584]
	cmp	w0, 1
	bls	.L1598
.L1597:
	ldr	w3, [x22, 1920]
.L1565:
	cmp	w3, wzr
	csetm	w0, ne
.L1596:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1547:
	add	w0, w0, 4
	add	x22, x19, 65536
	lsl	w23, w23, w0
	ldrb	w0, [x20, 1584]
	cmp	w0, 1
	bhi	.L1597
.L1598:
	ldr	x1, .LC176
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 796]
	cbz	w0, .L1556
	ldr	w0, [x20, 1636]
	cmn	w0, #2
	beq	.L1579
	ldr	x24, .LC178
	mov	w27, 0
	ldr	x26, .LC186
	ldr	x25, .LC182
	b	.L1562
	.p2align 3
.L1557:
	cmp	w0, 2
	beq	.L1599
.L1560:
	ldr	w0, [x20, 1636]
	add	w0, w0, 2
	cmp	w0, w27
	bls	.L1600
.L1562:
	add	x21, x19, x27, uxtw 2
	mov	x1, x24
	add	x21, x21, 20480
	mov	x0, x19
	add	w27, w27, 1
	bl	ue_v
	cmp	w0, 3
	str	w0, [x21, 800]
	ldr	w3, [x22, 1920]
	bhi	.L1553
	cbnz	w3, .L1553
	beq	.L1556
	cmp	w0, 1
	bhi	.L1557
	mov	x1, x25
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1064]
	cmp	w23, w0
	ldr	w3, [x22, 1920]
	bls	.L1559
	cbz	w3, .L1560
.L1559:
	ldr	x1, .LC184
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1596
	.p2align 3
.L1556:
	ldrb	w0, [x20, 1584]
.L1549:
	cmp	w0, 1
	bne	.L1597
	ldr	x1, .LC190
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 797]
	cbz	w0, .L1597
	ldr	w0, [x20, 1640]
	cmn	w0, #2
	beq	.L1597
	ldr	x24, .LC192
	mov	w27, 0
	ldr	x26, .LC200
	ldr	x25, .LC196
	b	.L1577
	.p2align 3
.L1571:
	cmp	w0, 2
	beq	.L1601
	ldr	w0, [x20, 1640]
	add	w0, w0, 2
	cmp	w27, w0
	beq	.L1578
.L1576:
	add	w27, w27, 1
	cmp	w27, w0
	bcs	.L1597
.L1577:
	add	x21, x19, x27, uxtw 2
	mov	x1, x24
	add	x21, x21, 20480
	mov	x0, x19
	bl	ue_v
	cmp	w0, 3
	str	w0, [x21, 932]
	ldr	w3, [x22, 1920]
	bhi	.L1569
	cbnz	w3, .L1569
	beq	.L1565
	cmp	w0, 1
	bhi	.L1571
	mov	x1, x25
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1196]
	cmp	w23, w0
	ldr	w3, [x22, 1920]
	bls	.L1573
	cbnz	w3, .L1573
.L1574:
	ldr	w0, [x20, 1640]
	add	w0, w0, 2
	cmp	w0, w27
	bne	.L1576
	ldr	w1, [x21, 932]
	cmp	w1, 3
	beq	.L1576
.L1578:
	ldr	x1, .LC202
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1596
	.p2align 3
.L1599:
	mov	x1, x26
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1328]
	b	.L1560
	.p2align 3
.L1601:
	mov	x1, x26
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 1456]
	b	.L1574
	.p2align 3
.L1553:
	ldr	x1, .LC180
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1596
	.p2align 3
.L1569:
	ldr	x1, .LC194
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1596
	.p2align 3
.L1600:
	bne	.L1556
.L1551:
	uxtw	x0, w27
	add	x0, x0, 4096
	add	x0, x19, x0, lsl 2
	ldr	w0, [x0, 4896]
	cmp	w0, 3
	bne	.L1563
	ldrb	w0, [x20, 1584]
	add	x22, x19, 65536
	b	.L1549
.L1573:
	ldr	x1, .LC198
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1596
.L1579:
	mov	w27, 0
	b	.L1551
.L1563:
	ldr	x1, .LC188
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1596
	.size	ref_pic_list_reordering, .-ref_pic_list_reordering
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC180:
	.xword	.LC179
	.align	3
.LC182:
	.xword	.LC181
	.align	3
.LC184:
	.xword	.LC183
	.align	3
.LC186:
	.xword	.LC185
	.align	3
.LC188:
	.xword	.LC187
	.align	3
.LC190:
	.xword	.LC189
	.align	3
.LC192:
	.xword	.LC191
	.align	3
.LC194:
	.xword	.LC193
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC200:
	.xword	.LC199
	.align	3
.LC202:
	.xword	.LC201
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	pred_weight_table
	.type	pred_weight_table, %function
pred_weight_table:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	add	x21, x26, 20480
	mov	w24, 2208
	bl	_mcount
	mov	w20, 4000
	ldr	x2, [x26, 14968]
	mov	x0, x26
	ldr	w4, [x21, 1592]
	mov	w19, 1
	ldr	x1, .LC204
	mov	w25, 0
	ldr	x5, [x26, 14960]
	umull	x4, w4, w24
	add	x24, x2, x4
	ldr	w2, [x24, 28]
	umull	x2, w2, w20
	add	x20, x5, x2
	bl	ue_v
	str	w0, [x21, 1644]
	lsl	w23, w19, w0
	ldr	w1, [x20, 40]
	cbnz	w1, .L1627
.L1603:
	cmp	w0, 7
	bhi	.L1606
	ldr	w0, [x21, 1648]
	cmp	w0, 7
	bhi	.L1606
	add	x0, x26, 65536
	str	x0, [x29, 104]
	ldr	w2, [x0, 1920]
	cbnz	w2, .L1605
	ldr	x22, .LC210
	mov	w27, 0
	b	.L1614
	.p2align 3
.L1609:
	str	w23, [x1, 1652]
	add	x0, x26, x19, lsl 2
	str	wzr, [x1, 2420]
	add	x0, x0, 20480
	ldr	w1, [x20, 40]
	cbnz	w1, .L1628
.L1611:
	str	wzr, [x0, 1780]
	str	wzr, [x0, 1908]
	str	wzr, [x0, 2548]
	str	wzr, [x0, 2676]
.L1613:
	ldr	w0, [x21, 1636]
	add	w27, w27, 1
	cmp	w0, w27
	bcc	.L1629
.L1614:
	mov	x1, x22
	mov	x0, x26
	uxtw	x19, w27
	bl	u_1
	add	x1, x26, x19, lsl 2
	add	x1, x1, 20480
	cbz	w0, .L1609
	ldr	x1, .LC212
	mov	x0, x26
	bl	se_v
	add	x4, x26, x19, lsl 2
	ldr	x1, .LC214
	add	x28, x4, 20480
	str	w0, [x28, 1652]
	mov	x0, x26
	bl	se_v
	str	w0, [x28, 2420]
	add	x0, x26, x19, lsl 2
	ldr	w1, [x20, 40]
	add	x0, x0, 20480
	cbz	w1, .L1611
.L1628:
	ldr	x1, .LC216
	mov	x0, x26
	bl	u_1
	add	x1, x26, x19, lsl 2
	add	x1, x1, 20480
	cbnz	w0, .L1630
	str	w25, [x1, 1780]
	add	w27, w27, 1
	str	w25, [x1, 1908]
	str	wzr, [x1, 2548]
	str	wzr, [x1, 2676]
	ldr	w0, [x21, 1636]
	cmp	w0, w27
	bcs	.L1614
.L1629:
	ldr	w0, [x24, 44]
	cmp	w0, 1
	beq	.L1615
.L1616:
	ldr	x0, [x29, 104]
	ldr	w0, [x0, 1920]
	cmp	w0, wzr
	csetm	w0, ne
.L1608:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1630:
	ldr	x1, .LC218
	mov	x0, x26
	add	x19, x26, x19, lsl 2
	add	x19, x19, 20480
	bl	se_v
	ldr	x1, .LC220
	str	w0, [x19, 1780]
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 2548]
	ldr	x1, .LC218
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 1908]
	ldr	x1, .LC220
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 2676]
	b	.L1613
	.p2align 3
.L1627:
	ldr	x1, .LC206
	mov	x0, x26
	bl	ue_v
	mov	w25, w0
	ldr	w0, [x21, 1644]
	str	w25, [x21, 1648]
	lsl	w25, w19, w25
	b	.L1603
	.p2align 3
.L1615:
	ldrb	w0, [x21, 1584]
	cmp	w0, 1
	bne	.L1616
	ldr	x22, .LC222
	mov	w28, 0
	ldr	x27, .LC224
	b	.L1622
	.p2align 3
.L1617:
	add	x0, x26, x19, lsl 2
	add	x0, x0, 20480
	str	w23, [x0, 2036]
	str	wzr, [x0, 2804]
	add	x0, x26, x19, lsl 2
	add	x0, x0, 20480
	ldr	w1, [x20, 40]
	cbnz	w1, .L1631
.L1619:
	str	wzr, [x0, 2164]
	str	wzr, [x0, 2292]
	str	wzr, [x0, 2932]
	str	wzr, [x0, 3060]
.L1621:
	ldr	w0, [x21, 1640]
	add	w28, w28, 1
	cmp	w0, w28
	bcc	.L1616
.L1622:
	mov	x1, x22
	mov	x0, x26
	uxtw	x19, w28
	bl	u_1
	cbz	w0, .L1617
	mov	x1, x27
	mov	x0, x26
	bl	se_v
	add	x4, x26, x19, lsl 2
	ldr	x1, .LC226
	add	x24, x4, 20480
	str	w0, [x24, 2036]
	mov	x0, x26
	bl	se_v
	str	w0, [x24, 2804]
	add	x0, x26, x19, lsl 2
	ldr	w1, [x20, 40]
	add	x0, x0, 20480
	cbz	w1, .L1619
.L1631:
	ldr	x1, .LC228
	mov	x0, x26
	bl	u_1
	cbnz	w0, .L1632
	add	x0, x26, x19, lsl 2
	add	x0, x0, 20480
	str	w25, [x0, 2164]
	str	w25, [x0, 2292]
	str	wzr, [x0, 2932]
	str	wzr, [x0, 3060]
	b	.L1621
.L1606:
	add	x3, x26, 65536
	ldr	w2, [x3, 1920]
.L1605:
	ldr	x1, .LC208
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1608
.L1632:
	ldr	x1, .LC230
	mov	x0, x26
	add	x19, x26, x19, lsl 2
	add	x19, x19, 20480
	bl	se_v
	ldr	x1, .LC232
	str	w0, [x19, 2164]
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 2932]
	ldr	x1, .LC230
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 2292]
	ldr	x1, .LC232
	mov	x0, x26
	bl	se_v
	str	w0, [x19, 3060]
	b	.L1621
	.size	pred_weight_table, .-pred_weight_table
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC206:
	.xword	.LC205
	.align	3
.LC208:
	.xword	.LC207
	.align	3
.LC210:
	.xword	.LC209
	.align	3
.LC212:
	.xword	.LC211
	.align	3
.LC214:
	.xword	.LC213
	.align	3
.LC216:
	.xword	.LC215
	.align	3
.LC218:
	.xword	.LC217
	.align	3
.LC220:
	.xword	.LC219
	.align	3
.LC222:
	.xword	.LC221
	.align	3
.LC224:
	.xword	.LC223
	.align	3
.LC226:
	.xword	.LC225
	.align	3
.LC228:
	.xword	.LC227
	.align	3
.LC230:
	.xword	.LC229
	.align	3
.LC232:
	.xword	.LC231
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecMMCO
	.type	DecMMCO, %function
DecMMCO:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	w19, w1
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L1634
	mov	w22, 100
	ldr	x21, .LC236
	ldr	x25, .LC238
	add	x23, x20, 65536
	ldr	x27, .LC244
	ldr	x24, .LC242
	ldr	x26, .LC240
	b	.L1645
	.p2align 3
.L1646:
	cmp	w19, 2
	beq	.L1659
.L1647:
	cmp	w19, 6
	cset	w0, eq
	orr	w0, w28, w0
	cbnz	w0, .L1650
	cmp	w19, 4
	beq	.L1660
.L1651:
	cmp	w19, 6
	bhi	.L1643
	ldr	w0, [x23, 1920]
	cbnz	w0, .L1643
.L1661:
	cbz	w19, .L1653
.L1652:
	subs	w22, w22, #1
	beq	.L1654
.L1645:
	mov	x1, x21
	mov	x0, x20
	bl	ue_v
	cmp	w0, 3
	mov	w19, w0
	and	w0, w0, -3
	cset	w28, eq
	cmp	w0, 1
	bne	.L1646
	mov	x1, x25
	mov	x0, x20
	bl	ue_v
	cmp	w19, 2
	bne	.L1647
.L1659:
	mov	x1, x26
	mov	x0, x20
	bl	ue_v
	ldr	w0, [x23, 1920]
	cbz	w0, .L1661
	.p2align 2
.L1643:
	ldr	x1, .LC246
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L1637:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1650:
	mov	x1, x24
	mov	x0, x20
	bl	ue_v
	cmp	w19, 4
	bne	.L1651
.L1660:
	mov	x1, x27
	mov	x0, x20
	bl	ue_v
	ldr	w0, [x23, 1920]
	cbz	w0, .L1652
	b	.L1643
	.p2align 3
.L1634:
	ldr	x21, .LC236
	mov	w26, 0
	ldr	x25, .LC238
	add	x22, x20, 24576
	ldr	x24, .LC242
	add	x23, x20, 65536
	b	.L1636
	.p2align 3
.L1638:
	cmp	w1, 2
	beq	.L1662
.L1639:
	cmp	w1, 3
	ccmp	w1, 6, 4, ne
	beq	.L1663
.L1640:
	cmp	w1, 4
	beq	.L1664
.L1641:
	cmp	w1, 6
	bhi	.L1643
	ldr	w0, [x23, 1920]
	cbnz	w0, .L1643
	add	w26, w26, 1
	cbz	w1, .L1653
	cmp	w26, 100
	beq	.L1665
.L1636:
	ldr	w28, [x22, 3180]
	mov	x1, x21
	mov	x0, x20
	uxtw	x27, w26
	lsl	x19, x27, 4
	bl	ue_v
	uxtw	x28, w28
	mov	w1, w0
	lsl	x0, x28, 6
	sub	x0, x0, x28
	add	x19, x19, x27, lsl 2
	lsl	x0, x0, 2
	and	w2, w1, -3
	sub	x0, x0, x28
	cmp	w2, 1
	lsl	x0, x0, 1
	sub	x0, x0, x28
	add	x19, x19, x0, lsl 2
	add	x19, x20, x19
	add	x19, x19, 20480
	str	w1, [x19, 3272]
	bne	.L1638
	mov	x1, x25
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3276]
	ldr	w1, [x19, 3272]
	cmp	w1, 2
	bne	.L1639
.L1662:
	ldr	x1, .LC240
	mov	x0, x20
	bl	ue_v
	lsl	x1, x28, 6
	sub	x1, x1, x28
	lsl	x1, x1, 2
	sub	x1, x1, x28
	lsl	x1, x1, 1
	sub	x2, x1, x28
	lsl	x1, x27, 4
	add	x1, x1, x27, lsl 2
	add	x1, x1, x2, lsl 2
	add	x1, x20, x1
	add	x1, x1, 20480
	str	w0, [x1, 3280]
	ldr	w1, [x1, 3272]
	cmp	w1, 3
	ccmp	w1, 6, 4, ne
	bne	.L1640
	.p2align 2
.L1663:
	mov	x1, x24
	mov	x0, x20
	bl	ue_v
	lsl	x1, x28, 6
	lsl	x2, x27, 4
	sub	x1, x1, x28
	add	x2, x2, x27, lsl 2
	lsl	x1, x1, 2
	sub	x1, x1, x28
	lsl	x1, x1, 1
	sub	x1, x1, x28
	add	x2, x2, x1, lsl 2
	add	x2, x20, x2
	add	x2, x2, 20480
	ldr	w1, [x2, 3272]
	str	w0, [x2, 3284]
	cmp	w1, 4
	bne	.L1641
.L1664:
	ldr	x1, .LC244
	mov	x0, x20
	bl	ue_v
	lsl	x1, x28, 6
	sub	x1, x1, x28
	lsl	x1, x1, 2
	sub	x1, x1, x28
	lsl	x1, x1, 1
	sub	x28, x1, x28
	lsl	x1, x27, 4
	add	x3, x1, x27, lsl 2
	add	x3, x3, x28, lsl 2
	add	x3, x20, x3
	add	x3, x3, 20480
	ldr	w1, [x3, 3272]
	str	w0, [x3, 3288]
	b	.L1641
	.p2align 3
.L1653:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1665:
	ldr	x1, .LC234
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1637
.L1654:
	mov	w0, -1
	b	.L1637
	.size	DecMMCO, .-DecMMCO
	.align	3
.LC234:
	.xword	.LC233
	.align	3
.LC236:
	.xword	.LC235
	.align	3
.LC238:
	.xword	.LC237
	.align	3
.LC240:
	.xword	.LC239
	.align	3
.LC242:
	.xword	.LC241
	.align	3
.LC244:
	.xword	.LC243
	.align	3
.LC246:
	.xword	.LC245
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	dec_ref_pic_marking
	.type	dec_ref_pic_marking, %function
dec_ref_pic_marking:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 24576
	bl	_mcount
	ldr	w23, [x20, 3180]
	cbz	x21, .L1686
	add	x1, x21, 20480
	ldrb	w0, [x1, 1589]
	cbnz	w0, .L1687
	uxtw	x19, w23
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x19, x0, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 20480
	ldrb	w0, [x19, 3268]
	cbnz	w0, .L1688
	ldrb	w0, [x1, 1587]
	uxtw	x19, w23
	cmp	w0, 5
	beq	.L1689
.L1670:
	ldr	x1, .LC256
	mov	x0, x21
	bl	u_1
	mov	w4, w0
	lsl	x3, x19, 6
	ldr	x1, .LC258
	sub	x3, x3, x19
	uxtb	w2, w0
	lsl	x3, x3, 2
	mov	w0, 16
	sub	x3, x3, x19
	lsl	x3, x3, 1
	sub	x19, x3, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 20480
	strb	w4, [x19, 3271]
	bl	dprint_vfmw
	ldrb	w0, [x19, 3271]
	cbnz	w0, .L1671
.L1675:
	mov	w22, 0
.L1683:
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1687:
	cmp	w23, wzr
	cset	w19, eq
	str	w19, [x20, 3180]
	ldrb	w0, [x1, 1587]
	cmp	w0, 5
	bne	.L1670
.L1689:
	ldr	x1, .LC250
	mov	x0, x21
	mov	w22, 0
	bl	u_1
	lsl	x2, x19, 6
	ldr	x1, .LC252
	sub	x2, x2, x19
	lsl	x2, x2, 2
	sub	x2, x2, x19
	lsl	x2, x2, 1
	sub	x19, x2, x19
	add	x19, x21, x19, lsl 2
	add	x19, x19, 20480
	strb	w0, [x19, 3269]
	mov	x0, x21
	bl	u_1
	strb	w0, [x19, 3270]
	ldrb	w2, [x19, 3269]
	mov	w0, 16
	ldr	x1, .LC254
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1671:
	mov	w1, 1
	mov	x0, x21
	bl	DecMMCO
	cmn	w0, #1
	mov	w22, w0
	beq	.L1690
	mov	w0, 1
	strb	w0, [x19, 3268]
	mov	w22, 0
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1688:
	ldrb	w0, [x1, 1587]
	cmp	w0, 5
	beq	.L1691
	ldr	x1, .LC256
	mov	x0, x21
	ldrb	w20, [x19, 3271]
	bl	u_1
	cmp	w20, w0
	bne	.L1692
	ldrb	w0, [x19, 3271]
	cbz	w0, .L1675
	mov	w1, 0
	mov	x0, x21
	bl	DecMMCO
	mov	w22, w0
	b	.L1683
	.p2align 3
.L1691:
	ldr	x1, .LC250
	mov	x0, x21
	ldrb	w20, [x19, 3269]
	bl	u_1
	cmp	w20, w0
	bne	.L1693
	ldr	x1, .LC252
	mov	x0, x21
	ldrb	w19, [x19, 3270]
	bl	u_1
	cmp	w19, w0
	beq	.L1675
	ldr	x1, .LC264
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1683
.L1692:
	ldr	x1, .LC266
	add	x21, x21, 65536
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	ldr	x1, .LC268
	mov	w0, 1
	ldr	w4, [x21, 1924]
	ldr	w2, [x21, 1944]
	ldr	w3, [x21, 1960]
	bl	dprint_vfmw
	b	.L1683
.L1693:
	ldr	x1, .LC262
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1683
.L1686:
	ldr	x2, .LC247
	mov	w3, 8284
	ldr	x1, .LC248
	mov	w0, 0
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1683
.L1690:
	strb	wzr, [x19, 3268]
	mov	w0, 1
	ldr	x1, .LC260
	str	w23, [x20, 3180]
	bl	dprint_vfmw
	b	.L1683
	.size	dec_ref_pic_marking, .-dec_ref_pic_marking
	.align	3
.LC247:
	.xword	.LC30
	.align	3
.LC248:
	.xword	.LC32
	.align	3
.LC250:
	.xword	.LC249
	.align	3
.LC252:
	.xword	.LC251
	.align	3
.LC254:
	.xword	.LC253
	.align	3
.LC256:
	.xword	.LC255
	.align	3
.LC258:
	.xword	.LC257
	.align	3
.LC260:
	.xword	.LC259
	.align	3
.LC262:
	.xword	.LC261
	.align	3
.LC264:
	.xword	.LC263
	.align	3
.LC266:
	.xword	.LC265
	.align	3
.LC268:
	.xword	.LC267
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessSliceHeaderFirstPart
	.type	ProcessSliceHeaderFirstPart, %function
ProcessSliceHeaderFirstPart:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	bl	_mcount
	cbz	x23, .L1759
	ldr	x1, .LC272
	mov	x0, x23
	bl	ue_v
	mov	w21, w0
	ldr	w0, [x23, 14948]
	sub	w0, w0, #1
	cmp	w21, w0
	bhi	.L1697
	add	x24, x23, 65536
	ldr	w0, [x24, 1920]
	cbnz	w0, .L1697
	mov	w1, w21
	mov	x0, x23
	bl	PPSSPSCheckTmpId
	mov	w22, w0
	cbnz	w0, .L1760
	add	x19, x23, 20480
	mov	w1, 2208
	mov	w20, 4000
	umull	x1, w21, w1
	str	w21, [x19, 1592]
	ldrb	w0, [x19, 1587]
	ldr	x21, [x23, 14968]
	cmp	w0, 5
	ldr	x2, [x23, 14960]
	add	x21, x21, x1
	ldr	w0, [x21, 28]
	umull	x0, w0, w20
	add	x20, x2, x0
	beq	.L1700
	ldr	w0, [x20, 3244]
	cbz	w0, .L1700
.L1701:
	ldr	w1, [x20, 2196]
	mov	x0, x23
	ldr	x2, .LC280
	add	w1, w1, 4
	bl	u_v
	str	w0, [x19, 1600]
	ldr	w1, [x24, 1920]
	cbnz	w1, .L1725
	ldrb	w1, [x19, 1587]
	cmp	w1, 5
	beq	.L1761
.L1704:
	strb	wzr, [x19, 1585]
	strb	wzr, [x19, 1586]
	ldrb	w0, [x20, 18]
	cbz	w0, .L1762
	ldr	w1, [x20, 3252]
	ldr	w2, [x20, 3248]
	add	w0, w1, 1
	madd	w0, w2, w0, w0
.L1728:
	ldrb	w1, [x20, 19]
	cbnz	w1, .L1711
	strb	wzr, [x19, 1588]
.L1713:
	ldr	w1, [x19, 1632]
	cmp	w1, w0
	bcs	.L1763
.L1714:
	ldrb	w0, [x19, 1587]
	cmp	w0, 5
	beq	.L1764
.L1716:
	str	wzr, [x19, 704]
	str	wzr, [x19, 708]
	ldr	w0, [x20, 2200]
	cbz	w0, .L1765
.L1720:
	str	wzr, [x19, 752]
	str	wzr, [x19, 756]
	ldr	w0, [x20, 2200]
	cmp	w0, 1
	beq	.L1766
.L1723:
	ldr	w0, [x24, 1920]
	cbnz	w0, .L1725
	ldrb	w0, [x21, 17]
	cbz	w0, .L1726
	ldr	x1, .LC304
	mov	x0, x23
	bl	ue_v
	cbnz	w0, .L1727
	ldr	w0, [x24, 1920]
	cbnz	w0, .L1727
.L1726:
	mov	x0, x23
	bl	IsNewPic
	uxtb	w0, w0
	strb	w0, [x19, 1589]
	cbnz	w0, .L1739
	ldr	w1, [x19, 1632]
	ldr	w0, [x19, 3264]
	cmp	w1, w0
	bls	.L1767
.L1739:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1700:
	ldrb	w0, [x19, 1584]
	cmp	w0, 2
	beq	.L1701
	ldr	x1, .LC278
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1739
	.p2align 3
.L1711:
	mov	w1, 1
	strb	w1, [x19, 1588]
.L1730:
	ldr	w1, [x19, 1632]
	cmp	w1, w0, lsr 1
	bcc	.L1714
	ldr	x1, .LC288
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1739
	.p2align 3
.L1727:
	ldr	x1, .LC306
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC307
	ldr	x4, [x0]
	cbz	x4, .L1725
	ldr	w0, [x24, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w22, -1
	blr	x4
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1762:
	ldr	x1, .LC284
	mov	x0, x23
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x19, 1585]
	cbnz	w0, .L1768
	ldr	w2, [x20, 3252]
	ldr	w1, [x20, 3248]
	add	w0, w2, 1
	ldrb	w3, [x20, 18]
	madd	w1, w1, w0, w0
	lsl	w0, w1, 1
	cbz	w3, .L1728
.L1708:
	ldrb	w2, [x19, 1585]
	mov	w0, 1
	b	.L1709
	.p2align 3
.L1765:
	ldr	w1, [x20, 2204]
	mov	x0, x23
	ldr	x2, .LC296
	add	w1, w1, 4
	bl	u_v
	str	w0, [x19, 704]
	ldrb	w0, [x21, 1]
	cbz	w0, .L1720
	ldrb	w0, [x19, 1585]
	cbnz	w0, .L1720
	ldr	x1, .LC298
	mov	x0, x23
	bl	se_v
	str	w0, [x19, 708]
	b	.L1720
	.p2align 3
.L1761:
	str	w0, [x19, 1596]
	cbz	w0, .L1704
	ldr	x1, .LC282
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1704
	.p2align 3
.L1766:
	ldrb	w0, [x20, 16]
	cbnz	w0, .L1723
	ldr	x1, .LC300
	mov	x0, x23
	bl	se_v
	str	w0, [x19, 752]
	ldrb	w0, [x21, 1]
	cmp	w0, 1
	bne	.L1723
	ldrb	w0, [x19, 1585]
	cbnz	w0, .L1723
	ldr	x1, .LC302
	mov	x0, x23
	bl	se_v
	str	w0, [x19, 756]
	b	.L1723
	.p2align 3
.L1725:
	mov	w22, -1
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1768:
	ldr	x1, .LC286
	mov	x0, x23
	bl	u_1
	strb	w0, [x19, 1586]
	ldr	w0, [x20, 3252]
	ldr	w1, [x20, 3248]
	ldrb	w2, [x20, 18]
	add	w0, w0, 1
	madd	w1, w1, w0, w0
	cbnz	w2, .L1708
	ldrb	w2, [x19, 1585]
	mov	w0, 2
.L1709:
	mul	w0, w0, w1
	cbz	w2, .L1728
	strb	wzr, [x19, 1588]
	cmp	w2, 1
	bne	.L1713
	b	.L1730
	.p2align 3
.L1764:
	ldr	x1, .LC292
	mov	x0, x23
	bl	ue_v
	str	w0, [x19, 1620]
	mov	w1, 65535
	cmp	w0, w1
	bhi	.L1717
	ldr	w0, [x24, 1920]
	cbz	w0, .L1716
.L1717:
	ldr	x1, .LC294
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1716
	.p2align 3
.L1697:
	ldr	x1, .LC274
	mov	w2, w21
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1760:
	ldr	x1, .LC276
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1739
.L1759:
	ldr	x2, .LC269
	mov	w3, 8378
	ldr	x1, .LC270
	mov	w0, 0
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1739
.L1763:
	ldr	x1, .LC290
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1739
.L1767:
	ldr	x1, .LC309
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L1739
	.size	ProcessSliceHeaderFirstPart, .-ProcessSliceHeaderFirstPart
	.align	3
.LC269:
	.xword	.LC30
	.align	3
.LC270:
	.xword	.LC32
	.align	3
.LC272:
	.xword	.LC271
	.align	3
.LC274:
	.xword	.LC273
	.align	3
.LC276:
	.xword	.LC275
	.align	3
.LC278:
	.xword	.LC277
	.align	3
.LC280:
	.xword	.LC279
	.align	3
.LC282:
	.xword	.LC281
	.align	3
.LC284:
	.xword	.LC283
	.align	3
.LC286:
	.xword	.LC285
	.align	3
.LC288:
	.xword	.LC287
	.align	3
.LC290:
	.xword	.LC289
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
.LC307:
	.xword	g_event_report
	.align	3
.LC309:
	.xword	.LC308
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessSliceHeaderSecondPart
	.type	ProcessSliceHeaderSecondPart, %function
ProcessSliceHeaderSecondPart:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1855
	add	x19, x20, 20480
	ldr	w0, [x20, 14948]
	sub	w0, w0, #1
	ldr	w2, [x19, 1592]
	cmp	w0, w2
	bcc	.L1772
	add	x25, x20, 65536
	ldr	w0, [x25, 1920]
	cbnz	w0, .L1772
	mov	x0, x20
	bl	PPSSPSCheck
	cbnz	w0, .L1856
	ldr	w21, [x19, 1592]
	mov	w1, 2208
	ldr	x23, [x20, 14968]
	umull	x21, w21, w1
	adds	x22, x23, x21
	beq	.L1857
	ldrb	w1, [x19, 1584]
	cmp	w1, 1
	beq	.L1858
	ldr	w0, [x22, 36]
	cmp	w1, 1
	str	w0, [x19, 1636]
	ldr	w0, [x22, 40]
	str	w0, [x19, 1640]
	bls	.L1859
.L1777:
	cmp	w1, 2
	beq	.L1803
.L1787:
	mov	w0, 32
	str	w0, [x19, 1640]
.L1788:
	mov	x0, x20
	bl	ref_pic_list_reordering
	mov	w24, w0
	cbnz	w0, .L1860
	ldrb	w0, [x22, 2]
	cbz	w0, .L1790
	ldrb	w0, [x19, 1584]
	cbnz	w0, .L1790
	mov	w0, 1
	mov	w2, w0
.L1866:
	ldr	x1, .LC329
	strb	w0, [x19, 1591]
	mov	w0, 19
	bl	dprint_vfmw
	str	wzr, [x19, 1644]
	ldrb	w0, [x19, 1591]
	str	wzr, [x19, 1648]
	cbz	w0, .L1792
.L1862:
	mov	x0, x20
	bl	pred_weight_table
	cbz	w0, .L1792
	ldr	x1, .LC331
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1790:
	ldr	w0, [x22, 44]
	cmp	w0, 1
	beq	.L1861
.L1807:
	mov	w0, 0
	ldr	x1, .LC329
	strb	w0, [x19, 1591]
	mov	w2, 0
	mov	w0, 19
	bl	dprint_vfmw
	str	wzr, [x19, 1644]
	ldrb	w0, [x19, 1591]
	str	wzr, [x19, 1648]
	cbnz	w0, .L1862
.L1792:
	ldr	w0, [x19, 1612]
	cbnz	w0, .L1863
.L1793:
	str	wzr, [x19, 3188]
	ldrb	w0, [x23, x21]
	cbz	w0, .L1794
	ldrb	w0, [x19, 1584]
	cmp	w0, 1
	bls	.L1864
.L1794:
	ldr	x1, .LC339
	mov	x0, x20
	bl	se_v
	add	x1, x19, 3072
	stp	w0, wzr, [x1, 120]
	stp	wzr, wzr, [x1, 128]
	ldrb	w0, [x22, 3]
	cbnz	w0, .L1865
.L1823:
	mov	w0, w24
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1865:
	ldr	x1, .LC341
	mov	x0, x20
	bl	ue_v
	cmp	w0, 2
	str	w0, [x19, 3196]
	bhi	.L1797
	ldr	w1, [x25, 1920]
	cbnz	w1, .L1797
	cmp	w0, 1
	beq	.L1823
	ldr	x1, .LC345
	mov	x0, x20
	bl	se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 3200]
	bhi	.L1800
	ldr	w0, [x25, 1920]
	cbnz	w0, .L1800
	ldr	x1, .LC349
	mov	x0, x20
	bl	se_v
	add	w1, w0, 6
	cmp	w1, 12
	str	w0, [x19, 3204]
	bhi	.L1802
	ldr	w0, [x25, 1920]
	cbz	w0, .L1823
.L1802:
	ldr	x1, .LC351
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1863:
	mov	x0, x20
	bl	dec_ref_pic_marking
	cbz	w0, .L1793
	ldr	x1, .LC333
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1803:
	mov	w0, 32
	str	w0, [x19, 1636]
	b	.L1787
	.p2align 3
.L1861:
	ldrb	w0, [x19, 1584]
	cmp	w0, 1
	bne	.L1807
	mov	w2, w0
	b	.L1866
	.p2align 3
.L1858:
	ldr	x1, .LC315
	mov	x0, x20
	bl	u_1
	strb	w0, [x19, 1590]
	ldrb	w1, [x19, 1584]
	ldr	w0, [x22, 36]
	str	w0, [x19, 1636]
	cmp	w1, 1
	ldr	w0, [x22, 40]
	str	w0, [x19, 1640]
	bhi	.L1777
	.p2align 2
.L1859:
	ldr	x1, .LC317
	mov	x0, x20
	bl	u_1
	cbnz	w0, .L1778
	ldr	w1, [x19, 1636]
.L1779:
	ldrb	w0, [x19, 1585]
	cbnz	w0, .L1780
	cmp	w1, 15
	bhi	.L1781
	ldr	w0, [x19, 1640]
	cmp	w0, 15
	bhi	.L1867
.L1782:
	ldr	w0, [x25, 1920]
	cbnz	w0, .L1781
.L1783:
	ldrb	w0, [x19, 1584]
	cmp	w0, 2
	beq	.L1803
	cmp	w0, 1
	beq	.L1788
	b	.L1787
	.p2align 3
.L1772:
	ldr	x1, .LC312
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1864:
	ldr	x1, .LC335
	mov	x0, x20
	bl	ue_v
	cmp	w0, 2
	str	w0, [x19, 3188]
	bhi	.L1795
	ldr	w0, [x25, 1920]
	cbz	w0, .L1794
.L1795:
	ldr	x1, .LC337
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1780:
	cmp	w1, 31
	bhi	.L1784
	ldr	w0, [x19, 1640]
	cmp	w0, 31
	bls	.L1785
	ldrb	w0, [x19, 1584]
	cmp	w0, 1
	bne	.L1785
.L1784:
	ldr	x1, .LC325
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1785:
	ldr	w0, [x25, 1920]
	cbz	w0, .L1783
	b	.L1784
	.p2align 3
.L1867:
	ldrb	w0, [x19, 1584]
	cmp	w0, 1
	bne	.L1782
.L1781:
	ldr	x1, .LC323
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1778:
	ldr	x1, .LC319
	mov	x0, x20
	bl	ue_v
	mov	w1, w0
	ldrb	w0, [x19, 1584]
	str	w1, [x19, 1636]
	cmp	w0, 1
	bne	.L1779
	ldr	x1, .LC321
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 1640]
	ldr	w1, [x19, 1636]
	b	.L1779
	.p2align 3
.L1800:
	ldr	x1, .LC347
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1797:
	ldr	x1, .LC343
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1856:
	ldr	x1, .LC313
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.p2align 3
.L1860:
	ldr	x1, .LC327
	mov	w0, 1
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
.L1855:
	ldr	x2, .LC310
	mov	w3, 8542
	ldr	x1, .LC311
	mov	w0, 0
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
.L1857:
	ldr	x2, .LC310
	mov	w3, 8559
	ldr	x1, .LC311
	mov	w24, -1
	bl	dprint_vfmw
	b	.L1823
	.size	ProcessSliceHeaderSecondPart, .-ProcessSliceHeaderSecondPart
	.align	3
.LC310:
	.xword	.LC30
	.align	3
.LC311:
	.xword	.LC32
	.align	3
.LC312:
	.xword	.LC273
	.align	3
.LC313:
	.xword	.LC275
	.align	3
.LC315:
	.xword	.LC314
	.align	3
.LC317:
	.xword	.LC316
	.align	3
.LC319:
	.xword	.LC318
	.align	3
.LC321:
	.xword	.LC320
	.align	3
.LC323:
	.xword	.LC322
	.align	3
.LC325:
	.xword	.LC324
	.align	3
.LC327:
	.xword	.LC326
	.align	3
.LC329:
	.xword	.LC328
	.align	3
.LC331:
	.xword	.LC330
	.align	3
.LC333:
	.xword	.LC332
	.align	3
.LC335:
	.xword	.LC334
	.align	3
.LC337:
	.xword	.LC336
	.align	3
.LC339:
	.xword	.LC338
	.align	3
.LC341:
	.xword	.LC340
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
.LC351:
	.xword	.LC350
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ExitSlice
	.type	ExitSlice, %function
ExitSlice:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1878
	add	x0, x19, 20480
	mov	w2, 2208
	ldr	x8, [x19, 14968]
	mov	w1, 4000
	ldr	x7, [x19, 14960]
	ldr	w4, [x0, 1592]
	ldrb	w3, [x0, 1585]
	ldr	w5, [x0, 1600]
	umull	x2, w4, w2
	ldr	w6, [x0, 1632]
	add	x2, x8, x2
	ldr	w2, [x2, 28]
	str	w4, [x0, 3232]
	umull	x1, w2, w1
	add	x1, x7, x1
	ldr	w2, [x1, 36]
	str	w2, [x0, 3228]
	strb	w3, [x0, 3224]
	str	w5, [x0, 3240]
	str	w6, [x0, 3264]
	cbnz	w3, .L1879
	ldrb	w2, [x0, 1587]
	ldr	w3, [x0, 1612]
	strb	w2, [x0, 3226]
	cmp	w2, 5
	str	w3, [x0, 3236]
	beq	.L1880
.L1872:
	ldr	w2, [x1, 2200]
	cbz	w2, .L1881
	cmp	w2, 1
	beq	.L1882
.L1874:
	add	x19, x19, 65536
	ldr	w0, [x19, 1936]
	add	w0, w0, 1
	str	w0, [x19, 1936]
.L1868:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1881:
	ldr	w2, [x0, 708]
	ldr	w3, [x0, 704]
	str	w3, [x0, 3248]
	str	w2, [x0, 3252]
	ldr	w2, [x1, 2200]
	cmp	w2, 1
	bne	.L1874
.L1882:
	ldr	w2, [x0, 752]
	ldr	w1, [x0, 756]
	str	w2, [x0, 3256]
	str	w1, [x0, 3260]
	b	.L1874
	.p2align 3
.L1879:
	ldrb	w2, [x0, 1586]
	strb	w2, [x0, 3225]
	ldrb	w2, [x0, 1587]
	ldr	w3, [x0, 1612]
	strb	w2, [x0, 3226]
	cmp	w2, 5
	str	w3, [x0, 3236]
	bne	.L1872
.L1880:
	ldr	w2, [x0, 1620]
	str	w2, [x0, 3244]
	b	.L1872
	.p2align 3
.L1878:
	ldr	x2, .LC352
	mov	w3, 8730
	ldr	x1, .LC353
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1868
	.size	ExitSlice, .-ExitSlice
	.align	3
.LC352:
	.xword	.LC30
	.align	3
.LC353:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PicTypeStatistic
	.type	PicTypeStatistic, %function
PicTypeStatistic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1894
	add	x1, x19, 20480
	ldrb	w0, [x1, 1584]
	cmp	w0, 1
	beq	.L1886
	cbz	w0, .L1887
	cmp	w0, 2
	bne	.L1883
	ldrb	w0, [x1, 1587]
	add	x19, x19, 61440
	cmp	w0, 5
	beq	.L1895
.L1889:
	str	wzr, [x19, 2728]
.L1883:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1887:
	add	x19, x19, 61440
	ldr	w0, [x19, 2724]
	cmp	w0, 2
	beq	.L1889
	mov	w0, 1
	str	w0, [x19, 2724]
	b	.L1889
	.p2align 3
.L1886:
	add	x19, x19, 61440
	mov	w0, 2
	str	wzr, [x19, 2728]
	str	w0, [x19, 2724]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1895:
	mov	w0, 1
	str	w0, [x19, 2728]
	b	.L1883
	.p2align 3
.L1894:
	ldr	x2, .LC354
	mov	w3, 8781
	ldr	x1, .LC355
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1883
	.size	PicTypeStatistic, .-PicTypeStatistic
	.align	3
.LC354:
	.xword	.LC30
	.align	3
.LC355:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CalcStreamBits
	.type	CalcStreamBits, %function
CalcStreamBits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1921
	add	x0, x19, 16384
	ldrb	w0, [x0, 2592]
	cbnz	w0, .L1922
.L1899:
	ldr	x3, [x19, 632]
	ldrb	w21, [x3]
	cbz	w21, .L1909
	sub	w1, w21, #1
	mov	w4, 32
	mov	x2, 48
	add	x0, x3, 16
	mov	w20, 0
	umaddl	x2, w1, w4, x2
	add	x2, x3, x2
	.p2align 2
.L1901:
	ldr	w1, [x0], 32
	cmp	x0, x2
	add	w20, w20, w1
	bne	.L1901
.L1900:
	sbfiz	x4, x21, 5, 32
	ldr	w2, [x3, 72]
	add	x4, x3, x4
	ldr	w5, [x3, 80]
	ldr	x1, .LC359
	mov	w3, w20
	mov	w0, 7
	ldr	w4, [x4, 16]
	bl	dprint_vfmw
	ldr	x2, [x19, 632]
	ubfiz	x3, x21, 5, 8
	ldrb	w0, [x2]
	ldr	w1, [x2, 72]
	add	x0, x2, x0, lsl 5
	and	w1, w1, 7
	str	w1, [x0, 28]
	ldr	x2, [x19, 632]
	ldrb	w1, [x2]
	ldr	w0, [x2, 72]
	add	x1, x2, x1, lsl 5
	ldr	w2, [x1, 20]
	add	w0, w2, w0, lsr 3
	mov	w2, w21
	sub	w0, w0, w20
	str	w0, [x1, 32]
	ldr	x4, [x19, 632]
	ldrb	w1, [x4]
	ldr	w0, [x4, 72]
	add	x4, x4, x1, lsl 5
	ldr	w1, [x4, 16]
	add	w20, w20, w1
	lsl	w20, w20, 3
	sub	w0, w20, w0
	str	w0, [x4, 24]
	ldr	x1, [x19, 632]
	ldrb	w0, [x1]
	add	x0, x1, x0, lsl 5
	ldp	w4, w1, [x0, 28]
	ubfiz	w1, w1, 3, 2
	add	w1, w1, w4
	str	w1, [x0, 28]
	ldr	x1, .LC361
	ldr	x4, [x19, 632]
	ldrb	w0, [x4]
	add	x4, x4, x0, lsl 5
	mov	w0, 7
	ldr	w5, [x4, 32]
	and	w5, w5, -4
	str	w5, [x4, 32]
	ldr	x6, [x19, 632]
	add	x3, x6, x3
	ldrb	w5, [x6]
	ldp	w4, w3, [x3, 24]
	add	x5, x6, x5, lsl 5
	ldr	w5, [x5, 32]
	bl	dprint_vfmw
	ldr	x0, [x19, 632]
	ldr	w2, [x0, 76]
	sub	w1, w2, #1
	cmp	w1, 1
	bhi	.L1923
	ldrb	w20, [x0]
	add	w3, w20, 1
	cmp	w3, 1
	ccmp	w2, w3, 0, ls
	bls	.L1903
	ldr	x21, .LC365
	add	w20, w20, 2
	.p2align 2
.L1904:
	sub	w2, w20, #1
	mov	x1, x21
	ubfiz	x3, x2, 5, 32
	add	x4, x0, x3
	mov	w0, 7
	str	wzr, [x4, 28]
	ldr	x4, [x19, 632]
	add	x4, x4, x3
	ldr	w5, [x4, 20]
	str	w5, [x4, 32]
	ldr	x4, [x19, 632]
	add	x4, x4, x3
	ldr	w5, [x4, 16]
	lsl	w5, w5, 3
	str	w5, [x4, 24]
	ldr	x4, [x19, 632]
	add	x4, x4, x3
	ldp	w6, w5, [x4, 28]
	ubfiz	w5, w5, 3, 2
	add	w5, w5, w6
	str	w5, [x4, 28]
	ldr	x4, [x19, 632]
	add	x4, x4, x3
	ldr	w5, [x4, 32]
	and	w5, w5, -4
	str	w5, [x4, 32]
	ldr	x4, [x19, 632]
	add	x3, x4, x3
	ldp	w4, w3, [x3, 24]
	bl	dprint_vfmw
	ldr	x0, [x19, 632]
	cmp	w20, 1
	cset	w3, ls
	ldr	w1, [x0, 76]
	cmp	w1, w20
	add	w20, w20, 1
	cset	w2, hi
	tst	w3, w2
	bne	.L1904
	sub	w1, w1, #1
.L1903:
	ubfiz	x1, x1, 5, 32
	ldr	w2, [x0, 80]
	add	x0, x0, x1
	add	x5, x19, 61440
	ldr	w1, [x0, 24]
	sub	w1, w1, w2
	str	w1, [x0, 24]
	ldr	x3, [x19, 632]
	ldrb	w0, [x3]
	ldr	w4, [x3, 76]
	.p2align 2
.L1920:
	cmp	w0, w4
	bcs	.L1896
.L1924:
	ubfiz	x1, x0, 5, 32
	ldr	w2, [x5, 2752]
	add	x1, x3, x1
	add	w0, w0, 1
	ldr	w1, [x1, 32]
	cmp	w1, w2
	bcs	.L1920
	str	w1, [x5, 2752]
	ldr	w4, [x3, 76]
	cmp	w0, w4
	bcc	.L1924
.L1896:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1922:
	ldr	x1, [x19, 632]
	ldr	w0, [x1, 72]
	add	w0, w0, 7
	and	w0, w0, -8
	str	w0, [x1, 72]
	ldr	x1, [x19, 632]
	ldr	w0, [x1, 80]
	sub	w0, w0, #1
	str	w0, [x1, 80]
	b	.L1899
	.p2align 3
.L1923:
	ldr	x1, .LC363
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1909:
	mov	w20, 0
	b	.L1900
.L1921:
	ldr	x2, .LC356
	mov	w3, 8835
	ldr	x1, .LC357
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1896
	.size	CalcStreamBits, .-CalcStreamBits
	.align	3
.LC356:
	.xword	.LC30
	.align	3
.LC357:
	.xword	.LC32
	.align	3
.LC359:
	.xword	.LC358
	.align	3
.LC361:
	.xword	.LC360
	.align	3
.LC363:
	.xword	.LC362
	.align	3
.LC365:
	.xword	.LC364
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsRefListWrong
	.type	IsRefListWrong, %function
IsRefListWrong:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1956
	add	x21, x20, 20480
	ldr	w0, [x21, 1624]
	cbz	w0, .L1928
	mov	w19, 0
	add	x22, x20, 65536
	b	.L1932
	.p2align 3
.L1929:
	ldr	x0, [x0, 32]
	cbz	x0, .L1931
	ldr	w0, [x21, 1624]
	cmp	w0, w19
	bls	.L1957
.L1932:
	add	x1, x20, x19, sxtw 3
	ldr	w0, [x22, 1980]
	add	w19, w19, 1
	ldr	x1, [x1, 28696]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 656]
	bl	FSP_GetLogicFs
	cbnz	x0, .L1929
.L1931:
	mov	w0, -1
.L1959:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1928:
	mov	w0, 0
.L1952:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1957:
	cbz	w0, .L1928
	ldr	w0, [x21, 1628]
	mov	w19, 0
	cbnz	w0, .L1945
	b	.L1928
	.p2align 3
.L1958:
	ldr	x0, [x0, 32]
	cbz	x0, .L1931
	ldr	w0, [x21, 1628]
	cmp	w0, w19
	bls	.L1928
.L1945:
	add	x1, x20, x19, sxtw 3
	ldr	w0, [x22, 1980]
	add	w19, w19, 1
	ldr	x1, [x1, 28960]
	ldr	x1, [x1, 40]
	ldr	w1, [x1, 656]
	bl	FSP_GetLogicFs
	cbnz	x0, .L1958
	mov	w0, -1
	b	.L1959
.L1956:
	ldr	x2, .LC366
	mov	w3, 8944
	ldr	x1, .LC367
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1952
	.size	IsRefListWrong, .-IsRefListWrong
	.align	3
.LC366:
	.xword	.LC30
	.align	3
.LC367:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Scaling_List
	.type	Scaling_List, %function
Scaling_List:
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
	ble	.L1960
	sub	w26, w27, #1
	mov	w0, 8
	ldr	x21, .LC370
	add	x26, x26, 1
	mov	x20, 0
	mov	w24, w0
	mov	w23, 255
	b	.L1965
	.p2align 3
.L1964:
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
	beq	.L1960
.L1965:
	cmp	w27, 16
	add	x1, x21, 16
	beq	.L1973
	ldrb	w19, [x20, x1]
.L1963:
	add	x20, x20, 1
	cbz	w0, .L1964
	ldr	x1, .LC372
	ldr	x0, [x29, 104]
	bl	se_v
	add	w0, w0, w24
	and	w0, w0, 255
	cmp	w19, wzr
	ccmp	w0, wzr, 0, eq
	cset	w1, eq
	cmp	w0, wzr
	csel	w24, w24, w0, eq
	str	w1, [x22]
	b	.L1964
	.p2align 3
.L1973:
	ldrb	w19, [x21, x20]
	b	.L1963
	.p2align 3
.L1960:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	Scaling_List, .-Scaling_List
	.align	3
.LC370:
	.xword	.LANCHOR2
	.align	3
.LC372:
	.xword	.LC371
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessPPS
	.type	ProcessPPS, %function
ProcessPPS:
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
	cbz	x19, .L2028
	cbz	x20, .L2029
	ldr	x1, .LC378
	mov	x0, x19
	add	x21, x19, 65536
	bl	u_1
	strb	w0, [x20]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2027
	ldr	x1, .LC380
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 1]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2027
	ldr	x1, .LC382
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 32]
	cbnz	w0, .L1980
	ldr	w0, [x21, 1920]
	cbz	w0, .L1981
.L1980:
	ldr	x1, .LC384
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC385
	ldr	x4, [x0]
	cbz	x4, .L2027
	ldr	w0, [x21, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	mov	w0, -1
.L1976:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1981:
	ldr	x1, .LC387
	mov	x0, x19
	bl	ue_v
	cmp	w0, 31
	str	w0, [x20, 36]
	bhi	.L1982
	ldr	w0, [x21, 1920]
	cbnz	w0, .L1982
	ldr	x1, .LC391
	mov	x0, x19
	bl	ue_v
	cmp	w0, 31
	str	w0, [x20, 40]
	bhi	.L1984
	ldr	w0, [x21, 1920]
	cbnz	w0, .L1984
	ldr	x1, .LC395
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 2]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2027
	ldr	x2, .LC397
	mov	w1, 2
	mov	x0, x19
	bl	u_v
	cmp	w0, 2
	str	w0, [x20, 44]
	bhi	.L2030
	ldr	x1, .LC401
	mov	x0, x19
	bl	se_v
	str	w0, [x20, 48]
	ldr	x1, .LC403
	mov	x0, x19
	bl	se_v
	ldr	x1, .LC405
	mov	x0, x19
	bl	se_v
	str	w0, [x20, 52]
	ldr	x1, .LC407
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 3]
	ldr	x1, .LC409
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 4]
	ldr	x1, .LC411
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 17]
	cbnz	w0, .L2031
.L1987:
	ldr	w1, [x20, 52]
	add	x0, x19, 12288
	stp	w1, wzr, [x20, 56]
	strb	wzr, [x20, 18]
	add	x0, x0, 2600
	bl	BsResidBits
	ldr	x1, [x19, 632]
	ldr	w1, [x1, 80]
	add	w1, w1, 3
	cmp	w0, w1
	bcc	.L2008
	ldr	x1, .LC415
	mov	x0, x19
	bl	u_1
	str	w0, [x20, 60]
	ldr	x1, .LC417
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 18]
	beq	.L1989
.L2007:
	ldr	x1, .LC419
	mov	x0, x19
	bl	se_v
	add	w1, w0, 12
	cmp	w1, 24
	str	w0, [x20, 56]
	bhi	.L1990
	ldr	w0, [x21, 1920]
	cbz	w0, .L2008
.L1990:
	ldr	x1, .LC426
	mov	w0, 1
	bl	dprint_vfmw
.L2027:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2008:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, 0
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2031:
	ldr	x1, .LC413
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1987
	.p2align 3
.L1982:
	ldr	x1, .LC389
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1976
	.p2align 3
.L1984:
	ldr	x1, .LC393
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1976
	.p2align 3
.L1989:
	ldr	x28, .LC422
	add	x22, x29, 120
	ldr	x26, .LC421
	add	x24, x20, 5
	add	x23, x20, 1984
	add	x25, x20, 64
	mov	w27, 0
	b	.L1998
	.p2align 3
.L2036:
	ldr	w0, [x20, 28]
	mov	w1, 4000
	umull	x0, w0, w1
	ldr	x1, [x19, 14960]
	add	x0, x1, x0
	ldrb	w1, [x0, 25]
	cmp	w1, 1
	beq	.L2032
	ldr	x0, .LC422
	ldr	x3, [x0, 104]
	ldr	x0, .LC374
	add	x1, x0, 96
	cbz	w27, .L2033
.L2026:
	mov	x2, 16
	mov	x0, x23
	blr	x3
.L1993:
	add	w27, w27, 1
	add	x22, x22, 4
	cmp	w27, 6
	add	x24, x24, 1
	add	x23, x23, 16
	add	x25, x25, 64
	beq	.L2034
.L1998:
	mov	x1, x26
	mov	x0, x19
	bl	u_1
	cmp	w0, 1
	strb	w0, [x24]
	str	w0, [x22]
	beq	.L2035
	cmp	w27, wzr
	ccmp	w27, 3, 4, ne
	beq	.L2036
	sub	w1, w27, #1
	ldr	x3, [x28, 104]
	add	x1, x1, 124
	add	x1, x20, x1, lsl 4
	b	.L2026
	.p2align 3
.L2034:
	ldr	x22, .LC422
	add	x26, x20, 2080
	ldr	x24, .LC374
	add	x27, x20, 448
	mov	x28, 0
	add	x23, x29, 112
	mov	w25, 4000
.L2006:
	ldr	w0, [x20, 60]
	mov	w8, w28
	cmp	w0, 1
	beq	.L2037
	add	x0, x20, x28
	str	wzr, [x23, x28, lsl 2]
	strb	wzr, [x0, 11]
.L2001:
	ldr	w0, [x20, 28]
	ldr	x1, [x19, 14960]
	umull	x0, w0, w25
	add	x0, x1, x0
	ldrb	w1, [x0, 25]
	cmp	w1, 1
	beq	.L2038
	add	x1, x24, 176
	ldr	x3, [x22, 104]
	cbz	w8, .L2039
.L2005:
	mov	x2, 64
	mov	x0, x26
	blr	x3
.L2002:
	add	x28, x28, 1
	add	x26, x26, 64
	cmp	x28, 2
	add	x27, x27, 256
	bne	.L2006
	b	.L2007
	.p2align 3
.L2035:
	mov	x0, x19
	mov	x4, x22
	mov	w3, 16
	mov	x2, x23
	mov	x1, x25
	bl	Scaling_List
	ldr	w0, [x22]
	cmp	w0, 1
	bne	.L1993
	ldr	x0, .LC374
	cmp	w27, 2
	add	x1, x0, 80
	add	x0, x0, 96
	csel	x1, x0, x1, hi
.L2025:
	ldr	x0, .LC422
	mov	x2, 16
	ldr	x3, [x0, 104]
	mov	x0, x23
	blr	x3
	b	.L1993
.L2029:
	ldr	x2, .LC375
	mov	w3, 9224
	ldr	x1, .LC376
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1976
.L2032:
	uxtw	x1, w27
	add	x1, x0, x1, lsl 4
	add	x1, x1, 1972
	b	.L2025
.L2030:
	ldr	x1, .LC399
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1976
.L2037:
	ldr	x1, .LC424
	mov	x0, x19
	str	w28, [x29, 108]
	bl	u_1
	cmp	w0, 1
	add	x1, x20, x28
	str	w0, [x23, x28, lsl 2]
	ldr	w8, [x29, 108]
	strb	w0, [x1, 11]
	bne	.L2001
	mov	x0, x19
	add	x4, x23, x28, lsl 2
	mov	w3, 64
	mov	x2, x26
	mov	x1, x27
	str	w8, [x29, 108]
	bl	Scaling_List
	ldr	w0, [x23, x28, lsl 2]
	ldr	w8, [x29, 108]
	cmp	w0, 1
	bne	.L2002
	ldr	x0, .LC422
	ldr	x3, [x0, 104]
	ldr	x0, .LC374
	add	x1, x0, 176
	cbnz	w8, .L2005
	add	x1, x0, 112
	b	.L2005
	.p2align 3
.L2038:
	ubfiz	x8, x8, 6, 32
	mov	x2, 64
	add	x1, x0, x8
	ldr	x0, .LC422
	add	x1, x1, 2068
	ldr	x3, [x0, 104]
	mov	x0, x26
	blr	x3
	b	.L2002
.L2028:
	ldr	x2, .LC375
	mov	w3, 9223
	ldr	x1, .LC376
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1976
.L2039:
	ldr	x1, .LC374
	add	x1, x1, 112
	b	.L2005
.L2033:
	add	x1, x0, 80
	b	.L2026
	.size	ProcessPPS, .-ProcessPPS
	.align	3
.LC374:
	.xword	.LANCHOR1
	.align	3
.LC375:
	.xword	.LC30
	.align	3
.LC376:
	.xword	.LC32
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
.LC385:
	.xword	g_event_report
	.align	3
.LC387:
	.xword	.LC386
	.align	3
.LC389:
	.xword	.LC388
	.align	3
.LC391:
	.xword	.LC390
	.align	3
.LC393:
	.xword	.LC392
	.align	3
.LC395:
	.xword	.LC394
	.align	3
.LC397:
	.xword	.LC396
	.align	3
.LC399:
	.xword	.LC398
	.align	3
.LC401:
	.xword	.LC400
	.align	3
.LC403:
	.xword	.LC402
	.align	3
.LC405:
	.xword	.LC404
	.align	3
.LC407:
	.xword	.LC406
	.align	3
.LC409:
	.xword	.LC408
	.align	3
.LC411:
	.xword	.LC410
	.align	3
.LC413:
	.xword	.LC412
	.align	3
.LC415:
	.xword	.LC414
	.align	3
.LC417:
	.xword	.LC416
	.align	3
.LC419:
	.xword	.LC418
	.align	3
.LC421:
	.xword	.LC420
	.align	3
.LC422:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC424:
	.xword	.LC423
	.align	3
.LC426:
	.xword	.LC425
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PPSEqual
	.type	PPSEqual, %function
PPSEqual:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L2062
	cbz	x20, .L2063
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
	ldr	w10, [x19, 60]
	cmp	w5, w4
	ldrb	w5, [x20, 2]
	ccmp	w3, w0, 0, eq
	ldr	w4, [x19, 44]
	cset	w3, eq
	cmp	w7, w5
	ldp	w0, w5, [x20, 44]
	ldr	w7, [x19, 52]
	and	w1, w1, w2
	ccmp	w4, w0, 0, eq
	ldr	w4, [x20, 52]
	cset	w0, eq
	cmp	w6, w5
	ldrb	w5, [x20, 3]
	and	w1, w3, w1
	ldrb	w6, [x19, 3]
	ccmp	w7, w4, 0, eq
	cset	w4, eq
	ldrb	w2, [x20, 4]
	and	w0, w0, w1
	cmp	w6, w5
	ldrb	w5, [x19, 4]
	and	w0, w4, w0
	ldr	w4, [x20, 60]
	ccmp	w5, w2, 0, eq
	ldrb	w3, [x19, 18]
	ldrb	w1, [x20, 18]
	cset	w2, eq
	cmp	w4, w10
	and	w0, w2, w0
	ccmp	w1, w3, 0, eq
	cset	w2, eq
	and	w2, w2, w0
	cbz	w3, .L2044
	lsl	w10, w10, 1
	cmn	w10, #6
	beq	.L2044
	mov	x1, x20
	add	x7, x19, 64
	mov	w9, -6
	mov	x8, 0
	.p2align 2
.L2049:
	add	x3, x19, x8
	add	x0, x20, x8
	ldrsb	w3, [x3, 5]
	ldrsb	w0, [x0, 5]
	cmp	w0, w3
	cset	w0, eq
	and	w2, w2, w0
	cbz	w3, .L2045
	cmp	w8, 5
	bhi	.L2046
	sub	x0, x7, #64
	mov	x3, x1
	.p2align 2
.L2047:
	ldr	w5, [x0, 64]
	add	x0, x0, 4
	ldr	w4, [x3, 64]
	add	x3, x3, 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x7, x0
	and	w2, w2, w4
	bne	.L2047
.L2045:
	add	w9, w9, 1
	add	x8, x8, 1
	cmp	w9, w10
	add	x1, x1, 64
	add	x7, x7, 64
	bne	.L2049
.L2044:
	ldr	w0, [x20, 56]
	ldr	w1, [x19, 56]
	cmp	w1, w0
	cset	w0, eq
	tst	w0, w2
	csetm	w0, eq
.L2042:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2046:
	ubfiz	x0, x9, 8, 32
	add	x3, x0, 448
	add	x6, x0, 704
	add	x6, x19, x6
	add	x0, x19, x3
	add	x3, x20, x3
	.p2align 2
.L2048:
	ldr	w5, [x0], 4
	ldr	w4, [x3], 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x6, x0
	and	w2, w2, w4
	bne	.L2048
	add	w9, w9, 1
	add	x8, x8, 1
	cmp	w9, w10
	add	x1, x1, 64
	add	x7, x7, 64
	bne	.L2049
	b	.L2044
.L2063:
	ldr	x2, .LC427
	mov	w3, 9410
	ldr	x1, .LC428
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2042
.L2062:
	ldr	x2, .LC427
	mov	w3, 9409
	ldr	x1, .LC428
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2042
	.size	PPSEqual, .-PPSEqual
	.align	3
.LC427:
	.xword	.LC30
	.align	3
.LC428:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecPPS
	.type	H264_DecPPS, %function
H264_DecPPS:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2078
	ldr	x1, .LC432
	mov	x0, x19
	bl	ue_v
	mov	w20, w0
	ldr	w0, [x19, 14948]
	sub	w0, w0, #1
	cmp	w20, w0
	bhi	.L2079
	ldr	x1, .LC437
	mov	x0, x19
	bl	ue_v
	mov	w2, w0
	ldr	w0, [x19, 14944]
	sub	w0, w0, #1
	cmp	w2, w0
	bhi	.L2080
	mov	w0, 4000
	ldr	x1, [x19, 14960]
	umull	x0, w2, w0
	add	x0, x1, x0
	ldrb	w0, [x0, 23]
	cbz	w0, .L2081
	mov	w21, 2208
	ldr	x0, [x19, 14968]
	umull	x21, w20, w21
	add	x0, x0, x21
	ldrb	w1, [x0, 19]
	cbz	w1, .L2070
	ldr	x22, .LC442
	mov	x0, x19
	mov	x1, x22
	stp	w20, w2, [x22, 24]
	bl	ProcessPPS
	cbnz	w0, .L2082
	ldr	x1, [x19, 14968]
	mov	x0, x22
	add	x1, x1, x21
	bl	PPSEqual
	cbz	w0, .L2066
	ldr	x3, .LC446
	mov	w1, 1
	ldr	x0, [x19, 14968]
	mov	x2, 2208
	strb	w1, [x22, 20]
	ldr	x3, [x3, 112]
	add	x0, x0, x21
	strb	w1, [x22, 19]
	mov	x1, x22
	blr	x3
	mov	w0, 0
	b	.L2066
	.p2align 3
.L2079:
	ldr	x1, .LC434
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 14948]
	sub	w1, w0, #1
	cmp	w20, w1
	bls	.L2074
	ldr	x1, .LC435
	ldr	x4, [x1]
	cbz	x4, .L2074
	add	x19, x19, 65536
	mov	w3, 8
	stp	w20, w0, [x29, 56]
	add	x2, x29, 56
	mov	w1, 110
	ldr	w0, [x19, 1980]
	blr	x4
	mov	w0, -1
.L2066:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2070:
	str	w20, [x0, 24]
	mov	x0, x19
	ldr	x1, [x19, 14968]
	add	x1, x1, x21
	str	w2, [x1, 28]
	ldr	x1, [x19, 14968]
	add	x1, x1, x21
	bl	ProcessPPS
	cbnz	w0, .L2083
	ldr	x1, [x19, 14968]
	mov	w2, 1
	add	x1, x1, x21
	strb	w2, [x1, 20]
	ldr	x1, [x19, 14968]
	add	x21, x1, x21
	strb	w2, [x21, 19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2074:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 64
	ret
.L2082:
	ldr	x2, .LC443
	mov	w0, 1
	ldr	x1, .LC445
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2066
.L2080:
	ldr	x1, .LC439
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2066
.L2081:
	ldr	x1, .LC441
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2066
.L2078:
	ldr	x2, .LC429
	mov	w3, 9477
	ldr	x1, .LC430
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2066
.L2083:
	ldr	x2, .LC443
	mov	w0, 1
	ldr	x1, .LC448
	add	x2, x2, 80
	bl	dprint_vfmw
	ldr	x1, [x19, 14968]
	mov	w2, 1
	mov	w0, -1
	add	x1, x1, x21
	strb	w2, [x1, 20]
	ldr	x1, [x19, 14968]
	add	x21, x1, x21
	strb	wzr, [x21, 19]
	b	.L2066
	.size	H264_DecPPS, .-H264_DecPPS
	.align	3
.LC429:
	.xword	.LC30
	.align	3
.LC430:
	.xword	.LC32
	.align	3
.LC432:
	.xword	.LC431
	.align	3
.LC434:
	.xword	.LC433
	.align	3
.LC435:
	.xword	g_event_report
	.align	3
.LC437:
	.xword	.LC436
	.align	3
.LC439:
	.xword	.LC438
	.align	3
.LC441:
	.xword	.LC440
	.align	3
.LC442:
	.xword	.LANCHOR3
	.align	3
.LC443:
	.xword	.LANCHOR2
	.align	3
.LC445:
	.xword	.LC444
	.align	3
.LC446:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC448:
	.xword	.LC447
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	vui_parameters
	.type	vui_parameters, %function
vui_parameters:
	stp	x29, x30, [sp, -96]!
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
	cbz	x19, .L2128
	ldr	x1, .LC450
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20]
	cbnz	w0, .L2129
	strb	wzr, [x20, 15]
.L2088:
	ldr	x1, .LC458
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 1]
	cbnz	w0, .L2130
.L2089:
	ldr	x1, .LC462
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 3]
	cbnz	w0, .L2131
	mov	w0, 5
	str	w0, [x20, 28]
.L2091:
	ldr	x1, .LC476
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 6]
	cbnz	w0, .L2132
.L2092:
	ldr	x1, .LC482
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 8]
	cbnz	w0, .L2133
.L2094:
	ldr	x1, .LC491
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 7]
	cbz	w0, .L2096
	ldr	x1, .LC493
	mov	x0, x19
	add	x24, x20, 84
	bl	ue_v
	ldr	x2, .LC495
	mov	w1, 4
	str	w0, [x24, 36]
	mov	x0, x19
	bl	u_v
	strb	w0, [x24, 32]
	ldr	x2, .LC497
	mov	w1, 4
	mov	x0, x19
	bl	u_v
	strb	w0, [x24, 33]
	ldr	w1, [x24, 36]
	cmp	w1, 31
	bhi	.L2098
	add	x28, x19, 65536
	ldr	w0, [x28, 1920]
	cbnz	w0, .L2098
	ldr	x27, .LC501
	mov	w21, 0
	ldr	x26, .LC503
	ldr	x25, .LC505
	.p2align 2
.L2099:
	uxtw	x22, w21
	mov	x1, x27
	mov	x0, x19
	add	w21, w21, 1
	add	x23, x20, x22, lsl 2
	bl	ue_v
	mov	x1, x26
	str	w0, [x23, 124]
	mov	x0, x19
	bl	ue_v
	str	w0, [x23, 252]
	mov	x1, x25
	mov	x0, x19
	bl	u_1
	strb	w0, [x24, x22]
	ldr	w0, [x24, 36]
	cmp	w0, w21
	bcs	.L2099
	ldr	x2, .LC507
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 296]
	ldr	x2, .LC509
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 300]
	ldr	x2, .LC511
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 304]
	ldr	x2, .LC513
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 308]
.L2096:
	ldr	x1, .LC515
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 10]
	cbnz	w0, .L2134
	ldrb	w0, [x20, 7]
	add	x28, x19, 65536
	cbz	w0, .L2103
.L2104:
	ldr	x1, .LC517
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 14]
.L2103:
	ldr	x1, .LC519
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 11]
	ldr	x1, .LC521
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 12]
	cbnz	w0, .L2105
	ldr	w0, [x28, 1920]
.L2106:
	cmp	w0, wzr
	csetm	w0, ne
.L2127:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2133:
	ldr	x2, .LC484
	mov	w1, 32
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 52]
	ldr	x2, .LC486
	mov	w1, 32
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 56]
	ldr	x1, .LC488
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 9]
	ldr	w1, [x20, 52]
	cbz	w1, .L2094
	ldr	w0, [x20, 56]
	mov	w3, 10000
	ldr	x2, .LC489
	add	x28, x19, 65536
	umull	x0, w0, w3
	ldr	x2, [x2, 488]
	lsr	x0, x0, 1
	blr	x2
	add	w0, w0, 5
	mov	w1, 52429
	movk	w1, 0xcccc, lsl 16
	umull	x0, w0, w1
	lsr	x0, x0, 35
	str	w0, [x28, 660]
	b	.L2094
	.p2align 3
.L2132:
	ldr	x1, .LC478
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 44]
	ldr	x1, .LC480
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 48]
	b	.L2092
	.p2align 3
.L2131:
	ldr	x2, .LC464
	mov	w1, 3
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 28]
	ldr	x1, .LC466
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 4]
	ldr	x1, .LC468
	mov	x0, x19
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x20, 5]
	cbz	w0, .L2091
	ldr	x2, .LC470
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 32]
	ldr	x2, .LC472
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 36]
	ldr	x2, .LC474
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 40]
	b	.L2091
	.p2align 3
.L2130:
	ldr	x1, .LC460
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 2]
	b	.L2089
	.p2align 3
.L2129:
	ldr	x2, .LC452
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	uxtb	w0, w0
	cmp	w0, 255
	strb	w0, [x20, 15]
	bne	.L2088
	ldr	x2, .LC454
	mov	w1, 16
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 16]
	ldr	x2, .LC456
	mov	w1, 16
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 20]
	b	.L2088
	.p2align 3
.L2134:
	ldr	x1, .LC493
	mov	x0, x19
	add	x24, x20, 396
	bl	ue_v
	ldr	x2, .LC495
	mov	w1, 4
	str	w0, [x24, 36]
	mov	x0, x19
	bl	u_v
	strb	w0, [x24, 32]
	ldr	x2, .LC497
	mov	w1, 4
	mov	x0, x19
	bl	u_v
	strb	w0, [x24, 33]
	ldr	w1, [x24, 36]
	cmp	w1, 31
	bhi	.L2098
	add	x28, x19, 65536
	ldr	w0, [x28, 1920]
	cbnz	w0, .L2098
	ldr	x27, .LC501
	mov	w21, 0
	ldr	x26, .LC503
	ldr	x25, .LC505
	.p2align 2
.L2101:
	uxtw	x22, w21
	mov	x1, x27
	mov	x0, x19
	add	w21, w21, 1
	add	x23, x20, x22, lsl 2
	bl	ue_v
	mov	x1, x26
	str	w0, [x23, 436]
	mov	x0, x19
	bl	ue_v
	str	w0, [x23, 564]
	mov	x1, x25
	mov	x0, x19
	bl	u_1
	strb	w0, [x24, x22]
	ldr	w0, [x24, 36]
	cmp	w0, w21
	bcs	.L2101
	ldr	x2, .LC507
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 296]
	ldr	x2, .LC509
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 300]
	ldr	x2, .LC511
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 304]
	ldr	x2, .LC513
	mov	w1, 5
	mov	x0, x19
	bl	u_v
	str	w0, [x24, 308]
	ldrb	w0, [x20, 7]
	cbnz	w0, .L2104
	ldrb	w0, [x20, 10]
	cbnz	w0, .L2104
	b	.L2103
	.p2align 3
.L2105:
	ldr	x1, .LC523
	mov	x0, x19
	bl	u_1
	strb	w0, [x20, 13]
	ldr	x1, .LC525
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 60]
	ldr	x1, .LC527
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 64]
	ldr	x1, .LC529
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 72]
	ldr	x1, .LC531
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 68]
	ldr	x1, .LC533
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 76]
	ldr	x1, .LC535
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 80]
	ldr	w0, [x28, 1920]
	cbz	w0, .L2106
.L2128:
	mov	w0, -1
	b	.L2127
.L2098:
	ldr	x1, .LC499
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2127
	.size	vui_parameters, .-vui_parameters
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
.LC489:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC491:
	.xword	.LC490
	.align	3
.LC493:
	.xword	.LC492
	.align	3
.LC495:
	.xword	.LC494
	.align	3
.LC497:
	.xword	.LC496
	.align	3
.LC499:
	.xword	.LC498
	.align	3
.LC501:
	.xword	.LC500
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
.LC521:
	.xword	.LC520
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SPSEqual
	.type	SPSEqual, %function
SPSEqual:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	x19, .L2167
	cbz	x20, .L2168
	ldp	w3, w6, [x19, 28]
	ldp	w2, w5, [x20, 28]
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
	ldr	w2, [x20, 36]
	ccmp	w1, w0, 0, eq
	ldr	w4, [x19, 36]
	cset	w0, eq
	ldrb	w1, [x19, 25]
	and	w0, w3, w0
	cmp	w6, w5
	ldrb	w3, [x20, 25]
	ccmp	w4, w2, 0, eq
	cset	w2, eq
	cmp	w3, w1
	and	w0, w2, w0
	cset	w2, eq
	and	w0, w2, w0
	cbz	w1, .L2139
	mov	x2, x19
	mov	x8, x20
	mov	w9, -6
	mov	x1, 0
	.p2align 2
.L2144:
	add	x4, x19, x1
	add	x3, x20, x1
	add	x6, x2, 64
	ldrsb	w3, [x3, 4]
	ldrsb	w4, [x4, 4]
	cmp	w3, w4
	cset	w3, eq
	and	w0, w0, w3
	cbz	w4, .L2140
	cmp	w1, 5
	bhi	.L2141
	mov	x3, x8
	.p2align 2
.L2142:
	ldr	w5, [x2, 52]
	add	x2, x2, 4
	ldr	w4, [x3, 52]
	add	x3, x3, 4
	cmp	w5, w4
	cset	w4, eq
	cmp	x2, x6
	and	w0, w0, w4
	bne	.L2142
.L2140:
	add	x1, x1, 1
	add	w9, w9, 1
	cmp	x1, 8
	mov	x2, x6
	add	x8, x8, 64
	bne	.L2144
.L2139:
	ldr	w4, [x19, 2196]
	ldr	w3, [x20, 2196]
	ldr	w2, [x20, 2200]
	ldr	w1, [x19, 2200]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w0, w2, w0
	cbz	w1, .L2146
	cmp	w1, 1
	bne	.L2145
	ldrb	w4, [x19, 16]
	ldrb	w3, [x20, 16]
	ldr	w2, [x19, 2208]
	ldr	w1, [x20, 2208]
	cmp	w4, w3
	ldr	w5, [x19, 2212]
	ldr	w4, [x20, 2212]
	ccmp	w2, w1, 0, eq
	ldr	w2, [x20, 2216]
	cset	w3, eq
	ldr	w1, [x19, 2216]
	cmp	w5, w4
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w2, w3, w2
	and	w0, w0, w2
	cbz	w1, .L2145
	sub	w5, w1, #1
	add	x2, x20, 2220
	add	x5, x5, 556
	add	x1, x19, 2220
	add	x5, x19, x5, lsl 2
	.p2align 2
.L2148:
	ldr	w4, [x1], 4
	ldr	w3, [x2], 4
	cmp	w4, w3
	cset	w3, eq
	cmp	x1, x5
	and	w0, w0, w3
	bne	.L2148
.L2145:
	ldr	w4, [x19, 3244]
	ldr	w3, [x20, 3244]
	ldrb	w2, [x19, 17]
	ldrb	w1, [x20, 17]
	cmp	w4, w3
	ldr	w6, [x19, 3248]
	ldr	w4, [x20, 3248]
	ccmp	w2, w1, 0, eq
	ldr	w5, [x19, 3252]
	cset	w2, eq
	ldr	w1, [x20, 3252]
	cmp	w6, w4
	ldrb	w3, [x19, 18]
	ldrb	w4, [x20, 18]
	ccmp	w5, w1, 0, eq
	cset	w1, eq
	cmp	w4, w3
	and	w2, w2, w1
	cset	w1, eq
	and	w1, w2, w1
	and	w0, w1, w0
	cbnz	w3, .L2149
	ldrb	w1, [x20, 19]
	ldrb	w2, [x19, 19]
	cmp	w2, w1
	cset	w1, eq
	and	w0, w0, w1
.L2149:
	ldrb	w4, [x19, 20]
	ldrb	w3, [x20, 20]
	ldrb	w2, [x20, 21]
	ldrb	w1, [x19, 21]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w2, eq
	and	w0, w2, w0
	cbnz	w1, .L2169
.L2150:
	ldrb	w4, [x19, 22]
	ldrb	w3, [x20, 22]
	ldr	w1, [x20, 3316]
	ldr	w2, [x19, 3316]
	cmp	w4, w3
	ccmp	w2, w1, 0, eq
	cset	w1, eq
	tst	w1, w0
	csetm	w0, eq
.L2137:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2169:
	ldr	w4, [x19, 3264]
	ldr	w3, [x20, 3264]
	ldr	w2, [x19, 3268]
	ldr	w1, [x20, 3268]
	cmp	w4, w3
	ldr	w5, [x19, 3256]
	ldr	w4, [x20, 3256]
	ccmp	w2, w1, 0, eq
	ldr	w3, [x19, 3260]
	cset	w2, eq
	ldr	w1, [x20, 3260]
	cmp	w5, w4
	ccmp	w3, w1, 0, eq
	cset	w1, eq
	and	w1, w2, w1
	and	w0, w0, w1
	b	.L2150
	.p2align 3
.L2141:
	ubfiz	x3, x9, 8, 32
	add	x4, x3, 436
	add	x7, x3, 692
	add	x7, x19, x7
	add	x3, x19, x4
	add	x4, x20, x4
	.p2align 2
.L2143:
	ldr	w6, [x3], 4
	ldr	w5, [x4], 4
	cmp	w6, w5
	cset	w5, eq
	cmp	x3, x7
	and	w0, w0, w5
	bne	.L2143
	add	x1, x1, 1
	add	x6, x2, 64
	cmp	x1, 8
	add	w9, w9, 1
	mov	x2, x6
	add	x8, x8, 64
	bne	.L2144
	b	.L2139
	.p2align 3
.L2146:
	ldr	w1, [x20, 2204]
	ldr	w2, [x19, 2204]
	cmp	w2, w1
	cset	w1, eq
	and	w0, w0, w1
	b	.L2145
.L2168:
	ldr	x2, .LC536
	mov	w3, 9737
	ldr	x1, .LC537
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2137
.L2167:
	ldr	x2, .LC536
	mov	w3, 9736
	ldr	x1, .LC537
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2137
	.size	SPSEqual, .-SPSEqual
	.align	3
.LC536:
	.xword	.LC30
	.align	3
.LC537:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264GetDar
	.type	H264GetDar, %function
H264GetDar:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w22, w2
	mov	w21, w3
	mov	w23, w4
	bl	_mcount
	cbz	w19, .L2182
	mov	w0, 255
	cmp	w19, 16
	ccmp	w19, w0, 4, gt
	bne	.L2182
	cmp	w20, wzr
	ccmp	w22, wzr, 4, ne
	ccmp	w19, w0, 0, eq
	beq	.L2182
	cmp	w19, 1
	beq	.L2196
	cmp	w19, 255
	beq	.L2173
	ldr	x0, .LC538
	sbfiz	x19, x19, 3, 32
	add	x0, x0, 96
	add	x1, x0, x19
	ldr	w20, [x0, x19]
	ldr	w22, [x1, 4]
.L2173:
	lsl	w20, w20, 10
	lsl	w21, w21, 10
	sdiv	w20, w20, w22
	sdiv	w2, w21, w23
	mul	w2, w20, w2
	cmp	w2, wzr
	add	w0, w2, 1023
	csel	w2, w0, w2, lt
	asr	w2, w2, 10
	subs	w1, w2, #2406
	bmi	.L2197
.L2174:
	subs	w0, w2, #2263
	bmi	.L2198
	cmp	w1, w0
	mov	w19, 4
	blt	.L2171
.L2178:
	subs	w1, w2, #1820
	bmi	.L2199
	cmp	w0, w1
	mov	w19, 3
	blt	.L2171
.L2179:
	subs	w0, w2, #1365
	bmi	.L2200
.L2177:
	mov	w19, 2
	cmp	w1, w0
	csinc	w19, w19, wzr, lt
	b	.L2171
	.p2align 3
.L2182:
	mov	w19, 0
	mov	w2, 0
.L2171:
	ldr	x1, .LC540
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
.L2198:
	mov	w0, 2263
	mov	w19, 4
	sub	w0, w0, w2
	cmp	w1, w0
	blt	.L2171
	b	.L2178
	.p2align 3
.L2197:
	mov	w1, 2406
	sub	w1, w1, w2
	b	.L2174
	.p2align 3
.L2196:
	mov	w0, 2160
	cmp	w21, 3840
	ccmp	w23, w0, 0, eq
	bne	.L2201
.L2185:
	mov	w19, 2
	mov	w2, 0
	b	.L2171
	.p2align 3
.L2201:
	sub	w0, w23, #1080
	mov	w1, 1920
	and	w0, w0, -9
	cmp	w0, wzr
	ccmp	w21, w1, 0, eq
	beq	.L2185
	mov	w0, 720
	cmp	w21, 1280
	ccmp	w23, w0, 0, eq
	beq	.L2185
	mov	w0, 480
	cmp	w21, 640
	ccmp	w23, w0, 0, eq
	mov	w19, 5
	cset	w0, eq
	mov	w2, 0
	cmp	w0, wzr
	csinc	w19, w19, wzr, eq
	b	.L2171
	.p2align 3
.L2199:
	mov	w1, 1820
	mov	w19, 3
	sub	w1, w1, w2
	cmp	w0, w1
	blt	.L2171
	b	.L2179
.L2200:
	mov	w0, 1365
	sub	w0, w0, w2
	b	.L2177
	.size	H264GetDar, .-H264GetDar
	.align	3
.LC538:
	.xword	.LANCHOR2
	.align	3
.LC540:
	.xword	.LC539
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessSPS
	.type	ProcessSPS, %function
ProcessSPS:
	stp	x29, x30, [sp, -144]!
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
	cbz	x20, .L2327
	cbz	x19, .L2330
	ldr	w0, [x19, 28]
	mov	w2, 144
	mov	w1, 110
	mov	w3, 86
	cmp	w0, 122
	ccmp	w0, w2, 4, ne
	cset	w2, eq
	cmp	w0, 100
	ccmp	w0, w1, 4, ne
	cset	w1, eq
	cmp	w0, 83
	ccmp	w0, w3, 4, ne
	orr	w0, w2, w1
	cset	w1, eq
	orr	w0, w1, w0
	cbnz	w0, .L2331
	mov	w0, 1
	strb	wzr, [x19, 25]
	str	w0, [x19, 40]
.L2220:
	ldr	x1, .LC567
	mov	x0, x20
	bl	ue_v
	cmp	w0, 12
	str	w0, [x19, 2196]
	bhi	.L2233
	add	x21, x20, 65536
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2233
	ldr	x1, .LC571
	mov	x0, x20
	bl	ue_v
	cmp	w0, 2
	str	w0, [x19, 2200]
	bhi	.L2235
	ldr	w1, [x21, 1920]
	cbnz	w1, .L2235
	cbz	w0, .L2332
	cmp	w0, 1
	beq	.L2333
.L2239:
	ldr	x1, .LC628
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3244]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2327
	ldr	x1, .LC591
	mov	x0, x20
	bl	u_1
	strb	w0, [x19, 17]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2327
	ldr	x1, .LC593
	mov	x0, x20
	bl	ue_v
	sub	w1, w0, #1
	cmp	w1, 509
	str	w0, [x19, 3248]
	bhi	.L2244
	ldr	w1, [x21, 1920]
	cbnz	w1, .L2244
	ldr	x1, .LC597
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3252]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2327
	ldr	x1, .LC599
	mov	x0, x20
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x19, 18]
	ldr	w1, [x21, 1920]
	cbnz	w1, .L2327
	cbnz	w0, .L2334
	ldr	x1, .LC630
	mov	x0, x20
	bl	u_1
	ldr	w23, [x19, 3252]
	strb	w0, [x19, 19]
	add	w23, w23, 1
	cmp	w23, 255
	bhi	.L2280
	ldr	w0, [x19, 3248]
	cmp	w23, 1
	mov	w24, 2
	add	w0, w0, 1
	ccmp	w0, 3, 0, hi
	cset	w1, ls
	cbnz	w1, .L2280
.L2248:
	mul	w23, w24, w23
	lsl	w25, w0, 4
	mov	w1, 100663296
	lsl	w23, w23, 4
	mul	w0, w25, w23
	lsr	w0, w0, 1
	lsl	w22, w0, 2
	sub	w0, w22, w0
	cmp	w0, w1
	bhi	.L2335
	ldr	w2, [x19, 32]
	sub	w1, w2, #10
	cmp	w1, 31
	bls	.L2336
.L2250:
	ldr	x1, .LC606
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
	.p2align 3
.L2331:
	ldr	x1, .LC546
	mov	x0, x20
	bl	ue_v
	cmp	w0, 1
	str	w0, [x19, 40]
	bls	.L2337
.L2207:
	ldr	x1, .LC548
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC550
	mov	x0, x20
	bl	ue_v
	uxth	w0, w0
	add	w2, w0, 8
	str	w2, [x19, 44]
	cmp	w2, 8
	beq	.L2338
.L2209:
	ldr	x1, .LC552
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC553
	ldr	x4, [x0]
	cbz	x4, .L2327
	add	x20, x20, 65536
	ldr	w0, [x19, 44]
	stp	wzr, w0, [x29, 120]
	mov	w3, 8
	add	x2, x29, 120
	ldr	w0, [x20, 1980]
	mov	w1, 119
	blr	x4
	mov	w0, -1
.L2319:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2337:
	add	x21, x20, 65536
	ldr	w1, [x21, 1920]
	cbnz	w1, .L2207
	ldr	x1, .LC550
	mov	x0, x20
	bl	ue_v
	uxth	w0, w0
	add	w2, w0, 8
	str	w2, [x19, 44]
	cmp	w2, 8
	bne	.L2211
	ldr	w0, [x21, 1920]
	cbz	w0, .L2212
.L2211:
	ldr	x1, .LC552
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC553
	ldr	x4, [x0]
	cbz	x4, .L2212
	ldr	w1, [x19, 44]
	mov	w3, 8
	ldr	w0, [x21, 1980]
	add	x2, x29, 120
	stp	wzr, w1, [x29, 120]
	mov	w1, 119
	blr	x4
.L2212:
	ldr	x1, .LC555
	mov	x0, x20
	bl	ue_v
	uxth	w0, w0
	add	w2, w0, 8
	str	w2, [x19, 48]
	cmp	w2, 8
	bne	.L2214
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2214
.L2215:
	ldr	x1, .LC559
	mov	x0, x20
	bl	u_1
	cbnz	w0, .L2217
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2217
	ldr	x1, .LC563
	mov	x0, x20
	bl	u_1
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 25]
	bne	.L2220
	ldr	x26, .LC542
	add	x21, x29, 120
	ldr	x25, .LC564
	add	x23, x19, 4
	add	x22, x19, 1972
	add	x24, x19, 52
	mov	w28, 0
	ldr	x27, .LC565
	b	.L2226
	.p2align 3
.L2341:
	ldr	x0, .LC542
	cmp	w28, wzr
	ldr	x3, [x27, 104]
	mov	x2, 16
	add	x1, x0, 80
	add	x0, x26, 96
	csel	x1, x0, x1, ne
	mov	x0, x22
	blr	x3
.L2222:
	add	w28, w28, 1
	add	x21, x21, 4
	cmp	w28, 6
	add	x23, x23, 1
	add	x22, x22, 16
	add	x24, x24, 64
	beq	.L2339
.L2226:
	mov	x1, x25
	mov	x0, x20
	bl	u_1
	cmp	w0, 1
	strb	w0, [x23]
	str	w0, [x21]
	beq	.L2340
	cmp	w28, wzr
	ccmp	w28, 3, 4, ne
	beq	.L2341
	ldr	x0, .LC565
	sub	w1, w28, #1
	mov	x2, 16
	add	x1, x19, x1, lsl 4
	ldr	x3, [x0, 104]
	add	x1, x1, 1972
	mov	x0, x22
	blr	x3
	b	.L2222
	.p2align 3
.L2338:
	add	x0, x20, 65536
	ldr	w0, [x0, 1920]
	cbnz	w0, .L2209
	.p2align 2
.L2327:
	mov	w0, -1
.L2349:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2332:
	ldr	x1, .LC575
	mov	x0, x20
	bl	ue_v
	cmp	w0, 12
	str	w0, [x19, 2204]
	bhi	.L2238
	ldr	w0, [x21, 1920]
	cbz	w0, .L2239
.L2238:
	ldr	x1, .LC577
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
	.p2align 3
.L2214:
	ldr	x1, .LC557
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC553
	ldr	x4, [x0]
	cbz	x4, .L2215
	ldr	w1, [x19, 48]
	mov	w3, 8
	ldr	w0, [x21, 1980]
	add	x2, x29, 120
	stp	wzr, w1, [x29, 120]
	mov	w1, 119
	blr	x4
	b	.L2215
	.p2align 3
.L2334:
	ldr	w23, [x19, 3252]
	strb	wzr, [x19, 19]
	sub	w0, w23, #1
	cmp	w0, 509
	bhi	.L2280
	ldr	w0, [x19, 3248]
	mov	w24, 1
	add	w23, w23, 1
	add	w0, w0, w24
	b	.L2248
	.p2align 3
.L2336:
	ldr	x3, .LC604
	ldrh	w1, [x3,w1,uxtw #1]
	adr	x3, .Lrtx2252
	add	x1, x3, w1, sxth #2
	br	x1
.Lrtx2252:
	.section	.rodata
	.align	0
	.align	2
.L2252:
	.2byte	(.L2251 - .Lrtx2252) / 4
	.2byte	(.L2287 - .Lrtx2252) / 4
	.2byte	(.L2254 - .Lrtx2252) / 4
	.2byte	(.L2254 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2254 - .Lrtx2252) / 4
	.2byte	(.L2255 - .Lrtx2252) / 4
	.2byte	(.L2257 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2257 - .Lrtx2252) / 4
	.2byte	(.L2258 - .Lrtx2252) / 4
	.2byte	(.L2259 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2250 - .Lrtx2252) / 4
	.2byte	(.L2261 - .Lrtx2252) / 4
	.2byte	(.L2261 - .Lrtx2252) / 4
	.text
	.p2align 3
.L2254:
	mov	w22, 60416
	movk	w22, 0xd, lsl 16
.L2253:
	udiv	w22, w22, w0
	mov	w2, 16
	ldr	x1, .LC608
	mov	w0, 21
	cmp	w22, w2
	csel	w22, w22, w2, ls
	mov	w2, w22
	bl	dprint_vfmw
	ldr	w2, [x19, 3244]
	cmp	w2, w22
	bhi	.L2262
	ldr	w0, [x21, 1920]
	cbz	w0, .L2263
.L2262:
	ldr	x1, .LC610
	mov	w3, w22
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 3244]
	cmp	w0, 16
	bhi	.L2324
	cmp	w22, w0
	csel	w22, w22, w0, cs
.L2324:
	str	w22, [x19, 3244]
.L2263:
	ldr	x1, .LC612
	mov	x0, x20
	bl	u_1
	strb	w0, [x19, 20]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2327
	ldr	x1, .LC614
	mov	x0, x20
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x19, 21]
	ldr	w1, [x21, 1920]
	cbnz	w1, .L2327
	cbnz	w0, .L2342
.L2265:
	add	x2, x19, 3072
	lsr	w1, w25, 1
	lsr	w0, w23, 1
	stp	w25, w23, [x2, 204]
	stp	w1, w0, [x2, 212]
.L2267:
	ldr	x1, .LC624
	mov	x0, x20
	bl	u_1
	uxtb	w0, w0
	strb	w0, [x19, 22]
	ldr	w1, [x21, 1920]
	cbnz	w1, .L2327
	mov	w1, 2
	str	w1, [x19, 3332]
	cbnz	w0, .L2343
	mov	w0, 5
	strb	wzr, [x19, 3307]
	str	w0, [x19, 3320]
	mov	w0, 0
.L2270:
	ldr	w1, [x19, 3308]
	mov	w4, w23
	ldr	w2, [x19, 3312]
	mov	w3, w25
	bl	H264GetDar
	str	w0, [x19, 3316]
	ldr	w1, [x19, 3244]
	cbnz	w1, .L2273
	ldr	x0, [x20]
.L2274:
	cmp	w22, 16
	mov	w1, 16
	csel	w22, w22, w1, ls
	str	w22, [x20, 14952]
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L2344
.L2277:
	add	w22, w22, 1
	mov	w0, 0
	str	w22, [x19, 3272]
	b	.L2319
	.p2align 3
.L2261:
	mov	w22, 12582912
	b	.L2253
	.p2align 3
.L2257:
	mov	w22, 30208
	movk	w22, 0x2f, lsl 16
	b	.L2253
.L2287:
	mov	w22, 17920
	movk	w22, 0x5, lsl 16
	b	.L2253
.L2251:
	mov	w22, 20992
	movk	w22, 0x2, lsl 16
	b	.L2253
.L2258:
	mov	w22, 30720
	movk	w22, 0x69, lsl 16
	b	.L2253
.L2255:
	mov	w22, 55296
	movk	w22, 0x1b, lsl 16
	b	.L2253
.L2259:
	mov	w22, 7864320
	b	.L2253
.L2280:
	ldr	x1, .LC601
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
	.p2align 3
.L2273:
	ldr	w0, [x19, 3372]
	cmp	w1, w0
	ldr	x0, [x20]
	bhi	.L2276
	ldr	w2, [x0, 24]
	sub	w2, w2, #2
	cmp	w2, 1
	bhi	.L2274
.L2276:
	cmp	w22, w1
	csel	w22, w22, w1, ls
	b	.L2274
	.p2align 3
.L2233:
	ldr	x1, .LC569
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
	.p2align 3
.L2342:
	ldr	x1, .LC616
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3256]
	ldr	x1, .LC618
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3260]
	ldr	x1, .LC620
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3264]
	ldr	x1, .LC622
	mov	x0, x20
	bl	ue_v
	str	w0, [x19, 3268]
	ldr	w1, [x19, 3264]
	ldr	w2, [x19, 3256]
	lsl	w1, w1, 1
	ldr	w3, [x19, 3260]
	lsl	w2, w2, 1
	mul	w1, w1, w24
	sub	w4, w25, w2
	lsl	w24, w24, 1
	sub	w3, w4, w3, lsl 1
	sub	w4, w23, w1
	cmp	w3, wzr
	msub	w0, w24, w0, w4
	ccmp	w0, wzr, 4, gt
	ble	.L2265
	add	x4, x19, 3072
	add	w2, w2, w3, lsr 1
	add	w1, w1, w0, lsr 1
	stp	w3, w0, [x4, 204]
	stp	w2, w1, [x4, 212]
	b	.L2267
	.p2align 3
.L2343:
	add	x1, x19, 3292
	mov	x0, x20
	bl	vui_parameters
	cbnz	w0, .L2326
	ldrb	w0, [x19, 3304]
	cbz	w0, .L2326
	ldr	w2, [x19, 3372]
	cmp	w2, wzr
	ccmp	w22, w2, 0, ne
	bcc	.L2345
	ldr	w22, [x19, 3244]
	ldrb	w0, [x19, 3307]
	cmp	w22, w2
	csel	w22, w22, w2, cs
	b	.L2270
	.p2align 3
.L2344:
	ldr	w1, [x0, 772]
	cbnz	w1, .L2277
	ldr	w1, [x0, 756]
	cmp	w22, w1
	bls	.L2278
	ldr	x0, .LC553
	ldr	x4, [x0]
	cbz	x4, .L2327
	ldr	w0, [x21, 1980]
	mov	w3, 8
	stp	w22, w1, [x29, 112]
	add	x2, x29, 112
	mov	w1, 106
	blr	x4
	mov	w0, -1
	b	.L2319
.L2345:
	ldr	x1, .LC626
	mov	w3, w22
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L2326:
	ldrb	w0, [x19, 3307]
	b	.L2270
	.p2align 3
.L2339:
	ldr	x24, .LC565
	add	x21, x19, 2068
	ldr	x23, .LC542
	add	x22, x19, 436
	mov	x27, 0
	add	x26, x29, 104
	mov	x28, x24
.L2231:
	mov	x1, x25
	mov	x0, x20
	bl	u_1
	cmp	w0, 1
	add	x2, x19, x27
	str	w0, [x26, x27, lsl 2]
	add	x1, x23, 176
	strb	w0, [x2, 10]
	beq	.L2346
	ldr	x3, [x24, 104]
	cbz	w27, .L2347
.L2230:
	mov	x0, x21
	mov	x2, 64
.L2323:
	blr	x3
.L2228:
	add	x27, x27, 1
	add	x21, x21, 64
	cmp	x27, 2
	add	x22, x22, 256
	bne	.L2231
	b	.L2220
	.p2align 3
.L2333:
	ldr	x1, .LC579
	mov	x0, x20
	bl	u_1
	strb	w0, [x19, 16]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2327
	ldr	x1, .LC581
	mov	x0, x20
	bl	se_v
	str	w0, [x19, 2208]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2327
	ldr	x1, .LC583
	mov	x0, x20
	bl	se_v
	str	w0, [x19, 2212]
	ldr	w0, [x21, 1920]
	cbnz	w0, .L2327
	ldr	x1, .LC585
	mov	x0, x20
	bl	ue_v
	cmp	w0, 255
	str	w0, [x19, 2216]
	bhi	.L2240
	ldr	w1, [x21, 1920]
	cbnz	w1, .L2240
	cbz	w0, .L2239
	ldr	x23, .LC589
	mov	w22, 0
	b	.L2243
	.p2align 3
.L2348:
	ldr	w0, [x19, 2216]
	cmp	w0, w22
	bls	.L2239
.L2243:
	mov	x1, x23
	mov	x0, x20
	bl	se_v
	add	x1, x19, x22, uxtw 2
	add	w22, w22, 1
	str	w0, [x1, 2220]
	ldr	w0, [x21, 1920]
	cbz	w0, .L2348
	mov	w0, -1
	b	.L2349
	.p2align 3
.L2340:
	mov	x0, x20
	mov	x4, x21
	mov	x2, x22
	mov	x1, x24
	mov	w3, 16
	bl	Scaling_List
	ldr	w0, [x21]
	cmp	w0, 1
	bne	.L2222
	ldr	x0, .LC542
	cmp	w28, 2
	mov	x2, 16
	add	x1, x0, 80
	add	x0, x0, 96
	csel	x1, x0, x1, hi
	ldr	x0, .LC565
	ldr	x3, [x0, 104]
	mov	x0, x22
	blr	x3
	b	.L2222
	.p2align 3
.L2244:
	ldr	x1, .LC595
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
	.p2align 3
.L2235:
	ldr	x1, .LC573
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
	.p2align 3
.L2217:
	ldr	x1, .LC561
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
.L2346:
	mov	x0, x20
	add	x4, x26, x27, lsl 2
	mov	x2, x21
	mov	x1, x22
	mov	w3, 64
	bl	Scaling_List
	ldr	w0, [x26, x27, lsl 2]
	cmp	w0, 1
	bne	.L2228
	ldr	x1, .LC542
	mov	x2, 64
	mov	x0, x21
	ldr	x3, [x28, 104]
	add	x1, x1, 176
	cbnz	w27, .L2323
	ldr	x1, .LC542
	add	x1, x1, 112
	b	.L2323
	.p2align 3
.L2278:
	ldr	w2, [x0, 732]
	ldr	w1, [x0, 736]
	cmp	w25, w2
	ccmp	w23, w1, 2, ls
	bls	.L2277
	ldr	x0, .LC553
	ldr	x4, [x0]
	cbz	x4, .L2327
	ldr	w0, [x21, 1980]
	mov	w3, 8
	strh	w2, [x29, 116]
	add	x2, x29, 112
	strh	w1, [x29, 118]
	mov	w1, 107
	strh	w25, [x29, 112]
	strh	w23, [x29, 114]
	blr	x4
	mov	w0, -1
	b	.L2349
.L2330:
	ldr	x2, .LC543
	mov	w3, 9948
	ldr	x1, .LC544
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
.L2335:
	ldr	x1, .LC603
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
.L2240:
	ldr	x1, .LC587
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2319
.L2347:
	ldr	x1, .LC542
	add	x1, x1, 112
	b	.L2230
	.size	ProcessSPS, .-ProcessSPS
	.align	3
.LC542:
	.xword	.LANCHOR1
	.align	3
.LC543:
	.xword	.LC30
	.align	3
.LC544:
	.xword	.LC32
	.align	3
.LC546:
	.xword	.LC545
	.align	3
.LC548:
	.xword	.LC547
	.align	3
.LC550:
	.xword	.LC549
	.align	3
.LC552:
	.xword	.LC551
	.align	3
.LC553:
	.xword	g_event_report
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
.LC561:
	.xword	.LC560
	.align	3
.LC563:
	.xword	.LC562
	.align	3
.LC564:
	.xword	.LC420
	.align	3
.LC565:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC567:
	.xword	.LC566
	.align	3
.LC569:
	.xword	.LC568
	.align	3
.LC571:
	.xword	.LC570
	.align	3
.LC573:
	.xword	.LC572
	.align	3
.LC575:
	.xword	.LC574
	.align	3
.LC577:
	.xword	.LC576
	.align	3
.LC579:
	.xword	.LC578
	.align	3
.LC581:
	.xword	.LC580
	.align	3
.LC583:
	.xword	.LC582
	.align	3
.LC585:
	.xword	.LC584
	.align	3
.LC587:
	.xword	.LC586
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
.LC604:
	.xword	.L2252
	.align	3
.LC606:
	.xword	.LC605
	.align	3
.LC608:
	.xword	.LC607
	.align	3
.LC610:
	.xword	.LC609
	.align	3
.LC612:
	.xword	.LC611
	.align	3
.LC614:
	.xword	.LC613
	.align	3
.LC616:
	.xword	.LC615
	.align	3
.LC618:
	.xword	.LC617
	.align	3
.LC620:
	.xword	.LC619
	.align	3
.LC622:
	.xword	.LC621
	.align	3
.LC624:
	.xword	.LC623
	.align	3
.LC626:
	.xword	.LC625
	.align	3
.LC628:
	.xword	.LC627
	.align	3
.LC630:
	.xword	.LC629
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Sps_SvcExt
	.type	Sps_SvcExt, %function
Sps_SvcExt:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, 4000
	bl	_mcount
	add	x1, x19, 20480
	mov	w3, 2208
	ldr	x2, [x19, 14968]
	add	x0, x19, 12288
	ldr	x5, [x19, 14960]
	add	x0, x0, 2600
	ldr	w4, [x1, 1592]
	mov	w1, 32
	umull	x3, w4, w3
	add	x3, x2, x3
	ldr	w2, [x3, 28]
	umull	x2, w2, w20
	add	x20, x5, x2
	bl	BsGet
	mov	w21, w0
	ldr	x1, .LC632
	mov	x0, x19
	bl	u_1
	mov	w2, w0
	ldr	x1, .LC634
	mov	w0, 17
	bl	dprint_vfmw
	ldr	x2, .LC636
	mov	w1, 2
	mov	x0, x19
	bl	u_v
	cmp	w0, 1
	beq	.L2361
	ldr	w0, [x20, 40]
	sub	w1, w0, #1
	cmp	w1, 1
	bls	.L2362
.L2353:
	cmp	w0, 1
	beq	.L2363
.L2354:
	ldr	x1, .LC648
	mov	x0, x19
	bl	u_1
	cbnz	w0, .L2364
.L2355:
	ldr	x1, .LC654
	mov	x0, x19
	mov	w19, 0
	bl	u_1
	cmp	w0, 1
	beq	.L2352
	ldr	x1, .LC656
	mov	w2, w0
	ldr	w4, [x20, 40]
	mov	w3, w21
	mov	w0, 1
	bl	dprint_vfmw
.L2352:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2364:
	ldr	x1, .LC650
	mov	x0, x19
	bl	u_1
	mov	w2, w0
	ldr	x1, .LC652
	mov	w0, 17
	bl	dprint_vfmw
	b	.L2355
	.p2align 3
.L2363:
	ldr	x2, .LC644
	mov	w1, 2
	mov	x0, x19
	bl	u_v
	mov	w2, w0
	ldr	x1, .LC646
	mov	w0, 17
	bl	dprint_vfmw
	b	.L2354
	.p2align 3
.L2362:
	ldr	x1, .LC640
	mov	x0, x19
	bl	u_1
	mov	w2, w0
	ldr	x1, .LC642
	mov	w0, 17
	bl	dprint_vfmw
	ldr	w0, [x20, 40]
	b	.L2353
.L2361:
	ldr	x1, .LC638
	mov	w19, -1
	bl	dprint_vfmw
	b	.L2352
	.size	Sps_SvcExt, .-Sps_SvcExt
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecSPS
	.type	H264_DecSPS, %function
H264_DecSPS:
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
	cbz	x19, .L2396
	ldr	x2, .LC660
	mov	w1, 8
	mov	x0, x19
	add	x27, x19, 65536
	bl	u_v
	mov	w22, w0
	ldr	x1, .LC662
	mov	x0, x19
	bl	u_1
	mov	w26, w0
	ldr	x1, .LC664
	mov	x0, x19
	bl	u_1
	mov	w25, w0
	ldr	x1, .LC666
	mov	x0, x19
	bl	u_1
	mov	w24, w0
	ldr	x1, .LC668
	mov	x0, x19
	bl	u_1
	mov	w23, w0
	ldr	x2, .LC670
	mov	w1, 4
	mov	x0, x19
	bl	u_v
	ldr	x2, .LC672
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	mov	w20, w0
	ldr	x1, .LC674
	mov	x0, x19
	bl	ue_v
	mov	w21, w0
	ldr	w0, [x27, 1920]
	cbnz	w0, .L2395
	ldr	w0, [x19, 14944]
	sub	w0, w0, #1
	cmp	w21, w0
	bhi	.L2397
	sub	w0, w22, #66
	mov	w27, w22
	cmp	w0, 78
	bls	.L2398
.L2371:
	ldr	x1, .LC685
	mov	w2, w22
	mov	w0, 1
	mov	w27, 100
	bl	dprint_vfmw
.L2374:
	cmp	w20, 9
	mov	w3, w20
	bls	.L2394
	cmp	w20, 41
	bhi	.L2394
	mov	w20, 4000
	ldr	x0, [x19, 14960]
	umull	x20, w21, w20
	add	x0, x0, x20
	ldrb	w1, [x0, 23]
	cbz	w1, .L2379
.L2401:
	ldr	x28, .LC688
	mov	w1, 0
	ldr	x4, .LC689
	mov	x2, 4000
	str	w3, [x29, 100]
	add	x22, x4, 2208
	ldr	x5, [x28, 96]
	mov	x0, x22
	str	x4, [x29, 104]
	blr	x5
	strb	w25, [x22, 1]
	ldr	w3, [x29, 100]
	mov	x1, x22
	ldr	x4, [x29, 104]
	mov	x0, x19
	strb	w24, [x22, 2]
	strb	w23, [x22, 3]
	strb	w26, [x4, 2208]
	stp	w27, w3, [x22, 28]
	str	w21, [x22, 36]
	bl	ProcessSPS
	cbnz	w0, .L2399
	ldr	x1, [x19, 14960]
	mov	x0, x22
	add	x1, x1, x20
	bl	SPSEqual
	cbnz	w0, .L2400
.L2381:
	mov	w0, 86
	cmp	w27, 83
	ccmp	w27, w0, 4, ne
	beq	.L2383
.L2384:
	mov	w0, 0
.L2367:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2398:
	ldr	x1, .LC677
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx2373
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2373:
	.section	.rodata
	.align	0
	.align	2
.L2373:
	.byte	(.L2372 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2374 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2374 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2374 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2375 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2374 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2376 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2376 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2371 - .Lrtx2373) / 4
	.byte	(.L2376 - .Lrtx2373) / 4
	.text
	.p2align 3
.L2383:
	mov	x0, x19
	bl	Sps_SvcExt
	cbz	w0, .L2384
	ldr	x1, .LC693
	mov	w0, 1
	bl	dprint_vfmw
.L2395:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2394:
	ldr	x1, .LC687
	mov	w2, w3
	mov	w0, 1
	mov	w3, 41
	mov	w20, 4000
	bl	dprint_vfmw
	umull	x20, w21, w20
	ldr	x0, [x19, 14960]
	mov	w3, 41
	add	x0, x0, x20
	ldrb	w1, [x0, 23]
	cbnz	w1, .L2401
.L2379:
	str	w27, [x0, 28]
	ldr	x0, [x19, 14960]
	strb	w26, [x0, x20]
	mov	x0, x19
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	strb	w25, [x1, 1]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	strb	w24, [x1, 2]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	strb	w23, [x1, 3]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	str	w3, [x1, 32]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	str	w21, [x1, 36]
	ldr	x1, [x19, 14960]
	add	x1, x1, x20
	bl	ProcessSPS
	cbnz	w0, .L2402
	ldr	x0, [x19, 14960]
	mov	w1, 1
	add	x0, x0, x20
	strb	w1, [x0, 24]
	ldr	x0, [x19, 14960]
	add	x20, x0, x20
	strb	w1, [x20, 23]
	b	.L2381
	.p2align 3
.L2397:
	ldr	x1, .LC675
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 14944]
	sub	w0, w1, #1
	cmp	w21, w0
	bls	.L2395
	ldr	x0, .LC676
	ldr	x4, [x0]
	cbz	x4, .L2395
	ldr	w0, [x27, 1980]
	add	x2, x29, 120
	stp	w21, w1, [x29, 120]
	mov	w3, 8
	mov	w1, 109
	blr	x4
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2375:
	ldr	x1, .LC681
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2374
	.p2align 3
.L2376:
	ldr	x1, .LC683
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2374
	.p2align 3
.L2372:
	ldr	x1, .LC679
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2374
	.p2align 3
.L2400:
	ldr	x0, [x19, 14960]
	mov	w1, 1
	ldr	x3, [x28, 112]
	mov	x2, 4000
	strb	w1, [x22, 24]
	add	x0, x0, x20
	strb	w1, [x22, 23]
	mov	x1, x22
	blr	x3
	b	.L2381
	.p2align 3
.L2399:
	ldr	x1, .LC691
	mov	w3, w21
	mov	w2, 10566
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2367
.L2396:
	ldr	x2, .LC657
	mov	w3, 10479
	ldr	x1, .LC658
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2367
.L2402:
	ldr	x1, .LC691
	mov	w2, 10591
	mov	w3, w21
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x19, 14960]
	mov	w2, 1
	mov	w0, -1
	add	x1, x1, x20
	strb	w2, [x1, 24]
	ldr	x1, [x19, 14960]
	add	x20, x1, x20
	strb	wzr, [x20, 23]
	b	.L2367
	.size	H264_DecSPS, .-H264_DecSPS
	.align	3
.LC657:
	.xword	.LC30
	.align	3
.LC658:
	.xword	.LC32
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
.LC675:
	.xword	.LC438
	.align	3
.LC676:
	.xword	g_event_report
	.align	3
.LC677:
	.xword	.L2373
	.align	3
.LC679:
	.xword	.LC678
	.align	3
.LC681:
	.xword	.LC680
	.align	3
.LC683:
	.xword	.LC682
	.align	3
.LC685:
	.xword	.LC684
	.align	3
.LC687:
	.xword	.LC686
	.align	3
.LC688:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC689:
	.xword	.LANCHOR3
	.align	3
.LC691:
	.xword	.LC690
	.align	3
.LC693:
	.xword	.LC692
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PassBytes
	.type	PassBytes, %function
PassBytes:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x0, [x20, 632]
	cmp	w19, wzr
	ccmp	x0, xzr, 4, ne
	beq	.L2412
	ldrb	w2, [x0]
	sbfiz	x1, x2, 5, 32
	add	x1, x0, x1
	ldr	x1, [x1, 8]
	cbz	x1, .L2412
	ldr	w1, [x0, 76]
	cmp	w2, 1
	ccmp	w1, 2, 2, ls
	bhi	.L2412
	cmp	w1, w2
	bls	.L2412
	uxtw	x5, w2
	add	x3, x0, x5, lsl 5
	ldr	w1, [x3, 28]
	ldr	w3, [x3, 16]
	add	w1, w1, w19, lsl 3
	lsl	w3, w3, 3
	cmp	w1, w3
	bhi	.L2407
	b	.L2405
	.p2align 3
.L2408:
	ldr	w4, [x6, 28]
	ldr	w6, [x6, 16]
	sub	w4, w4, w3
	add	w1, w1, w4
	lsl	w3, w6, 3
	cmp	w1, w3
	bls	.L2405
.L2407:
	add	x0, x0, x5, lsl 5
	add	w5, w2, 1
	mov	x2, x5
	str	w3, [x0, 28]
	ldr	x0, [x20, 632]
	ldrb	w4, [x0]
	add	w4, w4, 1
	strb	w4, [x0]
	ldr	x0, [x20, 632]
	add	x6, x0, x5, lsl 5
	ldr	w4, [x0, 76]
	cmp	w4, w5
	bhi	.L2408
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2405:
	add	x5, x0, x5, lsl 5
	mov	w0, 1
	str	w1, [x5, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2412:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PassBytes, .-PassBytes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetBytes
	.type	GetBytes, %function
GetBytes:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x19, x1
	mov	x0, x30
	mov	w20, w2
	bl	_mcount
	cbz	x19, .L2428
	ldr	x1, [x21, 632]
	cmp	x1, xzr
	ccmp	w20, wzr, 4, ne
	ble	.L2428
	ldrb	w2, [x1]
	sbfiz	x0, x2, 5, 32
	add	x0, x1, x0
	ldr	x0, [x0, 8]
	cbz	x0, .L2428
	ldr	w0, [x1, 76]
	cmp	w2, 1
	ccmp	w0, 2, 2, ls
	bhi	.L2428
	cmp	w0, w2
	bls	.L2428
	mov	w6, 0
.L2423:
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
	bcs	.L2418
	ldrb	w0, [x4, x0]
	add	w6, w6, 1
	strb	w0, [x19]
	cmp	w6, w20
	add	x19, x19, 1
	add	x5, x5, 1
	ldr	x0, [x21, 632]
	add	x0, x0, x7
	ldr	w3, [x0, 28]
	add	w3, w3, 8
	str	w3, [x0, 28]
	bcc	.L2421
	b	.L2420
	.p2align 3
.L2422:
	ldrb	w1, [x5], 1
	add	w6, w6, 1
	strb	w1, [x19], 1
	cmp	w6, w20
	ldr	x3, [x21, 632]
	add	x3, x3, x7
	ldr	w4, [x3, 28]
	add	w4, w4, 8
	str	w4, [x3, 28]
	bcs	.L2420
.L2421:
	cmp	x8, x5
	bne	.L2422
	ldr	x1, [x21, 632]
.L2418:
	ldrb	w0, [x1]
	add	w2, w2, 1
	add	w0, w0, 1
	strb	w0, [x1]
	ldr	x1, [x21, 632]
	ldr	w0, [x1, 76]
	cmp	w0, w2
	bhi	.L2423
	mov	w0, w6
	b	.L2417
	.p2align 3
.L2420:
	mov	w0, w20
.L2417:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2428:
	mov	w0, -1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetBytes, .-GetBytes
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecFramePackingSEI
	.type	H264_DecFramePackingSEI, %function
H264_DecFramePackingSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 24576
	bl	_mcount
	add	x20, x21, 3184
	ldr	x1, .LC696
	mov	x0, x19
	bl	ue_v
	str	w0, [x20, 24]
	ldr	x2, .LC698
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	sxtb	w0, w0
	strb	w0, [x20, 1]
	cbz	w0, .L2436
.L2431:
	ldr	x2, .LC730
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x21, 3186]
	mov	w1, 1
	strb	w1, [x21, 3184]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2436:
	ldr	x2, .LC700
	mov	w1, 7
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 16]
	ldr	x2, .LC702
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 3]
	ldr	x2, .LC704
	mov	w1, 6
	mov	x0, x19
	bl	u_v
	str	w0, [x20, 20]
	ldr	x2, .LC706
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 4]
	ldr	x2, .LC708
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 5]
	ldr	x2, .LC710
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 6]
	ldr	x2, .LC712
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 7]
	ldr	x2, .LC714
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 8]
	ldr	x2, .LC716
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 9]
	ldrsb	w1, [x20, 3]
	cbnz	w1, .L2432
	ldr	w0, [x20, 16]
	cmp	w0, 5
	beq	.L2432
	ldr	x2, .LC718
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 10]
	ldr	x2, .LC720
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 11]
	ldr	x2, .LC722
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 12]
	ldr	x2, .LC724
	mov	w1, 1
	mov	x0, x19
	bl	u_v
	strb	w0, [x20, 13]
.L2432:
	ldr	x2, .LC726
	mov	w1, 8
	mov	x0, x19
	bl	u_v
	str	w0, [x21, 3212]
	ldr	x1, .LC728
	mov	x0, x19
	bl	ue_v
	str	w0, [x21, 3216]
	b	.L2431
	.size	H264_DecFramePackingSEI, .-H264_DecFramePackingSEI
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
.LC708:
	.xword	.LC707
	.align	3
.LC710:
	.xword	.LC709
	.align	3
.LC712:
	.xword	.LC711
	.align	3
.LC714:
	.xword	.LC713
	.align	3
.LC716:
	.xword	.LC715
	.align	3
.LC718:
	.xword	.LC717
	.align	3
.LC720:
	.xword	.LC719
	.align	3
.LC722:
	.xword	.LC721
	.align	3
.LC724:
	.xword	.LC723
	.align	3
.LC726:
	.xword	.LC725
	.align	3
.LC728:
	.xword	.LC727
	.align	3
.LC730:
	.xword	.LC729
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecPicTimingSEI
	.type	H264_DecPicTimingSEI, %function
H264_DecPicTimingSEI:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 4000
	bl	_mcount
	ldr	w0, [x20, 15012]
	ldr	x3, [x20, 14960]
	umull	x19, w0, w19
	add	x19, x3, x19
	ldrb	w0, [x19, 23]
	cbnz	w0, .L2438
	ldr	w1, [x20, 14944]
	cmp	w1, wzr
	ble	.L2439
	ldrb	w0, [x3, 23]
	cbnz	w0, .L2456
	sub	w1, w1, #1
	add	x0, x3, 4000
	add	x2, x1, 1
	lsl	x1, x2, 6
	sub	x1, x1, x2
	lsl	x1, x1, 1
	sub	x1, x1, x2
	add	x2, x3, x1, lsl 5
	b	.L2442
	.p2align 3
.L2443:
	ldrb	w1, [x1]
	cbnz	w1, .L2440
.L2442:
	cmp	x0, x2
	mov	x19, x0
	add	x0, x0, 4000
	sub	x1, x0, #3977
	bne	.L2443
.L2439:
	ldr	x1, .LC732
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
.L2444:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2456:
	mov	x19, x3
	.p2align 2
.L2440:
	cbz	x19, .L2439
.L2438:
	ldrb	w0, [x19, 22]
	cbz	w0, .L2446
	ldrb	w0, [x19, 3299]
	cbz	w0, .L2457
	ldr	w1, [x19, 3676]
	ldr	w22, [x19, 3680]
	add	w1, w1, 1
	add	w22, w22, 1
.L2450:
	ldr	x2, .LC734
	mov	x0, x20
	add	x21, x20, 24576
	bl	u_v
	ldr	x2, .LC736
	mov	w1, w22
	str	w0, [x21, 3224]
	mov	x0, x20
	bl	u_v
	str	w0, [x21, 3228]
	add	x1, x20, 65536
	ldr	x0, .LC737
	ldrsw	x1, [x1, 1980]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L2458
.L2446:
	ldrb	w0, [x19, 3303]
	mov	w19, 0
	cbz	w0, .L2444
	ldr	x2, .LC739
	mov	w1, 4
	mov	x0, x20
	bl	u_v
	add	x1, x20, 24576
	strb	w0, [x1, 3220]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2457:
	ldrb	w0, [x19, 3302]
	cbz	w0, .L2446
	ldr	w1, [x19, 3988]
	ldr	w22, [x19, 3992]
	add	w1, w1, 1
	add	w22, w22, 1
	b	.L2450
	.p2align 3
.L2458:
	ldr	x1, [x0, 160]
	mov	x0, 1
	movk	x0, 0x2, lsl 32
	cmp	x1, x0
	bne	.L2446
	mov	x0, x20
	bl	H264_Sei_Get_Dpb_Output_Time
	b	.L2446
	.size	H264_DecPicTimingSEI, .-H264_DecPicTimingSEI
	.align	3
.LC732:
	.xword	.LC731
	.align	3
.LC734:
	.xword	.LC733
	.align	3
.LC736:
	.xword	.LC735
	.align	3
.LC737:
	.xword	s_pstVfmwChan
	.align	3
.LC739:
	.xword	.LC738
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecSEI
	.type	H264_DecSEI, %function
H264_DecSEI:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	bl	_mcount
	strb	wzr, [x29, 127]
	cbz	x27, .L2694
	add	x21, x27, 65536
	ldr	x0, .LC742
	ldrsw	x1, [x21, 1980]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L2695
.L2462:
	ldr	x0, [x27, 632]
	mov	w1, 32
	str	w1, [x0, 28]
.L2463:
	add	x20, x27, 12288
	mov	w23, 0
	add	x19, x20, 2600
	b	.L2466
	.p2align 3
.L2697:
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	cmp	w22, wzr
	ble	.L2465
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2696
.L2466:
	mov	w2, 1
	add	x1, x29, 127
	mov	x0, x27
	bl	GetBytes
	mov	w22, w0
	ldr	w2, [x27, 14912]
	ldr	w0, [x27, 14920]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w23, w23, w1
	bls	.L2697
.L2465:
	ldr	x1, .LC744
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2461
	.p2align 3
.L2696:
	ldr	x26, .LC750
	mov	w24, 0
	ldr	x22, .LC747
	add	x0, x26, 232
	str	x0, [x29, 104]
	.p2align 2
.L2646:
	mov	w19, 0
	add	x25, x20, 2600
	b	.L2471
	.p2align 3
.L2699:
	mov	w1, 8
	mov	x0, x25
	bl	BsSkip
	cmp	w28, wzr
	ble	.L2469
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2698
.L2471:
	mov	w2, 1
	add	x1, x29, 127
	mov	x0, x27
	bl	GetBytes
	mov	w28, w0
	ldr	w2, [x27, 14912]
	ldr	w0, [x27, 14920]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w19, w19, w1
	bls	.L2699
.L2469:
	ldr	x1, .LC746
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L2461:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2698:
	cmp	w19, 409600
	bgt	.L2469
	ldr	x0, [x27, 632]
	ldr	w1, [x0, 76]
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L2700
.L2473:
	cmp	w23, 45
	bls	.L2701
.L2474:
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2702
.L2636:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2639
	.p2align 3
.L2640:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2639:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2640
	.p2align 2
.L2689:
	ldr	w0, [x21, 664]
.L2501:
	cmp	w0, 3
	bhi	.L2703
.L2641:
	mov	w23, 0
	add	x19, x20, 2600
	b	.L2645
	.p2align 3
.L2643:
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	cmp	w25, wzr
	ble	.L2644
	ldrb	w0, [x29, 127]
	cmp	w0, 255
	bne	.L2704
.L2645:
	mov	w2, 1
	add	x1, x29, 127
	mov	x0, x27
	bl	GetBytes
	mov	w25, w0
	ldr	w2, [x27, 14912]
	ldr	w0, [x27, 14920]
	ldrb	w1, [x29, 127]
	add	w0, w0, 8
	cmp	w0, w2, lsl 3
	add	w23, w23, w1
	bls	.L2643
.L2644:
	mov	w0, 0
.L2705:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L2704:
	cmp	w0, 128
	bne	.L2646
	mov	w0, 0
	b	.L2705
	.p2align 3
.L2701:
	ldrh	w0, [x22,w23,uxtw #1]
	adr	x1, .Lrtx2476
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx2476:
	.section	.rodata
	.align	0
	.align	2
.L2476:
	.2byte	(.L2475 - .Lrtx2476) / 4
	.2byte	(.L2477 - .Lrtx2476) / 4
	.2byte	(.L2478 - .Lrtx2476) / 4
	.2byte	(.L2479 - .Lrtx2476) / 4
	.2byte	(.L2480 - .Lrtx2476) / 4
	.2byte	(.L2481 - .Lrtx2476) / 4
	.2byte	(.L2482 - .Lrtx2476) / 4
	.2byte	(.L2483 - .Lrtx2476) / 4
	.2byte	(.L2484 - .Lrtx2476) / 4
	.2byte	(.L2485 - .Lrtx2476) / 4
	.2byte	(.L2486 - .Lrtx2476) / 4
	.2byte	(.L2487 - .Lrtx2476) / 4
	.2byte	(.L2488 - .Lrtx2476) / 4
	.2byte	(.L2489 - .Lrtx2476) / 4
	.2byte	(.L2490 - .Lrtx2476) / 4
	.2byte	(.L2491 - .Lrtx2476) / 4
	.2byte	(.L2492 - .Lrtx2476) / 4
	.2byte	(.L2493 - .Lrtx2476) / 4
	.2byte	(.L2494 - .Lrtx2476) / 4
	.2byte	(.L2495 - .Lrtx2476) / 4
	.2byte	(.L2496 - .Lrtx2476) / 4
	.2byte	(.L2497 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2474 - .Lrtx2476) / 4
	.2byte	(.L2498 - .Lrtx2476) / 4
	.text
.L2498:
	mov	w1, w19
	mov	x0, x27
	ldr	w25, [x27, 14920]
	bl	H264_DecFramePackingSEI
	ldr	w3, [x27, 14920]
	sub	w0, w3, w25
	lsl	w25, w19, 3
	cmp	w0, w25
	bge	.L2629
	sub	w26, w25, w0
	ldr	w0, [x27, 14912]
	cmp	w26, wzr
	add	w23, w26, 7
	csel	w23, w23, w26, lt
	lsl	w0, w0, 3
	asr	w23, w23, 3
	cmp	w23, wzr
	ble	.L2631
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2631
	add	x28, x20, 2600
	mov	w25, 0
	b	.L2632
	.p2align 3
.L2633:
	ldr	w0, [x27, 14912]
	ldr	w3, [x27, 14920]
	lsl	w0, w0, 3
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2631
.L2632:
	mov	w1, 8
	mov	x0, x28
	add	w25, w25, 1
	bl	BsSkip
	cmp	w25, w23
	bne	.L2633
	ldr	w0, [x27, 14912]
	ldr	w3, [x27, 14920]
	lsl	w0, w0, 3
.L2631:
	asr	w1, w26, 31
	lsr	w2, w1, 29
	add	w1, w26, w2
	and	w1, w1, 7
	sub	w1, w1, w2
	add	w3, w1, w3
	cmp	w3, w0
	bls	.L2706
.L2629:
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbz	w0, #31, .L2689
	ldr	x1, .LC752
	mov	w3, 11693
	ldr	x2, .LC808
	mov	w0, 20
	bl	dprint_vfmw
	ldr	w0, [x21, 664]
	b	.L2501
.L2497:
	ldr	x1, .LC805
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2707
.L2623:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2626
	.p2align 3
.L2627:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2626:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2627
	b	.L2689
.L2496:
	ldr	x1, .LC803
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2708
.L2618:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2621
	.p2align 3
.L2622:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2621:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2622
	b	.L2689
.L2495:
	ldr	x1, .LC801
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2709
.L2613:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2616
	.p2align 3
.L2617:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2616:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2617
	b	.L2689
.L2494:
	ldr	x1, .LC799
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2710
.L2608:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2611
	.p2align 3
.L2612:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2611:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2612
	b	.L2689
.L2493:
	ldr	x1, .LC797
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2711
.L2603:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2606
	.p2align 3
.L2607:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2606:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2607
	b	.L2689
.L2492:
	ldr	x1, .LC795
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2712
.L2598:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2601
	.p2align 3
.L2602:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2601:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2602
	b	.L2689
.L2491:
	ldr	x1, .LC793
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2713
.L2593:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2596
	.p2align 3
.L2597:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2596:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2597
	b	.L2689
.L2490:
	ldr	x1, .LC791
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2714
.L2588:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2591
	.p2align 3
.L2592:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2591:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2592
	b	.L2689
.L2489:
	ldr	x1, .LC789
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2715
.L2583:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2586
	.p2align 3
.L2587:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2586:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2587
	b	.L2689
.L2488:
	ldr	x1, .LC787
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2716
.L2578:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2581
	.p2align 3
.L2582:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2581:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2582
	b	.L2689
.L2487:
	ldr	x1, .LC785
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2717
.L2573:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2576
	.p2align 3
.L2577:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2576:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2577
	b	.L2689
.L2486:
	ldr	x1, .LC783
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2718
.L2568:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2571
	.p2align 3
.L2572:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2571:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2572
	b	.L2689
.L2485:
	ldr	x1, .LC781
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2719
.L2563:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2566
	.p2align 3
.L2567:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2566:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2567
	b	.L2689
.L2484:
	ldr	x1, .LC779
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2720
.L2558:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2561
	.p2align 3
.L2562:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2561:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2562
	b	.L2689
.L2483:
	ldr	x1, .LC777
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2721
.L2553:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2556
	.p2align 3
.L2557:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2556:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2557
	b	.L2689
.L2482:
	ldr	x1, .LC775
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	cmp	w19, wzr
	ble	.L2550
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2550
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2551
	.p2align 3
.L2552:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2550
.L2551:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2552
.L2550:
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbz	w0, #31, .L2689
	ldr	x2, .LC750
	mov	w3, 11265
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	ldr	w0, [x21, 664]
	b	.L2501
.L2481:
	cbnz	w24, .L2480
	ldr	x1, .LC762
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	ldr	w23, [x21, 664]
	cmp	w23, 3
	bhi	.L2722
.L2525:
	ldr	w0, [x21, 1980]
	bl	GetUsd
	uxtw	x1, w23
	add	x1, x1, 8192
	add	x1, x1, 84
	str	x0, [x27, x1, lsl 3]
	ldr	w0, [x21, 664]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x6, [x27, x0, lsl 3]
	cbz	x6, .L2649
	ldr	x3, [x27, 632]
	cmp	w19, 1024
	mov	w28, 1024
	csel	w28, w19, w28, le
	ldrb	w2, [x3]
	ldr	w5, [x3, 76]
	cmp	w2, w5
	bcs	.L2650
	mov	w25, 0
	.p2align 2
.L2527:
	ubfiz	x1, x2, 5, 32
	add	w2, w2, 1
	add	x1, x3, x1
	cmp	w2, w5
	ldr	w0, [x1, 28]
	ldr	w1, [x1, 16]
	add	w0, w0, 7
	sub	w0, w1, w0, lsr 3
	add	w25, w25, w0
	bne	.L2527
	mov	w0, w25
.L2526:
	cmp	w28, w0
	csel	w25, w25, w28, gt
	cbnz	w24, .L2723
	mov	w23, 0
	mov	w26, 0
.L2529:
	sub	w2, w25, w23
	cmp	w2, wzr
	ble	.L2724
	ldr	w0, [x21, 664]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x1, [x27, x0, lsl 3]
	mov	x0, x27
	bl	GetBytes
	cmp	w0, wzr
	mov	w25, w0
	ble	.L2725
	sub	w0, w28, w26
	cmp	w25, w0
	bge	.L2535
	ldr	w0, [x21, 664]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x0, [x27, x0, lsl 3]
	str	w25, [x0, 1052]
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2536
	add	x19, x20, 2600
	mov	w23, 0
	b	.L2537
	.p2align 3
.L2540:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2536
.L2537:
	mov	w1, 8
	mov	x0, x19
	add	w23, w23, 1
	bl	BsSkip
	cmp	w25, w23
	bne	.L2540
.L2536:
	ldr	w0, [x21, 664]
	cmp	w24, 1
	ldr	x1, [x27]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x1, [x1, 64]
	ldr	x0, [x27, x0, lsl 3]
	str	x1, [x0, 1056]
	mov	w0, 8
	mov	w1, 9
	csel	w1, w0, w1, eq
	ldr	w0, [x21, 664]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x0, [x27, x0, lsl 3]
	str	w1, [x0, 1040]
	ldr	x0, .LC769
	ldr	x5, [x0]
.L2692:
	ldr	w0, [x21, 664]
	ldr	w1, [x21, 1940]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x0, [x27, x0, lsl 3]
	str	w1, [x0, 1044]
	cbz	x5, .L2546
	ldr	w0, [x21, 664]
	mov	w3, 1064
	mov	w1, 6
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x2, [x27, x0, lsl 3]
	ldr	w0, [x21, 1980]
	blr	x5
.L2546:
	ldr	w0, [x21, 664]
	add	w0, w0, 1
	str	w0, [x21, 664]
	cmp	w0, 3
	bls	.L2641
.L2703:
	ldr	x1, .LC807
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2461
.L2479:
	ldr	x1, .LC758
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2726
.L2518:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2521
	.p2align 3
.L2522:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2521:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2522
	b	.L2689
.L2478:
	ldr	x1, .LC756
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2727
.L2513:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2516
	.p2align 3
.L2517:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2516:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2517
	b	.L2689
.L2477:
	ldr	x1, .LC754
	mov	w3, w19
	mov	w0, 20
	bl	dprint_vfmw
	ldr	w25, [x27, 14920]
	mov	w1, w19
	mov	x0, x27
	bl	H264_DecPicTimingSEI
	ldr	w3, [x27, 14920]
	sub	w0, w3, w25
	lsl	w25, w19, 3
	cmp	w0, w25
	bge	.L2506
	sub	w25, w25, w0
	ldr	w0, [x27, 14912]
	cmp	w25, wzr
	add	w23, w25, 7
	csel	w23, w23, w25, lt
	lsl	w0, w0, 3
	asr	w23, w23, 3
	cmp	w23, wzr
	ble	.L2508
	add	w1, w3, 8
	cmp	w0, w1
	bcc	.L2508
	add	x28, x20, 2600
	mov	w26, 0
	b	.L2509
	.p2align 3
.L2510:
	ldr	w0, [x27, 14912]
	ldr	w3, [x27, 14920]
	lsl	w0, w0, 3
	add	w1, w3, 8
	cmp	w1, w0
	bhi	.L2508
.L2509:
	mov	w1, 8
	mov	x0, x28
	add	w26, w26, 1
	bl	BsSkip
	cmp	w23, w26
	bne	.L2510
	ldr	w0, [x27, 14912]
	ldr	w3, [x27, 14920]
	lsl	w0, w0, 3
.L2508:
	asr	w1, w25, 31
	lsr	w2, w1, 29
	add	w1, w25, w2
	and	w1, w1, 7
	sub	w1, w1, w2
	add	w3, w1, w3
	cmp	w3, w0
	bls	.L2728
.L2506:
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbz	w0, #31, .L2689
	ldr	x2, .LC750
	mov	w3, 11022
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	ldr	w0, [x21, 664]
	b	.L2501
.L2475:
	add	x0, x27, 24576
	mov	w3, 1
	ldr	w1, [x0, 3232]
	strb	w3, [x0, 3312]
	mov	w3, w19
	add	w1, w1, 1
	str	w1, [x0, 3232]
	ldr	x1, .LC749
	str	wzr, [x0, 3240]
	mov	w0, 20
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x27
	bl	PassBytes
	tbnz	w0, #31, .L2729
.L2499:
	cmp	w19, wzr
	ble	.L2689
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
	add	x23, x20, 2600
	mov	w25, 0
	b	.L2503
	.p2align 3
.L2504:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2689
.L2503:
	mov	w1, 8
	mov	x0, x23
	add	w25, w25, 1
	bl	BsSkip
	cmp	w19, w25
	bne	.L2504
	b	.L2689
.L2480:
	ldr	x1, .LC760
	mov	w3, w19
	mov	w0, 20
	mov	w24, 1
	bl	dprint_vfmw
	ldr	w23, [x21, 664]
	cmp	w23, 3
	bls	.L2525
.L2722:
	ldr	w0, [x21, 1980]
	mov	w23, 0
	ldr	x1, [x21, 672]
	bl	FreeUsdByDec
	ldr	w0, [x21, 1980]
	ldr	x1, [x21, 680]
	bl	FreeUsdByDec
	ldr	w0, [x21, 1980]
	ldr	x1, [x21, 688]
	bl	FreeUsdByDec
	ldr	w0, [x21, 1980]
	ldr	x1, [x21, 696]
	bl	FreeUsdByDec
	str	wzr, [x21, 664]
	add	x0, x21, 512
	stp	xzr, xzr, [x0, 160]
	stp	xzr, xzr, [x0, 176]
	b	.L2525
	.p2align 3
.L2700:
	ldr	w0, [x0, 60]
	add	w2, w2, w0
	lsr	w2, w2, 3
	b	.L2473
.L2535:
	ldr	w0, [x21, 664]
	sub	w23, w19, w26
	cmp	w28, w19
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x0, [x27, x0, lsl 3]
	str	w23, [x0, 1052]
	bcc	.L2730
.L2542:
	cmp	w23, wzr
	ble	.L2536
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2536
	add	x19, x20, 2600
	mov	w25, 0
	b	.L2544
	.p2align 3
.L2545:
	ldr	w1, [x27, 14912]
	ldr	w0, [x27, 14920]
	add	w0, w0, 8
	cmp	w0, w1, lsl 3
	bhi	.L2536
.L2544:
	mov	w1, 8
	mov	x0, x19
	add	w25, w25, 1
	bl	BsSkip
	cmp	w23, w25
	bne	.L2545
	b	.L2536
.L2695:
	mov	x1, 1
	ldr	x2, [x0, 160]
	movk	x1, 0x2, lsl 32
	cmp	x2, x1
	bne	.L2462
	ldr	w0, [x0, 156]
	cmp	w0, 1
	bne	.L2462
	ldr	x0, [x27, 632]
	mov	w1, 48
	str	w1, [x0, 28]
	b	.L2463
.L2728:
	add	x0, x20, 2600
	bl	BsSkip
	b	.L2506
.L2706:
	add	x0, x20, 2600
	bl	BsSkip
	b	.L2629
.L2723:
	strb	w24, [x6, 1026]
	mov	w1, 8
	ldr	x2, .LC764
	mov	x0, x27
	ldr	w3, [x21, 664]
	add	x3, x3, 8192
	add	x3, x3, 84
	ldr	x23, [x27, x3, lsl 3]
	bl	u_v
	strb	w0, [x23, 1027]
	ldr	w0, [x21, 664]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x23, [x27, x0, lsl 3]
	ldrb	w0, [x23, 1027]
	cmp	w0, 255
	beq	.L2530
	strb	wzr, [x23, 1028]
	mov	w23, 3
	mov	w26, w23
.L2531:
	ldr	w0, [x21, 664]
	mov	w1, 16
	ldr	x2, .LC768
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x5, [x27, x0, lsl 3]
	mov	x0, x27
	str	x5, [x29, 96]
	bl	u_v
	ldr	x5, [x29, 96]
	mov	w1, w23
	strh	w0, [x5, 1030]
	mov	x0, x27
	bl	PassBytes
	cmp	w25, w23
	bne	.L2529
	ldr	w0, [x21, 664]
	ldr	x1, [x27]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x1, [x1, 64]
	ldr	x0, [x27, x0, lsl 3]
	str	x1, [x0, 1056]
	mov	w1, 8
	ldr	x0, .LC769
	ldr	x5, [x0]
	ldr	w0, [x21, 664]
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x0, [x27, x0, lsl 3]
	str	w1, [x0, 1040]
	b	.L2692
.L2730:
	sub	w1, w19, w28
	mov	x0, x27
	bl	PassBytes
	tbz	w0, #31, .L2542
	ldr	x2, .LC750
	mov	w3, 11215
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2542
.L2650:
	mov	w0, 0
	mov	w25, 0
	b	.L2526
.L2721:
	ldr	x2, .LC750
	mov	w3, 11277
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2553
.L2727:
	ldr	x2, .LC750
	mov	w3, 11034
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2513
.L2726:
	ldr	x2, .LC750
	mov	w3, 11060
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2518
.L2729:
	ldr	x2, .LC750
	mov	w3, 10969
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2499
.L2702:
	ldr	x1, .LC752
	mov	w3, 11705
	ldr	x2, [x29, 104]
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2636
.L2708:
	ldr	x2, .LC750
	mov	w3, 11615
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2618
.L2707:
	ldr	x1, .LC752
	mov	w3, 11641
	ldr	x2, .LC808
	mov	w0, 20
	bl	dprint_vfmw
	b	.L2623
.L2712:
	ldr	x2, .LC750
	mov	w3, 11511
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2598
.L2711:
	ldr	x2, .LC750
	mov	w3, 11537
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2603
.L2710:
	ldr	x2, .LC750
	mov	w3, 11563
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2608
.L2709:
	ldr	x2, .LC750
	mov	w3, 11589
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2613
.L2720:
	ldr	x2, .LC750
	mov	w3, 11303
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2558
.L2719:
	ldr	x2, .LC750
	mov	w3, 11329
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2563
.L2718:
	ldr	x2, .LC750
	mov	w3, 11355
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2568
.L2717:
	ldr	x2, .LC750
	mov	w3, 11381
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2573
.L2716:
	ldr	x2, .LC750
	mov	w3, 11407
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2578
.L2715:
	ldr	x2, .LC750
	mov	w3, 11433
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2583
.L2714:
	ldr	x2, .LC750
	mov	w3, 11459
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2588
.L2713:
	ldr	x2, .LC750
	mov	w3, 11485
	ldr	x1, .LC752
	mov	w0, 20
	add	x2, x2, 232
	bl	dprint_vfmw
	b	.L2593
.L2649:
	mov	w0, -1
	b	.L2461
.L2724:
	ldr	x1, .LC771
	mov	w0, 1
	bl	dprint_vfmw
.L2690:
	ldr	w1, [x21, 664]
	ldr	w0, [x21, 1980]
	add	x1, x1, 8192
	add	x1, x1, 84
	ldr	x1, [x27, x1, lsl 3]
	bl	FreeUsdByDec
	ldr	w1, [x21, 664]
	mov	w0, -1
	add	x1, x1, 8192
	add	x1, x1, 84
	str	xzr, [x27, x1, lsl 3]
	b	.L2461
.L2725:
	ldr	x1, .LC773
	mov	w0, 1
	bl	dprint_vfmw
	b	.L2690
.L2530:
	ldr	x2, .LC766
	mov	w1, 8
	mov	x0, x27
	bl	u_v
	strb	w0, [x23, 1028]
	mov	w23, 4
	mov	w26, w23
	b	.L2531
.L2694:
	ldr	x2, .LC740
	mov	w3, 10873
	ldr	x1, .LC741
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2461
	.size	H264_DecSEI, .-H264_DecSEI
	.align	3
.LC740:
	.xword	.LC30
	.align	3
.LC741:
	.xword	.LC32
	.align	3
.LC742:
	.xword	s_pstVfmwChan
	.align	3
.LC744:
	.xword	.LC743
	.align	3
.LC746:
	.xword	.LC745
	.align	3
.LC747:
	.xword	.L2476
	.align	3
.LC749:
	.xword	.LC748
	.align	3
.LC750:
	.xword	.LANCHOR2
	.align	3
.LC752:
	.xword	.LC751
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
	.align	3
.LC768:
	.xword	.LC767
	.align	3
.LC769:
	.xword	g_event_report
	.align	3
.LC771:
	.xword	.LC770
	.align	3
.LC773:
	.xword	.LC772
	.align	3
.LC775:
	.xword	.LC774
	.align	3
.LC777:
	.xword	.LC776
	.align	3
.LC779:
	.xword	.LC778
	.align	3
.LC781:
	.xword	.LC780
	.align	3
.LC783:
	.xword	.LC782
	.align	3
.LC785:
	.xword	.LC784
	.align	3
.LC787:
	.xword	.LC786
	.align	3
.LC789:
	.xword	.LC788
	.align	3
.LC791:
	.xword	.LC790
	.align	3
.LC793:
	.xword	.LC792
	.align	3
.LC795:
	.xword	.LC794
	.align	3
.LC797:
	.xword	.LC796
	.align	3
.LC799:
	.xword	.LC798
	.align	3
.LC801:
	.xword	.LC800
	.align	3
.LC803:
	.xword	.LC802
	.align	3
.LC805:
	.xword	.LC804
	.align	3
.LC807:
	.xword	.LC806
	.align	3
.LC808:
	.xword	.LANCHOR2+232
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_IsNewPicNal
	.type	H264_IsNewPicNal, %function
H264_IsNewPicNal:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w0, [x20, 3]
	and	w0, w0, 31
	sub	w0, w0, #1
	cmp	w0, 7
	bls	.L2740
.L2739:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2740:
	ldr	x1, .LC809
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx2734
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2734:
	.section	.rodata
	.align	0
	.align	2
.L2734:
	.byte	(.L2733 - .Lrtx2734) / 4
	.byte	(.L2739 - .Lrtx2734) / 4
	.byte	(.L2739 - .Lrtx2734) / 4
	.byte	(.L2739 - .Lrtx2734) / 4
	.byte	(.L2733 - .Lrtx2734) / 4
	.byte	(.L2739 - .Lrtx2734) / 4
	.byte	(.L2735 - .Lrtx2734) / 4
	.byte	(.L2735 - .Lrtx2734) / 4
	.text
	.p2align 3
.L2735:
	ldr	w0, [x19]
	mov	w1, 1
	str	w1, [x19]
	cmp	w0, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2733:
	ldr	w0, [x19]
	cbz	w0, .L2736
.L2738:
	mov	w0, -1
	str	wzr, [x19]
.L2741:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2736:
	ldr	w20, [x20, 4]
	rev	w20, w20
	mov	w0, w20
	bl	ZerosMS_32
	cmp	w0, 15
	bhi	.L2738
	mov	w1, 31
	str	wzr, [x19]
	sub	w0, w1, w0, lsl 1
	lsr	w20, w20, w0
	cmp	w20, 1
	csetm	w0, ne
	b	.L2741
	.size	H264_IsNewPicNal, .-H264_IsNewPicNal
	.align	3
.LC809:
	.xword	.L2734
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindZeroBitsInSeg
	.type	FindZeroBitsInSeg, %function
FindZeroBitsInSeg:
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
	ble	.L2762
	and	w1, w23, 63
	add	w0, w23, 63
	cmp	w1, wzr
	cset	w26, ne
	cmp	w23, wzr
	csel	w0, w0, w23, lt
	add	w26, w26, w0, asr 6
	cmp	w26, wzr
	ble	.L2755
	ldr	x20, .LC813
	mov	w25, w23
	ldr	x27, .LC812
	mov	w19, 0
	mov	w24, 64
	add	x20, x20, 1856
	.p2align 2
.L2754:
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
	cbnz	w1, .L2746
	cmp	x0, x20
	add	w19, w19, 1
	bne	.L2749
	b	.L2747
	.p2align 3
.L2750:
	add	w19, w19, 1
	beq	.L2747
.L2749:
	ldrb	w1, [x0, -1]!
	cmp	x0, x20
	cbz	w1, .L2750
.L2746:
	lsl	w0, w19, 3
.L2745:
	cmp	w19, w23
	mov	w1, 0
	bge	.L2751
	sxtw	x2, w23
	sub	x2, x2, #1
	sub	x19, x2, x19, sxtw
	ldrb	w2, [x22, x19]
	tbnz	x2, 0, .L2751
	lsr	w2, w2, 1
	mov	w1, 1
	.p2align 2
.L2753:
	tbnz	x2, 0, .L2751
	add	w1, w1, 1
	lsr	w2, w2, 1
	cmp	w1, 8
	bne	.L2753
.L2751:
	add	w0, w1, w0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2747:
	subs	w26, w26, #1
	sub	w25, w25, #64
	bne	.L2754
	b	.L2746
.L2762:
	ldr	x1, .LC811
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
.L2755:
	mov	w0, 0
	mov	w19, 0
	b	.L2745
	.size	FindZeroBitsInSeg, .-FindZeroBitsInSeg
	.align	3
.LC811:
	.xword	.LC810
	.align	3
.LC812:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC813:
	.xword	.LANCHOR4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindTrailZeros
	.type	FindTrailZeros, %function
FindTrailZeros:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2769
	ldr	x2, [x19, 632]
	ldr	w0, [x2, 76]
	cmp	w0, 1
	bls	.L2768
	ldr	w1, [x2, 48]
	ldr	x0, [x2, 40]
	bl	FindZeroBitsInSeg
	ldr	x2, [x19, 632]
	ldr	w1, [x2, 48]
	cmp	w0, w1, lsl 3
	bcs	.L2772
	cmn	w0, #1
	beq	.L2768
	add	w0, w0, 1
	str	w0, [x2, 80]
	ldr	x0, [x19, 632]
	ldr	w1, [x0, 76]
	cmp	w1, 1
	bls	.L2770
.L2773:
	ldr	w2, [x0, 48]
	mov	w20, 0
	ldr	w1, [x0, 80]
	cmp	w1, w2, lsl 3
	bcc	.L2764
	add	x2, x19, 65536
	ldr	w1, [x0, 68]
	ldr	w0, [x2, 1980]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 632]
	mov	w1, 1
	str	xzr, [x0, 40]
	ldr	x0, [x19, 632]
	str	w1, [x0, 76]
	ldr	x0, [x19, 632]
	str	wzr, [x0, 80]
.L2764:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2772:
	add	x0, x19, 65536
	ldr	w1, [x2, 68]
	ldr	w0, [x0, 1980]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 632]
	mov	w1, 1
	str	xzr, [x0, 40]
	ldr	x0, [x19, 632]
	str	w1, [x0, 76]
	ldr	x2, [x19, 632]
.L2768:
	ldr	w1, [x2, 16]
	ldr	x0, [x2, 8]
	bl	FindZeroBitsInSeg
	add	w0, w0, 1
	ldr	x2, [x19, 632]
	str	w0, [x2, 80]
	ldr	x0, [x19, 632]
	ldr	w1, [x0, 76]
	cmp	w1, 1
	bhi	.L2773
.L2770:
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2769:
	mov	w20, -1
	b	.L2764
	.size	FindTrailZeros, .-FindTrailZeros
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CombinePacket
	.type	CombinePacket, %function
CombinePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2774
	ldr	x0, [x19, 632]
	ldr	w0, [x0, 16]
	cmp	w0, 4095
	bhi	.L2774
	mov	x0, x19
	bl	CombinePacket.part.17
.L2774:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CombinePacket, .-CombinePacket
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FindNaluArraySlot
	.type	FindNaluArraySlot, %function
FindNaluArraySlot:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L2784
	ldrb	w0, [x19, 641]
	cbz	w0, .L2785
	add	x0, x19, 745
	mov	x1, 1
	b	.L2783
	.p2align 3
.L2782:
	add	w1, w1, 1
	cmp	w1, 137
	beq	.L2784
.L2783:
	ldrb	w2, [x0]
	add	x0, x0, 104
	cbnz	w2, .L2782
	mov	w0, w1
.L2781:
	lsl	x2, x1, 3
	mov	w3, 1
	sub	x2, x2, x1
	lsl	x2, x2, x3
	sub	x1, x2, x1
	add	x1, x19, x1, lsl 3
	strb	w3, [x1, 641]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2784:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2785:
	mov	w0, 0
	mov	x1, 0
	b	.L2781
	.size	FindNaluArraySlot, .-FindNaluArraySlot
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InquireSliceExtProperty
	.type	InquireSliceExtProperty, %function
InquireSliceExtProperty:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 12288
	mov	w1, 24
	add	x0, x0, 2600
	bl	BsGet
	ubfx	x2, x0, 23, 1
	ldr	x1, [x19, 632]
	strb	w2, [x1, 3]
	ldr	x3, [x19, 632]
	ldrb	w1, [x3, 3]
	cbnz	w1, .L2789
	add	x1, x19, 61440
	ldrb	w2, [x1, 3560]
.L2790:
	cmp	w2, 1
	bne	.L2791
	mov	w0, 5
	strb	w0, [x3, 2]
.L2791:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2789:
	add	x1, x19, 61440
	ubfx	x5, x0, 16, 6
	ubfx	x4, x0, 15, 1
	ubfx	x2, x0, 22, 1
	ubfx	x9, x0, 12, 3
	ubfx	x8, x0, 8, 4
	ubfx	x7, x0, 5, 3
	ubfx	x6, x0, 4, 1
	strb	w5, [x1, 3561]
	ubfx	x5, x0, 3, 1
	strb	w4, [x1, 3562]
	ubfx	x4, x0, 2, 1
	strb	w2, [x1, 3560]
	and	w0, w0, 3
	strb	w9, [x1, 3563]
	strb	w8, [x1, 3564]
	strb	w7, [x1, 3565]
	strb	w6, [x1, 3566]
	strb	w5, [x1, 3567]
	strb	w4, [x1, 3568]
	strb	w0, [x1, 3569]
	b	.L2790
	.size	InquireSliceExtProperty, .-InquireSliceExtProperty
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InquireSliceProperty
	.type	InquireSliceProperty, %function
InquireSliceProperty:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x20, x2
	bl	_mcount
	add	x21, x19, 20480
	add	x2, x19, 65536
	ldr	x1, .LC816
	mov	w0, 22
	ldr	w2, [x2, 1924]
	sub	w2, w2, #1
	bl	dprint_vfmw
	str	wzr, [x20]
	str	wzr, [x23]
	mov	x0, x19
	ldr	x1, [x19, 632]
	ldrb	w2, [x1, 2]
	strb	w2, [x21, 1587]
	ldr	w1, [x1, 84]
	str	w1, [x21, 1612]
	bl	SliceCheck
	mov	w22, w0
	cbnz	w0, .L2796
	mov	x0, x19
	bl	ProcessSliceHeaderFirstPart
	cbnz	w0, .L2800
	ldrb	w3, [x21, 1589]
	mov	w1, 2208
	mov	w0, 4000
	mov	w2, 2
	cmp	w3, 1
	cset	w3, eq
	str	w3, [x23]
	ldr	w3, [x21, 1592]
	ldr	x4, [x19, 14968]
	ldr	x6, [x19, 14960]
	umull	x1, w3, w1
	ldr	w5, [x19, 14936]
	add	x1, x4, x1
	ldr	w4, [x19, 14932]
	ldr	w1, [x1, 28]
	umull	x0, w1, w0
	add	x0, x6, x0
	ldrb	w1, [x0, 18]
	ldr	w6, [x0, 3252]
	sub	w1, w2, w1
	ldr	w3, [x0, 3248]
	madd	w1, w6, w1, w1
	add	w2, w3, 1
	cmp	w1, w5
	ccmp	w2, w4, 0, eq
	bne	.L2801
.L2795:
	add	x19, x19, 24576
	ldr	w1, [x0, 3272]
	ldr	w0, [x19, 3704]
	add	w0, w0, 1
	cmp	w1, w0
	beq	.L2793
	mov	w0, 1
	str	w0, [x20]
.L2793:
	mov	w0, w22
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2801:
	mov	w1, 1
	str	w1, [x20]
	b	.L2795
	.p2align 3
.L2796:
	mov	w22, -1
	b	.L2793
	.p2align 3
.L2800:
	ldr	x1, .LC818
	mov	w0, 1
	mov	w22, -1
	bl	dprint_vfmw
	b	.L2793
	.size	InquireSliceProperty, .-InquireSliceProperty
	.align	3
.LC816:
	.xword	.LC815
	.align	3
.LC818:
	.xword	.LC817
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	HaveSliceToDec
	.type	HaveSliceToDec, %function
HaveSliceToDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 65536
	bl	_mcount
	ldr	w0, [x19, 1904]
	ldr	x19, [sp, 16]
	cmp	w0, wzr
	csetm	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	HaveSliceToDec, .-HaveSliceToDec
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_Destroy
	.type	H264DEC_Destroy, %function
H264DEC_Destroy:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	cbz	x22, .L2827
	mov	x0, x22
	add	x20, x22, 12288
	add	x19, x22, 640
	add	x21, x22, 65536
	bl	H264_ClearCurrPic
	add	x20, x20, 2600
	b	.L2807
	.p2align 3
.L2806:
	add	x19, x19, 104
	cmp	x20, x19
	beq	.L2828
.L2807:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L2806
	ldr	w0, [x21, 1980]
	mov	x1, x19
	add	x19, x19, 104
	bl	ReleaseNAL
	cmp	x20, x19
	bne	.L2807
.L2828:
	ldr	w0, [x21, 1916]
	cmp	w0, 1
	beq	.L2829
.L2808:
	ldr	w0, [x21, 664]
	mov	w20, 0
	cbz	w0, .L2813
	.p2align 2
.L2821:
	add	x19, x22, x20, uxtw 3
	add	w20, w20, 1
	add	x19, x19, 65536
	ldr	x0, [x19, 672]
	mov	x1, x0
	cbz	x0, .L2811
	ldr	w0, [x21, 1980]
	bl	FreeUsdByDec
	str	xzr, [x19, 672]
.L2811:
	ldr	w0, [x21, 664]
	cmp	w0, w20
	bhi	.L2821
.L2813:
	add	x20, x22, 28672
	add	x22, x22, 61440
	add	x20, x20, 1144
	add	x22, x22, 2616
	.p2align 2
.L2810:
	sub	x19, x20, #32
.L2815:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L2814
	ldr	w0, [x21, 1980]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L2814:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L2815
	add	x20, x19, 856
	cmp	x20, x22
	bne	.L2810
	ldr	x1, .LC822
	mov	w0, 2
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2829:
	str	wzr, [x21, 1916]
	b	.L2808
.L2827:
	ldr	x2, .LC819
	mov	w3, 12685
	ldr	x1, .LC820
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	H264DEC_Destroy, .-H264DEC_Destroy
	.align	3
.LC819:
	.xword	.LC30
	.align	3
.LC820:
	.xword	.LC32
	.align	3
.LC822:
	.xword	.LC821
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_RecycleImage
	.type	H264DEC_RecycleImage, %function
H264DEC_RecycleImage:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	ldr	x1, .LC824
	mov	w0, 2
	bl	dprint_vfmw
	cbz	x21, .L2841
	add	x21, x21, 65536
	mov	w1, w22
	ldr	w0, [x21, 1980]
	bl	FSP_GetLogicFs
	cbz	x0, .L2836
	ldrsb	w1, [x0, 1]
	cbz	w1, .L2836
	add	x19, x0, 592
	add	x20, x0, 624
.L2834:
	ldr	x1, [x19]
	cbnz	x1, .L2842
.L2833:
	add	x19, x19, 8
	cmp	x19, x20
	bne	.L2834
	ldr	w0, [x21, 1980]
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, 0
.L2832:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2842:
	ldr	w0, [x21, 1980]
	bl	FreeUsdByDec
	str	xzr, [x19]
	b	.L2833
	.p2align 3
.L2836:
	mov	w0, -1
	b	.L2832
.L2841:
	ldr	x2, .LC825
	mov	w3, 13409
	ldr	x1, .LC826
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2832
	.size	H264DEC_RecycleImage, .-H264DEC_RecycleImage
	.align	3
.LC824:
	.xword	.LC823
	.align	3
.LC825:
	.xword	.LC30
	.align	3
.LC826:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OutputFrmToVO
	.type	OutputFrmToVO, %function
OutputFrmToVO:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x22, x1
	mov	w23, w2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x22, xzr, 4, ne
	beq	.L2885
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cbz	w0, .L2846
	add	x0, x19, 65536
	ldr	w0, [x0, 1908]
	cmp	w0, 2
	beq	.L2846
	add	x19, x19, 61440
	ldr	x0, [x19, 3544]
	cbz	x0, .L2848
	strb	wzr, [x0, 1]
	mov	w0, 1
	str	xzr, [x19, 3544]
.L2845:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2846:
	mov	x1, x22
	mov	x0, x19
	bl	CheckFrameStore
	cmn	w0, #3
	beq	.L2848
	add	x20, x19, 61440
	ldr	x1, [x20, 3544]
	cbz	x1, .L2849
	mov	x0, x19
	bl	GetImagePara
	ldr	x1, [x20, 3544]
	mov	x0, x19
	bl	CheckFrameStore
	cbz	w0, .L2886
	cmn	w0, #3
	beq	.L2856
	ldr	x1, .LC834
	mov	w3, w0
	mov	w2, 2215
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x20, 3544]
	mov	x0, x19
	ldr	w1, [x1, 164]
	bl	H264DEC_RecycleImage
.L2856:
	ldr	x0, [x20, 3544]
	strb	wzr, [x0, 1]
	ldr	x0, [x20, 3544]
	str	xzr, [x20, 3544]
	cmp	x22, x0
	beq	.L2887
.L2849:
	mov	x1, x22
	mov	x0, x19
	bl	GetImagePara
	mov	x1, x22
	mov	x0, x19
	bl	CheckFrameStore
	cbz	w0, .L2888
	cmn	w0, #3
	beq	.L2848
	ldr	x1, .LC834
	mov	w3, w0
	mov	w2, 2272
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x22, 164]
	mov	x0, x19
	bl	H264DEC_RecycleImage
	mov	w0, 2
	b	.L2845
	.p2align 3
.L2885:
	ldr	x1, .LC828
	mov	x3, x22
	mov	x2, x19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2848:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L2888:
	add	x21, x19, 65536
	ldr	w1, [x22, 656]
	mov	w2, 1
	ldr	w0, [x21, 1980]
	bl	FSP_SetDisplay
	ldr	w0, [x21, 1980]
	ldr	w1, [x22, 656]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L2889
	cmp	w23, 1
	beq	.L2890
.L2860:
	ldr	w0, [x21, 1980]
	mov	x4, x20
	add	x3, x19, 8
	mov	x2, x19
	mov	w1, 0
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L2891
	ldr	x0, [x19]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L2892
	str	wzr, [x20, 16]
.L2863:
	ldr	w1, [x21, 2000]
	mov	w0, 0
	ldr	w2, [x21, 2008]
	add	w1, w1, 2
	str	w1, [x21, 2000]
	add	w2, w2, 1
	str	w2, [x21, 2008]
	b	.L2845
	.p2align 3
.L2886:
	ldr	x0, [x20, 3544]
	add	x21, x19, 65536
	mov	w2, 1
	ldr	w1, [x0, 656]
	ldr	w0, [x21, 1980]
	bl	FSP_SetDisplay
	ldr	x1, [x20, 3544]
	ldr	w0, [x21, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	cbz	x0, .L2893
	ldr	x0, [x20, 3544]
	cmp	x0, x22
	ccmp	w23, 1, 0, eq
	beq	.L2894
.L2852:
	ldr	w0, [x21, 1980]
	mov	x4, x24
	add	x3, x19, 8
	mov	x2, x19
	mov	w1, 0
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L2895
	ldr	x0, [x19]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L2896
	str	wzr, [x24, 16]
.L2855:
	ldr	w0, [x21, 2000]
	ldr	w1, [x21, 2008]
	add	w0, w0, 2
	str	w0, [x21, 2000]
	add	w1, w1, 1
	str	w1, [x21, 2008]
	b	.L2856
	.p2align 3
.L2890:
	str	w23, [x0, 180]
	b	.L2860
	.p2align 3
.L2892:
	mov	x1, x20
	mov	x0, x19
	bl	SetFrmRepeatCount.part.7
	b	.L2863
	.p2align 3
.L2896:
	mov	x1, x24
	mov	x0, x19
	bl	SetFrmRepeatCount.part.7
	b	.L2855
	.p2align 3
.L2894:
	mov	w0, 1
	str	w0, [x24, 180]
	b	.L2852
	.p2align 3
.L2887:
	mov	w0, 0
	b	.L2845
.L2891:
	ldr	x1, .LC832
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x21, 1980]
	mov	w2, 0
	ldr	w1, [x22, 656]
	bl	FSP_SetDisplay
	mov	w1, 1
	mov	x0, x19
	bl	ClearAll
	mov	w0, -1
	b	.L2845
.L2895:
	ldr	x1, .LC832
	mov	w2, w0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x20, 3544]
	mov	w2, 0
	strb	wzr, [x0, 1]
	ldr	x1, [x20, 3544]
	ldr	w0, [x21, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetDisplay
	str	xzr, [x20, 3544]
	mov	w1, 1
	mov	x0, x19
	bl	ClearAll
	mov	w0, -1
	b	.L2845
.L2893:
	ldr	x1, .LC830
	mov	w2, 2186
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2845
.L2889:
	ldr	x1, .LC836
	mov	w2, 2242
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2845
	.size	OutputFrmToVO, .-OutputFrmToVO
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OutputFrmFromDPB
	.type	OutputFrmFromDPB, %function
OutputFrmFromDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L2902
	add	x20, x19, x21, uxtw 3
	ldr	x0, [x20, 27896]
	cbz	x0, .L2903
	strb	wzr, [x0, 4]
	mov	w2, 0
	mov	x0, x19
	ldr	x1, [x20, 27896]
	bl	OutputFrmToVO
	ldr	x1, [x20, 27896]
	mov	w20, w0
	ldrb	w0, [x1, 2]
	cbnz	w0, .L2899
	mov	w1, w21
	mov	x0, x19
	bl	RemoveFrameStoreOutDPB
.L2899:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2903:
	ldr	x2, .LC837
	mov	w3, 2292
	ldr	x1, .LC838
	mov	w20, -1
	bl	dprint_vfmw
	b	.L2899
.L2902:
	ldr	x2, .LC837
	mov	w3, 2291
	ldr	x1, .LC838
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L2899
	.size	OutputFrmFromDPB, .-OutputFrmFromDPB
	.align	3
.LC837:
	.xword	.LC30
	.align	3
.LC838:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FlushDPB
	.type	FlushDPB, %function
FlushDPB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L2905
	add	x19, x20, 24576
	mov	w21, 0
	ldr	w0, [x19, 3708]
	cbnz	w0, .L2923
	b	.L2907
	.p2align 3
.L2909:
	ldr	w0, [x19, 3708]
	cmp	w0, w21
	bls	.L2907
.L2923:
	add	x0, x20, x21, uxtw 3
	add	w21, w21, 1
	ldr	x1, [x0, 27896]
	ldrb	w0, [x1, 2]
	cbz	w0, .L2909
	mov	x0, x20
	bl	UnMarkFrameStoreRef
	ldr	w0, [x19, 3708]
	cmp	w0, w21
	bhi	.L2923
	.p2align 2
.L2907:
	mov	x0, x20
	bl	RemoveUnUsedFrameStore
	cbnz	w0, .L2907
	.p2align 2
.L2912:
	ldr	w6, [x19, 3708]
	cbz	w6, .L2928
	ldr	w0, [x19, 3704]
	cmp	w6, w0
	bls	.L2913
	str	w0, [x19, 3708]
	cbz	w0, .L2918
	mov	w6, w0
.L2913:
	add	x2, x19, 3320
	mov	w5, 2147483647
	mov	w0, 0
	mov	w1, 0
	.p2align 2
.L2916:
	ldr	x4, [x2]
	add	x2, x2, 8
	ldr	w3, [x4, 672]
	cmp	w3, w5
	bge	.L2915
	ldrb	w4, [x4, 4]
	cmp	w4, wzr
	csel	w5, w5, w3, eq
	csel	w1, w1, w0, eq
.L2915:
	add	w0, w0, 1
	cmp	w6, w0
	bhi	.L2916
	mov	x0, x20
	bl	OutputFrmFromDPB
	cmn	w0, #1
	bne	.L2912
.L2908:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2918:
	mov	w1, 0
	mov	x0, x20
	bl	OutputFrmFromDPB
	cmn	w0, #1
	bne	.L2912
	b	.L2908
	.p2align 3
.L2928:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2905:
	ldr	x2, .LC839
	mov	w3, 2414
	ldr	x1, .LC840
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2908
	.size	FlushDPB, .-FlushDPB
	.align	3
.LC839:
	.xword	.LC30
	.align	3
.LC840:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AdaptiveMemMark
	.type	AdaptiveMemMark, %function
AdaptiveMemMark:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x26, x21, 61440
	add	x25, x21, 20480
	bl	_mcount
	ldr	x24, .LC841
	add	x23, x26, 2024
	mov	w27, 1
	ldr	x22, [x26, 2688]
	add	x20, x22, 8
	add	x22, x22, 2008
	.p2align 2
.L2942:
	ldr	w0, [x20, -4]
	cmp	w0, 6
	bhi	.L2930
	ldrb	w0, [x24,w0,uxtw]
	adr	x1, .Lrtx2932
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx2932:
	.section	.rodata
	.align	0
	.align	2
.L2932:
	.byte	(.L2931 - .Lrtx2932) / 4
	.byte	(.L2933 - .Lrtx2932) / 4
	.byte	(.L2934 - .Lrtx2932) / 4
	.byte	(.L2935 - .Lrtx2932) / 4
	.byte	(.L2936 - .Lrtx2932) / 4
	.byte	(.L2937 - .Lrtx2932) / 4
	.byte	(.L2938 - .Lrtx2932) / 4
	.text
	.p2align 3
.L2937:
	add	x28, x21, 24576
	mov	w19, 0
	ldr	w0, [x28, 3712]
	cbz	w0, .L2941
	.p2align 2
.L2949:
	add	x1, x21, x19, uxtw 3
	mov	x0, x21
	add	w19, w19, 1
	ldr	x1, [x1, 28024]
	bl	UnMarkFrameStoreRef
	ldr	w0, [x28, 3712]
	cmp	w19, w0
	bcc	.L2949
.L2941:
	mov	x0, x21
	bl	UpdateReflist
	mov	w1, 0
	mov	x0, x21
	bl	UpdateMaxLTFrmIdx
	mov	x0, x21
	bl	UpdateLTReflist
	str	w27, [x25, 728]
	.p2align 2
.L2930:
	add	x20, x20, 20
	cmp	x20, x22
	bne	.L2942
	.p2align 2
.L2931:
	ldr	w1, [x25, 728]
	mov	w0, 0
	cmp	w1, 1
	beq	.L2952
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L2936:
	ldr	w1, [x20, 12]
	mov	x0, x21
	bl	UpdateMaxLTFrmIdx
	mov	x0, x21
	bl	UpdateLTReflist
	b	.L2930
	.p2align 3
.L2935:
	ldr	w2, [x20]
	mov	x1, x23
	ldr	w3, [x20, 8]
	mov	x0, x21
	bl	MarkSTToLTRef
	mov	x0, x21
	bl	UpdateReflist
	mov	x0, x21
	bl	UpdateLTReflist
	b	.L2930
	.p2align 3
.L2934:
	ldr	w2, [x20, 4]
	mov	x0, x21
	mov	x1, x23
	bl	UnMarkLTRef
	mov	x0, x21
	bl	UpdateLTReflist
	b	.L2930
	.p2align 3
.L2933:
	ldr	w2, [x20]
	mov	x0, x21
	mov	x1, x23
	bl	UnMarkSTRef
	mov	x0, x21
	bl	UpdateReflist
	b	.L2930
	.p2align 3
.L2938:
	ldr	w2, [x20, 8]
	mov	x1, x23
	mov	x0, x21
	bl	MarkCurrPicLT
	b	.L2930
	.p2align 3
.L2952:
	ldrb	w0, [x26, 2027]
	str	wzr, [x26, 2696]
	cmp	w0, 1
	beq	.L2945
	cbz	w0, .L2946
	cmp	w0, 2
	bne	.L2944
	str	wzr, [x26, 2708]
	str	wzr, [x26, 2720]
	str	wzr, [x25, 740]
	str	wzr, [x25, 748]
.L2944:
	mov	x0, x21
	bl	FlushDPB
	cmp	w0, wzr
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2946:
	ldr	w2, [x26, 2708]
	ldr	w0, [x26, 2716]
	ldr	w1, [x26, 2720]
	sub	w0, w0, w2
	str	w0, [x26, 2716]
	sub	w1, w1, w2
	str	w1, [x26, 2720]
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x26, 2708]
	str	w0, [x26, 2712]
	ldr	w2, [x25, 748]
	ldr	w0, [x25, 736]
	ldr	w1, [x25, 740]
	sub	w0, w0, w2
	str	w0, [x25, 736]
	sub	w1, w1, w2
	str	w1, [x25, 740]
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x25, 744]
	str	w0, [x25, 748]
	b	.L2944
.L2945:
	str	wzr, [x26, 2708]
	str	wzr, [x26, 2716]
	str	wzr, [x25, 736]
	str	wzr, [x25, 748]
	b	.L2944
	.size	AdaptiveMemMark, .-AdaptiveMemMark
	.align	3
.LC841:
	.xword	.L2932
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IDRMemMarking
	.type	IDRMemMarking, %function
IDRMemMarking:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x22, x0
	mov	x0, x30
	add	x24, x22, 61440
	bl	_mcount
	ldr	x0, [x24, 2688]
	ldrb	w0, [x0, 1]
	cbz	w0, .L2954
	add	x23, x22, 24576
	mov	w21, 0
	add	x20, x22, 65536
	mov	w25, 1
	ldr	w0, [x23, 3708]
	cbnz	w0, .L2969
	b	.L2961
	.p2align 3
.L2958:
	strb	wzr, [x0, 706]
	strb	wzr, [x0, 705]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 754]
	strb	wzr, [x0, 753]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 802]
	strb	wzr, [x0, 801]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 2]
	ldr	x1, [x19, 27896]
	ldr	w0, [x20, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetRef
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 1]
	ldr	x0, [x19, 27896]
	strb	wzr, [x0, 4]
	ldr	x0, [x19, 27896]
	str	w25, [x0, 676]
	ldr	x1, [x19, 27896]
	ldr	w0, [x1, 696]
	add	x0, x0, 4096
	add	x0, x0, 2980
	str	wzr, [x22, x0, lsl 2]
	ldr	w1, [x1, 656]
	ldr	w0, [x20, 1980]
	bl	FSP_GetDisplay
	cmp	w0, 3
	mov	w2, 0
	beq	.L2959
	ldr	x1, [x19, 27896]
	ldr	w0, [x20, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetDisplay
.L2959:
	str	xzr, [x19, 27896]
	str	xzr, [x19, 28024]
	str	xzr, [x19, 28152]
	ldr	w0, [x23, 3708]
	cmp	w0, w21
	bls	.L2961
.L2969:
	add	x19, x22, x21, uxtw 3
	mov	w2, 0
	add	w21, w21, 1
	ldr	x0, [x19, 27896]
	ldr	w1, [x0, 848]
	cmp	w1, 1
	bne	.L2958
	str	w1, [x20, 652]
	b	.L2958
	.p2align 3
.L2961:
	str	wzr, [x23, 3708]
	ldr	w0, [x20, 640]
	cbz	w0, .L2957
	sub	w1, w0, #1
	add	x0, x20, 568
	add	x1, x1, 16384
	add	x1, x1, 143
	add	x1, x22, x1, lsl 2
	.p2align 2
.L2964:
	str	wzr, [x0], 4
	cmp	x0, x1
	bne	.L2964
.L2957:
	mov	x0, x22
	bl	UpdateReflist
	mov	x0, x22
	bl	UpdateLTReflist
	ldr	x0, [x24, 2688]
	ldrb	w0, [x0, 2]
	cbnz	w0, .L2975
	mov	w0, 1
	str	wzr, [x23, 3720]
	strb	w0, [x24, 2029]
	mov	w0, 0
	strb	wzr, [x24, 2028]
.L2965:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2975:
	mov	w0, 1
	str	w0, [x23, 3720]
	strb	w0, [x24, 2028]
	mov	w0, 0
	strb	wzr, [x24, 2029]
	str	wzr, [x24, 2700]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L2954:
	mov	x0, x22
	bl	FlushDPB
	cbnz	w0, .L2966
	add	x23, x22, 24576
	b	.L2957
.L2966:
	mov	w0, -1
	b	.L2965
	.size	IDRMemMarking, .-IDRMemMarking
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Marking
	.type	Marking, %function
Marking:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 61440
	bl	_mcount
	add	x0, x20, 20480
	str	wzr, [x0, 728]
	ldrb	w1, [x19, 2027]
	cmp	w1, 2
	cset	w1, eq
	str	w1, [x0, 732]
	ldrb	w0, [x19, 2030]
	cmp	w0, 5
	beq	.L2977
	ldr	w0, [x19, 2724]
	cbnz	w0, .L2978
	ldr	x0, [x20]
	mov	x1, 4294967296
	ldr	x2, [x0, 696]
	cmp	x2, x1
	beq	.L3002
.L2978:
	ldr	x0, [x19, 2688]
	ldrb	w0, [x0, 3]
	cbz	w0, .L3003
	ldr	w0, [x19, 2704]
	cbnz	w0, .L3004
.L2985:
	mov	w0, 0
.L2982:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3003:
	ldr	w0, [x19, 2704]
	cbz	w0, .L2985
.L2984:
	ldrb	w1, [x19, 2025]
	cbnz	w1, .L2989
	add	x1, x20, 24576
	add	x2, x20, 16384
	ldr	w4, [x1, 3716]
	ldr	w2, [x2, 1836]
	ldr	w3, [x1, 3712]
	sub	w1, w2, w4
	cmp	w3, w1
	beq	.L3005
	strb	wzr, [x19, 2028]
.L2987:
	cbz	w0, .L2985
.L2989:
	ldrb	w1, [x19, 2028]
	mov	w0, 0
	cmp	w1, wzr
	cset	w1, eq
	strb	w1, [x19, 2029]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3002:
	ldr	w1, [x0, 704]
	cbnz	w1, .L2978
	ldr	w0, [x0, 660]
	add	w0, w0, 1024
	cmp	w0, 2048
	bls	.L2978
	.p2align 2
.L2977:
	mov	x0, x20
	bl	IDRMemMarking
	cbz	w0, .L2986
.L2979:
	mov	w0, -1
	b	.L2982
	.p2align 3
.L3004:
	mov	x0, x20
	bl	AdaptiveMemMark
	cbnz	w0, .L2979
.L2986:
	ldrb	w0, [x19, 2030]
	cmp	w0, 5
	bne	.L3006
	ldr	w0, [x19, 2704]
	b	.L2987
	.p2align 3
.L3005:
	mov	x0, x20
	bl	SlidingWinMark.part.8
	strb	wzr, [x19, 2028]
	ldr	w0, [x19, 2704]
	b	.L2987
.L3006:
	ldr	w0, [x19, 2704]
	cbz	w0, .L2985
	ldr	x1, [x19, 2688]
	ldrb	w1, [x1, 3]
	cbnz	w1, .L2989
	b	.L2984
	.size	Marking, .-Marking
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitDPB
	.type	InitDPB, %function
InitDPB:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L3045
	mov	x0, x21
	add	x23, x21, 24576
	add	x19, x23, 3320
	add	x22, x23, 3448
	add	x20, x21, 65536
	bl	ClearAllSlice
	.p2align 2
.L3013:
	ldr	x0, [x19]
	mov	w2, 1
	cbz	x0, .L3010
	ldr	w1, [x0, 656]
	ldr	w0, [x20, 1980]
	bl	FSP_ClearLogicFs
.L3010:
	ldr	x0, [x19, 128]
	mov	w2, 1
	cbz	x0, .L3011
	ldr	w1, [x0, 656]
	ldr	w0, [x20, 1980]
	bl	FSP_ClearLogicFs
.L3011:
	ldr	x0, [x19, 256]
	mov	w2, 1
	cbz	x0, .L3012
	ldr	w1, [x0, 656]
	ldr	w0, [x20, 1980]
	bl	FSP_ClearLogicFs
.L3012:
	str	xzr, [x19, 128]
	str	xzr, [x19, 256]
	str	xzr, [x19], 8
	cmp	x19, x22
	bne	.L3013
	add	x0, x21, 16384
	add	x1, x23, 3584
	add	x19, x21, 61440
	ldr	w0, [x0, 1864]
	stp	wzr, wzr, [x1, 128]
	sub	w0, w0, #1
	stp	w0, wzr, [x1, 120]
	str	wzr, [x23, 3720]
	ldr	x1, [x19, 3544]
	cbz	x1, .L3015
	ldr	w0, [x20, 1908]
	cmp	w0, 2
	beq	.L3046
.L3016:
	ldr	w0, [x20, 1980]
	mov	w2, 1
	ldr	w1, [x1, 656]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 2680]
	cbz	x0, .L3019
	ldr	x2, [x19, 3544]
	ldr	w1, [x0, 656]
	ldr	w0, [x2, 656]
	cmp	w0, w1
	beq	.L3019
	ldr	w0, [x20, 1980]
	mov	w2, 1
	bl	FSP_ClearLogicFs
.L3019:
	str	xzr, [x19, 3544]
.L3015:
	ldr	x3, .LC847
	mov	x2, 392
	mov	w1, 0
	add	x0, x23, 3728
	ldr	x3, [x3, 96]
	blr	x3
	str	wzr, [x23, 3988]
	ldr	w0, [x23, 3704]
	str	w0, [x23, 3984]
	add	x0, x20, 568
	add	x20, x20, 636
	.p2align 2
.L3020:
	str	wzr, [x0], 4
	cmp	x0, x20
	bne	.L3020
	add	x2, x21, 28672
	add	x1, x2, 24
	add	x0, x2, 288
	.p2align 2
.L3021:
	str	xzr, [x1], 8
	cmp	x0, x1
	bne	.L3021
	add	x21, x21, 20480
	add	x1, x2, 552
	str	wzr, [x21, 1624]
	.p2align 2
.L3022:
	str	xzr, [x0], 8
	cmp	x1, x0
	bne	.L3022
	mov	w0, 0
	str	wzr, [x21, 1628]
.L3009:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L3046:
	mov	w2, 0
	mov	x0, x21
	bl	OutputFrmToVO
	cbnz	w0, .L3047
.L3017:
	ldr	x1, [x19, 3544]
	cbz	x1, .L3015
	b	.L3016
	.p2align 3
.L3047:
	ldr	x2, .LC844
	mov	w4, w0
	ldr	x1, .LC846
	mov	w3, 2357
	add	x2, x2, 248
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3017
.L3045:
	ldr	x2, .LC842
	mov	w3, 2319
	ldr	x1, .LC843
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3009
	.size	InitDPB, .-InitDPB
	.align	3
.LC842:
	.xword	.LC30
	.align	3
.LC843:
	.xword	.LC32
	.align	3
.LC844:
	.xword	.LANCHOR2
	.align	3
.LC846:
	.xword	.LC845
	.align	3
.LC847:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearAll
	.type	ClearAll, %function
ClearAll:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	str	x19, [x29, 104]
	bl	_mcount
	ldr	x1, .LC849
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x19
	cbz	x19, .L3079
	ldr	x20, [x29, 104]
	mov	x0, x20
	add	x19, x20, 640
	add	x22, x20, 65536
	add	x20, x20, 12288
	bl	H264_ClearCurrPic
	add	x20, x20, 2600
	b	.L3052
	.p2align 3
.L3051:
	add	x19, x19, 104
	cmp	x19, x20
	beq	.L3080
.L3052:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L3051
	ldr	w0, [x22, 1980]
	mov	x1, x19
	add	x19, x19, 104
	bl	ReleaseNAL
	cmp	x19, x20
	bne	.L3052
.L3080:
	ldr	x19, [x29, 104]
	mov	x0, x19
	bl	InitDPB
	cbz	w21, .L3053
	ldr	w0, [x22, 1980]
	add	x1, x19, 8
	bl	FSP_ClearNotInVoQueue
.L3054:
	ldr	x0, [x29, 104]
	mov	w21, 0
	mov	w28, -1
	mov	w23, 1
	add	x19, x0, 28672
	mov	w27, 17
	mov	w25, 16
	mov	w24, 2
	add	x19, x19, 552
	.p2align 2
.L3057:
	add	x0, x19, 512
	strb	wzr, [x19]
	strb	wzr, [x19, 1]
	add	x26, x19, 560
	strb	wzr, [x19, 2]
	add	x20, x19, 592
	strb	wzr, [x19, 4]
	strb	wzr, [x19, 704]
	strb	w23, [x19, 752]
	strb	w24, [x19, 800]
	str	w21, [x19, 164]
	stp	wzr, w28, [x0, 148]
	stp	wzr, wzr, [x0, 156]
	str	w23, [x19, 676]
	str	w27, [x19, 692]
	str	w25, [x19, 696]
	str	x19, [x19, 744]
	str	x19, [x19, 792]
	str	x19, [x19, 840]
.L3056:
	ldr	x0, [x26]
	mov	x1, x0
	cbz	x0, .L3055
	ldr	w0, [x22, 1980]
	bl	FreeUsdByDec
	str	xzr, [x26]
.L3055:
	add	x26, x26, 8
	cmp	x26, x20
	bne	.L3056
	add	w21, w21, 1
	add	x19, x19, 856
	cmp	w21, 40
	bne	.L3057
	ldr	x0, [x29, 104]
	add	x21, x0, 61440
	add	x19, x21, 2584
	add	x20, x21, 2616
.L3059:
	ldr	x0, [x19]
	mov	x1, x0
	cbz	x0, .L3058
	ldr	w0, [x22, 1980]
	bl	FreeUsdByDec
	str	xzr, [x19]
.L3058:
	add	x19, x19, 8
	cmp	x20, x19
	bne	.L3059
	ldr	w0, [x22, 664]
	mov	w20, 0
	cbz	w0, .L3063
	.p2align 2
.L3070:
	ldr	x0, [x29, 104]
	add	x19, x0, x20, uxtw 3
	add	w20, w20, 1
	add	x19, x19, 65536
	ldr	x0, [x19, 672]
	mov	x1, x0
	cbz	x0, .L3061
	ldr	w0, [x22, 1980]
	bl	FreeUsdByDec
	str	xzr, [x19, 672]
.L3061:
	ldr	w0, [x22, 664]
	cmp	w0, w20
	bhi	.L3070
.L3063:
	ldr	x1, [x29, 104]
	mov	x2, 1640
	str	wzr, [x22, 644]
	add	x0, x1, 24576
	str	wzr, [x22, 652]
	str	wzr, [x22, 656]
	add	x19, x1, 20480
	str	wzr, [x22, 664]
	str	wzr, [x22, 1904]
	str	wzr, [x22, 1912]
	str	wzr, [x22, 1956]
	str	wzr, [x22, 1964]
	str	wzr, [x22, 1984]
	str	xzr, [x1, 632]
	mov	w1, 0
	ldr	x3, .LC852
	strb	wzr, [x0, 1176]
	str	wzr, [x0, 3180]
	strb	wzr, [x19, 3268]
	strb	wzr, [x0, 1177]
	add	x0, x19, 1584
	ldr	x3, [x3, 96]
	strb	wzr, [x19, 3269]
	blr	x3
	mov	w0, 1
	mov	w1, 2
	strb	w0, [x19, 1589]
	mov	w0, 256
	strb	w1, [x19, 1584]
	str	w0, [x21, 3520]
	mov	w0, 0
	strb	wzr, [x21, 2024]
	strb	wzr, [x21, 3512]
	str	wzr, [x21, 3516]
.L3050:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3053:
	ldr	x0, [x29, 104]
	add	x0, x0, 8
	bl	ResetVoQueue
	ldr	w0, [x22, 1980]
	bl	FSP_EmptyInstance
	b	.L3054
.L3079:
	ldr	x2, .LC850
	mov	w3, 2033
	ldr	x1, .LC851
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3050
	.size	ClearAll, .-ClearAll
	.align	3
.LC849:
	.xword	.LC848
	.align	3
.LC850:
	.xword	.LC30
	.align	3
.LC851:
	.xword	.LC32
	.align	3
.LC852:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AllocFrameStore
	.type	AllocFrameStore, %function
AllocFrameStore:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	mov	x0, x30
	add	x20, x28, 20480
	mov	w23, w1
	bl	_mcount
	ldrb	w0, [x20, 1585]
	cbz	w0, .L3082
	ldrb	w1, [x20, 1586]
	cbz	w1, .L3151
	ldr	w2, [x20, 1592]
	mov	w1, 2208
	add	x21, x28, 65536
	ldr	x3, [x28, 14968]
	ldr	x4, [x28, 14960]
	umull	x1, w2, w1
	ldr	w22, [x21, 1908]
	add	x1, x3, x1
	str	x4, [x29, 104]
	cmp	w22, 2
	ldr	w25, [x1, 28]
	beq	.L3152
	add	x27, x28, 61440
	mov	w22, 2
	ldrb	w1, [x27, 3512]
	strb	wzr, [x27, 2025]
	cmp	w1, 1
	bne	.L3085
	b	.L3110
	.p2align 3
.L3082:
	ldr	w1, [x20, 1592]
	mov	w0, 2208
	add	x21, x28, 65536
	ldr	x2, [x28, 14968]
	ldr	x3, [x28, 14960]
	umull	x0, w1, w0
	ldr	w1, [x21, 1908]
	add	x0, x2, x0
	str	x3, [x29, 104]
	cmp	w1, 2
	ldr	w25, [x0, 28]
	beq	.L3153
	add	x27, x28, 61440
	mov	w22, 0
.L3146:
	strb	wzr, [x27, 2025]
.L3085:
	strb	wzr, [x27, 2024]
	ldr	w3, [x21, 636]
	cbz	w3, .L3100
	add	x19, x28, 28672
	mov	x26, 0
	add	x19, x19, 552
	.p2align 2
.L3099:
	ldrb	w0, [x19, 1]
	cbnz	w0, .L3094
	cbz	x19, .L3095
	add	x0, x28, 24576
	ldr	w2, [x0, 3708]
	cbz	w2, .L3095
	ldr	x0, [x28, 27896]
	cmp	x0, x19
	beq	.L3094
	sub	w2, w2, #1
	mov	x0, x28
	add	x2, x28, x2, lsl 3
	b	.L3097
	.p2align 3
.L3098:
	ldr	x1, [x0, 27896]
	cmp	x1, x19
	beq	.L3094
.L3097:
	cmp	x0, x2
	add	x0, x0, 8
	bne	.L3098
.L3095:
	lsl	x1, x26, 3
	str	x19, [x27, 2680]
	sub	x1, x1, x26
	mov	w24, 1
	lsl	x1, x1, 2
	strb	w24, [x27, 2024]
	sub	x1, x1, x26
	mov	w4, 101
	lsl	x1, x1, 2
	mov	x2, 640
	sub	x26, x1, x26
	add	x0, x27, 2040
	add	x26, x28, x26, lsl 3
	add	x26, x26, 28672
	add	x1, x26, 568
	str	wzr, [x26, 1240]
	str	w4, [x27, 2732]
	bl	memcpy
	str	wzr, [x27, 2192]
	strb	wzr, [x26, 555]
	str	wzr, [x19, 676]
	ldr	x0, [x27, 2680]
	strb	wzr, [x0, 2]
	ldr	x0, [x27, 2680]
	strb	w24, [x0, 4]
	ldr	x0, [x27, 2680]
	str	wzr, [x0, 848]
	ldrb	w19, [x27, 2024]
	cmp	w19, 1
	bne	.L3100
	cmp	w23, wzr
	ldr	w0, [x21, 1980]
	cset	w1, eq
	bl	FSP_NewLogicFs
	mov	w26, w0
	mov	w1, w0
	ldr	w0, [x21, 1980]
	bl	FSP_GetLogicFs
	mov	x23, x0
	cmp	w26, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L3101
	mov	w0, 4000
	add	x1, x23, 48
	umull	x25, w25, w0
	ldr	x0, [x29, 104]
	add	x24, x0, x25
	ldrb	w0, [x24, 3296]
	strb	w0, [x23, 488]
	ldr	w0, [x24, 3324]
	strb	w0, [x23, 489]
	ldr	w0, [x24, 3332]
	strb	w0, [x23, 490]
	ldr	w0, [x24, 3328]
	str	w0, [x23, 492]
	ldr	x0, [x28]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L3154
.L3102:
	ldr	x19, .LC855
	mov	x2, 640
	ldr	x0, [x27, 2680]
	ldr	x3, [x19, 104]
	add	x0, x0, 16
	blr	x3
	ldr	x1, [x27, 2680]
	mov	x2, 640
	ldr	x3, [x19, 104]
	add	x0, x27, 2040
	add	x1, x1, 16
	blr	x3
	ldr	x0, [x27, 2680]
	mov	w4, w26
	str	w26, [x0, 656]
	ldrsb	w0, [x23, 4]
	str	w0, [x27, 2756]
	ldr	x3, [x27, 2680]
	ldrb	w0, [x20, 1585]
.L3092:
	cmp	w0, wzr
	uxtb	w1, w22
	mov	w2, 3
	strb	w1, [x27, 2027]
	csel	w0, w0, w2, eq
	strb	w0, [x3, 704]
	ldrb	w0, [x27, 2025]
	cmp	w0, 1
	beq	.L3155
	strb	w1, [x27, 3512]
	ldr	w0, [x20, 1600]
	str	w0, [x27, 3520]
	ldr	w0, [x20, 1612]
	str	w0, [x27, 3516]
	ldr	w0, [x21, 1992]
	str	w0, [x27, 3528]
	str	w4, [x27, 3532]
	cbnz	w22, .L3156
	strb	wzr, [x27, 3513]
	mov	w0, 0
.L3141:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3151:
	ldr	w2, [x20, 1592]
	mov	w1, 2208
	add	x21, x28, 65536
	ldr	x3, [x28, 14968]
	ldr	x4, [x28, 14960]
	umull	x1, w2, w1
	ldr	w2, [x21, 1908]
	add	x1, x3, x1
	str	x4, [x29, 104]
	cmp	w2, 2
	ldr	w25, [x1, 28]
	beq	.L3157
	add	x27, x28, 61440
	mov	w22, 1
	ldrb	w1, [x27, 3512]
	strb	wzr, [x27, 2025]
	cmp	w1, 2
	bne	.L3085
.L3110:
	ldr	w1, [x20, 1600]
	ldr	w2, [x27, 3520]
	cmp	w2, w1
	bne	.L3085
	ldr	w1, [x20, 1612]
	cbnz	w1, .L3086
	ldr	w1, [x27, 3516]
	cbnz	w1, .L3085
.L3087:
	ldr	w2, [x21, 1988]
	ldr	w1, [x21, 1992]
	sub	w1, w1, w2
	cmp	w1, 2
	bhi	.L3085
	ldr	x3, [x27, 2680]
	mov	w1, 1
	strb	w1, [x27, 2025]
	cbz	x3, .L3146
	cmp	w22, 2
	beq	.L3158
	cmp	w22, 1
	mov	w4, 0
	bne	.L3092
	ldrb	w1, [x3, 1]
	cmp	w1, 2
	bne	.L3146
	b	.L3092
	.p2align 3
.L3094:
	add	w26, w26, 1
	add	x19, x19, 856
	cmp	w26, w3
	bne	.L3099
.L3100:
	ldr	x1, .LC854
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x28
	bl	ClearAll
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3156:
	mov	w1, 1
	strb	w1, [x27, 3513]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3153:
	mov	w22, 0
	add	x27, x28, 61440
	b	.L3146
.L3157:
	mov	w22, 1
	add	x27, x28, 61440
	b	.L3146
.L3155:
	strb	wzr, [x27, 3512]
	mov	w0, 0
	ldr	w1, [x20, 1600]
	str	w1, [x27, 3520]
	ldr	w1, [x20, 1612]
	str	w1, [x27, 3516]
	ldr	w1, [x21, 1992]
	str	w1, [x27, 3528]
	strb	wzr, [x27, 3513]
	str	w4, [x27, 3532]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3154:
	ldr	w2, [x28, 14936]
	ldr	w0, [x1, 112]
	lsl	w2, w2, 4
	ldr	w3, [x28, 14932]
	stp	wzr, wzr, [x1, 240]
	mul	w19, w2, w0
	ldr	w0, [x1, 36]
	lsl	w3, w3, 4
	stp	wzr, wzr, [x1, 248]
	stp	w3, w2, [x1, 68]
	add	w0, w19, w0
	str	wzr, [x1, 256]
	str	w0, [x1, 40]
	str	x1, [x29, 104]
	bl	MEM_Phy2Vir
	ldr	x1, [x29, 104]
	ldr	w2, [x1, 20]
	ldr	w3, [x1, 116]
	str	x0, [x1, 512]
	add	w0, w19, w2
	str	w0, [x1, 24]
	add	w0, w3, w0
	str	w0, [x1, 32]
	b	.L3102
.L3152:
	add	x27, x28, 61440
	b	.L3146
.L3086:
	ldr	w1, [x27, 3516]
	cbz	w1, .L3085
	b	.L3087
.L3101:
	ldr	x2, [x27, 2680]
	mov	w0, 0
	strb	wzr, [x27, 2024]
	ldr	x1, .LC857
	strb	wzr, [x2, 4]
	bl	dprint_vfmw
	mov	w1, w19
	mov	x0, x28
	bl	ClearAll
	mov	w0, -1
	b	.L3141
.L3158:
	ldrb	w1, [x3, 1]
	mov	w4, 0
	cmp	w1, 1
	bne	.L3146
	b	.L3092
	.size	AllocFrameStore, .-AllocFrameStore
	.align	3
.LC854:
	.xword	.LC853
	.align	3
.LC855:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC857:
	.xword	.LC856
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_Init
	.type	H264DEC_Init, %function
H264DEC_Init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cbz	x19, .L3171
	cbz	x21, .L3172
	ldr	x22, .LC860
	mov	x2, 2032
	movk	x2, 0x1, lsl 16
	mov	w1, 0
	mov	x0, x19
	ldr	w20, [x19, 608]
	ldr	x3, [x22, 96]
	blr	x3
	str	w20, [x19, 608]
	add	x0, x19, 8
	bl	ResetVoQueue
	str	x21, [x19]
	str	xzr, [x19, 616]
	str	wzr, [x19, 624]
	ldr	w0, [x21, 28]
	cmp	w0, 25
	beq	.L3173
	mov	w2, 32
	mov	w1, 256
	mov	w0, 136
	str	w2, [x19, 14944]
	str	w0, [x19, 14940]
	str	w1, [x19, 14948]
.L3164:
	ldr	w0, [x21, 632]
	mov	w23, 2208
	add	x20, x19, 65536
	bl	MEM_Phy2Vir
	ldr	x1, [x19]
	mov	w2, 4000
	ldr	w4, [x19, 14944]
	ldr	w5, [x19, 14948]
	ldrsw	x3, [x1, 628]
	smull	x2, w4, w2
	add	x3, x0, x3
	str	x3, [x19, 14960]
	add	x1, x3, x2
	str	x1, [x19, 14968]
	cmp	x1, xzr
	smaddl	x0, w5, w23, x1
	ccmp	x3, xzr, 4, ne
	str	x0, [x20, 1896]
	ccmp	x0, xzr, 4, ne
	beq	.L3174
	ldr	w6, [x21, 664]
	cmp	w6, wzr
	ccmp	x3, xzr, 4, eq
	ccmp	x1, xzr, 4, ne
	beq	.L3166
	ldr	x4, [x22, 96]
	mov	w1, 0
	mov	x0, x3
	blr	x4
	ldr	w2, [x19, 14948]
	mov	w1, 0
	ldr	x0, [x19, 14968]
	ldr	x3, [x22, 96]
	smull	x2, w2, w23
	blr	x3
	ldr	w4, [x19, 14944]
	ldr	w5, [x19, 14948]
	ldr	x0, [x20, 1896]
.L3166:
	add	x2, x19, 16384
	ldr	x6, [x22, 96]
	mov	w1, 0
	str	w5, [x2, 2616]
	str	w4, [x19, 15012]
	ldrsw	x3, [x19, 14940]
	lsl	x2, x3, 7
	sub	x2, x2, x3
	lsl	x2, x2, 5
	blr	x6
	str	wzr, [x20, 644]
	mov	w0, 17
	mov	w1, 40
	str	w0, [x20, 640]
	add	x0, x20, 512
	str	w1, [x20, 636]
	add	x1, x20, 512
	add	x2, x20, 1792
	add	x3, x20, 1792
	stp	wzr, wzr, [x0, 140]
	stp	wzr, wzr, [x0, 148]
	stp	xzr, xzr, [x1, 160]
	stp	xzr, xzr, [x1, 176]
	str	wzr, [x20, 1916]
	mov	x0, x19
	stp	wzr, wzr, [x2, 132]
	stp	wzr, wzr, [x2, 140]
	stp	wzr, wzr, [x3, 148]
	stp	wzr, wzr, [x3, 156]
	str	wzr, [x20, 1984]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x20, 1980]
	beq	.L3175
	mov	w1, 0
	mov	x0, x19
	bl	ClearAll
	mov	w0, 1
.L3161:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3173:
	ldr	w0, [x21, 748]
	str	w0, [x19, 14944]
	ldr	w0, [x21, 752]
	str	w0, [x19, 14948]
	ldr	w0, [x21, 740]
	str	w0, [x19, 14940]
	b	.L3164
.L3174:
	ldr	x2, .LC861
	mov	w3, 12614
	ldr	x1, .LC863
	mov	w0, 0
	add	x2, x2, 256
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3161
	.p2align 3
.L3175:
	ldr	x1, .LC865
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L3161
.L3172:
	ldr	x2, .LC858
	mov	w3, 12580
	ldr	x1, .LC859
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3161
.L3171:
	ldr	x2, .LC858
	mov	w3, 12579
	ldr	x1, .LC859
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3161
	.size	H264DEC_Init, .-H264DEC_Init
	.align	3
.LC858:
	.xword	.LC30
	.align	3
.LC859:
	.xword	.LC32
	.align	3
.LC860:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC861:
	.xword	.LANCHOR2
	.align	3
.LC863:
	.xword	.LC862
	.align	3
.LC865:
	.xword	.LC864
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ClearDPB
	.type	ClearDPB, %function
ClearDPB:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	FlushDPB
	cbz	w0, .L3177
	ldr	x1, .LC867
	mov	w3, w0
	mov	w2, 2449
	mov	w0, 0
	bl	dprint_vfmw
.L3177:
	mov	x0, x19
	add	x19, x19, 65536
	bl	InitDPB
	str	wzr, [x19, 652]
	mov	w0, 0
	str	wzr, [x19, 1984]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ClearDPB, .-ClearDPB
	.align	3
.LC867:
	.xword	.LC866
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertFrmInDPB
	.type	InsertFrmInDPB, %function
InsertFrmInDPB:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	mov	w20, w1
	mov	x19, x2
	bl	_mcount
	cmp	w20, 15
	bhi	.L3276
	ldrb	w21, [x19, 3]
	cmp	w21, 1
	beq	.L3185
	cbz	w21, .L3186
	cmp	w21, 2
	bne	.L3277
	ldr	x0, [x19, 656]
	mov	w1, 3
	uxtw	x22, w20
	strb	w1, [x0, 704]
	ldrb	w0, [x19, 1]
	cbz	w0, .L3204
	add	x20, x23, x22, lsl 3
	ldr	x0, [x20, 27896]
	cbz	x0, .L3204
	strb	w21, [x0, 800]
	ldr	x0, [x20, 27896]
	ldr	x1, [x19, 656]
	str	x1, [x0, 840]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 801]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 802]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 696]
	str	w1, [x0, 812]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 700]
	str	w1, [x0, 820]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 832]
	str	w1, [x0, 832]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 708]
	str	w1, [x0, 816]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 768]
	ldr	w1, [x0, 816]
	add	w1, w2, w1
	str	w1, [x0, 688]
	str	w1, [x0, 720]
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1]
	cbz	w0, .L3210
	ldrb	w0, [x19, 2]
.L3210:
	strb	w0, [x1]
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1, 1]
	orr	w0, w0, 2
	strb	w0, [x1, 1]
	ldrb	w0, [x19, 7]
	ldr	x1, [x20, 27896]
	cmp	w0, 1
	beq	.L3278
	ldrb	w0, [x1, 3]
.L3212:
	strb	w0, [x1, 3]
	mov	x2, 640
	add	x1, x19, 16
	ldr	x3, [x20, 27896]
	add	x0, x3, 16
	ldr	x4, [x3, 600]
	str	x4, [x29, 104]
	ldp	w26, w25, [x3, 16]
	ldp	w24, w21, [x3, 24]
	ldr	x28, [x3, 608]
	ldr	x27, [x3, 616]
	bl	memcpy
	ldr	x4, [x29, 104]
	cmn	x4, #1
	beq	.L3213
	ldr	x0, [x20, 27896]
	str	x4, [x0, 600]
.L3213:
	ldr	x0, [x19, 608]
	ldr	x1, [x20, 27896]
	cmp	x0, x28
	csel	x0, x0, x28, ls
	str	x0, [x1, 608]
	ldr	x0, [x19, 616]
	ldr	x1, [x20, 27896]
	cmp	x0, x27
	csel	x0, x0, x27, ls
	str	x0, [x1, 616]
	ldr	w0, [x19, 16]
	ldr	x1, [x20, 27896]
	cmp	w0, w26
	csel	w0, w0, w26, ls
	str	w0, [x1, 16]
	ldr	w0, [x19, 20]
	ldr	x1, [x20, 27896]
	cmp	w0, w25
	csel	w0, w0, w25, ls
	str	w0, [x1, 20]
	ldr	w0, [x19, 24]
	ldr	x1, [x20, 27896]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x1, 24]
	ldr	w0, [x19, 28]
	ldr	x1, [x20, 27896]
	cmp	w0, w21
	csel	w0, w0, w21, ls
	str	w0, [x1, 28]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3214
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3214
.L3215:
	ldr	x1, [x20, 27896]
	ldr	w0, [x1, 772]
	ldr	w2, [x1, 820]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	str	w0, [x1, 684]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 684]
	str	w1, [x0, 672]
	ldr	x0, [x20, 27896]
	bl	CombineFldsToFrm
	ldr	x1, [x20, 27896]
	ldr	w0, [x1, 696]
	ldr	w1, [x1, 812]
	add	x0, x0, 4096
	add	x0, x0, 3028
	str	w1, [x23, x0, lsl 2]
	b	.L3203
	.p2align 3
.L3186:
	uxtw	x22, w20
	ldr	x1, [x19, 656]
	mov	w2, 3
	mov	w0, 3
	add	x20, x23, x22, lsl 3
	str	x1, [x20, 27896]
	ldrb	w3, [x19, 2]
	strb	w3, [x1]
	ldr	x1, [x20, 27896]
	strb	w2, [x1, 1]
	ldr	x2, [x19, 656]
	ldr	x1, [x20, 27896]
	ldrb	w2, [x2, 4]
	strb	w2, [x1, 4]
	ldr	x2, [x19, 656]
	ldr	x1, [x20, 27896]
	ldr	w2, [x2, 676]
	str	w2, [x1, 676]
	ldrb	w2, [x19, 4]
	ldr	x1, [x20, 27896]
	cbz	w2, .L3279
.L3188:
	strb	w0, [x1, 2]
	mov	x2, 640
	add	x1, x19, 16
	mov	w21, 3
	ldr	x0, [x20, 27896]
	ldr	w3, [x19, 732]
	str	w3, [x0, 692]
	ldr	x0, [x20, 27896]
	add	x0, x0, 16
	bl	memcpy
	ldr	x0, [x20, 27896]
	mov	w3, 2
	ldr	w1, [x19, 708]
	mov	w6, 1
	str	w1, [x0, 688]
	str	w1, [x0, 720]
	ldr	x0, [x20, 27896]
	ldr	x1, [x19, 656]
	str	x1, [x0, 744]
	str	x1, [x0, 792]
	str	x1, [x0, 840]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 676]
	str	w1, [x0, 668]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 672]
	str	w1, [x0, 660]
	ldr	x0, [x20, 27896]
	strb	wzr, [x0, 704]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 705]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 706]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 700]
	str	w1, [x0, 684]
	str	w1, [x0, 724]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 9]
	str	w1, [x0, 680]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 684]
	str	w1, [x0, 672]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 688]
	str	w1, [x0, 716]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 692]
	str	w1, [x0, 764]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 696]
	str	w1, [x0, 812]
	ldrb	w1, [x19, 7]
	ldr	x0, [x20, 27896]
	cmp	w1, 1
	csel	w21, wzr, w21, ne
	strb	w21, [x0, 3]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 736]
	str	w1, [x0, 736]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 720]
	ldr	x1, [x0, 744]
	ldrb	w5, [x0, 705]
	ldrb	w4, [x0, 706]
	strb	w3, [x0, 800]
	ldr	w3, [x0, 724]
	str	w2, [x0, 768]
	str	x1, [x0, 792]
	str	w2, [x0, 816]
	mov	w2, 0
	strb	w5, [x0, 753]
	strb	w4, [x0, 754]
	strb	w6, [x0, 752]
	strb	w5, [x0, 801]
	strb	w4, [x0, 802]
	str	w3, [x0, 772]
	str	w3, [x0, 820]
	str	x1, [x0, 840]
	mov	x0, x23
	ldr	x1, [x19, 656]
	bl	GetAPC
	cbnz	w0, .L3280
.L3203:
	add	x3, x23, x22, lsl 3
	add	x0, x23, 65536
	mov	w2, 1
	ldr	x1, [x3, 27896]
	ldr	w0, [x0, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetRef
	mov	w0, 0
.L3183:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3277:
	ldr	x1, .LC873
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x23
	bl	ClearAll
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3185:
	ldr	x0, [x19, 656]
	mov	w1, 3
	uxtw	x22, w20
	strb	w1, [x0, 704]
	ldrb	w0, [x19, 1]
	cbz	w0, .L3191
	add	x20, x23, x22, lsl 3
	ldr	x0, [x20, 27896]
	cbz	x0, .L3191
	strb	w21, [x0, 752]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 700]
	str	w1, [x0, 772]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 4]
	strb	w1, [x0, 753]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x19, 5]
	strb	w1, [x0, 754]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 692]
	str	w1, [x0, 764]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 700]
	str	w1, [x0, 772]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 784]
	str	w1, [x0, 784]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 708]
	str	w1, [x0, 768]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 768]
	ldr	w1, [x0, 816]
	add	w1, w2, w1
	str	w1, [x0, 688]
	str	w1, [x0, 720]
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1]
	cbz	w0, .L3196
	ldrb	w0, [x19, 2]
.L3196:
	strb	w0, [x1]
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1, 1]
	orr	w0, w0, 1
	strb	w0, [x1, 1]
	ldrb	w0, [x19, 7]
	ldr	x1, [x20, 27896]
	cmp	w0, 1
	beq	.L3281
	ldrb	w0, [x1, 3]
.L3198:
	strb	w0, [x1, 3]
	mov	x2, 640
	add	x1, x19, 16
	ldr	x3, [x20, 27896]
	add	x0, x3, 16
	ldr	x4, [x3, 600]
	str	x4, [x29, 104]
	ldp	w26, w25, [x3, 16]
	ldp	w24, w21, [x3, 24]
	ldr	x28, [x3, 608]
	ldr	x27, [x3, 616]
	bl	memcpy
	ldr	x0, [x19, 600]
	ldr	x4, [x29, 104]
	cmn	x0, #1
	ccmn	x4, #1, 4, eq
	beq	.L3199
	ldr	x0, [x20, 27896]
	str	x4, [x0, 600]
.L3199:
	ldr	x0, [x19, 608]
	ldr	x1, [x20, 27896]
	cmp	x0, x28
	csel	x0, x0, x28, ls
	str	x0, [x1, 608]
	ldr	x0, [x19, 616]
	ldr	x1, [x20, 27896]
	cmp	x0, x27
	csel	x0, x0, x27, ls
	str	x0, [x1, 616]
	ldr	w0, [x19, 16]
	ldr	x1, [x20, 27896]
	cmp	w0, w26
	csel	w0, w0, w26, ls
	str	w0, [x1, 16]
	ldr	w0, [x19, 20]
	ldr	x1, [x20, 27896]
	cmp	w0, w25
	csel	w0, w0, w25, ls
	str	w0, [x1, 20]
	ldr	w0, [x19, 24]
	ldr	x1, [x20, 27896]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x1, 24]
	ldr	w0, [x19, 28]
	ldr	x1, [x20, 27896]
	cmp	w0, w21
	csel	w0, w0, w21, ls
	str	w0, [x1, 28]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3200
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3200
.L3201:
	ldr	x1, [x20, 27896]
	ldr	w0, [x1, 772]
	ldr	w2, [x1, 820]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	str	w0, [x1, 684]
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 684]
	str	w1, [x0, 672]
	ldr	x0, [x20, 27896]
	bl	CombineFldsToFrm
	ldr	x1, [x20, 27896]
	ldr	w0, [x1, 696]
	ldr	w1, [x1, 764]
	add	x0, x0, 4096
	add	x0, x0, 3012
	str	w1, [x23, x0, lsl 2]
	b	.L3203
	.p2align 3
.L3191:
	add	x20, x23, x22, lsl 3
	ldr	x0, [x19, 656]
	mov	w1, 1
	str	x0, [x20, 27896]
	strb	w1, [x0, 752]
	ldr	x0, [x20, 27896]
	ldr	x2, [x19, 656]
	str	x2, [x0, 792]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 4]
	strb	w2, [x0, 753]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 5]
	strb	w2, [x0, 754]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 692]
	str	w2, [x0, 764]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 700]
	str	w2, [x0, 772]
	ldr	x2, [x19, 656]
	ldr	x0, [x20, 27896]
	ldr	w2, [x2, 784]
	str	w2, [x0, 784]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 708]
	str	w2, [x0, 768]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 768]
	str	w2, [x0, 688]
	str	w2, [x0, 720]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 2]
	strb	w2, [x0]
	ldr	x0, [x20, 27896]
	strb	w1, [x0, 1]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x1, 4]
	strb	w1, [x0, 4]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 676]
	str	w1, [x0, 676]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3193
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3193
.L3194:
	ldr	x0, [x20, 27896]
	mov	x2, 640
	add	x1, x19, 16
	str	wzr, [x0, 680]
	ldr	x0, [x20, 27896]
	add	x0, x0, 16
	bl	memcpy
	ldr	x1, [x20, 27896]
	mov	w2, 1
	ldr	w3, [x19, 732]
	mov	x0, x23
	str	w3, [x1, 692]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 672]
	str	w3, [x1, 660]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 684]
	str	w3, [x1, 672]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 700]
	str	w3, [x1, 684]
	ldrb	w3, [x19, 7]
	ldr	x1, [x20, 27896]
	cmp	w3, w2
	cset	w3, eq
	strb	w3, [x1, 3]
	ldr	x1, [x19, 656]
	bl	GetAPC
	cbz	w0, .L3203
	ldr	x1, .LC871
	mov	w3, w0
	mov	w2, 2707
	b	.L3274
	.p2align 3
.L3204:
	add	x20, x23, x22, lsl 3
	ldr	x0, [x19, 656]
	mov	w1, 2
	str	x0, [x20, 27896]
	strb	w1, [x0, 800]
	ldr	x0, [x20, 27896]
	ldr	x2, [x19, 656]
	str	x2, [x0, 840]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 4]
	strb	w2, [x0, 801]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 5]
	strb	w2, [x0, 802]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 696]
	str	w2, [x0, 812]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 700]
	str	w2, [x0, 820]
	ldr	x2, [x19, 656]
	ldr	x0, [x20, 27896]
	ldr	w2, [x2, 832]
	str	w2, [x0, 832]
	ldr	x0, [x20, 27896]
	ldr	w2, [x19, 708]
	str	w2, [x0, 816]
	ldr	x0, [x20, 27896]
	ldr	w2, [x0, 768]
	str	w2, [x0, 688]
	str	w2, [x0, 720]
	ldr	x0, [x20, 27896]
	ldrb	w2, [x19, 2]
	strb	w2, [x0]
	ldr	x0, [x20, 27896]
	strb	w1, [x0, 1]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 27896]
	ldrb	w1, [x1, 4]
	strb	w1, [x0, 4]
	ldr	x1, [x19, 656]
	ldr	x0, [x20, 27896]
	ldr	w1, [x1, 676]
	str	w1, [x0, 676]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	beq	.L3206
	ldrb	w0, [x19, 5]
	cmp	w0, 1
	beq	.L3206
.L3207:
	ldr	x0, [x20, 27896]
	mov	x2, 640
	add	x1, x19, 16
	str	wzr, [x0, 680]
	ldr	x0, [x20, 27896]
	add	x0, x0, 16
	bl	memcpy
	ldr	x1, [x20, 27896]
	mov	w2, 2
	ldr	w3, [x19, 732]
	mov	x0, x23
	str	w3, [x1, 692]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 672]
	str	w3, [x1, 660]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 684]
	str	w3, [x1, 672]
	ldr	x1, [x20, 27896]
	ldr	w3, [x19, 700]
	str	w3, [x1, 684]
	str	w3, [x1, 820]
	ldrb	w3, [x19, 7]
	ldr	x1, [x20, 27896]
	cmp	w3, 1
	csel	w21, w21, wzr, eq
	strb	w21, [x1, 3]
	ldr	x1, [x19, 656]
	bl	GetAPC
	cbz	w0, .L3203
	ldr	x1, .LC871
	mov	w3, w0
	mov	w2, 2830
.L3274:
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, x23
	bl	ClearDPB
	mov	w0, -1
	b	.L3183
	.p2align 3
.L3279:
	ldrb	w0, [x19, 5]
	mov	w2, 3
	cmp	w0, wzr
	csel	w0, w0, w2, eq
	b	.L3188
	.p2align 3
.L3206:
	ldr	x0, [x20, 27896]
	mov	w1, 2
	strb	w1, [x0, 2]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3207
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 676]
	str	w1, [x0, 668]
	b	.L3207
	.p2align 3
.L3193:
	ldr	x0, [x20, 27896]
	mov	w1, 1
	strb	w1, [x0, 2]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3194
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 676]
	str	w1, [x0, 668]
	b	.L3194
	.p2align 3
.L3214:
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 2
	strb	w0, [x1, 2]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3215
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 676]
	str	w1, [x0, 668]
	b	.L3215
	.p2align 3
.L3200:
	ldr	x1, [x20, 27896]
	ldrb	w0, [x1, 2]
	orr	w0, w0, 1
	strb	w0, [x1, 2]
	ldrb	w0, [x19, 4]
	cmp	w0, 1
	bne	.L3201
	ldr	x0, [x20, 27896]
	ldr	w1, [x19, 676]
	str	w1, [x0, 668]
	b	.L3201
	.p2align 3
.L3278:
	ldrb	w0, [x1, 3]
	orr	w0, w0, 2
	uxtb	w0, w0
	b	.L3212
	.p2align 3
.L3281:
	ldrb	w0, [x1, 3]
	orr	w0, w0, 1
	uxtb	w0, w0
	b	.L3198
	.p2align 3
.L3276:
	ldr	x1, .LC869
	mov	w3, w20
	mov	w2, 2613
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3183
.L3280:
	ldr	x1, .LC871
	mov	w3, w0
	mov	w2, 2652
	b	.L3274
	.size	InsertFrmInDPB, .-InsertFrmInDPB
	.align	3
.LC869:
	.xword	.LC868
	.align	3
.LC871:
	.xword	.LC870
	.align	3
.LC873:
	.xword	.LC872
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecVDM
	.type	DecVDM, %function
DecVDM:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	cbz	x22, .L3372
	add	x21, x22, 61440
	ldrb	w0, [x21, 2027]
	cbnz	w0, .L3373
.L3285:
	add	x19, x22, 65536
	ldr	w0, [x19, 2004]
	ldr	w1, [x19, 2008]
	add	w0, w0, 1
	cmp	w0, w1
	csel	w0, w0, w1, ge
	str	w0, [x19, 2004]
	sub	w0, w0, w1
	ldr	x1, [x22]
	str	w0, [x1, 624]
.L3286:
	ldr	w20, [x19, 1968]
	ldr	w0, [x19, 1908]
	ubfx	x20, x20, 16, 3
	cmp	w20, w0
	beq	.L3287
	sub	w0, w0, #2
	cmp	w0, 1
	ccmp	w20, 2, 4, ls
	beq	.L3287
	cmp	w20, 1
	ccmp	w20, 4, 4, hi
	beq	.L3374
.L3287:
	cmp	w20, 2
	str	w20, [x19, 1908]
	beq	.L3289
	cmp	w20, 3
	beq	.L3290
	cmp	w20, 1
	beq	.L3375
	ldr	w0, [x19, 1904]
	cbz	w0, .L3293
	cmp	w20, 4
	ldr	w0, [x21, 2724]
	bne	.L3300
	cbnz	w0, .L3300
	ldr	w0, [x19, 656]
	cbnz	w0, .L3301
	mov	w0, 2
	str	w0, [x19, 656]
	b	.L3313
	.p2align 3
.L3373:
	ldrb	w0, [x21, 2025]
	add	x19, x22, 65536
	cmp	w0, 1
	bne	.L3286
	b	.L3285
.L3374:
	ldr	x1, .LC877
	mov	w2, w20
	mov	w0, 2
	bl	dprint_vfmw
	str	w20, [x19, 1908]
	.p2align 2
.L3290:
	mov	x0, x22
	bl	H264_ClearCurrPic
	mov	x0, x22
	bl	ClearDPB
	mov	w0, -1
.L3366:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3289:
	ldr	w0, [x21, 2724]
	cbnz	w0, .L3296
	ldr	w0, [x19, 1904]
	cbz	w0, .L3293
	ldr	x0, [x19, 1896]
	ldr	w0, [x0, 48]
	cbz	w0, .L3313
	mov	w1, 1
	mov	x0, x22
	strb	w1, [x21, 2031]
	bl	H264_ClearCurrPic
	ldr	x1, .LC879
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3366
	.p2align 3
.L3293:
	mov	x0, x22
	bl	H264_ClearCurrPic
	ldr	x0, .LC880
	ldr	x4, [x0]
	cbz	x4, .L3370
	ldr	w0, [x19, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3375:
	ldr	w0, [x21, 2724]
	cmp	w0, 2
	beq	.L3376
	ldr	w1, [x19, 1904]
	cbz	w1, .L3293
.L3302:
	cmp	w0, 1
	bne	.L3313
	str	w0, [x19, 656]
.L3313:
	ldr	w2, [x19, 1944]
	mov	w0, 2
	ldr	x1, .LC885
	ldrb	w3, [x21, 2027]
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	w0, [x21, 2748]
	str	w0, [x19, 1444]
	mov	w0, 1
	strb	w0, [x19, 706]
	ldr	w2, [x19, 1904]
	ldr	w1, [x21, 2752]
	ldr	w0, [x19, 1944]
	str	w1, [x19, 1440]
	str	w2, [x19, 1644]
	cbz	w0, .L3304
	ldr	w4, [x21, 2724]
	cbnz	w4, .L3305
	ldr	x0, .LC880
	ldr	x5, [x0]
	cbz	x5, .L3306
	ldr	x1, [x19, 1648]
	cbz	x1, .L3307
	mov	w2, 0
	.p2align 2
.L3308:
	ldp	w3, w0, [x1, 8]
	ldr	x1, [x1, 4056]
	add	w0, w3, w0
	add	w0, w0, 7
	add	w2, w2, w0, lsr 3
	mov	w4, w2
	cbnz	x1, .L3308
.L3307:
	add	x2, x29, 64
	ldr	w0, [x19, 1980]
	mov	w1, 20
	mov	w3, 4
	str	w4, [x2, -8]!
	blr	x5
	ldr	x1, [x22]
.L3309:
	add	x2, x19, 704
	str	x2, [x22, 616]
	ldr	w0, [x1, 952]
	cmp	w0, 1
	beq	.L3377
	cmp	w0, 2
	beq	.L3378
.L3312:
	ldr	w2, [x1, 640]
	mov	w0, 0
	strb	w2, [x19, 708]
	ldr	w2, [x1, 648]
	str	w2, [x19, 712]
	ldr	w2, [x1, 652]
	str	w2, [x19, 716]
	ldr	w2, [x1, 644]
	strb	w2, [x19, 709]
	ldr	w1, [x1, 692]
	strb	w1, [x19, 720]
	ldr	w4, [x21, 2764]
	ldr	x3, [x21, 2680]
	ldr	w1, [x21, 2760]
	str	w4, [x21, 2760]
	sub	w1, w1, w4
	ldr	w2, [x3, 256]
	add	w2, w2, w1
	str	w2, [x3, 256]
	ldr	w2, [x21, 2280]
	add	w1, w2, w1
	str	w1, [x21, 2280]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L3376:
	ldr	w0, [x21, 2704]
	cbz	w0, .L3296
	ldr	w0, [x19, 1904]
	cbz	w0, .L3293
.L3314:
	ldr	w0, [x19, 656]
	cmp	w0, 2
	bne	.L3313
	ldr	x0, [x22]
	ldr	w0, [x0, 24]
	cbnz	w0, .L3313
	ldr	x0, .LC881
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L3313
	ldr	x1, .LC883
	mov	w0, 1
	ldr	w3, [x21, 2704]
	ldr	w2, [x21, 2708]
	bl	dprint_vfmw
	mov	x0, x22
	bl	H264_ClearCurrPic
	ldr	x0, .LC880
	ldr	x4, [x0]
	cbz	x4, .L3303
	ldr	w0, [x19, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3303:
	ldr	x1, [x21, 2680]
	mov	w2, 0
	ldr	w0, [x19, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetDisplay
	mov	w0, -1
	b	.L3366
	.p2align 3
.L3305:
	add	x0, x22, 24576
	ldr	w0, [x0, 3708]
	cbnz	w0, .L3306
	ldr	x1, [x22]
	ldr	w0, [x1, 24]
	cmp	w0, 2
	beq	.L3309
	ldr	x0, .LC880
	ldr	x4, [x0]
	cbz	x4, .L3369
	ldr	w0, [x19, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 127
	blr	x4
.L3369:
	mov	x0, x22
	bl	H264_ClearCurrPic
	.p2align 2
.L3370:
	mov	w0, -1
	b	.L3366
	.p2align 3
.L3300:
	cmp	w0, 2
	beq	.L3314
	b	.L3302
	.p2align 3
.L3304:
	ldr	x1, [x22]
	b	.L3312
	.p2align 3
.L3306:
	ldr	x1, [x22]
	b	.L3309
	.p2align 3
.L3377:
	cbz	x2, .L3312
	ldr	w0, [x21, 2724]
	cmp	w0, 2
	bne	.L3312
	str	xzr, [x22, 616]
	mov	w2, 0
	ldr	x1, [x21, 2680]
	ldr	w0, [x19, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetDisplay
	b	.L3369
	.p2align 3
.L3378:
	ldr	w0, [x1, 956]
	cmp	w0, wzr
	ccmp	x2, xzr, 4, gt
	beq	.L3312
	ldr	w0, [x21, 2724]
	cmp	w0, 2
	bne	.L3312
	str	xzr, [x22, 616]
	mov	w2, 0
	ldr	x1, [x21, 2680]
	ldr	w0, [x19, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetDisplay
	ldr	x2, [x22]
	mov	x0, x22
	ldr	w1, [x2, 956]
	sub	w1, w1, #1
	str	w1, [x2, 956]
	bl	H264_ClearCurrPic
	mov	w0, -1
	b	.L3366
	.p2align 3
.L3301:
	mov	w0, 1
	str	w0, [x19, 656]
	b	.L3313
.L3296:
	mov	w1, 1
	mov	x0, x22
	strb	w1, [x21, 2031]
	bl	H264_ClearCurrPic
	mov	w0, -1
	b	.L3366
.L3372:
	ldr	x2, .LC874
	mov	w3, 7489
	ldr	x1, .LC875
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3366
	.size	DecVDM, .-DecVDM
	.align	3
.LC874:
	.xword	.LC30
	.align	3
.LC875:
	.xword	.LC32
	.align	3
.LC877:
	.xword	.LC876
	.align	3
.LC879:
	.xword	.LC878
	.align	3
.LC880:
	.xword	g_event_report
	.align	3
.LC881:
	.xword	g_allow_B_before_P
	.align	3
.LC883:
	.xword	.LC882
	.align	3
.LC885:
	.xword	.LC884
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_FlushDecoder
	.type	H264_FlushDecoder, %function
H264_FlushDecoder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L3385
	add	x1, x19, 20480
	mov	w2, 1
	mov	w20, 1
	mov	x0, x19
	strb	w2, [x1, 1589]
	str	wzr, [x1, 1632]
	str	w20, [x19, 624]
	bl	DecVDM
	cbz	w0, .L3379
	ldr	x1, .LC889
	mov	w0, w20
	bl	dprint_vfmw
.L3379:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3385:
	ldr	x2, .LC886
	mov	w3, 11768
	ldr	x1, .LC887
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	H264_FlushDecoder, .-H264_FlushDecoder
	.align	3
.LC886:
	.xword	.LC30
	.align	3
.LC887:
	.xword	.LC32
	.align	3
.LC889:
	.xword	.LC888
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_VES_Splitter
	.type	H264_VES_Splitter, %function
H264_VES_Splitter:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 12288
	mov	w20, w1
	mov	w23, w2
	mov	w24, w3
	add	x19, x19, 2600
	bl	_mcount
	add	x22, x21, 61440
	mov	w1, 24
	mov	x0, x19
	str	xzr, [x29, 72]
	bl	BsSkip
	ldr	x0, [x22, 2472]
	str	x0, [x29, 72]
	cbz	w20, .L3388
	cmp	w20, 1
	bne	.L3493
	cmp	w23, 1
	mov	w1, 16
	mov	x0, x19
	beq	.L3494
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	mov	w1, 31745
	cmp	w20, w1
	beq	.L3410
	mov	w1, 24
	mov	x0, x19
	bl	BsBack
	mov	w1, 24
	mov	x0, x19
	bl	BsBack
	mov	w0, 32257
	cmp	w20, w0
	beq	.L3495
.L3476:
	mov	w0, 0
.L3497:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3493:
	ldr	x1, .LC903
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L3473:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3388:
	cmp	w23, 1
	beq	.L3496
	mov	w1, 24
	mov	x0, x19
	bl	BsBack
	mov	w0, 0
	b	.L3497
	.p2align 3
.L3410:
	and	w0, w0, 31
	cmp	w0, 25
	bne	.L3476
	ldr	x19, .LC890
	ldr	x4, [x19]
	cbz	x4, .L3412
	add	x0, x21, 65536
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	ldr	w0, [x0, 1980]
	blr	x4
.L3412:
	mov	x0, x21
	bl	DecVDM
	cbz	w0, .L3413
.L3483:
	ldr	x4, [x19]
	cbz	x4, .L3477
	add	x21, x21, 65536
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	ldr	w0, [x21, 1980]
	blr	x4
	mov	w0, -1
	b	.L3473
	.p2align 3
.L3495:
	ldr	x2, .LC891
	mov	w3, 12971
	ldr	x1, .LC901
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	.p2align 2
.L3486:
	ldr	x1, [x21, 632]
	cbz	x1, .L3477
	add	x0, x21, 65536
	ldr	w0, [x0, 1980]
	bl	ReleaseNAL
	str	xzr, [x21, 632]
.L3477:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3496:
	mov	w1, 16
	mov	x0, x19
	mov	w23, 31745
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	cmp	w20, w23
	beq	.L3391
	mov	w1, 24
	mov	x0, x19
	and	w20, w20, -513
	bl	BsBack
	mov	w1, 24
	mov	x0, x19
	bl	BsBack
	cmp	w20, w23
	beq	.L3486
	mov	w0, 0
	b	.L3497
	.p2align 3
.L3494:
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	mov	w1, 31745
	cmp	w20, w1
	beq	.L3403
	mov	w1, 32
	mov	x0, x19
	bl	BsBack
	ldr	x0, [x21, 632]
	mov	w2, 32257
	mov	w1, 16
	cmp	w20, w2
	str	w1, [x0, 72]
	beq	.L3498
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	and	w0, w0, 31
	cmp	w0, 11
	bne	.L3486
	mov	x0, x21
	bl	H264_IsEosNal
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L3486
	ldr	x1, [x21, 632]
	mov	x0, x19
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	mov	w0, 3
	b	.L3473
	.p2align 3
.L3391:
	and	w0, w0, 31
	cmp	w0, 25
	bne	.L3486
	ldr	x19, .LC890
	ldr	x4, [x19]
	cbz	x4, .L3394
	add	x0, x21, 65536
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	ldr	w0, [x0, 1980]
	blr	x4
.L3394:
	mov	x0, x21
	bl	DecVDM
	cbnz	w0, .L3483
	ldr	x0, [x21, 632]
	add	x23, x22, 2456
	add	x20, x21, 65536
	ldr	w1, [x23, 8]
	add	x2, x29, 72
	ldr	w4, [x0, 16]
	ldr	w3, [x0, 48]
	ldr	w0, [x20, 1980]
	add	w3, w4, w3
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L3499
	ldr	x19, .LC894
	mov	x2, 5
	ldr	x1, .LC895
	ldr	x0, [x29, 72]
	ldr	x3, [x19, 104]
	blr	x3
	ldr	x1, [x21, 632]
	ldr	x0, [x29, 72]
	ldr	x3, [x19, 104]
	ldr	w2, [x1, 16]
	add	x0, x0, 5
	sub	w2, w2, #6
	str	w2, [x23, 4]
	ldr	x1, [x1, 8]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x23, 4]
	add	w0, w0, 5
	str	w0, [x23, 4]
	ldr	x1, [x21, 632]
	ldr	w2, [x1, 48]
	cbnz	w2, .L3500
.L3398:
	ldr	x23, .LC896
	ldr	w0, [x20, 1980]
	ldr	x1, [x23, w0, sxtw 3]
	cbz	x1, .L3399
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x20, 1980]
	ldr	w1, [x22, 2460]
	ldr	x3, [x19, 88]
	ldr	x2, [x23, x2, lsl 3]
	ldr	x0, [x29, 72]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x20, 1980]
.L3399:
	ldr	x1, [x29, 72]
	bl	MetadataUnMapToSec
	cbnz	w0, .L3501
.L3417:
	ldr	x1, [x21, 632]
	cbz	x1, .L3477
	ldr	w0, [x20, 1980]
	bl	ReleaseNAL
	str	xzr, [x21, 632]
	mov	w0, -1
	b	.L3473
	.p2align 3
.L3403:
	and	w0, w0, 31
	cmp	w0, 25
	ccmp	w24, 2, 0, eq
	bne	.L3486
	ldr	x19, .LC890
	ldr	x4, [x19]
	cbz	x4, .L3406
	add	x0, x21, 65536
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	ldr	w0, [x0, 1980]
	blr	x4
.L3406:
	mov	x0, x21
	bl	DecVDM
	cbz	w0, .L3486
	b	.L3483
	.p2align 3
.L3498:
	add	x22, x21, 65536
	ldr	x20, .LC899
	ldrsw	x0, [x22, 1980]
	ldr	x0, [x20, x0, lsl 3]
	cbz	x0, .L3476
	ldr	x19, .LC894
	mov	w0, 0
	ldr	x1, [x19, 32]
	blr	x1
	ldr	x0, [x21, 632]
	ldrsw	x2, [x22, 1980]
	ldr	x3, [x19, 88]
	ldr	w1, [x0, 16]
	ldr	x2, [x20, x2, lsl 3]
	ldr	x0, [x0, 8]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	mov	w0, 0
	b	.L3473
	.p2align 3
.L3413:
	ldr	x0, [x21, 632]
	add	x23, x22, 2456
	add	x20, x21, 65536
	ldr	w1, [x23, 8]
	add	x2, x29, 72
	ldr	w4, [x0, 16]
	ldr	w3, [x0, 48]
	ldr	w0, [x20, 1980]
	add	w3, w4, w3
	sub	w3, w3, #1
	bl	MetadataMapToSec
	cbnz	w0, .L3502
	ldr	x19, .LC894
	mov	x2, 5
	ldr	x1, .LC895
	ldr	x0, [x29, 72]
	ldr	x3, [x19, 104]
	blr	x3
	ldr	x1, [x21, 632]
	ldr	x0, [x29, 72]
	ldr	x3, [x19, 104]
	ldr	w2, [x1, 16]
	add	x0, x0, 5
	sub	w2, w2, #6
	str	w2, [x23, 4]
	ldr	x1, [x1, 8]
	add	x1, x1, 6
	blr	x3
	ldr	w0, [x23, 4]
	add	w0, w0, 5
	str	w0, [x23, 4]
	ldr	x1, [x21, 632]
	ldr	w2, [x1, 48]
	cbnz	w2, .L3503
.L3415:
	ldr	x23, .LC896
	ldr	w0, [x20, 1980]
	ldr	x1, [x23, w0, sxtw 3]
	cbz	x1, .L3416
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldrsw	x2, [x20, 1980]
	ldr	w1, [x22, 2460]
	ldr	x3, [x19, 88]
	ldr	x2, [x23, x2, lsl 3]
	ldr	x0, [x29, 72]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	ldr	w0, [x20, 1980]
.L3416:
	ldr	x1, [x29, 72]
	bl	MetadataUnMapToSec
	cbz	w0, .L3417
	ldr	x2, .LC891
	mov	w3, 12959
	ldr	x1, .LC898
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3473
	.p2align 3
.L3503:
	ldr	x4, [x29, 72]
	uxtw	x2, w2
	ldr	x1, [x1, 40]
	ldr	x3, [x19, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x21, 632]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 48]
	add	w0, w1, w0
	str	w0, [x23, 4]
	b	.L3415
.L3500:
	ldr	x4, [x29, 72]
	uxtw	x2, w2
	ldr	x1, [x1, 40]
	ldr	x3, [x19, 104]
	add	x0, x4, x0, uxtw
	blr	x3
	ldr	x1, [x21, 632]
	ldr	w0, [x23, 4]
	ldr	w1, [x1, 48]
	add	w0, w1, w0
	str	w0, [x23, 4]
	b	.L3398
.L3502:
	ldr	x2, .LC891
	mov	w3, 12929
	ldr	x1, .LC893
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3473
.L3499:
	ldr	x2, .LC891
	mov	w3, 12768
	ldr	x1, .LC893
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3473
.L3501:
	ldr	x2, .LC891
	mov	w3, 12802
	ldr	x1, .LC898
	mov	w0, 0
	add	x2, x2, 272
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3473
	.size	H264_VES_Splitter, .-H264_VES_Splitter
	.align	3
.LC890:
	.xword	g_event_report
	.align	3
.LC891:
	.xword	.LANCHOR2
	.align	3
.LC893:
	.xword	.LC892
	.align	3
.LC894:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC895:
	.xword	g_RpuStartCode
	.align	3
.LC896:
	.xword	vfmw_save_metadata_file
	.align	3
.LC898:
	.xword	.LC897
	.align	3
.LC899:
	.xword	vfmw_save_el_file
	.align	3
.LC901:
	.xword	.LC900
	.align	3
.LC903:
	.xword	.LC902
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReceivePacket
	.type	ReceivePacket, %function
ReceivePacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 65536
	bl	_mcount
	ldr	x1, .LC905
	mov	w0, 7
	ldp	w3, w4, [x19, 16]
	ldr	x2, [x19, 8]
	bl	dprint_vfmw
	str	wzr, [x21, 2012]
	ldr	x0, [x20]
	ldr	w1, [x0, 912]
	cmp	w1, 1
	beq	.L3576
.L3505:
	ldr	x0, [x20, 632]
	cbz	x0, .L3510
	ldrb	w1, [x19]
	cmp	w1, 1
	beq	.L3577
.L3508:
	ldr	x1, .LC907
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L3510
	ldr	w0, [x21, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L3510:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L3512
	ldr	x0, [x19, 8]
	cbz	x0, .L3512
	ldr	w0, [x19, 16]
	cbz	w0, .L3512
	cbz	x20, .L3518
	ldrb	w0, [x20, 641]
	cbz	w0, .L3534
	add	x1, x20, 745
	mov	x0, 1
	b	.L3517
	.p2align 3
.L3516:
	add	w0, w0, 1
	cmp	w0, 137
	beq	.L3518
.L3517:
	ldrb	w2, [x1]
	add	x1, x1, 104
	cbnz	w2, .L3516
	mov	w2, w0
.L3515:
	lsl	x1, x0, 3
	mov	w3, 1
	sub	x1, x1, x0
	cmn	w2, #1
	lsl	x1, x1, x3
	sub	x0, x1, x0
	add	x0, x20, x0, lsl 3
	strb	w3, [x0, 641]
	beq	.L3518
	sxtw	x1, w2
	mov	w2, 1
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	lsl	x0, x0, 3
	add	x1, x0, 640
	add	x0, x20, x0
	add	x1, x20, x1
	str	x1, [x20, 632]
	ldr	x1, [x19, 8]
	str	x1, [x0, 648]
	ldr	w1, [x19, 20]
	str	w1, [x0, 656]
	ldr	w1, [x19, 16]
	str	w1, [x0, 660]
	ldr	x0, [x20, 632]
	str	wzr, [x0, 28]
	ldr	x0, [x20, 632]
	ldr	w1, [x19, 24]
	str	w1, [x0, 36]
	ldr	x0, [x20, 632]
	ldr	x1, [x19, 32]
	str	x1, [x0, 96]
	ldr	x0, [x20, 632]
	str	w2, [x0, 76]
	ldr	x0, [x20, 632]
	strb	wzr, [x0]
	ldr	x0, [x20, 632]
	ldrb	w1, [x19]
	strb	w1, [x0, 4]
	ldr	x0, [x20]
	ldrb	w0, [x0, 984]
	cmp	w0, w2
	beq	.L3573
	add	x0, x20, 61440
	ldr	w2, [x19, 20]
	ldr	w1, [x0, 2760]
	ldr	w3, [x0, 2764]
	add	w2, w1, w2
	str	w2, [x0, 2760]
	ldr	w1, [x19, 20]
	add	w1, w3, w1
	str	w1, [x0, 2764]
	ldr	x0, [x20, 632]
	b	.L3523
	.p2align 3
.L3577:
	ldr	w2, [x0, 76]
	cmp	w2, 1
	bhi	.L3508
	ldrb	w2, [x0, 4]
	cmp	w2, 1
	bne	.L3509
	b	.L3508
	.p2align 3
.L3576:
	ldr	w0, [x0, 960]
	cbz	w0, .L3505
	ldr	x0, [x20, 632]
	cbz	x0, .L3510
	ldrb	w1, [x19]
.L3509:
	strb	w1, [x0, 4]
	ldr	x0, [x20]
	ldr	w1, [x0, 912]
	cmp	w1, 1
	beq	.L3578
.L3525:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L3526
	ldr	x1, [x19, 8]
	cbz	x1, .L3526
	ldr	w0, [x19, 16]
	cbz	w0, .L3526
	ldr	x0, [x20, 632]
	ldr	w2, [x0, 76]
	cmp	w2, 1
	bls	.L3579
.L3527:
	mov	w1, 1
	strb	w1, [x0, 4]
	ldr	w1, [x19, 24]
	ldr	w0, [x21, 1980]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC910
	ldr	x4, [x0]
	cbz	x4, .L3573
	ldr	w0, [x21, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3573:
	ldr	x0, [x20, 632]
.L3523:
	ldrb	w0, [x0, 4]
	ldp	x19, x20, [sp, 16]
	cmp	w0, wzr
	csetm	w0, eq
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3512:
	ldr	x1, .LC912
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w1, [x19, 24]
	ldr	w0, [x21, 1980]
	bl	SM_ReleaseStreamSeg
	ldr	x0, .LC910
	ldr	x4, [x0]
	cbz	x4, .L3575
.L3574:
	ldr	w0, [x21, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L3575:
	mov	w0, -1
.L3582:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3526:
	ldr	x0, [x20, 632]
	b	.L3527
	.p2align 3
.L3578:
	ldr	w0, [x0, 960]
	cbnz	w0, .L3573
	b	.L3525
	.p2align 3
.L3579:
	ubfiz	x2, x2, 5, 32
	add	x0, x0, x2
	str	x1, [x0, 8]
	ldr	x1, [x20, 632]
	ldr	w2, [x19, 20]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 16]
	ldr	x1, [x20, 632]
	ldr	w2, [x19, 16]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 20]
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	wzr, [x0, 28]
	ldr	x1, [x20, 632]
	ldr	w2, [x19, 24]
	ldr	w0, [x1, 76]
	add	x0, x1, x0, lsl 5
	str	w2, [x0, 36]
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 76]
	add	w0, w0, 1
	str	w0, [x1, 76]
	ldr	x0, [x20]
	ldrb	w0, [x0, 984]
	cmp	w0, 1
	beq	.L3528
	add	x0, x20, 61440
	ldr	w2, [x19, 20]
	ldr	w1, [x0, 2760]
	ldr	w3, [x0, 2764]
	add	w2, w1, w2
	str	w2, [x0, 2760]
	ldr	w1, [x19, 20]
	add	w1, w3, w1
	str	w1, [x0, 2764]
.L3528:
	ldr	x0, [x20, 632]
	cbz	x20, .L3530
	ldr	w1, [x0, 16]
	cmp	w1, 4095
	bls	.L3580
.L3530:
	mov	w1, 1
	str	w1, [x21, 2012]
	b	.L3523
	.p2align 3
.L3580:
	mov	x0, x20
	bl	CombinePacket.part.17
	ldr	x0, [x20, 632]
	b	.L3530
	.p2align 3
.L3518:
	ldr	x1, .LC909
	mov	w0, 0
	add	x22, x20, 12288
	add	x19, x20, 640
	add	x22, x22, 2600
	bl	dprint_vfmw
	b	.L3514
	.p2align 3
.L3519:
	add	x19, x19, 104
	cmp	x22, x19
	beq	.L3581
.L3514:
	ldrb	w0, [x19, 1]
	cmp	w0, 1
	bne	.L3519
	ldr	w0, [x21, 1980]
	mov	x1, x19
	bl	ReleaseNAL
	b	.L3519
.L3581:
	mov	x0, x20
	bl	H264_ClearCurrPic
	mov	x0, x20
	bl	ClearDPB
	ldr	x0, .LC910
	ldr	x4, [x0]
	cbnz	x4, .L3574
	mov	w0, -1
	b	.L3582
.L3534:
	mov	w2, 0
	mov	x0, 0
	b	.L3515
	.size	ReceivePacket, .-ReceivePacket
	.align	3
.LC905:
	.xword	.LC904
	.align	3
.LC907:
	.xword	.LC906
	.align	3
.LC909:
	.xword	.LC908
	.align	3
.LC910:
	.xword	g_event_report
	.align	3
.LC912:
	.xword	.LC911
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DirectOutput
	.type	DirectOutput, %function
DirectOutput:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 61440
	bl	_mcount
	ldrb	w0, [x19, 2027]
	cmp	w0, 1
	beq	.L3585
	cbz	w0, .L3586
	cmp	w0, 2
	beq	.L3587
	mov	w21, 0
.L3584:
	mov	w0, w21
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3587:
	ldr	x0, [x19, 2680]
	mov	w1, 3
	strb	w1, [x0, 704]
	ldrb	w0, [x19, 2025]
	cbz	w0, .L3669
	ldr	x0, [x19, 3544]
	cbz	x0, .L3670
.L3609:
	ldr	x27, [x0, 600]
	mov	x2, 640
	ldp	w24, w23, [x0, 16]
	ldp	w22, w21, [x0, 24]
	ldr	x26, [x0, 608]
	add	x1, x19, 2040
	ldr	x25, [x0, 616]
	add	x0, x0, 16
	bl	memcpy
	cmn	x27, #1
	beq	.L3610
	ldr	x0, [x19, 3544]
	str	x27, [x0, 600]
.L3610:
	ldr	x0, [x19, 2632]
	ldr	x1, [x19, 3544]
	cmp	x0, x26
	csel	x0, x0, x26, ls
	str	x0, [x1, 608]
	ldr	x0, [x19, 2640]
	ldr	x1, [x19, 3544]
	cmp	x0, x25
	csel	x0, x0, x25, ls
	str	x0, [x1, 616]
	ldr	w0, [x19, 2040]
	ldr	x1, [x19, 3544]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x1, 16]
	ldr	w0, [x19, 2044]
	ldr	x1, [x19, 3544]
	cmp	w0, w23
	csel	w0, w0, w23, ls
	str	w0, [x1, 20]
	ldr	w0, [x19, 2048]
	ldr	x1, [x19, 3544]
	cmp	w0, w22
	csel	w0, w0, w22, ls
	str	w0, [x1, 24]
	ldr	w0, [x19, 2052]
	ldr	x1, [x19, 3544]
	cmp	w0, w21
	csel	w0, w0, w21, ls
	str	w0, [x1, 28]
	ldr	x1, [x19, 3544]
	ldrb	w0, [x1]
	cbz	w0, .L3611
	ldrb	w0, [x19, 2026]
.L3611:
	strb	w0, [x1]
	mov	w4, 2
	mov	w3, 3
	ldr	x1, [x19, 3544]
	ldrb	w0, [x1, 1]
	orr	w0, w0, 2
	strb	w0, [x1, 1]
	ldr	x1, [x19, 3544]
	ldr	w0, [x19, 2724]
	ldr	w2, [x1, 684]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	str	w0, [x1, 684]
	ldr	x0, [x19, 3544]
	strb	w4, [x0, 800]
	ldr	x0, [x19, 3544]
	strb	w3, [x0, 704]
	ldr	x0, [x19, 3544]
	ldr	w1, [x19, 2732]
	str	w1, [x0, 816]
	ldr	x1, [x19, 3544]
	ldr	w2, [x1, 768]
	ldr	w0, [x1, 816]
	add	w0, w2, w0
	lsr	w0, w0, 1
	str	w0, [x1, 720]
	ldr	x0, [x19, 3544]
	ldr	w1, [x0, 720]
	str	w1, [x0, 688]
	ldr	x0, [x19, 3544]
	ldr	x1, [x0, 840]
	str	x1, [x0, 744]
	ldrb	w0, [x19, 2031]
	ldr	x1, [x19, 3544]
	cmp	w0, 1
	beq	.L3671
.L3612:
	ldrb	w0, [x1, 3]
.L3613:
	strb	w0, [x1, 3]
	add	x22, x20, 65536
	mov	w2, 0
	b	.L3666
	.p2align 3
.L3586:
	ldr	x0, [x19, 2680]
	strb	wzr, [x0, 704]
	ldr	x1, [x19, 3544]
	cbz	x1, .L3659
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	cbnz	w0, .L3672
.L3589:
	ldr	x0, [x19, 3544]
	cbz	x0, .L3659
	ldr	x0, [x19, 2680]
	add	x22, x20, 65536
	mov	w2, 1
	ldr	w1, [x0, 656]
	ldr	w0, [x22, 1980]
	bl	FSP_ClearLogicFs
.L3588:
	ldr	x0, [x19, 2680]
	mov	w3, 3
	str	x0, [x19, 3544]
	mov	x2, 640
	add	x1, x19, 2040
	str	x0, [x0, 744]
	ldr	x0, [x19, 3544]
	ldr	x4, [x19, 2680]
	str	x4, [x0, 792]
	ldr	x0, [x19, 3544]
	ldr	x4, [x19, 2680]
	str	x4, [x0, 840]
	ldr	x0, [x19, 3544]
	ldrb	w4, [x19, 2026]
	strb	w4, [x0]
	ldr	x0, [x19, 3544]
	strb	w3, [x0, 1]
	ldr	x0, [x19, 3544]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 3544]
	strb	wzr, [x0, 4]
	ldr	x0, [x19, 3544]
	str	wzr, [x0, 676]
	ldr	x0, [x19, 3544]
	add	x0, x0, 16
	bl	memcpy
	ldr	x1, [x19, 3544]
	mov	w0, 3
	ldr	w3, [x19, 2732]
	mov	w2, 0
	str	w3, [x1, 688]
	str	w3, [x1, 720]
	ldr	x1, [x19, 3544]
	strb	wzr, [x1, 704]
	ldr	x1, [x19, 3544]
	ldr	w3, [x19, 2724]
	str	w3, [x1, 684]
	ldr	x1, [x19, 3544]
	ldrb	w3, [x19, 2033]
	str	w3, [x1, 680]
	ldrb	w3, [x19, 2031]
	ldr	x1, [x19, 3544]
	cmp	w3, 1
	csel	w0, wzr, w0, ne
	strb	w0, [x1, 3]
.L3666:
	ldr	x1, [x19, 3544]
	ldr	w0, [x22, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetRef
	ldr	x1, [x19, 3544]
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x19, 3544]
	cbz	x0, .L3614
	ldr	x1, [x19, 2680]
	mov	w2, 1
	ldr	w0, [x22, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_ClearLogicFs
.L3614:
	str	xzr, [x19, 3544]
.L3674:
	mov	w0, w21
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3585:
	ldr	x0, [x19, 2680]
	mov	w1, 3
	strb	w1, [x0, 704]
	ldrb	w0, [x19, 2025]
	cbnz	w0, .L3592
	ldr	x1, [x19, 3544]
	cbz	x1, .L3593
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	mov	w21, w0
	cbnz	w0, .L3673
.L3594:
	ldr	x0, [x19, 2680]
	str	x0, [x19, 3544]
	str	x0, [x0, 792]
.L3595:
	ldr	x0, [x19, 3544]
	mov	w22, 1
	ldrb	w3, [x19, 2026]
	add	x1, x19, 2040
	mov	x2, 640
	add	x23, x20, 65536
	strb	w3, [x0]
	ldr	x0, [x19, 3544]
	strb	w22, [x0, 1]
	ldr	x0, [x19, 3544]
	strb	wzr, [x0, 4]
	ldr	x0, [x19, 3544]
	str	wzr, [x0, 676]
	ldr	x0, [x19, 3544]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 3544]
	ldr	w3, [x19, 2724]
	str	w3, [x0, 684]
	ldr	x0, [x19, 3544]
	str	wzr, [x0, 680]
	ldr	x0, [x19, 3544]
	add	x0, x0, 16
	bl	memcpy
	ldr	x0, [x19, 3544]
	ldr	w1, [x19, 2732]
	str	w1, [x0, 768]
	ldr	x0, [x19, 3544]
	ldr	w1, [x0, 768]
	str	w1, [x0, 688]
	str	w1, [x0, 720]
	ldr	x0, [x19, 3544]
	strb	w22, [x0, 752]
	ldrb	w1, [x19, 2031]
	ldr	x0, [x19, 3544]
	cmp	w1, 1
	cset	w1, eq
	strb	w1, [x0, 3]
	ldr	w22, [x23, 1912]
	cmp	w22, 1
	bne	.L3584
.L3663:
	ldr	x1, [x19, 3544]
	mov	w2, 0
	ldr	w0, [x23, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_SetRef
	ldr	x1, [x19, 3544]
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	mov	w21, w0
	ldr	x0, [x19, 3544]
	cbz	x0, .L3614
	ldr	x1, [x19, 2680]
	mov	w2, w22
	ldr	w0, [x23, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_ClearLogicFs
	str	xzr, [x19, 3544]
	b	.L3674
	.p2align 3
.L3669:
	ldr	x1, [x19, 3544]
	cbz	x1, .L3604
	mov	w2, 0
	mov	x0, x20
	bl	OutputFrmToVO
	mov	w21, w0
	cbnz	w0, .L3675
.L3605:
	ldr	x0, [x19, 2680]
	str	x0, [x19, 3544]
	str	x0, [x0, 840]
.L3606:
	ldr	x0, [x19, 3544]
	mov	w22, 2
	ldrb	w3, [x19, 2026]
	mov	x2, 640
	add	x1, x19, 2040
	add	x23, x20, 65536
	strb	w3, [x0]
	ldr	x0, [x19, 3544]
	strb	w22, [x0, 1]
	ldr	x0, [x19, 3544]
	strb	wzr, [x0, 4]
	ldr	x0, [x19, 3544]
	str	wzr, [x0, 676]
	ldr	x0, [x19, 3544]
	strb	wzr, [x0, 2]
	ldr	x0, [x19, 3544]
	ldr	w3, [x19, 2724]
	str	w3, [x0, 684]
	ldr	x0, [x19, 3544]
	str	wzr, [x0, 680]
	ldr	x0, [x19, 3544]
	add	x0, x0, 16
	bl	memcpy
	ldr	x1, [x19, 3544]
	mov	w0, 2
	ldr	w2, [x19, 2732]
	str	w2, [x1, 816]
	ldr	x1, [x19, 3544]
	ldr	w2, [x1, 816]
	str	w2, [x1, 688]
	str	w2, [x1, 720]
	ldr	x1, [x19, 3544]
	strb	w22, [x1, 800]
	ldrb	w2, [x19, 2031]
	ldr	x1, [x19, 3544]
	cmp	w2, 1
	csel	w0, wzr, w0, ne
	strb	w0, [x1, 3]
	ldr	w22, [x23, 1912]
	cmp	w22, 1
	beq	.L3663
	mov	w0, w21
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L3592:
	ldr	x0, [x19, 3544]
	cbz	x0, .L3676
.L3597:
	ldr	x27, [x0, 600]
	mov	x2, 640
	ldp	w24, w23, [x0, 16]
	ldp	w22, w21, [x0, 24]
	ldr	x26, [x0, 608]
	add	x1, x19, 2040
	ldr	x25, [x0, 616]
	add	x0, x0, 16
	bl	memcpy
	ldr	x0, [x19, 2624]
	cmn	x0, #1
	ccmn	x27, #1, 4, eq
	beq	.L3598
	ldr	x0, [x19, 3544]
	str	x27, [x0, 600]
.L3598:
	ldr	x0, [x19, 2632]
	ldr	x1, [x19, 3544]
	cmp	x0, x26
	csel	x0, x0, x26, ls
	str	x0, [x1, 608]
	ldr	x0, [x19, 2640]
	ldr	x1, [x19, 3544]
	cmp	x0, x25
	csel	x0, x0, x25, ls
	str	x0, [x1, 616]
	ldr	w0, [x19, 2040]
	ldr	x1, [x19, 3544]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x1, 16]
	ldr	w0, [x19, 2044]
	ldr	x1, [x19, 3544]
	cmp	w0, w23
	csel	w0, w0, w23, ls
	str	w0, [x1, 20]
	ldr	w0, [x19, 2048]
	ldr	x1, [x19, 3544]
	cmp	w0, w22
	csel	w0, w0, w22, ls
	str	w0, [x1, 24]
	ldr	w0, [x19, 2052]
	ldr	x1, [x19, 3544]
	cmp	w0, w21
	csel	w0, w0, w21, ls
	str	w0, [x1, 28]
	ldr	x1, [x19, 3544]
	ldrb	w0, [x1]
	cbz	w0, .L3599
	ldrb	w0, [x19, 2026]
.L3599:
	strb	w0, [x1]
	mov	w4, 1
	mov	w3, 3
	ldr	x1, [x19, 3544]
	ldrb	w0, [x1, 1]
	orr	w0, w0, 1
	strb	w0, [x1, 1]
	ldr	x1, [x19, 3544]
	ldr	w0, [x19, 2724]
	ldr	w2, [x1, 684]
	cmp	w0, w2
	csel	w0, w0, w2, cs
	str	w0, [x1, 684]
	ldr	x0, [x19, 3544]
	strb	w4, [x0, 752]
	ldr	x0, [x19, 3544]
	strb	w3, [x0, 704]
	ldr	x0, [x19, 3544]
	ldr	w1, [x19, 2732]
	str	w1, [x0, 768]
	ldr	x1, [x19, 3544]
	ldr	w2, [x1, 768]
	ldr	w0, [x1, 816]
	add	w0, w2, w0
	lsr	w0, w0, w4
	str	w0, [x1, 720]
	ldr	x0, [x19, 3544]
	ldr	w1, [x0, 720]
	str	w1, [x0, 688]
	ldr	x0, [x19, 3544]
	ldr	x1, [x0, 792]
	str	x1, [x0, 744]
	ldrb	w0, [x19, 2031]
	ldr	x1, [x19, 3544]
	cmp	w0, 1
	bne	.L3612
	ldrb	w0, [x1, 3]
	orr	w0, w0, 1
	uxtb	w0, w0
	b	.L3613
	.p2align 3
.L3659:
	add	x22, x20, 65536
	b	.L3588
	.p2align 3
.L3672:
	ldr	x2, .LC913
	mov	w4, w0
	ldr	x1, .LC914
	mov	w3, 2961
	add	x2, x2, 296
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3589
	.p2align 3
.L3671:
	ldrb	w0, [x1, 3]
	orr	w0, w0, 2
	uxtb	w0, w0
	b	.L3613
	.p2align 3
.L3604:
	ldr	x0, [x19, 2680]
	mov	w21, 0
	str	x0, [x19, 3544]
	str	x0, [x0, 840]
	b	.L3606
	.p2align 3
.L3593:
	ldr	x0, [x19, 2680]
	mov	w21, 0
	str	x0, [x19, 3544]
	str	x0, [x0, 792]
	b	.L3595
	.p2align 3
.L3675:
	ldr	x2, .LC913
	mov	w4, w0
	ldr	x1, .LC914
	mov	w3, 3129
	add	x2, x2, 296
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3605
	.p2align 3
.L3673:
	ldr	x2, .LC913
	mov	w4, w0
	ldr	x1, .LC914
	mov	w3, 3013
	add	x2, x2, 296
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3594
	.p2align 3
.L3670:
	ldr	x0, [x19, 2680]
	str	x0, [x19, 3544]
	str	x0, [x0, 840]
	ldr	x0, [x19, 3544]
	b	.L3609
	.p2align 3
.L3676:
	ldr	x0, [x19, 2680]
	str	x0, [x19, 3544]
	str	x0, [x0, 792]
	ldr	x0, [x19, 3544]
	b	.L3597
	.size	DirectOutput, .-DirectOutput
	.align	3
.LC913:
	.xword	.LANCHOR2
	.align	3
.LC914:
	.xword	.LC845
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	StorePicInDPB
	.type	StorePicInDPB, %function
StorePicInDPB:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L3869
	add	x0, x20, 20480
	add	x23, x20, 61440
	str	wzr, [x0, 728]
	ldrb	w1, [x23, 2027]
	cmp	w1, 2
	cset	w1, eq
	str	w1, [x0, 732]
	ldrb	w0, [x23, 2024]
	cbz	w0, .L3870
	add	x21, x20, 65536
	ldr	x0, .LC921
	ldrsw	x1, [x21, 1980]
	ldr	w2, [x21, 1992]
	str	w2, [x21, 1988]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L3871
.L3682:
	ldr	w0, [x21, 1908]
	cmp	w0, 2
	beq	.L3872
	ldr	x19, [x20]
	ldr	w0, [x19, 24]
	cbnz	w0, .L3687
	ldr	w1, [x21, 1984]
	cmp	w1, 2
	beq	.L3689
	ldrb	w1, [x23, 2026]
	cbnz	w1, .L3689
	ldrb	w1, [x23, 2027]
	ldr	x24, [x23, 2680]
	sub	w2, w1, #1
	uxtb	w2, w2
	cbnz	w1, .L3873
.L3691:
	cmp	w2, 1
	bls	.L3874
.L3853:
	cbz	w1, .L3696
	ldrb	w2, [x24, 1]
	cbnz	w2, .L3696
.L3690:
	cmp	w0, 2
	beq	.L3875
.L3689:
	ldr	w6, [x23, 2704]
	cbz	w6, .L3725
	ldr	w3, [x21, 1972]
	ldr	w2, [x23, 2732]
	cmp	w3, w2
	bcs	.L3726
	ldrb	w0, [x23, 2026]
	cbnz	w0, .L3726
	ldr	w0, [x19, 684]
	cbz	w0, .L3876
.L3726:
	mov	x0, x20
	bl	Marking
	cbnz	w0, .L3877
	mov	x0, x20
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	mov	x0, x20
	bl	RemoveUnUsedFrameStore
	cbnz	w0, .L3878
.L3719:
	ldrb	w0, [x23, 2025]
	cmp	w0, 1
	beq	.L3730
	add	x24, x20, 24576
.L3734:
	ldr	w6, [x23, 2704]
	cbz	w6, .L3879
	ldr	w4, [x24, 3712]
	ldr	w5, [x24, 3716]
	ldr	w3, [x24, 3704]
	add	w0, w4, w5
	cmp	w3, w0
	bhi	.L3742
	ldr	x0, [x20]
	ldr	w0, [x0, 24]
	cmp	w0, 3
	beq	.L3743
	ldr	x0, .LC937
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L3743
	ldr	x1, .LC939
	mov	w2, 4128
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x20
	bl	ClearDPB
	ldr	x1, .LC920
	mov	w3, 4130
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC930
	b	.L3773
	.p2align 3
.L3687:
	ldrb	w1, [x23, 2026]
	cbnz	w1, .L3690
	ldrb	w1, [x23, 2027]
	ldr	x24, [x23, 2680]
	sub	w2, w1, #1
	uxtb	w2, w2
	cbz	w1, .L3691
	b	.L3873
.L3870:
	ldr	x1, .LC918
	add	x21, x20, 65536
	bl	dprint_vfmw
	ldr	x1, .LC920
	mov	w3, 3808
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC930
.L3773:
	ldr	x1, [x23, 2680]
	mov	w2, 1
	ldr	w0, [x21, 1980]
	mov	w19, -1
	ldr	w1, [x1, 656]
	bl	FSP_ClearLogicFs
	mov	w3, w19
	mov	w2, 4228
	mov	x1, x20
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, [x23, 2680]
	strb	wzr, [x0, 4]
	ldr	x0, [x23, 2680]
	strb	wzr, [x0, 1]
.L3770:
	strb	wzr, [x23, 2024]
	mov	w0, w19
.L3852:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3871:
	ldr	x1, [x0, 160]
	mov	x0, 1
	movk	x0, 0x2, lsl 32
	cmp	x1, x0
	bne	.L3682
	mov	x0, x20
	bl	H264_Sei_Get_Frame_Pts
	b	.L3682
.L3873:
	ldrb	w3, [x24, 1]
	cmp	w3, wzr
	ccmp	w2, 1, 0, eq
	bhi	.L3690
	b	.L3691
.L3877:
	ldr	x1, .LC934
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC920
	mov	w3, 4049
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC930
	b	.L3773
.L3874:
	ldr	w2, [x21, 1984]
	cbnz	w2, .L3693
	mov	w0, 1
	mov	x2, 744
	str	w0, [x21, 1984]
	add	x1, x23, 2024
	add	x0, x23, 2768
	bl	memcpy
	ldr	w0, [x19, 24]
	b	.L3690
.L3696:
	add	x22, x23, 2024
.L3699:
	cbz	w1, .L3700
	ldrb	w0, [x22, 1]
	cmp	w0, 1
	beq	.L3880
.L3700:
	ldr	w0, [x22, 708]
	str	w0, [x24, 688]
.L3701:
	mov	x1, x24
	mov	x0, x20
	bl	GetImagePara
	ldr	w0, [x21, 1980]
	ldr	w1, [x24, 656]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L3881
	ldrb	w0, [x22, 3]
	cbz	w0, .L3703
	ldrb	w0, [x22, 1]
	cmp	w0, 1
	beq	.L3882
.L3703:
	ldr	x0, [x22, 600]
.L3861:
	str	x0, [x19, 584]
.L3704:
	ldr	x0, [x22, 608]
	str	x0, [x19, 592]
	ldr	x0, [x22, 616]
	str	x0, [x19, 600]
	ldr	w0, [x22, 16]
	str	w0, [x19]
	ldr	w0, [x22, 20]
	str	w0, [x19, 4]
	ldr	w0, [x22, 24]
	str	w0, [x19, 8]
	ldr	w0, [x22, 28]
	str	w0, [x19, 12]
	ldr	w1, [x24, 688]
	str	w1, [x19, 152]
	ldr	w0, [x22, 440]
	str	w0, [x19, 424]
	ldr	w0, [x22, 436]
	str	w0, [x19, 420]
	ldr	x0, [x22, 448]
	str	x0, [x19, 432]
	cbz	w1, .L3710
	ldrb	w0, [x19, 64]
	and	w0, w0, 3
	cbz	w0, .L3883
.L3708:
	ldr	x0, [x20]
	ldr	w2, [x0, 4]
	cmp	w2, w1
	bcs	.L3710
	ldr	w0, [x0, 684]
	cmp	w0, 1
	beq	.L3710
	ldr	x0, .LC928
	ldr	x4, [x0]
	cbz	x4, .L3717
	ldr	w0, [x21, 1980]
	mov	w3, 8
	stp	w1, w2, [x29, 88]
	add	x2, x29, 88
	mov	w1, 104
	blr	x4
.L3717:
	ldr	w0, [x21, 1980]
	mov	w2, 0
	ldr	w1, [x24, 656]
	bl	FSP_SetDisplay
	ldr	x1, .LC920
	mov	w3, 3972
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC930
	b	.L3773
.L3693:
	cmp	w2, 1
	bne	.L3853
	cmp	w1, 1
	add	x22, x23, 2024
	ldr	x24, [x23, 3424]
	beq	.L3884
	cmp	w1, 2
	bne	.L3699
	ldr	w0, [x23, 2720]
	str	w0, [x24, 812]
	ldrb	w1, [x22, 3]
	b	.L3699
.L3883:
	ldr	x1, .LC927
	mov	w2, 3947
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC928
	ldr	x4, [x0]
	cbz	x4, .L3709
	ldr	w0, [x21, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 111
	blr	x4
.L3709:
	ldr	w1, [x19, 152]
	cbnz	w1, .L3708
.L3710:
	ldr	w0, [x21, 1980]
	mov	w2, 1
	ldr	w1, [x24, 656]
	bl	FSP_SetDisplay
	ldr	w0, [x21, 1980]
	mov	x4, x19
	add	x3, x20, 8
	mov	x2, x20
	mov	w1, 0
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L3885
	ldr	w0, [x21, 1980]
	mov	w2, 0
	ldr	w1, [x24, 656]
	bl	FSP_SetDisplay
.L3712:
	ldr	x0, [x20]
	ldr	w0, [x0, 660]
	add	w0, w0, 2047
	cmp	w0, 4095
	bhi	.L3886
	str	wzr, [x19, 16]
.L3714:
	ldr	w0, [x21, 2000]
	ldr	w1, [x21, 1984]
	add	w0, w0, 2
	str	w0, [x21, 2000]
	cmp	w1, 2
	beq	.L3716
	mov	w0, 1
	str	w0, [x24, 848]
.L3716:
	mov	w0, 2
	str	w0, [x21, 1984]
	ldr	x19, [x20]
	ldr	w0, [x19, 24]
	cmp	w0, 2
	bne	.L3689
.L3875:
	ldr	w0, [x23, 2704]
	cbz	w0, .L3719
	ldrb	w0, [x23, 2030]
	cmp	w0, 5
	beq	.L3720
.L3723:
	mov	x0, x20
	add	x19, x20, 24576
	bl	SimpleSlideDPB
	ldr	w1, [x19, 3708]
	add	x2, x23, 2024
	mov	x0, x20
	bl	InsertFrmInDPB
	cbz	w0, .L3887
	ldr	x20, .LC930
	mov	w3, w0
	mov	w2, 4015
	mov	w0, 0
	mov	x1, x20
	bl	dprint_vfmw
	ldr	x1, .LC920
	mov	w3, 4016
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3773
.L3725:
	ldrb	w0, [x23, 2025]
	cmp	w0, 1
	beq	.L3730
	add	x24, x20, 24576
	ldr	w3, [x24, 3704]
.L3742:
	mov	w7, -1
	mov	w8, w7
	.p2align 2
.L3761:
	ldr	w1, [x24, 3708]
	cmp	w1, w3
	bcc	.L3888
	cmp	w1, w3
	mov	w19, w1
	bls	.L3749
	mov	w19, w3
	str	w3, [x24, 3708]
.L3749:
	cbz	w19, .L3780
	add	x1, x24, 3320
	mov	w5, 2147483647
	mov	w22, 0
	mov	w0, 0
	.p2align 2
.L3752:
	ldr	x4, [x1]
	add	x1, x1, 8
	ldr	w2, [x4, 672]
	cmp	w2, w5
	bge	.L3751
	ldrb	w4, [x4, 4]
	cmp	w4, wzr
	csel	w22, w22, w0, eq
	csel	w5, w5, w2, eq
.L3751:
	add	w0, w0, 1
	cmp	w0, w19
	bne	.L3752
.L3750:
	cbnz	w6, .L3753
	ldr	w0, [x23, 2708]
	cmp	w0, w5
	blt	.L3754
.L3753:
	cbz	w3, .L3754
	cmp	w8, w22
	ccmp	w7, w19, 0, eq
	beq	.L3889
	mov	w1, w22
	mov	x0, x20
	bl	OutputFrmFromDPB
	cmn	w0, #1
	mov	w25, w0
	beq	.L3760
	mov	w7, w19
	mov	w8, w22
	ldr	w6, [x23, 2704]
	ldr	w3, [x24, 3704]
	b	.L3761
.L3754:
	ldr	w0, [x21, 1908]
	cmp	w0, 2
	beq	.L3890
.L3756:
	mov	x0, x20
	bl	DirectOutput
	cmn	w0, #1
	mov	w19, w0
	beq	.L3891
	cmp	w0, 1
	bne	.L3758
	ldr	x0, [x23, 2680]
	strb	wzr, [x0, 4]
	ldr	x0, [x23, 2680]
	strb	wzr, [x0, 1]
.L3758:
	ldr	x1, .LC920
	mov	w3, 4159
	mov	w2, w19
	mov	w0, 14
	bl	dprint_vfmw
.L3686:
	cmn	w19, #1
	bne	.L3770
	ldr	x20, .LC930
	b	.L3773
	.p2align 3
.L3780:
	mov	w5, 2147483647
	mov	w22, 0
	b	.L3750
.L3730:
	ldr	x0, [x23, 3544]
	ldr	x3, [x23, 2680]
	cmp	x3, x0
	ccmp	x0, xzr, 4, eq
	beq	.L3892
	mov	x0, x20
	bl	DirectOutput
	cmn	w0, #1
	mov	w19, w0
	beq	.L3893
	cmp	w0, 1
	bne	.L3738
	ldr	x0, [x23, 2680]
	strb	wzr, [x0, 4]
	ldr	x0, [x23, 2680]
	strb	wzr, [x0, 1]
.L3738:
	ldr	x1, .LC920
	mov	w3, 4085
	mov	w2, w19
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3686
.L3872:
	ldr	x1, .LC923
	bl	dprint_vfmw
	mov	x0, x20
	bl	DirectOutput
	mov	w19, w0
	ldr	w1, [x21, 640]
	ldr	w0, [x23, 2756]
	cmp	w0, w1
	beq	.L3684
	uxtw	x0, w0
	add	x0, x0, 16384
	add	x20, x20, x0, lsl 2
	str	wzr, [x20, 568]
	str	w1, [x23, 2756]
.L3684:
	cmp	w19, 1
	beq	.L3894
.L3685:
	ldr	x1, .LC920
	mov	w3, 3842
	mov	w2, w19
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3686
.L3888:
	cbz	w6, .L3763
	ldrb	w0, [x23, 2028]
	cbnz	w0, .L3763
	ldr	w0, [x24, 3712]
	cbz	w0, .L3763
	mov	w0, 0
	b	.L3768
.L3765:
	ldr	w1, [x24, 3712]
	cmp	w1, w0
	bls	.L3895
.L3768:
	add	x1, x20, x0, uxtw 3
	ldr	w3, [x23, 2696]
	add	w0, w0, 1
	ldr	x2, [x1, 28024]
	ldr	w4, [x2, 660]
	cmp	w4, w3
	bne	.L3765
	ldr	w3, [x2, 848]
	cmp	w3, 1
	beq	.L3765
	strb	wzr, [x2, 2]
	ldr	x2, [x1, 28024]
	ldrb	w3, [x2, 4]
	cmp	w3, 1
	bne	.L3767
	str	w3, [x2, 676]
	ldr	x2, [x1, 28024]
	strb	wzr, [x2, 4]
	ldr	x2, [x1, 28024]
.L3767:
	ldr	w1, [x2, 692]
	ldr	w3, [x21, 640]
	cmp	w1, w3
	uxtw	x1, w1
	add	x1, x1, 16384
	beq	.L3765
	add	x1, x20, x1, lsl 2
	str	wzr, [x1, 568]
	str	w3, [x2, 692]
	b	.L3765
.L3895:
	ldr	w1, [x24, 3708]
.L3763:
	add	x2, x23, 2024
	mov	x0, x20
	bl	InsertFrmInDPB
	ldr	w1, [x24, 3708]
	str	w1, [x23, 3536]
	cbz	w0, .L3769
	ldr	x20, .LC930
	mov	w3, w0
	mov	w2, 4214
	mov	w0, 1
	mov	x1, x20
	bl	dprint_vfmw
	ldr	x1, .LC920
	mov	w3, 4215
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3773
.L3760:
	ldr	x20, .LC930
	mov	w3, w0
	mov	w2, 4177
	mov	w0, 1
	mov	x1, x20
	bl	dprint_vfmw
	ldr	x1, .LC920
	mov	w3, 4178
	mov	w2, w25
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3773
.L3885:
	ldr	w0, [x21, 2008]
	add	w0, w0, 1
	str	w0, [x21, 2008]
	b	.L3712
.L3887:
	ldr	w1, [x19, 3708]
	mov	x0, x20
	add	w1, w1, 1
	str	w1, [x19, 3708]
	mov	w19, 0
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	ldr	x1, .LC920
	mov	w3, 4024
	mov	w2, 0
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3770
.L3769:
	add	w1, w1, 1
	mov	x0, x20
	str	w1, [x24, 3708]
	mov	w19, 0
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	b	.L3770
.L3743:
	ldr	w5, [x24, 3708]
	cmp	w5, w3
	bls	.L3745
	mov	w5, w3
	str	w3, [x24, 3708]
.L3745:
	cbz	w5, .L3777
	add	x2, x24, 3320
	mov	w1, 0
	mov	w0, 0
	mov	w4, 2147483647
	.p2align 2
.L3748:
	ldr	x3, [x2]
	add	x2, x2, 8
	ldr	w3, [x3, 672]
	cmp	w3, w4
	bge	.L3747
	mov	w1, w0
	mov	w4, w3
.L3747:
	add	w0, w0, 1
	cmp	w0, w5
	bne	.L3748
.L3746:
	mov	x0, x20
	bl	RemoveFrameStoreOutDPB
	mov	x0, x20
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	ldr	w6, [x23, 2704]
	ldr	w3, [x24, 3704]
	b	.L3742
.L3876:
	ldr	x1, .LC932
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC928
	ldr	x4, [x0]
	cbz	x4, .L3727
	ldr	w1, [x21, 1972]
	mov	w3, 8
	ldr	w2, [x23, 2732]
	ldr	w0, [x21, 1980]
	stp	w2, w1, [x29, 88]
	add	x2, x29, 88
	mov	w1, 104
	blr	x4
.L3727:
	mov	x0, x20
	bl	H264_ClearCurrPic
	mov	x0, x20
	bl	ClearDPB
	ldr	x1, .LC920
	mov	w3, 4041
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC930
	b	.L3773
.L3882:
	ldr	x0, [x22, 600]
	cmn	x0, #1
	bne	.L3704
	ldr	x0, [x23, 3368]
	cmn	x0, #1
	bne	.L3861
	b	.L3704
	.p2align 3
.L3889:
	ldr	x2, .LC940
	mov	w3, w22
	ldr	x1, .LC942
	mov	w0, 1
	add	x2, x2, 312
	bl	dprint_vfmw
	ldr	x1, .LC920
	mov	w3, 4166
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC930
	b	.L3773
.L3890:
	ldrb	w0, [x23, 2027]
	cbz	w0, .L3756
	ldr	x0, [x23, 2680]
	str	x0, [x23, 3552]
	b	.L3756
.L3878:
	ldr	x1, .LC936
	mov	w0, 22
	bl	dprint_vfmw
	b	.L3719
.L3886:
	mov	x1, x19
	mov	x0, x20
	bl	SetFrmRepeatCount.part.7
	b	.L3714
.L3879:
	ldr	w3, [x24, 3704]
	b	.L3742
.L3892:
	add	x24, x20, 24576
	ldr	w4, [x24, 3708]
	cbz	w4, .L3734
	ldr	x0, [x20, 27896]
	cmp	x3, x0
	beq	.L3896
	add	x0, x24, 3328
	mov	w1, 0
	.p2align 2
.L3739:
	add	w1, w1, 1
	cmp	w1, w4
	beq	.L3734
	ldr	x2, [x0], 8
	cmp	x3, x2
	bne	.L3739
.L3735:
	add	x2, x23, 2024
	mov	x0, x20
	bl	InsertFrmInDPB
	cmn	w0, #1
	mov	w19, w0
	beq	.L3897
	mov	x0, x20
	mov	w19, 0
	bl	UpdateReflist
	mov	x0, x20
	bl	UpdateLTReflist
	ldr	x1, .LC920
	mov	w3, 4105
	mov	w2, 0
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3770
.L3894:
	ldr	x0, [x23, 2680]
	strb	wzr, [x0, 4]
	ldr	x0, [x23, 2680]
	strb	wzr, [x0, 1]
	b	.L3685
.L3720:
	mov	x0, x20
	bl	IDRMemMarking
	cbz	w0, .L3723
	mov	w0, -1
	b	.L3852
	.p2align 3
.L3880:
	mov	w0, 3
	strb	w0, [x24, 1]
	ldr	w1, [x24, 688]
	ldr	w0, [x22, 708]
	add	w0, w1, w0
	str	w0, [x24, 688]
	b	.L3701
.L3891:
	ldr	x1, .LC930
	mov	w3, w0
	mov	w2, 4150
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3758
.L3881:
	ldr	x1, .LC925
	mov	w2, 3915
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC920
	mov	w3, 3916
	mov	w2, -1
	mov	w0, 14
	bl	dprint_vfmw
	ldr	x20, .LC930
	b	.L3773
.L3897:
	ldr	x20, .LC930
	mov	w3, w0
	mov	w2, 4098
	mov	w0, 1
	mov	x1, x20
	bl	dprint_vfmw
	ldr	x1, .LC920
	mov	w3, 4099
	mov	w2, w19
	mov	w0, 14
	bl	dprint_vfmw
	b	.L3773
.L3777:
	mov	w1, 0
	b	.L3746
.L3869:
	ldr	x2, .LC915
	mov	w3, 3799
	ldr	x1, .LC916
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L3852
.L3884:
	ldr	w0, [x23, 2716]
	str	w0, [x24, 764]
	ldrb	w1, [x22, 3]
	b	.L3699
.L3896:
	mov	w1, 0
	b	.L3735
.L3893:
	ldr	x1, .LC930
	mov	w3, w0
	mov	w2, 4075
	mov	w0, 1
	bl	dprint_vfmw
	b	.L3738
	.size	StorePicInDPB, .-StorePicInDPB
	.align	3
.LC915:
	.xword	.LC30
	.align	3
.LC916:
	.xword	.LC32
	.align	3
.LC918:
	.xword	.LC917
	.align	3
.LC920:
	.xword	.LC919
	.align	3
.LC921:
	.xword	s_pstVfmwChan
	.align	3
.LC923:
	.xword	.LC922
	.align	3
.LC925:
	.xword	.LC924
	.align	3
.LC927:
	.xword	.LC926
	.align	3
.LC928:
	.xword	g_event_report
	.align	3
.LC930:
	.xword	.LC929
	.align	3
.LC932:
	.xword	.LC931
	.align	3
.LC934:
	.xword	.LC933
	.align	3
.LC936:
	.xword	.LC935
	.align	3
.LC937:
	.xword	g_apple_airplay_mirrorinig_flag
	.align	3
.LC939:
	.xword	.LC938
	.align	3
.LC940:
	.xword	.LANCHOR2
	.align	3
.LC942:
	.xword	.LC941
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecGap
	.type	DecGap, %function
DecGap:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x25, x19, 24576
	add	x20, x19, 20480
	bl	_mcount
	add	x28, x19, 16384
	add	x0, x19, 12288
	add	x27, x19, 61440
	ldr	w1, [x25, 3180]
	mov	w22, 2
	ldr	w2, [x20, 1600]
	ldrb	w0, [x0, 2705]
	ldr	w5, [x20, 1596]
	cmp	w0, 1
	lsl	x0, x1, 6
	sub	x0, x0, x1
	ldr	w21, [x28, 788]
	lsl	x0, x0, 2
	str	w2, [x29, 120]
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	lsl	x0, x0, 2
	add	x1, x19, x0
	add	x0, x0, 20480
	add	x1, x1, 20480
	add	x0, x19, x0
	add	x0, x0, 3268
	ldrb	w1, [x1, 3271]
	str	w1, [x29, 104]
	ldr	w1, [x20, 752]
	str	w1, [x29, 112]
	ldr	w1, [x20, 756]
	str	x0, [x27, 2688]
	str	w1, [x29, 108]
	csel	w1, wzr, w22, ne
	ldr	w0, [x25, 3708]
	str	w1, [x29, 116]
	cbz	w0, .L3922
	mov	w0, 1
	add	w21, w21, 4
	add	w2, w5, 1
	lsl	w21, w0, w21
	ldr	x1, .LC946
	mov	w0, w22
	udiv	w5, w2, w21
	str	wzr, [x20, 752]
	str	wzr, [x20, 756]
	msub	w26, w5, w21, w2
	bl	dprint_vfmw
	ldr	x1, .LC948
	mov	w3, w26
	ldr	w2, [x29, 120]
	mov	w0, w22
	bl	dprint_vfmw
	ldr	w1, [x25, 3704]
	ldr	w0, [x25, 3708]
	cmp	w0, w1
	bhi	.L3923
.L3902:
	cbz	w0, .L3913
	sub	w3, w0, #1
	mov	w22, 0
	add	x3, x3, 3488
	add	x0, x25, 3320
	add	x3, x19, x3, lsl 3
	.p2align 2
.L3905:
	ldr	x2, [x0]
	add	x0, x0, 8
	ldr	w1, [x2, 672]
	cmp	w22, w1
	bge	.L3904
	ldrb	w2, [x2, 4]
	cmp	w2, wzr
	csel	w22, w22, w1, eq
.L3904:
	cmp	x0, x3
	bne	.L3905
.L3903:
	ldr	w0, [x29, 120]
	mov	w23, 1
	str	wzr, [x29, 124]
	mov	w24, w23
	cmp	w0, w26
	bne	.L3918
	b	.L3910
	.p2align 3
.L3908:
	mov	x1, 0
	mov	x0, x19
	strb	wzr, [x27, 2028]
	bl	StorePicInDPB
	add	w1, w26, 1
	cbnz	w0, .L3924
.L3909:
	sdiv	w0, w1, w21
	str	w26, [x20, 1596]
	msub	w26, w0, w21, w1
	ldr	w0, [x29, 120]
	cmp	w0, w26
	beq	.L3910
	ldr	w0, [x25, 3708]
	ldr	w1, [x29, 124]
	cmp	w1, w0
	bhi	.L3910
.L3918:
	mov	w1, 1
	mov	x0, x19
	bl	AllocFrameStore
	cbnz	w0, .L3925
	ldr	x1, .LC952
	mov	w0, 2
	bl	dprint_vfmw
	strb	w24, [x27, 2030]
	ldr	x0, [x27, 2680]
	str	w26, [x0, 660]
	str	w26, [x27, 2696]
	ldr	x0, [x27, 2680]
	str	w26, [x0, 712]
	ldr	w0, [x29, 116]
	str	w0, [x27, 2704]
	ldr	x0, [x27, 2680]
	str	wzr, [x0, 708]
	ldr	x0, [x27, 2680]
	str	w23, [x0, 676]
	ldr	x0, [x27, 2680]
	strb	wzr, [x0, 4]
	ldr	x0, [x27, 2680]
	strb	w23, [x0]
	strb	w24, [x27, 2026]
	ldr	x0, [x27, 2688]
	strb	wzr, [x0, 3]
	ldr	w0, [x28, 792]
	cbz	w0, .L3908
	mov	x0, x19
	str	w26, [x20, 768]
	bl	DecPOC
	ldr	w0, [x20, 748]
	str	w0, [x27, 2708]
	ldr	w0, [x20, 744]
	str	w0, [x27, 2712]
	ldr	w0, [x20, 736]
	str	w0, [x27, 2716]
	cmp	w0, w22
	ldr	w0, [x20, 740]
	str	w0, [x27, 2720]
	bls	.L3908
	cmp	w0, w22
	ldr	w0, [x29, 124]
	mov	x1, 0
	strb	wzr, [x27, 2028]
	csinc	w0, w0, w0, ls
	str	w0, [x29, 124]
	mov	x0, x19
	bl	StorePicInDPB
	add	w1, w26, 1
	cbz	w0, .L3909
.L3924:
	ldr	w1, [x29, 112]
	mov	w3, w0
	str	w1, [x20, 752]
	mov	w2, 6491
	ldr	w1, [x29, 108]
	mov	w0, 0
	str	w1, [x20, 756]
	ldrb	w5, [x29, 104]
	ldr	x4, [x27, 2688]
	ldr	x1, .LC954
	strb	w5, [x4, 3]
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
.L3923:
	mov	w0, w1
	str	w1, [x25, 3708]
	b	.L3902
	.p2align 3
.L3922:
	ldr	x1, .LC944
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3910:
	ldr	w0, [x29, 112]
	str	w0, [x20, 752]
	ldr	w0, [x29, 108]
	str	w0, [x20, 756]
	mov	w0, 0
	ldrb	w2, [x29, 104]
	ldr	x1, [x27, 2688]
	strb	w2, [x1, 3]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L3925:
	ldr	w0, [x29, 112]
	str	w0, [x20, 752]
	ldr	w0, [x29, 108]
	str	w0, [x20, 756]
	mov	w0, 0
	ldrb	w3, [x29, 104]
	ldr	x2, [x27, 2688]
	ldr	x1, .LC950
	strb	w3, [x2, 3]
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L3913:
	mov	w22, 0
	b	.L3903
	.size	DecGap, .-DecGap
	.align	3
.LC944:
	.xword	.LC943
	.align	3
.LC946:
	.xword	.LC945
	.align	3
.LC948:
	.xword	.LC947
	.align	3
.LC950:
	.xword	.LC949
	.align	3
.LC952:
	.xword	.LC951
	.align	3
.LC954:
	.xword	.LC953
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitPic
	.type	InitPic, %function
InitPic:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L4038
	add	x20, x21, 20480
	mov	w25, 2208
	ldr	x0, [x21, 14968]
	add	x19, x21, 61440
	mov	w22, 4000
	ldr	x3, [x21, 14960]
	ldr	w1, [x20, 1592]
	add	x23, x21, 65536
	ldrb	w2, [x19, 2024]
	umull	x1, w1, w25
	add	x25, x0, x1
	ldr	w0, [x25, 28]
	umull	x0, w0, w22
	add	x22, x3, x0
	cbnz	w2, .L4039
	add	x1, x29, 108
	mov	x0, x21
	bl	GetReRangeFlag
	mov	w24, w0
	ldr	w1, [x21, 15012]
	ldr	w0, [x22, 36]
	cmp	w1, w0
	beq	.L4040
.L3932:
	ldr	x1, .LC960
	add	x0, x21, 12288
	strb	wzr, [x22, 24]
	mov	x2, 4000
	add	x0, x0, 2688
	ldr	x3, [x1, 112]
	mov	x1, x22
	blr	x3
.L3933:
	ldr	w0, [x29, 108]
	cbz	w0, .L4041
	ldr	w0, [x23, 1940]
	add	w0, w0, 1
	str	w0, [x23, 1940]
	cbnz	w24, .L3936
.L4045:
	ldr	x0, [x21]
	ldr	w0, [x0, 960]
	cmp	w0, 1
	beq	.L3937
	mov	x0, x21
	bl	FlushDPB
	cbnz	w0, .L4042
.L4033:
	mov	x0, x21
	bl	InitDPB
	cbnz	w0, .L3980
	ldr	x0, [x21]
	ldr	w0, [x0, 960]
	cmp	w0, 1
	beq	.L3941
.L4034:
	add	x24, x21, 16384
.L3935:
	ldr	w1, [x24, 2616]
	ldr	w0, [x25, 24]
	cmp	w1, w0
	bne	.L3943
	ldrb	w0, [x25, 20]
	cbnz	w0, .L3943
.L3944:
	ldr	w0, [x20, 728]
	ldr	w3, [x24, 788]
	cbz	w0, .L3945
	str	wzr, [x20, 1596]
	str	wzr, [x19, 3520]
.L3945:
	ldr	w0, [x23, 1908]
	cmp	w0, 2
	beq	.L3946
	ldr	x2, [x21]
	ldr	w0, [x2, 24]
	sub	w0, w0, #2
	cmp	w0, 1
	bls	.L3946
	ldr	w1, [x20, 1596]
	ldr	w4, [x20, 1600]
	cmp	w4, w1
	beq	.L3947
	mov	w0, 1
	add	w3, w3, 4
	lsl	w3, w0, w3
	add	w5, w1, w0
	udiv	w0, w5, w3
	msub	w0, w0, w3, w5
	cmp	w4, w0
	beq	.L3983
	ldr	w0, [x2, 656]
	cbnz	w0, .L3948
	ldr	x5, [x2, 696]
	mov	x0, 4294967296
	cmp	x5, x0
	beq	.L4043
.L3949:
	cmp	w4, w1
	bls	.L3950
	ldr	w0, [x24, 1864]
	sub	w1, w4, w1
	cmp	w0, w1
	bcs	.L3948
	ldrb	w0, [x20, 1584]
	cmp	w0, 2
	beq	.L3951
.L3956:
	ldr	w0, [x23, 1976]
	cbnz	w0, .L3948
	mov	x0, x21
	bl	H264_ClearCurrPic
	ldr	x0, .LC966
	ldrb	w0, [x0]
	cbz	w0, .L4044
.L3957:
	ldr	w0, [x20, 1596]
	mov	w2, 6703
	ldr	w3, [x20, 1600]
	ldr	x1, .LC968
	ldr	w4, [x24, 1864]
	sub	w3, w3, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L4012:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L4041:
	ldr	x0, [x21]
	ldr	w0, [x0, 960]
	cmp	w0, 1
	bne	.L4034
	ldr	w0, [x23, 1940]
	add	w0, w0, 1
	str	w0, [x23, 1940]
	cbz	w24, .L4045
	b	.L3936
	.p2align 3
.L4039:
	ldr	x0, [x19, 2680]
	cbz	x0, .L3930
	ldrb	w1, [x0, 1]
	cbz	w1, .L4046
	strb	wzr, [x19, 2024]
.L4054:
	add	x1, x29, 108
	mov	x0, x21
	bl	GetReRangeFlag
	mov	w24, w0
	ldr	w1, [x21, 15012]
	ldr	w0, [x22, 36]
	cmp	w1, w0
	bne	.L3932
.L4040:
	ldrb	w0, [x22, 24]
	cbz	w0, .L3933
	b	.L3932
	.p2align 3
.L3943:
	ldr	x0, .LC960
	mov	x2, 2208
	strb	wzr, [x25, 20]
	mov	x1, x25
	ldr	x3, [x0, 112]
	add	x0, x24, 2592
	blr	x3
	b	.L3944
	.p2align 3
.L3936:
	ldr	x1, .LC980
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x21
	bl	InitDPB
	cbnz	w0, .L3980
.L3941:
	add	x24, x21, 16384
	add	x1, x21, 12288
	add	x3, x23, 636
	ldr	w4, [x24, 1864]
	str	w4, [x23, 640]
	ldr	w0, [x24, 1844]
	ldrb	w26, [x1, 2706]
	mov	w1, 2
	add	w0, w0, 1
	ldr	w27, [x24, 1840]
	sub	w26, w1, w26
	lsl	w0, w0, 4
	add	w27, w27, 1
	mul	w26, w0, w26
	lsl	w27, w27, 4
	mov	x0, x21
	mov	w1, w27
	mov	w2, w26
	bl	H264_ArrangeVahbMem
	cmp	w0, 1
	beq	.L4047
	ldr	x1, [x21]
	mov	w0, -2
	ldr	w1, [x1, 960]
	cmp	w1, 1
	beq	.L4012
	ldr	x1, .LC965
	mov	w0, 0
	str	wzr, [x21, 14932]
	str	wzr, [x21, 14936]
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, x21
	bl	ClearAll
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, -1
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L3983:
	mov	w1, w4
	.p2align 2
.L3947:
	ldr	w0, [x20, 1612]
	cbz	w0, .L3966
	str	w1, [x20, 1596]
.L3966:
	mov	x0, x21
	str	w1, [x20, 768]
	bl	DecPOC
	mov	w1, 0
	mov	x0, x21
	bl	AllocFrameStore
	cbnz	w0, .L4048
	strb	wzr, [x19, 2031]
	mov	w0, 1
	strb	w0, [x19, 2024]
	mov	w1, -1
	mov	w4, 1
	ldrb	w0, [x20, 1587]
	strb	w0, [x19, 2030]
	ldr	w5, [x20, 1600]
	str	w5, [x19, 2696]
	ldr	w3, [x20, 1612]
	str	w3, [x19, 2704]
	ldr	w0, [x20, 748]
	str	w0, [x19, 2708]
	ldr	w0, [x20, 744]
	str	w0, [x19, 2712]
	ldr	w0, [x20, 736]
	str	w0, [x19, 2716]
	ldr	w0, [x20, 740]
	str	w0, [x19, 2720]
	strb	wzr, [x19, 2026]
	strb	wzr, [x19, 2029]
	strb	wzr, [x19, 2028]
	str	w1, [x19, 2752]
	ldrb	w2, [x20, 1585]
	cbz	w2, .L3968
	strb	w4, [x20, 1585]
	mov	w2, w4
	mov	w4, 2
.L3968:
	add	x25, x21, 12288
	ldr	w6, [x24, 1844]
	mov	w1, 2
	ldrb	w0, [x25, 2706]
	sub	w0, w1, w0
	madd	w0, w6, w0, w0
	str	w0, [x19, 2744]
	udiv	w0, w0, w4
	str	w0, [x19, 2740]
	ldr	w1, [x24, 1840]
	add	w1, w1, 1
	str	w1, [x19, 2736]
	mul	w0, w0, w1
	str	w0, [x19, 2748]
	ldrb	w0, [x24, 2592]
	strb	w0, [x19, 2032]
	cbnz	w2, .L3985
	ldrb	w0, [x25, 2707]
	mov	w1, 0
	cbnz	w0, .L4049
.L3969:
	strb	w0, [x19, 2033]
	str	w1, [x23, 1888]
	cbz	w3, .L3970
	str	w5, [x20, 1596]
.L3970:
	add	x2, x21, 24576
	mov	x20, -1
	ldr	x1, .LC974
	mov	w0, 29
	mov	w26, 2
	ldr	w3, [x2, 3180]
	lsl	x2, x3, 6
	sub	x2, x2, x3
	lsl	x2, x2, 2
	sub	x2, x2, x3
	lsl	x2, x2, 1
	sub	x2, x2, x3
	add	x2, x21, x2, lsl 2
	add	x2, x2, 20480
	add	x2, x2, 3268
	str	x2, [x19, 2688]
	ldr	x2, [x21]
	ldr	x3, [x2, 64]
	str	x3, [x19, 2624]
	ldr	x3, [x2, 80]
	str	x3, [x19, 2632]
	ldr	x3, [x2, 96]
	str	x3, [x19, 2640]
	ldr	w3, [x2, 112]
	str	w3, [x19, 2040]
	ldr	w3, [x2, 116]
	str	w3, [x19, 2044]
	ldr	w3, [x2, 120]
	str	w3, [x19, 2048]
	ldr	w3, [x2, 136]
	str	w3, [x19, 2052]
	ldrb	w3, [x2, 56]
	strb	w3, [x19, 2672]
	ldr	w3, [x22, 44]
	str	w3, [x19, 2208]
	ldr	w3, [x22, 48]
	str	w3, [x19, 2212]
	str	x20, [x2, 64]
	ldr	x2, [x19, 2624]
	bl	dprint_vfmw
	ldr	x1, .LC976
	mov	w0, 29
	ldr	x2, [x19, 2632]
	bl	dprint_vfmw
	ldr	w0, [x24, 1840]
	ldr	x1, .LC960
	add	w0, w0, 1
	lsl	w0, w0, 4
	str	w0, [x19, 2108]
	ldr	x3, [x1, 96]
	ldrb	w1, [x25, 2706]
	ldr	w2, [x24, 1844]
	sub	w0, w26, w1
	mov	w1, 0
	madd	w0, w2, w0, w0
	mov	x2, 4
	lsl	w0, w0, 4
	str	w0, [x19, 2112]
	ldr	w0, [x21, 15016]
	ldr	w25, [x24, 1908]
	cmp	w0, 1
	add	x0, x19, 2104
	cset	w27, ne
	and	w25, w25, 7
	blr	x3
	ldrb	w0, [x19, 2104]
	ldrb	w2, [x19, 2105]
	and	w0, w0, 252
	bfi	w0, w27, 2, 3
	strb	w0, [x19, 2104]
	bfi	w2, w26, 0, 2
	ldr	w1, [x24, 1912]
	and	w2, w2, -13
	bfi	w2, w26, 4, 2
	strb	w2, [x19, 2105]
	bfi	w0, w1, 5, 3
	strb	w0, [x19, 2104]
	mov	w1, w25
	add	x0, x19, 2040
	ldr	w2, [x19, 2104]
	bfi	w2, w25, 14, 3
	str	w2, [x19, 2104]
	bl	SetAspectRatio
	ldrb	w2, [x19, 2027]
	ldr	w1, [x23, 1940]
	cmp	w2, wzr
	ldr	x0, [x19, 2680]
	str	w1, [x19, 2196]
	cset	w1, ne
	str	w1, [x19, 2092]
	cbz	x0, .L4050
	ldr	w1, [x19, 2104]
	str	w1, [x0, 80]
	ldr	x0, [x19, 2680]
	ldr	w1, [x19, 2092]
	str	w1, [x0, 68]
	ldr	x0, [x19, 2680]
	ldr	w1, [x19, 2144]
	str	w1, [x0, 120]
	ldr	x0, [x19, 2680]
	ldr	w1, [x19, 2140]
	str	w1, [x0, 116]
	ldr	x0, [x19, 2680]
	ldr	w1, [x19, 2108]
	str	w1, [x0, 84]
	ldr	x0, [x19, 2680]
	ldr	w1, [x19, 2112]
	str	w1, [x0, 88]
	ldr	x1, [x19, 2680]
	ldr	w0, [x22, 3284]
	str	w0, [x1, 100]
	str	w0, [x19, 2124]
	ldr	x1, [x19, 2680]
	ldr	w0, [x22, 3288]
	str	w0, [x1, 104]
	str	w0, [x19, 2128]
	ldr	x1, [x19, 2680]
	ldr	w0, [x22, 3276]
	str	w0, [x1, 92]
	str	w0, [x19, 2116]
	ldr	x1, [x19, 2680]
	ldr	w0, [x22, 3280]
	str	w0, [x1, 96]
	str	w0, [x19, 2120]
	ldr	x1, [x19, 2680]
	ldr	w0, [x23, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_GetDispPhyFs
	cbz	x0, .L3972
	ldr	w3, [x19, 2092]
	mov	w1, 0
	ldr	w2, [x0, 4]
	cmp	w3, wzr
	ldr	w0, [x23, 1980]
	cset	w3, ne
	bl	FSP_SetStoreType
.L3972:
	ldr	w1, [x23, 664]
	add	x2, x19, 2584
	add	x5, x19, 2616
.L3976:
	ldr	x0, [x2]
	cbz	x0, .L4051
.L3973:
	add	x2, x2, 8
	cmp	x5, x2
	bne	.L3976
	cbz	w1, .L3978
	cmp	w1, wzr
	ble	.L3978
	.p2align 2
.L3979:
	add	x22, x21, x1, sxtw 3
	sub	w20, w1, #1
	add	x22, x22, 65536
	ldr	w0, [x23, 1980]
	ldr	x1, [x22, 664]
	bl	FreeUsdByDec
	str	xzr, [x22, 664]
	mov	w1, w20
	cbnz	w20, .L3979
.L3978:
	str	wzr, [x23, 664]
	mov	x0, x21
	str	wzr, [x19, 2724]
	bl	CalcPicNum
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mov	w0, 0
	ldp	x29, x30, [sp], 112
	ret
.L3951:
	cbnz	w4, .L3953
	sub	w3, w3, #1
.L3954:
	mov	x0, x21
	str	w3, [x20, 1596]
	bl	FlushDPB
	cbnz	w0, .L4052
	ldrb	w0, [x20, 1584]
	cmp	w0, 2
	bne	.L3956
	.p2align 2
.L3948:
	mov	x0, x21
	bl	DecGap
	cbnz	w0, .L4053
.L3946:
	ldr	w1, [x20, 1600]
	b	.L3947
	.p2align 3
.L4051:
	cbz	w1, .L3973
	ldr	x0, [x23, 672]
	subs	w1, w1, #1
	str	x0, [x2]
	beq	.L3974
	add	x4, x23, 672
	mov	w3, 0
	.p2align 2
.L3975:
	add	w0, w3, 1
	mov	x3, x0
	cmp	w0, w1
	add	x0, x0, 8192
	add	x0, x0, 84
	ldr	x0, [x21, x0, lsl 3]
	str	x0, [x4], 8
	bne	.L3975
.L3974:
	uxtw	x0, w1
	add	x0, x0, 8192
	add	x0, x0, 84
	str	xzr, [x21, x0, lsl 3]
	str	w1, [x23, 664]
	b	.L3973
	.p2align 3
.L3985:
	mov	w1, 0
	mov	w0, 0
	b	.L3969
	.p2align 3
.L3937:
	ldr	x1, .LC980
	mov	w0, 22
	bl	dprint_vfmw
	b	.L4033
	.p2align 3
.L4049:
	mov	w1, 1
	mov	w0, w1
	b	.L3969
	.p2align 3
.L4046:
	ldr	w1, [x0, 656]
	mov	w2, 1
	ldr	w0, [x23, 1980]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 2680]
	strb	wzr, [x0, 1]
	ldr	x0, [x19, 2680]
	strb	wzr, [x0, 4]
	strb	wzr, [x19, 2024]
	b	.L4054
	.p2align 3
.L4047:
	lsr	w27, w27, 4
	lsr	w26, w26, 4
	str	w27, [x21, 14932]
	str	w26, [x21, 14936]
	b	.L3935
	.p2align 3
.L3950:
	sub	w0, w4, w1
	ldr	w1, [x24, 1864]
	add	w0, w0, w3
	cmp	w1, w0
	bcs	.L3948
	ldrb	w0, [x20, 1584]
	cmp	w0, 2
	beq	.L3958
.L3963:
	ldr	w0, [x23, 1976]
	cbnz	w0, .L3948
	mov	x0, x21
	bl	H264_ClearCurrPic
	ldr	x0, .LC966
	ldrb	w0, [x0]
	cbz	w0, .L4055
.L3964:
	ldr	w0, [x20, 1596]
	mov	w2, 6736
	ldr	w3, [x20, 1600]
	ldr	x1, .LC968
	ldr	w4, [x24, 1864]
	sub	w3, w3, w0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4012
	.p2align 3
.L3980:
	ldr	x1, .LC963
	mov	w3, w0
	mov	w2, 6607
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4012
.L4053:
	ldr	x1, .LC970
	mov	w2, 6746
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4012
	.p2align 3
.L3930:
	ldr	x2, .LC957
	mov	w3, 6570
	ldr	x1, .LC959
	mov	w0, 22
	add	x2, x2, 328
	bl	dprint_vfmw
	strb	wzr, [x19, 2024]
	b	.L4054
.L4043:
	ldr	w0, [x2, 704]
	cbnz	w0, .L3949
	ldr	w0, [x2, 660]
	add	w0, w0, 1024
	cmp	w0, 2048
	bhi	.L3948
	b	.L3949
.L4048:
	ldr	x1, .LC972
	mov	w2, 6765
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4012
.L3958:
	cbnz	w4, .L3960
	sub	w3, w3, #1
.L3961:
	mov	x0, x21
	str	w3, [x20, 1596]
	bl	FlushDPB
	cbnz	w0, .L4056
	ldrb	w0, [x20, 1584]
	cmp	w0, 2
	beq	.L3948
	b	.L3963
	.p2align 3
.L4050:
	ldr	x2, .LC957
	mov	w3, 6843
	ldr	x1, .LC978
	mov	w0, 22
	add	x2, x2, 328
	bl	dprint_vfmw
	mov	w0, w20
	b	.L4012
.L4042:
	ldr	x1, .LC961
	mov	w3, w0
	mov	w2, 6599
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4012
.L3953:
	sub	w3, w4, #1
	b	.L3954
.L3960:
	sub	w3, w4, #1
	b	.L3961
.L4038:
	ldr	x2, .LC955
	mov	w3, 6537
	ldr	x1, .LC956
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4012
.L4056:
	ldr	x1, .LC961
	mov	w3, w0
	mov	w2, 6720
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4012
.L4055:
	mov	x0, x21
	bl	ClearDPB
	b	.L3964
.L4044:
	mov	x0, x21
	bl	ClearDPB
	b	.L3957
.L4052:
	ldr	x1, .LC961
	mov	w3, w0
	mov	w2, 6687
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4012
	.size	InitPic, .-InitPic
	.align	3
.LC955:
	.xword	.LC30
	.align	3
.LC956:
	.xword	.LC32
	.align	3
.LC957:
	.xword	.LANCHOR2
	.align	3
.LC959:
	.xword	.LC958
	.align	3
.LC960:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC961:
	.xword	.LC866
	.align	3
.LC963:
	.xword	.LC962
	.align	3
.LC965:
	.xword	.LC964
	.align	3
.LC966:
	.xword	g_apple_airplay_mirrorinig_flag
	.align	3
.LC968:
	.xword	.LC967
	.align	3
.LC970:
	.xword	.LC969
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecSlice
	.type	H264_DecSlice, %function
H264_DecSlice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L4111
	add	x20, x19, 65536
	ldr	x1, .LC983
	mov	w0, 22
	add	x21, x19, 20480
	ldr	w2, [x20, 1924]
	sub	w2, w2, #1
	bl	dprint_vfmw
	ldr	x0, [x19, 632]
	ldr	x2, .LC984
	ldrb	w1, [x0, 2]
	strb	w1, [x21, 1587]
	ldr	w0, [x0, 84]
	str	w0, [x21, 1612]
	ldrsw	x0, [x20, 1980]
	ldr	x0, [x2, x0, lsl 3]
	ldrsb	w2, [x0, 44]
	cmp	w2, 1
	beq	.L4112
.L4060:
	mov	x0, x19
	bl	ProcessSliceHeaderFirstPart
	cbnz	w0, .L4110
	mov	x0, x19
	bl	ProcessSliceHeaderSecondPart
	cbnz	w0, .L4110
	ldr	w2, [x20, 1904]
	mov	w3, 0
	add	x22, x19, 61440
	cbz	w2, .L4066
	sub	w9, w2, #1
	add	x22, x19, 61440
	add	x9, x9, 4096
	add	x4, x22, 3576
	add	x9, x9, 4032
	mov	w10, 0
	mov	w3, 0
	mov	x0, 0
	add	x9, x19, x9, lsl 3
	.p2align 2
.L4074:
	ldr	x1, [x4]
	ldr	x6, [x1, 8]
	cbz	x6, .L4088
	ldr	x5, [x1, 40]
	ldr	w7, [x1, 16]
	cbz	x5, .L4089
.L4119:
	ldr	w1, [x1, 48]
.L4069:
	cbz	x0, .L4070
	cmp	x6, x0
	mov	w8, w7
	bls	.L4071
	sub	x0, x6, x0
	sub	w0, w0, w10
	add	w8, w0, w7
.L4071:
	add	w3, w1, w3
	add	w3, w8, w3
.L4072:
	cbz	x5, .L4113
	mov	x0, x5
	mov	w10, w1
.L4073:
	add	x4, x4, 8
	cmp	x9, x4
	bne	.L4074
.L4066:
	str	w3, [x20, 1964]
	ldr	w0, [x22, 2736]
	ldr	w4, [x22, 2740]
	mul	w4, w0, w4
	cmp	w4, 1620
	bgt	.L4114
	lsl	w0, w4, 2
	mov	w1, 32769
	sub	w4, w0, w4
	mov	w0, 16384
	lsl	w4, w4, 8
	cmp	w4, w1
	asr	w4, w4, 1
	csel	w4, w4, w0, gt
.L4076:
	ldr	w0, [x19, 14940]
	cmp	w0, w2
	bls	.L4077
	cmp	w4, w3
	bcc	.L4077
	ldrb	w0, [x21, 1589]
	cbz	w0, .L4080
	ldr	x1, .LC992
	mov	w0, 2
	bl	dprint_vfmw
	ldrb	w0, [x21, 1587]
	cmp	w0, 5
	ldr	w0, [x20, 1944]
	beq	.L4115
.L4082:
	add	w0, w0, 1
	str	wzr, [x20, 1960]
	str	w0, [x20, 1944]
	ldrb	w0, [x22, 2027]
	cbnz	w0, .L4083
	ldr	w0, [x20, 1948]
	add	w0, w0, 1
	str	w0, [x20, 1948]
.L4084:
	mov	x0, x19
	bl	InitPic
	cmn	w0, #2
	beq	.L4059
	cbnz	w0, .L4116
	mov	x0, x19
	bl	WritePicMsg
.L4080:
	mov	x0, x19
	bl	PicTypeStatistic
	mov	x0, x19
	bl	DecList
	cbnz	w0, .L4117
	mov	x0, x19
	bl	IsRefListWrong
	cbnz	w0, .L4118
	mov	x0, x19
	bl	ExitSlice
	mov	x0, x19
	bl	CalcStreamBits
	mov	x0, x19
	bl	WriteSliceMsg
	ldr	w1, [x20, 1960]
	mov	w2, 1
	mov	w0, 0
	str	w2, [x20, 644]
	add	w1, w1, w2
	str	w1, [x20, 1960]
.L4059:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L4113:
	mov	x0, x6
	mov	w10, w7
	b	.L4073
	.p2align 3
.L4070:
	add	w3, w7, w3
	add	w3, w3, w1
	b	.L4072
	.p2align 3
.L4088:
	ldr	x5, [x1, 40]
	mov	w7, 0
	cbnz	x5, .L4119
	.p2align 2
.L4089:
	mov	w1, 0
	b	.L4069
	.p2align 3
.L4114:
	lsl	w4, w4, 8
	b	.L4076
	.p2align 3
.L4112:
	ldr	x2, [x0, 160]
	mov	x0, 1
	movk	x0, 0x2, lsl 32
	cmp	x2, x0
	bne	.L4060
	cmp	w1, 5
	bne	.L4060
	ldr	x0, [x19]
	ldr	x0, [x0, 64]
	cmn	x0, #1
	beq	.L4060
	ldr	x1, [x19, 27840]
	str	x0, [x19, 27872]
	str	x1, [x19, 27880]
	b	.L4060
	.p2align 3
.L4083:
	ldr	w0, [x20, 1952]
	add	w0, w0, 1
	str	w0, [x20, 1952]
	b	.L4084
	.p2align 3
.L4115:
	str	w0, [x20, 1956]
	b	.L4082
.L4110:
	ldr	x1, .LC985
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC986
	ldr	x4, [x0]
	cbz	x4, .L4108
	add	x2, x29, 64
	ldr	w0, [x20, 1980]
	mov	w5, -1
	mov	w3, 4
	mov	w1, 100
	str	w5, [x2, -8]!
	blr	x4
.L4108:
	mov	x0, x19
	bl	ClearCurrSlice
	mov	w0, -1
	b	.L4059
.L4077:
	ldr	x1, .LC988
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x19, 14940]
	ldr	w2, [x20, 1904]
	cmp	w2, w1
	bcc	.L4079
	ldr	x0, .LC986
	ldr	x4, [x0]
	cbz	x4, .L4079
	ldr	w0, [x20, 1980]
	mov	w3, 8
	stp	w2, w1, [x29, 56]
	add	x2, x29, 56
	mov	w1, 108
	blr	x4
.L4079:
	ldr	x1, .LC990
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	H264_ClearCurrPic
	mov	w0, -1
	b	.L4059
.L4117:
	ldr	x1, .LC996
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4059
.L4118:
	ldr	x1, .LC998
	mov	w0, 1
	ldr	w2, [x22, 2708]
	bl	dprint_vfmw
	b	.L4108
.L4116:
	ldr	x1, .LC994
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4059
.L4111:
	ldr	x2, .LC981
	mov	w3, 9000
	ldr	x1, .LC982
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4059
	.size	H264_DecSlice, .-H264_DecSlice
	.align	3
.LC981:
	.xword	.LC30
	.align	3
.LC982:
	.xword	.LC32
	.align	3
.LC983:
	.xword	.LC815
	.align	3
.LC984:
	.xword	s_pstVfmwChan
	.align	3
.LC985:
	.xword	.LC817
	.align	3
.LC986:
	.xword	g_event_report
	.align	3
.LC988:
	.xword	.LC987
	.align	3
.LC990:
	.xword	.LC989
	.align	3
.LC992:
	.xword	.LC991
	.align	3
.LC994:
	.xword	.LC993
	.align	3
.LC996:
	.xword	.LC995
	.align	3
.LC998:
	.xword	.LC997
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264_DecOneNal
	.type	H264_DecOneNal, %function
H264_DecOneNal:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x20, .L4257
	ldr	x3, [x20, 632]
	add	x19, x20, 65536
	ldr	w0, [x3, 76]
	cbz	w0, .L4127
	ldr	w2, [x19, 1964]
	mov	w0, 0
	.p2align 2
.L4126:
	ubfiz	x1, x0, 5, 32
	add	w0, w0, 1
	add	x1, x3, x1
	ldr	w1, [x1, 16]
	add	w2, w2, w1
	str	w2, [x19, 1964]
	ldr	w1, [x3, 76]
	cmp	w1, w0
	bhi	.L4126
.L4127:
	strb	wzr, [x3]
	ldr	x0, .LC999
	ldrsw	x1, [x19, 1980]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w1, [x0, 44]
	cmp	w1, 1
	beq	.L4272
.L4125:
	add	x23, x20, 12288
	mov	w1, 32
	add	x0, x23, 2600
	bl	BsGet
	mov	w22, w0
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 72]
	add	w0, w0, 32
	str	w0, [x1, 72]
.L4128:
	ldr	x4, [x20, 632]
	and	w0, w22, 31
	ubfx	x2, x22, 5, 2
	ubfx	x3, x22, 7, 1
	ldr	x1, .LC1001
	strb	w0, [x4, 2]
	ldr	x0, [x20, 632]
	str	w2, [x0, 84]
	mov	w0, 22
	ldr	x2, [x20, 632]
	str	w3, [x2, 88]
	str	wzr, [x19, 1920]
	ldr	w2, [x19, 1924]
	ldr	x3, [x20, 632]
	ldrb	w3, [x3, 2]
	bl	dprint_vfmw
	ldr	w0, [x19, 1924]
	cmp	w0, 371
	beq	.L4273
	add	w0, w0, 1
	str	w0, [x19, 1924]
	ldr	x0, [x20, 632]
	ldrb	w2, [x0, 2]
	cmp	w2, 20
	beq	.L4274
.L4130:
	sub	w0, w2, #1
	cmp	w0, 29
	bls	.L4275
.L4135:
	ldr	x1, .LC1044
	mov	w3, w22
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x2, [x20, 632]
	mov	w0, 0
	ldr	x1, .LC1046
	ldrb	w2, [x2, 2]
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L4161
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4161:
	ldr	x0, .LC1015
	ldr	x4, [x0]
	cbz	x4, .L4258
.L4262:
	ldr	w0, [x19, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4258:
	mov	w0, 0
.L4122:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4275:
	ldr	x1, .LC1010
	ldrh	w0, [x1,w0,uxtw #1]
	adr	x1, .Lrtx4137
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx4137:
	.section	.rodata
	.align	0
	.align	2
.L4137:
	.2byte	(.L4136 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4136 - .Lrtx4137) / 4
	.2byte	(.L4138 - .Lrtx4137) / 4
	.2byte	(.L4139 - .Lrtx4137) / 4
	.2byte	(.L4140 - .Lrtx4137) / 4
	.2byte	(.L4141 - .Lrtx4137) / 4
	.2byte	(.L4142 - .Lrtx4137) / 4
	.2byte	(.L4143 - .Lrtx4137) / 4
	.2byte	(.L4144 - .Lrtx4137) / 4
	.2byte	(.L4145 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4139 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4146 - .Lrtx4137) / 4
	.2byte	(.L4136 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4135 - .Lrtx4137) / 4
	.2byte	(.L4147 - .Lrtx4137) / 4
	.text
	.p2align 3
.L4272:
	mov	x1, 1
	ldr	x2, [x0, 160]
	movk	x1, 0x2, lsl 32
	cmp	x2, x1
	bne	.L4125
	ldr	w0, [x0, 156]
	cmp	w0, 1
	ccmp	w21, wzr, 0, eq
	bne	.L4125
	add	x23, x20, 12288
	mov	w1, 40
	add	x22, x23, 2600
	mov	x0, x22
	bl	BsSkip
	mov	w1, 8
	mov	x0, x22
	bl	BsGet
	mov	w22, w0
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 72]
	add	w0, w0, 48
	str	w0, [x1, 72]
	b	.L4128
.L4146:
	ldr	x1, .LC1040
	mov	w2, 19
	mov	w0, 22
	bl	dprint_vfmw
.L4267:
	ldr	x1, [x20, 632]
	cbz	x1, .L4258
.L4259:
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L4145:
	ldr	x1, .LC1038
	mov	w2, 13
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbnz	x1, .L4259
	b	.L4258
.L4144:
	ldr	x1, .LC1034
	mov	w2, 12
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbnz	x1, .L4259
	b	.L4258
.L4143:
	ldr	x1, .LC1036
	mov	w2, 11
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	H264_IsEosNal
	uxtb	w1, w0
	cmp	w1, 1
	bne	.L4267
	ldr	x21, .LC1015
	strb	w0, [x23, 2640]
	ldr	x4, [x21]
	cbz	x4, .L4157
	ldr	w0, [x19, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 117
	blr	x4
.L4157:
	mov	x0, x20
	str	wzr, [x20, 624]
	bl	DecVDM
	cbz	w0, .L4267
	ldr	x1, [x20, 632]
	cbz	x1, .L4269
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
	b	.L4269
.L4142:
	ldr	x1, .LC1032
	mov	w2, 10
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbnz	x1, .L4259
	b	.L4258
.L4141:
	ldr	x1, .LC1030
	mov	w2, 9
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbnz	x1, .L4259
	b	.L4258
.L4147:
	ldr	x1, .LC1042
	mov	w2, 30
	mov	w0, 22
	bl	dprint_vfmw
	cbnz	w21, .L4159
	ldr	x1, [x20, 632]
	cbz	x1, .L4159
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4159:
	add	x23, x23, 2600
	mov	w1, 32
	mov	x0, x23
	bl	BsGet
	mov	w21, w0
	mov	w1, 32
	mov	x0, x23
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w21, w2
	ccmp	w0, w1, 0, eq
	bne	.L4258
	ldr	x21, .LC1015
	ldr	x4, [x21]
	cbz	x4, .L4160
	ldr	w0, [x19, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 112
	blr	x4
.L4160:
	mov	x0, x20
	str	wzr, [x20, 624]
	bl	DecVDM
	cbz	w0, .L4258
.L4269:
	ldr	x4, [x21]
	cbz	x4, .L4257
.L4261:
	ldr	w0, [x19, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L4257:
	mov	w0, -1
.L4278:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L4140:
	ldr	x1, .LC1017
	mov	w2, 8
	ldr	w3, [x19, 1932]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	H264_DecPPS
	mov	w21, w0
	ldr	x1, [x20, 632]
	cbz	x1, .L4150
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4150:
	cbnz	w21, .L4276
	ldr	w1, [x19, 1932]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 1932]
	b	.L4122
.L4138:
	ldr	x1, .LC1026
	mov	w2, 6
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	H264_DecSEI
	mov	w21, w0
	ldr	x1, [x20, 632]
	cbz	x1, .L4154
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4154:
	cbz	w21, .L4258
	ldr	x1, .LC1028
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC1015
	ldr	x4, [x0]
	cbnz	x4, .L4262
	b	.L4258
.L4136:
	ldr	x1, .LC1012
	mov	w0, 22
	ldr	w3, [x19, 1936]
	bl	dprint_vfmw
	ldr	x2, [x20, 632]
	add	x1, x20, 20480
	mov	x0, x20
	ldrb	w3, [x2, 2]
	strb	w3, [x1, 1587]
	ldr	w2, [x2, 84]
	str	w2, [x1, 1612]
	bl	SliceCheck
	cbnz	w0, .L4277
	mov	x0, x20
	bl	H264_DecSlice
	cmn	w0, #2
	beq	.L4122
	cbz	w0, .L4258
	ldr	x0, .LC1015
	ldr	x4, [x0]
	cbnz	x4, .L4261
	mov	w0, -1
	b	.L4278
	.p2align 3
.L4139:
	ldr	x1, .LC1022
	mov	w0, 22
	ldr	w3, [x19, 1928]
	bl	dprint_vfmw
	mov	x0, x20
	bl	H264_DecSPS
	mov	w21, w0
	ldr	x1, [x20, 632]
	cbz	x1, .L4152
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
.L4152:
	cbnz	w21, .L4279
	ldr	w1, [x19, 1928]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x19, 1928]
	b	.L4122
	.p2align 3
.L4273:
	ldr	x1, .LC1003
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x19, 1924]
	add	w0, w0, 1
	str	w0, [x19, 1924]
	ldr	x0, [x20, 632]
	ldrb	w2, [x0, 2]
	cmp	w2, 20
	bne	.L4130
	.p2align 2
.L4274:
	mov	w1, 24
	add	x0, x23, 2600
	bl	BsGet
	mov	w22, w0
	ldr	x1, [x20, 632]
	ubfx	x2, x22, 23, 1
	add	x0, x20, 61440
	strb	w2, [x1, 3]
	ldr	x2, [x20, 632]
	ldrb	w1, [x2, 3]
	cbz	w1, .L4131
	ubfx	x1, x22, 16, 6
	strb	w1, [x0, 3561]
	ubfx	x1, x22, 12, 3
	ubfx	x3, x22, 22, 1
	strb	w1, [x0, 3563]
	ubfx	x1, x22, 5, 3
	ubfx	x4, x22, 15, 1
	strb	w3, [x0, 3560]
	strb	w1, [x0, 3565]
	ubfx	x3, x22, 8, 4
	ubfx	x1, x22, 3, 1
	strb	w4, [x0, 3562]
	strb	w3, [x0, 3564]
	ubfx	x4, x22, 4, 1
	ubfx	x3, x22, 2, 1
	strb	w1, [x0, 3567]
	strb	w4, [x0, 3566]
	and	w1, w22, 3
	strb	w3, [x0, 3568]
	strb	w1, [x0, 3569]
.L4131:
	mov	x1, 16711680
	ldr	x3, [x0, 3560]
	movk	x1, 0xff, lsl 32
	and	x1, x3, x1
	cmp	x1, 65536
	beq	.L4132
	ldrb	w3, [x0, 3562]
	ldrb	w2, [x0, 3564]
	mov	w0, 1
	ldr	x1, .LC1005
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	cbz	x1, .L4257
	ldr	w0, [x19, 1980]
	bl	ReleaseNAL
	str	xzr, [x20, 632]
	mov	w0, -1
	b	.L4122
.L4132:
	ldrb	w1, [x0, 3560]
	cmp	w1, 1
	beq	.L4280
.L4134:
	ldrb	w4, [x0, 3565]
	ldrb	w3, [x0, 3563]
	ldrb	w2, [x0, 3564]
	mov	w0, 22
	ldr	x1, .LC1007
	bl	dprint_vfmw
	ldr	x1, .LC1009
	mov	w2, w22
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x1, [x20, 632]
	ldr	w0, [x1, 72]
	add	w0, w0, 24
	str	w0, [x1, 72]
	ldr	x0, [x20, 632]
	ldrb	w2, [x0, 2]
	b	.L4130
.L4277:
	ldr	x1, .LC1014
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x20
	bl	ClearCurrSlice
	ldr	x0, .LC1015
	ldr	x4, [x0]
	cbnz	x4, .L4261
	mov	w0, -1
	b	.L4278
.L4276:
	ldr	x2, .LC1018
	mov	w0, 1
	ldr	x1, .LC1020
	add	x2, x2, 336
	bl	dprint_vfmw
	ldr	x21, .LC1015
	ldr	x4, [x21]
	cbz	x4, .L4257
.L4265:
	add	x2, x29, 80
	ldr	w0, [x19, 1980]
	mov	w20, -1
	mov	w3, 4
	mov	w1, 100
	str	w20, [x2, -8]!
	blr	x4
	ldr	x4, [x21]
	cbz	x4, .L4257
	ldr	w0, [x19, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, w20
	b	.L4122
.L4279:
	ldr	x1, .LC1024
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, .LC1015
	ldr	x4, [x21]
	cbnz	x4, .L4265
	mov	w0, -1
	b	.L4278
.L4280:
	mov	w1, 5
	strb	w1, [x2, 2]
	b	.L4134
	.size	H264_DecOneNal, .-H264_DecOneNal
	.align	3
.LC999:
	.xword	s_pstVfmwChan
	.align	3
.LC1001:
	.xword	.LC1000
	.align	3
.LC1003:
	.xword	.LC1002
	.align	3
.LC1005:
	.xword	.LC1004
	.align	3
.LC1007:
	.xword	.LC1006
	.align	3
.LC1009:
	.xword	.LC1008
	.align	3
.LC1010:
	.xword	.L4137
	.align	3
.LC1012:
	.xword	.LC1011
	.align	3
.LC1014:
	.xword	.LC1013
	.align	3
.LC1015:
	.xword	g_event_report
	.align	3
.LC1017:
	.xword	.LC1016
	.align	3
.LC1018:
	.xword	.LANCHOR2
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
	.align	3
.LC1040:
	.xword	.LC1039
	.align	3
.LC1042:
	.xword	.LC1041
	.align	3
.LC1044:
	.xword	.LC1043
	.align	3
.LC1046:
	.xword	.LC1045
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_DecodePacket
	.type	H264DEC_DecodePacket, %function
H264DEC_DecodePacket:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	str	wzr, [x29, 84]
	stp	wzr, wzr, [x29, 76]
	cbz	x19, .L4334
	cbz	x21, .L4335
	ldr	x0, [x19]
	add	x20, x19, 65536
	ldr	w2, [x0, 8]
	ldr	w1, [x20, 648]
	ubfiz	w2, w2, 16, 3
	str	w2, [x20, 1968]
	cmp	w1, 1
	ldr	w1, [x0]
	str	w1, [x20, 1972]
	ldr	w1, [x0, 4]
	str	w1, [x20, 1976]
	str	wzr, [x20, 1920]
	beq	.L4285
	ldr	w1, [x0, 912]
	cmp	w1, 1
	beq	.L4336
.L4286:
	mov	x1, x21
	mov	x0, x19
	bl	ReceivePacket
	mov	w1, w0
	ldr	x0, [x19, 632]
	str	x0, [x20, 2016]
.L4288:
	str	wzr, [x20, 648]
	mov	w0, 0
	cbz	w1, .L4337
.L4325:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4336:
	ldr	w0, [x0, 960]
	cmp	w0, 1
	bne	.L4286
	ldr	w0, [x20, 2012]
	cmp	w0, 1
	bne	.L4286
	ldr	x0, [x20, 2016]
	str	x0, [x19, 632]
	str	wzr, [x20, 648]
	str	wzr, [x20, 2012]
	b	.L4287
	.p2align 3
.L4337:
	ldr	x0, [x19, 632]
.L4287:
	str	wzr, [x0, 72]
	add	x21, x19, 12288
	add	x21, x21, 2600
	ldr	x1, [x19, 632]
	mov	x0, x21
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	ldr	x0, .LC1049
	ldrsw	x1, [x20, 1980]
	ldr	x0, [x0, x1, lsl 3]
	ldrsb	w22, [x0, 44]
	cmp	w22, 1
	beq	.L4289
.L4291:
	mov	w22, 0
.L4290:
	mov	w1, 32
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	ldr	x3, [x19, 632]
	and	w2, w0, 31
	mov	w1, 27
	and	w1, w0, w1
	ubfx	x0, x0, 5, 2
	strb	w2, [x3, 2]
	cmp	w1, 1
	ccmp	w2, 20, 4, ne
	ldr	x1, [x19, 632]
	str	w0, [x1, 84]
	beq	.L4338
.L4292:
	mov	x0, x19
	bl	FindTrailZeros
	cbnz	w0, .L4339
	ldr	x1, [x19, 632]
	mov	x0, x21
	str	wzr, [x1, 72]
	ldr	x1, [x19, 632]
	ldr	w2, [x1, 16]
	ldr	x1, [x1, 8]
	bl	BsInit
	mov	w1, w22
	mov	x0, x19
	bl	H264_DecOneNal
	cmn	w0, #2
	beq	.L4325
	cbnz	w0, .L4340
	add	x19, x19, 61440
	mov	w0, 0
	str	wzr, [x19, 2764]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L4285:
	ldr	x0, [x19, 632]
	cmp	x0, xzr
	csetm	w1, eq
	b	.L4288
	.p2align 3
.L4338:
	cmp	w2, 20
	beq	.L4341
.L4293:
	add	x2, x29, 92
	add	x1, x29, 88
	mov	x0, x19
	bl	InquireSliceProperty
	cbz	w0, .L4342
	ldr	x1, [x19, 632]
	cbz	x1, .L4304
	ldr	w0, [x20, 1980]
	bl	ReleaseNAL
	str	xzr, [x19, 632]
.L4304:
	ldr	x0, .LC1052
	ldr	x4, [x0]
	cbz	x4, .L4332
	ldr	w0, [x20, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	mov	w0, -1
	b	.L4325
	.p2align 3
.L4342:
	ldr	w1, [x29, 88]
	ldr	w0, [x20, 1992]
	cmp	w1, 1
	csinc	w0, w0, w0, ne
	str	w0, [x20, 1992]
	beq	.L4343
.L4295:
	ldr	w0, [x29, 92]
	cmp	w0, 1
	bne	.L4292
	mov	x0, x19
	bl	FlushDPB
	cbnz	w0, .L4344
.L4302:
	ldr	w0, [x20, 1980]
	bl	FSP_GetFspType
	cbnz	w0, .L4292
	ldr	w0, [x20, 1980]
	add	x3, x29, 84
	add	x2, x29, 80
	add	x1, x29, 76
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19]
	ldr	w0, [x0, 772]
	cmp	w0, 1
	bne	.L4292
	ldr	w0, [x29, 84]
	cmp	w0, wzr
	ble	.L4345
	.p2align 2
.L4299:
	mov	w1, 1
	mov	w0, -2
	str	w1, [x20, 648]
	b	.L4325
	.p2align 3
.L4289:
	ldp	w1, w2, [x0, 156]
	ldr	w3, [x0, 164]
	mov	x0, x19
	bl	H264_VES_Splitter
	cmp	w0, 3
	beq	.L4290
	cbnz	w0, .L4325
	b	.L4291
	.p2align 3
.L4341:
	mov	x0, x19
	bl	InquireSliceExtProperty
	b	.L4293
.L4339:
	ldr	x1, .LC1054
	mov	w0, 22
	bl	dprint_vfmw
.L4332:
	mov	w0, -1
	b	.L4325
	.p2align 3
.L4343:
	add	x23, x19, 20480
	ldrb	w0, [x23, 1585]
	cmp	w0, 1
	ldr	w0, [x20, 1996]
	beq	.L4346
	add	w0, w0, 2
	str	w0, [x20, 1996]
.L4297:
	ldr	w0, [x20, 1904]
	cbz	w0, .L4295
	ldr	x3, [x19, 632]
	mov	w2, 20
	ldr	x1, .LC1050
	mov	x0, x21
	add	x1, x1, 432
	str	wzr, [x3, 72]
	bl	BsInit
	mov	w1, 1
	mov	x0, x19
	bl	H264_DecOneNal
	ldrb	w0, [x23, 1585]
	cmp	w0, 1
	ldr	w0, [x20, 1996]
	beq	.L4347
	sub	w0, w0, #2
	str	w0, [x20, 1996]
	b	.L4299
.L4346:
	add	w0, w0, 1
	str	w0, [x20, 1996]
	b	.L4297
.L4344:
	ldr	x1, .LC1051
	mov	w3, w0
	mov	w2, 13318
	mov	w0, 0
	bl	dprint_vfmw
	b	.L4302
.L4334:
	ldr	x2, .LC1047
	mov	w3, 13197
	ldr	x1, .LC1048
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4325
.L4335:
	ldr	x2, .LC1047
	mov	w3, 13198
	ldr	x1, .LC1048
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4325
.L4340:
	ldr	x1, .LC1056
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4325
.L4347:
	sub	w0, w0, #1
	str	w0, [x20, 1996]
	b	.L4299
.L4345:
	ldr	w0, [x29, 80]
	cmp	w0, 32
	bgt	.L4299
	ldr	x0, [x19, 616]
	cbnz	x0, .L4299
	ldr	w0, [x20, 1944]
	cbz	w0, .L4292
	ldr	w0, [x19, 14932]
	cbz	w0, .L4292
	ldr	w1, [x19, 14936]
	ldr	w2, [x20, 2024]
	cmp	w1, w2
	beq	.L4292
	ldr	w2, [x20, 2028]
	cmp	w0, w2
	beq	.L4292
	ldr	x2, .LC1052
	str	w1, [x20, 2024]
	str	w0, [x20, 2028]
	ldr	x4, [x2]
	cbz	x4, .L4292
	ldr	w0, [x20, 1980]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L4292
	.size	H264DEC_DecodePacket, .-H264DEC_DecodePacket
	.align	3
.LC1047:
	.xword	.LC30
	.align	3
.LC1048:
	.xword	.LC32
	.align	3
.LC1049:
	.xword	s_pstVfmwChan
	.align	3
.LC1050:
	.xword	.LANCHOR1
	.align	3
.LC1051:
	.xword	.LC866
	.align	3
.LC1052:
	.xword	g_event_report
	.align	3
.LC1054:
	.xword	.LC1053
	.align	3
.LC1056:
	.xword	.LC1055
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_GetRemainImg
	.type	H264DEC_GetRemainImg, %function
H264DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L4349
	add	x20, x21, 24576
	mov	w19, 0
	ldr	w0, [x20, 3708]
	cbnz	w0, .L4368
	b	.L4351
	.p2align 3
.L4353:
	ldr	w0, [x20, 3708]
	cmp	w0, w19
	bls	.L4351
.L4368:
	add	x0, x21, x19, uxtw 3
	add	w19, w19, 1
	ldr	x1, [x0, 27896]
	ldrb	w0, [x1, 2]
	cbz	w0, .L4353
	mov	x0, x21
	bl	UnMarkFrameStoreRef
	ldr	w0, [x20, 3708]
	cmp	w0, w19
	bhi	.L4368
	.p2align 2
.L4351:
	mov	x0, x21
	bl	RemoveUnUsedFrameStore
	cbnz	w0, .L4351
	mov	w23, -1
	.p2align 2
.L4356:
	ldr	w5, [x20, 3708]
	cbz	w5, .L4374
.L4362:
	ldr	w0, [x20, 3704]
	cmp	w5, w0
	bls	.L4357
	str	w0, [x20, 3708]
	cbz	w0, .L4363
	mov	w5, w0
.L4357:
	add	x1, x20, 3320
	mov	w4, 2147483647
	mov	w0, 0
	mov	w19, 0
	.p2align 2
.L4360:
	ldr	x3, [x1]
	add	x1, x1, 8
	ldr	w2, [x3, 672]
	cmp	w2, w4
	bge	.L4359
	ldrb	w3, [x3, 4]
	cmp	w3, wzr
	csel	w4, w4, w2, eq
	csel	w19, w19, w0, eq
.L4359:
	add	w0, w0, 1
	cmp	w5, w0
	bhi	.L4360
.L4358:
	add	x22, x21, x19, uxtw 3
	mov	x0, x21
	ldr	x1, [x22, 27896]
	strb	wzr, [x1, 4]
	ldr	w2, [x20, 3708]
	ldr	x1, [x22, 27896]
	bl	OutputFrmToVO
	mov	w23, w0
	ldr	x0, [x22, 27896]
	ldrb	w0, [x0, 2]
	cbnz	w0, .L4356
	mov	w1, w19
	mov	x0, x21
	bl	RemoveFrameStoreOutDPB
	ldr	w5, [x20, 3708]
	cbnz	w5, .L4362
.L4374:
	mov	w0, 0
	cbz	w23, .L4352
	add	x0, x21, 8
	bl	GetVoLastImageID
.L4352:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L4363:
	mov	w19, 0
	b	.L4358
.L4349:
	ldr	x2, .LC1057
	mov	w3, 3256
	ldr	x1, .LC1058
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4352
	.size	H264DEC_GetRemainImg, .-H264DEC_GetRemainImg
	.align	3
.LC1057:
	.xword	.LC30
	.align	3
.LC1058:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_VDMPostProc
	.type	H264DEC_VDMPostProc, %function
H264DEC_VDMPostProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	w24, w1
	mov	x20, x3
	mov	w25, w4
	mov	w23, w5
	bl	_mcount
	cbz	x19, .L4408
	add	x21, x19, 61440
	ldr	x0, [x21, 2680]
	cbz	x0, .L4409
	ldr	x2, [x19, 616]
	ldr	x3, [x19]
	ldrb	w1, [x2, 17]
	ldr	w26, [x3, 684]
	strb	w1, [x0, 5]
	ldrb	w1, [x2, 4]
	str	w1, [x0, 8]
	ldr	w22, [x19, 624]
	str	w24, [x21, 2732]
	cbnz	w22, .L4379
	cbz	w25, .L4380
	ldr	x0, .LC1061
	sbfiz	x23, x23, 6, 32
	add	x23, x0, x23
	ldr	w0, [x23, 44]
	cmp	w0, 3
	beq	.L4410
	cmp	w0, 1
	beq	.L4380
	cmp	w26, 1
	beq	.L4411
.L4383:
	mov	x1, x20
	mov	x0, x19
	bl	StorePicInDPB
	cmp	w0, 1
	mov	w20, w0
	bls	.L4393
.L4412:
	ldr	x1, [x21, 2680]
	add	x0, x19, 65536
	mov	w2, 1
	mov	w22, -1
	ldr	w0, [x0, 1980]
	ldr	w1, [x1, 656]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC1066
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	x0, x19
	bl	H264_ClearCurrPic
	mov	x0, x19
	bl	ClearDPB
	str	xzr, [x21, 2680]
.L4377:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4380:
	mov	x0, x19
	bl	ClearAllSlice
	cmp	w26, 1
	bne	.L4383
.L4411:
	ldr	x25, [x19, 616]
	ldr	w0, [x25, 316]
	add	x0, x25, x0, lsl 2
	ldr	w26, [x0, 584]
	mov	w0, w26
	bl	MEM_Phy2Vir
	mov	x24, x0
	ldr	w2, [x25, 36]
	mov	w1, w26
	ldr	w7, [x25, 44]
	ldr	x3, .LC1062
	mul	w23, w7, w2
	ldr	x3, [x3, 280]
	lsl	w2, w23, 2
	blr	x3
	cbz	w23, .L4396
	mov	w7, 0
	mov	w6, 0
	mov	w4, 2147483647
	mov	w5, 0
	mov	w2, 0
	.p2align 2
.L4390:
	ubfiz	x0, x2, 2, 30
	ldr	w1, [x24, x0]
	and	w3, w1, 16383
	and	w8, w1, 8191
	neg	w3, w3
	tbz	x1, 13, .L4386
	and	w8, w3, 8191
.L4386:
	asr	w1, w1, 14
	and	w3, w1, 4095
	and	w0, w1, 2047
	neg	w3, w3
	tbz	x1, 11, .L4388
	and	w0, w3, 2047
.L4388:
	add	w0, w8, w0
	add	w2, w2, 1
	cmp	w4, w0
	add	w7, w7, w0
	csel	w4, w4, w0, le
	cmp	w5, w0
	csel	w5, w5, w0, ge
	cmp	w0, wzr
	csinc	w6, w6, w6, ne
	cmp	w23, w2
	bne	.L4390
	lsl	w0, w6, 2
	sub	w0, w0, w6
	lsl	w1, w0, 5
	add	w0, w0, w1
	add	w6, w0, w6
.L4384:
	udiv	w6, w6, w23
	ldr	x1, [x21, 2680]
	cmp	w6, 100
	csel	w4, w4, wzr, ne
	udiv	w7, w7, w23
	cbz	x1, .L4392
	ldr	w0, [x1, 260]
	cmp	w0, w5
	csel	w5, w0, w5, cs
	str	w5, [x1, 260]
	ldr	x1, [x21, 2680]
	ldr	w0, [x1, 264]
	cmp	w0, w4
	csel	w4, w0, w4, cs
	str	w4, [x1, 264]
	ldr	x0, [x21, 2680]
	str	w7, [x0, 268]
	ldr	x0, [x21, 2680]
	str	w6, [x0, 272]
	ldr	x0, [x21, 2680]
	ldr	w1, [x0, 260]
	str	w1, [x21, 2284]
	ldr	w1, [x0, 264]
	str	w1, [x21, 2288]
	mov	x1, x20
	str	w7, [x21, 2292]
	ldr	w0, [x0, 272]
	str	w0, [x21, 2296]
	mov	x0, x19
	bl	StorePicInDPB
	cmp	w0, 1
	mov	w20, w0
	bhi	.L4412
.L4393:
	add	x19, x19, 65536
	mov	w0, 1
	str	w0, [x19, 644]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4379:
	mov	x0, x19
	bl	ClearAllSlice
	mov	x1, x20
	mov	x0, x19
	bl	StorePicInDPB
	cbnz	w0, .L4413
.L4394:
	mov	x0, x19
	bl	FlushDPB
	cbnz	w0, .L4414
.L4395:
	add	x1, x19, 65536
	add	x0, x19, 20480
	mov	w4, 32
	mov	w7, 23352
	movk	w7, 0x1, lsl 16
	mov	w6, 2
	str	wzr, [x1, 644]
	mov	w5, 7
	mov	w3, 3
	mov	w2, -1
	ldr	w8, [x19, 14948]
	mov	w1, 262144
	strb	w4, [x0, 3226]
	add	x4, x0, 3072
	strb	wzr, [x0, 3224]
	mov	w22, 0
	strb	w6, [x0, 3225]
	str	w8, [x0, 3232]
	str	w5, [x0, 3236]
	str	w7, [x0, 3240]
	stp	w3, w2, [x4, 176]
	stp	wzr, wzr, [x4, 184]
	str	w1, [x0, 3264]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4414:
	ldr	x1, .LC1070
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4395
	.p2align 3
.L4413:
	ldr	x1, .LC1068
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	b	.L4394
	.p2align 3
.L4408:
	ldr	x2, .LC1059
	mov	w3, 13467
	ldr	x1, .LC1060
	mov	w0, 0
	mov	w22, -1
	bl	dprint_vfmw
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4409:
	ldr	x2, .LC1059
	mov	w3, 13468
	ldr	x1, .LC1060
	mov	w22, -1
	bl	dprint_vfmw
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4410:
	mov	x0, x19
	bl	ClearAllSlice
	b	.L4377
	.p2align 3
.L4392:
	ldr	x1, .LC1064
	mov	w0, 0
	mov	w22, -1
	bl	dprint_vfmw
	b	.L4377
.L4396:
	mov	w6, 0
	mov	w7, 0
	mov	w4, 2147483647
	mov	w5, 0
	b	.L4384
	.size	H264DEC_VDMPostProc, .-H264DEC_VDMPostProc
	.align	3
.LC1059:
	.xword	.LC30
	.align	3
.LC1060:
	.xword	.LC32
	.align	3
.LC1061:
	.xword	g_VdmDrvParam
	.align	3
.LC1062:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1064:
	.xword	.LC1063
	.align	3
.LC1066:
	.xword	.LC1065
	.align	3
.LC1068:
	.xword	.LC1067
	.align	3
.LC1070:
	.xword	.LC1069
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	H264DEC_GetImageBuffer
	.type	H264DEC_GetImageBuffer, %function
H264DEC_GetImageBuffer:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L4457
	add	x19, x21, 65536
	ldr	w0, [x19, 636]
	cbz	w0, .L4419
	add	x1, x21, 61440
	ldrb	w1, [x1, 2024]
	cmp	w1, 1
	beq	.L4419
	sub	w0, w0, #1
	mov	w4, 856
	mov	x2, 30080
	add	x1, x21, 28672
	add	x1, x1, 552
	umaddl	x4, w0, w4, x2
	add	x4, x21, x4
	.p2align 2
.L4425:
	ldrb	w0, [x1, 1]
	cbnz	w0, .L4420
	cbz	x1, .L4421
	add	x23, x21, 24576
	ldr	w3, [x23, 3708]
	cbz	w3, .L4421
	ldr	x0, [x21, 27896]
	cmp	x0, x1
	beq	.L4420
	sub	w3, w3, #1
	mov	x0, x21
	add	x3, x21, x3, lsl 3
	b	.L4422
	.p2align 3
.L4423:
	ldr	x2, [x0, 27896]
	cmp	x2, x1
	beq	.L4420
.L4422:
	cmp	x3, x0
	add	x0, x0, 8
	bne	.L4423
.L4421:
	ldr	w0, [x19, 1980]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L4419
	cmn	w0, #1
	beq	.L4458
.L4455:
	mov	w0, 0
.L4460:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4419:
	mov	w0, 1
.L4453:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4420:
	add	x1, x1, 856
	cmp	x1, x4
	bne	.L4425
	add	x2, x29, 76
	add	x1, x29, 72
	add	x0, x21, 8
	bl	GetQueueImgNum
	ldr	x1, .LC1074
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, .LC1076
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 636]
	cbz	w0, .L4459
	ldr	x20, .LC1080
	mov	w22, 0
	add	x23, x21, 24576
	.p2align 2
.L4432:
	uxtw	x1, w22
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x1, x0, x1
	lsl	x1, x1, 3
	add	x0, x21, x1
	add	x1, x1, 28672
	add	x0, x0, 28672
	add	x1, x21, x1
	adds	x1, x1, 552
	ldrb	w3, [x0, 553]
	ldrb	w4, [x0, 556]
	beq	.L4436
	ldr	w5, [x23, 3708]
	cbz	w5, .L4436
	ldr	x0, [x21, 27896]
	cmp	x1, x0
	beq	.L4438
	sub	w5, w5, #1
	mov	x0, x21
	add	x5, x21, x5, lsl 3
	b	.L4430
	.p2align 3
.L4431:
	ldr	x2, [x0, 27896]
	cmp	x1, x2
	beq	.L4438
.L4430:
	cmp	x5, x0
	add	x0, x0, 8
	bne	.L4431
.L4436:
	mov	w5, 1
.L4429:
	mov	w2, w22
	mov	x1, x20
	mov	w0, 0
	add	w22, w22, 1
	bl	dprint_vfmw
	ldr	w0, [x19, 636]
	cmp	w0, w22
	bhi	.L4432
.L4433:
	ldp	w2, w3, [x29, 72]
	ldr	x1, .LC1078
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 636]
	ldr	w2, [x23, 3708]
	ldp	w3, w1, [x29, 72]
	sub	w0, w0, #2
	sub	w0, w0, w2
	add	w1, w3, w1
	cmp	w1, w0
	bge	.L4455
	ldr	x1, .LC1082
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	mov	x0, x21
	bl	ClearAll
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, 0
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L4438:
	mov	w5, 0
	b	.L4429
.L4458:
	ldr	w0, [x19, 1980]
	add	x1, x21, 8
	bl	FSP_ClearNotInVoQueue
	mov	w0, 0
	b	.L4460
.L4459:
	add	x23, x21, 24576
	b	.L4433
.L4457:
	ldr	x2, .LC1071
	mov	w3, 13702
	ldr	x1, .LC1072
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L4453
	.size	H264DEC_GetImageBuffer, .-H264DEC_GetImageBuffer
	.align	3
.LC1071:
	.xword	.LC30
	.align	3
.LC1072:
	.xword	.LC32
	.align	3
.LC1074:
	.xword	.LC1073
	.align	3
.LC1076:
	.xword	.LC1075
	.align	3
.LC1078:
	.xword	.LC1077
	.align	3
.LC1080:
	.xword	.LC1079
	.align	3
.LC1082:
	.xword	.LC1081
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
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.10961, %object
	.size	__func__.10961, 23
__func__.10961:
	.string	"RemoveFrameStoreOutDPB"
	.align	3
.LANCHOR2 = . + 0
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
	.type	__func__.12239, %object
	.size	__func__.12239, 12
__func__.12239:
	.string	"H264_DecPPS"
	.zero	4
	.type	SarTable.12286, %object
	.size	SarTable.12286, 136
SarTable.12286:
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
	.type	__func__.12439, %object
	.size	__func__.12439, 12
__func__.12439:
	.string	"H264_DecSEI"
	.zero	4
	.type	__func__.11259, %object
	.size	__func__.11259, 8
__func__.11259:
	.string	"InitDPB"
	.type	__FUNCTION__.12662, %object
	.size	__FUNCTION__.12662, 13
__FUNCTION__.12662:
	.string	"H264DEC_Init"
	.zero	3
	.type	__func__.12693, %object
	.size	__func__.12693, 18
__func__.12693:
	.string	"H264_VES_Splitter"
	.zero	6
	.type	__func__.11342, %object
	.size	__func__.11342, 13
__func__.11342:
	.string	"DirectOutput"
	.zero	3
	.type	__func__.11453, %object
	.size	__func__.11453, 14
__func__.11453:
	.string	"StorePicInDPB"
	.zero	2
	.type	__FUNCTION__.11918, %object
	.size	__FUNCTION__.11918, 8
__FUNCTION__.11918:
	.string	"InitPic"
	.type	__func__.12579, %object
	.size	__func__.12579, 15
__func__.12579:
	.string	"H264_DecOneNal"
	.data
	.align	3
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
	.zero	192
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
	.zero	4
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
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC2:
	ASCII(.string	"list[%d][%d]: frame_num=%d, poc=%d\n" )
	.zero	4
.LC4:
	ASCII(.string	"L0: " )
	.zero	3
.LC6:
	ASCII(.string	"\n" )
	.zero	6
.LC8:
	ASCII(.string	"%d " )
	.zero	4
.LC10:
	ASCII(.string	"%dt " )
	.zero	3
.LC12:
	ASCII(.string	"%db " )
	.zero	3
.LC14:
	ASCII(.string	"L1:" )
	.zero	4
.LC16:
	ASCII(.string	"\n\nEND of the bit buffer, copy the first packet!\n\n" )
	.zero	6
.LC18:
	ASCII(.string	"0:phy:0x%x, 1:phy:0x%x; len0:%d len1:%d\n" )
	.zero	7
.LC21:
	ASCII(.string	"0:phy:0x%x, len0:%d\n" )
	.zero	3
.LC23:
	ASCII(.string	"%-50s%50d\n" )
	.zero	5
.LC30:
	ASCII(.string	"../../core/syntax/h264.c" )
	.zero	7
.LC32:
	ASCII(.string	"NULL pointer: %s, L%d\n" )
	.zero	1
.LC34:
	ASCII(.string	"\n VFMW ** release streambuff=%p   bitstream_length=%d\n" )
	.zero	1
.LC37:
	ASCII(.string	"%s DPB.fs[%d] = NULL\n" )
	.zero	2
.LC41:
	ASCII(.string	"clear curr slice.\n" )
	.zero	5
.LC51:
	ASCII(.string	"frame %d, state=%d, is already output\n" )
	.zero	1
.LC53:
	ASCII(.string	"plfs(fs=%p, eFoState=%d) is null, logic_fs_id = %d\n" )
	.zero	4
.LC55:
	ASCII(.string	"not used frame: (%d,%d)\n" )
	.zero	7
.LC57:
	ASCII(.string	"frame skip: is_used=%d,skip=%d\n" )
.LC59:
	ASCII(.string	"topfield skip: is_used=%d,skip=%d\n" )
	.zero	5
.LC61:
	ASCII(.string	"bottom field skip: is_used=%d,skip=%d\n" )
	.zero	1
.LC63:
	ASCII(.string	"err(%d) > out_thr(%d)\n" )
	.zero	1
.LC66:
	ASCII(.string	"exg_pts: %lld <-> %lld\n" )
.LC68:
	ASCII(.string	"stream frame packing type is %d! what can we do?\n" )
	.zero	6
.LC73:
	ASCII(.string	"framestore %d allocate apc %d\n" )
	.zero	1
.LC75:
	ASCII(.string	"find APC, but logic_fs_id %d abnormal(ref=%d,plfs=%p, pdfs=%p)\n" )
.LC79:
	ASCII(.string	"pH264Ctx->DPB.fs[%d]: frame_num=%d poc=%d is_reference=%d\n" )
	.zero	5
.LC81:
	ASCII(.string	"pH264Ctx->DPB.fs_ref[%d]: frame_num=%d poc=%d is_reference=%d\n" )
	.zero	1
.LC83:
	ASCII(.string	"pH264Ctx->DPB.fs_ref[%d]: frame.poc=%d \n" )
	.zero	7
.LC86:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC88:
	ASCII(.string	"resolution error, ImageWidth=%d, ImageHeight=%d\n" )
	.zero	7
.LC90:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC92:
	ASCII(.string	"ERROR: FSP_ConfigInstance fail!\n" )
	.zero	7
.LC96:
	ASCII(.string	"slice_type %d invalid, clear current slice.\n" )
	.zero	3
.LC98:
	ASCII(.string	"pRepairPic(%p)/found(%d) = 0, clear current slice.\n" )
	.zero	4
.LC100:
	ASCII(.string	"listXsize[%d] = %d, clear current slice.\n" )
	.zero	6
.LC110:
	ASCII(.string	"for P slice size of list equal 0.\n" )
	.zero	5
.LC116:
	ASCII(.string	"for B slice size of two list all equal 0.\n" )
	.zero	5
.LC122:
	ASCII(.string	"init list error.\n" )
	.zero	6
.LC124:
	ASCII(.string	"L0: list after init.\n" )
	.zero	2
.LC127:
	ASCII(.string	"L0: list after reorder.\n" )
	.zero	7
.LC132:
	ASCII(.string	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=%d\n" )
	.zero	1
.LC134:
	ASCII(.string	"logic frame id(=%d): get LogicFs error!\n" )
	.zero	7
.LC136:
	ASCII(.string	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p\n" )
	.zero	3
.LC140:
	ASCII(.string	"line: %d pstLogicFs is null\n" )
	.zero	3
.LC142:
	ASCII(.string	"SH: first_mb_in_slice" )
	.zero	2
.LC144:
	ASCII(.string	"slicecheck first_mb_in_slice >= MAX_MB_NUM_IN_PIC error.\n" )
	.zero	6
.LC146:
	ASCII(.string	"SH: slice_type" )
	.zero	1
.LC148:
	ASCII(.string	"slice type = %d\n" )
	.zero	7
.LC151:
	ASCII(.string	"slice type = %d, err\n" )
	.zero	2
.LC153:
	ASCII(.string	"slice  pps id = %d\n" )
	.zero	4
.LC157:
	ASCII(.string	"pps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	1
.LC159:
	ASCII(.string	"sps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	1
.LC161:
	ASCII(.string	"tmp slice  pps id = %d\n" )
.LC165:
	ASCII(.string	"PPSSPSCheckTmpId: pps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	7
.LC167:
	ASCII(.string	"PPSSPSCheckTmpId: seq_parameter_set_id out of range.\n" )
	.zero	2
.LC169:
	ASCII(.string	"PPSSPSCheckTmpId: sps with this pic_parameter_set_id = %d havn't decode\n" )
	.zero	7
.LC173:
	ASCII(.string	"new pic flag = %d\n" )
	.zero	5
.LC175:
	ASCII(.string	"SH: ref_pic_list_reordering_flag_l0" )
	.zero	4
.LC177:
	ASCII(.string	"SH: reordering_of_pic_nums_idc_l0" )
	.zero	6
.LC179:
	ASCII(.string	"reorder idc l0 = %d, g_SeErrFlag=%d\n" )
	.zero	3
.LC181:
	ASCII(.string	"SH: abs_diff_pic_num_minus1_l0" )
	.zero	1
.LC183:
	ASCII(.string	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\n" )
	.zero	7
.LC185:
	ASCII(.string	"SH: long_term_pic_idx_l0" )
	.zero	7
.LC187:
	ASCII(.string	"num of idc l0 exceed\n" )
	.zero	2
.LC189:
	ASCII(.string	"SH: ref_pic_list_reordering_flag_l1" )
	.zero	4
.LC191:
	ASCII(.string	"SH: reordering_of_pic_nums_idc_l1" )
	.zero	6
.LC193:
	ASCII(.string	"reorder idc l1 = %d, g_SeErrFlag=%d\n" )
	.zero	3
.LC195:
	ASCII(.string	"SH: abs_diff_pic_num_minus1_l1" )
	.zero	1
.LC197:
	ASCII(.string	"abs_diff_pic_num_minus1_l1 = %d, g_SeErrFlag=%d\n" )
	.zero	7
.LC199:
	ASCII(.string	"SH: long_term_pic_idx_l1" )
	.zero	7
.LC201:
	ASCII(.string	"num of idc l1 exceed\n" )
	.zero	2
.LC203:
	ASCII(.string	"SH: luma_log2_weight_denom" )
	.zero	5
.LC205:
	ASCII(.string	"SH: chroma_log2_weight_denom" )
	.zero	3
.LC207:
	ASCII(.string	"WP log2 exceed  and err flag = %d\n" )
	.zero	5
.LC209:
	ASCII(.string	"SH: luma_weight_flag_l0" )
.LC211:
	ASCII(.string	"SH: luma_weight_l0" )
	.zero	5
.LC213:
	ASCII(.string	"SH: luma_offset_l0" )
	.zero	5
.LC215:
	ASCII(.string	"SH: chroma_weight_flag_l0" )
	.zero	6
.LC217:
	ASCII(.string	"SH: chroma_weight_l0" )
	.zero	3
.LC219:
	ASCII(.string	"SH: chroma_offset_l0" )
	.zero	3
.LC221:
	ASCII(.string	"SH: luma_weight_flag_l1" )
.LC223:
	ASCII(.string	"SH: luma_weight_l1" )
	.zero	5
.LC225:
	ASCII(.string	"SH: luma_offset_l1" )
	.zero	5
.LC227:
	ASCII(.string	"SH: chroma_weight_flag_l1" )
	.zero	6
.LC229:
	ASCII(.string	"SH: chroma_weight_l1" )
	.zero	3
.LC231:
	ASCII(.string	"SH: chroma_offset_l1" )
	.zero	3
.LC233:
	ASCII(.string	"overflow MAX_MMCO_LEN\n" )
	.zero	1
.LC235:
	ASCII(.string	"SH: memory_management_control_operation" )
.LC237:
	ASCII(.string	"SH: difference_of_pic_nums_minus1" )
	.zero	6
.LC239:
	ASCII(.string	"SH: long_term_pic_num" )
	.zero	2
.LC241:
	ASCII(.string	"SH: long_term_frame_idx" )
.LC243:
	ASCII(.string	"SH: max_long_term_frame_idx_plus1" )
	.zero	6
.LC245:
	ASCII(.string	"mmco exceed 6\n" )
	.zero	1
.LC249:
	ASCII(.string	"SH: no_output_of_prior_pics_flag" )
	.zero	7
.LC251:
	ASCII(.string	"SH: long_term_reference_flag" )
	.zero	3
.LC253:
	ASCII(.string	"IDR and no_output_of_prior_pics_flag = %d\n" )
	.zero	5
.LC255:
	ASCII(.string	"SH: adaptive_ref_pic_marking_mode_flag" )
	.zero	1
.LC257:
	ASCII(.string	"adaptive_ref_pic_marking_mode_flag = %d\n" )
	.zero	7
.LC259:
	ASCII(.string	"MMCO para would save dec err\n" )
	.zero	2
.LC261:
	ASCII(.string	"mulitislice diff no_out_of_prior_pics_flag, used first.\n" )
	.zero	7
.LC263:
	ASCII(.string	"mulitislice diff long_term_reference_flag, used first.\n" )
.LC265:
	ASCII(.string	"mulitislice diff adaptive_ref_pic_marking_mode_flag, used first.\n" )
	.zero	6
.LC267:
	ASCII(.string	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\n" )
	.zero	1
.LC271:
	ASCII(.string	"SH: pic_parameter_set_id" )
	.zero	7
.LC273:
	ASCII(.string	"pps id:%d in sliceheader err\n" )
	.zero	2
.LC275:
	ASCII(.string	"PPS or SPS of this slice not valid\n" )
	.zero	4
.LC277:
	ASCII(.string	"recover point but isn't I_SLICE.\n" )
	.zero	6
.LC279:
	ASCII(.string	"SH: frame_num" )
	.zero	2
.LC281:
	ASCII(.string	"IDR NAL but frame_num!=0.\n" )
	.zero	5
.LC283:
	ASCII(.string	"SH: field_pic_flag" )
	.zero	5
.LC285:
	ASCII(.string	"SH: bottom_field_flag" )
	.zero	2
.LC287:
	ASCII(.string	"field first_mb_in_slice bigger than pic size\n" )
	.zero	2
.LC289:
	ASCII(.string	"frame first_mb_in_slice bigger than pic size\n" )
	.zero	2
.LC291:
	ASCII(.string	"SH: idr_pic_id" )
	.zero	1
.LC293:
	ASCII(.string	"idr_pic_id bigger than 65535\n" )
	.zero	2
.LC295:
	ASCII(.string	"SH: pic_order_cnt_lsb" )
	.zero	2
.LC297:
	ASCII(.string	"SH: delta_pic_order_cnt_bottom" )
	.zero	1
.LC299:
	ASCII(.string	"SH: delta_pic_order_cnt[0]" )
	.zero	5
.LC301:
	ASCII(.string	"SH: delta_pic_order_cnt[1]" )
	.zero	5
.LC303:
	ASCII(.string	"SH: redundant_pic_cnt" )
	.zero	2
.LC305:
	ASCII(.string	"redundant pic not support.\n" )
	.zero	4
.LC308:
	ASCII(.string	"first_mb_in_slice in currslice small than prevslice in same pic\n" )
	.zero	7
.LC314:
	ASCII(.string	"SH: direct_spatial_mv_pred_flag" )
.LC316:
	ASCII(.string	"SH: num_ref_idx_override_flag" )
	.zero	2
.LC318:
	ASCII(.string	"SH: num_ref_idx_l0_active_minus1" )
	.zero	7
.LC320:
	ASCII(.string	"SH: num_ref_idx_l1_active_minus1" )
	.zero	7
.LC322:
	ASCII(.string	"frame num_ref_idx_lx_active_minus1 exceed\n" )
	.zero	5
.LC324:
	ASCII(.string	"field num_ref_idx_lx_active_minus1 exceed\n" )
	.zero	5
.LC326:
	ASCII(.string	"reordering para dec err\n" )
	.zero	7
.LC328:
	ASCII(.string	"apply_weights_flag=%d\n" )
	.zero	1
.LC330:
	ASCII(.string	"wpt dec err\n" )
	.zero	3
.LC332:
	ASCII(.string	"mark para dec err\n" )
	.zero	5
.LC334:
	ASCII(.string	"SH: cabac_init_idc" )
	.zero	5
.LC336:
	ASCII(.string	"cabac_init_idc bigger than 3\n" )
	.zero	2
.LC338:
	ASCII(.string	"SH: slice_qp_delta" )
	.zero	5
.LC340:
	ASCII(.string	"SH: disable_deblocking_filter_idc" )
	.zero	6
.LC342:
	ASCII(.string	"disable_deblocking_filter_idc dec err\n" )
	.zero	1
.LC344:
	ASCII(.string	"SH: slice_alpha_c0_offset_div2" )
	.zero	1
.LC346:
	ASCII(.string	"slice_alpha_c0_offset_div2 dec err\n" )
	.zero	4
.LC348:
	ASCII(.string	"SH: slice_beta_offset_div2" )
	.zero	5
.LC350:
	ASCII(.string	"slice_beta_offset_div2 dec err\n" )
.LC358:
	ASCII(.string	"pH264Ctx->pCurrNal->nal_bitoffset = %d; code_len_byte = %d; bitstream_length = %d; pH264Ctx->pCurrNal->nal_trail_zero_bit_num = %d\n" )
	.zero	4
.LC360:
	ASCII(.string	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; bytespos = %x\n" )
	.zero	1
.LC362:
	ASCII(.string	"nal_segment = %d is not expected value\n" )
.LC364:
	ASCII(.string	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\n" )
.LC371:
	ASCII(.string	"   : delta_sl   " )
	.zero	7
.LC377:
	ASCII(.string	"PPS: entropy_coding_mode_flag" )
	.zero	2
.LC379:
	ASCII(.string	"PPS: pic_order_present_flag" )
	.zero	4
.LC381:
	ASCII(.string	"PPS: num_slice_groups_minus1" )
	.zero	3
.LC383:
	ASCII(.string	"Baseline stream with FMO, not support.\n" )
.LC386:
	ASCII(.string	"PPS: num_ref_idx_l0_active_minus1" )
	.zero	6
.LC388:
	ASCII(.string	"num_ref_idx_l0_active_minus1 out of range.\n" )
	.zero	4
.LC390:
	ASCII(.string	"PPS: num_ref_idx_l1_active_minus1" )
	.zero	6
.LC392:
	ASCII(.string	"num_ref_idx_l1_active_minus1 out of range.\n" )
	.zero	4
.LC394:
	ASCII(.string	"PPS: weighted prediction flag" )
	.zero	2
.LC396:
	ASCII(.string	"PPS: weighted_bipred_idc" )
	.zero	7
.LC398:
	ASCII(.string	"weighted_bipred_idc out of range\n" )
	.zero	6
.LC400:
	ASCII(.string	"PPS: pic_init_qp_minus26" )
	.zero	7
.LC402:
	ASCII(.string	"PPS: pic_init_qs_minus26" )
	.zero	7
.LC404:
	ASCII(.string	"PPS: chroma_qp_index_offset" )
	.zero	4
.LC406:
	ASCII(.string	"PPS: deblocking_filter_control_present_flag" )
	.zero	4
.LC408:
	ASCII(.string	"PPS: constrained_intra_pred_flag" )
	.zero	7
.LC410:
	ASCII(.string	"PPS: redundant_pic_cnt_present_flag" )
	.zero	4
.LC412:
	ASCII(.string	"redundant pic not support when find redundant slice later, exit\n" )
	.zero	7
.LC414:
	ASCII(.string	"PPS: transform_8x8_mode_flag" )
	.zero	3
.LC416:
	ASCII(.string	"PPS: pic_scaling_matrix_present_flag" )
	.zero	3
.LC418:
	ASCII(.string	"PPS: second_chroma_qp_index_offset" )
	.zero	5
.LC420:
	ASCII(.string	"SPS: seq_scaling_list_present_flag" )
	.zero	5
.LC423:
	ASCII(.string	"PPS: pic_scaling_list_present_flag" )
	.zero	5
.LC425:
	ASCII(.string	"second_chroma_qp_index_offset out of range.\n" )
	.zero	3
.LC431:
	ASCII(.string	"PPS: pic_parameter_set_id" )
	.zero	6
.LC433:
	ASCII(.string	"pic_parameter_set_id out of range.\n" )
	.zero	4
.LC436:
	ASCII(.string	"PPS: seq_parameter_set_id" )
	.zero	6
.LC438:
	ASCII(.string	"seq_parameter_set_id out of range.\n" )
	.zero	4
.LC440:
	ASCII(.string	"SPS haven't decode.\n" )
	.zero	3
.LC444:
	ASCII(.string	"%s: PPS decode error 1.\n" )
	.zero	7
.LC447:
	ASCII(.string	"%s: PPS decode error 2.\n" )
	.zero	7
.LC449:
	ASCII(.string	"VUI: aspect_ratio_info_present_flag" )
	.zero	4
.LC451:
	ASCII(.string	"VUI: aspect_ratio_idc" )
	.zero	2
.LC453:
	ASCII(.string	"VUI: sar_width" )
	.zero	1
.LC455:
	ASCII(.string	"VUI: sar_height" )
.LC457:
	ASCII(.string	"VUI: overscan_info_present_flag" )
.LC459:
	ASCII(.string	"VUI: overscan_appropriate_flag" )
	.zero	1
.LC461:
	ASCII(.string	"VUI: video_signal_type_present_flag" )
	.zero	4
.LC463:
	ASCII(.string	"VUI: video_format" )
	.zero	6
.LC465:
	ASCII(.string	"VUI: video_full_range_flag" )
	.zero	5
.LC467:
	ASCII(.string	"VUI: color_description_present_flag" )
	.zero	4
.LC469:
	ASCII(.string	"VUI: colour_primaries" )
	.zero	2
.LC471:
	ASCII(.string	"VUI: transfer_characteristics" )
	.zero	2
.LC473:
	ASCII(.string	"VUI: matrix_coefficients" )
	.zero	7
.LC475:
	ASCII(.string	"VUI: chroma_loc_info_present_flag" )
	.zero	6
.LC477:
	ASCII(.string	"VUI: chroma_sample_loc_type_top_field" )
	.zero	2
.LC479:
	ASCII(.string	"VUI: chroma_sample_loc_type_bottom_field" )
	.zero	7
.LC481:
	ASCII(.string	"VUI: timing_info_present_flag" )
	.zero	2
.LC483:
	ASCII(.string	"VUI: num_units_in_tick" )
	.zero	1
.LC485:
	ASCII(.string	"VUI: time_scale" )
.LC487:
	ASCII(.string	"VUI: fixed_frame_rate_flag" )
	.zero	5
.LC490:
	ASCII(.string	"VUI: nal_hrd_parameters_present_flag" )
	.zero	3
.LC492:
	ASCII(.string	"VUI: cpb_cnt_minus1" )
	.zero	4
.LC494:
	ASCII(.string	"VUI: bit_rate_scale" )
	.zero	4
.LC496:
	ASCII(.string	"VUI: cpb_size_scale" )
	.zero	4
.LC498:
	ASCII(.string	"hrd->cpb_cnt_minus1 out of range\n" )
	.zero	6
.LC500:
	ASCII(.string	"VUI: bit_rate_value_minus1" )
	.zero	5
.LC502:
	ASCII(.string	"VUI: cpb_size_value_minus1" )
	.zero	5
.LC504:
	ASCII(.string	"VUI: cbr_flag" )
	.zero	2
.LC506:
	ASCII(.string	"VUI: initial_cpb_removal_delay_length_minus1" )
	.zero	3
.LC508:
	ASCII(.string	"VUI: cpb_removal_delay_length_minus1" )
	.zero	3
.LC510:
	ASCII(.string	"VUI: dpb_output_delay_length_minus1" )
	.zero	4
.LC512:
	ASCII(.string	"VUI: time_offset_length" )
.LC514:
	ASCII(.string	"VUI: vcl_hrd_parameters_present_flag" )
	.zero	3
.LC516:
	ASCII(.string	"VUI: low_delay_hrd_flag" )
.LC518:
	ASCII(.string	"VUI: pic_struct_present_flag" )
	.zero	3
.LC520:
	ASCII(.string	"VUI: bitstream_restriction_flag" )
.LC522:
	ASCII(.string	"VUI: motion_vectors_over_pic_boundaries_flag" )
	.zero	3
.LC524:
	ASCII(.string	"VUI: max_bytes_per_pic_denom" )
	.zero	3
.LC526:
	ASCII(.string	"VUI: max_bits_per_mb_denom" )
	.zero	5
.LC528:
	ASCII(.string	"VUI: log2_max_mv_length_horizontal" )
	.zero	5
.LC530:
	ASCII(.string	"VUI: log2_max_mv_length_vertical" )
	.zero	7
.LC532:
	ASCII(.string	"VUI: num_reorder_frames" )
.LC534:
	ASCII(.string	"VUI: max_dec_frame_buffering" )
	.zero	3
.LC539:
	ASCII(.string	"dar=%d, final_dar=%d\n" )
	.zero	2
.LC545:
	ASCII(.string	"SPS: chroma_format_idc" )
	.zero	1
.LC547:
	ASCII(.string	"pSPS->chroma_format_idc = %d out of range.\n" )
	.zero	4
.LC549:
	ASCII(.string	"SPS: bit_depth_luma_minus8" )
	.zero	5
.LC551:
	ASCII(.string	"bit_depth_luma(%d) not equal 8.\n" )
	.zero	7
.LC554:
	ASCII(.string	"SPS: bit_depth_chroma_minus8" )
	.zero	3
.LC556:
	ASCII(.string	"bit_depth_chroma(%d) not equal 8.\n" )
	.zero	5
.LC558:
	ASCII(.string	"SPS: qpprime_y_zero_trans_bypass_flag" )
	.zero	2
.LC560:
	ASCII(.string	"qpprime_y_zero_trans_bypass_flag not equal 0.\n" )
	.zero	1
.LC562:
	ASCII(.string	"SPS: seq_scaling_matrix_present_flag" )
	.zero	3
.LC566:
	ASCII(.string	"SPS: log2_max_frame_num_minus4" )
	.zero	1
.LC568:
	ASCII(.string	"pSPS->log2_max_frame_num_minus4 out of range.\n" )
	.zero	1
.LC570:
	ASCII(.string	"SPS: pic_order_cnt_type" )
.LC572:
	ASCII(.string	"pSPS->pic_order_cnt_type out of range.\n" )
.LC574:
	ASCII(.string	"SPS: log2_max_pic_order_cnt_lsb_minus4" )
	.zero	1
.LC576:
	ASCII(.string	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of range.\n" )
	.zero	1
.LC578:
	ASCII(.string	"SPS: delta_pic_order_always_zero_flag" )
	.zero	2
.LC580:
	ASCII(.string	"SPS: offset_for_non_ref_pic" )
	.zero	4
.LC582:
	ASCII(.string	"SPS: offset_for_top_to_bottom_field" )
	.zero	4
.LC584:
	ASCII(.string	"SPS: num_ref_frames_in_pic_order_cnt_cycle" )
	.zero	5
.LC586:
	ASCII(.string	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of range.\n" )
	.zero	5
.LC588:
	ASCII(.string	"SPS: offset_for_ref_frame[i]" )
	.zero	3
.LC590:
	ASCII(.string	"SPS: gaps_in_frame_num_value_allowed_flag" )
	.zero	6
.LC592:
	ASCII(.string	"SPS: pic_width_in_mbs_minus1" )
	.zero	3
.LC594:
	ASCII(.string	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\n" )
	.zero	6
.LC596:
	ASCII(.string	"SPS: pic_height_in_map_units_minus1" )
	.zero	4
.LC598:
	ASCII(.string	"SPS: frame_mbs_only_flag" )
	.zero	7
.LC600:
	ASCII(.string	"pSPS->pic_height_in_map_units_minus1 out of range.\n" )
	.zero	4
.LC602:
	ASCII(.string	"pic size too large.\n" )
	.zero	3
.LC605:
	ASCII(.string	"level_idc %d not support.\n" )
	.zero	5
.LC607:
	ASCII(.string	"dpb size according level : %d\n" )
	.zero	1
.LC609:
	ASCII(.string	"pSPS->num_ref_frames(%d) > DPB size(%d), try to select the reasonable one.\n" )
	.zero	4
.LC611:
	ASCII(.string	"SPS: direct_8x8_inference_flag" )
	.zero	1
.LC613:
	ASCII(.string	"SPS: frame_cropping_flag" )
	.zero	7
.LC615:
	ASCII(.string	"SPS: frame_cropping_rect_left_offset" )
	.zero	3
.LC617:
	ASCII(.string	"SPS: frame_cropping_rect_right_offset" )
	.zero	2
.LC619:
	ASCII(.string	"SPS: frame_cropping_rect_top_offset" )
	.zero	4
.LC621:
	ASCII(.string	"SPS: frame_cropping_rect_bottom_offset" )
	.zero	1
.LC623:
	ASCII(.string	"SPS: vui_parameters_present_flag" )
	.zero	7
.LC625:
	ASCII(.string	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\n" )
	.zero	2
.LC627:
	ASCII(.string	"SPS: num_ref_frames" )
	.zero	4
.LC629:
	ASCII(.string	"SPS: mb_adaptive_frame_field_flag" )
	.zero	6
.LC631:
	ASCII(.string	"SPS_SVC_EXT: inter_layer_deblocking_filter_control_present_flag" )
.LC633:
	ASCII(.string	"inter_layer_present_flag:%d!\n" )
	.zero	2
.LC635:
	ASCII(.string	"SPS_SVC_EXT: extended_spatial_scalability_idc" )
	.zero	2
.LC637:
	ASCII(.string	"spatial scalability not support!!\n" )
	.zero	5
.LC639:
	ASCII(.string	"SPS_SVC_EXT: chroma_phase_x_plus1_flag" )
	.zero	1
.LC641:
	ASCII(.string	"chroma_phase_x_plus1_flag:%d!!\n" )
.LC643:
	ASCII(.string	"SPS_SVC_EXT: chroma_phase_y_plus1" )
	.zero	6
.LC645:
	ASCII(.string	"chroma_phase_y_plus1:%d!\n" )
	.zero	6
.LC647:
	ASCII(.string	"SPS_SVC_EXT: seq_tcoeff_level_prediction_flag" )
	.zero	2
.LC649:
	ASCII(.string	"SPS_SVC_EXT: adaptive_tcoeff_level_prediction_flag" )
	.zero	5
.LC651:
	ASCII(.string	"adaptive_tcoeff_level_prediction_flag:%d!\n" )
	.zero	5
.LC653:
	ASCII(.string	"SPS_SVC_EXT: slice_header_restriction_flag" )
	.zero	5
.LC655:
	ASCII(.string	"slice_header_restriction_flag error:%d,%x,%d\n" )
	.zero	2
.LC659:
	ASCII(.string	"SPS: profile_idc" )
	.zero	7
.LC661:
	ASCII(.string	"SPS: constrained_set0_flag" )
	.zero	5
.LC663:
	ASCII(.string	"SPS: constrained_set1_flag" )
	.zero	5
.LC665:
	ASCII(.string	"SPS: constrained_set2_flag" )
	.zero	5
.LC667:
	ASCII(.string	"SPS: constrained_set3_flag" )
	.zero	5
.LC669:
	ASCII(.string	"SPS: reserved_zero_4bits" )
	.zero	7
.LC671:
	ASCII(.string	"SPS: level_idc" )
	.zero	1
.LC673:
	ASCII(.string	"SPS: seq_parameter_set_id" )
	.zero	6
.LC678:
	ASCII(.string	"Baseline stream, try to decode, exit when FMO occurred.\n" )
	.zero	7
.LC680:
	ASCII(.string	"EXTENDED stream, try to decode, exit when datapartition occurred.\n" )
	.zero	5
.LC682:
	ASCII(.string	"others High profile stream, try to decode, exit when high profile not support occurred.\n" )
	.zero	7
.LC684:
	ASCII(.string	"profile_idc = %5d error, try to decode as main profile.\n" )
	.zero	7
.LC686:
	ASCII(.string	"level_idc = %5d error, try to decode as level_idc %d.\n" )
	.zero	1
.LC690:
	ASCII(.string	"Line %d: SPS[%d] decode error.\n" )
.LC692:
	ASCII(.string	"svc ext error:\n" )
.LC695:
	ASCII(.string	"SEI: frame_packing_arrangement_id" )
	.zero	6
.LC697:
	ASCII(.string	"SEI: frame_packing_arrangement_cancel_flag" )
	.zero	5
.LC699:
	ASCII(.string	"SEI: frame_packing_arrangement_type" )
	.zero	4
.LC701:
	ASCII(.string	"SEI: quincunx_sampling_flag" )
	.zero	4
.LC703:
	ASCII(.string	"SEI: content_interpretation_type" )
	.zero	7
.LC705:
	ASCII(.string	"SEI: spatial_flipping_flag" )
	.zero	5
.LC707:
	ASCII(.string	"SEI: frame0_flipped_flag" )
	.zero	7
.LC709:
	ASCII(.string	"SEI: field_views_flag" )
	.zero	2
.LC711:
	ASCII(.string	"SEI: current_frame_is_frame0_flag" )
	.zero	6
.LC713:
	ASCII(.string	"SEI: frame0_self_contained_flag" )
.LC715:
	ASCII(.string	"SEI: frame1_self_contained_flag" )
.LC717:
	ASCII(.string	"SEI: frame0_grid_position_x" )
	.zero	4
.LC719:
	ASCII(.string	"SEI: frame0_grid_position_y" )
	.zero	4
.LC721:
	ASCII(.string	"SEI: frame1_grid_position_x" )
	.zero	4
.LC723:
	ASCII(.string	"SEI: frame1_grid_position_y" )
	.zero	4
.LC725:
	ASCII(.string	"SEI: frame_packing_arrangement_reserved_byte" )
	.zero	3
.LC727:
	ASCII(.string	"SEI: frame_packing_arrangement_repetition_period" )
	.zero	7
.LC729:
	ASCII(.string	"SEI: frame_packing_arrangement_extension_flag" )
	.zero	2
.LC731:
	ASCII(.string	"DecPicTimingSEI but SPS is invalid.\n" )
	.zero	3
.LC733:
	ASCII(.string	"SEI: cpb_removal_delay" )
	.zero	1
.LC735:
	ASCII(.string	"SEI: dpb_output_delay" )
	.zero	2
.LC738:
	ASCII(.string	"pic_struct" )
	.zero	5
.LC743:
	ASCII(.string	"SEI nal dec payload type err\n" )
	.zero	2
.LC745:
	ASCII(.string	"SEI nal dec payloadSize err\n" )
	.zero	3
.LC748:
	ASCII(.string	"SEI_BUFFERING_PERIOD,offset = %d,payload_size = %d \n" )
	.zero	3
.LC751:
	ASCII(.string	"PassBytes err [%s][%d]\n" )
.LC753:
	ASCII(.string	"SEI_PIC_TIMING,offset = %d,payload_size = %d \n" )
	.zero	1
.LC755:
	ASCII(.string	"SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d \n" )
	.zero	6
.LC757:
	ASCII(.string	"SEI_FILLER_PAYLOAD,offset = %d,payload_size = %d \n" )
	.zero	5
.LC759:
	ASCII(.string	"SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d, payload_size = %d \n" )
	.zero	3
.LC761:
	ASCII(.string	"SEI_USER_DATA_UNREGISTERED, offset = %d, payload_size = %d \n" )
	.zero	3
.LC763:
	ASCII(.string	"SEI: itu_t_t35_country_code" )
	.zero	4
.LC765:
	ASCII(.string	"SEI: itu_t_t35_country_code_extension_byte" )
	.zero	5
.LC767:
	ASCII(.string	"SEI: itu_t_t35_provider_code" )
	.zero	3
.LC770:
	ASCII(.string	"len_tmp = %d cann't dec usrdata\n" )
	.zero	7
.LC772:
	ASCII(.string	"cann't dec usrdata\n" )
	.zero	4
.LC774:
	ASCII(.string	"SEI_RECOVERY_POINT,offset = %d,payload_size = %d \n" )
	.zero	5
.LC776:
	ASCII(.string	"SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d,payload_size = %d \n" )
	.zero	5
.LC778:
	ASCII(.string	"SEI_SPARE_PIC,offset = %d,payload_size = %d \n" )
	.zero	2
.LC780:
	ASCII(.string	"SEI_SCENE_INFO,offset = %d,payload_size = %d \n" )
	.zero	1
.LC782:
	ASCII(.string	"SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d \n" )
	.zero	7
.LC784:
	ASCII(.string	"SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	6
.LC786:
	ASCII(.string	"SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	4
.LC788:
	ASCII(.string	"SEI_FULL_FRAME_FREEZE,offset = %d,payload_size = %d \n" )
	.zero	2
.LC790:
	ASCII(.string	"SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,payload_size = %d \n" )
	.zero	2
.LC792:
	ASCII(.string	"SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_size = %d \n" )
.LC794:
	ASCII(.string	"SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset = %d,payload_size = %d \n" )
	.zero	7
.LC796:
	ASCII(.string	"SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset = %d,payload_size = %d \n" )
	.zero	1
.LC798:
	ASCII(.string	"SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset = %d,payload_size = %d \n" )
	.zero	1
.LC800:
	ASCII(.string	"SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payload_size = %d \n" )
	.zero	1
.LC802:
	ASCII(.string	"SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset = %d,payload_size = %d \n" )
	.zero	7
.LC804:
	ASCII(.string	"SEI_STEREO_VIDEO_INFO,offset = %d,payload_size = %d \n" )
	.zero	2
.LC806:
	ASCII(.string	"too much usrdat, cann't dec SEI\n" )
	.zero	7
.LC810:
	ASCII(.string	"\nthe stream is error,len:%d\n" )
	.zero	3
.LC815:
	ASCII(.string	"\nSlice nal or IDR nal = %d\n" )
	.zero	4
.LC817:
	ASCII(.string	"sliceheader dec err\n" )
	.zero	3
.LC821:
	ASCII(.string	"H264Dec destroy\n" )
	.zero	7
.LC823:
	ASCII(.string	"H264 recycle image\n" )
	.zero	4
.LC827:
	ASCII(.string	"pH264Ctx is %p, pFrameStore is %p\n" )
	.zero	5
.LC829:
	ASCII(.string	"line; %d pstLogicFsImage is NULL!\n" )
	.zero	5
.LC831:
	ASCII(.string	"InsertVO err:%d, ClearAll\n" )
	.zero	5
.LC833:
	ASCII(.string	"H264.c line %d: frame para err(ret=%d), recycle image self\n" )
	.zero	4
.LC835:
	ASCII(.string	"line: %d pstLogicFsImage is NULL!\n" )
	.zero	5
.LC845:
	ASCII(.string	"[%s][%d] OutputFrmToVO return %d\n" )
	.zero	6
.LC848:
	ASCII(.string	"clear all dec para\n" )
	.zero	4
.LC853:
	ASCII(.string	"FS_ALLOC_ERR, ClearAll\n" )
.LC856:
	ASCII(.string	"Can not new logic fs! ClearAll\n" )
.LC862:
	ASCII(.string	"%s %d unknow error!!\n" )
	.zero	2
.LC864:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC866:
	ASCII(.string	"line %d: flush dpb return %d\n" )
	.zero	2
.LC868:
	ASCII(.string	"[%s %d], pos is %d out of range\n" )
	.zero	7
.LC870:
	ASCII(.string	"line %d, get APC error, ret %d\n" )
.LC872:
	ASCII(.string	"InserFrmInDPB: cur pic struct = %d!\n" )
	.zero	3
.LC876:
	ASCII(.string	"----------------- Imode -> %d ------------------\n" )
	.zero	6
.LC878:
	ASCII(.string	"I_MODE but first_mb_in_slice != 0\n" )
	.zero	5
.LC882:
	ASCII(.string	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\n" )
.LC884:
	ASCII(.string	"***** VDM start, TotalPicNum=%d, pH264Ctx->CurrPic.structure=%d.\n" )
	.zero	6
.LC888:
	ASCII(.string	"DecVDM ERR\n" )
	.zero	4
.LC892:
	ASCII(.string	"%s:%d Metadata map failed\n" )
	.zero	5
.LC897:
	ASCII(.string	"%s:%d Metadata unmap failed\n" )
	.zero	3
.LC900:
	ASCII(.string	"*****[%s][%d],EL Codec can only dec EL stream in DV_DUAL_VES_IMP stream!!*****\n" )
.LC902:
	ASCII(.string	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****\n" )
	.zero	3
.LC904:
	ASCII(.string	"\n receive streambuff=%p; phy_addr=0x%x; bitstream_length=%d\n" )
	.zero	3
.LC906:
	ASCII(.string	"nal_release_err\n" )
	.zero	7
.LC908:
	ASCII(.string	"cann't find slot for current nal\n" )
	.zero	6
.LC911:
	ASCII(.string	"receive a zero packet\n" )
	.zero	1
.LC917:
	ASCII(.string	"CurrPic.state is 'EMPTY'\n" )
	.zero	6
.LC919:
	ASCII(.string	"StorePicInDPB return(%d) from L%d\n" )
	.zero	5
.LC922:
	ASCII(.string	"directoutput mode\n" )
	.zero	5
.LC924:
	ASCII(.string	"line: %d pImg is NULL!\n" )
.LC926:
	ASCII(.string	"line %d, REPORT_IFRAME_ERR\n" )
	.zero	4
.LC929:
	ASCII(.string	"line %d, return %d\n" )
	.zero	4
.LC931:
	ASCII(.string	"err(%d) > ref_thr(%d)\n" )
	.zero	1
.LC933:
	ASCII(.string	"marking return %d\n" )
	.zero	5
.LC935:
	ASCII(.string	"return value is unexpeced!\n" )
	.zero	4
.LC938:
	ASCII(.string	"line %d: pH264Ctx->DPB.size = %d, ref %d, ltref %d\n" )
	.zero	4
.LC941:
	ASCII(.string	"%s: pos(%d) = pre_pos, force return.\n" )
	.zero	2
.LC943:
	ASCII(.string	"GAP found while DPB is empty!\n" )
	.zero	1
.LC945:
	ASCII(.string	"frame num gap try to fill it \n" )
	.zero	1
.LC947:
	ASCII(.string	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\n" )
	.zero	7
.LC949:
	ASCII(.string	"cann't allocate frame store when gap find\n" )
	.zero	5
.LC951:
	ASCII(.string	"allocate frame store when gap find\n" )
	.zero	4
.LC953:
	ASCII(.string	"line %d: store gap pic err, ret=%d\n" )
	.zero	4
.LC958:
	ASCII(.string	"%s %d frame_store is null!!\n" )
	.zero	3
.LC962:
	ASCII(.string	"line %d: init dpb return %d\n" )
	.zero	3
.LC964:
	ASCII(.string	"mem arrange err, ClearAll\n" )
	.zero	5
.LC967:
	ASCII(.string	"line %d: frame gap(=%d) > dpb size(=%d)\n" )
	.zero	7
.LC969:
	ASCII(.string	"line %d: dec gap failed\n" )
	.zero	7
.LC971:
	ASCII(.string	"line %d: alloc framestore failed\n" )
	.zero	6
.LC973:
	ASCII(.string	"dec_pts: %lld\n" )
	.zero	1
.LC975:
	ASCII(.string	"dec_usertag: %lld\n" )
	.zero	5
.LC977:
	ASCII(.string	"%s %d NULL == pH264Ctx->CurrPic.frame_store!!\n" )
	.zero	1
.LC979:
	ASCII(.string	"get back frm\n" )
	.zero	2
.LC987:
	ASCII(.string	"Start Reason: SliceParaNum, MaxBytesReceived = %d, %d(thr=%d)\n" )
	.zero	1
.LC989:
	ASCII(.string	"Too many slice or bitstream, err!\n" )
	.zero	5
.LC991:
	ASCII(.string	"Start Reason: new_pic_flag\n" )
	.zero	4
.LC993:
	ASCII(.string	"init pic err, find next recover point or next valid sps, pps, or exit\n" )
	.zero	1
.LC995:
	ASCII(.string	"DecList error, ret=%d\n" )
	.zero	1
.LC997:
	ASCII(.string	"dec list err, cur pic poc %d.\n" )
	.zero	1
.LC1000:
	ASCII(.string	"pH264Ctx->TotalNal = %d, type:%d\n" )
	.zero	6
.LC1002:
	ASCII(.string	"stop i want\n" )
	.zero	3
.LC1004:
	ASCII(.string	"svc_extension_flag error:priority_id:%d, pred_flag%d\n" )
	.zero	2
.LC1006:
	ASCII(.string	"%d,%d,%d\n" )
	.zero	6
.LC1008:
	ASCII(.string	"svc stream,nal_header:%x\n" )
	.zero	6
.LC1011:
	ASCII(.string	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=%d\n" )
	.zero	1
.LC1013:
	ASCII(.string	"SliceCheck failed, clear current slice.\n" )
	.zero	7
.LC1016:
	ASCII(.string	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\n" )
	.zero	1
.LC1019:
	ASCII(.string	"%s: PPS decode error.\n" )
	.zero	1
.LC1021:
	ASCII(.string	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\n" )
	.zero	1
.LC1023:
	ASCII(.string	"SPS decode error.\n" )
	.zero	5
.LC1025:
	ASCII(.string	"***** NAL: SEI, nal_unit_type=%d\n" )
	.zero	6
.LC1027:
	ASCII(.string	"SEI decode error.\n" )
	.zero	5
.LC1029:
	ASCII(.string	"***** NAL: AUD, nal_unit_type=%d\n" )
	.zero	6
.LC1031:
	ASCII(.string	"***** NAL: EOSEQ, nal_unit_type=%d\n" )
	.zero	4
.LC1033:
	ASCII(.string	"***** NAL: FILL, nal_unit_type=%d\n" )
	.zero	5
.LC1035:
	ASCII(.string	"***** NAL: EOSTREAM, nal_unit_type=%d\n" )
	.zero	1
.LC1037:
	ASCII(.string	"***** NAL: SPSEXT, nal_unit_type=%d\n" )
	.zero	3
.LC1039:
	ASCII(.string	"***** NAL: AUX, nal_unit_type=%d\n" )
	.zero	6
.LC1041:
	ASCII(.string	"***** NAL: EOPIC, nal_unit_type=%d\n" )
	.zero	4
.LC1043:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:%x\n" )
	.zero	1
.LC1045:
	ASCII(.string	"***** NAL: UNSUPPORT, nal_unit_type=%d\n" )
.LC1053:
	ASCII(.string	"FindTrailZeros ERR\n" )
	.zero	4
.LC1055:
	ASCII(.string	"H264_DecOneNal ERR\n" )
	.zero	4
.LC1063:
	ASCII(.string	"pH264Ctx->CurrPic.frame_store is null pointer\n" )
	.zero	1
.LC1065:
	ASCII(.string	"store pic err, ret = %d\n" )
	.zero	7
.LC1067:
	ASCII(.string	"imode nal store pic err, ret = %d\n" )
	.zero	5
.LC1069:
	ASCII(.string	"imode nal flush dpb err, ret = %d\n" )
	.zero	5
.LC1073:
	ASCII(.string	"cann't find FrameStore\n" )
.LC1075:
	ASCII(.string	"========== H264 FrameStore state(is_used, is_in_dpb, IsOutDPB) ========\n" )
	.zero	7
.LC1077:
	ASCII(.string	"ReadImgNum = %d, NewImgNum = %d\n" )
	.zero	7
.LC1079:
	ASCII(.string	"%02d: %d %d %d\n" )
.LC1081:
	ASCII(.string	"FrameStore leak, ClearAll\n" )
	.bss
	.align	3
.LANCHOR3 = . + 0
.LANCHOR4 = . + 4352
	.type	pps_tmp.12235, %object
	.size	pps_tmp.12235, 2208
pps_tmp.12235:
	.zero	2208
	.type	sps_tmp.12356, %object
	.size	sps_tmp.12356, 4000
sps_tmp.12356:
	.zero	4000
	.type	TmpBuf, %object
	.size	TmpBuf, 68
TmpBuf:
	.zero	68
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
