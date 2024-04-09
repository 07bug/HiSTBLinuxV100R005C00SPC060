#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"real8.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetBits
	.type	Real8_CB_GetBits, %function
Real8_CB_GetBits:
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
	.size	Real8_CB_GetBits, .-Real8_CB_GetBits
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_Get1Bit
	.type	Real8_CB_Get1Bit, %function
Real8_CB_Get1Bit:
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
	.size	Real8_CB_Get1Bit, .-Real8_CB_Get1Bit
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetVLCBits
	.type	Real8_CB_GetVLCBits, %function
Real8_CB_GetVLCBits:
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
	ldr	x22, .LC3
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
	.size	Real8_CB_GetVLCBits, .-Real8_CB_GetVLCBits
	.align	3
.LC3:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_GetImageBuffer
	.type	Real8_GetImageBuffer, %function
Real8_GetImageBuffer:
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
	ldr	w0, [x21, 2328]
	bl	FSP_NewLogicFs
	str	w0, [x20, 2576]
	mov	w1, w0
	tbnz	w0, #31, .L14
	ldr	w0, [x21, 2328]
	bl	FSP_GetLogicFs
	mov	x19, x0
	cbz	x0, .L15
	ldr	x1, .LC9
	mov	w0, 18
	ldr	w2, [x20, 2576]
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	cbz	x0, .L13
	ldr	x1, [x19, 40]
	cbz	x1, .L13
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC11
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
	ldr	x1, .LC5
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 2572]
	mov	w2, 1
	ldr	w0, [x21, 2328]
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 2568]
	mov	w2, 1
	ldr	w0, [x21, 2328]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 2568]
	str	wzr, [x20, 2572]
	ldr	w0, [x21, 2328]
	bl	FSP_GetNullLogicFs
	str	w0, [x20, 2568]
	str	w0, [x20, 2572]
	add	x1, x21, 1720
	strb	wzr, [x19, 23]
	ldr	w0, [x21, 2328]
	bl	FSP_ClearNotInVoQueue
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L15:
	ldr	x1, .LC7
	mov	w2, 516
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L10
	.size	Real8_GetImageBuffer, .-Real8_GetImageBuffer
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_ArrangeVHBMem
	.type	Real8_ArrangeVHBMem, %function
Real8_ArrangeVHBMem:
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
	ldp	w3, w2, [x19, 112]
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
	ldp	w23, w22, [x19, 104]
	mov	w25, 5
	mov	w21, 2
	mov	w24, 4
.L28:
	ldr	x0, .LC16
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 88
	blr	x3
	ldr	x0, [x20]
	ldp	w1, w2, [x19, 104]
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
	ldr	w0, [x19, 2328]
	bl	FSP_ConfigInstance
	mov	w2, 0
	cbnz	w0, .L43
	ldr	x1, [x20]
	add	x3, x29, 84
	ldr	w0, [x19, 2328]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L49
	cbnz	w0, .L36
	add	x20, x20, 8192
	mov	w0, 1
	mov	w2, 1
	strb	w0, [x20, 3204]
	b	.L43
	.p2align 3
.L18:
	ldr	x1, .LC13
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
	ldp	w3, w2, [x19, 104]
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
	ldr	x1, .LC15
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
	.p2align 3
.L48:
	ldr	w22, [x0, 732]
	ldp	w3, w2, [x19, 104]
	cmp	w2, w22
	bhi	.L50
	ldr	w23, [x0, 736]
	cmp	w3, w23
	bhi	.L51
	add	x1, x20, 8192
	ldrb	w2, [x1, 3204]
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
	add	x0, x19, 1720
	bl	ResetVoQueue
.L36:
	ldr	x1, .LC18
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
	.p2align 3
.L51:
	mov	w5, w23
.L24:
	ldr	x1, .LC15
	mov	w4, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w2, 0
	b	.L43
.L50:
	ldr	w5, [x0, 736]
	b	.L24
	.size	Real8_ArrangeVHBMem, .-Real8_ArrangeVHBMem
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC16:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC18:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetCPFMT
	.type	Real8_CB_GetCPFMT, %function
Real8_CB_GetCPFMT:
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
	str	w20, [x21, 108]
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
	str	w22, [x21, 104]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real8_CB_GetCPFMT, .-Real8_CB_GetCPFMT
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_SetDimensions
	.type	Real8_CB_SetDimensions, %function
Real8_CB_SetDimensions:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x1, 96
	ldr	x0, [x19, 104]
	movk	x1, 0x80, lsl 32
	cmp	x0, x1
	beq	.L72
	mov	x1, 144
	movk	x1, 0xb0, lsl 32
	cmp	x0, x1
	beq	.L73
	mov	x1, 288
	movk	x1, 0x160, lsl 32
	cmp	x0, x1
	beq	.L74
	mov	x1, 576
	movk	x1, 0x2c0, lsl 32
	cmp	x0, x1
	beq	.L75
	mov	x1, 1152
	movk	x1, 0x580, lsl 32
	cmp	x0, x1
	beq	.L76
	ldr	w0, [x19, 108]
	add	x1, x19, 16
	mov	w2, 6
	add	w0, w0, 15
	lsr	w0, w0, 4
	str	w0, [x1, 28]
	ldr	w3, [x19, 104]
	add	w3, w3, 15
	lsr	w3, w3, 4
	str	w3, [x1, 24]
	mul	w0, w0, w3
	sub	w0, w0, #1
	cmp	w0, 47
	bls	.L58
	cmp	w0, 98
	bls	.L67
	cmp	w0, 395
	bls	.L68
	cmp	w0, 1583
	bls	.L69
.L71:
	mov	w3, 6335
	mov	w2, 14
	cmp	w0, w3
	bhi	.L58
	mov	w2, 4
	b	.L60
	.p2align 3
.L72:
	add	x1, x19, 16
	mov	w0, 6
	mov	w3, 8
	mov	w2, w0
	stp	w0, w3, [x1, 24]
.L58:
	str	w2, [x1, 32]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L73:
	add	x1, x19, 16
	mov	w3, 11
	mov	w0, 9
	mov	w2, 1
	stp	w0, w3, [x1, 24]
.L60:
	ldr	x0, .LC19
	add	x0, x0, 256
	ldr	w2, [x0, w2, uxtw 2]
	str	w2, [x1, 32]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L74:
	add	x1, x19, 16
	mov	w2, 22
	mov	w0, 18
	stp	w0, w2, [x1, 24]
.L68:
	mov	w2, 2
	b	.L60
	.p2align 3
.L76:
	add	x1, x19, 16
	mov	w3, 88
	mov	w2, 72
	mov	w0, 6335
	stp	w2, w3, [x1, 24]
	b	.L71
	.p2align 3
.L75:
	add	x1, x19, 16
	mov	w2, 44
	mov	w0, 36
	stp	w0, w2, [x1, 24]
.L69:
	mov	w2, 3
	b	.L60
.L67:
	mov	w2, 1
	b	.L60
	.size	Real8_CB_SetDimensions, .-Real8_CB_SetDimensions
	.align	3
.LC19:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetPicSize
	.type	Real8_CB_GetPicSize, %function
Real8_CB_GetPicSize:
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
	ldr	x0, .LC21
	mov	w3, 180
	ldr	w1, [x20, 36]
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
	ldr	w0, [x20, 68]
	str	w0, [x24]
	ldr	w0, [x20, 72]
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
	.size	Real8_CB_GetPicSize, .-Real8_CB_GetPicSize
	.align	3
.LC21:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_FindNextSliceStartCode
	.type	Real8_CB_FindNextSliceStartCode, %function
Real8_CB_FindNextSliceStartCode:
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
	sub	w21, w21, #2
	cmp	w21, wzr
	bgt	.L100
	b	.L97
	.p2align 3
.L103:
	bl	BsSkip
	cmp	w19, w21
	beq	.L97
.L100:
	mov	w1, 17
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	mov	w2, w0
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L103
	mov	w0, w2
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L97:
	mov	w2, 0
	ldr	x21, [sp, 32]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	Real8_CB_FindNextSliceStartCode, .-Real8_CB_FindNextSliceStartCode
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_SearchBits_IgnoreOnly0
	.type	Real8_CB_SearchBits_IgnoreOnly0, %function
Real8_CB_SearchBits_IgnoreOnly0:
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
	beq	.L105
	tst	w22, w19
	bne	.L105
	ldr	x0, .LC24
	mov	w20, 0
	add	x0, x0, 344
	ldr	w25, [x0, w25, uxtw 2]
	b	.L106
	.p2align 3
.L107:
	tst	w22, w19
	bne	.L105
.L106:
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
	bhi	.L107
.L105:
	cmp	w23, w19
	ldr	x25, [sp, 64]
	cset	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	Real8_CB_SearchBits_IgnoreOnly0, .-Real8_CB_SearchBits_IgnoreOnly0
	.align	3
.LC24:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_SetRPRSizes
	.type	Real8_CB_SetRPRSizes, %function
Real8_CB_SetRPRSizes:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	ldr	x0, .LC26
	add	x6, x29, 56
	add	x1, x29, 96
	str	x21, [x19, 24]
	add	x0, x0, 448
	add	x1, x1, x20, uxtw 2
	str	w20, [x19, 32]
	ldp	x4, x5, [x0]
	stp	x4, x5, [x6]
	add	x4, x29, 72
	ldp	x2, x3, [x0, 16]
	ldr	w0, [x0, 32]
	stp	x2, x3, [x4]
	str	w0, [x29, 88]
	ldr	w0, [x1, -40]
	str	w0, [x19, 20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.size	Real8_CB_SetRPRSizes, .-Real8_CB_SetRPRSizes
	.align	3
.LC26:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetSSC
	.type	Real8_CB_GetSSC, %function
Real8_CB_GetSSC:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	Real8_CB_FindNextSliceStartCode
	cmp	w0, wzr
	cset	w0, ne
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_CB_GetSSC, .-Real8_CB_GetSSC
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetSliceHeader
	.type	Real8_CB_GetSliceHeader, %function
Real8_CB_GetSliceHeader:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x5
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	mov	x22, x2
	mov	x24, x3
	mov	x23, x4
	bl	_mcount
	ldr	w0, [x19, 96]
	cmp	w0, 1
	beq	.L148
	cbz	w21, .L149
	str	wzr, [x22]
	mov	w0, -1
	mov	w19, 1
	str	w0, [x23]
.L139:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L148:
	cbnz	w21, .L150
	add	x21, x19, 16
	mov	w1, 3
	mov	x0, x20
	ldr	w26, [x21, 40]
	bl	BsShow
	mov	w25, w0
	mov	w1, 3
	mov	x0, x20
	bl	BsSkip
	cmp	w25, 7
	bhi	.L119
	ldr	x0, .LC28
	add	x0, x0, 488
	ldr	w0, [x0, w25, uxtw 2]
	cmp	w0, 2
	bhi	.L119
	cmn	w26, #1
	mov	w1, 2
	mov	x0, x20
	beq	.L151
	bl	BsShow
	mov	w25, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	ldr	w0, [x21, 36]
	cmp	w0, w25
	bne	.L119
.L121:
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	cbnz	w25, .L119
	mov	w1, 5
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 5
	mov	x0, x20
	bl	BsSkip
	uxtb	w0, w25
	strb	w0, [x21, 2]
	cmp	w0, 31
	bhi	.L119
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	cmp	w25, wzr
	mov	w1, 13
	cset	w0, ne
	cmn	w26, #1
	strb	w0, [x21, 1]
	mov	x0, x20
	bne	.L122
	bl	BsShow
	mov	w26, w0
	mov	w1, 13
	mov	x0, x20
	bl	BsSkip
	ldr	w25, [x21, 4]
	str	w26, [x21, 44]
	cbz	w25, .L140
	mov	w1, w25
	mov	x0, x20
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	str	w26, [x21, 56]
	ldr	x1, [x21, 8]
	cbz	x1, .L119
	lsl	w26, w26, 1
	mov	x0, x19
	add	w3, w26, 1
	ldr	w2, [x1, w26, uxtw 2]
	ldr	w1, [x1, w3, uxtw 2]
	stp	w2, w1, [x21, 60]
	stp	w1, w2, [x19, 104]
	bl	Real8_CB_SetDimensions
.L140:
	ldr	w25, [x21, 32]
	mov	x0, x20
	mov	w1, w25
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	str	w26, [x21, 40]
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	strb	w25, [x19, 16]
	b	.L116
	.p2align 3
.L149:
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w21, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	cmp	w21, 1
	beq	.L152
.L119:
	mov	w19, 0
.L153:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L150:
	add	x21, x19, 16
.L116:
	ldr	w0, [x21, 40]
	mov	w19, 1
	str	w0, [x22]
	ldrb	w0, [x21, 2]
	str	w0, [x23]
	mov	w0, w19
	str	wzr, [x24]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L152:
	ldr	w25, [x19, 48]
	mov	x0, x20
	mov	w1, w25
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	str	w26, [x22]
	ldr	w0, [x19, 48]
	cmp	w0, 11
	bls	.L132
	mov	w1, w21
	mov	x0, x20
	bl	BsShow
	mov	w19, w0
	mov	w1, w21
	mov	x0, x20
	bl	BsSkip
	cmp	w19, 1
	bne	.L119
.L132:
	mov	w1, 5
	mov	x0, x20
	bl	BsShow
	mov	w19, w0
	mov	w1, 5
	mov	x0, x20
	bl	BsSkip
	str	w19, [x23]
	cmp	w19, 31
	bgt	.L119
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w19, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	cmp	w19, 1
	bne	.L119
	mov	w1, 2
	mov	x0, x20
	bl	BsShow
	mov	w21, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	str	w21, [x24]
	b	.L139
	.p2align 3
.L151:
	bl	BsShow
	mov	w25, w0
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	str	w25, [x21, 36]
	b	.L121
.L122:
	bl	BsShow
	mov	w25, w0
	mov	w1, 13
	mov	x0, x20
	bl	BsSkip
	ldr	w0, [x21, 44]
	cmp	w0, w25
	bne	.L119
	ldr	w25, [x21, 4]
	cbz	w25, .L144
	mov	w1, w25
	mov	x0, x20
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	ldr	w0, [x21, 56]
	cmp	w0, w26
	bne	.L119
.L144:
	ldr	w25, [x21, 32]
	mov	x0, x20
	mov	w1, w25
	bl	BsShow
	mov	w26, w0
	mov	w1, w25
	mov	x0, x20
	bl	BsSkip
	str	w26, [x21, 40]
	mov	w1, 1
	mov	x0, x20
	bl	BsShow
	mov	w25, w0
	mov	w1, 1
	mov	x0, x20
	bl	BsSkip
	ldrb	w0, [x19, 16]
	cmp	w0, w25
	beq	.L116
	mov	w19, 0
	b	.L153
	.size	Real8_CB_GetSliceHeader, .-Real8_CB_GetSliceHeader
	.align	3
.LC28:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_CB_GetPictureHeader
	.type	Real8_CB_GetPictureHeader, %function
Real8_CB_GetPictureHeader:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 96]
	cmp	w0, 1
	beq	.L181
	ldr	x3, .LC31
	mov	x2, 160
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	w1, 24
	mov	x0, x20
	bl	BsShow
	mov	w21, w0
	mov	w1, 24
	mov	x0, x20
	bl	BsSkip
	cmp	w21, 1
	bne	.L173
	mov	x0, x20
	add	x1, x29, 60
	bl	Real8_CB_GetVLCBits
	cmp	w0, 30
	bls	.L173
	ldr	w0, [x29, 60]
	tbnz	x0, 0, .L173
	tbz	x0, 1, .L182
	stp	wzr, wzr, [x19, 104]
.L166:
	ubfx	x1, x0, 2, 5
	ubfx	x0, x0, 7, 8
	str	w1, [x19, 140]
	add	x1, x29, 60
	str	w0, [x19, 128]
	mov	x0, x20
	bl	Real8_CB_GetVLCBits
	cmp	w0, 1
	beq	.L177
	cmp	w0, 3
	beq	.L183
	cmp	w0, 5
	bne	.L173
	ldr	w0, [x29, 60]
	cbnz	w0, .L173
	mov	w0, 2
.L177:
	str	w0, [x19, 100]
.L168:
	ldr	w0, [x19, 108]
	cbz	w0, .L184
.L170:
	sub	w0, w0, #48
	mov	w1, 8144
	cmp	w0, w1
	bhi	.L173
.L180:
	ldr	w0, [x19, 104]
	sub	w0, w0, #48
	cmp	w0, w1
	bhi	.L173
	mov	x0, x19
	bl	Real8_CB_SetDimensions
	mov	w0, 1
.L156:
	ldp	w2, w1, [x19, 104]
	add	w1, w1, 15
	add	w2, w2, 15
	lsr	w2, w2, 4
	lsr	w1, w1, 4
	stp	w2, w1, [x19, 112]
	mul	w1, w1, w2
	str	w1, [x19, 120]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L182:
	mov	w2, 176
	mov	w1, 144
	stp	w1, w2, [x19, 104]
	b	.L166
	.p2align 3
.L183:
	ldr	w0, [x29, 60]
	cmp	w0, 1
	beq	.L185
.L173:
	mov	w0, -2
.L187:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L181:
	add	x21, x19, 16
	mov	w0, -1
	mov	x5, x19
	add	x4, x29, 60
	add	x3, x29, 52
	add	x2, x29, 56
	str	w0, [x21, 40]
	mov	w1, 0
	mov	x0, x20
	bl	Real8_CB_GetSliceHeader
	cmp	w0, 1
	mov	w0, -2
	bne	.L156
	ldr	w0, [x21, 36]
	cmp	w0, 3
	bls	.L186
.L157:
	ldrb	w1, [x19, 16]
	str	w1, [x19, 132]
	mov	w1, 8144
	ldr	w0, [x19, 108]
	ldrb	w2, [x21, 1]
	str	w2, [x19, 136]
	sub	w0, w0, #48
	cmp	w0, w1
	ldrb	w0, [x21, 2]
	str	w0, [x19, 140]
	ldr	w0, [x21, 44]
	str	w0, [x19, 128]
	ldr	w0, [x21, 48]
	str	w0, [x19, 148]
	ldr	w0, [x21, 52]
	str	w0, [x19, 152]
	bls	.L180
	mov	w0, -2
	b	.L187
	.p2align 3
.L184:
	mov	x1, x19
	mov	x0, x20
	bl	Real8_CB_GetCPFMT
	cbz	w0, .L173
	ldr	w0, [x19, 108]
	b	.L170
	.p2align 3
.L186:
	ldr	x1, .LC30
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx159
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx159:
	.section	.rodata
	.align	0
	.align	2
.L159:
	.byte	(.L158 - .Lrtx159) / 4
	.byte	(.L160 - .Lrtx159) / 4
	.byte	(.L161 - .Lrtx159) / 4
	.byte	(.L162 - .Lrtx159) / 4
	.text
	.p2align 3
.L185:
	str	wzr, [x19, 100]
	b	.L168
.L161:
	mov	w0, 1
	str	w0, [x19, 100]
	b	.L157
.L160:
	str	wzr, [x19, 100]
	str	wzr, [x21, 20]
	b	.L157
.L158:
	str	wzr, [x19, 100]
	mov	w0, 1
	str	w0, [x21, 20]
	b	.L157
.L162:
	mov	w0, 2
	str	w0, [x19, 100]
	b	.L157
	.size	Real8_CB_GetPictureHeader, .-Real8_CB_GetPictureHeader
	.align	3
.LC30:
	.xword	.L159
	.align	3
.LC31:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_SetImgFormat
	.type	Real8_SetImgFormat, %function
Real8_SetImgFormat:
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
	ldr	w0, [x21, 2328]
	ldr	w1, [x1, 2576]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L188
	ldr	w3, [x21, 380]
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
	ldr	w2, [x21, 388]
	str	w2, [x0, 68]
	ldr	w2, [x21, 384]
	str	w2, [x0, 72]
	bl	SetAspectRatio
	ldr	x0, [x20]
	ldr	w0, [x0, 28]
	cmp	w0, 25
	beq	.L194
.L190:
	mov	w1, 1
	strb	w1, [x19, 291]
	strb	w1, [x19, 289]
	add	x1, x19, 256
	strb	wzr, [x19, 284]
	mov	w0, 8
	stp	w0, w0, [x1, 40]
	stp	w0, w0, [x1, 48]
.L188:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L194:
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
	b	.L190
	.size	Real8_SetImgFormat, .-Real8_SetImgFormat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	RV8_RecordVFMWState
	.type	RV8_RecordVFMWState, %function
RV8_RecordVFMWState:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	RV8_RecordVFMWState, .-RV8_RecordVFMWState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_WriteSliceMsg
	.type	Real8_WriteSliceMsg, %function
Real8_WriteSliceMsg:
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
	ldr	w0, [x1, 468]
	add	x2, x19, x2, lsl 2
	str	w0, [x2, 96]
	ldr	w0, [x1, 460]
	str	w0, [x2, 104]
	ldr	w0, [x1, 464]
	str	w0, [x2, 112]
	ldr	w0, [x1, 480]
	str	w0, [x2, 100]
	ldr	w0, [x1, 472]
	str	w0, [x2, 108]
	ldr	w0, [x1, 476]
	str	w0, [x2, 116]
	ldr	w0, [x1, 448]
	str	w0, [x2, 120]
	ldr	w0, [x1, 444]
	str	w0, [x2, 124]
	ldr	w0, [x1, 440]
	str	w0, [x2, 128]
	ldr	w0, [x1, 452]
	str	w0, [x2, 132]
	str	w20, [x19, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_WriteSliceMsg, .-Real8_WriteSliceMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_WritePicMsg
	.type	Real8_WritePicMsg, %function
Real8_WritePicMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x2, x19, 53248
	mov	x0, 52336
	add	x0, x19, x0
	add	x2, x2, 280
	ldr	w3, [x2, 100]
	strb	w3, [x19, 28]
	cmp	w3, 2
	ldr	w3, [x2, 116]
	str	w3, [x19, 20]
	ldr	w3, [x2, 112]
	str	w3, [x19, 24]
	ldr	w3, [x0, 2492]
	str	w3, [x19, 32]
	ldr	w3, [x0, 2496]
	str	w3, [x19, 36]
	ldr	w2, [x2, 140]
	str	w2, [x19, 40]
	ldr	w3, [x0, 1396]
	str	w3, [x19, 44]
	ldr	w3, [x0, 1400]
	str	w3, [x19, 48]
	beq	.L197
	str	w2, [x0, 1396]
.L197:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_WritePicMsg, .-Real8_WritePicMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_WriteReg
	.type	Real8_WriteReg, %function
Real8_WriteReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	str	w20, [x19, 56]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Real8_WriteReg, .-Real8_WriteReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Real8_ModifySliceMsg
	.type	Real8_ModifySliceMsg, %function
Real8_ModifySliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 16
	ldr	w1, [x0, 132]
	cbnz	w1, .L207
	ldp	w1, w4, [x0, 4]
	ldr	w5, [x0, 36]
	mul	w4, w1, w4
	cmp	w5, 2
	sub	w4, w4, #1
	bhi	.L229
.L206:
	cmp	w5, 1
	bls	.L211
	sub	w7, w5, #1
	mov	w3, 0
	b	.L212
	.p2align 3
.L213:
	add	w3, w3, 1
	lsl	x1, x1, 2
	sub	x1, x1, x2
	sxtw	x6, w3
	lsl	x2, x6, 2
	add	x1, x0, x1, lsl 2
	sub	x2, x2, x6
	lsl	x2, x2, 2
	sub	x2, x2, x6
	ldr	w6, [x1, 132]
	add	x1, x0, x2, lsl 2
	ldr	w1, [x1, 132]
	cmp	w6, w1
	bge	.L207
.L212:
	sxtw	x2, w3
	cmp	w3, w7
	lsl	x1, x2, 2
	sub	x1, x1, x2
	bne	.L213
	uxtw	x3, w3
	lsl	x1, x3, 2
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x3, x1, x3
	add	x3, x0, x3, lsl 2
	ldr	w1, [x3, 132]
	cmp	w4, w1
	ccmp	w1, wzr, 4, ge
	ble	.L207
.L211:
	cbz	w5, .L214
	sub	w9, w5, #1
	mov	w8, 0
	mov	x10, 44
	b	.L217
	.p2align 3
.L232:
	beq	.L230
.L217:
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
	beq	.L231
	sub	x3, x3, x6
	add	x2, x0, x2, lsl 2
	add	x3, x0, x3, lsl 2
	ldr	w3, [x3, 132]
	sub	w3, w3, #1
	str	w3, [x2, 136]
.L216:
	lsl	x1, x7, 2
	add	w8, w8, 1
	sub	x1, x1, x7
	lsl	x1, x1, 2
	sub	x1, x1, x7
	add	x1, x0, x1, lsl 2
	ldr	w2, [x1, 132]
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
	cbz	w1, .L232
	.p2align 2
.L207:
	mov	w0, 0
.L227:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L229:
	ldr	w1, [x0, 176]
	sub	w6, w5, #1
	mov	w2, 1
	cmp	w4, w1
	ccmp	w1, wzr, 4, gt
	bgt	.L209
	b	.L207
	.p2align 3
.L210:
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x1, x1, x3
	add	x1, x0, x1, lsl 2
	ldr	w1, [x1, 132]
	cmp	w1, wzr
	ccmp	w4, w1, 4, gt
	ble	.L207
.L209:
	add	w2, w2, 1
	cmp	w2, w6
	sxtw	x3, w2
	lsl	x1, x3, 2
	bne	.L210
	b	.L206
.L230:
	ldr	w3, [x0, 96]
	mov	w6, 0
	mov	x4, 0
	mov	w2, w3
	b	.L220
	.p2align 3
.L233:
	ldr	w2, [x2, 96]
.L220:
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
	ldr	w7, [x1, 100]
	add	x2, x0, x2, lsl 2
	cmp	w7, w3
	bcs	.L218
	ldr	w1, [x1, 116]
	cmp	w1, wzr
	csel	w3, w3, w7, eq
.L218:
	cmp	w6, w5
	bne	.L233
	and	w3, w3, -16
	mov	w6, 0
	str	w3, [x0, 44]
	b	.L224
	.p2align 3
.L234:
	ldr	w2, [x1, 104]
	ldr	w7, [x1, 96]
	mov	x4, x2
	add	w2, w7, w2, lsr 3
	and	w4, w4, 7
	sub	w3, w2, w3
	ubfiz	w2, w3, 3, 4
	and	w3, w3, -16
	add	w2, w2, w4
	str	w3, [x1, 96]
	str	w2, [x1, 104]
.L222:
	add	w6, w6, 1
	cmp	w5, w6
	bls	.L223
	ldr	w3, [x0, 44]
.L224:
	sxtw	x2, w6
	lsl	x1, x2, 2
	sub	x1, x1, x2
	lsl	x1, x1, 2
	sub	x1, x1, x2
	add	x1, x0, x1, lsl 2
	ldr	w2, [x1, 100]
	cbz	w2, .L234
	ldp	w4, w2, [x1, 104]
	ldp	w10, w9, [x1, 96]
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
	stp	w4, w3, [x1, 96]
	stp	w7, w2, [x1, 104]
	b	.L222
.L214:
	ldr	w1, [x0, 96]
	and	w1, w1, -16
	str	w1, [x0, 44]
.L223:
	mov	w0, 1
	b	.L227
.L231:
	madd	x1, x7, x10, x0
	mov	w3, w4
	str	w4, [x1, 136]
	b	.L216
	.size	Real8_ModifySliceMsg, .-Real8_ModifySliceMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_Init
	.type	REAL8DEC_Init, %function
REAL8DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L239
	ldr	x3, .LC34
	add	x20, x19, 53248
	mov	x2, 55592
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	ldr	w22, [x20, 2320]
	blr	x3
	str	w22, [x20, 2320]
	add	x0, x20, 1720
	bl	ResetVoQueue
	str	x21, [x19]
	add	x1, x19, 8192
	mov	w5, 15
	add	x1, x1, 3184
	mov	w3, 1
	add	x4, x1, 40960
	mov	w6, 8192
	mov	x0, x19
	str	w5, [x4, 1396]
	str	w5, [x4, 1400]
	ldr	w4, [x21, 8]
	strb	w4, [x1, 18]
	strb	wzr, [x1, 20]
	strb	w3, [x20, 288]
	str	w3, [x20, 376]
	str	w6, [x20, 404]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x20, 2328]
	mov	w0, 0
	beq	.L240
.L237:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L239:
	ldr	x1, .LC33
	mov	w2, 1524
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L240:
	ldr	x1, .LC36
	bl	dprint_vfmw
	mov	w0, -20
	b	.L237
	.size	REAL8DEC_Init, .-REAL8DEC_Init
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC34:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC36:
	.xword	.LC35
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_Destroy
	.type	REAL8DEC_Destroy, %function
REAL8DEC_Destroy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L244
	mov	x0, 52336
	ldr	x1, .LC39
	add	x2, x19, x0
	mov	w0, 2
	ldr	w2, [x2, 2468]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L244:
	ldr	x1, .LC37
	mov	w2, 1575
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL8DEC_Destroy, .-REAL8DEC_Destroy
	.align	3
.LC37:
	.xword	.LC32
	.align	3
.LC39:
	.xword	.LC38
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_Decode
	.type	REAL8DEC_Decode, %function
REAL8DEC_Decode:
	stp	x29, x30, [sp, -416]!
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
	add	x0, x29, 256
	cmp	x20, xzr
	stp	xzr, xzr, [x29, 192]
	stp	xzr, xzr, [x29, 208]
	stp	xzr, xzr, [x0]
	add	x0, x29, 272
	ccmp	x19, xzr, 4, ne
	stp	xzr, xzr, [x29, 224]
	stp	xzr, xzr, [x29, 240]
	stp	xzr, xzr, [x0]
	add	x0, x29, 288
	stp	xzr, xzr, [x0]
	add	x0, x29, 304
	stp	xzr, xzr, [x0]
	add	x0, x29, 320
	stp	xzr, xzr, [x0]
	add	x0, x29, 336
	stp	xzr, xzr, [x0]
	add	x0, x29, 352
	stp	xzr, xzr, [x0]
	add	x0, x29, 368
	stp	xzr, xzr, [x0]
	add	x0, x29, 384
	stp	xzr, xzr, [x0]
	add	x0, x29, 400
	stp	xzr, xzr, [x0]
	beq	.L374
	add	x22, x20, 53248
	add	x8, x29, 256
	mov	w0, 1
	mov	w4, 8192
	add	x24, x20, 16
	ldr	w3, [x22, 356]
	ldr	w2, [x22, 360]
	str	w3, [x22, 364]
	str	w2, [x22, 368]
	str	w0, [x22, 376]
	str	w4, [x22, 404]
	stp	w3, w2, [x8, 76]
	stp	w3, w2, [x8, 84]
	str	w0, [x29, 352]
	str	w4, [x29, 380]
	cbz	x19, .L375
	ldr	x26, .LC45
	mov	w1, 0
	mov	x2, 11360
	mov	x0, x24
	add	x23, x20, 8192
	ldr	x3, [x26, 96]
	blr	x3
	add	x1, x23, 3184
	add	x0, x1, 40960
	str	wzr, [x0, 2432]
	ldr	w2, [x19, 20]
	str	w2, [x0, 2452]
	ldr	w2, [x19, 16]
	str	w2, [x0, 2436]
	ldr	x2, [x19]
	str	x2, [x20, 11376]
	ldr	w2, [x19, 20]
	str	w2, [x0, 2440]
	ldrb	w3, [x19, 10]
	strb	w3, [x1, 16]
	ldrb	w3, [x19, 10]
	cmp	w3, 1
	beq	.L249
	ldr	w3, [x19, 104]
	str	w3, [x0, 2444]
	ldr	x3, [x19, 88]
	str	x3, [x1, 8]
	ldr	w3, [x19, 108]
	str	w3, [x0, 2448]
	ldrb	w0, [x19, 98]
	strb	w0, [x1, 17]
	ldrb	w0, [x19, 98]
	cmp	w0, 1
	bne	.L376
	mov	w0, 65460
	sub	w1, w2, #75
	movk	w0, 0x2f, lsl 16
	cmp	w1, w0
	bhi	.L252
.L251:
	ldr	x1, [x20, 11376]
	cbz	x1, .L252
	add	x19, x22, 1680
	mov	x0, x19
	bl	BsInit
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w21, w0
	mov	w1, 8
	mov	x0, x19
	str	w21, [x29, 120]
	bl	BsSkip
	cmp	w21, 8
	bhi	.L252
	mov	x25, 0
	add	x21, x29, 192
	.p2align 2
.L253:
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	mov	w27, w0
	mov	w1, 32
	mov	x0, x19
	rev	w27, w27
	bl	BsSkip
	str	w27, [x21, x25]
	add	x25, x25, 4
	cmp	x25, 64
	bne	.L253
	mov	w1, 8
	mov	x0, x19
	bl	BsShow
	mov	w25, w0
	mov	w1, 8
	mov	x0, x19
	bl	BsSkip
	add	w0, w25, 1
	cmp	w25, 255
	add	x25, x23, 3184
	mov	w2, w0
	add	x27, x25, 40960
	str	w0, [x27, 1404]
	bhi	.L252
	cbz	w0, .L254
	stp	x27, x25, [x29, 128]
	mov	w28, 3145727
	mov	w27, 0
	b	.L255
	.p2align 3
.L377:
	ldr	x0, [x29, 128]
	ldr	w2, [x0, 1404]
	cmp	w2, w27
	bls	.L254
.L255:
	mov	w1, 32
	mov	x0, x19
	bl	BsSkip
	mov	w1, 32
	mov	x0, x19
	bl	BsShow
	mov	w25, w0
	mov	w1, 32
	mov	x0, x19
	bl	BsSkip
	uxtw	x1, w27
	ldr	x2, [x29, 136]
	add	x1, x1, 8192
	rev	w0, w25
	add	x1, x1, 2400
	cmp	w0, w28
	add	w27, w27, 1
	str	w0, [x2, x1, lsl 2]
	ble	.L377
.L252:
	mov	w28, 0
	mov	w0, w28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 416
	ret
	.p2align 3
.L376:
	ldr	w1, [x19, 24]
	mov	w28, 0
	ldr	w0, [x22, 2328]
	bl	SM_ReleaseStreamSeg
	ldr	w1, [x19, 112]
	ldr	w0, [x22, 2328]
	bl	SM_ReleaseStreamSeg
.L363:
	mov	w0, w28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 416
	ret
	.p2align 3
.L374:
	ldr	x1, .LC42
	mov	w2, 1613
	mov	w0, 0
	mov	w28, 0
	bl	dprint_vfmw
	mov	w0, w28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 416
	ret
	.p2align 3
.L249:
	str	wzr, [x0, 2444]
	str	xzr, [x1, 8]
	str	wzr, [x0, 2448]
	mov	w0, 65460
	strb	wzr, [x1, 17]
	movk	w0, 0x2f, lsl 16
	sub	w1, w2, #75
	cmp	w1, w0
	bls	.L251
	b	.L252
	.p2align 3
.L375:
	mov	x2, 52336
	ldr	x1, .LC44
	add	x20, x20, x2
	mov	w28, 0
	ldr	w2, [x20, 2468]
	bl	dprint_vfmw
	b	.L363
	.p2align 3
.L254:
	add	x3, x22, 496
	sub	w5, w2, #1
	mov	w1, 0
	b	.L256
	.p2align 3
.L257:
	add	x0, x0, 8192
	ldr	w4, [x3], 4
	add	x0, x23, x0, lsl 2
	ldr	w0, [x0, 12784]
	cmp	w0, w4
	ble	.L252
.L256:
	cmp	w1, w5
	add	w0, w1, 1
	mov	x1, x0
	bne	.L257
	add	x4, x23, 3184
	lsl	w2, w2, 3
	add	x0, x4, 40960
	add	w25, w2, 66
	mov	w2, 65461
	mov	w1, 3145727
	movk	w2, 0x2f, lsl 16
	str	x4, [x29, 136]
	ldr	w27, [x0, 1408]
	add	w27, w25, w27
	sub	w3, w27, #74
	cmp	w3, w2
	ccmp	w25, w1, 0, ls
	bgt	.L252
	ldr	w2, [x0, 2440]
	sub	w2, w2, w27
	cmp	w2, wzr
	ble	.L252
	ldr	x1, [x20, 11376]
	mov	x0, x19
	add	x1, x1, x27, sxtw
	bl	BsInit
	str	x21, [x29, 280]
	ldr	w0, [x29, 120]
	add	x1, x29, 416
	ldr	x3, .LC46
	add	x4, x29, 152
	str	w0, [x29, 288]
	add	x2, x1, x0, uxtw 2
	add	x3, x3, 448
	ldr	w0, [x3, 32]
	sub	x2, x2, #4096
	str	w0, [x29, 184]
	add	x1, x29, 256
	ldp	x6, x7, [x3]
	stp	x6, x7, [x4]
	ldp	x6, x7, [x3, 16]
	add	x3, x29, 168
	mov	x0, x19
	stp	x6, x7, [x3]
	ldr	w2, [x2, 3832]
	str	w2, [x29, 276]
	bl	Real8_CB_GetPictureHeader
	cmp	w0, 1
	mov	w28, w0
	ldr	x4, [x29, 136]
	bne	.L378
	ldrb	w0, [x4, 20]
	cbnz	w0, .L259
	ldr	x21, .LC49
	ldr	x4, [x21]
	cbz	x4, .L260
	ldr	w0, [x22, 392]
	mov	w3, 8
	ldr	w1, [x29, 372]
	add	x2, x29, 152
	strh	w0, [x29, 154]
	ldr	w0, [x29, 368]
	strh	w1, [x29, 156]
	strh	w0, [x29, 158]
	ldr	w1, [x22, 396]
	ldr	w0, [x22, 2328]
	strh	w1, [x29, 152]
	mov	w1, 2
	blr	x4
.L260:
	ldr	w0, [x22, 2328]
	bl	FSP_GetFspType
	cbnz	w0, .L261
	ldr	w0, [x22, 2328]
	add	x2, x29, 148
	add	x3, x29, 152
	add	x1, x29, 144
	stp	wzr, wzr, [x29, 144]
	str	wzr, [x29, 152]
	bl	VCTRL_GetChanImgNum
	ldr	x0, [x20]
	ldr	w2, [x0, 772]
	cmp	w2, 1
	beq	.L379
.L261:
	add	x4, x23, 3184
	add	x1, x22, 1720
	add	x21, x4, 40960
	ldr	w0, [x22, 2328]
	stp	x1, x4, [x29, 128]
	mov	w2, 1
	ldr	w1, [x21, 2572]
	bl	FSP_ClearLogicFs
	ldr	w1, [x21, 2568]
	mov	w2, 1
	ldr	w0, [x22, 2328]
	bl	FSP_ClearLogicFs
	str	wzr, [x21, 2568]
	str	wzr, [x21, 2572]
	ldr	w0, [x22, 2328]
	bl	FSP_GetNullLogicFs
	str	w0, [x21, 2568]
	ldr	x4, [x29, 136]
	add	x1, x22, 1720
	str	w0, [x21, 2572]
	strb	wzr, [x4, 23]
	ldr	w0, [x22, 2328]
	bl	FSP_ClearNotInVoQueue
	ldr	w2, [x29, 372]
	ldr	w3, [x29, 368]
	cmp	w2, 512
	ldr	x4, [x29, 136]
	bhi	.L268
	ldr	w0, [x29, 368]
	cmp	w0, 512
	mov	w3, w0
	bhi	.L268
	ldr	x1, [x20]
	ldr	w3, [x1, 772]
	cbnz	w3, .L270
	ldr	w1, [x1, 28]
	cmp	w1, 25
	beq	.L380
.L270:
	ldr	w0, [x22, 2328]
	bl	FSP_GetFspType
	cbz	w0, .L364
.L367:
	ldr	w0, [x29, 368]
	ldr	w2, [x29, 372]
.L272:
	ldr	x1, .LC55
	mov	w3, w0
	mov	w0, 1
	bl	dprint_vfmw
	add	x2, x29, 256
	mov	x1, x20
	mov	w0, 6
	bl	Real8_ArrangeVHBMem
	cbz	w0, .L381
.L259:
	ldr	x3, [x26, 104]
	add	x0, x22, 280
	add	x1, x29, 256
	mov	x2, 160
	str	x0, [x29, 128]
	add	x21, x23, 3184
	blr	x3
	ldr	x0, [x20]
	ldr	w0, [x0, 8]
	strb	w0, [x23, 3202]
	mov	x0, x20
	bl	Real8_GetImageBuffer
	cbz	w0, .L382
	add	x26, x21, 40960
	ldr	w0, [x22, 2328]
	ldr	w1, [x26, 2576]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L275
	ldr	x0, [x20]
	mov	x4, -1
	ldr	x1, .LC61
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
	ldr	x0, [x29, 128]
	ldr	w0, [x0, 100]
	cmp	w0, 2
	beq	.L383
	cmp	w0, 1
	beq	.L384
	ldrb	w0, [x21, 23]
	cmp	w0, wzr
	mov	w0, 2
	csinc	w0, w0, wzr, ne
.L279:
	add	x21, x23, 3184
	strb	w0, [x23, 3207]
	add	x21, x21, 40960
	ldr	w2, [x21, 2568]
	ldr	w0, [x21, 2572]
	cmp	w2, w0
	beq	.L280
	ldr	x1, .LC63
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w1, [x21, 2568]
	mov	w2, 0
	ldr	w0, [x22, 2328]
	bl	FSP_SetRef
.L280:
	add	x26, x23, 3184
	mov	w2, 1
	add	x21, x26, 40960
	ldr	w0, [x21, 2572]
	ldr	w1, [x21, 2576]
	str	w1, [x21, 2572]
	str	w0, [x21, 2568]
	ldr	w0, [x22, 2328]
	bl	FSP_SetRef
	ldr	w1, [x21, 2568]
	ldr	w0, [x22, 2328]
	bl	FSP_RemovePmv
	ldr	x1, .LC65
	mov	w0, 13
	ldr	w2, [x21, 2576]
	bl	dprint_vfmw
	ldrb	w0, [x23, 3202]
	cmp	w0, 4
	bne	.L282
	ldr	w0, [x22, 380]
	cbnz	w0, .L285
	str	wzr, [x21, 2584]
.L282:
	add	x26, x23, 3184
	ldr	w0, [x22, 2328]
	add	x26, x26, 40960
	ldr	w1, [x26, 2576]
	bl	FSP_GetLogicFs
	mov	x21, x0
	ldr	w1, [x26, 2568]
	ldr	w0, [x22, 2328]
	bl	FSP_GetLogicFs
	mov	x9, x0
	ldr	w1, [x26, 2572]
	ldr	w0, [x22, 2328]
	str	x9, [x29, 136]
	bl	FSP_GetLogicFs
	mov	x26, x0
	ldr	x9, [x29, 136]
	cmp	x21, xzr
	ccmp	x9, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L385
	ldr	x0, [x21, 32]
	cbz	x0, .L289
	ldr	x1, [x21, 40]
	cbz	x1, .L289
	ldr	x1, [x26, 32]
	cbz	x1, .L291
	ldr	w5, [x1, 8]
.L292:
	str	w5, [x24, 48]
	ldr	x0, [x9, 32]
	cbz	x0, .L386
.L368:
	ldr	w4, [x0, 8]
	str	w4, [x24, 52]
	ldr	x1, .LC72
	ldr	x0, [x21, 32]
	str	x9, [x29, 136]
	ldr	w2, [x0, 8]
	mov	w0, 13
	str	w2, [x24, 56]
	ldr	w6, [x21, 8]
	str	w6, [x24, 68]
	ldr	w7, [x26, 8]
	str	w7, [x24, 72]
	ldr	x3, [x21, 40]
	ldr	w3, [x3, 8]
	str	w3, [x24, 60]
	bl	dprint_vfmw
	ldr	x0, [x21, 40]
	ldr	x9, [x29, 136]
	ldr	w0, [x0, 24]
	str	w0, [x24, 64]
	ldr	x0, [x21, 40]
	ldr	w0, [x0, 60]
	str	w0, [x24, 84]
	ldr	x0, [x21, 40]
	ldr	w0, [x0, 44]
	str	w0, [x24, 88]
	ldr	x0, [x21, 40]
	ldr	w0, [x0, 48]
	str	w0, [x24, 92]
	ldr	w0, [x22, 380]
	cmp	w0, 2
	beq	.L387
.L295:
	ldr	w0, [x22, 408]
	str	w0, [x21, 16]
	add	x0, x23, 3184
	add	x0, x0, 40960
	ldr	w2, [x22, 380]
	ldr	w3, [x22, 420]
	strb	w2, [x24, 12]
	cmp	w2, 2
	str	w3, [x29, 136]
	ldr	w2, [x22, 396]
	str	w2, [x24, 4]
	ldr	w1, [x22, 392]
	str	w1, [x24, 8]
	ldr	w1, [x0, 2492]
	str	w1, [x24, 16]
	ldr	w1, [x0, 2496]
	stp	w1, w3, [x24, 20]
	ldr	w1, [x0, 1396]
	str	w1, [x24, 28]
	ldr	w1, [x0, 1400]
	str	w1, [x24, 32]
	beq	.L300
	str	w3, [x0, 1396]
.L300:
	mov	x0, x19
	bl	BsPos
	and	w1, w0, -2147483641
	add	x2, x22, 440
	tbnz	w0, #31, .L388
.L301:
	str	w1, [x2, 20]
	add	x1, x23, 3184
	add	x1, x1, 40960
	ldr	w0, [x1, 1404]
	cmp	w0, 1
	beq	.L389
	ldr	w21, [x1, 1408]
	ldr	w0, [x1, 1412]
.L369:
	sub	w21, w0, w21
	mov	x0, x19
	lsl	w21, w21, 3
	bl	BsPos
	sub	w0, w21, w0
	add	x21, x23, 3184
	str	w0, [x22, 464]
	add	x9, x21, 40960
	mov	x0, x19
	str	x9, [x29, 120]
	ldr	w1, [x9, 2436]
	add	w27, w27, w1
	bl	BsPos
	add	x5, x22, 256
	mov	w1, 8
	add	x6, x22, 256
	ldr	w2, [x22, 416]
	ldr	w3, [x22, 424]
	mov	w7, 1
	sdiv	w0, w0, w1
	ldr	w4, [x29, 136]
	ldr	x9, [x29, 120]
	stp	w4, w3, [x5, 184]
	stp	w2, wzr, [x5, 192]
	stp	wzr, wzr, [x6, 220]
	add	w0, w0, w27
	stp	w0, wzr, [x6, 212]
	str	w0, [x24, 96]
	ldr	w0, [x22, 460]
	str	w0, [x24, 104]
	ldr	w0, [x22, 464]
	stp	wzr, w0, [x24, 108]
	str	w7, [x24, 36]
	str	wzr, [x24, 100]
	stp	wzr, w2, [x24, 116]
	stp	w3, w4, [x24, 124]
	str	wzr, [x24, 132]
	ldr	w0, [x9, 1404]
	cmp	w0, w7
	bls	.L323
	ldr	w6, [x9, 1412]
	mov	w0, 3145727
	add	w6, w25, w6
	cmp	w6, w0
	bgt	.L309
	cmp	w6, 73
	ble	.L309
	ldr	w2, [x9, 2440]
	sub	w2, w2, w6
	cmp	w2, wzr
	ble	.L309
	mov	w26, w7
	mov	x27, x9
	stp	w0, w7, [x29, 112]
	b	.L312
	.p2align 3
.L313:
	ldr	w0, [x27, 1404]
	add	w26, w26, 1
	cmp	w0, w26
	bls	.L323
	uxtw	x0, w26
	add	x0, x0, 8192
	add	x0, x0, 2400
	ldr	w6, [x21, x0, lsl 2]
	ldr	w0, [x29, 112]
	add	w6, w25, w6
	cmp	w6, w0
	bgt	.L309
	cmp	w6, 73
	ble	.L309
	ldr	w2, [x27, 2440]
	sub	w2, w2, w6
	cmp	w2, wzr
	ble	.L309
.L312:
	ldr	x1, [x21]
	mov	x0, x19
	str	w6, [x29, 120]
	add	x1, x1, x6, sxtw
	bl	BsInit
	ldr	x5, [x29, 128]
	add	x2, x29, 144
	add	x4, x29, 152
	add	x3, x29, 148
	mov	w1, 0
	mov	x0, x19
	bl	Real8_CB_GetSliceHeader
	cmp	w0, 1
	mov	w2, w0
	ldr	w6, [x29, 120]
	bne	.L313
	ldr	w1, [x29, 144]
	ldr	w0, [x22, 396]
	str	w1, [x29, 120]
	cbz	w0, .L390
	ldr	w0, [x29, 152]
	ldr	w1, [x29, 136]
	cmp	w0, wzr
	str	w6, [x29, 108]
	csel	w0, w1, w0, lt
	str	w0, [x29, 136]
	mov	x0, x19
	bl	BsPos
	asr	w1, w0, 31
	lsr	w1, w1, 29
	ldr	w6, [x29, 108]
	add	w0, w0, w1
	and	w0, w0, 7
	sub	w0, w0, w1
	str	w0, [x22, 460]
	add	x0, x22, 440
	str	x0, [x29, 96]
	ldr	w0, [x27, 1404]
	sub	w0, w0, #1
	cmp	w0, w26
	beq	.L391
	cmp	w26, 254
	bhi	.L392
	add	w0, w26, 1
	uxtw	x1, w26
	add	x0, x0, 8192
	add	x1, x1, 8192
	add	x0, x0, 2400
	add	x1, x1, 2400
	str	w6, [x29, 96]
	ldr	w0, [x21, x0, lsl 2]
	ldr	w1, [x21, x1, lsl 2]
.L370:
	sub	w1, w0, w1
	mov	x0, x19
	lsl	w1, w1, 3
	str	w1, [x29, 108]
	bl	BsPos
	ldr	w1, [x29, 108]
	ldr	w6, [x29, 96]
	sub	w0, w1, w0
	str	w0, [x22, 464]
	mov	x0, x19
	ldr	w2, [x27, 2436]
	add	w6, w6, w2
	str	w6, [x29, 108]
	bl	BsPos
	cmp	w0, wzr
	add	w3, w0, 7
	ldr	w6, [x29, 108]
	csel	w0, w3, w0, lt
	ldr	w4, [x29, 120]
	str	w4, [x22, 452]
	add	w2, w6, w0, asr 3
	ldr	w0, [x29, 136]
	str	w0, [x22, 440]
	add	x0, x22, 256
	stp	w2, wzr, [x0, 212]
	stp	wzr, wzr, [x0, 220]
	ldr	w0, [x29, 116]
	sxtw	x3, w0
	add	w0, w0, 1
	mov	w5, w0
	cmp	w0, 131
	lsl	x0, x3, 2
	str	w5, [x29, 116]
	sub	x0, x0, x3
	lsl	x0, x0, 2
	sub	x0, x0, x3
	ldr	w3, [x22, 424]
	str	w3, [x22, 444]
	add	x0, x24, x0, lsl 2
	ldr	w3, [x22, 416]
	str	w3, [x22, 448]
	str	w2, [x0, 96]
	ldr	w2, [x22, 460]
	str	w2, [x0, 104]
	ldr	w2, [x22, 464]
	str	w2, [x0, 112]
	ldr	w2, [x22, 480]
	str	w2, [x0, 100]
	ldr	w2, [x22, 472]
	str	w2, [x0, 108]
	ldr	w2, [x22, 476]
	str	w2, [x0, 116]
	ldr	w2, [x22, 448]
	str	w2, [x0, 120]
	ldr	w2, [x22, 444]
	str	w2, [x0, 124]
	ldr	w2, [x22, 440]
	str	w2, [x0, 128]
	ldr	w1, [x22, 452]
	str	w1, [x0, 132]
	str	w5, [x24, 36]
	ble	.L313
	mov	x0, x20
	bl	Real8_ModifySliceMsg
	cmp	w0, 1
	bne	.L393
	str	x24, [x20, 8]
	cbz	x24, .L394
	ldr	x0, [x20]
	ldr	w1, [x0, 952]
	cmp	w1, 1
	beq	.L395
	cmp	w1, 2
	bne	.L313
	ldr	w0, [x0, 956]
	cmp	w0, wzr
	ble	.L313
	ldrb	w0, [x24, 12]
	cmp	w0, 2
	bne	.L313
	str	xzr, [x20, 8]
	mov	w2, 0
	mov	w28, 0
	ldr	w1, [x22, 1664]
	ldr	w0, [x22, 2328]
	bl	FSP_SetDisplay
	ldr	x3, [x20]
	mov	x1, x20
	mov	w0, 8
	ldr	w2, [x3, 956]
	sub	w2, w2, #1
	str	w2, [x3, 956]
	bl	ReleasePacket
	b	.L363
	.p2align 3
.L378:
	ldr	x1, .LC48
	mov	w0, 1
	mov	w28, 0
	bl	dprint_vfmw
	b	.L363
.L268:
	ldr	x1, .LC53
	mov	w0, 18
	mov	w28, 0
	bl	dprint_vfmw
	b	.L363
.L382:
	add	x21, x21, 40960
	ldr	x1, .LC59
	mov	w28, 0
	ldr	w2, [x21, 2468]
	bl	dprint_vfmw
	b	.L363
.L381:
	ldr	x1, .LC57
	mov	w0, 1
	mov	w28, 0
	bl	dprint_vfmw
	b	.L363
.L383:
	ldrb	w0, [x21, 23]
	cmp	w0, 1
	bls	.L309
	ldrb	w0, [x21, 18]
	cmp	w0, 4
	bne	.L282
.L325:
	add	x0, x23, 3184
	add	x0, x0, 40960
	ldr	w1, [x0, 2584]
	cbnz	w1, .L282
	ldr	w1, [x0, 2576]
	mov	w2, 1
	ldr	w0, [x22, 2328]
	mov	w28, 0
	bl	FSP_ClearLogicFs
	b	.L363
.L384:
	ldrb	w1, [x21, 23]
	mov	w0, 2
	cbnz	w1, .L279
.L309:
	add	x1, x23, 3184
	ldr	w0, [x22, 2328]
	add	x1, x1, 40960
	mov	w2, 1
	mov	w28, 0
	ldr	w1, [x1, 2576]
	bl	FSP_ClearLogicFs
	b	.L363
.L380:
	ldrb	w1, [x4, 20]
	cbnz	w1, .L272
.L364:
	add	x0, x22, 1720
	bl	ResetVoQueue
	b	.L367
.L323:
	mov	w19, 1
	str	w19, [x24, 40]
	ldr	x0, [x20, 8]
	cbz	x0, .L396
.L306:
	ldr	x0, [x20]
	ldr	w1, [x0, 640]
	str	w1, [x20, 92]
	ldr	w0, [x0, 692]
	str	w0, [x20, 96]
	b	.L363
.L389:
	ldr	w0, [x1, 2440]
	ldr	w21, [x1, 1408]
	sub	w0, w0, w25
	b	.L369
.L387:
	ldr	w3, [x9, 16]
	ldr	w1, [x22, 408]
	ldr	w0, [x26, 16]
	subs	w1, w1, w3
	sub	w0, w0, w3
	bmi	.L397
.L296:
	tbnz	w0, #31, .L398
.L297:
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w0, wzr
	ble	.L329
	sub	w3, w0, w1
	lsl	w4, w1, 14
	lsl	w3, w3, 14
	sdiv	w4, w4, w0
	sdiv	w3, w3, w0
.L299:
	add	x2, x23, 3184
	add	x2, x2, 40960
	add	x7, x2, 2304
	stp	w1, w0, [x7, 180]
	stp	w4, w3, [x7, 188]
	b	.L295
.L385:
	ldr	x2, .LC66
	mov	w3, 1929
	ldr	x1, .LC68
	mov	w0, 22
	mov	w28, 0
	bl	dprint_vfmw
	b	.L363
.L379:
	ldr	w0, [x29, 152]
	cmp	w0, wzr
	bgt	.L264
	ldr	w0, [x29, 148]
	cmp	w0, 32
	bgt	.L264
	ldr	x0, [x20, 8]
	cbnz	x0, .L264
	ldr	w3, [x22, 1552]
	cbz	w3, .L261
	ldr	w4, [x22, 396]
	cbz	w4, .L261
	ldr	w1, [x22, 2332]
	ldr	w7, [x29, 368]
	cmp	w7, w1
	beq	.L261
	ldr	w1, [x22, 2336]
	ldr	w6, [x29, 372]
	cmp	w6, w1
	beq	.L261
	ldr	x1, .LC51
	mov	w0, w2
	ldr	w5, [x22, 392]
	bl	dprint_vfmw
	ldr	w0, [x29, 368]
	str	w0, [x22, 2332]
	ldr	x4, [x21]
	ldr	w0, [x29, 372]
	str	w0, [x22, 2336]
	cbz	x4, .L261
	ldr	w0, [x22, 2328]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 120
	blr	x4
	b	.L261
.L285:
	cmp	w0, 2
	beq	.L325
	cmp	w0, 1
	bne	.L282
	str	w0, [x21, 2584]
	b	.L282
.L391:
	uxtw	x0, w26
	str	w6, [x29, 96]
	add	x0, x0, 8192
	add	x0, x0, 2400
	ldr	w1, [x21, x0, lsl 2]
	ldr	w0, [x27, 2440]
	sub	w0, w0, w25
	b	.L370
.L390:
	add	x21, x21, 40960
	ldr	w0, [x22, 2328]
	mov	w28, 0
	ldr	w1, [x21, 2576]
	bl	FSP_ClearLogicFs
	b	.L363
.L393:
	ldr	w0, [x22, 2328]
	mov	w2, 1
	ldr	w1, [x27, 2576]
	mov	w28, 0
	bl	FSP_ClearLogicFs
	b	.L363
.L392:
	ldr	x1, .LC74
	mov	w2, 2092
	mov	w0, 22
	mov	w28, 0
	bl	dprint_vfmw
	b	.L363
.L395:
	ldrb	w0, [x24, 12]
	cmp	w0, 2
	bne	.L313
	str	xzr, [x20, 8]
	mov	w2, 0
	mov	w28, 0
	ldr	w1, [x22, 1664]
	ldr	w0, [x22, 2328]
	bl	FSP_SetDisplay
	mov	x1, x20
	mov	w0, 8
	bl	ReleasePacket
	b	.L363
.L394:
	ldr	x2, .LC66
	mov	w3, 2125
	ldr	x1, .LC76
	mov	w0, 22
	mov	w28, 0
	bl	dprint_vfmw
	b	.L363
.L289:
	add	x1, x23, 3184
	ldr	w0, [x22, 2328]
	add	x1, x1, 40960
	mov	w2, 1
	mov	w28, 0
	ldr	w1, [x1, 2576]
	bl	FSP_ClearLogicFs
	ldr	x1, .LC70
	mov	w0, 0
	bl	dprint_vfmw
	b	.L363
.L264:
	mov	w28, -2
	b	.L363
.L397:
	ldr	w2, [x22, 404]
	add	w1, w1, w2
	b	.L296
.L388:
	sub	w1, w1, #1
	orr	w1, w1, -8
	add	w1, w1, 1
	b	.L301
.L329:
	mov	w3, 0
	mov	w4, 0
	b	.L299
.L398:
	ldr	w2, [x22, 404]
	add	w0, w0, w2
	b	.L297
.L275:
	ldr	w0, [x22, 2328]
	mov	w2, 1
	ldr	w1, [x26, 2576]
	mov	w28, 0
	bl	FSP_ClearLogicFs
	b	.L363
.L396:
	mov	x0, x20
	bl	Real8_ModifySliceMsg
	cmp	w0, 1
	bne	.L399
	str	x24, [x20, 8]
	b	.L306
.L386:
	ldr	x0, [x21, 32]
	b	.L368
.L291:
	ldr	w5, [x0, 8]
	b	.L292
.L399:
	add	x1, x23, 3184
	ldr	w0, [x22, 2328]
	add	x1, x1, 40960
	mov	w2, w19
	mov	w28, 0
	ldr	w1, [x1, 2576]
	bl	FSP_ClearLogicFs
	b	.L363
	.size	REAL8DEC_Decode, .-REAL8DEC_Decode
	.align	3
.LC42:
	.xword	.LC32
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC45:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC46:
	.xword	.LANCHOR0
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC49:
	.xword	g_event_report
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
.LC61:
	.xword	.LC60
	.align	3
.LC63:
	.xword	.LC62
	.align	3
.LC65:
	.xword	.LC64
	.align	3
.LC66:
	.xword	.LANCHOR1
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
.LC76:
	.xword	.LC75
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_RecycleImage
	.type	REAL8DEC_RecycleImage, %function
REAL8DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L402
	add	x19, x19, 53248
	mov	w1, w20
	mov	w2, 0
	ldr	w0, [x19, 2328]
	bl	FSP_SetDisplay
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L402:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL8DEC_RecycleImage, .-REAL8DEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_GetRemainImg
	.type	REAL8DEC_GetRemainImg, %function
REAL8DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L418
	ldr	x0, [x19]
	add	x20, x19, 53248
	ldr	w0, [x0, 24]
	cmp	w0, 1
	beq	.L406
	mov	x21, 52336
	add	x20, x19, 53248
	add	x21, x19, x21
	ldr	w0, [x20, 2328]
	ldr	w1, [x21, 2572]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	cbz	x0, .L406
	ldr	w0, [x20, 2328]
	ldr	w1, [x21, 2572]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L419
.L406:
	add	x22, x20, 1720
.L409:
	mov	x0, x22
	bl	GetVoLastImageID
.L415:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L419:
	mov	x0, x19
	add	x22, x20, 1720
	bl	Real8_SetImgFormat
	mov	w2, 1
	str	w2, [x23, 180]
	ldr	w0, [x20, 2328]
	ldr	w1, [x21, 2572]
	bl	FSP_SetDisplay
	ldr	w0, [x20, 2328]
	mov	x4, x23
	mov	x3, x22
	mov	x2, x19
	mov	w1, 8
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L407
	ldr	w0, [x20, 2328]
	mov	w2, 0
	ldr	w1, [x21, 2572]
	bl	FSP_SetDisplay
	b	.L409
	.p2align 3
.L418:
	ldr	x1, .LC78
	mov	w2, 2201
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L415
	.p2align 3
.L407:
	ldr	w0, [x23, 152]
	cmp	w0, 100
	bhi	.L406
	ldr	w0, [x23, 68]
	cmp	w0, 31
	bls	.L406
	ldr	w1, [x23, 72]
	mov	w0, 0
	cmp	w1, 31
	bhi	.L415
	b	.L409
	.size	REAL8DEC_GetRemainImg, .-REAL8DEC_GetRemainImg
	.align	3
.LC78:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_VDMPostProc
	.type	REAL8DEC_VDMPostProc, %function
REAL8DEC_VDMPostProc:
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
	cbz	x20, .L445
	ldr	x1, .LC81
	mov	w2, w22
	mov	w0, 22
	add	x21, x20, 53248
	add	x19, x20, 8192
	bl	dprint_vfmw
	add	x25, x19, 3184
	ldr	x2, [x20, 8]
	mov	x1, x20
	mov	w0, 8
	add	x23, x25, 40960
	ldrb	w3, [x2]
	strb	w3, [x21, 280]
	ldr	w2, [x2, 76]
	str	w2, [x21, 284]
	bl	ReleasePacket
	ldr	w0, [x21, 2328]
	ldr	w1, [x23, 2576]
	bl	FSP_GetFsImagePtr
	cbz	x0, .L430
	ldr	w1, [x23, 1292]
	strb	w1, [x19, 3205]
	cmp	w1, 2
	beq	.L423
	and	w24, w24, 31
	str	w24, [x23, 1400]
.L423:
	tbnz	w22, #31, .L431
	mov	w1, 100
	cmp	w22, w1
	csel	w22, w22, w1, le
.L424:
	ldr	x1, .LC83
	str	w22, [x0, 152]
	mov	w0, 22
	bl	dprint_vfmw
	mov	x0, x20
	bl	Real8_SetImgFormat
	ldrb	w1, [x19, 3202]
	add	x0, x19, 3184
	cmp	w1, 2
	beq	.L427
	ldr	x1, [x20]
	ldr	w1, [x1, 24]
	cbnz	w1, .L427
	add	x1, x0, 40960
	ldr	w2, [x1, 1292]
	cmp	w2, 2
	beq	.L427
	ldrb	w0, [x0, 23]
	cmp	w0, 1
	bls	.L432
	ldr	w1, [x1, 2568]
.L428:
	add	x0, x19, 3184
	cmn	w1, #1
	add	x0, x0, 40960
	str	w1, [x0, 2580]
	beq	.L429
.L447:
	add	x22, x19, 3184
	ldr	w0, [x21, 2328]
	add	x22, x22, 40960
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	ldr	w23, [x22, 2580]
	ldr	w0, [x21, 2328]
	mov	w1, w23
	bl	FSP_GetRef
	mov	w3, w0
	ldr	x1, .LC85
	mov	w2, w23
	mov	w0, 12
	bl	dprint_vfmw
	ldr	w0, [x21, 2328]
	mov	w2, 1
	ldr	w1, [x22, 2580]
	bl	FSP_SetDisplay
	ldr	w0, [x21, 2328]
	mov	x4, x24
	add	x3, x21, 1720
	mov	x2, x20
	mov	w1, 8
	bl	InsertImgToVoQueue
	cmp	w0, 1
	bne	.L446
.L429:
	add	x19, x19, 3184
	mov	w0, 1
	add	x19, x19, 40960
	ldr	w1, [x19, 2468]
	add	w1, w1, w0
	str	w1, [x19, 2468]
.L422:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L427:
	add	x0, x19, 3184
	add	x0, x0, 40960
	ldr	w1, [x0, 2576]
	str	w1, [x0, 2580]
	cmn	w1, #1
	bne	.L447
	b	.L429
	.p2align 3
.L431:
	mov	w22, 0
	b	.L424
	.p2align 3
.L446:
	ldr	w0, [x21, 2328]
	mov	w2, 0
	ldr	w1, [x22, 2580]
	bl	FSP_SetDisplay
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L432:
	mov	w1, -1
	b	.L428
	.p2align 3
.L445:
	ldr	x1, .LC79
	mov	w2, 2259
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L430:
	mov	w0, 0
	b	.L422
	.size	REAL8DEC_VDMPostProc, .-REAL8DEC_VDMPostProc
	.align	3
.LC79:
	.xword	.LC32
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC83:
	.xword	.LC82
	.align	3
.LC85:
	.xword	.LC84
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_GetImageBuffer
	.type	REAL8DEC_GetImageBuffer, %function
REAL8DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L455
	add	x19, x19, 53248
	ldr	w0, [x19, 2328]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	mov	w20, w0
	beq	.L450
	ldr	w0, [x19, 2328]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	beq	.L456
.L450:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L456:
	ldr	w0, [x19, 2328]
	add	x1, x19, 1720
	bl	FSP_ClearNotInVoQueue
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L455:
	ldr	x1, .LC86
	mov	w2, 2340
	mov	w0, 0
	mov	w20, 0
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	REAL8DEC_GetImageBuffer, .-REAL8DEC_GetImageBuffer
	.align	3
.LC86:
	.xword	.LC32
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	REAL8DEC_Support
	.type	REAL8DEC_Support, %function
REAL8DEC_Support:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L460
	mov	w0, 1
	str	w0, [x19]
.L457:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L460:
	ldr	x1, .LC87
	mov	w2, 2362
	mov	w0, 0
	bl	dprint_vfmw
	b	.L457
	.size	REAL8DEC_Support, .-REAL8DEC_Support
	.align	3
.LC87:
	.xword	.LC32
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
	.zero	4
.LC2:
	.word	0
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	3
	.zero	4
	.type	s_RVVersionEncodingToMinorVersion, %object
	.size	s_RVVersionEncodingToMinorVersion, 32
s_RVVersionEncodingToMinorVersion:
	.word	2
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.align	3
.LANCHOR1 = . + 0
	.type	__FUNCTION__.11242, %object
	.size	__FUNCTION__.11242, 16
__FUNCTION__.11242:
	.string	"REAL8DEC_Decode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC4:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC6:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC8:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC10:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC12:
	ASCII(.string	"image size abnormal (%dx%d) in MB\n" )
	.zero	5
.LC14:
	ASCII(.string	"real8 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
.LC17:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC32:
	ASCII(.string	"line: %d\n" )
	.zero	6
.LC35:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC38:
	ASCII(.string	"Decoding quits at frm %d\n" )
	.zero	6
.LC43:
	ASCII(.string	"ERROR: frm %d, Invalid packet pointer!\n" )
.LC47:
	ASCII(.string	"Real8_CB_GetPictureHeader Error!\n" )
	.zero	6
.LC50:
	ASCII(.string	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d,new w/h = %d/%d\n" )
	.zero	3
.LC52:
	ASCII(.string	"pic width/height to large,MbWidth = %d, MbHeight = %d" )
	.zero	2
.LC54:
	ASCII(.string	"new seq size %d * %d\n" )
	.zero	2
.LC56:
	ASCII(.string	"Real8_ArrangeVHBMem err\n" )
	.zero	7
.LC58:
	ASCII(.string	"Fatal Error: frm%d, get image buffer failed\n" )
	.zero	3
.LC60:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.zero	2
.LC62:
	ASCII(.string	"---------- unref %d\n" )
	.zero	3
.LC64:
	ASCII(.string	"++++++++++ ref %d\n" )
	.zero	5
.LC67:
	ASCII(.string	"%s %d unknow error!!\n" )
	.zero	2
.LC69:
	ASCII(.string	"CurFsID abnormal!\n" )
	.zero	5
.LC71:
	ASCII(.string	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p,%p,%p,%p,%p\n" )
.LC73:
	ASCII(.string	"line:%d! i > (RV8_MAX_SLC_PARAM_NUM - 2)\n" )
	.zero	6
.LC75:
	ASCII(.string	"%s %d NULL == pCtx->pRv8DecParam!!\n" )
	.zero	4
.LC80:
	ASCII(.string	"ErrRatio = %d\n" )
	.zero	1
.LC82:
	ASCII(.string	"DEBUG: DEC over\n" )
	.zero	7
.LC84:
	ASCII(.string	"insert buf %d ref %d\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
