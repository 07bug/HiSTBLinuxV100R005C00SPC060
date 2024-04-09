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
	add	x2, x0, 307200
	mov	w0, 0
	str	w20, [x2, 1524]
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
	add	x0, x0, 307200
	ldr	w0, [x0, 1524]
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
	mov	w0, 31688
	movk	w0, 0xc, lsl 16
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L471:
	mov	w0, 17864
	movk	w0, 0xb2, lsl 16
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
	add	x0, x3, 311296
	ldr	w1, [x0, 1544]
	cbz	w1, .L536
	ldr	w0, [x0, 1020]
	mov	w2, 0
	cmp	w22, w0
	bne	.L539
	b	.L568
	.p2align 3
.L540:
	add	x0, x0, 3135
	add	x0, x3, x0, lsl 4
	ldr	w0, [x0, 12]
	cmp	w22, w0
	beq	.L537
.L539:
	add	w2, w2, 1
	cmp	w1, w2
	mov	w20, w2
	sxtw	x0, w2
	add	x0, x0, 16384
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
	add	x0, x3, 299008
	mov	w21, 1
	add	x0, x0, 3896
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
	add	x3, x1, 299008
	add	x1, x1, 303104
	strb	wzr, [x3, 3802]
	strb	wzr, [x1, 2522]
	blr	x2
	cmp	w22, w20
	bls	.L551
	sxtw	x21, w24
	uxtw	x23, w20
	.p2align 2
.L543:
	add	w20, w20, 1
	add	x23, x23, 16384
	add	x0, x23, 3135
	ldr	x3, [x19, x21, lsl 3]
	uxtw	x23, w20
	ldr	x4, [x25, 104]
	add	x1, x23, 16384
	add	x0, x3, x0, lsl 4
	add	x1, x1, 3135
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
	add	x0, x0, 16384
	ldr	x3, [x25, 96]
	add	x0, x0, 3135
	mov	x2, 16
	mov	w1, 0
	add	x0, x4, x0, lsl 4
	add	x0, x0, 8
	blr	x3
	ldr	x1, [x19, w24, sxtw 3]
	mov	w0, 0
	add	x1, x1, 311296
	ldr	w2, [x1, 1544]
	sub	w2, w2, #1
	str	w2, [x1, 1544]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L570:
	add	x2, x3, 278528
	ldr	x20, .LC389
	ldr	x1, .LC396
	mov	w3, 3295
	add	x20, x20, 512
	mov	w0, 1
	ldrsb	w4, [x2, 2123]
	mov	x2, x20
	bl	dprint_vfmw
	ldr	x6, [x19, w24, sxtw 3]
	add	x0, x6, 278528
	ldrsb	w0, [x0, 2123]
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
	add	x4, x4, 299008
	ldr	w4, [x4, 3808]
	bl	dprint_vfmw
	ldr	x6, [x19, x21, lsl 3]
	add	x0, x6, 278528
	ldrsb	w0, [x0, 2123]
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
	add	x0, x0, 311296
	mov	x1, x19
	add	x0, x0, 1616
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
	add	x1, x1, 327680
	ldrb	w1, [x1, 1128]
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
	add	x0, x0, 311296
	add	x0, x0, 1616
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
	add	x0, x1, 311296
	add	x0, x0, 1616
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
	add	x0, x0, 311296
	add	x0, x0, 1616
	bl	SYNTAX_ReturnImage
	ldr	x0, [x21, w20, sxtw 3]
	mov	x1, x19
	add	x0, x0, 311296
	add	x0, x0, 1616
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
	add	x0, x0, 311296
	add	x0, x0, 1616
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
	add	x0, x0, 311296
	add	x0, x0, 1616
	bl	SYNTAX_ReturnImage
	ldr	x0, [x21, w20, sxtw 3]
	mov	x1, x19
	add	x0, x0, 311296
	add	x0, x0, 1616
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
	add	x0, x0, 311296
	add	x0, x0, 1616
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
	add	x0, x0, 311296
	add	x0, x0, 1616
	bl	SYNTAX_ReleaseImage
	mov	w23, w0
	ldr	w2, [x20, 188]
	cmn	w2, #1
	beq	.L626
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x29, 64
	str	w2, [x29, 212]
	add	x0, x0, 311296
	add	x0, x0, 1616
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
	bhi	.L682
	ldr	x0, .LC452
	ldr	x20, [x0, w19, sxtw 3]
	cbz	x20, .L682
	ldr	w0, [x20, 4]
	mov	x1, 0
	cmp	w0, 1
	bne	.L661
	ldr	w0, [x20, 8]
	cmp	w0, 1
	bne	.L661
	ldr	w3, [x20, 632]
	cmp	w3, 17
	bls	.L683
.L662:
	ldr	x2, .LC454
	mov	w0, 0
	ldr	x1, .LC456
	add	x2, x2, 664
	bl	dprint_vfmw
	mov	x1, 0
	b	.L661
	.p2align 3
.L682:
	mov	x1, 0
.L661:
	mov	x0, x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L683:
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
	.text
	.p2align 3
.L672:
	add	x0, x20, 311296
	ldr	x19, [x0, 1632]
.L677:
	cbz	x19, .L682
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
.L674:
	add	x0, x20, 311296
	ldr	x19, [x0, 1856]
	b	.L677
	.p2align 3
.L666:
	add	x0, x20, 311296
	ldr	x19, [x0, 2664]
	b	.L677
	.p2align 3
.L675:
	add	x0, x20, 311296
	ldr	x19, [x0, 4072]
	b	.L677
	.p2align 3
.L663:
	add	x0, x20, 311296
	ldr	x19, [x0, 2240]
	b	.L677
	.p2align 3
.L669:
	add	x0, x20, 311296
	ldr	x19, [x0, 1648]
	b	.L677
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
	str	x19, [sp, 16]
	mov	x19, x1
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L686
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L686:
	ldr	x1, .LC459
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
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
	bhi	.L704
	ldr	x0, .LC464
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w1, [x0, 632]
	cmp	w1, 17
	bls	.L705
.L687:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L705:
	ldr	x2, .LC465
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx691
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx691:
	.section	.rodata
	.align	0
	.align	2
.L691:
	.byte	(.L690 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L693 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L687 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L696 - .Lrtx691) / 4
	.byte	(.L687 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.byte	(.L687 - .Lrtx691) / 4
	.byte	(.L701 - .Lrtx691) / 4
	.byte	(.L702 - .Lrtx691) / 4
	.byte	(.L700 - .Lrtx691) / 4
	.text
	.p2align 3
.L700:
	add	x0, x0, 311296
	str	xzr, [x0, 1632]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L704:
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
.L696:
	add	x0, x0, 311296
	str	xzr, [x0, 1648]
	b	.L687
	.p2align 3
.L701:
	add	x0, x0, 311296
	str	xzr, [x0, 1856]
	b	.L687
	.p2align 3
.L693:
	add	x0, x0, 311296
	str	xzr, [x0, 2664]
	b	.L687
	.p2align 3
.L702:
	add	x0, x0, 311296
	str	xzr, [x0, 4072]
	b	.L687
	.p2align 3
.L690:
	add	x0, x0, 311296
	str	xzr, [x0, 2240]
	b	.L687
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
	.xword	.L691
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VCTRL_VdmProcSedOnly
	.type	VCTRL_VdmProcSedOnly, %function
VCTRL_VdmProcSedOnly:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 31
	bhi	.L711
	ldr	x0, .LC470
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L712
	ldr	w0, [x0, 8]
	cmp	w0, 1
	beq	.L710
	ldr	x2, .LC468
	mov	w3, 4241
	ldr	x4, .LC473
	mov	w0, 0
	ldr	x1, .LC469
	add	x2, x2, 24
	bl	dprint_vfmw
.L706:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L710:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L711:
	ldr	x2, .LC468
	mov	w3, 4239
	ldr	x4, .LC467
	mov	w0, 0
	ldr	x1, .LC469
	add	x2, x2, 24
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L712:
	ldr	x2, .LC468
	mov	w3, 4240
	ldr	x4, .LC471
	ldr	x1, .LC469
	add	x2, x2, 24
	bl	dprint_vfmw
	b	.L706
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
	bhi	.L736
	ldr	x0, .LC477
	ldr	x1, [x0, w19, sxtw 3]
	cbz	x1, .L737
	ldr	w0, [x1, 8]
	cmp	w0, 1
	bne	.L738
	ldr	w2, [x1, 632]
	cmp	w2, 17
	bls	.L739
.L732:
	mov	w0, 0
	b	.L715
	.p2align 3
.L739:
	ldr	x3, .LC480
	ldrb	w2, [x3,w2,uxtw]
	adr	x3, .Lrtx719
	add	x2, x3, w2, sxtb #2
	br	x2
.Lrtx719:
	.section	.rodata
	.align	0
	.align	2
.L719:
	.byte	(.L718 - .Lrtx719) / 4
	.byte	(.L720 - .Lrtx719) / 4
	.byte	(.L721 - .Lrtx719) / 4
	.byte	(.L722 - .Lrtx719) / 4
	.byte	(.L732 - .Lrtx719) / 4
	.byte	(.L723 - .Lrtx719) / 4
	.byte	(.L724 - .Lrtx719) / 4
	.byte	(.L732 - .Lrtx719) / 4
	.byte	(.L725 - .Lrtx719) / 4
	.byte	(.L726 - .Lrtx719) / 4
	.byte	(.L727 - .Lrtx719) / 4
	.byte	(.L727 - .Lrtx719) / 4
	.byte	(.L727 - .Lrtx719) / 4
	.byte	(.L728 - .Lrtx719) / 4
	.byte	(.L732 - .Lrtx719) / 4
	.byte	(.L729 - .Lrtx719) / 4
	.byte	(.L730 - .Lrtx719) / 4
	.byte	(.L731 - .Lrtx719) / 4
	.text
	.p2align 3
.L731:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	VP9DEC_GetImageBuffer
.L715:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L730:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	HEVCDEC_GetImageBuffer
	b	.L715
	.p2align 3
.L729:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	MVC_DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L728:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	VP8DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L727:
	ldr	x2, .LC481
	ldr	w2, [x2, 2064]
	tbz	x2, 0, .L715
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	VP6DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L726:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	REAL9DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L725:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	REAL8DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L724:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	AVSDEC_GetImageBuffer
	b	.L715
	.p2align 3
.L723:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	DIVX3DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L722:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	MPEG2DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L721:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	MPEG4DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L720:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	VC1DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L718:
	add	x0, x1, 311296
	add	x0, x0, 1624
	bl	H264DEC_GetImageBuffer
	b	.L715
	.p2align 3
.L738:
	ldr	x2, .LC475
	mov	w3, 4276
	ldr	x4, .LC479
	mov	w0, 0
	ldr	x1, .LC476
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L715
	.p2align 3
.L736:
	ldr	x2, .LC475
	mov	w3, 4274
	ldr	x4, .LC474
	mov	w0, 0
	ldr	x1, .LC476
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L715
.L737:
	ldr	x2, .LC475
	mov	w3, 4275
	ldr	x4, .LC478
	mov	w0, 0
	ldr	x1, .LC476
	add	x2, x2, 48
	bl	dprint_vfmw
	mov	w0, -1
	b	.L715
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
	.xword	.L719
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
	bhi	.L746
	ldr	x0, .LC485
	ldr	x2, [x0, w19, sxtw 3]
	cbz	x2, .L747
	ldr	w0, [x2, 4]
	cmp	w0, 1
	bne	.L748
	cbz	x20, .L749
	ldr	w1, [x20]
	mov	w0, 0
	str	w1, [x2, 1300]
.L742:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L748:
	ldr	x2, .LC483
	mov	w3, 4392
	ldr	x4, .LC489
	mov	w0, 0
	ldr	x1, .LC484
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L742
	.p2align 3
.L746:
	ldr	x2, .LC483
	mov	w3, 4390
	ldr	x4, .LC482
	mov	w0, 0
	ldr	x1, .LC484
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L742
.L747:
	ldr	x2, .LC483
	mov	w3, 4391
	ldr	x4, .LC487
	mov	w0, 0
	ldr	x1, .LC484
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L742
.L749:
	ldr	x2, .LC483
	mov	w3, 4393
	ldr	x4, .LC491
	mov	w0, 0
	ldr	x1, .LC484
	add	x2, x2, 72
	bl	dprint_vfmw
	mov	w0, -1
	b	.L742
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
	bhi	.L756
	ldr	x0, .LC495
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L757
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L758
	cbz	x20, .L759
	ldr	x3, .LC499
	mov	x2, 20
	mov	x1, x20
	add	x0, x0, 1336
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L752:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L758:
	ldr	x2, .LC493
	mov	w3, 4405
	ldr	x4, .LC497
	mov	w0, 0
	ldr	x1, .LC494
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L752
	.p2align 3
.L756:
	ldr	x2, .LC493
	mov	w3, 4403
	ldr	x4, .LC492
	mov	w0, 0
	ldr	x1, .LC494
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L752
.L759:
	ldr	x2, .LC493
	mov	w3, 4406
	ldr	x4, .LC498
	mov	w0, 0
	ldr	x1, .LC494
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L752
.L757:
	ldr	x2, .LC493
	mov	w3, 4404
	ldr	x4, .LC496
	ldr	x1, .LC494
	add	x2, x2, 96
	bl	dprint_vfmw
	mov	w0, -1
	b	.L752
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
	bhi	.L767
	ldr	x0, .LC503
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L766
	ldr	w1, [x0, 4]
	cbz	w1, .L766
	ldr	w1, [x0, 8]
	cbz	w1, .L766
	ldr	w1, [x0, 20]
	cbz	w1, .L766
	ldr	w0, [x0, 632]
	cmp	w0, 22
	csetm	w0, eq
.L762:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L766:
	mov	w0, -1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L767:
	ldr	x2, .LC501
	mov	w3, 4415
	ldr	x4, .LC500
	mov	w0, 0
	ldr	x1, .LC502
	add	x2, x2, 120
	bl	dprint_vfmw
	mov	w0, -1
	b	.L762
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
	beq	.L784
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
	b	.L773
	.p2align 3
.L771:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L785
.L773:
	ldr	x2, [x3, x0, lsl 3]
	add	x1, x2, 311296
	add	x1, x1, 1624
	cbz	x2, .L771
	cmp	x19, x1
	bne	.L771
	cmn	w0, #1
	str	w0, [x19, 616]
	mov	w0, 1
	beq	.L775
.L779:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L785:
	mov	w0, -1
	str	w0, [x19, 616]
.L775:
	ldr	x1, .LC510
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -20
	b	.L779
.L784:
	ldr	x2, .LC504
	mov	w0, 0
	ldr	x1, .LC506
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w0, -20
	b	.L779
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
	cbz	x19, .L788
	ldr	w0, [x19, 616]
	mov	w1, w20
	mov	w2, 0
	bl	FSP_SetDisplay
	ldr	w0, [x19, 616]
	mov	w1, w20
	bl	FSP_GetFsImagePtr
	mov	x20, x0
	cbz	x0, .L789
	ldr	w0, [x19, 616]
	ldr	x1, [x20, 544]
	bl	FreeUsdByDec
	str	xzr, [x20, 544]
	ldr	x1, [x20, 552]
	ldr	w0, [x19, 616]
	bl	FreeUsdByDec
	str	xzr, [x20, 552]
	mov	w0, 1
.L787:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L789:
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L788:
	mov	w0, -2
	b	.L787
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
	cbz	x0, .L804
	ldr	w1, [x0, 632]
	cmp	w1, 20
	bne	.L805
	ldr	w0, [x0, 556]
	cmp	w0, 2
	ble	.L806
	mov	w1, 1
	mov	w0, w20
	bl	FSP_NewLogicFs
	mov	w22, w0
	tbnz	w0, #31, .L807
	mov	w1, w0
	mov	w0, w20
	bl	FSP_GetLogicFs
	mov	x19, x0
	ldr	x1, .LC522
	mov	w2, w22
	mov	w0, 18
	bl	dprint_vfmw
	cbz	x19, .L808
	ldr	x0, [x19, 32]
	cbz	x0, .L797
	ldr	x1, [x19, 40]
	cbz	x1, .L797
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
.L792:
	mov	w0, w1
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L805:
	ldr	x1, .LC516
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L792
	.p2align 3
.L806:
	ldr	x1, .LC518
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L792
	.p2align 3
.L797:
	ldr	x1, .LC528
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L792
	.p2align 3
.L807:
	ldr	x1, .LC520
	mov	w0, 0
	bl	dprint_vfmw
	mov	w1, -1
	b	.L792
.L804:
	ldr	x2, .LC513
	mov	w3, 4607
	ldr	x1, .LC514
	ldr	x4, .LC512
	add	x2, x2, 160
	bl	dprint_vfmw
	mov	w1, -1
	b	.L792
.L808:
	ldr	x1, .LC524
	mov	w2, 4635
	mov	w0, 22
	bl	dprint_vfmw
	mov	w1, -1
	b	.L792
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
	cbz	x1, .L827
	ldr	w0, [x1, 632]
	cmp	w0, 20
	bls	.L828
.L809:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L828:
	ldr	x2, .LC533
	ldrb	w0, [x2,w0,uxtw]
	adr	x2, .Lrtx813
	add	x0, x2, w0, sxtb #2
	br	x0
.Lrtx813:
	.section	.rodata
	.align	0
	.align	2
.L813:
	.byte	(.L812 - .Lrtx813) / 4
	.byte	(.L814 - .Lrtx813) / 4
	.byte	(.L815 - .Lrtx813) / 4
	.byte	(.L816 - .Lrtx813) / 4
	.byte	(.L809 - .Lrtx813) / 4
	.byte	(.L817 - .Lrtx813) / 4
	.byte	(.L818 - .Lrtx813) / 4
	.byte	(.L809 - .Lrtx813) / 4
	.byte	(.L819 - .Lrtx813) / 4
	.byte	(.L820 - .Lrtx813) / 4
	.byte	(.L821 - .Lrtx813) / 4
	.byte	(.L821 - .Lrtx813) / 4
	.byte	(.L821 - .Lrtx813) / 4
	.byte	(.L822 - .Lrtx813) / 4
	.byte	(.L809 - .Lrtx813) / 4
	.byte	(.L823 - .Lrtx813) / 4
	.byte	(.L824 - .Lrtx813) / 4
	.byte	(.L825 - .Lrtx813) / 4
	.byte	(.L809 - .Lrtx813) / 4
	.byte	(.L809 - .Lrtx813) / 4
	.byte	(.L826 - .Lrtx813) / 4
	.text
	.p2align 3
.L826:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	USERDEC_Init
	b	.L809
	.p2align 3
.L825:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	VP9DEC_Init
	b	.L809
	.p2align 3
.L824:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	HEVCDEC_Init
	b	.L809
	.p2align 3
.L823:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	MVC_DEC_Init
	b	.L809
	.p2align 3
.L822:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	VP8DEC_Init
	b	.L809
	.p2align 3
.L821:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	VP6DEC_Init
	b	.L809
	.p2align 3
.L820:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	REAL9DEC_Init
	b	.L809
	.p2align 3
.L819:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	REAL8DEC_Init
	b	.L809
	.p2align 3
.L818:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	AVSDEC_Init
	b	.L809
	.p2align 3
.L817:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	DIVX3DEC_Init
	b	.L809
	.p2align 3
.L816:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	MPEG2DEC_Init
	b	.L809
	.p2align 3
.L815:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	MPEG4DEC_Init
	b	.L809
	.p2align 3
.L814:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	VC1DEC_Init
	b	.L809
	.p2align 3
.L812:
	add	x0, x1, 311296
	add	x1, x1, 640
	add	x0, x0, 1624
	bl	H264DEC_Init
	b	.L809
	.p2align 3
.L827:
	ldr	x2, .LC531
	mov	w3, 4684
	ldr	x4, .LC530
	mov	w0, 0
	ldr	x1, .LC532
	add	x2, x2, 184
	bl	dprint_vfmw
	b	.L809
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
	.xword	.L813
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
	tbnz	w0, #31, .L830
	ldr	w0, [x19, 12]
	cmp	w0, 31
	ble	.L830
	ldr	w0, [x19, 16]
	cmp	w0, 31
	ble	.L830
	ldr	w1, [x19, 56]
	mov	w0, 262143
	cmp	w1, w0
	ble	.L830
	ldr	w0, [x19, 44]
	cmp	w0, 1
	beq	.L836
	cmp	w0, 2
	mov	w0, 0
	bne	.L832
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L830
	ldr	w0, [x19, 24]
	cmp	w0, wzr
	ble	.L830
.L835:
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L830
	ldr	w0, [x19, 32]
	cmp	w0, wzr
	bgt	.L837
.L830:
	ldr	x1, .LC535
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, -1
.L832:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L837:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L836:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	bgt	.L835
	b	.L830
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
	cbz	w0, .L840
	mov	w4, 17
	add	w0, w5, 1
	cmp	w0, w4
	csel	w4, w0, w4, le
.L840:
	ldr	x1, .LC536
	sub	w0, w21, #27
	mov	w7, -2
	cmp	w0, 5
	csinv	w7, w7, wzr, ls
	ldr	x8, [x1, 128]
	cbz	x8, .L844
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
	cbnz	w0, .L844
	cmp	w21, 26
	beq	.L854
	mov	w1, 31688
	movk	w1, 0xc, lsl 16
	mov	w2, w1
.L845:
	ldr	w0, [x22, 2328]
	add	w3, w0, 16
	str	w3, [x20]
	ldr	w3, [x19, 192]
	cmp	w3, 1
	beq	.L846
	add	w0, w0, 307200
	add	w0, w0, 2576
	str	w0, [x20]
	ldr	w0, [x19, 56]
	add	w0, w0, 32768
	str	w0, [x20, 4]
.L847:
	str	w2, [x20, 8]
	ldr	w0, [x19, 44]
	cbnz	w0, .L855
	mov	w0, 61264
	movk	w0, 0x9, lsl 16
.L848:
	add	sp, x29, 0
	add	w1, w0, w1
	str	w1, [x20, 8]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L855:
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
	beq	.L850
	mov	w0, 61264
	movk	w0, 0x9, lsl 16
	cmp	w2, w0
	csel	w0, w2, w0, cs
	b	.L848
	.p2align 3
.L844:
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
.L846:
	ldr	w0, [x19, 56]
	add	w0, w0, 339968
	add	w0, w0, 2576
	str	w0, [x20, 4]
	b	.L847
	.p2align 3
.L854:
	mov	w1, 17864
	movk	w1, 0xb2, lsl 16
	mov	w2, w1
	b	.L845
	.p2align 3
.L850:
	mov	w5, 3992
	mov	w3, 2240
	and	x2, x2, 4294967295
	mov	w0, 61264
	smaddl	x4, w7, w5, x4
	movk	w0, 0x9, lsl 16
	smaddl	x6, w6, w3, x4
	cmp	x6, x2
	csel	x2, x6, x2, cs
	cmp	w2, w0
	csel	w0, w2, w0, cs
	b	.L848
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
	beq	.L857
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
	blt	.L864
	str	w0, [x19, 36]
	str	w1, [x19, 60]
.L857:
	mov	x0, x19
	bl	VCTRL_VarifyOption
	cbnz	w0, .L860
	mov	x2, x22
	mov	x1, x19
	mov	w0, w21
	bl	VCTRL_GetMemSize_onDecode
.L859:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L860:
	mov	w0, -1
	b	.L859
	.p2align 3
.L864:
	ldr	x1, .LC543
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, -1
	b	.L859
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
	cbz	w0, .L890
	ldr	w0, [x19, 112]
	cmp	w0, wzr
	cset	w21, ne
.L866:
	ldr	w20, [x19, 24]
	ldr	w22, [x19, 16]
	ldr	x23, [x19, 8]
	cbz	w20, .L867
	ldr	x0, .LC544
	ldr	x1, [x0, 120]
	cbz	x1, .L919
	mov	w0, 0
	blr	x1
	cbz	w21, .L870
.L871:
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
.L867:
	mov	w2, w20
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 88]
	ldr	w22, [x19, 80]
	ldr	x23, [x19, 72]
	cbz	w20, .L873
	ldr	x0, .LC544
	ldr	x1, [x0, 120]
	cbz	x1, .L920
	mov	w0, 0
	blr	x1
	cbz	w21, .L876
.L877:
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 64
	ldr	x3, [x3, 96]
	blr	x3
.L873:
	mov	w2, w20
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 56]
	ldr	w22, [x19, 48]
	ldr	x23, [x19, 40]
	cbnz	w20, .L921
.L879:
	mov	x1, x23
	mov	w2, w20
	mov	w0, w22
	bl	MEM_DelMemRecord
	bl	SM_InstInit
	ldr	w21, [x19, 144]
	ldr	w22, [x19, 136]
	ldr	x23, [x19, 128]
	cbnz	w21, .L922
.L882:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	add	x20, x19, 216
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 240]
	ldr	w22, [x19, 232]
	ldr	x23, [x19, 224]
	cbnz	w21, .L923
.L883:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 208]
	ldr	w22, [x19, 200]
	ldr	x23, [x19, 192]
	cbnz	w21, .L924
.L884:
	mov	w2, w21
	mov	x1, x23
	mov	w0, w22
	add	x20, x19, 152
	bl	MEM_DelMemRecord
	ldr	w21, [x19, 176]
	ldr	w22, [x19, 168]
	ldr	x23, [x19, 160]
	cbnz	w21, .L925
.L885:
	mov	w2, w21
	mov	w0, w22
	mov	x1, x23
	add	x19, x19, 248
	bl	MEM_DelMemRecord
	ldr	w20, [x19, 24]
	ldr	w21, [x19, 16]
	ldr	x22, [x19, 8]
	cbnz	w20, .L926
	mov	w2, w20
	mov	x1, x22
	mov	w0, w21
	bl	MEM_DelMemRecord
	ldr	x19, .LC547
	ldr	w0, [x19, 584]
	cmp	w0, 1
	beq	.L927
.L887:
	ldr	w0, [x19, 588]
	cmp	w0, 1
	beq	.L928
.L888:
	ldr	w0, [x19, 592]
	add	x19, x19, 256
	cmp	w0, 1
	beq	.L929
.L889:
	bl	HEVCDEC_ReleaseHevcGlbMem
	ldr	x23, [sp, 48]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L921:
	mov	w0, 0
	bl	SM_CloseSCDDrv
	cbz	w21, .L880
.L881:
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, x2
	ldr	x3, [x3, 96]
	blr	x3
	b	.L879
	.p2align 3
.L922:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 120
	ldr	x3, [x3, 96]
	blr	x3
	b	.L882
	.p2align 3
.L926:
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
	bne	.L887
.L927:
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
	bne	.L888
	.p2align 2
.L928:
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
	bne	.L889
.L929:
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
.L925:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	b	.L885
	.p2align 3
.L924:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	add	x0, x19, 184
	ldr	x3, [x3, 96]
	blr	x3
	b	.L884
	.p2align 3
.L923:
	mov	x1, x23
	mov	w0, w22
	bl	MEM_UnmapRegisterAddr
	ldr	x3, .LC545
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
	ldr	x3, [x3, 96]
	blr	x3
	b	.L883
	.p2align 3
.L919:
	ldr	x1, .LC546
	mov	w2, 5178
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w21, .L871
	.p2align 2
.L870:
	ldr	w0, [x19, 16]
	ldr	x1, [x19, 8]
	bl	MEM_ReleaseMemBlock
	b	.L871
	.p2align 3
.L920:
	ldr	x1, .LC546
	mov	w2, 5198
	mov	w0, 0
	bl	dprint_vfmw
	cbnz	w21, .L877
	.p2align 2
.L876:
	ldr	w0, [x19, 80]
	ldr	x1, [x19, 72]
	bl	MEM_ReleaseMemBlock
	b	.L877
	.p2align 3
.L890:
	mov	w21, 0
	b	.L866
	.p2align 3
.L880:
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_ReleaseMemBlock
	b	.L881
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
	cbnz	w0, .L931
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
	cbz	w0, .L964
	mov	w2, 53248
	ldr	x1, .LC551
	movk	w2, 0xf8c3, lsl 16
.L957:
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, .LC552
	mov	x2, 32
	mov	w1, 0
	mov	x0, x20
.L958:
	ldr	x3, [x3, 96]
	blr	x3
	mov	x0, x19
	bl	CloseDrivers
	mov	w0, -1
.L934:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L964:
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
	cbnz	w0, .L935
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
	cbz	x0, .L937
	blr	x0
	cmp	w0, wzr
	mov	w2, w0
	ble	.L937
	mov	w21, 3
	mov	w4, 0
	mov	x3, x19
	mov	w1, 0
	add	x0, x29, 96
	str	w21, [x19, 28]
	bl	MEM_AllocMemBlock
	cbnz	w0, .L938
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
	cbz	x1, .L939
	add	x0, x29, 120
	blr	x1
	cbnz	w0, .L939
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
	mov	w2, 16384
	mov	w1, 0
	add	x0, x29, 96
	bl	MEM_AllocMemBlock
	cbnz	w0, .L940
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
	cbnz	w0, .L965
	ldr	w2, [x19, 56]
	ldr	x1, [x19, 40]
	ldr	w0, [x19, 48]
	bl	MEM_AddMemRecord
	ldr	w0, [x19, 48]
	mov	w2, 0
	ldr	w1, [x19, 56]
	bl	SM_OpenSCDDrv
	cbnz	w0, .L943
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
	cbnz	w0, .L966
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
	cbnz	w0, .L967
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
	cbnz	w0, .L968
	str	w27, [x22, 336]
	bl	HEVCDEC_AllocHevcGlbMem
	cbz	w0, .L934
	ldr	x1, .LC576
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L934
	.p2align 3
.L931:
	ldr	x1, .LC551
	mov	w2, -121438208
	b	.L957
	.p2align 3
.L937:
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
	b	.L934
.L935:
	ldr	x1, .LC551
	mov	w2, 49152
	movk	w2, 0xf8c3, lsl 16
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x3, .LC552
	mov	x2, 32
	mov	w1, 0
	mov	x0, x21
	b	.L958
.L939:
	ldr	x1, .LC560
.L959:
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
	b	.L934
.L966:
	ldr	x1, .LC571
	mov	w2, 127
.L960:
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
	b	.L934
.L967:
	ldr	x1, .LC571
	mov	w2, 136
	b	.L960
.L968:
	ldr	x1, .LC571
	mov	w2, 181
	b	.L960
.L943:
	ldr	x1, .LC569
	mov	w2, 0
	b	.L960
.L965:
	ldr	x1, .LC567
	mov	w2, 0
	b	.L960
.L938:
	ldr	x1, .LC558
	b	.L959
.L940:
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
	b	.L934
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
	cbz	x23, .L1002
	ldr	x20, .LC583
	mov	x2, 8
	mov	w1, 0
	add	x0, x29, 64
	ldr	x3, [x20, 96]
	blr	x3
	ldr	x22, .LC584
	ldr	w19, [x22, 256]
	cbnz	w19, .L1001
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
	cbz	x0, .L973
	ldr	x1, .LC589
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L993
	ldr	x1, .LC591
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1003
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
	bhi	.L978
.L1008:
	mov	w0, 5000
	mov	w1, -5000
	cmp	w2, w0
	csel	w0, w2, w0, le
	cmp	w0, w1
	csel	w0, w0, w1, ge
.L974:
	str	w0, [x21, 3560]
.L976:
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
	cbz	x0, .L979
	ldr	x1, .LC589
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L980
	ldr	x1, .LC591
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1004
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
	bhi	.L984
.L1009:
	mov	w19, 5000
	mov	w0, -5000
	cmp	w2, w19
	csel	w19, w2, w19, le
	cmp	w19, w0
	csel	w19, w19, w0, ge
.L980:
	str	w19, [x21, 3564]
.L982:
	ldr	x24, .LC600
	str	xzr, [x29, 72]
	ldr	w0, [x24, 248]
	cbz	w0, .L985
	ldr	x2, .LC601
	and	w4, w0, 1
	ubfx	x3, x0, 1, 1
	ubfx	x1, x0, 2, 1
	strb	w4, [x24, 252]
	ubfx	x0, x0, 3, 1
	strb	w3, [x2, 96]
	strb	w1, [x24, 253]
	strb	w0, [x24, 254]
.L986:
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
.L990:
	str	w2, [x0], 4
	cmp	x1, x0
	bne	.L990
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
	cbnz	w0, .L1001
	ldr	x2, [x20, 248]
	mov	w1, 1
	blr	x2
	ldr	x2, .LC608
	add	x0, x22, 272
	ldr	x1, .LC610
	ldr	x3, [x20, 400]
	blr	x3
	cbnz	w0, .L1005
	mov	w1, 1
	str	w1, [x22, 256]
.L971:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L985:
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
	cbz	x0, .L986
	ldr	x1, .LC589
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1006
	ldr	x1, .LC591
	add	x0, x29, 72
	ldr	x2, [x20, 184]
	blr	x2
	cbz	x0, .L1007
	ldr	x3, [x20, 168]
	mov	x1, 0
	mov	w2, 0
	blr	x3
	mov	w1, w0
	str	w0, [x24, 248]
.L988:
	ldr	x2, .LC601
	and	w4, w1, 1
	ubfx	x3, x1, 1, 1
	ubfx	x0, x1, 2, 1
	strb	w4, [x24, 252]
	ubfx	x1, x1, 3, 1
	strb	w3, [x2, 96]
	strb	w0, [x24, 253]
	strb	w1, [x24, 254]
	b	.L986
.L973:
	ldr	w2, [x21, 3560]
	mov	w1, 10000
	add	w0, w2, 4096
	add	w0, w0, 904
	cmp	w0, w1
	bls	.L1008
.L978:
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
	b	.L974
.L979:
	ldr	w2, [x21, 3564]
	mov	w1, 10000
	add	w0, w2, 4096
	add	w0, w0, 904
	cmp	w0, w1
	bls	.L1009
.L984:
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
	b	.L980
.L993:
	mov	w0, 0
	b	.L974
.L1006:
	ldr	w1, [x24, 248]
	b	.L988
.L1005:
	mov	x0, x19
	bl	CloseDrivers
.L1001:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	mov	w0, -1
	ldp	x29, x30, [sp], 80
	ret
.L1004:
	ldr	x2, .LC581
	mov	w3, 6026
	ldr	x1, .LC593
	mov	w0, 22
	add	x2, x2, 240
	bl	dprint_vfmw
	b	.L982
.L1003:
	ldr	x2, .LC581
	mov	w3, 5984
	ldr	x1, .LC593
	mov	w0, 22
	add	x2, x2, 216
	bl	dprint_vfmw
	b	.L976
.L1007:
	ldr	x2, .LC581
	mov	w3, 6077
	ldr	x1, .LC593
	mov	w0, 22
	add	x2, x2, 264
	bl	dprint_vfmw
	b	.L986
.L1002:
	ldr	x2, .LC581
	mov	w3, 938
	ldr	x4, .LC580
	mov	w0, 0
	ldr	x1, .LC582
	add	x2, x2, 200
	bl	dprint_vfmw
	mov	w0, -1
	b	.L971
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
	beq	.L1015
	cmp	w19, w22
	mov	w19, w21
	blt	.L1016
.L1012:
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
.L1016:
	ldr	x1, .LC619
	mov	w0, 30
	mov	w19, 3
	bl	dprint_vfmw
	b	.L1012
	.p2align 3
.L1015:
	cmp	w20, w22
	mov	w19, w21
	ble	.L1012
	ldr	x1, .LC617
	mov	w0, 30
	mov	w19, 0
	bl	dprint_vfmw
	b	.L1012
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
	b	.L1020
	.p2align 3
.L1018:
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1026
.L1020:
	ldr	x2, [x3, x0, lsl 3]
	add	x1, x2, 311296
	add	x1, x1, 1624
	cbz	x2, .L1018
	cmp	x19, x1
	bne	.L1018
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1026:
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
.L1032:
	ldr	x4, [x6, x5, lsl 3]
	mov	w0, w5
	cbz	x4, .L1028
	add	x4, x4, 307200
	add	x1, x4, 1560
	add	x4, x4, 3864
	.p2align 2
.L1031:
	ldr	w2, [x1]
	cmp	w2, w19
	bhi	.L1029
	ldr	w3, [x1, -20]
	add	w2, w2, w3
	cmp	w19, w2
	bcc	.L1030
.L1029:
	add	x1, x1, 72
	cmp	x1, x4
	bne	.L1031
.L1028:
	add	x5, x5, 1
	cmp	x5, 32
	bne	.L1032
	mov	w0, -1
.L1030:
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
	beq	.L1069
	cmp	w2, 6
	sub	w0, w2, #2
	ccmp	w2, 18, 4, ne
	ccmp	w0, 1, 0, ne
	bls	.L1041
.L1042:
	ldr	x2, [x19, 40]
	cmn	x2, #1
	beq	.L1070
	str	x2, [x4, 704]
.L1052:
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
	ldrb	w5, [x19, 19]
	strb	w5, [x4, 696]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1069:
	add	x0, x4, 311296
	ldr	x0, [x0, 1624]
	ldrsb	w0, [x0, 604]
	cmp	w0, 1
	bne	.L1042
.L1041:
	add	x3, x19, 8
	add	x1, x4, 1240
	mov	w0, w20
	bl	IsNewpicSeg
	cbz	w0, .L1071
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	beq	.L1048
.L1047:
	ldr	x1, [x19, 40]
	cmn	x1, #1
	beq	.L1049
.L1068:
	str	x1, [x0, 712]
.L1049:
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
.L1048:
	ldr	x2, [x0, 720]
	mov	w0, 29
	ldr	x1, .LC628
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1071:
	ldr	x0, [x21, w20, sxtw 3]
	ldr	w1, [x0, 52]
	cmp	w1, 3
	ldr	x1, [x0, 712]
	beq	.L1067
	cmn	x1, #1
	beq	.L1045
.L1067:
	str	x1, [x0, 704]
.L1045:
	ldr	x3, [x0, 728]
	mov	x2, -1
	ldr	x1, [x0, 744]
	str	x2, [x0, 712]
	str	x3, [x0, 720]
	str	x1, [x0, 736]
	cbnz	x1, .L1046
	ldr	x1, [x19, 64]
	str	x1, [x0, 736]
.L1046:
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
	bne	.L1047
	ldr	x1, [x19, 40]
	b	.L1068
	.p2align 3
.L1070:
	ldr	x2, [x4, 704]
	b	.L1052
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
	bhi	.L1073
	ldr	x1, .LC632
	ldr	w1, [x1, 2064]
	tbz	x1, 0, .L1074
.L1073:
	and	w1, w0, -17
	cmp	w1, 4
	ccmp	w0, 14, 4, ne
	beq	.L1074
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbnz	x0, .L1076
.L1074:
	mov	w0, 0
.L1075:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1076:
	mov	w0, -2
	b	.L1075
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
	bhi	.L1117
	ldr	x21, .LC636
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1118
	ldr	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1119
	ldr	w1, [x0, 24]
	cbnz	w1, .L1120
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
	bls	.L1089
	str	w2, [x1, w19, sxtw 2]
	bl	DecChanCheckDecParam
	cmn	w0, #2
	mov	w20, w0
	beq	.L1121
	mov	w0, w19
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	bne	.L1099
	mov	w20, w0
.L1100:
	ldr	x1, [x21, w19, sxtw 3]
	add	x0, x1, 278528
	ldr	w3, [x0, 2152]
	cmp	w3, 1
	beq	.L1122
	cmp	w3, 3
	beq	.L1123
	add	x24, x1, 784
	ldrb	w0, [x24, 1]
	cbnz	w0, .L1093
	ldr	w0, [x1, 1600]
	cbz	w0, .L1124
.L1093:
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
	bne	.L1125
.L1095:
	ldr	x1, [x21, w19, sxtw 3]
	mov	x0, x24
	add	x2, x1, 311296
	ldr	w1, [x1, 632]
	add	x2, x2, 1624
	bl	DecodeStream
	mov	w0, 4
	bl	CHECK_REC_POS_ENABLE
	cbnz	w0, .L1096
.L1097:
	mov	w20, 0
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1089:
	bl	DecChanCheckDecParam
	cmn	w0, #2
	mov	w20, w0
	bne	.L1126
.L1106:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1126:
	mov	w0, w19
	mov	w20, -3
	bl	VCTRL_GetImageBuffer
	cmp	w0, 1
	bne	.L1106
	mov	w20, 0
	b	.L1100
	.p2align 3
.L1121:
	ldr	x1, .LC645
	mov	w2, w19
	mov	w0, 23
	bl	dprint_vfmw
	b	.L1106
	.p2align 3
.L1096:
	ldr	x0, [x23]
	add	x22, x22, 520
	blr	x0
	mov	w1, w0
	ldr	x2, .LC656
	ldr	w0, [x22, w19, sxtw 2]
	ldr	w2, [x2]
	sub	w0, w1, w0
	cmp	w0, w2
	bls	.L1097
	mov	w0, w19
	str	w1, [x22, w19, sxtw 2]
	bl	VCTRL_GetDecParam
	cbz	x0, .L1097
	ldr	x0, .LC634
	lsl	w2, w19, 24
	add	w2, w2, 262144
	mov	w1, 5740
	add	x0, x0, 296
	mov	w20, 0
	bl	DBG_AddTrace
	b	.L1106
.L1122:
	ldr	x1, .LC649
	mov	w0, 31
	mov	w20, -3
	bl	dprint_vfmw
	b	.L1106
	.p2align 3
.L1099:
	ldr	x1, .LC647
	mov	w2, w19
	mov	w0, 23
	mov	w20, -3
	bl	dprint_vfmw
	b	.L1106
	.p2align 3
.L1119:
	ldr	x2, .LC634
	mov	w3, 5640
	ldr	x4, .LC638
	mov	w0, 0
	ldr	x1, .LC635
	add	x2, x2, 280
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1106
	.p2align 3
.L1120:
	ldr	x2, .LC634
	mov	w3, 5641
	ldr	x4, .LC640
	mov	w0, 0
	ldr	x1, .LC635
	add	x2, x2, 280
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1106
	.p2align 3
.L1124:
	add	x1, x1, 792
	mov	w0, w19
	bl	SM_ReadSegStream
	cbz	w0, .L1093
	cmp	w20, 1
	beq	.L1127
.L1094:
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 1
	mov	w20, -4
	str	w1, [x0, 472]
	b	.L1106
	.p2align 3
.L1117:
	ldr	x2, .LC634
	mov	w3, 5638
	ldr	x4, .LC633
	mov	w0, 0
	ldr	x1, .LC635
	add	x2, x2, 280
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1106
	.p2align 3
.L1125:
	ldr	x0, .LC634
	lsl	w2, w19, 24
	add	w2, w2, 196608
	mov	w1, 5722
	add	x0, x0, 296
	bl	DBG_AddTrace
	b	.L1095
.L1118:
	ldr	x2, .LC634
	mov	w3, 5639
	ldr	x4, .LC637
	mov	w20, -1
	ldr	x1, .LC635
	add	x2, x2, 280
	bl	dprint_vfmw
	b	.L1106
.L1123:
	ldr	w2, [x1, 1552]
	mov	w0, 31
	ldr	x1, .LC651
	mov	w20, -1
	bl	dprint_vfmw
	b	.L1106
.L1127:
	ldr	x1, .LC653
	mov	w2, w19
	mov	w0, 23
	bl	dprint_vfmw
	b	.L1094
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
	b	.L1131
	.p2align 3
.L1159:
	ldr	w1, [x1, 20]
	str	w1, [x2, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1158
.L1131:
	ldr	x1, [x21, x0, lsl 3]
	add	x2, x23, 648
	cbnz	x1, .L1159
	add	x1, x23, 648
	str	wzr, [x1, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L1131
.L1158:
	ldr	x24, .LC661
	mov	w20, -1
	.p2align 2
.L1132:
	ldr	w3, [x23, 648]
	add	x1, x23, 652
	mov	w0, 0
	mov	w19, 0
	.p2align 2
.L1133:
	add	w0, w0, 1
	cmp	w0, 32
	beq	.L1160
.L1135:
	ldr	w2, [x1]
	add	x1, x1, 4
	cmp	w3, w2
	bge	.L1133
	mov	w19, w0
	add	w0, w0, 1
	cmp	w0, 32
	mov	w3, w2
	bne	.L1135
.L1160:
	add	x2, x23, 648
	add	x0, x21, 256
	add	w1, w19, 1
	cmp	w3, wzr
	sxtw	x25, w19
	str	wzr, [x2, w19, sxtw 2]
	str	w1, [x0, 28]
	ble	.L1136
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1132
	ldr	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1132
	ldr	w1, [x0, 76]
	cmp	w1, wzr
	ble	.L1138
	ldr	w0, [x0, 80]
	cbz	w0, .L1161
.L1138:
	mov	w22, 500
	b	.L1146
	.p2align 3
.L1141:
	ldr	x0, [x21, x25, lsl 3]
	cbnz	w20, .L1144
	ldr	w1, [x0, 1632]
	cmp	w1, 1
	beq	.L1144
	subs	w22, w22, #1
	beq	.L1132
.L1146:
	mov	w0, w19
	bl	DecChanSyntax
	cmn	w0, #1
	mov	w20, w0
	bne	.L1141
	ldr	x4, [x23, 256]
	cbz	x4, .L1142
	mov	w3, 0
	mov	x2, 0
	mov	w1, 102
	mov	w0, w19
	blr	x4
.L1142:
	mov	w0, w20
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 112
	ret
.L1144:
	str	wzr, [x0, 1632]
	b	.L1132
.L1161:
	add	x1, x29, 88
	mov	w0, w19
	bl	SM_GetInfo
	cbnz	w0, .L1162
.L1139:
	ldr	x20, [x21, x25, lsl 3]
	ldr	w1, [x29, 100]
	ldr	w2, [x20, 76]
	ldr	w0, [x20, 648]
	bl	GetNextDecodeMode
	str	w0, [x20, 648]
	ldr	x1, [x21, x25, lsl 3]
	ldr	w0, [x1, 648]
	cbz	w0, .L1140
	str	wzr, [x1, 640]
	str	wzr, [x1, 644]
	b	.L1138
.L1136:
	str	wzr, [x0, 28]
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 112
	ret
.L1140:
	ldr	w0, [x1, 72]
	str	w0, [x1, 640]
	str	w0, [x1, 644]
	b	.L1138
.L1162:
	ldr	x3, [x24, 96]
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 88
	blr	x3
	b	.L1139
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
	beq	.L1172
.L1164:
	ldr	w0, [x20, 1124]
	mov	w1, 100
	str	w1, [x20, 280]
	cmp	w0, wzr
	ldr	x21, .LC665
	ble	.L1165
	ldr	x1, [x21, 240]
	blr	x1
.L1165:
	ldr	x1, [x21, 24]
	mov	w0, 0
	mov	w22, 0
	blr	x1
	bl	SM_Wakeup
	ldr	w0, [x20, 1120]
	mov	w1, 101
	str	w1, [x20, 280]
	cbz	w0, .L1173
.L1166:
	mov	w0, 102
	mov	w19, 0
	str	w0, [x20, 280]
	bl	VDMDRV_WakeUpVdm
	.p2align 2
.L1167:
	mov	w0, w19
	mov	w1, 0
	add	w19, w19, 1
	bl	DeleteRawPacketInBuffer
	cmp	w19, 32
	bne	.L1167
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
.L1173:
	bl	DecSyntax
	mov	w22, w0
	b	.L1166
.L1172:
	mov	w0, 11
	bl	VCTRL_RecordPosTime
	strb	wzr, [x20, 2816]
	b	.L1164
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
.L1175:
.L1182:
	mov	x1, x25
	mov	w0, 2
	str	wzr, [x20, 280]
	bl	dprint_vfmw
	str	w21, [x20, 260]
	ldr	w0, [x20, 264]
	cmp	w0, 2
	bne	.L1197
	b	.L1180
	.p2align 3
.L1199:
	str	w21, [x20, 280]
	bl	VCTRL_RunProcess
	mov	x1, x22
	mov	w0, 22
	bl	dprint_vfmw
	ldr	w0, [x20, 264]
	cmp	w0, 2
	beq	.L1180
.L1197:
	cmp	w0, 3
	bne	.L1199
.L1178:
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
.L1180:
	mov	w2, 4
	mov	x1, x26
	mov	w0, 2
	str	w2, [x20, 280]
	mov	w27, 5
	bl	dprint_vfmw
	mov	w0, 1
	str	w0, [x20, 260]
	b	.L1177
	.p2align 3
.L1200:
	ldr	x1, [x24, 240]
	blr	x1
.L1177:
	mov	x1, x23
	mov	w0, 22
	str	w27, [x20, 280]
	bl	dprint_vfmw
	ldr	w1, [x20, 264]
	mov	w0, 10
	cmp	w1, 1
	beq	.L1182
	cmp	w1, 3
	bne	.L1200
	b	.L1178
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
	cbz	x0, .L1219
	ldr	w1, [x0, 632]
	cmp	w1, 20
	bls	.L1220
.L1219:
	mov	x0, 0
.L1202:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1220:
	ldr	x2, .LC680
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx1204
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx1204:
	.section	.rodata
	.align	0
	.align	2
.L1204:
	.byte	(.L1217 - .Lrtx1204) / 4
	.byte	(.L1205 - .Lrtx1204) / 4
	.byte	(.L1206 - .Lrtx1204) / 4
	.byte	(.L1207 - .Lrtx1204) / 4
	.byte	(.L1219 - .Lrtx1204) / 4
	.byte	(.L1208 - .Lrtx1204) / 4
	.byte	(.L1209 - .Lrtx1204) / 4
	.byte	(.L1219 - .Lrtx1204) / 4
	.byte	(.L1210 - .Lrtx1204) / 4
	.byte	(.L1211 - .Lrtx1204) / 4
	.byte	(.L1212 - .Lrtx1204) / 4
	.byte	(.L1212 - .Lrtx1204) / 4
	.byte	(.L1212 - .Lrtx1204) / 4
	.byte	(.L1213 - .Lrtx1204) / 4
	.byte	(.L1219 - .Lrtx1204) / 4
	.byte	(.L1214 - .Lrtx1204) / 4
	.byte	(.L1215 - .Lrtx1204) / 4
	.byte	(.L1216 - .Lrtx1204) / 4
	.byte	(.L1219 - .Lrtx1204) / 4
	.byte	(.L1219 - .Lrtx1204) / 4
	.byte	(.L1217 - .Lrtx1204) / 4
	.text
	.p2align 3
.L1217:
	add	x0, x0, 311296
	ldr	x19, [sp, 16]
	add	x0, x0, 1632
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1215:
	add	x0, x0, 315392
	add	x0, x0, 3560
	b	.L1202
	.p2align 3
.L1214:
	add	x0, x0, 311296
	add	x0, x0, 2536
	b	.L1202
	.p2align 3
.L1213:
	add	x0, x0, 319488
	add	x0, x0, 1664
	b	.L1202
	.p2align 3
.L1212:
	add	x0, x0, 323584
	add	x0, x0, 2096
	b	.L1202
	.p2align 3
.L1216:
	add	x0, x0, 585728
	add	x0, x0, 3040
	b	.L1202
	.p2align 3
.L1205:
	add	x0, x0, 364544
	add	x0, x0, 1912
	b	.L1202
	.p2align 3
.L1207:
	add	x0, x0, 401408
	add	x0, x0, 304
	b	.L1202
	.p2align 3
.L1206:
	add	x0, x0, 331776
	add	x0, x0, 3864
	b	.L1202
	.p2align 3
.L1211:
	add	x0, x0, 364544
	add	x0, x0, 3320
	b	.L1202
	.p2align 3
.L1210:
	add	x0, x0, 364544
	add	x0, x0, 3344
	b	.L1202
	.p2align 3
.L1209:
	add	x0, x0, 327680
	add	x0, x0, 1504
	b	.L1202
	.p2align 3
.L1208:
	add	x0, x0, 352256
	add	x0, x0, 3288
	b	.L1202
	.size	VCTRL_GetChanVoQue, .-VCTRL_GetChanVoQue
	.align	3
.LC679:
	.xword	.LANCHOR1
	.align	3
.LC680:
	.xword	.L1204
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
	bhi	.L1237
	mov	w0, w19
	bl	VCTRL_GetChanVoQue
	mov	x20, x0
	cbz	x0, .L1231
	add	x2, x29, 48
	add	x1, x29, 40
	str	wzr, [x29, 40]
	str	wzr, [x2, -4]!
	bl	GetQueueImgNum
	ldr	w2, [x29, 40]
	mov	w0, -1
	cbz	w2, .L1223
	cmp	w2, 32
	bhi	.L1238
.L1225:
	ldr	x1, .LC686
	ldrh	w0, [x20, 4]
	ldr	x5, [x1, w19, sxtw 3]
	and	x0, x0, 63
	add	x0, x0, 2
	add	x6, x5, 311296
	ldr	x4, [x20, x0, lsl 3]
	ldr	w3, [x6, 1544]
	cmp	w3, 32
	bhi	.L1226
	mov	w1, 1
	b	.L1228
	.p2align 3
.L1229:
	ldrh	w0, [x20, 4]
	cmp	w3, 33
	add	w0, w0, w1
	add	w1, w1, 1
	and	x0, x0, 63
	add	x0, x0, 2
	ldr	x4, [x20, x0, lsl 3]
	beq	.L1226
.L1228:
	ubfiz	x0, x3, 4, 32
	ldr	w4, [x4, 20]
	add	x0, x5, x0
	add	w3, w3, 1
	add	x0, x0, 311296
	cmp	w1, w2
	str	wzr, [x0, 1016]
	str	w4, [x0, 1020]
	str	xzr, [x0, 1024]
	str	w3, [x6, 1544]
	bcc	.L1229
	mov	w0, 0
.L1223:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1226:
	ldr	x1, .LC688
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L1223
	.p2align 3
.L1238:
	ldr	x1, .LC685
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x29, 40]
	cbnz	w2, .L1225
	mov	w0, 0
	b	.L1223
.L1231:
	mov	w0, -1
	b	.L1223
.L1237:
	ldr	x2, .LC682
	mov	w3, 3086
	ldr	x4, .LC681
	mov	w0, 0
	ldr	x1, .LC683
	add	x2, x2, 312
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1223
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
	bhi	.L1256
	cbz	x19, .L1257
	mov	w0, w22
	bl	VCTRL_GetChanVoQue
	mov	x20, x0
	cbz	x0, .L1249
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
	cbnz	w2, .L1258
	ldr	x6, .LC696
	ldr	x4, [x6, w22, sxtw 3]
	add	x0, x4, 311296
	ldr	w0, [x0, 1544]
	cbz	w0, .L1247
	mov	w2, 0
	sxtw	x0, w22
	.p2align 2
.L1248:
	sxtw	x3, w2
	add	w2, w2, 1
	add	x1, x3, 16384
	lsl	x3, x3, 4
	add	x1, x1, 3135
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
	add	x1, x4, 311296
	ldr	w1, [x1, 1544]
	cmp	w2, w1
	bcc	.L1248
	str	w1, [x19, 528]
	b	.L1247
	.p2align 3
.L1258:
	cmp	w2, 32
	bhi	.L1259
.L1244:
	mov	w0, 0
	.p2align 2
.L1246:
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
	bhi	.L1246
	uxth	w1, w2
.L1245:
	ldrh	w0, [x20, 4]
	add	w0, w1, w0
	and	w0, w0, 63
	strh	w0, [x20, 4]
	str	w2, [x19, 528]
.L1247:
	ldr	x1, [x21, 32]
	mov	w0, 4
	blr	x1
	mov	w0, 0
.L1241:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1259:
	ldr	x1, .LC695
	mov	w3, 32
	mov	w0, 1
	bl	dprint_vfmw
	ldr	w2, [x29, 72]
	cbnz	w2, .L1244
	mov	w2, 0
	mov	w1, 0
	b	.L1245
.L1249:
	mov	w0, -1
	b	.L1241
.L1256:
	ldr	x2, .LC690
	mov	w3, 3162
	ldr	x4, .LC689
	mov	w0, 0
	ldr	x1, .LC691
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1241
.L1257:
	ldr	x2, .LC690
	mov	w3, 3163
	ldr	x4, .LC693
	mov	w0, 0
	ldr	x1, .LC691
	add	x2, x2, 336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1241
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
	cbz	x20, .L1273
	cbz	x21, .L1274
	cbz	x22, .L1275
	cmp	w19, 31
	bhi	.L1276
	ldr	x23, .LC706
	ldr	x0, [x23, w19, sxtw 3]
	cbz	x0, .L1277
	mov	w0, w19
	bl	VCTRL_GetChanVoQue
	cbz	x0, .L1267
	mov	x2, x22
	mov	x1, x21
	bl	GetQueueImgNum
	ldr	x0, [x23, w19, sxtw 3]
	ldr	w3, [x0, 632]
	cbz	w3, .L1278
	cmp	w3, 16
	beq	.L1279
	cmp	w3, 17
	beq	.L1280
	cmp	w3, 15
	beq	.L1281
	cmp	w3, 18
	beq	.L1282
	mov	w0, 2
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1267:
	str	wzr, [x22]
	str	wzr, [x21]
	str	wzr, [x20]
.L1260:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1276:
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
.L1278:
	add	x0, x0, 339968
	ldr	w0, [x0, 1232]
	str	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1279:
	add	x0, x0, 315392
	ldr	w0, [x0, 296]
	str	w0, [x20]
	b	.L1260
	.p2align 3
.L1280:
	mov	w0, 9
	str	w0, [x20]
	b	.L1260
	.p2align 3
.L1273:
	ldr	x2, .LC699
	mov	w3, 5846
	ldr	x4, .LC698
	mov	w0, 0
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1260
	.p2align 3
.L1274:
	ldr	x2, .LC699
	mov	w3, 5847
	ldr	x4, .LC702
	mov	w0, 0
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1260
	.p2align 3
.L1275:
	ldr	x2, .LC699
	mov	w3, 5848
	ldr	x4, .LC704
	mov	w0, 0
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1260
	.p2align 3
.L1281:
	add	x0, x0, 11436032
	ldr	w0, [x0, 2448]
	str	w0, [x20]
	b	.L1260
	.p2align 3
.L1277:
	ldr	x2, .LC699
	mov	w3, 5850
	ldr	x4, .LC707
	ldr	x1, .LC700
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1260
	.p2align 3
.L1282:
	ldr	x2, .LC699
	mov	w0, 32
	ldr	x1, .LC709
	add	x2, x2, 368
	bl	dprint_vfmw
	b	.L1260
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
	.align	3
.LC709:
	.xword	.LC708
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
	cbz	x19, .L1293
	cmp	w20, 31
	bhi	.L1294
	ldr	x21, .LC717
	ldr	x0, [x21, w20, sxtw 3]
	cbz	x0, .L1295
	ldr	x0, .LC719
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
	add	x0, x5, 278528
	ldrsb	w0, [x0, 2123]
	cmp	w0, wzr
	ble	.L1291
	mov	x2, 40754
	sub	w4, w0, #1
	mov	w3, 88
	movk	x2, 0x4, lsl 16
	add	x0, x5, 299008
	mov	w1, 0
	umaddl	x2, w4, w3, x2
	add	x0, x0, 3802
	add	x3, x5, x2
	.p2align 2
.L1290:
	ldrsb	w2, [x0], 88
	cmp	w2, 3
	csinc	w1, w1, w1, ne
	cmp	x0, x3
	bne	.L1290
.L1288:
	str	w1, [x19, 84]
	add	x3, x29, 68
	add	x2, x29, 64
	mov	w0, w20
	ldr	x4, [x21, w20, sxtw 3]
	add	x1, x29, 60
	sxtw	x22, w20
	add	x4, x4, 278528
	ldrsb	w4, [x4, 2123]
	str	w4, [x19, 92]
	bl	VCTRL_GetChanImgNum
	ldr	x2, .LC720
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
	mov	x0, 63064
	ldr	x1, [x21, w20, sxtw 3]
	movk	x0, 0x4, lsl 16
	add	x0, x1, x0
	ldrb	w0, [x0, 3616]
	and	w0, w0, 1
	str	w0, [x19, 88]
.L1283:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1294:
	ldr	x2, .LC714
	mov	w3, 1264
	ldr	x4, .LC716
	mov	w0, 0
	ldr	x1, .LC715
	add	x2, x2, 392
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L1295:
	ldr	x2, .LC714
	mov	w3, 1265
	ldr	x4, .LC718
	ldr	x1, .LC715
	add	x2, x2, 392
	bl	dprint_vfmw
	b	.L1283
.L1291:
	mov	w1, 0
	b	.L1288
.L1293:
	ldr	x2, .LC714
	mov	w3, 1263
	ldr	x4, .LC713
	mov	w0, 0
	ldr	x1, .LC715
	add	x2, x2, 392
	bl	dprint_vfmw
	b	.L1283
	.size	VCTRL_GetChanState, .-VCTRL_GetChanState
	.align	3
.LC713:
	.xword	.LC712
	.align	3
.LC714:
	.xword	.LANCHOR4
	.align	3
.LC715:
	.xword	.LC6
	.align	3
.LC716:
	.xword	.LC376
	.align	3
.LC717:
	.xword	.LANCHOR1
	.align	3
.LC718:
	.xword	.LC381
	.align	3
.LC719:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC720:
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
	bhi	.L1300
	ldr	x0, .LC725
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1301
	ldr	w0, [x0, 1372]
.L1298:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1300:
	ldr	x2, .LC723
	mov	w3, 5913
	ldr	x4, .LC722
	mov	w0, 0
	ldr	x1, .LC724
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1298
.L1301:
	ldr	x2, .LC723
	mov	w3, 5914
	ldr	x4, .LC726
	ldr	x1, .LC724
	add	x2, x2, 416
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1298
	.size	VCTRL_GetChanWidth, .-VCTRL_GetChanWidth
	.align	3
.LC722:
	.xword	.LC193
	.align	3
.LC723:
	.xword	.LANCHOR4
	.align	3
.LC724:
	.xword	.LC6
	.align	3
.LC725:
	.xword	.LANCHOR1
	.align	3
.LC726:
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
	bhi	.L1306
	ldr	x0, .LC730
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1307
	ldr	w0, [x0, 1376]
.L1304:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1306:
	ldr	x2, .LC728
	mov	w3, 5921
	ldr	x4, .LC727
	mov	w0, 0
	ldr	x1, .LC729
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1304
.L1307:
	ldr	x2, .LC728
	mov	w3, 5922
	ldr	x4, .LC731
	ldr	x1, .LC729
	add	x2, x2, 440
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1304
	.size	VCTRL_GetChanHeight, .-VCTRL_GetChanHeight
	.align	3
.LC727:
	.xword	.LC193
	.align	3
.LC728:
	.xword	.LANCHOR4
	.align	3
.LC729:
	.xword	.LC6
	.align	3
.LC730:
	.xword	.LANCHOR1
	.align	3
.LC731:
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
	bhi	.L1312
	ldr	x0, .LC735
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1311
	ldr	w0, [x0, 36]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1312:
	ldr	x2, .LC733
	mov	w3, 5929
	ldr	x4, .LC732
	mov	w0, 0
	ldr	x1, .LC734
	add	x2, x2, 464
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1311:
	mov	w0, 33
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_GetChanCapLevel, .-VCTRL_GetChanCapLevel
	.align	3
.LC732:
	.xword	.LC193
	.align	3
.LC733:
	.xword	.LANCHOR4
	.align	3
.LC734:
	.xword	.LC6
	.align	3
.LC735:
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
	ldr	x20, .LC736
	add	w0, w21, 4096
	mov	w1, 10000
	add	w0, w0, 904
	mov	w2, w21
	cmp	w0, w1
	str	w21, [x20, 3560]
	bhi	.L1318
.L1314:
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
	bhi	.L1319
.L1315:
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
.L1318:
	ldr	x1, .LC738
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w2, [x20, 3560]
	b	.L1314
	.p2align 3
.L1319:
	ldr	x1, .LC740
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	w19, [x20, 3564]
	b	.L1315
	.size	VCTRL_SetVdecExtra, .-VCTRL_SetVdecExtra
	.align	3
.LC736:
	.xword	.LANCHOR3
	.align	3
.LC738:
	.xword	.LC737
	.align	3
.LC740:
	.xword	.LC739
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
	cbz	w19, .L1324
	ldr	x3, .LC743
	mov	w1, 1
	ldr	x0, .LC741
	add	x3, x3, 488
	b	.L1322
	.p2align 3
.L1323:
	ldr	w4, [x3, x4]
	add	w1, w1, 1
	ubfiz	x2, x1, 4, 32
	cmp	w4, w19
	add	x2, x3, x2
	beq	.L1321
	ldr	x0, [x2, 8]
.L1322:
	ubfiz	x4, x1, 4, 32
	cbnz	x0, .L1323
.L1321:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1324:
	ldr	x0, .LC742
	b	.L1321
	.size	VfmwProcGetHandler, .-VfmwProcGetHandler
	.align	3
.LC741:
	.xword	VfmwProc_SetErrorThread
	.align	3
.LC742:
	.xword	VfmwProc_SetPrintLevel
	.align	3
.LC743:
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
	cbz	x20, .L1335
	cbz	w19, .L1332
	ldr	x4, .LC747
	mov	w0, 1
	ldr	x5, .LC745
	add	x4, x4, 488
	b	.L1328
	.p2align 3
.L1333:
	ldr	w6, [x4, x6]
	add	w0, w0, 1
	ubfiz	x3, x0, 4, 32
	cmp	w19, w6
	add	x3, x4, x3
	beq	.L1327
	ldr	x5, [x3, 8]
.L1328:
	ubfiz	x6, x0, 4, 32
	cbnz	x5, .L1333
	ldr	x1, .LC749
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
.L1335:
	mov	w0, -2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1332:
	ldr	x5, .LC746
.L1327:
	mov	x0, x20
	blr	x5
	mov	w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetDbgOption, .-VCTRL_SetDbgOption
	.align	3
.LC745:
	.xword	VfmwProc_SetErrorThread
	.align	3
.LC746:
	.xword	VfmwProc_SetPrintLevel
	.align	3
.LC747:
	.xword	.LANCHOR4
	.align	3
.LC749:
	.xword	.LC748
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
	bhi	.L1342
	ldr	x0, .LC751
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1336
	str	w20, [x0, 476]
.L1336:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1342:
	bl	VCTRL_SetLastFrameState.part.23
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetLastFrameState, .-VCTRL_SetLastFrameState
	.align	3
.LC751:
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
	cbz	w20, .L1350
	cmp	w20, 1
	mov	w0, 3
	mov	w1, 4
	csel	w0, w0, w1, eq
	cmp	w19, 31
	bhi	.L1357
.L1347:
	ldr	x21, .LC752
	ldr	x1, [x21, w19, sxtw 3]
	cbz	x1, .L1348
	str	w0, [x1, 476]
.L1348:
	ldr	x0, .LC753
	ldr	x4, [x0, 256]
	cbz	x4, .L1349
	add	x2, x29, 64
	mov	w3, 4
	mov	w1, 115
	mov	w0, w19
	str	w20, [x2, -8]!
	blr	x4
.L1349:
	ldr	x4, [x21, w19, sxtw 3]
	mov	w3, w20
	ldr	x1, .LC755
	mov	w2, w19
	mov	w0, 1
	ldr	w4, [x4, 476]
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1350:
	cmp	w19, 31
	mov	w0, 2
	bls	.L1347
.L1357:
	bl	VCTRL_SetLastFrameState.part.23
	ldr	x21, .LC752
	b	.L1348
	.size	VCTRL_ReportLastFrame, .-VCTRL_ReportLastFrame
	.align	3
.LC752:
	.xword	.LANCHOR1
	.align	3
.LC753:
	.xword	.LANCHOR5
	.align	3
.LC755:
	.xword	.LC754
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
	bhi	.L1385
	ldr	x0, .LC759
	ldr	x0, [x0, w20, sxtw 3]
	cbz	x0, .L1386
	add	x0, x0, 311296
	ldr	w1, [x0, 1616]
	cmp	w1, 17
	bls	.L1387
.L1378:
	mov	w1, 1
	mov	w0, w20
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC763
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, -1
.L1360:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1387:
	ldr	x2, .LC761
	ldrb	w1, [x2,w1,uxtw]
	adr	x2, .Lrtx1364
	add	x1, x2, w1, sxtb #2
	br	x1
.Lrtx1364:
	.section	.rodata
	.align	0
	.align	2
.L1364:
	.byte	(.L1363 - .Lrtx1364) / 4
	.byte	(.L1365 - .Lrtx1364) / 4
	.byte	(.L1366 - .Lrtx1364) / 4
	.byte	(.L1367 - .Lrtx1364) / 4
	.byte	(.L1378 - .Lrtx1364) / 4
	.byte	(.L1368 - .Lrtx1364) / 4
	.byte	(.L1369 - .Lrtx1364) / 4
	.byte	(.L1378 - .Lrtx1364) / 4
	.byte	(.L1370 - .Lrtx1364) / 4
	.byte	(.L1371 - .Lrtx1364) / 4
	.byte	(.L1372 - .Lrtx1364) / 4
	.byte	(.L1372 - .Lrtx1364) / 4
	.byte	(.L1372 - .Lrtx1364) / 4
	.byte	(.L1373 - .Lrtx1364) / 4
	.byte	(.L1378 - .Lrtx1364) / 4
	.byte	(.L1374 - .Lrtx1364) / 4
	.byte	(.L1375 - .Lrtx1364) / 4
	.byte	(.L1376 - .Lrtx1364) / 4
	.text
	.p2align 3
.L1376:
	add	x0, x0, 1624
	bl	VP9DEC_GetRemainImg
	mov	w19, w0
	.p2align 2
.L1362:
	cmn	w19, #1
	beq	.L1378
	cbnz	w19, .L1388
	mov	w0, w20
	mov	w1, 0
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC765
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1375:
	add	x0, x0, 1624
	bl	HEVCDEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1374:
	add	x0, x0, 1624
	bl	MVC_DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1373:
	add	x0, x0, 1624
	bl	VP8DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1372:
	add	x0, x0, 1624
	bl	VP6DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1371:
	add	x0, x0, 1624
	bl	REAL9DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1370:
	add	x0, x0, 1624
	bl	REAL8DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1369:
	add	x0, x0, 1624
	bl	AVSDEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1368:
	add	x0, x0, 1624
	bl	DIVX3DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1367:
	add	x0, x0, 1624
	bl	MPEG2DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1366:
	add	x0, x0, 1624
	bl	MPEG4DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1365:
	add	x0, x0, 1624
	bl	VC1DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1363:
	add	x0, x0, 1624
	bl	H264DEC_GetRemainImg
	mov	w19, w0
	b	.L1362
	.p2align 3
.L1388:
	mov	w1, w19
	mov	w0, w20
	bl	VCTRL_ReportLastFrame
	ldr	x1, .LC767
	sub	w2, w19, #2
	mov	w0, 2
	bl	dprint_vfmw
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1385:
	ldr	x2, .LC757
	mov	w3, 7206
	ldr	x4, .LC756
	mov	w0, 0
	ldr	x1, .LC758
	add	x2, x2, 1208
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1360
.L1386:
	ldr	x2, .LC757
	mov	w3, 7207
	ldr	x4, .LC760
	ldr	x1, .LC758
	add	x2, x2, 1208
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1360
	.size	VCTRL_OutputLastFrame, .-VCTRL_OutputLastFrame
	.align	3
.LC756:
	.xword	.LC193
	.align	3
.LC757:
	.xword	.LANCHOR4
	.align	3
.LC758:
	.xword	.LC6
	.align	3
.LC759:
	.xword	.LANCHOR1
	.align	3
.LC760:
	.xword	.LC9
	.align	3
.LC761:
	.xword	.L1364
	.align	3
.LC763:
	.xword	.LC762
	.align	3
.LC765:
	.xword	.LC764
	.align	3
.LC767:
	.xword	.LC766
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
	ldr	x21, .LC768
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1423
	ldr	w1, [x0, 632]
	ldr	w24, [x0, 1312]
	cmp	w1, 17
	bls	.L1424
.L1389:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1424:
	ldr	x2, .LC772
	ldrh	w1, [x2,w1,uxtw #1]
	adr	x2, .Lrtx1393
	add	x1, x2, w1, sxth #2
	br	x1
.Lrtx1393:
	.section	.rodata
	.align	0
	.align	2
.L1393:
	.2byte	(.L1392 - .Lrtx1393) / 4
	.2byte	(.L1394 - .Lrtx1393) / 4
	.2byte	(.L1395 - .Lrtx1393) / 4
	.2byte	(.L1396 - .Lrtx1393) / 4
	.2byte	(.L1389 - .Lrtx1393) / 4
	.2byte	(.L1397 - .Lrtx1393) / 4
	.2byte	(.L1398 - .Lrtx1393) / 4
	.2byte	(.L1389 - .Lrtx1393) / 4
	.2byte	(.L1399 - .Lrtx1393) / 4
	.2byte	(.L1400 - .Lrtx1393) / 4
	.2byte	(.L1401 - .Lrtx1393) / 4
	.2byte	(.L1401 - .Lrtx1393) / 4
	.2byte	(.L1401 - .Lrtx1393) / 4
	.2byte	(.L1402 - .Lrtx1393) / 4
	.2byte	(.L1389 - .Lrtx1393) / 4
	.2byte	(.L1403 - .Lrtx1393) / 4
	.2byte	(.L1404 - .Lrtx1393) / 4
	.2byte	(.L1405 - .Lrtx1393) / 4
	.text
	.p2align 3
.L1405:
	add	x0, x0, 311296
	mov	w3, w22
	mov	w2, w24
	mov	w1, w20
	add	x0, x0, 1624
	bl	VP9DEC_VDMPostProc
	cmp	w24, 1
	beq	.L1389
.L1421:
	ldr	x0, [x21, w19, sxtw 3]
.L1422:
	add	x0, x0, 311296
	str	xzr, [x0, 1632]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1404:
	add	x0, x0, 311296
	mov	w5, w22
	mov	w4, w24
	mov	x3, x23
	mov	w2, 1
	mov	w1, w20
	add	x0, x0, 1624
	bl	HEVCDEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	ldrb	w0, [x0, 1633]
	cmp	w0, 1
	beq	.L1425
.L1408:
	cmp	w24, 1
	beq	.L1389
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	str	xzr, [x0, 4072]
	b	.L1389
	.p2align 3
.L1403:
	add	x0, x0, 311296
	mov	w1, w20
	mov	w2, 1
	add	x0, x0, 1624
	bl	MVC_DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	ldrb	w1, [x0, 1625]
	cmp	w1, 1
	beq	.L1426
	str	xzr, [x0, 1856]
	b	.L1389
	.p2align 3
.L1402:
	add	x0, x0, 311296
	mov	w1, w20
	add	x0, x0, 1624
	bl	VP8DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	str	xzr, [x0, 1632]
	b	.L1389
	.p2align 3
.L1401:
	add	x0, x0, 311296
	mov	w1, w20
	add	x0, x0, 1624
	bl	VP6DEC_VDMPostProc
	b	.L1421
	.p2align 3
.L1400:
	mov	w0, w22
	bl	VDMDRV_GetMb0QpInCurrPic
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 311296
	add	x0, x0, 1624
	bl	REAL9DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	str	xzr, [x0, 1632]
	b	.L1389
	.p2align 3
.L1399:
	mov	w0, w22
	bl	VDMDRV_GetMb0QpInCurrPic
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 311296
	add	x0, x0, 1624
	bl	REAL8DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	str	xzr, [x0, 1632]
	b	.L1389
	.p2align 3
.L1398:
	add	x0, x0, 311296
	mov	w1, w20
	add	x0, x0, 1624
	bl	AVSDEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	ldrb	w1, [x0, 1624]
	cmp	w1, 1
	beq	.L1427
	str	xzr, [x0, 1648]
	b	.L1389
	.p2align 3
.L1397:
	mov	w0, w22
	bl	VDMDRV_GetSwitchRounding
	mov	w2, w0
	ldr	x3, [x21, w19, sxtw 3]
	mov	w1, w20
	add	x0, x3, 311296
	add	x0, x0, 1624
	bl	DIVX3DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	str	xzr, [x0, 1632]
	b	.L1389
	.p2align 3
.L1396:
	add	x0, x0, 311296
	mov	w1, w20
	add	x0, x0, 1624
	bl	MPEG2DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 401408
	ldrb	w1, [x1, 930]
	cmp	w1, 1
	bne	.L1422
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 401408
	strb	wzr, [x1, 930]
	b	.L1422
	.p2align 3
.L1395:
	add	x0, x0, 311296
	mov	w1, w20
	mov	x2, x23
	add	x0, x0, 1624
	bl	MPEG4DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 335872
	ldrb	w1, [x1, 412]
	cmp	w1, 1
	beq	.L1428
.L1411:
	add	x0, x0, 311296
	str	xzr, [x0, 2664]
	b	.L1389
	.p2align 3
.L1394:
	add	x0, x0, 311296
	mov	w1, w20
	add	x0, x0, 1624
	bl	VC1DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 327680
	ldrb	w1, [x1, 55]
	cmp	w1, 1
	bne	.L1422
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 327680
	strb	wzr, [x1, 55]
	b	.L1422
	.p2align 3
.L1392:
	add	x0, x0, 311296
	mov	w5, w22
	mov	w4, w24
	mov	x3, x23
	mov	w2, 1
	mov	w1, w20
	add	x0, x0, 1624
	bl	H264DEC_VDMPostProc
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 327680
	ldrb	w0, [x0, 168]
	cmp	w0, 1
	beq	.L1429
.L1406:
	cmp	w24, 1
	beq	.L1389
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	str	xzr, [x0, 2240]
	b	.L1389
	.p2align 3
.L1427:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	strb	wzr, [x0, 1624]
	str	xzr, [x0, 1648]
	b	.L1389
	.p2align 3
.L1426:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	strb	wzr, [x0, 1625]
	str	xzr, [x0, 1856]
	b	.L1389
	.p2align 3
.L1423:
	ldr	x2, .LC770
	mov	w3, 4036
	ldr	x4, .LC769
	ldr	x1, .LC771
	add	x2, x2, 1232
	bl	dprint_vfmw
	b	.L1389
	.p2align 3
.L1428:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 335872
	strb	wzr, [x1, 412]
	b	.L1411
.L1429:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 327680
	strb	wzr, [x0, 168]
	b	.L1406
.L1425:
	mov	w0, w19
	bl	VCTRL_OutputLastFrame
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	strb	wzr, [x0, 1633]
	b	.L1408
	.size	VCTRL_PostProc, .-VCTRL_PostProc
	.align	3
.LC768:
	.xword	.LANCHOR1
	.align	3
.LC769:
	.xword	.LC9
	.align	3
.LC770:
	.xword	.LANCHOR4
	.align	3
.LC771:
	.xword	.LC6
	.align	3
.LC772:
	.xword	.L1393
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
	bhi	.L1438
	ldr	x0, .LC776
	ldr	x0, [x0, w19, sxtw 3]
	cbz	x0, .L1439
	ldr	w0, [x0, 8]
	cmp	w0, 1
	beq	.L1434
	ldr	x2, .LC774
	mov	w3, 4226
	ldr	x4, .LC778
	mov	w0, 0
	ldr	x1, .LC775
	add	x2, x2, 1248
	bl	dprint_vfmw
.L1430:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1434:
	mov	w0, w19
	bl	VCTRL_GetDecParam
	cbz	x0, .L1430
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
.L1438:
	ldr	x2, .LC774
	mov	w3, 4224
	ldr	x4, .LC773
	mov	w0, 0
	ldr	x1, .LC775
	add	x2, x2, 1248
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1439:
	ldr	x2, .LC774
	mov	w3, 4225
	ldr	x4, .LC777
	ldr	x1, .LC775
	add	x2, x2, 1248
	bl	dprint_vfmw
	b	.L1430
	.size	VCTRL_VdmPostProc, .-VCTRL_VdmPostProc
	.align	3
.LC773:
	.xword	.LC466
	.align	3
.LC774:
	.xword	.LANCHOR4
	.align	3
.LC775:
	.xword	.LC6
	.align	3
.LC776:
	.xword	.LANCHOR1
	.align	3
.LC777:
	.xword	.LC426
	.align	3
.LC778:
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
	bhi	.L1443
	add	w1, w20, 2
	mov	w0, w19
	bl	VCTRL_ReportLastFrame
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1443:
	ldr	x2, .LC780
	mov	w3, 7332
	ldr	x4, .LC779
	mov	w0, 0
	ldr	x1, .LC781
	add	x2, x2, 1272
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SvdecLastFrame, .-VCTRL_SvdecLastFrame
	.align	3
.LC779:
	.xword	.LC193
	.align	3
.LC780:
	.xword	.LANCHOR4
	.align	3
.LC781:
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
	bls	.L1462
	ldr	x1, .LC784
	mov	w3, w19
	mov	w2, 7816
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, 13
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1462:
	ldr	x0, .LC782
	ldrb	w0, [x0,w19,uxtw]
	adr	x1, .Lrtx1447
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx1447:
	.section	.rodata
	.align	0
	.align	2
.L1447:
	.byte	(.L1446 - .Lrtx1447) / 4
	.byte	(.L1448 - .Lrtx1447) / 4
	.byte	(.L1449 - .Lrtx1447) / 4
	.byte	(.L1450 - .Lrtx1447) / 4
	.byte	(.L1451 - .Lrtx1447) / 4
	.byte	(.L1452 - .Lrtx1447) / 4
	.byte	(.L1453 - .Lrtx1447) / 4
	.text
	.p2align 3
.L1452:
	cmp	w20, 1
	mov	w1, 12
	mov	w0, 13
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1453:
	cmp	w20, 1
	mov	w0, 7
	csinc	w0, w0, wzr, ne
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1446:
	cmp	w20, 1
	mov	w0, 6
	csel	w0, wzr, w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1448:
	cmp	w20, 1
	mov	w1, 8
	mov	w0, 2
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1449:
	cmp	w20, 1
	mov	w1, 10
	mov	w0, 4
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1450:
	cmp	w20, 1
	mov	w1, 9
	mov	w0, 3
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1451:
	cmp	w20, 1
	mov	w1, 11
	mov	w0, 5
	csel	w0, w0, w1, eq
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	Get_YuvFormat, .-Get_YuvFormat
	.align	3
.LC782:
	.xword	.L1447
	.align	3
.LC784:
	.xword	.LC783
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
	beq	.L1472
	ldr	w0, [x20, 4]
	cmp	w0, 1
	beq	.L1466
	mov	w0, w21
	mov	w2, 0
	mov	w1, w22
	bl	FSP_ClearLogicFs
	mov	w0, 0
.L1465:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1466:
	ldr	w0, [x20, 48]
	bl	MEM_Phy2Vir
	cbz	x0, .L1473
.L1467:
	mov	w1, w22
	mov	w0, w21
	bl	FSP_GetFsImagePtr
	mov	x19, x0
	cbz	x0, .L1474
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
	ldr	x4, .LC791
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
	beq	.L1475
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
	ldr	x2, .LC794
	mov	x4, x19
	mov	w1, w24
	mov	w0, w21
	ldr	x2, [x2, w21, sxtw 3]
	add	x2, x2, 311296
	add	x3, x2, 1632
	add	x2, x2, 1624
	bl	InsertImgToVoQueue
	cmp	w0, 1
	mov	w0, 0
	beq	.L1465
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
	b	.L1465
	.p2align 3
.L1473:
	ldr	w0, [x20, 4]
	cmp	w0, 1
	bne	.L1467
	ldr	x1, .LC788
	mov	w0, 0
	ldr	w2, [x20, 48]
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1465
.L1472:
	ldr	x1, .LC786
	mov	w0, 0
	ldr	w2, [x20, 40]
	bl	dprint_vfmw
	mov	w0, w22
	b	.L1465
.L1475:
	ldr	x1, .LC793
	mov	w2, w0
	mov	w0, w23
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1465
.L1474:
	ldr	x1, .LC790
	mov	w2, 4519
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1465
	.size	VDH_PutUsrdecFrame, .-VDH_PutUsrdecFrame
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
.LC791:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC793:
	.xword	.LC792
	.align	3
.LC794:
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
	ldr	x20, .LC795
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1484
	cbz	x21, .L1485
	ldr	w2, [x0, 632]
	cmp	w2, 20
	bne	.L1486
	ldr	x3, .LC803
	mov	x1, x21
	mov	x2, 72
	add	x0, x0, 560
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 560
	bl	VDH_PutUsrdecFrame
	cbnz	w0, .L1487
.L1478:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1486:
	ldr	x1, .LC802
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1478
	.p2align 3
.L1487:
	ldr	x1, .LC805
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1478
.L1485:
	ldr	x2, .LC797
	mov	w3, 4660
	ldr	x4, .LC800
	mov	w0, 0
	ldr	x1, .LC798
	add	x2, x2, 1296
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1478
.L1484:
	ldr	x2, .LC797
	mov	w3, 4659
	ldr	x4, .LC796
	ldr	x1, .LC798
	add	x2, x2, 1296
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1478
	.size	VCTRL_PutUsrdecFrame, .-VCTRL_PutUsrdecFrame
	.align	3
.LC795:
	.xword	.LANCHOR1
	.align	3
.LC796:
	.xword	.LC9
	.align	3
.LC797:
	.xword	.LANCHOR4
	.align	3
.LC798:
	.xword	.LC6
	.align	3
.LC800:
	.xword	.LC799
	.align	3
.LC802:
	.xword	.LC801
	.align	3
.LC803:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC805:
	.xword	.LC804
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
	beq	.L1490
	mov	w0, w19
	bl	VCTRL_CanBeDecodedByHardWare.part.25
.L1490:
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
	beq	.L1495
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1495:
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
	bhi	.L1531
	ldr	x20, .LC808
	ldr	x0, [x20, w21, sxtw 3]
	cbz	x0, .L1532
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L1500
	ldr	w0, [x0, 632]
	cmp	w0, 22
	beq	.L1500
	cmp	w0, 7
	ccmp	w0, 4, 4, ne
	beq	.L1496
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cbz	w0, .L1496
	mov	x19, 0
	mov	w22, 0
	.p2align 2
.L1505:
	mov	w0, w19
	bl	VCTRL_IsChanActive
	cbnz	w0, .L1504
	ldr	x0, [x20, x19, lsl 3]
	ldr	w1, [x0, 632]
	cmp	w1, 4
	mov	w0, w1
	ccmp	w1, 7, 4, ne
	beq	.L1504
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cmp	w0, wzr
	csinc	w22, w22, w22, eq
.L1504:
	add	x19, x19, 1
	cmp	x19, 32
	bne	.L1505
	cmp	w22, 1
	beq	.L1533
.L1506:
	mov	x0, x20
	add	x3, x20, 256
	mov	w2, 0
	.p2align 2
.L1513:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbz	x1, .L1512
	ldr	w1, [x1, 632]
	cmp	w1, 6
	csinc	w2, w2, wzr, ne
.L1512:
	cmp	x0, x3
	bne	.L1513
	cmp	w2, 1
	beq	.L1534
.L1514:
	ldr	x0, [x20, w21, sxtw 3]
	ldr	w0, [x0, 632]
	cmp	w0, 1
	bne	.L1496
	ldr	x0, .LC813
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L1535
	ldr	x0, .LC814
	ldr	x1, [x0, 56]
	cbz	x1, .L1496
	mov	w0, 0
	blr	x1
	b	.L1496
	.p2align 3
.L1500:
	ldr	x1, .LC812
	mov	w2, 7877
	mov	w0, 0
	bl	dprint_vfmw
.L1496:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1531:
	ldr	x1, .LC807
	mov	w2, 7865
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1533:
	ldr	x19, .LC813
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1536
	mov	w1, 0
	mov	w0, w22
	bl	VDH_Need_Module
.L1509:
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L1510
	ldr	x0, .LC814
	ldr	x1, [x0, 40]
	cbz	x1, .L1537
	mov	w0, 0
	blr	x1
	b	.L1506
.L1534:
	ldr	x0, .LC813
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1538
	mov	w1, 0
	mov	w0, 3
	bl	VDH_Need_Module
	b	.L1514
.L1538:
	ldr	x0, .LC814
	ldr	x1, [x0, 24]
	cbz	x1, .L1539
	mov	w0, 0
	blr	x1
	b	.L1514
.L1536:
	ldr	x0, .LC814
	ldr	x1, [x0, 8]
	cbz	x1, .L1540
	mov	w0, 0
	blr	x1
	b	.L1509
.L1532:
	ldr	x1, .LC810
	mov	w2, 7871
	bl	dprint_vfmw
	b	.L1496
.L1535:
	mov	w1, 0
	mov	w0, 2
	bl	VDH_Need_Module
	b	.L1496
.L1510:
	mov	w1, 0
	mov	w0, 0
	bl	VDH_Need_Module
	b	.L1506
.L1537:
	ldr	x1, .LC815
	mov	w2, 7926
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1506
.L1539:
	ldr	x1, .LC815
	mov	w2, 7957
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1514
.L1540:
	ldr	x1, .LC815
	mov	w2, 7912
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1509
	.size	VCTRL_OpenHardware, .-VCTRL_OpenHardware
	.align	3
.LC807:
	.xword	.LC806
	.align	3
.LC808:
	.xword	.LANCHOR1
	.align	3
.LC810:
	.xword	.LC809
	.align	3
.LC812:
	.xword	.LC811
	.align	3
.LC813:
	.xword	g_HalDisable
	.align	3
.LC814:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC815:
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
	bhi	.L1552
	ldr	x19, .LC820
	ldr	x0, [x19, w20, sxtw 3]
	cbz	x0, .L1553
	ldr	w21, [x0, 4]
	cmp	w21, 1
	bne	.L1554
	ldr	w0, [x0, 632]
	cmp	w0, 22
	beq	.L1555
	mov	w0, w20
	bl	SM_Start
	ldr	x0, [x19, w20, sxtw 3]
	add	x1, x0, 311296
	str	w21, [x1, 1612]
	str	w21, [x0, 8]
	ldr	x0, [x19, w20, sxtw 3]
	str	w21, [x0, 12]
	ldr	x0, [x19, w20, sxtw 3]
	str	wzr, [x0, 24]
	ldr	x0, [x19, w20, sxtw 3]
	str	w21, [x0, 16]
	ldr	x1, [x19, w20, sxtw 3]
	ldr	w0, [x1, 20]
	cbnz	w0, .L1547
	str	w21, [x1, 20]
	mov	x1, 0
	ldr	x0, .LC825
	ldr	x5, .LC826
	b	.L1550
	.p2align 3
.L1557:
	ldr	w4, [x2, 20]
	str	w4, [x3, x1, lsl 2]
	ldr	w2, [x2, 20]
	str	w2, [x5, x1, lsl 2]
	add	x1, x1, 1
	cmp	x1, 32
	beq	.L1556
.L1550:
	ldr	x2, [x19, x1, lsl 3]
	add	x3, x0, 1544
	cbnz	x2, .L1557
	add	x2, x0, 1544
	str	wzr, [x5, x1, lsl 2]
	str	wzr, [x2, x1, lsl 2]
	add	x1, x1, 1
	cmp	x1, 32
	bne	.L1550
	.p2align 2
.L1556:
	add	x0, x0, 1544
	bl	VDMDRV_SetPriority
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
.L1547:
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w20
	bl	VCTRL_OpenHardware
	ldr	x19, .LC827
	ldr	x0, .LC828
	mov	x2, 12
	mov	w1, 0
	ldr	x3, [x19, 96]
	blr	x3
	ldr	x3, [x19, 96]
	mov	x2, 720
	ldr	x0, .LC829
	mov	w1, 0
	blr	x3
	ldr	x3, [x19, 96]
	mov	x2, 2
	ldr	x0, .LC830
	mov	w1, 0
	blr	x3
	ldr	x0, .LC831
	mov	x2, 120
	ldr	x3, [x19, 96]
	mov	w1, 0
	blr	x3
	mov	w0, 0
.L1543:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1554:
	ldr	x2, .LC818
	mov	w3, 2310
	ldr	x4, .LC822
	mov	w0, 0
	ldr	x1, .LC819
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1543
.L1552:
	ldr	x2, .LC818
	mov	w3, 2308
	ldr	x4, .LC817
	mov	w0, 0
	ldr	x1, .LC819
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1543
.L1555:
	ldr	x2, .LC818
	mov	w3, 2311
	ldr	x4, .LC824
	mov	w0, 0
	ldr	x1, .LC819
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1543
.L1553:
	ldr	x2, .LC818
	mov	w3, 2309
	ldr	x4, .LC821
	ldr	x1, .LC819
	add	x2, x2, 1320
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1543
	.size	VCTRL_StartChan, .-VCTRL_StartChan
	.align	3
.LC817:
	.xword	.LC193
	.align	3
.LC818:
	.xword	.LANCHOR4
	.align	3
.LC819:
	.xword	.LC6
	.align	3
.LC820:
	.xword	.LANCHOR1
	.align	3
.LC821:
	.xword	.LC292
	.align	3
.LC822:
	.xword	.LC488
	.align	3
.LC824:
	.xword	.LC823
	.align	3
.LC825:
	.xword	.LANCHOR5
	.align	3
.LC826:
	.xword	g_ChanCtx
	.align	3
.LC827:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC828:
	.xword	g_TimeRecId
	.align	3
.LC829:
	.xword	g_TimeRecTable
	.align	3
.LC830:
	.xword	g_DataRecId
	.align	3
.LC831:
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
	ldr	x1, .LC834
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStartChan, .-VfmwProc_TestStartChan
	.align	3
.LC834:
	.xword	.LC833
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
	ldr	x19, .LC835
	mov	w0, 0
	add	x23, x19, 256
	b	.L1568
	.p2align 3
.L1610:
	ldr	w1, [x20, 4]
	cmp	w1, 1
	beq	.L1607
.L1560:
	add	x19, x19, 8
	cmp	x19, x23
	beq	.L1608
.L1568:
	ldr	x20, [x19]
	cbz	x20, .L1560
	ldr	w21, [x20, 632]
	cbnz	w0, .L1561
	ldr	w1, [x20, 4]
	cmp	w1, 1
	beq	.L1609
.L1561:
	cmp	w22, wzr
	ccmp	w21, 1, 0, eq
	beq	.L1610
.L1564:
	cmp	w24, wzr
	ccmp	w21, 6, 0, eq
	bne	.L1560
	ldr	w1, [x20, 4]
	cmp	w1, 1
	bne	.L1560
	ldr	w26, [x20, 8]
.L1588:
	cmp	w26, 1
	add	x19, x19, 8
	csinc	w24, w24, wzr, ne
	cmp	x19, x23
	bne	.L1568
	.p2align 2
.L1608:
	cbnz	w0, .L1569
	ldr	x19, .LC836
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1574
	mov	w0, w25
	bl	SCDDRV_ResetSCD
	mov	w0, w25
	bl	VDMDRV_ResetVDH
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1574
	mov	w1, 0
	mov	w0, 1
	bl	VDH_UnNeed_Module
	ldrb	w0, [x19]
	cmp	w0, 1
	bne	.L1577
.L1616:
	ldr	x0, .LC837
	ldr	x1, [x0, 48]
	cbz	x1, .L1611
	mov	w0, 0
	blr	x1
.L1580:
	mov	w0, 0
	bl	SCDDRV_SetStateIdle
.L1569:
	cbnz	w24, .L1581
	ldr	x0, .LC836
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1612
	mov	w1, 0
	mov	w0, 3
	bl	VDH_UnNeed_Module
.L1581:
	cbnz	w22, .L1559
	ldr	x0, .LC836
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L1613
	ldr	x0, .LC837
	ldr	x1, [x0, 64]
	cbz	x1, .L1559
	mov	w0, 0
	blr	x1
.L1559:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1609:
	ldr	w26, [x20, 8]
	cmp	w26, 1
	beq	.L1614
.L1563:
	cmp	w21, 1
	ccmp	w22, wzr, 0, eq
	bne	.L1564
.L1587:
	cmp	w26, 1
	csinc	w22, w22, wzr, ne
	cmp	w21, 6
	ccmp	w24, wzr, 0, eq
	beq	.L1588
	b	.L1560
	.p2align 3
.L1614:
	cmp	w21, 4
	ccmp	w21, 7, 4, ne
	beq	.L1563
	mov	w0, w21
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cmp	w0, wzr
	cset	w0, ne
	b	.L1563
.L1574:
	ldr	x0, .LC837
	ldr	x1, [x0, 16]
	cbz	x1, .L1615
	mov	w0, 0
	blr	x1
.L1576:
	mov	w0, 0
	bl	VDMDRV_SetStateIdle
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L1616
.L1577:
	mov	w1, 0
	mov	w0, 0
	bl	VDH_UnNeed_Module
	b	.L1569
.L1613:
	mov	w1, 0
	mov	w0, 2
	bl	VDH_UnNeed_Module
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1612:
	ldr	x0, .LC837
	ldr	x1, [x0, 32]
	cbz	x1, .L1617
	mov	w0, 0
	blr	x1
	b	.L1581
.L1611:
	ldr	x1, .LC838
	mov	w2, 8051
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1580
.L1615:
	ldr	x1, .LC838
	mov	w2, 8036
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1576
.L1617:
	ldr	x1, .LC838
	mov	w2, 8069
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1581
.L1607:
	ldr	w26, [x20, 8]
	b	.L1587
	.size	VCTRL_CloseHardware, .-VCTRL_CloseHardware
	.align	3
.LC835:
	.xword	.LANCHOR1
	.align	3
.LC836:
	.xword	g_HalDisable
	.align	3
.LC837:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC838:
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
	bhi	.L1624
	ldr	x20, .LC843
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1625
	ldr	w1, [x0, 4]
	cmp	w1, 1
	bne	.L1623
	str	w1, [x0, 24]
	mov	w0, w19
	ldr	x1, [x20, w19, sxtw 3]
	str	wzr, [x1, 12]
	ldr	x1, [x20, w19, sxtw 3]
	str	wzr, [x1, 8]
	bl	SM_Stop
	cbnz	w0, .L1623
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
.L1620:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1623:
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1624:
	ldr	x2, .LC841
	mov	w3, 2395
	ldr	x4, .LC840
	mov	w0, 0
	ldr	x1, .LC842
	add	x2, x2, 1336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1620
.L1625:
	ldr	x2, .LC841
	mov	w3, 2396
	ldr	x4, .LC845
	ldr	x1, .LC842
	add	x2, x2, 1336
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1620
	.size	VCTRL_StopChan, .-VCTRL_StopChan
	.align	3
.LC840:
	.xword	.LC193
	.align	3
.LC841:
	.xword	.LANCHOR4
	.align	3
.LC842:
	.xword	.LC6
	.align	3
.LC843:
	.xword	.LANCHOR1
	.align	3
.LC845:
	.xword	.LC844
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
	ldr	x19, .LC846
	b	.L1628
	.p2align 3
.L1632:
	ldr	x1, [x19, 240]
	mov	w0, 10
	add	w20, w20, 1
	blr	x1
	cmp	w20, 50
	beq	.L1630
.L1628:
	ldr	x1, [x19, 24]
	mov	w0, 0
	blr	x1
	mov	w0, w22
	bl	VCTRL_StopChan
	mov	w21, w0
	ldr	x1, [x19, 32]
	mov	w0, 0
	blr	x1
	cbnz	w21, .L1632
	cmp	w20, 49
	bgt	.L1630
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1630:
	ldr	x1, .LC848
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
.LC846:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC848:
	.xword	.LC847
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
	bhi	.L1659
	ldr	x20, .LC852
	sxtw	x24, w19
	ldr	x1, [x20, w19, sxtw 3]
	cbz	x1, .L1660
	ldr	w0, [x21]
	cmp	w0, 1
	bhi	.L1661
	mov	w0, w19
	ldr	w23, [x1, 8]
	bl	VCTRL_StopChan
	ldr	x22, .LC856
	ldr	x3, [x20, w19, sxtw 3]
	lsl	x0, x24, 2
	ldr	x1, .LC857
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
	add	x1, x0, 311296
	ldr	w0, [x0, 632]
	add	x1, x1, 1624
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
	beq	.L1662
.L1638:
	ldr	w0, [x0, 632]
	cmp	w0, 20
	beq	.L1639
	ldr	w0, [x21, 8]
	cbz	w0, .L1663
.L1639:
	mov	w0, w19
	bl	FSP_EmptyInstance
.L1640:
	mov	w0, w19
	bl	InitUsdPool
	ldr	w0, [x21]
	cbz	w0, .L1664
.L1641:
	ldr	w0, [x20, 1396]
	cbz	w0, .L1642
	add	x20, x20, 2192
	str	w19, [x29, 76]
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1644
	mov	w0, 512
	add	x1, x29, 76
	bl	VCTRL_SetDbgOption
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1644
	add	x1, x29, 76
	mov	w0, 512
	bl	VCTRL_SetDbgOption
.L1644:
	ldr	x1, .LC859
	mov	w0, 32
	bl	dprint_vfmw
.L1642:
	cbnz	w23, .L1665
.L1646:
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, 0
.L1635:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L1664:
	mov	w0, w19
	bl	SM_Reset
	b	.L1641
	.p2align 3
.L1665:
	mov	w0, w19
	bl	VCTRL_StartChan
	b	.L1646
	.p2align 3
.L1662:
	add	x1, x0, 311296
	str	wzr, [x0, 1600]
	str	wzr, [x1, 1548]
	b	.L1638
	.p2align 3
.L1663:
	mov	w0, w19
	bl	FSP_ResetInstance
	b	.L1640
	.p2align 3
.L1661:
	ldr	x1, .LC855
	mov	w2, 2972
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1635
	.p2align 3
.L1659:
	ldr	x2, .LC850
	mov	w3, 2967
	ldr	x4, .LC849
	mov	w0, 0
	ldr	x1, .LC851
	add	x2, x2, 1352
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1635
.L1660:
	ldr	x2, .LC850
	mov	w3, 2968
	ldr	x4, .LC853
	mov	w0, 0
	ldr	x1, .LC851
	add	x2, x2, 1352
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1635
	.size	VCTRL_ResetChanWithOption, .-VCTRL_ResetChanWithOption
	.align	3
.LC849:
	.xword	.LC376
	.align	3
.LC850:
	.xword	.LANCHOR4
	.align	3
.LC851:
	.xword	.LC6
	.align	3
.LC852:
	.xword	.LANCHOR1
	.align	3
.LC853:
	.xword	.LC381
	.align	3
.LC855:
	.xword	.LC854
	.align	3
.LC856:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC857:
	.xword	.LANCHOR5
	.align	3
.LC859:
	.xword	.LC858
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
	bhi	.L1688
	ldr	x20, .LC865
	ldr	x1, [x20, w19, sxtw 3]
	cbz	x1, .L1689
	mov	w0, w19
	ldr	w22, [x1, 8]
	bl	VCTRL_StopChan
	ldr	x21, .LC867
	ldr	x1, [x20, w19, sxtw 3]
	mov	w0, 4
	ldr	x2, [x21, 24]
	str	wzr, [x1, 480]
	str	wzr, [x1, 484]
	blr	x2
	ldr	x0, [x20, w19, sxtw 3]
	ldr	w1, [x0, 1552]
	cmp	w1, 1
	beq	.L1690
.L1670:
	sxtw	x3, w19
	ldr	x1, .LC868
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
	add	x1, x0, 311296
	str	x2, [x0, 704]
	str	x2, [x0, 712]
	str	wzr, [x0, 1240]
	str	wzr, [x1, 1568]
	str	wzr, [x1, 1572]
	str	wzr, [x1, 1576]
	str	wzr, [x0, 1636]
	ldr	w2, [x0, 1552]
	cmp	w2, 1
	beq	.L1691
.L1671:
	ldr	w0, [x0, 632]
	cmp	w0, 20
	mov	w0, w19
	beq	.L1672
	bl	FSP_ResetInstance
.L1673:
	ldr	x1, [x21, 32]
	mov	w0, 4
	blr	x1
	mov	w0, w19
	bl	InitUsdPool
	mov	w0, w19
	bl	SM_Reset
	ldr	w0, [x20, 1396]
	cbz	w0, .L1674
	add	x20, x20, 2192
	str	w19, [x29, 60]
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1676
	mov	w0, 512
	add	x1, x29, 60
	bl	VCTRL_SetDbgOption
	ldr	x0, [x20, w19, sxtw 3]
	cbz	x0, .L1676
	add	x1, x29, 60
	mov	w0, 512
	bl	VCTRL_SetDbgOption
.L1676:
	ldr	x1, .LC869
	mov	w0, 32
	bl	dprint_vfmw
.L1674:
	cbnz	w22, .L1692
.L1678:
	mov	w0, w19
	bl	VDMDRV_ClearChanIsDec
	mov	w0, 0
.L1668:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L1692:
	mov	w0, w19
	bl	VCTRL_StartChan
	b	.L1678
	.p2align 3
.L1672:
	bl	FSP_EmptyInstance
	b	.L1673
	.p2align 3
.L1691:
	str	wzr, [x0, 1600]
	str	wzr, [x1, 1548]
	b	.L1671
	.p2align 3
.L1690:
	add	x1, x0, 311296
	ldr	w2, [x0, 632]
	ldr	w1, [x1, 1616]
	cmp	w1, w2
	bne	.L1670
	str	wzr, [x0, 12]
	mov	w0, w19
	bl	VCTRL_FindOccupiedFrame
	b	.L1670
	.p2align 3
.L1688:
	ldr	x2, .LC863
	mov	w3, 3310
	ldr	x4, .LC862
	mov	w0, 0
	ldr	x1, .LC864
	add	x2, x2, 1384
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1668
.L1689:
	ldr	x2, .LC863
	mov	w3, 3311
	ldr	x4, .LC866
	mov	w0, 0
	ldr	x1, .LC864
	add	x2, x2, 1384
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1668
	.size	VCTRL_ResetChan, .-VCTRL_ResetChan
	.align	3
.LC862:
	.xword	.LC376
	.align	3
.LC863:
	.xword	.LANCHOR4
	.align	3
.LC864:
	.xword	.LC6
	.align	3
.LC865:
	.xword	.LANCHOR1
	.align	3
.LC866:
	.xword	.LC381
	.align	3
.LC867:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC868:
	.xword	.LANCHOR5
	.align	3
.LC869:
	.xword	.LC858
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
	ldr	x22, .LC872
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
	cbz	x19, .L1791
	ldr	w0, [x19, 36]
	tbnz	w0, #31, .L1696
	ldr	w0, [x19, 12]
	cmp	w0, 31
	ble	.L1696
	ldr	w0, [x19, 16]
	cmp	w0, 31
	ble	.L1696
	ldr	w1, [x19, 56]
	mov	w0, 262143
	cmp	w1, w0
	ble	.L1696
	ldr	w0, [x19, 44]
	cmp	w0, 1
	beq	.L1792
	cmp	w0, 2
	bne	.L1698
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	ble	.L1696
	ldr	w0, [x19, 24]
	cmp	w0, wzr
	ble	.L1696
.L1786:
	ldr	w0, [x19, 28]
	cmp	w0, wzr
	ble	.L1696
	ldr	w0, [x19, 32]
	cmp	w0, wzr
	bgt	.L1698
.L1696:
	ldr	x1, .LC875
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
.L1807:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 336
	ret
	.p2align 3
.L1698:
	ldr	w0, [x19, 192]
	cmp	w0, 1
	bls	.L1700
	str	wzr, [x19, 192]
.L1700:
	mov	w24, 17864
	mov	w0, 31688
	movk	w0, 0xc, lsl 16
	cmp	w20, 26
	movk	w24, 0xb2, lsl 16
	mov	w21, 1
	csel	w24, w24, w0, eq
	mov	w3, w23
	add	x2, x29, 88
	mov	x1, x19
	mov	w0, w20
	stp	w21, w21, [x19, 216]
	bl	VCTRL_GetChanMemSize
	cbnz	w0, .L1793
	ldr	x25, .LC878
	ldr	x0, [x25]
	cbz	x0, .L1794
	add	x0, x25, 8
	b	.L1705
	.p2align 3
.L1796:
	add	w21, w21, 1
	cmp	w21, 32
	beq	.L1795
.L1705:
	ldr	x1, [x0]
	add	x0, x0, 8
	cbnz	x1, .L1796
.L1704:
	ldr	w0, [x19, 228]
	cmp	w0, 1
	beq	.L1750
.L1707:
	cmp	w21, 31
	bhi	.L1751
	ldr	x3, [x22, 96]
	add	x23, x19, 72
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	ldr	x0, [x23, 56]
	cbz	x0, .L1709
	ldr	w0, [x23, 64]
	cbnz	w0, .L1710
.L1709:
	mov	w1, 3
	mov	w0, 7
	str	w1, [x29, 148]
	bl	VFMW_GetString
	ldr	w2, [x29, 96]
	mov	w4, 1
	add	x3, x29, 120
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1797
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
.L1713:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	ldr	x0, [x23, 8]
	cbnz	x0, .L1798
.L1745:
	ldr	w0, [x19, 192]
	cmp	w0, 1
	beq	.L1716
	mov	w1, 3
	mov	w0, 8
	str	w1, [x29, 148]
	bl	VFMW_GetString
	ldr	w2, [x29, 88]
	mov	w4, 0
	add	x3, x29, 120
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1799
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
.L1720:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	ldr	x0, [x23, 32]
	cbz	x0, .L1747
	ldr	w0, [x23, 40]
	cbnz	w0, .L1724
.L1747:
	mov	w1, 3
	mov	w0, 9
	str	w1, [x29, 148]
	bl	VFMW_GetString
	ldr	w2, [x29, 92]
	mov	w4, 0
	add	x3, x29, 120
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L1800
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
.L1729:
	ldr	x3, [x22, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 120
	blr	x3
	ldr	w0, [x19, 168]
	cbz	w0, .L1734
	ldr	w1, [x19, 184]
	cbz	w1, .L1734
	str	w1, [x29, 144]
	ldr	w1, [x19, 224]
	str	w0, [x29, 136]
	cmp	w1, 1
	beq	.L1801
	ldr	x1, [x22, 352]
	add	x0, x29, 120
	str	wzr, [x29, 148]
	blr	x1
	mov	x1, x0
	str	x0, [x29, 128]
.L1736:
	ldr	w2, [x29, 144]
	ldr	w0, [x29, 136]
	bl	MEM_AddMemRecord
	ldr	w1, [x29, 136]
	ldr	w2, [x29, 144]
	ldr	x0, [x29, 128]
	str	w1, [x29, 312]
	str	x0, [x29, 320]
	str	w2, [x29, 328]
.L1734:
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
	ldr	x3, .LC895
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
	add	x2, x0, 311296
	str	w1, [x0, 632]
	str	w1, [x2, 1616]
	str	wzr, [x0, 28]
	ldr	x0, [x25, w21, sxtw 3]
	ldr	w2, [x19, 224]
	add	x1, x0, 311296
	str	w2, [x1, 1592]
	lsl	x1, x26, 4
	mov	w2, 30
	str	w2, [x0, 1640]
	add	x2, x0, 1648
	str	x2, [x3, x1]
	add	x1, x0, 278528
	add	x1, x1, 2120
	ldr	w0, [x19, 216]
	str	w0, [x2, 76]
	ldr	w0, [x19, 220]
	str	w0, [x2, 80]
	mov	w0, w21
	bl	FSP_EnableInstance
	cbnz	w0, .L1802
	mov	w0, w21
	mov	w20, 0
	mov	w24, 255
	bl	VCTRL_ResetChan
	ldr	x0, [x25, w21, sxtw 3]
	ldp	w3, w2, [x29, 104]
	add	x1, x0, 307200
	ldr	w4, [x29, 112]
	str	w2, [x0, 404]
	add	x2, x1, 1280
	str	w3, [x0, 400]
	str	w4, [x0, 408]
	add	x0, x0, 311296
	stp	wzr, wzr, [x2, 220]
	stp	wzr, wzr, [x2, 228]
	str	wzr, [x1, 1516]
	str	wzr, [x1, 1520]
	ldr	w1, [x19, 192]
	str	w1, [x0, 1556]
	str	wzr, [x0, 1548]
	ldr	w1, [x19, 228]
	str	w1, [x0, 1608]
	str	wzr, [x0, 1612]
	.p2align 2
.L1739:
	uxtw	x1, w20
	ldr	x0, [x25, x26, lsl 3]
	lsl	x19, x1, 6
	ldr	x4, [x22, 96]
	add	x19, x19, x1, lsl 3
	mov	x2, 72
	add	x3, x19, 307200
	mov	w1, 0
	add	x0, x0, x3
	add	w20, w20, 1
	add	x0, x0, 1528
	blr	x4
	ldr	x0, [x25, x26, lsl 3]
	cmp	w20, 32
	add	x1, x0, x19
	add	x1, x1, 307200
	str	w24, [x1, 1528]
	str	w24, [x1, 1532]
	str	w24, [x1, 1536]
	bne	.L1739
	ldr	x3, [x22, 96]
	add	x0, x0, 307200
	mov	x2, 1248
	mov	w1, 0
	add	x0, x0, 3832
	blr	x3
	ldr	x0, [x25, x26, lsl 3]
	mov	x2, 24
	ldr	x3, [x22, 96]
	mov	w1, 0
	add	x0, x0, 311296
	add	x0, x0, 984
	blr	x3
	ldr	x0, [x25, x26, lsl 3]
	ldr	w6, [x29, 264]
	ldr	x3, .LC898
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
	add	x5, x0, 278528
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
	str	wzr, [x5, 2152]
	ldr	w5, [x0, 1552]
	cmp	w5, 1
	beq	.L1740
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
.L1741:
	ldr	x1, [x25, w21, sxtw 3]
	mov	w0, w21
	str	w21, [x1]
	ldr	x1, [x25, w21, sxtw 3]
	add	x2, x1, 278528
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
	add	x19, x19, 311296
	blr	x0
	ldr	x1, [x22, 32]
	str	w0, [x19, 1564]
	mov	w0, 0
	blr	x1
	mov	w0, w21
.L1780:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 336
	ret
	.p2align 3
.L1798:
	ldr	w0, [x23, 16]
	cbz	w0, .L1745
	ldr	x3, [x22, 104]
	mov	x2, 24
	mov	x1, x23
	add	x0, x29, 216
	blr	x3
	ldr	w0, [x19, 192]
	ldr	w2, [x29, 232]
	cmp	w0, 1
	beq	.L1722
	ldr	w4, [x29, 88]
	cmp	w2, w4
	blt	.L1803
.L1722:
	ldr	w0, [x29, 216]
	ldr	x1, [x29, 224]
	bl	MEM_AddMemRecord
	b	.L1720
	.p2align 3
.L1716:
	str	wzr, [x29, 104]
	str	wzr, [x29, 216]
	str	xzr, [x29, 224]
	str	wzr, [x29, 232]
	b	.L1720
	.p2align 3
.L1795:
	ldr	w0, [x19, 228]
	cmp	w0, 1
	bne	.L1751
.L1750:
	add	x1, x29, 84
	mov	w0, 1
	bl	PDT_GetAttribute
	ldr	w0, [x29, 84]
	cmp	w0, 1
	ccmp	w21, 15, 4, ne
	ble	.L1707
	ldr	x1, .LC880
	mov	w2, w21
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1780
	.p2align 3
.L1792:
	ldr	w0, [x19, 20]
	cmp	w0, wzr
	bgt	.L1786
	b	.L1696
	.p2align 3
.L1740:
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
	b	.L1741
.L1710:
	ldr	x3, [x22, 104]
	mov	x2, 24
	add	x1, x19, 120
	add	x0, x29, 264
	blr	x3
	ldr	w0, [x29, 96]
	ldr	w2, [x29, 280]
	cmp	w2, w0
	blt	.L1804
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_AddMemRecord
	b	.L1713
.L1724:
	ldr	x3, [x22, 104]
	add	x1, x19, 96
	add	x0, x29, 240
	mov	x2, 24
	blr	x3
	ldr	x1, [x29, 248]
	cbz	x1, .L1730
	ldr	w0, [x29, 92]
	ldr	w2, [x29, 256]
	cmp	w2, w0
	blt	.L1730
	ldr	w0, [x29, 240]
	bl	MEM_AddMemRecord
	b	.L1729
.L1801:
	ldr	x1, [x22, 320]
	mov	w2, 3
	add	x0, x29, 120
	str	w2, [x29, 148]
	blr	x1
	mov	x1, x0
	str	x0, [x29, 128]
	b	.L1736
.L1800:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L1805
.L1726:
	ldr	w0, [x29, 104]
	cmp	w0, 1
	beq	.L1806
.L1727:
	ldr	x1, .LC892
	mov	w2, 1679
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1807
.L1799:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L1808
.L1718:
	ldr	x1, .LC888
	mov	w2, 1743
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1807
.L1794:
	mov	w21, 0
	b	.L1704
.L1751:
	ldr	x1, .LC882
	mov	w2, 32
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1780
.L1802:
	ldr	x1, .LC897
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
	add	x3, x1, 311296
	add	x2, x1, 307200
	ldr	w6, [x1, 404]
	add	x2, x2, 1528
	ldr	w4, [x1, 400]
	ldr	w5, [x1, 408]
	stp	w4, w6, [x29, 196]
	ldr	w4, [x3, 1556]
	ldr	w19, [x3, 1592]
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
	b	.L1807
.L1797:
	ldr	x1, .LC884
	mov	w2, 1800
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1807
.L1730:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L1809
.L1732:
	ldr	w0, [x29, 104]
	cmp	w0, 1
	beq	.L1810
.L1733:
	ldr	x1, .LC894
	mov	w2, 1707
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1807
.L1793:
	ldr	x1, .LC877
	mov	w2, 1947
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1780
.L1806:
	ldr	w0, [x29, 216]
	ldr	x1, [x29, 224]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 216]
	ldr	w2, [x29, 232]
	ldr	x1, [x29, 224]
	bl	MEM_DelMemRecord
	b	.L1727
.L1808:
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 264]
	ldr	w2, [x29, 280]
	ldr	x1, [x29, 272]
	bl	MEM_DelMemRecord
	b	.L1718
.L1805:
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 264]
	ldr	w2, [x29, 280]
	ldr	x1, [x29, 272]
	bl	MEM_DelMemRecord
	b	.L1726
.L1804:
	ldr	x1, .LC886
	mov	w2, 1816
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1807
.L1803:
	ldr	w0, [x29, 112]
	cmp	w0, 1
	beq	.L1811
.L1723:
	ldr	x1, .LC890
	mov	w3, w2
	mov	w0, 1
	mov	w2, 1774
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1807
.L1810:
	ldr	w0, [x29, 216]
	ldr	x1, [x29, 224]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 216]
	ldr	w2, [x29, 232]
	ldr	x1, [x29, 224]
	bl	MEM_DelMemRecord
	b	.L1733
.L1791:
	ldr	x1, .LC874
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1807
.L1809:
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_ReleaseMemBlock
	ldr	w0, [x29, 264]
	ldr	w2, [x29, 280]
	ldr	x1, [x29, 272]
	bl	MEM_DelMemRecord
	b	.L1732
.L1811:
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_ReleaseMemBlock
	ldr	w2, [x29, 280]
	ldr	w0, [x29, 264]
	ldr	x1, [x29, 272]
	bl	MEM_DelMemRecord
	ldr	w4, [x29, 88]
	ldr	w2, [x29, 232]
	b	.L1723
	.size	VCTRL_CreateChan, .-VCTRL_CreateChan
	.align	3
.LC872:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC874:
	.xword	.LC873
	.align	3
.LC875:
	.xword	.LC534
	.align	3
.LC877:
	.xword	.LC876
	.align	3
.LC878:
	.xword	.LANCHOR1
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
.LC894:
	.xword	.LC893
	.align	3
.LC895:
	.xword	s_SmIIS
	.align	3
.LC897:
	.xword	.LC896
	.align	3
.LC898:
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
	mov	w20, w0
	mov	x23, x1
	mov	x0, x30
	bl	_mcount
	cbz	x23, .L1853
	cmp	w20, 31
	bhi	.L1854
	ldr	x22, .LC905
	ldr	x0, [x22, w20, sxtw 3]
	cbz	x0, .L1855
	ldr	w0, [x0, 4]
	cmp	w0, 1
	bne	.L1856
	mov	x1, x23
	mov	w0, w20
	bl	VCTRL_CheckChanWH
	mov	w21, w0
	cbnz	w0, .L1857
	ldr	x19, .LC910
	add	x24, x19, 1800
	mov	x1, x24
	bl	PDT_GetAttribute
	ldr	w0, [x19, 1820]
	ldr	w2, [x23, 8]
	cmp	w0, 21
	bhi	.L1820
	cmp	w0, w2
	beq	.L1821
	add	x0, x19, 1824
	add	x3, x19, 1948
	.p2align 2
.L1823:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 21
	bhi	.L1820
	cmp	w1, w2
	beq	.L1821
	cmp	x0, x3
	bne	.L1823
.L1821:
	cmp	w2, 8
	str	wzr, [x29, 96]
	beq	.L1858
.L1824:
	cmp	w2, 9
	beq	.L1859
	cmp	w2, 5
	str	wzr, [x29, 96]
	beq	.L1860
.L1843:
	mov	x1, x23
	mov	w0, w20
	bl	VCTRL_CmpConfigParameter
	cbz	w0, .L1861
	ldr	x24, .LC915
	mov	x2, 148
	ldr	x0, [x22, w20, sxtw 3]
	mov	x1, x23
	ldr	x3, [x24, 104]
	add	x0, x0, 44
	blr	x3
	ldr	x0, [x22, w20, sxtw 3]
	mov	x2, 80
	ldr	w1, [x23, 24]
	str	w1, [x0, 20]
	ldr	x0, [x22, w20, sxtw 3]
	ldr	w1, [x23, 8]
	ldr	x3, [x24, 96]
	str	w1, [x0, 632]
	ldr	w1, [x23, 100]
	str	w1, [x0, 1560]
	mov	w1, 0
	add	x0, x29, 96
	blr	x3
	ldr	x0, [x22, w20, sxtw 3]
	ldr	w0, [x0, 424]
	str	w0, [x29, 112]
	bl	MEM_Phy2Vir
	str	x0, [x29, 96]
	ldr	x1, [x22, w20, sxtw 3]
	ldr	w0, [x23, 84]
	ldr	w3, [x23, 24]
	ldr	w2, [x1, 436]
	cmp	w0, 1
	str	w2, [x29, 116]
	add	x1, x1, 311296
	ldr	w2, [x23, 8]
	str	w2, [x29, 108]
	mov	w2, 49152
	movk	w2, 0xf8c3, lsl 16
	strb	w3, [x29, 104]
	str	w2, [x29, 120]
	beq	.L1862
	str	wzr, [x1, 1604]
.L1832:
	ldr	w0, [x23, 88]
	cbnz	w0, .L1863
.L1833:
	ldr	w0, [x23, 80]
	add	x26, x23, 12
	ldr	x3, [x24, 104]
	mov	x2, 12
	mov	x1, x26
	str	w0, [x29, 144]
	stp	wzr, wzr, [x29, 136]
	add	x0, x29, 124
	blr	x3
	add	x1, x29, 96
	mov	w0, w20
	bl	SM_Config
	ldr	x3, [x24, 96]
	mov	x2, 1
	mov	w1, 0
	add	x0, x29, 88
	blr	x3
	ldr	w2, [x23, 84]
	cmp	w2, 1
	beq	.L1864
.L1834:
	ldr	x0, [x22, w20, sxtw 3]
	ldr	x1, .LC916
	ldr	w2, [x0, 352]
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
	ldr	w1, [x1, 72]
	ldr	w2, [x23, 28]
	str	w2, [x0, 644]
	cmp	w1, 7
	ldr	w2, [x23, 28]
	str	w2, [x0, 640]
	ldr	w2, [x23, 36]
	str	w2, [x0, 648]
	beq	.L1865
.L1835:
	str	w1, [x0, 664]
	mov	w25, 1
	ldr	w1, [x23, 44]
	str	w1, [x0, 652]
	ldr	w1, [x23, 132]
	str	w1, [x0, 1324]
	ldr	w1, [x23, 140]
	str	w1, [x0, 1628]
	str	w25, [x0, 1328]
	str	w25, [x0, 1332]
	ldr	w1, [x23, 72]
	cmp	w1, w25
	cset	w1, eq
	str	w1, [x0, 1308]
	ldr	w1, [x23, 76]
	str	w1, [x0, 1312]
	ldr	w1, [x23, 48]
	str	w1, [x0, 1316]
	ldr	w1, [x29, 140]
	str	w1, [x0, 1320]
	str	wzr, [x0, 1600]
	str	wzr, [x0, 1620]
	str	wzr, [x0, 1636]
	add	x0, x0, 311296
	ldrsb	w1, [x23, 1]
	strb	w1, [x0, 1552]
	mov	x1, x23
	mov	w0, w20
	bl	VCTRL_ConfigChanCompress
	ldr	x0, [x22, w20, sxtw 3]
	mov	x2, 12
	ldr	x3, [x24, 104]
	mov	x1, x26
	add	x0, x0, 1244
	blr	x3
	ldr	x0, [x22, w20, sxtw 3]
	add	x1, x0, 311296
	ldr	w2, [x0, 632]
	ldr	w0, [x1, 1616]
	cmp	w0, w2
	beq	.L1836
	mov	w0, w20
	bl	VCTRL_ResetChan
	ldr	w1, [x23, 8]
	ldr	x0, [x22, w20, sxtw 3]
	cmp	w1, 20
	beq	.L1837
	ldr	w2, [x0, 632]
	add	x1, x0, 311296
.L1836:
	ldr	x4, .LC919
	mov	x0, 0
	str	w2, [x1, 1616]
	b	.L1841
	.p2align 3
.L1867:
	ldr	w3, [x1, 20]
	str	w3, [x2, x0, lsl 2]
	ldr	w1, [x1, 20]
	str	w1, [x4, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	beq	.L1866
.L1841:
	ldr	x1, [x22, x0, lsl 3]
	add	x2, x19, 1952
	cbnz	x1, .L1867
	add	x1, x19, 1952
	str	wzr, [x4, x0, lsl 2]
	str	wzr, [x1, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L1841
.L1866:
	add	x0, x19, 1952
	bl	VDMDRV_SetPriority
	mov	w0, w20
	bl	VDMDRV_ClearChanIsDec
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1861:
	ldr	x1, .LC914
	mov	w21, 0
	bl	dprint_vfmw
.L1852:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1820:
	ldr	x1, .LC912
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 176
	ret
	.p2align 3
.L1863:
	mov	w0, 1
	str	w0, [x29, 152]
	b	.L1833
	.p2align 3
.L1859:
	add	x0, x29, 96
	bl	REAL9DEC_Support
	ldr	w0, [x29, 96]
	cbz	w0, .L1825
	ldr	w2, [x23, 8]
	str	wzr, [x29, 96]
	cmp	w2, 5
	bne	.L1843
	b	.L1860
.L1858:
	add	x0, x29, 96
	bl	REAL8DEC_Support
	ldr	w0, [x29, 96]
	cbz	w0, .L1825
	ldr	w2, [x23, 8]
	b	.L1824
.L1860:
	add	x0, x29, 96
	bl	DIVX3DEC_Support
	ldr	w0, [x29, 96]
	cbnz	w0, .L1843
.L1825:
	mov	w21, -1
	b	.L1852
.L1856:
	ldr	x2, .LC902
	mov	w3, 2616
	ldr	x4, .LC907
	mov	w0, 0
	ldr	x1, .LC903
	add	x2, x2, 1400
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1852
.L1862:
	ldr	w2, [x23, 92]
	str	w2, [x29, 156]
	ldr	w2, [x23, 96]
	str	w0, [x29, 148]
	str	w2, [x29, 160]
	ldr	w0, [x23, 136]
	str	w0, [x1, 1604]
	b	.L1832
.L1865:
	ldr	w1, [x23, 40]
	b	.L1835
.L1864:
	add	x1, x29, 88
	mov	w0, w20
	strb	w2, [x29, 88]
	bl	FSP_ConfigAttribute
	b	.L1834
.L1857:
	ldr	x1, .LC909
	mov	w0, 0
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1852
.L1837:
	ldr	w3, [x0, 428]
	ldr	w4, [x0, 432]
	ldr	w1, [x0, 1372]
	ldr	w2, [x0, 1376]
	mov	w0, w20
	bl	VCTRL_PartitionMemForStdUser
	cbnz	w0, .L1838
	ldr	x0, [x22, w20, sxtw 3]
	add	x1, x0, 311296
	ldr	w2, [x0, 632]
	b	.L1836
.L1854:
	ldr	x2, .LC902
	mov	w3, 2614
	ldr	x4, .LC904
	mov	w0, 0
	ldr	x1, .LC903
	add	x2, x2, 1400
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1852
.L1855:
	ldr	x2, .LC902
	mov	w3, 2615
	ldr	x4, .LC906
	mov	w21, -1
	ldr	x1, .LC903
	add	x2, x2, 1400
	bl	dprint_vfmw
	b	.L1852
.L1853:
	ldr	x2, .LC902
	mov	w3, 2613
	ldr	x4, .LC901
	mov	w0, 0
	ldr	x1, .LC903
	add	x2, x2, 1400
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1852
.L1838:
	ldr	x1, .LC918
	mov	w0, w25
	mov	w21, -1
	bl	dprint_vfmw
	b	.L1852
	.size	VCTRL_ConfigChan, .-VCTRL_ConfigChan
	.align	3
.LC901:
	.xword	.LC900
	.align	3
.LC902:
	.xword	.LANCHOR4
	.align	3
.LC903:
	.xword	.LC6
	.align	3
.LC904:
	.xword	.LC376
	.align	3
.LC905:
	.xword	.LANCHOR1
	.align	3
.LC906:
	.xword	.LC381
	.align	3
.LC907:
	.xword	.LC250
	.align	3
.LC909:
	.xword	.LC908
	.align	3
.LC910:
	.xword	.LANCHOR5
	.align	3
.LC912:
	.xword	.LC911
	.align	3
.LC914:
	.xword	.LC913
	.align	3
.LC915:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC916:
	.xword	.LANCHOR2
	.align	3
.LC918:
	.xword	.LC917
	.align	3
.LC919:
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
	ldr	x1, .LC924
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC925
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbz	w0, .L1871
	ldr	x1, .LC927
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L1871:
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 172]
	bl	VCTRL_ConfigChan
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetUvmosEnable, .-VfmwProc_SetUvmosEnable
	.align	3
.LC924:
	.xword	.LC923
	.align	3
.LC925:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC927:
	.xword	.LC926
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
	ldr	x1, .LC929
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC930
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1872
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 72]
	bl	VCTRL_ConfigChan
.L1872:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetDropStreamThread, .-VfmwProc_SetDropStreamThread
	.align	3
.LC929:
	.xword	.LC928
	.align	3
.LC930:
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
	ldr	x1, .LC932
	lsr	w20, w3, 24
	and	w19, w3, 7
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC933
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbz	w0, .L1877
	ldr	x1, .LC935
	mov	w2, w20
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.p2align 3
.L1877:
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 76]
	bl	VCTRL_ConfigChan
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetDecMode, .-VfmwProc_SetDecMode
	.align	3
.LC932:
	.xword	.LC931
	.align	3
.LC933:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC935:
	.xword	.LC934
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
	ldr	x1, .LC937
	lsr	w20, w3, 24
	and	w19, w3, 3
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC938
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1878
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 80]
	bl	VCTRL_ConfigChan
.L1878:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetDecOrderOutput, .-VfmwProc_SetDecOrderOutput
	.align	3
.LC937:
	.xword	.LC936
	.align	3
.LC938:
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
	ldr	x1, .LC940
	lsr	w20, w3, 24
	and	w19, w3, 16777215
	mov	w3, w19
	mov	w2, w20
	bl	dprint_vfmw
	ldr	x3, .LC941
	mov	w1, 0
	mov	x2, 148
	add	x0, x29, 40
	ldr	x3, [x3, 96]
	blr	x3
	add	x1, x29, 40
	mov	w0, w20
	bl	VCTRL_GetChanCfg
	cbnz	w0, .L1880
	add	x1, x29, 40
	mov	w0, w20
	str	w19, [x29, 68]
	bl	VCTRL_ConfigChan
.L1880:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 192
	ret
	.size	VfmwProc_SetErrorThread, .-VfmwProc_SetErrorThread
	.align	3
.LC940:
	.xword	.LC939
	.align	3
.LC941:
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
	ldr	x1, .LC943
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestResetChan, .-VfmwProc_TestResetChan
	.align	3
.LC943:
	.xword	.LC942
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
	ldr	x20, .LC944
	mov	w0, 0
	ldr	x1, [x20, 24]
	blr	x1
	cmp	w19, 31
	bhi	.L1894
	ldr	x21, .LC949
	ldr	x0, [x21, w19, sxtw 3]
	cbz	x0, .L1895
	ldr	w22, [x0, 4]
	cmp	w22, 1
	bne	.L1896
	str	wzr, [x0, 8]
	mov	w0, 0
	ldr	x1, [x20, 32]
	blr	x1
	mov	w0, w19
	bl	SCDDRV_IsChanDec
	cbnz	w0, .L1897
.L1888:
	ldr	x1, [x20, 24]
	mov	w0, 0
	sxtw	x22, w19
	blr	x1
	ldr	x2, .LC954
	mov	w0, 4
	ldr	x1, [x20, 24]
	str	wzr, [x2, w19, sxtw 2]
	blr	x1
	mov	w0, w19
	bl	VCTRL_StopChan
	ldr	x1, [x20, 32]
	cbnz	w0, .L1898
	mov	w0, 4
	lsl	x22, x22, 4
	blr	x1
	mov	w0, w19
	bl	VCTRL_ResetChan
	bl	VDMDRV_ParamInit
	ldr	x1, .LC955
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
	ldr	x4, .LC956
	add	x3, x1, 311296
	add	x2, x1, 307200
	ldr	w5, [x1, 408]
	add	x2, x2, 1528
	str	w5, [x29, 116]
	ldr	w5, [x1, 400]
	str	w5, [x29, 108]
	ldr	w5, [x1, 404]
	ldr	w23, [x3, 1592]
	str	w5, [x29, 112]
	ldr	w5, [x3, 1556]
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
.L1885:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L1897:
	mov	w0, w19
	ldr	x23, [x20, 264]
	bl	SCDDRV_IsChanDec
	cmp	w0, wzr
	mov	w2, 500
	cset	w1, eq
	mov	w0, w22
	blr	x23
	b	.L1888
	.p2align 3
.L1896:
	ldr	x2, .LC946
	mov	w3, 2222
	ldr	x4, .LC953
	mov	w0, 0
	ldr	x1, .LC948
	add	x2, x2, 1424
.L1893:
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
.L1898:
	mov	w0, 4
	blr	x1
	ldr	x1, [x20, 32]
	mov	w0, 0
	blr	x1
	mov	w0, -1
	b	.L1885
	.p2align 3
.L1894:
	ldr	x2, .LC946
	mov	w3, 2208
	ldr	x4, .LC945
	mov	w0, 0
	ldr	x1, .LC948
	add	x2, x2, 1424
	b	.L1893
.L1895:
	ldr	x2, .LC946
	mov	w3, 2215
	ldr	x4, .LC951
	ldr	x1, .LC948
	add	x2, x2, 1424
	b	.L1893
	.size	VCTRL_DestroyChan, .-VCTRL_DestroyChan
	.align	3
.LC944:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC945:
	.xword	.LC193
	.align	3
.LC946:
	.xword	.LANCHOR4
	.align	3
.LC948:
	.xword	.LC947
	.align	3
.LC949:
	.xword	.LANCHOR1
	.align	3
.LC951:
	.xword	.LC950
	.align	3
.LC953:
	.xword	.LC952
	.align	3
.LC954:
	.xword	g_LowDelaySeqIndex
	.align	3
.LC955:
	.xword	.LANCHOR5
	.align	3
.LC956:
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
	ldr	x20, .LC959
	ldr	w0, [x20, 256]
	cmp	w0, 1
	bne	.L1906
	mov	x19, 0
	.p2align 2
.L1902:
	ldr	x1, [x20, x19, lsl 3]
	mov	w0, w19
	add	x19, x19, 1
	cbz	x1, .L1901
	bl	VCTRL_DestroyChan
.L1901:
	cmp	x19, 32
	bne	.L1902
	bl	FSP_Exit
	ldr	x21, .LC960
	ldr	w1, [x20, 260]
	mov	w2, 3
	str	w2, [x20, 264]
	cbz	w1, .L1904
	ldr	x1, [x21, 240]
	mov	w0, 10
	mov	w19, 49
	blr	x1
	b	.L1905
	.p2align 3
.L1916:
	ldr	x1, [x21, 240]
	blr	x1
	subs	w19, w19, #1
	beq	.L1904
.L1905:
	ldr	w1, [x20, 260]
	mov	w0, 10
	cbnz	w1, .L1916
.L1904:
	ldr	x0, .LC961
	mov	x2, 128
	ldr	x3, [x21, 96]
	mov	w1, 0
	add	x0, x0, 264
	blr	x3
	add	x0, x20, 288
	bl	CloseDrivers
	str	wzr, [x20, 256]
	mov	w0, 0
.L1915:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1906:
	mov	w0, -1
	b	.L1915
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	3
.LC959:
	.xword	.LANCHOR1
	.align	3
.LC960:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC961:
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
	ldr	x1, .LC964
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, w19
	bl	VCTRL_ResetChan
	mov	w3, w0
	ldr	x1, .LC965
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, w19
	bl	VCTRL_StartChan
	mov	w3, w0
	ldr	x1, .LC966
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestRestartChan, .-VfmwProc_TestRestartChan
	.align	3
.LC964:
	.xword	.LC963
	.align	3
.LC965:
	.xword	.LC942
	.align	3
.LC966:
	.xword	.LC833
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
	ldr	x1, .LC967
	mov	w2, w19
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VfmwProc_TestStopChan, .-VfmwProc_TestStopChan
	.align	3
.LC967:
	.xword	.LC963
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
	beq	.L1929
	mov	w19, 2
	cmp	w20, wzr
	csel	w19, w19, wzr, eq
.L1920:
	ldr	x0, .LC968
	ldrb	w0, [x0]
	cmp	w0, 1
	beq	.L1931
	mov	w1, w19
	mov	w0, 0
	bl	VDH_Require_DspCode
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1931:
	ldr	x20, .LC969
	ldr	x1, [x20, 8]
	cbz	x1, .L1932
	mov	w0, 0
	blr	x1
.L1923:
	ldr	x1, [x20, 40]
	cbz	x1, .L1933
	mov	w0, 0
	blr	x1
.L1925:
	ldr	x1, [x20, 24]
	cbz	x1, .L1934
	mov	w0, 0
	blr	x1
.L1927:
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
.L1929:
	mov	w19, 1
	b	.L1920
	.p2align 3
.L1932:
	ldr	x1, .LC970
	mov	w2, 2876
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1923
	.p2align 3
.L1933:
	ldr	x1, .LC970
	mov	w2, 2877
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1925
	.p2align 3
.L1934:
	ldr	x1, .LC970
	mov	w2, 2878
	mov	w0, 0
	bl	dprint_vfmw
	b	.L1927
	.size	VCTRL_InitDspCode, .-VCTRL_InitDspCode
	.align	3
.LC968:
	.xword	g_HalDisable
	.align	3
.LC969:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC970:
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
	ldr	x0, .LC971
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w1, [x0, 632]
	cbnz	w1, .L1947
	ldr	w21, [x0, 1316]
	mov	w0, 0
	cmp	w21, wzr
	cset	w3, eq
	cmp	w1, 6
	cset	w2, ne
	tst	w3, w2
	beq	.L1966
.L1953:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1947:
	cmp	w1, 6
	mov	w3, 1
	cset	w2, ne
	mov	w21, 0
	tst	w3, w2
	mov	w0, 0
	bne	.L1953
.L1966:
	ldr	x20, .LC972
	add	x0, x20, 268
	add	x3, x20, 392
	ldr	w2, [x20, 264]
	cbz	w2, .L1938
	b	.L1937
	.p2align 3
.L1968:
	beq	.L1967
.L1938:
	ldr	w2, [x0]
	add	x0, x0, 4
	cmp	x3, x0
	cbz	w2, .L1968
.L1937:
	cmp	w2, 1
	beq	.L1969
	cmp	w1, 6
	mov	w0, 0
	beq	.L1953
	ldr	x1, .LC976
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1953
	.p2align 3
.L1967:
	mov	w0, w19
	bl	VCTRL_InitDspCode
	cmp	w21, 1
	beq	.L1970
	add	x20, x20, 264
	mov	w1, 2
	mov	w0, 0
	str	w1, [x20, w19, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L1970:
	add	x20, x20, 264
	mov	w0, 0
	str	w21, [x20, w19, sxtw 2]
	b	.L1953
	.p2align 3
.L1969:
	cmp	w21, 1
	mov	w0, 0
	beq	.L1953
	ldr	x1, .LC974
	bl	dprint_vfmw
	mov	w0, -1
	b	.L1953
	.size	VCTRL_LoadDspCode, .-VCTRL_LoadDspCode
	.align	3
.LC971:
	.xword	.LANCHOR1
	.align	3
.LC972:
	.xword	.LANCHOR5
	.align	3
.LC974:
	.xword	.LC973
	.align	3
.LC976:
	.xword	.LC975
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
	ldr	x0, .LC979
	ldr	x0, [x0, w20, sxtw 3]
	add	x0, x0, 278528
	str	w19, [x0, 2152]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_SetChanFsPartitionState, .-VCTRL_SetChanFsPartitionState
	.align	3
.LC979:
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
	ldr	x0, .LC980
	ldr	x0, [x0, w19, sxtw 3]
	ldr	x19, [sp, 16]
	add	x0, x0, 307200
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 1500]
	ret
	.size	VCTRL_GetCurChanFsSize, .-VCTRL_GetCurChanFsSize
	.align	3
.LC980:
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
	beq	.L1975
	cbz	w19, .L1976
	cmp	w19, 2
	bne	.L1984
	ldr	x0, .LC981
	add	x0, x0, 1672
	ldr	w1, [x0, w20, sxtw 2]
	cmp	w1, 1
	beq	.L1980
.L1982:
	str	w19, [x0, w20, sxtw 2]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1984:
	mov	w0, 0
.L1974:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1976:
	ldr	x1, .LC981
	mov	w0, 0
	add	x1, x1, 1672
	str	wzr, [x1, w20, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L1975:
	ldr	x0, .LC981
	add	x0, x0, 1672
	ldr	w1, [x0, w20, sxtw 2]
	cbz	w1, .L1982
.L1980:
	mov	w0, -1
	b	.L1974
	.size	VCTRT_SetChanCtrlState, .-VCTRT_SetChanCtrlState
	.align	3
.LC981:
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
	beq	.L1986
	ldr	w2, [x19, 12]
	ldr	w0, [x19, 32]
	ldr	x1, [x19, 24]
	bl	MEM_AddMemRecord
.L1986:
	ldr	w0, [x19, 4]
	cmp	w0, 255
	beq	.L1987
	ldr	w2, [x19, 16]
	ldr	w0, [x19, 48]
	ldr	x1, [x19, 40]
	bl	MEM_AddMemRecord
.L1987:
	ldr	w0, [x19, 8]
	cmp	w0, 255
	beq	.L1985
	ldr	w2, [x19, 20]
	ldr	w0, [x19, 64]
	ldr	x1, [x19, 56]
	bl	MEM_AddMemRecord
.L1985:
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
	ldr	x21, .LC983
	ldr	w4, [x20, 12]
	ldr	x0, [x21, w19, sxtw 3]
	add	x1, x0, 311296
	add	x0, x0, 307200
	ldr	w5, [x1, 976]
	cmp	w5, w4
	beq	.L1999
	ldr	w2, [x0, 1496]
	cbz	w2, .L2028
.L1999:
	ldr	w0, [x0, 3888]
	cbz	w0, .L2001
	ldr	w0, [x1, 1008]
	cbz	w0, .L2029
.L2001:
	ldr	x22, .LC989
	mov	w0, 8
	ldr	x1, [x22, 24]
	blr	x1
	ldr	x4, [x21, w19, sxtw 3]
	add	x2, x4, 307200
	ldr	w0, [x2, 1528]
	cmp	w0, 255
	beq	.L2009
	add	x2, x2, 1600
	mov	x1, 1
	b	.L2003
	.p2align 3
.L2031:
	add	w1, w1, 1
	cmp	w1, 32
	beq	.L2030
.L2003:
	ldr	w3, [x2]
	add	x2, x2, 72
	cmp	w3, 255
	bne	.L2031
.L2002:
	lsl	x0, x1, 6
	ldr	x3, [x22, 104]
	add	x0, x0, x1, lsl 3
	mov	x2, 72
	add	x0, x0, 307200
	mov	x1, x20
	add	x0, x4, x0
	add	x0, x0, 1528
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	x0, x20
	add	x1, x1, 311296
	ldr	w2, [x1, 1008]
	add	w2, w2, 1
	str	w2, [x1, 1008]
	bl	VCTRL_AddFrameBufMemoryRecord
	ldr	x0, [x21, w19, sxtw 3]
	add	x0, x0, 311296
	ldr	w0, [x0, 1012]
	cbnz	w0, .L2032
.L2007:
	mov	w19, 0
.L2006:
	ldr	x1, [x22, 32]
	mov	w0, 8
	blr	x1
	mov	w0, w19
.L2022:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L2029:
	ldr	w5, [x20, 8]
	cmp	w5, 255
	bne	.L2001
	ldr	x2, .LC984
	mov	w4, 0
	ldr	x1, .LC988
	mov	w3, 8182
	add	x2, x2, 1448
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2022
	.p2align 3
.L2030:
	ldr	x2, .LC984
	ldr	x1, .LC993
.L2025:
	mov	w3, w19
	add	x2, x2, 1448
	mov	w0, 1
	mov	w19, -1
	bl	dprint_vfmw
	b	.L2006
	.p2align 3
.L2032:
	mov	x1, x20
	mov	w0, w19
	bl	FSP_SetSingleFrameBuf
	cbz	w0, .L2007
	ldr	x2, .LC984
	ldr	x1, .LC991
	b	.L2025
.L2009:
	mov	x1, 0
	b	.L2002
.L2028:
	ldr	x2, .LC984
	mov	w3, 8172
	ldr	x1, .LC986
	mov	w0, 1
	add	x2, x2, 1448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L2022
	.size	VCTRL_SetSingleFrameBufToChan, .-VCTRL_SetSingleFrameBufToChan
	.align	3
.LC983:
	.xword	.LANCHOR1
	.align	3
.LC984:
	.xword	.LANCHOR4
	.align	3
.LC986:
	.xword	.LC985
	.align	3
.LC988:
	.xword	.LC987
	.align	3
.LC989:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC991:
	.xword	.LC990
	.align	3
.LC993:
	.xword	.LC992
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
	ldr	x21, .LC994
	add	x3, x21, 1672
	ldr	w0, [x3, w19, sxtw 2]
	cbz	w0, .L2043
	ldr	x2, .LC1001
	mov	w3, w19
	ldr	x1, .LC1003
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
.L2043:
	ldr	x23, .LC995
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
	ldr	x22, .LC996
	mov	w20, w0
	ldr	x0, [x22, w19, sxtw 3]
	add	x2, x0, 278528
	cbnz	w20, .L2044
.L2036:
	ldr	x1, .LC1000
	mov	w3, 2
	mov	w0, 31
	str	w3, [x2, 2152]
	bl	dprint_vfmw
	ldr	x0, [x22, w19, sxtw 3]
	add	x0, x0, 311296
	ldr	w0, [x0, 1612]
	cmp	w0, 1
	beq	.L2045
.L2037:
	add	x21, x21, 1672
	mov	w0, w20
	str	wzr, [x21, w19, sxtw 2]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 144
	ret
	.p2align 3
.L2044:
	add	x1, x0, 307200
	add	x2, x0, 278528
	ldr	w0, [x1, 1500]
	cbz	w0, .L2036
	ldr	x1, .LC998
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x0, [x22, w19, sxtw 3]
	mov	w1, 3
	add	x2, x0, 278528
	str	w1, [x2, 2152]
	b	.L2036
	.p2align 3
.L2045:
	ldr	x1, [x23, 256]
	mov	w0, 0
	blr	x1
	ldr	x0, [x22, w19, sxtw 3]
	add	x0, x0, 311296
	str	wzr, [x0, 1612]
	b	.L2037
	.size	VCTRL_AllocMemToDecoder, .-VCTRL_AllocMemToDecoder
	.align	3
.LC994:
	.xword	.LANCHOR5
	.align	3
.LC995:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC996:
	.xword	.LANCHOR1
	.align	3
.LC998:
	.xword	.LC997
	.align	3
.LC1000:
	.xword	.LC999
	.align	3
.LC1001:
	.xword	.LANCHOR4
	.align	3
.LC1003:
	.xword	.LC1002
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
	ldr	x3, .LC1005
	mov	x2, 24
	mov	w1, 0
	add	x0, x29, 56
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x0, .LC1006
	ldr	x6, [x0, 104]
	cbz	x6, .L2047
	ldr	x4, .LC1007
	add	x5, x29, 56
	mov	w3, 0
	mov	w2, w21
	mov	w1, w20
	mov	w0, w19
	ldr	x4, [x4, w19, sxtw 3]
	add	x4, x4, 311296
	ldr	w4, [x4, 1616]
	blr	x6
.L2047:
	ldr	w0, [x29, 60]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VCTRL_GetFsSize, .-VCTRL_GetFsSize
	.align	3
.LC1005:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC1006:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC1007:
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
	ldr	x0, .LC1008
	mov	w1, 1
	add	x0, x0, 2080
	str	w1, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_EnableEsBuf, .-VCTRL_EnableEsBuf
	.align	3
.LC1008:
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
	ldr	x0, .LC1010
	add	x0, x0, 2080
	str	wzr, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_DisableEsBuf, .-VCTRL_DisableEsBuf
	.align	3
.LC1010:
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
	ldr	x0, .LC1012
	add	x0, x0, 2080
	ldr	w0, [x0, w19, sxtw 2]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VCTRL_IfEsBufEnable, .-VCTRL_IfEsBufEnable
	.align	3
.LC1012:
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
	.type	__func__.51477, %object
	.size	__func__.51477, 18
__func__.51477:
	.string	"VCTRL_EventReport"
	.zero	6
	.type	__func__.52639, %object
	.size	__func__.52639, 24
__func__.52639:
	.string	"VCTRL_SetLastFrameState"
	.type	__func__.51416, %object
	.size	__func__.51416, 20
__func__.51416:
	.string	"VCTRL_RecordPosTime"
	.zero	4
	.type	__func__.51421, %object
	.size	__func__.51421, 17
__func__.51421:
	.string	"VCTRL_RecordData"
	.zero	7
	.type	__func__.51468, %object
	.size	__func__.51468, 23
__func__.51468:
	.string	"VCTRL_SetMoreGapEnable"
	.zero	1
	.type	__func__.51489, %object
	.size	__func__.51489, 18
__func__.51489:
	.string	"VCTRL_SetCallBack"
	.zero	6
	.type	__func__.51529, %object
	.size	__func__.51529, 25
__func__.51529:
	.string	"VCTRL_SetStreamInterface"
	.zero	7
	.type	__func__.51534, %object
	.size	__func__.51534, 29
__func__.51534:
	.string	"VCTRL_SetSendStreamAgainFlag"
	.zero	3
	.type	__func__.51538, %object
	.size	__func__.51538, 29
__func__.51538:
	.string	"VCTRL_GetSendStreamAgainFlag"
	.zero	3
	.type	__func__.51548, %object
	.size	__func__.51548, 20
__func__.51548:
	.string	"VCTRL_GetStreamSize"
	.zero	4
	.type	__func__.51555, %object
	.size	__func__.51555, 20
__func__.51555:
	.string	"VCTRL_CheckFreshRaw"
	.zero	4
	.type	__func__.51562, %object
	.size	__func__.51562, 20
__func__.51562:
	.string	"VCTRL_CheckFreshSeg"
	.zero	4
	.type	__func__.51567, %object
	.size	__func__.51567, 25
__func__.51567:
	.string	"VCTRL_SetDiscardPicParam"
	.zero	7
	.type	__FUNCTION__.51595, %object
	.size	__FUNCTION__.51595, 29
__FUNCTION__.51595:
	.string	"VCTRL_PartitionMemForStdUser"
	.zero	3
	.type	__func__.51610, %object
	.size	__func__.51610, 21
__func__.51610:
	.string	"DelAllFrameMemRecord"
	.zero	3
	.type	__func__.51620, %object
	.size	__func__.51620, 23
__func__.51620:
	.string	"VCTRL_FreeChanResource"
	.zero	1
	.type	__func__.51746, %object
	.size	__func__.51746, 17
__func__.51746:
	.string	"VCTRL_GetChanCfg"
	.zero	7
	.type	__func__.51807, %object
	.size	__func__.51807, 14
__func__.51807:
	.string	"VCTRL_SeekPts"
	.zero	2
	.type	__func__.51840, %object
	.size	__func__.51840, 20
__func__.51840:
	.string	"VCTRL_ReleaseStream"
	.zero	4
	.type	__func__.51860, %object
	.size	__func__.51860, 24
__func__.51860:
	.string	"VCTRL_ImageOutputEnable"
	.type	__func__.51899, %object
	.size	__func__.51899, 25
__func__.51899:
	.string	"VCTRL_TryToRelSpecialFrm"
	.zero	7
	.type	__func__.51923, %object
	.size	__func__.51923, 19
__func__.51923:
	.string	"VCTRL_GetChanImage"
	.zero	5
	.type	__FUNCTION__.51931, %object
	.size	__FUNCTION__.51931, 19
__FUNCTION__.51931:
	.string	"VCTRL_GetChanImage"
	.zero	5
	.type	__func__.51938, %object
	.size	__func__.51938, 23
__func__.51938:
	.string	"VCTRL_ReleaseChanImage"
	.zero	1
	.type	__FUNCTION__.51942, %object
	.size	__FUNCTION__.51942, 23
__FUNCTION__.51942:
	.string	"VCTRL_ReleaseChanImage"
	.zero	1
	.type	__func__.51950, %object
	.size	__func__.51950, 23
__func__.51950:
	.string	"VCTRL_GetHDRConfigInfo"
	.zero	1
	.type	__func__.51976, %object
	.size	__func__.51976, 18
__func__.51976:
	.string	"VCTRL_GetDecParam"
	.align	3
.LANCHOR4 = . + 0
	.type	__func__.52058, %object
	.size	__func__.52058, 20
__func__.52058:
	.string	"VCTRL_ClearDecparam"
	.zero	4
	.type	__func__.52087, %object
	.size	__func__.52087, 21
__func__.52087:
	.string	"VCTRL_VdmProcSedOnly"
	.zero	3
	.type	__func__.52095, %object
	.size	__func__.52095, 21
__func__.52095:
	.string	"VCTRL_GetImageBuffer"
	.zero	3
	.type	__func__.52118, %object
	.size	__func__.52118, 22
__func__.52118:
	.string	"VCTRL_ConfigFFFBSpeed"
	.zero	2
	.type	__func__.52123, %object
	.size	__func__.52123, 20
__func__.52123:
	.string	"VCTRL_ConfigPVRInfo"
	.zero	4
	.type	__func__.52127, %object
	.size	__func__.52127, 19
__func__.52127:
	.string	"VCTRL_IsChanActive"
	.zero	5
	.type	__func__.52133, %object
	.size	__func__.52133, 13
__func__.52133:
	.string	"USERDEC_Init"
	.zero	3
	.type	__func__.52152, %object
	.size	__func__.52152, 21
__func__.52152:
	.string	"VCTRL_GetUsrdecFrame"
	.zero	3
	.type	__func__.52162, %object
	.size	__func__.52162, 14
__func__.52162:
	.string	"InitSyntaxCtx"
	.zero	2
	.type	__func__.51498, %object
	.size	__func__.51498, 15
__func__.51498:
	.string	"VCTRL_OpenVfmw"
	.zero	1
	.type	__FUNCTION__.52369, %object
	.size	__FUNCTION__.52369, 18
__FUNCTION__.52369:
	.string	"GetExtraRefFrmNum"
	.zero	6
	.type	__FUNCTION__.52375, %object
	.size	__FUNCTION__.52375, 19
__FUNCTION__.52375:
	.string	"GetExtraDispFrmNum"
	.zero	5
	.type	__FUNCTION__.52381, %object
	.size	__FUNCTION__.52381, 16
__FUNCTION__.52381:
	.string	"GetExtraCtrlCmd"
	.type	__func__.52315, %object
	.size	__func__.52315, 14
__func__.52315:
	.string	"DecChanSyntax"
	.zero	2
	.type	__FUNCTION__.52316, %object
	.size	__FUNCTION__.52316, 14
__FUNCTION__.52316:
	.string	"DecChanSyntax"
	.zero	2
	.type	__func__.51849, %object
	.size	__func__.51849, 24
__func__.51849:
	.string	"VCTRL_FindOccupiedFrame"
	.type	__func__.51870, %object
	.size	__func__.51870, 26
__func__.51870:
	.string	"VCTRL_ReportOccupiedFrame"
	.zero	6
	.type	__func__.52346, %object
	.size	__func__.52346, 20
__func__.52346:
	.string	"VCTRL_GetChanImgNum"
	.zero	4
	.type	__func__.51578, %object
	.size	__func__.51578, 19
__func__.51578:
	.string	"VCTRL_GetChanState"
	.zero	5
	.type	__func__.52350, %object
	.size	__func__.52350, 19
__func__.52350:
	.string	"VCTRL_GetChanWidth"
	.zero	5
	.type	__func__.52354, %object
	.size	__func__.52354, 20
__func__.52354:
	.string	"VCTRL_GetChanHeight"
	.zero	4
	.type	__func__.52358, %object
	.size	__func__.52358, 22
__func__.52358:
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
	.type	__func__.52654, %object
	.size	__func__.52654, 22
__func__.52654:
	.string	"VCTRL_OutputLastFrame"
	.zero	2
	.type	__func__.52033, %object
	.size	__func__.52033, 15
__func__.52033:
	.string	"VCTRL_PostProc"
	.zero	1
	.type	__func__.52082, %object
	.size	__func__.52082, 18
__func__.52082:
	.string	"VCTRL_VdmPostProc"
	.zero	6
	.type	__func__.52680, %object
	.size	__func__.52680, 21
__func__.52680:
	.string	"VCTRL_SvdecLastFrame"
	.zero	3
	.type	__func__.52158, %object
	.size	__func__.52158, 21
__func__.52158:
	.string	"VCTRL_PutUsrdecFrame"
	.zero	3
	.type	__func__.51725, %object
	.size	__func__.51725, 16
__func__.51725:
	.string	"VCTRL_StartChan"
	.type	__func__.51741, %object
	.size	__func__.51741, 15
__func__.51741:
	.string	"VCTRL_StopChan"
	.zero	1
	.type	__func__.51834, %object
	.size	__func__.51834, 26
__func__.51834:
	.string	"VCTRL_ResetChanWithOption"
	.zero	6
	.type	__func__.51913, %object
	.size	__func__.51913, 16
__func__.51913:
	.string	"VCTRL_ResetChan"
	.type	__func__.51792, %object
	.size	__func__.51792, 17
__func__.51792:
	.string	"VCTRL_ConfigChan"
	.zero	7
	.type	__func__.51719, %object
	.size	__func__.51719, 18
__func__.51719:
	.string	"VCTRL_DestroyChan"
	.zero	6
	.type	__func__.52775, %object
	.size	__func__.52775, 30
__func__.52775:
	.string	"VCTRL_SetSingleFrameBufToChan"
	.zero	2
	.type	__func__.52787, %object
	.size	__func__.52787, 24
__func__.52787:
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
.LC708:
	ASCII(.string	"%s not support std %d\n" )
	.zero	1
.LC712:
	ASCII(.string	"pstChanState = NULL" )
	.zero	4
.LC737:
	ASCII(.string	"SetVdecExtra ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\n" )
	.zero	1
.LC739:
	ASCII(.string	"SetVdecExtra ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\n" )
.LC748:
	ASCII(.string	"Command \"%d\" not registerd!\n" )
	.zero	3
.LC754:
	ASCII(.string	"Chan %d Report Last Frame, Value=%d, LastFrameState=%d\n" )
.LC762:
	ASCII(.string	"Last frame output failed!\n" )
	.zero	5
.LC764:
	ASCII(.string	"Last frame output successed!\n" )
	.zero	2
.LC766:
	ASCII(.string	"Last frame already output, image id: %d!\n" )
	.zero	6
.LC783:
	ASCII(.string	"line %d can not know YuvFormat = %d\n" )
	.zero	3
.LC785:
	ASCII(.string	"userdec frame(phy=%#x) address error!\n" )
	.zero	1
.LC787:
	ASCII(.string	"can not map vir addr for usrdat frame(cbphy=%#x)\n" )
	.zero	6
.LC789:
	ASCII(.string	"line: %d, pLogic is Null!\n" )
	.zero	5
.LC792:
	ASCII(.string	"eYuvFormat %d is not support!!\n" )
.LC799:
	ASCII(.string	"pUsrdecFrame == NULL" )
	.zero	3
.LC801:
	ASCII(.string	"VCTRL_PutUsrdecFrame: VidStd is %d\n" )
	.zero	4
.LC804:
	ASCII(.string	"VCTRL_PutUsrdecFrame return err\n" )
	.zero	7
.LC806:
	ASCII(.string	"L:%d ChanID out of range\n" )
	.zero	6
.LC809:
	ASCII(.string	"L:%d This Chan has not been created!!!\n" )
.LC811:
	ASCII(.string	"L:%d WARNING: vidio std not setted!\n" )
	.zero	3
.LC823:
	ASCII(.string	"WARNING: vidio std not setted!" )
	.zero	1
.LC833:
	ASCII(.string	"start chan %d: VCTRL_StartChan return %d\n" )
	.zero	6
.LC844:
	ASCII(.string	"This Chan has not been created or has been destroyed !" )
	.zero	1
.LC847:
	ASCII(.string	"VCTRL_StopChanWithCheck fail!\n" )
	.zero	1
.LC854:
	ASCII(.string	"vdm_ctrl.c,L%d: pOption->s32KeepBS error\n" )
	.zero	6
.LC858:
	ASCII(.string	"-------------------------------------------------------------------------\n" )
	.zero	5
.LC873:
	ASCII(.string	"Param Invalid of PChanOption is NULL\n" )
	.zero	2
.LC876:
	ASCII(.string	"line %d VCTRL_GetChanMemSize failed!\n" )
	.zero	2
.LC879:
	ASCII(.string	"ChanID: %d is out of range!\n" )
	.zero	3
.LC881:
	ASCII(.string	"vfmw have max(%d) channels opened, can NOT create more channels\n" )
	.zero	7
.LC883:
	ASCII(.string	"L: %d : part we can NOT alloc buffer for channel context\n" )
	.zero	6
.LC885:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel context\n" )
	.zero	6
.LC887:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel vdh\n" )
	.zero	2
.LC889:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel vdh, %#x < %#x\n" )
	.zero	7
.LC891:
	ASCII(.string	"L: %d : can NOT alloc buffer for channel scd\n" )
	.zero	2
.LC893:
	ASCII(.string	"L: %d : can NOT alloc buffer for SCD\n" )
	.zero	2
.LC896:
	ASCII(.string	"Chan:%d can NOT enable FSP instance\n" )
	.zero	3
.LC900:
	ASCII(.string	"pstCfg = NULL" )
	.zero	2
.LC908:
	ASCII(.string	"VCTRL_CheckChanWH return err.\n" )
	.zero	1
.LC911:
	ASCII(.string	"VFMW didn't support std %d.\n" )
	.zero	3
.LC913:
	ASCII(.string	"VCTRL_ConfigChan with same config paramater.\n" )
	.zero	2
.LC917:
	ASCII(.string	"can NOT VCTRL_PartitionMemForStdUser\n" )
	.zero	2
.LC923:
	ASCII(.string	"chan %d: new UvmosEnable = %d\n" )
	.zero	1
.LC926:
	ASCII(.string	"chan %d: SetUvmosEnable failed!\n" )
	.zero	7
.LC928:
	ASCII(.string	"chan %d: new StrmOFThr = %d\n" )
	.zero	3
.LC931:
	ASCII(.string	"chan %d: new DecMode = %d\n" )
	.zero	5
.LC934:
	ASCII(.string	"chan %d: GetChanCfg failed!\n" )
	.zero	3
.LC936:
	ASCII(.string	"chan %d: new DecOrderOutput = %d\n" )
	.zero	6
.LC939:
	ASCII(.string	"chan %d: new ChanErrThr = %d\n" )
	.zero	2
.LC942:
	ASCII(.string	"reset chan %d: VCTRL_ResetChan return %d\n" )
	.zero	6
.LC947:
	ASCII(.string	"%s:L%d: %s\n" )
	.zero	4
.LC950:
	ASCII(.string	"This Chan has not been created or has been destroyed !!!" )
	.zero	7
.LC952:
	ASCII(.string	"can NOT stop a not-opened Chan" )
	.zero	1
.LC963:
	ASCII(.string	"stop chan %d: VCTRL_StopChan return %d\n" )
.LC973:
	ASCII(.string	"WARNNING: dsp in lowdelay state, we can not supported  avs in the same time!!!\n" )
.LC975:
	ASCII(.string	"WARNNING: dsp in avs state, we can not supported  lowdelay in the same time!!!\n" )
.LC985:
	ASCII(.string	"%s, %d, actul size = 0x%x, except size= 0x%x\n" )
	.zero	2
.LC987:
	ASCII(.string	"%s, %d, CfgFrameNum = %x, PmvNodeStatus= 0x%x\n" )
	.zero	1
.LC990:
	ASCII(.string	"%s: Chan %d set single frame failed!\n" )
	.zero	2
.LC992:
	ASCII(.string	"%s: Chan %d no frame buffer store!\n" )
	.zero	4
.LC997:
	ASCII(.string	"DFS, request frame store fail!, chanid: %d\n" )
	.zero	4
.LC999:
	ASCII(.string	"DFS, set decoding thread state to success!\n " )
	.zero	3
.LC1002:
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
	.type	save_file_cnt.52517, %object
	.size	save_file_cnt.52517, 4
save_file_cnt.52517:
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
	.type	save_file_cnt.52511, %object
	.size	save_file_cnt.52511, 4
save_file_cnt.52511:
	.zero	4
	.type	save_metadata_reorder_chan_num, %object
	.size	save_metadata_reorder_chan_num, 4
save_metadata_reorder_chan_num:
	.zero	4
	.type	vfmw_save_metadata_file, %object
	.size	vfmw_save_metadata_file, 256
vfmw_save_metadata_file:
	.zero	256
	.type	save_file_cnt.52505, %object
	.size	save_file_cnt.52505, 4
save_file_cnt.52505:
	.zero	4
	.type	save_metadata_chan_num, %object
	.size	save_metadata_chan_num, 4
save_metadata_chan_num:
	.zero	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 256
vfmw_save_seg_file:
	.zero	256
	.type	save_file_cnt.52483, %object
	.size	save_file_cnt.52483, 4
save_file_cnt.52483:
	.zero	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.zero	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 256
vfmw_save_str_file:
	.zero	256
	.type	save_file_cnt.52477, %object
	.size	save_file_cnt.52477, 4
save_file_cnt.52477:
	.zero	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.zero	4
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 256
vfmw_save_yuv_file:
	.zero	256
	.type	save_file_cnt.52490, %object
	.size	save_file_cnt.52490, 4
save_file_cnt.52490:
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
	.type	FspInstInfo.51591, %object
	.size	FspInstInfo.51591, 2824
FspInstInfo.51591:
	.zero	2824
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.zero	4
	.zero	4
	.type	last_rec_pos_time.51928, %object
	.size	last_rec_pos_time.51928, 128
last_rec_pos_time.51928:
	.zero	128
	.type	last_rec_pos_time.51939, %object
	.size	last_rec_pos_time.51939, 128
last_rec_pos_time.51939:
	.zero	128
	.type	MemArrange.52192, %object
	.size	MemArrange.52192, 1232
MemArrange.52192:
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
	.type	last_rec_pos_time.52310, %object
	.size	last_rec_pos_time.52310, 128
last_rec_pos_time.52310:
	.zero	128
	.type	last_rec_pos_decparam_time.52311, %object
	.size	last_rec_pos_decparam_time.52311, 128
last_rec_pos_decparam_time.52311:
	.zero	128
	.type	ChanPriTab.52260, %object
	.size	ChanPriTab.52260, 128
ChanPriTab.52260:
	.zero	128
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 768
g_VfmwChanStat:
	.zero	768
	.type	PrioArray.51724, %object
	.size	PrioArray.51724, 128
PrioArray.51724:
	.zero	128
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 128
s_ChanControlState:
	.zero	128
	.type	Capability.51788, %object
	.size	Capability.51788, 148
Capability.51788:
	.zero	148
	.zero	4
	.type	PrioArray.51787, %object
	.size	PrioArray.51787, 128
PrioArray.51787:
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
