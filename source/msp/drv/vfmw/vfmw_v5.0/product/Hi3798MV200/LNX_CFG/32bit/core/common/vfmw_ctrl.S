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
	addne	r3, r0, #471040
	movne	r0, #0
	strne	r1, [r3, #1252]
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
	addne	r0, r0, #471040
	ldrne	r0, [r0, #1252]
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
	movweq	r3, #46512
	movwne	r3, #63768
	movteq	r3, 180
	movtne	r3, 14
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #31
	mov	r4, r0
	bhi	.L690
	ldr	r5, .L695
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L691
	add	r3, r0, #475136
	ldr	ip, [r3, #1272]
	cmp	ip, #0
	beq	.L659
	ldr	r3, [r3, #748]
	cmp	r1, r3
	movne	r2, #0
	bne	.L662
	b	.L692
.L665:
	add	r3, r3, #748
	ldr	r3, [r0, r3]
	cmp	r1, r3
	beq	.L660
.L662:
	add	r2, r2, #1
	cmp	r2, ip
	mov	r3, r2, asl #4
	mov	r6, r2
	add	r3, r3, #475136
	bne	.L665
.L659:
	mvn	r0, #0
.L683:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L692:
	mov	r6, #0
.L660:
	add	r3, r0, #462848
	ldr	r3, [r3, #3536]
	cmp	r3, r1
	movwne	r3, #7720
	movne	r7, #1
	movtne	r3, 7
	addne	r3, r0, r3
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
	sub	r8, ip, #1
	ldr	r3, [r9, #12]
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	mov	r1, #88
	movw	r2, #7624
	movt	r2, 7
	mov	r0, #3
	mla	r7, r1, r7, r3
	movw	r3, #10440
	movt	r3, 7
	mov	r1, #0
	add	r2, r7, r2
	add	r3, r7, r3
	ldr	r7, [r9, #16]
	strb	r1, [r2, #2]
	strb	r1, [r3, #2]
	blx	r7
	cmp	r8, r6
	bls	.L675
	mov	r7, r6, asl #4
.L668:
	add	r6, r6, #1
	add	r0, r7, #475136
	ldr	r1, [r5, r4, asl #2]
	add	r0, r0, #744
	mov	r7, r6, asl #4
	ldr	r10, [r9, #52]
	add	r3, r7, #475136
	add	r0, r1, r0
	add	r3, r3, #744
	mov	r2, #16
	add	r1, r1, r3
	blx	r10
	cmp	r8, r6
	bhi	.L668
.L667:
	mov	ip, r8, asl #4
	ldr	r0, [r5, r4, asl #2]
	add	ip, ip, #475136
	ldr	r3, [r9, #48]
	add	ip, ip, #744
	mov	r2, #16
	add	r0, r0, ip
	mov	r1, #0
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	mov	r0, #0
	add	r3, r3, #475136
	ldr	r2, [r3, #1272]
	sub	r2, r2, #1
	str	r2, [r3, #1272]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L694:
	add	r0, r0, #442368
	movw	r6, #2107
	movw	r3, #3295
	ldr	r2, .L695+8
	ldrsb	ip, [r0, r6]
	mov	r0, #1
	ldr	r1, .L695+12
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r5, r4, asl #2]
	add	r3, ip, #442368
	ldrsb	r3, [r3, r6]
	cmp	r3, #0
	movgt	r6, #0
	ble	.L659
.L671:
	mov	r2, #88
	movw	r3, #3298
	mla	ip, r2, r6, ip
	mov	r0, #1
	ldr	r2, .L695+8
	add	r6, r6, r0
	ldr	r1, .L695+16
	add	ip, ip, #462848
	ldr	ip, [ip, #3536]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r5, r4, asl #2]
	movw	r3, #51259
	movt	r3, 6
	add	r3, ip, r3
	ldrsb	r3, [r3]
	cmp	r3, r6
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
	mov	r8, r6
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
	add	r0, r6, #475136
	mov	r1, r4
	add	r0, r0, #1344
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
	add	r3, r3, #491520
	ldrb	r3, [r3, #780]	@ zero_extendqisi2
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
	ldr	r0, [r7, r5, asl #2]
	sub	r1, fp, #676
	add	r0, r0, #475136
	add	r0, r0, #1344
	bl	SYNTAX_ReceiveImage
	cmp	r0, #1
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
	mov	r6, r0
	add	r0, r3, #475136
	add	r0, r0, #1344
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
	ldr	r0, [r7, r5, asl #2]
	bgt	.L740
	cmp	r3, #0
	bne	.L712
	add	r0, r0, #475136
	mvn	r6, #0
	add	r0, r0, #1344
	mvn	r9, #1
	bl	SYNTAX_ReturnImage
	ldr	r0, [r7, r5, asl #2]
	mov	r1, r4
	add	r0, r0, #475136
	add	r0, r0, #1344
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r4, #184]
	ldr	r2, .L742+24
	mov	r0, #1
	ldr	r1, .L742+48
	bl	dprint_vfmw
	b	.L714
.L712:
	add	r0, r0, #475136
	mov	r1, r4
	add	r0, r0, #1344
	ldr	r6, .L742
	bl	SYNTAX_ReleaseImage
	ldr	r3, [fp, #-496]
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
	add	r0, r0, #475136
	mvn	r6, #0
	add	r0, r0, #1344
	mvn	r9, #1
	bl	SYNTAX_ReturnImage
	ldr	r0, [r7, r5, asl #2]
	mov	r1, r4
	add	r0, r0, #475136
	add	r0, r0, #1344
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
	ldr	r0, [r6, r5, asl #2]
	sub	r1, fp, #676
	mvn	r6, #0
	mvn	r9, #1
	add	r0, r0, #475136
	add	r0, r0, #1344
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r4, #184]
	ldr	r2, .L742+24
	mov	r0, #1
	ldr	r1, .L742+52
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
	ldr	r0, [r6, r4, asl #2]
	mov	r1, r5
	add	r0, r0, #475136
	add	r0, r0, #1344
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r5, #188]
	cmn	r3, #1
	mov	r8, r0
	beq	.L753
	ldr	r0, [r6, r4, asl #2]
	sub	r1, fp, #676
	str	r3, [fp, #-528]
	add	r0, r0, #475136
	add	r0, r0, #1344
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
	add	r3, r5, #475136
	ldr	r4, [r3, #1356]
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
	add	r3, r5, #475136
	ldr	r4, [r3, #1580]
	b	.L809
.L798:
	add	r3, r5, #475136
	ldr	r4, [r3, #2388]
	b	.L809
.L807:
	add	r3, r5, #475136
	ldr	r4, [r3, #3776]
	b	.L809
.L795:
	add	r3, r5, #475136
	ldr	r4, [r3, #1712]
	b	.L809
.L801:
	add	r3, r5, #475136
	ldr	r4, [r3, #1368]
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r1, #0
	beq	.L826
	cmp	r0, #0
	beq	.L821
	cmp	r0, #16
	bne	.L827
	add	r0, r4, #4096
	ldrb	r0, [r0, #1084]	@ zero_extendqisi2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L827:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L821:
	ldrb	r0, [r4, #1184]	@ zero_extendqisi2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L826:
	ldr	r1, .L828
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L829:
	.align	2
.L828:
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
	bhi	.L847
	ldr	r3, .L848
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #568]
	cmp	r2, #17
	ldrls	pc, [pc, r2, asl #2]
	b	.L830
.L834:
	.word	.L833
	.word	.L843
	.word	.L836
	.word	.L843
	.word	.L830
	.word	.L843
	.word	.L839
	.word	.L830
	.word	.L843
	.word	.L843
	.word	.L843
	.word	.L843
	.word	.L843
	.word	.L843
	.word	.L830
	.word	.L844
	.word	.L845
	.word	.L843
.L844:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1580]
.L830:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L843:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1356]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L847:
	ldr	ip, .L848+4
	movw	r3, #4161
	ldr	r2, .L848+8
	mov	r0, #0
	ldr	r1, .L848+12
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L839:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1368]
	b	.L830
.L833:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1712]
	b	.L830
.L845:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #3776]
	b	.L830
.L836:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #2388]
	b	.L830
.L849:
	.align	2
.L848:
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
	ldrhi	ip, .L862
	movwhi	r3, #4239
	bhi	.L860
	ldr	r5, .L862+4
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L861
	ldr	r3, [r3, #8]
	cmp	r3, #1
	beq	.L854
	ldr	ip, .L862+8
	movw	r3, #4241
.L860:
	ldr	r2, .L862+12
	mov	r0, #0
	ldr	r1, .L862+16
	str	ip, [sp]
	bl	dprint_vfmw
.L850:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L854:
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L850
	ldr	r2, [r5, r4, asl #2]
	ldr	r3, [r2, #568]
	cmp	r3, #0
	beq	.L855
	cmp	r3, #16
	bne	.L850
	movw	r0, #17736
	mov	r1, r6
	movt	r0, 7
	add	r0, r2, r0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	HEVCDEC_VDMProcSedOnly
.L855:
	movw	r0, #17736
	mov	r1, r6
	movt	r0, 7
	add	r0, r2, r0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	H264DEC_VDMProcSedOnly
.L861:
	ldr	ip, .L862+20
	mov	r0, r3
	ldr	r2, .L862+12
	movw	r3, #4240
	ldr	r1, .L862+16
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L850
.L863:
	.align	2
.L862:
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
	ldrhi	ip, .L891
	movwhi	r3, #4274
	bhi	.L887
	ldr	r3, .L891+4
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L888
	ldr	r0, [r3, #8]
	cmp	r0, #1
	bne	.L889
	ldr	r2, [r3, #568]
	cmp	r2, #17
	ldrls	pc, [pc, r2, asl #2]
	b	.L883
.L870:
	.word	.L869
	.word	.L871
	.word	.L872
	.word	.L873
	.word	.L883
	.word	.L874
	.word	.L875
	.word	.L883
	.word	.L876
	.word	.L877
	.word	.L878
	.word	.L878
	.word	.L878
	.word	.L879
	.word	.L883
	.word	.L880
	.word	.L881
	.word	.L882
.L882:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_GetImageBuffer
.L869:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_GetImageBuffer
.L871:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_GetImageBuffer
.L872:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_GetImageBuffer
.L873:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_GetImageBuffer
.L874:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_GetImageBuffer
.L875:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_GetImageBuffer
.L876:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_GetImageBuffer
.L877:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_GetImageBuffer
.L878:
	ldr	r2, .L891+8
	ldr	r2, [r2, #-3180]
	tst	r2, #1
	bne	.L890
.L866:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L879:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_GetImageBuffer
.L880:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_GetImageBuffer
.L881:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_GetImageBuffer
.L889:
	ldr	ip, .L891+12
	movw	r3, #4276
.L887:
	ldr	r2, .L891+16
	mov	r0, #0
	ldr	r1, .L891+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L866
.L883:
	mov	r0, #0
	b	.L866
.L890:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_GetImageBuffer
.L888:
	ldr	ip, .L891+24
	mov	r0, r3
	ldr	r2, .L891+16
	movw	r3, #4275
	ldr	r1, .L891+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L866
.L892:
	.align	2
.L891:
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
	ldrhi	ip, .L903
	movwhi	r3, #4390
	bhi	.L899
	ldr	r3, .L903+4
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	moveq	r0, r3
	ldreq	ip, .L903+8
	movweq	r3, #4391
	beq	.L900
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L901
	cmp	r1, #0
	ldrne	r2, [r1]
	movne	r0, #0
	strne	r2, [r3, #1196]
	beq	.L902
.L895:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L901:
	ldr	ip, .L903+12
	movw	r3, #4392
.L899:
	ldr	r2, .L903+16
	mov	r0, #0
	ldr	r1, .L903+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L895
.L902:
	ldr	ip, .L903+24
	mov	r0, r1
	movw	r3, #4393
.L900:
	ldr	r2, .L903+16
	ldr	r1, .L903+20
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
	ldrhi	ip, .L915
	movwhi	r3, #4403
	bhi	.L911
	ldr	r3, .L915+4
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldreq	ip, .L915+8
	movweq	r3, #4404
	beq	.L912
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L913
	cmp	r1, #0
	beq	.L914
	ldr	r3, .L915+12
	add	r0, r0, #1232
	mov	r2, #20
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
.L907:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L913:
	ldr	ip, .L915+16
	movw	r3, #4405
.L911:
	ldr	r2, .L915+20
	mov	r0, #0
	ldr	r1, .L915+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L907
.L914:
	ldr	ip, .L915+28
	mov	r0, r1
	movw	r3, #4406
.L912:
	ldr	r2, .L915+20
	ldr	r1, .L915+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L907
.L916:
	.align	2
.L915:
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
	bhi	.L924
	ldr	r3, .L925
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L923
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L923
	ldr	r2, [r3, #8]
	cmp	r2, #0
	beq	.L923
	ldr	r2, [r3, #20]
	cmp	r2, #0
	beq	.L923
	ldr	r0, [r3, #568]
	cmp	r0, #22
	movne	r0, #0
	mvneq	r0, #0
.L919:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L923:
	mvn	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L924:
	ldr	ip, .L925+4
	movw	r3, #4415
	ldr	r2, .L925+8
	mov	r0, #0
	ldr	r1, .L925+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L919
.L926:
	.align	2
.L925:
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
	beq	.L944
	ldr	r3, .L946
	mov	r1, r4
	ldr	r7, [r0, #352]
	mov	r2, #368
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r5, #8
	str	r7, [r5, #352]
	bl	ResetVoQueue
	ldr	r0, .L946+4
	mov	r1, r4
	str	r6, [r5]
	b	.L932
.L930:
	add	r1, r1, #1
	cmp	r1, #32
	beq	.L945
.L932:
	ldr	r2, [r0], #4
	movw	r3, #17736
	movt	r3, 7
	cmp	r2, #0
	add	r3, r2, r3
	beq	.L930
	cmp	r5, r3
	bne	.L930
	cmn	r1, #1
	str	r1, [r5, #360]
	beq	.L931
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L945:
	mvn	r3, #0
	str	r3, [r5, #360]
.L931:
	ldr	r1, .L946+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L944:
	ldr	r2, .L946+12
	mov	r0, #0
	ldr	r1, .L946+16
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L947:
	.align	2
.L946:
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
	beq	.L950
	mov	r2, #0
	ldr	r0, [r4, #360]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #360]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L951
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
.L951:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L950:
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
	ldr	r7, .L971
	mov	r6, r0
	mov	r5, r1
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L966
	ldr	r2, [r3, #568]
	cmp	r2, #20
	bne	.L967
	ldr	r3, [r3, #488]
	cmp	r3, #2
	ble	.L968
	mov	r1, #1
	bl	FSP_NewLogicFs
	subs	r8, r0, #0
	blt	.L969
	mov	r1, r8
	mov	r0, r6
	bl	FSP_GetLogicFs
	mov	r2, r8
	ldr	r1, .L971+4
	mov	r4, r0
	mov	r0, #18
	bl	dprint_vfmw
	cmp	r4, #0
	beq	.L970
	ldr	r2, [r4, #28]
	cmp	r2, #0
	beq	.L959
	ldr	r3, [r4, #32]
	cmp	r3, #0
	beq	.L959
	ldr	r2, [r2, #8]
	mov	r0, #18
	ldr	r3, [r3, #8]
	ldr	r1, .L971+8
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
.L954:
	mov	r0, r2
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L967:
	ldr	r1, .L971+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L954
.L968:
	ldr	r1, .L971+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L954
.L959:
	ldr	r1, .L971+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L954
.L969:
	ldr	r1, .L971+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L954
.L966:
	ldr	ip, .L971+28
	mov	r0, r3
	ldr	r2, .L971+32
	movw	r3, #4607
	ldr	r1, .L971+36
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L954
.L970:
	movw	r2, #4635
	ldr	r1, .L971+40
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r2, #0
	b	.L954
.L972:
	.align	2
.L971:
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
	ldr	r3, .L992
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L991
	ldr	r2, [r3, #568]
	cmp	r2, #20
	ldrls	pc, [pc, r2, asl #2]
	b	.L973
.L977:
	.word	.L976
	.word	.L978
	.word	.L979
	.word	.L980
	.word	.L973
	.word	.L981
	.word	.L982
	.word	.L973
	.word	.L983
	.word	.L984
	.word	.L985
	.word	.L985
	.word	.L985
	.word	.L986
	.word	.L973
	.word	.L987
	.word	.L988
	.word	.L989
	.word	.L973
	.word	.L973
	.word	.L990
.L990:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	USERDEC_Init
.L976:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_Init
.L978:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_Init
.L979:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_Init
.L980:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_Init
.L981:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_Init
.L982:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_Init
.L983:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_Init
.L984:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_Init
.L985:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_Init
.L986:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_Init
.L987:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_Init
.L988:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_Init
.L989:
	movw	r0, #17736
	add	r1, r3, #576
	movt	r0, 7
	add	r0, r3, r0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_Init
.L991:
	ldr	ip, .L992+4
	mov	r0, r3
	ldr	r2, .L992+8
	movw	r3, #4684
	ldr	r1, .L992+12
	str	ip, [sp]
	bl	dprint_vfmw
.L973:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L993:
	.align	2
.L992:
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
	blt	.L995
	ldr	r3, [r0, #12]
	cmp	r3, #31
	ble	.L995
	ldr	r3, [r0, #16]
	cmp	r3, #31
	ble	.L995
	ldr	r3, [r0, #56]
	cmp	r3, #262144
	blt	.L995
	ldr	r3, [r0, #44]
	cmp	r3, #1
	beq	.L1001
	cmp	r3, #2
	bne	.L999
	ldr	r3, [r0, #20]
	cmp	r3, #0
	ble	.L995
	ldr	r3, [r0, #24]
	cmp	r3, #0
	ble	.L995
.L1000:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	ble	.L995
	ldr	r3, [r0, #32]
	cmp	r3, #0
	bgt	.L999
.L995:
	ldr	r1, .L1002
	mov	r0, #32
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L999:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1001:
	ldr	r3, [r0, #20]
	cmp	r3, #0
	bgt	.L1000
	b	.L995
.L1003:
	.align	2
.L1002:
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
	beq	.L1006
	add	r0, r1, #1
	cmp	r0, #17
	movge	r0, #17
.L1006:
	ldr	r3, .L1019
	sub	r2, r6, #27
	cmp	r2, #6
	ldr	r2, [r4, #60]
	ldr	r7, [r3, #64]
	mvncc	ip, #1
	mvncs	ip, #0
	cmp	r7, #0
	beq	.L1010
	ldr	lr, .L1019+4
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
	bne	.L1010
	ldr	r3, .L1019+8
	cmp	r6, #26
	movwne	r1, #63768
	movweq	r1, #46512
	ldr	r2, [r3, #-2920]
	movtne	r1, 14
	movteq	r1, 180
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
	beq	.L1014
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
	beq	.L1015
	movw	r2, #57056
	movt	r2, 9
	cmp	r3, r2
	movcc	r3, r2
.L1014:
	mov	r0, #0
	add	r3, r3, r1
	str	r3, [r5, #8]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1010:
	movw	r2, #4839
	ldr	r1, .L1019+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1015:
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
	b	.L1014
.L1020:
	.align	2
.L1019:
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
	beq	.L1022
	ldr	r1, .L1030
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
	bmi	.L1029
.L1022:
	mov	r0, r4
	bl	VCTRL_VarifyOption
	cmp	r0, #0
	bne	.L1024
	mov	r2, r6
	mov	r1, r4
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_GetMemSize_onDecode
.L1029:
	stmia	sp, {ip, lr}
	mov	r0, #32
	ldr	r1, .L1030+4
	bl	dprint_vfmw
.L1024:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1031:
	.align	2
.L1030:
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
	beq	.L1033
	ldr	r5, [r0, #88]
	adds	r5, r5, #0
	movne	r5, #1
.L1033:
	ldr	r6, [r4, #16]
	ldr	r7, [r4, #8]
	cmp	r6, #0
	ldr	r8, [r4, #4]
	beq	.L1034
	ldr	r3, .L1097
	ldr	r3, [r3, #60]
	cmp	r3, #0
	beq	.L1086
	mov	r0, #0
	blx	r3
.L1039:
	cmp	r5, #0
	beq	.L1037
.L1038:
	ldr	r3, .L1097+4
	mov	r2, #24
	mov	r1, #0
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
.L1034:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	ldr	r6, [r4, #64]
	ldr	r7, [r4, #56]
	cmp	r6, #0
	ldr	r8, [r4, #52]
	beq	.L1040
	ldr	r3, .L1097
	ldr	r3, [r3, #60]
	cmp	r3, #0
	beq	.L1087
	mov	r0, #0
	blx	r3
.L1045:
	cmp	r5, #0
	beq	.L1043
.L1044:
	ldr	r3, .L1097+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #48
	ldr	r3, [r3, #48]
	blx	r3
.L1040:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	ldr	r6, [r4, #40]
	ldr	r7, [r4, #32]
	cmp	r6, #0
	ldr	r8, [r4, #28]
	bne	.L1088
.L1046:
	mov	r2, r6
	mov	r1, r8
	mov	r0, r7
	bl	MEM_DelMemRecord
	bl	SM_InstInit
	ldr	r5, [r4, #112]
	ldr	r6, [r4, #104]
	cmp	r5, #0
	ldr	r7, [r4, #100]
	bne	.L1089
.L1049:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #184]
	ldr	r6, [r4, #176]
	cmp	r5, #0
	ldr	r7, [r4, #172]
	bne	.L1090
.L1050:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #160]
	ldr	r6, [r4, #152]
	cmp	r5, #0
	ldr	r7, [r4, #148]
	bne	.L1091
.L1051:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #136]
	ldr	r6, [r4, #128]
	cmp	r5, #0
	ldr	r7, [r4, #124]
	bne	.L1092
.L1052:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #208]
	ldr	r6, [r4, #200]
	cmp	r5, #0
	ldr	r7, [r4, #196]
	bne	.L1093
.L1053:
	ldr	r4, .L1097+8
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r3, [r4, #376]
	cmp	r3, #1
	beq	.L1094
	ldr	r3, [r4, #380]
	ldr	r5, .L1097+8
	cmp	r3, #1
	beq	.L1095
.L1055:
	ldr	r3, [r4, #384]
	ldr	r4, .L1097+8
	cmp	r3, #1
	beq	.L1096
.L1056:
	bl	HEVCDEC_ReleaseHevcGlbMem
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1088:
	mov	r0, #0
	bl	SM_CloseSCDDrv
	cmp	r5, #0
	beq	.L1047
.L1048:
	ldr	r3, .L1097+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, r2
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1046
.L1089:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1097+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #96
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1049
.L1093:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1097+4
	add	r0, r4, #192
	mov	r2, #24
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1053
.L1092:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1097+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #120
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1052
.L1091:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1097+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #144
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1051
.L1090:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L1097+4
	mov	r2, #24
	mov	r1, #0
	add	r0, r4, #168
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1050
.L1086:
	mov	r0, r3
	movw	r2, #5178
	ldr	r1, .L1097+12
	bl	dprint_vfmw
	b	.L1039
.L1087:
	mov	r0, r3
	movw	r2, #5198
	ldr	r1, .L1097+12
	bl	dprint_vfmw
	b	.L1045
.L1096:
	ldr	r3, .L1097+4
	mov	r0, #13
	ldr	r5, [r3, #208]
	bl	VFMW_GetString
	ldr	r2, .L1097+16
	mov	r1, r0
	mov	r0, #181
	blx	r5
	mov	r3, #0
	str	r3, [r4, #384]
	b	.L1056
.L1043:
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #56]
	bl	MEM_ReleaseMemBlock
	b	.L1044
.L1037:
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_ReleaseMemBlock
	b	.L1038
.L1094:
	ldr	r3, .L1097+4
	mov	r0, #0
	ldr	r5, [r3, #208]
	bl	VFMW_GetString
	ldr	r2, .L1097+16
	mov	r1, r0
	mov	r0, #127
	blx	r5
	mov	r3, #0
	str	r3, [r4, #376]
	ldr	r3, [r4, #380]
	ldr	r5, .L1097+8
	cmp	r3, #1
	bne	.L1055
.L1095:
	ldr	r3, .L1097+4
	mov	r0, #4
	ldr	r6, [r3, #208]
	bl	VFMW_GetString
	ldr	r2, .L1097+16
	mov	r1, r0
	mov	r0, #136
	blx	r6
	mov	r3, #0
	str	r3, [r5, #380]
	b	.L1055
.L1047:
	ldr	r1, [r4, #28]
	ldr	r0, [r4, #32]
	bl	MEM_ReleaseMemBlock
	b	.L1048
.L1098:
	.align	2
.L1097:
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
	bne	.L1100
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
	beq	.L1137
	mov	r2, #53248
	ldr	r1, .L1142
	movt	r2, 63683
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r3, .L1142+4
	mov	r1, r6
	mov	r0, r5
.L1127:
	mov	r2, #24
.L1126:
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
.L1103:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1137:
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
	bne	.L1104
	ldr	r5, .L1142+4
	ldr	r2, [r4, #160]
	ldr	r1, [r4, #148]
	ldr	r0, [r4, #152]
	bl	MEM_AddMemRecord
	mov	r0, #15
	ldr	r7, [r5, #68]
	bl	VFMW_GetString
	ldr	r8, .L1142+8
	mov	r3, r6
	mov	r1, #20
	mov	r2, r0
	sub	r0, fp, #84
	blx	r7
	ldr	r3, [r8, #48]
	cmp	r3, #0
	beq	.L1106
	blx	r3
	subs	r2, r0, #0
	ble	.L1106
	str	r6, [sp]
	mov	r7, #3
	mov	r3, r4
	str	r7, [r4, #20]
	mov	r1, r6
	sub	r0, fp, #84
	bl	MEM_AllocMemBlock
	subs	r9, r0, #0
	bne	.L1107
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
	beq	.L1108
	sub	r0, fp, #64
	blx	r3
	subs	r8, r0, #0
	bne	.L1108
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
	bne	.L1109
	add	r3, r4, #24
	ldr	r1, [r4, #52]
	ldr	r2, [r4, #64]
	ldr	r0, [r4, #56]
	mov	r9, r3
	str	r3, [fp, #-92]
	bl	MEM_AddMemRecord
	ldr	r2, .L1142+12
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
	bne	.L1138
	ldr	r2, [r4, #40]
	ldr	r1, [r4, #28]
	ldr	r0, [r4, #32]
	bl	MEM_AddMemRecord
	mov	r2, #0
	ldr	r1, [r4, #40]
	ldr	r0, [r4, #32]
	bl	SM_OpenSCDDrv
	subs	r7, r0, #0
	bne	.L1112
	ldr	r6, .L1142+16
	bl	SM_InstInit
	mov	r0, r7
	ldr	r8, [r5, #204]
	ldr	r5, .L1142+20
	ldr	r9, [r6, #92]
	bl	VFMW_GetString
	ldr	r1, .L1142+24
	str	r5, [sp]
	mov	r2, r9
	ldr	r9, .L1142+4
	mov	r3, r0
	mov	r0, #127
	blx	r8
	subs	r3, r0, #0
	str	r3, [fp, #-96]
	bne	.L1139
	ldr	r2, [r6, #92]
	mov	r0, #4
	ldr	r7, .L1142+28
	mov	r8, #1
	ldr	r10, [r9, #204]
	str	r2, [fp, #-88]
	str	r8, [r7, #376]
	bl	VFMW_GetString
	str	r5, [sp]
	ldr	r2, [fp, #-88]
	ldr	r1, .L1142+32
	mov	r3, r0
	mov	r0, #136
	blx	r10
	subs	r3, r0, #0
	str	r3, [fp, #-88]
	bne	.L1140
	mov	r0, #13
	ldr	r10, [r6, #92]
	str	r8, [r7, #380]
	ldr	r6, [r9, #204]
	bl	VFMW_GetString
	str	r5, [sp]
	mov	r2, r10
	ldr	r1, .L1142+36
	mov	r3, r0
	mov	r0, #181
	blx	r6
	subs	r5, r0, #0
	bne	.L1141
	str	r8, [r7, #384]
	bl	HEVCDEC_AllocHevcGlbMem
	cmp	r0, #0
	beq	.L1103
	ldr	r1, .L1142+40
	mov	r0, r5
	bl	dprint_vfmw
	mov	r0, r5
	b	.L1103
.L1100:
	mov	r2, #0
	ldr	r1, .L1142
	movt	r2, 63683
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, .L1142+4
	mov	r0, r5
	mov	r2, #24
	mov	r1, #0
	b	.L1126
.L1106:
	mov	r2, #0
	ldr	r1, .L1142+44
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	mov	r0, r9
.L1128:
	mov	r2, #24
	mov	r1, #0
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1103
.L1104:
	mov	r2, #49152
	ldr	r1, .L1142
	movt	r2, 63683
	mov	r0, r7
	bl	dprint_vfmw
	ldr	r3, .L1142+4
	mov	r1, r7
	mov	r0, r9
	b	.L1127
.L1108:
	mov	r2, #0
	ldr	r1, .L1142+48
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	mov	r2, #24
	mov	r1, #0
.L1132:
	mov	r0, r4
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1103
.L1139:
	ldr	r1, .L1142+52
	mov	r2, #127
	mov	r0, r7
	bl	dprint_vfmw
	ldr	r3, [r9, #48]
	mov	r1, r7
.L1130:
	ldr	r0, [fp, #-92]
.L1133:
	mov	r2, #24
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L1103
.L1140:
	ldr	r1, .L1142+52
	mov	r2, #136
	ldr	r5, [fp, #-96]
.L1129:
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r3, [r9, #48]
	mov	r1, r5
	b	.L1130
.L1141:
	mov	r2, #181
	ldr	r1, .L1142+52
	ldr	r5, [fp, #-88]
	b	.L1129
.L1112:
	ldr	r1, .L1142+56
	mov	r2, #0
.L1131:
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	ldr	r0, [fp, #-92]
	b	.L1128
.L1138:
	mov	r2, #0
	ldr	r1, .L1142+60
	b	.L1131
.L1107:
	mov	r2, r6
	ldr	r1, .L1142+64
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	mov	r1, r6
	mov	r2, #24
	b	.L1132
.L1109:
	ldr	r1, .L1142+68
	mov	r2, r8
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r3, [r5, #48]
	mov	r1, r8
	mov	r0, r9
	b	.L1133
.L1143:
	.align	2
.L1142:
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
	beq	.L1176
	ldr	r4, .L1181
	mov	r2, #8
	ldr	r7, .L1181+4
	sub	r0, fp, #52
	mov	r1, #0
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r5, [r7, #128]
	cmp	r5, #0
	bne	.L1175
	mov	r1, #1024
	ldr	r3, [r4, #80]
	str	r5, [fp, #-56]
	ldr	r0, .L1181+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1181+12
	ldr	r0, .L1181+8
	blx	r3
	ldr	r6, .L1181+16
	cmp	r0, #0
	str	r0, [fp, #-56]
	beq	.L1148
	ldr	r3, [r4, #92]
	sub	r0, fp, #56
	ldr	r1, .L1181+20
	blx	r3
	cmp	r0, #0
	beq	.L1167
	sub	r0, fp, #56
	ldr	r3, [r4, #92]
	ldr	r1, .L1181+24
	blx	r3
	cmp	r0, #0
	beq	.L1177
	mov	r2, r5
	ldr	r3, [r4, #84]
	mov	r1, r5
	blx	r3
	mov	r2, r0
	str	r0, [r6, #-1688]
.L1152:
	add	r3, r2, #4992
	movw	r1, #10000
	add	r3, r3, #8
	movw	r9, #5000
	cmp	r3, r1
	bhi	.L1153
	cmp	r2, r9
	movw	r3, #60536
.L1174:
	movt	r3, 65535
	movge	r2, r9
	cmp	r2, r3
	movlt	r2, r3
.L1149:
	str	r2, [r6, #-1688]
.L1151:
	mov	r9, #0
	ldr	r3, [r4, #80]
	mov	r1, #1024
	str	r9, [fp, #-56]
	ldr	r0, .L1181+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1181+28
	ldr	r0, .L1181+8
	blx	r3
	ldr	r10, .L1181
	cmp	r0, r9
	str	r0, [fp, #-56]
	beq	.L1154
	ldr	r2, [r10, #92]
	sub	r0, fp, #56
	ldr	r1, .L1181+20
	blx	r2
	cmp	r0, r9
	beq	.L1155
	sub	r0, fp, #56
	ldr	r2, [r10, #92]
	ldr	r1, .L1181+24
	blx	r2
	cmp	r0, r9
	beq	.L1178
	ldr	r3, [r10, #84]
	mov	r2, r9
	mov	r1, r9
	blx	r3
	ldr	r3, .L1181+16
	mov	r2, r0
	str	r0, [r3, #-1684]
.L1158:
	add	r3, r2, #4992
	movw	r1, #10000
	add	r3, r3, #8
	movw	r9, #5000
	cmp	r3, r1
	bhi	.L1159
	cmp	r2, r9
	movw	r3, #60536
	movt	r3, 65535
	movlt	r5, r2
	movge	r5, r9
	cmp	r5, r3
	movlt	r5, r3
.L1155:
	str	r5, [r6, #-1684]
.L1157:
	ldr	r5, [r6, #-652]
	mov	r3, #0
	ldr	r9, .L1181+16
	cmp	r5, r3
	str	r3, [fp, #-56]
	beq	.L1160
	ldr	r2, .L1181+32
	and	r3, r5, #1
	ubfx	r1, r5, #1, #1
	strb	r3, [r9, #-648]
	ubfx	r3, r5, #2, #1
	ubfx	r5, r5, #3, #1
	strb	r1, [r2, #96]
	strb	r3, [r9, #-647]
	strb	r5, [r9, #-646]
.L1161:
	ldr	r5, .L1181+4
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
	ldr	r1, .L1181+36
	sub	r0, fp, #52
	mov	r2, #134217728
	mov	r3, #75497472
	str	r2, [fp, #-52]
	str	r1, [r6, #-644]
	str	r3, [fp, #-48]
	str	r9, [r7, #132]
	bl	MEM_InitMemManager
	bl	FSP_Init
	ldr	r6, .L1181
	bl	ChanCtx_Init
	ldr	r3, [r4, #48]
	mov	r2, #128
	mov	r1, #0
	ldr	r0, .L1181+40
	blx	r3
	ldr	r3, [r4, #52]
	add	r1, r8, #8
	mov	r2, #24
	add	r0, r5, #224
	blx	r3
	add	r0, r5, #152
	bl	OpenDrivers
	cmp	r0, #0
	bne	.L1175
	ldr	r3, [r6, #124]
	mov	r1, r9
	blx	r3
	ldr	r3, [r6, #200]
	ldr	r2, .L1181+44
	add	r0, r5, #140
	ldr	r1, .L1181+48
	blx	r3
	cmp	r0, #0
	streq	r9, [r5, #128]
	bne	.L1179
.L1146:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1160:
	ldr	r3, [r4, #80]
	mov	r1, #1024
	ldr	r0, .L1181+8
	blx	r3
	ldr	r3, [r4, #96]
	ldr	r1, .L1181+52
	ldr	r0, .L1181+8
	blx	r3
	ldr	r10, .L1181
	cmp	r0, #0
	str	r0, [fp, #-56]
	beq	.L1161
	ldr	r3, [r10, #92]
	sub	r0, fp, #56
	ldr	r1, .L1181+20
	blx	r3
	cmp	r0, #0
	ldreq	r0, [r9, #-652]
	beq	.L1163
	sub	r0, fp, #56
	ldr	r3, [r10, #92]
	ldr	r1, .L1181+24
	blx	r3
	cmp	r0, #0
	beq	.L1180
	ldr	r3, [r10, #84]
	mov	r2, r5
	mov	r1, r5
	blx	r3
	str	r0, [r9, #-652]
.L1163:
	ldr	r2, .L1181+32
	and	r3, r0, #1
	ubfx	r1, r0, #1, #1
	strb	r3, [r6, #-648]
	ubfx	r3, r0, #2, #1
	ubfx	r0, r0, #3, #1
	strb	r1, [r2, #96]
	strb	r3, [r6, #-647]
	strb	r0, [r6, #-646]
	b	.L1161
.L1154:
	ldr	r3, .L1181+16
	ldr	r2, [r3, #-1684]
	b	.L1158
.L1148:
	ldr	r2, [r6, #-1688]
	b	.L1152
.L1153:
	ldr	r1, .L1181+56
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r2, [r6, #-1688]
	movw	r3, #60536
	cmp	r2, r9
	b	.L1174
.L1159:
	ldr	r1, .L1181+60
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r5, [r6, #-1684]
	movw	r3, #60536
	cmp	r5, r9
	movt	r3, 65535
	movge	r5, r9
	cmp	r5, r3
	movlt	r5, r3
	b	.L1155
.L1167:
	mov	r2, r5
	b	.L1149
.L1179:
	add	r0, r5, #152
	bl	CloseDrivers
.L1175:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1178:
	movw	r3, #6026
	ldr	r2, .L1181+64
	ldr	r1, .L1181+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1157
.L1177:
	movw	r3, #5984
	ldr	r2, .L1181+72
	ldr	r1, .L1181+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1151
.L1180:
	movw	r3, #6077
	ldr	r2, .L1181+76
	ldr	r1, .L1181+68
	mov	r0, #22
	bl	dprint_vfmw
	b	.L1161
.L1176:
	ldr	ip, .L1181+80
	movw	r3, #938
	ldr	r2, .L1181+84
	ldr	r1, .L1181+88
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1146
.L1182:
	.align	2
.L1181:
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
	ldr	r1, .L1191
	mov	r2, r5
	mov	r0, #30
	bl	dprint_vfmw
	cmp	r6, #3
	beq	.L1189
	cmp	r4, r7
	movge	r4, r6
	blt	.L1190
.L1185:
	mov	r2, r6
	mov	r3, r4
	ldr	r1, .L1191+4
	mov	r0, #30
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1190:
	ldr	r1, .L1191+8
	mov	r0, #30
	bl	dprint_vfmw
.L1188:
	mov	r4, #3
	b	.L1185
.L1189:
	cmp	r5, r7
	ble	.L1188
	ldr	r1, .L1191+12
	mov	r0, #30
	bl	dprint_vfmw
	mov	r4, #0
	b	.L1185
.L1192:
	.align	2
.L1191:
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
	ldr	ip, .L1203
	mov	r2, #0
	b	.L1196
.L1194:
	add	r2, r2, #1
	cmp	r2, #32
	beq	.L1202
.L1196:
	ldr	r1, [ip], #4
	movw	r3, #17736
	movt	r3, 7
	cmp	r1, #0
	add	r3, r1, r3
	beq	.L1194
	cmp	r0, r3
	bne	.L1194
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L1202:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1204:
	.align	2
.L1203:
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
	ldr	r4, .L1217
	mov	lr, #0
.L1210:
	ldr	r2, [r4], #4
	cmp	r2, #0
	beq	.L1206
	movw	r3, #13576
	movw	r1, #15880
	movt	r3, 7
	movt	r1, 7
	add	r3, r2, r3
	add	r1, r2, r1
.L1209:
	ldr	r2, [r3]
	cmp	r2, r0
	bhi	.L1207
	ldr	ip, [r3, #-20]
	add	r2, r2, ip
	cmp	r0, r2
	bcc	.L1211
.L1207:
	add	r3, r3, #72
	cmp	r3, r1
	bne	.L1209
.L1206:
	add	lr, lr, #1
	cmp	lr, #32
	bne	.L1210
	mvn	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L1211:
	mov	r0, lr
	ldmfd	sp, {r4, fp, sp, pc}
.L1218:
	.align	2
.L1217:
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
	ldr	r6, .L1246
	mov	r5, r0
	mov	r4, r1
	ldr	ip, [r6, r0, asl #2]
	ldr	r2, [ip, #52]
	cmp	r2, #1
	beq	.L1241
	cmp	r2, #6
	cmpne	r2, #18
	sub	r1, r2, #2
	moveq	r3, #1
	movne	r3, #0
	cmp	r1, #1
	orrls	r3, r3, #1
	cmp	r3, #0
	bne	.L1221
.L1222:
	ldrd	r2, [r4, #32]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1242
	add	r1, ip, #640
	strd	r2, [r1]
.L1232:
	ldrd	r8, [r4, #48]
	add	r0, ip, #656
	add	lr, ip, #672
	ldr	r1, .L1246+4
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
	ldrb	lr, [r4, #16]	@ zero_extendqisi2
	strb	lr, [ip, #632]
	strd	r8, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1241:
	add	r3, ip, #475136
	ldr	r3, [r3, #1352]
	ldr	r2, [r3, #564]
	sxtb	r2, r2
	cmp	r2, #1
	bne	.L1222
.L1221:
	add	r1, ip, #1136
	add	r3, r4, #8
	mov	r0, r5
	bl	IsNewpicSeg
	cmp	r0, #0
	beq	.L1243
.L1223:
	ldr	r1, [r6, r5, asl #2]
	ldr	r3, [r1, #52]
	cmp	r3, #3
	addeq	r0, r1, #656
	beq	.L1229
.L1228:
	ldrd	r2, [r4, #32]
	mvn	r7, #0
	mvn	r6, #0
	add	r0, r1, #656
	cmp	r3, r7
	cmpeq	r2, r6
	strned	r2, [r0, #-8]
.L1230:
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
.L1229:
	ldrd	r2, [r0]
	mov	r0, #29
	ldr	r1, .L1246+8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L1243:
	ldr	ip, [r6, r5, asl #2]
	add	lr, ip, #656
	ldr	r3, [ip, #52]
	cmp	r3, #3
	beq	.L1244
	ldrd	r2, [lr, #-8]
	mvn	r1, #0
	mvn	r0, #0
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L1245
	add	r1, ip, #640
	strd	r2, [r1]
.L1225:
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
.L1227:
	ldr	r1, [ip, #704]
	mov	r0, #29
	ldr	r7, [ip, #700]
	ldr	lr, [ip, #708]
	str	r1, [ip, #692]
	ldr	r1, [ip, #716]
	str	r7, [ip, #688]
	str	lr, [ip, #696]
	str	r1, [ip, #712]
	ldr	r1, .L1246+12
	bl	dprint_vfmw
	ldr	r1, [r6, r5, asl #2]
	ldr	r3, [r1, #52]
	cmp	r3, #3
	bne	.L1228
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
	b	.L1223
.L1244:
	ldrd	r2, [lr, #-8]
	add	r1, ip, #640
	strd	r2, [r1]
	b	.L1225
.L1242:
	add	r3, ip, #640
	ldrd	r2, [r3]
	b	.L1232
.L1245:
	add	r3, ip, #640
	ldrd	r2, [r3]
	b	.L1225
.L1247:
	.align	2
.L1246:
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
	ldr	r3, .L1256
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #568]
	sub	r3, r2, #10
	cmp	r3, #2
	bhi	.L1249
	ldr	r3, .L1256+4
	ldr	r3, [r3, #-3180]
	ands	r3, r3, #1
	beq	.L1250
.L1249:
	bic	r3, r2, #16
	cmp	r3, #4
	cmpne	r2, #14
	movne	r3, #1
	moveq	r3, #0
	beq	.L1250
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	mvnne	r3, #1
	moveq	r3, #0
.L1250:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1257:
	.align	2
.L1256:
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
	ldrhi	ip, .L1302
	movwhi	r3, #5638
	bhi	.L1291
	ldr	r6, .L1302+4
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	beq	.L1294
	ldr	r3, [r0, #8]
	cmp	r3, #1
	bne	.L1295
	ldr	r5, [r0, #24]
	cmp	r5, #0
	ldrne	ip, .L1302+8
	movwne	r3, #5641
	bne	.L1291
	ldr	r8, .L1302+12
	mov	r7, r4, asl #2
	str	r5, [r0, #404]
	ldr	r9, .L1302+16
	ldr	r3, [r8]
	blx	r3
	add	r2, r9, r7
	ldr	r3, [r2, #-512]
	mov	r1, r0
	ldr	r0, .L1302+20
	rsb	r3, r3, r1
	ldr	r0, [r0]
	cmp	r3, r0
	mov	r0, r4
	bls	.L1264
	str	r1, [r2, #-512]
	bl	DecChanCheckDecParam
	cmn	r0, #2
	mov	r10, r0
	bne	.L1265
	mov	r2, r4
	ldr	r1, .L1302+24
	mov	r0, #23
	bl	dprint_vfmw
.L1281:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1264:
	bl	DecChanCheckDecParam
	cmn	r0, #2
	mov	r10, r0
	beq	.L1281
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	cmp	r0, #1
	mvnne	r10, #2
	bne	.L1281
.L1275:
	ldr	r1, [r6, r4, asl #2]
	add	r3, r1, #442368
	ldr	r3, [r3, #2136]
	cmp	r3, #1
	beq	.L1296
	cmp	r3, #3
	beq	.L1297
	ldrb	r3, [r1, #721]	@ zero_extendqisi2
	add	r10, r1, #720
	cmp	r3, #0
	bne	.L1268
	ldr	r3, [r1, #1496]
	cmp	r3, #0
	beq	.L1298
.L1268:
	ldrd	r2, [r10, #32]
	mov	r0, #29
	ldr	r1, .L1302+28
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
	bne	.L1299
.L1270:
	ldr	r3, [r6, r4, asl #2]
	movw	r2, #17736
	mov	r0, r10
	movt	r2, 7
	add	r2, r3, r2
	ldr	r1, [r3, #568]
	bl	DecodeStream
	mov	r0, #4
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L1300
.L1292:
	mov	r10, #0
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1265:
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	cmp	r0, #1
	moveq	r5, r0
	beq	.L1275
	mov	r2, r4
	ldr	r1, .L1302+32
	mov	r0, #23
	mvn	r10, #2
	bl	dprint_vfmw
	b	.L1281
.L1295:
	ldr	ip, .L1302+36
	movw	r3, #5640
.L1291:
	ldr	r2, .L1302+40
	mov	r0, #0
	ldr	r1, .L1302+44
	mvn	r10, #0
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1281
.L1300:
	ldr	r3, [r8]
	add	r7, r9, r7
	blx	r3
	ldr	r1, .L1302+48
	ldr	r3, [r7, #-384]
	ldr	r1, [r1]
	rsb	r3, r3, r0
	mov	r2, r0
	cmp	r3, r1
	bls	.L1292
	mov	r0, r4
	str	r2, [r7, #-384]
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L1292
	mov	r2, r4, asl #24
	movw	r1, #5740
	add	r2, r2, #262144
	ldr	r0, .L1302+52
	bl	DBG_AddTrace
	b	.L1292
.L1298:
	add	r1, r1, #728
	mov	r0, r4
	bl	SM_ReadSegStream
	cmp	r0, #0
	beq	.L1268
	cmp	r5, #1
	beq	.L1301
.L1269:
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #1
	mvn	r10, #3
	str	r2, [r3, #404]
	b	.L1281
.L1299:
	mov	r2, r4, asl #24
	movw	r1, #5722
	add	r2, r2, #196608
	ldr	r0, .L1302+52
	bl	DBG_AddTrace
	b	.L1270
.L1294:
	ldr	ip, .L1302+56
	movw	r3, #5639
	ldr	r2, .L1302+40
	mvn	r10, #0
	ldr	r1, .L1302+44
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1281
.L1296:
	ldr	r1, .L1302+60
	mov	r0, #31
	bl	dprint_vfmw
	mvn	r10, #2
	b	.L1281
.L1297:
	ldr	r2, [r1, #1448]
	mov	r0, #31
	ldr	r1, .L1302+64
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L1281
.L1301:
	mov	r2, r4
	ldr	r1, .L1302+68
	mov	r0, #23
	bl	dprint_vfmw
	b	.L1269
.L1303:
	.align	2
.L1302:
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
	ldr	r0, .L1336
	ldr	r1, .L1336+4
	sub	r3, r0, #128
.L1307:
	ldr	r2, [r1, #4]!
	add	r3, r3, #4
	cmp	r2, #0
	ldrne	r2, [r2, #20]
	str	r2, [r3, #-4]
	cmp	r3, r0
	bne	.L1307
	ldr	r7, .L1336+8
	mvn	r5, #0
	ldr	r8, .L1336+12
	mov	r9, #0
	mov	r10, r7
.L1308:
	mov	r3, #0
	ldr	r0, [r8, #-256]
	mov	r4, r3
	ldr	r1, .L1336+16
	b	.L1309
.L1311:
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	movlt	r0, r2
	movlt	r4, r3
.L1309:
	add	r3, r3, #1
	cmp	r3, #32
	bne	.L1311
	add	r3, r8, r4, lsl #2
	cmp	r0, #0
	add	r2, r4, #1
	mov	r1, #0
	str	r9, [r3, #-256]
	str	r2, [r7, #148]
	ldr	r3, .L1336+8
	ble	.L1312
	ldr	r3, [r10, r4, asl #2]
	cmp	r3, r1
	beq	.L1308
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bne	.L1308
	ldr	r2, [r3, #76]
	cmp	r2, r1
	ble	.L1314
	ldr	r5, [r3, #80]
	cmp	r5, r1
	beq	.L1334
.L1314:
	mov	r6, #500
	b	.L1322
.L1317:
	cmp	r0, #0
	ldr	r3, [r7, r4, asl #2]
	bne	.L1320
	ldr	r2, [r3, #1528]
	cmp	r2, #1
	beq	.L1320
	subs	r6, r6, #1
	beq	.L1308
.L1322:
	mov	r0, r4
	bl	DecChanSyntax
	cmn	r0, #1
	mov	r5, r0
	bne	.L1317
	ldr	r6, [r8, #-644]
	cmp	r6, #0
	beq	.L1328
	mov	r3, #0
	mov	r0, r4
	mov	r2, r3
	mov	r1, #102
	blx	r6
.L1328:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1320:
	str	r9, [r3, #1528]
	b	.L1308
.L1334:
	mov	r0, r4
	sub	r1, fp, #68
	bl	SM_GetInfo
	cmp	r0, #0
	bne	.L1335
.L1315:
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
	b	.L1314
.L1312:
	mov	r0, r5
	str	r1, [r3, #148]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1335:
	ldr	r3, .L1336+20
	mov	r1, r5
	sub	r0, fp, #68
	mov	r2, #24
	ldr	r3, [r3, #48]
	blx	r3
	b	.L1315
.L1337:
	.align	2
.L1336:
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
	ldr	r5, .L1349
	mov	r0, #0
	bl	VCTRL_RecordPosTime
	ldrb	r3, [r5, #1792]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1347
.L1339:
	ldr	r0, [r5, #912]
	mov	r3, #100
	ldr	r6, .L1349+4
	cmp	r0, #0
	str	r3, [r5, #144]
	ble	.L1340
	ldr	r3, [r6, #120]
	blx	r3
.L1340:
	ldr	r3, [r6, #12]
	mov	r0, #0
	blx	r3
	bl	SM_Wakeup
	ldr	r3, [r5, #908]
	mov	r2, #101
	str	r2, [r5, #144]
	cmp	r3, #0
	movne	r7, #0
	beq	.L1348
.L1341:
	mov	r3, #102
	str	r3, [r5, #144]
	bl	VDMDRV_WakeUpVdm
	mov	r4, #0
.L1342:
	mov	r0, r4
	mov	r1, #0
	add	r4, r4, #1
	bl	DeleteRawPacketInBuffer
	cmp	r4, #32
	bne	.L1342
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
.L1348:
	bl	DecSyntax
	mov	r7, r0
	b	.L1341
.L1347:
	mov	r0, #11
	bl	VCTRL_RecordPosTime
	mov	r3, #0
	strb	r3, [r5, #1792]
	b	.L1339
.L1350:
	.align	2
.L1349:
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
	ldr	r4, .L1378
	ldr	r6, .L1378+4
.L1352:
.L1359:
	ldr	r1, .L1378+8
	mov	r0, #2
	mov	r3, #0
	str	r3, [r4, #144]
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	mov	r5, #2
	str	r5, [r4, #132]
	cmp	r3, r5
	bne	.L1374
	b	.L1357
.L1376:
	str	r5, [r4, #144]
	bl	VCTRL_RunProcess
	ldr	r1, .L1378+12
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	cmp	r3, #2
	beq	.L1357
.L1374:
	cmp	r3, #3
	bne	.L1376
.L1355:
	ldr	r1, .L1378+16
	mov	r0, #2
	mov	r3, #6
	str	r3, [r4, #144]
	bl	dprint_vfmw
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #132]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1357:
	ldr	r1, .L1378+20
	mov	r0, #2
	mov	r3, #4
	str	r3, [r4, #144]
	bl	dprint_vfmw
	mov	r3, #1
	str	r3, [r4, #132]
	b	.L1354
.L1377:
	ldr	r3, [r6, #120]
	blx	r3
.L1354:
	ldr	r1, .L1378+24
	mov	r0, #22
	mov	r3, #5
	str	r3, [r4, #144]
	bl	dprint_vfmw
	ldr	r3, [r4, #136]
	mov	r0, #10
	cmp	r3, #1
	beq	.L1359
	cmp	r3, #3
	bne	.L1377
	b	.L1355
.L1379:
	.align	2
.L1378:
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
	ldr	r3, .L1399
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L1397
	ldr	r2, [r3, #568]
	cmp	r2, #20
	ldrls	pc, [pc, r2, asl #2]
	b	.L1398
.L1383:
	.word	.L1396
	.word	.L1384
	.word	.L1385
	.word	.L1386
	.word	.L1398
	.word	.L1387
	.word	.L1388
	.word	.L1398
	.word	.L1389
	.word	.L1390
	.word	.L1391
	.word	.L1391
	.word	.L1391
	.word	.L1392
	.word	.L1398
	.word	.L1393
	.word	.L1394
	.word	.L1395
	.word	.L1398
	.word	.L1398
	.word	.L1396
.L1396:
	add	r0, r3, #475136
	add	r0, r0, #1360
	ldmfd	sp, {fp, sp, pc}
.L1384:
	add	r0, r3, #524288
	add	r0, r0, #1520
	ldmfd	sp, {fp, sp, pc}
.L1385:
	movw	r0, #40360
	movt	r0, 7
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1386:
	movw	r0, #40904
	movt	r0, 8
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1387:
	movw	r0, #60264
	movt	r0, 7
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1388:
	movw	r0, #33928
	movt	r0, 7
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1389:
	add	r0, r3, #528384
	add	r0, r0, #2960
	ldmfd	sp, {fp, sp, pc}
.L1390:
	movw	r0, #7048
	movt	r0, 8
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1391:
	movw	r0, #30424
	movt	r0, 7
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1392:
	movw	r0, #25944
	movt	r0, 7
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1393:
	add	r0, r3, #475136
	add	r0, r0, #1936
	ldmfd	sp, {fp, sp, pc}
.L1394:
	movw	r0, #23320
	movt	r0, 7
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1395:
	add	r0, r3, #749568
	add	r0, r0, #2752
	ldmfd	sp, {fp, sp, pc}
.L1398:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1397:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1400:
	.align	2
.L1399:
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
	bhi	.L1417
	bl	VCTRL_GetChanVoQue
	subs	r4, r0, #0
	beq	.L1412
	sub	r2, fp, #36
	mov	r3, #0
	sub	r1, fp, #44
	str	r3, [fp, #-44]
	str	r3, [r2, #-4]!
	bl	GetQueueImgNum
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	beq	.L1412
	cmp	r2, #32
	bhi	.L1405
.L1408:
	ldr	r3, .L1419
	ldrh	r1, [r4, #4]
	ldr	r0, [r3, r5, asl #2]
	and	r1, r1, #63
	add	lr, r0, #475136
	add	r1, r4, r1, lsl #2
	ldr	r3, [lr, #1272]
	ldr	r1, [r1, #12]
	cmp	r3, #32
	bhi	.L1406
	add	r0, r0, r3, lsl #4
	mov	r6, #0
	add	r0, r0, #475136
	mov	r7, #0
	mov	ip, #1
	add	r0, r0, #748
	mov	r8, #0
	b	.L1409
.L1410:
	ldrh	r1, [r4, #4]
	cmp	r3, #33
	add	r1, r1, ip
	add	ip, ip, #1
	and	r1, r1, #63
	add	r1, r4, r1, lsl #2
	ldr	r1, [r1, #12]
	beq	.L1406
.L1409:
	ldr	r1, [r1, #20]
	cmp	ip, r2
	strd	r6, [r0, #4]
	add	r3, r3, #1
	str	r8, [r0, #-4]
	add	r0, r0, #16
	str	r1, [r0, #-16]
	str	r3, [lr, #1272]
	bcc	.L1410
.L1416:
	mov	r0, #0
.L1418:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1412:
	mvn	r0, #0
.L1403:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1406:
	mov	r2, r5
	ldr	r1, .L1419+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1418
.L1405:
	mov	r3, #32
	ldr	r1, .L1419+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	bne	.L1408
	b	.L1416
.L1417:
	ldr	ip, .L1419+12
	movw	r3, #3086
	ldr	r2, .L1419+16
	mov	r0, #0
	ldr	r1, .L1419+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1403
.L1420:
	.align	2
.L1419:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	cmp	r0, #31
	mov	r7, r0
	mov	r4, r1
	bhi	.L1438
	cmp	r1, #0
	beq	.L1439
	bl	VCTRL_GetChanVoQue
	subs	r5, r0, #0
	mvneq	r0, #0
	beq	.L1423
	ldr	r6, .L1441
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
	beq	.L1425
	cmp	r2, #32
	bhi	.L1440
.L1426:
	mov	r1, #0
	mov	r0, r1
	mov	lr, r1
.L1428:
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
	bcc	.L1428
	uxth	r3, r2
.L1427:
	ldrh	r1, [r5, #4]
	add	r3, r3, r1
	and	r3, r3, #63
	strh	r3, [r5, #4]	@ movhi
	str	r2, [r4, #528]
.L1429:
	ldr	r3, [r6, #16]
	mov	r0, #4
	blx	r3
	mov	r0, #0
.L1423:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1425:
	ldr	ip, .L1441+4
	ldr	r3, [ip, r7, asl #2]
	add	r1, r3, #475136
	ldr	r1, [r1, #1272]
	cmp	r1, #0
	beq	.L1429
	mov	r0, r2
	mov	lr, r2
.L1430:
	mov	r1, r0, asl #4
	add	r5, r0, #29696
	add	r3, r3, r1
	add	r1, r4, r1
	add	r3, r3, #475136
	add	r5, r5, #47
	add	r3, r3, #744
	mov	r8, #0
	add	r2, r2, #1
	ldr	r3, [r3, #4]
	uxth	r2, r2
	str	r3, [r1, #4]
	ldr	r3, [ip, r7, asl #2]
	ldr	r3, [r3, r5, asl #4]
	str	r8, [r1, #12]
	str	r3, [r1, #8]
	str	lr, [r4, r0, asl #4]
	sxth	r0, r2
	ldr	r3, [ip, r7, asl #2]
	add	r1, r3, #475136
	ldr	r1, [r1, #1272]
	cmp	r0, r1
	bcc	.L1430
	str	r1, [r4, #528]
	b	.L1429
.L1440:
	mov	r3, #32
	ldr	r1, .L1441+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [fp, #-44]
	cmp	r2, #0
	moveq	r3, r2
	bne	.L1426
	b	.L1427
.L1438:
	ldr	ip, .L1441+12
	movw	r3, #3162
	ldr	r2, .L1441+16
	mov	r0, #0
	ldr	r1, .L1441+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1423
.L1439:
	ldr	ip, .L1441+24
	mov	r0, r1
	movw	r3, #3163
	ldr	r2, .L1441+16
	ldr	r1, .L1441+20
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1423
.L1442:
	.align	2
.L1441:
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
	beq	.L1456
	cmp	r2, #0
	beq	.L1457
	cmp	r3, #0
	beq	.L1458
	cmp	r0, #31
	bhi	.L1459
	ldr	r7, .L1465
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L1460
	bl	VCTRL_GetChanVoQue
	subs	r3, r0, #0
	beq	.L1450
	mov	r2, r6
	mov	r1, r5
	bl	GetQueueImgNum
	ldr	r2, [r7, r4, asl #2]
	ldr	r3, [r2, #568]
	cmp	r3, #0
	beq	.L1461
	cmp	r3, #16
	beq	.L1462
	cmp	r3, #17
	moveq	r3, #9
	streq	r3, [r8]
	beq	.L1443
	cmp	r3, #15
	beq	.L1463
	cmp	r3, #18
	movne	r3, #2
	strne	r3, [r8]
	beq	.L1464
.L1443:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1450:
	str	r3, [r6]
	str	r3, [r5]
	str	r3, [r8]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1459:
	ldr	ip, .L1465+4
	movw	r3, #5849
	ldr	r2, .L1465+8
	mov	r0, #0
	ldr	r1, .L1465+12
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1461:
	add	r2, r2, #499712
	ldr	r3, [r2, #3488]
	str	r3, [r8]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1462:
	add	r2, r2, #475136
	ldr	r3, [r2, #3948]
	str	r3, [r8]
	b	.L1443
.L1464:
	ldr	r2, .L1465+8
	mov	r0, #32
	ldr	r1, .L1465+16
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L1456:
	ldr	ip, .L1465+20
	mov	r0, r8
	movw	r3, #5846
	ldr	r2, .L1465+8
	ldr	r1, .L1465+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1443
.L1457:
	ldr	ip, .L1465+24
	mov	r0, r2
	movw	r3, #5847
	ldr	r2, .L1465+8
	ldr	r1, .L1465+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1443
.L1458:
	ldr	ip, .L1465+28
	mov	r0, r3
	ldr	r2, .L1465+8
	movw	r3, #5848
	ldr	r1, .L1465+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1443
.L1463:
	add	r2, r2, #11599872
	ldr	r3, [r2, #176]
	str	r3, [r8]
	b	.L1443
.L1460:
	ldr	ip, .L1465+32
	mov	r0, r3
	ldr	r2, .L1465+8
	movw	r3, #5850
	ldr	r1, .L1465+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1443
.L1466:
	.align	2
.L1465:
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
	beq	.L1477
	cmp	r0, #31
	bhi	.L1478
	ldr	r6, .L1480
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	beq	.L1479
	ldr	r3, .L1480+4
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
	movw	r3, #2107
	ldr	r2, [r2, #1152]
	str	r2, [r4, #32]
	ldr	r2, [r6, r5, asl #2]
	ldr	r2, [r2, #1156]
	str	r2, [r4, #36]
	ldr	r2, [r6, r5, asl #2]
	ldr	r2, [r2, #1160]
	str	r2, [r4, #44]
	ldr	r2, [r6, r5, asl #2]
	add	r1, r2, #442368
	ldrsb	ip, [r1, r3]
	cmp	ip, r7
	ble	.L1475
	movw	r3, #7626
	mov	r1, r7
	movt	r3, 7
	add	r3, r2, r3
	mov	r0, r7
.L1474:
	ldrsb	r2, [r3]
	add	r1, r1, #1
	add	r3, r3, #88
	cmp	r2, #3
	addeq	r0, r0, #1
	cmp	r1, ip
	bne	.L1474
.L1472:
	str	r0, [r4, #84]
	movw	lr, #2107
	ldr	ip, [r6, r5, asl #2]
	sub	r3, fp, #56
	sub	r2, fp, #60
	sub	r1, fp, #64
	add	ip, ip, #442368
	mov	r0, r5
	ldrsb	ip, [ip, lr]
	str	ip, [r4, #92]
	bl	VCTRL_GetChanImgNum
	ldr	r2, .L1480+8
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
	add	r3, r3, #491520
	ldrb	r3, [r3, #840]	@ zero_extendqisi2
	and	r3, r3, #1
	str	r3, [r4, #88]
.L1467:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1478:
	ldr	ip, .L1480+12
	mov	r3, #1264
	ldr	r2, .L1480+16
	mov	r0, #0
	ldr	r1, .L1480+20
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1479:
	ldr	ip, .L1480+24
	movw	r3, #1265
	ldr	r2, .L1480+16
	ldr	r1, .L1480+20
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1467
.L1475:
	mov	r0, r7
	b	.L1472
.L1477:
	ldr	ip, .L1480+28
	mov	r0, r4
	movw	r3, #1263
	ldr	r2, .L1480+16
	ldr	r1, .L1480+20
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1467
.L1481:
	.align	2
.L1480:
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
	bhi	.L1486
	ldr	r3, .L1488
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #1268]
	beq	.L1487
.L1484:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1486:
	ldr	ip, .L1488+4
	movw	r3, #5913
	ldr	r2, .L1488+8
	mov	r0, #0
	ldr	r1, .L1488+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1484
.L1487:
	ldr	ip, .L1488+16
	movw	r3, #5914
	ldr	r2, .L1488+8
	ldr	r1, .L1488+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1484
.L1489:
	.align	2
.L1488:
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
	bhi	.L1494
	ldr	r3, .L1496
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #1272]
	beq	.L1495
.L1492:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1494:
	ldr	ip, .L1496+4
	movw	r3, #5921
	ldr	r2, .L1496+8
	mov	r0, #0
	ldr	r1, .L1496+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1492
.L1495:
	ldr	ip, .L1496+16
	movw	r3, #5922
	ldr	r2, .L1496+8
	ldr	r1, .L1496+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1492
.L1497:
	.align	2
.L1496:
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
	bhi	.L1502
	ldr	r3, .L1503
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r0, [r3, #36]
	moveq	r0, #33
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1502:
	ldr	ip, .L1503+4
	movw	r3, #5929
	ldr	r2, .L1503+8
	mov	r0, #0
	ldr	r1, .L1503+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1504:
	.align	2
.L1503:
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
	ldr	r5, .L1512
	add	r3, r3, #8
	movw	r2, #10000
	cmp	r3, r2
	mov	r4, r1
	str	r0, [r5, #-1688]
	bhi	.L1510
.L1506:
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
	ldr	r6, .L1512
	bhi	.L1511
.L1507:
	movw	r2, #5000
	cmp	r4, r2
	movw	r3, #60536
	movge	r4, r2
	movt	r3, 65535
	cmp	r4, r3
	movlt	r4, r3
	str	r4, [r5, #-1684]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1510:
	mov	r2, r0
	ldr	r1, .L1512+4
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r0, [r5, #-1688]
	b	.L1506
.L1511:
	mov	r2, r4
	ldr	r1, .L1512+8
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r4, [r6, #-1684]
	b	.L1507
.L1513:
	.align	2
.L1512:
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
	ldrne	r3, .L1526
	bne	.L1518
	b	.L1524
.L1519:
	ldr	r2, [r3, #8]!
	cmp	r2, r1
	beq	.L1525
.L1518:
	ldr	r0, [r3, #12]
	cmp	r0, #0
	bne	.L1519
	ldmfd	sp, {fp, sp, pc}
.L1525:
	ldmfd	sp, {fp, sp, pc}
.L1524:
	ldr	r0, .L1526+4
	ldmfd	sp, {fp, sp, pc}
.L1527:
	.align	2
.L1526:
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
	beq	.L1535
	cmp	r0, #0
	ldrne	r3, .L1541
	bne	.L1533
	b	.L1540
.L1534:
	ldr	ip, [r3, #8]!
	cmp	r0, ip
	beq	.L1531
.L1533:
	ldr	r4, [r3, #12]
	cmp	r4, #0
	bne	.L1534
	mov	r2, r0
	ldr	r1, .L1541+4
	mov	r0, #32
	bl	dprint_vfmw
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1540:
	ldr	r4, .L1541+8
.L1531:
	mov	r0, r1
	blx	r4
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1535:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1542:
	.align	2
.L1541:
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
	bhi	.L1549
	ldr	r3, .L1550
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	strne	r1, [r3, #408]
	ldmfd	sp, {fp, sp, pc}
.L1549:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_SetLastFrameState.part.23
.L1551:
	.align	2
.L1550:
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
	beq	.L1554
	cmp	r5, #1
	moveq	r2, #3
	movne	r2, #4
.L1554:
	cmp	r4, #31
	bhi	.L1566
	ldr	r7, .L1567
	ldr	r3, [r7, r4, asl #2]
	cmp	r3, #0
	strne	r2, [r3, #408]
.L1557:
	ldr	r3, .L1567+4
	ldr	r6, [r3, #-644]
	cmp	r6, #0
	beq	.L1558
	sub	r2, fp, #28
	mov	r3, #4
	mov	r1, #115
	mov	r0, r4
	str	r5, [r2, #-4]!
	blx	r6
.L1558:
	ldr	ip, [r7, r4, asl #2]
	mov	r3, r5
	mov	r2, r4
	ldr	r1, .L1567+8
	mov	r0, #1
	ldr	ip, [ip, #408]
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1566:
	bl	VCTRL_SetLastFrameState.part.23
	ldr	r7, .L1567
	b	.L1557
.L1568:
	.align	2
.L1567:
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
	bhi	.L1596
	ldr	r3, .L1599
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L1597
	add	r2, r3, #475136
	ldr	r2, [r2, #1344]
	cmp	r2, #17
	ldrls	pc, [pc, r2, asl #2]
	b	.L1589
.L1575:
	.word	.L1574
	.word	.L1576
	.word	.L1577
	.word	.L1578
	.word	.L1589
	.word	.L1579
	.word	.L1580
	.word	.L1589
	.word	.L1581
	.word	.L1582
	.word	.L1583
	.word	.L1583
	.word	.L1583
	.word	.L1584
	.word	.L1589
	.word	.L1585
	.word	.L1586
	.word	.L1587
.L1589:
	mov	r0, r5
	mov	r1, #1
	bl	VCTRL_ReportLastFrame
	ldr	r1, .L1599+4
	mov	r0, #2
	bl	dprint_vfmw
	mvn	r0, #0
.L1571:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1587:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	VP9DEC_GetRemainImg
	mov	r4, r0
.L1573:
	cmn	r4, #1
	beq	.L1589
	cmp	r4, #0
	bne	.L1598
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_ReportLastFrame
	ldr	r1, .L1599+8
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1574:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	H264DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1577:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	MPEG4DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1578:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	MPEG2DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1576:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	VC1DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1579:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	DIVX3DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1580:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	AVSDEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1581:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	REAL8DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1582:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	REAL9DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1583:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	VP6DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1584:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	VP8DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1585:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	MVC_DEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1586:
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	HEVCDEC_GetRemainImg
	mov	r4, r0
	b	.L1573
.L1598:
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_ReportLastFrame
	sub	r2, r4, #2
	ldr	r1, .L1599+12
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1596:
	ldr	ip, .L1599+16
	movw	r3, #7206
	ldr	r2, .L1599+20
	mov	r0, #0
	ldr	r1, .L1599+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1571
.L1597:
	ldr	ip, .L1599+28
	mov	r0, r3
	ldr	r2, .L1599+20
	movw	r3, #7207
	ldr	r1, .L1599+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1571
.L1600:
	.align	2
.L1599:
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
	ldr	r5, .L1641
	mov	r4, r0
	ldr	ip, [r5, r0, asl #2]
	cmp	ip, #0
	beq	.L1634
	ldr	r0, [ip, #568]
	ldr	r6, [ip, #1208]
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L1601
.L1605:
	.word	.L1604
	.word	.L1606
	.word	.L1607
	.word	.L1608
	.word	.L1601
	.word	.L1609
	.word	.L1610
	.word	.L1601
	.word	.L1611
	.word	.L1612
	.word	.L1613
	.word	.L1613
	.word	.L1613
	.word	.L1614
	.word	.L1601
	.word	.L1615
	.word	.L1616
	.word	.L1617
.L1616:
	movw	r0, #17736
	str	r3, [sp, #4]
	str	r6, [sp]
	mov	r3, r2
	movt	r0, 7
	mov	r2, #1
	add	r0, ip, r0
	ldr	r7, .L1641
	bl	HEVCDEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r3, r3, #475136
	ldrb	r3, [r3, #1361]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1635
.L1620:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #475136
	strne	r2, [r3, #3776]
.L1601:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1617:
	movw	r0, #17736
	mov	r2, r6
	movt	r0, 7
	add	r0, ip, r0
	bl	VP9DEC_VDMPostProc
	cmp	r6, #1
	bne	.L1633
	b	.L1601
.L1604:
	movw	r0, #17736
	str	r3, [sp, #4]
	str	r6, [sp]
	mov	r3, r2
	movt	r0, 7
	mov	r2, #1
	add	r0, ip, r0
	ldr	r7, .L1641
	bl	H264DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r3, r3, #487424
	ldrb	r3, [r3, #2624]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1636
.L1618:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #475136
	strne	r2, [r3, #1712]
	b	.L1601
.L1607:
	movw	r0, #17736
	ldr	r6, .L1641
	movt	r0, 7
	add	r0, ip, r0
	bl	MPEG4DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #495616
	ldrb	r2, [r2, #3884]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1637
.L1623:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #2388]
	b	.L1601
.L1608:
	movw	r0, #17736
	movt	r0, 7
	add	r0, ip, r0
	bl	MPEG2DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1641
	add	r2, r3, #565248
	ldrb	r2, [r2, #314]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1638
.L1625:
	add	r3, r3, #475136
	mov	r2, #0
	str	r2, [r3, #1356]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1606:
	movw	r0, #17736
	movt	r0, 7
	add	r0, ip, r0
	bl	VC1DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1641
	add	r2, r3, #487424
	ldrb	r2, [r2, #1807]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1625
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #487424
	strb	r1, [r2, #1807]
	b	.L1625
.L1609:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetSwitchRounding
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	DIVX3DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1356]
	b	.L1601
.L1610:
	movw	r0, #17736
	movt	r0, 7
	add	r0, ip, r0
	bl	AVSDEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1641
	add	r3, r3, #475136
	ldrb	r2, [r3, #1352]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1639
.L1624:
	mov	r2, #0
	str	r2, [r3, #1368]
	b	.L1601
.L1611:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetMb0QpInCurrPic
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	REAL8DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1356]
	b	.L1601
.L1612:
	mov	r0, r3
	str	r1, [fp, #-32]
	bl	VDMDRV_GetMb0QpInCurrPic
	ldr	r3, [r5, r4, asl #2]
	ldr	r1, [fp, #-32]
	mov	r2, r0
	movw	r0, #17736
	movt	r0, 7
	add	r0, r3, r0
	bl	REAL9DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1356]
	b	.L1601
.L1613:
	movw	r0, #17736
	movt	r0, 7
	add	r0, ip, r0
	bl	VP6DEC_VDMPostProc
.L1633:
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1356]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1615:
	movw	r0, #17736
	mov	r2, #1
	movt	r0, 7
	add	r0, ip, r0
	bl	MVC_DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r6, .L1641
	add	r3, r3, #475136
	ldrb	r2, [r3, #1353]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1640
.L1626:
	mov	r2, #0
	str	r2, [r3, #1580]
	b	.L1601
.L1614:
	movw	r0, #17736
	movt	r0, 7
	add	r0, ip, r0
	bl	VP8DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1356]
	b	.L1601
.L1634:
	ldr	lr, .L1641+4
	mov	r0, ip
	movw	r3, #4036
	ldr	r2, .L1641+8
	ldr	r1, .L1641+12
	str	lr, [sp]
	bl	dprint_vfmw
	b	.L1601
.L1637:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #495616
	strb	r1, [r2, #3884]
	b	.L1623
.L1638:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #565248
	strb	r1, [r2, #314]
	b	.L1625
.L1640:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r2, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r2, #475136
	mov	r3, r2
	strb	r1, [r2, #1353]
	b	.L1626
.L1639:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r2, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r2, #475136
	mov	r3, r2
	strb	r1, [r2, #1352]
	b	.L1624
.L1636:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #487424
	strb	r2, [r3, #2624]
	b	.L1618
.L1635:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	strb	r2, [r3, #1361]
	b	.L1620
.L1642:
	.align	2
.L1641:
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
	ldrhi	ip, .L1653
	movhi	r3, #4224
	bhi	.L1651
	ldr	ip, .L1653+4
	ldr	ip, [ip, r0, asl #2]
	cmp	ip, #0
	beq	.L1652
	ldr	ip, [ip, #8]
	cmp	ip, #1
	beq	.L1647
	ldr	ip, .L1653+8
	movw	r3, #4226
.L1651:
	ldr	r2, .L1653+12
	mov	r0, #0
	ldr	r1, .L1653+16
	str	ip, [sp]
	bl	dprint_vfmw
.L1643:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1647:
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L1643
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_PostProc
.L1652:
	ldr	lr, .L1653+20
	mov	r0, ip
	movw	r3, #4225
	ldr	r2, .L1653+12
	ldr	r1, .L1653+16
	str	lr, [sp]
	bl	dprint_vfmw
	b	.L1643
.L1654:
	.align	2
.L1653:
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
	bhi	.L1659
	add	r1, r1, #2
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_ReportLastFrame
.L1659:
	ldr	ip, .L1660
	movw	r3, #7332
	ldr	r2, .L1660+4
	mov	r0, #0
	ldr	r1, .L1660+8
	str	ip, [sp]
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L1661:
	.align	2
.L1660:
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
	b	.L1663
.L1665:
	.word	.L1664
	.word	.L1666
	.word	.L1667
	.word	.L1668
	.word	.L1669
	.word	.L1670
	.word	.L1671
.L1671:
	cmp	r0, #1
	moveq	r0, #1
	movne	r0, #7
	ldmfd	sp, {fp, sp, pc}
.L1664:
	cmp	r0, #1
	moveq	r0, #0
	movne	r0, #6
	ldmfd	sp, {fp, sp, pc}
.L1666:
	cmp	r0, #1
	moveq	r0, #2
	movne	r0, #8
	ldmfd	sp, {fp, sp, pc}
.L1667:
	cmp	r0, #1
	moveq	r0, #4
	movne	r0, #10
	ldmfd	sp, {fp, sp, pc}
.L1668:
	cmp	r0, #1
	moveq	r0, #3
	movne	r0, #9
	ldmfd	sp, {fp, sp, pc}
.L1669:
	cmp	r0, #1
	moveq	r0, #5
	movne	r0, #11
	ldmfd	sp, {fp, sp, pc}
.L1670:
	cmp	r0, #1
	moveq	r0, #13
	movne	r0, #12
	ldmfd	sp, {fp, sp, pc}
.L1663:
	mov	r3, r1
	movw	r2, #7816
	ldr	r1, .L1680
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #13
	ldmfd	sp, {fp, sp, pc}
.L1681:
	.align	2
.L1680:
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
	beq	.L1690
	ldr	r3, [r5, #4]
	cmp	r3, #1
	beq	.L1685
	mov	r1, r0
	mov	r2, #0
	mov	r0, r8
	bl	FSP_ClearLogicFs
	mov	r0, #0
.L1684:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1685:
	ldr	r0, [r5, #48]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L1691
.L1686:
	mov	r1, r7
	mov	r0, r8
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1692
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
	ldr	ip, .L1694
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
	beq	.L1693
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
	ldr	r3, .L1694+4
	str	r4, [sp]
	movw	r2, #17736
	mov	r1, r9
	movt	r2, 7
	ldr	ip, [r3, r8, asl #2]
	mov	r0, r8
	add	r3, ip, #475136
	add	r2, ip, r2
	add	r3, r3, #1360
	bl	InsertImgToVoQueue
	cmp	r0, #1
	moveq	r0, r6
	beq	.L1684
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
	b	.L1684
.L1691:
	ldr	r3, [r5, #4]
	cmp	r3, #1
	bne	.L1686
	ldr	r2, [r5, #48]
	ldr	r1, .L1694+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1684
.L1690:
	ldr	r2, [r5, #40]
	mov	r0, #0
	ldr	r1, .L1694+12
	bl	dprint_vfmw
	mov	r0, r7
	b	.L1684
.L1693:
	mov	r2, r0
	ldr	r1, .L1694+16
	mov	r0, r9
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1684
.L1692:
	movw	r2, #4519
	ldr	r1, .L1694+20
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1684
.L1695:
	.align	2
.L1694:
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
	ldr	r5, .L1708
	mov	r4, r0
	mov	r3, r1
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	ldreq	ip, .L1708+4
	movweq	r3, #4659
	beq	.L1704
	cmp	r3, #0
	beq	.L1705
	ldr	r2, [r0, #568]
	cmp	r2, #20
	bne	.L1706
	ldr	r3, .L1708+8
	mov	r2, #72
	add	r0, r0, #496
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r1, [r5, r4, asl #2]
	mov	r0, r4
	add	r1, r1, #496
	bl	VDH_PutUsrdecFrame
	cmp	r0, #0
	bne	.L1707
.L1698:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1706:
	ldr	r1, .L1708+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1698
.L1707:
	ldr	r1, .L1708+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1698
.L1705:
	ldr	ip, .L1708+20
	mov	r0, r3
	movw	r3, #4660
.L1704:
	ldr	r2, .L1708+24
	ldr	r1, .L1708+28
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1698
.L1709:
	.align	2
.L1708:
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
	beq	.L1712
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_CanBeDecodedByHardWare.part.25
.L1712:
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
	ldrhi	r1, .L1762
	bhi	.L1752
	ldr	r5, .L1762+4
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L1753
	ldr	r3, [r0, #4]
	cmp	r3, #1
	bne	.L1719
	ldr	r0, [r0, #568]
	cmp	r0, #22
	beq	.L1719
	cmp	r0, #4
	cmpne	r0, #7
	moveq	r7, #1
	movne	r7, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r4, r7
.L1725:
	mov	r0, r4
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L1724
	ldr	r3, [r5, r4, asl #2]
	ldr	r0, [r3, #568]
	cmp	r0, #4
	cmpne	r0, #7
	beq	.L1724
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	cmp	r0, #0
	addne	r7, r7, #1
.L1724:
	add	r4, r4, #1
	cmp	r4, #32
	bne	.L1725
	cmp	r7, #1
	beq	.L1754
.L1726:
	ldr	r3, .L1762+8
	mov	r1, #0
	add	r0, r3, #128
.L1733:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1732
	ldr	r2, [r2, #568]
	cmp	r2, #6
	moveq	r1, #1
.L1732:
	cmp	r3, r0
	bne	.L1733
	cmp	r1, #1
	beq	.L1755
.L1734:
	ldr	r3, [r5, r6, asl #2]
	ldr	r3, [r3, #568]
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, .L1762+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1756
	ldr	r3, .L1762+16
	ldr	r3, [r3, #28]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L1719:
	ldr	r1, .L1762+20
	movw	r2, #7877
.L1752:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1754:
	ldr	r4, .L1762+12
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1757
	mov	r0, r7
	mov	r1, #0
	bl	VDH_Need_Module
.L1729:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1730
	ldr	r3, .L1762+16
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L1758
	mov	r0, #0
	blx	r3
	b	.L1726
.L1755:
	ldr	r3, .L1762+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1759
	mov	r1, #0
	mov	r0, #3
	bl	VDH_Need_Module
	b	.L1734
.L1759:
	ldr	r3, .L1762+16
	ldr	r3, [r3, #12]
	cmp	r3, #0
	beq	.L1760
	mov	r0, #0
	blx	r3
	b	.L1734
.L1757:
	ldr	r3, .L1762+16
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1761
	mov	r0, #0
	blx	r3
	b	.L1729
.L1753:
	movw	r2, #7871
	ldr	r1, .L1762+24
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1756:
	mov	r1, #0
	mov	r0, #2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Need_Module
.L1730:
	mov	r1, #0
	mov	r0, r1
	bl	VDH_Need_Module
	b	.L1726
.L1758:
	mov	r0, r3
	movw	r2, #7926
	ldr	r1, .L1762+28
	bl	dprint_vfmw
	b	.L1726
.L1760:
	mov	r0, r3
	movw	r2, #7957
	ldr	r1, .L1762+28
	bl	dprint_vfmw
	b	.L1734
.L1761:
	mov	r0, r3
	movw	r2, #7912
	ldr	r1, .L1762+28
	bl	dprint_vfmw
	b	.L1729
.L1763:
	.align	2
.L1762:
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
	ldrhi	ip, .L1778
	movwhi	r3, #2308
	bhi	.L1775
	ldr	r4, .L1778+4
	ldr	r3, [r4, r0, asl #2]
	cmp	r3, #0
	beq	.L1776
	ldr	r6, [r3, #4]
	cmp	r6, #1
	bne	.L1777
	ldr	r3, [r3, #568]
	cmp	r3, #22
	ldreq	ip, .L1778+8
	movweq	r3, #2311
	beq	.L1775
	bl	SM_Start
	ldr	r3, [r4, r5, asl #2]
	mov	r2, #0
	add	r1, r3, #475136
	str	r6, [r1, #1340]
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
	bne	.L1770
	ldr	r3, .L1778+12
	sub	r0, r4, #4
	ldr	r1, .L1778+16
	add	lr, r3, #128
	str	r6, [r2, #20]
.L1773:
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
	bne	.L1773
	ldr	r0, .L1778+12
	bl	VDMDRV_SetPriority
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
.L1770:
	ldr	r4, .L1778+20
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r5
	bl	VCTRL_OpenHardware
	mov	r2, #12
	ldr	r3, [r4, #48]
	mov	r1, #0
	ldr	r0, .L1778+24
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #720
	mov	r1, #0
	ldr	r0, .L1778+28
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #2
	mov	r1, #0
	ldr	r0, .L1778+32
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #120
	mov	r1, #0
	ldr	r0, .L1778+36
	blx	r3
	mov	r0, #0
.L1766:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1777:
	ldr	ip, .L1778+40
	movw	r3, #2310
.L1775:
	ldr	r2, .L1778+44
	mov	r0, #0
	ldr	r1, .L1778+48
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1766
.L1776:
	ldr	ip, .L1778+52
	mov	r0, r3
	ldr	r2, .L1778+44
	movw	r3, #2309
	ldr	r1, .L1778+48
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1766
.L1779:
	.align	2
.L1778:
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
	ldr	r1, .L1781
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1782:
	.align	2
.L1781:
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
	ldr	r5, .L1845
	mov	r8, #0
	str	r0, [fp, #-48]
	mov	r7, r8
	add	r9, r5, #128
	mov	r1, r8
	b	.L1793
.L1835:
	ldr	r3, [r4, #4]
	cmp	r3, #1
	beq	.L1832
.L1789:
	cmp	r8, #0
	cmpeq	r6, #6
	bne	.L1784
	ldr	r3, [r4, #4]
	cmp	r3, #1
	beq	.L1833
.L1784:
	cmp	r5, r9
	beq	.L1834
.L1793:
	ldr	r4, [r5, #4]!
	cmp	r4, #0
	beq	.L1784
	cmp	r1, #0
	ldr	r6, [r4, #568]
	beq	.L1835
	cmp	r7, #0
	cmpeq	r6, #1
	bne	.L1789
	ldr	r3, [r4, #4]
	cmp	r3, #1
	bne	.L1784
	ldr	r10, [r4, #8]
.L1812:
	cmp	r10, #1
	moveq	r7, #1
	cmp	r8, #0
	cmpeq	r6, #6
	bne	.L1784
.L1813:
	cmp	r10, #1
	moveq	r8, #1
	cmp	r5, r9
	bne	.L1793
.L1834:
	cmp	r1, #0
	beq	.L1836
.L1794:
	cmp	r8, #0
	bne	.L1806
	ldr	r3, .L1845+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1837
	mov	r1, r8
	mov	r0, #3
	bl	VDH_UnNeed_Module
.L1806:
	cmp	r7, #0
	bne	.L1783
.L1842:
	ldr	r3, .L1845+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1838
	ldr	r3, .L1845+8
	ldr	r3, [r3, #32]
	cmp	r3, #0
	beq	.L1783
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L1833:
	ldr	r10, [r4, #8]
	b	.L1813
.L1832:
	ldr	r10, [r4, #8]
	cmp	r10, #1
	beq	.L1839
.L1788:
	cmp	r7, #0
	cmpeq	r6, #1
	beq	.L1812
	b	.L1789
.L1839:
	cmp	r6, #7
	cmpne	r6, #4
	beq	.L1788
	mov	r0, r6
	bl	VCTRL_CanBeDecodedByHardWare.part.25
	adds	r1, r0, #0
	movne	r1, #1
	b	.L1788
.L1836:
	ldr	r4, .L1845+4
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1799
	ldr	r5, [fp, #-48]
	str	r1, [fp, #-52]
	mov	r0, r5
	bl	SCDDRV_ResetSCD
	mov	r0, r5
	bl	VDMDRV_ResetVDH
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r1, [fp, #-52]
	cmp	r3, #1
	beq	.L1799
	mov	r0, #1
	bl	VDH_UnNeed_Module
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1802
.L1844:
	ldr	r3, .L1845+8
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L1840
	mov	r0, #0
	blx	r3
.L1805:
	mov	r0, #0
	bl	SCDDRV_SetStateIdle
	b	.L1794
.L1837:
	ldr	r3, .L1845+8
	mov	r0, r8
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L1841
	blx	r3
	cmp	r7, #0
	beq	.L1842
.L1783:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1838:
	mov	r1, r7
	mov	r0, #2
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	VDH_UnNeed_Module
.L1799:
	ldr	r3, .L1845+8
	ldr	r3, [r3, #8]
	cmp	r3, #0
	beq	.L1843
	mov	r0, #0
	blx	r3
.L1801:
	mov	r0, #0
	bl	VDMDRV_SetStateIdle
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1844
.L1802:
	mov	r1, #0
	mov	r0, r1
	bl	VDH_UnNeed_Module
	b	.L1794
.L1840:
	mov	r0, r3
	movw	r2, #8051
	ldr	r1, .L1845+12
	bl	dprint_vfmw
	b	.L1805
.L1841:
	movw	r2, #8069
	ldr	r1, .L1845+12
	bl	dprint_vfmw
	b	.L1806
.L1843:
	mov	r0, r3
	movw	r2, #8036
	ldr	r1, .L1845+12
	bl	dprint_vfmw
	b	.L1801
.L1846:
	.align	2
.L1845:
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
	bhi	.L1853
	ldr	r6, .L1855
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1854
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L1852
	str	r2, [r3, #24]
	mov	r3, #0
	ldr	r2, [r6, r0, asl #2]
	str	r3, [r2, #12]
	ldr	r2, [r6, r0, asl #2]
	str	r3, [r2, #8]
	bl	SM_Stop
	subs	r5, r0, #0
	bne	.L1852
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
.L1849:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1852:
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1853:
	ldr	ip, .L1855+4
	movw	r3, #2395
	ldr	r2, .L1855+8
	mov	r0, #0
	ldr	r1, .L1855+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1849
.L1854:
	ldr	ip, .L1855+16
	mov	r0, r3
	ldr	r2, .L1855+8
	movw	r3, #2396
	ldr	r1, .L1855+12
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1849
.L1856:
	.align	2
.L1855:
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
	ldr	r5, .L1864
	mov	r7, r0
	mov	r4, #0
	mov	r8, r5
	b	.L1859
.L1863:
	add	r4, r4, #1
	ldr	r3, [r8, #120]
	blx	r3
	cmp	r4, #50
	beq	.L1861
.L1859:
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
	bne	.L1863
	cmp	r4, #49
	bgt	.L1861
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1861:
	ldr	r1, .L1864+4
	mvn	r6, #0
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1865:
	.align	2
.L1864:
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
	bhi	.L1892
	ldr	r6, .L1898
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1893
	ldr	r2, [r1]
	cmp	r2, #1
	bhi	.L1894
	ldr	r9, .L1898+4
	mov	r5, #0
	ldr	r7, [r3, #8]
	bl	VCTRL_StopChan
	ldr	r2, [r6, r4, asl #2]
	mov	r3, r4, asl #5
	ldr	r0, .L1898+8
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
	movw	r1, #17736
	movt	r1, 7
	add	r1, r3, r1
	ldr	r0, [r3, #568]
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
	addeq	r2, r3, #475136
	streq	r5, [r3, #1496]
	streq	r5, [r2, #1276]
	ldr	r3, [r3, #568]
	cmp	r3, #20
	beq	.L1872
	ldr	r3, [r8, #8]
	cmp	r3, #0
	beq	.L1895
.L1872:
	bl	FSP_EmptyInstance
.L1873:
	mov	r0, r4
	bl	InitUsdPool
	ldr	r3, [r8]
	cmp	r3, #0
	beq	.L1896
.L1874:
	ldr	r2, [r6, #1056]
	ldr	r3, .L1898
	cmp	r2, #0
	beq	.L1875
	add	r5, r3, r4, lsl #2
	str	r4, [fp, #-48]
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1877
	mov	r0, #512
	sub	r1, fp, #48
	bl	VCTRL_SetDbgOption
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1877
	sub	r1, fp, #48
	mov	r0, #512
	bl	VCTRL_SetDbgOption
.L1877:
	ldr	r1, .L1898+12
	mov	r0, #32
	bl	dprint_vfmw
.L1875:
	cmp	r7, #0
	bne	.L1897
.L1879:
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, #0
.L1868:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1896:
	mov	r0, r4
	bl	SM_Reset
	b	.L1874
.L1897:
	mov	r0, r4
	bl	VCTRL_StartChan
	b	.L1879
.L1895:
	bl	FSP_ResetInstance
	b	.L1873
.L1894:
	movw	r2, #2972
	ldr	r1, .L1898+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1868
.L1892:
	ldr	ip, .L1898+20
	movw	r3, #2967
	ldr	r2, .L1898+24
	mov	r0, #0
	ldr	r1, .L1898+28
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1868
.L1893:
	ldr	ip, .L1898+32
	mov	r0, r3
	ldr	r2, .L1898+24
	movw	r3, #2968
	ldr	r1, .L1898+28
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1868
.L1899:
	.align	2
.L1898:
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
	bhi	.L1922
	ldr	r6, .L1926
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1923
	ldr	r8, [r3, #8]
	bl	VCTRL_StopChan
	ldr	r7, .L1926+4
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
	beq	.L1924
.L1904:
	mov	r3, r4, asl #5
	ldr	r0, .L1926+8
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
	add	r2, r3, #475136
	add	lr, r3, #640
	add	ip, r3, #656
	strd	r0, [lr]
	strd	r0, [ip, #-8]
	mov	r0, r4
	str	r5, [r3, #1136]
	str	r5, [r2, #1304]
	str	r5, [r2, #1296]
	str	r5, [r2, #1300]
	ldr	r1, [r3, #1448]
	str	r5, [r3, #1532]
	cmp	r1, #1
	streq	r5, [r3, #1496]
	streq	r5, [r2, #1276]
	ldr	r3, [r3, #568]
	cmp	r3, #20
	beq	.L1906
	bl	FSP_ResetInstance
.L1907:
	ldr	r3, [r7, #16]
	mov	r0, #4
	blx	r3
	mov	r0, r4
	bl	InitUsdPool
	mov	r0, r4
	bl	SM_Reset
	ldr	r2, [r6, #1056]
	ldr	r3, .L1926
	cmp	r2, #0
	beq	.L1908
	add	r5, r3, r4, lsl #2
	str	r4, [fp, #-40]
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1910
	mov	r0, #512
	sub	r1, fp, #40
	bl	VCTRL_SetDbgOption
	ldr	r3, [r5, #1468]
	cmp	r3, #0
	beq	.L1910
	sub	r1, fp, #40
	mov	r0, #512
	bl	VCTRL_SetDbgOption
.L1910:
	ldr	r1, .L1926+12
	mov	r0, #32
	bl	dprint_vfmw
.L1908:
	cmp	r8, #0
	bne	.L1925
.L1912:
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, #0
.L1902:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1925:
	mov	r0, r4
	bl	VCTRL_StartChan
	b	.L1912
.L1906:
	bl	FSP_EmptyInstance
	b	.L1907
.L1924:
	add	r2, r3, #475136
	ldr	r1, [r3, #568]
	ldr	r2, [r2, #1344]
	cmp	r2, r1
	bne	.L1904
	str	r5, [r3, #12]
	mov	r0, r4
	bl	VCTRL_FindOccupiedFrame
	b	.L1904
.L1922:
	ldr	ip, .L1926+16
	movw	r3, #3310
	ldr	r2, .L1926+20
	mov	r0, #0
	ldr	r1, .L1926+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1902
.L1923:
	ldr	ip, .L1926+28
	mov	r0, r3
	ldr	r2, .L1926+20
	movw	r3, #3311
	ldr	r1, .L1926+24
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1902
.L1927:
	.align	2
.L1926:
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
	ldr	r6, .L2039
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
	beq	.L2024
	ldr	r2, [r7, #36]
	cmp	r2, #0
	blt	.L1931
	ldr	r2, [r7, #12]
	cmp	r2, #31
	ble	.L1931
	ldr	r3, [r7, #16]
	cmp	r3, #31
	ble	.L1931
	ldr	r3, [r7, #56]
	cmp	r3, #262144
	blt	.L1931
	ldr	r2, [r7, #44]
	cmp	r2, #1
	beq	.L2025
	cmp	r2, #2
	bne	.L1933
	ldr	r3, [r7, #20]
	cmp	r3, #0
	ble	.L1931
	ldr	r3, [r7, #24]
	cmp	r3, #0
	ble	.L1931
.L2019:
	ldr	r3, [r7, #28]
	cmp	r3, #0
	ble	.L1931
	ldr	r3, [r7, #32]
	cmp	r3, #0
	bgt	.L1933
.L1931:
	ldr	r1, .L2039+4
	mov	r0, #0
	bl	dprint_vfmw
.L2021:
	mvn	r0, #0
.L2014:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1933:
	ldr	r3, [r7, #192]
	movw	ip, #63768
	mov	r4, #1
	movt	ip, 14
	cmp	r3, #1
	sub	r2, fp, #256
	movw	r8, #46512
	mov	r1, r7
	movhi	r3, #0
	strhi	r3, [r7, #192]
	cmp	r10, #26
	mov	r3, r5
	str	r4, [r7, #216]
	mov	r0, r10
	str	r4, [r7, #220]
	movt	r8, 180
	movne	r8, ip
	bl	VCTRL_GetChanMemSize
	cmp	r0, #0
	bne	.L2026
	ldr	r5, .L2039+8
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L1986
	mov	r3, r5
.L1939:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1938
	add	r4, r4, #1
	cmp	r4, #32
	bne	.L1939
	ldr	r3, [r7, #228]
	cmp	r3, #1
	beq	.L1983
.L1984:
	mov	r2, #32
	ldr	r1, .L2039+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2014
.L2025:
	ldr	r3, [r7, #20]
	cmp	r3, #0
	bgt	.L2019
	b	.L1931
.L2026:
	movw	r2, #1947
	ldr	r1, .L2039+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2014
.L2024:
	mov	r0, r7
	ldr	r1, .L2039+20
	bl	dprint_vfmw
	b	.L2021
.L1986:
	mov	r4, r3
.L1938:
	ldr	r3, [r7, #228]
	cmp	r3, #1
	beq	.L1983
.L1941:
	cmp	r4, #31
	bhi	.L1984
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #228
	blx	r3
	ldrd	r2, [r7, #128]
	ldr	r9, .L2039
	orrs	r3, r2, r3
	beq	.L1943
	ldr	r3, [r7, #136]
	cmp	r3, #0
	bne	.L1944
.L1943:
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
	bne	.L2027
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
.L1947:
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #228
	blx	r3
	ldrd	r2, [r7, #80]
	ldr	r1, .L2039
	orrs	r3, r2, r3
	beq	.L1978
	ldr	r3, [r7, #88]
	cmp	r3, #0
	bne	.L1949
.L1978:
	ldr	r3, [r7, #192]
	cmp	r3, #1
	beq	.L1950
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
	bne	.L2028
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
.L1954:
	ldr	r3, [r6, #48]
	mov	r2, #24
	mov	r1, #0
	sub	r0, fp, #228
	blx	r3
	ldrd	r2, [r7, #104]
	ldr	r1, .L2039
	orrs	r3, r2, r3
	beq	.L1980
	ldr	r3, [r7, #112]
	cmp	r3, #0
	bne	.L1958
.L1980:
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
	bne	.L2029
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
.L1963:
	ldr	r3, [r6, #48]
	mov	r1, #0
	mov	r2, #24
	sub	r0, fp, #228
	blx	r3
	ldr	r3, [r7, #168]
	ldr	r1, .L2039
	cmp	r3, #0
	beq	.L1968
	ldr	r2, [r7, #184]
	cmp	r2, #0
	beq	.L1968
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
.L1968:
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
	ldr	r1, [r5, r4, asl #2]
	mov	r2, #22
	ldr	ip, .L2039+24
	mov	lr, #30
	mov	r0, r4
	str	r10, [r1, #36]
	ldr	r3, [r5, r4, asl #2]
	str	r8, [r1, #1164]
	movw	r1, #51256
	movt	r1, 6
	str	r4, [r3]
	str	r10, [r3, #604]
	str	r9, [r3, #1192]
	ldr	r3, [r5, r4, asl #2]
	ldr	r10, [r7]
	str	r10, [r3, #32]
	ldr	r3, [r5, r4, asl #2]
	add	r10, r3, #475136
	str	r2, [r3, #568]
	str	r2, [r10, #1344]
	str	r9, [r3, #28]
	ldr	r3, [r5, r4, asl #2]
	ldr	r10, [r7, #224]
	add	r2, r3, #475136
	add	r1, r3, r1
	str	r10, [r2, #1320]
	add	r2, r3, #1536
	str	lr, [r3, #1536]
	add	r2, r2, #8
	str	r2, [ip, r4, asl #3]
	ldr	r2, [r7, #216]
	ldr	r10, .L2039+8
	str	r2, [r3, #1616]
	ldr	r2, [r7, #220]
	str	r2, [r3, #1620]
	bl	FSP_EnableInstance
	subs	r2, r0, #0
	bne	.L2030
	mov	r0, r4
	mov	r9, r2
	str	r2, [fp, #-264]
	bl	VCTRL_ResetChan
	ldr	r3, [r10, r4, asl #2]
	ldr	r2, [fp, #-264]
	ldr	lr, [fp, #-244]
	add	r1, r3, #471040
	ldr	ip, [fp, #-240]
	ldr	r0, [fp, #-236]
	str	lr, [r3, #332]
	str	ip, [r3, #336]
	str	r0, [r3, #340]
	add	r3, r3, #475136
	str	r2, [r1, #1228]
	str	r2, [r1, #1232]
	str	r2, [r1, #1240]
	str	r2, [r1, #1244]
	str	r2, [r1, #1236]
	str	r2, [r1, #1248]
	ldr	r1, [r7, #192]
	str	r2, [r3, #1276]
	str	r1, [r3, #1284]
	ldr	r1, [r7, #228]
	str	r2, [r3, #1340]
	str	r1, [r3, #1336]
.L1973:
	mov	r7, r9, asl #6
	ldr	r0, [r5, r4, asl #2]
	add	r7, r7, r9, lsl #3
	movw	r3, #13544
	movt	r3, 7
	add	r3, r7, r3
	add	r0, r0, r3
	mov	r2, #72
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	ldr	r1, [r5, r4, asl #2]
	add	r9, r9, #1
	movw	r3, #13544
	add	r7, r1, r7
	movt	r3, 7
	add	r0, r7, #471040
	add	r3, r7, r3
	cmp	r9, #32
	mov	r2, #255
	ldr	r7, .L2039+8
	str	r2, [r3]
	str	r2, [r3, #4]
	ldr	r10, .L2039
	str	r2, [r0, #1264]
	bne	.L1973
	movw	r0, #15848
	ldr	r3, [r10, #48]
	mov	r2, #1248
	movt	r0, 7
	add	r0, r1, r0
	mov	r1, #0
	blx	r3
	ldr	r0, [r7, r4, asl #2]
	ldr	r3, [r10, #48]
	mov	r2, #24
	add	r0, r0, #475136
	mov	r1, #0
	add	r0, r0, #712
	blx	r3
	ldr	r3, [r7, r4, asl #2]
	ldr	r10, [fp, #-156]
	mov	r7, #0
	ldr	r9, [fp, #-132]
	add	ip, r3, #442368
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
	str	r7, [ip, #2136]
	ldr	ip, .L2039+28
	ldr	r9, [r3, #1448]
	add	ip, ip, r4, lsl #2
	cmp	r9, #1
	str	r7, [ip, #768]
	beq	.L1974
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
.L2020:
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
	add	r2, r3, #425984
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
	add	r5, r5, #475136
	str	r0, [r5, #1292]
	mov	r0, #0
	blx	r3
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1950:
	mov	r3, #0
	mov	r0, #0
	mov	r1, #0
	str	r3, [fp, #-164]
	str	r3, [fp, #-148]
	str	r3, [fp, #-244]
	strd	r0, [fp, #-156]
	b	.L1954
.L1974:
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
	b	.L2020
.L1944:
	ldr	r3, [r9, #52]
	mov	r2, #24
	add	r1, r7, #120
	sub	r0, fp, #116
	blx	r3
	ldr	r2, [fp, #-100]
	ldr	r3, [fp, #-248]
	cmp	r2, r3
	blt	.L2031
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_AddMemRecord
	b	.L1947
.L1958:
	ldr	r3, [r1, #52]
	mov	r2, #24
	add	r1, r7, #96
	sub	r0, fp, #140
	blx	r3
	ldrd	r0, [fp, #-132]
	orrs	r3, r0, r1
	beq	.L1964
	ldr	r2, [fp, #-124]
	ldr	r3, [fp, #-252]
	cmp	r2, r3
	blt	.L1964
	mov	r1, r0
	ldr	r0, [fp, #-140]
	bl	MEM_AddMemRecord
	b	.L1963
.L1983:
	sub	r1, fp, #260
	mov	r0, #1
	bl	PDT_GetAttribute
	ldr	r3, [fp, #-260]
	cmp	r3, #1
	cmpne	r4, #15
	ble	.L1941
	mov	r2, r4
	ldr	r1, .L2039+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2014
.L1949:
	ldr	r3, [r1, #52]
	mov	r2, #24
	sub	r0, fp, #164
	add	r1, r7, #72
	blx	r3
	ldr	r3, [r7, #192]
	ldr	r2, [fp, #-148]
	cmp	r3, #1
	beq	.L1956
	ldr	r3, [fp, #-256]
	cmp	r2, r3
	blt	.L2032
.L1956:
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_AddMemRecord
	b	.L1954
.L2029:
	ldr	r3, [fp, #-236]
	cmp	r3, #1
	beq	.L2033
.L1960:
	ldr	r3, [fp, #-244]
	cmp	r3, #1
	beq	.L2034
.L1961:
	movw	r2, #1679
	ldr	r1, .L2039+36
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2021
.L2028:
	ldr	r3, [fp, #-236]
	cmp	r3, #1
	beq	.L2035
.L1952:
	movw	r2, #1743
	ldr	r1, .L2039+40
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2021
.L2030:
	mov	r2, r4
	ldr	r1, .L2039+44
	mov	r0, #1
	sub	r5, fp, #44
	bl	dprint_vfmw
	mov	r0, r4
	bl	FSP_DisableInstance
	mov	r0, r4
	bl	CloseUsdPool_WithMem
	ldr	r3, [r10, r4, asl #2]
	movw	r2, #13544
	mov	r0, r4
	movt	r2, 7
	add	r2, r3, r2
	str	r2, [fp, #-192]
	add	r1, r3, #475136
	ldr	r2, [r3, #340]
	ldr	ip, [r3, #332]
	ldr	lr, [r1, #1284]
	str	r2, [fp, #-172]
	ldr	r2, [r3, #336]
	str	lr, [fp, #-184]
	ldr	r6, [r1, #1320]
	add	r1, r3, #236
	str	ip, [fp, #-180]
	str	r1, [fp, #-204]
	str	r2, [fp, #-176]
	add	r2, r3, #260
	str	r9, [r10, r4, asl #2]
	str	r2, [fp, #-200]
	add	r2, r3, #284
	add	r3, r3, #308
	str	r2, [fp, #-196]
	str	r3, [r5, #-144]!
	bl	VDMDRV_ClearChanIsDec
	ldr	r3, .L2039
	mov	r0, r9
	ldr	r3, [r3, #16]
	blx	r3
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_DelRecordEsBuf.isra.5
	sub	r1, fp, #204
	mov	r0, r4
	bl	VCTRL_FreeChanResource
	b	.L2021
.L2027:
	mov	r0, r9
	movw	r2, #1800
	ldr	r1, .L2039+48
	bl	dprint_vfmw
	b	.L2021
.L1964:
	ldr	r3, [fp, #-236]
	cmp	r3, #1
	beq	.L2036
.L1966:
	ldr	r3, [fp, #-244]
	cmp	r3, #1
	beq	.L2037
.L1967:
	movw	r2, #1707
	ldr	r1, .L2039+52
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2021
.L2034:
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-148]
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_DelMemRecord
	b	.L1961
.L2033:
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_DelMemRecord
	b	.L1960
.L2031:
	movw	r2, #1816
	ldr	r1, .L2039+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2021
.L2035:
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_DelMemRecord
	b	.L1952
.L2032:
	ldr	r1, [fp, #-236]
	cmp	r1, #1
	beq	.L2038
.L1957:
	str	r3, [sp]
	mov	r0, #1
	mov	r3, r2
	ldr	r1, .L2039+60
	movw	r2, #1774
	bl	dprint_vfmw
	b	.L2021
.L2037:
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-148]
	ldr	r1, [fp, #-156]
	ldr	r0, [fp, #-164]
	bl	MEM_DelMemRecord
	b	.L1967
.L2036:
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_DelMemRecord
	b	.L1966
.L2038:
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [fp, #-100]
	ldr	r1, [fp, #-108]
	ldr	r0, [fp, #-116]
	bl	MEM_DelMemRecord
	ldr	r2, [fp, #-148]
	ldr	r3, [fp, #-256]
	b	.L1957
.L2040:
	.align	2
.L2039:
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
	@ args = 0, pretend = 0, frame = 88
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #100)
	sub	sp, sp, #100
	subs	r6, r1, #0
	mov	r7, r0
	ldreq	ip, .L2110
	moveq	r0, r6
	movweq	r3, #2613
	beq	.L2098
	cmp	r7, #31
	ldrhi	ip, .L2110+4
	movwhi	r3, #2614
	bhi	.L2099
	ldr	r8, .L2110+8
	ldr	r3, [r8, r7, asl #2]
	cmp	r3, #0
	beq	.L2100
	ldr	r3, [r3, #4]
	cmp	r3, #1
	bne	.L2101
	bl	VCTRL_CheckChanWH
	subs	r10, r0, #0
	bne	.L2102
	ldr	r4, .L2110+12
	add	r1, r4, #896
	bl	PDT_GetAttribute
	ldr	r3, [r4, #916]
	ldr	r2, [r6, #8]
	cmp	r3, #21
	bhi	.L2049
	cmp	r3, r2
	beq	.L2050
	add	r3, r4, #916
	add	r0, r4, #1040
.L2052:
	ldr	r1, [r3, #4]!
	cmp	r1, #21
	bhi	.L2049
	cmp	r1, r2
	beq	.L2050
	cmp	r3, r0
	bne	.L2052
.L2050:
	cmp	r2, #8
	mov	r3, #0
	str	r3, [fp, #-116]
	beq	.L2103
.L2053:
	cmp	r2, #9
	beq	.L2104
.L2078:
	cmp	r2, #5
	mov	r3, #0
	str	r3, [fp, #-116]
	beq	.L2105
.L2079:
	mov	r1, r6
	mov	r0, r7
	bl	VCTRL_CmpConfigParameter
	subs	r3, r0, #0
	beq	.L2106
	ldr	r9, .L2110+16
	mov	r2, #148
	ldr	r0, [r8, r7, asl #2]
	mov	r1, r6
	ldr	r3, [r9, #52]
	add	r0, r0, #44
	blx	r3
	ldr	ip, [r6, #24]
	ldr	r3, [r8, r7, asl #2]
	mov	r2, #72
	mov	r1, #0
	sub	r0, fp, #116
	str	ip, [r3, #20]
	ldr	r3, [r8, r7, asl #2]
	ldr	ip, [r6, #8]
	ldr	r4, [r9, #48]
	str	ip, [r3, #568]
	ldr	ip, [r6, #100]
	str	ip, [r3, #1456]
	blx	r4
	ldr	r3, [r8, r7, asl #2]
	ldr	r3, [r3, #356]
	mov	r0, r3
	str	r3, [fp, #-104]
	bl	MEM_Phy2Vir
	ldr	r3, [r8, r7, asl #2]
	ldr	r1, [r6, #84]
	mov	r2, #49152
	ldr	ip, [r6, #8]
	movt	r2, 63683
	cmp	r1, #1
	ldr	lr, [r6, #24]
	str	r0, [fp, #-116]
	ldr	r0, [r3, #368]
	addeq	r3, r3, #475136
	str	r2, [fp, #-96]
	addne	r3, r3, #475136
	ldreq	r2, [r6, #136]
	movne	r2, #0
	str	r0, [fp, #-100]
	str	ip, [fp, #-108]
	ldreq	r0, [r6, #96]
	ldreq	ip, [r6, #92]
	streq	r1, [fp, #-68]
	streq	r0, [fp, #-56]
	streq	ip, [fp, #-60]
	strb	lr, [fp, #-112]
	str	r2, [r3, #1332]
	ldr	r3, [r6, #88]
	ldr	r2, [r6, #8]
	cmp	r3, #0
	ldr	r1, [r6, #80]
	movne	r3, #1
	strne	r3, [fp, #-64]
	mov	r3, #0
	cmp	r2, r3
	str	r3, [fp, #-80]
	str	r1, [fp, #-72]
	bne	.L2107
.L2097:
	ldr	r3, [r6, #52]
.L2064:
	ldr	r4, .L2110+20
	mov	r1, #0
	str	r3, [fp, #-76]
	add	r5, r4, #128
	mov	r3, r4
.L2066:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	addne	r1, r1, #1
	cmp	r3, r5
	bne	.L2066
	ldr	r3, .L2110+24
	cmp	r1, #1
	str	r3, [fp, #-132]
	ble	.L2108
.L2067:
	mov	r3, #0
	str	r3, [fp, #-76]
.L2068:
	ldr	r3, [r8, r7, asl #2]
	mov	r2, #12
	sub	r0, fp, #92
	ldrsb	r3, [r3, #44]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [fp, #-76]
	add	r3, r6, #12
	str	r3, [fp, #-128]
	mov	r1, r3
	ldr	r3, [r9, #52]
	blx	r3
	sub	r1, fp, #116
	mov	r0, r7
	bl	SM_Config
	ldr	r3, [r9, #48]
	sub	r0, fp, #120
	mov	r2, #1
	mov	r1, #0
	blx	r3
	ldr	r3, [r6, #84]
	cmp	r3, #1
	beq	.L2109
.L2070:
	ldr	r3, [r8, r7, asl #2]
	mov	lr, #1
	ldr	r2, [fp, #-132]
	ldr	r1, [r3, #292]
	ldr	ip, [r3, #300]
	ldr	r0, [r3, #348]
	str	r1, [r3, #1168]
	ldr	r1, [r3, #352]
	str	ip, [r3, #1172]
	str	r0, [r3, #592]
	str	r1, [r3, #596]
	ldr	ip, [r3, #372]
	ldr	r0, [r3, #376]
	ldr	r1, [r3, #380]
	str	ip, [r3, #608]
	str	r0, [r3, #612]
	str	r1, [r3, #616]
	ldr	ip, [r3, #384]
	ldr	r0, [r3, #388]
	ldr	r1, [r3, #392]
	str	ip, [r3, #620]
	add	ip, r3, #475136
	str	r0, [r3, #624]
	str	r1, [r3, #628]
	ldr	r1, [r6, #28]
	ldr	r2, [r2, #72]
	str	r1, [r3, #580]
	cmp	r2, #7
	ldr	r1, [r6, #28]
	str	r1, [r3, #576]
	ldr	r1, [r6, #36]
	str	r1, [r3, #584]
	ldreq	r2, [r6, #40]
	str	r2, [r3, #600]
	mov	r2, #0
	ldr	r1, [r6, #44]
	str	r1, [r3, #588]
	mov	r1, r6
	ldr	r0, [r6, #132]
	str	r0, [r3, #1220]
	ldr	r0, [r6, #140]
	str	lr, [r3, #1224]
	str	lr, [r3, #1228]
	str	r0, [r3, #1524]
	ldr	r0, [r6, #72]
	rsb	r0, lr, r0
	clz	r0, r0
	mov	r0, r0, lsr #5
	str	r0, [r3, #1204]
	ldr	r0, [r6, #76]
	str	r0, [r3, #1208]
	ldr	r0, [r6, #48]
	str	r0, [r3, #1212]
	ldr	r0, [fp, #-76]
	str	r2, [r3, #1496]
	str	r2, [r3, #1516]
	str	r0, [r3, #1216]
	mov	r0, r7
	str	r2, [r3, #1532]
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	strb	r3, [ip, #1280]
	bl	VCTRL_ConfigChanCompress
	ldr	r0, [r8, r7, asl #2]
	ldr	r3, [r9, #52]
	mov	r2, #12
	add	r0, r0, #1136
	ldr	r1, [fp, #-128]
	add	r0, r0, #4
	ldr	r9, .L2110+8
	blx	r3
	ldr	ip, [r8, r7, asl #2]
	add	r3, ip, #475136
	ldr	r0, [ip, #568]
	ldr	r2, [r3, #1344]
	cmp	r2, r0
	beq	.L2072
	mov	r0, r7
	bl	VCTRL_ResetChan
	ldr	r3, [r6, #8]
	ldr	ip, [r9, r7, asl #2]
	cmp	r3, #20
	beq	.L2073
	ldr	r0, [ip, #568]
	add	r3, ip, #475136
.L2072:
	ldr	r1, .L2110+28
	ldr	r2, .L2110+32
	str	r0, [r3, #1344]
.L2077:
	ldr	r3, [r4, #4]!
	add	r1, r1, #4
	add	r2, r2, #4
	cmp	r3, #0
	streq	r3, [r1, #-4]
	ldrne	r0, [r3, #20]
	strne	r0, [r1, #-4]
	ldrne	r3, [r3, #20]
	cmp	r5, r4
	str	r3, [r2, #-4]
	bne	.L2077
	ldr	r0, .L2110+28
	bl	VDMDRV_SetPriority
	mov	r0, r7
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2106:
	ldr	r1, .L2110+36
	mov	r10, r3
	bl	dprint_vfmw
.L2094:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2049:
	ldr	r1, .L2110+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r10, #0
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2107:
	cmp	r2, #16
	beq	.L2097
	b	.L2064
.L2104:
	sub	r0, fp, #116
	bl	REAL9DEC_Support
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	ldrne	r2, [r6, #8]
	bne	.L2078
.L2054:
	mvn	r10, #0
	b	.L2094
.L2103:
	sub	r0, fp, #116
	bl	REAL8DEC_Support
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	beq	.L2054
	ldr	r2, [r6, #8]
	b	.L2053
.L2105:
	sub	r0, fp, #116
	bl	DIVX3DEC_Support
	ldr	r3, [fp, #-116]
	cmp	r3, #0
	bne	.L2079
	b	.L2054
.L2101:
	ldr	ip, .L2110+44
	movw	r3, #2616
.L2099:
	ldr	r2, .L2110+48
	mov	r0, #0
	ldr	r1, .L2110+52
	mvn	r10, #0
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2108:
	ldr	r3, [r3, #88]
	cmp	r3, #0
	bne	.L2068
	b	.L2067
.L2109:
	sub	r1, fp, #120
	mov	r0, r7
	strb	r3, [fp, #-120]
	bl	FSP_ConfigAttribute
	b	.L2070
.L2102:
	ldr	r1, .L2110+56
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L2094
.L2073:
	ldr	r3, [ip, #360]
	mov	r0, r7
	ldr	r2, [ip, #1272]
	ldr	r1, [ip, #1268]
	ldr	ip, [ip, #364]
	str	ip, [sp]
	bl	VCTRL_PartitionMemForStdUser
	cmp	r0, #0
	bne	.L2074
	ldr	ip, [r9, r7, asl #2]
	add	r3, ip, #475136
	ldr	r0, [ip, #568]
	b	.L2072
.L2100:
	ldr	ip, .L2110+60
	mov	r0, r3
	movw	r3, #2615
.L2098:
	ldr	r2, .L2110+48
	mvn	r10, #0
	ldr	r1, .L2110+52
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L2094
.L2074:
	mov	r0, #1
	ldr	r1, .L2110+64
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L2094
.L2111:
	.align	2
.L2110:
	.word	.LC218
	.word	.LC99
	.word	.LANCHOR1
	.word	.LANCHOR3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1-4
	.word	.LANCHOR2
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
	ldr	r1, .L2116
	mov	r0, #32
	bic	r5, r4, #-16777216
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2116+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	beq	.L2115
	mov	r2, r4
	ldr	r1, .L2116+8
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2115:
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-36]
	bl	VCTRL_ConfigChan
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2117:
	.align	2
.L2116:
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
	ldr	r1, .L2120
	mov	r0, #32
	bic	r5, r4, #-16777216
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2120+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2118
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-136]
	bl	VCTRL_ConfigChan
.L2118:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2121:
	.align	2
.L2120:
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
	ldr	r1, .L2126
	mov	r0, #32
	and	r5, r4, #7
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2126+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	beq	.L2125
	mov	r2, r4
	ldr	r1, .L2126+8
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2125:
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-132]
	bl	VCTRL_ConfigChan
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2127:
	.align	2
.L2126:
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
	ldr	r1, .L2130
	mov	r0, #32
	and	r5, r4, #3
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2130+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2128
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-128]
	bl	VCTRL_ConfigChan
.L2128:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2131:
	.align	2
.L2130:
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
	ldr	r1, .L2134
	mov	r0, #32
	bic	r5, r4, #-16777216
	mov	r4, r4, lsr #24
	mov	r3, r5
	mov	r2, r4
	bl	dprint_vfmw
	ldr	r3, .L2134+4
	mov	r2, #148
	mov	r1, #0
	sub	r0, fp, #168
	ldr	r3, [r3, #48]
	blx	r3
	sub	r1, fp, #168
	mov	r0, r4
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L2132
	sub	r1, fp, #168
	mov	r0, r4
	str	r5, [fp, #-140]
	bl	VCTRL_ConfigChan
.L2132:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2135:
	.align	2
.L2134:
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
	ldr	r1, .L2137
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2138:
	.align	2
.L2137:
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
	ldr	r5, .L2154
	mov	r4, r0
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	cmp	r4, #31
	ldrhi	ip, .L2154+4
	movhi	r3, #2208
	bhi	.L2149
	ldr	r6, .L2154+8
	ldr	r7, [r6, r4, asl #2]
	cmp	r7, #0
	beq	.L2150
	ldr	r8, [r7, #4]
	cmp	r8, #1
	bne	.L2151
	mov	r0, #0
	str	r0, [r7, #8]
	ldr	r3, [r5, #16]
	blx	r3
	mov	r0, r4
	bl	SCDDRV_IsChanDec
	cmp	r0, #0
	bne	.L2152
.L2144:
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r2, .L2154+12
	ldr	r3, [r5, #12]
	mov	r8, #0
	mov	r0, #4
	ldr	r7, .L2154
	str	r8, [r2, r4, asl #2]
	blx	r3
	mov	r0, r4
	bl	VCTRL_StopChan
	ldr	r3, [r7, #16]
	subs	r5, r0, #0
	mov	r0, #4
	bne	.L2153
	blx	r3
	mov	r0, r4
	bl	VCTRL_ResetChan
	bl	VDMDRV_ParamInit
	ldr	r3, .L2154+16
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
	ldr	r0, .L2154+20
	add	r2, r3, #475136
	str	r5, [r6, r4, asl #2]
	ldr	ip, [r3, #340]
	add	r6, r6, r4, lsl #4
	ldr	r1, [r2, #1284]
	ldr	r8, [r2, #1320]
	movw	r2, #13544
	movt	r2, 7
	add	r2, r3, r2
	str	r1, [fp, #-56]
	str	r2, [fp, #-64]
	ldr	r1, [r3, #332]
	ldr	r2, [r3, #336]
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
.L2141:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2152:
	mov	r0, r4
	ldr	r7, [r5, #132]
	bl	SCDDRV_IsChanDec
	mov	r2, #500
	clz	r1, r0
	mov	r0, r8
	mov	r1, r1, lsr #5
	blx	r7
	b	.L2144
.L2151:
	ldr	ip, .L2154+24
	movw	r3, #2222
.L2149:
	ldr	r2, .L2154+28
	mov	r0, #0
	ldr	r1, .L2154+32
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2153:
	blx	r3
	ldr	r3, [r7, #16]
	mov	r0, r8
	blx	r3
	mvn	r0, #0
	b	.L2141
.L2150:
	ldr	ip, .L2154+36
	movw	r3, #2215
	ldr	r2, .L2154+28
	mov	r0, r7
	ldr	r1, .L2154+32
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #16]
	mov	r0, r7
	blx	r3
	mvn	r0, #0
	b	.L2141
.L2155:
	.align	2
.L2154:
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
	ldr	r6, .L2174
	ldr	r3, [r6, #128]
	cmp	r3, #1
	bne	.L2163
	sub	r5, r6, #4
	mov	r4, #0
.L2159:
	ldr	r3, [r5, #4]!
	mov	r0, r4
	add	r4, r4, #1
	cmp	r3, #0
	beq	.L2158
	bl	VCTRL_DestroyChan
.L2158:
	cmp	r4, #32
	bne	.L2159
	bl	FSP_Exit
	ldr	r3, [r6, #132]
	mov	r2, #3
	ldr	r5, .L2174+4
	cmp	r3, #0
	str	r2, [r6, #136]
	beq	.L2161
	mov	r0, #10
	ldr	r3, [r5, #120]
	mov	r4, #49
	blx	r3
	b	.L2162
.L2173:
	ldr	r3, [r5, #120]
	blx	r3
	subs	r4, r4, #1
	beq	.L2161
.L2162:
	ldr	r3, [r6, #132]
	mov	r0, #10
	cmp	r3, #0
	bne	.L2173
.L2161:
	ldr	r3, [r5, #48]
	mov	r2, #128
	mov	r1, #0
	ldr	r0, .L2174+8
	blx	r3
	ldr	r0, .L2174+12
	bl	CloseDrivers
	mov	r3, #0
	mov	r0, r3
	str	r3, [r6, #128]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2163:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2175:
	.align	2
.L2174:
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
	ldr	r1, .L2177
	mov	r3, r0
	mov	r0, #32
	bl	dprint_vfmw
	mov	r0, r4
	bl	VCTRL_ResetChan
	mov	r2, r4
	ldr	r1, .L2177+4
	mov	r3, r0
	mov	r0, #32
	bl	dprint_vfmw
	mov	r0, r4
	bl	VCTRL_StartChan
	mov	r2, r4
	ldr	r1, .L2177+8
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2178:
	.align	2
.L2177:
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
	ldr	r1, .L2180
	mov	r3, r0
	mov	r0, #32
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L2181:
	.align	2
.L2180:
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
	beq	.L2183
	cmp	r1, #0
	moveq	r4, #2
	movne	r4, #0
.L2183:
	ldr	r3, .L2197
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L2193
	mov	r1, r4
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDH_Require_DspCode
.L2193:
	ldr	r6, .L2197+4
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L2194
	mov	r0, #0
	blx	r3
.L2186:
	ldr	r3, [r6, #20]
	cmp	r3, #0
	beq	.L2195
	mov	r0, #0
	blx	r3
.L2188:
	ldr	r3, [r6, #12]
	cmp	r3, #0
	beq	.L2196
	mov	r0, #0
	blx	r3
.L2190:
	mov	r1, r4
	mov	r0, #0
	bl	SCDDRV_LoadDspCode
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_CloseHardware
.L2194:
	mov	r0, r3
	movw	r2, #2876
	ldr	r1, .L2197+8
	bl	dprint_vfmw
	b	.L2186
.L2195:
	mov	r0, r3
	movw	r2, #2877
	ldr	r1, .L2197+8
	bl	dprint_vfmw
	b	.L2188
.L2196:
	mov	r0, r3
	movw	r2, #2878
	ldr	r1, .L2197+8
	bl	dprint_vfmw
	b	.L2190
.L2198:
	.align	2
.L2197:
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
	ldr	r3, .L2225
	mov	r5, r0
	ldr	r3, [r3, r0, asl #2]
	ldr	r1, [r3, #568]
	cmp	r1, #0
	movne	r3, #1
	movne	r6, #0
	ldreq	r6, [r3, #1212]
	clzeq	r3, r6
	moveq	r3, r3, lsr #5
.L2200:
	cmp	r1, #6
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	beq	.L2221
.L2212:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2221:
	ldr	r7, .L2225+4
	ldr	r4, [r7, #-640]
	cmp	r4, #0
	bne	.L2201
	sub	r3, r7, #640
	sub	r2, r7, #516
	b	.L2202
.L2223:
	cmp	r3, r2
	beq	.L2222
.L2202:
	ldr	r4, [r3, #4]!
	cmp	r4, #0
	beq	.L2223
.L2201:
	cmp	r4, #1
	beq	.L2224
	cmp	r1, #6
	beq	.L2212
	ldr	r1, .L2225+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2222:
	mov	r0, r5
	add	r5, r7, r5, lsl #2
	bl	VCTRL_InitDspCode
	cmp	r6, #1
	mov	r0, r4
	streq	r6, [r5, #-640]
	movne	r3, #2
	strne	r3, [r5, #-640]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2224:
	cmp	r6, #1
	beq	.L2212
	ldr	r1, .L2225+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2226:
	.align	2
.L2225:
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
	ldr	r3, .L2228
	ldr	r3, [r3, r0, asl #2]
	add	r3, r3, #442368
	str	r1, [r3, #2136]
	ldmfd	sp, {fp, sp, pc}
.L2229:
	.align	2
.L2228:
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
	ldr	r3, .L2231
	ldr	r3, [r3, r0, asl #2]
	add	r3, r3, #471040
	ldr	r0, [r3, #1228]
	ldmfd	sp, {fp, sp, pc}
.L2232:
	.align	2
.L2231:
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
	beq	.L2235
	bcc	.L2236
	cmp	r1, #2
	bne	.L2243
	ldr	r3, .L2244
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #768]
	cmp	r3, #1
	beq	.L2240
	mov	r3, #0
	str	r1, [r0, #768]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2243:
	mov	r3, #0
.L2234:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2236:
	ldr	r2, .L2244
	mov	r1, #0
	mov	r3, r1
	add	r0, r2, r0, lsl #2
	str	r1, [r0, #768]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2235:
	ldr	r3, .L2244
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #768]
	cmp	r3, #0
	bne	.L2240
	str	r1, [r0, #768]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L2240:
	mvn	r3, #0
	b	.L2234
.L2245:
	.align	2
.L2244:
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
	beq	.L2247
	ldr	r2, [r0, #12]
	ldr	r1, [r0, #24]
	ldr	r0, [r0, #32]
	bl	MEM_AddMemRecord
.L2247:
	ldr	r3, [r4, #4]
	cmp	r3, #255
	beq	.L2248
	ldr	r2, [r4, #16]
	ldr	r1, [r4, #40]
	ldr	r0, [r4, #48]
	bl	MEM_AddMemRecord
.L2248:
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
	ldr	r7, .L2290
	mov	r4, r0
	mov	r5, r1
	ldr	r1, [r1, #12]
	ldr	r3, [r7, r0, asl #2]
	add	r2, r3, #475136
	add	r3, r3, #471040
	ldr	r0, [r2, #704]
	cmp	r0, r1
	beq	.L2257
	ldr	ip, [r3, #1224]
	cmp	ip, #0
	beq	.L2285
.L2257:
	ldr	r3, [r3, #3616]
	cmp	r3, #0
	beq	.L2259
	ldr	r2, [r2, #736]
	cmp	r2, #0
	beq	.L2286
.L2259:
	ldr	r6, .L2290+4
	mov	r0, #8
	ldr	r3, [r6, #12]
	blx	r3
	ldr	r0, [r7, r4, asl #2]
	add	r2, r0, #471040
	ldr	r3, [r2, #1256]
	cmp	r3, #255
	beq	.L2267
	add	r2, r2, #1328
	mov	r1, #1
	b	.L2261
.L2288:
	add	r1, r1, #1
	cmp	r1, #32
	beq	.L2287
.L2261:
	ldr	ip, [r2]
	add	r2, r2, #72
	cmp	ip, #255
	bne	.L2288
.L2260:
	mov	r2, r1, asl #6
	movw	r3, #13544
	add	r1, r2, r1, lsl #3
	movt	r3, 7
	add	r3, r1, r3
	mov	r2, #72
	add	r0, r0, r3
	mov	r1, r5
	ldr	r8, [r6, #52]
	blx	r8
	ldr	r3, [r7, r4, asl #2]
	mov	r0, r5
	add	r3, r3, #475136
	ldr	r2, [r3, #736]
	add	r2, r2, #1
	str	r2, [r3, #736]
	bl	VCTRL_AddFrameBufMemoryRecord
	ldr	r3, [r7, r4, asl #2]
	add	r3, r3, #475136
	ldr	r3, [r3, #740]
	cmp	r3, #0
	bne	.L2289
.L2265:
	mov	r4, #0
.L2264:
	ldr	r3, [r6, #16]
	mov	r0, #8
	blx	r3
	mov	r0, r4
.L2280:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2286:
	ldr	r3, [r5, #8]
	cmp	r3, #255
	bne	.L2259
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	movw	r3, #8182
	ldr	r2, .L2290+8
	ldr	r1, .L2290+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2280
.L2287:
	mov	r3, r4
	ldr	r2, .L2290+8
	ldr	r1, .L2290+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2264
.L2289:
	mov	r1, r5
	mov	r0, r4
	bl	FSP_SetSingleFrameBuf
	cmp	r0, #0
	beq	.L2265
	mov	r3, r4
	ldr	r2, .L2290+8
	ldr	r1, .L2290+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r4, #0
	b	.L2264
.L2267:
	mov	r1, #0
	b	.L2260
.L2285:
	str	r0, [sp, #4]
	movw	r3, #8172
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L2290+8
	ldr	r1, .L2290+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2280
.L2291:
	.align	2
.L2290:
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
	ldr	r5, .L2304
	mov	r7, r0, asl #2
	mov	r4, r0
	add	r3, r5, r7
	ldr	r10, [r3, #768]
	cmp	r10, #0
	bne	.L2293
	ldr	r8, .L2304+4
	mov	ip, #1
	mov	r2, #72
	str	ip, [r3, #768]
	sub	r0, fp, #116
	ldr	r9, .L2304+8
	ldr	r3, [r8, #52]
	blx	r3
	sub	r1, fp, #116
	mov	r0, r4
	bl	VCTRL_SetSingleFrameBufToChan
	ldr	r3, [r9, r4, asl #2]
	subs	r6, r0, #0
	bne	.L2302
.L2295:
	add	r3, r3, #442368
	mov	r2, #2
	ldr	r1, .L2304+12
	mov	r0, #31
	str	r2, [r3, #2136]
	bl	dprint_vfmw
	ldr	r3, [r9, r4, asl #2]
	ldr	r9, .L2304+8
	add	r3, r3, #475136
	ldr	r3, [r3, #1340]
	cmp	r3, #1
	beq	.L2303
.L2296:
	add	r5, r5, r7
	mov	r0, r6
	mov	r3, #0
	str	r3, [r5, #768]
.L2301:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2302:
	add	r2, r3, #471040
	ldr	r2, [r2, #1228]
	cmp	r2, #0
	beq	.L2295
	mov	r2, r4
	ldr	r1, .L2304+16
	mov	r0, r10
	bl	dprint_vfmw
	ldr	r3, [r9, r4, asl #2]
	mov	r1, #3
	add	r2, r3, #442368
	str	r1, [r2, #2136]
	b	.L2295
.L2303:
	ldr	r3, [r8, #128]
	mov	r0, #0
	blx	r3
	ldr	r3, [r9, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #475136
	str	r2, [r3, #1340]
	b	.L2296
.L2293:
	mov	r3, r0
	ldr	r2, .L2304+20
	ldr	r1, .L2304+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2301
.L2305:
	.align	2
.L2304:
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
	ldr	r3, .L2311
	mov	r5, r0
	mov	r6, r1
	mov	r7, r2
	sub	r0, fp, #52
	ldr	r3, [r3, #48]
	mov	r2, #24
	mov	r1, #0
	blx	r3
	ldr	r3, .L2311+4
	ldr	r4, [r3, #52]
	cmp	r4, #0
	beq	.L2307
	ldr	ip, .L2311+8
	sub	r3, fp, #52
	str	r3, [sp, #4]
	mov	r2, r7
	mov	r1, r6
	mov	r0, r5
	ldr	ip, [ip, r5, asl #2]
	mov	r3, #0
	add	ip, ip, #475136
	ldr	ip, [ip, #1344]
	str	ip, [sp]
	blx	r4
.L2307:
	ldr	r0, [fp, #-48]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2312:
	.align	2
.L2311:
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
	ldr	r3, .L2314
	mov	r2, #1
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #1172]
	ldmfd	sp, {fp, sp, pc}
.L2315:
	.align	2
.L2314:
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
	ldr	r3, .L2317
	mov	r2, #0
	add	r0, r3, r0, lsl #2
	str	r2, [r0, #1172]
	ldmfd	sp, {fp, sp, pc}
.L2318:
	.align	2
.L2317:
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
	ldr	r3, .L2320
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #1172]
	ldmfd	sp, {fp, sp, pc}
.L2321:
	.align	2
.L2320:
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
	.type	__func__.52808, %object
	.size	__func__.52808, 18
__func__.52808:
	.ascii	"VCTRL_EventReport\000"
	.space	2
	.type	__func__.53974, %object
	.size	__func__.53974, 24
__func__.53974:
	.ascii	"VCTRL_SetLastFrameState\000"
	.type	__func__.52747, %object
	.size	__func__.52747, 20
__func__.52747:
	.ascii	"VCTRL_RecordPosTime\000"
	.type	__func__.52752, %object
	.size	__func__.52752, 17
__func__.52752:
	.ascii	"VCTRL_RecordData\000"
	.space	3
	.type	__func__.52799, %object
	.size	__func__.52799, 23
__func__.52799:
	.ascii	"VCTRL_SetMoreGapEnable\000"
	.space	1
	.type	__func__.52820, %object
	.size	__func__.52820, 18
__func__.52820:
	.ascii	"VCTRL_SetCallBack\000"
	.space	2
	.type	__func__.52860, %object
	.size	__func__.52860, 25
__func__.52860:
	.ascii	"VCTRL_SetStreamInterface\000"
	.space	3
	.type	__func__.52865, %object
	.size	__func__.52865, 29
__func__.52865:
	.ascii	"VCTRL_SetSendStreamAgainFlag\000"
	.space	3
	.type	__func__.52869, %object
	.size	__func__.52869, 29
__func__.52869:
	.ascii	"VCTRL_GetSendStreamAgainFlag\000"
	.space	3
	.type	__func__.52879, %object
	.size	__func__.52879, 20
__func__.52879:
	.ascii	"VCTRL_GetStreamSize\000"
	.type	__func__.52886, %object
	.size	__func__.52886, 20
__func__.52886:
	.ascii	"VCTRL_CheckFreshRaw\000"
	.type	__func__.52893, %object
	.size	__func__.52893, 20
__func__.52893:
	.ascii	"VCTRL_CheckFreshSeg\000"
	.type	__func__.52898, %object
	.size	__func__.52898, 25
__func__.52898:
	.ascii	"VCTRL_SetDiscardPicParam\000"
	.space	3
	.type	__FUNCTION__.52926, %object
	.size	__FUNCTION__.52926, 29
__FUNCTION__.52926:
	.ascii	"VCTRL_PartitionMemForStdUser\000"
	.space	3
	.type	__func__.52941, %object
	.size	__func__.52941, 21
__func__.52941:
	.ascii	"DelAllFrameMemRecord\000"
	.space	3
	.type	__func__.52951, %object
	.size	__func__.52951, 23
__func__.52951:
	.ascii	"VCTRL_FreeChanResource\000"
	.space	1
	.type	__func__.53077, %object
	.size	__func__.53077, 17
__func__.53077:
	.ascii	"VCTRL_GetChanCfg\000"
	.space	3
	.type	__func__.53138, %object
	.size	__func__.53138, 14
__func__.53138:
	.ascii	"VCTRL_SeekPts\000"
	.space	2
	.type	__func__.53171, %object
	.size	__func__.53171, 20
__func__.53171:
	.ascii	"VCTRL_ReleaseStream\000"
	.type	__func__.53191, %object
	.size	__func__.53191, 24
__func__.53191:
	.ascii	"VCTRL_ImageOutputEnable\000"
	.type	__func__.53230, %object
	.size	__func__.53230, 25
__func__.53230:
	.ascii	"VCTRL_TryToRelSpecialFrm\000"
	.space	3
	.type	__func__.53254, %object
	.size	__func__.53254, 19
__func__.53254:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__FUNCTION__.53262, %object
	.size	__FUNCTION__.53262, 19
__FUNCTION__.53262:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__func__.53269, %object
	.size	__func__.53269, 23
__func__.53269:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__FUNCTION__.53273, %object
	.size	__FUNCTION__.53273, 23
__FUNCTION__.53273:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__func__.53281, %object
	.size	__func__.53281, 23
__func__.53281:
	.ascii	"VCTRL_GetHDRConfigInfo\000"
	.space	1
	.type	__func__.53307, %object
	.size	__func__.53307, 18
__func__.53307:
	.ascii	"VCTRL_GetDecParam\000"
	.space	2
	.type	__func__.53391, %object
	.size	__func__.53391, 20
__func__.53391:
	.ascii	"VCTRL_ClearDecparam\000"
	.type	__func__.53420, %object
	.size	__func__.53420, 21
__func__.53420:
	.ascii	"VCTRL_VdmProcSedOnly\000"
	.space	3
	.type	__func__.53430, %object
	.size	__func__.53430, 21
__func__.53430:
	.ascii	"VCTRL_GetImageBuffer\000"
	.space	3
	.type	__func__.53453, %object
	.size	__func__.53453, 22
__func__.53453:
	.ascii	"VCTRL_ConfigFFFBSpeed\000"
	.space	2
	.type	__func__.53458, %object
	.size	__func__.53458, 20
__func__.53458:
	.ascii	"VCTRL_ConfigPVRInfo\000"
	.type	__func__.53462, %object
	.size	__func__.53462, 19
__func__.53462:
	.ascii	"VCTRL_IsChanActive\000"
	.space	1
	.type	__func__.53468, %object
	.size	__func__.53468, 13
__func__.53468:
	.ascii	"USERDEC_Init\000"
	.space	3
	.type	__func__.53487, %object
	.size	__func__.53487, 21
__func__.53487:
	.ascii	"VCTRL_GetUsrdecFrame\000"
	.space	3
	.type	__func__.53497, %object
	.size	__func__.53497, 14
__func__.53497:
	.ascii	"InitSyntaxCtx\000"
	.space	2
	.type	__func__.52829, %object
	.size	__func__.52829, 15
__func__.52829:
	.ascii	"VCTRL_OpenVfmw\000"
	.space	1
	.type	__FUNCTION__.53704, %object
	.size	__FUNCTION__.53704, 18
__FUNCTION__.53704:
	.ascii	"GetExtraRefFrmNum\000"
	.space	2
	.type	__FUNCTION__.53710, %object
	.size	__FUNCTION__.53710, 19
__FUNCTION__.53710:
	.ascii	"GetExtraDispFrmNum\000"
	.space	1
	.type	__FUNCTION__.53716, %object
	.size	__FUNCTION__.53716, 16
__FUNCTION__.53716:
	.ascii	"GetExtraCtrlCmd\000"
	.type	__func__.53650, %object
	.size	__func__.53650, 14
__func__.53650:
	.ascii	"DecChanSyntax\000"
	.space	2
	.type	__FUNCTION__.53651, %object
	.size	__FUNCTION__.53651, 14
__FUNCTION__.53651:
	.ascii	"DecChanSyntax\000"
	.space	2
	.type	__func__.53180, %object
	.size	__func__.53180, 24
__func__.53180:
	.ascii	"VCTRL_FindOccupiedFrame\000"
	.type	__func__.53201, %object
	.size	__func__.53201, 26
__func__.53201:
	.ascii	"VCTRL_ReportOccupiedFrame\000"
	.space	2
	.type	__func__.53681, %object
	.size	__func__.53681, 20
__func__.53681:
	.ascii	"VCTRL_GetChanImgNum\000"
	.type	__func__.52909, %object
	.size	__func__.52909, 19
__func__.52909:
	.ascii	"VCTRL_GetChanState\000"
	.space	1
	.type	__func__.53685, %object
	.size	__func__.53685, 19
__func__.53685:
	.ascii	"VCTRL_GetChanWidth\000"
	.space	1
	.type	__func__.53689, %object
	.size	__func__.53689, 20
__func__.53689:
	.ascii	"VCTRL_GetChanHeight\000"
	.type	__func__.53693, %object
	.size	__func__.53693, 22
__func__.53693:
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
	.type	__func__.53989, %object
	.size	__func__.53989, 22
__func__.53989:
	.ascii	"VCTRL_OutputLastFrame\000"
	.space	2
	.type	__func__.53366, %object
	.size	__func__.53366, 15
__func__.53366:
	.ascii	"VCTRL_PostProc\000"
	.space	1
	.type	__func__.53415, %object
	.size	__func__.53415, 18
__func__.53415:
	.ascii	"VCTRL_VdmPostProc\000"
	.space	2
	.type	__func__.54015, %object
	.size	__func__.54015, 21
__func__.54015:
	.ascii	"VCTRL_SvdecLastFrame\000"
	.space	3
	.type	__func__.53493, %object
	.size	__func__.53493, 21
__func__.53493:
	.ascii	"VCTRL_PutUsrdecFrame\000"
	.space	3
	.type	__func__.53056, %object
	.size	__func__.53056, 16
__func__.53056:
	.ascii	"VCTRL_StartChan\000"
	.type	__func__.53072, %object
	.size	__func__.53072, 15
__func__.53072:
	.ascii	"VCTRL_StopChan\000"
	.space	1
	.type	__func__.53165, %object
	.size	__func__.53165, 26
__func__.53165:
	.ascii	"VCTRL_ResetChanWithOption\000"
	.space	2
	.type	__func__.53244, %object
	.size	__func__.53244, 16
__func__.53244:
	.ascii	"VCTRL_ResetChan\000"
	.type	__func__.53123, %object
	.size	__func__.53123, 17
__func__.53123:
	.ascii	"VCTRL_ConfigChan\000"
	.space	3
	.type	__func__.53050, %object
	.size	__func__.53050, 18
__func__.53050:
	.ascii	"VCTRL_DestroyChan\000"
	.space	2
	.type	__func__.54110, %object
	.size	__func__.54110, 30
__func__.54110:
	.ascii	"VCTRL_SetSingleFrameBufToChan\000"
	.space	2
	.type	__func__.54122, %object
	.size	__func__.54122, 24
__func__.54122:
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
	.type	save_file_cnt.53852, %object
	.size	save_file_cnt.53852, 4
save_file_cnt.53852:
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
	.type	save_file_cnt.53846, %object
	.size	save_file_cnt.53846, 4
save_file_cnt.53846:
	.space	4
	.type	save_metadata_reorder_chan_num, %object
	.size	save_metadata_reorder_chan_num, 4
save_metadata_reorder_chan_num:
	.space	4
	.type	vfmw_save_metadata_file, %object
	.size	vfmw_save_metadata_file, 128
vfmw_save_metadata_file:
	.space	128
	.type	save_file_cnt.53840, %object
	.size	save_file_cnt.53840, 4
save_file_cnt.53840:
	.space	4
	.type	save_metadata_chan_num, %object
	.size	save_metadata_chan_num, 4
save_metadata_chan_num:
	.space	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 128
vfmw_save_seg_file:
	.space	128
	.type	save_file_cnt.53818, %object
	.size	save_file_cnt.53818, 4
save_file_cnt.53818:
	.space	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.space	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 128
vfmw_save_str_file:
	.space	128
	.type	save_file_cnt.53812, %object
	.size	save_file_cnt.53812, 4
save_file_cnt.53812:
	.space	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.space	4
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 128
vfmw_save_yuv_file:
	.space	128
	.type	save_file_cnt.53825, %object
	.size	save_file_cnt.53825, 4
save_file_cnt.53825:
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
	.type	FspInstInfo.52922, %object
	.size	FspInstInfo.52922, 2824
FspInstInfo.52922:
	.space	2824
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.space	4
	.type	last_rec_pos_time.53259, %object
	.size	last_rec_pos_time.53259, 128
last_rec_pos_time.53259:
	.space	128
	.type	last_rec_pos_time.53270, %object
	.size	last_rec_pos_time.53270, 128
last_rec_pos_time.53270:
	.space	128
	.type	MemArrange.53527, %object
	.size	MemArrange.53527, 1232
MemArrange.53527:
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
	.type	last_rec_pos_time.53645, %object
	.size	last_rec_pos_time.53645, 128
last_rec_pos_time.53645:
	.space	128
	.type	last_rec_pos_decparam_time.53646, %object
	.size	last_rec_pos_decparam_time.53646, 128
last_rec_pos_decparam_time.53646:
	.space	128
	.type	ChanPriTab.53595, %object
	.size	ChanPriTab.53595, 128
ChanPriTab.53595:
	.space	128
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 768
g_VfmwChanStat:
	.space	768
	.type	PrioArray.53055, %object
	.size	PrioArray.53055, 128
PrioArray.53055:
	.space	128
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 128
s_ChanControlState:
	.space	128
	.type	Capability.53119, %object
	.size	Capability.53119, 148
Capability.53119:
	.space	148
	.type	PrioArray.53118, %object
	.size	PrioArray.53118, 128
PrioArray.53118:
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
