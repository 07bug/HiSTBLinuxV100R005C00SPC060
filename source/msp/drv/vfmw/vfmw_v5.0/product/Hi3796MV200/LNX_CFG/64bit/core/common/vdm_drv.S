#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_drv.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VDMDRV_AdjustErrRatio, %function
VDMDRV_AdjustErrRatio:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	sxtw	x19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	ldr	x22, .LC0
	add	x1, x22, x19, lsl 6
	ldr	w24, [x1, 8]
	cbz	w20, .L3
	cmp	w20, 2
	bls	.L15
	add	x0, x29, 80
	ldr	w2, [x1, 12]
	ldr	x1, [x1, 48]
	str	w2, [x29, 68]
	str	w19, [x0, -16]!
	str	x1, [x29, 72]
	bl	PostPro_GetErrRatio
	str	w0, [x21]
	ldr	x20, .LC3
	cbnz	w0, .L16
.L6:
	add	x19, x22, x19, lsl 6
	ldr	x1, [x20, w24, sxtw 3]
	mov	w0, 0
	add	x1, x1, 507904
	ldr	w3, [x19, 12]
	sub	w4, w3, #8
	ldr	w2, [x1, 1724]
	cmp	w4, 1
	ccmp	w3, 5, 4, hi
	add	w2, w2, 1
	cset	w3, eq
	str	w2, [x1, 1724]
	cbz	w3, .L17
	str	w0, [x21]
.L18:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L15:
	ldr	x1, .LC2
	mov	w4, 100
	mov	w3, w20
	mov	w2, w24
	str	w4, [x21]
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L3:
	str	wzr, [x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L17:
	ldr	w0, [x21]
	mov	w1, 100
	cmp	w0, w1
	csel	w0, w0, w1, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	str	w0, [x21]
	b	.L18
	.p2align 3
.L16:
	ldr	x3, [x20, w24, sxtw 3]
	mov	w4, w0
	ldr	x1, .LC5
	mov	w2, w24
	add	x3, x3, 507904
	mov	w0, 1
	ldr	w3, [x3, 1724]
	bl	dprint_vfmw
	b	.L6
	.size	VDMDRV_AdjustErrRatio, .-VDMDRV_AdjustErrRatio
	.align	3
.LC0:
	.xword	.LANCHOR0
	.align	3
.LC2:
	.xword	.LC1
	.align	3
.LC3:
	.xword	s_pstVfmwChan
	.align	3
.LC5:
	.xword	.LC4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VDMDRV_ClearChanIsDec.part.4, %function
VDMDRV_ClearChanIsDec.part.4:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC6
	mov	w3, 225
	ldr	x1, .LC8
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMDRV_ClearChanIsDec.part.4, .-VDMDRV_ClearChanIsDec.part.4
	.align	3
.LC6:
	.xword	.LANCHOR1
	.align	3
.LC8:
	.xword	.LC7
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_Init
	.type	VDMDRV_Init, %function
VDMDRV_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L23
	ldr	x3, .LC11
	mov	x2, 64
	ldr	x19, .LC12
	mov	w1, 0
	ldr	x3, [x3, 96]
	mov	x0, x19
	blr	x3
	str	wzr, [x19, 64]
	ldr	x0, .LC13
	str	wzr, [x19, 72]
	str	wzr, [x0, 16]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L23:
	ldr	x2, .LC9
	mov	w3, 36
	ldr	x1, .LC10
	mov	w0, 1
	add	x2, x2, 24
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_Init, .-VDMDRV_Init
	.align	3
.LC9:
	.xword	.LANCHOR1
	.align	3
.LC10:
	.xword	.LC7
	.align	3
.LC11:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC12:
	.xword	.LANCHOR0
	.align	3
.LC13:
	.xword	g_VfmwGlobalStat
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_Reset
	.type	VDMDRV_Reset, %function
VDMDRV_Reset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L27
	ldr	x3, .LC16
	mov	x2, 64
	ldr	x0, .LC17
	mov	w1, 0
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L27:
	ldr	x2, .LC14
	mov	w3, 47
	ldr	x1, .LC15
	mov	w0, 1
	add	x2, x2, 40
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_Reset, .-VDMDRV_Reset
	.align	3
.LC14:
	.xword	.LANCHOR1
	.align	3
.LC15:
	.xword	.LC7
	.align	3
.LC16:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC17:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_SetPriority
	.type	VDMDRV_SetPriority, %function
VDMDRV_SetPriority:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L42
	ldr	x6, .LC22
	mov	w4, 0
	mov	w3, 0
	add	x5, x6, 208
	.p2align 2
.L37:
	mov	x0, 0
	mov	w2, 0
	.p2align 2
.L32:
	ldr	w1, [x19, x0, lsl 2]
	cmp	w1, w2
	ble	.L31
	mov	w3, w0
	mov	w2, w1
.L31:
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L32
	cmp	w2, wzr
	ble	.L43
	str	w3, [x5], 4
	add	w4, w4, 1
	str	wzr, [x19, w3, sxtw 2]
	cmp	w4, 32
	bne	.L37
.L28:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L43:
	cmp	w4, 31
	add	x1, x6, 80
	mov	w2, -1
	bgt	.L28
	.p2align 2
.L38:
	add	x0, x1, x4, sxtw 2
	add	w4, w4, 1
	cmp	w4, 32
	str	w2, [x0, 128]
	bne	.L38
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L42:
	ldr	x2, .LC20
	mov	w3, 61
	ldr	x1, .LC21
	mov	w0, 1
	add	x2, x2, 56
	bl	dprint_vfmw
	b	.L28
	.size	VDMDRV_SetPriority, .-VDMDRV_SetPriority
	.align	3
.LC20:
	.xword	.LANCHOR1
	.align	3
.LC21:
	.xword	.LC7
	.align	3
.LC22:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_AdjustPriorityAfterDec
	.type	VDMDRV_AdjustPriorityAfterDec, %function
VDMDRV_AdjustPriorityAfterDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x8, .LC23
	ldr	w0, [x8, 208]
	cmp	w19, w0
	beq	.L54
	add	x2, x8, 212
	mov	x0, 1
	b	.L50
	.p2align 3
.L46:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L54
.L50:
	ldr	w3, [x2]
	mov	w1, w0
	add	x2, x2, 4
	cmp	w3, w19
	bne	.L46
	cmp	w0, 30
	bgt	.L44
	add	x3, x0, 1
	lsl	x3, x3, 2
.L45:
	add	x2, x8, 208
	add	x7, x2, x3
	ldr	w3, [x2, x3]
	tbz	w3, #31, .L51
	b	.L44
	.p2align 3
.L53:
	add	x7, x2, x3, lsl 2
	ldr	w3, [x2, x3, lsl 2]
	tbnz	w3, #31, .L44
.L51:
	add	x4, x8, 80
	ldr	w5, [x2, x0, lsl 2]
	add	w1, w1, 1
	ldr	w6, [x4, w3, sxtw 2]
	ldr	w4, [x4, w5, sxtw 2]
	cmp	w6, w4
	blt	.L52
	str	w3, [x2, x0, lsl 2]
	str	w5, [x7]
.L52:
	cmp	w1, 30
	sxtw	x0, w1
	add	x3, x0, 1
	ble	.L53
.L44:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L54:
	mov	x3, 4
	mov	x0, 0
	mov	w1, 0
	b	.L45
	.size	VDMDRV_AdjustPriorityAfterDec, .-VDMDRV_AdjustPriorityAfterDec
	.align	3
.LC23:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_PrepareSleep
	.type	VDMDRV_PrepareSleep, %function
VDMDRV_PrepareSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L62
	ldr	x1, .LC28
	ldr	w0, [x1, 64]
	cbnz	w0, .L61
	ldr	w0, [x1]
	cbz	w0, .L63
	mov	w2, 1
	mov	w0, 0
	str	w2, [x1, 64]
.L59:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L63:
	mov	w2, 2
	str	w2, [x1, 64]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L61:
	mov	w0, -1
	b	.L59
	.p2align 3
.L62:
	ldr	x2, .LC26
	mov	w3, 134
	ldr	x1, .LC27
	mov	w0, 1
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w0, -1
	b	.L59
	.size	VDMDRV_PrepareSleep, .-VDMDRV_PrepareSleep
	.align	3
.LC26:
	.xword	.LANCHOR1
	.align	3
.LC27:
	.xword	.LC7
	.align	3
.LC28:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_GetSleepStage
	.type	VDMDRV_GetSleepStage, %function
VDMDRV_GetSleepStage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L67
	ldr	x0, .LC31
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 64]
	ret
	.p2align 3
.L67:
	ldr	x2, .LC29
	mov	w3, 159
	ldr	x1, .LC30
	mov	w0, 1
	add	x2, x2, 104
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_GetSleepStage, .-VDMDRV_GetSleepStage
	.align	3
.LC29:
	.xword	.LANCHOR1
	.align	3
.LC30:
	.xword	.LC7
	.align	3
.LC31:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ForceSleep
	.type	VDMDRV_ForceSleep, %function
VDMDRV_ForceSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L75
	ldr	x19, .LC34
	ldr	w0, [x19, 64]
	cmp	w0, 2
	beq	.L71
	mov	w0, 0
	bl	VDMDRV_Reset
	mov	w0, 2
	str	w0, [x19, 64]
.L71:
	ldr	x1, .LC36
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L75:
	ldr	x2, .LC32
	mov	w3, 165
	ldr	x1, .LC33
	mov	w0, 1
	add	x2, x2, 128
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_ForceSleep, .-VDMDRV_ForceSleep
	.align	3
.LC32:
	.xword	.LANCHOR1
	.align	3
.LC33:
	.xword	.LC7
	.align	3
.LC34:
	.xword	.LANCHOR0
	.align	3
.LC36:
	.xword	.LC35
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ExitSleep
	.type	VDMDRV_ExitSleep, %function
VDMDRV_ExitSleep:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L79
	ldr	x0, .LC39
	str	wzr, [x0, 64]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L79:
	ldr	x2, .LC37
	mov	w3, 179
	ldr	x1, .LC38
	mov	w0, 1
	add	x2, x2, 152
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_ExitSleep, .-VDMDRV_ExitSleep
	.align	3
.LC37:
	.xword	.LANCHOR1
	.align	3
.LC38:
	.xword	.LC7
	.align	3
.LC39:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_StartRepair
	.type	VDMDRV_StartRepair, %function
VDMDRV_StartRepair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	bl	_mcount
	mov	w0, 8
	bl	VCTRL_RecordPosTime
	ldr	x0, .LC40
	ldr	x3, [x0, 232]
	cbz	x3, .L81
	mov	x1, x21
	mov	w0, w19
	sbfiz	x19, x19, 6, 32
	blr	x3
	ldr	x0, .LC43
	str	w20, [x0, x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L81:
	ldr	x1, .LC42
	mov	w2, 187
	mov	w0, 0
	sbfiz	x19, x19, 6, 32
	bl	dprint_vfmw
	ldr	x0, .LC43
	str	w20, [x0, x19]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMDRV_StartRepair, .-VDMDRV_StartRepair
	.align	3
.LC40:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC42:
	.xword	.LC41
	.align	3
.LC43:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_StartDec
	.type	VDMDRV_StartDec, %function
VDMDRV_StartDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	mov	w0, 8
	bl	VCTRL_RecordPosTime
	ldr	x0, .LC44
	ldr	x2, [x0, 240]
	cbz	x2, .L84
	mov	x1, x20
	mov	w0, w19
	sbfiz	x19, x19, 6, 32
	blr	x2
	ldr	x0, .LC46
	mov	w1, 1
	str	w1, [x0, x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L84:
	ldr	x1, .LC45
	mov	w2, 195
	mov	w0, 0
	sbfiz	x19, x19, 6, 32
	bl	dprint_vfmw
	ldr	x0, .LC46
	mov	w1, 1
	str	w1, [x0, x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_StartDec, .-VDMDRV_StartDec
	.align	3
.LC44:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC45:
	.xword	.LC41
	.align	3
.LC46:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsChanDec
	.type	VDMDRV_IsChanDec, %function
VDMDRV_IsChanDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L89
	ldr	x0, .LC49
	add	x19, x0, x19, sxtw 2
	ldr	w0, [x19, 336]
	cmp	w0, wzr
	cset	w0, ne
.L88:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L89:
	ldr	x2, .LC47
	mov	w3, 202
	ldr	x1, .LC48
	mov	w0, 1
	add	x2, x2, 176
	bl	dprint_vfmw
	mov	w0, -1
	b	.L88
	.size	VDMDRV_IsChanDec, .-VDMDRV_IsChanDec
	.align	3
.LC47:
	.xword	.LANCHOR1
	.align	3
.LC48:
	.xword	.LC7
	.align	3
.LC49:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_SetChanIsDec
	.type	VDMDRV_SetChanIsDec, %function
VDMDRV_SetChanIsDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L94
	cbnz	w20, .L95
	ldr	x2, .LC52
	mov	w0, w19
	mov	w1, 1
	add	x19, x2, x19, sxtw 2
	str	w1, [x19, 336]
	bl	VDMDRV_AdjustPriorityAfterDec
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L95:
	ldr	x2, .LC50
	mov	w3, 216
	ldr	x1, .LC51
	mov	w0, 1
	add	x2, x2, 200
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L94:
	ldr	x2, .LC50
	mov	w3, 215
	ldr	x1, .LC51
	mov	w0, 1
	add	x2, x2, 200
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_SetChanIsDec, .-VDMDRV_SetChanIsDec
	.align	3
.LC50:
	.xword	.LANCHOR1
	.align	3
.LC51:
	.xword	.LC7
	.align	3
.LC52:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ClearChanIsDec
	.type	VDMDRV_ClearChanIsDec, %function
VDMDRV_ClearChanIsDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L99
	ldr	x0, .LC53
	add	x19, x0, x19, sxtw 2
	str	wzr, [x19, 336]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L99:
	bl	VDMDRV_ClearChanIsDec.part.4
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_ClearChanIsDec, .-VDMDRV_ClearChanIsDec
	.align	3
.LC53:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ParamInit
	.type	VDMDRV_ParamInit, %function
VDMDRV_ParamInit:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC56
	mov	w3, 1
	add	x2, x0, 256
	.p2align 2
.L102:
	ldr	x1, [x0]
	add	x0, x0, 8
	cmp	x0, x2
	cbz	x1, .L101
	str	w3, [x1, 16]
.L101:
	bne	.L102
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMDRV_ParamInit, .-VDMDRV_ParamInit
	.align	3
.LC56:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ChnDecReady
	.type	VDMDRV_ChnDecReady, %function
VDMDRV_ChnDecReady:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	w19, w1
	mov	x21, x2
	bl	_mcount
	mov	w0, w19
	bl	VCTRL_IsChanActive
	mov	w20, w0
	cbnz	w0, .L116
	cmp	w19, 31
	bhi	.L117
	ldr	x0, .LC62
	add	x0, x0, x19, sxtw 2
	ldr	w0, [x0, 336]
	cbnz	w0, .L118
.L111:
	mov	w0, w19
	str	xzr, [x21]
	bl	VCTRL_GetDecParam
	str	x0, [x21]
	cbz	x0, .L119
	mov	w1, w22
	mov	w0, 1
	bl	VDH_TaskInUse
	cmp	w0, 1
	mov	w2, w0
	beq	.L120
.L109:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L117:
	ldr	x2, .LC58
	mov	w3, 202
	ldr	x1, .LC61
	mov	w0, 1
	add	x2, x2, 176
	bl	dprint_vfmw
	b	.L111
	.p2align 3
.L116:
	ldr	x2, .LC58
	mov	w3, w19
	ldr	x1, .LC60
	mov	w0, 22
	add	x2, x2, 224
	mov	w20, 1
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L118:
	ldr	x1, .LC64
	mov	w2, w19
	mov	w0, 22
	mov	w20, 1
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L120:
	ldr	x1, .LC68
	mov	w0, 22
	mov	w20, w2
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L119:
	ldr	x1, .LC66
	mov	w2, w19
	mov	w0, 22
	mov	w20, 1
	bl	dprint_vfmw
	b	.L109
	.size	VDMDRV_ChnDecReady, .-VDMDRV_ChnDecReady
	.align	3
.LC58:
	.xword	.LANCHOR1
	.align	3
.LC60:
	.xword	.LC59
	.align	3
.LC61:
	.xword	.LC7
	.align	3
.LC62:
	.xword	.LANCHOR0
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
	.global	PostPro_CopyYuvByProtocol
	.type	PostPro_CopyYuvByProtocol, %function
PostPro_CopyYuvByProtocol:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	mov	w19, w3
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	sub	w3, w19, #1
	cmp	w3, 11
	bls	.L128
.L127:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L128:
	ldr	x0, .LC69
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx124
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx124:
	.section	.rodata
	.align	0
	.align	2
.L124:
	.byte	(.L123 - .Lrtx124) / 4
	.byte	(.L125 - .Lrtx124) / 4
	.byte	(.L127 - .Lrtx124) / 4
	.byte	(.L127 - .Lrtx124) / 4
	.byte	(.L127 - .Lrtx124) / 4
	.byte	(.L127 - .Lrtx124) / 4
	.byte	(.L127 - .Lrtx124) / 4
	.byte	(.L127 - .Lrtx124) / 4
	.byte	(.L127 - .Lrtx124) / 4
	.byte	(.L126 - .Lrtx124) / 4
	.byte	(.L126 - .Lrtx124) / 4
	.byte	(.L126 - .Lrtx124) / 4
	.text
	.p2align 3
.L126:
	ldr	x0, [x22]
	mov	x2, x21
	mov	w1, w20
	bl	PostPro_CopyYuv_Vp6
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L125:
	ldr	x0, [x22]
	mov	x2, x21
	mov	w1, w20
	bl	PostPro_CopyYuv_Mpeg4
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L123:
	ldr	x0, [x22]
	mov	x2, x21
	mov	w1, w20
	bl	PostPro_CopyYuv_Vc1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PostPro_CopyYuvByProtocol, .-PostPro_CopyYuvByProtocol
	.align	3
.LC69:
	.xword	.L124
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_GetMb0QpInCurrPic
	.type	VDMDRV_GetMb0QpInCurrPic, %function
VDMDRV_GetMb0QpInCurrPic:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC70
	lsl	x1, x0, 2
	ldr	x19, [sp, 16]
	sub	x0, x1, x0
	lsl	x1, x0, 4
	sub	x0, x1, x0
	ldp	x29, x30, [sp], 32
	add	x0, x2, x0, lsl 2
	ldr	w0, [x0, 472]
	and	w0, w0, 31
	ret
	.size	VDMDRV_GetMb0QpInCurrPic, .-VDMDRV_GetMb0QpInCurrPic
	.align	3
.LC70:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_GetSwitchRounding
	.type	VDMDRV_GetSwitchRounding, %function
VDMDRV_GetSwitchRounding:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC71
	lsl	x1, x0, 2
	ldr	x19, [sp, 16]
	sub	x0, x1, x0
	lsl	x1, x0, 4
	sub	x0, x1, x0
	ldp	x29, x30, [sp], 32
	add	x0, x2, x0, lsl 2
	ldr	w0, [x0, 476]
	and	w0, w0, 1
	ret
	.size	VDMDRV_GetSwitchRounding, .-VDMDRV_GetSwitchRounding
	.align	3
.LC71:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_MMUIntServeProc
	.type	VDMDRV_MMUIntServeProc, %function
VDMDRV_MMUIntServeProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L153
	ldr	x20, .LC74
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	ldr	x19, .LC75
	ldr	x2, [x19, 208]
	cbz	x2, .L139
	mov	w1, 0
	mov	w0, 5
	blr	x2
	mov	w23, w0
	ldr	x2, [x19, 208]
	cbz	x2, .L139
	mov	w1, 0
	mov	w0, 6
	and	w22, w23, 7
	mov	w21, 0
	blr	x2
	mov	w24, w0
	ldr	x2, [x19, 208]
	cbz	x2, .L134
	mov	w1, 0
	mov	w0, 7
	blr	x2
	mov	w21, w0
.L134:
	cbz	w22, .L139
	cbnz	w24, .L154
	cbnz	w21, .L155
	.p2align 2
.L139:
	ldr	x1, [x19, 184]
	cbz	x1, .L140
	mov	w0, 0
	blr	x1
.L141:
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L153:
	ldr	x2, .LC72
	mov	w3, 756
	ldr	x1, .LC73
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L155:
	ldr	x1, .LC79
	mov	w3, w21
	mov	w2, w23
	mov	w0, 32
	bl	dprint_vfmw
	b	.L139
	.p2align 3
.L154:
	ldr	x1, .LC77
	mov	w3, w24
	mov	w2, w23
	mov	w0, 32
	bl	dprint_vfmw
	cbz	w21, .L139
	b	.L155
	.p2align 3
.L140:
	ldr	x1, .LC80
	mov	w2, 793
	mov	w0, 0
	bl	dprint_vfmw
	b	.L141
	.size	VDMDRV_MMUIntServeProc, .-VDMDRV_MMUIntServeProc
	.align	3
.LC72:
	.xword	.LANCHOR2
	.align	3
.LC73:
	.xword	.LC7
	.align	3
.LC74:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC75:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC79:
	.xword	.LC78
	.align	3
.LC80:
	.xword	.LC41
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_SetStateIdle
	.type	VDMDRV_SetStateIdle, %function
VDMDRV_SetStateIdle:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L159
	ldr	x0, .LC83
	str	wzr, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L159:
	ldr	x2, .LC81
	mov	w3, 801
	ldr	x1, .LC82
	mov	w0, 1
	add	x2, x2, 24
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMDRV_SetStateIdle, .-VDMDRV_SetStateIdle
	.align	3
.LC81:
	.xword	.LANCHOR2
	.align	3
.LC82:
	.xword	.LC7
	.align	3
.LC83:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_WaitVdmReadyIfNoIsr
	.type	VDMDRV_WaitVdmReadyIfNoIsr, %function
VDMDRV_WaitVdmReadyIfNoIsr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L171
	ldr	x20, .LC86
	mov	w19, 0
	b	.L164
	.p2align 3
.L166:
	add	w19, w19, 1
	cmp	w19, 400
	beq	.L165
.L164:
	ldr	x1, [x20, 256]
	mov	w0, 0
	cbz	x1, .L166
	blr	x1
	cbz	w0, .L166
.L165:
	cmp	w19, 399
	cset	w0, hi
.L162:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L171:
	ldr	x2, .LC84
	mov	w3, 811
	ldr	x1, .LC85
	mov	w0, 1
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L162
	.size	VDMDRV_WaitVdmReadyIfNoIsr, .-VDMDRV_WaitVdmReadyIfNoIsr
	.align	3
.LC84:
	.xword	.LANCHOR2
	.align	3
.LC85:
	.xword	.LC7
	.align	3
.LC86:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_AvsFirstFldNeedRepair
	.type	VDMDRV_AvsFirstFldNeedRepair, %function
VDMDRV_AvsFirstFldNeedRepair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	sxtw	x20, w2
	bl	_mcount
	cmp	w19, 6
	mov	w0, 0
	beq	.L176
.L173:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L176:
	ldrb	w1, [x21, 17]
	mov	w0, 0
	cmp	w1, 1
	bne	.L173
	lsl	x0, x20, 3
	ldr	x1, .LC87
	sub	x0, x0, x20
	lsl	x0, x0, 3
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x20, x0, x20
	add	x20, x1, x20, lsl 3
	ldr	w0, [x20, 692]
	cmp	w0, wzr
	cset	w0, gt
	b	.L173
	.size	VDMDRV_AvsFirstFldNeedRepair, .-VDMDRV_AvsFirstFldNeedRepair
	.align	3
.LC87:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_AvsSecondFldNeedRepair
	.type	VDMDRV_AvsSecondFldNeedRepair, %function
VDMDRV_AvsSecondFldNeedRepair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	sxtw	x20, w2
	bl	_mcount
	cmp	w19, 6
	mov	w0, 0
	beq	.L181
.L178:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L181:
	ldrb	w1, [x21, 17]
	mov	w0, 0
	cmp	w1, 1
	bne	.L178
	lsl	x0, x20, 3
	ldr	x1, .LC88
	sub	x0, x0, x20
	lsl	x0, x0, 3
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x20, x0, x20
	add	x20, x1, x20, lsl 3
	ldr	w0, [x20, 1568]
	cmp	w0, wzr
	cset	w0, gt
	b	.L178
	.size	VDMDRV_AvsSecondFldNeedRepair, .-VDMDRV_AvsSecondFldNeedRepair
	.align	3
.LC88:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsCopy
	.type	VDMDRV_IsCopy, %function
VDMDRV_IsCopy:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L190
	sub	w0, w19, #1
	cmp	w0, 11
	bls	.L191
.L189:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L191:
	ldr	x1, .LC91
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx186
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx186:
	.section	.rodata
	.align	0
	.align	2
.L186:
	.byte	(.L188 - .Lrtx186) / 4
	.byte	(.L187 - .Lrtx186) / 4
	.byte	(.L189 - .Lrtx186) / 4
	.byte	(.L189 - .Lrtx186) / 4
	.byte	(.L189 - .Lrtx186) / 4
	.byte	(.L189 - .Lrtx186) / 4
	.byte	(.L189 - .Lrtx186) / 4
	.byte	(.L189 - .Lrtx186) / 4
	.byte	(.L189 - .Lrtx186) / 4
	.byte	(.L188 - .Lrtx186) / 4
	.byte	(.L188 - .Lrtx186) / 4
	.byte	(.L188 - .Lrtx186) / 4
	.text
	.p2align 3
.L188:
	ldrb	w0, [x20, 1]
	cmp	w0, 1
	cset	w0, eq
.L184:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L187:
	ldrb	w0, [x20, 166]
	ldp	x19, x20, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L190:
	ldr	x1, .LC90
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L184
	.size	VDMDRV_IsCopy, .-VDMDRV_IsCopy
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC91:
	.xword	.L186
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_DoBeforeDec
	.type	VDMDRV_DoBeforeDec, %function
VDMDRV_DoBeforeDec:
	stp	x29, x30, [sp, -304]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w24, w0
	mov	x0, x30
	mov	w22, w1
	mov	x20, x2
	bl	_mcount
	mov	x26, 0
	ldr	x0, .LC92
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L193
	ldr	x3, .LC93
	add	x0, x29, 112
	mov	x2, 188
	mov	w1, 0
	mov	x26, x0
	ldr	x3, [x3, 96]
	blr	x3
.L193:
	ldr	x0, [x20]
	cbz	x0, .L216
	mov	w0, w22
	sxtw	x23, w24
	bl	VCTRL_GetVidStd
	ldr	x21, .LC96
	ldr	x1, .LC97
	add	x25, x21, x23, lsl 6
	ldr	x1, [x1]
	str	w0, [x25, 12]
	cbz	x1, .L196
	ldr	x2, [x20]
	stp	w22, w0, [x29, 96]
	str	x2, [x29, 104]
	add	x0, x29, 96
	blr	x1
	cmp	w0, 1
	mov	w19, w0
	beq	.L195
	ldr	w0, [x25, 12]
.L196:
	ldr	x1, [x20]
	add	x25, x21, x23, lsl 6
	add	x27, x25, 4
	bl	VDMDRV_IsCopy
	mov	w19, w0
	cbz	w0, .L198
	ldr	w3, [x25, 12]
	mov	x2, x26
	mov	x0, x20
	mov	w1, w24
	bl	PostPro_CopyYuvByProtocol
	mov	w19, w0
	cbz	w0, .L217
	mov	w19, 0
.L195:
	mov	w0, w19
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L198:
	ldr	w0, [x25, 12]
	ldr	x1, [x20]
	bl	VCTRL_IsSedOnlyMode
	uxtb	w0, w0
	cbz	w0, .L218
	mov	w0, 1
	str	w0, [x25, 56]
.L200:
	ldr	x0, .LC100
	ldr	x4, [x0, 248]
	cbz	x4, .L204
	add	x25, x21, x23, lsl 6
	ldr	x1, [x20]
	mov	x3, x26
	mov	w2, w24
	ldr	w0, [x25, 12]
	blr	x4
	cbz	w0, .L219
.L204:
	ldr	x1, .LC102
	mov	w0, 0
	add	x23, x21, x23, lsl 6
	bl	dprint_vfmw
	mov	x2, x27
	mov	w1, 2
	mov	w0, w24
	bl	VDMDRV_AdjustErrRatio
	ldr	w1, [x23, 4]
	mov	w3, w24
	mov	x2, 0
	mov	w0, w22
	bl	VCTRL_VdmPostProc
	mov	w0, w24
	bl	VDMDRV_Reset
	cmp	w22, 31
	bhi	.L220
	add	x21, x21, x22, sxtw 2
	mov	w0, w19
	str	wzr, [x21, 336]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L218:
	str	wzr, [x25, 56]
	b	.L200
	.p2align 3
.L217:
	mov	w0, w24
	mov	x2, x27
	mov	w1, 0
	bl	VDMDRV_AdjustErrRatio
	mov	x2, x26
	mov	w1, w24
	mov	w0, 2
	bl	VDMDRV_StartRepair
	ldr	x0, .LC93
	ldr	x0, [x0]
	blr	x0
	mov	w2, w0
	lsl	x0, x23, 4
	ldr	x3, .LC98
	sub	x23, x0, x23
	mov	w1, w24
	mov	w0, w22
	str	w2, [x25, 20]
	add	x23, x3, x23, lsl 2
	str	w2, [x23, 4]
	bl	VDMDRV_SetChanIsDec
	ldr	x3, .LC99
	add	x2, x21, 2400
	add	x2, x2, x22, sxtw 2
	mov	w0, w22
	mov	w4, 401
	add	x3, x3, 80
	mov	w1, 7
	bl	RecordPOS
	ldr	x27, [sp, 80]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L216:
	ldr	x1, .LC95
	mov	w2, w22
	mov	w0, 22
	mov	w19, 1
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 304
	ret
	.p2align 3
.L219:
	mov	x1, x26
	mov	w0, w24
	mov	w19, 0
	bl	VDMDRV_StartDec
	ldr	x0, .LC93
	ldr	x0, [x0]
	blr	x0
	mov	w2, w0
	lsl	x0, x23, 4
	ldr	x3, .LC98
	sub	x23, x0, x23
	mov	w1, w24
	mov	w0, w22
	str	w2, [x25, 20]
	add	x23, x3, x23, lsl 2
	str	w2, [x23, 4]
	bl	VDMDRV_SetChanIsDec
	ldr	x3, .LC99
	add	x2, x21, 2400
	mov	w4, 434
	add	x2, x2, x22, sxtw 2
	add	x3, x3, 80
	mov	w1, 5
	mov	w0, w22
	bl	RecordPOS
	b	.L195
	.p2align 3
.L220:
	bl	VDMDRV_ClearChanIsDec.part.4
	b	.L195
	.size	VDMDRV_DoBeforeDec, .-VDMDRV_DoBeforeDec
	.align	3
.LC92:
	.xword	g_HalDisable
	.align	3
.LC93:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC96:
	.xword	.LANCHOR0
	.align	3
.LC97:
	.xword	AcceleratorCharacter
	.align	3
.LC98:
	.xword	g_VfmwGlobalStat
	.align	3
.LC99:
	.xword	.LANCHOR2
	.align	3
.LC100:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC102:
	.xword	.LC101
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ActivateVDH
	.type	VDMDRV_ActivateVDH, %function
VDMDRV_ActivateVDH:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w22, w0
	mov	x0, x30
	sbfiz	x20, x22, 6, 32
	bl	_mcount
	ldr	x25, .LC105
	ldr	x24, .LC104
	mov	w0, 5
	add	x21, x20, 48
	ldr	x1, [x25, 24]
	add	x21, x24, x21
	blr	x1
	ldr	w0, [x24, 208]
	tbnz	w0, #31, .L222
	add	x19, x24, 212
	add	x23, x24, 336
	add	x20, x24, x20
	b	.L223
	.p2align 3
.L226:
	cmp	x19, x23
	beq	.L222
	ldr	w0, [x19], 4
	tbnz	w0, #31, .L222
.L223:
	mov	w1, w0
	str	w0, [x20, 8]
	mov	x2, x21
	mov	w0, w22
	bl	VDMDRV_ChnDecReady
	cbnz	w0, .L226
	ldr	w1, [x20, 8]
	mov	x2, x21
	mov	w0, w22
	bl	VDMDRV_DoBeforeDec
	cbnz	w0, .L226
.L222:
	ldr	x1, [x25, 32]
	mov	w0, 5
	blr	x1
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDMDRV_ActivateVDH, .-VDMDRV_ActivateVDH
	.align	3
.LC104:
	.xword	.LANCHOR0
	.align	3
.LC105:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_AfterDec
	.type	VDMDRV_AfterDec, %function
VDMDRV_AfterDec:
	stp	x29, x30, [sp, -448]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w22, w0
	mov	x0, x30
	uxtb	w23, w1
	bl	_mcount
	ldr	x19, .LC107
	mov	x2, 160
	mov	w1, 0
	add	x0, x29, 96
	ldr	x3, [x19, 96]
	blr	x3
	ldr	x0, .LC108
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L229
	add	x20, x29, 256
	ldr	x3, [x19, 96]
	mov	x2, 188
	mov	w1, 0
	mov	x0, x20
	blr	x3
	str	x20, [x29, 240]
.L229:
	ldr	x3, [x19, 96]
	add	x24, x29, 100
	mov	w1, 0
	mov	x2, 136
	mov	x0, x24
	sxtw	x21, w22
	blr	x3
	ldr	x20, .LC109
	lsl	x0, x21, 6
	ldr	x25, .LC110
	add	x19, x20, x0
	strb	w23, [x29, 248]
	ldr	w3, [x20, x0]
	ldr	w0, [x19, 8]
	cmp	w3, 2
	ldr	x1, [x25, w0, sxtw 3]
	ldr	w1, [x1, 1312]
	str	w1, [x29, 96]
	beq	.L231
	cmp	w3, 3
	beq	.L232
	cmp	w3, 1
	beq	.L276
	ldr	x1, .LC118
	mov	w2, w0
	mov	w4, w23
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 8]
	cmp	w0, 31
	bhi	.L277
	add	x20, x20, x0, sxtw 2
	str	wzr, [x20, 336]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 448
	ret
	.p2align 3
.L276:
	ldr	w24, [x19, 28]
	add	x23, x19, 4
	cmp	w24, 1
	beq	.L278
	mov	w1, 3
	mov	x2, x23
	mov	w0, w22
	bl	VDMDRV_AdjustErrRatio
	ldr	w1, [x19, 4]
	cbz	w1, .L235
	ldr	x0, .LC113
	ldr	x4, [x0]
	cbz	x4, .L235
	ldr	w0, [x19, 8]
	mov	w3, 4
	str	w1, [x29, 88]
	add	x2, x29, 88
	mov	w1, 114
	blr	x4
.L235:
	ldr	w0, [x29, 96]
	cmp	w0, 1
	beq	.L279
.L236:
	add	x19, x20, x21, lsl 6
	ldr	w0, [x19, 8]
	ldr	x1, [x25, w0, sxtw 3]
	add	x1, x1, 507904
	ldrsb	w1, [x1, 1680]
	cbnz	w1, .L280
	ldr	w1, [x19, 4]
.L254:
	ldr	w2, [x29, 96]
	cmp	w2, 1
	bne	.L239
	add	x21, x20, x21, lsl 6
	mov	w3, w22
	ldr	w2, [x21, 44]
	cmp	w2, 2
	add	x2, x29, 100
	beq	.L281
.L240:
	bl	VCTRL_VdmPostProc
	ldr	w0, [x21, 8]
	bl	VCTRL_ClearDecparam
	ldr	w0, [x21, 8]
	cmp	w0, 31
	bhi	.L244
.L242:
	add	x20, x20, x0, sxtw 2
	str	wzr, [x20, 336]
.L243:
	mov	w0, w22
	bl	VDMDRV_Reset
	mov	w0, w22
	bl	VDMDRV_ActivateVDH
.L228:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 448
	ret
	.p2align 3
.L232:
	ldr	w1, [x19, 4]
	mov	w3, w22
	mov	x2, x24
	str	wzr, [x19, 28]
	bl	VCTRL_VdmPostProc
	ldr	w0, [x19, 8]
	bl	VCTRL_ClearDecparam
	ldr	w0, [x19, 8]
	cmp	w0, 31
	bls	.L242
.L244:
	bl	VDMDRV_ClearChanIsDec.part.4
	b	.L243
	.p2align 3
.L231:
	ldr	w0, [x19, 12]
	add	x23, x19, 4
	str	wzr, [x19, 28]
	cmp	w0, 6
	ldr	x1, [x19, 48]
	beq	.L282
.L249:
	bl	VDMDRV_IsCopy
	cbz	w0, .L283
	mov	x2, x23
	mov	w1, 0
	mov	w0, w22
	add	x21, x20, x21, lsl 6
	bl	VDMDRV_AdjustErrRatio
	mov	w3, w22
	add	x2, x29, 100
	ldp	w1, w0, [x21, 4]
	b	.L240
	.p2align 3
.L283:
	add	x21, x20, x21, lsl 6
	mov	w3, w22
	add	x2, x29, 100
	ldp	w1, w0, [x21, 4]
	b	.L240
	.p2align 3
.L278:
	ldr	x1, [x19, 48]
	mov	w2, w22
	ldr	w0, [x19, 12]
	bl	PostPro_SetFullRepair
	mov	x2, x23
	mov	w1, w24
	mov	w0, w22
	bl	VDMDRV_AdjustErrRatio
	str	wzr, [x19, 28]
	ldrb	w2, [x29, 248]
	mov	w0, 0
	ldr	x1, .LC112
	bl	dprint_vfmw
	b	.L235
	.p2align 3
.L282:
	ldrb	w2, [x1, 17]
	cmp	w2, 1
	bne	.L249
	lsl	x3, x21, 3
	sub	x3, x3, x21
	lsl	x3, x3, 3
	sub	x3, x3, x21
	lsl	x3, x3, 2
	sub	x3, x3, x21
	add	x3, x20, x3, lsl 3
	ldr	w3, [x3, 1568]
	cmp	w3, wzr
	ble	.L249
	ldr	x3, .LC114
	ldr	x5, [x3, 272]
	cbz	x5, .L246
	ldr	x4, [x29, 240]
	mov	w3, w22
	blr	x5
	cbnz	w0, .L246
	ldr	x2, [x29, 240]
	mov	w1, w22
	mov	w0, 3
	bl	VDMDRV_StartRepair
	lsl	x2, x21, 4
	ldr	x3, .LC115
	sub	x21, x2, x21
	ldr	x2, .LC116
	ldr	w0, [x19, 8]
	mov	w4, 995
	add	x2, x2, x21, lsl 2
	add	x3, x3, 136
	add	x2, x2, 4
	mov	w1, 7
	bl	RecordPOS
	b	.L228
	.p2align 3
.L277:
	bl	VDMDRV_ClearChanIsDec.part.4
	b	.L228
	.p2align 3
.L239:
	mov	w3, w22
	add	x2, x29, 100
	add	x21, x20, x21, lsl 6
	b	.L240
	.p2align 3
.L280:
	ldr	x1, [x19, 48]
	ldr	w0, [x19, 12]
	bl	PostPro_GetRepairStratage
	ldr	w1, [x19, 4]
	cmp	w1, wzr
	cset	w2, eq
	cmp	w0, 1
	cset	w0, eq
	orr	w2, w2, w0
	cbnz	w2, .L284
	ldr	w0, [x19, 12]
	ldr	x1, [x19, 48]
	mov	w19, 2
	cmp	w0, 6
	beq	.L285
.L245:
	ldr	x3, .LC114
	ldr	x5, [x3, 272]
	cbz	x5, .L246
	ldr	x4, [x29, 240]
	mov	w3, w22
	blr	x5
	cbz	w0, .L286
.L246:
	add	x19, x20, x21, lsl 6
	mov	x2, x23
	mov	w1, 2
	mov	w0, w22
	bl	VDMDRV_AdjustErrRatio
	ldp	w1, w0, [x19, 4]
	mov	w3, w22
	add	x2, x29, 100
	bl	VCTRL_VdmPostProc
	ldr	w0, [x19, 8]
	bl	VCTRL_ClearDecparam
	ldr	w0, [x19, 8]
	cmp	w0, 31
	bhi	.L287
	add	x0, x20, x0, sxtw 2
	str	wzr, [x0, 336]
.L248:
	lsl	x21, x21, 6
	str	wzr, [x20, x21]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 448
	ret
	.p2align 3
.L287:
	bl	VDMDRV_ClearChanIsDec.part.4
	b	.L248
	.p2align 3
.L279:
	mov	x2, x23
	mov	w1, 0
	mov	w0, w22
	bl	VDMDRV_AdjustErrRatio
	b	.L236
	.p2align 3
.L285:
	ldrb	w3, [x1, 17]
	cmp	w3, 1
	bne	.L245
	lsl	x2, x21, 3
	sub	x2, x2, x21
	lsl	x2, x2, 3
	sub	x2, x2, x21
	lsl	x2, x2, 2
	sub	x2, x2, x21
	add	x2, x20, x2, lsl 3
	ldr	w3, [x2, 1568]
	cmp	w3, wzr
	mov	w3, 3
	cset	w2, gt
	csel	w19, w19, w3, le
	b	.L245
	.p2align 3
.L286:
	ldr	x2, [x29, 240]
	mov	w1, w22
	mov	w0, w19
	add	x20, x20, x21, lsl 6
	bl	VDMDRV_StartRepair
	lsl	x2, x21, 4
	ldr	x3, .LC115
	sub	x21, x2, x21
	ldr	x2, .LC116
	ldr	w0, [x20, 8]
	mov	w4, 964
	add	x2, x2, x21, lsl 2
	mov	w1, 7
	add	x3, x3, 104
	add	x2, x2, 4
	bl	RecordPOS
	b	.L228
	.p2align 3
.L281:
	bl	VCTRL_VdmPostProc
	b	.L228
.L284:
	ldr	w0, [x19, 8]
	b	.L254
	.size	VDMDRV_AfterDec, .-VDMDRV_AfterDec
	.align	3
.LC107:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC108:
	.xword	g_HalDisable
	.align	3
.LC109:
	.xword	.LANCHOR0
	.align	3
.LC110:
	.xword	s_pstVfmwChan
	.align	3
.LC112:
	.xword	.LC111
	.align	3
.LC113:
	.xword	g_event_report
	.align	3
.LC114:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC115:
	.xword	.LANCHOR2
	.align	3
.LC116:
	.xword	g_VfmwGlobalStat
	.align	3
.LC118:
	.xword	.LC117
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_CheckDevice
	.type	VDMDRV_CheckDevice, %function
VDMDRV_CheckDevice:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	sxtw	x19, w0
	mov	x0, x30
	mov	x21, x19
	bl	_mcount
	ldr	x20, .LC119
	lsl	x0, x19, 6
	add	x22, x20, x0
	ldr	w0, [x20, x0]
	cbnz	w0, .L307
	add	x19, x20, x19, lsl 2
	mov	w0, 0
	ldr	w1, [x19, 64]
	cbz	w1, .L304
	cmp	w1, 1
	beq	.L308
.L292:
	mov	w0, 1
.L304:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L307:
	ldr	x0, .LC120
	ldr	x0, [x0]
	blr	x0
	str	w0, [x22, 24]
	ldr	w1, [x22, 20]
	cmp	w0, w1
	bcc	.L290
	sub	w3, w0, w1
	cmp	w3, wzr
	ccmp	w1, wzr, 4, ge
	beq	.L290
	cmp	w3, 1000
	bls	.L292
	ldr	x1, .LC122
	mov	w0, 1
	ldr	w2, [x22, 8]
	bl	dprint_vfmw
	ldr	x0, .LC123
	ldr	x4, [x0]
	cbz	x4, .L293
	ldr	w0, [x22, 8]
	mov	w3, 0
	mov	x2, 0
	mov	w1, 101
	blr	x4
.L293:
	ldr	x0, .LC124
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L294
	mov	w1, w21
	mov	w0, 1
	bl	VDH_Reset_Module
.L295:
	add	x0, x20, x19, lsl 6
	mov	w2, 1
	ldr	w1, [x0, 36]
	str	w2, [x0, 28]
	cmp	w1, w2
	bne	.L297
	str	wzr, [x0, 36]
.L298:
	lsl	x19, x19, 6
	add	x0, x20, x19
	str	wzr, [x20, x19]
	ldr	w19, [x0, 8]
	str	wzr, [x0, 28]
	cmp	w19, 31
	bhi	.L309
	add	x19, x20, x19, sxtw 2
	mov	w0, 0
	str	wzr, [x19, 336]
	b	.L304
	.p2align 3
.L290:
	str	w0, [x22, 20]
	mov	w0, 1
	b	.L304
	.p2align 3
.L308:
	mov	w2, 2
	str	w2, [x19, 64]
	mov	w0, w1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L297:
	mov	w1, 0
	mov	w0, w21
	bl	VDMDRV_AfterDec
	b	.L298
	.p2align 3
.L294:
	ldr	x0, .LC125
	ldr	x1, [x0, 152]
	cbz	x1, .L296
	mov	w0, w21
	blr	x1
	b	.L295
.L296:
	ldr	x1, .LC126
	mov	w2, 1117
	mov	w0, 0
	bl	dprint_vfmw
	b	.L295
	.p2align 3
.L309:
	bl	VDMDRV_ClearChanIsDec.part.4
	mov	w0, 0
	b	.L304
	.size	VDMDRV_CheckDevice, .-VDMDRV_CheckDevice
	.align	3
.LC119:
	.xword	.LANCHOR0
	.align	3
.LC120:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC122:
	.xword	.LC121
	.align	3
.LC123:
	.xword	g_event_report
	.align	3
.LC124:
	.xword	g_HalDisable
	.align	3
.LC125:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC126:
	.xword	.LC41
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_WakeUpVdm
	.type	VDMDRV_WakeUpVdm, %function
VDMDRV_WakeUpVdm:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	VDMDRV_CheckDevice
	cbz	w0, .L312
	ldp	x29, x30, [sp], 16
	ret
	.p2align 3
.L312:
	bl	VDMDRV_ActivateVDH
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMDRV_WakeUpVdm, .-VDMDRV_WakeUpVdm
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_IsrProcess
	.type	VDMDRV_IsrProcess, %function
VDMDRV_IsrProcess:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	ble	.L314
	ldr	x2, .LC127
	mov	w3, w19
	ldr	x1, .LC129
	mov	w4, 0
	add	x2, x2, 168
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L314:
	mov	w0, 9
	sxtw	x20, w19
	bl	VCTRL_RecordPosTime
	ldr	x23, .LC130
	mov	w0, 0
	ldr	x1, [x23, 24]
	blr	x1
	ldr	x21, .LC131
	add	x0, x21, x20, lsl 6
	ldr	w0, [x0, 8]
	tbnz	w0, #31, .L363
	ldr	x1, .LC132
	ldr	x0, [x1, w0, sxtw 3]
	cbz	x0, .L363
	ldr	x22, .LC133
	ldr	w25, [x0, 1312]
	ldr	x2, [x22, 312]
	cbz	x2, .L364
.L406:
	mov	w1, w19
	mov	w0, 2
	blr	x2
	mov	w24, w0
	ldr	x2, [x22, 312]
	cbz	x2, .L365
	mov	w1, w19
	mov	w0, 1
	mov	w27, 0
	blr	x2
	mov	w26, w0
	ldr	x2, [x22, 312]
	cbz	x2, .L317
	mov	w1, w19
	mov	w0, 3
	blr	x2
	mov	w27, w0
.L317:
	ldr	x2, [x22, 320]
	cbz	x2, .L318
	mov	w1, w19
	mov	w0, 2
	blr	x2
	cmp	w24, 1
	beq	.L319
	cmp	w25, 1
	ccmp	w0, 1, 0, eq
	bne	.L361
.L319:
	add	x0, x21, x20, lsl 6
	ldr	w0, [x0, 8]
	tbnz	w0, #31, .L331
	ldr	x1, .LC132
	ldr	x0, [x1, w0, sxtw 3]
	cbz	x0, .L331
	ldr	x2, [x22, 320]
	ldr	w24, [x0, 1312]
	cbz	x2, .L367
	mov	w1, w19
	mov	w0, 1
	blr	x2
	mov	w25, w0
.L329:
	ldr	x2, [x22, 312]
	cbz	x2, .L330
	mov	w1, w19
	mov	w0, 1
	blr	x2
	cmp	w24, 1
	beq	.L399
.L331:
	mov	w24, 1
.L328:
	ldr	x1, [x22, 288]
	cbz	x1, .L335
	mov	w0, w19
	blr	x1
.L336:
	ldr	x1, [x22, 176]
	cbz	x1, .L337
	mov	w0, w19
	blr	x1
.L338:
	add	x0, x21, x20, lsl 6
	ldr	x3, .LC127
	add	x2, x21, 2528
	mov	w4, 1193
	mov	w1, 6
	add	x3, x3, 192
	ldr	w0, [x0, 8]
	add	x2, x2, x0, sxtw 2
	bl	RecordPOS
	ldr	x0, [x23]
	blr	x0
	lsl	x1, x20, 4
	ldr	x4, .LC136
	sub	x1, x1, x20
	lsl	x1, x1, 2
	add	x5, x4, x1
	ldr	w2, [x5, 4]
	cbz	w2, .L340
	ldr	w6, [x4, x1]
	add	w3, w6, 49152
	add	w3, w3, 848
	cmp	w2, w3
	bhi	.L341
	ldr	w3, [x5, 8]
.L342:
	sub	w2, w0, w2
	lsl	x5, x20, 2
	add	w2, w2, w3
	sub	x3, x5, x20
	lsl	x5, x3, 4
	lsl	x1, x20, 4
	sub	x5, x5, x3
	sub	x1, x1, x20
	sub	w0, w0, w6
	add	x5, x21, x5, lsl 2
	add	x1, x4, x1, lsl 2
	cmp	w0, 999
	ldr	w6, [x5, 488]
	ldp	w7, w3, [x1, 28]
	stp	wzr, w2, [x1, 4]
	add	w7, w7, 1
	add	w6, w3, w6, lsr 10
	stp	w7, w6, [x1, 28]
	bls	.L340
	add	x3, x21, x20, lsl 6
	ldr	w5, [x3, 16]
	cbnz	w5, .L344
	ldr	w5, [x1, 12]
.L345:
	lsl	w1, w5, 6
	sub	w1, w1, w5
	lsl	w1, w1, 1
	sub	w5, w1, w5
	lsl	w1, w2, 6
	sub	w3, w1, w2
	lsl	x1, x20, 4
	lsl	w3, w3, 1
	sub	x1, x1, x20
	sub	w3, w3, w2
	lsl	w2, w7, 6
	lsl	x1, x1, 2
	sub	w2, w2, w7
	lsl	w2, w2, 1
	lsl	w5, w5, 3
	sub	w2, w2, w7
	lsl	w3, w3, 3
	lsl	w2, w2, 3
	str	wzr, [x4, x1]
	udiv	w5, w5, w0
	add	x1, x4, x1
	stp	wzr, w6, [x1, 32]
	str	w0, [x1, 40]
	udiv	w3, w3, w0
	stp	w3, w5, [x1, 16]
	udiv	w2, w2, w0
	stp	w2, wzr, [x1, 24]
.L340:
	lsl	x0, x20, 6
	add	x22, x21, x0
	ldr	w1, [x22, 36]
	ldr	w25, [x22, 8]
	cmp	w1, 1
	beq	.L400
	ldr	w1, [x22, 56]
	cmp	w1, 1
	beq	.L401
	ldr	w2, [x21, x0]
	cbz	w2, .L349
	ldr	x0, [x22, 48]
	cbz	x0, .L402
.L349:
	mov	w0, w25
	bl	VCTRL_IsChanActive
	cbnz	w0, .L403
	mov	w0, w25
	bl	VCTRL_GetDecParam
	cbz	x0, .L404
	mov	w1, 1
	mov	w0, w19
	bl	VDMDRV_AfterDec
.L358:
	add	x0, x21, x20, lsl 6
	ldr	w0, [x0, 8]
	bl	VCTRL_InformVdmFree
	cmp	w24, 1
	beq	.L405
.L353:
	ldr	x1, [x23, 32]
	mov	w0, 0
	blr	x1
	lsl	x0, x20, 2
	sub	x20, x0, x20
	mov	w0, 1
	lsl	x1, x20, 4
	sub	x20, x1, x20
	add	x21, x21, x20, lsl 2
	ldr	w1, [x21, 488]
	bl	VCTRL_RecordData
	mov	w0, 10
	bl	VCTRL_RecordPosTime
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L318:
	cmp	w24, 1
	beq	.L319
.L361:
	cbnz	w24, .L355
	cmp	w26, 1
	ccmp	w27, 1, 0, eq
	beq	.L355
	ldr	x1, [x22, 264]
	cbz	x1, .L324
	mov	w0, w19
	blr	x1
	cbnz	w0, .L355
.L324:
	ldr	x2, [x22, 312]
	cbz	x2, .L323
	mov	w1, w19
	mov	w0, 1
	blr	x2
	cbnz	w0, .L355
.L323:
	lsl	x0, x20, 6
	str	wzr, [x21, x0]
.L355:
	add	x20, x21, x20, lsl 6
	ldr	w0, [x20, 8]
	bl	VCTRL_InformVdmFree
	ldr	x0, .LC134
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L326
	mov	w1, w19
	mov	w0, 1
	bl	VDH_Notify_ModuleIdle
.L326:
	ldr	x1, [x23, 32]
	mov	w0, 0
	blr	x1
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L363:
	ldr	x22, .LC133
	mov	w25, 0
	ldr	x2, [x22, 312]
	cbnz	x2, .L406
.L364:
	mov	w26, 0
	mov	w24, 0
	mov	w27, 0
	b	.L317
	.p2align 3
.L403:
	ldr	x1, .LC142
	mov	w3, w25
	mov	w2, 737
	mov	w0, 0
	bl	dprint_vfmw
.L347:
	add	x0, x21, x20, lsl 6
	ldr	w0, [x0, 8]
	cmp	w0, 31
	bhi	.L407
	add	x0, x21, x0, sxtw 2
	str	wzr, [x0, 336]
.L352:
	lsl	x0, x20, 6
	str	wzr, [x21, x0]
	b	.L358
	.p2align 3
.L341:
	str	w2, [x4, x1]
	mov	w6, w2
	mov	w3, 0
	b	.L342
	.p2align 3
.L399:
	cmp	w0, 1
	cset	w2, eq
	cmp	w25, 1
	cset	w1, eq
	tst	w2, w1
	beq	.L332
.L334:
	add	x0, x21, x20, lsl 6
	mov	w1, 1
	mov	w24, w1
	str	w1, [x0, 44]
	b	.L328
	.p2align 3
.L344:
	udiv	w5, w6, w5
	str	w5, [x1, 12]
	b	.L345
	.p2align 3
.L367:
	mov	w25, 0
	b	.L329
	.p2align 3
.L330:
	cmp	w24, 1
	bne	.L331
	cmp	w25, 1
	bne	.L331
.L356:
	add	x0, x21, x20, lsl 6
	mov	w1, 2
	mov	w24, 0
	str	w1, [x0, 44]
	b	.L328
	.p2align 3
.L407:
	bl	VDMDRV_ClearChanIsDec.part.4
	b	.L352
	.p2align 3
.L337:
	ldr	x1, .LC135
	mov	w2, 1191
	mov	w0, 0
	bl	dprint_vfmw
	b	.L338
	.p2align 3
.L335:
	ldr	x1, .LC135
	mov	w2, 1189
	mov	w0, 0
	bl	dprint_vfmw
	b	.L336
	.p2align 3
.L405:
	ldr	x0, .LC134
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L353
	mov	w1, w19
	mov	w0, w24
	bl	VDH_Notify_ModuleIdle
	b	.L353
	.p2align 3
.L400:
	ldr	x1, .LC138
	mov	w2, 709
	mov	w0, 0
	bl	dprint_vfmw
	str	wzr, [x22, 36]
	b	.L347
	.p2align 3
.L332:
	cmp	w0, wzr
	cset	w0, eq
	tst	w1, w0
	bne	.L356
	cmp	w25, wzr
	cset	w0, eq
	tst	w2, w0
	beq	.L331
	add	x0, x21, x20, lsl 6
	ldr	w1, [x0, 44]
	cmp	w1, 2
	bne	.L334
	mov	w1, 3
	str	w1, [x0, 44]
	b	.L328
	.p2align 3
.L401:
	mov	w1, w19
	mov	w0, w25
	bl	VCTRL_VdmProcSedOnly
	b	.L347
.L404:
	ldr	x1, .LC144
	mov	w3, w25
	mov	w2, 743
	bl	dprint_vfmw
	b	.L347
.L402:
	ldr	x1, .LC140
	bl	dprint_vfmw
	mov	w0, w25
	bl	VCTRL_GetDecParam
	cbz	x0, .L347
	mov	w3, w19
	mov	x2, 0
	mov	w1, 100
	mov	w0, w25
	bl	VCTRL_VdmPostProc
	b	.L347
.L365:
	mov	w26, 0
	mov	w27, 0
	b	.L317
	.size	VDMDRV_IsrProcess, .-VDMDRV_IsrProcess
	.align	3
.LC127:
	.xword	.LANCHOR2
	.align	3
.LC129:
	.xword	.LC128
	.align	3
.LC130:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC131:
	.xword	.LANCHOR0
	.align	3
.LC132:
	.xword	s_pstVfmwChan
	.align	3
.LC133:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC134:
	.xword	g_HalDisable
	.align	3
.LC135:
	.xword	.LC41
	.align	3
.LC136:
	.xword	g_VfmwGlobalStat
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
.LC144:
	.xword	.LC143
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMDRV_ResetVDH
	.type	VDMDRV_ResetVDH, %function
VDMDRV_ResetVDH:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L409
	ldr	x20, .LC146
	ldr	w0, [x20, 8]
	cmp	w19, w0
	beq	.L416
.L408:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L409:
	ldr	x2, .LC147
	mov	w3, 1272
	ldr	x1, .LC148
	mov	w0, 1
	add	x2, x2, 216
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L416:
	ldr	x0, .LC149
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L412
	mov	w1, 0
	mov	w0, 1
	bl	VDH_Reset_Module
	str	wzr, [x20]
	b	.L408
	.p2align 3
.L412:
	ldr	x0, .LC150
	ldr	x1, [x0, 152]
	cbz	x1, .L414
	mov	w0, 0
	blr	x1
	str	wzr, [x20]
	b	.L408
.L414:
	ldr	x1, .LC151
	mov	w2, 1286
	mov	w0, 0
	bl	dprint_vfmw
	str	wzr, [x20]
	b	.L408
	.size	VDMDRV_ResetVDH, .-VDMDRV_ResetVDH
	.align	3
.LC146:
	.xword	.LANCHOR0
	.align	3
.LC147:
	.xword	.LANCHOR2
	.align	3
.LC148:
	.xword	.LC7
	.align	3
.LC149:
	.xword	g_HalDisable
	.align	3
.LC150:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC151:
	.xword	.LC41
	.global	g_VdmExtParam
	.global	g_DspDrvState
	.global	g_VdmDrvParam
	.global	USE_FF_APT_EN
	.global	g_ChanCtx
	.global	g_BackUp
	.global	g_DecReport
	.global	g_RepairParam
	.global	g_HwMem
	.global	g_UpMsg
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.11536, %object
	.size	__func__.11536, 22
__func__.11536:
	.string	"VDMDRV_ClearChanIsDec"
	.zero	2
	.type	__func__.11460, %object
	.size	__func__.11460, 12
__func__.11460:
	.string	"VDMDRV_Init"
	.zero	4
	.type	__func__.11464, %object
	.size	__func__.11464, 13
__func__.11464:
	.string	"VDMDRV_Reset"
	.zero	3
	.type	__func__.11474, %object
	.size	__func__.11474, 19
__func__.11474:
	.string	"VDMDRV_SetPriority"
	.zero	5
	.type	__func__.11502, %object
	.size	__func__.11502, 20
__func__.11502:
	.string	"VDMDRV_PrepareSleep"
	.zero	4
	.type	__func__.11506, %object
	.size	__func__.11506, 21
__func__.11506:
	.string	"VDMDRV_GetSleepStage"
	.zero	3
	.type	__func__.11510, %object
	.size	__func__.11510, 18
__func__.11510:
	.string	"VDMDRV_ForceSleep"
	.zero	6
	.type	__func__.11514, %object
	.size	__func__.11514, 17
__func__.11514:
	.string	"VDMDRV_ExitSleep"
	.zero	7
	.type	__func__.11527, %object
	.size	__func__.11527, 17
__func__.11527:
	.string	"VDMDRV_IsChanDec"
	.zero	7
	.type	__func__.11532, %object
	.size	__func__.11532, 20
__func__.11532:
	.string	"VDMDRV_SetChanIsDec"
	.zero	4
	.type	__func__.11550, %object
	.size	__func__.11550, 19
__func__.11550:
	.string	"VDMDRV_ChnDecReady"
	.align	3
.LANCHOR2 = . + 0
	.type	__func__.11665, %object
	.size	__func__.11665, 23
__func__.11665:
	.string	"VDMDRV_MMUIntServeProc"
	.zero	1
	.type	__func__.11669, %object
	.size	__func__.11669, 20
__func__.11669:
	.string	"VDMDRV_SetStateIdle"
	.zero	4
	.type	__func__.11674, %object
	.size	__func__.11674, 27
__func__.11674:
	.string	"VDMDRV_WaitVdmReadyIfNoIsr"
	.zero	5
	.type	__FUNCTION__.11591, %object
	.size	__FUNCTION__.11591, 19
__FUNCTION__.11591:
	.string	"VDMDRV_DoBeforeDec"
	.zero	5
	.type	__FUNCTION__.11706, %object
	.size	__FUNCTION__.11706, 29
__FUNCTION__.11706:
	.string	"VDMDRV_AfterDecProcessNormal"
	.zero	3
	.type	__FUNCTION__.11718, %object
	.size	__FUNCTION__.11718, 29
__FUNCTION__.11718:
	.string	"VDMDRV_AfterDecProcessRepair"
	.zero	3
	.type	__func__.11756, %object
	.size	__func__.11756, 18
__func__.11756:
	.string	"VDMDRV_IsrProcess"
	.zero	6
	.type	__FUNCTION__.11757, %object
	.size	__FUNCTION__.11757, 18
__FUNCTION__.11757:
	.string	"VDMDRV_IsrProcess"
	.zero	6
	.type	__func__.11780, %object
	.size	__func__.11780, 16
__func__.11780:
	.string	"VDMDRV_ResetVDH"
	.data
	.align	2
	.type	USE_FF_APT_EN, %object
	.size	USE_FF_APT_EN, 4
USE_FF_APT_EN:
	.word	1
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"Chan %d: CorrectType = %d ErrRatio = %d \n" )
	.zero	6
.LC4:
	ASCII(.string	"Chan %d: Current frame:%d  ErrRatio = %d\n" )
	.zero	6
.LC7:
	ASCII(.string	"[%s %d]assert warning\n" )
	.zero	1
.LC35:
	ASCII(.string	"====== forece VDM sleep! ======\n" )
	.zero	7
.LC41:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC59:
	ASCII(.string	"%s The channel %d is not active\n" )
	.zero	7
.LC63:
	ASCII(.string	"The channel %d is decoding\n" )
	.zero	4
.LC65:
	ASCII(.string	"The channel %d DEC PARAM is not ready\n" )
	.zero	1
.LC67:
	ASCII(.string	"some task is already wait to process!!!!\n" )
	.zero	6
.LC76:
	ASCII(.string	"SMMU_READ_ERR  MODULE : VFMW \t SMMU INT STATE: 0x%x \t read_err_addr  = 0x%x\n" )
	.zero	3
.LC78:
	ASCII(.string	"SMMU_WRITE_ERR MODULE : VFMW \t SMMU INT STATE: 0x%x \t write_err_addr = 0x%x\n" )
	.zero	3
.LC89:
	ASCII(.string	"VDMDRV_IsProtocolCopy point of picture para null, wait forever!!!\n" )
	.zero	5
.LC94:
	ASCII(.string	"The channel %d DEC PARAM is not ready(pDecParam == NULL)\n" )
	.zero	6
.LC101:
	ASCII(.string	"VDM Start Fail 2 !\n" )
	.zero	4
.LC111:
	ASCII(.string	"ISR process vdm timeout! FromInt = %d\n" )
	.zero	1
.LC117:
	ASCII(.string	"Chan %d VdmStateMachine=%d Error! FromInt = %d.\n" )
	.zero	7
.LC121:
	ASCII(.string	"Chan %d VDM Time Out(%d ms), Reset VDM!\n" )
	.zero	7
.LC128:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC137:
	ASCII(.string	"Line %d, ISR called, ChanResetFlag = 1!!\n" )
	.zero	6
.LC139:
	ASCII(.string	"vdm state machine = %d, but DecParam is null!\n" )
	.zero	1
.LC141:
	ASCII(.string	"line :%d ISR called but chan %d is not active!\n" )
.LC143:
	ASCII(.string	"line :%d ISR called chan %d is active! But Dec Param in CTX is NULL!!!\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_VdmDrvParam, %object
	.size	g_VdmDrvParam, 64
g_VdmDrvParam:
	.zero	64
	.type	s_eVdmDrvSleepState, %object
	.size	s_eVdmDrvSleepState, 4
s_eVdmDrvSleepState:
	.zero	4
	.zero	4
	.type	g_DspDrvState, %object
	.size	g_DspDrvState, 8
g_DspDrvState:
	.zero	8
	.type	g_ChanCtx, %object
	.size	g_ChanCtx, 384
g_ChanCtx:
	.zero	384
	.type	g_BackUp, %object
	.size	g_BackUp, 180
g_BackUp:
	.zero	180
	.zero	4
	.type	g_RepairParam, %object
	.size	g_RepairParam, 1752
g_RepairParam:
	.zero	1752
	.type	last_rec_pos_time.11588, %object
	.size	last_rec_pos_time.11588, 128
last_rec_pos_time.11588:
	.zero	128
	.type	LastRecPosTime.11753, %object
	.size	LastRecPosTime.11753, 128
LastRecPosTime.11753:
	.zero	128
	.type	g_VdmExtParam, %object
	.size	g_VdmExtParam, 268
g_VdmExtParam:
	.zero	268
	.zero	4
	.type	g_DecReport, %object
	.size	g_DecReport, 824
g_DecReport:
	.zero	824
	.type	g_HwMem, %object
	.size	g_HwMem, 1256
g_HwMem:
	.zero	1256
	.type	g_UpMsg, %object
	.size	g_UpMsg, 3200
g_UpMsg:
	.zero	3200
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
