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
	.type	SCDDRV_SaveStreamSeg.part.6, %function
SCDDRV_SaveStreamSeg.part.6:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x19, .LC4
	mov	w0, 0
	ldr	x1, [x19, 32]
	blr	x1
	ldr	x2, .LC5
	ldr	x3, [x19, 88]
	ldr	w1, [x20, 20]
	ldr	x2, [x2, w21, sxtw 3]
	ldr	x0, [x20]
	blr	x3
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	SCDDRV_SaveStreamSeg.part.6, .-SCDDRV_SaveStreamSeg.part.6
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC5:
	.xword	vfmw_save_seg_file
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	GetFreeSegBufSize.part.7, %function
GetFreeSegBufSize.part.7:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	add	x0, x19, 360448
	str	wzr, [x20]
	ldp	w2, w3, [x0, 32]
	cmp	w3, w2
	sub	w2, w2, #1
	bls	.L4
	ldr	w0, [x0, 28]
	add	w2, w0, w2
	sub	w2, w2, w3
.L5:
	cmp	w2, w0
	bgt	.L3
	str	w2, [x20]
.L3:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L4:
	bcs	.L6
	sub	w2, w2, w3
	ldr	w0, [x0, 28]
	b	.L5
	.p2align 3
.L6:
	ldr	w0, [x0, 28]
	sub	w2, w0, #1
	b	.L5
	.size	GetFreeSegBufSize.part.7, .-GetFreeSegBufSize.part.7
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
	cbz	w19, .L24
.L9:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L24:
	ldr	x20, .LC6
	ldr	w0, [x20, 72]
	bl	MEM_Phy2Vir
	cbz	x0, .L25
	cmp	w22, 1
	beq	.L26
	cmp	w22, 2
	beq	.L27
	ldr	x1, .LC13
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L27:
	ldr	x21, .LC9
	mov	x2, 17920
	ldr	x1, .LC11
	ldr	x3, [x21, 104]
	add	x1, x1, 512
	blr	x3
	ldr	w0, [x20, 80]
	mov	w1, 0
	bl	MEM_WritePhyWord
.L14:
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
	b	.L17
	.p2align 3
.L28:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L18
.L17:
	ldr	x1, [x21, 232]
	mov	x0, 30
	blr	x1
	ldr	w0, [x20, 80]
	add	w0, w0, 260
	bl	MEM_ReadPhyWord
	tbz	x0, 0, .L28
	cmp	w19, 999
	bhi	.L18
	ldr	x2, .LC14
	mov	w0, 0
	ldr	x1, .LC18
	bl	dprint_vfmw
.L20:
	cmp	w22, 1
	beq	.L29
	cmp	w22, 2
	bne	.L9
	ldr	x0, .LC19
	mov	w1, 1
	str	w1, [x0]
	b	.L9
	.p2align 3
.L18:
	ldr	x2, .LC14
	mov	w0, 0
	ldr	x1, .LC16
	bl	dprint_vfmw
	b	.L20
	.p2align 3
.L26:
	ldr	x21, .LC9
	mov	x2, 17920
	ldr	x1, .LC10
	ldr	x3, [x21, 104]
	blr	x3
	ldr	w0, [x20, 80]
	mov	w1, w22
	bl	MEM_WritePhyWord
	b	.L14
	.p2align 3
.L29:
	ldr	x0, .LC19
	mov	w1, 2
	str	w1, [x0]
	b	.L9
.L25:
	ldr	x1, .LC8
	ldr	w2, [x20, 72]
	bl	dprint_vfmw
	b	.L9
	.size	SCDDRV_LoadDspCode, .-SCDDRV_LoadDspCode
	.align	3
.LC6:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC9:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC10:
	.xword	.LANCHOR1
	.align	3
.LC11:
	.xword	.LANCHOR2
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC14:
	.xword	.LANCHOR3
	.align	3
.LC16:
	.xword	.LC15
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC19:
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
	ldr	x3, .LC22
	mov	x0, 0
	b	.L33
	.p2align 3
.L31:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L39
.L33:
	add	x1, x3, x0, lsl 4
	ldr	x1, [x1, 88]
	add	x2, x1, 88
	cmp	x19, x2
	cbz	x1, .L31
	bne	.L31
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L39:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	GetInstIDByRawArray, .-GetInstIDByRawArray
	.align	3
.LC22:
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
	cbnz	w19, .L40
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
.L40:
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
	cbnz	w19, .L42
	ldr	x0, .LC23
	mov	w1, 1
	str	w1, [x0, 56]
.L42:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SetStateWork, .-SCDDRV_SetStateWork
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetSCD
	.type	ResetSCD, %function
ResetSCD:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	str	wzr, [x29, 60]
	cbnz	w19, .L51
	ldr	x19, .LC24
	mov	w1, 3
	ldr	w0, [x19, 80]
	add	w0, w0, 2176
	bl	MEM_WritePhyWord
	ldr	w0, [x19, 80]
	add	w0, w0, 2076
	bl	MEM_ReadPhyWord
	ldr	x20, .LC25
	mov	w21, w0
	ldr	x2, [x20]
	add	x2, x2, 61440
	ldr	w0, [x2, 2052]
	str	w0, [x29, 60]
	and	w0, w0, 3
	cbnz	w0, .L46
	ldr	x1, .LC27
	mov	w2, 0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, 1
.L53:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L46:
	ldr	w1, [x2, 2060]
	mov	w0, 0
	str	w1, [x29, 60]
	mov	w3, 10000
	orr	w1, w1, 4
	strb	w1, [x29, 60]
	ldr	w1, [x29, 60]
	str	w1, [x2, 2060]
	b	.L48
	.p2align 3
.L54:
	add	w0, w0, 1
	cmp	w0, w3
	beq	.L49
.L48:
	ldr	w1, [x2, 2064]
	tbz	x1, 2, .L54
	mov	w1, 9999
	cmp	w0, w1
	bhi	.L49
.L50:
	ldr	w3, [x2, 2060]
	and	w1, w21, 1
	str	w3, [x29, 60]
	and	w3, w3, -5
	strb	w3, [x29, 60]
	ldr	w0, [x19, 80]
	ldr	w3, [x29, 60]
	str	w3, [x2, 2060]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldr	w0, [x19, 80]
	mov	w1, 2
	add	w0, w0, 2176
	bl	MEM_WritePhyWord
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L49:
	ldr	x1, .LC29
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x2, [x20]
	add	x2, x2, 61440
	b	.L50
.L51:
	mov	w0, -2
	b	.L53
	.size	ResetSCD, .-ResetSCD
	.align	3
.LC24:
	.xword	.LANCHOR0
	.align	3
.LC25:
	.xword	g_HwMem
	.align	3
.LC27:
	.xword	.LC26
	.align	3
.LC29:
	.xword	.LC28
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
	ldr	x0, .LC30
	ldr	w0, [x0, 52]
	cmp	w19, w0
	beq	.L59
.L55:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L59:
	ldr	x0, .LC31
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L57
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Reset_Module
.L58:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	b	.L55
	.p2align 3
.L57:
	mov	w0, 0
	bl	ResetSCD
	b	.L58
	.size	SCDDRV_ResetSCD, .-SCDDRV_ResetSCD
	.align	3
.LC30:
	.xword	.LANCHOR0
	.align	3
.LC31:
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
	ldr	x0, .LC32
	add	x19, x0, x19, sxtw 4
	ldr	w0, [x20, 4]
	cmp	w0, wzr
	ldr	x0, [x19, 88]
	ccmp	x0, xzr, 4, ne
	beq	.L63
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
	beq	.L64
	sxtw	x3, w3
	ldr	x5, .LC33
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
.L62:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L64:
	mov	w0, -4
	b	.L62
.L63:
	mov	w0, -1
	b	.L62
	.size	SCDDRV_InsertRawPacket, .-SCDDRV_InsertRawPacket
	.align	3
.LC32:
	.xword	.LANCHOR0
	.align	3
.LC33:
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
	bhi	.L68
	ldr	x0, .LC34
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	cbz	x0, .L68
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
.L66:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L68:
	mov	w0, -4
	b	.L66
	.size	GetRawState, .-GetRawState
	.align	3
.LC34:
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
	bhi	.L73
	ldr	w1, [x19, 4]
	cmp	w0, w1
	beq	.L73
	sxtw	x0, w0
	ldr	x1, .LC35
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
.L71:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L73:
	mov	w0, -3
	b	.L71
	.size	ShowRawPacket, .-ShowRawPacket
	.align	3
.LC35:
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
	beq	.L76
	add	x0, x19, 98304
	ldp	w2, w1, [x0]
	cmp	w2, w1
	beq	.L77
	ldr	w1, [x0, 12]
	mov	w0, 0
	str	w1, [x20]
.L75:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L76:
	mov	w0, -1
	b	.L75
	.p2align 3
.L77:
	mov	w0, -3
	b	.L75
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
	cbz	x23, .L83
	add	x20, x23, 98304
	ldp	w1, w0, [x20]
	cmp	w1, w0
	beq	.L82
	ldr	w24, [x20, 12]
	mov	w22, w24
	sxtw	x21, w24
.L80:
	cmp	w1, 1023
	str	w1, [x20, 16]
	bhi	.L81
	ldr	w0, [x20, 4]
	cmp	w0, w1
	beq	.L81
	sxtw	x1, w1
	ldr	x3, .LC36
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
.L81:
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
.L82:
	mov	x21, 0
	mov	w22, 0
	mov	w24, 0
	b	.L80
	.p2align 3
.L83:
	mov	x0, 98304
	mov	x21, 0
	mov	w22, 0
	mov	w24, 0
	mov	x20, x0
	ldr	w1, [x0]
	b	.L80
	.size	GetFirstRawPacket, .-GetFirstRawPacket
	.align	3
.LC36:
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
	cbz	x19, .L88
	add	x3, x19, 98304
	ldp	w0, w2, [x3]
	cmp	w0, w2
	beq	.L87
	sxtw	x0, w0
	ldr	w4, [x3, 12]
	lsl	x2, x0, 2
	sub	x0, x2, x0
	add	w1, w20, w4
	add	x0, x19, x0, lsl 5
	ldr	w0, [x0, 12]
	cmp	w1, w0
	bge	.L88
	mov	w0, 0
	str	w1, [x3, 12]
.L85:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L88:
	mov	w0, -1
	b	.L85
	.p2align 3
.L87:
	mov	w0, -3
	b	.L85
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
	beq	.L105
	ldr	x27, .LC37
	mov	x0, 0
	b	.L93
	.p2align 3
.L91:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L94
.L93:
	add	x1, x27, x0, lsl 4
	mov	w3, w0
	ldr	x1, [x1, 88]
	add	x2, x1, 88
	cmp	x26, x2
	cbz	x1, .L91
	bne	.L91
	cmp	w0, 31
	bhi	.L94
	add	x23, x26, 98304
	ldp	w0, w2, [x23]
	cmp	w0, w2
	bgt	.L116
.L113:
	sub	w2, w2, w0
	cmp	w2, w20
	bcc	.L117
	mov	w24, w0
	cbz	w20, .L99
	ldr	x21, .LC42
	add	x27, x27, 88
	ldr	x22, .LC44
	mov	w25, 0
	add	x21, x21, 24
	add	x27, x27, x3, sxtw 4
	.p2align 2
.L100:
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
	bne	.L100
	ldr	w0, [x23]
	add	w20, w20, w0
	str	w20, [x23]
	cmp	w20, 1023
	ble	.L103
	sub	w20, w20, #1024
	str	w20, [x23]
.L103:
	str	wzr, [x23, 12]
.L114:
	mov	w0, 0
.L111:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L116:
	add	w2, w2, 1024
	b	.L113
.L99:
	cmp	w0, 1023
	str	w0, [x23]
	ble	.L114
	sub	w0, w0, #1024
	str	w0, [x23]
	b	.L114
	.p2align 3
.L105:
	mov	w0, -1
	b	.L111
.L117:
	ldr	x1, .LC41
	mov	w3, w20
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, -1
	b	.L111
	.p2align 3
.L94:
	ldr	x1, .LC39
	mov	w2, 476
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L111
	.size	DeleteRawPacket, .-DeleteRawPacket
	.align	3
.LC37:
	.xword	.LANCHOR0
	.align	3
.LC39:
	.xword	.LC38
	.align	3
.LC41:
	.xword	.LC40
	.align	3
.LC42:
	.xword	.LANCHOR3
	.align	3
.LC44:
	.xword	.LC43
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
	blt	.L126
	cmp	x21, xzr
	ccmp	x22, xzr, 4, ne
	ccmp	x23, xzr, 4, ne
	beq	.L126
	add	x2, x20, 98304
	ldr	w1, [x2]
	ldr	w8, [x2, 12]
	sxtw	x3, w1
	lsl	x0, x3, 2
	sub	x0, x0, x3
	add	x0, x20, x0, lsl 5
	ldr	w0, [x0, 12]
	sub	w8, w0, w8
	cbz	x20, .L127
	ldr	w10, [x2, 4]
	sub	w10, w10, w1
	add	w0, w10, 1024
	cmp	w10, wzr
	csel	w10, w0, w10, lt
.L120:
	add	w10, w1, w10
	cmp	w19, w8
	ccmp	w10, w1, 0, ge
	mov	w0, w1
	bls	.L128
	mov	w6, w1
	b	.L122
	.p2align 3
.L129:
	mov	w8, w5
.L122:
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
	cbz	w7, .L129
	cmp	w1, w6
	beq	.L121
	sub	w8, w19, w8
	str	w8, [x22]
.L124:
	str	w0, [x23]
	mov	w0, 0
	ldr	w1, [x2]
	sub	w6, w6, w1
	str	w6, [x21]
.L119:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L128:
	mov	w6, w1
	.p2align 2
.L121:
	str	w19, [x22]
	b	.L124
	.p2align 3
.L127:
	mov	w10, 0
	b	.L120
.L126:
	mov	w0, -1
	b	.L119
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
	blt	.L133
	stp	wzr, wzr, [x29, 52]
	cbz	x19, .L133
	add	x20, x19, 98304
	ldr	w1, [x20, 12]
	ldr	w0, [x20, 20]
	sub	w0, w0, w1
	asr	w21, w0, 31
	cbnz	w21, .L132
	cmp	w22, w0
	bgt	.L133
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
	ldr	x1, .LC48
	sxtw	x6, w0
	lsl	x2, x6, 2
	sub	x0, x2, x6
	mov	w2, 642
	add	x0, x19, x0, lsl 5
	ldrb	w7, [x0, 2]
	ldr	w6, [x0, 12]
	mov	w0, 26
	bl	dprint_vfmw
	ldr	w1, [x29, 52]
	mov	x0, x19
	bl	DeleteRawPacket
	ldp	w0, w1, [x20]
	cmp	w0, w1
	beq	.L134
	sxtw	x0, w0
	ldr	w2, [x20, 12]
	lsl	x1, x0, 2
	ldr	w3, [x29, 56]
	sub	x0, x1, x0
	add	w1, w3, w2
	add	x19, x19, x0, lsl 5
	ldr	w0, [x19, 12]
	cmp	w1, w0
	blt	.L138
.L133:
	mov	w21, -1
.L132:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L138:
	str	w1, [x20, 12]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L134:
	mov	w21, -3
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	DeleteRawLen, .-DeleteRawLen
	.align	3
.LC48:
	.xword	.LC47
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
	bhi	.L139
	ldr	x0, .LC49
	ubfiz	x19, x19, 4, 32
	add	x0, x0, 88
	ldr	x0, [x0, x19]
	cbz	x0, .L142
	add	x19, x0, 458752
	ldr	w1, [x19, 168]
	cmp	w1, wzr
	ble	.L139
	add	x0, x0, 88
	bl	DeleteRawPacket
	str	wzr, [x19, 168]
.L139:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L142:
	ldr	x1, .LC51
	mov	w2, 659
	bl	dprint_vfmw
	b	.L139
	.size	DeleteLastSendRaw, .-DeleteLastSendRaw
	.align	3
.LC49:
	.xword	.LANCHOR0
	.align	3
.LC51:
	.xword	.LC50
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
	beq	.L145
	add	x19, x19, 98304
	ldr	w2, [x19, 20]
	str	w2, [x20]
	ldr	w0, [x19, 12]
	sub	w0, w2, w0
	str	w0, [x20]
	asr	w0, w0, 31
.L144:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L145:
	mov	w0, -1
	b	.L144
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
	beq	.L149
	add	x19, x19, 98304
	ldp	w1, w0, [x19]
	subs	w0, w0, w1
	bmi	.L148
	str	w0, [x20]
	mov	w0, 0
.L147:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L148:
	add	w2, w0, 1024
	str	w2, [x20]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L149:
	mov	w0, -1
	b	.L147
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
	cbz	x19, .L153
	cmp	w20, wzr
	mov	w0, 262143
	ccmp	x22, xzr, 4, ne
	ccmp	w21, w0, 0, ne
	bls	.L153
	ldr	x3, .LC53
	mov	x2, 32824
	mov	w1, 0
	movk	x2, 0x5, lsl 16
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x19, 360448
	mov	w0, 0
	str	w20, [x1, 24]
	str	x22, [x19]
	stp	w21, w20, [x1, 28]
	str	w20, [x1, 36]
.L151:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L153:
	mov	w0, -1
	b	.L151
	.size	ConfigStreamSegArray, .-ConfigStreamSegArray
	.align	3
.LC53:
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
	cbz	x19, .L154
	ldr	x3, .LC54
	mov	x2, 32768
	mov	w1, 0
	movk	x2, 0x5, lsl 16
	add	x0, x19, 8
	ldr	x3, [x3, 96]
	blr	x3
	add	x0, x19, 360448
	ldr	w1, [x0, 24]
	stp	wzr, wzr, [x0, 8]
	str	wzr, [x0, 16]
	stp	w1, w1, [x0, 32]
.L154:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ResetStreamSegArray, .-ResetStreamSegArray
	.align	3
.LC54:
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
	cbz	x19, .L163
	add	x1, x19, 360448
	ldp	w0, w2, [x1, 32]
	cmp	w2, w0
	sub	w0, w0, #1
	bhi	.L164
	sub	w0, w0, w2
	bcc	.L160
	ldr	w0, [x1, 28]
	sub	w0, w0, #1
.L160:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L164:
	ldr	w1, [x1, 28]
	ldr	x19, [sp, 16]
	add	w0, w0, w1
	sub	w0, w0, w2
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L163:
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
	cbz	x19, .L165
	and	w0, w20, 31
	sub	w1, w0, #30
	sub	w2, w0, #1
	uxtb	w1, w1
	cmp	w1, 1
	ccmp	w0, 19, 4, hi
	ccmp	w2, 12, 0, ne
	bhi	.L167
	add	x1, x19, 507904
	ldr	w0, [x1, 1696]
	add	w0, w0, 1
	str	w0, [x1, 1696]
.L167:
	sub	w2, w20, #1
	add	w0, w20, 79
	uxtb	w2, w2
	uxtb	w0, w0
	cmp	w2, 183
	ccmp	w0, 4, 0, ls
	bhi	.L177
.L168:
	add	x19, x19, 507904
	ldr	w0, [x19, 1700]
	add	w0, w0, 1
	str	w0, [x19, 1700]
.L165:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L177:
	add	w20, w20, 73
	uxtb	w20, w20
	cmp	w20, 3
	bls	.L168
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
	cbz	x19, .L178
	add	x0, x19, 507904
	ldr	w1, [x0, 1704]
	cmp	w1, 2
	ble	.L178
	and	w20, w20, 31
	cbz	w20, .L178
	ldr	w2, [x0, 1712]
	ldr	w1, [x0, 1716]
	sub	w3, w1, w2
	cmp	w3, 1
	beq	.L192
.L180:
	cmp	w1, w2
	beq	.L193
.L178:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L193:
	ldr	w2, [x0, 1708]
	cmp	w1, w2
	bne	.L178
.L181:
	cmp	w1, 20
	ccmp	w1, 1, 4, ne
	beq	.L178
	ldr	w1, [x0, 1696]
	cmp	w1, wzr
	ble	.L182
	sub	w1, w1, #1
	str	w1, [x0, 1696]
.L182:
	ldr	w1, [x0, 1700]
	add	w1, w1, 1
	str	w1, [x0, 1700]
	b	.L178
	.p2align 3
.L192:
	ldr	w3, [x0, 1708]
	sub	w3, w2, w3
	cmp	w3, 1
	bne	.L180
	b	.L181
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
	ldr	x0, .LC55
	ldr	x19, [x0, w21, sxtw 3]
	cbz	x19, .L194
	ldr	w0, [x19, 632]
	cmp	w0, wzr
	ccmp	w0, 3, 4, ne
	bne	.L194
	add	x20, x19, 507904
	ldr	w0, [x20, 1704]
	cmp	w0, 199
	bgt	.L194
	ldrb	w1, [x22]
	cbz	w1, .L212
.L202:
	mov	w3, 0
	mov	w22, 0
.L198:
	add	x4, x20, 1536
	ldr	w2, [x20, 1712]
	ldr	w1, [x20, 1716]
	add	w0, w0, 1
	stp	w1, w3, [x4, 176]
	stp	w0, w2, [x4, 168]
	mov	w1, w22
	mov	x0, x19
	bl	CheckData
	mov	x0, x19
	mov	w1, w22
	bl	CheckStartCodeCnt
	ldr	w0, [x20, 1704]
	cmp	w0, 199
	ble	.L194
	ldr	w1, [x20, 1696]
	ldr	w0, [x20, 1700]
	sub	w2, w1, w0
	cmp	w2, 49
	bgt	.L213
.L199:
	sub	w0, w0, w1
	cmp	w0, 49
	ble	.L194
	ldr	w0, [x19, 632]
	cbnz	w0, .L194
	ldr	x0, .LC56
	ldr	x4, [x0]
	cbz	x4, .L194
	mov	w3, 0
	mov	x2, 0
	mov	w1, 124
	mov	w0, w21
	blr	x4
.L194:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L212:
	ldrb	w1, [x22, 1]
	cbnz	w1, .L202
	ldrb	w1, [x22, 2]
	cmp	w1, 1
	bne	.L202
	ldrb	w22, [x22, 3]
	and	w3, w22, 31
	b	.L198
	.p2align 3
.L213:
	ldr	w2, [x19, 632]
	cmp	w2, 3
	bne	.L199
	ldr	x0, .LC56
	ldr	x4, [x0]
	cbz	x4, .L194
	mov	w1, 124
	mov	w3, 0
	mov	x2, 0
	mov	w0, w21
	blr	x4
	ldr	w1, [x20, 1696]
	ldr	w0, [x20, 1700]
	b	.L199
	.size	CheckStream.part.3, .-CheckStream.part.3
	.align	3
.LC55:
	.xword	s_pstVfmwChan
	.align	3
.LC56:
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
	cbz	x19, .L214
	cmp	w20, 31
	bhi	.L214
	mov	w1, w20
	mov	x0, x19
	bl	CheckStream.part.3
.L214:
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
	beq	.L223
	add	x20, x22, 360448
	ldp	w1, w19, [x20, 8]
	add	w0, w19, 1
	asr	w3, w0, 31
	lsr	w3, w3, 20
	add	w0, w0, w3
	and	w0, w0, 4095
	sub	w0, w0, w3
	cmp	w0, w1
	beq	.L224
	ldr	x0, [x21]
	cbz	x0, .L221
	cmp	w23, 31
	bls	.L231
.L221:
	sxtw	x0, w19
	ldr	x3, .LC57
	lsl	x19, x0, 2
	mov	x2, 88
	sub	x19, x19, x0
	mov	x1, x21
	lsl	x19, x19, 2
	ldr	x3, [x3, 104]
	sub	x19, x19, x0
	add	x19, x22, x19, lsl 3
	add	x0, x19, 8
	blr	x3
	ldr	w3, [x20, 12]
	mov	w5, 1
	add	w1, w3, 1
	sxtw	x4, w3
	asr	w2, w1, 31
	lsl	x0, x4, 2
	lsr	w2, w2, 20
	sub	x0, x0, x4
	add	w1, w1, w2
	lsl	x0, x0, 2
	and	w1, w1, 4095
	sub	x0, x0, x4
	sub	w1, w1, w2
	add	x0, x22, x0, lsl 3
	strb	w5, [x0, 16]
	str	w3, [x19, 32]
	str	w1, [x20, 12]
	ldrsb	w0, [x21, 9]
	cmp	w0, 2
	beq	.L222
	ldp	w1, w2, [x21, 16]
	ldp	w0, w3, [x20, 40]
	add	w2, w1, w2
	str	w2, [x20, 36]
	ldr	w1, [x21, 20]
	add	w1, w0, w1
	str	w1, [x20, 40]
	ldr	w0, [x21, 20]
	add	w0, w3, w0
	str	w0, [x20, 44]
.L222:
	ldr	w1, [x20, 48]
	mov	w0, 0
	add	w1, w1, 1
	str	w1, [x20, 48]
.L220:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L231:
	mov	w1, w23
	bl	CheckStream.part.3
	ldr	w19, [x20, 12]
	b	.L221
	.p2align 3
.L223:
	mov	w0, -1
	b	.L220
	.p2align 3
.L224:
	mov	w0, -4
	b	.L220
	.size	InsertStreamSeg, .-InsertStreamSeg
	.align	3
.LC57:
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
	stp	x23, x24, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x24, x1
	bl	_mcount
	cmp	x21, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L243
	add	x22, x21, 360448
	ldr	w19, [x22, 8]
	tbnz	w19, #31, .L243
	ldr	w1, [x22, 12]
	tbnz	w1, #31, .L243
	cmp	w19, w1
	beq	.L245
	sxtw	x20, w19
	lsl	x0, x20, 2
	b	.L250
	.p2align 3
.L236:
	add	w0, w19, 1
	asr	w19, w0, 31
	lsr	w19, w19, 20
	add	w0, w0, w19
	and	w0, w0, 4095
	sub	w19, w0, w19
	cmp	w1, w19
	sxtw	x20, w19
	lsl	x0, x20, 2
	beq	.L245
.L250:
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x0, x0, x20
	add	x0, x21, x0, lsl 3
	ldrsb	w0, [x0, 16]
	cmp	w0, 1
	bne	.L236
	lsl	x23, x20, 2
	sub	x23, x23, x20
	lsl	x23, x23, 2
	sub	x23, x23, x20
	add	x23, x21, x23, lsl 3
	adds	x1, x23, 8
	beq	.L245
	ldr	x3, .LC58
	mov	x2, 88
	mov	x0, x24
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 88
	mov	w1, 2
	smaddl	x19, w19, w0, x21
	ldrsb	w0, [x19, 17]
	strb	w1, [x19, 16]
	cmp	w0, 2
	ldr	w2, [x22, 44]
	ldr	w3, [x23, 28]
	beq	.L240
	sub	w2, w2, w3
.L240:
	lsl	x0, x20, 2
	ldr	w1, [x22, 48]
	sub	x0, x0, x20
	cmp	w2, wzr
	lsl	x0, x0, 2
	csel	w2, w2, wzr, ge
	sub	x20, x0, x20
	subs	w1, w1, #1
	csel	w1, w1, wzr, pl
	mov	w0, 26
	add	x21, x21, x20, lsl 3
	stp	w2, w1, [x22, 44]
	ldr	x1, .LC60
	ldrb	w4, [x19, 18]
	ldr	w2, [x21, 24]
	bl	dprint_vfmw
	mov	w0, 0
.L233:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L245:
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L243:
	mov	w0, -1
	b	.L233
	.size	SCDDRV_GetStreamSeg, .-SCDDRV_GetStreamSeg
	.align	3
.LC58:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC60:
	.xword	.LC59
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ReleaseStreamSeg
	.type	ReleaseStreamSeg, %function
ReleaseStreamSeg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x24, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x24, .L270
	sub	w1, w20, #4096
	mov	w0, -4098
	cmp	w1, w0
	bls	.L270
	cmn	w20, #1
	add	x23, x24, 360448
	beq	.L286
	ldp	w0, w1, [x23, 8]
	cmp	w0, w1
	bne	.L282
	b	.L274
	.p2align 3
.L258:
	add	w0, w0, 1
	and	w0, w0, 4095
	cmp	w0, w1
	beq	.L274
.L282:
	cmp	w20, w0
	bne	.L258
	uxtw	x1, w0
	mov	w0, -3
	lsl	x22, x1, 2
	sub	x22, x22, x1
	lsl	x22, x22, 2
	sub	x1, x22, x1
	add	x1, x24, x1, lsl 3
	add	x22, x1, 8
	ldrsb	w2, [x1, 16]
	cmp	w2, 2
	beq	.L255
.L278:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L286:
	ldp	w20, w0, [x23, 8]
	cmp	w20, w0
	bne	.L287
.L274:
	mov	w0, -3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L287:
	sxtw	x22, w20
	lsl	x0, x22, 2
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x22, x0, x22
	add	x22, x24, x22, lsl 3
	add	x22, x22, 8
.L255:
	mov	w0, -3
	cbz	x22, .L278
	ldrb	w4, [x22, 10]
	mov	w5, w20
	ldr	x1, .LC62
	mov	w0, 26
	ldp	w2, w3, [x22, 16]
	strb	wzr, [x22, 8]
	bl	dprint_vfmw
	ldr	w19, [x23, 8]
	cmp	w20, w19
	beq	.L288
.L260:
	ldrsb	w0, [x22, 9]
	cmp	w0, 2
	beq	.L285
	ldr	w1, [x22, 20]
	ldr	w0, [x23, 40]
	sub	w1, w0, w1
.L264:
	cmp	w1, wzr
	mov	w0, 0
	csel	w1, w1, wzr, ge
	str	w1, [x23, 40]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L285:
	ldr	w1, [x23, 40]
	b	.L264
	.p2align 3
.L288:
	ldr	x20, .LC63
	ldr	x21, .LC65
	add	x20, x20, 40
	b	.L265
	.p2align 3
.L261:
	ldr	w2, [x23, 12]
	lsl	x0, x0, 2
	sub	x0, x0, x1
	cmp	w19, w2
	add	x0, x24, x0, lsl 3
	beq	.L267
	ldrsb	w1, [x0, 16]
	cbnz	w1, .L289
.L262:
	add	w19, w19, 1
	and	w19, w19, 4095
.L265:
	uxtw	x1, w19
	cmp	w19, 4095
	lsl	x0, x1, 2
	sub	x0, x0, x1
	bls	.L261
	mov	x2, x20
	mov	x1, x21
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x23, 12]
	cmp	w19, w2
	bne	.L262
	.p2align 2
.L267:
	ldr	w0, [x23, 36]
	str	w2, [x23, 8]
	str	w0, [x23, 32]
	b	.L260
	.p2align 3
.L289:
	str	w19, [x23, 8]
	ldrsb	w1, [x22, 9]
	cmp	w1, 2
	beq	.L285
	ldr	w0, [x0, 24]
	str	w0, [x23, 32]
	b	.L260
.L270:
	mov	w0, -1
	b	.L278
	.size	ReleaseStreamSeg, .-ReleaseStreamSeg
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC63:
	.xword	.LANCHOR3
	.align	3
.LC65:
	.xword	.LC64
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
	beq	.L292
	add	x19, x19, 360448
	mov	w0, 0
	ldr	w1, [x19, 40]
	str	w1, [x20]
.L291:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L292:
	mov	w0, -1
	b	.L291
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
	cbz	x19, .L295
	add	x19, x19, 360448
	ldp	w1, w0, [x19, 8]
	ldr	x19, [sp, 16]
	sub	w0, w0, w1
	and	w0, w0, 4095
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L295:
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
	beq	.L296
	add	x19, x19, 360448
	ldr	w0, [x19, 48]
	str	w0, [x21]
	ldr	w0, [x19, 44]
	str	w0, [x20]
.L296:
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
	cbnz	w19, .L302
	ldr	x1, .LC67
	ldr	w0, [x1, 600]
	cbnz	w0, .L302
	ldr	w0, [x1, 56]
	cbz	w0, .L303
	mov	w2, 1
	mov	w0, 0
	str	w2, [x1, 600]
.L299:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L303:
	mov	w2, 2
	str	w2, [x1, 600]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L302:
	mov	w0, -1
	b	.L299
	.size	SCDDRV_PrepareSleep, .-SCDDRV_PrepareSleep
	.align	3
.LC67:
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
	cbz	w19, .L307
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L307:
	ldr	x0, .LC68
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 600]
	ret
	.size	SCDDRV_GetSleepStage, .-SCDDRV_GetSleepStage
	.align	3
.LC68:
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
	cbnz	w19, .L308
	ldr	x0, .LC69
	ldr	w1, [x0, 600]
	cmp	w1, 2
	beq	.L308
	mov	w1, 2
	str	w1, [x0, 600]
.L308:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ForceSleep, .-SCDDRV_ForceSleep
	.align	3
.LC69:
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
	cbnz	w19, .L313
	ldr	x0, .LC70
	str	wzr, [x0, 600]
.L313:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_ExitSleep, .-SCDDRV_ExitSleep
	.align	3
.LC70:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ResetLastUnfinishedSegInfo
	.type	ResetLastUnfinishedSegInfo, %function
ResetLastUnfinishedSegInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L315
	add	x0, x19, 458752
	ldr	x4, .LC71
	add	x6, x0, 256
	mov	w3, -1
	mov	w5, 1
	mov	x2, 88
	strh	w3, [x0, 468]
	mov	w1, 0
	strh	w3, [x0, 476]
	add	x0, x0, 512
	str	w3, [x0, -40]
	ldr	x4, [x4, 96]
	stp	w3, wzr, [x6, 224]
	stp	w5, wzr, [x6, 232]
	str	wzr, [x0, -16]
	str	wzr, [x0, -12]
	str	wzr, [x0, -8]
	blr	x4
.L315:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ResetLastUnfinishedSegInfo, .-ResetLastUnfinishedSegInfo
	.align	3
.LC71:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ClearInst
	.type	SM_ClearInst, %function
SM_ClearInst:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L323
	ldr	x20, .LC73
	sbfiz	x19, x19, 4, 32
	ldr	x21, .LC72
	mov	x2, 16984
	add	x20, x20, 88
	movk	x2, 0x7, lsl 16
	mov	w1, 0
	ldr	x3, [x21, 96]
	ldr	x0, [x20, x19]
	blr	x3
	ldr	x0, [x20, x19]
	cbz	x0, .L322
	add	x0, x0, 458752
	mov	w3, -1
	add	x6, x0, 256
	ldr	x4, [x21, 96]
	mov	w5, 1
	mov	x2, 88
	strh	w3, [x0, 468]
	mov	w1, 0
	strh	w3, [x0, 476]
	add	x0, x0, 512
	str	w3, [x0, -40]
	stp	w3, wzr, [x6, 224]
	stp	w5, wzr, [x6, 232]
	str	wzr, [x0, -16]
	str	wzr, [x0, -12]
	str	wzr, [x0, -8]
	blr	x4
	ldr	x0, [x20, x19]
.L322:
	add	x1, x0, 458752
	mov	x2, -1
	mov	w0, 0
	str	x2, [x1, 280]
.L321:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L323:
	mov	w0, -1
	b	.L321
	.size	SM_ClearInst, .-SM_ClearInst
	.align	3
.LC72:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC73:
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
	ldr	x20, .LC75
	ldr	x21, .LC76
	add	x19, x20, 88
	add	x20, x20, 600
	.p2align 2
.L328:
	ldr	x3, [x21, 96]
	mov	x0, x19
	mov	x2, 16
	mov	w1, 0
	add	x19, x19, x2
	blr	x3
	cmp	x19, x20
	bne	.L328
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	SM_InstInit, .-SM_InstInit
	.align	3
.LC75:
	.xword	.LANCHOR0
	.align	3
.LC76:
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
	beq	.L338
	cbz	w20, .L339
	cmp	w20, 1
	bne	.L346
	mov	w0, 49152
	movk	w0, 0xf9c5, lsl 16
.L333:
	sxtw	x21, w20
	ldr	x24, .LC81
	lsl	x25, x21, 6
	add	x25, x25, x21, lsl 3
	add	x26, x24, x21, lsl 2
	add	x20, x24, x25
	str	w0, [x26, 80]
	ldr	w0, [x20, 48]
	cmp	w0, 1
	beq	.L337
	ldr	x0, .LC82
	mov	x2, 72
	mov	w1, 0
	ldr	x3, [x0, 96]
	mov	x0, x20
	blr	x3
	str	w19, [x24, x25]
	lsl	x2, x21, 4
	ldr	x1, .LC83
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
	add	w19, w19, 45056
	add	w19, w19, 127
	bl	MEM_Phy2Vir
	add	w19, w19, w22
	str	x0, [x20, 24]
	and	w19, w19, -128
	mov	w0, 32768
	str	w0, [x20, 36]
	mov	w0, w19
	str	w19, [x24, 72]
	bl	MEM_Phy2Vir
	str	x0, [x24, 608]
	cbz	x0, .L347
	add	w22, w22, 61440
	ldr	w2, [x26, 80]
	add	w22, w22, 1536
	ldr	w0, [x26, 624]
	mov	w1, 17920
	cmp	w23, w22
	stp	w2, w0, [x20, 40]
	str	w1, [x24, 616]
	blt	.L337
	ldr	x0, [x20, 8]
	cbz	x0, .L337
	ldr	x0, [x20, 24]
	cbz	x0, .L337
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
.L346:
	ldr	x2, .LC78
	mov	w0, 0
	ldr	x1, .LC80
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -7
.L331:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L339:
	mov	w0, 49152
	movk	w0, 0xf8c3, lsl 16
	b	.L333
	.p2align 3
.L337:
	mov	w0, -7
	b	.L331
	.p2align 3
.L338:
	mov	w0, -1
	b	.L331
.L347:
	ldr	x2, .LC78
	ldr	x1, .LC85
	add	x2, x2, 64
	bl	dprint_vfmw
	mov	w0, -1
	b	.L331
	.size	SM_OpenSCDDrv, .-SM_OpenSCDDrv
	.align	3
.LC78:
	.xword	.LANCHOR3
	.align	3
.LC80:
	.xword	.LC79
	.align	3
.LC81:
	.xword	.LANCHOR0
	.align	3
.LC82:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC83:
	.xword	g_VfmwGlobalStat
	.align	3
.LC85:
	.xword	.LC84
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
	cbnz	w19, .L352
	ldr	x0, .LC86
	mov	w1, 0
	add	x2, x0, 88
	b	.L351
	.p2align 3
.L350:
	cmp	w1, 32
	add	x2, x2, 16
	beq	.L360
.L351:
	cmp	w1, 31
	add	w1, w1, 1
	bhi	.L350
	ldr	x3, [x2]
	add	x4, x3, 458752
	cbz	x3, .L350
	ldr	w3, [x4, 256]
	cbz	w3, .L350
	ldr	w3, [x4, 244]
	cmp	w3, wzr
	bgt	.L350
	str	wzr, [x4, 256]
	cmp	w1, 32
	add	x2, x2, 16
	bne	.L351
	.p2align 2
.L360:
	ldr	x3, .LC88
	mov	x2, 72
	ldr	x4, .LC87
	mov	w1, 0
	ldr	x3, [x3, 96]
	str	wzr, [x4, 56]
	blr	x3
	mov	w0, 0
.L349:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L352:
	mov	w0, -1
	b	.L349
	.size	SM_CloseSCDDrv, .-SM_CloseSCDDrv
	.align	3
.LC86:
	.xword	.LANCHOR0
	.align	3
.LC87:
	.xword	g_VfmwGlobalStat
	.align	3
.LC88:
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
	bhi	.L364
	ldr	x1, .LC89
	add	x0, x1, x22, sxtw 4
	ldr	x24, [x0, 88]
	cbz	x24, .L364
	add	x23, x24, 458752
	ldr	w0, [x19, 48]
	str	w0, [x23, 328]
	ldr	w0, [x19, 16]
	ldr	w2, [x24, 24]
	cmp	w2, w0
	beq	.L384
	cbz	w0, .L364
	ldr	x0, [x19]
	cbz	x0, .L364
	ldr	x2, [x1, 8]
	str	x2, [x23, 192]
	ldp	w5, w4, [x1, 16]
	ldr	x2, [x1, 24]
	ldr	w3, [x1, 32]
	ldr	w1, [x1, 36]
	str	x2, [x23, 208]
	mov	w2, 262143
	str	w1, [x23, 220]
	mov	w1, 4096
	stp	w4, w5, [x23, 200]
	str	w1, [x23, 224]
	str	w3, [x23, 216]
	ldr	w20, [x19, 16]
	ldr	x25, [x19]
	add	w21, w20, 3
	and	w21, w21, -4
	sub	w20, w21, w20
	add	w21, w21, 131072
	str	w21, [x23, 228]
	sxtw	x1, w20
	add	x1, x1, 131072
	add	x25, x25, x1
	str	x25, [x23, 184]
	ldr	w1, [x19, 20]
	sub	w20, w1, w20
	sub	w20, w20, #131072
	sub	w20, w20, #1024
	str	w20, [x23, 232]
	cmp	w20, w2
	ble	.L364
	add	x27, x24, 98304
	adds	x28, x27, 112
	beq	.L385
	cmp	w21, wzr
	ldr	x26, .LC90
	ccmp	x25, xzr, 4, ne
	ccmp	w20, w2, 0, ne
	bhi	.L386
.L367:
	add	x20, x24, 8
	ldr	x3, [x26, 104]
	mov	x2, 80
	mov	x1, x19
	mov	x0, x20
	blr	x3
	str	wzr, [x23, 244]
.L366:
	ldr	x3, [x26, 104]
	mov	x2, 80
	mov	x1, x19
	mov	x0, x20
	blr	x3
	mov	w0, 2
	str	w0, [x23, 316]
	ldr	w0, [x19, 12]
	cmp	w0, 2
	beq	.L387
.L368:
	ldr	x0, .LC91
	ldr	w0, [x0]
	cmp	w0, 1
	beq	.L388
.L369:
	mov	w0, 0
	str	w22, [x23, 240]
.L363:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L388:
	ldr	w1, [x19, 12]
	cmp	w1, 17
	bne	.L369
	str	w0, [x24, 4]
	b	.L369
	.p2align 3
.L387:
	mov	w0, 3
	str	w0, [x23, 316]
	b	.L368
	.p2align 3
.L386:
	mov	x0, x28
	mov	x2, 32824
	add	x28, x28, 360448
	ldr	x3, [x26, 96]
	movk	x2, 0x5, lsl 16
	mov	w1, 0
	blr	x3
	str	w21, [x28, 24]
	str	x25, [x27, 112]
	stp	w20, w21, [x28, 28]
	str	w21, [x28, 36]
	b	.L367
	.p2align 3
.L384:
	add	x20, x24, 8
	ldr	x26, .LC90
	b	.L366
	.p2align 3
.L385:
	ldr	x26, .LC90
	b	.L367
	.p2align 3
.L364:
	mov	w0, -1
	b	.L363
	.size	SM_Config, .-SM_Config
	.align	3
.LC89:
	.xword	.LANCHOR0
	.align	3
.LC90:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC91:
	.xword	g_SegBypassEnable
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
	bhi	.L397
	cbnz	w20, .L398
	ldr	x1, .LC96
	add	x19, x1, x19, sxtw 4
	ldr	x2, [x19, 88]
	cbz	x2, .L393
	add	x2, x2, 458752
	ldr	w0, [x2, 244]
	cbz	w0, .L391
	ldp	w7, w5, [x1, 16]
	ldr	w4, [x1, 32]
	mov	w0, 0
	ldr	x6, [x1, 8]
	ldr	x3, [x1, 24]
	ldr	w1, [x1, 36]
	stp	w4, w1, [x2, 216]
	str	x6, [x2, 192]
	mov	w1, 4096
	stp	w5, w7, [x2, 200]
	str	x3, [x2, 208]
	str	wzr, [x2, 244]
	str	w1, [x2, 224]
.L391:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L397:
	ldr	x1, .LC93
	mov	w3, w19
	mov	w2, 1403
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L391
	.p2align 3
.L398:
	ldr	x1, .LC95
	mov	w3, w20
	mov	w2, 1410
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L391
.L393:
	mov	w0, -1
	b	.L391
	.size	SM_CfgBuf, .-SM_CfgBuf
	.align	3
.LC93:
	.xword	.LC92
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC96:
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
	bhi	.L401
	ldr	x0, .LC97
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	cbz	x0, .L404
	ldr	w1, [x0, 28]
	cbz	w1, .L404
	add	x1, x0, 458752
	ldr	w0, [x1, 256]
	cbnz	w0, .L404
	mov	w2, 1
	str	w2, [x1, 256]
.L400:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L404:
	mov	w0, -7
	b	.L400
	.p2align 3
.L401:
	mov	w0, -1
	b	.L400
	.size	SM_Start, .-SM_Start
	.align	3
.LC97:
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
	bhi	.L407
	ldr	x0, .LC98
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	cbz	x0, .L408
	add	x1, x0, 458752
	ldr	w0, [x1, 256]
	cbz	w0, .L406
	ldr	w0, [x1, 244]
	cmp	w0, wzr
	bgt	.L409
	mov	w0, 0
	str	wzr, [x1, 256]
.L406:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L409:
	mov	w0, -7
	b	.L406
	.p2align 3
.L408:
	mov	w0, 0
	b	.L406
	.p2align 3
.L407:
	mov	w0, -1
	b	.L406
	.size	SM_Stop, .-SM_Stop
	.align	3
.LC98:
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
	cmp	w20, 31
	ccmp	x19, xzr, 4, ls
	beq	.L428
	ldr	x3, .LC99
	mov	x2, 24
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, .LC100
	add	x20, x0, x20, sxtw 4
	ldr	x0, [x20, 88]
	cbz	x0, .L429
	add	x1, x0, 458752
	add	x2, x0, 98304
	adds	x4, x2, 112
	ldr	w3, [x1, 256]
	strb	w3, [x19]
	ldr	w1, [x1, 308]
	str	w1, [x19, 20]
	beq	.L422
	add	x3, x4, 360448
	ldr	w1, [x3, 12]
	ldr	w3, [x3, 8]
	sub	w1, w1, w3
	and	w1, w1, 4095
.L418:
	adds	x0, x0, 88
	str	w1, [x19, 8]
	cset	w3, eq
	cmn	x19, #4
	cset	w1, eq
	orr	w1, w3, w1
	cbnz	w1, .L428
	add	x5, x0, 98304
	ldr	w1, [x5, 4]
	ldr	w5, [x5]
	subs	w1, w1, w5
	bmi	.L430
	str	w1, [x19, 4]
.L420:
	cmn	x19, #12
	cset	w1, eq
	orr	w1, w3, w1
	cbnz	w1, .L428
	add	x0, x0, 98304
	ldr	w1, [x0, 20]
	str	w1, [x19, 12]
	ldr	w0, [x0, 12]
	sub	w0, w1, w0
	str	w0, [x19, 12]
	asr	w0, w0, 31
	cbnz	w0, .L424
	add	x1, x19, 16
	cmp	x1, xzr
	ccmp	x4, xzr, 4, ne
	beq	.L428
	add	x2, x2, 112
	add	x2, x2, 360448
	ldr	w1, [x2, 40]
	str	w1, [x19, 16]
.L424:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L429:
	cbz	x19, .L428
	strb	wzr, [x19]
.L428:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L430:
	add	w1, w1, 1024
	str	w1, [x19, 4]
	b	.L420
	.p2align 3
.L422:
	mov	w1, 0
	b	.L418
	.size	SM_GetInfo, .-SM_GetInfo
	.align	3
.LC99:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC100:
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
	b	.L432
	.p2align 3
.L434:
	ldr	w3, [x19]
	add	w3, w3, 1
	str	w3, [x19]
	ldr	w1, [x21]
	ldr	w3, [x4, 12]
	add	w3, w1, w3
	str	w3, [x21]
	ldr	w1, [x2, 4]
	cmp	w0, w1
	beq	.L436
	ldr	w1, [x19]
	cmp	w1, 1024
	bhi	.L436
.L432:
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
	cbnz	w1, .L434
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L436:
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
	cbz	w4, .L442
	uxtw	x7, w5
	lsl	x0, x7, 2
	sub	x0, x0, x7
	add	x0, x22, x0, lsl 5
	ldr	w6, [x0, 12]
	cmp	w6, 2
	bgt	.L443
	mov	w0, w6
	mov	w3, 3
	mov	w2, 0
	b	.L440
	.p2align 3
.L441:
	uxtw	x7, w5
	lsl	x0, x7, 2
	sub	x0, x0, x7
	add	x0, x22, x0, lsl 5
	ldr	w0, [x0, 12]
	add	w6, w6, w0
	cmp	w6, 2
	bgt	.L445
.L440:
	add	w2, w2, 1
	add	w5, w5, 1
	cmp	w2, w4
	sub	w3, w3, w0
	and	w5, w5, 1023
	bne	.L441
.L442:
	mov	w0, -4
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L445:
	sxtw	x3, w3
.L439:
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
.L443:
	mov	x3, 3
	mov	w2, 0
	b	.L439
	.size	AdjustRawPacketVP6A, .-AdjustRawPacketVP6A
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_LinkRawToSeg
	.type	SM_LinkRawToSeg, %function
SM_LinkRawToSeg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC101
	add	x0, x0, x20, sxtw 4
	ldr	x6, [x0, 88]
	cbz	x6, .L455
	add	x5, x6, 88
	add	x0, x6, 98304
	add	x0, x0, 112
	cmp	x5, xzr
	add	x1, x5, 98304
	ccmp	x0, xzr, 4, ne
	ccmp	x19, xzr, 4, ne
	ldr	w3, [x1]
	beq	.L455
	ldr	w1, [x1, 4]
	cmp	w3, w1
	beq	.L461
	uxtw	x3, w3
	lsl	x1, x3, 2
	sub	x1, x1, x3
	lsl	x1, x1, 5
	add	x7, x6, x1
	ldrb	w2, [x7, 88]
	cbnz	w2, .L462
	add	x4, x5, x1
	ldr	x8, [x4, 40]
	cbz	x8, .L463
	ldr	w1, [x6, 20]
	cmp	w1, 12
	beq	.L464
.L450:
	ldr	x1, .LC107
	ldr	x1, [x1, w20, sxtw 3]
	add	x1, x1, 507904
	ldr	w1, [x1, 1720]
	cmp	w1, 1
	beq	.L465
	ldr	w1, [x7, 96]
	str	w1, [x19, 16]
.L453:
	lsl	x1, x3, 2
	mov	w4, 1
	sub	x3, x1, x3
	mov	w2, w20
	mov	x1, x19
	add	x3, x5, x3, lsl 5
	ldr	x5, [x3, 40]
	str	x5, [x19]
	ldr	w5, [x7, 100]
	str	w5, [x19, 20]
	ldr	x5, [x3, 64]
	str	x5, [x19, 32]
	ldr	x5, [x3, 64]
	str	x5, [x19, 40]
	ldr	x5, [x3, 48]
	str	x5, [x19, 48]
	ldr	x5, [x3, 56]
	str	x5, [x19, 56]
	ldr	w5, [x3, 24]
	str	w5, [x19, 64]
	ldr	w5, [x3, 28]
	str	w5, [x19, 68]
	ldr	w5, [x3, 32]
	str	w5, [x19, 72]
	ldr	w3, [x3, 36]
	str	w3, [x19, 76]
	ldrb	w3, [x7, 89]
	strb	w3, [x19, 11]
	strb	w4, [x19, 10]
	bl	InsertStreamSeg
	mov	w0, 0
.L460:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L464:
	ldr	w1, [x7, 100]
	cbz	w1, .L450
	cmp	w1, 2
	bgt	.L466
	mov	x0, x5
	bl	DeleteRawLen
.L461:
	mov	w0, -4
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L465:
	ldr	w1, [x7, 92]
	str	w1, [x19, 16]
	b	.L453
.L466:
	add	x8, x8, 3
	str	x8, [x4, 40]
	sub	w1, w1, #3
	str	w1, [x7, 100]
	b	.L450
	.p2align 3
.L462:
	ldr	w1, [x7, 100]
	mov	x0, x5
	bl	DeleteRawLen
	ldr	x2, .LC102
	mov	w0, 0
	ldr	x1, .LC104
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -4
	b	.L460
	.p2align 3
.L463:
	ldr	w1, [x7, 100]
	mov	x0, x5
	bl	DeleteRawLen
	ldr	x2, .LC102
	mov	w0, 1
	ldr	x1, .LC106
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -4
	b	.L460
	.p2align 3
.L455:
	mov	w0, -1
	b	.L460
	.size	SM_LinkRawToSeg, .-SM_LinkRawToSeg
	.align	3
.LC101:
	.xword	.LANCHOR0
	.align	3
.LC102:
	.xword	.LANCHOR3
	.align	3
.LC104:
	.xword	.LC103
	.align	3
.LC106:
	.xword	.LC105
	.align	3
.LC107:
	.xword	s_pstVfmwChan
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
	cbz	x28, .L488
	add	x22, x28, 88
	add	x25, x28, 98304
	add	x0, x25, 112
	cmp	x22, xzr
	ccmp	x0, xzr, 4, ne
	str	x0, [x29, 104]
	ccmp	x26, xzr, 4, ne
	beq	.L488
	add	x0, x22, 98304
	ldp	w23, w4, [x0]
	cmp	w4, w23
	beq	.L508
	uxtw	x1, w23
	mov	w0, w23
	lsl	x2, x1, 2
	mov	x3, x1
	sub	x2, x2, x1
	mov	w21, 1
	add	x1, x22, x2, lsl 5
	ldr	w27, [x1, 12]
	b	.L470
	.p2align 3
.L472:
	add	w21, w21, 1
	ldr	w1, [x2, 12]
	cmp	w21, 1024
	ccmp	w4, w0, 4, ls
	add	w27, w27, w1
	beq	.L508
.L470:
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
	cbnz	w1, .L472
	ldr	x0, [x29, 104]
	cbz	x0, .L485
	ldr	x0, .LC109
	mov	x2, 32768
	mov	w1, 0
	movk	x2, 0x5, lsl 16
	ldr	x3, [x0, 96]
	add	x0, x25, 120
	blr	x3
	add	x0, x25, 112
	add	x0, x0, 360448
	ldr	w1, [x0, 24]
	stp	wzr, wzr, [x0, 8]
	str	wzr, [x0, 16]
	stp	w1, w1, [x0, 32]
.L485:
	add	x0, x25, 112
	add	x0, x0, 360448
	ldr	w1, [x0, 28]
	cmp	w1, w27
	blt	.L510
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
	beq	.L475
	cbz	w21, .L508
	uxtw	x20, w23
	lsl	x1, x20, 2
	sub	x1, x1, x20
	add	x1, x22, x1, lsl 5
	ldr	w25, [x1, 12]
	cmp	w25, 2
	bgt	.L489
	mov	w6, 3
	mov	w2, 0
	mov	w5, w25
	b	.L478
	.p2align 3
.L479:
	uxtw	x20, w23
	lsl	x1, x20, 2
	sub	x1, x1, x20
	add	x1, x22, x1, lsl 5
	ldr	w5, [x1, 12]
	add	w25, w25, w5
	cmp	w25, 2
	bgt	.L511
.L478:
	add	w2, w2, 1
	add	w23, w23, 1
	cmp	w2, w21
	sub	w6, w6, w5
	and	w23, w23, 1023
	bne	.L479
	.p2align 2
.L508:
	mov	w0, -4
.L505:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L511:
	sxtw	x6, w6
.L476:
	lsl	x1, x20, 2
	sub	w21, w21, w2
	sub	x1, x1, x20
	sub	w25, w25, #3
	add	x1, x22, x1, lsl 5
	ldr	x28, [x1, 40]
	add	x28, x28, x6
	.p2align 2
.L475:
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
	strb	w3, [x26, 10]
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
	cbz	w21, .L480
	cmp	x28, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L508
	ldr	x0, .LC109
	mov	w19, 0
	uxtw	x20, w23
	str	x0, [x29, 112]
	b	.L482
	.p2align 3
.L483:
	cmp	x28, xzr
	ccmp	x24, xzr, 4, ne
	beq	.L508
.L482:
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
	strb	w1, [x26, 11]
	str	w25, [x26, 20]
	ldr	w25, [x0, 12]
	ldr	x28, [x0, 40]
	bne	.L483
	ldr	x0, [x26]
.L480:
	cbz	x0, .L512
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
.L510:
	ldr	x1, .LC111
	mov	w2, w27
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, w27
	mov	x0, x22
	bl	DeleteRawLen
	cbz	w0, .L508
	ldr	x1, .LC113
	mov	w2, 1708
	mov	w0, 0
	bl	dprint_vfmw
	b	.L508
.L488:
	mov	w0, -1
	b	.L505
.L489:
	mov	x6, 3
	mov	w2, 0
	b	.L476
.L512:
	ldr	x2, .LC114
	mov	w3, 1769
	ldr	x1, .LC116
	mov	w0, 1
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -4
	b	.L505
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
	beq	.L517
	sub	w0, w19, #2
	cmp	w0, 1
	bls	.L517
	cmp	w19, 6
	mov	w0, 0
	ccmp	w19, 18, 4, ne
	cset	w1, eq
	cbnz	w1, .L514
	cmp	w19, 1
	beq	.L520
.L515:
	cmp	w19, 15
	cset	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L517:
	mov	w0, 0
.L514:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L520:
	ldr	w1, [x20]
	cbz	w1, .L515
	b	.L514
	.size	SCDDRV_IsSCDByPass, .-SCDDRV_IsSCDByPass
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCDDRV_SaveStreamSeg
	.type	SCDDRV_SaveStreamSeg, %function
SCDDRV_SaveStreamSeg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC117
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L521
	ldrsb	w0, [x20, 9]
	cmp	w0, 2
	beq	.L521
	mov	x1, x20
	mov	w0, w19
	bl	SCDDRV_SaveStreamSeg.part.6
.L521:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_SaveStreamSeg, .-SCDDRV_SaveStreamSeg
	.align	3
.LC117:
	.xword	vfmw_save_seg_file
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_ReadSegStream
	.type	SM_ReadSegStream, %function
SM_ReadSegStream:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x22, x1
	bl	_mcount
	cmp	x22, xzr
	ccmp	w20, 31, 2, ne
	bhi	.L536
	ldr	x0, .LC118
	add	x0, x0, x20, sxtw 4
	ldr	x19, [x0, 88]
	cbz	x19, .L536
	ldr	w0, [x19, 20]
	add	x1, x19, 36
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cbz	w0, .L531
	ldr	w0, [x19, 4]
	mov	x1, x22
	cmp	w0, 1
	mov	w0, w20
	beq	.L546
	bl	SM_CopyRawToSeg
	cbnz	w0, .L547
.L531:
	add	x0, x19, 98304
	mov	x1, x22
	add	x0, x0, 112
	add	x19, x19, 458752
	bl	SCDDRV_GetStreamSeg
	cbnz	w0, .L534
	ldr	x0, .LC119
	str	wzr, [x19, 308]
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L537
	ldrsb	w0, [x22, 9]
	mov	w21, 0
	cmp	w0, 2
	beq	.L530
	mov	x1, x22
	mov	w0, w20
	bl	SCDDRV_SaveStreamSeg.part.6
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L534:
	mov	w21, w0
	ldr	w0, [x19, 308]
	add	w0, w0, 1
	str	w0, [x19, 308]
.L530:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L546:
	bl	SM_LinkRawToSeg
	cbz	w0, .L531
.L547:
	add	x19, x19, 458752
	mov	w21, -7
	ldr	w0, [x19, 308]
	add	w0, w0, 1
	str	w0, [x19, 308]
	b	.L530
	.p2align 3
.L537:
	mov	w21, 0
	b	.L530
	.p2align 3
.L536:
	mov	w21, -1
	b	.L530
	.size	SM_ReadSegStream, .-SM_ReadSegStream
	.align	3
.LC118:
	.xword	.LANCHOR0
	.align	3
.LC119:
	.xword	vfmw_save_seg_file
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
	bhi	.L551
	ldr	x0, .LC120
	add	x19, x0, x19, sxtw 4
	ldr	x19, [x19, 88]
	cbz	x19, .L551
	add	x0, x19, 98304
	mov	w1, w20
	add	x0, x0, 112
	bl	ReleaseStreamSeg
	cbnz	w0, .L552
	ldr	w0, [x19, 4]
	mov	w20, 0
	cbz	w0, .L549
	mov	w1, 1
	add	x0, x19, 88
	bl	DeleteRawPacket
.L549:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L551:
	mov	w20, -1
	b	.L549
	.p2align 3
.L552:
	mov	w20, -3
	b	.L549
	.size	SM_ReleaseStreamSeg, .-SM_ReleaseStreamSeg
	.align	3
.LC120:
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
	ldr	x1, .LC121
	mov	w0, 0
	ldr	x1, [x1, 256]
	blr	x1
	ldp	x29, x30, [sp], 16
	ret
	.size	SM_GiveThreadEvent, .-SM_GiveThreadEvent
	.align	3
.LC121:
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
	ldr	x0, .LC122
	ldr	x0, [x0]
	blr	x0
	mov	w3, w0
	add	x1, x19, 458752
	cbnz	w20, .L560
	ldr	w2, [x1, 272]
	cmp	w0, w2
	bhi	.L561
	str	wzr, [x1, 268]
	mov	w0, 0
	str	w3, [x1, 272]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L561:
	sub	w0, w0, w2
	str	w0, [x1, 268]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L560:
	str	wzr, [x1, 268]
	mov	w0, 0
	str	w3, [x1, 272]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CalcInstBlockTime, .-CalcInstBlockTime
	.align	3
.LC122:
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
	ldr	x0, .LC123
	ldr	w1, [x0, 56]
	cmp	w1, 1
	beq	.L565
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L565:
	ldr	w0, [x0, 52]
	cmp	w0, w19
	ldr	x19, [sp, 16]
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	SCDDRV_IsChanDec, .-SCDDRV_IsChanDec
	.align	3
.LC123:
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
	cbnz	w3, .L567
	add	x0, x19, 98304
	ldr	w3, [x0, 20]
	str	w3, [x20]
	ldr	w0, [x0, 12]
	sub	w3, w3, w0
	str	w3, [x20]
.L567:
	cmp	x21, xzr
	cset	w0, eq
	orr	w0, w1, w0
	cbnz	w0, .L566
	add	x19, x19, 98304
	ldp	w1, w0, [x19]
	subs	w0, w0, w1
	bmi	.L573
.L572:
	str	w0, [x21]
.L566:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L573:
	add	w0, w0, 1024
	b	.L572
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
	beq	.L574
	mov	x1, x20
	mov	x0, x19
	bl	GetFreeSegBufSize.part.7
.L574:
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
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x21, x0
	mov	x0, x30
	mov	x23, x4
	mov	x20, x2
	mov	w19, w1
	mov	x22, x3
	bl	_mcount
	cmp	x21, xzr
	str	wzr, [x23]
	ccmp	x20, xzr, 4, ne
	bne	.L583
.L577:
	ldr	w1, [x20]
	add	w0, w19, 79
	mov	w3, 0
	cmp	w1, w0
	bcc	.L578
	sub	w1, w1, w19
	sub	w3, w1, #79
.L578:
	add	x2, x21, 360448
	str	w3, [x20]
	ldr	w1, [x2, 28]
	lsl	w0, w1, 3
	sub	w0, w0, w1
	cmp	w0, wzr
	add	w1, w0, 7
	csel	w0, w1, w0, lt
	cmp	w19, w0, asr 3
	bcc	.L579
	add	w19, w3, w19
	str	w19, [x20]
	mov	w0, 1
	str	w0, [x23]
.L579:
	cbz	x21, .L582
	ldp	w0, w1, [x2, 8]
	mov	w2, 4096
	sub	w0, w1, w0
	and	w0, w0, 4095
	sub	w0, w2, w0
	str	w0, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L583:
	mov	x1, x20
	mov	x0, x21
	bl	GetFreeSegBufSize.part.7
	b	.L577
	.p2align 3
.L582:
	mov	w0, 4096
	str	w0, [x22]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
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
	cmp	w19, 1024
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
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	mov	x21, x3
	mov	x20, x1
	mov	w24, w2
	mov	x22, x4
	mov	x23, x5
	mov	x25, x6
	bl	_mcount
	cmp	x21, xzr
	ccmp	x19, xzr, 4, ne
	beq	.L588
	add	x1, x19, 98304
	ldr	w0, [x1, 20]
	str	w0, [x21]
	ldr	w1, [x1, 12]
	sub	w0, w0, w1
	str	w0, [x21]
.L588:
	cbz	x19, .L592
	add	x19, x19, 98304
	ldr	w3, [x21]
	mov	w0, -5
	ldp	w1, w2, [x19]
	sub	w2, w2, w1
	cmp	w2, wzr
	add	w1, w2, 1024
	csel	w2, w1, w2, lt
	cmp	w3, 3
	ccmp	w2, wzr, 4, hi
	cset	w1, eq
	cbnz	w1, .L589
	mov	x0, x20
	mov	x4, x25
	mov	x3, x23
	mov	x2, x22
	mov	w1, w24
	bl	SCDDRV_GetSegStreamStatus
	ldr	w0, [x23]
	cmp	w0, 1024
	bls	.L594
	add	x20, x20, 360448
	ldr	w1, [x22]
	mov	w0, -6
	ldr	w2, [x20, 28]
	cmp	w1, w2, lsr 3
	csel	w0, w0, wzr, ls
.L589:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L592:
	mov	w0, -5
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L594:
	mov	w0, -6
	b	.L589
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
	ldr	w1, [x20, 20]
	cmp	w1, 18
	beq	.L602
	cmp	w1, 6
	cset	w5, eq
	cmp	w1, 1
	cset	w4, eq
	cmp	w1, 15
	cset	w0, eq
	mov	w6, w5
	orr	w4, w4, w0
.L597:
	add	x0, x20, 458752
	mov	w2, 1
	strb	w2, [x19, 2]
	mov	x2, 112
	movk	x2, 0x7, lsl 16
	ldr	w3, [x0, 204]
	add	x2, x20, x2
	str	w3, [x19, 4]
	ldr	x3, [x0, 192]
	str	x3, [x19, 8]
	ldr	w3, [x0, 216]
	str	w3, [x19, 24]
	ldr	w7, [x0, 224]
	ldr	w3, [x0, 316]
	mul	w3, w3, w7
	str	w3, [x19, 28]
	ldr	w3, [x2, 24]
	str	w3, [x19, 32]
	ldp	w7, w3, [x2, 24]
	add	w3, w7, w3
	str	w3, [x19, 36]
	ldr	w3, [x0, 488]
	cmp	w3, 1
	beq	.L607
	ldr	w2, [x0, 484]
	str	w2, [x19, 40]
.L599:
	mov	w2, 1
	strb	w2, [x19]
	ldr	w3, [x20, 48]
	str	w3, [x19, 52]
	str	w6, [x19, 68]
	cbnz	w4, .L603
	sub	w3, w1, #2
	cmp	w3, 1
	cset	w3, ls
	orr	w5, w5, w3
	cbnz	w5, .L608
	strb	wzr, [x19, 1]
.L609:
	mov	w2, 1
	stp	w1, w2, [x19, 44]
	stp	w2, w2, [x19, 56]
	ldr	w0, [x0, 464]
	str	w0, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L608:
	strb	w2, [x19, 1]
	mov	w2, 1
	stp	w1, w2, [x19, 44]
	stp	w2, w2, [x19, 56]
	ldr	w0, [x0, 464]
	str	w0, [x19, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L603:
	mov	w1, 0
	strb	wzr, [x19, 1]
	b	.L609
	.p2align 3
.L607:
	ldr	w2, [x2, 36]
	add	w2, w2, 3
	and	w2, w2, -4
	str	w2, [x19, 40]
	b	.L599
	.p2align 3
.L602:
	mov	w5, 1
	mov	w4, 0
	mov	w6, w5
	mov	w1, 6
	b	.L597
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
	add	x19, x20, 458752
	mov	w22, w1
	mov	w21, w2
	bl	_mcount
	cmp	w22, w21
	str	w22, [x19, 288]
	str	w21, [x19, 292]
	bls	.L613
	strb	wzr, [x20, 2]
.L612:
	mov	w1, 1
	ldr	x0, .LC124
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
.L613:
	mov	w0, 1
	strb	w0, [x20, 2]
	b	.L612
	.size	SCDDRV_RecordStartState, .-SCDDRV_RecordStartState
	.align	3
.LC124:
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
	ldr	x0, .LC125
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L621
	cmp	w20, 4
	ldr	x22, .LC126
	beq	.L622
.L617:
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
.L621:
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
.L622:
	add	x0, x22, x19, lsl 2
	ldr	w0, [x0, 80]
	add	w0, w0, 4
	cbnz	w21, .L618
	bl	MEM_ReadPhyWord
	uxth	w21, w0
	b	.L617
	.p2align 3
.L618:
	bl	MEM_ReadPhyWord
	orr	w21, w0, 65536
	b	.L617
	.size	SCD_ConfigReg, .-SCD_ConfigReg
	.align	3
.LC125:
	.xword	g_HalDisable
	.align	3
.LC126:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteScdVtrlReg
	.type	WriteScdVtrlReg, %function
WriteScdVtrlReg:
	stp	x29, x30, [sp, -272]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w24, w0
	mov	x0, x30
	mov	x19, x1
	mov	w21, w2
	bl	_mcount
	ldr	x20, .LC127
	ldrb	w0, [x20]
	cmp	w0, 1
	beq	.L624
	ldr	x3, .LC128
	add	x0, x29, 80
	mov	x2, 188
	mov	w1, 0
	mov	x23, x0
	ldr	x3, [x3, 96]
	blr	x3
.L625:
	ldrb	w0, [x20]
	ldr	w1, [x19, 4]
	cmp	w0, 1
	bne	.L662
	ldr	x22, .LC129
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2052
	bl	MEM_WritePhyWord
.L627:
	ldrb	w0, [x20]
	ldr	w1, [x19, 24]
	cmp	w0, 1
	bne	.L663
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2056
	bl	MEM_WritePhyWord
.L629:
	ldrb	w0, [x20]
	ldr	w1, [x19, 28]
	cmp	w0, 1
	bne	.L664
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2060
	bl	MEM_WritePhyWord
.L631:
	ldrb	w0, [x20]
	ldr	w1, [x19, 32]
	cmp	w0, 1
	bne	.L665
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2064
	bl	MEM_WritePhyWord
.L633:
	ldrb	w0, [x20]
	ldr	w1, [x19, 36]
	cmp	w0, 1
	bne	.L666
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2068
	bl	MEM_WritePhyWord
.L635:
	ldrb	w0, [x20]
	ldr	w1, [x19, 40]
	cmp	w0, 1
	bne	.L667
	add	x0, x22, x21, sxtw 2
	sxtw	x25, w24
	ldr	w0, [x0, 80]
	add	w0, w0, 2072
	bl	MEM_WritePhyWord
	add	x0, x22, x25, lsl 4
	ldr	x0, [x0, 88]
	add	x0, x0, 458752
	ldr	w1, [x0, 488]
	cmp	w1, 1
	beq	.L668
.L638:
	mov	w2, 3
	ldr	w1, [x0, 472]
	movk	w2, 0x300, lsl 16
	cmp	w1, w2
	beq	.L669
.L643:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L670
	add	x0, x22, x21, sxtw 2
	add	x25, x22, x25, lsl 4
	ldr	w0, [x0, 80]
	add	w0, w0, 2108
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	cmp	w0, 1
	ldr	x0, [x25, 88]
	add	x0, x0, 458752
	ldrh	w1, [x0, 468]
	bne	.L671
.L649:
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2116
	bl	MEM_WritePhyWord
.L642:
	ldp	w0, w4, [x19, 52]
	ldr	w2, [x19, 44]
	ldr	w5, [x19, 60]
	lsl	w0, w0, 8
	and	w2, w2, 15
	ldrb	w1, [x19, 1]
	orr	w2, w2, w4, lsl 13
	ldrb	w4, [x20]
	orr	w3, w0, w5, lsl 9
	ubfiz	w1, w1, 4, 1
	cmp	w4, 1
	orr	w0, w3, w2
	orr	w1, w0, w1
	bne	.L672
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 80]
	add	w0, w0, 2080
	bl	MEM_WritePhyWord
	ldr	w0, [x19, 52]
	cbnz	w0, .L673
.L652:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L674
	add	x0, x22, x21, sxtw 2
	mov	w1, 0
	ldr	w0, [x0, 80]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldrb	w25, [x20]
	cmp	w25, 1
	beq	.L656
.L677:
	ldr	w1, [x19, 52]
	add	x0, x29, 80
	strb	w21, [x29, 80]
	strb	w1, [x29, 81]
	stp	wzr, w24, [x29, 84]
	bl	VDH_PostTask
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 272
	ret
	.p2align 3
.L669:
	ldrh	w0, [x0, 468]
	cbnz	w0, .L643
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L675
	add	x0, x22, x21, sxtw 2
	mov	w1, 3
	ldr	w0, [x0, 80]
	add	w0, w0, 2108
	bl	MEM_WritePhyWord
.L645:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L676
	add	x0, x22, x21, sxtw 2
	mov	w1, 0
	ldr	w0, [x0, 80]
	add	w0, w0, 2116
	bl	MEM_WritePhyWord
	b	.L642
	.p2align 3
.L670:
	mov	w3, w1
	mov	x0, x23
	mov	w1, 1
	mov	w2, 2108
	add	x25, x22, x25, lsl 4
	bl	VDH_Record_RegData
	ldrb	w0, [x20]
	cmp	w0, 1
	ldr	x0, [x25, 88]
	add	x0, x0, 458752
	ldrh	w1, [x0, 468]
	beq	.L649
.L671:
	mov	w3, w1
	mov	w2, 2116
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L642
	.p2align 3
.L674:
	mov	w3, 0
	mov	w2, 2076
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	ldrb	w25, [x20]
	cmp	w25, 1
	bne	.L677
.L656:
	add	x21, x22, x21, sxtw 2
	mov	w1, 0
	ldr	w0, [x21, 80]
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
	ldrb	w0, [x20]
	ldrb	w1, [x19, 2]
	cmp	w0, 1
	and	w1, w1, 1
	bne	.L678
	ldr	w0, [x21, 80]
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 272
	ret
	.p2align 3
.L672:
	mov	w3, w1
	mov	x0, x23
	mov	w2, 2080
	mov	w1, 1
	bl	VDH_Record_RegData
	ldr	w0, [x19, 52]
	cbz	w0, .L652
.L673:
	ldrb	w0, [x20]
	ldr	w1, [x19, 68]
	cmp	w0, 1
	bne	.L679
	add	x0, x22, x21, sxtw 2
	ldr	w0, [x0, 80]
	bl	MEM_WritePhyWord
	b	.L652
	.p2align 3
.L667:
	mov	w3, w1
	mov	x0, x23
	mov	w1, 1
	mov	w2, 2072
	sxtw	x25, w24
	bl	VDH_Record_RegData
	add	x0, x22, x25, lsl 4
	ldr	x0, [x0, 88]
	add	x0, x0, 458752
	ldr	w1, [x0, 488]
	cmp	w1, 1
	bne	.L638
.L668:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L680
	add	x0, x22, x21, sxtw 2
	mov	w1, -1
	ldr	w0, [x0, 80]
	add	w0, w0, 2108
	bl	MEM_WritePhyWord
.L640:
	ldrb	w0, [x20]
	cmp	w0, 1
	bne	.L681
	add	x0, x22, x21, sxtw 2
	mov	w1, -1
	ldr	w0, [x0, 80]
	add	w0, w0, 2116
	bl	MEM_WritePhyWord
	b	.L642
	.p2align 3
.L666:
	mov	w3, w1
	mov	w2, 2068
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L635
	.p2align 3
.L665:
	mov	w3, w1
	mov	w2, 2064
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L633
	.p2align 3
.L664:
	mov	w3, w1
	mov	w2, 2060
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L631
	.p2align 3
.L663:
	mov	w3, w1
	mov	w2, 2056
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L629
	.p2align 3
.L662:
	mov	w3, w1
	mov	w2, 2052
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	ldr	x22, .LC129
	b	.L627
	.p2align 3
.L624:
	mov	w0, w21
	mov	x23, 0
	bl	ResetSCD
	b	.L625
	.p2align 3
.L679:
	mov	w3, w1
	mov	w2, 0
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L652
	.p2align 3
.L678:
	mov	w3, w1
	mov	x0, x23
	mov	w1, w25
	mov	w2, 2048
	bl	VDH_Record_RegData
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 272
	ret
	.p2align 3
.L680:
	mov	w3, -1
	mov	w2, 2108
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L640
	.p2align 3
.L681:
	mov	w3, -1
	mov	w2, 2116
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L642
	.p2align 3
.L675:
	mov	w3, 3
	mov	w2, 2108
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L645
	.p2align 3
.L676:
	mov	w3, 0
	mov	w2, 2116
	mov	w1, 1
	mov	x0, x23
	bl	VDH_Record_RegData
	b	.L642
	.size	WriteScdVtrlReg, .-WriteScdVtrlReg
	.align	3
.LC127:
	.xword	g_HalDisable
	.align	3
.LC128:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC129:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	WriteScdMsg
	.type	WriteScdMsg, %function
WriteScdMsg:
	stp	x29, x30, [sp, -240]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w7, w0
	mov	x27, x1
	mov	x0, x30
	mov	x26, x4
	sxtw	x1, w7
	mov	x22, x3
	mov	x19, x1
	mov	w23, w2
	stp	w5, w2, [x29, 128]
	str	w6, [x29, 116]
	str	x1, [x29, 104]
	bl	_mcount
	ldr	x0, .LC132
	mov	x2, 16384
	ldr	x11, .LC133
	mov	w1, 0
	add	x0, x0, x19, lsl 4
	str	x11, [x29, 136]
	stp	xzr, xzr, [x29, 144]
	ldr	x3, [x11, 96]
	ldr	x24, [x0, 88]
	stp	xzr, xzr, [x29, 160]
	add	x0, x24, 458752
	add	x20, x0, 600
	mov	x21, x0
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	stp	xzr, xzr, [x29, 208]
	stp	xzr, xzr, [x29, 224]
	add	x19, x0, 480
	mov	x0, x20
	str	x21, [x29, 96]
	add	x28, x21, 476
	blr	x3
	str	x22, [x29, 120]
	add	x1, x29, 144
	mov	x0, x22
	bl	GetFirstRawPacket
	str	wzr, [x26, 8]
	ldr	w3, [x29, 156]
	stp	wzr, wzr, [x26]
	cmp	w3, w23
	str	wzr, [x27, 4]
	bgt	.L683
	ldr	x0, [x29, 120]
	mov	w22, w3
	ldr	x11, [x29, 136]
	mov	w25, 0
	mov	w23, 0
	mov	w24, 0
	mov	w2, w3
	add	x21, x0, 98304
	.p2align 2
.L686:
	cmp	w2, wzr
	ubfiz	x1, x25, 4, 32
	add	x12, x26, x23, sxtw 2
	add	x13, x20, x1
	add	w24, w24, 1
	ble	.L684
	ldr	w0, [x29, 148]
	add	w25, w25, 1
	str	w0, [x26, w23, sxtw 2]
	add	w23, w23, 3
	sub	w0, w0, #1
	ldr	x14, [x29, 184]
	add	w0, w0, w2
	ldr	w2, [x29, 128]
	add	w2, w2, w23, lsl 2
	stp	w0, w2, [x12, 4]
	str	x14, [x20, x1]
	ldr	x0, [x29, 184]
	ldrsw	x1, [x29, 156]
	sub	x0, x0, #1
	add	x0, x0, x1
	str	x0, [x13, 8]
	str	wzr, [x29, 156]
.L684:
	str	w22, [x27, 4]
	ldr	w12, [x21, 16]
	cmp	w12, 1023
	bls	.L738
.L685:
	ldr	w0, [x29, 116]
	cbz	w0, .L739
.L687:
	cbz	w24, .L704
	cmp	w23, wzr
	ble	.L690
	add	x4, x26, x23, sxtw 2
	str	wzr, [x4, -4]
.L690:
	ldr	x0, [x29, 104]
	mov	w2, 6
	ldr	x1, .LC132
	ldr	w4, [x27, 4]
	add	x26, x1, x0, lsl 4
	cmp	w4, w2
	csel	w4, w4, w2, le
	ldr	x0, [x26, 88]
	cmp	w4, 5
	add	x0, x0, 458752
	ldr	w1, [x0, 480]
	str	w1, [x0, 472]
	ldrh	w1, [x0, 476]
	strh	w1, [x0, 468]
	bls	.L740
.L707:
	mov	w10, 2
	mov	w9, 4
.L691:
	cmp	w25, wzr
	mov	w8, w25
	mov	x11, -16
	ble	.L700
	.p2align 2
.L722:
	add	x0, x11, x8, sxtw 4
	add	x1, x20, x0
	ldr	x3, [x20, x0]
	ldr	x2, [x1, 8]
	add	w0, w2, 1
	sub	w3, w0, w3
	cmp	w3, w9
	csel	w4, w3, w9, ls
	cbz	w9, .L696
	cbz	w4, .L699
	mov	x0, 0
	.p2align 2
.L698:
	neg	x1, x0
	ldrb	w1, [x1, x2]
	strb	w1, [x19, x0]
	add	x0, x0, 1
	cmp	w4, w0
	bhi	.L698
	sub	w0, w4, #1
	subs	w9, w9, w4
	add	x0, x0, 1
	add	x19, x19, x0
	beq	.L696
.L699:
	subs	w8, w8, #1
	bne	.L722
	.p2align 2
.L700:
	mov	w0, 1
	str	w24, [x27]
	str	w0, [x27, 8]
	mov	w0, 0
.L735:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
	.p2align 3
.L696:
	cbz	w10, .L700
	sub	w1, w3, w4
	sub	x2, x2, x4, uxtw
	cmp	w1, w10
	csel	w1, w1, w10, ls
	cbz	w1, .L736
	mov	x0, 0
	.p2align 2
.L702:
	neg	x3, x0
	ldrb	w3, [x3, x2]
	strb	w3, [x28, x0]
	add	x0, x0, 1
	cmp	w1, w0
	bhi	.L702
	sub	w0, w1, #1
	subs	w10, w10, w1
	add	x0, x0, 1
	add	x28, x28, x0
	beq	.L700
.L736:
	mov	w9, 0
	b	.L699
	.p2align 3
.L738:
	sxtw	x13, w12
	ldr	x3, [x29, 120]
	lsl	x1, x13, 2
	mov	x2, 96
	sub	x1, x1, x13
	ldr	w13, [x21, 4]
	add	x0, x29, 144
	cmp	w12, w13
	add	x1, x3, x1, lsl 5
	beq	.L685
	ldr	x12, [x11, 104]
	str	x11, [x29, 136]
	blr	x12
	ldr	w0, [x21, 16]
	ldr	w2, [x29, 156]
	add	w0, w0, 1
	ldr	w3, [x29, 132]
	asr	w1, w0, 31
	add	w22, w22, w2
	lsr	w1, w1, 22
	cmp	w3, w22
	add	w0, w0, w1
	mov	w3, 1023
	and	w0, w0, w3
	ccmp	w24, w3, 0, ge
	sub	w0, w0, w1
	str	w0, [x21, 16]
	ldr	x11, [x29, 136]
	ble	.L686
	ldr	w0, [x29, 116]
	cbnz	w0, .L687
.L739:
	ldr	w0, [x29, 156]
	cbz	w0, .L687
.L705:
	ldr	w3, [x29, 132]
	ldr	w1, [x27, 4]
	sub	w2, w3, #16
	cmp	w1, w2
	bge	.L687
	cmp	w3, w22
	mov	w2, 1023
	ccmp	w24, w2, 0, lt
	bgt	.L687
	sub	w1, w3, w1
	cmp	w0, w1
	blt	.L687
	ldr	w0, [x29, 148]
	add	w24, w24, 1
	str	w0, [x26, w23, sxtw 2]
	sub	w0, w0, #1
	str	w1, [x29, 156]
	add	w1, w0, w1
	add	x0, x26, x23, sxtw 2
	add	w23, w23, 3
	str	w1, [x0, 4]
	ldr	w1, [x29, 128]
	add	w1, w1, w23, lsl 2
	str	w1, [x0, 8]
	ubfiz	x0, x25, 4, 32
	ldr	x1, [x29, 184]
	add	w25, w25, 1
	str	x1, [x20, x0]
	add	x0, x20, x0
	ldr	x1, [x29, 184]
	sub	x2, x1, #1
	ldrsw	x1, [x29, 156]
	add	x1, x2, x1
	str	x1, [x0, 8]
	ldr	w1, [x27, 4]
	ldr	w0, [x29, 156]
	str	wzr, [x29, 156]
	add	w0, w1, w0
	str	w0, [x27, 4]
	b	.L687
	.p2align 3
.L740:
	cmp	w4, 1
	beq	.L741
	mov	x0, 3
	sub	w9, w4, #2
	sub	x9, x0, x9
	subs	w2, w2, w4
	ldr	x0, [x29, 96]
	add	x12, x0, 477
	beq	.L707
	mov	w0, 0
	mov	w11, 2
	.p2align 2
.L693:
	uxtw	x1, w0
	sub	w2, w2, #1
	sub	x3, x9, x1
	sub	x1, x12, x1
	add	w0, w0, 1
	cmp	w2, wzr
	ccmp	w0, 1, 2, ne
	sub	w10, w11, w0
	ldrb	w3, [x19, x3]
	strb	w3, [x1]
	bls	.L693
	mov	w9, 4
	cbnz	w10, .L691
	ldr	x0, [x29, 96]
	add	x5, x0, 483
	mov	x0, 3
	sub	x4, x0, x4, uxtw
	cbz	w2, .L691
	mov	w1, 0
	.p2align 2
.L694:
	uxtw	x0, w1
	add	w1, w1, 1
	sub	x3, x4, x0
	sub	x0, x5, x0
	cmp	w2, w1
	ldrb	w3, [x19, x3]
	strb	w3, [x0]
	bne	.L694
	mov	w9, 4
	sub	w9, w9, w2
	b	.L691
.L741:
	ldr	x2, [x29, 96]
	mov	w10, 0
	mov	w9, w4
	ldrb	w0, [x2, 483]
	ldrb	w1, [x2, 476]
	strb	w0, [x2, 476]
	ldrb	w0, [x2, 481]
	strb	w1, [x2, 477]
	ldrb	w1, [x2, 482]
	strb	w0, [x2, 482]
	ldrb	w0, [x2, 480]
	strb	w1, [x2, 483]
	strb	w0, [x2, 481]
	b	.L691
.L683:
	ldr	w0, [x29, 116]
	cbnz	w0, .L704
	cbz	w3, .L704
	mov	w0, w3
	mov	w25, 0
	mov	w22, w3
	mov	w23, 0
	mov	w24, 0
	b	.L705
.L704:
	mov	w0, -6
	b	.L735
	.size	WriteScdMsg, .-WriteScdMsg
	.align	3
.LC132:
	.xword	.LANCHOR0
	.align	3
.LC133:
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
	add	x19, x1, 458752
	mov	x22, x0
	mov	x0, x30
	mov	x20, x1
	mov	w25, w2
	mov	w24, w3
	bl	_mcount
	add	x21, x19, 168
	ldr	w0, [x19, 240]
	add	x20, x20, 88
	ldr	w27, [x19, 204]
	ldr	x26, [x19, 192]
	bl	VCTRL_IfEsBufEnable
	cbz	w0, .L746
	ldr	x23, .LC136
	mov	x2, 12
	mov	w1, 0
	mov	x0, x21
	ldr	x3, [x23, 96]
	blr	x3
	ldr	w0, [x19, 240]
	mov	x3, x20
	ldr	w6, [x22, 52]
	mov	w5, w27
	mov	x4, x26
	mov	w2, w25
	mov	x1, x21
	bl	WriteScdMsg
	mov	w20, w0
	cbnz	w0, .L744
	ldr	x0, [x23]
	blr	x0
	sxtw	x3, w24
	ldr	x4, .LC137
	lsl	x1, x3, 4
	mov	w2, w24
	sub	x3, x1, x3
	mov	x1, x22
	add	x3, x4, x3, lsl 2
	str	w0, [x3, 48]
	ldr	w0, [x19, 240]
	bl	WriteScdVtrlReg
.L744:
	mov	w0, w20
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L746:
	ldr	x1, .LC135
	mov	w0, 1
	ldr	w2, [x19, 240]
	mov	w20, -7
	bl	dprint_vfmw
	b	.L744
	.size	SCDDRV_StartSCD, .-SCDDRV_StartSCD
	.align	3
.LC135:
	.xword	.LC134
	.align	3
.LC136:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC137:
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
	mov	x21, x0
	mov	x0, x30
	mov	w22, w1
	add	x19, x21, 458752
	bl	_mcount
	str	wzr, [x29, 64]
	add	x6, x29, 144
	add	x1, x21, 98304
	ldr	w2, [x19, 496]
	add	x5, x29, 60
	add	x4, x29, 64
	add	x3, x29, 56
	str	wzr, [x6, -76]!
	add	x1, x1, 112
	add	x0, x21, 88
	stp	wzr, wzr, [x29, 56]
	bl	SCDDRV_CheckConditionOfStartSCD
	mov	w20, w0
	cbnz	w0, .L755
	ldr	w0, [x29, 68]
	cmp	w0, wzr
	ccmp	x21, xzr, 4, ne
	beq	.L750
	ldr	x2, .LC140
	add	x4, x19, 256
	mov	w0, -1
	strh	w0, [x19, 468]
	strh	w0, [x19, 476]
	mov	w1, 1
	str	w0, [x19, 472]
	ldr	x3, [x2, 96]
	mov	x2, 88
	stp	w0, wzr, [x4, 224]
	stp	w1, wzr, [x4, 232]
	str	wzr, [x19, 496]
	mov	w1, 0
	str	wzr, [x19, 500]
	add	x0, x19, 512
	str	wzr, [x19, 504]
	blr	x3
.L750:
	ldr	w0, [x19, 240]
	mov	w1, w22
	bl	SM_CfgBuf
	mov	w20, w0
	cbnz	w0, .L756
	ldr	w3, [x19, 316]
	mov	x0, x21
	ldr	w2, [x29, 60]
	add	x1, x29, 72
	str	w2, [x19, 224]
	mul	w2, w2, w3
	lsl	w2, w2, 2
	str	w2, [x19, 220]
	bl	SCDDRV_SetCtrlReg
	ldr	w2, [x29, 64]
	mov	w3, w22
	mov	x1, x21
	add	x0, x29, 72
	bl	SCDDRV_StartSCD
	mov	w2, w0
	cbnz	w0, .L749
	ldr	w1, [x29, 56]
	ldr	w0, [x29, 64]
	str	w1, [x19, 288]
	cmp	w1, w0
	str	w0, [x19, 292]
	bls	.L757
	strb	wzr, [x21, 2]
.L753:
	mov	w1, 1
	ldr	x0, .LC140
	str	w1, [x19, 248]
	strb	wzr, [x21, 3]
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 312]
	mov	w2, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, w2
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L756:
	ldr	x1, .LC142
	mov	w2, w0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w2, w20
.L749:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, w2
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L755:
	ldr	x1, .LC139
	mov	w2, w0
	mov	w0, 26
	bl	dprint_vfmw
	mov	w2, w20
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	mov	w0, w2
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L757:
	mov	w0, 1
	strb	w0, [x21, 2]
	b	.L753
	.size	CutStreamWithSCD, .-CutStreamWithSCD
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC140:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC142:
	.xword	.LC141
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
	ldr	x1, .LC143
	add	x19, x1, x19, sxtw 2
	ldr	w0, [x19, 80]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	and	w0, w0, 1
	str	w0, [x20]
	ldr	w0, [x19, 80]
	add	w0, w0, 2124
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
	ldr	w1, [x19, 80]
	add	w0, w1, 2140
	bl	MEM_ReadPhyWord
	str	w0, [x20, 28]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ReadScdStateReg, .-ReadScdStateReg
	.align	3
.LC143:
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
	beq	.L762
	orr	w0, w0, 1
	strb	w0, [x19]
.L761:
	ldr	w1, [x20, 4]
	ldrb	w0, [x19]
	lsr	w1, w1, 30
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
.L762:
	and	w0, w0, -2
	strb	w0, [x19]
	b	.L761
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
	cbz	x20, .L769
	ldr	w0, [x20, 16]
	cbz	w0, .L771
	ldr	x0, [x20]
	cbz	x0, .L771
	cbz	x19, .L772
	add	x1, x19, 360448
	ldp	w2, w0, [x1, 32]
	cmp	w0, w2
	sub	w2, w2, #1
	bhi	.L774
	sub	w0, w2, w0
	bcc	.L766
	ldr	w0, [x1, 28]
	sub	w0, w0, #1
.L766:
	ldr	w2, [x20, 20]
	mov	w1, -7
	cmp	w2, w0
	csel	w0, wzr, w1, ls
.L765:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L774:
	ldr	w1, [x1, 28]
	add	w2, w2, w1
	sub	w0, w2, w0
	b	.L766
	.p2align 3
.L772:
	mov	w0, 0
	b	.L766
	.p2align 3
.L771:
	mov	w0, -7
	b	.L765
.L769:
	mov	w0, -1
	b	.L765
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
	strb	w0, [x19, 12]
	ldr	x0, [x21]
	cmp	x1, x0
	beq	.L778
.L776:
	str	x1, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L778:
	ldr	x0, .LC144
	ldr	x0, [x0, w22, sxtw 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 1732]
	cbnz	w0, .L776
	mov	x0, -1
	str	x0, [x19, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	GetSegPts, .-GetSegPts
	.align	3
.LC144:
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
	beq	.L784
	cmp	w19, 2
	mov	w0, 0
	beq	.L785
	mov	w1, -33488896
	cmp	w20, w1
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L784:
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
.L785:
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
	beq	.L795
	add	x3, x3, 360448
	mov	w0, 4096
	ldp	w10, w1, [x3, 8]
	sub	w10, w1, w10
	and	w10, w10, 4095
	sub	w10, w0, w10
.L787:
	sub	w3, w19, #1
	mov	w5, w3
	tbnz	w3, #31, .L796
	add	x21, x21, 458752
	add	x0, x2, 112
	add	x0, x0, 360448
	ldr	x7, [x2, 112]
	mov	w8, -33488896
	mov	w11, -1241448448
	ldr	w2, [x21, 316]
	ldr	w1, [x0, 24]
	ldr	w6, [x21, 260]
	mul	w4, w3, w2
	b	.L794
	.p2align 3
.L789:
	cmp	w6, 2
	beq	.L798
	cmp	w0, w8
	beq	.L792
.L793:
	sub	w5, w5, #1
	mov	w19, w3
	cmn	w5, #1
	sub	w4, w4, w2
	beq	.L796
.L799:
	sub	w3, w3, #1
.L794:
	ldr	w0, [x20, w4, uxtw 2]
	cmp	w6, 1
	sub	w0, w0, w1
	ldr	w0, [x7, x0]
	bne	.L789
	cmp	w0, w11
	cset	w9, eq
.L790:
	cmp	w0, w8
	beq	.L792
	cbz	w9, .L793
	.p2align 2
.L792:
	cmp	w3, w10
	mov	w19, w3
	bls	.L796
	sub	w5, w5, #1
	sub	w3, w3, #1
	cmn	w5, #1
	mov	w19, w3
	sub	w4, w4, w2
	bne	.L799
.L796:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L798:
	ubfx	x9, x0, 16, 8
	sub	w9, w9, #128
	cmp	w9, 3
	cset	w9, ls
	b	.L790
.L795:
	mov	w10, 4096
	b	.L787
	.size	GetNextVop, .-GetNextVop
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CorrectRollPhyAddr
	.type	CorrectRollPhyAddr, %function
CorrectRollPhyAddr:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	bl	_mcount
	cmp	w20, w21
	mov	w0, w19
	bcs	.L801
	sub	w0, w20, w21
	add	w0, w0, w19
.L801:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	CorrectRollPhyAddr, .-CorrectRollPhyAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CorrectSegNextAddr
	.type	CorrectSegNextAddr, %function
CorrectSegNextAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w20, w19
	csel	w0, w20, w19, cs
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	CorrectSegNextAddr, .-CorrectSegNextAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SetLastUnfinishedSegInfo
	.type	SetLastUnfinishedSegInfo, %function
SetLastUnfinishedSegInfo:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x21, x0
	mov	x0, x30
	mov	w20, w1
	mov	x22, x2
	bl	_mcount
	add	x19, x21, 458752
	add	x0, x29, 88
	add	x1, x29, 120
	str	xzr, [x29, 168]
	add	x24, x19, 512
	ldr	x23, [x19, 208]
	mov	x3, x24
	stp	xzr, xzr, [x0]
	add	x0, x29, 104
	ldr	w4, [x19, 240]
	stp	xzr, xzr, [x1]
	add	x1, x29, 136
	add	x2, x19, 280
	stp	xzr, xzr, [x0]
	ldr	w0, [x19, 316]
	add	x25, x21, 98304
	stp	xzr, xzr, [x1]
	add	x1, x29, 152
	mul	w20, w0, w20
	add	w0, w20, 1
	stp	xzr, xzr, [x1]
	ldr	w1, [x23, w0, uxtw 2]
	add	x0, x21, 88
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	x0, .LC145
	mov	x2, 88
	mov	x1, x24
	ldr	x3, [x0, 104]
	add	x0, x29, x2
	blr	x3
	ldr	w5, [x23, w20, uxtw 2]
	add	x23, x25, 112
	add	x1, x23, 360448
	str	w5, [x19, 492]
	ldr	w0, [x22, 28]
	ldr	w4, [x1, 24]
	cmp	w0, w4
	csel	w0, w0, w4, cs
	str	w0, [x19, 484]
	cmp	w5, w0
	bls	.L805
	mov	w1, 1
	str	w1, [x19, 500]
	ldr	w2, [x22, 28]
	ldr	w1, [x22, 16]
	cmp	w4, w2
	bls	.L806
	add	w1, w1, w2
	sub	w1, w1, w4
.L806:
	sub	w20, w0, w4
	sub	w3, w1, w5
	str	w1, [x19, 504]
	add	w1, w3, w20
	str	w1, [x19, 496]
	ldr	w0, [x21, 52]
	cmp	w0, 1
	beq	.L818
.L808:
	str	wzr, [x19, 488]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L805:
	sub	w3, w0, w5
	str	wzr, [x19, 500]
	str	w3, [x19, 496]
	str	wzr, [x19, 504]
	ldr	w0, [x21, 52]
	cmp	w0, 1
	ccmp	w3, 3, 0, eq
	bls	.L808
	ldr	x6, [x25, 112]
	sub	w4, w5, w4
	ldr	w2, [x19, 240]
	mov	w7, 1
	add	x4, x6, x4
	add	x1, x29, 88
	mov	w6, 2
	mov	x0, x23
	strb	w7, [x29, 98]
	strb	w6, [x29, 97]
	str	x4, [x29, 88]
	stp	w5, w3, [x29, 104]
	bl	InsertStreamSeg
	b	.L808
	.p2align 3
.L818:
	cbz	x23, .L809
	add	x6, x25, 112
	mov	w7, 4096
	add	x6, x6, 360448
	ldp	w0, w2, [x6, 8]
	sub	w0, w2, w0
	and	w0, w0, 4095
	sub	w0, w7, w0
	cmp	w0, 3
	cset	w0, hi
.L809:
	cmp	w1, 3
	cset	w1, hi
	tst	w0, w1
	beq	.L808
	ldr	x0, [x25, 112]
	sub	w4, w5, w4
	ldr	w2, [x19, 240]
	add	x21, x25, 112
	add	x4, x0, x4
	add	x1, x29, 88
	add	x21, x21, 360448
	mov	x0, x23
	stp	w5, w3, [x29, 104]
	mov	w22, 2
	str	x4, [x29, 88]
	strb	wzr, [x29, 98]
	strb	w22, [x29, 97]
	bl	InsertStreamSeg
	ldr	w4, [x21, 24]
	mov	w3, 1
	ldr	x5, [x25, 112]
	add	x1, x29, 88
	ldr	w2, [x19, 240]
	mov	x0, x23
	strb	w3, [x29, 98]
	strb	w22, [x29, 97]
	str	x5, [x29, 88]
	stp	w4, w20, [x29, 104]
	bl	InsertStreamSeg
	b	.L808
	.size	SetLastUnfinishedSegInfo, .-SetLastUnfinishedSegInfo
	.align	3
.LC145:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessSegRoll
	.type	ProcessSegRoll, %function
ProcessSegRoll:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x20, x0
	mov	x0, x30
	add	x25, x20, 458752
	add	x20, x20, 98304
	mov	w24, w2
	mov	x19, x1
	sxtb	w22, w3
	sxtb	w23, w4
	add	x27, x20, 112
	bl	_mcount
	add	x4, x27, 360448
	ldr	x0, [x25, 208]
	ldr	w1, [x25, 492]
	ldr	w28, [x4, 24]
	sub	w24, w24, w1
	ldr	w21, [x0]
	sub	w21, w21, w28
	add	w3, w24, w21
	cbz	x27, .L820
	ldp	w2, w0, [x4, 8]
	str	w1, [x19, 16]
	cmp	w3, 3
	sub	w0, w0, w2
	ldr	w2, [x4, 24]
	and	w0, w0, 4095
	sub	w1, w1, w2
	ldr	x2, [x20, 112]
	str	w3, [x19, 20]
	add	x1, x2, x1
	str	x1, [x19]
	mov	w1, 4096
	sub	w0, w1, w0
	bls	.L826
	cmp	w0, 2
	bls	.L824
.L823:
	mov	x1, x27
	mov	x0, x19
	bl	CheckSegValid
	mov	w26, w0
	cbnz	w0, .L824
	str	w24, [x19, 20]
	cbz	w21, .L828
	strb	wzr, [x19, 10]
	mov	x1, x19
	strb	w22, [x19, 9]
	mov	x0, x27
	ldr	w2, [x25, 240]
	bl	InsertStreamSeg
	str	w28, [x19, 16]
	add	x2, x20, 112
	mov	x0, x27
	add	x2, x2, 360448
	ldr	x3, [x20, 112]
	ldr	w1, [x2, 24]
	mov	w2, 1
	strb	w23, [x19, 9]
	sub	w1, w28, w1
	strb	w2, [x19, 10]
	add	x1, x3, x1
	str	w21, [x19, 20]
	str	x1, [x19]
	mov	x1, x19
	ldr	w2, [x25, 240]
	bl	InsertStreamSeg
.L827:
	mov	w0, w26
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L828:
	strb	w22, [x19, 9]
	mov	w0, 1
	strb	w0, [x19, 10]
	mov	x1, x19
	mov	x0, x27
	ldr	w2, [x25, 240]
	bl	InsertStreamSeg
	mov	w0, w26
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L820:
	str	w1, [x19, 16]
	cmp	w3, 3
	ldr	w0, [x4, 24]
	sub	w1, w1, w0
	ldr	x0, [x20, 112]
	str	w3, [x19, 20]
	add	x1, x0, x1
	str	x1, [x19]
	bhi	.L823
.L826:
	ldr	x1, .LC147
	mov	w2, 2754
	mov	w0, 0
	mov	w26, 0
	bl	dprint_vfmw
	mov	w0, w26
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L824:
	mov	w26, -4
	b	.L827
	.size	ProcessSegRoll, .-ProcessSegRoll
	.align	3
.LC147:
	.xword	.LC146
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ProcessLastUnfinishedSeg
	.type	ProcessLastUnfinishedSeg, %function
ProcessLastUnfinishedSeg:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x2
	mov	w23, w1
	bl	_mcount
	add	x21, x19, 98304
	add	x1, x29, 72
	add	x0, x21, 112
	add	x0, x0, 360448
	ldr	w3, [x20, 28]
	str	xzr, [x29, 152]
	stp	xzr, xzr, [x1]
	add	x1, x29, 88
	ldr	w2, [x0, 24]
	ldr	w22, [x20, 16]
	cmp	w2, w3
	stp	xzr, xzr, [x1]
	add	x1, x29, 104
	stp	xzr, xzr, [x1]
	add	x1, x29, 120
	stp	xzr, xzr, [x1]
	add	x1, x29, 136
	stp	xzr, xzr, [x1]
	bls	.L830
	add	w3, w22, w3
	sub	w22, w3, w2
.L830:
	cbnz	w23, .L831
	add	x0, x19, 458752
	ldr	w1, [x0, 292]
	ldr	w3, [x0, 288]
	cmp	w3, w1
	cset	w1, gt
	strb	w1, [x19]
	ldr	w4, [x0, 492]
	cbz	w4, .L842
	ldr	w3, [x0, 496]
	ldr	w1, [x0, 172]
	ldr	w5, [x0, 500]
	add	w3, w3, w1
	str	w3, [x0, 496]
	cbnz	w5, .L834
	ldr	w3, [x20, 28]
	cmp	w4, w3
	bls	.L834
	mov	w3, 1
	str	w22, [x0, 504]
	str	w3, [x0, 500]
.L834:
	str	wzr, [x0, 488]
	ldr	w3, [x20, 28]
	cmp	w3, w2
	csel	w2, w3, w2, cs
	str	w2, [x0, 484]
.L833:
	add	x0, x19, 88
	bl	DeleteRawLen
	mov	w20, w0
.L835:
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L831:
	add	x23, x19, 458752
	strb	wzr, [x19]
	mov	w20, 0
	ldr	w0, [x23, 492]
	cbz	w0, .L835
	ldr	x3, .LC148
	mov	x2, 88
	add	x1, x23, 512
	add	x0, x29, 72
	ldr	x3, [x3, 104]
	blr	x3
	ldr	w3, [x23, 500]
	cmp	w3, 1
	beq	.L843
	ldr	x2, [x23, 208]
	ldr	w1, [x23, 492]
	ldr	w0, [x2]
	cmp	w0, w1
	bcc	.L837
	add	x19, x21, 112
	ldr	x3, [x21, 112]
	add	x0, x19, 360448
	str	w1, [x29, 88]
	mov	w4, 1
	ldr	w0, [x0, 24]
	sub	w0, w1, w0
	add	x0, x3, x0
	str	x0, [x29, 72]
	ldr	w3, [x2]
	strb	w4, [x29, 82]
	sub	w3, w3, w1
	strb	w4, [x29, 81]
	cmp	w3, 3
	str	w3, [x29, 92]
	bls	.L844
	mov	x1, x19
	add	x0, x29, 72
	bl	CheckSegValid
	cbnz	w0, .L840
	ldr	w2, [x23, 240]
	add	x1, x29, 72
	mov	x0, x19
	bl	InsertStreamSeg
	mov	w20, w0
	b	.L835
	.p2align 3
.L842:
	ldr	w1, [x0, 172]
	b	.L833
	.p2align 3
.L837:
	mov	w4, 0
	mov	w3, 1
	mov	w2, w22
	add	x1, x29, 72
	mov	x0, x19
	bl	ProcessSegRoll
	mov	w20, w0
	b	.L835
	.p2align 3
.L844:
	ldr	x1, .LC149
	mov	w2, 2843
	mov	w0, 0
	bl	dprint_vfmw
	b	.L835
	.p2align 3
.L843:
	ldr	w2, [x23, 504]
	mov	w4, w3
	add	x1, x29, 72
	mov	x0, x19
	bl	ProcessSegRoll
	mov	w20, w0
	b	.L835
.L840:
	mov	w20, -4
	b	.L835
	.size	ProcessLastUnfinishedSeg, .-ProcessLastUnfinishedSeg
	.align	3
.LC148:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC149:
	.xword	.LC146
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
	beq	.L847
	mov	w0, 0
.L847:
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
	ldr	x1, .LC151
	mov	w3, w20
	mov	w2, 2882
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
.LC151:
	.xword	.LC150
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
	mov	x20, x0
	mov	x0, x30
	str	x20, [x29, 96]
	mov	x28, x2
	str	w1, [x29, 124]
	bl	_mcount
	add	x0, x29, 136
	add	x19, x20, 458752
	mov	x3, x20
	add	x20, x20, 98304
	add	x20, x20, 112
	mov	w25, 1
	stp	xzr, xzr, [x0]
	add	x0, x29, 152
	ldr	w24, [x19, 316]
	mov	w27, 0
	mov	x23, x20
	add	x21, x20, 360448
	ldr	x26, [x19, 208]
	stp	xzr, xzr, [x0]
	add	x0, x29, 168
	str	xzr, [x29, 216]
	stp	xzr, xzr, [x0]
	add	x0, x29, 184
	stp	xzr, xzr, [x0]
	add	x0, x29, 200
	stp	xzr, xzr, [x0]
	add	x0, x3, 88
	str	x0, [x29, 112]
	sub	w0, w24, #1
	str	w0, [x29, 120]
	b	.L851
	.p2align 3
.L875:
	ldr	w1, [x21, 24]
	sub	w3, w3, w0
	ldr	x4, [x23]
	mov	w2, 1
	sub	w1, w0, w1
	strb	w2, [x29, 146]
	stp	w0, w3, [x29, 152]
	cmp	w3, 3
	add	x0, x4, x1
	str	x0, [x29, 136]
	bls	.L874
	mov	x1, x20
	add	x0, x29, 136
	bl	CheckSegValid
	cbnz	w0, .L858
	strb	wzr, [x29, 145]
	add	x2, x19, 280
	ldr	x0, [x29, 112]
	add	x3, x29, 136
	ldr	w1, [x26, w25, uxtw 2]
	ldr	w4, [x19, 240]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 136
	mov	x0, x20
	bl	InsertStreamSeg
	cbnz	w0, .L858
.L854:
	add	w25, w25, w24
	mov	w27, w22
.L851:
	ldr	w0, [x29, 124]
	cmp	w27, w0
	beq	.L858
	ldr	w1, [x29, 120]
	sub	w0, w25, #1
	add	w22, w27, 1
	add	w1, w1, w25
	ldr	w0, [x26, w0, uxtw 2]
	ldr	w3, [x26, w1, uxtw 2]
	cmp	w0, w3
	bls	.L875
	ldr	w1, [x21, 24]
	ldr	w2, [x28, 16]
	sub	w5, w3, w1
	sub	w2, w2, w0
	add	w3, w2, w5
	cbz	x20, .L859
	ldr	x4, [x23]
	sub	w1, w0, w1
	stp	w0, w3, [x29, 152]
	add	x1, x4, x1
	cmp	w3, 3
	str	x1, [x29, 136]
	ldp	w1, w0, [x21, 8]
	bls	.L867
	sub	w0, w0, w1
	mov	w1, 4096
	and	w0, w0, 4095
	sub	w0, w1, w0
	cmp	w0, 2
	bls	.L858
.L868:
	mov	x1, x20
	add	x0, x29, 136
	stp	w5, w2, [x29, 104]
	bl	CheckSegValid
	cbnz	w0, .L858
	ldp	w5, w2, [x29, 104]
	cbnz	w5, .L861
	str	w2, [x29, 156]
	mov	w0, 1
	strb	wzr, [x29, 145]
	add	x2, x19, 280
	strb	w0, [x29, 146]
	add	x3, x29, 136
	ldr	x0, [x29, 112]
	ldr	w1, [x26, w25, uxtw 2]
	ldr	w4, [x19, 240]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 136
	mov	x0, x20
	bl	InsertStreamSeg
	b	.L854
	.p2align 3
.L861:
	str	w2, [x29, 156]
	add	x3, x29, 136
	strb	wzr, [x29, 146]
	add	x2, x19, 280
	strb	wzr, [x29, 145]
	ldr	w4, [x19, 240]
	ldr	w1, [x26, w25, uxtw 2]
	ldr	x0, [x29, 112]
	and	w1, w1, 1073741823
	str	w5, [x29, 108]
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 136
	mov	x0, x20
	bl	InsertStreamSeg
	strb	wzr, [x29, 145]
	ldr	w7, [x21, 24]
	mov	w3, 1
	ldr	w5, [x29, 108]
	add	x1, x29, 136
	ldr	x4, [x23]
	mov	x0, x20
	ldr	w2, [x19, 240]
	strb	w3, [x29, 146]
	str	x4, [x29, 136]
	stp	w7, w5, [x29, 152]
	bl	InsertStreamSeg
	b	.L854
	.p2align 3
.L859:
	sub	w1, w0, w1
	cmp	w3, 3
	stp	w0, w3, [x29, 152]
	ldr	x0, [x23]
	add	x1, x0, x1
	str	x1, [x29, 136]
	bhi	.L868
	.p2align 2
.L867:
	ldr	x1, .LC152
	mov	w2, 2956
	mov	w0, 0
	bl	dprint_vfmw
	b	.L854
	.p2align 3
.L874:
	ldr	x1, .LC152
	mov	w2, 2924
	mov	w0, 0
	bl	dprint_vfmw
	b	.L854
	.p2align 3
.L858:
	cmp	w27, wzr
	ble	.L876
	ldr	w0, [x28, 12]
	sub	w0, w0, #1
	cmp	w27, w0
	bcs	.L863
	mul	w0, w24, w27
	add	w0, w0, 1
	ldr	w20, [x26, w0, uxtw 2]
	ldr	x0, [x29, 96]
	and	w20, w20, 1073741823
	cbz	x0, .L864
	ldr	x2, .LC153
	add	x4, x19, 256
	mov	w0, -1
	strh	w0, [x19, 468]
	strh	w0, [x19, 476]
	mov	w1, 1
	str	w0, [x19, 472]
	ldr	x3, [x2, 96]
	mov	x2, 88
	stp	w0, wzr, [x4, 224]
	stp	w1, wzr, [x4, 232]
	str	wzr, [x19, 496]
	mov	w1, 0
	str	wzr, [x19, 500]
	add	x0, x19, 512
	str	wzr, [x19, 504]
	blr	x3
.L864:
	ldr	x0, [x29, 112]
	mov	w1, w20
	bl	DeleteRawLen
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
	.p2align 3
.L876:
	blt	.L866
	ldr	w0, [x28, 12]
	sub	w0, w0, #1
.L863:
	cmp	w27, w0
	beq	.L877
.L866:
	ldr	x0, [x29, 96]
	mov	x2, x28
	mov	w1, 0
	bl	SetLastUnfinishedSegInfo
.L850:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L877:
	ldr	x0, [x29, 96]
	mov	w1, w27
	mov	x2, x28
	ldr	w19, [x19, 172]
	bl	SetLastUnfinishedSegInfo
	ldr	x0, [x29, 112]
	mov	w1, w19
	bl	DeleteRawLen
	b	.L850
	.size	ProcessNotMpeg4ScdUpMsg, .-ProcessNotMpeg4ScdUpMsg
	.align	3
.LC152:
	.xword	.LC146
	.align	3
.LC153:
	.xword	vfmw_Osal_Func_Ptr_S
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
	add	x19, x0, 458752
	mov	w20, w1
	mov	x0, x30
	mov	w27, 0
	mov	w28, 0
	bl	_mcount
	ldr	w22, [x19, 316]
	ldr	x21, [x19, 208]
	cbz	w20, .L878
	ldr	x26, .LC157
	mov	w23, 288
	mov	w25, 2
	mov	w24, 1
	b	.L892
	.p2align 3
.L898:
	cmp	w1, 32768
	str	w24, [x19, 260]
	str	wzr, [x19, 264]
	beq	.L896
.L884:
	add	w28, w28, 1
	add	w27, w27, w22
	cmp	w28, w20
	beq	.L878
.L892:
	ldr	w0, [x21, w27, uxtw 2]
	bl	MEM_Phy2Vir
	cbz	x0, .L897
	ldr	w1, [x0]
	rev	w1, w1
	cmp	w1, 438
	ccmp	w1, w23, 4, ne
	and	w1, w1, -1024
	beq	.L898
	cmp	w1, 32768
	bne	.L884
	ldr	w0, [x19, 260]
	cmp	w0, 1
	beq	.L899
.L886:
	str	w25, [x19, 260]
.L900:
	add	w28, w28, 1
	add	w27, w27, w22
	cmp	w28, w20
	bne	.L892
.L878:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L896:
	str	w24, [x19, 264]
	b	.L884
	.p2align 3
.L897:
	ldr	x2, .LC154
	mov	w3, 3025
	ldr	x1, .LC156
	mov	w0, 1
	add	x2, x2, 112
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L899:
	ldr	w0, [x19, 264]
	add	w0, w0, 1
	str	w0, [x19, 264]
	cmp	w0, 30
	bls	.L884
	ldr	x4, [x26]
	cbz	x4, .L886
	ldr	w0, [x19, 240]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	blr	x4
	str	w25, [x19, 260]
	b	.L900
	.size	GetMpeg4ModeFlag, .-GetMpeg4ModeFlag
	.align	3
.LC154:
	.xword	.LANCHOR3
	.align	3
.LC156:
	.xword	.LC155
	.align	3
.LC157:
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
	mov	x22, x0
	mov	x0, x30
	add	x19, x22, 458752
	mov	x25, x2
	stp	x22, x2, [x29, 104]
	mov	w23, w1
	str	w1, [x29, 100]
	bl	_mcount
	ldr	x28, [x19, 208]
	ldr	w1, [x19, 316]
	add	x20, x22, 98304
	ldr	w0, [x19, 136]
	add	x20, x20, 112
	mov	w24, w1
	add	x1, x29, 232
	str	w24, [x29, 136]
	mov	w27, 0
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x1]
	add	x1, x29, 248
	str	xzr, [x29, 224]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x1]
	add	x1, x29, 264
	str	xzr, [x29, 312]
	stp	xzr, xzr, [x29, 192]
	stp	xzr, xzr, [x29, 208]
	stp	xzr, xzr, [x1]
	add	x1, x29, 280
	mov	x26, x20
	stp	xzr, xzr, [x1]
	add	x1, x29, 296
	stp	xzr, xzr, [x1]
	bl	MEM_Phy2Vir
	mov	x21, x0
	mov	x0, x25
	add	x1, x22, 88
	str	x1, [x29, 128]
	mov	w25, 1
	ldr	w0, [x0, 16]
	bl	MEM_Phy2Vir
	sub	w3, w24, #1
	str	w3, [x29, 140]
	ldr	x3, .LC158
	mov	x2, 4
	mov	x1, x21
	ldr	x3, [x3, 104]
	blr	x3
	mov	x0, x22
	mov	w1, w23
	bl	GetMpeg4ModeFlag
	mov	x0, x22
	mov	w2, w23
	mov	x1, x28
	add	x22, x20, 360448
	bl	GetNextVop
	mov	w24, w0
	b	.L902
	.p2align 3
.L944:
	ldr	w0, [x29, 248]
	cbz	w0, .L904
	ldr	w2, [x29, 252]
	mov	x1, x20
	add	x0, x29, 232
	add	w3, w2, w3
	str	w3, [x29, 252]
	bl	CheckSegValid
	cbnz	w0, .L908
	ldr	w2, [x19, 240]
	add	x1, x29, 232
	mov	x0, x20
	strb	wzr, [x29, 241]
	bl	InsertStreamSeg
	mov	w23, w0
	ldr	x0, .LC158
	mov	x2, 88
	mov	w1, 0
	ldr	x4, [x0, 96]
	add	x0, x29, 232
	blr	x4
	cbnz	w23, .L908
.L909:
	ldr	w0, [x29, 136]
	mov	w27, w21
	add	w25, w25, w0
.L902:
	cmp	w27, w24
	beq	.L908
	ldr	w1, [x29, 140]
	sub	w0, w25, #1
	add	w21, w27, 1
	add	w1, w1, w25
	add	x23, x28, x0, uxtw 2
	ldr	w2, [x28, w0, uxtw 2]
	ldr	w0, [x28, w1, uxtw 2]
	sub	w3, w0, w2
	cmp	w3, 3
	bgt	.L944
	sub	w1, w3, #1
	cmp	w1, 2
	bls	.L945
	ldr	x1, [x29, 112]
	ldr	w10, [x1, 16]
	ldr	w1, [x22, 24]
	sub	w10, w10, w2
	sub	w9, w0, w1
	add	w3, w10, w9
	cbz	x20, .L918
	ldr	x0, [x26]
	sub	w1, w2, w1
	cmp	w3, 3
	add	x1, x0, x1
	str	x1, [x29, 144]
	stp	w2, w3, [x29, 160]
	ldr	w0, [x22, 12]
	ldr	w1, [x22, 8]
	bls	.L930
	sub	w0, w0, w1
	mov	w1, 4096
	and	w0, w0, 4095
	sub	w0, w1, w0
	cmp	w0, 2
	bls	.L908
.L931:
	mov	x1, x20
	add	x0, x29, 144
	stp	w9, w10, [x29, 120]
	bl	CheckSegValid
	cbnz	w0, .L908
	ldp	w9, w10, [x29, 120]
	ldr	w0, [x19, 260]
	cmp	w0, 1
	ldrb	w0, [x29, 224]
	cbnz	w9, .L920
	beq	.L946
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L922:
	ldr	w1, [x23, 4]
	mov	w2, 1
	ldrb	w0, [x29, 224]
	add	x3, x29, 144
	lsr	w1, w1, 30
	ldr	w4, [x19, 240]
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 224]
	ldrh	w1, [x23, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x29, 224]
	ldr	w1, [x23, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 224]
	ldr	w0, [x23, 8]
	ldrh	w1, [x29, 224]
	and	w0, w0, 7
	strb	w2, [x29, 154]
	strb	wzr, [x29, 153]
	bfi	w1, w0, 7, 4
	str	w10, [x29, 164]
	add	x2, x19, 280
	strh	w1, [x29, 224]
	ldr	x0, [x29, 128]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 144
	mov	x0, x20
	bl	InsertStreamSeg
	b	.L909
	.p2align 3
.L904:
	ldr	w4, [x22, 24]
	mov	w9, 1
	ldr	x10, [x26]
	mov	x1, x20
	sub	w4, w2, w4
	add	x0, x29, 144
	add	x4, x10, x4
	strb	w9, [x29, 154]
	str	x4, [x29, 144]
	stp	w2, w3, [x29, 160]
	bl	CheckSegValid
	cbnz	w0, .L908
	ldr	w0, [x19, 260]
	cmp	w0, 1
	ldrb	w0, [x29, 224]
	beq	.L947
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L911:
	ldr	w3, [x23, 4]
	add	x2, x19, 280
	ldrb	w1, [x29, 224]
	lsr	w3, w3, 30
	ldr	w4, [x19, 240]
	bfi	w1, w3, 1, 1
	strb	w1, [x29, 224]
	ldr	x0, [x29, 128]
	ldrh	w3, [x23, 10]
	bfi	w1, w3, 2, 1
	strb	w1, [x29, 224]
	add	x3, x29, 144
	ldr	w9, [x23, 8]
	ubfx	x9, x9, 4, 3
	bfi	w1, w9, 3, 4
	strb	w1, [x29, 224]
	ldr	w1, [x23, 8]
	ldrh	w7, [x29, 224]
	and	w1, w1, 7
	bfi	w7, w1, 7, 4
	strh	w7, [x29, 224]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	strb	wzr, [x29, 153]
	ldr	w2, [x19, 240]
	add	x1, x29, 144
	mov	x0, x20
	bl	InsertStreamSeg
	cbz	w0, .L909
	.p2align 2
.L908:
	cmp	w27, wzr
	ble	.L907
	ldr	x0, [x29, 112]
	ldr	w0, [x0, 12]
	sub	w0, w0, #1
	cmp	w27, w0
	bcs	.L926
	ldr	w0, [x29, 136]
	mul	w0, w0, w27
	add	w0, w0, 1
	ldr	w20, [x28, w0, uxtw 2]
	ldr	x0, [x29, 104]
	and	w20, w20, 1073741823
	cbz	x0, .L927
	ldr	x0, .LC158
	add	x5, x19, 256
	mov	w1, 1
	mov	x2, 88
	ldr	x3, [x0, 96]
	mov	w0, -1
	strh	w0, [x19, 468]
	strh	w0, [x19, 476]
	str	w0, [x19, 472]
	stp	w0, wzr, [x5, 224]
	stp	w1, wzr, [x5, 232]
	str	wzr, [x19, 496]
	mov	w1, 0
	str	wzr, [x19, 500]
	add	x0, x19, 512
	str	wzr, [x19, 504]
	blr	x3
.L927:
	ldr	x0, [x29, 128]
	mov	w1, w20
	bl	DeleteRawLen
.L901:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L945:
	stp	w3, w2, [x29, 120]
	bl	MEM_Phy2Vir
	ldp	w3, w2, [x29, 120]
	cbz	x0, .L948
	ldr	w0, [x0]
	and	w0, w0, 16777215
	cmp	w0, 65536
	beq	.L909
	ldr	w0, [x19, 260]
	cmp	w0, 1
	ldrb	w0, [x29, 312]
	beq	.L949
	orr	w0, w0, 1
	strb	w0, [x29, 312]
.L917:
	ldr	w1, [x23, 4]
	ldrb	w0, [x29, 312]
	lsr	w1, w1, 30
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 312]
	ldr	w1, [x22, 24]
	ldrh	w4, [x23, 10]
	sub	w1, w2, w1
	bfi	w0, w4, 2, 1
	ldr	x4, [x26]
	strb	w0, [x29, 312]
	add	x1, x4, x1
	str	x1, [x29, 232]
	ldr	w1, [x23, 8]
	ldr	w4, [x19, 240]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 312]
	mov	w1, 1
	ldr	w0, [x23, 8]
	strb	w1, [x29, 242]
	ldrh	w1, [x29, 312]
	and	w0, w0, 7
	stp	w2, w3, [x29, 248]
	bfi	w1, w0, 7, 4
	strh	w1, [x29, 312]
	ldr	x0, [x29, 128]
	add	x3, x29, 232
	ldr	w1, [x28, w25, uxtw 2]
	add	x2, x19, 280
	and	w1, w1, 1073741823
	bl	GetSegPts
	b	.L909
	.p2align 3
.L920:
	beq	.L950
	orr	w0, w0, 1
	strb	w0, [x29, 224]
.L924:
	ldr	w1, [x23, 4]
	add	x3, x29, 144
	ldrb	w0, [x29, 224]
	add	x2, x19, 280
	lsr	w1, w1, 30
	ldr	w4, [x19, 240]
	bfi	w0, w1, 1, 1
	strb	w0, [x29, 224]
	str	w9, [x29, 124]
	ldrh	w1, [x23, 10]
	bfi	w0, w1, 2, 1
	strb	w0, [x29, 224]
	ldr	w1, [x23, 8]
	ubfx	x1, x1, 4, 3
	bfi	w0, w1, 3, 4
	strb	w0, [x29, 224]
	ldr	w0, [x23, 8]
	ldrh	w1, [x29, 224]
	and	w0, w0, 7
	str	w10, [x29, 164]
	strb	wzr, [x29, 154]
	bfi	w1, w0, 7, 4
	strb	wzr, [x29, 153]
	strh	w1, [x29, 224]
	ldr	x0, [x29, 128]
	ldr	w1, [x28, w25, uxtw 2]
	and	w1, w1, 1073741823
	bl	GetSegPts
	ldr	w2, [x19, 240]
	add	x1, x29, 144
	mov	x0, x20
	bl	InsertStreamSeg
	strb	wzr, [x29, 153]
	ldr	w3, [x22, 24]
	add	x1, x29, 144
	ldr	w9, [x29, 124]
	mov	x0, x20
	ldr	x4, [x26]
	ldr	w2, [x19, 240]
	stp	w3, w9, [x29, 160]
	mov	w3, 1
	str	x4, [x29, 144]
	strb	w3, [x29, 154]
	bl	InsertStreamSeg
	b	.L909
	.p2align 3
.L918:
	ldr	x0, [x26]
	sub	w1, w2, w1
	cmp	w3, 3
	add	x1, x0, x1
	str	x1, [x29, 144]
	stp	w2, w3, [x29, 160]
	bhi	.L931
	.p2align 2
.L930:
	ldr	x1, .LC161
	mov	w2, 3165
	mov	w0, 0
	bl	dprint_vfmw
	b	.L909
	.p2align 3
.L947:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L911
	.p2align 3
.L946:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L922
	.p2align 3
.L950:
	and	w0, w0, -2
	strb	w0, [x29, 224]
	b	.L924
	.p2align 3
.L926:
	beq	.L951
.L907:
	ldr	w0, [x29, 100]
	cmp	w0, 1024
	ccmp	w24, wzr, 0, hi
	beq	.L952
	ldr	x0, [x29, 104]
	cbz	x0, .L901
.L953:
	ldr	x0, .LC158
	add	x4, x19, 256
	mov	w1, 1
	mov	x2, 88
	ldr	x3, [x0, 96]
	mov	w0, -1
	strh	w0, [x19, 468]
	strh	w0, [x19, 476]
	str	w0, [x19, 472]
	stp	w0, wzr, [x4, 224]
	stp	w1, wzr, [x4, 232]
	str	wzr, [x19, 496]
	mov	w1, 0
	str	wzr, [x19, 500]
	add	x0, x19, 512
	str	wzr, [x19, 504]
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 320
	ret
	.p2align 3
.L949:
	and	w0, w0, -2
	strb	w0, [x29, 312]
	b	.L917
.L952:
	ldr	x1, .LC163
	mov	x2, x0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x29, 128]
	mov	w1, 1
	bl	DeleteRawPacket
	ldr	x0, [x29, 104]
	cbnz	x0, .L953
	b	.L901
.L951:
	ldp	x0, x2, [x29, 104]
	mov	w1, w27
	ldr	w19, [x19, 172]
	bl	SetLastUnfinishedSegInfo
	ldr	x0, [x29, 128]
	mov	w1, w19
	bl	DeleteRawLen
	b	.L901
.L948:
	ldr	x1, .LC160
	mov	w2, 3135
	bl	dprint_vfmw
	b	.L901
	.size	ProcessMpeg4ScdUpMsg, .-ProcessMpeg4ScdUpMsg
	.align	3
.LC158:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC160:
	.xword	.LC159
	.align	3
.LC161:
	.xword	.LC146
	.align	3
.LC163:
	.xword	.LC162
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	ProcessScdReturn.part.10, %function
ProcessScdReturn.part.10:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	mov	w1, w19
	add	x0, x29, 32
	bl	ReadScdStateReg
	mov	w0, 34464
	ldr	w1, [x29, 44]
	movk	w0, 0x1, lsl 16
	cmp	w1, w0
	bls	.L955
	ldr	w0, [x20, 20]
	cbz	w0, .L960
.L955:
	add	x2, x20, 458752
	ldr	w0, [x29, 56]
	ldr	w19, [x2, 316]
	udiv	w19, w0, w19
	cmp	w19, w1
	csel	w19, w19, w1, ls
	cmp	w1, w19
	bhi	.L961
.L957:
	mov	w1, w19
	add	x2, x29, 32
	mov	x0, x20
	bl	ProcessLastUnfinishedSeg
	cmp	w0, wzr
	ccmp	w19, wzr, 4, eq
	cset	w1, eq
	cbnz	w1, .L956
	ldr	w0, [x20, 20]
	add	x2, x29, 32
	sub	w1, w19, #1
	cmp	w0, 2
	mov	x0, x20
	beq	.L958
	bl	ProcessNotMpeg4ScdUpMsg
	mov	w0, 0
.L956:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L961:
	ldrsb	w0, [x20, 2]
	cmp	w0, 1
	bne	.L957
	strb	wzr, [x20, 2]
	b	.L957
	.p2align 3
.L958:
	bl	ProcessMpeg4ScdUpMsg
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
.L960:
	mov	x0, x20
	bl	ProcessExceptionalStartCodeNum
	mov	w0, -7
	b	.L956
	.size	ProcessScdReturn.part.10, .-ProcessScdReturn.part.10
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
	add	x2, x19, 458752
	add	x2, x2, 168
	ldr	w0, [x2, 8]
	cmp	w0, 3
	beq	.L965
	mov	w0, 2
	mov	w1, w20
	str	w0, [x2, 8]
	mov	x0, x19
	bl	ProcessScdReturn.part.10
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L965:
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
	ldr	x21, .LC164
	ldr	x0, [x21, w22, sxtw 3]
	cbz	x0, .L966
	ldr	x19, .LC165
	mov	w0, 0
	ldr	w24, [x23, 20]
	ldr	x1, [x19, 32]
	blr	x1
	ldrb	w0, [x20, 2]
	cbnz	w0, .L968
	add	x1, x23, 36
	mov	w0, w24
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cbnz	w0, .L976
.L969:
	ldr	x2, [x21, w22, sxtw 3]
	ldr	w1, [x20, 12]
	ldr	x3, [x19, 88]
	ldr	x0, [x20, 40]
	blr	x3
.L968:
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
.L966:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L976:
	ldr	x2, [x21, w22, sxtw 3]
	mov	w1, 4
	ldr	x3, [x19, 88]
	add	x0, x20, 12
	blr	x3
	b	.L969
	.size	SCDDRV_SaveRawStream, .-SCDDRV_SaveRawStream
	.align	3
.LC164:
	.xword	vfmw_save_str_file
	.align	3
.LC165:
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
	cbnz	w0, .L978
	ldr	w1, [x19, 64]
	mov	w0, 1
	cbz	w1, .L979
.L978:
	add	x19, x19, 458752
	mov	w0, 0
	ldr	w1, [x19, 160]
	cmp	w1, 8
	bgt	.L979
	ldr	x0, .LC166
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 1732]
	cmp	w0, 1
	ccmp	w1, wzr, 4, eq
	cset	w0, le
.L979:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	NeedReadStream, .-NeedReadStream
	.align	3
.LC166:
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
	ldr	x21, .LC168
	ldr	x0, .LC167
	mov	x2, 100
	add	x1, x21, 136
	add	x20, x0, x20, sxtw 4
	add	x0, x29, 56
	ldr	x20, [x20, 88]
	bl	memcpy
	cbz	x19, .L997
	ldr	w3, [x20, 20]
	cmp	w3, 18
	bls	.L998
.L986:
	ldr	x1, .LC173
	add	x2, x21, 240
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
.L995:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 160
	ret
	.p2align 3
.L998:
	ldr	x0, .LC171
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx988
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx988:
	.section	.rodata
	.align	0
	.align	2
.L988:
	.byte	(.L993 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L986 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.byte	(.L990 - .Lrtx988) / 4
	.byte	(.L986 - .Lrtx988) / 4
	.byte	(.L989 - .Lrtx988) / 4
	.text
	.p2align 3
.L993:
	ldr	w3, [x19, 12]
	mov	w20, 15
	ldr	w5, [x19, 80]
	add	x1, x29, 56
	add	w0, w3, w20
	cmp	w0, w5
	bhi	.L991
.L996:
	ldr	x4, .LC176
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
.L990:
	ldr	w3, [x19, 12]
	mov	w20, 16
	ldr	w5, [x19, 80]
	add	x1, x29, 136
	add	w0, w3, w20
	cmp	w0, w5
	bls	.L996
.L991:
	ldr	x1, .LC175
	mov	w4, w20
	add	x2, x21, 240
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L995
	.p2align 3
.L989:
	ldr	w3, [x19, 12]
	mov	w0, 0
	ldr	w5, [x19, 80]
	cmp	w3, w5
	bls	.L995
	mov	w20, 0
	b	.L991
	.p2align 3
.L997:
	ldr	x1, .LC170
	add	x2, x21, 240
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L995
	.size	FillEopRawStream, .-FillEopRawStream
	.align	3
.LC167:
	.xword	.LANCHOR0
	.align	3
.LC168:
	.xword	.LANCHOR3
	.align	3
.LC170:
	.xword	.LC169
	.align	3
.LC171:
	.xword	.L988
	.align	3
.LC173:
	.xword	.LC172
	.align	3
.LC175:
	.xword	.LC174
	.align	3
.LC176:
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
	ldr	x0, .LC177
	mov	x2, 100
	ldr	x1, .LC178
	add	x19, x0, x19, sxtw 4
	add	x0, x29, 40
	add	x1, x1, 264
	ldr	x19, [x19, 88]
	bl	memcpy
	cbz	x20, .L1019
	ldr	w3, [x19, 20]
	cmp	w3, 18
	bls	.L1020
.L1002:
	ldr	x2, .LC179
	mov	w0, 0
	ldr	x1, .LC182
	bl	dprint_vfmw
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1020:
	ldr	x0, .LC181
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx1004
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1004:
	.section	.rodata
	.align	0
	.align	2
.L1004:
	.byte	(.L1003 - .Lrtx1004) / 4
	.byte	(.L1005 - .Lrtx1004) / 4
	.byte	(.L1006 - .Lrtx1004) / 4
	.byte	(.L1007 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1014 - .Lrtx1004) / 4
	.byte	(.L1002 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1003 - .Lrtx1004) / 4
	.byte	(.L1009 - .Lrtx1004) / 4
	.byte	(.L1017 - .Lrtx1004) / 4
	.byte	(.L1014 - .Lrtx1004) / 4
	.text
	.p2align 3
.L1003:
	mov	w19, 15
	add	x1, x29, 40
.L1008:
	ldr	w4, [x20, 12]
	cmp	w19, w4
	bls	.L1021
	ldr	x2, .LC179
	mov	w3, w19
	ldr	x1, .LC184
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1015
	.p2align 3
.L1021:
	ldr	x3, .LC185
	and	x2, x19, 31
	ldr	x0, [x20, 40]
	ldr	x3, [x3, 104]
	blr	x3
	str	w19, [x20, 12]
.L1017:
	mov	w0, 0
.L1015:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L1005:
	ldr	w0, [x19, 36]
	cmp	w0, 1
	bne	.L1017
.L1014:
	mov	w19, 15
	add	x1, x29, 60
	b	.L1008
	.p2align 3
.L1009:
	mov	w19, 16
	add	x1, x29, 120
	b	.L1008
	.p2align 3
.L1007:
	mov	w19, 16
	add	x1, x29, 100
	b	.L1008
	.p2align 3
.L1006:
	mov	w19, 19
	add	x1, x29, 80
	b	.L1008
.L1019:
	ldr	x2, .LC179
	mov	w0, 0
	ldr	x1, .LC180
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1015
	.size	FillEosRawStream, .-FillEosRawStream
	.align	3
.LC177:
	.xword	.LANCHOR0
	.align	3
.LC178:
	.xword	.LANCHOR3
	.align	3
.LC179:
	.xword	.LANCHOR4
	.align	3
.LC180:
	.xword	.LC169
	.align	3
.LC181:
	.xword	.L1004
	.align	3
.LC182:
	.xword	.LC172
	.align	3
.LC184:
	.xword	.LC183
	.align	3
.LC185:
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
	beq	.L1034
	ldr	w0, [x19, 76]
	tbnz	x0, 7, .L1035
	add	x20, x20, 458752
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	ldr	w0, [x20, 332]
	add	w3, w2, w0
	cmp	w3, w4
	bhi	.L1036
	ldr	x1, [x19, 40]
	sxtw	x2, w2
	ldr	x22, .LC189
	mov	w21, 0
	add	x0, x1, x0, uxtw
.L1033:
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
.L1026:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1035:
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	add	w3, w2, 12
	cmp	w3, 128
	ccmp	w3, w4, 2, le
	bhi	.L1037
	ldr	x22, .LC189
	sxtw	x2, w2
	ldr	x1, [x19, 40]
	add	x20, x20, 458752
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
.L1034:
	ldr	w1, [x19, 76]
	tbnz	x1, 7, .L1038
	ldrb	w1, [x19, 72]
	mov	w21, 0
	cbz	w1, .L1026
	add	x20, x20, 458752
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	ldr	w5, [x20, 332]
	add	w3, w2, w5
	cmp	w3, w4
	bhi	.L1039
	ldr	x1, [x19, 40]
	sxtw	x2, w2
	ldr	x22, .LC189
	add	x0, x1, x5, uxtw
	b	.L1033
	.p2align 3
.L1038:
	ldr	w3, [x19, 12]
	cmp	w3, 127
	bhi	.L1040
	add	x20, x20, 458752
	ldr	x1, .LC189
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
.L1037:
	ldr	x2, .LC186
	mov	w5, 128
	ldr	x1, .LC193
	mov	w0, 1
	add	x2, x2, 24
	mov	w21, -2
	bl	dprint_vfmw
	b	.L1026
	.p2align 3
.L1036:
	ldr	x2, .LC186
	mov	w0, 1
	ldr	x1, .LC191
	mov	w21, -2
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L1026
.L1040:
	ldr	x2, .LC186
	mov	w4, 128
	ldr	x1, .LC188
	mov	w21, -2
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L1026
.L1039:
	ldr	x2, .LC186
	mov	w21, -2
	ldr	x1, .LC191
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L1026
	.size	FillVC1ExtraData, .-FillVC1ExtraData
	.align	3
.LC186:
	.xword	.LANCHOR4
	.align	3
.LC188:
	.xword	.LC187
	.align	3
.LC189:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC191:
	.xword	.LC190
	.align	3
.LC193:
	.xword	.LC192
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
	bhi	.L1044
	ldr	x20, .LC197
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
.L1043:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1044:
	ldr	x2, .LC194
	mov	w0, 1
	ldr	x1, .LC196
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -2
	b	.L1043
	.size	FillDIVX3ExtraData, .-FillDIVX3ExtraData
	.align	3
.LC194:
	.xword	.LANCHOR4
	.align	3
.LC196:
	.xword	.LC195
	.align	3
.LC197:
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
	tbz	x0, 7, .L1046
	ldr	w3, [x19, 12]
	cmp	w3, 127
	bhi	.L1050
	add	x20, x20, 458752
	ldr	x1, .LC200
	add	x0, x20, 336
	str	w3, [x20, 332]
	ldr	x3, [x1, 104]
	ldr	w2, [x19, 12]
	ldr	x1, [x19, 40]
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1046:
	add	x20, x20, 458752
	ldr	w2, [x19, 12]
	ldr	w4, [x19, 80]
	ldr	w0, [x20, 332]
	add	w3, w2, w0
	cmp	w3, w4
	bhi	.L1051
	ldr	x21, .LC200
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
.L1048:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1051:
	ldr	x2, .LC198
	mov	w0, 1
	ldr	x1, .LC202
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -2
	b	.L1048
	.p2align 3
.L1050:
	ldr	x2, .LC198
	mov	w4, 128
	ldr	x1, .LC199
	mov	w0, 1
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -2
	b	.L1048
	.size	FillREAL8ExtraData, .-FillREAL8ExtraData
	.align	3
.LC198:
	.xword	.LANCHOR4
	.align	3
.LC199:
	.xword	.LC187
	.align	3
.LC200:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC202:
	.xword	.LC201
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
	bhi	.L1058
	ldr	w3, [x20, 12]
	cmp	w3, wzr
	ble	.L1061
	ldr	x0, .LC206
	add	x19, x0, x19, sxtw 4
	ldr	x0, [x19, 88]
	ldr	w1, [x0, 20]
	cmp	w1, 5
	beq	.L1055
	cmp	w1, 8
	beq	.L1056
	cmp	w1, 1
	beq	.L1062
	mov	w0, 0
.L1053:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1056:
	mov	x1, x20
	bl	FillREAL8ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1055:
	mov	x1, x20
	bl	FillDIVX3ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1062:
	mov	x1, x20
	bl	FillVC1ExtraData
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1058:
	mov	w0, -1
	b	.L1053
.L1061:
	ldr	x2, .LC203
	mov	w0, 1
	ldr	x1, .LC205
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1053
	.size	FillExtraData, .-FillExtraData
	.align	3
.LC203:
	.xword	.LANCHOR4
	.align	3
.LC205:
	.xword	.LC204
	.align	3
.LC206:
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
	ldr	x19, .LC207
	mov	x20, x0
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 72
	ldr	x3, [x19, 96]
	blr	x3
	cbz	x20, .L1079
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
	ldr	x23, .LC210
	ldr	x0, [x20, 16]
	cbz	x0, .L1066
	lsl	x20, x21, 4
	add	x24, x23, 88
	ldr	x0, [x24, x20]
	ldr	w0, [x0, 60]
	cmp	w0, 1
	beq	.L1080
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	ldr	x2, [x19, 48]
	mov	w1, w22
	mov	w0, 1
	blr	x2
	ldr	x0, [x24, x20]
	cbz	x0, .L1071
	ldr	w0, [x29, 72]
	add	x1, x29, 96
	ldr	x2, [x29, 88]
	blr	x2
	mov	w20, w0
.L1069:
	ldr	x2, [x19, 56]
	mov	w0, 1
	mov	w1, w22
	blr	x2
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	cbz	w20, .L1070
.L1066:
	mov	w20, -7
.L1070:
	add	x21, x23, x21, lsl 4
	mov	w0, w20
	ldr	x1, [x21, 88]
	cbz	x1, .L1081
.L1065:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L1080:
	ldr	w0, [x29, 72]
	add	x1, x29, 96
	ldr	x2, [x29, 88]
	blr	x2
	mov	w20, w0
	cbz	w20, .L1070
	b	.L1066
	.p2align 3
.L1071:
	mov	w20, -7
	b	.L1069
.L1079:
	ldr	x1, .LC209
	mov	w2, w22
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1065
.L1081:
	ldr	x1, .LC212
	mov	w3, w22
	mov	w2, 4088
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1065
	.size	ReleaseRawStreamData, .-ReleaseRawStreamData
	.align	3
.LC207:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC209:
	.xword	.LC208
	.align	3
.LC210:
	.xword	.LANCHOR0
	.align	3
.LC212:
	.xword	.LC211
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
	mov	w23, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w23, 31
	bhi	.L1094
	ldr	x28, .LC214
	sxtw	x0, w23
	add	x1, x28, x0, lsl 4
	ldr	x27, [x1, 88]
	cbz	x27, .L1094
	cbz	w19, .L1098
.L1084:
	adds	x22, x27, 88
	beq	.L1094
	add	x1, x22, 98304
	ldr	w21, [x1]
	ldr	w20, [x1, 8]
	cmp	w21, w20
	blt	.L1099
.L1097:
	sub	w21, w21, w20
	cbz	w21, .L1094
	ldr	x25, .LC215
	add	x28, x28, 88
	ldr	x24, .LC216
	mov	w26, 0
	add	x25, x25, 112
	add	x28, x28, x0, lsl 4
	b	.L1088
	.p2align 3
.L1101:
	cmp	w26, w21
	beq	.L1100
.L1088:
	uxtw	x19, w20
	mov	x2, x25
	lsl	x0, x19, 2
	mov	x1, x24
	sub	x19, x0, x19
	mov	w0, 26
	lsl	x19, x19, 5
	add	w20, w20, 1
	add	x3, x27, x19
	add	w26, w26, 1
	and	w20, w20, 1023
	ldr	w4, [x3, 100]
	ldr	w3, [x3, 92]
	bl	dprint_vfmw
	add	x1, x22, x19
	mov	w0, w23
	bl	ReleaseRawStreamData
	ldr	x0, [x28]
	cmp	x27, x0
	ccmp	x0, xzr, 4, eq
	bne	.L1101
	mov	w0, -7
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1098:
	add	x1, x27, 458752
	ldr	w1, [x1, 256]
	cbnz	w1, .L1084
.L1094:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1099:
	add	w21, w21, 1024
	b	.L1097
	.p2align 3
.L1100:
	add	x22, x22, 98304
	ldr	w20, [x22, 8]
	add	w20, w20, w26
	cmp	w20, 1023
	ble	.L1102
	sub	w20, w20, #1024
	str	w20, [x22, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1102:
	str	w20, [x22, 8]
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
.LC214:
	.xword	.LANCHOR0
	.align	3
.LC215:
	.xword	.LANCHOR4
	.align	3
.LC216:
	.xword	.LC43
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
	bhi	.L1115
	ldr	x27, .LC219
	sxtw	x23, w21
	add	x0, x27, x23, lsl 4
	ldr	x20, [x0, 88]
	cbz	x20, .L1105
	ldr	w0, [x27, 52]
	cmp	w21, w0
	bne	.L1107
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	ldr	x2, .LC223
	mov	w3, 1149
	ldr	x1, .LC225
	mov	w0, 22
	add	x2, x2, 136
	bl	dprint_vfmw
.L1107:
	ldr	x22, .LC222
	mov	x2, 80
	add	x1, x20, 8
	add	x0, x29, 96
	add	x19, x20, 458752
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
	cbz	x0, .L1108
	add	x0, x0, 458752
	ldr	w1, [x0, 256]
	cbnz	w1, .L1125
.L1108:
	adds	x0, x20, 88
	beq	.L1109
	add	x2, x0, 98304
	ldr	w1, [x2, 4]
	ldr	w2, [x2]
	sub	w1, w1, w2
	add	w2, w1, 1024
	cmp	w1, wzr
	csel	w1, w2, w1, lt
	bl	DeleteRawPacket
	mov	w1, 1
	mov	w0, w21
	bl	DeleteRawPacketInBuffer
	ldrsb	w23, [x19, 240]
	mov	x2, 16984
	ldr	x3, [x22, 96]
	mov	x0, x20
	movk	x2, 0x7, lsl 16
	mov	w1, 0
	blr	x3
.L1114:
	mov	w0, -1
	strh	w0, [x19, 468]
	strh	w0, [x19, 476]
	mov	x2, 88
	str	w0, [x19, 472]
	mov	w1, 0
	str	w0, [x19, 480]
	add	x0, x19, 256
	str	wzr, [x19, 484]
	sub	w24, w24, #1
	ldr	x3, [x22, 96]
	stp	wzr, wzr, [x0, 236]
	stp	wzr, wzr, [x0, 244]
	mov	w0, 1
	str	w0, [x19, 488]
	add	x0, x19, 512
	blr	x3
	str	w23, [x19, 240]
	mov	w0, 2
	mov	x2, -1
	add	x1, x29, 96
	str	x2, [x19, 280]
	str	w0, [x19, 316]
	mov	w0, w21
	bl	SM_Config
	str	w26, [x19, 332]
	cmp	w24, 1
	ldr	x3, [x22, 104]
	cset	w0, ls
	mov	x2, 128
	str	w0, [x19, 256]
	add	x1, x29, 176
	mov	x0, x25
	blr	x3
	mov	w0, 0
.L1122:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L1125:
	ldr	w1, [x0, 244]
	cmp	w1, wzr
	bgt	.L1108
	str	wzr, [x0, 256]
	b	.L1108
	.p2align 3
.L1109:
	ldr	x2, .LC223
	mov	w3, 1165
	ldr	x1, .LC227
	mov	w0, 22
	add	x2, x2, 136
	bl	dprint_vfmw
	mov	w1, 0
	mov	x0, 0
	bl	DeleteRawPacket
	mov	w1, 1
	mov	w0, w21
	bl	DeleteRawPacketInBuffer
	ldrsb	w23, [x19, 240]
	mov	x2, 16984
	ldr	x3, [x22, 96]
	mov	x0, x20
	movk	x2, 0x7, lsl 16
	mov	w1, 0
	blr	x3
	b	.L1114
	.p2align 3
.L1115:
	mov	w0, -1
	b	.L1122
.L1105:
	ldr	x1, .LC221
	mov	w2, 1139
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1122
	.size	SM_Reset, .-SM_Reset
	.align	3
.LC219:
	.xword	.LANCHOR0
	.align	3
.LC221:
	.xword	.LC220
	.align	3
.LC222:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC223:
	.xword	.LANCHOR4
	.align	3
.LC225:
	.xword	.LC224
	.align	3
.LC227:
	.xword	.LC226
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
	str	x25, [sp, 64]
	mov	w23, w0
	mov	x0, x30
	mov	x24, x1
	sbfiz	x25, x23, 4, 32
	bl	_mcount
	ldr	x20, .LC228
	ldr	x22, .LC229
	mov	x2, 24
	add	x20, x20, 88
	mov	w1, 0
	add	x0, x29, 88
	ldr	x3, [x22, 96]
	ldr	x19, [x20, x25]
	blr	x3
	cbz	x19, .L1127
	mov	w0, w23
	bl	VCTRL_GetStreamInterface
	mov	x21, x0
	cbz	x0, .L1159
	ldr	x3, [x22, 104]
	mov	x2, 24
	add	x0, x29, 88
	mov	x1, x21
	blr	x3
	ldr	x0, [x21, 8]
	cbz	x0, .L1127
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1160
	ldr	x1, [x22, 32]
	mov	w0, 0
	blr	x1
	ldr	x2, [x29, 96]
	mov	x1, x24
	ldr	w0, [x29, 88]
	blr	x2
	mov	w21, w0
	ldr	x1, [x22, 24]
	mov	w0, 0
	blr	x1
	ldr	x0, [x20, x25]
	cmp	x19, x0
	ccmp	x0, xzr, 4, eq
	beq	.L1161
	cbz	w21, .L1133
.L1127:
	mov	w0, -7
.L1156:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1133:
	ldrb	w20, [x24, 1]
	cmp	w20, 1
	beq	.L1162
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1163
.L1135:
	add	x19, x19, 98304
	ldr	w1, [x24, 12]
	mov	w0, 0
	ldr	w2, [x19, 108]
	add	w1, w2, w1
	str	w1, [x19, 108]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1161:
	ldr	x1, .LC233
	mov	w3, w23
	mov	w2, 3993
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1156
	.p2align 3
.L1162:
	mov	x1, x24
	mov	w0, w23
	bl	FillEosRawStream
	cbnz	w0, .L1164
	mov	w1, w20
	mov	w0, w23
	bl	VCTRL_SetLastFrameState
	b	.L1135
	.p2align 3
.L1160:
	ldr	w0, [x29, 88]
	mov	x1, x24
	ldr	x2, [x29, 96]
	blr	x2
	mov	w21, w0
	cbz	w21, .L1133
	b	.L1127
	.p2align 3
.L1163:
	mov	x1, x24
	mov	w0, w23
	bl	FillExtraData
	cbnz	w0, .L1165
	add	x0, x19, 458752
	ldr	w0, [x0, 328]
	cbz	w0, .L1135
	ldrb	w0, [x24]
	cbnz	w0, .L1135
	mov	x1, x24
	mov	w0, w23
	bl	FillEopRawStream
	b	.L1135
	.p2align 3
.L1165:
	ldr	x1, .LC237
	mov	w2, w23
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x29, 88]
	mov	x1, x24
	bl	ReleaseRawStreamData
	cbz	w0, .L1127
	ldr	x1, .LC239
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1156
.L1159:
	ldr	x1, .LC231
	mov	w2, w23
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1156
.L1164:
	ldr	x1, .LC235
	mov	w2, w23
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1156
	.size	ReadRawStreamData, .-ReadRawStreamData
	.align	3
.LC228:
	.xword	.LANCHOR0
	.align	3
.LC229:
	.xword	vfmw_Osal_Func_Ptr_S
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
	ldr	x24, .LC241
	ldr	x23, .LC242
	mov	x2, 96
	add	x4, x24, x22, lsl 4
	mov	w1, 0
	add	x0, x29, 112
	ldr	x3, [x23, 96]
	ldr	x21, [x4, 88]
	blr	x3
	cbz	x21, .L1166
	ldr	w0, [x21, 20]
	cmp	w0, 20
	beq	.L1166
	lsl	w0, w22, 24
	ldr	x28, .LC243
	str	w0, [x29, 108]
	add	x19, x21, 458752
	ldr	x0, .LC251
	mov	x27, x28
	ldr	x26, .LC245
	ldr	x25, .LC247
	add	x0, x0, 152
	str	x0, [x29, 96]
	.p2align 2
.L1182:
	ldr	w0, [x21, 60]
	cbnz	w0, .L1168
	ldr	w0, [x21, 64]
	cbz	w0, .L1169
.L1168:
	ldr	w1, [x19, 160]
	cmp	w1, 8
	bgt	.L1166
	ldr	x0, [x28, x22, lsl 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 1732]
	cmp	w0, 1
	ccmp	w1, wzr, 4, eq
	ble	.L1169
.L1166:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1169:
	cmp	w20, 31
	bhi	.L1173
	add	x0, x24, x22, lsl 4
	ldr	x0, [x0, 88]
	cbz	x0, .L1173
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
	beq	.L1173
	add	x1, x29, 112
	mov	w0, w20
	bl	ReadRawStreamData
	cbnz	w0, .L1166
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
	cbnz	w1, .L1175
	str	w0, [x19, 300]
.L1176:
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
	beq	.L1203
	add	x1, x29, 112
	mov	w0, w20
	bl	SCDDRV_InsertRawPacket
	cbnz	w0, .L1204
.L1178:
	mov	w1, 1
	strb	w1, [x21, 3]
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L1205
.L1180:
	mov	w0, w20
	add	x2, x29, 112
	mov	x1, x21
	bl	SCDDRV_SaveRawStream
	ldr	x0, [x27, x22, lsl 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 1732]
	cmp	w0, 1
	bne	.L1182
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L1173:
	ldr	x1, .LC253
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
.L1175:
	sub	w1, w0, w1
	cmp	w1, 2000
	bls	.L1176
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
	b	.L1176
	.p2align 3
.L1205:
	ldr	x0, [x23]
	blr	x0
	ldr	x1, .LC250
	add	x2, x24, 632
	ldr	w3, [x1]
	ldr	w1, [x2, x22, lsl 2]
	sub	w1, w0, w1
	cmp	w1, w3
	bls	.L1180
	str	w0, [x2, x22, lsl 2]
	mov	w1, 3402
	ldr	w2, [x29, 108]
	ldr	x0, [x29, 96]
	bl	DBG_AddTrace
	b	.L1180
	.p2align 3
.L1203:
	mov	x0, -1
	add	x1, x29, 112
	str	x0, [x29, 176]
	mov	w0, w20
	bl	SCDDRV_InsertRawPacket
	cbz	w0, .L1178
.L1204:
	ldr	x1, .LC249
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1166
	.size	FillRawData, .-FillRawData
	.align	3
.LC241:
	.xword	.LANCHOR0
	.align	3
.LC242:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC243:
	.xword	s_pstVfmwChan
	.align	3
.LC245:
	.xword	.LC244
	.align	3
.LC247:
	.xword	.LC246
	.align	3
.LC249:
	.xword	.LC248
	.align	3
.LC250:
	.xword	g_TraceBsPeriod
	.align	3
.LC251:
	.xword	.LANCHOR4
	.align	3
.LC253:
	.xword	.LC252
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
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	cmp	w19, 4096
	beq	.L1211
	cmp	w19, w21
	beq	.L1211
	mov	w24, 0
	add	x23, x20, 360448
	mov	w22, 2
	.p2align 2
.L1209:
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
	cmp	w0, wzr
	add	w1, w19, 1
	csinc	w24, w24, w24, ne
	asr	w19, w1, 31
	lsr	w19, w19, 20
	add	w1, w1, w19
	and	w1, w1, 4095
	sub	w19, w1, w19
	cmp	w21, w19
	bne	.L1209
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1211:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	ReleaseSegArrayPackets, .-ReleaseSegArrayPackets
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SM_SeekPtsInSegArray
	.type	SM_SeekPtsInSegArray, %function
SM_SeekPtsInSegArray:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	mov	x0, x30
	add	x19, x21, 98304
	mov	x22, x1
	add	x27, x19, 112
	bl	_mcount
	add	x26, x27, 360448
	mov	w20, 0
	ldp	x28, x23, [x22]
	mov	x25, x27
	ldp	w24, w3, [x26, 8]
	str	w24, [x26, 16]
	.p2align 2
.L1214:
	cmp	w24, w3
	beq	.L1215
.L1240:
	sxtw	x1, w24
	lsl	x0, x1, 2
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x0, x0, x1
	add	x0, x25, x0, lsl 3
	ldrsb	w1, [x0, 16]
	cbz	w1, .L1237
	cmp	w1, 2
	beq	.L1239
	ldr	x0, [x0, 48]
	cmn	x0, #1
	beq	.L1237
	cmp	x28, x0
	bls	.L1221
	add	w0, w24, 1
	str	w24, [x26, 16]
.L1236:
	asr	w24, w0, 31
	lsr	w24, w24, 20
	add	w0, w0, w24
	and	w0, w0, 4095
	sub	w24, w0, w24
	cmp	w24, w3
	bne	.L1240
.L1215:
	add	x1, x19, 112
	mov	w2, w24
	add	x1, x1, 360448
	mov	x0, x27
	ldr	w1, [x1, 8]
	bl	ReleaseSegArrayPackets
	add	w1, w20, w0
	ldr	w2, [x21, 4]
	cbz	w2, .L1229
	add	x0, x21, 88
	bl	DeleteRawPacket
.L1229:
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1237:
	add	w0, w24, 1
	b	.L1236
	.p2align 3
.L1221:
	beq	.L1241
	bcs	.L1214
	add	x4, x25, 360448
	ldr	w3, [x4, 16]
	sxtw	x2, w3
	lsl	x1, x2, 2
	sub	x1, x1, x2
	lsl	x1, x1, 2
	sub	x1, x1, x2
	add	x25, x25, x1, lsl 3
	ldr	x1, [x25, 48]
	cmn	x1, #1
	beq	.L1242
	cmp	x28, x1
	bls	.L1231
	sub	x28, x28, x1
	cmp	x23, x28
	bcs	.L1231
	add	x2, x19, 112
	mov	x1, x0
	add	x0, x2, 360448
	str	w24, [x0, 16]
.L1225:
	str	x1, [x22]
.L1223:
	add	x1, x19, 112
	mov	w2, w24
	add	x1, x1, 360448
	mov	x0, x27
	ldr	w1, [x1, 8]
	bl	ReleaseSegArrayPackets
	ldr	w2, [x21, 4]
	cbnz	w2, .L1243
	mov	w0, 0
.L1244:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1239:
	mov	w1, w24
	mov	x0, x27
	bl	ReleaseStreamSeg
	cmp	w0, wzr
	add	w1, w24, 1
	csinc	w20, w20, w20, ne
	asr	w24, w1, 31
	ldr	w3, [x26, 12]
	lsr	w24, w24, 20
	add	w1, w1, w24
	and	w1, w1, 4095
	sub	w24, w1, w24
	b	.L1214
.L1231:
	mov	w24, w3
	b	.L1225
.L1241:
	str	x28, [x22]
	b	.L1223
.L1242:
	mov	x1, x0
	str	w24, [x4, 16]
	b	.L1225
.L1243:
	add	w1, w20, w0
	add	x0, x21, 88
	bl	DeleteRawPacket
	mov	w0, 0
	b	.L1244
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
	ldr	x0, .LC256
	add	x0, x0, x19, sxtw 4
	ldr	x9, [x0, 88]
	cbz	x9, .L1266
	add	x7, x20, 98304
	ldr	w1, [x7]
	tbnz	w1, #31, .L1266
	ldr	w6, [x7, 4]
	tbnz	w6, #31, .L1266
	cmp	w22, 1
	mov	w3, w1
	mov	w10, 0
	ldp	x8, x11, [x21]
	beq	.L1279
.L1247:
	mov	w1, w3
	str	w3, [x7, 8]
	.p2align 2
.L1248:
	sxtw	x5, w1
	add	w0, w1, 1
	asr	w4, w0, 31
	lsl	x2, x5, 2
	sub	x2, x2, x5
	lsr	w4, w4, 22
	cmp	w1, w6
	add	w0, w0, w4
	add	x2, x20, x2, lsl 5
	and	w0, w0, 1023
	beq	.L1280
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L1281
	cmp	x8, x2
	bls	.L1254
	str	w1, [x7, 8]
	sub	w1, w0, w4
	b	.L1248
	.p2align 3
.L1281:
	add	w0, w1, 1
	asr	w1, w0, 31
	lsr	w1, w1, 22
	add	w0, w0, w1
	and	w0, w0, 1023
	sub	w1, w0, w1
	b	.L1248
	.p2align 3
.L1280:
	cmp	w3, w1
	bgt	.L1282
.L1275:
	sub	w1, w1, w3
	str	w3, [x7, 8]
	mov	x0, x20
	bl	DeleteRawPacket
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, -2
.L1246:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1282:
	add	w1, w1, 1024
	b	.L1275
	.p2align 3
.L1254:
	beq	.L1283
	ldr	w0, [x7, 8]
	sxtw	x4, w0
	lsl	x2, x4, 2
	sub	x2, x2, x4
	add	x2, x20, x2, lsl 5
	ldr	x2, [x2, 64]
	cmn	x2, #1
	beq	.L1277
	cmp	x8, x2
	bls	.L1260
	sub	x8, x8, x2
	cmp	x11, x8
	bcs	.L1260
.L1277:
	mov	w0, w1
	str	w1, [x7, 8]
.L1260:
	cmp	w3, w0
	sub	w1, w0, w3
	bgt	.L1284
.L1262:
	cmp	w22, 1
	beq	.L1285
.L1263:
	sxtw	x2, w0
	mov	x0, x20
	lsl	x3, x2, 2
	sub	x2, x3, x2
	add	x20, x20, x2, lsl 5
.L1278:
	ldr	x2, [x20, 64]
	str	x2, [x21]
	ldr	w2, [x7]
	str	w2, [x7, 8]
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
.L1279:
	add	x0, x9, 458752
	ldr	w10, [x0, 176]
	cmp	w10, 1
	bne	.L1247
	mov	w1, 3
	str	w1, [x0, 176]
	ldp	w3, w6, [x7]
	b	.L1247
	.p2align 3
.L1284:
	add	w1, w0, 1024
	sub	w1, w1, w3
	b	.L1262
.L1283:
	cmp	w1, w3
	bge	.L1276
	add	w1, w1, 1024
.L1276:
	cmp	w22, 1
	sub	w1, w1, w3
	beq	.L1286
.L1258:
	lsl	x0, x5, 2
	sub	x5, x0, x5
	mov	x0, x20
	add	x20, x20, x5, lsl 5
	b	.L1278
.L1285:
	add	x9, x9, 458752
	ldr	w2, [x9, 168]
	cmp	w1, w2
	ccmp	w10, 1, 0, le
	bne	.L1263
	str	w10, [x9, 176]
	ldr	w0, [x7, 8]
	b	.L1263
.L1286:
	add	x9, x9, 458752
	ldr	w0, [x9, 168]
	cmp	w1, w0
	ccmp	w10, 1, 0, le
	bne	.L1258
	str	w10, [x9, 176]
	b	.L1258
.L1266:
	mov	w0, -1
	b	.L1246
	.size	SM_SeekPtsInRawArray, .-SM_SeekPtsInRawArray
	.align	3
.LC256:
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
	mov	w22, w0
	mov	x0, x30
	mov	x23, x1
	bl	_mcount
	cmp	x23, xzr
	ccmp	w22, 31, 2, ne
	bhi	.L1301
	ldr	x0, .LC257
	add	x0, x0, x22, sxtw 4
	ldr	x20, [x0, 88]
	cbz	x20, .L1301
	mov	x1, x23
	mov	x0, x20
	bl	SM_SeekPtsInSegArray
	cbnz	w0, .L1290
.L1291:
	mov	w0, 0
.L1289:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1290:
	mov	w1, 0
	mov	w0, w22
	add	x20, x20, 88
	bl	DeleteRawPacketInBuffer
	mov	w3, 1
	mov	w2, w22
	mov	x1, x23
	mov	x0, x20
	bl	SM_SeekPtsInRawArray
	cbz	w0, .L1291
	add	x1, x20, 98304
	ldp	w3, w0, [x1]
	cmp	w3, w0
	bgt	.L1311
.L1310:
	sub	w3, w0, w3
	ldr	x2, [x23, 16]
	sxtw	x3, w3
	cmp	x3, x2
	bcs	.L1312
	sub	x3, x2, x3
	and	x0, x3, 1023
	lsr	x21, x3, 10
	cbnz	x0, .L1313
.L1296:
	add	w21, w21, 1
	mov	w19, 0
	cmp	w21, wzr
	bgt	.L1306
	b	.L1299
	.p2align 3
.L1314:
	cmp	w19, w21
	beq	.L1299
.L1306:
	mov	w2, w22
	mov	x1, x23
	mov	x0, x20
	add	w19, w19, 1
	bl	SM_SeekPtsAfterFillNewRaw
	cbnz	w0, .L1314
	b	.L1291
	.p2align 3
.L1311:
	add	w0, w0, 1024
	b	.L1310
	.p2align 3
.L1313:
	add	w21, w21, 1
	b	.L1296
	.p2align 3
.L1299:
	mov	w0, -2
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1301:
	mov	w0, -1
	b	.L1289
.L1312:
	ldr	x1, .LC259
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -2
	b	.L1289
	.size	SM_SeekPts, .-SM_SeekPts
	.align	3
.LC257:
	.xword	.LANCHOR0
	.align	3
.LC259:
	.xword	.LC258
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
	bgt	.L1318
	ldr	x1, .LC260
	sxtw	x2, w2
	ldr	x3, [x21, 128]
	add	x20, x20, 458752
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
.L1319:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1318:
	ldr	x1, .LC262
	mov	w3, w2
	mov	w2, w0
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -7
	b	.L1319
	.size	SM_MoveRawData, .-SM_MoveRawData
	.align	3
.LC260:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC262:
	.xword	.LC261
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
	mov	x21, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x21, 98304
	adds	x22, x0, 112
	beq	.L1333
	add	x1, x22, 360448
	ldp	w23, w24, [x1, 44]
.L1321:
	add	x0, x0, 112
	ldrsb	w1, [x21, 1]
	add	x19, x0, 360448
	ldr	w20, [x19, 28]
	cbnz	w1, .L1322
	add	w20, w20, w20, lsr 31
	mov	w0, 127
	asr	w20, w20, 1
	cmp	w20, w23
	ccmp	w24, w0, 0, gt
	ble	.L1340
.L1320:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1322:
	ldr	x0, .LC263
	ldr	x0, [x0]
	blr	x0
	add	x1, x21, 458752
	ldr	w2, [x1, 272]
	cmp	w0, w2
	bls	.L1325
	sub	w2, w0, w2
	str	w2, [x1, 268]
	cmp	w2, 1000
	ble	.L1320
	cmp	w20, wzr
	add	w0, w20, 3
	csel	w20, w0, w20, lt
	mov	w0, 63
	asr	w20, w20, 2
	cmp	w20, w23
	ccmp	w24, w0, 0, gt
	bgt	.L1320
	cbnz	w23, .L1328
	ldr	w0, [x1, 496]
	cbz	w0, .L1328
	cbz	x22, .L1331
	ldp	w1, w0, [x19, 8]
	mov	w23, 43691
	sub	w0, w0, w1
	movk	w23, 0xaaaa, lsl 16
	and	w0, w0, 4095
	umull	x23, w0, w23
	lsr	x23, x23, 32
	lsr	w23, w23, 1
	cbz	w23, .L1331
	mov	w20, 0
	b	.L1332
	.p2align 3
.L1341:
	ldr	w1, [x19, 8]
.L1332:
	add	w1, w1, w20
	mov	x0, x22
	add	w20, w20, 1
	bl	ReleaseStreamSeg
	cmp	w23, w20
	bne	.L1341
.L1331:
	ldr	x1, .LC265
	mov	w0, 0
	bl	dprint_vfmw
.L1330:
	strb	wzr, [x21, 1]
	strb	wzr, [x21]
	b	.L1320
	.p2align 3
.L1325:
	str	wzr, [x1, 268]
	str	w0, [x1, 272]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1333:
	mov	w23, 0
	mov	w24, 0
	b	.L1321
	.p2align 3
.L1340:
	ldr	x0, .LC263
	mov	w1, 1
	strb	w1, [x21, 1]
	add	x21, x21, 458752
	ldr	x0, [x0]
	blr	x0
	str	wzr, [x21, 268]
	str	w0, [x21, 272]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1328:
	ldr	x1, .LC267
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	mov	x0, x22
	bl	ReleaseStreamSeg
	b	.L1330
	.size	SCDDRV_ProcessSegFull, .-SCDDRV_ProcessSegFull
	.align	3
.LC263:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC265:
	.xword	.LC264
	.align	3
.LC267:
	.xword	.LC266
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
	ldr	x0, .LC268
	add	x19, x0, x19, sxtw 4
	ldr	x1, [x19, 88]
	cbz	x1, .L1345
	add	x0, x1, 458752
	ldr	w2, [x0, 256]
	cbz	w2, .L1345
	ldr	w0, [x0, 248]
	cmp	w0, 1
	beq	.L1345
	ldr	w0, [x1, 20]
	ldr	x2, [x1, 36]
	ldr	w1, [x1, 44]
	cmp	w0, 19
	str	x2, [x29, 32]
	str	w1, [x29, 40]
	beq	.L1345
	add	x1, x29, 32
	bl	SCDDRV_IsSCDByPass
	uxtb	w0, w0
	cmp	w0, wzr
	ldr	x19, [sp, 16]
	cset	w0, ne
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1345:
	ldr	x19, [sp, 16]
	mov	w0, 1
	ldp	x29, x30, [sp], 48
	ret
	.size	SCDDRV_CanNotSelectInst, .-SCDDRV_CanNotSelectInst
	.align	3
.LC268:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SM_DoNextInstance.part.12, %function
SM_DoNextInstance.part.12:
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
	ldr	x25, .LC269
	sxtw	x0, w21
	ldr	x23, .LC270
	lsl	x1, x0, 6
	ldr	x24, .LC271
	add	x0, x1, x0, lsl 3
	add	x22, x25, 88
	add	x0, x25, x0
	ldr	w19, [x0, 52]
	b	.L1363
	.p2align 3
.L1356:
	subs	w20, w20, #1
	beq	.L1370
.L1363:
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
	cbnz	w0, .L1356
	sxtw	x28, w19
	ldr	x0, [x23]
	lsl	x1, x28, 4
	ldr	x27, [x22, x1]
	blr	x0
	add	x26, x27, 458752
	ldr	w1, [x26, 312]
	subs	w1, w0, w1
	bmi	.L1371
	ldrsh	w2, [x27, 2]
	cmp	w2, 1
	beq	.L1372
.L1358:
	str	w0, [x26, 312]
	ldrsb	w0, [x27]
	cmp	w0, 1
	beq	.L1373
.L1360:
	strb	wzr, [x27, 1]
.L1361:
	ldr	x2, [x24, x28, lsl 3]
	mov	w1, w21
	mov	x0, x27
	add	x2, x2, 507904
	ldr	w2, [x2, 1720]
	str	w2, [x26, 464]
	bl	CutStreamWithSCD
	cmn	w0, #6
	cset	w1, eq
	strb	w1, [x27]
	cbnz	w0, .L1356
	ldr	x0, [x29, 104]
	add	x2, x25, 760
	ldr	x3, .LC272
	mov	w1, 1
	add	x2, x2, x28, lsl 2
	mov	w4, 4580
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
.L1371:
	str	w0, [x26, 312]
	ldrsh	w1, [x27, 2]
	cmp	w1, 1
	beq	.L1356
	str	w0, [x26, 312]
	ldrsb	w0, [x27]
	cmp	w0, 1
	bne	.L1360
.L1373:
	mov	x0, x27
	bl	SCDDRV_ProcessSegFull
	b	.L1361
	.p2align 3
.L1372:
	cmp	w1, 499
	bhi	.L1358
	subs	w20, w20, #1
	bne	.L1363
.L1370:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	mov	w0, -3
	ldp	x29, x30, [sp], 112
	ret
	.size	SM_DoNextInstance.part.12, .-SM_DoNextInstance.part.12
	.align	3
.LC269:
	.xword	.LANCHOR0
	.align	3
.LC270:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC271:
	.xword	s_pstVfmwChan
	.align	3
.LC272:
	.xword	.LANCHOR4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	SCDDRV_ActivateSCD.part.13, %function
SCDDRV_ActivateSCD.part.13:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC275
	add	x1, x20, x19, lsl 2
	ldr	w0, [x1, 600]
	cbz	w0, .L1375
	cmp	w0, 1
	beq	.L1379
.L1374:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1375:
	add	x1, x29, 60
	mov	w0, w19
	bl	SM_DoNextInstance.part.12
	cbnz	w0, .L1374
	lsl	x0, x19, 6
	ldr	w1, [x29, 60]
	add	x0, x0, x19, lsl 3
	add	x0, x20, x0
	str	w1, [x0, 52]
	cbnz	w19, .L1377
	mov	w0, 1
	str	w0, [x20, 56]
.L1377:
	ldr	x0, .LC276
	ldr	x0, [x0]
	blr	x0
	lsl	x1, x19, 6
	ldr	x2, .LC277
	add	x19, x1, x19, lsl 3
	ldr	x1, .LC279
	add	x19, x20, x19
	mov	w3, 4799
	add	x2, x2, 192
	str	w0, [x19, 60]
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1379:
	mov	w0, 2
	str	w0, [x1, 600]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	SCDDRV_ActivateSCD.part.13, .-SCDDRV_ActivateSCD.part.13
	.align	3
.LC275:
	.xword	.LANCHOR0
	.align	3
.LC276:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC277:
	.xword	.LANCHOR4
	.align	3
.LC279:
	.xword	.LC278
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
	ldr	x2, .LC280
	add	x2, x2, x19, sxtw 2
	ldr	w0, [x2, 600]
	cbz	w0, .L1381
	cmp	w0, 1
	mov	w0, -3
	beq	.L1384
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1381:
	mov	x1, x20
	mov	w0, w19
	bl	SM_DoNextInstance.part.12
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1384:
	mov	w1, 2
	str	w1, [x2, 600]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_DoNextInstance, .-SM_DoNextInstance
	.align	3
.LC280:
	.xword	.LANCHOR0
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
	ldr	x0, .LC281
	ldr	x0, [x0]
	blr	x0
	sxtw	x2, w19
	ldr	x5, .LC282
	lsl	x1, x2, 4
	sub	x1, x1, x2
	add	x1, x5, x1, lsl 2
	ldr	w3, [x1, 48]
	cbz	w3, .L1385
	ldr	w6, [x1, 44]
	add	w4, w6, 49152
	add	w4, w4, 848
	cmp	w3, w4
	bhi	.L1388
	ldr	w4, [x1, 52]
.L1389:
	lsl	x1, x2, 4
	sub	w3, w0, w3
	sub	x2, x1, x2
	sub	w0, w0, w6
	add	w3, w3, w4
	cmp	w0, 999
	add	x2, x5, x2, lsl 2
	stp	wzr, w3, [x2, 48]
	bls	.L1385
	lsl	w1, w3, 6
	str	wzr, [x2, 44]
	sub	w1, w1, w3
	lsl	w1, w1, 1
	sub	w3, w1, w3
	lsl	w3, w3, 3
	udiv	w0, w3, w0
	str	w0, [x2, 56]
.L1385:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1388:
	mov	w6, w3
	mov	w4, 0
	str	w3, [x1, 44]
	b	.L1389
	.size	SCDDRV_RecordGlobalState, .-SCDDRV_RecordGlobalState
	.align	3
.LC281:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC282:
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
	ldr	x0, .LC283
	add	x19, x0, x19, sxtw 4
	ldr	x19, [x19, 88]
	ldr	w0, [x19, 60]
	cmp	w0, 1
	beq	.L1401
.L1391:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1401:
	adds	x1, x19, 88
	beq	.L1394
	add	x1, x1, 98304
	ldr	w0, [x1, 4]
	ldr	w1, [x1]
	sub	w0, w0, w1
	add	w1, w0, 1024
	cmp	w0, wzr
	csel	w0, w1, w0, lt
.L1397:
	ldrsb	w20, [x19, 2]
	cmp	w20, 1
	bne	.L1391
	ldr	w1, [x19, 68]
	cmp	w1, w0
	bne	.L1391
	mov	x0, x19
	bl	SM_MoveRawData
	cbz	w0, .L1391
	ldr	x1, .LC285
	mov	w0, w20
	add	x19, x19, 458752
	bl	dprint_vfmw
	ldr	w0, [x19, 240]
	bl	SM_Reset
	b	.L1391
	.p2align 3
.L1394:
	ldr	x1, .LC287
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1397
	.size	SCDDRV_MoveRawByOmxPath, .-SCDDRV_MoveRawByOmxPath
	.align	3
.LC283:
	.xword	.LANCHOR0
	.align	3
.LC285:
	.xword	.LC284
	.align	3
.LC287:
	.xword	.LC286
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
	cbz	w19, .L1420
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1420:
	ldr	x20, .LC288
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	ldr	x19, .LC289
	ldr	w0, [x19, 80]
	add	w0, w0, 2112
	bl	MEM_ReadPhyWord
	tbnz	x0, 0, .L1421
.L1404:
	ldr	x0, .LC291
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1413
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Notify_ModuleIdle
.L1413:
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1421:
	ldr	w0, [x19, 80]
	mov	w1, 1
	add	w0, w0, 2084
	bl	MEM_WritePhyWord
	ldp	w1, w21, [x19, 48]
	cmp	w1, wzr
	add	x0, x19, x21, sxtw 4
	ldr	x22, [x0, 88]
	ccmp	x22, xzr, 4, ne
	beq	.L1422
	ldr	x3, .LC290
	mov	w4, 4673
	add	x2, x19, 888
	mov	w1, 2
	add	x3, x3, 216
	mov	w0, w21
	bl	RecordPOS
	mov	w0, 0
	bl	SCDDRV_RecordGlobalState
	ldr	w0, [x19, 56]
	cmp	w0, 1
	beq	.L1423
.L1406:
	ldr	x1, [x20, 256]
	mov	w0, 1
	blr	x1
	ldr	x1, [x20, 256]
	mov	w0, 0
	blr	x1
	b	.L1404
	.p2align 3
.L1423:
	add	x23, x22, 458752
	ldr	w0, [x23, 256]
	cmp	w0, 1
	beq	.L1424
.L1407:
	ldr	w0, [x19, 600]
	str	wzr, [x23, 248]
	cbz	w0, .L1410
	cmp	w0, 1
	beq	.L1425
.L1411:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	b	.L1406
	.p2align 3
.L1422:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	b	.L1404
.L1410:
	add	x1, x29, 76
	mov	w0, 0
	bl	SM_DoNextInstance.part.12
	cbnz	w0, .L1411
	ldr	w1, [x29, 76]
	ldr	x0, [x20]
	str	w1, [x19, 52]
	mov	w1, 1
	str	w1, [x19, 56]
	blr	x0
	str	w0, [x19, 60]
	b	.L1406
.L1424:
	add	x0, x23, 168
	ldr	w1, [x0, 8]
	cmp	w1, 3
	beq	.L1426
	mov	w2, 2
	mov	w1, 0
	str	w2, [x0, 8]
	mov	x0, x22
	bl	ProcessScdReturn.part.10
.L1409:
	mov	w0, w21
	bl	SCDDRV_MoveRawByOmxPath
	b	.L1407
.L1425:
	mov	w0, 2
	str	w0, [x19, 600]
	b	.L1411
.L1426:
	mov	w1, 2
	str	w1, [x0, 8]
	b	.L1409
	.size	SM_SCDIntServeProc, .-SM_SCDIntServeProc
	.align	3
.LC288:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC289:
	.xword	.LANCHOR0
	.align	3
.LC290:
	.xword	.LANCHOR4
	.align	3
.LC291:
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
	cbnz	w19, .L1436
	ldr	x19, .LC292
	mov	w4, 0
	ldr	x23, .LC293
	mov	w3, 4725
	ldr	x22, .LC295
	mov	w0, 26
	add	x21, x23, 240
	ldr	w5, [x19, 56]
	mov	x2, x21
	mov	x1, x22
	bl	dprint_vfmw
	ldr	w20, [x19, 56]
	cbz	w20, .L1438
	mov	w4, 0
	mov	w5, w20
	mov	w3, 4734
	mov	x2, x21
	mov	x1, x22
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x0, .LC298
	ldr	x0, [x0]
	blr	x0
	ldr	w4, [x19, 60]
	cmp	w0, w4
	bcs	.L1430
	str	w0, [x19, 60]
.L1431:
	ldr	x1, .LC303
	mov	w4, 0
	mov	w3, 4780
	add	x2, x23, 240
	mov	w0, 26
	mov	w20, 1
	bl	dprint_vfmw
.L1437:
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1430:
	sub	w4, w0, w4
	cmp	w4, 2000
	bls	.L1431
	ldr	x1, .LC300
	mov	w3, 0
	ldr	w2, [x19, 52]
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, .LC301
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1432
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Reset_Module
.L1433:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle.part.0
	ldr	w0, [x19, 52]
	add	x19, x19, x0, sxtw 4
	ldr	x1, [x19, 88]
	cbz	x1, .L1435
	add	x1, x1, 458752
	str	wzr, [x1, 248]
.L1435:
	bl	DeleteLastSendRaw
	mov	w20, 0
	mov	w0, w20
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1438:
	ldr	x1, .LC297
	mov	x2, x21
	mov	w4, 0
	mov	w3, 4729
	mov	w0, 26
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1432:
	mov	w0, 0
	bl	ResetSCD
	b	.L1433
	.p2align 3
.L1436:
	mov	w20, -1
	b	.L1437
	.size	SCDDRV_CheckDevice, .-SCDDRV_CheckDevice
	.align	3
.LC292:
	.xword	.LANCHOR0
	.align	3
.LC293:
	.xword	.LANCHOR4
	.align	3
.LC295:
	.xword	.LC294
	.align	3
.LC297:
	.xword	.LC296
	.align	3
.LC298:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC300:
	.xword	.LC299
	.align	3
.LC301:
	.xword	g_HalDisable
	.align	3
.LC303:
	.xword	.LC302
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
	cbnz	w19, .L1439
	mov	w0, 0
	bl	SCDDRV_ActivateSCD.part.13
.L1439:
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
	ldr	x20, .LC305
	add	x20, x20, 88
	b	.L1443
	.p2align 3
.L1442:
	add	w19, w19, 1
	cmp	w19, 32
	beq	.L1450
.L1443:
	ldr	x0, [x20]
	add	x20, x20, 16
	add	x1, x0, 458752
	cbz	x0, .L1442
	ldr	w0, [x1, 256]
	cmp	w0, 1
	bne	.L1442
	mov	w0, w19
	add	w19, w19, 1
	bl	FillRawData
	cmp	w19, 32
	bne	.L1443
	.p2align 2
.L1450:
	ldr	x19, .LC306
	mov	w4, 1
	ldr	x1, .LC308
	mov	w3, 0
	add	x19, x19, 264
	mov	w0, 26
	mov	x2, x19
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_CheckDevice
	cbz	w0, .L1444
	ldr	x1, .LC310
	mov	x2, x19
	mov	w4, 0
	mov	w3, 4828
	mov	w0, 26
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1444:
	ldr	x1, .LC312
	mov	x2, x19
	mov	w4, 0
	mov	w3, 4823
	mov	w0, 26
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_ActivateSCD.part.13
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SM_Wakeup, .-SM_Wakeup
	.align	3
.LC305:
	.xword	.LANCHOR0
	.align	3
.LC306:
	.xword	.LANCHOR4
	.align	3
.LC308:
	.xword	.LC307
	.align	3
.LC310:
	.xword	.LC309
	.align	3
.LC312:
	.xword	.LC311
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
	bls	.L1465
.L1451:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1465:
	mov	w0, 26
	bl	IsDprintTypeEnable
	cbz	w0, .L1451
	ldr	x3, .LC314
	mov	w2, w20
	ldr	x1, .LC316
	mov	w0, 26
	add	x3, x3, x20, sxtw 4
	ldr	x23, [x3, 88]
	bl	dprint_vfmw
	ldr	x1, .LC318
	mov	w0, 26
	add	x22, x23, 88
	add	x21, x22, 98304
	ldr	w2, [x21]
	bl	dprint_vfmw
	ldr	x1, .LC320
	mov	w0, 26
	ldr	w2, [x21, 4]
	bl	dprint_vfmw
	ldr	x1, .LC322
	mov	w0, 26
	ldr	w2, [x21, 8]
	bl	dprint_vfmw
	ldr	x1, .LC324
	mov	w0, 26
	ldr	w2, [x21, 12]
	bl	dprint_vfmw
	ldr	x1, .LC326
	mov	w0, 26
	ldr	w2, [x21, 16]
	bl	dprint_vfmw
	cmp	w19, 1
	beq	.L1455
.L1459:
	ldr	x1, .LC328
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
.L1455:
	cbz	x22, .L1456
	ldp	w28, w21, [x21]
	sub	w21, w21, w28
	cmp	w21, wzr
	add	w0, w21, 1024
	csel	w21, w0, w21, lt
	cmp	w21, wzr
	ble	.L1459
	ldr	x27, .LC330
	add	w0, w21, w28
	ldr	x26, .LC332
	ldr	x25, .LC334
	ldr	x24, .LC336
	str	w0, [x29, 108]
	.p2align 2
.L1458:
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
	bne	.L1458
	b	.L1459
.L1456:
	ldr	x2, .LC337
	mov	w3, 4857
	ldr	x1, .LC339
	mov	w0, 22
	add	x2, x2, 280
	bl	dprint_vfmw
	b	.L1459
	.size	PrintScdRawState, .-PrintScdRawState
	.align	3
.LC314:
	.xword	.LANCHOR0
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
	.align	3
.LC337:
	.xword	.LANCHOR4
	.align	3
.LC339:
	.xword	.LC338
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
	bls	.L1480
.L1466:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L1480:
	mov	w0, 26
	bl	IsDprintTypeEnable
	cbz	w0, .L1466
	ldr	x3, .LC340
	mov	w2, w20
	ldr	x1, .LC342
	mov	w0, 26
	add	x3, x3, x20, sxtw 4
	ldr	x22, [x3, 88]
	bl	dprint_vfmw
	ldr	x1, .LC344
	mov	w0, 26
	add	x24, x22, 98304
	add	x21, x24, 112
	add	x19, x21, 360448
	ldr	w2, [x19, 8]
	bl	dprint_vfmw
	ldr	x1, .LC346
	mov	w0, 26
	ldr	w2, [x19, 12]
	bl	dprint_vfmw
	ldr	x1, .LC348
	mov	w0, 26
	ldr	w2, [x19, 20]
	bl	dprint_vfmw
	ldr	x1, .LC350
	mov	w0, 26
	ldr	w2, [x19, 24]
	bl	dprint_vfmw
	ldr	x1, .LC352
	mov	w0, 26
	ldr	x2, [x24, 112]
	bl	dprint_vfmw
	ldr	x1, .LC354
	mov	w0, 26
	ldr	w2, [x19, 28]
	bl	dprint_vfmw
	ldr	x1, .LC356
	mov	w0, 26
	ldr	w2, [x19, 32]
	bl	dprint_vfmw
	ldr	x1, .LC358
	mov	w0, 26
	ldr	w2, [x19, 36]
	bl	dprint_vfmw
	cmp	w23, 1
	beq	.L1470
.L1471:
	ldr	x1, .LC360
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
.L1470:
	cbz	x21, .L1471
	ldp	w24, w23, [x19, 8]
	sub	w23, w23, w24
	ands	w23, w23, 4095
	beq	.L1471
	ldr	x28, .LC362
	add	w23, w24, w23
	ldr	x27, .LC364
	ldr	x26, .LC366
	ldr	x25, .LC368
	str	x21, [x29, 104]
	.p2align 2
.L1472:
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
	ldr	x1, .LC370
	bl	dprint_vfmw
	ldrb	w2, [x21, 130]
	mov	w0, 26
	ldr	x1, .LC372
	bl	dprint_vfmw
	ldr	x1, .LC374
	mov	w0, 26
	ldr	x2, [x19, 40]
	bl	dprint_vfmw
	cmp	w23, w24
	bne	.L1472
	b	.L1471
	.size	PrintScdSegState, .-PrintScdSegState
	.align	3
.LC340:
	.xword	.LANCHOR0
	.align	3
.LC342:
	.xword	.LC341
	.align	3
.LC344:
	.xword	.LC343
	.align	3
.LC346:
	.xword	.LC345
	.align	3
.LC348:
	.xword	.LC347
	.align	3
.LC350:
	.xword	.LC349
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
	.global	g_pScdDrvParamBase
	.global	s_ScdRegResetOKPhyAddr
	.global	s_ScdRegResetPhyAddr
	.global	s_ScdRegPhyBaseAddr
	.global	g_ScdDrvParam
	.global	s_SmIIS
	.global	g_hex_flag
	.global	g_hex_len
	.global	g_hex_base_addr
	.global	g_hex_base_vir_addr
	.section	.rodata
	.align	3
.LANCHOR3 = . + 0
	.type	__func__.52822, %object
	.size	__func__.52822, 19
__func__.52822:
	.string	"SCDDRV_LoadDspCode"
	.zero	5
	.type	__func__.52895, %object
	.size	__func__.52895, 16
__func__.52895:
	.string	"DeleteRawPacket"
	.type	__FUNCTION__.53001, %object
	.size	__FUNCTION__.53001, 17
__FUNCTION__.53001:
	.string	"ReleaseStreamSeg"
	.zero	7
	.type	__func__.53069, %object
	.size	__func__.53069, 14
__func__.53069:
	.string	"SM_OpenSCDDrv"
	.zero	2
	.type	__func__.53144, %object
	.size	__func__.53144, 16
__func__.53144:
	.string	"SM_LinkRawToSeg"
	.type	__func__.53164, %object
	.size	__func__.53164, 16
__func__.53164:
	.string	"SM_CopyRawToSeg"
	.type	__func__.53497, %object
	.size	__func__.53497, 17
__func__.53497:
	.string	"GetMpeg4ModeFlag"
	.zero	7
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
	.type	__func__.53571, %object
	.size	__func__.53571, 17
__func__.53571:
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
	.type	__func__.53599, %object
	.size	__func__.53599, 17
__func__.53599:
	.string	"FillEosRawStream"
	.zero	7
	.type	__func__.53624, %object
	.size	__func__.53624, 17
__func__.53624:
	.string	"FillVC1ExtraData"
	.zero	7
	.type	__func__.53629, %object
	.size	__func__.53629, 19
__func__.53629:
	.string	"FillDIVX3ExtraData"
	.zero	5
	.type	__func__.53634, %object
	.size	__func__.53634, 19
__func__.53634:
	.string	"FillREAL8ExtraData"
	.zero	5
	.type	__func__.53642, %object
	.size	__func__.53642, 14
__func__.53642:
	.string	"FillExtraData"
	.zero	2
	.type	__func__.52909, %object
	.size	__func__.52909, 24
__func__.52909:
	.string	"DeleteRawPacketInBuffer"
	.type	__FUNCTION__.53043, %object
	.size	__FUNCTION__.53043, 9
__FUNCTION__.53043:
	.string	"SM_Reset"
	.zero	7
	.type	__FUNCTION__.53561, %object
	.size	__FUNCTION__.53561, 12
__FUNCTION__.53561:
	.string	"FillRawData"
	.zero	4
	.type	__FUNCTION__.53767, %object
	.size	__FUNCTION__.53767, 18
__FUNCTION__.53767:
	.string	"SM_DoNextInstance"
	.zero	6
	.type	__func__.53804, %object
	.size	__func__.53804, 19
__func__.53804:
	.string	"SCDDRV_ActivateSCD"
	.zero	5
	.type	__FUNCTION__.53791, %object
	.size	__FUNCTION__.53791, 19
__FUNCTION__.53791:
	.string	"SM_SCDIntServeProc"
	.zero	5
	.type	__func__.53798, %object
	.size	__func__.53798, 19
__func__.53798:
	.string	"SCDDRV_CheckDevice"
	.zero	5
	.type	__func__.53813, %object
	.size	__func__.53813, 10
__func__.53813:
	.string	"SM_Wakeup"
	.zero	6
	.type	__FUNCTION__.53825, %object
	.size	__FUNCTION__.53825, 17
__FUNCTION__.53825:
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
.LC7:
	ASCII(.string	"Fatal: get g_hex_base_addr(0x%x) vir addr failed!\n" )
	.zero	5
.LC12:
	ASCII(.string	"Warn: eVidStd = %d have not DSP vfmw bin file!!\n" )
	.zero	7
.LC15:
	ASCII(.string	"%s failed!\n" )
	.zero	4
.LC17:
	ASCII(.string	"%s success!\n" )
	.zero	3
.LC26:
	ASCII(.string	"Ignore the reset request when the SCD[%d] clock is closed.\n" )
	.zero	4
.LC28:
	ASCII(.string	"SCD[%d]   ResetSCD ERROR!!!\n" )
	.zero	3
.LC38:
	ASCII(.string	"line: %d Get SmID fail!" )
.LC40:
	ASCII(.string	"DelRaw err PacketNum = %d, DelNum = %d\n" )
.LC43:
	ASCII(.string	"%s release RawPhyAddr = 0x%x, Len = %d\n" )
.LC47:
	ASCII(.string	"line: %d DelNum = %d,RawPacketOffSet = %d,DelNum = %d,Next Length = %d,is_extern_eop_flag = %d\n\n" )
	.zero	7
.LC50:
	ASCII(.string	"line: %d pSmInstArray is NULL!\n" )
.LC59:
	ASCII(.string	"Read_seg SegPacket.PhyAddr=0x%x, LenByte=%d, IsLastSeg=%d\n" )
	.zero	5
.LC61:
	ASCII(.string	"Release SegPacket.PhyAddr=0x%x,LenByte=%d,IsLastSeg=%d StreamID=%d\n" )
	.zero	4
.LC64:
	ASCII(.string	"Array out of bound in function %s\n" )
	.zero	5
.LC79:
	ASCII(.string	"ScdId is wrong! %s error\n" )
	.zero	6
.LC84:
	ASCII(.string	"%s: g_hex_base_vir_addr = NULL\n" )
.LC92:
	ASCII(.string	"line: %d, SmID = %d is not expected!\n" )
	.zero	2
.LC94:
	ASCII(.string	"line: %d, SmID = %d, ScdId = %d is not expected!\n" )
	.zero	6
.LC103:
	ASCII(.string	"%s not support discontinue raw.\n" )
	.zero	7
.LC105:
	ASCII(.string	"%s VirAddr is null!!\n" )
	.zero	2
.LC110:
	ASCII(.string	"Raw packet TOO BIG! Can't copy to seg! Len: 0x%x\n" )
	.zero	6
.LC112:
	ASCII(.string	"line: %d, delet raw failed!\n" )
	.zero	3
.LC115:
	ASCII(.string	"[%s %d] VirAddr is null!!\n" )
	.zero	5
.LC134:
	ASCII(.string	"InstID = %d EsRelease!\n" )
.LC138:
	ASCII(.string	"Cann't Start SCD, Ret = %d\n" )
	.zero	4
.LC141:
	ASCII(.string	"SM_CfgBuf Err! ret =%d\n" )
.LC146:
	ASCII(.string	"Line: %d, The length of seg packet is invalid: %d\n" )
	.zero	5
.LC150:
	ASCII(.string	"Line: %d, start code num from scd state reg: %d, release raw packet anyway!\n" )
	.zero	3
.LC155:
	ASCII(.string	"[%s %d] pCurrentStartCodeVirAddr is null!!\n" )
	.zero	4
.LC159:
	ASCII(.string	"Line: %d, pNextStartCodeVirAddr is null!\n" )
	.zero	6
.LC162:
	ASCII(.string	"ValidSegNum = %d, FilteredSegNum = 0, release raw packet anyway!\n" )
	.zero	6
.LC169:
	ASCII(.string	"%s: pRawPacket = NULL!\n" )
.LC172:
	ASCII(.string	"%s: unkown standard type = %d!\n" )
.LC174:
	ASCII(.string	"%s: Length(%d)+FlagLen(%d) > BufLen(%d)\n" )
	.zero	7
.LC183:
	ASCII(.string	"%s: FlagLen(%d) > RawPacketLength(%d)\n" )
	.zero	1
.LC187:
	ASCII(.string	"Func: %s, buffer has no enough space,(act: %d, header_buf: %d)\n" )
.LC190:
	ASCII(.string	"Func: %s, buffer has no enough space,(act: %d, str_buf: %d)\n" )
	.zero	3
.LC192:
	ASCII(.string	"Func: %s, buffer has no enough space,(act:%d, str_buf: %d, header_buf: %d)\n" )
	.zero	4
.LC195:
	ASCII(.string	"Func: %s, buffer has no enough space, (act: %d, str_buf: %d)\n" )
	.zero	2
.LC201:
	ASCII(.string	"Func: %s, buffer has no enough space,(act:%d, str_buf:%d)\n" )
	.zero	5
.LC204:
	ASCII(.string	"%s: RawPacket Length %d <= 0\n" )
	.zero	2
.LC208:
	ASCII(.string	"Chan %d has been destroyed or the function pointer -- ReleaseRawStreamData pStreamIntf is NULL!" )
.LC211:
	ASCII(.string	"line: %d s_SmIIS[%d].pSmInstArray is NULL\n" )
	.zero	5
.LC220:
	ASCII(.string	"line: %d, pScdInstance is NULL!\n" )
	.zero	7
.LC224:
	ASCII(.string	"%s %d force to clear SCDState = 0\n" )
	.zero	5
.LC226:
	ASCII(.string	"%s %d FMW_OK !=  GetRawStreamNum !!\n" )
	.zero	3
.LC230:
	ASCII(.string	"Chan %d has been destroyed or the function pointer -- ReadRawStreamData pStreamIntf is NULL!" )
	.zero	3
.LC232:
	ASCII(.string	"line: %d s_SmIIS.pSmInstArray[%d] is NULL\n" )
	.zero	5
.LC234:
	ASCII(.string	"Chan %d FillEosRawStream failed!\n" )
	.zero	6
.LC236:
	ASCII(.string	"Chan %d FillExtraData failed!\n" )
	.zero	1
.LC238:
	ASCII(.string	"Release this packet failed!\n" )
	.zero	3
.LC244:
	ASCII(.string	"raw_pts: %lld\n" )
	.zero	1
.LC246:
	ASCII(.string	"Get RawPhyAddr=0x%x,Len=%d\n" )
	.zero	4
.LC248:
	ASCII(.string	"!!!push raw err!!!\n" )
	.zero	4
.LC252:
	ASCII(.string	"Chan%d raw full\n" )
	.zero	7
.LC258:
	ASCII(.string	"RawNum %lld <= RawNumInVfmw %lld\n" )
	.zero	6
.LC261:
	ASCII(.string	"No space for raw move, total:%d+%d > max:%d!\n" )
	.zero	2
.LC264:
	ASCII(.string	"scd buffer is full, reset scd!\n" )
.LC266:
	ASCII(.string	"(%d ms) not release stream seg, release anyway!\n" )
	.zero	7
.LC278:
	ASCII(.string	"%s,%d, active scd Success!\n" )
	.zero	4
.LC284:
	ASCII(.string	"Move raw data failed, force to reset scd.\n" )
	.zero	5
.LC286:
	ASCII(.string	"SCD GetRawStreamNum Fail.\n" )
	.zero	5
.LC294:
	ASCII(.string	"%s,%d,SCD(ID = %d) SCDState = %d\n" )
	.zero	6
.LC296:
	ASCII(.string	"%s,%d,SCD(ID = %d) return Idle!\n" )
	.zero	7
.LC299:
	ASCII(.string	"Chan %d SCD[%d] Time Out(%d ms), Reset it!\n" )
	.zero	4
.LC302:
	ASCII(.string	"%s,%d,SCD(ID = %d) really busy!\n" )
	.zero	7
.LC307:
	ASCII(.string	"%s prepare to check SCD(%d)/(MAX_SCD_NUM = %d)\n" )
.LC309:
	ASCII(.string	"%s,%d,SCD(ID = %d) return BUSY!!\n" )
	.zero	6
.LC311:
	ASCII(.string	"%s,%d,find idle SCD(ID = %d)\n" )
	.zero	2
.LC315:
	ASCII(.string	"********** SmID [%d] RawState begin **********\n" )
.LC317:
	ASCII(.string	"RawHead=%d\n" )
	.zero	4
.LC319:
	ASCII(.string	"RawTail=%d\n" )
	.zero	4
.LC321:
	ASCII(.string	"RawHistory=%d\n" )
	.zero	1
.LC323:
	ASCII(.string	"RawFirstPacketOffset=%d\n" )
	.zero	7
.LC325:
	ASCII(.string	"CurShowIndex=%d\n" )
	.zero	7
.LC327:
	ASCII(.string	"********** SmID [%d] RawState end   **********\n" )
.LC329:
	ASCII(.string	"RawPhyAddr=0x%x\n" )
	.zero	7
.LC331:
	ASCII(.string	"RawVirAddr=0x%x\n" )
	.zero	7
.LC333:
	ASCII(.string	"RawLength=%d\n" )
	.zero	2
.LC335:
	ASCII(.string	"RawPts=%ld\n" )
	.zero	4
.LC338:
	ASCII(.string	"%s %d FMW_OK !=  GetRawStreamNum!!\n" )
	.zero	4
.LC341:
	ASCII(.string	"********** SmID [%d] SegState begin **********\n" )
.LC343:
	ASCII(.string	"SegHead=%d\n" )
	.zero	4
.LC345:
	ASCII(.string	"SegTail=%d\n" )
	.zero	4
.LC347:
	ASCII(.string	"SegCurrent=%d\n" )
	.zero	1
.LC349:
	ASCII(.string	"SegBufPhyAddr=%p\n" )
	.zero	6
.LC351:
	ASCII(.string	"SegBufVirAddr=%p\n" )
	.zero	6
.LC353:
	ASCII(.string	"SegBufSize=%d\n" )
	.zero	1
.LC355:
	ASCII(.string	"SegBufReadAddr=%p\n" )
	.zero	5
.LC357:
	ASCII(.string	"SegBufWriteAddr=%pd\n" )
	.zero	3
.LC359:
	ASCII(.string	"********** SmID [%d] SegState end   **********\n" )
.LC361:
	ASCII(.string	"SegPhyAddr=0x%x\n" )
	.zero	7
.LC363:
	ASCII(.string	"SegVirAddr=0x%x\n" )
	.zero	7
.LC365:
	ASCII(.string	"SegLength=%d\n" )
	.zero	2
.LC367:
	ASCII(.string	"SegStreamID=%d\n" )
.LC369:
	ASCII(.string	"SegState=%d\n" )
	.zero	3
.LC371:
	ASCII(.string	"SegIsLastSeg=%d\n" )
	.zero	7
.LC373:
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
	.type	last_rec_pos_time.53556, %object
	.size	last_rec_pos_time.53556, 128
last_rec_pos_time.53556:
	.zero	128
	.type	LastRecPosTime.53764, %object
	.size	LastRecPosTime.53764, 128
LastRecPosTime.53764:
	.zero	128
	.type	last_rec_pos_time.53789, %object
	.size	last_rec_pos_time.53789, 128
last_rec_pos_time.53789:
	.zero	128
	.type	s_ScdRegResetOKPhyAddr, %object
	.size	s_ScdRegResetOKPhyAddr, 4
s_ScdRegResetOKPhyAddr:
	.zero	4
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
