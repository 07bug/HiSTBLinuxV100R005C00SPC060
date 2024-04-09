#include "hi_asm_define.h"
	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"vfmw_ctrl.c"
	.text
	.align	2
	.type	VfmwProc_SetPrintLevel, %function
VfmwProc_SetPrintLevel:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2
	ldr	r2, [r0]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	g_PrintEnable
	UNWIND(.fnend)
	.size	VfmwProc_SetPrintLevel, .-VfmwProc_SetPrintLevel
	.align	2
	.type	VfmwProc_OpenScdLowdly, %function
VfmwProc_OpenScdLowdly:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L5
	mov	r2, #1
	ldr	r1, [r0]
	ldr	r3, [r3, r1, asl #3]
	str	r2, [r3, #44]
	ldmfd	sp, {fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	s_SmIIS
	UNWIND(.fnend)
	.size	VfmwProc_OpenScdLowdly, .-VfmwProc_OpenScdLowdly
	.align	2
	.type	VfmwProc_CloseScdLowdly, %function
VfmwProc_CloseScdLowdly:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L8
	mov	r2, #0
	ldr	r1, [r0]
	ldr	r3, [r3, r1, asl #3]
	str	r2, [r3, #44]
	ldmfd	sp, {fp, sp, pc}
.L9:
	.align	2
.L8:
	.word	s_SmIIS
	UNWIND(.fnend)
	.size	VfmwProc_CloseScdLowdly, .-VfmwProc_CloseScdLowdly
	.align	2
	.global	VCTRL_EventReport
	.type	VCTRL_EventReport, %function
VCTRL_EventReport:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L22
	ldr	lr, .L26
	ldr	ip, [lr, r0, asl #2]
	cmp	ip, #0
	beq	.L23
	ldr	ip, [ip, #32]
	cmp	ip, #0
	beq	.L15
	cmp	ip, #1
	bne	.L24
	ldr	r3, [lr, #372]
	cmp	r3, #0
	beq	.L25
.L18:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L24:
	str	r3, [sp]
	mov	r0, #0
	mov	r3, ip
	ldr	r2, .L26+4
	ldr	r1, .L26+8
	bl	dprint_vfmw
.L12:
	mvn	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L15:
	ldr	r3, [lr, #368]
	cmp	r3, #0
	bne	.L18
	mov	r0, r3
	ldr	r1, .L26+12
	bl	dprint_vfmw
	b	.L12
.L25:
	mov	r0, r3
	ldr	r1, .L26+16
	bl	dprint_vfmw
	b	.L12
.L22:
	ldr	ip, .L26+20
	mov	r3, #872
	ldr	r2, .L26+4
	mov	r0, #0
	ldr	r1, .L26+24
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L12
.L23:
	ldr	lr, .L26+28
	mov	r0, ip
	movw	r3, #873
	ldr	r2, .L26+4
	ldr	r1, .L26+24
	str	lr, [sp]
	bl	dprint_vfmw
	b	.L12
.L27:
	.align	2
.L26:
	.word	.LANCHOR1
	.word	.LANCHOR0
	.word	.LC5
	.word	.LC3
	.word	.LC4
	.word	.LC1
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_EventReport, .-VCTRL_EventReport
	.align	2
	.type	VfmwProc_SetStandardObedience, %function
VfmwProc_SetStandardObedience:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L29
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L29+4
	mov	r2, r3
	str	r3, [ip, #392]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L30:
	.align	2
.L29:
	.word	.LANCHOR1
	.word	.LC6
	UNWIND(.fnend)
	.size	VfmwProc_SetStandardObedience, .-VfmwProc_SetStandardObedience
	.align	2
	.type	VfmwProc_SetClkSelect, %function
VfmwProc_SetClkSelect:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	ldr	r2, .L35
	cmp	r3, #4
	strls	r3, [r2]
	ldmlsfd	sp, {fp, sp, pc}
	ldr	r1, .L35+4
	mov	r0, #32
	ldr	r2, [r2]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L36:
	.align	2
.L35:
	.word	.LANCHOR2
	.word	.LC7
	UNWIND(.fnend)
	.size	VfmwProc_SetClkSelect, .-VfmwProc_SetClkSelect
	.align	2
	.type	VfmwProc_SetCompressPara, %function
VfmwProc_SetCompressPara:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	ldr	ip, .L81
	ldr	r5, [r0, #4]
	mov	r3, r0
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #52
	ldr	r7, [ip, #48]
	ldr	r4, [r3]
	ldr	r8, [r3, #8]
	ldr	r9, [r3, #12]
	ldr	r6, [r3, #16]
	blx	r7
	cmp	r5, #0
	beq	.L73
	cmp	r8, #0
	beq	.L74
	movw	r3, #625
	cmp	r9, r3
	mov	r3, #1
	str	r3, [fp, #-52]
	str	r3, [fp, #-48]
	beq	.L68
	bls	.L75
	movw	r3, #750
	cmp	r9, r3
	beq	.L46
	movw	r3, #875
	cmp	r9, r3
	moveq	r3, #3
	streq	r3, [fp, #-44]
.L48:
	movw	r3, #625
	cmp	r6, r3
	beq	.L50
.L80:
	bls	.L76
	movw	r3, #750
	cmp	r6, r3
	moveq	r3, #2
	streq	r3, [fp, #-40]
	beq	.L49
	movw	r3, #875
	cmp	r6, r3
	moveq	r3, #3
	streq	r3, [fp, #-40]
	b	.L49
.L74:
	mvn	r3, #0
	mov	r2, #1
	str	r8, [fp, #-48]
	str	r2, [fp, #-52]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
.L49:
	ldr	r1, [fp, #-48]
	cmp	r1, #1
	beq	.L77
	cmp	r1, #0
	beq	.L78
.L39:
	mov	r2, r4
	ldr	r1, .L81+4
	mov	r0, #32
	bl	dprint_vfmw
.L56:
	ldr	r3, .L81+8
	ldr	r2, [r3, r4, asl #2]
	cmp	r2, #0
	beq	.L79
.L57:
	mov	r2, r4
	ldr	r1, .L81+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L73:
	mvn	r3, #0
	str	r5, [fp, #-52]
	str	r5, [fp, #-48]
	str	r3, [fp, #-44]
	str	r3, [fp, #-40]
	b	.L39
.L75:
	cmp	r9, #500
	moveq	r3, #0
	streq	r3, [fp, #-44]
	movw	r3, #625
	cmp	r6, r3
	bne	.L80
.L50:
	mov	r3, #1
	str	r3, [fp, #-40]
	b	.L49
.L76:
	cmp	r6, #500
	moveq	r3, #0
	streq	r3, [fp, #-40]
	b	.L49
.L46:
	mov	r3, #2
.L68:
	str	r3, [fp, #-44]
	b	.L48
.L78:
	str	r1, [sp]
	mov	r3, #1
	mov	r2, r4
	ldr	r1, .L81+16
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L81+8
	ldr	r2, [r3, r4, asl #2]
	cmp	r2, #0
	bne	.L57
.L79:
	ldr	lr, [fp, #-44]
	add	r3, r3, r4, lsl #4
	ldr	ip, [fp, #-40]
	mov	r2, r4
	ldr	r6, [fp, #-52]
	mov	r0, #32
	ldr	r5, [fp, #-48]
	str	lr, [r3, #404]
	str	ip, [r3, #408]
	str	r6, [r3, #396]
	str	r5, [r3, #400]
	ldr	r1, .L81+20
	bl	dprint_vfmw
	ldr	r2, [fp, #-52]
	ldr	r1, .L81+24
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r2, [fp, #-48]
	ldr	r1, .L81+28
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, [fp, #-40]
	ldr	r2, [fp, #-44]
	mov	r0, #32
	ldr	r1, .L81+32
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L77:
	mov	r3, r1
	str	r1, [sp]
	str	r6, [sp, #8]
	mov	r2, r4
	str	r9, [sp, #4]
	mov	r0, #32
	ldr	r1, .L81+36
	bl	dprint_vfmw
	b	.L56
.L82:
	.align	2
.L81:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	.word	.LANCHOR1
	.word	.LC15
	.word	.LC9
	.word	.LC11
	.word	.LC12
	.word	.LC13
	.word	.LC14
	.word	.LC8
	UNWIND(.fnend)
	.size	VfmwProc_SetCompressPara, .-VfmwProc_SetCompressPara
	.align	2
	.type	VfmwProc_SetTunnelLineNumber, %function
VfmwProc_SetTunnelLineNumber:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L84
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L84+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L85:
	.align	2
.L84:
	.word	g_TunnelLineNumber
	.word	.LC16
	UNWIND(.fnend)
	.size	VfmwProc_SetTunnelLineNumber, .-VfmwProc_SetTunnelLineNumber
	.align	2
	.type	VfmwProc_SetSaveYuvBitWidth, %function
VfmwProc_SetSaveYuvBitWidth:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	bic	r2, r3, #2
	cmp	r2, #8
	bne	.L88
	ldr	ip, .L89
	mov	r2, r3
	ldr	r1, .L89+4
	mov	r0, #32
	str	r3, [ip, #4]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L88:
	mov	r2, r3
	ldr	r1, .L89+8
	mov	r0, #32
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L90:
	.align	2
.L89:
	.word	.LANCHOR2
	.word	.LC18
	.word	.LC17
	UNWIND(.fnend)
	.size	VfmwProc_SetSaveYuvBitWidth, .-VfmwProc_SetSaveYuvBitWidth
	.align	2
	.type	VfmwProc_SetTraceImgPeriod, %function
VfmwProc_SetTraceImgPeriod:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L92
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L92+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L93:
	.align	2
.L92:
	.word	g_TraceImgPeriod
	.word	.LC19
	UNWIND(.fnend)
	.size	VfmwProc_SetTraceImgPeriod, .-VfmwProc_SetTraceImgPeriod
	.align	2
	.type	VfmwProc_SetTraceFramePeriod, %function
VfmwProc_SetTraceFramePeriod:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L95
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L95+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L96:
	.align	2
.L95:
	.word	g_TraceFramePeriod
	.word	.LC20
	UNWIND(.fnend)
	.size	VfmwProc_SetTraceFramePeriod, .-VfmwProc_SetTraceFramePeriod
	.align	2
	.type	VfmwProc_SetTraceBSPeriod, %function
VfmwProc_SetTraceBSPeriod:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L98
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L98+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L99:
	.align	2
.L98:
	.word	g_TraceBsPeriod
	.word	.LC21
	UNWIND(.fnend)
	.size	VfmwProc_SetTraceBSPeriod, .-VfmwProc_SetTraceBSPeriod
	.align	2
	.type	VfmwProc_SetTraceCtrl, %function
VfmwProc_SetTraceCtrl:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L101
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L101+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L102:
	.align	2
.L101:
	.word	g_TraceCtrl
	.word	.LC22
	UNWIND(.fnend)
	.size	VfmwProc_SetTraceCtrl, .-VfmwProc_SetTraceCtrl
	.align	2
	.type	VfmwProc_TestStopDec, %function
VfmwProc_TestStopDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L104
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L104+4
	mov	r2, r3
	str	r3, [ip, #908]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L105:
	.align	2
.L104:
	.word	.LANCHOR1
	.word	.LC23
	UNWIND(.fnend)
	.size	VfmwProc_TestStopDec, .-VfmwProc_TestStopDec
	.align	2
	.type	VfmwProc_TestTimeSequence, %function
VfmwProc_TestTimeSequence:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L107
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L107+4
	mov	r2, r3
	str	r3, [ip, #912]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L108:
	.align	2
.L107:
	.word	.LANCHOR1
	.word	.LC24
	UNWIND(.fnend)
	.size	VfmwProc_TestTimeSequence, .-VfmwProc_TestTimeSequence
	.align	2
	.type	VfmwProc_SaveEL, %function
VfmwProc_SaveEL:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bhi	.L109
	ldr	r6, .L115
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #916]
	cmp	r7, #0
	beq	.L114
	ldr	r1, .L115+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L115+8
	ldr	r0, [r5, #916]
	ldr	r3, [r3, #36]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #916]
.L109:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L114:
	ldr	r2, [r6, #1044]
	mov	r1, #50
	ldr	r8, .L115+8
	sub	r0, fp, #88
	add	ip, r2, #1
	ldr	r3, .L115+12
	str	r2, [sp]
	ldr	r9, [r8, #68]
	ldr	r2, .L115+16
	str	ip, [r6, #1044]
	blx	r9
	ldr	r3, [r8, #32]
	mov	r2, r7
	sub	r0, fp, #88
	mov	r1, #66
	blx	r3
	str	r4, [r6, #1048]
	cmp	r0, #0
	str	r0, [r5, #916]
	beq	.L112
	mov	r3, r4
	sub	r2, fp, #88
	ldr	r1, .L115+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L109
.L112:
	sub	r2, fp, #88
	ldr	r1, .L115+24
	mov	r0, #32
	bl	dprint_vfmw
	b	.L109
.L116:
	.align	2
.L115:
	.word	.LANCHOR1
	.word	.LC28
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	.LC25
	.word	.LC26
	.word	.LC27
	UNWIND(.fnend)
	.size	VfmwProc_SaveEL, .-VfmwProc_SaveEL
	.align	2
	.type	VfmwProc_SetCurProcChan, %function
VfmwProc_SetCurProcChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	cmp	r3, #32
	bhi	.L119
	ldr	ip, .L120
	mov	r2, r3
	ldr	r1, .L120+4
	mov	r0, #32
	str	r3, [ip, #1052]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L119:
	mov	r2, r3
	ldr	r1, .L120+8
	mov	r0, #32
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L121:
	.align	2
.L120:
	.word	.LANCHOR1
	.word	.LC30
	.word	.LC29
	UNWIND(.fnend)
	.size	VfmwProc_SetCurProcChan, .-VfmwProc_SetCurProcChan
	.align	2
	.type	VfmwProc_SetSaveFileAfterReset, %function
VfmwProc_SetSaveFileAfterReset:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	cmp	r3, #1
	bls	.L124
	mov	r2, r3
	ldr	r1, .L125
	mov	r0, #32
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L124:
	ldr	ip, .L125+4
	mov	r2, r3
	ldr	r1, .L125+8
	mov	r0, #32
	str	r3, [ip, #1056]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L126:
	.align	2
.L125:
	.word	.LC32
	.word	.LANCHOR1
	.word	.LC31
	UNWIND(.fnend)
	.size	VfmwProc_SetSaveFileAfterReset, .-VfmwProc_SetSaveFileAfterReset
	.align	2
	.type	VfmwProc_SetUSE_FF_APT_EN, %function
VfmwProc_SetUSE_FF_APT_EN:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	cmp	r3, #1
	bls	.L129
	mov	r2, r3
	ldr	r1, .L130
	mov	r0, #32
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L129:
	ldr	ip, .L130+4
	mov	r2, r3
	ldr	r1, .L130+8
	mov	r0, #32
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L131:
	.align	2
.L130:
	.word	.LC34
	.word	USE_FF_APT_EN
	.word	.LC33
	UNWIND(.fnend)
	.size	VfmwProc_SetUSE_FF_APT_EN, .-VfmwProc_SetUSE_FF_APT_EN
	.align	2
	.type	VfmwProc_SetVp9DecFrameNum, %function
VfmwProc_SetVp9DecFrameNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L133
	ldr	r3, [r0]
	mov	r0, #32
	ldr	r1, .L133+4
	mov	r2, r3
	str	r3, [ip]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L134:
	.align	2
.L133:
	.word	g_CfgVp9FrmNum
	.word	.LC35
	UNWIND(.fnend)
	.size	VfmwProc_SetVp9DecFrameNum, .-VfmwProc_SetVp9DecFrameNum
	.align	2
	.type	VfmwProc_SetDefaultOutputOrder, %function
VfmwProc_SetDefaultOutputOrder:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0]
	cmp	r4, #7
	mov	r2, r4
	bhi	.L137
	ldr	r1, .L138
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L138+4
	str	r4, [r3, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L137:
	ldr	r1, .L138+8
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L139:
	.align	2
.L138:
	.word	.LC37
	.word	.LANCHOR2
	.word	.LC36
	UNWIND(.fnend)
	.size	VfmwProc_SetDefaultOutputOrder, .-VfmwProc_SetDefaultOutputOrder
	.align	2
	.global	VCTRL_Isr_0
	.type	VCTRL_Isr_0, %function
VCTRL_Isr_0:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #0
	bl	VDMDRV_IsrProcess
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Isr_0, .-VCTRL_Isr_0
	.align	2
	.global	VCTRL_Scd_Isr
	.type	VCTRL_Scd_Isr, %function
VCTRL_Scd_Isr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #0
	bl	SM_SCDIntServeProc
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Scd_Isr, .-VCTRL_Scd_Isr
	.align	2
	.global	VCTRL_MMU_ISR
	.type	VCTRL_MMU_ISR, %function
VCTRL_MMU_ISR:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #0
	bl	VDMDRV_MMUIntServeProc
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_MMU_ISR, .-VCTRL_MMU_ISR
	.align	2
	.type	VfmwProc_SaveReorderMetadata, %function
VfmwProc_SaveReorderMetadata:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bhi	.L143
	ldr	r6, .L149
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #1060]
	cmp	r7, #0
	beq	.L148
	ldr	r1, .L149+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L149+8
	ldr	r0, [r5, #1060]
	ldr	r3, [r3, #36]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #1060]
.L143:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L148:
	ldr	r8, .L149+8
	mov	r0, #24
	ldr	r9, [r8, #68]
	bl	VFMW_GetString
	ldr	r2, [r6, #1188]
	mov	r1, #50
	ldr	r3, .L149+12
	add	ip, r2, #1
	str	ip, [r6, #1188]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	ldr	r3, [r8, #32]
	mov	r2, r7
	sub	r0, fp, #88
	mov	r1, #66
	blx	r3
	str	r4, [r6, #1192]
	cmp	r0, #0
	str	r0, [r5, #1060]
	beq	.L146
	mov	r3, r4
	sub	r2, fp, #88
	ldr	r1, .L149+16
	mov	r0, #32
	bl	dprint_vfmw
	b	.L143
.L146:
	sub	r2, fp, #88
	ldr	r1, .L149+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L143
.L150:
	.align	2
.L149:
	.word	.LANCHOR1
	.word	.LC40
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	.LC38
	.word	.LC39
	UNWIND(.fnend)
	.size	VfmwProc_SaveReorderMetadata, .-VfmwProc_SaveReorderMetadata
	.align	2
	.type	VfmwProc_SaveMetadata, %function
VfmwProc_SaveMetadata:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bls	.L157
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L157:
	ldr	r5, .L159
	mov	r1, r4
	ldr	r7, .L159+4
	mov	r0, #2
	add	r6, r7, r4, lsl #2
	ldr	r3, [r5, #24]
	blx	r3
	ldr	r8, [r6, #1196]
	cmp	r8, #0
	beq	.L158
	ldr	r1, .L159+8
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, [r5, #36]
	ldr	r0, [r6, #1196]
	blx	r3
	mov	r3, #0
	str	r3, [r6, #1196]
.L156:
	ldr	r3, [r5, #28]
	mov	r1, r4
	mov	r0, #2
	blx	r3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L158:
	mov	r0, #23
	ldr	r9, [r5, #68]
	bl	VFMW_GetString
	ldr	r2, [r7, #1324]
	ldr	r3, .L159+12
	mov	r1, #50
	add	ip, r2, #1
	str	ip, [r7, #1324]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	mov	r2, r8
	sub	r0, fp, #88
	ldr	r3, [r5, #32]
	mov	r1, #66
	blx	r3
	sub	r2, fp, #88
	str	r4, [r7, #1328]
	cmp	r0, #0
	str	r0, [r6, #1196]
	beq	.L154
	mov	r3, r4
	ldr	r1, .L159+16
	mov	r0, #32
	bl	dprint_vfmw
	b	.L156
.L154:
	ldr	r1, .L159+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L156
.L160:
	.align	2
.L159:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC40
	.word	.LANCHOR2+8
	.word	.LC41
	.word	.LC42
	UNWIND(.fnend)
	.size	VfmwProc_SaveMetadata, .-VfmwProc_SaveMetadata
	.align	2
	.type	VfmwProc_Save1DYUV, %function
VfmwProc_Save1DYUV:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, .L168
	ldmia	r0, {r5, r7}
	mov	r3, r0
	ldr	r8, [r3, #8]
	ldr	r2, [r4, #212]
	mov	r0, r5
	blx	r2
	subs	r6, r0, #0
	beq	.L167
	mov	r0, #22
	ldr	r9, [r4, #68]
	bl	VFMW_GetString
	mov	r1, #50
	ldr	r3, .L168+4
	str	r5, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	sub	r0, fp, #88
	ldr	r3, [r4, #32]
	mov	r2, #0
	mov	r1, #66
	blx	r3
	subs	r9, r0, #0
	beq	.L164
	ldr	r3, .L168+8
	ldr	r5, [r3, #148]
	cmp	r5, #0
	beq	.L165
	mov	r1, #1
	mov	r3, r8
	str	r1, [sp]
	mov	r2, r7
	mov	r1, r6
	blx	r5
.L166:
	mov	r0, r9
	ldr	r3, [r4, #36]
	blx	r3
	sub	r2, fp, #88
	ldr	r1, .L168+12
	mov	r0, #32
	bl	dprint_vfmw
.L163:
	ldr	r3, [r4, #156]
	mov	r0, r6
	blx	r3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L165:
	mov	r0, r5
	movw	r2, #6572
	ldr	r1, .L168+16
	bl	dprint_vfmw
	b	.L166
.L167:
	mov	r2, r5
	ldr	r1, .L168+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L163
.L164:
	sub	r2, fp, #88
	ldr	r1, .L168+24
	mov	r0, #32
	bl	dprint_vfmw
	b	.L163
.L169:
	.align	2
.L168:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	g_vdm_hal_fun_ptr
	.word	.LC45
	.word	.LC44
	.word	.LC43
	.word	.LC46
	UNWIND(.fnend)
	.size	VfmwProc_Save1DYUV, .-VfmwProc_Save1DYUV
	.align	2
	.type	VfmwProc_SaveSeg, %function
VfmwProc_SaveSeg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bhi	.L170
	ldr	r6, .L176
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #1332]
	cmp	r7, #0
	beq	.L175
	ldr	r1, .L176+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L176+8
	ldr	r0, [r5, #1332]
	ldr	r3, [r3, #36]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #1332]
.L170:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L175:
	ldr	r8, .L176+8
	mov	r0, #19
	ldr	r9, [r8, #68]
	bl	VFMW_GetString
	ldr	r2, [r6, #1460]
	mov	r1, #50
	ldr	r3, .L176+12
	add	ip, r2, #1
	str	ip, [r6, #1460]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	ldr	r3, [r8, #32]
	mov	r2, r7
	sub	r0, fp, #88
	mov	r1, #66
	blx	r3
	str	r4, [r6, #1464]
	cmp	r0, #0
	str	r0, [r5, #1332]
	beq	.L173
	mov	r3, r4
	sub	r2, fp, #88
	ldr	r1, .L176+16
	mov	r0, #32
	bl	dprint_vfmw
	b	.L170
.L173:
	sub	r2, fp, #88
	ldr	r1, .L176+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L170
.L177:
	.align	2
.L176:
	.word	.LANCHOR1
	.word	.LC49
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	.LC47
	.word	.LC48
	UNWIND(.fnend)
	.size	VfmwProc_SaveSeg, .-VfmwProc_SaveSeg
	.align	2
	.type	VfmwProc_Savestream, %function
VfmwProc_Savestream:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #64)
	sub	sp, sp, #64
	ldr	r4, [r0]
	cmp	r4, #31
	bhi	.L178
	ldr	r6, .L184
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #1468]
	cmp	r7, #0
	beq	.L183
	ldr	r1, .L184+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, .L184+8
	ldr	r0, [r5, #1468]
	ldr	r3, [r3, #36]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #1468]
.L178:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L183:
	ldr	r8, .L184+8
	mov	r0, #18
	ldr	r9, [r8, #68]
	bl	VFMW_GetString
	ldr	r2, [r6, #1596]
	mov	r1, #50
	ldr	r3, .L184+12
	add	ip, r2, #1
	str	ip, [r6, #1596]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #88
	blx	r9
	ldr	r3, [r8, #32]
	mov	r2, r7
	sub	r0, fp, #88
	mov	r1, #66
	blx	r3
	str	r4, [r6, #1600]
	cmp	r0, #0
	str	r0, [r5, #1468]
	beq	.L181
	mov	r3, r4
	sub	r2, fp, #88
	ldr	r1, .L184+16
	mov	r0, #32
	bl	dprint_vfmw
	b	.L178
.L181:
	sub	r2, fp, #88
	ldr	r1, .L184+20
	mov	r0, #32
	bl	dprint_vfmw
	b	.L178
.L185:
	.align	2
.L184:
	.word	.LANCHOR1
	.word	.LC52
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+8
	.word	.LC50
	.word	.LC51
	UNWIND(.fnend)
	.size	VfmwProc_Savestream, .-VfmwProc_Savestream
	.align	2
	.type	VfmwProc_SaveYUV, %function
VfmwProc_SaveYUV:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #116)
	sub	sp, sp, #116
	ldr	r6, [r0]
	cmp	r6, #31
	bls	.L196
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L196:
	ldr	r7, .L199
	mov	r1, r6
	ldr	r4, .L199+4
	mov	r0, #2
	add	r8, r4, r6, lsl #2
	ldr	r3, [r7, #24]
	blx	r3
	ldr	r5, [r8, #1604]
	cmp	r5, #0
	beq	.L197
	ldr	r1, .L199+8
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, [r7, #36]
	ldr	r0, [r8, #1604]
	mov	r5, #0
	blx	r3
	ldr	r0, [r4, #1744]
	ldr	r3, .L199+12
	mvn	r2, #0
	cmp	r0, r5
	str	r5, [r8, #1604]
	str	r5, [r4, #1760]
	str	r2, [r3, #76]
	str	r5, [r4, #1764]
	str	r5, [r4, #1768]
	str	r5, [r4, #1772]
	str	r5, [r4, #1776]
	str	r5, [r4, #1780]
	str	r5, [r4, #1788]
	str	r5, [r4, #1784]
	bne	.L198
.L192:
	ldr	r3, [r7, #28]
	mov	r1, r6
	mov	r0, #2
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L198:
	ldr	r1, [r4, #1740]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [r4, #1752]
	ldr	r1, [r4, #1740]
	ldr	r0, [r4, #1744]
	bl	MEM_DelMemRecord
	mov	r1, r5
	ldr	r3, [r7, #48]
	mov	r2, #24
	ldr	r0, .L199+16
	blx	r3
	b	.L192
.L197:
	mov	r0, #20
	ldr	r10, [r7, #68]
	bl	VFMW_GetString
	ldr	r3, [r4, #1732]
	ldr	r9, .L199+12
	mov	r1, #100
	add	r2, r3, #1
	str	r2, [r4, #1732]
	str	r3, [sp]
	add	r3, r9, #8
	mov	r2, r0
	sub	r0, fp, #144
	blx	r10
	sub	r0, fp, #144
	ldr	r3, [r7, #32]
	mov	r2, r5
	movw	r1, #578
	blx	r3
	cmp	r0, #0
	str	r0, [r8, #1604]
	beq	.L189
	mov	r2, #24
	mov	r1, r5
	ldr	r3, [r7, #48]
	ldr	r0, .L199+16
	blx	r3
	mov	r0, #27
	mov	r3, #3
	str	r3, [r4, #1756]
	bl	VFMW_GetString
	str	r5, [sp]
	ldr	r3, .L199+16
	mov	r2, #47185920
	mov	r1, r5
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	beq	.L190
	ldr	r1, .L199+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #36]
	ldr	r0, [r8, #1604]
	blx	r3
	mvn	r3, #0
	str	r5, [r8, #1604]
	str	r5, [r4, #1760]
	str	r5, [r4, #1764]
	str	r5, [r4, #1768]
	str	r5, [r4, #1772]
	str	r5, [r4, #1776]
	str	r5, [r4, #1780]
	str	r5, [r4, #1784]
	str	r3, [r9, #76]
	b	.L192
.L189:
	sub	r2, fp, #144
	ldr	r1, .L199+24
	mov	r0, #32
	bl	dprint_vfmw
	b	.L192
.L190:
	ldr	r2, [r4, #1752]
	ldr	r1, [r4, #1740]
	ldr	r0, [r4, #1744]
	bl	MEM_AddMemRecord
	ldr	ip, [r4, #1740]
	and	lr, r6, #3
	mov	r3, r6, lsr #24
	str	lr, [sp]
	sub	r2, fp, #144
	ldr	r1, .L199+28
	mov	r0, #32
	add	r5, ip, #9437184
	str	ip, [r4, #1768]
	str	r5, [r4, #1764]
	add	r5, ip, #11796480
	str	lr, [r4, #1784]
	add	lr, ip, #14155776
	str	r3, [r9, #76]
	str	lr, [r4, #1780]
	add	lr, ip, #23592960
	str	r5, [r4, #1760]
	str	lr, [r4, #1776]
	add	lr, ip, #25952256
	add	ip, ip, #28311552
	str	lr, [r4, #1772]
	str	ip, [r4, #1788]
	bl	dprint_vfmw
	b	.L192
.L200:
	.align	2
.L199:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC56
	.word	.LANCHOR2
	.word	.LANCHOR1+1736
	.word	.LC53
	.word	.LC55
	.word	.LC54
	UNWIND(.fnend)
	.size	VfmwProc_SaveYUV, .-VfmwProc_SaveYUV
	.align	2
	.type	VfmwProc_SetScdPrint, %function
VfmwProc_SetScdPrint:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L202
	mov	r1, #1
	ldr	r0, [r0]
	mov	r3, #67108864
	ldr	r5, [r4]
	str	r3, [r4]
	bl	PrintScdRawState
	str	r5, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L203:
	.align	2
.L202:
	.word	g_PrintEnable
	UNWIND(.fnend)
	.size	VfmwProc_SetScdPrint, .-VfmwProc_SetScdPrint
	.align	2
	.type	VfmwProc_PrintTracer, %function
VfmwProc_PrintTracer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L205
	ldr	r4, [r0]
	mov	r0, #32
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DBG_PrintTracer
.L206:
	.align	2
.L205:
	.word	.LC57
	UNWIND(.fnend)
	.size	VfmwProc_PrintTracer, .-VfmwProc_PrintTracer
	.align	2
	.type	VfmwProc_SetSegBypass, %function
VfmwProc_SetSegBypass:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L209
	ldr	r3, .L210
	mov	r2, #1
	ldr	r1, .L210+4
	mov	r0, #32
	str	r2, [r3, #80]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L209:
	ldr	r2, .L210
	mov	r0, #32
	ldr	r1, .L210+8
	str	r3, [r2, #80]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L211:
	.align	2
.L210:
	.word	.LANCHOR2
	.word	.LC59
	.word	.LC58
	UNWIND(.fnend)
	.size	VfmwProc_SetSegBypass, .-VfmwProc_SetSegBypass
	.align	2
	.type	VfmwProc_SetSmmuIrqEnable, %function
VfmwProc_SetSmmuIrqEnable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0]
	cmp	r4, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r5, .L216
	ldr	r3, [r5, #84]
	cmp	r3, #1
	beq	.L215
	ldr	r1, .L216+4
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [r5, #84]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L215:
	ldr	r1, .L216+8
	mov	r0, #32
	bl	dprint_vfmw
	str	r4, [r5, #84]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L217:
	.align	2
.L216:
	.word	.LANCHOR2
	.word	.LC61
	.word	.LC60
	UNWIND(.fnend)
	.size	VfmwProc_SetSmmuIrqEnable, .-VfmwProc_SetSmmuIrqEnable
	.align	2
	.type	VfmwProc_SetSedOnlyEnable, %function
VfmwProc_SetSedOnlyEnable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L220
	ldr	r3, .L221
	mov	r2, #1
	ldr	r1, .L221+4
	mov	r0, #32
	str	r2, [r3, #88]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L220:
	ldr	r2, .L221
	mov	r0, #32
	ldr	r1, .L221+8
	str	r3, [r2, #88]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L222:
	.align	2
.L221:
	.word	.LANCHOR2
	.word	.LC63
	.word	.LC62
	UNWIND(.fnend)
	.size	VfmwProc_SetSedOnlyEnable, .-VfmwProc_SetSedOnlyEnable
	.align	2
	.type	VfmwProc_CloseModuleLowly, %function
VfmwProc_CloseModuleLowly:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	cmp	r3, #31
	bhi	.L225
	ldr	lr, .L226
	mov	r2, r3
	mov	ip, #0
	ldr	r1, .L226+4
	mov	r0, #32
	ldr	r3, [lr, r3, asl #2]
	str	ip, [r3, #1208]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L225:
	ldr	r1, .L226+8
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L227:
	.align	2
.L226:
	.word	.LANCHOR1
	.word	.LC16
	.word	.LC64
	UNWIND(.fnend)
	.size	VfmwProc_CloseModuleLowly, .-VfmwProc_CloseModuleLowly
	.align	2
	.type	VfmwProc_OpenModuleLowly, %function
VfmwProc_OpenModuleLowly:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	cmp	r3, #31
	bhi	.L230
	ldr	lr, .L231
	mov	r2, r3
	mov	ip, #1
	ldr	r1, .L231+4
	mov	r0, #32
	ldr	r3, [lr, r3, asl #2]
	str	ip, [r3, #1208]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L230:
	ldr	r1, .L231+8
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L232:
	.align	2
.L231:
	.word	.LANCHOR1
	.word	.LC16
	.word	.LC64
	UNWIND(.fnend)
	.size	VfmwProc_OpenModuleLowly, .-VfmwProc_OpenModuleLowly
	.align	2
	.type	VCTRL_DelRecordEsBuf.isra.5, %function
VCTRL_DelRecordEsBuf.isra.5:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, [r1]
	mov	r4, r1
	ldr	r2, [r3, #8]
	cmp	r2, #0
	beq	.L233
	ldr	r1, [r3, #16]
	cmp	r1, #0
	beq	.L233
	cmp	r0, #1
	strne	r2, [fp, #-36]
	subne	r0, fp, #44
	ldrne	r2, [r3, #4]
	ldreq	r2, .L243
	ldrne	r3, .L243
	ldreq	r0, [r3, #4]
	strne	r2, [fp, #-40]
	ldreq	r3, [r2, #164]
	ldrne	r3, [r3, #180]
	blx	r3
	ldr	r3, [r4]
	ldr	r2, [r3, #16]
	ldr	r1, [r3, #4]
	ldr	r0, [r3, #8]
	bl	MEM_DelMemRecord
.L233:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L244:
	.align	2
.L243:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_DelRecordEsBuf.isra.5, .-VCTRL_DelRecordEsBuf.isra.5
	.align	2
	.type	VCTRL_StopTask.part.14, %function
VCTRL_StopTask.part.14:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L257
	ldr	r3, [r5, #132]
	cmp	r3, #1
	beq	.L248
	ldr	r6, .L257+4
	mov	r0, #10
	mov	r4, #49
	ldr	r3, [r6, #120]
	blx	r3
	b	.L249
.L256:
	ldr	r3, [r6, #120]
	blx	r3
	subs	r4, r4, #1
	beq	.L255
.L249:
	ldr	r3, [r5, #132]
	mov	r0, #10
	cmp	r3, #1
	bne	.L256
.L248:
	mov	r0, #0
.L247:
	mov	r3, #0
	str	r3, [r5, #136]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L255:
	mvn	r0, #0
	b	.L247
.L258:
	.align	2
.L257:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_StopTask.part.14, .-VCTRL_StopTask.part.14
	.align	2
	.type	VCTRL_StartTask.part.15, %function
VCTRL_StartTask.part.15:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L271
	ldr	r3, [r5, #132]
	cmp	r3, #2
	beq	.L262
	ldr	r6, .L271+4
	mov	r0, #10
	mov	r4, #49
	ldr	r3, [r6, #120]
	blx	r3
	b	.L263
.L270:
	ldr	r3, [r6, #120]
	blx	r3
	subs	r4, r4, #1
	beq	.L269
.L263:
	ldr	r3, [r5, #132]
	mov	r0, #10
	cmp	r3, #2
	bne	.L270
.L262:
	mov	r0, #0
.L261:
	mov	r3, #0
	str	r3, [r5, #136]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L269:
	mvn	r0, #0
	b	.L261
.L272:
	.align	2
.L271:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_StartTask.part.15, .-VCTRL_StartTask.part.15
	.align	2
	.type	VCTRL_SetLastFrameState.part.23, %function
VCTRL_SetLastFrameState.part.23:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	ip, .L274
	movw	r3, #7166
	ldr	r2, .L274+4
	ldr	r1, .L274+8
	mov	r0, #0
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L275:
	.align	2
.L274:
	.word	.LC65
	.word	.LANCHOR0+20
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_SetLastFrameState.part.23, .-VCTRL_SetLastFrameState.part.23
	.align	2
	.type	VCTRL_CanBeDecodedByHardWare.part.25, %function
VCTRL_CanBeDecodedByHardWare.part.25:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	sub	r3, r0, #19
	cmp	r0, #14
	cmpne	r3, #1
	movls	r0, #1
	movhi	r0, #0
	eor	r0, r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_CanBeDecodedByHardWare.part.25, .-VCTRL_CanBeDecodedByHardWare.part.25
	.align	2
	.global	VCTRL_Suspend
	.type	VCTRL_Suspend, %function
VCTRL_Suspend:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r6, .L331
	ldr	r8, .L331+4
	ldr	r3, [r6]
	blx	r3
	ldr	r3, [r8]
	cmp	r3, #0
	mov	r9, r0
	beq	.L278
	mov	r0, #0
	blx	r3
.L279:
	mov	r0, #0
	mov	r4, #32
	mov	r5, r0
	bl	SCDDRV_PrepareSleep
	mov	r0, r5
	mov	r7, r5
	bl	VDMDRV_PrepareSleep
	ldr	r3, [r6]
	blx	r3
	mov	r10, r0
.L288:
	mov	r0, #0
	bl	SCDDRV_GetSleepStage
	cmp	r0, #2
	bne	.L323
	mov	r0, #0
	bl	VDMDRV_GetSleepStage
	cmp	r0, #2
	bne	.L324
.L283:
	ldr	r3, .L331+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L325
.L290:
	ldr	r3, .L331+12
	ldr	r2, [r3, #128]
	cmp	r2, #1
	beq	.L326
.L296:
	ldr	r3, [r6]
	blx	r3
	ldr	r1, .L331+16
	cmp	r9, r0
	rsbls	r2, r9, r0
	mvnhi	r9, r9
	addhi	r2, r9, r0
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L323:
	mov	r0, #0
	str	r7, [fp, #-48]
	bl	VDMDRV_GetSleepStage
	ldr	r3, [fp, #-48]
	cmp	r0, #2
	bne	.L299
	mov	r5, #1
	mov	r2, r5
.L300:
	tst	r2, r3
	bne	.L283
	subs	r4, r4, #1
	beq	.L327
	ldr	r3, [r6, #120]
	mov	r0, #10
	blx	r3
	eor	r3, r5, #1
	eor	r2, r7, #1
	orrs	r3, r3, r2
	bne	.L288
	ldr	r3, .L331+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L290
.L325:
	ldr	r3, [r8, #32]
	cmp	r3, #0
	beq	.L291
	mov	r0, #0
	blx	r3
.L291:
	ldr	r3, [r8, #24]
	cmp	r3, #0
	beq	.L328
	mov	r0, #0
	blx	r3
	ldr	r3, [r8, #8]
	cmp	r3, #0
	beq	.L293
.L330:
	mov	r0, #0
	blx	r3
.L294:
	ldr	r3, [r8, #40]
	cmp	r3, #0
	beq	.L290
	mov	r0, #0
	blx	r3
	ldr	r3, .L331+12
	ldr	r2, [r3, #128]
	cmp	r2, #1
	bne	.L296
.L326:
	mov	r2, #2
	str	r2, [r3, #136]
	bl	VCTRL_StopTask.part.14
	b	.L296
.L324:
	mov	r7, #1
	mov	r3, r7
.L299:
	mov	r2, r5
	b	.L300
.L327:
	ldr	r3, [r6]
	blx	r3
	str	r5, [sp]
	mov	r3, r7
	ldr	r1, .L331+20
	cmp	r10, r0
	rsbls	r2, r10, r0
	mvnhi	r10, r10
	addhi	r2, r10, r0
	mov	r0, #0
	bl	dprint_vfmw
	cmp	r7, #1
	beq	.L329
	mov	r2, #0
	ldr	r1, .L331+24
	mov	r0, r2
	bl	dprint_vfmw
	mov	r0, #0
	bl	SCDDRV_ForceSleep
	cmp	r5, #1
	beq	.L283
.L305:
	mov	r2, #0
	ldr	r1, .L331+28
	mov	r0, r2
	bl	dprint_vfmw
	mov	r0, #0
	bl	VDMDRV_ForceSleep
	b	.L283
.L329:
	cmp	r5, #1
	bne	.L305
	b	.L283
.L328:
	mov	r0, r3
	movw	r2, #345
	ldr	r1, .L331+32
	bl	dprint_vfmw
	ldr	r3, [r8, #8]
	cmp	r3, #0
	bne	.L330
.L293:
	mov	r0, r3
	movw	r2, #350
	ldr	r1, .L331+32
	bl	dprint_vfmw
	b	.L294
.L278:
	mov	r0, r3
	mov	r2, #247
	ldr	r1, .L331+32
	bl	dprint_vfmw
	b	.L279
.L332:
	.align	2
.L331:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	g_HalDisable
	.word	.LANCHOR1
	.word	.LC67
	.word	.LC68
	.word	.LC69
	.word	.LC66
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_Suspend, .-VCTRL_Suspend
	.align	2
	.type	VfmwProc_TestSuspend, %function
VfmwProc_TestSuspend:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L334
	mov	r2, r0
	mov	r0, #22
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_Suspend
.L335:
	.align	2
.L334:
	.word	.LC70
	UNWIND(.fnend)
	.size	VfmwProc_TestSuspend, .-VfmwProc_TestSuspend
	.align	2
	.global	VCTRL_Resume
	.type	VCTRL_Resume, %function
VCTRL_Resume:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L360
	ldr	r3, [r5]
	blx	r3
	ldr	r3, .L360+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	mov	r4, r0
	beq	.L356
.L337:
	mov	r0, #0
	bl	SCDDRV_ExitSleep
	mov	r0, #0
	bl	VDMDRV_ExitSleep
	ldr	r3, .L360+8
	ldr	r2, [r3, #128]
	cmp	r2, #1
	beq	.L357
.L347:
	ldr	r3, [r5]
	blx	r3
	ldr	r1, .L360+12
	cmp	r4, r0
	rsbls	r2, r4, r0
	mvnhi	r2, r4
	addhi	r2, r2, r0
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L356:
	ldr	r6, .L360+16
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L358
	mov	r0, #0
	blx	r3
.L339:
	ldr	r3, [r6, #20]
	cmp	r3, #0
	beq	.L359
	mov	r0, #0
	blx	r3
.L341:
	ldr	r3, [r6, #28]
	cmp	r3, #0
	beq	.L342
	mov	r0, #0
	blx	r3
.L342:
	ldr	r3, [r6, #36]
	cmp	r3, #0
	beq	.L343
	mov	r0, #0
	blx	r3
.L343:
	ldr	r3, [r6, #68]
	cmp	r3, #0
	beq	.L344
	mov	r0, #0
	blx	r3
.L345:
	ldr	r0, [r6, #72]
	cmp	r0, #0
	beq	.L346
	blx	r0
	b	.L337
.L357:
	str	r2, [r3, #136]
	bl	VCTRL_StartTask.part.15
	b	.L347
.L359:
	mov	r0, r3
	mov	r2, #392
	ldr	r1, .L360+20
	bl	dprint_vfmw
	b	.L341
.L344:
	mov	r0, r3
	movw	r2, #399
	ldr	r1, .L360+20
	bl	dprint_vfmw
	b	.L345
.L346:
	mov	r2, #400
	ldr	r1, .L360+20
	bl	dprint_vfmw
	b	.L337
.L358:
	mov	r0, r3
	movw	r2, #387
	ldr	r1, .L360+20
	bl	dprint_vfmw
	b	.L339
.L361:
	.align	2
.L360:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_HalDisable
	.word	.LANCHOR1
	.word	.LC71
	.word	g_vdm_hal_fun_ptr
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_Resume, .-VCTRL_Resume
	.align	2
	.type	VfmwProc_TestResume, %function
VfmwProc_TestResume:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L363
	mov	r2, r0
	mov	r0, #22
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_Resume
.L364:
	.align	2
.L363:
	.word	.LC70
	UNWIND(.fnend)
	.size	VfmwProc_TestResume, .-VfmwProc_TestResume
	.align	2
	.global	ChanCtx_Init
	.type	ChanCtx_Init, %function
ChanCtx_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L368
	mov	r2, #384
	mov	r1, #0
	ldr	r0, .L368+4
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, .L368+8
	mvn	r1, #0
	add	r2, r3, #128
.L366:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L366
	ldmfd	sp, {fp, sp, pc}
.L369:
	.align	2
.L368:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_ChanCtx
	.word	g_ChanCtx+124
	UNWIND(.fnend)
	.size	ChanCtx_Init, .-ChanCtx_Init
	.align	2
	.global	VCTRL_RecordPosTime
	.type	VCTRL_RecordPosTime, %function
VCTRL_RecordPosTime:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #11
	mov	r4, r0
	bhi	.L377
	ldr	r6, .L378
	ldrb	r3, [r6, r0]	@ zero_extendqisi2
	cmp	r3, #14
	movhi	r3, #0
	strhib	r3, [r6, r0]
	cmp	r0, #10
	mov	r5, r3
	ldreq	r3, .L378+4
	moveq	r2, #1
	streqb	r2, [r3, #1792]
	ldr	r3, .L378+8
	ldr	r3, [r3, #4]
	blx	r3
	rsb	r3, r4, r4, lsl #4
	ldr	r1, .L378+12
	add	r3, r3, r5
	ldrb	r2, [r6, r4]	@ zero_extendqisi2
	add	r2, r2, #1
	strb	r2, [r6, r4]
	str	r0, [r1, r3, asl #2]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L377:
	str	r0, [sp]
	movw	r3, #641
	ldr	r2, .L378+16
	mov	r0, #32
	ldr	r1, .L378+20
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L379:
	.align	2
.L378:
	.word	g_TimeRecId
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_TimeRecTable
	.word	.LANCHOR0+44
	.word	.LC72
	UNWIND(.fnend)
	.size	VCTRL_RecordPosTime, .-VCTRL_RecordPosTime
	.align	2
	.global	VCTRL_RecordData
	.type	VCTRL_RecordData, %function
VCTRL_RecordData:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #1
	bhi	.L385
	ldr	ip, .L386
	rsb	r2, r0, r0, lsl #4
	ldr	r4, .L386+4
	ldrb	r3, [ip, r0]	@ zero_extendqisi2
	cmp	r3, #14
	addls	lr, r3, #1
	movhi	r3, #0
	add	r3, r2, r3
	uxtbls	lr, lr
	movhi	lr, #1
	str	r1, [r4, r3, asl #2]
	strb	lr, [ip, r0]
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L385:
	str	r0, [sp]
	mov	r3, #664
	ldr	r2, .L386+8
	mov	r0, #32
	ldr	r1, .L386+12
	bl	dprint_vfmw
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L387:
	.align	2
.L386:
	.word	g_DataRecId
	.word	g_DataTable
	.word	.LANCHOR0+64
	.word	.LC73
	UNWIND(.fnend)
	.size	VCTRL_RecordData, .-VCTRL_RecordData
	.align	2
	.global	VCTRL_Isr_1
	.type	VCTRL_Isr_1, %function
VCTRL_Isr_1:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #1
	bl	VDMDRV_IsrProcess
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Isr_1, .-VCTRL_Isr_1
	.align	2
	.global	VCTRL_Isr_2
	.type	VCTRL_Isr_2, %function
VCTRL_Isr_2:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #2
	bl	VDMDRV_IsrProcess
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Isr_2, .-VCTRL_Isr_2
	.align	2
	.global	VCTRL_Scd_Isr_1
	.type	VCTRL_Scd_Isr_1, %function
VCTRL_Scd_Isr_1:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #1
	bl	SM_SCDIntServeProc
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Scd_Isr_1, .-VCTRL_Scd_Isr_1
	.align	2
	.global	VCTRL_Scd_Isr_2
	.type	VCTRL_Scd_Isr_2, %function
VCTRL_Scd_Isr_2:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #2
	bl	SM_SCDIntServeProc
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_Scd_Isr_2, .-VCTRL_Scd_Isr_2
	.align	2
	.global	VCTRL_InformVdmFree
	.type	VCTRL_InformVdmFree, %function
VCTRL_InformVdmFree:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L393
	mov	r0, #0
	ldr	r3, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L394:
	.align	2
.L393:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_InformVdmFree, .-VCTRL_InformVdmFree
	.align	2
	.global	VCTRL_ExtraWakeUpThread
	.type	VCTRL_ExtraWakeUpThread, %function
VCTRL_ExtraWakeUpThread:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L396
	mov	r0, #0
	ldr	r3, [r3, #128]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L397:
	.align	2
.L396:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_ExtraWakeUpThread, .-VCTRL_ExtraWakeUpThread
	.align	2
	.global	VCTRL_SetMoreGapEnable
	.type	VCTRL_SetMoreGapEnable, %function
VCTRL_SetMoreGapEnable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	ldrhi	ip, .L407
	movwhi	r3, #799
	bhi	.L404
	ldr	r3, .L407+4
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L405
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L406
	cmp	r1, #1
	strls	r1, [r3, #1192]
	movls	r0, #0
	mvnhi	r0, #0
	movhi	r2, #0
	strhi	r2, [r3, #1192]
.L400:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L406:
	ldr	ip, .L407+8
	movw	r3, #801
.L404:
	ldr	r2, .L407+12
	mov	r0, #0
	ldr	r1, .L407+16
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L400
.L405:
	ldr	ip, .L407+20
	mov	r0, r3
	ldr	r2, .L407+12
	mov	r3, #800
	ldr	r1, .L407+16
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L400
.L408:
	.align	2
.L407:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC74
	.word	.LANCHOR0+84
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_SetMoreGapEnable, .-VCTRL_SetMoreGapEnable
	.align	2
	.global	VCTRL_SetCallBack
	.type	VCTRL_SetCallBack, %function
VCTRL_SetCallBack:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r1, #0
	beq	.L417
	cmp	r0, #0
	beq	.L413
	cmp	r0, #1
	beq	.L414
	mov	r3, r0
	ldr	r2, .L418
	ldr	r1, .L418+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L411:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L414:
	ldr	r3, .L418+8
	mov	r0, #0
	str	r1, [r3, #372]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L413:
	ldr	r3, .L418+8
	str	r1, [r3, #368]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L417:
	ldr	ip, .L418+12
	mov	r0, r1
	movw	r3, #914
	ldr	r2, .L418
	ldr	r1, .L418+16
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L411
.L419:
	.align	2
.L418:
	.word	.LANCHOR0+108
	.word	.LC76
	.word	.LANCHOR1
	.word	.LC75
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_SetCallBack, .-VCTRL_SetCallBack
	.align	2
	.global	VCTRL_StopTask
	.type	VCTRL_StopTask, %function
VCTRL_StopTask:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L422
	ldr	r2, [r3, #128]
	cmp	r2, #1
	bne	.L421
	mov	r2, #2
	str	r2, [r3, #136]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_StopTask.part.14
.L421:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L423:
	.align	2
.L422:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_StopTask, .-VCTRL_StopTask
	.align	2
	.global	VCTRL_StartTask
	.type	VCTRL_StartTask, %function
VCTRL_StartTask:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L426
	ldr	r2, [r3, #128]
	cmp	r2, #1
	bne	.L425
	str	r2, [r3, #136]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_StartTask.part.15
.L425:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L427:
	.align	2
.L426:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_StartTask, .-VCTRL_StartTask
	.align	2
	.global	VCTRL_SetStreamInterface
	.type	VCTRL_SetStreamInterface, %function
VCTRL_SetStreamInterface:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r6, r1, #0
	mov	r4, r0
	ldreq	ip, .L436
	moveq	r0, r6
	movweq	r3, #1134
	beq	.L433
	cmp	r4, #31
	bhi	.L434
	ldr	r3, .L436+4
	ldr	r0, [r3, r4, asl #2]
	cmp	r0, #0
	beq	.L435
	ldr	r5, .L436+8
	mov	r2, #12
	add	r0, r0, #192
	ldr	r3, [r5, #52]
	blx	r3
	mov	r3, r4, asl #4
	ldr	r0, .L436+12
	sub	r4, r3, r4, asl #2
	mov	r1, r6
	ldr	r3, [r5, #52]
	add	r0, r0, r4
	mov	r2, #12
	blx	r3
	mov	r0, #0
.L430:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L434:
	ldr	ip, .L436+16
	movw	r3, #1135
	ldr	r2, .L436+20
	mov	r0, #0
	ldr	r1, .L436+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L430
.L435:
	ldr	ip, .L436+28
	mov	r3, #1136
.L433:
	ldr	r2, .L436+20
	ldr	r1, .L436+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L430
.L437:
	.align	2
.L436:
	.word	.LC77
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+1796
	.word	.LC78
	.word	.LANCHOR0+128
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_SetStreamInterface, .-VCTRL_SetStreamInterface
	.align	2
	.global	VCTRL_SetSendStreamAgainFlag
	.type	VCTRL_SetSendStreamAgainFlag, %function
VCTRL_SetSendStreamAgainFlag:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L442
	ldr	r3, .L444
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r3, r0, #290816
	movne	r0, #0
	strne	r1, [r3, #1132]
	beq	.L443
.L440:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L442:
	ldr	ip, .L444+4
	movw	r3, #1147
	ldr	r2, .L444+8
	mov	r0, #0
	ldr	r1, .L444+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L440
.L443:
	ldr	ip, .L444+16
	movw	r3, #1148
	ldr	r2, .L444+8
	ldr	r1, .L444+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L440
.L445:
	.align	2
.L444:
	.word	.LANCHOR1
	.word	.LC78
	.word	.LANCHOR0+156
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_SetSendStreamAgainFlag, .-VCTRL_SetSendStreamAgainFlag
	.align	2
	.global	VCTRL_GetSendStreamAgainFlag
	.type	VCTRL_GetSendStreamAgainFlag, %function
VCTRL_GetSendStreamAgainFlag:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L450
	ldr	r3, .L452
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r0, r0, #290816
	ldrne	r0, [r0, #1132]
	beq	.L451
.L448:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L450:
	ldr	ip, .L452+4
	movw	r3, #1157
	ldr	r2, .L452+8
	mov	r0, #0
	ldr	r1, .L452+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L448
.L451:
	ldr	ip, .L452+16
	movw	r3, #1158
	ldr	r2, .L452+8
	ldr	r1, .L452+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L448
.L453:
	.align	2
.L452:
	.word	.LANCHOR1
	.word	.LC78
	.word	.LANCHOR0+188
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_GetSendStreamAgainFlag, .-VCTRL_GetSendStreamAgainFlag
	.align	2
	.global	VCTRL_GetStreamInterface
	.type	VCTRL_GetStreamInterface, %function
VCTRL_GetStreamInterface:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r4, r0
	bhi	.L459
	ldr	r5, .L461
	ldr	r1, [r5, r0, asl #2]
	cmp	r1, #0
	beq	.L459
	ldr	ip, .L461+4
	mov	r3, r0, asl #4
	ldr	r0, .L461+8
	sub	r3, r3, r4, asl #2
	add	r1, r1, #192
	mov	r2, #12
	add	r0, r0, r3
	ldr	r3, [ip, #60]
	blx	r3
	cmp	r0, #0
	bne	.L460
	ldr	r1, [r5, r4, asl #2]
	add	r0, r1, #192
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L460:
	mov	r3, r4
	movw	r2, #1173
	ldr	r1, .L461+12
	mov	r0, #0
	bl	dprint_vfmw
.L459:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L462:
	.align	2
.L461:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+1796
	.word	.LC79
	UNWIND(.fnend)
	.size	VCTRL_GetStreamInterface, .-VCTRL_GetStreamInterface
	.align	2
	.global	VCTRL_GetStreamSize
	.type	VCTRL_GetStreamSize, %function
VCTRL_GetStreamSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	ldrhi	ip, .L471
	movwhi	r3, #1186
	bhi	.L468
	ldr	r3, .L471+4
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L469
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L470
	add	r0, r0, #99328
	add	r0, r0, #624
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	GetSegStreamSize
.L470:
	ldr	ip, .L471+8
	movw	r3, #1188
.L468:
	ldr	r2, .L471+12
	mov	r0, #0
	ldr	r1, .L471+16
	str	ip, [sp]
	bl	dprint_vfmw
.L465:
	mvn	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L469:
	ldr	ip, .L471+20
	movw	r3, #1187
	ldr	r2, .L471+12
	ldr	r1, .L471+16
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L465
.L472:
	.align	2
.L471:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC81
	.word	.LANCHOR0+220
	.word	.LC0
	.word	.LC80
	UNWIND(.fnend)
	.size	VCTRL_GetStreamSize, .-VCTRL_GetStreamSize
	.align	2
	.global	VCTRL_CheckFreshRaw
	.type	VCTRL_CheckFreshRaw, %function
VCTRL_CheckFreshRaw:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	cmp	r0, #31
	mov	r3, #0
	str	r3, [fp, #-28]
	str	r3, [fp, #-24]
	movhi	r0, r3
	ldrhi	ip, .L483
	movhi	r3, #1200
	bhi	.L480
	ldr	r2, .L483+4
	ldr	r0, [r2, r0, asl #2]
	cmp	r0, #0
	ldreq	ip, .L483+8
	movweq	r3, #1201
	beq	.L480
	ldr	r2, [r0, #4]
	cmp	r2, #1
	bne	.L482
	add	r4, r0, #1616
	sub	r1, fp, #28
	add	r4, r4, #8
	mov	r0, r4
	bl	GetRawStreamNum
	cmp	r0, #0
	bne	.L481
	mov	r0, r4
	sub	r1, fp, #24
	bl	GetRawStreamSize
	cmp	r0, #0
	bne	.L481
	ldr	r3, [fp, #-24]
	mov	r0, #22
	ldr	r2, [fp, #-28]
	ldr	r1, .L483+12
	bl	dprint_vfmw
	ldr	r3, [fp, #-28]
	cmp	r3, #0
	ble	.L481
	ldr	r0, [fp, #-24]
	cmp	r0, #3
	movgt	r0, #0
	mvnle	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L482:
	ldr	ip, .L483+16
	mov	r0, r3
	movw	r3, #1202
.L480:
	ldr	r2, .L483+20
	ldr	r1, .L483+24
	str	ip, [sp]
	bl	dprint_vfmw
.L481:
	mvn	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L484:
	.align	2
.L483:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC80
	.word	.LC82
	.word	.LC81
	.word	.LANCHOR0+240
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_CheckFreshRaw, .-VCTRL_CheckFreshRaw
	.align	2
	.global	VCTRL_CheckFreshSeg
	.type	VCTRL_CheckFreshSeg, %function
VCTRL_CheckFreshSeg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	cmp	r0, #31
	mov	r2, #0
	str	r2, [fp, #-20]
	str	r2, [fp, #-16]
	movhi	r0, r2
	ldrhi	ip, .L492
	movwhi	r3, #1223
	bhi	.L490
	ldr	r3, .L492+4
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L491
	ldr	r1, [r0, #4]
	cmp	r1, #1
	ldrne	ip, .L492+8
	movne	r0, r2
	movwne	r3, #1225
	bne	.L490
	add	r0, r0, #99328
	sub	r2, fp, #16
	sub	r1, fp, #20
	add	r0, r0, #624
	bl	GetFreshSegStream
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-20]
	mov	r0, #22
	ldr	r1, .L492+12
	bl	dprint_vfmw
	ldr	r0, [fp, #-20]
	cmp	r0, #0
	movgt	r0, #0
	mvnle	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L491:
	ldr	ip, .L492+16
	movw	r3, #1224
.L490:
	ldr	r2, .L492+20
	ldr	r1, .L492+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L493:
	.align	2
.L492:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC81
	.word	.LC83
	.word	.LC80
	.word	.LANCHOR0+260
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_CheckFreshSeg, .-VCTRL_CheckFreshSeg
	.align	2
	.global	VCTRL_SetDiscardPicParam
	.type	VCTRL_SetDiscardPicParam, %function
VCTRL_SetDiscardPicParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	mov	r4, r0
	mov	r0, r1
	bhi	.L501
	cmp	r1, #0
	ldreq	ip, .L503
	movweq	r3, #1242
	beq	.L500
	ldr	r5, .L503+4
	ldr	r0, [r5, r4, asl #2]
	cmp	r0, #0
	beq	.L502
	ldr	r3, .L503+8
	mov	r2, #8
	add	r0, r0, #1488
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r2, [r5, r4, asl #2]
	mov	r0, #0
	ldr	r3, [r2, #1488]
	sub	r3, r3, #1
	cmp	r3, #1
	strhi	r0, [r2, #1488]
.L496:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L501:
	ldr	ip, .L503+12
	movw	r3, #1241
	ldr	r2, .L503+16
	mov	r0, #0
	ldr	r1, .L503+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L496
.L502:
	ldr	ip, .L503+24
	movw	r3, #1243
.L500:
	ldr	r2, .L503+16
	ldr	r1, .L503+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L496
.L504:
	.align	2
.L503:
	.word	.LC84
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC65
	.word	.LANCHOR0+280
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_SetDiscardPicParam, .-VCTRL_SetDiscardPicParam
	.align	2
	.global	VCTRL_PartitionMemForStdUser
	.type	VCTRL_PartitionMemForStdUser, %function
VCTRL_PartitionMemForStdUser:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r9, .L522
	cmp	r2, #31
	cmpgt	r1, #31
	mov	r5, r2
	mov	r6, r1
	mov	r8, r0
	movle	r2, #1
	movgt	r2, #0
	str	r3, [fp, #-72]
	ldr	r4, [r9, r0, asl #2]
	ble	.L518
	ldr	r3, [fp, #-72]
	ldr	r1, [fp, #4]
	cmp	r1, #0
	cmpne	r3, #0
	moveq	r7, #1
	movne	r7, #0
	beq	.L519
	ldr	r10, .L522+4
	mov	r2, #20
	mov	r1, r7
	sub	r0, fp, #64
	ldr	r3, [r10, #48]
	blx	r3
	sub	r1, fp, #64
	mov	r0, r8
	str	r5, [fp, #-56]
	mov	r3, #1
	str	r5, [fp, #-48]
	str	r6, [fp, #-60]
	str	r6, [fp, #-52]
	strb	r7, [fp, #-63]
	strb	r7, [fp, #-62]
	strb	r7, [fp, #-61]
	strb	r3, [fp, #-64]
	bl	FSP_ConfigInstance
	subs	r5, r0, #0
	bne	.L509
	ldr	r2, [fp, #4]
	sub	r3, fp, #68
	ldr	r1, [fp, #-72]
	mov	r0, r8
	bl	FSP_ConfigFrameBuf
	subs	r6, r0, #0
	bne	.L520
	mov	r0, r8
	ldr	r1, .L522+8
	bl	FSP_GetInstInfo
	movw	r3, #2182
	ldrsb	r3, [r9, r3]
	cmp	r3, #16
	movge	r3, #16
	cmp	r3, #2
	str	r3, [r4, #488]
	ble	.L521
	ldr	ip, [r9, #2184]
	mov	r2, #64
	ldr	r3, [r10, #48]
	mov	r1, r5
	add	r0, r4, #420
	str	ip, [r4, #484]
	blx	r3
	ldr	r0, [r4, #488]
	cmp	r0, #0
	ble	.L507
	ldr	r2, .L522+8
	add	r4, r4, #416
	mov	r3, r5
.L514:
	ldr	r1, [r2, #16]
	add	r3, r3, #1
	cmp	r3, r0
	add	r2, r2, #88
	str	r1, [r4, #4]!
	bne	.L514
.L507:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L519:
	mov	r0, r2
	ldr	r1, .L522+12
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L507
.L509:
	mov	r0, r7
	ldr	r1, .L522+16
	bl	dprint_vfmw
.L517:
	mvn	r5, #0
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L520:
	mov	r0, r5
	ldr	r1, .L522+20
	bl	dprint_vfmw
	b	.L517
.L521:
	mov	r0, r6
	movw	r3, #1353
	ldr	r2, .L522+24
	ldr	r1, .L522+28
	bl	dprint_vfmw
	b	.L517
.L518:
	mov	r3, r5
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L522+32
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L507
.L523:
	.align	2
.L522:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+2180
	.word	.LC86
	.word	.LC89
	.word	.LC87
	.word	.LANCHOR0+308
	.word	.LC88
	.word	.LC85
	UNWIND(.fnend)
	.size	VCTRL_PartitionMemForStdUser, .-VCTRL_PartitionMemForStdUser
	.align	2
	.global	VCTRL_UnInstallChan
	.type	VCTRL_UnInstallChan, %function
VCTRL_UnInstallChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	FSP_DisableInstance
	mov	r0, r4
	bl	CloseUsdPool_WithMem
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_UnInstallChan, .-VCTRL_UnInstallChan
	.align	2
	.global	DelAllFrameMemRecord
	.type	DelAllFrameMemRecord, %function
DelAllFrameMemRecord:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r1, #0
	movne	r4, r1
	addne	r5, r4, #2304
	beq	.L542
.L531:
	ldr	r3, [r4]
	cmp	r3, #255
	beq	.L528
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #24]
	ldr	r0, [r4, #32]
	bl	MEM_DelMemRecord
.L528:
	ldr	r3, [r4, #4]
	cmp	r3, #255
	beq	.L529
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #40]
	ldr	r0, [r4, #48]
	bl	MEM_DelMemRecord
.L529:
	ldr	r3, [r4, #8]
	cmp	r3, #255
	beq	.L530
	ldr	r2, [r4, #20]
	ldr	r1, [r4, #56]
	ldr	r0, [r4, #64]
	bl	MEM_DelMemRecord
.L530:
	add	r4, r4, #72
	cmp	r4, r5
	bne	.L531
	mov	r0, #0
.L527:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L542:
	ldr	ip, .L543
	mov	r0, r1
	mov	r3, #1392
	ldr	r2, .L543+4
	ldr	r1, .L543+8
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L527
.L544:
	.align	2
.L543:
	.word	.LC90
	.word	.LANCHOR0+340
	.word	.LC0
	UNWIND(.fnend)
	.size	DelAllFrameMemRecord, .-DelAllFrameMemRecord
	.align	2
	.global	VCTRL_FreeChanResource
	.type	VCTRL_FreeChanResource, %function
VCTRL_FreeChanResource:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r5, r1, #0
	beq	.L569
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L570
	ldr	r3, [r5, #20]
	cmp	r3, #1
	beq	.L550
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_DelMemRecord
.L551:
	ldr	r3, [r5, #24]
	cmp	r3, #1
	beq	.L571
.L549:
	ldr	r4, [r5, #4]
	cmp	r4, #0
	beq	.L572
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_DelMemRecord
	ldr	r3, [r5, #28]
	cmp	r3, #1
	beq	.L573
.L554:
	ldr	r4, [r5, #8]
	cmp	r4, #0
	beq	.L574
.L555:
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_DelMemRecord
	ldr	r3, [r5, #32]
	cmp	r3, #1
	bne	.L556
	ldr	r0, [r4, #8]
	cmp	r0, #0
	bne	.L575
.L556:
	ldr	r3, .L577
	ldr	r0, [r4, #4]
	ldr	r3, [r3, #164]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L550:
	ldr	r1, [r5, #12]
	cmp	r1, #0
	beq	.L576
	bl	DelAllFrameMemRecord
	cmp	r0, #0
	beq	.L551
	ldr	r1, .L577+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r5, #24]
	cmp	r3, #1
	bne	.L549
.L571:
	ldr	r0, [r4, #8]
	cmp	r0, #0
	beq	.L549
	ldr	r1, [r4, #4]
	bl	MEM_ReleaseMemBlock
	b	.L549
.L573:
	ldr	r0, [r4, #8]
	cmp	r0, #0
	beq	.L554
	ldr	r1, [r4, #4]
	bl	MEM_ReleaseMemBlock
	b	.L554
.L572:
	mov	r0, r4
	ldr	r2, .L577+8
	ldr	r1, .L577+12
	bl	dprint_vfmw
	ldr	r4, [r5, #8]
	cmp	r4, #0
	bne	.L555
.L574:
	ldr	r2, .L577+8
	mov	r0, r4
	ldr	r1, .L577+16
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L575:
	ldr	r1, [r4, #4]
	bl	MEM_ReleaseMemBlock
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L576:
	mov	r0, r1
	ldr	r2, .L577+8
	ldr	r1, .L577+20
	bl	dprint_vfmw
	b	.L551
.L570:
	mov	r0, r4
	ldr	r2, .L577+8
	ldr	r1, .L577+24
	bl	dprint_vfmw
	b	.L549
.L569:
	mov	r0, r5
	ldr	r2, .L577+8
	ldr	r1, .L577+28
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L578:
	.align	2
.L577:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC94
	.word	.LANCHOR0+364
	.word	.LC95
	.word	.LC96
	.word	.LC93
	.word	.LC92
	.word	.LC91
	UNWIND(.fnend)
	.size	VCTRL_FreeChanResource, .-VCTRL_FreeChanResource
	.align	2
	.global	VCTRL_GetChanCtxSize
	.type	VCTRL_GetChanCtxSize, %function
VCTRL_GetChanCtxSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #26
	movweq	r3, #62768
	movwne	r3, #14496
	movteq	r3, 177
	movtne	r3, 12
	str	r3, [r1]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_GetChanCtxSize, .-VCTRL_GetChanCtxSize
	.align	2
	.global	VCTRL_GetChanCfg
	.type	VCTRL_GetChanCfg, %function
VCTRL_GetChanCfg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	mov	r3, r1
	bhi	.L588
	cmp	r1, #0
	ldreq	ip, .L590
	moveq	r0, r1
	movweq	r3, #2429
	beq	.L587
	ldr	r2, .L590+4
	ldr	r1, [r2, r0, asl #2]
	cmp	r1, #0
	beq	.L589
	ldr	ip, .L590+8
	mov	r0, r3
	add	r1, r1, #44
	mov	r2, #148
	ldr	r3, [ip, #52]
	blx	r3
	mov	r0, #0
.L584:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L588:
	ldr	ip, .L590+12
	movw	r3, #2428
	ldr	r2, .L590+16
	mov	r0, #0
	ldr	r1, .L590+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L584
.L589:
	ldr	ip, .L590+24
	mov	r0, r1
	movw	r3, #2430
.L587:
	ldr	r2, .L590+16
	ldr	r1, .L590+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L584
.L591:
	.align	2
.L590:
	.word	.LC97
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC65
	.word	.LANCHOR0+388
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_GetChanCfg, .-VCTRL_GetChanCfg
	.align	2
	.global	VCTRL_CheckCommonParameter
	.type	VCTRL_CheckCommonParameter, %function
VCTRL_CheckCommonParameter:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L605
	ldr	r2, [r1, #8]
	ldr	r3, [r3, r0, asl #2]
	ldr	r0, [r3, #52]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #72]
	ldr	r2, [r1, #28]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #68]
	ldr	r2, [r1, #24]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #76]
	ldr	r2, [r1, #32]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #80]
	ldr	r2, [r1, #36]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #84]
	ldr	r2, [r1, #40]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #100]
	ldr	r2, [r1, #56]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #112]
	ldr	r2, [r1, #68]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #108]
	ldr	r2, [r1, #64]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #104]
	ldr	r2, [r1, #60]
	cmp	r0, r2
	bne	.L604
	ldr	r0, [r3, #116]
	ldr	r2, [r1, #72]
	cmp	r0, r2
	bne	.L604
	ldr	r3, [r3, #176]
	ldr	r0, [r1, #132]
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L604:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L606:
	.align	2
.L605:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_CheckCommonParameter, .-VCTRL_CheckCommonParameter
	.align	2
	.global	VCTRL_CmpConfigParameter
	.type	VCTRL_CmpConfigParameter, %function
VCTRL_CmpConfigParameter:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L614
	mov	r5, r1
	ldr	r4, [r3, r0, asl #2]
	ldr	r3, [r4, #568]
	cmp	r3, #22
	beq	.L612
	bl	VCTRL_CheckCommonParameter
	cmp	r0, #0
	bne	.L612
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L613
	sub	r3, r3, #10
	cmp	r3, #2
	ldmhifd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, [r4, #56]
	ldr	r0, [r5, #12]
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L613:
	ldr	r2, [r4, #56]
	ldr	r3, [r5, #12]
	cmp	r2, r3
	bne	.L612
	ldr	r3, [r4, #60]
	ldr	r0, [r5, #16]
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L612:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L615:
	.align	2
.L614:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_CmpConfigParameter, .-VCTRL_CmpConfigParameter
	.align	2
	.global	VCTRL_CheckChanWH
	.type	VCTRL_CheckChanWH, %function
VCTRL_CheckChanWH:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L621
	ldr	r2, .L621+4
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r2]
	ldr	r0, [r3, #1268]
	ldr	r3, [r3, #1272]
	cmp	r0, r2
	bgt	.L617
	ldr	r0, .L621+8
	ldr	r0, [r0]
	cmp	r3, r0
	ble	.L619
.L617:
	ldr	r0, [r1, #8]
	cmp	r0, #20
	cmpne	r0, #0
	bic	r0, r0, #2
	movne	r3, #1
	moveq	r3, #0
	cmp	r0, #13
	moveq	r0, #0
	andne	r0, r3, #1
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r3, .L621+8
	mov	r0, #0
	ldr	r1, .L621+12
	ldr	r3, [r3]
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L619:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L622:
	.align	2
.L621:
	.word	.LANCHOR1
	.word	g_ChipMaxWidth
	.word	g_ChipMaxHeight
	.word	.LC98
	UNWIND(.fnend)
	.size	VCTRL_CheckChanWH, .-VCTRL_CheckChanWH
	.align	2
	.global	VCTRL_ConfigChanCompress
	.type	VCTRL_ConfigChanCompress, %function
VCTRL_ConfigChanCompress:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r2, [r1, #56]
	ldr	r3, .L629
	cmp	r2, #2
	ldr	r2, [r3, r0, asl #2]
	beq	.L628
	add	r0, r3, r0, lsl #4
	ldr	r3, [r0, #400]
	ldr	r1, [r0, #396]
	cmp	r3, #1
	str	r3, [r2, #1180]
	str	r1, [r2, #1176]
	mvnne	r3, #0
	ldreq	r1, [r0, #404]
	ldreq	r3, [r0, #408]
	strne	r3, [r2, #1184]
	streq	r1, [r2, #1184]
	str	r3, [r2, #1188]
	ldmfd	sp, {fp, sp, pc}
.L628:
	mov	r1, #0
	mvn	r3, #0
	str	r1, [r2, #1176]
	str	r1, [r2, #1180]
	str	r3, [r2, #1184]
	str	r3, [r2, #1188]
	ldmfd	sp, {fp, sp, pc}
.L630:
	.align	2
.L629:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_ConfigChanCompress, .-VCTRL_ConfigChanCompress
	.align	2
	.global	VCTRL_SeekPts
	.type	VCTRL_SeekPts, %function
VCTRL_SeekPts:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, .L639
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L637
	ldr	r3, [r3, #568]
	sub	r2, r3, #10
	cmp	r2, #2
	bls	.L638
.L634:
	cmp	r3, #14
	cmpne	r3, #4
	beq	.L636
	bl	SM_SeekPts
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L633:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L638:
	ldr	r2, .L639+4
	ldr	r2, [r2, #-3180]
	tst	r2, #1
	bne	.L634
.L636:
	mvn	r0, #0
	b	.L633
.L637:
	ldr	ip, .L639+8
	mov	r0, r3
	ldr	r2, .L639+12
	movw	r3, #2825
	ldr	r1, .L639+16
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L633
.L640:
	.align	2
.L639:
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	.LC2
	.word	.LANCHOR0+408
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_SeekPts, .-VCTRL_SeekPts
	.align	2
	.global	VCTRL_ReleaseStream
	.type	VCTRL_ReleaseStream, %function
VCTRL_ReleaseStream:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L645
	ldr	r2, .L647
	ldr	r3, [r2, r0, asl #2]
	cmp	r3, #0
	beq	.L646
	bl	SM_Reset
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L643:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L645:
	ldr	ip, .L647+4
	movw	r3, #3070
	ldr	r2, .L647+8
	mov	r0, #0
	ldr	r1, .L647+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L643
.L646:
	ldr	ip, .L647+16
	mov	r0, r3
	ldr	r2, .L647+8
	movw	r3, #3071
	ldr	r1, .L647+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L643
.L648:
	.align	2
.L647:
	.word	.LANCHOR1
	.word	.LC99
	.word	.LANCHOR0+424
	.word	.LC0
	.word	.LC100
	UNWIND(.fnend)
	.size	VCTRL_ReleaseStream, .-VCTRL_ReleaseStream
	.align	2
	.global	VCTRL_ImageOutputEnable
	.type	VCTRL_ImageOutputEnable, %function
VCTRL_ImageOutputEnable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #31
	mov	r4, r0
	mov	r6, r1
	bhi	.L652
	ldr	r5, .L653
	mov	r0, #4
	ldr	r3, [r5, #12]
	blx	r3
	ldr	r3, .L653+4
	ldr	r2, [r6]
	mov	r0, #4
	ldr	r3, [r3, r4, asl #2]
	str	r2, [r3, #12]
	ldr	r3, [r5, #16]
	blx	r3
	mov	r0, #0
.L651:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L652:
	ldr	ip, .L653+8
	movw	r3, #3140
	ldr	r2, .L653+12
	mov	r0, #0
	ldr	r1, .L653+16
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L651
.L654:
	.align	2
.L653:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC65
	.word	.LANCHOR0+444
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_ImageOutputEnable, .-VCTRL_ImageOutputEnable
	.align	2
	.global	VCTRL_TryToRelSpecialFrm
	.type	VCTRL_TryToRelSpecialFrm, %function
VCTRL_TryToRelSpecialFrm:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	mov	r5, r0
	bhi	.L690
	ldr	r6, .L695
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	beq	.L691
	add	r3, r0, #294912
	ldr	r8, [r3, #1152]
	cmp	r8, #0
	beq	.L659
	ldr	r3, [r3, #628]
	cmp	r1, r3
	movne	r2, #0
	bne	.L662
	b	.L692
.L665:
	add	r3, r3, #628
	ldr	r3, [r0, r3]
	cmp	r1, r3
	beq	.L660
.L662:
	add	r2, r2, #1
	cmp	r2, r8
	mov	r3, r2, asl #4
	mov	r4, r2
	add	r3, r3, #294912
	bne	.L665
.L659:
	mvn	r0, #0
.L683:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L692:
	mov	r4, #0
.L660:
	add	r3, r0, #282624
	ldr	r2, [r3, #3416]
	cmp	r2, r1
	addne	r3, r3, #3504
	movne	r7, #1
	bne	.L669
	b	.L693
.L666:
	add	r7, r7, #1
	cmp	r7, #32
	beq	.L694
.L669:
	ldr	r2, [r3]
	add	r3, r3, #88
	cmp	r2, r1
	bne	.L666
.L663:
	ldr	r9, .L695+4
	mov	r0, #3
	sub	r8, r8, #1
	ldr	r3, [r9, #12]
	blx	r3
	ldr	r2, [r6, r5, asl #2]
	mov	r1, #88
	mov	r3, #0
	mov	r0, #3
	mla	r7, r1, r7, r2
	ldr	r2, [r9, #16]
	add	r1, r7, #282624
	add	r7, r7, #286720
	strb	r3, [r1, #3410]
	strb	r3, [r7, #2130]
	blx	r2
	cmp	r8, r4
	bls	.L675
	add	r7, r4, #18432
	add	r7, r7, #39
.L668:
	ldr	r1, [r6, r5, asl #2]
	add	r4, r4, #1
	ldr	r3, [r9, #52]
	mov	r2, #16
	add	r0, r1, r7, lsl #4
	add	r7, r4, #18432
	add	r7, r7, #39
	add	r1, r1, r7, lsl #4
	blx	r3
	cmp	r8, r4
	bhi	.L668
.L667:
	add	r8, r8, #18432
	ldr	r0, [r6, r5, asl #2]
	add	r8, r8, #39
	ldr	r3, [r9, #48]
	mov	r2, #16
	mov	r1, #0
	add	r0, r0, r8, lsl #4
	blx	r3
	ldr	r3, [r6, r5, asl #2]
	mov	r0, #0
	add	r3, r3, #294912
	ldr	r2, [r3, #1152]
	sub	r2, r2, #1
	str	r2, [r3, #1152]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L694:
	add	r0, r0, #262144
	movw	r4, #1987
	movw	r3, #3295
	ldr	r2, .L695+8
	ldrsb	ip, [r0, r4]
	mov	r0, #1
	ldr	r1, .L695+12
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	lr, [r6, r5, asl #2]
	add	r3, lr, #262144
	ldrsb	r3, [r3, r4]
	cmp	r3, #0
	movgt	r4, #0
	ble	.L659
.L671:
	mov	r3, #88
	movw	ip, #23896
	mla	lr, r3, r4, lr
	movt	ip, 4
	movw	r3, #3298
	mov	r0, #1
	ldr	r2, .L695+8
	add	r4, r4, r0
	add	ip, lr, ip
	ldr	r1, .L695+16
	ldr	ip, [ip]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	lr, [r6, r5, asl #2]
	movw	r3, #1987
	movt	r3, 4
	add	r3, lr, r3
	ldrsb	r3, [r3]
	cmp	r3, r4
	bgt	.L671
	b	.L659
.L690:
	ldr	ip, .L695+20
	movw	r3, #3260
	ldr	r2, .L695+8
	mov	r0, #0
	ldr	r1, .L695+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L683
.L675:
	mov	r8, r4
	b	.L667
.L693:
	mov	r7, #0
	b	.L663
.L691:
	ldr	ip, .L695+20
	movw	r3, #3261
	ldr	r2, .L695+8
	ldr	r1, .L695+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L683
.L696:
	.align	2
.L695:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+468
	.word	.LC102
	.word	.LC101
	.word	.LC65
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_TryToRelSpecialFrm, .-VCTRL_TryToRelSpecialFrm
	.align	2
	.global	VCTRL_GetChanImage
	.type	VCTRL_GetChanImage, %function
VCTRL_GetChanImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 640
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #648)
	sub	sp, sp, #648
	cmp	r0, #31
	mov	r5, r0
	mov	r4, r1
	bhi	.L729
	ldr	r7, .L742
	ldr	r0, [r7, r0, asl #2]
	cmp	r0, #0
	ldreq	ip, .L742+4
	movweq	r3, #3421
	beq	.L726
	cmp	r1, #0
	beq	.L730
	ldr	r8, .L742+8
	mov	r0, #4
	ldr	r3, [r8, #12]
	blx	r3
	ldr	r6, [r7, r5, asl #2]
	cmp	r6, #0
	beq	.L731
	ldr	r3, [r6, #4]
	cmp	r3, #1
	bne	.L732
	ldr	r3, [r6, #12]
	cmp	r3, #1
	bne	.L733
	movw	r0, #33992
	mov	r1, r4
	movt	r0, 4
	add	r0, r6, r0
	bl	SYNTAX_ReceiveImage
	cmp	r0, #1
	mov	r9, r0
	beq	.L734
	mov	r0, #9
	mvn	r6, #0
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L717
.L716:
	ldr	r3, [r7, r5, asl #2]
	mov	r0, #4
	ldr	r2, [r8, #16]
	add	r3, r3, #311296
	ldrb	r3, [r3, #660]	@ zero_extendqisi2
	strb	r3, [r4, #392]
	blx	r2
.L725:
	mov	r0, r6
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L734:
	ldr	r2, [r4, #192]
	mvn	r3, #0
	str	r3, [r4, #188]
	cmp	r2, #1
	beq	.L735
.L706:
	mov	r0, #9
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L736
.L718:
	ldr	r2, [r4, #64]
	mov	r6, #0
	ldr	r3, [r7, r5, asl #2]
	str	r2, [r3, #396]
	ldr	r2, [r4, #276]
	str	r2, [r3, #400]
	b	.L716
.L736:
	mov	r6, #0
.L717:
	ldr	r3, [r8]
	blx	r3
	ldr	r3, .L742+12
	ldr	r1, .L742+16
	add	r3, r3, r5, lsl #2
	ldr	r2, [r3, #-3176]
	ldr	r1, [r1]
	rsb	r2, r2, r0
	cmp	r2, r1
	bhi	.L737
.L715:
	cmp	r6, #0
	bne	.L716
	b	.L718
.L737:
	mov	r2, r5, asl #24
	str	r0, [r3, #-3176]
	add	r2, r2, #589824
	movw	r1, #3573
	cmp	r9, #1
	addeq	r2, r2, #1
	ldr	r0, .L742+20
	bl	DBG_AddTrace
	b	.L715
.L735:
	ldr	r2, [r4, #180]
	cmp	r2, #0
	beq	.L738
	ldr	r0, [r4, #24]
	mov	r2, #3
	ldr	r1, [r4, #20]
	str	r3, [r4, #188]
	str	r9, [r4, #180]
	str	r0, [r4, #200]
	str	r1, [r4, #196]
	str	r2, [r4, #276]
	b	.L706
.L733:
	ldr	r3, [r8, #16]
	mov	r0, #4
	blx	r3
	ldr	r2, .L742+24
	ldr	r1, .L742+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r6, #0
	b	.L725
.L732:
	ldr	r3, [r8, #16]
	mov	r0, #4
	blx	r3
	mov	r2, r5
	ldr	r1, .L742+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r6, #0
	b	.L725
.L738:
	ldr	r3, [r7, r5, asl #2]
	movw	r0, #33992
	movt	r0, 4
	sub	r1, fp, #676
	add	r0, r3, r0
	bl	SYNTAX_ReceiveImage
	cmp	r0, #1
	mov	r6, r0
	bne	.L739
	ldr	r3, [r4, #184]
	ldr	r2, [fp, #-492]
	cmp	r3, r2
	bge	.L709
	ldr	r1, [fp, #-652]
	mov	r3, #3
	ldr	r2, [fp, #-656]
	mov	r9, #1
	ldr	r6, [fp, #-496]
	ldr	r0, [fp, #-648]
	cmp	r6, #0
	str	r1, [r4, #200]
	str	r2, [r4, #196]
	ldr	r1, [fp, #-644]
	movne	r6, #0
	ldr	r2, [fp, #-528]
	str	r0, [r4, #204]
	str	r1, [r4, #208]
	str	r2, [r4, #188]
	str	r3, [r4, #276]
	strne	r9, [r4, #180]
.L714:
	mov	r0, #9
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L717
	cmp	r6, #0
	bne	.L716
	b	.L718
.L729:
	ldr	ip, .L742+36
	movw	r3, #3420
	ldr	r2, .L742+24
	mov	r0, #0
	ldr	r1, .L742+40
	mvn	r6, #0
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L725
.L739:
	ldr	r3, [r7, r5, asl #2]
	movw	r0, #33992
	movt	r0, 4
	add	r0, r3, r0
	bl	SYNTAX_ReturnImage
	ldr	r3, [r8, #16]
	mov	r0, #4
	blx	r3
	b	.L725
.L730:
	ldr	ip, .L742+44
	mov	r0, r1
	movw	r3, #3422
.L726:
	ldr	r2, .L742+24
	mvn	r6, #0
	ldr	r1, .L742+40
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L725
.L709:
	bgt	.L740
	cmp	r3, #0
	movw	r0, #33992
	ldr	r3, [r7, r5, asl #2]
	movt	r0, 4
	bne	.L712
	add	r0, r3, r0
	mvn	r6, #0
	bl	SYNTAX_ReturnImage
	ldr	r3, [r7, r5, asl #2]
	movw	r0, #33992
	mov	r1, r4
	movt	r0, 4
	add	r0, r3, r0
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r4, #184]
	ldr	r2, .L742+24
	mov	r0, #1
	ldr	r1, .L742+48
	mvn	r9, #1
	bl	dprint_vfmw
	b	.L714
.L712:
	add	r0, r3, r0
	mov	r1, r4
	bl	SYNTAX_ReleaseImage
	ldr	r3, [fp, #-496]
	ldr	r6, .L742
	cmp	r3, #0
	beq	.L741
	ldr	r3, [r4, #184]
	mov	r0, #1
	ldr	r2, .L742+24
	ldr	r1, .L742+52
	bl	dprint_vfmw
	sub	r1, fp, #676
	ldr	r3, [r8, #52]
	mov	r2, #640
	mov	r0, r4
	blx	r3
	ldr	r3, [fp, #-652]
	ldr	r1, [fp, #-656]
	mvn	r0, #0
	mov	r2, #3
	str	r0, [r4, #188]
	str	r3, [r4, #200]
	mov	r3, #1
	str	r1, [r4, #196]
	str	r2, [r4, #276]
	str	r3, [r4, #180]
	b	.L706
.L731:
	ldr	r3, [r8, #16]
	mov	r0, #4
	blx	r3
	mov	r0, r6
	movw	r2, #3429
	ldr	r1, .L742+56
	bl	dprint_vfmw
	mvn	r6, #0
	b	.L725
.L740:
	ldr	r3, [r7, r5, asl #2]
	movw	r0, #33992
	movt	r0, 4
	mvn	r6, #0
	add	r0, r3, r0
	mvn	r9, #1
	bl	SYNTAX_ReturnImage
	ldr	r3, [r7, r5, asl #2]
	movw	r0, #33992
	mov	r1, r4
	movt	r0, 4
	add	r0, r3, r0
	bl	SYNTAX_ReleaseImage
	ldr	r1, [fp, #-492]
	ldr	r3, [r4, #184]
	mov	r0, #1
	ldr	r2, .L742+24
	str	r1, [sp]
	ldr	r1, .L742+60
	bl	dprint_vfmw
	b	.L714
.L741:
	ldr	r3, [r6, r5, asl #2]
	movw	r0, #33992
	sub	r1, fp, #676
	movt	r0, 4
	add	r0, r3, r0
	mvn	r6, #0
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r4, #184]
	ldr	r2, .L742+24
	mov	r0, #1
	ldr	r1, .L742+52
	mvn	r9, #1
	bl	dprint_vfmw
	b	.L714
.L743:
	.align	2
.L742:
	.word	.LANCHOR1
	.word	.LC2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	g_TraceImgPeriod
	.word	.LANCHOR0+516
	.word	.LANCHOR0+496
	.word	.LC106
	.word	.LC105
	.word	.LC65
	.word	.LC0
	.word	.LC103
	.word	.LC108
	.word	.LC109
	.word	.LC104
	.word	.LC107
	UNWIND(.fnend)
	.size	VCTRL_GetChanImage, .-VCTRL_GetChanImage
	.align	2
	.global	VCTRL_ReleaseChanImage
	.type	VCTRL_ReleaseChanImage, %function
VCTRL_ReleaseChanImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 640
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #652)
	sub	sp, sp, #652
	cmp	r0, #31
	mov	r4, r0
	mov	r5, r1
	ldrhi	ip, .L773
	movhi	r3, #3616
	bhi	.L764
	ldr	r6, .L773+4
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	ldreq	ip, .L773+8
	movweq	r3, #3617
	beq	.L765
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L767
	cmp	r1, #0
	beq	.L768
	ldr	r7, .L773+12
	mov	r0, #4
	ldr	r3, [r7, #12]
	blx	r3
	ldr	r0, [r6, r4, asl #2]
	cmp	r0, #0
	movweq	r2, #3625
	ldreq	r1, .L773+16
	beq	.L766
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L769
	ldr	r1, [r5, #20]
	mov	r0, r4
	bl	VCTRL_TryToRelSpecialFrm
	subs	r8, r0, #0
	beq	.L770
	ldr	r3, [r6, r4, asl #2]
	movw	r0, #33992
	movt	r0, 4
	mov	r1, r5
	add	r0, r3, r0
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r5, #188]
	cmn	r3, #1
	mov	r8, r0
	beq	.L753
	ldr	r2, [r6, r4, asl #2]
	movw	r0, #33992
	movt	r0, 4
	sub	r1, fp, #676
	add	r0, r2, r0
	str	r3, [fp, #-528]
	bl	SYNTAX_ReleaseImage
	mov	r8, r0
.L753:
	mov	r0, #10
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L771
.L755:
	subs	r4, r8, #1
	mvnne	r4, #0
	cmp	r4, #0
	bne	.L772
.L757:
	ldr	r3, [r7, #16]
	mov	r0, #4
	blx	r3
.L746:
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L770:
	ldr	r3, [r7, #16]
	mov	r0, #4
	blx	r3
	movw	r2, #3646
	ldr	r1, .L773+20
	mov	r0, r8
	bl	dprint_vfmw
	mov	r4, r8
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L772:
	ldr	r2, .L773+24
	mov	r0, #0
	ldr	r1, .L773+28
	bl	dprint_vfmw
	b	.L757
.L771:
	ldr	r3, [r7]
	blx	r3
	ldr	r3, .L773+32
	ldr	r1, .L773+36
	add	r3, r3, r4, lsl #2
	ldr	r2, [r3, #-3048]
	ldr	r1, [r1]
	rsb	r2, r2, r0
	mov	ip, r0
	cmp	r2, r1
	bls	.L755
	mov	r2, r4, asl #24
	movw	r1, #3675
	add	r2, r2, #655360
	ldr	r0, .L773+40
	cmp	r8, #1
	addeq	r2, r2, #1
	str	ip, [r3, #-3048]
	bl	DBG_AddTrace
	b	.L755
.L769:
	ldr	r1, .L773+44
	movw	r2, #3634
	mov	r0, #0
.L766:
	bl	dprint_vfmw
	ldr	r3, [r7, #16]
	mov	r0, #4
	mvn	r4, #0
	blx	r3
	b	.L746
.L767:
	ldr	ip, .L773+48
	movw	r3, #3618
.L764:
	ldr	r2, .L773+24
	mov	r0, #0
	ldr	r1, .L773+52
	mvn	r4, #0
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L746
.L768:
	ldr	ip, .L773+56
	mov	r0, r1
	movw	r3, #3619
.L765:
	ldr	r2, .L773+24
	mvn	r4, #0
	ldr	r1, .L773+52
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L746
.L774:
	.align	2
.L773:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC104
	.word	.LC112
	.word	.LANCHOR0+536
	.word	.LC113
	.word	.LANCHOR3
	.word	g_TraceImgPeriod
	.word	.LANCHOR0+560
	.word	.LC111
	.word	.LC110
	.word	.LC0
	.word	.LC103
	UNWIND(.fnend)
	.size	VCTRL_ReleaseChanImage, .-VCTRL_ReleaseChanImage
	.align	2
	.global	VCTRL_GetVidStd
	.type	VCTRL_GetVidStd, %function
VCTRL_GetVidStd:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L776
	ldr	r3, .L780
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L776
	ldr	r2, [r3, #4]
	cmp	r2, #1
	beq	.L779
	mov	r3, r0
	movw	r2, #3702
	ldr	r1, .L780+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #22
	ldmfd	sp, {fp, sp, pc}
.L776:
	mov	r2, #3696
	ldr	r1, .L780+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #22
	ldmfd	sp, {fp, sp, pc}
.L779:
	ldr	r0, [r3, #568]
	ldmfd	sp, {fp, sp, pc}
.L781:
	.align	2
.L780:
	.word	.LANCHOR1
	.word	.LC115
	.word	.LC114
	UNWIND(.fnend)
	.size	VCTRL_GetVidStd, .-VCTRL_GetVidStd
	.align	2
	.global	VCTRL_GetHDRConfigInfo
	.type	VCTRL_GetHDRConfigInfo, %function
VCTRL_GetHDRConfigInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L787
	ldr	r3, .L790
	ldr	r2, [r3, r0, asl #2]
	cmp	r2, #0
	beq	.L788
	cmp	r1, #0
	beq	.L789
	ldrb	r2, [r2, #44]	@ zero_extendqisi2
	strb	r2, [r1, #65]
	ldr	r2, [r3, r0, asl #2]
	ldrb	r2, [r2, #46]	@ zero_extendqisi2
	strb	r2, [r1, #66]
	ldr	r2, [r3, r0, asl #2]
	ldr	r2, [r2, #156]
	str	r2, [r1, #76]
	ldr	r2, [r3, r0, asl #2]
	ldr	r2, [r2, #160]
	str	r2, [r1, #68]
	ldr	r3, [r3, r0, asl #2]
	ldr	r3, [r3, #164]
	str	r3, [r1, #72]
.L782:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L787:
	ldr	ip, .L790+4
	movw	r3, #3711
	ldr	r2, .L790+8
	mov	r0, #0
	ldr	r1, .L790+12
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L788:
	ldr	ip, .L790+16
	mov	r0, r2
	mov	r3, #3712
	ldr	r2, .L790+8
	ldr	r1, .L790+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L782
.L789:
	ldr	ip, .L790+20
	mov	r0, r1
	movw	r3, #3713
	ldr	r2, .L790+8
	ldr	r1, .L790+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L782
.L791:
	.align	2
.L790:
	.word	.LANCHOR1
	.word	.LC65
	.word	.LANCHOR0+584
	.word	.LC0
	.word	.LC2
	.word	.LC116
	UNWIND(.fnend)
	.size	VCTRL_GetHDRConfigInfo, .-VCTRL_GetHDRConfigInfo
	.align	2
	.global	VCTRL_GetDecParam
	.type	VCTRL_GetDecParam, %function
VCTRL_GetDecParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L813
	ldr	r3, .L816
	ldr	r5, [r3, r0, asl #2]
	cmp	r5, #0
	moveq	r3, r5
	beq	.L793
	ldr	r3, [r5, #4]
	cmp	r3, #1
	beq	.L815
.L813:
	mov	r3, #0
.L793:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L815:
	ldr	r3, [r5, #8]
	cmp	r3, #1
	bne	.L813
	ldr	r3, [r5, #568]
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L794
.L796:
	.word	.L795
	.word	.L804
	.word	.L798
	.word	.L804
	.word	.L794
	.word	.L804
	.word	.L801
	.word	.L794
	.word	.L804
	.word	.L804
	.word	.L804
	.word	.L804
	.word	.L804
	.word	.L804
	.word	.L794
	.word	.L806
	.word	.L807
	.word	.L804
.L804:
	add	r3, r5, #294912
	ldr	r4, [r3, #1236]
.L809:
	cmp	r4, #0
	moveq	r3, r4
	beq	.L793
	ldr	r3, .L816+4
	ldr	r3, [r3]
	blx	r3
	mov	r3, r4
	str	r0, [r5, #40]
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L806:
	add	r3, r5, #294912
	ldr	r4, [r3, #1460]
	b	.L809
.L798:
	add	r3, r5, #294912
	ldr	r4, [r3, #2268]
	b	.L809
.L807:
	add	r3, r5, #294912
	ldr	r4, [r3, #3624]
	b	.L809
.L795:
	add	r3, r5, #294912
	ldr	r4, [r3, #1592]
	b	.L809
.L801:
	add	r3, r5, #294912
	ldr	r4, [r3, #1248]
	b	.L809
.L794:
	ldr	r2, .L816+8
	mov	r0, #0
	ldr	r1, .L816+12
	bl	dprint_vfmw
	mov	r3, #0
	b	.L793
.L817:
	.align	2
.L816:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+608
	.word	.LC117
	UNWIND(.fnend)
	.size	VCTRL_GetDecParam, .-VCTRL_GetDecParam
	.align	2
	.global	VCTRL_IsSedOnlyMode
	.type	VCTRL_IsSedOnlyMode, %function
VCTRL_IsSedOnlyMode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r0, r1, #0
	beq	.L820
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L820:
	ldr	r1, .L821
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L822:
	.align	2
.L821:
	.word	.LC118
	UNWIND(.fnend)
	.size	VCTRL_IsSedOnlyMode, .-VCTRL_IsSedOnlyMode
	.align	2
	.global	VCTRL_ClearDecparam
	.type	VCTRL_ClearDecparam, %function
VCTRL_ClearDecparam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L840
	ldr	r3, .L841
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #568]
	cmp	r2, #17
	ldrls	pc, [pc, r2, asl #2]
	b	.L823
.L827:
	.word	.L826
	.word	.L836
	.word	.L829
	.word	.L836
	.word	.L823
	.word	.L836
	.word	.L832
	.word	.L823
	.word	.L836
	.word	.L836
	.word	.L836
	.word	.L836
	.word	.L836
	.word	.L836
	.word	.L823
	.word	.L837
	.word	.L838
	.word	.L836
.L837:
	add	r3, r3, #294912
	mov	r2, #0
	str	r2, [r3, #1460]
.L823:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L836:
	add	r3, r3, #294912
	mov	r2, #0
	str	r2, [r3, #1236]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L840:
	ldr	ip, .L841+4
	movw	r3, #4161
	ldr	r2, .L841+8
	mov	r0, #0
	ldr	r1, .L841+12
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L832:
	add	r3, r3, #294912
	mov	r2, #0
	str	r2, [r3, #1248]
	b	.L823
.L826:
	add	r3, r3, #294912
	mov	r2, #0
	str	r2, [r3, #1592]
	b	.L823
.L838:
	add	r3, r3, #294912
	mov	r2, #0
	str	r2, [r3, #3624]
	b	.L823
.L829:
	add	r3, r3, #294912
	mov	r2, #0
	str	r2, [r3, #2268]
	b	.L823
.L842:
	.align	2
.L841:
	.word	.LANCHOR1
	.word	.LC119
	.word	.LANCHOR0+628
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_ClearDecparam, .-VCTRL_ClearDecparam
	.align	2
	.global	VCTRL_VdmProcSedOnly
	.type	VCTRL_VdmProcSedOnly, %function
VCTRL_VdmProcSedOnly:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	mov	r3, r0
	ldrhi	ip, .L850
	movwhi	r3, #4239
	bhi	.L848
	ldr	r2, .L850+4
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	beq	.L849
	ldr	r3, [r3, #8]
	cmp	r3, #1
	beq	.L847
	ldr	ip, .L850+8
	movw	r3, #4241
.L848:
	ldr	r2, .L850+12
	mov	r0, #0
	ldr	r1, .L850+16
	str	ip, [sp]
	bl	dprint_vfmw
.L843:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L847:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_GetDecParam
.L849:
	ldr	ip, .L850+20
	mov	r0, r3
	ldr	r2, .L850+12
	movw	r3, #4240
	ldr	r1, .L850+16
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L843
.L851:
	.align	2
.L850:
	.word	.LC120
	.word	.LANCHOR1
	.word	.LC121
	.word	.LANCHOR0+648
	.word	.LC0
	.word	.LC110
	UNWIND(.fnend)
	.size	VCTRL_VdmProcSedOnly, .-VCTRL_VdmProcSedOnly
	.align	2
	.global	VCTRL_GetImageBuffer
	.type	VCTRL_GetImageBuffer, %function
VCTRL_GetImageBuffer:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	ldrhi	ip, .L879
	movwhi	r3, #4274
	bhi	.L875
	ldr	r3, .L879+4
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L876
	ldr	r0, [r3, #8]
	cmp	r0, #1
	bne	.L877
	ldr	r2, [r3, #568]
	cmp	r2, #17
	ldrls	pc, [pc, r2, asl #2]
	b	.L871
.L858:
	.word	.L857
	.word	.L859
	.word	.L860
	.word	.L861
	.word	.L871
	.word	.L862
	.word	.L863
	.word	.L871
	.word	.L864
	.word	.L865
	.word	.L866
	.word	.L866
	.word	.L866
	.word	.L867
	.word	.L871
	.word	.L868
	.word	.L869
	.word	.L870
.L870:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_GetImageBuffer
.L857:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_GetImageBuffer
.L859:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_GetImageBuffer
.L860:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_GetImageBuffer
.L861:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_GetImageBuffer
.L862:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_GetImageBuffer
.L863:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_GetImageBuffer
.L864:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_GetImageBuffer
.L865:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_GetImageBuffer
.L866:
	ldr	r2, .L879+8
	ldr	r2, [r2, #-3180]
	tst	r2, #1
	bne	.L878
.L854:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L867:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_GetImageBuffer
.L868:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_GetImageBuffer
.L869:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_GetImageBuffer
.L877:
	ldr	ip, .L879+12
	movw	r3, #4276
.L875:
	ldr	r2, .L879+16
	mov	r0, #0
	ldr	r1, .L879+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L854
.L871:
	mov	r0, #0
	b	.L854
.L878:
	add	r0, r3, #294912
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_GetImageBuffer
.L876:
	ldr	ip, .L879+24
	mov	r0, r3
	ldr	r2, .L879+16
	movw	r3, #4275
	ldr	r1, .L879+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L854
.L880:
	.align	2
.L879:
	.word	.LC120
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	.LC121
	.word	.LANCHOR0+672
	.word	.LC0
	.word	.LC110
	UNWIND(.fnend)
	.size	VCTRL_GetImageBuffer, .-VCTRL_GetImageBuffer
	.align	2
	.global	VCTRL_ConfigFFFBSpeed
	.type	VCTRL_ConfigFFFBSpeed, %function
VCTRL_ConfigFFFBSpeed:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	ldrhi	ip, .L891
	movwhi	r3, #4390
	bhi	.L887
	ldr	r3, .L891+4
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	moveq	r0, r3
	ldreq	ip, .L891+8
	movweq	r3, #4391
	beq	.L888
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L889
	cmp	r1, #0
	ldrne	r2, [r1]
	movne	r0, #0
	strne	r2, [r3, #1196]
	beq	.L890
.L883:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L889:
	ldr	ip, .L891+12
	movw	r3, #4392
.L887:
	ldr	r2, .L891+16
	mov	r0, #0
	ldr	r1, .L891+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L883
.L890:
	ldr	ip, .L891+24
	mov	r0, r1
	movw	r3, #4393
.L888:
	ldr	r2, .L891+16
	ldr	r1, .L891+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L883
.L892:
	.align	2
.L891:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC122
	.word	.LC123
	.word	.LANCHOR0+696
	.word	.LC0
	.word	.LC124
	UNWIND(.fnend)
	.size	VCTRL_ConfigFFFBSpeed, .-VCTRL_ConfigFFFBSpeed
	.align	2
	.global	VCTRL_ConfigPVRInfo
	.type	VCTRL_ConfigPVRInfo, %function
VCTRL_ConfigPVRInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	ldrhi	ip, .L903
	movwhi	r3, #4403
	bhi	.L899
	ldr	r3, .L903+4
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldreq	ip, .L903+8
	movweq	r3, #4404
	beq	.L900
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L901
	cmp	r1, #0
	beq	.L902
	ldr	r3, .L903+12
	add	r0, r0, #1232
	mov	r2, #20
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
.L895:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L901:
	ldr	ip, .L903+16
	movw	r3, #4405
.L899:
	ldr	r2, .L903+20
	mov	r0, #0
	ldr	r1, .L903+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L895
.L902:
	ldr	ip, .L903+28
	mov	r0, r1
	movw	r3, #4406
.L900:
	ldr	r2, .L903+20
	ldr	r1, .L903+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L895
.L904:
	.align	2
.L903:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC122
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC123
	.word	.LANCHOR0+720
	.word	.LC0
	.word	.LC124
	UNWIND(.fnend)
	.size	VCTRL_ConfigPVRInfo, .-VCTRL_ConfigPVRInfo
	.align	2
	.global	VCTRL_IsChanActive
	.type	VCTRL_IsChanActive, %function
VCTRL_IsChanActive:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L912
	ldr	r3, .L913
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L911
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L911
	ldr	r2, [r3, #8]
	cmp	r2, #0
	beq	.L911
	ldr	r2, [r3, #20]
	cmp	r2, #0
	beq	.L911
	ldr	r0, [r3, #568]
	cmp	r0, #22
	movne	r0, #0
	mvneq	r0, #0
.L907:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L911:
	mvn	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L912:
	ldr	ip, .L913+4
	movw	r3, #4415
	ldr	r2, .L913+8
	mov	r0, #0
	ldr	r1, .L913+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L907
.L914:
	.align	2
.L913:
	.word	.LANCHOR1
	.word	.LC65
	.word	.LANCHOR0+740
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_IsChanActive, .-VCTRL_IsChanActive
	.align	2
	.global	USERDEC_Init
	.type	USERDEC_Init, %function
USERDEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r1
	mov	r5, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L932
	ldr	r3, .L934
	mov	r1, r4
	ldr	r7, [r0, #352]
	mov	r2, #368
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r5, #8
	str	r7, [r5, #352]
	bl	ResetVoQueue
	ldr	r0, .L934+4
	mov	r1, r4
	str	r6, [r5]
	b	.L920
.L918:
	add	r1, r1, #1
	cmp	r1, #32
	beq	.L933
.L920:
	ldr	r2, [r0], #4
	cmp	r2, #0
	add	r3, r2, #294912
	add	r3, r3, #1232
	beq	.L918
	cmp	r5, r3
	bne	.L918
	cmn	r1, #1
	str	r1, [r5, #360]
	beq	.L919
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L933:
	mvn	r3, #0
	str	r3, [r5, #360]
.L919:
	ldr	r1, .L934+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L932:
	ldr	r2, .L934+12
	mov	r0, #0
	ldr	r1, .L934+16
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L935:
	.align	2
.L934:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC126
	.word	.LANCHOR0+760
	.word	.LC125
	UNWIND(.fnend)
	.size	USERDEC_Init, .-USERDEC_Init
	.align	2
	.global	USERDEC_RecycleImage
	.type	USERDEC_RecycleImage, %function
USERDEC_RecycleImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L938
	mov	r2, #0
	ldr	r0, [r4, #360]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #360]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L939
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #360]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #360]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L939:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L938:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	USERDEC_RecycleImage, .-USERDEC_RecycleImage
	.align	2
	.global	VCTRL_GetUsrdecFrame
	.type	VCTRL_GetUsrdecFrame, %function
VCTRL_GetUsrdecFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r7, .L959
	mov	r6, r0
	mov	r5, r1
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L954
	ldr	r2, [r3, #568]
	cmp	r2, #20
	bne	.L955
	ldr	r3, [r3, #488]
	cmp	r3, #2
	ble	.L956
	mov	r1, #1
	bl	FSP_NewLogicFs
	subs	r8, r0, #0
	blt	.L957
	mov	r1, r8
	mov	r0, r6
	bl	FSP_GetLogicFs
	mov	r2, r8
	ldr	r1, .L959+4
	mov	r4, r0
	mov	r0, #18
	bl	dprint_vfmw
	cmp	r4, #0
	beq	.L958
	ldr	r2, [r4, #28]
	cmp	r2, #0
	beq	.L947
	ldr	r3, [r4, #32]
	cmp	r3, #0
	beq	.L947
	ldr	r2, [r2, #8]
	mov	r0, #18
	ldr	r3, [r3, #8]
	ldr	r1, .L959+8
	bl	dprint_vfmw
	ldr	r3, [r4, #28]
	ldr	r3, [r3, #8]
	str	r3, [r5, #40]
	ldr	r3, [r7, r6, asl #2]
	ldr	r3, [r3, #484]
	str	r3, [r5, #20]
	ldr	r3, [r4, #28]
	ldr	r3, [r3, #20]
	str	r3, [r5, #24]
	ldr	r3, [r4, #28]
	ldr	r0, [r3, #20]
	bl	MEM_Phy2Vir
	mov	r3, #0
	mov	r2, r3
	str	r3, [r5, #36]
	str	r0, [r5, #32]
.L942:
	mov	r0, r2
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L955:
	ldr	r1, .L959+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L942
.L956:
	ldr	r1, .L959+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L942
.L947:
	ldr	r1, .L959+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L942
.L957:
	ldr	r1, .L959+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L942
.L954:
	ldr	ip, .L959+28
	mov	r0, r3
	ldr	r2, .L959+32
	movw	r3, #4607
	ldr	r1, .L959+36
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L942
.L958:
	movw	r2, #4635
	ldr	r1, .L959+40
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L942
.L960:
	.align	2
.L959:
	.word	.LANCHOR1
	.word	.LC130
	.word	.LC132
	.word	.LC127
	.word	.LC128
	.word	.LC133
	.word	.LC129
	.word	.LC2
	.word	.LANCHOR0+776
	.word	.LC0
	.word	.LC131
	UNWIND(.fnend)
	.size	VCTRL_GetUsrdecFrame, .-VCTRL_GetUsrdecFrame
	.align	2
	.global	InitSyntaxCtx
	.type	InitSyntaxCtx, %function
InitSyntaxCtx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, .L980
	ldr	r1, [r3, r0, asl #2]
	cmp	r1, #0
	beq	.L979
	ldr	r3, [r1, #568]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L961
.L965:
	.word	.L964
	.word	.L966
	.word	.L967
	.word	.L968
	.word	.L961
	.word	.L969
	.word	.L970
	.word	.L961
	.word	.L971
	.word	.L972
	.word	.L973
	.word	.L973
	.word	.L973
	.word	.L974
	.word	.L961
	.word	.L975
	.word	.L976
	.word	.L977
	.word	.L961
	.word	.L961
	.word	.L978
.L978:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	USERDEC_Init
.L964:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_Init
.L966:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_Init
.L967:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_Init
.L968:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_Init
.L969:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_Init
.L970:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_Init
.L971:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_Init
.L972:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_Init
.L973:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_Init
.L974:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_Init
.L975:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_Init
.L976:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_Init
.L977:
	add	r0, r1, #294912
	add	r1, r1, #576
	add	r0, r0, #1232
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_Init
.L979:
	ldr	ip, .L980+4
	mov	r0, r1
	movw	r3, #4684
	ldr	r2, .L980+8
	ldr	r1, .L980+12
	str	ip, [sp]
	bl	dprint_vfmw
.L961:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L981:
	.align	2
.L980:
	.word	.LANCHOR1
	.word	.LC2
	.word	.LANCHOR0+800
	.word	.LC0
	UNWIND(.fnend)
	.size	InitSyntaxCtx, .-InitSyntaxCtx
	.align	2
	.global	VCTRL_VarifyOption
	.type	VCTRL_VarifyOption, %function
VCTRL_VarifyOption:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #36]
	cmp	r3, #0
	blt	.L983
	ldr	r3, [r0, #12]
	cmp	r3, #31
	ble	.L983
	ldr	r3, [r0, #16]
	cmp	r3, #31
	ble	.L983
	ldr	r3, [r0, #56]
	cmp	r3, #262144
	blt	.L983
	ldr	r3, [r0, #44]
	cmp	r3, #1
	beq	.L989
	cmp	r3, #2
	bne	.L987
	ldr	r3, [r0, #20]
	cmp	r3, #0
	ble	.L983
	ldr	r3, [r0, #24]
	cmp	r3, #0
	ble	.L983
.L988:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	ble	.L983
	ldr	r3, [r0, #32]
	cmp	r3, #0
	bgt	.L987
.L983:
	ldr	r1, .L990
	mov	r0, #32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L987:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L989:
	ldr	r3, [r0, #20]
	cmp	r3, #0
	bgt	.L988
	b	.L983
.L991:
	.align	2
.L990:
	.word	.LC134
	UNWIND(.fnend)
	.size	VCTRL_VarifyOption, .-VCTRL_VarifyOption
	.align	2
	.global	VCTRL_GetMemSize_onDecode
	.type	VCTRL_GetMemSize_onDecode, %function
VCTRL_GetMemSize_onDecode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	ldr	r3, [r1, #40]
	mov	r4, r1
	mov	r6, r0
	cmp	r3, #0
	mov	r5, r2
	ldr	r1, [r1, #36]
	moveq	r0, #1
	beq	.L994
	add	r0, r1, #1
	cmp	r0, #17
	movge	r0, #17
.L994:
	ldr	r3, .L1007
	sub	r2, r6, #27
	cmp	r2, #6
	ldr	r2, [r4, #60]
	ldr	r7, [r3, #64]
	mvncc	ip, #1
	mvncs	ip, #0
	cmp	r7, #0
	beq	.L998
	ldr	lr, .L1007+4
	add	r1, r2, r1
	ldr	r3, [r4, #16]
	add	r1, r1, #2
	ldr	r2, [r4, #12]
	str	r1, [sp, #4]
	mvn	r1, #-2147483648
	str	r0, [sp]
	mov	r0, #0
	str	ip, [sp, #12]
	str	r0, [sp, #8]
	mov	r0, #1
	str	lr, [sp, #16]
	blx	r7
	cmp	r0, #0
	bne	.L998
	ldr	r3, .L1007+8
	cmp	r6, #26
	movwne	r1, #14496
	movweq	r1, #62768
	ldr	r2, [r3, #-2920]
	movtne	r1, 12
	movteq	r1, 177
	add	r3, r2, #16
	str	r3, [r5]
	ldr	r3, [r4, #192]
	cmp	r3, #1
	addne	r2, r2, #307200
	ldreq	r3, [r4, #56]
	addne	r2, r2, #2576
	strne	r2, [r5]
	ldrne	r3, [r4, #56]
	addeq	r3, r3, #339968
	addeq	r3, r3, #2576
	str	r1, [r5, #8]
	addne	r3, r3, #32768
	str	r3, [r5, #4]
	ldr	r3, [r4, #44]
	cmp	r3, #0
	movweq	r3, #57056
	movteq	r3, 9
	beq	.L1002
	ldr	r0, [r4, #20]
	movw	ip, #4060
	ldr	r7, [r4, #28]
	mov	r3, #4000
	ldr	lr, [r4, #32]
	mov	r2, #2208
	mul	r0, ip, r0
	mla	r3, r3, r7, r0
	mla	r3, r2, lr, r3
	cmp	r3, #0
	movcc	r3, #0
	cmp	r6, #26
	beq	.L1003
	movw	r2, #57056
	movt	r2, 9
	cmp	r3, r2
	movcc	r3, r2
.L1002:
	mov	r0, #0
	add	r3, r3, r1
	str	r3, [r5, #8]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L998:
	movw	r2, #4839
	ldr	r1, .L1007+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1003:
	movw	r2, #3992
	mov	ip, #2240
	mla	r0, r2, r7, r0
	movw	r2, #57056
	movt	r2, 9
	mla	lr, ip, lr, r0
	cmp	lr, r2
	movcc	lr, r2
	cmp	lr, r3
	movcs	r3, lr
	b	.L1002
.L1008:
	.align	2
.L1007:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR3-2920
	.word	.LANCHOR3
	.word	.LC135
	UNWIND(.fnend)
	.size	VCTRL_GetMemSize_onDecode, .-VCTRL_GetMemSize_onDecode
	.align	2
	.global	VCTRL_GetChanMemSize
	.type	VCTRL_GetChanMemSize, %function
VCTRL_GetChanMemSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r3, #2
	mov	r5, r0
	mov	r4, r1
	mov	r6, r2
	beq	.L1010
	ldr	r1, .L1018
	ldr	r2, [r4, #36]
	ldr	ip, [r4, #60]
	ldr	r3, [r1, #-1688]
	ldr	lr, [r1, #-1684]
	add	r1, r2, r3
	cmp	r1, #16
	add	r0, ip, lr
	movge	r1, #16
	orrs	r7, r1, r0
	strpl	r1, [r4, #36]
	strpl	r0, [r4, #60]
	bmi	.L1017
.L1010:
	mov	r0, r4
	bl	VCTRL_VarifyOption
	cmp	r0, #0
	bne	.L1012
	mov	r2, r6
	mov	r1, r4
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_GetMemSize_onDecode
.L1017:
	stmia	sp, {ip, lr}
	mov	r0, #32
	ldr	r1, .L1018+4
	bl	dprint_vfmw
.L1012:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1019:
	.align	2
.L1018:
	.word	.LANCHOR3
	.word	.LC136
	UNWIND(.fnend)
	.size	VCTRL_GetChanMemSize, .-VCTRL_GetChanMemSize
	.align	2
	.global	CloseDrivers
	.type	CloseDrivers, %function
CloseDrivers:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, [r0, #72]
	mov	r4, r0
	cmp	r5, #0
	beq	.L1021
	ldr	r5, [r0, #88]
	adds	r5, r5, #0
	movne	r5, #1
.L1021:
	ldr	r6, [r4, #16]
	ldr	r7, [r4, #8]
	cmp	r6, #0
	ldr	r8, [r4, #4]
	beq	.L1022
	ldr	r3, .L1085
	ldr	r3, [r3, #60]
	cmp	r3, #0
	beq	.L1074
	mov	r0, #0
	blx	r3
.L1027:
	cmp	r5, #0
	beq	.L1025
.L1026:
	ldr	r3, .L1085+4
	mov	r2, #24
	mov	r1, #0
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
.L1022:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	ldr	r6, [r4, #64]
	ldr	r7, [r4, #56]
	cmp	r6, #0
	ldr	r8, [r4, #52]
	beq	.L1028
	ldr	r3, .L1085
	ldr	r3, [r3, #60]
	cmp	r3, #0
	beq	.L1075
	mov	r0, #0
	blx	r3
.L1033:
	cmp	r5, #0
	beq	.L1031
.L1032:
	ldr	r3, .L1085+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #48
	ldr	r3, [r3, #48]
	blx	r3
.L1028:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	ldr	r6, [r4, #40]
	ldr	r7, [r4, #32]
	cmp	r6, #0
	ldr	r8, [r4, #28]
	bne	.L1076
.L1034:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	bl	SM_InstInit
	ldr	r5, [r4, #112]
	ldr	r6, [r4, #104]
	cmp	r5, #0
	ldr	r7, [r4, #100]
	bne	.L1077
.L1037:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #184]
	ldr	r6, [r4, #176]
	cmp	r5, #0
	ldr	r7, [r4, #172]
	bne	.L1078
.L1038:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #160]
	ldr	r6, [r4, #152]
	cmp	r5, #0
	ldr	r7, [r4, #148]
	bne	.L1079
.L1039:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #136]
	ldr	r6, [r4, #128]
	cmp	r5, #0
	ldr	r7, [r4, #124]
	bne	.L1080
.L1040:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #208]
	ldr	r6, [r4, #200]
	cmp	r5, #0
	ldr	r7, [r4, #196]
	bne	.L1081
.L1041:
	ldr	r4, .L1085+8
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r3, [r4, #376]
	cmp	r3, #1
	beq	.L1082
	ldr	r3, [r4, #380]
	ldr	r5, .L1085+8
	cmp	r3, #1
	beq	.L1083
.L1043:
	ldr	r3, [r4, #384]
	ldr	r4, .L1085+8
	cmp	r3, #1
	beq	.L1084
.L1044:
	bl	HEVCDEC_ReleaseHevcGlbMem
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1076:
	mov	r0, #0
	bl	SM_CloseSCDDrv
	cmp	r5, #0
	beq	.L1035
.L1036:
	ldr	r3, .L1085+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, r2
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1034
.L1077:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1085+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #96
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1037
.L1081:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1085+4
	add	r0, r4, #192
	mov	r2, #24
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1041
.L1080:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1085+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #120
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1040
.L1079:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1085+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #144
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1039
.L1078:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1085+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #168
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1038
.L1074:
	mov	r0, r3
	movw	r2, #5178
	ldr	r1, .L1085+12
	bl	dprint_vfmw
	b	.L1027
.L1075:
	mov	r0, r3
	movw	r2, #5198
	ldr	r1, .L1085+12
	bl	dprint_vfmw
	b	.L1033
.L1084:
	ldr	r3, .L1085+4
	mov	r0, #13
	ldr	r5, [r3, #208]
	bl	VFMW_GetString
	ldr	r2, .L1085+16
	mov	r1, r0
	mov	r0, #181
	blx	r5
	mov	r3, #0
	str	r3, [r4, #384]
	b	.L1044
.L1031:
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #56]
	bl	MEM_ReleaseMemBlock
	b	.L1032
.L1025:
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_ReleaseMemBlock
	b	.L1026
.L1082:
	ldr	r3, .L1085+4
	mov	r0, #0
	ldr	r5, [r3, #208]
	bl	VFMW_GetString
	ldr	r2, .L1085+16
	mov	r1, r0
	mov	r0, #127
	blx	r5
	mov	r3, #0
	str	r3, [r4, #376]
	ldr	r3, [r4, #380]
	ldr	r5, .L1085+8
	cmp	r3, #1
	bne	.L1043
.L1083:
	ldr	r3, .L1085+4
	mov	r0, #4
	ldr	r6, [r3, #208]
	bl	VFMW_GetString
	ldr	r2, .L1085+16
	mov	r1, r0
	mov	r0, #136
	blx	r6
	mov	r3, #0
	str	r3, [r5, #380]
	b	.L1043
.L1035:
	ldr	r1, [r4, #28]
	ldr	r0, [r4, #32]
	bl	MEM_ReleaseMemBlock
	b	.L1036
.L1086:
	.align	2
.L1085:
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC44
	.word	.LANCHOR3-1680
	UNWIND(.fnend)
	.size	CloseDrivers, .-CloseDrivers
	.align	2
	.global	OpenDrivers
	.type	OpenDrivers, %function
OpenDrivers:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	add	r5, r0, #96
	mov	r4, r0
	mov	r0, #0
	mov	r1, #65536
	mov	r2, r5
	movt	r0, 63683
	bl	MEM_MapRegisterAddr
	subs	r6, r0, #0
	bne	.L1088
	ldr	r2, [r4, #112]
	add	r5, r4, #168
	ldr	r1, [r4, #100]
	ldr	r0, [r4, #104]
	bl	MEM_AddMemRecord
	mov	r0, #53248
	mov	r2, r5
	movt	r0, 63683
	mov	r1, #4096
	bl	MEM_MapRegisterAddr
	subs	r7, r0, #0
	beq	.L1125
	mov	r2, #53248
	ldr	r1, .L1130
	movt	r2, 63683
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r3, .L1130+4
	mov	r1, r6
	mov	r0, r5
.L1115:
	mov	r2, #24
.L1114:
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
.L1091:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1125:
	ldr	r2, [r4, #184]
	add	r9, r4, #144
	ldr	r1, [r4, #172]
	ldr	r0, [r4, #176]
	bl	MEM_AddMemRecord
	mov	r0, #49152
	mov	r2, r9
	movt	r0, 63683
	mov	r1, #4096
	bl	MEM_MapRegisterAddr
	subs	r6, r0, #0
	bne	.L1092
	ldr	r5, .L1130+4
	ldr	r2, [r4, #160]
	ldr	r1, [r4, #148]
	ldr	r0, [r4, #152]
	bl	MEM_AddMemRecord
	mov	r0, #15
	ldr	r7, [r5, #68]
	bl	VFMW_GetString
	ldr	r8, .L1130+8
	mov	r3, r6
	mov	r1, #20
	mov	r2, r0
	sub	r0, fp, #84
	blx	r7
	ldr	r3, [r8, #48]
	cmp	r3, #0
	beq	.L1094
	blx	r3
	subs	r2, r0, #0
	ble	.L1094
	str	r6, [sp]
	mov	r7, #3
	mov	r3, r4
	str	r7, [r4, #20]
	mov	r1, r6
	sub	r0, fp, #84
	bl	MEM_AllocMemBlock
	subs	r9, r0, #0
	bne	.L1095
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_AddMemRecord
	ldr	r3, [r5, #48]
	mov	r2, #20
	mov	r1, r9
	sub	r0, fp, #64
	blx	r3
	ldr	r3, [r8, #56]
	ldr	r1, [r4, #8]
	ldr	r2, [r4, #16]
	cmp	r3, #0
	str	r9, [fp, #-56]
	str	r1, [fp, #-64]
	str	r2, [fp, #-60]
	beq	.L1096
	sub	r0, fp, #64
	blx	r3
	subs	r8, r0, #0
	bne	.L1096
	str	r7, [r4, #68]
	mov	r0, #16
	ldr	r6, [r5, #68]
	bl	VFMW_GetString
	add	r9, r4, #48
	mov	r3, r8
	mov	r1, #20
	mov	r2, r0
	sub	r0, fp, #84
	blx	r6
	mov	r1, #1
	mov	r3, r9
	str	r1, [sp]
	mov	r2, #16384
	mov	r1, r8
	sub	r0, fp, #84
	bl	MEM_AllocMemBlock
	subs	r6, r0, #0
	bne	.L1097
	add	r3, r4, #24
	ldr	r1, [r4, #52]
	ldr	r2, [r4, #64]
	ldr	r0, [r4, #56]
	mov	r9, r3
	str	r3, [fp, #-92]
	bl	MEM_AddMemRecord
	ldr	r2, .L1130+12
	mov	r0, r6
	ldr	r3, [r4, #56]
	str	r3, [r2, #1196]
	ldr	r3, [r4, #56]
	add	r3, r3, #5120
	str	r3, [r2, #1200]
	bl	VDMDRV_Init
	mov	r0, #17
	ldr	r8, [r5, #68]
	bl	VFMW_GetString
	mov	r3, r6
	mov	r1, #20
	mov	r2, r0
	sub	r0, fp, #84
	blx	r8
	str	r7, [r4, #44]
	mov	r1, r6
	str	r6, [sp]
	sub	r0, fp, #84
	mov	r3, r9
	mov	r2, #716800
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L1126
	ldr	r2, [r4, #40]
	ldr	r1, [r4, #28]
	ldr	r0, [r4, #32]
	bl	MEM_AddMemRecord
	mov	r2, #0
	ldr	r1, [r4, #40]
	ldr	r0, [r4, #32]
	bl	SM_OpenSCDDrv
	subs	r7, r0, #0
	bne	.L1100
	ldr	r6, .L1130+16
	bl	SM_InstInit
	mov	r0, r7
	ldr	r8, [r5, #204]
	ldr	r5, .L1130+20
	ldr	r9, [r6, #92]
	bl	VFMW_GetString
	ldr	r1, .L1130+24
	str	r5, [sp]
	mov	r2, r9
	ldr	r9, .L1130+4
	mov	r3, r0
	mov	r0, #127
	blx	r8
	subs	r3, r0, #0
	str	r3, [fp, #-96]
	bne	.L1127
	ldr	r2, [r6, #92]
	mov	r0, #4
	ldr	r7, .L1130+28
	mov	r8, #1
	ldr	r10, [r9, #204]
	str	r2, [fp, #-88]
	str	r8, [r7, #376]
	bl	VFMW_GetString
	str	r5, [sp]
	ldr	r2, [fp, #-88]
	ldr	r1, .L1130+32
	mov	r3, r0
	mov	r0, #136
	blx	r10
	subs	r3, r0, #0
	str	r3, [fp, #-88]
	bne	.L1128
	mov	r0, #13
	ldr	r10, [r6, #92]
	str	r8, [r7, #380]
	ldr	r6, [r9, #204]
	bl	VFMW_GetString
	str	r5, [sp]
	mov	r2, r10
	ldr	r1, .L1130+36
	mov	r3, r0
	mov	r0, #181
	blx	r6
	subs	r5, r0, #0
	bne	.L1129
	str	r8, [r7, #384]
	bl	HEVCDEC_AllocHevcGlbMem
	cmp	r0, #0
	beq	.L1091
	ldr	r1, .L1130+40
	mov	r0, r5
	bl	dprint_vfmw
	mov	r0, r5
	b	.L1091
.L1088:
	mov	r2, #0
	ldr	r1, .L1130
	movt	r2, 63683
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, .L1130+4
	mov	r0, r5
	mov	r2, #24
	mov	r1, #0
	b	.L1114
.L1094:
	mov	r2, #0
	ldr	r1, .L1130+44
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	mov	r0, r9
.L1116:
	mov	r2, #24
	mov	r1, #0
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1091
.L1092:
	mov	r2, #49152
	ldr	r1, .L1130
	movt	r2, 63683
	mov	r0, r7
	bl	dprint_vfmw
	ldr	r3, .L1130+4
	mov	r1, r7
	mov	r0, r9
	b	.L1115
.L1096:
	mov	r2, #0
	ldr	r1, .L1130+48
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	mov	r2, #24
	mov	r1, #0
.L1120:
	mov	r0, r4
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1091
.L1127:
	ldr	r1, .L1130+52
	mov	r2, #127
	mov	r0, r7
	bl	dprint_vfmw
	ldr	r3, [r9, #48]
	mov	r1, r7
.L1118:
	ldr	r0, [fp, #-92]
.L1121:
	mov	r2, #24
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1091
.L1128:
	ldr	r1, .L1130+52
	mov	r2, #136
	ldr	r5, [fp, #-96]
.L1117:
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r3, [r9, #48]
	mov	r1, r5
	b	.L1118
.L1129:
	mov	r2, #181
	ldr	r1, .L1130+52
	ldr	r5, [fp, #-88]
	b	.L1117
.L1100:
	ldr	r1, .L1130+56
	mov	r2, #0
.L1119:
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	ldr	r0, [fp, #-92]
	b	.L1116
.L1126:
	mov	r2, #0
	ldr	r1, .L1130+60
	b	.L1119
.L1095:
	mov	r2, r6
	ldr	r1, .L1130+64
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	mov	r1, r6
	mov	r2, #24
	b	.L1120
.L1097:
	ldr	r1, .L1130+68
	mov	r2, r8
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	mov	r1, r8
	mov	r0, r9
	b	.L1121
.L1131:
	.align	2
.L1130:
	.word	.LC137
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	g_HwMem
	.word	.LANCHOR2
	.word	.LANCHOR3-1680
	.word	VCTRL_Isr_0
	.word	.LANCHOR1
	.word	VCTRL_Scd_Isr
	.word	VCTRL_MMU_ISR
	.word	.LC145
	.word	.LC138
	.word	.LC140
	.word	.LC144
	.word	.LC143
	.word	.LC142
	.word	.LC139
	.word	.LC141
	UNWIND(.fnend)
	.size	OpenDrivers, .-OpenDrivers
	.align	2
	.global	VCTRL_OpenVfmw
	.type	VCTRL_OpenVfmw, %function
VCTRL_OpenVfmw:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	subs	r8, r0, #0
	beq	.L1164
	ldr	r4, .L1169
	mov	r2, #8
	ldr	r7, .L1169+4
	sub	r0, fp, #52
	mov	r1, #0
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r5, [r7, #128]
	cmp	r5, #0
	bne	.L1163
	mov	r1, #1024
	ldr	r3, [r4, #80]
	str	r5, [fp, #-56]
	ldr	r0, .L1169+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1169+12
	ldr	r0, .L1169+8
	blx	r3
	ldr	r6, .L1169+16
	cmp	r0, #0
	str	r0, [fp, #-56]
	beq	.L1136
	ldr	r3, [r4, #92]
	sub	r0, fp, #56
	ldr	r1, .L1169+20
	blx	r3
	cmp	r0, #0
	beq	.L1155
	sub	r0, fp, #56
	ldr	r3, [r4, #92]
	ldr	r1, .L1169+24
	blx	r3
	cmp	r0, #0
	beq	.L1165
	mov	r2, r5
	ldr	r3, [r4, #84]
	mov	r1, r5
	blx	r3
	mov	r2, r0
	str	r0, [r6, #-1688]
.L1140:
	add	r3, r2, #4992
	movw	r1, #10000
	add	r3, r3, #8
	movw	r9, #5000
	cmp	r3, r1
	bhi	.L1141
	cmp	r2, r9
	movw	r3, #60536
.L1162:
	movt	r3, 65535
	movge	r2, r9
	cmp	r2, r3
	movlt	r2, r3
.L1137:
	str	r2, [r6, #-1688]
.L1139:
	mov	r9, #0
	ldr	r3, [r4, #80]
	mov	r1, #1024
	str	r9, [fp, #-56]
	ldr	r0, .L1169+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1169+28
	ldr	r0, .L1169+8
	blx	r3
	ldr	r10, .L1169
	cmp	r0, r9
	str	r0, [fp, #-56]
	beq	.L1142
	ldr	r2, [r10, #92]
	sub	r0, fp, #56
	ldr	r1, .L1169+20
	blx	r2
	cmp	r0, r9
	beq	.L1143
	sub	r0, fp, #56
	ldr	r2, [r10, #92]
	ldr	r1, .L1169+24
	blx	r2
	cmp	r0, r9
	beq	.L1166
	ldr	r3, [r10, #84]
	mov	r2, r9
	mov	r1, r9
	blx	r3
	ldr	r3, .L1169+16
	mov	r2, r0
	str	r0, [r3, #-1684]
.L1146:
	add	r3, r2, #4992
	movw	r1, #10000
	add	r3, r3, #8
	movw	r9, #5000
	cmp	r3, r1
	bhi	.L1147
	cmp	r2, r9
	movw	r3, #60536
	movt	r3, 65535
	movlt	r5, r2
	movge	r5, r9
	cmp	r5, r3
	movlt	r5, r3
.L1143:
	str	r5, [r6, #-1684]
.L1145:
	ldr	r5, [r6, #-652]
	mov	r3, #0
	ldr	r9, .L1169+16
	cmp	r5, r3
	str	r3, [fp, #-56]
	beq	.L1148
	ldr	r2, .L1169+32
	and	r3, r5, #1
	ubfx	r1, r5, #1, #1
	strb	r3, [r9, #-648]
	ubfx	r3, r5, #2, #1
	ubfx	r5, r5, #3, #1
	strb	r1, [r2, #96]
	strb	r3, [r9, #-647]
	strb	r5, [r9, #-646]
.L1149:
	ldr	r5, .L1169+4
	mov	r2, #264
	ldr	r3, [r4, #48]
	mov	r1, #0
	add	r0, r5, #128
	mov	r9, #1
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #128
	mov	r1, #0
	mov	r0, r5
	blx	r3
	ldr	r1, .L1169+36
	sub	r0, fp, #52
	mov	r2, #134217728
	mov	r3, #75497472
	str	r2, [fp, #-52]
	str	r1, [r6, #-644]
	str	r3, [fp, #-48]
	str	r9, [r7, #132]
	bl	MEM_InitMemManager
	bl	FSP_Init
	ldr	r6, .L1169
	bl	ChanCtx_Init
	ldr	r3, [r4, #48]
	mov	r2, #128
	mov	r1, #0
	ldr	r0, .L1169+40
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r8, #8
	mov	r2, #24
	add	r0, r5, #224
	blx	r3
	add	r0, r5, #152
	bl	OpenDrivers
	cmp	r0, #0
	bne	.L1163
	ldr	r3, [r6, #124]
	mov	r1, r9
	blx	r3
	ldr	r3, [r6, #200]
	ldr	r2, .L1169+44
	add	r0, r5, #140
	ldr	r1, .L1169+48
	blx	r3
	cmp	r0, #0
	streq	r9, [r5, #128]
	bne	.L1167
.L1134:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1148:
	ldr	r3, [r4, #80]
	mov	r1, #1024
	ldr	r0, .L1169+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1169+52
	ldr	r0, .L1169+8
	blx	r3
	ldr	r10, .L1169
	cmp	r0, #0
	str	r0, [fp, #-56]
	beq	.L1149
	ldr	r3, [r10, #92]
	sub	r0, fp, #56
	ldr	r1, .L1169+20
	blx	r3
	cmp	r0, #0
	ldreq	r0, [r9, #-652]
	beq	.L1151
	sub	r0, fp, #56
	ldr	r3, [r10, #92]
	ldr	r1, .L1169+24
	blx	r3
	cmp	r0, #0
	beq	.L1168
	ldr	r3, [r10, #84]
	mov	r2, r5
	mov	r1, r5
	blx	r3
	str	r0, [r9, #-652]
.L1151:
	ldr	r2, .L1169+32
	and	r3, r0, #1
	ubfx	r1, r0, #1, #1
	strb	r3, [r6, #-648]
	ubfx	r3, r0, #2, #1
	ubfx	r0, r0, #3, #1
	strb	r1, [r2, #96]
	strb	r3, [r6, #-647]
	strb	r0, [r6, #-646]
	b	.L1149
.L1142:
	ldr	r3, .L1169+16
	ldr	r2, [r3, #-1684]
	b	.L1146
.L1136:
	ldr	r2, [r6, #-1688]
	b	.L1140
.L1141:
	ldr	r1, .L1169+56
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r2, [r6, #-1688]
	movw	r3, #60536
	cmp	r2, r9
	b	.L1162
.L1147:
	ldr	r1, .L1169+60
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r5, [r6, #-1684]
	movw	r3, #60536
	cmp	r5, r9
	movt	r3, 65535
	movge	r5, r9
	cmp	r5, r3
	movlt	r5, r3
	b	.L1143
.L1155:
	mov	r2, r5
	b	.L1137
.L1167:
	add	r0, r5, #152
	bl	CloseDrivers
.L1163:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1166:
	movw	r3, #6026
	ldr	r2, .L1169+64
	ldr	r1, .L1169+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1145
.L1165:
	movw	r3, #5984
	ldr	r2, .L1169+72
	ldr	r1, .L1169+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1139
.L1168:
	movw	r3, #6077
	ldr	r2, .L1169+76
	ldr	r1, .L1169+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1149
.L1164:
	ldr	ip, .L1169+80
	movw	r3, #938
	ldr	r2, .L1169+84
	ldr	r1, .L1169+88
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1134
.L1170:
	.align	2
.L1169:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LANCHOR3-1676
	.word	.LC147
	.word	.LANCHOR3
	.word	.LC148
	.word	.LC149
	.word	.LC152
	.word	.LANCHOR2
	.word	VCTRL_EventReport
	.word	.LANCHOR3-640
	.word	VFMW_CTRL_thread_proc
	.word	.LC155
	.word	.LC154
	.word	.LC151
	.word	.LC153
	.word	.LANCHOR0+852
	.word	.LC150
	.word	.LANCHOR0+832
	.word	.LANCHOR0+872
	.word	.LC146
	.word	.LANCHOR0+816
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_OpenVfmw, .-VCTRL_OpenVfmw
	.align	2
	.global	GetNextDecodeMode
	.type	GetNextDecodeMode, %function
GetNextDecodeMode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	mov	r4, r2
	mov	ip, r4, asl #1
	movw	r2, #21846
	cmp	r4, #0
	movt	r2, 21845
	smull	r2, r3, ip, r2
	add	r5, r4, #7
	movge	r5, r4
	mov	r6, r0
	mov	r5, r5, asr #3
	str	r1, [sp, #4]
	str	r4, [sp]
	mov	r7, r1
	sub	r3, r3, ip, asr #31
	ldr	r1, .L1179
	mov	r2, r5
	mov	r0, #30
	bl	dprint_vfmw
	cmp	r6, #3
	beq	.L1177
	cmp	r4, r7
	movge	r4, r6
	blt	.L1178
.L1173:
	mov	r2, r6
	mov	r3, r4
	ldr	r1, .L1179+4
	mov	r0, #30
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1178:
	ldr	r1, .L1179+8
	mov	r0, #30
	bl	dprint_vfmw
.L1176:
	mov	r4, #3
	b	.L1173
.L1177:
	cmp	r5, r7
	ble	.L1176
	ldr	r1, .L1179+12
	mov	r0, #30
	bl	dprint_vfmw
	mov	r4, #0
	b	.L1173
.L1180:
	.align	2
.L1179:
	.word	.LC156
	.word	.LC159
	.word	.LC158
	.word	.LC157
	UNWIND(.fnend)
	.size	GetNextDecodeMode, .-GetNextDecodeMode
	.align	2
	.global	VCTRL_GetChanIDByCtx
	.type	VCTRL_GetChanIDByCtx, %function
VCTRL_GetChanIDByCtx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L1191
	mov	r2, #0
	b	.L1184
.L1182:
	add	r2, r2, #1
	cmp	r2, #32
	beq	.L1190
.L1184:
	ldr	r1, [ip], #4
	cmp	r1, #0
	add	r3, r1, #294912
	add	r3, r3, #1232
	beq	.L1182
	cmp	r0, r3
	bne	.L1182
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L1190:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1192:
	.align	2
.L1191:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_GetChanIDByCtx, .-VCTRL_GetChanIDByCtx
	.align	2
	.global	VCTRL_GetChanIDByMemAddr
	.type	VCTRL_GetChanIDByMemAddr, %function
VCTRL_GetChanIDByMemAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L1205
	mov	lr, #0
.L1198:
	ldr	r1, [r4], #4
	cmp	r1, #0
	beq	.L1194
	add	r1, r1, #290816
	add	r3, r1, #1168
	add	r1, r1, #3472
.L1197:
	ldr	r2, [r3]
	cmp	r2, r0
	bhi	.L1195
	ldr	ip, [r3, #-20]
	add	r2, r2, ip
	cmp	r0, r2
	bcc	.L1199
.L1195:
	add	r3, r3, #72
	cmp	r3, r1
	bne	.L1197
.L1194:
	add	lr, lr, #1
	cmp	lr, #32
	bne	.L1198
	mvn	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L1199:
	mov	r0, lr
	ldmfd	sp, {r4, fp, sp, pc}
.L1206:
	.align	2
.L1205:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_GetChanIDByMemAddr, .-VCTRL_GetChanIDByMemAddr
	.align	2
	.global	DecChanProcessPts
	.type	DecChanProcessPts, %function
DecChanProcessPts:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r6, .L1234
	mov	r5, r0
	mov	r4, r1
	ldr	ip, [r6, r0, asl #2]
	ldr	r2, [ip, #52]
	cmp	r2, #1
	beq	.L1229
	cmp	r2, #6
	cmpne	r2, #18
	sub	r1, r2, #2
	moveq	r3, #1
	movne	r3, #0
	cmp	r1, #1
	orrls	r3, r3, #1
	cmp	r3, #0
	bne	.L1209
.L1210:
	ldrd	r2, [r4, #32]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1230
	add	r1, ip, #640
	strd	r2, [r1]
.L1220:
	ldrd	r8, [r4, #48]
	add	r0, ip, #656
	add	lr, ip, #672
	ldr	r1, .L1234+4
	strd	r8, [r0]
	mov	r0, #29
	ldrd	r6, [r4, #56]
	strd	r6, [lr]
	ldr	lr, [r4, #64]
	str	lr, [ip, #688]
	ldr	lr, [r4, #68]
	str	lr, [ip, #692]
	ldr	lr, [r4, #72]
	str	lr, [ip, #696]
	ldr	lr, [r4, #76]
	str	lr, [ip, #712]
	ldrb	lr, [r4, #15]	@ zero_extendqisi2
	strb	lr, [ip, #632]
	strd	r8, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1229:
	add	r3, ip, #294912
	ldr	r3, [r3, #1232]
	ldr	r2, [r3, #564]
	sxtb	r2, r2
	cmp	r2, #1
	bne	.L1210
.L1209:
	add	r1, ip, #1136
	add	r3, r4, #8
	mov	r0, r5
	bl	IsNewpicSeg
	cmp	r0, #0
	beq	.L1231
.L1211:
	ldr	r1, [r6, r5, asl #2]
	ldr	r3, [r1, #52]
	cmp	r3, #3
	addeq	r0, r1, #656
	beq	.L1217
.L1216:
	ldrd	r2, [r4, #32]
	mvn	r7, #0
	mvn	r6, #0
	add	r0, r1, #656
	cmp	r3, r7
	cmpeq	r2, r6
	strned	r2, [r0, #-8]
.L1218:
	ldrd	r2, [r4, #48]
	add	lr, r1, #672
	add	ip, r1, #688
	strd	r2, [lr, #-8]
	ldrd	r2, [r4, #56]
	strd	r2, [ip, #-8]
	ldr	r3, [r4, #64]
	str	r3, [r1, #700]
	ldr	r3, [r4, #68]
	str	r3, [r1, #704]
	ldr	r3, [r4, #72]
	str	r3, [r1, #708]
	ldr	r3, [r4, #76]
	str	r3, [r1, #716]
.L1217:
	ldrd	r2, [r0]
	mov	r0, #29
	ldr	r1, .L1234+8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1231:
	ldr	ip, [r6, r5, asl #2]
	add	lr, ip, #656
	ldr	r3, [ip, #52]
	cmp	r3, #3
	beq	.L1232
	ldrd	r2, [lr, #-8]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1233
	add	r1, ip, #640
	strd	r2, [r1]
.L1213:
	add	r7, ip, #672
	mvn	r0, #0
	mvn	r1, #0
	strd	r0, [lr, #-8]
	ldrd	r0, [r7, #-8]
	add	r8, ip, #688
	strd	r0, [lr]
	ldrd	r0, [r8, #-8]
	orrs	lr, r0, r1
	strd	r0, [r7]
	ldreqd	r0, [r4, #56]
	streqd	r0, [r7]
.L1215:
	ldr	r1, [ip, #704]
	mov	r0, #29
	ldr	r7, [ip, #700]
	ldr	lr, [ip, #708]
	str	r1, [ip, #692]
	ldr	r1, [ip, #716]
	str	r7, [ip, #688]
	str	lr, [ip, #696]
	str	r1, [ip, #712]
	ldr	r1, .L1234+12
	bl	dprint_vfmw
	ldr	r1, [r6, r5, asl #2]
	ldr	r3, [r1, #52]
	cmp	r3, #3
	bne	.L1216
	ldrd	r2, [r4, #32]
	add	lr, r1, #656
	add	ip, r1, #672
	add	r0, r1, #688
	strd	r2, [lr, #-8]
	ldrd	r2, [r4, #48]
	strd	r2, [ip, #-8]
	ldrd	r2, [r4, #56]
	strd	r2, [r0, #-8]
	ldr	r3, [r4, #64]
	str	r3, [r1, #700]
	ldr	r3, [r4, #68]
	str	r3, [r1, #704]
	ldr	r3, [r4, #72]
	str	r3, [r1, #708]
	ldr	r3, [r4, #76]
	str	r3, [r1, #716]
	b	.L1211
.L1232:
	ldrd	r2, [lr, #-8]
	add	r1, ip, #640
	strd	r2, [r1]
	b	.L1213
.L1230:
	add	r3, ip, #640
	ldrd	r2, [r3]
	b	.L1220
.L1233:
	add	r3, ip, #640
	ldrd	r2, [r3]
	b	.L1213
.L1235:
	.align	2
.L1234:
	.word	.LANCHOR1
	.word	.LC162
	.word	.LC161
	.word	.LC160
	UNWIND(.fnend)
	.size	DecChanProcessPts, .-DecChanProcessPts
	.align	2
	.global	DecChanCheckDecParam
	.type	DecChanCheckDecParam, %function
DecChanCheckDecParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L1244
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #568]
	sub	r3, r2, #10
	cmp	r3, #2
	bhi	.L1237
	ldr	r3, .L1244+4
	ldr	r3, [r3, #-3180]
	ands	r3, r3, #1
	beq	.L1238
.L1237:
	bic	r3, r2, #16
	cmp	r3, #4
	cmpne	r2, #14
	movne	r3, #1
	moveq	r3, #0
	beq	.L1238
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	mvnne	r3, #1
	moveq	r3, #0
.L1238:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1245:
	.align	2
.L1244:
	.word	.LANCHOR1
	.word	.LANCHOR3
	UNWIND(.fnend)
	.size	DecChanCheckDecParam, .-DecChanCheckDecParam
	.align	2
	.global	DecChanSyntax
	.type	DecChanSyntax, %function
DecChanSyntax:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	cmp	r0, #31
	mov	r4, r0
	ldrhi	ip, .L1290
	movwhi	r3, #5638
	bhi	.L1279
	ldr	r6, .L1290+4
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	beq	.L1282
	ldr	r3, [r0, #8]
	cmp	r3, #1
	bne	.L1283
	ldr	r5, [r0, #24]
	cmp	r5, #0
	ldrne	ip, .L1290+8
	movwne	r3, #5641
	bne	.L1279
	ldr	r8, .L1290+12
	mov	r7, r4, asl #2
	str	r5, [r0, #404]
	ldr	r9, .L1290+16
	ldr	r3, [r8]
	blx	r3
	add	r2, r9, r7
	ldr	r3, [r2, #-512]
	mov	r1, r0
	ldr	r0, .L1290+20
	rsb	r3, r3, r1
	ldr	r0, [r0]
	cmp	r3, r0
	mov	r0, r4
	bls	.L1252
	str	r1, [r2, #-512]
	bl	DecChanCheckDecParam
	cmn	r0, #2
	mov	r10, r0
	bne	.L1253
	mov	r2, r4
	ldr	r1, .L1290+24
	mov	r0, #23
	bl	dprint_vfmw
.L1269:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1252:
	bl	DecChanCheckDecParam
	cmn	r0, #2
	mov	r10, r0
	beq	.L1269
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	cmp	r0, #1
	mvnne	r10, #2
	bne	.L1269
.L1263:
	ldr	r1, [r6, r4, asl #2]
	add	r3, r1, #262144
	ldr	r3, [r3, #2016]
	cmp	r3, #1
	beq	.L1284
	cmp	r3, #3
	beq	.L1285
	ldrb	r3, [r1, #721]	@ zero_extendqisi2
	add	r10, r1, #720
	cmp	r3, #0
	bne	.L1256
	ldr	r3, [r1, #1496]
	cmp	r3, #0
	beq	.L1286
.L1256:
	ldrd	r2, [r10, #32]
	mov	r0, #29
	ldr	r1, .L1290+28
	strd	r2, [fp, #-52]
	ldrd	r2, [r10, #48]
	strd	r2, [sp]
	ldrd	r2, [fp, #-52]
	bl	dprint_vfmw
	mov	r1, r10
	mov	r0, r4
	bl	DecChanProcessPts
	mov	r0, #3
	bl	CHECK_REC_POS_ENABLE
	adds	r3, r0, #0
	movne	r3, #1
	cmp	r5, #1
	movne	r3, #0
	cmp	r3, #0
	bne	.L1287
.L1258:
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r10
	add	r2, r3, #294912
	add	r2, r2, #1232
	ldr	r1, [r3, #568]
	bl	DecodeStream
	mov	r0, #4
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1288
.L1280:
	mov	r10, #0
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1253:
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	cmp	r0, #1
	moveq	r5, r0
	beq	.L1263
	mov	r2, r4
	ldr	r1, .L1290+32
	mov	r0, #23
	mvn	r10, #2
	bl	dprint_vfmw
	b	.L1269
.L1283:
	ldr	ip, .L1290+36
	movw	r3, #5640
.L1279:
	ldr	r2, .L1290+40
	mov	r0, #0
	ldr	r1, .L1290+44
	mvn	r10, #0
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1269
.L1288:
	ldr	r3, [r8]
	add	r7, r9, r7
	blx	r3
	ldr	r1, .L1290+48
	ldr	r3, [r7, #-384]
	ldr	r1, [r1]
	rsb	r3, r3, r0
	mov	r2, r0
	cmp	r3, r1
	bls	.L1280
	mov	r0, r4
	str	r2, [r7, #-384]
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L1280
	mov	r2, r4, asl #24
	movw	r1, #5740
	add	r2, r2, #262144
	ldr	r0, .L1290+52
	bl	DBG_AddTrace
	b	.L1280
.L1286:
	add	r1, r1, #728
	mov	r0, r4
	bl	SM_ReadSegStream
	cmp	r0, #0
	beq	.L1256
	cmp	r5, #1
	beq	.L1289
.L1257:
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #1
	mvn	r10, #3
	str	r2, [r3, #404]
	b	.L1269
.L1287:
	mov	r2, r4, asl #24
	movw	r1, #5722
	add	r2, r2, #196608
	ldr	r0, .L1290+52
	bl	DBG_AddTrace
	b	.L1258
.L1282:
	ldr	ip, .L1290+56
	movw	r3, #5639
	ldr	r2, .L1290+40
	mvn	r10, #0
	ldr	r1, .L1290+44
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1269
.L1284:
	ldr	r1, .L1290+60
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r10, #2
	b	.L1269
.L1285:
	ldr	r2, [r1, #1448]
	mov	r0, #31
	ldr	r1, .L1290+64
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L1269
.L1289:
	mov	r2, r4
	ldr	r1, .L1290+68
	mov	r0, #23
	bl	dprint_vfmw
	b	.L1257
.L1291:
	.align	2
.L1290:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC163
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	g_TraceBsPeriod
	.word	.LC164
	.word	.LC169
	.word	.LC165
	.word	.LC121
	.word	.LANCHOR0+888
	.word	.LC0
	.word	g_TraceFramePeriod
	.word	.LANCHOR0+904
	.word	.LC110
	.word	.LC166
	.word	.LC167
	.word	.LC168
	UNWIND(.fnend)
	.size	DecChanSyntax, .-DecChanSyntax
	.align	2
	.global	DecSyntax
	.type	DecSyntax, %function
DecSyntax:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r0, .L1324
	ldr	r1, .L1324+4
	sub	r3, r0, #128
.L1295:
	ldr	r2, [r1, #4]!
	add	r3, r3, #4
	cmp	r2, #0
	ldrne	r2, [r2, #20]
	str	r2, [r3, #-4]
	cmp	r3, r0
	bne	.L1295
	ldr	r7, .L1324+8
	mvn	r5, #0
	ldr	r8, .L1324+12
	mov	r9, #0
	mov	r10, r7
.L1296:
	mov	r3, #0
	ldr	r0, [r8, #-256]
	mov	r4, r3
	ldr	r1, .L1324+16
	b	.L1297
.L1299:
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	movlt	r0, r2
	movlt	r4, r3
.L1297:
	add	r3, r3, #1
	cmp	r3, #32
	bne	.L1299
	add	r3, r8, r4, lsl #2
	cmp	r0, #0
	add	r2, r4, #1
	mov	r1, #0
	str	r9, [r3, #-256]
	str	r2, [r7, #148]
	ldr	r3, .L1324+8
	ble	.L1300
	ldr	r3, [r10, r4, asl #2]
	cmp	r3, r1
	beq	.L1296
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bne	.L1296
	ldr	r2, [r3, #76]
	cmp	r2, r1
	ble	.L1302
	ldr	r5, [r3, #80]
	cmp	r5, r1
	beq	.L1322
.L1302:
	mov	r6, #500
	b	.L1310
.L1305:
	cmp	r0, #0
	ldr	r3, [r7, r4, asl #2]
	bne	.L1308
	ldr	r2, [r3, #1528]
	cmp	r2, #1
	beq	.L1308
	subs	r6, r6, #1
	beq	.L1296
.L1310:
	mov	r0, r4
	bl	DecChanSyntax
	cmn	r0, #1
	mov	r5, r0
	bne	.L1305
	ldr	r6, [r8, #-644]
	cmp	r6, #0
	beq	.L1316
	mov	r3, #0
	mov	r0, r4
	mov	r2, r3
	mov	r1, #102
	blx	r6
.L1316:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1308:
	str	r9, [r3, #1528]
	b	.L1296
.L1322:
	mov	r0, r4
	sub	r1, fp, #68
	bl	SM_GetInfo
	cmp	r0, #0
	bne	.L1323
.L1303:
	ldr	r5, [r7, r4, asl #2]
	ldr	r1, [fp, #-56]
	ldr	r2, [r5, #76]
	ldr	r0, [r5, #584]
	bl	GetNextDecodeMode
	ldr	r3, [r7, r4, asl #2]
	str	r0, [r5, #584]
	ldr	r2, [r3, #584]
	cmp	r2, #0
	strne	r9, [r3, #580]
	strne	r9, [r3, #576]
	ldreq	r2, [r3, #72]
	streq	r2, [r3, #580]
	streq	r2, [r3, #576]
	b	.L1302
.L1300:
	mov	r0, r5
	str	r1, [r3, #148]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1323:
	ldr	r3, .L1324+20
	mov	r1, r5
	sub	r0, fp, #68
	mov	r2, #24
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1303
.L1325:
	.align	2
.L1324:
	.word	.LANCHOR3-128
	.word	.LANCHOR1-4
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	.LANCHOR3-256
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	DecSyntax, .-DecSyntax
	.align	2
	.global	VCTRL_RunProcess
	.type	VCTRL_RunProcess, %function
VCTRL_RunProcess:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L1337
	mov	r0, #0
	bl	VCTRL_RecordPosTime
	ldrb	r3, [r5, #1792]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1335
.L1327:
	ldr	r0, [r5, #912]
	mov	r3, #100
	ldr	r6, .L1337+4
	cmp	r0, #0
	str	r3, [r5, #144]
	ble	.L1328
	ldr	r3, [r6, #120]
	blx	r3
.L1328:
	ldr	r3, [r6, #12]
	mov	r0, #0
	blx	r3
	bl	SM_Wakeup
	ldr	r3, [r5, #908]
	mov	r2, #101
	str	r2, [r5, #144]
	cmp	r3, #0
	movne	r7, #0
	beq	.L1336
.L1329:
	mov	r3, #102
	str	r3, [r5, #144]
	bl	VDMDRV_WakeUpVdm
	mov	r4, #0
.L1330:
	mov	r0, r4
	mov	r1, #0
	add	r4, r4, #1
	bl	DeleteRawPacketInBuffer
	cmp	r4, #32
	bne	.L1330
	ldr	r3, [r6, #16]
	mov	r0, #0
	blx	r3
	mov	r0, #1
	mov	r3, #105
	str	r3, [r5, #144]
	bl	VCTRL_RecordPosTime
	mov	r1, #0
	ldr	r3, [r6, #132]
	mov	r0, r1
	mov	r2, #10
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1336:
	bl	DecSyntax
	mov	r7, r0
	b	.L1329
.L1335:
	mov	r0, #11
	bl	VCTRL_RecordPosTime
	mov	r3, #0
	strb	r3, [r5, #1792]
	b	.L1327
.L1338:
	.align	2
.L1337:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_RunProcess, .-VCTRL_RunProcess
	.align	2
	.global	VFMW_CTRL_thread_proc
	.type	VFMW_CTRL_thread_proc, %function
VFMW_CTRL_thread_proc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L1366
	ldr	r6, .L1366+4
.L1340:
.L1347:
	ldr	r1, .L1366+8
	mov	r0, #2
	mov	r3, #0
	str	r3, [r4, #144]
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	mov	r5, #2
	str	r5, [r4, #132]
	cmp	r3, r5
	bne	.L1362
	b	.L1345
.L1364:
	str	r5, [r4, #144]
	bl	VCTRL_RunProcess
	ldr	r1, .L1366+12
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	cmp	r3, #2
	beq	.L1345
.L1362:
	cmp	r3, #3
	bne	.L1364
.L1343:
	ldr	r1, .L1366+16
	mov	r0, #2
	mov	r3, #6
	str	r3, [r4, #144]
	bl	dprint_vfmw
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #132]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1345:
	ldr	r1, .L1366+20
	mov	r0, #2
	mov	r3, #4
	str	r3, [r4, #144]
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [r4, #132]
	b	.L1342
.L1365:
	ldr	r3, [r6, #120]
	blx	r3
.L1342:
	ldr	r1, .L1366+24
	mov	r0, #22
	mov	r3, #5
	str	r3, [r4, #144]
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	mov	r0, #10
	cmp	r3, #1
	beq	.L1347
	cmp	r3, #3
	bne	.L1365
	b	.L1343
.L1367:
	.align	2
.L1366:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC170
	.word	.LC172
	.word	.LC174
	.word	.LC171
	.word	.LC173
	UNWIND(.fnend)
	.size	VFMW_CTRL_thread_proc, .-VFMW_CTRL_thread_proc
	.align	2
	.global	VCTRL_GetChanVoQue
	.type	VCTRL_GetChanVoQue, %function
VCTRL_GetChanVoQue:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L1387
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L1385
	ldr	r2, [r3, #568]
	cmp	r2, #20
	ldrls	pc, [pc, r2, asl #2]
	b	.L1386
.L1371:
	.word	.L1384
	.word	.L1372
	.word	.L1373
	.word	.L1374
	.word	.L1386
	.word	.L1375
	.word	.L1376
	.word	.L1386
	.word	.L1377
	.word	.L1378
	.word	.L1379
	.word	.L1379
	.word	.L1379
	.word	.L1380
	.word	.L1386
	.word	.L1381
	.word	.L1382
	.word	.L1383
	.word	.L1386
	.word	.L1386
	.word	.L1384
.L1384:
	movw	r0, #34008
	movt	r0, 4
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1372:
	movw	r0, #17784
	movt	r0, 5
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1373:
	add	r0, r3, #315392
	add	r0, r0, #3376
	ldmfd	sp, {fp, sp, pc}
.L1374:
	add	r0, r3, #380928
	add	r0, r0, #3920
	ldmfd	sp, {fp, sp, pc}
.L1375:
	add	r0, r3, #335872
	add	r0, r0, #2800
	ldmfd	sp, {fp, sp, pc}
.L1376:
	add	r0, r3, #311296
	add	r0, r0, #1040
	ldmfd	sp, {fp, sp, pc}
.L1377:
	movw	r0, #23320
	movt	r0, 5
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1378:
	add	r0, r3, #348160
	add	r0, r0, #2832
	ldmfd	sp, {fp, sp, pc}
.L1379:
	add	r0, r3, #307200
	add	r0, r0, #1632
	ldmfd	sp, {fp, sp, pc}
.L1380:
	add	r0, r3, #303104
	add	r0, r0, #1248
	ldmfd	sp, {fp, sp, pc}
.L1381:
	movw	r0, #34584
	movt	r0, 4
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1382:
	add	r0, r3, #299008
	add	r0, r0, #2688
	ldmfd	sp, {fp, sp, pc}
.L1383:
	movw	r0, #47688
	movt	r0, 8
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1386:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1385:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1388:
	.align	2
.L1387:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_GetChanVoQue, .-VCTRL_GetChanVoQue
	.align	2
	.global	VCTRL_FindOccupiedFrame
	.type	VCTRL_FindOccupiedFrame, %function
VCTRL_FindOccupiedFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	cmp	r0, #31
	mov	r5, r0
	bhi	.L1405
	bl	VCTRL_GetChanVoQue
	subs	r4, r0, #0
	beq	.L1400
	sub	r2, fp, #36
	mov	r3, #0
	sub	r1, fp, #44
	str	r3, [fp, #-44]
	str	r3, [r2, #-4]!
	bl	GetQueueImgNum
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	beq	.L1400
	cmp	r2, #32
	bhi	.L1393
.L1396:
	ldr	r3, .L1407
	ldrh	r1, [r4, #4]
	ldr	r0, [r3, r5, asl #2]
	and	r1, r1, #63
	add	lr, r0, #294912
	add	r1, r4, r1, lsl #2
	ldr	r3, [lr, #1152]
	ldr	r1, [r1, #12]
	cmp	r3, #32
	bhi	.L1394
	add	r0, r0, r3, lsl #4
	mov	r6, #0
	add	r0, r0, #294912
	mov	r7, #0
	mov	ip, #1
	add	r0, r0, #628
	mov	r8, #0
	b	.L1397
.L1398:
	ldrh	r1, [r4, #4]
	cmp	r3, #33
	add	r1, r1, ip
	add	ip, ip, #1
	and	r1, r1, #63
	add	r1, r4, r1, lsl #2
	ldr	r1, [r1, #12]
	beq	.L1394
.L1397:
	ldr	r1, [r1, #20]
	cmp	ip, r2
	strd	r6, [r0, #4]
	add	r3, r3, #1
	str	r8, [r0, #-4]
	add	r0, r0, #16
	str	r1, [r0, #-16]
	str	r3, [lr, #1152]
	bcc	.L1398
.L1404:
	mov	r0, #0
.L1406:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1400:
	mvn	r0, #0
.L1391:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1394:
	mov	r2, r5
	ldr	r1, .L1407+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1406
.L1393:
	mov	r3, #32
	ldr	r1, .L1407+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	bne	.L1396
	b	.L1404
.L1405:
	ldr	ip, .L1407+12
	movw	r3, #3086
	ldr	r2, .L1407+16
	mov	r0, #0
	ldr	r1, .L1407+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1391
.L1408:
	.align	2
.L1407:
	.word	.LANCHOR1
	.word	.LC176
	.word	.LC175
	.word	.LC65
	.word	.LANCHOR0+920
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_FindOccupiedFrame, .-VCTRL_FindOccupiedFrame
	.align	2
	.global	VCTRL_ReportOccupiedFrame
	.type	VCTRL_ReportOccupiedFrame, %function
VCTRL_ReportOccupiedFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	cmp	r0, #31
	mov	r7, r0
	mov	r4, r1
	bhi	.L1426
	cmp	r1, #0
	beq	.L1427
	bl	VCTRL_GetChanVoQue
	subs	r5, r0, #0
	mvneq	r0, #0
	beq	.L1411
	ldr	r6, .L1429
	sub	r8, fp, #36
	mov	r3, #0
	mov	r0, #4
	str	r3, [r8, #-4]!
	str	r3, [fp, #-44]
	ldr	r3, [r6, #12]
	blx	r3
	mov	r2, r8
	sub	r1, fp, #44
	mov	r0, r5
	bl	GetQueueImgNum
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	beq	.L1413
	cmp	r2, #32
	bhi	.L1428
.L1414:
	mov	r1, #0
	mov	r0, r1
	mov	lr, r1
.L1416:
	ldrh	r3, [r5, #4]
	add	ip, r4, r0, lsl #4
	add	r1, r1, #1
	mov	r7, #0
	add	r3, r3, r0
	and	r3, r3, #63
	uxth	r1, r1
	add	r3, r5, r3, lsl #2
	ldr	r3, [r3, #12]
	ldr	r8, [r3, #20]
	str	r8, [ip, #4]
	ldr	r3, [r3, #504]
	str	r7, [ip, #12]
	str	r3, [ip, #8]
	str	lr, [r4, r0, asl #4]
	sxth	r0, r1
	cmp	r0, r2
	bcc	.L1416
	uxth	r3, r2
.L1415:
	ldrh	r1, [r5, #4]
	add	r3, r3, r1
	and	r3, r3, #63
	strh	r3, [r5, #4]	@ movhi
	str	r2, [r4, #528]
.L1417:
	ldr	r3, [r6, #16]
	mov	r0, #4
	blx	r3
	mov	r0, #0
.L1411:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1413:
	ldr	ip, .L1429+4
	ldr	r8, [ip, r7, asl #2]
	add	r3, r8, #294912
	ldr	r3, [r3, #1152]
	cmp	r3, #0
	beq	.L1417
	mov	r1, r2
	mov	lr, r2
.L1418:
	add	r5, r1, #18432
	mov	r9, r1, asl #4
	add	r5, r5, #39
	add	r0, r4, r9
	add	r2, r2, #1
	add	r5, r8, r5, lsl #4
	uxth	r2, r2
	ldr	r3, [r5, #4]
	str	r3, [r0, #4]
	ldr	r3, [ip, r7, asl #2]
	add	r3, r3, r9
	add	r3, r3, #294912
	add	r3, r3, #632
	ldrd	r8, [r3]
	mov	r9, #0
	strd	r8, [r0, #8]
	str	lr, [r4, r1, asl #4]
	sxth	r1, r2
	ldr	r8, [ip, r7, asl #2]
	add	r3, r8, #294912
	ldr	r3, [r3, #1152]
	cmp	r1, r3
	bcc	.L1418
	str	r3, [r4, #528]
	b	.L1417
.L1428:
	mov	r3, #32
	ldr	r1, .L1429+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	moveq	r3, r2
	bne	.L1414
	b	.L1415
.L1426:
	ldr	ip, .L1429+12
	movw	r3, #3162
	ldr	r2, .L1429+16
	mov	r0, #0
	ldr	r1, .L1429+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1411
.L1427:
	ldr	ip, .L1429+24
	mov	r0, r1
	movw	r3, #3163
	ldr	r2, .L1429+16
	ldr	r1, .L1429+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1411
.L1430:
	.align	2
.L1429:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC175
	.word	.LC65
	.word	.LANCHOR0+944
	.word	.LC0
	.word	.LC177
	UNWIND(.fnend)
	.size	VCTRL_ReportOccupiedFrame, .-VCTRL_ReportOccupiedFrame
	.align	2
	.global	VCTRL_GetChanImgNum
	.type	VCTRL_GetChanImgNum, %function
VCTRL_GetChanImgNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r8, r1, #0
	mov	r5, r2
	mov	r6, r3
	mov	r4, r0
	beq	.L1444
	cmp	r2, #0
	beq	.L1445
	cmp	r3, #0
	beq	.L1446
	cmp	r0, #31
	bhi	.L1447
	ldr	r7, .L1453
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L1448
	bl	VCTRL_GetChanVoQue
	subs	r3, r0, #0
	beq	.L1438
	mov	r2, r6
	mov	r1, r5
	bl	GetQueueImgNum
	ldr	r2, [r7, r4, asl #2]
	ldr	r3, [r2, #568]
	cmp	r3, #0
	beq	.L1449
	cmp	r3, #16
	beq	.L1450
	cmp	r3, #17
	moveq	r3, #9
	streq	r3, [r8]
	beq	.L1431
	cmp	r3, #15
	beq	.L1451
	cmp	r3, #18
	movne	r3, #2
	strne	r3, [r8]
	beq	.L1452
.L1431:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1438:
	str	r3, [r6]
	str	r3, [r5]
	str	r3, [r8]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1447:
	ldr	ip, .L1453+4
	movw	r3, #5849
	ldr	r2, .L1453+8
	mov	r0, #0
	ldr	r1, .L1453+12
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1449:
	add	r2, r2, #319488
	ldr	r3, [r2, #3368]
	str	r3, [r8]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1450:
	add	r2, r2, #294912
	ldr	r3, [r2, #3796]
	str	r3, [r8]
	b	.L1431
.L1452:
	ldr	r2, .L1453+8
	mov	r0, #32
	ldr	r1, .L1453+16
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L1444:
	ldr	ip, .L1453+20
	mov	r0, r8
	movw	r3, #5846
	ldr	r2, .L1453+8
	ldr	r1, .L1453+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1431
.L1445:
	ldr	ip, .L1453+24
	mov	r0, r2
	movw	r3, #5847
	ldr	r2, .L1453+8
	ldr	r1, .L1453+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1431
.L1446:
	ldr	ip, .L1453+28
	mov	r0, r3
	ldr	r2, .L1453+8
	movw	r3, #5848
	ldr	r1, .L1453+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1431
.L1451:
	add	r2, r2, #11403264
	add	r2, r2, #16384
	ldr	r3, [r2, #56]
	str	r3, [r8]
	b	.L1431
.L1448:
	ldr	ip, .L1453+32
	mov	r0, r3
	ldr	r2, .L1453+8
	movw	r3, #5850
	ldr	r1, .L1453+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1431
.L1454:
	.align	2
.L1453:
	.word	.LANCHOR1
	.word	.LC65
	.word	.LANCHOR0+972
	.word	.LC0
	.word	.LC181
	.word	.LC178
	.word	.LC179
	.word	.LC180
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_GetChanImgNum, .-VCTRL_GetChanImgNum
	.align	2
	.global	VCTRL_GetChanState
	.type	VCTRL_GetChanState, %function
VCTRL_GetChanState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #48)
	sub	sp, sp, #48
	subs	r4, r1, #0
	mov	r5, r0
	beq	.L1465
	cmp	r0, #31
	bhi	.L1466
	ldr	r6, .L1468
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	beq	.L1467
	ldr	r3, .L1468+4
	mov	r7, #0
	mov	r1, r7
	mov	r2, #100
	str	r7, [fp, #-56]
	mov	r0, r4
	ldr	r3, [r3, #48]
	str	r7, [fp, #-60]
	str	r7, [fp, #-64]
	blx	r3
	ldr	r2, [r6, r5, asl #2]
	movw	r3, #1987
	ldr	r2, [r2, #1152]
	str	r2, [r4, #32]
	ldr	r2, [r6, r5, asl #2]
	ldr	r2, [r2, #1156]
	str	r2, [r4, #36]
	ldr	r2, [r6, r5, asl #2]
	ldr	r2, [r2, #1160]
	str	r2, [r4, #44]
	ldr	r2, [r6, r5, asl #2]
	add	r1, r2, #262144
	ldrsb	ip, [r1, r3]
	cmp	ip, r7
	ble	.L1463
	movw	r3, #23890
	mov	r1, r7
	movt	r3, 4
	add	r3, r2, r3
	mov	r0, r7
.L1462:
	ldrsb	r2, [r3]
	add	r1, r1, #1
	add	r3, r3, #88
	cmp	r2, #3
	addeq	r0, r0, #1
	cmp	r1, ip
	bne	.L1462
.L1460:
	str	r0, [r4, #84]
	movw	lr, #1987
	ldr	ip, [r6, r5, asl #2]
	sub	r3, fp, #56
	sub	r2, fp, #60
	sub	r1, fp, #64
	add	ip, ip, #262144
	mov	r0, r5
	ldrsb	ip, [ip, lr]
	str	ip, [r4, #92]
	bl	VCTRL_GetChanImgNum
	ldr	r2, .L1468+8
	mov	r3, r5, asl #5
	ldr	ip, [fp, #-60]
	sub	r3, r3, r5, asl #3
	sub	r1, fp, #52
	add	r3, r2, r3
	ldr	r2, [fp, #-56]
	mov	r0, r5
	add	r2, ip, r2
	str	r2, [r4, #48]
	ldr	r2, [r3, #-108]
	str	r2, [r4, #96]
	ldr	r3, [r3, #-120]
	str	r3, [r4, #20]
	bl	SM_GetInfo
	ldr	r3, [fp, #-32]
	ldr	r1, [fp, #-36]
	ldr	r2, [fp, #-44]
	cmp	r3, #10
	str	r1, [r4, #52]
	movle	r3, #0
	movgt	r3, #1
	str	r2, [r4, #56]
	str	r3, [r4, #80]
	ldr	r3, [r6, r5, asl #2]
	add	r3, r3, #311296
	ldrb	r3, [r3, #720]	@ zero_extendqisi2
	and	r3, r3, #1
	str	r3, [r4, #88]
.L1455:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1466:
	ldr	ip, .L1468+12
	mov	r3, #1264
	ldr	r2, .L1468+16
	mov	r0, #0
	ldr	r1, .L1468+20
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1467:
	ldr	ip, .L1468+24
	movw	r3, #1265
	ldr	r2, .L1468+16
	ldr	r1, .L1468+20
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1455
.L1463:
	mov	r0, r7
	b	.L1460
.L1465:
	ldr	ip, .L1468+28
	mov	r0, r4
	movw	r3, #1263
	ldr	r2, .L1468+16
	ldr	r1, .L1468+20
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1455
.L1469:
	.align	2
.L1468:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	.LC99
	.word	.LANCHOR0+992
	.word	.LC0
	.word	.LC100
	.word	.LC182
	UNWIND(.fnend)
	.size	VCTRL_GetChanState, .-VCTRL_GetChanState
	.align	2
	.global	VCTRL_GetChanWidth
	.type	VCTRL_GetChanWidth, %function
VCTRL_GetChanWidth:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L1474
	ldr	r3, .L1476
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #1268]
	beq	.L1475
.L1472:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1474:
	ldr	ip, .L1476+4
	movw	r3, #5913
	ldr	r2, .L1476+8
	mov	r0, #0
	ldr	r1, .L1476+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1472
.L1475:
	ldr	ip, .L1476+16
	movw	r3, #5914
	ldr	r2, .L1476+8
	ldr	r1, .L1476+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1472
.L1477:
	.align	2
.L1476:
	.word	.LANCHOR1
	.word	.LC65
	.word	.LANCHOR0+1012
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_GetChanWidth, .-VCTRL_GetChanWidth
	.align	2
	.global	VCTRL_GetChanHeight
	.type	VCTRL_GetChanHeight, %function
VCTRL_GetChanHeight:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L1482
	ldr	r3, .L1484
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #1272]
	beq	.L1483
.L1480:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1482:
	ldr	ip, .L1484+4
	movw	r3, #5921
	ldr	r2, .L1484+8
	mov	r0, #0
	ldr	r1, .L1484+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1480
.L1483:
	ldr	ip, .L1484+16
	movw	r3, #5922
	ldr	r2, .L1484+8
	ldr	r1, .L1484+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1480
.L1485:
	.align	2
.L1484:
	.word	.LANCHOR1
	.word	.LC65
	.word	.LANCHOR0+1032
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_GetChanHeight, .-VCTRL_GetChanHeight
	.align	2
	.global	VCTRL_GetChanCapLevel
	.type	VCTRL_GetChanCapLevel, %function
VCTRL_GetChanCapLevel:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L1490
	ldr	r3, .L1491
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r0, [r3, #36]
	moveq	r0, #33
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1490:
	ldr	ip, .L1491+4
	movw	r3, #5929
	ldr	r2, .L1491+8
	mov	r0, #0
	ldr	r1, .L1491+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1492:
	.align	2
.L1491:
	.word	.LANCHOR1
	.word	.LC65
	.word	.LANCHOR0+1052
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_GetChanCapLevel, .-VCTRL_GetChanCapLevel
	.align	2
	.global	VCTRL_SetVdecExtra
	.type	VCTRL_SetVdecExtra, %function
VCTRL_SetVdecExtra:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #4992
	ldr	r5, .L1500
	add	r3, r3, #8
	movw	r2, #10000
	cmp	r3, r2
	mov	r4, r1
	str	r0, [r5, #-1688]
	bhi	.L1498
.L1494:
	movw	r1, #5000
	cmp	r0, r1
	movw	r2, #60536
	add	r3, r4, #4992
	movge	r0, r1
	movt	r2, 65535
	cmp	r0, r2
	add	r3, r3, #8
	movw	r1, #10000
	str	r4, [r5, #-1684]
	movlt	r0, r2
	cmp	r3, r1
	str	r0, [r5, #-1688]
	ldr	r6, .L1500
	bhi	.L1499
.L1495:
	movw	r2, #5000
	cmp	r4, r2
	movw	r3, #60536
	movge	r4, r2
	movt	r3, 65535
	cmp	r4, r3
	movlt	r4, r3
	str	r4, [r5, #-1684]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1498:
	mov	r2, r0
	ldr	r1, .L1500+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r0, [r5, #-1688]
	b	.L1494
.L1499:
	mov	r2, r4
	ldr	r1, .L1500+8
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r4, [r6, #-1684]
	b	.L1495
.L1501:
	.align	2
.L1500:
	.word	.LANCHOR3
	.word	.LC183
	.word	.LC184
	UNWIND(.fnend)
	.size	VCTRL_SetVdecExtra, .-VCTRL_SetVdecExtra
	.align	2
	.global	VfmwProcGetHandler
	.type	VfmwProcGetHandler, %function
VfmwProcGetHandler:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r1, r0, #0
	ldrne	r3, .L1514
	bne	.L1506
	b	.L1512
.L1507:
	ldr	r2, [r3, #8]!
	cmp	r2, r1
	beq	.L1513
.L1506:
	ldr	r0, [r3, #12]
	cmp	r0, #0
	bne	.L1507
	ldmfd	sp, {fp, sp, pc}
.L1513:
	ldmfd	sp, {fp, sp, pc}
.L1512:
	ldr	r0, .L1514+4
	ldmfd	sp, {fp, sp, pc}
.L1515:
	.align	2
.L1514:
	.word	.LANCHOR0+1076
	.word	VfmwProc_SetPrintLevel
	UNWIND(.fnend)
	.size	VfmwProcGetHandler, .-VfmwProcGetHandler
	.align	2
	.global	VCTRL_SetDbgOption
	.type	VCTRL_SetDbgOption, %function
VCTRL_SetDbgOption:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	beq	.L1523
	cmp	r0, #0
	ldrne	r3, .L1529
	bne	.L1521
	b	.L1528
.L1522:
	ldr	ip, [r3, #8]!
	cmp	r0, ip
	beq	.L1519
.L1521:
	ldr	r4, [r3, #12]
	cmp	r4, #0
	bne	.L1522
	mov	r2, r0
	ldr	r1, .L1529+4
	mov	r0, #32
	bl	dprint_vfmw
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1528:
	ldr	r4, .L1529+8
.L1519:
	mov	r0, r1
	blx	r4
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1523:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1530:
	.align	2
.L1529:
	.word	.LANCHOR0+1076
	.word	.LC185
	.word	VfmwProc_SetPrintLevel
	UNWIND(.fnend)
	.size	VCTRL_SetDbgOption, .-VCTRL_SetDbgOption
	.align	2
	.global	VCTRL_SetLastFrameState
	.type	VCTRL_SetLastFrameState, %function
VCTRL_SetLastFrameState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L1537
	ldr	r3, .L1538
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	strne	r1, [r3, #408]
	ldmfd	sp, {fp, sp, pc}
.L1537:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_SetLastFrameState.part.23
.L1539:
	.align	2
.L1538:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_SetLastFrameState, .-VCTRL_SetLastFrameState
	.align	2
	.global	VCTRL_ReportLastFrame
	.type	VCTRL_ReportLastFrame, %function
VCTRL_ReportLastFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	subs	r5, r1, #0
	mov	r4, r0
	moveq	r2, #2
	beq	.L1542
	cmp	r5, #1
	moveq	r2, #3
	movne	r2, #4
.L1542:
	cmp	r4, #31
	bhi	.L1554
	ldr	r7, .L1555
	ldr	r3, [r7, r4, asl #2]
	cmp	r3, #0
	strne	r2, [r3, #408]
.L1545:
	ldr	r3, .L1555+4
	ldr	r6, [r3, #-644]
	cmp	r6, #0
	beq	.L1546
	sub	r2, fp, #28
	mov	r3, #4
	mov	r1, #115
	mov	r0, r4
	str	r5, [r2, #-4]!
	blx	r6
.L1546:
	ldr	ip, [r7, r4, asl #2]
	mov	r3, r5
	mov	r2, r4
	ldr	r1, .L1555+8
	mov	r0, #1
	ldr	ip, [ip, #408]
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1554:
	bl	VCTRL_SetLastFrameState.part.23
	ldr	r7, .L1555
	b	.L1545
.L1556:
	.align	2
.L1555:
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	.LC186
	UNWIND(.fnend)
	.size	VCTRL_ReportLastFrame, .-VCTRL_ReportLastFrame
	.align	2
	.global	VCTRL_OutputLastFrame
	.type	VCTRL_OutputLastFrame, %function
VCTRL_OutputLastFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	mov	r5, r0
	bhi	.L1584
	ldr	r3, .L1587
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1585
	add	r0, r0, #294912
	ldr	r3, [r0, #1224]
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L1577
.L1563:
	.word	.L1562
	.word	.L1564
	.word	.L1565
	.word	.L1566
	.word	.L1577
	.word	.L1567
	.word	.L1568
	.word	.L1577
	.word	.L1569
	.word	.L1570
	.word	.L1571
	.word	.L1571
	.word	.L1571
	.word	.L1572
	.word	.L1577
	.word	.L1573
	.word	.L1574
	.word	.L1575
.L1577:
	mov	r0, r5
	mov	r1, #1
	bl	VCTRL_ReportLastFrame
	ldr	r1, .L1587+4
	mov	r0, #2
	bl	dprint_vfmw
	mvn	r0, #0
.L1559:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1575:
	add	r0, r0, #1232
	bl	VP9DEC_GetRemainImg
	mov	r4, r0
.L1561:
	cmn	r4, #1
	beq	.L1577
	cmp	r4, #0
	bne	.L1586
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_ReportLastFrame
	ldr	r1, .L1587+8
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1562:
	add	r0, r0, #1232
	bl	H264DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1565:
	add	r0, r0, #1232
	bl	MPEG4DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1566:
	add	r0, r0, #1232
	bl	MPEG2DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1564:
	add	r0, r0, #1232
	bl	VC1DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1567:
	add	r0, r0, #1232
	bl	DIVX3DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1568:
	add	r0, r0, #1232
	bl	AVSDEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1569:
	add	r0, r0, #1232
	bl	REAL8DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1570:
	add	r0, r0, #1232
	bl	REAL9DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1571:
	add	r0, r0, #1232
	bl	VP6DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1572:
	add	r0, r0, #1232
	bl	VP8DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1573:
	add	r0, r0, #1232
	bl	MVC_DEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1574:
	add	r0, r0, #1232
	bl	HEVCDEC_GetRemainImg
	mov	r4, r0
	b	.L1561
.L1586:
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_ReportLastFrame
	sub	r2, r4, #2
	ldr	r1, .L1587+12
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1584:
	ldr	ip, .L1587+16
	movw	r3, #7206
	ldr	r2, .L1587+20
	mov	r0, #0
	ldr	r1, .L1587+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1559
.L1585:
	ldr	ip, .L1587+28
	movw	r3, #7207
	ldr	r2, .L1587+20
	ldr	r1, .L1587+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1559
.L1588:
	.align	2
.L1587:
	.word	.LANCHOR1
	.word	.LC187
	.word	.LC188
	.word	.LC189
	.word	.LC65
	.word	.LANCHOR0+1436
	.word	.LC0
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_OutputLastFrame, .-VCTRL_OutputLastFrame
	.align	2
	.global	VCTRL_PostProc
	.type	VCTRL_PostProc, %function
VCTRL_PostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r5, .L1629
	mov	r4, r0
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L1622
	ldr	ip, [r0, #568]
	ldr	r6, [r0, #1208]
	cmp	ip, #17
	ldrls	pc, [pc, ip, asl #2]
	b	.L1589
.L1593:
	.word	.L1592
	.word	.L1594
	.word	.L1595
	.word	.L1596
	.word	.L1589
	.word	.L1597
	.word	.L1598
	.word	.L1589
	.word	.L1599
	.word	.L1600
	.word	.L1601
	.word	.L1601
	.word	.L1601
	.word	.L1602
	.word	.L1589
	.word	.L1603
	.word	.L1604
	.word	.L1605
.L1604:
	add	r0, r0, #294912
	str	r3, [sp, #4]
	add	r0, r0, #1232
	mov	r3, r2
	str	r6, [sp]
	mov	r2, #1
	bl	HEVCDEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r7, .L1629
	add	r3, r3, #294912
	ldrb	r3, [r3, #1241]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1623
.L1608:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #294912
	strne	r2, [r3, #3624]
.L1589:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1605:
	add	r0, r0, #294912
	mov	r2, r6
	add	r0, r0, #1232
	bl	VP9DEC_VDMPostProc
	cmp	r6, #1
	bne	.L1621
	b	.L1589
.L1592:
	add	r0, r0, #294912
	str	r3, [sp, #4]
	add	r0, r0, #1232
	mov	r3, r2
	str	r6, [sp]
	mov	r2, #1
	bl	H264DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r7, .L1629
	add	r3, r3, #307200
	ldrb	r3, [r3, #2504]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1624
.L1606:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #294912
	strne	r2, [r3, #1592]
	b	.L1589
.L1595:
	add	r0, r0, #294912
	add	r0, r0, #1232
	bl	MPEG4DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1629
	add	r2, r3, #315392
	ldrb	r2, [r2, #3764]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1625
.L1611:
	add	r3, r3, #294912
	mov	r2, #0
	str	r2, [r3, #2268]
	b	.L1589
.L1596:
	add	r0, r0, #294912
	ldr	r6, .L1629
	add	r0, r0, #1232
	bl	MPEG2DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #385024
	ldrb	r2, [r2, #194]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1626
.L1613:
	add	r3, r3, #294912
	mov	r2, #0
	str	r2, [r3, #1236]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1594:
	add	r0, r0, #294912
	ldr	r6, .L1629
	add	r0, r0, #1232
	bl	VC1DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #307200
	ldrb	r2, [r2, #1687]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1613
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #307200
	strb	r1, [r2, #1687]
	b	.L1613
.L1597:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetSwitchRounding
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	add	r0, r3, #294912
	add	r0, r0, #1232
	bl	DIVX3DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #294912
	str	r2, [r3, #1236]
	b	.L1589
.L1598:
	add	r0, r0, #294912
	ldr	r6, .L1629
	add	r0, r0, #1232
	bl	AVSDEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r3, r3, #294912
	ldrb	r2, [r3, #1232]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1627
.L1612:
	mov	r2, #0
	str	r2, [r3, #1248]
	b	.L1589
.L1599:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetMb0QpInCurrPic
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	add	r0, r3, #294912
	add	r0, r0, #1232
	bl	REAL8DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #294912
	str	r2, [r3, #1236]
	b	.L1589
.L1600:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetMb0QpInCurrPic
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	add	r0, r3, #294912
	add	r0, r0, #1232
	bl	REAL9DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #294912
	str	r2, [r3, #1236]
	b	.L1589
.L1601:
	add	r0, r0, #294912
	add	r0, r0, #1232
	bl	VP6DEC_VDMPostProc
.L1621:
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #294912
	str	r2, [r3, #1236]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1603:
	add	r0, r0, #294912
	mov	r2, #1
	add	r0, r0, #1232
	bl	MVC_DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1629
	add	r3, r3, #294912
	ldrb	r2, [r3, #1233]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1628
.L1614:
	mov	r2, #0
	str	r2, [r3, #1460]
	b	.L1589
.L1602:
	add	r0, r0, #294912
	add	r0, r0, #1232
	bl	VP8DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #294912
	str	r2, [r3, #1236]
	b	.L1589
.L1622:
	ldr	ip, .L1629+4
	movw	r3, #4036
	ldr	r2, .L1629+8
	ldr	r1, .L1629+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1589
.L1625:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #315392
	strb	r1, [r2, #3764]
	b	.L1611
.L1626:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #385024
	strb	r1, [r2, #194]
	b	.L1613
.L1628:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r2, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r2, #294912
	mov	r3, r2
	strb	r1, [r2, #1233]
	b	.L1614
.L1627:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r2, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r2, #294912
	mov	r3, r2
	strb	r1, [r2, #1232]
	b	.L1612
.L1624:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #307200
	strb	r2, [r3, #2504]
	b	.L1606
.L1623:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #294912
	strb	r2, [r3, #1241]
	b	.L1608
.L1630:
	.align	2
.L1629:
	.word	.LANCHOR1
	.word	.LC2
	.word	.LANCHOR0+1460
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_PostProc, .-VCTRL_PostProc
	.align	2
	.global	VCTRL_VdmPostProc
	.type	VCTRL_VdmPostProc, %function
VCTRL_VdmPostProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	mov	r7, r3
	mov	r4, r0
	mov	r5, r1
	mov	r6, r2
	ldrhi	ip, .L1641
	movhi	r3, #4224
	bhi	.L1639
	ldr	ip, .L1641+4
	ldr	ip, [ip, r0, asl #2]
	cmp	ip, #0
	beq	.L1640
	ldr	ip, [ip, #8]
	cmp	ip, #1
	beq	.L1635
	ldr	ip, .L1641+8
	movw	r3, #4226
.L1639:
	ldr	r2, .L1641+12
	mov	r0, #0
	ldr	r1, .L1641+16
	str	ip, [sp]
	bl	dprint_vfmw
.L1631:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1635:
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L1631
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_PostProc
.L1640:
	ldr	lr, .L1641+20
	mov	r0, ip
	movw	r3, #4225
	ldr	r2, .L1641+12
	ldr	r1, .L1641+16
	str	lr, [sp]
	bl	dprint_vfmw
	b	.L1631
.L1642:
	.align	2
.L1641:
	.word	.LC120
	.word	.LANCHOR1
	.word	.LC121
	.word	.LANCHOR0+1476
	.word	.LC0
	.word	.LC110
	UNWIND(.fnend)
	.size	VCTRL_VdmPostProc, .-VCTRL_VdmPostProc
	.align	2
	.global	VCTRL_SvdecLastFrame
	.type	VCTRL_SvdecLastFrame, %function
VCTRL_SvdecLastFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #31
	bhi	.L1647
	add	r1, r1, #2
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_ReportLastFrame
.L1647:
	ldr	ip, .L1648
	movw	r3, #7332
	ldr	r2, .L1648+4
	mov	r0, #0
	ldr	r1, .L1648+8
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1649:
	.align	2
.L1648:
	.word	.LC65
	.word	.LANCHOR0+1496
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_SvdecLastFrame, .-VCTRL_SvdecLastFrame
	.align	2
	.global	Get_YuvFormat
	.type	Get_YuvFormat, %function
Get_YuvFormat:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #6
	ldrls	pc, [pc, r1, asl #2]
	b	.L1651
.L1653:
	.word	.L1652
	.word	.L1654
	.word	.L1655
	.word	.L1656
	.word	.L1657
	.word	.L1658
	.word	.L1659
.L1659:
	cmp	r0, #1
	moveq	r0, #1
	movne	r0, #7
	ldmfd	sp, {fp, sp, pc}
.L1652:
	cmp	r0, #1
	moveq	r0, #0
	movne	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L1654:
	cmp	r0, #1
	moveq	r0, #2
	movne	r0, #8
	ldmfd	sp, {fp, sp, pc}
.L1655:
	cmp	r0, #1
	moveq	r0, #4
	movne	r0, #10
	ldmfd	sp, {fp, sp, pc}
.L1656:
	cmp	r0, #1
	moveq	r0, #3
	movne	r0, #9
	ldmfd	sp, {fp, sp, pc}
.L1657:
	cmp	r0, #1
	moveq	r0, #5
	movne	r0, #11
	ldmfd	sp, {fp, sp, pc}
.L1658:
	cmp	r0, #1
	moveq	r0, #13
	movne	r0, #12
	ldmfd	sp, {fp, sp, pc}
.L1651:
	mov	r3, r1
	movw	r2, #7816
	ldr	r1, .L1668
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #13
	ldmfd	sp, {fp, sp, pc}
.L1669:
	.align	2
.L1668:
	.word	.LC190
	UNWIND(.fnend)
	.size	Get_YuvFormat, .-Get_YuvFormat
	.align	2
	.global	VDH_PutUsrdecFrame
	.type	VDH_PutUsrdecFrame, %function
VDH_PutUsrdecFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r5, r1
	ldr	r1, [r1, #40]
	mov	r8, r0
	bl	FSP_GetLogicIdByPhyAddr
	cmn	r0, #1
	mov	r7, r0
	beq	.L1678
	ldr	r3, [r5, #4]
	cmp	r3, #1
	beq	.L1673
	mov	r1, r0
	mov	r2, #0
	mov	r0, r8
	bl	FSP_ClearLogicFs
	mov	r0, #0
.L1672:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1673:
	ldr	r0, [r5, #48]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L1679
.L1674:
	mov	r1, r7
	mov	r0, r8
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1680
	str	r7, [r4, #148]
	add	ip, r4, #576
	ldrd	r2, [r5, #64]
	add	r0, r4, #592
	add	r1, r4, #608
	mov	r6, #0
	mov	r9, #1
	strd	r2, [ip]
	ldrd	r2, [r5, #64]
	strd	r2, [r0, #-8]
	ldrd	r2, [r5, #64]
	strd	r2, [r0]
	ldrd	r2, [r5, #64]
	strd	r2, [r1, #-8]
	str	r9, [r4]
	str	r6, [r4, #4]
	str	r6, [r4, #8]
	str	r6, [r4, #12]
	ldr	r3, [r5, #40]
	str	r3, [r4, #20]
	mov	r0, r3
	str	r3, [r4, #36]
	ldr	r3, [r5, #48]
	str	r3, [r4, #24]
	str	r3, [r4, #40]
	bl	MEM_Phy2Vir
	str	r6, [r4, #508]
	str	r0, [r4, #504]
	ldr	r0, [r4, #24]
	bl	MEM_Phy2Vir
	str	r6, [r4, #516]
	ldr	lr, [r4, #20]
	mov	r1, r6
	ldr	r10, [r4, #24]
	mov	r2, #4
	ldr	ip, .L1682
	str	r0, [r4, #512]
	add	r0, r4, #64
	ldr	r3, [r5, #44]
	add	lr, r3, lr
	str	lr, [r4, #28]
	ldr	r3, [r5, #44]
	str	r6, [r4, #52]
	add	r3, r3, r10
	str	r3, [r4, #32]
	ldr	r3, [r5, #12]
	ldr	r10, [ip, #48]
	str	r3, [r4, #68]
	ldr	r3, [r5, #16]
	str	r3, [r4, #72]
	ldr	r3, [r5, #12]
	mov	ip, r3, lsr r9
	str	r3, [r4, #76]
	ldr	r3, [r5, #16]
	str	ip, [r4, #84]
	str	r3, [r4, #80]
	mov	r3, r3, lsr r9
	str	r3, [r4, #88]
	ldr	r3, [r5, #44]
	str	r6, [r4, #108]
	str	r6, [r4, #152]
	str	r3, [r4, #112]
	mov	r3, r3, lsr r9
	str	r9, [r4, #164]
	str	r3, [r4, #116]
	blx	r10
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	ldrb	r2, [r4, #64]	@ zero_extendqisi2
	and	r3, r3, #252
	orr	r3, r3, #12
	and	r2, r2, #224
	bfi	r3, r9, #4, #2
	bfi	r2, r9, #5, #3
	strb	r3, [r4, #65]
	strb	r2, [r4, #64]
	ldr	r0, [r5, #24]
	str	r0, [r4, #212]
	bl	MEM_Phy2Vir
	str	r6, [r4, #524]
	str	r0, [r4, #520]
	ldr	r1, [r5]
	ldr	r0, [r5, #8]
	bl	Get_YuvFormat
	cmp	r0, #13
	beq	.L1681
	str	r0, [r4, #388]
	mov	r2, r9
	ldr	r3, [r5, #56]
	mov	r9, #20
	mov	r1, r7
	mov	r0, r8
	str	r3, [r4, #364]
	ldr	r3, [r5, #60]
	str	r3, [r4, #360]
	ldr	r3, [r5, #52]
	str	r9, [r4, #296]
	str	r3, [r4, #368]
	bl	FSP_SetDisplay
	ldr	r2, .L1682+4
	str	r4, [sp]
	movw	r3, #34008
	mov	r1, r9
	movt	r3, 4
	ldr	ip, [r2, r8, asl #2]
	mov	r0, r8
	add	r2, ip, #294912
	add	r3, ip, r3
	add	r2, r2, #1232
	bl	InsertImgToVoQueue
	cmp	r0, #1
	moveq	r0, r6
	beq	.L1672
	add	r9, r4, #544
	ldr	r1, [r4, #544]
	mov	r0, r8
	add	r5, r4, #560
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	mov	r0, r8
	strd	r2, [r9]
	ldr	r1, [r4, #552]
	strd	r2, [fp, #-52]
	bl	FreeUsdByDec
	ldrd	r2, [fp, #-52]
	mov	r0, r8
	mov	r1, r7
	strd	r2, [r5, #-8]
	mov	r2, r6
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L1672
.L1679:
	ldr	r3, [r5, #4]
	cmp	r3, #1
	bne	.L1674
	ldr	r2, [r5, #48]
	ldr	r1, .L1682+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1672
.L1678:
	ldr	r2, [r5, #40]
	mov	r0, #0
	ldr	r1, .L1682+12
	bl	dprint_vfmw
	mov	r0, r7
	b	.L1672
.L1681:
	mov	r2, r0
	ldr	r1, .L1682+16
	mov	r0, r9
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1672
.L1680:
	movw	r2, #4519
	ldr	r1, .L1682+20
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1672
.L1683:
	.align	2
.L1682:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC192
	.word	.LC191
	.word	.LC194
	.word	.LC193
	UNWIND(.fnend)
	.size	VDH_PutUsrdecFrame, .-VDH_PutUsrdecFrame
	.align	2
	.global	VCTRL_PutUsrdecFrame
	.type	VCTRL_PutUsrdecFrame, %function
VCTRL_PutUsrdecFrame:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r5, .L1696
	mov	r4, r0
	mov	r3, r1
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	ldreq	ip, .L1696+4
	movweq	r3, #4659
	beq	.L1692
	cmp	r3, #0
	beq	.L1693
	ldr	r2, [r0, #568]
	cmp	r2, #20
	bne	.L1694
	ldr	r3, .L1696+8
	mov	r2, #72
	add	r0, r0, #496
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r1, [r5, r4, asl #2]
	mov	r0, r4
	add	r1, r1, #496
	bl	VDH_PutUsrdecFrame
	cmp	r0, #0
	bne	.L1695
.L1686:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1694:
	ldr	r1, .L1696+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1686
.L1695:
	ldr	r1, .L1696+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1686
.L1693:
	ldr	ip, .L1696+20
	mov	r0, r3
	movw	r3, #4660
.L1692:
	ldr	r2, .L1696+24
	ldr	r1, .L1696+28
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1686
.L1697:
	.align	2
.L1696:
	.word	.LANCHOR1
	.word	.LC2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC196
	.word	.LC197
	.word	.LC195
	.word	.LANCHOR0+1520
	.word	.LC0
	UNWIND(.fnend)
	.size	VCTRL_PutUsrdecFrame, .-VCTRL_PutUsrdecFrame
	.align	2
	.global	VCTRL_ResetHardware
	.type	VCTRL_ResetHardware, %function
VCTRL_ResetHardware:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	bl	SCDDRV_ResetSCD
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VDMDRV_ResetVDH
	UNWIND(.fnend)
	.size	VCTRL_ResetHardware, .-VCTRL_ResetHardware
	.align	2
	.global	VCTRL_CanBeDecodedByHardWare
	.type	VCTRL_CanBeDecodedByHardWare, %function
VCTRL_CanBeDecodedByHardWare:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #4
	cmpne	r0, #7
	beq	.L1700
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_CanBeDecodedByHardWare.part.25
.L1700:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_CanBeDecodedByHardWare, .-VCTRL_CanBeDecodedByHardWare
	.align	2
	.global	VCTRL_IsChanOpenAndRun
	.type	VCTRL_IsChanOpenAndRun, %function
VCTRL_IsChanOpenAndRun:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #4]
	cmp	r3, #1
	ldreq	r0, [r0, #8]
	subeq	r0, r0, #1
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VCTRL_IsChanOpenAndRun, .-VCTRL_IsChanOpenAndRun
	.align	2
	.global	VCTRL_OpenHardware
	.type	VCTRL_OpenHardware, %function
VCTRL_OpenHardware:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r6, r0
	movwhi	r2, #7865
	ldrhi	r1, .L1750
	bhi	.L1740
	ldr	r5, .L1750+4
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L1741
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L1707
	ldr	r0, [r0, #568]
	cmp	r0, #22
	beq	.L1707
	cmp	r0, #4
	cmpne	r0, #7
	moveq	r7, #1
	movne	r7, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r4, r7
.L1713:
	mov	r0, r4
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L1712
	ldr	r3, [r5, r4, asl #2]
	ldr	r0, [r3, #568]
	cmp	r0, #4
	cmpne	r0, #7
	beq	.L1712
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cmp	r0, #0
	addne	r7, r7, #1
.L1712:
	add	r4, r4, #1
	cmp	r4, #32
	bne	.L1713
	cmp	r7, #1
	beq	.L1742
.L1714:
	ldr	r3, .L1750+8
	mov	r1, #0
	add	r0, r3, #128
.L1721:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1720
	ldr	r2, [r2, #568]
	cmp	r2, #6
	moveq	r1, #1
.L1720:
	cmp	r3, r0
	bne	.L1721
	cmp	r1, #1
	beq	.L1743
.L1722:
	ldr	r3, [r5, r6, asl #2]
	ldr	r3, [r3, #568]
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, .L1750+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1744
	ldr	r3, .L1750+16
	ldr	r3, [r3, #28]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L1707:
	ldr	r1, .L1750+20
	movw	r2, #7877
.L1740:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1742:
	ldr	r4, .L1750+12
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1745
	mov	r0, r7
	mov	r1, #0
	bl	VDH_Need_Module
.L1717:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1718
	ldr	r3, .L1750+16
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L1746
	mov	r0, #0
	blx	r3
	b	.L1714
.L1743:
	ldr	r3, .L1750+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1747
	mov	r1, #0
	mov	r0, #3
	bl	VDH_Need_Module
	b	.L1722
.L1747:
	ldr	r3, .L1750+16
	ldr	r3, [r3, #12]
	cmp	r3, #0
	beq	.L1748
	mov	r0, #0
	blx	r3
	b	.L1722
.L1745:
	ldr	r3, .L1750+16
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1749
	mov	r0, #0
	blx	r3
	b	.L1717
.L1741:
	movw	r2, #7871
	ldr	r1, .L1750+24
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1744:
	mov	r1, #0
	mov	r0, #2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Need_Module
.L1718:
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Need_Module
	b	.L1714
.L1746:
	mov	r0, r3
	movw	r2, #7926
	ldr	r1, .L1750+28
	bl	dprint_vfmw
	b	.L1714
.L1748:
	mov	r0, r3
	movw	r2, #7957
	ldr	r1, .L1750+28
	bl	dprint_vfmw
	b	.L1722
.L1749:
	mov	r0, r3
	movw	r2, #7912
	ldr	r1, .L1750+28
	bl	dprint_vfmw
	b	.L1717
.L1751:
	.align	2
.L1750:
	.word	.LC198
	.word	.LANCHOR1
	.word	.LANCHOR1-4
	.word	g_HalDisable
	.word	g_vdm_hal_fun_ptr
	.word	.LC200
	.word	.LC199
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_OpenHardware, .-VCTRL_OpenHardware
	.align	2
	.global	VCTRL_StartChan
	.type	VCTRL_StartChan, %function
VCTRL_StartChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #31
	mov	r5, r0
	ldrhi	ip, .L1766
	movwhi	r3, #2308
	bhi	.L1763
	ldr	r4, .L1766+4
	ldr	r3, [r4, r0, asl #2]
	cmp	r3, #0
	beq	.L1764
	ldr	r6, [r3, #4]
	cmp	r6, #1
	bne	.L1765
	ldr	r3, [r3, #568]
	cmp	r3, #22
	ldreq	ip, .L1766+8
	movweq	r3, #2311
	beq	.L1763
	bl	SM_Start
	ldr	r3, [r4, r5, asl #2]
	mov	r2, #0
	add	r1, r3, #294912
	str	r6, [r1, #1220]
	str	r6, [r3, #8]
	ldr	r3, [r4, r5, asl #2]
	str	r6, [r3, #12]
	ldr	r3, [r4, r5, asl #2]
	str	r2, [r3, #24]
	ldr	r3, [r4, r5, asl #2]
	str	r6, [r3, #16]
	ldr	r2, [r4, r5, asl #2]
	ldr	r3, [r2, #20]
	cmp	r3, #0
	bne	.L1758
	ldr	r3, .L1766+12
	sub	r0, r4, #4
	ldr	r1, .L1766+16
	add	lr, r3, #128
	str	r6, [r2, #20]
.L1761:
	ldr	r2, [r0, #4]!
	add	r3, r3, #4
	add	r1, r1, #4
	cmp	r2, #0
	streq	r2, [r3, #-4]
	ldrne	ip, [r2, #20]
	strne	ip, [r3, #-4]
	ldrne	r2, [r2, #20]
	cmp	r3, lr
	str	r2, [r1, #-4]
	bne	.L1761
	ldr	r0, .L1766+12
	bl	VDMDRV_SetPriority
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
.L1758:
	ldr	r4, .L1766+20
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r5
	bl	VCTRL_OpenHardware
	mov	r2, #12
	ldr	r3, [r4, #48]
	mov	r1, #0
	ldr	r0, .L1766+24
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #720
	mov	r1, #0
	ldr	r0, .L1766+28
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #2
	mov	r1, #0
	ldr	r0, .L1766+32
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #120
	mov	r1, #0
	ldr	r0, .L1766+36
	blx	r3
	mov	r0, #0
.L1754:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1765:
	ldr	ip, .L1766+40
	movw	r3, #2310
.L1763:
	ldr	r2, .L1766+44
	mov	r0, #0
	ldr	r1, .L1766+48
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1754
.L1764:
	ldr	ip, .L1766+52
	mov	r0, r3
	ldr	r2, .L1766+44
	movw	r3, #2309
	ldr	r1, .L1766+48
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1754
.L1767:
	.align	2
.L1766:
	.word	.LC65
	.word	.LANCHOR1
	.word	.LC201
	.word	.LANCHOR3+640
	.word	g_ChanCtx
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_TimeRecId
	.word	g_TimeRecTable
	.word	g_DataRecId
	.word	g_DataTable
	.word	.LC123
	.word	.LANCHOR0+1544
	.word	.LC0
	.word	.LC80
	UNWIND(.fnend)
	.size	VCTRL_StartChan, .-VCTRL_StartChan
	.align	2
	.type	VfmwProc_TestStartChan, %function
VfmwProc_TestStartChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0]
	mov	r0, r4
	bl	VCTRL_StartChan
	mov	r2, r4
	ldr	r1, .L1769
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1770:
	.align	2
.L1769:
	.word	.LC202
	UNWIND(.fnend)
	.size	VfmwProc_TestStartChan, .-VfmwProc_TestStartChan
	.align	2
	.global	VCTRL_CloseHardware
	.type	VCTRL_CloseHardware, %function
VCTRL_CloseHardware:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r5, .L1833
	mov	r8, #0
	str	r0, [fp, #-48]
	mov	r7, r8
	add	r9, r5, #128
	mov	r1, r8
	b	.L1781
.L1823:
	ldr	r3, [r4, #4]
	cmp	r3, #1
	beq	.L1820
.L1777:
	cmp	r8, #0
	cmpeq	r6, #6
	bne	.L1772
	ldr	r3, [r4, #4]
	cmp	r3, #1
	beq	.L1821
.L1772:
	cmp	r5, r9
	beq	.L1822
.L1781:
	ldr	r4, [r5, #4]!
	cmp	r4, #0
	beq	.L1772
	cmp	r1, #0
	ldr	r6, [r4, #568]
	beq	.L1823
	cmp	r7, #0
	cmpeq	r6, #1
	bne	.L1777
	ldr	r3, [r4, #4]
	cmp	r3, #1
	bne	.L1772
	ldr	r10, [r4, #8]
.L1800:
	cmp	r10, #1
	moveq	r7, #1
	cmp	r8, #0
	cmpeq	r6, #6
	bne	.L1772
.L1801:
	cmp	r10, #1
	moveq	r8, #1
	cmp	r5, r9
	bne	.L1781
.L1822:
	cmp	r1, #0
	beq	.L1824
.L1782:
	cmp	r8, #0
	bne	.L1794
	ldr	r3, .L1833+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1825
	mov	r1, r8
	mov	r0, #3
	bl	VDH_UnNeed_Module
.L1794:
	cmp	r7, #0
	bne	.L1771
.L1830:
	ldr	r3, .L1833+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1826
	ldr	r3, .L1833+8
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L1771
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L1821:
	ldr	r10, [r4, #8]
	b	.L1801
.L1820:
	ldr	r10, [r4, #8]
	cmp	r10, #1
	beq	.L1827
.L1776:
	cmp	r7, #0
	cmpeq	r6, #1
	beq	.L1800
	b	.L1777
.L1827:
	cmp	r6, #7
	cmpne	r6, #4
	beq	.L1776
	mov	r0, r6
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	adds	r1, r0, #0
	movne	r1, #1
	b	.L1776
.L1824:
	ldr	r4, .L1833+4
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1787
	ldr	r5, [fp, #-48]
	str	r1, [fp, #-52]
	mov	r0, r5
	bl	SCDDRV_ResetSCD
	mov	r0, r5
	bl	VDMDRV_ResetVDH
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r1, [fp, #-52]
	cmp	r3, #1
	beq	.L1787
	mov	r0, #1
	bl	VDH_UnNeed_Module
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1790
.L1832:
	ldr	r3, .L1833+8
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L1828
	mov	r0, #0
	blx	r3
.L1793:
	mov	r0, #0
	bl	SCDDRV_SetStateIdle
	b	.L1782
.L1825:
	ldr	r3, .L1833+8
	mov	r0, r8
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L1829
	blx	r3
	cmp	r7, #0
	beq	.L1830
.L1771:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1826:
	mov	r1, r7
	mov	r0, #2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDH_UnNeed_Module
.L1787:
	ldr	r3, .L1833+8
	ldr	r3, [r3, #8]
	cmp	r3, #0
	beq	.L1831
	mov	r0, #0
	blx	r3
.L1789:
	mov	r0, #0
	bl	VDMDRV_SetStateIdle
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1832
.L1790:
	mov	r1, #0
	mov	r0, r1
	bl	VDH_UnNeed_Module
	b	.L1782
.L1828:
	mov	r0, r3
	movw	r2, #8051
	ldr	r1, .L1833+12
	bl	dprint_vfmw
	b	.L1793
.L1829:
	movw	r2, #8069
	ldr	r1, .L1833+12
	bl	dprint_vfmw
	b	.L1794
.L1831:
	mov	r0, r3
	movw	r2, #8036
	ldr	r1, .L1833+12
	bl	dprint_vfmw
	b	.L1789
.L1834:
	.align	2
.L1833:
	.word	.LANCHOR1-4
	.word	g_HalDisable
	.word	g_vdm_hal_fun_ptr
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_CloseHardware, .-VCTRL_CloseHardware
	.align	2
	.global	VCTRL_StopChan
	.type	VCTRL_StopChan, %function
VCTRL_StopChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #31
	mov	r4, r0
	bhi	.L1841
	ldr	r6, .L1843
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1842
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L1840
	str	r2, [r3, #24]
	mov	r3, #0
	ldr	r2, [r6, r0, asl #2]
	str	r3, [r2, #12]
	ldr	r2, [r6, r0, asl #2]
	str	r3, [r2, #8]
	bl	SM_Stop
	subs	r5, r0, #0
	bne	.L1840
	mov	r1, r5
	mov	r0, r4
	bl	DeleteRawPacketInBuffer
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r4
	str	r5, [r3, #24]
	bl	VCTRL_CloseHardware
	mov	r0, r5
.L1837:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1840:
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1841:
	ldr	ip, .L1843+4
	movw	r3, #2395
	ldr	r2, .L1843+8
	mov	r0, #0
	ldr	r1, .L1843+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1837
.L1842:
	ldr	ip, .L1843+16
	mov	r0, r3
	ldr	r2, .L1843+8
	movw	r3, #2396
	ldr	r1, .L1843+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1837
.L1844:
	.align	2
.L1843:
	.word	.LANCHOR1
	.word	.LC65
	.word	.LANCHOR0+1560
	.word	.LC0
	.word	.LC203
	UNWIND(.fnend)
	.size	VCTRL_StopChan, .-VCTRL_StopChan
	.align	2
	.global	VCTRL_StopChanWithCheck
	.type	VCTRL_StopChanWithCheck, %function
VCTRL_StopChanWithCheck:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L1852
	mov	r7, r0
	mov	r4, #0
	mov	r8, r5
	b	.L1847
.L1851:
	add	r4, r4, #1
	ldr	r3, [r8, #120]
	blx	r3
	cmp	r4, #50
	beq	.L1849
.L1847:
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	mov	r0, r7
	bl	VCTRL_StopChan
	ldr	r3, [r5, #16]
	mov	r6, r0
	mov	r0, #0
	blx	r3
	cmp	r6, #0
	mov	r0, #10
	bne	.L1851
	cmp	r4, #49
	bgt	.L1849
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1849:
	ldr	r1, .L1852+4
	mvn	r6, #0
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1853:
	.align	2
.L1852:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC204
	UNWIND(.fnend)
	.size	VCTRL_StopChanWithCheck, .-VCTRL_StopChanWithCheck
	.align	2
	.global	VCTRL_ResetChanWithOption
	.type	VCTRL_ResetChanWithOption, %function
VCTRL_ResetChanWithOption:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	cmp	r0, #31
	mov	r4, r0
	mov	r8, r1
	bhi	.L1880
	ldr	r6, .L1886
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1881
	ldr	r2, [r1]
	cmp	r2, #1
	bhi	.L1882
	ldr	r9, .L1886+4
	mov	r5, #0
	ldr	r7, [r3, #8]
	bl	VCTRL_StopChan
	ldr	r2, [r6, r4, asl #2]
	mov	r3, r4, asl #5
	ldr	r0, .L1886+8
	sub	r3, r3, r4, asl #3
	mov	r1, r5
	ldr	r10, [r9, #48]
	add	r0, r0, r3
	str	r5, [r2, #412]
	str	r5, [r2, #416]
	mov	r2, #24
	blx	r10
	mov	r1, r5
	mov	r0, r4
	bl	VCTRL_SetSendStreamAgainFlag
	ldr	r3, [r9, #12]
	mov	r0, #4
	blx	r3
	mov	r0, r4
	bl	VCTRL_FindOccupiedFrame
	ldr	r3, [r9, #16]
	mov	r0, #4
	blx	r3
	ldr	r2, [r8, #4]
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r4
	str	r2, [r3, #1200]
	bl	InitSyntaxCtx
	ldr	r3, [r6, r4, asl #2]
	add	r1, r3, #294912
	ldr	r0, [r3, #568]
	add	r1, r1, #1232
	bl	ReleaseCurPic
	ldr	r0, [r6, r4, asl #2]
	ldr	r3, [r9, #48]
	mov	r1, r5
	mov	r2, #416
	add	r0, r0, #720
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mvn	r0, #0
	mvn	r1, #0
	add	r2, r3, #656
	add	ip, r3, #640
	strd	r0, [ip]
	strd	r0, [r2, #-8]
	mov	r0, r4
	ldr	r2, [r3, #1448]
	str	r5, [r3, #1136]
	cmp	r2, #1
	str	r5, [r3, #1532]
	addeq	r2, r3, #294912
	streq	r5, [r3, #1496]
	streq	r5, [r2, #1156]
	ldr	r3, [r3, #568]
	cmp	r3, #20
	beq	.L1860
	ldr	r3, [r8, #8]
	cmp	r3, #0
	beq	.L1883
.L1860:
	bl	FSP_EmptyInstance
.L1861:
	mov	r0, r4
	bl	InitUsdPool
	ldr	r3, [r8]
	cmp	r3, #0
	beq	.L1884
.L1862:
	ldr	r2, [r6, #1056]
	ldr	r3, .L1886
	cmp	r2, #0
	beq	.L1863
	add	r5, r3, r4, lsl #2
	str	r4, [fp, #-48]
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1865
	mov	r0, #512
	sub	r1, fp, #48
	bl	VCTRL_SetDbgOption
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1865
	sub	r1, fp, #48
	mov	r0, #512
	bl	VCTRL_SetDbgOption
.L1865:
	ldr	r1, .L1886+12
	mov	r0, #32
	bl	dprint_vfmw
.L1863:
	cmp	r7, #0
	bne	.L1885
.L1867:
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, #0
.L1856:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1884:
	mov	r0, r4
	bl	SM_Reset
	b	.L1862
.L1885:
	mov	r0, r4
	bl	VCTRL_StartChan
	b	.L1867
.L1883:
	bl	FSP_ResetInstance
	b	.L1861
.L1882:
	movw	r2, #2972
	ldr	r1, .L1886+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1856
.L1880:
	ldr	ip, .L1886+20
	movw	r3, #2967
	ldr	r2, .L1886+24
	mov	r0, #0
	ldr	r1, .L1886+28
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1856
.L1881:
	ldr	ip, .L1886+32
	mov	r0, r3
	ldr	r2, .L1886+24
	movw	r3, #2968
	ldr	r1, .L1886+28
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1856
.L1887:
	.align	2
.L1886:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3-128
	.word	.LC206
	.word	.LC205
	.word	.LC99
	.word	.LANCHOR0+1576
	.word	.LC0
	.word	.LC100
	UNWIND(.fnend)
	.size	VCTRL_ResetChanWithOption, .-VCTRL_ResetChanWithOption
	.align	2
	.global	VCTRL_ResetChan
	.type	VCTRL_ResetChan, %function
VCTRL_ResetChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	cmp	r0, #31
	mov	r4, r0
	bhi	.L1910
	ldr	r6, .L1914
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1911
	ldr	r8, [r3, #8]
	bl	VCTRL_StopChan
	ldr	r7, .L1914+4
	mov	r5, #0
	ldr	r3, [r6, r4, asl #2]
	mov	r0, #4
	ldr	r2, [r7, #12]
	str	r5, [r3, #412]
	str	r5, [r3, #416]
	blx	r2
	ldr	r3, [r6, r4, asl #2]
	ldr	r2, [r3, #1448]
	cmp	r2, #1
	beq	.L1912
.L1892:
	mov	r3, r4, asl #5
	ldr	r0, .L1914+8
	sub	r3, r3, r4, asl #3
	mov	r1, #0
	mov	r5, r1
	mov	r2, #24
	add	r0, r0, r3
	ldr	r9, [r7, #48]
	blx	r9
	mov	r1, r5
	mov	r0, r4
	bl	VCTRL_SetSendStreamAgainFlag
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r4
	str	r5, [r3, #1200]
	bl	InitSyntaxCtx
	ldr	r0, [r6, r4, asl #2]
	mov	r1, r5
	ldr	r3, [r7, #48]
	mov	r2, #416
	add	r0, r0, #720
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mvn	r0, #0
	mvn	r1, #0
	add	r2, r3, #294912
	add	lr, r3, #640
	add	ip, r3, #656
	strd	r0, [lr]
	strd	r0, [ip, #-8]
	mov	r0, r4
	str	r5, [r3, #1136]
	str	r5, [r2, #1184]
	str	r5, [r2, #1176]
	str	r5, [r2, #1180]
	ldr	r1, [r3, #1448]
	str	r5, [r3, #1532]
	cmp	r1, #1
	streq	r5, [r3, #1496]
	streq	r5, [r2, #1156]
	ldr	r3, [r3, #568]
	cmp	r3, #20
	beq	.L1894
	bl	FSP_ResetInstance
.L1895:
	ldr	r3, [r7, #16]
	mov	r0, #4
	blx	r3
	mov	r0, r4
	bl	InitUsdPool
	mov	r0, r4
	bl	SM_Reset
	ldr	r2, [r6, #1056]
	ldr	r3, .L1914
	cmp	r2, #0
	beq	.L1896
	add	r5, r3, r4, lsl #2
	str	r4, [fp, #-40]
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1898
	mov	r0, #512
	sub	r1, fp, #40
	bl	VCTRL_SetDbgOption
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1898
	sub	r1, fp, #40
	mov	r0, #512
	bl	VCTRL_SetDbgOption
.L1898:
	ldr	r1, .L1914+12
	mov	r0, #32
	bl	dprint_vfmw
.L1896:
	cmp	r8, #0
	bne	.L1913
.L1900:
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, #0
.L1890:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1913:
	mov	r0, r4
	bl	VCTRL_StartChan
	b	.L1900
.L1894:
	bl	FSP_EmptyInstance
	b	.L1895
.L1912:
	add	r2, r3, #294912
	ldr	r1, [r3, #568]
	ldr	r2, [r2, #1224]
	cmp	r2, r1
	bne	.L1892
	str	r5, [r3, #12]
	mov	r0, r4
	bl	VCTRL_FindOccupiedFrame
	b	.L1892
.L1910:
	ldr	ip, .L1914+16
	movw	r3, #3310
	ldr	r2, .L1914+20
	mov	r0, #0
	ldr	r1, .L1914+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1890
.L1911:
	ldr	ip, .L1914+28
	mov	r0, r3
	ldr	r2, .L1914+20
	movw	r3, #3311
	ldr	r1, .L1914+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1890
.L1915:
	.align	2
.L1914:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3-128
	.word	.LC206
	.word	.LC99
	.word	.LANCHOR0+1604
	.word	.LC0
	.word	.LC100
	UNWIND(.fnend)
	.size	VCTRL_ResetChan, .-VCTRL_ResetChan
	.align	2
	.global	VCTRL_CreateChan
	.type	VCTRL_CreateChan, %function
VCTRL_CreateChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 224
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #236)
	sub	sp, sp, #236
	ldr	r6, .L2027
	mov	r4, #0
	mov	r7, r1
	mov	r10, r0
	mov	r1, r4
	ldr	r3, [r6, #48]
	mov	r5, r2
	sub	r0, fp, #204
	mov	r2, #40
	str	r4, [fp, #-260]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #120
	sub	r0, fp, #164
	blx	r3
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #16
	sub	r0, fp, #244
	blx	r3
	mov	r1, r4
	ldr	r3, [r6, #48]
	sub	r0, fp, #256
	mov	r2, #12
	blx	r3
	cmp	r7, r4
	beq	.L2012
	ldr	r2, [r7, #36]
	cmp	r2, #0
	blt	.L1919
	ldr	r2, [r7, #12]
	cmp	r2, #31
	ble	.L1919
	ldr	r3, [r7, #16]
	cmp	r3, #31
	ble	.L1919
	ldr	r3, [r7, #56]
	cmp	r3, #262144
	blt	.L1919
	ldr	r2, [r7, #44]
	cmp	r2, #1
	beq	.L2013
	cmp	r2, #2
	bne	.L1921
	ldr	r3, [r7, #20]
	cmp	r3, #0
	ble	.L1919
	ldr	r3, [r7, #24]
	cmp	r3, #0
	ble	.L1919
.L2007:
	ldr	r3, [r7, #28]
	cmp	r3, #0
	ble	.L1919
	ldr	r3, [r7, #32]
	cmp	r3, #0
	bgt	.L1921
.L1919:
	ldr	r1, .L2027+4
	mov	r0, #0
	bl	dprint_vfmw
.L2009:
	mvn	r0, #0
.L2002:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1921:
	ldr	r3, [r7, #192]
	movw	ip, #14496
	mov	r4, #1
	movt	ip, 12
	cmp	r3, #1
	sub	r2, fp, #256
	movw	r8, #62768
	mov	r1, r7
	movhi	r3, #0
	strhi	r3, [r7, #192]
	cmp	r10, #26
	mov	r3, r5
	str	r4, [r7, #216]
	mov	r0, r10
	str	r4, [r7, #220]
	movt	r8, 177
	movne	r8, ip
	bl	VCTRL_GetChanMemSize
	cmp	r0, #0
	bne	.L2014
	ldr	r5, .L2027+8
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L1974
	mov	r3, r5
.L1927:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1926
	add	r4, r4, #1
	cmp	r4, #32
	bne	.L1927
	ldr	r3, [r7, #228]
	cmp	r3, #1
	beq	.L1971
.L1972:
	mov	r2, #32
	ldr	r1, .L2027+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2002
.L2013:
	ldr	r3, [r7, #20]
	cmp	r3, #0
	bgt	.L2007
	b	.L1919
.L2014:
	movw	r2, #1947
	ldr	r1, .L2027+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2002
.L2012:
	mov	r0, r7
	ldr	r1, .L2027+20
	bl	dprint_vfmw
	b	.L2009
.L1974:
	mov	r4, r3
.L1926:
	ldr	r3, [r7, #228]
	cmp	r3, #1
	beq	.L1971
.L1929:
	cmp	r4, #31
	bhi	.L1972
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #228
	blx	r3
	ldrd	r2, [r7, #128]
	ldr	r9, .L2027
	orrs	r3, r2, r3
	beq	.L1931
	ldr	r3, [r7, #136]
	cmp	r3, #0
	bne	.L1932
.L1931:
	mov	r0, #7
	mov	r3, #3
	mov	r9, #1
	str	r3, [fp, #-208]
	bl	VFMW_GetString
	sub	r3, fp, #228
	ldr	r2, [fp, #-248]
	mov	r1, #0
	str	r9, [sp]
	bl	MEM_AllocMemBlock
	subs	r3, r0, #0
	bne	.L2015
	ldr	r2, [fp, #-212]
	ldr	r1, [fp, #-224]
	ldr	r0, [fp, #-220]
	str	r3, [fp, #-264]
	bl	MEM_AddMemRecord
	ldr	r0, [fp, #-220]
	ldr	r1, [fp, #-224]
	ldr	r2, [fp, #-212]
	ldr	r3, [fp, #-264]
	str	r9, [fp, #-236]
	str	r0, [fp, #-116]
	str	r3, [fp, #-104]
	str	r1, [fp, #-108]
	str	r2, [fp, #-100]
.L1935:
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #228
	blx	r3
	ldrd	r2, [r7, #80]
	ldr	r1, .L2027
	orrs	r3, r2, r3
	beq	.L1966
	ldr	r3, [r7, #88]
	cmp	r3, #0
	bne	.L1937
.L1966:
	ldr	r3, [r7, #192]
	cmp	r3, #1
	beq	.L1938
	mov	r0, #8
	mov	r3, #3
	str	r3, [fp, #-208]
	bl	VFMW_GetString
	mov	r3, #0
	ldr	r2, [fp, #-256]
	mov	r1, r3
	str	r3, [sp]
	sub	r3, fp, #228
	bl	MEM_AllocMemBlock
	subs	r9, r0, #0
	bne	.L2016
	ldr	r2, [fp, #-212]
	ldr	r1, [fp, #-224]
	ldr	r0, [fp, #-220]
	bl	MEM_AddMemRecord
	ldr	r0, [fp, #-220]
	ldr	r1, [fp, #-224]
	mov	r3, #1
	ldr	r2, [fp, #-212]
	str	r9, [fp, #-152]
	str	r0, [fp, #-164]
	str	r1, [fp, #-156]
	str	r2, [fp, #-148]
	str	r3, [fp, #-244]
.L1942:
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #228
	blx	r3
	ldrd	r2, [r7, #104]
	ldr	r1, .L2027
	orrs	r3, r2, r3
	beq	.L1968
	ldr	r3, [r7, #112]
	cmp	r3, #0
	bne	.L1946
.L1968:
	mov	r0, #9
	mov	r3, #3
	str	r3, [fp, #-208]
	bl	VFMW_GetString
	mov	r3, #0
	ldr	r2, [fp, #-252]
	mov	r1, r3
	str	r3, [sp]
	sub	r3, fp, #228
	bl	MEM_AllocMemBlock
	subs	r9, r0, #0
	bne	.L2017
	ldr	r2, [fp, #-212]
	ldr	r1, [fp, #-224]
	ldr	r0, [fp, #-220]
	bl	MEM_AddMemRecord
	ldr	r0, [fp, #-220]
	ldr	r1, [fp, #-224]
	mov	r3, #1
	ldr	r2, [fp, #-212]
	str	r9, [fp, #-128]
	str	r0, [fp, #-140]
	str	r1, [fp, #-132]
	str	r2, [fp, #-124]
	str	r3, [fp, #-240]
.L1951:
	ldr	r3, [r6, #48]
	mov	r1, #0
	mov	r2, #24
	sub	r0, fp, #228
	blx	r3
	ldr	r3, [r7, #168]
	ldr	r1, .L2027
	cmp	r3, #0
	beq	.L1956
	ldr	r2, [r7, #184]
	cmp	r2, #0
	beq	.L1956
	ldr	r0, [r7, #224]
	str	r3, [fp, #-220]
	cmp	r0, #1
	str	r2, [fp, #-212]
	subeq	r0, fp, #228
	subne	r0, fp, #228
	ldreq	r3, [r1, #160]
	moveq	r2, #3
	ldrne	r3, [r1, #176]
	movne	r2, #0
	str	r2, [fp, #-208]
	blx	r3
	ldr	r2, [fp, #-212]
	mov	r1, r0
	str	r0, [fp, #-224]
	ldr	r0, [fp, #-220]
	bl	MEM_AddMemRecord
	ldr	r0, [fp, #-212]
	ldr	r1, [fp, #-220]
	mov	r3, #0
	ldr	r2, [fp, #-224]
	str	r0, [fp, #-52]
	str	r1, [fp, #-68]
	str	r2, [fp, #-60]
	str	r3, [fp, #-56]
.L1956:
	ldr	r3, [r6, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [fp, #-108]
	sub	r2, r8, #205824
	ldr	r3, [r6, #48]
	sub	r2, r2, #520
	mov	r1, #0
	str	r0, [r5, r4, asl #2]
	mov	r9, #0
	blx	r3
	ldr	r0, [r5, r4, asl #2]
	ldr	r3, [r6, #52]
	mov	r2, #232
	add	r0, r0, #1248
	mov	r1, r7
	add	r0, r0, #8
	blx	r3
	ldr	r0, [r5, r4, asl #2]
	mov	r2, #22
	ldr	r1, .L2027+24
	mov	ip, #30
	str	r10, [r0, #36]
	ldr	r3, [r5, r4, asl #2]
	str	r8, [r0, #1164]
	mov	r0, r4
	str	r4, [r3]
	str	r10, [r3, #604]
	str	r9, [r3, #1192]
	ldr	r3, [r5, r4, asl #2]
	ldr	lr, [r7]
	str	lr, [r3, #32]
	ldr	r3, [r5, r4, asl #2]
	add	lr, r3, #294912
	str	r2, [r3, #568]
	str	r2, [lr, #1224]
	str	r9, [r3, #28]
	ldr	r3, [r5, r4, asl #2]
	ldr	r10, [r7, #224]
	add	lr, r3, #294912
	add	r2, r3, #1536
	add	r2, r2, #8
	str	r2, [r1, r4, asl #3]
	str	r10, [lr, #1200]
	add	r1, r3, #262144
	str	ip, [r3, #1536]
	add	r1, r1, #1984
	ldr	r2, [r7, #216]
	ldr	r10, .L2027+8
	str	r2, [r3, #1616]
	ldr	r2, [r7, #220]
	str	r2, [r3, #1620]
	bl	FSP_EnableInstance
	subs	r2, r0, #0
	bne	.L2018
	mov	r0, r4
	mov	r9, r2
	str	r2, [fp, #-264]
	bl	VCTRL_ResetChan
	ldr	r3, [r10, r4, asl #2]
	ldr	r2, [fp, #-264]
	ldr	lr, [fp, #-244]
	add	r1, r3, #290816
	ldr	ip, [fp, #-240]
	ldr	r0, [fp, #-236]
	str	lr, [r3, #332]
	str	ip, [r3, #336]
	str	r0, [r3, #340]
	add	r3, r3, #294912
	str	r2, [r1, #1108]
	str	r2, [r1, #1112]
	str	r2, [r1, #1120]
	str	r2, [r1, #1124]
	str	r2, [r1, #1116]
	str	r2, [r1, #1128]
	ldr	r1, [r7, #192]
	str	r2, [r3, #1156]
	str	r1, [r3, #1164]
	ldr	r1, [r7, #228]
	str	r2, [r3, #1220]
	str	r1, [r3, #1216]
.L1961:
	mov	r7, r9, asl #6
	ldr	r0, [r5, r4, asl #2]
	add	r7, r7, r9, lsl #3
	ldr	r10, [r6, #48]
	add	r3, r7, #290816
	mov	r2, #72
	add	r3, r3, #1136
	mov	r1, #0
	add	r0, r0, r3
	add	r9, r9, #1
	blx	r10
	ldr	r0, [r5, r4, asl #2]
	movw	r3, #29816
	cmp	r9, #32
	add	r7, r0, r7
	movt	r3, 4
	add	r1, r7, #290816
	add	r3, r7, r3
	mov	r2, #255
	ldr	r7, .L2027+8
	str	r2, [r1, #1136]
	str	r2, [r1, #1140]
	ldr	r10, .L2027
	str	r2, [r3]
	bne	.L1961
	add	r0, r0, #290816
	ldr	r3, [r10, #48]
	mov	r2, #1248
	mov	r1, #0
	add	r0, r0, #3440
	blx	r3
	ldr	r0, [r7, r4, asl #2]
	ldr	r3, [r10, #48]
	mov	r2, #24
	add	r0, r0, #294912
	mov	r1, #0
	add	r0, r0, #592
	blx	r3
	ldr	r3, [r7, r4, asl #2]
	ldr	r10, [fp, #-156]
	mov	r7, #0
	ldr	r9, [fp, #-132]
	add	ip, r3, #262144
	ldr	r2, [fp, #-116]
	ldr	r1, [fp, #-108]
	ldr	lr, [fp, #-100]
	ldr	r0, [fp, #-68]
	str	r10, [r3, #240]
	str	r9, [r3, #264]
	str	r2, [r3, #292]
	ldr	r9, [fp, #-52]
	ldr	r2, [fp, #-164]
	str	r1, [r3, #288]
	str	lr, [r3, #300]
	ldr	r1, [fp, #-148]
	str	r0, [r3, #316]
	ldr	r10, [fp, #-60]
	ldr	lr, [fp, #-140]
	ldr	r0, [fp, #-124]
	str	r9, [r3, #324]
	str	r10, [r3, #312]
	str	r2, [r3, #244]
	str	r2, [r3, #360]
	str	r1, [r3, #252]
	str	r1, [r3, #364]
	str	lr, [r3, #268]
	str	r0, [r3, #276]
	str	r7, [ip, #2016]
	ldr	ip, .L2027+28
	ldr	r9, [r3, #1448]
	add	ip, ip, r4, lsl #2
	cmp	r9, #1
	str	r7, [ip, #768]
	beq	.L1962
	sub	r1, r1, #307200
	str	r2, [r3, #348]
	sub	r1, r1, #2576
	str	r1, [r3, #352]
	add	r2, r1, r2
	str	lr, [r3, #356]
	add	r1, r2, #47616
	add	ip, r2, #14848
	add	r1, r1, #15
	add	r2, r2, #15
	bic	r1, r1, #15
	add	ip, ip, #15
	bic	ip, ip, #15
	str	r0, [r3, #368]
	str	ip, [r3, #380]
.L2008:
	str	r1, [r3, #388]
	bic	r2, r2, #15
	mov	r1, #32768
	str	r2, [r3, #372]
	str	r1, [r3, #384]
	mov	r0, #14848
	mov	r2, #262144
	str	r0, [r3, #376]
	str	r2, [r3, #392]
	mov	r0, r4
	ldr	r3, [r5, r4, asl #2]
	sub	r8, r8, #203776
	sub	r8, r8, #520
	str	r4, [r3]
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #262144
	str	r4, [r3, #228]
	str	r4, [r3, #232]
	str	r4, [r2, #1756]
	bl	SM_ClearInst
	ldr	r3, [r5, r4, asl #2]
	mov	r0, r4
	ldr	r1, [r3, #288]
	add	r1, r1, r8
	bl	OpenUsdPool_WithMem
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #1
	mov	r0, r4
	str	r2, [r3, #4]
	bl	VDMDRV_ClearChanIsDec
	bl	VDMDRV_ParamInit
	ldr	r3, [r6]
	ldr	r5, [r5, r4, asl #2]
	blx	r3
	ldr	r3, [r6, #16]
	add	r5, r5, #294912
	str	r0, [r5, #1172]
	mov	r0, #0
	blx	r3
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1938:
	mov	r3, #0
	mov	r0, #0
	mov	r1, #0
	str	r3, [fp, #-164]
	str	r3, [fp, #-148]
	str	r3, [fp, #-244]
	strd	r0, [fp, #-156]
	b	.L1942
.L1962:
	sub	r0, r0, #307200
	str	r7, [r3, #348]
	sub	r0, r0, #2576
	str	r0, [r3, #368]
	add	r2, r0, lr
	str	r7, [r3, #352]
	add	r0, r2, #14848
	add	r1, r2, #47616
	add	r0, r0, #15
	add	r1, r1, #15
	bic	r0, r0, #15
	add	r2, r2, #15
	str	lr, [r3, #356]
	bic	r1, r1, #15
	str	r0, [r3, #380]
	b	.L2008
.L1932:
	ldr	r3, [r9, #52]
	mov	r2, #24
	add	r1, r7, #120
	sub	r0, fp, #116
	blx	r3
	ldr	r2, [fp, #-100]
	ldr	r3, [fp, #-248]
	cmp	r2, r3
	blt	.L2019
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_AddMemRecord
	b	.L1935
.L1946:
	ldr	r3, [r1, #52]
	mov	r2, #24
	add	r1, r7, #96
	sub	r0, fp, #140
	blx	r3
	ldrd	r0, [fp, #-132]
	orrs	r3, r0, r1
	beq	.L1952
	ldr	r2, [fp, #-124]
	ldr	r3, [fp, #-252]
	cmp	r2, r3
	blt	.L1952
	mov	r1, r0
	ldr	r0, [fp, #-140]
	bl	MEM_AddMemRecord
	b	.L1951
.L1971:
	sub	r1, fp, #260
	mov	r0, #1
	bl	PDT_GetAttribute
	ldr	r3, [fp, #-260]
	cmp	r3, #1
	cmpne	r4, #15
	ble	.L1929
	mov	r2, r4
	ldr	r1, .L2027+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2002
.L1937:
	ldr	r3, [r1, #52]
	mov	r2, #24
	sub	r0, fp, #164
	add	r1, r7, #72
	blx	r3
	ldr	r3, [r7, #192]
	ldr	r2, [fp, #-148]
	cmp	r3, #1
	beq	.L1944
	ldr	r3, [fp, #-256]
	cmp	r2, r3
	blt	.L2020
.L1944:
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_AddMemRecord
	b	.L1942
.L2017:
	ldr	r3, [fp, #-236]
	cmp	r3, #1
	beq	.L2021
.L1948:
	ldr	r3, [fp, #-244]
	cmp	r3, #1
	beq	.L2022
.L1949:
	movw	r2, #1679
	ldr	r1, .L2027+36
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2009
.L2016:
	ldr	r3, [fp, #-236]
	cmp	r3, #1
	beq	.L2023
.L1940:
	movw	r2, #1743
	ldr	r1, .L2027+40
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2009
.L2018:
	mov	r2, r4
	ldr	r1, .L2027+44
	mov	r0, #1
	sub	r5, fp, #44
	bl	dprint_vfmw
	mov	r0, r4
	bl	FSP_DisableInstance
	mov	r0, r4
	bl	CloseUsdPool_WithMem
	ldr	r3, [r10, r4, asl #2]
	mov	r0, r4
	str	r9, [r10, r4, asl #2]
	add	r2, r3, #290816
	add	r1, r3, #294912
	add	r2, r2, #1136
	str	r2, [fp, #-192]
	add	r2, r3, #236
	str	r2, [fp, #-204]
	ldr	r2, [r3, #340]
	ldr	ip, [r1, #1164]
	ldr	r6, [r1, #1200]
	add	r1, r3, #260
	str	r2, [fp, #-172]
	add	r2, r3, #284
	str	r1, [fp, #-200]
	add	r3, r3, #308
	ldr	r1, [r3, #24]
	str	r2, [fp, #-196]
	ldr	r2, [r3, #28]
	str	ip, [fp, #-184]
	str	r1, [fp, #-180]
	str	r3, [r5, #-144]!
	str	r2, [fp, #-176]
	bl	VDMDRV_ClearChanIsDec
	ldr	r3, .L2027
	mov	r0, r9
	ldr	r3, [r3, #16]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_DelRecordEsBuf.isra.5
	sub	r1, fp, #204
	mov	r0, r4
	bl	VCTRL_FreeChanResource
	b	.L2009
.L2015:
	mov	r0, r9
	movw	r2, #1800
	ldr	r1, .L2027+48
	bl	dprint_vfmw
	b	.L2009
.L1952:
	ldr	r3, [fp, #-236]
	cmp	r3, #1
	beq	.L2024
.L1954:
	ldr	r3, [fp, #-244]
	cmp	r3, #1
	beq	.L2025
.L1955:
	movw	r2, #1707
	ldr	r1, .L2027+52
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2009
.L2022:
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-148]
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_DelMemRecord
	b	.L1949
.L2021:
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_DelMemRecord
	b	.L1948
.L2019:
	movw	r2, #1816
	ldr	r1, .L2027+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2009
.L2023:
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_DelMemRecord
	b	.L1940
.L2020:
	ldr	r1, [fp, #-236]
	cmp	r1, #1
	beq	.L2026
.L1945:
	str	r3, [sp]
	mov	r0, #1
	mov	r3, r2
	ldr	r1, .L2027+60
	movw	r2, #1774
	bl	dprint_vfmw
	b	.L2009
.L2025:
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-148]
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_DelMemRecord
	b	.L1955
.L2024:
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_DelMemRecord
	b	.L1954
.L2026:
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_DelMemRecord
	ldr	r2, [fp, #-148]
	ldr	r3, [fp, #-256]
	b	.L1945
.L2028:
	.align	2
.L2027:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC134
	.word	.LANCHOR1
	.word	.LC210
	.word	.LC208
	.word	.LC207
	.word	s_SmIIS
	.word	.LANCHOR3
	.word	.LC209
	.word	.LC215
	.word	.LC213
	.word	.LC217
	.word	.LC211
	.word	.LC216
	.word	.LC212
	.word	.LC214
	UNWIND(.fnend)
	.size	VCTRL_CreateChan, .-VCTRL_CreateChan
	.align	2
	.global	VCTRL_ConfigChan
	.type	VCTRL_ConfigChan, %function
VCTRL_ConfigChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #92)
	sub	sp, sp, #92
	subs	r8, r1, #0
	mov	r4, r0
	ldreq	ip, .L2080
	moveq	r0, r8
	movweq	r3, #2613
	beq	.L2070
	cmp	r4, #31
	ldrhi	ip, .L2080+4
	movwhi	r3, #2614
	bhi	.L2071
	ldr	r7, .L2080+8
	ldr	r3, [r7, r4, asl #2]
	cmp	r3, #0
	beq	.L2072
	ldr	r3, [r3, #4]
	cmp	r3, #1
	bne	.L2073
	bl	VCTRL_CheckChanWH
	subs	r5, r0, #0
	bne	.L2074
	ldr	r6, .L2080+12
	add	r1, r6, #896
	bl	PDT_GetAttribute
	ldr	r3, [r6, #916]
	ldr	r2, [r8, #8]
	cmp	r3, #21
	bhi	.L2037
	cmp	r3, r2
	beq	.L2038
	add	r3, r6, #916
	add	r0, r6, #1040
.L2040:
	ldr	r1, [r3, #4]!
	cmp	r1, #21
	bhi	.L2037
	cmp	r1, r2
	beq	.L2038
	cmp	r3, r0
	bne	.L2040
.L2038:
	cmp	r2, #8
	mov	r3, #0
	str	r3, [fp, #-116]
	beq	.L2075
.L2041:
	cmp	r2, #9
	beq	.L2076
.L2059:
	cmp	r2, #5
	mov	r3, #0
	str	r3, [fp, #-116]
	beq	.L2077
.L2060:
	mov	r1, r8
	mov	r0, r4
	bl	VCTRL_CmpConfigParameter
	subs	r3, r0, #0
	beq	.L2078
	ldr	r6, .L2080+16
	mov	r2, #148
	ldr	r0, [r7, r4, asl #2]
	mov	r1, r8
	add	r10, r8, #12
	ldr	r3, [r6, #52]
	add	r0, r0, #44
	blx	r3
	ldr	ip, [r8, #24]
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #72
	mov	r1, #0
	sub	r0, fp, #116
	str	ip, [r3, #20]
	ldr	r3, [r7, r4, asl #2]
	ldr	ip, [r8, #8]
	ldr	r9, [r6, #48]
	str	ip, [r3, #568]
	ldr	ip, [r8, #100]
	str	ip, [r3, #1456]
	blx	r9
	ldr	r3, [r7, r4, asl #2]
	mov	r9, #0
	ldr	r3, [r3, #356]
	mov	r0, r3
	str	r3, [fp, #-104]
	bl	MEM_Phy2Vir
	ldr	r3, [r7, r4, asl #2]
	ldr	r1, [r8, #84]
	mov	r2, #49152
	ldr	ip, [r8, #8]
	movt	r2, 63683
	cmp	r1, #1
	ldr	lr, [r8, #24]
	str	r0, [fp, #-116]
	ldr	r0, [r3, #368]
	addeq	r3, r3, #294912
	str	r2, [fp, #-96]
	addne	r3, r3, #294912
	str	ip, [fp, #-108]
	movne	r2, #0
	ldreq	ip, [r8, #92]
	str	r0, [fp, #-100]
	ldreq	r2, [r8, #136]
	ldreq	r0, [r8, #96]
	streq	ip, [fp, #-60]
	strb	lr, [fp, #-112]
	streq	r1, [fp, #-68]
	mov	r1, r10
	streq	r0, [fp, #-56]
	sub	r0, fp, #92
	str	r2, [r3, #1212]
	ldr	r3, [r8, #88]
	ldr	r2, [r8, #80]
	cmp	r3, #0
	str	r9, [fp, #-80]
	str	r9, [fp, #-76]
	movne	r3, #1
	str	r2, [fp, #-72]
	strne	r3, [fp, #-64]
	mov	r2, #12
	ldr	r3, [r6, #52]
	blx	r3
	sub	r1, fp, #116
	mov	r0, r4
	bl	SM_Config
	ldr	r3, [r6, #48]
	mov	r1, r9
	sub	r0, fp, #120
	mov	r2, #1
	blx	r3
	ldr	r3, [r8, #84]
	cmp	r3, #1
	beq	.L2079
.L2051:
	ldr	r3, [r7, r4, asl #2]
	mov	r9, #1
	ldr	r2, .L2080+20
	ldr	r1, [r3, #300]
	ldr	r0, [r3, #348]
	ldr	ip, [r3, #292]
	str	r1, [r3, #1172]
	ldr	r1, [r3, #352]
	str	r0, [r3, #592]
	ldr	r0, [r3, #372]
	str	r1, [r3, #596]
	ldr	r1, [r3, #376]
	str	r0, [r3, #608]
	ldr	r0, [r3, #380]
	str	r1, [r3, #612]
	ldr	r1, [r3, #384]
	str	r0, [r3, #616]
	ldr	r0, [r3, #388]
	str	r1, [r3, #620]
	ldr	r1, [r3, #392]
	str	ip, [r3, #1168]
	add	ip, r3, #294912
	str	r0, [r3, #624]
	str	r1, [r3, #628]
	ldr	r1, [r8, #28]
	ldr	r2, [r2, #72]
	str	r1, [r3, #580]
	cmp	r2, #7
	ldr	r1, [r8, #28]
	str	r1, [r3, #576]
	ldr	r1, [r8, #36]
	str	r1, [r3, #584]
	ldreq	r2, [r8, #40]
	str	r2, [r3, #600]
	mov	r2, #0
	ldr	r1, [r8, #44]
	str	r1, [r3, #588]
	mov	r1, r8
	ldr	r0, [r8, #132]
	str	r0, [r3, #1220]
	ldr	r0, [r8, #140]
	str	r9, [r3, #1224]
	str	r9, [r3, #1228]
	str	r0, [r3, #1524]
	ldr	r0, [r8, #72]
	rsb	r0, r9, r0
	clz	r0, r0
	mov	r0, r0, lsr #5
	str	r0, [r3, #1204]
	ldr	r0, [r8, #76]
	str	r0, [r3, #1208]
	ldr	r0, [r8, #48]
	str	r0, [r3, #1212]
	ldr	r0, [fp, #-76]
	str	r2, [r3, #1496]
	str	r2, [r3, #1516]
	str	r0, [r3, #1216]
	mov	r0, r4
	str	r2, [r3, #1532]
	ldrb	r3, [r8, #1]	@ zero_extendqisi2
	strb	r3, [ip, #1160]
	bl	VCTRL_ConfigChanCompress
	ldr	r0, [r7, r4, asl #2]
	ldr	r3, [r6, #52]
	mov	r2, #12
	add	r0, r0, #1136
	mov	r1, r10
	add	r0, r0, #4
	ldr	r6, .L2080+8
	blx	r3
	ldr	ip, [r7, r4, asl #2]
	add	r3, ip, #294912
	ldr	r7, [ip, #568]
	ldr	r2, [r3, #1224]
	cmp	r2, r7
	beq	.L2053
	mov	r0, r4
	bl	VCTRL_ResetChan
	ldr	r3, [r8, #8]
	ldr	ip, [r6, r4, asl #2]
	cmp	r3, #20
	beq	.L2054
	ldr	r7, [ip, #568]
	add	r3, ip, #294912
.L2053:
	ldr	r2, .L2080+24
	ldr	r0, .L2080+28
	ldr	r1, .L2080+32
	add	lr, r2, #128
	str	r7, [r3, #1224]
.L2058:
	ldr	r3, [r2, #4]!
	add	r0, r0, #4
	add	r1, r1, #4
	cmp	r3, #0
	streq	r3, [r0, #-4]
	ldrne	ip, [r3, #20]
	strne	ip, [r0, #-4]
	ldrne	r3, [r3, #20]
	cmp	r2, lr
	str	r3, [r1, #-4]
	bne	.L2058
	ldr	r0, .L2080+28
	bl	VDMDRV_SetPriority
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2078:
	ldr	r1, .L2080+36
	mov	r5, r3
	bl	dprint_vfmw
.L2069:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2037:
	ldr	r1, .L2080+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r5, #0
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2076:
	sub	r0, fp, #116
	bl	REAL9DEC_Support
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	ldrne	r2, [r8, #8]
	bne	.L2059
.L2042:
	mvn	r5, #0
	b	.L2069
.L2075:
	sub	r0, fp, #116
	bl	REAL8DEC_Support
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	beq	.L2042
	ldr	r2, [r8, #8]
	b	.L2041
.L2077:
	sub	r0, fp, #116
	bl	DIVX3DEC_Support
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	bne	.L2060
	b	.L2042
.L2073:
	ldr	ip, .L2080+44
	movw	r3, #2616
.L2071:
	ldr	r2, .L2080+48
	mov	r0, #0
	ldr	r1, .L2080+52
	mvn	r5, #0
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2079:
	sub	r1, fp, #120
	mov	r0, r4
	strb	r3, [fp, #-120]
	bl	FSP_ConfigAttribute
	b	.L2051
.L2074:
	ldr	r1, .L2080+56
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L2069
.L2054:
	ldr	r3, [ip, #360]
	mov	r0, r4
	ldr	r2, [ip, #1272]
	ldr	r1, [ip, #1268]
	ldr	ip, [ip, #364]
	str	ip, [sp]
	bl	VCTRL_PartitionMemForStdUser
	cmp	r0, #0
	bne	.L2055
	ldr	ip, [r6, r4, asl #2]
	add	r3, ip, #294912
	ldr	r7, [ip, #568]
	b	.L2053
.L2072:
	ldr	ip, .L2080+60
	mov	r0, r3
	movw	r3, #2615
.L2070:
	ldr	r2, .L2080+48
	mvn	r5, #0
	ldr	r1, .L2080+52
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L2069
.L2055:
	mov	r0, r9
	ldr	r1, .L2080+64
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L2069
.L2081:
	.align	2
.L2080:
	.word	.LC218
	.word	.LC99
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2
	.word	.LANCHOR1-4
	.word	.LANCHOR3+1044
	.word	g_ChanCtx
	.word	.LC221
	.word	.LC220
	.word	.LC74
	.word	.LANCHOR0+1620
	.word	.LC0
	.word	.LC219
	.word	.LC100
	.word	.LC222
	UNWIND(.fnend)
	.size	VCTRL_ConfigChan, .-VCTRL_ConfigChan
	.align	2
	.type	VfmwProc_SetUvmosEnable, %function
VfmwProc_SetUvmosEnable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #152)
	sub	sp, sp, #152
	ldr	r4, [r0]
	ldr	r1, .L2086
	mov	r0, #32
	bic	r5, r4, #-16777216
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2086+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	beq	.L2085
	mov	r2, r4
	ldr	r1, .L2086+8
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2085:
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-36]
	bl	VCTRL_ConfigChan
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2087:
	.align	2
.L2086:
	.word	.LC223
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC224
	UNWIND(.fnend)
	.size	VfmwProc_SetUvmosEnable, .-VfmwProc_SetUvmosEnable
	.align	2
	.type	VfmwProc_SetDropStreamThread, %function
VfmwProc_SetDropStreamThread:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #152)
	sub	sp, sp, #152
	ldr	r4, [r0]
	ldr	r1, .L2090
	mov	r0, #32
	bic	r5, r4, #-16777216
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2090+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2088
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-136]
	bl	VCTRL_ConfigChan
.L2088:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2091:
	.align	2
.L2090:
	.word	.LC225
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VfmwProc_SetDropStreamThread, .-VfmwProc_SetDropStreamThread
	.align	2
	.type	VfmwProc_SetDecMode, %function
VfmwProc_SetDecMode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #152)
	sub	sp, sp, #152
	ldr	r4, [r0]
	ldr	r1, .L2096
	mov	r0, #32
	and	r5, r4, #7
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2096+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	beq	.L2095
	mov	r2, r4
	ldr	r1, .L2096+8
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2095:
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-132]
	bl	VCTRL_ConfigChan
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2097:
	.align	2
.L2096:
	.word	.LC226
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC227
	UNWIND(.fnend)
	.size	VfmwProc_SetDecMode, .-VfmwProc_SetDecMode
	.align	2
	.type	VfmwProc_SetDecOrderOutput, %function
VfmwProc_SetDecOrderOutput:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #152)
	sub	sp, sp, #152
	ldr	r4, [r0]
	ldr	r1, .L2100
	mov	r0, #32
	and	r5, r4, #3
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2100+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2098
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-128]
	bl	VCTRL_ConfigChan
.L2098:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2101:
	.align	2
.L2100:
	.word	.LC228
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VfmwProc_SetDecOrderOutput, .-VfmwProc_SetDecOrderOutput
	.align	2
	.type	VfmwProc_SetErrorThread, %function
VfmwProc_SetErrorThread:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 152
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #152)
	sub	sp, sp, #152
	ldr	r4, [r0]
	ldr	r1, .L2104
	mov	r0, #32
	bic	r5, r4, #-16777216
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2104+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2102
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-140]
	bl	VCTRL_ConfigChan
.L2102:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2105:
	.align	2
.L2104:
	.word	.LC229
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VfmwProc_SetErrorThread, .-VfmwProc_SetErrorThread
	.align	2
	.type	VfmwProc_TestResetChan, %function
VfmwProc_TestResetChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0]
	mov	r0, r4
	bl	VCTRL_ResetChan
	mov	r2, r4
	ldr	r1, .L2107
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2108:
	.align	2
.L2107:
	.word	.LC230
	UNWIND(.fnend)
	.size	VfmwProc_TestResetChan, .-VfmwProc_TestResetChan
	.align	2
	.global	VCTRL_DestroyChan
	.type	VCTRL_DestroyChan, %function
VCTRL_DestroyChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #52)
	sub	sp, sp, #52
	ldr	r5, .L2124
	mov	r4, r0
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	cmp	r4, #31
	ldrhi	ip, .L2124+4
	movhi	r3, #2208
	bhi	.L2119
	ldr	r6, .L2124+8
	ldr	r7, [r6, r4, asl #2]
	cmp	r7, #0
	beq	.L2120
	ldr	r8, [r7, #4]
	cmp	r8, #1
	bne	.L2121
	mov	r0, #0
	str	r0, [r7, #8]
	ldr	r3, [r5, #16]
	blx	r3
	mov	r0, r4
	bl	SCDDRV_IsChanDec
	cmp	r0, #0
	bne	.L2122
.L2114:
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r2, .L2124+12
	ldr	r3, [r5, #12]
	mov	r8, #0
	mov	r0, #4
	ldr	r7, .L2124
	str	r8, [r2, r4, asl #2]
	blx	r3
	mov	r0, r4
	bl	VCTRL_StopChan
	ldr	r3, [r7, #16]
	subs	r5, r0, #0
	mov	r0, #4
	bne	.L2123
	blx	r3
	mov	r0, r4
	bl	VCTRL_ResetChan
	bl	VDMDRV_ParamInit
	ldr	r3, .L2124+16
	ldr	r2, [r7, #12]
	mov	r0, #4
	add	r3, r3, r4, lsl #2
	str	r5, [r3, #-640]
	blx	r2
	mov	r0, r4
	bl	FSP_DisableInstance
	mov	r0, r4
	bl	CloseUsdPool_WithMem
	ldr	r3, [r6, r4, asl #2]
	ldr	r0, .L2124+20
	add	r2, r3, #294912
	str	r5, [r6, r4, asl #2]
	ldr	ip, [r3, #340]
	add	r6, r6, r4, lsl #4
	ldr	r1, [r2, #1164]
	ldr	r8, [r2, #1200]
	add	r2, r3, #290816
	add	r2, r2, #1136
	str	r2, [fp, #-64]
	str	r1, [fp, #-56]
	ldr	r2, [r3, #336]
	ldr	r1, [r3, #332]
	str	r5, [r0, r4, asl #3]
	mov	r0, r4
	str	ip, [fp, #-44]
	str	r1, [fp, #-52]
	add	r1, r3, #236
	str	r2, [fp, #-48]
	add	r2, r3, #260
	str	r1, [fp, #-76]
	str	r2, [fp, #-72]
	add	r2, r3, #284
	add	r3, r3, #308
	str	r2, [fp, #-68]
	str	r3, [fp, #-60]
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r4
	bl	SCDDRV_ResetSCD
	mov	r0, r4
	bl	VDMDRV_ResetVDH
	ldr	r2, [r7, #16]
	mvn	r3, #0
	str	r5, [r6, #396]
	str	r3, [r6, #408]
	mov	r0, #4
	str	r3, [r6, #404]
	str	r5, [r6, #400]
	blx	r2
	ldr	r3, [r7, #16]
	mov	r0, r5
	blx	r3
	ldr	r3, [r7, #24]
	mov	r1, r4
	mov	r0, #1
	blx	r3
	mov	r0, r8
	sub	r1, fp, #60
	bl	VCTRL_DelRecordEsBuf.isra.5
	sub	r1, fp, #76
	mov	r0, r4
	bl	VCTRL_FreeChanResource
	mov	r0, #1
	ldr	r3, [r7, #28]
	mov	r1, r4
	blx	r3
	mov	r0, r5
.L2111:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2122:
	mov	r0, r4
	ldr	r7, [r5, #132]
	bl	SCDDRV_IsChanDec
	mov	r2, #500
	clz	r1, r0
	mov	r0, r8
	mov	r1, r1, lsr #5
	blx	r7
	b	.L2114
.L2121:
	ldr	ip, .L2124+24
	movw	r3, #2222
.L2119:
	ldr	r2, .L2124+28
	mov	r0, #0
	ldr	r1, .L2124+32
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2123:
	blx	r3
	ldr	r3, [r7, #16]
	mov	r0, r8
	blx	r3
	mvn	r0, #0
	b	.L2111
.L2120:
	ldr	ip, .L2124+36
	movw	r3, #2215
	ldr	r2, .L2124+28
	mov	r0, r7
	ldr	r1, .L2124+32
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #16]
	mov	r0, r7
	blx	r3
	mvn	r0, #0
	b	.L2111
.L2125:
	.align	2
.L2124:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC65
	.word	.LANCHOR1
	.word	g_LowDelaySeqIndex
	.word	.LANCHOR3
	.word	s_SmIIS
	.word	.LC233
	.word	.LANCHOR0+1640
	.word	.LC231
	.word	.LC232
	UNWIND(.fnend)
	.size	VCTRL_DestroyChan, .-VCTRL_DestroyChan
	.align	2
	.global	VCTRL_CloseVfmw
	.type	VCTRL_CloseVfmw, %function
VCTRL_CloseVfmw:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, .L2144
	ldr	r3, [r6, #128]
	cmp	r3, #1
	bne	.L2133
	sub	r5, r6, #4
	mov	r4, #0
.L2129:
	ldr	r3, [r5, #4]!
	mov	r0, r4
	add	r4, r4, #1
	cmp	r3, #0
	beq	.L2128
	bl	VCTRL_DestroyChan
.L2128:
	cmp	r4, #32
	bne	.L2129
	bl	FSP_Exit
	ldr	r3, [r6, #132]
	mov	r2, #3
	ldr	r5, .L2144+4
	cmp	r3, #0
	str	r2, [r6, #136]
	beq	.L2131
	mov	r0, #10
	ldr	r3, [r5, #120]
	mov	r4, #49
	blx	r3
	b	.L2132
.L2143:
	ldr	r3, [r5, #120]
	blx	r3
	subs	r4, r4, #1
	beq	.L2131
.L2132:
	ldr	r3, [r6, #132]
	mov	r0, #10
	cmp	r3, #0
	bne	.L2143
.L2131:
	ldr	r3, [r5, #48]
	mov	r2, #128
	mov	r1, #0
	ldr	r0, .L2144+8
	blx	r3
	ldr	r0, .L2144+12
	bl	CloseDrivers
	mov	r3, #0
	mov	r0, r3
	str	r3, [r6, #128]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2133:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2145:
	.align	2
.L2144:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3-640
	.word	.LANCHOR1+152
	UNWIND(.fnend)
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	2
	.type	VfmwProc_TestRestartChan, %function
VfmwProc_TestRestartChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0]
	mov	r0, r4
	bl	VCTRL_StopChan
	mov	r2, r4
	ldr	r1, .L2147
	mov	r3, r0
	mov	r0, #32
	bl	dprint_vfmw
	mov	r0, r4
	bl	VCTRL_ResetChan
	mov	r2, r4
	ldr	r1, .L2147+4
	mov	r3, r0
	mov	r0, #32
	bl	dprint_vfmw
	mov	r0, r4
	bl	VCTRL_StartChan
	mov	r2, r4
	ldr	r1, .L2147+8
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2148:
	.align	2
.L2147:
	.word	.LC234
	.word	.LC230
	.word	.LC202
	UNWIND(.fnend)
	.size	VfmwProc_TestRestartChan, .-VfmwProc_TestRestartChan
	.align	2
	.type	VfmwProc_TestStopChan, %function
VfmwProc_TestStopChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [r0]
	mov	r0, r4
	bl	VCTRL_StopChan
	mov	r2, r4
	ldr	r1, .L2150
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2151:
	.align	2
.L2150:
	.word	.LC234
	UNWIND(.fnend)
	.size	VfmwProc_TestStopChan, .-VfmwProc_TestStopChan
	.align	2
	.global	VCTRL_InitDspCode
	.type	VCTRL_InitDspCode, %function
VCTRL_InitDspCode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #6
	mov	r5, r0
	moveq	r4, #1
	beq	.L2153
	cmp	r1, #0
	moveq	r4, #2
	movne	r4, #0
.L2153:
	ldr	r3, .L2167
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L2163
	mov	r1, r4
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Require_DspCode
.L2163:
	ldr	r6, .L2167+4
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L2164
	mov	r0, #0
	blx	r3
.L2156:
	ldr	r3, [r6, #20]
	cmp	r3, #0
	beq	.L2165
	mov	r0, #0
	blx	r3
.L2158:
	ldr	r3, [r6, #12]
	cmp	r3, #0
	beq	.L2166
	mov	r0, #0
	blx	r3
.L2160:
	mov	r1, r4
	mov	r0, #0
	bl	SCDDRV_LoadDspCode
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_CloseHardware
.L2164:
	mov	r0, r3
	movw	r2, #2876
	ldr	r1, .L2167+8
	bl	dprint_vfmw
	b	.L2156
.L2165:
	mov	r0, r3
	movw	r2, #2877
	ldr	r1, .L2167+8
	bl	dprint_vfmw
	b	.L2158
.L2166:
	mov	r0, r3
	movw	r2, #2878
	ldr	r1, .L2167+8
	bl	dprint_vfmw
	b	.L2160
.L2168:
	.align	2
.L2167:
	.word	g_HalDisable
	.word	g_vdm_hal_fun_ptr
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_InitDspCode, .-VCTRL_InitDspCode
	.align	2
	.global	VCTRL_LoadDspCode
	.type	VCTRL_LoadDspCode, %function
VCTRL_LoadDspCode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2195
	mov	r5, r0
	ldr	r3, [r3, r0, asl #2]
	ldr	r1, [r3, #568]
	cmp	r1, #0
	movne	r3, #1
	movne	r6, #0
	ldreq	r6, [r3, #1212]
	clzeq	r3, r6
	moveq	r3, r3, lsr #5
.L2170:
	cmp	r1, #6
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	beq	.L2191
.L2182:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2191:
	ldr	r7, .L2195+4
	ldr	r4, [r7, #-640]
	cmp	r4, #0
	bne	.L2171
	sub	r3, r7, #640
	sub	r2, r7, #516
	b	.L2172
.L2193:
	cmp	r3, r2
	beq	.L2192
.L2172:
	ldr	r4, [r3, #4]!
	cmp	r4, #0
	beq	.L2193
.L2171:
	cmp	r4, #1
	beq	.L2194
	cmp	r1, #6
	beq	.L2182
	ldr	r1, .L2195+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2192:
	mov	r0, r5
	add	r5, r7, r5, lsl #2
	bl	VCTRL_InitDspCode
	cmp	r6, #1
	mov	r0, r4
	streq	r6, [r5, #-640]
	movne	r3, #2
	strne	r3, [r5, #-640]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2194:
	cmp	r6, #1
	beq	.L2182
	ldr	r1, .L2195+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2196:
	.align	2
.L2195:
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	.LC236
	.word	.LC235
	UNWIND(.fnend)
	.size	VCTRL_LoadDspCode, .-VCTRL_LoadDspCode
	.align	2
	.global	VCTRL_SetChanFsPartitionState
	.type	VCTRL_SetChanFsPartitionState, %function
VCTRL_SetChanFsPartitionState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2198
	ldr	r3, [r3, r0, asl #2]
	add	r3, r3, #262144
	str	r1, [r3, #2016]
	ldmfd	sp, {fp, sp, pc}
.L2199:
	.align	2
.L2198:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_SetChanFsPartitionState, .-VCTRL_SetChanFsPartitionState
	.align	2
	.global	VCTRL_GetCurChanFsSize
	.type	VCTRL_GetCurChanFsSize, %function
VCTRL_GetCurChanFsSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2201
	ldr	r3, [r3, r0, asl #2]
	add	r3, r3, #290816
	ldr	r0, [r3, #1108]
	ldmfd	sp, {fp, sp, pc}
.L2202:
	.align	2
.L2201:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_GetCurChanFsSize, .-VCTRL_GetCurChanFsSize
	.align	2
	.global	VCTRT_SetChanCtrlState
	.type	VCTRT_SetChanCtrlState, %function
VCTRT_SetChanCtrlState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #1
	beq	.L2205
	bcc	.L2206
	cmp	r1, #2
	bne	.L2213
	ldr	r3, .L2214
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #768]
	cmp	r3, #1
	beq	.L2210
	mov	r3, #0
	str	r1, [r0, #768]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2213:
	mov	r3, #0
.L2204:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2206:
	ldr	r2, .L2214
	mov	r1, #0
	mov	r3, r1
	add	r0, r2, r0, lsl #2
	str	r1, [r0, #768]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2205:
	ldr	r3, .L2214
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #768]
	cmp	r3, #0
	bne	.L2210
	str	r1, [r0, #768]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2210:
	mvn	r3, #0
	b	.L2204
.L2215:
	.align	2
.L2214:
	.word	.LANCHOR3
	UNWIND(.fnend)
	.size	VCTRT_SetChanCtrlState, .-VCTRT_SetChanCtrlState
	.align	2
	.global	VCTRL_AddFrameBufMemoryRecord
	.type	VCTRL_AddFrameBufMemoryRecord, %function
VCTRL_AddFrameBufMemoryRecord:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0]
	mov	r4, r0
	cmp	r3, #255
	beq	.L2217
	ldr	r2, [r0, #12]
	ldr	r1, [r0, #24]
	ldr	r0, [r0, #32]
	bl	MEM_AddMemRecord
.L2217:
	ldr	r3, [r4, #4]
	cmp	r3, #255
	beq	.L2218
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #40]
	ldr	r0, [r4, #48]
	bl	MEM_AddMemRecord
.L2218:
	ldr	r3, [r4, #8]
	cmp	r3, #255
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, [r4, #20]
	ldr	r1, [r4, #56]
	ldr	r0, [r4, #64]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MEM_AddMemRecord
	UNWIND(.fnend)
	.size	VCTRL_AddFrameBufMemoryRecord, .-VCTRL_AddFrameBufMemoryRecord
	.align	2
	.global	VCTRL_SetSingleFrameBufToChan
	.type	VCTRL_SetSingleFrameBufToChan, %function
VCTRL_SetSingleFrameBufToChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r6, .L2260
	mov	r4, r0
	mov	r5, r1
	ldr	r1, [r1, #12]
	ldr	r2, [r6, r0, asl #2]
	add	r3, r2, #294912
	add	r2, r2, #290816
	ldr	r0, [r3, #584]
	cmp	r0, r1
	beq	.L2227
	ldr	ip, [r2, #1104]
	cmp	ip, #0
	beq	.L2255
.L2227:
	ldr	r2, [r2, #3496]
	cmp	r2, #0
	beq	.L2229
	ldr	r2, [r3, #616]
	cmp	r2, #0
	beq	.L2256
.L2229:
	ldr	r7, .L2260+4
	mov	r0, #8
	ldr	r3, [r7, #12]
	blx	r3
	ldr	r0, [r6, r4, asl #2]
	add	r3, r0, #290816
	ldr	r3, [r3, #1136]
	cmp	r3, #255
	beq	.L2237
	movw	r2, #29880
	mov	r1, #1
	movt	r2, 4
	add	r2, r0, r2
	b	.L2231
.L2258:
	add	r1, r1, #1
	cmp	r1, #32
	beq	.L2257
.L2231:
	ldr	ip, [r2]
	add	r2, r2, #72
	cmp	ip, #255
	bne	.L2258
.L2230:
	mov	r3, r1, asl #6
	mov	r2, #72
	add	r1, r3, r1, lsl #3
	ldr	r8, [r7, #52]
	add	r3, r1, #290816
	mov	r1, r5
	add	r3, r3, #1136
	add	r0, r0, r3
	blx	r8
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r5
	add	r3, r3, #294912
	ldr	r2, [r3, #616]
	add	r2, r2, #1
	str	r2, [r3, #616]
	bl	VCTRL_AddFrameBufMemoryRecord
	ldr	r3, [r6, r4, asl #2]
	add	r3, r3, #294912
	ldr	r3, [r3, #620]
	cmp	r3, #0
	bne	.L2259
.L2235:
	mov	r4, #0
.L2234:
	ldr	r3, [r7, #16]
	mov	r0, #8
	blx	r3
	mov	r0, r4
.L2250:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2256:
	ldr	r3, [r5, #8]
	cmp	r3, #255
	bne	.L2229
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	movw	r3, #8182
	ldr	r2, .L2260+8
	ldr	r1, .L2260+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2250
.L2257:
	mov	r3, r4
	ldr	r2, .L2260+8
	ldr	r1, .L2260+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2234
.L2259:
	mov	r1, r5
	mov	r0, r4
	bl	FSP_SetSingleFrameBuf
	cmp	r0, #0
	beq	.L2235
	mov	r3, r4
	ldr	r2, .L2260+8
	ldr	r1, .L2260+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2234
.L2237:
	mov	r1, #0
	b	.L2230
.L2255:
	str	r0, [sp, #4]
	movw	r3, #8172
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L2260+8
	ldr	r1, .L2260+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2250
.L2261:
	.align	2
.L2260:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1660
	.word	.LC238
	.word	.LC240
	.word	.LC239
	.word	.LC237
	UNWIND(.fnend)
	.size	VCTRL_SetSingleFrameBufToChan, .-VCTRL_SetSingleFrameBufToChan
	.align	2
	.global	VCTRL_AllocMemToDecoder
	.type	VCTRL_AllocMemToDecoder, %function
VCTRL_AllocMemToDecoder:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r5, .L2274
	mov	r7, r0, asl #2
	mov	r4, r0
	add	r3, r5, r7
	ldr	r10, [r3, #768]
	cmp	r10, #0
	bne	.L2263
	ldr	r8, .L2274+4
	mov	ip, #1
	mov	r2, #72
	str	ip, [r3, #768]
	sub	r0, fp, #116
	ldr	r9, .L2274+8
	ldr	r3, [r8, #52]
	blx	r3
	sub	r1, fp, #116
	mov	r0, r4
	bl	VCTRL_SetSingleFrameBufToChan
	ldr	r3, [r9, r4, asl #2]
	subs	r6, r0, #0
	bne	.L2272
.L2265:
	add	r3, r3, #262144
	mov	r2, #2
	ldr	r1, .L2274+12
	mov	r0, #31
	str	r2, [r3, #2016]
	bl	dprint_vfmw
	ldr	r3, [r9, r4, asl #2]
	ldr	r9, .L2274+8
	add	r3, r3, #294912
	ldr	r3, [r3, #1220]
	cmp	r3, #1
	beq	.L2273
.L2266:
	add	r5, r5, r7
	mov	r0, r6
	mov	r3, #0
	str	r3, [r5, #768]
.L2271:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2272:
	add	r2, r3, #290816
	ldr	r2, [r2, #1108]
	cmp	r2, #0
	beq	.L2265
	mov	r2, r4
	ldr	r1, .L2274+16
	mov	r0, r10
	bl	dprint_vfmw
	ldr	r3, [r9, r4, asl #2]
	mov	r1, #3
	add	r2, r3, #262144
	str	r1, [r2, #2016]
	b	.L2265
.L2273:
	ldr	r3, [r8, #128]
	mov	r0, #0
	blx	r3
	ldr	r3, [r9, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #294912
	str	r2, [r3, #1220]
	b	.L2266
.L2263:
	mov	r3, r0
	ldr	r2, .L2274+20
	ldr	r1, .L2274+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2271
.L2275:
	.align	2
.L2274:
	.word	.LANCHOR3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC242
	.word	.LC241
	.word	.LANCHOR0+1692
	.word	.LC243
	UNWIND(.fnend)
	.size	VCTRL_AllocMemToDecoder, .-VCTRL_AllocMemToDecoder
	.align	2
	.global	VCTRL_GetFsSize
	.type	VCTRL_GetFsSize, %function
VCTRL_GetFsSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	ldr	r3, .L2281
	mov	r5, r0
	mov	r6, r1
	mov	r7, r2
	sub	r0, fp, #52
	ldr	r3, [r3, #48]
	mov	r2, #24
	mov	r1, #0
	blx	r3
	ldr	r3, .L2281+4
	ldr	r4, [r3, #52]
	cmp	r4, #0
	beq	.L2277
	ldr	ip, .L2281+8
	sub	r3, fp, #52
	str	r3, [sp, #4]
	mov	r2, r7
	mov	r1, r6
	mov	r0, r5
	ldr	ip, [ip, r5, asl #2]
	mov	r3, #0
	add	ip, ip, #294912
	ldr	ip, [ip, #1224]
	str	ip, [sp]
	blx	r4
.L2277:
	ldr	r0, [fp, #-48]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2282:
	.align	2
.L2281:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	VCTRL_GetFsSize, .-VCTRL_GetFsSize
	.align	2
	.global	VCTRL_EnableEsBuf
	.type	VCTRL_EnableEsBuf, %function
VCTRL_EnableEsBuf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2284
	mov	r2, #1
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #1172]
	ldmfd	sp, {fp, sp, pc}
.L2285:
	.align	2
.L2284:
	.word	.LANCHOR3
	UNWIND(.fnend)
	.size	VCTRL_EnableEsBuf, .-VCTRL_EnableEsBuf
	.align	2
	.global	VCTRL_DisableEsBuf
	.type	VCTRL_DisableEsBuf, %function
VCTRL_DisableEsBuf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2287
	mov	r2, #0
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #1172]
	ldmfd	sp, {fp, sp, pc}
.L2288:
	.align	2
.L2287:
	.word	.LANCHOR3
	UNWIND(.fnend)
	.size	VCTRL_DisableEsBuf, .-VCTRL_DisableEsBuf
	.align	2
	.global	VCTRL_IfEsBufEnable
	.type	VCTRL_IfEsBufEnable, %function
VCTRL_IfEsBufEnable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L2290
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #1172]
	ldmfd	sp, {fp, sp, pc}
.L2291:
	.align	2
.L2290:
	.word	.LANCHOR3
	UNWIND(.fnend)
	.size	VCTRL_IfEsBufEnable, .-VCTRL_IfEsBufEnable
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
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.54146, %object
	.size	__func__.54146, 18
__func__.54146:
	.ascii	"VCTRL_EventReport\000"
	.space	2
	.type	__func__.55308, %object
	.size	__func__.55308, 24
__func__.55308:
	.ascii	"VCTRL_SetLastFrameState\000"
	.type	__func__.54085, %object
	.size	__func__.54085, 20
__func__.54085:
	.ascii	"VCTRL_RecordPosTime\000"
	.type	__func__.54090, %object
	.size	__func__.54090, 17
__func__.54090:
	.ascii	"VCTRL_RecordData\000"
	.space	3
	.type	__func__.54137, %object
	.size	__func__.54137, 23
__func__.54137:
	.ascii	"VCTRL_SetMoreGapEnable\000"
	.space	1
	.type	__func__.54158, %object
	.size	__func__.54158, 18
__func__.54158:
	.ascii	"VCTRL_SetCallBack\000"
	.space	2
	.type	__func__.54198, %object
	.size	__func__.54198, 25
__func__.54198:
	.ascii	"VCTRL_SetStreamInterface\000"
	.space	3
	.type	__func__.54203, %object
	.size	__func__.54203, 29
__func__.54203:
	.ascii	"VCTRL_SetSendStreamAgainFlag\000"
	.space	3
	.type	__func__.54207, %object
	.size	__func__.54207, 29
__func__.54207:
	.ascii	"VCTRL_GetSendStreamAgainFlag\000"
	.space	3
	.type	__func__.54217, %object
	.size	__func__.54217, 20
__func__.54217:
	.ascii	"VCTRL_GetStreamSize\000"
	.type	__func__.54224, %object
	.size	__func__.54224, 20
__func__.54224:
	.ascii	"VCTRL_CheckFreshRaw\000"
	.type	__func__.54231, %object
	.size	__func__.54231, 20
__func__.54231:
	.ascii	"VCTRL_CheckFreshSeg\000"
	.type	__func__.54236, %object
	.size	__func__.54236, 25
__func__.54236:
	.ascii	"VCTRL_SetDiscardPicParam\000"
	.space	3
	.type	__FUNCTION__.54264, %object
	.size	__FUNCTION__.54264, 29
__FUNCTION__.54264:
	.ascii	"VCTRL_PartitionMemForStdUser\000"
	.space	3
	.type	__func__.54279, %object
	.size	__func__.54279, 21
__func__.54279:
	.ascii	"DelAllFrameMemRecord\000"
	.space	3
	.type	__func__.54289, %object
	.size	__func__.54289, 23
__func__.54289:
	.ascii	"VCTRL_FreeChanResource\000"
	.space	1
	.type	__func__.54415, %object
	.size	__func__.54415, 17
__func__.54415:
	.ascii	"VCTRL_GetChanCfg\000"
	.space	3
	.type	__func__.54476, %object
	.size	__func__.54476, 14
__func__.54476:
	.ascii	"VCTRL_SeekPts\000"
	.space	2
	.type	__func__.54509, %object
	.size	__func__.54509, 20
__func__.54509:
	.ascii	"VCTRL_ReleaseStream\000"
	.type	__func__.54529, %object
	.size	__func__.54529, 24
__func__.54529:
	.ascii	"VCTRL_ImageOutputEnable\000"
	.type	__func__.54568, %object
	.size	__func__.54568, 25
__func__.54568:
	.ascii	"VCTRL_TryToRelSpecialFrm\000"
	.space	3
	.type	__func__.54592, %object
	.size	__func__.54592, 19
__func__.54592:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__FUNCTION__.54600, %object
	.size	__FUNCTION__.54600, 19
__FUNCTION__.54600:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__func__.54607, %object
	.size	__func__.54607, 23
__func__.54607:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__FUNCTION__.54611, %object
	.size	__FUNCTION__.54611, 23
__FUNCTION__.54611:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__func__.54619, %object
	.size	__func__.54619, 23
__func__.54619:
	.ascii	"VCTRL_GetHDRConfigInfo\000"
	.space	1
	.type	__func__.54645, %object
	.size	__func__.54645, 18
__func__.54645:
	.ascii	"VCTRL_GetDecParam\000"
	.space	2
	.type	__func__.54727, %object
	.size	__func__.54727, 20
__func__.54727:
	.ascii	"VCTRL_ClearDecparam\000"
	.type	__func__.54756, %object
	.size	__func__.54756, 21
__func__.54756:
	.ascii	"VCTRL_VdmProcSedOnly\000"
	.space	3
	.type	__func__.54764, %object
	.size	__func__.54764, 21
__func__.54764:
	.ascii	"VCTRL_GetImageBuffer\000"
	.space	3
	.type	__func__.54787, %object
	.size	__func__.54787, 22
__func__.54787:
	.ascii	"VCTRL_ConfigFFFBSpeed\000"
	.space	2
	.type	__func__.54792, %object
	.size	__func__.54792, 20
__func__.54792:
	.ascii	"VCTRL_ConfigPVRInfo\000"
	.type	__func__.54796, %object
	.size	__func__.54796, 19
__func__.54796:
	.ascii	"VCTRL_IsChanActive\000"
	.space	1
	.type	__func__.54802, %object
	.size	__func__.54802, 13
__func__.54802:
	.ascii	"USERDEC_Init\000"
	.space	3
	.type	__func__.54821, %object
	.size	__func__.54821, 21
__func__.54821:
	.ascii	"VCTRL_GetUsrdecFrame\000"
	.space	3
	.type	__func__.54831, %object
	.size	__func__.54831, 14
__func__.54831:
	.ascii	"InitSyntaxCtx\000"
	.space	2
	.type	__func__.54167, %object
	.size	__func__.54167, 15
__func__.54167:
	.ascii	"VCTRL_OpenVfmw\000"
	.space	1
	.type	__FUNCTION__.55038, %object
	.size	__FUNCTION__.55038, 18
__FUNCTION__.55038:
	.ascii	"GetExtraRefFrmNum\000"
	.space	2
	.type	__FUNCTION__.55044, %object
	.size	__FUNCTION__.55044, 19
__FUNCTION__.55044:
	.ascii	"GetExtraDispFrmNum\000"
	.space	1
	.type	__FUNCTION__.55050, %object
	.size	__FUNCTION__.55050, 16
__FUNCTION__.55050:
	.ascii	"GetExtraCtrlCmd\000"
	.type	__func__.54984, %object
	.size	__func__.54984, 14
__func__.54984:
	.ascii	"DecChanSyntax\000"
	.space	2
	.type	__FUNCTION__.54985, %object
	.size	__FUNCTION__.54985, 14
__FUNCTION__.54985:
	.ascii	"DecChanSyntax\000"
	.space	2
	.type	__func__.54518, %object
	.size	__func__.54518, 24
__func__.54518:
	.ascii	"VCTRL_FindOccupiedFrame\000"
	.type	__func__.54539, %object
	.size	__func__.54539, 26
__func__.54539:
	.ascii	"VCTRL_ReportOccupiedFrame\000"
	.space	2
	.type	__func__.55015, %object
	.size	__func__.55015, 20
__func__.55015:
	.ascii	"VCTRL_GetChanImgNum\000"
	.type	__func__.54247, %object
	.size	__func__.54247, 19
__func__.54247:
	.ascii	"VCTRL_GetChanState\000"
	.space	1
	.type	__func__.55019, %object
	.size	__func__.55019, 19
__func__.55019:
	.ascii	"VCTRL_GetChanWidth\000"
	.space	1
	.type	__func__.55023, %object
	.size	__func__.55023, 20
__func__.55023:
	.ascii	"VCTRL_GetChanHeight\000"
	.type	__func__.55027, %object
	.size	__func__.55027, 22
__func__.55027:
	.ascii	"VCTRL_GetChanCapLevel\000"
	.space	2
	.type	g_ProcCommandTable, %object
	.size	g_ProcCommandTable, 360
g_ProcCommandTable:
	.word	0
	.word	VfmwProc_SetPrintLevel
	.word	2
	.word	VfmwProc_SetErrorThread
	.word	3
	.word	VfmwProc_SetDefaultOutputOrder
	.word	4
	.word	VfmwProc_SetDecOrderOutput
	.word	5
	.word	VfmwProc_SetDecMode
	.word	7
	.word	VfmwProc_SetDropStreamThread
	.word	8
	.word	VfmwProc_SetVp9DecFrameNum
	.word	9
	.word	VfmwProc_SetUvmosEnable
	.word	11
	.word	VfmwProc_SetUSE_FF_APT_EN
	.word	12
	.word	VfmwProc_SetSaveFileAfterReset
	.word	13
	.word	VfmwProc_SetCurProcChan
	.word	256
	.word	VfmwProc_PrintTracer
	.word	257
	.word	VfmwProc_SetScdPrint
	.word	512
	.word	VfmwProc_Savestream
	.word	513
	.word	VfmwProc_SaveSeg
	.word	514
	.word	VfmwProc_SaveYUV
	.word	516
	.word	VfmwProc_Save1DYUV
	.word	528
	.word	VfmwProc_SaveMetadata
	.word	544
	.word	VfmwProc_SaveReorderMetadata
	.word	560
	.word	VfmwProc_SaveEL
	.word	768
	.word	VfmwProc_TestSuspend
	.word	769
	.word	VfmwProc_TestResume
	.word	896
	.word	VfmwProc_TestStopChan
	.word	897
	.word	VfmwProc_TestResetChan
	.word	898
	.word	VfmwProc_TestStartChan
	.word	899
	.word	VfmwProc_TestRestartChan
	.word	1024
	.word	VfmwProc_TestTimeSequence
	.word	1026
	.word	VfmwProc_TestStopDec
	.word	1280
	.word	VfmwProc_SetTraceCtrl
	.word	1281
	.word	VfmwProc_SetTraceBSPeriod
	.word	1282
	.word	VfmwProc_SetTraceFramePeriod
	.word	1283
	.word	VfmwProc_SetTraceImgPeriod
	.word	1285
	.word	VfmwProc_SetSaveYuvBitWidth
	.word	1536
	.word	VfmwProc_OpenModuleLowly
	.word	1537
	.word	VfmwProc_CloseModuleLowly
	.word	1538
	.word	VfmwProc_SetTunnelLineNumber
	.word	1539
	.word	VfmwProc_OpenScdLowdly
	.word	1540
	.word	VfmwProc_CloseScdLowdly
	.word	1541
	.word	VfmwProc_SetSedOnlyEnable
	.word	1792
	.word	VfmwProc_SetSmmuIrqEnable
	.word	2048
	.word	VfmwProc_SetCompressPara
	.word	2304
	.word	VfmwProc_SetClkSelect
	.word	2305
	.word	VfmwProc_SetStandardObedience
	.word	2306
	.word	VfmwProc_SetSegBypass
	.word	65535
	.word	0
	.type	__func__.55323, %object
	.size	__func__.55323, 22
__func__.55323:
	.ascii	"VCTRL_OutputLastFrame\000"
	.space	2
	.type	__func__.54702, %object
	.size	__func__.54702, 15
__func__.54702:
	.ascii	"VCTRL_PostProc\000"
	.space	1
	.type	__func__.54751, %object
	.size	__func__.54751, 18
__func__.54751:
	.ascii	"VCTRL_VdmPostProc\000"
	.space	2
	.type	__func__.55349, %object
	.size	__func__.55349, 21
__func__.55349:
	.ascii	"VCTRL_SvdecLastFrame\000"
	.space	3
	.type	__func__.54827, %object
	.size	__func__.54827, 21
__func__.54827:
	.ascii	"VCTRL_PutUsrdecFrame\000"
	.space	3
	.type	__func__.54394, %object
	.size	__func__.54394, 16
__func__.54394:
	.ascii	"VCTRL_StartChan\000"
	.type	__func__.54410, %object
	.size	__func__.54410, 15
__func__.54410:
	.ascii	"VCTRL_StopChan\000"
	.space	1
	.type	__func__.54503, %object
	.size	__func__.54503, 26
__func__.54503:
	.ascii	"VCTRL_ResetChanWithOption\000"
	.space	2
	.type	__func__.54582, %object
	.size	__func__.54582, 16
__func__.54582:
	.ascii	"VCTRL_ResetChan\000"
	.type	__func__.54461, %object
	.size	__func__.54461, 17
__func__.54461:
	.ascii	"VCTRL_ConfigChan\000"
	.space	3
	.type	__func__.54388, %object
	.size	__func__.54388, 18
__func__.54388:
	.ascii	"VCTRL_DestroyChan\000"
	.space	2
	.type	__func__.55444, %object
	.size	__func__.55444, 30
__func__.55444:
	.ascii	"VCTRL_SetSingleFrameBufToChan\000"
	.space	2
	.type	__func__.55456, %object
	.size	__func__.55456, 24
__func__.55456:
	.ascii	"VCTRL_AllocMemToDecoder\000"
	.data
	.align	2
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
	.space	59
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%s %d: %s\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"InstID out of range\000" )
.LC2:
	ASCII(.ascii	"Chan inactive\000" )
	.space	2
.LC3:
	ASCII(.ascii	"s_VfmwCTrl.event_report_vdec = NULL\012\000" )
	.space	3
.LC4:
	ASCII(.ascii	"s_VfmwCTrl.event_report_omxvdec = NULL\012\000" )
.LC5:
	ASCII(.ascii	"%s Unkown Adapter Type: %d, Len: %d\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"Set standard obedience: %d\012\000" )
.LC7:
	ASCII(.ascii	"g_ClkSelect(%d) set error! dat = %d not support\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC8:
	ASCII(.ascii	"ChanID: %d, VcmpEn: %d, LossCmpEN: %d, YRatio: 0.%d" )
	ASCII(.ascii	", UVRatio: 0.%d\012\000" )
.LC9:
	ASCII(.ascii	"ChanID: %d, VcmpEn: %d, LossCmpEN: %d\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"ChanID:%d, Compress Disable!\000" )
	.space	3
.LC11:
	ASCII(.ascii	"ChanID:%d; \000" )
.LC12:
	ASCII(.ascii	"VCmpEnable:%d; \000" )
.LC13:
	ASCII(.ascii	"LossCmpEnable:%d; \000" )
	.space	1
.LC14:
	ASCII(.ascii	"YCmpRatio:%d, YCmpRatio:%d\012\000" )
.LC15:
	ASCII(.ascii	"ChanID %d Already Create! Can not be set!!\012\000" )
.LC16:
	ASCII(.ascii	"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleL" )
	ASCII(.ascii	"owlyEnable = 1 ------\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"ERROR: g_SaveYUVBitWidth should be 8 or 10! (not to" )
	ASCII(.ascii	" be %d)\012\000" )
.LC18:
	ASCII(.ascii	"------ g_SaveYUVBitWidth = %d ------\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"------ g_TraceImgPeriod = %x ------\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"------ g_TraceFramePeriod = %x ------\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"------ g_TraceBsPeriod = %x ------\012\000" )
.LC22:
	ASCII(.ascii	"------ g_TraceCtrl = %x ------\012\000" )
.LC23:
	ASCII(.ascii	"------ dec stop = %d ------\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"------ dec task delay %d ms ------\012\000" )
.LC25:
	ASCII(.ascii	"%s/vfmw_el_save_%d.dat\000" )
	.space	1
.LC26:
	ASCII(.ascii	"OK create file '%s' for channel %d el stream save\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC27:
	ASCII(.ascii	"failed create file '%s' for el stream save!\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	">>>> close el stream saving >>>>\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"NO SUCH CHANNEL : %d\012\000" )
	.space	2
.LC30:
	ASCII(.ascii	"Pay attention to  CHANNEL : %d\012\000" )
.LC31:
	ASCII(.ascii	"ResetCreateNewSave = %d\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"ResetCreateNewSave can NOT be set to %d, must be 0 " )
	ASCII(.ascii	"or 1\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"USE_FF_APT_EN = %d\012\000" )
.LC34:
	ASCII(.ascii	"USE_FF_APT_EN can NOT be set to %d, must be 0 or 1\012" )
	ASCII(.ascii	"\000" )
.LC35:
	ASCII(.ascii	"g_CfgVp9FrmNum = %d\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"Invalid output order %d\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"set default output order %d\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"OK create file '%s' for channel %d metadata_reorder" )
	ASCII(.ascii	" stream save\012\000" )
	.space	3
.LC39:
	ASCII(.ascii	"failed create file '%s' for metadata_reorder stream" )
	ASCII(.ascii	" save!\012\000" )
	.space	1
.LC40:
	ASCII(.ascii	">>>> close metadata stream saving >>>>\012\000" )
.LC41:
	ASCII(.ascii	"OK create file '%s' for channel %d metadata stream " )
	ASCII(.ascii	"save\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"failed create file '%s' for metadata stream save!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC43:
	ASCII(.ascii	"address '0x%x' is not valid!\012\000" )
	.space	2
.LC44:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"1d image has been saved to '%s'\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"open file '%s' fail!\012\000" )
	.space	2
.LC47:
	ASCII(.ascii	"OK create file '%s' for channel %d seg stream save\012" )
	ASCII(.ascii	"\000" )
.LC48:
	ASCII(.ascii	"failed create file '%s' for seg stream save!\012\000" )
	.space	2
.LC49:
	ASCII(.ascii	">>>> close seg stream saving >>>>\012\000" )
	.space	1
.LC50:
	ASCII(.ascii	"OK create file '%s' for channel %d raw stream save\012" )
	ASCII(.ascii	"\000" )
.LC51:
	ASCII(.ascii	"failed create file '%s' for raw stream save!\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	">>>> close raw stream saving >>>>\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"Failed to alloc VFMW_DumpImageTmp size %d!\012\000" )
.LC54:
	ASCII(.ascii	"OK create file '%s' for chan %d yuv save.(crop %d)\012" )
	ASCII(.ascii	"\000" )
.LC55:
	ASCII(.ascii	"failed create file '%s' for yuv save!\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"OK close yuv save.\012\000" )
.LC57:
	ASCII(.ascii	"print memory tracer...\012\000" )
.LC58:
	ASCII(.ascii	"Disable seg bypass.\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"Enable seg bypass.\012\000" )
.LC60:
	ASCII(.ascii	"unmask vfmw mmu err int!\012\000" )
	.space	2
.LC61:
	ASCII(.ascii	"mask vfmw mmu err int!\012\000" )
.LC62:
	ASCII(.ascii	"Disable SedOnly Func\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"Enable SedOnly Func\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"The channel number is to Large.\012\000" )
	.space	3
.LC65:
	ASCII(.ascii	"ChanID out of range\000" )
.LC66:
	ASCII(.ascii	"Force vdm %d sleep.\012\000" )
	.space	3
.LC67:
	ASCII(.ascii	"Vfmw suspend totally take %d ms\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"Wait sleep time out %d ms (isScdSleep=%d, isVdmSlee" )
	ASCII(.ascii	"p=%d)!\012\000" )
	.space	1
.LC69:
	ASCII(.ascii	"Force scd %d sleep.\012\000" )
	.space	3
.LC70:
	ASCII(.ascii	"proc cmd need no param:%p\012\000" )
	.space	1
.LC71:
	ASCII(.ascii	"Vfmw resume totally take %d ms\012\000" )
.LC72:
	ASCII(.ascii	"%s,%d,pos(%d) error!\012\000" )
	.space	2
.LC73:
	ASCII(.ascii	"%s, %d, pos(%d) error!\012\000" )
.LC74:
	ASCII(.ascii	"can NOT config a not-opened Chan\000" )
	.space	3
.LC75:
	ASCII(.ascii	"event_report null!\000" )
	.space	1
.LC76:
	ASCII(.ascii	"%s Unkown Adapter Type: %d\012\000" )
.LC77:
	ASCII(.ascii	"pstStreamParam is NULL\000" )
	.space	1
.LC78:
	ASCII(.ascii	"ChanID invalid\000" )
	.space	1
.LC79:
	ASCII(.ascii	"L: %d, Stream Interface Error!!, ChanID: %d\012\000" )
	.space	3
.LC80:
	ASCII(.ascii	"This Chan has not been created!!!\000" )
	.space	2
.LC81:
	ASCII(.ascii	"can NOT get a not-opened Chan's information of bits" )
	ASCII(.ascii	"tream\000" )
	.space	3
.LC82:
	ASCII(.ascii	"Raw FreshNum=%d, FreshSize=%d\012\000" )
	.space	1
.LC83:
	ASCII(.ascii	"Seg FreshNum=%d, FreshSize=%d\012\000" )
	.space	1
.LC84:
	ASCII(.ascii	"pArgs is null\000" )
	.space	2
.LC85:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC86:
	ASCII(.ascii	"no mem to arrange for soft dec\012\000" )
.LC87:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC88:
	ASCII(.ascii	"%s: L%d : vdm chan memory is too small to support u" )
	ASCII(.ascii	"ser decoder\012\000" )
.LC89:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC90:
	ASCII(.ascii	"parameter err, null pointer!!!\000" )
	.space	1
.LC91:
	ASCII(.ascii	"%s FATAL: pstChan = NULL!\012\000" )
	.space	1
.LC92:
	ASCII(.ascii	"%s FATAL: pChanMem_vdh = NULL!\012\000" )
.LC93:
	ASCII(.ascii	"%s FATAL: pChanMem_frm = NULL!\012\000" )
.LC94:
	ASCII(.ascii	"DelAllFrameMemRecord err in VCTRL_FreeChanResource " )
	ASCII(.ascii	"!\012\000" )
	.space	2
.LC95:
	ASCII(.ascii	"%s FATAL: pChanMem_scd = NULL!\012\000" )
.LC96:
	ASCII(.ascii	"%s FATAL: pChanMem_ctx = NULL!\012\000" )
.LC97:
	ASCII(.ascii	"pstCfg is null\000" )
	.space	1
.LC98:
	ASCII(.ascii	"Chip not support beyond %dx%d when Std != H264/VP8/" )
	ASCII(.ascii	"MVC/USER.\012\000" )
	.space	2
.LC99:
	ASCII(.ascii	"ChanID out of range!\000" )
	.space	3
.LC100:
	ASCII(.ascii	"s_pstVfmwChan = NULL\000" )
	.space	3
.LC101:
	ASCII(.ascii	"%s,%d,s_pstVfmwChan[chanID]->FspInst.stDecFsRec[i]." )
	ASCII(.ascii	"PhyFS.PhyAddr = 0x%x\012\000" )
	.space	3
.LC102:
	ASCII(.ascii	"%s,%d,can't find special frame match DecFs Num = %d" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC103:
	ASCII(.ascii	"pImage is NULL\000" )
	.space	1
.LC104:
	ASCII(.ascii	"vdm_ctrl.c,L%d: Chan inactive\012\000" )
	.space	1
.LC105:
	ASCII(.ascii	"This channel %d is not opened!\012\000" )
.LC106:
	ASCII(.ascii	"%s cannot output!\012\000" )
	.space	1
.LC107:
	ASCII(.ascii	"%s: view_0 id(%d) > view_1 id(%d), error!\012\000" )
	.space	1
.LC108:
	ASCII(.ascii	"%s: continuous view0 id(%d)!\012\000" )
	.space	2
.LC109:
	ASCII(.ascii	"%s: continuous view1 id(%d)!\012\000" )
	.space	2
.LC110:
	ASCII(.ascii	"This channel is not opened\000" )
	.space	1
.LC111:
	ASCII(.ascii	"vdm_ctrl.c,L%d: This channel is not opened\012\000" )
.LC112:
	ASCII(.ascii	"vdm_ctrl.c,L%d: VCTRL_TryToRelSpecialFrm success!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC113:
	ASCII(.ascii	"%s call SYNTAX_ReleaseImage failed\012\000" )
.LC114:
	ASCII(.ascii	"vfmw_ctrl.c, line %d: ChanID out of range\012\000" )
	.space	1
.LC115:
	ASCII(.ascii	"vfmw_ctrl.c, line %d: Chan %d is not open or not ru" )
	ASCII(.ascii	"nning\012\000" )
	.space	2
.LC116:
	ASCII(.ascii	"pstHDRInput = null\000" )
	.space	1
.LC117:
	ASCII(.ascii	"%s VidStd=%d Error!\012\000" )
	.space	3
.LC118:
	ASCII(.ascii	"Get DecParam Type Failure!\012\000" )
.LC119:
	ASCII(.ascii	"ChanId invalid!\000" )
.LC120:
	ASCII(.ascii	"ChanId out of range\000" )
.LC121:
	ASCII(.ascii	"This channel is not running\000" )
.LC122:
	ASCII(.ascii	"chan not create\000" )
.LC123:
	ASCII(.ascii	"can NOT start a not-opened Chan\000" )
.LC124:
	ASCII(.ascii	"NULL == pArgs\000" )
	.space	2
.LC125:
	ASCII(.ascii	"%s param invalid!\012\000" )
	.space	1
.LC126:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err!\012\000" )
	.space	1
.LC127:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame but VFMW_USER != s_pstVfmwChan" )
	ASCII(.ascii	"[ChanID]->eVidStd!\012\000" )
	.space	1
.LC128:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame but s_pstVfmwChan[ChanID]->s32" )
	ASCII(.ascii	"UsrdecFrameNum < MIN_USERDEC_FRAME_NUM!\012\000" )
.LC129:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC130:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC131:
	ASCII(.ascii	"line: %d, pLf is NULL!\012\000" )
.LC132:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC133:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame get LogicFs fail!\012\000" )
.LC134:
	ASCII(.ascii	"CAP_LEVEL_USER_DEFINE_WITH_OPTION option is illegal" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC135:
	ASCII(.ascii	"VCTRL_GetChanMemSizeByOption L%d: arrange return fa" )
	ASCII(.ascii	"ilure\012\000" )
	.space	2
.LC136:
	ASCII(.ascii	"ERROR: s32MaxRefFrameNum(%d), extra_ref(%d), s32Dis" )
	ASCII(.ascii	"playFrameNum(%d), extra_disp(%d)\012\000" )
	.space	3
.LC137:
	ASCII(.ascii	"MEM_MapRegisterAddr reg 0x%x failed!\012\000" )
	.space	2
.LC138:
	ASCII(.ascii	"VDMHAL_GetHalMemSize Vdh %d failed!\012\000" )
	.space	3
.LC139:
	ASCII(.ascii	"MEM_AllocMemBlock Vdh %d failed!\012\000" )
	.space	2
.LC140:
	ASCII(.ascii	"VDMHAL_OpenHAL Vdh %d failed!\012\000" )
	.space	1
.LC141:
	ASCII(.ascii	"MEM_AllocMemBlock VFMW_VP9Prob %d failed!\012\000" )
	.space	1
.LC142:
	ASCII(.ascii	"MEM_AllocMemBlock Scd %d failed!\012\000" )
	.space	2
.LC143:
	ASCII(.ascii	"SM_OpenSCDDrv Scd %d failed!\012\000" )
	.space	2
.LC144:
	ASCII(.ascii	"Register irq %d failed!\012\000" )
	.space	3
.LC145:
	ASCII(.ascii	"HEVCDEC_AllocHevcGlbMem Error!\012\000" )
.LC146:
	ASCII(.ascii	"pArgs = NULL\000" )
	.space	3
.LC147:
	ASCII(.ascii	"extra_ref=\000" )
	.space	1
.LC148:
	ASCII(.ascii	"=\000" )
	.space	2
.LC149:
	ASCII(.ascii	" \000" )
	.space	2
.LC150:
	ASCII(.ascii	"fuction return value is null,%s %d unknow error!!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC151:
	ASCII(.ascii	"ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC152:
	ASCII(.ascii	"extra_disp=\000" )
.LC153:
	ASCII(.ascii	"ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC154:
	ASCII(.ascii	"extra_cmd=\000" )
	.space	1
.LC155:
	ASCII(.ascii	"HI_VFMW_VideoDecode\000" )
.LC156:
	ASCII(.ascii	"(safe,warn,danger) :amount = %d,%d,%d,%d\012\000" )
	.space	2
.LC157:
	ASCII(.ascii	"strm_ctrl: I->IPB\012\000" )
	.space	1
.LC158:
	ASCII(.ascii	"strm_ctrl: IPB->I\012\000" )
	.space	1
.LC159:
	ASCII(.ascii	"(CurrMode,NextMode) = %d,%d\012\000" )
	.space	3
.LC160:
	ASCII(.ascii	"pic_pts: %lld\012\000" )
	.space	1
.LC161:
	ASCII(.ascii	"pic_usertag: %lld\012\000" )
	.space	1
.LC162:
	ASCII(.ascii	"pic_pts: %lld pic_usertag = %lld\012\000" )
	.space	2
.LC163:
	ASCII(.ascii	"Syntax is stopped from This channel\000" )
.LC164:
	ASCII(.ascii	"[%d] vdm busy\012\000" )
	.space	1
.LC165:
	ASCII(.ascii	"[%d] no frame\012\000" )
	.space	1
.LC166:
	ASCII(.ascii	"DFS, Wait Partition\012\000" )
	.space	3
.LC167:
	ASCII(.ascii	"DFS, Partition fail, u32DynamicFrameStoreAllocEn: %" )
	ASCII(.ascii	"d, eFspPartitionState: %d\012\000" )
	.space	2
.LC168:
	ASCII(.ascii	"[%d] no stream\012\000" )
.LC169:
	ASCII(.ascii	"seg_pts: %lld, seg_usertag = %lld\012\000" )
	.space	1
.LC170:
	ASCII(.ascii	"Thread running...\012\000" )
	.space	1
.LC171:
	ASCII(.ascii	"Thread stopped!\012\000" )
	.space	3
.LC172:
	ASCII(.ascii	"thread running...\012\000" )
	.space	1
.LC173:
	ASCII(.ascii	"thread stopped...\012\000" )
	.space	1
.LC174:
	ASCII(.ascii	"Thread killed!\012\000" )
.LC175:
	ASCII(.ascii	"ERROR:ReadNum = %d larger than VFMW_MAX_RESERVE_NUM" )
	ASCII(.ascii	"(%d)\012\000" )
	.space	3
.LC176:
	ASCII(.ascii	"The array of occupied frames is overflow, s_pstVfmw" )
	ASCII(.ascii	"Chan[%d]->specialFrameNum = %d\000" )
	.space	2
.LC177:
	ASCII(.ascii	"pSpecialFrmInfo = null!!!\000" )
	.space	2
.LC178:
	ASCII(.ascii	"pRefImgNum  = null\000" )
	.space	1
.LC179:
	ASCII(.ascii	"pReadImgNum = null\000" )
	.space	1
.LC180:
	ASCII(.ascii	"pNewImgNum  = null\000" )
	.space	1
.LC181:
	ASCII(.ascii	"%s not support std %d\012\000" )
	.space	1
.LC182:
	ASCII(.ascii	"pstChanState = NULL\000" )
.LC183:
	ASCII(.ascii	"SetVdecExtra ERROR: extra_ref = %d is out of [ -500" )
	ASCII(.ascii	"0, 5000 ]!\012\000" )
	.space	1
.LC184:
	ASCII(.ascii	"SetVdecExtra ERROR: extra_disp = %d is out of [ -50" )
	ASCII(.ascii	"00, 5000 ]!\012\000" )
.LC185:
	ASCII(.ascii	"Command \"%d\" not registerd!\012\000" )
	.space	3
.LC186:
	ASCII(.ascii	"Chan %d Report Last Frame, Value=%d, LastFrameState" )
	ASCII(.ascii	"=%d\012\000" )
.LC187:
	ASCII(.ascii	"Last frame output failed!\012\000" )
	.space	1
.LC188:
	ASCII(.ascii	"Last frame output successed!\012\000" )
	.space	2
.LC189:
	ASCII(.ascii	"Last frame already output, image id: %d!\012\000" )
	.space	2
.LC190:
	ASCII(.ascii	"line %d can not know YuvFormat = %d\012\000" )
	.space	3
.LC191:
	ASCII(.ascii	"userdec frame(phy=%#x) address error!\012\000" )
	.space	1
.LC192:
	ASCII(.ascii	"can not map vir addr for usrdat frame(cbphy=%#x)\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC193:
	ASCII(.ascii	"line: %d, pLogic is Null!\012\000" )
	.space	1
.LC194:
	ASCII(.ascii	"eYuvFormat %d is not support!!\012\000" )
.LC195:
	ASCII(.ascii	"pUsrdecFrame == NULL\000" )
	.space	3
.LC196:
	ASCII(.ascii	"VCTRL_PutUsrdecFrame: VidStd is %d\012\000" )
.LC197:
	ASCII(.ascii	"VCTRL_PutUsrdecFrame return err\012\000" )
	.space	3
.LC198:
	ASCII(.ascii	"L:%d ChanID out of range\012\000" )
	.space	2
.LC199:
	ASCII(.ascii	"L:%d This Chan has not been created!!!\012\000" )
.LC200:
	ASCII(.ascii	"L:%d WARNING: vidio std not setted!\012\000" )
	.space	3
.LC201:
	ASCII(.ascii	"WARNING: vidio std not setted!\000" )
	.space	1
.LC202:
	ASCII(.ascii	"start chan %d: VCTRL_StartChan return %d\012\000" )
	.space	2
.LC203:
	ASCII(.ascii	"This Chan has not been created or has been destroye" )
	ASCII(.ascii	"d !\000" )
	.space	1
.LC204:
	ASCII(.ascii	"VCTRL_StopChanWithCheck fail!\012\000" )
	.space	1
.LC205:
	ASCII(.ascii	"vdm_ctrl.c,L%d: pOption->s32KeepBS error\012\000" )
	.space	2
.LC206:
	ASCII(.ascii	"---------------------------------------------------" )
	ASCII(.ascii	"----------------------\012\000" )
	.space	1
.LC207:
	ASCII(.ascii	"Param Invalid of PChanOption is NULL\012\000" )
	.space	2
.LC208:
	ASCII(.ascii	"line %d VCTRL_GetChanMemSize failed!\012\000" )
	.space	2
.LC209:
	ASCII(.ascii	"ChanID: %d is out of range!\012\000" )
	.space	3
.LC210:
	ASCII(.ascii	"vfmw have max(%d) channels opened, can NOT create m" )
	ASCII(.ascii	"ore channels\012\000" )
	.space	3
.LC211:
	ASCII(.ascii	"L: %d : part we can NOT alloc buffer for channel co" )
	ASCII(.ascii	"ntext\012\000" )
	.space	2
.LC212:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel context\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC213:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel vdh\012\000" )
	.space	2
.LC214:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel vdh, %#x <" )
	ASCII(.ascii	" %#x\012\000" )
	.space	3
.LC215:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel scd\012\000" )
	.space	2
.LC216:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for SCD\012\000" )
	.space	2
.LC217:
	ASCII(.ascii	"Chan:%d can NOT enable FSP instance\012\000" )
	.space	3
.LC218:
	ASCII(.ascii	"pstCfg = NULL\000" )
	.space	2
.LC219:
	ASCII(.ascii	"VCTRL_CheckChanWH return err.\012\000" )
	.space	1
.LC220:
	ASCII(.ascii	"VFMW didn't support std %d.\012\000" )
	.space	3
.LC221:
	ASCII(.ascii	"VCTRL_ConfigChan with same config paramater.\012\000" )
	.space	2
.LC222:
	ASCII(.ascii	"can NOT VCTRL_PartitionMemForStdUser\012\000" )
	.space	2
.LC223:
	ASCII(.ascii	"chan %d: new UvmosEnable = %d\012\000" )
	.space	1
.LC224:
	ASCII(.ascii	"chan %d: SetUvmosEnable failed!\012\000" )
	.space	3
.LC225:
	ASCII(.ascii	"chan %d: new StrmOFThr = %d\012\000" )
	.space	3
.LC226:
	ASCII(.ascii	"chan %d: new DecMode = %d\012\000" )
	.space	1
.LC227:
	ASCII(.ascii	"chan %d: GetChanCfg failed!\012\000" )
	.space	3
.LC228:
	ASCII(.ascii	"chan %d: new DecOrderOutput = %d\012\000" )
	.space	2
.LC229:
	ASCII(.ascii	"chan %d: new ChanErrThr = %d\012\000" )
	.space	2
.LC230:
	ASCII(.ascii	"reset chan %d: VCTRL_ResetChan return %d\012\000" )
	.space	2
.LC231:
	ASCII(.ascii	"%s:L%d: %s\012\000" )
.LC232:
	ASCII(.ascii	"This Chan has not been created or has been destroye" )
	ASCII(.ascii	"d !!!\000" )
	.space	3
.LC233:
	ASCII(.ascii	"can NOT stop a not-opened Chan\000" )
	.space	1
.LC234:
	ASCII(.ascii	"stop chan %d: VCTRL_StopChan return %d\012\000" )
.LC235:
	ASCII(.ascii	"WARNNING: dsp in lowdelay state, we can not support" )
	ASCII(.ascii	"ed  avs in the same time!!!\012\000" )
.LC236:
	ASCII(.ascii	"WARNNING: dsp in avs state, we can not supported  l" )
	ASCII(.ascii	"owdelay in the same time!!!\012\000" )
.LC237:
	ASCII(.ascii	"%s, %d, actul size = 0x%x, except size= 0x%x\012\000" )
	.space	2
.LC238:
	ASCII(.ascii	"%s, %d, CfgFrameNum = %x, PmvNodeStatus= 0x%x\012\000" )
	.space	1
.LC239:
	ASCII(.ascii	"%s: Chan %d set single frame failed!\012\000" )
	.space	2
.LC240:
	ASCII(.ascii	"%s: Chan %d no frame buffer store!\012\000" )
.LC241:
	ASCII(.ascii	"DFS, request frame store fail!, chanid: %d\012\000" )
.LC242:
	ASCII(.ascii	"DFS, set decoding thread state to success!\012 \000" )
	.space	3
.LC243:
	ASCII(.ascii	"%s set chan %d ctrl state CHAN_FRAME_STORE_ALLOC fa" )
	ASCII(.ascii	"iled!\012\000" )
	.bss
	.align	3
.LANCHOR1 = . + 0
.LANCHOR3 = . + 8184
	.type	s_pstVfmwChan, %object
	.size	s_pstVfmwChan, 128
s_pstVfmwChan:
	.space	128
	.type	s_VfmwCTrl, %object
	.size	s_VfmwCTrl, 264
s_VfmwCTrl:
	.space	264
	.type	g_StandardObedience, %object
	.size	g_StandardObedience, 4
g_StandardObedience:
	.space	4
	.type	g_VfmwCompressPara, %object
	.size	g_VfmwCompressPara, 512
g_VfmwCompressPara:
	.space	512
	.type	g_StopDec, %object
	.size	g_StopDec, 4
g_StopDec:
	.space	4
	.type	g_SleepTime, %object
	.size	g_SleepTime, 4
g_SleepTime:
	.space	4
	.type	vfmw_save_el_file, %object
	.size	vfmw_save_el_file, 128
vfmw_save_el_file:
	.space	128
	.type	save_file_cnt.55186, %object
	.size	save_file_cnt.55186, 4
save_file_cnt.55186:
	.space	4
	.type	save_el_chan_num, %object
	.size	save_el_chan_num, 4
save_el_chan_num:
	.space	4
	.type	g_CurProcChan, %object
	.size	g_CurProcChan, 4
g_CurProcChan:
	.space	4
	.type	g_ResetCreateNewSave, %object
	.size	g_ResetCreateNewSave, 4
g_ResetCreateNewSave:
	.space	4
	.type	vfmw_save_metadata_reorder_file, %object
	.size	vfmw_save_metadata_reorder_file, 128
vfmw_save_metadata_reorder_file:
	.space	128
	.type	save_file_cnt.55180, %object
	.size	save_file_cnt.55180, 4
save_file_cnt.55180:
	.space	4
	.type	save_metadata_reorder_chan_num, %object
	.size	save_metadata_reorder_chan_num, 4
save_metadata_reorder_chan_num:
	.space	4
	.type	vfmw_save_metadata_file, %object
	.size	vfmw_save_metadata_file, 128
vfmw_save_metadata_file:
	.space	128
	.type	save_file_cnt.55174, %object
	.size	save_file_cnt.55174, 4
save_file_cnt.55174:
	.space	4
	.type	save_metadata_chan_num, %object
	.size	save_metadata_chan_num, 4
save_metadata_chan_num:
	.space	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 128
vfmw_save_seg_file:
	.space	128
	.type	save_file_cnt.55152, %object
	.size	save_file_cnt.55152, 4
save_file_cnt.55152:
	.space	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.space	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 128
vfmw_save_str_file:
	.space	128
	.type	save_file_cnt.55146, %object
	.size	save_file_cnt.55146, 4
save_file_cnt.55146:
	.space	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.space	4
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 128
vfmw_save_yuv_file:
	.space	128
	.type	save_file_cnt.55159, %object
	.size	save_file_cnt.55159, 4
save_file_cnt.55159:
	.space	4
	.type	MemRecord_YUV, %object
	.size	MemRecord_YUV, 24
MemRecord_YUV:
	.space	24
	.type	pVl, %object
	.size	pVl, 4
pVl:
	.space	4
	.type	pUl, %object
	.size	pUl, 4
pUl:
	.space	4
	.type	pY, %object
	.size	pY, 4
pY:
	.space	4
	.type	pVl_2bit, %object
	.size	pVl_2bit, 4
pVl_2bit:
	.space	4
	.type	pUl_2bit, %object
	.size	pUl_2bit, 4
pUl_2bit:
	.space	4
	.type	pY_2bit, %object
	.size	pY_2bit, 4
pY_2bit:
	.space	4
	.type	save_yuv_with_crop, %object
	.size	save_yuv_with_crop, 4
save_yuv_with_crop:
	.space	4
	.type	pPixelArray, %object
	.size	pPixelArray, 4
pPixelArray:
	.space	4
	.type	g_IsrFlag, %object
	.size	g_IsrFlag, 1
g_IsrFlag:
	.space	1
	.space	3
	.type	s_StreamIntf, %object
	.size	s_StreamIntf, 384
s_StreamIntf:
	.space	384
	.type	FspInstInfo.54260, %object
	.size	FspInstInfo.54260, 2824
FspInstInfo.54260:
	.space	2824
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.space	4
	.type	last_rec_pos_time.54597, %object
	.size	last_rec_pos_time.54597, 128
last_rec_pos_time.54597:
	.space	128
	.type	last_rec_pos_time.54608, %object
	.size	last_rec_pos_time.54608, 128
last_rec_pos_time.54608:
	.space	128
	.type	MemArrange.54861, %object
	.size	MemArrange.54861, 1232
MemArrange.54861:
	.space	1232
	.type	extra_ref, %object
	.size	extra_ref, 4
extra_ref:
	.space	4
	.type	extra_disp, %object
	.size	extra_disp, 4
extra_disp:
	.space	4
	.type	g_VfmwIrqHandle, %object
	.size	g_VfmwIrqHandle, 4
g_VfmwIrqHandle:
	.space	4
	.type	cmdline, %object
	.size	cmdline, 1024
cmdline:
	.space	1024
	.type	extra_cmd, %object
	.size	extra_cmd, 4
extra_cmd:
	.space	4
	.type	g_allow_B_before_P, %object
	.size	g_allow_B_before_P, 1
g_allow_B_before_P:
	.space	1
	.type	g_not_allow_H264FullPictureRepair_flag, %object
	.size	g_not_allow_H264FullPictureRepair_flag, 1
g_not_allow_H264FullPictureRepair_flag:
	.space	1
	.type	g_apple_airplay_mirrorinig_flag, %object
	.size	g_apple_airplay_mirrorinig_flag, 1
g_apple_airplay_mirrorinig_flag:
	.space	1
	.space	1
	.type	g_event_report, %object
	.size	g_event_report, 4
g_event_report:
	.space	4
	.type	g_DSPState, %object
	.size	g_DSPState, 128
g_DSPState:
	.space	128
	.type	last_rec_pos_time.54979, %object
	.size	last_rec_pos_time.54979, 128
last_rec_pos_time.54979:
	.space	128
	.type	last_rec_pos_decparam_time.54980, %object
	.size	last_rec_pos_decparam_time.54980, 128
last_rec_pos_decparam_time.54980:
	.space	128
	.type	ChanPriTab.54929, %object
	.size	ChanPriTab.54929, 128
ChanPriTab.54929:
	.space	128
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 768
g_VfmwChanStat:
	.space	768
	.type	PrioArray.54393, %object
	.size	PrioArray.54393, 128
PrioArray.54393:
	.space	128
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 128
s_ChanControlState:
	.space	128
	.type	Capability.54457, %object
	.size	Capability.54457, 148
Capability.54457:
	.space	148
	.type	PrioArray.54456, %object
	.size	PrioArray.54456, 128
PrioArray.54456:
	.space	128
	.type	g_EsBufValidFlag, %object
	.size	g_EsBufValidFlag, 128
g_EsBufValidFlag:
	.space	128
	.type	g_eVdmVersion, %object
	.size	g_eVdmVersion, 4
g_eVdmVersion:
	.space	4
	.type	g_VfmwGlobalStat, %object
	.size	g_VfmwGlobalStat, 60
g_VfmwGlobalStat:
	.space	60
	.type	AcceleratorCharacter, %object
	.size	AcceleratorCharacter, 4
AcceleratorCharacter:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
