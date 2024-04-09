#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"avs2.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	AVS2_ue_v.isra.2, %function
AVS2_ue_v.isra.2:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	bls	.L5
	ldr	x1, .LC1
	mov	w2, w0
	mov	w3, -4370
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -4370
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5:
	mov	w1, w0
	mov	x0, x19
	add	w21, w1, 1
	bl	BsSkip
	mov	w1, w21
	mov	x0, x19
	bl	BsShow
	sub	w20, w0, #1
	mov	w1, w21
	mov	x0, x19
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_ue_v.isra.2, .-AVS2_ue_v.isra.2
	.align	3
.LC1:
	.xword	.LC0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AVS2_se_v.isra.3, %function
AVS2_se_v.isra.3:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 32
	mov	x0, x20
	bl	BsShow
	bl	ZerosMS_32
	cmp	w0, 31
	bls	.L11
	mov	w0, 2147483647
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L11:
	mov	w1, w0
	mov	x0, x20
	add	w21, w1, 1
	bl	BsSkip
	mov	w1, w21
	mov	x0, x20
	bl	BsShow
	sub	w0, w0, #1
	asr	w2, w0, 1
	and	w0, w0, 1
	cmp	w0, wzr
	mov	w1, w21
	mov	x0, x20
	neg	w19, w2
	csinc	w19, w19, w2, eq
	bl	BsSkip
	ldr	x21, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_se_v.isra.3, .-AVS2_se_v.isra.3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	AVS2_UpdateSceneBuf.part.7, %function
AVS2_UpdateSceneBuf.part.7:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 16384
	add	x20, x21, 20480
	add	x22, x21, 8192
	bl	_mcount
	add	x19, x19, 3072
	add	x20, x20, 640
	b	.L16
	.p2align 3
.L14:
	add	x19, x19, 104
	cmp	x19, x20
	beq	.L21
.L16:
	ldrb	w0, [x19, 7]
	sub	w0, w0, #5
	uxtb	w0, w0
	cmp	w0, 1
	bhi	.L14
	ldrb	w0, [x19, 6]
	and	w1, w0, 1
	tbz	x0, 1, .L14
	ldr	x0, [x22, 2952]
	cmp	x0, x19
	beq	.L14
	strb	w1, [x19, 6]
	cbnz	w1, .L14
	strb	wzr, [x19, 5]
	mov	w2, 0
	ldr	w1, [x19, 56]
	add	x19, x19, 104
	ldr	w0, [x21, 4]
	bl	FSP_SetRef
	cmp	x19, x20
	bne	.L16
.L21:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_UpdateSceneBuf.part.7, .-AVS2_UpdateSceneBuf.part.7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_Vfmw_EpbRemove
	.type	AVS2_Vfmw_EpbRemove, %function
AVS2_Vfmw_EpbRemove:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x23, x19, 56
	add	x24, x19, 96
	bl	_mcount
	mov	w1, 8
	mov	x0, x23
	ldr	w21, [x23, 24]
	bl	BsGet
	strb	w0, [x19, 96]
	mov	w1, 8
	mov	x0, x23
	sub	w21, w21, #3
	bl	BsGet
	strb	w0, [x19, 97]
	mov	w1, 8
	mov	x0, x23
	bl	BsGet
	strb	w0, [x19, 98]
	mov	w1, 24
	mov	x0, x23
	bl	BsShow
	mov	w3, w0
	lsr	w25, w0, 8
	cbz	w21, .L32
	mov	w22, 3
	mov	w20, 16
	b	.L28
	.p2align 3
.L24:
	add	w20, w20, 8
	orr	w25, w1, w25, lsl 8
.L25:
	cmp	w20, 23
	mov	w1, 8
	mov	x0, x23
	sub	w21, w21, #1
	lsl	w19, w3, 8
	ble	.L26
	cmp	w22, 511
	sub	w20, w20, #8
	lsr	w2, w25, w20
	bhi	.L27
	strb	w2, [x24, w22, uxtw]
	add	w22, w22, 1
.L26:
	bl	BsGet
	mov	w1, 24
	mov	x0, x23
	bl	BsShow
	uxtb	w0, w0
	orr	w3, w0, w19
	cbz	w21, .L34
.L28:
	and	w0, w3, 16777215
	and	w1, w3, 255
	cmp	w0, 2
	bne	.L24
	ubfx	x0, x3, 2, 6
	add	w20, w20, 6
	orr	w25, w0, w25, lsl 6
	b	.L25
	.p2align 3
.L27:
	mov	w1, 32
	mov	x0, x23
	bl	BsShow
	uxtb	w2, w0
	ldr	x1, .LC6
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L34:
	cmp	w20, 16
	mov	w2, w22
	ble	.L23
	cmp	w22, 511
	bhi	.L27
	mov	w0, 24
	lsr	w25, w25, 16
	sub	w0, w0, w20
	lsl	w0, w25, w0
	uxtb	w0, w0
	strb	w0, [x24, w22, uxtw]
	cmp	w0, wzr
	csinc	w2, w22, w22, eq
.L23:
	mov	x1, x24
	mov	x0, x23
	bl	BsInit
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L32:
	mov	w2, 3
	b	.L23
	.size	AVS2_Vfmw_EpbRemove, .-AVS2_Vfmw_EpbRemove
	.align	3
.LC6:
	.xword	.LC5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SkipToNextStartCode
	.type	AVS2_SkipToNextStartCode, %function
AVS2_SkipToNextStartCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	mov	x0, x20
	bl	BsToNextByte
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w21, w1, w0, lt
	asr	w21, w21, 3
	sub	w21, w21, #3
	cmp	w21, wzr
	bgt	.L42
	b	.L39
	.p2align 3
.L45:
	bl	BsSkip
	cmp	w19, w21
	beq	.L39
.L42:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	mov	w2, w0
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L45
	mov	w0, w2
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L39:
	mov	w2, 0
	ldr	x21, [sp, 32]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_SkipToNextStartCode, .-AVS2_SkipToNextStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DumpDpbStatus
	.type	AVS2_DumpDpbStatus, %function
AVS2_DumpDpbStatus:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	stp	x19, x20, [sp, 48]
	stp	x21, x22, [sp, 64]
	stp	x23, x24, [sp, 80]
	str	x25, [sp, 96]
	mov	x19, x0
	mov	x0, x30
	uxtb	w21, w1
	add	x19, x19, 16384
	bl	_mcount
	mov	w25, 0
	ldr	x1, .LC12
	mov	w0, 32
	mov	w20, 0
	add	x19, x19, 3078
	bl	dprint_vfmw
	ldr	x1, .LC14
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x23, .LC17
	cmp	w21, 1
	ldr	x22, .LC10
	ldr	x24, .LC15
	cset	w21, eq
	b	.L49
	.p2align 3
.L47:
	add	w20, w20, 1
	add	x19, x19, 104
	cmp	w20, 16
	beq	.L55
.L49:
	ldrb	w4, [x19]
	cmp	w4, wzr
	cset	w0, ne
	orr	w0, w21, w0
	cbz	w0, .L47
	ldrb	w3, [x19, 1]
	mov	w2, w20
	mov	x1, x23
	mov	w0, 32
	cmp	w3, 6
	add	w25, w25, 1
	uxtb	x5, w3
	mov	x3, x22
	bhi	.L48
	ldr	x3, [x24, x5, lsl 3]
.L48:
	ldr	w8, [x19, 74]
	add	w20, w20, 1
	ldrsh	w7, [x19, -6]
	add	x19, x19, 104
	ldrb	w6, [x19, -106]
	ldrb	w5, [x19, -105]
	str	w8, [sp, 24]
	ldr	w8, [x19, -50]
	str	w8, [sp, 16]
	ldr	w8, [x19, -54]
	str	w8, [sp, 8]
	ldrsh	w8, [x19, -108]
	str	w8, [sp]
	bl	dprint_vfmw
	cmp	w20, 16
	bne	.L49
.L55:
	ldr	x1, .LC19
	mov	w2, w25
	mov	w0, 32
	bl	dprint_vfmw
	add	sp, x29, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	AVS2_DumpDpbStatus, .-AVS2_DumpDpbStatus
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC15:
	.xword	.LANCHOR0
	.align	3
.LC17:
	.xword	.LC16
	.align	3
.LC19:
	.xword	.LC18
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ClearPacket
	.type	AVS2_ClearPacket, %function
AVS2_ClearPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 16384
	bl	_mcount
	ldr	w0, [x20, 4]
	ldr	w1, [x19, 2920]
	bl	SM_ReleaseStreamSeg
	ldrb	w0, [x19, 2906]
	cbnz	w0, .L56
	ldrb	w0, [x19, 2994]
	cmp	w0, 1
	beq	.L61
.L56:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L61:
	ldr	w0, [x19, 3000]
	cbz	w0, .L56
	ldr	w1, [x19, 3008]
	ldr	w0, [x20, 4]
	bl	SM_ReleaseStreamSeg
	b	.L56
	.size	AVS2_ClearPacket, .-AVS2_ClearPacket
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ClearPicSlice
	.type	AVS2_ClearPicSlice, %function
AVS2_ClearPicSlice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	w0, [x21, 1748]
	cbnz	w0, .L69
	b	.L66
	.p2align 3
.L64:
	ldr	w0, [x21, 1748]
	cmp	w0, w20
	bls	.L66
.L69:
	uxtw	x1, w20
	ldr	w0, [x21, 4]
	lsl	x19, x1, 5
	add	w20, w20, 1
	add	x19, x19, x1, lsl 2
	add	x19, x21, x19
	ldr	w1, [x19, 1780]
	bl	SM_ReleaseStreamSeg
	ldrh	w0, [x19, 1776]
	cmp	w0, 256
	bne	.L64
	ldr	w0, [x19, 1764]
	cbz	w0, .L64
	ldr	w1, [x19, 1784]
	ldr	w0, [x21, 4]
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x21, 1748]
	cmp	w0, w20
	bhi	.L69
.L66:
	str	wzr, [x21, 1748]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_ClearPicSlice, .-AVS2_ClearPicSlice
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ClearDpb
	.type	AVS2_ClearDpb, %function
AVS2_ClearDpb:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 16384
	add	x20, x21, 20480
	bl	_mcount
	add	x19, x19, 3078
	add	x20, x20, 646
	b	.L75
	.p2align 3
.L74:
	add	x19, x19, 104
	cmp	x19, x20
	beq	.L80
.L75:
	ldrb	w0, [x19]
	cbz	w0, .L74
	ldr	w1, [x19, 50]
	mov	w2, 0
	ldr	w0, [x21, 4]
	add	x19, x19, 104
	bl	FSP_ClearLogicFs
	strb	wzr, [x19, -104]
	cmp	x19, x20
	bne	.L75
.L80:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_ClearDpb, .-AVS2_ClearDpb
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SequenceDisplayExtension
	.type	AVS2_SequenceDisplayExtension, %function
AVS2_SequenceDisplayExtension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 56
	add	x19, x19, 16384
	bl	_mcount
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1020]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1024]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1028]
	cbnz	w0, .L87
.L82:
	mov	w1, 14
	mov	x0, x20
	add	x19, x19, 1020
	bl	BsGet
	str	w0, [x19, 24]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 28]
	mov	w1, 14
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 32]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 36]
	cmp	w0, 1
	mov	w21, w0
	beq	.L88
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L87:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1032]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1036]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1040]
	b	.L82
	.p2align 3
.L88:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 40]
	mov	w1, w21
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 44]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_SequenceDisplayExtension, .-AVS2_SequenceDisplayExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_CopyrightExtension
	.type	AVS2_CopyrightExtension, %function
AVS2_CopyrightExtension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 56
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 7
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 20
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_CopyrightExtension, .-AVS2_CopyrightExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_CameraParametersExtension
	.type	AVS2_CameraParametersExtension, %function
AVS2_CameraParametersExtension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 56
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 7
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 22
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_CameraParametersExtension, .-AVS2_CameraParametersExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_TemporalScalabilityExtension
	.type	AVS2_TemporalScalabilityExtension, %function
AVS2_TemporalScalabilityExtension:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 56
	mov	w21, 0
	bl	_mcount
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	add	x1, x22, 16384
	add	x23, x1, 2140
	str	w0, [x1, 2140]
	cbz	w0, .L97
	.p2align 2
.L95:
	add	x19, x22, x21, uxtw 2
	mov	w1, 4
	add	x19, x19, 16384
	mov	x0, x20
	add	w21, w21, 1
	bl	BsGet
	mov	w1, 18
	str	w0, [x19, 2144]
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 2172]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	mov	w1, 12
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 2204]
	ldr	w0, [x23]
	cmp	w0, w21
	bhi	.L95
.L97:
	mov	w0, 1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	AVS2_TemporalScalabilityExtension, .-AVS2_TemporalScalabilityExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_PictureDisplayExtension
	.type	AVS2_PictureDisplayExtension, %function
AVS2_PictureDisplayExtension:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	add	x20, x23, 56
	add	x22, x23, 12288
	bl	_mcount
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	ldr	w0, [x22, 2704]
	cmp	w0, 1
	beq	.L115
	ldr	w0, [x22, 5340]
	cbnz	w0, .L116
.L100:
	mov	w0, 1
	str	w0, [x23, 14980]
.L102:
	mov	w21, 0
	add	x22, x22, 2692
	.p2align 2
.L104:
	add	x19, x23, x21, sxtw 2
	mov	w1, 16
	add	x19, x19, 16384
	mov	x0, x20
	bl	BsGet
	mov	w1, 1
	str	w0, [x19, 2116]
	mov	x0, x20
	add	w21, w21, w1
	bl	BsGet
	mov	w1, 16
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 2128]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	ldr	w0, [x22]
	cmp	w0, w21
	bhi	.L104
	mov	x0, x20
	bl	AVS2_SkipToNextStartCode
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L116:
	ldr	w0, [x22, 5348]
	cmp	w0, 1
	beq	.L103
.L101:
	mov	w0, 2
	str	w0, [x23, 14980]
	b	.L102
	.p2align 3
.L115:
	ldr	w0, [x22, 5348]
	cmp	w0, 1
	bne	.L100
	ldr	w0, [x22, 5344]
	cmp	w0, 1
	bne	.L101
	.p2align 2
.L103:
	mov	w0, 3
	str	w0, [x23, 14980]
	b	.L102
	.size	AVS2_PictureDisplayExtension, .-AVS2_PictureDisplayExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_MasteringMetadataExtension
	.type	AVS2_MasteringMetadataExtension, %function
AVS2_MasteringMetadataExtension:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 16384
	add	x19, x19, 56
	bl	_mcount
	add	x20, x21, 2240
	mov	w1, 4
	mov	x0, x19
	add	x22, x21, 2252
	bl	BsGet
.L118:
	add	x20, x20, 4
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, -4]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, 8]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	cmp	x20, x22
	bne	.L118
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 2264]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 2268]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 2272]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 2276]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 2280]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 2284]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	mov	w1, 16
	mov	x0, x19
	bl	BsGet
	mov	w1, 1
	str	w1, [x21, 2232]
	str	w1, [x21, 2236]
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_MasteringMetadataExtension, .-AVS2_MasteringMetadataExtension
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_Extension
	.type	AVS2_Extension, %function
AVS2_Extension:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 56
	bl	_mcount
	mov	w1, 32
	mov	x0, x19
	bl	BsGet
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	sub	w0, w0, #2
	cmp	w0, 10
	bls	.L131
.L121:
	mov	w1, 4
	mov	x0, x19
	bl	BsSkip
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L131:
	ldr	x1, .LC20
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx123
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx123:
	.section	.rodata
	.align	0
	.align	2
.L123:
	.byte	(.L122 - .Lrtx123) / 4
	.byte	(.L124 - .Lrtx123) / 4
	.byte	(.L125 - .Lrtx123) / 4
	.byte	(.L121 - .Lrtx123) / 4
	.byte	(.L121 - .Lrtx123) / 4
	.byte	(.L126 - .Lrtx123) / 4
	.byte	(.L121 - .Lrtx123) / 4
	.byte	(.L121 - .Lrtx123) / 4
	.byte	(.L127 - .Lrtx123) / 4
	.byte	(.L128 - .Lrtx123) / 4
	.byte	(.L130 - .Lrtx123) / 4
	.text
	.p2align 3
.L130:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L122:
	mov	x0, x20
	bl	AVS2_SequenceDisplayExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L124:
	mov	x0, x20
	bl	AVS2_TemporalScalabilityExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L125:
	mov	x0, x20
	bl	AVS2_CopyrightExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L126:
	mov	x0, x20
	bl	AVS2_PictureDisplayExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L127:
	mov	x0, x20
	bl	AVS2_MasteringMetadataExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L128:
	mov	x0, x20
	bl	AVS2_CameraParametersExtension
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_Extension, .-AVS2_Extension
	.align	3
.LC20:
	.xword	.L123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_User_Data
	.type	AVS2_User_Data, %function
AVS2_User_Data:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 56
	bl	_mcount
	ldr	x1, .LC22
	mov	w0, 7
	bl	dprint_vfmw
	mov	w1, 32
	mov	x0, x19
	bl	BsGet
	b	.L133
	.p2align 3
.L136:
	ldr	w4, [x19, 24]
	ldr	w3, [x19, 32]
	add	w2, w3, 8
	cmp	w2, w4, lsl 3
	bhi	.L137
	bl	BsGet
.L133:
	mov	w1, 24
	mov	x0, x19
	bl	BsShow
	cmp	w0, 1
	mov	w1, 8
	mov	x0, x19
	bne	.L136
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L137:
	ldr	x2, .LC23
	mov	w0, 1
	ldr	x1, .LC25
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_User_Data, .-AVS2_User_Data
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC23:
	.xword	.LANCHOR1
	.align	3
.LC25:
	.xword	.LC24
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ConvertHDRInfo
	.type	AVS2_ConvertHDRInfo, %function
AVS2_ConvertHDRInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x21, x1
	mov	x0, x30
	mov	x20, x2
	bl	_mcount
	ldr	w0, [x21, 4]
	add	x3, x19, 496
	strb	w0, [x19, 488]
	mov	x0, x20
	add	x2, x20, 20
	ldr	w1, [x21, 12]
	strb	w1, [x19, 489]
	ldr	w1, [x21, 20]
	strb	w1, [x19, 490]
	ldr	w1, [x21, 16]
	str	w1, [x19, 492]
	ldr	w1, [x0], 8
	strb	w1, [x19, 464]
.L139:
	ldr	w1, [x0]
	add	x0, x0, 4
	strh	w1, [x3]
	add	x3, x3, 2
	cmp	x0, x2
	ldr	w1, [x0, 8]
	strh	w1, [x3, 4]
	bne	.L139
	ldr	w0, [x20, 32]
	strh	w0, [x19, 508]
	ldr	w0, [x20, 36]
	strh	w0, [x19, 510]
	ldr	w0, [x20, 40]
	str	w0, [x19, 512]
	ldr	w0, [x20, 44]
	str	w0, [x19, 516]
	ldr	w0, [x20, 4]
	strb	w0, [x19, 465]
	ldr	w0, [x20, 48]
	str	w0, [x19, 520]
	ldr	w0, [x20, 52]
	str	w0, [x19, 524]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_ConvertHDRInfo, .-AVS2_ConvertHDRInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_WriteSliceMsg
	.type	AVS2_WriteSliceMsg, %function
AVS2_WriteSliceMsg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 1748]
	cmp	w2, 255
	bhi	.L147
	add	x20, x19, 56
	mov	w1, 24
	mov	x0, x20
	bl	BsSkip
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	cmp	w0, 143
	mov	w21, w0
	bhi	.L148
	add	x22, x19, 12288
	ldr	w2, [x22, 2772]
	mov	w0, 144
	ldr	w1, [x22, 2720]
	lsl	w0, w0, w2
	cmp	w1, w0
	bhi	.L149
.L145:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	mov	w23, w0
	ldr	w2, [x22, 2772]
	mov	w0, 255
	ldr	w1, [x22, 2712]
	lsl	w0, w0, w2
	cmp	w1, w0
	bhi	.L150
.L146:
	ldr	w1, [x19, 1748]
	mov	w0, 1
	add	x3, x19, 16384
	add	w4, w1, w0
	uxtw	x1, w1
	lsl	x2, x1, 5
	add	x1, x2, x1, lsl 2
	add	x1, x19, x1
	strh	w21, [x1, 1754]
	strh	w23, [x1, 1752]
	ldrh	w2, [x22, 5104]
	madd	w21, w2, w21, w23
	str	w21, [x1, 1756]
	ldr	w2, [x3, 2912]
	str	w2, [x1, 1760]
	ldr	w2, [x3, 3000]
	str	w2, [x1, 1764]
	ldr	w2, [x3, 2916]
	str	w2, [x1, 1768]
	ldr	w2, [x3, 3004]
	str	w2, [x1, 1772]
	ldrb	w2, [x3, 2906]
	strb	w2, [x1, 1776]
	ldrb	w2, [x3, 2994]
	strb	w2, [x1, 1777]
	ldr	w2, [x3, 2920]
	str	w2, [x1, 1780]
	ldr	w2, [x3, 3008]
	str	w2, [x1, 1784]
	str	w4, [x19, 1748]
	ldr	w1, [x19, 12]
	orr	w1, w1, 32768
	str	w1, [x19, 12]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L147:
	ldr	x1, .LC27
	mov	w3, 256
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L148:
	ldr	x1, .LC29
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L150:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	add	w23, w23, w0, lsl 8
	b	.L146
	.p2align 3
.L149:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	add	w21, w21, w0, lsl 7
	b	.L145
	.size	AVS2_WriteSliceMsg, .-AVS2_WriteSliceMsg
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC29:
	.xword	.LC28
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_Head_GetRefConfigSet
	.type	AVS2_Head_GetRefConfigSet, %function
AVS2_Head_GetRefConfigSet:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	w20, 0
	bl	_mcount
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	str	w0, [x19]
	mov	w1, 3
	mov	x0, x21
	bl	BsGet
	str	w0, [x19, 4]
	cbz	w0, .L156
	.p2align 2
.L159:
	mov	w1, 6
	mov	x0, x21
	bl	BsGet
	add	x1, x19, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 8]
	ldr	w0, [x19, 4]
	cmp	w0, w20
	bhi	.L159
.L156:
	mov	w1, 3
	mov	x0, x21
	mov	w20, 0
	bl	BsGet
	str	w0, [x19, 36]
	cbz	w0, .L154
	.p2align 2
.L158:
	mov	w1, 6
	mov	x0, x21
	bl	BsGet
	add	x1, x19, x20, uxtw 2
	add	w20, w20, 1
	str	w0, [x1, 40]
	ldr	w0, [x19, 36]
	cmp	w0, w20
	bhi	.L158
.L154:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_Head_GetRefConfigSet, .-AVS2_Head_GetRefConfigSet
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_WeightQuantMatrix
	.type	AVS2_WeightQuantMatrix, %function
AVS2_WeightQuantMatrix:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	add	x23, x22, 16
	mov	x20, x2
	bl	_mcount
	.p2align 2
.L165:
	mov	x19, 0
	.p2align 2
.L164:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	strb	w0, [x22, x19]
	add	x19, x19, 1
	cmp	x19, 4
	bne	.L164
	add	x22, x22, 4
	cmp	x22, x23
	bne	.L165
	add	x22, x21, 64
	.p2align 2
.L167:
	mov	x19, 0
	.p2align 2
.L166:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	strb	w0, [x21, x19]
	add	x19, x19, 1
	cmp	x19, 8
	bne	.L166
	add	x21, x21, 8
	cmp	x21, x22
	bne	.L167
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	AVS2_WeightQuantMatrix, .-AVS2_WeightQuantMatrix
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupWqMatrix84DataIdx01
	.type	AVS2_SetupWqMatrix84DataIdx01, %function
AVS2_SetupWqMatrix84DataIdx01:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x29, 56
	bl	_mcount
	ldr	x22, .LC35
	mov	x2, 6
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x22, 96]
	blr	x3
	ldr	x20, .LC34
	ldr	w0, [x19, 2716]
	cbz	w0, .L199
	cmp	w0, 1
	beq	.L200
	cmp	w0, 2
	beq	.L201
.L174:
	ldr	w0, [x19, 2720]
	cbz	w0, .L188
	cmp	w0, 1
	beq	.L202
	add	x3, x20, 240
	add	x4, x20, 176
	mov	x0, x19
	add	x7, x3, 16
	mov	x6, x19
	mov	w2, 0
	.p2align 2
.L181:
	mov	x1, 0
	b	.L184
	.p2align 3
.L182:
	ldrb	w2, [x3, x1]
.L184:
	sub	x5, x29, #4032
	add	x2, x5, x2, sxtw
	add	x5, x6, x1
	add	x1, x1, 1
	cmp	x1, 4
	ldrb	w2, [x2, 4088]
	strb	w2, [x5, 2486]
	bne	.L182
	add	x3, x3, 4
	add	x6, x6, 4
	cmp	x3, x7
	beq	.L183
	ldrb	w2, [x3]
	b	.L181
.L188:
	add	x4, x20, 16
	add	x3, x20, 80
.L180:
	mov	x0, x19
	add	x7, x3, 16
	mov	x6, x19
	mov	w2, 0
	b	.L181
	.p2align 3
.L183:
	add	x5, x4, 64
	.p2align 2
.L186:
	mov	x1, 0
	.p2align 2
.L185:
	ldrb	w2, [x4, x1]
	sub	x6, x29, #4032
	add	x3, x0, x1
	add	x1, x1, 1
	add	x2, x6, x2
	cmp	x1, 8
	ldrb	w2, [x2, 4088]
	strb	w2, [x3, 2502]
	bne	.L185
	add	x4, x4, 8
	add	x0, x0, 8
	cmp	x4, x5
	bne	.L186
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L199:
	ldr	x3, [x22, 104]
	mov	x2, 6
	mov	x0, x21
	add	x1, x20, 256
	blr	x3
	b	.L174
.L200:
	mov	x0, 0
	mov	w2, 67
	b	.L177
	.p2align 3
.L203:
	ldrb	w2, [x0, x3]
.L177:
	add	x1, x19, x0
	add	x3, x20, 264
	ldrb	w1, [x1, 2474]
	add	w1, w2, w1
	strb	w1, [x21, x0]
	add	x0, x0, 1
	cmp	x0, 6
	bne	.L203
	b	.L174
.L201:
	mov	x0, 0
	mov	w2, 64
	b	.L179
	.p2align 3
.L204:
	ldrb	w2, [x0, x3]
.L179:
	add	x1, x19, x0
	add	x3, x20, 272
	ldrb	w1, [x1, 2480]
	add	w1, w2, w1
	strb	w1, [x21, x0]
	add	x0, x0, 1
	cmp	x0, 6
	bne	.L204
	b	.L174
.L202:
	add	x4, x20, 96
	add	x3, x20, 160
	b	.L180
	.size	AVS2_SetupWqMatrix84DataIdx01, .-AVS2_SetupWqMatrix84DataIdx01
	.align	3
.LC34:
	.xword	.LANCHOR1
	.align	3
.LC35:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupWqMatrix84
	.type	AVS2_SetupWqMatrix84, %function
AVS2_SetupWqMatrix84:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 2696]
	cbz	w0, .L210
	ldr	w0, [x19, 2700]
	cbz	w0, .L211
	cmp	w0, 1
	beq	.L212
.L205:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L211:
	ldr	w0, [x19, 88]
	cbnz	w0, .L209
	ldr	x21, .LC38
	mov	x2, 16
	ldr	x20, .LC39
	add	x0, x19, 2486
	ldr	x3, [x21, 104]
	add	x1, x20, 280
	blr	x3
	ldr	x3, [x21, 104]
	add	x1, x20, 296
	mov	x2, 64
	add	x0, x19, 2502
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L210:
	ldr	x20, .LC38
	mov	x2, 16
	mov	w1, 64
	add	x0, x19, 2486
	ldr	x3, [x20, 96]
	blr	x3
	mov	x2, 64
	ldr	x3, [x20, 96]
	add	x0, x19, 2502
	mov	w1, w2
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L209:
	ldr	x20, .LC38
	add	x1, x19, 108
	mov	x2, 16
	add	x0, x19, 2486
	ldr	x3, [x20, 104]
	blr	x3
	ldr	x3, [x20, 104]
	add	x1, x19, 124
	mov	x2, 64
	add	x0, x19, 2502
	blr	x3
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L212:
	mov	x0, x19
	bl	AVS2_SetupWqMatrix84DataIdx01
	b	.L205
	.size	AVS2_SetupWqMatrix84, .-AVS2_SetupWqMatrix84
	.align	3
.LC38:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC39:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ALF_ParameterSet
	.type	AVS2_ALF_ParameterSet, %function
AVS2_ALF_ParameterSet:
	sub	sp, sp, #608
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
	ldr	w24, [x19, 252]
	cmp	w24, 1
	beq	.L214
.L242:
	ldr	w0, [x19, 256]
	cmp	w0, 1
	beq	.L271
.L216:
	ldr	w0, [x19, 260]
	cmp	w0, 1
	beq	.L248
	mov	w0, 1
.L264:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 608
	ret
	.p2align 3
.L248:
	mov	x0, x20
	add	x22, x19, 948
	mov	w21, 0
	bl	AVS2_se_v.isra.3
	mov	w3, w0
	str	w0, [x19, 944]
	b	.L253
	.p2align 3
.L251:
	bl	AVS2_se_v.isra.3
	add	w21, w21, 1
	str	w0, [x22], 4
	cmp	w21, 8
	mov	w3, w0
	beq	.L272
.L253:
	add	w1, w3, 64
	mov	x0, x20
	cmp	w1, 127
	bls	.L251
	ldr	x1, .LC59
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L264
	.p2align 3
.L271:
	mov	x0, x20
	add	x22, x19, 912
	mov	w21, 0
	bl	AVS2_se_v.isra.3
	mov	w3, w0
	str	w0, [x19, 908]
	b	.L247
	.p2align 3
.L245:
	bl	AVS2_se_v.isra.3
	add	w21, w21, 1
	str	w0, [x22], 4
	cmp	w21, 8
	mov	w3, w0
	beq	.L273
.L247:
	add	w1, w3, 64
	mov	x0, x20
	cmp	w1, 127
	bls	.L245
	ldr	x1, .LC55
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L264
	.p2align 3
.L214:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	cmp	w0, 15
	str	w0, [x19, 264]
	bhi	.L217
	cmn	w0, #1
	mov	w25, 0
	beq	.L274
	str	w24, [x29, 108]
.L256:
	cmp	w25, wzr
	ccmp	w0, 15, 4, gt
	beq	.L221
	mov	x0, x20
	sxtw	x23, w25
	bl	AVS2_ue_v.isra.2
	sub	w2, w0, #1
	add	x1, x19, x23, lsl 2
	cmp	w2, 14
	str	w0, [x1, 268]
	bhi	.L275
.L223:
	mov	x0, x20
	lsl	x22, x23, 2
	add	x27, x22, x23, lsl 5
	add	x26, x29, 128
	bl	AVS2_se_v.isra.3
	mov	w3, w0
	add	x0, x29, 704
	add	x28, x27, 4
	add	x0, x0, x27
	mov	w21, 0
	sub	x0, x0, #4096
	add	x28, x26, x28
	str	w3, [x0, 3520]
	b	.L225
	.p2align 3
.L277:
	ldr	w2, [x24, 268]
	cmp	w2, 63
	bhi	.L228
	bl	AVS2_se_v.isra.3
	add	w21, w21, 1
	str	w0, [x28], 4
	cmp	w21, 8
	mov	w3, w0
	beq	.L276
.L225:
	cmn	w3, #64
	add	x24, x19, x22
	mov	x0, x20
	bge	.L277
.L228:
	ldr	x1, .LC49
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L264
	.p2align 3
.L221:
	cmp	w25, wzr
	sxtw	x23, w25
	ble	.L223
	add	x0, x19, x23, lsl 2
	ldr	w1, [x29, 108]
	str	w1, [x0, 268]
	b	.L223
	.p2align 3
.L217:
	ldr	x1, .LC43
	mov	w2, w0
	mov	w0, w24
	bl	dprint_vfmw
	mov	w0, 0
	b	.L264
.L275:
	ldr	x1, .LC45
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L264
.L274:
	strb	wzr, [x29, 112]
	mov	w0, 0
	add	x26, x29, 128
	sub	x21, x29, #3392
.L232:
	sxtw	x3, w0
	.p2align 2
.L240:
	add	x1, x21, x3
	add	x2, x21, x0, sxtw
	add	w0, w0, 1
	cmp	w0, 15
	ldrb	w1, [x1, 3504]
	strb	w1, [x2, 3504]
	ble	.L240
.L241:
	ldr	x23, .LC50
	add	x22, x19, 332
	add	x24, x19, 908
	mov	w0, 0
	add	x23, x23, 361
	ldr	x25, .LC51
	b	.L239
	.p2align 3
.L278:
	ldrb	w0, [x23], 1
.L239:
	add	x0, x21, x0, sxtw
	ldr	x3, [x25, 104]
	mov	x2, 36
	ldrb	w0, [x0, 3504]
	lsl	x1, x0, 5
	add	x1, x1, x0, lsl 2
	mov	x0, x22
	add	x1, x26, x1
	add	x22, x22, x2
	blr	x3
	cmp	x22, x24
	bne	.L278
	b	.L242
.L272:
	add	w0, w3, 1088
	cmp	w0, 2159
	bhi	.L249
	add	x0, x19, 944
	add	x3, x19, 976
	mov	w1, 64
	.p2align 2
.L250:
	ldr	w2, [x0], 4
	cmp	x3, x0
	sub	w1, w1, w2, lsl 1
	bne	.L250
	ldr	w2, [x19, 976]
	mov	w0, 1
	add	w1, w2, w1
	str	w1, [x19, 976]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 608
	ret
.L276:
	cmn	w3, #1088
	blt	.L226
	ldr	w0, [x24, 268]
	cmp	w0, 1071
	bhi	.L226
	add	x0, x29, 128
	mov	w1, 64
	add	x27, x0, x27
	mov	x0, 0
	.p2align 2
.L227:
	ldr	w2, [x27, x0]
	add	x0, x0, 4
	cmp	x0, 32
	sub	w1, w1, w2, lsl 1
	bne	.L227
	lsl	x3, x23, 5
	add	x2, x29, 704
	add	x3, x3, x23, lsl 2
	ldr	w0, [x19, 264]
	add	x3, x2, x3
	add	w25, w25, 1
	sub	x3, x3, #4096
	add	w7, w0, 1
	cmp	w7, w25
	ldr	w2, [x3, 3552]
	add	w1, w2, w1
	str	w1, [x3, 3552]
	bhi	.L256
	strb	wzr, [x29, 112]
	cmp	w7, 1
	bls	.L254
	mov	w2, 0
	mov	w5, 0
	mov	w9, 1
	sub	x21, x29, #3392
	.p2align 2
.L233:
	add	x0, x19, x9, sxtw 2
	ldr	w8, [x0, 268]
	subs	w6, w8, #1
	beq	.L238
	mov	w0, w5
	mov	w1, 0
	b	.L237
	.p2align 3
.L234:
	ldrb	w2, [x4, 3504]
.L237:
	add	w0, w0, 1
	add	w1, w1, 1
	cmp	w1, w6
	add	x3, x21, x0, sxtw
	uxtb	w0, w0
	add	x4, x21, x0, sxtw
	strb	w2, [x3, 3504]
	bne	.L234
	add	w5, w5, 1
	sub	w8, w8, #2
	add	w5, w8, w5, uxtb
	uxtb	w5, w5
	add	x0, x21, x5, sxtw
	ldrb	w2, [x0, 3504]
.L238:
	add	w5, w5, 1
	add	w9, w9, 1
	add	w2, w2, 1
	cmp	w7, w9
	add	x0, x21, x5, sxtw
	uxtb	w5, w5
	strb	w2, [x0, 3504]
	beq	.L235
	add	x0, x21, x5, sxtw
	ldrb	w2, [x0, 3504]
	b	.L233
.L235:
	cmp	w5, 15
	mov	w0, w5
	ble	.L232
	b	.L241
.L273:
	add	w0, w3, 1088
	cmp	w0, 2159
	bhi	.L243
	add	x0, x19, 908
	add	x3, x19, 940
	mov	w1, 64
	.p2align 2
.L244:
	ldr	w2, [x0], 4
	cmp	x3, x0
	sub	w1, w1, w2, lsl 1
	bne	.L244
	ldr	w0, [x19, 940]
	add	w1, w0, w1
	str	w1, [x19, 940]
	b	.L216
.L243:
	ldr	x1, .LC53
	mov	w2, w3
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L264
.L249:
	ldr	x1, .LC57
	mov	w2, w3
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L264
.L254:
	mov	w0, 0
	sub	x21, x29, #3392
	b	.L232
.L226:
	ldr	x1, .LC47
	mov	w2, w3
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L264
	.size	AVS2_ALF_ParameterSet, .-AVS2_ALF_ParameterSet
	.align	3
.LC43:
	.xword	.LC42
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.align	3
.LC50:
	.xword	.LANCHOR1
	.align	3
.LC51:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC53:
	.xword	.LC52
	.align	3
.LC55:
	.xword	.LC54
	.align	3
.LC57:
	.xword	.LC56
	.align	3
.LC59:
	.xword	.LC58
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DeriveMaxDpbNum
	.type	AVS2_DeriveMaxDpbNum, %function
AVS2_DeriveMaxDpbNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 4]
	cmp	w1, 34
	bls	.L288
	ldr	w0, [x19, 16]
	cmp	w1, 74
	ldr	w2, [x19, 24]
	add	w0, w0, 7
	add	w2, w2, 7
	and	w0, w0, -8
	and	w2, w2, -8
	mul	w2, w0, w2
	bhi	.L282
	mov	w0, 13369344
.L287:
	udiv	w0, w0, w2
	mov	w1, 16
	mov	w4, 7
	mov	w3, 10
	cmp	w0, w1
	csel	w0, w0, w1, ls
	cmp	w2, 2088960
	sub	w0, w0, #1
	uxtb	w1, w0
	mov	w0, 6
	csel	w4, w0, w4, hi
	mov	w0, 15
	csel	w2, w3, w0, hi
	cmp	w1, w4
	csel	w0, w1, w4, cs
	cmp	w0, w2
	csel	w0, w0, w2, ls
	strb	w0, [x19, 2412]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L282:
	cmp	w1, 90
	mov	w0, 56623104
	bls	.L287
	mov	w0, 213909504
	b	.L287
	.p2align 3
.L288:
	mov	w0, 15
	strb	w0, [x19, 2412]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_DeriveMaxDpbNum, .-AVS2_DeriveMaxDpbNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_IntraPictureHeader
	.type	AVS2_IntraPictureHeader, %function
AVS2_IntraPictureHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x19, x22, 16384
	add	x20, x22, 56
	bl	_mcount
	ldr	x24, .LC60
	ldr	w3, [x22, 12]
	mov	x2, 16
	mov	w1, 0
	add	x0, x19, 1336
	and	w3, w3, -262145
	str	w3, [x22, 12]
	ldr	x3, [x24, 96]
	blr	x3
	mov	x0, x22
	bl	AVS2_Vfmw_EpbRemove
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1164]
	ldr	w0, [x22, 14984]
	cmp	w0, 72
	beq	.L363
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x19, 1172]
	beq	.L364
.L291:
	add	x21, x22, 12288
	ldr	w0, [x21, 2784]
	cbz	w0, .L365
	str	wzr, [x19, 1208]
.L294:
	add	x23, x19, 1068
	str	wzr, [x19, 1212]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 148]
	ldr	w0, [x21, 2764]
	cmp	w0, 1
	beq	.L366
.L296:
	str	wzr, [x23, 152]
.L297:
	ldr	w0, [x21, 2760]
	cbnz	w0, .L298
	ldr	w1, [x19, 1208]
	cbz	w1, .L299
	ldr	w0, [x19, 1212]
	cmp	w0, 1
	beq	.L299
.L298:
	str	wzr, [x19, 1224]
.L300:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1228]
	cbz	w0, .L301
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtw	x1, w0
	lsl	x4, x1, 6
	ldr	x3, [x24, 104]
	add	x1, x4, x1, lsl 2
	str	w0, [x19, 1232]
	add	x1, x21, x1
	mov	x2, 68
	add	x1, x1, 2912
	add	x0, x19, 2048
	blr	x3
	ldr	w0, [x21, 2760]
	cmp	w0, 1
	beq	.L367
.L303:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1240]
	add	x1, x21, 2696
	ldr	w3, [x1, 8]
	cmp	w3, 1
	beq	.L368
.L304:
	ldr	w1, [x1, 12]
	cmp	w1, 1
	beq	.L369
	cbz	w0, .L308
.L306:
	mov	w0, 1
	str	w0, [x19, 1244]
.L341:
	mov	w1, 1
	add	x23, x19, 1068
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 180]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 184]
	ldr	w24, [x21, 2708]
	cmp	w24, 1
	beq	.L370
	mov	w0, 1
	str	w0, [x23, 188]
.L310:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1260]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1264]
	add	x1, x21, 2696
	ldrb	w23, [x1, 2413]
	lsl	w23, w23, 3
	sub	w23, w23, #1
	cmp	w23, w0
	bcc	.L371
.L311:
	add	x23, x19, 1068
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 208]
	cbz	w0, .L372
.L313:
	add	x23, x19, 1068
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 232]
	cbz	w0, .L373
	stp	wzr, wzr, [x23, 236]
.L319:
	add	x23, x19, 1068
	mov	w0, 2
	strb	w0, [x23, 1]
	ldr	w0, [x21, 2776]
	cbnz	w0, .L374
	stp	wzr, wzr, [x23, 224]
.L326:
	ldr	w0, [x21, 2900]
	cmp	w0, 1
	beq	.L375
.L329:
	str	wzr, [x19, 1320]
	str	wzr, [x19, 1324]
	str	wzr, [x19, 1328]
.L332:
	ldr	w0, [x19, 1328]
	cbz	w0, .L335
.L336:
	mov	x1, x20
	add	x0, x19, 1068
	bl	AVS2_ALF_ParameterSet
	mov	w20, w0
	cbz	w0, .L376
.L335:
	add	x0, x19, 1068
	ldr	w1, [x0, 140]
	cbz	w1, .L377
	ldr	w1, [x0, 144]
	cmp	w1, 1
	beq	.L378
	mov	w1, 6
	str	w1, [x0, 132]
.L339:
	mov	w20, 1
	add	x0, x21, 2692
	strb	wzr, [x19, 1068]
	str	w20, [x19, 1204]
	bl	AVS2_SetupWqMatrix84
	ldr	w0, [x22, 12]
	orr	w0, w0, 262144
	str	w0, [x22, 12]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L301:
	add	x0, x19, 2048
	mov	x1, x20
	bl	AVS2_Head_GetRefConfigSet
	ldr	w0, [x21, 2760]
	cmp	w0, 1
	bne	.L303
.L367:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	str	w0, [x19, 1236]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1240]
	add	x1, x21, 2696
	ldr	w3, [x1, 8]
	cmp	w3, 1
	bne	.L304
	.p2align 2
.L368:
	str	w3, [x19, 1240]
	ldr	w0, [x1, 12]
	cmp	w0, 1
	bne	.L306
.L305:
	ldr	x1, .LC64
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 1240]
.L308:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1244]
	b	.L341
	.p2align 3
.L377:
	str	wzr, [x0, 132]
	b	.L339
	.p2align 3
.L299:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	cmp	w0, 63
	str	w0, [x19, 1224]
	bls	.L300
	ldr	x1, .LC62
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 63
	str	w0, [x19, 1224]
	b	.L300
	.p2align 3
.L365:
	add	x23, x19, 1068
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x23, 140]
	bne	.L294
	mov	w1, w0
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 144]
	add	x23, x19, 1068
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 148]
	ldr	w0, [x21, 2764]
	cmp	w0, 1
	bne	.L296
	.p2align 2
.L366:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 152]
	b	.L297
	.p2align 3
.L374:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 224]
	cbnz	w0, .L379
	str	wzr, [x23, 228]
	ldr	w0, [x21, 2900]
	cmp	w0, 1
	bne	.L329
.L375:
	add	x23, x19, 1320
	add	x24, x19, 1332
.L330:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23], 4
	cmp	x24, x23
	bne	.L330
	add	x0, x19, 1068
	ldr	w1, [x0, 252]
	cbnz	w1, .L336
	ldr	w0, [x0, 256]
	cbnz	w0, .L336
	b	.L332
	.p2align 3
.L373:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 16
	cmp	w1, 32
	str	w0, [x23, 236]
	bhi	.L380
.L318:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 16
	cmp	w1, 32
	str	w0, [x19, 1308]
	bls	.L319
	ldr	x1, .LC74
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 1308]
	b	.L319
	.p2align 3
.L372:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 212]
	cbnz	w0, .L381
	stp	wzr, wzr, [x23, 216]
	b	.L313
	.p2align 3
.L371:
	ldr	x1, .LC66
	mov	w2, w0
	mov	w4, w23
	mov	w3, w23
	mov	w0, 1
	bl	dprint_vfmw
	str	w23, [x19, 1264]
	b	.L311
	.p2align 3
.L369:
	cbnz	w0, .L305
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1244]
	b	.L341
	.p2align 3
.L376:
	ldr	x2, .LC75
	mov	w0, 1
	ldr	x1, .LC77
	add	x2, x2, 376
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L363:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1180]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1168]
	ldr	w1, [x19, 1164]
	orr	w0, w0, w1, lsl 7
	mov	w1, 1
	str	w0, [x19, 1164]
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x19, 1172]
	bne	.L291
	.p2align 2
.L364:
	mov	w1, 24
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1176]
	b	.L291
	.p2align 3
.L370:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 188]
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	b	.L310
	.p2align 3
.L378:
	mov	w1, 5
	str	w1, [x0, 132]
	b	.L339
	.p2align 3
.L381:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 8
	cmp	w1, 16
	str	w0, [x23, 216]
	bhi	.L382
.L315:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 8
	cmp	w1, 16
	str	w0, [x19, 1288]
	bls	.L313
	ldr	x1, .LC70
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 1288]
	b	.L313
	.p2align 3
.L380:
	ldr	x1, .LC72
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 236]
	b	.L318
	.p2align 3
.L379:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x23, 228]
	beq	.L383
	cmp	w0, 2
	bne	.L326
	mov	x2, x20
	add	x1, x19, 1098
	add	x0, x19, 1082
	bl	AVS2_WeightQuantMatrix
	b	.L326
	.p2align 3
.L382:
	ldr	x1, .LC68
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 216]
	b	.L315
	.p2align 3
.L383:
	mov	w1, w0
	mov	x0, x20
	bl	BsGet
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 244]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 248]
	ldr	w1, [x23, 244]
	cmp	w1, 1
	beq	.L384
.L323:
	cmp	w1, 2
	bne	.L326
	add	x23, x19, 1076
	add	x24, x19, 1082
	.p2align 2
.L327:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	strb	w0, [x23], 1
	cmp	x24, x23
	bne	.L327
	b	.L326
.L384:
	add	x23, x19, 1070
	add	x24, x19, 1076
	.p2align 2
.L324:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	strb	w0, [x23], 1
	cmp	x23, x24
	bne	.L324
	ldr	w1, [x19, 1312]
	b	.L323
	.size	AVS2_IntraPictureHeader, .-AVS2_IntraPictureHeader
	.align	3
.LC60:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
	.align	3
.LC66:
	.xword	.LC65
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC70:
	.xword	.LC69
	.align	3
.LC72:
	.xword	.LC71
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC75:
	.xword	.LANCHOR1
	.align	3
.LC77:
	.xword	.LC76
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_InterPictureHeader
	.type	AVS2_InterPictureHeader, %function
AVS2_InterPictureHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 56
	add	x19, x22, 16384
	bl	_mcount
	ldr	w1, [x22, 12]
	mov	x0, x22
	and	w1, w1, -262145
	str	w1, [x22, 12]
	bl	AVS2_Vfmw_EpbRemove
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1164]
	ldr	w0, [x22, 14984]
	cmp	w0, 72
	beq	.L458
.L386:
	add	x23, x19, 1068
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 116]
	cbz	w0, .L459
	add	x21, x22, 12288
	cmp	w0, 1
	ldr	w0, [x21, 2784]
	ccmp	w0, wzr, 0, eq
	beq	.L460
	str	wzr, [x23, 120]
.L390:
	str	wzr, [x19, 1192]
	cbz	w0, .L461
.L391:
	add	x23, x19, 1068
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 148]
	ldr	w0, [x21, 2764]
	cmp	w0, 1
	beq	.L462
	str	wzr, [x23, 152]
.L393:
	ldr	w0, [x21, 2760]
	cbz	w0, .L463
	str	wzr, [x19, 1224]
.L395:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1228]
	cbnz	w0, .L464
	add	x0, x19, 2048
	mov	x1, x20
	bl	AVS2_Head_GetRefConfigSet
	ldr	w0, [x21, 2760]
	cmp	w0, 1
	beq	.L465
.L398:
	mov	w1, 1
	mov	x0, x20
	add	x23, x21, 2696
	bl	BsGet
	str	w0, [x19, 1240]
	ldr	w1, [x23, 8]
	cmp	w1, 1
	ccmp	w0, 1, 4, eq
	beq	.L399
	ldr	x1, .LC84
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x19, 1240]
	ldr	w0, [x23, 12]
	cmp	w0, 1
	beq	.L403
	.p2align 2
.L400:
	mov	w0, 1
	str	w0, [x19, 1244]
.L439:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1248]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1252]
	ldr	w24, [x21, 2708]
	cmp	w24, 1
	beq	.L466
.L404:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1260]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1264]
	add	x1, x21, 2696
	ldrb	w23, [x1, 2413]
	lsl	w23, w23, 3
	sub	w23, w23, #1
	cmp	w23, w0
	bcc	.L467
.L405:
	ldr	w1, [x19, 1184]
	cmp	w1, 2
	bne	.L406
	ldr	w0, [x19, 1244]
	cmp	w0, 1
	beq	.L407
.L406:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1272]
.L407:
	mov	w1, 1
	add	x23, x19, 1068
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 128]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 208]
	cbz	w0, .L468
.L409:
	add	x23, x19, 1068
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 232]
	cbz	w0, .L469
	stp	wzr, wzr, [x23, 236]
.L415:
	add	x23, x19, 1068
	mov	w0, 2
	strb	w0, [x23, 1]
	ldr	w0, [x21, 2776]
	cbnz	w0, .L470
	str	wzr, [x23, 224]
.L422:
	ldr	w0, [x21, 2900]
	cmp	w0, 1
	beq	.L471
	str	wzr, [x19, 1320]
	str	wzr, [x19, 1324]
	str	wzr, [x19, 1328]
.L428:
	ldr	w0, [x19, 1328]
	cbnz	w0, .L432
.L431:
	add	x1, x19, 1068
	ldr	w0, [x1, 116]
	cmp	w0, 1
	beq	.L472
	cmp	w0, 2
	beq	.L440
	cmp	w0, 3
	bne	.L441
.L440:
	str	w0, [x1, 132]
	ldrb	w0, [x1, 984]
	strb	w0, [x19, 1068]
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 6
	bhi	.L473
.L438:
	add	x0, x21, 2692
	str	wzr, [x19, 1204]
	mov	w20, 1
	bl	AVS2_SetupWqMatrix84
	ldr	w0, [x22, 12]
	orr	w0, w0, 262144
	str	w0, [x22, 12]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L464:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtw	x1, w0
	ldr	x3, .LC82
	lsl	x4, x1, 6
	add	x1, x4, x1, lsl 2
	str	w0, [x19, 1232]
	add	x1, x21, x1
	mov	x2, 68
	ldr	x3, [x3, 104]
	add	x1, x1, 2912
	add	x0, x19, 2048
	blr	x3
	ldr	w0, [x21, 2760]
	cmp	w0, 1
	bne	.L398
.L465:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	str	w0, [x19, 1236]
	b	.L398
	.p2align 3
.L461:
	ldr	w0, [x19, 1184]
	cmp	w0, 2
	beq	.L391
	ldr	w0, [x19, 1188]
	cbnz	w0, .L391
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1192]
	b	.L391
	.p2align 3
.L471:
	add	x23, x19, 1320
	add	x24, x19, 1332
.L426:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23], 4
	cmp	x23, x24
	bne	.L426
	add	x0, x19, 1068
	ldr	w1, [x0, 252]
	cbz	w1, .L429
.L432:
	mov	x1, x20
	add	x0, x19, 1068
	bl	AVS2_ALF_ParameterSet
	mov	w20, w0
	cbnz	w0, .L431
	ldr	x2, .LC97
	mov	w0, 1
	ldr	x1, .LC98
	add	x2, x2, 400
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L472:
	ldr	w2, [x1, 120]
	cbnz	w2, .L434
	str	w0, [x1, 132]
	ldr	w0, [x1, 984]
	strb	w0, [x19, 1068]
.L441:
	ldrb	w0, [x19, 1068]
.L480:
	sub	w0, w0, #1
	uxtb	w0, w0
	cmp	w0, 6
	bls	.L438
.L473:
	ldr	x2, .LC97
	mov	w3, 7
	ldr	x1, .LC100
	mov	w0, 1
	add	x2, x2, 400
	mov	w20, 0
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L399:
	ldr	w1, [x23, 12]
	cmp	w1, 1
	beq	.L474
	cbnz	w0, .L400
	.p2align 2
.L401:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1244]
	b	.L439
	.p2align 3
.L463:
	mov	x0, x20
	bl	AVS2_ue_v.isra.2
	cmp	w0, 63
	str	w0, [x19, 1224]
	bls	.L395
	ldr	x1, .LC81
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 63
	str	w0, [x19, 1224]
	b	.L395
	.p2align 3
.L470:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 224]
	cbnz	w0, .L475
	str	wzr, [x23, 228]
	b	.L422
	.p2align 3
.L469:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 16
	cmp	w1, 32
	str	w0, [x23, 236]
	bhi	.L476
.L414:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 16
	cmp	w1, 32
	str	w0, [x19, 1308]
	bls	.L415
	ldr	x1, .LC96
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 1308]
	b	.L415
	.p2align 3
.L468:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 212]
	cbnz	w0, .L477
	stp	wzr, wzr, [x23, 216]
	b	.L409
	.p2align 3
.L467:
	ldr	x1, .LC88
	mov	w2, w0
	mov	w4, w23
	mov	w3, w23
	mov	w0, 1
	bl	dprint_vfmw
	str	w23, [x19, 1264]
	b	.L405
	.p2align 3
.L459:
	ldr	x1, .LC79
	mov	w2, 0
	mov	w0, 1
	mov	w20, 0
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L477:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 8
	cmp	w1, 16
	str	w0, [x23, 216]
	bhi	.L478
.L411:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	add	w1, w0, 8
	cmp	w1, 16
	str	w0, [x19, 1288]
	bls	.L409
	ldr	x1, .LC92
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 1288]
	b	.L409
	.p2align 3
.L475:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x23, 228]
	beq	.L479
	cmp	w0, 2
	bne	.L422
	mov	x2, x20
	add	x1, x19, 1098
	add	x0, x19, 1082
	bl	AVS2_WeightQuantMatrix
	b	.L422
	.p2align 3
.L476:
	ldr	x1, .LC94
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 236]
	b	.L414
	.p2align 3
.L474:
	cbz	w0, .L401
.L403:
	ldr	x1, .LC86
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x19, 1240]
	b	.L401
	.p2align 3
.L458:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1180]
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1168]
	ldr	w1, [x19, 1164]
	orr	w0, w0, w1, lsl 7
	str	w0, [x19, 1164]
	b	.L386
	.p2align 3
.L466:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 1256]
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	b	.L404
	.p2align 3
.L462:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 152]
	b	.L393
	.p2align 3
.L434:
	mov	w2, 4
	str	w2, [x1, 132]
	strb	w0, [x19, 1068]
	ldrb	w0, [x19, 1068]
	b	.L480
	.p2align 3
.L460:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 120]
	ldr	w0, [x21, 2784]
	b	.L390
	.p2align 3
.L478:
	ldr	x1, .LC90
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 216]
	b	.L411
.L479:
	mov	w1, w0
	mov	x0, x20
	bl	BsGet
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 244]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	str	w0, [x23, 248]
	ldr	w1, [x23, 244]
	cmp	w1, 1
	beq	.L481
.L419:
	cmp	w1, 2
	bne	.L422
	add	x23, x19, 1076
	add	x24, x19, 1082
	.p2align 2
.L423:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	strb	w0, [x23], 1
	cmp	x23, x24
	bne	.L423
	b	.L422
.L481:
	add	x23, x19, 1070
	add	x24, x19, 1076
	.p2align 2
.L420:
	mov	x0, x20
	bl	AVS2_se_v.isra.3
	strb	w0, [x23], 1
	cmp	x23, x24
	bne	.L420
	ldr	w1, [x19, 1312]
	b	.L419
.L429:
	ldr	w0, [x0, 256]
	cbnz	w0, .L432
	b	.L428
	.size	AVS2_InterPictureHeader, .-AVS2_InterPictureHeader
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC82:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC84:
	.xword	.LC83
	.align	3
.LC86:
	.xword	.LC85
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC94:
	.xword	.LC93
	.align	3
.LC96:
	.xword	.LC95
	.align	3
.LC97:
	.xword	.LANCHOR1
	.align	3
.LC98:
	.xword	.LC76
	.align	3
.LC100:
	.xword	.LC99
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SequenceHeader
	.type	AVS2_SequenceHeader, %function
AVS2_SequenceHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 56
	add	x22, x20, 12288
	bl	_mcount
	add	x21, x22, 2696
	ldr	x1, .LC102
	mov	w0, 7
	bl	dprint_vfmw
	ldr	w2, [x20, 12]
	mov	w1, 32
	mov	x0, x19
	and	w2, w2, -65537
	str	w2, [x20, 12]
	bl	BsGet
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	and	w1, w0, -3
	cmp	w1, 32
	str	w0, [x20, 14984]
	ccmp	w0, 18, 4, ne
	bne	.L521
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 4]
	cbz	w0, .L522
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 8]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 12]
	ldr	w1, [x21, 8]
	cmp	w1, 1
	ccmp	w0, 1, 0, eq
	beq	.L523
.L486:
	add	x21, x22, 2696
	mov	w1, 14
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 16]
	cbz	w0, .L524
	mov	w1, 14
	mov	x0, x19
	bl	BsGet
	str	w0, [x21, 24]
	cbz	w0, .L525
	ldr	w1, [x21, 16]
	add	w2, w0, 7
	and	w2, w2, -8
	str	w0, [x21, 28]
	stp	w1, w2, [x21, 20]
	add	w1, w1, 7
	mov	x0, x19
	and	w1, w1, -8
	str	w1, [x21, 16]
	mov	w1, 2
	bl	BsGet
	cmp	w0, 1
	str	w0, [x21, 32]
	mov	w23, w0
	beq	.L489
	ldr	x1, .LC114
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L522:
	ldr	x1, .LC106
	mov	w2, 0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L484:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L521:
	ldr	x1, .LC104
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L525:
	ldr	x1, .LC112
	mov	w2, 0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L524:
	ldr	x1, .LC110
	mov	w2, 0
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L489:
	mov	w1, 3
	mov	x0, x19
	bl	BsGet
	add	w0, w0, 3
	lsl	w2, w0, 1
	str	w2, [x21, 36]
	and	w1, w2, -3
	cmp	w1, 8
	bne	.L526
	ldr	w0, [x20, 14984]
	cmp	w0, 34
	beq	.L527
	strb	w1, [x21, 2413]
	mov	w2, w1
	str	wzr, [x21, 40]
.L494:
	ldr	x3, [x20, 40]
	mov	w1, 4
	mov	x0, x19
	str	w2, [x3, 972]
	bl	BsGet
	str	w0, [x22, 2740]
	cbz	w0, .L528
.L495:
	mov	w1, 4
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2744]
	cbz	w0, .L529
.L496:
	mov	w1, 18
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2748]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2752]
	mov	w1, 12
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2756]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2760]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2752]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2764]
	mov	w1, 18
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2768]
	mov	w1, 3
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 2772]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	cmp	w0, 1
	str	w0, [x22, 2776]
	beq	.L530
.L498:
	add	x23, x22, 2696
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 88]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 92]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 96]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 100]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 184]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 188]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 192]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 196]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 200]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 204]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 208]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	str	w0, [x23, 56]
	mov	w1, 6
	mov	x0, x19
	bl	BsGet
	cmp	w0, 32
	str	w0, [x23, 212]
	bhi	.L500
	mov	w21, 0
	cbz	w0, .L505
	.p2align 2
.L515:
	uxtw	x0, w21
	mov	x1, x19
	lsl	x2, x0, 6
	add	w21, w21, 1
	add	x0, x2, x0, lsl 2
	add	x0, x23, x0
	add	x0, x0, 216
	bl	AVS2_Head_GetRefConfigSet
	ldr	w0, [x23, 212]
	cmp	w0, w21
	bhi	.L515
.L505:
	ldr	w0, [x22, 2760]
	cbz	w0, .L531
	str	wzr, [x22, 5088]
.L506:
	mov	x0, x19
	mov	w1, 1
	add	x19, x22, 2696
	bl	BsGet
	str	w0, [x22, 5092]
	mov	w1, 1
	mov	x0, x19
	ldr	w3, [x19, 76]
	ldr	w2, [x19, 16]
	lsl	w1, w1, w3
	sub	w2, w2, #1
	uxth	w1, w1
	add	w2, w1, w2
	uxth	w2, w2
	asr	w2, w2, w3
	strh	w2, [x22, 5104]
	ldr	w2, [x19, 24]
	sub	w2, w2, #1
	add	w1, w1, w2
	uxth	w1, w1
	asr	w1, w1, w3
	strh	w1, [x22, 5106]
	bl	AVS2_DeriveMaxDpbNum
	ldr	w0, [x20, 11308]
	cbz	w0, .L507
	ldr	w1, [x20, 11316]
	cbz	w1, .L507
	ldr	w2, [x19, 16]
	cmp	w0, w2
	beq	.L532
.L510:
	mov	w0, 1
	str	w0, [x20, 20]
.L509:
	ldr	w1, [x20, 12]
	mov	w0, 1
	orr	w1, w1, 65536
	str	w1, [x20, 12]
	b	.L484
	.p2align 3
.L526:
	ldr	x1, .LC116
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, 0
	b	.L484
	.p2align 3
.L507:
	str	wzr, [x20, 20]
	b	.L509
	.p2align 3
.L523:
	ldr	x1, .LC108
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x21, 12]
	b	.L486
	.p2align 3
.L529:
	ldr	x1, .LC122
	mov	w0, 1
	bl	dprint_vfmw
	b	.L496
	.p2align 3
.L528:
	ldr	x1, .LC120
	mov	w0, 1
	bl	dprint_vfmw
	b	.L495
	.p2align 3
.L531:
	mov	w1, 5
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 5088]
	b	.L506
.L500:
	ldr	x1, .LC124
	mov	w2, w0
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L484
.L527:
	mov	w1, 3
	mov	x0, x19
	bl	BsGet
	add	w2, w0, 3
	ubfiz	w2, w2, 1, 7
	str	w0, [x21, 40]
	and	w0, w2, 252
	strb	w2, [x21, 2413]
	cmp	w0, 8
	ldr	w3, [x21, 36]
	bne	.L493
	cmp	w2, w3
	bcs	.L494
.L493:
	ldr	x1, .LC118
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L484
.L530:
	mov	w1, w0
	mov	x0, x19
	bl	BsGet
	cmp	w0, 1
	str	w0, [x22, 2780]
	bne	.L498
	mov	x2, x19
	add	x1, x22, 2816
	add	x0, x22, 2800
	bl	AVS2_WeightQuantMatrix
	b	.L498
.L532:
	ldr	w0, [x19, 24]
	cmp	w1, w0
	bne	.L510
	b	.L509
	.size	AVS2_SequenceHeader, .-AVS2_SequenceHeader
	.align	3
.LC102:
	.xword	.LC101
	.align	3
.LC104:
	.xword	.LC103
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC108:
	.xword	.LC107
	.align	3
.LC110:
	.xword	.LC109
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC114:
	.xword	.LC113
	.align	3
.LC116:
	.xword	.LC115
	.align	3
.LC118:
	.xword	.LC117
	.align	3
.LC120:
	.xword	.LC119
	.align	3
.LC122:
	.xword	.LC121
	.align	3
.LC124:
	.xword	.LC123
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_AllocateVHB
	.type	AVS2_AllocateVHB, %function
AVS2_AllocateVHB:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 12288
	bl	_mcount
	str	wzr, [x29, 88]
	add	x1, x20, 2696
	add	x0, x29, 72
	ldr	w6, [x1, 16]
	ldr	w3, [x1, 24]
	stp	xzr, xzr, [x0]
	ldr	w0, [x1, 8]
	cmp	w0, 1
	add	w0, w6, 15
	lsr	w2, w0, 4
	beq	.L566
	add	w3, w3, 31
	lsr	w3, w3, 5
	lsl	w3, w3, 1
.L535:
	sub	w0, w2, #2
	cmp	w0, 510
	bhi	.L536
	sub	w0, w3, #2
	cmp	w0, 510
	bhi	.L536
	ldr	x0, [x19, 40]
	ldr	w21, [x0, 772]
	ldr	w1, [x0, 28]
	cmp	w1, 25
	cbnz	w21, .L539
	beq	.L567
.L540:
	add	x0, x19, 16384
	mov	w22, 0
	ldrb	w23, [x0, 1012]
	add	w23, w23, 1
	mov	w21, w23
.L545:
	ldr	x3, .LC131
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 72
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x2, [x19, 40]
	ldr	w1, [x20, 2712]
	ldr	w0, [x20, 2720]
	ldr	w2, [x2, 28]
	stp	w1, w0, [x29, 84]
	add	w1, w1, 15
	add	w0, w0, 15
	and	w1, w1, -16
	and	w0, w0, -16
	cmp	w2, 24
	stp	w1, w0, [x29, 76]
	beq	.L551
	strb	w23, [x29, 73]
	sxtb	w21, w21
	strb	w22, [x29, 74]
.L556:
	ldr	w0, [x19, 4]
	add	x1, x29, 72
	strb	w21, [x29, 75]
	bl	FSP_ConfigInstance
	mov	w21, w0
	cbnz	w0, .L552
	ldr	x1, [x19, 40]
	add	x3, x29, 96
	ldr	w0, [x19, 4]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	str	wzr, [x3, -28]!
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L568
	cbnz	w0, .L569
	mov	w21, 1
	str	w21, [x19, 24]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L536:
	ldr	x1, .LC126
	mov	w0, 1
	mov	w21, 0
	bl	dprint_vfmw
.L560:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L566:
	add	w3, w3, 15
	lsr	w3, w3, 4
	b	.L535
	.p2align 3
.L539:
	bne	.L540
	ldr	w4, [x0, 732]
	ldr	w5, [x0, 736]
	cmp	w6, w4
	ldr	w3, [x20, 2720]
	bhi	.L548
	cmp	w3, w5
	bhi	.L548
.L549:
	ldr	w2, [x0, 760]
	mov	w21, 1
	ldr	w1, [x0, 756]
	add	w23, w1, 2
	cbnz	w2, .L570
	ldrsb	w22, [x0, 780]
	b	.L545
	.p2align 3
.L552:
	ldr	x1, .LC135
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L567:
	ldr	w4, [x0, 732]
	ldr	w5, [x0, 736]
	cmp	w6, w4
	ldr	w3, [x20, 2720]
	bhi	.L542
	cmp	w3, w5
	bhi	.L542
	ldr	w21, [x19, 24]
	cmp	w21, 1
	bne	.L549
	b	.L560
	.p2align 3
.L551:
	strb	wzr, [x29, 73]
	mov	w21, 1
	strb	w22, [x29, 74]
	b	.L556
	.p2align 3
.L569:
	ldr	x1, .LC133
	mov	w0, 0
	bl	dprint_vfmw
	b	.L560
	.p2align 3
.L548:
	ldr	x1, .LC130
	mov	w2, w6
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	b	.L560
	.p2align 3
.L570:
	add	w1, w1, w21
	mov	w21, 17
	cmp	w1, w21
	ldrsb	w22, [x0, 780]
	csel	w21, w1, w21, le
	b	.L545
	.p2align 3
.L542:
	ldr	x1, .LC128
	mov	w2, w6
	mov	w0, 0
	bl	dprint_vfmw
	b	.L560
	.p2align 3
.L568:
	add	x0, x19, 16384
	mov	w21, 3
	add	x0, x0, 2288
	bl	ResetVoQueue
	b	.L560
	.size	AVS2_AllocateVHB, .-AVS2_AllocateVHB
	.align	3
.LC126:
	.xword	.LC125
	.align	3
.LC128:
	.xword	.LC127
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC131:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC133:
	.xword	.LC132
	.align	3
.LC135:
	.xword	.LC134
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_OutputOneFrame
	.type	AVS2_OutputOneFrame, %function
AVS2_OutputOneFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w20, [x20, 56]
	ldr	w0, [x19, 4]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x21, x0
	cbz	x0, .L577
	ldr	w0, [x19, 4]
	mov	w2, 1
	mov	w1, w20
	bl	FSP_SetDisplay
	add	x3, x19, 16384
	ldr	w0, [x19, 4]
	mov	x4, x21
	add	x3, x3, 2288
	mov	x2, x19
	mov	w1, 18
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L573
	ldr	w0, [x19, 4]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	x1, .LC139
	mov	w2, w20
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
.L573:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L577:
	ldr	x1, .LC137
	mov	w2, 2277
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_OutputOneFrame, .-AVS2_OutputOneFrame
	.align	3
.LC137:
	.xword	.LC136
	.align	3
.LC139:
	.xword	.LC138
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DisplayFrameInPOI
	.type	AVS2_DisplayFrameInPOI, %function
AVS2_DisplayFrameInPOI:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	mov	w22, 0
	bl	_mcount
	add	x2, x23, 8192
	add	x0, x23, 16384
	mov	w1, 0
	add	x0, x0, 3082
	ldrsh	w3, [x2, 2778]
	.p2align 2
.L580:
	ldrsh	w2, [x0]
	cmp	w2, w3
	bgt	.L579
	ldrb	w2, [x0, -6]
	cbnz	w2, .L579
	sub	x2, x29, #4000
	add	w4, w22, 1
	add	x5, x2, x22, sxtw
	ldrb	w2, [x0, -4]
	cbz	w2, .L579
	strb	w1, [x5, 4080]
	uxtb	w22, w4
	.p2align 2
.L579:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	bne	.L580
	cbz	w22, .L578
	ldr	x20, .LC141
	mov	w24, 0
	mov	w25, 0
	mov	w19, 32767
	mov	w21, 1
	.p2align 2
.L582:
	cbz	w22, .L585
	mov	x1, 0
	mov	w5, 32767
	add	x4, x29, 80
	.p2align 2
.L584:
	ldrb	w2, [x4, x1]
	add	x1, x1, 1
	lsl	x0, x2, 3
	mov	x3, x2
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x0, x0, x2
	add	x0, x23, x0, lsl 3
	add	x0, x0, 16384
	ldrb	w2, [x0, 3076]
	cbnz	w2, .L583
	ldrsh	w0, [x0, 3074]
	cmp	w0, w5
	bgt	.L583
	mov	w5, w0
	mov	w25, w3
.L583:
	cmp	w22, w1
	bgt	.L584
	cmp	w5, w19
	beq	.L585
	sxtw	x2, w25
	mov	x0, x23
	lsl	x1, x2, 3
	sub	x1, x1, x2
	lsl	x1, x1, 1
	sub	x1, x1, x2
	lsl	x1, x1, 3
	add	x26, x23, x1
	add	x1, x1, 16384
	add	x26, x26, 16384
	add	x1, x1, 3072
	add	x1, x23, x1
	strb	w21, [x26, 3076]
	bl	AVS2_OutputOneFrame
	ldrsh	w2, [x26, 3074]
	mov	x1, x20
	mov	w0, 13
	bl	dprint_vfmw
.L585:
	add	w24, w24, 1
	uxtb	w24, w24
	cmp	w22, w24
	bne	.L582
.L578:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	AVS2_DisplayFrameInPOI, .-AVS2_DisplayFrameInPOI
	.align	3
.LC141:
	.xword	.LC140
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_UpdateSceneBuf
	.type	AVS2_UpdateSceneBuf, %function
AVS2_UpdateSceneBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 13892]
	sub	w0, w0, #5
	cmp	w0, 1
	bhi	.L596
	mov	x0, x19
	bl	AVS2_UpdateSceneBuf.part.7
.L596:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_UpdateSceneBuf, .-AVS2_UpdateSceneBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_UpdateRefBuf
	.type	AVS2_UpdateRefBuf, %function
AVS2_UpdateRefBuf:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x23, x0
	mov	x0, x30
	add	x25, x23, 12288
	add	x25, x25, 2452
	bl	_mcount
	ldr	x1, .LC143
	mov	w0, 13
	ldr	w2, [x25, 36]
	bl	dprint_vfmw
	ldr	w0, [x25, 36]
	cbz	w0, .L598
	ldr	x22, .LC145
	mov	w24, 0
	add	x21, x23, 8192
	add	x20, x23, 16384
	.p2align 2
.L604:
	add	x4, x25, x24, sxtw 2
	ldrh	w3, [x21, 2778]
	mov	x1, x22
	mov	w2, w24
	mov	w0, 13
	ldr	w19, [x4, 40]
	sub	w19, w3, w19
	sxth	w19, w19
	mov	w3, w19
	bl	dprint_vfmw
	add	x0, x20, 3078
	mov	w1, 0
	b	.L603
	.p2align 3
.L600:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	beq	.L602
.L603:
	ldrsh	w2, [x0, -6]
	cmp	w2, w19
	bne	.L600
	ldrb	w2, [x0]
	and	w3, w2, 2
	cbz	w2, .L600
	ldrb	w2, [x0, 1]
	uxtb	w3, w3
	sub	w2, w2, #5
	uxtb	w2, w2
	cmp	w2, 1
	bhi	.L601
	strb	w3, [x0]
	cbnz	w3, .L600
.L601:
	sxtw	x1, w1
	mov	w2, 0
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	add	x0, x23, x0, lsl 3
	add	x0, x0, 16384
	strb	wzr, [x0, 3077]
	ldr	w1, [x0, 3128]
	ldr	w0, [x23, 4]
	bl	FSP_SetRef
	.p2align 2
.L602:
	ldr	w0, [x25, 36]
	add	w24, w24, 1
	cmp	w0, w24
	bhi	.L604
.L598:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	AVS2_UpdateRefBuf, .-AVS2_UpdateRefBuf
	.align	3
.LC143:
	.xword	.LC142
	.align	3
.LC145:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_RefreshBuf
	.type	AVS2_RefreshBuf, %function
AVS2_RefreshBuf:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 16384
	mov	w19, 0
	bl	_mcount
	add	x20, x20, 3078
	b	.L615
	.p2align 3
.L613:
	cmp	w19, 16
	add	x20, x20, 104
	beq	.L617
.L615:
	sxtw	x1, w19
	ldrb	w2, [x20]
	lsl	x0, x1, 3
	add	w19, w19, 1
	sub	x0, x0, x1
	lsl	x0, x0, 1
	cbz	w2, .L613
	sub	x0, x0, x1
	add	x0, x21, x0, lsl 3
	add	x0, x0, 16384
	ldrh	w0, [x0, 3076]
	cmp	w0, 1
	bne	.L613
	and	w2, w2, 2
	uxtb	w2, w2
	strb	w2, [x20]
	cbnz	w2, .L613
	ldr	w1, [x20, 50]
	add	x20, x20, 104
	ldr	w0, [x21, 4]
	bl	FSP_SetRef
	cmp	w19, 16
	bne	.L615
.L617:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	AVS2_RefreshBuf, .-AVS2_RefreshBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetPicInfo
	.type	AVS2_SetPicInfo, %function
AVS2_SetPicInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x5, x19, 8192
	ldr	w0, [x5, 5716]
	ldr	w3, [x5, 5724]
	add	x6, x5, 3096
	ldr	w2, [x5, 5492]
	sxth	w7, w0
	add	w0, w3, w0
	sub	w0, w0, w2
	strh	w7, [x5, 2778]
	strh	w0, [x5, 2780]
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L620
	ldrsh	w0, [x5, 2776]
	cmp	w0, w7
	ble	.L620
	add	x0, x19, 16384
	add	x4, x19, 20480
	ldr	w6, [x6, 16]
	add	x0, x0, 3074
	add	x4, x4, 642
	.p2align 2
.L622:
	ldrh	w1, [x0]
	ldrh	w3, [x0, -2]
	sub	w1, w1, #256
	ldrh	w2, [x0, 8]
	sub	w3, w3, #256
	strh	w3, [x0, -2]
	sxth	w1, w1
	sub	w2, w2, #256
	strh	w1, [x0]
	lsl	w1, w1, 1
	strh	w2, [x0, 8]
	strh	w1, [x0, 6]
	cbnz	w6, .L621
	ldr	w2, [x5, 5756]
	add	w1, w1, 1
	cbnz	w2, .L621
	strh	w1, [x0, 6]
.L621:
	add	x0, x0, 104
	cmp	x0, x4
	bne	.L622
.L620:
	strh	w7, [x5, 2776]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_SetPicInfo, .-AVS2_SetPicInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_VarifyDecMode
	.type	AVS2_VarifyDecMode, %function
AVS2_VarifyDecMode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, [x20, 40]
	ldr	w19, [x0, 8]
	cmp	w19, 2
	beq	.L627
	cmp	w19, 3
	beq	.L628
	cmp	w19, 1
	mov	w21, 1
	beq	.L643
.L626:
	str	w19, [x20, 32]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L643:
	ldr	w0, [x20, 13892]
	add	x22, x20, 12288
	mov	w21, w19
	add	x22, x22, 1472
	cmp	w0, 2
	beq	.L644
.L630:
	ldr	w0, [x20, 32]
	cmp	w0, 1
	beq	.L626
	mov	x0, x20
	bl	AVS2_ClearDpb
	str	w19, [x20, 32]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L628:
	str	w19, [x20, 32]
	mov	w21, 0
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L627:
	ldr	w0, [x20, 13896]
	str	w19, [x20, 32]
	cmp	w0, wzr
	cset	w21, ne
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L644:
	ldr	w0, [x22, 980]
	cbnz	w0, .L630
	mov	x0, x20
	bl	AVS2_DisplayFrameInPOI
	ldr	w0, [x22, 1016]
	cbnz	w0, .L645
.L631:
	mov	x0, x20
	mov	w21, 0
	bl	AVS2_RefreshBuf
	b	.L630
.L645:
	mov	x0, x20
	bl	AVS2_UpdateRefBuf
	b	.L631
	.size	AVS2_VarifyDecMode, .-AVS2_VarifyDecMode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_VarifyFrame
	.type	AVS2_VarifyFrame, %function
AVS2_VarifyFrame:
	sub	sp, sp, #80
	stp	x29, x30, [sp, 48]
	add	x29, sp, 48
	stp	x19, x20, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x20, 16384
	mov	w2, 0
	add	x0, x0, 3078
	b	.L651
	.p2align 3
.L647:
	add	w2, w2, 1
	add	x0, x0, 104
	cmp	w2, 16
	beq	.L660
.L651:
	ldrb	w3, [x0]
	cbz	w3, .L647
	ldr	w1, [x0, 50]
	ldr	w4, [x19, 56]
	cmp	w4, w1
	beq	.L648
	ldr	w5, [x0, 54]
	ldr	w6, [x19, 100]
	cmp	w6, w5
	beq	.L661
	ldr	w7, [x0, 74]
	ldr	w6, [x19, 80]
	cmp	w6, w7
	bne	.L647
	ldrb	w8, [x0, -1]
	cmp	w8, 1
	beq	.L654
	tbz	x3, 1, .L647
.L654:
	mov	w9, w6
	sxtw	x2, w2
.L650:
	lsl	x0, x2, 3
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x2, x0, x2
	mov	w0, 1
	add	x2, x20, x2, lsl 3
	add	x2, x2, 16384
	ldrb	w7, [x2, 3079]
	str	w9, [sp, 40]
	str	w1, [sp, 24]
	str	w5, [sp, 32]
	ldrsh	w1, [x2, 3072]
	str	w1, [sp, 16]
	str	w8, [sp, 8]
	str	w3, [sp]
	ldr	x1, .LC147
	ldrsh	w3, [x19]
	ldrb	w2, [x19, 7]
	ldr	w5, [x19, 60]
	bl	dprint_vfmw
	add	sp, x29, 0
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L660:
	add	sp, x29, 0
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L648:
	sxtw	x2, w2
	ldr	w6, [x19, 80]
	lsl	x0, x2, 3
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x0, x0, x2
	add	x0, x20, x0, lsl 3
	add	x0, x0, 16384
	ldrb	w8, [x0, 3077]
	ldr	w5, [x0, 3132]
	ldr	w9, [x0, 3152]
	b	.L650
.L661:
	sxtw	x2, w2
	ldr	w6, [x19, 80]
	lsl	x0, x2, 3
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x0, x0, x2
	add	x0, x20, x0, lsl 3
	add	x0, x0, 16384
	ldrb	w8, [x0, 3077]
	ldr	w9, [x0, 3152]
	b	.L650
	.size	AVS2_VarifyFrame, .-AVS2_VarifyFrame
	.align	3
.LC147:
	.xword	.LC146
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ReleaseFrameBuf
	.type	AVS2_ReleaseFrameBuf, %function
AVS2_ReleaseFrameBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 8192
	bl	_mcount
	add	x19, x19, 2776
	ldr	x0, [x20, 11144]
	cbz	x0, .L663
	ldr	w1, [x0, 56]
	mov	w2, 0
	ldr	w0, [x20, 4]
	bl	FSP_ClearLogicFs
	ldr	x0, [x19, 176]
	strb	wzr, [x0, 6]
.L663:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_ReleaseFrameBuf, .-AVS2_ReleaseFrameBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupFrameBuf
	.type	AVS2_SetupFrameBuf, %function
AVS2_SetupFrameBuf:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 8192
	bl	_mcount
	add	x3, x21, 16384
	ldr	w0, [x22, 5700]
	cmp	w0, 6
	beq	.L668
.L672:
	ldrb	w0, [x3, 3078]
	cbz	w0, .L708
	add	x0, x3, 3182
	mov	w19, 1
.L677:
	ldrb	w1, [x0]
	add	x0, x0, 104
	cbz	w1, .L669
	add	w19, w19, 1
	cmp	w19, 16
	bne	.L677
.L676:
	ldr	x2, .LC148
	mov	w0, 1
	ldr	x1, .LC150
	mov	w20, 0
	add	x2, x2, 424
	bl	dprint_vfmw
.L678:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L708:
	mov	w19, 0
.L669:
	sxtw	x19, w19
	mov	w1, 1
	lsl	x0, x19, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x19, x0, x19
	lsl	x19, x19, 3
	add	x19, x19, 16384
	add	x19, x19, 3072
	add	x19, x21, x19
	str	x19, [x22, 2952]
	ldr	w0, [x21, 4]
	bl	FSP_NewLogicFs
	mov	w24, w0
	cbz	x19, .L676
.L673:
	ldr	w0, [x21, 4]
	mov	w1, w24
	bl	FSP_GetLogicFs
	cmp	w24, wzr
	ccmp	x0, xzr, 4, ge
	beq	.L679
	add	x23, x21, 12288
	ldr	w5, [x23, 1428]
	strb	w5, [x0, 488]
	add	x2, x0, 496
	add	x1, x23, 2644
	add	x4, x23, 2656
	ldr	w5, [x23, 1436]
	strb	w5, [x0, 489]
	ldr	w5, [x23, 1444]
	strb	w5, [x0, 490]
	ldr	w3, [x23, 1440]
	str	w3, [x0, 492]
	ldr	w3, [x21, 14924]
	strb	w3, [x0, 464]
.L680:
	ldr	w3, [x1]
	add	x1, x1, 4
	strh	w3, [x2]
	add	x2, x2, 2
	cmp	x1, x4
	ldr	w3, [x1, 8]
	strh	w3, [x2, 4]
	bne	.L680
	ldr	w1, [x23, 2668]
	strh	w1, [x0, 508]
	mov	w1, w24
	ldr	w3, [x23, 2672]
	strh	w3, [x0, 510]
	ldr	w3, [x23, 2676]
	str	w3, [x0, 512]
	ldr	w3, [x23, 2680]
	str	w3, [x0, 516]
	ldr	w3, [x23, 2640]
	strb	w3, [x0, 465]
	ldr	w3, [x23, 2684]
	str	w3, [x0, 520]
	ldr	w2, [x23, 2688]
	str	w2, [x0, 524]
	ldr	w0, [x21, 4]
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L709
	str	w24, [x19, 56]
	mov	w1, w24
	ldr	w0, [x0, 112]
	str	w0, [x19, 88]
	ldr	w0, [x20, 116]
	str	w0, [x19, 92]
	ldr	w0, [x20, 140]
	str	w0, [x19, 96]
	ldp	w2, w0, [x20, 36]
	sub	w0, w0, w2
	str	w0, [x19, 84]
	ldr	w0, [x20, 36]
	str	w0, [x19, 60]
	ldr	w0, [x20, 40]
	str	w0, [x19, 64]
	ldr	w0, [x21, 4]
	bl	FSP_GetPmvAddr
	str	w0, [x19, 80]
	mov	x2, -1
	ldr	w1, [x20, 212]
	str	w1, [x19, 100]
	ldr	w1, [x20, 144]
	str	w1, [x19, 68]
	ldr	w3, [x20, 36]
	ldr	w1, [x20, 44]
	sub	w1, w1, w3
	str	w1, [x19, 72]
	ldp	w3, w1, [x20, 44]
	sub	w1, w1, w3
	str	w1, [x19, 76]
	ldr	w1, [x21, 28]
	str	w1, [x20, 176]
	ldrb	w1, [x23, 1417]
	str	w1, [x20, 168]
	ldrb	w1, [x23, 1417]
	str	w1, [x20, 172]
	ldr	x1, [x21, 40]
	ldr	x1, [x1, 64]
	str	x1, [x20, 584]
	ldr	x1, [x21, 40]
	ldr	x1, [x1, 80]
	str	x1, [x20, 592]
	ldr	x1, [x21, 40]
	ldr	x1, [x1, 96]
	str	x1, [x20, 600]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 112]
	str	w1, [x20]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 116]
	str	w1, [x20, 4]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 120]
	str	w1, [x20, 8]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 136]
	str	w1, [x20, 12]
	ldr	w1, [x22, 5744]
	cmp	w1, wzr
	cset	w1, eq
	str	w1, [x20, 52]
	ldr	x1, [x21, 40]
	str	x2, [x1, 64]
	ldrsh	w1, [x22, 2778]
	strh	w1, [x19]
	ldrsh	w1, [x22, 2780]
	strh	w1, [x19, 2]
	lsl	w1, w1, 1
	ldr	w2, [x22, 5700]
	strb	w2, [x19, 7]
	ldr	w2, [x22, 6548]
	strb	w2, [x19, 5]
	strb	wzr, [x19, 4]
	ldrh	w0, [x22, 2778]
	ldr	w2, [x22, 5724]
	strh	w1, [x19, 8]
	add	w0, w2, w0
	strh	w0, [x19, 10]
	ldr	w0, [x22, 3112]
	cbz	w0, .L710
.L705:
	ldr	w0, [x22, 5756]
.L684:
	strb	w0, [x19, 12]
	mov	x1, x19
	mov	x0, x21
	ldr	w2, [x22, 5744]
	strb	w2, [x19, 13]
	ldr	w2, [x22, 5748]
	strb	w2, [x19, 14]
	strb	wzr, [x19, 6]
	bl	AVS2_VarifyFrame
	mov	w20, w0
	cbz	w0, .L711
	ldrb	w0, [x19, 7]
	cmp	w0, 4
	bhi	.L686
	ldrb	w0, [x19, 5]
	mov	w1, 1
	strb	w1, [x19, 6]
	mov	w20, 1
	cbz	w0, .L678
.L687:
	ldr	w1, [x19, 56]
	mov	w2, 1
	ldr	w0, [x21, 4]
	mov	w20, w2
	bl	FSP_SetRef
.L713:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L710:
	ldr	w0, [x22, 5756]
	cbnz	w0, .L684
	add	w1, w1, 1
	strh	w1, [x19, 8]
	b	.L705
	.p2align 3
.L668:
	mov	w1, 0
	add	x0, x3, 3078
	b	.L674
	.p2align 3
.L671:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	beq	.L672
.L674:
	ldrb	w2, [x0]
	cbz	w2, .L671
	ldrb	w2, [x0, 1]
	cmp	w2, 6
	bne	.L671
	ldrsh	w5, [x0, -6]
	ldrsh	w4, [x22, 2778]
	cmp	w5, w4
	bne	.L671
	sxtw	x1, w1
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x1, x0, x1
	lsl	x0, x1, 3
	add	x19, x0, 16384
	add	x0, x21, x0
	add	x19, x19, 3072
	add	x0, x0, 16384
	add	x19, x21, x19
	str	x19, [x22, 2952]
	ldr	w24, [x0, 3128]
	cbnz	x19, .L673
	b	.L672
	.p2align 3
.L686:
	cmp	w0, 6
	beq	.L712
	mov	w0, 3
	strb	w0, [x19, 6]
	ldr	w1, [x19, 56]
	mov	w2, 1
	ldr	w0, [x21, 4]
	mov	w20, w2
	bl	FSP_SetRef
	b	.L713
	.p2align 3
.L712:
	mov	w0, 2
	strb	w0, [x19, 6]
	b	.L687
	.p2align 3
.L679:
	ldr	x2, .LC148
	mov	w0, 1
	ldr	x1, .LC152
	mov	w20, 0
	add	x2, x2, 424
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L711:
	ldrsh	w2, [x19]
	mov	w0, 1
	ldr	x1, .LC156
	bl	dprint_vfmw
	mov	x0, x21
	bl	AVS2_ReleaseFrameBuf
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L709:
	ldr	x2, .LC148
	mov	w0, 1
	ldr	x1, .LC154
	mov	w20, 0
	add	x2, x2, 424
	bl	dprint_vfmw
	b	.L678
	.size	AVS2_SetupFrameBuf, .-AVS2_SetupFrameBuf
	.align	3
.LC148:
	.xword	.LANCHOR1
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC152:
	.xword	.LC151
	.align	3
.LC154:
	.xword	.LC153
	.align	3
.LC156:
	.xword	.LC155
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupRefFrame
	.type	AVS2_SetupRefFrame, %function
AVS2_SetupRefFrame:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	add	x24, x19, 8192
	bl	_mcount
	add	x0, x24, 2960
	add	x1, x24, 3080
	.p2align 2
.L715:
	str	xzr, [x0], 8
	cmp	x0, x1
	bne	.L715
	add	x26, x19, 12288
	ldr	w0, [x26, 1604]
	cmp	w0, 4
	beq	.L752
	add	x23, x26, 2452
	ldr	w3, [x23, 4]
	sub	w1, w3, #1
	cmp	w1, 6
	bhi	.L720
	cbz	w3, .L721
	ldr	x20, .LC162
	mov	w21, 0
	mov	w22, 0
	add	x25, x19, 16384
	.p2align 2
.L726:
	add	x0, x23, x22, sxtw 2
	ldrsh	w2, [x24, 2778]
	ldr	w3, [x0, 8]
	sub	w3, w2, w3
	sxth	w3, w3
	cmp	w2, w3
	beq	.L722
	add	x0, x25, 3078
	mov	w1, 0
	b	.L725
	.p2align 3
.L723:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	beq	.L724
.L725:
	ldrb	w4, [x0]
	tbz	x4, 0, .L723
	ldrsh	w4, [x0, -6]
	cmp	w4, w3
	bne	.L723
	ldrb	w4, [x0, -1]
	cmp	w4, 1
	bne	.L723
	ldrb	w4, [x0, 1]
	cmp	w4, 6
	beq	.L723
	cmp	w1, 15
	sxtw	x1, w1
	lsl	x0, x1, 3
	sub	x0, x0, x1
	lsl	x0, x0, 1
	sub	x0, x0, x1
	add	x1, x24, x21, uxtw 3
	lsl	x0, x0, 3
	add	w21, w21, 1
	add	x0, x0, 16384
	add	x0, x0, 3072
	add	x0, x19, x0
	str	x0, [x1, 2960]
	bgt	.L724
	.p2align 2
.L722:
	ldr	w3, [x23, 4]
	add	w22, w22, 1
	cmp	w3, w22
	bhi	.L726
.L754:
	cmp	w3, w21
	bhi	.L727
	ldr	w0, [x26, 1604]
.L721:
	and	w0, w0, -3
	cmp	w0, 1
	bne	.L729
	ldr	w0, [x26, 1596]
	cmp	w0, 1
	beq	.L753
.L729:
	mov	w0, 1
.L718:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L724:
	mov	x1, x20
	mov	w0, 1
	add	w22, w22, 1
	bl	dprint_vfmw
	ldr	w3, [x23, 4]
	cmp	w3, w22
	bhi	.L726
	b	.L754
.L752:
	add	x0, x19, 16384
	mov	w1, 0
	add	x0, x0, 3078
	.p2align 2
.L719:
	ldrb	w2, [x0]
	tbz	x2, 1, .L717
	ldrb	w2, [x0, 1]
	sub	w2, w2, #5
	uxtb	w2, w2
	cmp	w2, 1
	bls	.L755
.L717:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	bne	.L719
	ldr	x1, .LC160
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L727:
	ldr	x1, .LC164
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L753:
	sub	w0, w3, #1
	add	x1, x19, 16384
	add	x2, x19, 20480
	add	x1, x1, 3072
	add	x0, x24, x0, lsl 3
	add	x2, x2, 640
	add	x0, x0, 2952
	b	.L731
	.p2align 3
.L730:
	add	x1, x1, 104
	cmp	x2, x1
	beq	.L729
.L731:
	ldrb	w3, [x1, 6]
	tbz	x3, 1, .L730
	ldrb	w3, [x1, 7]
	sub	w3, w3, #5
	uxtb	w3, w3
	cmp	w3, 1
	bhi	.L730
	str	x1, [x0, 8]
	b	.L730
.L720:
	ldr	x2, .LC165
	mov	w4, 7
	ldr	x1, .LC167
	mov	w0, 1
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L755:
	sxtw	x1, w1
	mov	w0, 1
	lsl	x2, x1, 3
	sub	x2, x2, x1
	lsl	x2, x2, 1
	sub	x1, x2, x1
	lsl	x1, x1, 3
	add	x1, x1, 16384
	add	x1, x1, 3072
	add	x19, x19, x1
	str	x19, [x24, 2960]
	b	.L718
	.size	AVS2_SetupRefFrame, .-AVS2_SetupRefFrame
	.align	3
.LC160:
	.xword	.LC159
	.align	3
.LC162:
	.xword	.LC161
	.align	3
.LC164:
	.xword	.LC163
	.align	3
.LC165:
	.xword	.LANCHOR1
	.align	3
.LC167:
	.xword	.LC166
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetupHalConfig
	.type	AVS2_SetupHalConfig, %function
AVS2_SetupHalConfig:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 608
	add	x20, x21, 8192
	bl	_mcount
	ldr	x1, [x21, 40]
	add	x0, x20, 3096
	ldr	x22, [x20, 2960]
	ldr	w3, [x1, 640]
	strb	w3, [x19, 2]
	ldr	w3, [x1, 672]
	strb	w3, [x19, 4]
	ldr	w1, [x1, 692]
	strb	w1, [x19, 1]
	ldr	x2, [x20, 2952]
	ldr	w1, [x2, 60]
	str	w1, [x19, 92]
	ldr	w1, [x2, 88]
	str	w1, [x19, 260]
	ldr	w1, [x2, 92]
	str	w1, [x19, 264]
	ldr	w1, [x2, 84]
	str	w1, [x19, 268]
	ldr	w1, [x2, 96]
	str	w1, [x19, 272]
	ldr	w1, [x2, 100]
	str	w1, [x19, 96]
	ldr	w1, [x2, 68]
	str	w1, [x19, 276]
	ldr	w1, [x2, 72]
	str	w1, [x19, 280]
	ldr	w1, [x2, 76]
	str	w1, [x19, 284]
	ldr	w1, [x20, 3116]
	str	w1, [x19, 100]
	ldr	w1, [x20, 3124]
	str	w1, [x19, 104]
	ldrh	w1, [x20, 5508]
	str	w1, [x19, 108]
	ldrh	w1, [x20, 5510]
	str	w1, [x19, 112]
	ldr	w1, [x20, 5756]
	str	w1, [x19, 120]
	ldrb	w3, [x0, 2417]
	strb	w3, [x21, 608]
	ldr	w3, [x20, 5764]
	str	w3, [x19, 124]
	ldr	w3, [x20, 5760]
	str	w3, [x19, 128]
	ldr	w3, [x20, 5700]
	str	w3, [x19, 132]
	ldr	w0, [x20, 3112]
	cmp	w0, 1
	beq	.L777
	str	wzr, [x19, 136]
.L759:
	ldr	w1, [x20, 5496]
	add	x0, x20, 3096
	str	w1, [x19, 140]
	ldr	w1, [x20, 3288]
	str	w1, [x19, 144]
	ldr	w1, [x20, 3132]
	str	w1, [x19, 148]
	ldr	w1, [x20, 3292]
	str	w1, [x19, 152]
	ldr	w1, [x20, 3192]
	str	w1, [x19, 156]
	ldr	w1, [x20, 3200]
	str	w1, [x19, 160]
	ldr	w1, [x20, 3196]
	str	w1, [x19, 164]
	ldrb	w1, [x0, 2472]
	str	w1, [x19, 168]
	ldr	w1, [x20, 3284]
	str	w1, [x19, 172]
	ldr	w1, [x20, 5824]
	ldr	w4, [x20, 5828]
	ldr	w3, [x20, 5820]
	lsl	w1, w1, 1
	orr	w1, w1, w4, lsl 2
	orr	w1, w1, w3
	str	w1, [x19, 176]
	ldr	w1, [x20, 3300]
	str	w1, [x19, 180]
	ldr	w1, [x20, 3304]
	str	w1, [x19, 184]
	ldr	w1, [x20, 3176]
	str	w1, [x19, 116]
	ldr	w1, [x20, 3296]
	str	w1, [x19, 188]
	ldr	w0, [x20, 3180]
	str	w0, [x19, 192]
	ldr	w0, [x20, 5792]
	str	w0, [x19, 208]
	ldr	w0, [x20, 5808]
	str	w0, [x19, 196]
	ldr	w0, [x20, 5804]
	str	w0, [x19, 200]
	ldr	w0, [x20, 5800]
	str	w0, [x19, 204]
	ldr	w0, [x20, 5788]
	str	w0, [x19, 212]
	ldr	w0, [x20, 5784]
	str	w0, [x19, 216]
	ldr	w0, [x20, 5780]
	str	w0, [x19, 220]
	ldr	w0, [x20, 5776]
	str	w0, [x19, 224]
	ldrb	w0, [x2, 12]
	str	w0, [x19, 228]
	ldrb	w0, [x2, 13]
	str	w0, [x19, 232]
	ldrb	w0, [x2, 14]
	str	w0, [x19, 236]
	ldr	w0, [x20, 5704]
	cbnz	w0, .L760
	add	x4, x20, 2968
	mov	x0, x21
	mov	x1, x22
	mov	w3, 7
	b	.L763
	.p2align 3
.L778:
	ldr	x1, [x4], 8
.L763:
	subs	w3, w3, #1
	cbz	x1, .L761
	ldrb	w5, [x1, 12]
	str	w5, [x0, 924]
	ldrb	w5, [x1, 13]
	str	w5, [x0, 952]
	ldrb	w5, [x1, 14]
	str	w5, [x0, 980]
	ldr	w1, [x1, 60]
	str	w1, [x0, 1008]
.L761:
	add	x0, x0, 4
	bne	.L778
	ldr	w0, [x2, 80]
	str	w0, [x19, 240]
	cbz	x22, .L764
.L780:
	ldr	w0, [x22, 80]
	str	w0, [x19, 244]
.L765:
	ldr	x23, .LC168
	add	x24, x20, 3096
	mov	x2, 576
	add	x1, x24, 2804
	add	x0, x21, 1100
	ldr	x3, [x23, 104]
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 72
	add	x1, x24, 3380
	add	x0, x21, 1676
	blr	x3
	ldr	w0, [x20, 5704]
	cbz	w0, .L779
	ldrb	w0, [x24, 2473]
	str	w0, [x19, 248]
	ldr	w0, [x24, 212]
	str	w0, [x19, 252]
	ldr	w0, [x20, 5692]
	str	w0, [x19, 256]
.L767:
	ldr	x3, [x23, 96]
	mov	x2, 28
	mov	w1, 0
	add	x0, x21, 896
	blr	x3
.L768:
	add	x20, x20, 3096
	ldr	x3, [x23, 104]
	add	x1, x20, 2486
	mov	x2, 16
	add	x0, x21, 613
	blr	x3
	ldr	x3, [x23, 104]
	add	x1, x20, 2502
	mov	x2, 64
	add	x0, x21, 629
	blr	x3
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L760:
	ldrb	w0, [x2, 12]
	str	w0, [x19, 316]
	ldrb	w0, [x2, 13]
	str	w0, [x19, 344]
	ldrb	w0, [x2, 14]
	str	w0, [x19, 372]
	ldr	w0, [x2, 60]
	str	w0, [x19, 400]
	ldr	w0, [x2, 80]
	str	w0, [x19, 240]
	cbnz	x22, .L780
.L764:
	str	wzr, [x19, 244]
	b	.L765
	.p2align 3
.L779:
	ldr	x3, [x23, 104]
	mov	x2, 14
	add	x1, x20, 2788
	add	x0, x21, 1036
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 14
	add	x1, x20, 2816
	add	x0, x21, 1052
	blr	x3
	ldr	x3, [x23, 104]
	mov	x2, 14
	add	x1, x20, 2802
	add	x0, x21, 1068
	blr	x3
	ldr	x3, [x23, 104]
	add	x1, x20, 2830
	mov	x2, 14
	add	x0, x21, 1084
	blr	x3
	strh	wzr, [x19, 442]
	strh	wzr, [x19, 458]
	strh	wzr, [x19, 474]
	strh	wzr, [x19, 490]
	ldrb	w1, [x24, 2473]
	ldr	w0, [x20, 5704]
	str	w1, [x19, 248]
	ldr	w1, [x24, 212]
	str	w1, [x19, 252]
	ldr	w1, [x20, 5692]
	str	w1, [x19, 256]
	cbnz	w0, .L767
	ldrb	w0, [x22, 46]
	str	w0, [x19, 288]
	ldrb	w0, [x22, 47]
	str	w0, [x19, 292]
	ldrb	w0, [x22, 48]
	str	w0, [x19, 296]
	ldrb	w0, [x22, 49]
	str	w0, [x19, 300]
	ldrb	w0, [x22, 50]
	str	w0, [x19, 304]
	ldrb	w0, [x22, 51]
	str	w0, [x19, 308]
	ldrb	w0, [x22, 52]
	str	w0, [x19, 312]
	b	.L768
	.p2align 3
.L777:
	mov	w0, 2
	cmp	w1, 1
	csel	w1, w1, w0, eq
	str	w1, [x19, 136]
	b	.L759
	.size	AVS2_SetupHalConfig, .-AVS2_SetupHalConfig
	.align	3
.LC168:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_CalDistance
	.type	AVS2_CalDistance, %function
AVS2_CalDistance:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x5, x19, 8192
	add	x1, x5, 2776
	ldr	x0, [x1, 184]
	cbz	x0, .L807
	add	x7, x19, 12288
	ldrb	w3, [x7, 1472]
	sub	w0, w3, #1
	uxtb	w0, w0
	cmp	w0, 6
	bhi	.L783
	ldr	x3, [x1, 176]
	mov	w2, 1
	mov	w1, 16384
	add	x6, x3, 18
	add	x8, x3, 32
	mov	x0, x6
.L786:
	strh	w2, [x0]
	add	x0, x0, 2
	strh	w1, [x0, 12]
	cmp	x0, x8
	bne	.L786
	ldrb	w2, [x7, 1472]
	add	x0, x7, 1472
	cbz	w2, .L787
	ldrsh	w10, [x3, 2]
	mov	w4, 0
	add	x9, x5, 2776
	mov	w12, 1
	mov	w11, 16384
	b	.L792
	.p2align 3
.L809:
	ldrsh	w0, [x3, 8]
	add	x13, x3, x2, lsl 1
	ldrsh	w1, [x1, 8]
	sub	w1, w0, w1
	add	w1, w1, 512
	asr	w0, w1, 31
	lsr	w0, w0, 23
	add	w1, w1, w0
	and	w1, w1, 511
	sub	w0, w1, w0
	mov	w1, 16384
	sxth	w0, w0
	strh	w0, [x14, 18]
	cbz	w0, .L790
.L810:
	sdiv	w0, w11, w0
	add	x2, x2, 16
	add	w4, w4, 1
	sxth	w1, w0
	strh	w1, [x3, x2, lsl 1]
	ldrb	w2, [x7, 1472]
	cmp	w2, w4
	bls	.L808
.L792:
	uxtw	x2, w4
	add	x0, x3, x2
	add	x1, x9, x2, lsl 3
	add	x14, x3, x2, lsl 1
	ldr	x1, [x1, 184]
	ldrb	w13, [x1, 12]
	strb	w13, [x0, 46]
	ldrsh	w0, [x1, 2]
	cmp	w0, w10
	blt	.L809
	ldrsh	w0, [x1, 8]
	add	x13, x3, x2, lsl 1
	ldrsh	w1, [x3, 8]
	sub	w1, w0, w1
	add	w1, w1, 512
	asr	w0, w1, 31
	lsr	w0, w0, 23
	add	w1, w1, w0
	and	w1, w1, 511
	sub	w0, w1, w0
	mov	w1, 16384
	sxth	w0, w0
	strh	w0, [x14, 18]
	cbnz	w0, .L810
.L790:
	add	x2, x2, 16
	strh	w12, [x13, 18]
	add	w4, w4, 1
	strh	w1, [x3, x2, lsl 1]
	ldrb	w2, [x7, 1472]
	cmp	w2, w4
	bhi	.L792
.L808:
	ldr	w0, [x7, 1596]
	ldr	x1, [x5, 2960]
	cmp	w0, 1
	beq	.L811
.L793:
	add	x0, x5, 2788
	add	x1, x1, 18
	.p2align 2
.L797:
	ldrsh	w2, [x6]
	add	x1, x1, 2
	strh	w2, [x0]
	add	x0, x0, 2
	add	x6, x6, 2
	ldrsh	w2, [x1, -2]
	cmp	x6, x8
	strh	w2, [x0, 26]
	ldrsh	w2, [x6, 12]
	strh	w2, [x0, 12]
	ldrsh	w2, [x1, 12]
	strh	w2, [x0, 40]
	bne	.L797
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L807:
	add	x19, x19, 12288
	ldrb	w3, [x19, 1472]
	.p2align 2
.L783:
	ldr	x2, .LC169
	mov	w4, 7
	ldr	x1, .LC171
	mov	w0, 1
	add	x2, x2, 472
	bl	dprint_vfmw
.L781:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L811:
	cmp	w2, 1
	beq	.L812
.L794:
	add	x0, x5, 2788
	add	x1, x1, 18
	.p2align 2
.L796:
	ldrsh	w3, [x6]
	add	x1, x1, 2
	strh	w3, [x0]
	add	x0, x0, 2
	add	x6, x6, 2
	ldrsh	w3, [x1, -2]
	cmp	x6, x8
	strh	w3, [x0, 26]
	ldrsh	w3, [x6, 12]
	strh	w3, [x0, 12]
	ldrsh	w3, [x1, 12]
	strh	w3, [x0, 40]
	bne	.L796
	add	x0, x19, x2, uxtb 1
	mov	w1, 16384
	add	x0, x0, 8192
	mov	w2, 1
	strh	w1, [x0, 2800]
	strh	w2, [x0, 2786]
	b	.L781
.L787:
	ldr	w0, [x0, 124]
	ldr	x1, [x5, 2960]
	cmp	w0, 1
	bne	.L793
	b	.L794
.L812:
	add	x1, x5, 2788
	add	x0, x5, 2802
	mov	w3, 16384
	.p2align 2
.L795:
	strh	w2, [x1]
	add	x1, x1, 2
	strh	w2, [x1, 26]
	strh	w3, [x1, 12]
	strh	w3, [x1, 40]
	cmp	x1, x0
	bne	.L795
	b	.L781
	.size	AVS2_CalDistance, .-AVS2_CalDistance
	.align	3
.LC169:
	.xword	.LANCHOR1
	.align	3
.LC171:
	.xword	.LC170
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SetImgFormat
	.type	AVS2_SetImgFormat, %function
AVS2_SetImgFormat:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 8192
	bl	_mcount
	ldr	w0, [x20, 3108]
	ldr	w22, [x20, 5520]
	cmp	w0, 1
	ldr	w23, [x20, 5700]
	beq	.L821
	ldr	w0, [x20, 5740]
	cmp	w0, 1
	cset	w26, ne
.L814:
	ldr	w0, [x20, 3144]
	mov	w25, 0
	ldr	w24, [x20, 5748]
	sub	w0, w0, #1
	cmp	w0, 3
	bhi	.L815
	ldr	x1, .LC172
	add	x1, x1, 496
	ldr	w25, [x1, w0, uxtw 2]
.L815:
	ldr	x1, [x20, 2952]
	ldr	w0, [x21, 4]
	ldr	w1, [x1, 56]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L826
	mov	w3, 3
	cbnz	w26, .L827
.L818:
	ldr	w0, [x19, 64]
	mov	w1, w25
	bfi	w0, w25, 14, 3
	str	w0, [x19, 64]
	lsr	w2, w0, 8
	bfi	w0, w22, 5, 3
	bfi	w2, w24, 4, 2
	and	w0, w0, -29
	bfi	w2, w3, 2, 2
	bfi	w0, w23, 0, 2
	bfi	w2, w26, 0, 2
	strb	w0, [x19, 64]
	strb	w2, [x19, 65]
	mov	x0, x19
	ldrb	w2, [x19, 66]
	ldr	x3, [x20, 2952]
	ldrb	w3, [x3, 15]
	bfi	w2, w3, 1, 1
	strb	w2, [x19, 66]
	ldr	w2, [x20, 2784]
	str	w2, [x19, 152]
	stp	w23, w23, [x19, 56]
	bl	SetAspectRatio
	ldr	x1, [x20, 2952]
	ldrb	w1, [x1, 16]
	str	w1, [x19, 120]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 644]
	str	w1, [x19, 124]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 648]
	str	w1, [x19, 128]
	ldr	x1, [x21, 40]
	ldr	w1, [x1, 652]
	str	w1, [x19, 132]
	ldr	w1, [x20, 3116]
	str	w1, [x19, 68]
	ldr	w1, [x20, 3124]
	str	w1, [x19, 72]
	ldr	w2, [x20, 3120]
	str	w2, [x19, 76]
	ldr	w0, [x20, 3128]
	str	w0, [x19, 80]
	ldr	w0, [x20, 5516]
	str	w0, [x19, 108]
	ldr	x0, [x21, 40]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L828
.L819:
	mov	w0, 18
	str	w0, [x19, 296]
	mov	w0, 4
	mov	w1, 8
	ldr	w3, [x20, 5744]
	mov	w2, 1
	str	w1, [x19, 300]
	cmp	w3, 1
	strb	w2, [x19, 291]
	csel	w0, w0, wzr, ne
	strb	w2, [x19, 289]
	strb	w0, [x19, 284]
	str	w1, [x19, 304]
	str	w1, [x19, 308]
.L813:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L821:
	mov	w26, 0
	b	.L814
	.p2align 3
.L828:
	ldr	w3, [x19, 112]
	add	w1, w1, 15
	lsr	w0, w1, 4
	ldr	w2, [x19, 36]
	lsl	w1, w3, 4
	ldr	x4, [x19, 504]
	add	w5, w3, w2
	mul	w1, w0, w1
	add	w0, w1, w2
	str	w0, [x19, 40]
	add	w3, w3, w0
	add	x1, x4, x1, sxtw
	stp	w2, w0, [x19, 20]
	stp	w5, w3, [x19, 28]
	str	x1, [x19, 512]
	b	.L819
	.p2align 3
.L827:
	ldr	w0, [x20, 5756]
	mov	w3, 2
	cmp	w0, 1
	csinc	w3, w3, wzr, ne
	b	.L818
	.p2align 3
.L826:
	ldr	x1, .LC174
	mov	w2, 3140
	mov	w0, 0
	bl	dprint_vfmw
	b	.L813
	.size	AVS2_SetImgFormat, .-AVS2_SetImgFormat
	.align	3
.LC172:
	.xword	.LANCHOR1
	.align	3
.LC174:
	.xword	.LC173
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_SimpleDirectProcess
	.type	AVS2_SimpleDirectProcess, %function
AVS2_SimpleDirectProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, [x20, 11144]
	mov	w1, 1
	ldrb	w0, [x19, 7]
	strb	w1, [x19, 4]
	cmp	w0, 6
	beq	.L832
	mov	x1, x19
	mov	x0, x20
	bl	AVS2_OutputOneFrame
.L831:
	strb	wzr, [x19, 5]
	mov	w2, 0
	ldr	w1, [x19, 56]
	ldr	w0, [x20, 4]
	bl	FSP_SetRef
	strb	wzr, [x19, 6]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L832:
	ldr	w1, [x19, 56]
	mov	w2, 0
	ldr	w0, [x20, 4]
	bl	FSP_SetDisplay
	b	.L831
	.size	AVS2_SimpleDirectProcess, .-AVS2_SimpleDirectProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DispOrderProcess
	.type	AVS2_DispOrderProcess, %function
AVS2_DispOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 8192
	add	x1, x1, 2776
	ldr	x0, [x1, 176]
	ldrb	w2, [x0, 7]
	cmp	w2, 6
	beq	.L836
	ldrb	w2, [x19, 1]
	cbnz	w2, .L835
	ldr	x2, [x19, 40]
	ldr	w2, [x2, 12]
	cbz	w2, .L837
.L835:
	mov	x0, x19
	bl	AVS2_DisplayFrameInPOI
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L837:
	mov	w20, 1
	strb	w20, [x0, 4]
	mov	x0, x19
	ldr	x1, [x1, 176]
	bl	AVS2_OutputOneFrame
	strb	w20, [x19, 1]
	mov	x0, x19
	bl	AVS2_DisplayFrameInPOI
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L836:
	mov	w2, 1
	strb	w2, [x0, 4]
	mov	w2, 0
	ldr	x1, [x1, 176]
	ldr	w0, [x19, 4]
	ldr	w1, [x1, 56]
	bl	FSP_SetDisplay
	b	.L835
	.size	AVS2_DispOrderProcess, .-AVS2_DispOrderProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DecOrderProcess
	.type	AVS2_DecOrderProcess, %function
AVS2_DecOrderProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 11144]
	mov	w2, 1
	ldrb	w0, [x1, 7]
	strb	w2, [x1, 4]
	cmp	w0, 6
	beq	.L841
	mov	x0, x19
	bl	AVS2_OutputOneFrame
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L841:
	ldr	w0, [x19, 4]
	mov	w2, 0
	ldr	w1, [x1, 56]
	bl	FSP_SetDisplay
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_DecOrderProcess, .-AVS2_DecOrderProcess
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_UpdateFrameBuf
	.type	AVS2_UpdateFrameBuf, %function
AVS2_UpdateFrameBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 13892]
	sub	w0, w0, #5
	cmp	w0, 1
	bls	.L844
	mov	x0, x19
	bl	AVS2_UpdateRefBuf
	mov	x0, x19
	bl	AVS2_RefreshBuf
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L844:
	mov	x0, x19
	bl	AVS2_UpdateSceneBuf.part.7
	mov	x0, x19
	bl	AVS2_UpdateRefBuf
	mov	x0, x19
	bl	AVS2_RefreshBuf
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_UpdateFrameBuf, .-AVS2_UpdateFrameBuf
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_FlushFrameInDpb
	.type	AVS2_FlushFrameInDpb, %function
AVS2_FlushFrameInDpb:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x24, x0
	mov	x0, x30
	add	x19, x24, 16384
	mov	w23, 0
	bl	_mcount
	add	x0, x19, 3076
	mov	w1, 0
	.p2align 2
.L847:
	ldrb	w2, [x0]
	cbnz	w2, .L846
	sub	x2, x29, #3984
	add	w3, w23, 1
	add	x4, x2, x23, sxtw
	ldrb	w2, [x0, 2]
	cbz	w2, .L846
	strb	w1, [x4, 4080]
	uxtb	w23, w3
.L846:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	bne	.L847
	cbz	w23, .L848
	ldr	x21, .LC176
	mov	w25, 0
	mov	w26, 0
	mov	w20, 32767
	mov	w22, 1
	.p2align 2
.L849:
	cbz	w23, .L852
	mov	x1, 0
	mov	w5, 32767
	add	x4, x29, 96
	.p2align 2
.L851:
	ldrb	w2, [x4, x1]
	add	x1, x1, 1
	lsl	x0, x2, 3
	mov	x3, x2
	sub	x0, x0, x2
	lsl	x0, x0, 1
	sub	x0, x0, x2
	add	x0, x24, x0, lsl 3
	add	x0, x0, 16384
	ldrb	w2, [x0, 3076]
	cbnz	w2, .L850
	ldrsh	w0, [x0, 3074]
	cmp	w0, w5
	bgt	.L850
	mov	w5, w0
	mov	w26, w3
.L850:
	cmp	w23, w1
	bgt	.L851
	cmp	w5, w20
	beq	.L852
	sxtw	x2, w26
	mov	x0, x24
	lsl	x1, x2, 3
	sub	x1, x1, x2
	lsl	x1, x1, 1
	sub	x1, x1, x2
	lsl	x1, x1, 3
	add	x27, x24, x1
	add	x1, x1, 16384
	add	x27, x27, 16384
	add	x1, x1, 3072
	add	x1, x24, x1
	strb	w22, [x27, 3076]
	bl	AVS2_OutputOneFrame
	ldrsh	w2, [x27, 3074]
	mov	x1, x21
	mov	w0, 13
	bl	dprint_vfmw
.L852:
	add	w25, w25, 1
	uxtb	w25, w25
	cmp	w23, w25
	bne	.L849
.L848:
	add	x0, x24, 20480
	add	x19, x19, 3078
	add	x0, x0, 646
	b	.L855
	.p2align 3
.L854:
	add	x19, x19, 104
	cmp	x0, x19
	beq	.L866
.L855:
	ldrb	w1, [x19, -2]
	cmp	w1, 1
	bne	.L854
	ldrb	w1, [x19, -1]
	cbnz	w1, .L854
	ldrb	w1, [x19]
	add	x19, x19, 104
	and	w1, w1, 2
	strb	w1, [x19, -104]
	cmp	x0, x19
	bne	.L855
.L866:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	AVS2_FlushFrameInDpb, .-AVS2_FlushFrameInDpb
	.align	3
.LC176:
	.xword	.LC140
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_FlushPreSizeImg
	.type	AVS2_FlushPreSizeImg, %function
AVS2_FlushPreSizeImg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x3, x29, 48
	ldr	w0, [x19, 4]
	add	x2, x29, 40
	add	x1, x29, 36
	stp	wzr, wzr, [x29, 36]
	str	wzr, [x3, -4]!
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x19, 40]
	ldr	w0, [x0, 772]
	cmp	w0, 1
	beq	.L872
	mov	w0, 1
.L868:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L872:
	ldr	w1, [x29, 44]
	mov	w0, 0
	cmp	w1, wzr
	bgt	.L868
	ldr	w1, [x29, 40]
	cmp	w1, 32
	bgt	.L868
	ldr	x0, [x19, 48]
	cmp	x0, xzr
	cset	w0, eq
	b	.L868
	.size	AVS2_FlushPreSizeImg, .-AVS2_FlushPreSizeImg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ArrangeFrameBuf
	.type	AVS2_ArrangeFrameBuf, %function
AVS2_ArrangeFrameBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 20]
	cbz	w0, .L874
	mov	x0, x19
	bl	AVS2_FlushPreSizeImg
	cbnz	w0, .L875
.L877:
	mov	w0, 3
.L876:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L875:
	mov	x0, x19
	bl	AVS2_ClearDpb
	add	x1, x19, 16384
	ldr	w0, [x19, 4]
	add	x1, x1, 2288
	bl	FSP_ClearNotInVoQueue
	str	wzr, [x19, 20]
	.p2align 2
.L874:
	mov	x0, x19
	str	wzr, [x19, 24]
	bl	AVS2_AllocateVHB
	cmp	w0, 3
	mov	w1, w0
	beq	.L877
	mov	w0, 1
	cbnz	w1, .L876
	ldr	x1, .LC178
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_ArrangeFrameBuf, .-AVS2_ArrangeFrameBuf
	.align	3
.LC178:
	.xword	.LC177
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_ParseHeader
	.type	AVS2_ParseHeader, %function
AVS2_ParseHeader:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 56
	bl	_mcount
	mov	w1, 32
	mov	x0, x20
	str	wzr, [x19, 8]
	bl	BsShow
	uxtb	w21, w0
	sub	w0, w21, #176
	cmp	w0, 78
	bls	.L925
.L886:
	cmp	w21, 143
	bhi	.L899
	ldr	w1, [x19, 12]
	mov	w0, 327680
	and	w0, w1, w0
	cmp	w0, 327680
	beq	.L926
.L899:
	mov	x0, x19
	mov	w20, 0
	bl	AVS2_ClearPacket
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L925:
	ldr	x1, .LC179
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx888
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx888:
	.section	.rodata
	.align	0
	.align	2
.L888:
	.byte	(.L887 - .Lrtx888) / 4
	.byte	(.L889 - .Lrtx888) / 4
	.byte	(.L924 - .Lrtx888) / 4
	.byte	(.L891 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L892 - .Lrtx888) / 4
	.byte	(.L891 - .Lrtx888) / 4
	.byte	(.L889 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L886 - .Lrtx888) / 4
	.byte	(.L893 - .Lrtx888) / 4
	.text
	.p2align 3
.L889:
	ldr	w0, [x19, 12]
	tbnz	x0, 15, .L923
	cmp	w21, 177
	beq	.L927
	ldr	x1, .LC184
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x20, .LC180
.L908:
	ldr	w0, [x20]
	tbnz	x0, 0, .L924
	mov	x0, x19
	bl	AVS2_ClearDpb
	.p2align 2
.L924:
	mov	x0, x19
	mov	w20, 1
	bl	AVS2_ClearPacket
.L895:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L887:
	ldr	w0, [x19, 12]
	tbnz	x0, 15, .L923
	ldr	w0, [x19, 28]
	cmn	w0, #1
	mov	x0, x19
	beq	.L928
	bl	AVS2_FlushFrameInDpb
.L897:
	mov	x0, x19
	mov	w20, 1
	bl	AVS2_SequenceHeader
	mov	x0, x19
	bl	AVS2_ClearPacket
	b	.L895
	.p2align 3
.L891:
	ldr	w0, [x19, 12]
	tbnz	x0, 15, .L923
	tbz	x0, 16, .L899
	ldr	w0, [x19, 20]
	cmp	w0, 1
	beq	.L900
	ldr	w0, [x19, 24]
	cbnz	w0, .L901
.L900:
	mov	x0, x19
	bl	AVS2_ArrangeFrameBuf
	cmp	w0, 1
	mov	w20, w0
	beq	.L901
	cmp	w0, 3
	bne	.L922
	mov	w0, 1
	str	w0, [x19, 8]
	b	.L895
	.p2align 3
.L892:
	mov	x0, x19
	mov	w20, 1
	bl	AVS2_Extension
	mov	x0, x19
	bl	AVS2_ClearPacket
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L893:
	mov	w1, 32
	mov	x0, x20
	bl	BsSkip
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 32
	mov	x0, x20
	bl	BsGet
	ldr	w1, [x19, 12]
	tbnz	x1, 15, .L929
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w21, w2
	ccmp	w0, w1, 0, eq
	bne	.L899
	mov	w1, -1
	mov	w0, 1
	str	w1, [x19, 28]
	strb	w0, [x19]
	b	.L924
	.p2align 3
.L923:
	mov	w20, 1
	orr	w0, w0, 16384
	stp	w20, w0, [x19, 8]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L929:
	mov	w20, 1
	orr	w1, w1, 16384
	stp	w20, w1, [x19, 8]
	b	.L895
	.p2align 3
.L927:
	ldr	x20, .LC180
	ldr	w0, [x20]
	tbz	x0, 0, .L930
.L907:
	ldr	x1, .LC182
	mov	w0, 1
	bl	dprint_vfmw
	b	.L908
	.p2align 3
.L901:
	ldr	w0, [x19, 28]
	cmp	w21, 179
	add	w0, w0, 1
	str	w0, [x19, 28]
	mov	x0, x19
	beq	.L931
	bl	AVS2_InterPictureHeader
	b	.L924
	.p2align 3
.L928:
	bl	AVS2_ClearDpb
	b	.L897
	.p2align 3
.L926:
	mov	x0, x19
	bl	AVS2_WriteSliceMsg
	mov	w20, w0
	cbnz	w0, .L895
.L922:
	mov	x0, x19
	bl	AVS2_ClearPacket
	b	.L895
	.p2align 3
.L930:
	mov	x0, x19
	bl	AVS2_FlushFrameInDpb
	b	.L907
	.p2align 3
.L931:
	bl	AVS2_IntraPictureHeader
	b	.L924
	.size	AVS2_ParseHeader, .-AVS2_ParseHeader
	.align	3
.LC179:
	.xword	.L888
	.align	3
.LC180:
	.xword	g_StandardObedience
	.align	3
.LC182:
	.xword	.LC181
	.align	3
.LC184:
	.xword	.LC183
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_DecodeArbiter
	.type	AVS2_DecodeArbiter, %function
AVS2_DecodeArbiter:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, 49152
	ldr	w20, [x19, 12]
	movk	w0, 0x5, lsl 16
	and	w0, w20, w0
	cmp	w0, 376832
	beq	.L935
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L935:
	add	x0, x19, 8192
	add	x1, x19, 12288
	mov	x2, 3692
	add	x1, x1, 2692
	add	x0, x0, 3096
	bl	memcpy
	mov	w0, 16383
	movk	w0, 0xfffb, lsl 16
	and	w20, w20, w0
	str	w20, [x19, 12]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_DecodeArbiter, .-AVS2_DecodeArbiter
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_PrepareDecode
	.type	AVS2_PrepareDecode, %function
AVS2_PrepareDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	AVS2_SetPicInfo
	ldr	w3, [x19, 1748]
	sub	w0, w3, #1
	cmp	w0, 255
	bhi	.L951
	mov	x0, x19
	bl	AVS2_VarifyDecMode
	cbnz	w0, .L952
.L950:
	mov	w0, 0
.L938:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L952:
	mov	x0, x19
	bl	AVS2_SetupFrameBuf
	cbz	w0, .L950
	ldr	w0, [x19, 13896]
	cbnz	w0, .L941
	mov	x0, x19
	bl	AVS2_SetupRefFrame
	cbz	w0, .L943
	mov	x0, x19
	bl	AVS2_CalDistance
.L941:
	mov	x0, x19
	bl	AVS2_SetupHalConfig
	cbz	w0, .L943
	mov	w0, 1
	b	.L938
	.p2align 3
.L951:
	ldr	x2, .LC185
	mov	w0, 1
	ldr	x1, .LC187
	add	x2, x2, 512
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L943:
	mov	x0, x19
	bl	AVS2_ReleaseFrameBuf
	b	.L950
	.size	AVS2_PrepareDecode, .-AVS2_PrepareDecode
	.align	3
.LC185:
	.xword	.LANCHOR1
	.align	3
.LC187:
	.xword	.LC186
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_StartDecode
	.type	AVS2_StartDecode, %function
AVS2_StartDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, [x19, 40]
	add	x0, x19, 608
	str	x0, [x19, 48]
	ldr	w2, [x1, 640]
	strb	w2, [x19, 610]
	ldr	w1, [x1, 692]
	strb	w1, [x19, 609]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_StartDecode, .-AVS2_StartDecode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_PostProcess
	.type	AVS2_PostProcess, %function
AVS2_PostProcess:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	AVS2_SetImgFormat
	ldr	x0, [x19, 40]
	ldr	w1, [x0, 8]
	cmp	w1, 2
	beq	.L961
	ldr	w2, [x0, 24]
	cbz	w2, .L962
	sub	w0, w2, #1
	cmp	w0, 1
	bls	.L960
	ldr	x1, .LC189
	mov	w0, 1
	bl	dprint_vfmw
.L960:
	mov	x0, x19
	bl	AVS2_DecOrderProcess
.L958:
	mov	x0, x19
	bl	AVS2_UpdateFrameBuf
.L954:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L962:
	mov	x0, x19
	bl	AVS2_DispOrderProcess
	b	.L958
	.p2align 3
.L961:
	mov	x0, x19
	bl	AVS2_SimpleDirectProcess
	b	.L954
	.size	AVS2_PostProcess, .-AVS2_PostProcess
	.align	3
.LC189:
	.xword	.LC188
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_Init
	.type	AVS2DEC_Init, %function
AVS2DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L967
	ldr	x3, .LC191
	add	x21, x19, 16384
	mov	x2, 21120
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	ldr	w22, [x21, 2888]
	blr	x3
	str	w22, [x21, 2888]
	mov	x0, x19
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 4]
	beq	.L968
	add	x0, x21, 2288
	bl	ResetVoQueue
	str	x20, [x19, 40]
	str	wzr, [x20, 960]
	mov	w1, -1
	mov	w0, 1
	str	w1, [x19, 28]
.L965:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L967:
	ldr	x1, .LC190
	mov	w2, 3698
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L968:
	ldr	x2, .LC192
	mov	w0, 0
	ldr	x1, .LC194
	add	x2, x2, 536
	bl	dprint_vfmw
	mov	w0, -20
	b	.L965
	.size	AVS2DEC_Init, .-AVS2DEC_Init
	.align	3
.LC190:
	.xword	.LC136
	.align	3
.LC191:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC192:
	.xword	.LANCHOR1
	.align	3
.LC194:
	.xword	.LC193
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_Destroy
	.type	AVS2DEC_Destroy, %function
AVS2DEC_Destroy:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	AVS2DEC_Destroy, .-AVS2DEC_Destroy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2_TryReleaseOldestFs
	.type	AVS2_TryReleaseOldestFs, %function
AVS2_TryReleaseOldestFs:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, -1
	bl	_mcount
	add	x6, x20, 16384
	mov	w3, 4095
	add	x0, x6, 3078
	mov	w4, 0
	mov	w1, 0
	b	.L972
	.p2align 3
.L971:
	add	w1, w1, 1
	add	x0, x0, 104
	cmp	w1, 16
	beq	.L978
.L972:
	ldrb	w2, [x0]
	cbz	w2, .L971
	ldrb	w2, [x0, -1]
	cmp	w2, 1
	bne	.L971
	ldrsh	w2, [x0, -6]
	add	w4, w4, 1
	cmp	w2, w3
	bge	.L971
	ldrb	w5, [x0, -2]
	add	x0, x0, 104
	cmp	w5, 1
	csel	w19, w19, w1, ne
	add	w1, w1, 1
	csel	w3, w3, w2, ne
	cmp	w1, 16
	bne	.L972
	.p2align 2
.L978:
	ldrb	w0, [x6, 1012]
	add	w0, w0, 1
	cmp	w4, w0
	ccmn	w19, #1, 4, cs
	beq	.L970
	ldr	x2, .LC195
	mov	w0, 1
	ldr	x1, .LC197
	sxtw	x19, w19
	add	x2, x2, 552
	bl	dprint_vfmw
	lsl	x0, x19, 3
	mov	w2, 0
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 3
	add	x0, x0, 16384
	strb	wzr, [x0, 3078]
	strb	wzr, [x0, 3077]
	ldr	w1, [x0, 3128]
	ldr	w0, [x20, 4]
	bl	FSP_SetRef
.L970:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2_TryReleaseOldestFs, .-AVS2_TryReleaseOldestFs
	.align	3
.LC195:
	.xword	.LANCHOR1
	.align	3
.LC197:
	.xword	.LC196
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_GetImageBuffer
	.type	AVS2DEC_GetImageBuffer, %function
AVS2DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L986
	ldr	w0, [x19, 4]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L981
	ldr	w0, [x19, 4]
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L987
.L982:
	mov	x0, x19
	bl	AVS2_TryReleaseOldestFs
	mov	w0, 0
.L981:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L987:
	add	x1, x19, 16384
	ldr	w0, [x19, 4]
	add	x1, x1, 2288
	bl	FSP_ClearNotInVoQueue
	b	.L982
	.p2align 3
.L986:
	ldr	x1, .LC198
	mov	w2, 3772
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2DEC_GetImageBuffer, .-AVS2DEC_GetImageBuffer
	.align	3
.LC198:
	.xword	.LC136
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_Decode
	.type	AVS2DEC_Decode, %function
AVS2DEC_Decode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L996
	ldr	w2, [x20, 20]
	add	x0, x19, 56
	ldr	x1, [x20]
	bl	BsInit
	ldr	x3, .LC200
	add	x0, x19, 16384
	mov	x2, 176
	mov	x1, x20
	add	x0, x0, 2896
	ldr	x3, [x3, 104]
	blr	x3
	ldr	w0, [x19, 12]
	str	w0, [x19, 16]
	mov	x0, x19
	bl	AVS2_ParseHeader
	cmp	w0, 3
	beq	.L997
	mov	w20, 0
	cbz	w0, .L990
	mov	w0, 49152
	ldr	w21, [x19, 12]
	movk	w0, 0x5, lsl 16
	and	w0, w21, w0
	cmp	w0, 376832
	beq	.L998
.L990:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L996:
	ldr	x1, .LC199
	mov	w2, 3795
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L997:
	ldr	w1, [x19, 16]
	mov	w20, w0
	str	w1, [x19, 12]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L998:
	add	x0, x19, 8192
	add	x1, x19, 12288
	mov	x2, 3692
	add	x1, x1, 2692
	add	x0, x0, 3096
	bl	memcpy
	mov	w0, 16383
	movk	w0, 0xfffb, lsl 16
	and	w21, w21, w0
	mov	x0, x19
	str	w21, [x19, 12]
	bl	AVS2_PrepareDecode
	cbz	w0, .L999
	ldr	x1, [x19, 40]
	add	x0, x19, 608
	str	x0, [x19, 48]
	mov	w20, 1
	ldr	w2, [x1, 640]
	strb	w2, [x19, 610]
	ldr	w1, [x1, 692]
	strb	w1, [x19, 609]
	b	.L990
	.p2align 3
.L999:
	mov	x0, x19
	bl	AVS2_ClearPicSlice
	b	.L990
	.size	AVS2DEC_Decode, .-AVS2DEC_Decode
	.align	3
.LC199:
	.xword	.LC136
	.align	3
.LC200:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_RecycleImage
	.type	AVS2DEC_RecycleImage, %function
AVS2DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L1004
	ldr	w0, [x19, 4]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x19, 4]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L1003
	ldr	w0, [x19, 4]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 4]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1003:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1004:
	ldr	x1, .LC201
	mov	w2, 3880
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2DEC_RecycleImage, .-AVS2DEC_RecycleImage
	.align	3
.LC201:
	.xword	.LC136
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_GetRemainImg
	.type	AVS2DEC_GetRemainImg, %function
AVS2DEC_GetRemainImg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1008
	mov	x0, x19
	bl	AVS2_FlushFrameInDpb
	add	x0, x19, 16384
	add	x0, x0, 2288
	bl	GetVoLastImageID
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1008:
	ldr	x1, .LC202
	mov	w2, 3902
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2DEC_GetRemainImg, .-AVS2DEC_GetRemainImg
	.align	3
.LC202:
	.xword	.LC136
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_ClearCurPic
	.type	AVS2DEC_ClearCurPic, %function
AVS2DEC_ClearCurPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1012
	mov	x0, x19
	bl	AVS2_ClearPicSlice
	mov	x0, x19
	bl	AVS2_ReleaseFrameBuf
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1012:
	ldr	x1, .LC203
	mov	w2, 3924
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	AVS2DEC_ClearCurPic, .-AVS2DEC_ClearCurPic
	.align	3
.LC203:
	.xword	.LC136
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AVS2DEC_VDMPostProc
	.type	AVS2DEC_VDMPostProc, %function
AVS2DEC_VDMPostProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	mov	w22, w2
	mov	w20, w3
	bl	_mcount
	cbz	x19, .L1023
	ldr	x1, [x19, 11144]
	ldrb	w2, [x19, 611]
	strb	w2, [x1, 15]
	ldrb	w0, [x19, 610]
	strb	w0, [x1, 16]
	cbz	w22, .L1016
	ldr	x3, .LC205
	sbfiz	x20, x20, 6, 32
	add	x20, x3, x20
	ldr	w0, [x20, 44]
	cmp	w0, 3
	beq	.L1024
	cmp	w0, 1
	beq	.L1016
	ldr	x0, [x19, 40]
	ldr	w0, [x0, 4]
	cmp	w0, w21
	mov	x0, x19
	blt	.L1025
.L1019:
	bl	AVS2_PostProcess
	mov	w0, 1
.L1015:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1016:
	mov	x0, x19
	bl	AVS2_ClearPicSlice
	ldr	x0, [x19, 40]
	ldr	w0, [x0, 4]
	cmp	w0, w21
	mov	x0, x19
	bge	.L1019
.L1025:
	bl	AVS2DEC_ClearCurPic
	ldr	x3, [x19, 40]
	mov	w2, w21
	ldr	x1, .LC207
	mov	w0, 1
	ldr	w3, [x3, 4]
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1024:
	mov	x0, x19
	bl	AVS2_ClearPicSlice
	mov	w0, 1
	b	.L1015
	.p2align 3
.L1023:
	ldr	x1, .LC204
	mov	w2, 3835
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1015
	.size	AVS2DEC_VDMPostProc, .-AVS2DEC_VDMPostProc
	.align	3
.LC204:
	.xword	.LC136
	.align	3
.LC205:
	.xword	g_VdmDrvParam
	.align	3
.LC207:
	.xword	.LC206
	.global	AVS2_WqM4x4IdxModel2
	.global	AVS2_WqM4x4IdxModel1
	.global	AVS2_WqM4x4IdxModel0
	.global	AVS2_WqM8x8IdxModel2
	.global	AVS2_WqM8x8IdxModel1
	.global	AVS2_WqM8x8IdxModel0
	.global	AVS2_WQM_8x8Default
	.global	AVS2_WQM_4x4Default
	.global	AVS2_WeightQuantParamBase2
	.global	AVS2_WeightQuantParamBase1
	.global	AVS2_WeightQuantParamDefault
	.global	Avs2_AlfRegionTable
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	CSWTCH.36, %object
	.size	CSWTCH.36, 56
CSWTCH.36:
	.xword	.LC208
	.xword	.LC209
	.xword	.LC210
	.xword	.LC211
	.xword	.LC212
	.xword	.LC213
	.xword	.LC214
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.11572, %object
	.size	__func__.11572, 15
__func__.11572:
	.string	"AVS2_User_Data"
	.zero	1
	.type	AVS2_WqM8x8IdxModel0, %object
	.size	AVS2_WqM8x8IdxModel0, 64
AVS2_WqM8x8IdxModel0:
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
	.type	AVS2_WqM4x4IdxModel0, %object
	.size	AVS2_WqM4x4IdxModel0, 16
AVS2_WqM4x4IdxModel0:
	.byte	0
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	2
	.byte	1
	.byte	5
	.byte	3
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM8x8IdxModel1, %object
	.size	AVS2_WqM8x8IdxModel1, 64
AVS2_WqM8x8IdxModel1:
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
	.type	AVS2_WqM4x4IdxModel1, %object
	.size	AVS2_WqM4x4IdxModel1, 16
AVS2_WqM4x4IdxModel1:
	.byte	0
	.byte	4
	.byte	4
	.byte	5
	.byte	3
	.byte	2
	.byte	2
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WqM8x8IdxModel2, %object
	.size	AVS2_WqM8x8IdxModel2, 64
AVS2_WqM8x8IdxModel2:
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
	.type	AVS2_WqM4x4IdxModel2, %object
	.size	AVS2_WqM4x4IdxModel2, 16
AVS2_WqM4x4IdxModel2:
	.byte	0
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.type	AVS2_WeightQuantParamDefault, %object
	.size	AVS2_WeightQuantParamDefault, 6
AVS2_WeightQuantParamDefault:
	.byte	64
	.byte	49
	.byte	53
	.byte	58
	.byte	58
	.byte	64
	.zero	2
	.type	AVS2_WeightQuantParamBase1, %object
	.size	AVS2_WeightQuantParamBase1, 6
AVS2_WeightQuantParamBase1:
	.byte	67
	.byte	71
	.byte	71
	.byte	80
	.byte	80
	.byte	106
	.zero	2
	.type	AVS2_WeightQuantParamBase2, %object
	.size	AVS2_WeightQuantParamBase2, 6
AVS2_WeightQuantParamBase2:
	.byte	64
	.byte	49
	.byte	53
	.byte	58
	.byte	58
	.byte	64
	.zero	2
	.type	AVS2_WQM_4x4Default, %object
	.size	AVS2_WQM_4x4Default, 16
AVS2_WQM_4x4Default:
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	64
	.byte	68
	.byte	76
	.byte	80
	.byte	72
	.byte	76
	.byte	84
	.byte	96
	.type	AVS2_WQM_8x8Default, %object
	.size	AVS2_WQM_8x8Default, 64
AVS2_WQM_8x8Default:
	.byte	64
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	68
	.byte	72
	.byte	76
	.byte	64
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	84
	.byte	92
	.byte	64
	.byte	64
	.byte	68
	.byte	72
	.byte	76
	.byte	80
	.byte	88
	.byte	100
	.byte	64
	.byte	68
	.byte	72
	.byte	80
	.byte	84
	.byte	92
	.byte	100
	.byte	112
	.byte	68
	.byte	72
	.byte	80
	.byte	84
	.byte	92
	.byte	104
	.byte	112
	.byte	-128
	.byte	76
	.byte	80
	.byte	84
	.byte	92
	.byte	104
	.byte	116
	.byte	-124
	.byte	-104
	.byte	96
	.byte	100
	.byte	104
	.byte	116
	.byte	124
	.byte	-116
	.byte	-92
	.byte	-68
	.byte	104
	.byte	108
	.byte	116
	.byte	-128
	.byte	-104
	.byte	-84
	.byte	-64
	.byte	-40
	.type	Avs2_AlfRegionTable, %object
	.size	Avs2_AlfRegionTable, 16
Avs2_AlfRegionTable:
	.byte	0
	.byte	1
	.byte	4
	.byte	5
	.byte	15
	.byte	2
	.byte	3
	.byte	6
	.byte	14
	.byte	11
	.byte	10
	.byte	7
	.byte	13
	.byte	12
	.byte	9
	.byte	8
	.type	__func__.11728, %object
	.size	__func__.11728, 24
__func__.11728:
	.string	"AVS2_IntraPictureHeader"
	.type	__func__.11746, %object
	.size	__func__.11746, 24
__func__.11746:
	.string	"AVS2_InterPictureHeader"
	.type	__func__.11883, %object
	.size	__func__.11883, 19
__func__.11883:
	.string	"AVS2_SetupFrameBuf"
	.zero	5
	.type	__func__.11902, %object
	.size	__func__.11902, 19
__func__.11902:
	.string	"AVS2_SetupRefFrame"
	.zero	5
	.type	__func__.11933, %object
	.size	__func__.11933, 17
__func__.11933:
	.string	"AVS2_CalDistance"
	.zero	7
	.type	CSWTCH.82, %object
	.size	CSWTCH.82, 16
CSWTCH.82:
	.word	5
	.word	1
	.word	2
	.word	3
	.type	__func__.12041, %object
	.size	__func__.12041, 19
__func__.12041:
	.string	"AVS2_PrepareDecode"
	.zero	5
	.type	__func__.12058, %object
	.size	__func__.12058, 13
__func__.12058:
	.string	"AVS2DEC_Init"
	.zero	3
	.type	__func__.12073, %object
	.size	__func__.12073, 24
__func__.12073:
	.string	"AVS2_TryReleaseOldestFs"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC0:
	ASCII(.string	"AVS2_ue_v ERROR: LeadingZeros (%d) >= 32, return 0x%x\n" )
	.zero	1
.LC5:
	ASCII(.string	"Stream StartCode is 0x%x Length is too Long cannot Remove DPB!!" )
.LC9:
	ASCII(.string	"Unkown" )
	.zero	1
.LC11:
	ASCII(.string	"\n" )
	.zero	6
.LC13:
	ASCII(.string	" ----> Dump Dpb Status:\n" )
	.zero	7
.LC16:
	ASCII(.string	"Pic %2d, Type %6s, Occupied %d, Ref %d, Disp %d, DOI %d, POI %d, FspID %d, FsPhy 0x%x, PmvPhy 0x%x\n" )
	.zero	4
.LC18:
	ASCII(.string	" ----> Dump End: Totoal Occupied Frame %d\n\n" )
	.zero	4
.LC21:
	ASCII(.string	"User Data:\n" )
	.zero	4
.LC24:
	ASCII(.string	"%s: cosume TotalPos(%d > %d)!\n" )
	.zero	1
.LC26:
	ASCII(.string	"Slice num out of slot: %d > %d\n" )
.LC28:
	ASCII(.string	"Stream ERROR: slice_vertical_position %d out of range [0, 0x8F].\n" )
	.zero	6
.LC42:
	ASCII(.string	"Stream ERROR: alf_filter_num_minus1 %d > 15.\n" )
	.zero	2
.LC44:
	ASCII(.string	"ALF ERROR: alf_region_distance %d out of range [1, 15].\n" )
	.zero	7
.LC46:
	ASCII(.string	"ALF ERROR: alf_coef_luma_8 %d out of range [-1088, 1071].\n" )
	.zero	5
.LC48:
	ASCII(.string	"ALF ERROR: alf_coef_luma_%d %d out of range [-64, 63].\n" )
.LC52:
	ASCII(.string	"ALF ERROR: alf_coef_chroma0_8 %d out of range [-1088, 1071].\n" )
	.zero	2
.LC54:
	ASCII(.string	"ALF ERROR: alf_coef_chroma0_%d %d out of range [-64, 63].\n" )
	.zero	5
.LC56:
	ASCII(.string	"ALF ERROR: alf_coef_chroma1_8 %d out of range [-1088, 1071].\n" )
	.zero	2
.LC58:
	ASCII(.string	"ALF ERROR: alf_coef_chroma1_%d %d out of range [-64, 63].\n" )
	.zero	5
.LC61:
	ASCII(.string	"Intra stream ERROR: picture_output_delay out of range [0, 63], force 63.\n" )
	.zero	6
.LC63:
	ASCII(.string	"Intra stream ERROR: force progressive_frame to 0 for field_coded_sequence = 1\n" )
	.zero	1
.LC65:
	ASCII(.string	"Intra stream ERROR: picture_qp %d out of range [0, %d], force %d.\n" )
	.zero	5
.LC67:
	ASCII(.string	"Intra stream ERROR: alpha_c_offset %d out of range [-8, 8], force 0.\n" )
	.zero	2
.LC69:
	ASCII(.string	"Intra stream ERROR: beta_offset %d out of range [-8, 8], force 0.\n" )
	.zero	5
.LC71:
	ASCII(.string	"Intra stream ERROR: chroma_quant_param_delta_cb %d out of range [-16, 16], force 0.\n" )
	.zero	3
.LC73:
	ASCII(.string	"Intra stream ERROR: chroma_quant_param_delta_cr %d out of range [-16, 16], force 0.\n" )
	.zero	3
.LC76:
	ASCII(.string	"%s call AVS2_alf_parameter_set failed\n" )
	.zero	1
.LC78:
	ASCII(.string	"Inter stream ERROR: picture_coding_type should not equal 0.\n" )
	.zero	3
.LC80:
	ASCII(.string	"Inter stream ERROR: picture_output_delay out of range [0, 63], force 63.\n" )
	.zero	6
.LC83:
	ASCII(.string	"Inter stream ERROR: force progressive_frame to 1 for progressive_sequence = 1\n" )
	.zero	1
.LC85:
	ASCII(.string	"Inter stream ERROR: force progressive_frame to 0 for field_coded_sequence = 1\n" )
	.zero	1
.LC87:
	ASCII(.string	"Inter stream ERROR: picture_qp %d out of range [0, %d], force %d.\n" )
	.zero	5
.LC89:
	ASCII(.string	"Inter stream ERROR: alpha_c_offset %d out of range [-8, 8], force 0.\n" )
	.zero	2
.LC91:
	ASCII(.string	"Inter stream ERROR: beta_offset %d out of range [-8, 8], force 0.\n" )
	.zero	5
.LC93:
	ASCII(.string	"Inter stream ERROR: chroma_quant_param_delta_cb %d out of range [-16, 16], force 0.\n" )
	.zero	3
.LC95:
	ASCII(.string	"Inter stream ERROR: chroma_quant_param_delta_cr %d out of range [-16, 16], force 0.\n" )
	.zero	3
.LC99:
	ASCII(.string	"%s ERROR: ucRefPicNum out of range [1, %d].\n" )
	.zero	3
.LC101:
	ASCII(.string	"Sequence Header:\n" )
	.zero	6
.LC103:
	ASCII(.string	"Stream ERROR: profile_id 0x%x unsupport.\n" )
	.zero	6
.LC105:
	ASCII(.string	"Stream ERROR: level_id should not equal 0.\n" )
	.zero	4
.LC107:
	ASCII(.string	"Stream ERROR: field_coded_sequence should be 0 when progressive_sequence = 1\n" )
	.zero	2
.LC109:
	ASCII(.string	"Stream ERROR: horizontal_size should not equal 0.\n" )
	.zero	5
.LC111:
	ASCII(.string	"Stream ERROR: vertical_size should not equal 0.\n" )
	.zero	7
.LC113:
	ASCII(.string	"Stream ERROR: chroma_format %d not support, only 4:2:0 now.\n" )
	.zero	3
.LC115:
	ASCII(.string	"Stream ERROR: sample_precision %d should equal to 8/10\n" )
.LC117:
	ASCII(.string	"AVS2 sequence ERROR: ucBitDepth %d should equal to 8/10, and not less than sample_precision %d\n" )
.LC119:
	ASCII(.string	"Stream ERROR: aspect_ratio = 0 is forbidden!\n" )
	.zero	2
.LC121:
	ASCII(.string	"Stream ERROR: frame_rate_code = 0 is forbidden!\n" )
	.zero	7
.LC123:
	ASCII(.string	"Stream ERROR: num_of_rcs %d out of range [0, %d]\n" )
	.zero	6
.LC125:
	ASCII(.string	"MbWidth = %d, MbHeight = %d, don't support!\n" )
	.zero	3
.LC127:
	ASCII(.string	"avs2 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	1
.LC129:
	ASCII(.string	"avs2 actual frame size(%dx%d) exceed max config(%dx%d)\n" )
.LC132:
	ASCII(.string	"ERROR: partition fs memory failed!\n" )
	.zero	4
.LC134:
	ASCII(.string	"ERROR: FSP_ConfigInstance failed!\n" )
	.zero	5
.LC136:
	ASCII(.string	"line: %d\n" )
	.zero	6
.LC138:
	ASCII(.string	"ERROR: AVS2_OutputOneFrame is err(%d)\n" )
	.zero	1
.LC140:
	ASCII(.string	"Dump frame, POI: %d\n" )
	.zero	3
.LC142:
	ASCII(.string	"NumOfRemovedPicture: %d\n" )
	.zero	7
.LC144:
	ASCII(.string	"Target removal DOI[%d]: %d\n" )
	.zero	4
.LC146:
	ASCII(.string	"Conflict: cur frame(Type %d, DOI %d, FspID %d, FsPhy 0x%x, PmvPhy 0x%x) with frame(Type %d, Occupied %d, UsedAsRef %d, DOI %d, FspID %d, FsPhy 0x%x, PmvPhy 0x%x)\n" )
	.zero	5
.LC149:
	ASCII(.string	"%s: Can't find non-occupied frame memory buffer!!!\n" )
	.zero	4
.LC151:
	ASCII(.string	"%s ERROR: get frame store fail!\n" )
	.zero	7
.LC153:
	ASCII(.string	"%s ERROR: get image pointer fail!\n" )
	.zero	5
.LC155:
	ASCII(.string	"Varify current frame DOI %d failed!\n" )
	.zero	3
.LC159:
	ASCII(.string	"Can't find G or GB picture for the reference of S picture.\n" )
	.zero	4
.LC161:
	ASCII(.string	"CurPic Doi %d cant find ref frame TargetDoi %d\n" )
.LC163:
	ASCII(.string	"Found ref num %d < num_of_reference_picture %d\n" )
.LC166:
	ASCII(.string	"%s ERROR: num_of_reference_picture %d out of range [1, %d].\n" )
	.zero	3
.LC170:
	ASCII(.string	"%s ERROR: pstRefFrmMem[0] = NULL or ucRefPicNum %d out of range [1, %d].\n" )
	.zero	6
.LC173:
	ASCII(.string	"line: %d pImage is null\n" )
	.zero	7
.LC177:
	ASCII(.string	"ERROR: allocate vhb\n" )
	.zero	3
.LC181:
	ASCII(.string	"AVS2_VIDEO_SEQUENCE_END_CODE\n" )
	.zero	2
.LC183:
	ASCII(.string	"AVS2_VIDEO_EDIT_CODE\n" )
	.zero	2
.LC186:
	ASCII(.string	"%s SliceNum %d invalid.\n" )
	.zero	7
.LC188:
	ASCII(.string	"AVS2 unsupport output order %d, force dec order output.\n" )
	.zero	7
.LC193:
	ASCII(.string	"%s get chan id failed!\n" )
.LC196:
	ASCII(.string	"%s set fs unref with oldest Doi %d to proceed decoding for ref num %d is full.\n" )
.LC206:
	ASCII(.string	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\n" )
	.zero	1
.LC208:
	ASCII(.string	"I_PIC" )
	.zero	2
.LC209:
	ASCII(.string	"P_PIC" )
	.zero	2
.LC210:
	ASCII(.string	"B_PIC" )
	.zero	2
.LC211:
	ASCII(.string	"F_PIC" )
	.zero	2
.LC212:
	ASCII(.string	"S_PIC" )
	.zero	2
.LC213:
	ASCII(.string	"G_PIC" )
	.zero	2
.LC214:
	ASCII(.string	"GB_PIC" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
