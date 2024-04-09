#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vc1.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VC1_Vfmw_GenerateIntensityMap, %function
VC1_Vfmw_GenerateIntensityMap:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w2
	mov	w21, w1
	uxtb	w22, w3
	bl	_mcount
	cmp	w20, 32
	sub	w0, w20, #64
	csel	w20, w0, w20, ge
	cbnz	w21, .L3
	lsl	w2, w20, 25
	mov	w4, -64
	sub	w2, w2, w20
	lsl	w2, w2, 7
	add	w2, w2, 12288
	add	w2, w2, 4032
.L4:
	cbnz	w22, .L5
	mov	x0, x19
	add	w2, w2, 32
	add	x5, x19, 256
	mov	w3, 255
	.p2align 2
.L6:
	asr	w1, w2, 6
	add	w2, w2, w4
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	cmp	w1, 255
	csel	w1, w1, w3, le
	strb	w1, [x0], 1
	cmp	x5, x0
	bne	.L6
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L5:
	lsl	w2, w4, 25
	mov	x0, x19
	sub	w2, w2, w4
	add	x5, x19, 256
	lsl	w2, w2, 7
	mov	w3, 255
	add	w2, w2, 8192
	add	w2, w2, 32
	.p2align 2
.L7:
	asr	w1, w2, 6
	add	w2, w2, w4
	cmp	w1, wzr
	csel	w1, w1, wzr, ge
	cmp	w1, 255
	csel	w1, w1, w3, le
	strb	w1, [x0], 1
	cmp	x5, x0
	bne	.L7
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L3:
	add	w4, w21, 32
	lsl	w2, w20, 6
	b	.L4
	.size	VC1_Vfmw_GenerateIntensityMap, .-VC1_Vfmw_GenerateIntensityMap
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	emp_print
	.type	emp_print, %function
emp_print:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	mov	x0, x30
	stp	x2, x3, [x29, 16]
	stp	x4, x5, [x29, 32]
	stp	x6, x7, [x29, 48]
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 64
	ret
	.size	emp_print, .-emp_print
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AbandonBitsLenthNoUse
	.type	AbandonBitsLenthNoUse, %function
AbandonBitsLenthNoUse:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldrb	w1, [x19]
	mov	w0, 0
	cbz	w1, .L22
	b	.L26
	.p2align 3
.L20:
	mov	w0, w2
.L22:
	ldrb	w1, [x19, -1]!
	add	w2, w0, 8
	cbz	w1, .L20
	add	w0, w0, 9
.L18:
	tbz	x1, 0, .L23
	b	.L16
	.p2align 3
.L21:
	mov	w2, w0
.L23:
	lsr	w1, w1, 1
	add	w0, w2, 1
	tbz	x1, 0, .L21
	add	w0, w2, 2
.L16:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L26:
	mov	w0, 1
	mov	w2, 0
	b	.L18
	.size	AbandonBitsLenthNoUse, .-AbandonBitsLenthNoUse
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_Init
	.type	VC1DEC_Init, %function
VC1DEC_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L31
	ldr	x3, .LC14
	add	x19, x20, 53248
	mov	x2, 54152
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	ldr	w22, [x19, 888]
	blr	x3
	str	w22, [x19, 888]
	add	x0, x19, 288
	bl	ResetVoQueue
	add	x4, x20, 12288
	ldr	w1, [x21, 32]
	str	x21, [x20]
	mov	w5, 1
	add	w1, w1, 255
	mov	x0, x20
	strb	w5, [x4, 2529]
	and	w1, w1, -256
	add	w3, w1, 4096
	add	w2, w1, 8192
	ldr	w6, [x21, 8]
	str	w6, [x19, 236]
	add	w6, w1, 2048
	str	w1, [x19, 208]
	add	w1, w1, 12288
	str	w3, [x19, 216]
	add	w3, w3, 2048
	str	w2, [x19, 224]
	add	w2, w2, 2048
	str	w6, [x19, 212]
	str	w3, [x19, 220]
	stp	w2, w1, [x19, 228]
	strb	w5, [x4, 2530]
	stp	wzr, wzr, [x19, 168]
	bl	VCTRL_GetChanIDByCtx
	cmn	w0, #1
	str	w0, [x19, 896]
	beq	.L32
	ldr	x1, .LC18
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1
.L29:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L31:
	ldr	x1, .LC13
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -2
	b	.L29
	.p2align 3
.L32:
	ldr	x1, .LC16
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L29
	.size	VC1DEC_Init, .-VC1DEC_Init
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC14:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC16:
	.xword	.LC15
	.align	3
.LC18:
	.xword	.LC17
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Vc1SMPSeqHdr
	.type	Vc1SMPSeqHdr, %function
Vc1SMPSeqHdr:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x2
	mov	w21, w1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L47
	lsl	w2, w21, 3
	mov	x1, x20
	add	x0, x29, 56
	bl	BsInit
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w20, w20, w0, lsl 8
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w20, w20, w0, lsl 16
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w0, w20, w0, lsl 24
	mov	w1, 8
	str	w0, [x19, 8]
	add	x0, x29, 56
	bl	BsGet
	mov	w20, w0
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w20, w20, w0, lsl 8
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w20, w20, w0, lsl 16
	mov	w1, 8
	add	x0, x29, 56
	bl	BsGet
	add	w0, w20, w0, lsl 24
	ldr	w1, [x19, 8]
	str	w0, [x19, 12]
	cmp	w1, 8192
	bgt	.L38
	cmp	w0, 8192
	bgt	.L39
	cmp	w1, 31
	ble	.L38
	cmp	w0, 31
	ble	.L39
	mov	w1, 2
	add	x0, x29, 56
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 16]
	bhi	.L41
	mov	w1, 2
	add	x0, x29, 56
	bl	BsGet
	cbnz	w0, .L41
	mov	w1, 3
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 17]
	mov	w1, 5
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 18]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 19]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	cbnz	w0, .L41
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 20]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 22]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 23]
	mov	w1, 2
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 25]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	mov	w20, w0
	cbnz	w0, .L41
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 26]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 27]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 28]
	ldrb	w1, [x19, 16]
	cbnz	w1, .L42
	strb	wzr, [x19, 28]
.L42:
	mov	w1, 3
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 29]
	mov	w1, 2
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 30]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	strb	w0, [x19, 31]
	mov	w1, 1
	add	x0, x29, 56
	bl	BsGet
	mov	w1, 32
	add	x0, x29, 56
	bl	BsGet
	cbnz	w0, .L48
.L35:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L48:
	ldr	x1, .LC31
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L41:
	ldr	x3, .LC29
.L46:
	ldr	x2, .LC23
	mov	w0, 0
	ldr	x1, .LC25
	mov	w20, -1
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L39:
	ldr	x3, .LC27
	b	.L46
	.p2align 3
.L47:
	ldr	x1, .LC20
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L35
	.p2align 3
.L38:
	ldr	x3, .LC22
	b	.L46
	.size	Vc1SMPSeqHdr, .-Vc1SMPSeqHdr
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC23:
	.xword	.LANCHOR0
	.align	3
.LC25:
	.xword	.LC24
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC31:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_SetImgFormat
	.type	VC1_SetImgFormat, %function
VC1_SetImgFormat:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	add	x20, x21, 12288
	bl	_mcount
	add	x22, x20, 2520
	add	x1, x22, 20480
	add	x0, x21, 53248
	ldr	w1, [x1, 3716]
	ldr	w0, [x0, 896]
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L49
	mov	w23, 1
	str	w23, [x0, 296]
	ldrsb	w0, [x20, 2523]
	cmp	w0, 3
	beq	.L58
	ldr	x3, .LC32
	mov	x2, 4
	strb	wzr, [x19, 284]
	mov	w1, 0
	add	x0, x19, 64
	ldr	x3, [x3, 96]
	blr	x3
	ldrb	w0, [x19, 65]
	orr	w0, w0, 12
	bfi	w0, w23, 4, 2
	strb	w0, [x19, 65]
.L53:
	add	x20, x20, 2520
	ldrb	w3, [x19, 66]
	add	x2, x20, 36864
	add	x20, x20, 20480
	mov	w1, 0
	mov	x0, x19
	ldrb	w4, [x2, 1817]
	bfi	w3, w4, 1, 1
	strb	w3, [x19, 66]
	ldr	w2, [x2, 1820]
	str	w2, [x19, 120]
	ldr	w2, [x20, 3660]
	str	w2, [x19, 72]
	ldr	w2, [x20, 3656]
	str	w2, [x19, 68]
	bl	SetAspectRatio
	ldr	w2, [x21, 14592]
	ldr	w1, [x19, 36]
	ldr	w3, [x19, 112]
	ldr	x4, [x19, 504]
	add	w0, w2, w1
	stp	w1, w0, [x19, 20]
	str	w0, [x19, 40]
	add	w1, w3, w1
	add	w0, w3, w0
	add	x2, x4, x2, uxtw
	stp	w1, w0, [x19, 28]
	str	x2, [x19, 512]
	mov	w1, 8
	ldr	w0, [x19, 68]
	mov	w2, 1
	ldr	w3, [x20, 3660]
	str	w3, [x19, 80]
	add	w0, w0, 511
	and	w0, w0, -512
	ldr	w3, [x20, 3656]
	lsr	w0, w0, 5
	strb	w2, [x19, 291]
	strb	w2, [x19, 289]
	str	w3, [x19, 76]
	str	w0, [x19, 136]
	str	w1, [x19, 300]
	str	w1, [x19, 304]
	str	w1, [x19, 308]
.L49:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L58:
	mov	w0, 4
	strb	w0, [x19, 284]
	ldrb	w1, [x19, 65]
	mov	w5, 0
	ldrb	w3, [x21, 24]
	ubfx	x2, x1, 2, 2
	mov	x0, x1
	add	w1, w3, w23
	orr	w1, w1, w2
	and	w2, w1, 3
	cmp	w1, 3
	csel	w1, w2, w5, ls
	bfi	w0, w1, 2, 2
	bfi	w0, w23, 0, 2
	bfi	w0, w23, 4, 2
	strb	w0, [x19, 65]
	b	.L53
	.size	VC1_SetImgFormat, .-VC1_SetImgFormat
	.align	3
.LC32:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_Destroy
	.type	VC1DEC_Destroy, %function
VC1DEC_Destroy:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VC1DEC_Destroy, .-VC1DEC_Destroy
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_RecycleImage
	.type	VC1DEC_RecycleImage, %function
VC1DEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L64
	add	x19, x19, 53248
	mov	w1, w20
	mov	w2, 0
	ldr	w0, [x19, 896]
	bl	FSP_SetDisplay
	ldr	w0, [x19, 896]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L63
	ldr	w0, [x19, 896]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 896]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L63:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L64:
	ldr	x1, .LC34
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1DEC_RecycleImage, .-VC1DEC_RecycleImage
	.align	3
.LC34:
	.xword	.LC33
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_GetRemainImg
	.type	VC1DEC_GetRemainImg, %function
VC1DEC_GetRemainImg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L82
	add	x20, x19, 12288
	add	x20, x20, 2520
	ldr	x0, [x20, 24096]
	cbz	x0, .L73
	ldr	x0, [x19]
	add	x21, x19, 53248
	ldr	w0, [x0, 24]
	cmp	w0, 1
	beq	.L68
	add	x23, x20, 20480
	add	x21, x19, 53248
	ldr	w1, [x23, 3712]
	ldr	w0, [x21, 896]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L68
	ldr	w0, [x21, 896]
	ldr	w1, [x23, 3712]
	bl	FSP_GetDisplay
	cmp	w0, 2
	beq	.L83
.L68:
	add	x20, x21, 288
.L72:
	mov	x0, x20
	bl	GetVoLastImageID
.L79:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L83:
	mov	x0, x19
	bl	VC1_SetImgFormat
	str	xzr, [x22, 544]
	mov	w2, 1
	str	xzr, [x22, 552]
	str	w2, [x22, 180]
	ldr	w1, [x22, 148]
	ldr	w0, [x21, 896]
	bl	FSP_SetDisplay
	ldr	x0, [x20, 24096]
	ldrb	w1, [x0]
	cmp	w1, 1
	beq	.L84
.L69:
	add	x20, x21, 288
	ldr	w0, [x21, 896]
	mov	x4, x22
	mov	x3, x20
	mov	x2, x19
	mov	w1, 1
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L70
	ldr	w1, [x22, 148]
	mov	x0, x19
	bl	VC1DEC_RecycleImage
	ldr	w0, [x21, 896]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x21, 896]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	b	.L72
	.p2align 3
.L70:
	ldr	w0, [x22, 152]
	cmp	w0, 100
	bhi	.L68
	ldr	w0, [x22, 68]
	cmp	w0, 31
	bls	.L68
	ldr	w1, [x22, 72]
	mov	w0, 0
	cmp	w1, 31
	bhi	.L79
	b	.L72
	.p2align 3
.L84:
	strb	w1, [x0, 1]
	mov	w0, 3
	ldr	x1, [x20, 24096]
	strb	wzr, [x1]
	strb	w0, [x20, 1]
	b	.L69
.L73:
	mov	w0, -1
	b	.L79
.L82:
	ldr	x3, .LC36
	mov	w2, 397
	ldr	x1, .LC38
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L79
	.size	VC1DEC_GetRemainImg, .-VC1DEC_GetRemainImg
	.align	3
.LC36:
	.xword	.LC35
	.align	3
.LC38:
	.xword	.LC37
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_ArrangeVahbMem
	.type	VC1_ArrangeVahbMem, %function
VC1_ArrangeVahbMem:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w1
	mov	w23, w2
	bl	_mcount
	sub	w1, w21, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L86
	sub	w1, w23, #32
	cmp	w1, w0
	bhi	.L86
	add	x0, x22, 28672
	mov	w1, 0
	add	x0, x0, 144
	.p2align 2
.L89:
	str	w1, [x0, 1188]
	add	w1, w1, 1
	strb	wzr, [x0, 1]
	cmp	w1, 5
	strb	wzr, [x0]
	add	x0, x0, 1680
	bne	.L89
	ldr	x0, [x22]
	ldr	w19, [x0, 772]
	ldr	w2, [x0, 28]
	cmp	w2, 25
	cbnz	w19, .L90
	beq	.L116
.L110:
	mov	w19, w1
	mov	w24, 3
	mov	w20, 2
.L91:
	ldr	x0, .LC45
	mov	x2, 20
	mov	w1, 0
	ldr	x3, [x0, 96]
	add	x0, x29, 72
	blr	x3
	ldr	x0, [x22]
	stp	w21, w23, [x29, 76]
	stp	w21, w23, [x29, 84]
	ldr	w0, [x0, 28]
	cmp	w0, 24
	beq	.L101
	strb	w19, [x29, 74]
	sxtb	w19, w20
	strb	w24, [x29, 73]
.L106:
	add	x20, x22, 53248
	add	x1, x29, 72
	strb	w19, [x29, 75]
	ldr	w0, [x20, 896]
	bl	FSP_ConfigInstance
	mov	w19, w0
	cbnz	w0, .L102
	ldr	x1, [x22]
	add	x3, x29, 68
	ldr	w0, [x20, 896]
	ldr	w2, [x1, 20]
	ldr	w1, [x1, 16]
	bl	FSP_ConfigFrameBuf
	cmp	w0, 2
	beq	.L117
	cbnz	w0, .L104
	mov	w19, 1
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L86:
	ldr	x1, .LC42
	mov	w3, w23
	mov	w2, w21
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
.L112:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L90:
	bne	.L110
	ldr	w4, [x0, 732]
	ldr	w5, [x0, 736]
	cmp	w21, w4
	bhi	.L98
	cmp	w23, w5
	bhi	.L98
	ldr	w2, [x0, 760]
	mov	w20, 1
	ldr	w1, [x0, 756]
	add	w24, w1, 2
	cbnz	w2, .L118
	ldrsb	w19, [x0, 780]
	b	.L91
	.p2align 3
.L102:
	ldr	x1, .LC49
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L116:
	ldr	w4, [x0, 732]
	cmp	w21, w4
	bhi	.L119
	ldr	w1, [x0, 736]
	cmp	w23, w1
	mov	w5, w1
	bhi	.L93
	add	x2, x22, 12288
	mov	w19, 1
	ldrb	w2, [x2, 2520]
	tbnz	x2, 3, .L112
	ldr	w3, [x0, 760]
	mov	w20, w19
	ldr	w2, [x0, 756]
	add	w24, w2, 2
	cbz	w3, .L96
	add	w2, w2, w19
	mov	w19, 17
	cmp	w2, w19
	csel	w20, w2, w19, ls
.L96:
	ldrsb	w19, [x0, 780]
	mov	w23, w1
	mov	w21, w4
	b	.L91
	.p2align 3
.L101:
	mov	w0, 1
	strb	w19, [x29, 74]
	strb	w0, [x29, 73]
	mov	w19, 1
	b	.L106
	.p2align 3
.L98:
	ldr	x1, .LC44
	mov	w3, w23
	mov	w2, w21
	mov	w0, 0
	mov	w19, 0
	bl	dprint_vfmw
	b	.L112
	.p2align 3
.L117:
	add	x0, x20, 288
	bl	ResetVoQueue
.L104:
	ldr	x1, .LC47
	mov	w0, 0
	bl	dprint_vfmw
	b	.L112
	.p2align 3
.L118:
	mov	w19, 17
	add	w1, w1, w20
	cmp	w1, w19
	csel	w20, w1, w19, ls
	ldrsb	w19, [x0, 780]
	b	.L91
.L119:
	ldr	w5, [x0, 736]
.L93:
	ldr	x1, .LC44
	mov	w3, w23
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	b	.L112
	.size	VC1_ArrangeVahbMem, .-VC1_ArrangeVahbMem
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC44:
	.xword	.LC43
	.align	3
.LC45:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC47:
	.xword	.LC46
	.align	3
.LC49:
	.xword	.LC48
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_WritePicMsg
	.type	VC1_WritePicMsg, %function
VC1_WritePicMsg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 12288
	mov	x19, x1
	add	x21, x20, 2520
	bl	_mcount
	add	x22, x22, 53248
	add	x1, x21, 20480
	ldr	w0, [x22, 896]
	ldr	w1, [x1, 3716]
	bl	FSP_GetLogicFs
	cbz	x0, .L145
	ldrsb	w1, [x21, 3104]
	cbz	w1, .L123
	ldr	w2, [x21, 10804]
	add	x1, x21, 8192
	strb	w2, [x19, 5]
	mov	w2, 3
	ldrb	w3, [x1, 2224]
	strb	w3, [x19, 4]
	ldrb	w1, [x1, 2569]
	cmp	w1, 4
	csel	w1, w1, w2, ne
	strb	w1, [x19, 3]
	ldr	w1, [x21, 10804]
	add	x21, x21, 36864
	cmp	w1, w2
	ldr	w1, [x21, 1764]
	beq	.L146
	sub	w1, w1, #1
	strh	w1, [x19, 84]
.L126:
	add	x2, x20, 2520
	add	x3, x2, 36864
	add	x1, x2, 8192
	add	x5, x2, 20480
	ldr	w3, [x3, 1760]
	sub	w3, w3, #1
	strh	w3, [x19, 82]
	ldrb	w3, [x1, 2609]
	strb	w3, [x19, 8]
	ldrb	w3, [x1, 2400]
	strb	w3, [x19, 6]
	ldrb	w3, [x1, 2600]
	strb	w3, [x19, 9]
	ldrb	w3, [x20, 2528]
	strb	w3, [x19, 7]
	ldrsw	x4, [x5, 3680]
	lsl	x3, x4, 3
	sub	x4, x3, x4
	lsl	x3, x4, 4
	sub	x3, x3, x4
	add	x3, x2, x3, lsl 4
	add	x3, x3, 12288
	ldrb	w3, [x3, 2747]
	strb	w3, [x19, 10]
	ldrsw	x4, [x5, 3696]
	lsl	x3, x4, 3
	sub	x4, x3, x4
	lsl	x3, x4, 4
	sub	x3, x3, x4
	add	x3, x2, x3, lsl 4
	add	x3, x3, 12288
	ldrb	w3, [x3, 2747]
	strb	w3, [x19, 11]
	ldrb	w3, [x1, 2598]
	strb	w3, [x19, 15]
	ldrb	w3, [x1, 2401]
	strb	w3, [x19, 13]
	ldrb	w3, [x1, 2405]
	strb	w3, [x19, 14]
	ldrb	w3, [x1, 2568]
	strb	w3, [x19, 12]
	ldrb	w3, [x1, 2736]
	strb	w3, [x19, 18]
	ldrb	w3, [x1, 2571]
	strb	w3, [x19, 19]
	ldrb	w3, [x1, 2578]
	strb	w3, [x19, 17]
	ldr	w2, [x20, 13396]
	strb	w2, [x19, 16]
	ldrb	w2, [x1, 2406]
	cbnz	w2, .L127
	ldrb	w1, [x1, 2578]
	cmp	w1, 8
	cset	w1, ls
	strb	w1, [x19, 20]
.L128:
	add	x2, x20, 2520
	add	x1, x2, 8192
	add	x4, x2, 36864
	ldrb	w3, [x1, 2730]
	strb	w3, [x19, 24]
	ldrb	w3, [x1, 2729]
	strb	w3, [x19, 23]
	ldrb	w3, [x1, 2403]
	strb	w3, [x19, 22]
	ldrb	w3, [x1, 2728]
	strb	w3, [x19, 25]
	ldr	w3, [x20, 13452]
	strb	w3, [x19, 26]
	ldrb	w3, [x1, 2731]
	strb	w3, [x19, 21]
	ldrb	w3, [x1, 2582]
	strb	w3, [x19, 27]
	ldrb	w3, [x1, 2583]
	strb	w3, [x19, 28]
	ldrb	w3, [x1, 2601]
	strb	w3, [x19, 34]
	ldrb	w3, [x1, 2593]
	strb	w3, [x19, 33]
	ldr	x5, [x20, 26616]
	ldrb	w3, [x1, 2609]
	add	x3, x5, x3
	ldrb	w3, [x3, 1029]
	strb	w3, [x19, 30]
	ldrb	w3, [x1, 2609]
	ldr	x5, [x20, 26608]
	add	x3, x5, x3
	ldrb	w3, [x3, 1029]
	strb	w3, [x19, 29]
	ldrb	w3, [x1, 2581]
	strb	w3, [x19, 31]
	ldrb	w3, [x1, 2599]
	strb	w3, [x19, 32]
	ldrb	w3, [x1, 2592]
	strb	w3, [x19, 35]
	ldrb	w3, [x1, 2404]
	strb	w3, [x19, 36]
	ldrb	w3, [x1, 2588]
	strb	w3, [x19, 37]
	ldrb	w3, [x1, 2590]
	strb	w3, [x19, 38]
	ldrb	w3, [x1, 2591]
	strb	w3, [x19, 39]
	ldrb	w3, [x1, 2589]
	strb	w3, [x19, 40]
	ldrb	w3, [x1, 2605]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 46]
	ldrb	w3, [x1, 2603]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 42]
	ldrb	w3, [x1, 2607]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 44]
	ldrb	w3, [x1, 2608]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 41]
	ldrb	w3, [x1, 2602]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 43]
	ldrb	w3, [x1, 2606]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 47]
	ldrb	w3, [x1, 2604]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 45]
	ldrb	w3, [x1, 2570]
	strb	w3, [x19, 50]
	ldrb	w3, [x1, 2587]
	strb	w3, [x19, 49]
	ldrb	w3, [x1, 2586]
	strb	w3, [x19, 48]
	ldrb	w3, [x1, 2597]
	strb	w3, [x19, 53]
	ldrb	w3, [x1, 2594]
	strb	w3, [x19, 54]
	ldrb	w3, [x1, 2595]
	strb	w3, [x19, 51]
	ldrb	w3, [x1, 2596]
	strb	w3, [x19, 52]
	ldr	w3, [x20, 13428]
	str	w3, [x19, 14424]
	ldr	w3, [x4, 1736]
	str	w3, [x19, 14428]
	ldr	w3, [x4, 1740]
	str	w3, [x19, 14432]
	ldrb	w3, [x1, 2409]
	strb	w3, [x19, 55]
	ldrb	w3, [x1, 2410]
	strb	w3, [x19, 56]
	ldrb	w3, [x1, 2411]
	strb	w3, [x19, 57]
	ldrb	w3, [x1, 2412]
	strb	w3, [x19, 58]
	ldr	w2, [x20, 13324]
	cmp	w2, 3
	beq	.L147
	ldrb	w2, [x1, 2409]
	strb	w2, [x0, 333]
	ldrb	w2, [x1, 2410]
	strb	w2, [x0, 334]
	ldrb	w2, [x1, 2411]
	strb	w2, [x0, 335]
	ldrb	w1, [x1, 2412]
	strb	w1, [x0, 336]
.L133:
	add	x1, x20, 2520
	add	x2, x1, 8192
	ldrb	w2, [x2, 2224]
	strb	w2, [x0, 338]
	ldrb	w0, [x20, 2531]
	strb	w0, [x19, 63]
	b	.L134
	.p2align 3
.L123:
	add	x1, x21, 8192
	strb	wzr, [x19, 5]
	add	x3, x21, 36864
	mov	w4, 3
	ldrb	w2, [x1, 2208]
	strb	w2, [x19, 4]
	ldrb	w2, [x1, 2459]
	cmp	w2, 4
	csel	w2, w2, w4, ne
	strb	w2, [x19, 3]
	ldr	w2, [x3, 1764]
	sub	w2, w2, #1
	strh	w2, [x19, 84]
	ldr	w2, [x3, 1760]
	strb	wzr, [x19, 8]
	sub	w2, w2, #1
	strh	w2, [x19, 82]
	ldrb	w2, [x1, 2211]
	strb	w2, [x19, 6]
	strb	wzr, [x19, 9]
	ldrb	w2, [x21, 8]
	strb	w2, [x19, 7]
	strb	wzr, [x19, 10]
	strb	wzr, [x19, 11]
	ldrb	w2, [x1, 2214]
	strb	w2, [x19, 13]
	ldrb	w2, [x1, 2218]
	strb	w2, [x19, 14]
	ldrb	w2, [x1, 2478]
	strb	w2, [x19, 12]
	ldrb	w2, [x1, 2488]
	strb	w2, [x19, 18]
	ldrb	w2, [x1, 2463]
	strb	w2, [x19, 19]
	ldrb	w2, [x1, 2462]
	strb	w2, [x19, 17]
	ldr	w2, [x21, 10752]
	strb	w2, [x19, 16]
	ldrb	w2, [x1, 2222]
	cbnz	w2, .L136
	ldrb	w1, [x1, 2462]
	cmp	w1, 8
	cset	w1, ls
	strb	w1, [x19, 20]
.L137:
	add	x2, x20, 2520
	add	x1, x2, 8192
	ldrb	w3, [x1, 2482]
	strb	w3, [x19, 24]
	ldrb	w3, [x1, 2481]
	strb	w3, [x19, 23]
	ldrb	w3, [x1, 2216]
	strb	w3, [x19, 22]
	ldrb	w3, [x1, 2480]
	strb	w3, [x19, 25]
	ldr	w3, [x20, 13204]
	strb	w3, [x19, 26]
	ldrb	w3, [x1, 2483]
	strb	w3, [x19, 21]
	ldrb	w3, [x1, 2467]
	strb	w3, [x19, 27]
	ldrb	w3, [x1, 2468]
	strb	w3, [x19, 28]
	ldr	x3, [x20, 26616]
	ldrb	w3, [x3, 1029]
	strb	w3, [x19, 30]
	ldr	x3, [x20, 26608]
	ldrb	w3, [x3, 1029]
	strb	w3, [x19, 29]
	ldrb	w3, [x1, 2465]
	strb	w3, [x19, 31]
	ldrb	w3, [x1, 2599]
	strb	w3, [x19, 32]
	ldrb	w3, [x1, 2477]
	strb	w3, [x19, 35]
	ldrb	w3, [x1, 2217]
	strb	w3, [x19, 36]
	ldrb	w3, [x1, 2473]
	strb	w3, [x19, 37]
	ldrb	w3, [x1, 2475]
	strb	w3, [x19, 38]
	ldrb	w3, [x1, 2476]
	strb	w3, [x19, 39]
	ldrb	w3, [x1, 2474]
	strb	w3, [x19, 40]
	ldr	w3, [x20, 13264]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 42]
	ldr	w3, [x20, 13260]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 43]
	ldr	w3, [x20, 13268]
	cmp	w3, wzr
	cset	w3, eq
	strb	w3, [x19, 45]
	ldrb	w3, [x1, 2460]
	strb	w3, [x19, 50]
	ldrb	w3, [x1, 2472]
	strb	w3, [x19, 49]
	ldrb	w3, [x1, 2471]
	strb	w3, [x19, 48]
	ldr	w3, [x20, 13276]
	str	w3, [x19, 14424]
	ldrb	w3, [x1, 2220]
	cmp	w3, 1
	beq	.L148
	mov	w5, 0
	mov	w2, 0
	mov	w4, 0
	mov	w3, 0
.L140:
	add	x1, x20, 2520
	strb	w3, [x19, 59]
	strb	w4, [x19, 60]
	add	x1, x1, 8192
	strb	w2, [x19, 61]
	str	w5, [x0, 360]
	ldrb	w1, [x1, 2208]
	strb	w1, [x0, 338]
.L134:
	add	x2, x20, 2520
	add	x20, x20, 2533
	add	x0, x2, 20480
	add	x1, x2, 36864
	ldr	x5, .LC52
	ldrh	w4, [x19, 82]
	ldr	w3, [x0, 3724]
	strh	w3, [x19, 76]
	add	w4, w4, 1
	ldr	w3, [x0, 3656]
	strh	w3, [x19, 78]
	ldr	w3, [x0, 3660]
	strh	w3, [x19, 80]
	ldrb	w3, [x2, 11]
	strb	w3, [x19, 63]
	ldrb	w2, [x2, 12]
	strb	w2, [x19, 62]
	ldr	w2, [x0, 3640]
	add	w3, w2, 254
	adds	w2, w2, 127
	csel	w2, w3, w2, mi
	asr	w2, w2, 7
	lsl	w2, w2, 4
	str	w2, [x19, 14456]
	ldr	w0, [x1, 1784]
	str	w0, [x19, 14460]
	ldr	w0, [x1, 1788]
	str	w0, [x19, 14464]
	ldr	w0, [x1, 1792]
	str	w0, [x19, 14468]
	ldr	w0, [x1, 1796]
	str	w0, [x19, 14472]
	ldr	w0, [x1, 1800]
	str	w0, [x19, 14476]
	ldr	w0, [x1, 1804]
	str	w0, [x19, 14480]
	ldr	w0, [x1, 1808]
	str	w0, [x19, 14484]
	str	x20, [x19, 64]
	ldrsw	x0, [x22, 896]
	ldr	x0, [x5, x0, lsl 3]
	str	w4, [x0, 1604]
	ldrsw	x1, [x22, 896]
	ldrh	w0, [x19, 84]
	ldr	x1, [x5, x1, lsl 3]
	add	w0, w0, 1
	str	w0, [x1, 1608]
.L120:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L136:
	cmp	w2, 1
	beq	.L149
	cmp	w2, 2
	beq	.L150
	mov	w1, 1
	strb	w1, [x19, 20]
	b	.L137
	.p2align 3
.L127:
	cmp	w2, 1
	beq	.L151
	cmp	w2, 2
	beq	.L152
	mov	w1, 1
	strb	w1, [x19, 20]
	b	.L128
	.p2align 3
.L151:
	ldrb	w1, [x1, 2579]
	cmp	w1, wzr
	cset	w1, ne
	strb	w1, [x19, 20]
	b	.L128
	.p2align 3
.L149:
	ldrb	w1, [x1, 2464]
	cmp	w1, wzr
	cset	w1, ne
	strb	w1, [x19, 20]
	b	.L137
	.p2align 3
.L147:
	ldrb	w2, [x1, 2609]
	cbnz	w2, .L132
	ldrb	w2, [x1, 2409]
	strb	w2, [x0, 333]
	ldrb	w2, [x1, 2410]
	strb	w2, [x0, 334]
	ldrb	w2, [x1, 2411]
	strb	w2, [x0, 335]
	ldrb	w2, [x1, 2412]
	strb	w2, [x0, 336]
	ldrb	w2, [x1, 2609]
.L132:
	cmp	w2, 1
	bne	.L133
	add	x1, x20, 2520
	add	x1, x1, 8192
	ldrb	w2, [x1, 2409]
	strb	w2, [x0, 328]
	ldrb	w2, [x1, 2410]
	strb	w2, [x0, 329]
	ldrb	w2, [x1, 2411]
	strb	w2, [x0, 330]
	ldrb	w1, [x1, 2412]
	strb	w1, [x0, 331]
	b	.L133
	.p2align 3
.L146:
	add	w1, w1, 1
	add	w1, w1, w1, lsr 31
	asr	w1, w1, 1
	sub	w1, w1, #1
	strh	w1, [x19, 84]
	b	.L126
	.p2align 3
.L148:
	add	x3, x2, 20480
	ldr	w5, [x3, 3680]
	ldr	w4, [x3, 3696]
	lsl	x3, x5, 3
	sub	x6, x3, x5
	lsl	x3, x4, 3
	sub	x4, x3, x4
	lsl	x5, x6, 4
	lsl	x3, x4, 4
	sub	x5, x5, x6
	sub	x4, x3, x4
	ldrb	w3, [x1, 2459]
	add	x5, x2, x5, lsl 4
	sub	w3, w3, #2
	add	x2, x2, x4, lsl 4
	and	w3, w3, -3
	add	x4, x5, 12288
	add	x2, x2, 12288
	uxtb	w3, w3
	ldrb	w4, [x4, 1722]
	ldrb	w2, [x2, 1722]
	cbnz	w3, .L141
	mov	w5, w2
	mov	w3, w2
	b	.L140
	.p2align 3
.L141:
	ldrb	w3, [x1, 2458]
	mov	w5, w3
	b	.L140
	.p2align 3
.L150:
	strb	wzr, [x19, 20]
	b	.L137
	.p2align 3
.L152:
	strb	wzr, [x19, 20]
	b	.L128
	.p2align 3
.L145:
	ldr	x1, .LC51
	mov	w2, 916
	mov	w0, 22
	bl	dprint_vfmw
	b	.L120
	.size	VC1_WritePicMsg, .-VC1_WritePicMsg
	.align	3
.LC51:
	.xword	.LC50
	.align	3
.LC52:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_WriteSliceMsg
	.type	VC1_WriteSliceMsg, %function
VC1_WriteSliceMsg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x2, x19, 20480
	ldr	x4, .LC53
	add	x1, x2, 3728
	add	x0, x20, 88
	ldr	w3, [x2, 3724]
	strb	w3, [x20, 74]
	ldr	w3, [x2, 3724]
	ldr	x4, [x4, 104]
	lsl	x2, x3, 3
	sub	x2, x2, x3
	lsl	x2, x2, 3
	blr	x4
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_WriteSliceMsg, .-VC1_WriteSliceMsg
	.align	3
.LC53:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_CfgVDH
	.type	VC1_CfgVDH, %function
VC1_CfgVDH:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldrsb	w0, [x19, 3104]
	cbz	w0, .L155
	ldr	w0, [x19, 10804]
	cmp	w0, 3
	beq	.L160
.L155:
	add	x0, x19, 36864
	ldr	w0, [x0, 1768]
	sub	w0, w0, #1
	str	w0, [x20, 14504]
.L156:
	add	x1, x19, 20480
	ldr	w3, [x20, 14600]
	mov	w0, 16385
	movk	w0, 0x2001, lsl 16
	ubfiz	w3, w3, 30, 1
	ldr	w4, [x1, 3664]
	cmp	w4, wzr
	add	w2, w4, 63
	csel	w2, w2, w4, lt
	asr	w2, w2, 6
	add	w0, w0, w2, lsl 4
	orr	w0, w0, w3
	str	w0, [x20, 14508]
	ldrsw	x4, [x1, 3696]
	ldrsw	x2, [x1, 3680]
	lsl	x1, x4, 3
	ldr	x5, [x19, 24088]
	sub	x4, x1, x4
	lsl	x0, x2, 3
	lsl	x3, x4, 4
	sub	x2, x0, x2
	sub	x4, x3, x4
	lsl	x0, x2, 4
	sub	x2, x0, x2
	ldr	w0, [x5, 1092]
	add	x4, x19, x4, lsl 4
	and	w0, w0, 3
	add	x19, x19, x2, lsl 4
	ubfiz	w3, w0, 4, 4
	ldr	w0, [x4, 15100]
	ldr	w2, [x19, 15100]
	and	w0, w0, 3
	strb	wzr, [x20, 73]
	and	w2, w2, 3
	orr	w0, w3, w0, lsl 2
	orr	w0, w0, w2
	strb	w0, [x20, 72]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L160:
	add	x0, x19, 36864
	ldr	w1, [x0, 1764]
	ldr	w2, [x0, 1760]
	add	w0, w1, 1
	add	w0, w0, w0, lsr 31
	asr	w0, w0, 1
	mul	w0, w0, w2
	sub	w0, w0, #1
	str	w0, [x20, 14504]
	b	.L156
	.size	VC1_CfgVDH, .-VC1_CfgVDH
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_GenerateDecPara
	.type	VC1_Vfmw_GenerateDecPara, %function
VC1_Vfmw_GenerateDecPara:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VC1_Vfmw_GenerateDecPara, .-VC1_Vfmw_GenerateDecPara
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_GetImageBuffer
	.type	VC1DEC_GetImageBuffer, %function
VC1DEC_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L174
	add	x0, x19, 12288
	add	x0, x0, 2520
	ldrsb	w1, [x0, 3]
	cmp	w1, 3
	beq	.L175
.L165:
	add	x19, x19, 53248
	ldr	w0, [x19, 896]
	bl	FSP_IsNewFsAvalible
	cmp	w0, 1
	beq	.L166
	ldr	w0, [x19, 896]
	mov	w20, 0
	bl	FSP_IsNewFsAvalible
	cmn	w0, #1
	bne	.L164
	ldr	w0, [x19, 896]
	add	x1, x19, 288
	bl	FSP_ClearNotInVoQueue
	b	.L164
	.p2align 3
.L175:
	ldrb	w0, [x0, 9]
	cmp	w0, 1
	beq	.L165
.L166:
	mov	w20, 1
.L164:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L174:
	ldr	x3, .LC54
	mov	w2, 1794
	ldr	x1, .LC55
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L164
	.size	VC1DEC_GetImageBuffer, .-VC1DEC_GetImageBuffer
	.align	3
.LC54:
	.xword	.LC35
	.align	3
.LC55:
	.xword	.LC37
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_GetImageBuffer
	.type	VC1_Vfmw_GetImageBuffer, %function
VC1_Vfmw_GetImageBuffer:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	add	x22, x21, 53248
	add	x19, x21, 12288
	bl	_mcount
	mov	w1, 1
	ldr	w0, [x22, 896]
	bl	FSP_NewLogicFs
	mov	w1, w0
	add	x0, x19, 2520
	add	x20, x0, 20480
	str	w1, [x20, 3716]
	tbnz	w1, #31, .L196
	add	x20, x21, 28672
	add	x0, x0, 12288
	add	x0, x0, 1720
	ldrh	w2, [x20, 144]
	cbz	w2, .L186
	add	x21, x21, 36864
	add	x0, x20, 1824
	add	x4, x21, 352
.L183:
	ldrh	w3, [x0]
	mov	x2, x0
	add	x0, x0, 1680
	cmp	x0, x4
	cbz	w3, .L180
	bne	.L183
	ldr	w0, [x22, 896]
	mov	w2, 1
	add	x21, x21, 353
	bl	FSP_ClearLogicFs
	ldr	x1, .LC61
	mov	w0, 1
	bl	dprint_vfmw
	add	x0, x20, 145
.L185:
	strb	wzr, [x0]
	strb	wzr, [x0, -1]
	add	x0, x0, 1680
	cmp	x0, x21
	bne	.L185
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L186:
	mov	x2, x0
.L180:
	str	x2, [x19, 26608]
	mov	w0, 1
	mov	w1, 0
	strb	w0, [x2, 1]
	.p2align 2
.L182:
	ldr	x4, [x19, 26608]
	sxtw	x0, w1
	uxtb	w2, w1
	add	w1, w1, 1
	add	x4, x4, x0
	cmp	w1, 256
	strb	w2, [x4, 3]
	ldr	x4, [x19, 26608]
	add	x4, x4, x0
	strb	w2, [x4, 259]
	ldr	x4, [x19, 26608]
	add	x4, x4, x0
	strb	w2, [x4, 515]
	ldr	x3, [x19, 26608]
	add	x0, x3, x0
	strb	w2, [x0, 771]
	bne	.L182
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L196:
	ldr	x1, .LC57
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w1, [x20, 3712]
	ldr	w0, [x22, 896]
	bl	FSP_GetFsImagePtr
	mov	x21, x0
	cbz	x0, .L178
	ldr	w0, [x22, 896]
	ldr	x1, [x21, 544]
	bl	FreeUsdByDec
	ldr	w0, [x22, 896]
	ldr	x1, [x21, 552]
	bl	FreeUsdByDec
	ldr	w0, [x22, 896]
	ldr	x1, [x21, 560]
	bl	FreeUsdByDec
	ldr	w0, [x22, 896]
	ldr	x1, [x21, 568]
	bl	FreeUsdByDec
	add	x0, x21, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w1, [x20, 3712]
	ldr	w0, [x22, 896]
	bl	FSP_ClearLogicFs
	ldr	w1, [x20, 3708]
	mov	w2, 1
	ldr	w0, [x22, 896]
	bl	FSP_ClearLogicFs
	str	wzr, [x20, 3708]
	str	wzr, [x20, 3712]
	ldr	w0, [x22, 896]
	bl	FSP_GetNullLogicFs
	str	w0, [x20, 3708]
	str	w0, [x20, 3712]
.L178:
	add	x0, x19, 2520
	add	x1, x22, 288
	add	x0, x0, 20480
	str	wzr, [x0, 3704]
	ldr	w0, [x22, 896]
	bl	FSP_ClearNotInVoQueue
	ldr	x1, .LC59
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VC1_Vfmw_GetImageBuffer, .-VC1_Vfmw_GetImageBuffer
	.align	3
.LC57:
	.xword	.LC56
	.align	3
.LC59:
	.xword	.LC58
	.align	3
.LC61:
	.xword	.LC60
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_MemMove
	.type	VC1_Vfmw_MemMove, %function
VC1_Vfmw_MemMove:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x19, 20480
	ldr	x5, [x19, 24088]
	ldr	x1, [x19, 24096]
	ldr	x4, .LC62
	ldr	w3, [x0, 3644]
	ldr	w2, [x0, 3664]
	add	w3, w3, 1
	ldr	x4, [x4, 104]
	ldr	x1, [x1, 1544]
	add	w3, w3, w3, lsr 31
	ldr	x0, [x5, 1544]
	asr	w3, w3, 1
	lsl	w3, w3, 5
	mul	w2, w3, w2
	lsl	w3, w2, 2
	sub	w2, w3, w2
	asr	w2, w2, 1
	sxtw	x2, w2
	blr	x4
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_Vfmw_MemMove, .-VC1_Vfmw_MemMove
	.align	3
.LC62:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_BuildRefList
	.type	VC1_Vfmw_BuildRefList, %function
VC1_Vfmw_BuildRefList:
	sub	sp, sp, #512
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w1
	mov	w24, w2
	mov	w25, w3
	bl	_mcount
	mov	x2, 256
	mov	w1, 0
	add	x0, x29, 96
	bl	memset
	mov	x2, 256
	mov	w1, 0
	add	x0, x29, 352
	bl	memset
	cbz	x21, .L263
	ldr	x20, .LC65
	add	x22, x21, 20480
	mov	x2, 16
	mov	w1, 0
	add	x0, x22, 3672
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x22, 3688
	blr	x3
	ldrsb	w0, [x21, 4]
	tst	w0, -3
	bne	.L201
	cmp	w19, 1
	beq	.L264
	cmp	w19, 2
	beq	.L265
.L209:
	str	wzr, [x22, 3676]
	str	wzr, [x22, 3692]
.L261:
	mov	w0, 1
.L246:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	add	sp, sp, 512
	ret
	.p2align 3
.L201:
	add	x26, x21, 8192
	ldrb	w0, [x26, 2572]
	cmp	w0, 1
	ldrb	w0, [x26, 2609]
	beq	.L266
	cbz	w0, .L267
.L220:
	ldr	x0, [x21, 24104]
	ldr	w27, [x0, 1188]
	mov	w23, w27
.L219:
	cmp	w19, 1
	beq	.L268
.L221:
	cmp	w19, 2
	bne	.L209
	mov	w0, 1
	strb	wzr, [x22, 3672]
	strb	w0, [x22, 3673]
	str	w19, [x22, 3676]
	str	w19, [x22, 3692]
	cbnz	w24, .L269
	ldr	x0, [x21, 24104]
	ldr	w7, [x0, 1188]
	str	w7, [x22, 3680]
	ldr	x1, [x21, 24088]
.L238:
	strb	wzr, [x22, 3688]
	mov	w0, 1
	strb	w0, [x22, 3689]
	ldr	x0, [x21, 24096]
	ldr	w6, [x0, 1188]
	str	w6, [x22, 3696]
	ldr	w0, [x0, 1188]
	str	w0, [x22, 3700]
	ldr	w0, [x21, 10888]
	ldr	w1, [x1, 1188]
	cmp	w0, 1
	bls	.L270
	ands	w0, w0, -3
	bne	.L240
	ldrb	w2, [x26, 2582]
	cmp	w2, 4
	beq	.L246
.L240:
	mov	w8, 1680
	mov	x0, x21
	mov	x4, 0
	smull	x7, w7, w8
	smull	x6, w6, w8
	smull	x8, w1, w8
	.p2align 2
.L241:
	add	x3, x4, x7
	add	x0, x0, 1
	add	x3, x21, x3
	add	x2, x4, x6
	add	x3, x3, 12288
	add	x2, x21, x2
	add	x2, x2, 12288
	add	x1, x4, x8
	add	x1, x21, x1
	add	x4, x4, 1
	ldrb	w5, [x3, 1723]
	add	x1, x1, 12288
	strb	w5, [x0, 12]
	cmp	x4, 256
	ldrb	w5, [x3, 1979]
	strb	w5, [x0, 268]
	ldrb	w5, [x3, 2235]
	strb	w5, [x0, 524]
	ldrb	w3, [x3, 2491]
	strb	w3, [x0, 780]
	ldrb	w3, [x2, 1723]
	strb	w3, [x0, 1036]
	ldrb	w3, [x2, 1979]
	strb	w3, [x0, 1292]
	ldrb	w3, [x2, 2235]
	strb	w3, [x0, 1548]
	ldrb	w2, [x2, 2491]
	strb	w2, [x0, 1804]
	ldrb	w2, [x1, 1723]
	strb	w2, [x0, 2060]
	ldrb	w2, [x1, 1979]
	strb	w2, [x0, 2316]
	ldrb	w2, [x1, 2235]
	strb	w2, [x0, 2572]
	ldrb	w1, [x1, 2491]
	strb	w1, [x0, 2828]
	bne	.L241
	b	.L261
	.p2align 3
.L267:
	ldr	x0, [x21, 24096]
	cmp	w19, 1
	ldr	x1, [x21, 24104]
	ldr	w23, [x0, 1188]
	ldr	w27, [x1, 1188]
	bne	.L221
.L268:
	ldrb	w0, [x26, 2600]
	strb	w19, [x22, 3673]
	add	w0, w0, 1
	strb	wzr, [x22, 3672]
	str	w0, [x22, 3676]
	str	wzr, [x22, 3692]
	cbz	w24, .L222
	cbz	w25, .L223
	ldr	x0, [x21, 24104]
	ldr	x1, [x21, 24088]
	ldr	w19, [x0, 1188]
	str	w19, [x22, 3680]
	b	.L225
	.p2align 3
.L266:
	cbz	w0, .L220
	ldr	x1, [x21, 24096]
	ldr	x0, [x21, 24104]
	ldr	w27, [x1, 1188]
	ldr	w23, [x0, 1188]
	b	.L219
	.p2align 3
.L264:
	strb	wzr, [x22, 3672]
	str	w19, [x22, 3676]
	str	wzr, [x22, 3692]
	ldr	x0, [x21, 24104]
	ldr	w19, [x0, 1188]
	str	w19, [x22, 3680]
	ldrsb	w0, [x21, 3104]
	cbz	w0, .L203
	ldr	w1, [x21, 10804]
	add	x0, x21, 8192
	cmp	w1, 2
	ldrb	w20, [x0, 2584]
	ldrb	w22, [x0, 2585]
	ldrb	w0, [x0, 2582]
	beq	.L271
.L204:
	cmp	w0, 4
	beq	.L205
.L208:
	mov	w2, 1680
	add	x1, x21, 13
	smull	x2, w19, w2
	add	x2, x2, 12288
	add	x0, x2, 1723
	add	x2, x2, 1979
	add	x0, x21, x0
	add	x2, x21, x2
	.p2align 2
.L206:
	ldrb	w3, [x0]
	add	x0, x0, 1
	strb	w3, [x1]
	add	x1, x1, 1
	cmp	x0, x2
	ldrb	w3, [x0, 255]
	strb	w3, [x1, 255]
	ldrb	w3, [x0, 511]
	strb	w3, [x1, 511]
	ldrb	w3, [x0, 767]
	strb	w3, [x1, 767]
	bne	.L206
	b	.L261
.L265:
	strb	wzr, [x22, 3672]
	mov	w0, 1
	str	w0, [x22, 3676]
	str	w0, [x22, 3692]
	ldr	x0, [x21, 24104]
	ldr	w19, [x0, 1188]
	str	w19, [x22, 3680]
	strb	wzr, [x22, 3688]
	ldr	x0, [x21, 24096]
	ldr	w20, [x0, 1188]
	str	w20, [x22, 3696]
	ldrsb	w0, [x21, 3104]
	cbz	w0, .L210
	add	x0, x21, 8192
	ldrb	w22, [x0, 2584]
	ldrb	w23, [x0, 2585]
	ldrb	w0, [x0, 2582]
.L211:
	cmp	w0, 4
	beq	.L212
.L215:
	mov	w1, 1680
	mov	x3, 14011
	add	x0, x21, 13
	add	x4, x21, 269
	smaddl	x2, w19, w1, x3
	smaddl	x1, w20, w1, x3
	add	x2, x21, x2
	add	x1, x21, x1
	.p2align 2
.L213:
	add	x0, x0, 1
	ldrb	w3, [x2]
	add	x2, x2, 1
	add	x1, x1, 1
	cmp	x0, x4
	strb	w3, [x0, -1]
	ldrb	w3, [x2, 255]
	strb	w3, [x0, 255]
	ldrb	w3, [x2, 511]
	strb	w3, [x0, 511]
	ldrb	w3, [x2, 767]
	strb	w3, [x0, 767]
	ldrb	w3, [x1, -1]
	strb	w3, [x0, 1023]
	ldrb	w3, [x1, 255]
	strb	w3, [x0, 1279]
	ldrb	w3, [x1, 511]
	strb	w3, [x0, 1535]
	ldrb	w3, [x1, 767]
	strb	w3, [x0, 1791]
	bne	.L213
	b	.L261
.L263:
	ldr	x1, .LC64
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	mov	w0, 0
	add	sp, sp, 512
	ret
.L203:
	add	x0, x21, 8192
	ldrb	w20, [x0, 2469]
	ldrb	w22, [x0, 2470]
	ldrb	w0, [x0, 2467]
	b	.L204
.L222:
	ldr	x0, [x21, 24104]
	ldr	w19, [x0, 1188]
	str	w19, [x22, 3680]
	ldr	x1, [x21, 24088]
.L225:
	ldr	w0, [x0, 1188]
	str	w0, [x22, 3684]
	ldr	w0, [x21, 10888]
	ldr	w20, [x1, 1188]
	cmp	w0, 1
	bls	.L272
.L226:
	tst	w0, -3
	bne	.L227
	ldrb	w1, [x26, 2582]
	cmp	w1, 4
	beq	.L273
.L227:
	mov	w3, 1680
	mov	x2, 14011
	add	x0, x21, 13
	add	x4, x21, 269
	smaddl	x1, w19, w3, x2
	smaddl	x2, w20, w3, x2
	add	x1, x21, x1
	add	x2, x21, x2
	.p2align 2
.L234:
	add	x0, x0, 1
	ldrb	w3, [x1]
	add	x1, x1, 1
	add	x2, x2, 1
	cmp	x0, x4
	strb	w3, [x0, -1]
	ldrb	w3, [x1, 255]
	strb	w3, [x0, 255]
	ldrb	w3, [x1, 511]
	strb	w3, [x0, 511]
	ldrb	w3, [x1, 767]
	strb	w3, [x0, 767]
	ldrb	w3, [x2, -1]
	strb	w3, [x0, 2047]
	ldrb	w3, [x2, 255]
	strb	w3, [x0, 2303]
	ldrb	w3, [x2, 511]
	strb	w3, [x0, 2559]
	ldrb	w3, [x2, 767]
	strb	w3, [x0, 2815]
	bne	.L234
	b	.L261
.L210:
	add	x0, x21, 8192
	ldrb	w22, [x0, 2469]
	ldrb	w23, [x0, 2470]
	ldrb	w0, [x0, 2467]
	b	.L211
.L269:
	cbz	w25, .L236
	ldr	x0, [x21, 24104]
	ldr	x1, [x21, 24088]
	ldr	w7, [x0, 1188]
	str	w7, [x22, 3680]
	b	.L238
.L223:
	ldr	x1, [x21, 24088]
	ldr	x0, [x21, 24104]
	ldr	w19, [x1, 1188]
	str	w19, [x22, 3680]
	b	.L225
.L271:
	ldr	w1, [x21, 10880]
	cmp	w1, 1
	bne	.L204
.L205:
	mov	w3, 0
	mov	w2, w22
	mov	w1, w20
	add	x0, x29, 96
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w2, w22
	mov	w1, w20
	add	x0, x29, 352
	mov	w3, 1
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w2, 1680
	sub	x0, x29, #3488
	smull	x2, w19, w2
	add	x2, x2, 12288
	add	x1, x2, 1723
	add	x2, x2, 1979
	add	x1, x21, x1
	add	x6, x21, x2
	.p2align 2
.L207:
	ldrb	w5, [x1]
	add	x1, x1, 1
	ldrb	w4, [x1, 255]
	ldrb	w3, [x1, 511]
	add	x5, x0, x5
	ldrb	w2, [x1, 767]
	add	x4, x0, x4
	add	x3, x0, x3
	cmp	x1, x6
	add	x2, x0, x2
	ldrb	w5, [x5, 3584]
	ldrb	w4, [x4, 3840]
	ldrb	w3, [x3, 3584]
	ldrb	w2, [x2, 3840]
	strb	w5, [x1, -1]
	strb	w4, [x1, 255]
	strb	w3, [x1, 511]
	strb	w2, [x1, 767]
	bne	.L207
	b	.L208
.L273:
	cbnz	w0, .L231
	ldr	w22, [x21, 10892]
	ldr	w24, [x21, 10896]
	uxtb	w22, w22
	uxtb	w24, w24
.L232:
	mov	w3, 0
	mov	w2, w24
	add	x0, x29, 96
	mov	w1, w22
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w2, w24
	mov	w1, w22
	add	x0, x29, 352
	mov	w3, 1
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w2, 1680
	sub	x0, x29, #3488
	smull	x2, w23, w2
	add	x2, x2, 12288
	add	x1, x2, 2235
	add	x2, x2, 2491
	add	x1, x21, x1
	add	x4, x21, x2
	.p2align 2
.L233:
	ldrb	w3, [x1]
	add	x1, x1, 1
	ldrb	w2, [x1, 255]
	cmp	x1, x4
	add	x3, x0, x3
	add	x2, x0, x2
	ldrb	w3, [x3, 3584]
	ldrb	w2, [x2, 3840]
	strb	w3, [x1, -1]
	strb	w2, [x1, 255]
	bne	.L233
	b	.L227
.L272:
	ldrb	w0, [x26, 2582]
	cmp	w0, 4
	bne	.L227
	ldrb	w22, [x26, 2584]
	mov	w3, 0
	ldrb	w24, [x26, 2585]
	add	x0, x29, 96
	mov	w1, w22
	mov	w2, w24
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w1, w22
	mov	w3, 1
	add	x0, x29, 352
	mov	w2, w24
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w0, 1680
	smull	x0, w27, w0
	add	x0, x0, 12288
	add	x1, x0, 1723
	add	x0, x0, 1979
	add	x3, x21, x0
	add	x1, x21, x1
	sub	x0, x29, #3488
	.p2align 2
.L228:
	ldrb	w2, [x1]
	add	x1, x1, 1
	add	x2, x0, x2
	ldrb	w2, [x2, 3584]
	strb	w2, [x1, -1]
	ldrb	w2, [x1, 255]
	add	x2, x0, x2
	ldrb	w2, [x2, 3840]
	strb	w2, [x1, 255]
	cmp	x1, x3
	bne	.L228
	ldr	w0, [x21, 10888]
	b	.L226
.L270:
	ldrb	w0, [x26, 2582]
	cmp	w0, 4
	bne	.L240
	mov	w0, 0
	b	.L246
.L236:
	ldr	x1, [x21, 24088]
	ldr	w7, [x1, 1188]
	str	w7, [x22, 3680]
	b	.L238
.L212:
	mov	w3, 0
	mov	w2, w23
	mov	w1, w22
	add	x0, x29, 96
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w3, 1
	mov	w2, w23
	mov	w1, w22
	add	x0, x29, 352
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	w1, 1680
	mov	x2, 14011
	sub	x0, x29, #3488
	smull	x3, w19, w1
	smaddl	x2, w20, w1, x2
	add	x3, x3, 12288
	add	x1, x3, 1723
	add	x3, x3, 1979
	add	x1, x21, x1
	add	x2, x21, x2
	add	x7, x21, x3
	.p2align 2
.L214:
	ldrb	w6, [x1]
	add	x1, x1, 1
	ldrb	w5, [x1, 255]
	add	x2, x2, 1
	ldrb	w4, [x1, 511]
	add	x6, x0, x6
	ldrb	w3, [x1, 767]
	add	x5, x0, x5
	add	x4, x0, x4
	cmp	x1, x7
	add	x3, x0, x3
	ldrb	w6, [x6, 3584]
	ldrb	w5, [x5, 3840]
	ldrb	w4, [x4, 3584]
	ldrb	w3, [x3, 3840]
	strb	w6, [x1, -1]
	strb	w5, [x1, 255]
	strb	w4, [x1, 511]
	strb	w3, [x1, 767]
	ldrb	w6, [x2, -1]
	ldrb	w5, [x2, 255]
	ldrb	w4, [x2, 511]
	add	x6, x0, x6
	ldrb	w3, [x2, 767]
	add	x5, x0, x5
	add	x4, x0, x4
	add	x3, x0, x3
	ldrb	w6, [x6, 3584]
	ldrb	w5, [x5, 3840]
	ldrb	w4, [x4, 3584]
	ldrb	w3, [x3, 3840]
	strb	w6, [x2, -1]
	strb	w5, [x2, 255]
	strb	w4, [x2, 511]
	strb	w3, [x2, 767]
	bne	.L214
	b	.L215
.L231:
	ldrb	w22, [x26, 2584]
	ldrb	w24, [x26, 2585]
	b	.L232
	.size	VC1_Vfmw_BuildRefList, .-VC1_Vfmw_BuildRefList
	.align	3
.LC64:
	.xword	.LC63
	.align	3
.LC65:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_GetStreamInfo
	.type	VC1_Vfmw_GetStreamInfo, %function
VC1_Vfmw_GetStreamInfo:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 12288
	bl	_mcount
	add	x0, x19, 2520
	add	x1, x0, 20480
	ldrsb	w2, [x0, 3104]
	ldr	w22, [x1, 3640]
	cbz	w2, .L275
	ldr	w0, [x19, 13324]
	ldr	w21, [x1, 3644]
	cmp	w0, 3
	beq	.L355
.L353:
	ldrh	w0, [x19, 5878]
	ldrh	w1, [x19, 5876]
	add	w0, w0, 15
	add	w1, w1, 15
	asr	w0, w0, 4
	mul	w21, w21, w22
	asr	w1, w1, 4
.L327:
	lsl	w2, w1, 4
	mov	w4, 8160
	sub	w3, w2, #32
	cmp	w3, w4
	lsl	w3, w0, 4
	bhi	.L278
	sub	w5, w3, #32
	cmp	w5, w4
	bhi	.L278
	add	x4, x19, 2520
	add	x2, x4, 20480
	ldr	w3, [x2, 3652]
	cmp	w0, w3
	beq	.L356
.L281:
	add	x1, x19, 2520
	lsl	w0, w22, 4
	add	x2, x1, 20480
	add	w0, w0, 63
	and	w0, w0, -64
	mov	w3, 1
	ldr	w4, [x2, 3644]
	str	w22, [x2, 3648]
	str	w4, [x2, 3652]
	str	w0, [x2, 3664]
	ldrb	w0, [x19, 2528]
	cbz	w0, .L289
.L283:
	ldrsb	w1, [x19, 2523]
	cmp	w1, 3
	beq	.L357
.L286:
	ldrb	w1, [x19, 2520]
	eor	x1, x1, 8
	ubfx	x1, x1, 3, 1
	orr	w0, w3, w1
	cbnz	w0, .L289
.L293:
	mov	x0, x20
	bl	VC1_Vfmw_GetImageBuffer
	mov	w23, w0
	cbz	w0, .L358
	add	x1, x19, 2520
	add	x23, x20, 53248
	add	x1, x1, 20480
	ldr	w0, [x23, 896]
	ldr	w1, [x1, 3716]
	bl	FSP_GetFsImagePtr
	mov	x2, x0
	cbz	x0, .L295
	ldr	x3, [x20]
	mov	x4, -1
	ldr	x1, .LC72
	mov	w0, 29
	ldr	x3, [x3, 64]
	str	x3, [x2, 584]
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
.L295:
	add	x0, x19, 2520
	ldrsb	w1, [x0, 3104]
	cbz	w1, .L296
	ldr	w1, [x19, 13324]
	cmp	w1, 3
	beq	.L359
.L296:
	ldr	x0, [x19, 26608]
	str	wzr, [x0, 1092]
.L297:
	ldr	x1, [x19, 26608]
	add	x0, x19, 2520
	strb	wzr, [x1, 2]
	ldrsb	w1, [x0, 3104]
	cbnz	w1, .L298
	add	x1, x0, 8192
	ldrb	w2, [x1, 2220]
	cmp	w2, 1
	beq	.L360
.L298:
	add	x24, x19, 2520
	ldrb	w0, [x24, 2]
	cmp	w0, 1
	ccmp	w0, 5, 4, hi
	bne	.L299
	add	x24, x24, 20480
	mov	w0, 2
	ldr	w1, [x24, 3704]
	ldr	w2, [x24, 3708]
	ldr	w3, [x24, 3712]
	cmp	w1, wzr
	csinc	w0, w0, wzr, ne
	str	w0, [x24, 3704]
	cmp	w2, w3
	beq	.L301
	ldr	x1, .LC75
	mov	w0, 13
	bl	dprint_vfmw
	ldr	w0, [x23, 896]
	mov	w2, 0
	ldr	w1, [x24, 3708]
	bl	FSP_SetRef
	ldr	w3, [x24, 3712]
.L301:
	add	x24, x19, 2520
	mov	w2, 1
	add	x25, x24, 20480
	ldr	w1, [x25, 3716]
	str	w3, [x25, 3708]
	str	w1, [x25, 3712]
	ldr	w0, [x23, 896]
	bl	FSP_SetRef
	ldr	w0, [x23, 896]
	ldr	w1, [x25, 3708]
	bl	FSP_RemovePmv
	ldrb	w0, [x24, 2]
	cmp	w0, 1
	ccmp	w0, 5, 4, hi
	bne	.L303
	ldr	x0, [x24, 24104]
	mov	w1, 1
	strb	wzr, [x0]
	ldr	x0, [x24, 24088]
	strb	w1, [x0]
	ldr	x1, [x24, 24096]
	ldr	x0, [x24, 24088]
	str	x0, [x24, 24096]
	str	x1, [x24, 24104]
.L303:
	add	x25, x19, 2520
	ldr	w0, [x23, 896]
	add	x26, x25, 20480
	ldr	w1, [x26, 3716]
	bl	FSP_GetLogicFs
	mov	x24, x0
	ldr	w1, [x26, 3708]
	ldr	w0, [x23, 896]
	bl	FSP_GetLogicFs
	mov	x28, x0
	ldr	w1, [x26, 3712]
	ldr	w0, [x23, 896]
	bl	FSP_GetLogicFs
	mov	x27, x0
	cmp	x24, xzr
	ccmp	x28, xzr, 4, ne
	ccmp	x0, xzr, 4, ne
	beq	.L361
	ldrsb	w0, [x25, 3104]
	cbnz	w0, .L362
.L309:
	str	wzr, [x24, 100]
.L310:
	ldrb	w1, [x19, 2522]
	add	x0, x19, 2520
	cmp	w1, 5
	beq	.L363
.L311:
	ldr	x1, [x24, 32]
	cbz	x1, .L312
	ldr	x0, [x24, 40]
	cbz	x0, .L312
	ldr	x0, [x27, 32]
	cbz	x0, .L314
	ldr	w0, [x0, 8]
.L315:
	str	w0, [x20, 14460]
	ldr	x0, [x28, 32]
	cbz	x0, .L364
.L354:
	ldr	w0, [x0, 8]
	str	w0, [x20, 14456]
	ldr	x0, [x24, 32]
	ldr	w0, [x0, 8]
	str	w0, [x20, 14584]
	ldr	w0, [x24, 8]
	str	w0, [x20, 14464]
	ldr	w0, [x27, 8]
	str	w0, [x20, 14468]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 8]
	str	w0, [x20, 14452]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 24]
	str	w0, [x20, 14532]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 28]
	str	w0, [x20, 14536]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 60]
	str	w0, [x20, 14540]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 44]
	str	w0, [x20, 14544]
	ldr	x0, [x24, 40]
	ldr	w0, [x0, 48]
	str	w0, [x20, 14548]
	ldr	x0, [x24, 32]
	ldr	x24, [x19, 26608]
	ldr	w0, [x0, 8]
	bl	MEM_Phy2Vir
	str	x0, [x24, 1544]
	ldr	x24, [x19, 26624]
	ldr	w0, [x20, 14456]
	bl	MEM_Phy2Vir
	str	x0, [x24, 1544]
	ldr	x23, [x19, 26616]
	ldr	w0, [x20, 14460]
	bl	MEM_Phy2Vir
	str	x0, [x23, 1544]
.L288:
	add	x0, x19, 2520
	ldr	x2, [x0, 24088]
	ldrsb	w1, [x0, 3104]
	cbz	w1, .L365
	ldr	w3, [x0, 10804]
	add	x1, x0, 8192
	strb	w3, [x2, 1027]
	ldr	x2, [x0, 24088]
	ldrb	w3, [x1, 2569]
	strb	w3, [x2, 1028]
	ldrb	w3, [x1, 2582]
	ldr	x4, [x0, 24088]
	sub	w2, w3, #2
	ldrb	w0, [x1, 2609]
	uxtb	w2, w2
	cmp	w2, 1
	bls	.L334
	cmp	w3, 4
	mov	w2, 0
	beq	.L366
.L321:
	add	x1, x4, x0, sxtw
	add	x0, x19, 2520
	add	x0, x0, 20480
	strb	w2, [x1, 1029]
	ldr	w3, [x0, 3724]
	cbz	w3, .L322
	subs	w3, w3, #1
	beq	.L367
	add	x1, x20, 36864
	mov	w2, 0
	add	x1, x1, 2168
	.p2align 2
.L325:
	ldr	w0, [x1, 72]
	add	x1, x1, 56
	strb	w2, [x1, -56]
	add	w2, w2, 1
	cmp	w2, 254
	mul	w0, w22, w0
	ccmp	w3, w2, 0, le
	sub	w0, w0, #1
	str	w0, [x1, -40]
	bhi	.L325
	uxtb	w1, w3
.L324:
	uxtw	x3, w3
	add	x2, x19, 2520
	lsl	x0, x3, 3
	sub	w21, w21, #1
	sub	x3, x0, x3
	add	x0, x2, x3, lsl 3
	add	x0, x0, 20480
	strb	w1, [x0, 3744]
	str	w21, [x0, 3760]
	ldrb	w1, [x19, 2522]
	cmp	w1, 2
	bne	.L320
	add	x0, x2, 8192
	ldr	w3, [x19, 13428]
	add	x2, x2, 36864
	ldrb	w0, [x0, 2599]
	mul	w3, w0, w3
	asr	w3, w3, 8
	str	w3, [x2, 1736]
	sub	w0, w0, w3
	subs	w0, w0, #1
	csel	w0, w0, wzr, pl
	str	w0, [x2, 1740]
	b	.L320
	.p2align 3
.L278:
	ldr	x1, .LC66
	mov	w0, 0
	mov	w23, 0
	bl	dprint_vfmw
.L352:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L275:
	ldr	w0, [x1, 3644]
	mov	w1, w22
	mul	w21, w22, w0
	b	.L327
	.p2align 3
.L355:
	add	w21, w21, 1
	add	w21, w21, w21, lsr 31
	asr	w21, w21, 1
	b	.L353
	.p2align 3
.L289:
	add	x0, x19, 2520
	add	x23, x20, 53248
	add	x25, x0, 20480
	add	x1, x25, 1928
	str	x1, [x19, 26608]
	str	x1, [x19, 26616]
	str	x1, [x19, 26624]
	str	x1, [x19, 26632]
	ldr	w0, [x23, 896]
	ldr	w1, [x25, 3712]
	bl	FSP_GetFsImagePtr
	mov	x24, x0
	cbz	x0, .L285
	ldr	w0, [x23, 896]
	ldr	x1, [x24, 544]
	bl	FreeUsdByDec
	ldr	w0, [x23, 896]
	ldr	x1, [x24, 552]
	bl	FreeUsdByDec
	ldr	w0, [x23, 896]
	ldr	x1, [x24, 560]
	bl	FreeUsdByDec
	ldr	w0, [x23, 896]
	ldr	x1, [x24, 568]
	bl	FreeUsdByDec
	add	x0, x24, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w0, [x23, 896]
	ldr	w1, [x25, 3712]
	bl	FSP_ClearLogicFs
	ldr	w0, [x23, 896]
	mov	w2, 1
	ldr	w1, [x25, 3708]
	bl	FSP_ClearLogicFs
	str	wzr, [x25, 3708]
	str	wzr, [x25, 3712]
	ldr	w0, [x23, 896]
	bl	FSP_GetNullLogicFs
	str	w0, [x25, 3708]
	str	w0, [x25, 3712]
.L285:
	add	x2, x19, 2520
	add	x0, x20, 28672
	add	x2, x2, 20480
	add	x1, x20, 36864
	add	x0, x0, 145
	add	x1, x1, 353
	str	wzr, [x2, 3704]
	.p2align 2
.L291:
	strb	wzr, [x0]
	strb	wzr, [x0, -1]
	add	x0, x0, 1680
	cmp	x0, x1
	bne	.L291
	add	x24, x23, 288
	ldr	w0, [x23, 896]
	mov	x1, x24
	bl	FSP_ClearNotInVoQueue
	ldrb	w0, [x19, 2520]
	tbnz	x0, 3, .L293
	mov	x0, x24
	bl	ResetVoQueue
	ldr	x1, [x20]
	ldr	w0, [x1, 732]
	ldr	w3, [x1, 736]
	adds	w1, w0, 15
	add	w0, w0, 30
	add	w2, w3, 30
	csel	w1, w0, w1, mi
	adds	w0, w3, 15
	asr	w1, w1, 4
	csel	w0, w2, w0, mi
	str	w1, [x20, 14624]
	asr	w0, w0, 4
	mov	w3, 2
	add	w2, w0, 1
	str	w0, [x20, 14628]
	lsl	w1, w1, 4
	mov	x0, x20
	add	w2, w2, w2, lsr 31
	asr	w2, w2, 1
	lsl	w2, w2, 5
	bl	VC1_ArrangeVahbMem
	cmp	w0, 1
	bne	.L292
	ldrb	w0, [x19, 2520]
	orr	w0, w0, 8
	strb	w0, [x19, 2520]
	b	.L293
	.p2align 3
.L358:
	ldr	x1, .LC70
	mov	w0, 1
	bl	dprint_vfmw
	b	.L352
	.p2align 3
.L356:
	ldr	w0, [x2, 3648]
	cmp	w1, w0
	bne	.L281
	lsl	w0, w22, 4
	mov	w3, 0
	add	w0, w0, 63
	and	w0, w0, -64
	str	w0, [x2, 3664]
	ldrb	w0, [x4, 8]
	cbz	w0, .L286
	b	.L283
	.p2align 3
.L299:
	add	x0, x24, 20480
	ldr	w1, [x0, 3704]
	cmp	w1, 1
	bhi	.L303
	ldr	w1, [x0, 3716]
	mov	w2, 1
	ldr	w0, [x23, 896]
	mov	w23, 0
	bl	FSP_ClearLogicFs
	ldr	x2, [x24, 24088]
	mov	w0, 1
	ldr	x1, .LC77
	strb	wzr, [x2]
	ldr	x2, [x24, 24088]
	strb	wzr, [x2, 1]
	bl	dprint_vfmw
	b	.L352
	.p2align 3
.L361:
	ldr	w0, [x23, 896]
	mov	w2, 1
	ldr	w1, [x26, 3716]
	bl	FSP_ClearLogicFs
	ldr	x0, [x25, 24088]
	mov	x5, x27
	ldr	x1, .LC79
	mov	x4, x28
	mov	x3, x24
	mov	w2, 2066
	strb	wzr, [x0]
	mov	w0, 0
	ldr	x6, [x25, 24088]
	strb	wzr, [x6, 1]
	bl	dprint_vfmw
	ldrb	w0, [x25, 2]
	cmp	w0, 5
	beq	.L368
.L307:
	ldr	x1, .LC81
	mov	w0, 1
	mov	w23, 0
	bl	dprint_vfmw
	b	.L352
	.p2align 3
.L365:
	strb	wzr, [x2, 1027]
	add	x1, x0, 8192
	ldr	x2, [x0, 24088]
	ldrb	w3, [x1, 2459]
	strb	w3, [x2, 1028]
	ldrb	w3, [x1, 2467]
	ldr	x2, [x0, 24088]
	sub	w0, w3, #2
	uxtb	w0, w0
	cmp	w0, 1
	bls	.L332
	cmp	w3, 4
	mov	w0, 0
	beq	.L369
.L319:
	add	x24, x19, 2520
	strb	w0, [x2, 1030]
	add	x21, x24, 20480
	strb	w0, [x2, 1029]
	mov	w0, 1
	add	x22, x24, 36864
	strb	wzr, [x21, 3744]
	str	w0, [x21, 3724]
	ldr	x0, [x19, 5656]
	ldr	x23, [x22, 1688]
	bl	BsPos
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w0, w1, w0, lt
	asr	w0, w0, 3
	add	x0, x23, x0, sxtw
	str	x0, [x19, 26728]
	ldr	x0, [x19, 5656]
	ldr	w23, [x22, 1708]
	bl	BsPos
	add	w1, w0, 7
	cmp	w0, wzr
	csel	w0, w1, w0, lt
	add	w0, w23, w0, asr 3
	str	w0, [x21, 3748]
	ldr	x0, [x19, 5656]
	bl	BsPos
	and	w0, w0, 7
	str	w0, [x21, 3752]
	ldr	w23, [x22, 1716]
	ldr	x0, [x19, 5656]
	lsl	w23, w23, 3
	bl	BsPos
	sub	w0, w23, w0
	str	w0, [x21, 3756]
	ldr	w1, [x22, 1764]
	ldr	w0, [x22, 1760]
	mul	w0, w0, w1
	sub	w0, w0, #1
	str	w0, [x21, 3760]
	ldrb	w1, [x19, 2522]
.L320:
	add	x19, x19, 2520
	mov	w3, 1
	mov	w2, 0
	mov	x0, x19
	bl	VC1_Vfmw_BuildRefList
	mov	w23, w0
	cbz	w0, .L370
	mov	w23, 1
	b	.L352
	.p2align 3
.L362:
	ldr	w0, [x25, 10804]
	cmp	w0, 3
	bne	.L309
	ldr	x0, .LC73
	ldr	w0, [x0]
	cmp	w0, 1
	bne	.L309
	str	w0, [x24, 100]
	b	.L310
	.p2align 3
.L368:
	add	x25, x25, 36864
	ldr	w0, [x25, 1780]
	cmp	w0, wzr
	ble	.L307
	sub	w0, w0, #1
	str	w0, [x25, 1780]
	b	.L307
	.p2align 3
.L357:
	ldrb	w0, [x19, 2529]
	cmp	w0, 1
	bne	.L288
	b	.L286
	.p2align 3
.L370:
	add	x0, x19, 20480
	add	x20, x20, 53248
	mov	w2, 1
	ldr	w1, [x0, 3716]
	ldr	w0, [x20, 896]
	bl	FSP_ClearLogicFs
	ldr	x2, [x19, 24088]
	mov	w0, 1
	ldr	x1, .LC85
	strb	wzr, [x2]
	ldr	x2, [x19, 24088]
	strb	wzr, [x2, 1]
	bl	dprint_vfmw
	b	.L352
	.p2align 3
.L322:
	mov	w2, 1
	mov	w1, 0
	str	w2, [x0, 3724]
	b	.L324
	.p2align 3
.L363:
	ldr	w1, [x28, 100]
	add	x0, x0, 36864
	str	w1, [x24, 100]
	ldr	x2, [x19, 26624]
	ldr	x1, [x19, 26608]
	ldr	w2, [x2, 1092]
	str	w2, [x1, 1092]
	ldr	w1, [x0, 1780]
	add	w1, w1, 1
	str	w1, [x0, 1780]
	b	.L311
	.p2align 3
.L360:
	ldr	x0, [x19, 26608]
	ldrb	w1, [x1, 2458]
	strb	w1, [x0, 2]
	b	.L298
	.p2align 3
.L359:
	ldr	x1, .LC73
	ldr	w1, [x1]
	cmp	w1, 1
	bne	.L296
	ldr	x0, [x19, 26608]
	str	w1, [x0, 1092]
	b	.L297
	.p2align 3
.L312:
	add	x19, x19, 2520
	ldr	w0, [x23, 896]
	add	x20, x19, 20480
	mov	w2, 1
	ldr	w1, [x20, 3716]
	bl	FSP_ClearLogicFs
	ldr	x2, [x19, 24088]
	mov	w0, 0
	ldr	x1, .LC83
	strb	wzr, [x2]
	ldr	x2, [x19, 24088]
	strb	wzr, [x2, 1]
	ldr	w2, [x20, 3708]
	ldr	w4, [x20, 3712]
	ldr	w3, [x20, 3716]
	ldp	x5, x6, [x24, 32]
	bl	dprint_vfmw
	ldrb	w0, [x19, 2]
	cmp	w0, 5
	bne	.L307
	add	x19, x19, 36864
	ldr	w0, [x19, 1780]
	cmp	w0, wzr
	ble	.L307
	sub	w0, w0, #1
	str	w0, [x19, 1780]
	b	.L307
	.p2align 3
.L292:
	ldr	x1, .LC68
	mov	w0, 1
	mov	w23, 0
	bl	dprint_vfmw
	ldrb	w0, [x19, 2520]
	and	w0, w0, -9
	strb	w0, [x19, 2520]
	b	.L352
	.p2align 3
.L334:
	mov	w2, 1
	b	.L321
	.p2align 3
.L332:
	mov	w0, 1
	b	.L319
	.p2align 3
.L314:
	ldr	w0, [x1, 8]
	b	.L315
	.p2align 3
.L364:
	ldr	x0, [x24, 32]
	b	.L354
	.p2align 3
.L366:
	ldrb	w1, [x1, 2583]
	sub	w1, w1, #2
	uxtb	w1, w1
	cmp	w1, 1
	cset	w2, ls
	b	.L321
	.p2align 3
.L369:
	ldrb	w0, [x1, 2468]
	sub	w0, w0, #2
	uxtb	w0, w0
	cmp	w0, 1
	cset	w0, ls
	b	.L319
.L367:
	mov	w1, 0
	mov	w3, 0
	b	.L324
	.size	VC1_Vfmw_GetStreamInfo, .-VC1_Vfmw_GetStreamInfo
	.align	3
.LC66:
	.xword	.LC41
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
.LC73:
	.xword	USE_FF_APT_EN
	.align	3
.LC75:
	.xword	.LC74
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC79:
	.xword	.LC78
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
	.global	VC1_Vfmw_PrepareDecode
	.type	VC1_Vfmw_PrepareDecode, %function
VC1_Vfmw_PrepareDecode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L375
	mov	x0, x19
	bl	VC1_Vfmw_GetStreamInfo
	mov	w19, w0
	cbz	w0, .L376
	mov	w19, 1
.L373:
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L376:
	ldr	x1, .LC90
	bl	dprint_vfmw
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L375:
	ldr	x3, .LC87
	mov	w2, 2242
	ldr	x1, .LC88
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L373
	.size	VC1_Vfmw_PrepareDecode, .-VC1_Vfmw_PrepareDecode
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC88:
	.xword	.LC37
	.align	3
.LC90:
	.xword	.LC89
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvrange
	.type	VC1_DecMvrange, %function
VC1_DecMvrange:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC91
	mov	w1, 3
	mov	x0, x19
	ldp	x8, x9, [x3, 16]
	ldp	x6, x7, [x3, 32]
	ldp	x4, x5, [x3, 48]
	ldp	x2, x3, [x3, 64]
	stp	x8, x9, [x29, 32]
	stp	x6, x7, [x29, 48]
	stp	x4, x5, [x29, 64]
	stp	x2, x3, [x29, 80]
	bl	BsShow
	add	x1, x29, 96
	add	x1, x1, x0, sxtw 3
	mov	x0, x19
	ldp	w19, w1, [x1, -64]
	bl	BsSkip
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.size	VC1_DecMvrange, .-VC1_DecMvrange
	.align	3
.LC91:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecTransacfrm
	.type	VC1_DecTransacfrm, %function
VC1_DecTransacfrm:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w2, 2
	mov	w3, 1
	mov	w1, w2
	mov	x0, x19
	stp	xzr, xzr, [x29, 32]
	str	w3, [x29, 36]
	stp	w3, w3, [x29, 44]
	stp	w2, w2, [x29, 52]
	str	w2, [x29, 60]
	stp	xzr, xzr, [x29, 64]
	stp	xzr, xzr, [x29, 80]
	bl	BsShow
	add	x1, x29, 96
	add	x1, x1, x0, sxtw 3
	mov	x0, x19
	ldp	w19, w1, [x1, -64]
	bl	BsSkip
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
	.size	VC1_DecTransacfrm, .-VC1_DecTransacfrm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_SetCurPicResolutionInfo
	.type	VC1_SetCurPicResolutionInfo, %function
VC1_SetCurPicResolutionInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x1, x19, 20480
	cmp	w20, 1
	add	x0, x19, 36864
	ldr	w2, [x1, 3640]
	beq	.L381
	cmp	w20, 2
	beq	.L387
	cbz	w20, .L386
	add	w2, w2, 1
	add	w2, w2, w2, lsr 31
	asr	w2, w2, 1
.L387:
	str	w2, [x0, 1760]
	ldr	w1, [x1, 3644]
	add	w1, w1, 1
	add	w1, w1, w1, lsr 31
	asr	w1, w1, 1
	str	w1, [x0, 1764]
	b	.L384
	.p2align 3
.L381:
	add	w2, w2, 1
	add	w2, w2, w2, lsr 31
	asr	w2, w2, 1
.L386:
	str	w2, [x0, 1760]
	ldr	w1, [x1, 3644]
	str	w1, [x0, 1764]
.L384:
	mul	w3, w2, w1
	str	w3, [x0, 1768]
	lsl	w2, w2, 4
	lsl	w1, w1, 4
	str	w2, [x0, 1752]
	str	w1, [x0, 1756]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_SetCurPicResolutionInfo, .-VC1_SetCurPicResolutionInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvmodeProgrP
	.type	VC1_DecMvmodeProgrP, %function
VC1_DecMvmodeProgrP:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	uxtb	w21, w1
	bl	_mcount
	mov	w1, 4
	mov	x0, x20
	bl	BsShow
	cmp	w0, 1
	ldr	x1, .LC93
	add	x2, x1, 104
	ldp	x4, x5, [x1, 80]
	ldr	w3, [x1, 96]
	ldp	x6, x7, [x2]
	add	x2, x29, 72
	ldr	w1, [x1, 120]
	stp	x4, x5, [x29, 48]
	str	w3, [x29, 64]
	stp	x6, x7, [x2]
	str	w1, [x29, 88]
	ble	.L396
	cmp	w0, 3
	ble	.L394
	cmp	w0, 8
	mov	w1, 2
	csinc	w1, w1, wzr, lt
	cset	w19, lt
.L390:
	mov	x0, x20
	sbfiz	x19, x19, 2, 32
	bl	BsSkip
	cmp	w21, 12
	add	x0, x29, 96
	add	x19, x0, x19
	bhi	.L397
.L391:
	ldr	w0, [x19, -24]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L394:
	mov	w1, 3
	mov	x0, x20
	mov	w19, 2
	bl	BsSkip
	sbfiz	x19, x19, 2, 32
	cmp	w21, 12
	add	x0, x29, 96
	add	x19, x0, x19
	bls	.L391
.L397:
	ldr	w0, [x19, -48]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L396:
	mov	w1, 4
	mov	w19, 3
	cbz	w0, .L390
	mov	w19, w1
	b	.L390
	.size	VC1_DecMvmodeProgrP, .-VC1_DecMvmodeProgrP
	.align	3
.LC93:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvmodeProgrB
	.type	VC1_DecMvmodeProgrB, %function
VC1_DecMvmodeProgrB:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 1
	mov	x0, x19
	bl	BsSkip
	ldr	x19, [sp, 16]
	add	x1, x29, 48
	mov	w2, 3
	add	x0, x1, x0, sxtw 2
	mov	w1, 1
	stp	w2, w1, [x29, 40]
	ldr	w0, [x0, -8]
	ldp	x29, x30, [sp], 48
	ret
	.size	VC1_DecMvmodeProgrB, .-VC1_DecMvmodeProgrB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvmodeInterB
	.type	VC1_DecMvmodeInterB, %function
VC1_DecMvmodeInterB:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	uxtb	w21, w1
	bl	_mcount
	mov	w1, 3
	mov	x0, x20
	bl	BsShow
	str	wzr, [x29, 88]
	add	x1, x29, 72
	mov	w3, 1
	mov	w2, 2
	cmp	w0, w3
	stp	w2, wzr, [x29, 64]
	stp	xzr, xzr, [x1]
	str	w3, [x29, 72]
	mov	w1, 3
	stp	w1, w3, [x29, 56]
	stp	w2, w1, [x29, 80]
	ble	.L406
	cmp	w0, 4
	csinc	w1, w2, wzr, lt
	cset	w19, lt
.L401:
	mov	x0, x20
	bl	BsSkip
	cmp	w21, 12
	sbfiz	x2, x19, 2, 32
	add	x0, x29, 96
	add	x2, x0, x2
	bhi	.L407
	ldr	w0, [x2, -24]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L407:
	ldr	w0, [x2, -40]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L406:
	mov	w19, w1
	cbz	w0, .L401
	mov	w19, w2
	b	.L401
	.size	VC1_DecMvmodeInterB, .-VC1_DecMvmodeInterB
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecMvmode2
	.type	VC1_DecMvmode2, %function
VC1_DecMvmode2:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	uxtb	w21, w1
	bl	_mcount
	mov	w1, 3
	mov	x0, x20
	bl	BsShow
	mov	w3, 1
	mov	w1, 3
	mov	w2, 2
	cmp	w0, w3
	stp	w1, w3, [x29, 48]
	stp	w2, wzr, [x29, 56]
	stp	w3, wzr, [x29, 64]
	stp	w2, w1, [x29, 72]
	ble	.L415
	cmp	w0, 4
	csinc	w1, w2, wzr, lt
	cset	w19, lt
.L410:
	mov	x0, x20
	bl	BsSkip
	cmp	w21, 12
	sbfiz	x2, x19, 2, 32
	add	x0, x29, 80
	add	x2, x0, x2
	bhi	.L416
	ldr	w0, [x2, -16]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L416:
	ldr	w0, [x2, -32]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L415:
	mov	w19, w1
	cbz	w0, .L410
	mov	w19, w2
	b	.L410
	.size	VC1_DecMvmode2, .-VC1_DecMvmode2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecBfractionSMP
	.type	VC1_DecBfractionSMP, %function
VC1_DecBfractionSMP:
	stp	x29, x30, [sp, -256]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	x20, x1
	mov	x22, x2
	bl	_mcount
	ldr	x0, .LC95
	add	x1, x0, 248
	add	x8, x0, 304
	ldp	x4, x5, [x0, 128]
	ldr	w3, [x0, 184]
	ldr	x6, [x0, 144]
	stp	x4, x5, [x29, 48]
	ldr	x4, [x0, 176]
	ldr	w7, [x0, 152]
	str	x6, [x29, 64]
	str	x4, [x29, 96]
	ldr	x6, [x0, 240]
	ldp	x4, x5, [x0, 192]
	str	w3, [x29, 104]
	ldr	x3, [x0, 296]
	str	w7, [x29, 72]
	stp	x4, x5, [x29, 144]
	str	x6, [x29, 192]
	ldp	x4, x5, [x0, 208]
	ldp	x6, x7, [x0, 160]
	str	x3, [x29, 248]
	ldp	x2, x3, [x0, 224]
	add	x0, x29, 200
	stp	x6, x7, [x29, 80]
	ldp	x6, x7, [x1]
	stp	x6, x7, [x0]
	ldp	x6, x7, [x8]
	stp	x6, x7, [x29, 112]
	add	x6, x29, 216
	mov	x0, x21
	stp	x4, x5, [x29, 160]
	ldp	x4, x5, [x1, 16]
	stp	x4, x5, [x6]
	add	x4, x29, 232
	stp	x2, x3, [x29, 176]
	ldp	x2, x3, [x1, 32]
	stp	x2, x3, [x4]
	ldp	x2, x3, [x8, 16]
	mov	w1, 3
	stp	x2, x3, [x29, 128]
	bl	BsShow
	cmp	w0, 6
	mov	w19, w0
	bgt	.L418
	mov	w1, 3
	mov	x0, x21
	bl	BsSkip
	add	x0, x29, 256
	add	x0, x0, x19, sxtw 2
	ldr	w2, [x0, -208]
	ldr	w1, [x0, -176]
.L419:
	sub	w1, w1, #1
	add	x3, x29, 256
	mov	w0, w19
	add	x1, x3, x1, sxtw 2
	ldr	w1, [x1, -144]
	mul	w1, w1, w2
	str	w1, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L418:
	mov	w1, 7
	mov	x0, x21
	bl	BsGet
	and	w19, w0, 15
	cmp	w19, 15
	beq	.L422
	sub	w0, w0, #112
	add	x1, x29, 256
	add	w19, w19, 7
	add	x0, x1, x0, sxtw 2
	ldr	w2, [x0, -112]
	ldr	w1, [x0, -56]
	b	.L419
	.p2align 3
.L422:
	mov	w1, 4
	strb	w1, [x22]
	mov	w0, 22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 256
	ret
	.size	VC1_DecBfractionSMP, .-VC1_DecBfractionSMP
	.align	3
.LC95:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecBfraction
	.type	VC1_DecBfraction, %function
VC1_DecBfraction:
	stp	x29, x30, [sp, -256]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x19, .LC101
	add	x0, x19, 248
	ldr	w6, [x19, 152]
	ldr	x8, [x19, 176]
	str	w6, [x29, 72]
	add	x6, x29, 200
	ldr	w5, [x19, 184]
	ldr	x4, [x19, 240]
	str	x8, [x29, 96]
	add	x8, x29, 216
	ldp	x2, x3, [x19, 128]
	str	w5, [x29, 104]
	str	x4, [x29, 192]
	ldp	x4, x5, [x0]
	stp	x4, x5, [x6]
	stp	x2, x3, [x29, 48]
	ldp	x4, x5, [x0, 16]
	ldp	x2, x3, [x19, 160]
	add	x6, x19, 304
	ldr	x7, [x19, 144]
	stp	x4, x5, [x8]
	stp	x2, x3, [x29, 80]
	add	x4, x29, 232
	str	x7, [x29, 64]
	ldp	x2, x3, [x19, 192]
	stp	x2, x3, [x29, 144]
	ldp	x2, x3, [x19, 208]
	stp	x2, x3, [x29, 160]
	ldp	x2, x3, [x0, 32]
	stp	x2, x3, [x4]
	ldp	x2, x3, [x6]
	ldp	x0, x1, [x19, 224]
	ldr	x7, [x19, 296]
	stp	x2, x3, [x29, 112]
	ldp	x2, x3, [x6, 16]
	stp	x0, x1, [x29, 176]
	mov	w1, 3
	mov	x0, x22
	str	x7, [x29, 248]
	stp	x2, x3, [x29, 128]
	bl	BsShow
	cmp	w0, 6
	mov	w20, w0
	bgt	.L424
	mov	w1, 3
	mov	x0, x22
	bl	BsSkip
	add	x0, x29, 256
	add	x0, x0, x20, sxtw 2
	ldr	w4, [x0, -176]
	ldr	w1, [x0, -208]
	sub	w0, w4, #1
	cmp	w0, 7
	bhi	.L428
.L430:
	add	x2, x29, 256
	add	x0, x2, x0, sxtw 2
	ldr	w0, [x0, -144]
	mul	w0, w1, w0
.L429:
	str	w0, [x21]
.L426:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L424:
	mov	w1, 7
	mov	x0, x22
	bl	BsGet
	and	w20, w0, 15
	sub	w1, w20, #14
	add	w20, w20, 7
	cmp	w1, 1
	bls	.L426
	sub	w1, w0, #112
	cmp	w1, 13
	bhi	.L427
	add	x0, x29, 256
	add	x0, x0, x1, sxtw 2
	ldr	w4, [x0, -56]
	ldr	w1, [x0, -112]
	sub	w0, w4, #1
	cmp	w0, 7
	bls	.L430
.L428:
	ldr	x1, .LC105
	mov	w3, 3214
	add	x2, x19, 336
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L429
	.p2align 3
.L427:
	ldr	x1, .LC103
	mov	w4, w0
	mov	w3, 3204
	add	x2, x19, 336
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x1, .LC105
	mov	w4, 0
	mov	w3, 3214
	add	x2, x19, 336
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L429
	.size	VC1_DecBfraction, .-VC1_DecBfraction
	.align	3
.LC101:
	.xword	.LANCHOR0
	.align	3
.LC103:
	.xword	.LC102
	.align	3
.LC105:
	.xword	.LC104
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_VopDQuant
	.type	VC1_VopDQuant, %function
VC1_VopDQuant:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	uxtb	w21, w1
	uxtb	w20, w2
	mov	x19, x3
	bl	_mcount
	cmp	w21, 2
	beq	.L449
	mov	w1, 1
	mov	x0, x22
	bl	BsGet
	uxtb	w21, w0
	cmp	w21, 1
	strb	w21, [x19]
	beq	.L450
.L435:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L449:
	mov	w0, 1
	mov	w1, 3
	strb	w0, [x19, 3]
	strb	w0, [x19]
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 7
	strb	w0, [x19, 4]
	beq	.L451
	add	w20, w20, 1
	add	w0, w0, w20
	strb	w0, [x19, 8]
.L434:
	mov	w0, 1
	str	w0, [x19, 12]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L450:
	mov	w1, 2
	mov	x0, x22
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19, 1]
	cbnz	w1, .L437
	str	w21, [x19, 12]
.L438:
	ldr	w0, [x19]
	and	w0, w0, 16776960
	cmp	w0, 768
	beq	.L435
	mov	w0, 1
	mov	w1, 3
	strb	w0, [x19, 3]
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 7
	strb	w0, [x19, 4]
	beq	.L452
	add	w20, w20, 1
	add	w0, w0, w20
	strb	w0, [x19, 8]
	b	.L435
	.p2align 3
.L437:
	cmp	w1, 2
	beq	.L453
	cmp	w1, 1
	beq	.L454
	cmp	w1, 3
	beq	.L455
	str	wzr, [x19, 12]
	b	.L438
.L455:
	mov	w1, w21
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	mov	w1, 10
	mov	w2, 11
	cmp	w0, wzr
	strb	w0, [x19, 2]
	csel	w0, w1, w2, ne
	str	w0, [x19, 12]
	b	.L438
	.p2align 3
.L451:
	mov	w1, 5
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 5]
	strb	w0, [x19, 8]
	b	.L434
.L453:
	mov	x0, x22
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x19, 6]
	add	w0, w1, 6
	str	w0, [x19, 12]
	b	.L438
.L454:
	mov	w1, 2
	mov	x0, x22
	bl	BsGet
	and	w1, w0, 255
	strb	w0, [x19, 7]
	add	w0, w1, 2
	str	w0, [x19, 12]
	b	.L438
.L452:
	mov	w1, 5
	mov	x0, x22
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 5]
	strb	w0, [x19, 8]
	b	.L435
	.size	VC1_VopDQuant, .-VC1_VopDQuant
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecNormDiff6Tile
	.type	VC1_DecNormDiff6Tile, %function
VC1_DecNormDiff6Tile:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x1
	mov	x20, x0
	mov	x0, x30
	mov	w22, 0
	bl	_mcount
	ldr	w24, [x23]
	b	.L457
	.p2align 3
.L467:
	mov	w22, w19
.L457:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	mov	w21, w0
	mov	w1, 3
	mov	x0, x20
	cbnz	w21, .L466
	bl	BsGet
	cmp	w0, 1
	mov	w19, w0
	mov	w1, w0
	mov	x0, x20
	bgt	.L476
	bne	.L460
	bl	BsGet
	cbz	w0, .L461
	cbz	w22, .L467
.L473:
	str	w24, [x23]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L466:
	mov	w0, 0
.L458:
	eor	w1, w0, 63
	cmp	w22, wzr
	csel	w0, w1, w0, ne
	mov	w21, 1
	str	w0, [x23]
.L478:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L476:
	sub	w19, w19, #2
	mov	w0, 1
	lsl	w0, w0, w19
	b	.L458
	.p2align 3
.L460:
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	cmp	w0, 255
	beq	.L473
	ldr	x1, .LC111
	add	x1, x1, 488
	ldr	w0, [x1, w0, sxtw 2]
	b	.L458
	.p2align 3
.L461:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	ldr	x1, .LC111
	add	x1, x1, 360
	ldr	w1, [x1, w0, sxtw 2]
	cmp	w1, 2
	beq	.L477
	cmp	w1, 3
	beq	.L458
	str	w0, [x23]
	b	.L478
.L477:
	orr	w0, w0, 32
	b	.L458
	.size	VC1_DecNormDiff6Tile, .-VC1_DecNormDiff6Tile
	.align	3
.LC111:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvSeqHdr
	.type	VC1_Vfmw_ParseAdvSeqHdr, %function
VC1_Vfmw_ParseAdvSeqHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x2
	bl	_mcount
	add	x19, x22, 16
	ldr	x3, .LC114
	mov	x2, 172
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	x0, x20
	bl	BsPos
	str	w0, [x19, 168]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	mov	w0, 2
	mov	w1, 3
	strb	w0, [x22, 16]
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 1]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 12
	mov	x0, x20
	bl	BsGet
	uxth	w0, w0
	add	w2, w0, 1
	mov	w1, 12
	ubfiz	w2, w2, 1, 15
	mov	x0, x20
	strh	w2, [x19, 156]
	bl	BsGet
	uxth	w0, w0
	add	w2, w0, 1
	mov	w1, 1
	ubfiz	w2, w2, 1, 15
	mov	x0, x20
	strh	w2, [x19, 158]
	bl	BsGet
	strb	w0, [x19, 6]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w21, w0
	cmp	w21, 1
	strb	w21, [x19, 10]
	beq	.L493
	ldrh	w1, [x19, 156]
	ldrh	w0, [x19, 158]
	strh	w1, [x19, 160]
	strh	w0, [x19, 162]
.L486:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 23]
	beq	.L487
.L489:
	mov	x0, x20
	bl	BsPos
	ldr	w1, [x19, 168]
	mov	w2, 1
	sub	w0, w0, w1
	str	w0, [x19, 168]
.L488:
	mov	w0, w2
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L487:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 31
	strb	w0, [x19, 24]
	mov	w2, 0
	bhi	.L488
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 25]
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 26]
	ldrb	w1, [x19, 24]
	cbz	w1, .L489
	mov	w21, 0
	.p2align 2
.L490:
	add	x23, x22, x21, sxtw 1
	mov	w1, 16
	mov	x0, x20
	add	w21, w21, 1
	bl	BsGet
	strh	w0, [x23, 44]
	mov	w1, 16
	mov	x0, x20
	bl	BsGet
	strh	w0, [x23, 108]
	ldrb	w0, [x19, 24]
	cmp	w0, w21
	bgt	.L490
	b	.L489
	.p2align 3
.L493:
	mov	w1, 14
	mov	x0, x20
	bl	BsGet
	add	w0, w0, 1
	mov	w1, 14
	strh	w0, [x19, 160]
	mov	x0, x20
	bl	BsGet
	add	w0, w0, 1
	mov	w1, w21
	strh	w0, [x19, 162]
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 11]
	beq	.L494
.L482:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w1, w0
	cmp	w1, 1
	strb	w1, [x19, 15]
	beq	.L495
.L484:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 19]
	bne	.L486
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 20]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 22]
	b	.L486
	.p2align 3
.L495:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 16]
	cbnz	w0, .L485
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 17]
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	b	.L484
	.p2align 3
.L494:
	mov	w1, 4
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 15
	strb	w0, [x19, 12]
	bne	.L482
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 13]
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 14]
	b	.L482
.L485:
	mov	w1, 16
	mov	x0, x20
	bl	BsGet
	strh	w0, [x19, 164]
	b	.L484
	.size	VC1_Vfmw_ParseAdvSeqHdr, .-VC1_Vfmw_ParseAdvSeqHdr
	.align	3
.LC114:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvEntptHdr
	.type	VC1_Vfmw_ParseAdvEntptHdr, %function
VC1_Vfmw_ParseAdvEntptHdr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	bl	_mcount
	add	x19, x21, 188
	ldr	x3, .LC115
	mov	x2, 60
	mov	w1, 0
	mov	x0, x19
	add	x22, x21, 16
	ldr	x3, [x3, 96]
	blr	x3
	mov	x0, x20
	bl	BsPos
	str	w0, [x19, 56]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x21, 188]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 1]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 2]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 6]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 10]
	ldrb	w0, [x22, 23]
	cmp	w0, 1
	beq	.L497
.L500:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 11]
	beq	.L517
.L515:
	ldrh	w0, [x19, 52]
.L502:
	ldrh	w1, [x19, 50]
	ldrh	w2, [x22, 156]
	cmp	w1, 15
	ccmp	w1, w2, 2, hi
	bls	.L503
	strh	w2, [x19, 50]
.L503:
	ldrh	w1, [x22, 158]
	cmp	w0, 15
	ccmp	w1, w0, 0, hi
	bcs	.L504
	strh	w1, [x19, 52]
.L504:
	ldrb	w1, [x19, 6]
	cmp	w1, 1
	beq	.L518
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 13]
	beq	.L519
.L506:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 15]
	beq	.L520
.L507:
	mov	x0, x20
	bl	BsPos
	ldr	w1, [x19, 56]
	sub	w1, w0, w1
	str	w1, [x19, 56]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L497:
	ldrb	w0, [x22, 24]
	cbz	w0, .L500
	mov	w21, 0
	.p2align 2
.L501:
	mov	w1, 8
	mov	x0, x20
	bl	BsGet
	add	x1, x19, x21, sxtw
	add	w21, w21, 1
	strb	w0, [x1, 17]
	ldrb	w0, [x22, 24]
	cmp	w0, w21
	bgt	.L501
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 11]
	bne	.L515
.L517:
	mov	w1, 12
	mov	x0, x20
	bl	BsGet
	add	w0, w0, 1
	ubfiz	w0, w0, 1, 15
	mov	w1, 12
	strh	w0, [x19, 50]
	mov	x0, x20
	bl	BsGet
	add	w0, w0, 1
	ubfiz	w0, w0, 1, 15
	strh	w0, [x19, 52]
	b	.L502
	.p2align 3
.L520:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	b	.L507
	.p2align 3
.L518:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 13]
	bne	.L506
	.p2align 2
.L519:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 14]
	b	.L506
	.size	VC1_Vfmw_ParseAdvEntptHdr, .-VC1_Vfmw_ParseAdvEntptHdr
	.align	3
.LC115:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecFcm
	.type	VC1_DecFcm, %function
VC1_DecFcm:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 2
	mov	x0, x20
	bl	BsShow
	cmp	w0, 1
	mov	w19, w0
	ble	.L524
	mov	w1, 2
	mov	x0, x20
	bl	BsSkip
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L524:
	mov	w1, 1
	mov	x0, x20
	mov	w19, 0
	bl	BsSkip
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_DecFcm, .-VC1_DecFcm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecAdvPtype
	.type	VC1_DecAdvPtype, %function
VC1_DecAdvPtype:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	cmp	w0, 7
	ble	.L527
	cmp	w0, 11
	bgt	.L531
	mov	w1, 2
	mov	w20, w1
.L526:
	mov	x0, x19
	bl	BsSkip
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L531:
	cmp	w0, 13
	ble	.L529
	cmp	w0, 14
	mov	w1, 4
	beq	.L530
	mov	w20, 5
	b	.L526
	.p2align 3
.L527:
	mov	w1, 1
	mov	x0, x19
	mov	w20, w1
	bl	BsSkip
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L529:
	mov	w1, 3
	mov	w20, 0
	b	.L526
	.p2align 3
.L530:
	mov	w20, w1
	b	.L526
	.size	VC1_DecAdvPtype, .-VC1_DecAdvPtype
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecRefdist
	.type	VC1_DecRefdist, %function
VC1_DecRefdist:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsShow
	cmp	w0, 23
	mov	w2, w0
	bgt	.L533
	mov	w1, 2
	mov	x0, x20
	asr	w19, w2, 3
	bl	BsSkip
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L533:
	cmp	w0, 27
	mov	w19, 3
	bgt	.L539
	mov	w1, w19
	mov	x0, x20
	bl	BsSkip
	mov	w0, w19
.L540:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L539:
	mov	w0, 5
	cmp	w2, 29
	mov	w19, 4
	csel	w19, w0, w19, gt
	mov	x0, x20
	mov	w1, w19
	bl	BsSkip
	mov	w0, w19
	b	.L540
	.size	VC1_DecRefdist, .-VC1_DecRefdist
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_DecIntCompField
	.type	VC1_DecIntCompField, %function
VC1_DecIntCompField:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC116
	mov	w1, 2
	mov	x0, x19
	add	x2, x2, 552
	ldp	x4, x5, [x2]
	ldp	x2, x3, [x2, 16]
	stp	x4, x5, [x29, 32]
	stp	x2, x3, [x29, 48]
	bl	BsShow
	add	x1, x29, 64
	add	x1, x1, x0, sxtw 3
	mov	x0, x19
	ldp	w19, w1, [x1, -32]
	bl	BsSkip
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.size	VC1_DecIntCompField, .-VC1_DecIntCompField
	.align	3
.LC116:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_next_start_code
	.type	VC1_Vfmw_next_start_code, %function
VC1_Vfmw_next_start_code:
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
	bgt	.L549
	b	.L546
	.p2align 3
.L552:
	bl	BsSkip
	cmp	w19, w21
	beq	.L546
.L549:
	mov	w1, 24
	mov	x0, x20
	add	w19, w19, 1
	bl	BsShow
	mov	w2, w0
	cmp	w2, 1
	mov	w1, 8
	mov	x0, x20
	bne	.L552
	mov	w0, w2
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L546:
	mov	w2, 0
	ldr	x21, [sp, 32]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VC1_Vfmw_next_start_code, .-VC1_Vfmw_next_start_code
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_UserData
	.type	VC1_Vfmw_UserData, %function
VC1_Vfmw_UserData:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VC1_Vfmw_UserData, .-VC1_Vfmw_UserData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_RecordSlcStream
	.type	VC1_RecordSlcStream, %function
VC1_RecordSlcStream:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	add	x20, x22, 20480
	mov	x21, x1
	mov	x23, x2
	bl	_mcount
	add	x1, x21, 536
	add	x5, x20, 3728
	ldr	w0, [x20, 3724]
	ldr	x4, [x22, 3136]
	uxtw	x21, w0
	lsl	x3, x21, 3
	sub	x3, x3, x21
	lsl	x3, x3, 3
	add	x19, x5, x3
	strb	w0, [x19, 16]
	ldr	w0, [x4, 32]
	ubfx	x0, x0, 3, 29
	add	x0, x23, x0
	str	x0, [x5, x3]
	ldr	w2, [x4, 32]
	and	w2, w2, 7
	str	w2, [x19, 24]
	ldr	w3, [x4, 24]
	ldr	w2, [x4, 32]
	lsl	w3, w3, 3
	sub	w3, w3, w2
	lsl	x2, x21, 2
	sub	x2, x2, x21
	str	w3, [x19, 28]
	add	x21, x1, x2, lsl 2
	bl	MEM_Vir2Phy
	add	x2, x22, 36864
	str	w0, [x19, 20]
	add	x0, x2, 1688
	ldr	w1, [x2, 1724]
	str	w1, [x19, 48]
	ldr	x1, [x2, 1696]
	cbz	x1, .L555
	ldr	w2, [x2, 1712]
	cbnz	w2, .L574
.L555:
	mov	x1, 0
	str	xzr, [x19, 8]
	stp	wzr, wzr, [x19, 36]
	str	wzr, [x19, 44]
	str	wzr, [x19, 52]
.L556:
	ldr	w4, [x20, 3640]
	ldr	w0, [x20, 3644]
	ldrb	w2, [x22, 8]
	mul	w4, w0, w4
	sub	w4, w4, #1
	cbz	w2, .L557
	add	w0, w0, 1
	ldr	w3, [x21, 4]
	add	w0, w0, w0, lsr 31
	sub	w3, w3, w0, asr 1
	str	w3, [x19, 32]
	cmp	w4, w3
	ccmp	w3, wzr, 4, cc
	bgt	.L575
.L558:
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L560
	cbz	x1, .L561
	ldr	w0, [x19, 44]
	cmp	w0, wzr
	ble	.L560
.L561:
	ldr	w1, [x20, 3724]
	mov	w0, 1
	add	w1, w1, w0
	str	w1, [x20, 3724]
.L559:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L557:
	ldr	w3, [x21, 4]
	str	w3, [x19, 32]
	cmp	w4, w3
	bcs	.L558
	ldr	w2, [x21, 4]
	mov	w0, 1
	ldr	x1, .LC121
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L574:
	str	x1, [x19, 8]
	str	wzr, [x19, 40]
	ldr	w2, [x0, 32]
	lsl	w2, w2, 3
	str	w2, [x19, 44]
	ldr	w2, [x0, 24]
	str	w2, [x19, 36]
	ldr	w0, [x0, 40]
	str	w0, [x19, 52]
	b	.L556
	.p2align 3
.L575:
	ldr	x1, .LC119
	mov	w0, 1
	ldr	w4, [x20, 3644]
	ldr	w2, [x21, 4]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L559
	.p2align 3
.L560:
	ldr	x1, .LC123
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	VC1_RecordSlcStream, .-VC1_RecordSlcStream
	.align	3
.LC119:
	.xword	.LC118
	.align	3
.LC121:
	.xword	.LC120
	.align	3
.LC123:
	.xword	.LC122
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_UpdateAdvSPS
	.type	VC1_Vfmw_UpdateAdvSPS, %function
VC1_Vfmw_UpdateAdvSPS:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	add	x21, x0, 8192
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldrh	w1, [x19, 238]
	ldrh	w0, [x21, 2446]
	cmp	w0, w1
	beq	.L577
	add	x0, x20, 20480
	add	w1, w1, 15
	asr	w1, w1, 4
	str	w1, [x0, 3640]
	ldrh	w1, [x19, 238]
	str	w1, [x0, 3656]
	ldrh	w1, [x19, 240]
	ldrh	w2, [x21, 2448]
	cmp	w2, w1
	beq	.L578
.L579:
	add	w1, w1, 15
	asr	w1, w1, 4
	str	w1, [x0, 3644]
	ldrh	w1, [x19, 240]
	str	w1, [x0, 3660]
.L578:
	add	x1, x19, 16
	add	x0, x21, 2224
	add	x19, x19, 188
	mov	x2, 172
	add	x21, x21, 2396
	bl	memcpy
	ldp	x0, x1, [x19]
	stp	x0, x1, [x21]
	mov	w0, 1
	ldp	x2, x3, [x19, 16]
	stp	x2, x3, [x21, 16]
	ldp	x2, x3, [x19, 32]
	stp	x2, x3, [x21, 32]
	ldr	x1, [x19, 48]
	str	x1, [x21, 48]
	ldr	w1, [x19, 56]
	str	w1, [x21, 56]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L577:
	ldrh	w1, [x19, 240]
	ldrh	w0, [x21, 2448]
	cmp	w0, w1
	bne	.L584
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L584:
	add	x0, x20, 20480
	b	.L579
	.size	VC1_Vfmw_UpdateAdvSPS, .-VC1_Vfmw_UpdateAdvSPS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_UpdataLastPicRNDCTRL
	.type	VC1_Vfmw_UpdataLastPicRNDCTRL, %function
VC1_Vfmw_UpdataLastPicRNDCTRL:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L592
	ldrsb	w1, [x19, 3104]
	mov	w0, 1
	cbnz	w1, .L587
	add	x1, x19, 8192
	ldrb	w2, [x1, 2459]
	and	w3, w2, -5
	cbz	w3, .L591
	cmp	w2, w0
	ldrsb	w0, [x19, 10]
	uxtb	w2, w0
	beq	.L593
.L588:
	strb	w0, [x19, 10]
	mov	w0, 1
	strb	w2, [x1, 2478]
.L587:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L591:
	mov	w2, w0
	b	.L588
	.p2align 3
.L593:
	cmp	w0, wzr
	cset	w0, eq
	mov	w2, w0
	sxtb	w0, w0
	b	.L588
.L592:
	ldr	x3, .LC125
	mov	w2, 5809
	ldr	x1, .LC126
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L587
	.size	VC1_Vfmw_UpdataLastPicRNDCTRL, .-VC1_Vfmw_UpdataLastPicRNDCTRL
	.align	3
.LC125:
	.xword	.LC124
	.align	3
.LC126:
	.xword	.LC37
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_DecPQUANT
	.type	VC1_Vfmw_DecPQUANT, %function
VC1_Vfmw_DecPQUANT:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x1, .LC127
	mov	x2, 128
	add	x0, x29, 32
	add	x1, x1, 584
	bl	memcpy
	mov	w0, w19
	cbnz	w20, .L595
	add	x0, x29, 160
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, -128]
.L595:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 160
	ret
	.size	VC1_Vfmw_DecPQUANT, .-VC1_Vfmw_DecPQUANT
	.align	3
.LC127:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseSMPIPicHdr
	.type	VC1_Vfmw_ParseSMPIPicHdr, %function
VC1_Vfmw_ParseSMPIPicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x23, x1
	bl	_mcount
	add	x19, x21, 248
	mov	w1, 7
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 5]
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 6]
	mov	w1, 0
	cbz	w22, .L598
	ldrb	w24, [x21, 14]
	mov	w1, w22
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 104]
	cmp	w22, 8
	bls	.L609
	strb	wzr, [x19, 7]
.L600:
	cmp	w24, 1
	beq	.L610
	strb	wzr, [x19, 8]
.L602:
	ldrb	w0, [x21, 7]
	cmp	w0, 1
	beq	.L611
	strb	wzr, [x19, 9]
.L604:
	ldrb	w0, [x19, 3]
	sub	w0, w0, #2
	and	w0, w0, -3
	uxtb	w0, w0
	cbz	w0, .L607
	ldrb	w0, [x21, 4]
	cmp	w0, 1
	beq	.L612
.L607:
	ldrb	w1, [x19, 10]
.L606:
	mov	x0, x23
	bl	VC1_SetCurPicResolutionInfo
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 19]
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 20]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 1
.L598:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L609:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	ldrb	w24, [x21, 14]
	b	.L600
	.p2align 3
.L611:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 9]
	b	.L604
	.p2align 3
.L610:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	b	.L602
	.p2align 3
.L612:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19, 10]
	b	.L606
	.size	VC1_Vfmw_ParseSMPIPicHdr, .-VC1_Vfmw_ParseSMPIPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseSMPPPicHdr
	.type	VC1_Vfmw_ParseSMPPPicHdr, %function
VC1_Vfmw_ParseSMPPPicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x23, x1
	add	x19, x21, 248
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 6]
	cbz	w22, .L625
	ldrb	w24, [x21, 14]
	uxtb	w1, w0
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 104]
	cmp	w22, 8
	bls	.L636
	strb	wzr, [x19, 7]
.L617:
	cmp	w24, 1
	beq	.L637
	strb	wzr, [x19, 8]
.L619:
	ldrb	w0, [x21, 7]
	cmp	w0, 1
	beq	.L638
	strb	wzr, [x19, 9]
.L621:
	ldrb	w0, [x21, 4]
	cmp	w0, 1
	beq	.L622
	ldrb	w1, [x19, 10]
.L623:
	mov	x0, x23
	bl	VC1_SetCurPicResolutionInfo
	mov	x0, x20
	bl	BsPos
	mov	w2, w0
	ldr	x1, .LC129
	mov	w0, 18
	bl	dprint_vfmw
	ldrb	w1, [x19, 104]
	mov	x0, x20
	bl	VC1_DecMvmodeProgrP
	uxtb	w0, w0
	cmp	w0, 4
	strb	w0, [x19, 11]
	beq	.L639
.L624:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x23
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L625
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 15]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	ldrb	w1, [x21, 8]
	cbnz	w1, .L640
.L626:
	mov	x0, x20
	bl	BsPos
	mov	w2, w0
	ldr	x1, .LC131
	mov	w0, 18
	bl	dprint_vfmw
	ldrb	w1, [x21, 9]
	cmp	w1, 1
	beq	.L641
.L628:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 19]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L625:
	mov	w1, 0
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L636:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	ldrb	w24, [x21, 14]
	b	.L617
	.p2align 3
.L640:
	ldrb	w2, [x19, 104]
	add	x3, x21, 272
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L626
	.p2align 3
.L639:
	ldrb	w1, [x19, 104]
	mov	x0, x20
	bl	VC1_DecMvmode2
	strb	w0, [x19, 12]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 13]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 14]
	b	.L624
	.p2align 3
.L622:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w1, w0
	strb	w1, [x19, 10]
	b	.L623
	.p2align 3
.L638:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 9]
	b	.L621
	.p2align 3
.L637:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	b	.L619
	.p2align 3
.L641:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 17]
	bne	.L628
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	b	.L628
	.size	VC1_Vfmw_ParseSMPPPicHdr, .-VC1_Vfmw_ParseSMPPPicHdr
	.align	3
.LC129:
	.xword	.LC128
	.align	3
.LC131:
	.xword	.LC130
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseMPBPicHdr
	.type	VC1_Vfmw_ParseMPBPicHdr, %function
VC1_Vfmw_ParseMPBPicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x24, x1
	add	x19, x21, 248
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 6]
	cbz	w22, .L652
	ldrb	w23, [x21, 14]
	uxtb	w1, w0
	mov	w0, w23
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 104]
	cmp	w22, 8
	bls	.L664
	strb	wzr, [x19, 7]
.L646:
	cmp	w23, 1
	beq	.L665
	strb	wzr, [x19, 8]
.L648:
	ldrb	w0, [x21, 7]
	cmp	w0, 1
	beq	.L666
	strb	wzr, [x19, 9]
.L650:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	mov	w1, 3
	mov	w3, 0
	csinc	w0, w1, wzr, eq
	mov	x2, x21
	strb	w0, [x19, 11]
	mov	x1, x24
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L652
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 15]
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	ldrb	w1, [x21, 8]
	cbnz	w1, .L667
.L653:
	ldrb	w1, [x21, 9]
	cmp	w1, 1
	beq	.L668
.L655:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 19]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	mov	w1, 1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L652:
	mov	w1, 0
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L664:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 7]
	ldrb	w23, [x21, 14]
	b	.L646
	.p2align 3
.L667:
	ldrb	w2, [x19, 104]
	add	x3, x21, 272
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L653
	.p2align 3
.L666:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 9]
	b	.L650
	.p2align 3
.L665:
	mov	w1, w23
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	b	.L648
	.p2align 3
.L668:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 17]
	bne	.L655
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	b	.L655
	.size	VC1_Vfmw_ParseMPBPicHdr, .-VC1_Vfmw_ParseMPBPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseSMPPicHdr
	.type	VC1_Vfmw_ParseSMPPicHdr, %function
VC1_Vfmw_ParseSMPPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	add	x19, x2, 248
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	mov	x22, x2
	bl	_mcount
	ldrb	w23, [x19, 10]
	mov	x0, x21
	mov	w1, w23
	bl	VC1_SetCurPicResolutionInfo
	ldr	w0, [x20, 24]
	cmp	w0, 1
	ble	.L707
	ldr	x25, .LC132
	mov	x2, 112
	mov	w1, 0
	mov	x0, x19
	add	x24, x21, 36864
	ldr	x3, [x25, 96]
	blr	x3
	strb	w23, [x19, 10]
	ldr	x3, [x25, 96]
	add	x0, x21, 20480
	mov	x2, 14336
	mov	w1, 0
	add	x0, x0, 3728
	blr	x3
	ldr	x1, .LC134
	mov	w0, 18
	ldr	w2, [x24, 1680]
	bl	dprint_vfmw
	mov	x0, x20
	bl	BsPos
	str	w0, [x19, 88]
	ldrb	w0, [x22, 15]
	cbnz	w0, .L672
	ldrb	w2, [x22, 248]
.L673:
	ldr	x1, .LC136
	mov	w0, 18
	bl	dprint_vfmw
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 1]
	ldrb	w0, [x22, 12]
	cbnz	w0, .L708
.L674:
	ldrb	w0, [x22, 13]
	mov	w1, 1
	cbnz	w0, .L675
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	cset	w0, ne
	strb	w0, [x19, 3]
.L676:
	strb	w0, [x21, 2]
	strb	wzr, [x21, 4]
	ldrb	w0, [x19, 3]
	cmp	w0, 4
	bhi	.L705
	ldr	x1, .LC137
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx681
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx681:
	.section	.rodata
	.align	0
	.align	2
.L681:
	.byte	(.L680 - .Lrtx681) / 4
	.byte	(.L682 - .Lrtx681) / 4
	.byte	(.L683 - .Lrtx681) / 4
	.byte	(.L705 - .Lrtx681) / 4
	.byte	(.L684 - .Lrtx681) / 4
	.text
	.p2align 3
.L682:
	mov	x1, x21
	mov	x2, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseSMPPPicHdr
	mov	w21, w0
.L685:
	mov	x0, x20
	bl	BsPos
	ldr	w1, [x19, 88]
	sub	w0, w0, w1
	str	w0, [x19, 88]
	mov	x0, x20
	ldr	w19, [x24, 1716]
	bl	BsPos
	lsl	w19, w19, 3
	sub	w19, w19, w0
	mov	w0, w21
	cmp	w19, wzr
	bgt	.L698
	ldr	x1, .LC143
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L705:
	mov	w0, 0
.L698:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L707:
	mov	w0, 5
	strb	w0, [x19, 3]
	strb	w0, [x21, 2]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L675:
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	beq	.L709
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	beq	.L710
	mov	w0, 2
	add	x2, x22, 251
	strb	w0, [x19, 3]
	add	x1, x22, 356
	mov	x0, x20
	bl	VC1_DecBfractionSMP
	uxtb	w0, w0
	cmp	w0, 21
	strb	w0, [x19, 4]
	beq	.L705
	ldrb	w0, [x19, 3]
	b	.L676
	.p2align 3
.L672:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w2, w0
	strb	w2, [x22, 248]
	b	.L673
	.p2align 3
.L709:
	strb	w0, [x19, 3]
	b	.L676
	.p2align 3
.L684:
	ldrb	w23, [x21, 3120]
	cmp	w23, 1
	bne	.L705
	mov	x1, x21
	mov	x2, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseSMPIPicHdr
	cmp	w0, 1
	mov	w21, w0
	beq	.L685
	ldr	x1, .LC141
	mov	w0, w23
	bl	dprint_vfmw
	b	.L685
	.p2align 3
.L683:
	ldrb	w23, [x21, 3120]
	cmp	w23, 1
	bne	.L705
	mov	x1, x21
	mov	x2, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseMPBPicHdr
	cmp	w0, 1
	mov	w21, w0
	beq	.L685
	ldr	x1, .LC139
	mov	w0, w23
	bl	dprint_vfmw
	b	.L685
	.p2align 3
.L680:
	mov	x1, x21
	mov	x2, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseSMPIPicHdr
	mov	w21, w0
	b	.L685
	.p2align 3
.L708:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 2]
	b	.L674
	.p2align 3
.L710:
	strb	wzr, [x19, 3]
	mov	w0, 0
	b	.L676
	.size	VC1_Vfmw_ParseSMPPicHdr, .-VC1_Vfmw_ParseSMPPicHdr
	.align	3
.LC132:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC134:
	.xword	.LC133
	.align	3
.LC136:
	.xword	.LC135
	.align	3
.LC137:
	.xword	.L681
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC141:
	.xword	.LC140
	.align	3
.LC143:
	.xword	.LC142
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvIPicHdr
	.type	VC1_Vfmw_ParseAdvIPicHdr, %function
VC1_Vfmw_ParseAdvIPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x25, x1
	bl	_mcount
	add	x23, x21, 16
	mov	w1, 1
	mov	x0, x20
	add	x19, x21, 360
	bl	BsGet
	strb	w0, [x21, 360]
	ldrb	w1, [x23, 7]
	cmp	w1, 1
	beq	.L727
.L712:
	ldr	w0, [x19, 44]
	cbnz	w0, .L713
	ldrb	w1, [x23, 9]
	cmp	w1, 1
	beq	.L728
.L713:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 10]
	cbz	w22, .L721
	add	x26, x21, 188
	ldrb	w24, [x26, 10]
	uxtb	w1, w0
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w22, 8
	bls	.L729
	strb	wzr, [x19, 3]
.L717:
	cmp	w24, 1
	beq	.L730
	strb	wzr, [x19, 11]
.L719:
	ldrb	w0, [x23, 5]
	cmp	w0, 1
	beq	.L731
.L720:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x25
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L721
	mov	x0, x20
	mov	w22, 1
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 23]
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	ldrb	w1, [x26, 7]
	cbz	w1, .L715
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L721:
	mov	w22, 0
.L715:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L729:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w24, [x26, 10]
	b	.L717
	.p2align 3
.L728:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	b	.L713
	.p2align 3
.L727:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	b	.L712
	.p2align 3
.L731:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L720
	.p2align 3
.L730:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L719
	.size	VC1_Vfmw_ParseAdvIPicHdr, .-VC1_Vfmw_ParseAdvIPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvPPicHdr
	.type	VC1_Vfmw_ParseAdvPPicHdr, %function
VC1_Vfmw_ParseAdvPPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x26, x1
	bl	_mcount
	add	x22, x21, 16
	mov	w1, 1
	mov	x0, x20
	add	x19, x21, 360
	bl	BsGet
	strb	w0, [x21, 360]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	beq	.L733
	ldr	w0, [x19, 44]
	cmp	w0, 2
	beq	.L733
	ldrb	w1, [x22, 9]
	cmp	w1, 1
	beq	.L769
.L735:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w23, w0
	strb	w23, [x19, 10]
	cbz	w23, .L749
	add	x24, x21, 188
	ldrb	w25, [x24, 10]
	uxtb	w1, w0
	mov	w0, w25
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w23, 8
	bls	.L770
	strb	wzr, [x19, 3]
.L739:
	cmp	w25, 1
	beq	.L771
	strb	wzr, [x19, 11]
.L741:
	ldrb	w0, [x22, 5]
	cmp	w0, 1
	beq	.L772
.L742:
	ldrb	w0, [x24, 6]
	cmp	w0, 1
	beq	.L773
.L743:
	ldr	w0, [x19, 44]
	cbz	w0, .L774
	ldrb	w0, [x24, 12]
	cmp	w0, 1
	beq	.L775
	strb	wzr, [x19, 25]
.L747:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 26]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, 1
	str	w0, [x19, 120]
	beq	.L776
.L748:
	strb	wzr, [x19, 34]
.L745:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x26
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L749
	ldr	w1, [x19, 44]
	cmp	w1, 2
	beq	.L777
.L750:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	ldr	w1, [x19, 44]
	cbnz	w1, .L751
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
.L752:
	ldr	w22, [x19, 44]
	strb	w0, [x19, 19]
	cmp	w22, 2
	beq	.L778
.L753:
	ldrb	w1, [x24, 7]
	cbnz	w1, .L779
.L755:
	ldrb	w1, [x24, 8]
	cmp	w1, 1
	beq	.L780
.L757:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L749:
	mov	w1, 0
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L733:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	ldrb	w1, [x22, 9]
	cmp	w1, 1
	bne	.L735
.L769:
	ldr	w0, [x19, 44]
	cbnz	w0, .L735
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	b	.L735
	.p2align 3
.L751:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	b	.L752
	.p2align 3
.L770:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w25, [x24, 10]
	b	.L739
	.p2align 3
.L776:
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 17]
	b	.L748
	.p2align 3
.L774:
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmodeProgrP
	uxtb	w0, w0
	cmp	w0, 4
	strb	w0, [x19, 14]
	bne	.L745
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmode2
	strb	w0, [x19, 15]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 17]
	b	.L745
	.p2align 3
.L779:
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L755
	.p2align 3
.L771:
	mov	w1, w25
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L741
	.p2align 3
.L773:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 13]
	b	.L743
	.p2align 3
.L772:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L742
	.p2align 3
.L777:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 27]
	b	.L750
	.p2align 3
.L778:
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 28]
	ldrb	w1, [x19, 26]
	mov	w0, 0
	cmp	w1, 1
	beq	.L781
	strb	w0, [x19, 29]
	b	.L753
	.p2align 3
.L780:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 20]
	bne	.L757
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	b	.L757
	.p2align 3
.L775:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 25]
	b	.L747
.L781:
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 29]
	b	.L753
	.size	VC1_Vfmw_ParseAdvPPicHdr, .-VC1_Vfmw_ParseAdvPPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvBPicHdr
	.type	VC1_Vfmw_ParseAdvBPicHdr, %function
VC1_Vfmw_ParseAdvBPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x25, x1
	bl	_mcount
	add	x22, x21, 16
	mov	w1, 1
	mov	x0, x20
	add	x19, x21, 360
	bl	BsGet
	strb	w0, [x21, 360]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	beq	.L783
	ldr	w2, [x19, 44]
	cmp	w2, 2
	beq	.L783
.L784:
	ldrb	w1, [x22, 9]
	cmp	w1, 1
	beq	.L824
.L785:
	cbnz	w2, .L789
	add	x1, x21, 508
	mov	x0, x20
	bl	VC1_DecBfraction
	uxtb	w0, w0
	cmp	w0, 21
	strb	w0, [x19, 2]
	beq	.L787
.L789:
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w23, w0
	strb	w23, [x19, 10]
	cbz	w23, .L787
	add	x24, x21, 188
	ldrb	w26, [x24, 10]
	uxtb	w1, w0
	mov	w0, w26
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w23, 8
	bls	.L825
	strb	wzr, [x19, 3]
.L792:
	cmp	w26, 1
	beq	.L826
	strb	wzr, [x19, 11]
.L794:
	ldrb	w0, [x22, 5]
	cmp	w0, 1
	beq	.L827
.L795:
	ldr	w0, [x19, 44]
	cmp	w0, 2
	beq	.L828
.L796:
	ldrb	w0, [x24, 6]
	cmp	w0, 1
	beq	.L829
.L797:
	ldr	w0, [x19, 44]
	cbz	w0, .L830
	ldrb	w0, [x24, 12]
	cmp	w0, 1
	beq	.L831
.L801:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 120]
.L800:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x25
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L787
	ldr	w1, [x19, 44]
	cmp	w1, 2
	beq	.L832
.L802:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	ldr	w1, [x19, 44]
	cbnz	w1, .L803
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
.L804:
	ldr	w22, [x19, 44]
	strb	w0, [x19, 19]
	cmp	w22, 2
	beq	.L833
.L805:
	ldrb	w1, [x24, 7]
	cbnz	w1, .L834
.L806:
	ldrb	w1, [x24, 8]
	cmp	w1, 1
	beq	.L835
.L808:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L787:
	mov	w1, 0
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L824:
	cbnz	w2, .L789
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 9]
	ldr	w2, [x19, 44]
	b	.L785
	.p2align 3
.L783:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 8]
	ldr	w2, [x19, 44]
	b	.L784
	.p2align 3
.L803:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	b	.L804
	.p2align 3
.L825:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w26, [x24, 10]
	b	.L792
	.p2align 3
.L830:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	mov	w1, 3
	csinc	w1, w1, wzr, eq
	strb	w1, [x19, 14]
	b	.L800
	.p2align 3
.L834:
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L806
	.p2align 3
.L829:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 13]
	b	.L797
	.p2align 3
.L828:
	add	x1, x21, 508
	mov	x0, x20
	bl	VC1_DecBfraction
	strb	w0, [x19, 2]
	b	.L796
	.p2align 3
.L827:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L795
	.p2align 3
.L826:
	mov	w1, w26
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L794
	.p2align 3
.L835:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 20]
	bne	.L808
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	b	.L808
	.p2align 3
.L833:
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 28]
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 29]
	b	.L805
	.p2align 3
.L832:
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 27]
	b	.L802
	.p2align 3
.L831:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 25]
	b	.L801
	.size	VC1_Vfmw_ParseAdvBPicHdr, .-VC1_Vfmw_ParseAdvBPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvFramePicHdr
	.type	VC1_Vfmw_ParseAdvFramePicHdr, %function
VC1_Vfmw_ParseAdvFramePicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x23, x1
	mov	x21, x2
	bl	_mcount
	mov	w1, 4
	mov	x0, x19
	bl	BsShow
	cmp	w0, 7
	ble	.L857
	cmp	w0, 11
	bgt	.L869
	mov	w24, 2
	mov	w1, w24
.L837:
	add	x20, x21, 360
	mov	x0, x19
	add	x22, x21, 16
	bl	BsSkip
	strb	w24, [x20, 1]
	ldrb	w0, [x23, 3545]
	strb	w0, [x23, 2]
	ldrb	w0, [x22, 8]
	cbnz	w0, .L870
.L838:
	ldrb	w0, [x22, 6]
	cbz	w0, .L839
	ldrb	w0, [x22, 7]
	cbnz	w0, .L840
	mov	w1, 2
	mov	x0, x19
	bl	BsGet
	strb	w0, [x20, 6]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	ldrb	w0, [x22, 6]
	beq	.L844
.L873:
	cmp	w0, 1
	bne	.L843
	ldrb	w0, [x20, 6]
	add	w0, w0, 1
	str	w0, [x20, 144]
.L846:
	ldrb	w1, [x21, 190]
	cmp	w1, 1
	beq	.L847
.L855:
	ldrb	w0, [x20, 1]
	cmp	w0, 5
	bls	.L871
.L861:
	mov	w0, 0
	b	.L848
	.p2align 3
.L871:
	ldr	x1, .LC144
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx850
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx850:
	.section	.rodata
	.align	0
	.align	2
.L850:
	.byte	(.L853 - .Lrtx850) / 4
	.byte	(.L851 - .Lrtx850) / 4
	.byte	(.L852 - .Lrtx850) / 4
	.byte	(.L861 - .Lrtx850) / 4
	.byte	(.L853 - .Lrtx850) / 4
	.byte	(.L854 - .Lrtx850) / 4
	.text
	.p2align 3
.L869:
	cmp	w0, 13
	ble	.L859
	cmp	w0, 14
	beq	.L872
	mov	w24, 5
	mov	w1, 4
	b	.L837
	.p2align 3
.L853:
	mov	x2, x21
	mov	x1, x23
	mov	x0, x19
	bl	VC1_Vfmw_ParseAdvIPicHdr
.L848:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L839:
	mov	w0, 1
	strb	w0, [x20, 4]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	beq	.L842
.L843:
	mov	w0, 1
	str	w0, [x20, 144]
	ldrb	w1, [x21, 190]
	cmp	w1, 1
	bne	.L855
.L847:
	mov	x0, x19
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x20, 7]
	bne	.L855
	ldr	w0, [x20, 144]
	cmp	w0, wzr
	ble	.L855
	mov	w24, 0
	.p2align 2
.L856:
	add	x22, x21, x24, sxtw 2
	mov	w1, 18
	mov	x0, x19
	add	w24, w24, 1
	bl	BsGet
	str	w0, [x22, 412]
	mov	w1, 18
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 428]
	mov	w1, 14
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 444]
	mov	w1, 14
	mov	x0, x19
	bl	BsGet
	str	w0, [x22, 460]
	ldr	w0, [x20, 144]
	cmp	w0, w24
	bgt	.L856
	b	.L855
	.p2align 3
.L842:
	mov	w0, 2
	str	w0, [x20, 144]
	b	.L846
	.p2align 3
.L857:
	mov	w24, 1
	mov	w1, w24
	b	.L837
	.p2align 3
.L870:
	mov	w1, 8
	mov	x0, x19
	bl	BsGet
	str	w0, [x20, 48]
	b	.L838
	.p2align 3
.L840:
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	strb	w0, [x20, 4]
	mov	w1, 1
	mov	x0, x19
	bl	BsGet
	strb	w0, [x20, 5]
	ldrb	w0, [x22, 7]
	cmp	w0, 1
	ldrb	w0, [x22, 6]
	bne	.L873
.L844:
	cmp	w0, 1
	bne	.L842
	ldrb	w0, [x20, 5]
	add	w0, w0, 2
	str	w0, [x20, 144]
	b	.L846
	.p2align 3
.L851:
	mov	x2, x21
	mov	x1, x23
	mov	x0, x19
	bl	VC1_Vfmw_ParseAdvPPicHdr
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L854:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L852:
	mov	x2, x21
	mov	x1, x23
	mov	x0, x19
	bl	VC1_Vfmw_ParseAdvBPicHdr
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L859:
	mov	w24, 0
	mov	w1, 3
	b	.L837
	.p2align 3
.L872:
	mov	w24, 4
	mov	w1, w24
	b	.L837
	.size	VC1_Vfmw_ParseAdvFramePicHdr, .-VC1_Vfmw_ParseAdvFramePicHdr
	.align	3
.LC144:
	.xword	.L850
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvIFieldHdr
	.type	VC1_Vfmw_ParseAdvIFieldHdr, %function
VC1_Vfmw_ParseAdvIFieldHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x2
	mov	x25, x1
	add	x19, x21, 360
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 10]
	cbz	w22, .L882
	add	x24, x21, 188
	ldrb	w23, [x24, 10]
	uxtb	w1, w0
	mov	w0, w23
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w22, 8
	bls	.L888
	strb	wzr, [x19, 3]
.L878:
	cmp	w23, 1
	beq	.L889
	strb	wzr, [x19, 11]
.L880:
	ldrb	w0, [x21, 21]
	cmp	w0, 1
	beq	.L890
.L881:
	mov	w3, 0
	mov	x2, x21
	mov	x1, x25
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L882
	mov	x0, x20
	mov	w22, 1
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 23]
	mov	w1, w22
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	ldrb	w1, [x24, 7]
	cbz	w1, .L876
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	ldr	x25, [sp, 64]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L882:
	mov	w22, 0
.L876:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L888:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w23, [x24, 10]
	b	.L878
	.p2align 3
.L890:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L881
	.p2align 3
.L889:
	mov	w1, w23
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L880
	.size	VC1_Vfmw_ParseAdvIFieldHdr, .-VC1_Vfmw_ParseAdvIFieldHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvPFieldHdr
	.type	VC1_Vfmw_ParseAdvPFieldHdr, %function
VC1_Vfmw_ParseAdvPFieldHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x23, x2
	add	x19, x23, 360
	bl	_mcount
	mov	w1, 5
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 10]
	mov	w1, 0
	cbz	w22, .L892
	add	x21, x23, 188
	ldrb	w24, [x21, 10]
	mov	w1, w22
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w22, 8
	bls	.L919
	strb	wzr, [x19, 3]
.L894:
	cmp	w24, 1
	beq	.L920
	strb	wzr, [x19, 11]
.L896:
	ldrb	w0, [x23, 21]
	cmp	w0, 1
	beq	.L921
.L897:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	strb	w0, [x19, 32]
	cbz	w0, .L922
.L898:
	ldrb	w0, [x21, 6]
	cmp	w0, 1
	beq	.L923
.L899:
	ldrb	w0, [x21, 12]
	cmp	w0, 1
	beq	.L924
.L900:
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmodeProgrP
	uxtb	w0, w0
	cmp	w0, 4
	strb	w0, [x19, 14]
	beq	.L925
.L902:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 27]
	ldrb	w1, [x19, 32]
	cbnz	w1, .L904
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	mov	w1, 3
	strb	w0, [x19, 18]
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 19]
	ldrb	w1, [x19, 14]
	cbz	w1, .L906
.L928:
	ldrh	w0, [x19, 14]
	cmp	w0, 4
	beq	.L906
	ldrb	w1, [x21, 7]
	cbnz	w1, .L926
.L908:
	ldrb	w1, [x21, 8]
	cmp	w1, 1
	beq	.L927
.L910:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
.L892:
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L904:
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	mov	w1, 3
	strb	w0, [x19, 18]
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 19]
	ldrb	w1, [x19, 14]
	cbnz	w1, .L928
.L906:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 29]
	ldrb	w1, [x21, 7]
	cbz	w1, .L908
.L926:
	ldrb	w2, [x19, 116]
	add	x3, x23, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L908
	.p2align 3
.L919:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w24, [x21, 10]
	b	.L894
	.p2align 3
.L922:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	cmp	w0, wzr
	cset	w0, eq
	strb	w0, [x19, 33]
	b	.L898
	.p2align 3
.L925:
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmode2
	strb	w0, [x19, 15]
	mov	x0, x20
	bl	VC1_DecIntCompField
	str	w0, [x19, 128]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 16]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 17]
	ldr	w1, [x19, 128]
	cbnz	w1, .L902
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 132]
	mov	w1, 6
	mov	x0, x20
	bl	BsGet
	str	w0, [x19, 136]
	b	.L902
	.p2align 3
.L924:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 25]
	b	.L900
	.p2align 3
.L927:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 20]
	bne	.L910
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	b	.L910
	.p2align 3
.L923:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 13]
	b	.L899
	.p2align 3
.L921:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L897
	.p2align 3
.L920:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L896
	.size	VC1_Vfmw_ParseAdvPFieldHdr, .-VC1_Vfmw_ParseAdvPFieldHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvBFieldHdr
	.type	VC1_Vfmw_ParseAdvBFieldHdr, %function
VC1_Vfmw_ParseAdvBFieldHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	add	x19, x2, 360
	mov	x21, x2
	mov	x25, x1
	bl	_mcount
	mov	w0, 1
	mov	w1, 5
	strb	w0, [x19, 32]
	mov	x0, x20
	bl	BsGet
	uxtb	w22, w0
	strb	w22, [x19, 10]
	cbz	w22, .L939
	add	x23, x21, 188
	ldrb	w24, [x23, 10]
	uxtb	w1, w0
	mov	w0, w24
	bl	VC1_Vfmw_DecPQUANT
	str	w0, [x19, 116]
	cmp	w22, 8
	bls	.L951
	strb	wzr, [x19, 3]
.L933:
	cmp	w24, 1
	beq	.L952
	strb	wzr, [x19, 11]
.L935:
	ldrb	w0, [x21, 21]
	cmp	w0, 1
	beq	.L953
.L936:
	ldrb	w0, [x23, 6]
	cmp	w0, 1
	beq	.L954
.L937:
	ldrb	w0, [x23, 12]
	cmp	w0, 1
	beq	.L955
.L938:
	ldrb	w1, [x19, 116]
	mov	x0, x20
	bl	VC1_DecMvmodeInterB
	strb	w0, [x19, 14]
	mov	w3, 0
	mov	x2, x21
	mov	x1, x25
	mov	x0, x20
	bl	BPD_Drv
	cmp	w0, 1
	beq	.L939
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 27]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 18]
	mov	w1, 3
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 19]
	ldrb	w1, [x19, 14]
	cbz	w1, .L956
.L940:
	ldrb	w1, [x23, 7]
	cbnz	w1, .L957
.L941:
	ldrb	w1, [x23, 8]
	cmp	w1, 1
	beq	.L958
.L943:
	mov	x0, x20
	bl	VC1_DecTransacfrm
	strb	w0, [x19, 22]
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 24]
	mov	w1, 1
	mov	w0, w1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L939:
	mov	w1, 0
	ldr	x25, [sp, 64]
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L951:
	mov	w1, 1
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 3]
	ldrb	w24, [x23, 10]
	b	.L933
	.p2align 3
.L957:
	ldrb	w2, [x19, 116]
	add	x3, x21, 520
	mov	x0, x20
	bl	VC1_VopDQuant
	b	.L941
	.p2align 3
.L956:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 29]
	b	.L940
	.p2align 3
.L955:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 25]
	b	.L938
	.p2align 3
.L954:
	mov	x0, x20
	bl	VC1_DecMvrange
	strb	w0, [x19, 13]
	b	.L937
	.p2align 3
.L953:
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 12]
	b	.L936
	.p2align 3
.L952:
	mov	w1, w24
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 11]
	b	.L935
	.p2align 3
.L958:
	mov	x0, x20
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 20]
	bne	.L943
	mov	w1, 2
	mov	x0, x20
	bl	BsGet
	strb	w0, [x19, 21]
	b	.L943
	.size	VC1_Vfmw_ParseAdvBFieldHdr, .-VC1_Vfmw_ParseAdvBFieldHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvFieldPicHdr
	.type	VC1_Vfmw_ParseAdvFieldPicHdr, %function
VC1_Vfmw_ParseAdvFieldPicHdr:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x20, x1
	mov	x21, x0
	mov	x0, x30
	mov	x22, x2
	bl	_mcount
	ldrb	w0, [x20, 8]
	cbz	w0, .L960
	add	x0, x20, 20480
	ldr	w0, [x0, 3724]
	cbnz	w0, .L960
	add	x19, x22, 360
	ldr	w0, [x19, 156]
	strb	w0, [x19, 1]
	ldrb	w0, [x20, 3545]
	strb	w0, [x20, 2]
.L979:
	ldrb	w0, [x19, 1]
	cmp	w0, 4
	bls	.L1000
.L988:
	ldrb	w1, [x19, 4]
	mov	w0, 0
	cbz	w1, .L986
.L1005:
	ldrb	w1, [x20, 8]
	cmp	w1, wzr
	cset	w1, ne
	strb	w1, [x19, 41]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L960:
	mov	w1, 3
	mov	x0, x21
	add	x19, x22, 360
	add	x23, x22, 16
	bl	BsGet
	sbfiz	x1, x0, 3, 32
	ldr	x2, .LC145
	str	w0, [x19, 124]
	add	x0, x2, x1
	ldr	w1, [x2, x1]
	ldr	w0, [x0, 4]
	stp	w1, w0, [x19, 152]
	uxtb	w1, w1
	ldrb	w2, [x20, 8]
	uxtb	w0, w0
	cmp	w2, wzr
	csel	w0, w0, w1, ne
	strb	w0, [x19, 1]
	ldrb	w0, [x20, 3545]
	strb	w0, [x20, 2]
	ldrb	w0, [x23, 8]
	cbnz	w0, .L1001
	ldrb	w0, [x23, 6]
	cbnz	w0, .L1002
.L965:
	mov	w0, 1
	strb	w0, [x19, 4]
	ldrb	w0, [x23, 7]
	cmp	w0, 1
	beq	.L968
.L969:
	mov	w0, 1
	str	w0, [x19, 144]
.L972:
	add	x23, x22, 188
	ldrb	w1, [x23, 2]
	cmp	w1, 1
	beq	.L973
.L976:
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	strb	w0, [x22, 360]
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	strb	w0, [x19, 8]
	ldrb	w0, [x23, 3]
	cmp	w0, 1
	beq	.L1003
.L975:
	ldr	w0, [x19, 124]
	cmp	w0, 3
	ble	.L979
.L980:
	add	x1, x22, 508
	mov	x0, x21
	bl	VC1_DecBfraction
	strb	w0, [x19, 2]
	ldrb	w0, [x19, 1]
	cmp	w0, 4
	bhi	.L988
	.p2align 2
.L1000:
	ldr	x1, .LC146
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx983
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx983:
	.section	.rodata
	.align	0
	.align	2
.L983:
	.byte	(.L982 - .Lrtx983) / 4
	.byte	(.L984 - .Lrtx983) / 4
	.byte	(.L985 - .Lrtx983) / 4
	.byte	(.L988 - .Lrtx983) / 4
	.byte	(.L982 - .Lrtx983) / 4
	.text
	.p2align 3
.L1002:
	ldrb	w0, [x23, 7]
	cbz	w0, .L1004
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	strb	w0, [x19, 4]
	mov	w1, 1
	mov	x0, x21
	bl	BsGet
	strb	w0, [x19, 5]
.L967:
	ldrb	w0, [x23, 7]
	cmp	w0, 1
	ldrb	w0, [x23, 6]
	beq	.L970
	cmp	w0, 1
	bne	.L969
	ldrb	w0, [x19, 6]
	add	w0, w0, 1
	str	w0, [x19, 144]
	b	.L972
	.p2align 3
.L985:
	mov	x2, x22
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvBFieldHdr
.L981:
	ldrb	w1, [x19, 4]
	cbnz	w1, .L1005
.L986:
	ldrb	w1, [x20, 8]
	cmp	w1, 1
	cset	w1, ne
	strb	w1, [x19, 41]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L984:
	mov	x2, x22
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvPFieldHdr
	b	.L981
	.p2align 3
.L982:
	mov	x2, x22
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvIFieldHdr
	b	.L981
	.p2align 3
.L1001:
	mov	w1, 8
	mov	x0, x21
	bl	BsGet
	str	w0, [x19, 48]
	ldrb	w0, [x23, 6]
	cbz	w0, .L965
	b	.L1002
	.p2align 3
.L1004:
	mov	w1, 2
	mov	x0, x21
	bl	BsGet
	strb	w0, [x19, 6]
	b	.L967
	.p2align 3
.L1003:
	ldr	w0, [x19, 124]
	cmp	w0, 3
	bgt	.L980
	mov	x0, x21
	bl	VC1_DecRefdist
	strb	w0, [x19, 31]
	b	.L975
	.p2align 3
.L968:
	mov	w0, 2
	str	w0, [x19, 144]
	b	.L972
	.p2align 3
.L970:
	cmp	w0, 1
	bne	.L968
	ldrb	w0, [x19, 5]
	add	w0, w0, 2
	str	w0, [x19, 144]
	b	.L972
	.p2align 3
.L973:
	mov	x0, x21
	bl	BsGet
	uxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 7]
	bne	.L976
	ldr	w0, [x19, 144]
	cmp	w0, wzr
	ble	.L976
	mov	w25, 0
	.p2align 2
.L977:
	add	x24, x22, x25, sxtw 2
	mov	w1, 18
	mov	x0, x21
	add	w25, w25, 1
	bl	BsGet
	str	w0, [x24, 412]
	mov	w1, 18
	mov	x0, x21
	bl	BsGet
	str	w0, [x24, 428]
	mov	w1, 14
	mov	x0, x21
	bl	BsGet
	str	w0, [x24, 444]
	mov	w1, 14
	mov	x0, x21
	bl	BsGet
	str	w0, [x24, 460]
	ldr	w0, [x19, 144]
	cmp	w0, w25
	bgt	.L977
	b	.L976
	.size	VC1_Vfmw_ParseAdvFieldPicHdr, .-VC1_Vfmw_ParseAdvFieldPicHdr
	.align	3
.LC145:
	.xword	.LANCHOR1
	.align	3
.LC146:
	.xword	.L983
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvPicHdr
	.type	VC1_Vfmw_ParseAdvPicHdr, %function
VC1_Vfmw_ParseAdvPicHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	bl	_mcount
	add	x2, x19, 20480
	add	x0, x19, 36864
	ldr	w1, [x2, 3640]
	str	w1, [x0, 1760]
	lsl	w4, w1, 4
	ldr	w3, [x2, 3644]
	str	w3, [x0, 1764]
	str	w4, [x0, 1752]
	lsl	w4, w3, 4
	mul	w1, w1, w3
	str	w1, [x0, 1768]
	str	w4, [x0, 1756]
	ldrb	w0, [x19, 8]
	cbz	w0, .L1007
	ldr	w0, [x2, 3724]
	cbz	w0, .L1017
.L1007:
	ldrb	w23, [x20, 23]
	cmp	w23, 1
	beq	.L1018
	mov	w1, 0
	mov	w0, 0
.L1009:
	str	w0, [x20, 404]
	mov	x2, x20
	cbz	w1, .L1019
.L1011:
	mov	x1, x19
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvFieldPicHdr
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1017:
	ldr	w1, [x20, 404]
	mov	x2, x20
	and	w1, w1, -3
	cbnz	w1, .L1011
.L1019:
	mov	x1, x19
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvFramePicHdr
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1018:
	mov	w1, 2
	mov	x0, x21
	bl	BsShow
	cmp	w0, 1
	mov	w22, w0
	ble	.L1020
	mov	w1, 2
	mov	x0, x21
	bl	BsSkip
	and	w1, w22, -3
	mov	w0, w22
	b	.L1009
	.p2align 3
.L1020:
	mov	w1, w23
	mov	x0, x21
	bl	BsSkip
	mov	w1, 0
	mov	w0, 0
	b	.L1009
	.size	VC1_Vfmw_ParseAdvPicHdr, .-VC1_Vfmw_ParseAdvPicHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvSlcHdr
	.type	VC1_Vfmw_ParseAdvSlcHdr, %function
VC1_Vfmw_ParseAdvSlcHdr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x22, x1
	mov	x21, x2
	bl	_mcount
	add	x2, x22, 20480
	mov	w1, 9
	mov	x0, x20
	ldr	w19, [x2, 3724]
	bl	BsGet
	mov	w1, 1
	uxtw	x19, w19
	lsl	x2, x19, 2
	sub	x19, x2, x19
	add	x19, x21, x19, lsl 2
	str	w0, [x19, 540]
	mov	x0, x20
	bl	BsGet
	sxtb	w0, w0
	cmp	w0, 1
	strb	w0, [x19, 536]
	beq	.L1024
	mov	w0, 1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1024:
	add	x19, x22, 4096
	add	x4, x21, 188
	add	x3, x19, 2884
	mov	x2, 172
	add	x23, x19, 2696
	ldp	x0, x1, [x4]
	stp	x0, x1, [x3]
	add	x1, x21, 16
	add	x0, x19, 2712
	ldp	x6, x7, [x4, 16]
	stp	x6, x7, [x3, 16]
	ldp	x6, x7, [x4, 32]
	stp	x6, x7, [x3, 32]
	ldr	x5, [x21, 236]
	str	x5, [x3, 48]
	ldr	w4, [x21, 244]
	str	w4, [x22, 7036]
	bl	memcpy
	add	x1, x21, 360
	mov	x2, 176
	add	x0, x19, 3056
	bl	memcpy
	mov	x2, x23
	mov	x1, x22
	mov	x0, x20
	bl	VC1_Vfmw_ParseAdvPicHdr
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	VC1_Vfmw_ParseAdvSlcHdr, .-VC1_Vfmw_ParseAdvSlcHdr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_ClearCurPacket
	.type	VC1_ClearCurPacket, %function
VC1_ClearCurPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x19, 36]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
	ldrsb	w0, [x19, 16]
	cmp	w0, 1
	beq	.L1026
	ldr	w1, [x19, 40]
	mov	w0, w20
	bl	SM_ReleaseStreamSeg
.L1026:
	ldr	x3, .LC147
	mov	x2, 48
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VC1_ClearCurPacket, .-VC1_ClearCurPacket
	.align	3
.LC147:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_ClearCurPic
	.type	VC1_ClearCurPic, %function
VC1_ClearCurPic:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	w23, w1
	bl	_mcount
	cbz	x22, .L1047
	cmp	w23, 32
	bhi	.L1048
	ldrsb	w0, [x22, 3104]
	cbz	w0, .L1034
	add	x24, x22, 20480
	mov	w20, 0
	ldr	w0, [x24, 3724]
	cbnz	w0, .L1043
	b	.L1030
	.p2align 3
.L1036:
	ldr	w0, [x24, 3724]
	cmp	w0, w20
	bls	.L1030
.L1043:
	sxtw	x19, w20
	mov	w0, w23
	lsl	x1, x19, 3
	add	w20, w20, 1
	sub	x19, x1, x19
	add	x19, x22, x19, lsl 3
	add	x21, x19, 20480
	ldr	w1, [x21, 3776]
	bl	SM_ReleaseStreamSeg
	ldr	x0, [x19, 24216]
	cbz	x0, .L1036
	ldr	w0, [x21, 3764]
	cbz	w0, .L1036
	ldr	w1, [x21, 3780]
	mov	w0, w23
	bl	SM_ReleaseStreamSeg
	ldr	w0, [x24, 3724]
	cmp	w0, w20
	bhi	.L1043
.L1030:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1048:
	ldr	x1, .LC151
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1034:
	add	x1, x22, 36864
	mov	w0, w23
	add	x1, x1, 1688
	bl	VC1_ClearCurPacket
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1047:
	ldr	x1, .LC149
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1030
	.size	VC1_ClearCurPic, .-VC1_ClearCurPic
	.align	3
.LC149:
	.xword	.LC148
	.align	3
.LC151:
	.xword	.LC150
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_VDMPostProc
	.type	VC1DEC_VDMPostProc, %function
VC1DEC_VDMPostProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cbz	x19, .L1083
	add	x21, x19, 12288
	ldr	x2, [x19, 8]
	add	x0, x21, 2520
	add	x20, x19, 53248
	add	x1, x0, 36864
	add	x24, x0, 20480
	ldrb	w3, [x2, 75]
	strb	w3, [x1, 1817]
	ldr	w2, [x2, 14600]
	str	w2, [x1, 1820]
	ldr	w1, [x20, 896]
	bl	VC1_ClearCurPic
	ldr	w1, [x24, 3716]
	ldr	w0, [x20, 896]
	bl	FSP_GetFsImagePtr
	mov	x23, x0
	ldr	w1, [x24, 3712]
	ldr	w0, [x20, 896]
	bl	FSP_GetFsImagePtr
	mov	x25, x0
	ldr	w1, [x24, 3708]
	ldr	w0, [x20, 896]
	bl	FSP_GetFsImagePtr
	cbz	x23, .L1084
	tbnz	w22, #31, .L1070
	mov	w0, 100
	cmp	w22, w0
	csel	w22, w22, w0, le
.L1053:
	mov	x0, x19
	str	w22, [x23, 152]
	bl	VC1_SetImgFormat
	ldrsb	w1, [x21, 2523]
	cmp	w1, 3
	beq	.L1085
.L1054:
	str	xzr, [x23, 544]
	str	xzr, [x23, 552]
	ldr	x0, [x19]
	ldr	w0, [x0, 24]
	cbz	w0, .L1086
	add	x0, x21, 2520
	mov	w24, 0
	add	x0, x0, 20480
	ldr	w1, [x0, 3716]
	str	w1, [x0, 3720]
.L1058:
	add	x23, x21, 2520
	cmn	w1, #1
	add	x2, x23, 36864
	ldr	w0, [x2, 1680]
	add	w0, w0, 1
	str	w0, [x2, 1680]
	beq	.L1059
.L1090:
	ldr	w0, [x20, 896]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L1087
	ldr	w2, [x0, 152]
	cbz	w2, .L1061
	ldr	x0, [x19]
	ldr	w3, [x0, 4]
	cmp	w2, w3
	bhi	.L1062
.L1061:
	add	x23, x21, 2520
	ldr	w0, [x20, 896]
	add	x25, x23, 20480
	ldr	w26, [x25, 3720]
	mov	w1, w26
	bl	FSP_GetRef
	mov	w3, w0
	ldr	x1, .LC159
	mov	w2, w26
	mov	w0, 12
	bl	dprint_vfmw
	ldr	w0, [x20, 896]
	mov	w2, 1
	ldr	w1, [x25, 3720]
	bl	FSP_SetDisplay
	cbnz	w24, .L1088
	ldr	x1, [x23, 24088]
	mov	w2, 1
	mov	w0, 2
	strb	w2, [x1, 1]
	strb	w0, [x23, 1]
.L1064:
	ldr	w0, [x20, 896]
	mov	x4, x22
	add	x3, x20, 288
	mov	x2, x19
	mov	w1, 1
	bl	InsertImgToVoQueue
	cmp	w0, 1
	beq	.L1065
	ldr	w0, [x20, 896]
	add	x21, x21, 2520
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x20, 896]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	add	x0, x21, 20480
	mov	w2, 0
	ldr	w1, [x0, 3720]
	ldr	w0, [x20, 896]
	bl	FSP_SetDisplay
	cbnz	w24, .L1089
	ldr	x1, [x21, 24088]
	mov	w0, 0
	strb	wzr, [x1, 1]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1086:
	add	x1, x21, 2520
	ldrb	w0, [x1, 2]
	sub	w0, w0, #2
	and	w0, w0, -3
	uxtb	w0, w0
	cbz	w0, .L1056
	add	x1, x1, 20480
	ldr	w2, [x1, 3704]
	cmp	w2, 1
	bls	.L1071
	ldr	w1, [x1, 3708]
.L1057:
	add	x0, x21, 2520
	add	x23, x21, 2520
	add	x0, x0, 20480
	cmp	w2, 1
	add	x2, x23, 36864
	cset	w24, hi
	cmn	w1, #1
	str	w1, [x0, 3720]
	ldr	w0, [x2, 1680]
	add	w0, w0, 1
	str	w0, [x2, 1680]
	bne	.L1090
	.p2align 2
.L1059:
	mov	w0, 1
.L1051:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1083:
	ldr	x3, .LC152
	mov	w2, 502
	ldr	x1, .LC153
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1056:
	add	x0, x1, 20480
	ldr	w1, [x0, 3716]
	str	w1, [x0, 3720]
	cbz	x25, .L1072
	ldr	x2, [x23, 584]
	mov	w24, 0
	ldr	x3, [x25, 584]
	cmp	x3, x2
	bge	.L1058
	str	x3, [x23, 584]
	str	x2, [x25, 584]
	ldr	w1, [x0, 3720]
	b	.L1058
	.p2align 3
.L1088:
	ldr	x0, [x23, 24104]
	strb	w24, [x0, 1]
	strb	w24, [x23, 1]
	b	.L1064
	.p2align 3
.L1062:
	ldr	x1, .LC161
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w0, [x20, 896]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	str	xzr, [x22, 544]
	ldr	x1, [x22, 552]
	ldr	w0, [x20, 896]
	bl	FreeUsdByDec
	str	xzr, [x22, 552]
	add	x0, x23, 20480
	mov	w2, 0
	ldr	w1, [x0, 3720]
	ldr	w0, [x20, 896]
	bl	FSP_SetDisplay
	cbnz	w24, .L1091
	ldr	x1, [x23, 24088]
	mov	w0, 1
	strb	wzr, [x1, 1]
	b	.L1051
	.p2align 3
.L1085:
	ldrb	w0, [x21, 2529]
	cmp	w0, 1
	bne	.L1059
	b	.L1054
	.p2align 3
.L1070:
	mov	w22, 0
	b	.L1053
	.p2align 3
.L1065:
	add	x21, x21, 2520
	ldrsb	w1, [x21, 1]
	cmp	w1, 3
	beq	.L1092
	cmp	w1, 1
	beq	.L1093
	cmp	w1, 2
	bne	.L1059
	ldr	x1, [x21, 24088]
	strb	wzr, [x1, 1]
	strb	wzr, [x21, 1]
	b	.L1051
	.p2align 3
.L1089:
	ldr	x1, [x21, 24104]
	mov	w0, 0
	strb	wzr, [x1, 1]
	b	.L1051
	.p2align 3
.L1071:
	mov	w1, -1
	b	.L1057
	.p2align 3
.L1093:
	ldr	x2, [x21, 24104]
	mov	w0, w1
	strb	wzr, [x2, 1]
	strb	wzr, [x21, 1]
	b	.L1051
	.p2align 3
.L1092:
	ldr	x0, [x21, 24096]
	strb	wzr, [x0, 1]
	strb	wzr, [x21, 1]
	b	.L1059
	.p2align 3
.L1084:
	ldr	x1, .LC155
	mov	x4, x0
	mov	x3, x25
	mov	x2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1051
	.p2align 3
.L1072:
	mov	w24, 0
	b	.L1058
	.p2align 3
.L1087:
	ldr	x1, .LC157
	mov	w2, 584
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1051
	.p2align 3
.L1091:
	ldr	x1, [x23, 24104]
	mov	w0, w24
	strb	wzr, [x1, 1]
	b	.L1051
	.size	VC1DEC_VDMPostProc, .-VC1DEC_VDMPostProc
	.align	3
.LC152:
	.xword	.LC35
	.align	3
.LC153:
	.xword	.LC37
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_DecodeArbiter
	.type	VC1_Vfmw_DecodeArbiter, %function
VC1_Vfmw_DecodeArbiter:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1150
	add	x19, x20, 12288
	add	x3, x19, 2520
	ldrb	w0, [x19, 2520]
	tbz	x0, 4, .L1148
	mov	w2, -21
	add	x1, x3, 36864
	and	w0, w0, w2
	strb	w0, [x19, 2520]
	ldr	w0, [x1, 1812]
	sub	w0, w0, #2
	cmp	w0, 1
	ldr	x0, [x20]
	bls	.L1098
	add	x3, x3, 20480
	ldr	w2, [x0, 8]
	ldr	w3, [x3, 3704]
.L1099:
	add	x0, x19, 2520
	sub	w1, w2, #1
	add	x0, x0, 36864
	cmp	w1, 3
	str	w2, [x0, 1812]
	bls	.L1151
.L1126:
	mov	w4, 1
	.p2align 2
.L1105:
	cbz	w3, .L1116
.L1115:
	cmp	w3, 1
	bls	.L1152
.L1119:
	cbz	w4, .L1118
	add	x19, x19, 2520
	add	x20, x20, 16384
	ldrsb	w0, [x19, 3104]
	cbnz	w0, .L1121
	add	x1, x20, 1608
	add	x19, x19, 8192
	add	x0, x19, 2048
	add	x20, x20, 1856
	add	x19, x19, 2456
	ldp	x2, x3, [x1]
	stp	x2, x3, [x0, 160]
	mov	w0, 1
	ldp	x2, x3, [x20]
	stp	x2, x3, [x19]
	ldp	x2, x3, [x20, 16]
	stp	x2, x3, [x19, 16]
	ldp	x2, x3, [x20, 32]
	stp	x2, x3, [x19, 32]
	ldp	x2, x3, [x20, 48]
	stp	x2, x3, [x19, 48]
	ldp	x2, x3, [x20, 64]
	stp	x2, x3, [x19, 64]
	ldp	x2, x3, [x20, 80]
	stp	x2, x3, [x19, 80]
	ldp	x2, x3, [x20, 96]
	stp	x2, x3, [x19, 96]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1147:
	ldr	x0, [x20]
	ldr	w1, [x0, 8]
	add	x0, x19, 2520
	add	x0, x0, 36864
	sub	w2, w1, #1
	cmp	w2, 3
	str	w1, [x0, 1812]
	bls	.L1153
	mov	w4, 1
	.p2align 2
.L1116:
	ldrb	w0, [x19, 2522]
	sub	w2, w0, #1
	sub	w1, w0, #4
	uxtb	w2, w2
	uxtb	w1, w1
	cmp	w2, 1
	ccmp	w1, 1, 0, hi
	bls	.L1122
.L1117:
	sub	w0, w0, #2
	and	w0, w0, -3
	uxtb	w0, w0
	cbnz	w0, .L1119
	ldr	x1, .LC170
	mov	w0, 1
	bl	dprint_vfmw
	.p2align 2
.L1118:
	add	x20, x20, 53248
	add	x0, x19, 2520
	ldr	w1, [x20, 896]
	bl	VC1_ClearCurPic
	ldr	x0, .LC172
	ldr	x4, [x0]
	cbz	x4, .L1148
	ldr	w0, [x20, 896]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
.L1148:
	mov	w0, 0
.L1145:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1151:
	ldr	x0, .LC166
	ldrb	w0, [x0,w1,uxtw]
	adr	x1, .Lrtx1107
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1107:
	.section	.rodata
	.align	0
	.align	2
.L1107:
	.byte	(.L1106 - .Lrtx1107) / 4
	.byte	(.L1108 - .Lrtx1107) / 4
	.byte	(.L1109 - .Lrtx1107) / 4
	.byte	(.L1110 - .Lrtx1107) / 4
	.text
	.p2align 3
.L1098:
	ldr	w2, [x0, 8]
	cmp	w2, 1
	ccmp	w2, 4, 4, hi
	beq	.L1100
	add	x3, x3, 20480
	ldr	w3, [x3, 3704]
	b	.L1099
	.p2align 3
.L1109:
	mov	w4, 0
	b	.L1105
	.p2align 3
.L1106:
	ldrb	w0, [x19, 2522]
	sub	w0, w0, #2
	and	w0, w0, -3
	uxtb	w0, w0
	cmp	w0, wzr
	cset	w4, ne
	b	.L1105
	.p2align 3
.L1110:
	add	x0, x19, 2520
	ldrb	w1, [x0, 2]
	cbnz	w1, .L1111
	add	x0, x0, 36864
	mov	w4, 1
	str	wzr, [x0, 1744]
	b	.L1105
	.p2align 3
.L1108:
	ldrb	w0, [x19, 2522]
	cmp	w0, wzr
	cset	w4, eq
	b	.L1105
	.p2align 3
.L1111:
	cmp	w1, 2
	bne	.L1113
	add	x0, x0, 36864
	ldr	w0, [x0, 1744]
	cbnz	w0, .L1126
	mov	w4, 0
	cbnz	w3, .L1115
	.p2align 2
.L1122:
	ldr	x1, .LC168
	mov	w0, 1
	bl	dprint_vfmw
	b	.L1118
	.p2align 3
.L1121:
	add	x21, x19, 8192
	add	x1, x20, 1624
	mov	x2, 172
	add	x0, x21, 2224
	bl	memcpy
	add	x4, x20, 1796
	add	x3, x21, 2396
	mov	x2, 176
	ldp	x0, x1, [x4]
	stp	x0, x1, [x3]
	add	x1, x20, 1968
	add	x0, x21, 2568
	ldp	x6, x7, [x4, 16]
	stp	x6, x7, [x3, 16]
	ldp	x6, x7, [x4, 32]
	stp	x6, x7, [x3, 32]
	ldr	x5, [x4, 48]
	str	x5, [x3, 48]
	ldr	w4, [x20, 1852]
	str	w4, [x19, 10644]
	bl	memcpy
	ldr	w0, [x20, 2012]
	add	x3, x19, 20480
	strb	w0, [x19, 4]
	add	x1, x20, 2144
	ldr	x2, .LC171
	add	x0, x21, 2744
	ldr	w3, [x3, 3724]
	ldr	x4, [x2, 104]
	lsl	x2, x3, 2
	sub	x2, x2, x3
	lsl	x2, x2, 2
	blr	x4
	ldr	x23, [sp, 48]
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1113:
	and	w1, w1, -5
	uxtb	w1, w1
	cmp	w1, 1
	bne	.L1126
	add	x0, x0, 36864
	mov	w4, w1
	str	w1, [x0, 1744]
	cbnz	w3, .L1115
	b	.L1122
	.p2align 3
.L1100:
	ldr	x1, .LC165
	add	x21, x3, 20480
	mov	w0, 2
	add	x23, x20, 53248
	bl	dprint_vfmw
	ldr	w1, [x21, 3712]
	ldr	w0, [x23, 896]
	bl	FSP_GetFsImagePtr
	mov	x22, x0
	cbz	x0, .L1101
	ldr	w0, [x23, 896]
	ldr	x1, [x22, 544]
	bl	FreeUsdByDec
	ldr	w0, [x23, 896]
	ldr	x1, [x22, 552]
	bl	FreeUsdByDec
	ldr	w0, [x23, 896]
	ldr	x1, [x22, 560]
	bl	FreeUsdByDec
	ldr	w0, [x23, 896]
	ldr	x1, [x22, 568]
	bl	FreeUsdByDec
	add	x0, x22, 512
	mov	w2, 1
	stp	xzr, xzr, [x0, 32]
	stp	xzr, xzr, [x0, 48]
	ldr	w1, [x21, 3712]
	ldr	w0, [x23, 896]
	bl	FSP_ClearLogicFs
	ldr	w1, [x21, 3708]
	mov	w2, 1
	ldr	w0, [x23, 896]
	bl	FSP_ClearLogicFs
	str	wzr, [x21, 3708]
	str	wzr, [x21, 3712]
	ldr	w0, [x23, 896]
	bl	FSP_GetNullLogicFs
	str	w0, [x21, 3708]
	str	w0, [x21, 3712]
.L1101:
	add	x0, x19, 2520
	add	x1, x0, 20480
	str	wzr, [x1, 3704]
	ldr	x2, [x0, 24096]
	cbz	x2, .L1147
	ldr	x3, [x0, 24104]
	cbz	x3, .L1147
	strb	wzr, [x2, 1]
	ldr	x2, [x0, 24104]
	strb	wzr, [x2, 1]
	ldr	x2, [x0, 24096]
	strb	wzr, [x2]
	ldr	x0, [x0, 24104]
	strb	wzr, [x0]
	ldr	x0, [x20]
	ldr	w3, [x1, 3704]
	ldr	w2, [x0, 8]
	b	.L1099
.L1153:
	ldr	x0, .LC173
	mov	w3, 0
	ldrh	w0, [x0,w2,uxtw #1]
	adr	x1, .Lrtx1125
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx1125:
	.section	.rodata
	.align	0
	.align	2
.L1125:
	.2byte	(.L1106 - .Lrtx1125) / 4
	.2byte	(.L1108 - .Lrtx1125) / 4
	.2byte	(.L1109 - .Lrtx1125) / 4
	.2byte	(.L1110 - .Lrtx1125) / 4
	.text
.L1150:
	ldr	x3, .LC162
	mov	w2, 2259
	ldr	x1, .LC163
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1145
.L1152:
	ldrb	w0, [x19, 2522]
	b	.L1117
	.size	VC1_Vfmw_DecodeArbiter, .-VC1_Vfmw_DecodeArbiter
	.align	3
.LC162:
	.xword	.LC86
	.align	3
.LC163:
	.xword	.LC37
	.align	3
.LC165:
	.xword	.LC164
	.align	3
.LC166:
	.xword	.L1107
	.align	3
.LC168:
	.xword	.LC167
	.align	3
.LC170:
	.xword	.LC169
	.align	3
.LC171:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC172:
	.xword	g_event_report
	.align	3
.LC173:
	.xword	.L1125
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_StartDecode
	.type	VC1_Vfmw_StartDecode, %function
VC1_Vfmw_StartDecode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1173
	ldr	x0, [x19]
	add	x20, x19, 16
	add	x22, x19, 12288
	add	x21, x22, 2520
	ldr	w1, [x0, 640]
	str	w1, [x20, 14600]
	ldr	w0, [x0, 692]
	str	w0, [x20, 14604]
	ldrsb	w0, [x21, 3104]
	cmp	w0, 1
	beq	.L1157
	mov	x0, x21
	bl	VC1_Vfmw_UpdataLastPicRNDCTRL
.L1157:
	mov	x1, x20
	mov	x0, x19
	add	x23, x22, 2520
	bl	VC1_WritePicMsg
	add	x2, x23, 20480
	ldr	x3, .LC176
	add	x1, x2, 3728
	add	x0, x19, 104
	ldr	w2, [x2, 3724]
	strb	w2, [x20, 74]
	uxtw	x2, w2
	ldr	x4, [x3, 104]
	lsl	x3, x2, 3
	sub	x2, x3, x2
	lsl	x2, x2, 3
	blr	x4
	mov	x0, x21
	mov	x1, x20
	bl	VC1_CfgVDH
	ldrb	w0, [x22, 2522]
	cmp	w0, 1
	bls	.L1174
.L1158:
	cmp	w0, 5
	beq	.L1175
	strb	wzr, [x20, 1]
	add	x23, x22, 2520
	ldrsb	w1, [x22, 2524]
	ldrb	w0, [x22, 2528]
	strb	w1, [x19, 16]
	strb	w1, [x23, 3]
	strb	w0, [x23, 9]
	ldrb	w1, [x20, 3]
	cmp	w1, 2
	beq	.L1176
.L1161:
	and	w0, w1, -5
	uxtb	w0, w0
	cmp	w0, 1
	bne	.L1162
	add	x23, x23, 36864
	str	w0, [x23, 1744]
.L1162:
	ldr	x2, [x19]
	str	x20, [x19, 8]
	ldr	w0, [x2, 952]
	cmp	w0, 1
	beq	.L1177
	cmp	w0, 2
	beq	.L1178
.L1165:
	mov	w0, 1
.L1156:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1178:
	ldr	w0, [x2, 956]
	cmp	w0, wzr
	ccmp	x20, xzr, 4, gt
	beq	.L1165
	sub	w1, w1, #2
	mov	w0, 1
	and	w1, w1, -3
	uxtb	w1, w1
	cbnz	w1, .L1156
	ldr	x1, [x22, 26608]
	add	x3, x19, 53248
	mov	x0, x21
	strb	wzr, [x1, 1]
	ldr	x2, [x19]
	ldr	w1, [x2, 956]
	sub	w1, w1, #1
	str	w1, [x2, 956]
	ldr	w1, [x3, 896]
	bl	VC1_ClearCurPic
	str	xzr, [x19, 8]
	mov	w0, 0
	b	.L1156
	.p2align 3
.L1175:
	mov	w3, 1
	strb	w3, [x20, 1]
	add	x2, x22, 2520
	strb	w3, [x22, 2528]
	ldrsb	w1, [x22, 2525]
	add	x4, x2, 36864
	strb	w1, [x22, 2524]
	add	x23, x22, 2520
	mov	w0, 1
	ldr	w2, [x4, 1768]
	sub	w2, w2, #1
	str	w2, [x20, 14504]
	strb	w1, [x19, 16]
	strb	w1, [x23, 3]
	strb	w0, [x23, 9]
	ldrb	w1, [x20, 3]
	cmp	w1, 2
	bne	.L1161
.L1176:
	add	x24, x23, 36864
	ldr	w0, [x24, 1744]
	cbnz	w0, .L1162
	add	x1, x19, 53248
	mov	x0, x21
	ldr	w1, [x1, 896]
	bl	VC1_ClearCurPic
	ldr	x1, [x23, 24088]
	mov	w0, 0
	strb	wzr, [x1]
	ldr	w1, [x24, 1748]
	add	w1, w1, 1
	str	w1, [x24, 1748]
	str	xzr, [x19, 8]
	b	.L1156
	.p2align 3
.L1174:
	ldrb	w1, [x22, 2524]
	strb	w1, [x22, 2525]
	b	.L1158
	.p2align 3
.L1177:
	cbz	x20, .L1156
	sub	w1, w1, #2
	and	w1, w1, -3
	uxtb	w1, w1
	cbnz	w1, .L1156
	ldr	x2, [x22, 26608]
	add	x1, x19, 53248
	mov	x0, x21
	strb	wzr, [x2, 1]
	ldr	w1, [x1, 896]
	bl	VC1_ClearCurPic
	str	xzr, [x19, 8]
	mov	w0, 0
	b	.L1156
.L1173:
	ldr	x3, .LC174
	mov	w2, 2404
	ldr	x1, .LC175
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1156
	.size	VC1_Vfmw_StartDecode, .-VC1_Vfmw_StartDecode
	.align	3
.LC174:
	.xword	.LC86
	.align	3
.LC175:
	.xword	.LC37
	.align	3
.LC176:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseAdvHdr
	.type	VC1_Vfmw_ParseAdvHdr, %function
VC1_Vfmw_ParseAdvHdr:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w24, w2
	mov	x25, x1
	bl	_mcount
	add	x22, x20, 36864
	ldr	x21, [x20, 3136]
	mov	w1, 32
	strb	wzr, [x20, 6]
	add	x23, x22, 1688
	mov	x0, x21
	bl	BsGet
	ldr	x19, [x22, 1688]
	ldr	w3, [x21, 32]
	uxtb	w26, w0
	ldr	w2, [x23, 28]
	mov	x0, x21
	lsr	w3, w3, 3
	add	x19, x19, x3
	sub	w2, w2, w3
	mov	x1, x19
	bl	BsInit
	sub	w0, w26, #10
	cmp	w0, 5
	bhi	.L1180
	cmp	w26, 11
	beq	.L1248
	ldrb	w1, [x20]
	and	w2, w1, 7
	cmp	w2, 7
	beq	.L1249
	add	x27, x20, 20480
	strb	wzr, [x20, 8]
	ldr	x2, .LC184
	str	wzr, [x27, 3724]
	ldrh	w0, [x2,w0,uxtw #1]
	adr	x2, .Lrtx1196
	add	x0, x2, w0, sxth #2
	br	x0
.Lrtx1196:
	.section	.rodata
	.align	0
	.align	2
.L1196:
	.2byte	(.L1195 - .Lrtx1196) / 4
	.2byte	(.L1212 - .Lrtx1196) / 4
	.2byte	(.L1197 - .Lrtx1196) / 4
	.2byte	(.L1213 - .Lrtx1196) / 4
	.2byte	(.L1199 - .Lrtx1196) / 4
	.2byte	(.L1200 - .Lrtx1196) / 4
	.text
	.p2align 3
.L1180:
	sub	w0, w26, #27
	cmp	w0, 4
	bls	.L1250
	cmp	w26, 254
	beq	.L1251
.L1212:
	mov	w0, w24
	mov	x1, x23
	bl	VC1_ClearCurPacket
	mov	w0, 0
.L1185:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1248:
	ldrb	w0, [x20]
	and	w0, w0, 7
	cmp	w0, 7
	bne	.L1212
	mov	x0, x21
	mov	x2, x25
	mov	x1, x20
	bl	VC1_Vfmw_ParseAdvSlcHdr
	cmp	w0, 1
	mov	w21, w0
	bne	.L1183
	add	x27, x20, 20480
	ldr	w0, [x27, 3724]
	cmp	w0, 255
	bls	.L1184
	mov	w1, w24
	mov	x0, x20
	bl	VC1_ClearCurPic
	ldr	x1, .LC178
	mov	w0, w21
	ldr	w2, [x27, 3724]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1185
	.p2align 3
.L1250:
	mov	x1, x23
	mov	w0, w24
	bl	VC1_ClearCurPacket
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1213:
	ldr	x26, .LC185
.L1243:
	ldr	x3, [x26, 96]
	mov	x2, 176
	mov	w1, 0
	add	x0, x25, 360
	ldrb	w28, [x25, 391]
	blr	x3
	strb	w28, [x25, 391]
.L1201:
	ldr	x3, [x26, 96]
	add	x28, x27, 3728
	mov	x2, 14336
	mov	w1, 0
	mov	x0, x28
	blr	x3
	mov	x0, x21
	bl	BsPos
	str	w0, [x25, 500]
	mov	x2, x25
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvPicHdr
	cmp	w0, 1
	mov	w26, w0
	beq	.L1252
	mov	x1, x23
	mov	w0, w24
	bl	VC1_ClearCurPacket
	ldr	x1, .LC187
	mov	w2, 5701
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w26
	b	.L1185
	.p2align 3
.L1251:
	mov	w1, 32
	mov	x0, x21
	bl	BsGet
	mov	w19, w0
	mov	w1, 32
	mov	x0, x21
	bl	BsGet
	mov	w2, 20553
	mov	w1, 20036
	movk	w2, 0x4853, lsl 16
	movk	w1, 0x4345, lsl 16
	cmp	w19, w2
	ccmp	w0, w1, 0, eq
	bne	.L1212
	add	x1, x20, 20480
	mov	w0, 1
	strb	w0, [x20, 7]
	mov	w0, 1
	ldr	w1, [x1, 3724]
	cbz	w1, .L1185
	ldrb	w1, [x20]
	strb	w0, [x20, 6]
	orr	w1, w1, 16
	strb	w1, [x20]
	b	.L1185
	.p2align 3
.L1249:
	mov	w0, 1
	orr	w1, w1, 16
	strb	w0, [x20, 6]
	mov	w0, 1
	strb	w1, [x20]
	b	.L1185
	.p2align 3
.L1195:
	orr	w0, w1, 32
	mov	x1, x23
	strb	w0, [x20]
	mov	w0, w24
	bl	VC1_ClearCurPacket
	mov	w0, 1
	b	.L1185
	.p2align 3
.L1199:
	mov	x2, x25
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvEntptHdr
	cmp	w0, 1
	mov	w19, w0
	beq	.L1253
.L1210:
	mov	w0, w24
	mov	x1, x23
	bl	VC1_ClearCurPacket
	mov	w0, w19
	b	.L1185
	.p2align 3
.L1200:
	mov	x2, x25
	mov	x1, x20
	mov	x0, x21
	bl	VC1_Vfmw_ParseAdvSeqHdr
	cmp	w0, 1
	mov	w19, w0
	bne	.L1210
	ldrb	w0, [x20]
	orr	w0, w0, 1
	strb	w0, [x20]
	b	.L1210
	.p2align 3
.L1197:
	ldr	x26, .LC185
	mov	w0, 1
	strb	w0, [x20, 8]
	mov	x2, 16
	mov	w1, 0
	add	x0, x25, 520
	ldr	x3, [x26, 96]
	blr	x3
	ldrb	w0, [x20, 8]
	cbnz	w0, .L1201
	b	.L1243
	.p2align 3
.L1183:
	mov	x1, x23
	mov	w0, w24
	bl	VC1_ClearCurPacket
	ldr	x1, .LC183
	mov	w2, 5616
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w21
	b	.L1185
	.p2align 3
.L1252:
	mov	x0, x21
	add	x22, x22, 1688
	bl	BsPos
	ldr	w1, [x25, 500]
	sub	w0, w0, w1
	str	w0, [x25, 500]
	mov	x0, x21
	ldrb	w1, [x20]
	orr	w1, w1, 4
	strb	w1, [x20]
	bl	BsPos
	add	w0, w0, 32
	ldr	w1, [x22, 28]
	cmp	w0, w1, lsl 3
	bge	.L1203
	ldr	w3, [x27, 3724]
	add	x23, x25, 536
	ldr	x2, [x20, 3136]
	uxtw	x0, w3
	lsl	x1, x0, 3
	sub	x1, x1, x0
	lsl	x1, x1, 3
	add	x21, x28, x1
	strb	w3, [x21, 16]
	lsl	x3, x0, 2
	sub	x0, x3, x0
	add	x23, x23, x0, lsl 2
	ldr	w0, [x2, 32]
	ubfx	x0, x0, 3, 29
	add	x0, x19, x0
	str	x0, [x28, x1]
	ldr	w1, [x2, 32]
	and	w1, w1, 7
	str	w1, [x21, 24]
	ldr	w1, [x2, 24]
	ldr	w2, [x2, 32]
	lsl	w1, w1, 3
	sub	w1, w1, w2
	str	w1, [x21, 28]
	bl	MEM_Vir2Phy
	str	w0, [x21, 20]
	ldr	w0, [x22, 36]
	str	w0, [x21, 48]
	ldr	x1, [x22, 8]
	cbz	x1, .L1204
	ldr	w0, [x22, 24]
	cbz	w0, .L1204
	str	x1, [x21, 8]
	str	wzr, [x21, 40]
	ldr	w0, [x22, 32]
	lsl	w0, w0, 3
	str	w0, [x21, 44]
	ldr	w0, [x22, 24]
	str	w0, [x21, 36]
	ldr	w0, [x22, 40]
	str	w0, [x21, 52]
.L1205:
	ldr	w4, [x27, 3640]
	ldr	w0, [x27, 3644]
	ldrb	w2, [x20, 8]
	mul	w4, w0, w4
	sub	w4, w4, #1
	cbz	w2, .L1206
	add	w0, w0, 1
	ldr	w3, [x23, 4]
	add	w0, w0, w0, lsr 31
	sub	w3, w3, w0, asr 1
	str	w3, [x21, 32]
	cmp	w3, wzr
	ccmp	w4, w3, 2, gt
	bcc	.L1254
.L1189:
	ldr	w0, [x21, 28]
	cmp	w0, wzr
	ble	.L1192
	cbz	x1, .L1208
	ldr	w0, [x21, 44]
	cmp	w0, wzr
	ble	.L1192
.L1208:
	ldr	w1, [x27, 3724]
	mov	w0, 1
	add	w1, w1, w0
	str	w1, [x27, 3724]
	b	.L1185
	.p2align 3
.L1203:
	mov	x1, x23
	mov	w0, w24
	bl	VC1_ClearCurPacket
	ldr	x1, .LC187
	mov	w2, 5695
	mov	w0, w26
	bl	dprint_vfmw
	mov	w0, w26
	b	.L1185
	.p2align 3
.L1184:
	uxtw	x4, w0
	add	x3, x27, 3728
	lsl	x1, x4, 3
	ldr	x2, [x20, 3136]
	sub	x1, x1, x4
	add	x22, x25, 536
	lsl	x1, x1, 3
	add	x21, x3, x1
	strb	w0, [x21, 16]
	lsl	x0, x4, 2
	sub	x4, x0, x4
	ldr	w0, [x2, 32]
	add	x22, x22, x4, lsl 2
	ubfx	x0, x0, 3, 29
	add	x0, x19, x0
	str	x0, [x3, x1]
	ldr	w1, [x2, 32]
	and	w1, w1, 7
	str	w1, [x21, 24]
	ldr	w1, [x2, 24]
	ldr	w2, [x2, 32]
	lsl	w1, w1, 3
	sub	w1, w1, w2
	str	w1, [x21, 28]
	bl	MEM_Vir2Phy
	str	w0, [x21, 20]
	ldr	w0, [x23, 36]
	str	w0, [x21, 48]
	ldr	x1, [x23, 8]
	cbz	x1, .L1186
	ldr	w0, [x23, 24]
	cbz	w0, .L1186
	str	x1, [x21, 8]
	str	wzr, [x21, 40]
	ldr	w0, [x23, 32]
	lsl	w0, w0, 3
	str	w0, [x21, 44]
	ldr	w0, [x23, 24]
	str	w0, [x21, 36]
	ldr	w0, [x23, 40]
	str	w0, [x21, 52]
.L1187:
	ldr	w4, [x27, 3640]
	ldr	w0, [x27, 3644]
	ldrb	w2, [x20, 8]
	mul	w4, w0, w4
	sub	w4, w4, #1
	cbz	w2, .L1188
	add	w0, w0, 1
	ldr	w3, [x22, 4]
	add	w0, w0, w0, lsr 31
	sub	w3, w3, w0, asr 1
	str	w3, [x21, 32]
	cmp	w3, wzr
	ccmp	w4, w3, 2, gt
	bcs	.L1189
	ldr	x1, .LC179
	mov	w0, 1
	ldr	w2, [x22, 4]
	ldr	w4, [x27, 3644]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1185
	.p2align 3
.L1204:
	mov	x1, 0
	str	xzr, [x21, 8]
	stp	wzr, wzr, [x21, 36]
	str	wzr, [x21, 44]
	str	wzr, [x21, 52]
	b	.L1205
.L1253:
	mov	x1, x25
	mov	x0, x20
	bl	VC1_Vfmw_UpdateAdvSPS
	ldrb	w0, [x20]
	orr	w0, w0, 2
	strb	w0, [x20]
	b	.L1210
.L1206:
	ldr	w3, [x23, 4]
	str	w3, [x21, 32]
	cmp	w4, w3
	bcs	.L1189
	ldr	x1, .LC180
	mov	w0, 1
	ldr	w2, [x23, 4]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1185
.L1186:
	mov	x1, 0
	str	xzr, [x21, 8]
	stp	wzr, wzr, [x21, 36]
	str	wzr, [x21, 44]
	str	wzr, [x21, 52]
	b	.L1187
.L1188:
	ldr	w3, [x22, 4]
	str	w3, [x21, 32]
	cmp	w4, w3
	bcs	.L1189
	ldr	x1, .LC180
	mov	w0, 1
	ldr	w2, [x22, 4]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1185
.L1192:
	ldr	x1, .LC181
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1185
.L1254:
	ldr	x1, .LC179
	mov	w0, 1
	ldr	w2, [x23, 4]
	ldr	w4, [x27, 3644]
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1185
	.size	VC1_Vfmw_ParseAdvHdr, .-VC1_Vfmw_ParseAdvHdr
	.align	3
.LC178:
	.xword	.LC177
	.align	3
.LC179:
	.xword	.LC118
	.align	3
.LC180:
	.xword	.LC120
	.align	3
.LC181:
	.xword	.LC122
	.align	3
.LC183:
	.xword	.LC182
	.align	3
.LC184:
	.xword	.L1196
	.align	3
.LC185:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC187:
	.xword	.LC186
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_Vfmw_ParseHeader
	.type	VC1_Vfmw_ParseHeader, %function
VC1_Vfmw_ParseHeader:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L1261
	cmp	w21, 32
	bhi	.L1262
	ldrsb	w0, [x19, 3104]
	cbz	w0, .L1263
	mov	w2, w21
	mov	x1, x20
	mov	x0, x19
	bl	VC1_Vfmw_ParseAdvHdr
.L1257:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1263:
	ldrb	w3, [x19]
	mov	x2, x20
	ldr	x0, [x19, 3136]
	mov	x1, x19
	orr	w3, w3, 3
	strb	w3, [x19]
	bl	VC1_Vfmw_ParseSMPPicHdr
	cmp	w0, 1
	bne	.L1257
	ldrb	w2, [x19]
	mov	w1, 20
	orr	w1, w2, w1
	strb	w1, [x19]
	b	.L1257
	.p2align 3
.L1261:
	ldr	x1, .LC189
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1262:
	ldr	x1, .LC190
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VC1_Vfmw_ParseHeader, .-VC1_Vfmw_ParseHeader
	.align	3
.LC189:
	.xword	.LC188
	.align	3
.LC190:
	.xword	.LC150
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_SetCodeInfo
	.type	VC1_SetCodeInfo, %function
VC1_SetCodeInfo:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	add	x19, x19, 12288
	mov	x21, x1
	bl	_mcount
	add	x2, x19, 2520
	add	x0, x2, 3144
	str	x0, [x19, 5656]
	ldrb	w1, [x2, 3106]
	cmp	w1, 8
	beq	.L1269
	strb	wzr, [x2, 12]
	strb	w1, [x2, 11]
.L1266:
	add	x20, x19, 2520
	ldr	w2, [x21, 28]
	ldrsb	w1, [x20, 3104]
	cbz	w1, .L1270
	ldr	x1, [x21]
	bl	BsInit
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1270:
	ldr	x1, [x21]
	bl	BsInit
	ldr	w1, [x19, 5632]
	add	x2, x20, 20480
	add	x3, x20, 3120
	add	x20, x20, 3184
	adds	w4, w1, 15
	add	w0, w1, 30
	csel	w0, w0, w4, mi
	asr	w0, w0, 4
	str	w0, [x2, 3640]
	ldr	w0, [x19, 5636]
	str	w0, [x2, 3660]
	str	w1, [x2, 3656]
	add	w1, w0, 30
	adds	w0, w0, 15
	csel	w0, w1, w0, mi
	asr	w0, w0, 4
	str	w0, [x2, 3644]
	ldp	x0, x1, [x3]
	stp	x0, x1, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1269:
	mov	w3, 1
	mov	w1, 6
	strb	w3, [x2, 12]
	strb	w1, [x2, 11]
	b	.L1266
	.size	VC1_SetCodeInfo, .-VC1_SetCodeInfo
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_ReceivePacket
	.type	VC1_ReceivePacket, %function
VC1_ReceivePacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x20, 53248
	add	x1, x0, 112
	cbz	x19, .L1279
	ldr	w2, [x19, 16]
	str	w2, [x1, 20]
	ldr	x2, [x19]
	str	x2, [x0, 112]
	ldr	w2, [x19, 20]
	str	w2, [x1, 28]
	ldrb	w2, [x19, 10]
	strb	w2, [x1, 16]
	ldr	w2, [x19, 24]
	str	w2, [x1, 36]
	ldrb	w2, [x19, 10]
	cmp	w2, 1
	beq	.L1274
	ldr	w2, [x19, 104]
	str	w2, [x1, 24]
	ldr	x2, [x19, 88]
	str	x2, [x1, 8]
	ldr	w2, [x19, 108]
	str	w2, [x1, 32]
	ldrb	w2, [x19, 98]
	strb	w2, [x1, 17]
	ldr	w2, [x19, 112]
	str	w2, [x1, 40]
	ldrb	w2, [x19, 98]
	cmp	w2, 1
	bne	.L1280
.L1275:
	mov	x0, x20
	bl	VC1_SetCodeInfo
	mov	w0, 1
.L1273:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1280:
	ldr	w0, [x0, 896]
	bl	VC1_ClearCurPacket
	ldrb	w2, [x19, 98]
	mov	w0, 1
	ldr	x1, .LC194
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1274:
	strb	wzr, [x1, 17]
	str	xzr, [x1, 8]
	str	wzr, [x1, 24]
	str	wzr, [x1, 32]
	str	wzr, [x1, 40]
	b	.L1275
	.p2align 3
.L1279:
	ldr	x1, .LC192
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1273
	.size	VC1_ReceivePacket, .-VC1_ReceivePacket
	.align	3
.LC192:
	.xword	.LC191
	.align	3
.LC194:
	.xword	.LC193
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1DEC_Decode
	.type	VC1DEC_Decode, %function
VC1DEC_Decode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x21, x1
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L1309
	cbz	x19, .L1310
	ldr	x3, .LC199
	add	x20, x19, 12288
	add	x22, x20, 2344
	mov	x1, x21
	mov	x2, 176
	mov	x0, x22
	ldr	x3, [x3, 104]
	blr	x3
	mov	x1, x22
	mov	x0, x19
	bl	VC1_ReceivePacket
	mov	w21, w0
	cbz	w0, .L1311
	ldr	x0, [x19]
	add	x22, x19, 53248
	ldr	w1, [x0, 912]
	cmp	w1, 1
	beq	.L1312
.L1286:
	ldrb	w0, [x20, 2520]
	strb	w0, [x22, 240]
.L1287:
	add	x20, x20, 2520
	add	x1, x19, 16384
	ldr	w2, [x22, 896]
	add	x1, x1, 1608
	mov	x0, x20
	bl	VC1_Vfmw_ParseHeader
	mov	w23, w0
	cbnz	w0, .L1288
	ldr	w0, [x22, 896]
	add	x1, x22, 112
	bl	VC1_ClearCurPacket
	ldr	x0, .LC202
	ldr	x4, [x0]
	cbz	x4, .L1290
	ldr	w0, [x22, 896]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	mov	w21, 0
	blr	x4
.L1283:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1288:
	mov	x0, x19
	bl	VC1_Vfmw_DecodeArbiter
	cbnz	w0, .L1313
.L1290:
	mov	w21, 0
.L1316:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1312:
	ldr	w0, [x0, 960]
	cmp	w0, 1
	bne	.L1286
	ldrb	w0, [x22, 240]
	strb	w0, [x20, 2520]
	b	.L1287
	.p2align 3
.L1313:
	mov	x0, x19
	bl	VC1_Vfmw_PrepareDecode
	mov	w21, w0
	cbnz	w0, .L1291
	ldr	x0, [x19]
	ldr	w1, [x0, 912]
	cmp	w1, 1
	beq	.L1314
.L1292:
	ldr	w1, [x22, 896]
	mov	x0, x20
	bl	VC1_ClearCurPic
.L1293:
	ldr	x0, .LC202
	ldr	x4, [x0]
	cbz	x4, .L1290
.L1307:
	ldr	w0, [x22, 896]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 113
	blr	x4
	b	.L1283
	.p2align 3
.L1311:
	add	x19, x19, 53248
	ldr	x1, .LC201
	ldr	w2, [x19, 104]
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1310:
	ldr	x1, .LC198
	mov	w0, 0
	mov	w21, 0
	bl	dprint_vfmw
	b	.L1283
	.p2align 3
.L1314:
	ldr	w0, [x0, 960]
	cmp	w0, 1
	bne	.L1292
	b	.L1293
	.p2align 3
.L1309:
	ldr	x1, .LC196
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1283
	.p2align 3
.L1291:
	mov	x0, x19
	bl	VC1_Vfmw_StartDecode
	mov	w21, w0
	cbz	w0, .L1315
	mov	w21, w23
	b	.L1283
	.p2align 3
.L1315:
	add	x19, x19, 36864
	ldr	w0, [x22, 896]
	mov	w2, 1
	ldr	w1, [x19, 2140]
	bl	FSP_ClearLogicFs
	ldr	x1, [x19, 2032]
	ldr	x0, .LC202
	strb	wzr, [x1]
	ldr	x1, [x19, 2032]
	strb	wzr, [x1, 1]
	ldr	x4, [x0]
	cbnz	x4, .L1307
	mov	w21, 0
	b	.L1316
	.size	VC1DEC_Decode, .-VC1DEC_Decode
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC198:
	.xword	.LC197
	.align	3
.LC199:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC201:
	.xword	.LC200
	.align	3
.LC202:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VC1_GetPacketState
	.type	VC1_GetPacketState, %function
VC1_GetPacketState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1321
	add	x19, x19, 12288
	mov	w0, 2
	ldrsb	w1, [x19, 2526]
	cmp	w1, 1
	csel	w0, wzr, w0, ne
.L1319:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1321:
	ldr	x3, .LC203
	mov	w2, 5981
	ldr	x1, .LC204
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1319
	.size	VC1_GetPacketState, .-VC1_GetPacketState
	.align	3
.LC203:
	.xword	.LC35
	.align	3
.LC204:
	.xword	.LC37
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.11588, %object
	.size	__func__.11588, 13
__func__.11588:
	.string	"Vc1SMPSeqHdr"
	.zero	3
.LC0:
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	1
	.word	2
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
.LC1:
	.word	3
	.word	1
	.word	2
	.word	0
	.word	4
	.zero	4
.LC2:
	.word	1
	.word	0
	.word	2
	.word	3
	.word	4
	.zero	4
.LC3:
	.word	1
	.word	1
	.word	2
	.word	1
	.word	3
	.word	1
	.word	2
	.zero	4
.LC4:
	.word	2
	.word	3
	.word	3
	.word	4
	.word	4
	.word	5
	.word	5
	.zero	4
.LC5:
	.word	3
	.word	4
	.word	1
	.word	5
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	1
	.word	3
	.word	5
	.word	7
.LC6:
	.word	5
	.word	5
	.word	6
	.word	6
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	8
	.word	8
	.word	8
	.word	8
.LC7:
	.word	256
	.word	128
	.word	85
	.word	64
	.word	51
	.word	43
	.word	37
	.word	32
	.type	__func__.11899, %object
	.size	__func__.11899, 17
__func__.11899:
	.string	"VC1_DecBfraction"
	.zero	7
	.type	aCount, %object
	.size	aCount, 128
aCount:
	.word	0
	.word	1
	.word	1
	.word	2
	.word	1
	.word	2
	.word	2
	.word	3
	.word	1
	.word	2
	.word	2
	.word	3
	.word	2
	.word	3
	.word	3
	.word	4
	.word	1
	.word	2
	.word	2
	.word	3
	.word	2
	.word	3
	.word	3
	.word	4
	.word	2
	.word	3
	.word	3
	.word	4
	.word	3
	.word	4
	.word	4
	.word	5
	.type	a2On4Off, %object
	.size	a2On4Off, 60
a2On4Off:
	.word	3
	.word	5
	.word	6
	.word	9
	.word	10
	.word	12
	.word	17
	.word	18
	.word	20
	.word	24
	.word	33
	.word	34
	.word	36
	.word	40
	.word	48
	.zero	4
.LC8:
	.word	1
	.word	2
	.word	2
	.word	2
	.word	0
	.word	1
	.word	0
	.word	1
.LC9:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	16
	.word	17
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	25
	.word	27
	.word	29
	.word	31
	.align	3
.LANCHOR1 = . + 0
	.type	FldPTypeTab, %object
	.size	FldPTypeTab, 64
FldPTypeTab:
	.word	0
	.word	0
	.word	0
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	4
	.word	4
	.word	2
	.word	4
	.word	4
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC12:
	ASCII(.string	"pCtx or pstExtraData is NULL! \n" )
.LC15:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err! \n" )
	.zero	4
.LC17:
	ASCII(.string	"VC1 INIT!!!\n" )
	.zero	3
.LC19:
	ASCII(.string	"pBitBuf or pVc1Info is NULL! \n" )
	.zero	1
.LC21:
	ASCII(.string	"picture width out of range" )
	.zero	5
.LC24:
	ASCII(.string	"%s: %s\n" )
.LC26:
	ASCII(.string	"picture height out of range" )
	.zero	4
.LC28:
	ASCII(.string	"Vc1SMPSeqHdr Err, BS is wrong" )
	.zero	2
.LC30:
	ASCII(.string	"Vc1SMPSeqHdr Err, BS is wrong\n" )
	.zero	1
.LC33:
	ASCII(.string	"pCtx is NULL! \n" )
.LC35:
	ASCII(.string	"pCtx is NULL!" )
	.zero	2
.LC37:
	ASCII(.string	"vc1.c,L%d: %s\n" )
	.zero	1
.LC41:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC43:
	ASCII(.string	"vc1 actual frame size(%dx%d) exeed max config(%dx%d)\n" )
	.zero	2
.LC46:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC48:
	ASCII(.string	"ERROR: FSP_ConfigInstance fail!\n" )
	.zero	7
.LC50:
	ASCII(.string	"line: %d, pImage is NULL!\n" )
	.zero	5
.LC56:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC58:
	ASCII(.string	"VC1_Vfmw_GetImageBuffer get imgbuf err, clear all ref!\n" )
.LC60:
	ASCII(.string	"VC1_Vfmw_GetImageBuffer get_flag!=1, FSP_ClearLogicFs.\n" )
.LC63:
	ASCII(.string	"pCodecInf is NULL! \n" )
	.zero	3
.LC67:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo VC1_ArrangeVahbMem err!\n" )
.LC69:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_GetImageBuffer err!\n" )
	.zero	3
.LC71:
	ASCII(.string	"dec_pts: %lld Usertag = %lld\n" )
	.zero	2
.LC74:
	ASCII(.string	"---------- unref %d\n" )
	.zero	3
.LC76:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo B pic pCodecInf->RefNum < 2 err!\n" )
	.zero	7
.LC78:
	ASCII(.string	"line: %d (pCur,pFwd,pBwd)(%p,%p,%p)\n" )
	.zero	3
.LC80:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo imgbuf = NULL err!\n" )
	.zero	5
.LC82:
	ASCII(.string	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p)\n" )
	.zero	6
.LC84:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_BuildRefList err!\n" )
	.zero	5
.LC86:
	ASCII(.string	"pVC1_CTX_S is NULL!" )
	.zero	4
.LC89:
	ASCII(.string	"VC1_Vfmw_GetStreamInfo error! Release all packets!\n" )
	.zero	4
.LC102:
	ASCII(.string	"%s:%d Code(%d) is invalid\n" )
	.zero	5
.LC104:
	ASCII(.string	"%s:%d Denominator(%d) is invalid\n" )
	.zero	6
.LC118:
	ASCII(.string	"SLICE_ADDR = %d,SlcEndMbn = %d, MbHeight = %d\n" )
	.zero	1
.LC120:
	ASCII(.string	"SLICE_ADDR = %d,SlcEndMbn = %d, totalMbMin1 = %d\n" )
	.zero	6
.LC122:
	ASCII(.string	"VC1_RecordSlcStream stream len <= 0\n" )
	.zero	3
.LC124:
	ASCII(.string	"pCodecInf is NULL!" )
	.zero	5
.LC128:
	ASCII(.string	"Check Pos 2: %d\n" )
	.zero	7
.LC130:
	ASCII(.string	"Check Pos 3: %d\n" )
	.zero	7
.LC133:
	ASCII(.string	"\n======PicNum  :%6d=========\n" )
	.zero	2
.LC135:
	ASCII(.string	"INTERPFRM  :%#x\n" )
	.zero	7
.LC138:
	ASCII(.string	"VC1_Vfmw_ParseMPBPicHdr err!\n" )
	.zero	2
.LC140:
	ASCII(.string	"VC1_Vfmw_ParseSMPIPicHdr err!\n" )
	.zero	1
.LC142:
	ASCII(.string	"After VC1_Vfmw_ParseSMPPicHdr BS Len <= 0 err!\n" )
.LC148:
	ASCII(.string	"pCodeInfo  is NULL! \n" )
	.zero	2
.LC150:
	ASCII(.string	"ChanID is out of range! \n" )
	.zero	6
.LC154:
	ASCII(.string	"pImg is null, pCurImg %p pBwdImg %p pFwdImg %p\n" )
.LC156:
	ASCII(.string	"line: %d, pToQueImg is Null!\n" )
	.zero	2
.LC158:
	ASCII(.string	"insert buf %d ref %d\n" )
	.zero	2
.LC160:
	ASCII(.string	"err(%d) > out_thr(%d)\n" )
	.zero	1
.LC164:
	ASCII(.string	"----------------- VC1 Imode -> %d ------------------\n" )
	.zero	2
.LC167:
	ASCII(.string	"NOTE: Drop non-I\n" )
	.zero	6
.LC169:
	ASCII(.string	"NOTE: Drop B\n" )
	.zero	2
.LC177:
	ASCII(.string	" pCodecInf->SlcNum = %d >= 256 \n" )
	.zero	7
.LC182:
	ASCII(.string	"line %d, Code = VC1_SCSLC failed!\n" )
	.zero	5
.LC186:
	ASCII(.string	"line %d, Code = VC1_SCFRM failed!\n" )
	.zero	5
.LC188:
	ASCII(.string	"pCodecInf or pSyntax is NULL! \n" )
.LC191:
	ASCII(.string	"bitsream para error -----\n" )
	.zero	5
.LC193:
	ASCII(.string	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\n" )
.LC195:
	ASCII(.string	"ERROR: p_Packet is Null pointer!\n" )
	.zero	6
.LC197:
	ASCII(.string	"ERROR: pVC1_CTX_S is Null pointer!\n" )
	.zero	4
.LC200:
	ASCII(.string	"ERROR: frm %d, Invalid packet pointer!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
