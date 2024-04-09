#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vfmw_ctrl.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetPrintLevel, %function
VfmwProc_SetPrintLevel:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC0
	ldr	w1, [x19]
	str	w1, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetPrintLevel, .-VfmwProc_SetPrintLevel
	.align	3
.LC0:
	.xword	g_PrintEnable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_OpenScdLowdly, %function
VfmwProc_OpenScdLowdly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	mov	w1, 1
	ldr	x2, .LC1
	lsl	x0, x0, 4
	ldr	x0, [x2, x0]
	str	w1, [x0, 48]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_OpenScdLowdly, .-VfmwProc_OpenScdLowdly
	.align	3
.LC1:
	.xword	s_SmIIS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_CloseScdLowdly, %function
VfmwProc_CloseScdLowdly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x1, .LC2
	lsl	x0, x0, 4
	ldr	x0, [x1, x0]
	str	wzr, [x0, 48]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_CloseScdLowdly, .-VfmwProc_CloseScdLowdly
	.align	3
.LC2:
	.xword	s_SmIIS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_EventReport
	.type	VCTRL_EventReport, %function
VCTRL_EventReport:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	cmp	w19, 31
	bhi	.L16
	ldr	x4, .LC8
	ldr	x0, [x4, w19, sxtw 3]
	cbz	x0, .L17
	ldr	w3, [x0, 32]
	cbz	w3, .L9
	cmp	w3, 1
	bne	.L18
	ldr	x3, [x4, 576]
	cbz	x3, .L19
.L12:
	mov	x2, x21
	mov	w1, w20
	mov	w0, w19
	blr	x3
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L18:
	ldr	x2, .LC5
	mov	w4, w22
	ldr	x1, .LC16
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L6:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L9:
	ldr	x3, [x4, 568]
	cbnz	x3, .L12
	ldr	x1, .LC12
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L6
	.p2align 3
.L16:
	ldr	x4, .LC4
	mov	w3, 872
	ldr	x2, .LC5
	mov	w0, 0
	ldr	x1, .LC7
	bl	dprint_vfmw
	mov	w0, -1
	b	.L6
.L17:
	ldr	x4, .LC10
	mov	w3, 873
	ldr	x2, .LC5
	ldr	x1, .LC7
	bl	dprint_vfmw
	mov	w0, -1
	b	.L6
.L19:
	ldr	x1, .LC14
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L6
	.size	VCTRL_EventReport, .-VCTRL_EventReport
	.align	3
.LC4:
	.xword	.LC3
	.align	3
.LC5:
	.xword	.LANCHOR0
	.align	3
.LC7:
	.xword	.LC6
	.align	3
.LC8:
	.xword	.LANCHOR1
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
.LC16:
	.xword	.LC15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetStandardObedience, %function
VfmwProc_SetStandardObedience:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC17
	ldr	x1, .LC19
	mov	w2, w3
	str	w3, [x4, 600]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetStandardObedience, .-VfmwProc_SetStandardObedience
	.align	3
.LC17:
	.xword	.LANCHOR1
	.align	3
.LC19:
	.xword	.LC18
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetClkSelect, %function
VfmwProc_SetClkSelect:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 4
	bhi	.L22
	ldr	x0, .LC20
	str	w3, [x0]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L22:
	ldr	x2, .LC20
	mov	w0, 32
	ldr	x1, .LC22
	ldr	w2, [x2]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetClkSelect, .-VfmwProc_SetClkSelect
	.align	3
.LC20:
	.xword	.LANCHOR2
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetCompressPara, %function
VfmwProc_SetCompressPara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC23
	mov	x2, 16
	ldp	w20, w21, [x19]
	mov	w1, 0
	add	x0, x29, 64
	ldr	x3, [x3, 96]
	ldp	w23, w22, [x19, 8]
	ldr	w19, [x19, 16]
	blr	x3
	cbz	w21, .L76
	cbz	w23, .L77
	mov	w0, 1
	cmp	w22, 625
	stp	w0, w0, [x29, 64]
	beq	.L71
	bls	.L78
	cmp	w22, 750
	beq	.L32
	cmp	w22, 875
	bne	.L34
	mov	w0, 3
	str	w0, [x29, 72]
.L34:
	cmp	w19, 625
	beq	.L36
	bls	.L79
	cmp	w19, 750
	beq	.L39
	cmp	w19, 875
	bne	.L35
	mov	w0, 3
	str	w0, [x29, 76]
.L35:
	mov	w4, 1
	ldr	x1, .LC29
	mov	w6, w19
	mov	w5, w22
	mov	w3, w4
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	b	.L26
	.p2align 3
.L76:
	ldr	x1, .LC25
	mov	w3, -1
	mov	w2, w20
	mov	w0, 32
	stp	wzr, wzr, [x29, 64]
	stp	w3, w3, [x29, 72]
	bl	dprint_vfmw
.L26:
	ldr	x0, .LC30
	sxtw	x2, w20
	ldr	x1, [x0, w20, sxtw 3]
	cbz	x1, .L80
.L42:
	ldr	x1, .LC40
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L77:
	mov	w6, 1
	ldr	x1, .LC27
	mov	w2, w20
	mov	w5, -1
	mov	w4, 0
	mov	w3, w6
	mov	w0, 32
	stp	w6, wzr, [x29, 64]
	stp	w5, w5, [x29, 72]
	bl	dprint_vfmw
	ldr	x0, .LC30
	sxtw	x2, w20
	ldr	x1, [x0, w20, sxtw 3]
	cbnz	x1, .L42
.L80:
	lsl	x4, x2, 4
	add	x3, x0, 608
	add	x0, x3, x4
	ldr	w5, [x29, 76]
	ldp	w7, w6, [x29, 68]
	ldr	x1, .LC32
	mov	w2, w20
	str	w5, [x0, 12]
	ldr	w5, [x29, 64]
	stp	w7, w6, [x0, 4]
	str	w5, [x3, x4]
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w2, [x29, 64]
	mov	w0, 32
	ldr	x1, .LC34
	bl	dprint_vfmw
	ldr	w2, [x29, 68]
	mov	w0, 32
	ldr	x1, .LC36
	bl	dprint_vfmw
	ldp	w2, w3, [x29, 72]
	ldr	x1, .LC38
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L78:
	cmp	w22, 500
	bne	.L34
	str	wzr, [x29, 72]
	b	.L34
	.p2align 3
.L32:
	mov	w0, 2
.L71:
	str	w0, [x29, 72]
	b	.L34
	.p2align 3
.L79:
	cmp	w19, 500
	bne	.L35
	str	wzr, [x29, 76]
	b	.L35
	.p2align 3
.L39:
	mov	w0, 2
	str	w0, [x29, 76]
	b	.L35
	.p2align 3
.L36:
	mov	w0, 1
	str	w0, [x29, 76]
	b	.L35
	.size	VfmwProc_SetCompressPara, .-VfmwProc_SetCompressPara
	.align	3
.LC23:
	.xword	vfmw_Osal_Func_Ptr_S
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
.LC30:
	.xword	.LANCHOR1
	.align	3
.LC32:
	.xword	.LC31
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC36:
	.xword	.LC35
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC40:
	.xword	.LC39
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTunnelLineNumber, %function
VfmwProc_SetTunnelLineNumber:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC42
	ldr	x1, .LC44
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTunnelLineNumber, .-VfmwProc_SetTunnelLineNumber
	.align	3
.LC42:
	.xword	g_TunnelLineNumber
	.align	3
.LC44:
	.xword	.LC43
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSaveYuvBitWidth, %function
VfmwProc_SetSaveYuvBitWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	and	w0, w3, -3
	cmp	w0, 8
	bne	.L85
	ldr	x4, .LC47
	mov	w2, w3
	ldr	x1, .LC49
	mov	w0, 32
	str	w3, [x4, 4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L85:
	ldr	x1, .LC46
	mov	w2, w3
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSaveYuvBitWidth, .-VfmwProc_SetSaveYuvBitWidth
	.align	3
.LC46:
	.xword	.LC45
	.align	3
.LC47:
	.xword	.LANCHOR2
	.align	3
.LC49:
	.xword	.LC48
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTraceImgPeriod, %function
VfmwProc_SetTraceImgPeriod:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC50
	ldr	x1, .LC52
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTraceImgPeriod, .-VfmwProc_SetTraceImgPeriod
	.align	3
.LC50:
	.xword	g_TraceImgPeriod
	.align	3
.LC52:
	.xword	.LC51
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTraceFramePeriod, %function
VfmwProc_SetTraceFramePeriod:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC53
	ldr	x1, .LC55
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTraceFramePeriod, .-VfmwProc_SetTraceFramePeriod
	.align	3
.LC53:
	.xword	g_TraceFramePeriod
	.align	3
.LC55:
	.xword	.LC54
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTraceBSPeriod, %function
VfmwProc_SetTraceBSPeriod:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC56
	ldr	x1, .LC58
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTraceBSPeriod, .-VfmwProc_SetTraceBSPeriod
	.align	3
.LC56:
	.xword	g_TraceBsPeriod
	.align	3
.LC58:
	.xword	.LC57
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetTraceCtrl, %function
VfmwProc_SetTraceCtrl:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC59
	ldr	x1, .LC61
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetTraceCtrl, .-VfmwProc_SetTraceCtrl
	.align	3
.LC59:
	.xword	g_TraceCtrl
	.align	3
.LC61:
	.xword	.LC60
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestStopDec, %function
VfmwProc_TestStopDec:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC62
	ldr	x1, .LC64
	mov	w2, w3
	str	w3, [x4, 1120]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStopDec, .-VfmwProc_TestStopDec
	.align	3
.LC62:
	.xword	.LANCHOR1
	.align	3
.LC64:
	.xword	.LC63
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestTimeSequence, %function
VfmwProc_TestTimeSequence:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC65
	ldr	x1, .LC67
	mov	w2, w3
	str	w3, [x4, 1124]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestTimeSequence, .-VfmwProc_TestTimeSequence
	.align	3
.LC65:
	.xword	.LANCHOR1
	.align	3
.LC67:
	.xword	.LC66
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveEL, %function
VfmwProc_SaveEL:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bhi	.L92
	ldr	x21, .LC68
	add	x20, x21, 1128
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L97
	ldr	x1, .LC78
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC69
	ldr	x0, [x20, w19, uxtw 3]
	ldr	x1, [x1, 72]
	blr	x1
	str	xzr, [x20, w19, uxtw 3]
.L92:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L97:
	ldr	x22, .LC69
	mov	x1, 50
	ldr	w0, [x21, 1384]
	ldr	x3, .LC70
	mov	w4, w0
	ldr	x2, .LC72
	add	w0, w0, 1
	ldr	x5, [x22, 136]
	add	x3, x3, 8
	str	w0, [x21, 1384]
	add	x0, x29, 56
	blr	x5
	ldr	x3, [x22, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 56
	blr	x3
	str	w19, [x21, 1388]
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L95
	ldr	x1, .LC74
	mov	w3, w19
	add	x2, x29, 56
	mov	w0, 32
	bl	dprint_vfmw
	b	.L92
	.p2align 3
.L95:
	ldr	x1, .LC76
	add	x2, x29, 56
	mov	w0, 32
	bl	dprint_vfmw
	b	.L92
	.size	VfmwProc_SaveEL, .-VfmwProc_SaveEL
	.align	3
.LC68:
	.xword	.LANCHOR1
	.align	3
.LC69:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC70:
	.xword	.LANCHOR2
	.align	3
.LC72:
	.xword	.LC71
	.align	3
.LC74:
	.xword	.LC73
	.align	3
.LC76:
	.xword	.LC75
	.align	3
.LC78:
	.xword	.LC77
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetCurProcChan, %function
VfmwProc_SetCurProcChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 32
	bhi	.L101
	ldr	x4, .LC82
	mov	w2, w3
	ldr	x1, .LC84
	mov	w0, 32
	str	w3, [x4, 1392]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L101:
	ldr	x1, .LC81
	mov	w2, w3
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetCurProcChan, .-VfmwProc_SetCurProcChan
	.align	3
.LC81:
	.xword	.LC80
	.align	3
.LC82:
	.xword	.LANCHOR1
	.align	3
.LC84:
	.xword	.LC83
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSaveFileAfterReset, %function
VfmwProc_SetSaveFileAfterReset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 1
	bls	.L105
	ldr	x1, .LC89
	mov	w2, w3
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L105:
	ldr	x4, .LC85
	mov	w2, w3
	ldr	x1, .LC87
	mov	w0, 32
	str	w3, [x4, 1396]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSaveFileAfterReset, .-VfmwProc_SetSaveFileAfterReset
	.align	3
.LC85:
	.xword	.LANCHOR1
	.align	3
.LC87:
	.xword	.LC86
	.align	3
.LC89:
	.xword	.LC88
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetUSE_FF_APT_EN, %function
VfmwProc_SetUSE_FF_APT_EN:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 1
	bls	.L109
	ldr	x1, .LC94
	mov	w2, w3
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L109:
	ldr	x4, .LC90
	mov	w2, w3
	ldr	x1, .LC92
	mov	w0, 32
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetUSE_FF_APT_EN, .-VfmwProc_SetUSE_FF_APT_EN
	.align	3
.LC90:
	.xword	USE_FF_APT_EN
	.align	3
.LC92:
	.xword	.LC91
	.align	3
.LC94:
	.xword	.LC93
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetVp9DecFrameNum, %function
VfmwProc_SetVp9DecFrameNum:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x4, .LC95
	ldr	x1, .LC97
	mov	w2, w3
	str	w3, [x4]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetVp9DecFrameNum, .-VfmwProc_SetVp9DecFrameNum
	.align	3
.LC95:
	.xword	g_CfgVp9FrmNum
	.align	3
.LC97:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetDefaultOutputOrder, %function
VfmwProc_SetDefaultOutputOrder:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 7
	bhi	.L114
	ldr	x1, .LC101
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x0, .LC102
	str	w19, [x0, 72]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L114:
	ldr	x1, .LC99
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetDefaultOutputOrder, .-VfmwProc_SetDefaultOutputOrder
	.align	3
.LC99:
	.xword	.LC98
	.align	3
.LC101:
	.xword	.LC100
	.align	3
.LC102:
	.xword	.LANCHOR2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Isr_0
	.type	VCTRL_Isr_0, %function
VCTRL_Isr_0:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	VDMDRV_IsrProcess
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Isr_0, .-VCTRL_Isr_0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Scd_Isr
	.type	VCTRL_Scd_Isr, %function
VCTRL_Scd_Isr:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	SM_SCDIntServeProc
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Scd_Isr, .-VCTRL_Scd_Isr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_MMU_ISR
	.type	VCTRL_MMU_ISR, %function
VCTRL_MMU_ISR:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	VDMDRV_MMUIntServeProc
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_MMU_ISR, .-VCTRL_MMU_ISR
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveReorderMetadata, %function
VfmwProc_SaveReorderMetadata:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bhi	.L118
	ldr	x21, .LC103
	add	x20, x21, 1400
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L123
	ldr	x1, .LC111
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC104
	ldr	x0, [x20, w19, uxtw 3]
	ldr	x1, [x1, 72]
	blr	x1
	str	xzr, [x20, w19, uxtw 3]
.L118:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L123:
	ldr	x22, .LC104
	mov	w0, 24
	ldr	x23, [x22, 136]
	bl	VFMW_GetString
	ldr	w1, [x21, 1656]
	mov	x2, x0
	ldr	x3, .LC105
	add	x0, x29, 72
	mov	w4, w1
	add	w1, w1, 1
	add	x3, x3, 8
	str	w1, [x21, 1656]
	mov	x1, 50
	blr	x23
	ldr	x3, [x22, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	str	w19, [x21, 1660]
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L121
	ldr	x1, .LC107
	mov	w3, w19
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L118
	.p2align 3
.L121:
	ldr	x1, .LC109
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L118
	.size	VfmwProc_SaveReorderMetadata, .-VfmwProc_SaveReorderMetadata
	.align	3
.LC103:
	.xword	.LANCHOR1
	.align	3
.LC104:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC105:
	.xword	.LANCHOR2
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC109:
	.xword	.LC108
	.align	3
.LC111:
	.xword	.LC110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveMetadata, %function
VfmwProc_SaveMetadata:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bls	.L130
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L130:
	ldr	x20, .LC113
	mov	w1, w19
	mov	w0, 2
	ldr	x2, [x20, 48]
	blr	x2
	ldr	x22, .LC114
	add	x21, x22, 1664
	ldr	x0, [x21, w19, uxtw 3]
	cbz	x0, .L131
	ldr	x1, .LC120
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x0, [x21, w19, uxtw 3]
	ldr	x1, [x20, 72]
	blr	x1
	str	xzr, [x21, w19, uxtw 3]
.L129:
	ldr	x2, [x20, 56]
	mov	w1, w19
	mov	w0, 2
	blr	x2
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L131:
	mov	w0, 23
	ldr	x23, [x20, 136]
	bl	VFMW_GetString
	mov	x2, x0
	ldr	w1, [x22, 1920]
	add	x0, x29, 72
	ldr	x3, .LC115
	mov	w4, w1
	add	w1, w1, 1
	add	x3, x3, 8
	str	w1, [x22, 1920]
	mov	x1, 50
	blr	x23
	ldr	x3, [x20, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	str	w19, [x22, 1924]
	str	x0, [x21, w19, uxtw 3]
	cbz	x0, .L127
	ldr	x1, .LC117
	mov	w3, w19
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L129
.L127:
	ldr	x1, .LC119
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L129
	.size	VfmwProc_SaveMetadata, .-VfmwProc_SaveMetadata
	.align	3
.LC113:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC114:
	.xword	.LANCHOR1
	.align	3
.LC115:
	.xword	.LANCHOR2
	.align	3
.LC117:
	.xword	.LC116
	.align	3
.LC119:
	.xword	.LC118
	.align	3
.LC120:
	.xword	.LC110
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_Save1DYUV, %function
VfmwProc_Save1DYUV:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC122
	ldp	w21, w23, [x20]
	ldr	w24, [x20, 8]
	ldr	x1, [x19, 424]
	mov	w0, w21
	blr	x1
	mov	x20, x0
	cbz	x0, .L138
	mov	w0, 22
	ldr	x22, [x19, 136]
	bl	VFMW_GetString
	mov	x2, x0
	ldr	x3, .LC125
	mov	w4, w21
	mov	x1, 50
	add	x0, x29, 72
	add	x3, x3, 8
	blr	x22
	ldr	x3, [x19, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	mov	x21, x0
	cbz	x0, .L135
	ldr	x1, .LC126
	ldr	x5, [x1, 296]
	cbz	x5, .L136
	mov	w4, 1
	mov	w3, w24
	mov	w2, w23
	mov	x1, x20
	blr	x5
.L137:
	ldr	x1, [x19, 72]
	mov	x0, x21
	blr	x1
	ldr	x1, .LC130
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
.L134:
	ldr	x1, [x19, 312]
	mov	x0, x20
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L136:
	ldr	x1, .LC128
	mov	w2, 6572
	mov	w0, 0
	bl	dprint_vfmw
	b	.L137
	.p2align 3
.L138:
	ldr	x1, .LC124
	mov	w2, w21
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, [x19, 312]
	mov	x0, x20
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L135:
	ldr	x1, .LC132
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L134
	.size	VfmwProc_Save1DYUV, .-VfmwProc_Save1DYUV
	.align	3
.LC122:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC124:
	.xword	.LC123
	.align	3
.LC125:
	.xword	.LANCHOR2
	.align	3
.LC126:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC128:
	.xword	.LC127
	.align	3
.LC130:
	.xword	.LC129
	.align	3
.LC132:
	.xword	.LC131
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SaveSeg, %function
VfmwProc_SaveSeg:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bhi	.L139
	ldr	x21, .LC133
	add	x20, x21, 1928
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L144
	ldr	x1, .LC141
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC134
	ldr	x0, [x20, w19, uxtw 3]
	ldr	x1, [x1, 72]
	blr	x1
	str	xzr, [x20, w19, uxtw 3]
.L139:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L144:
	ldr	x22, .LC134
	mov	w0, 19
	ldr	x23, [x22, 136]
	bl	VFMW_GetString
	ldr	w1, [x21, 2184]
	mov	x2, x0
	ldr	x3, .LC135
	add	x0, x29, 72
	mov	w4, w1
	add	w1, w1, 1
	add	x3, x3, 8
	str	w1, [x21, 2184]
	mov	x1, 50
	blr	x23
	ldr	x3, [x22, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	str	w19, [x21, 2188]
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L142
	ldr	x1, .LC137
	mov	w3, w19
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L139
	.p2align 3
.L142:
	ldr	x1, .LC139
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L139
	.size	VfmwProc_SaveSeg, .-VfmwProc_SaveSeg
	.align	3
.LC133:
	.xword	.LANCHOR1
	.align	3
.LC134:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC135:
	.xword	.LANCHOR2
	.align	3
.LC137:
	.xword	.LC136
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC141:
	.xword	.LC140
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_Savestream, %function
VfmwProc_Savestream:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	cmp	w19, 31
	bhi	.L145
	ldr	x21, .LC143
	add	x20, x21, 2192
	ldr	x0, [x20, w19, uxtw 3]
	cbz	x0, .L150
	ldr	x1, .LC151
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x1, .LC144
	ldr	x0, [x20, w19, uxtw 3]
	ldr	x1, [x1, 72]
	blr	x1
	str	xzr, [x20, w19, uxtw 3]
.L145:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L150:
	ldr	x22, .LC144
	mov	w0, 18
	ldr	x23, [x22, 136]
	bl	VFMW_GetString
	ldr	w1, [x21, 2448]
	mov	x2, x0
	ldr	x3, .LC145
	add	x0, x29, 72
	mov	w4, w1
	add	w1, w1, 1
	add	x3, x3, 8
	str	w1, [x21, 2448]
	mov	x1, 50
	blr	x23
	ldr	x3, [x22, 64]
	mov	w2, 0
	mov	w1, 66
	add	x0, x29, 72
	blr	x3
	str	w19, [x21, 2452]
	str	x0, [x20, w19, uxtw 3]
	cbz	x0, .L148
	ldr	x1, .LC147
	mov	w3, w19
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L145
	.p2align 3
.L148:
	ldr	x1, .LC149
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L145
	.size	VfmwProc_Savestream, .-VfmwProc_Savestream
	.align	3
.LC143:
	.xword	.LANCHOR1
	.align	3
.LC144:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC145:
	.xword	.LANCHOR2
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
	.type	VfmwProc_SaveYUV, %function
VfmwProc_SaveYUV:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w20, [x19]
	cmp	w20, 31
	bls	.L161
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L161:
	ldr	x21, .LC153
	mov	w1, w20
	mov	w0, 2
	ldr	x2, [x21, 48]
	blr	x2
	ldr	x19, .LC154
	add	x22, x19, 2456
	ldr	x0, [x22, w20, uxtw 3]
	cbz	x0, .L162
	ldr	x1, .LC163
	mov	w0, 32
	add	x23, x19, 2720
	bl	dprint_vfmw
	ldr	x0, [x22, w20, uxtw 3]
	ldr	x1, [x21, 72]
	blr	x1
	str	xzr, [x22, w20, uxtw 3]
	ldr	x1, .LC155
	mov	w2, -1
	ldr	w0, [x19, 2736]
	str	w2, [x1, 76]
	add	x1, x19, 2560
	stp	xzr, xzr, [x1, 192]
	stp	xzr, xzr, [x1, 208]
	str	xzr, [x19, 2784]
	str	xzr, [x19, 2792]
	str	wzr, [x19, 2800]
	str	xzr, [x19, 2808]
	cbnz	w0, .L163
.L157:
	ldr	x2, [x21, 56]
	mov	w1, w20
	mov	w0, 2
	blr	x2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L163:
	ldr	x1, [x19, 2728]
	bl	MEM_ReleaseMemBlock
	ldr	w2, [x19, 2744]
	ldr	x1, [x19, 2728]
	ldr	w0, [x19, 2736]
	bl	MEM_DelMemRecord
	ldr	x3, [x21, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x23
	blr	x3
	b	.L157
	.p2align 3
.L162:
	mov	w0, 20
	ldr	x23, [x21, 136]
	bl	VFMW_GetString
	ldr	x24, .LC155
	ldr	w1, [x19, 2712]
	mov	x2, x0
	add	x3, x24, 8
	add	x0, x29, 72
	mov	w4, w1
	add	w1, w1, 1
	str	w1, [x19, 2712]
	mov	x1, 100
	blr	x23
	ldr	x3, [x21, 64]
	mov	w2, 0
	mov	w1, 578
	add	x0, x29, 72
	blr	x3
	str	x0, [x22, w20, uxtw 3]
	cbz	x0, .L154
	add	x23, x19, 2720
	ldr	x3, [x21, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x23
	blr	x3
	mov	w1, 3
	mov	w0, 27
	str	w1, [x23, 28]
	bl	VFMW_GetString
	mov	w4, 0
	mov	x3, x23
	mov	w2, 47185920
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbz	w0, .L155
	ldr	x1, .LC157
	mov	w0, 1
	bl	dprint_vfmw
	ldr	x0, [x22, w20, uxtw 3]
	ldr	x1, [x21, 72]
	blr	x1
	str	xzr, [x22, w20, uxtw 3]
	add	x2, x19, 2560
	mov	w0, -1
	stp	xzr, xzr, [x2, 192]
	stp	xzr, xzr, [x2, 208]
	str	xzr, [x19, 2784]
	str	xzr, [x19, 2792]
	str	wzr, [x19, 2800]
	str	w0, [x24, 76]
	b	.L157
.L154:
	ldr	x1, .LC161
	add	x2, x29, 72
	mov	w0, 32
	bl	dprint_vfmw
	b	.L157
	.p2align 3
.L155:
	ldr	w2, [x23, 24]
	ldr	x1, [x23, 8]
	ldr	w0, [x23, 16]
	bl	MEM_AddMemRecord
	ldr	x5, [x23, 8]
	lsr	w1, w20, 24
	mov	x0, 23592960
	and	w7, w20, 3
	add	x6, x5, 9437184
	str	x6, [x19, 2760]
	mov	x6, 25952256
	add	x0, x5, x0
	add	x6, x5, x6
	str	x6, [x19, 2776]
	mov	x6, 28311552
	mov	w3, w1
	add	x6, x5, x6
	str	w1, [x24, 76]
	ldr	x1, .LC159
	mov	w4, w7
	str	x5, [x19, 2768]
	add	x2, x29, 72
	str	x0, [x19, 2784]
	mov	w0, 32
	str	x6, [x19, 2808]
	add	x6, x5, 11796480
	add	x5, x5, 14155776
	str	w7, [x19, 2800]
	str	x6, [x19, 2752]
	str	x5, [x19, 2792]
	bl	dprint_vfmw
	b	.L157
	.size	VfmwProc_SaveYUV, .-VfmwProc_SaveYUV
	.align	3
.LC153:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC154:
	.xword	.LANCHOR1
	.align	3
.LC155:
	.xword	.LANCHOR2
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
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetScdPrint, %function
VfmwProc_SetScdPrint:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC166
	ldr	w0, [x20]
	mov	w2, 67108864
	mov	w1, 1
	ldr	w20, [x19]
	str	w2, [x19]
	bl	PrintScdRawState
	str	w20, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetScdPrint, .-VfmwProc_SetScdPrint
	.align	3
.LC166:
	.xword	g_PrintEnable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_PrintTracer, %function
VfmwProc_PrintTracer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC168
	mov	w0, 32
	ldr	w19, [x19]
	bl	dprint_vfmw
	mov	w0, w19
	bl	DBG_PrintTracer
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_PrintTracer, .-VfmwProc_PrintTracer
	.align	3
.LC168:
	.xword	.LC167
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSegBypass, %function
VfmwProc_SetSegBypass:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x2, .LC169
	cbz	w0, .L169
	ldr	x1, .LC173
	mov	w3, 1
	mov	w0, 32
	str	w3, [x2, 80]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L169:
	ldr	x1, .LC171
	mov	w0, 32
	str	wzr, [x2, 80]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSegBypass, .-VfmwProc_SetSegBypass
	.align	3
.LC169:
	.xword	.LANCHOR2
	.align	3
.LC171:
	.xword	.LC170
	.align	3
.LC173:
	.xword	.LC172
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSmmuIrqEnable, %function
VfmwProc_SetSmmuIrqEnable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	cbnz	w0, .L170
	ldr	x19, .LC174
	ldr	w0, [x19, 84]
	cmp	w0, 1
	beq	.L173
	ldr	x1, .LC178
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x19, 84]
.L170:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L173:
	ldr	x1, .LC176
	mov	w0, 32
	bl	dprint_vfmw
	str	wzr, [x19, 84]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSmmuIrqEnable, .-VfmwProc_SetSmmuIrqEnable
	.align	3
.LC174:
	.xword	.LANCHOR2
	.align	3
.LC176:
	.xword	.LC175
	.align	3
.LC178:
	.xword	.LC177
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetSedOnlyEnable, %function
VfmwProc_SetSedOnlyEnable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	ldr	x2, .LC179
	cbz	w0, .L177
	ldr	x1, .LC183
	mov	w3, 1
	mov	w0, 32
	str	w3, [x2, 88]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L177:
	ldr	x1, .LC181
	mov	w0, 32
	str	wzr, [x2, 88]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_SetSedOnlyEnable, .-VfmwProc_SetSedOnlyEnable
	.align	3
.LC179:
	.xword	.LANCHOR2
	.align	3
.LC181:
	.xword	.LC180
	.align	3
.LC183:
	.xword	.LC182
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_OpenModuleLowly, %function
VfmwProc_OpenModuleLowly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 31
	bhi	.L181
	ldr	x5, .LC186
	mov	w2, w3
	ldr	x1, .LC187
	mov	w4, 1
	mov	w0, 32
	ldr	x3, [x5, w3, uxtw 3]
	str	w4, [x3, 1312]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L181:
	ldr	x1, .LC185
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_OpenModuleLowly, .-VfmwProc_OpenModuleLowly
	.align	3
.LC185:
	.xword	.LC184
	.align	3
.LC186:
	.xword	.LANCHOR1
	.align	3
.LC187:
	.xword	.LC43
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_DelRecordEsBuf.isra.5, %function
VCTRL_DelRecordEsBuf.isra.5:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x2, [x19]
	ldr	w0, [x2, 16]
	cbz	w0, .L182
	ldr	w1, [x2, 24]
	cbz	w1, .L182
	cmp	w20, 1
	ldr	x1, .LC188
	beq	.L192
	str	w0, [x29, 48]
	add	x0, x29, 32
	ldr	x1, [x1, 360]
	ldr	x2, [x2, 8]
	str	x2, [x29, 40]
	blr	x1
.L185:
	ldr	x0, [x19]
	ldr	w2, [x0, 24]
	ldr	x1, [x0, 8]
	ldr	w0, [x0, 16]
	bl	MEM_DelMemRecord
.L182:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L192:
	ldr	x1, [x1, 328]
	ldr	x0, [x2, 8]
	blr	x1
	b	.L185
	.size	VCTRL_DelRecordEsBuf.isra.5, .-VCTRL_DelRecordEsBuf.isra.5
	.align	3
.LC188:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_StopTask.part.14, %function
VCTRL_StopTask.part.14:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC189
	ldr	w0, [x20, 260]
	cmp	w0, 1
	beq	.L196
	ldr	x21, .LC190
	mov	w0, 10
	mov	w19, 49
	ldr	x1, [x21, 240]
	blr	x1
	b	.L197
	.p2align 3
.L204:
	ldr	x1, [x21, 240]
	blr	x1
	subs	w19, w19, #1
	beq	.L203
.L197:
	ldr	w1, [x20, 260]
	mov	w0, 10
	cmp	w1, 1
	bne	.L204
.L196:
	str	wzr, [x20, 264]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L203:
	str	wzr, [x20, 264]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VCTRL_StopTask.part.14, .-VCTRL_StopTask.part.14
	.align	3
.LC189:
	.xword	.LANCHOR1
	.align	3
.LC190:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_StartTask.part.15, %function
VCTRL_StartTask.part.15:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC191
	ldr	w0, [x20, 260]
	cmp	w0, 2
	beq	.L208
	ldr	x21, .LC192
	mov	w0, 10
	mov	w19, 49
	ldr	x1, [x21, 240]
	blr	x1
	b	.L209
	.p2align 3
.L216:
	ldr	x1, [x21, 240]
	blr	x1
	subs	w19, w19, #1
	beq	.L215
.L209:
	ldr	w1, [x20, 260]
	mov	w0, 10
	cmp	w1, 2
	bne	.L216
.L208:
	str	wzr, [x20, 264]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L215:
	str	wzr, [x20, 264]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VCTRL_StartTask.part.15, .-VCTRL_StartTask.part.15
	.align	3
.LC191:
	.xword	.LANCHOR1
	.align	3
.LC192:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_SetLastFrameState.part.23, %function
VCTRL_SetLastFrameState.part.23:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC195
	mov	w3, 7166
	ldr	x4, .LC194
	mov	w0, 0
	ldr	x1, .LC196
	add	x2, x2, 24
	bl	dprint_vfmw
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_SetLastFrameState.part.23, .-VCTRL_SetLastFrameState.part.23
	.align	3
.LC194:
	.xword	.LC193
	.align	3
.LC195:
	.xword	.LANCHOR0
	.align	3
.LC196:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VCTRL_CanBeDecodedByHardWare.part.25, %function
VCTRL_CanBeDecodedByHardWare.part.25:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sub	w0, w19, #19
	cmp	w0, 1
	ccmp	w19, 14, 4, hi
	ldr	x19, [sp, 16]
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_CanBeDecodedByHardWare.part.25, .-VCTRL_CanBeDecodedByHardWare.part.25
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_CloseModuleLowly, %function
VfmwProc_CloseModuleLowly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	cmp	w3, 31
	bhi	.L222
	ldr	x4, .LC198
	mov	w2, w3
	ldr	x1, .LC199
	mov	w0, 32
	ldr	x3, [x4, w3, uxtw 3]
	str	wzr, [x3, 1312]
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L222:
	ldr	x1, .LC197
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_CloseModuleLowly, .-VfmwProc_CloseModuleLowly
	.align	3
.LC197:
	.xword	.LC184
	.align	3
.LC198:
	.xword	.LANCHOR1
	.align	3
.LC199:
	.xword	.LC43
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Suspend
	.type	VCTRL_Suspend, %function
VCTRL_Suspend:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC200
	ldr	x0, [x21]
	blr	x0
	ldr	x24, .LC201
	mov	w25, w0
	ldr	x1, [x24]
	cbz	x1, .L224
	mov	w0, 0
	blr	x1
.L225:
	mov	w0, 0
	mov	w20, 32
	mov	w22, 0
	mov	w19, 0
	bl	SCDDRV_PrepareSleep
	mov	w0, 0
	bl	VDMDRV_PrepareSleep
	ldr	x0, [x21]
	blr	x0
	mov	w26, w0
	b	.L236
	.p2align 3
.L226:
	bl	VDMDRV_GetSleepStage
	cmp	w0, 2
	mov	w19, 1
	mov	w23, w19
	beq	.L229
.L260:
	tst	w23, w22
	mov	w0, 10
	bne	.L229
	subs	w20, w20, #1
	beq	.L261
	ldr	x1, [x21, 240]
	blr	x1
	cmp	w19, 1
	ccmp	w22, 1, 0, eq
	beq	.L229
.L236:
	mov	w0, 0
	bl	SCDDRV_GetSleepStage
	cmp	w0, 2
	mov	w0, 0
	beq	.L226
	bl	VDMDRV_GetSleepStage
	cmp	w0, 2
	mov	w23, w19
	bne	.L260
	mov	w22, 1
	b	.L260
	.p2align 3
.L261:
	ldr	x0, [x21]
	blr	x0
	cmp	w26, w0
	sub	w2, w0, w26
	bls	.L232
	mvn	w26, w26
	add	w2, w26, w0
.L232:
	ldr	x1, .LC204
	mov	w4, w22
	mov	w3, w19
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w19, .L248
	ldr	x1, .LC210
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	bl	SCDDRV_ForceSleep
.L248:
	cbnz	w22, .L229
	ldr	x1, .LC212
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	bl	VDMDRV_ForceSleep
.L229:
	ldr	x0, .LC205
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L262
.L238:
	ldr	x0, .LC206
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	beq	.L263
.L245:
	ldr	x0, [x21]
	blr	x0
	cmp	w25, w0
	sub	w2, w0, w25
	bls	.L247
	mvn	w25, w25
	add	w2, w25, w0
.L247:
	ldr	x1, .LC208
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L262:
	ldr	x1, [x24, 64]
	cbz	x1, .L239
	mov	w0, 0
	blr	x1
.L239:
	ldr	x1, [x24, 48]
	cbz	x1, .L240
	mov	w0, 0
	blr	x1
	ldr	x1, [x24, 16]
	cbz	x1, .L242
.L264:
	mov	w0, 0
	blr	x1
.L243:
	ldr	x1, [x24, 80]
	cbz	x1, .L238
	mov	w0, 0
	blr	x1
	ldr	x0, .LC206
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	bne	.L245
	.p2align 2
.L263:
	mov	w0, 2
	str	w0, [x1, 8]
	bl	VCTRL_StopTask.part.14
	b	.L245
.L240:
	ldr	x1, .LC202
	mov	w2, 345
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x24, 16]
	cbnz	x1, .L264
	.p2align 2
.L242:
	ldr	x1, .LC202
	mov	w2, 350
	mov	w0, 0
	bl	dprint_vfmw
	b	.L243
	.p2align 3
.L224:
	ldr	x1, .LC202
	mov	w2, 247
	mov	w0, 0
	bl	dprint_vfmw
	b	.L225
	.size	VCTRL_Suspend, .-VCTRL_Suspend
	.align	3
.LC200:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC201:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC202:
	.xword	.LC127
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC205:
	.xword	g_HalDisable
	.align	3
.LC206:
	.xword	.LANCHOR1
	.align	3
.LC208:
	.xword	.LC207
	.align	3
.LC210:
	.xword	.LC209
	.align	3
.LC212:
	.xword	.LC211
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestSuspend, %function
VfmwProc_TestSuspend:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC215
	mov	x2, x19
	mov	w0, 22
	bl	dprint_vfmw
	bl	VCTRL_Suspend
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestSuspend, .-VfmwProc_TestSuspend
	.align	3
.LC215:
	.xword	.LC214
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Resume
	.type	VCTRL_Resume, %function
VCTRL_Resume:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC216
	ldr	x0, [x20]
	blr	x0
	mov	w19, w0
	ldr	x0, .LC217
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L286
.L267:
	mov	w0, 0
	bl	SCDDRV_ExitSleep
	mov	w0, 0
	bl	VDMDRV_ExitSleep
	ldr	x0, .LC220
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	beq	.L287
.L277:
	ldr	x0, [x20]
	blr	x0
	cmp	w19, w0
	sub	w2, w0, w19
	bls	.L279
	mvn	w2, w19
	add	w2, w2, w0
.L279:
	ldr	x1, .LC222
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L286:
	ldr	x21, .LC218
	ldr	x1, [x21, 8]
	cbz	x1, .L288
	mov	w0, 0
	blr	x1
.L269:
	ldr	x1, [x21, 40]
	cbz	x1, .L289
	mov	w0, 0
	blr	x1
.L271:
	ldr	x1, [x21, 56]
	cbz	x1, .L272
	mov	w0, 0
	blr	x1
.L272:
	ldr	x1, [x21, 72]
	cbz	x1, .L273
	mov	w0, 0
	blr	x1
.L273:
	ldr	x1, [x21, 136]
	cbz	x1, .L274
	mov	w0, 0
	blr	x1
.L275:
	ldr	x0, [x21, 144]
	cbz	x0, .L276
	blr	x0
	b	.L267
	.p2align 3
.L287:
	str	w0, [x1, 8]
	bl	VCTRL_StartTask.part.15
	b	.L277
	.p2align 3
.L289:
	ldr	x1, .LC219
	mov	w2, 392
	mov	w0, 0
	bl	dprint_vfmw
	b	.L271
	.p2align 3
.L274:
	ldr	x1, .LC219
	mov	w2, 399
	mov	w0, 0
	bl	dprint_vfmw
	b	.L275
	.p2align 3
.L276:
	ldr	x1, .LC219
	mov	w2, 400
	mov	w0, 0
	bl	dprint_vfmw
	b	.L267
	.p2align 3
.L288:
	ldr	x1, .LC219
	mov	w2, 387
	mov	w0, 0
	bl	dprint_vfmw
	b	.L269
	.size	VCTRL_Resume, .-VCTRL_Resume
	.align	3
.LC216:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC217:
	.xword	g_HalDisable
	.align	3
.LC218:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC219:
	.xword	.LC127
	.align	3
.LC220:
	.xword	.LANCHOR1
	.align	3
.LC222:
	.xword	.LC221
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestResume, %function
VfmwProc_TestResume:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC224
	mov	x2, x19
	mov	w0, 22
	bl	dprint_vfmw
	bl	VCTRL_Resume
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestResume, .-VfmwProc_TestResume
	.align	3
.LC224:
	.xword	.LC214
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	ChanCtx_Init
	.type	ChanCtx_Init, %function
ChanCtx_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC228
	ldr	x0, .LC227
	mov	x2, 384
	mov	w1, 0
	ldr	x3, [x0, 96]
	mov	x0, x19
	blr	x3
	add	x0, x19, 128
	add	x1, x19, 256
	mov	w2, -1
	.p2align 2
.L292:
	str	w2, [x0], 4
	cmp	x0, x1
	bne	.L292
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ChanCtx_Init, .-ChanCtx_Init
	.align	3
.LC227:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC228:
	.xword	g_ChanCtx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_RecordPosTime
	.type	VCTRL_RecordPosTime, %function
VCTRL_RecordPosTime:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, 11
	bhi	.L300
	ldr	x22, .LC234
	uxtw	x20, w21
	ldrb	w0, [x22, x20]
	cmp	w0, 14
	mov	w19, w0
	bhi	.L301
	cmp	w21, 10
	beq	.L302
.L299:
	ldr	x0, .LC236
	ldr	x0, [x0, 8]
	blr	x0
	lsl	x1, x20, 4
	ldr	x2, .LC237
	sub	x1, x1, x20
	add	x19, x1, x19, sxtw
	ldrb	w1, [x22, x20]
	add	w1, w1, 1
	strb	w1, [x22, x20]
	str	w0, [x2, x19, lsl 2]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L301:
	strb	wzr, [x22, x20]
	cmp	w21, 10
	mov	w19, 0
	bne	.L299
.L302:
	ldr	x0, .LC235
	mov	w1, 1
	strb	w1, [x0, 2816]
	b	.L299
	.p2align 3
.L300:
	ldr	x2, .LC231
	mov	w4, w21
	ldr	x1, .LC233
	mov	w3, 641
	add	x2, x2, 48
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VCTRL_RecordPosTime, .-VCTRL_RecordPosTime
	.align	3
.LC231:
	.xword	.LANCHOR0
	.align	3
.LC233:
	.xword	.LC232
	.align	3
.LC234:
	.xword	g_TimeRecId
	.align	3
.LC235:
	.xword	.LANCHOR1
	.align	3
.LC236:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC237:
	.xword	g_TimeRecTable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_RecordData
	.type	VCTRL_RecordData, %function
VCTRL_RecordData:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	uxtw	x19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 1
	bhi	.L308
	ldr	x3, .LC241
	ldrb	w0, [x3, x19]
	cmp	w0, 14
	bhi	.L307
	add	w4, w0, 1
	uxtb	w4, w4
.L306:
	lsl	x2, x19, 4
	ldr	x1, .LC242
	sub	x2, x2, x19
	strb	w4, [x3, x19]
	add	x0, x2, x0, sxtw
	str	w20, [x1, x0, lsl 2]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L307:
	mov	w4, 1
	mov	w0, 0
	b	.L306
	.p2align 3
.L308:
	ldr	x2, .LC238
	mov	w4, w19
	ldr	x1, .LC240
	mov	w3, 664
	add	x2, x2, 72
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_RecordData, .-VCTRL_RecordData
	.align	3
.LC238:
	.xword	.LANCHOR0
	.align	3
.LC240:
	.xword	.LC239
	.align	3
.LC241:
	.xword	g_DataRecId
	.align	3
.LC242:
	.xword	g_DataTable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Isr_1
	.type	VCTRL_Isr_1, %function
VCTRL_Isr_1:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	bl	VDMDRV_IsrProcess
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Isr_1, .-VCTRL_Isr_1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Isr_2
	.type	VCTRL_Isr_2, %function
VCTRL_Isr_2:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 2
	bl	VDMDRV_IsrProcess
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Isr_2, .-VCTRL_Isr_2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Scd_Isr_1
	.type	VCTRL_Scd_Isr_1, %function
VCTRL_Scd_Isr_1:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1
	bl	SM_SCDIntServeProc
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Scd_Isr_1, .-VCTRL_Scd_Isr_1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_Scd_Isr_2
	.type	VCTRL_Scd_Isr_2, %function
VCTRL_Scd_Isr_2:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 2
	bl	SM_SCDIntServeProc
	mov	w0, 1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_Scd_Isr_2, .-VCTRL_Scd_Isr_2
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_InformVdmFree
	.type	VCTRL_InformVdmFree, %function
VCTRL_InformVdmFree:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC243
	mov	w0, 0
	ldr	x1, [x1, 256]
	blr	x1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_InformVdmFree, .-VCTRL_InformVdmFree
	.align	3
.LC243:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ExtraWakeUpThread
	.type	VCTRL_ExtraWakeUpThread, %function
VCTRL_ExtraWakeUpThread:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC244
	mov	w0, 0
	ldr	x1, [x1, 256]
	blr	x1
	ldp	x29, x30, [sp], 16
	ret
	.size	VCTRL_ExtraWakeUpThread, .-VCTRL_ExtraWakeUpThread
	.align	3
.LC244:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetMoreGapEnable
	.type	VCTRL_SetMoreGapEnable, %function
VCTRL_SetMoreGapEnable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L321
	ldr	x0, .LC248
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L322
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L323
	cmp	w20, 1
	bhi	.L320
	str	w20, [x0, 1296]
	mov	w0, 0
.L317:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L320:
	str	wzr, [x0, 1296]
	mov	w0, -1
	b	.L317
	.p2align 3
.L323:
	ldr	x2, .LC246
	mov	w3, 801
	ldr	x4, .LC251
	mov	w0, 0
	ldr	x1, .LC247
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L317
	.p2align 3
.L321:
	ldr	x2, .LC246
	mov	w3, 799
	ldr	x4, .LC245
	mov	w0, 0
	ldr	x1, .LC247
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L317
.L322:
	ldr	x2, .LC246
	mov	w3, 800
	ldr	x4, .LC249
	ldr	x1, .LC247
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L317
	.size	VCTRL_SetMoreGapEnable, .-VCTRL_SetMoreGapEnable
	.align	3
.LC245:
	.xword	.LC193
	.align	3
.LC246:
	.xword	.LANCHOR0
	.align	3
.LC247:
	.xword	.LC6
	.align	3
.LC248:
	.xword	.LANCHOR1
	.align	3
.LC249:
	.xword	.LC9
	.align	3
.LC251:
	.xword	.LC250
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetCallBack
	.type	VCTRL_SetCallBack, %function
VCTRL_SetCallBack:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L332
	cbz	w19, .L328
	cmp	w19, 1
	beq	.L329
	ldr	x2, .LC254
	mov	w3, w19
	ldr	x1, .LC258
	mov	w0, 0
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -1
.L326:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L329:
	ldr	x1, .LC256
	mov	w0, 0
	str	x20, [x1, 576]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L328:
	ldr	x1, .LC256
	mov	w0, 0
	str	x20, [x1, 568]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L332:
	ldr	x2, .LC254
	mov	w3, 914
	ldr	x4, .LC253
	mov	w0, 0
	ldr	x1, .LC255
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -1
	b	.L326
	.size	VCTRL_SetCallBack, .-VCTRL_SetCallBack
	.align	3
.LC253:
	.xword	.LC252
	.align	3
.LC254:
	.xword	.LANCHOR0
	.align	3
.LC255:
	.xword	.LC6
	.align	3
.LC256:
	.xword	.LANCHOR1
	.align	3
.LC258:
	.xword	.LC257
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StopTask
	.type	VCTRL_StopTask, %function
VCTRL_StopTask:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC259
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	bne	.L335
	mov	w0, 2
	str	w0, [x1, 8]
	bl	VCTRL_StopTask.part.14
.L334:
	ldp	x29, x30, [sp], 16
	ret
	.p2align 3
.L335:
	mov	w0, -1
	b	.L334
	.size	VCTRL_StopTask, .-VCTRL_StopTask
	.align	3
.LC259:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StartTask
	.type	VCTRL_StartTask, %function
VCTRL_StartTask:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC261
	add	x1, x0, 256
	ldr	w0, [x0, 256]
	cmp	w0, 1
	bne	.L338
	str	w0, [x1, 8]
	bl	VCTRL_StartTask.part.15
.L337:
	ldp	x29, x30, [sp], 16
	ret
	.p2align 3
.L338:
	mov	w0, -1
	b	.L337
	.size	VCTRL_StartTask, .-VCTRL_StartTask
	.align	3
.LC261:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetStreamInterface
	.type	VCTRL_SetStreamInterface, %function
VCTRL_SetStreamInterface:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x21, x1
	mov	x0, x30
	bl	_mcount
	cbz	x21, .L344
	cmp	w20, 31
	bhi	.L345
	ldr	x19, .LC269
	sxtw	x22, w20
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L346
	ldr	x20, .LC271
	mov	x2, 24
	mov	x1, x21
	add	x0, x0, 192
	add	x19, x19, 2824
	ldr	x3, [x20, 104]
	blr	x3
	lsl	x0, x22, 2
	ldr	x3, [x20, 104]
	sub	x0, x0, x22
	mov	x2, 24
	mov	x1, x21
	add	x0, x19, x0, lsl 3
	blr	x3
	mov	w0, 0
.L341:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L345:
	ldr	x2, .LC265
	mov	w3, 1135
	ldr	x4, .LC268
	mov	w0, 0
	ldr	x1, .LC266
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, -1
	b	.L341
.L346:
	ldr	x2, .LC265
	mov	w3, 1136
	ldr	x4, .LC270
	ldr	x1, .LC266
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, -1
	b	.L341
.L344:
	ldr	x2, .LC265
	mov	w3, 1134
	ldr	x4, .LC264
	mov	w0, 0
	ldr	x1, .LC266
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, -1
	b	.L341
	.size	VCTRL_SetStreamInterface, .-VCTRL_SetStreamInterface
	.align	3
.LC264:
	.xword	.LC263
	.align	3
.LC265:
	.xword	.LANCHOR0
	.align	3
.LC266:
	.xword	.LC6
	.align	3
.LC268:
	.xword	.LC267
	.align	3
.LC269:
	.xword	.LANCHOR1
	.align	3
.LC270:
	.xword	.LC9
	.align	3
.LC271:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetSendStreamAgainFlag
	.type	VCTRL_SetSendStreamAgainFlag, %function
VCTRL_SetSendStreamAgainFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L351
	ldr	x0, .LC276
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L352
	add	x2, x0, 503808
	mov	w0, 0
	str	w20, [x2, 1652]
.L349:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L351:
	ldr	x2, .LC274
	mov	w3, 1147
	ldr	x4, .LC273
	mov	w0, 0
	ldr	x1, .LC275
	add	x2, x2, 176
	bl	dprint_vfmw
	mov	w0, -1
	b	.L349
.L352:
	ldr	x2, .LC274
	mov	w3, 1148
	ldr	x4, .LC277
	ldr	x1, .LC275
	add	x2, x2, 176
	bl	dprint_vfmw
	mov	w0, -1
	b	.L349
	.size	VCTRL_SetSendStreamAgainFlag, .-VCTRL_SetSendStreamAgainFlag
	.align	3
.LC273:
	.xword	.LC267
	.align	3
.LC274:
	.xword	.LANCHOR0
	.align	3
.LC275:
	.xword	.LC6
	.align	3
.LC276:
	.xword	.LANCHOR1
	.align	3
.LC277:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetSendStreamAgainFlag
	.type	VCTRL_GetSendStreamAgainFlag, %function
VCTRL_GetSendStreamAgainFlag:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L357
	ldr	x0, .LC281
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L358
	add	x0, x0, 503808
	ldr	w0, [x0, 1652]
.L355:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L357:
	ldr	x2, .LC279
	mov	w3, 1157
	ldr	x4, .LC278
	mov	w0, 0
	ldr	x1, .LC280
	add	x2, x2, 208
	bl	dprint_vfmw
	mov	w0, -1
	b	.L355
.L358:
	ldr	x2, .LC279
	mov	w3, 1158
	ldr	x4, .LC282
	ldr	x1, .LC280
	add	x2, x2, 208
	bl	dprint_vfmw
	mov	w0, -1
	b	.L355
	.size	VCTRL_GetSendStreamAgainFlag, .-VCTRL_GetSendStreamAgainFlag
	.align	3
.LC278:
	.xword	.LC267
	.align	3
.LC279:
	.xword	.LANCHOR0
	.align	3
.LC280:
	.xword	.LC6
	.align	3
.LC281:
	.xword	.LANCHOR1
	.align	3
.LC282:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetStreamInterface
	.type	VCTRL_GetStreamInterface, %function
VCTRL_GetStreamInterface:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L363
	ldr	x20, .LC283
	sxtw	x2, w19
	ldr	x1, [x20, w19, sxtw 3]
	cbz	x1, .L363
	ldr	x3, .LC284
	lsl	x0, x2, 2
	sub	x0, x0, x2
	add	x4, x20, 2824
	mov	x2, 24
	add	x1, x1, 192
	ldr	x3, [x3, 120]
	add	x0, x4, x0, lsl 3
	blr	x3
	cbnz	w0, .L364
	ldr	x0, [x20, w19, sxtw 3]
	add	x0, x0, 192
.L360:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L363:
	mov	x0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L364:
	ldr	x1, .LC286
	mov	w3, w19
	mov	w2, 1173
	mov	w0, 0
	bl	dprint_vfmw
	mov	x0, 0
	b	.L360
	.size	VCTRL_GetStreamInterface, .-VCTRL_GetStreamInterface
	.align	3
.LC283:
	.xword	.LANCHOR1
	.align	3
.LC284:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC286:
	.xword	.LC285
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetStreamSize
	.type	VCTRL_GetStreamSize, %function
VCTRL_GetStreamSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L370
	ldr	x0, .LC291
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L371
	ldr	w2, [x0, 4]
	cmp	w2, 1
	bne	.L372
	mov	x2, 34528
	mov	x1, x20
	movk	x2, 0x1, lsl 16
	add	x0, x0, x2
	bl	GetSegStreamSize
.L367:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L372:
	ldr	x2, .LC289
	mov	w3, 1188
	ldr	x4, .LC295
	mov	w0, 0
	ldr	x1, .LC290
	add	x2, x2, 240
	bl	dprint_vfmw
	mov	w0, -1
	b	.L367
	.p2align 3
.L370:
	ldr	x2, .LC289
	mov	w3, 1186
	ldr	x4, .LC288
	mov	w0, 0
	ldr	x1, .LC290
	add	x2, x2, 240
	bl	dprint_vfmw
	mov	w0, -1
	b	.L367
.L371:
	ldr	x2, .LC289
	mov	w3, 1187
	ldr	x4, .LC293
	ldr	x1, .LC290
	add	x2, x2, 240
	bl	dprint_vfmw
	mov	w0, -1
	b	.L367
	.size	VCTRL_GetStreamSize, .-VCTRL_GetStreamSize
	.align	3
.LC288:
	.xword	.LC193
	.align	3
.LC289:
	.xword	.LANCHOR0
	.align	3
.LC290:
	.xword	.LC6
	.align	3
.LC291:
	.xword	.LANCHOR1
	.align	3
.LC293:
	.xword	.LC292
	.align	3
.LC295:
	.xword	.LC294
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CheckFreshRaw
	.type	VCTRL_CheckFreshRaw, %function
VCTRL_CheckFreshRaw:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	stp	wzr, wzr, [x29, 40]
	bhi	.L380
	ldr	x0, .LC299
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L381
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L382
	add	x19, x0, 1736
	add	x1, x29, 40
	mov	x0, x19
	bl	GetRawStreamNum
	cbnz	w0, .L379
	add	x1, x29, 44
	mov	x0, x19
	bl	GetRawStreamSize
	cbnz	w0, .L379
	ldr	x1, .LC303
	mov	w0, 22
	ldp	w2, w3, [x29, 40]
	bl	dprint_vfmw
	ldr	w0, [x29, 40]
	cmp	w0, wzr
	ble	.L379
	ldr	w0, [x29, 44]
	cmp	w0, 3
	csetm	w0, le
.L375:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L379:
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L382:
	ldr	x2, .LC297
	mov	w3, 1202
	ldr	x4, .LC301
	mov	w0, 0
	ldr	x1, .LC298
	add	x2, x2, 264
	bl	dprint_vfmw
	mov	w0, -1
	b	.L375
	.p2align 3
.L380:
	ldr	x2, .LC297
	mov	w3, 1200
	ldr	x4, .LC296
	mov	w0, 0
	ldr	x1, .LC298
	add	x2, x2, 264
	bl	dprint_vfmw
	mov	w0, -1
	b	.L375
.L381:
	ldr	x2, .LC297
	mov	w3, 1201
	ldr	x4, .LC300
	ldr	x1, .LC298
	add	x2, x2, 264
	bl	dprint_vfmw
	mov	w0, -1
	b	.L375
	.size	VCTRL_CheckFreshRaw, .-VCTRL_CheckFreshRaw
	.align	3
.LC296:
	.xword	.LC193
	.align	3
.LC297:
	.xword	.LANCHOR0
	.align	3
.LC298:
	.xword	.LC6
	.align	3
.LC299:
	.xword	.LANCHOR1
	.align	3
.LC300:
	.xword	.LC292
	.align	3
.LC301:
	.xword	.LC294
	.align	3
.LC303:
	.xword	.LC302
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CheckFreshSeg
	.type	VCTRL_CheckFreshSeg, %function
VCTRL_CheckFreshSeg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	stp	wzr, wzr, [x29, 40]
	bhi	.L388
	ldr	x0, .LC307
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L389
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L390
	mov	x3, 34528
	add	x2, x29, 44
	movk	x3, 0x1, lsl 16
	add	x1, x29, 40
	add	x0, x0, x3
	bl	GetFreshSegStream
	ldr	x1, .LC311
	mov	w0, 22
	ldp	w2, w3, [x29, 40]
	bl	dprint_vfmw
	ldr	w0, [x29, 40]
	cmp	w0, wzr
	csetm	w0, le
.L385:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L390:
	ldr	x2, .LC305
	mov	w3, 1225
	ldr	x4, .LC309
	mov	w0, 0
	ldr	x1, .LC306
	add	x2, x2, 288
	bl	dprint_vfmw
	mov	w0, -1
	b	.L385
	.p2align 3
.L388:
	ldr	x2, .LC305
	mov	w3, 1223
	ldr	x4, .LC304
	mov	w0, 0
	ldr	x1, .LC306
	add	x2, x2, 288
	bl	dprint_vfmw
	mov	w0, -1
	b	.L385
.L389:
	ldr	x2, .LC305
	mov	w3, 1224
	ldr	x4, .LC308
	ldr	x1, .LC306
	add	x2, x2, 288
	bl	dprint_vfmw
	mov	w0, -1
	b	.L385
	.size	VCTRL_CheckFreshSeg, .-VCTRL_CheckFreshSeg
	.align	3
.LC304:
	.xword	.LC193
	.align	3
.LC305:
	.xword	.LANCHOR0
	.align	3
.LC306:
	.xword	.LC6
	.align	3
.LC307:
	.xword	.LANCHOR1
	.align	3
.LC308:
	.xword	.LC292
	.align	3
.LC309:
	.xword	.LC294
	.align	3
.LC311:
	.xword	.LC310
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetDiscardPicParam
	.type	VCTRL_SetDiscardPicParam, %function
VCTRL_SetDiscardPicParam:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L397
	cbz	x20, .L398
	ldr	x21, .LC317
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L399
	ldr	x3, .LC319
	mov	x1, x20
	mov	x2, 8
	add	x0, x0, 1592
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w0, [x1, 1592]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L396
	mov	w0, 0
	str	wzr, [x1, 1592]
.L393:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L396:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L397:
	ldr	x2, .LC313
	mov	w3, 1241
	ldr	x4, .LC312
	mov	w0, 0
	ldr	x1, .LC314
	add	x2, x2, 312
	bl	dprint_vfmw
	mov	w0, -1
	b	.L393
.L399:
	ldr	x2, .LC313
	mov	w3, 1243
	ldr	x4, .LC318
	ldr	x1, .LC314
	add	x2, x2, 312
	bl	dprint_vfmw
	mov	w0, -1
	b	.L393
.L398:
	ldr	x2, .LC313
	mov	w3, 1242
	ldr	x4, .LC316
	mov	w0, 0
	ldr	x1, .LC314
	add	x2, x2, 312
	bl	dprint_vfmw
	mov	w0, -1
	b	.L393
	.size	VCTRL_SetDiscardPicParam, .-VCTRL_SetDiscardPicParam
	.align	3
.LC312:
	.xword	.LC193
	.align	3
.LC313:
	.xword	.LANCHOR0
	.align	3
.LC314:
	.xword	.LC6
	.align	3
.LC316:
	.xword	.LC315
	.align	3
.LC317:
	.xword	.LANCHOR1
	.align	3
.LC318:
	.xword	.LC9
	.align	3
.LC319:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_PartitionMemForStdUser
	.type	VCTRL_PartitionMemForStdUser, %function
VCTRL_PartitionMemForStdUser:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	w23, w1
	mov	w21, w2
	mov	w25, w3
	mov	w26, w4
	bl	_mcount
	ldr	x19, .LC320
	cmp	w23, 31
	ccmp	w21, 31, 4, gt
	ldr	x22, [x19, w20, sxtw 3]
	ble	.L412
	cmp	w25, wzr
	ccmp	w26, wzr, 4, ne
	beq	.L413
	ldr	x24, .LC325
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 88
	ldr	x3, [x24, 96]
	blr	x3
	strb	wzr, [x29, 89]
	mov	w2, 1
	add	x1, x29, 88
	mov	w0, w20
	strb	wzr, [x29, 90]
	stp	w23, w21, [x29, 92]
	stp	w23, w21, [x29, 100]
	strb	wzr, [x29, 91]
	strb	w2, [x29, 88]
	bl	FSP_ConfigInstance
	mov	w21, w0
	cbnz	w0, .L404
	add	x3, x29, 84
	mov	w2, w26
	mov	w1, w25
	mov	w0, w20
	bl	FSP_ConfigFrameBuf
	cbnz	w0, .L414
	add	x23, x19, 3592
	mov	w0, w20
	mov	x1, x23
	bl	FSP_GetInstInfo
	ldrsb	w0, [x23, 2]
	mov	w1, 16
	cmp	w0, w1
	csel	w0, w0, w1, le
	str	w0, [x22, 556]
	cmp	w0, 2
	ble	.L415
	ldr	w0, [x23, 4]
	add	x20, x22, 488
	ldr	x3, [x24, 96]
	mov	x2, 64
	str	w0, [x22, 552]
	mov	w1, 0
	mov	x0, x20
	blr	x3
	ldr	w0, [x22, 556]
	cmp	w0, wzr
	ble	.L402
	sub	w4, w0, #1
	mov	w3, 88
	mov	x2, 104
	add	x1, x19, 3608
	mov	x0, x20
	umaddl	x2, w4, w3, x2
	add	x3, x23, x2
	.p2align 2
.L409:
	ldr	w2, [x1], 88
	str	w2, [x0], 4
	cmp	x1, x3
	bne	.L409
.L402:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
.L413:
	ldr	x1, .LC324
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L402
.L404:
	ldr	x1, .LC332
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L402
.L414:
	ldr	x1, .LC327
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L402
.L415:
	ldr	x2, .LC328
	mov	w3, 1353
	ldr	x1, .LC330
	mov	w0, 0
	add	x2, x2, 344
	mov	w21, -1
	bl	dprint_vfmw
	b	.L402
.L412:
	ldr	x1, .LC322
	mov	w3, w21
	mov	w2, w23
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L402
	.size	VCTRL_PartitionMemForStdUser, .-VCTRL_PartitionMemForStdUser
	.align	3
.LC320:
	.xword	.LANCHOR1
	.align	3
.LC322:
	.xword	.LC321
	.align	3
.LC324:
	.xword	.LC323
	.align	3
.LC325:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC327:
	.xword	.LC326
	.align	3
.LC328:
	.xword	.LANCHOR0
	.align	3
.LC330:
	.xword	.LC329
	.align	3
.LC332:
	.xword	.LC331
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_UnInstallChan
	.type	VCTRL_UnInstallChan, %function
VCTRL_UnInstallChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	FSP_DisableInstance
	mov	w0, w19
	bl	CloseUsdPool_WithMem
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_UnInstallChan, .-VCTRL_UnInstallChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DelAllFrameMemRecord
	.type	DelAllFrameMemRecord, %function
DelAllFrameMemRecord:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	add	x20, x1, 2304
	bl	_mcount
	cbz	x19, .L435
	.p2align 2
.L430:
	ldr	w0, [x19]
	cmp	w0, 255
	beq	.L420
	ldr	w2, [x19, 12]
	ldr	w0, [x19, 32]
	ldr	x1, [x19, 24]
	bl	MEM_DelMemRecord
.L420:
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L421
	ldr	w2, [x19, 16]
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_DelMemRecord
.L421:
	ldr	w0, [x19, 8]
	cmp	w0, 255
	beq	.L422
	ldr	w2, [x19, 20]
	ldr	w0, [x19, 64]
	ldr	x1, [x19, 56]
	bl	MEM_DelMemRecord
.L422:
	add	x19, x19, 72
	cmp	x19, x20
	bne	.L430
	mov	w0, 0
.L419:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L435:
	ldr	x2, .LC338
	mov	w3, 1392
	ldr	x4, .LC337
	mov	w0, 0
	ldr	x1, .LC339
	add	x2, x2, 376
	bl	dprint_vfmw
	mov	w0, -1
	b	.L419
	.size	DelAllFrameMemRecord, .-DelAllFrameMemRecord
	.align	3
.LC337:
	.xword	.LC336
	.align	3
.LC338:
	.xword	.LANCHOR0
	.align	3
.LC339:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_FreeChanResource
	.type	VCTRL_FreeChanResource, %function
VCTRL_FreeChanResource:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L460
	ldr	x20, [x19]
	cbz	x20, .L461
	ldr	w0, [x19, 40]
	cmp	w0, 1
	beq	.L441
	ldr	w0, [x20, 16]
	ldr	w2, [x20, 24]
	ldr	x1, [x20, 8]
	bl	MEM_DelMemRecord
.L442:
	ldr	w0, [x19, 44]
	cmp	w0, 1
	beq	.L462
.L440:
	ldr	x20, [x19, 8]
	cbz	x20, .L463
	ldr	w0, [x20, 16]
	ldr	w2, [x20, 24]
	ldr	x1, [x20, 8]
	bl	MEM_DelMemRecord
	ldr	w0, [x19, 48]
	cmp	w0, 1
	beq	.L464
.L445:
	ldr	x20, [x19, 16]
	cbz	x20, .L465
.L446:
	ldr	w0, [x20, 16]
	ldr	w2, [x20, 24]
	ldr	x1, [x20, 8]
	bl	MEM_DelMemRecord
	ldr	w0, [x19, 52]
	cmp	w0, 1
	bne	.L447
	ldr	w0, [x20, 16]
	cbnz	w0, .L466
.L447:
	ldr	x1, .LC353
	ldr	x0, [x20, 8]
	ldr	x1, [x1, 328]
	blr	x1
	mov	w0, 0
.L438:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L441:
	ldr	x1, [x19, 24]
	cbz	x1, .L467
	mov	w0, w21
	bl	DelAllFrameMemRecord
	cbz	w0, .L442
	ldr	x1, .LC348
	mov	w0, 0
	bl	dprint_vfmw
	ldr	w0, [x19, 44]
	cmp	w0, 1
	bne	.L440
	.p2align 2
.L462:
	ldr	w0, [x20, 16]
	cbz	w0, .L440
	ldr	x1, [x20, 8]
	bl	MEM_ReleaseMemBlock
	b	.L440
	.p2align 3
.L464:
	ldr	w0, [x20, 16]
	cbz	w0, .L445
	ldr	x1, [x20, 8]
	bl	MEM_ReleaseMemBlock
	b	.L445
	.p2align 3
.L463:
	ldr	x2, .LC340
	mov	w0, 0
	ldr	x1, .LC350
	add	x2, x2, 400
	bl	dprint_vfmw
	ldr	x20, [x19, 16]
	cbnz	x20, .L446
.L465:
	ldr	x2, .LC340
	mov	w0, 0
	ldr	x1, .LC352
	add	x2, x2, 400
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L466:
	ldr	x1, [x20, 8]
	bl	MEM_ReleaseMemBlock
	mov	w0, 0
	b	.L438
	.p2align 3
.L467:
	ldr	x2, .LC340
	mov	w0, 0
	ldr	x1, .LC346
	add	x2, x2, 400
	bl	dprint_vfmw
	b	.L442
	.p2align 3
.L461:
	ldr	x2, .LC340
	mov	w0, 0
	ldr	x1, .LC344
	add	x2, x2, 400
	bl	dprint_vfmw
	b	.L440
.L460:
	ldr	x2, .LC340
	mov	w0, 0
	ldr	x1, .LC342
	add	x2, x2, 400
	bl	dprint_vfmw
	mov	w0, -1
	b	.L438
	.size	VCTRL_FreeChanResource, .-VCTRL_FreeChanResource
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
.LC353:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanCtxSize
	.type	VCTRL_GetChanCtxSize, %function
VCTRL_GetChanCtxSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 26
	beq	.L471
	mov	w0, 47544
	movk	w0, 0xf, lsl 16
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L471:
	mov	w0, 17992
	movk	w0, 0xb5, lsl 16
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanCtxSize, .-VCTRL_GetChanCtxSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanCfg
	.type	VCTRL_GetChanCfg, %function
VCTRL_GetChanCfg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L477
	cbz	x20, .L478
	ldr	x0, .LC359
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L479
	ldr	x3, .LC361
	mov	x2, 148
	add	x1, x1, 44
	mov	x0, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L474:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L477:
	ldr	x2, .LC355
	mov	w3, 2428
	ldr	x4, .LC354
	mov	w0, 0
	ldr	x1, .LC356
	add	x2, x2, 424
	bl	dprint_vfmw
	mov	w0, -1
	b	.L474
.L479:
	ldr	x2, .LC355
	mov	w3, 2430
	ldr	x4, .LC360
	mov	w0, 0
	ldr	x1, .LC356
	add	x2, x2, 424
	bl	dprint_vfmw
	mov	w0, -1
	b	.L474
.L478:
	ldr	x2, .LC355
	mov	w3, 2429
	ldr	x4, .LC358
	mov	w0, 0
	ldr	x1, .LC356
	add	x2, x2, 424
	bl	dprint_vfmw
	mov	w0, -1
	b	.L474
	.size	VCTRL_GetChanCfg, .-VCTRL_GetChanCfg
	.align	3
.LC354:
	.xword	.LC193
	.align	3
.LC355:
	.xword	.LANCHOR0
	.align	3
.LC356:
	.xword	.LC6
	.align	3
.LC358:
	.xword	.LC357
	.align	3
.LC359:
	.xword	.LANCHOR1
	.align	3
.LC360:
	.xword	.LC9
	.align	3
.LC361:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CheckCommonParameter
	.type	VCTRL_CheckCommonParameter, %function
VCTRL_CheckCommonParameter:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x0, .LC362
	ldr	w1, [x19, 8]
	ldr	x0, [x0, w20, sxtw 3]
	ldr	w2, [x0, 52]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 72]
	ldr	w1, [x19, 28]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 68]
	ldr	w1, [x19, 24]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 76]
	ldr	w1, [x19, 32]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 80]
	ldr	w1, [x19, 36]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 84]
	ldr	w1, [x19, 40]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 100]
	ldr	w1, [x19, 56]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 112]
	ldr	w1, [x19, 68]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 108]
	ldr	w1, [x19, 64]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 104]
	ldr	w1, [x19, 60]
	cmp	w2, w1
	bne	.L492
	ldr	w2, [x0, 116]
	ldr	w1, [x19, 72]
	cmp	w2, w1
	bne	.L492
	ldr	w1, [x0, 176]
	ldr	w0, [x19, 132]
	ldp	x19, x20, [sp, 16]
	cmp	w1, w0
	csetm	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L492:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_CheckCommonParameter, .-VCTRL_CheckCommonParameter
	.align	3
.LC362:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CmpConfigParameter
	.type	VCTRL_CmpConfigParameter, %function
VCTRL_CmpConfigParameter:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x0, .LC363
	ldr	x19, [x0, w20, sxtw 3]
	ldr	w0, [x19, 632]
	cmp	w0, 22
	beq	.L498
	mov	x1, x21
	mov	w0, w20
	bl	VCTRL_CheckCommonParameter
	cbnz	w0, .L498
	ldr	w1, [x19, 52]
	cmp	w1, 1
	beq	.L499
	sub	w1, w1, #10
	cmp	w1, 2
	bhi	.L494
	ldr	w0, [x21, 12]
	ldr	w1, [x19, 56]
	cmp	w1, w0
	csetm	w0, ne
.L494:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L499:
	ldr	w1, [x19, 56]
	ldr	w0, [x21, 12]
	cmp	w1, w0
	bne	.L498
	ldr	w0, [x21, 16]
	ldr	w1, [x19, 60]
	ldr	x21, [sp, 32]
	cmp	w1, w0
	csetm	w0, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L498:
	mov	w0, -1
	b	.L494
	.size	VCTRL_CmpConfigParameter, .-VCTRL_CmpConfigParameter
	.align	3
.LC363:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CheckChanWH
	.type	VCTRL_CheckChanWH, %function
VCTRL_CheckChanWH:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC364
	ldr	x2, .LC365
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w2, [x2]
	ldr	w3, [x0, 1372]
	cmp	w3, w2
	bgt	.L501
	ldr	x1, .LC366
	ldr	w3, [x0, 1376]
	mov	w0, 0
	ldr	w1, [x1]
	cmp	w3, w1
	ble	.L502
.L501:
	ldr	w1, [x20, 8]
	mov	w0, 0
	cmp	w1, wzr
	and	w3, w1, -3
	ccmp	w1, 20, 4, ne
	ccmp	w3, 13, 4, ne
	cset	w1, ne
	cbnz	w1, .L506
.L502:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L506:
	ldr	x3, .LC366
	ldr	x1, .LC368
	ldr	w3, [x3]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L502
	.size	VCTRL_CheckChanWH, .-VCTRL_CheckChanWH
	.align	3
.LC364:
	.xword	.LANCHOR1
	.align	3
.LC365:
	.xword	g_ChipMaxWidth
	.align	3
.LC366:
	.xword	g_ChipMaxHeight
	.align	3
.LC368:
	.xword	.LC367
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ConfigChanCompress
	.type	VCTRL_ConfigChanCompress, %function
VCTRL_ConfigChanCompress:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 56]
	sxtw	x2, w19
	ldr	x1, .LC369
	cmp	w0, 2
	ldr	x0, [x1, w19, sxtw 3]
	beq	.L512
	add	x1, x1, 608
	lsl	x2, x2, 4
	add	x3, x1, x2
	add	x0, x0, 640
	ldr	w2, [x1, x2]
	ldr	w1, [x3, 4]
	str	w2, [x0, 640]
	cmp	w1, 1
	str	w1, [x0, 644]
	beq	.L513
	mov	w1, -1
	str	w1, [x0, 648]
.L511:
	str	w1, [x0, 652]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L513:
	ldp	w2, w1, [x3, 8]
	str	w2, [x0, 648]
	b	.L511
	.p2align 3
.L512:
	add	x2, x0, 1280
	mov	w1, -1
	stp	wzr, wzr, [x2]
	stp	w1, w1, [x2, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_ConfigChanCompress, .-VCTRL_ConfigChanCompress
	.align	3
.LC369:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SeekPts
	.type	VCTRL_SeekPts, %function
VCTRL_SeekPts:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x0, .LC371
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L520
	ldr	w0, [x0, 632]
	sub	w2, w0, #10
	cmp	w2, 2
	bls	.L521
.L517:
	cmp	w0, 14
	ccmp	w0, 4, 4, ne
	beq	.L519
	mov	x1, x20
	mov	w0, w19
	bl	SM_SeekPts
	cmp	w0, wzr
	csetm	w0, ne
.L516:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L521:
	ldr	x1, .LC375
	ldr	w1, [x1, 2064]
	tbnz	x1, 0, .L517
.L519:
	mov	w0, -1
	b	.L516
.L520:
	ldr	x2, .LC373
	mov	w3, 2825
	ldr	x4, .LC372
	ldr	x1, .LC374
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L516
	.size	VCTRL_SeekPts, .-VCTRL_SeekPts
	.align	3
.LC371:
	.xword	.LANCHOR1
	.align	3
.LC372:
	.xword	.LC9
	.align	3
.LC373:
	.xword	.LANCHOR0
	.align	3
.LC374:
	.xword	.LC6
	.align	3
.LC375:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ReleaseStream
	.type	VCTRL_ReleaseStream, %function
VCTRL_ReleaseStream:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L526
	ldr	x0, .LC380
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L527
	mov	w0, w19
	bl	SM_Reset
	cmp	w0, wzr
	csetm	w0, ne
.L524:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L526:
	ldr	x2, .LC378
	mov	w3, 3070
	ldr	x4, .LC377
	mov	w0, 0
	ldr	x1, .LC379
	add	x2, x2, 464
	bl	dprint_vfmw
	mov	w0, -1
	b	.L524
.L527:
	ldr	x2, .LC378
	mov	w3, 3071
	ldr	x4, .LC382
	ldr	x1, .LC379
	add	x2, x2, 464
	bl	dprint_vfmw
	mov	w0, -1
	b	.L524
	.size	VCTRL_ReleaseStream, .-VCTRL_ReleaseStream
	.align	3
.LC377:
	.xword	.LC376
	.align	3
.LC378:
	.xword	.LANCHOR0
	.align	3
.LC379:
	.xword	.LC6
	.align	3
.LC380:
	.xword	.LANCHOR1
	.align	3
.LC382:
	.xword	.LC381
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ImageOutputEnable
	.type	VCTRL_ImageOutputEnable, %function
VCTRL_ImageOutputEnable:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L531
	ldr	x20, .LC386
	mov	w0, 4
	ldr	x1, [x20, 24]
	blr	x1
	ldr	x1, .LC387
	mov	w0, 4
	ldr	w2, [x21]
	ldr	x1, [x1, w19, sxtw 3]
	str	w2, [x1, 12]
	ldr	x1, [x20, 32]
	blr	x1
	mov	w0, 0
.L530:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L531:
	ldr	x2, .LC384
	mov	w3, 3140
	ldr	x4, .LC383
	mov	w0, 0
	ldr	x1, .LC385
	add	x2, x2, 488
	bl	dprint_vfmw
	mov	w0, -1
	b	.L530
	.size	VCTRL_ImageOutputEnable, .-VCTRL_ImageOutputEnable
	.align	3
.LC383:
	.xword	.LC193
	.align	3
.LC384:
	.xword	.LANCHOR0
	.align	3
.LC385:
	.xword	.LC6
	.align	3
.LC386:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC387:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_TryToRelSpecialFrm
	.type	VCTRL_TryToRelSpecialFrm, %function
VCTRL_TryToRelSpecialFrm:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	w24, w0
	mov	x0, x30
	mov	w22, w1
	bl	_mcount
	cmp	w24, 31
	bhi	.L566
	ldr	x19, .LC391
	ldr	x3, [x19, w24, sxtw 3]
	cbz	x3, .L567
	add	x0, x3, 507904
	ldr	w1, [x0, 1672]
	cbz	w1, .L536
	ldr	w0, [x0, 1148]
	mov	w2, 0
	cmp	w22, w0
	bne	.L539
	b	.L568
	.p2align 3
.L540:
	add	x0, x0, 3143
	add	x0, x3, x0, lsl 4
	ldr	w0, [x0, 12]
	cmp	w22, w0
	beq	.L537
.L539:
	add	w2, w2, 1
	cmp	w1, w2
	mov	w20, w2
	sxtw	x0, w2
	add	x0, x0, 28672
	bne	.L540
.L536:
	mov	w0, -1
.L559:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L568:
	mov	w20, 0
	.p2align 2
.L537:
	add	x0, x3, 495616
	mov	w21, 1
	add	x0, x0, 4024
	ldr	w2, [x0, -88]
	cmp	w2, w22
	bne	.L544
	b	.L569
	.p2align 3
.L541:
	add	w21, w21, 1
	cmp	w21, 32
	beq	.L570
.L544:
	ldr	w2, [x0]
	add	x0, x0, 88
	cmp	w22, w2
	bne	.L541
.L547:
	ldr	x25, .LC392
	sub	w22, w1, #1
	mov	w0, 3
	sxtw	x21, w21
	ldr	x1, [x25, 24]
	blr	x1
	lsl	x0, x21, 2
	ldr	x3, [x19, w24, sxtw 3]
	sub	x0, x0, x21
	ldr	x2, [x25, 32]
	lsl	x1, x0, 2
	mov	w0, 3
	sub	x21, x1, x21
	add	x1, x3, x21, lsl 3
	add	x3, x1, 495616
	add	x1, x1, 499712
	strb	wzr, [x3, 3930]
	strb	wzr, [x1, 2650]
	blr	x2
	cmp	w22, w20
	bls	.L551
	sxtw	x21, w24
	uxtw	x23, w20
	.p2align 2
.L543:
	add	w20, w20, 1
	add	x23, x23, 28672
	add	x0, x23, 3143
	ldr	x3, [x19, x21, lsl 3]
	uxtw	x23, w20
	ldr	x4, [x25, 104]
	add	x1, x23, 28672
	add	x0, x3, x0, lsl 4
	add	x1, x1, 3143
	mov	x2, 16
	add	x0, x0, 8
	add	x1, x3, x1, lsl 4
	add	x1, x1, 8
	blr	x4
	cmp	w20, w22
	bcc	.L543
.L542:
	uxtw	x0, w22
	ldr	x4, [x19, w24, sxtw 3]
	add	x0, x0, 28672
	ldr	x3, [x25, 96]
	add	x0, x0, 3143
	mov	x2, 16
	mov	w1, 0
	add	x0, x4, x0, lsl 4
	add	x0, x0, 8
	blr	x3
	ldr	x1, [x19, w24, sxtw 3]
	mov	w0, 0
	add	x1, x1, 507904
	ldr	w2, [x1, 1672]
	sub	w2, w2, #1
	str	w2, [x1, 1672]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L570:
	add	x2, x3, 475136
	ldr	x20, .LC389
	ldr	x1, .LC396
	mov	w3, 3295
	add	x20, x20, 512
	mov	w0, 1
	ldrsb	w4, [x2, 2251]
	mov	x2, x20
	bl	dprint_vfmw
	ldr	x6, [x19, w24, sxtw 3]
	add	x0, x6, 475136
	ldrsb	w0, [x0, 2251]
	cmp	w0, wzr
	ble	.L536
	ldr	x22, .LC394
	mov	w23, 0
	sxtw	x21, w24
	.p2align 2
.L546:
	sxtw	x4, w23
	mov	w0, 1
	lsl	x5, x4, 2
	mov	w3, 3298
	sub	x5, x5, x4
	mov	x2, x20
	lsl	x5, x5, 2
	mov	x1, x22
	sub	x4, x5, x4
	add	w23, w23, w0
	add	x4, x6, x4, lsl 3
	add	x4, x4, 495616
	ldr	w4, [x4, 3936]
	bl	dprint_vfmw
	ldr	x6, [x19, x21, lsl 3]
	add	x0, x6, 475136
	ldrsb	w0, [x0, 2251]
	cmp	w0, w23
	bgt	.L546
	b	.L536
.L566:
	ldr	x2, .LC389
	mov	w3, 3260
	ldr	x4, .LC388
	mov	w0, 0
	ldr	x1, .LC390
	add	x2, x2, 512
	bl	dprint_vfmw
	mov	w0, -1
	b	.L559
.L551:
	mov	w22, w20
	b	.L542
.L569:
	mov	w21, 0
	b	.L547
.L567:
	ldr	x2, .LC389
	mov	w3, 3261
	ldr	x4, .LC388
	mov	w0, 0
	ldr	x1, .LC390
	add	x2, x2, 512
	bl	dprint_vfmw
	mov	w0, -1
	b	.L559
	.size	VCTRL_TryToRelSpecialFrm, .-VCTRL_TryToRelSpecialFrm
	.align	3
.LC388:
	.xword	.LC193
	.align	3
.LC389:
	.xword	.LANCHOR0
	.align	3
.LC390:
	.xword	.LC6
	.align	3
.LC391:
	.xword	.LANCHOR1
	.align	3
.LC392:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC394:
	.xword	.LC393
	.align	3
.LC396:
	.xword	.LC395
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanImage
	.type	VCTRL_GetChanImage, %function
VCTRL_GetChanImage:
	sub	sp, sp, #640
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 31
	bhi	.L602
	ldr	x21, .LC401
	ldr	x0, [x21, w20, sxtw 3]
	cbz	x0, .L603
	cbz	x19, .L604
	ldr	x22, .LC405
	mov	w0, 4
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x0, [x21, w20, sxtw 3]
	cbz	x0, .L605
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L606
	ldr	w1, [x0, 12]
	cmp	w1, 1
	bne	.L607
	add	x0, x0, 507904
	mov	x1, x19
	add	x0, x0, 1744
	bl	SYNTAX_ReceiveImage
	cmp	w0, 1
	mov	w24, w0
	beq	.L608
	mov	w0, 9
	mov	w23, -1
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L591
.L590:
	ldr	x1, [x21, w20, sxtw 3]
	mov	w0, 4
	ldr	x2, [x22, 32]
	add	x1, x1, 524288
	ldrb	w1, [x1, 1256]
	strb	w1, [x19, 392]
	blr	x2
.L600:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, w23
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 640
	ret
	.p2align 3
.L608:
	ldr	w1, [x19, 192]
	mov	w0, -1
	str	w0, [x19, 188]
	cmp	w1, 1
	beq	.L609
.L580:
	mov	w0, 9
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L610
	ldr	x0, [x21, w20, sxtw 3]
	mov	w23, 0
	ldr	w1, [x19, 64]
	str	w1, [x0, 464]
	ldr	w1, [x19, 276]
	str	w1, [x0, 468]
	b	.L590
	.p2align 3
.L614:
	ldr	x0, [x21, w20, sxtw 3]
	add	x1, x29, 64
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReceiveImage
	cmp	w0, 1
	bne	.L611
	ldr	w0, [x19, 184]
	ldr	w1, [x29, 248]
	cmp	w0, w1
	bge	.L583
	ldp	w3, w4, [x29, 84]
	ldp	w2, w1, [x29, 92]
	ldr	w0, [x29, 212]
	mov	w5, 3
	ldr	w23, [x29, 244]
	mov	w24, 1
	str	w0, [x19, 188]
	stp	w3, w4, [x19, 196]
	stp	w2, w1, [x19, 204]
	str	w5, [x19, 276]
	cbz	w23, .L588
	mov	w23, 0
	str	w24, [x19, 180]
.L588:
	mov	w0, 9
	bl	CHECK_REC_POS_ENABLE
	cbz	w0, .L589
	.p2align 2
.L591:
	ldr	x0, [x22]
	blr	x0
	mov	w3, w0
	ldr	x1, .LC418
	ldr	x0, .LC419
	add	x1, x1, 2072
	ldr	w2, [x0]
	ldr	w0, [x1, w20, sxtw 2]
	sub	w0, w3, w0
	cmp	w0, w2
	bhi	.L612
.L589:
	cbnz	w23, .L590
.L613:
	ldr	x0, [x21, w20, sxtw 3]
	mov	w23, 0
	ldr	w1, [x19, 64]
	str	w1, [x0, 464]
	ldr	w1, [x19, 276]
	str	w1, [x0, 468]
	b	.L590
	.p2align 3
.L610:
	mov	w23, 0
	b	.L591
	.p2align 3
.L612:
	lsl	w2, w20, 24
	ldr	x0, .LC399
	add	w2, w2, 589824
	cmp	w24, 1
	str	w3, [x1, w20, sxtw 2]
	csinc	w2, w2, w2, ne
	add	x0, x0, 568
	mov	w1, 3573
	bl	DBG_AddTrace
	cbz	w23, .L613
	b	.L590
	.p2align 3
.L609:
	ldr	w1, [x19, 180]
	cbz	w1, .L614
	ldp	w2, w3, [x19, 20]
	mov	w1, 3
	str	w24, [x19, 180]
	str	w0, [x19, 188]
	stp	w2, w3, [x19, 196]
	str	w1, [x19, 276]
	b	.L580
	.p2align 3
.L607:
	ldr	x1, [x22, 32]
	mov	w0, 4
	mov	w23, -1
	blr	x1
	ldr	x2, .LC399
	mov	w0, 0
	ldr	x1, .LC411
	add	x2, x2, 544
	bl	dprint_vfmw
	b	.L600
	.p2align 3
.L606:
	ldr	x1, [x22, 32]
	mov	w0, 4
	mov	w23, -1
	blr	x1
	ldr	x1, .LC409
	mov	w2, w20
	mov	w0, 0
	bl	dprint_vfmw
	b	.L600
	.p2align 3
.L602:
	ldr	x2, .LC399
	mov	w3, 3420
	ldr	x4, .LC398
	mov	w0, 0
	ldr	x1, .LC400
	add	x2, x2, 544
	mov	w23, -1
	bl	dprint_vfmw
	b	.L600
	.p2align 3
.L611:
	ldr	x1, [x21, w20, sxtw 3]
	mov	w23, w0
	add	x0, x1, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReturnImage
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
	b	.L600
.L583:
	bgt	.L615
	cbnz	w0, .L586
	ldr	x0, [x21, w20, sxtw 3]
	mov	w23, -1
	mov	w24, -2
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReturnImage
	ldr	x0, [x21, w20, sxtw 3]
	mov	x1, x19
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReleaseImage
	ldr	x2, .LC399
	mov	w0, 1
	ldr	x1, .LC415
	ldr	w3, [x19, 184]
	add	x2, x2, 544
	bl	dprint_vfmw
	b	.L588
.L604:
	ldr	x2, .LC399
	mov	w3, 3422
	ldr	x4, .LC404
	mov	w0, 0
	ldr	x1, .LC400
	add	x2, x2, 544
	mov	w23, -1
	bl	dprint_vfmw
	b	.L600
.L586:
	ldr	x0, [x21, w20, sxtw 3]
	mov	x1, x19
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReleaseImage
	ldr	w0, [x29, 244]
	cbz	w0, .L616
	ldr	x2, .LC399
	mov	w0, 1
	ldr	x1, .LC417
	ldr	w3, [x19, 184]
	add	x2, x2, 544
	bl	dprint_vfmw
	ldr	x3, [x22, 104]
	mov	x2, 640
	add	x1, x29, 64
	mov	x0, x19
	blr	x3
	ldp	w3, w4, [x29, 84]
	mov	w2, -1
	mov	w1, 3
	mov	w0, 1
	str	w2, [x19, 188]
	str	w0, [x19, 180]
	stp	w3, w4, [x19, 196]
	str	w1, [x19, 276]
	b	.L580
.L615:
	ldr	x0, [x21, w20, sxtw 3]
	mov	w23, -1
	mov	w24, -2
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReturnImage
	ldr	x0, [x21, w20, sxtw 3]
	mov	x1, x19
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReleaseImage
	ldr	x2, .LC399
	mov	w0, 1
	ldr	x1, .LC413
	ldr	w3, [x19, 184]
	add	x2, x2, 544
	ldr	w4, [x29, 248]
	bl	dprint_vfmw
	b	.L588
.L603:
	ldr	x2, .LC399
	mov	w3, 3421
	ldr	x4, .LC402
	mov	w23, -1
	ldr	x1, .LC400
	add	x2, x2, 544
	bl	dprint_vfmw
	b	.L600
.L605:
	ldr	x1, [x22, 32]
	mov	w0, 4
	mov	w23, -1
	blr	x1
	ldr	x1, .LC407
	mov	w2, 3429
	mov	w0, 0
	bl	dprint_vfmw
	b	.L600
.L616:
	ldr	x0, [x21, w20, sxtw 3]
	add	x1, x29, 64
	mov	w23, -1
	mov	w24, -2
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReleaseImage
	ldr	x2, .LC399
	mov	w0, 1
	ldr	x1, .LC417
	ldr	w3, [x19, 184]
	add	x2, x2, 544
	bl	dprint_vfmw
	b	.L588
	.size	VCTRL_GetChanImage, .-VCTRL_GetChanImage
	.align	3
.LC398:
	.xword	.LC193
	.align	3
.LC399:
	.xword	.LANCHOR0
	.align	3
.LC400:
	.xword	.LC6
	.align	3
.LC401:
	.xword	.LANCHOR1
	.align	3
.LC402:
	.xword	.LC9
	.align	3
.LC404:
	.xword	.LC403
	.align	3
.LC405:
	.xword	vfmw_Osal_Func_Ptr_S
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
.LC418:
	.xword	.LANCHOR3
	.align	3
.LC419:
	.xword	g_TraceImgPeriod
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ReleaseChanImage
	.type	VCTRL_ReleaseChanImage, %function
VCTRL_ReleaseChanImage:
	sub	sp, sp, #640
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L638
	ldr	x21, .LC424
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L639
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L640
	cbz	x20, .L641
	ldr	x22, .LC429
	mov	w0, 4
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L642
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L643
	ldr	w1, [x20, 20]
	mov	w0, w19
	bl	VCTRL_TryToRelSpecialFrm
	cbz	w0, .L644
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x20
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReleaseImage
	mov	w23, w0
	ldr	w2, [x20, 188]
	cmn	w2, #1
	beq	.L626
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x29, 64
	str	w2, [x29, 212]
	add	x0, x0, 507904
	add	x0, x0, 1744
	bl	SYNTAX_ReleaseImage
	mov	w23, w0
.L626:
	mov	w0, 10
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L645
.L628:
	cmp	w23, 1
	csetm	w19, ne
	cbnz	w19, .L646
.L630:
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
.L619:
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 640
	ret
	.p2align 3
.L644:
	ldr	x1, [x22, 32]
	mov	w0, 4
	mov	w19, 0
	blr	x1
	ldr	x1, .LC434
	mov	w2, 3646
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x21, x22, [sp, 32]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	add	sp, sp, 640
	ret
	.p2align 3
.L646:
	ldr	x2, .LC422
	mov	w0, 0
	ldr	x1, .LC438
	add	x2, x2, 592
	bl	dprint_vfmw
	b	.L630
	.p2align 3
.L645:
	ldr	x0, [x22]
	blr	x0
	mov	w4, w0
	ldr	x3, .LC435
	ldr	x0, .LC436
	add	x3, x3, 2200
	ldr	w1, [x0]
	ldr	w0, [x3, w19, sxtw 2]
	sub	w0, w4, w0
	cmp	w0, w1
	bls	.L628
	lsl	w2, w19, 24
	ldr	x0, .LC422
	cmp	w23, 1
	add	w2, w2, 655360
	csinc	w2, w2, w2, ne
	mov	w1, 3675
	add	x0, x0, 616
	str	w4, [x3, w19, sxtw 2]
	bl	DBG_AddTrace
	b	.L628
	.p2align 3
.L643:
	ldr	x1, .LC432
	mov	w2, 3634
	mov	w0, 0
.L637:
	bl	dprint_vfmw
	mov	w19, -1
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
	b	.L619
	.p2align 3
.L640:
	ldr	x2, .LC422
	mov	w3, 3618
	ldr	x4, .LC427
	mov	w0, 0
	ldr	x1, .LC423
	add	x2, x2, 592
	mov	w19, -1
	bl	dprint_vfmw
	b	.L619
	.p2align 3
.L638:
	ldr	x2, .LC422
	mov	w3, 3616
	ldr	x4, .LC421
	mov	w0, 0
	ldr	x1, .LC423
	add	x2, x2, 592
	mov	w19, -1
	bl	dprint_vfmw
	b	.L619
.L641:
	ldr	x2, .LC422
	mov	w3, 3619
	ldr	x4, .LC428
	mov	w0, 0
	ldr	x1, .LC423
	add	x2, x2, 592
	mov	w19, -1
	bl	dprint_vfmw
	b	.L619
.L639:
	ldr	x2, .LC422
	mov	w3, 3617
	ldr	x4, .LC425
	mov	w19, -1
	ldr	x1, .LC423
	add	x2, x2, 592
	bl	dprint_vfmw
	b	.L619
.L642:
	ldr	x1, .LC430
	mov	w2, 3625
	b	.L637
	.size	VCTRL_ReleaseChanImage, .-VCTRL_ReleaseChanImage
	.align	3
.LC421:
	.xword	.LC193
	.align	3
.LC422:
	.xword	.LANCHOR0
	.align	3
.LC423:
	.xword	.LC6
	.align	3
.LC424:
	.xword	.LANCHOR1
	.align	3
.LC425:
	.xword	.LC9
	.align	3
.LC427:
	.xword	.LC426
	.align	3
.LC428:
	.xword	.LC403
	.align	3
.LC429:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC430:
	.xword	.LC406
	.align	3
.LC432:
	.xword	.LC431
	.align	3
.LC434:
	.xword	.LC433
	.align	3
.LC435:
	.xword	.LANCHOR3
	.align	3
.LC436:
	.xword	g_TraceImgPeriod
	.align	3
.LC438:
	.xword	.LC437
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetVidStd
	.type	VCTRL_GetVidStd, %function
VCTRL_GetVidStd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L648
	ldr	x0, .LC440
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L648
	ldr	w1, [x0, 4]
	cmp	w1, 1
	beq	.L651
	ldr	x1, .LC444
	mov	w3, w19
	mov	w2, 3702
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 22
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L648:
	ldr	x1, .LC442
	mov	w2, 3696
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 22
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L651:
	ldr	w0, [x0, 632]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetVidStd, .-VCTRL_GetVidStd
	.align	3
.LC440:
	.xword	.LANCHOR1
	.align	3
.LC442:
	.xword	.LC441
	.align	3
.LC444:
	.xword	.LC443
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetHDRConfigInfo
	.type	VCTRL_GetHDRConfigInfo, %function
VCTRL_GetHDRConfigInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L657
	ldr	x0, .LC448
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L658
	cbz	x20, .L659
	ldrb	w1, [x1, 44]
	strb	w1, [x20, 65]
	ldr	x1, [x0, w19, sxtw 3]
	ldrb	w1, [x1, 46]
	strb	w1, [x20, 66]
	ldr	x1, [x0, w19, sxtw 3]
	ldr	w1, [x1, 156]
	str	w1, [x20, 76]
	ldr	x1, [x0, w19, sxtw 3]
	ldr	w1, [x1, 160]
	str	w1, [x20, 68]
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 164]
	str	w0, [x20, 72]
.L652:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L657:
	ldr	x2, .LC446
	mov	w3, 3711
	ldr	x4, .LC445
	mov	w0, 0
	ldr	x1, .LC447
	add	x2, x2, 640
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L658:
	ldr	x2, .LC446
	mov	w3, 3712
	ldr	x4, .LC449
	mov	w0, 0
	ldr	x1, .LC447
	add	x2, x2, 640
	bl	dprint_vfmw
	b	.L652
	.p2align 3
.L659:
	ldr	x2, .LC446
	mov	w3, 3713
	ldr	x4, .LC451
	mov	w0, 0
	ldr	x1, .LC447
	add	x2, x2, 640
	bl	dprint_vfmw
	b	.L652
	.size	VCTRL_GetHDRConfigInfo, .-VCTRL_GetHDRConfigInfo
	.align	3
.LC445:
	.xword	.LC193
	.align	3
.LC446:
	.xword	.LANCHOR0
	.align	3
.LC447:
	.xword	.LC6
	.align	3
.LC448:
	.xword	.LANCHOR1
	.align	3
.LC449:
	.xword	.LC9
	.align	3
.LC451:
	.xword	.LC450
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetDecParam
	.type	VCTRL_GetDecParam, %function
VCTRL_GetDecParam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L683
	ldr	x0, .LC452
	ldr	x20, [x0, w19, sxtw 3]
	cbz	x20, .L683
	ldr	w0, [x20, 4]
	mov	x1, 0
	cmp	w0, 1
	bne	.L661
	ldr	w0, [x20, 8]
	cmp	w0, 1
	bne	.L661
	ldr	w3, [x20, 632]
	cmp	w3, 18
	bls	.L684
.L662:
	ldr	x2, .LC454
	mov	w0, 0
	ldr	x1, .LC456
	add	x2, x2, 664
	bl	dprint_vfmw
	mov	x1, 0
	b	.L661
	.p2align 3
.L683:
	mov	x1, 0
.L661:
	mov	x0, x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L684:
	ldr	x0, .LC453
	ldrb	w0, [x0,w3,uxtw]
	adr	x1, .Lrtx664
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx664:
	.section	.rodata
	.align	0
	.align	2
.L664:
	.byte	(.L663 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L666 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L662 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L669 - .Lrtx664) / 4
	.byte	(.L662 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L662 - .Lrtx664) / 4
	.byte	(.L674 - .Lrtx664) / 4
	.byte	(.L675 - .Lrtx664) / 4
	.byte	(.L672 - .Lrtx664) / 4
	.byte	(.L677 - .Lrtx664) / 4
	.text
	.p2align 3
.L672:
	add	x0, x20, 507904
	ldr	x19, [x0, 1760]
.L678:
	cbz	x19, .L683
	ldr	x0, .LC457
	ldr	x0, [x0]
	blr	x0
	str	w0, [x20, 40]
	mov	x1, x19
	mov	x0, x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L669:
	add	x0, x20, 507904
	ldr	x19, [x0, 1776]
	b	.L678
	.p2align 3
.L674:
	add	x0, x20, 507904
	ldr	x19, [x0, 1984]
	b	.L678
	.p2align 3
.L675:
	add	x0, x20, 512000
	ldr	x19, [x0, 712]
	b	.L678
	.p2align 3
.L666:
	add	x0, x20, 507904
	ldr	x19, [x0, 2792]
	b	.L678
	.p2align 3
.L677:
	add	x0, x20, 507904
	ldr	x19, [x0, 1800]
	b	.L678
	.p2align 3
.L663:
	add	x0, x20, 507904
	ldr	x19, [x0, 2368]
	b	.L678
	.size	VCTRL_GetDecParam, .-VCTRL_GetDecParam
	.align	3
.LC452:
	.xword	.LANCHOR1
	.align	3
.LC453:
	.xword	.L664
	.align	3
.LC454:
	.xword	.LANCHOR0
	.align	3
.LC456:
	.xword	.LC455
	.align	3
.LC457:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IsSedOnlyMode
	.type	VCTRL_IsSedOnlyMode, %function
VCTRL_IsSedOnlyMode:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L693
	cbz	w20, .L688
	cmp	w20, 16
	beq	.L689
	mov	w0, 0
.L687:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L689:
	ldr	w0, [x19, 5188]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	uxtb	w0, w0
	ret
	.p2align 3
.L688:
	ldrb	w0, [x19, 1188]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L693:
	ldr	x1, .LC459
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L687
	.size	VCTRL_IsSedOnlyMode, .-VCTRL_IsSedOnlyMode
	.align	3
.LC459:
	.xword	.LC458
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ClearDecparam
	.type	VCTRL_ClearDecparam, %function
VCTRL_ClearDecparam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L712
	ldr	x0, .LC464
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w1, [x0, 632]
	cmp	w1, 18
	bls	.L713
.L694:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L713:
	ldr	x2, .LC465
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx698
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx698:
	.section	.rodata
	.align	0
	.align	2
.L698:
	.byte	(.L697 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L700 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L694 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L703 - .Lrtx698) / 4
	.byte	(.L694 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L694 - .Lrtx698) / 4
	.byte	(.L708 - .Lrtx698) / 4
	.byte	(.L709 - .Lrtx698) / 4
	.byte	(.L707 - .Lrtx698) / 4
	.byte	(.L711 - .Lrtx698) / 4
	.text
	.p2align 3
.L707:
	add	x0, x0, 507904
	str	xzr, [x0, 1760]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L712:
	ldr	x4, .LC461
	mov	w3, 4161
	ldr	x2, .LC462
	mov	w0, 0
	ldr	x1, .LC463
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L703:
	add	x0, x0, 507904
	str	xzr, [x0, 1776]
	b	.L694
	.p2align 3
.L708:
	add	x0, x0, 507904
	str	xzr, [x0, 1984]
	b	.L694
	.p2align 3
.L709:
	add	x0, x0, 512000
	str	xzr, [x0, 712]
	b	.L694
	.p2align 3
.L700:
	add	x0, x0, 507904
	str	xzr, [x0, 2792]
	b	.L694
	.p2align 3
.L711:
	add	x0, x0, 507904
	str	xzr, [x0, 1800]
	b	.L694
	.p2align 3
.L697:
	add	x0, x0, 507904
	str	xzr, [x0, 2368]
	b	.L694
	.size	VCTRL_ClearDecparam, .-VCTRL_ClearDecparam
	.align	3
.LC461:
	.xword	.LC460
	.align	3
.LC462:
	.xword	.LANCHOR4
	.align	3
.LC463:
	.xword	.LC6
	.align	3
.LC464:
	.xword	.LANCHOR1
	.align	3
.LC465:
	.xword	.L698
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_VdmProcSedOnly
	.type	VCTRL_VdmProcSedOnly, %function
VCTRL_VdmProcSedOnly:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L724
	ldr	x20, .LC470
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L725
	ldr	w0, [x0, 8]
	cmp	w0, 1
	beq	.L718
	ldr	x2, .LC468
	mov	w3, 4241
	ldr	x4, .LC473
	mov	w0, 0
	ldr	x1, .LC469
	add	x2, x2, 24
	bl	dprint_vfmw
.L714:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L718:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbz	x0, .L714
	ldr	x0, [x20, w19, sxtw 3]
	ldr	w1, [x0, 632]
	cbz	w1, .L719
	cmp	w1, 16
	bne	.L714
	add	x0, x0, 507904
	mov	w1, w21
	add	x0, x0, 1752
	bl	HEVCDEC_VDMProcSedOnly
	b	.L714
	.p2align 3
.L724:
	ldr	x2, .LC468
	mov	w3, 4239
	ldr	x4, .LC467
	mov	w0, 0
	ldr	x1, .LC469
	add	x2, x2, 24
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L719:
	add	x0, x0, 507904
	mov	w1, w21
	add	x0, x0, 1752
	bl	H264DEC_VDMProcSedOnly
	b	.L714
	.p2align 3
.L725:
	ldr	x2, .LC468
	mov	w3, 4240
	ldr	x4, .LC471
	ldr	x1, .LC469
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L714
	.size	VCTRL_VdmProcSedOnly, .-VCTRL_VdmProcSedOnly
	.align	3
.LC467:
	.xword	.LC466
	.align	3
.LC468:
	.xword	.LANCHOR4
	.align	3
.LC469:
	.xword	.LC6
	.align	3
.LC470:
	.xword	.LANCHOR1
	.align	3
.LC471:
	.xword	.LC426
	.align	3
.LC473:
	.xword	.LC472
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetImageBuffer
	.type	VCTRL_GetImageBuffer, %function
VCTRL_GetImageBuffer:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L750
	ldr	x0, .LC477
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L751
	ldr	w0, [x1, 8]
	cmp	w0, 1
	bne	.L752
	ldr	w2, [x1, 632]
	cmp	w2, 18
	bls	.L753
.L746:
	mov	w0, 0
	b	.L728
	.p2align 3
.L753:
	ldr	x3, .LC480
	ldrb	w2, [x3,w2,uxtw]
	adr	x3, .Lrtx732
	add	x2, x3, w2, sxtb #2
	br	x2
.Lrtx732:
	.section	.rodata
	.align	0
	.align	2
.L732:
	.byte	(.L731 - .Lrtx732) / 4
	.byte	(.L733 - .Lrtx732) / 4
	.byte	(.L734 - .Lrtx732) / 4
	.byte	(.L735 - .Lrtx732) / 4
	.byte	(.L746 - .Lrtx732) / 4
	.byte	(.L736 - .Lrtx732) / 4
	.byte	(.L737 - .Lrtx732) / 4
	.byte	(.L746 - .Lrtx732) / 4
	.byte	(.L738 - .Lrtx732) / 4
	.byte	(.L739 - .Lrtx732) / 4
	.byte	(.L740 - .Lrtx732) / 4
	.byte	(.L740 - .Lrtx732) / 4
	.byte	(.L740 - .Lrtx732) / 4
	.byte	(.L741 - .Lrtx732) / 4
	.byte	(.L746 - .Lrtx732) / 4
	.byte	(.L742 - .Lrtx732) / 4
	.byte	(.L743 - .Lrtx732) / 4
	.byte	(.L744 - .Lrtx732) / 4
	.byte	(.L745 - .Lrtx732) / 4
	.text
	.p2align 3
.L745:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	AVS2DEC_GetImageBuffer
.L728:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L744:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	VP9DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L743:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	HEVCDEC_GetImageBuffer
	b	.L728
	.p2align 3
.L742:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	MVC_DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L741:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	VP8DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L740:
	ldr	x2, .LC481
	ldr	w2, [x2, 2064]
	tbz	x2, 0, .L728
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	VP6DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L739:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	REAL9DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L738:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	REAL8DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L737:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	AVSDEC_GetImageBuffer
	b	.L728
	.p2align 3
.L736:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	DIVX3DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L735:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	MPEG2DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L734:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	MPEG4DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L733:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	VC1DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L731:
	add	x0, x1, 507904
	add	x0, x0, 1752
	bl	H264DEC_GetImageBuffer
	b	.L728
	.p2align 3
.L752:
	ldr	x2, .LC475
	mov	w3, 4276
	ldr	x4, .LC479
	mov	w0, 0
	ldr	x1, .LC476
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L728
	.p2align 3
.L750:
	ldr	x2, .LC475
	mov	w3, 4274
	ldr	x4, .LC474
	mov	w0, 0
	ldr	x1, .LC476
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L728
.L751:
	ldr	x2, .LC475
	mov	w3, 4275
	ldr	x4, .LC478
	mov	w0, 0
	ldr	x1, .LC476
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L728
	.size	VCTRL_GetImageBuffer, .-VCTRL_GetImageBuffer
	.align	3
.LC474:
	.xword	.LC466
	.align	3
.LC475:
	.xword	.LANCHOR4
	.align	3
.LC476:
	.xword	.LC6
	.align	3
.LC477:
	.xword	.LANCHOR1
	.align	3
.LC478:
	.xword	.LC426
	.align	3
.LC479:
	.xword	.LC472
	.align	3
.LC480:
	.xword	.L732
	.align	3
.LC481:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ConfigFFFBSpeed
	.type	VCTRL_ConfigFFFBSpeed, %function
VCTRL_ConfigFFFBSpeed:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L760
	ldr	x0, .LC485
	ldr	x2, [x0, w19, sxtw 3]
	cbz	x2, .L761
	ldr	w0, [x2, 4]
	cmp	w0, 1
	bne	.L762
	cbz	x20, .L763
	ldr	w1, [x20]
	mov	w0, 0
	str	w1, [x2, 1300]
.L756:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L762:
	ldr	x2, .LC483
	mov	w3, 4392
	ldr	x4, .LC489
	mov	w0, 0
	ldr	x1, .LC484
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L756
	.p2align 3
.L760:
	ldr	x2, .LC483
	mov	w3, 4390
	ldr	x4, .LC482
	mov	w0, 0
	ldr	x1, .LC484
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L756
.L761:
	ldr	x2, .LC483
	mov	w3, 4391
	ldr	x4, .LC487
	mov	w0, 0
	ldr	x1, .LC484
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L756
.L763:
	ldr	x2, .LC483
	mov	w3, 4393
	ldr	x4, .LC491
	mov	w0, 0
	ldr	x1, .LC484
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L756
	.size	VCTRL_ConfigFFFBSpeed, .-VCTRL_ConfigFFFBSpeed
	.align	3
.LC482:
	.xword	.LC193
	.align	3
.LC483:
	.xword	.LANCHOR4
	.align	3
.LC484:
	.xword	.LC6
	.align	3
.LC485:
	.xword	.LANCHOR1
	.align	3
.LC487:
	.xword	.LC486
	.align	3
.LC489:
	.xword	.LC488
	.align	3
.LC491:
	.xword	.LC490
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ConfigPVRInfo
	.type	VCTRL_ConfigPVRInfo, %function
VCTRL_ConfigPVRInfo:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L770
	ldr	x0, .LC495
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L771
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L772
	cbz	x20, .L773
	ldr	x3, .LC499
	mov	x2, 20
	mov	x1, x20
	add	x0, x0, 1336
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L766:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L772:
	ldr	x2, .LC493
	mov	w3, 4405
	ldr	x4, .LC497
	mov	w0, 0
	ldr	x1, .LC494
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L766
	.p2align 3
.L770:
	ldr	x2, .LC493
	mov	w3, 4403
	ldr	x4, .LC492
	mov	w0, 0
	ldr	x1, .LC494
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L766
.L773:
	ldr	x2, .LC493
	mov	w3, 4406
	ldr	x4, .LC498
	mov	w0, 0
	ldr	x1, .LC494
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L766
.L771:
	ldr	x2, .LC493
	mov	w3, 4404
	ldr	x4, .LC496
	ldr	x1, .LC494
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L766
	.size	VCTRL_ConfigPVRInfo, .-VCTRL_ConfigPVRInfo
	.align	3
.LC492:
	.xword	.LC193
	.align	3
.LC493:
	.xword	.LANCHOR4
	.align	3
.LC494:
	.xword	.LC6
	.align	3
.LC495:
	.xword	.LANCHOR1
	.align	3
.LC496:
	.xword	.LC486
	.align	3
.LC497:
	.xword	.LC488
	.align	3
.LC498:
	.xword	.LC490
	.align	3
.LC499:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IsChanActive
	.type	VCTRL_IsChanActive, %function
VCTRL_IsChanActive:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L781
	ldr	x0, .LC503
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L780
	ldr	w1, [x0, 4]
	cbz	w1, .L780
	ldr	w1, [x0, 8]
	cbz	w1, .L780
	ldr	w1, [x0, 20]
	cbz	w1, .L780
	ldr	w0, [x0, 632]
	cmp	w0, 22
	csetm	w0, eq
.L776:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L780:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L781:
	ldr	x2, .LC501
	mov	w3, 4415
	ldr	x4, .LC500
	mov	w0, 0
	ldr	x1, .LC502
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -1
	b	.L776
	.size	VCTRL_IsChanActive, .-VCTRL_IsChanActive
	.align	3
.LC500:
	.xword	.LC193
	.align	3
.LC501:
	.xword	.LANCHOR4
	.align	3
.LC502:
	.xword	.LC6
	.align	3
.LC503:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	USERDEC_Init
	.type	USERDEC_Init, %function
USERDEC_Init:
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
	beq	.L798
	ldr	x3, .LC507
	mov	x2, 624
	mov	w1, 0
	mov	x0, x19
	ldr	w21, [x19, 608]
	ldr	x3, [x3, 96]
	blr	x3
	str	w21, [x19, 608]
	add	x0, x19, 8
	bl	ResetVoQueue
	str	x20, [x19]
	ldr	x3, .LC508
	mov	x0, 0
	b	.L787
	.p2align 3
.L785:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L799
.L787:
	ldr	x2, [x3, x0, lsl 3]
	add	x1, x2, 507904
	add	x1, x1, 1752
	cbz	x2, .L785
	cmp	x19, x1
	bne	.L785
	cmn	w0, #1
	str	w0, [x19, 616]
	mov	w0, 1
	beq	.L789
.L793:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L799:
	mov	w0, -1
	str	w0, [x19, 616]
.L789:
	ldr	x1, .LC510
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L793
.L798:
	ldr	x2, .LC504
	mov	w0, 0
	ldr	x1, .LC506
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, -20
	b	.L793
	.size	USERDEC_Init, .-USERDEC_Init
	.align	3
.LC504:
	.xword	.LANCHOR4
	.align	3
.LC506:
	.xword	.LC505
	.align	3
.LC507:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC508:
	.xword	.LANCHOR1
	.align	3
.LC510:
	.xword	.LC509
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	USERDEC_RecycleImage
	.type	USERDEC_RecycleImage, %function
USERDEC_RecycleImage:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cbz	x19, .L802
	ldr	w0, [x19, 616]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x19, 616]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L803
	ldr	w0, [x19, 616]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 616]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
.L801:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L803:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L802:
	mov	w0, -2
	b	.L801
	.size	USERDEC_RecycleImage, .-USERDEC_RecycleImage
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetUsrdecFrame
	.type	VCTRL_GetUsrdecFrame, %function
VCTRL_GetUsrdecFrame:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w20, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x23, .LC511
	ldr	x0, [x23, w20, sxtw 3]
	cbz	x0, .L818
	ldr	w1, [x0, 632]
	cmp	w1, 20
	bne	.L819
	ldr	w0, [x0, 556]
	cmp	w0, 2
	ble	.L820
	mov	w1, 1
	mov	w0, w20
	bl	FSP_NewLogicFs
	mov	w22, w0
	tbnz	w0, #31, .L821
	mov	w1, w0
	mov	w0, w20
	bl	FSP_GetLogicFs
	mov	x19, x0
	ldr	x1, .LC522
	mov	w2, w22
	mov	w0, 18
	bl	dprint_vfmw
	cbz	x19, .L822
	ldr	x0, [x19, 32]
	cbz	x0, .L811
	ldr	x1, [x19, 40]
	cbz	x1, .L811
	ldr	w2, [x0, 8]
	mov	w0, 18
	ldr	w3, [x1, 8]
	ldr	x1, .LC526
	bl	dprint_vfmw
	ldr	x0, [x19, 32]
	ldr	w0, [x0, 8]
	str	w0, [x21, 40]
	ldr	x0, [x23, w20, sxtw 3]
	ldr	w0, [x0, 552]
	str	w0, [x21, 20]
	ldr	x0, [x19, 32]
	ldr	w0, [x0, 20]
	str	w0, [x21, 24]
	ldr	x0, [x19, 32]
	ldr	w0, [x0, 20]
	bl	MEM_Phy2Vir
	str	x0, [x21, 32]
	mov	w1, 0
.L806:
	mov	w0, w1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L819:
	ldr	x1, .LC516
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L806
	.p2align 3
.L820:
	ldr	x1, .LC518
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L806
	.p2align 3
.L811:
	ldr	x1, .LC528
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L806
	.p2align 3
.L821:
	ldr	x1, .LC520
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L806
.L818:
	ldr	x2, .LC513
	mov	w3, 4607
	ldr	x1, .LC514
	ldr	x4, .LC512
	add	x2, x2, 160
	bl	dprint_vfmw
	mov	w1, -1
	b	.L806
.L822:
	ldr	x1, .LC524
	mov	w2, 4635
	mov	w0, 22
	bl	dprint_vfmw
	mov	w1, -1
	b	.L806
	.size	VCTRL_GetUsrdecFrame, .-VCTRL_GetUsrdecFrame
	.align	3
.LC511:
	.xword	.LANCHOR1
	.align	3
.LC512:
	.xword	.LC9
	.align	3
.LC513:
	.xword	.LANCHOR4
	.align	3
.LC514:
	.xword	.LC6
	.align	3
.LC516:
	.xword	.LC515
	.align	3
.LC518:
	.xword	.LC517
	.align	3
.LC520:
	.xword	.LC519
	.align	3
.LC522:
	.xword	.LC521
	.align	3
.LC524:
	.xword	.LC523
	.align	3
.LC526:
	.xword	.LC525
	.align	3
.LC528:
	.xword	.LC527
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	InitSyntaxCtx
	.type	InitSyntaxCtx, %function
InitSyntaxCtx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC529
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L842
	ldr	w0, [x1, 632]
	cmp	w0, 20
	bls	.L843
.L823:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L843:
	ldr	x2, .LC533
	ldrb	w0, [x2,w0,uxtw]
	adr	x2, .Lrtx827
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx827:
	.section	.rodata
	.align	0
	.align	2
.L827:
	.byte	(.L826 - .Lrtx827) / 4
	.byte	(.L828 - .Lrtx827) / 4
	.byte	(.L829 - .Lrtx827) / 4
	.byte	(.L830 - .Lrtx827) / 4
	.byte	(.L823 - .Lrtx827) / 4
	.byte	(.L831 - .Lrtx827) / 4
	.byte	(.L832 - .Lrtx827) / 4
	.byte	(.L823 - .Lrtx827) / 4
	.byte	(.L833 - .Lrtx827) / 4
	.byte	(.L834 - .Lrtx827) / 4
	.byte	(.L835 - .Lrtx827) / 4
	.byte	(.L835 - .Lrtx827) / 4
	.byte	(.L835 - .Lrtx827) / 4
	.byte	(.L836 - .Lrtx827) / 4
	.byte	(.L823 - .Lrtx827) / 4
	.byte	(.L837 - .Lrtx827) / 4
	.byte	(.L838 - .Lrtx827) / 4
	.byte	(.L839 - .Lrtx827) / 4
	.byte	(.L840 - .Lrtx827) / 4
	.byte	(.L823 - .Lrtx827) / 4
	.byte	(.L841 - .Lrtx827) / 4
	.text
	.p2align 3
.L841:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	USERDEC_Init
	b	.L823
	.p2align 3
.L840:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	AVS2DEC_Init
	b	.L823
	.p2align 3
.L839:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	VP9DEC_Init
	b	.L823
	.p2align 3
.L838:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	HEVCDEC_Init
	b	.L823
	.p2align 3
.L837:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	MVC_DEC_Init
	b	.L823
	.p2align 3
.L836:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	VP8DEC_Init
	b	.L823
	.p2align 3
.L835:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	VP6DEC_Init
	b	.L823
	.p2align 3
.L834:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	REAL9DEC_Init
	b	.L823
	.p2align 3
.L833:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	REAL8DEC_Init
	b	.L823
	.p2align 3
.L832:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	AVSDEC_Init
	b	.L823
	.p2align 3
.L831:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	DIVX3DEC_Init
	b	.L823
	.p2align 3
.L830:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	MPEG2DEC_Init
	b	.L823
	.p2align 3
.L829:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	MPEG4DEC_Init
	b	.L823
	.p2align 3
.L828:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	VC1DEC_Init
	b	.L823
	.p2align 3
.L826:
	add	x0, x1, 507904
	add	x1, x1, 640
	add	x0, x0, 1752
	bl	H264DEC_Init
	b	.L823
	.p2align 3
.L842:
	ldr	x2, .LC531
	mov	w3, 4684
	ldr	x4, .LC530
	mov	w0, 0
	ldr	x1, .LC532
	add	x2, x2, 184
	bl	dprint_vfmw
	b	.L823
	.size	InitSyntaxCtx, .-InitSyntaxCtx
	.align	3
.LC529:
	.xword	.LANCHOR1
	.align	3
.LC530:
	.xword	.LC9
	.align	3
.LC531:
	.xword	.LANCHOR4
	.align	3
.LC532:
	.xword	.LC6
	.align	3
.LC533:
	.xword	.L827
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_VarifyOption
	.type	VCTRL_VarifyOption, %function
VCTRL_VarifyOption:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 36]
	tbnz	w0, #31, .L845
	ldr	w0, [x19, 12]
	cmp	w0, 31
	ble	.L845
	ldr	w0, [x19, 16]
	cmp	w0, 31
	ble	.L845
	ldr	w1, [x19, 56]
	mov	w0, 262143
	cmp	w1, w0
	ble	.L845
	ldr	w0, [x19, 44]
	cmp	w0, 1
	beq	.L851
	cmp	w0, 2
	mov	w0, 0
	bne	.L847
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L845
	ldr	w0, [x19, 24]
	cmp	w0, wzr
	ble	.L845
.L850:
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L845
	ldr	w0, [x19, 32]
	cmp	w0, wzr
	bgt	.L852
.L845:
	ldr	x1, .LC535
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, -1
.L847:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L852:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L851:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	bgt	.L850
	b	.L845
	.size	VCTRL_VarifyOption, .-VCTRL_VarifyOption
	.align	3
.LC535:
	.xword	.LC534
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetMemSize_onDecode
	.type	VCTRL_GetMemSize_onDecode, %function
VCTRL_GetMemSize_onDecode:
	sub	sp, sp, #64
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	mov	x19, x1
	mov	w21, w0
	mov	x0, x30
	mov	x20, x2
	bl	_mcount
	ldp	w5, w0, [x19, 36]
	mov	w4, 1
	cbz	w0, .L855
	mov	w4, 17
	add	w0, w5, 1
	cmp	w0, w4
	csel	w4, w0, w4, le
.L855:
	ldr	x1, .LC536
	sub	w0, w21, #27
	mov	w7, -2
	cmp	w0, 5
	csinv	w7, w7, wzr, ls
	ldr	x8, [x1, 128]
	cbz	x8, .L859
	ldr	w0, [x19, 60]
	mov	w6, 0
	ldr	x22, .LC539
	mov	w1, 2147483647
	add	w5, w5, w0
	ldp	w2, w3, [x19, 12]
	add	x0, x22, 2328
	add	w5, w5, 2
	str	x0, [sp]
	mov	w0, 1
	blr	x8
	cbnz	w0, .L859
	cmp	w21, 26
	beq	.L869
	mov	w1, 47544
	movk	w1, 0xf, lsl 16
	mov	w2, w1
.L860:
	ldr	w0, [x22, 2328]
	add	w3, w0, 16
	str	w3, [x20]
	ldr	w3, [x19, 192]
	cmp	w3, 1
	beq	.L861
	add	w0, w0, 307200
	add	w0, w0, 2576
	str	w0, [x20]
	ldr	w0, [x19, 56]
	add	w0, w0, 32768
	str	w0, [x20, 4]
.L862:
	str	w2, [x20, 8]
	ldr	w0, [x19, 44]
	cbnz	w0, .L870
	mov	w0, 62160
	movk	w0, 0x13, lsl 16
.L863:
	add	sp, x29, 0
	add	w1, w0, w1
	str	w1, [x20, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L870:
	ldrsw	x4, [x19, 20]
	mov	w0, 4000
	ldp	w7, w6, [x19, 28]
	lsl	x5, x4, 7
	mov	w3, 2208
	sub	x4, x5, x4
	cmp	w21, 26
	lsl	x4, x4, 5
	smaddl	x0, w7, w0, x4
	smaddl	x2, w6, w3, x0
	beq	.L865
	mov	w0, 62160
	movk	w0, 0x13, lsl 16
	cmp	w2, w0
	csel	w0, w2, w0, cs
	b	.L863
	.p2align 3
.L859:
	ldr	x1, .LC538
	mov	w2, 4839
	mov	w0, 0
	bl	dprint_vfmw
	add	sp, x29, 0
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L861:
	ldr	w0, [x19, 56]
	add	w0, w0, 339968
	add	w0, w0, 2576
	str	w0, [x20, 4]
	b	.L862
	.p2align 3
.L869:
	mov	w1, 17992
	movk	w1, 0xb5, lsl 16
	mov	w2, w1
	b	.L860
	.p2align 3
.L865:
	mov	w5, 3992
	mov	w3, 2240
	and	x2, x2, 4294967295
	mov	w0, 62160
	smaddl	x4, w7, w5, x4
	movk	w0, 0x13, lsl 16
	smaddl	x6, w6, w3, x4
	cmp	x6, x2
	csel	x2, x6, x2, cs
	cmp	w2, w0
	csel	w0, w2, w0, cs
	b	.L863
	.size	VCTRL_GetMemSize_onDecode, .-VCTRL_GetMemSize_onDecode
	.align	3
.LC536:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC538:
	.xword	.LC537
	.align	3
.LC539:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanMemSize
	.type	VCTRL_GetChanMemSize, %function
VCTRL_GetChanMemSize:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w3
	mov	x19, x1
	mov	x22, x2
	bl	_mcount
	cmp	w20, 2
	beq	.L872
	ldr	x0, .LC541
	mov	w6, 16
	ldr	w2, [x19, 36]
	ldr	w4, [x19, 60]
	ldr	w3, [x0, 3560]
	ldr	w5, [x0, 3564]
	add	w0, w2, w3
	cmp	w0, w6
	add	w1, w4, w5
	csel	w0, w0, w6, le
	cmp	w0, wzr
	ccmp	w1, wzr, 1, ge
	blt	.L879
	str	w0, [x19, 36]
	str	w1, [x19, 60]
.L872:
	mov	x0, x19
	bl	VCTRL_VarifyOption
	cbnz	w0, .L875
	mov	x2, x22
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_GetMemSize_onDecode
.L874:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L875:
	mov	w0, -1
	b	.L874
	.p2align 3
.L879:
	ldr	x1, .LC543
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, -1
	b	.L874
	.size	VCTRL_GetChanMemSize, .-VCTRL_GetChanMemSize
	.align	3
.LC541:
	.xword	.LANCHOR3
	.align	3
.LC543:
	.xword	.LC542
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CloseDrivers
	.type	CloseDrivers, %function
CloseDrivers:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 96]
	cbz	w0, .L905
	ldr	w0, [x19, 112]
	cmp	w0, wzr
	cset	w21, ne
.L881:
	ldr	w20, [x19, 24]
	ldr	w22, [x19, 16]
	ldr	x23, [x19, 8]
	cbz	w20, .L882
	ldr	x0, .LC544
	ldr	x1, [x0, 120]
	cbz	x1, .L934
	mov	w0, 0
	blr	x1
	cbz	w21, .L885
.L886:
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
.L882:
	mov	w2, w20
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 88]
	ldr	w22, [x19, 80]
	ldr	x23, [x19, 72]
	cbz	w20, .L888
	ldr	x0, .LC544
	ldr	x1, [x0, 120]
	cbz	x1, .L935
	mov	w0, 0
	blr	x1
	cbz	w21, .L891
.L892:
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 64
	ldr	x3, [x3, 96]
	blr	x3
.L888:
	mov	w2, w20
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 56]
	ldr	w22, [x19, 48]
	ldr	x23, [x19, 40]
	cbnz	w20, .L936
.L894:
	mov	x1, x23
	mov	w2, w20
	mov	w0, w22
	bl	MEM_DelMemRecord
	bl	SM_InstInit
	ldr	w21, [x19, 144]
	ldr	w22, [x19, 136]
	ldr	x23, [x19, 128]
	cbnz	w21, .L937
.L897:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	add	x20, x19, 216
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 240]
	ldr	w22, [x19, 232]
	ldr	x23, [x19, 224]
	cbnz	w21, .L938
.L898:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 208]
	ldr	w22, [x19, 200]
	ldr	x23, [x19, 192]
	cbnz	w21, .L939
.L899:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	add	x20, x19, 152
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 176]
	ldr	w22, [x19, 168]
	ldr	x23, [x19, 160]
	cbnz	w21, .L940
.L900:
	mov	w2, w21
	mov	w0, w22
	mov	x1, x23
	add	x19, x19, 248
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 24]
	ldr	w21, [x19, 16]
	ldr	x22, [x19, 8]
	cbnz	w20, .L941
	mov	w2, w20
	mov	x1, x22
	mov	w0, w21
	bl	MEM_DelMemRecord
	ldr	x19, .LC547
	ldr	w0, [x19, 584]
	cmp	w0, 1
	beq	.L942
.L902:
	ldr	w0, [x19, 588]
	cmp	w0, 1
	beq	.L943
.L903:
	ldr	w0, [x19, 592]
	add	x19, x19, 256
	cmp	w0, 1
	beq	.L944
.L904:
	bl	HEVCDEC_ReleaseHevcGlbMem
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L936:
	mov	w0, 0
	bl	SM_CloseSCDDrv
	cbz	w21, .L895
.L896:
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, x2
	ldr	x3, [x3, 96]
	blr	x3
	b	.L894
	.p2align 3
.L937:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 120
	ldr	x3, [x3, 96]
	blr	x3
	b	.L897
	.p2align 3
.L941:
	mov	x1, x22
	mov	w0, w21
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	w2, w20
	mov	x1, x22
	mov	w0, w21
	bl	MEM_DelMemRecord
	ldr	x19, .LC547
	ldr	w0, [x19, 584]
	cmp	w0, 1
	bne	.L902
.L942:
	ldr	x1, .LC545
	mov	w0, 0
	ldr	x21, [x1, 416]
	bl	VFMW_GetString
	ldr	x2, .LC548
	mov	x1, x0
	mov	w0, 127
	add	x2, x2, 3568
	blr	x21
	str	wzr, [x19, 584]
	ldr	w0, [x19, 588]
	cmp	w0, 1
	bne	.L903
	.p2align 2
.L943:
	ldr	x1, .LC545
	mov	w0, 4
	add	x19, x19, 256
	ldr	x21, [x1, 416]
	bl	VFMW_GetString
	ldr	x2, .LC548
	mov	x1, x0
	mov	w0, 136
	add	x2, x2, 3568
	blr	x21
	str	wzr, [x19, 332]
	ldr	w0, [x19, 336]
	cmp	w0, 1
	bne	.L904
.L944:
	ldr	x1, .LC545
	mov	w0, 13
	ldr	x20, [x1, 416]
	bl	VFMW_GetString
	ldr	x2, .LC548
	mov	x1, x0
	mov	w0, 181
	add	x2, x2, 3568
	blr	x20
	str	wzr, [x19, 336]
	bl	HEVCDEC_ReleaseHevcGlbMem
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L940:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	b	.L900
	.p2align 3
.L939:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 184
	ldr	x3, [x3, 96]
	blr	x3
	b	.L899
	.p2align 3
.L938:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	b	.L898
	.p2align 3
.L934:
	ldr	x1, .LC546
	mov	w2, 5178
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w21, .L886
	.p2align 2
.L885:
	ldr	w0, [x19, 16]
	ldr	x1, [x19, 8]
	bl	MEM_ReleaseMemBlock
	b	.L886
	.p2align 3
.L935:
	ldr	x1, .LC546
	mov	w2, 5198
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w21, .L892
	.p2align 2
.L891:
	ldr	w0, [x19, 80]
	ldr	x1, [x19, 72]
	bl	MEM_ReleaseMemBlock
	b	.L892
	.p2align 3
.L905:
	mov	w21, 0
	b	.L881
	.p2align 3
.L895:
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_ReleaseMemBlock
	b	.L896
	.size	CloseDrivers, .-CloseDrivers
	.align	3
.LC544:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC545:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC546:
	.xword	.LC127
	.align	3
.LC547:
	.xword	.LANCHOR1
	.align	3
.LC548:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	OpenDrivers
	.type	OpenDrivers, %function
OpenDrivers:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x19, x0
	mov	x0, x30
	add	x20, x19, 120
	bl	_mcount
	mov	x2, x20
	mov	w1, 65536
	mov	w0, -121438208
	bl	MEM_MapRegisterAddr
	cbnz	w0, .L946
	ldr	w2, [x19, 144]
	add	x20, x19, 216
	ldr	x1, [x19, 128]
	ldr	w0, [x19, 136]
	bl	MEM_AddMemRecord
	mov	w0, 53248
	mov	x2, x20
	mov	w1, 4096
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_MapRegisterAddr
	cbz	w0, .L979
	mov	w2, 53248
	ldr	x1, .LC551
	movk	w2, 0xf8c3, lsl 16
.L972:
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, .LC552
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
.L973:
	ldr	x3, [x3, 96]
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
.L949:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L979:
	ldr	w2, [x20, 24]
	add	x21, x19, 184
	ldr	x1, [x20, 8]
	ldr	w0, [x20, 16]
	bl	MEM_AddMemRecord
	mov	w0, 49152
	mov	x2, x21
	mov	w1, 4096
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_MapRegisterAddr
	cbnz	w0, .L950
	ldr	w2, [x19, 208]
	ldr	x1, [x19, 192]
	ldr	w0, [x19, 200]
	bl	MEM_AddMemRecord
	ldr	x20, .LC552
	mov	w0, 15
	ldr	x22, [x20, 136]
	bl	VFMW_GetString
	mov	w3, 0
	mov	x2, x0
	mov	x1, 20
	add	x0, x29, 96
	blr	x22
	ldr	x22, .LC553
	ldr	x0, [x22, 96]
	cbz	x0, .L952
	blr	x0
	cmp	w0, wzr
	mov	w2, w0
	ble	.L952
	mov	w21, 3
	mov	w4, 0
	mov	x3, x19
	mov	w1, 0
	add	x0, x29, 96
	str	w21, [x19, 28]
	bl	MEM_AllocMemBlock
	cbnz	w0, .L953
	ldr	w2, [x19, 24]
	ldr	x1, [x19, 8]
	ldr	w0, [x19, 16]
	bl	MEM_AddMemRecord
	ldr	x3, [x20, 96]
	mov	x2, 20
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	str	wzr, [x29, 128]
	ldr	w2, [x19, 16]
	ldr	w0, [x19, 24]
	ldr	x1, [x22, 112]
	stp	w2, w0, [x29, 120]
	cbz	x1, .L954
	add	x0, x29, 120
	blr	x1
	cbnz	w0, .L954
	str	w21, [x19, 92]
	mov	w0, 16
	add	x22, x19, 64
	ldr	x23, [x20, 136]
	bl	VFMW_GetString
	mov	w3, 0
	mov	x2, x0
	mov	x1, 20
	add	x0, x29, 96
	blr	x23
	mov	w4, 1
	mov	x3, x22
	mov	w2, 10240
	mov	w1, 0
	add	x0, x29, 96
	bl	MEM_AllocMemBlock
	cbnz	w0, .L955
	ldr	w2, [x19, 88]
	add	x23, x19, 32
	ldr	x1, [x19, 72]
	ldr	w0, [x19, 80]
	bl	MEM_AddMemRecord
	ldr	x2, .LC554
	mov	w0, 0
	ldr	w1, [x19, 80]
	str	w1, [x2, 1212]
	ldr	w1, [x19, 80]
	add	w1, w1, 4096
	add	w1, w1, 1024
	str	w1, [x2, 1216]
	bl	VDMDRV_Init
	ldr	x22, [x20, 136]
	mov	w0, 17
	bl	VFMW_GetString
	mov	x2, x0
	mov	w3, 0
	mov	x1, 20
	add	x0, x29, 96
	blr	x22
	str	w21, [x19, 60]
	mov	w2, 61440
	mov	w4, 0
	mov	x3, x23
	movk	w2, 0xa, lsl 16
	mov	w1, 0
	add	x0, x29, 96
	bl	MEM_AllocMemBlock
	cbnz	w0, .L980
	ldr	w2, [x19, 56]
	ldr	x1, [x19, 40]
	ldr	w0, [x19, 48]
	bl	MEM_AddMemRecord
	ldr	w0, [x19, 48]
	mov	w2, 0
	ldr	w1, [x19, 56]
	bl	SM_OpenSCDDrv
	cbnz	w0, .L958
	bl	SM_InstInit
	ldr	x24, .LC563
	mov	w0, 0
	ldr	x22, [x20, 408]
	ldrsw	x25, [x24, 92]
	bl	VFMW_GetString
	ldr	x21, .LC564
	mov	x3, x0
	ldr	x1, .LC565
	mov	x2, x25
	add	x21, x21, 3568
	mov	w0, 127
	mov	x4, x21
	blr	x22
	cbnz	w0, .L981
	ldr	x22, .LC572
	mov	w0, 4
	ldrsw	x26, [x24, 92]
	mov	w27, 1
	add	x22, x22, 256
	ldr	x25, [x20, 408]
	str	w27, [x22, 328]
	bl	VFMW_GetString
	ldr	x1, .LC573
	mov	x3, x0
	mov	x4, x21
	mov	x2, x26
	mov	w0, 136
	blr	x25
	cbnz	w0, .L982
	mov	w0, 13
	ldrsw	x25, [x24, 92]
	str	w27, [x22, 332]
	ldr	x24, [x20, 408]
	bl	VFMW_GetString
	ldr	x1, .LC574
	mov	x3, x0
	mov	x4, x21
	mov	x2, x25
	mov	w0, 181
	blr	x24
	cbnz	w0, .L983
	str	w27, [x22, 336]
	bl	HEVCDEC_AllocHevcGlbMem
	cbz	w0, .L949
	ldr	x1, .LC576
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L949
	.p2align 3
.L946:
	ldr	x1, .LC551
	mov	w2, -121438208
	b	.L972
	.p2align 3
.L952:
	ldr	x1, .LC556
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x21
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
	b	.L949
.L950:
	ldr	x1, .LC551
	mov	w2, 49152
	movk	w2, 0xf8c3, lsl 16
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, .LC552
	mov	x2, 32
	mov	w1, 0
	mov	x0, x21
	b	.L973
.L954:
	ldr	x1, .LC560
.L974:
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
	b	.L949
.L981:
	ldr	x1, .LC571
	mov	w2, 127
.L975:
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x23
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
	b	.L949
.L982:
	ldr	x1, .LC571
	mov	w2, 136
	b	.L975
.L983:
	ldr	x1, .LC571
	mov	w2, 181
	b	.L975
.L958:
	ldr	x1, .LC569
	mov	w2, 0
	b	.L975
.L980:
	ldr	x1, .LC567
	mov	w2, 0
	b	.L975
.L953:
	ldr	x1, .LC558
	b	.L974
.L955:
	ldr	x1, .LC562
	mov	w2, 0
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, [x20, 96]
	mov	x2, 32
	mov	w1, 0
	mov	x0, x22
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
	b	.L949
	.size	OpenDrivers, .-OpenDrivers
	.align	3
.LC551:
	.xword	.LC550
	.align	3
.LC552:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC553:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC554:
	.xword	g_HwMem
	.align	3
.LC556:
	.xword	.LC555
	.align	3
.LC558:
	.xword	.LC557
	.align	3
.LC560:
	.xword	.LC559
	.align	3
.LC562:
	.xword	.LC561
	.align	3
.LC563:
	.xword	.LANCHOR2
	.align	3
.LC564:
	.xword	.LANCHOR3
	.align	3
.LC565:
	.xword	VCTRL_Isr_0
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
.LC572:
	.xword	.LANCHOR1
	.align	3
.LC573:
	.xword	VCTRL_Scd_Isr
	.align	3
.LC574:
	.xword	VCTRL_MMU_ISR
	.align	3
.LC576:
	.xword	.LC575
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_OpenVfmw
	.type	VCTRL_OpenVfmw, %function
VCTRL_OpenVfmw:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	x0, x30
	bl	_mcount
	cbz	x23, .L1017
	ldr	x20, .LC583
	mov	x2, 8
	mov	w1, 0
	add	x0, x29, 64
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x22, .LC584
	ldr	w19, [x22, 256]
	cbnz	w19, .L1016
	ldr	x21, .LC585
	mov	w1, 1024
	ldr	x2, [x20, 160]
	add	x24, x21, 3576
	str	xzr, [x29, 72]
	mov	x0, x24
	blr	x2
	ldr	x1, .LC587
	mov	x0, x24
	ldr	x2, [x20, 192]
	blr	x2
	str	x0, [x29, 72]
	cbz	x0, .L988
	ldr	x1, .LC589
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1008
	ldr	x1, .LC591
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1018
	ldr	x3, [x20, 168]
	mov	w2, 0
	mov	x1, 0
	blr	x3
	mov	w2, w0
	str	w0, [x21, 3560]
	add	w0, w2, 4096
	mov	w1, 10000
	add	w0, w0, 904
	cmp	w0, w1
	bhi	.L993
.L1023:
	mov	w0, 5000
	mov	w1, -5000
	cmp	w2, w0
	csel	w0, w2, w0, le
	cmp	w0, w1
	csel	w0, w0, w1, ge
.L989:
	str	w0, [x21, 3560]
.L991:
	add	x24, x21, 3576
	ldr	x2, [x20, 160]
	mov	w1, 1024
	mov	x0, x24
	str	xzr, [x29, 72]
	blr	x2
	ldr	x1, .LC597
	mov	x0, x24
	ldr	x2, [x20, 192]
	blr	x2
	str	x0, [x29, 72]
	cbz	x0, .L994
	ldr	x1, .LC589
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L995
	ldr	x1, .LC591
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1019
	ldr	x3, [x20, 168]
	mov	w2, 0
	mov	x1, 0
	blr	x3
	mov	w2, w0
	str	w0, [x21, 3564]
	add	w0, w2, 4096
	mov	w1, 10000
	add	w0, w0, 904
	cmp	w0, w1
	bhi	.L999
.L1024:
	mov	w19, 5000
	mov	w0, -5000
	cmp	w2, w19
	csel	w19, w2, w19, le
	cmp	w19, w0
	csel	w19, w19, w0, ge
.L995:
	str	w19, [x21, 3564]
.L997:
	ldr	x24, .LC600
	str	xzr, [x29, 72]
	ldr	w0, [x24, 248]
	cbz	w0, .L1000
	ldr	x2, .LC601
	and	w4, w0, 1
	ubfx	x3, x0, 1, 1
	ubfx	x1, x0, 2, 1
	strb	w4, [x24, 252]
	ubfx	x0, x0, 3, 1
	strb	w3, [x2, 96]
	strb	w1, [x24, 253]
	strb	w0, [x24, 254]
.L1001:
	add	x19, x22, 256
	ldr	x3, [x20, 96]
	mov	x2, 344
	mov	w1, 0
	mov	x0, x19
	blr	x3
	ldr	x3, [x20, 96]
	mov	x2, 256
	mov	w1, 0
	mov	x0, x22
	blr	x3
	ldr	x2, .LC604
	mov	w1, 1
	add	x0, x29, 64
	str	w1, [x22, 260]
	str	x2, [x24, 256]
	mov	w1, 75497472
	mov	w2, 134217728
	stp	w2, w1, [x29, 64]
	bl	MEM_InitMemManager
	bl	FSP_Init
	ldr	x19, .LC605
	ldr	x3, [x20, 96]
	mov	x2, 384
	mov	w1, 0
	mov	x0, x19
	blr	x3
	add	x0, x19, 128
	add	x1, x19, 256
	mov	w2, -1
	.p2align 2
.L1005:
	str	w2, [x0], 4
	cmp	x1, x0
	bne	.L1005
	ldr	x3, [x20, 96]
	mov	x2, 128
	mov	w1, 0
	add	x0, x24, 264
	add	x19, x22, 288
	blr	x3
	ldr	x3, [x20, 104]
	mov	x2, 24
	add	x1, x23, 8
	add	x0, x22, 384
	blr	x3
	mov	x0, x19
	bl	OpenDrivers
	cbnz	w0, .L1016
	ldr	x2, [x20, 248]
	mov	w1, 1
	blr	x2
	ldr	x2, .LC608
	add	x0, x22, 272
	ldr	x1, .LC610
	ldr	x3, [x20, 400]
	blr	x3
	cbnz	w0, .L1020
	mov	w1, 1
	str	w1, [x22, 256]
.L986:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1000:
	add	x21, x21, 3576
	ldr	x2, [x20, 160]
	mov	w1, 1024
	mov	x0, x21
	blr	x2
	ldr	x1, .LC603
	mov	x0, x21
	ldr	x2, [x20, 192]
	blr	x2
	str	x0, [x29, 72]
	cbz	x0, .L1001
	ldr	x1, .LC589
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1021
	ldr	x1, .LC591
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1022
	ldr	x3, [x20, 168]
	mov	x1, 0
	mov	w2, 0
	blr	x3
	mov	w1, w0
	str	w0, [x24, 248]
.L1003:
	ldr	x2, .LC601
	and	w4, w1, 1
	ubfx	x3, x1, 1, 1
	ubfx	x0, x1, 2, 1
	strb	w4, [x24, 252]
	ubfx	x1, x1, 3, 1
	strb	w3, [x2, 96]
	strb	w0, [x24, 253]
	strb	w1, [x24, 254]
	b	.L1001
.L988:
	ldr	w2, [x21, 3560]
	mov	w1, 10000
	add	w0, w2, 4096
	add	w0, w0, 904
	cmp	w0, w1
	bls	.L1023
.L993:
	ldr	x1, .LC595
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w0, [x21, 3560]
	mov	w2, 5000
	mov	w1, -5000
	cmp	w0, w2
	csel	w0, w0, w2, le
	cmp	w0, w1
	csel	w0, w0, w1, ge
	b	.L989
.L994:
	ldr	w2, [x21, 3564]
	mov	w1, 10000
	add	w0, w2, 4096
	add	w0, w0, 904
	cmp	w0, w1
	bls	.L1024
.L999:
	ldr	x1, .LC599
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w19, [x21, 3564]
	mov	w1, 5000
	mov	w0, -5000
	cmp	w19, w1
	csel	w19, w19, w1, le
	cmp	w19, w0
	csel	w19, w19, w0, ge
	b	.L995
.L1008:
	mov	w0, 0
	b	.L989
.L1021:
	ldr	w1, [x24, 248]
	b	.L1003
.L1020:
	mov	x0, x19
	bl	CloseDrivers
.L1016:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
.L1019:
	ldr	x2, .LC581
	mov	w3, 6026
	ldr	x1, .LC593
	mov	w0, 22
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L997
.L1018:
	ldr	x2, .LC581
	mov	w3, 5984
	ldr	x1, .LC593
	mov	w0, 22
	add	x2, x2, 216
	bl	dprint_vfmw
	b	.L991
.L1022:
	ldr	x2, .LC581
	mov	w3, 6077
	ldr	x1, .LC593
	mov	w0, 22
	add	x2, x2, 264
	bl	dprint_vfmw
	b	.L1001
.L1017:
	ldr	x2, .LC581
	mov	w3, 938
	ldr	x4, .LC580
	mov	w0, 0
	ldr	x1, .LC582
	add	x2, x2, 200
	bl	dprint_vfmw
	mov	w0, -1
	b	.L986
	.size	VCTRL_OpenVfmw, .-VCTRL_OpenVfmw
	.align	3
.LC580:
	.xword	.LC579
	.align	3
.LC581:
	.xword	.LANCHOR4
	.align	3
.LC582:
	.xword	.LC6
	.align	3
.LC583:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC584:
	.xword	.LANCHOR1
	.align	3
.LC585:
	.xword	.LANCHOR3
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
.LC600:
	.xword	.LANCHOR5
	.align	3
.LC601:
	.xword	.LANCHOR2
	.align	3
.LC603:
	.xword	.LC602
	.align	3
.LC604:
	.xword	VCTRL_EventReport
	.align	3
.LC605:
	.xword	g_ChanCtx
	.align	3
.LC608:
	.xword	VFMW_CTRL_thread_proc
	.align	3
.LC610:
	.xword	.LC609
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	GetNextDecodeMode
	.type	GetNextDecodeMode, %function
GetNextDecodeMode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w19, w2
	mov	w22, w1
	bl	_mcount
	add	w20, w19, 7
	mov	w0, 21846
	lsl	w3, w19, 1
	movk	w0, 0x5555, lsl 16
	cmp	w19, wzr
	csel	w20, w20, w19, lt
	ldr	x1, .LC615
	smull	x0, w3, w0
	asr	w20, w20, 3
	mov	w5, w22
	lsr	x0, x0, 32
	mov	w4, w19
	sub	w3, w0, w3, asr 31
	mov	w2, w20
	mov	w0, 30
	bl	dprint_vfmw
	cmp	w21, 3
	beq	.L1030
	cmp	w19, w22
	mov	w19, w21
	blt	.L1031
.L1027:
	ldr	x1, .LC621
	mov	w3, w19
	mov	w2, w21
	mov	w0, 30
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1031:
	ldr	x1, .LC619
	mov	w0, 30
	mov	w19, 3
	bl	dprint_vfmw
	b	.L1027
	.p2align 3
.L1030:
	cmp	w20, w22
	mov	w19, w21
	ble	.L1027
	ldr	x1, .LC617
	mov	w0, 30
	mov	w19, 0
	bl	dprint_vfmw
	b	.L1027
	.size	GetNextDecodeMode, .-GetNextDecodeMode
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
.LC621:
	.xword	.LC620
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanIDByCtx
	.type	VCTRL_GetChanIDByCtx, %function
VCTRL_GetChanIDByCtx:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC622
	mov	x0, 0
	b	.L1035
	.p2align 3
.L1033:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1041
.L1035:
	ldr	x2, [x3, x0, lsl 3]
	add	x1, x2, 507904
	add	x1, x1, 1752
	cbz	x2, .L1033
	cmp	x19, x1
	bne	.L1033
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1041:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanIDByCtx, .-VCTRL_GetChanIDByCtx
	.align	3
.LC622:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanIDByMemAddr
	.type	VCTRL_GetChanIDByMemAddr, %function
VCTRL_GetChanIDByMemAddr:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x6, .LC623
	mov	x5, 0
.L1047:
	ldr	x4, [x6, x5, lsl 3]
	mov	w0, w5
	cbz	x4, .L1043
	add	x4, x4, 503808
	add	x1, x4, 1688
	add	x4, x4, 3992
	.p2align 2
.L1046:
	ldr	w2, [x1]
	cmp	w2, w19
	bhi	.L1044
	ldr	w3, [x1, -20]
	add	w2, w2, w3
	cmp	w19, w2
	bcc	.L1045
.L1044:
	add	x1, x1, 72
	cmp	x1, x4
	bne	.L1046
.L1043:
	add	x5, x5, 1
	cmp	x5, 32
	bne	.L1047
	mov	w0, -1
.L1045:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanIDByMemAddr, .-VCTRL_GetChanIDByMemAddr
	.align	3
.LC623:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecChanProcessPts
	.type	DecChanProcessPts, %function
DecChanProcessPts:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC624
	ldr	x4, [x21, w20, sxtw 3]
	ldr	w2, [x4, 52]
	cmp	w2, 1
	beq	.L1084
	cmp	w2, 6
	sub	w0, w2, #2
	ccmp	w2, 18, 4, ne
	ccmp	w0, 1, 0, ne
	bls	.L1056
.L1057:
	ldr	x2, [x19, 40]
	cmn	x2, #1
	beq	.L1085
	str	x2, [x4, 704]
.L1067:
	ldr	x3, [x19, 56]
	mov	w0, 29
	str	x3, [x4, 720]
	ldr	x1, .LC630
	ldr	x5, [x19, 64]
	str	x5, [x4, 736]
	ldr	w5, [x19, 72]
	str	w5, [x4, 752]
	ldr	w5, [x19, 76]
	str	w5, [x4, 756]
	ldr	w5, [x19, 80]
	str	w5, [x4, 760]
	ldr	w5, [x19, 84]
	str	w5, [x4, 776]
	ldrb	w5, [x19, 20]
	strb	w5, [x4, 696]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1084:
	add	x0, x4, 507904
	ldr	x0, [x0, 1752]
	ldrsb	w0, [x0, 604]
	cmp	w0, 1
	bne	.L1057
.L1056:
	add	x3, x19, 8
	add	x1, x4, 1240
	mov	w0, w20
	bl	IsNewpicSeg
	cbz	w0, .L1086
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	beq	.L1063
.L1062:
	ldr	x1, [x19, 40]
	cmn	x1, #1
	beq	.L1064
.L1083:
	str	x1, [x0, 712]
.L1064:
	ldr	x1, [x19, 56]
	str	x1, [x0, 728]
	ldr	x1, [x19, 64]
	str	x1, [x0, 744]
	ldr	w1, [x19, 72]
	str	w1, [x0, 764]
	ldr	w1, [x19, 76]
	str	w1, [x0, 768]
	ldr	w1, [x19, 80]
	str	w1, [x0, 772]
	ldr	w1, [x19, 84]
	str	w1, [x0, 780]
.L1063:
	ldr	x2, [x0, 720]
	mov	w0, 29
	ldr	x1, .LC628
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1086:
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	ldr	x1, [x0, 712]
	beq	.L1082
	cmn	x1, #1
	beq	.L1060
.L1082:
	str	x1, [x0, 704]
.L1060:
	ldr	x3, [x0, 728]
	mov	x2, -1
	ldr	x1, [x0, 744]
	str	x2, [x0, 712]
	str	x3, [x0, 720]
	str	x1, [x0, 736]
	cbnz	x1, .L1061
	ldr	x1, [x19, 64]
	str	x1, [x0, 736]
.L1061:
	ldr	w6, [x0, 764]
	ldr	w5, [x0, 768]
	ldr	w4, [x0, 772]
	ldr	w3, [x0, 780]
	ldr	x1, .LC626
	ldr	x2, [x0, 704]
	str	w6, [x0, 752]
	str	w5, [x0, 756]
	str	w4, [x0, 760]
	str	w3, [x0, 776]
	mov	w0, 29
	bl	dprint_vfmw
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	bne	.L1062
	ldr	x1, [x19, 40]
	b	.L1083
	.p2align 3
.L1085:
	ldr	x2, [x4, 704]
	b	.L1067
	.size	DecChanProcessPts, .-DecChanProcessPts
	.align	3
.LC624:
	.xword	.LANCHOR1
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
	.global	DecChanCheckDecParam
	.type	DecChanCheckDecParam, %function
DecChanCheckDecParam:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC631
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 632]
	sub	w1, w0, #10
	cmp	w1, 2
	bhi	.L1088
	ldr	x1, .LC632
	ldr	w1, [x1, 2064]
	tbz	x1, 0, .L1089
.L1088:
	and	w1, w0, -17
	cmp	w1, 4
	ccmp	w0, 14, 4, ne
	beq	.L1089
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbnz	x0, .L1091
.L1089:
	mov	w0, 0
.L1090:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1091:
	mov	w0, -2
	b	.L1090
	.size	DecChanCheckDecParam, .-DecChanCheckDecParam
	.align	3
.LC631:
	.xword	.LANCHOR1
	.align	3
.LC632:
	.xword	.LANCHOR3
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecChanSyntax
	.type	DecChanSyntax, %function
DecChanSyntax:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1132
	ldr	x21, .LC636
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1133
	ldr	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1134
	ldr	w1, [x0, 24]
	cbnz	w1, .L1135
	ldr	x23, .LC641
	str	wzr, [x0, 472]
	ldr	x0, [x23]
	blr	x0
	ldr	x22, .LC642
	mov	w2, w0
	ldr	x0, .LC643
	add	x1, x22, 392
	ldr	w3, [x0]
	ldr	w0, [x1, w19, sxtw 2]
	sub	w0, w2, w0
	cmp	w0, w3
	mov	w0, w19
	bls	.L1104
	str	w2, [x1, w19, sxtw 2]
	bl	DecChanCheckDecParam
	cmn	w0, #2
	mov	w20, w0
	beq	.L1136
	mov	w0, w19
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	bne	.L1114
	mov	w20, w0
.L1115:
	ldr	x1, [x21, w19, sxtw 3]
	add	x0, x1, 475136
	ldr	w3, [x0, 2280]
	cmp	w3, 1
	beq	.L1137
	cmp	w3, 3
	beq	.L1138
	add	x24, x1, 784
	ldrb	w0, [x24, 1]
	cbnz	w0, .L1108
	ldr	w0, [x1, 1600]
	cbz	w0, .L1139
.L1108:
	ldr	x2, [x24, 40]
	mov	w0, 29
	ldr	x3, [x24, 56]
	ldr	x1, .LC655
	bl	dprint_vfmw
	mov	x1, x24
	mov	w0, w19
	bl	DecChanProcessPts
	mov	w0, 3
	bl	CHECK_REC_POS_ENABLE
	cmp	w20, 1
	ccmp	w0, wzr, 4, eq
	bne	.L1140
.L1110:
	ldr	x1, [x21, w19, sxtw 3]
	mov	x0, x24
	add	x2, x1, 507904
	ldr	w1, [x1, 632]
	add	x2, x2, 1752
	bl	DecodeStream
	mov	w0, 4
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L1111
.L1112:
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1104:
	bl	DecChanCheckDecParam
	cmn	w0, #2
	mov	w20, w0
	bne	.L1141
.L1121:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1141:
	mov	w0, w19
	mov	w20, -3
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	bne	.L1121
	mov	w20, 0
	b	.L1115
	.p2align 3
.L1136:
	ldr	x1, .LC645
	mov	w2, w19
	mov	w0, 23
	bl	dprint_vfmw
	b	.L1121
	.p2align 3
.L1111:
	ldr	x0, [x23]
	add	x22, x22, 520
	blr	x0
	mov	w1, w0
	ldr	x2, .LC656
	ldr	w0, [x22, w19, sxtw 2]
	ldr	w2, [x2]
	sub	w0, w1, w0
	cmp	w0, w2
	bls	.L1112
	mov	w0, w19
	str	w1, [x22, w19, sxtw 2]
	bl	VCTRL_GetDecParam
	cbz	x0, .L1112
	ldr	x0, .LC634
	lsl	w2, w19, 24
	add	w2, w2, 262144
	mov	w1, 5740
	add	x0, x0, 296
	mov	w20, 0
	bl	DBG_AddTrace
	b	.L1121
.L1137:
	ldr	x1, .LC649
	mov	w0, 31
	mov	w20, -3
	bl	dprint_vfmw
	b	.L1121
	.p2align 3
.L1114:
	ldr	x1, .LC647
	mov	w2, w19
	mov	w0, 23
	mov	w20, -3
	bl	dprint_vfmw
	b	.L1121
	.p2align 3
.L1134:
	ldr	x2, .LC634
	mov	w3, 5640
	ldr	x4, .LC638
	mov	w0, 0
	ldr	x1, .LC635
	add	x2, x2, 280
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1121
	.p2align 3
.L1135:
	ldr	x2, .LC634
	mov	w3, 5641
	ldr	x4, .LC640
	mov	w0, 0
	ldr	x1, .LC635
	add	x2, x2, 280
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1121
	.p2align 3
.L1139:
	add	x1, x1, 792
	mov	w0, w19
	bl	SM_ReadSegStream
	cbz	w0, .L1108
	cmp	w20, 1
	beq	.L1142
.L1109:
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 1
	mov	w20, -4
	str	w1, [x0, 472]
	b	.L1121
	.p2align 3
.L1132:
	ldr	x2, .LC634
	mov	w3, 5638
	ldr	x4, .LC633
	mov	w0, 0
	ldr	x1, .LC635
	add	x2, x2, 280
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1121
	.p2align 3
.L1140:
	ldr	x0, .LC634
	lsl	w2, w19, 24
	add	w2, w2, 196608
	mov	w1, 5722
	add	x0, x0, 296
	bl	DBG_AddTrace
	b	.L1110
.L1133:
	ldr	x2, .LC634
	mov	w3, 5639
	ldr	x4, .LC637
	mov	w20, -1
	ldr	x1, .LC635
	add	x2, x2, 280
	bl	dprint_vfmw
	b	.L1121
.L1138:
	ldr	w2, [x1, 1552]
	mov	w0, 31
	ldr	x1, .LC651
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1121
.L1142:
	ldr	x1, .LC653
	mov	w2, w19
	mov	w0, 23
	bl	dprint_vfmw
	b	.L1109
	.size	DecChanSyntax, .-DecChanSyntax
	.align	3
.LC633:
	.xword	.LC193
	.align	3
.LC634:
	.xword	.LANCHOR4
	.align	3
.LC635:
	.xword	.LC6
	.align	3
.LC636:
	.xword	.LANCHOR1
	.align	3
.LC637:
	.xword	.LC426
	.align	3
.LC638:
	.xword	.LC472
	.align	3
.LC640:
	.xword	.LC639
	.align	3
.LC641:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC642:
	.xword	.LANCHOR5
	.align	3
.LC643:
	.xword	g_TraceBsPeriod
	.align	3
.LC645:
	.xword	.LC644
	.align	3
.LC647:
	.xword	.LC646
	.align	3
.LC649:
	.xword	.LC648
	.align	3
.LC651:
	.xword	.LC650
	.align	3
.LC653:
	.xword	.LC652
	.align	3
.LC655:
	.xword	.LC654
	.align	3
.LC656:
	.xword	g_TraceFramePeriod
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DecSyntax
	.type	DecSyntax, %function
DecSyntax:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC659
	ldr	x23, .LC660
	mov	x0, 0
	b	.L1146
	.p2align 3
.L1174:
	ldr	w1, [x1, 20]
	str	w1, [x2, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1173
.L1146:
	ldr	x1, [x21, x0, lsl 3]
	add	x2, x23, 648
	cbnz	x1, .L1174
	add	x1, x23, 648
	str	wzr, [x1, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L1146
.L1173:
	ldr	x24, .LC661
	mov	w20, -1
	.p2align 2
.L1147:
	ldr	w3, [x23, 648]
	add	x1, x23, 652
	mov	w0, 0
	mov	w19, 0
	.p2align 2
.L1148:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L1175
.L1150:
	ldr	w2, [x1]
	add	x1, x1, 4
	cmp	w3, w2
	bge	.L1148
	mov	w19, w0
	add	w0, w0, 1
	cmp	w0, 32
	mov	w3, w2
	bne	.L1150
.L1175:
	add	x2, x23, 648
	add	x0, x21, 256
	add	w1, w19, 1
	cmp	w3, wzr
	sxtw	x25, w19
	str	wzr, [x2, w19, sxtw 2]
	str	w1, [x0, 28]
	ble	.L1151
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1147
	ldr	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1147
	ldr	w1, [x0, 76]
	cmp	w1, wzr
	ble	.L1153
	ldr	w0, [x0, 80]
	cbz	w0, .L1176
.L1153:
	mov	w22, 500
	b	.L1161
	.p2align 3
.L1156:
	ldr	x0, [x21, x25, lsl 3]
	cbnz	w20, .L1159
	ldr	w1, [x0, 1632]
	cmp	w1, 1
	beq	.L1159
	subs	w22, w22, #1
	beq	.L1147
.L1161:
	mov	w0, w19
	bl	DecChanSyntax
	cmn	w0, #1
	mov	w20, w0
	bne	.L1156
	ldr	x4, [x23, 256]
	cbz	x4, .L1157
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w0, w19
	blr	x4
.L1157:
	mov	w0, w20
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
.L1159:
	str	wzr, [x0, 1632]
	b	.L1147
.L1176:
	add	x1, x29, 88
	mov	w0, w19
	bl	SM_GetInfo
	cbnz	w0, .L1177
.L1154:
	ldr	x20, [x21, x25, lsl 3]
	ldr	w1, [x29, 100]
	ldr	w2, [x20, 76]
	ldr	w0, [x20, 648]
	bl	GetNextDecodeMode
	str	w0, [x20, 648]
	ldr	x1, [x21, x25, lsl 3]
	ldr	w0, [x1, 648]
	cbz	w0, .L1155
	str	wzr, [x1, 640]
	str	wzr, [x1, 644]
	b	.L1153
.L1151:
	str	wzr, [x0, 28]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
.L1155:
	ldr	w0, [x1, 72]
	str	w0, [x1, 640]
	str	w0, [x1, 644]
	b	.L1153
.L1177:
	ldr	x3, [x24, 96]
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 88
	blr	x3
	b	.L1154
	.size	DecSyntax, .-DecSyntax
	.align	3
.LC659:
	.xword	.LANCHOR1
	.align	3
.LC660:
	.xword	.LANCHOR5
	.align	3
.LC661:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_RunProcess
	.type	VCTRL_RunProcess, %function
VCTRL_RunProcess:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	bl	VCTRL_RecordPosTime
	ldr	x20, .LC664
	ldrb	w0, [x20, 2816]
	cmp	w0, 1
	beq	.L1187
.L1179:
	ldr	w0, [x20, 1124]
	mov	w1, 100
	str	w1, [x20, 280]
	cmp	w0, wzr
	ldr	x21, .LC665
	ble	.L1180
	ldr	x1, [x21, 240]
	blr	x1
.L1180:
	ldr	x1, [x21, 24]
	mov	w0, 0
	mov	w22, 0
	blr	x1
	bl	SM_Wakeup
	ldr	w0, [x20, 1120]
	mov	w1, 101
	str	w1, [x20, 280]
	cbz	w0, .L1188
.L1181:
	mov	w0, 102
	mov	w19, 0
	str	w0, [x20, 280]
	bl	VDMDRV_WakeUpVdm
	.p2align 2
.L1182:
	mov	w0, w19
	mov	w1, 0
	add	w19, w19, 1
	bl	DeleteRawPacketInBuffer
	cmp	w19, 32
	bne	.L1182
	ldr	x1, [x21, 32]
	mov	w0, 0
	blr	x1
	mov	w1, 105
	mov	w0, 1
	str	w1, [x20, 280]
	bl	VCTRL_RecordPosTime
	ldr	x3, [x21, 264]
	mov	w2, 10
	mov	w1, 0
	mov	w0, 0
	blr	x3
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1188:
	bl	DecSyntax
	mov	w22, w0
	b	.L1181
.L1187:
	mov	w0, 11
	bl	VCTRL_RecordPosTime
	strb	wzr, [x20, 2816]
	b	.L1179
	.size	VCTRL_RunProcess, .-VCTRL_RunProcess
	.align	3
.LC664:
	.xword	.LANCHOR1
	.align	3
.LC665:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VFMW_CTRL_thread_proc
	.type	VFMW_CTRL_thread_proc, %function
VFMW_CTRL_thread_proc:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	x0, x30
	mov	w21, 2
	bl	_mcount
	ldr	x20, .LC666
	ldr	x25, .LC668
	ldr	x22, .LC672
	ldr	x26, .LC670
	ldr	x23, .LC674
	ldr	x24, .LC675
.L1190:
.L1197:
	mov	x1, x25
	mov	w0, 2
	str	wzr, [x20, 280]
	bl	dprint_vfmw
	str	w21, [x20, 260]
	ldr	w0, [x20, 264]
	cmp	w0, 2
	bne	.L1212
	b	.L1195
	.p2align 3
.L1214:
	str	w21, [x20, 280]
	bl	VCTRL_RunProcess
	mov	x1, x22
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x20, 264]
	cmp	w0, 2
	beq	.L1195
.L1212:
	cmp	w0, 3
	bne	.L1214
.L1193:
	ldr	x1, .LC677
	mov	w2, 6
	mov	w0, 2
	str	w2, [x20, 280]
	bl	dprint_vfmw
	str	wzr, [x20, 260]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1195:
	mov	w2, 4
	mov	x1, x26
	mov	w0, 2
	str	w2, [x20, 280]
	mov	w27, 5
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x20, 260]
	b	.L1192
	.p2align 3
.L1215:
	ldr	x1, [x24, 240]
	blr	x1
.L1192:
	mov	x1, x23
	mov	w0, 22
	str	w27, [x20, 280]
	bl	dprint_vfmw
	ldr	w1, [x20, 264]
	mov	w0, 10
	cmp	w1, 1
	beq	.L1197
	cmp	w1, 3
	bne	.L1215
	b	.L1193
	.size	VFMW_CTRL_thread_proc, .-VFMW_CTRL_thread_proc
	.align	3
.LC666:
	.xword	.LANCHOR1
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
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC677:
	.xword	.LC676
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanVoQue
	.type	VCTRL_GetChanVoQue, %function
VCTRL_GetChanVoQue:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC679
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1235
	ldr	w1, [x0, 632]
	cmp	w1, 20
	bls	.L1236
.L1235:
	mov	x0, 0
.L1217:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1236:
	ldr	x2, .LC680
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx1219
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx1219:
	.section	.rodata
	.align	0
	.align	2
.L1219:
	.byte	(.L1233 - .Lrtx1219) / 4
	.byte	(.L1220 - .Lrtx1219) / 4
	.byte	(.L1221 - .Lrtx1219) / 4
	.byte	(.L1222 - .Lrtx1219) / 4
	.byte	(.L1235 - .Lrtx1219) / 4
	.byte	(.L1223 - .Lrtx1219) / 4
	.byte	(.L1224 - .Lrtx1219) / 4
	.byte	(.L1235 - .Lrtx1219) / 4
	.byte	(.L1225 - .Lrtx1219) / 4
	.byte	(.L1226 - .Lrtx1219) / 4
	.byte	(.L1227 - .Lrtx1219) / 4
	.byte	(.L1227 - .Lrtx1219) / 4
	.byte	(.L1227 - .Lrtx1219) / 4
	.byte	(.L1228 - .Lrtx1219) / 4
	.byte	(.L1235 - .Lrtx1219) / 4
	.byte	(.L1229 - .Lrtx1219) / 4
	.byte	(.L1230 - .Lrtx1219) / 4
	.byte	(.L1231 - .Lrtx1219) / 4
	.byte	(.L1232 - .Lrtx1219) / 4
	.byte	(.L1235 - .Lrtx1219) / 4
	.byte	(.L1233 - .Lrtx1219) / 4
	.text
	.p2align 3
.L1233:
	add	x0, x0, 507904
	ldr	x19, [sp, 16]
	add	x0, x0, 1760
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1220:
	add	x0, x0, 561152
	add	x0, x0, 2040
	b	.L1217
	.p2align 3
.L1230:
	add	x0, x0, 516096
	add	x0, x0, 504
	b	.L1217
	.p2align 3
.L1229:
	add	x0, x0, 507904
	add	x0, x0, 2664
	b	.L1217
	.p2align 3
.L1228:
	add	x0, x0, 516096
	add	x0, x0, 1792
	b	.L1217
	.p2align 3
.L1227:
	add	x0, x0, 520192
	add	x0, x0, 2224
	b	.L1217
	.p2align 3
.L1232:
	add	x0, x0, 524288
	add	x0, x0, 4040
	b	.L1217
	.p2align 3
.L1231:
	add	x0, x0, 786432
	add	x0, x0, 1696
	b	.L1217
	.p2align 3
.L1222:
	add	x0, x0, 598016
	add	x0, x0, 432
	b	.L1217
	.p2align 3
.L1221:
	add	x0, x0, 528384
	add	x0, x0, 3992
	b	.L1217
	.p2align 3
.L1226:
	add	x0, x0, 561152
	add	x0, x0, 3448
	b	.L1217
	.p2align 3
.L1225:
	add	x0, x0, 561152
	add	x0, x0, 3472
	b	.L1217
	.p2align 3
.L1224:
	add	x0, x0, 524288
	add	x0, x0, 1632
	b	.L1217
	.p2align 3
.L1223:
	add	x0, x0, 548864
	add	x0, x0, 3416
	b	.L1217
	.size	VCTRL_GetChanVoQue, .-VCTRL_GetChanVoQue
	.align	3
.LC679:
	.xword	.LANCHOR1
	.align	3
.LC680:
	.xword	.L1219
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_FindOccupiedFrame
	.type	VCTRL_FindOccupiedFrame, %function
VCTRL_FindOccupiedFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1253
	mov	w0, w19
	bl	VCTRL_GetChanVoQue
	mov	x20, x0
	cbz	x0, .L1247
	add	x2, x29, 48
	add	x1, x29, 40
	str	wzr, [x29, 40]
	str	wzr, [x2, -4]!
	bl	GetQueueImgNum
	ldr	w2, [x29, 40]
	mov	w0, -1
	cbz	w2, .L1239
	cmp	w2, 32
	bhi	.L1254
.L1241:
	ldr	x1, .LC686
	ldrh	w0, [x20, 4]
	ldr	x5, [x1, w19, sxtw 3]
	and	x0, x0, 63
	add	x0, x0, 2
	add	x6, x5, 507904
	ldr	x4, [x20, x0, lsl 3]
	ldr	w3, [x6, 1672]
	cmp	w3, 32
	bhi	.L1242
	mov	w1, 1
	b	.L1244
	.p2align 3
.L1245:
	ldrh	w0, [x20, 4]
	cmp	w3, 33
	add	w0, w0, w1
	add	w1, w1, 1
	and	x0, x0, 63
	add	x0, x0, 2
	ldr	x4, [x20, x0, lsl 3]
	beq	.L1242
.L1244:
	ubfiz	x0, x3, 4, 32
	ldr	w4, [x4, 20]
	add	x0, x5, x0
	add	w3, w3, 1
	add	x0, x0, 507904
	cmp	w1, w2
	str	wzr, [x0, 1144]
	str	w4, [x0, 1148]
	str	xzr, [x0, 1152]
	str	w3, [x6, 1672]
	bcc	.L1245
	mov	w0, 0
.L1239:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1242:
	ldr	x1, .LC688
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1239
	.p2align 3
.L1254:
	ldr	x1, .LC685
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x29, 40]
	cbnz	w2, .L1241
	mov	w0, 0
	b	.L1239
.L1247:
	mov	w0, -1
	b	.L1239
.L1253:
	ldr	x2, .LC682
	mov	w3, 3086
	ldr	x4, .LC681
	mov	w0, 0
	ldr	x1, .LC683
	add	x2, x2, 312
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1239
	.size	VCTRL_FindOccupiedFrame, .-VCTRL_FindOccupiedFrame
	.align	3
.LC681:
	.xword	.LC193
	.align	3
.LC682:
	.xword	.LANCHOR4
	.align	3
.LC683:
	.xword	.LC6
	.align	3
.LC685:
	.xword	.LC684
	.align	3
.LC686:
	.xword	.LANCHOR1
	.align	3
.LC688:
	.xword	.LC687
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ReportOccupiedFrame
	.type	VCTRL_ReportOccupiedFrame, %function
VCTRL_ReportOccupiedFrame:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w22, 31
	bhi	.L1272
	cbz	x19, .L1273
	mov	w0, w22
	bl	VCTRL_GetChanVoQue
	mov	x20, x0
	cbz	x0, .L1265
	ldr	x21, .LC694
	add	x23, x29, 80
	mov	w0, 4
	str	wzr, [x29, 72]
	ldr	x1, [x21, 24]
	str	wzr, [x23, -4]!
	blr	x1
	mov	x2, x23
	add	x1, x29, 72
	mov	x0, x20
	bl	GetQueueImgNum
	ldr	w2, [x29, 72]
	cbnz	w2, .L1274
	ldr	x6, .LC696
	ldr	x4, [x6, w22, sxtw 3]
	add	x0, x4, 507904
	ldr	w0, [x0, 1672]
	cbz	w0, .L1263
	mov	w2, 0
	sxtw	x0, w22
	.p2align 2
.L1264:
	sxtw	x3, w2
	add	w2, w2, 1
	add	x1, x3, 28672
	lsl	x3, x3, 4
	add	x1, x1, 3143
	add	x5, x19, x3
	lsl	x1, x1, 4
	sxth	w2, w2
	add	x4, x4, x1
	ldr	w4, [x4, 12]
	str	w4, [x5, 4]
	ldr	x4, [x6, x0, lsl 3]
	add	x1, x4, x1
	ldr	x1, [x1, 16]
	str	x1, [x5, 8]
	str	wzr, [x19, x3]
	ldr	x4, [x6, x0, lsl 3]
	add	x1, x4, 507904
	ldr	w1, [x1, 1672]
	cmp	w2, w1
	bcc	.L1264
	str	w1, [x19, 528]
	b	.L1263
	.p2align 3
.L1274:
	cmp	w2, 32
	bhi	.L1275
.L1260:
	mov	w0, 0
	.p2align 2
.L1262:
	ldrh	w1, [x20, 4]
	sbfiz	x3, x0, 4, 32
	add	w5, w0, 1
	add	x4, x19, x3
	add	w0, w1, w0
	and	x1, x0, 63
	sxth	w0, w5
	add	x1, x1, 2
	cmp	w2, w0
	ldr	x1, [x20, x1, lsl 3]
	ldr	w5, [x1, 20]
	str	w5, [x4, 4]
	ldr	x1, [x1, 504]
	str	x1, [x4, 8]
	str	wzr, [x19, x3]
	bhi	.L1262
	uxth	w1, w2
.L1261:
	ldrh	w0, [x20, 4]
	add	w0, w1, w0
	and	w0, w0, 63
	strh	w0, [x20, 4]
	str	w2, [x19, 528]
.L1263:
	ldr	x1, [x21, 32]
	mov	w0, 4
	blr	x1
	mov	w0, 0
.L1257:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1275:
	ldr	x1, .LC695
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x29, 72]
	cbnz	w2, .L1260
	mov	w2, 0
	mov	w1, 0
	b	.L1261
.L1265:
	mov	w0, -1
	b	.L1257
.L1272:
	ldr	x2, .LC690
	mov	w3, 3162
	ldr	x4, .LC689
	mov	w0, 0
	ldr	x1, .LC691
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1257
.L1273:
	ldr	x2, .LC690
	mov	w3, 3163
	ldr	x4, .LC693
	mov	w0, 0
	ldr	x1, .LC691
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1257
	.size	VCTRL_ReportOccupiedFrame, .-VCTRL_ReportOccupiedFrame
	.align	3
.LC689:
	.xword	.LC193
	.align	3
.LC690:
	.xword	.LANCHOR4
	.align	3
.LC691:
	.xword	.LC6
	.align	3
.LC693:
	.xword	.LC692
	.align	3
.LC694:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC695:
	.xword	.LC684
	.align	3
.LC696:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanImgNum
	.type	VCTRL_GetChanImgNum, %function
VCTRL_GetChanImgNum:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	mov	x21, x2
	mov	x22, x3
	bl	_mcount
	cbz	x20, .L1289
	cbz	x21, .L1290
	cbz	x22, .L1291
	cmp	w19, 31
	bhi	.L1292
	ldr	x23, .LC706
	ldr	x0, [x23, w19, sxtw 3]
	cbz	x0, .L1293
	mov	w0, w19
	bl	VCTRL_GetChanVoQue
	cbz	x0, .L1283
	mov	x1, x21
	mov	x2, x22
	bl	GetQueueImgNum
	ldr	x1, [x23, w19, sxtw 3]
	ldr	w0, [x1, 632]
	cbz	w0, .L1294
	cmp	w0, 16
	beq	.L1295
	cmp	w0, 17
	beq	.L1296
	cmp	w0, 15
	beq	.L1297
	cmp	w0, 18
	beq	.L1298
	mov	w0, 2
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1283:
	str	wzr, [x22]
	str	wzr, [x21]
	str	wzr, [x20]
.L1276:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1292:
	ldr	x2, .LC699
	mov	w3, 5849
	ldr	x4, .LC705
	mov	w0, 0
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1294:
	add	x1, x1, 536576
	ldr	w0, [x1, 1360]
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1295:
	add	x1, x1, 512000
	ldr	w0, [x1, 1032]
	str	w0, [x20]
	b	.L1276
	.p2align 3
.L1296:
	mov	w0, 9
	str	w0, [x20]
	b	.L1276
	.p2align 3
.L1289:
	ldr	x2, .LC699
	mov	w3, 5846
	ldr	x4, .LC698
	mov	w0, 0
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1276
	.p2align 3
.L1290:
	ldr	x2, .LC699
	mov	w3, 5847
	ldr	x4, .LC702
	mov	w0, 0
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1276
	.p2align 3
.L1298:
	mov	w0, 5
	str	w0, [x20]
	b	.L1276
	.p2align 3
.L1291:
	ldr	x2, .LC699
	mov	w3, 5848
	ldr	x4, .LC704
	mov	w0, 0
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1276
	.p2align 3
.L1297:
	add	x1, x1, 11632640
	ldr	w0, [x1, 2576]
	str	w0, [x20]
	b	.L1276
	.p2align 3
.L1293:
	ldr	x2, .LC699
	mov	w3, 5850
	ldr	x4, .LC707
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1276
	.size	VCTRL_GetChanImgNum, .-VCTRL_GetChanImgNum
	.align	3
.LC698:
	.xword	.LC697
	.align	3
.LC699:
	.xword	.LANCHOR4
	.align	3
.LC700:
	.xword	.LC6
	.align	3
.LC702:
	.xword	.LC701
	.align	3
.LC704:
	.xword	.LC703
	.align	3
.LC705:
	.xword	.LC193
	.align	3
.LC706:
	.xword	.LANCHOR1
	.align	3
.LC707:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanState
	.type	VCTRL_GetChanState, %function
VCTRL_GetChanState:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L1309
	cmp	w20, 31
	bhi	.L1310
	ldr	x21, .LC715
	ldr	x0, [x21, w20, sxtw 3]
	cbz	x0, .L1311
	ldr	x0, .LC717
	mov	x2, 100
	mov	w1, 0
	str	wzr, [x29, 68]
	stp	wzr, wzr, [x29, 60]
	ldr	x3, [x0, 96]
	mov	x0, x19
	blr	x3
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1256]
	str	w0, [x19, 32]
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1260]
	str	w0, [x19, 36]
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w0, [x0, 1264]
	str	w0, [x19, 44]
	ldr	x5, [x21, w20, sxtw 3]
	add	x0, x5, 475136
	ldrsb	w0, [x0, 2251]
	cmp	w0, wzr
	ble	.L1307
	mov	x2, 40882
	sub	w4, w0, #1
	mov	w3, 88
	movk	x2, 0x7, lsl 16
	add	x0, x5, 495616
	mov	w1, 0
	umaddl	x2, w4, w3, x2
	add	x0, x0, 3930
	add	x3, x5, x2
	.p2align 2
.L1306:
	ldrsb	w2, [x0], 88
	cmp	w2, 3
	csinc	w1, w1, w1, ne
	cmp	x0, x3
	bne	.L1306
.L1304:
	str	w1, [x19, 84]
	add	x3, x29, 68
	add	x2, x29, 64
	mov	w0, w20
	ldr	x4, [x21, w20, sxtw 3]
	add	x1, x29, 60
	sxtw	x22, w20
	add	x4, x4, 475136
	ldrsb	w4, [x4, 2251]
	str	w4, [x19, 92]
	bl	VCTRL_GetChanImgNum
	ldr	x2, .LC718
	lsl	x0, x22, 2
	sub	x0, x0, x22
	add	x1, x29, 72
	ldp	w4, w3, [x29, 64]
	add	x2, x2, 776
	add	x2, x2, x0, lsl 3
	add	w0, w4, w3
	str	w0, [x19, 48]
	mov	w0, w20
	ldr	w3, [x2, 20]
	str	w3, [x19, 96]
	ldr	w2, [x2, 8]
	str	w2, [x19, 20]
	bl	SM_GetInfo
	ldp	w1, w2, [x29, 88]
	ldr	w0, [x29, 80]
	cmp	w2, 10
	stp	w1, w0, [x19, 52]
	cset	w0, gt
	str	w0, [x19, 80]
	mov	x0, 63192
	ldr	x1, [x21, w20, sxtw 3]
	movk	x0, 0x7, lsl 16
	add	x0, x1, x0
	ldrb	w0, [x0, 3616]
	and	w0, w0, 1
	str	w0, [x19, 88]
.L1299:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1310:
	ldr	x2, .LC712
	mov	w3, 1264
	ldr	x4, .LC714
	mov	w0, 0
	ldr	x1, .LC713
	add	x2, x2, 392
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1311:
	ldr	x2, .LC712
	mov	w3, 1265
	ldr	x4, .LC716
	ldr	x1, .LC713
	add	x2, x2, 392
	bl	dprint_vfmw
	b	.L1299
.L1307:
	mov	w1, 0
	b	.L1304
.L1309:
	ldr	x2, .LC712
	mov	w3, 1263
	ldr	x4, .LC711
	mov	w0, 0
	ldr	x1, .LC713
	add	x2, x2, 392
	bl	dprint_vfmw
	b	.L1299
	.size	VCTRL_GetChanState, .-VCTRL_GetChanState
	.align	3
.LC711:
	.xword	.LC710
	.align	3
.LC712:
	.xword	.LANCHOR4
	.align	3
.LC713:
	.xword	.LC6
	.align	3
.LC714:
	.xword	.LC376
	.align	3
.LC715:
	.xword	.LANCHOR1
	.align	3
.LC716:
	.xword	.LC381
	.align	3
.LC717:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC718:
	.xword	.LANCHOR5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanWidth
	.type	VCTRL_GetChanWidth, %function
VCTRL_GetChanWidth:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1316
	ldr	x0, .LC723
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1317
	ldr	w0, [x0, 1372]
.L1314:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1316:
	ldr	x2, .LC721
	mov	w3, 5913
	ldr	x4, .LC720
	mov	w0, 0
	ldr	x1, .LC722
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1314
.L1317:
	ldr	x2, .LC721
	mov	w3, 5914
	ldr	x4, .LC724
	ldr	x1, .LC722
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1314
	.size	VCTRL_GetChanWidth, .-VCTRL_GetChanWidth
	.align	3
.LC720:
	.xword	.LC193
	.align	3
.LC721:
	.xword	.LANCHOR4
	.align	3
.LC722:
	.xword	.LC6
	.align	3
.LC723:
	.xword	.LANCHOR1
	.align	3
.LC724:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanHeight
	.type	VCTRL_GetChanHeight, %function
VCTRL_GetChanHeight:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1322
	ldr	x0, .LC728
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1323
	ldr	w0, [x0, 1376]
.L1320:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1322:
	ldr	x2, .LC726
	mov	w3, 5921
	ldr	x4, .LC725
	mov	w0, 0
	ldr	x1, .LC727
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1320
.L1323:
	ldr	x2, .LC726
	mov	w3, 5922
	ldr	x4, .LC729
	ldr	x1, .LC727
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1320
	.size	VCTRL_GetChanHeight, .-VCTRL_GetChanHeight
	.align	3
.LC725:
	.xword	.LC193
	.align	3
.LC726:
	.xword	.LANCHOR4
	.align	3
.LC727:
	.xword	.LC6
	.align	3
.LC728:
	.xword	.LANCHOR1
	.align	3
.LC729:
	.xword	.LC9
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetChanCapLevel
	.type	VCTRL_GetChanCapLevel, %function
VCTRL_GetChanCapLevel:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1328
	ldr	x0, .LC733
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1327
	ldr	w0, [x0, 36]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1328:
	ldr	x2, .LC731
	mov	w3, 5929
	ldr	x4, .LC730
	mov	w0, 0
	ldr	x1, .LC732
	add	x2, x2, 464
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1327:
	mov	w0, 33
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanCapLevel, .-VCTRL_GetChanCapLevel
	.align	3
.LC730:
	.xword	.LC193
	.align	3
.LC731:
	.xword	.LANCHOR4
	.align	3
.LC732:
	.xword	.LC6
	.align	3
.LC733:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetVdecExtra
	.type	VCTRL_SetVdecExtra, %function
VCTRL_SetVdecExtra:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x20, .LC734
	add	w0, w21, 4096
	mov	w1, 10000
	add	w0, w0, 904
	mov	w2, w21
	cmp	w0, w1
	str	w21, [x20, 3560]
	bhi	.L1334
.L1330:
	mov	w3, 5000
	mov	w1, -5000
	cmp	w2, w3
	add	w0, w19, 4096
	csel	w2, w2, w3, le
	add	w0, w0, 904
	cmp	w2, w1
	mov	w3, 10000
	csel	w2, w2, w1, ge
	str	w19, [x20, 3564]
	cmp	w0, w3
	str	w2, [x20, 3560]
	bhi	.L1335
.L1331:
	mov	w2, 5000
	mov	w0, -5000
	cmp	w19, w2
	csel	w19, w19, w2, le
	cmp	w19, w0
	csel	w19, w19, w0, ge
	str	w19, [x20, 3564]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1334:
	ldr	x1, .LC736
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w2, [x20, 3560]
	b	.L1330
	.p2align 3
.L1335:
	ldr	x1, .LC738
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w19, [x20, 3564]
	b	.L1331
	.size	VCTRL_SetVdecExtra, .-VCTRL_SetVdecExtra
	.align	3
.LC734:
	.xword	.LANCHOR3
	.align	3
.LC736:
	.xword	.LC735
	.align	3
.LC738:
	.xword	.LC737
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VfmwProcGetHandler
	.type	VfmwProcGetHandler, %function
VfmwProcGetHandler:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbz	w19, .L1340
	ldr	x3, .LC741
	mov	w1, 1
	ldr	x0, .LC739
	add	x3, x3, 488
	b	.L1338
	.p2align 3
.L1339:
	ldr	w4, [x3, x4]
	add	w1, w1, 1
	ubfiz	x2, x1, 4, 32
	cmp	w4, w19
	add	x2, x3, x2
	beq	.L1337
	ldr	x0, [x2, 8]
.L1338:
	ubfiz	x4, x1, 4, 32
	cbnz	x0, .L1339
.L1337:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1340:
	ldr	x0, .LC740
	b	.L1337
	.size	VfmwProcGetHandler, .-VfmwProcGetHandler
	.align	3
.LC739:
	.xword	VfmwProc_SetErrorThread
	.align	3
.LC740:
	.xword	VfmwProc_SetPrintLevel
	.align	3
.LC741:
	.xword	.LANCHOR4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetDbgOption
	.type	VCTRL_SetDbgOption, %function
VCTRL_SetDbgOption:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	cbz	x20, .L1351
	cbz	w19, .L1348
	ldr	x4, .LC745
	mov	w0, 1
	ldr	x5, .LC743
	add	x4, x4, 488
	b	.L1344
	.p2align 3
.L1349:
	ldr	w6, [x4, x6]
	add	w0, w0, 1
	ubfiz	x3, x0, 4, 32
	cmp	w19, w6
	add	x3, x4, x3
	beq	.L1343
	ldr	x5, [x3, 8]
.L1344:
	ubfiz	x6, x0, 4, 32
	cbnz	x5, .L1349
	ldr	x1, .LC747
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
.L1351:
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1348:
	ldr	x5, .LC744
.L1343:
	mov	x0, x20
	blr	x5
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetDbgOption, .-VCTRL_SetDbgOption
	.align	3
.LC743:
	.xword	VfmwProc_SetErrorThread
	.align	3
.LC744:
	.xword	VfmwProc_SetPrintLevel
	.align	3
.LC745:
	.xword	.LANCHOR4
	.align	3
.LC747:
	.xword	.LC746
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetLastFrameState
	.type	VCTRL_SetLastFrameState, %function
VCTRL_SetLastFrameState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L1358
	ldr	x0, .LC749
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1352
	str	w20, [x0, 476]
.L1352:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1358:
	bl	VCTRL_SetLastFrameState.part.23
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetLastFrameState, .-VCTRL_SetLastFrameState
	.align	3
.LC749:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ReportLastFrame
	.type	VCTRL_ReportLastFrame, %function
VCTRL_ReportLastFrame:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	w20, w1
	mov	x0, x30
	bl	_mcount
	cbz	w20, .L1366
	cmp	w20, 1
	mov	w0, 3
	mov	w1, 4
	csel	w0, w0, w1, eq
	cmp	w19, 31
	bhi	.L1373
.L1363:
	ldr	x21, .LC750
	ldr	x1, [x21, w19, sxtw 3]
	cbz	x1, .L1364
	str	w0, [x1, 476]
.L1364:
	ldr	x0, .LC751
	ldr	x4, [x0, 256]
	cbz	x4, .L1365
	add	x2, x29, 64
	mov	w3, 4
	mov	w1, 115
	mov	w0, w19
	str	w20, [x2, -8]!
	blr	x4
.L1365:
	ldr	x4, [x21, w19, sxtw 3]
	mov	w3, w20
	ldr	x1, .LC753
	mov	w2, w19
	mov	w0, 1
	ldr	w4, [x4, 476]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1366:
	cmp	w19, 31
	mov	w0, 2
	bls	.L1363
.L1373:
	bl	VCTRL_SetLastFrameState.part.23
	ldr	x21, .LC750
	b	.L1364
	.size	VCTRL_ReportLastFrame, .-VCTRL_ReportLastFrame
	.align	3
.LC750:
	.xword	.LANCHOR1
	.align	3
.LC751:
	.xword	.LANCHOR5
	.align	3
.LC753:
	.xword	.LC752
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_OutputLastFrame
	.type	VCTRL_OutputLastFrame, %function
VCTRL_OutputLastFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	cmp	w20, 31
	bhi	.L1402
	ldr	x0, .LC757
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L1403
	add	x0, x0, 507904
	ldr	w1, [x0, 1744]
	cmp	w1, 18
	bls	.L1404
.L1395:
	mov	w1, 1
	mov	w0, w20
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC761
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, -1
.L1376:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1404:
	ldr	x2, .LC759
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx1380
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx1380:
	.section	.rodata
	.align	0
	.align	2
.L1380:
	.byte	(.L1379 - .Lrtx1380) / 4
	.byte	(.L1381 - .Lrtx1380) / 4
	.byte	(.L1382 - .Lrtx1380) / 4
	.byte	(.L1383 - .Lrtx1380) / 4
	.byte	(.L1395 - .Lrtx1380) / 4
	.byte	(.L1384 - .Lrtx1380) / 4
	.byte	(.L1385 - .Lrtx1380) / 4
	.byte	(.L1395 - .Lrtx1380) / 4
	.byte	(.L1386 - .Lrtx1380) / 4
	.byte	(.L1387 - .Lrtx1380) / 4
	.byte	(.L1388 - .Lrtx1380) / 4
	.byte	(.L1388 - .Lrtx1380) / 4
	.byte	(.L1388 - .Lrtx1380) / 4
	.byte	(.L1389 - .Lrtx1380) / 4
	.byte	(.L1395 - .Lrtx1380) / 4
	.byte	(.L1390 - .Lrtx1380) / 4
	.byte	(.L1391 - .Lrtx1380) / 4
	.byte	(.L1392 - .Lrtx1380) / 4
	.byte	(.L1393 - .Lrtx1380) / 4
	.text
	.p2align 3
.L1393:
	add	x0, x0, 1752
	bl	AVS2DEC_GetRemainImg
	mov	w19, w0
	.p2align 2
.L1378:
	cmn	w19, #1
	beq	.L1395
	cbnz	w19, .L1405
	mov	w0, w20
	mov	w1, 0
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC763
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1392:
	add	x0, x0, 1752
	bl	VP9DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1391:
	add	x0, x0, 1752
	bl	HEVCDEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1390:
	add	x0, x0, 1752
	bl	MVC_DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1389:
	add	x0, x0, 1752
	bl	VP8DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1388:
	add	x0, x0, 1752
	bl	VP6DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1387:
	add	x0, x0, 1752
	bl	REAL9DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1386:
	add	x0, x0, 1752
	bl	REAL8DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1385:
	add	x0, x0, 1752
	bl	AVSDEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1384:
	add	x0, x0, 1752
	bl	DIVX3DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1383:
	add	x0, x0, 1752
	bl	MPEG2DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1382:
	add	x0, x0, 1752
	bl	MPEG4DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1381:
	add	x0, x0, 1752
	bl	VC1DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1379:
	add	x0, x0, 1752
	bl	H264DEC_GetRemainImg
	mov	w19, w0
	b	.L1378
	.p2align 3
.L1405:
	mov	w1, w19
	mov	w0, w20
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC765
	sub	w2, w19, #2
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1402:
	ldr	x2, .LC755
	mov	w3, 7206
	ldr	x4, .LC754
	mov	w0, 0
	ldr	x1, .LC756
	add	x2, x2, 1208
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1376
.L1403:
	ldr	x2, .LC755
	mov	w3, 7207
	ldr	x4, .LC758
	ldr	x1, .LC756
	add	x2, x2, 1208
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1376
	.size	VCTRL_OutputLastFrame, .-VCTRL_OutputLastFrame
	.align	3
.LC754:
	.xword	.LC193
	.align	3
.LC755:
	.xword	.LANCHOR4
	.align	3
.LC756:
	.xword	.LC6
	.align	3
.LC757:
	.xword	.LANCHOR1
	.align	3
.LC758:
	.xword	.LC9
	.align	3
.LC759:
	.xword	.L1380
	.align	3
.LC761:
	.xword	.LC760
	.align	3
.LC763:
	.xword	.LC762
	.align	3
.LC765:
	.xword	.LC764
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_PostProc
	.type	VCTRL_PostProc, %function
VCTRL_PostProc:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x23, x2
	mov	w22, w3
	bl	_mcount
	ldr	x21, .LC766
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1445
	ldr	w1, [x0, 632]
	ldr	w24, [x0, 1312]
	cmp	w1, 18
	bls	.L1446
.L1406:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1446:
	ldr	x2, .LC770
	ldrh	w1, [x2,w1,uxtw #1]
	adr	x2, .Lrtx1410
	add	x1, x2, w1, sxth #2
	br	x1
.Lrtx1410:
	.section	.rodata
	.align	0
	.align	2
.L1410:
	.2byte	(.L1409 - .Lrtx1410) / 4
	.2byte	(.L1411 - .Lrtx1410) / 4
	.2byte	(.L1412 - .Lrtx1410) / 4
	.2byte	(.L1413 - .Lrtx1410) / 4
	.2byte	(.L1406 - .Lrtx1410) / 4
	.2byte	(.L1414 - .Lrtx1410) / 4
	.2byte	(.L1415 - .Lrtx1410) / 4
	.2byte	(.L1406 - .Lrtx1410) / 4
	.2byte	(.L1416 - .Lrtx1410) / 4
	.2byte	(.L1417 - .Lrtx1410) / 4
	.2byte	(.L1418 - .Lrtx1410) / 4
	.2byte	(.L1418 - .Lrtx1410) / 4
	.2byte	(.L1418 - .Lrtx1410) / 4
	.2byte	(.L1419 - .Lrtx1410) / 4
	.2byte	(.L1406 - .Lrtx1410) / 4
	.2byte	(.L1420 - .Lrtx1410) / 4
	.2byte	(.L1421 - .Lrtx1410) / 4
	.2byte	(.L1422 - .Lrtx1410) / 4
	.2byte	(.L1423 - .Lrtx1410) / 4
	.text
	.p2align 3
.L1423:
	add	x0, x0, 507904
	mov	w3, w22
	mov	w2, w24
	mov	w1, w20
	add	x0, x0, 1752
	bl	AVS2DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldrb	w0, [x0, 1752]
	cmp	w0, 1
	beq	.L1447
.L1431:
	cmp	w24, 1
	beq	.L1406
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1800]
	b	.L1406
	.p2align 3
.L1422:
	add	x0, x0, 507904
	mov	w3, w22
	mov	w2, w24
	mov	w1, w20
	add	x0, x0, 1752
	bl	VP9DEC_VDMPostProc
	cmp	w24, 1
	beq	.L1406
.L1443:
	ldr	x0, [x21, w19, sxtw 3]
.L1444:
	add	x0, x0, 507904
	str	xzr, [x0, 1760]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1421:
	add	x0, x0, 507904
	mov	w5, w22
	mov	w4, w24
	mov	x3, x23
	mov	w2, 1
	mov	w1, w20
	add	x0, x0, 1752
	bl	HEVCDEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldrb	w0, [x0, 1763]
	cmp	w0, 1
	beq	.L1448
.L1426:
	cmp	w24, 1
	beq	.L1406
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 512000
	str	xzr, [x0, 712]
	b	.L1406
	.p2align 3
.L1420:
	add	x0, x0, 507904
	mov	w1, w20
	mov	w2, 1
	add	x0, x0, 1752
	bl	MVC_DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldrb	w1, [x0, 1753]
	cmp	w1, 1
	beq	.L1449
	str	xzr, [x0, 1984]
	b	.L1406
	.p2align 3
.L1419:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1752
	bl	VP8DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1760]
	b	.L1406
	.p2align 3
.L1418:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1752
	bl	VP6DEC_VDMPostProc
	b	.L1443
	.p2align 3
.L1417:
	mov	w0, w22
	bl	VDMDRV_GetMb0QpInCurrPic
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 507904
	add	x0, x0, 1752
	bl	REAL9DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1760]
	b	.L1406
	.p2align 3
.L1416:
	mov	w0, w22
	bl	VDMDRV_GetMb0QpInCurrPic
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 507904
	add	x0, x0, 1752
	bl	REAL8DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1760]
	b	.L1406
	.p2align 3
.L1415:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1752
	bl	AVSDEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldrb	w1, [x0, 1752]
	cmp	w1, 1
	beq	.L1450
	str	xzr, [x0, 1776]
	b	.L1406
	.p2align 3
.L1414:
	mov	w0, w22
	bl	VDMDRV_GetSwitchRounding
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 507904
	add	x0, x0, 1752
	bl	DIVX3DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 1760]
	b	.L1406
	.p2align 3
.L1413:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1752
	bl	MPEG2DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 598016
	ldrb	w1, [x1, 1058]
	cmp	w1, 1
	bne	.L1444
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 598016
	strb	wzr, [x1, 1058]
	b	.L1444
	.p2align 3
.L1412:
	add	x0, x0, 507904
	mov	w1, w20
	mov	x2, x23
	add	x0, x0, 1752
	bl	MPEG4DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 532480
	ldrb	w1, [x1, 540]
	cmp	w1, 1
	beq	.L1451
.L1429:
	add	x0, x0, 507904
	str	xzr, [x0, 2792]
	b	.L1406
	.p2align 3
.L1411:
	add	x0, x0, 507904
	mov	w1, w20
	add	x0, x0, 1752
	bl	VC1DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 524288
	ldrb	w1, [x1, 183]
	cmp	w1, 1
	bne	.L1444
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 524288
	strb	wzr, [x1, 183]
	b	.L1444
	.p2align 3
.L1409:
	add	x0, x0, 507904
	mov	w5, w22
	mov	w4, w24
	mov	x3, x23
	mov	w2, 1
	mov	w1, w20
	add	x0, x0, 1752
	bl	H264DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 524288
	ldrb	w0, [x0, 296]
	cmp	w0, 1
	beq	.L1452
.L1424:
	cmp	w24, 1
	beq	.L1406
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	str	xzr, [x0, 2368]
	b	.L1406
	.p2align 3
.L1450:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	strb	wzr, [x0, 1752]
	str	xzr, [x0, 1776]
	b	.L1406
	.p2align 3
.L1449:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	strb	wzr, [x0, 1753]
	str	xzr, [x0, 1984]
	b	.L1406
	.p2align 3
.L1445:
	ldr	x2, .LC768
	mov	w3, 4036
	ldr	x4, .LC767
	ldr	x1, .LC769
	add	x2, x2, 1232
	bl	dprint_vfmw
	b	.L1406
	.p2align 3
.L1451:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 532480
	strb	wzr, [x1, 540]
	b	.L1429
.L1452:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 524288
	strb	wzr, [x0, 296]
	b	.L1424
.L1448:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	strb	wzr, [x0, 1763]
	b	.L1426
.L1447:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	strb	wzr, [x0, 1752]
	b	.L1431
	.size	VCTRL_PostProc, .-VCTRL_PostProc
	.align	3
.LC766:
	.xword	.LANCHOR1
	.align	3
.LC767:
	.xword	.LC9
	.align	3
.LC768:
	.xword	.LANCHOR4
	.align	3
.LC769:
	.xword	.LC6
	.align	3
.LC770:
	.xword	.L1410
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_VdmPostProc
	.type	VCTRL_VdmPostProc, %function
VCTRL_VdmPostProc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	mov	w22, w3
	bl	_mcount
	cmp	w19, 31
	bhi	.L1461
	ldr	x0, .LC774
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1462
	ldr	w0, [x0, 8]
	cmp	w0, 1
	beq	.L1457
	ldr	x2, .LC772
	mov	w3, 4226
	ldr	x4, .LC776
	mov	w0, 0
	ldr	x1, .LC773
	add	x2, x2, 1248
	bl	dprint_vfmw
.L1453:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1457:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbz	x0, .L1453
	mov	w3, w22
	mov	x2, x21
	mov	w1, w20
	mov	w0, w19
	bl	VCTRL_PostProc
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1461:
	ldr	x2, .LC772
	mov	w3, 4224
	ldr	x4, .LC771
	mov	w0, 0
	ldr	x1, .LC773
	add	x2, x2, 1248
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1462:
	ldr	x2, .LC772
	mov	w3, 4225
	ldr	x4, .LC775
	ldr	x1, .LC773
	add	x2, x2, 1248
	bl	dprint_vfmw
	b	.L1453
	.size	VCTRL_VdmPostProc, .-VCTRL_VdmPostProc
	.align	3
.LC771:
	.xword	.LC466
	.align	3
.LC772:
	.xword	.LANCHOR4
	.align	3
.LC773:
	.xword	.LC6
	.align	3
.LC774:
	.xword	.LANCHOR1
	.align	3
.LC775:
	.xword	.LC426
	.align	3
.LC776:
	.xword	.LC472
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SvdecLastFrame
	.type	VCTRL_SvdecLastFrame, %function
VCTRL_SvdecLastFrame:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w19, 31
	bhi	.L1466
	add	w1, w20, 2
	mov	w0, w19
	bl	VCTRL_ReportLastFrame
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1466:
	ldr	x2, .LC778
	mov	w3, 7332
	ldr	x4, .LC777
	mov	w0, 0
	ldr	x1, .LC779
	add	x2, x2, 1272
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SvdecLastFrame, .-VCTRL_SvdecLastFrame
	.align	3
.LC777:
	.xword	.LC193
	.align	3
.LC778:
	.xword	.LANCHOR4
	.align	3
.LC779:
	.xword	.LC6
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	Get_YuvFormat
	.type	Get_YuvFormat, %function
Get_YuvFormat:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 6
	bls	.L1485
	ldr	x1, .LC782
	mov	w3, w19
	mov	w2, 7816
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 13
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1485:
	ldr	x0, .LC780
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1470
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1470:
	.section	.rodata
	.align	0
	.align	2
.L1470:
	.byte	(.L1469 - .Lrtx1470) / 4
	.byte	(.L1471 - .Lrtx1470) / 4
	.byte	(.L1472 - .Lrtx1470) / 4
	.byte	(.L1473 - .Lrtx1470) / 4
	.byte	(.L1474 - .Lrtx1470) / 4
	.byte	(.L1475 - .Lrtx1470) / 4
	.byte	(.L1476 - .Lrtx1470) / 4
	.text
	.p2align 3
.L1475:
	cmp	w20, 1
	mov	w1, 12
	mov	w0, 13
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1476:
	cmp	w20, 1
	mov	w0, 7
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1469:
	cmp	w20, 1
	mov	w0, 6
	csel	w0, wzr, w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1471:
	cmp	w20, 1
	mov	w1, 8
	mov	w0, 2
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1472:
	cmp	w20, 1
	mov	w1, 10
	mov	w0, 4
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1473:
	cmp	w20, 1
	mov	w1, 9
	mov	w0, 3
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1474:
	cmp	w20, 1
	mov	w1, 11
	mov	w0, 5
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_YuvFormat, .-Get_YuvFormat
	.align	3
.LC780:
	.xword	.L1470
	.align	3
.LC782:
	.xword	.LC781
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_PutUsrdecFrame
	.type	VDH_PutUsrdecFrame, %function
VDH_PutUsrdecFrame:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w21, w0
	mov	x20, x1
	mov	x0, x30
	bl	_mcount
	ldr	w1, [x20, 40]
	mov	w0, w21
	bl	FSP_GetLogicIdByPhyAddr
	cmn	w0, #1
	mov	w22, w0
	beq	.L1495
	ldr	w0, [x20, 4]
	cmp	w0, 1
	beq	.L1489
	mov	w0, w21
	mov	w2, 0
	mov	w1, w22
	bl	FSP_ClearLogicFs
	mov	w0, 0
.L1488:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1489:
	ldr	w0, [x20, 48]
	bl	MEM_Phy2Vir
	cbz	x0, .L1496
.L1490:
	mov	w1, w22
	mov	w0, w21
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1497
	str	w22, [x0, 148]
	mov	w23, 1
	ldr	x0, [x20, 64]
	str	x0, [x19, 576]
	ldr	x0, [x20, 64]
	str	x0, [x19, 584]
	ldr	x0, [x20, 64]
	str	x0, [x19, 592]
	ldr	x0, [x20, 64]
	str	x0, [x19, 600]
	stp	w23, wzr, [x19]
	stp	wzr, wzr, [x19, 8]
	ldr	w0, [x20, 40]
	str	w0, [x19, 20]
	str	w0, [x19, 36]
	ldr	w1, [x20, 48]
	str	w1, [x19, 24]
	str	w1, [x19, 40]
	bl	MEM_Phy2Vir
	str	x0, [x19, 504]
	ldr	w0, [x19, 24]
	bl	MEM_Phy2Vir
	str	x0, [x19, 512]
	ldr	w0, [x19, 20]
	mov	x2, 4
	ldr	w1, [x20, 44]
	ldr	w3, [x19, 24]
	add	w1, w0, w1
	str	w1, [x19, 28]
	ldr	x4, .LC789
	ldr	w0, [x20, 44]
	str	wzr, [x19, 52]
	add	w0, w3, w0
	str	w0, [x19, 32]
	ldr	w0, [x20, 12]
	str	w0, [x19, 68]
	ldr	w0, [x20, 16]
	str	w0, [x19, 72]
	ldr	w0, [x20, 12]
	str	w0, [x19, 76]
	lsr	w1, w0, 1
	ldr	w0, [x20, 16]
	stp	w0, w1, [x19, 80]
	lsr	w0, w0, 1
	str	w0, [x19, 88]
	mov	w1, 0
	add	x0, x19, 64
	ldr	w3, [x20, 44]
	ldr	x4, [x4, 96]
	stp	wzr, w3, [x19, 108]
	str	wzr, [x19, 152]
	lsr	w3, w3, 1
	str	w23, [x19, 164]
	str	w3, [x19, 116]
	blr	x4
	ldrb	w0, [x19, 65]
	ldrb	w1, [x19, 64]
	and	w0, w0, -4
	and	w1, w1, 224
	orr	w0, w0, 12
	bfi	w1, w23, 5, 3
	bfi	w0, w23, 4, 2
	strb	w1, [x19, 64]
	strb	w0, [x19, 65]
	ldr	w0, [x20, 24]
	str	w0, [x19, 212]
	bl	MEM_Phy2Vir
	str	x0, [x19, 520]
	ldr	w1, [x20]
	ldr	w0, [x20, 8]
	bl	Get_YuvFormat
	cmp	w0, 13
	beq	.L1498
	str	w0, [x19, 388]
	mov	w24, 20
	mov	w2, w23
	mov	w1, w22
	ldr	w3, [x20, 56]
	mov	w0, w21
	str	w3, [x19, 364]
	ldr	w3, [x20, 60]
	str	w3, [x19, 360]
	ldr	w3, [x20, 52]
	str	w3, [x19, 368]
	str	w24, [x19, 296]
	bl	FSP_SetDisplay
	ldr	x2, .LC792
	mov	x4, x19
	mov	w1, w24
	mov	w0, w21
	ldr	x2, [x2, w21, sxtw 3]
	add	x2, x2, 507904
	add	x3, x2, 1760
	add	x2, x2, 1752
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w0, 0
	beq	.L1488
	ldr	x1, [x19, 544]
	mov	w0, w21
	bl	FreeUsdByDec
	str	xzr, [x19, 544]
	ldr	x1, [x19, 552]
	mov	w0, w21
	bl	FreeUsdByDec
	str	xzr, [x19, 552]
	mov	w0, w21
	mov	w2, 0
	mov	w1, w22
	bl	FSP_SetDisplay
	mov	w0, -1
	b	.L1488
	.p2align 3
.L1496:
	ldr	w0, [x20, 4]
	cmp	w0, 1
	bne	.L1490
	ldr	x1, .LC786
	mov	w0, 0
	ldr	w2, [x20, 48]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1488
.L1495:
	ldr	x1, .LC784
	mov	w0, 0
	ldr	w2, [x20, 40]
	bl	dprint_vfmw
	mov	w0, w22
	b	.L1488
.L1498:
	ldr	x1, .LC791
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1488
.L1497:
	ldr	x1, .LC788
	mov	w2, 4519
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1488
	.size	VDH_PutUsrdecFrame, .-VDH_PutUsrdecFrame
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
.LC789:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC791:
	.xword	.LC790
	.align	3
.LC792:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_PutUsrdecFrame
	.type	VCTRL_PutUsrdecFrame, %function
VCTRL_PutUsrdecFrame:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	ldr	x20, .LC793
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1507
	cbz	x21, .L1508
	ldr	w2, [x0, 632]
	cmp	w2, 20
	bne	.L1509
	ldr	x3, .LC801
	mov	x1, x21
	mov	x2, 72
	add	x0, x0, 560
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 560
	bl	VDH_PutUsrdecFrame
	cbnz	w0, .L1510
.L1501:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1509:
	ldr	x1, .LC800
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1501
	.p2align 3
.L1510:
	ldr	x1, .LC803
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1501
.L1508:
	ldr	x2, .LC795
	mov	w3, 4660
	ldr	x4, .LC798
	mov	w0, 0
	ldr	x1, .LC796
	add	x2, x2, 1296
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1501
.L1507:
	ldr	x2, .LC795
	mov	w3, 4659
	ldr	x4, .LC794
	ldr	x1, .LC796
	add	x2, x2, 1296
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1501
	.size	VCTRL_PutUsrdecFrame, .-VCTRL_PutUsrdecFrame
	.align	3
.LC793:
	.xword	.LANCHOR1
	.align	3
.LC794:
	.xword	.LC9
	.align	3
.LC795:
	.xword	.LANCHOR4
	.align	3
.LC796:
	.xword	.LC6
	.align	3
.LC798:
	.xword	.LC797
	.align	3
.LC800:
	.xword	.LC799
	.align	3
.LC801:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC803:
	.xword	.LC802
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ResetHardware
	.type	VCTRL_ResetHardware, %function
VCTRL_ResetHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	SCDDRV_ResetSCD
	mov	w0, w19
	bl	VDMDRV_ResetVDH
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_ResetHardware, .-VCTRL_ResetHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CanBeDecodedByHardWare
	.type	VCTRL_CanBeDecodedByHardWare, %function
VCTRL_CanBeDecodedByHardWare:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 4
	mov	w0, 0
	ccmp	w19, 7, 4, ne
	beq	.L1513
	mov	w0, w19
	bl	VCTRL_CanBeDecodedByHardWare.part.25
.L1513:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_CanBeDecodedByHardWare, .-VCTRL_CanBeDecodedByHardWare
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IsChanOpenAndRun
	.type	VCTRL_IsChanOpenAndRun, %function
VCTRL_IsChanOpenAndRun:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19, 4]
	cmp	w0, 1
	beq	.L1518
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1518:
	ldr	w0, [x19, 8]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_IsChanOpenAndRun, .-VCTRL_IsChanOpenAndRun
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_OpenHardware
	.type	VCTRL_OpenHardware, %function
VCTRL_OpenHardware:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, 31
	bhi	.L1554
	ldr	x20, .LC806
	ldr	x0, [x20, w21, sxtw 3]
	cbz	x0, .L1555
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L1523
	ldr	w0, [x0, 632]
	cmp	w0, 22
	beq	.L1523
	cmp	w0, 7
	ccmp	w0, 4, 4, ne
	beq	.L1519
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cbz	w0, .L1519
	mov	x19, 0
	mov	w22, 0
	.p2align 2
.L1528:
	mov	w0, w19
	bl	VCTRL_IsChanActive
	cbnz	w0, .L1527
	ldr	x0, [x20, x19, lsl 3]
	ldr	w1, [x0, 632]
	cmp	w1, 4
	mov	w0, w1
	ccmp	w1, 7, 4, ne
	beq	.L1527
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cmp	w0, wzr
	csinc	w22, w22, w22, eq
.L1527:
	add	x19, x19, 1
	cmp	x19, 32
	bne	.L1528
	cmp	w22, 1
	beq	.L1556
.L1529:
	mov	x0, x20
	add	x3, x20, 256
	mov	w2, 0
	.p2align 2
.L1536:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L1535
	ldr	w1, [x1, 632]
	cmp	w1, 6
	csinc	w2, w2, wzr, ne
.L1535:
	cmp	x0, x3
	bne	.L1536
	cmp	w2, 1
	beq	.L1557
.L1537:
	ldr	x0, [x20, w21, sxtw 3]
	ldr	w0, [x0, 632]
	cmp	w0, 1
	bne	.L1519
	ldr	x0, .LC811
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L1558
	ldr	x0, .LC812
	ldr	x1, [x0, 56]
	cbz	x1, .L1519
	mov	w0, 0
	blr	x1
	b	.L1519
	.p2align 3
.L1523:
	ldr	x1, .LC810
	mov	w2, 7877
	mov	w0, 0
	bl	dprint_vfmw
.L1519:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1554:
	ldr	x1, .LC805
	mov	w2, 7865
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1556:
	ldr	x19, .LC811
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1559
	mov	w1, 0
	mov	w0, w22
	bl	VDH_Need_Module
.L1532:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L1533
	ldr	x0, .LC812
	ldr	x1, [x0, 40]
	cbz	x1, .L1560
	mov	w0, 0
	blr	x1
	b	.L1529
.L1557:
	ldr	x0, .LC811
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1561
	mov	w1, 0
	mov	w0, 3
	bl	VDH_Need_Module
	b	.L1537
.L1561:
	ldr	x0, .LC812
	ldr	x1, [x0, 24]
	cbz	x1, .L1562
	mov	w0, 0
	blr	x1
	b	.L1537
.L1559:
	ldr	x0, .LC812
	ldr	x1, [x0, 8]
	cbz	x1, .L1563
	mov	w0, 0
	blr	x1
	b	.L1532
.L1555:
	ldr	x1, .LC808
	mov	w2, 7871
	bl	dprint_vfmw
	b	.L1519
.L1558:
	mov	w1, 0
	mov	w0, 2
	bl	VDH_Need_Module
	b	.L1519
.L1533:
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Need_Module
	b	.L1529
.L1560:
	ldr	x1, .LC813
	mov	w2, 7926
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1529
.L1562:
	ldr	x1, .LC813
	mov	w2, 7957
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1537
.L1563:
	ldr	x1, .LC813
	mov	w2, 7912
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1532
	.size	VCTRL_OpenHardware, .-VCTRL_OpenHardware
	.align	3
.LC805:
	.xword	.LC804
	.align	3
.LC806:
	.xword	.LANCHOR1
	.align	3
.LC808:
	.xword	.LC807
	.align	3
.LC810:
	.xword	.LC809
	.align	3
.LC811:
	.xword	g_HalDisable
	.align	3
.LC812:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC813:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StartChan
	.type	VCTRL_StartChan, %function
VCTRL_StartChan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	cmp	w20, 31
	bhi	.L1575
	ldr	x19, .LC818
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L1576
	ldr	w21, [x0, 4]
	cmp	w21, 1
	bne	.L1577
	ldr	w0, [x0, 632]
	cmp	w0, 22
	beq	.L1578
	mov	w0, w20
	bl	SM_Start
	ldr	x0, [x19, w20, sxtw 3]
	add	x1, x0, 507904
	str	w21, [x1, 1740]
	str	w21, [x0, 8]
	ldr	x0, [x19, w20, sxtw 3]
	str	w21, [x0, 12]
	ldr	x0, [x19, w20, sxtw 3]
	str	wzr, [x0, 24]
	ldr	x0, [x19, w20, sxtw 3]
	str	w21, [x0, 16]
	ldr	x1, [x19, w20, sxtw 3]
	ldr	w0, [x1, 20]
	cbnz	w0, .L1570
	str	w21, [x1, 20]
	mov	x1, 0
	ldr	x0, .LC823
	ldr	x5, .LC824
	b	.L1573
	.p2align 3
.L1580:
	ldr	w4, [x2, 20]
	str	w4, [x3, x1, lsl 2]
	ldr	w2, [x2, 20]
	str	w2, [x5, x1, lsl 2]
	add	x1, x1, 1
	cmp	x1, 32
	beq	.L1579
.L1573:
	ldr	x2, [x19, x1, lsl 3]
	add	x3, x0, 1544
	cbnz	x2, .L1580
	add	x2, x0, 1544
	str	wzr, [x5, x1, lsl 2]
	str	wzr, [x2, x1, lsl 2]
	add	x1, x1, 1
	cmp	x1, 32
	bne	.L1573
	.p2align 2
.L1579:
	add	x0, x0, 1544
	bl	VDMDRV_SetPriority
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
.L1570:
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w20
	bl	VCTRL_OpenHardware
	ldr	x19, .LC825
	ldr	x0, .LC826
	mov	x2, 12
	mov	w1, 0
	ldr	x3, [x19, 96]
	blr	x3
	ldr	x3, [x19, 96]
	mov	x2, 720
	ldr	x0, .LC827
	mov	w1, 0
	blr	x3
	ldr	x3, [x19, 96]
	mov	x2, 2
	ldr	x0, .LC828
	mov	w1, 0
	blr	x3
	ldr	x0, .LC829
	mov	x2, 120
	ldr	x3, [x19, 96]
	mov	w1, 0
	blr	x3
	mov	w0, 0
.L1566:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1577:
	ldr	x2, .LC816
	mov	w3, 2310
	ldr	x4, .LC820
	mov	w0, 0
	ldr	x1, .LC817
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1566
.L1575:
	ldr	x2, .LC816
	mov	w3, 2308
	ldr	x4, .LC815
	mov	w0, 0
	ldr	x1, .LC817
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1566
.L1578:
	ldr	x2, .LC816
	mov	w3, 2311
	ldr	x4, .LC822
	mov	w0, 0
	ldr	x1, .LC817
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1566
.L1576:
	ldr	x2, .LC816
	mov	w3, 2309
	ldr	x4, .LC819
	ldr	x1, .LC817
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1566
	.size	VCTRL_StartChan, .-VCTRL_StartChan
	.align	3
.LC815:
	.xword	.LC193
	.align	3
.LC816:
	.xword	.LANCHOR4
	.align	3
.LC817:
	.xword	.LC6
	.align	3
.LC818:
	.xword	.LANCHOR1
	.align	3
.LC819:
	.xword	.LC292
	.align	3
.LC820:
	.xword	.LC488
	.align	3
.LC822:
	.xword	.LC821
	.align	3
.LC823:
	.xword	.LANCHOR5
	.align	3
.LC824:
	.xword	g_ChanCtx
	.align	3
.LC825:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC826:
	.xword	g_TimeRecId
	.align	3
.LC827:
	.xword	g_TimeRecTable
	.align	3
.LC828:
	.xword	g_DataRecId
	.align	3
.LC829:
	.xword	g_DataTable
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestStartChan, %function
VfmwProc_TestStartChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	mov	w0, w19
	bl	VCTRL_StartChan
	mov	w3, w0
	ldr	x1, .LC832
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStartChan, .-VfmwProc_TestStartChan
	.align	3
.LC832:
	.xword	.LC831
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CloseHardware
	.type	VCTRL_CloseHardware, %function
VCTRL_CloseHardware:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w25, w0
	mov	x0, x30
	mov	w24, 0
	mov	w22, 0
	bl	_mcount
	ldr	x19, .LC833
	mov	w0, 0
	add	x23, x19, 256
	b	.L1591
	.p2align 3
.L1633:
	ldr	w1, [x20, 4]
	cmp	w1, 1
	beq	.L1630
.L1583:
	add	x19, x19, 8
	cmp	x19, x23
	beq	.L1631
.L1591:
	ldr	x20, [x19]
	cbz	x20, .L1583
	ldr	w21, [x20, 632]
	cbnz	w0, .L1584
	ldr	w1, [x20, 4]
	cmp	w1, 1
	beq	.L1632
.L1584:
	cmp	w22, wzr
	ccmp	w21, 1, 0, eq
	beq	.L1633
.L1587:
	cmp	w24, wzr
	ccmp	w21, 6, 0, eq
	bne	.L1583
	ldr	w1, [x20, 4]
	cmp	w1, 1
	bne	.L1583
	ldr	w26, [x20, 8]
.L1611:
	cmp	w26, 1
	add	x19, x19, 8
	csinc	w24, w24, wzr, ne
	cmp	x19, x23
	bne	.L1591
	.p2align 2
.L1631:
	cbnz	w0, .L1592
	ldr	x19, .LC834
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1597
	mov	w0, w25
	bl	SCDDRV_ResetSCD
	mov	w0, w25
	bl	VDMDRV_ResetVDH
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1597
	mov	w1, 0
	mov	w0, 1
	bl	VDH_UnNeed_Module
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L1600
.L1639:
	ldr	x0, .LC835
	ldr	x1, [x0, 48]
	cbz	x1, .L1634
	mov	w0, 0
	blr	x1
.L1603:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle
.L1592:
	cbnz	w24, .L1604
	ldr	x0, .LC834
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1635
	mov	w1, 0
	mov	w0, 3
	bl	VDH_UnNeed_Module
.L1604:
	cbnz	w22, .L1582
	ldr	x0, .LC834
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L1636
	ldr	x0, .LC835
	ldr	x1, [x0, 64]
	cbz	x1, .L1582
	mov	w0, 0
	blr	x1
.L1582:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1632:
	ldr	w26, [x20, 8]
	cmp	w26, 1
	beq	.L1637
.L1586:
	cmp	w21, 1
	ccmp	w22, wzr, 0, eq
	bne	.L1587
.L1610:
	cmp	w26, 1
	csinc	w22, w22, wzr, ne
	cmp	w21, 6
	ccmp	w24, wzr, 0, eq
	beq	.L1611
	b	.L1583
	.p2align 3
.L1637:
	cmp	w21, 4
	ccmp	w21, 7, 4, ne
	beq	.L1586
	mov	w0, w21
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cmp	w0, wzr
	cset	w0, ne
	b	.L1586
.L1597:
	ldr	x0, .LC835
	ldr	x1, [x0, 16]
	cbz	x1, .L1638
	mov	w0, 0
	blr	x1
.L1599:
	mov	w0, 0
	bl	VDMDRV_SetStateIdle
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1639
.L1600:
	mov	w1, 0
	mov	w0, 0
	bl	VDH_UnNeed_Module
	b	.L1592
.L1636:
	mov	w1, 0
	mov	w0, 2
	bl	VDH_UnNeed_Module
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1635:
	ldr	x0, .LC835
	ldr	x1, [x0, 32]
	cbz	x1, .L1640
	mov	w0, 0
	blr	x1
	b	.L1604
.L1634:
	ldr	x1, .LC836
	mov	w2, 8051
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1603
.L1638:
	ldr	x1, .LC836
	mov	w2, 8036
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1599
.L1640:
	ldr	x1, .LC836
	mov	w2, 8069
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1604
.L1630:
	ldr	w26, [x20, 8]
	b	.L1610
	.size	VCTRL_CloseHardware, .-VCTRL_CloseHardware
	.align	3
.LC833:
	.xword	.LANCHOR1
	.align	3
.LC834:
	.xword	g_HalDisable
	.align	3
.LC835:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC836:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StopChan
	.type	VCTRL_StopChan, %function
VCTRL_StopChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1647
	ldr	x20, .LC841
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1648
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L1646
	str	w1, [x0, 24]
	mov	w0, w19
	ldr	x1, [x20, w19, sxtw 3]
	str	wzr, [x1, 12]
	ldr	x1, [x20, w19, sxtw 3]
	str	wzr, [x1, 8]
	bl	SM_Stop
	cbnz	w0, .L1646
	mov	w1, 0
	mov	w0, w19
	bl	DeleteRawPacketInBuffer
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	str	wzr, [x1, 24]
	bl	VCTRL_CloseHardware
	mov	w0, 0
.L1643:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1646:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1647:
	ldr	x2, .LC839
	mov	w3, 2395
	ldr	x4, .LC838
	mov	w0, 0
	ldr	x1, .LC840
	add	x2, x2, 1336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1643
.L1648:
	ldr	x2, .LC839
	mov	w3, 2396
	ldr	x4, .LC843
	ldr	x1, .LC840
	add	x2, x2, 1336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1643
	.size	VCTRL_StopChan, .-VCTRL_StopChan
	.align	3
.LC838:
	.xword	.LC193
	.align	3
.LC839:
	.xword	.LANCHOR4
	.align	3
.LC840:
	.xword	.LC6
	.align	3
.LC841:
	.xword	.LANCHOR1
	.align	3
.LC843:
	.xword	.LC842
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_StopChanWithCheck
	.type	VCTRL_StopChanWithCheck, %function
VCTRL_StopChanWithCheck:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	mov	w20, 0
	bl	_mcount
	ldr	x19, .LC844
	b	.L1651
	.p2align 3
.L1655:
	ldr	x1, [x19, 240]
	mov	w0, 10
	add	w20, w20, 1
	blr	x1
	cmp	w20, 50
	beq	.L1653
.L1651:
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	mov	w0, w22
	bl	VCTRL_StopChan
	mov	w21, w0
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	cbnz	w21, .L1655
	cmp	w20, 49
	bgt	.L1653
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1653:
	ldr	x1, .LC846
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	VCTRL_StopChanWithCheck, .-VCTRL_StopChanWithCheck
	.align	3
.LC844:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC846:
	.xword	.LC845
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ResetChanWithOption
	.type	VCTRL_ResetChanWithOption, %function
VCTRL_ResetChanWithOption:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	x21, x1
	bl	_mcount
	cmp	w19, 31
	bhi	.L1682
	ldr	x20, .LC850
	sxtw	x24, w19
	ldr	x1, [x20, w19, sxtw 3]
	cbz	x1, .L1683
	ldr	w0, [x21]
	cmp	w0, 1
	bhi	.L1684
	mov	w0, w19
	ldr	w23, [x1, 8]
	bl	VCTRL_StopChan
	ldr	x22, .LC854
	ldr	x3, [x20, w19, sxtw 3]
	lsl	x0, x24, 2
	ldr	x1, .LC855
	sub	x2, x0, x24
	ldr	x4, [x22, 96]
	add	x0, x1, 776
	str	wzr, [x3, 480]
	str	wzr, [x3, 484]
	add	x0, x0, x2, lsl 3
	mov	w1, 0
	mov	x2, 24
	blr	x4
	mov	w1, 0
	mov	w0, w19
	bl	VCTRL_SetSendStreamAgainFlag
	ldr	x1, [x22, 24]
	mov	w0, 4
	blr	x1
	mov	w0, w19
	bl	VCTRL_FindOccupiedFrame
	ldr	x1, [x22, 32]
	mov	w0, 4
	blr	x1
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	ldr	w2, [x21, 4]
	str	w2, [x1, 1304]
	bl	InitSyntaxCtx
	ldr	x0, [x20, w19, sxtw 3]
	add	x1, x0, 507904
	ldr	w0, [x0, 632]
	add	x1, x1, 1752
	bl	ReleaseCurPic
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, 456
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 784
	blr	x3
	ldr	x0, [x20, w19, sxtw 3]
	mov	x1, -1
	ldr	w2, [x0, 1552]
	str	x1, [x0, 704]
	cmp	w2, 1
	str	x1, [x0, 712]
	str	wzr, [x0, 1240]
	str	wzr, [x0, 1636]
	beq	.L1685
.L1661:
	ldr	w0, [x0, 632]
	cmp	w0, 20
	beq	.L1662
	ldr	w0, [x21, 8]
	cbz	w0, .L1686
.L1662:
	mov	w0, w19
	bl	FSP_EmptyInstance
.L1663:
	mov	w0, w19
	bl	InitUsdPool
	ldr	w0, [x21]
	cbz	w0, .L1687
.L1664:
	ldr	w0, [x20, 1396]
	cbz	w0, .L1665
	add	x20, x20, 2192
	str	w19, [x29, 76]
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1667
	mov	w0, 512
	add	x1, x29, 76
	bl	VCTRL_SetDbgOption
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1667
	add	x1, x29, 76
	mov	w0, 512
	bl	VCTRL_SetDbgOption
.L1667:
	ldr	x1, .LC857
	mov	w0, 32
	bl	dprint_vfmw
.L1665:
	cbnz	w23, .L1688
.L1669:
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, 0
.L1658:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1687:
	mov	w0, w19
	bl	SM_Reset
	b	.L1664
	.p2align 3
.L1688:
	mov	w0, w19
	bl	VCTRL_StartChan
	b	.L1669
	.p2align 3
.L1685:
	add	x1, x0, 507904
	str	wzr, [x0, 1600]
	str	wzr, [x1, 1676]
	b	.L1661
	.p2align 3
.L1686:
	mov	w0, w19
	bl	FSP_ResetInstance
	b	.L1663
	.p2align 3
.L1684:
	ldr	x1, .LC853
	mov	w2, 2972
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1658
	.p2align 3
.L1682:
	ldr	x2, .LC848
	mov	w3, 2967
	ldr	x4, .LC847
	mov	w0, 0
	ldr	x1, .LC849
	add	x2, x2, 1352
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1658
.L1683:
	ldr	x2, .LC848
	mov	w3, 2968
	ldr	x4, .LC851
	mov	w0, 0
	ldr	x1, .LC849
	add	x2, x2, 1352
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1658
	.size	VCTRL_ResetChanWithOption, .-VCTRL_ResetChanWithOption
	.align	3
.LC847:
	.xword	.LC376
	.align	3
.LC848:
	.xword	.LANCHOR4
	.align	3
.LC849:
	.xword	.LC6
	.align	3
.LC850:
	.xword	.LANCHOR1
	.align	3
.LC851:
	.xword	.LC381
	.align	3
.LC853:
	.xword	.LC852
	.align	3
.LC854:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC855:
	.xword	.LANCHOR5
	.align	3
.LC857:
	.xword	.LC856
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ResetChan
	.type	VCTRL_ResetChan, %function
VCTRL_ResetChan:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L1711
	ldr	x20, .LC863
	ldr	x1, [x20, w19, sxtw 3]
	cbz	x1, .L1712
	mov	w0, w19
	ldr	w22, [x1, 8]
	bl	VCTRL_StopChan
	ldr	x21, .LC865
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, 4
	ldr	x2, [x21, 24]
	str	wzr, [x1, 480]
	str	wzr, [x1, 484]
	blr	x2
	ldr	x0, [x20, w19, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	beq	.L1713
.L1693:
	sxtw	x3, w19
	ldr	x1, .LC866
	lsl	x0, x3, 2
	ldr	x4, [x21, 96]
	sub	x3, x0, x3
	add	x0, x1, 776
	mov	x2, 24
	mov	w1, 0
	add	x0, x0, x3, lsl 3
	blr	x4
	mov	w1, 0
	mov	w0, w19
	bl	VCTRL_SetSendStreamAgainFlag
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	str	wzr, [x1, 1304]
	bl	InitSyntaxCtx
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, 456
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x0, x0, 784
	blr	x3
	ldr	x0, [x20, w19, sxtw 3]
	mov	x2, -1
	add	x1, x0, 507904
	str	x2, [x0, 704]
	str	x2, [x0, 712]
	str	wzr, [x0, 1240]
	str	wzr, [x1, 1696]
	str	wzr, [x1, 1700]
	str	wzr, [x1, 1704]
	str	wzr, [x0, 1636]
	ldr	w2, [x0, 1552]
	cmp	w2, 1
	beq	.L1714
.L1694:
	ldr	w0, [x0, 632]
	cmp	w0, 20
	mov	w0, w19
	beq	.L1695
	bl	FSP_ResetInstance
.L1696:
	ldr	x1, [x21, 32]
	mov	w0, 4
	blr	x1
	mov	w0, w19
	bl	InitUsdPool
	mov	w0, w19
	bl	SM_Reset
	ldr	w0, [x20, 1396]
	cbz	w0, .L1697
	add	x20, x20, 2192
	str	w19, [x29, 60]
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1699
	mov	w0, 512
	add	x1, x29, 60
	bl	VCTRL_SetDbgOption
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1699
	add	x1, x29, 60
	mov	w0, 512
	bl	VCTRL_SetDbgOption
.L1699:
	ldr	x1, .LC867
	mov	w0, 32
	bl	dprint_vfmw
.L1697:
	cbnz	w22, .L1715
.L1701:
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, 0
.L1691:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1715:
	mov	w0, w19
	bl	VCTRL_StartChan
	b	.L1701
	.p2align 3
.L1695:
	bl	FSP_EmptyInstance
	b	.L1696
	.p2align 3
.L1714:
	str	wzr, [x0, 1600]
	str	wzr, [x1, 1676]
	b	.L1694
	.p2align 3
.L1713:
	add	x1, x0, 507904
	ldr	w2, [x0, 632]
	ldr	w1, [x1, 1744]
	cmp	w1, w2
	bne	.L1693
	str	wzr, [x0, 12]
	mov	w0, w19
	bl	VCTRL_FindOccupiedFrame
	b	.L1693
	.p2align 3
.L1711:
	ldr	x2, .LC861
	mov	w3, 3310
	ldr	x4, .LC860
	mov	w0, 0
	ldr	x1, .LC862
	add	x2, x2, 1384
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1691
.L1712:
	ldr	x2, .LC861
	mov	w3, 3311
	ldr	x4, .LC864
	mov	w0, 0
	ldr	x1, .LC862
	add	x2, x2, 1384
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1691
	.size	VCTRL_ResetChan, .-VCTRL_ResetChan
	.align	3
.LC860:
	.xword	.LC376
	.align	3
.LC861:
	.xword	.LANCHOR4
	.align	3
.LC862:
	.xword	.LC6
	.align	3
.LC863:
	.xword	.LANCHOR1
	.align	3
.LC864:
	.xword	.LC381
	.align	3
.LC865:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC866:
	.xword	.LANCHOR5
	.align	3
.LC867:
	.xword	.LC856
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CreateChan
	.type	VCTRL_CreateChan, %function
VCTRL_CreateChan:
	stp	x29, x30, [sp, -336]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	mov	w23, w2
	bl	_mcount
	ldr	x22, .LC870
	mov	x2, 64
	mov	w1, 0
	add	x0, x29, 152
	str	wzr, [x29, 84]
	ldr	x3, [x22, 96]
	blr	x3
	ldr	x4, [x22, 96]
	mov	x2, 120
	mov	w1, 0
	add	x0, x29, 216
	blr	x4
	ldr	x4, [x22, 96]
	mov	x2, 16
	mov	w1, 0
	add	x0, x29, 104
	blr	x4
	ldr	x4, [x22, 96]
	mov	x2, 12
	mov	w1, 0
	add	x0, x29, 88
	blr	x4
	cbz	x19, .L1814
	ldr	w0, [x19, 36]
	tbnz	w0, #31, .L1719
	ldr	w0, [x19, 12]
	cmp	w0, 31
	ble	.L1719
	ldr	w0, [x19, 16]
	cmp	w0, 31
	ble	.L1719
	ldr	w1, [x19, 56]
	mov	w0, 262143
	cmp	w1, w0
	ble	.L1719
	ldr	w0, [x19, 44]
	cmp	w0, 1
	beq	.L1815
	cmp	w0, 2
	bne	.L1721
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L1719
	ldr	w0, [x19, 24]
	cmp	w0, wzr
	ble	.L1719
.L1809:
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L1719
	ldr	w0, [x19, 32]
	cmp	w0, wzr
	bgt	.L1721
.L1719:
	ldr	x1, .LC873
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1830:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 336
	ret
	.p2align 3
.L1721:
	ldr	w0, [x19, 192]
	cmp	w0, 1
	bls	.L1723
	str	wzr, [x19, 192]
.L1723:
	mov	w24, 17992
	mov	w0, 47544
	movk	w0, 0xf, lsl 16
	cmp	w20, 26
	movk	w24, 0xb5, lsl 16
	mov	w21, 1
	csel	w24, w24, w0, eq
	mov	w3, w23
	add	x2, x29, 88
	mov	x1, x19
	mov	w0, w20
	stp	w21, w21, [x19, 216]
	bl	VCTRL_GetChanMemSize
	cbnz	w0, .L1816
	ldr	x25, .LC876
	ldr	x0, [x25]
	cbz	x0, .L1817
	add	x0, x25, 8
	b	.L1728
	.p2align 3
.L1819:
	add	w21, w21, 1
	cmp	w21, 32
	beq	.L1818
.L1728:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbnz	x1, .L1819
.L1727:
	ldr	w0, [x19, 228]
	cmp	w0, 1
	beq	.L1773
.L1730:
	cmp	w21, 31
	bhi	.L1774
	ldr	x3, [x22, 96]
	add	x23, x19, 72
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	ldr	x0, [x23, 56]
	cbz	x0, .L1732
	ldr	w0, [x23, 64]
	cbnz	w0, .L1733
.L1732:
	mov	w1, 3
	mov	w0, 7
	str	w1, [x29, 148]
	bl	VFMW_GetString
	ldr	w2, [x29, 96]
	mov	w4, 1
	add	x3, x29, 120
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1820
	ldr	w0, [x29, 136]
	ldr	w2, [x29, 144]
	ldr	x1, [x29, 128]
	bl	MEM_AddMemRecord
	ldr	w0, [x29, 136]
	str	w0, [x29, 264]
	ldr	x0, [x29, 128]
	str	x0, [x29, 272]
	ldr	w0, [x29, 144]
	str	w0, [x29, 280]
	mov	w0, 1
	str	w0, [x29, 112]
.L1736:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	ldr	x0, [x23, 8]
	cbnz	x0, .L1821
.L1768:
	ldr	w0, [x19, 192]
	cmp	w0, 1
	beq	.L1739
	mov	w1, 3
	mov	w0, 8
	str	w1, [x29, 148]
	bl	VFMW_GetString
	ldr	w2, [x29, 88]
	mov	w4, 0
	add	x3, x29, 120
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1822
	ldr	w0, [x29, 136]
	ldr	w2, [x29, 144]
	ldr	x1, [x29, 128]
	bl	MEM_AddMemRecord
	ldr	w0, [x29, 136]
	str	w0, [x29, 216]
	ldr	x0, [x29, 128]
	str	x0, [x29, 224]
	ldr	w0, [x29, 144]
	str	w0, [x29, 232]
	mov	w0, 1
	str	w0, [x29, 104]
.L1743:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	ldr	x0, [x23, 32]
	cbz	x0, .L1770
	ldr	w0, [x23, 40]
	cbnz	w0, .L1747
.L1770:
	mov	w1, 3
	mov	w0, 9
	str	w1, [x29, 148]
	bl	VFMW_GetString
	ldr	w2, [x29, 92]
	mov	w4, 0
	add	x3, x29, 120
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1823
	ldr	x1, [x29, 128]
	ldr	w0, [x29, 136]
	ldr	w2, [x29, 144]
	bl	MEM_AddMemRecord
	ldr	w1, [x29, 136]
	ldr	x0, [x29, 128]
	str	w1, [x29, 240]
	ldr	w1, [x29, 144]
	str	x0, [x29, 248]
	mov	w0, 1
	str	w1, [x29, 256]
	str	w0, [x29, 108]
.L1752:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	ldr	w0, [x19, 168]
	cbz	w0, .L1757
	ldr	w1, [x19, 184]
	cbz	w1, .L1757
	str	w1, [x29, 144]
	ldr	w1, [x19, 224]
	str	w0, [x29, 136]
	cmp	w1, 1
	beq	.L1824
	ldr	x1, [x22, 352]
	add	x0, x29, 120
	str	wzr, [x29, 148]
	blr	x1
	mov	x1, x0
	str	x0, [x29, 128]
.L1759:
	ldr	w2, [x29, 144]
	ldr	w0, [x29, 136]
	bl	MEM_AddMemRecord
	ldr	w1, [x29, 136]
	ldr	w2, [x29, 144]
	ldr	x0, [x29, 128]
	str	w1, [x29, 312]
	str	x0, [x29, 320]
	str	w2, [x29, 328]
.L1757:
	ldr	x1, [x22, 24]
	mov	w0, 0
	sxtw	x23, w24
	sxtw	x26, w21
	blr	x1
	ldr	x3, [x22, 96]
	sub	x2, x23, #204800
	ldr	x0, [x29, 272]
	sub	x2, x2, #1544
	mov	w1, 0
	str	x0, [x25, w21, sxtw 3]
	blr	x3
	ldr	x0, [x25, w21, sxtw 3]
	mov	x1, x19
	ldr	x3, [x22, 104]
	mov	x2, 232
	add	x0, x0, 1360
	blr	x3
	ldr	x0, [x25, w21, sxtw 3]
	mov	w1, 22
	ldr	x3, .LC893
	str	w20, [x0, 36]
	str	w24, [x0, 1268]
	ldr	x0, [x25, w21, sxtw 3]
	str	w21, [x0]
	str	w20, [x0, 668]
	str	wzr, [x0, 1296]
	ldr	x0, [x25, w21, sxtw 3]
	ldr	w2, [x19]
	str	w2, [x0, 32]
	ldr	x0, [x25, w21, sxtw 3]
	add	x2, x0, 507904
	str	w1, [x0, 632]
	str	w1, [x2, 1744]
	str	wzr, [x0, 28]
	ldr	x0, [x25, w21, sxtw 3]
	ldr	w2, [x19, 224]
	add	x1, x0, 507904
	str	w2, [x1, 1720]
	lsl	x1, x26, 4
	mov	w2, 30
	str	w2, [x0, 1640]
	add	x2, x0, 1648
	str	x2, [x3, x1]
	add	x1, x0, 475136
	add	x1, x1, 2248
	ldr	w0, [x19, 216]
	str	w0, [x2, 76]
	ldr	w0, [x19, 220]
	str	w0, [x2, 80]
	mov	w0, w21
	bl	FSP_EnableInstance
	cbnz	w0, .L1825
	mov	w0, w21
	mov	w20, 0
	mov	w24, 255
	bl	VCTRL_ResetChan
	ldr	x0, [x25, w21, sxtw 3]
	ldp	w3, w2, [x29, 104]
	add	x1, x0, 503808
	ldr	w4, [x29, 112]
	str	w2, [x0, 404]
	add	x2, x1, 1536
	str	w3, [x0, 400]
	str	w4, [x0, 408]
	add	x0, x0, 507904
	stp	wzr, wzr, [x2, 92]
	stp	wzr, wzr, [x2, 100]
	str	wzr, [x1, 1644]
	str	wzr, [x1, 1648]
	ldr	w1, [x19, 192]
	str	w1, [x0, 1684]
	str	wzr, [x0, 1676]
	ldr	w1, [x19, 228]
	str	w1, [x0, 1736]
	str	wzr, [x0, 1740]
	.p2align 2
.L1762:
	uxtw	x1, w20
	ldr	x0, [x25, x26, lsl 3]
	lsl	x19, x1, 6
	ldr	x4, [x22, 96]
	add	x19, x19, x1, lsl 3
	mov	x2, 72
	add	x3, x19, 503808
	mov	w1, 0
	add	x0, x0, x3
	add	w20, w20, 1
	add	x0, x0, 1656
	blr	x4
	ldr	x0, [x25, x26, lsl 3]
	cmp	w20, 32
	add	x1, x0, x19
	add	x1, x1, 503808
	str	w24, [x1, 1656]
	str	w24, [x1, 1660]
	str	w24, [x1, 1664]
	bne	.L1762
	ldr	x3, [x22, 96]
	add	x0, x0, 503808
	mov	x2, 1248
	mov	w1, 0
	add	x0, x0, 3960
	blr	x3
	ldr	x0, [x25, x26, lsl 3]
	mov	x2, 24
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 507904
	add	x0, x0, 1112
	blr	x3
	ldr	x0, [x25, x26, lsl 3]
	ldr	w6, [x29, 264]
	ldr	x3, .LC896
	str	w6, [x0, 352]
	ldr	x6, [x29, 272]
	add	x3, x3, 1672
	ldr	x5, [x29, 224]
	str	x6, [x0, 344]
	ldr	w6, [x29, 280]
	str	x5, [x0, 280]
	str	w6, [x0, 360]
	ldr	x5, [x29, 248]
	ldr	w6, [x29, 312]
	str	x5, [x0, 312]
	add	x5, x0, 475136
	str	w6, [x0, 384]
	ldr	x6, [x29, 320]
	ldr	w1, [x29, 216]
	ldr	w2, [x29, 232]
	str	x6, [x0, 376]
	str	wzr, [x3, x26, lsl 2]
	ldr	w4, [x29, 240]
	ldr	w3, [x29, 256]
	ldr	w6, [x29, 328]
	str	w1, [x0, 288]
	str	w2, [x0, 296]
	str	w4, [x0, 320]
	str	w3, [x0, 328]
	str	w1, [x0, 428]
	str	w2, [x0, 432]
	str	w6, [x0, 392]
	str	wzr, [x5, 2280]
	ldr	w5, [x0, 1552]
	cmp	w5, 1
	beq	.L1763
	sub	w2, w2, #307200
	str	w1, [x0, 416]
	sub	w2, w2, #2576
	str	w4, [x0, 424]
	add	w1, w2, w1
	str	w2, [x0, 420]
	add	w4, w1, 12288
	add	w2, w1, 45056
	add	w1, w1, 15
	add	w4, w4, 2575
	and	w1, w1, -16
	add	w2, w2, 2575
	mov	w6, 14848
	mov	w5, 32768
	and	w4, w4, -16
	and	w2, w2, -16
	str	w1, [x0, 440]
	mov	w1, 262144
	str	w3, [x0, 436]
	str	w6, [x0, 444]
	str	w5, [x0, 452]
	str	w4, [x0, 448]
	str	w2, [x0, 456]
	str	w1, [x0, 460]
.L1764:
	ldr	x1, [x25, w21, sxtw 3]
	mov	w0, w21
	str	w21, [x1]
	ldr	x1, [x25, w21, sxtw 3]
	add	x2, x1, 458752
	str	w21, [x1, 264]
	str	w21, [x1, 268]
	str	w21, [x2, 1888]
	bl	SM_ClearInst
	ldr	x2, [x25, w21, sxtw 3]
	sub	x1, x23, #200704
	sub	x1, x1, #3592
	mov	w0, w21
	ldr	x2, [x2, 344]
	add	x1, x2, x1
	bl	OpenUsdPool_WithMem
	ldr	x1, [x25, w21, sxtw 3]
	mov	w2, 1
	mov	w0, w21
	str	w2, [x1, 4]
	bl	VDMDRV_ClearChanIsDec
	bl	VDMDRV_ParamInit
	ldr	x19, [x25, w21, sxtw 3]
	ldr	x0, [x22]
	add	x19, x19, 507904
	blr	x0
	ldr	x1, [x22, 32]
	str	w0, [x19, 1692]
	mov	w0, 0
	blr	x1
	mov	w0, w21
.L1803:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 336
	ret
	.p2align 3
.L1821:
	ldr	w0, [x23, 16]
	cbz	w0, .L1768
	ldr	x3, [x22, 104]
	mov	x2, 24
	mov	x1, x23
	add	x0, x29, 216
	blr	x3
	ldr	w0, [x19, 192]
	ldr	w2, [x29, 232]
	cmp	w0, 1
	beq	.L1745
	ldr	w4, [x29, 88]
	cmp	w2, w4
	blt	.L1826
.L1745:
	ldr	w0, [x29, 216]
	ldr	x1, [x29, 224]
	bl	MEM_AddMemRecord
	b	.L1743
	.p2align 3
.L1739:
	str	wzr, [x29, 104]
	str	wzr, [x29, 216]
	str	xzr, [x29, 224]
	str	wzr, [x29, 232]
	b	.L1743
	.p2align 3
.L1818:
	ldr	w0, [x19, 228]
	cmp	w0, 1
	bne	.L1774
.L1773:
	add	x1, x29, 84
	mov	w0, 1
	bl	PDT_GetAttribute
	ldr	w0, [x29, 84]
	cmp	w0, 1
	ccmp	w21, 15, 4, ne
	ble	.L1730
	ldr	x1, .LC878
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
	.p2align 3
.L1815:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	bgt	.L1809
	b	.L1719
	.p2align 3
.L1763:
	sub	w1, w3, #307200
	mov	w3, 14848
	sub	w1, w1, #2576
	str	w4, [x0, 424]
	add	w2, w1, w4
	str	w1, [x0, 436]
	str	w3, [x0, 444]
	add	w1, w2, 45056
	add	w3, w2, 12288
	add	w4, w2, 15
	and	w2, w4, -16
	add	w3, w3, 2575
	add	w1, w1, 2575
	mov	w5, 32768
	and	w3, w3, -16
	and	w1, w1, -16
	str	w2, [x0, 440]
	mov	w2, 262144
	str	wzr, [x0, 416]
	str	wzr, [x0, 420]
	str	w5, [x0, 452]
	str	w3, [x0, 448]
	str	w1, [x0, 456]
	str	w2, [x0, 460]
	b	.L1764
.L1733:
	ldr	x3, [x22, 104]
	mov	x2, 24
	add	x1, x19, 120
	add	x0, x29, 264
	blr	x3
	ldr	w0, [x29, 96]
	ldr	w2, [x29, 280]
	cmp	w2, w0
	blt	.L1827
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_AddMemRecord
	b	.L1736
.L1747:
	ldr	x3, [x22, 104]
	add	x1, x19, 96
	add	x0, x29, 240
	mov	x2, 24
	blr	x3
	ldr	x1, [x29, 248]
	cbz	x1, .L1753
	ldr	w0, [x29, 92]
	ldr	w2, [x29, 256]
	cmp	w2, w0
	blt	.L1753
	ldr	w0, [x29, 240]
	bl	MEM_AddMemRecord
	b	.L1752
.L1824:
	ldr	x1, [x22, 320]
	mov	w2, 3
	add	x0, x29, 120
	str	w2, [x29, 148]
	blr	x1
	mov	x1, x0
	str	x0, [x29, 128]
	b	.L1759
.L1823:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L1828
.L1749:
	ldr	w0, [x29, 104]
	cmp	w0, 1
	beq	.L1829
.L1750:
	ldr	x1, .LC890
	mov	w2, 1679
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1830
.L1822:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L1831
.L1741:
	ldr	x1, .LC886
	mov	w2, 1743
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1830
.L1817:
	mov	w21, 0
	b	.L1727
.L1774:
	ldr	x1, .LC880
	mov	w2, 32
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
.L1825:
	ldr	x1, .LC895
	mov	w2, w21
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, w21
	bl	FSP_DisableInstance
	mov	w0, w21
	bl	CloseUsdPool_WithMem
	ldr	x1, [x25, w21, sxtw 3]
	mov	w0, w21
	str	xzr, [x25, w21, sxtw 3]
	add	x3, x1, 507904
	add	x2, x1, 503808
	ldr	w6, [x1, 404]
	add	x2, x2, 1656
	ldr	w4, [x1, 400]
	ldr	w5, [x1, 408]
	stp	w4, w6, [x29, 196]
	ldr	w4, [x3, 1684]
	ldr	w19, [x3, 1720]
	add	x3, x1, 336
	str	w5, [x29, 204]
	add	x5, x1, 272
	str	w4, [x29, 192]
	add	x4, x1, 304
	add	x1, x1, 368
	str	x2, [x29, 176]
	str	x5, [x29, 152]
	str	x3, [x29, 168]
	str	x4, [x29, 160]
	str	x1, [x29, 184]
	bl	VDMDRV_ClearChanIsDec
	ldr	x1, [x22, 32]
	mov	w0, 0
	blr	x1
	add	x1, x29, 184
	mov	w0, w19
	bl	VCTRL_DelRecordEsBuf.isra.5
	add	x1, x29, 152
	mov	w0, w21
	bl	VCTRL_FreeChanResource
	mov	w0, -1
	b	.L1830
.L1820:
	ldr	x1, .LC882
	mov	w2, 1800
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1830
.L1753:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L1832
.L1755:
	ldr	w0, [x29, 104]
	cmp	w0, 1
	beq	.L1833
.L1756:
	ldr	x1, .LC892
	mov	w2, 1707
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1830
.L1816:
	ldr	x1, .LC875
	mov	w2, 1947
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1803
.L1829:
	ldr	w0, [x29, 216]
	ldr	x1, [x29, 224]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 216]
	ldr	w2, [x29, 232]
	ldr	x1, [x29, 224]
	bl	MEM_DelMemRecord
	b	.L1750
.L1831:
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 264]
	ldr	w2, [x29, 280]
	ldr	x1, [x29, 272]
	bl	MEM_DelMemRecord
	b	.L1741
.L1828:
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 264]
	ldr	w2, [x29, 280]
	ldr	x1, [x29, 272]
	bl	MEM_DelMemRecord
	b	.L1749
.L1827:
	ldr	x1, .LC884
	mov	w2, 1816
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1830
.L1826:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L1834
.L1746:
	ldr	x1, .LC888
	mov	w3, w2
	mov	w0, 1
	mov	w2, 1774
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1830
.L1833:
	ldr	w0, [x29, 216]
	ldr	x1, [x29, 224]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 216]
	ldr	w2, [x29, 232]
	ldr	x1, [x29, 224]
	bl	MEM_DelMemRecord
	b	.L1756
.L1814:
	ldr	x1, .LC872
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1830
.L1832:
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 264]
	ldr	w2, [x29, 280]
	ldr	x1, [x29, 272]
	bl	MEM_DelMemRecord
	b	.L1755
.L1834:
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_ReleaseMemBlock
	ldr	w2, [x29, 280]
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_DelMemRecord
	ldr	w4, [x29, 88]
	ldr	w2, [x29, 232]
	b	.L1746
	.size	VCTRL_CreateChan, .-VCTRL_CreateChan
	.align	3
.LC870:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC872:
	.xword	.LC871
	.align	3
.LC873:
	.xword	.LC534
	.align	3
.LC875:
	.xword	.LC874
	.align	3
.LC876:
	.xword	.LANCHOR1
	.align	3
.LC878:
	.xword	.LC877
	.align	3
.LC880:
	.xword	.LC879
	.align	3
.LC882:
	.xword	.LC881
	.align	3
.LC884:
	.xword	.LC883
	.align	3
.LC886:
	.xword	.LC885
	.align	3
.LC888:
	.xword	.LC887
	.align	3
.LC890:
	.xword	.LC889
	.align	3
.LC892:
	.xword	.LC891
	.align	3
.LC893:
	.xword	s_SmIIS
	.align	3
.LC895:
	.xword	.LC894
	.align	3
.LC896:
	.xword	.LANCHOR5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_ConfigChan
	.type	VCTRL_ConfigChan, %function
VCTRL_ConfigChan:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w19, w0
	mov	x24, x1
	mov	x0, x30
	bl	_mcount
	cbz	x24, .L1890
	cmp	w19, 31
	bhi	.L1891
	ldr	x21, .LC903
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1892
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L1893
	mov	x1, x24
	mov	w0, w19
	bl	VCTRL_CheckChanWH
	mov	w20, w0
	cbnz	w0, .L1894
	ldr	x22, .LC908
	add	x23, x22, 1800
	mov	x1, x23
	bl	PDT_GetAttribute
	ldr	w0, [x22, 1820]
	ldr	w2, [x24, 8]
	cmp	w0, 21
	bhi	.L1843
	cmp	w0, w2
	beq	.L1844
	add	x0, x22, 1824
	add	x3, x22, 1948
	.p2align 2
.L1846:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 21
	bhi	.L1843
	cmp	w1, w2
	beq	.L1844
	cmp	x3, x0
	bne	.L1846
.L1844:
	cmp	w2, 8
	str	wzr, [x29, 96]
	beq	.L1895
.L1847:
	cmp	w2, 9
	beq	.L1896
	cmp	w2, 5
	str	wzr, [x29, 96]
	beq	.L1897
.L1873:
	mov	x1, x24
	mov	w0, w19
	bl	VCTRL_CmpConfigParameter
	cbz	w0, .L1898
	ldr	x23, .LC913
	mov	x2, 148
	ldr	x0, [x21, w19, sxtw 3]
	mov	x1, x24
	ldr	x3, [x23, 104]
	add	x0, x0, 44
	blr	x3
	ldr	x0, [x21, w19, sxtw 3]
	mov	x2, 80
	ldr	w1, [x24, 24]
	str	w1, [x0, 20]
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x24, 8]
	ldr	x3, [x23, 96]
	str	w1, [x0, 632]
	ldr	w1, [x24, 100]
	str	w1, [x0, 1560]
	mov	w1, 0
	add	x0, x29, 96
	blr	x3
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w0, [x0, 424]
	str	w0, [x29, 112]
	bl	MEM_Phy2Vir
	str	x0, [x29, 96]
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w0, [x24, 84]
	ldr	w3, [x24, 24]
	ldr	w2, [x1, 436]
	cmp	w0, 1
	str	w2, [x29, 116]
	add	x1, x1, 507904
	ldr	w2, [x24, 8]
	str	w2, [x29, 108]
	mov	w2, 49152
	movk	w2, 0xf8c3, lsl 16
	strb	w3, [x29, 104]
	str	w2, [x29, 120]
	beq	.L1899
	str	wzr, [x1, 1732]
.L1855:
	ldr	w0, [x24, 88]
	cbz	w0, .L1856
	mov	w0, 1
	str	w0, [x29, 152]
.L1856:
	ldr	w1, [x24, 80]
	ldr	w0, [x24, 8]
	str	wzr, [x29, 136]
	str	w1, [x29, 144]
	cbnz	w0, .L1900
.L1889:
	ldr	w0, [x24, 52]
.L1858:
	str	w0, [x29, 140]
	add	x3, x21, 256
	mov	w1, 0
	mov	x0, x21
	.p2align 2
.L1860:
	ldr	x2, [x0], 8
	cmp	x2, xzr
	csinc	w1, w1, w1, eq
	cmp	x3, x0
	bne	.L1860
	cmp	w1, 1
	ldr	x25, .LC914
	ble	.L1901
.L1861:
	str	wzr, [x29, 140]
.L1862:
	ldr	x0, [x21, w19, sxtw 3]
	ldrsb	w0, [x0, 44]
	cmp	w0, 1
	beq	.L1902
.L1863:
	ldr	x3, [x23, 104]
	add	x26, x24, 12
	mov	x2, 12
	mov	x1, x26
	add	x0, x29, 124
	blr	x3
	add	x1, x29, 96
	mov	w0, w19
	bl	SM_Config
	ldr	x3, [x23, 96]
	mov	x2, 1
	mov	w1, 0
	add	x0, x29, 88
	blr	x3
	ldr	w0, [x24, 84]
	cmp	w0, 1
	beq	.L1903
.L1864:
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x25, 72]
	ldr	w2, [x0, 352]
	cmp	w1, 7
	str	w2, [x0, 1272]
	ldr	w2, [x0, 360]
	str	w2, [x0, 1276]
	ldr	w2, [x0, 416]
	str	w2, [x0, 656]
	ldr	w2, [x0, 420]
	str	w2, [x0, 660]
	ldr	w2, [x0, 440]
	str	w2, [x0, 672]
	ldr	w2, [x0, 444]
	str	w2, [x0, 676]
	ldr	w2, [x0, 448]
	str	w2, [x0, 680]
	ldr	w2, [x0, 452]
	str	w2, [x0, 684]
	ldr	w2, [x0, 456]
	str	w2, [x0, 688]
	ldr	w2, [x0, 460]
	str	w2, [x0, 692]
	ldr	w2, [x24, 28]
	str	w2, [x0, 644]
	ldr	w2, [x24, 28]
	str	w2, [x0, 640]
	ldr	w2, [x24, 36]
	str	w2, [x0, 648]
	beq	.L1904
.L1865:
	str	w1, [x0, 664]
	mov	w25, 1
	ldr	w1, [x24, 44]
	str	w1, [x0, 652]
	ldr	w1, [x24, 132]
	str	w1, [x0, 1324]
	ldr	w1, [x24, 140]
	str	w1, [x0, 1628]
	str	w25, [x0, 1328]
	str	w25, [x0, 1332]
	ldr	w1, [x24, 72]
	cmp	w1, w25
	cset	w1, eq
	str	w1, [x0, 1308]
	ldr	w1, [x24, 76]
	str	w1, [x0, 1312]
	ldr	w1, [x24, 48]
	str	w1, [x0, 1316]
	ldr	w1, [x29, 140]
	str	w1, [x0, 1320]
	str	wzr, [x0, 1600]
	str	wzr, [x0, 1620]
	str	wzr, [x0, 1636]
	add	x0, x0, 507904
	ldrsb	w1, [x24, 1]
	strb	w1, [x0, 1680]
	mov	x1, x24
	mov	w0, w19
	bl	VCTRL_ConfigChanCompress
	ldr	x0, [x21, w19, sxtw 3]
	mov	x2, 12
	ldr	x3, [x23, 104]
	mov	x1, x26
	add	x0, x0, 1244
	blr	x3
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 507904
	ldr	w2, [x0, 632]
	ldr	w0, [x1, 1744]
	cmp	w0, w2
	beq	.L1866
	mov	w0, w19
	bl	VCTRL_ResetChan
	ldr	w1, [x24, 8]
	ldr	x0, [x21, w19, sxtw 3]
	cmp	w1, 20
	beq	.L1867
	ldr	w2, [x0, 632]
	add	x1, x0, 507904
.L1866:
	ldr	x4, .LC917
	mov	x0, 0
	str	w2, [x1, 1744]
	b	.L1871
	.p2align 3
.L1906:
	ldr	w3, [x1, 20]
	str	w3, [x2, x0, lsl 2]
	ldr	w1, [x1, 20]
	str	w1, [x4, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1905
.L1871:
	ldr	x1, [x21, x0, lsl 3]
	add	x2, x22, 1952
	cbnz	x1, .L1906
	add	x1, x22, 1952
	str	wzr, [x4, x0, lsl 2]
	str	wzr, [x1, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L1871
.L1905:
	add	x0, x22, 1952
	bl	VDMDRV_SetPriority
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1898:
	ldr	x1, .LC912
	mov	w20, 0
	bl	dprint_vfmw
.L1887:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1843:
	ldr	x1, .LC910
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1900:
	cmp	w0, 16
	mov	w0, 0
	beq	.L1889
	b	.L1858
	.p2align 3
.L1896:
	add	x0, x29, 96
	bl	REAL9DEC_Support
	ldr	w0, [x29, 96]
	cbz	w0, .L1848
	ldr	w2, [x24, 8]
	str	wzr, [x29, 96]
	cmp	w2, 5
	bne	.L1873
	b	.L1897
.L1901:
	ldr	w0, [x25, 88]
	cbnz	w0, .L1862
	b	.L1861
.L1895:
	add	x0, x29, 96
	bl	REAL8DEC_Support
	ldr	w0, [x29, 96]
	cbz	w0, .L1848
	ldr	w2, [x24, 8]
	b	.L1847
.L1897:
	add	x0, x29, 96
	bl	DIVX3DEC_Support
	ldr	w0, [x29, 96]
	cbnz	w0, .L1873
.L1848:
	mov	w20, -1
	b	.L1887
.L1893:
	ldr	x2, .LC900
	mov	w3, 2616
	ldr	x4, .LC905
	mov	w0, 0
	ldr	x1, .LC901
	add	x2, x2, 1400
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1887
.L1902:
	str	wzr, [x29, 140]
	b	.L1863
.L1904:
	ldr	w1, [x24, 40]
	b	.L1865
.L1899:
	ldr	w2, [x24, 92]
	str	w2, [x29, 156]
	ldr	w2, [x24, 96]
	str	w0, [x29, 148]
	str	w2, [x29, 160]
	ldr	w0, [x24, 136]
	str	w0, [x1, 1732]
	b	.L1855
.L1903:
	strb	w0, [x29, 88]
	add	x1, x29, 88
	mov	w0, w19
	bl	FSP_ConfigAttribute
	b	.L1864
.L1894:
	ldr	x1, .LC907
	mov	w0, 0
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1887
.L1867:
	ldr	w3, [x0, 428]
	ldr	w4, [x0, 432]
	ldr	w1, [x0, 1372]
	ldr	w2, [x0, 1376]
	mov	w0, w19
	bl	VCTRL_PartitionMemForStdUser
	cbnz	w0, .L1868
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 507904
	ldr	w2, [x0, 632]
	b	.L1866
.L1891:
	ldr	x2, .LC900
	mov	w3, 2614
	ldr	x4, .LC902
	mov	w0, 0
	ldr	x1, .LC901
	add	x2, x2, 1400
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1887
.L1892:
	ldr	x2, .LC900
	mov	w3, 2615
	ldr	x4, .LC904
	mov	w20, -1
	ldr	x1, .LC901
	add	x2, x2, 1400
	bl	dprint_vfmw
	b	.L1887
.L1890:
	ldr	x2, .LC900
	mov	w3, 2613
	ldr	x4, .LC899
	mov	w0, 0
	ldr	x1, .LC901
	add	x2, x2, 1400
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1887
.L1868:
	ldr	x1, .LC916
	mov	w0, w25
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1887
	.size	VCTRL_ConfigChan, .-VCTRL_ConfigChan
	.align	3
.LC899:
	.xword	.LC898
	.align	3
.LC900:
	.xword	.LANCHOR4
	.align	3
.LC901:
	.xword	.LC6
	.align	3
.LC902:
	.xword	.LC376
	.align	3
.LC903:
	.xword	.LANCHOR1
	.align	3
.LC904:
	.xword	.LC381
	.align	3
.LC905:
	.xword	.LC250
	.align	3
.LC907:
	.xword	.LC906
	.align	3
.LC908:
	.xword	.LANCHOR5
	.align	3
.LC910:
	.xword	.LC909
	.align	3
.LC912:
	.xword	.LC911
	.align	3
.LC913:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC914:
	.xword	.LANCHOR2
	.align	3
.LC916:
	.xword	.LC915
	.align	3
.LC917:
	.xword	g_ChanCtx
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetUvmosEnable, %function
VfmwProc_SetUvmosEnable:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC923
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC924
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbz	w0, .L1910
	ldr	x1, .LC926
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L1910:
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 172]
	bl	VCTRL_ConfigChan
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetUvmosEnable, .-VfmwProc_SetUvmosEnable
	.align	3
.LC923:
	.xword	.LC922
	.align	3
.LC924:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC926:
	.xword	.LC925
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetDropStreamThread, %function
VfmwProc_SetDropStreamThread:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC928
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC929
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1911
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 72]
	bl	VCTRL_ConfigChan
.L1911:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetDropStreamThread, .-VfmwProc_SetDropStreamThread
	.align	3
.LC928:
	.xword	.LC927
	.align	3
.LC929:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetDecMode, %function
VfmwProc_SetDecMode:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC931
	lsr	w20, w3, 24
	and	w19, w3, 7
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC932
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbz	w0, .L1916
	ldr	x1, .LC934
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L1916:
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 76]
	bl	VCTRL_ConfigChan
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetDecMode, .-VfmwProc_SetDecMode
	.align	3
.LC931:
	.xword	.LC930
	.align	3
.LC932:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC934:
	.xword	.LC933
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetDecOrderOutput, %function
VfmwProc_SetDecOrderOutput:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC936
	lsr	w20, w3, 24
	and	w19, w3, 3
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC937
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1917
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 80]
	bl	VCTRL_ConfigChan
.L1917:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetDecOrderOutput, .-VfmwProc_SetDecOrderOutput
	.align	3
.LC936:
	.xword	.LC935
	.align	3
.LC937:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_SetErrorThread, %function
VfmwProc_SetErrorThread:
	stp	x29, x30, [sp, -192]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w3, [x19]
	mov	w0, 32
	ldr	x1, .LC939
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC940
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1919
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 68]
	bl	VCTRL_ConfigChan
.L1919:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetErrorThread, .-VfmwProc_SetErrorThread
	.align	3
.LC939:
	.xword	.LC938
	.align	3
.LC940:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestResetChan, %function
VfmwProc_TestResetChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	mov	w0, w19
	bl	VCTRL_ResetChan
	mov	w3, w0
	ldr	x1, .LC942
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestResetChan, .-VfmwProc_TestResetChan
	.align	3
.LC942:
	.xword	.LC941
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_DestroyChan
	.type	VCTRL_DestroyChan, %function
VCTRL_DestroyChan:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC943
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	cmp	w19, 31
	bhi	.L1933
	ldr	x21, .LC948
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1934
	ldr	w22, [x0, 4]
	cmp	w22, 1
	bne	.L1935
	str	wzr, [x0, 8]
	mov	w0, 0
	ldr	x1, [x20, 32]
	blr	x1
	mov	w0, w19
	bl	SCDDRV_IsChanDec
	cbnz	w0, .L1936
.L1927:
	ldr	x1, [x20, 24]
	mov	w0, 0
	sxtw	x22, w19
	blr	x1
	ldr	x2, .LC953
	mov	w0, 4
	ldr	x1, [x20, 24]
	str	wzr, [x2, w19, sxtw 2]
	blr	x1
	mov	w0, w19
	bl	VCTRL_StopChan
	ldr	x1, [x20, 32]
	cbnz	w0, .L1937
	mov	w0, 4
	lsl	x22, x22, 4
	blr	x1
	mov	w0, w19
	bl	VCTRL_ResetChan
	bl	VDMDRV_ParamInit
	ldr	x1, .LC954
	mov	w0, 4
	ldr	x2, [x20, 24]
	add	x1, x1, 264
	str	wzr, [x1, w19, sxtw 2]
	blr	x2
	mov	w0, w19
	bl	FSP_DisableInstance
	mov	w0, w19
	bl	CloseUsdPool_WithMem
	ldr	x1, [x21, w19, sxtw 3]
	mov	w0, w19
	ldr	x4, .LC955
	add	x3, x1, 507904
	add	x2, x1, 503808
	ldr	w5, [x1, 408]
	add	x2, x2, 1656
	str	w5, [x29, 116]
	ldr	w5, [x1, 400]
	str	w5, [x29, 108]
	ldr	w5, [x1, 404]
	ldr	w23, [x3, 1720]
	str	w5, [x29, 112]
	ldr	w5, [x3, 1684]
	add	x3, x1, 272
	str	xzr, [x4, x22]
	str	x2, [x29, 88]
	add	x2, x1, 368
	str	x3, [x29, 64]
	add	x3, x1, 304
	add	x1, x1, 336
	str	w5, [x29, 104]
	stp	x3, x1, [x29, 72]
	str	x2, [x29, 96]
	str	xzr, [x21, w19, sxtw 3]
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w19
	add	x21, x21, 608
	bl	SCDDRV_ResetSCD
	mov	w0, w19
	bl	VDMDRV_ResetVDH
	str	wzr, [x21, x22]
	add	x1, x21, x22
	ldr	x3, [x20, 32]
	mov	w2, -1
	mov	w0, 4
	stp	wzr, w2, [x1, 4]
	str	w2, [x1, 12]
	blr	x3
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	ldr	x2, [x20, 48]
	mov	w1, w19
	mov	w0, 1
	blr	x2
	add	x1, x29, 96
	mov	w0, w23
	bl	VCTRL_DelRecordEsBuf.isra.5
	add	x1, x29, 64
	mov	w0, w19
	bl	VCTRL_FreeChanResource
	ldr	x2, [x20, 56]
	mov	w0, 1
	mov	w1, w19
	blr	x2
	mov	w0, 0
.L1924:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1936:
	mov	w0, w19
	ldr	x23, [x20, 264]
	bl	SCDDRV_IsChanDec
	cmp	w0, wzr
	mov	w2, 500
	cset	w1, eq
	mov	w0, w22
	blr	x23
	b	.L1927
	.p2align 3
.L1935:
	ldr	x2, .LC945
	mov	w3, 2222
	ldr	x4, .LC952
	mov	w0, 0
	ldr	x1, .LC947
	add	x2, x2, 1424
.L1932:
	bl	dprint_vfmw
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1937:
	mov	w0, 4
	blr	x1
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, -1
	b	.L1924
	.p2align 3
.L1933:
	ldr	x2, .LC945
	mov	w3, 2208
	ldr	x4, .LC944
	mov	w0, 0
	ldr	x1, .LC947
	add	x2, x2, 1424
	b	.L1932
.L1934:
	ldr	x2, .LC945
	mov	w3, 2215
	ldr	x4, .LC950
	ldr	x1, .LC947
	add	x2, x2, 1424
	b	.L1932
	.size	VCTRL_DestroyChan, .-VCTRL_DestroyChan
	.align	3
.LC943:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC944:
	.xword	.LC193
	.align	3
.LC945:
	.xword	.LANCHOR4
	.align	3
.LC947:
	.xword	.LC946
	.align	3
.LC948:
	.xword	.LANCHOR1
	.align	3
.LC950:
	.xword	.LC949
	.align	3
.LC952:
	.xword	.LC951
	.align	3
.LC953:
	.xword	g_LowDelaySeqIndex
	.align	3
.LC954:
	.xword	.LANCHOR5
	.align	3
.LC955:
	.xword	s_SmIIS
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_CloseVfmw
	.type	VCTRL_CloseVfmw, %function
VCTRL_CloseVfmw:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC958
	ldr	w0, [x20, 256]
	cmp	w0, 1
	bne	.L1945
	mov	x19, 0
	.p2align 2
.L1941:
	ldr	x1, [x20, x19, lsl 3]
	mov	w0, w19
	add	x19, x19, 1
	cbz	x1, .L1940
	bl	VCTRL_DestroyChan
.L1940:
	cmp	x19, 32
	bne	.L1941
	bl	FSP_Exit
	ldr	x21, .LC959
	ldr	w1, [x20, 260]
	mov	w2, 3
	str	w2, [x20, 264]
	cbz	w1, .L1943
	ldr	x1, [x21, 240]
	mov	w0, 10
	mov	w19, 49
	blr	x1
	b	.L1944
	.p2align 3
.L1955:
	ldr	x1, [x21, 240]
	blr	x1
	subs	w19, w19, #1
	beq	.L1943
.L1944:
	ldr	w1, [x20, 260]
	mov	w0, 10
	cbnz	w1, .L1955
.L1943:
	ldr	x0, .LC960
	mov	x2, 128
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x0, x0, 264
	blr	x3
	add	x0, x20, 288
	bl	CloseDrivers
	str	wzr, [x20, 256]
	mov	w0, 0
.L1954:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1945:
	mov	w0, -1
	b	.L1954
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	3
.LC958:
	.xword	.LANCHOR1
	.align	3
.LC959:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC960:
	.xword	.LANCHOR5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestRestartChan, %function
VfmwProc_TestRestartChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	mov	w0, w19
	bl	VCTRL_StopChan
	mov	w3, w0
	ldr	x1, .LC963
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, w19
	bl	VCTRL_ResetChan
	mov	w3, w0
	ldr	x1, .LC964
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, w19
	bl	VCTRL_StartChan
	mov	w3, w0
	ldr	x1, .LC965
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestRestartChan, .-VfmwProc_TestRestartChan
	.align	3
.LC963:
	.xword	.LC962
	.align	3
.LC964:
	.xword	.LC941
	.align	3
.LC965:
	.xword	.LC831
	.global	_mcount
	.align	2
	.p2align 3,,7
	.type	VfmwProc_TestStopChan, %function
VfmwProc_TestStopChan:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w19, [x19]
	mov	w0, w19
	bl	VCTRL_StopChan
	mov	w3, w0
	ldr	x1, .LC966
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStopChan, .-VfmwProc_TestStopChan
	.align	3
.LC966:
	.xword	.LC962
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_InitDspCode
	.type	VCTRL_InitDspCode, %function
VCTRL_InitDspCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w21, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 6
	beq	.L1968
	mov	w19, 2
	cmp	w20, wzr
	csel	w19, w19, wzr, eq
.L1959:
	ldr	x0, .LC967
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1970
	mov	w1, w19
	mov	w0, 0
	bl	VDH_Require_DspCode
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1970:
	ldr	x20, .LC968
	ldr	x1, [x20, 8]
	cbz	x1, .L1971
	mov	w0, 0
	blr	x1
.L1962:
	ldr	x1, [x20, 40]
	cbz	x1, .L1972
	mov	w0, 0
	blr	x1
.L1964:
	ldr	x1, [x20, 24]
	cbz	x1, .L1973
	mov	w0, 0
	blr	x1
.L1966:
	mov	w1, w19
	mov	w0, 0
	bl	SCDDRV_LoadDspCode
	mov	w0, w21
	bl	VCTRL_CloseHardware
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1968:
	mov	w19, 1
	b	.L1959
	.p2align 3
.L1971:
	ldr	x1, .LC969
	mov	w2, 2876
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1962
	.p2align 3
.L1972:
	ldr	x1, .LC969
	mov	w2, 2877
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1964
	.p2align 3
.L1973:
	ldr	x1, .LC969
	mov	w2, 2878
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1966
	.size	VCTRL_InitDspCode, .-VCTRL_InitDspCode
	.align	3
.LC967:
	.xword	g_HalDisable
	.align	3
.LC968:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC969:
	.xword	.LC127
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_LoadDspCode
	.type	VCTRL_LoadDspCode, %function
VCTRL_LoadDspCode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC970
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w1, [x0, 632]
	cbnz	w1, .L1986
	ldr	w21, [x0, 1316]
	mov	w0, 0
	cmp	w21, wzr
	cset	w3, eq
	cmp	w1, 6
	cset	w2, ne
	tst	w3, w2
	beq	.L2005
.L1992:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1986:
	cmp	w1, 6
	mov	w3, 1
	cset	w2, ne
	mov	w21, 0
	tst	w3, w2
	mov	w0, 0
	bne	.L1992
.L2005:
	ldr	x20, .LC971
	add	x0, x20, 268
	add	x3, x20, 392
	ldr	w2, [x20, 264]
	cbz	w2, .L1977
	b	.L1976
	.p2align 3
.L2007:
	beq	.L2006
.L1977:
	ldr	w2, [x0]
	add	x0, x0, 4
	cmp	x3, x0
	cbz	w2, .L2007
.L1976:
	cmp	w2, 1
	beq	.L2008
	cmp	w1, 6
	mov	w0, 0
	beq	.L1992
	ldr	x1, .LC975
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1992
	.p2align 3
.L2006:
	mov	w0, w19
	bl	VCTRL_InitDspCode
	cmp	w21, 1
	beq	.L2009
	add	x20, x20, 264
	mov	w1, 2
	mov	w0, 0
	str	w1, [x20, w19, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2009:
	add	x20, x20, 264
	mov	w0, 0
	str	w21, [x20, w19, sxtw 2]
	b	.L1992
	.p2align 3
.L2008:
	cmp	w21, 1
	mov	w0, 0
	beq	.L1992
	ldr	x1, .LC973
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1992
	.size	VCTRL_LoadDspCode, .-VCTRL_LoadDspCode
	.align	3
.LC970:
	.xword	.LANCHOR1
	.align	3
.LC971:
	.xword	.LANCHOR5
	.align	3
.LC973:
	.xword	.LC972
	.align	3
.LC975:
	.xword	.LC974
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetChanFsPartitionState
	.type	VCTRL_SetChanFsPartitionState, %function
VCTRL_SetChanFsPartitionState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	ldr	x0, .LC978
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 475136
	str	w19, [x0, 2280]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetChanFsPartitionState, .-VCTRL_SetChanFsPartitionState
	.align	3
.LC978:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetCurChanFsSize
	.type	VCTRL_GetCurChanFsSize, %function
VCTRL_GetCurChanFsSize:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC979
	ldr	x0, [x0, w19, sxtw 3]
	ldr	x19, [sp, 16]
	add	x0, x0, 503808
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 1628]
	ret
	.size	VCTRL_GetCurChanFsSize, .-VCTRL_GetCurChanFsSize
	.align	3
.LC979:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRT_SetChanCtrlState
	.type	VCTRT_SetChanCtrlState, %function
VCTRT_SetChanCtrlState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	w19, w1
	bl	_mcount
	cmp	w19, 1
	beq	.L2014
	cbz	w19, .L2015
	cmp	w19, 2
	bne	.L2023
	ldr	x0, .LC980
	add	x0, x0, 1672
	ldr	w1, [x0, w20, sxtw 2]
	cmp	w1, 1
	beq	.L2019
.L2021:
	str	w19, [x0, w20, sxtw 2]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2023:
	mov	w0, 0
.L2013:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2015:
	ldr	x1, .LC980
	mov	w0, 0
	add	x1, x1, 1672
	str	wzr, [x1, w20, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L2014:
	ldr	x0, .LC980
	add	x0, x0, 1672
	ldr	w1, [x0, w20, sxtw 2]
	cbz	w1, .L2021
.L2019:
	mov	w0, -1
	b	.L2013
	.size	VCTRT_SetChanCtrlState, .-VCTRT_SetChanCtrlState
	.align	3
.LC980:
	.xword	.LANCHOR5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_AddFrameBufMemoryRecord
	.type	VCTRL_AddFrameBufMemoryRecord, %function
VCTRL_AddFrameBufMemoryRecord:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	cmp	w0, 255
	beq	.L2025
	ldr	w2, [x19, 12]
	ldr	w0, [x19, 32]
	ldr	x1, [x19, 24]
	bl	MEM_AddMemRecord
.L2025:
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L2026
	ldr	w2, [x19, 16]
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_AddMemRecord
.L2026:
	ldr	w0, [x19, 8]
	cmp	w0, 255
	beq	.L2024
	ldr	w2, [x19, 20]
	ldr	w0, [x19, 64]
	ldr	x1, [x19, 56]
	bl	MEM_AddMemRecord
.L2024:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_AddFrameBufMemoryRecord, .-VCTRL_AddFrameBufMemoryRecord
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_SetSingleFrameBufToChan
	.type	VCTRL_SetSingleFrameBufToChan, %function
VCTRL_SetSingleFrameBufToChan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x21, .LC982
	ldr	w4, [x20, 12]
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 507904
	add	x0, x0, 503808
	ldr	w5, [x1, 1104]
	cmp	w5, w4
	beq	.L2038
	ldr	w2, [x0, 1624]
	cbz	w2, .L2067
.L2038:
	ldr	w0, [x0, 4016]
	cbz	w0, .L2040
	ldr	w0, [x1, 1136]
	cbz	w0, .L2068
.L2040:
	ldr	x22, .LC988
	mov	w0, 8
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x4, [x21, w19, sxtw 3]
	add	x2, x4, 503808
	ldr	w0, [x2, 1656]
	cmp	w0, 255
	beq	.L2048
	add	x2, x2, 1728
	mov	x1, 1
	b	.L2042
	.p2align 3
.L2070:
	add	w1, w1, 1
	cmp	w1, 32
	beq	.L2069
.L2042:
	ldr	w3, [x2]
	add	x2, x2, 72
	cmp	w3, 255
	bne	.L2070
.L2041:
	lsl	x0, x1, 6
	ldr	x3, [x22, 104]
	add	x0, x0, x1, lsl 3
	mov	x2, 72
	add	x0, x0, 503808
	mov	x1, x20
	add	x0, x4, x0
	add	x0, x0, 1656
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	x0, x20
	add	x1, x1, 507904
	ldr	w2, [x1, 1136]
	add	w2, w2, 1
	str	w2, [x1, 1136]
	bl	VCTRL_AddFrameBufMemoryRecord
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 1140]
	cbnz	w0, .L2071
.L2046:
	mov	w19, 0
.L2045:
	ldr	x1, [x22, 32]
	mov	w0, 8
	blr	x1
	mov	w0, w19
.L2061:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2068:
	ldr	w5, [x20, 8]
	cmp	w5, 255
	bne	.L2040
	ldr	x2, .LC983
	mov	w4, 0
	ldr	x1, .LC987
	mov	w3, 8182
	add	x2, x2, 1448
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2061
	.p2align 3
.L2069:
	ldr	x2, .LC983
	ldr	x1, .LC992
.L2064:
	mov	w3, w19
	add	x2, x2, 1448
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
	b	.L2045
	.p2align 3
.L2071:
	mov	x1, x20
	mov	w0, w19
	bl	FSP_SetSingleFrameBuf
	cbz	w0, .L2046
	ldr	x2, .LC983
	ldr	x1, .LC990
	b	.L2064
.L2048:
	mov	x1, 0
	b	.L2041
.L2067:
	ldr	x2, .LC983
	mov	w3, 8172
	ldr	x1, .LC985
	mov	w0, 1
	add	x2, x2, 1448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2061
	.size	VCTRL_SetSingleFrameBufToChan, .-VCTRL_SetSingleFrameBufToChan
	.align	3
.LC982:
	.xword	.LANCHOR1
	.align	3
.LC983:
	.xword	.LANCHOR4
	.align	3
.LC985:
	.xword	.LC984
	.align	3
.LC987:
	.xword	.LC986
	.align	3
.LC988:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC990:
	.xword	.LC989
	.align	3
.LC992:
	.xword	.LC991
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_AllocMemToDecoder
	.type	VCTRL_AllocMemToDecoder, %function
VCTRL_AllocMemToDecoder:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	ldr	x21, .LC993
	add	x3, x21, 1672
	ldr	w0, [x3, w19, sxtw 2]
	cbz	w0, .L2082
	ldr	x2, .LC1000
	mov	w3, w19
	ldr	x1, .LC1002
	mov	w0, 0
	add	x2, x2, 1480
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mov	w0, -1
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2082:
	ldr	x23, .LC994
	mov	x2, 72
	mov	x1, x20
	add	x0, x29, x2
	mov	w5, 1
	str	w5, [x3, w19, sxtw 2]
	ldr	x4, [x23, 104]
	blr	x4
	add	x1, x29, 72
	mov	w0, w19
	bl	VCTRL_SetSingleFrameBufToChan
	ldr	x22, .LC995
	mov	w20, w0
	ldr	x0, [x22, w19, sxtw 3]
	add	x2, x0, 475136
	cbnz	w20, .L2083
.L2075:
	ldr	x1, .LC999
	mov	w3, 2
	mov	w0, 31
	str	w3, [x2, 2280]
	bl	dprint_vfmw
	ldr	x0, [x22, w19, sxtw 3]
	add	x0, x0, 507904
	ldr	w0, [x0, 1740]
	cmp	w0, 1
	beq	.L2084
.L2076:
	add	x21, x21, 1672
	mov	w0, w20
	str	wzr, [x21, w19, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2083:
	add	x1, x0, 503808
	add	x2, x0, 475136
	ldr	w0, [x1, 1628]
	cbz	w0, .L2075
	ldr	x1, .LC997
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x22, w19, sxtw 3]
	mov	w1, 3
	add	x2, x0, 475136
	str	w1, [x2, 2280]
	b	.L2075
	.p2align 3
.L2084:
	ldr	x1, [x23, 256]
	mov	w0, 0
	blr	x1
	ldr	x0, [x22, w19, sxtw 3]
	add	x0, x0, 507904
	str	wzr, [x0, 1740]
	b	.L2076
	.size	VCTRL_AllocMemToDecoder, .-VCTRL_AllocMemToDecoder
	.align	3
.LC993:
	.xword	.LANCHOR5
	.align	3
.LC994:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC995:
	.xword	.LANCHOR1
	.align	3
.LC997:
	.xword	.LC996
	.align	3
.LC999:
	.xword	.LC998
	.align	3
.LC1000:
	.xword	.LANCHOR4
	.align	3
.LC1002:
	.xword	.LC1001
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_GetFsSize
	.type	VCTRL_GetFsSize, %function
VCTRL_GetFsSize:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	w21, w2
	bl	_mcount
	ldr	x3, .LC1004
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, .LC1005
	ldr	x6, [x0, 104]
	cbz	x6, .L2086
	ldr	x4, .LC1006
	add	x5, x29, 56
	mov	w3, 0
	mov	w2, w21
	mov	w1, w20
	mov	w0, w19
	ldr	x4, [x4, w19, sxtw 3]
	add	x4, x4, 507904
	ldr	w4, [x4, 1744]
	blr	x6
.L2086:
	ldr	w0, [x29, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VCTRL_GetFsSize, .-VCTRL_GetFsSize
	.align	3
.LC1004:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1005:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC1006:
	.xword	.LANCHOR1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_EnableEsBuf
	.type	VCTRL_EnableEsBuf, %function
VCTRL_EnableEsBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC1007
	mov	w1, 1
	add	x0, x0, 2080
	str	w1, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_EnableEsBuf, .-VCTRL_EnableEsBuf
	.align	3
.LC1007:
	.xword	.LANCHOR5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_DisableEsBuf
	.type	VCTRL_DisableEsBuf, %function
VCTRL_DisableEsBuf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC1009
	add	x0, x0, 2080
	str	wzr, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_DisableEsBuf, .-VCTRL_DisableEsBuf
	.align	3
.LC1009:
	.xword	.LANCHOR5
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_IfEsBufEnable
	.type	VCTRL_IfEsBufEnable, %function
VCTRL_IfEsBufEnable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC1011
	add	x0, x0, 2080
	ldr	w0, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_IfEsBufEnable, .-VCTRL_IfEsBufEnable
	.align	3
.LC1011:
	.xword	.LANCHOR5
	.global	g_EsBufValidFlag
	.global	g_StopDec
	.global	g_SleepTime
	.global	s_VfmwSavePath
	.global	MemRecord_YUV
	.global	pPixelArray
	.global	pVl_2bit
	.global	pUl_2bit
	.global	pY_2bit
	.global	pVl
	.global	pUl
	.global	pY
	.global	g_eVdmVersion
	.global	g_VdmCharacter
	.global	g_StandardObedience
	.global	g_CurProcChan
	.global	g_SegBypassEnable
	.global	g_ResetCreateNewSave
	.global	g_SaveYUVBitWidth
	.global	save_yuv_with_crop
	.global	save_el_chan_num
	.global	vfmw_save_el_file
	.global	save_metadata_reorder_chan_num
	.global	vfmw_save_metadata_reorder_file
	.global	save_metadata_chan_num
	.global	vfmw_save_metadata_file
	.global	save_yuv_chan_num
	.global	vfmw_save_yuv_file
	.global	save_seg_chan_num
	.global	vfmw_save_seg_file
	.global	save_str_chan_num
	.global	vfmw_save_str_file
	.global	g_not_allow_H264FullPictureRepair_flag
	.global	g_not_direct_8x8_inference_flag
	.global	g_allow_B_before_P
	.global	extra_cmd
	.global	extra_disp
	.global	extra_ref
	.global	g_VfmwGlobalStat
	.global	g_VfmwChanStat
	.global	s_pstVfmwChan
	.global	AcceleratorCharacter
	.global	g_event_report
	.global	g_IsrFlag
	.global	g_VfmwCompressPara
	.global	g_DSPState
	.global	g_ClkSelect
	.global	mask_mmu_err_int
	.global	g_apple_airplay_mirrorinig_flag
	.global	g_IRQ_FLAG
	.global	g_SedOnlyEnable
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.52853, %object
	.size	__func__.52853, 18
__func__.52853:
	.string	"VCTRL_EventReport"
	.zero	6
	.type	__func__.54031, %object
	.size	__func__.54031, 24
__func__.54031:
	.string	"VCTRL_SetLastFrameState"
	.type	__func__.52792, %object
	.size	__func__.52792, 20
__func__.52792:
	.string	"VCTRL_RecordPosTime"
	.zero	4
	.type	__func__.52797, %object
	.size	__func__.52797, 17
__func__.52797:
	.string	"VCTRL_RecordData"
	.zero	7
	.type	__func__.52844, %object
	.size	__func__.52844, 23
__func__.52844:
	.string	"VCTRL_SetMoreGapEnable"
	.zero	1
	.type	__func__.52865, %object
	.size	__func__.52865, 18
__func__.52865:
	.string	"VCTRL_SetCallBack"
	.zero	6
	.type	__func__.52905, %object
	.size	__func__.52905, 25
__func__.52905:
	.string	"VCTRL_SetStreamInterface"
	.zero	7
	.type	__func__.52910, %object
	.size	__func__.52910, 29
__func__.52910:
	.string	"VCTRL_SetSendStreamAgainFlag"
	.zero	3
	.type	__func__.52914, %object
	.size	__func__.52914, 29
__func__.52914:
	.string	"VCTRL_GetSendStreamAgainFlag"
	.zero	3
	.type	__func__.52924, %object
	.size	__func__.52924, 20
__func__.52924:
	.string	"VCTRL_GetStreamSize"
	.zero	4
	.type	__func__.52931, %object
	.size	__func__.52931, 20
__func__.52931:
	.string	"VCTRL_CheckFreshRaw"
	.zero	4
	.type	__func__.52938, %object
	.size	__func__.52938, 20
__func__.52938:
	.string	"VCTRL_CheckFreshSeg"
	.zero	4
	.type	__func__.52943, %object
	.size	__func__.52943, 25
__func__.52943:
	.string	"VCTRL_SetDiscardPicParam"
	.zero	7
	.type	__FUNCTION__.52971, %object
	.size	__FUNCTION__.52971, 29
__FUNCTION__.52971:
	.string	"VCTRL_PartitionMemForStdUser"
	.zero	3
	.type	__func__.52986, %object
	.size	__func__.52986, 21
__func__.52986:
	.string	"DelAllFrameMemRecord"
	.zero	3
	.type	__func__.52996, %object
	.size	__func__.52996, 23
__func__.52996:
	.string	"VCTRL_FreeChanResource"
	.zero	1
	.type	__func__.53122, %object
	.size	__func__.53122, 17
__func__.53122:
	.string	"VCTRL_GetChanCfg"
	.zero	7
	.type	__func__.53183, %object
	.size	__func__.53183, 14
__func__.53183:
	.string	"VCTRL_SeekPts"
	.zero	2
	.type	__func__.53216, %object
	.size	__func__.53216, 20
__func__.53216:
	.string	"VCTRL_ReleaseStream"
	.zero	4
	.type	__func__.53236, %object
	.size	__func__.53236, 24
__func__.53236:
	.string	"VCTRL_ImageOutputEnable"
	.type	__func__.53275, %object
	.size	__func__.53275, 25
__func__.53275:
	.string	"VCTRL_TryToRelSpecialFrm"
	.zero	7
	.type	__func__.53299, %object
	.size	__func__.53299, 19
__func__.53299:
	.string	"VCTRL_GetChanImage"
	.zero	5
	.type	__FUNCTION__.53307, %object
	.size	__FUNCTION__.53307, 19
__FUNCTION__.53307:
	.string	"VCTRL_GetChanImage"
	.zero	5
	.type	__func__.53314, %object
	.size	__func__.53314, 23
__func__.53314:
	.string	"VCTRL_ReleaseChanImage"
	.zero	1
	.type	__FUNCTION__.53318, %object
	.size	__FUNCTION__.53318, 23
__FUNCTION__.53318:
	.string	"VCTRL_ReleaseChanImage"
	.zero	1
	.type	__func__.53326, %object
	.size	__func__.53326, 23
__func__.53326:
	.string	"VCTRL_GetHDRConfigInfo"
	.zero	1
	.type	__func__.53353, %object
	.size	__func__.53353, 18
__func__.53353:
	.string	"VCTRL_GetDecParam"
	.align	3
.LANCHOR4 = . + 0
	.type	__func__.53444, %object
	.size	__func__.53444, 20
__func__.53444:
	.string	"VCTRL_ClearDecparam"
	.zero	4
	.type	__func__.53474, %object
	.size	__func__.53474, 21
__func__.53474:
	.string	"VCTRL_VdmProcSedOnly"
	.zero	3
	.type	__func__.53484, %object
	.size	__func__.53484, 21
__func__.53484:
	.string	"VCTRL_GetImageBuffer"
	.zero	3
	.type	__func__.53508, %object
	.size	__func__.53508, 22
__func__.53508:
	.string	"VCTRL_ConfigFFFBSpeed"
	.zero	2
	.type	__func__.53513, %object
	.size	__func__.53513, 20
__func__.53513:
	.string	"VCTRL_ConfigPVRInfo"
	.zero	4
	.type	__func__.53517, %object
	.size	__func__.53517, 19
__func__.53517:
	.string	"VCTRL_IsChanActive"
	.zero	5
	.type	__func__.53523, %object
	.size	__func__.53523, 13
__func__.53523:
	.string	"USERDEC_Init"
	.zero	3
	.type	__func__.53542, %object
	.size	__func__.53542, 21
__func__.53542:
	.string	"VCTRL_GetUsrdecFrame"
	.zero	3
	.type	__func__.53552, %object
	.size	__func__.53552, 14
__func__.53552:
	.string	"InitSyntaxCtx"
	.zero	2
	.type	__func__.52874, %object
	.size	__func__.52874, 15
__func__.52874:
	.string	"VCTRL_OpenVfmw"
	.zero	1
	.type	__FUNCTION__.53761, %object
	.size	__FUNCTION__.53761, 18
__FUNCTION__.53761:
	.string	"GetExtraRefFrmNum"
	.zero	6
	.type	__FUNCTION__.53767, %object
	.size	__FUNCTION__.53767, 19
__FUNCTION__.53767:
	.string	"GetExtraDispFrmNum"
	.zero	5
	.type	__FUNCTION__.53773, %object
	.size	__FUNCTION__.53773, 16
__FUNCTION__.53773:
	.string	"GetExtraCtrlCmd"
	.type	__func__.53706, %object
	.size	__func__.53706, 14
__func__.53706:
	.string	"DecChanSyntax"
	.zero	2
	.type	__FUNCTION__.53707, %object
	.size	__FUNCTION__.53707, 14
__FUNCTION__.53707:
	.string	"DecChanSyntax"
	.zero	2
	.type	__func__.53225, %object
	.size	__func__.53225, 24
__func__.53225:
	.string	"VCTRL_FindOccupiedFrame"
	.type	__func__.53246, %object
	.size	__func__.53246, 26
__func__.53246:
	.string	"VCTRL_ReportOccupiedFrame"
	.zero	6
	.type	__func__.53738, %object
	.size	__func__.53738, 20
__func__.53738:
	.string	"VCTRL_GetChanImgNum"
	.zero	4
	.type	__func__.52954, %object
	.size	__func__.52954, 19
__func__.52954:
	.string	"VCTRL_GetChanState"
	.zero	5
	.type	__func__.53742, %object
	.size	__func__.53742, 19
__func__.53742:
	.string	"VCTRL_GetChanWidth"
	.zero	5
	.type	__func__.53746, %object
	.size	__func__.53746, 20
__func__.53746:
	.string	"VCTRL_GetChanHeight"
	.zero	4
	.type	__func__.53750, %object
	.size	__func__.53750, 22
__func__.53750:
	.string	"VCTRL_GetChanCapLevel"
	.zero	2
	.type	g_ProcCommandTable, %object
	.size	g_ProcCommandTable, 720
g_ProcCommandTable:
	.word	0
	.zero	4
	.xword	VfmwProc_SetPrintLevel
	.word	2
	.zero	4
	.xword	VfmwProc_SetErrorThread
	.word	3
	.zero	4
	.xword	VfmwProc_SetDefaultOutputOrder
	.word	4
	.zero	4
	.xword	VfmwProc_SetDecOrderOutput
	.word	5
	.zero	4
	.xword	VfmwProc_SetDecMode
	.word	7
	.zero	4
	.xword	VfmwProc_SetDropStreamThread
	.word	8
	.zero	4
	.xword	VfmwProc_SetVp9DecFrameNum
	.word	9
	.zero	4
	.xword	VfmwProc_SetUvmosEnable
	.word	11
	.zero	4
	.xword	VfmwProc_SetUSE_FF_APT_EN
	.word	12
	.zero	4
	.xword	VfmwProc_SetSaveFileAfterReset
	.word	13
	.zero	4
	.xword	VfmwProc_SetCurProcChan
	.word	256
	.zero	4
	.xword	VfmwProc_PrintTracer
	.word	257
	.zero	4
	.xword	VfmwProc_SetScdPrint
	.word	512
	.zero	4
	.xword	VfmwProc_Savestream
	.word	513
	.zero	4
	.xword	VfmwProc_SaveSeg
	.word	514
	.zero	4
	.xword	VfmwProc_SaveYUV
	.word	516
	.zero	4
	.xword	VfmwProc_Save1DYUV
	.word	528
	.zero	4
	.xword	VfmwProc_SaveMetadata
	.word	544
	.zero	4
	.xword	VfmwProc_SaveReorderMetadata
	.word	560
	.zero	4
	.xword	VfmwProc_SaveEL
	.word	768
	.zero	4
	.xword	VfmwProc_TestSuspend
	.word	769
	.zero	4
	.xword	VfmwProc_TestResume
	.word	896
	.zero	4
	.xword	VfmwProc_TestStopChan
	.word	897
	.zero	4
	.xword	VfmwProc_TestResetChan
	.word	898
	.zero	4
	.xword	VfmwProc_TestStartChan
	.word	899
	.zero	4
	.xword	VfmwProc_TestRestartChan
	.word	1024
	.zero	4
	.xword	VfmwProc_TestTimeSequence
	.word	1026
	.zero	4
	.xword	VfmwProc_TestStopDec
	.word	1280
	.zero	4
	.xword	VfmwProc_SetTraceCtrl
	.word	1281
	.zero	4
	.xword	VfmwProc_SetTraceBSPeriod
	.word	1282
	.zero	4
	.xword	VfmwProc_SetTraceFramePeriod
	.word	1283
	.zero	4
	.xword	VfmwProc_SetTraceImgPeriod
	.word	1285
	.zero	4
	.xword	VfmwProc_SetSaveYuvBitWidth
	.word	1536
	.zero	4
	.xword	VfmwProc_OpenModuleLowly
	.word	1537
	.zero	4
	.xword	VfmwProc_CloseModuleLowly
	.word	1538
	.zero	4
	.xword	VfmwProc_SetTunnelLineNumber
	.word	1539
	.zero	4
	.xword	VfmwProc_OpenScdLowdly
	.word	1540
	.zero	4
	.xword	VfmwProc_CloseScdLowdly
	.word	1541
	.zero	4
	.xword	VfmwProc_SetSedOnlyEnable
	.word	1792
	.zero	4
	.xword	VfmwProc_SetSmmuIrqEnable
	.word	2048
	.zero	4
	.xword	VfmwProc_SetCompressPara
	.word	2304
	.zero	4
	.xword	VfmwProc_SetClkSelect
	.word	2305
	.zero	4
	.xword	VfmwProc_SetStandardObedience
	.word	2306
	.zero	4
	.xword	VfmwProc_SetSegBypass
	.word	65535
	.zero	4
	.xword	0
	.type	__func__.54046, %object
	.size	__func__.54046, 22
__func__.54046:
	.string	"VCTRL_OutputLastFrame"
	.zero	2
	.type	__func__.53418, %object
	.size	__func__.53418, 15
__func__.53418:
	.string	"VCTRL_PostProc"
	.zero	1
	.type	__func__.53469, %object
	.size	__func__.53469, 18
__func__.53469:
	.string	"VCTRL_VdmPostProc"
	.zero	6
	.type	__func__.54073, %object
	.size	__func__.54073, 21
__func__.54073:
	.string	"VCTRL_SvdecLastFrame"
	.zero	3
	.type	__func__.53548, %object
	.size	__func__.53548, 21
__func__.53548:
	.string	"VCTRL_PutUsrdecFrame"
	.zero	3
	.type	__func__.53101, %object
	.size	__func__.53101, 16
__func__.53101:
	.string	"VCTRL_StartChan"
	.type	__func__.53117, %object
	.size	__func__.53117, 15
__func__.53117:
	.string	"VCTRL_StopChan"
	.zero	1
	.type	__func__.53210, %object
	.size	__func__.53210, 26
__func__.53210:
	.string	"VCTRL_ResetChanWithOption"
	.zero	6
	.type	__func__.53289, %object
	.size	__func__.53289, 16
__func__.53289:
	.string	"VCTRL_ResetChan"
	.type	__func__.53168, %object
	.size	__func__.53168, 17
__func__.53168:
	.string	"VCTRL_ConfigChan"
	.zero	7
	.type	__func__.53095, %object
	.size	__func__.53095, 18
__func__.53095:
	.string	"VCTRL_DestroyChan"
	.zero	6
	.type	__func__.54168, %object
	.size	__func__.54168, 30
__func__.54168:
	.string	"VCTRL_SetSingleFrameBufToChan"
	.zero	2
	.type	__func__.54180, %object
	.size	__func__.54180, 24
__func__.54180:
	.string	"VCTRL_AllocMemToDecoder"
	.data
	.align	3
.LANCHOR2 = . + 0
	.type	g_ClkSelect, %object
	.size	g_ClkSelect, 4
g_ClkSelect:
	.word	-1
	.type	g_SaveYUVBitWidth, %object
	.size	g_SaveYUVBitWidth, 4
g_SaveYUVBitWidth:
	.word	8
	.type	s_VfmwSavePath, %object
	.size	s_VfmwSavePath, 64
s_VfmwSavePath:
	.byte	47
	.byte	109
	.byte	110
	.byte	116
	.byte	0
	.zero	59
	.type	g_DefaultOutputOrder, %object
	.size	g_DefaultOutputOrder, 4
g_DefaultOutputOrder:
	.word	7
	.type	save_yuv_chan_num, %object
	.size	save_yuv_chan_num, 4
save_yuv_chan_num:
	.word	-1
	.type	g_SegBypassEnable, %object
	.size	g_SegBypassEnable, 4
g_SegBypassEnable:
	.word	1
	.type	mask_mmu_err_int, %object
	.size	mask_mmu_err_int, 4
mask_mmu_err_int:
	.word	1
	.type	g_SedOnlyEnable, %object
	.size	g_SedOnlyEnable, 4
g_SedOnlyEnable:
	.word	1
	.type	g_IRQ_FLAG, %object
	.size	g_IRQ_FLAG, 4
g_IRQ_FLAG:
	.word	128
	.type	g_not_direct_8x8_inference_flag, %object
	.size	g_not_direct_8x8_inference_flag, 1
g_not_direct_8x8_inference_flag:
	.byte	1
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC3:
	ASCII(.string	"InstID out of range" )
	.zero	4
.LC6:
	ASCII(.string	"%s %d: %s\n" )
	.zero	5
.LC9:
	ASCII(.string	"Chan inactive" )
	.zero	2
.LC11:
	ASCII(.string	"s_VfmwCTrl.event_report_vdec = NULL\n" )
	.zero	3
.LC13:
	ASCII(.string	"s_VfmwCTrl.event_report_omxvdec = NULL\n" )
.LC15:
	ASCII(.string	"%s Unkown Adapter Type: %d, Len: %d\n" )
	.zero	3
.LC18:
	ASCII(.string	"Set standard obedience: %d\n" )
	.zero	4
.LC21:
	ASCII(.string	"g_ClkSelect(%d) set error! dat = %d not support\n" )
	.zero	7
.LC24:
	ASCII(.string	"ChanID:%d, Compress Disable!" )
	.zero	3
.LC26:
	ASCII(.string	"ChanID: %d, VcmpEn: %d, LossCmpEN: %d\n" )
	.zero	1
.LC28:
	ASCII(.string	"ChanID: %d, VcmpEn: %d, LossCmpEN: %d, YRatio: 0.%d, UVRatio: 0.%d\n" )
	.zero	4
.LC31:
	ASCII(.string	"ChanID:%d; " )
	.zero	4
.LC33:
	ASCII(.string	"VCmpEnable:%d; " )
.LC35:
	ASCII(.string	"LossCmpEnable:%d; " )
	.zero	5
.LC37:
	ASCII(.string	"YCmpRatio:%d, YCmpRatio:%d\n" )
	.zero	4
.LC39:
	ASCII(.string	"ChanID %d Already Create! Can not be set!!\n" )
	.zero	4
.LC43:
	ASCII(.string	"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleLowlyEnable = 1 ------\n" )
	.zero	6
.LC45:
	ASCII(.string	"ERROR: g_SaveYUVBitWidth should be 8 or 10! (not to be %d)\n" )
	.zero	4
.LC48:
	ASCII(.string	"------ g_SaveYUVBitWidth = %d ------\n" )
	.zero	2
.LC51:
	ASCII(.string	"------ g_TraceImgPeriod = %x ------\n" )
	.zero	3
.LC54:
	ASCII(.string	"------ g_TraceFramePeriod = %x ------\n" )
	.zero	1
.LC57:
	ASCII(.string	"------ g_TraceBsPeriod = %x ------\n" )
	.zero	4
.LC60:
	ASCII(.string	"------ g_TraceCtrl = %x ------\n" )
.LC63:
	ASCII(.string	"------ dec stop = %d ------\n" )
	.zero	3
.LC66:
	ASCII(.string	"------ dec task delay %d ms ------\n" )
	.zero	4
.LC71:
	ASCII(.string	"%s/vfmw_el_save_%d.dat" )
	.zero	1
.LC73:
	ASCII(.string	"OK create file '%s' for channel %d el stream save\n" )
	.zero	5
.LC75:
	ASCII(.string	"failed create file '%s' for el stream save!\n" )
	.zero	3
.LC77:
	ASCII(.string	">>>> close el stream saving >>>>\n" )
	.zero	6
.LC80:
	ASCII(.string	"NO SUCH CHANNEL : %d\n" )
	.zero	2
.LC83:
	ASCII(.string	"Pay attention to  CHANNEL : %d\n" )
.LC86:
	ASCII(.string	"ResetCreateNewSave = %d\n" )
	.zero	7
.LC88:
	ASCII(.string	"ResetCreateNewSave can NOT be set to %d, must be 0 or 1\n" )
	.zero	7
.LC91:
	ASCII(.string	"USE_FF_APT_EN = %d\n" )
	.zero	4
.LC93:
	ASCII(.string	"USE_FF_APT_EN can NOT be set to %d, must be 0 or 1\n" )
	.zero	4
.LC96:
	ASCII(.string	"g_CfgVp9FrmNum = %d\n" )
	.zero	3
.LC98:
	ASCII(.string	"Invalid output order %d\n" )
	.zero	7
.LC100:
	ASCII(.string	"set default output order %d\n" )
	.zero	3
.LC106:
	ASCII(.string	"OK create file '%s' for channel %d metadata_reorder stream save\n" )
	.zero	7
.LC108:
	ASCII(.string	"failed create file '%s' for metadata_reorder stream save!\n" )
	.zero	5
.LC110:
	ASCII(.string	">>>> close metadata stream saving >>>>\n" )
.LC116:
	ASCII(.string	"OK create file '%s' for channel %d metadata stream save\n" )
	.zero	7
.LC118:
	ASCII(.string	"failed create file '%s' for metadata stream save!\n" )
	.zero	5
.LC123:
	ASCII(.string	"address '0x%x' is not valid!\n" )
	.zero	2
.LC127:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC129:
	ASCII(.string	"1d image has been saved to '%s'\n" )
	.zero	7
.LC131:
	ASCII(.string	"open file '%s' fail!\n" )
	.zero	2
.LC136:
	ASCII(.string	"OK create file '%s' for channel %d seg stream save\n" )
	.zero	4
.LC138:
	ASCII(.string	"failed create file '%s' for seg stream save!\n" )
	.zero	2
.LC140:
	ASCII(.string	">>>> close seg stream saving >>>>\n" )
	.zero	5
.LC146:
	ASCII(.string	"OK create file '%s' for channel %d raw stream save\n" )
	.zero	4
.LC148:
	ASCII(.string	"failed create file '%s' for raw stream save!\n" )
	.zero	2
.LC150:
	ASCII(.string	">>>> close raw stream saving >>>>\n" )
	.zero	5
.LC156:
	ASCII(.string	"Failed to alloc VFMW_DumpImageTmp size %d!\n" )
	.zero	4
.LC158:
	ASCII(.string	"OK create file '%s' for chan %d yuv save.(crop %d)\n" )
	.zero	4
.LC160:
	ASCII(.string	"failed create file '%s' for yuv save!\n" )
	.zero	1
.LC162:
	ASCII(.string	"OK close yuv save.\n" )
	.zero	4
.LC167:
	ASCII(.string	"print memory tracer...\n" )
.LC170:
	ASCII(.string	"Disable seg bypass.\n" )
	.zero	3
.LC172:
	ASCII(.string	"Enable seg bypass.\n" )
	.zero	4
.LC175:
	ASCII(.string	"unmask vfmw mmu err int!\n" )
	.zero	6
.LC177:
	ASCII(.string	"mask vfmw mmu err int!\n" )
.LC180:
	ASCII(.string	"Disable SedOnly Func\n" )
	.zero	2
.LC182:
	ASCII(.string	"Enable SedOnly Func\n" )
	.zero	3
.LC184:
	ASCII(.string	"The channel number is to Large.\n" )
	.zero	7
.LC193:
	ASCII(.string	"ChanID out of range" )
	.zero	4
.LC203:
	ASCII(.string	"Wait sleep time out %d ms (isScdSleep=%d, isVdmSleep=%d)!\n" )
	.zero	5
.LC207:
	ASCII(.string	"Vfmw suspend totally take %d ms\n" )
	.zero	7
.LC209:
	ASCII(.string	"Force scd %d sleep.\n" )
	.zero	3
.LC211:
	ASCII(.string	"Force vdm %d sleep.\n" )
	.zero	3
.LC214:
	ASCII(.string	"proc cmd need no param:%p\n" )
	.zero	5
.LC221:
	ASCII(.string	"Vfmw resume totally take %d ms\n" )
.LC232:
	ASCII(.string	"%s,%d,pos(%d) error!\n" )
	.zero	2
.LC239:
	ASCII(.string	"%s, %d, pos(%d) error!\n" )
.LC250:
	ASCII(.string	"can NOT config a not-opened Chan" )
	.zero	7
.LC252:
	ASCII(.string	"event_report null!" )
	.zero	5
.LC257:
	ASCII(.string	"%s Unkown Adapter Type: %d\n" )
	.zero	4
.LC263:
	ASCII(.string	"pstStreamParam is NULL" )
	.zero	1
.LC267:
	ASCII(.string	"ChanID invalid" )
	.zero	1
.LC285:
	ASCII(.string	"L: %d, Stream Interface Error!!, ChanID: %d\n" )
	.zero	3
.LC292:
	ASCII(.string	"This Chan has not been created!!!" )
	.zero	6
.LC294:
	ASCII(.string	"can NOT get a not-opened Chan's information of bitstream" )
	.zero	7
.LC302:
	ASCII(.string	"Raw FreshNum=%d, FreshSize=%d\n" )
	.zero	1
.LC310:
	ASCII(.string	"Seg FreshNum=%d, FreshSize=%d\n" )
	.zero	1
.LC315:
	ASCII(.string	"pArgs is null" )
	.zero	2
.LC321:
	ASCII(.string	"image size abnormal(%dx%d)\n" )
	.zero	4
.LC323:
	ASCII(.string	"no mem to arrange for soft dec\n" )
.LC326:
	ASCII(.string	"partition fs memory fail!\n" )
	.zero	5
.LC329:
	ASCII(.string	"%s: L%d : vdm chan memory is too small to support user decoder\n" )
.LC331:
	ASCII(.string	"FSP_ConfigInstance fail!\n" )
	.zero	6
.LC336:
	ASCII(.string	"parameter err, null pointer!!!" )
	.zero	1
.LC341:
	ASCII(.string	"%s FATAL: pstChan = NULL!\n" )
	.zero	5
.LC343:
	ASCII(.string	"%s FATAL: pChanMem_vdh = NULL!\n" )
.LC345:
	ASCII(.string	"%s FATAL: pChanMem_frm = NULL!\n" )
.LC347:
	ASCII(.string	"DelAllFrameMemRecord err in VCTRL_FreeChanResource !\n" )
	.zero	2
.LC349:
	ASCII(.string	"%s FATAL: pChanMem_scd = NULL!\n" )
.LC351:
	ASCII(.string	"%s FATAL: pChanMem_ctx = NULL!\n" )
.LC357:
	ASCII(.string	"pstCfg is null" )
	.zero	1
.LC367:
	ASCII(.string	"Chip not support beyond %dx%d when Std != H264/VP8/MVC/USER.\n" )
	.zero	2
.LC376:
	ASCII(.string	"ChanID out of range!" )
	.zero	3
.LC381:
	ASCII(.string	"s_pstVfmwChan = NULL" )
	.zero	3
.LC393:
	ASCII(.string	"%s,%d,s_pstVfmwChan[chanID]->FspInst.stDecFsRec[i].PhyFS.PhyAddr = 0x%x\n" )
	.zero	7
.LC395:
	ASCII(.string	"%s,%d,can't find special frame match DecFs Num = %d\n" )
	.zero	3
.LC403:
	ASCII(.string	"pImage is NULL" )
	.zero	1
.LC406:
	ASCII(.string	"vdm_ctrl.c,L%d: Chan inactive\n" )
	.zero	1
.LC408:
	ASCII(.string	"This channel %d is not opened!\n" )
.LC410:
	ASCII(.string	"%s cannot output!\n" )
	.zero	5
.LC412:
	ASCII(.string	"%s: view_0 id(%d) > view_1 id(%d), error!\n" )
	.zero	5
.LC414:
	ASCII(.string	"%s: continuous view0 id(%d)!\n" )
	.zero	2
.LC416:
	ASCII(.string	"%s: continuous view1 id(%d)!\n" )
	.zero	2
.LC426:
	ASCII(.string	"This channel is not opened" )
	.zero	5
.LC431:
	ASCII(.string	"vdm_ctrl.c,L%d: This channel is not opened\n" )
	.zero	4
.LC433:
	ASCII(.string	"vdm_ctrl.c,L%d: VCTRL_TryToRelSpecialFrm success!\n" )
	.zero	5
.LC437:
	ASCII(.string	"%s call SYNTAX_ReleaseImage failed\n" )
	.zero	4
.LC441:
	ASCII(.string	"vfmw_ctrl.c, line %d: ChanID out of range\n" )
	.zero	5
.LC443:
	ASCII(.string	"vfmw_ctrl.c, line %d: Chan %d is not open or not running\n" )
	.zero	6
.LC450:
	ASCII(.string	"pstHDRInput = null" )
	.zero	5
.LC455:
	ASCII(.string	"%s VidStd=%d Error!\n" )
	.zero	3
.LC458:
	ASCII(.string	"Get DecParam Type Failure!\n" )
	.zero	4
.LC460:
	ASCII(.string	"ChanId invalid!" )
.LC466:
	ASCII(.string	"ChanId out of range" )
	.zero	4
.LC472:
	ASCII(.string	"This channel is not running" )
	.zero	4
.LC486:
	ASCII(.string	"chan not create" )
.LC488:
	ASCII(.string	"can NOT start a not-opened Chan" )
.LC490:
	ASCII(.string	"NULL == pArgs" )
	.zero	2
.LC505:
	ASCII(.string	"%s param invalid!\n" )
	.zero	5
.LC509:
	ASCII(.string	"-1 == VCTRL_GetChanIDByCtx() Err!\n" )
	.zero	5
.LC515:
	ASCII(.string	"VCTRL_GetUsrdecFrame but VFMW_USER != s_pstVfmwChan[ChanID]->eVidStd!\n" )
	.zero	1
.LC517:
	ASCII(.string	"VCTRL_GetUsrdecFrame but s_pstVfmwChan[ChanID]->s32UsrdecFrameNum < MIN_USERDEC_FRAME_NUM!\n" )
	.zero	4
.LC519:
	ASCII(.string	"get frame store fail!\n" )
	.zero	1
.LC521:
	ASCII(.string	"get image buffer ok: LogicFsID = %d\n" )
	.zero	3
.LC523:
	ASCII(.string	"line: %d, pLf is NULL!\n" )
.LC525:
	ASCII(.string	"decode %p, disp %p, tf %p\n" )
	.zero	5
.LC527:
	ASCII(.string	"VCTRL_GetUsrdecFrame get LogicFs fail!\n" )
.LC534:
	ASCII(.string	"CAP_LEVEL_USER_DEFINE_WITH_OPTION option is illegal.\n" )
	.zero	2
.LC537:
	ASCII(.string	"VCTRL_GetChanMemSizeByOption L%d: arrange return failure\n" )
	.zero	6
.LC542:
	ASCII(.string	"ERROR: s32MaxRefFrameNum(%d), extra_ref(%d), s32DisplayFrameNum(%d), extra_disp(%d)\n" )
	.zero	3
.LC550:
	ASCII(.string	"MEM_MapRegisterAddr reg 0x%x failed!\n" )
	.zero	2
.LC555:
	ASCII(.string	"VDMHAL_GetHalMemSize Vdh %d failed!\n" )
	.zero	3
.LC557:
	ASCII(.string	"MEM_AllocMemBlock Vdh %d failed!\n" )
	.zero	6
.LC559:
	ASCII(.string	"VDMHAL_OpenHAL Vdh %d failed!\n" )
	.zero	1
.LC561:
	ASCII(.string	"MEM_AllocMemBlock VFMW_VP9Prob %d failed!\n" )
	.zero	5
.LC566:
	ASCII(.string	"MEM_AllocMemBlock Scd %d failed!\n" )
	.zero	6
.LC568:
	ASCII(.string	"SM_OpenSCDDrv Scd %d failed!\n" )
	.zero	2
.LC570:
	ASCII(.string	"Register irq %d failed!\n" )
	.zero	7
.LC575:
	ASCII(.string	"HEVCDEC_AllocHevcGlbMem Error!\n" )
.LC579:
	ASCII(.string	"pArgs = NULL" )
	.zero	3
.LC586:
	ASCII(.string	"extra_ref=" )
	.zero	5
.LC588:
	ASCII(.string	"=" )
	.zero	6
.LC590:
	ASCII(.string	" " )
	.zero	6
.LC592:
	ASCII(.string	"fuction return value is null,%s %d unknow error!!\n" )
	.zero	5
.LC594:
	ASCII(.string	"ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\n" )
	.zero	6
.LC596:
	ASCII(.string	"extra_disp=" )
	.zero	4
.LC598:
	ASCII(.string	"ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\n" )
	.zero	5
.LC602:
	ASCII(.string	"extra_cmd=" )
	.zero	5
.LC609:
	ASCII(.string	"HI_VFMW_VideoDecode" )
	.zero	4
.LC614:
	ASCII(.string	"(safe,warn,danger) :amount = %d,%d,%d,%d\n" )
	.zero	6
.LC616:
	ASCII(.string	"strm_ctrl: I->IPB\n" )
	.zero	5
.LC618:
	ASCII(.string	"strm_ctrl: IPB->I\n" )
	.zero	5
.LC620:
	ASCII(.string	"(CurrMode,NextMode) = %d,%d\n" )
	.zero	3
.LC625:
	ASCII(.string	"pic_pts: %lld\n" )
	.zero	1
.LC627:
	ASCII(.string	"pic_usertag: %lld\n" )
	.zero	5
.LC629:
	ASCII(.string	"pic_pts: %lld pic_usertag = %lld\n" )
	.zero	6
.LC639:
	ASCII(.string	"Syntax is stopped from This channel" )
	.zero	4
.LC644:
	ASCII(.string	"[%d] vdm busy\n" )
	.zero	1
.LC646:
	ASCII(.string	"[%d] no frame\n" )
	.zero	1
.LC648:
	ASCII(.string	"DFS, Wait Partition\n" )
	.zero	3
.LC650:
	ASCII(.string	"DFS, Partition fail, u32DynamicFrameStoreAllocEn: %d, eFspPartitionState: %d\n" )
	.zero	2
.LC652:
	ASCII(.string	"[%d] no stream\n" )
.LC654:
	ASCII(.string	"seg_pts: %lld, seg_usertag = %lld\n" )
	.zero	5
.LC667:
	ASCII(.string	"Thread running...\n" )
	.zero	5
.LC669:
	ASCII(.string	"Thread stopped!\n" )
	.zero	7
.LC671:
	ASCII(.string	"thread running...\n" )
	.zero	5
.LC673:
	ASCII(.string	"thread stopped...\n" )
	.zero	5
.LC676:
	ASCII(.string	"Thread killed!\n" )
.LC684:
	ASCII(.string	"ERROR:ReadNum = %d larger than VFMW_MAX_RESERVE_NUM(%d)\n" )
	.zero	7
.LC687:
	ASCII(.string	"The array of occupied frames is overflow, s_pstVfmwChan[%d]->specialFrameNum = %d" )
	.zero	6
.LC692:
	ASCII(.string	"pSpecialFrmInfo = null!!!" )
	.zero	6
.LC697:
	ASCII(.string	"pRefImgNum  = null" )
	.zero	5
.LC701:
	ASCII(.string	"pReadImgNum = null" )
	.zero	5
.LC703:
	ASCII(.string	"pNewImgNum  = null" )
	.zero	5
.LC710:
	ASCII(.string	"pstChanState = NULL" )
	.zero	4
.LC735:
	ASCII(.string	"SetVdecExtra ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\n" )
	.zero	1
.LC737:
	ASCII(.string	"SetVdecExtra ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\n" )
.LC746:
	ASCII(.string	"Command \"%d\" not registerd!\n" )
	.zero	3
.LC752:
	ASCII(.string	"Chan %d Report Last Frame, Value=%d, LastFrameState=%d\n" )
.LC760:
	ASCII(.string	"Last frame output failed!\n" )
	.zero	5
.LC762:
	ASCII(.string	"Last frame output successed!\n" )
	.zero	2
.LC764:
	ASCII(.string	"Last frame already output, image id: %d!\n" )
	.zero	6
.LC781:
	ASCII(.string	"line %d can not know YuvFormat = %d\n" )
	.zero	3
.LC783:
	ASCII(.string	"userdec frame(phy=%#x) address error!\n" )
	.zero	1
.LC785:
	ASCII(.string	"can not map vir addr for usrdat frame(cbphy=%#x)\n" )
	.zero	6
.LC787:
	ASCII(.string	"line: %d, pLogic is Null!\n" )
	.zero	5
.LC790:
	ASCII(.string	"eYuvFormat %d is not support!!\n" )
.LC797:
	ASCII(.string	"pUsrdecFrame == NULL" )
	.zero	3
.LC799:
	ASCII(.string	"VCTRL_PutUsrdecFrame: VidStd is %d\n" )
	.zero	4
.LC802:
	ASCII(.string	"VCTRL_PutUsrdecFrame return err\n" )
	.zero	7
.LC804:
	ASCII(.string	"L:%d ChanID out of range\n" )
	.zero	6
.LC807:
	ASCII(.string	"L:%d This Chan has not been created!!!\n" )
.LC809:
	ASCII(.string	"L:%d WARNING: vidio std not setted!\n" )
	.zero	3
.LC821:
	ASCII(.string	"WARNING: vidio std not setted!" )
	.zero	1
.LC831:
	ASCII(.string	"start chan %d: VCTRL_StartChan return %d\n" )
	.zero	6
.LC842:
	ASCII(.string	"This Chan has not been created or has been destroyed !" )
	.zero	1
.LC845:
	ASCII(.string	"VCTRL_StopChanWithCheck fail!\n" )
	.zero	1
.LC852:
	ASCII(.string	"vdm_ctrl.c,L%d: pOption->s32KeepBS error\n" )
	.zero	6
.LC856:
	ASCII(.string	"-------------------------------------------------------------------------\n" )
	.zero	5
.LC871:
	ASCII(.string	"Param Invalid of PChanOption is NULL\n" )
	.zero	2
.LC874:
	ASCII(.string	"line %d VCTRL_GetChanMemSize failed!\n" )
	.zero	2
.LC877:
	ASCII(.string	"ChanID: %d is out of range!\n" )
	.zero	3
.LC879:
	ASCII(.string	"vfmw have max(%d) channels opened, can NOT create more channels\n" )
	.zero	7
.LC881:
	ASCII(.string	"L: %d : part we can NOT alloc buffer for channel context\n" )
	.zero	6
.LC883:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel context\n" )
	.zero	6
.LC885:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel vdh\n" )
	.zero	2
.LC887:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel vdh, %#x < %#x\n" )
	.zero	7
.LC889:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel scd\n" )
	.zero	2
.LC891:
	ASCII(.string	"L: %d : can NOT alloc buffer for SCD\n" )
	.zero	2
.LC894:
	ASCII(.string	"Chan:%d can NOT enable FSP instance\n" )
	.zero	3
.LC898:
	ASCII(.string	"pstCfg = NULL" )
	.zero	2
.LC906:
	ASCII(.string	"VCTRL_CheckChanWH return err.\n" )
	.zero	1
.LC909:
	ASCII(.string	"VFMW didn't support std %d.\n" )
	.zero	3
.LC911:
	ASCII(.string	"VCTRL_ConfigChan with same config paramater.\n" )
	.zero	2
.LC915:
	ASCII(.string	"can NOT VCTRL_PartitionMemForStdUser\n" )
	.zero	2
.LC922:
	ASCII(.string	"chan %d: new UvmosEnable = %d\n" )
	.zero	1
.LC925:
	ASCII(.string	"chan %d: SetUvmosEnable failed!\n" )
	.zero	7
.LC927:
	ASCII(.string	"chan %d: new StrmOFThr = %d\n" )
	.zero	3
.LC930:
	ASCII(.string	"chan %d: new DecMode = %d\n" )
	.zero	5
.LC933:
	ASCII(.string	"chan %d: GetChanCfg failed!\n" )
	.zero	3
.LC935:
	ASCII(.string	"chan %d: new DecOrderOutput = %d\n" )
	.zero	6
.LC938:
	ASCII(.string	"chan %d: new ChanErrThr = %d\n" )
	.zero	2
.LC941:
	ASCII(.string	"reset chan %d: VCTRL_ResetChan return %d\n" )
	.zero	6
.LC946:
	ASCII(.string	"%s:L%d: %s\n" )
	.zero	4
.LC949:
	ASCII(.string	"This Chan has not been created or has been destroyed !!!" )
	.zero	7
.LC951:
	ASCII(.string	"can NOT stop a not-opened Chan" )
	.zero	1
.LC962:
	ASCII(.string	"stop chan %d: VCTRL_StopChan return %d\n" )
.LC972:
	ASCII(.string	"WARNNING: dsp in lowdelay state, we can not supported  avs in the same time!!!\n" )
.LC974:
	ASCII(.string	"WARNNING: dsp in avs state, we can not supported  lowdelay in the same time!!!\n" )
.LC984:
	ASCII(.string	"%s, %d, actul size = 0x%x, except size= 0x%x\n" )
	.zero	2
.LC986:
	ASCII(.string	"%s, %d, CfgFrameNum = %x, PmvNodeStatus= 0x%x\n" )
	.zero	1
.LC989:
	ASCII(.string	"%s: Chan %d set single frame failed!\n" )
	.zero	2
.LC991:
	ASCII(.string	"%s: Chan %d no frame buffer store!\n" )
	.zero	4
.LC996:
	ASCII(.string	"DFS, request frame store fail!, chanid: %d\n" )
	.zero	4
.LC998:
	ASCII(.string	"DFS, set decoding thread state to success!\n " )
	.zero	3
.LC1001:
	ASCII(.string	"%s set chan %d ctrl state CHAN_FRAME_STORE_ALLOC failed!\n" )
	.bss
	.align	3
.LANCHOR1 = . + 0
.LANCHOR3 = . + 4352
.LANCHOR5 = . + 8704
	.type	s_pstVfmwChan, %object
	.size	s_pstVfmwChan, 256
s_pstVfmwChan:
	.zero	256
	.type	s_VfmwCTrl, %object
	.size	s_VfmwCTrl, 344
s_VfmwCTrl:
	.zero	344
	.type	g_StandardObedience, %object
	.size	g_StandardObedience, 4
g_StandardObedience:
	.zero	4
	.zero	4
	.type	g_VfmwCompressPara, %object
	.size	g_VfmwCompressPara, 512
g_VfmwCompressPara:
	.zero	512
	.type	g_StopDec, %object
	.size	g_StopDec, 4
g_StopDec:
	.zero	4
	.type	g_SleepTime, %object
	.size	g_SleepTime, 4
g_SleepTime:
	.zero	4
	.type	vfmw_save_el_file, %object
	.size	vfmw_save_el_file, 256
vfmw_save_el_file:
	.zero	256
	.type	save_file_cnt.53909, %object
	.size	save_file_cnt.53909, 4
save_file_cnt.53909:
	.zero	4
	.type	save_el_chan_num, %object
	.size	save_el_chan_num, 4
save_el_chan_num:
	.zero	4
	.type	g_CurProcChan, %object
	.size	g_CurProcChan, 4
g_CurProcChan:
	.zero	4
	.type	g_ResetCreateNewSave, %object
	.size	g_ResetCreateNewSave, 4
g_ResetCreateNewSave:
	.zero	4
	.type	vfmw_save_metadata_reorder_file, %object
	.size	vfmw_save_metadata_reorder_file, 256
vfmw_save_metadata_reorder_file:
	.zero	256
	.type	save_file_cnt.53903, %object
	.size	save_file_cnt.53903, 4
save_file_cnt.53903:
	.zero	4
	.type	save_metadata_reorder_chan_num, %object
	.size	save_metadata_reorder_chan_num, 4
save_metadata_reorder_chan_num:
	.zero	4
	.type	vfmw_save_metadata_file, %object
	.size	vfmw_save_metadata_file, 256
vfmw_save_metadata_file:
	.zero	256
	.type	save_file_cnt.53897, %object
	.size	save_file_cnt.53897, 4
save_file_cnt.53897:
	.zero	4
	.type	save_metadata_chan_num, %object
	.size	save_metadata_chan_num, 4
save_metadata_chan_num:
	.zero	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 256
vfmw_save_seg_file:
	.zero	256
	.type	save_file_cnt.53875, %object
	.size	save_file_cnt.53875, 4
save_file_cnt.53875:
	.zero	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.zero	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 256
vfmw_save_str_file:
	.zero	256
	.type	save_file_cnt.53869, %object
	.size	save_file_cnt.53869, 4
save_file_cnt.53869:
	.zero	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.zero	4
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 256
vfmw_save_yuv_file:
	.zero	256
	.type	save_file_cnt.53882, %object
	.size	save_file_cnt.53882, 4
save_file_cnt.53882:
	.zero	4
	.zero	4
	.type	MemRecord_YUV, %object
	.size	MemRecord_YUV, 32
MemRecord_YUV:
	.zero	32
	.type	pVl, %object
	.size	pVl, 8
pVl:
	.zero	8
	.type	pUl, %object
	.size	pUl, 8
pUl:
	.zero	8
	.type	pY, %object
	.size	pY, 8
pY:
	.zero	8
	.type	pVl_2bit, %object
	.size	pVl_2bit, 8
pVl_2bit:
	.zero	8
	.type	pUl_2bit, %object
	.size	pUl_2bit, 8
pUl_2bit:
	.zero	8
	.type	pY_2bit, %object
	.size	pY_2bit, 8
pY_2bit:
	.zero	8
	.type	save_yuv_with_crop, %object
	.size	save_yuv_with_crop, 4
save_yuv_with_crop:
	.zero	4
	.zero	4
	.type	pPixelArray, %object
	.size	pPixelArray, 8
pPixelArray:
	.zero	8
	.type	g_IsrFlag, %object
	.size	g_IsrFlag, 1
g_IsrFlag:
	.zero	1
	.zero	7
	.type	s_StreamIntf, %object
	.size	s_StreamIntf, 768
s_StreamIntf:
	.zero	768
	.type	FspInstInfo.52967, %object
	.size	FspInstInfo.52967, 2824
FspInstInfo.52967:
	.zero	2824
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.zero	4
	.zero	4
	.type	last_rec_pos_time.53304, %object
	.size	last_rec_pos_time.53304, 128
last_rec_pos_time.53304:
	.zero	128
	.type	last_rec_pos_time.53315, %object
	.size	last_rec_pos_time.53315, 128
last_rec_pos_time.53315:
	.zero	128
	.type	MemArrange.53583, %object
	.size	MemArrange.53583, 1232
MemArrange.53583:
	.zero	1232
	.type	extra_ref, %object
	.size	extra_ref, 4
extra_ref:
	.zero	4
	.type	extra_disp, %object
	.size	extra_disp, 4
extra_disp:
	.zero	4
	.type	g_VfmwIrqHandle, %object
	.size	g_VfmwIrqHandle, 4
g_VfmwIrqHandle:
	.zero	4
	.zero	4
	.type	cmdline, %object
	.size	cmdline, 1024
cmdline:
	.zero	1024
	.type	extra_cmd, %object
	.size	extra_cmd, 4
extra_cmd:
	.zero	4
	.type	g_allow_B_before_P, %object
	.size	g_allow_B_before_P, 1
g_allow_B_before_P:
	.zero	1
	.type	g_not_allow_H264FullPictureRepair_flag, %object
	.size	g_not_allow_H264FullPictureRepair_flag, 1
g_not_allow_H264FullPictureRepair_flag:
	.zero	1
	.type	g_apple_airplay_mirrorinig_flag, %object
	.size	g_apple_airplay_mirrorinig_flag, 1
g_apple_airplay_mirrorinig_flag:
	.zero	1
	.zero	1
	.type	g_event_report, %object
	.size	g_event_report, 8
g_event_report:
	.zero	8
	.type	g_DSPState, %object
	.size	g_DSPState, 128
g_DSPState:
	.zero	128
	.type	last_rec_pos_time.53701, %object
	.size	last_rec_pos_time.53701, 128
last_rec_pos_time.53701:
	.zero	128
	.type	last_rec_pos_decparam_time.53702, %object
	.size	last_rec_pos_decparam_time.53702, 128
last_rec_pos_decparam_time.53702:
	.zero	128
	.type	ChanPriTab.53651, %object
	.size	ChanPriTab.53651, 128
ChanPriTab.53651:
	.zero	128
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 768
g_VfmwChanStat:
	.zero	768
	.type	PrioArray.53100, %object
	.size	PrioArray.53100, 128
PrioArray.53100:
	.zero	128
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 128
s_ChanControlState:
	.zero	128
	.type	Capability.53164, %object
	.size	Capability.53164, 148
Capability.53164:
	.zero	148
	.zero	4
	.type	PrioArray.53163, %object
	.size	PrioArray.53163, 128
PrioArray.53163:
	.zero	128
	.type	g_EsBufValidFlag, %object
	.size	g_EsBufValidFlag, 128
g_EsBufValidFlag:
	.zero	128
	.type	g_eVdmVersion, %object
	.size	g_eVdmVersion, 4
g_eVdmVersion:
	.zero	4
	.zero	4
	.type	g_VfmwGlobalStat, %object
	.size	g_VfmwGlobalStat, 60
g_VfmwGlobalStat:
	.zero	60
	.zero	4
	.type	AcceleratorCharacter, %object
	.size	AcceleratorCharacter, 8
AcceleratorCharacter:
	.zero	8
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
