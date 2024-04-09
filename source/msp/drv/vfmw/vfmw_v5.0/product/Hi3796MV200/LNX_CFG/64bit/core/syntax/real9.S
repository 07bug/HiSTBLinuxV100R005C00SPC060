#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"real9.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetBits
	.type	Real9_CB_GetBits, %function
Real9_CB_GetBits:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	x0, x19
	bl	BsShow
	mov	w21, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	mov	w0, w21
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real9_CB_GetBits, .-Real9_CB_GetBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_Get1Bit
	.type	Real9_CB_Get1Bit, %function
Real9_CB_Get1Bit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_CB_Get1Bit, .-Real9_CB_Get1Bit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetVLCBits
	.type	Real9_CB_GetVLCBits, %function
Real9_CB_GetVLCBits:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x23, x1
	mov	w20, 0
	bl	_mcount
	ldr	x22, .LC2
	mov	w19, 0
	.p2align 2
.L4:
	mov	w1, 8
	mov	x0, x21
	bl	BsShow
	ldrb	w2, [x22, w0, uxtw]
	mov	x0, x21
	lsr	w1, w2, 4
	lsr	w3, w2, 5
	add	w20, w20, w1
	and	w2, w2, 15
	lsl	w19, w19, w3
	orr	w19, w2, w19
	bl	BsSkip
	tbz	x20, 0, .L4
	str	w19, [x23]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	Real9_CB_GetVLCBits, .-Real9_CB_GetVLCBits
	.align	3
.LC2:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_GetImageBuffer
	.type	Real9_GetImageBuffer, %function
Real9_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x21, x19, 53248
	add	x19, x19, 8192
	bl	_mcount
	add	x19, x19, 3184
	add	x20, x19, 40960
	mov	w1, 1
	ldr	w0, [x21, 2304]
	bl	FSP_NewLogicFs
	str	w0, [x20, 2552]
	mov	w1, w0
	tbnz	w0, #31, .L14
	ldr	w0, [x21, 2304]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L15
	ldr	x1, .LC8
	mov	w0, 18
	ldr	w2, [x20, 2552]
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L13
	ldr	x1, [x19, 40]
	cbz	x1, .L13
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC10
	bl	dprint_vfmw
	mov	w0, 1
.L10:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L13:
	mov	w0, 1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L14:
	ldr	x1, .LC4
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 2548]
	mov	w2, 1
	ldr	w0, [x21, 2304]
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 2544]
	mov	w2, 1
	ldr	w0, [x21, 2304]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 2544]
	str	wzr, [x20, 2548]
	ldr	w0, [x21, 2304]
	bl	FSP_GetNullLogicFs
	str	w0, [x20, 2544]
	str	w0, [x20, 2548]
	add	x1, x21, 1696
	strb	wzr, [x19, 25]
	ldr	w0, [x21, 2304]
	bl	FSP_ClearNotInVoQueue
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L15:
	ldr	x1, .LC6
	mov	w2, 464
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L10
	.size	Real9_GetImageBuffer, .-Real9_GetImageBuffer
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC6:
	.xword	.LC5
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC10:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_ArrangeVHBMem
	.type	Real9_ArrangeVHBMem, %function
Real9_ArrangeVHBMem:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x2
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldp	w3, w2, [x19, 28]
	cmp	w2, 1
	bls	.L18
	sub	w1, w3, #2
	mov	w0, 512
	cmp	w1, 510
	ccmp	w2, w0, 2, ls
	bhi	.L18
	ldr	x0, [x20]
	ldr	w1, [x0, 772]
	cbnz	w1, .L21
	ldr	w1, [x0, 28]
	cmp	w1, 25
	beq	.L48
.L22:
	ldp	w23, w22, [x19, 20]
	mov	w25, 5
	mov	w21, 2
	mov	w24, 4
.L28:
	ldr	x0, .LC15
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x20]
	ldp	w1, w2, [x19, 20]
	stp	w22, w23, [x29, 92]
	ldr	w0, [x0, 28]
	stp	w2, w1, [x29, 100]
	cmp	w0, 24
	beq	.L34
	strb	w24, [x29, 89]
	sxtb	w0, w21
	strb	w25, [x29, 90]
.L38:
	add	x19, x20, 53248
	strb	w0, [x29, 91]
	add	x1, x29, 88
	ldr	w0, [x19, 2304]
	bl	FSP_ConfigInstance
	mov	w2, 0
	cbnz	w0, .L43
	ldr	x1, [x20]
	add	x3, x29, 84
	ldr	w0, [x19, 2304]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L49
	cbnz	w0, .L36
	add	x20, x20, 8192
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x20, 3212]
	b	.L43
	.p2align 3
.L18:
	ldr	x1, .LC12
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
.L43:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mov	w0, w2
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L21:
	ldr	w1, [x0, 28]
	cmp	w1, 25
	bne	.L22
	ldr	w4, [x0, 732]
	ldp	w3, w2, [x19, 20]
	ldr	w5, [x0, 736]
	cmp	w2, w4
	bhi	.L31
	cmp	w3, w5
	bhi	.L31
	ldr	w4, [x0, 760]
	mov	w22, w2
	ldr	w1, [x0, 756]
	mov	w23, w3
	mov	w21, 1
	add	w24, w1, 2
	cbz	w4, .L33
.L46:
	add	w1, w1, w21
	mov	w21, 17
	cmp	w1, w21
	csel	w21, w1, w21, le
.L33:
	ldrsb	w25, [x0, 780]
	b	.L28
	.p2align 3
.L34:
	mov	w0, 1
	strb	w25, [x29, 90]
	strb	w0, [x29, 89]
	mov	w0, 1
	b	.L38
	.p2align 3
.L31:
	ldr	x1, .LC14
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
	.p2align 3
.L48:
	ldr	w22, [x0, 732]
	ldp	w3, w2, [x19, 20]
	cmp	w2, w22
	bhi	.L50
	ldr	w23, [x0, 736]
	cmp	w3, w23
	bhi	.L51
	add	x1, x20, 8192
	ldrb	w2, [x1, 3212]
	cmp	w2, 1
	beq	.L43
	ldr	w2, [x0, 760]
	mov	w21, 1
	ldr	w1, [x0, 756]
	add	w24, w1, 2
	cbnz	w2, .L46
	ldrsb	w25, [x0, 780]
	b	.L28
	.p2align 3
.L49:
	add	x0, x19, 1696
	bl	ResetVoQueue
.L36:
	ldr	x1, .LC17
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
	.p2align 3
.L51:
	mov	w5, w23
.L24:
	ldr	x1, .LC14
	mov	w4, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
.L50:
	ldr	w5, [x0, 736]
	b	.L24
	.size	Real9_ArrangeVHBMem, .-Real9_ArrangeVHBMem
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC15:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC17:
	.xword	.LC16
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetCPFMT
	.type	Real9_CB_GetCPFMT, %function
Real9_CB_GetCPFMT:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 4
	mov	x0, x19
	bl	BsSkip
	strb	w20, [x21, 8]
	mov	w1, 9
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 9
	mov	x0, x19
	add	w20, w20, 1
	bl	BsSkip
	lsl	w20, w20, 2
	mov	w1, 1
	str	w20, [x21, 24]
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cmp	w20, 1
	beq	.L55
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L55:
	mov	w1, 9
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, 9
	mov	x0, x19
	lsl	w22, w22, 2
	bl	BsSkip
	str	w22, [x21, 20]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real9_CB_GetCPFMT, .-Real9_CB_GetCPFMT
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_SetDimensions
	.type	Real9_CB_SetDimensions, %function
Real9_CB_SetDimensions:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldp	w2, w0, [x19, 20]
	cmp	w0, 128
	beq	.L73
	cmp	w0, 176
	beq	.L74
	cmp	w0, 352
	bne	.L62
	cmp	w2, 288
	beq	.L75
	.p2align 2
.L58:
	add	w1, w0, 15
	add	w2, w2, 15
	add	x19, x19, 72
	lsr	w1, w1, 4
	lsr	w2, w2, 4
	mov	w0, 6
	stp	w2, w1, [x19, 8]
	mul	w1, w1, w2
	sub	w1, w1, #1
	cmp	w1, 47
	bls	.L59
	cmp	w1, 98
	bls	.L68
	cmp	w1, 395
	bls	.L69
	cmp	w1, 1583
	bls	.L70
.L72:
	mov	w2, 6335
	mov	w0, 14
	cmp	w1, w2
	bls	.L76
.L59:
	str	w0, [x19, 16]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L74:
	cmp	w2, 144
	bne	.L58
	add	x19, x19, 72
	mov	w2, 11
	mov	w0, 9
	mov	w1, 1
	stp	w0, w2, [x19, 8]
.L61:
	ldr	x0, .LC18
	add	x0, x0, 256
	ldr	w0, [x0, w1, uxtw 2]
	str	w0, [x19, 16]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L73:
	cmp	w2, 96
	bne	.L58
	add	x19, x19, 72
	mov	w1, 6
	mov	w2, 8
	mov	w0, w1
	stp	w1, w2, [x19, 8]
	b	.L59
	.p2align 3
.L62:
	cmp	w0, 704
	bne	.L64
	cmp	w2, 576
	bne	.L58
	add	x19, x19, 72
	mov	w1, 44
	mov	w0, 36
	stp	w0, w1, [x19, 8]
.L70:
	mov	w1, 3
	b	.L61
	.p2align 3
.L75:
	add	x19, x19, 72
	mov	w1, 22
	mov	w0, 18
	stp	w0, w1, [x19, 8]
.L69:
	mov	w1, 2
	b	.L61
	.p2align 3
.L64:
	cmp	w0, 1408
	bne	.L58
	cmp	w2, 1152
	bne	.L58
	add	x19, x19, 72
	mov	w2, 88
	mov	w0, 72
	mov	w1, 6335
	stp	w0, w2, [x19, 8]
	b	.L72
	.p2align 3
.L76:
	mov	w1, 4
	b	.L61
.L68:
	mov	w1, 1
	b	.L61
	.size	Real9_CB_SetDimensions, .-Real9_CB_SetDimensions
	.align	3
.LC18:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetPicSize
	.type	Real9_CB_GetPicSize, %function
Real9_CB_GetPicSize:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x24, x2
	mov	x23, x3
	bl	_mcount
	ldr	x0, .LC20
	mov	w3, 180
	ldr	w1, [x20, 20]
	add	x2, x0, 280
	add	x0, x0, 312
	sub	w1, w1, #2
	str	w3, [x29, 64]
	cmp	w1, 1
	ldp	x4, x5, [x2]
	stp	x4, x5, [x29, 80]
	ldp	x4, x5, [x0]
	ldp	x2, x3, [x2, 16]
	stp	x4, x5, [x29, 112]
	ldp	x4, x5, [x0, 16]
	stp	x2, x3, [x29, 96]
	mov	w0, 576
	mov	w2, 360
	stp	x4, x5, [x29, 128]
	stp	w0, wzr, [x29, 72]
	str	w2, [x29, 68]
	bls	.L91
.L78:
	mov	w1, 3
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 3
	mov	x0, x19
	bl	BsSkip
	add	x0, x29, 144
	add	x20, x0, x20, uxtw 2
	ldr	w21, [x20, -64]
	cbz	w21, .L81
.L80:
	mov	w1, 3
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, 3
	mov	x0, x19
	bl	BsSkip
	add	x0, x29, 144
	add	x0, x0, x22, uxtw 2
	ldr	w20, [x0, -32]
	cbz	w20, .L92
.L82:
	str	w21, [x24]
	str	w20, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L81:
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 8
	mov	x0, x19
	add	w21, w21, w20, lsl 2
	bl	BsSkip
	cmp	w20, 255
	beq	.L81
	b	.L80
	.p2align 3
.L91:
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w21, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cbz	w21, .L78
	ldr	w0, [x20, 52]
	str	w0, [x24]
	ldr	w0, [x20, 56]
	str	w0, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L92:
	mov	w1, 1
	mov	x0, x19
	lsl	w22, w22, 1
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	orr	w0, w20, w22
	add	x1, x29, 144
	ubfiz	x0, x0, 2, 2
	add	x0, x1, x0
	ldr	w20, [x0, -80]
	cbnz	w20, .L82
	.p2align 2
.L83:
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, 8
	mov	x0, x19
	add	w20, w20, w22, lsl 2
	bl	BsSkip
	cmp	w22, 255
	beq	.L83
	b	.L82
	.size	Real9_CB_GetPicSize, .-Real9_CB_GetPicSize
	.align	3
.LC20:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_FindNextSliceStartCode
	.type	Real9_CB_FindNextSliceStartCode, %function
Real9_CB_FindNextSliceStartCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w22, 7184
	mov	w19, 0
	bl	_mcount
	movk	w22, 0x1d, lsl 16
	mov	x0, x20
	bl	BsToNextByte
	mov	x0, x20
	bl	BsResidBits
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w21, w1, w0, lt
	asr	w21, w21, 3
	sub	w21, w21, #2
	cmp	w21, wzr
	bgt	.L99
	b	.L97
	.p2align 3
.L101:
	bl	BsSkip
	cmp	w19, w21
	beq	.L97
.L99:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	cmp	w0, w22
	mov	w1, 8
	mov	x0, x20
	bne	.L101
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L97:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real9_CB_FindNextSliceStartCode, .-Real9_CB_FindNextSliceStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_SearchBits_IgnoreOnly0
	.type	Real9_CB_SearchBits_IgnoreOnly0, %function
Real9_CB_SearchBits_IgnoreOnly0:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	w25, w1
	mov	w24, w3
	mov	w23, w2
	bl	_mcount
	sub	w2, w25, #1
	mov	w1, w25
	mov	x0, x21
	mov	w22, 1
	lsl	w22, w22, w2
	bl	BsShow
	mov	w19, w0
	mov	w1, w25
	mov	x0, x21
	bl	BsSkip
	cmp	w23, w19
	ccmp	w24, wzr, 4, ne
	beq	.L103
	tst	w22, w19
	bne	.L103
	ldr	x0, .LC23
	mov	w20, 0
	add	x0, x0, 344
	ldr	w25, [x0, w25, uxtw 2]
	b	.L104
	.p2align 3
.L105:
	tst	w22, w19
	bne	.L103
.L104:
	mov	w1, 1
	mov	x0, x21
	add	w20, w20, w1
	and	w19, w25, w19, lsl 1
	bl	BsShow
	mov	w2, w0
	mov	w1, 1
	mov	x0, x21
	orr	w19, w2, w19
	bl	BsSkip
	cmp	w23, w19
	ccmp	w24, w20, 0, ne
	bhi	.L105
.L103:
	cmp	w23, w19
	ldr	x25, [sp, 64]
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	Real9_CB_SearchBits_IgnoreOnly0, .-Real9_CB_SearchBits_IgnoreOnly0
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetSSC
	.type	Real9_CB_GetSSC, %function
Real9_CB_GetSSC:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	cmp	w0, 1
	beq	.L111
	mov	x0, x20
	bl	Real9_CB_FindNextSliceStartCode
	cmp	w0, wzr
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L111:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_CB_GetSSC, .-Real9_CB_GetSSC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetSliceHeader
	.type	Real9_CB_GetSliceHeader, %function
Real9_CB_GetSliceHeader:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x5
	mov	x19, x0
	mov	x0, x30
	mov	w22, w1
	mov	x23, x2
	mov	x25, x3
	mov	x24, x4
	bl	_mcount
	ldr	w20, [x21, 12]
	cmp	w20, 1
	beq	.L150
	cbz	w22, .L151
	str	wzr, [x23]
	mov	w0, -1
	mov	w20, 1
	str	w0, [x24]
.L136:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L150:
	add	x26, x21, 72
	cbnz	w22, .L114
	ldr	w0, [x26, 24]
	cmn	w0, #1
	beq	.L152
	mov	w1, w20
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	cbnz	w27, .L119
	mov	w1, 2
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	ldr	w0, [x26, 20]
	cmp	w0, w20
	beq	.L117
.L119:
	mov	w20, 0
	ldr	x27, [sp, 80]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L151:
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cmp	w20, 1
	bne	.L119
	ldr	w26, [x21, 88]
	mov	x0, x19
	mov	w1, w26
	bl	BsShow
	mov	w27, w0
	mov	w1, w26
	mov	x0, x19
	bl	BsSkip
	str	w27, [x23]
	ldr	w0, [x21, 88]
	cmp	w0, 11
	bls	.L132
	mov	w1, w20
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	cmp	w22, 1
	bne	.L119
.L132:
	mov	w1, 5
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 5
	mov	x0, x19
	bl	BsSkip
	str	w20, [x24]
	cmp	w20, 31
	bgt	.L119
	mov	w1, 2
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	str	w20, [x21, 60]
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cmp	w20, 1
	bne	.L119
	mov	w1, 2
	mov	x0, x19
	bl	BsShow
	mov	w21, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	str	w21, [x25]
	b	.L136
	.p2align 3
.L152:
	mov	w1, w20
	mov	x0, x19
	bl	BsShow
	mov	w22, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	cbnz	w22, .L119
	mov	w1, 2
	mov	x0, x19
	mov	w22, w20
	bl	BsShow
	mov	w20, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	str	w20, [x26, 20]
.L117:
	mov	w1, 5
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 5
	mov	x0, x19
	bl	BsSkip
	uxtb	w0, w20
	strb	w0, [x26, 2]
	cmp	w0, 31
	bhi	.L119
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cbnz	w20, .L119
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w20, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cbnz	w20, .L119
	mov	w1, 2
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, 2
	mov	x0, x19
	bl	BsSkip
	str	w27, [x21, 60]
	mov	w1, 1
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	cmp	w27, wzr
	mov	w1, 13
	cset	w0, ne
	strb	w0, [x26, 1]
	mov	x0, x19
	cbz	w22, .L120
	bl	BsShow
	mov	w22, w0
	mov	w1, 13
	mov	x0, x19
	bl	BsSkip
	str	w22, [x26, 28]
	ldr	w0, [x26, 20]
	cmp	w0, 1
	bls	.L122
	cmp	w0, 2
	bne	.L140
	ldp	w1, w0, [x26, 44]
	stp	w1, w0, [x26, 52]
.L140:
	add	x2, x29, 104
	mov	x1, x26
	mov	x0, x19
	add	x3, x29, 108
	bl	Real9_CB_GetPicSize
	ldp	w1, w0, [x29, 104]
	stp	w1, w0, [x26, 44]
	sub	w2, w1, #48
	stp	w0, w1, [x21, 20]
	mov	w1, 8144
	cmp	w2, w1
	bhi	.L136
	sub	w0, w0, #48
	cmp	w0, w1
	bhi	.L136
	mov	x0, x21
	bl	Real9_CB_SetDimensions
.L128:
	ldr	w20, [x26, 16]
	mov	x0, x19
	mov	w1, w20
	bl	BsShow
	mov	w21, w0
	mov	w1, w20
	mov	x0, x19
	bl	BsSkip
	str	w21, [x26, 24]
.L114:
	ldr	w0, [x26, 24]
	mov	w20, 1
	str	w0, [x23]
	ldrb	w0, [x26, 2]
	str	w0, [x24]
	mov	w0, w20
	str	wzr, [x25]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L120:
	bl	BsShow
	mov	w21, w0
	mov	w1, 13
	mov	x0, x19
	bl	BsSkip
	ldr	w0, [x26, 28]
	cmp	w0, w21
	bne	.L119
	mov	x1, x26
	mov	x0, x19
	add	x3, x29, 108
	add	x2, x29, 104
	bl	Real9_CB_GetPicSize
	ldr	w1, [x26, 44]
	ldr	w0, [x29, 104]
	cmp	w1, w0
	bne	.L136
	ldr	w1, [x26, 48]
	ldr	w0, [x29, 108]
	cmp	w1, w0
	bne	.L136
	b	.L128
.L122:
	stp	wzr, wzr, [x26, 52]
	b	.L140
	.size	Real9_CB_GetSliceHeader, .-Real9_CB_GetSliceHeader
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_CB_GetPictureHeader
	.type	Real9_CB_GetPictureHeader, %function
Real9_CB_GetPictureHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 12]
	cmp	w0, 1
	beq	.L178
	ldr	x3, .LC26
	mov	x2, 136
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	w1, 16
	mov	x0, x20
	bl	BsShow
	mov	w21, w0
	mov	w1, 16
	mov	x0, x20
	bl	BsSkip
	mov	w0, 21845
	cmp	w21, w0
	bne	.L173
	mov	w1, 16
	mov	x0, x20
	bl	BsShow
	mov	w22, w0
	mov	w1, 16
	mov	x0, x20
	bl	BsSkip
	cmp	w22, w21
	bne	.L173
	mov	x0, x20
	add	x1, x29, 60
	bl	Real9_CB_GetVLCBits
	cmp	w0, 30
	bls	.L173
	ldr	w0, [x29, 60]
	tbnz	x0, 0, .L173
	tbnz	x0, 1, .L164
	mov	w2, 176
	mov	w1, 144
	stp	w1, w2, [x19, 20]
.L165:
	ubfx	x1, x0, 2, 5
	ubfx	x0, x0, 7, 8
	str	w1, [x19, 56]
	add	x1, x29, 60
	str	w0, [x19, 44]
	mov	x0, x20
	bl	Real9_CB_GetVLCBits
	cmp	w0, 1
	beq	.L177
	cmp	w0, 3
	beq	.L179
	cmp	w0, 5
	bne	.L173
	ldr	w0, [x29, 60]
	cbnz	w0, .L173
	mov	w0, 2
.L177:
	str	w0, [x19, 16]
.L167:
	ldr	w0, [x19, 24]
	cbz	w0, .L180
.L169:
	sub	w0, w0, #48
	mov	w1, 8144
	cmp	w0, w1
	bhi	.L173
	ldr	w0, [x19, 20]
	sub	w0, w0, #48
	cmp	w0, w1
	bhi	.L173
	mov	x0, x19
	mov	w21, 1
	bl	Real9_CB_SetDimensions
	mov	w1, 2
	mov	x0, x20
	bl	BsShow
	mov	w22, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	str	w22, [x19, 60]
.L155:
	ldp	w2, w1, [x19, 20]
	mov	w0, w21
	add	w1, w1, 15
	add	w2, w2, 15
	lsr	w2, w2, 4
	lsr	w1, w1, 4
	stp	w2, w1, [x19, 28]
	mul	w1, w1, w2
	str	w1, [x19, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L179:
	ldr	w0, [x29, 60]
	cmp	w0, 1
	beq	.L181
.L173:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -2
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L178:
	add	x22, x19, 72
	mov	w0, -1
	mov	x5, x19
	add	x4, x29, 60
	add	x3, x29, 52
	add	x2, x29, 56
	str	w0, [x22, 24]
	mov	w1, 0
	mov	x0, x20
	mov	w21, -2
	bl	Real9_CB_GetSliceHeader
	cmp	w0, 1
	bne	.L155
	ldr	w0, [x22, 20]
	cmp	w0, 3
	bls	.L182
.L156:
	ldrb	w1, [x22, 1]
	str	w1, [x19, 52]
	mov	w1, 8144
	ldr	w0, [x19, 24]
	ldrb	w2, [x22, 2]
	str	w2, [x19, 56]
	sub	w0, w0, #48
	cmp	w0, w1
	ldr	w0, [x22, 28]
	str	w0, [x19, 44]
	ldr	w0, [x22, 32]
	str	w0, [x19, 64]
	ldr	w0, [x22, 36]
	str	w0, [x19, 68]
	bhi	.L173
	ldr	w0, [x19, 20]
	sub	w0, w0, #48
	cmp	w0, w1
	bhi	.L173
	mov	x0, x19
	bl	Real9_CB_SetDimensions
	b	.L155
	.p2align 3
.L164:
	stp	wzr, wzr, [x19, 20]
	b	.L165
	.p2align 3
.L180:
	mov	x1, x19
	mov	x0, x20
	bl	Real9_CB_GetCPFMT
	cbz	w0, .L173
	ldr	w0, [x19, 24]
	b	.L169
	.p2align 3
.L182:
	ldr	x1, .LC25
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx158
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx158:
	.section	.rodata
	.align	0
	.align	2
.L158:
	.byte	(.L157 - .Lrtx158) / 4
	.byte	(.L159 - .Lrtx158) / 4
	.byte	(.L160 - .Lrtx158) / 4
	.byte	(.L161 - .Lrtx158) / 4
	.text
	.p2align 3
.L181:
	str	wzr, [x19, 16]
	b	.L167
.L160:
	mov	w0, 1
	str	w0, [x19, 16]
	mov	w21, w0
	b	.L156
.L159:
	str	wzr, [x19, 16]
	mov	w21, 1
	str	wzr, [x22, 4]
	b	.L156
.L157:
	mov	w0, 1
	str	wzr, [x19, 16]
	mov	w21, w0
	str	w0, [x22, 4]
	b	.L156
.L161:
	mov	w0, 2
	mov	w21, 1
	str	w0, [x19, 16]
	b	.L156
	.size	Real9_CB_GetPictureHeader, .-Real9_CB_GetPictureHeader
	.align	3
.LC25:
	.xword	.L158
	.align	3
.LC26:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_SetImgFormat
	.type	Real9_SetImgFormat, %function
Real9_SetImgFormat:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x21, x20, 53248
	bl	_mcount
	mov	x1, 52336
	add	x1, x20, x1
	ldr	w0, [x21, 2304]
	ldr	w1, [x1, 2552]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L183
	ldr	w3, [x21, 296]
	mov	w6, 5
	ldrb	w2, [x0, 64]
	mov	w5, 1
	ldrb	w1, [x0, 65]
	bfi	w2, w3, 0, 2
	and	w3, w3, 3
	and	w1, w1, -4
	and	w2, w2, -29
	orr	w1, w1, 12
	bfi	w2, w6, 5, 3
	bfi	w1, w5, 4, 2
	strb	w2, [x0, 64]
	strb	w1, [x0, 65]
	mov	w1, 0
	ldr	w2, [x0, 64]
	and	w2, w2, -114689
	str	w2, [x0, 64]
	lsr	w2, w2, 16
	ldrb	w5, [x21, 280]
	bfi	w2, w5, 1, 1
	strb	w2, [x0, 66]
	ldr	w2, [x21, 284]
	str	w2, [x0, 120]
	stp	wzr, w3, [x0, 52]
	str	w3, [x0, 60]
	ldr	w2, [x21, 304]
	str	w2, [x0, 68]
	ldr	w2, [x21, 300]
	str	w2, [x0, 72]
	bl	SetAspectRatio
	ldr	x0, [x20]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L189
.L185:
	mov	w1, 1
	strb	w1, [x19, 291]
	strb	w1, [x19, 289]
	add	x1, x19, 256
	strb	wzr, [x19, 284]
	mov	w0, 8
	mov	w2, 9
	stp	w0, w0, [x1, 48]
	stp	w2, w0, [x1, 40]
.L183:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L189:
	ldr	w1, [x19, 72]
	ldr	w3, [x19, 112]
	add	w1, w1, 15
	ldr	w2, [x19, 36]
	lsl	w0, w3, 4
	lsr	w1, w1, 4
	ldr	x4, [x19, 504]
	add	w5, w3, w2
	mul	w0, w1, w0
	add	w1, w0, w2
	str	w1, [x19, 40]
	add	w3, w3, w1
	add	x0, x4, x0, sxtw
	stp	w2, w1, [x19, 20]
	stp	w5, w3, [x19, 28]
	str	x0, [x19, 512]
	b	.L185
	.size	Real9_SetImgFormat, .-Real9_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RV9_RecordVFMWState
	.type	RV9_RecordVFMWState, %function
RV9_RecordVFMWState:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	RV9_RecordVFMWState, .-RV9_RecordVFMWState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_WriteSliceMsg
	.type	Real9_WriteSliceMsg, %function
Real9_WriteSliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	add	x1, x19, 53248
	lsl	x2, x0, 2
	add	x19, x19, 16
	sub	x2, x2, x0
	add	w20, w20, 1
	lsl	x2, x2, 2
	sub	x2, x2, x0
	ldr	w0, [x1, 444]
	add	x2, x19, x2, lsl 2
	str	w0, [x2, 92]
	ldr	w0, [x1, 436]
	str	w0, [x2, 100]
	ldr	w0, [x1, 440]
	str	w0, [x2, 108]
	ldr	w0, [x1, 456]
	str	w0, [x2, 96]
	ldr	w0, [x1, 448]
	str	w0, [x2, 104]
	ldr	w0, [x1, 452]
	str	w0, [x2, 112]
	ldr	w0, [x1, 424]
	str	w0, [x2, 116]
	ldr	w0, [x1, 420]
	str	w0, [x2, 120]
	ldr	w0, [x1, 416]
	str	w0, [x2, 124]
	ldr	w0, [x1, 428]
	str	w0, [x2, 128]
	str	w20, [x19, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_WriteSliceMsg, .-Real9_WriteSliceMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_WritePicMsg
	.type	Real9_WritePicMsg, %function
Real9_WritePicMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 53248
	mov	x1, 52336
	add	x1, x19, x1
	add	x2, x2, 280
	ldr	w3, [x2, 16]
	strb	w3, [x19, 16]
	cmp	w3, 2
	ldr	w3, [x2, 32]
	str	w3, [x19, 20]
	ldr	w3, [x2, 28]
	str	w3, [x19, 24]
	ldr	w3, [x1, 2468]
	str	w3, [x19, 28]
	ldr	w3, [x1, 2472]
	str	w3, [x19, 32]
	ldr	w2, [x2, 56]
	str	w2, [x19, 36]
	ldr	w3, [x1, 1372]
	str	w3, [x19, 40]
	ldr	w3, [x1, 1376]
	str	w3, [x19, 44]
	beq	.L192
	str	w2, [x1, 1372]
.L192:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_WritePicMsg, .-Real9_WritePicMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_WriteReg
	.type	Real9_WriteReg, %function
Real9_WriteReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	str	w20, [x19, 52]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real9_WriteReg, .-Real9_WriteReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real9_ModifySliceMsg
	.type	Real9_ModifySliceMsg, %function
Real9_ModifySliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 16
	ldr	w1, [x0, 128]
	cbnz	w1, .L202
	ldp	w1, w4, [x0, 4]
	ldr	w5, [x0, 32]
	mul	w4, w1, w4
	cmp	w5, 2
	sub	w4, w4, #1
	bhi	.L224
.L201:
	cmp	w5, 1
	bls	.L206
	sub	w7, w5, #1
	mov	w3, 0
	b	.L207
	.p2align 3
.L208:
	add	w3, w3, 1
	lsl	x1, x1, 2
	sub	x1, x1, x2
	sxtw	x6, w3
	lsl	x2, x6, 2
	add	x1, x0, x1, lsl 2
	sub	x2, x2, x6
	lsl	x2, x2, 2
	sub	x2, x2, x6
	ldr	w6, [x1, 128]
	add	x1, x0, x2, lsl 2
	ldr	w1, [x1, 128]
	cmp	w6, w1
	bge	.L202
.L207:
	sxtw	x2, w3
	cmp	w3, w7
	lsl	x1, x2, 2
	sub	x1, x1, x2
	bne	.L208
	uxtw	x3, w3
	lsl	x1, x3, 2
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x3, x1, x3
	add	x3, x0, x3, lsl 2
	ldr	w1, [x3, 128]
	cmp	w4, w1
	ccmp	w1, wzr, 4, ge
	ble	.L202
.L206:
	cbz	w5, .L209
	sub	w9, w5, #1
	mov	w8, 0
	mov	x10, 44
	b	.L212
	.p2align 3
.L227:
	beq	.L225
.L212:
	add	w3, w8, 1
	sxtw	x7, w8
	lsl	x2, x7, 2
	cmp	w8, w9
	sxtw	x6, w3
	sub	x2, x2, x7
	lsl	x3, x6, 2
	lsl	x2, x2, 2
	sub	x3, x3, x6
	sub	x2, x2, x7
	lsl	x3, x3, 2
	beq	.L226
	sub	x3, x3, x6
	add	x2, x0, x2, lsl 2
	add	x3, x0, x3, lsl 2
	ldr	w3, [x3, 128]
	sub	w3, w3, #1
	str	w3, [x2, 132]
.L211:
	lsl	x1, x7, 2
	add	w8, w8, 1
	sub	x1, x1, x7
	lsl	x1, x1, 2
	sub	x1, x1, x7
	add	x1, x0, x1, lsl 2
	ldr	w2, [x1, 128]
	cmp	w2, w3
	ccmp	w3, wzr, 1, le
	cset	w1, lt
	cmp	w2, wzr
	ccmp	w4, w2, 1, ge
	cset	w2, lt
	cmp	w4, w3
	cset	w3, lt
	orr	w1, w1, w2
	orr	w1, w3, w1
	cmp	w8, w5
	cbz	w1, .L227
	.p2align 2
.L202:
	mov	w0, 0
.L222:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L224:
	ldr	w1, [x0, 172]
	sub	w6, w5, #1
	mov	w2, 1
	cmp	w4, w1
	ccmp	w1, wzr, 4, gt
	bgt	.L204
	b	.L202
	.p2align 3
.L205:
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x1, x1, x3
	add	x1, x0, x1, lsl 2
	ldr	w1, [x1, 128]
	cmp	w1, wzr
	ccmp	w4, w1, 4, gt
	ble	.L202
.L204:
	add	w2, w2, 1
	cmp	w2, w6
	sxtw	x3, w2
	lsl	x1, x3, 2
	bne	.L205
	b	.L201
.L225:
	ldr	w3, [x0, 92]
	mov	w6, 0
	mov	x4, 0
	mov	w2, w3
	b	.L215
	.p2align 3
.L228:
	ldr	w2, [x2, 92]
.L215:
	lsl	x1, x4, 2
	add	w6, w6, 1
	sub	x1, x1, x4
	cmp	w3, w2
	lsl	x1, x1, 2
	csel	w3, w3, w2, ls
	sub	x1, x1, x4
	sxtw	x4, w6
	lsl	x2, x4, 2
	add	x1, x0, x1, lsl 2
	sub	x2, x2, x4
	lsl	x2, x2, 2
	sub	x2, x2, x4
	ldr	w7, [x1, 96]
	add	x2, x0, x2, lsl 2
	cmp	w7, w3
	bcs	.L213
	ldr	w1, [x1, 112]
	cmp	w1, wzr
	csel	w3, w3, w7, eq
.L213:
	cmp	w6, w5
	bne	.L228
	and	w3, w3, -16
	mov	w6, 0
	str	w3, [x0, 40]
	b	.L219
	.p2align 3
.L229:
	ldr	w2, [x1, 100]
	ldr	w7, [x1, 92]
	mov	x4, x2
	add	w2, w7, w2, lsr 3
	and	w4, w4, 7
	sub	w3, w2, w3
	ubfiz	w2, w3, 3, 4
	and	w3, w3, -16
	add	w2, w2, w4
	str	w3, [x1, 92]
	str	w2, [x1, 100]
.L217:
	add	w6, w6, 1
	cmp	w5, w6
	bls	.L218
	ldr	w3, [x0, 40]
.L219:
	sxtw	x2, w6
	lsl	x1, x2, 2
	sub	x1, x1, x2
	lsl	x1, x1, 2
	sub	x1, x1, x2
	add	x1, x0, x1, lsl 2
	ldr	w2, [x1, 96]
	cbz	w2, .L229
	ldp	w4, w2, [x1, 100]
	ldp	w10, w9, [x1, 92]
	mov	x7, x2
	mov	x8, x4
	add	w2, w9, w2, lsr 3
	add	w4, w10, w4, lsr 3
	sub	w4, w4, w3
	sub	w3, w2, w3
	ubfiz	w10, w4, 3, 4
	ubfiz	w9, w3, 3, 4
	and	w2, w7, 7
	and	w8, w8, 7
	and	w4, w4, -16
	add	w7, w10, w8
	and	w3, w3, -16
	add	w2, w9, w2
	stp	w4, w3, [x1, 92]
	stp	w7, w2, [x1, 100]
	b	.L217
.L209:
	ldr	w1, [x0, 92]
	and	w1, w1, -16
	str	w1, [x0, 40]
.L218:
	mov	w0, 1
	b	.L222
.L226:
	madd	x1, x7, x10, x0
	mov	w3, w4
	str	w4, [x1, 132]
	b	.L211
	.size	Real9_ModifySliceMsg, .-Real9_ModifySliceMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_Init
	.type	REAL9DEC_Init, %function
REAL9DEC_Init:
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
	beq	.L234
	ldr	x3, .LC29
	mov	x2, 55568
	mov	w1, 0
	mov	x0, x19
	add	x21, x19, 53248
	ldr	x3, [x3, 96]
	blr	x3
	add	x0, x21, 1696
	bl	ResetVoQueue
	str	x20, [x19]
	add	x1, x19, 8192
	mov	w5, 15
	add	x1, x1, 3184
	mov	w3, 1
	add	x4, x1, 40960
	mov	w6, 8192
	mov	x0, x19
	str	w5, [x4, 1372]
	str	w5, [x4, 1376]
	ldr	w4, [x20, 8]
	strb	w4, [x1, 24]
	strb	wzr, [x1, 28]
	strb	w3, [x21, 288]
	str	w3, [x21, 292]
	str	w6, [x21, 320]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x21, 2304]
	mov	w0, 0
	beq	.L235
.L232:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L234:
	ldr	x1, .LC28
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -20
	b	.L232
.L235:
	ldr	x1, .LC31
	bl	dprint_vfmw
	mov	w0, -20
	b	.L232
	.size	REAL9DEC_Init, .-REAL9DEC_Init
	.align	3
.LC28:
	.xword	.LC27
	.align	3
.LC29:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC31:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_Destroy
	.type	REAL9DEC_Destroy, %function
REAL9DEC_Destroy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, 52336
	ldr	x1, .LC33
	add	x2, x19, x0
	mov	w0, 2
	ldr	w2, [x2, 2444]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL9DEC_Destroy, .-REAL9DEC_Destroy
	.align	3
.LC33:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_Decode
	.type	REAL9DEC_Decode, %function
REAL9DEC_Decode:
	stp	x29, x30, [sp, -304]!
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
	str	xzr, [x29, 296]
	add	x0, x29, 168
	stp	xzr, xzr, [x0]
	add	x0, x29, 184
	stp	xzr, xzr, [x0]
	add	x0, x29, 200
	stp	xzr, xzr, [x0]
	add	x0, x29, 216
	stp	xzr, xzr, [x0]
	add	x0, x29, 232
	stp	xzr, xzr, [x0]
	add	x0, x29, 248
	stp	xzr, xzr, [x0]
	add	x0, x29, 264
	stp	xzr, xzr, [x0]
	add	x0, x29, 280
	stp	xzr, xzr, [x0]
	cbz	x20, .L378
	add	x22, x20, 53248
	add	x6, x29, 256
	mov	w0, 1
	mov	w4, 8192
	str	w0, [x29, 180]
	add	x1, x20, 16
	ldr	w3, [x22, 396]
	ldr	w2, [x22, 400]
	str	w0, [x22, 292]
	str	w4, [x22, 320]
	str	w3, [x22, 404]
	str	w2, [x22, 408]
	str	x1, [x29, 136]
	str	w4, [x29, 208]
	stp	w3, w2, [x6, 28]
	stp	w3, w2, [x6, 36]
	cbz	x19, .L379
	ldr	x27, .LC40
	mov	w1, 0
	mov	x2, 11356
	add	x0, x20, 16
	add	x23, x20, 8192
	ldr	x3, [x27, 96]
	blr	x3
	add	x1, x23, 3184
	add	x0, x1, 40960
	str	wzr, [x0, 2408]
	ldr	w2, [x19, 20]
	str	w2, [x0, 2428]
	ldr	w2, [x19, 16]
	str	w2, [x0, 2412]
	ldr	x2, [x19]
	str	x2, [x20, 11376]
	ldr	w2, [x19, 20]
	str	w2, [x0, 2416]
	ldrb	w3, [x19, 10]
	strb	w3, [x1, 8]
	ldrb	w3, [x19, 10]
	cmp	w3, 1
	beq	.L241
	ldr	w3, [x19, 104]
	str	w3, [x0, 2420]
	ldr	x3, [x19, 88]
	str	x3, [x1, 16]
	ldr	w3, [x19, 108]
	str	w3, [x0, 2424]
	ldrb	w0, [x19, 98]
	strb	w0, [x1, 9]
	ldrb	w0, [x19, 98]
	cmp	w0, 1
	bne	.L380
	mov	w0, 65525
	sub	w1, w2, #10
	movk	w0, 0x2f, lsl 16
	cmp	w1, w0
	bhi	.L244
.L243:
	ldr	x1, [x20, 11376]
	add	x21, x23, 3184
	cbz	x1, .L244
	add	x19, x22, 1656
	mov	x0, x19
	bl	BsInit
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w25, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	add	w0, w25, 1
	cmp	w25, 255
	add	x25, x21, 40960
	mov	w3, w0
	str	w0, [x25, 1380]
	bhi	.L244
	cbz	w0, .L245
	mov	w24, 0
	mov	w26, 3145727
	b	.L246
	.p2align 3
.L381:
	ldr	w3, [x25, 1380]
	cmp	w3, w24
	bls	.L245
.L246:
	mov	w1, 32
	mov	x0, x19
	bl	BsSkip
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	mov	w28, w0
	mov	w1, 32
	mov	x0, x19
	bl	BsSkip
	uxtw	x1, w24
	rev	w0, w28
	add	x1, x1, 8192
	cmp	w0, w26
	add	w24, w24, 1
	add	x1, x21, x1, lsl 2
	str	w0, [x1, 9576]
	ble	.L381
	.p2align 2
.L244:
	mov	w28, 0
.L367:
	mov	w0, w28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L380:
	ldr	w1, [x19, 24]
	mov	w28, 0
	ldr	w0, [x22, 2304]
	bl	SM_ReleaseStreamSeg
	ldr	w1, [x19, 112]
	ldr	w0, [x22, 2304]
	bl	SM_ReleaseStreamSeg
	mov	w0, w28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L241:
	str	wzr, [x0, 2420]
	str	xzr, [x1, 16]
	str	wzr, [x0, 2424]
	mov	w0, 65525
	strb	wzr, [x1, 9]
	movk	w0, 0x2f, lsl 16
	sub	w1, w2, #10
	cmp	w1, w0
	bls	.L243
	b	.L244
	.p2align 3
.L379:
	mov	x2, 52336
	ldr	x1, .LC39
	add	x20, x20, x2
	mov	w28, 0
	ldr	w2, [x20, 2444]
	bl	dprint_vfmw
	b	.L367
	.p2align 3
.L245:
	add	x2, x22, 472
	sub	w5, w3, #1
	mov	w1, 0
	add	x6, x23, 3184
	b	.L247
	.p2align 3
.L248:
	add	x0, x0, 8192
	ldr	w4, [x2], 4
	add	x0, x6, x0, lsl 2
	ldr	w0, [x0, 9576]
	cmp	w0, w4
	ble	.L244
.L247:
	cmp	w1, w5
	add	w0, w1, 1
	mov	x1, x0
	bne	.L248
	add	x25, x23, 3184
	lsl	w3, w3, 3
	add	x0, x25, 40960
	add	w21, w3, 1
	mov	w1, 65534
	movk	w1, 0x2f, lsl 16
	ldr	w26, [x0, 1384]
	add	w26, w21, w26
	sub	w2, w26, #1
	cmp	w2, w1
	mov	w1, 3145727
	ccmp	w21, w1, 0, ls
	bgt	.L244
	ldr	w2, [x0, 2416]
	sub	w2, w2, w26
	cmp	w2, wzr
	ble	.L244
	ldr	x1, [x20, 11376]
	mov	x0, x19
	add	x1, x1, x26, sxtw
	bl	BsInit
	add	x1, x29, 168
	mov	x0, x19
	bl	Real9_CB_GetPictureHeader
	cmp	w0, 1
	mov	w28, w0
	bne	.L382
	ldrb	w0, [x25, 28]
	cbz	w0, .L250
	ldr	w1, [x22, 312]
	ldr	w2, [x29, 200]
	cmp	w2, w1
	beq	.L383
.L250:
	ldr	x24, .LC43
	ldr	x4, [x24]
	cbz	x4, .L252
	ldr	w0, [x22, 308]
	mov	w3, 8
	strh	w0, [x29, 162]
	add	x2, x29, 160
	ldp	w0, w1, [x29, 196]
	strh	w1, [x29, 164]
	strh	w0, [x29, 166]
	ldr	w1, [x22, 312]
	ldr	w0, [x22, 2304]
	strh	w1, [x29, 160]
	mov	w1, 2
	blr	x4
.L252:
	ldr	w0, [x22, 2304]
	bl	FSP_GetFspType
	cbnz	w0, .L253
	add	x25, x29, 304
	ldr	w0, [x22, 2304]
	add	x2, x29, 156
	add	x1, x29, 152
	stp	wzr, wzr, [x29, 152]
	str	wzr, [x25, -144]!
	mov	x3, x25
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x20]
	ldr	w2, [x0, 772]
	cmp	w2, 1
	beq	.L384
.L253:
	add	x0, x23, 3184
	mov	w2, 1
	add	x25, x0, 40960
	mov	x1, x0
	ldr	w0, [x22, 2304]
	add	x24, x22, 1696
	str	x1, [x29, 128]
	ldr	w1, [x25, 2548]
	bl	FSP_ClearLogicFs
	ldr	w1, [x25, 2544]
	mov	w2, 1
	ldr	w0, [x22, 2304]
	bl	FSP_ClearLogicFs
	str	wzr, [x25, 2544]
	str	wzr, [x25, 2548]
	ldr	w0, [x22, 2304]
	bl	FSP_GetNullLogicFs
	str	w0, [x25, 2544]
	ldr	x1, [x29, 128]
	str	w0, [x25, 2548]
	strb	wzr, [x1, 25]
	mov	x1, x24
	ldr	w0, [x22, 2304]
	bl	FSP_ClearNotInVoQueue
	ldr	w2, [x29, 200]
	cmp	w2, 512
	bhi	.L385
	ldr	w0, [x29, 196]
	cmp	w0, 512
	mov	w3, w0
	bhi	.L260
	ldr	x1, [x20]
	ldr	w3, [x1, 772]
	cbnz	w3, .L262
	ldr	w1, [x1, 28]
	cmp	w1, 25
	beq	.L386
.L262:
	ldr	w0, [x22, 2304]
	bl	FSP_GetFspType
	cbz	w0, .L368
.L371:
	ldp	w0, w2, [x29, 196]
.L264:
	ldr	x1, .LC49
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	add	x2, x29, 168
	mov	x1, x20
	mov	w0, 6
	bl	Real9_ArrangeVHBMem
	cbz	w0, .L387
.L251:
	ldr	x3, [x27, 104]
	add	x0, x22, 280
	add	x1, x29, 168
	mov	x2, 136
	str	x0, [x29, 112]
	add	x25, x23, 3184
	blr	x3
	ldr	x0, [x20]
	ldr	w0, [x0, 8]
	strb	w0, [x25, 24]
	mov	x0, x20
	bl	Real9_GetImageBuffer
	cbz	w0, .L388
	add	x24, x25, 40960
	ldr	w0, [x22, 2304]
	ldr	w1, [x24, 2552]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L374
	ldr	x0, [x20]
	mov	x4, -1
	ldr	x1, .LC55
	ldr	x0, [x0, 64]
	str	x0, [x2, 584]
	mov	w0, 29
	ldr	x3, [x20]
	ldr	x3, [x3, 80]
	str	x3, [x2, 592]
	ldr	x3, [x20]
	ldr	x3, [x3, 96]
	str	x3, [x2, 600]
	ldr	x3, [x20]
	ldr	w3, [x3, 112]
	str	w3, [x2]
	ldr	x3, [x20]
	ldr	w3, [x3, 116]
	str	w3, [x2, 4]
	ldr	x3, [x20]
	ldr	w3, [x3, 120]
	str	w3, [x2, 8]
	ldr	x3, [x20]
	ldr	w3, [x3, 136]
	str	w3, [x2, 12]
	ldr	x3, [x20]
	str	x4, [x3, 64]
	ldr	x3, [x2, 592]
	ldr	x2, [x2, 584]
	bl	dprint_vfmw
	ldr	x0, [x29, 112]
	ldr	w0, [x0, 16]
	cmp	w0, 2
	beq	.L375
	cmp	w0, 1
	ldrb	w0, [x25, 25]
	beq	.L389
	cmp	w0, wzr
	mov	w0, 2
	csinc	w0, w0, wzr, ne
.L271:
	add	x25, x23, 3184
	strb	w0, [x23, 3209]
	add	x25, x25, 40960
	ldr	w2, [x25, 2544]
	ldr	w0, [x25, 2548]
	cmp	w2, w0
	beq	.L272
	ldr	x1, .LC57
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w0, [x22, 2304]
	mov	w2, 0
	ldr	w1, [x25, 2544]
	bl	FSP_SetRef
.L272:
	add	x0, x23, 3184
	mov	w2, 1
	add	x25, x0, 40960
	mov	x24, x0
	ldr	w1, [x25, 2552]
	ldr	w0, [x25, 2548]
	str	w0, [x25, 2544]
	str	w1, [x25, 2548]
	ldr	w0, [x22, 2304]
	bl	FSP_SetRef
	ldr	w0, [x22, 2304]
	ldr	w1, [x25, 2544]
	bl	FSP_RemovePmv
	ldr	x1, .LC59
	mov	w0, 13
	ldr	w2, [x25, 2552]
	bl	dprint_vfmw
	ldrb	w0, [x24, 24]
	cmp	w0, 4
	bne	.L274
	ldr	w0, [x22, 296]
	cbnz	w0, .L276
	str	wzr, [x25, 2560]
.L274:
	add	x0, x23, 3184
	add	x24, x0, 40960
	ldr	w0, [x22, 2304]
	ldr	w1, [x24, 2552]
	bl	FSP_GetLogicFs
	mov	x25, x0
	ldr	w1, [x24, 2544]
	ldr	w0, [x22, 2304]
	bl	FSP_GetLogicFs
	mov	x9, x0
	ldr	w1, [x24, 2548]
	ldr	w0, [x22, 2304]
	str	x9, [x29, 128]
	bl	FSP_GetLogicFs
	mov	x24, x0
	ldr	x9, [x29, 128]
	cmp	x25, xzr
	ccmp	x9, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L390
	ldr	x0, [x25, 32]
	cbz	x0, .L280
	ldr	x1, [x25, 40]
	cbz	x1, .L280
	ldr	x1, [x24, 32]
	cbz	x1, .L282
	ldr	w5, [x1, 8]
.L283:
	ldr	x0, [x29, 136]
	str	w5, [x0, 44]
	ldr	x0, [x9, 32]
	cbz	x0, .L391
.L372:
	ldr	x27, [x29, 136]
	ldr	w4, [x0, 8]
	ldr	x1, .LC66
	str	w4, [x27, 48]
	str	x9, [x29, 128]
	ldr	x0, [x25, 32]
	ldr	w2, [x0, 8]
	mov	w0, 13
	str	w2, [x27, 52]
	ldr	w6, [x25, 8]
	str	w6, [x27, 64]
	ldr	w7, [x24, 8]
	str	w7, [x27, 68]
	ldr	x3, [x25, 40]
	ldr	w3, [x3, 8]
	str	w3, [x27, 56]
	bl	dprint_vfmw
	ldr	x0, [x25, 40]
	ldr	x9, [x29, 128]
	ldr	w0, [x0, 24]
	str	w0, [x27, 60]
	add	x0, x23, 3184
	add	x0, x0, 40960
	ldr	x1, [x25, 40]
	ldr	w1, [x1, 24]
	str	w1, [x0, 2516]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 60]
	str	w0, [x27, 80]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 44]
	str	w0, [x27, 84]
	ldr	x0, [x25, 40]
	ldr	w0, [x0, 48]
	str	w0, [x27, 88]
	ldr	w0, [x22, 296]
	cmp	w0, 2
	beq	.L392
.L286:
	ldr	w0, [x22, 324]
	str	w0, [x25, 16]
	add	x0, x23, 3184
	add	x0, x0, 40960
	ldr	w3, [x22, 336]
	ldr	w2, [x22, 296]
	strb	w2, [x20, 16]
	mov	w4, w3
	ldr	x3, [x29, 136]
	cmp	w2, 2
	ldr	w2, [x22, 312]
	str	w4, [x29, 108]
	str	w2, [x3, 4]
	ldr	w1, [x22, 308]
	str	w1, [x3, 8]
	ldr	w1, [x0, 2468]
	str	w1, [x3, 12]
	ldr	w1, [x0, 2472]
	str	w1, [x3, 16]
	str	w4, [x3, 20]
	ldr	w1, [x0, 1372]
	str	w1, [x3, 24]
	ldr	w1, [x0, 1376]
	str	w1, [x3, 28]
	beq	.L291
	str	w4, [x0, 1372]
.L291:
	mov	x0, x19
	add	x25, x22, 416
	bl	BsPos
	asr	w1, w0, 31
	lsr	w1, w1, 29
	add	w0, w0, w1
	and	w0, w0, 7
	sub	w0, w0, w1
	add	x1, x23, 3184
	add	x1, x1, 40960
	str	w0, [x22, 436]
	ldr	w0, [x1, 1380]
	cmp	w0, 1
	beq	.L393
	ldr	w0, [x1, 1388]
	ldr	w1, [x1, 1384]
.L373:
	sub	w1, w0, w1
	mov	x0, x19
	lsl	w27, w1, 3
	bl	BsPos
	sub	w0, w27, w0
	add	x27, x23, 3184
	str	w0, [x25, 24]
	add	x25, x27, 40960
	mov	x0, x19
	ldr	w1, [x25, 2412]
	add	w26, w26, w1
	bl	BsPos
	cmp	w0, wzr
	add	w2, w0, 7
	add	x1, x22, 256
	ldr	w3, [x22, 340]
	csel	w0, w2, w0, lt
	ldr	w5, [x29, 108]
	mov	w7, 1
	str	w5, [x22, 416]
	add	w0, w26, w0, asr 3
	str	w3, [x22, 420]
	str	wzr, [x22, 428]
	ldr	x4, [x29, 136]
	stp	w0, wzr, [x1, 188]
	stp	wzr, wzr, [x1, 196]
	ldr	w2, [x22, 332]
	str	w2, [x22, 424]
	str	w0, [x4, 92]
	ldr	w0, [x22, 436]
	str	w0, [x4, 100]
	ldr	w0, [x22, 440]
	stp	wzr, w0, [x4, 104]
	str	w7, [x4, 32]
	str	wzr, [x4, 96]
	stp	wzr, w2, [x4, 112]
	str	w3, [x4, 120]
	str	wzr, [x4, 128]
	str	w5, [x4, 124]
	ldr	w0, [x25, 1380]
	cmp	w0, w7
	bls	.L311
	ldr	w6, [x25, 1388]
	mov	w0, 3145727
	add	w6, w21, w6
	cmp	w6, w0
	bgt	.L299
	cmp	w6, wzr
	ble	.L299
	ldr	w2, [x25, 2416]
	sub	w2, w2, w6
	cmp	w2, wzr
	ble	.L299
	mov	x26, x27
	str	w7, [x29, 104]
	mov	x27, x25
	str	w0, [x29, 120]
	add	x25, x29, 160
	b	.L302
	.p2align 3
.L303:
	ldr	w0, [x27, 1380]
	add	w7, w7, 1
	cmp	w0, w7
	bls	.L311
	uxtw	x0, w7
	add	x0, x0, 8192
	add	x0, x26, x0, lsl 2
	ldr	w6, [x0, 9576]
	ldr	w0, [x29, 120]
	add	w6, w21, w6
	cmp	w6, w0
	bgt	.L299
	cmp	w6, wzr
	ble	.L299
	ldr	w2, [x27, 2416]
	sub	w2, w2, w6
	cmp	w2, wzr
	ble	.L299
.L302:
	ldr	x1, [x26]
	mov	x0, x19
	stp	w7, w6, [x29, 124]
	add	x1, x1, x6, sxtw
	bl	BsInit
	ldr	x5, [x29, 112]
	add	x2, x29, 152
	mov	x4, x25
	add	x3, x29, 156
	mov	w1, 0
	mov	x0, x19
	bl	Real9_CB_GetSliceHeader
	cmp	w0, 1
	mov	w2, w0
	ldp	w7, w6, [x29, 124]
	bne	.L303
	ldr	w1, [x29, 152]
	ldr	w0, [x22, 312]
	str	w1, [x29, 128]
	cbz	w0, .L394
	ldr	w0, [x29, 160]
	add	x24, x22, 416
	ldr	w1, [x29, 108]
	cmp	w0, wzr
	str	w7, [x29, 100]
	csel	w0, w1, w0, lt
	str	w0, [x29, 108]
	mov	x0, x19
	str	w6, [x29, 124]
	bl	BsPos
	asr	w1, w0, 31
	lsr	w1, w1, 29
	ldr	w7, [x29, 100]
	add	w0, w0, w1
	ldr	w6, [x29, 124]
	and	w0, w0, 7
	sub	w0, w0, w1
	str	w0, [x22, 436]
	ldr	w0, [x27, 1380]
	sub	w0, w0, #1
	cmp	w0, w7
	beq	.L395
	cmp	w7, 254
	bhi	.L396
	add	w0, w7, 1
	uxtw	x1, w7
	add	x0, x0, 8192
	add	x1, x1, 8192
	stp	w6, w7, [x29, 96]
	add	x0, x26, x0, lsl 2
	add	x1, x26, x1, lsl 2
	ldr	w0, [x0, 9576]
	ldr	w1, [x1, 9576]
	sub	w1, w0, w1
	mov	x0, x19
	lsl	w1, w1, 3
	str	w1, [x29, 124]
	bl	BsPos
	ldr	w1, [x29, 124]
	ldp	w6, w7, [x29, 96]
	sub	w0, w1, w0
	str	w0, [x24, 24]
.L307:
	ldr	w2, [x27, 2412]
	mov	x0, x19
	str	w7, [x29, 100]
	add	w6, w6, w2
	str	w6, [x29, 124]
	bl	BsPos
	cmp	w0, wzr
	add	w3, w0, 7
	ldp	w6, w4, [x29, 124]
	csel	w0, w3, w0, lt
	str	w4, [x22, 428]
	add	w2, w6, w0, asr 3
	ldr	w0, [x29, 108]
	str	w0, [x22, 416]
	add	x0, x22, 256
	ldr	x6, [x29, 136]
	stp	w2, wzr, [x0, 188]
	stp	wzr, wzr, [x0, 196]
	ldr	w0, [x29, 104]
	sxtw	x3, w0
	add	w0, w0, 1
	mov	w5, w0
	cmp	w0, 131
	lsl	x0, x3, 2
	str	w5, [x29, 104]
	sub	x0, x0, x3
	lsl	x0, x0, 2
	sub	x0, x0, x3
	ldr	w3, [x22, 340]
	str	w3, [x22, 420]
	add	x0, x6, x0, lsl 2
	ldr	w3, [x22, 332]
	str	w3, [x22, 424]
	mov	x3, x6
	str	w2, [x0, 92]
	ldr	w2, [x22, 436]
	str	w2, [x0, 100]
	ldr	w2, [x22, 440]
	str	w2, [x0, 108]
	ldr	w2, [x22, 456]
	str	w2, [x0, 96]
	ldr	w2, [x22, 448]
	str	w2, [x0, 104]
	ldr	w2, [x22, 452]
	str	w2, [x0, 112]
	ldr	w2, [x22, 424]
	str	w2, [x0, 116]
	ldr	w2, [x22, 420]
	str	w2, [x0, 120]
	ldr	w2, [x22, 416]
	str	w2, [x0, 124]
	ldr	w1, [x22, 428]
	str	w1, [x0, 128]
	str	w5, [x3, 32]
	ldr	w7, [x29, 100]
	ble	.L303
	mov	x0, x20
	str	w7, [x29, 128]
	bl	Real9_ModifySliceMsg
	cmp	w0, 1
	ldr	w7, [x29, 128]
	bne	.L397
	ldr	x0, [x29, 136]
	str	x0, [x20, 8]
	b	.L303
.L386:
	ldr	x1, [x29, 128]
	ldrb	w1, [x1, 28]
	cbnz	w1, .L264
.L368:
	mov	x0, x24
	bl	ResetVoQueue
	b	.L371
	.p2align 3
.L378:
	ldr	x1, .LC37
	mov	w0, 1
	mov	w28, 0
	bl	dprint_vfmw
	b	.L367
.L382:
	ldr	x1, .LC42
	mov	w0, 1
	mov	w28, 0
	bl	dprint_vfmw
	b	.L367
.L385:
	ldr	w3, [x29, 196]
.L260:
	ldr	x1, .LC47
	mov	w0, 18
	mov	w28, 0
	bl	dprint_vfmw
	b	.L367
.L388:
	add	x25, x25, 40960
	ldr	x1, .LC53
	mov	w28, 0
	ldr	w2, [x25, 2444]
	bl	dprint_vfmw
	b	.L367
.L384:
	ldr	w0, [x29, 160]
	cmp	w0, wzr
	bgt	.L256
	ldr	w0, [x29, 156]
	cmp	w0, 32
	bgt	.L256
	ldr	x0, [x20, 8]
	cbnz	x0, .L256
	ldr	w3, [x22, 1528]
	cbz	w3, .L253
	ldr	w4, [x22, 312]
	cbz	w4, .L253
	ldr	w1, [x22, 2308]
	ldr	w7, [x29, 196]
	cmp	w7, w1
	beq	.L253
	ldr	w1, [x22, 2312]
	ldr	w6, [x29, 200]
	cmp	w6, w1
	beq	.L253
	ldr	x1, .LC45
	mov	w0, w2
	ldr	w5, [x22, 308]
	bl	dprint_vfmw
	ldr	w0, [x29, 196]
	str	w0, [x22, 2308]
	ldr	x4, [x24]
	ldr	w0, [x29, 200]
	str	w0, [x22, 2312]
	cbz	x4, .L253
	ldr	w0, [x22, 2304]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L253
	.p2align 3
.L383:
	ldr	w0, [x22, 308]
	ldr	w1, [x29, 196]
	cmp	w1, w0
	bne	.L250
	b	.L251
.L387:
	ldr	x1, .LC51
	mov	w0, 1
	mov	w28, 0
	bl	dprint_vfmw
	b	.L367
.L299:
	add	x1, x23, 3184
	ldr	w0, [x22, 2304]
	add	x1, x1, 40960
	mov	w2, 1
	mov	w28, 0
	ldr	w1, [x1, 2552]
	bl	FSP_ClearLogicFs
	b	.L367
.L375:
	ldrb	w0, [x25, 25]
	cmp	w0, 1
	bls	.L374
	ldrb	w0, [x25, 24]
	cmp	w0, 4
	bne	.L274
.L315:
	add	x0, x23, 3184
	add	x0, x0, 40960
	ldr	w1, [x0, 2560]
	cbnz	w1, .L274
	ldr	w1, [x0, 2552]
	mov	w2, 1
	ldr	w0, [x22, 2304]
	mov	w28, 0
	bl	FSP_ClearLogicFs
	b	.L367
.L256:
	mov	w28, -2
	b	.L367
.L390:
	ldr	x2, .LC60
	mov	w3, 1896
	ldr	x1, .LC62
	mov	w0, 0
	mov	w28, 0
	bl	dprint_vfmw
	b	.L367
.L389:
	cbz	w0, .L244
	mov	w0, 2
	b	.L271
.L395:
	uxtw	x0, w7
	add	x0, x0, 8192
	stp	w6, w7, [x29, 96]
	add	x0, x26, x0, lsl 2
	ldr	w1, [x0, 9576]
	ldr	w0, [x27, 2416]
	sub	w0, w0, w21
	sub	w1, w0, w1
	mov	x0, x19
	lsl	w1, w1, 3
	str	w1, [x29, 124]
	bl	BsPos
	ldr	w1, [x29, 124]
	ldp	w6, w7, [x29, 96]
	sub	w0, w1, w0
	str	w0, [x24, 24]
	b	.L307
.L280:
	add	x1, x23, 3184
	ldr	w0, [x22, 2304]
	add	x1, x1, 40960
	mov	w2, 1
	mov	w28, 0
	ldr	w1, [x1, 2552]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC64
	mov	w0, 0
	bl	dprint_vfmw
	b	.L367
.L276:
	cmp	w0, 2
	beq	.L315
	cmp	w0, 1
	bne	.L274
	str	w0, [x25, 2560]
	b	.L274
.L374:
	ldr	w0, [x22, 2304]
	mov	w2, 1
	ldr	w1, [x24, 2552]
	mov	w28, 0
	bl	FSP_ClearLogicFs
	b	.L367
.L311:
	ldr	x0, [x29, 136]
	mov	w19, 1
	str	w19, [x0, 36]
	ldr	x3, [x20, 8]
	cbz	x3, .L398
	ldr	x0, [x20]
	ldr	w1, [x0, 952]
	cmp	w1, 1
	beq	.L316
.L313:
	cmp	w1, 2
	beq	.L399
.L314:
	ldr	w1, [x0, 640]
	str	w1, [x20, 88]
	ldr	w0, [x0, 692]
	str	w0, [x20, 92]
	b	.L367
.L393:
	ldr	w0, [x1, 2416]
	ldr	w1, [x1, 1384]
	sub	w0, w0, w21
	b	.L373
.L391:
	ldr	x0, [x25, 32]
	b	.L372
.L282:
	ldr	w5, [x0, 8]
	b	.L283
.L392:
	ldr	w3, [x9, 16]
	ldr	w1, [x22, 324]
	ldr	w0, [x24, 16]
	subs	w1, w1, w3
	sub	w0, w0, w3
	bmi	.L400
.L287:
	tbnz	w0, #31, .L401
.L288:
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w0, wzr
	ble	.L319
	sub	w3, w0, w1
	lsl	w4, w1, 14
	lsl	w3, w3, 14
	sdiv	w4, w4, w0
	sdiv	w3, w3, w0
.L290:
	add	x2, x23, 3184
	add	x2, x2, 40960
	add	x5, x2, 2304
	stp	w1, w0, [x5, 156]
	stp	w4, w3, [x5, 164]
	b	.L286
.L400:
	ldr	w2, [x22, 320]
	add	w1, w1, w2
	b	.L287
.L319:
	mov	w3, 0
	mov	w4, 0
	b	.L290
.L401:
	ldr	w2, [x22, 320]
	add	w0, w0, w2
	b	.L288
.L397:
	ldr	w0, [x22, 2304]
	mov	w2, 1
	ldr	w1, [x27, 2552]
	mov	w28, 0
	bl	FSP_ClearLogicFs
	b	.L367
.L396:
	ldr	x1, .LC68
	mov	w2, 2122
	mov	w0, 22
	mov	w28, 0
	bl	dprint_vfmw
	b	.L367
.L394:
	add	x10, x26, 40960
	ldr	w0, [x22, 2304]
	mov	w28, 0
	ldr	w1, [x10, 2552]
	bl	FSP_ClearLogicFs
	b	.L367
.L399:
	ldr	w1, [x0, 956]
	cmp	w1, wzr
	ble	.L314
	ldr	x1, [x20, 8]
	cbz	x1, .L314
	ldrb	w1, [x1]
	cmp	w1, 2
	bne	.L314
	str	xzr, [x20, 8]
	mov	w2, 0
	mov	w28, 0
	ldr	w1, [x22, 1640]
	ldr	w0, [x22, 2304]
	bl	FSP_SetDisplay
	ldr	x3, [x20]
	mov	x1, x20
	mov	w0, 9
	ldr	w2, [x3, 956]
	sub	w2, w2, #1
	str	w2, [x3, 956]
	bl	ReleasePacket
	b	.L367
.L398:
	mov	x0, x20
	bl	Real9_ModifySliceMsg
	cmp	w0, 1
	bne	.L402
	ldr	x0, [x20]
	ldr	x2, [x29, 136]
	str	x2, [x20, 8]
	ldr	w1, [x0, 952]
	cmp	w1, 1
	bne	.L313
	cbz	x2, .L314
	mov	x3, x2
.L316:
	ldrb	w1, [x3]
	cmp	w1, 2
	bne	.L314
	str	xzr, [x20, 8]
	mov	w2, 0
	mov	w28, 0
	ldr	w1, [x22, 1640]
	ldr	w0, [x22, 2304]
	bl	FSP_SetDisplay
	mov	x1, x20
	mov	w0, 9
	bl	ReleasePacket
	b	.L367
.L402:
	add	x1, x23, 3184
	ldr	w0, [x22, 2304]
	add	x1, x1, 40960
	mov	w2, w19
	mov	w28, 0
	ldr	w1, [x1, 2552]
	bl	FSP_ClearLogicFs
	b	.L367
	.size	REAL9DEC_Decode, .-REAL9DEC_Decode
	.align	3
.LC37:
	.xword	.LC36
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC40:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC43:
	.xword	g_event_report
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
.LC51:
	.xword	.LC50
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
	.align	3
.LC60:
	.xword	.LANCHOR1
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_RecycleImage
	.type	REAL9DEC_RecycleImage, %function
REAL9DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L405
	add	x19, x19, 53248
	mov	w2, 0
	mov	w1, w20
	ldr	w0, [x19, 2304]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 2304]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L405:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL9DEC_RecycleImage, .-REAL9DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_GetRemainImg
	.type	REAL9DEC_GetRemainImg, %function
REAL9DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L421
	ldr	x0, [x19]
	add	x20, x19, 53248
	ldr	w0, [x0, 24]
	cmp	w0, 1
	beq	.L409
	mov	x21, 52336
	add	x20, x19, 53248
	add	x21, x19, x21
	ldr	w0, [x20, 2304]
	ldr	w1, [x21, 2548]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L409
	ldr	w0, [x20, 2304]
	ldr	w1, [x21, 2548]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L422
.L409:
	add	x22, x20, 1696
.L412:
	mov	x0, x22
	bl	GetVoLastImageID
.L418:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L422:
	mov	x0, x19
	add	x22, x20, 1696
	bl	Real9_SetImgFormat
	mov	w2, 1
	str	w2, [x23, 180]
	ldr	w0, [x20, 2304]
	ldr	w1, [x21, 2548]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 2304]
	mov	x4, x23
	mov	x3, x22
	mov	x2, x19
	mov	w1, 9
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L410
	ldr	w0, [x20, 2304]
	mov	w2, 0
	ldr	w1, [x21, 2548]
	bl	FSP_SetDisplay
	b	.L412
	.p2align 3
.L410:
	ldr	w0, [x23, 152]
	cmp	w0, 100
	bhi	.L409
	ldr	w0, [x23, 68]
	cmp	w0, 31
	bls	.L409
	ldr	w1, [x23, 72]
	mov	w0, 0
	cmp	w1, 31
	bhi	.L418
	b	.L412
	.p2align 3
.L421:
	ldr	x1, .LC69
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L418
	.size	REAL9DEC_GetRemainImg, .-REAL9DEC_GetRemainImg
	.align	3
.LC69:
	.xword	.LC36
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_VDMPostProc
	.type	REAL9DEC_VDMPostProc, %function
REAL9DEC_VDMPostProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	mov	w24, w2
	bl	_mcount
	cbz	x20, .L448
	ldr	x1, .LC72
	mov	w2, w22
	mov	w0, 22
	add	x21, x20, 53248
	add	x19, x20, 8192
	bl	dprint_vfmw
	add	x25, x19, 3184
	ldr	x2, [x20, 8]
	mov	x1, x20
	mov	w0, 9
	add	x23, x25, 40960
	ldrb	w3, [x2, 1]
	strb	w3, [x21, 280]
	ldr	w2, [x2, 72]
	str	w2, [x21, 284]
	bl	ReleasePacket
	ldr	w0, [x21, 2304]
	ldr	w1, [x23, 2552]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L433
	ldr	w1, [x23, 1208]
	strb	w1, [x19, 3210]
	cmp	w1, 2
	beq	.L426
	and	w24, w24, 31
	str	w24, [x23, 1376]
.L426:
	tbnz	w22, #31, .L434
	mov	w1, 100
	cmp	w22, w1
	csel	w22, w22, w1, le
.L427:
	ldr	x1, .LC74
	str	w22, [x0, 152]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	Real9_SetImgFormat
	ldrb	w1, [x19, 3208]
	add	x0, x19, 3184
	cmp	w1, 2
	beq	.L430
	ldr	x1, [x20]
	ldr	w1, [x1, 24]
	cbnz	w1, .L430
	add	x1, x0, 40960
	ldr	w2, [x1, 1208]
	cmp	w2, 2
	beq	.L430
	ldrb	w0, [x0, 25]
	cmp	w0, 1
	bls	.L435
	ldr	w1, [x1, 2544]
.L431:
	add	x0, x19, 3184
	cmn	w1, #1
	add	x0, x0, 40960
	str	w1, [x0, 2556]
	beq	.L432
.L450:
	add	x22, x19, 3184
	ldr	w0, [x21, 2304]
	add	x22, x22, 40960
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	ldr	w23, [x22, 2556]
	ldr	w0, [x21, 2304]
	mov	w1, w23
	bl	FSP_GetRef
	mov	w3, w0
	ldr	x1, .LC76
	mov	w2, w23
	mov	w0, 12
	bl	dprint_vfmw
	ldr	w0, [x21, 2304]
	mov	w2, 1
	ldr	w1, [x22, 2556]
	bl	FSP_SetDisplay
	ldr	w0, [x21, 2304]
	mov	x4, x24
	add	x3, x21, 1696
	mov	x2, x20
	mov	w1, 9
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L449
.L432:
	add	x19, x19, 3184
	mov	w0, 1
	add	x19, x19, 40960
	ldr	w1, [x19, 2444]
	add	w1, w1, w0
	str	w1, [x19, 2444]
.L425:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L430:
	add	x0, x19, 3184
	add	x0, x0, 40960
	ldr	w1, [x0, 2552]
	str	w1, [x0, 2556]
	cmn	w1, #1
	bne	.L450
	b	.L432
	.p2align 3
.L434:
	mov	w22, 0
	b	.L427
	.p2align 3
.L449:
	ldr	w0, [x21, 2304]
	mov	w2, 0
	ldr	w1, [x22, 2556]
	bl	FSP_SetDisplay
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L435:
	mov	w1, -1
	b	.L431
	.p2align 3
.L448:
	ldr	x1, .LC70
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
.L433:
	mov	w0, 0
	b	.L425
	.size	REAL9DEC_VDMPostProc, .-REAL9DEC_VDMPostProc
	.align	3
.LC70:
	.xword	.LC36
	.align	3
.LC72:
	.xword	.LC71
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_GetImageBuffer
	.type	REAL9DEC_GetImageBuffer, %function
REAL9DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L458
	add	x19, x19, 53248
	ldr	w0, [x19, 2304]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w20, w0
	beq	.L453
	ldr	w0, [x19, 2304]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L459
.L453:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L459:
	ldr	w0, [x19, 2304]
	add	x1, x19, 1696
	bl	FSP_ClearNotInVoQueue
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L458:
	ldr	x1, .LC77
	mov	w0, 1
	mov	w20, 0
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL9DEC_GetImageBuffer, .-REAL9DEC_GetImageBuffer
	.align	3
.LC77:
	.xword	.LC36
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL9DEC_Support
	.type	REAL9DEC_Support, %function
REAL9DEC_Support:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L463
	mov	w0, 1
	str	w0, [x19]
.L460:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L463:
	ldr	x1, .LC79
	mov	w0, 1
	bl	dprint_vfmw
	b	.L460
	.size	REAL9DEC_Support, .-REAL9DEC_Support
	.align	3
.LC79:
	.xword	.LC78
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	gs_VLCDecodeTable, %object
	.size	gs_VLCDecodeTable, 256
gs_VLCDecodeTable:
	.byte	-128
	.byte	-127
	.byte	112
	.byte	112
	.byte	-126
	.byte	-125
	.byte	113
	.byte	113
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	-124
	.byte	-123
	.byte	114
	.byte	114
	.byte	-122
	.byte	-121
	.byte	115
	.byte	115
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	-120
	.byte	-119
	.byte	116
	.byte	116
	.byte	-118
	.byte	-117
	.byte	117
	.byte	117
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	-116
	.byte	-115
	.byte	118
	.byte	118
	.byte	-114
	.byte	-113
	.byte	119
	.byte	119
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.type	MBA_FieldWidth, %object
	.size	MBA_FieldWidth, 24
MBA_FieldWidth:
	.word	6
	.word	7
	.word	9
	.word	11
	.word	13
	.word	14
.LC0:
	.word	160
	.word	176
	.word	240
	.word	320
	.word	352
	.word	640
	.word	704
	.word	0
.LC1:
	.word	120
	.word	132
	.word	144
	.word	240
	.word	288
	.word	480
	.word	0
	.word	0
	.type	GetBitsMask, %object
	.size	GetBitsMask, 100
GetBitsMask:
	.word	0
	.word	1
	.word	3
	.word	7
	.word	15
	.word	31
	.word	63
	.word	127
	.word	255
	.word	511
	.word	1023
	.word	2047
	.word	4095
	.word	8191
	.word	16383
	.word	32767
	.word	65535
	.word	131071
	.word	262143
	.word	524287
	.word	1048575
	.word	2097151
	.word	4194303
	.word	8388607
	.word	16777215
	.align	3
.LANCHOR1 = . + 0
	.type	__FUNCTION__.11709, %object
	.size	__FUNCTION__.11709, 16
__FUNCTION__.11709:
	.string	"REAL9DEC_Decode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC3:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC5:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC7:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC9:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC11:
	ASCII(.string	"image size abnormal (%dx%d) in MB\n" )
	.zero	5
.LC13:
	ASCII(.string	"real9 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
.LC16:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC27:
	ASCII(.string	"ERROR: Invalid packet pointer!\n" )
.LC30:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC32:
	ASCII(.string	"Decoding quits at frm %d\n" )
	.zero	6
.LC36:
	ASCII(.string	"pCtx is NULL!\n" )
	.zero	1
.LC38:
	ASCII(.string	"ERROR: frm %d, Invalid packet pointer!\n" )
.LC41:
	ASCII(.string	"Real9_CB_GetPictureHeader Error!\n" )
	.zero	6
.LC44:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC46:
	ASCII(.string	"pic width/height to large,MbWidth = %d, MbHeight = %d" )
	.zero	2
.LC48:
	ASCII(.string	"new seq size %d * %d\n" )
	.zero	2
.LC50:
	ASCII(.string	"Real9_ArrangeVHBMem err\n" )
	.zero	7
.LC52:
	ASCII(.string	"Fatal Error: frm%d, get image buffer failed\n" )
	.zero	3
.LC54:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.zero	2
.LC56:
	ASCII(.string	"---------- unref %d\n" )
	.zero	3
.LC58:
	ASCII(.string	"++++++++++ ref %d\n" )
	.zero	5
.LC61:
	ASCII(.string	"CurFsID abnormal!,%s %d (NULL == pCur) || (NULL == pFwd) || (NULL == pBwd)!!\n" )
	.zero	2
.LC63:
	ASCII(.string	"CurFsID abnormal!\n" )
	.zero	5
.LC65:
	ASCII(.string	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p,%p,%p,%p,%p\n" )
.LC67:
	ASCII(.string	"line:%d! i > (RV9_MAX_SLC_PARAM_NUM - 2)\n" )
	.zero	6
.LC71:
	ASCII(.string	"ErrRatio = %d\n" )
	.zero	1
.LC73:
	ASCII(.string	"DEBUG: DEC over\n" )
	.zero	7
.LC75:
	ASCII(.string	"insert buf %d ref %d\n" )
	.zero	2
.LC78:
	ASCII(.string	"flag is NULL!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
