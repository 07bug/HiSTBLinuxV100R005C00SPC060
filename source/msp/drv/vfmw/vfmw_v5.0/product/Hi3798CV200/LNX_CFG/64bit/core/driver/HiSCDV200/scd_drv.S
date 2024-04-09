#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"scd_drv.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	SCDDRV_SetStateIdle.part.0, %function
SCDDRV_SetStateIdle.part.0:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x3, .LC2
	lsl	x1, x0, 6
	ldr	x2, .LC3
	add	x0, x1, x0, lsl 3
	add	x1, x3, x0
	mov	w0, 1
	ldr	x2, [x2, 256]
	str	wzr, [x1, 56]
	blr	x2
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SetStateIdle.part.0, .-SCDDRV_SetStateIdle.part.0
	.align	3
.LC2:
	.xword	.LANCHOR0
	.align	3
.LC3:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	GetFreeSegBufSize.part.6, %function
GetFreeSegBufSize.part.6:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x0, x19, 180224
	str	wzr, [x20]
	ldp	w2, w3, [x0, 32]
	cmp	w3, w2
	sub	w2, w2, #1
	bls	.L3
	ldr	w0, [x0, 28]
	add	w2, w0, w2
	sub	w2, w2, w3
.L4:
	cmp	w2, w0
	bgt	.L2
	str	w2, [x20]
.L2:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L3:
	bcs	.L5
	sub	w2, w2, w3
	ldr	w0, [x0, 28]
	b	.L4
	.p2align 3
.L5:
	ldr	w0, [x0, 28]
	sub	w2, w0, #1
	b	.L4
	.size	GetFreeSegBufSize.part.6, .-GetFreeSegBufSize.part.6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteCabacTabDsp
	.type	WriteCabacTabDsp, %function
WriteCabacTabDsp:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	MEM_Phy2Vir
	cbz	x0, .L11
	ldr	x3, .LC6
	mov	x2, 5120
	ldr	x1, .LC7
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L11:
	ldr	x1, .LC5
	mov	w2, 56
	mov	w0, 22
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	WriteCabacTabDsp, .-WriteCabacTabDsp
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC6:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC7:
	.xword	g_CabacMN
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_LoadDspCode
	.type	SCDDRV_LoadDspCode, %function
SCDDRV_LoadDspCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cbz	w19, .L27
.L12:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L27:
	ldr	x20, .LC8
	ldr	w0, [x20, 72]
	bl	MEM_Phy2Vir
	cbz	x0, .L28
	cmp	w22, 1
	beq	.L29
	cmp	w22, 2
	beq	.L30
	ldr	x1, .LC15
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L30:
	ldr	x21, .LC11
	mov	x2, 17920
	ldr	x1, .LC13
	ldr	x3, [x21, 104]
	add	x1, x1, 512
	blr	x3
	ldr	w0, [x20, 80]
	mov	w1, 0
	bl	MEM_WritePhyWord
.L17:
	ldr	w0, [x20, 80]
	mov	w1, 4480
	mov	w19, 0
	add	w0, w0, 264
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 80]
	ldr	w1, [x20, 72]
	add	w0, w0, 268
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 80]
	mov	w1, 0
	add	w0, w0, 256
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 80]
	mov	w1, 5
	add	w0, w0, 256
	bl	MEM_WritePhyWord
	b	.L20
	.p2align 3
.L31:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L21
.L20:
	ldr	x1, [x21, 232]
	mov	x0, 30
	blr	x1
	ldr	w0, [x20, 80]
	add	w0, w0, 260
	bl	MEM_ReadPhyWord
	tbz	x0, 0, .L31
	cmp	w19, 999
	bhi	.L21
	ldr	x2, .LC16
	mov	w0, 0
	ldr	x1, .LC20
	bl	dprint_vfmw
.L23:
	cmp	w22, 1
	beq	.L32
	cmp	w22, 2
	bne	.L12
	ldr	x0, .LC21
	mov	w1, 1
	str	w1, [x0]
	b	.L12
	.p2align 3
.L21:
	ldr	x2, .LC16
	mov	w0, 0
	ldr	x1, .LC18
	bl	dprint_vfmw
	b	.L23
	.p2align 3
.L29:
	ldr	x21, .LC11
	mov	x2, 17920
	ldr	x1, .LC12
	ldr	x3, [x21, 104]
	blr	x3
	ldr	w0, [x20, 80]
	mov	w1, w22
	bl	MEM_WritePhyWord
	b	.L17
	.p2align 3
.L32:
	ldr	x0, .LC21
	mov	w1, 2
	str	w1, [x0]
	b	.L12
.L28:
	ldr	x1, .LC10
	ldr	w2, [x20, 72]
	bl	dprint_vfmw
	b	.L12
	.size	SCDDRV_LoadDspCode, .-SCDDRV_LoadDspCode
	.align	3
.LC8:
	.xword	.LANCHOR0
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC11:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC12:
	.xword	.LANCHOR1
	.align	3
.LC13:
	.xword	.LANCHOR2
	.align	3
.LC15:
	.xword	.LC14
	.align	3
.LC16:
	.xword	.LANCHOR3
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC21:
	.xword	g_DspDrvState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetInstIDByRawArray
	.type	GetInstIDByRawArray, %function
GetInstIDByRawArray:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC24
	mov	x0, 0
	b	.L36
	.p2align 3
.L34:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L42
.L36:
	add	x1, x3, x0, lsl 4
	ldr	x1, [x1, 88]
	add	x2, x1, 88
	cmp	x19, x2
	cbz	x1, .L34
	bne	.L34
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L42:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetInstIDByRawArray, .-GetInstIDByRawArray
	.align	3
.LC24:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SetStateIdle
	.type	SCDDRV_SetStateIdle, %function
SCDDRV_SetStateIdle:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L43
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
.L43:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SetStateIdle, .-SCDDRV_SetStateIdle
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SetStateWork
	.type	SCDDRV_SetStateWork, %function
SCDDRV_SetStateWork:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L45
	ldr	x0, .LC25
	mov	w1, 1
	str	w1, [x0, 56]
.L45:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SetStateWork, .-SCDDRV_SetStateWork
	.align	3
.LC25:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetSCD
	.type	ResetSCD, %function
ResetSCD:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L54
	ldr	x20, .LC26
	mov	w1, 3
	ldr	w0, [x20, 80]
	add	w0, w0, 2176
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 80]
	add	w0, w0, 2076
	bl	MEM_ReadPhyWord
	ldr	x21, .LC27
	mov	w22, w0
	ldr	x2, [x21]
	ldr	w19, [x2, 120]
	tbz	x19, 0, .L57
	orr	w19, w19, 32
	mov	w0, 0
	mov	w3, 10000
	str	w19, [x2, 120]
	b	.L51
	.p2align 3
.L58:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L52
.L51:
	ldr	w1, [x2, 372]
	tbz	x1, 1, .L58
	mov	w1, 9999
	cmp	w0, w1
	bhi	.L52
.L53:
	ldr	w0, [x20, 80]
	and	w1, w22, 1
	and	w19, w19, -33
	str	w19, [x2, 120]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldr	w0, [x20, 80]
	mov	w1, 2
	add	w0, w0, 2176
	bl	MEM_WritePhyWord
	mov	w0, 1
.L56:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L52:
	ldr	x1, .LC31
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x2, [x21]
	b	.L53
.L57:
	ldr	x1, .LC29
	mov	w2, 0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, 1
	b	.L56
.L54:
	mov	w0, -2
	b	.L56
	.size	ResetSCD, .-ResetSCD
	.align	3
.LC26:
	.xword	.LANCHOR0
	.align	3
.LC27:
	.xword	g_pstRegCrg
	.align	3
.LC29:
	.xword	.LC28
	.align	3
.LC31:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ResetSCD
	.type	SCDDRV_ResetSCD, %function
SCDDRV_ResetSCD:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC32
	ldr	w0, [x0, 52]
	cmp	w19, w0
	beq	.L63
.L59:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L63:
	ldr	x0, .LC33
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L61
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Reset_Module
.L62:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	b	.L59
	.p2align 3
.L61:
	mov	w0, 0
	bl	ResetSCD
	b	.L62
	.size	SCDDRV_ResetSCD, .-SCDDRV_ResetSCD
	.align	3
.LC32:
	.xword	.LANCHOR0
	.align	3
.LC33:
	.xword	g_HalDisable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsRawArrayFull
	.type	SCDDRV_IsRawArrayFull, %function
SCDDRV_IsRawArrayFull:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x1, x19, 98304
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldp	w0, w2, [x1, 4]
	add	w0, w0, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w0, w0, w1
	cmp	w0, w2
	cset	w0, eq
	ret
	.size	SCDDRV_IsRawArrayFull, .-SCDDRV_IsRawArrayFull
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_InsertRawPacket
	.type	SCDDRV_InsertRawPacket, %function
SCDDRV_InsertRawPacket:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC34
	add	x19, x0, x19, sxtw 4
	ldr	w0, [x20, 4]
	cmp	w0, wzr
	ldr	x0, [x19, 88]
	ccmp	x0, xzr, 4, ne
	beq	.L67
	add	x0, x0, 88
	add	x19, x0, 98304
	ldp	w3, w1, [x19, 4]
	add	w2, w3, 1
	asr	w4, w2, 31
	lsr	w4, w4, 22
	add	w2, w2, w4
	and	w2, w2, 1023
	sub	w2, w2, w4
	cmp	w2, w1
	beq	.L68
	sxtw	x3, w3
	ldr	x5, .LC35
	lsl	x4, x3, 2
	mov	x2, 96
	sub	x3, x4, x3
	mov	x1, x20
	ldr	x4, [x5, 104]
	add	x0, x0, x3, lsl 5
	blr	x4
	ldr	w1, [x19, 4]
	mov	w0, 0
	add	w1, w1, 1
	asr	w2, w1, 31
	lsr	w2, w2, 22
	add	w1, w1, w2
	and	w1, w1, 1023
	sub	w1, w1, w2
	str	w1, [x19, 4]
.L66:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L68:
	mov	w0, -4
	b	.L66
.L67:
	mov	w0, -1
	b	.L66
	.size	SCDDRV_InsertRawPacket, .-SCDDRV_InsertRawPacket
	.align	3
.LC34:
	.xword	.LANCHOR0
	.align	3
.LC35:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawState
	.type	GetRawState, %function
GetRawState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L72
	ldr	x0, .LC36
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	cbz	x0, .L72
	add	x2, x0, 88
	mov	w0, -4
	add	x2, x2, 98304
	ldp	w1, w3, [x2, 4]
	add	w1, w1, 1
	asr	w2, w1, 31
	lsr	w2, w2, 22
	add	w1, w1, w2
	and	w1, w1, 1023
	sub	w1, w1, w2
	cmp	w1, w3
	csel	w0, w0, wzr, eq
.L70:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L72:
	mov	w0, -4
	b	.L70
	.size	GetRawState, .-GetRawState
	.align	3
.LC36:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ShowRawPacket
	.type	ShowRawPacket, %function
ShowRawPacket:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 98304
	mov	x21, x1
	bl	_mcount
	ldr	w0, [x19, 16]
	cmp	w0, 1023
	bhi	.L77
	ldr	w1, [x19, 4]
	cmp	w0, w1
	beq	.L77
	sxtw	x0, w0
	ldr	x1, .LC37
	lsl	x3, x0, 2
	mov	x2, 96
	sub	x3, x3, x0
	mov	x0, x21
	ldr	x4, [x1, 104]
	add	x1, x20, x3, lsl 5
	blr	x4
	ldr	w1, [x19, 16]
	mov	w0, 0
	add	w1, w1, 1
	asr	w2, w1, 31
	lsr	w2, w2, 22
	add	w1, w1, w2
	and	w1, w1, 1023
	sub	w1, w1, w2
	str	w1, [x19, 16]
.L75:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L77:
	mov	w0, -3
	b	.L75
	.size	ShowRawPacket, .-ShowRawPacket
	.align	3
.LC37:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetFirstOffset
	.type	GetFirstOffset, %function
GetFirstOffset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L80
	add	x0, x19, 98304
	ldp	w2, w1, [x0]
	cmp	w2, w1
	beq	.L81
	ldr	w1, [x0, 12]
	mov	w0, 0
	str	w1, [x20]
.L79:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L80:
	mov	w0, -1
	b	.L79
	.p2align 3
.L81:
	mov	w0, -3
	b	.L79
	.size	GetFirstOffset, .-GetFirstOffset
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetFirstRawPacket
	.type	GetFirstRawPacket, %function
GetFirstRawPacket:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cbz	x23, .L87
	add	x20, x23, 98304
	ldp	w1, w0, [x20]
	cmp	w1, w0
	beq	.L86
	ldr	w24, [x20, 12]
	mov	w22, w24
	sxtw	x21, w24
.L84:
	cmp	w1, 1023
	str	w1, [x20, 16]
	bhi	.L85
	ldr	w0, [x20, 4]
	cmp	w0, w1
	beq	.L85
	sxtw	x1, w1
	ldr	x3, .LC38
	lsl	x0, x1, 2
	mov	x2, 96
	sub	x1, x0, x1
	mov	x0, x19
	ldr	x3, [x3, 104]
	add	x1, x23, x1, lsl 5
	blr	x3
	ldr	w0, [x20, 16]
	add	w0, w0, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w0, w0, w1
	str	w0, [x20, 16]
.L85:
	ldr	w2, [x19, 4]
	ldr	w0, [x19, 12]
	ldr	x1, [x19, 40]
	add	w22, w2, w22
	sub	w0, w0, w24
	str	w22, [x19, 4]
	str	w0, [x19, 12]
	add	x21, x1, x21
	str	x21, [x19, 40]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L86:
	mov	x21, 0
	mov	w22, 0
	mov	w24, 0
	b	.L84
	.p2align 3
.L87:
	mov	x0, 98304
	mov	x21, 0
	mov	w22, 0
	mov	w24, 0
	mov	x20, x0
	ldr	w1, [x0]
	b	.L84
	.size	GetFirstRawPacket, .-GetFirstRawPacket
	.align	3
.LC38:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetFirstOffset
	.type	SetFirstOffset, %function
SetFirstOffset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L92
	add	x3, x19, 98304
	ldp	w0, w2, [x3]
	cmp	w0, w2
	beq	.L91
	sxtw	x0, w0
	ldr	w4, [x3, 12]
	lsl	x2, x0, 2
	sub	x0, x2, x0
	add	w1, w20, w4
	add	x0, x19, x0, lsl 5
	ldr	w0, [x0, 12]
	cmp	w1, w0
	bge	.L92
	mov	w0, 0
	str	w1, [x3, 12]
.L89:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L92:
	mov	w0, -1
	b	.L89
	.p2align 3
.L91:
	mov	w0, -3
	b	.L89
	.size	SetFirstOffset, .-SetFirstOffset
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DeleteRawPacket
	.type	DeleteRawPacket, %function
DeleteRawPacket:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x26, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	x26, xzr
	ccmp	w20, wzr, 4, ne
	beq	.L109
	ldr	x27, .LC39
	mov	x0, 0
	b	.L97
	.p2align 3
.L95:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L98
.L97:
	add	x1, x27, x0, lsl 4
	mov	w3, w0
	ldr	x1, [x1, 88]
	add	x2, x1, 88
	cmp	x26, x2
	cbz	x1, .L95
	bne	.L95
	cmp	w0, 31
	bhi	.L98
	add	x23, x26, 98304
	ldp	w0, w2, [x23]
	cmp	w0, w2
	bgt	.L120
.L117:
	sub	w2, w2, w0
	cmp	w2, w20
	bcc	.L121
	mov	w24, w0
	cbz	w20, .L103
	ldr	x21, .LC44
	add	x27, x27, 88
	ldr	x22, .LC46
	mov	w25, 0
	add	x21, x21, 24
	add	x27, x27, x3, sxtw 4
	.p2align 2
.L104:
	uxtw	x19, w24
	mov	x2, x21
	lsl	x0, x19, 2
	mov	x1, x22
	sub	x19, x0, x19
	mov	w0, 26
	add	w25, w25, 1
	add	w24, w24, 1
	add	x19, x26, x19, lsl 5
	and	w24, w24, 1023
	ldr	w3, [x19, 4]
	ldr	w4, [x19, 12]
	bl	dprint_vfmw
	ldr	x1, [x27]
	ldr	w2, [x19, 12]
	add	x1, x1, 98304
	ldr	w0, [x1, 108]
	subs	w0, w0, w2
	csel	w0, w0, wzr, pl
	cmp	w20, w25
	str	w0, [x1, 108]
	bne	.L104
	ldr	w0, [x23]
	add	w20, w20, w0
	str	w20, [x23]
	cmp	w20, 1023
	ble	.L107
	sub	w20, w20, #1024
	str	w20, [x23]
.L107:
	str	wzr, [x23, 12]
.L118:
	mov	w0, 0
.L115:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L120:
	add	w2, w2, 1024
	b	.L117
.L103:
	cmp	w0, 1023
	str	w0, [x23]
	ble	.L118
	sub	w0, w0, #1024
	str	w0, [x23]
	b	.L118
	.p2align 3
.L109:
	mov	w0, -1
	b	.L115
.L121:
	ldr	x1, .LC43
	mov	w3, w20
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, -1
	b	.L115
	.p2align 3
.L98:
	ldr	x1, .LC41
	mov	w2, 435
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L115
	.size	DeleteRawPacket, .-DeleteRawPacket
	.align	3
.LC39:
	.xword	.LANCHOR0
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC43:
	.xword	.LC42
	.align	3
.LC44:
	.xword	.LANCHOR3
	.align	3
.LC46:
	.xword	.LC45
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawNumOffset
	.type	GetRawNumOffset, %function
GetRawNumOffset:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	mov	x22, x3
	mov	x23, x4
	bl	_mcount
	cmp	x20, xzr
	ccmp	w19, wzr, 1, ne
	blt	.L130
	cmp	x21, xzr
	ccmp	x22, xzr, 4, ne
	ccmp	x23, xzr, 4, ne
	beq	.L130
	add	x2, x20, 98304
	ldr	w1, [x2]
	ldr	w8, [x2, 12]
	sxtw	x3, w1
	lsl	x0, x3, 2
	sub	x0, x0, x3
	add	x0, x20, x0, lsl 5
	ldr	w0, [x0, 12]
	sub	w8, w0, w8
	cbz	x20, .L131
	ldr	w10, [x2, 4]
	sub	w10, w10, w1
	add	w0, w10, 1024
	cmp	w10, wzr
	csel	w10, w0, w10, lt
.L124:
	add	w10, w1, w10
	cmp	w19, w8
	ccmp	w10, w1, 0, ge
	mov	w0, w1
	bls	.L132
	mov	w6, w1
	b	.L126
	.p2align 3
.L133:
	mov	w8, w5
.L126:
	add	w6, w6, 1
	asr	w0, w6, 31
	lsr	w5, w0, 22
	add	w0, w6, w5
	and	w0, w0, 1023
	sub	w0, w0, w5
	sxtw	x7, w0
	lsl	x5, x7, 2
	sub	x5, x5, x7
	add	x5, x20, x5, lsl 5
	ldr	w5, [x5, 12]
	add	w5, w8, w5
	cmp	w19, w5
	cset	w9, lt
	cmp	w10, w6
	cset	w7, ls
	orr	w7, w9, w7
	cbz	w7, .L133
	cmp	w1, w6
	beq	.L125
	sub	w8, w19, w8
	str	w8, [x22]
.L128:
	str	w0, [x23]
	mov	w0, 0
	ldr	w1, [x2]
	sub	w6, w6, w1
	str	w6, [x21]
.L123:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L132:
	mov	w6, w1
	.p2align 2
.L125:
	str	w19, [x22]
	b	.L128
	.p2align 3
.L131:
	mov	w10, 0
	b	.L124
.L130:
	mov	w0, -1
	b	.L123
	.size	GetRawNumOffset, .-GetRawNumOffset
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DeleteRawLen
	.type	DeleteRawLen, %function
DeleteRawLen:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cmp	x19, xzr
	ccmp	w22, wzr, 1, ne
	blt	.L137
	stp	wzr, wzr, [x29, 52]
	cbz	x19, .L137
	add	x20, x19, 98304
	ldr	w1, [x20, 12]
	ldr	w0, [x20, 20]
	sub	w0, w0, w1
	asr	w21, w0, 31
	cbnz	w21, .L143
	cmp	w22, w0
	bgt	.L137
	add	x4, x29, 60
	add	x3, x29, 56
	add	x2, x29, 52
	mov	w1, w22
	mov	x0, x19
	bl	GetRawNumOffset
	ldp	w5, w4, [x29, 52]
	ldr	w1, [x20]
	mov	w3, w5
	add	w1, w5, w1
	asr	w0, w1, 31
	lsr	w0, w0, 22
	add	w1, w1, w0
	and	w1, w1, 1023
	sub	w0, w1, w0
	str	w0, [x29, 60]
	ldr	x1, .LC50
	sxtw	x6, w0
	lsl	x2, x6, 2
	sub	x0, x2, x6
	mov	w2, 601
	add	x0, x19, x0, lsl 5
	ldrb	w7, [x0, 2]
	ldr	w6, [x0, 12]
	mov	w0, 26
	bl	dprint_vfmw
	ldrsw	x1, [x29, 60]
	lsl	x0, x1, 2
	sub	x0, x0, x1
	add	x0, x19, x0, lsl 5
	ldrb	w1, [x0, 2]
	cbnz	w1, .L138
	ldr	w1, [x29, 52]
	mov	x0, x19
	bl	DeleteRawPacket
	ldp	w0, w1, [x20]
	cmp	w0, w1
	beq	.L148
.L146:
	sxtw	x0, w0
	ldr	w2, [x20, 12]
	lsl	x1, x0, 2
	ldr	w3, [x29, 56]
	sub	x0, x1, x0
	add	w1, w3, w2
	add	x19, x19, x0, lsl 5
	ldr	w0, [x19, 12]
	cmp	w1, w0
	blt	.L149
.L137:
	mov	w21, -1
.L143:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L149:
	str	w1, [x20, 12]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L138:
	ldr	w5, [x0, 12]
	mov	w2, 606
	ldr	x1, .LC52
	mov	w0, 26
	ldp	w3, w4, [x29, 52]
	bl	dprint_vfmw
	ldr	w1, [x29, 52]
	mov	x0, x19
	add	w1, w1, 1
	stp	w1, wzr, [x29, 52]
	bl	DeleteRawPacket
	ldp	w0, w1, [x20]
	cmp	w0, w1
	bne	.L146
.L148:
	mov	w21, -3
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	DeleteRawLen, .-DeleteRawLen
	.align	3
.LC50:
	.xword	.LC49
	.align	3
.LC52:
	.xword	.LC51
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DeleteLastSendRaw
	.type	DeleteLastSendRaw, %function
DeleteLastSendRaw:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L150
	ldr	x0, .LC53
	ubfiz	x19, x19, 4, 32
	add	x0, x0, 88
	ldr	x0, [x0, x19]
	cbz	x0, .L153
	add	x19, x0, 278528
	ldr	w1, [x19, 168]
	cmp	w1, wzr
	ble	.L150
	add	x0, x0, 88
	bl	DeleteRawPacket
	str	wzr, [x19, 168]
.L150:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L153:
	ldr	x1, .LC55
	mov	w2, 626
	bl	dprint_vfmw
	b	.L150
	.size	DeleteLastSendRaw, .-DeleteLastSendRaw
	.align	3
.LC53:
	.xword	.LANCHOR0
	.align	3
.LC55:
	.xword	.LC54
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawStreamSize
	.type	GetRawStreamSize, %function
GetRawStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L156
	add	x19, x19, 98304
	ldr	w2, [x19, 20]
	str	w2, [x20]
	ldr	w0, [x19, 12]
	sub	w0, w2, w0
	str	w0, [x20]
	asr	w0, w0, 31
.L155:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L156:
	mov	w0, -1
	b	.L155
	.size	GetRawStreamSize, .-GetRawStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawStreamNum
	.type	GetRawStreamNum, %function
GetRawStreamNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L160
	add	x19, x19, 98304
	ldp	w1, w0, [x19]
	subs	w0, w0, w1
	bmi	.L159
	str	w0, [x20]
	mov	w0, 0
.L158:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L159:
	add	w2, w0, 1024
	str	w2, [x20]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L160:
	mov	w0, -1
	b	.L158
	.size	GetRawStreamNum, .-GetRawStreamNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ConfigStreamSegArray
	.type	ConfigStreamSegArray, %function
ConfigStreamSegArray:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	mov	x22, x2
	mov	w21, w3
	bl	_mcount
	cbz	x19, .L164
	cmp	w20, wzr
	mov	w0, 262143
	ccmp	x22, xzr, 4, ne
	ccmp	w21, w0, 0, ne
	bls	.L164
	ldr	x3, .LC57
	mov	x2, 49208
	mov	w1, 0
	movk	x2, 0x2, lsl 16
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x19, 180224
	mov	w0, 0
	str	w20, [x1, 24]
	str	x22, [x19]
	stp	w21, w20, [x1, 28]
	str	w20, [x1, 36]
.L162:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L164:
	mov	w0, -1
	b	.L162
	.size	ConfigStreamSegArray, .-ConfigStreamSegArray
	.align	3
.LC57:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetStreamSegArray
	.type	ResetStreamSegArray, %function
ResetStreamSegArray:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L165
	ldr	x3, .LC58
	mov	x2, 49152
	mov	w1, 0
	movk	x2, 0x2, lsl 16
	add	x0, x19, 8
	ldr	x3, [x3, 96]
	blr	x3
	add	x0, x19, 180224
	ldr	w1, [x0, 24]
	stp	wzr, wzr, [x0, 8]
	str	wzr, [x0, 16]
	stp	w1, w1, [x0, 32]
.L165:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ResetStreamSegArray, .-ResetStreamSegArray
	.align	3
.LC58:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSegBufFreeSize
	.type	GetSegBufFreeSize, %function
GetSegBufFreeSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L174
	add	x1, x19, 180224
	ldp	w0, w2, [x1, 32]
	cmp	w2, w0
	sub	w0, w0, #1
	bhi	.L175
	sub	w0, w0, w2
	bcc	.L171
	ldr	w0, [x1, 28]
	sub	w0, w0, #1
.L171:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L175:
	ldr	w1, [x1, 28]
	ldr	x19, [sp, 16]
	add	w0, w0, w1
	sub	w0, w0, w2
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L174:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetSegBufFreeSize, .-GetSegBufFreeSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckData
	.type	CheckData, %function
CheckData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	uxtb	w20, w1
	bl	_mcount
	cbz	x19, .L176
	and	w0, w20, 31
	sub	w1, w0, #30
	sub	w2, w0, #1
	uxtb	w1, w1
	cmp	w1, 1
	ccmp	w0, 19, 4, hi
	ccmp	w2, 12, 0, ne
	bhi	.L178
	add	x1, x19, 311296
	ldr	w0, [x1, 1568]
	add	w0, w0, 1
	str	w0, [x1, 1568]
.L178:
	sub	w2, w20, #1
	add	w0, w20, 79
	uxtb	w2, w2
	uxtb	w0, w0
	cmp	w2, 183
	ccmp	w0, 4, 0, ls
	bhi	.L188
.L179:
	add	x19, x19, 311296
	ldr	w0, [x19, 1572]
	add	w0, w0, 1
	str	w0, [x19, 1572]
.L176:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L188:
	add	w20, w20, 73
	uxtb	w20, w20
	cmp	w20, 3
	bls	.L179
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CheckData, .-CheckData
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckStartCodeCnt
	.type	CheckStartCodeCnt, %function
CheckStartCodeCnt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	uxtb	w20, w1
	bl	_mcount
	cbz	x19, .L189
	add	x0, x19, 311296
	ldr	w1, [x0, 1576]
	cmp	w1, 2
	ble	.L189
	and	w20, w20, 31
	cbz	w20, .L189
	ldr	w2, [x0, 1584]
	ldr	w1, [x0, 1588]
	sub	w3, w1, w2
	cmp	w3, 1
	beq	.L203
.L191:
	cmp	w1, w2
	beq	.L204
.L189:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L204:
	ldr	w2, [x0, 1580]
	cmp	w1, w2
	bne	.L189
.L192:
	cmp	w1, 20
	ccmp	w1, 1, 4, ne
	beq	.L189
	ldr	w1, [x0, 1568]
	cmp	w1, wzr
	ble	.L193
	sub	w1, w1, #1
	str	w1, [x0, 1568]
.L193:
	ldr	w1, [x0, 1572]
	add	w1, w1, 1
	str	w1, [x0, 1572]
	b	.L189
	.p2align 3
.L203:
	ldr	w3, [x0, 1580]
	sub	w3, w2, w3
	cmp	w3, 1
	bne	.L191
	b	.L192
	.size	CheckStartCodeCnt, .-CheckStartCodeCnt
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	CheckStream.part.3, %function
CheckStream.part.3:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	ldr	x0, .LC59
	ldr	x19, [x0, w21, sxtw 3]
	cbz	x19, .L205
	ldr	w0, [x19, 632]
	cmp	w0, wzr
	ccmp	w0, 3, 4, ne
	bne	.L205
	add	x20, x19, 311296
	ldr	w0, [x20, 1576]
	cmp	w0, 199
	bgt	.L205
	ldrb	w1, [x22]
	cbz	w1, .L223
.L213:
	mov	w3, 0
	mov	w22, 0
.L209:
	add	x4, x20, 1536
	ldr	w2, [x20, 1584]
	ldr	w1, [x20, 1588]
	add	w0, w0, 1
	stp	w1, w3, [x4, 48]
	stp	w0, w2, [x4, 40]
	mov	w1, w22
	mov	x0, x19
	bl	CheckData
	mov	x0, x19
	mov	w1, w22
	bl	CheckStartCodeCnt
	ldr	w0, [x20, 1576]
	cmp	w0, 199
	ble	.L205
	ldr	w1, [x20, 1568]
	ldr	w0, [x20, 1572]
	sub	w2, w1, w0
	cmp	w2, 49
	bgt	.L224
.L210:
	sub	w0, w0, w1
	cmp	w0, 49
	ble	.L205
	ldr	w0, [x19, 632]
	cbnz	w0, .L205
	ldr	x0, .LC60
	ldr	x4, [x0]
	cbz	x4, .L205
	mov	w3, 0
	mov	x2, 0
	mov	w1, 124
	mov	w0, w21
	blr	x4
.L205:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L223:
	ldrb	w1, [x22, 1]
	cbnz	w1, .L213
	ldrb	w1, [x22, 2]
	cmp	w1, 1
	bne	.L213
	ldrb	w22, [x22, 3]
	and	w3, w22, 31
	b	.L209
	.p2align 3
.L224:
	ldr	w2, [x19, 632]
	cmp	w2, 3
	bne	.L210
	ldr	x0, .LC60
	ldr	x4, [x0]
	cbz	x4, .L205
	mov	w1, 124
	mov	w3, 0
	mov	x2, 0
	mov	w0, w21
	blr	x4
	ldr	w1, [x20, 1568]
	ldr	w0, [x20, 1572]
	b	.L210
	.size	CheckStream.part.3, .-CheckStream.part.3
	.align	3
.LC59:
	.xword	s_pstVfmwChan
	.align	3
.LC60:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckStream
	.type	CheckStream, %function
CheckStream:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L225
	cmp	w20, 31
	bhi	.L225
	mov	w1, w20
	mov	x0, x19
	bl	CheckStream.part.3
.L225:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CheckStream, .-CheckStream
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InsertStreamSeg
	.type	InsertStreamSeg, %function
InsertStreamSeg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x22, x0
	mov	x0, x30
	mov	x21, x1
	mov	w23, w2
	bl	_mcount
	cmp	x22, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L233
	add	x19, x22, 180224
	ldp	w1, w20, [x19, 8]
	add	w0, w20, 1
	asr	w3, w0, 31
	lsr	w3, w3, 21
	add	w0, w0, w3
	and	w0, w0, 2047
	sub	w0, w0, w3
	cmp	w0, w1
	beq	.L234
	ldr	x0, [x21]
	cbz	x0, .L232
	cmp	w23, 31
	bls	.L238
.L232:
	sxtw	x0, w20
	ldr	x3, .LC61
	lsl	x20, x0, 2
	mov	x2, 88
	sub	x20, x20, x0
	mov	x1, x21
	lsl	x20, x20, 2
	ldr	x3, [x3, 104]
	sub	x20, x20, x0
	add	x20, x22, x20, lsl 3
	add	x0, x20, 8
	blr	x3
	ldr	w4, [x19, 12]
	mov	w5, 1
	mov	w0, 0
	add	w2, w4, 1
	sxtw	x3, w4
	lsl	x1, x3, 2
	sub	x1, x1, x3
	lsl	x1, x1, 2
	sub	x1, x1, x3
	asr	w3, w2, 31
	lsr	w3, w3, 21
	add	x1, x22, x1, lsl 3
	add	w2, w2, w3
	and	w2, w2, 2047
	sub	w2, w2, w3
	strb	w5, [x1, 16]
	str	w4, [x20, 32]
	str	w2, [x19, 12]
	ldp	w1, w5, [x19, 40]
	ldp	w3, w4, [x21, 16]
	ldr	w2, [x19, 48]
	add	w4, w3, w4
	str	w4, [x19, 36]
	add	w2, w2, 1
	ldr	w3, [x21, 20]
	add	w3, w1, w3
	str	w3, [x19, 40]
	ldr	w1, [x21, 20]
	add	w1, w5, w1
	stp	w1, w2, [x19, 44]
.L231:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L238:
	mov	w1, w23
	bl	CheckStream.part.3
	ldr	w20, [x19, 12]
	b	.L232
	.p2align 3
.L233:
	mov	w0, -1
	b	.L231
	.p2align 3
.L234:
	mov	w0, -4
	b	.L231
	.size	InsertStreamSeg, .-InsertStreamSeg
	.align	3
.LC61:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetStreamSeg
	.type	SCDDRV_GetStreamSeg, %function
SCDDRV_GetStreamSeg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x23, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x23, xzr, 4, ne
	beq	.L246
	add	x22, x20, 180224
	ldp	w19, w2, [x22, 8]
	cmp	w19, w2
	beq	.L248
	sxtw	x1, w19
	lsl	x0, x1, 2
	b	.L253
	.p2align 3
.L243:
	add	w0, w19, 1
	asr	w19, w0, 31
	lsr	w19, w19, 21
	add	w0, w0, w19
	and	w0, w0, 2047
	sub	w19, w0, w19
	cmp	w19, w2
	sxtw	x1, w19
	lsl	x0, x1, 2
	beq	.L248
.L253:
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x20, x0, lsl 3
	ldrsb	w0, [x0, 16]
	cmp	w0, 1
	bne	.L243
	lsl	x21, x1, 2
	sub	x21, x21, x1
	lsl	x21, x21, 2
	sub	x1, x21, x1
	add	x21, x20, x1, lsl 3
	adds	x1, x21, 8
	beq	.L248
	ldr	x3, .LC62
	mov	x2, 88
	mov	x0, x23
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 88
	mov	w2, 2
	ldr	x1, .LC64
	smaddl	x19, w19, w0, x20
	mov	w0, 26
	strb	w2, [x19, 16]
	ldp	w4, w2, [x22, 44]
	ldr	w3, [x21, 28]
	subs	w4, w4, w3
	csel	w4, w4, wzr, pl
	subs	w2, w2, #1
	csel	w2, w2, wzr, pl
	stp	w4, w2, [x22, 44]
	ldrb	w4, [x19, 17]
	ldr	w2, [x21, 24]
	bl	dprint_vfmw
	mov	w0, 0
.L240:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L248:
	mov	w0, -3
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L246:
	mov	w0, -1
	b	.L240
	.size	SCDDRV_GetStreamSeg, .-SCDDRV_GetStreamSeg
	.align	3
.LC62:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC64:
	.xword	.LC63
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseStreamSeg
	.type	ReleaseStreamSeg, %function
ReleaseStreamSeg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cbz	x20, .L275
	sub	w0, w22, #2048
	cmn	w0, #2050
	bls	.L275
	cmn	w22, #1
	add	x24, x20, 180224
	beq	.L288
	ldp	w0, w1, [x24, 8]
	cmp	w0, w1
	bne	.L285
	b	.L263
	.p2align 3
.L266:
	add	w0, w0, 1
	and	w0, w0, 2047
	cmp	w0, w1
	beq	.L263
.L285:
	cmp	w22, w0
	bne	.L266
	uxtw	x0, w0
	lsl	x21, x0, 2
	sub	x21, x21, x0
	lsl	x21, x21, 2
	sub	x0, x21, x0
	add	x0, x20, x0, lsl 3
	add	x21, x0, 8
	ldrsb	w1, [x0, 16]
	cmp	w1, 2
	beq	.L260
.L263:
	mov	w0, -3
.L284:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L288:
	ldp	w22, w0, [x24, 8]
	cmp	w22, w0
	beq	.L263
	sxtw	x23, w22
	ldr	x1, .LC66
	lsl	x3, x23, 2
	mov	w2, w22
	sub	x3, x3, x23
	mov	w0, 0
	lsl	x3, x3, 2
	sub	x23, x3, x23
	bl	dprint_vfmw
	add	x23, x20, x23, lsl 3
	add	x21, x23, 8
	ldr	w0, [x23, 28]
	cbz	w0, .L262
	ldr	x26, .LC70
	mov	x25, 0
	mov	w19, 0
	.p2align 2
.L261:
	ldr	x2, [x23, 8]
	mov	x1, x26
	mov	w0, 0
	add	w19, w19, 1
	ldrb	w2, [x2, x25]
	add	x25, x25, 1
	bl	dprint_vfmw
	ldr	w0, [x23, 28]
	cmp	w0, w19
	ccmp	w19, 15, 2, hi
	bls	.L261
.L262:
	ldr	x1, .LC68
	mov	w0, 0
	bl	dprint_vfmw
.L260:
	cbz	x21, .L263
	ldrb	w4, [x21, 9]
	mov	w5, w22
	ldr	x1, .LC72
	mov	w0, 26
	ldp	w2, w3, [x21, 16]
	strb	wzr, [x21, 8]
	bl	dprint_vfmw
	ldr	w19, [x24, 8]
	cmp	w22, w19
	beq	.L289
.L268:
	ldr	w2, [x21, 20]
	mov	w0, 0
	ldr	w1, [x24, 40]
	subs	w1, w1, w2
	csel	w1, w1, wzr, pl
	str	w1, [x24, 40]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L289:
	ldr	x22, .LC73
	ldr	x23, .LC75
	add	x22, x22, 40
	b	.L271
	.p2align 3
.L269:
	ldr	w2, [x24, 12]
	lsl	x0, x0, 2
	sub	x0, x0, x1
	cmp	w19, w2
	add	x0, x20, x0, lsl 3
	beq	.L272
	ldrsb	w1, [x0, 16]
	cbnz	w1, .L290
.L270:
	add	w19, w19, 1
	and	w19, w19, 2047
.L271:
	uxtw	x1, w19
	cmp	w19, 2047
	lsl	x0, x1, 2
	sub	x0, x0, x1
	bls	.L269
	mov	x2, x22
	mov	x1, x23
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x24, 12]
	cmp	w19, w2
	bne	.L270
	.p2align 2
.L272:
	ldr	w0, [x24, 36]
	str	w2, [x24, 8]
	str	w0, [x24, 32]
	b	.L268
	.p2align 3
.L290:
	str	w19, [x24, 8]
	ldr	w0, [x0, 24]
	str	w0, [x24, 32]
	b	.L268
.L275:
	mov	w0, -1
	b	.L284
	.size	ReleaseStreamSeg, .-ReleaseStreamSeg
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
.LC73:
	.xword	.LANCHOR3
	.align	3
.LC75:
	.xword	.LC74
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSegStreamSize
	.type	GetSegStreamSize, %function
GetSegStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L293
	add	x19, x19, 180224
	mov	w0, 0
	ldr	w1, [x19, 40]
	str	w1, [x20]
.L292:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L293:
	mov	w0, -1
	b	.L292
	.size	GetSegStreamSize, .-GetSegStreamSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSegStreamNum
	.type	GetSegStreamNum, %function
GetSegStreamNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L296
	add	x19, x19, 180224
	ldp	w1, w0, [x19, 8]
	ldr	x19, [sp, 16]
	sub	w0, w0, w1
	and	w0, w0, 2047
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L296:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetSegStreamNum, .-GetSegStreamNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetFreshSegStream
	.type	GetFreshSegStream, %function
GetFreshSegStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x1
	mov	x20, x2
	bl	_mcount
	cmp	x21, xzr
	ccmp	x20, xzr, 4, ne
	ccmp	x19, xzr, 4, ne
	beq	.L297
	add	x19, x19, 180224
	ldr	w0, [x19, 48]
	str	w0, [x21]
	ldr	w0, [x19, 44]
	str	w0, [x20]
.L297:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetFreshSegStream, .-GetFreshSegStream
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_PrepareSleep
	.type	SCDDRV_PrepareSleep, %function
SCDDRV_PrepareSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L303
	ldr	x1, .LC77
	ldr	w0, [x1, 600]
	cbnz	w0, .L303
	ldr	w0, [x1, 56]
	cbz	w0, .L304
	mov	w2, 1
	mov	w0, 0
	str	w2, [x1, 600]
.L300:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L304:
	mov	w2, 2
	str	w2, [x1, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L303:
	mov	w0, -1
	b	.L300
	.size	SCDDRV_PrepareSleep, .-SCDDRV_PrepareSleep
	.align	3
.LC77:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetSleepStage
	.type	SCDDRV_GetSleepStage, %function
SCDDRV_GetSleepStage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, 3
	cbz	w19, .L308
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L308:
	ldr	x0, .LC78
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 600]
	ret
	.size	SCDDRV_GetSleepStage, .-SCDDRV_GetSleepStage
	.align	3
.LC78:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ForceSleep
	.type	SCDDRV_ForceSleep, %function
SCDDRV_ForceSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L309
	ldr	x0, .LC79
	ldr	w1, [x0, 600]
	cmp	w1, 2
	beq	.L309
	mov	w1, 2
	str	w1, [x0, 600]
.L309:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ForceSleep, .-SCDDRV_ForceSleep
	.align	3
.LC79:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ExitSleep
	.type	SCDDRV_ExitSleep, %function
SCDDRV_ExitSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L314
	ldr	x0, .LC80
	str	wzr, [x0, 600]
.L314:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	3
.LC80:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ClearInst
	.type	SM_ClearInst, %function
SM_ClearInst:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L318
	ldr	x20, .LC82
	sbfiz	x19, x19, 4, 32
	ldr	x0, .LC81
	mov	x2, 16856
	add	x20, x20, 88
	movk	x2, 0x4, lsl 16
	mov	w1, 0
	ldr	x3, [x0, 96]
	ldr	x0, [x20, x19]
	blr	x3
	ldr	x1, [x20, x19]
	mov	x2, -1
	mov	w0, 0
	add	x1, x1, 278528
	str	x2, [x1, 280]
.L317:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L318:
	mov	w0, -1
	b	.L317
	.size	SM_ClearInst, .-SM_ClearInst
	.align	3
.LC81:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC82:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_InstInit
	.type	SM_InstInit, %function
SM_InstInit:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC84
	ldr	x21, .LC85
	add	x19, x20, 88
	add	x20, x20, 600
	.p2align 2
.L320:
	ldr	x3, [x21, 96]
	mov	x0, x19
	mov	x2, 16
	mov	w1, 0
	add	x19, x19, x2
	blr	x3
	cmp	x19, x20
	bne	.L320
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	SM_InstInit, .-SM_InstInit
	.align	3
.LC84:
	.xword	.LANCHOR0
	.align	3
.LC85:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_OpenSCDDrv
	.type	SM_OpenSCDDrv, %function
SM_OpenSCDDrv:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w19, w0
	mov	x0, x30
	mov	w23, w1
	mov	w20, w2
	bl	_mcount
	cmp	w23, wzr
	ccmp	w20, wzr, 0, gt
	ccmp	w19, wzr, 4, eq
	beq	.L330
	cbz	w20, .L331
	cmp	w20, 1
	bne	.L338
	mov	w0, 49152
	movk	w0, 0xf9c5, lsl 16
.L325:
	sxtw	x21, w20
	ldr	x24, .LC90
	lsl	x25, x21, 6
	add	x25, x25, x21, lsl 3
	add	x26, x24, x21, lsl 2
	add	x20, x24, x25
	str	w0, [x26, 80]
	ldr	w0, [x20, 48]
	cmp	w0, 1
	beq	.L329
	ldr	x0, .LC91
	mov	x2, 72
	mov	w1, 0
	ldr	x3, [x0, 96]
	mov	x0, x20
	blr	x3
	str	w19, [x24, x25]
	lsl	x2, x21, 4
	ldr	x1, .LC92
	sub	x21, x2, x21
	add	w0, w19, 15
	and	w0, w0, -16
	str	w23, [x20, 4]
	add	x21, x1, x21, lsl 2
	str	w0, [x20, 16]
	sub	w22, w0, w19
	str	wzr, [x26, 600]
	str	wzr, [x21, 56]
	bl	MEM_Phy2Vir
	str	x0, [x20, 8]
	add	w1, w19, 12288
	mov	w0, 12288
	add	w1, w1, w22
	str	w0, [x20, 20]
	str	w1, [x20, 32]
	mov	w0, w1
	add	w19, w19, 28672
	add	w19, w19, 127
	bl	MEM_Phy2Vir
	add	w19, w19, w22
	str	x0, [x20, 24]
	and	w19, w19, -128
	mov	w0, 16384
	str	w0, [x20, 36]
	mov	w0, w19
	str	w19, [x24, 72]
	bl	MEM_Phy2Vir
	str	x0, [x24, 608]
	cbz	x0, .L339
	add	w22, w22, 45056
	ldr	w2, [x26, 80]
	add	w22, w22, 1536
	ldr	w0, [x26, 624]
	mov	w1, 17920
	cmp	w23, w22
	stp	w2, w0, [x20, 40]
	str	w1, [x24, 616]
	blt	.L329
	ldr	x0, [x20, 8]
	cbz	x0, .L329
	ldr	x0, [x20, 24]
	cbz	x0, .L329
	mov	w1, 1
	str	w1, [x20, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L338:
	ldr	x2, .LC87
	mov	w0, 0
	ldr	x1, .LC89
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -7
.L323:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L331:
	mov	w0, 49152
	movk	w0, 0xf8c3, lsl 16
	b	.L325
	.p2align 3
.L329:
	mov	w0, -7
	b	.L323
	.p2align 3
.L330:
	mov	w0, -1
	b	.L323
.L339:
	ldr	x2, .LC87
	ldr	x1, .LC94
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L323
	.size	SM_OpenSCDDrv, .-SM_OpenSCDDrv
	.align	3
.LC87:
	.xword	.LANCHOR3
	.align	3
.LC89:
	.xword	.LC88
	.align	3
.LC90:
	.xword	.LANCHOR0
	.align	3
.LC91:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC92:
	.xword	g_VfmwGlobalStat
	.align	3
.LC94:
	.xword	.LC93
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_CloseSCDDrv
	.type	SM_CloseSCDDrv, %function
SM_CloseSCDDrv:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L344
	ldr	x0, .LC95
	mov	w1, 0
	add	x2, x0, 88
	b	.L343
	.p2align 3
.L342:
	cmp	w1, 32
	add	x2, x2, 16
	beq	.L352
.L343:
	cmp	w1, 31
	add	w1, w1, 1
	bhi	.L342
	ldr	x3, [x2]
	add	x4, x3, 278528
	cbz	x3, .L342
	ldr	w3, [x4, 256]
	cbz	w3, .L342
	ldr	w3, [x4, 244]
	cmp	w3, wzr
	bgt	.L342
	str	wzr, [x4, 256]
	cmp	w1, 32
	add	x2, x2, 16
	bne	.L343
	.p2align 2
.L352:
	ldr	x3, .LC97
	mov	x2, 72
	ldr	x4, .LC96
	mov	w1, 0
	ldr	x3, [x3, 96]
	str	wzr, [x4, 56]
	blr	x3
	mov	w0, 0
.L341:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L344:
	mov	w0, -1
	b	.L341
	.size	SM_CloseSCDDrv, .-SM_CloseSCDDrv
	.align	3
.LC95:
	.xword	.LANCHOR0
	.align	3
.LC96:
	.xword	g_VfmwGlobalStat
	.align	3
.LC97:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Config
	.type	SM_Config, %function
SM_Config:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	w22, 31, 2, ne
	bhi	.L356
	ldr	x1, .LC98
	add	x0, x1, x22, sxtw 4
	ldr	x20, [x0, 88]
	cbz	x20, .L356
	add	x24, x20, 278528
	ldr	w0, [x19, 48]
	str	w0, [x24, 328]
	ldr	w0, [x19, 16]
	ldr	w2, [x20, 24]
	cmp	w2, w0
	beq	.L375
	cbz	w0, .L356
	ldr	x0, [x19]
	cbz	x0, .L356
	ldr	x2, [x1, 8]
	str	x2, [x24, 192]
	ldp	w5, w4, [x1, 16]
	ldr	x2, [x1, 24]
	ldr	w3, [x1, 32]
	ldr	w1, [x1, 36]
	str	x2, [x24, 208]
	mov	w2, 262143
	str	w1, [x24, 220]
	mov	w1, 2048
	stp	w4, w5, [x24, 200]
	str	w1, [x24, 224]
	str	w3, [x24, 216]
	ldr	w21, [x19, 16]
	ldr	x25, [x19]
	add	w23, w21, 3
	and	w23, w23, -4
	sub	w21, w23, w21
	add	w23, w23, 131072
	str	w23, [x24, 228]
	sxtw	x1, w21
	add	x1, x1, 131072
	add	x25, x25, x1
	str	x25, [x24, 184]
	ldr	w1, [x19, 20]
	sub	w21, w1, w21
	sub	w21, w21, #131072
	sub	w21, w21, #1024
	str	w21, [x24, 232]
	cmp	w21, w2
	ble	.L356
	add	x27, x20, 98304
	adds	x28, x27, 112
	beq	.L376
	cmp	w23, wzr
	ldr	x26, .LC99
	ccmp	x25, xzr, 4, ne
	ccmp	w21, w2, 0, ne
	bhi	.L377
.L359:
	add	x20, x20, 8
	ldr	x3, [x26, 104]
	mov	x2, 80
	mov	x1, x19
	mov	x0, x20
	blr	x3
	str	wzr, [x24, 244]
.L358:
	ldr	x3, [x26, 104]
	mov	x2, 80
	mov	x1, x19
	mov	x0, x20
	blr	x3
	mov	w0, 2
	str	w0, [x24, 316]
	ldr	w0, [x19, 12]
	cmp	w0, 2
	beq	.L378
.L360:
	mov	w0, 0
	str	w22, [x24, 240]
.L355:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L378:
	mov	w0, 3
	str	w0, [x24, 316]
	b	.L360
	.p2align 3
.L377:
	mov	x0, x28
	mov	x2, 49208
	add	x28, x28, 180224
	ldr	x3, [x26, 96]
	movk	x2, 0x2, lsl 16
	mov	w1, 0
	blr	x3
	str	w23, [x28, 24]
	str	x25, [x27, 112]
	stp	w21, w23, [x28, 28]
	str	w23, [x28, 36]
	b	.L359
	.p2align 3
.L375:
	add	x20, x20, 8
	ldr	x26, .LC99
	b	.L358
	.p2align 3
.L376:
	ldr	x26, .LC99
	b	.L359
	.p2align 3
.L356:
	mov	w0, -1
	b	.L355
	.size	SM_Config, .-SM_Config
	.align	3
.LC98:
	.xword	.LANCHOR0
	.align	3
.LC99:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_CfgBuf
	.type	SM_CfgBuf, %function
SM_CfgBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L387
	cbnz	w20, .L388
	ldr	x1, .LC104
	add	x19, x1, x19, sxtw 4
	ldr	x2, [x19, 88]
	cbz	x2, .L383
	add	x2, x2, 278528
	ldr	w0, [x2, 244]
	cbz	w0, .L381
	ldp	w7, w5, [x1, 16]
	ldr	w4, [x1, 32]
	mov	w0, 0
	ldr	x6, [x1, 8]
	ldr	x3, [x1, 24]
	ldr	w1, [x1, 36]
	stp	w4, w1, [x2, 216]
	str	x6, [x2, 192]
	mov	w1, 2048
	stp	w5, w7, [x2, 200]
	str	x3, [x2, 208]
	str	wzr, [x2, 244]
	str	w1, [x2, 224]
.L381:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L387:
	ldr	x1, .LC101
	mov	w3, w19
	mov	w2, 1338
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L381
	.p2align 3
.L388:
	ldr	x1, .LC103
	mov	w3, w20
	mov	w2, 1345
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L381
.L383:
	mov	w0, -1
	b	.L381
	.size	SM_CfgBuf, .-SM_CfgBuf
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC103:
	.xword	.LC102
	.align	3
.LC104:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Start
	.type	SM_Start, %function
SM_Start:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L391
	ldr	x0, .LC105
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	cbz	x0, .L394
	ldr	w1, [x0, 28]
	cbz	w1, .L394
	add	x1, x0, 278528
	ldr	w0, [x1, 256]
	cbnz	w0, .L394
	mov	w2, 1
	str	w2, [x1, 256]
.L390:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L394:
	mov	w0, -7
	b	.L390
	.p2align 3
.L391:
	mov	w0, -1
	b	.L390
	.size	SM_Start, .-SM_Start
	.align	3
.LC105:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Stop
	.type	SM_Stop, %function
SM_Stop:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L397
	ldr	x0, .LC106
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	cbz	x0, .L398
	add	x1, x0, 278528
	ldr	w0, [x1, 256]
	cbz	w0, .L396
	ldr	w0, [x1, 244]
	cmp	w0, wzr
	bgt	.L399
	mov	w0, 0
	str	wzr, [x1, 256]
.L396:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L399:
	mov	w0, -7
	b	.L396
	.p2align 3
.L398:
	mov	w0, 0
	b	.L396
	.p2align 3
.L397:
	mov	w0, -1
	b	.L396
	.size	SM_Stop, .-SM_Stop
	.align	3
.LC106:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_GetInfo
	.type	SM_GetInfo, %function
SM_GetInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	w20, 31, 2, ne
	bhi	.L413
	ldr	x0, .LC107
	add	x20, x0, x20, sxtw 4
	ldr	x0, [x20, 88]
	cbz	x0, .L417
	add	x2, x0, 278528
	add	x1, x0, 98304
	adds	x5, x1, 112
	ldr	w3, [x2, 256]
	strb	w3, [x19]
	ldr	w2, [x2, 308]
	str	w2, [x19, 20]
	beq	.L414
	add	x3, x5, 180224
	ldr	w2, [x3, 12]
	ldr	w3, [x3, 8]
	sub	w2, w2, w3
	and	w2, w2, 2047
.L406:
	adds	x0, x0, 88
	str	w2, [x19, 8]
	cset	w4, eq
	cmn	x19, #4
	cset	w3, eq
	orr	w3, w4, w3
	cbnz	w3, .L408
	add	x3, x0, 98304
	ldr	w2, [x3, 4]
	ldr	w3, [x3]
	subs	w2, w2, w3
	bmi	.L418
.L416:
	str	w2, [x19, 4]
.L408:
	cmn	x19, #12
	cset	w2, eq
	orr	w2, w4, w2
	cbnz	w2, .L411
	add	x0, x0, 98304
	ldr	w2, [x0, 20]
	str	w2, [x19, 12]
	ldr	w0, [x0, 12]
	sub	w2, w2, w0
	str	w2, [x19, 12]
.L411:
	add	x0, x19, 16
	cmp	x0, xzr
	ccmp	x5, xzr, 4, ne
	beq	.L415
	add	x1, x1, 112
	mov	w0, 0
	add	x1, x1, 180224
	ldr	w1, [x1, 40]
	str	w1, [x19, 16]
.L404:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L418:
	add	w2, w2, 1024
	b	.L416
	.p2align 3
.L417:
	cbz	x19, .L413
	strb	wzr, [x19]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L414:
	mov	w2, 0
	b	.L406
	.p2align 3
.L415:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L413:
	mov	w0, -1
	b	.L404
	.size	SM_GetInfo, .-SM_GetInfo
	.align	3
.LC107:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetRawNumInFrame
	.type	GetRawNumInFrame, %function
GetRawNumInFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	mov	x21, x2
	bl	_mcount
	add	x2, x20, 98304
	mov	w3, 1
	ldr	w0, [x2]
	uxtw	x5, w0
	lsl	x1, x5, 2
	sub	x1, x1, x5
	add	x1, x20, x1, lsl 5
	ldr	w1, [x1, 12]
	str	w1, [x21]
	str	w3, [x19]
	b	.L420
	.p2align 3
.L422:
	ldr	w3, [x19]
	add	w3, w3, 1
	str	w3, [x19]
	ldr	w1, [x21]
	ldr	w3, [x4, 12]
	add	w3, w1, w3
	str	w3, [x21]
	ldr	w1, [x2, 4]
	cmp	w0, w1
	beq	.L424
	ldr	w1, [x19]
	cmp	w1, 1024
	bhi	.L424
.L420:
	lsl	x3, x5, 2
	add	w0, w0, 1
	sub	x3, x3, x5
	and	w0, w0, 1023
	lsl	x3, x3, 5
	uxtw	x5, w0
	lsl	x4, x5, 2
	ldrb	w1, [x20, x3]
	sub	x4, x4, x5
	add	x4, x20, x4, lsl 5
	cbnz	w1, .L422
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L424:
	mov	w0, -4
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	GetRawNumInFrame, .-GetRawNumInFrame
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	AdjustRawPacketVP6A
	.type	AdjustRawPacketVP6A, %function
AdjustRawPacketVP6A:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x23, x1
	mov	x22, x0
	mov	x0, x30
	mov	x19, x4
	mov	x21, x2
	mov	x20, x3
	bl	_mcount
	add	x0, x22, 98304
	ldr	w4, [x23]
	ldr	w5, [x0]
	cbz	w4, .L430
	uxtw	x7, w5
	lsl	x0, x7, 2
	sub	x0, x0, x7
	add	x0, x22, x0, lsl 5
	ldr	w6, [x0, 12]
	cmp	w6, 2
	bgt	.L431
	mov	w0, w6
	mov	w3, 3
	mov	w2, 0
	b	.L428
	.p2align 3
.L429:
	uxtw	x7, w5
	lsl	x0, x7, 2
	sub	x0, x0, x7
	add	x0, x22, x0, lsl 5
	ldr	w0, [x0, 12]
	add	w6, w6, w0
	cmp	w6, 2
	bgt	.L433
.L428:
	add	w2, w2, 1
	add	w5, w5, 1
	cmp	w2, w4
	sub	w3, w3, w0
	and	w5, w5, 1023
	bne	.L429
.L430:
	mov	w0, -4
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L433:
	sxtw	x3, w3
.L427:
	lsl	x0, x7, 2
	sub	w2, w4, w2
	sub	x7, x0, x7
	str	w2, [x23]
	sub	w6, w6, #3
	mov	w0, 0
	add	x22, x22, x7, lsl 5
	ldr	x1, [x22, 40]
	add	x3, x1, x3
	str	x3, [x21]
	str	w6, [x20]
	str	w5, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L431:
	mov	x3, 3
	mov	w2, 0
	b	.L427
	.size	AdjustRawPacketVP6A, .-AdjustRawPacketVP6A
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_CopyRawToSeg
	.type	SM_CopyRawToSeg, %function
SM_CopyRawToSeg:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	mov	x26, x1
	str	w19, [x29, 100]
	bl	_mcount
	ldr	x0, .LC108
	mov	x1, x19
	add	x0, x0, x1, sxtw 4
	ldr	x28, [x0, 88]
	cbz	x28, .L455
	add	x22, x28, 88
	add	x25, x28, 98304
	add	x0, x25, 112
	cmp	x22, xzr
	ccmp	x0, xzr, 4, ne
	str	x0, [x29, 104]
	ccmp	x26, xzr, 4, ne
	beq	.L455
	add	x0, x22, 98304
	ldp	w23, w4, [x0]
	cmp	w4, w23
	beq	.L475
	uxtw	x1, w23
	mov	w0, w23
	lsl	x2, x1, 2
	mov	x3, x1
	sub	x2, x2, x1
	mov	w21, 1
	add	x1, x22, x2, lsl 5
	ldr	w27, [x1, 12]
	b	.L437
	.p2align 3
.L439:
	add	w21, w21, 1
	ldr	w1, [x2, 12]
	cmp	w21, 1024
	ccmp	w4, w0, 4, ls
	add	w27, w27, w1
	beq	.L475
.L437:
	lsl	x2, x3, 2
	add	w0, w0, 1
	sub	x1, x2, x3
	and	w0, w0, 1023
	lsl	x1, x1, 5
	uxtw	x3, w0
	lsl	x2, x3, 2
	ldrb	w1, [x22, x1]
	sub	x2, x2, x3
	add	x2, x22, x2, lsl 5
	cbnz	w1, .L439
	ldr	x0, [x29, 104]
	cbz	x0, .L452
	ldr	x0, .LC109
	mov	x2, 49152
	mov	w1, 0
	movk	x2, 0x2, lsl 16
	ldr	x3, [x0, 96]
	add	x0, x25, 120
	blr	x3
	add	x0, x25, 112
	add	x0, x0, 180224
	ldr	w1, [x0, 24]
	stp	wzr, wzr, [x0, 8]
	str	wzr, [x0, 16]
	stp	w1, w1, [x0, 32]
.L452:
	add	x0, x25, 112
	add	x0, x0, 180224
	ldr	w1, [x0, 28]
	cmp	w1, w27
	blt	.L477
	sxtw	x19, w23
	ldr	w1, [x28, 20]
	lsl	x2, x19, 2
	ldr	x24, [x25, 112]
	sub	x2, x2, x19
	cmp	w1, 12
	add	x1, x22, 98304
	ldr	w0, [x0, 24]
	add	x2, x22, x2, lsl 5
	ldr	w23, [x1]
	ldr	w25, [x2, 12]
	ldr	x28, [x2, 40]
	ccmp	w25, wzr, 4, eq
	beq	.L442
	cbz	w21, .L475
	uxtw	x20, w23
	lsl	x1, x20, 2
	sub	x1, x1, x20
	add	x1, x22, x1, lsl 5
	ldr	w25, [x1, 12]
	cmp	w25, 2
	bgt	.L456
	mov	w6, 3
	mov	w2, 0
	mov	w5, w25
	b	.L445
	.p2align 3
.L446:
	uxtw	x20, w23
	lsl	x1, x20, 2
	sub	x1, x1, x20
	add	x1, x22, x1, lsl 5
	ldr	w5, [x1, 12]
	add	w25, w25, w5
	cmp	w25, 2
	bgt	.L478
.L445:
	add	w2, w2, 1
	add	w23, w23, 1
	cmp	w2, w21
	sub	w6, w6, w5
	and	w23, w23, 1023
	bne	.L446
	.p2align 2
.L475:
	mov	w0, -4
.L472:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L478:
	sxtw	x6, w6
.L443:
	lsl	x1, x20, 2
	sub	w21, w21, w2
	sub	x1, x1, x20
	sub	w25, w25, #3
	add	x1, x22, x1, lsl 5
	ldr	x28, [x1, 40]
	add	x28, x28, x6
	.p2align 2
.L442:
	str	w0, [x26, 16]
	bl	MEM_Phy2Vir
	str	x0, [x26]
	lsl	x1, x19, 2
	sub	x2, x24, x0
	sub	x1, x1, x19
	str	w2, [x26, 20]
	mov	w3, 1
	add	x1, x22, x1, lsl 5
	ldr	x2, [x1, 64]
	str	x2, [x26, 32]
	ldr	x2, [x1, 64]
	str	x2, [x26, 40]
	ldr	x2, [x1, 48]
	str	x2, [x26, 48]
	strb	w3, [x26, 9]
	ldr	x2, [x1, 56]
	str	x2, [x26, 56]
	ldr	w2, [x1, 24]
	str	w2, [x26, 64]
	ldr	w2, [x1, 28]
	str	w2, [x26, 68]
	ldr	w2, [x1, 32]
	str	w2, [x26, 72]
	ldr	w1, [x1, 36]
	str	w1, [x26, 76]
	cbz	w21, .L447
	cmp	x28, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L475
	ldr	x0, .LC109
	mov	w19, 0
	uxtw	x20, w23
	str	x0, [x29, 112]
	b	.L449
	.p2align 3
.L450:
	cmp	x28, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L475
.L449:
	sxtw	x2, w25
	mov	w0, 2
	str	x2, [x29, 120]
	add	w23, w23, 1
	bl	VCTRL_RecordPosTime
	and	w23, w23, 1023
	ldp	x0, x2, [x29, 112]
	mov	x1, x28
	add	w19, w19, 1
	ldr	x6, [x0, 104]
	mov	x0, x24
	add	x24, x24, x2
	blr	x6
	mov	w0, 3
	bl	VCTRL_RecordPosTime
	mov	w1, w25
	mov	w0, 0
	bl	VCTRL_RecordData
	lsl	x2, x20, 2
	ldr	w1, [x26, 20]
	sub	x2, x2, x20
	uxtw	x20, w23
	lsl	x0, x20, 2
	add	w25, w1, w25
	add	x2, x22, x2, lsl 5
	sub	x0, x0, x20
	cmp	w21, w19
	add	x0, x22, x0, lsl 5
	ldrb	w1, [x2, 1]
	strb	w1, [x26, 10]
	str	w25, [x26, 20]
	ldr	w25, [x0, 12]
	ldr	x28, [x0, 40]
	bne	.L450
	ldr	x0, [x26]
.L447:
	cbz	x0, .L479
	ldr	w2, [x29, 100]
	mov	x1, x26
	ldr	x0, [x29, 104]
	bl	InsertStreamSeg
	mov	w1, w27
	mov	x0, x22
	bl	DeleteRawLen
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L477:
	ldr	x1, .LC111
	mov	w2, w27
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, w27
	mov	x0, x22
	bl	DeleteRawLen
	cbz	w0, .L475
	ldr	x1, .LC113
	mov	w2, 1561
	mov	w0, 0
	bl	dprint_vfmw
	b	.L475
.L455:
	mov	w0, -1
	b	.L472
.L456:
	mov	x6, 3
	mov	w2, 0
	b	.L443
.L479:
	ldr	x2, .LC114
	mov	w3, 1622
	ldr	x1, .LC116
	mov	w0, 1
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -4
	b	.L472
	.size	SM_CopyRawToSeg, .-SM_CopyRawToSeg
	.align	3
.LC108:
	.xword	.LANCHOR0
	.align	3
.LC109:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.align	3
.LC114:
	.xword	.LANCHOR3
	.align	3
.LC116:
	.xword	.LC115
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsSCDByPass
	.type	SCDDRV_IsSCDByPass, %function
SCDDRV_IsSCDByPass:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	tst	w19, -17
	beq	.L484
	sub	w0, w19, #2
	cmp	w0, 1
	ccmp	w19, 6, 4, hi
	beq	.L484
	cmp	w19, 1
	beq	.L486
.L482:
	cmp	w19, 15
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L484:
	mov	w0, 0
.L481:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L486:
	ldr	w1, [x20]
	mov	w0, 0
	cbz	w1, .L482
	b	.L481
	.size	SCDDRV_IsSCDByPass, .-SCDDRV_IsSCDByPass
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SaveStreamSeg
	.type	SCDDRV_SaveStreamSeg, %function
SCDDRV_SaveStreamSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	ldr	x20, .LC117
	ldr	x0, [x20, w21, sxtw 3]
	cbz	x0, .L487
	ldr	x19, .LC118
	mov	w0, 0
	ldr	x1, [x19, 32]
	blr	x1
	ldr	w1, [x22, 20]
	ldr	x2, [x20, w21, sxtw 3]
	ldr	x3, [x19, 88]
	ldr	x0, [x22]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
.L487:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	SCDDRV_SaveStreamSeg, .-SCDDRV_SaveStreamSeg
	.align	3
.LC117:
	.xword	vfmw_save_seg_file
	.align	3
.LC118:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ReadSegStream
	.type	SM_ReadSegStream, %function
SM_ReadSegStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	x21, xzr
	ccmp	w20, 31, 2, ne
	bhi	.L497
	ldr	x0, .LC119
	add	x0, x0, x20, sxtw 4
	ldr	x19, [x0, 88]
	cbz	x19, .L497
	ldr	w0, [x19, 20]
	add	x1, x19, 36
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cbnz	w0, .L504
.L494:
	add	x0, x19, 98304
	mov	x1, x21
	add	x0, x0, 112
	add	x19, x19, 278528
	bl	SCDDRV_GetStreamSeg
	cbz	w0, .L505
	ldr	w1, [x19, 308]
	add	w1, w1, 1
	str	w1, [x19, 308]
.L493:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L504:
	mov	x1, x21
	mov	w0, w20
	bl	SM_CopyRawToSeg
	cbz	w0, .L494
	ldr	x1, .LC121
	add	x19, x19, 278528
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w1, [x19, 308]
	mov	w0, -7
	add	w1, w1, 1
	str	w1, [x19, 308]
	b	.L493
	.p2align 3
.L505:
	mov	x1, x21
	mov	w0, w20
	str	wzr, [x19, 308]
	bl	SCDDRV_SaveStreamSeg
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L497:
	mov	w0, -1
	b	.L493
	.size	SM_ReadSegStream, .-SM_ReadSegStream
	.align	3
.LC119:
	.xword	.LANCHOR0
	.align	3
.LC121:
	.xword	.LC120
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ReleaseStreamSeg
	.type	SM_ReleaseStreamSeg, %function
SM_ReleaseStreamSeg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L509
	ldr	x0, .LC122
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	cbz	x0, .L509
	add	x0, x0, 98304
	mov	w1, w20
	add	x0, x0, 112
	bl	ReleaseStreamSeg
.L507:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L509:
	mov	w0, -1
	b	.L507
	.size	SM_ReleaseStreamSeg, .-SM_ReleaseStreamSeg
	.align	3
.LC122:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_GiveThreadEvent
	.type	SM_GiveThreadEvent, %function
SM_GiveThreadEvent:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC123
	mov	w0, 0
	ldr	x1, [x1, 256]
	blr	x1
	ldp	x29, x30, [sp], 16
	ret
	.size	SM_GiveThreadEvent, .-SM_GiveThreadEvent
	.align	3
.LC123:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CalcInstBlockTime
	.type	CalcInstBlockTime, %function
CalcInstBlockTime:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x0, .LC124
	ldr	x0, [x0]
	blr	x0
	mov	w3, w0
	add	x1, x19, 278528
	cbnz	w20, .L515
	ldr	w2, [x1, 272]
	cmp	w0, w2
	bhi	.L516
	str	wzr, [x1, 268]
	mov	w0, 0
	str	w3, [x1, 272]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L516:
	sub	w0, w0, w2
	str	w0, [x1, 268]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L515:
	str	wzr, [x1, 268]
	mov	w0, 0
	str	w3, [x1, 272]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CalcInstBlockTime, .-CalcInstBlockTime
	.align	3
.LC124:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsChanDec
	.type	SCDDRV_IsChanDec, %function
SCDDRV_IsChanDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC125
	ldr	w1, [x0, 56]
	cmp	w1, 1
	beq	.L520
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L520:
	ldr	w0, [x0, 52]
	cmp	w0, w19
	ldr	x19, [sp, 16]
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsChanDec, .-SCDDRV_IsChanDec
	.align	3
.LC125:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetRawStreamStatus
	.type	SCDDRV_GetRawStreamStatus, %function
SCDDRV_GetRawStreamStatus:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	cmp	x19, xzr
	cset	w1, eq
	cmp	x20, xzr
	cset	w3, eq
	orr	w3, w1, w3
	cbnz	w3, .L522
	add	x0, x19, 98304
	ldr	w3, [x0, 20]
	str	w3, [x20]
	ldr	w0, [x0, 12]
	sub	w3, w3, w0
	str	w3, [x20]
.L522:
	cmp	x21, xzr
	cset	w0, eq
	orr	w0, w1, w0
	cbnz	w0, .L521
	add	x19, x19, 98304
	ldp	w1, w0, [x19]
	subs	w0, w0, w1
	bmi	.L528
.L527:
	str	w0, [x21]
.L521:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L528:
	add	w0, w0, 1024
	b	.L527
	.size	SCDDRV_GetRawStreamStatus, .-SCDDRV_GetRawStreamStatus
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetFreeSegBufSize
	.type	GetFreeSegBufSize, %function
GetFreeSegBufSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L529
	mov	x1, x20
	mov	x0, x19
	bl	GetFreeSegBufSize.part.6
.L529:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetFreeSegBufSize, .-GetFreeSegBufSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_GetSegStreamStatus
	.type	SCDDRV_GetSegStreamStatus, %function
SCDDRV_GetSegStreamStatus:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	x21, x2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	bne	.L537
.L532:
	ldr	w0, [x20]
	cmp	w0, 78
	bhi	.L533
	str	wzr, [x20]
	cbz	x19, .L536
.L538:
	add	x19, x19, 180224
	mov	w2, 2048
	ldp	w0, w1, [x19, 8]
	sub	w0, w1, w0
	and	w0, w0, 2047
	sub	w0, w2, w0
	str	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L533:
	sub	w0, w0, #79
	str	w0, [x20]
	cbnz	x19, .L538
.L536:
	mov	w0, 2048
	str	w0, [x21]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L537:
	mov	x1, x20
	mov	x0, x19
	bl	GetFreeSegBufSize.part.6
	b	.L532
	.size	SCDDRV_GetSegStreamStatus, .-SCDDRV_GetSegStreamStatus
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsRawStreamNotEnough
	.type	SCDDRV_IsRawStreamNotEnough, %function
SCDDRV_IsRawStreamNotEnough:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, wzr
	ccmp	w19, 3, 0, ne
	cset	w0, ls
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsRawStreamNotEnough, .-SCDDRV_IsRawStreamNotEnough
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsFreeSegSlotNotEnough
	.type	SCDDRV_IsFreeSegSlotNotEnough, %function
SCDDRV_IsFreeSegSlotNotEnough:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 512
	ldr	x19, [sp, 16]
	cset	w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsFreeSegSlotNotEnough, .-SCDDRV_IsFreeSegSlotNotEnough
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_IsFreeSegBufNotEnough
	.type	SCDDRV_IsFreeSegBufNotEnough, %function
SCDDRV_IsFreeSegBufNotEnough:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, w20, lsr 3
	cset	w0, ls
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsFreeSegBufNotEnough, .-SCDDRV_IsFreeSegBufNotEnough
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_CheckConditionOfStartSCD
	.type	SCDDRV_CheckConditionOfStartSCD, %function
SCDDRV_CheckConditionOfStartSCD:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x2
	mov	x20, x1
	mov	x22, x3
	mov	x23, x4
	bl	_mcount
	cmp	x21, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L543
	add	x1, x19, 98304
	ldr	w0, [x1, 20]
	str	w0, [x21]
	ldr	w1, [x1, 12]
	sub	w0, w0, w1
	str	w0, [x21]
.L543:
	cbz	x19, .L547
	add	x19, x19, 98304
	ldr	w3, [x21]
	mov	w0, -5
	ldp	w2, w1, [x19]
	sub	w1, w1, w2
	cmp	w1, wzr
	add	w2, w1, 1024
	csel	w1, w2, w1, lt
	cmp	w3, 3
	ccmp	w1, wzr, 4, hi
	cset	w1, eq
	cbnz	w1, .L544
	mov	x0, x20
	mov	x2, x23
	mov	x1, x22
	bl	SCDDRV_GetSegStreamStatus
	ldr	w0, [x23]
	cmp	w0, 512
	bls	.L549
	add	x20, x20, 180224
	ldr	w1, [x22]
	mov	w0, -6
	ldr	w2, [x20, 28]
	cmp	w1, w2, lsr 3
	csel	w0, w0, wzr, ls
.L544:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L547:
	mov	w0, -5
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L549:
	mov	w0, -6
	b	.L544
	.size	SCDDRV_CheckConditionOfStartSCD, .-SCDDRV_CheckConditionOfStartSCD
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SetCtrlReg
	.type	SCDDRV_SetCtrlReg, %function
SCDDRV_SetCtrlReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	add	x0, x20, 278528
	ldr	w2, [x20, 20]
	mov	w4, 1
	strb	w4, [x19, 2]
	mov	x1, 16496
	cmp	w2, 6
	ldr	w3, [x0, 204]
	movk	x1, 0x4, lsl 16
	str	w3, [x19, 4]
	add	x1, x20, x1
	cset	w5, eq
	cmp	w2, 1
	ldr	x3, [x0, 192]
	ccmp	w2, 15, 4, ne
	str	x3, [x19, 8]
	ldr	w3, [x0, 216]
	str	w3, [x19, 24]
	ldr	w6, [x0, 224]
	ldr	w3, [x0, 316]
	mul	w3, w3, w6
	str	w3, [x19, 28]
	ldr	w3, [x1, 24]
	str	w3, [x19, 32]
	ldp	w6, w3, [x1, 24]
	add	w3, w6, w3
	str	w3, [x19, 36]
	ldr	w1, [x1, 36]
	strb	w4, [x19]
	add	w1, w1, 3
	and	w1, w1, -4
	str	w1, [x19, 40]
	ldr	w1, [x20, 48]
	str	w1, [x19, 52]
	str	w5, [x19, 68]
	beq	.L556
	cmp	w2, 6
	beq	.L554
	sub	w1, w2, #2
	cmp	w1, 1
	bhi	.L552
.L554:
	strb	w4, [x19, 1]
	mov	w1, 1
	stp	w2, w1, [x19, 44]
	stp	w1, w1, [x19, 56]
	ldr	w0, [x0, 464]
	str	w0, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L556:
	mov	w2, 0
.L552:
	strb	wzr, [x19, 1]
	mov	w1, 1
	stp	w2, w1, [x19, 44]
	stp	w1, w1, [x19, 56]
	ldr	w0, [x0, 464]
	str	w0, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SetCtrlReg, .-SCDDRV_SetCtrlReg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_RecordStartState
	.type	SCDDRV_RecordStartState, %function
SCDDRV_RecordStartState:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	add	x19, x20, 278528
	mov	w22, w1
	mov	w21, w2
	bl	_mcount
	cmp	w22, w21
	str	w22, [x19, 288]
	str	w21, [x19, 292]
	bls	.L560
	strb	wzr, [x20, 2]
.L559:
	mov	w1, 1
	ldr	x0, .LC126
	str	w1, [x19, 248]
	strb	wzr, [x20, 3]
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 312]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L560:
	mov	w0, 1
	strb	w0, [x20, 2]
	b	.L559
	.size	SCDDRV_RecordStartState, .-SCDDRV_RecordStartState
	.align	3
.LC126:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCD_ConfigReg
	.type	SCD_ConfigReg, %function
SCD_ConfigReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w21, w1
	sxtw	x19, w2
	mov	x22, x3
	bl	_mcount
	ldr	x0, .LC127
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L568
	cmp	w20, 4
	ldr	x22, .LC128
	beq	.L569
.L564:
	add	x19, x22, x19, lsl 2
	mov	w1, w21
	ldr	w0, [x19, 80]
	add	w0, w20, w0
	bl	MEM_WritePhyWord
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L568:
	mov	w3, w21
	mov	w2, w20
	mov	x0, x22
	mov	w1, 1
	bl	VDH_Record_RegData
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L569:
	add	x0, x22, x19, lsl 2
	ldr	w0, [x0, 80]
	add	w0, w0, 4
	cbnz	w21, .L565
	bl	MEM_ReadPhyWord
	uxth	w21, w0
	b	.L564
	.p2align 3
.L565:
	bl	MEM_ReadPhyWord
	orr	w21, w0, 65536
	b	.L564
	.size	SCD_ConfigReg, .-SCD_ConfigReg
	.align	3
.LC127:
	.xword	g_HalDisable
	.align	3
.LC128:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteScdVtrlReg
	.type	WriteScdVtrlReg, %function
WriteScdVtrlReg:
	stp	x29, x30, [sp, -256]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w23, w0
	mov	x0, x30
	mov	x19, x1
	mov	w21, w2
	bl	_mcount
	ldr	x20, .LC129
	ldrb	w0, [x20]
	cmp	w0, 1
	beq	.L571
	ldr	x3, .LC130
	add	x0, x29, 64
	mov	x2, 188
	mov	w1, 0
	mov	x22, x0
	ldr	x3, [x3, 96]
	blr	x3
.L572:
	ldrb	w0, [x20]
	ldr	w1, [x19, 4]
	cmp	w0, 1
	bne	.L597
	ldr	x0, .LC131
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2052
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 24]
	cmp	w0, 1
	bne	.L598
.L575:
	ldr	x0, .LC131
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2056
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 28]
	cmp	w0, 1
	bne	.L599
.L577:
	ldr	x0, .LC131
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2060
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 32]
	cmp	w0, 1
	bne	.L600
.L579:
	ldr	x0, .LC131
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2064
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 36]
	cmp	w0, 1
	bne	.L601
.L581:
	ldr	x0, .LC131
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2068
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldr	w1, [x19, 40]
	cmp	w0, 1
	bne	.L602
.L583:
	ldr	x0, .LC131
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2072
	bl	MEM_WritePhyWord
.L584:
	ldrb	w0, [x19, 1]
	ldrb	w3, [x20]
	ldr	w2, [x19, 44]
	ubfiz	w0, w0, 4, 1
	ldr	w1, [x19, 52]
	cmp	w3, 1
	ldr	w4, [x19, 60]
	and	w2, w2, 15
	lsl	w1, w1, 8
	orr	w0, w0, w2
	orr	w1, w1, w4, lsl 9
	orr	w1, w0, w1
	bne	.L603
	ldr	x0, .LC131
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2080
	bl	MEM_WritePhyWord
	ldr	w0, [x19, 52]
	cbnz	w0, .L604
.L587:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L605
	ldr	x0, .LC131
	mov	w1, 0
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldrb	w24, [x20]
	cmp	w24, 1
	beq	.L591
.L606:
	ldr	w1, [x19, 52]
	add	x0, x29, 64
	strb	w21, [x29, 64]
	strb	w1, [x29, 65]
	stp	wzr, w23, [x29, 68]
	bl	VDH_PostTask
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L597:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2052
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 24]
	cmp	w0, 1
	beq	.L575
.L598:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2056
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 28]
	cmp	w0, 1
	beq	.L577
.L599:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2060
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 32]
	cmp	w0, 1
	beq	.L579
.L600:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2064
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 36]
	cmp	w0, 1
	beq	.L581
.L601:
	mov	w3, w1
	mov	x0, x22
	mov	w1, 1
	mov	w2, 2068
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	ldr	w1, [x19, 40]
	cmp	w0, 1
	beq	.L583
.L602:
	mov	w3, w1
	mov	w2, 2072
	mov	w1, 1
	mov	x0, x22
	bl	VDH_Record_RegData
	b	.L584
	.p2align 3
.L605:
	mov	w3, 0
	mov	w2, 2076
	mov	w1, 1
	mov	x0, x22
	bl	VDH_Record_RegData
	ldrb	w24, [x20]
	cmp	w24, 1
	bne	.L606
.L591:
	ldr	x0, .LC131
	mov	w1, 0
	add	x21, x0, x21, sxtw 2
	ldr	w0, [x21, 80]
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldrb	w1, [x19, 2]
	cmp	w0, 1
	and	w1, w1, 1
	bne	.L607
	ldr	w0, [x21, 80]
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 256
	ret
	.p2align 3
.L603:
	mov	w3, w1
	mov	x0, x22
	mov	w2, 2080
	mov	w1, 1
	bl	VDH_Record_RegData
	ldr	w0, [x19, 52]
	cbz	w0, .L587
.L604:
	ldrb	w0, [x20]
	ldr	w1, [x19, 68]
	cmp	w0, 1
	bne	.L608
	ldr	x0, .LC131
	add	x0, x0, x21, sxtw 2
	ldr	w0, [x0, 80]
	bl	MEM_WritePhyWord
	b	.L587
	.p2align 3
.L571:
	mov	w0, w21
	mov	x22, 0
	bl	ResetSCD
	b	.L572
	.p2align 3
.L608:
	mov	w3, w1
	mov	w2, 0
	mov	w1, 1
	mov	x0, x22
	bl	VDH_Record_RegData
	b	.L587
	.p2align 3
.L607:
	mov	w3, w1
	mov	x0, x22
	mov	w1, w24
	mov	w2, 2048
	bl	VDH_Record_RegData
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 256
	ret
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	3
.LC129:
	.xword	g_HalDisable
	.align	3
.LC130:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC131:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteScdMsg
	.type	WriteScdMsg, %function
WriteScdMsg:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	mov	w21, w1
	mov	x22, x2
	mov	x19, x3
	mov	w23, w4
	str	w5, [x29, 100]
	str	x2, [x29, 104]
	bl	_mcount
	add	x1, x29, 112
	mov	x0, x22
	stp	xzr, xzr, [x29, 112]
	stp	xzr, xzr, [x29, 128]
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	bl	GetFirstRawPacket
	ldr	w3, [x29, 124]
	cmp	w3, w21
	mov	w27, w3
	bgt	.L610
	ldr	x24, .LC132
	add	x28, x22, 98304
	mov	w26, 0
	mov	w25, 0
	mov	w22, 1023
	.p2align 2
.L613:
	cmp	w3, wzr
	add	x1, x19, x26, sxtw 2
	add	w25, w25, 1
	ble	.L611
	ldr	w0, [x29, 116]
	str	w0, [x19, w26, sxtw 2]
	add	w26, w26, 3
	sub	w0, w0, #1
	add	w0, w0, w3
	add	w2, w23, w26, lsl 2
	stp	w0, w2, [x1, 4]
.L611:
	str	w27, [x20, 4]
	ldr	w5, [x28, 16]
	cmp	w5, 1023
	bls	.L627
.L612:
	ldr	w0, [x29, 100]
	cbz	w0, .L628
.L614:
	cbz	w25, .L618
	cmp	w26, wzr
	ble	.L617
	add	x19, x19, x26, sxtw 2
	str	wzr, [x19, -4]
.L617:
	mov	w0, 1
	str	w25, [x20]
	str	w0, [x20, 8]
	mov	w0, 0
.L625:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L627:
	sxtw	x7, w5
	ldr	x4, [x29, 104]
	lsl	x1, x7, 2
	mov	x2, 96
	sub	x1, x1, x7
	ldr	w7, [x28, 4]
	add	x0, x29, 112
	cmp	w5, w7
	add	x1, x4, x1, lsl 5
	beq	.L612
	ldr	x3, [x24, 104]
	blr	x3
	ldr	w0, [x28, 16]
	ldr	w3, [x29, 124]
	add	w0, w0, 1
	asr	w1, w0, 31
	add	w27, w27, w3
	lsr	w1, w1, 22
	cmp	w21, w27
	add	w0, w0, w1
	ccmp	w25, w22, 0, ge
	and	w0, w0, 1023
	sub	w0, w0, w1
	str	w0, [x28, 16]
	ble	.L613
	ldr	w0, [x29, 100]
	cbnz	w0, .L614
.L628:
	ldr	w0, [x20, 4]
	sub	w1, w21, #16
	cmp	w0, w1
	bge	.L614
.L619:
	mov	w1, 1023
	cmp	w21, w27
	ccmp	w25, w1, 0, lt
	bgt	.L614
	sub	w0, w21, w0
	cmp	w3, w0
	blt	.L614
	add	x2, x19, x26, sxtw 2
	ldr	w1, [x29, 116]
	str	w1, [x19, w26, sxtw 2]
	add	w26, w26, 3
	sub	w1, w1, #1
	add	w25, w25, 1
	add	w1, w1, w0
	add	w23, w23, w26, lsl 2
	stp	w1, w23, [x2, 4]
	ldr	w1, [x20, 4]
	add	w0, w1, w0
	str	w0, [x20, 4]
	b	.L614
.L610:
	ldr	w0, [x29, 100]
	cbnz	w0, .L618
	ldr	w0, [x20, 4]
	sub	w1, w21, #16
	cmp	w0, w1
	bge	.L618
	mov	w26, 0
	mov	w25, 0
	b	.L619
.L618:
	mov	w0, -6
	b	.L625
	.size	WriteScdMsg, .-WriteScdMsg
	.align	3
.LC132:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_StartSCD
	.type	SCDDRV_StartSCD, %function
SCDDRV_StartSCD:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x23, x0
	mov	x0, x30
	mov	x21, x1
	mov	w25, w2
	mov	w22, w3
	bl	_mcount
	ldr	x24, .LC133
	add	x19, x21, 278528
	add	x20, x19, 168
	mov	x2, 12
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x24, 96]
	ldr	w27, [x19, 204]
	ldr	x26, [x19, 192]
	blr	x3
	ldr	w5, [x23, 52]
	mov	x0, x20
	mov	w6, w22
	mov	w4, w27
	mov	x3, x26
	add	x2, x21, 88
	mov	w1, w25
	bl	WriteScdMsg
	mov	w20, w0
	cbnz	w0, .L630
	ldr	x0, [x24]
	blr	x0
	sxtw	x3, w22
	ldr	x4, .LC134
	lsl	x1, x3, 4
	mov	w2, w22
	sub	x3, x1, x3
	mov	x1, x23
	add	x3, x4, x3, lsl 2
	str	w0, [x3, 48]
	ldr	w0, [x19, 240]
	bl	WriteScdVtrlReg
.L630:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	SCDDRV_StartSCD, .-SCDDRV_StartSCD
	.align	3
.LC133:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC134:
	.xword	g_VfmwGlobalStat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CutStreamWithSCD
	.type	CutStreamWithSCD, %function
CutStreamWithSCD:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	str	wzr, [x29, 68]
	add	x1, x20, 98304
	add	x4, x29, 64
	add	x3, x29, 68
	add	x2, x29, 60
	add	x1, x1, 112
	add	x0, x20, 88
	stp	wzr, wzr, [x29, 60]
	bl	SCDDRV_CheckConditionOfStartSCD
	mov	w19, w0
	cbnz	w0, .L638
	add	x21, x20, 278528
	mov	w1, w22
	ldr	w0, [x21, 240]
	bl	SM_CfgBuf
	mov	w19, w0
	cbnz	w0, .L639
	ldr	w3, [x21, 316]
	mov	x0, x20
	ldr	w2, [x29, 64]
	add	x1, x29, 72
	str	w2, [x21, 224]
	mul	w2, w2, w3
	lsl	w2, w2, 2
	str	w2, [x21, 220]
	bl	SCDDRV_SetCtrlReg
	ldr	w2, [x29, 68]
	mov	w3, w22
	mov	x1, x20
	add	x0, x29, 72
	bl	SCDDRV_StartSCD
	mov	w19, w0
	cbnz	w0, .L633
	ldr	w1, [x29, 60]
	ldr	w0, [x29, 68]
	str	w1, [x21, 288]
	cmp	w1, w0
	str	w0, [x21, 292]
	bls	.L640
	strb	wzr, [x20, 2]
.L636:
	mov	w1, 1
	ldr	x0, .LC139
	str	w1, [x21, 248]
	mov	w19, 0
	strb	wzr, [x20, 3]
	ldr	x0, [x0]
	blr	x0
	str	w0, [x21, 312]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L639:
	ldr	x1, .LC138
	mov	w2, w0
	mov	w0, 26
	bl	dprint_vfmw
.L633:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L638:
	ldr	x1, .LC136
	mov	w2, w0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L640:
	mov	w0, 1
	strb	w0, [x20, 2]
	b	.L636
	.size	CutStreamWithSCD, .-CutStreamWithSCD
	.align	3
.LC136:
	.xword	.LC135
	.align	3
.LC138:
	.xword	.LC137
	.align	3
.LC139:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReadScdStateReg
	.type	ReadScdStateReg, %function
ReadScdStateReg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x1, .LC140
	add	x19, x1, x19, sxtw 2
	ldr	w0, [x19, 80]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	and	w0, w0, 1
	str	w0, [x20]
	ldr	w0, [x19, 80]
	add	w0, w0, 2116
	bl	MEM_ReadPhyWord
	and	w0, w0, 1
	ldr	w1, [x19, 80]
	str	w0, [x20, 4]
	add	w0, w1, 2124
	bl	MEM_ReadPhyWord
	lsr	w0, w0, 22
	ldr	w1, [x19, 80]
	str	w0, [x20, 8]
	add	w0, w1, 2124
	bl	MEM_ReadPhyWord
	and	w0, w0, 4194303
	ldr	w1, [x19, 80]
	str	w0, [x20, 12]
	add	w0, w1, 2128
	bl	MEM_ReadPhyWord
	str	w0, [x20, 16]
	ldr	w1, [x19, 80]
	add	w0, w1, 2132
	bl	MEM_ReadPhyWord
	str	w0, [x20, 20]
	ldr	w1, [x19, 80]
	add	w0, w1, 2060
	bl	MEM_ReadPhyWord
	str	w0, [x20, 24]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ReadScdStateReg, .-ReadScdStateReg
	.align	3
.LC140:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ParseMpeg4UniqueUpMsg
	.type	ParseMpeg4UniqueUpMsg, %function
ParseMpeg4UniqueUpMsg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x19, x1
	mov	x20, x2
	bl	_mcount
	cmp	w21, 1
	ldrb	w0, [x19]
	beq	.L645
	orr	w0, w0, 1
	strb	w0, [x19]
.L644:
	ldr	w1, [x20]
	ldrb	w0, [x19]
	lsr	w1, w1, 31
	bfi	w0, w1, 1, 1
	strb	w0, [x19]
	ldrh	w1, [x20, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x19]
	ldr	w1, [x20, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x19]
	ldr	w0, [x20, 8]
	ldrh	w1, [x19]
	and	w0, w0, 7
	bfi	w1, w0, 7, 4
	strh	w1, [x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L645:
	and	w0, w0, -2
	strb	w0, [x19]
	b	.L644
	.size	ParseMpeg4UniqueUpMsg, .-ParseMpeg4UniqueUpMsg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ConvertByteOrder
	.type	ConvertByteOrder, %function
ConvertByteOrder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x19, [sp, 16]
	rev	w0, w0
	ldp	x29, x30, [sp], 32
	ret
	.size	ConvertByteOrder, .-ConvertByteOrder
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CheckSegValid
	.type	CheckSegValid, %function
CheckSegValid:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cbz	x20, .L652
	ldr	w0, [x20, 16]
	cbz	w0, .L654
	ldr	x0, [x20]
	cbz	x0, .L654
	cbz	x19, .L655
	add	x1, x19, 180224
	ldp	w2, w0, [x1, 32]
	cmp	w0, w2
	sub	w2, w2, #1
	bhi	.L657
	sub	w0, w2, w0
	bcc	.L649
	ldr	w0, [x1, 28]
	sub	w0, w0, #1
.L649:
	ldr	w2, [x20, 20]
	mov	w1, -7
	cmp	w2, w0
	csel	w0, wzr, w1, ls
.L648:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L657:
	ldr	w1, [x1, 28]
	add	w2, w2, w1
	sub	w0, w2, w0
	b	.L649
	.p2align 3
.L655:
	mov	w0, 0
	b	.L649
	.p2align 3
.L654:
	mov	w0, -7
	b	.L648
.L652:
	mov	w0, -1
	b	.L648
	.size	CheckSegValid, .-CheckSegValid
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetSegPts
	.type	GetSegPts, %function
GetSegPts:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x3
	mov	x21, x2
	mov	w23, w1
	mov	w22, w4
	bl	_mcount
	add	x4, x29, 80
	add	x2, x29, 68
	mov	w1, w23
	add	x3, x29, 72
	mov	x0, x20
	str	wzr, [x4, -4]!
	stp	wzr, wzr, [x29, 68]
	bl	GetRawNumOffset
	ldr	w1, [x29, 76]
	lsl	x0, x1, 2
	sub	x0, x0, x1
	add	x0, x20, x0, lsl 5
	ldr	x1, [x0, 64]
	str	x1, [x19, 32]
	ldr	x2, [x0, 48]
	str	x2, [x19, 48]
	ldr	x2, [x0, 64]
	str	x2, [x19, 40]
	ldr	x2, [x0, 56]
	str	x2, [x19, 56]
	ldr	w2, [x0, 24]
	str	w2, [x19, 64]
	ldr	w2, [x0, 28]
	str	w2, [x19, 68]
	ldr	w2, [x0, 32]
	str	w2, [x19, 72]
	ldr	w2, [x0, 36]
	str	w2, [x19, 76]
	ldrb	w0, [x0, 92]
	strb	w0, [x19, 11]
	ldr	x0, [x21]
	cmp	x1, x0
	beq	.L661
.L659:
	str	x1, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L661:
	ldr	x0, .LC141
	ldr	x0, [x0, w22, sxtw 3]
	add	x0, x0, 311296
	ldr	w0, [x0, 1604]
	cbnz	w0, .L659
	mov	x0, -1
	str	x0, [x19, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	GetSegPts, .-GetSegPts
	.align	3
.LC141:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	IsVopHeader
	.type	IsVopHeader, %function
IsVopHeader:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 1
	beq	.L667
	cmp	w19, 2
	mov	w0, 0
	beq	.L668
	mov	w1, -33488896
	cmp	w20, w1
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L667:
	mov	w0, -1241448448
	mov	w1, -33488896
	cmp	w20, w0
	cset	w0, eq
	cmp	w20, w1
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L668:
	ubfx	x0, x20, 16, 8
	mov	w1, -33488896
	sub	w0, w0, #128
	cmp	w0, 3
	cset	w0, ls
	cmp	w20, w1
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	IsVopHeader, .-IsVopHeader
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CorrectSegPhyAddr
	.type	CorrectSegPhyAddr, %function
CorrectSegPhyAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, w20
	orr	w0, w19, -2147483648
	csel	w0, w0, w19, cc
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CorrectSegPhyAddr, .-CorrectSegPhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetNextVop
	.type	GetNextVop, %function
GetNextVop:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x21, x0
	mov	x0, x30
	mov	w19, w2
	mov	x20, x1
	bl	_mcount
	add	x2, x21, 98304
	adds	x3, x2, 112
	beq	.L682
	add	x3, x3, 180224
	mov	w0, 2048
	ldp	w10, w1, [x3, 8]
	sub	w10, w1, w10
	and	w10, w10, 2047
	sub	w10, w0, w10
.L673:
	sub	w3, w19, #1
	mov	w5, w3
	tbnz	w3, #31, .L683
	add	x21, x21, 278528
	add	x0, x2, 112
	add	x0, x0, 180224
	mov	w9, -33488896
	mov	w11, -1241448448
	ldr	x1, [x2, 112]
	ldr	w8, [x21, 316]
	ldr	w6, [x0, 24]
	ldr	w7, [x21, 260]
	mul	w4, w3, w8
	b	.L681
	.p2align 3
.L676:
	cmp	w7, 2
	beq	.L685
	cmp	w0, w9
	beq	.L679
.L680:
	sub	w5, w5, #1
	mov	w19, w3
	cmn	w5, #1
	sub	w4, w4, w8
	beq	.L683
.L686:
	sub	w3, w3, #1
.L681:
	ldr	w0, [x20, w4, uxtw 2]
	and	w0, w0, 2147483647
	cmp	w0, w6
	orr	w2, w0, -2147483648
	csel	w0, w2, w0, cc
	cmp	w7, 1
	sub	w0, w0, w6
	ldr	w0, [x1, x0]
	bne	.L676
	cmp	w0, w11
	cset	w2, eq
.L677:
	cmp	w0, w9
	beq	.L679
	cbz	w2, .L680
	.p2align 2
.L679:
	cmp	w3, w10
	mov	w19, w3
	bls	.L683
	sub	w5, w5, #1
	sub	w3, w3, #1
	cmn	w5, #1
	mov	w19, w3
	sub	w4, w4, w8
	bne	.L686
.L683:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L685:
	ubfx	x2, x0, 16, 8
	sub	w2, w2, #128
	cmp	w2, 3
	cset	w2, ls
	b	.L677
.L682:
	mov	w10, 2048
	b	.L673
	.size	GetNextVop, .-GetNextVop
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetPushRawOverState
	.type	SetPushRawOverState, %function
SetPushRawOverState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	w0, [x19, 8]
	str	w20, [x19, 8]
	cmp	w0, 3
	mov	w0, -7
	ccmp	w20, 2, 0, eq
	beq	.L689
	mov	w0, 0
.L689:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SetPushRawOverState, .-SetPushRawOverState
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessExceptionalStartCodeNum
	.type	ProcessExceptionalStartCodeNum, %function
ProcessExceptionalStartCodeNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	x1, .LC143
	mov	w3, w20
	mov	w2, 2352
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, 1
	add	x0, x19, 88
	bl	DeleteRawPacket
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ProcessExceptionalStartCodeNum, .-ProcessExceptionalStartCodeNum
	.align	3
.LC143:
	.xword	.LC142
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetValidStartCodeNum
	.type	GetValidStartCodeNum, %function
GetValidStartCodeNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	ldr	w2, [x19, 24]
	ldr	w0, [x19, 12]
	udiv	w1, w2, w20
	ldp	x19, x20, [sp, 16]
	cmp	w1, w0
	csel	w0, w1, w0, ls
	ldp	x29, x30, [sp], 32
	ret
	.size	GetValidStartCodeNum, .-GetValidStartCodeNum
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessNoSeg
	.type	ProcessNoSeg, %function
ProcessNoSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	add	x0, x19, 278528
	ldr	w1, [x0, 292]
	ldr	w2, [x0, 288]
	ldr	w20, [x0, 172]
	cmp	w2, w1
	cset	w1, gt
	strb	w1, [x19]
	cbnz	w21, .L693
	sub	w1, w20, #3
	cmp	w20, 4
	csel	w1, w1, wzr, cs
.L694:
	add	x0, x19, 88
	bl	DeleteRawLen
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L693:
	ldr	w1, [x0, 140]
	ldr	x2, [x0, 208]
	lsl	w0, w1, 2
	sub	w0, w0, w1
	ldr	w1, [x2, 4]
	cmp	w0, wzr
	add	w2, w0, 3
	csel	w0, w2, w0, lt
	and	w1, w1, 2147483647
	sub	w2, w20, w1
	cmp	w2, w0, asr 2
	bls	.L694
	ldr	x1, .LC145
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, w20
	add	x0, x19, 88
	bl	DeleteRawLen
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	ProcessNoSeg, .-ProcessNoSeg
	.align	3
.LC145:
	.xword	.LC144
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessNotMpeg4ScdUpMsg
	.type	ProcessNotMpeg4ScdUpMsg, %function
ProcessNotMpeg4ScdUpMsg:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x27, x0
	mov	x0, x30
	mov	w25, w1
	str	w2, [x29, 104]
	bl	_mcount
	add	x19, x27, 278528
	add	x0, x29, 136
	add	x20, x27, 98304
	add	x20, x20, 112
	mov	w26, 1
	ldr	w23, [x19, 316]
	mov	x24, x20
	stp	xzr, xzr, [x0]
	add	x0, x29, 152
	add	x21, x20, 180224
	ldr	x28, [x19, 208]
	str	xzr, [x29, 216]
	stp	xzr, xzr, [x0]
	add	x0, x29, 168
	stp	xzr, xzr, [x0]
	add	x0, x29, 184
	stp	xzr, xzr, [x0]
	add	x0, x29, 200
	stp	xzr, xzr, [x0]
	add	x0, x27, 88
	mov	w27, 0
	str	x0, [x29, 112]
	sub	w0, w23, #1
	str	w0, [x29, 124]
	b	.L697
	.p2align 3
.L714:
	ldr	x4, [x24]
	sub	w3, w3, w0
	sub	w1, w0, w1
	mov	w2, 1
	add	x1, x4, x1
	strb	w2, [x29, 145]
	cmp	w3, 3
	str	x1, [x29, 136]
	stp	w0, w3, [x29, 152]
	ble	.L713
	mov	x1, x20
	add	x0, x29, 136
	bl	CheckSegValid
	cbnz	w0, .L706
	ldr	w1, [x28, w26, uxtw 2]
	add	x2, x19, 280
	ldr	x0, [x29, 112]
	add	x3, x29, 136
	ldr	w4, [x19, 240]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 136
	mov	x0, x20
	bl	InsertStreamSeg
	cbnz	w0, .L706
.L702:
	add	w26, w26, w23
	mov	w27, w22
.L697:
	cmp	w27, w25
	beq	.L706
	ldr	w1, [x29, 124]
	sub	w0, w26, #1
	add	w22, w27, 1
	add	w2, w1, w26
	ldr	w1, [x21, 24]
	ldr	w0, [x28, w0, uxtw 2]
	ldr	w3, [x28, w2, uxtw 2]
	and	w0, w0, 2147483647
	orr	w2, w0, -2147483648
	cmp	w1, w0
	and	w3, w3, 2147483647
	csel	w0, w2, w0, hi
	cmp	w1, w3
	orr	w2, w3, -2147483648
	csel	w3, w2, w3, hi
	cmp	w0, w3
	bls	.L714
	ldr	w2, [x29, 104]
	sub	w5, w3, w1
	sub	w2, w2, w0
	add	w3, w2, w5
	cbz	x20, .L707
	ldr	x4, [x24]
	sub	w1, w0, w1
	stp	w0, w3, [x29, 152]
	add	x1, x4, x1
	cmp	w3, 3
	str	x1, [x29, 136]
	ldp	w1, w0, [x21, 8]
	ble	.L711
	sub	w0, w0, w1
	mov	w1, 2048
	and	w0, w0, 2047
	sub	w0, w1, w0
	cmp	w0, 2
	bls	.L706
.L712:
	mov	x1, x20
	add	x0, x29, 136
	str	w5, [x29, 108]
	str	w2, [x29, 120]
	bl	CheckSegValid
	cbnz	w0, .L706
	ldr	w5, [x29, 108]
	ldr	w2, [x29, 120]
	cbnz	w5, .L709
	str	w2, [x29, 156]
	mov	w0, 1
	strb	w0, [x29, 145]
	add	x2, x19, 280
	ldr	x0, [x29, 112]
	add	x3, x29, 136
	ldr	w1, [x28, w26, uxtw 2]
	ldr	w4, [x19, 240]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 136
	mov	x0, x20
	bl	InsertStreamSeg
	b	.L702
	.p2align 3
.L709:
	str	w2, [x29, 156]
	add	x3, x29, 136
	strb	wzr, [x29, 145]
	add	x2, x19, 280
	ldr	w4, [x19, 240]
	ldr	w1, [x28, w26, uxtw 2]
	ldr	x0, [x29, 112]
	and	w1, w1, 2147483647
	str	w5, [x29, 120]
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 136
	mov	x0, x20
	bl	InsertStreamSeg
	ldr	w7, [x21, 24]
	mov	w3, 1
	ldr	w5, [x29, 120]
	add	x1, x29, 136
	ldr	x4, [x24]
	mov	x0, x20
	ldr	w2, [x19, 240]
	strb	w3, [x29, 145]
	str	x4, [x29, 136]
	stp	w7, w5, [x29, 152]
	bl	InsertStreamSeg
	b	.L702
	.p2align 3
.L707:
	sub	w1, w0, w1
	cmp	w3, 3
	stp	w0, w3, [x29, 152]
	ldr	x0, [x24]
	add	x1, x0, x1
	str	x1, [x29, 136]
	bgt	.L712
	.p2align 2
.L711:
	ldr	x1, .LC147
	mov	w2, 2452
	mov	w0, 0
	bl	dprint_vfmw
	b	.L702
	.p2align 3
.L713:
	ldr	x1, .LC147
	mov	w2, 2421
	mov	w0, 0
	bl	dprint_vfmw
	b	.L702
	.p2align 3
.L706:
	cmp	w27, wzr
	ble	.L696
	mul	w1, w23, w27
	ldr	x0, [x29, 112]
	add	w1, w1, 1
	ldr	w1, [x28, w1, uxtw 2]
	and	w1, w1, 2147483647
	bl	DeleteRawLen
.L696:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
	.size	ProcessNotMpeg4ScdUpMsg, .-ProcessNotMpeg4ScdUpMsg
	.align	3
.LC147:
	.xword	.LC146
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetMpeg4ModeFlag
	.type	GetMpeg4ModeFlag, %function
GetMpeg4ModeFlag:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	add	x27, x0, 278528
	mov	w19, w1
	mov	x0, x30
	mov	w25, 0
	mov	w26, 0
	bl	_mcount
	ldr	w20, [x27, 316]
	ldr	x28, [x27, 208]
	cbz	w19, .L715
	ldr	x24, .LC151
	mov	w21, 288
	mov	w23, 2
	mov	w22, 1
	b	.L730
	.p2align 3
.L736:
	cmp	w1, 32768
	str	w22, [x27, 260]
	str	wzr, [x27, 264]
	beq	.L734
.L722:
	add	w26, w26, 1
	add	w25, w25, w20
	cmp	w26, w19
	beq	.L715
.L730:
	ldr	w1, [x28, w25, uxtw 2]
	ldr	w2, [x27, 136]
	and	w1, w1, 2147483647
	orr	w0, w1, -2147483648
	cmp	w2, w1
	csel	w0, w0, w1, hi
	bl	MEM_Phy2Vir
	cbz	x0, .L735
	ldr	w1, [x0]
	rev	w1, w1
	cmp	w1, 438
	ccmp	w1, w21, 4, ne
	and	w1, w1, -1024
	beq	.L736
	cmp	w1, 32768
	bne	.L722
	ldr	w0, [x27, 260]
	cmp	w0, 1
	beq	.L737
.L724:
	str	w23, [x27, 260]
.L738:
	add	w26, w26, 1
	add	w25, w25, w20
	cmp	w26, w19
	bne	.L730
.L715:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L734:
	str	w22, [x27, 264]
	b	.L722
	.p2align 3
.L735:
	ldr	x2, .LC148
	mov	w3, 2507
	ldr	x1, .LC150
	mov	w0, 1
	add	x2, x2, 96
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L737:
	ldr	w0, [x27, 264]
	add	w0, w0, 1
	str	w0, [x27, 264]
	cmp	w0, 30
	bls	.L722
	ldr	x4, [x24]
	cbz	x4, .L724
	ldr	w0, [x27, 240]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	str	w23, [x27, 260]
	b	.L738
	.size	GetMpeg4ModeFlag, .-GetMpeg4ModeFlag
	.align	3
.LC148:
	.xword	.LANCHOR3
	.align	3
.LC150:
	.xword	.LC149
	.align	3
.LC151:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessMpeg4ScdUpMsg
	.type	ProcessMpeg4ScdUpMsg, %function
ProcessMpeg4ScdUpMsg:
	stp	x29, x30, [sp, -320]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 278528
	mov	w25, w2
	stp	w1, w2, [x29, 108]
	mov	w23, w1
	bl	_mcount
	ldr	w1, [x19, 316]
	add	x20, x21, 98304
	ldr	w0, [x19, 136]
	add	x20, x20, 112
	mov	w24, w1
	add	x1, x29, 232
	ldr	x28, [x19, 208]
	mov	w27, 0
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x1]
	add	x1, x29, 248
	str	w24, [x29, 132]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x1]
	add	x1, x29, 264
	str	xzr, [x29, 224]
	stp	xzr, xzr, [x29, 192]
	stp	xzr, xzr, [x29, 208]
	stp	xzr, xzr, [x1]
	add	x1, x29, 280
	str	xzr, [x29, 312]
	mov	x26, x20
	stp	xzr, xzr, [x1]
	add	x1, x29, 296
	stp	xzr, xzr, [x1]
	bl	MEM_Phy2Vir
	mov	x22, x0
	add	x1, x21, 88
	mov	w0, w25
	str	x1, [x29, 120]
	mov	w25, 1
	bl	MEM_Phy2Vir
	ldr	x3, .LC152
	mov	x1, x22
	mov	x2, 4
	add	x22, x20, 180224
	ldr	x3, [x3, 104]
	blr	x3
	mov	w1, w23
	mov	x0, x21
	bl	GetMpeg4ModeFlag
	mov	w2, w23
	mov	x1, x28
	mov	x0, x21
	bl	GetNextVop
	str	w0, [x29, 140]
	sub	w0, w24, #1
	str	w0, [x29, 136]
	b	.L740
	.p2align 3
.L777:
	ldr	w0, [x29, 248]
	cbz	w0, .L744
	ldr	w2, [x29, 252]
	mov	x1, x20
	add	x0, x29, 232
	add	w3, w2, w3
	str	w3, [x29, 252]
	bl	CheckSegValid
	cbnz	w0, .L748
	ldr	w2, [x19, 240]
	add	x1, x29, 232
	mov	x0, x20
	bl	InsertStreamSeg
	mov	w23, w0
	ldr	x0, .LC152
	mov	x2, 88
	mov	w1, 0
	ldr	x4, [x0, 96]
	add	x0, x29, 232
	blr	x4
	cbnz	w23, .L748
.L749:
	ldr	w0, [x29, 132]
	mov	w27, w21
	add	w25, w25, w0
.L740:
	ldr	w0, [x29, 140]
	cmp	w27, w0
	beq	.L748
	ldr	w0, [x29, 136]
	sub	w23, w25, #1
	ldr	w4, [x22, 24]
	add	w21, w27, 1
	add	w0, w0, w25
	add	x24, x28, x23, uxtw 2
	ldr	w2, [x28, w23, uxtw 2]
	ldr	w0, [x28, w0, uxtw 2]
	and	w2, w2, 2147483647
	orr	w1, w2, -2147483648
	cmp	w4, w2
	and	w0, w0, 2147483647
	csel	w2, w1, w2, hi
	cmp	w4, w0
	orr	w1, w0, -2147483648
	csel	w0, w1, w0, hi
	sub	w3, w0, w2
	cmp	w3, 3
	bgt	.L777
	sub	w1, w3, #1
	cmp	w1, 2
	bls	.L778
	ldr	w1, [x29, 112]
	sub	w10, w0, w4
	sub	w11, w1, w2
	add	w3, w11, w10
	cbz	x20, .L758
	ldr	x0, [x26]
	sub	w4, w2, w4
	cmp	w3, 3
	ldr	w1, [x22, 8]
	add	x4, x0, x4
	str	x4, [x29, 144]
	stp	w2, w3, [x29, 160]
	ldr	w0, [x22, 12]
	ble	.L767
	sub	w0, w0, w1
	mov	w1, 2048
	and	w0, w0, 2047
	sub	w0, w1, w0
	cmp	w0, 2
	bls	.L748
.L768:
	mov	x1, x20
	add	x0, x29, 144
	str	w10, [x29, 116]
	str	w11, [x29, 128]
	bl	CheckSegValid
	cbnz	w0, .L748
	ldr	w10, [x29, 116]
	ldr	w0, [x19, 260]
	ldr	w11, [x29, 128]
	cmp	w0, 1
	ldrb	w0, [x29, 224]
	cbnz	w10, .L760
	beq	.L779
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L762:
	ldr	w1, [x28, w23, uxtw 2]
	mov	w2, 1
	ldrb	w0, [x29, 224]
	add	x3, x29, 144
	lsr	w1, w1, 31
	ldr	w4, [x19, 240]
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 224]
	ldrh	w1, [x24, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x29, 224]
	ldr	w1, [x24, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 224]
	ldr	w0, [x24, 8]
	ldrh	w1, [x29, 224]
	and	w0, w0, 7
	strb	w2, [x29, 153]
	bfi	w1, w0, 7, 4
	str	w11, [x29, 164]
	strh	w1, [x29, 224]
	add	x2, x19, 280
	ldr	x0, [x29, 120]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 144
	mov	x0, x20
	bl	InsertStreamSeg
	b	.L749
	.p2align 3
.L744:
	ldr	x10, [x26]
	sub	w4, w2, w4
	mov	x1, x20
	add	x0, x29, 144
	add	x4, x10, x4
	mov	w10, 1
	str	x4, [x29, 144]
	strb	w10, [x29, 153]
	stp	w2, w3, [x29, 160]
	bl	CheckSegValid
	cbnz	w0, .L748
	ldr	w0, [x19, 260]
	cmp	w0, 1
	ldrb	w0, [x29, 224]
	beq	.L780
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L751:
	ldr	w3, [x28, w23, uxtw 2]
	add	x2, x19, 280
	ldrb	w1, [x29, 224]
	lsr	w3, w3, 31
	ldr	w4, [x19, 240]
	bfi	w1, w3, 1, 1
	strb	w1, [x29, 224]
	ldr	x0, [x29, 120]
	add	x3, x29, 144
	ldrh	w9, [x24, 10]
	bfi	w1, w9, 2, 1
	strb	w1, [x29, 224]
	ldr	w9, [x24, 8]
	ubfx	x9, x9, 4, 3
	bfi	w1, w9, 3, 4
	strb	w1, [x29, 224]
	ldr	w1, [x24, 8]
	ldrh	w8, [x29, 224]
	and	w1, w1, 7
	bfi	w8, w1, 7, 4
	strh	w8, [x29, 224]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 144
	mov	x0, x20
	bl	InsertStreamSeg
	cbz	w0, .L749
	.p2align 2
.L748:
	cmp	w27, wzr
	ble	.L781
	ldr	w0, [x29, 132]
	mul	w1, w0, w27
	ldr	x0, [x29, 120]
	add	w1, w1, 1
	ldr	w1, [x28, w1, uxtw 2]
	and	w1, w1, 2147483647
	bl	DeleteRawLen
.L739:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L778:
	str	w3, [x29, 116]
	str	w2, [x29, 128]
	bl	MEM_Phy2Vir
	ldr	w3, [x29, 116]
	ldr	w2, [x29, 128]
	cbz	x0, .L782
	ldr	w0, [x0]
	and	w0, w0, 16777215
	cmp	w0, 65536
	beq	.L749
	ldr	w0, [x19, 260]
	cmp	w0, 1
	ldrb	w0, [x29, 312]
	beq	.L783
	orr	w0, w0, 1
	strb	w0, [x29, 312]
.L757:
	ldr	w1, [x28, w23, uxtw 2]
	ldrb	w0, [x29, 312]
	lsr	w1, w1, 31
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 312]
	ldr	w1, [x22, 24]
	ldrh	w4, [x24, 10]
	sub	w1, w2, w1
	bfi	w0, w4, 2, 1
	ldr	x4, [x26]
	strb	w0, [x29, 312]
	add	x1, x4, x1
	str	x1, [x29, 232]
	ldr	w1, [x24, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 312]
	ldr	w0, [x24, 8]
	ldrh	w1, [x29, 312]
	and	w0, w0, 7
	stp	w2, w3, [x29, 248]
	bfi	w1, w0, 7, 4
	mov	w2, 1
	strh	w1, [x29, 312]
	add	x3, x29, 232
	strb	w2, [x29, 241]
	add	x2, x19, 280
	ldr	w4, [x19, 240]
	ldr	w1, [x28, w25, uxtw 2]
	ldr	x0, [x29, 120]
	and	w1, w1, 2147483647
	bl	GetSegPts
	b	.L749
	.p2align 3
.L760:
	beq	.L784
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L764:
	ldr	w1, [x28, w23, uxtw 2]
	add	x3, x29, 144
	ldrb	w0, [x29, 224]
	add	x2, x19, 280
	lsr	w1, w1, 31
	ldr	w4, [x19, 240]
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 224]
	str	w10, [x29, 128]
	ldrh	w1, [x24, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x29, 224]
	ldr	w1, [x24, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 224]
	ldr	w0, [x24, 8]
	ldrh	w1, [x29, 224]
	and	w0, w0, 7
	str	w11, [x29, 164]
	strb	wzr, [x29, 153]
	bfi	w1, w0, 7, 4
	strh	w1, [x29, 224]
	ldr	x0, [x29, 120]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 2147483647
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 144
	mov	x0, x20
	bl	InsertStreamSeg
	ldr	w3, [x22, 24]
	add	x1, x29, 144
	ldr	w10, [x29, 128]
	mov	x0, x20
	ldr	x4, [x26]
	ldr	w2, [x19, 240]
	stp	w3, w10, [x29, 160]
	mov	w3, 1
	str	x4, [x29, 144]
	strb	w3, [x29, 153]
	bl	InsertStreamSeg
	b	.L749
	.p2align 3
.L758:
	ldr	x0, [x26]
	sub	w4, w2, w4
	cmp	w3, 3
	add	x4, x0, x4
	str	x4, [x29, 144]
	stp	w2, w3, [x29, 160]
	bgt	.L768
	.p2align 2
.L767:
	ldr	x1, .LC156
	mov	w2, 2643
	mov	w0, 0
	bl	dprint_vfmw
	b	.L749
	.p2align 3
.L780:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L751
	.p2align 3
.L779:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L762
	.p2align 3
.L784:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L764
	.p2align 3
.L783:
	and	w0, w0, -2
	strb	w0, [x29, 312]
	b	.L757
	.p2align 3
.L781:
	ldr	w0, [x29, 108]
	cmp	w0, 2048
	ldr	w0, [x29, 140]
	ccmp	w0, wzr, 0, hi
	bne	.L739
	ldr	w2, [x29, 108]
	mov	w0, 0
	ldr	x1, .LC158
	bl	dprint_vfmw
	ldr	x0, [x29, 120]
	mov	w1, 1
	bl	DeleteRawPacket
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
.L782:
	ldr	x2, .LC153
	mov	w3, 2615
	ldr	x1, .LC155
	mov	w0, 1
	add	x2, x2, 120
	bl	dprint_vfmw
	b	.L739
	.size	ProcessMpeg4ScdUpMsg, .-ProcessMpeg4ScdUpMsg
	.align	3
.LC152:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC153:
	.xword	.LANCHOR3
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC156:
	.xword	.LC146
	.align	3
.LC158:
	.xword	.LC157
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ProcessScdReturn.part.9, %function
ProcessScdReturn.part.9:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x0, x29, 32
	mov	w1, w20
	bl	ReadScdStateReg
	mov	w0, 34464
	ldr	w2, [x29, 44]
	movk	w0, 0x1, lsl 16
	cmp	w2, w0
	bls	.L786
	ldr	w0, [x19, 20]
	cbz	w0, .L790
.L786:
	add	x1, x19, 278528
	ldr	w0, [x29, 56]
	ldr	w1, [x1, 316]
	udiv	w0, w0, w1
	cmp	w0, w2
	csel	w1, w0, w2, ls
	cmp	w1, 1
	bls	.L791
	ldr	w0, [x19, 20]
	sub	w1, w1, #1
	strb	wzr, [x19]
	cmp	w0, 2
	ldr	w2, [x29, 48]
	mov	x0, x19
	beq	.L789
	bl	ProcessNotMpeg4ScdUpMsg
	mov	w0, 0
.L787:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L789:
	bl	ProcessMpeg4ScdUpMsg
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L791:
	mov	x0, x19
	bl	ProcessNoSeg
	b	.L787
.L790:
	mov	x0, x19
	mov	w1, w2
	bl	ProcessExceptionalStartCodeNum
	mov	w0, -7
	b	.L787
	.size	ProcessScdReturn.part.9, .-ProcessScdReturn.part.9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessScdReturn
	.type	ProcessScdReturn, %function
ProcessScdReturn:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	add	x2, x19, 278528
	add	x2, x2, 168
	ldr	w0, [x2, 8]
	cmp	w0, 3
	beq	.L795
	mov	w0, 2
	mov	w1, w20
	str	w0, [x2, 8]
	mov	x0, x19
	bl	ProcessScdReturn.part.9
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L795:
	mov	w1, 2
	str	w1, [x2, 8]
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ProcessScdReturn, .-ProcessScdReturn
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SaveRawStream
	.type	SCDDRV_SaveRawStream, %function
SCDDRV_SaveRawStream:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	x23, x1
	mov	x20, x2
	bl	_mcount
	ldr	x21, .LC159
	ldr	x0, [x21, w22, sxtw 3]
	cbz	x0, .L796
	ldr	x19, .LC160
	mov	w0, 0
	ldr	w24, [x23, 20]
	ldr	x1, [x19, 32]
	blr	x1
	ldrb	w0, [x20, 2]
	cbnz	w0, .L798
	add	x1, x23, 36
	mov	w0, w24
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cbnz	w0, .L806
.L799:
	ldr	x2, [x21, w22, sxtw 3]
	ldr	w1, [x20, 12]
	ldr	x3, [x19, 88]
	ldr	x0, [x20, 40]
	blr	x3
.L798:
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
.L796:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L806:
	ldr	x2, [x21, w22, sxtw 3]
	mov	w1, 4
	ldr	x3, [x19, 88]
	add	x0, x20, 12
	blr	x3
	b	.L799
	.size	SCDDRV_SaveRawStream, .-SCDDRV_SaveRawStream
	.align	3
.LC159:
	.xword	vfmw_save_str_file
	.align	3
.LC160:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	NeedReadStream
	.type	NeedReadStream, %function
NeedReadStream:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 60]
	cbnz	w0, .L808
	ldr	w1, [x19, 64]
	mov	w0, 1
	cbz	w1, .L809
.L808:
	add	x19, x19, 278528
	mov	w0, 0
	ldr	w1, [x19, 160]
	cmp	w1, 8
	bgt	.L809
	ldr	x0, .LC161
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 311296
	ldr	w0, [x0, 1604]
	cmp	w0, 1
	ccmp	w1, wzr, 4, eq
	cset	w0, le
.L809:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	NeedReadStream, .-NeedReadStream
	.align	3
.LC161:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillEopRawStream
	.type	FillEopRawStream, %function
FillEopRawStream:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC163
	ldr	x0, .LC162
	mov	x2, 100
	add	x1, x21, 144
	add	x20, x0, x20, sxtw 4
	add	x0, x29, 56
	ldr	x20, [x20, 88]
	bl	memcpy
	cbz	x19, .L827
	ldr	w3, [x20, 20]
	cmp	w3, 16
	bls	.L828
.L816:
	ldr	x1, .LC168
	add	x2, x21, 248
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
.L825:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L828:
	ldr	x0, .LC166
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx818
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx818:
	.section	.rodata
	.align	0
	.align	2
.L818:
	.byte	(.L823 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L816 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L819 - .Lrtx818) / 4
	.byte	(.L820 - .Lrtx818) / 4
	.text
	.p2align 3
.L823:
	ldr	w3, [x19, 12]
	mov	w20, 15
	ldr	w5, [x19, 80]
	add	x1, x29, 56
	add	w0, w3, w20
	cmp	w0, w5
	bhi	.L821
.L826:
	ldr	x4, .LC171
	and	x2, x20, 31
	ldr	x0, [x19, 40]
	add	x0, x0, x3, sxtw
	ldr	x3, [x4, 104]
	blr	x3
	ldr	w4, [x19, 12]
	mov	w0, 0
	add	w20, w4, w20
	str	w20, [x19, 12]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L820:
	ldr	w3, [x19, 12]
	mov	w20, 16
	ldr	w5, [x19, 80]
	add	x1, x29, 136
	add	w0, w3, w20
	cmp	w0, w5
	bls	.L826
.L821:
	ldr	x1, .LC170
	mov	w4, w20
	add	x2, x21, 248
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L825
	.p2align 3
.L819:
	ldr	w3, [x19, 12]
	mov	w0, 0
	ldr	w5, [x19, 80]
	cmp	w3, w5
	bls	.L825
	mov	w20, 0
	b	.L821
	.p2align 3
.L827:
	ldr	x1, .LC165
	add	x2, x21, 248
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L825
	.size	FillEopRawStream, .-FillEopRawStream
	.align	3
.LC162:
	.xword	.LANCHOR0
	.align	3
.LC163:
	.xword	.LANCHOR3
	.align	3
.LC165:
	.xword	.LC164
	.align	3
.LC166:
	.xword	.L818
	.align	3
.LC168:
	.xword	.LC167
	.align	3
.LC170:
	.xword	.LC169
	.align	3
.LC171:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillEosRawStream
	.type	FillEosRawStream, %function
FillEosRawStream:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC172
	mov	x2, 100
	ldr	x1, .LC173
	add	x19, x0, x19, sxtw 4
	add	x0, x29, 40
	add	x1, x1, 272
	ldr	x19, [x19, 88]
	bl	memcpy
	cbz	x20, .L849
	ldr	w3, [x19, 20]
	cmp	w3, 17
	bls	.L850
.L832:
	ldr	x2, .LC174
	mov	w0, 0
	ldr	x1, .LC177
	bl	dprint_vfmw
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L850:
	ldr	x0, .LC176
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx834
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx834:
	.section	.rodata
	.align	0
	.align	2
.L834:
	.byte	(.L833 - .Lrtx834) / 4
	.byte	(.L835 - .Lrtx834) / 4
	.byte	(.L836 - .Lrtx834) / 4
	.byte	(.L837 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L844 - .Lrtx834) / 4
	.byte	(.L832 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.byte	(.L833 - .Lrtx834) / 4
	.byte	(.L839 - .Lrtx834) / 4
	.byte	(.L847 - .Lrtx834) / 4
	.text
	.p2align 3
.L833:
	mov	w19, 15
	add	x1, x29, 40
.L838:
	ldr	w4, [x20, 12]
	cmp	w19, w4
	bls	.L851
	ldr	x2, .LC174
	mov	w3, w19
	ldr	x1, .LC179
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L845
	.p2align 3
.L851:
	ldr	x3, .LC180
	and	x2, x19, 31
	ldr	x0, [x20, 40]
	ldr	x3, [x3, 104]
	blr	x3
	str	w19, [x20, 12]
.L847:
	mov	w0, 0
.L845:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L835:
	ldr	w0, [x19, 36]
	cmp	w0, 1
	bne	.L847
.L844:
	mov	w19, 15
	add	x1, x29, 60
	b	.L838
	.p2align 3
.L839:
	mov	w19, 16
	add	x1, x29, 120
	b	.L838
	.p2align 3
.L837:
	mov	w19, 16
	add	x1, x29, 100
	b	.L838
	.p2align 3
.L836:
	mov	w19, 19
	add	x1, x29, 80
	b	.L838
.L849:
	ldr	x2, .LC174
	mov	w0, 0
	ldr	x1, .LC175
	bl	dprint_vfmw
	mov	w0, -7
	b	.L845
	.size	FillEosRawStream, .-FillEosRawStream
	.align	3
.LC172:
	.xword	.LANCHOR0
	.align	3
.LC173:
	.xword	.LANCHOR3
	.align	3
.LC174:
	.xword	.LANCHOR4
	.align	3
.LC175:
	.xword	.LC164
	.align	3
.LC176:
	.xword	.L834
	.align	3
.LC177:
	.xword	.LC167
	.align	3
.LC179:
	.xword	.LC178
	.align	3
.LC180:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillVC1ExtraData
	.type	FillVC1ExtraData, %function
FillVC1ExtraData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	w0, [x20, 36]
	cmp	w0, 1
	beq	.L864
	ldr	w0, [x19, 76]
	tbnz	x0, 7, .L865
	add	x20, x20, 278528
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	ldr	w0, [x20, 332]
	add	w3, w2, w0
	cmp	w3, w4
	bhi	.L866
	ldr	x1, [x19, 40]
	sxtw	x2, w2
	ldr	x22, .LC184
	mov	w21, 0
	add	x0, x1, x0, uxtw
.L863:
	ldr	x3, [x22, 112]
	blr	x3
	ldr	w2, [x20, 332]
	add	x1, x20, 336
	ldr	x0, [x19, 40]
	ldr	x3, [x22, 104]
	blr	x3
	ldr	w1, [x19, 12]
	ldr	w0, [x20, 332]
	add	w0, w1, w0
	str	w0, [x19, 12]
.L856:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L865:
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	add	w3, w2, 12
	cmp	w3, 128
	ccmp	w3, w4, 2, le
	bhi	.L867
	ldr	x22, .LC184
	sxtw	x2, w2
	ldr	x1, [x19, 40]
	add	x20, x20, 278528
	mov	w21, 0
	ldr	x3, [x22, 112]
	add	x0, x1, 8
	blr	x3
	ldr	x3, [x22, 104]
	add	x1, x19, 84
	ldr	x0, [x19, 40]
	mov	x2, 4
	blr	x3
	ldr	x0, [x19, 40]
	mov	x2, 4
	ldr	x3, [x22, 104]
	add	x1, x19, 88
	add	x0, x0, x2
	blr	x3
	ldr	x0, [x19, 40]
	mov	x2, 4
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 12
	blr	x3
	mov	w1, 16
	str	w1, [x19, 12]
	str	w1, [x20, 332]
	add	x0, x20, 336
	ldr	x3, [x22, 104]
	ldrsw	x2, [x19, 12]
	ldr	x1, [x19, 40]
	blr	x3
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L864:
	ldr	w1, [x19, 76]
	tbnz	x1, 7, .L868
	ldrb	w1, [x19, 72]
	mov	w21, 0
	cbz	w1, .L856
	add	x20, x20, 278528
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	ldr	w5, [x20, 332]
	add	w3, w2, w5
	cmp	w3, w4
	bhi	.L869
	ldr	x1, [x19, 40]
	sxtw	x2, w2
	ldr	x22, .LC184
	add	x0, x1, x5, uxtw
	b	.L863
	.p2align 3
.L868:
	ldr	w3, [x19, 12]
	cmp	w3, 128
	bgt	.L870
	add	x20, x20, 278528
	ldr	x1, .LC184
	add	x0, x20, 336
	mov	w21, 0
	str	w3, [x20, 332]
	ldr	x3, [x1, 104]
	ldrsw	x2, [x19, 12]
	ldr	x1, [x19, 40]
	blr	x3
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L867:
	ldr	x2, .LC181
	mov	w5, 128
	ldr	x1, .LC188
	mov	w0, 1
	add	x2, x2, 24
	mov	w21, -2
	bl	dprint_vfmw
	b	.L856
	.p2align 3
.L866:
	ldr	x2, .LC181
	mov	w0, 1
	ldr	x1, .LC186
	mov	w21, -2
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L856
.L870:
	ldr	x2, .LC181
	mov	w4, 128
	ldr	x1, .LC183
	mov	w21, -2
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L856
.L869:
	ldr	x2, .LC181
	mov	w21, -2
	ldr	x1, .LC186
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L856
	.size	FillVC1ExtraData, .-FillVC1ExtraData
	.align	3
.LC181:
	.xword	.LANCHOR4
	.align	3
.LC183:
	.xword	.LC182
	.align	3
.LC184:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC186:
	.xword	.LC185
	.align	3
.LC188:
	.xword	.LC187
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillDIVX3ExtraData
	.type	FillDIVX3ExtraData, %function
FillDIVX3ExtraData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	add	w3, w2, 8
	cmp	w3, w4
	bhi	.L874
	ldr	x20, .LC192
	sxtw	x2, w2
	ldr	x1, [x19, 40]
	ldr	x3, [x20, 112]
	add	x0, x1, 8
	blr	x3
	ldr	x3, [x20, 104]
	mov	x2, 4
	ldr	x0, [x19, 40]
	add	x1, x19, 84
	blr	x3
	ldr	x0, [x19, 40]
	mov	x2, 4
	ldr	x3, [x20, 104]
	add	x1, x19, 88
	add	x0, x0, x2
	blr	x3
	ldr	w1, [x19, 12]
	mov	w0, 0
	add	w1, w1, 8
	str	w1, [x19, 12]
.L873:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L874:
	ldr	x2, .LC189
	mov	w0, 1
	ldr	x1, .LC191
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -2
	b	.L873
	.size	FillDIVX3ExtraData, .-FillDIVX3ExtraData
	.align	3
.LC189:
	.xword	.LANCHOR4
	.align	3
.LC191:
	.xword	.LC190
	.align	3
.LC192:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillREAL8ExtraData
	.type	FillREAL8ExtraData, %function
FillREAL8ExtraData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x1
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 76]
	tbz	x0, 7, .L876
	ldr	w3, [x19, 12]
	cmp	w3, 128
	bgt	.L880
	add	x20, x20, 278528
	ldr	x1, .LC195
	add	x0, x20, 336
	str	w3, [x20, 332]
	ldr	x3, [x1, 104]
	ldrsw	x2, [x19, 12]
	ldr	x1, [x19, 40]
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L876:
	add	x20, x20, 278528
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	ldr	w0, [x20, 332]
	add	w3, w2, w0
	cmp	w3, w4
	bhi	.L881
	ldr	x21, .LC195
	sxtw	x2, w2
	ldr	x1, [x19, 40]
	ldr	x3, [x21, 112]
	add	x0, x1, x0, uxtw
	blr	x3
	ldr	w2, [x20, 332]
	add	x1, x20, 336
	ldr	x0, [x19, 40]
	ldr	x3, [x21, 104]
	blr	x3
	ldr	w2, [x19, 12]
	mov	w0, 0
	ldr	w1, [x20, 332]
	add	w1, w2, w1
	str	w1, [x19, 12]
.L878:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L881:
	ldr	x2, .LC193
	mov	w0, 1
	ldr	x1, .LC197
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -2
	b	.L878
	.p2align 3
.L880:
	ldr	x2, .LC193
	mov	w4, 128
	ldr	x1, .LC194
	mov	w0, 1
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -2
	b	.L878
	.size	FillREAL8ExtraData, .-FillREAL8ExtraData
	.align	3
.LC193:
	.xword	.LANCHOR4
	.align	3
.LC194:
	.xword	.LC182
	.align	3
.LC195:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC197:
	.xword	.LC196
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillExtraData
	.type	FillExtraData, %function
FillExtraData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	x20, xzr
	ccmp	w19, 31, 2, ne
	bhi	.L888
	ldr	w3, [x20, 12]
	cmp	w3, wzr
	ble	.L891
	ldr	x0, .LC201
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	ldr	w1, [x0, 20]
	cmp	w1, 5
	beq	.L885
	cmp	w1, 8
	beq	.L886
	cmp	w1, 1
	beq	.L892
	mov	w0, 0
.L883:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L886:
	mov	x1, x20
	bl	FillREAL8ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L885:
	mov	x1, x20
	bl	FillDIVX3ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L892:
	mov	x1, x20
	bl	FillVC1ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L888:
	mov	w0, -1
	b	.L883
.L891:
	ldr	x2, .LC198
	mov	w0, 1
	ldr	x1, .LC200
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L883
	.size	FillExtraData, .-FillExtraData
	.align	3
.LC198:
	.xword	.LANCHOR4
	.align	3
.LC200:
	.xword	.LC199
	.align	3
.LC201:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseRawStreamData
	.type	ReleaseRawStreamData, %function
ReleaseRawStreamData:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	mov	w0, w22
	bl	VCTRL_GetStreamInterface
	ldr	x19, .LC202
	mov	x20, x0
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 72
	ldr	x3, [x19, 96]
	blr	x3
	cbz	x20, .L909
	ldr	x3, [x19, 104]
	mov	x2, 24
	mov	x1, x20
	add	x0, x29, 72
	blr	x3
	mov	x2, 96
	ldr	x3, [x19, 104]
	mov	x1, x21
	add	x0, x29, x2
	sxtw	x21, w22
	blr	x3
	ldr	x23, .LC205
	ldr	x0, [x20, 16]
	cbz	x0, .L896
	lsl	x20, x21, 4
	add	x24, x23, 88
	ldr	x0, [x24, x20]
	ldr	w0, [x0, 60]
	cmp	w0, 1
	beq	.L910
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldr	x2, [x19, 48]
	mov	w1, w22
	mov	w0, 1
	blr	x2
	ldr	x0, [x24, x20]
	cbz	x0, .L901
	ldr	w0, [x29, 72]
	add	x1, x29, 96
	ldr	x2, [x29, 88]
	blr	x2
	mov	w20, w0
.L899:
	ldr	x2, [x19, 56]
	mov	w0, 1
	mov	w1, w22
	blr	x2
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	cbz	w20, .L900
.L896:
	mov	w20, -7
.L900:
	add	x21, x23, x21, lsl 4
	mov	w0, w20
	ldr	x1, [x21, 88]
	cbz	x1, .L911
.L895:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L910:
	ldr	w0, [x29, 72]
	add	x1, x29, 96
	ldr	x2, [x29, 88]
	blr	x2
	mov	w20, w0
	cbz	w20, .L900
	b	.L896
	.p2align 3
.L901:
	mov	w20, -7
	b	.L899
.L909:
	ldr	x1, .LC204
	mov	w2, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L895
.L911:
	ldr	x1, .LC207
	mov	w3, w22
	mov	w2, 3596
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L895
	.size	ReleaseRawStreamData, .-ReleaseRawStreamData
	.align	3
.LC202:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC205:
	.xword	.LANCHOR0
	.align	3
.LC207:
	.xword	.LC206
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DeleteRawPacketInBuffer
	.type	DeleteRawPacketInBuffer, %function
DeleteRawPacketInBuffer:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w24, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w24, 31
	bhi	.L924
	ldr	x28, .LC209
	sxtw	x0, w24
	add	x1, x28, x0, lsl 4
	ldr	x22, [x1, 88]
	cbz	x22, .L924
	cbz	w19, .L928
.L914:
	adds	x23, x22, 88
	beq	.L924
	add	x1, x23, 98304
	ldr	w21, [x1]
	ldr	w20, [x1, 8]
	cmp	w21, w20
	blt	.L929
.L927:
	sub	w21, w21, w20
	cbz	w21, .L924
	ldr	x25, .LC210
	add	x28, x28, 88
	ldr	x26, .LC211
	mov	w27, 0
	add	x25, x25, 112
	add	x28, x28, x0, lsl 4
	b	.L918
	.p2align 3
.L931:
	beq	.L930
.L918:
	uxtw	x19, w20
	mov	x2, x25
	lsl	x0, x19, 2
	mov	x1, x26
	sub	x19, x0, x19
	mov	w0, 26
	lsl	x19, x19, 5
	add	w27, w27, 1
	add	x3, x22, x19
	add	w20, w20, 1
	and	w20, w20, 1023
	ldr	w4, [x3, 100]
	ldr	w3, [x3, 92]
	bl	dprint_vfmw
	add	x1, x23, x19
	mov	w0, w24
	bl	ReleaseRawStreamData
	ldr	x0, [x28]
	cmp	w27, w21
	cbnz	x0, .L931
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L928:
	add	x1, x22, 278528
	ldr	w1, [x1, 256]
	cbnz	w1, .L914
.L924:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L929:
	add	w21, w21, 1024
	b	.L927
	.p2align 3
.L930:
	add	x23, x23, 98304
	ldr	w20, [x23, 8]
	add	w20, w20, w27
	cmp	w20, 1023
	ble	.L932
	sub	w20, w20, #1024
	str	w20, [x23, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L932:
	str	w20, [x23, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.size	DeleteRawPacketInBuffer, .-DeleteRawPacketInBuffer
	.align	3
.LC209:
	.xword	.LANCHOR0
	.align	3
.LC210:
	.xword	.LANCHOR4
	.align	3
.LC211:
	.xword	.LC45
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Reset
	.type	SM_Reset, %function
SM_Reset:
	stp	x29, x30, [sp, -304]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, 31
	bhi	.L945
	ldr	x27, .LC214
	sxtw	x23, w21
	add	x0, x27, x23, lsl 4
	ldr	x20, [x0, 88]
	cbz	x20, .L935
	ldr	w0, [x27, 52]
	cmp	w21, w0
	bne	.L937
	ldr	x2, .LC217
	mov	w3, 1095
	ldr	x1, .LC219
	mov	w0, 22
	add	x2, x2, 136
	str	wzr, [x27, 56]
	bl	dprint_vfmw
.L937:
	ldr	x22, .LC220
	mov	x2, 80
	add	x1, x20, 8
	add	x0, x29, 96
	add	x19, x20, 278528
	add	x23, x27, x23, lsl 4
	ldr	x3, [x22, 104]
	add	x25, x19, 336
	blr	x3
	ldr	w24, [x19, 256]
	ldr	x3, [x22, 104]
	mov	x2, 128
	mov	x1, x25
	add	x0, x29, 176
	ldr	w26, [x19, 332]
	blr	x3
	ldr	x0, [x23, 88]
	cbz	x0, .L938
	add	x0, x0, 278528
	ldr	w1, [x0, 256]
	cbnz	w1, .L955
.L938:
	adds	x23, x20, 88
	beq	.L939
	add	x1, x23, 98304
	ldr	w0, [x1, 4]
	ldr	w1, [x1]
	sub	w0, w0, w1
	cmp	w0, wzr
	add	w1, w0, 1024
	csel	w1, w1, w0, lt
.L944:
	mov	x0, x23
	sub	w24, w24, #1
	bl	DeleteRawPacket
	mov	w1, 1
	mov	w0, w21
	bl	DeleteRawPacketInBuffer
	ldr	x3, [x22, 96]
	mov	x2, 16856
	movk	x2, 0x4, lsl 16
	mov	w1, 0
	mov	x0, x20
	blr	x3
	mov	x1, -1
	mov	w0, 2
	str	x1, [x19, 280]
	add	x1, x29, 96
	str	w0, [x19, 316]
	mov	w0, w21
	bl	SM_Config
	cmp	w24, 1
	bls	.L956
	str	wzr, [x19, 256]
.L942:
	ldr	x3, [x22, 104]
	mov	x2, 128
	add	x1, x29, 176
	mov	x0, x25
	str	w26, [x19, 332]
	blr	x3
	mov	w0, 0
.L952:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L955:
	ldr	w1, [x0, 244]
	cmp	w1, wzr
	bgt	.L938
	str	wzr, [x0, 256]
	b	.L938
	.p2align 3
.L939:
	ldr	x2, .LC217
	mov	w3, 1110
	ldr	x1, .LC222
	mov	w0, 22
	add	x2, x2, 136
	bl	dprint_vfmw
	mov	w1, 0
	b	.L944
	.p2align 3
.L956:
	mov	w0, 1
	str	w0, [x19, 256]
	b	.L942
	.p2align 3
.L945:
	mov	w0, -1
	b	.L952
.L935:
	ldr	x1, .LC216
	mov	w2, 1085
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L952
	.size	SM_Reset, .-SM_Reset
	.align	3
.LC214:
	.xword	.LANCHOR0
	.align	3
.LC216:
	.xword	.LC215
	.align	3
.LC217:
	.xword	.LANCHOR4
	.align	3
.LC219:
	.xword	.LC218
	.align	3
.LC220:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC222:
	.xword	.LC221
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReadRawStreamData
	.type	ReadRawStreamData, %function
ReadRawStreamData:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	sxtw	x23, w0
	mov	x0, x30
	mov	x24, x1
	mov	x20, x23
	bl	_mcount
	ldr	x25, .LC223
	ldr	x21, .LC224
	mov	x2, 24
	add	x0, x25, x23, lsl 4
	mov	w1, 0
	ldr	x3, [x21, 96]
	ldr	x19, [x0, 88]
	add	x0, x29, 88
	blr	x3
	cbz	x19, .L958
	mov	w0, w23
	bl	VCTRL_GetStreamInterface
	mov	x22, x0
	cbz	x0, .L993
	ldr	x3, [x21, 104]
	mov	x2, 24
	add	x0, x29, 88
	mov	x1, x22
	blr	x3
	ldr	x0, [x22, 8]
	cbz	x0, .L958
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L994
	ldr	x22, .LC227
	ldr	x0, [x22, w23, sxtw 3]
	cbz	x0, .L974
	add	x0, x0, 311296
	ldr	w26, [x0, 1564]
.L964:
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	ldr	x0, [x22, w20, sxtw 3]
	cbz	x0, .L965
	add	x0, x0, 311296
	ldr	w0, [x0, 1564]
	cmp	w26, w0
	bne	.L995
.L965:
	ldr	x2, [x29, 96]
	mov	x1, x24
	ldr	w0, [x29, 88]
	add	x23, x25, x23, lsl 4
	blr	x2
	mov	w22, w0
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	ldr	x0, [x23, 88]
	cbz	x0, .L996
	cbz	w22, .L966
.L958:
	mov	w0, -7
.L990:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L966:
	ldrb	w21, [x24, 1]
	cmp	w21, 1
	beq	.L997
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L998
.L968:
	add	x19, x19, 98304
	ldr	w1, [x24, 12]
	mov	w0, 0
	ldr	w2, [x19, 108]
	add	w1, w2, w1
	str	w1, [x19, 108]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L997:
	mov	x1, x24
	mov	w0, w20
	bl	FillEosRawStream
	cbnz	w0, .L999
	mov	w1, w21
	mov	w0, w20
	bl	VCTRL_SetLastFrameState
	b	.L968
	.p2align 3
.L994:
	ldr	w0, [x29, 88]
	mov	x1, x24
	ldr	x2, [x29, 96]
	blr	x2
	mov	w22, w0
	cbz	w22, .L966
	b	.L958
	.p2align 3
.L974:
	mov	w26, 0
	b	.L964
	.p2align 3
.L998:
	mov	x1, x24
	mov	w0, w20
	bl	FillExtraData
	cbnz	w0, .L1000
	add	x0, x19, 278528
	ldr	w0, [x0, 328]
	cbz	w0, .L968
	ldrb	w0, [x24]
	cbnz	w0, .L968
	mov	x1, x24
	mov	w0, w20
	bl	FillEopRawStream
	b	.L968
	.p2align 3
.L1000:
	ldr	x1, .LC233
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x29, 88]
	mov	x1, x24
	bl	ReleaseRawStreamData
	cbz	w0, .L958
	ldr	x1, .LC235
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L990
.L996:
	ldr	x1, .LC229
	mov	w3, w20
	mov	w2, 3501
	bl	dprint_vfmw
	mov	w0, -7
	b	.L990
	.p2align 3
.L995:
	ldr	x1, [x21, 24]
	mov	w0, 0
	blr	x1
	mov	w0, -7
	b	.L990
.L993:
	ldr	x1, .LC226
	mov	w2, w23
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L990
.L999:
	ldr	x1, .LC231
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L990
	.size	ReadRawStreamData, .-ReadRawStreamData
	.align	3
.LC223:
	.xword	.LANCHOR0
	.align	3
.LC224:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC226:
	.xword	.LC225
	.align	3
.LC227:
	.xword	s_pstVfmwChan
	.align	3
.LC229:
	.xword	.LC228
	.align	3
.LC231:
	.xword	.LC230
	.align	3
.LC233:
	.xword	.LC232
	.align	3
.LC235:
	.xword	.LC234
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	FillRawData
	.type	FillRawData, %function
FillRawData:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	sxtw	x22, w0
	mov	x0, x30
	mov	x20, x22
	bl	_mcount
	ldr	x24, .LC236
	ldr	x23, .LC237
	mov	x2, 96
	add	x4, x24, x22, lsl 4
	mov	w1, 0
	add	x0, x29, 112
	ldr	x3, [x23, 96]
	ldr	x21, [x4, 88]
	blr	x3
	cbz	x21, .L1001
	ldr	w0, [x21, 20]
	cmp	w0, 20
	beq	.L1001
	lsl	w0, w22, 24
	ldr	x28, .LC238
	str	w0, [x29, 108]
	add	x19, x21, 278528
	ldr	x0, .LC246
	mov	x27, x28
	ldr	x26, .LC240
	ldr	x25, .LC242
	add	x0, x0, 152
	str	x0, [x29, 96]
	.p2align 2
.L1017:
	ldr	w0, [x21, 60]
	cbnz	w0, .L1003
	ldr	w0, [x21, 64]
	cbz	w0, .L1004
.L1003:
	ldr	w1, [x19, 160]
	cmp	w1, 8
	bgt	.L1001
	ldr	x0, [x28, x22, lsl 3]
	add	x0, x0, 311296
	ldr	w0, [x0, 1604]
	cmp	w0, 1
	ccmp	w1, wzr, 4, eq
	ble	.L1004
.L1001:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1004:
	cmp	w20, 31
	bhi	.L1008
	add	x0, x24, x22, lsl 4
	ldr	x0, [x0, 88]
	cbz	x0, .L1008
	add	x0, x0, 88
	add	x1, x0, 98304
	ldp	w0, w2, [x1, 4]
	add	w0, w0, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w0, w0, w1
	cmp	w0, w2
	beq	.L1008
	add	x1, x29, 112
	mov	w0, w20
	bl	ReadRawStreamData
	cbnz	w0, .L1001
	ldr	w2, [x19, 296]
	ldr	w4, [x19, 320]
	ldr	w1, [x19, 324]
	ldr	w0, [x29, 124]
	ldr	x3, [x23]
	add	w1, w1, 1
	add	w2, w2, w0
	str	w1, [x19, 324]
	add	w0, w4, w0
	str	w2, [x19, 296]
	str	w0, [x19, 320]
	blr	x3
	ldr	w1, [x19, 300]
	cbnz	w1, .L1010
	str	w0, [x19, 300]
.L1011:
	ldr	x2, [x29, 176]
	mov	x1, x26
	mov	w0, 29
	bl	dprint_vfmw
	ldr	w2, [x29, 116]
	mov	x1, x25
	ldr	w3, [x29, 124]
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x1, [x29, 176]
	mov	x0, 4294967295
	cmp	x1, x0
	beq	.L1040
	add	x1, x29, 112
	mov	w0, w20
	bl	SCDDRV_InsertRawPacket
	cbnz	w0, .L1041
.L1013:
	mov	w1, 1
	strb	w1, [x21, 3]
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L1042
.L1015:
	mov	w0, w20
	add	x2, x29, 112
	mov	x1, x21
	bl	SCDDRV_SaveRawStream
	ldr	x0, [x27, x22, lsl 3]
	add	x0, x0, 311296
	ldr	w0, [x0, 1604]
	cmp	w0, 1
	bne	.L1017
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1008:
	ldr	x1, .LC248
	mov	w2, w20
	mov	w0, 23
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1010:
	sub	w1, w0, w1
	cmp	w1, 2000
	bls	.L1011
	ldr	w2, [x19, 296]
	str	w0, [x19, 300]
	lsl	w0, w2, 3
	str	wzr, [x19, 296]
	udiv	w1, w0, w1
	lsl	w0, w1, 6
	sub	w0, w0, w1
	lsl	w0, w0, 1
	sub	w1, w0, w1
	ubfx	x1, x1, 7, 22
	str	w1, [x19, 304]
	b	.L1011
	.p2align 3
.L1042:
	ldr	x0, [x23]
	blr	x0
	ldr	x1, .LC245
	add	x2, x24, 632
	ldr	w3, [x1]
	ldr	w1, [x2, x22, lsl 2]
	sub	w1, w0, w1
	cmp	w1, w3
	bls	.L1015
	str	w0, [x2, x22, lsl 2]
	mov	w1, 2863
	ldr	w2, [x29, 108]
	ldr	x0, [x29, 96]
	bl	DBG_AddTrace
	b	.L1015
	.p2align 3
.L1040:
	mov	x0, -1
	add	x1, x29, 112
	str	x0, [x29, 176]
	mov	w0, w20
	bl	SCDDRV_InsertRawPacket
	cbz	w0, .L1013
.L1041:
	ldr	x1, .LC244
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1001
	.size	FillRawData, .-FillRawData
	.align	3
.LC236:
	.xword	.LANCHOR0
	.align	3
.LC237:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC238:
	.xword	s_pstVfmwChan
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
.LC245:
	.xword	g_TraceBsPeriod
	.align	3
.LC246:
	.xword	.LANCHOR4
	.align	3
.LC248:
	.xword	.LC247
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseSegArrayPackets
	.type	ReleaseSegArrayPackets, %function
ReleaseSegArrayPackets:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	cmp	w19, 2048
	beq	.L1043
	cmp	w19, w21
	beq	.L1043
	add	x23, x20, 180224
	mov	w22, 2
	.p2align 2
.L1046:
	sxtw	x3, w19
	mov	w1, w19
	lsl	x2, x3, 2
	mov	x0, x20
	sub	x2, x2, x3
	lsl	x2, x2, 2
	sub	x2, x2, x3
	add	x2, x20, x2, lsl 3
	strb	w22, [x2, 16]
	ldr	w4, [x2, 28]
	ldp	w3, w2, [x23, 44]
	subs	w3, w3, w4
	csel	w3, w3, wzr, pl
	subs	w2, w2, #1
	csel	w2, w2, wzr, pl
	stp	w3, w2, [x23, 44]
	bl	ReleaseStreamSeg
	add	w0, w19, 1
	asr	w19, w0, 31
	lsr	w19, w19, 21
	add	w0, w0, w19
	and	w0, w0, 2047
	sub	w19, w0, w19
	cmp	w21, w19
	bne	.L1046
.L1043:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ReleaseSegArrayPackets, .-ReleaseSegArrayPackets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPtsInSegArray
	.type	SM_SeekPtsInSegArray, %function
SM_SeekPtsInSegArray:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	add	x21, x0, 180224
	mov	x25, x0
	mov	x0, x30
	mov	x23, x1
	bl	_mcount
	ldp	w20, w4, [x21, 8]
	ldp	x22, x24, [x23]
	str	w20, [x21, 16]
	.p2align 2
.L1049:
	sxtw	x19, w20
	cmp	w20, w4
	lsl	x3, x19, 2
	mov	w1, w20
	sub	x3, x3, x19
	mov	x0, x25
	lsl	x3, x3, 2
	sub	x19, x3, x19
	beq	.L1060
	add	x19, x25, x19, lsl 3
	ldrsb	w2, [x19, 16]
	cmp	w2, 1
	bne	.L1052
	ldr	x1, [x19, 48]
	add	w0, w20, 1
	cmn	x1, #1
	beq	.L1061
	cmp	x22, x1
	asr	w1, w0, 31
	lsr	w1, w1, 21
	bls	.L1055
	add	w0, w0, w1
	str	w20, [x21, 16]
	and	w20, w0, 2047
	sub	w20, w20, w1
	b	.L1049
	.p2align 3
.L1052:
	bl	ReleaseStreamSeg
	add	w0, w20, 1
	ldr	w4, [x21, 12]
	asr	w20, w0, 31
	lsr	w20, w20, 21
	add	w0, w0, w20
	and	w0, w0, 2047
	sub	w20, w0, w20
	b	.L1049
	.p2align 3
.L1055:
	beq	.L1062
	bcs	.L1049
	ldr	w2, [x21, 16]
	sxtw	x1, w2
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x25, x0, lsl 3
	ldr	x0, [x0, 48]
	cmn	x0, #1
	beq	.L1059
	cmp	x22, x0
	bls	.L1058
	sub	x22, x22, x0
	cmp	x24, x22
	bcs	.L1058
.L1059:
	mov	w2, w20
	str	w20, [x21, 16]
.L1058:
	ldr	w1, [x21, 8]
	mov	x0, x25
	bl	ReleaseSegArrayPackets
	ldrsw	x2, [x21, 16]
	mov	w0, 0
	lsl	x1, x2, 2
	sub	x1, x1, x2
	lsl	x1, x1, 2
	sub	x1, x1, x2
	add	x25, x25, x1, lsl 3
	ldr	x1, [x25, 48]
	str	x1, [x23]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1061:
	asr	w20, w0, 31
	lsr	w20, w20, 21
	add	w0, w0, w20
	and	w0, w0, 2047
	sub	w20, w0, w20
	b	.L1049
	.p2align 3
.L1060:
	ldr	w1, [x21, 8]
	mov	w2, w20
	bl	ReleaseSegArrayPackets
	ldr	x25, [sp, 64]
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L1062:
	ldr	w1, [x21, 8]
	mov	w2, w20
	mov	x0, x25
	bl	ReleaseSegArrayPackets
	ldr	x0, [x19, 48]
	str	x0, [x23]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	SM_SeekPtsInSegArray, .-SM_SeekPtsInSegArray
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPtsInRawArray
	.type	SM_SeekPtsInRawArray, %function
SM_SeekPtsInRawArray:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	mov	x21, x1
	mov	w22, w3
	bl	_mcount
	ldr	x0, .LC251
	add	x0, x0, x19, sxtw 4
	ldr	x9, [x0, 88]
	cbz	x9, .L1082
	cmp	w22, 1
	mov	w10, 0
	ldp	x8, x11, [x21]
	beq	.L1094
.L1065:
	add	x6, x20, 98304
	ldp	w3, w7, [x6]
	str	w3, [x6, 8]
	mov	w1, w3
	.p2align 2
.L1066:
	sxtw	x5, w1
	add	w0, w1, 1
	asr	w4, w0, 31
	lsl	x2, x5, 2
	sub	x2, x2, x5
	lsr	w4, w4, 22
	cmp	w1, w7
	add	w0, w0, w4
	add	x2, x20, x2, lsl 5
	and	w0, w0, 1023
	beq	.L1095
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L1096
	cmp	x8, x2
	bls	.L1072
	str	w1, [x6, 8]
	sub	w1, w0, w4
	b	.L1066
	.p2align 3
.L1096:
	add	w0, w1, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w1, w0, w1
	b	.L1066
	.p2align 3
.L1095:
	cmp	w3, w1
	bgt	.L1097
.L1090:
	sub	w1, w1, w3
	str	w3, [x6, 8]
	mov	x0, x20
	bl	DeleteRawPacket
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, -2
.L1064:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1097:
	add	w1, w1, 1024
	b	.L1090
	.p2align 3
.L1072:
	beq	.L1098
	ldr	w0, [x6, 8]
	sxtw	x4, w0
	lsl	x2, x4, 2
	sub	x2, x2, x4
	add	x2, x20, x2, lsl 5
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L1092
	cmp	x8, x2
	bls	.L1078
	sub	x8, x8, x2
	cmp	x11, x8
	bcs	.L1078
.L1092:
	mov	w0, w1
	str	w1, [x6, 8]
.L1078:
	cmp	w3, w0
	sub	w1, w0, w3
	bgt	.L1099
.L1080:
	cmp	w22, 1
	beq	.L1100
.L1081:
	sxtw	x2, w0
	mov	x0, x20
	lsl	x3, x2, 2
	sub	x2, x3, x2
	add	x20, x20, x2, lsl 5
.L1093:
	ldr	x2, [x20, 64]
	str	x2, [x21]
	ldr	w2, [x6]
	str	w2, [x6, 8]
	bl	DeleteRawPacket
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1094:
	add	x0, x9, 278528
	ldr	w10, [x0, 176]
	cmp	w10, 1
	bne	.L1065
	mov	w1, 3
	str	w1, [x0, 176]
	b	.L1065
	.p2align 3
.L1099:
	add	w1, w0, 1024
	sub	w1, w1, w3
	b	.L1080
.L1098:
	cmp	w1, w3
	bge	.L1091
	add	w1, w1, 1024
.L1091:
	cmp	w22, 1
	sub	w1, w1, w3
	beq	.L1101
.L1076:
	lsl	x0, x5, 2
	sub	x5, x0, x5
	mov	x0, x20
	add	x20, x20, x5, lsl 5
	b	.L1093
.L1100:
	add	x9, x9, 278528
	ldr	w2, [x9, 168]
	cmp	w1, w2
	ccmp	w10, 1, 0, le
	bne	.L1081
	str	w10, [x9, 176]
	ldr	w0, [x6, 8]
	b	.L1081
.L1101:
	add	x9, x9, 278528
	ldr	w0, [x9, 168]
	cmp	w1, w0
	ccmp	w10, 1, 0, le
	bne	.L1076
	str	w10, [x9, 176]
	b	.L1076
.L1082:
	mov	w0, -1
	b	.L1064
	.size	SM_SeekPtsInRawArray, .-SM_SeekPtsInRawArray
	.align	3
.LC251:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPtsAfterFillNewRaw
	.type	SM_SeekPtsAfterFillNewRaw, %function
SM_SeekPtsAfterFillNewRaw:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w2
	mov	x21, x1
	bl	_mcount
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, w19
	bl	FillRawData
	mov	w2, w19
	mov	x1, x21
	mov	w3, 0
	mov	x0, x20
	bl	SM_SeekPtsInRawArray
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	SM_SeekPtsAfterFillNewRaw, .-SM_SeekPtsAfterFillNewRaw
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPts
	.type	SM_SeekPts, %function
SM_SeekPts:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w21, w0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	cmp	x22, xzr
	ccmp	w21, 31, 2, ne
	bhi	.L1116
	ldr	x0, .LC252
	add	x0, x0, x21, sxtw 4
	ldr	x20, [x0, 88]
	cbz	x20, .L1116
	add	x0, x20, 98304
	mov	x1, x22
	add	x0, x0, 112
	bl	SM_SeekPtsInSegArray
	cbnz	w0, .L1105
.L1106:
	mov	w0, 0
.L1104:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1105:
	mov	w1, 0
	mov	w0, w21
	add	x20, x20, 88
	bl	DeleteRawPacketInBuffer
	mov	w3, 1
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	bl	SM_SeekPtsInRawArray
	cbz	w0, .L1106
	add	x1, x20, 98304
	ldp	w3, w0, [x1]
	cmp	w3, w0
	bgt	.L1126
.L1125:
	sub	w3, w0, w3
	ldr	x2, [x22, 16]
	sxtw	x3, w3
	cmp	x3, x2
	bcs	.L1127
	sub	x3, x2, x3
	and	x0, x3, 1023
	lsr	x23, x3, 10
	cbnz	x0, .L1128
.L1111:
	add	w23, w23, 1
	mov	w19, 0
	cmp	w23, wzr
	bgt	.L1121
	b	.L1114
	.p2align 3
.L1129:
	cmp	w19, w23
	beq	.L1114
.L1121:
	mov	w2, w21
	mov	x1, x22
	mov	x0, x20
	add	w19, w19, 1
	bl	SM_SeekPtsAfterFillNewRaw
	cbnz	w0, .L1129
	b	.L1106
	.p2align 3
.L1126:
	add	w0, w0, 1024
	b	.L1125
	.p2align 3
.L1128:
	add	w23, w23, 1
	b	.L1111
	.p2align 3
.L1114:
	mov	w0, -2
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1116:
	mov	w0, -1
	b	.L1104
.L1127:
	ldr	x1, .LC254
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L1104
	.size	SM_SeekPts, .-SM_SeekPts
	.align	3
.LC252:
	.xword	.LANCHOR0
	.align	3
.LC254:
	.xword	.LC253
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_MoveRawData
	.type	SM_MoveRawData, %function
SM_MoveRawData:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	add	x24, x20, 98304
	bl	_mcount
	ldr	w4, [x20, 72]
	ldr	w0, [x24, 92]
	add	w1, w0, 1023
	subs	w22, w0, #1
	csel	w22, w1, w22, mi
	add	w1, w0, 1022
	subs	w0, w0, #2
	csel	w0, w1, w0, mi
	sxtw	x2, w22
	lsl	x1, x2, 2
	sxtw	x0, w0
	sub	x1, x1, x2
	lsl	x21, x0, 2
	lsl	x1, x1, 5
	sub	x0, x21, x0
	add	x23, x20, x1
	add	x19, x23, 88
	add	x21, x20, x0, lsl 5
	ldr	w2, [x23, 100]
	ldr	w0, [x21, 100]
	add	w1, w0, w2
	cmp	w1, w4
	bgt	.L1133
	ldr	x1, .LC255
	sxtw	x2, w2
	ldr	x3, [x21, 128]
	add	x20, x20, 278528
	add	x0, x3, x0, sxtw
	ldr	x3, [x1, 104]
	ldr	x1, [x23, 128]
	blr	x3
	ldr	w2, [x21, 100]
	mov	x1, x19
	ldr	w0, [x23, 100]
	add	w0, w2, w0
	str	w0, [x21, 100]
	ldr	w0, [x20, 240]
	bl	ReleaseRawStreamData
	str	w22, [x24, 92]
	mov	w0, 0
.L1134:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1133:
	ldr	x1, .LC257
	mov	w3, w2
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1134
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	3
.LC255:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC257:
	.xword	.LC256
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ProcessSegFull
	.type	SCDDRV_ProcessSegFull, %function
SCDDRV_ProcessSegFull:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x20, 98304
	adds	x23, x0, 112
	beq	.L1145
	add	x1, x23, 180224
	ldp	w22, w21, [x1, 44]
.L1136:
	add	x0, x0, 112
	ldrsb	w1, [x20, 1]
	add	x0, x0, 180224
	ldr	w19, [x0, 28]
	cbnz	w1, .L1137
	add	w19, w19, w19, lsr 31
	mov	w0, 127
	asr	w19, w19, 1
	cmp	w19, w22
	ccmp	w21, w0, 0, gt
	ble	.L1149
.L1135:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1137:
	ldr	x0, .LC258
	add	x24, x20, 278528
	ldr	x0, [x0]
	blr	x0
	ldr	w2, [x24, 272]
	cmp	w0, w2
	bls	.L1140
	sub	w2, w0, w2
	str	w2, [x24, 268]
	cmp	w2, 1000
	ble	.L1135
	cmp	w19, wzr
	add	w0, w19, 3
	csel	w19, w0, w19, lt
	mov	w0, 63
	asr	w19, w19, 2
	cmp	w19, w22
	ccmp	w21, w0, 0, gt
	bgt	.L1135
	orr	w21, w22, w21
	cbnz	w21, .L1143
	ldp	w1, w0, [x24, 120]
	cmp	w1, w0
	beq	.L1143
	ldr	x1, .LC260
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x24, 240]
	bl	SM_Reset
	b	.L1144
	.p2align 3
.L1140:
	str	wzr, [x24, 268]
	str	w0, [x24, 272]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1143:
	ldr	x1, .LC262
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x23
	bl	ReleaseStreamSeg
.L1144:
	strb	wzr, [x20, 1]
	strb	wzr, [x20]
	b	.L1135
	.p2align 3
.L1145:
	mov	w22, 0
	mov	w21, 0
	b	.L1136
	.p2align 3
.L1149:
	ldr	x0, .LC258
	mov	w1, 1
	strb	w1, [x20, 1]
	add	x20, x20, 278528
	ldr	x0, [x0]
	blr	x0
	str	wzr, [x20, 268]
	str	w0, [x20, 272]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	SCDDRV_ProcessSegFull, .-SCDDRV_ProcessSegFull
	.align	3
.LC258:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC260:
	.xword	.LC259
	.align	3
.LC262:
	.xword	.LC261
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_CanNotSelectInst
	.type	SCDDRV_CanNotSelectInst, %function
SCDDRV_CanNotSelectInst:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC263
	add	x19, x0, x19, sxtw 4
	ldr	x1, [x19, 88]
	cbz	x1, .L1153
	add	x0, x1, 278528
	ldr	w2, [x0, 256]
	cbz	w2, .L1153
	ldr	w0, [x0, 248]
	cmp	w0, 1
	beq	.L1153
	ldr	w0, [x1, 20]
	ldr	x2, [x1, 36]
	ldr	w1, [x1, 44]
	cmp	w0, 19
	str	x2, [x29, 32]
	str	w1, [x29, 40]
	beq	.L1153
	add	x1, x29, 32
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cmp	w0, wzr
	ldr	x19, [sp, 16]
	cset	w0, ne
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1153:
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 48
	ret
	.size	SCDDRV_CanNotSelectInst, .-SCDDRV_CanNotSelectInst
	.align	3
.LC263:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SM_DoNextInstance.part.11, %function
SM_DoNextInstance.part.11:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w21, w0
	mov	x0, x30
	str	x1, [x29, 104]
	mov	w20, 32
	bl	_mcount
	ldr	x25, .LC264
	sxtw	x0, w21
	ldr	x23, .LC265
	lsl	x1, x0, 6
	ldr	x24, .LC266
	add	x0, x1, x0, lsl 3
	add	x22, x25, 88
	add	x0, x25, x0
	ldr	w19, [x0, 52]
	b	.L1169
	.p2align 3
.L1164:
	subs	w20, w20, #1
	beq	.L1172
.L1169:
	add	w0, w19, 1
	mov	w1, w21
	asr	w19, w0, 31
	lsr	w19, w19, 27
	add	w0, w0, w19
	and	w0, w0, 31
	sub	w19, w0, w19
	mov	w0, w19
	bl	SCDDRV_CanNotSelectInst
	uxtb	w0, w0
	cbnz	w0, .L1164
	sxtw	x28, w19
	ldr	x0, [x23]
	lsl	x1, x28, 4
	ldr	x27, [x22, x1]
	blr	x0
	add	x26, x27, 278528
	ldr	w1, [x26, 312]
	subs	w1, w0, w1
	bmi	.L1165
	ldrsh	w2, [x27, 2]
	cmp	w2, 1
	beq	.L1173
.L1165:
	str	w0, [x26, 312]
	ldrsb	w0, [x27]
	cmp	w0, 1
	beq	.L1174
	strb	wzr, [x27, 1]
.L1167:
	ldr	x2, [x24, x28, lsl 3]
	mov	w1, w21
	mov	x0, x27
	add	x2, x2, 311296
	ldr	w2, [x2, 1592]
	str	w2, [x26, 464]
	bl	CutStreamWithSCD
	cmn	w0, #6
	cset	w1, eq
	strb	w1, [x27]
	cbnz	w0, .L1164
	ldr	x0, [x29, 104]
	add	x2, x25, 760
	ldr	x3, .LC267
	mov	w1, 1
	add	x2, x2, x28, lsl 2
	mov	w4, 4053
	str	w19, [x0]
	add	x3, x3, 168
	mov	w0, w19
	str	w1, [x26, 256]
	bl	RecordPOS
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1173:
	cmp	w1, 199
	bhi	.L1165
	subs	w20, w20, #1
	bne	.L1169
.L1172:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -3
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1174:
	mov	x0, x27
	bl	SCDDRV_ProcessSegFull
	b	.L1167
	.size	SM_DoNextInstance.part.11, .-SM_DoNextInstance.part.11
	.align	3
.LC264:
	.xword	.LANCHOR0
	.align	3
.LC265:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC266:
	.xword	s_pstVfmwChan
	.align	3
.LC267:
	.xword	.LANCHOR4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SCDDRV_ActivateSCD.part.12, %function
SCDDRV_ActivateSCD.part.12:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC270
	add	x1, x20, x19, lsl 2
	ldr	w0, [x1, 600]
	cbz	w0, .L1176
	cmp	w0, 1
	beq	.L1180
.L1175:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1176:
	add	x1, x29, 60
	mov	w0, w19
	bl	SM_DoNextInstance.part.11
	cbnz	w0, .L1175
	lsl	x0, x19, 6
	ldr	w1, [x29, 60]
	add	x0, x0, x19, lsl 3
	add	x0, x20, x0
	str	w1, [x0, 52]
	cbnz	w19, .L1178
	mov	w0, 1
	str	w0, [x20, 56]
.L1178:
	ldr	x0, .LC271
	ldr	x0, [x0]
	blr	x0
	lsl	x1, x19, 6
	ldr	x2, .LC272
	add	x19, x1, x19, lsl 3
	ldr	x1, .LC274
	add	x19, x20, x19
	mov	w3, 4296
	add	x2, x2, 192
	str	w0, [x19, 60]
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1180:
	mov	w0, 2
	str	w0, [x1, 600]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	SCDDRV_ActivateSCD.part.12, .-SCDDRV_ActivateSCD.part.12
	.align	3
.LC270:
	.xword	.LANCHOR0
	.align	3
.LC271:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC272:
	.xword	.LANCHOR4
	.align	3
.LC274:
	.xword	.LC273
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_DoNextInstance
	.type	SM_DoNextInstance, %function
SM_DoNextInstance:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x2, .LC275
	add	x2, x2, x19, sxtw 2
	ldr	w0, [x2, 600]
	cbz	w0, .L1182
	cmp	w0, 1
	mov	w0, -3
	beq	.L1185
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1182:
	mov	x1, x20
	mov	w0, w19
	bl	SM_DoNextInstance.part.11
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1185:
	mov	w1, 2
	str	w1, [x2, 600]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	3
.LC275:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_AddMatchMode
	.type	SM_AddMatchMode, %function
SM_AddMatchMode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC276
	ldr	x23, .LC277
	ldr	x22, .LC279
	add	x20, x21, 88
	add	x21, x21, 600
	.p2align 2
.L1191:
	ldr	x19, [x20]
	cbz	x19, .L1187
	ldr	w2, [x19, 48]
	mov	x1, x22
	mov	w0, 0
	cbz	w2, .L1187
	ldp	w4, w3, [x23]
	cmp	w4, 1
	mov	w2, w4
	beq	.L1200
.L1190:
	bl	dprint_vfmw
.L1199:
	add	x19, x19, 278528
	str	wzr, [x19, 252]
.L1187:
	add	x20, x20, 16
	cmp	x20, x21
	bne	.L1191
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1200:
	cmp	w3, 1
	beq	.L1199
	cmp	w3, 2
	bne	.L1190
	add	x19, x19, 278528
	str	w4, [x19, 252]
	b	.L1187
	.size	SM_AddMatchMode, .-SM_AddMatchMode
	.align	3
.LC276:
	.xword	.LANCHOR0
	.align	3
.LC277:
	.xword	g_DspDrvState
	.align	3
.LC279:
	.xword	.LC278
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_RecordGlobalState
	.type	SCDDRV_RecordGlobalState, %function
SCDDRV_RecordGlobalState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC282
	ldr	x0, [x0]
	blr	x0
	sxtw	x2, w19
	ldr	x5, .LC283
	lsl	x1, x2, 4
	sub	x1, x1, x2
	add	x1, x5, x1, lsl 2
	ldr	w3, [x1, 48]
	cbz	w3, .L1201
	ldr	w6, [x1, 44]
	add	w4, w6, 49152
	add	w4, w4, 848
	cmp	w3, w4
	bhi	.L1204
	ldr	w4, [x1, 52]
.L1205:
	lsl	x1, x2, 4
	sub	w3, w0, w3
	sub	x2, x1, x2
	sub	w0, w0, w6
	add	w3, w3, w4
	cmp	w0, 999
	add	x2, x5, x2, lsl 2
	stp	wzr, w3, [x2, 48]
	bls	.L1201
	lsl	w1, w3, 6
	str	wzr, [x2, 44]
	sub	w1, w1, w3
	lsl	w1, w1, 1
	sub	w3, w1, w3
	lsl	w3, w3, 3
	udiv	w0, w3, w0
	str	w0, [x2, 56]
.L1201:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1204:
	mov	w6, w3
	mov	w4, 0
	str	w3, [x1, 44]
	b	.L1205
	.size	SCDDRV_RecordGlobalState, .-SCDDRV_RecordGlobalState
	.align	3
.LC282:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC283:
	.xword	g_VfmwGlobalStat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_MoveRawByOmxPath
	.type	SCDDRV_MoveRawByOmxPath, %function
SCDDRV_MoveRawByOmxPath:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC284
	add	x19, x0, x19, sxtw 4
	ldr	x19, [x19, 88]
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1217
.L1207:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1217:
	adds	x1, x19, 88
	beq	.L1210
	add	x1, x1, 98304
	ldr	w0, [x1, 4]
	ldr	w1, [x1]
	sub	w0, w0, w1
	add	w1, w0, 1024
	cmp	w0, wzr
	csel	w0, w1, w0, lt
.L1213:
	ldrsb	w20, [x19, 2]
	cmp	w20, 1
	bne	.L1207
	ldr	w1, [x19, 68]
	cmp	w1, w0
	bne	.L1207
	mov	x0, x19
	bl	SM_MoveRawData
	cbz	w0, .L1207
	ldr	x1, .LC286
	mov	w0, w20
	add	x19, x19, 278528
	bl	dprint_vfmw
	ldr	w0, [x19, 240]
	bl	SM_Reset
	b	.L1207
	.p2align 3
.L1210:
	ldr	x1, .LC288
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1213
	.size	SCDDRV_MoveRawByOmxPath, .-SCDDRV_MoveRawByOmxPath
	.align	3
.LC284:
	.xword	.LANCHOR0
	.align	3
.LC286:
	.xword	.LC285
	.align	3
.LC288:
	.xword	.LC287
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SCDIntServeProc
	.type	SM_SCDIntServeProc, %function
SM_SCDIntServeProc:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbz	w19, .L1237
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1237:
	ldr	x20, .LC289
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	ldr	x19, .LC290
	ldr	w0, [x19, 80]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	tbnz	x0, 0, .L1238
.L1220:
	ldr	x0, .LC292
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1229
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Notify_ModuleIdle
.L1229:
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1238:
	ldr	w0, [x19, 80]
	mov	w1, 1
	add	w0, w0, 2084
	bl	MEM_WritePhyWord
	ldp	w1, w21, [x19, 48]
	cmp	w1, wzr
	add	x0, x19, x21, sxtw 4
	ldr	x22, [x0, 88]
	ccmp	x22, xzr, 4, ne
	beq	.L1239
	ldr	x3, .LC291
	mov	w4, 4179
	add	x2, x19, 888
	mov	w1, 2
	add	x3, x3, 216
	mov	w0, w21
	bl	RecordPOS
	mov	w0, 0
	bl	SCDDRV_RecordGlobalState
	ldr	w0, [x19, 56]
	cmp	w0, 1
	beq	.L1240
.L1222:
	ldr	x1, [x20, 256]
	mov	w0, 1
	blr	x1
	ldr	x1, [x20, 256]
	mov	w0, 0
	blr	x1
	b	.L1220
.L1240:
	add	x23, x22, 278528
	ldr	w0, [x23, 256]
	cmp	w0, 1
	beq	.L1241
.L1223:
	ldr	w0, [x19, 600]
	str	wzr, [x23, 248]
	cbz	w0, .L1226
	cmp	w0, 1
	beq	.L1242
.L1227:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	b	.L1222
	.p2align 3
.L1239:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	b	.L1220
.L1226:
	add	x1, x29, 76
	mov	w0, 0
	bl	SM_DoNextInstance.part.11
	cbnz	w0, .L1227
	ldr	w1, [x29, 76]
	ldr	x0, [x20]
	str	w1, [x19, 52]
	mov	w1, 1
	str	w1, [x19, 56]
	blr	x0
	str	w0, [x19, 60]
	b	.L1222
.L1241:
	add	x0, x23, 168
	ldr	w1, [x0, 8]
	cmp	w1, 3
	beq	.L1243
	mov	w2, 2
	mov	w1, 0
	str	w2, [x0, 8]
	mov	x0, x22
	bl	ProcessScdReturn.part.9
.L1225:
	mov	w0, w21
	bl	SCDDRV_MoveRawByOmxPath
	b	.L1223
.L1242:
	mov	w0, 2
	str	w0, [x19, 600]
	b	.L1227
.L1243:
	mov	w1, 2
	str	w1, [x0, 8]
	b	.L1225
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
	.align	3
.LC289:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC290:
	.xword	.LANCHOR0
	.align	3
.LC291:
	.xword	.LANCHOR4
	.align	3
.LC292:
	.xword	g_HalDisable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_CheckDevice
	.type	SCDDRV_CheckDevice, %function
SCDDRV_CheckDevice:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L1253
	ldr	x19, .LC293
	mov	w4, 0
	ldr	x23, .LC294
	mov	w3, 4229
	ldr	x22, .LC296
	mov	w0, 26
	add	x21, x23, 240
	ldr	w5, [x19, 56]
	mov	x2, x21
	mov	x1, x22
	bl	dprint_vfmw
	ldr	w20, [x19, 56]
	cbz	w20, .L1255
	mov	w4, 0
	mov	w5, w20
	mov	w3, 4239
	mov	x2, x21
	mov	x1, x22
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x0, .LC299
	ldr	x0, [x0]
	blr	x0
	ldr	w4, [x19, 60]
	cmp	w0, w4
	bcs	.L1247
	str	w0, [x19, 60]
.L1248:
	ldr	x1, .LC304
	mov	w4, 0
	mov	w3, 4276
	add	x2, x23, 240
	mov	w0, 26
	mov	w20, 1
	bl	dprint_vfmw
.L1254:
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1247:
	sub	w4, w0, w4
	cmp	w4, 2000
	bls	.L1248
	ldr	x1, .LC301
	mov	w3, 0
	ldr	w2, [x19, 52]
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC302
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1249
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Reset_Module
.L1250:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	ldr	w0, [x19, 52]
	add	x19, x19, x0, sxtw 4
	ldr	x1, [x19, 88]
	cbz	x1, .L1252
	add	x1, x1, 278528
	str	wzr, [x1, 248]
.L1252:
	bl	DeleteLastSendRaw
	mov	w20, 0
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1255:
	ldr	x1, .LC298
	mov	x2, x21
	mov	w4, 0
	mov	w3, 4233
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1249:
	mov	w0, 0
	bl	ResetSCD
	b	.L1250
	.p2align 3
.L1253:
	mov	w20, -1
	b	.L1254
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
	.align	3
.LC293:
	.xword	.LANCHOR0
	.align	3
.LC294:
	.xword	.LANCHOR4
	.align	3
.LC296:
	.xword	.LC295
	.align	3
.LC298:
	.xword	.LC297
	.align	3
.LC299:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC301:
	.xword	.LC300
	.align	3
.LC302:
	.xword	g_HalDisable
	.align	3
.LC304:
	.xword	.LC303
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_ActivateSCD
	.type	SCDDRV_ActivateSCD, %function
SCDDRV_ActivateSCD:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L1256
	mov	w0, 0
	bl	SCDDRV_ActivateSCD.part.12
.L1256:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ActivateSCD, .-SCDDRV_ActivateSCD
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_Wakeup
	.type	SM_Wakeup, %function
SM_Wakeup:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	mov	w19, 0
	bl	_mcount
	ldr	x20, .LC306
	add	x20, x20, 88
	b	.L1260
	.p2align 3
.L1259:
	add	w19, w19, 1
	cmp	w19, 32
	beq	.L1267
.L1260:
	ldr	x0, [x20]
	add	x20, x20, 16
	add	x1, x0, 278528
	cbz	x0, .L1259
	ldr	w0, [x1, 256]
	cmp	w0, 1
	bne	.L1259
	mov	w0, w19
	add	w19, w19, 1
	bl	FillRawData
	cmp	w19, 32
	bne	.L1260
	.p2align 2
.L1267:
	ldr	x19, .LC307
	mov	w4, 1
	ldr	x1, .LC309
	mov	w3, 0
	add	x19, x19, 264
	mov	w0, 26
	mov	x2, x19
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_CheckDevice
	cbz	w0, .L1261
	ldr	x1, .LC311
	mov	x2, x19
	mov	w4, 0
	mov	w3, 4325
	mov	w0, 26
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1261:
	ldr	x1, .LC313
	mov	x2, x19
	mov	w4, 0
	mov	w3, 4320
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_ActivateSCD.part.12
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_Wakeup, .-SM_Wakeup
	.align	3
.LC306:
	.xword	.LANCHOR0
	.align	3
.LC307:
	.xword	.LANCHOR4
	.align	3
.LC309:
	.xword	.LC308
	.align	3
.LC311:
	.xword	.LC310
	.align	3
.LC313:
	.xword	.LC312
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WaitSCDFinish
	.type	WaitSCDFinish, %function
WaitSCDFinish:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x22, .LC315
	lsl	x1, x20, 6
	add	x1, x1, x20, lsl 3
	add	x1, x22, x1
	ldr	w0, [x1, 56]
	cmp	w0, 1
	beq	.L1269
.L1271:
	mov	w0, 0
.L1270:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1269:
	ldr	x23, .LC316
	mov	w19, 41248
	movk	w19, 0x7, lsl 16
	lsl	x20, x20, 2
	ldr	x0, [x23]
	blr	x0
	mov	w21, w0
	b	.L1275
	.p2align 3
.L1279:
	ldr	x0, [x23]
	blr	x0
	cmp	w21, w0
	sub	w4, w21, w0
	mvn	w4, w4
	bhi	.L1273
	sub	w4, w0, w21
.L1273:
	cmp	w4, 1000
	bhi	.L1277
	subs	w19, w19, #1
	beq	.L1278
.L1275:
	add	x0, x22, x20
	ldr	w0, [x0, 80]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	tbz	x0, 0, .L1279
	b	.L1271
	.p2align 3
.L1277:
	ldr	x1, .LC318
	mov	w3, w0
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1270
.L1278:
	mov	w0, -7
	b	.L1270
	.size	WaitSCDFinish, .-WaitSCDFinish
	.align	3
.LC315:
	.xword	.LANCHOR0
	.align	3
.LC316:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC318:
	.xword	.LC317
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintScdRawState
	.type	PrintScdRawState, %function
PrintScdRawState:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, 31
	bls	.L1294
.L1280:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1294:
	mov	w0, 26
	bl	IsDprintTypeEnable
	cbz	w0, .L1280
	ldr	x3, .LC319
	mov	w2, w20
	ldr	x1, .LC321
	mov	w0, 26
	add	x3, x3, x20, sxtw 4
	ldr	x23, [x3, 88]
	bl	dprint_vfmw
	ldr	x1, .LC323
	mov	w0, 26
	add	x22, x23, 88
	add	x21, x22, 98304
	ldr	w2, [x21]
	bl	dprint_vfmw
	ldr	x1, .LC325
	mov	w0, 26
	ldr	w2, [x21, 4]
	bl	dprint_vfmw
	ldr	x1, .LC327
	mov	w0, 26
	ldr	w2, [x21, 8]
	bl	dprint_vfmw
	ldr	x1, .LC329
	mov	w0, 26
	ldr	w2, [x21, 12]
	bl	dprint_vfmw
	ldr	x1, .LC331
	mov	w0, 26
	ldr	w2, [x21, 16]
	bl	dprint_vfmw
	cmp	w19, 1
	beq	.L1284
.L1288:
	ldr	x1, .LC333
	mov	w2, w20
	mov	w0, 26
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1284:
	cbz	x22, .L1285
	ldp	w28, w21, [x21]
	sub	w21, w21, w28
	cmp	w21, wzr
	add	w0, w21, 1024
	csel	w21, w0, w21, lt
	cmp	w21, wzr
	ble	.L1288
	ldr	x27, .LC335
	add	w0, w21, w28
	ldr	x26, .LC337
	ldr	x25, .LC339
	ldr	x24, .LC341
	str	w0, [x29, 108]
	.p2align 2
.L1287:
	sxtw	x19, w28
	mov	x1, x27
	lsl	x0, x19, 2
	add	w28, w28, 1
	sub	x19, x0, x19
	mov	w0, 26
	lsl	x19, x19, 5
	add	x21, x23, x19
	add	x19, x22, x19
	ldr	w2, [x21, 92]
	bl	dprint_vfmw
	ldr	x2, [x19, 40]
	mov	x1, x26
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w2, [x21, 100]
	mov	x1, x25
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x2, [x19, 64]
	mov	x1, x24
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w0, [x29, 108]
	cmp	w28, w0
	bne	.L1287
	b	.L1288
.L1285:
	ldr	x2, .LC342
	mov	w3, 4392
	ldr	x1, .LC344
	mov	w0, 22
	add	x2, x2, 280
	bl	dprint_vfmw
	b	.L1288
	.size	PrintScdRawState, .-PrintScdRawState
	.align	3
.LC319:
	.xword	.LANCHOR0
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
.LC342:
	.xword	.LANCHOR4
	.align	3
.LC344:
	.xword	.LC343
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PrintScdSegState
	.type	PrintScdSegState, %function
PrintScdSegState:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w20, w0
	mov	x0, x30
	mov	w23, w1
	bl	_mcount
	cmp	w20, 31
	bls	.L1309
.L1295:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1309:
	mov	w0, 26
	bl	IsDprintTypeEnable
	cbz	w0, .L1295
	ldr	x3, .LC345
	mov	w2, w20
	ldr	x1, .LC347
	mov	w0, 26
	add	x3, x3, x20, sxtw 4
	ldr	x22, [x3, 88]
	bl	dprint_vfmw
	ldr	x1, .LC349
	mov	w0, 26
	add	x24, x22, 98304
	add	x21, x24, 112
	add	x19, x21, 180224
	ldr	w2, [x19, 8]
	bl	dprint_vfmw
	ldr	x1, .LC351
	mov	w0, 26
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	x1, .LC353
	mov	w0, 26
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	ldr	x1, .LC355
	mov	w0, 26
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	x1, .LC357
	mov	w0, 26
	ldr	x2, [x24, 112]
	bl	dprint_vfmw
	ldr	x1, .LC359
	mov	w0, 26
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	x1, .LC361
	mov	w0, 26
	ldr	w2, [x19, 32]
	bl	dprint_vfmw
	ldr	x1, .LC363
	mov	w0, 26
	ldr	w2, [x19, 36]
	bl	dprint_vfmw
	cmp	w23, 1
	beq	.L1299
.L1300:
	ldr	x1, .LC365
	mov	w2, w20
	mov	w0, 26
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1299:
	cbz	x21, .L1300
	ldp	w24, w23, [x19, 8]
	sub	w23, w23, w24
	ands	w23, w23, 2047
	beq	.L1300
	ldr	x28, .LC367
	add	w23, w24, w23
	ldr	x27, .LC369
	ldr	x26, .LC371
	ldr	x25, .LC373
	str	x21, [x29, 104]
	.p2align 2
.L1301:
	sxtw	x19, w24
	mov	x1, x28
	lsl	x0, x19, 2
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	ldr	x0, [x29, 104]
	add	x19, x0, x19, lsl 3
	mov	w0, 26
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	mov	w0, 88
	mov	x1, x27
	smaddl	x3, w24, w0, x22
	mov	w0, 26
	add	w24, w24, 1
	add	x21, x3, 98304
	ldr	x2, [x21, 120]
	bl	dprint_vfmw
	ldr	w2, [x19, 28]
	mov	x1, x26
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w2, [x19, 32]
	mov	x1, x25
	mov	w0, 26
	bl	dprint_vfmw
	ldrsb	w2, [x21, 128]
	mov	w0, 26
	ldr	x1, .LC375
	bl	dprint_vfmw
	ldrb	w2, [x21, 129]
	mov	w0, 26
	ldr	x1, .LC377
	bl	dprint_vfmw
	ldr	x1, .LC379
	mov	w0, 26
	ldr	x2, [x19, 40]
	bl	dprint_vfmw
	cmp	w23, w24
	bne	.L1301
	b	.L1300
	.size	PrintScdSegState, .-PrintScdSegState
	.align	3
.LC345:
	.xword	.LANCHOR0
	.align	3
.LC347:
	.xword	.LC346
	.align	3
.LC349:
	.xword	.LC348
	.align	3
.LC351:
	.xword	.LC350
	.align	3
.LC353:
	.xword	.LC352
	.align	3
.LC355:
	.xword	.LC354
	.align	3
.LC357:
	.xword	.LC356
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
	.align	3
.LC367:
	.xword	.LC366
	.align	3
.LC369:
	.xword	.LC368
	.align	3
.LC371:
	.xword	.LC370
	.align	3
.LC373:
	.xword	.LC372
	.align	3
.LC375:
	.xword	.LC374
	.align	3
.LC377:
	.xword	.LC376
	.align	3
.LC379:
	.xword	.LC378
	.global	g_pScdDrvParamBase
	.global	s_ScdRegResetOKPhyAddr
	.global	s_ScdRegResetPhyAddr
	.global	s_ScdRegPhyBaseAddr
	.global	g_ScdDrvParam
	.global	s_SmIIS
	.global	ForceRelease
	.global	g_hex_flag
	.global	g_hex_len
	.global	g_hex_base_addr
	.global	g_hex_base_vir_addr
	.section	.rodata
	.align	3
.LANCHOR3 = . + 0
	.type	__func__.51152, %object
	.size	__func__.51152, 19
__func__.51152:
	.string	"SCDDRV_LoadDspCode"
	.zero	5
	.type	__func__.51224, %object
	.size	__func__.51224, 16
__func__.51224:
	.string	"DeleteRawPacket"
	.type	__FUNCTION__.51334, %object
	.size	__FUNCTION__.51334, 17
__FUNCTION__.51334:
	.string	"ReleaseStreamSeg"
	.zero	7
	.type	__func__.51398, %object
	.size	__func__.51398, 14
__func__.51398:
	.string	"SM_OpenSCDDrv"
	.zero	2
	.type	__func__.51482, %object
	.size	__func__.51482, 16
__func__.51482:
	.string	"SM_CopyRawToSeg"
	.type	__func__.51733, %object
	.size	__func__.51733, 17
__func__.51733:
	.string	"GetMpeg4ModeFlag"
	.zero	7
	.type	__func__.51760, %object
	.size	__func__.51760, 21
__func__.51760:
	.string	"ProcessMpeg4ScdUpMsg"
	.zero	3
.LC0:
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
	.byte	1
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
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
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
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
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-70
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
	.byte	1
	.byte	-70
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	96
	.byte	0
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
	.byte	1
	.byte	-1
	.byte	0
	.byte	0
	.byte	0
	.zero	4
	.type	__func__.51808, %object
	.size	__func__.51808, 17
__func__.51808:
	.string	"FillEopRawStream"
	.zero	7
.LC1:
	.byte	0
	.byte	0
	.byte	1
	.byte	11
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
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
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
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-2
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
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	-73
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
	.byte	1
	.byte	-73
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	98
	.byte	0
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
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.align	3
.LANCHOR4 = . + 0
	.type	__func__.51835, %object
	.size	__func__.51835, 17
__func__.51835:
	.string	"FillEosRawStream"
	.zero	7
	.type	__func__.51859, %object
	.size	__func__.51859, 17
__func__.51859:
	.string	"FillVC1ExtraData"
	.zero	7
	.type	__func__.51864, %object
	.size	__func__.51864, 19
__func__.51864:
	.string	"FillDIVX3ExtraData"
	.zero	5
	.type	__func__.51869, %object
	.size	__func__.51869, 19
__func__.51869:
	.string	"FillREAL8ExtraData"
	.zero	5
	.type	__func__.51877, %object
	.size	__func__.51877, 14
__func__.51877:
	.string	"FillExtraData"
	.zero	2
	.type	__func__.51238, %object
	.size	__func__.51238, 24
__func__.51238:
	.string	"DeleteRawPacketInBuffer"
	.type	__FUNCTION__.51372, %object
	.size	__FUNCTION__.51372, 9
__FUNCTION__.51372:
	.string	"SM_Reset"
	.zero	7
	.type	__FUNCTION__.51798, %object
	.size	__FUNCTION__.51798, 12
__FUNCTION__.51798:
	.string	"FillRawData"
	.zero	4
	.type	__FUNCTION__.51990, %object
	.size	__FUNCTION__.51990, 18
__FUNCTION__.51990:
	.string	"SM_DoNextInstance"
	.zero	6
	.type	__func__.52036, %object
	.size	__func__.52036, 19
__func__.52036:
	.string	"SCDDRV_ActivateSCD"
	.zero	5
	.type	__FUNCTION__.52023, %object
	.size	__FUNCTION__.52023, 19
__FUNCTION__.52023:
	.string	"SM_SCDIntServeProc"
	.zero	5
	.type	__func__.52030, %object
	.size	__func__.52030, 19
__func__.52030:
	.string	"SCDDRV_CheckDevice"
	.zero	5
	.type	__func__.52045, %object
	.size	__func__.52045, 10
__func__.52045:
	.string	"SM_Wakeup"
	.zero	6
	.type	__FUNCTION__.52067, %object
	.size	__FUNCTION__.52067, 17
__FUNCTION__.52067:
	.string	"PrintScdRawState"
	.data
	.align	3
.LANCHOR1 = . + 0
.LANCHOR2 = . + 17408
	.type	g_avsp_firmware, %object
	.size	g_avsp_firmware, 17920
g_avsp_firmware:
	.word	0
	.word	16283648
	.word	16349954
	.word	9468936
	.word	-252085482
	.word	9468688
	.word	9468692
	.word	16284426
	.word	9468680
	.word	18807566
	.word	-258442240
	.word	10517258
	.word	18807566
	.word	-258442239
	.word	10517258
	.word	18807566
	.word	-258442238
	.word	10517258
	.word	18807566
	.word	-258442237
	.word	10517258
	.word	18807566
	.word	-258442236
	.word	10517258
	.word	18807566
	.word	-258442235
	.word	10517258
	.word	18807566
	.word	-258442234
	.word	10517258
	.word	18807566
	.word	-258442233
	.word	10517258
	.word	-251200754
	.word	10517258
	.word	17758990
	.word	33128448
	.word	24738824
	.word	-1879048192
	.word	16349954
	.word	0
	.word	18512896
	.word	33390592
	.word	24738817
	.word	-250447311
	.word	9468672
	.word	17988136
	.word	-795837688
	.word	12090128
	.word	18807566
	.word	24967950
	.word	-249398743
	.word	33259520
	.word	554859056
	.word	-258966784
	.word	19561007
	.word	-235307008
	.word	-1063027960
	.word	16349968
	.word	0
	.word	11041536
	.word	0
	.word	1073741824
	.word	33259520
	.word	554859057
	.word	9468672
	.word	0
	.word	-1342177280
	.word	0
	.word	33128448
	.word	-1592624595
	.word	-258966776
	.word	12090128
	.word	0
	.word	17988137
	.word	9468680
	.word	16349968
	.word	17988143
	.word	-258966784
	.word	0
	.word	33521664
	.word	-1879048192
	.word	0
	.word	-1610612736
	.word	-248874449
	.word	9468688
	.word	9468692
	.word	11041536
	.word	0
	.word	0
	.word	0
	.word	286948352
	.word	9467906
	.word	33128448
	.word	-1320519377
	.word	1630697896
	.word	33128448
	.word	-786269183
	.word	17988140
	.word	9468680
	.word	12090128
	.word	21953294
	.word	19400197
	.word	33128448
	.word	-1059883006
	.word	33062912
	.word	-1073741824
	.word	1358526466
	.word	-1342177280
	.word	-1879048192
	.word	17988009
	.word	1620081416
	.word	1354267408
	.word	21953294
	.word	19400216
	.word	33128448
	.word	-2133624830
	.word	33062912
	.word	-2147483648
	.word	-2131134462
	.word	19400222
	.word	33128448
	.word	0
	.word	19036462
	.word	33390592
	.word	33398784
	.word	1092253959
	.word	33128448
	.word	1362626056
	.word	17988013
	.word	9468680
	.word	12090128
	.word	21429006
	.word	1092253999
	.word	33128448
	.word	-250447444
	.word	9468680
	.word	12090128
	.word	24673282
	.word	-250447445
	.word	814775048
	.word	12090128
	.word	0
	.word	-785744896
	.word	556956675
	.word	33128448
	.word	-235298816
	.word	-235290624
	.word	25000964
	.word	-2147483648
	.word	33128448
	.word	-1050147328
	.word	18351619
	.word	18875907
	.word	554858927
	.word	33128448
	.word	-235290624
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	-1845493760
	.word	23594500
	.word	18875906
	.word	554858927
	.word	33128448
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	872415232
	.word	-2147483648
	.word	18351646
	.word	24926480
	.word	-2124785392
	.word	-2147483648
	.word	0
	.word	19028272
	.word	20601264
	.word	554858927
	.word	10517258
	.word	546339592
	.word	0
	.word	-268435456
	.word	-1592100601
	.word	12090128
	.word	33128448
	.word	1634207232
	.word	18351619
	.word	18875907
	.word	554859050
	.word	33128448
	.word	-235290624
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	17988139
	.word	9468680
	.word	0
	.word	-771751936
	.word	23594500
	.word	18875906
	.word	554859050
	.word	33128448
	.word	-1073741824
	.word	10517258
	.word	9468680
	.word	0
	.word	17988139
	.word	9468680
	.word	0
	.word	-1543503872
	.word	1073741824
	.word	18351646
	.word	24926480
	.word	1096440080
	.word	-2147483648
	.word	17988138
	.word	19028272
	.word	20601264
	.word	536870912
	.word	10517258
	.word	9468680
	.word	17988139
	.word	9468680
	.word	0
	.word	-1879048192
	.word	1366850566
	.word	33398784
	.word	17987886
	.word	33398784
	.word	33398784
	.word	-518882770
	.word	9468680
	.word	16349968
	.word	0
	.word	-536870912
	.word	1903720450
	.word	1092093440
	.word	17988010
	.word	9468680
	.word	12090128
	.word	18807566
	.word	33259520
	.word	293436421
	.word	25000967
	.word	-1055753810
	.word	9468680
	.word	12090128
	.word	0
	.word	33460224
	.word	33460224
	.word	33198080
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1011712
	.word	0
	.word	0
	.word	1013760
	.word	18687
	.word	0
	.word	0
	.word	18688
	.word	0
	.word	0
	.word	103084
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	0
	.word	102700
	.word	0
	.word	102700
	.word	0
	.word	18432
	.word	916608
	.word	0
	.word	1027074
	.word	0
	.word	1013760
	.word	18432
	.word	916620
	.word	908352
	.word	1027075
	.word	0
	.word	1013760
	.word	105964
	.word	0
	.word	1013760
	.word	0
	.word	1031171
	.word	916484
	.word	1031173
	.word	98348
	.word	1013760
	.word	904428
	.word	1027075
	.word	0
	.word	1013760
	.word	0
	.word	1013760
	.word	1027075
	.word	916484
	.word	1031173
	.word	0
	.word	1013760
	.word	1035269
	.word	1031168
	.word	916712
	.word	1031172
	.word	23807
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	98348
	.word	1013760
	.word	916484
	.word	1031170
	.word	1007616
	.word	1018885
	.word	18687
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	1018880
	.word	1007616
	.word	18432
	.word	20480
	.word	916688
	.word	1031175
	.word	23552
	.word	916696
	.word	1027078
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	108112
	.word	917096
	.word	1031174
	.word	917076
	.word	1027078
	.word	25600
	.word	1018887
	.word	23553
	.word	908752
	.word	19456
	.word	22528
	.word	1013760
	.word	108112
	.word	917096
	.word	1031175
	.word	917076
	.word	1027079
	.word	25601
	.word	108108
	.word	917076
	.word	222628
	.word	19456
	.word	917068
	.word	917072
	.word	1027086
	.word	917068
	.word	1027080
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	23552
	.word	917068
	.word	1027080
	.word	0
	.word	0
	.word	1013760
	.word	1027080
	.word	23552
	.word	0
	.word	1013760
	.word	19457
	.word	20480
	.word	916756
	.word	916908
	.word	916844
	.word	0
	.word	1027083
	.word	917068
	.word	1027082
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	916844
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	989193
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	989194
	.word	1018891
	.word	113316
	.word	112296
	.word	1031179
	.word	310092
	.word	113572
	.word	0
	.word	0
	.word	69916
	.word	0
	.word	23552
	.word	1013760
	.word	988170
	.word	23553
	.word	0
	.word	917068
	.word	1027085
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	916844
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	1013760
	.word	989195
	.word	105120
	.word	595340
	.word	105112
	.word	916816
	.word	185196
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	1013760
	.word	989196
	.word	1018894
	.word	113316
	.word	112296
	.word	1031182
	.word	310092
	.word	113572
	.word	0
	.word	0
	.word	69916
	.word	0
	.word	0
	.word	1013760
	.word	0
	.word	1013760
	.word	988173
	.word	19456
	.word	917068
	.word	19456
	.word	917068
	.word	917064
	.word	1027086
	.word	0
	.word	0
	.word	1013760
	.word	1018894
	.word	23552
	.word	1027087
	.word	0
	.word	0
	.word	0
	.word	1013760
	.word	916712
	.word	23556
	.word	0
	.word	1027087
	.word	0
	.word	0
	.word	1013760
	.word	999424
	.word	999424
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65537
	.word	1900544
	.word	513
	.word	1537
	.word	352782197
	.word	352782197
	.word	65536
	.word	131074
	.word	4
	.word	0
	.word	65537
	.word	131073
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	131074
	.word	2
	.word	327686
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	131072
	.word	1
	.word	131072
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65538
	.word	1
	.word	0
	.word	0
	.word	131072
	.word	131073
	.word	131073
	.word	1
	.word	131072
	.word	1
	.word	131072
	.word	131073
	.word	131073
	.word	1
	.word	0
	.word	0
	.word	2
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	3
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	524289
	.word	4196352
	.word	1048608
	.word	8396800
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65536
	.word	0
	.word	65536
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65536
	.word	65537
	.word	65537
	.word	1
	.word	65536
	.word	1
	.word	65536
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	131073
	.word	33554688
	.word	1073741828
	.word	132096
	.word	65540
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	g_h264_firmware, %object
	.size	g_h264_firmware, 17920
g_h264_firmware:
	.word	0
	.word	823064910
	.word	8419328
	.word	9239400
	.word	16349184
	.word	285670144
	.word	33128448
	.word	-1879048192
	.word	1342177280
	.word	0
	.word	8420384
	.word	8420386
	.word	8420387
	.word	8420388
	.word	8420389
	.word	8420390
	.word	8420391
	.word	8420393
	.word	8420394
	.word	8420395
	.word	8420392
	.word	8420396
	.word	8715424
	.word	8715428
	.word	8682668
	.word	8682542
	.word	8682671
	.word	268435456
	.word	8420385
	.word	-1342177280
	.word	24673452
	.word	-268435456
	.word	24673326
	.word	1610612736
	.word	17234198
	.word	0
	.word	-2130020076
	.word	33259520
	.word	1610612736
	.word	1091206148
	.word	33259520
	.word	1610612736
	.word	17234274
	.word	822770726
	.word	33259520
	.word	1610612736
	.word	33325056
	.word	1610612736
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-2147483648
	.word	268435456
	.word	16349184
	.word	277150492
	.word	9239324
	.word	805306368
	.word	8419328
	.word	0
	.word	805306368
	.word	8419328
	.word	17234796
	.word	17758530
	.word	0
	.word	-268435456
	.word	1342177280
	.word	-235044864
	.word	1628371250
	.word	0
	.word	17464358
	.word	0
	.word	-235044864
	.word	1610612736
	.word	0
	.word	536870912
	.word	1610612736
	.word	24673326
	.word	-536870912
	.word	17234200
	.word	0
	.word	-2130020076
	.word	33259520
	.word	1610612736
	.word	1091206148
	.word	33259520
	.word	1610612736
	.word	17234274
	.word	822770726
	.word	33259520
	.word	1610612736
	.word	33325056
	.word	1610612736
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	1879048192
	.word	0
	.word	16349184
	.word	277150492
	.word	9239324
	.word	805306368
	.word	8419328
	.word	0
	.word	805306368
	.word	8419328
	.word	17234796
	.word	17758530
	.word	0
	.word	-268435456
	.word	1342177280
	.word	-235044864
	.word	1628371250
	.word	0
	.word	17464358
	.word	0
	.word	-235044864
	.word	-536870912
	.word	268435456
	.word	536870912
	.word	1610612736
	.word	24673455
	.word	1610612736
	.word	24935457
	.word	1610612736
	.word	24706208
	.word	1610612736
	.word	0
	.word	536870912
	.word	16349184
	.word	17758488
	.word	8715034
	.word	9239322
	.word	0
	.word	17234228
	.word	17758984
	.word	17758980
	.word	268435456
	.word	0
	.word	-234913792
	.word	1342177280
	.word	21428994
	.word	23525654
	.word	21952790
	.word	20904718
	.word	17758520
	.word	0
	.word	17234288
	.word	18282794
	.word	18807142
	.word	-2147483648
	.word	19331382
	.word	17235072
	.word	18283652
	.word	0
	.word	8715418
	.word	0
	.word	9763996
	.word	33325056
	.word	-1610612736
	.word	18282774
	.word	824113430
	.word	9239710
	.word	17235098
	.word	1610612736
	.word	16349184
	.word	9239710
	.word	17235098
	.word	17758988
	.word	0
	.word	805306368
	.word	17235098
	.word	18283278
	.word	18807964
	.word	0
	.word	805306368
	.word	18283278
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33128448
	.word	-1879048192
	.word	33128448
	.word	-1861813906
	.word	33128448
	.word	822540652
	.word	33128448
	.word	-536870912
	.word	0
	.word	-1073741824
	.word	24673280
	.word	805306368
	.word	16349184
	.word	17234704
	.word	19037185
	.word	-2129725162
	.word	18282848
	.word	18807144
	.word	-2147483648
	.word	805306368
	.word	805306368
	.word	24673296
	.word	805306368
	.word	16349184
	.word	17234706
	.word	19037201
	.word	-2129725088
	.word	18282848
	.word	18807144
	.word	-2147483648
	.word	805306368
	.word	17235098
	.word	17759388
	.word	18283678
	.word	8715424
	.word	9239714
	.word	9764004
	.word	14711981
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	21952864
	.word	-2147483648
	.word	16349184
	.word	17234228
	.word	17758984
	.word	0
	.word	17758980
	.word	268435456
	.word	33062912
	.word	-2147483648
	.word	-235175936
	.word	0
	.word	-235110400
	.word	-2147483648
	.word	16349184
	.word	17234288
	.word	17758978
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	16349184
	.word	20904718
	.word	17758520
	.word	0
	.word	19331382
	.word	17235072
	.word	0
	.word	0
	.word	8715420
	.word	16349184
	.word	17235100
	.word	17758982
	.word	0
	.word	17758988
	.word	33259520
	.word	-805306368
	.word	17235100
	.word	17758982
	.word	805306368
	.word	18282774
	.word	18807062
	.word	1879048192
	.word	17235100
	.word	17758988
	.word	0
	.word	0
	.word	805306368
	.word	17235100
	.word	18283278
	.word	18807558
	.word	0
	.word	805306368
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33128448
	.word	1073741824
	.word	33128448
	.word	1073741824
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420524
	.word	24706208
	.word	-2147483648
	.word	17759396
	.word	33521664
	.word	-536870912
	.word	17235104
	.word	17759396
	.word	18282774
	.word	18807062
	.word	-1879048192
	.word	16349184
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	17235104
	.word	18283278
	.word	18807970
	.word	0
	.word	805306368
	.word	18283278
	.word	-1073741824
	.word	268435456
	.word	17988648
	.word	286194026
	.word	33390592
	.word	0
	.word	536870912
	.word	33390592
	.word	-2147483648
	.word	268435456
	.word	1879048192
	.word	268435456
	.word	268435456
	.word	8420524
	.word	0
	.word	0
	.word	8420398
	.word	0
	.word	16349184
	.word	17234708
	.word	8715430
	.word	17758498
	.word	0
	.word	8715432
	.word	17758488
	.word	18807562
	.word	1073741824
	.word	0
	.word	805306368
	.word	8419328
	.word	16940070
	.word	17758514
	.word	0
	.word	-250676968
	.word	-268435456
	.word	1342177280
	.word	17758488
	.word	-268435456
	.word	1610612736
	.word	0
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715104
	.word	268435456
	.word	-536870912
	.word	8715106
	.word	16349184
	.word	17234708
	.word	805306368
	.word	10516480
	.word	8715108
	.word	17235088
	.word	8715110
	.word	17234214
	.word	8715120
	.word	17234244
	.word	8715118
	.word	16940060
	.word	-268435456
	.word	-805306368
	.word	17464339
	.word	-268435456
	.word	-1073741824
	.word	17464340
	.word	-268435456
	.word	-1323894504
	.word	17464322
	.word	0
	.word	-268435456
	.word	-1610612736
	.word	17464324
	.word	-268435456
	.word	268435456
	.word	24673285
	.word	-2147483648
	.word	17758486
	.word	805306368
	.word	24673316
	.word	-512197595
	.word	-1055983330
	.word	805306368
	.word	17758488
	.word	805306368
	.word	24673286
	.word	286193958
	.word	805306368
	.word	17758486
	.word	805306368
	.word	-536870912
	.word	17464323
	.word	0
	.word	8715328
	.word	17235110
	.word	18282776
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	17234710
	.word	8715330
	.word	1090976934
	.word	0
	.word	286718232
	.word	18807144
	.word	-2147483648
	.word	17235112
	.word	8715332
	.word	1090976934
	.word	0
	.word	555153688
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	17234712
	.word	8715334
	.word	-2130248538
	.word	0
	.word	823589144
	.word	18807144
	.word	-2147483648
	.word	17235090
	.word	8715336
	.word	16940202
	.word	8715338
	.word	17235092
	.word	33259520
	.word	-1610612736
	.word	0
	.word	8715340
	.word	17235094
	.word	8715342
	.word	16940203
	.word	8715344
	.word	17235096
	.word	33259520
	.word	805306368
	.word	0
	.word	8715346
	.word	-1593672675
	.word	17464365
	.word	0
	.word	-268435456
	.word	-1342177280
	.word	822770723
	.word	0
	.word	-268435456
	.word	-1879048192
	.word	17464353
	.word	0
	.word	8715348
	.word	-251495381
	.word	0
	.word	-268435456
	.word	1628077098
	.word	0
	.word	-268435456
	.word	268435456
	.word	17464327
	.word	-536870912
	.word	17464354
	.word	18807064
	.word	33128448
	.word	0
	.word	33128448
	.word	536870912
	.word	1091500310
	.word	268435456
	.word	1073741824
	.word	536870912
	.word	1073741824
	.word	0
	.word	8715350
	.word	17235112
	.word	1092024672
	.word	18807144
	.word	-2147483648
	.word	16940070
	.word	17758514
	.word	0
	.word	-268435456
	.word	8715352
	.word	17235112
	.word	0
	.word	-1055459048
	.word	18807144
	.word	-2147483648
	.word	0
	.word	8715354
	.word	-1056506712
	.word	0
	.word	-787023592
	.word	18807144
	.word	-2147483648
	.word	0
	.word	554173952
	.word	17827336
	.word	1879048192
	.word	-251200684
	.word	0
	.word	8420526
	.word	822609408
	.word	17827352
	.word	1879048192
	.word	-1073741824
	.word	11566081
	.word	-250446847
	.word	33325056
	.word	-805306368
	.word	17988609
	.word	33325056
	.word	-805306368
	.word	20085934
	.word	554203411
	.word	33128448
	.word	0
	.word	33128448
	.word	0
	.word	-2130151150
	.word	33128448
	.word	0
	.word	33128448
	.word	0
	.word	-519538416
	.word	33128448
	.word	0
	.word	33128448
	.word	16808209
	.word	33128448
	.word	0
	.word	-805306368
	.word	1091074311
	.word	33128448
	.word	-1342177280
	.word	33128448
	.word	-1342177280
	.word	-1593280239
	.word	33128448
	.word	-1342177280
	.word	33128448
	.word	-1342177280
	.word	-805306368
	.word	-1073741824
	.word	11566082
	.word	17827329
	.word	0
	.word	0
	.word	33390592
	.word	-805306368
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-805306368
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	0
	.word	33390592
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	268435456
	.word	33390592
	.word	-268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1073741824
	.word	-2128083448
	.word	0
	.word	0
	.word	33128448
	.word	805306368
	.word	-805306368
	.word	18282786
	.word	0
	.word	17758564
	.word	0
	.word	0
	.word	33128448
	.word	1879048192
	.word	0
	.word	286193948
	.word	0
	.word	33062912
	.word	-1073741824
	.word	-1342177280
	.word	-234881024
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-2128083448
	.word	0
	.word	0
	.word	33128448
	.word	536870912
	.word	-805306368
	.word	18282786
	.word	0
	.word	17758564
	.word	0
	.word	0
	.word	33128448
	.word	1610612736
	.word	0
	.word	286193964
	.word	0
	.word	33062912
	.word	-1342177280
	.word	-1610612736
	.word	-536870912
	.word	-268435456
	.word	268435456
	.word	8420354
	.word	-1073741824
	.word	11566088
	.word	-1073741824
	.word	33259520
	.word	1342177280
	.word	-805306368
	.word	-1073741824
	.word	11566089
	.word	0
	.word	33128448
	.word	268435456
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	-805306368
	.word	-805306368
	.word	-1073741824
	.word	11566091
	.word	-1073741824
	.word	33521664
	.word	-805306368
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	17234772
	.word	8420362
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	1879048192
	.word	1879048192
	.word	-1073741824
	.word	11566254
	.word	-268435456
	.word	33259520
	.word	-805306368
	.word	0
	.word	33521664
	.word	-805306368
	.word	16940206
	.word	0
	.word	1879048192
	.word	-1342177280
	.word	-1073741824
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	-1073741824
	.word	11566083
	.word	286193960
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	-1073741824
	.word	11566084
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566085
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	0
	.word	33128448
	.word	1610612736
	.word	-2147483648
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566086
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	286193946
	.word	20085764
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	825392131
	.word	33325056
	.word	-805306368
	.word	0
	.word	0
	.word	8420358
	.word	286193956
	.word	20085764
	.word	33325056
	.word	-805306368
	.word	33062912
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566087
	.word	24673455
	.word	-805306368
	.word	822609409
	.word	17827329
	.word	1879048192
	.word	268435456
	.word	8420352
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420352
	.word	0
	.word	-1073741824
	.word	11566097
	.word	17827583
	.word	33325056
	.word	-1342177280
	.word	33259520
	.word	-1342177280
	.word	-1073741824
	.word	11566098
	.word	17827359
	.word	33325056
	.word	-1342177280
	.word	33259520
	.word	-1342177280
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-2147483648
	.word	268435456
	.word	16349184
	.word	17758992
	.word	19037202
	.word	-2130249450
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935424
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566099
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566101
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	-1073741824
	.word	0
	.word	33390592
	.word	-1342177280
	.word	-1073741824
	.word	11566103
	.word	-268435456
	.word	33259520
	.word	-1342177280
	.word	-1073741824
	.word	11566104
	.word	-268435456
	.word	33259520
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566106
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827330
	.word	1879048192
	.word	20380500
	.word	11566107
	.word	822609408
	.word	17827330
	.word	1879048192
	.word	805306368
	.word	33062912
	.word	-1342177280
	.word	-805306368
	.word	11566109
	.word	-805306368
	.word	-805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566105
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566100
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566102
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	17234198
	.word	8420380
	.word	822541470
	.word	17759062
	.word	0
	.word	33521664
	.word	805306368
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566108
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935452
	.word	805306368
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	33390592
	.word	268435456
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	17235102
	.word	17759062
	.word	33521664
	.word	-536870912
	.word	-268435456
	.word	0
	.word	8420380
	.word	805306368
	.word	268435456
	.word	8420380
	.word	24673455
	.word	-1342177280
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	268435456
	.word	8420368
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420368
	.word	0
	.word	-1073741824
	.word	11566113
	.word	17758528
	.word	33062912
	.word	268435456
	.word	-1073741824
	.word	536870912
	.word	33128448
	.word	1610612736
	.word	1073741824
	.word	33128448
	.word	1610612736
	.word	1879048192
	.word	33128448
	.word	1610612736
	.word	-1879048192
	.word	33128448
	.word	1610612736
	.word	0
	.word	33128448
	.word	-1879048192
	.word	805306368
	.word	33128448
	.word	-1879048192
	.word	1342177280
	.word	33128448
	.word	-1879048192
	.word	-2147483648
	.word	33128448
	.word	-1879048192
	.word	268435456
	.word	33128448
	.word	-1073741824
	.word	1610612736
	.word	33128448
	.word	-1073741824
	.word	268435456
	.word	536870912
	.word	8944674
	.word	-536870912
	.word	0
	.word	8944674
	.word	-536870912
	.word	268435456
	.word	8944674
	.word	-1073741824
	.word	11566112
	.word	-268435456
	.word	33259520
	.word	268435456
	.word	16349184
	.word	286194442
	.word	805306368
	.word	0
	.word	33128448
	.word	-1610612736
	.word	805306368
	.word	16349184
	.word	17758994
	.word	19037216
	.word	-2130249376
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935440
	.word	268435456
	.word	16349184
	.word	17758992
	.word	19037202
	.word	-2130249450
	.word	18282848
	.word	18807142
	.word	-2147483648
	.word	24935424
	.word	268435456
	.word	822609408
	.word	1092254728
	.word	0
	.word	1879048192
	.word	0
	.word	8420388
	.word	8420389
	.word	24673285
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566116
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673316
	.word	1879048192
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566117
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	16940035
	.word	17464324
	.word	-268435456
	.word	-268435456
	.word	-2147483648
	.word	8420390
	.word	24673285
	.word	-1610612736
	.word	24673316
	.word	-1610612736
	.word	554335270
	.word	-2147483648
	.word	8420390
	.word	554335236
	.word	-268435456
	.word	-2147483648
	.word	268435456
	.word	0
	.word	8420356
	.word	285375524
	.word	17464326
	.word	0
	.word	8420391
	.word	1359641640
	.word	33390592
	.word	1342177280
	.word	-1073741824
	.word	17758528
	.word	33259520
	.word	268435456
	.word	17464329
	.word	33390592
	.word	536870912
	.word	822609408
	.word	1092254731
	.word	0
	.word	1879048192
	.word	16940053
	.word	285899812
	.word	0
	.word	33521664
	.word	536870912
	.word	1879048192
	.word	16940041
	.word	285899786
	.word	0
	.word	33521664
	.word	-536870912
	.word	1879048192
	.word	16940053
	.word	285899812
	.word	0
	.word	33521664
	.word	-536870912
	.word	1879048192
	.word	24935446
	.word	1073741824
	.word	-1073741824
	.word	0
	.word	33259520
	.word	268435456
	.word	285899810
	.word	33390592
	.word	-536870912
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	17234772
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	16940055
	.word	17464344
	.word	8420394
	.word	8944683
	.word	554335266
	.word	33128448
	.word	1610612736
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566121
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935465
	.word	1610612736
	.word	-1073741824
	.word	11566122
	.word	285899810
	.word	33390592
	.word	1610612736
	.word	-1073741824
	.word	11566123
	.word	554335266
	.word	33390592
	.word	-1342177280
	.word	0
	.word	8420394
	.word	285899810
	.word	33128448
	.word	0
	.word	0
	.word	8420395
	.word	554335266
	.word	33390592
	.word	1073741824
	.word	1610612736
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935598
	.word	1610612736
	.word	0
	.word	554335274
	.word	0
	.word	-1073741824
	.word	805306368
	.word	33259520
	.word	268435456
	.word	805306368
	.word	33128448
	.word	1610612736
	.word	0
	.word	33128448
	.word	536870912
	.word	268435456
	.word	33128448
	.word	536870912
	.word	536870912
	.word	33128448
	.word	1073741824
	.word	1342177280
	.word	1879048192
	.word	1342177280
	.word	1879048192
	.word	268435456
	.word	285899810
	.word	33390592
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24935598
	.word	-1342177280
	.word	0
	.word	554335275
	.word	0
	.word	-1073741824
	.word	805306368
	.word	33259520
	.word	268435456
	.word	805306368
	.word	33128448
	.word	-1342177280
	.word	0
	.word	33128448
	.word	1879048192
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	-1879048192
	.word	-1610612736
	.word	1879048192
	.word	-1610612736
	.word	1879048192
	.word	1610612736
	.word	17464354
	.word	286948379
	.word	33390592
	.word	293108762
	.word	-2147483648
	.word	1879048192
	.word	17464354
	.word	33390592
	.word	1879048192
	.word	-235044864
	.word	1879048192
	.word	-2147483648
	.word	536870912
	.word	-1073741824
	.word	24673282
	.word	-1073741824
	.word	-1073741824
	.word	17464362
	.word	268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-805306368
	.word	-805306368
	.word	24673282
	.word	-1342177280
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-1342177280
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-268435456
	.word	285899810
	.word	17988635
	.word	33390592
	.word	536870912
	.word	-235044864
	.word	536870912
	.word	17464363
	.word	268435456
	.word	0
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	268435456
	.word	-805306368
	.word	-805306368
	.word	24673282
	.word	268435456
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	268435456
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	-805306368
	.word	1342177280
	.word	24673324
	.word	-536870912
	.word	1359641640
	.word	33390592
	.word	-1342177280
	.word	822609408
	.word	17827330
	.word	1879048192
	.word	-536870912
	.word	554173952
	.word	17827329
	.word	1879048192
	.word	20380500
	.word	11566254
	.word	822609408
	.word	17827329
	.word	1879048192
	.word	24673454
	.word	-536870912
	.word	-1073741824
	.word	11566254
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	536870912
	.word	33128448
	.word	1879048192
	.word	1073741824
	.word	33128448
	.word	1879048192
	.word	1610612736
	.word	33128448
	.word	1879048192
	.word	805306368
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	-1073741824
	.word	-1342177280
	.word	-1073741824
	.word	-1073741824
	.word	16940206
	.word	33259520
	.word	1342177280
	.word	24673299
	.word	-1073741824
	.word	16940066
	.word	33128448
	.word	1879048192
	.word	268435456
	.word	33128448
	.word	1879048192
	.word	-1073741824
	.word	-1073741824
	.word	11566115
	.word	805306368
	.word	33062912
	.word	268435456
	.word	-805306368
	.word	11566125
	.word	24935449
	.word	-1879048192
	.word	-1073741824
	.word	536870912
	.word	33259520
	.word	268435456
	.word	17827329
	.word	33128448
	.word	-1879048192
	.word	-805306368
	.word	-805306368
	.word	24673455
	.word	268435456
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	268435456
	.word	8420398
	.word	0
	.word	822609409
	.word	17827328
	.word	1879048192
	.word	0
	.word	8420398
	.word	0
	.word	1073741824
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	268435456
	.word	8420527
	.word	0
	.word	1073741824
	.word	11565056
	.word	19331386
	.word	20379926
	.word	33390592
	.word	-536870912
	.word	20379926
	.word	11336516
	.word	11860806
	.word	19855676
	.word	0
	.word	805306368
	.word	11336520
	.word	9239370
	.word	9763660
	.word	11860814
	.word	10287952
	.word	-536870912
	.word	20379926
	.word	11336516
	.word	0
	.word	0
	.word	11336518
	.word	19855676
	.word	0
	.word	805306368
	.word	11336520
	.word	9239370
	.word	11860812
	.word	19855676
	.word	0
	.word	805306368
	.word	11336526
	.word	10287952
	.word	268435456
	.word	8715074
	.word	0
	.word	1073741824
	.word	11565056
	.word	823064854
	.word	18282784
	.word	1879048192
	.word	554629398
	.word	18282848
	.word	1879048192
	.word	-251200684
	.word	17758502
	.word	1342177280
	.word	9468968
	.word	9993260
	.word	823064854
	.word	18282848
	.word	1879048192
	.word	0
	.word	0
	.word	33390592
	.word	-1342177280
	.word	16349184
	.word	-2129724670
	.word	18906285
	.word	-2130249360
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	17235074
	.word	17758488
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715394
	.word	16349184
	.word	-2130248958
	.word	18906285
	.word	-2129725072
	.word	18282782
	.word	18807144
	.word	-2147483648
	.word	1879048192
	.word	16349184
	.word	-2129724670
	.word	19331848
	.word	-268435456
	.word	-2130249360
	.word	18282782
	.word	18807142
	.word	-2147483648
	.word	16349184
	.word	17234694
	.word	17759362
	.word	0
	.word	9239686
	.word	17234694
	.word	17759360
	.word	18283276
	.word	33259520
	.word	-536870912
	.word	805306368
	.word	17235072
	.word	17758988
	.word	18283270
	.word	18283278
	.word	0
	.word	9239684
	.word	17235074
	.word	17758488
	.word	-268435456
	.word	-268435456
	.word	268435456
	.word	0
	.word	8715394
	.word	16349184
	.word	-2130248958
	.word	19331848
	.word	-268435456
	.word	-2129725072
	.word	18282794
	.word	18807144
	.word	-2147483648
	.word	16349184
	.word	287767304
	.word	0
	.word	8715016
	.word	0
	.word	536870912
	.word	10516480
	.word	8715042
	.word	277674784
	.word	546634532
	.word	33128448
	.word	1073741824
	.word	33128448
	.word	-2147483648
	.word	33128448
	.word	-1073741824
	.word	-268435456
	.word	268435456
	.word	8715046
	.word	0
	.word	-268435456
	.word	268435456
	.word	8715048
	.word	0
	.word	-268435456
	.word	268435456
	.word	8715050
	.word	0
	.word	0
	.word	1073741824
	.word	11565056
	.word	20380502
	.word	24935443
	.word	-1879048192
	.word	1898379590
	.word	0
	.word	0
	.word	0
	.word	16349184
	.word	0
	.word	33390592
	.word	-1879048192
	.word	17235104
	.word	17759394
	.word	33259520
	.word	1610612736
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	33259520
	.word	1610612736
	.word	9763988
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235104
	.word	19331386
	.word	0
	.word	19855676
	.word	0
	.word	0
	.word	825162046
	.word	0
	.word	0
	.word	805306368
	.word	11336850
	.word	19855662
	.word	0
	.word	11041962
	.word	0
	.word	10288278
	.word	19331388
	.word	18283278
	.word	0
	.word	805306368
	.word	9993387
	.word	17759394
	.word	0
	.word	805306368
	.word	10288280
	.word	1342177280
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235104
	.word	17758988
	.word	0
	.word	805306368
	.word	0
	.word	17234236
	.word	17758990
	.word	0
	.word	805306368
	.word	0
	.word	19855678
	.word	0
	.word	805306368
	.word	10288274
	.word	19855662
	.word	0
	.word	9993386
	.word	17234702
	.word	17759394
	.word	0
	.word	805306368
	.word	0
	.word	10288276
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	-1073741824
	.word	17235104
	.word	17759396
	.word	-1879048192
	.word	17235100
	.word	17758982
	.word	18283276
	.word	33259520
	.word	1342177280
	.word	17235100
	.word	17758988
	.word	0
	.word	805306368
	.word	33259520
	.word	805306368
	.word	9763988
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235100
	.word	19331386
	.word	0
	.word	19855676
	.word	0
	.word	0
	.word	825162046
	.word	0
	.word	0
	.word	805306368
	.word	11336850
	.word	19855662
	.word	0
	.word	11041962
	.word	0
	.word	10288278
	.word	19331388
	.word	18283278
	.word	0
	.word	805306368
	.word	9993387
	.word	17758982
	.word	823590036
	.word	0
	.word	10288280
	.word	1073741824
	.word	19331386
	.word	18283278
	.word	0
	.word	9763984
	.word	17235100
	.word	17758988
	.word	0
	.word	805306368
	.word	0
	.word	17234236
	.word	17758990
	.word	0
	.word	805306368
	.word	0
	.word	19855678
	.word	0
	.word	805306368
	.word	10288274
	.word	19855662
	.word	0
	.word	9993386
	.word	17234694
	.word	17759388
	.word	18283276
	.word	0
	.word	0
	.word	805306368
	.word	0
	.word	10288276
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	-1073741824
	.word	17235100
	.word	17758982
	.word	805306368
	.word	-1879048192
	.word	19331386
	.word	0
	.word	10288272
	.word	19331388
	.word	0
	.word	805306368
	.word	19331374
	.word	0
	.word	11041962
	.word	0
	.word	9239700
	.word	19331390
	.word	0
	.word	805306368
	.word	11336850
	.word	0
	.word	10288278
	.word	9993387
	.word	10288280
	.word	0
	.word	1090520577
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17758538
	.word	20380498
	.word	18807090
	.word	0
	.word	33128448
	.word	-1055983284
	.word	0
	.word	286194514
	.word	-268435456
	.word	-805306368
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	-1879048192
	.word	-1342177280
	.word	268435456
	.word	8420527
	.word	0
	.word	1090520576
	.word	9992192
	.word	-2147483648
	.word	-1610612736
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17234226
	.word	20380498
	.word	0
	.word	286194514
	.word	-268435456
	.word	-805306368
	.word	18282776
	.word	33128448
	.word	1073741824
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	1073741824
	.word	1610612736
	.word	268435456
	.word	8420527
	.word	0
	.word	18875904
	.word	0
	.word	1091044864
	.word	546863104
	.word	17827332
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17234772
	.word	0
	.word	17455440
	.word	16778756
	.word	33390592
	.word	-1342177280
	.word	1091044864
	.word	815298560
	.word	17827332
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	17303041
	.word	17827336
	.word	33325056
	.word	-1879048192
	.word	17303072
	.word	33062912
	.word	268435456
	.word	285738497
	.word	18351620
	.word	-2147483648
	.word	0
	.word	17827352
	.word	33062912
	.word	1073741824
	.word	17303064
	.word	0
	.word	1091044864
	.word	815298560
	.word	17827352
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	536870912
	.word	1091044864
	.word	815298560
	.word	0
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	-536870912
	.word	1091044864
	.word	815298560
	.word	-2147483648
	.word	0
	.word	-2147483648
	.word	-1610612736
	.word	-268435456
	.word	268435456
	.word	0
	.word	17827329
	.word	0
	.word	8715072
	.word	0
	.word	286194520
	.word	-268435456
	.word	-536870912
	.word	18282776
	.word	33128448
	.word	1342177280
	.word	1879048192
	.word	268435456
	.word	8420527
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1011712
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	916484
	.word	1031168
	.word	1018880
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035272
	.word	0
	.word	1031172
	.word	0
	.word	1027080
	.word	0
	.word	1035361
	.word	16391
	.word	916544
	.word	1031176
	.word	16388
	.word	916544
	.word	1031176
	.word	0
	.word	18432
	.word	916544
	.word	1031176
	.word	916552
	.word	1031176
	.word	1035284
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031171
	.word	1018883
	.word	16384
	.word	17408
	.word	0
	.word	16384
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	593924
	.word	103056
	.word	103056
	.word	905516
	.word	1031176
	.word	589828
	.word	0
	.word	902208
	.word	916588
	.word	1031176
	.word	16384
	.word	1035355
	.word	1018888
	.word	0
	.word	1027079
	.word	0
	.word	1035361
	.word	16391
	.word	916544
	.word	1031176
	.word	16388
	.word	916544
	.word	1031176
	.word	0
	.word	18432
	.word	916544
	.word	1031176
	.word	916552
	.word	1031176
	.word	1035284
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031174
	.word	1018886
	.word	16384
	.word	17408
	.word	0
	.word	16384
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	593924
	.word	103056
	.word	103056
	.word	905516
	.word	1031176
	.word	589828
	.word	0
	.word	902208
	.word	916588
	.word	1031175
	.word	16384
	.word	1035355
	.word	1018888
	.word	0
	.word	1031176
	.word	0
	.word	1027080
	.word	0
	.word	1027080
	.word	16384
	.word	1035355
	.word	0
	.word	16384
	.word	0
	.word	0
	.word	1007616
	.word	0
	.word	0
	.word	589828
	.word	99972
	.word	622596
	.word	901164
	.word	1031182
	.word	0
	.word	109184
	.word	0
	.word	0
	.word	0
	.word	597444
	.word	107044
	.word	100000
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	589840
	.word	98332
	.word	592016
	.word	100508
	.word	0
	.word	902272
	.word	1031178
	.word	0
	.word	67204
	.word	0
	.word	0
	.word	1018891
	.word	17408
	.word	0
	.word	0
	.word	0
	.word	902208
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904392
	.word	69260
	.word	0
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031181
	.word	916612
	.word	1031181
	.word	916608
	.word	1031180
	.word	916608
	.word	1031180
	.word	1018894
	.word	1035295
	.word	0
	.word	1027086
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	98324
	.word	0
	.word	1035359
	.word	1018894
	.word	1035312
	.word	0
	.word	1027086
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	98324
	.word	0
	.word	1035359
	.word	1018894
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	983049
	.word	0
	.word	0
	.word	0
	.word	589828
	.word	0
	.word	99972
	.word	916484
	.word	1031188
	.word	916524
	.word	1031184
	.word	916524
	.word	1031188
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	597444
	.word	0
	.word	0
	.word	589840
	.word	98332
	.word	0
	.word	0
	.word	0
	.word	0
	.word	98308
	.word	0
	.word	916484
	.word	1031184
	.word	0
	.word	0
	.word	67204
	.word	0
	.word	0
	.word	1018897
	.word	0
	.word	0
	.word	902208
	.word	103044
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904400
	.word	69260
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031188
	.word	916612
	.word	1031188
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	0
	.word	1027092
	.word	16384
	.word	916544
	.word	1031186
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1018899
	.word	0
	.word	0
	.word	0
	.word	902208
	.word	67204
	.word	0
	.word	0
	.word	0
	.word	904392
	.word	69260
	.word	0
	.word	1035351
	.word	1035354
	.word	0
	.word	16384
	.word	916608
	.word	1031188
	.word	1018900
	.word	916612
	.word	1031188
	.word	1035322
	.word	1018900
	.word	1035322
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	98308
	.word	0
	.word	0
	.word	0
	.word	102028
	.word	592972
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	589828
	.word	901164
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	69260
	.word	69260
	.word	69260
	.word	606220
	.word	0
	.word	16384
	.word	66176
	.word	0
	.word	0
	.word	0
	.word	20480
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	66176
	.word	66176
	.word	0
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	590920
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	67204
	.word	606212
	.word	1027096
	.word	0
	.word	1018905
	.word	0
	.word	1027096
	.word	1027096
	.word	1018905
	.word	0
	.word	1018905
	.word	0
	.word	1027097
	.word	1018905
	.word	0
	.word	1018905
	.word	67204
	.word	606212
	.word	606212
	.word	0
	.word	0
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	17409
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	17410
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	17414
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	901124
	.word	1031195
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	17408
	.word	901124
	.word	1031196
	.word	16384
	.word	0
	.word	17409
	.word	98308
	.word	98308
	.word	66176
	.word	66176
	.word	18432
	.word	590980
	.word	67204
	.word	67204
	.word	606212
	.word	606212
	.word	0
	.word	18433
	.word	589832
	.word	66176
	.word	66176
	.word	590920
	.word	67204
	.word	67204
	.word	606212
	.word	67204
	.word	606212
	.word	18432
	.word	916552
	.word	1031198
	.word	916556
	.word	1031198
	.word	1018910
	.word	17408
	.word	1018910
	.word	17408
	.word	1018910
	.word	606212
	.word	0
	.word	0
	.word	17410
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	589828
	.word	901164
	.word	0
	.word	17419
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	16384
	.word	0
	.word	17423
	.word	98308
	.word	17410
	.word	0
	.word	1035359
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	17423
	.word	589828
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	0
	.word	16385
	.word	916488
	.word	1031215
	.word	16384
	.word	916608
	.word	1031215
	.word	0
	.word	16388
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16389
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16390
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	916864
	.word	1031202
	.word	1031215
	.word	16390
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	16391
	.word	916864
	.word	1031202
	.word	916868
	.word	1031202
	.word	1018920
	.word	1035374
	.word	0
	.word	17408
	.word	902532
	.word	903560
	.word	605256
	.word	1031215
	.word	1035374
	.word	17408
	.word	902532
	.word	1031215
	.word	1035374
	.word	17408
	.word	902532
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	902532
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	902532
	.word	1031208
	.word	29696
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027110
	.word	20480
	.word	30720
	.word	16384
	.word	916800
	.word	1031206
	.word	1035372
	.word	0
	.word	104840
	.word	104848
	.word	595332
	.word	16384
	.word	906560
	.word	1031206
	.word	103060
	.word	16384
	.word	112696
	.word	917380
	.word	1031206
	.word	1018917
	.word	990244
	.word	29696
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027112
	.word	20480
	.word	30720
	.word	16384
	.word	916800
	.word	1031208
	.word	1035372
	.word	0
	.word	104840
	.word	104848
	.word	595332
	.word	16384
	.word	906560
	.word	1031208
	.word	103060
	.word	16384
	.word	112696
	.word	917380
	.word	1031208
	.word	1018919
	.word	990246
	.word	1018920
	.word	16384
	.word	0
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1027113
	.word	1018927
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031210
	.word	17408
	.word	916868
	.word	1031210
	.word	17408
	.word	916868
	.word	1031211
	.word	1018927
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031211
	.word	1018927
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035376
	.word	1035376
	.word	1035374
	.word	0
	.word	17423
	.word	916868
	.word	1031215
	.word	17408
	.word	916868
	.word	1031211
	.word	29696
	.word	110208
	.word	1035376
	.word	988203
	.word	1035374
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	0
	.word	16384
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	1035374
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	916868
	.word	1031213
	.word	1018926
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	16384
	.word	916864
	.word	1031215
	.word	1018927
	.word	16384
	.word	0
	.word	16384
	.word	0
	.word	916864
	.word	1031215
	.word	916868
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	0
	.word	1031215
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031225
	.word	916872
	.word	1031225
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031225
	.word	916872
	.word	1031225
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031217
	.word	1018929
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	1035374
	.word	17408
	.word	916868
	.word	1031225
	.word	1035374
	.word	0
	.word	17409
	.word	916868
	.word	1031225
	.word	1035374
	.word	0
	.word	17409
	.word	916868
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	17408
	.word	916868
	.word	1031225
	.word	1035372
	.word	0
	.word	1035372
	.word	1035372
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	18432
	.word	0
	.word	901124
	.word	901128
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031225
	.word	20480
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	916880
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	916484
	.word	1031224
	.word	1018935
	.word	16384
	.word	0
	.word	1018937
	.word	16384
	.word	0
	.word	0
	.word	1031225
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	1035374
	.word	0
	.word	0
	.word	916868
	.word	1031254
	.word	1035374
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	17408
	.word	916868
	.word	1031228
	.word	1018966
	.word	17408
	.word	0
	.word	1018940
	.word	17408
	.word	0
	.word	1018940
	.word	17408
	.word	0
	.word	1035374
	.word	0
	.word	17423
	.word	916868
	.word	1031254
	.word	0
	.word	16384
	.word	99972
	.word	590912
	.word	916544
	.word	1031229
	.word	1018941
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031254
	.word	0
	.word	0
	.word	21506
	.word	300368
	.word	99412
	.word	0
	.word	1035359
	.word	0
	.word	1031254
	.word	16384
	.word	18432
	.word	100492
	.word	1035350
	.word	16384
	.word	0
	.word	0
	.word	0
	.word	1031232
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027136
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	98348
	.word	99436
	.word	294916
	.word	0
	.word	0
	.word	1031233
	.word	0
	.word	1031233
	.word	16384
	.word	294916
	.word	0
	.word	16384
	.word	99436
	.word	294916
	.word	17408
	.word	901124
	.word	0
	.word	18432
	.word	49160
	.word	589828
	.word	0
	.word	16384
	.word	916544
	.word	1031234
	.word	1035374
	.word	0
	.word	916868
	.word	1031254
	.word	16384
	.word	916544
	.word	1031235
	.word	16384
	.word	18432
	.word	100492
	.word	1035350
	.word	0
	.word	18432
	.word	50248
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	18432
	.word	50308
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	18432
	.word	50308
	.word	605188
	.word	1031235
	.word	1035376
	.word	0
	.word	1031236
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	16384
	.word	916484
	.word	1031236
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16384
	.word	916544
	.word	1031238
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031238
	.word	1035374
	.word	0
	.word	16384
	.word	916484
	.word	1031238
	.word	1035374
	.word	0
	.word	16384
	.word	916484
	.word	1031238
	.word	16386
	.word	0
	.word	16384
	.word	916484
	.word	1031239
	.word	16386
	.word	0
	.word	16384
	.word	916484
	.word	1031239
	.word	1018953
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031241
	.word	28672
	.word	16384
	.word	108548
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	17408
	.word	916868
	.word	1031241
	.word	17408
	.word	916868
	.word	1031241
	.word	18432
	.word	916872
	.word	1031241
	.word	17408
	.word	916868
	.word	1031241
	.word	1018953
	.word	1035376
	.word	1018953
	.word	1035376
	.word	983112
	.word	16384
	.word	902148
	.word	1031243
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1031243
	.word	28672
	.word	16384
	.word	108548
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	17408
	.word	916868
	.word	1031243
	.word	17408
	.word	916868
	.word	1031243
	.word	18432
	.word	916872
	.word	1031243
	.word	17408
	.word	916868
	.word	1031243
	.word	1018955
	.word	1035376
	.word	1018955
	.word	1035376
	.word	983114
	.word	16384
	.word	18432
	.word	901124
	.word	1031244
	.word	1031244
	.word	1018956
	.word	0
	.word	916612
	.word	1031244
	.word	130284
	.word	1031244
	.word	1018956
	.word	1018961
	.word	1035374
	.word	0
	.word	1027148
	.word	1035374
	.word	28672
	.word	16384
	.word	108548
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027149
	.word	1035372
	.word	1035372
	.word	0
	.word	1027150
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027150
	.word	1035372
	.word	1035372
	.word	1035372
	.word	1035372
	.word	983116
	.word	16384
	.word	0
	.word	916484
	.word	1031249
	.word	916652
	.word	1031249
	.word	28672
	.word	16384
	.word	108548
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027152
	.word	1035372
	.word	1035372
	.word	0
	.word	1027153
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027153
	.word	1035372
	.word	1035372
	.word	1035372
	.word	1035372
	.word	983119
	.word	0
	.word	1027155
	.word	16384
	.word	916544
	.word	1031249
	.word	16384
	.word	0
	.word	1035350
	.word	1018963
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	0
	.word	1027155
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	17408
	.word	916868
	.word	1031251
	.word	1018963
	.word	1035374
	.word	1018963
	.word	1035374
	.word	1035374
	.word	17408
	.word	916484
	.word	1031250
	.word	0
	.word	1027156
	.word	17408
	.word	916484
	.word	1031252
	.word	18432
	.word	916488
	.word	1031252
	.word	1018964
	.word	1035374
	.word	0
	.word	17408
	.word	916868
	.word	1031254
	.word	1035372
	.word	0
	.word	0
	.word	1031253
	.word	1035374
	.word	17408
	.word	916868
	.word	1031254
	.word	0
	.word	916872
	.word	1031253
	.word	1035372
	.word	1035372
	.word	0
	.word	1031254
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	999424
	.word	19456
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031255
	.word	1018967
	.word	16384
	.word	0
	.word	999424
	.word	22528
	.word	0
	.word	0
	.word	0
	.word	916632
	.word	1031256
	.word	594960
	.word	0
	.word	0
	.word	0
	.word	594964
	.word	71316
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	1018969
	.word	595088
	.word	0
	.word	593936
	.word	906516
	.word	0
	.word	0
	.word	594964
	.word	71316
	.word	0
	.word	0
	.word	0
	.word	0
	.word	595092
	.word	71316
	.word	0
	.word	0
	.word	16384
	.word	0
	.word	999424
	.word	22528
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	16384
	.word	0
	.word	1035350
	.word	17409
	.word	591876
	.word	98944
	.word	592900
	.word	0
	.word	16384
	.word	0
	.word	1035350
	.word	999424
	.word	17408
	.word	916484
	.word	1031260
	.word	0
	.word	21504
	.word	0
	.word	300368
	.word	99652
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	67204
	.word	67204
	.word	67204
	.word	606212
	.word	0
	.word	0
	.word	21504
	.word	0
	.word	300368
	.word	98624
	.word	0
	.word	1035359
	.word	1018975
	.word	0
	.word	21504
	.word	0
	.word	905516
	.word	300368
	.word	99652
	.word	0
	.word	1035359
	.word	0
	.word	0
	.word	0
	.word	99392
	.word	0
	.word	0
	.word	0
	.word	99392
	.word	916552
	.word	1031261
	.word	1018974
	.word	0
	.word	0
	.word	902208
	.word	902276
	.word	99460
	.word	0
	.word	0
	.word	0
	.word	67204
	.word	67204
	.word	67204
	.word	606212
	.word	0
	.word	0
	.word	21504
	.word	0
	.word	905516
	.word	300368
	.word	98624
	.word	0
	.word	1035359
	.word	0
	.word	16384
	.word	98560
	.word	0
	.word	999424
	.word	20480
	.word	0
	.word	20480
	.word	21504
	.word	22528
	.word	916688
	.word	1031264
	.word	916692
	.word	1031264
	.word	916696
	.word	1031264
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	1018976
	.word	16384
	.word	0
	.word	1013760
	.word	999424
	.word	22528
	.word	0
	.word	0
	.word	108184
	.word	1031265
	.word	19456
	.word	104664
	.word	596248
	.word	108184
	.word	0
	.word	17408
	.word	916484
	.word	1031270
	.word	0
	.word	0
	.word	916544
	.word	1031270
	.word	104088
	.word	0
	.word	903232
	.word	68232
	.word	903316
	.word	1027172
	.word	0
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	594176
	.word	905480
	.word	595264
	.word	102676
	.word	70288
	.word	102680
	.word	595220
	.word	104084
	.word	0
	.word	0
	.word	595220
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	593040
	.word	69260
	.word	0
	.word	0
	.word	904264
	.word	69260
	.word	0
	.word	1018982
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	903232
	.word	68232
	.word	903560
	.word	108168
	.word	0
	.word	589828
	.word	66176
	.word	100480
	.word	0
	.word	593044
	.word	102028
	.word	0
	.word	0
	.word	593044
	.word	0
	.word	0
	.word	0
	.word	904256
	.word	69260
	.word	904420
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	1018988
	.word	0
	.word	0
	.word	1018987
	.word	0
	.word	0
	.word	98308
	.word	916608
	.word	1031275
	.word	104088
	.word	0
	.word	903232
	.word	68232
	.word	903316
	.word	1027177
	.word	0
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	594176
	.word	905480
	.word	595264
	.word	102676
	.word	70288
	.word	102680
	.word	595220
	.word	104084
	.word	0
	.word	0
	.word	595220
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	593040
	.word	69260
	.word	0
	.word	0
	.word	67204
	.word	904264
	.word	0
	.word	1018987
	.word	0
	.word	0
	.word	592136
	.word	0
	.word	0
	.word	0
	.word	903232
	.word	68232
	.word	903560
	.word	108168
	.word	0
	.word	589828
	.word	66176
	.word	100480
	.word	0
	.word	593044
	.word	102028
	.word	0
	.word	0
	.word	593044
	.word	0
	.word	0
	.word	0
	.word	0
	.word	903300
	.word	904200
	.word	69260
	.word	904420
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	1018988
	.word	0
	.word	0
	.word	67204
	.word	1018987
	.word	0
	.word	592912
	.word	0
	.word	0
	.word	592912
	.word	69260
	.word	101592
	.word	595152
	.word	0
	.word	902244
	.word	0
	.word	0
	.word	595152
	.word	104084
	.word	0
	.word	19456
	.word	0
	.word	0
	.word	0
	.word	999424
	.word	19456
	.word	17408
	.word	66176
	.word	67204
	.word	606212
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	0
	.word	590936
	.word	596184
	.word	916544
	.word	1031277
	.word	612440
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031278
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031278
	.word	1018990
	.word	16384
	.word	0
	.word	999424
	.word	19456
	.word	17408
	.word	66176
	.word	67204
	.word	606212
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	0
	.word	595992
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031280
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031280
	.word	1018992
	.word	16384
	.word	0
	.word	999424
	.word	21504
	.word	22528
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	113280
	.word	0
	.word	102660
	.word	916544
	.word	1031282
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	0
	.word	104836
	.word	916872
	.word	1031280
	.word	104080
	.word	916804
	.word	1031285
	.word	70288
	.word	102660
	.word	295128
	.word	905472
	.word	104080
	.word	916628
	.word	1031284
	.word	0
	.word	905476
	.word	19456
	.word	16384
	.word	0
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	1018995
	.word	19456
	.word	16384
	.word	101008
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	1018997
	.word	19456
	.word	16384
	.word	299224
	.word	903504
	.word	66176
	.word	67204
	.word	68232
	.word	68232
	.word	606212
	.word	606216
	.word	606216
	.word	0
	.word	1013760
	.word	16384
	.word	99972
	.word	99972
	.word	589888
	.word	916608
	.word	1031286
	.word	1018998
	.word	16384
	.word	0
	.word	999424
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	65537
	.word	7208960
	.word	513
	.word	1537
	.word	319365736
	.word	319365736
	.word	9437306
	.word	5046372
	.word	0
	.word	0
	.word	1
	.word	131
	.word	16
	.word	2
	.word	24
	.word	256
	.word	263
	.word	3
	.word	351
	.word	4
	.word	64
	.word	127
	.word	262143
	.word	1048575
	.word	4194303
	.word	2147483647
	.word	-2147483648
	.word	-16
	.word	15
	.word	-128
	.word	8192
	.word	1048576
	.word	96000
	.word	-8
	.word	-1
	.word	262144
	.word	-524288
	.word	65280000
	.word	196612
	.word	131074
	.word	65537
	.word	65537
	.word	0
	.word	0
	.word	0
	.word	0
	.word	8
	.word	8160
	.word	255
	.word	0
	.word	1
	.word	5
	.word	8
	.word	7
	.word	64
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.type	g_pScdDrvParamBase, %object
	.size	g_pScdDrvParamBase, 8
g_pScdDrvParamBase:
	.xword	g_ScdDrvParam
	.type	g_hex_flag, %object
	.size	g_hex_flag, 4
g_hex_flag:
	.word	1
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC4:
	ASCII(.string	"line: %d, p = NULL is not expected value!\n" )
	.zero	5
.LC9:
	ASCII(.string	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\n" )
	.zero	5
.LC14:
	ASCII(.string	"Warn: eVidStd = %d have not DSP vfmw bin file!!\n" )
	.zero	7
.LC17:
	ASCII(.string	"%s failed!\n" )
	.zero	4
.LC19:
	ASCII(.string	"%s success!\n" )
	.zero	3
.LC28:
	ASCII(.string	"Ignore the reset request when the SCD[%d] clock is closed.\n" )
	.zero	4
.LC30:
	ASCII(.string	"SCD[%d]   ResetSCD ERROR!!!\n" )
	.zero	3
.LC40:
	ASCII(.string	"line: %d Get SmID fail!" )
.LC42:
	ASCII(.string	"DelRaw err PacketNum = %d, DelNum = %d\n" )
.LC45:
	ASCII(.string	"%s release RawPhyAddr = 0x%x, Len = %d\n" )
.LC49:
	ASCII(.string	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = %d,Next Length = %d,is_extern_eop_flag = %d\n\n" )
	.zero	7
.LC51:
	ASCII(.string	"line: %d DelNum = %d,RawPacketOffSet = %d,Next Length = %d\n\n" )
	.zero	3
.LC54:
	ASCII(.string	"line: %d pSmInstArray is NULL!\n" )
.LC63:
	ASCII(.string	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLastSeg=%d\n" )
	.zero	5
.LC65:
	ASCII(.string	"-------- forece release seg[%d] -----------\n" )
	.zero	3
.LC67:
	ASCII(.string	"\n" )
	.zero	6
.LC69:
	ASCII(.string	"0x%02x," )
.LC71:
	ASCII(.string	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d StreamID=%d\n" )
	.zero	4
.LC74:
	ASCII(.string	"Array out of bound in function %s\n" )
	.zero	5
.LC88:
	ASCII(.string	"ScdId is wrong! %s error\n" )
	.zero	6
.LC93:
	ASCII(.string	"%s: g_hex_base_vir_addr = NULL\n" )
.LC100:
	ASCII(.string	"line: %d, SmID = %d is not expected!\n" )
	.zero	2
.LC102:
	ASCII(.string	"line: %d, SmID = %d, ScdId = %d is not expected!\n" )
	.zero	6
.LC110:
	ASCII(.string	"Raw packet TOO BIG! Can't copy to seg! Len: 0x%x\n" )
	.zero	6
.LC112:
	ASCII(.string	"line: %d, delet raw failed!\n" )
	.zero	3
.LC115:
	ASCII(.string	"[%s %d] VirAddr is null!!\n" )
	.zero	5
.LC120:
	ASCII(.string	"copy raw to seg fail\n" )
	.zero	2
.LC135:
	ASCII(.string	"Cann't Start SCD, Ret = %d\n" )
	.zero	4
.LC137:
	ASCII(.string	"SM_CfgBuf Err! ret =%d\n" )
.LC142:
	ASCII(.string	"Line: %d, start code num from scd state reg: %d, release raw packet anyway!\n" )
	.zero	3
.LC144:
	ASCII(.string	"Error, discard raw packet!\n" )
	.zero	4
.LC146:
	ASCII(.string	"Line: %d, The length of seg packet is invalid: %d\n" )
	.zero	5
.LC149:
	ASCII(.string	"[%s %d] pCurrentStartCodeVirAddr is null!!\n" )
	.zero	4
.LC154:
	ASCII(.string	"[%s %d] pNextStartCodeVirAddr is null!!\n" )
	.zero	7
.LC157:
	ASCII(.string	"ValidSegNum = %d, FilteredSegNum = 0, release raw packet anyway!\n" )
	.zero	6
.LC164:
	ASCII(.string	"%s: pRawPacket = NULL!\n" )
.LC167:
	ASCII(.string	"%s: unkown standard type = %d!\n" )
.LC169:
	ASCII(.string	"%s: Length(%d)+FlagLen(%d) > BufLen(%d)\n" )
	.zero	7
.LC178:
	ASCII(.string	"%s: FlagLen(%d) > RawPacketLength(%d)\n" )
	.zero	1
.LC182:
	ASCII(.string	"Func: %s, buffer has no enough space,(act: %d, header_buf: %d)\n" )
.LC185:
	ASCII(.string	"Func: %s, buffer has no enough space,(act: %d, str_buf: %d)\n" )
	.zero	3
.LC187:
	ASCII(.string	"Func: %s, buffer has no enough space,(act:%d, str_buf: %d, header_buf: %d)\n" )
	.zero	4
.LC190:
	ASCII(.string	"Func: %s, buffer has no enough space, (act: %d, str_buf: %d)\n" )
	.zero	2
.LC196:
	ASCII(.string	"Func: %s, buffer has no enough space,(act:%d, str_buf:%d)\n" )
	.zero	5
.LC199:
	ASCII(.string	"%s: RawPacket Length %d <= 0\n" )
	.zero	2
.LC203:
	ASCII(.string	"Chan %d has been destroyed or the function pointer -- ReleaseRawStreamData pStreamIntf is NULL!" )
.LC206:
	ASCII(.string	"line: %d s_SmIIS[%d].pSmInstArray is NULL\n" )
	.zero	5
.LC215:
	ASCII(.string	"line: %d, pSmInstArray is NULL!\n" )
	.zero	7
.LC218:
	ASCII(.string	"%s %d force to clear SCDState = 0\n" )
	.zero	5
.LC221:
	ASCII(.string	"%s %d FMW_OK !=  GetRawStreamNum !!\n" )
	.zero	3
.LC225:
	ASCII(.string	"Chan %d has been destroyed or the function pointer -- ReadRawStreamData pStreamIntf is NULL!" )
	.zero	3
.LC228:
	ASCII(.string	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\n" )
	.zero	5
.LC230:
	ASCII(.string	"Chan %d FillEosRawStream failed!\n" )
	.zero	6
.LC232:
	ASCII(.string	"Chan %d FillExtraData failed!\n" )
	.zero	1
.LC234:
	ASCII(.string	"Release this packet failed!\n" )
	.zero	3
.LC239:
	ASCII(.string	"raw_pts: %lld\n" )
	.zero	1
.LC241:
	ASCII(.string	"Get RawPhyAddr=0x%x,Len=%d\n" )
	.zero	4
.LC243:
	ASCII(.string	"!!!push raw err!!!\n" )
	.zero	4
.LC247:
	ASCII(.string	"Chan%d raw full\n" )
	.zero	7
.LC253:
	ASCII(.string	"RawNum %lld <= RawNumInVfmw %lld\n" )
	.zero	6
.LC256:
	ASCII(.string	"No space for raw move, total:%d+%d > max:%d!\n" )
	.zero	2
.LC259:
	ASCII(.string	"scd buffer is full, reset scd!\n" )
.LC261:
	ASCII(.string	"(%d ms) not release stream seg, release anyway!\n" )
	.zero	7
.LC273:
	ASCII(.string	"%s,%d, active scd Success!\n" )
	.zero	4
.LC278:
	ASCII(.string	"Error:now DspState[0]= %d,[1]= %d not except!!\n" )
.LC285:
	ASCII(.string	"Move raw data failed, force to reset scd.\n" )
	.zero	5
.LC287:
	ASCII(.string	"SCD GetRawStreamNum Fail.\n" )
	.zero	5
.LC295:
	ASCII(.string	"%s,%d,SCD(ID = %d) SCDState = %d\n" )
	.zero	6
.LC297:
	ASCII(.string	"%s,%d,SCD(ID = %d) return Idle!\n" )
	.zero	7
.LC300:
	ASCII(.string	"Chan %d SCD[%d] Time Out(%d ms), Reset it!\n" )
	.zero	4
.LC303:
	ASCII(.string	"%s,%d,SCD(ID = %d) really busy!\n" )
	.zero	7
.LC308:
	ASCII(.string	"%s prepare to check SCD(%d)/(MAX_SCD_NUM = %d)\n" )
.LC310:
	ASCII(.string	"%s,%d,SCD(ID = %d) return BUSY!!\n" )
	.zero	6
.LC312:
	ASCII(.string	"%s,%d,find idle SCD(ID = %d)\n" )
	.zero	2
.LC317:
	ASCII(.string	"scd time out: t_start,t_now,t_wait = %d,%d,%d\n" )
	.zero	1
.LC320:
	ASCII(.string	"********** SmID [%d] RawState begin **********\n" )
.LC322:
	ASCII(.string	"RawHead=%d\n" )
	.zero	4
.LC324:
	ASCII(.string	"RawTail=%d\n" )
	.zero	4
.LC326:
	ASCII(.string	"RawHistory=%d\n" )
	.zero	1
.LC328:
	ASCII(.string	"RawFirstPacketOffset=%d\n" )
	.zero	7
.LC330:
	ASCII(.string	"CurShowIndex=%d\n" )
	.zero	7
.LC332:
	ASCII(.string	"********** SmID [%d] RawState end   **********\n" )
.LC334:
	ASCII(.string	"RawPhyAddr=0x%x\n" )
	.zero	7
.LC336:
	ASCII(.string	"RawVirAddr=0x%x\n" )
	.zero	7
.LC338:
	ASCII(.string	"RawLength=%d\n" )
	.zero	2
.LC340:
	ASCII(.string	"RawPts=%ld\n" )
	.zero	4
.LC343:
	ASCII(.string	"%s %d FMW_OK !=  GetRawStreamNum!!\n" )
	.zero	4
.LC346:
	ASCII(.string	"********** SmID [%d] SegState begin **********\n" )
.LC348:
	ASCII(.string	"SegHead=%d\n" )
	.zero	4
.LC350:
	ASCII(.string	"SegTail=%d\n" )
	.zero	4
.LC352:
	ASCII(.string	"SegCurrent=%d\n" )
	.zero	1
.LC354:
	ASCII(.string	"SegBufPhyAddr=%p\n" )
	.zero	6
.LC356:
	ASCII(.string	"SegBufVirAddr=%p\n" )
	.zero	6
.LC358:
	ASCII(.string	"SegBufSize=%d\n" )
	.zero	1
.LC360:
	ASCII(.string	"SegBufReadAddr=%p\n" )
	.zero	5
.LC362:
	ASCII(.string	"SegBufWriteAddr=%pd\n" )
	.zero	3
.LC364:
	ASCII(.string	"********** SmID [%d] SegState end   **********\n" )
.LC366:
	ASCII(.string	"SegPhyAddr=0x%x\n" )
	.zero	7
.LC368:
	ASCII(.string	"SegVirAddr=0x%x\n" )
	.zero	7
.LC370:
	ASCII(.string	"SegLength=%d\n" )
	.zero	2
.LC372:
	ASCII(.string	"SegStreamID=%d\n" )
.LC374:
	ASCII(.string	"SegState=%d\n" )
	.zero	3
.LC376:
	ASCII(.string	"SegIsLastSeg=%d\n" )
	.zero	7
.LC378:
	ASCII(.string	"SegPts=%lld\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_ScdDrvParam, %object
	.size	g_ScdDrvParam, 72
g_ScdDrvParam:
	.zero	72
	.type	g_hex_base_addr, %object
	.size	g_hex_base_addr, 4
g_hex_base_addr:
	.zero	4
	.zero	4
	.type	s_ScdRegPhyBaseAddr, %object
	.size	s_ScdRegPhyBaseAddr, 4
s_ScdRegPhyBaseAddr:
	.zero	4
	.zero	4
	.type	s_SmIIS, %object
	.size	s_SmIIS, 512
s_SmIIS:
	.zero	512
	.type	s_eScdDrvSleepStage, %object
	.size	s_eScdDrvSleepStage, 4
s_eScdDrvSleepStage:
	.zero	4
	.zero	4
	.type	g_hex_base_vir_addr, %object
	.size	g_hex_base_vir_addr, 8
g_hex_base_vir_addr:
	.zero	8
	.type	g_hex_len, %object
	.size	g_hex_len, 4
g_hex_len:
	.zero	4
	.zero	4
	.type	s_ScdRegResetPhyAddr, %object
	.size	s_ScdRegResetPhyAddr, 4
s_ScdRegResetPhyAddr:
	.zero	4
	.zero	4
	.type	last_rec_pos_time.51793, %object
	.size	last_rec_pos_time.51793, 128
last_rec_pos_time.51793:
	.zero	128
	.type	LastRecPosTime.51987, %object
	.size	LastRecPosTime.51987, 128
LastRecPosTime.51987:
	.zero	128
	.type	last_rec_pos_time.52021, %object
	.size	last_rec_pos_time.52021, 128
last_rec_pos_time.52021:
	.zero	128
	.type	s_ScdRegResetOKPhyAddr, %object
	.size	s_ScdRegResetOKPhyAddr, 4
s_ScdRegResetOKPhyAddr:
	.zero	4
	.type	ForceRelease, %object
	.size	ForceRelease, 4
ForceRelease:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
