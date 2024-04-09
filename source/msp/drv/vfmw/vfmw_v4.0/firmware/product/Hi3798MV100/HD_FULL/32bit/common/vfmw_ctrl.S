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
	.global	VCTRL_EventReport
	.type	VCTRL_EventReport, %function
VCTRL_EventReport:
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
	cmp	r0, #15
	mov	r4, r3
	bhi	.L13
	ldr	lr, .L17
	ldr	r3, [lr, r0, asl #2]
	cmp	r3, #0
	beq	.L14
	ldr	r3, [r3, #36]
	cmp	r3, #0
	beq	.L6
	cmp	r3, #1
	bne	.L15
	ldr	r3, [lr, #220]
	cmp	r3, #0
	beq	.L16
.L9:
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	r3
.L15:
	ldr	r1, .L17+4
	mov	r0, #0
	str	r4, [sp]
	ldr	r2, .L17+8
	ldr	r4, [r1, #68]
	ldr	r1, .L17+12
	blx	r4
.L3:
	mvn	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L6:
	ldr	r3, [lr, #216]
	cmp	r3, #0
	bne	.L9
	ldr	r2, .L17+4
	mov	r0, r3
	ldr	r1, .L17+16
	ldr	r3, [r2, #68]
	blx	r3
	b	.L3
.L16:
	ldr	r2, .L17+4
	mov	r0, r3
	ldr	r1, .L17+20
	ldr	r3, [r2, #68]
	blx	r3
	b	.L3
.L13:
	ldr	ip, .L17+4
	movw	r2, #762
	ldr	r3, .L17+24
	mov	r0, #0
	ldr	r1, .L17+28
	ldr	r4, [ip, #68]
	blx	r4
	b	.L3
.L14:
	ldr	ip, .L17+4
	mov	r0, r3
	movw	r2, #763
	ldr	r3, .L17+32
	ldr	r1, .L17+28
	ldr	r4, [ip, #68]
	blx	r4
	b	.L3
.L18:
	.align	2
.L17:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC5
	.word	.LC3
	.word	.LC4
	.word	.LC0
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_EventReport, .-VCTRL_EventReport
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
	bl	VDMDRV_VdmIntServProc
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
	.type	VCTRL_StopTask.part.1, %function
VCTRL_StopTask.part.1:
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
	ldr	r5, .L33
	ldr	r3, [r5, #68]
	cmp	r3, #1
	beq	.L24
	ldr	r6, .L33+4
	mov	r0, #10
	mov	r4, #49
	ldr	r3, [r6, #124]
	blx	r3
	b	.L25
.L32:
	ldr	r3, [r6, #124]
	blx	r3
	subs	r4, r4, #1
	beq	.L31
.L25:
	ldr	r3, [r5, #68]
	mov	r0, #10
	cmp	r3, #1
	bne	.L32
.L24:
	mov	r0, #0
.L23:
	mov	r3, #0
	str	r3, [r5, #72]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L31:
	mvn	r0, #0
	b	.L23
.L34:
	.align	2
.L33:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_StopTask.part.1, .-VCTRL_StopTask.part.1
	.align	2
	.type	VCTRL_StartTask.part.2, %function
VCTRL_StartTask.part.2:
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
	ldr	r5, .L47
	ldr	r3, [r5, #68]
	cmp	r3, #2
	beq	.L38
	ldr	r6, .L47+4
	mov	r0, #10
	mov	r4, #49
	ldr	r3, [r6, #124]
	blx	r3
	b	.L39
.L46:
	ldr	r3, [r6, #124]
	blx	r3
	subs	r4, r4, #1
	beq	.L45
.L39:
	ldr	r3, [r5, #68]
	mov	r0, #10
	cmp	r3, #2
	bne	.L46
.L38:
	mov	r0, #0
.L37:
	mov	r3, #0
	str	r3, [r5, #72]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L45:
	mvn	r0, #0
	b	.L37
.L48:
	.align	2
.L47:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_StartTask.part.2, .-VCTRL_StartTask.part.2
	.align	2
	.type	VCTRL_SetLastFrameState.part.6, %function
VCTRL_SetLastFrameState.part.6:
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
	ldr	ip, .L50
	movw	r2, #8103
	ldr	r3, .L50+4
	mov	r0, #0
	ldr	r1, .L50+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L51:
	.align	2
.L50:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_SetLastFrameState.part.6, .-VCTRL_SetLastFrameState.part.6
	.align	2
	.global	VCTRL_Suspend
	.type	VCTRL_Suspend, %function
VCTRL_Suspend:
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
	ldr	r5, .L96
	mov	r6, #0
	mov	r4, #32
	mov	r7, r6
	ldr	r3, [r5]
	blx	r3
	mov	r8, r0
	bl	VDM_ResetClock
	mov	r0, r6
	bl	SCDDRV_PrepareSleep
	mov	r0, r6
	bl	VDMDRV_PrepareSleep
	ldr	r3, [r5]
	blx	r3
	mov	r9, r0
.L60:
	mov	r0, #0
	bl	SCDDRV_GetSleepStage
	cmp	r0, #2
	bne	.L90
	mov	r0, #0
	bl	VDMDRV_GetSleepStage
	cmp	r0, #2
	bne	.L91
.L72:
	ldr	r4, .L96+4
	ldr	r3, [r4, #20]
	cmp	r3, #0
	beq	.L61
	mov	r0, #0
	blx	r3
.L62:
	ldr	r3, [r4, #28]
	cmp	r3, #0
	beq	.L63
	blx	r3
.L63:
	ldr	r3, [r4, #4]
	cmp	r3, #0
	beq	.L92
	mov	r0, #0
	blx	r3
	ldr	r3, .L96+8
	ldr	r2, [r3, #64]
	cmp	r2, #1
	beq	.L93
.L65:
	ldr	r3, [r5]
	blx	r3
	ldr	r3, [r5, #68]
	ldr	r1, .L96+12
	cmp	r8, r0
	rsbls	r2, r8, r0
	mvnhi	r8, r8
	addhi	r2, r8, r0
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L61:
	mov	r0, r3
	movw	r2, #353
	ldr	r3, [r5, #68]
	ldr	r1, .L96+16
	blx	r3
	b	.L62
.L92:
	mov	r0, r3
	mov	r2, #360
	ldr	r3, [r5, #68]
	ldr	r1, .L96+16
	blx	r3
	ldr	r3, .L96+8
	ldr	r2, [r3, #64]
	cmp	r2, #1
	bne	.L65
.L93:
	mov	r2, #2
	str	r2, [r3, #72]
	bl	VCTRL_StopTask.part.1
	b	.L65
.L90:
	mov	r0, #0
	mov	r10, r7
	bl	VDMDRV_GetSleepStage
	cmp	r0, #2
	bne	.L68
	mov	r6, #1
	mov	r3, r6
.L69:
	tst	r3, r10
	bne	.L72
	subs	r4, r4, #1
	beq	.L94
	ldr	r3, [r5, #124]
	mov	r0, #10
	blx	r3
	eor	r3, r6, #1
	eor	r2, r7, #1
	orrs	r3, r3, r2
	bne	.L60
	b	.L72
.L91:
	mov	r7, #1
	mov	r10, r7
.L68:
	mov	r3, r6
	b	.L69
.L94:
	ldr	r3, [r5]
	blx	r3
	ldr	r4, [r5, #68]
	str	r6, [sp]
	mov	r3, r7
	ldr	r1, .L96+20
	cmp	r9, r0
	rsbls	r2, r9, r0
	mvnhi	r9, r9
	addhi	r2, r9, r0
	mov	r0, #0
	blx	r4
	cmp	r7, #1
	beq	.L95
	mov	r2, #0
	ldr	r3, [r5, #68]
	mov	r0, r2
	ldr	r1, .L96+24
	blx	r3
	mov	r0, #0
	bl	SCDDRV_ForceSleep
	cmp	r6, #1
	beq	.L72
.L75:
	mov	r2, #0
	ldr	r3, [r5, #68]
	mov	r0, r2
	ldr	r1, .L96+28
	blx	r3
	mov	r0, #0
	bl	VDMDRV_ForceSleep
	b	.L72
.L95:
	cmp	r6, #1
	bne	.L75
	b	.L72
.L97:
	.align	2
.L96:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	.word	.LC9
	.word	.LC8
	.word	.LC10
	.word	.LC11
	.word	.LC7
	UNWIND(.fnend)
	.size	VCTRL_Suspend, .-VCTRL_Suspend
	.align	2
	.global	VCTRL_Resume
	.type	VCTRL_Resume, %function
VCTRL_Resume:
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
	ldr	r5, .L107
	ldr	r3, [r5]
	blx	r3
	mov	r4, r0
	mov	r0, #0
	bl	SCDDRV_ExitSleep
	mov	r0, #0
	bl	VDMDRV_ExitSleep
	ldr	r3, .L107+4
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L99
	blx	r3
.L99:
	ldr	r3, .L107+8
	ldr	r2, [r3, #64]
	cmp	r2, #1
	beq	.L106
.L100:
	ldr	r3, [r5]
	blx	r3
	ldr	r3, [r5, #68]
	ldr	r1, .L107+12
	cmp	r4, r0
	rsbls	r2, r4, r0
	mvnhi	r2, r4
	addhi	r2, r2, r0
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L106:
	str	r2, [r3, #72]
	bl	VCTRL_StartTask.part.2
	b	.L100
.L108:
	.align	2
.L107:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	.word	.LC12
	UNWIND(.fnend)
	.size	VCTRL_Resume, .-VCTRL_Resume
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
	ldr	r3, .L112
	mov	r2, #192
	mov	r1, #0
	ldr	r0, .L112+4
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, .L112+8
	mvn	r1, #0
	add	r2, r3, #64
.L110:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L110
	ldmfd	sp, {fp, sp, pc}
.L113:
	.align	2
.L112:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_ChanCtx
	.word	g_ChanCtx+60
	UNWIND(.fnend)
	.size	ChanCtx_Init, .-ChanCtx_Init
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
	bl	VDMDRV_VdmIntServProc
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
	bl	VDMDRV_VdmIntServProc
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
	ldr	r3, .L119
	mov	r0, #0
	ldr	r3, [r3, #132]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L120:
	.align	2
.L119:
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
	ldr	r3, .L122
	mov	r0, #0
	ldr	r3, [r3, #132]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L123:
	.align	2
.L122:
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L131
	ldr	r3, .L134
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L132
	ldr	r2, [r3, #12]
	cmp	r2, #1
	bne	.L133
	cmp	r1, #1
	strls	r1, [r3, #1216]
	movls	r0, #0
	movhi	r2, #0
	strhi	r2, [r3, #1216]
	mvnhi	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L133:
	ldr	ip, .L134+4
	movw	r2, #742
	ldr	r3, .L134+8
.L130:
	ldr	r1, .L134+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L131:
	ldr	ip, .L134+4
	mov	r2, #740
	ldr	r3, .L134+16
	b	.L130
.L132:
	ldr	ip, .L134+4
	mov	r0, r3
	movw	r2, #741
	ldr	r3, .L134+20
	ldr	r1, .L134+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L135:
	.align	2
.L134:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LC1
	.word	.LC6
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	beq	.L144
	cmp	r0, #0
	beq	.L140
	cmp	r0, #1
	bne	.L145
	ldr	r3, .L146
	mov	r0, #0
	str	r1, [r3, #220]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L145:
	ldr	ip, .L146+4
	mov	r3, r0
	ldr	r2, .L146+8
	mov	r0, #0
	ldr	r1, .L146+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L140:
	ldr	r3, .L146
	str	r1, [r3, #216]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L144:
	ldr	ip, .L146+4
	mov	r0, r1
	ldr	r3, .L146+16
	movw	r2, #803
	ldr	r1, .L146+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L147:
	.align	2
.L146:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+20
	.word	.LC15
	.word	.LC14
	.word	.LC1
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
	ldr	r3, .L150
	ldr	r2, [r3, #64]
	cmp	r2, #1
	bne	.L149
	mov	r2, #2
	str	r2, [r3, #72]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_StopTask.part.1
.L149:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L151:
	.align	2
.L150:
	.word	.LANCHOR0
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
	ldr	r3, .L154
	ldr	r2, [r3, #64]
	cmp	r2, #1
	bne	.L153
	str	r2, [r3, #72]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_StartTask.part.2
.L153:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L155:
	.align	2
.L154:
	.word	.LANCHOR0
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r4, r0
	mov	r6, r1
	bhi	.L161
	cmp	r1, #0
	beq	.L162
	ldr	r5, .L164
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L163
	ldr	r7, .L164+4
	mov	r2, #12
	add	r0, r0, #152
	add	r5, r5, #240
	ldr	r3, [r7, #52]
	blx	r3
	mov	r0, r4, asl #4
	sub	r0, r0, r4, asl #2
	ldr	r3, [r7, #52]
	mov	r1, r6
	add	r0, r5, r0
	mov	r2, #12
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L161:
	ldr	ip, .L164+4
	movw	r2, #1095
	ldr	r3, .L164+8
	mov	r0, #0
	ldr	r1, .L164+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L163:
	ldr	ip, .L164+4
	movw	r2, #1097
	ldr	r3, .L164+16
	ldr	r1, .L164+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L162:
	ldr	ip, .L164+4
	mov	r0, r1
	ldr	r3, .L164+20
	movw	r2, #1096
	ldr	r1, .L164+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L165:
	.align	2
.L164:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC2
	.word	.LC16
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L170
	ldr	r3, .L172
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L171
	add	r3, r0, #225280
	mov	r0, #0
	str	r1, [r3, #2900]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L170:
	ldr	ip, .L172+4
	movw	r2, #1110
	ldr	r3, .L172+8
	mov	r0, #0
	ldr	r1, .L172+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L171:
	ldr	ip, .L172+4
	movw	r2, #1111
	ldr	r3, .L172+16
	ldr	r1, .L172+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L173:
	.align	2
.L172:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L178
	ldr	r3, .L180
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L179
	add	r0, r0, #225280
	ldr	r0, [r0, #2900]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L178:
	ldr	ip, .L180+4
	movw	r2, #1118
	ldr	r3, .L180+8
	mov	r0, #0
	ldr	r1, .L180+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L179:
	ldr	ip, .L180+4
	movw	r2, #1119
	ldr	r3, .L180+16
	ldr	r1, .L180+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L181:
	.align	2
.L180:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r4, r0
	bhi	.L187
	ldr	r5, .L189
	ldr	r1, [r5, r0, asl #2]
	cmp	r1, #0
	beq	.L187
	ldr	r6, .L189+4
	mov	r3, r0, asl #4
	sub	r3, r3, r0, asl #2
	add	r0, r5, #240
	add	r0, r0, r3
	add	r1, r1, #152
	ldr	r3, [r6, #60]
	mov	r2, #12
	blx	r3
	cmp	r0, #0
	bne	.L188
	ldr	r1, [r5, r4, asl #2]
	add	r0, r1, #152
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L188:
	ldr	r5, [r6, #68]
	mov	r3, r4
	movw	r2, #1137
	ldr	r1, .L189+8
	mov	r0, #0
	blx	r5
.L187:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L190:
	.align	2
.L189:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC17
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L196
	ldr	r3, .L199
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L197
	ldr	r3, [r0, #12]
	cmp	r3, #1
	bne	.L198
	add	r0, r0, #99328
	add	r0, r0, #576
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	GetSegStreamSize
.L198:
	ldr	ip, .L199+4
	movw	r2, #1165
	ldr	r3, .L199+8
	mov	r0, #0
	ldr	r1, .L199+12
	ldr	r4, [ip, #68]
	blx	r4
.L193:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L196:
	ldr	ip, .L199+4
	movw	r2, #1163
	ldr	r3, .L199+16
	mov	r0, #0
	ldr	r1, .L199+12
	ldr	r4, [ip, #68]
	blx	r4
	b	.L193
.L197:
	ldr	ip, .L199+4
	movw	r2, #1164
	ldr	r3, .L199+20
	ldr	r1, .L199+12
	ldr	r4, [ip, #68]
	blx	r4
	b	.L193
.L200:
	.align	2
.L199:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	.word	.LC1
	.word	.LC6
	.word	.LC18
	UNWIND(.fnend)
	.size	VCTRL_GetStreamSize, .-VCTRL_GetStreamSize
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
	cmp	r0, #15
	mov	r4, r0
	mov	r0, r1
	bhi	.L207
	cmp	r1, #0
	beq	.L208
	ldr	r5, .L210
	ldr	r0, [r5, r4, asl #2]
	cmp	r0, #0
	beq	.L209
	ldr	r3, .L210+4
	add	r0, r0, #1424
	mov	r2, #8
	add	r0, r0, #12
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r2, [r5, r4, asl #2]
	mov	r0, #0
	ldr	r3, [r2, #1436]
	sub	r3, r3, #1
	cmp	r3, #1
	strhi	r0, [r2, #1436]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L207:
	ldr	ip, .L210+4
	movw	r2, #1177
	ldr	r3, .L210+8
	mov	r0, #0
	ldr	r1, .L210+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L209:
	ldr	ip, .L210+4
	movw	r2, #1179
	ldr	r3, .L210+16
	ldr	r1, .L210+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L208:
	ldr	ip, .L210+4
	movw	r2, #1178
	ldr	r3, .L210+20
	ldr	r1, .L210+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L211:
	.align	2
.L210:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC2
	.word	.LC20
	UNWIND(.fnend)
	.size	VCTRL_SetDiscardPicParam, .-VCTRL_SetDiscardPicParam
	.align	2
	.global	VCTRL_GetSyntaxCtx
	.type	VCTRL_GetSyntaxCtx, %function
VCTRL_GetSyntaxCtx:
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
	cmp	r0, #15
	bhi	.L214
	ldr	r3, .L216
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r0, r0, #229376
	addne	r0, r0, #112
	ldmfd	sp, {fp, sp, pc}
.L214:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L217:
	.align	2
.L216:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetSyntaxCtx, .-VCTRL_GetSyntaxCtx
	.align	2
	.global	VCTRL_GetImageInterface
	.type	VCTRL_GetImageInterface, %function
VCTRL_GetImageInterface:
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
	cmp	r0, #15
	bhi	.L220
	ldr	r3, .L222
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r0, r0, #164
	ldmfd	sp, {fp, sp, pc}
.L220:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L223:
	.align	2
.L222:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetImageInterface, .-VCTRL_GetImageInterface
	.align	2
	.global	VCTRL_PartitionMemForStdUser
	.type	VCTRL_PartitionMemForStdUser, %function
VCTRL_PartitionMemForStdUser:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #52)
	sub	sp, sp, #52
	ldr	r4, .L240
	cmp	r2, #31
	cmpgt	r1, #31
	mov	r7, r2
	mov	r8, r1
	mov	r9, r0
	movle	r2, #1
	movgt	r2, #0
	str	r3, [fp, #-88]
	ldr	r5, [r4, r0, asl #2]
	ble	.L236
	ldr	r3, [fp, #-88]
	ldr	r1, [fp, #4]
	cmp	r1, #0
	cmpne	r3, #0
	moveq	r6, #1
	movne	r6, #0
	beq	.L237
	ldr	r10, .L240+4
	mov	r2, #32
	mov	r1, r6
	sub	r0, fp, #76
	ldr	r3, [r10, #48]
	blx	r3
	sub	r1, fp, #76
	mov	r0, r9
	mov	r3, #1
	str	r7, [fp, #-64]
	str	r7, [fp, #-48]
	strb	r6, [fp, #-75]
	str	r8, [fp, #-68]
	str	r8, [fp, #-52]
	strb	r6, [fp, #-72]
	strb	r6, [fp, #-70]
	strb	r6, [fp, #-69]
	strb	r3, [fp, #-73]
	bl	FSP_ConfigInstance
	subs	r7, r0, #0
	bne	.L228
	ldr	r2, [fp, #4]
	sub	r3, fp, #80
	ldr	r1, [fp, #-88]
	mov	r0, r9
	bl	FSP_PartitionFsMemory
	subs	r6, r0, #0
	bne	.L238
	mov	r0, r9
	add	r1, r4, #432
	bl	FSP_GetInstInfo
	movw	r3, #433
	ldrsb	r3, [r4, r3]
	cmp	r3, #16
	movge	r3, #16
	cmp	r3, #2
	str	r3, [r5, #468]
	ble	.L239
	ldr	ip, [r4, #2488]
	mov	r2, #64
	ldr	r3, [r10, #48]
	mov	r1, r7
	add	r0, r5, #400
	str	ip, [r5, #464]
	blx	r3
	mov	r1, r7
	ldr	r3, [r10, #48]
	mov	r2, #64
	add	r0, r5, #336
	blx	r3
	ldr	r1, [r5, #468]
	cmp	r1, #0
	ble	.L226
	add	r4, r4, #432
	add	r5, r5, #396
	mov	r3, r7
.L233:
	ldr	r2, [r4, #20]
	add	r3, r3, #1
	cmp	r3, r1
	add	r4, r4, #64
	str	r2, [r5, #4]!
	bne	.L233
.L226:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L237:
	ldr	r3, .L240+4
	mov	r0, r2
	ldr	r1, .L240+8
	mvn	r7, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L226
.L228:
	ldr	r3, [r10, #68]
	mov	r0, r6
	ldr	r1, .L240+12
	mvn	r7, #0
	blx	r3
	b	.L226
.L238:
	ldr	r3, [r10, #68]
	mov	r0, r7
	ldr	r1, .L240+16
	blx	r3
.L230:
	mvn	r7, #0
	b	.L226
.L239:
	ldr	r4, [r10, #68]
	mov	r0, r6
	movw	r3, #1434
	ldr	r2, .L240+20
	ldr	r1, .L240+24
	blx	r4
	b	.L230
.L236:
	ldr	ip, .L240+4
	mov	r3, r7
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L240+28
	mvn	r7, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L226
.L241:
	.align	2
.L240:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC22
	.word	.LC25
	.word	.LC23
	.word	.LANCHOR1+40
	.word	.LC24
	.word	.LC21
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
	.global	VCTRL_RlsAllFrameNode
	.type	VCTRL_RlsAllFrameNode, %function
VCTRL_RlsAllFrameNode:
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
	cmp	r0, #15
	mov	r6, r0
	bhi	.L254
	ldr	r8, .L255
	ldr	r9, [r8, r0, asl #2]
	cmp	r9, #0
	beq	.L246
	mov	r4, #0
	mvn	r7, #0
	mov	r0, r4
	b	.L247
.L249:
	add	r9, r9, r5
	add	r9, r9, #227328
	ldr	r2, [r9, #868]
	ldr	r1, [r9, #860]
	ldr	r0, [r9, #864]
	bl	MEM_DelMemRecord
	ldr	r3, [r8, r6, asl #2]
	add	r5, r3, r5
	add	r5, r5, #227328
	strb	r7, [r5, #872]
.L248:
	cmp	r4, #32
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r9, [r8, r6, asl #2]
.L247:
	mov	r3, r4, asl #2
	mov	r2, r4, asl #4
	add	r5, r3, r2
	add	r4, r4, #1
	add	r3, r9, r5
	add	r3, r3, #227328
	ldrb	r2, [r3, #872]	@ zero_extendqisi2
	cmp	r2, #255
	beq	.L248
	cmp	r2, #1
	bne	.L249
	ldr	r1, [r3, #860]
	ldr	r0, [r3, #864]
	bl	MEM_ReleaseMemBlock
	b	.L249
.L254:
	ldr	ip, .L255+4
	movw	r2, #1496
	ldr	r3, .L255+8
	mov	r0, #0
	ldr	r1, .L255+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L246:
	ldr	ip, .L255+4
	mov	r0, r9
	ldr	r3, .L255+16
	movw	r2, #1497
	ldr	r1, .L255+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L256:
	.align	2
.L255:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC18
	UNWIND(.fnend)
	.size	VCTRL_RlsAllFrameNode, .-VCTRL_RlsAllFrameNode
	.align	2
	.type	VCTRL_AllocMemPre, %function
VCTRL_AllocMemPre:
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
	ldr	r10, .L271
	mov	r7, r1
	mov	r9, r0
	ldr	r1, [r10, r0, asl #2]
	add	r0, r1, #225280
	ldr	r2, [r1, #208]
	ldr	r6, [r1, #204]
	ldr	r8, [r0, #2872]
	cmp	r6, #0
	cmpne	r2, #0
	movne	r0, #1
	moveq	r0, #0
	cmp	r7, #31
	movgt	r0, #0
	andle	r0, r0, #1
	cmp	r0, #0
	beq	.L258
	mov	r5, #0
	rsb	r3, r6, r2
	mov	r4, r5
	str	r3, [fp, #-48]
	mov	r0, r5
	b	.L262
.L259:
	cmp	r7, r5
	ble	.L261
	add	r4, r4, #1
	add	r6, r6, r8
	cmp	r4, #32
	beq	.L261
.L269:
	ldr	r1, [r10, r9, asl #2]
.L262:
	mov	r3, r4, asl #4
	cmp	r5, r7
	add	r3, r3, r4, lsl #2
	add	r3, r1, r3
	movge	ip, #0
	add	r3, r3, #227328
	movlt	ip, #1
	ldrb	r2, [r3, #872]	@ zero_extendqisi2
	cmp	r2, #255
	movne	r2, #0
	andeq	r2, ip, #1
	cmp	r2, #0
	beq	.L259
	ldr	r0, [fp, #-48]
	mov	r1, r6
	str	r6, [r3, #860]
	add	r5, r5, #1
	add	r0, r0, r6
	str	r8, [r3, #868]
	str	r0, [r3, #864]
	mov	r2, r8
	mov	r0, #0
	strb	r0, [r3, #872]
	ldr	r0, [r3, #864]
	add	r4, r4, #1
	bl	MEM_AddMemRecord
	cmp	r7, r5
	add	r6, r6, r8
	movle	ip, #0
	movgt	ip, #1
	cmp	r4, #32
	bne	.L269
.L261:
	cmp	r4, #32
	movne	r4, #0
	andeq	r4, ip, #1
	cmp	r4, #0
	bne	.L270
.L263:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L270:
	ldr	r4, .L271+4
	mov	r3, r5
	mov	r2, r7
	ldr	r1, .L271+8
	mov	r0, #31
	ldr	r5, [r4, #68]
	blx	r5
	mov	r0, r9
	bl	VCTRL_RlsAllFrameNode
	cmp	r0, #0
	mvneq	r0, #0
	beq	.L263
	ldr	r3, [r4, #68]
	mov	r2, r9
	ldr	r1, .L271+12
	mov	r0, #31
	blx	r3
	mvn	r0, #0
	b	.L263
.L258:
	ldr	ip, .L271+4
	mov	r3, r6
	str	r7, [sp]
	mov	r0, #31
	ldr	r1, .L271+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L263
.L272:
	.align	2
.L271:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC28
	.word	.LC26
	UNWIND(.fnend)
	.size	VCTRL_AllocMemPre, .-VCTRL_AllocMemPre
	.align	2
	.type	VCTRL_AllocMemMMZ, %function
VCTRL_AllocMemMMZ:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldr	r10, .L292
	mov	r9, r0
	mov	r3, #0
	mov	r0, r3
	str	r3, [fp, #-48]
	ldr	r4, [r10, r9, asl #2]
	mov	r7, r3
	mov	r5, r3
	str	r1, [fp, #-52]
	add	r2, r4, #225280
	ldr	r3, [r4, #1408]
	ldr	r2, [r2, #2872]
	add	r3, r3, r3, lsr #31
	str	r2, [fp, #-60]
	mov	r3, r3, asr #1
	str	r3, [fp, #-72]
	b	.L280
.L274:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-48]
	cmp	r3, r2
	ble	.L279
	add	r5, r5, #1
	cmp	r5, #32
	beq	.L277
.L290:
	ldr	r4, [r10, r9, asl #2]
.L280:
	mov	r3, r5, asl #4
	mov	r6, r5, asl #2
	add	r8, r6, r3
	str	r3, [fp, #-56]
	add	r3, r4, r8
	ldr	r1, [fp, #-48]
	add	r3, r3, #227328
	ldrb	r2, [r3, #872]	@ zero_extendqisi2
	ldr	r3, [fp, #-52]
	cmp	r1, r3
	movge	r3, #0
	movlt	r3, #1
	cmp	r2, #255
	movne	r3, #0
	cmp	r3, #0
	beq	.L274
	add	r8, r8, #227328
	mov	r1, #0
	add	r8, r8, #856
	str	r1, [sp]
	add	r4, r4, r8
	ldr	r2, [fp, #-60]
	ldr	r0, .L292+4
	mov	r3, r4
	bl	MEM_AllocMemBlock
	ldr	r3, [fp, #-72]
	cmp	r0, #0
	cmpne	r3, r7
	ble	.L275
	str	r5, [fp, #-64]
	ldr	r5, [fp, #-60]
	str	r6, [fp, #-68]
	mov	r6, r3
.L276:
	ldr	r3, .L292+8
	mov	r0, #2
	add	r7, r7, #1
	ldr	r3, [r3, #124]
	blx	r3
	ldr	r4, [r10, r9, asl #2]
	mov	r1, #0
	mov	r2, r5
	add	r4, r4, r8
	str	r1, [sp]
	ldr	r0, .L292+4
	mov	r3, r4
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	cmpne	r6, r7
	bgt	.L276
	ldr	r5, [fp, #-64]
	ldr	r6, [fp, #-68]
.L275:
	cmp	r0, #0
	bne	.L277
	ldr	r3, [fp, #-48]
	add	r5, r5, #1
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #4]
	add	r3, r3, #1
	ldr	r0, [r4, #8]
	str	r3, [fp, #-48]
	bl	MEM_AddMemRecord
	ldr	r2, [fp, #-56]
	cmp	r5, #32
	ldr	r3, [r10, r9, asl #2]
	add	r6, r6, r2
	mov	r2, #1
	add	r6, r3, r6
	add	r6, r6, #227328
	strb	r2, [r6, #872]
	bne	.L290
.L277:
	ldr	r1, [fp, #-52]
	ldr	r3, [fp, #-48]
	cmp	r1, r3
	ble	.L279
	ldr	r4, .L292+8
	mov	r2, r9
	str	r1, [sp]
	mov	r0, #31
	str	r5, [sp, #4]
	ldr	r1, .L292+12
	ldr	r5, [r4, #68]
	blx	r5
	mov	r0, r9
	bl	VCTRL_RlsAllFrameNode
	cmp	r0, #0
	mvneq	r0, #0
	bne	.L291
.L279:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L291:
	ldr	r3, [r4, #68]
	mov	r0, #31
	ldr	r1, .L292+16
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L293:
	.align	2
.L292:
	.word	.LANCHOR0
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC30
	.word	.LC31
	UNWIND(.fnend)
	.size	VCTRL_AllocMemMMZ, .-VCTRL_AllocMemMMZ
	.align	2
	.global	VCTRL_FreeChanResource
	.type	VCTRL_FreeChanResource, %function
VCTRL_FreeChanResource:
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
	subs	r8, r1, #0
	beq	.L327
	ldr	r3, [r8, #88]
	cmp	r3, #1
	beq	.L297
	ldr	r2, [r8, #12]
	ldr	r1, [r8, #4]
	ldr	r0, [r8, #8]
	bl	MEM_DelMemRecord
.L298:
	ldr	r2, [r8, #28]
	cmp	r2, #0
	bne	.L328
	ldr	r3, [r8, #64]
	cmp	r3, #1
	beq	.L329
.L304:
	ldr	r3, [r8, #68]
	cmp	r3, #1
	beq	.L330
.L305:
	ldr	r3, [r8, #72]
	cmp	r3, #1
	beq	.L331
.L306:
	ldr	r3, .L333
	ldr	r0, [r8, #36]
	ldr	r3, [r3, #168]
	blx	r3
.L307:
	ldr	r2, [r8, #44]
	ldr	r1, [r8, #36]
	ldr	r0, [r8, #40]
	bl	MEM_DelMemRecord
	add	r0, r8, #48
	bl	SM_DeletDSPCtxMem
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L331:
	ldr	r0, [r8, #40]
	cmp	r0, #0
	beq	.L306
	ldr	r1, [r8, #36]
	bl	MEM_ReleaseMemBlock
	b	.L307
.L297:
	ldr	r7, .L333
	mov	r5, #0
	mvn	r6, #0
	b	.L302
.L301:
	ldr	r3, [r8, #92]
	add	r3, r3, r5
	strb	r6, [r3, #16]
.L299:
	add	r5, r5, #20
	cmp	r5, #640
	beq	.L298
.L302:
	ldr	r4, [r8, #92]
	add	r4, r4, r5
	ldrb	r3, [r4, #16]	@ zero_extendqisi2
	cmp	r3, #255
	beq	.L299
	cmp	r3, #1
	beq	.L332
.L300:
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_DelMemRecord
	cmp	r0, #0
	beq	.L301
	ldr	r2, [r4, #8]
	mov	r0, #1
	ldr	r3, [r7, #68]
	ldr	r1, .L333+4
	blx	r3
	b	.L301
.L332:
	ldr	r3, [r7, #68]
	mov	r0, #31
	ldr	r1, .L333+8
	blx	r3
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_ReleaseMemBlock
	b	.L300
.L328:
	ldr	r1, [r8, #20]
	ldr	r0, [r8, #24]
	bl	MEM_DelMemRecord
	ldr	r3, [r8, #64]
	cmp	r3, #1
	bne	.L304
.L329:
	ldr	r0, [r8, #8]
	cmp	r0, #0
	beq	.L304
	ldr	r1, [r8, #4]
	bl	MEM_ReleaseMemBlock
	b	.L304
.L330:
	ldr	r0, [r8, #24]
	cmp	r0, #0
	beq	.L305
	ldr	r1, [r8, #20]
	bl	MEM_ReleaseMemBlock
	b	.L305
.L327:
	ldr	ip, .L333
	mov	r0, r8
	ldr	r3, .L333+12
	movw	r2, #1527
	ldr	r1, .L333+16
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L334:
	.align	2
.L333:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC34
	.word	.LC33
	.word	.LC32
	.word	.LC1
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
	movweq	r3, #56880
	movwne	r3, #27784
	movteq	r3, 176
	movtne	r3, 8
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r3, r1
	bhi	.L343
	cmp	r1, #0
	beq	.L344
	ldr	r2, .L346
	ldr	ip, .L346+4
	ldr	r1, [r2, r0, asl #2]
	cmp	r1, #0
	beq	.L345
	add	r1, r1, #48
	mov	r0, r3
	mov	r2, #104
	ldr	r3, [ip, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L343:
	ldr	ip, .L346+4
	movw	r2, #2707
	ldr	r3, .L346+8
	mov	r0, #0
	ldr	r1, .L346+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L345:
	mov	r0, r1
	ldr	r3, .L346+16
	movw	r2, #2709
	ldr	r1, .L346+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L344:
	ldr	ip, .L346+4
	mov	r0, r1
	ldr	r3, .L346+20
	movw	r2, #2708
	ldr	r1, .L346+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L347:
	.align	2
.L346:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC2
	.word	.LC35
	UNWIND(.fnend)
	.size	VCTRL_GetChanCfg, .-VCTRL_GetChanCfg
	.align	2
	.global	VCTRL_CmpConfigParameter
	.type	VCTRL_CmpConfigParameter, %function
VCTRL_CmpConfigParameter:
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
	ldr	r3, .L367
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #528]
	cmp	r2, #20
	beq	.L364
	ldr	r2, [r3, #48]
	ldr	r0, [r1]
	cmp	r2, r0
	bne	.L364
	ldr	ip, [r3, #64]
	ldr	r0, [r1, #16]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #60]
	ldr	r0, [r1, #12]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #68]
	ldr	r0, [r1, #20]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #72]
	ldr	r0, [r1, #24]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #76]
	ldr	r0, [r1, #28]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #80]
	ldr	r0, [r1, #32]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #100]
	ldr	r0, [r1, #52]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #112]
	ldr	r0, [r1, #64]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #108]
	ldr	r0, [r1, #60]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #104]
	ldr	r0, [r1, #56]
	cmp	ip, r0
	bne	.L364
	ldr	ip, [r3, #116]
	ldr	r0, [r1, #68]
	cmp	ip, r0
	bne	.L364
	cmp	r2, #1
	beq	.L366
	sub	r2, r2, #10
	cmp	r2, #2
	bhi	.L365
	ldr	r3, [r3, #52]
	ldr	r0, [r1, #4]
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L364:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L365:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L366:
	ldr	r0, [r3, #52]
	ldr	r2, [r1, #4]
	cmp	r0, r2
	bne	.L364
	ldr	r3, [r3, #56]
	ldr	r0, [r1, #8]
	subs	r0, r3, r0
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L368:
	.align	2
.L367:
	.word	.LANCHOR0
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L374
	ldr	r2, .L374+4
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r2]
	ldr	r0, [r3, #1272]
	ldr	r3, [r3, #1276]
	cmp	r0, r2
	bgt	.L370
	ldr	r0, .L374+8
	ldr	r0, [r0]
	cmp	r3, r0
	ble	.L372
.L370:
	ldr	r3, [r1]
	cmp	r3, #19
	cmpne	r3, #13
	movne	r0, #1
	moveq	r0, #0
	bics	r3, r3, #16
	andne	r0, r0, #1
	moveq	r0, #0
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	ip, .L374+12
	mov	r0, #0
	ldr	r3, .L374+8
	ldr	r1, .L374+16
	ldr	r4, [ip, #68]
	ldr	r3, [r3]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L372:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L375:
	.align	2
.L374:
	.word	.LANCHOR0
	.word	g_ChipMaxWidth
	.word	g_ChipMaxHeight
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC36
	UNWIND(.fnend)
	.size	VCTRL_CheckChanWH, .-VCTRL_CheckChanWH
	.align	2
	.global	VCTRL_SeekPts
	.type	VCTRL_SeekPts, %function
VCTRL_SeekPts:
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
	beq	.L384
	cmp	r0, #15
	bhi	.L385
	ldr	r2, .L388
	ldr	r3, [r2, r0, asl #2]
	cmp	r3, #0
	beq	.L386
	ldr	r3, [r3, #528]
	sub	ip, r3, #10
	cmp	ip, #2
	bls	.L387
.L381:
	cmp	r3, #15
	cmpne	r3, #4
	beq	.L383
	bl	SM_SeekPts
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L387:
	ldr	r2, [r2, #2492]
	tst	r2, #1
	bne	.L381
.L383:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L385:
	ldr	ip, .L388+4
	movw	r2, #3158
	ldr	r3, .L388+8
	mov	r0, #0
	ldr	r1, .L388+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L384:
	ldr	ip, .L388+4
	mov	r0, r1
	ldr	r3, .L388+16
	movw	r2, #3157
	ldr	r1, .L388+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L386:
	ldr	ip, .L388+4
	mov	r0, r3
	movw	r2, #3159
	ldr	r3, .L388+20
	ldr	r1, .L388+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L389:
	.align	2
.L388:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC37
	.word	.LC2
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L394
	ldr	r2, .L396
	ldr	r3, [r2, r0, asl #2]
	cmp	r3, #0
	beq	.L395
	bl	SM_Reset
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L394:
	ldr	ip, .L396+4
	movw	r2, #3614
	ldr	r3, .L396+8
	mov	r0, #0
	ldr	r1, .L396+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L395:
	ldr	ip, .L396+4
	mov	r0, r3
	movw	r2, #3615
	ldr	r3, .L396+16
	ldr	r1, .L396+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L397:
	.align	2
.L396:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_ReleaseStream, .-VCTRL_ReleaseStream
	.align	2
	.global	VCTRL_ReleaseChanImage
	.type	VCTRL_ReleaseChanImage, %function
VCTRL_ReleaseChanImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 504
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #508)
	sub	sp, sp, #508
	cmp	r0, #15
	mov	r4, r0
	mov	r5, r1
	bhi	.L419
	ldr	r8, .L427
	ldr	r0, [r8, r0, asl #2]
	cmp	r0, #0
	beq	.L420
	ldr	r3, [r0, #12]
	cmp	r3, #1
	bne	.L421
	cmp	r1, #0
	beq	.L422
	ldr	r6, .L427+4
	mov	r2, r4
	ldr	r3, [r1, #196]
	mov	r0, #2
	ldr	r1, .L427+8
	ldr	r7, [r6, #68]
	blx	r7
	ldr	r3, [r6, #12]
	mov	r0, #4
	blx	r3
	ldr	r0, [r8, r4, asl #2]
	cmp	r0, #0
	beq	.L423
	ldr	r3, [r0, #12]
	cmp	r3, #1
	bne	.L424
	add	r0, r0, #229376
	mov	r1, r5
	add	r0, r0, #112
	bl	SYNTAX_ReleaseImage
	ldr	r3, [r5, #252]
	cmn	r3, #1
	mov	r7, r0
	beq	.L406
	ldr	r0, [r8, r4, asl #2]
	sub	r1, fp, #540
	str	r3, [fp, #-344]
	add	r0, r0, #229376
	add	r0, r0, #112
	bl	SYNTAX_ReleaseImage
	mov	r7, r0
.L406:
	mov	r0, #13
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L425
.L408:
	subs	r4, r7, #1
	mvnne	r4, #0
	cmp	r4, #0
	bne	.L426
.L410:
	ldr	r3, [r6, #16]
	mov	r0, #4
	blx	r3
.L400:
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L426:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r2, .L427+12
	ldr	r1, .L427+16
	blx	r3
	b	.L410
.L425:
	ldr	r3, [r6]
	add	r8, r8, r4, lsl #2
	blx	r3
	ldr	r2, .L427+20
	ldr	r3, [r8, #2496]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	mov	ip, r0
	cmp	r3, r2
	bls	.L408
	mov	r2, r4, asl #24
	movw	r1, #4217
	add	r2, r2, #851968
	ldr	r0, .L427+24
	cmp	r7, #1
	addeq	r2, r2, #1
	str	ip, [r8, #2496]
	bl	DBG_AddTrace
	b	.L408
.L424:
	ldr	r3, [r6, #68]
	movw	r2, #4119
	ldr	r1, .L427+28
	mov	r0, #0
.L418:
	blx	r3
	ldr	r3, [r6, #16]
	mov	r0, #4
	mvn	r4, #0
	blx	r3
	b	.L400
.L421:
	ldr	ip, .L427+4
	movw	r2, #4100
	ldr	r3, .L427+32
.L417:
	ldr	r1, .L427+36
	mov	r0, #0
	ldr	r5, [ip, #68]
	mvn	r4, #0
	blx	r5
	b	.L400
.L419:
	ldr	ip, .L427+4
	movw	r2, #4098
	ldr	r3, .L427+40
	b	.L417
.L422:
	ldr	ip, .L427+4
	mov	r0, r1
	ldr	r3, .L427+44
	movw	r2, #4101
	ldr	r1, .L427+36
	mvn	r4, #0
	ldr	r5, [ip, #68]
	blx	r5
	b	.L400
.L420:
	ldr	ip, .L427+4
	movw	r2, #4099
	ldr	r3, .L427+48
	mvn	r4, #0
	ldr	r1, .L427+36
	ldr	r5, [ip, #68]
	blx	r5
	b	.L400
.L423:
	ldr	r3, [r6, #68]
	movw	r2, #4109
	ldr	r1, .L427+52
	b	.L418
.L428:
	.align	2
.L427:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC40
	.word	.LANCHOR1+96
	.word	.LC43
	.word	g_TraceImgPeriod
	.word	.LANCHOR1+72
	.word	.LC42
	.word	.LC38
	.word	.LC1
	.word	.LC6
	.word	.LC39
	.word	.LC2
	.word	.LC41
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L430
	ldr	r3, .L434
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L430
	ldr	r2, [r3, #12]
	cmp	r2, #1
	beq	.L433
	ldr	ip, .L434+4
	mov	r3, r0
	movw	r2, #4269
	ldr	r1, .L434+8
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L430:
	ldr	r3, .L434+4
	movw	r2, #4262
	ldr	r1, .L434+12
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L433:
	ldr	r0, [r3, #528]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L435:
	.align	2
.L434:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC45
	.word	.LC44
	UNWIND(.fnend)
	.size	VCTRL_GetVidStd, .-VCTRL_GetVidStd
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
	cmp	r0, #15
	bhi	.L437
	ldr	r3, .L462
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L437
	ldr	r2, [r4, #12]
	cmp	r2, #1
	bne	.L458
	ldr	r2, [r4, #16]
	cmp	r2, #1
	bne	.L458
	ldr	r2, [r4, #528]
	cmp	r2, #17
	ldrls	pc, [pc, r2, asl #2]
	b	.L458
.L442:
	.word	.L441
	.word	.L461
	.word	.L444
	.word	.L461
	.word	.L458
	.word	.L461
	.word	.L461
	.word	.L458
	.word	.L461
	.word	.L461
	.word	.L450
	.word	.L450
	.word	.L450
	.word	.L461
	.word	.L458
	.word	.L458
	.word	.L452
	.word	.L453
.L458:
	mov	r3, #0
.L439:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L450:
	ldr	r3, [r3, #2492]
	ands	r3, r3, #1
	beq	.L439
.L461:
	add	r3, r4, #229376
	ldr	r5, [r3, #124]
.L440:
	cmp	r5, #0
	beq	.L458
	ldr	r3, .L462+4
	ldr	r3, [r3]
	blx	r3
	mov	r3, r5
	str	r0, [r4, #44]
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L437:
	ldr	ip, .L462+4
	mov	r3, r0
	movw	r2, #4286
	ldr	r1, .L462+8
	mov	r0, #22
	ldr	r4, [ip, #68]
	blx	r4
	mov	r3, #0
	b	.L439
.L441:
	add	r3, r4, #229376
	ldr	r5, [r3, #480]
	b	.L440
.L452:
	add	r3, r4, #229376
	ldr	r5, [r3, #348]
	b	.L440
.L453:
	add	r3, r4, #229376
	ldr	r5, [r3, #2432]
	b	.L440
.L444:
	add	r3, r4, #229376
	ldr	r5, [r3, #1156]
	b	.L440
.L463:
	.align	2
.L462:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC46
	UNWIND(.fnend)
	.size	VCTRL_GetDecParam, .-VCTRL_GetDecParam
	.align	2
	.global	VCTRL_ChanDecparamInValidFlag
	.type	VCTRL_ChanDecparamInValidFlag, %function
VCTRL_ChanDecparamInValidFlag:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #15
	mov	r2, r0
	bhi	.L465
	ldr	r5, .L476
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L465
	ldr	r1, [r3, #12]
	cmp	r1, #1
	bne	.L468
	ldr	r6, [r3, #16]
	cmp	r6, #1
	beq	.L469
.L468:
	ldr	r3, .L476+4
	mov	r0, #22
	ldr	r1, .L476+8
	mov	r4, #0
	ldr	r3, [r3, #68]
	blx	r3
.L467:
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L465:
	ldr	ip, .L476+4
	mov	r3, r2
	ldr	r1, .L476+12
	movw	r2, #4405
	mov	r0, #22
	mov	r4, #0
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L469:
	str	r0, [fp, #-40]
	bl	VCTRL_GetDecParam
	ldr	r2, [fp, #-40]
	subs	r7, r0, #0
	beq	.L474
	ldr	r2, [r5, r2, asl #2]
	mov	r3, #0
	mov	r4, r3
	str	r3, [r2, #328]
	str	r3, [r2, #332]
	b	.L467
.L474:
	ldr	r8, [r5, r2, asl #2]
	ldr	r4, [r8, #328]
	cmp	r4, #0
	beq	.L475
	ldr	r3, .L476+4
	str	r2, [fp, #-40]
	ldr	r3, [r3]
	blx	r3
	ldr	r2, [fp, #-40]
	ldr	r3, [r5, r2, asl #2]
	ldr	r2, [r3, #332]
	cmp	r0, r2
	bls	.L472
	rsb	r0, r2, r0
	cmp	r0, #40
	movls	r4, r7
	bls	.L467
.L472:
	str	r7, [r3, #328]
	mov	r4, r6
	str	r7, [r3, #332]
	b	.L467
.L475:
	ldr	r3, .L476+4
	str	r6, [r8, #328]
	ldr	r3, [r3]
	blx	r3
	str	r0, [r8, #332]
	b	.L467
.L477:
	.align	2
.L476:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC47
	.word	.LC46
	UNWIND(.fnend)
	.size	VCTRL_ChanDecparamInValidFlag, .-VCTRL_ChanDecparamInValidFlag
	.align	2
	.global	VCTRL_FlushDecoder
	.type	VCTRL_FlushDecoder, %function
VCTRL_FlushDecoder:
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
	cmp	r0, #15
	mov	r4, r0
	bhi	.L505
	ldr	r5, .L509
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L506
	add	r0, r0, #229376
	ldr	r3, [r0, #112]
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L498
.L483:
	.word	.L482
	.word	.L484
	.word	.L485
	.word	.L486
	.word	.L498
	.word	.L487
	.word	.L488
	.word	.L498
	.word	.L489
	.word	.L490
	.word	.L491
	.word	.L491
	.word	.L491
	.word	.L492
	.word	.L498
	.word	.L498
	.word	.L493
	.word	.L494
.L494:
	add	r0, r0, #120
	ldr	r4, .L509+4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L507
.L496:
	ldr	r3, [r4, #68]
	mov	r0, #32
	ldr	r1, .L509+8
	blx	r3
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L482:
	add	r0, r0, #120
	bl	H264_FlushDecoder
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	ldr	r0, [r5, r4, asl #2]
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	FlushDPB
	cmp	r0, #0
	bne	.L508
.L498:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L484:
	add	r0, r0, #120
	bl	VC1DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L485:
	add	r0, r0, #120
	bl	MPEG4DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L486:
	add	r0, r0, #120
	bl	MPEG2DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L487:
	add	r0, r0, #120
	bl	DIVX3DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L488:
	add	r0, r0, #120
	bl	AVSDEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L489:
	add	r0, r0, #120
	bl	REAL8DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L490:
	add	r0, r0, #120
	bl	REAL9DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L491:
	add	r0, r0, #120
	bl	VP6DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L492:
	add	r0, r0, #120
	bl	VP8DEC_GetRemainImg
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L493:
	add	r0, r0, #120
	bl	MVC_FlushDecoder
	bl	VDMDRV_WakeUpVdm
	bl	VDMDRV_WakeUpVdm
	ldr	r0, [r5, r4, asl #2]
	mvn	r1, #0
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	MVC_FlushDPB
	cmp	r0, #0
	beq	.L498
	ldr	ip, .L509+4
	movw	r3, #4717
	ldr	r2, .L509+12
	mov	r0, #22
	ldr	r1, .L509+16
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L507:
	movw	r2, #4700
	ldr	r1, .L509+20
	ldr	r3, [r4, #68]
	mov	r0, #0
	blx	r3
	b	.L496
.L508:
	ldr	r3, .L509+4
	movw	r2, #4690
	ldr	r1, .L509+20
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L505:
	ldr	ip, .L509+4
	movw	r2, #4663
	ldr	r3, .L509+24
	mov	r0, #0
	ldr	r1, .L509+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L506:
	ldr	ip, .L509+4
	movw	r2, #4664
	ldr	r3, .L509+32
	ldr	r1, .L509+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L510:
	.align	2
.L509:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC49
	.word	.LANCHOR1+120
	.word	.LC50
	.word	.LC48
	.word	.LC6
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_FlushDecoder, .-VCTRL_FlushDecoder
	.align	2
	.global	VCTRL_GetImageBuffer
	.type	VCTRL_GetImageBuffer, %function
VCTRL_GetImageBuffer:
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
	cmp	r0, #15
	bhi	.L534
	ldr	r1, .L537
	ldr	r3, [r1, r0, asl #2]
	cmp	r3, #0
	beq	.L535
	ldr	r0, [r3, #16]
	cmp	r0, #1
	bne	.L536
	ldr	r2, [r3, #528]
	cmp	r2, #17
	ldrls	pc, [pc, r2, asl #2]
	b	.L529
.L517:
	.word	.L516
	.word	.L518
	.word	.L519
	.word	.L520
	.word	.L529
	.word	.L521
	.word	.L522
	.word	.L529
	.word	.L523
	.word	.L524
	.word	.L525
	.word	.L525
	.word	.L525
	.word	.L526
	.word	.L529
	.word	.L529
	.word	.L527
	.word	.L528
.L528:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HEVCDEC_GetImageBuffer
.L516:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	H264DEC_GetImageBuffer
.L518:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VC1DEC_GetImageBuffer
.L519:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MPEG4DEC_GetImageBuffer
.L520:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MPEG2DEC_GetImageBuffer
.L521:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DIVX3DEC_GetImageBuffer
.L522:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	AVSDEC_GetImageBuffer
.L523:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	REAL8DEC_GetImageBuffer
.L524:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	REAL9DEC_GetImageBuffer
.L525:
	ldr	r2, [r1, #2492]
	tst	r2, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VP6DEC_GetImageBuffer
.L526:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VP8DEC_GetImageBuffer
.L527:
	add	r0, r3, #229376
	add	r0, r0, #120
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MVC_DEC_GetImageBuffer
.L529:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L536:
	ldr	ip, .L537+4
	movw	r2, #4782
	ldr	r3, .L537+8
.L533:
	ldr	r1, .L537+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L534:
	ldr	ip, .L537+4
	movw	r2, #4780
	ldr	r3, .L537+16
	b	.L533
.L535:
	ldr	ip, .L537+4
	mov	r0, r3
	movw	r2, #4781
	ldr	r3, .L537+20
	ldr	r1, .L537+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L538:
	.align	2
.L537:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC52
	.word	.LC1
	.word	.LC51
	.word	.LC38
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L546
	ldr	r3, .L550
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L547
	ldr	r2, [r3, #12]
	cmp	r2, #1
	bne	.L548
	cmp	r1, #0
	beq	.L549
	ldr	r2, [r1]
	mov	r0, #0
	str	r2, [r3, #1220]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L548:
	ldr	ip, .L550+4
	movw	r2, #4887
	ldr	r3, .L550+8
.L545:
	ldr	r1, .L550+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L546:
	ldr	ip, .L550+4
	movw	r2, #4885
	ldr	r3, .L550+16
	b	.L545
.L547:
	ldr	ip, .L550+4
	mov	r0, r3
	movw	r2, #4886
	ldr	r3, .L550+20
	ldr	r1, .L550+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L549:
	ldr	ip, .L550+4
	mov	r0, r1
	ldr	r3, .L550+24
	movw	r2, #4888
	ldr	r1, .L550+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L551:
	.align	2
.L550:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC54
	.word	.LC1
	.word	.LC6
	.word	.LC53
	.word	.LC55
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L559
	ldr	r3, .L563
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L560
	ldr	r3, [r0, #12]
	cmp	r3, #1
	bne	.L561
	cmp	r1, #0
	beq	.L562
	ldr	r3, .L563+4
	add	r0, r0, #1232
	mov	r2, #20
	add	r0, r0, #8
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L561:
	ldr	ip, .L563+4
	movw	r2, #4900
	ldr	r3, .L563+8
.L558:
	ldr	r1, .L563+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L559:
	ldr	ip, .L563+4
	movw	r2, #4898
	ldr	r3, .L563+16
	b	.L558
.L562:
	ldr	ip, .L563+4
	mov	r0, r1
	ldr	r3, .L563+20
	movw	r2, #4901
	ldr	r1, .L563+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L560:
	ldr	ip, .L563+4
	movw	r2, #4899
	ldr	r3, .L563+24
	ldr	r1, .L563+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L564:
	.align	2
.L563:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC54
	.word	.LC1
	.word	.LC6
	.word	.LC55
	.word	.LC53
	UNWIND(.fnend)
	.size	VCTRL_ConfigPVRInfo, .-VCTRL_ConfigPVRInfo
	.align	2
	.global	VCTRL_IsChanDecable
	.type	VCTRL_IsChanDecable, %function
VCTRL_IsChanDecable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	cmp	r0, #15
	mov	r4, r0
	bhi	.L568
	ldr	r5, .L574
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L568
	sub	r1, fp, #44
	bl	SM_GetInfo
	cmp	r0, #0
	bne	.L568
	ldr	r3, [fp, #-36]
	cmp	r3, #16
	bgt	.L569
	ldr	r3, [fp, #-28]
	cmp	r3, #524288
	ble	.L568
.L569:
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	subs	r0, r0, #1
	mvnne	r0, #0
	cmp	r0, #0
	bne	.L567
	ldr	r3, .L574+4
	ldr	r3, [r3]
	blx	r3
	ldr	r3, [r5, r4, asl #2]
	ldr	r3, [r3, #44]
	rsb	r0, r3, r0
	cmp	r0, #50
	movls	r0, #0
	mvnhi	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L568:
	mvn	r0, #0
.L567:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L575:
	.align	2
.L574:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VCTRL_IsChanDecable, .-VCTRL_IsChanDecable
	.align	2
	.global	VCTRL_IsChanSegEnough
	.type	VCTRL_IsChanSegEnough, %function
VCTRL_IsChanSegEnough:
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
	cmp	r0, #15
	bhi	.L579
	ldr	r3, .L580
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L579
	ldr	r0, [r3, #316]
	subs	r0, r0, #1
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L579:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L581:
	.align	2
.L580:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_IsChanSegEnough, .-VCTRL_IsChanSegEnough
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
	cmp	r0, #15
	bhi	.L588
	ldr	r3, .L589
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L588
	ldr	r2, [r3, #12]
	cmp	r2, #0
	beq	.L588
	ldr	r2, [r3, #16]
	cmp	r2, #0
	beq	.L588
	ldr	r2, [r3, #24]
	cmp	r2, #0
	beq	.L588
	ldr	r0, [r3, #528]
	cmp	r0, #20
	movne	r0, #0
	mvneq	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L588:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L590:
	.align	2
.L589:
	.word	.LANCHOR0
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
	ldr	r5, .L608
	mov	r4, r0
	ldr	r7, [r0, #352]
	mov	r2, #368
	mov	r6, r1
	mov	r1, #0
	ldr	r3, [r5, #48]
	blx	r3
	add	r0, r4, #8
	str	r7, [r4, #352]
	bl	ResetVoQueue
	ldr	r0, .L608+4
	mov	r2, #0
	str	r6, [r4]
.L595:
	ldr	r1, [r0], #4
	cmp	r1, #0
	add	r3, r1, #229376
	add	r3, r3, #120
	beq	.L592
	cmp	r4, r3
	beq	.L607
.L592:
	add	r2, r2, #1
	cmp	r2, #16
	bne	.L595
	mvn	r3, #0
	str	r3, [r4, #360]
.L593:
	ldr	r3, [r5, #68]
	mov	r0, #0
	ldr	r1, .L608+8
	blx	r3
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L607:
	cmn	r2, #1
	str	r2, [r4, #360]
	beq	.L593
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L609:
	.align	2
.L608:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC56
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L612
	mov	r2, #0
	ldr	r0, [r4, #360]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #360]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L613
	ldr	r1, [r5, #212]
	mov	r6, #0
	ldr	r0, [r4, #360]
	bl	FreeUsdByDec
	str	r6, [r5, #212]
	ldr	r1, [r5, #216]
	ldr	r0, [r4, #360]
	bl	FreeUsdByDec
	str	r6, [r5, #216]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L613:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L612:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #15
	mov	r4, r0
	mov	r7, r1
	bhi	.L633
	ldr	r6, .L640
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L634
	ldr	r2, [r3, #528]
	cmp	r2, #19
	bne	.L635
	ldr	r3, [r3, #468]
	cmp	r3, #2
	ble	.L636
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	bne	.L637
	mov	r1, r0
	mov	r0, r4
	bl	FSP_NewLogicFs
	subs	r8, r0, #0
	blt	.L638
	mov	r1, r8
	mov	r0, r4
	bl	FSP_GetLogicFs
	ldr	r9, .L640+4
	mov	r2, r8
	ldr	r1, .L640+8
	ldr	r3, [r9, #68]
	mov	r5, r0
	mov	r0, #18
	blx	r3
	cmp	r5, #0
	beq	.L639
	ldr	r2, [r5, #520]
	cmp	r2, #0
	beq	.L623
	ldr	r3, [r5, #524]
	cmp	r3, #0
	beq	.L623
	ldr	r1, [r5, #528]
	cmp	r1, #0
	beq	.L623
	ldr	ip, [r1, #12]
	mov	r0, #18
	ldr	r3, [r3, #12]
	ldr	r2, [r2, #12]
	ldr	r8, [r9, #68]
	ldr	r1, .L640+12
	str	ip, [sp]
	blx	r8
	ldr	r3, [r5, #520]
	mov	r0, #0
	ldr	r3, [r3, #12]
	str	r3, [r7]
	ldr	r3, [r6, r4, asl #2]
	ldr	r3, [r3, #464]
	str	r3, [r7, #8]
.L616:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L637:
	ldr	r3, .L640+4
	mov	r0, #0
	ldr	r1, .L640+16
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L616
.L635:
	ldr	r3, .L640+4
	mov	r0, #0
	ldr	r1, .L640+20
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L616
.L636:
	ldr	r3, .L640+4
	mov	r0, #0
	ldr	r1, .L640+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L616
.L623:
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r1, .L640+28
	blx	r3
	mvn	r0, #0
	b	.L616
.L633:
	ldr	ip, .L640+4
	movw	r2, #5269
	ldr	r3, .L640+32
	mov	r0, #0
	ldr	r1, .L640+36
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L616
.L638:
	ldr	r3, .L640+4
	mov	r0, #0
	ldr	r1, .L640+40
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L616
.L634:
	ldr	ip, .L640+4
	mov	r0, r3
	movw	r2, #5270
	ldr	r3, .L640+44
	ldr	r1, .L640+36
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L616
.L639:
	ldr	r3, [r9, #68]
	movw	r2, #5306
	ldr	r1, .L640+48
	mov	r0, #22
	blx	r3
	mvn	r0, #0
	b	.L616
.L641:
	.align	2
.L640:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC61
	.word	.LC63
	.word	.LC59
	.word	.LC57
	.word	.LC58
	.word	.LC64
	.word	.LC6
	.word	.LC1
	.word	.LC60
	.word	.LC2
	.word	.LC62
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
	ldr	r3, .L660
	ldr	r1, [r3, r0, asl #2]
	cmp	r1, #0
	beq	.L659
	ldr	r3, [r1, #528]
	cmp	r3, #19
	ldrls	pc, [pc, r3, asl #2]
	b	.L642
.L646:
	.word	.L645
	.word	.L647
	.word	.L648
	.word	.L649
	.word	.L642
	.word	.L650
	.word	.L651
	.word	.L642
	.word	.L652
	.word	.L653
	.word	.L654
	.word	.L654
	.word	.L654
	.word	.L655
	.word	.L642
	.word	.L642
	.word	.L656
	.word	.L657
	.word	.L642
	.word	.L658
.L658:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	USERDEC_Init
.L645:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_Init
.L647:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_Init
.L648:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_Init
.L649:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_Init
.L650:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_Init
.L651:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_Init
.L652:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_Init
.L653:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_Init
.L654:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_Init
.L655:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_Init
.L656:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_Init
.L657:
	add	r0, r1, #229376
	add	r1, r1, #536
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_Init
.L642:
	ldmfd	sp, {fp, sp, pc}
.L659:
	ldr	ip, .L660+4
	mov	r0, r1
	ldr	r3, .L660+8
	movw	r2, #5388
	ldr	r1, .L660+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L661:
	.align	2
.L660:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	InitSyntaxCtx, .-InitSyntaxCtx
	.align	2
	.global	VCTRL_GetChanMemSizeWithOption
	.type	VCTRL_GetChanMemSizeWithOption, %function
VCTRL_GetChanMemSizeWithOption:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 568
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #596)
	sub	sp, sp, #596
	subs	r4, r1, #0
	mov	r7, r0
	mov	r5, r2
	mov	r8, r3
	beq	.L696
	cmp	r2, #0
	beq	.L697
	cmp	r0, #26
	movw	r3, #27784
	movw	r6, #56880
	movt	r3, 8
	movt	r6, 176
	movne	r6, r3
	cmp	r8, #2
	beq	.L667
	ldr	r1, .L706
	ldr	r2, [r4, #36]
	ldr	r0, [r4, #60]
	ldr	ip, [r1, #2564]
	ldr	r3, [r1, #2560]
	add	r9, r0, ip
	add	r1, r2, r3
	orrs	lr, r9, r1
	bmi	.L698
	cmp	r1, #16
	strle	r1, [r4, #36]
	strle	r9, [r4, #60]
	bgt	.L699
.L670:
	subs	r3, r7, #25
	movne	r3, #1
	cmp	r8, #0
	movne	r3, #0
	cmp	r3, #0
	bne	.L700
.L667:
	ldr	r1, [r4, #36]
	cmp	r1, #0
	blt	.L671
	ldr	r2, [r4, #12]
	cmp	r2, #31
	ble	.L671
	ldr	r3, [r4, #16]
	cmp	r3, #31
	ble	.L671
	ldr	r0, [r4, #56]
	cmp	r0, #262144
	blt	.L671
	ldr	r0, [r4, #44]
	cmp	r0, #1
	beq	.L701
	cmp	r0, #2
	beq	.L702
.L673:
	ldr	r0, [r4, #40]
	cmp	r0, #0
	moveq	r0, #1
	bne	.L703
.L675:
	ldr	ip, .L706+4
	sub	r8, r7, #27
	cmp	r8, #6
	ldr	lr, [r4, #60]
	ldr	r9, [ip, #48]
	mvncc	ip, #1
	mvncs	ip, #0
	cmp	r9, #0
	beq	.L677
	add	r1, r1, lr
	str	ip, [sp, #12]
	add	r1, r1, #2
	stmia	sp, {r0, r1}
	sub	r0, fp, #608
	mov	r1, #0
	str	r0, [sp, #16]
	mov	r0, #1
	str	r1, [sp, #8]
	mvn	r1, #-2147483648
	blx	r9
	cmp	r0, #0
	bne	.L677
	ldr	r3, [fp, #-604]
	add	r2, r3, #16
	str	r2, [r5]
	ldr	r2, [r4, #144]
	cmp	r2, #1
	addne	r3, r3, #47616
	addne	r3, r3, #16
	ldreq	r3, [r4, #56]
	strne	r3, [r5]
	ldrne	r3, [r4, #56]
	addeq	r3, r3, #79872
	addeq	r3, r3, #528
	str	r6, [r5, #8]
	addne	r3, r3, #32768
	str	r3, [r5, #4]
	ldr	r3, [r4, #44]
	cmp	r3, #0
	beq	.L680
	ldr	r1, [r4, #20]
	movw	r0, #4060
	ldr	lr, [r4, #28]
	mov	r3, #4000
	ldr	ip, [r4, #32]
	mov	r2, #2208
	mul	r1, r0, r1
	mla	r3, r3, lr, r1
	mla	r3, r2, ip, r3
	cmp	r3, #0
	movcc	r3, #0
	cmp	r7, #26
	beq	.L704
.L680:
	cmp	r8, #5
	bhi	.L681
.L705:
	movw	r2, #51528
	movt	r2, 13
	cmp	r3, r2
	movcc	r3, r2
.L681:
	mov	r0, #0
	add	r3, r3, r6
	str	r3, [r5, #8]
.L664:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L703:
	add	r0, r1, #1
	cmp	r0, #17
	movge	r0, #17
	b	.L675
.L702:
	ldr	r0, [r4, #20]
	cmp	r0, #0
	ble	.L671
	ldr	r0, [r4, #24]
	cmp	r0, #0
	ble	.L671
.L695:
	ldr	r0, [r4, #28]
	cmp	r0, #0
	ble	.L671
	ldr	r0, [r4, #32]
	cmp	r0, #0
	bgt	.L673
.L671:
	ldr	r3, .L706+8
	mov	r0, #32
	ldr	r1, .L706+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L699:
	ldr	ip, .L706+8
	mov	r0, #32
	ldr	r1, .L706+16
	ldr	r10, [ip, #68]
	blx	r10
	mov	r3, #16
	str	r9, [r4, #60]
	str	r3, [r4, #36]
	b	.L670
.L677:
	ldr	r3, .L706+8
	movw	r2, #5658
	ldr	r1, .L706+20
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L701:
	ldr	r0, [r4, #20]
	cmp	r0, #0
	bgt	.L695
	b	.L671
.L704:
	movw	r0, #3992
	mov	r2, #2240
	mla	r1, r0, lr, r1
	mla	ip, r2, ip, r1
	cmp	r3, ip
	movcc	r3, ip
	cmp	r8, #5
	bls	.L705
	b	.L681
.L700:
	ldr	r3, .L706+8
	mov	r0, #32
	ldr	r1, .L706+24
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L664
.L698:
	ldr	r1, .L706+8
	stmia	sp, {r0, ip}
	mov	r0, #32
	ldr	r4, [r1, #68]
	ldr	r1, .L706+28
	blx	r4
	mvn	r0, #0
	b	.L664
.L697:
	ldr	ip, .L706+8
	mov	r0, r2
	ldr	r3, .L706+32
	movw	r2, #5491
	ldr	r1, .L706+36
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L664
.L696:
	ldr	ip, .L706+8
	mov	r0, r4
	ldr	r3, .L706+40
	movw	r2, #5490
	ldr	r1, .L706+36
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L664
.L707:
	.align	2
.L706:
	.word	.LANCHOR0
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC70
	.word	.LC68
	.word	.LC71
	.word	.LC69
	.word	.LC67
	.word	.LC66
	.word	.LC1
	.word	.LC65
	UNWIND(.fnend)
	.size	VCTRL_GetChanMemSizeWithOption, .-VCTRL_GetChanMemSizeWithOption
	.align	2
	.global	VCTRL_GetChanMemSize
	.type	VCTRL_GetChanMemSize, %function
VCTRL_GetChanMemSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 592
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #628)
	sub	sp, sp, #628
	cmp	r0, #32
	mov	r4, r0
	str	r1, [fp, #-620]
	str	r2, [fp, #-624]
	bhi	.L732
	mov	r2, r0, asl #5
	mov	r3, r0, asl #2
	ldr	r9, .L734
	str	r3, [fp, #-632]
	rsb	r3, r3, r2
	add	r3, r9, r3
	str	r2, [fp, #-636]
	sub	r2, r0, #18
	ldr	r1, [r3, #16]
	ldr	r8, [r3, #12]
	ldr	r10, [r3, #8]
	str	r1, [fp, #-616]
	ldr	r1, [r3, #20]
	str	r1, [fp, #-628]
	cmp	r2, #7
	ldrls	pc, [pc, r2, asl #2]
	b	.L711
.L713:
	.word	.L727
	.word	.L727
	.word	.L727
	.word	.L727
	.word	.L727
	.word	.L714
	.word	.L714
	.word	.L714
.L727:
	mov	r3, #3
.L712:
	ldr	r7, .L734+4
	rsb	r3, r3, r8
	sub	r3, r3, #2
	ldr	r2, [r7, #2560]
	cmp	r2, #0
	movlt	r2, #0
	strlt	r2, [r7, #2560]
	cmp	r3, #15
	movgt	r6, #0
	bgt	.L716
	ldr	r6, [r7, #2560]
	add	r3, r3, r6
	cmp	r3, #16
	rsbgt	r3, r3, #16
	addgt	r6, r6, r3
.L716:
	add	r3, r10, r6
	ldr	r5, [r7, #2564]
	cmp	r3, #0
	ble	.L733
	cmp	r3, #17
	movlt	r10, r3
	movge	r10, #17
.L718:
	cmp	r4, #23
	bhi	.L719
	ldr	r3, [fp, #-616]
	add	r5, r6, r5
	add	r2, r5, r8
	add	r1, r3, r5
	ldr	r3, [fp, #-628]
	cmp	r2, #0
	cmpgt	r1, #0
	add	r5, r3, r5
	movle	r3, #1
	movgt	r3, #0
	cmp	r5, #0
	orrle	r3, r3, #1
	cmp	r3, #0
	streq	r5, [fp, #-628]
	streq	r1, [fp, #-616]
	moveq	r8, r2
	beq	.L719
	ldr	r1, [r7, #2564]
	mov	r3, r6
	ldr	ip, .L734+8
	mov	r2, r8
	str	r6, [sp, #20]
	mov	r0, #32
	str	r1, [sp, #24]
	str	r1, [sp, #12]
	str	r1, [sp]
	ldr	r1, [fp, #-628]
	str	r6, [sp, #8]
	str	r1, [sp, #16]
	ldr	r1, [fp, #-616]
	str	r1, [sp, #4]
	ldr	r1, .L734+12
	ldr	r4, [ip, #68]
	blx	r4
.L719:
	ldr	r5, .L734+16
	ldr	r6, [r5, #48]
	cmp	r6, #0
	beq	.L720
	ldr	r3, [fp, #-636]
	mov	r1, #0
	ldr	r2, [fp, #-632]
	mov	r0, #1
	str	r8, [sp, #4]
	mvn	r8, #0
	rsb	r7, r2, r3
	str	r10, [sp]
	add	r4, r9, r7
	ldr	r2, [r9, r7]
	sub	r9, fp, #608
	ldr	r3, [r4, #4]
	str	r1, [sp, #8]
	mvn	r1, #-2147483648
	str	r9, [sp, #16]
	str	r8, [sp, #12]
	blx	r6
	ldr	r6, .L734
	cmp	r0, #0
	bne	.L720
	ldr	r2, [fp, #-620]
	ldr	r3, [fp, #-604]
	add	r3, r3, #47616
	add	r3, r3, #16
	str	r3, [r2]
	ldr	r2, [fp, #-624]
	ldr	r3, [r4, #24]
	add	r3, r3, #32768
	str	r3, [r2]
	ldr	r3, [r5, #48]
	subs	ip, r3, #0
	beq	.L722
	ldr	r3, [r4, #4]
	mvn	r1, #-2147483648
	ldr	r2, [r6, r7]
	str	r0, [sp, #8]
	ldr	r0, [fp, #-616]
	str	r9, [sp, #16]
	str	r8, [sp, #12]
	str	r0, [sp, #4]
	mov	r0, #1
	str	r10, [sp]
	blx	ip
	subs	ip, r0, #0
	bne	.L722
	ldr	r2, [fp, #-620]
	ldr	r3, [fp, #-604]
	add	r3, r3, #47616
	add	r3, r3, #16
	str	r3, [r2, #4]
	ldr	r2, [fp, #-624]
	ldr	r3, [r4, #24]
	add	r3, r3, #32768
	str	r3, [r2, #4]
	ldr	r5, [r5, #48]
	cmp	r5, #0
	beq	.L725
	ldr	r2, [r6, r7]
	mvn	r1, #-2147483648
	ldr	r3, [r4, #4]
	mov	r0, #1
	str	ip, [sp, #8]
	ldr	ip, [fp, #-628]
	str	r9, [sp, #16]
	str	r8, [sp, #12]
	stmia	sp, {r10, ip}
	blx	r5
	cmp	r0, #0
	bne	.L725
	ldr	r2, [fp, #-620]
	ldr	r3, [fp, #-604]
	add	r3, r3, #47616
	add	r3, r3, #16
	str	r3, [r2, #8]
	ldr	r2, [fp, #-624]
	ldr	r3, [r4, #24]
	add	r3, r3, #32768
	str	r3, [r2, #8]
.L730:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L714:
	mov	r3, #1
	b	.L712
.L720:
	ldr	r3, .L734+8
	movw	r2, #5827
.L731:
	ldr	r1, .L734+20
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L711:
	mov	r3, #6
	b	.L712
.L722:
	ldr	r3, .L734+8
	movw	r2, #5848
	b	.L731
.L725:
	ldr	r3, .L734+8
	movw	r2, #5869
	b	.L731
.L733:
	ldr	ip, .L734+8
	mov	r2, r10
	mov	r3, r6
	ldr	r1, .L734+24
	mov	r0, #32
	ldr	ip, [ip, #68]
	blx	ip
	cmp	r10, #17
	movge	r10, #17
	b	.L718
.L732:
	ldr	ip, .L734+8
	movw	r2, #5723
	ldr	r3, .L734+28
	mov	r0, #0
	ldr	r1, .L734+32
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L730
.L735:
	.align	2
.L734:
	.word	CapItem
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC74
	.word	g_vdm_hal_fun_ptr
	.word	.LC75
	.word	.LC73
	.word	.LC72
	.word	.LC1
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
	ldr	r5, [r0, #12]
	mov	r4, r0
	ldr	r6, [r0, #8]
	cmp	r5, #0
	ldr	r7, [r0, #4]
	beq	.L737
	ldr	r3, .L781
	ldr	r3, [r3, #44]
	cmp	r3, #0
	beq	.L772
	mov	r0, #0
	ldr	r8, .L781+4
	blx	r3
.L740:
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_ReleaseMemBlock
	ldr	r3, [r8, #48]
	mov	r2, #16
	mov	r1, #0
	mov	r0, r4
	blx	r3
.L737:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #28]
	ldr	r6, [r4, #24]
	cmp	r5, #0
	ldr	r7, [r4, #20]
	bne	.L773
.L741:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	bl	SM_InstInit
	ldr	r5, [r4, #60]
	ldr	r6, [r4, #56]
	cmp	r5, #0
	ldr	r7, [r4, #52]
	bne	.L774
.L742:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #108]
	ldr	r6, [r4, #104]
	cmp	r5, #0
	ldr	r7, [r4, #100]
	bne	.L775
.L743:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #92]
	ldr	r6, [r4, #88]
	cmp	r5, #0
	ldr	r7, [r4, #84]
	bne	.L776
.L744:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #76]
	ldr	r6, [r4, #72]
	cmp	r5, #0
	ldr	r7, [r4, #68]
	bne	.L777
.L745:
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r5, [r4, #124]
	ldr	r6, [r4, #120]
	cmp	r5, #0
	ldr	r7, [r4, #116]
	bne	.L778
.L746:
	ldr	r4, .L781+8
	mov	r2, r5
	mov	r1, r7
	mov	r0, r6
	bl	MEM_DelMemRecord
	ldr	r3, [r4, #224]
	cmp	r3, #1
	beq	.L779
.L747:
	ldr	r3, [r4, #228]
	ldr	r4, .L781+8
	cmp	r3, #1
	beq	.L780
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L773:
	mov	r0, #0
	bl	SM_CloseSCDDrv
	ldr	r1, [r4, #20]
	ldr	r0, [r4, #24]
	bl	MEM_ReleaseMemBlock
	ldr	r3, .L781+4
	mov	r2, #16
	mov	r1, #0
	add	r0, r4, r2
	ldr	r3, [r3, #48]
	blx	r3
	b	.L741
.L774:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L781+4
	mov	r2, #16
	mov	r1, #0
	add	r0, r4, #48
	ldr	r3, [r3, #48]
	blx	r3
	b	.L742
.L778:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L781+4
	add	r0, r4, #112
	mov	r2, #16
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	b	.L746
.L777:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L781+4
	mov	r2, #16
	mov	r1, #0
	add	r0, r4, #64
	ldr	r3, [r3, #48]
	blx	r3
	b	.L745
.L776:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L781+4
	mov	r2, #16
	mov	r1, #0
	add	r0, r4, #80
	ldr	r3, [r3, #48]
	blx	r3
	b	.L744
.L775:
	mov	r1, r7
	mov	r0, r6
	bl	MEM_UnmapRegisterAddr
	ldr	r3, .L781+4
	mov	r2, #16
	mov	r1, #0
	add	r0, r4, #96
	ldr	r3, [r3, #48]
	blx	r3
	b	.L743
.L772:
	ldr	r8, .L781+4
	mov	r0, r3
	movw	r2, #6248
	ldr	r1, .L781+12
	ldr	r3, [r8, #68]
	blx	r3
	b	.L740
.L780:
	ldr	r3, .L781+4
	mov	r0, #3
	ldr	r5, [r3, #184]
	bl	VFMW_GetString
	mov	r2, #0
	mov	r1, r0
	mov	r0, #136
	blx	r5
	mov	r3, #0
	mov	r0, #0
	str	r3, [r4, #228]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L779:
	ldr	r3, .L781+4
	mov	r0, #0
	ldr	r5, [r3, #184]
	bl	VFMW_GetString
	mov	r2, #0
	mov	r1, r0
	mov	r0, #127
	blx	r5
	mov	r3, #0
	str	r3, [r4, #224]
	b	.L747
.L782:
	.align	2
.L781:
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC8
	UNWIND(.fnend)
	.size	CloseDrivers, .-CloseDrivers
	.align	2
	.global	OpenDrivers
	.type	OpenDrivers, %function
OpenDrivers:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r5, r0, #48
	mov	r4, r0
	mov	r0, #0
	mov	r1, #4096
	mov	r2, r5
	movt	r0, 63683
	bl	MEM_MapRegisterAddr
	subs	r6, r0, #0
	bne	.L784
	ldr	r2, [r4, #60]
	add	r7, r4, #96
	ldr	r1, [r4, #52]
	ldr	r0, [r4, #56]
	bl	MEM_AddMemRecord
	mov	r0, #0
	mov	r2, r7
	movt	r0, 63686
	mov	r1, #4096
	bl	MEM_MapRegisterAddr
	cmp	r0, #0
	bne	.L790
	ldr	r5, .L813
	ldr	r3, [r5, #24]
	cmp	r3, #0
	beq	.L789
	blx	r3
	subs	r6, r0, #0
	beq	.L812
.L789:
	ldr	r3, .L813+4
	mov	r0, r7
.L808:
	mov	r2, #16
	mov	r1, #0
.L811:
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
.L787:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L812:
	ldr	r2, [r4, #108]
	add	r7, r4, #80
	ldr	r1, [r4, #100]
	ldr	r0, [r4, #104]
	bl	MEM_AddMemRecord
	mov	r0, #49152
	mov	r2, r7
	movt	r0, 63683
	mov	r1, #4096
	bl	MEM_MapRegisterAddr
	subs	r8, r0, #0
	bne	.L790
	ldr	r9, .L813+4
	ldr	r2, [r4, #92]
	ldr	r1, [r4, #84]
	ldr	r0, [r4, #88]
	bl	MEM_AddMemRecord
	mov	r0, #11
	ldr	r6, [r9, #72]
	bl	VFMW_GetString
	mov	r3, r8
	mov	r1, #20
	mov	r2, r0
	sub	r0, fp, #64
	blx	r6
	ldr	r3, [r5, #36]
	cmp	r3, #0
	beq	.L792
	blx	r3
	subs	r2, r0, #0
	ble	.L792
	str	r8, [sp]
	mov	r3, r4
	mov	r1, r8
	sub	r0, fp, #64
	bl	MEM_AllocMemBlock
	subs	r6, r0, #0
	bne	.L793
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #4]
	ldr	r0, [r4, #8]
	bl	MEM_AddMemRecord
	ldr	r3, [r9, #48]
	mov	r2, #12
	mov	r1, r6
	sub	r0, fp, #76
	blx	r3
	ldr	r3, [r5, #40]
	ldr	r1, [r4, #8]
	ldr	r2, [r4, #12]
	cmp	r3, #0
	str	r6, [fp, #-68]
	str	r1, [fp, #-76]
	str	r2, [fp, #-72]
	beq	.L794
	sub	r0, fp, #76
	blx	r3
	cmp	r0, #0
	bne	.L794
	bl	VDMDRV_Init
	mov	r0, #12
	ldr	r8, [r9, #72]
	bl	VFMW_GetString
	mov	r3, #0
	mov	r1, #20
	mov	r6, r3
	add	r7, r4, #16
	ldr	r5, .L813+4
	mov	r2, r0
	sub	r0, fp, #64
	blx	r8
	bl	get_scd_msg_size
	mov	r3, r7
	str	r6, [sp]
	mov	r1, r6
	mov	r2, r0
	sub	r0, fp, #64
	bl	MEM_AllocMemBlock
	subs	r8, r0, #0
	bne	.L798
	ldr	r2, [r4, #28]
	ldr	r1, [r4, #20]
	ldr	r0, [r4, #24]
	bl	MEM_AddMemRecord
	mov	r2, r8
	ldr	r1, [r4, #28]
	ldr	r0, [r4, #24]
	bl	SM_OpenSCDDrv
	subs	r6, r0, #0
	bne	.L807
	bl	SM_InstInit
	mov	r0, r6
	ldr	r8, [r5, #180]
	bl	VFMW_GetString
	str	r6, [sp]
	mov	r2, #32
	ldr	r1, .L813+8
	mov	r3, r0
	mov	r0, #127
	blx	r8
	subs	r8, r0, #0
	bne	.L798
	ldr	r6, .L813+12
	mov	r0, #3
	mov	r9, #1
	ldr	r10, [r5, #180]
	str	r9, [r6, #224]
	bl	VFMW_GetString
	str	r8, [sp]
	mov	r2, #32
	ldr	r1, .L813+16
	mov	r3, r0
	mov	r0, #136
	blx	r10
	cmp	r0, #0
	streq	r9, [r6, #228]
	beq	.L787
.L807:
	ldr	r3, [r5, #48]
	mov	r1, r8
.L810:
	mov	r2, #16
	mov	r0, r7
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L787
.L790:
	ldr	r3, .L813+4
	mov	r1, r6
	mov	r0, r7
	mov	r2, #16
	b	.L811
.L798:
	ldr	r3, [r5, #48]
	mov	r1, r6
	b	.L810
.L794:
	ldr	r3, [r9, #48]
	mov	r2, #16
	mov	r1, #0
.L809:
	mov	r0, r4
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L787
.L793:
	ldr	r3, [r9, #48]
	mov	r1, r8
	mov	r2, #16
	b	.L809
.L792:
	ldr	r3, [r9, #48]
	mov	r2, #16
	mov	r1, #0
	mov	r0, r7
	blx	r3
	mov	r0, r4
	bl	CloseDrivers
	mvn	r0, #0
	b	.L787
.L784:
	ldr	r3, .L813+4
	mov	r0, r5
	b	.L808
.L814:
	.align	2
.L813:
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	VCTRL_Isr_0
	.word	.LANCHOR0
	.word	VCTRL_Scd_Isr
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	r4, .L850
	ldr	r6, .L850+4
	mov	r2, #8
	sub	r0, fp, #44
	mov	r1, #0
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r5, [r6, #64]
	cmp	r5, #0
	bne	.L836
	mov	r1, #1024
	ldr	r3, [r4, #84]
	str	r5, [fp, #-48]
	ldr	r0, .L850+8
	blx	r3
	ldr	r3, [r4, #100]
	ldr	r1, .L850+12
	ldr	r0, .L850+8
	blx	r3
	cmp	r0, #0
	str	r0, [fp, #-48]
	beq	.L817
	ldr	r3, [r4, #96]
	sub	r0, fp, #48
	ldr	r1, .L850+16
	blx	r3
	cmp	r0, #0
	beq	.L837
	sub	r0, fp, #48
	ldr	r3, [r4, #96]
	ldr	r1, .L850+20
	blx	r3
	cmp	r0, #0
	beq	.L845
	mov	r2, r5
	ldr	r3, [r4, #88]
	mov	r1, r5
	blx	r3
	mov	r2, r0
	str	r0, [r6, #2560]
.L821:
	add	r3, r2, #4992
	movw	r1, #10000
	add	r3, r3, #8
	movw	r7, #5000
	cmp	r3, r1
	bhi	.L822
	cmp	r2, r7
	movw	r3, #60536
.L844:
	movt	r3, 65535
	movge	r2, r7
	cmp	r2, r3
	movlt	r2, r3
.L818:
	str	r2, [r6, #2560]
.L820:
	mov	r8, #0
	ldr	r3, [r4, #84]
	mov	r1, #1024
	str	r8, [fp, #-48]
	ldr	r0, .L850+8
	blx	r3
	ldr	r3, [r4, #100]
	ldr	r1, .L850+24
	ldr	r0, .L850+8
	blx	r3
	ldr	r9, .L850+4
	ldr	r7, .L850
	cmp	r0, r8
	str	r0, [fp, #-48]
	beq	.L823
	ldr	r3, [r7, #96]
	sub	r0, fp, #48
	ldr	r1, .L850+16
	blx	r3
	cmp	r0, r8
	beq	.L824
	sub	r0, fp, #48
	ldr	r3, [r7, #96]
	ldr	r1, .L850+20
	blx	r3
	cmp	r0, r8
	beq	.L846
	mov	r2, r8
	ldr	r3, [r7, #88]
	mov	r1, r8
	blx	r3
	mov	r2, r0
	str	r0, [r9, #2564]
.L827:
	add	r3, r2, #4992
	movw	r1, #10000
	add	r3, r3, #8
	movw	r7, #5000
	cmp	r3, r1
	bhi	.L828
	cmp	r2, r7
	movw	r3, #60536
	movt	r3, 65535
	movlt	r5, r2
	movge	r5, r7
	cmp	r5, r3
	movlt	r5, r3
.L824:
	str	r5, [r6, #2564]
.L826:
	ldr	r5, [r6, #3592]
	mov	r3, #0
	ldr	r7, .L850+4
	cmp	r5, r3
	str	r3, [fp, #-48]
	beq	.L829
	ldr	r2, .L850+28
	and	r3, r5, #1
	ubfx	r1, r5, #1, #1
	strb	r3, [r7, #3596]
	ubfx	r3, r5, #2, #1
	ubfx	r5, r5, #3, #1
	strb	r1, [r2]
	strb	r3, [r7, #3597]
	strb	r5, [r7, #3598]
.L830:
	ldr	r5, .L850+4
	mov	r2, #176
	ldr	r3, [r4, #48]
	mov	r1, #0
	add	r0, r5, #64
	mov	r7, #1
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #64
	mov	r1, #0
	mov	r0, r5
	blx	r3
	ldr	r1, .L850+32
	sub	r0, fp, #44
	mov	r2, #134217728
	mov	r3, #75497472
	str	r2, [fp, #-44]
	str	r1, [r6, #3600]
	str	r3, [fp, #-40]
	str	r7, [r6, #68]
	bl	MEM_InitMemManager
	bl	FSP_Init
	ldr	r6, .L850
	bl	ChanCtx_Init
	ldr	r3, [r4, #48]
	mov	r2, #64
	mov	r1, #0
	ldr	r0, .L850+36
	blx	r3
	add	r0, r5, #88
	bl	OpenDrivers
	cmp	r0, #0
	bne	.L847
	ldr	r3, [r6, #128]
	mov	r1, r7
	blx	r3
	ldr	r3, [r6, #176]
	ldr	r2, .L850+40
	add	r0, r5, #76
	ldr	r1, .L850+44
	blx	r3
	cmp	r0, #0
	streq	r7, [r5, #64]
	moveq	r3, #3
	streq	r3, [r5, #68]
	bne	.L848
.L816:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L829:
	ldr	r3, [r4, #84]
	mov	r1, #1024
	ldr	r0, .L850+8
	blx	r3
	ldr	r3, [r4, #100]
	ldr	r1, .L850+48
	ldr	r0, .L850+8
	blx	r3
	ldr	r8, .L850
	cmp	r0, #0
	str	r0, [fp, #-48]
	beq	.L830
	ldr	r3, [r8, #96]
	sub	r0, fp, #48
	ldr	r1, .L850+16
	blx	r3
	cmp	r0, #0
	ldreq	r0, [r7, #3592]
	beq	.L832
	sub	r0, fp, #48
	ldr	r3, [r8, #96]
	ldr	r1, .L850+20
	blx	r3
	cmp	r0, #0
	beq	.L849
	ldr	r3, [r8, #88]
	mov	r2, r5
	mov	r1, r5
	blx	r3
	str	r0, [r7, #3592]
.L832:
	ldr	r2, .L850+28
	and	r3, r0, #1
	ubfx	r1, r0, #1, #1
	strb	r3, [r6, #3596]
	ubfx	r3, r0, #2, #1
	ubfx	r0, r0, #3, #1
	strb	r1, [r2]
	strb	r3, [r6, #3597]
	strb	r0, [r6, #3598]
	b	.L830
.L823:
	ldr	r2, [r9, #2564]
	b	.L827
.L817:
	ldr	r2, [r6, #2560]
	b	.L821
.L828:
	ldr	r3, [r4, #68]
	mov	r0, #32
	ldr	r1, .L850+52
	blx	r3
	ldr	r5, [r6, #2564]
	movw	r3, #60536
	cmp	r5, r7
	movt	r3, 65535
	movge	r5, r7
	cmp	r5, r3
	movlt	r5, r3
	b	.L824
.L822:
	ldr	r3, [r4, #68]
	mov	r0, #32
	ldr	r1, .L850+56
	blx	r3
	ldr	r2, [r6, #2560]
	movw	r3, #60536
	cmp	r2, r7
	b	.L844
.L837:
	mov	r2, r5
	b	.L818
.L836:
	mvn	r0, #0
	b	.L816
.L845:
	ldr	r7, [r4, #68]
	movw	r3, #7347
	ldr	r2, .L850+60
	mov	r0, #22
	ldr	r1, .L850+64
	blx	r7
	b	.L820
.L846:
	ldr	r5, [r7, #68]
	movw	r3, #7394
	ldr	r2, .L850+68
	mov	r0, #22
	ldr	r1, .L850+64
	blx	r5
	b	.L826
.L847:
	ldr	r3, [r6, #68]
	mov	r0, r7
	ldr	r1, .L850+72
	blx	r3
	mvn	r0, #0
	b	.L816
.L849:
	ldr	r5, [r8, #68]
	movw	r3, #7451
	ldr	r2, .L850+76
	mov	r0, #22
	ldr	r1, .L850+64
	blx	r5
	b	.L830
.L848:
	add	r0, r5, #88
	bl	CloseDrivers
	mvn	r0, #0
	b	.L816
.L851:
	.align	2
.L850:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LANCHOR0+2568
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC81
	.word	.LANCHOR2
	.word	VCTRL_EventReport
	.word	.LANCHOR0+3604
	.word	VFMW_CTRL_thread_proc
	.word	.LC85
	.word	.LC83
	.word	.LC82
	.word	.LC80
	.word	.LANCHOR1+140
	.word	.LC79
	.word	.LANCHOR1+160
	.word	.LC84
	.word	.LANCHOR1+180
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
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
	ldr	r6, .L859
	movge	r5, r4
	mov	r5, r5, asr #3
	mov	r7, r0
	str	r1, [sp, #4]
	mov	r8, r1
	str	r4, [sp]
	sub	r3, r3, ip, asr #31
	mov	r2, r5
	ldr	r9, [r6, #68]
	ldr	r1, .L859+4
	mov	r0, #30
	blx	r9
	cmp	r7, #3
	beq	.L857
	cmp	r4, r8
	blt	.L858
.L856:
	mov	r4, r7
.L854:
	ldr	r5, [r6, #68]
	mov	r2, r7
	mov	r3, r4
	ldr	r1, .L859+8
	mov	r0, #30
	blx	r5
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L858:
	ldr	r3, [r6, #68]
	mov	r0, #30
	ldr	r1, .L859+12
	mov	r4, #3
	blx	r3
	b	.L854
.L857:
	cmp	r5, r8
	ble	.L856
	ldr	r3, [r6, #68]
	mov	r0, #30
	ldr	r1, .L859+16
	mov	r4, #0
	blx	r3
	b	.L854
.L860:
	.align	2
.L859:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC86
	.word	.LC89
	.word	.LC88
	.word	.LC87
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
	ldr	ip, .L870
	mov	r2, #0
.L864:
	ldr	r1, [ip], #4
	cmp	r1, #0
	add	r3, r1, #229376
	add	r3, r3, #120
	beq	.L862
	cmp	r0, r3
	beq	.L865
.L862:
	add	r2, r2, #1
	cmp	r2, #16
	bne	.L864
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L865:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L871:
	.align	2
.L870:
	.word	.LANCHOR0
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
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L883
	mov	r2, #0
.L876:
	ldr	r3, [ip], #4
	cmp	r3, #0
	beq	.L873
	ldr	r1, [r3, #208]
	cmp	r1, r0
	bhi	.L874
	ldr	lr, [r3, #212]
	add	r1, r1, lr
	cmp	r0, r1
	bcc	.L878
.L874:
	ldr	r1, [r3, #224]
	cmp	r0, r1
	bcc	.L873
	ldr	r3, [r3, #228]
	add	r1, r1, r3
	cmp	r0, r1
	bcc	.L878
.L873:
	add	r2, r2, #1
	cmp	r2, #16
	bne	.L876
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L878:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L884:
	.align	2
.L883:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetChanIDByMemAddr, .-VCTRL_GetChanIDByMemAddr
	.align	2
	.global	DecChanSyntax
	.type	DecChanSyntax, %function
DecChanSyntax:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	cmp	r0, #15
	mov	r4, r0
	bhi	.L955
	ldr	r6, .L970
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	beq	.L956
	ldr	r9, [r0, #16]
	cmp	r9, #1
	bne	.L957
	ldr	r5, [r0, #28]
	cmp	r5, #0
	bne	.L958
	ldr	r7, .L970+4
	mov	r3, r4, asl #2
	str	r5, [r0, #316]
	mov	r8, r3
	str	r3, [fp, #-48]
	ldr	r3, [r7]
	blx	r3
	add	r2, r6, r8
	ldr	r1, .L970+8
	ldr	r3, [r2, #3668]
	ldr	r1, [r1]
	rsb	r3, r3, r0
	cmp	r3, r1
	ldr	r3, [r6, r4, asl #2]
	strhi	r0, [r2, #3668]
	movhi	r10, r9
	movls	r10, r5
	ldr	r3, [r3, #528]
	ldr	r1, .L970
	sub	r2, r3, #10
	cmp	r2, #2
	bhi	.L892
	ldr	r2, [r1, #2492]
	tst	r2, #1
	bne	.L892
.L893:
	mov	r0, r4
	bl	VCTRL_GetImageBuffer
	cmp	r0, #1
	beq	.L894
	cmp	r10, #1
	mvnne	r5, #2
	beq	.L959
.L932:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L892:
	sub	r2, r3, #15
	bics	r2, r2, #4
	movne	r2, #1
	moveq	r2, #0
	cmp	r3, #4
	moveq	r3, #0
	andne	r3, r2, #1
	cmp	r3, #0
	beq	.L893
	mov	r0, r4
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L893
	cmp	r10, #1
	mvnne	r5, #1
	bne	.L932
	ldr	r3, [r7, #68]
	mov	r2, r4
	ldr	r1, .L970+12
	mov	r0, #23
	blx	r3
	mvn	r5, #1
	b	.L932
.L894:
	ldr	r3, [r6, r4, asl #2]
	ldr	r2, [r3, #1404]
	str	r3, [fp, #-52]
	cmp	r2, #0
	bne	.L960
.L895:
	ldr	r3, [fp, #-52]
	ldrb	r3, [r3, #665]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L952
	ldr	r3, [fp, #-52]
	add	r3, r3, #672
	str	r3, [fp, #-56]
.L898:
	ldr	r3, [fp, #-56]
	ldr	ip, [r7, #68]
	ldrd	r0, [r3, #40]
	ldrd	r8, [r3, #24]
	strd	r0, [fp, #-68]
	mov	r0, #29
	ldrd	r2, [fp, #-68]
	ldr	r1, .L970+16
	strd	r2, [sp]
	mov	r2, r8
	mov	r3, r9
	blx	ip
	ldr	ip, [r6, r4, asl #2]
	ldr	r1, [ip, #48]
	cmp	r1, #1
	beq	.L961
	sub	r3, r1, #2
	cmp	r1, #6
	cmpne	r3, #1
	bls	.L919
.L901:
	ldr	r3, [fp, #-56]
	mvn	r2, #0
	ldrd	r0, [r3, #24]
	mvn	r3, #0
	cmp	r1, r3
	add	r3, ip, #592
	cmpeq	r0, r2
	beq	.L962
	strd	r0, [r3, #-8]
.L912:
	ldr	r3, [fp, #-56]
	add	lr, ip, #608
	ldrd	r2, [r3, #40]
	mov	r8, r2
	mov	r9, r3
	add	r2, ip, #624
	mov	r3, r1
	str	r2, [fp, #-60]
	mov	r1, r9
	mov	r2, r0
	mov	r0, r8
	strd	r0, [lr, #-8]
	ldr	r1, [fp, #-56]
	strd	r8, [fp, #-68]
	ldrd	r0, [r1, #48]
	mov	r9, r1
	ldr	r1, [fp, #-60]
	mov	r8, r0
	mov	r0, #29
	strd	r8, [r1, #-8]
	ldr	r8, [fp, #-52]
	ldr	r1, .L970+20
	ldr	lr, [r8, #728]
	str	lr, [ip, #632]
	ldr	lr, [r8, #732]
	str	lr, [ip, #636]
	ldr	lr, [r8, #736]
	str	lr, [ip, #640]
	ldr	lr, [r8, #740]
	ldrd	r8, [fp, #-68]
	str	lr, [ip, #656]
	strd	r8, [sp]
	ldr	ip, [r7, #68]
	blx	ip
.L910:
	mov	r0, #3
	bl	CHECK_REC_POS_ENABLE
	adds	r3, r0, #0
	movne	r3, #1
	cmp	r10, #1
	movne	r3, #0
	cmp	r3, #0
	bne	.L963
.L913:
	ldr	r3, [r6, r4, asl #2]
	ldr	r2, [fp, #-52]
	ldr	r9, .L970
	add	r0, r2, #664
	add	r2, r3, #229376
	ldr	r1, [r3, #528]
	add	r2, r2, #120
	bl	DecodeStream
	ldr	r0, [r6, r4, asl #2]
	ldr	r3, [r0, #528]
	cmp	r3, #17
	beq	.L964
.L914:
	mov	r0, #4
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L932
	ldr	r3, [r7]
	blx	r3
	ldr	r3, [fp, #-48]
	ldr	r1, .L970+24
	add	r6, r6, r3
	ldr	r3, [r6, #3732]
	ldr	r1, [r1]
	rsb	r3, r3, r0
	mov	r2, r0
	cmp	r3, r1
	bls	.L932
	mov	r0, r4
	str	r2, [r6, #3732]
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L932
	mov	r2, r4, asl #24
	movw	r1, #7012
	add	r2, r2, #262144
	ldr	r0, .L970+28
	bl	DBG_AddTrace
	b	.L932
.L960:
	cmp	r2, #1
	beq	.L965
	ldr	r3, [fp, #-52]
	add	r9, r3, #225280
	ldr	r3, [r9, #2860]
.L918:
	ldr	r4, [r7, #68]
	mov	r0, #31
	ldr	r1, .L970+32
	mvn	r5, #0
	blx	r4
	b	.L932
.L959:
	ldr	r3, [r7, #68]
	mov	r2, r4
	ldr	r1, .L970+36
	mov	r0, #23
	blx	r3
	mvn	r5, #2
	b	.L932
.L952:
	ldr	r2, [fp, #-52]
	ldr	r3, [r2, #1444]
	cmp	r3, #0
	beq	.L953
	add	r3, r2, #672
	str	r3, [fp, #-56]
	b	.L898
.L961:
	add	r3, ip, #229376
	ldr	r3, [r3, #120]
	ldr	r1, [r3, #548]
	sxtb	r1, r1
	cmp	r1, #1
	bne	.L901
.L919:
	add	r0, ip, #1072
	ldr	r2, [fp, #-56]
	add	r0, r0, #8
	bl	IsNewpicSeg
	cmp	r0, #0
	bne	.L902
	ldr	r1, [r6, r4, asl #2]
	add	r0, r1, #592
	ldr	r3, [r1, #48]
	cmp	r3, #3
	beq	.L966
	ldrd	r8, [r0]
	mvn	r3, #0
	mvn	r2, #0
	cmp	r9, r3
	cmpeq	r8, r2
	beq	.L967
	mov	r2, r8
	mov	r3, r9
	strd	r2, [r0, #-8]
.L904:
	add	ip, r1, #608
	mvn	r2, #0
	mvn	r3, #0
	strd	r2, [r0]
	ldrd	r2, [ip]
	add	r0, r1, #624
	strd	r2, [ip, #-8]
	ldrd	r2, [r0]
	orrs	ip, r2, r3
	strd	r2, [r0, #-8]
	ldreq	r3, [fp, #-56]
	ldreqd	r2, [r3, #48]
	streqd	r2, [r0, #-8]
.L906:
	ldr	ip, [r1, #644]
	mov	r3, r9
	ldr	lr, [r1, #648]
	mov	r2, r8
	mov	r0, #29
	str	ip, [r1, #632]
	str	lr, [r1, #636]
	ldr	ip, [r1, #660]
	ldr	lr, [r1, #652]
	str	ip, [r1, #656]
	str	lr, [r1, #640]
	ldr	ip, [r7, #68]
	ldr	r1, .L970+40
	blx	ip
	ldr	ip, [r6, r4, asl #2]
	ldr	r3, [ip, #48]
	cmp	r3, #3
	beq	.L968
.L907:
	ldr	r3, [fp, #-56]
	mvn	r1, #0
	mvn	r0, #0
	ldrd	r2, [r3, #24]
	cmp	r3, r1
	cmpeq	r2, r0
	addne	r1, ip, #592
	strned	r2, [r1]
.L909:
	ldr	lr, [fp, #-56]
	add	r1, ip, #608
	add	r0, ip, #624
	ldrd	r2, [lr, #40]
	strd	r2, [r1]
	ldrd	r2, [lr, #48]
	strd	r2, [r0]
	ldr	r2, [fp, #-52]
	ldr	r3, [r2, #728]
	str	r3, [ip, #644]
	ldr	r3, [r2, #732]
	str	r3, [ip, #648]
	ldr	r3, [r2, #736]
	str	r3, [ip, #652]
	ldr	r3, [r2, #740]
	str	r3, [ip, #660]
.L908:
	ldrd	r2, [r1, #-8]
	mov	r0, #29
	ldr	r1, .L970+44
	ldr	ip, [r7, #68]
	blx	ip
	b	.L910
.L953:
	ldr	r3, [fp, #-52]
	mov	r0, r4
	add	r3, r3, #672
	str	r3, [fp, #-56]
	mov	r1, r3
	bl	SM_ReadStreamSeg
	cmp	r0, #0
	beq	.L898
	cmp	r10, #1
	beq	.L969
.L899:
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #1
	mvn	r5, #3
	str	r2, [r3, #316]
	b	.L932
.L957:
	ldr	ip, .L970+4
	movw	r2, #6764
	ldr	r3, .L970+48
.L954:
	ldr	r1, .L970+52
	mov	r0, #0
	ldr	r4, [ip, #68]
	mvn	r5, #0
	blx	r4
	b	.L932
.L958:
	ldr	ip, .L970+4
	movw	r2, #6765
	ldr	r3, .L970+56
	b	.L954
.L964:
	ldr	r3, [r0, #1460]
	cmp	r3, #1
	beq	.L914
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	IsMain10Profile
	cmp	r0, #0
	ldreq	r3, [r9, r4, asl #2]
	streq	r0, [r3, #1460]
	beq	.L914
	mov	r3, r4
	ldr	r10, [r7, #68]
	ldr	r2, .L970+28
	mov	r0, #0
	ldr	r1, .L970+60
	blx	r10
	ldr	r3, [r9, r4, asl #2]
	mov	r2, #1
	str	r2, [r3, #1460]
	bl	VDMDRV_AddMatchMode
	b	.L914
.L965:
	add	r3, r3, #225280
	ldr	r3, [r3, #2860]
	bics	r1, r3, #2
	beq	.L895
	cmp	r3, #1
	bne	.L918
	ldr	r3, [r7, #68]
	mov	r0, #31
	ldr	r1, .L970+64
	mvn	r5, #2
	blx	r3
	b	.L932
.L968:
	ldr	r8, [fp, #-56]
	add	lr, ip, #592
	add	r0, ip, #608
	add	r1, ip, #624
	ldrd	r2, [r8, #24]
	strd	r2, [lr]
	ldrd	r2, [r8, #40]
	strd	r2, [r0]
	ldrd	r2, [r8, #48]
	strd	r2, [r1]
	ldr	r2, [fp, #-52]
	ldr	r3, [r2, #728]
	str	r3, [ip, #644]
	ldr	r3, [r2, #732]
	str	r3, [ip, #648]
	ldr	r3, [r2, #736]
	str	r3, [ip, #652]
	ldr	r3, [r2, #740]
	str	r3, [ip, #660]
.L902:
	ldr	ip, [r6, r4, asl #2]
	ldr	r3, [ip, #48]
	cmp	r3, #3
	addeq	r1, ip, #608
	bne	.L907
	b	.L908
.L962:
	ldrd	r0, [r3, #-8]
	b	.L912
.L955:
	ldr	ip, .L970+4
	movw	r2, #6762
	ldr	r3, .L970+68
	b	.L954
.L963:
	mov	r2, r4, asl #24
	movw	r1, #6974
	add	r2, r2, #196608
	ldr	r0, .L970+28
	bl	DBG_AddTrace
	b	.L913
.L966:
	ldrd	r2, [r0]
	mov	r8, r2
	mov	r9, r3
	strd	r2, [r0, #-8]
	b	.L904
.L967:
	ldrd	r2, [r0, #-8]
	mov	r8, r2
	mov	r9, r3
	b	.L904
.L956:
	ldr	ip, .L970+4
	movw	r2, #6763
	ldr	r3, .L970+72
	mvn	r5, #0
	ldr	r1, .L970+52
	ldr	r4, [ip, #68]
	blx	r4
	b	.L932
.L969:
	ldr	r3, [r7, #68]
	mov	r2, r4
	ldr	r1, .L970+76
	mov	r0, #23
	blx	r3
	b	.L899
.L971:
	.align	2
.L970:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_TraceBsPeriod
	.word	.LC91
	.word	.LC94
	.word	.LC97
	.word	g_TraceFramePeriod
	.word	.LANCHOR1+196
	.word	.LC100
	.word	.LC92
	.word	.LC95
	.word	.LC96
	.word	.LC52
	.word	.LC1
	.word	.LC90
	.word	.LC98
	.word	.LC99
	.word	.LC6
	.word	.LC38
	.word	.LC93
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
	ldr	r0, .L1001
	ldr	r1, .L1001+4
	sub	r3, r0, #64
.L975:
	ldr	r2, [r1, #4]!
	add	r3, r3, #4
	cmp	r2, #0
	ldrne	r2, [r2, #24]
	str	r2, [r3, #-4]
	cmp	r3, r0
	bne	.L975
	ldr	r6, .L1001+8
	mvn	r5, #0
	ldr	r9, .L1001+12
	mov	r7, #0
	mov	r8, r6
.L976:
	mov	r3, #0
	ldr	r0, [r6, #3796]
	mov	r4, r3
	ldr	r1, .L1001+16
	b	.L977
.L979:
	ldr	r2, [r1, #4]!
	cmp	r0, r2
	movlt	r0, r2
	movlt	r4, r3
.L977:
	add	r3, r3, #1
	cmp	r3, #16
	bne	.L979
	add	r3, r6, r4, lsl #2
	cmp	r0, #0
	add	r2, r4, #1
	ldr	r1, .L1001+8
	str	r7, [r3, #3796]
	mov	r3, #0
	str	r2, [r6, #84]
	ble	.L980
	ldr	r3, [r8, r4, asl #2]
	cmp	r3, #0
	beq	.L976
	ldr	r2, [r3, #16]
	cmp	r2, #1
	bne	.L976
	ldr	r2, [r3, #68]
	cmp	r2, #0
	ble	.L982
	ldr	r5, [r3, #72]
	cmp	r5, #0
	beq	.L999
.L982:
	mov	r10, #200
	b	.L987
.L985:
	cmp	r0, #0
	bne	.L976
	subs	r10, r10, #1
	beq	.L976
.L987:
	mov	r0, r4
	bl	DecChanSyntax
	cmn	r0, #1
	mov	r5, r0
	bne	.L985
	ldr	r6, [r6, #3600]
	cmp	r6, #0
	beq	.L993
	mov	r3, #0
	mov	r0, r4
	mov	r2, r3
	mov	r1, #102
	blx	r6
.L993:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L999:
	mov	r0, r4
	sub	r1, fp, #68
	bl	SM_GetInfo
	cmp	r0, #0
	bne	.L1000
.L983:
	ldr	r5, [r6, r4, asl #2]
	ldr	r1, [fp, #-56]
	ldr	r2, [r5, #68]
	ldr	r0, [r5, #544]
	bl	GetNextDecodeMode
	ldr	r3, [r6, r4, asl #2]
	str	r0, [r5, #544]
	ldr	r2, [r3, #544]
	cmp	r2, #0
	strne	r7, [r3, #540]
	strne	r7, [r3, #536]
	ldreq	r2, [r3, #64]
	streq	r2, [r3, #540]
	streq	r2, [r3, #536]
	b	.L982
.L980:
	mov	r0, r5
	str	r3, [r1, #84]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1000:
	mov	r1, r5
	sub	r0, fp, #68
	ldr	r3, [r9, #48]
	mov	r2, #24
	blx	r3
	b	.L983
.L1002:
	.align	2
.L1001:
	.word	.LANCHOR0+3860
	.word	.LANCHOR0-4
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+3796
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
	ldr	r5, .L1018
	mov	r3, #100
	ldr	r6, .L1018+4
	ldr	r0, [r5, #3860]
	str	r3, [r5, #80]
	cmp	r0, #0
	ble	.L1004
	ldr	r3, [r6, #124]
	blx	r3
.L1004:
	ldr	r3, [r6, #12]
	mov	r0, #0
	blx	r3
	bl	SM_Wakeup
	ldr	r3, [r5, #3864]
	mov	r2, #101
	str	r2, [r5, #80]
	cmp	r3, #0
	movne	r7, #0
	beq	.L1016
.L1005:
	mov	r3, #102
	str	r3, [r5, #80]
	bl	VDMDRV_WakeUpVdm
	mov	r0, #0
	bl	SCDDRV_EnableInt
	ldr	r3, .L1018+8
	ldr	r3, [r3, #76]
	cmp	r3, #0
	beq	.L1017
	mov	r0, #0
	blx	r3
.L1007:
	mov	r4, #0
.L1008:
	mov	r0, r4
	mov	r1, #0
	add	r4, r4, #1
	bl	DeleteRawPacketInBuffer
	cmp	r4, #16
	bne	.L1008
	ldr	r3, [r6, #16]
	mov	r0, #0
	blx	r3
	mov	r2, #105
	ldr	r3, [r6, #136]
	mov	r1, #10
	str	r2, [r5, #80]
	mov	r0, #0
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1016:
	bl	DecSyntax
	mov	r7, r0
	b	.L1005
.L1017:
	mov	r0, r3
	mov	r2, #580
	ldr	r3, [r6, #68]
	ldr	r1, .L1018+12
	blx	r3
	b	.L1007
.L1019:
	.align	2
.L1018:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	.LC8
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, .L1050
	ldr	r5, .L1050+4
	mov	r6, r4
	mov	r7, r5
.L1021:
.L1028:
	mov	r2, #0
	ldr	r3, [r5, #68]
	str	r2, [r4, #80]
	mov	r0, #2
	ldr	r1, .L1050+8
	blx	r3
	ldr	r3, [r4, #72]
	mov	r2, #2
	str	r2, [r4, #68]
	cmp	r3, r2
	beq	.L1026
	cmp	r3, #3
	bne	.L1046
	b	.L1025
.L1048:
	cmp	r3, #3
	beq	.L1025
	ldr	r3, [r6, #68]
	cmp	r3, #0
	beq	.L1025
.L1046:
	mov	r3, #2
	str	r3, [r4, #80]
	bl	VCTRL_RunProcess
	ldr	r3, [r5, #68]
	ldr	r1, .L1050+12
	mov	r0, #22
	blx	r3
	ldr	r3, [r4, #72]
	cmp	r3, #2
	bne	.L1048
.L1026:
	mov	r2, #4
	ldr	r3, [r5, #68]
	str	r2, [r4, #80]
	mov	r0, #2
	ldr	r1, .L1050+16
	mov	r8, #5
	blx	r3
	mov	r3, #1
	str	r3, [r4, #68]
	b	.L1023
.L1049:
	ldr	r3, [r7, #124]
	blx	r3
	ldr	r3, [r6, #68]
	cmp	r3, #0
	beq	.L1025
.L1023:
	ldr	r3, [r5, #68]
	mov	r0, #22
	str	r8, [r4, #80]
	ldr	r1, .L1050+20
	blx	r3
	ldr	r3, [r4, #72]
	mov	r0, #10
	cmp	r3, #1
	beq	.L1028
	cmp	r3, #3
	bne	.L1049
.L1025:
	mov	r2, #6
	ldr	r3, [r5, #68]
	ldr	r1, .L1050+24
	mov	r0, #2
	str	r2, [r4, #80]
	blx	r3
	mov	r0, #0
	str	r0, [r4, #68]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1051:
	.align	2
.L1050:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC101
	.word	.LC104
	.word	.LC102
	.word	.LC105
	.word	.LC103
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
	cmp	r0, #15
	bhi	.L1070
	ldr	r3, .L1071
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L1069
	ldr	r2, [r3, #528]
	cmp	r2, #19
	ldrls	pc, [pc, r2, asl #2]
	b	.L1070
.L1055:
	.word	.L1067
	.word	.L1056
	.word	.L1057
	.word	.L1058
	.word	.L1070
	.word	.L1059
	.word	.L1060
	.word	.L1070
	.word	.L1061
	.word	.L1062
	.word	.L1063
	.word	.L1063
	.word	.L1063
	.word	.L1064
	.word	.L1070
	.word	.L1070
	.word	.L1065
	.word	.L1066
	.word	.L1070
	.word	.L1067
.L1067:
	add	r0, r3, #229376
	add	r0, r0, #128
	ldmfd	sp, {fp, sp, pc}
.L1056:
	movw	r0, #15832
	movt	r0, 4
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1057:
	add	r0, r3, #251904
	add	r0, r0, #200
	ldmfd	sp, {fp, sp, pc}
.L1058:
	movw	r0, #47864
	movt	r0, 4
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1059:
	movw	r0, #1160
	movt	r0, 4
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L1060:
	add	r0, r3, #244736
	add	r0, r0, #968
	ldmfd	sp, {fp, sp, pc}
.L1061:
	add	r0, r3, #274432
	add	r0, r0, #1200
	ldmfd	sp, {fp, sp, pc}
.L1062:
	add	r0, r3, #274432
	add	r0, r0, #1184
	ldmfd	sp, {fp, sp, pc}
.L1063:
	add	r0, r3, #241664
	add	r0, r0, #480
	ldmfd	sp, {fp, sp, pc}
.L1064:
	add	r0, r3, #237568
	add	r0, r0, #96
	ldmfd	sp, {fp, sp, pc}
.L1065:
	add	r0, r3, #229376
	add	r0, r0, #704
	ldmfd	sp, {fp, sp, pc}
.L1066:
	add	r0, r3, #278528
	add	r0, r0, #1968
	ldmfd	sp, {fp, sp, pc}
.L1070:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1069:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1072:
	.align	2
.L1071:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetChanVoQue, .-VCTRL_GetChanVoQue
	.align	2
	.global	VCTRL_GetChanImgNum
	.type	VCTRL_GetChanImgNum, %function
VCTRL_GetChanImgNum:
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
	cmp	r0, #15
	mov	r4, r0
	mov	r6, r1
	mov	r7, r2
	mov	r8, r3
	bhi	.L1082
	ldr	r5, .L1086
	ldr	r3, [r5, r0, asl #2]
	cmp	r3, #0
	beq	.L1083
	bl	VCTRL_GetChanVoQue
	subs	r3, r0, #0
	beq	.L1076
	mov	r2, r8
	mov	r1, r7
	bl	GetQueueImgNum
	ldr	r3, [r5, r4, asl #2]
	ldr	r2, [r3, #528]
	cmp	r2, #0
	beq	.L1084
	cmp	r2, #17
	beq	.L1085
	cmp	r2, #16
	addeq	r3, r3, #11337728
	addeq	r3, r3, #12288
	movne	r3, #2
	ldreq	r3, [r3, #2496]
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1084:
	add	r3, r3, #253952
	ldr	r3, [r3, #2176]
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1076:
	str	r3, [r8]
	str	r3, [r7]
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1082:
	ldr	ip, .L1086+4
	movw	r2, #7147
	ldr	r3, .L1086+8
	mov	r0, #0
.L1081:
	ldr	r1, .L1086+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L1085:
	add	r3, r3, #229376
	ldr	r3, [r3, #2608]
	str	r3, [r6]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1083:
	mov	r0, r3
	ldr	ip, .L1086+4
	ldr	r3, .L1086+16
	movw	r2, #7148
	b	.L1081
.L1087:
	.align	2
.L1086:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
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
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r0, #15
	mov	r5, r0
	mov	r4, r1
	bhi	.L1101
	cmp	r1, #0
	mov	r7, #0
	str	r7, [fp, #-64]
	str	r7, [fp, #-68]
	str	r7, [fp, #-72]
	beq	.L1088
	ldr	r8, .L1102
	mov	r1, r7
	ldr	r6, .L1102+4
	mov	r2, #108
	mov	r0, r4
	ldr	r3, [r8, #48]
	blx	r3
	ldr	r1, [r6, r5, asl #2]
	cmp	r1, r7
	beq	.L1088
	add	r1, r1, #1088
	ldr	r3, [r8, #52]
	add	r1, r1, #4
	mov	r2, #108
	mov	r0, r4
	blx	r3
	ldr	r0, [r6, r5, asl #2]
	movw	r3, #1482
	add	lr, r0, #204800
	ldrsb	ip, [lr, r3]
	cmp	ip, r7
	ble	.L1093
	mov	r1, r7
.L1095:
	mov	r2, r1, asl #6
	movw	r3, #27226
	movt	r3, 3
	add	r3, r2, r3
	add	r1, r1, #1
	ldrsb	r3, [r0, r3]
	cmp	r3, #3
	addeq	r7, r7, #1
	cmp	r1, ip
	bne	.L1095
.L1093:
	movw	r3, #1482
	str	r7, [r4, #92]
	ldrsb	ip, [lr, r3]
	sub	r2, fp, #68
	sub	r3, fp, #64
	sub	r1, fp, #72
	mov	r0, r5
	str	ip, [r4, #100]
	bl	VCTRL_GetChanImgNum
	mov	r3, #300
	mla	r3, r3, r5, r6
	ldr	r0, [fp, #-64]
	ldr	r2, [fp, #-68]
	sub	r1, fp, #60
	add	r2, r2, r0
	str	r2, [r4, #56]
	mov	r0, r5
	ldr	r2, [r3, #3888]
	str	r2, [r4, #104]
	ldr	r3, [r3, #3876]
	str	r3, [r4, #24]
	bl	SM_GetInfo
	ldr	r2, [fp, #-44]
	ldr	r3, [fp, #-52]
	sub	r1, fp, #60
	mov	r0, r5
	str	r2, [r4, #60]
	str	r3, [r4, #64]
	bl	SM_GetInfo
	ldr	r2, [fp, #-40]
	ldr	r3, [r6, r5, asl #2]
	cmp	r2, #10
	add	r3, r3, #241664
	movle	r2, #0
	movgt	r2, #1
	str	r2, [r4, #88]
	ldrb	r3, [r3, #3696]	@ zero_extendqisi2
	and	r3, r3, #1
	str	r3, [r4, #96]
.L1088:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1101:
	ldr	ip, .L1102
	movw	r2, #1226
	ldr	r3, .L1102+8
	mov	r0, #0
	ldr	r1, .L1102+12
	ldr	r4, [ip, #68]
	blx	r4
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1103:
	.align	2
.L1102:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC106
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L1108
	ldr	r3, .L1110
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1109
	ldr	r0, [r0, #1272]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1108:
	ldr	ip, .L1110+4
	movw	r2, #7196
	ldr	r3, .L1110+8
	mov	r0, #0
	ldr	r1, .L1110+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1109:
	ldr	ip, .L1110+4
	movw	r2, #7197
	ldr	r3, .L1110+16
	ldr	r1, .L1110+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1111:
	.align	2
.L1110:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L1116
	ldr	r3, .L1118
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1117
	ldr	r0, [r0, #1276]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1116:
	ldr	ip, .L1118+4
	movw	r2, #7204
	ldr	r3, .L1118+8
	mov	r0, #0
	ldr	r1, .L1118+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1117:
	ldr	ip, .L1118+4
	movw	r2, #7205
	ldr	r3, .L1118+16
	ldr	r1, .L1118+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1119:
	.align	2
.L1118:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L1124
	ldr	r3, .L1125
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	ldrne	r0, [r3, #40]
	moveq	r0, #33
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1124:
	ldr	ip, .L1125+4
	movw	r2, #7212
	ldr	r3, .L1125+8
	mov	r0, #0
	ldr	r1, .L1125+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1126:
	.align	2
.L1125:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
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
	ldr	r5, .L1134
	add	r3, r3, #8
	movw	r2, #10000
	cmp	r3, r2
	mov	r4, r1
	str	r0, [r5, #2560]
	bhi	.L1132
.L1128:
	movw	r1, #5000
	cmp	r0, r1
	movw	r2, #60536
	add	r3, r4, #4992
	movge	r0, r1
	movt	r2, 65535
	cmp	r0, r2
	add	r3, r3, #8
	movw	r1, #10000
	str	r4, [r5, #2564]
	movlt	r0, r2
	cmp	r3, r1
	str	r0, [r5, #2560]
	ldr	r6, .L1134
	bhi	.L1133
.L1129:
	movw	r2, #5000
	cmp	r4, r2
	movw	r3, #60536
	movge	r4, r2
	movt	r3, 65535
	cmp	r4, r3
	movlt	r4, r3
	str	r4, [r5, #2564]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1132:
	ldr	r3, .L1134+4
	mov	r2, r0
	ldr	r1, .L1134+8
	mov	r0, #32
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r0, [r5, #2560]
	b	.L1128
.L1133:
	ldr	r3, .L1134+4
	mov	r2, r4
	ldr	r1, .L1134+12
	mov	r0, #32
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r4, [r6, #2564]
	b	.L1129
.L1135:
	.align	2
.L1134:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC107
	.word	.LC108
	UNWIND(.fnend)
	.size	VCTRL_SetVdecExtra, .-VCTRL_SetVdecExtra
	.align	2
	.global	VCTRL_MaskAllInt
	.type	VCTRL_MaskAllInt, %function
VCTRL_MaskAllInt:
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
	ldr	r3, .L1140
	ldr	r3, [r3, #72]
	cmp	r3, #0
	beq	.L1139
	mov	r0, #0
	blx	r3
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_MaskInt
.L1139:
	ldr	ip, .L1140+4
	mov	r0, r3
	movw	r2, #7257
	ldr	r1, .L1140+8
	ldr	r3, [ip, #68]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_MaskInt
.L1141:
	.align	2
.L1140:
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	UNWIND(.fnend)
	.size	VCTRL_MaskAllInt, .-VCTRL_MaskAllInt
	.align	2
	.global	VCTRL_EnableAllInt
	.type	VCTRL_EnableAllInt, %function
VCTRL_EnableAllInt:
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
	ldr	r3, .L1146
	ldr	r3, [r3, #76]
	cmp	r3, #0
	beq	.L1145
	mov	r0, #0
	blx	r3
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_EnableInt
.L1145:
	ldr	ip, .L1146+4
	mov	r0, r3
	mov	r2, #7296
	ldr	r1, .L1146+8
	ldr	r3, [ip, #68]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SCDDRV_EnableInt
.L1147:
	.align	2
.L1146:
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	UNWIND(.fnend)
	.size	VCTRL_EnableAllInt, .-VCTRL_EnableAllInt
	.align	2
	.global	VCTRL_SetLastFrameIdPlus2
	.type	VCTRL_SetLastFrameIdPlus2, %function
VCTRL_SetLastFrameIdPlus2:
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
	cmp	r0, #15
	bhi	.L1154
	ldr	r3, .L1155
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	strne	r1, [r3, #320]
	ldmfd	sp, {fp, sp, pc}
.L1154:
	ldr	ip, .L1155+4
	movw	r2, #8091
	ldr	r3, .L1155+8
	mov	r0, #0
	ldr	r1, .L1155+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L1156:
	.align	2
.L1155:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_SetLastFrameIdPlus2, .-VCTRL_SetLastFrameIdPlus2
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
	cmp	r0, #15
	bhi	.L1163
	ldr	r3, .L1164
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	strne	r1, [r3, #324]
	ldmfd	sp, {fp, sp, pc}
.L1163:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_SetLastFrameState.part.6
.L1165:
	.align	2
.L1164:
	.word	.LANCHOR0
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #15
	mov	r4, r0
	mov	r5, r1
	bhi	.L1179
	ldr	r6, .L1181
	ldr	r0, [r6, r0, asl #2]
	cmp	r0, #0
	beq	.L1180
	cmp	r1, #0
	moveq	r3, #2
	beq	.L1171
	cmp	r1, #1
	moveq	r3, #3
	movne	r3, #4
.L1171:
	ldr	r7, [r6, #3600]
	str	r3, [r0, #324]
	cmp	r7, #0
	beq	.L1173
	sub	r2, fp, #28
	mov	r3, #4
	mov	r1, #115
	mov	r0, r4
	str	r5, [r2, #-4]!
	blx	r7
.L1173:
	ldr	r3, [r6, r4, asl #2]
	mov	r2, r5
	ldr	ip, .L1181+4
	mov	r0, #1
	ldr	r1, .L1181+8
	ldr	r3, [r3, #324]
	ldr	r4, [ip, #68]
	blx	r4
.L1166:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1179:
	ldr	ip, .L1181+4
	movw	r2, #8117
	ldr	r3, .L1181+12
	mov	r0, #0
	ldr	r1, .L1181+16
	ldr	r4, [ip, #68]
	blx	r4
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1180:
	ldr	ip, .L1181+4
	movw	r2, #8118
	ldr	r3, .L1181+20
	ldr	r1, .L1181+16
	ldr	r4, [ip, #68]
	blx	r4
	b	.L1166
.L1182:
	.align	2
.L1181:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC109
	.word	.LC6
	.word	.LC1
	.word	.LC2
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
	cmp	r0, #15
	mov	r5, r0
	bhi	.L1209
	ldr	r3, .L1212
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1210
	add	r0, r0, #229376
	ldr	r3, [r0, #112]
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L1202
.L1189:
	.word	.L1188
	.word	.L1190
	.word	.L1191
	.word	.L1192
	.word	.L1202
	.word	.L1193
	.word	.L1194
	.word	.L1202
	.word	.L1195
	.word	.L1196
	.word	.L1197
	.word	.L1197
	.word	.L1197
	.word	.L1198
	.word	.L1202
	.word	.L1202
	.word	.L1199
	.word	.L1200
.L1202:
	mov	r0, r5
	mov	r1, #1
	bl	VCTRL_ReportLastFrame
	ldr	r3, .L1212+4
	ldr	r1, .L1212+8
	mov	r0, #2
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1200:
	add	r0, r0, #120
	bl	HEVCDEC_GetRemainImg
	mov	r4, r0
.L1187:
	cmn	r4, #1
	beq	.L1202
	cmp	r4, #0
	bne	.L1211
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_ReportLastFrame
	ldr	r3, .L1212+4
	ldr	r1, .L1212+12
	mov	r0, #2
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1188:
	add	r0, r0, #120
	bl	H264DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1190:
	add	r0, r0, #120
	bl	VC1DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1191:
	add	r0, r0, #120
	bl	MPEG4DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1192:
	add	r0, r0, #120
	bl	MPEG2DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1193:
	add	r0, r0, #120
	bl	DIVX3DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1194:
	add	r0, r0, #120
	bl	AVSDEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1195:
	add	r0, r0, #120
	bl	REAL8DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1196:
	add	r0, r0, #120
	bl	REAL9DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1197:
	add	r0, r0, #120
	bl	VP6DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1198:
	add	r0, r0, #120
	bl	VP8DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1199:
	add	r0, r0, #120
	bl	MVC_DEC_GetRemainImg
	mov	r4, r0
	b	.L1187
.L1211:
	mov	r0, r5
	mov	r1, r4
	bl	VCTRL_ReportLastFrame
	ldr	r3, .L1212+4
	sub	r2, r4, #2
	ldr	r1, .L1212+16
	mov	r0, #2
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1209:
	ldr	ip, .L1212+4
	movw	r2, #8146
	ldr	r3, .L1212+20
	mov	r0, #0
	ldr	r1, .L1212+24
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1210:
	ldr	ip, .L1212+4
	movw	r2, #8147
	ldr	r3, .L1212+28
	ldr	r1, .L1212+24
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1213:
	.align	2
.L1212:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC110
	.word	.LC111
	.word	.LC112
	.word	.LC6
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_OutputLastFrame, .-VCTRL_OutputLastFrame
	.align	2
	.global	VCTRL_PostProc
	.type	VCTRL_PostProc, %function
VCTRL_PostProc:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
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
	ldr	r5, .L1248
	mov	r4, r0
	ldr	lr, [fp, #4]
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L1242
	ldr	ip, [r0, #528]
	ldr	r6, [r0, #1232]
	cmp	ip, #17
	ldrls	pc, [pc, ip, asl #2]
	b	.L1214
.L1218:
	.word	.L1217
	.word	.L1219
	.word	.L1220
	.word	.L1221
	.word	.L1214
	.word	.L1222
	.word	.L1223
	.word	.L1214
	.word	.L1224
	.word	.L1225
	.word	.L1226
	.word	.L1226
	.word	.L1226
	.word	.L1227
	.word	.L1214
	.word	.L1214
	.word	.L1228
	.word	.L1229
.L1217:
	add	r0, r0, #229376
	str	lr, [sp, #4]
	add	r0, r0, #120
	str	r6, [sp]
	mov	r2, #1
	ldr	r7, .L1248
	bl	H264DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r3, r3, #241664
	ldrb	r3, [r3, #1392]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1243
.L1230:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #229376
	strne	r2, [r3, #480]
.L1214:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1229:
	add	r0, r0, #229376
	str	lr, [sp, #4]
	add	r0, r0, #120
	str	r6, [sp]
	mov	r2, #1
	ldr	r7, .L1248
	bl	HEVCDEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r3, r3, #229376
	ldrb	r3, [r3, #126]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1244
.L1232:
	cmp	r6, #1
	ldrne	r3, [r5, r4, asl #2]
	movne	r2, #0
	addne	r3, r3, #229376
	strne	r2, [r3, #2432]
	b	.L1214
.L1219:
	add	r0, r0, #229376
	ldr	r6, .L1248
	add	r0, r0, #120
	bl	VC1DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #241664
	ldrb	r2, [r2, #551]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1245
.L1237:
	add	r3, r3, #229376
	mov	r2, #0
	str	r2, [r3, #124]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1220:
	add	r0, r0, #229376
	mov	r2, r3
	add	r0, r0, #120
	bl	MPEG4DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1248
	add	r2, r3, #282624
	ldrb	r2, [r2, #3680]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1246
.L1235:
	add	r3, r3, #229376
	mov	r2, #0
	str	r2, [r3, #1156]
	b	.L1214
.L1221:
	add	r0, r0, #229376
	ldr	r6, .L1248
	add	r0, r0, #120
	bl	MPEG2DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #344064
	ldrb	r2, [r2, #122]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1237
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #344064
	strb	r1, [r2, #122]
	b	.L1237
.L1222:
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	DIVX3DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #229376
	str	r2, [r3, #124]
	b	.L1214
.L1223:
	add	r0, r0, #229376
	ldr	r6, .L1248
	add	r0, r0, #120
	bl	AVSDEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	add	r2, r3, #245760
	ldrb	r2, [r2, #980]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1237
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #245760
	strb	r1, [r2, #980]
	b	.L1237
.L1224:
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	REAL8DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #229376
	str	r2, [r3, #124]
	b	.L1214
.L1225:
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	REAL9DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #229376
	str	r2, [r3, #124]
	b	.L1214
.L1226:
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	VP6DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #229376
	str	r2, [r3, #124]
	b	.L1214
.L1227:
	add	r0, r0, #229376
	add	r0, r0, #120
	bl	VP8DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #229376
	str	r2, [r3, #124]
	b	.L1214
.L1228:
	add	r0, r0, #229376
	mov	r2, #1
	add	r0, r0, #120
	bl	MVC_DEC_VDMPostProc
	ldr	r3, [r5, r4, asl #2]
	ldr	r5, .L1248
	add	r3, r3, #229376
	ldrb	r2, [r3, #121]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1247
.L1238:
	mov	r2, #0
	str	r2, [r3, #348]
	b	.L1214
.L1242:
	ldr	ip, .L1248+4
	movw	r2, #4469
	ldr	r3, .L1248+8
	ldr	r1, .L1248+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	ip
.L1246:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #282624
	strb	r1, [r2, #3680]
	b	.L1235
.L1245:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r6, r4, asl #2]
	mov	r1, #0
	add	r2, r3, #241664
	strb	r1, [r2, #551]
	b	.L1237
.L1247:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r2, [r5, r4, asl #2]
	mov	r1, #0
	add	r2, r2, #229376
	mov	r3, r2
	strb	r1, [r2, #121]
	b	.L1238
.L1243:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #241664
	strb	r2, [r3, #1392]
	b	.L1230
.L1244:
	mov	r0, r4
	bl	VCTRL_OutputLastFrame
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #0
	add	r3, r3, #229376
	strb	r2, [r3, #126]
	b	.L1232
.L1249:
	.align	2
.L1248:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRL_PostProc, .-VCTRL_PostProc
	.align	2
	.global	VCTRL_VdmPostProc
	.type	VCTRL_VdmPostProc, %function
VCTRL_VdmPostProc:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r4, r0
	mov	r5, r1
	mov	r6, r2
	mov	r7, r3
	ldr	r8, [fp, #4]
	bhi	.L1256
	ldr	ip, .L1258
	ldr	ip, [ip, r0, asl #2]
	cmp	ip, #0
	beq	.L1257
	ldr	ip, [ip, #16]
	cmp	ip, #1
	beq	.L1253
	ldr	ip, .L1258+4
	movw	r2, #4649
	ldr	r3, .L1258+8
.L1255:
	mov	r0, #0
	ldr	r1, .L1258+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L1253:
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	str	r8, [fp, #4]
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VCTRL_PostProc
.L1256:
	ldr	ip, .L1258+4
	movw	r2, #4647
	ldr	r3, .L1258+16
	b	.L1255
.L1257:
	ldr	lr, .L1258+4
	mov	r0, ip
	ldr	r3, .L1258+20
	movw	r2, #4648
	ldr	r1, .L1258+12
	ldr	ip, [lr, #68]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L1259:
	.align	2
.L1258:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC52
	.word	.LC1
	.word	.LC51
	.word	.LC38
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
	add	r1, r1, #2
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_ReportLastFrame
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #6
	ldrls	pc, [pc, r1, asl #2]
	b	.L1262
.L1264:
	.word	.L1263
	.word	.L1265
	.word	.L1266
	.word	.L1267
	.word	.L1268
	.word	.L1269
	.word	.L1270
.L1270:
	cmp	r0, #1
	moveq	r0, #1
	movne	r0, #7
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1263:
	cmp	r0, #1
	moveq	r0, #0
	movne	r0, #6
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1265:
	cmp	r0, #1
	moveq	r0, #2
	movne	r0, #8
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1266:
	cmp	r0, #1
	moveq	r0, #4
	movne	r0, #10
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1267:
	cmp	r0, #1
	moveq	r0, #3
	movne	r0, #9
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1268:
	cmp	r0, #1
	moveq	r0, #5
	movne	r0, #11
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1269:
	cmp	r0, #1
	moveq	r0, #13
	movne	r0, #12
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1262:
	ldr	ip, .L1279
	mov	r3, r1
	movw	r2, #8315
	ldr	r1, .L1279+4
	mov	r0, #1
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #13
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1280:
	.align	2
.L1279:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC113
	UNWIND(.fnend)
	.size	Get_YuvFormat, .-Get_YuvFormat
	.align	2
	.global	VDH_PutUsrdecFrame
	.type	VDH_PutUsrdecFrame, %function
VDH_PutUsrdecFrame:
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
	mov	r5, r1
	ldr	r1, [r1, #28]
	mov	r8, r0
	bl	FSP_GetLogicIdByPhyAddr
	cmn	r0, #1
	mov	r7, r0
	beq	.L1289
	ldr	r3, [r5, #4]
	cmp	r3, #1
	beq	.L1284
	mov	r1, r0
	mov	r2, #0
	mov	r0, r8
	bl	FSP_ClearLogicFs
	mov	r0, #0
.L1283:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1284:
	ldr	r0, [r5, #36]
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L1290
.L1285:
	mov	r1, r7
	mov	r0, r8
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L1291
	str	r7, [r4, #196]
	mov	r6, #0
	ldrd	r2, [r5, #8]
	mov	r9, #1
	strd	r2, [r4]
	ldrd	r2, [r5, #8]
	strd	r2, [r4, #8]
	ldrd	r2, [r5, #8]
	strd	r2, [r4, #16]
	ldrd	r2, [r5, #8]
	str	r9, [r4, #68]
	str	r6, [r4, #72]
	strd	r2, [r4, #24]
	str	r6, [r4, #76]
	str	r6, [r4, #80]
	ldr	r3, [r5, #28]
	str	r3, [r4, #88]
	mov	r0, r3
	str	r3, [r4, #120]
	str	r3, [r4, #104]
	ldr	r3, [r5, #36]
	str	r3, [r4, #92]
	str	r3, [r4, #124]
	str	r3, [r4, #108]
	bl	MEM_Phy2Vir
	mov	r3, r0
	ldr	r0, [r4, #92]
	str	r3, [r4, #48]
	str	r3, [r4, #32]
	bl	MEM_Phy2Vir
	ldr	r2, [r4, #88]
	movw	r1, #11296
	str	r0, [r4, #52]
	str	r0, [r4, #36]
	ldr	r3, [r5, #32]
	ldr	r0, [r4, #92]
	add	r2, r3, r2
	str	r2, [r4, #96]
	ldr	r3, [r5, #32]
	str	r6, [r4, #148]
	add	r3, r3, r0
	str	r3, [r4, #100]
	ldr	r3, [r5, #20]
	str	r3, [r4, #164]
	ldr	r3, [r5, #24]
	str	r3, [r4, #168]
	ldr	r3, [r5, #20]
	str	r3, [r4, #172]
	mov	r2, r3, lsr r9
	ldr	r3, [r5, #24]
	str	r2, [r4, #180]
	str	r3, [r4, #176]
	mov	r3, r3, lsr r9
	str	r3, [r4, #184]
	ldr	r3, [r5, #32]
	str	r6, [r4, #188]
	str	r6, [r4, #200]
	str	r3, [r4, #192]
	str	r9, [r4, #228]
	str	r6, [r4, #276]
	str	r6, [r4, #56]
	str	r1, [r4, #160]
	ldr	r1, [r5]
	ldr	r0, [r5, #16]
	bl	Get_YuvFormat
	cmp	r0, #13
	beq	.L1292
	str	r0, [r4, #476]
	mov	r2, r9
	ldr	r3, [r5, #44]
	mov	r9, #19
	mov	r1, r7
	mov	r0, r8
	str	r3, [r4, #452]
	ldr	r3, [r5, #48]
	str	r3, [r4, #448]
	ldr	r3, [r5, #40]
	str	r9, [r4, #384]
	str	r3, [r4, #456]
	bl	FSP_SetDisplay
	ldr	r3, .L1293
	str	r4, [sp]
	mov	r1, r9
	mov	r0, r8
	ldr	r2, [r3, r8, asl #2]
	add	r2, r2, #229376
	add	r3, r2, #128
	add	r2, r2, #120
	bl	InsertImgToVoQueue
	cmp	r0, #1
	moveq	r0, r6
	beq	.L1283
	ldr	r1, [r4, #212]
	mov	r0, r8
	bl	FreeUsdByDec
	ldr	r1, [r4, #216]
	mov	r0, r8
	str	r6, [r4, #212]
	bl	FreeUsdByDec
	mov	r0, r8
	str	r6, [r4, #216]
	mov	r2, r6
	mov	r1, r7
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L1283
.L1290:
	ldr	r3, [r5, #4]
	cmp	r3, #1
	bne	.L1285
	ldr	r3, .L1293+4
	ldr	r2, [r5, #36]
	ldr	r1, .L1293+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1283
.L1289:
	ldr	r3, .L1293+4
	mov	r0, #0
	ldr	r2, [r5, #28]
	ldr	r1, .L1293+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r7
	b	.L1283
.L1292:
	ldr	r3, .L1293+4
	mov	r2, r0
	ldr	r1, .L1293+16
	mov	r0, r9
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1283
.L1291:
	ldr	r3, .L1293+4
	movw	r2, #5090
	ldr	r1, .L1293+20
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1283
.L1294:
	.align	2
.L1293:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC115
	.word	.LC114
	.word	.LC117
	.word	.LC116
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r4, r0
	mov	r5, r1
	bhi	.L1304
	ldr	r3, .L1308
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1305
	cmp	r1, #0
	beq	.L1306
	ldr	r2, [r0, #528]
	cmp	r2, #19
	bne	.L1307
	ldr	r6, .L1308+4
	mov	r2, #56
	add	r0, r0, #472
	ldr	r3, [r6, #52]
	blx	r3
	mov	r1, r5
	mov	r0, r4
	bl	VDH_PutUsrdecFrame
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L1308+8
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1307:
	ldr	r3, .L1308+4
	mov	r0, #1
	ldr	r1, .L1308+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1304:
	ldr	ip, .L1308+4
	movw	r2, #5358
	ldr	r3, .L1308+16
	mov	r0, #0
	ldr	r1, .L1308+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1306:
	ldr	ip, .L1308+4
	mov	r0, r1
	ldr	r3, .L1308+24
	movw	r2, #5360
	ldr	r1, .L1308+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1305:
	ldr	ip, .L1308+4
	movw	r2, #5359
	ldr	r3, .L1308+28
	ldr	r1, .L1308+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1309:
	.align	2
.L1308:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC120
	.word	.LC119
	.word	.LC6
	.word	.LC1
	.word	.LC118
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_PutUsrdecFrame, .-VCTRL_PutUsrdecFrame
	.align	2
	.global	VCTRL_OpenHardware
	.type	VCTRL_OpenHardware, %function
VCTRL_OpenHardware:
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
	UNWIND(.pad #4)
	sub	sp, sp, #4
	ldr	r9, .L1353
	mov	r7, r0
	ldr	r6, [r9]
	cmp	r6, #0
	beq	.L1348
	cmp	r0, #15
	bhi	.L1349
	ldr	r8, .L1353+4
	ldr	r5, [r8, r0, asl #2]
	cmp	r5, #0
	beq	.L1350
	ldr	r3, [r5, #12]
	cmp	r3, #1
	bne	.L1314
	ldr	r3, [r5, #528]
	cmp	r3, #20
	beq	.L1314
	bic	r4, r3, #8
	cmp	r3, #4
	cmpne	r4, #7
	moveq	r4, #1
	movne	r4, #0
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	cmp	r3, #19
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r10, r4
.L1320:
	mov	r0, r4
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L1319
	ldr	r3, [r8, r4, asl #2]
	ldr	r3, [r3, #528]
	cmp	r3, #19
	cmpne	r3, #4
	bic	r3, r3, #8
	movne	r2, #1
	moveq	r2, #0
	cmp	r3, #7
	moveq	r3, #0
	andne	r3, r2, #1
	cmp	r3, #0
	addne	r10, r10, #1
.L1319:
	add	r4, r4, #1
	cmp	r4, #16
	bne	.L1320
	cmp	r10, #1
	beq	.L1351
.L1321:
	ldr	r1, .L1353+8
	mov	ip, #0
	add	lr, r1, #64
.L1326:
	ldr	r2, [r1, #4]!
	mov	r3, #0
	cmp	r2, r3
	beq	.L1324
	ldr	r0, [r2, #528]
	cmp	r0, r3
	ldreq	r2, [r2, #1236]
	subeq	r3, r2, #1
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	cmp	r0, #6
	orreq	r3, r3, #1
	cmp	r3, #0
	movne	ip, #1
.L1324:
	cmp	r1, lr
	bne	.L1326
	ldr	r3, [r6, #120]
	cmp	ip, #1
	orreq	r3, r3, #2
	bfcne	r3, #1, #1
	str	r3, [r6, #120]
	ldr	r3, [r5, #528]
	cmp	r3, #1
	ldmneib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, .L1353+12
	ldr	r3, [r3, #24]
	cmp	r3, #0
	ldmeqib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L1314:
	ldr	r3, .L1353+16
	movw	r2, #8355
	ldr	r1, .L1353+20
.L1347:
	mov	r0, #0
.L1346:
	ldr	r3, [r3, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L1349:
	ldr	r3, .L1353+16
	movw	r2, #8343
	ldr	r1, .L1353+24
	b	.L1347
.L1348:
	ldr	r3, .L1353+16
	mov	r0, r6
	movw	r2, #8337
	ldr	r1, .L1353+28
	b	.L1346
.L1351:
	ldr	r3, .L1353+12
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L1352
	mov	r0, #0
	blx	r3
.L1323:
	ldr	r6, [r9]
	mov	r2, #25
	ldr	r5, [r8, r7, asl #2]
	ldr	r3, [r6, #120]
	bfi	r3, r2, #12, #5
	bfc	r3, #17, #1
	str	r3, [r6, #120]
	ldr	r3, [r6, #120]
	orr	r3, r3, #131072
	str	r3, [r6, #120]
	b	.L1321
.L1350:
	ldr	r3, .L1353+16
	mov	r0, r5
	movw	r2, #8349
	ldr	r1, .L1353+32
	b	.L1346
.L1352:
	ldr	ip, .L1353+16
	mov	r0, r3
	movw	r2, #8391
	ldr	r1, .L1353+36
	ldr	r3, [ip, #68]
	blx	r3
	b	.L1323
.L1354:
	.align	2
.L1353:
	.word	g_pstRegCrg
	.word	.LANCHOR0
	.word	.LANCHOR0-4
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC124
	.word	.LC122
	.word	.LC121
	.word	.LC123
	.word	.LC8
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r5, r0
	bhi	.L1367
	ldr	r4, .L1371
	ldr	r3, [r4, r0, asl #2]
	cmp	r3, #0
	beq	.L1368
	ldr	r6, [r3, #12]
	cmp	r6, #1
	bne	.L1369
	ldr	r3, [r3, #528]
	cmp	r3, #20
	beq	.L1370
	bl	SM_Start
	ldr	r3, [r4, r5, asl #2]
	mov	r2, #0
	str	r6, [r3, #16]
	ldr	r3, [r4, r5, asl #2]
	str	r2, [r3, #28]
	ldr	r3, [r4, r5, asl #2]
	str	r6, [r3, #20]
	ldr	r2, [r4, r5, asl #2]
	ldr	r3, [r2, #24]
	cmp	r3, #0
	bne	.L1361
	ldr	r3, .L1371+4
	sub	r0, r4, #4
	ldr	r1, .L1371+8
	add	lr, r3, #64
	str	r6, [r2, #24]
.L1364:
	ldr	r2, [r0, #4]!
	add	r3, r3, #4
	add	r1, r1, #4
	cmp	r2, #0
	streq	r2, [r3, #-4]
	ldrne	ip, [r2, #24]
	strne	ip, [r3, #-4]
	ldrne	r2, [r2, #24]
	cmp	r3, lr
	str	r2, [r1, #-4]
	bne	.L1364
	ldr	r0, .L1371+4
	bl	VDMDRV_SetPriority
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
.L1361:
	mov	r0, r5
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r5
	bl	VCTRL_OpenHardware
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1369:
	ldr	ip, .L1371+12
	movw	r2, #2552
	ldr	r3, .L1371+16
.L1366:
	ldr	r1, .L1371+20
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1367:
	ldr	ip, .L1371+12
	movw	r2, #2550
	ldr	r3, .L1371+24
	b	.L1366
.L1370:
	ldr	ip, .L1371+12
	movw	r2, #2553
	ldr	r3, .L1371+28
	b	.L1366
.L1368:
	ldr	ip, .L1371+12
	mov	r0, r3
	movw	r2, #2551
	ldr	r3, .L1371+32
	ldr	r1, .L1371+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1372:
	.align	2
.L1371:
	.word	.LANCHOR0
	.word	.LANCHOR3+484
	.word	g_ChanCtx
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC54
	.word	.LC1
	.word	.LC6
	.word	.LC125
	.word	.LC18
	UNWIND(.fnend)
	.size	VCTRL_StartChan, .-VCTRL_StartChan
	.align	2
	.global	VCTRL_CloseHardware
	.type	VCTRL_CloseHardware, %function
VCTRL_CloseHardware:
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
	ldr	r1, .L1411
	mov	r5, #0
	mov	r4, r5
	mov	r0, r5
	add	lr, r1, #64
	b	.L1379
.L1405:
	ldr	ip, [r3, #12]
	cmp	ip, #1
	beq	.L1403
.L1376:
	cmp	r2, #0
	ldreq	ip, [r3, #1236]
	movne	ip, #0
	cmp	r5, #0
	bne	.L1374
	cmp	r2, #6
	cmpne	ip, #1
	bne	.L1374
	ldr	r2, [r3, #12]
	cmp	r2, #1
	ldreq	r5, [r3, #16]
	subeq	r5, r5, #1
	clzeq	r5, r5
	moveq	r5, r5, lsr #5
.L1374:
	cmp	r1, lr
	beq	.L1404
.L1379:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L1374
	cmp	r0, #0
	ldr	r2, [r3, #528]
	beq	.L1405
	cmp	r4, #0
	cmpeq	r2, #1
	bne	.L1376
	ldr	ip, [r3, #12]
	cmp	ip, #1
	bne	.L1376
	ldr	ip, [r3, #16]
.L1386:
	cmp	ip, #1
	moveq	r4, #1
	b	.L1376
.L1403:
	ldr	ip, [r3, #16]
	cmp	ip, #1
	beq	.L1406
.L1377:
	cmp	r4, #0
	cmpeq	r2, #1
	beq	.L1386
	b	.L1376
.L1404:
	cmp	r0, #0
	beq	.L1407
.L1380:
	cmp	r5, #0
	bne	.L1383
	ldr	r3, .L1411+4
	ldr	r3, [r3, #12]
	cmp	r3, #0
	beq	.L1408
	mov	r0, r5
	blx	r3
.L1383:
	cmp	r4, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L1411+4
	ldr	r3, [r3, #28]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L1407:
	ldr	r3, .L1411+4
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1409
	blx	r3
.L1382:
	ldr	r1, .L1411+8
	mov	r3, #0
	ldr	r2, .L1411+12
	str	r3, [r1]
	str	r3, [r2, #84]
	b	.L1380
.L1406:
	sub	r0, r2, #5
	cmp	r0, #1
	cmphi	r2, #3
	bhi	.L1410
.L1388:
	mov	r0, ip
	b	.L1377
.L1410:
	sub	r0, r2, #8
	cmp	r0, #5
	bls	.L1388
	sub	r0, r2, #16
	cmp	r0, #1
	movhi	r0, #0
	movls	r0, #1
	b	.L1377
.L1409:
	ldr	r3, .L1411+16
	movw	r2, #8516
	ldr	r1, .L1411+20
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1382
.L1408:
	ldr	r3, .L1411+16
	mov	r0, r5
	movw	r2, #8532
	ldr	r1, .L1411+20
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1383
.L1412:
	.align	2
.L1411:
	.word	.LANCHOR0-4
	.word	g_vdm_hal_fun_ptr
	.word	g_VdmDrvParam
	.word	g_ScdDrvParam
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r4, r0
	bhi	.L1419
	ldr	r6, .L1421
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1420
	ldr	r2, [r3, #12]
	cmp	r2, #1
	bne	.L1418
	str	r2, [r3, #28]
	mov	r2, #0
	ldr	r3, [r6, r0, asl #2]
	str	r2, [r3, #16]
	bl	SM_Stop
	subs	r5, r0, #0
	bne	.L1418
	mov	r1, r5
	mov	r0, r4
	bl	DeleteRawPacketInBuffer
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	ldr	r3, [r6, r4, asl #2]
	str	r5, [r3, #28]
	bl	VCTRL_CloseHardware
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1418:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1419:
	ldr	ip, .L1421+4
	movw	r2, #2657
	ldr	r3, .L1421+8
	mov	r0, #0
	ldr	r1, .L1421+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1420:
	ldr	ip, .L1421+4
	mov	r0, r3
	movw	r2, #2658
	ldr	r3, .L1421+16
	ldr	r1, .L1421+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1422:
	.align	2
.L1421:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC126
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
	ldr	r5, .L1430
	mov	r7, r0
	mov	r4, #0
	mov	r8, r5
	b	.L1425
.L1429:
	add	r4, r4, #1
	ldr	r3, [r8, #124]
	blx	r3
	cmp	r4, #50
	beq	.L1427
.L1425:
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	mov	r0, r7
	bl	VCTRL_StopChan
	mov	r6, r0
	bl	VCTRL_EnableAllInt
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	cmp	r6, #0
	mov	r0, #10
	bne	.L1429
	cmp	r4, #49
	bgt	.L1427
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1427:
	ldr	r3, [r5, #68]
	mvn	r6, #0
	ldr	r1, .L1430+4
	mov	r0, #0
	blx	r3
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1431:
	.align	2
.L1430:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC127
	UNWIND(.fnend)
	.size	VCTRL_StopChanWithCheck, .-VCTRL_StopChanWithCheck
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	cmp	r0, #15
	mov	r4, r0
	bhi	.L1453
	ldr	r6, .L1456
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1454
	ldr	r7, .L1456+4
	mov	r5, #0
	ldr	r8, [r3, #16]
	bl	VCTRL_StopChan
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #300
	ldr	r0, .L1456+8
	mov	r1, r5
	ldr	r9, [r7, #48]
	str	r5, [r3, #328]
	str	r5, [r3, #332]
	mla	r0, r2, r4, r0
	blx	r9
	mov	r1, r5
	mov	r0, r4
	bl	VCTRL_SetSendStreamAgainFlag
	mov	r1, r5
	mov	r2, #896
	ldr	r3, [r7, #48]
	ldr	r0, .L1456+12
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r4
	str	r5, [r3, #1224]
	bl	InitSyntaxCtx
	ldr	r0, [r6, r4, asl #2]
	ldr	r3, [r7, #48]
	mov	r1, r5
	mov	r2, #416
	add	r0, r0, #664
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mvn	r0, #0
	mvn	r1, #0
	add	r2, r3, #229376
	add	ip, r3, #592
	strd	r0, [ip, #-8]
	strd	r0, [ip]
	mov	r0, r4
	str	r5, [r3, #1080]
	str	r5, [r2, #88]
	str	r5, [r2, #80]
	str	r5, [r2, #84]
	ldr	r2, [r3, #1404]
	cmp	r2, #1
	streq	r5, [r3, #1444]
	bl	FSP_SwitchNotify
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r4
	ldr	r3, [r3, #528]
	cmp	r3, #19
	beq	.L1437
	bl	FSP_ResetInstance
.L1438:
	mov	r0, r4
	bl	InitUsdPool
	mov	r0, r4
	bl	SM_Reset
	ldr	r3, .L1456+16
	ldr	r2, [r3, #548]
	cmp	r2, #0
	beq	.L1439
	add	r5, r3, r4, lsl #2
	str	r4, [fp, #-40]
	ldr	r3, [r5, #552]
	cmp	r3, #0
	beq	.L1441
	mov	r0, #512
	sub	r1, fp, #40
	bl	VCTRL_SetDbgOption
	ldr	r3, [r5, #552]
	cmp	r3, #0
	beq	.L1441
	sub	r1, fp, #40
	mov	r0, #512
	bl	VCTRL_SetDbgOption
.L1441:
	ldr	r3, [r7, #68]
	mov	r0, #32
	ldr	r1, .L1456+20
	blx	r3
.L1439:
	cmp	r8, #0
	bne	.L1455
.L1443:
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, #0
.L1434:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1455:
	mov	r0, r4
	bl	VCTRL_StartChan
	b	.L1443
.L1437:
	bl	FSP_EmptyInstance
	b	.L1438
.L1453:
	ldr	ip, .L1456+4
	movw	r2, #3695
	ldr	r3, .L1456+24
	mov	r0, #0
	ldr	r1, .L1456+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1434
.L1454:
	ldr	ip, .L1456+4
	mov	r0, r3
	mov	r2, #3696
	ldr	r3, .L1456+32
	ldr	r1, .L1456+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1434
.L1457:
	.align	2
.L1456:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+3868
	.word	g_stLowdlyInfo
	.word	.LANCHOR3
	.word	.LC128
	.word	.LC6
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_ResetChan, .-VCTRL_ResetChan
	.align	2
	.global	VCTRL_CreateChanWithOption
	.type	VCTRL_CreateChanWithOption, %function
VCTRL_CreateChanWithOption:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 208
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #220)
	sub	sp, sp, #220
	subs	r9, r1, #0
	mov	r4, r0
	mov	r5, r2
	beq	.L1521
	ldr	r6, .L1538
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #204
	ldr	r10, .L1538+4
	ldr	r3, [r6, #48]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #188
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #172
	blx	r3
	ldr	r3, [r6, #48]
	sub	r0, fp, #140
	mov	r2, #96
	mov	r1, #0
	blx	r3
	subs	r3, r4, #25
	str	r9, [r10, #680]
	movne	r3, #1
	cmp	r5, #0
	movne	r3, #0
	cmp	r3, #0
	bne	.L1522
	ldr	r3, [r9, #36]
	cmp	r3, #0
	blt	.L1462
	ldr	r3, [r9, #12]
	cmp	r3, #31
	ble	.L1462
	ldr	r3, [r9, #16]
	cmp	r3, #31
	ble	.L1462
	ldr	r3, [r9, #56]
	cmp	r3, #262144
	blt	.L1462
	ldr	r3, [r9, #44]
	cmp	r3, #1
	beq	.L1523
	cmp	r3, #2
	beq	.L1524
.L1464:
	ldr	r3, [r9, #144]
	movw	ip, #27784
	movt	ip, 8
	movw	lr, #56880
	cmp	r3, #1
	sub	r2, fp, #216
	mov	r1, r9
	mov	r0, r4
	movhi	r3, #0
	strhi	r3, [r9, #144]
	cmp	r4, #26
	mov	r3, r5
	movt	lr, 176
	movne	lr, ip
	str	lr, [fp, #-224]
	bl	VCTRL_GetChanMemSizeWithOption
	subs	r5, r0, #0
	bne	.L1525
	ldr	r3, [r9, #116]
	cmp	r3, #0
	beq	.L1469
	ldr	r3, [r9, #120]
	cmp	r3, #0
	bne	.L1470
.L1469:
	mov	r0, #5
	mov	r5, #1
	bl	VFMW_GetString
	ldr	r2, [fp, #-208]
	str	r5, [sp]
	sub	r3, fp, #156
	mov	r1, #0
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L1526
	ldr	r2, [fp, #-144]
	ldr	r1, [fp, #-152]
	ldr	r0, [fp, #-148]
	str	r5, [fp, #-228]
	bl	MEM_AddMemRecord
	ldr	r1, [fp, #-148]
	ldr	r2, [fp, #-152]
	ldr	r3, [fp, #-144]
	str	r1, [fp, #-172]
	str	r2, [fp, #-168]
	str	r3, [fp, #-164]
.L1472:
	ldr	r3, [r9, #84]
	cmp	r3, #0
	beq	.L1474
	ldr	r3, [r9, #88]
	cmp	r3, #0
	bne	.L1475
.L1474:
	ldr	r3, [r9, #144]
	cmp	r3, #1
	beq	.L1476
	mov	r0, #6
	bl	VFMW_GetString
	mov	r1, #0
	ldr	r2, [fp, #-216]
	sub	r3, fp, #156
	str	r1, [sp]
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L1527
	ldr	r2, [fp, #-144]
	mov	r3, #1
	ldr	r1, [fp, #-152]
	ldr	r0, [fp, #-148]
	str	r3, [fp, #-232]
	bl	MEM_AddMemRecord
	ldr	r1, [fp, #-148]
	ldr	r2, [fp, #-152]
	ldr	r3, [fp, #-144]
	str	r1, [fp, #-204]
	str	r2, [fp, #-200]
	str	r3, [fp, #-196]
.L1479:
	ldr	r3, [r9, #100]
	cmp	r3, #0
	beq	.L1483
	ldr	r3, [r9, #104]
	cmp	r3, #0
	bne	.L1484
.L1483:
	mov	r0, #7
	bl	VFMW_GetString
	mov	r1, #0
	ldr	r2, [fp, #-212]
	sub	r3, fp, #156
	str	r1, [sp]
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	bne	.L1528
	ldr	r2, [fp, #-144]
	mov	r3, #1
	ldr	r1, [fp, #-152]
	ldr	r0, [fp, #-148]
	str	r3, [fp, #-236]
	bl	MEM_AddMemRecord
	ldr	r1, [fp, #-148]
	ldr	r2, [fp, #-152]
	ldr	r3, [fp, #-144]
	str	r1, [fp, #-188]
	str	r2, [fp, #-184]
	str	r3, [fp, #-180]
.L1488:
	ldr	r7, .L1538+8
	mov	r0, #0
	ldr	r3, [r6, #12]
	blx	r3
	bl	VCTRL_MaskAllInt
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L1502
	mov	r3, r7
	mov	r5, #1
.L1495:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1529
	add	r5, r5, #1
	cmp	r5, #16
	bne	.L1495
	mov	r2, r5
	ldr	r3, [r6, #68]
	ldr	r1, .L1538+12
	mov	r0, #1
	blx	r3
	bl	VCTRL_EnableAllInt
	ldr	r3, [r6, #16]
	mov	r0, #0
	blx	r3
	mvn	r0, #0
.L1517:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1476:
	mov	r3, #0
	str	r3, [fp, #-204]
	str	r3, [fp, #-200]
	str	r3, [fp, #-232]
	str	r3, [fp, #-196]
	b	.L1479
.L1524:
	ldr	r3, [r9, #20]
	cmp	r3, #0
	ble	.L1462
	ldr	r3, [r9, #24]
	cmp	r3, #0
	ble	.L1462
.L1519:
	ldr	r3, [r9, #28]
	cmp	r3, #0
	ble	.L1462
	ldr	r3, [r9, #32]
	cmp	r3, #0
	bgt	.L1464
.L1462:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L1538+16
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1529:
	uxtb	r3, r5
	str	r3, [fp, #-240]
.L1493:
	ldr	r3, [fp, #-224]
	mov	r1, #0
	ldr	r0, [fp, #-168]
	mov	r8, r1
	sub	r2, r3, #207872
	ldr	r3, [r6, #48]
	sub	r2, r2, #8
	str	r0, [r7, r5, asl #2]
	blx	r3
	ldr	r0, [r7, r5, asl #2]
	ldr	r3, [r6, #52]
	mov	r2, #176
	add	r0, r0, #1248
	mov	r1, r9
	add	r0, r0, #12
	blx	r3
	ldr	r1, [r7, r5, asl #2]
	ldr	r0, [fp, #-224]
	mov	ip, r5, asl #4
	mov	lr, r5, asl #6
	str	ip, [fp, #-244]
	str	r4, [r1, #40]
	mov	r2, #20
	ldr	r3, [r7, r5, asl #2]
	str	r0, [r1, #1200]
	rsb	r0, ip, lr
	mov	r1, #30
	str	lr, [fp, #-248]
	str	r5, [r3, #8]
	str	r4, [r3, #564]
	mov	r4, r8
	str	r8, [r3, #1216]
	ldr	r3, [r7, r5, asl #2]
	ldr	ip, [r9]
	str	ip, [r3, #36]
	ldr	r3, [r7, r5, asl #2]
	add	ip, r3, #229376
	str	r2, [r3, #528]
	str	r2, [ip, #112]
	ldr	ip, .L1538+20
	str	r8, [r3, #32]
	ldr	r3, [r7, r5, asl #2]
	add	r0, ip, r0
	ldrb	ip, [fp, #-240]	@ zero_extendqisi2
	add	r2, r3, #204800
	strb	ip, [r2, #1472]
	add	r2, r3, #205824
	str	r1, [r3, #1464]
	add	r3, r3, #1472
	ldr	r1, .L1538+24
	add	r2, r2, #448
	str	r3, [r0, #40]
	mov	r0, r5
	str	r2, [r1, r5, asl #2]
	bl	VCTRL_ResetChan
	ldr	r2, [r7, r5, asl #2]
	ldr	r0, [fp, #-236]
	ldr	r1, [fp, #-232]
	add	r3, r2, #225280
	str	r0, [r2, #252]
	ldr	r0, [fp, #-228]
	str	r1, [r2, #248]
	add	r1, r2, #229376
	str	r0, [r2, #256]
	str	r8, [r3, #2872]
	str	r8, [r3, #2876]
	str	r8, [r3, #2884]
	str	r8, [r3, #2888]
	str	r8, [r3, #2880]
	str	r8, [r3, #2896]
	ldr	r3, [r9, #144]
	str	r8, [r1, #68]
	str	r3, [r1, #72]
.L1497:
	ldr	r0, [r7, r5, asl #2]
	mov	r3, r4, asl #4
	add	r3, r3, r4, lsl #2
	mvn	r1, #0
	add	r2, r0, r3
	add	r3, r3, #227328
	add	r2, r2, #227328
	add	r3, r3, #856
	add	r0, r0, r3
	add	r4, r4, #1
	strb	r1, [r2, #872]
	mov	r2, #16
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	cmp	r4, #32
	ldr	r8, .L1538+8
	ldr	r3, .L1538
	bne	.L1497
	ldr	r0, [r8, r5, asl #2]
	mov	r2, #572
	ldr	r4, [r3, #48]
	mov	r1, #0
	add	r0, r0, #228352
	str	r3, [fp, #-228]
	add	r0, r0, #472
	add	r10, r10, r5, lsl #2
	blx	r4
	ldr	r0, [r8, r5, asl #2]
	ldr	r3, [fp, #-228]
	mov	r2, #24
	add	r0, r0, #229376
	mov	r1, #0
	add	r0, r0, #20
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r8, r5, asl #2]
	ldr	r2, [fp, #-200]
	mov	ip, #0
	ldr	r1, [fp, #-184]
	add	r4, r3, #225280
	ldr	lr, [fp, #-172]
	ldr	r8, [fp, #-168]
	str	r2, [r3, #204]
	ldr	r0, [fp, #-204]
	str	r1, [r3, #220]
	ldr	r2, [fp, #-196]
	str	lr, [r3, #240]
	str	r8, [r3, #236]
	ldr	lr, [fp, #-188]
	ldr	r1, [fp, #-180]
	ldr	r8, [fp, #-164]
	str	r0, [r3, #208]
	str	r0, [r3, #280]
	str	r8, [r3, #244]
	str	r2, [r3, #212]
	str	r2, [r3, #284]
	str	lr, [r3, #224]
	str	r1, [r3, #228]
	str	ip, [r4, #2860]
	ldr	r4, [r3, #1404]
	str	ip, [r10, #684]
	cmp	r4, #1
	beq	.L1498
	ldr	r4, [r3, #272]
	ldr	ip, [r3, #4]
	rsb	r2, r4, r2
	str	r1, [r3, #288]
	rsb	r2, ip, r2
	add	ip, r4, ip
	sub	r2, r2, #47616
	add	ip, ip, r0
	sub	r2, r2, #16
	str	r2, [r3, #264]
	add	r1, r2, ip
	mov	r0, #14848
	add	r2, r1, #14848
	add	r1, r1, #15
	add	r2, r2, #15
	bic	r1, r1, #15
	bic	r2, r2, #15
	str	lr, [r3, #276]
	str	r2, [r3, #300]
	mov	r2, #32768
	str	ip, [r3, #260]
	str	r1, [r3, #292]
	str	r0, [r3, #296]
	str	r2, [r3, #304]
.L1499:
	ldr	r3, [r7, r5, asl #2]
	mov	r0, r5
	ldr	r4, .L1538+8
	str	r5, [r3, #8]
	ldr	r3, [r7, r5, asl #2]
	add	r2, r3, #188416
	str	r5, [r3, #188]
	str	r5, [r3, #192]
	str	r5, [r2, #3816]
	bl	FSP_EnableInstance
	subs	r8, r0, #0
	bne	.L1530
	mov	r0, r5
	mov	r7, #1
	bl	SM_ClearInst
	ldr	r3, [r4, r5, asl #2]
	ldr	r2, [fp, #-224]
	mov	r0, r5
	sub	r1, r2, #205824
	ldr	r3, [r3, #236]
	sub	r1, r1, #8
	add	r1, r3, r1
	bl	OpenUsdPool_WithMem
	ldr	r3, [r4, r5, asl #2]
	mov	r0, r5
	str	r7, [r3, #12]
	bl	VDMDRV_ClearChanIsDec
	bl	VCTRL_EnableAllInt
	bl	VDMDRV_ParamInit
	ldr	r3, [r6, #16]
	mov	r0, r8
	blx	r3
	str	r7, [r9, #48]
	mov	r0, r5
	bl	SM_AllocDSPCtxMem
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1523:
	ldr	r3, [r9, #20]
	cmp	r3, #0
	bgt	.L1519
	b	.L1462
.L1470:
	ldr	r3, [r6, #52]
	mov	r2, #16
	add	r1, r9, #112
	sub	r0, fp, #172
	blx	r3
	ldr	r2, [fp, #-164]
	ldr	r3, [fp, #-208]
	ldr	r1, .L1538
	cmp	r2, r3
	blt	.L1531
	ldr	r1, [fp, #-168]
	ldr	r0, [fp, #-172]
	str	r5, [fp, #-228]
	bl	MEM_AddMemRecord
	b	.L1472
.L1484:
	add	r1, r9, #96
	sub	r0, fp, #188
	ldr	r3, [r6, #52]
	mov	r2, #16
	blx	r3
	ldr	r1, [fp, #-184]
	cmp	r1, #0
	beq	.L1489
	ldr	r2, [fp, #-180]
	ldr	r3, [fp, #-212]
	cmp	r2, r3
	blt	.L1489
	ldr	r0, [fp, #-188]
	mov	r3, #0
	str	r3, [fp, #-236]
	bl	MEM_AddMemRecord
	b	.L1488
.L1475:
	ldr	r3, [r6, #52]
	mov	r2, #16
	sub	r0, fp, #204
	add	r1, r9, #80
	blx	r3
	ldr	r3, [r9, #144]
	ldr	r2, [fp, #-196]
	cmp	r3, #1
	beq	.L1481
	ldr	r3, [fp, #-216]
	cmp	r2, r3
	blt	.L1532
.L1481:
	ldr	r1, [fp, #-200]
	mov	r3, #0
	ldr	r0, [fp, #-204]
	str	r3, [fp, #-232]
	bl	MEM_AddMemRecord
	b	.L1479
.L1498:
	sub	r1, r1, #47616
	str	ip, [r3, #260]
	sub	r1, r1, #16
	str	r1, [r3, #288]
	add	r2, r1, lr
	str	ip, [r3, #264]
	add	r1, r2, #14848
	add	r2, r2, #15
	add	r1, r1, #15
	bic	r2, r2, #15
	bic	r1, r1, #15
	str	r2, [r3, #292]
	str	r1, [r3, #300]
	mov	r2, #32768
	mov	r1, #14848
	str	lr, [r3, #276]
	str	r1, [r3, #296]
	str	r2, [r3, #304]
	b	.L1499
.L1528:
	ldr	r3, [fp, #-228]
	cmp	r3, #1
	beq	.L1533
.L1486:
	ldr	r3, [fp, #-232]
	cmp	r3, #1
	beq	.L1534
.L1487:
	ldr	r3, [r6, #68]
	movw	r2, #2056
	ldr	r1, .L1538+28
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	b	.L1517
.L1489:
	ldr	r3, [fp, #-228]
	cmp	r3, #1
	beq	.L1535
.L1491:
	ldr	r3, [fp, #-232]
	cmp	r3, #1
	beq	.L1536
.L1492:
	ldr	r3, [r6, #68]
	movw	r2, #2084
	ldr	r1, .L1538+32
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	b	.L1517
.L1534:
	ldr	r1, [fp, #-200]
	ldr	r0, [fp, #-204]
	bl	MEM_ReleaseMemBlock
	sub	r0, fp, #204
	ldmia	r0, {r0, r1, r2}
	bl	MEM_DelMemRecord
	b	.L1487
.L1533:
	ldr	r1, [fp, #-168]
	ldr	r0, [fp, #-172]
	bl	MEM_ReleaseMemBlock
	sub	r0, fp, #172
	ldmia	r0, {r0, r1, r2}
	bl	MEM_DelMemRecord
	b	.L1486
.L1502:
	str	r3, [fp, #-240]
	mov	r5, r3
	b	.L1493
.L1527:
	ldr	r3, [fp, #-228]
	cmp	r3, #1
	beq	.L1537
.L1478:
	ldr	r3, [r6, #68]
	movw	r2, #1999
	ldr	r1, .L1538+36
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	b	.L1517
.L1530:
	ldr	r3, [r6, #68]
	mov	r0, #1
	ldr	r1, .L1538+40
	mov	r7, #0
	blx	r3
	mov	r0, r5
	bl	FSP_DisableInstance
	mov	r0, r5
	bl	CloseUsdPool_WithMem
	ldr	r0, [r4, r5, asl #2]
	ldr	r3, [r6, #52]
	mov	r2, #16
	add	ip, r0, #227328
	add	r1, r0, #232
	ldr	lr, [r0, #256]
	add	ip, ip, #856
	str	ip, [fp, #-48]
	ldr	ip, [r0, #248]
	ldr	r0, [r0, #252]
	str	lr, [fp, #-68]
	str	ip, [fp, #-76]
	str	r0, [fp, #-72]
	sub	r0, fp, #108
	blx	r3
	ldr	r1, [r4, r5, asl #2]
	ldr	r3, [r6, #52]
	mov	r2, #16
	add	r1, r1, #200
	sub	r0, fp, #140
	blx	r3
	ldr	r1, [r4, r5, asl #2]
	ldr	r3, [r6, #52]
	mov	r2, #16
	add	r1, r1, #216
	sub	r0, fp, #124
	blx	r3
	ldr	r3, [fp, #-248]
	ldr	r2, [fp, #-244]
	sub	r0, fp, #92
	rsb	r1, r2, r3
	ldr	r3, .L1538+20
	mov	r2, #16
	add	r1, r3, r1
	ldr	r3, [r6, #52]
	blx	r3
	ldr	r1, [r4, r5, asl #2]
	mov	r2, #12
	ldr	r3, [r6, #52]
	add	r1, r1, #152
	sub	r0, fp, #64
	blx	r3
	mov	r0, r5
	str	r7, [r4, r5, asl #2]
	bl	VDMDRV_ClearChanIsDec
	bl	VCTRL_EnableAllInt
	ldr	r3, [r6, #16]
	mov	r0, r7
	blx	r3
	sub	r1, fp, #140
	mov	r0, r5
	bl	VCTRL_FreeChanResource
	mvn	r0, #0
	b	.L1517
.L1526:
	ldr	r3, [r6, #68]
	mov	r0, r5
	movw	r2, #1964
	ldr	r1, .L1538+44
	blx	r3
	mvn	r0, #0
	b	.L1517
.L1522:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L1538+48
	blx	r3
	mvn	r0, #0
	b	.L1517
.L1525:
	ldr	r3, [r6, #68]
	movw	r2, #1956
	ldr	r1, .L1538+52
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	b	.L1517
.L1531:
	ldr	r3, [r1, #68]
	movw	r2, #1980
	ldr	r1, .L1538+56
	mov	r0, #1
	blx	r3
	mvn	r0, #0
	b	.L1517
.L1521:
	ldr	ip, .L1538
	mov	r0, r9
	ldr	r3, .L1538+60
	movw	r2, #1906
	ldr	r1, .L1538+64
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1517
.L1532:
	ldr	r1, [fp, #-228]
	cmp	r1, #1
	bne	.L1482
	ldr	r1, [fp, #-168]
	ldr	r0, [fp, #-172]
	bl	MEM_ReleaseMemBlock
	sub	r0, fp, #172
	ldmia	r0, {r0, r1, r2}
	bl	MEM_DelMemRecord
	ldr	r2, [fp, #-196]
	ldr	r3, [fp, #-216]
.L1482:
	str	r3, [sp]
	mov	r0, #1
	mov	r3, r2
	ldr	r4, [r6, #68]
	movw	r2, #2031
	ldr	r1, .L1538+68
	blx	r4
	mvn	r0, #0
	b	.L1517
.L1537:
	ldr	r1, [fp, #-168]
	ldr	r0, [fp, #-172]
	bl	MEM_ReleaseMemBlock
	sub	r0, fp, #172
	ldmia	r0, {r0, r1, r2}
	bl	MEM_DelMemRecord
	b	.L1478
.L1536:
	ldr	r1, [fp, #-200]
	ldr	r0, [fp, #-204]
	bl	MEM_ReleaseMemBlock
	sub	r0, fp, #204
	ldmia	r0, {r0, r1, r2}
	bl	MEM_DelMemRecord
	b	.L1492
.L1535:
	ldr	r1, [fp, #-168]
	ldr	r0, [fp, #-172]
	bl	MEM_ReleaseMemBlock
	sub	r0, fp, #172
	ldmia	r0, {r0, r1, r2}
	bl	MEM_DelMemRecord
	b	.L1491
.L1539:
	.align	2
.L1538:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	.LANCHOR0
	.word	.LC139
	.word	.LC70
	.word	s_SmIIS
	.word	s_pFspInst
	.word	.LC136
	.word	.LC137
	.word	.LC134
	.word	.LC138
	.word	.LC132
	.word	.LC130
	.word	.LC131
	.word	.LC133
	.word	.LC129
	.word	.LC1
	.word	.LC135
	UNWIND(.fnend)
	.size	VCTRL_CreateChanWithOption, .-VCTRL_CreateChanWithOption
	.align	2
	.global	VCTRL_CreateChan
	.type	VCTRL_CreateChan, %function
VCTRL_CreateChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 232
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #240)
	sub	sp, sp, #240
	cmp	r0, #32
	mov	r4, r0
	mov	r6, r1
	bhi	.L1564
	ldr	r5, .L1567
	mov	r2, #176
	mov	r1, #0
	sub	r0, fp, #204
	mov	r7, #2
	ldr	r3, [r5, #48]
	blx	r3
	ldr	r3, [r5, #48]
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #236
	blx	r3
	ldr	r3, [r5, #48]
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #220
	blx	r3
	ldr	r2, .L1567+4
	mov	r0, r4, asl #2
	mov	r1, r4, asl #5
	rsb	ip, r0, r1
	sub	r3, r4, #18
	add	lr, r2, ip
	str	r7, [fp, #-196]
	ldr	ip, [r2, ip]
	ldr	lr, [lr, #4]
	str	ip, [fp, #-192]
	mov	ip, #136
	str	lr, [fp, #-188]
	mov	lr, #32
	str	ip, [fp, #-184]
	mov	ip, #256
	str	lr, [fp, #-176]
	str	ip, [fp, #-172]
	cmp	r3, #7
	ldrls	pc, [pc, r3, asl #2]
	b	.L1543
.L1545:
	.word	.L1555
	.word	.L1555
	.word	.L1555
	.word	.L1555
	.word	.L1555
	.word	.L1546
	.word	.L1546
	.word	.L1546
.L1555:
	mov	lr, #5
	mov	ip, #3
.L1544:
	rsb	r3, r0, r1
	rsb	r1, r0, r1
	add	r3, r2, r3
	add	r2, r2, r1
	str	ip, [fp, #-144]
	mov	r1, #0
	ldr	r3, [r3, #12]
	ldr	r2, [r2, #24]
	cmp	r3, lr
	str	r1, [fp, #-140]
	rsbgt	r3, ip, r3
	str	r1, [fp, #-136]
	movle	r3, #1
	subgt	r3, r3, #2
	cmp	r4, #24
	str	r3, [fp, #-168]
	str	r2, [fp, #-148]
	mov	r3, #1
	streq	r1, [fp, #-168]
	str	r3, [fp, #-164]
	str	r3, [fp, #-160]
	str	r3, [fp, #-152]
	streq	r3, [fp, #-144]
	beq	.L1550
	cmp	r4, #26
	beq	.L1565
	cmp	r4, #18
	moveq	r3, #4
	streq	r3, [fp, #-168]
	moveq	r3, #2
	streq	r3, [fp, #-144]
.L1550:
	sub	r2, fp, #248
	sub	r1, fp, #260
	mov	r0, r4
	bl	VCTRL_GetChanMemSize
	cmp	r0, #0
	bne	.L1566
	cmp	r6, #0
	beq	.L1556
	ldr	r3, [r6, #8]
	cmp	r3, #0
	beq	.L1553
	ldr	r2, [r6]
	cmp	r2, #0
	beq	.L1554
	ldr	r0, [r6, #4]
	cmp	r0, #0
	beq	.L1554
	ldr	r1, [fp, #-260]
	ldr	ip, [fp, #-248]
	add	r1, r1, ip
	cmp	r3, r1
	blt	.L1554
	ldr	ip, [fp, #-244]
	mov	lr, #3
	sub	r1, fp, #220
	str	r2, [fp, #-220]
	rsb	r3, ip, r3
	add	r2, ip, r2
	str	r0, [fp, #-216]
	add	r0, r0, ip
	str	r2, [fp, #-236]
	mov	r2, #16
	str	r0, [fp, #-232]
	sub	r0, fp, #108
	str	ip, [fp, #-212]
	str	r3, [fp, #-228]
	str	lr, [fp, #-196]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r5, #52]
	sub	r1, fp, #236
	mov	r2, #16
	sub	r0, fp, #124
	blx	r3
	mov	r3, #1
.L1553:
	sub	r1, fp, #204
	mov	r0, r4
	mov	r2, #1
	bl	VCTRL_CreateChanWithOption
	orr	r0, r0, r0, asr #31
.L1542:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1546:
	mov	lr, #3
	mov	ip, #1
	b	.L1544
.L1543:
	mov	lr, #8
	mov	ip, #6
	b	.L1544
.L1565:
	mov	r3, #16
	str	r3, [fp, #-168]
	mov	r3, #6
	str	r3, [fp, #-144]
	b	.L1550
.L1556:
	mov	r3, r6
	b	.L1553
.L1554:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L1567+8
	blx	r3
	ldr	ip, [r6, #8]
	ldmia	r6, {r2, r3}
	mov	r0, #1
	ldr	r1, .L1567+12
	str	ip, [sp]
	ldr	r4, [r5, #68]
	blx	r4
	ldr	r1, [fp, #-260]
	ldr	r2, [fp, #-248]
	mov	r0, #1
	ldr	r3, [r5, #68]
	add	r2, r1, r2
	ldr	r1, .L1567+16
	blx	r3
	mvn	r0, #0
	b	.L1542
.L1564:
	ldr	r3, .L1567
	mov	r2, r0
	ldr	r1, .L1567+20
	mov	r0, #1
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1542
.L1566:
	ldr	r3, [r5, #68]
	mov	r0, #1
	ldr	r1, .L1567+24
	blx	r3
	mvn	r0, #0
	b	.L1542
.L1568:
	.align	2
.L1567:
	.word	vfmw_Osal_Func_Ptr_S
	.word	CapItem
	.word	.LC142
	.word	.LC143
	.word	.LC144
	.word	.LC140
	.word	.LC141
	UNWIND(.fnend)
	.size	VCTRL_CreateChan, .-VCTRL_CreateChan
	.align	2
	.global	VCTRL_ConfigChan
	.type	VCTRL_ConfigChan, %function
VCTRL_ConfigChan:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #72)
	sub	sp, sp, #72
	subs	r8, r1, #0
	mov	r6, #0
	mov	r4, r0
	str	r6, [fp, #-92]
	beq	.L1606
	cmp	r0, #15
	bhi	.L1607
	ldr	r7, .L1616
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L1608
	ldr	r3, [r3, #12]
	cmp	r3, #1
	bne	.L1609
	bl	VCTRL_CheckChanWH
	subs	r5, r0, #0
	bne	.L1610
	ldr	r6, .L1616+4
	add	r0, r6, #748
	bl	GetVdecCapability
	ldr	r3, [r6, #768]
	ldr	r2, [r8]
	cmp	r3, #19
	bhi	.L1577
	cmp	r3, r2
	beq	.L1578
	add	r3, r6, #768
	add	r0, r6, #892
.L1580:
	ldr	r1, [r3, #4]!
	cmp	r1, #19
	bhi	.L1577
	cmp	r1, r2
	beq	.L1578
	cmp	r3, r0
	bne	.L1580
.L1578:
	cmp	r2, #8
	beq	.L1611
.L1581:
	cmp	r2, #9
	beq	.L1612
.L1583:
	cmp	r2, #5
	mov	r3, #0
	str	r3, [fp, #-88]
	beq	.L1613
.L1596:
	mov	r1, r8
	mov	r0, r4
	bl	VCTRL_CmpConfigParameter
	subs	r3, r0, #0
	beq	.L1614
	ldr	r6, .L1616+8
	mov	r2, #104
	ldr	r0, [r7, r4, asl #2]
	mov	r1, r8
	ldr	r3, [r6, #52]
	add	r0, r0, #48
	blx	r3
	ldr	ip, [r8, #12]
	ldr	r3, [r7, r4, asl #2]
	mov	r2, #52
	mov	r1, #0
	sub	r0, fp, #88
	str	ip, [r3, #24]
	ldr	r3, [r7, r4, asl #2]
	ldr	ip, [r8]
	ldr	r9, [r6, #48]
	str	ip, [r3, #528]
	ldr	ip, [r8, #92]
	str	ip, [r3, #1412]
	blx	r9
	ldr	r3, [r7, r4, asl #2]
	add	r9, r8, #4
	ldr	r3, [r3, #276]
	mov	r0, r3
	str	r3, [fp, #-76]
	bl	MEM_Phy2Vir
	ldr	lr, [r7, r4, asl #2]
	ldr	r1, [r8, #80]
	mov	r2, #49152
	movt	r2, 63683
	ldr	r3, [r8]
	cmp	r1, #1
	ldr	ip, [r8, #12]
	str	r0, [fp, #-88]
	ldr	r0, [lr, #288]
	str	r2, [fp, #-68]
	ldreq	r2, [r8, #88]
	str	r0, [fp, #-72]
	ldreq	r0, [r8, #84]
	streq	r1, [fp, #-48]
	mov	r1, r9
	streq	r2, [fp, #-40]
	mov	r2, #8
	streq	r0, [fp, #-44]
	cmp	r3, #0
	str	r3, [fp, #-80]
	ldr	r0, [r8, #76]
	movne	r3, #0
	ldreq	r3, [r8, #48]
	strb	ip, [fp, #-84]
	str	r0, [fp, #-52]
	sub	r0, fp, #64
	str	r3, [fp, #-56]
	ldr	r3, [r6, #52]
	blx	r3
	sub	r1, fp, #88
	mov	r0, r4
	bl	SM_Config
	ldr	r3, [r6, #48]
	sub	r0, fp, #96
	mov	r2, #1
	mov	r1, #0
	blx	r3
	ldr	r3, [r8, #80]
	cmp	r3, #1
	beq	.L1615
.L1589:
	ldr	r3, [r7, r4, asl #2]
	mov	r1, r9
	mov	lr, #0
	mov	r2, #8
	ldr	ip, [r3, #244]
	ldr	r0, [r3, #260]
	ldr	r9, [r3, #240]
	str	ip, [r3, #1208]
	ldr	ip, [r3, #264]
	str	r0, [r3, #556]
	ldr	r0, [r3, #292]
	str	ip, [r3, #560]
	ldr	ip, [r3, #296]
	str	r0, [r3, #568]
	ldr	r0, [r3, #300]
	str	ip, [r3, #572]
	ldr	ip, [r3, #304]
	str	r9, [r3, #1204]
	str	r0, [r3, #576]
	add	r0, r3, #1072
	str	ip, [r3, #580]
	add	r0, r0, #12
	ldr	ip, [r8, #16]
	str	ip, [r3, #540]
	ldr	ip, [r8, #16]
	str	ip, [r3, #536]
	ldr	ip, [r8, #24]
	str	ip, [r3, #544]
	ldr	ip, [r8, #28]
	str	ip, [r3, #548]
	ldr	ip, [r8, #32]
	str	ip, [r3, #552]
	ldr	ip, [r8, #52]
	str	ip, [r3, #1212]
	ldr	ip, [r8, #68]
	sub	ip, ip, #1
	clz	ip, ip
	mov	ip, ip, lsr #5
	str	ip, [r3, #1228]
	ldr	ip, [r8, #72]
	str	ip, [r3, #1232]
	ldr	ip, [r8, #48]
	ldr	r6, [r6, #52]
	str	lr, [r3, #1444]
	str	ip, [r3, #1236]
	str	lr, [r3, #1456]
	blx	r6
	ldr	ip, [r7, r4, asl #2]
	ldr	r6, .L1616
	add	r3, ip, #229376
	ldr	r7, .L1616+8
	ldr	r9, [ip, #528]
	ldr	r2, [r3, #112]
	cmp	r2, r9
	beq	.L1590
	mov	r0, r4
	bl	VCTRL_ResetChan
	ldr	r3, [r8]
	ldr	ip, [r6, r4, asl #2]
	cmp	r3, #19
	beq	.L1591
	ldr	r9, [ip, #528]
	add	r3, ip, #229376
.L1590:
	ldr	r2, .L1616+12
	ldr	r0, .L1616+16
	ldr	r1, .L1616+20
	add	lr, r2, #64
	str	r9, [r3, #112]
.L1595:
	ldr	r3, [r2, #4]!
	add	r0, r0, #4
	add	r1, r1, #4
	cmp	r3, #0
	streq	r3, [r0, #-4]
	ldrne	ip, [r3, #24]
	strne	ip, [r0, #-4]
	ldrne	r3, [r3, #24]
	cmp	r2, lr
	str	r3, [r1, #-4]
	bne	.L1595
	ldr	r0, .L1616+16
	bl	VDMDRV_SetPriority
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1614:
	ldr	r2, .L1616+8
	mov	r5, r3
	ldr	r1, .L1616+24
	ldr	r3, [r2, #68]
	blx	r3
.L1571:
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1577:
	ldr	r3, .L1616+8
	mov	r0, #0
	ldr	r1, .L1616+28
	mvn	r5, #0
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1611:
	sub	r0, fp, #92
	bl	REAL8DEC_Support
	ldr	r3, [fp, #-92]
	cmp	r3, #0
	ldrne	r2, [r8]
	bne	.L1581
.L1584:
	mvn	r5, #0
	b	.L1571
.L1612:
	sub	r0, fp, #92
	bl	REAL9DEC_Support
	ldr	r3, [fp, #-92]
	cmp	r3, #0
	beq	.L1584
	ldr	r2, [r8]
	b	.L1583
.L1613:
	sub	r0, fp, #88
	bl	DIVX3DEC_Support
	ldr	r3, [fp, #-88]
	cmp	r3, #0
	bne	.L1596
	b	.L1584
.L1609:
	ldr	ip, .L1616+8
	mov	r0, r6
	ldr	r3, .L1616+32
	movw	r2, #2870
	ldr	r1, .L1616+36
	mvn	r5, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L1571
.L1615:
	sub	r1, fp, #96
	mov	r0, r4
	strb	r3, [fp, #-96]
	bl	FSP_ConfigAttribute
	b	.L1589
.L1610:
	ldr	r3, .L1616+8
	mov	r0, r6
	ldr	r1, .L1616+40
	mvn	r5, #0
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1571
.L1591:
	ldr	r3, [ip, #280]
	mov	r0, r4
	ldr	r2, [ip, #1276]
	ldr	r1, [ip, #1272]
	ldr	ip, [ip, #284]
	str	ip, [sp]
	bl	VCTRL_PartitionMemForStdUser
	cmp	r0, #0
	bne	.L1592
	ldr	ip, [r6, r4, asl #2]
	add	r3, ip, #229376
	ldr	r9, [ip, #528]
	b	.L1590
.L1607:
	ldr	ip, .L1616+8
	mov	r0, r6
	ldr	r3, .L1616+44
	movw	r2, #2868
	ldr	r1, .L1616+36
	mvn	r5, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L1571
.L1608:
	ldr	ip, .L1616+8
	mov	r0, r3
	movw	r2, #2869
	ldr	r3, .L1616+48
	ldr	r1, .L1616+36
	mvn	r5, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L1571
.L1606:
	ldr	ip, .L1616+8
	mov	r0, r8
	ldr	r3, .L1616+52
	movw	r2, #2867
	ldr	r1, .L1616+36
	mvn	r5, #0
	ldr	r4, [ip, #68]
	blx	r4
	b	.L1571
.L1592:
	ldr	r3, [r7, #68]
	mov	r0, #1
	ldr	r1, .L1616+56
	mvn	r5, #0
	blx	r3
	b	.L1571
.L1617:
	.align	2
.L1616:
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0-4
	.word	.LANCHOR3+896
	.word	g_ChanCtx
	.word	.LC148
	.word	.LC147
	.word	.LC13
	.word	.LC1
	.word	.LC146
	.word	.LC6
	.word	.LC2
	.word	.LC145
	.word	.LC149
	UNWIND(.fnend)
	.size	VCTRL_ConfigChan, .-VCTRL_ConfigChan
	.align	2
	.global	VCTRL_SetDbgOption
	.type	VCTRL_SetDbgOption, %function
VCTRL_SetDbgOption:
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
	cmp	r1, #0
	beq	.L1697
	cmp	r0, #516
	ldr	r4, [r1]
	beq	.L1620
	bls	.L1721
	cmp	r0, #1280
	beq	.L1642
	bhi	.L1643
	movw	r3, #898
	cmp	r0, r3
	beq	.L1644
	bhi	.L1645
	movw	r3, #769
	cmp	r0, r3
	beq	.L1646
	bls	.L1722
	cmp	r0, #896
	beq	.L1649
	movw	r3, #897
	cmp	r0, r3
	bne	.L1697
	mov	r0, r4
	bl	VCTRL_ResetChan
	ldr	r3, .L1734
	ldr	r1, .L1734+4
	mov	r2, r4
.L1716:
	ldr	r4, [r3, #68]
	mov	r3, r0
	mov	r0, #32
	blx	r4
.L1719:
	mov	r0, #1
.L1619:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1643:
	movw	r3, #1537
	cmp	r0, r3
	beq	.L1656
	bhi	.L1657
	movw	r3, #1282
	cmp	r0, r3
	beq	.L1658
	bcc	.L1659
	movw	r3, #1283
	cmp	r0, r3
	beq	.L1660
	cmp	r0, #1536
	bne	.L1697
	cmp	r4, #15
	bhi	.L1715
	ldr	ip, .L1734+8
	mov	r5, #1
	ldr	r3, .L1734
	mov	r2, r4
	ldr	r1, .L1734+12
	mov	r0, #32
	ldr	ip, [ip, r4, asl #2]
	ldr	r3, [r3, #68]
	str	r5, [ip, #1232]
	blx	r3
	mov	r0, r5
	b	.L1619
.L1721:
	cmp	r0, #8
	beq	.L1719
	bls	.L1723
	movw	r3, #257
	cmp	r0, r3
	beq	.L1630
	bhi	.L1631
	cmp	r0, #12
	beq	.L1632
	bls	.L1724
	cmp	r0, #13
	beq	.L1635
	cmp	r0, #256
	bne	.L1697
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+16
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	bl	DBG_PrintTracer
	b	.L1719
.L1645:
	cmp	r0, #1024
	beq	.L1651
	bls	.L1725
	movw	r3, #1025
	cmp	r0, r3
	beq	.L1654
	movw	r3, #1026
	cmp	r0, r3
	bne	.L1697
	ldr	ip, .L1734+8
	mov	r2, r4
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+20
	str	r4, [ip, #3864]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1631:
	movw	r3, #513
	cmp	r0, r3
	beq	.L1637
	bls	.L1726
	movw	r3, #514
	cmp	r0, r3
	beq	.L1640
	movw	r3, #515
	cmp	r0, r3
	bne	.L1697
	ldr	r7, .L1734
	mov	r0, r4
	ldr	r3, [r7, #188]
	blx	r3
	subs	r5, r0, #0
	beq	.L1727
	mov	r0, #16
	ldr	r6, [r7, #72]
	bl	VFMW_GetString
	str	r4, [sp]
	mov	r1, #50
	ldr	r3, .L1734+24
	mov	r2, r0
	sub	r0, fp, #148
	blx	r6
	sub	r0, fp, #148
	ldr	r3, [r7, #32]
	mov	r2, #0
	mov	r1, #66
	blx	r3
	subs	r4, r0, #0
	beq	.L1688
	mov	r2, r4
	ldr	r3, [r7, #44]
	mov	r1, #3145728
	mov	r0, r5
	blx	r3
	mov	r0, r4
	ldr	r3, [r7, #36]
	blx	r3
	ldr	r3, [r7, #68]
	sub	r2, fp, #148
	ldr	r1, .L1734+28
	mov	r0, #32
	blx	r3
	b	.L1719
.L1657:
	movw	r3, #1539
	cmp	r0, r3
	beq	.L1662
	bcc	.L1663
	movw	r3, #1540
	cmp	r0, r3
	beq	.L1664
	movw	r3, #1541
	cmp	r0, r3
	bne	.L1697
	ldr	r3, .L1734
	mov	r2, r4
	ldr	r1, .L1734+32
	mov	r0, #32
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1719
.L1723:
	cmp	r0, #3
	beq	.L1719
	bls	.L1728
	cmp	r0, #5
	beq	.L1627
	bcc	.L1628
	cmp	r0, #6
	beq	.L1719
	cmp	r0, #7
	bne	.L1697
	ldr	r3, .L1734
	mov	r5, r4, lsr #24
	bic	r4, r4, #-16777216
	ldr	r1, .L1734+36
	mov	r2, r5
	mov	r0, #32
	ldr	r6, [r3, #68]
	mov	r3, r4
	blx	r6
	mov	r0, r5
	sub	r1, fp, #148
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L1719
	sub	r1, fp, #148
	mov	r0, r5
	str	r4, [fp, #-128]
	bl	VCTRL_ConfigChan
	b	.L1719
.L1728:
	cmp	r0, #1
	beq	.L1719
	ldrls	r3, .L1734+40
	movls	r0, #1
	strls	r4, [r3]
	bls	.L1619
.L1729:
	ldr	r7, .L1734
	sub	r5, fp, #148
	mov	r6, r4, lsr #24
	bic	r4, r4, #-16777216
	mov	r2, #104
	mov	r1, #0
	ldr	r3, [r7, #48]
	mov	r0, r5
	blx	r3
	mov	r3, r4
	mov	r2, r6
	ldr	r1, .L1734+44
	ldr	r7, [r7, #68]
	mov	r0, #32
	blx	r7
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L1719
	mov	r1, r5
	mov	r0, r6
	str	r4, [fp, #-132]
	bl	VCTRL_ConfigChan
	b	.L1719
.L1660:
	ldr	ip, .L1734+48
	mov	r2, r4
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+52
	str	r4, [ip]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1628:
	ldr	r7, .L1734
	sub	r5, fp, #148
	mov	r6, r4, lsr #24
	and	r4, r4, #3
	mov	r2, #104
	mov	r1, #0
	ldr	r3, [r7, #48]
	mov	r0, r5
	blx	r3
	mov	r3, r4
	mov	r2, r6
	ldr	r1, .L1734+56
	ldr	r7, [r7, #68]
	mov	r0, #32
	blx	r7
	mov	r1, r5
	mov	r0, r6
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L1719
	mov	r1, r5
	mov	r0, r6
	str	r4, [fp, #-120]
	bl	VCTRL_ConfigChan
	b	.L1719
.L1649:
	mov	r0, r4
	bl	VCTRL_StopChan
	ldr	r3, .L1734
	mov	r2, r4
	ldr	r1, .L1734+60
	b	.L1716
.L1640:
	cmp	r4, #15
	bhi	.L1719
	ldr	r6, .L1734+64
	add	r7, r6, r4, lsl #2
	ldr	r5, [r7, #1108]
	cmp	r5, #0
	beq	.L1730
	ldr	r5, .L1734
	mov	r0, #32
	ldr	r1, .L1734+68
	mov	r4, #0
	ldr	r3, [r5, #68]
	blx	r3
	ldr	r3, [r5, #36]
	ldr	r0, [r7, #1108]
	blx	r3
	ldr	r0, [r6, #1248]
	ldr	r3, .L1734+72
	mvn	r2, #0
	cmp	r0, r4
	str	r4, [r7, #1108]
	str	r4, [r6, #1256]
	str	r2, [r3, #68]
	str	r4, [r6, #1260]
	str	r4, [r6, #1264]
	str	r4, [r6, #1268]
	beq	.L1719
	ldr	r1, [r6, #1244]
	bl	MEM_ReleaseMemBlock
	ldr	r2, [r6, #1252]
	ldr	r1, [r6, #1244]
	ldr	r0, [r6, #1248]
	bl	MEM_DelMemRecord
	ldr	r3, [r5, #48]
	mov	r1, r4
	mov	r2, #16
	ldr	r0, .L1734+76
	blx	r3
	mov	r0, #1
	b	.L1619
.L1664:
	mov	r2, r4, asl #6
	ldr	r3, .L1734+80
	sub	r4, r2, r4, asl #4
	mov	r0, #1
	add	r4, r3, r4
	mov	r2, #0
	ldr	r3, [r4, #40]
	str	r2, [r3, #80]
	b	.L1619
.L1635:
	cmp	r4, #16
	ldrhi	r3, .L1734
	movhi	r2, r4
	ldrls	ip, .L1734+64
	movhi	r0, #32
	ldrls	r3, .L1734
	movls	r2, r4
	ldrhi	r1, .L1734+84
	movls	r0, #32
	ldrls	r1, .L1734+88
	strls	r4, [ip, #960]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1654:
	ldr	ip, .L1734+64
	mov	r2, r4
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+92
	str	r4, [ip, #1272]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1697:
	mvn	r0, #1
	b	.L1619
.L1725:
	movw	r3, #899
	cmp	r0, r3
	bne	.L1697
	mov	r0, r4
	ldr	r5, .L1734
	bl	VCTRL_StopChan
	mov	r2, r4
	ldr	r1, .L1734+60
	ldr	r6, [r5, #68]
	mov	r3, r0
	mov	r0, #32
	blx	r6
	mov	r0, r4
	bl	VCTRL_ResetChan
	mov	r2, r4
	ldr	r1, .L1734+4
	ldr	r6, [r5, #68]
	mov	r3, r0
	mov	r0, #32
	blx	r6
	mov	r0, r4
	bl	VCTRL_StartChan
	ldr	r5, [r5, #68]
	mov	r2, r4
	ldr	r1, .L1734+96
	mov	r3, r0
	mov	r0, #32
	blx	r5
	mov	r0, #1
	b	.L1619
.L1724:
	cmp	r0, #11
	bne	.L1697
	cmp	r4, #1
	ldrls	ip, .L1734+100
	movls	r2, r4
	ldrls	r3, .L1734
	movls	r0, #32
	ldrhi	r3, .L1734
	movhi	r2, r4
	strls	r4, [ip]
	movhi	r0, #32
	ldrls	r1, .L1734+104
	ldrhi	r1, .L1734+108
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1722:
	cmp	r0, #768
	bne	.L1697
	bl	VCTRL_Suspend
	mov	r0, #1
	b	.L1619
.L1726:
	cmp	r0, #512
	bne	.L1697
	cmp	r4, #15
	bhi	.L1719
	ldr	r6, .L1734+64
	add	r5, r6, r4, lsl #2
	ldr	r7, [r5, #552]
	cmp	r7, #0
	beq	.L1731
	ldr	r4, .L1734
	mov	r0, #32
	ldr	r1, .L1734+112
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r3, [r4, #36]
	ldr	r0, [r5, #552]
	blx	r3
	mov	r3, #0
	mov	r0, #1
	str	r3, [r5, #552]
	b	.L1619
.L1651:
	ldr	ip, .L1734+8
	mov	r2, r4
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+116
	str	r4, [ip, #3860]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1632:
	cmp	r4, #1
	ldrls	ip, .L1734+64
	movls	r2, r4
	ldrls	r3, .L1734
	movls	r0, #32
	ldrhi	r3, .L1734
	movhi	r2, r4
	ldrls	r1, .L1734+120
	movhi	r0, #32
	strls	r4, [ip, #548]
	ldrhi	r1, .L1734+124
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1646:
	bl	VCTRL_Resume
	mov	r0, #1
	b	.L1619
.L1637:
	cmp	r4, #15
	bhi	.L1719
	ldr	r5, .L1734+64
	mov	r6, r4, asl #2
	add	r3, r5, r6
	ldr	r3, [r3, #972]
	cmp	r3, #0
	beq	.L1732
	ldr	r4, .L1734
	add	r5, r5, r6
	ldr	r1, .L1734+128
	mov	r0, #32
	ldr	r3, [r4, #68]
	blx	r3
	ldr	r3, [r4, #36]
	ldr	r0, [r5, #972]
	blx	r3
	mov	r3, #0
	mov	r0, #1
	str	r3, [r5, #972]
	b	.L1619
.L1627:
	ldr	r6, .L1734
	mov	r5, r4, lsr #24
	and	r4, r4, #7
	ldr	r1, .L1734+132
	mov	r2, r5
	mov	r0, #32
	mov	r3, r4
	ldr	r7, [r6, #68]
	blx	r7
	mov	r0, r5
	sub	r1, fp, #148
	bl	VCTRL_GetChanCfg
	cmp	r0, #0
	bne	.L1668
	sub	r1, fp, #148
	mov	r0, r5
	str	r4, [fp, #-124]
	bl	VCTRL_ConfigChan
	b	.L1719
.L1642:
	ldr	ip, .L1734+136
	mov	r2, r4
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+140
	str	r4, [ip]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1663:
	ldr	ip, .L1734+144
	mov	r2, r4
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+12
	str	r4, [ip]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1662:
	mov	r2, r4, asl #6
	ldr	r3, .L1734+80
	sub	r4, r2, r4, asl #4
	mov	r2, #1
	add	r4, r3, r4
	mov	r0, r2
	ldr	r3, [r4, #40]
	str	r2, [r3, #80]
	b	.L1619
.L1715:
	ldr	r3, .L1734
	mov	r0, #0
	ldr	r1, .L1734+148
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1719
.L1659:
	ldr	ip, .L1734+152
	mov	r2, r4
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+156
	str	r4, [ip]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1658:
	ldr	ip, .L1734+160
	mov	r2, r4
	ldr	r3, .L1734
	mov	r0, #32
	ldr	r1, .L1734+164
	str	r4, [ip]
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1620:
	ldr	r6, .L1734
	mov	r0, r4
	ldmib	r1, {r7, r8}
	ldr	r3, [r6, #188]
	blx	r3
	subs	r9, r0, #0
	beq	.L1733
	mov	r0, #17
	ldr	r10, [r6, #72]
	bl	VFMW_GetString
	sub	r5, fp, #148
	str	r4, [sp]
	mov	r1, #50
	ldr	r3, .L1734+24
	mov	r2, r0
	mov	r0, r5
	blx	r10
	mov	r0, r5
	ldr	r3, [r6, #32]
	mov	r2, #0
	mov	r1, #66
	blx	r3
	subs	r4, r0, #0
	beq	.L1691
	ldr	r3, .L1734+168
	ldr	r10, [r3, #116]
	cmp	r10, #0
	beq	.L1692
	mov	ip, #1
	mov	r3, r8
	mov	r2, r7
	mov	r1, r9
	str	ip, [sp]
	blx	r10
.L1693:
	mov	r0, r4
	ldr	r3, [r6, #36]
	blx	r3
	ldr	r3, [r6, #68]
	mov	r2, r5
	ldr	r1, .L1734+172
	mov	r0, #32
	blx	r3
	b	.L1719
.L1644:
	mov	r0, r4
	bl	VCTRL_StartChan
	ldr	r3, .L1734
	mov	r2, r4
	ldr	r1, .L1734+96
	b	.L1716
.L1630:
	ldr	r5, .L1734+40
	mov	r0, r4
	mov	r1, #1
	mov	r3, #67108864
	ldr	r4, [r5]
	str	r3, [r5]
	bl	PrintScdRawState
	mov	r0, #1
	str	r4, [r5]
	b	.L1619
.L1656:
	cmp	r4, #15
	bhi	.L1715
	ldr	ip, .L1734+8
	mov	lr, #0
	ldr	r3, .L1734
	mov	r2, r4
	ldr	r1, .L1734+12
	mov	r0, #32
	ldr	ip, [ip, r4, asl #2]
	ldr	r3, [r3, #68]
	str	lr, [ip, #1232]
	blx	r3
	mov	r0, #1
	b	.L1619
.L1668:
	ldr	r3, [r6, #68]
	mov	r2, r5
	ldr	r1, .L1734+176
	mov	r0, #32
	blx	r3
	b	.L1719
.L1733:
	ldr	r3, [r6, #68]
	mov	r2, r4
	ldr	r1, .L1734+180
	mov	r0, #32
	blx	r3
	b	.L1719
.L1727:
	ldr	r3, [r7, #68]
	mov	r2, r4
	ldr	r1, .L1734+180
	mov	r0, #32
	blx	r3
	b	.L1719
.L1732:
	ldr	r7, .L1734
	mov	r0, #14
	add	r6, r5, r6
	ldr	r8, [r7, #72]
	bl	VFMW_GetString
	ldr	r2, [r5, #1100]
	mov	r1, #50
	ldr	r3, .L1734+24
	add	ip, r2, #1
	str	ip, [r5, #1100]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #148
	blx	r8
	ldr	r3, [r7, #32]
	sub	r0, fp, #148
	mov	r2, #0
	mov	r1, #66
	blx	r3
	str	r4, [r5, #1104]
	cmp	r0, #0
	str	r0, [r6, #972]
	beq	.L1680
	ldr	r5, [r7, #68]
	mov	r3, r4
	sub	r2, fp, #148
	ldr	r1, .L1734+184
	mov	r0, #32
	blx	r5
	b	.L1719
.L1731:
	ldr	r8, .L1734
	mov	r0, #13
	ldr	r9, [r8, #72]
	bl	VFMW_GetString
	ldr	r2, [r6, #964]
	mov	r1, #50
	ldr	r3, .L1734+24
	add	ip, r2, #1
	str	ip, [r6, #964]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #148
	blx	r9
	mov	r2, r7
	ldr	r3, [r8, #32]
	sub	r0, fp, #148
	mov	r1, #66
	blx	r3
	str	r4, [r6, #968]
	cmp	r0, #0
	str	r0, [r5, #552]
	beq	.L1676
	ldr	r5, [r8, #68]
	mov	r3, r4
	sub	r2, fp, #148
	ldr	r1, .L1734+188
	mov	r0, #32
	blx	r5
	b	.L1719
.L1688:
	ldr	r3, [r7, #68]
	sub	r2, fp, #148
	ldr	r1, .L1734+192
	mov	r0, #32
	blx	r3
	b	.L1719
.L1692:
	mov	r0, r10
	ldr	r3, [r6, #68]
	movw	r2, #7945
	ldr	r1, .L1734+196
	blx	r3
	b	.L1693
.L1730:
	ldr	r8, .L1734
	mov	r0, #15
	ldr	r9, .L1734+72
	ldr	r10, [r8, #72]
	bl	VFMW_GetString
	ldr	r2, [r6, #1236]
	add	r3, r9, #4
	mov	r1, #100
	add	ip, r2, #1
	str	ip, [r6, #1236]
	str	r2, [sp]
	mov	r2, r0
	sub	r0, fp, #148
	blx	r10
	ldr	r3, [r8, #32]
	sub	r0, fp, #148
	mov	r2, r5
	movw	r1, #578
	blx	r3
	cmp	r0, #0
	str	r0, [r7, #1108]
	beq	.L1683
	ldr	r3, [r8, #48]
	mov	r2, #16
	mov	r1, r5
	ldr	r0, .L1734+76
	blx	r3
	mov	r0, #19
	bl	VFMW_GetString
	str	r5, [sp]
	ldr	r3, .L1734+76
	mov	r2, #14155776
	mov	r1, r5
	bl	MEM_AllocMemBlock
	cmp	r0, #0
	beq	.L1684
	ldr	r3, [r8, #68]
	mov	r0, #1
	ldr	r1, .L1734+200
	blx	r3
	ldr	r3, [r8, #36]
	ldr	r0, [r7, #1108]
	blx	r3
	mvn	r3, #0
	str	r5, [r7, #1108]
	str	r5, [r6, #1256]
	str	r5, [r6, #1260]
	str	r5, [r6, #1264]
	str	r5, [r6, #1268]
	str	r3, [r9, #68]
	b	.L1719
.L1691:
	ldr	r3, [r6, #68]
	mov	r2, r5
	ldr	r1, .L1734+192
	mov	r0, #32
	blx	r3
	b	.L1719
.L1684:
	ldr	r2, [r6, #1252]
	ldr	r1, [r6, #1244]
	ldr	r0, [r6, #1248]
	bl	MEM_AddMemRecord
	ldr	r3, [r6, #1244]
	mov	r0, r4, lsr #24
	ldr	r5, [r8, #68]
	add	ip, r3, #9437184
	add	r1, r3, #11796480
	str	r3, [r6, #1264]
	and	r4, r4, #3
	str	r1, [r6, #1256]
	mov	r3, r0
	str	r0, [r9, #68]
	sub	r2, fp, #148
	str	ip, [r6, #1260]
	mov	r0, #32
	str	r4, [r6, #1268]
	ldr	r1, .L1734+204
	str	r4, [sp]
	blx	r5
	b	.L1719
.L1680:
	ldr	r3, [r7, #68]
	sub	r2, fp, #148
	ldr	r1, .L1734+208
	mov	r0, #32
	blx	r3
	b	.L1719
.L1676:
	ldr	r3, [r8, #68]
	sub	r2, fp, #148
	ldr	r1, .L1734+212
	mov	r0, #32
	blx	r3
	b	.L1719
.L1683:
	ldr	r3, [r8, #68]
	sub	r2, fp, #148
	ldr	r1, .L1734+216
	mov	r0, #32
	blx	r3
	b	.L1719
.L1735:
	.align	2
.L1734:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC177
	.word	.LANCHOR0
	.word	.LC187
	.word	.LC161
	.word	.LC181
	.word	.LANCHOR2+4
	.word	.LC173
	.word	.LC188
	.word	.LC154
	.word	g_PrintEnable
	.word	.LC150
	.word	g_TraceImgPeriod
	.word	.LC185
	.word	.LC151
	.word	.LC176
	.word	.LANCHOR3
	.word	.LC171
	.word	.LANCHOR2
	.word	.LANCHOR3+1240
	.word	s_SmIIS
	.word	.LC159
	.word	.LC160
	.word	.LC180
	.word	.LC178
	.word	USE_FF_APT_EN
	.word	.LC155
	.word	.LC156
	.word	.LC164
	.word	.LC179
	.word	.LC157
	.word	.LC158
	.word	.LC167
	.word	.LC152
	.word	g_TraceCtrl
	.word	.LC182
	.word	g_TunnelLineNumber
	.word	.LC186
	.word	g_TraceBsPeriod
	.word	.LC183
	.word	g_TraceFramePeriod
	.word	.LC184
	.word	g_vdm_hal_fun_ptr
	.word	.LC175
	.word	.LC153
	.word	.LC172
	.word	.LC165
	.word	.LC162
	.word	.LC174
	.word	.LC8
	.word	.LC168
	.word	.LC169
	.word	.LC166
	.word	.LC163
	.word	.LC170
	UNWIND(.fnend)
	.size	VCTRL_SetDbgOption, .-VCTRL_SetDbgOption
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	subs	r7, r1, #0
	mov	r4, r0
	beq	.L1763
	cmp	r0, #15
	bhi	.L1764
	ldr	r6, .L1770
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1765
	ldr	r2, [r7]
	cmp	r2, #1
	bhi	.L1766
	ldr	r9, [r3, #16]
	bl	VCTRL_StopChan
	ldr	r8, .L1770+4
	mov	r5, #0
	ldr	r3, [r6, r4, asl #2]
	mov	r2, #300
	ldr	r0, .L1770+8
	mov	r1, r5
	ldr	r10, [r8, #48]
	str	r5, [r3, #328]
	str	r5, [r3, #332]
	mla	r0, r2, r4, r0
	blx	r10
	mov	r1, r5
	mov	r0, r4
	bl	VCTRL_SetSendStreamAgainFlag
	ldr	r2, [r7, #4]
	ldr	r3, [r6, r4, asl #2]
	mov	r0, r4
	str	r2, [r3, #1224]
	bl	InitSyntaxCtx
	ldr	r3, [r6, r4, asl #2]
	add	r1, r3, #229376
	ldr	r0, [r3, #528]
	add	r1, r1, #120
	bl	ReleaseCurPic
	ldr	r0, [r6, r4, asl #2]
	ldr	r3, [r8, #48]
	mov	r1, r5
	mov	r2, #416
	add	r0, r0, #664
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	mvn	r0, #0
	mvn	r1, #0
	add	r2, r3, #592
	strd	r0, [r2, #-8]
	strd	r0, [r2]
	mov	r0, r4
	ldr	r2, [r3, #1404]
	str	r5, [r3, #1080]
	cmp	r2, #1
	streq	r5, [r3, #1444]
	ldr	r3, [r3, #528]
	cmp	r3, #19
	beq	.L1743
	ldr	r3, [r7, #8]
	cmp	r3, #0
	beq	.L1767
.L1743:
	bl	FSP_EmptyInstance
.L1744:
	mov	r0, r4
	bl	InitUsdPool
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L1768
.L1745:
	ldr	r3, .L1770+12
	ldr	r2, [r3, #548]
	cmp	r2, #0
	beq	.L1746
	add	r5, r3, r4, lsl #2
	str	r4, [fp, #-48]
	ldr	r3, [r5, #552]
	cmp	r3, #0
	beq	.L1748
	mov	r0, #512
	sub	r1, fp, #48
	bl	VCTRL_SetDbgOption
	ldr	r3, [r5, #552]
	cmp	r3, #0
	beq	.L1748
	sub	r1, fp, #48
	mov	r0, #512
	bl	VCTRL_SetDbgOption
.L1748:
	ldr	r3, [r8, #68]
	mov	r0, #32
	ldr	r1, .L1770+16
	blx	r3
.L1746:
	cmp	r9, #0
	bne	.L1769
.L1750:
	mov	r0, r4
	bl	VDMDRV_ClearChanIsDec
	mov	r0, #0
.L1738:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1768:
	mov	r0, r4
	bl	SM_Reset
	b	.L1745
.L1769:
	mov	r0, r4
	bl	VCTRL_StartChan
	b	.L1750
.L1767:
	bl	FSP_ResetInstance
	b	.L1744
.L1766:
	ldr	r3, .L1770+4
	movw	r2, #3505
	ldr	r1, .L1770+20
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L1738
.L1764:
	ldr	ip, .L1770+4
	movw	r2, #3500
	ldr	r3, .L1770+24
	mov	r0, #0
	ldr	r1, .L1770+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1738
.L1763:
	ldr	ip, .L1770+4
	mov	r0, r7
	ldr	r3, .L1770+32
	movw	r2, #3499
	ldr	r1, .L1770+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1738
.L1765:
	ldr	ip, .L1770+4
	mov	r0, r3
	movw	r2, #3501
	ldr	r3, .L1770+36
	ldr	r1, .L1770+28
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1738
.L1771:
	.align	2
.L1770:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+3868
	.word	.LANCHOR3
	.word	.LC128
	.word	.LC190
	.word	.LC6
	.word	.LC1
	.word	.LC189
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_ResetChanWithOption, .-VCTRL_ResetChanWithOption
	.align	2
	.global	VCTRL_DestroyChanWithOption
	.type	VCTRL_DestroyChanWithOption, %function
VCTRL_DestroyChanWithOption:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 96
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #96)
	sub	sp, sp, #96
	ldr	r5, .L1783
	mov	r4, r0
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	cmp	r4, #15
	bhi	.L1779
	ldr	r7, .L1783+4
	ldr	r6, [r7, r4, asl #2]
	cmp	r6, #0
	beq	.L1780
	ldr	r3, [r6, #12]
	cmp	r3, #1
	bne	.L1781
	ldr	r2, .L1783+8
	mov	r8, #0
	ldr	r3, [r5, #12]
	mov	r0, #4
	str	r8, [r2, r4, asl #2]
	blx	r3
	mov	r0, r4
	bl	VCTRL_StopChan
	subs	r6, r0, #0
	bne	.L1782
	mov	r0, r4
	bl	SCDDRV_ResetSCD
	ldr	r3, [r5, #16]
	mov	r0, #4
	blx	r3
	mov	r0, r4
	bl	VCTRL_ResetChan
	bl	VDMDRV_ParamInit
	add	r2, r7, r4, lsl #2
	ldr	r3, [r5, #12]
	mov	r0, #4
	str	r6, [r2, #3604]
	blx	r3
	mov	r0, r4
	bl	FSP_DisableInstance
	mov	r0, r4
	bl	CloseUsdPool_WithMem
	ldr	r3, [r7, r4, asl #2]
	ldr	r8, [r5, #52]
	mov	r2, #16
	add	r1, r3, #232
	add	r0, r3, #227328
	ldr	lr, [r3, #248]
	add	r0, r0, #856
	ldr	ip, [r3, #252]
	ldr	r9, [r3, #256]
	ldr	r3, [r3, #1404]
	str	lr, [fp, #-68]
	str	ip, [fp, #-64]
	str	r0, [fp, #-40]
	sub	r0, fp, #100
	str	r9, [fp, #-60]
	str	r3, [fp, #-44]
	blx	r8
	ldr	r1, [r7, r4, asl #2]
	ldr	r3, [r5, #52]
	mov	r2, #16
	add	r1, r1, #200
	sub	r0, fp, #132
	blx	r3
	ldr	r1, [r7, r4, asl #2]
	ldr	r3, [r5, #52]
	mov	r2, #16
	add	r1, r1, #216
	sub	r0, fp, #116
	blx	r3
	ldr	r8, .L1783+12
	mov	r3, r4, asl #6
	mov	r2, #16
	sub	r3, r3, r4, asl #4
	ldr	r9, [r5, #52]
	add	r8, r3, r8
	sub	r0, fp, #84
	mov	r1, r8
	blx	r9
	ldr	r1, [r7, r4, asl #2]
	mov	r2, #12
	ldr	r3, [r5, #52]
	add	r1, r1, #152
	sub	r0, fp, #56
	blx	r3
	ldr	r3, .L1783+16
	mov	r0, r4
	str	r6, [r8, #40]
	str	r6, [r7, r4, asl #2]
	str	r6, [r3, r4, asl #2]
	bl	VDMDRV_ClearChanIsDec
	mov	r0, r4
	bl	VDMDRV_ResetVDH
	ldr	r3, [r5, #16]
	mov	r0, #4
	blx	r3
	bl	VCTRL_EnableAllInt
	ldr	r3, [r5, #16]
	mov	r0, r6
	blx	r3
	sub	r1, fp, #132
	mov	r0, r4
	bl	VCTRL_FreeChanResource
	mov	r0, r6
.L1774:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1781:
	ldr	r4, [r5, #68]
	movw	r2, #2463
	ldr	r3, .L1783+20
.L1778:
	ldr	r1, .L1783+24
	mov	r0, #0
	blx	r4
	bl	VCTRL_EnableAllInt
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1782:
	ldr	r3, [r5, #16]
	mov	r0, #4
	blx	r3
	ldr	r3, [r5, #16]
	mov	r0, r8
	blx	r3
	mvn	r0, #0
	b	.L1774
.L1779:
	ldr	r4, [r5, #68]
	movw	r2, #2437
	ldr	r3, .L1783+28
	b	.L1778
.L1780:
	mov	r2, #2448
	ldr	r3, .L1783+32
	ldr	r1, .L1783+24
	mov	r0, r6
	ldr	r4, [r5, #68]
	blx	r4
	bl	VCTRL_EnableAllInt
	ldr	r3, [r5, #16]
	mov	r0, r6
	blx	r3
	mvn	r0, #0
	b	.L1774
.L1784:
	.align	2
.L1783:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	g_LowDelaySeqIndex
	.word	s_SmIIS
	.word	s_pFspInst
	.word	.LC193
	.word	.LC191
	.word	.LC6
	.word	.LC192
	UNWIND(.fnend)
	.size	VCTRL_DestroyChanWithOption, .-VCTRL_DestroyChanWithOption
	.align	2
	.global	VCTRL_DestroyChan
	.type	VCTRL_DestroyChan, %function
VCTRL_DestroyChan:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VCTRL_DestroyChanWithOption
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
	ldr	r6, .L1804
	ldr	r3, [r6, #64]
	cmp	r3, #1
	bne	.L1793
	sub	r5, r6, #4
	mov	r4, #0
.L1789:
	ldr	r3, [r5, #4]!
	mov	r0, r4
	add	r4, r4, #1
	cmp	r3, #0
	beq	.L1788
	bl	VCTRL_DestroyChanWithOption
.L1788:
	cmp	r4, #16
	bne	.L1789
	bl	FSP_Exit
	ldr	r3, [r6, #68]
	mov	r2, #3
	ldr	r5, .L1804+4
	cmp	r3, #0
	str	r2, [r6, #72]
	beq	.L1791
	mov	r0, #10
	ldr	r3, [r5, #124]
	mov	r4, #49
	blx	r3
	b	.L1792
.L1803:
	ldr	r3, [r5, #124]
	blx	r3
	subs	r4, r4, #1
	beq	.L1791
.L1792:
	ldr	r3, [r6, #68]
	mov	r0, #10
	cmp	r3, #0
	bne	.L1803
.L1791:
	ldr	r3, [r5, #48]
	mov	r2, #64
	mov	r1, #0
	ldr	r0, .L1804+8
	blx	r3
	ldr	r0, .L1804+12
	bl	CloseDrivers
	bl	DBG_DestroyTracer
	mov	r3, #0
	mov	r0, r3
	str	r3, [r6, #64]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1793:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1805:
	.align	2
.L1804:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+3604
	.word	.LANCHOR0+88
	UNWIND(.fnend)
	.size	VCTRL_CloseVfmw, .-VCTRL_CloseVfmw
	.align	2
	.global	VCTRL_LoadDspCode
	.type	VCTRL_LoadDspCode, %function
VCTRL_LoadDspCode:
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
	cmp	r0, #15
	mov	r6, r0
	bhi	.L1848
	ldr	r8, .L1855
	ldr	r0, [r8, r0, asl #2]
	cmp	r0, #0
	beq	.L1849
	ldr	r3, [r0, #528]
	cmp	r3, #0
	beq	.L1850
	ldr	r5, [r8, #3604]
	cmp	r5, #0
	bne	.L1833
	mov	r2, r5
	mov	r7, r5
.L1829:
	ldr	r1, .L1855+4
	add	r0, r1, #60
.L1815:
	ldr	r5, [r1, #4]!
	cmp	r5, #0
	bne	.L1811
	cmp	r1, r0
	bne	.L1815
.L1822:
	ldr	r4, .L1855+8
	ldr	r3, [r4]
	cmp	r3, #0
	beq	.L1851
	mov	r0, #0
	blx	r3
.L1817:
	ldr	r3, [r4, #8]
	cmp	r3, #0
	beq	.L1852
	mov	r0, #0
	blx	r3
.L1819:
	clz	r5, r5
	mov	r5, r5, lsr #5
	ands	r1, r5, r7
	beq	.L1853
	ldr	r3, [r8, r6, asl #2]
	add	r6, r8, r6, lsl #2
	mov	r1, #0
	ldr	r0, [r3, #528]
	bl	WriteHexFile
	mov	r3, #1
	str	r3, [r6, #3604]
.L1823:
	ldr	r1, .L1855+12
	mov	r0, #0
	add	lr, r1, #64
.L1826:
	ldr	r2, [r1, #4]!
	mov	r3, #0
	cmp	r2, r3
	beq	.L1824
	ldr	ip, [r2, #528]
	cmp	ip, r3
	ldreq	r2, [r2, #1236]
	subeq	r3, r2, #1
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	cmp	ip, #6
	orreq	r3, r3, #1
	cmp	r3, #0
	movne	r0, #1
.L1824:
	cmp	r1, lr
	bne	.L1826
	cmp	r0, #0
	bne	.L1827
	ldr	r3, [r4, #12]
	cmp	r3, #0
	beq	.L1854
	blx	r3
.L1827:
	bl	VCTRL_CloseHardware
	mov	r0, #0
.L1845:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1850:
	ldr	r2, [r0, #1236]
	ldr	r5, [r8, #3604]
	sub	r7, r2, #1
	clz	r7, r7
	cmp	r5, #0
	mov	r7, r7, lsr #5
	beq	.L1829
.L1811:
	cmp	r5, #2
	movne	r1, #0
	andeq	r1, r7, #1
	cmp	r1, #0
	bne	.L1813
.L1814:
	cmp	r5, #1
	cmpeq	r3, #6
	bne	.L1822
.L1813:
	ldr	ip, .L1855+16
	mov	r0, #0
	str	r5, [sp]
	ldr	r1, .L1855+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1845
.L1853:
	ldr	r3, [r8, r6, asl #2]
	ldr	r7, .L1855
	ldr	r0, [r3, #528]
	cmp	r0, #6
	movne	r5, #0
	andeq	r5, r5, #1
	cmp	r5, #0
	beq	.L1823
	add	r6, r7, r6, lsl #2
	bl	WriteHexFile
	mov	r3, #2
	str	r3, [r6, #3604]
	b	.L1823
.L1852:
	ldr	ip, .L1855+16
	mov	r0, r3
	movw	r2, #3369
	ldr	r1, .L1855+24
	ldr	r3, [ip, #68]
	blx	r3
	b	.L1819
.L1851:
	ldr	ip, .L1855+16
	mov	r0, r3
	movw	r2, #3368
	ldr	r1, .L1855+24
	ldr	r3, [ip, #68]
	blx	r3
	b	.L1817
.L1854:
	ldr	r3, .L1855+16
	movw	r2, #3422
	ldr	r1, .L1855+24
	ldr	r3, [r3, #68]
	blx	r3
	b	.L1827
.L1833:
	mov	r2, #0
	mov	r7, r2
	b	.L1814
.L1848:
	ldr	ip, .L1855+16
	movw	r2, #3196
	ldr	r3, .L1855+28
	mov	r0, #0
	ldr	r1, .L1855+32
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1845
.L1849:
	ldr	ip, .L1855+16
	movw	r2, #3197
	ldr	r3, .L1855+36
	ldr	r1, .L1855+32
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L1845
.L1856:
	.align	2
.L1855:
	.word	.LANCHOR0
	.word	.LANCHOR0+3604
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0-4
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC194
	.word	.LC8
	.word	.LC6
	.word	.LC1
	.word	.LC2
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
	cmp	r0, #15
	bhi	.L1861
	ldr	r3, .L1862
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r0, r0, #225280
	strne	r1, [r0, #2860]
	ldmnefd	sp, {fp, sp, pc}
	ldr	ip, .L1862+4
	movw	r2, #8549
	ldr	r3, .L1862+8
	b	.L1860
.L1861:
	ldr	ip, .L1862+4
	movw	r2, #8548
	ldr	r3, .L1862+12
	mov	r0, #0
.L1860:
	ldr	r1, .L1862+16
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L1863:
	.align	2
.L1862:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC6
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L1868
	ldr	r3, .L1870
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1869
	add	r0, r0, #225280
	ldr	r0, [r0, #2872]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1868:
	ldr	ip, .L1870+4
	movw	r2, #8556
	ldr	r3, .L1870+8
	mov	r0, #0
	ldr	r1, .L1870+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1869:
	ldr	ip, .L1870+4
	movw	r2, #8557
	ldr	r3, .L1870+16
	ldr	r1, .L1870+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1871:
	.align	2
.L1870:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC2
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r6, r0
	mov	r4, r1
	bhi	.L1885
	ldr	r5, .L1887
	mov	r0, #0
	ldr	r3, [r5, #12]
	blx	r3
	cmp	r4, #1
	beq	.L1876
	bcc	.L1877
	cmp	r4, #2
	bne	.L1886
	ldr	r3, .L1887+4
	add	r6, r3, r6, lsl #2
	ldr	r3, [r6, #684]
	cmp	r3, #1
	beq	.L1881
.L1883:
	str	r4, [r6, #684]
	mov	r4, #0
	b	.L1875
.L1877:
	ldr	r3, .L1887+4
	mov	r2, #0
	mov	r4, r2
	add	r6, r3, r6, lsl #2
	str	r2, [r6, #684]
.L1875:
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1886:
	mov	r4, #0
	b	.L1875
.L1876:
	ldr	r3, .L1887+4
	add	r6, r3, r6, lsl #2
	ldr	r0, [r6, #684]
	cmp	r0, #0
	beq	.L1883
.L1881:
	mvn	r4, #0
	b	.L1875
.L1885:
	ldr	ip, .L1887
	movw	r2, #8566
	ldr	r3, .L1887+8
	mov	r0, #0
	ldr	r1, .L1887+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1888:
	.align	2
.L1887:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR3
	.word	.LC6
	.word	.LC1
	UNWIND(.fnend)
	.size	VCTRT_SetChanCtrlState, .-VCTRT_SetChanCtrlState
	.global	__aeabi_idiv
	.align	2
	.global	VCTRL_RequestChanMem
	.type	VCTRL_RequestChanMem, %function
VCTRL_RequestChanMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r4, r0
	bhi	.L1903
	ldr	r6, .L1908
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L1904
	add	ip, r3, #225280
	ldr	r2, [r3, #264]
	ldr	r1, [ip, #2872]
	ldr	r7, [ip, #2880]
	cmp	r1, #0
	ble	.L1905
	ldr	r3, [r3, #260]
	cmp	r3, #0
	cmpne	r2, #0
	ble	.L1894
	mov	r0, r2
	bl	__aeabi_idiv
	cmp	r7, r0
	mov	r9, r0
	ble	.L1895
	rsb	r8, r0, r7
	cmp	r8, #0
	ble	.L1895
	mov	r1, r0
	mov	r0, r4
	bl	VCTRL_AllocMemPre
	ldr	r7, .L1908+4
	ldr	r10, [r6, r4, asl #2]
	ldr	r3, [r7]
	add	r10, r10, #229376
	mov	r5, r0
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	cmp	r5, #0
	add	r3, r3, #225280
	str	r0, [r10, #24]
	str	r9, [r3, #2884]
	bne	.L1896
	ldr	r3, [r3, #2892]
	cmp	r3, #1
	bne	.L1897
	mov	r1, r8
	mov	r0, r4
	bl	VCTRL_AllocMemMMZ
	subs	r5, r0, #0
	bne	.L1906
	ldr	r3, [r7]
	ldr	r7, [r6, r4, asl #2]
	blx	r3
	ldr	r2, [r6, r4, asl #2]
	mov	r3, r5
	add	r7, r7, #229376
	add	r2, r2, #225280
	str	r0, [r7, #28]
	mov	r0, r3
	str	r8, [r2, #2888]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1894:
	ldr	r3, [ip, #2892]
	cmp	r3, #1
	bne	.L1899
	mov	r1, r7
	ldr	r8, .L1908+4
	bl	VCTRL_AllocMemMMZ
	ldr	r9, [r6, r4, asl #2]
	ldr	r3, [r8]
	add	r9, r9, #229376
	mov	r5, r0
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	cmp	r5, #0
	add	r3, r3, #225280
	str	r0, [r9, #28]
	str	r7, [r3, #2888]
	bne	.L1907
.L1901:
	mov	r3, r5
.L1891:
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1895:
	mov	r1, r7
	mov	r0, r4
	bl	VCTRL_AllocMemPre
	ldr	r8, .L1908+4
	ldr	r9, [r6, r4, asl #2]
	ldr	r3, [r8]
	add	r9, r9, #229376
	mov	r5, r0
	blx	r3
	ldr	r3, [r6, r4, asl #2]
	cmp	r5, #0
	add	r3, r3, #225280
	str	r0, [r9, #24]
	str	r7, [r3, #2884]
	beq	.L1901
	ldr	r4, [r8, #68]
	movw	r3, #8809
	b	.L1902
.L1907:
	ldr	r4, [r8, #68]
	movw	r3, #8826
	ldr	r2, .L1908+8
	mov	r0, #31
	ldr	r1, .L1908+12
	blx	r4
	mov	r3, r5
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1896:
	ldr	r4, [r7, #68]
	movw	r3, #8795
.L1902:
	ldr	r2, .L1908+8
	mov	r0, #31
	ldr	r1, .L1908+16
	blx	r4
	mov	r3, r5
	mov	r0, r3
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1899:
	ldr	ip, .L1908+4
	mov	r0, #31
	ldr	r2, .L1908+8
	ldr	r1, .L1908+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r3, #0
	b	.L1891
.L1897:
	ldr	r4, [r7, #68]
	mov	r0, #31
	ldr	r2, .L1908+8
	ldr	r1, .L1908+24
	blx	r4
	mvn	r3, #0
	b	.L1891
.L1903:
	ldr	ip, .L1908+4
	movw	r2, #8742
	ldr	r3, .L1908+28
	mov	r0, #0
	ldr	r1, .L1908+32
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r3, #0
	b	.L1891
.L1906:
	movw	r3, #8778
	ldr	r4, [r7, #68]
	ldr	r2, .L1908+8
	mov	r0, #31
	ldr	r1, .L1908+12
	blx	r4
	mvn	r3, #0
	b	.L1891
.L1905:
	ldr	r3, .L1908+4
	mov	r2, r1
	mov	r0, #31
	ldr	r1, .L1908+36
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r3, #0
	b	.L1891
.L1904:
	ldr	ip, .L1908+4
	mov	r0, r3
	movw	r2, #8743
	ldr	r3, .L1908+40
	ldr	r1, .L1908+32
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r3, #0
	b	.L1891
.L1909:
	.align	2
.L1908:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+212
	.word	.LC196
	.word	.LC198
	.word	.LC199
	.word	.LC197
	.word	.LC6
	.word	.LC1
	.word	.LC195
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_RequestChanMem, .-VCTRL_RequestChanMem
	.align	2
	.global	VCTRL_SetFsParamToChan
	.type	VCTRL_SetFsParamToChan, %function
VCTRL_SetFsParamToChan:
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
	cmp	r0, #15
	bhi	.L1914
	ldr	r3, .L1916
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L1915
	ldr	r2, [r1, #8]
	add	r3, r0, #225280
	str	r2, [r0, #264]
	ldr	r2, [r1]
	str	r2, [r0, #260]
	ldr	r2, [r1]
	str	r2, [r0, #208]
	ldr	r2, [r1, #4]
	str	r2, [r0, #204]
	ldr	r2, [r1, #8]
	str	r2, [r0, #212]
	ldr	r2, [r1, #12]
	str	r2, [r3, #2880]
	ldr	r2, [r1, #16]
	str	r2, [r3, #2892]
	ldmfd	sp, {fp, sp, pc}
.L1914:
	ldr	ip, .L1916+4
	movw	r2, #8841
	ldr	r3, .L1916+8
	mov	r0, #0
.L1913:
	ldr	r1, .L1916+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L1915:
	ldr	ip, .L1916+4
	movw	r2, #8842
	ldr	r3, .L1916+16
	b	.L1913
.L1917:
	.align	2
.L1916:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	VCTRL_SetFsParamToChan, .-VCTRL_SetFsParamToChan
	.align	2
	.global	DBG_WriteBigTileYuv
	.type	DBG_WriteBigTileYuv, %function
DBG_WriteBigTileYuv:
	UNWIND(.fnstart)
	@ args = 32, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #52)
	sub	sp, sp, #52
	mov	r5, r3
	ldr	r3, [fp, #4]
	cmp	r0, #0
	cmpne	r1, #0
	str	r0, [fp, #-68]
	mov	r7, r1
	movne	ip, #1
	moveq	ip, #0
	mov	r0, r3
	str	r3, [fp, #-48]
	ldr	r3, [fp, #12]
	cmp	r2, #0
	moveq	ip, #0
	andne	ip, ip, #1
	cmp	ip, #0
	mov	r10, r2
	ldr	r8, [fp, #8]
	str	r3, [fp, #-60]
	ldr	r3, [fp, #16]
	ldr	r1, [fp, #24]
	str	r3, [fp, #-72]
	ldr	r3, [fp, #20]
	mov	ip, r3
	str	r3, [fp, #-76]
	ldr	r3, [fp, #28]
	mov	lr, r3
	str	r3, [fp, #-80]
	ldr	r3, [fp, #32]
	beq	.L1918
	ldr	r4, .L2025
	ldr	r2, [r4, #1264]
	cmp	r2, #0
	beq	.L1918
	ldr	r2, [r4, #1260]
	cmp	r2, #0
	beq	.L1918
	ldr	r2, [r4, #1256]
	cmp	r2, #0
	beq	.L1918
	rsb	r9, ip, r5
	ldr	r6, .L2025+4
	rsb	r1, r1, r9
	rsb	r2, lr, r0
	rsb	r3, r3, r2
	str	r1, [fp, #-64]
	mov	ip, r1
	mov	r0, #32
	mov	r2, ip
	ldr	r1, .L2025+8
	ldr	r9, [r6, #68]
	str	r3, [fp, #-88]
	blx	r9
	ldr	r2, [fp, #-48]
	cmp	r8, #0
	cmpne	r8, #3
	mov	r3, r5, lsr #1
	str	r3, [fp, #-84]
	mov	r3, r2, lsr #1
	str	r3, [fp, #-56]
	bne	.L1922
	cmp	r2, #0
	mov	r3, r2
	strne	r10, [fp, #-92]
	movne	r3, #0
	strne	r3, [fp, #-52]
	movne	r9, r3
	beq	.L1924
.L1926:
	cmp	r5, #0
	beq	.L1927
	ldr	r3, [fp, #-52]
	mov	r10, #0
	and	r8, r3, #15
	mov	r2, r3, lsr #4
	ldr	r3, [fp, #-60]
	mul	r2, r3, r2
	add	r8, r2, r8, lsl #8
.L1925:
	mov	r1, r10, lsr #8
	ldr	r0, [r4, #1264]
	add	r2, r9, r10
	ldr	r3, [r6, #52]
	add	r1, r8, r1, lsl #12
	add	r0, r0, r2
	add	r1, r7, r1
	add	r10, r10, #256
	mov	r2, #256
	blx	r3
	cmp	r5, r10
	bhi	.L1925
.L1927:
	ldr	r3, [fp, #-52]
	add	r9, r9, r5
	ldr	r2, [fp, #-48]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, r2
	bne	.L1926
	ldr	r10, [fp, #-92]
.L1924:
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-88]
	ldr	r1, [fp, #-48]
	cmp	r3, r5
	cmpeq	r2, r1
	moveq	r3, #1
	movne	r3, #0
	str	r3, [fp, #-92]
	beq	.L2020
	ldr	r2, [fp, #-76]
	ldr	r3, [fp, #-80]
	ldr	r9, [fp, #-88]
	mla	r7, r3, r5, r2
	cmp	r9, #0
	ldr	r2, [r4, #1264]
	add	r7, r2, r7
	beq	.L1932
	str	r10, [fp, #-48]
	ldr	r8, [fp, #-92]
	ldr	r10, [fp, #-68]
.L1933:
	mov	r0, r7
	add	r8, r8, #1
	ldr	r3, [r6, #44]
	mov	r2, r10
	ldr	r1, [fp, #-64]
	add	r7, r7, r5
	blx	r3
	cmp	r8, r9
	bne	.L1933
	ldr	r10, [fp, #-48]
.L1932:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	beq	.L1929
	ldr	r3, [fp, #-60]
	mov	r8, #0
	str	r8, [fp, #-48]
	mov	r3, r3, lsr #1
	str	r3, [fp, #-52]
.L1930:
	cmp	r5, #0
	beq	.L1937
	ldr	r3, [fp, #-48]
	mov	r9, #0
	and	r7, r3, #7
	mov	r2, r3, lsr #3
	ldr	r3, [fp, #-52]
	mul	r2, r3, r2
	add	r7, r2, r7, lsl #8
.L1935:
	mov	r1, r9, lsr #8
	ldr	r0, [r4, #1264]
	add	r2, r8, r9
	ldr	r3, [r6, #52]
	add	r1, r7, r1, lsl #11
	add	r0, r0, r2
	add	r1, r10, r1
	add	r9, r9, #256
	mov	r2, #256
	blx	r3
	cmp	r5, r9
	bhi	.L1935
.L1937:
	ldr	r3, [fp, #-48]
	add	r8, r8, r5
	ldr	r2, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L1930
	ldr	r3, [fp, #-72]
	ldr	lr, [r4, #1264]
	cmp	r3, #1
	beq	.L2021
.L1939:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	beq	.L2022
.L1940:
	ldr	r3, [fp, #-92]
	cmp	r3, #0
	bne	.L2023
	ldr	r1, [fp, #-88]
	ldr	r3, [fp, #-80]
	ldr	r2, [fp, #-76]
	movs	r8, r1, lsr #1
	ldr	r1, [fp, #-84]
	mov	r3, r3, lsr #1
	ldr	r5, [r4, #1260]
	mov	r2, r2, lsr #1
	ldr	r4, [r4, #1256]
	mla	r3, r3, r1, r2
	add	r5, r5, r3
	add	r4, r4, r3
	beq	.L1918
	ldr	r3, [fp, #-64]
	ldr	r7, [fp, #-92]
	ldr	r10, [fp, #-68]
	mov	r9, r3, lsr #1
	str	r4, [fp, #-48]
	mov	r4, r1
.L1946:
	mov	r0, r5
	add	r7, r7, #1
	ldr	r3, [r6, #44]
	mov	r2, r10
	mov	r1, r9
	add	r5, r5, r4
	blx	r3
	cmp	r7, r8
	bne	.L1946
	ldr	r4, [fp, #-48]
	mov	r5, #0
	ldr	r7, [fp, #-84]
	ldr	r10, [fp, #-68]
.L1947:
	mov	r0, r4
	add	r5, r5, #1
	ldr	r3, [r6, #44]
	mov	r2, r10
	mov	r1, r9
	add	r4, r4, r7
	blx	r3
	cmp	r5, r8
	bne	.L1947
.L1918:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1922:
	subs	r3, r8, #1
	ldr	r2, [fp, #-48]
	movne	r3, #1
	cmp	r2, r3
	str	r3, [fp, #-64]
	ldrhi	r3, [fp, #-64]
	strhi	r10, [fp, #-76]
	strhi	r3, [fp, #-52]
	bls	.L1949
.L1951:
	cmp	r5, #0
	beq	.L1952
	ldr	r3, [fp, #-52]
	mov	r10, #0
	and	r8, r3, #15
	mov	r2, r3, lsr #4
	mov	r9, r3, lsr #1
	ldr	r3, [fp, #-60]
	mul	r9, r5, r9
	mul	r2, r3, r2
	add	r8, r2, r8, lsl #8
.L1950:
	mov	r1, r10, lsr #8
	ldr	r0, [r4, #1264]
	add	r2, r10, r9
	ldr	r3, [r6, #52]
	add	r1, r8, r1, lsl #12
	add	r0, r0, r2
	add	r1, r7, r1
	add	r10, r10, #256
	mov	r2, #256
	blx	r3
	cmp	r5, r10
	bhi	.L1950
.L1952:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-48]
	add	r3, r3, #2
	str	r3, [fp, #-52]
	cmp	r2, r3
	bhi	.L1951
	ldr	r10, [fp, #-76]
.L1949:
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-68]
	ldr	r0, [r4, #1264]
	mul	r1, r3, r5
	ldr	r3, [r6, #44]
	mov	r1, r1, lsr #1
	blx	r3
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	beq	.L1953
	ldr	r3, [fp, #-60]
	mov	r8, #0
	str	r8, [fp, #-48]
	mov	r3, r3, lsr #1
	str	r3, [fp, #-52]
.L1954:
	cmp	r5, #0
	beq	.L1957
	ldr	r3, [fp, #-48]
	mov	r9, #0
	and	r7, r3, #7
	mov	r2, r3, lsr #3
	ldr	r3, [fp, #-52]
	mul	r2, r3, r2
	add	r7, r2, r7, lsl #8
.L1955:
	mov	r1, r9, lsr #8
	ldr	r0, [r4, #1264]
	add	r2, r8, r9
	ldr	r3, [r6, #52]
	add	r1, r7, r1, lsl #11
	add	r0, r0, r2
	add	r1, r10, r1
	add	r9, r9, #256
	mov	r2, #256
	blx	r3
	cmp	r5, r9
	bhi	.L1955
.L1957:
	ldr	r3, [fp, #-48]
	add	r8, r8, r5
	ldr	r2, [fp, #-56]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L1954
	ldr	r3, [fp, #-72]
	cmp	r3, #1
	ldr	r3, [r4, #1264]
	beq	.L2024
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	bne	.L1960
	ldr	r2, [fp, #-56]
	ldr	r3, [fp, #-64]
	cmp	r2, r3
	bls	.L1965
.L1966:
	add	r3, r3, #2
	cmp	r2, r3
	bhi	.L1966
.L1965:
	ldr	r3, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [r4, #1256]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [r4, #1260]
	blx	r3
.L1960:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-84]
	ldr	r7, [fp, #-68]
	ldr	r0, [r4, #1260]
	mul	r5, r3, r2
	ldr	r3, [r6, #44]
	mov	r2, r7
	mov	r5, r5, lsr #1
.L2019:
	mov	r1, r5
	blx	r3
	mov	r1, r5
	ldr	r3, [r6, #44]
	mov	r2, r7
	ldr	r0, [r4, #1256]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L2020:
	mul	r1, r1, r5
	ldr	r3, [r6, #44]
	ldr	r2, [fp, #-68]
	ldr	r0, [r4, #1264]
	blx	r3
	b	.L1932
.L2024:
	ldr	r2, [fp, #-64]
	mov	lr, #0
	ldr	r8, [fp, #-84]
	ldr	r9, [fp, #-56]
	mla	r3, r2, r5, r3
	mov	r5, r5, asl #1
	add	r7, r3, #1
.L1961:
	cmp	r8, #0
	beq	.L1964
	mov	r3, lr, lsr #1
	mov	r2, r7
	mul	r3, r8, r3
	add	ip, r3, r8
.L1962:
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	ldr	r1, [r4, #1256]
	strb	r0, [r1, r3]
	ldrb	r0, [r2], #2	@ zero_extendqisi2
	ldr	r1, [r4, #1260]
	strb	r0, [r1, r3]
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1962
.L1964:
	add	lr, lr, #2
	add	r7, r7, r5
	cmp	r9, lr
	bhi	.L1961
	b	.L1960
.L2021:
	ldr	r8, [fp, #-84]
	mov	r3, #0
	ldr	r9, [fp, #-56]
	add	lr, lr, #1
	mov	r7, r3
.L1941:
	cmp	r8, #0
	moveq	ip, r3
	beq	.L1944
	add	ip, r3, r8
	mov	r2, lr
.L1942:
	ldrb	r0, [r2, #-1]	@ zero_extendqisi2
	ldr	r1, [r4, #1256]
	strb	r0, [r1, r3]
	ldrb	r0, [r2], #2	@ zero_extendqisi2
	ldr	r1, [r4, #1260]
	strb	r0, [r1, r3]
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1942
.L1944:
	add	r7, r7, #1
	mov	r3, ip
	cmp	r7, r9
	add	lr, lr, r5
	bne	.L1941
	b	.L1940
.L2022:
	ldr	r3, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [r4, #1256]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #1048576
	mov	r1, #128
	ldr	r0, [r4, #1260]
	blx	r3
	b	.L1940
.L2023:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-84]
	ldr	r7, [fp, #-68]
	ldr	r0, [r4, #1260]
	mul	r5, r3, r2
	ldr	r3, [r6, #44]
	mov	r2, r7
	b	.L2019
.L1929:
	ldr	r3, [fp, #-72]
	cmp	r3, #1
	bne	.L1939
	b	.L1940
.L1953:
	ldr	r3, [fp, #-72]
	cmp	r3, #1
	beq	.L1960
	cmp	r3, #0
	beq	.L1965
	b	.L1960
.L2026:
	.align	2
.L2025:
	.word	.LANCHOR3
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC200
	UNWIND(.fnend)
	.size	DBG_WriteBigTileYuv, .-DBG_WriteBigTileYuv
	.align	2
	.global	VCTRL_GetChanImage
	.type	VCTRL_GetChanImage, %function
VCTRL_GetChanImage:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 520
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #556)
	sub	sp, sp, #556
	ldr	r6, .L2081
	mov	r4, r1
	mov	r2, r0
	mov	r5, r0
	ldr	r1, .L2081+4
	mov	r0, #2
	ldr	r3, [r6, #68]
	blx	r3
	cmp	r4, #0
	beq	.L2066
	cmp	r5, #15
	bhi	.L2067
	ldr	r7, .L2081+8
	ldr	r0, [r7, r5, asl #2]
	cmp	r0, #0
	beq	.L2068
	ldr	r3, [r0, #12]
	cmp	r3, #1
	bne	.L2069
	ldr	r3, [r6, #12]
	mov	r0, #4
	blx	r3
	ldr	r0, [r7, r5, asl #2]
	cmp	r0, #0
	beq	.L2070
	ldr	r3, [r0, #12]
	cmp	r3, #1
	bne	.L2071
	add	r0, r0, #229376
	mov	r1, r4
	add	r0, r0, #112
	bl	SYNTAX_ReceiveImage
	cmp	r0, #1
	mov	r9, r0
	beq	.L2072
	mov	r0, #12
	mvn	r8, #0
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L2073
.L2048:
	ldr	r3, [r7, r5, asl #2]
	mov	r0, #4
	ldr	r2, [r6, #16]
	add	r3, r3, #241664
	ldrb	r3, [r3, #4036]	@ zero_extendqisi2
	strb	r3, [r4, #480]
	blx	r2
.L2062:
	mov	r0, r8
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2072:
	ldr	r10, .L2081+12
	mov	r3, r5, asl #2
	str	r3, [fp, #-552]
	add	r3, r10, r3
	ldr	r0, [r3, #1108]
	cmp	r0, #0
	beq	.L2036
	ldr	r3, [r4, #160]
	ldr	lr, [r10, #1268]
	tst	r3, #28
	ldr	r2, [r4, #36]
	ldr	r3, [r4, #164]
	moveq	ip, #1
	movne	ip, #0
	cmp	lr, #0
	beq	.L2037
	ldr	lr, [r4, #352]
	mov	r8, #0
	ldr	r1, [r4, #32]
	str	ip, [sp, #12]
	ldr	ip, [r4, #348]
	str	lr, [sp, #28]
	ldr	lr, [r4, #344]
	str	ip, [sp, #24]
	ldr	ip, [r4, #340]
	str	lr, [sp, #20]
	ldr	lr, [r4, #192]
	str	ip, [sp, #16]
	ldr	ip, [r4, #168]
	stmib	sp, {r8, lr}
	str	ip, [sp]
	bl	DBG_WriteBigTileYuv
.L2036:
	ldr	r3, [r4, #256]
	mvn	r8, #0
	str	r8, [r4, #252]
	cmp	r3, #1
	beq	.L2050
.L2046:
	mov	r0, #12
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L2074
.L2051:
	mov	r2, #0
	mov	r1, #12
	mov	r0, r5
	mov	r8, r2
	bl	DBG_CountTimeInfo
	ldr	r2, [r4, #160]
	ldr	r3, [r7, r5, asl #2]
	str	r2, [r3, #308]
	ldr	r2, [r4, #364]
	str	r2, [r3, #312]
	b	.L2048
.L2037:
	ldr	r1, [r4, #32]
	ldr	r8, [r4, #192]
	str	lr, [sp, #28]
	str	lr, [sp, #24]
	str	lr, [sp, #20]
	str	lr, [sp, #16]
	str	ip, [sp, #12]
	ldr	ip, [r4, #168]
	str	lr, [sp, #4]
	str	r8, [sp, #8]
	str	ip, [sp]
	bl	DBG_WriteBigTileYuv
	b	.L2036
.L2073:
	ldr	r10, .L2081+12
	mov	r3, r5, asl #2
	str	r3, [fp, #-552]
.L2047:
	ldr	r3, [r6]
	blx	r3
	ldr	r3, [fp, #-552]
	ldr	r2, .L2081+16
	add	r1, r10, r3
	ldr	r3, [r1, #1276]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	cmp	r3, r2
	bhi	.L2075
.L2049:
	cmp	r8, #0
	bne	.L2048
	b	.L2051
.L2050:
	ldr	r2, [r4, #244]
	cmp	r2, #0
	str	r2, [fp, #-556]
	beq	.L2076
	ldr	r0, [r4, #92]
	mov	r2, #60
	ldr	ip, [r4, #88]
	add	r1, r4, #420
	str	r3, [fp, #-556]
	str	r0, [r4, #264]
	add	r0, r4, #280
	ldr	r3, [r6, #52]
	str	ip, [r4, #260]
	blx	r3
	ldr	r3, [fp, #-556]
	str	r8, [r4, #252]
	str	r3, [r4, #244]
	mov	r3, #3
	str	r3, [r4, #364]
	b	.L2046
.L2074:
	mov	r8, #0
	b	.L2047
.L2069:
	ldr	r4, [r6, #68]
	movw	r2, #3845
	ldr	r3, .L2081+20
	mov	r0, #0
	ldr	r1, .L2081+24
	mvn	r8, #0
	blx	r4
	b	.L2062
.L2071:
	ldr	r3, [r6, #68]
	movw	r2, #3863
	ldr	r1, .L2081+28
	mov	r0, #0
.L2063:
	blx	r3
	ldr	r3, [r6, #16]
	mov	r0, #4
	mvn	r8, #0
	blx	r3
	b	.L2062
.L2075:
	mov	r2, r5, asl #24
	str	r0, [r1, #1276]
	add	r2, r2, #786432
	movw	r1, #4053
	cmp	r9, #1
	addeq	r2, r2, #1
	ldr	r0, .L2081+32
	bl	DBG_AddTrace
	b	.L2049
.L2076:
	ldr	r0, [r7, r5, asl #2]
	sub	r1, fp, #548
	add	r0, r0, #229376
	add	r0, r0, #112
	bl	SYNTAX_ReceiveImage
	cmp	r0, #1
	str	r0, [fp, #-560]
	bne	.L2077
	ldr	r3, [r4, #248]
	ldr	r2, [fp, #-300]
	cmp	r3, r2
	blt	.L2078
	bgt	.L2079
	cmp	r3, #0
	ldr	r3, .L2081+8
	ldr	r0, [r3, r5, asl #2]
	bne	.L2043
	add	r0, r0, #229376
	mvn	r9, #1
	add	r0, r0, #112
	bl	SYNTAX_ReturnImage
	ldr	r3, .L2081+8
	mov	r1, r4
	ldr	r0, [r3, r5, asl #2]
	add	r0, r0, #229376
	add	r0, r0, #112
	bl	SYNTAX_ReleaseImage
	ldr	r0, [fp, #-560]
	ldr	r3, [r4, #248]
	ldr	r2, .L2081+36
	ldr	r1, .L2081+40
	ldr	ip, [r6, #68]
	blx	ip
.L2045:
	mov	r0, #12
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L2049
	b	.L2047
.L2067:
	ldr	r4, [r6, #68]
	movw	r2, #3841
	ldr	r3, .L2081+44
	mov	r0, #0
	ldr	r1, .L2081+24
	mvn	r8, #0
	blx	r4
	b	.L2062
.L2077:
	ldr	r3, .L2081+8
	ldr	r8, [fp, #-560]
	ldr	r0, [r3, r5, asl #2]
	add	r0, r0, #229376
	add	r0, r0, #112
	bl	SYNTAX_ReturnImage
	ldr	r3, [r6, #16]
	mov	r0, #4
	blx	r3
	b	.L2062
.L2078:
	ldr	r0, [fp, #-460]
	mov	r2, #60
	ldr	r3, [fp, #-452]
	sub	r1, fp, #128
	ldr	ip, [fp, #-456]
	ldr	lr, [fp, #-448]
	str	r0, [r4, #260]
	add	r0, r4, #280
	str	r3, [r4, #268]
	str	ip, [r4, #264]
	ldr	r3, [r6, #52]
	str	lr, [r4, #272]
	blx	r3
	ldr	r8, [fp, #-304]
	ldr	r3, [fp, #-352]
	mov	r2, #3
	cmp	r8, #0
	str	r2, [r4, #364]
	str	r3, [r4, #252]
	ldreq	r9, [fp, #-560]
	ldrne	r3, [fp, #-560]
	ldrne	r8, [fp, #-556]
	strne	r3, [r4, #244]
	movne	r9, r3
	b	.L2045
.L2043:
	add	r0, r0, #229376
	mov	r1, r4
	add	r0, r0, #112
	bl	SYNTAX_ReleaseImage
	ldr	r3, [fp, #-304]
	cmp	r3, #0
	beq	.L2080
	ldr	ip, [r6, #68]
	ldr	r3, [r4, #248]
	ldr	r2, .L2081+36
	ldr	r1, .L2081+48
	ldr	r0, [fp, #-560]
	blx	ip
	sub	r1, fp, #548
	ldr	r3, [r6, #52]
	mov	r2, #504
	mov	r0, r4
	blx	r3
	ldr	r0, [fp, #-456]
	ldr	ip, [fp, #-460]
	mov	r2, #60
	ldr	r3, [r6, #52]
	sub	r1, fp, #128
	str	r0, [r4, #264]
	add	r0, r4, #280
	str	ip, [r4, #260]
	blx	r3
	ldr	r3, [fp, #-560]
	str	r8, [r4, #252]
	str	r3, [r4, #244]
	mov	r3, #3
	str	r3, [r4, #364]
	b	.L2046
.L2079:
	ldr	r3, .L2081+8
	mvn	r9, #1
	ldr	r0, [r3, r5, asl #2]
	add	r0, r0, #229376
	add	r0, r0, #112
	bl	SYNTAX_ReturnImage
	ldr	r3, .L2081+8
	mov	r1, r4
	ldr	r0, [r3, r5, asl #2]
	add	r0, r0, #229376
	add	r0, r0, #112
	bl	SYNTAX_ReleaseImage
	ldr	r1, [fp, #-300]
	ldr	r3, [r4, #248]
	ldr	r0, [fp, #-560]
	str	r1, [sp]
	ldr	r2, .L2081+36
	ldr	r1, .L2081+52
	ldr	ip, [r6, #68]
	blx	ip
	b	.L2045
.L2066:
	ldr	r5, [r6, #68]
	mov	r0, r4
	ldr	r3, .L2081+56
	mov	r2, #3840
	ldr	r1, .L2081+24
	mvn	r8, #0
	blx	r5
	b	.L2062
.L2068:
	ldr	r4, [r6, #68]
	movw	r2, #3842
	ldr	r3, .L2081+60
	mvn	r8, #0
	ldr	r1, .L2081+24
	blx	r4
	b	.L2062
.L2070:
	ldr	r3, [r6, #68]
	movw	r2, #3853
	ldr	r1, .L2081+64
	b	.L2063
.L2080:
	ldr	r3, .L2081+8
	sub	r1, fp, #548
	mvn	r9, #1
	ldr	r0, [r3, r5, asl #2]
	add	r0, r0, #229376
	add	r0, r0, #112
	bl	SYNTAX_ReleaseImage
	ldr	r0, [fp, #-560]
	ldr	r3, [r4, #248]
	ldr	r2, .L2081+36
	ldr	r1, .L2081+48
	ldr	ip, [r6, #68]
	blx	ip
	b	.L2045
.L2082:
	.align	2
.L2081:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC201
	.word	.LANCHOR0
	.word	.LANCHOR3
	.word	g_TraceImgPeriod
	.word	.LC38
	.word	.LC1
	.word	.LC42
	.word	.LANCHOR1+256
	.word	.LANCHOR1+236
	.word	.LC203
	.word	.LC6
	.word	.LC204
	.word	.LC202
	.word	.LC39
	.word	.LC2
	.word	.LC41
	UNWIND(.fnend)
	.size	VCTRL_GetChanImage, .-VCTRL_GetChanImage
	.align	2
	.global	VCTRL_GetImageWidth
	.type	VCTRL_GetImageWidth, %function
VCTRL_GetImageWidth:
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
	cmp	r0, #15
	bhi	.L2084
	ldr	r3, .L2094
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L2084
	add	r0, r0, #229376
	ldr	r3, [r0, #112]
	cmp	r3, #2
	beq	.L2085
	cmp	r3, #17
	beq	.L2086
	cmp	r3, #0
	beq	.L2093
.L2084:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L2085:
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_GetImageWidth
.L2093:
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_GetImageWidth
.L2086:
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_GetImageWidth
.L2095:
	.align	2
.L2094:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetImageWidth, .-VCTRL_GetImageWidth
	.align	2
	.global	VCTRL_GetImageHeight
	.type	VCTRL_GetImageHeight, %function
VCTRL_GetImageHeight:
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
	cmp	r0, #15
	bhi	.L2097
	ldr	r3, .L2107
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L2097
	add	r0, r0, #229376
	ldr	r3, [r0, #112]
	cmp	r3, #2
	beq	.L2098
	cmp	r3, #17
	beq	.L2099
	cmp	r3, #0
	beq	.L2106
.L2097:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L2098:
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_GetImageHeight
.L2106:
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_GetImageHeight
.L2099:
	add	r0, r0, #120
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVCDEC_GetImageHeight
.L2108:
	.align	2
.L2107:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VCTRL_GetImageHeight, .-VCTRL_GetImageHeight
	.global	s_VfmwSavePath
	.global	g_DnrIrqHandle
	.global	g_VdecIrqHandle
	.global	g_StopDec
	.global	g_DnrSleepTime
	.global	g_SleepTime
	.global	MemRecord_YUV
	.global	pVl
	.global	pUl
	.global	pY
	.global	g_u32DFSMaxAllocTime
	.global	pOption
	.global	g_eVdmVersion
	.global	g_VdmCharacter
	.global	g_CurProcChan
	.global	g_ResetCreateNewSave
	.global	save_yuv_with_crop
	.global	save_yuv_chan_num
	.global	vfmw_save_yuv_file
	.global	save_seg_chan_num
	.global	vfmw_save_seg_file
	.global	save_str_chan_num
	.global	vfmw_save_str_file
	.global	g_apple_airplay_mirrorinig_flag
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
	.global	g_DSPState
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.25534, %object
	.size	__func__.25534, 18
__func__.25534:
	.ascii	"VCTRL_EventReport\000"
	.space	2
	.type	__func__.25546, %object
	.size	__func__.25546, 18
__func__.25546:
	.ascii	"VCTRL_SetCallBack\000"
	.space	2
	.type	__FUNCTION__.25634, %object
	.size	__FUNCTION__.25634, 29
__FUNCTION__.25634:
	.ascii	"VCTRL_PartitionMemForStdUser\000"
	.space	3
	.type	__FUNCTION__.25862, %object
	.size	__FUNCTION__.25862, 23
__FUNCTION__.25862:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__func__.25863, %object
	.size	__func__.25863, 23
__func__.25863:
	.ascii	"VCTRL_ReleaseChanImage\000"
	.space	1
	.type	__FUNCTION__.25934, %object
	.size	__FUNCTION__.25934, 19
__FUNCTION__.25934:
	.ascii	"VCTRL_FlushDecoder\000"
	.space	1
	.type	__FUNCTION__.26252, %object
	.size	__FUNCTION__.26252, 18
__FUNCTION__.26252:
	.ascii	"GetExtraRefFrmNum\000"
	.space	2
	.type	__FUNCTION__.26258, %object
	.size	__FUNCTION__.26258, 19
__FUNCTION__.26258:
	.ascii	"GetExtraDispFrmNum\000"
	.space	1
	.type	__FUNCTION__.26264, %object
	.size	__FUNCTION__.26264, 16
__FUNCTION__.26264:
	.ascii	"GetExtraCtrlCmd\000"
	.type	__FUNCTION__.26184, %object
	.size	__FUNCTION__.26184, 14
__FUNCTION__.26184:
	.ascii	"DecChanSyntax\000"
	.space	2
	.type	__FUNCTION__.26500, %object
	.size	__FUNCTION__.26500, 21
__FUNCTION__.26500:
	.ascii	"VCTRL_RequestChanMem\000"
	.space	3
	.type	__func__.25844, %object
	.size	__func__.25844, 19
__func__.25844:
	.ascii	"VCTRL_GetChanImage\000"
	.space	1
	.type	__FUNCTION__.25852, %object
	.size	__FUNCTION__.25852, 19
__FUNCTION__.25852:
	.ascii	"VCTRL_GetChanImage\000"
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	g_not_direct_8x8_inference_flag, %object
	.size	g_not_direct_8x8_inference_flag, 1
g_not_direct_8x8_inference_flag:
	.byte	1
	.space	3
	.type	s_VfmwSavePath, %object
	.size	s_VfmwSavePath, 64
s_VfmwSavePath:
	.byte	47
	.byte	109
	.byte	110
	.byte	116
	.byte	0
	.space	59
	.type	save_yuv_chan_num, %object
	.size	save_yuv_chan_num, 4
save_yuv_chan_num:
	.word	-1
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"InstID out of range\000" )
.LC1:
	ASCII(.ascii	"vfmw_ctrl.c,L%d: %s\012\000" )
	.space	3
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
	ASCII(.ascii	"ChanID out of range\000" )
.LC7:
	ASCII(.ascii	"Force vdm %d sleep.\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"Vfmw suspend totally take %d ms\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"Wait sleep time out %d ms (isScdSleep=%d, isVdmSlee" )
	ASCII(.ascii	"p=%d)!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"Force scd %d sleep.\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"Vfmw resume totally take %d ms\012\000" )
.LC13:
	ASCII(.ascii	"can NOT config a not-opened Chan\000" )
	.space	3
.LC14:
	ASCII(.ascii	"event_report null!\000" )
	.space	1
.LC15:
	ASCII(.ascii	"%s Unkown Adapter Type: %d\012\000" )
.LC16:
	ASCII(.ascii	"pstStreamParam is NULL\000" )
	.space	1
.LC17:
	ASCII(.ascii	"L: %d, Stream Interface Error!!, ChanID: %d\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"This Chan has not been created!!!\000" )
	.space	2
.LC19:
	ASCII(.ascii	"can NOT get a not-opened Chan's information of bits" )
	ASCII(.ascii	"tream\000" )
	.space	3
.LC20:
	ASCII(.ascii	"pArgs is null\000" )
	.space	2
.LC21:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC22:
	ASCII(.ascii	"no mem to arrange for soft dec\012\000" )
.LC23:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"%s: L%d : vdm chan memory is too small to support u" )
	ASCII(.ascii	"ser decoder\012\000" )
.LC25:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"DFS, Wrong! Phyaddr:0x%x, Viraddr:0x%x, frm_num: 0x" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"DFS, Not enough Frame node,rls all node, FrmNum:%d," )
	ASCII(.ascii	" AllocedFrameNum: %d\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"DFS, Rls Fail, chanid: %d\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"VFMW_FRM_BUF\000" )
	.space	3
.LC30:
	ASCII(.ascii	"DFS, Not enough resource, ChanID: %d, AllocedFrmNum" )
	ASCII(.ascii	": %d, FrmNum: %d, i: %d\012\000" )
.LC31:
	ASCII(.ascii	"DFS, Rls Frame Node Fail!\012\000" )
	.space	1
.LC32:
	ASCII(.ascii	"pstChan == NULL\000" )
.LC33:
	ASCII(.ascii	"DFS, rls MMZ Node\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"DelMemRecord 0x%x failed!\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"pstCfg is null\000" )
	.space	1
.LC36:
	ASCII(.ascii	"Chip not support beyond %dx%d when Std != H264/VP8/" )
	ASCII(.ascii	"MVC/USER.\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"pArgs is NULL\000" )
	.space	2
.LC38:
	ASCII(.ascii	"This channel is not opened\000" )
	.space	1
.LC39:
	ASCII(.ascii	"pImage is NULL\000" )
	.space	1
.LC40:
	ASCII(.ascii	"call VCTRL_ReleaseChanImage, ChanID, ImgID = %d,%d\012" )
	ASCII(.ascii	"\000" )
.LC41:
	ASCII(.ascii	"vdm_ctrl.c,L%d: Chan inactive\012\000" )
	.space	1
.LC42:
	ASCII(.ascii	"vdm_ctrl.c,L%d: This channel is not opened\012\000" )
.LC43:
	ASCII(.ascii	"%s call SYNTAX_ReleaseImage failed\012\000" )
.LC44:
	ASCII(.ascii	"vfmw_ctrl.c, line %d: ChanID out of range\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"vfmw_ctrl.c, line %d: Chan %d is not open or not ru" )
	ASCII(.ascii	"nning\012\000" )
	.space	2
.LC46:
	ASCII(.ascii	"vfmw_ctrl.c, line %d: ChanID out of range is %d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC47:
	ASCII(.ascii	"Chan %d is not open or not running\012\000" )
.LC48:
	ASCII(.ascii	"line: %d Flush DPB failed!\012\000" )
.LC49:
	ASCII(.ascii	"VCTRL_FlushDecoder\012\000" )
.LC50:
	ASCII(.ascii	"fuction return value is null,%s %d MVC_OK != MVC_Fl" )
	ASCII(.ascii	"ushDPB!!\012\000" )
	.space	3
.LC51:
	ASCII(.ascii	"ChanId out of range\000" )
.LC52:
	ASCII(.ascii	"This channel is not running\000" )
.LC53:
	ASCII(.ascii	"chan not create\000" )
.LC54:
	ASCII(.ascii	"can NOT start a not-opened Chan\000" )
.LC55:
	ASCII(.ascii	"NULL == pArgs\000" )
	.space	2
.LC56:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC57:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame but VFMW_USER != s_pstVfmwChan" )
	ASCII(.ascii	"[ChanID]->eVidStd!\012\000" )
	.space	1
.LC58:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame but s_pstVfmwChan[ChanID]->s32" )
	ASCII(.ascii	"UsrdecFrameNum < MIN_USERDEC_FRAME_NUM!\012\000" )
.LC59:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame but FSP_IsNewFsAvalible(ChanID" )
	ASCII(.ascii	") != 1!\012\000" )
.LC60:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC61:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC62:
	ASCII(.ascii	"line: %d, pLf is NULL!\012\000" )
.LC63:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC64:
	ASCII(.ascii	"VCTRL_GetUsrdecFrame get LogicFs fail!\012\000" )
.LC65:
	ASCII(.ascii	"pChanOption is NULL\000" )
.LC66:
	ASCII(.ascii	"pDetailMemSize is NULL\000" )
	.space	1
.LC67:
	ASCII(.ascii	"ERROR: s32MaxRefFrameNum(%d), extra_ref(%d), s32Dis" )
	ASCII(.ascii	"playFrameNum(%d), extra_disp(%d)\012\000" )
	.space	3
.LC68:
	ASCII(.ascii	"ERROR: (MaxRefFrameNum(%d) + extra_ref(%d)) > 16\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC69:
	ASCII(.ascii	"VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_BY_OPTION is desig" )
	ASCII(.ascii	"ned for CAP_LEVEL_USER_DEFINE_WITH_OPTION, please c" )
	ASCII(.ascii	"hange channel's capability or use VDEC_CID_GET_CHAN" )
	ASCII(.ascii	"_MEMSIZE.\012\000" )
.LC70:
	ASCII(.ascii	"CAP_LEVEL_USER_DEFINE_WITH_OPTION option is illegal" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC71:
	ASCII(.ascii	"VCTRL_GetChanMemSizeByOption L%d: arrange return fa" )
	ASCII(.ascii	"ilure\012\000" )
	.space	2
.LC72:
	ASCII(.ascii	"eCapLevel >= CAP_LEVEL_BUTT\000" )
.LC73:
	ASCII(.ascii	"ERROR: (nPmv(%d) + extra_ref(%d)) <= 0\012\000" )
.LC74:
	ASCII(.ascii	"ERROR: TempMinFrame(%d + %d + %d), TempMiddleFrame(" )
	ASCII(.ascii	"%d + %d + %d), TempFluentFrame(%d + %d + %d)\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"VCTRL_GetChanMemSize L%d: arrange return failure\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC76:
	ASCII(.ascii	"extra_ref=\000" )
	.space	1
.LC77:
	ASCII(.ascii	"=\000" )
	.space	2
.LC78:
	ASCII(.ascii	" \000" )
	.space	2
.LC79:
	ASCII(.ascii	"fuction return value is null,%s %d unknow error!!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC80:
	ASCII(.ascii	"ERROR: extra_ref = %d is out of [ -5000, 5000 ]!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC81:
	ASCII(.ascii	"extra_disp=\000" )
.LC82:
	ASCII(.ascii	"ERROR: extra_disp = %d is out of [ -5000, 5000 ]!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC83:
	ASCII(.ascii	"extra_cmd=\000" )
	.space	1
.LC84:
	ASCII(.ascii	"OpenDrivers() error\012\000" )
	.space	3
.LC85:
	ASCII(.ascii	"HI_VFMW_VideoDecode\000" )
.LC86:
	ASCII(.ascii	"(safe,warn,danger) :amount = %d,%d,%d,%d\012\000" )
	.space	2
.LC87:
	ASCII(.ascii	"strm_ctrl: I->IPB\012\000" )
	.space	1
.LC88:
	ASCII(.ascii	"strm_ctrl: IPB->I\012\000" )
	.space	1
.LC89:
	ASCII(.ascii	"(CurrMode,NextMode) = %d,%d\012\000" )
	.space	3
.LC90:
	ASCII(.ascii	"Syntax is stopped from This channel\000" )
.LC91:
	ASCII(.ascii	"[%d] vdm busy\012\000" )
	.space	1
.LC92:
	ASCII(.ascii	"[%d] no frame\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"[%d] no stream\012\000" )
.LC94:
	ASCII(.ascii	"seg_pts: %lld, seg_usertag = %lld\012\000" )
	.space	1
.LC95:
	ASCII(.ascii	"pic_pts: %lld\012\000" )
	.space	1
.LC96:
	ASCII(.ascii	"pic_usertag: %lld\012\000" )
	.space	1
.LC97:
	ASCII(.ascii	"pic_pts: %lld pic_usertag = %lld\012\000" )
	.space	2
.LC98:
	ASCII(.ascii	"%s:ChanId %d this hevc file is 10bit!!!\012\000" )
	.space	3
.LC99:
	ASCII(.ascii	"DFS, Wait Partition\012\000" )
	.space	3
.LC100:
	ASCII(.ascii	"DFS, Partition fail, u32DynamicFrameStoreAllocEn: %" )
	ASCII(.ascii	"d, eFspPartitionState: %d\012\000" )
	.space	2
.LC101:
	ASCII(.ascii	"Thread running...\012\000" )
	.space	1
.LC102:
	ASCII(.ascii	"Thread stopped!\012\000" )
	.space	3
.LC103:
	ASCII(.ascii	"Thread killed!\012\000" )
.LC104:
	ASCII(.ascii	"thread running...\012\000" )
	.space	1
.LC105:
	ASCII(.ascii	"thread stopped...\012\000" )
	.space	1
.LC106:
	ASCII(.ascii	"ChanID out of range!\000" )
	.space	3
.LC107:
	ASCII(.ascii	"SetVdecExtra ERROR: extra_ref = %d is out of [ -500" )
	ASCII(.ascii	"0, 5000 ]!\012\000" )
	.space	1
.LC108:
	ASCII(.ascii	"SetVdecExtra ERROR: extra_disp = %d is out of [ -50" )
	ASCII(.ascii	"00, 5000 ]!\012\000" )
.LC109:
	ASCII(.ascii	"Report Last Frame, Value=%d, LastFrameState=%d\012\000" )
.LC110:
	ASCII(.ascii	"Last frame output failed!\012\000" )
	.space	1
.LC111:
	ASCII(.ascii	"Last frame output successed!\012\000" )
	.space	2
.LC112:
	ASCII(.ascii	"Last frame already output, image id: %d!\012\000" )
	.space	2
.LC113:
	ASCII(.ascii	"line %d can not know YuvFormat = %d\012\000" )
	.space	3
.LC114:
	ASCII(.ascii	"userdec frame(phy=%#x) address error!\012\000" )
	.space	1
.LC115:
	ASCII(.ascii	"can not map vir addr for usrdat frame(cbphy=%#x)\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC116:
	ASCII(.ascii	"line: %d, pLogic is Null!\012\000" )
	.space	1
.LC117:
	ASCII(.ascii	"eYuvFormat %d is not support!!\012\000" )
.LC118:
	ASCII(.ascii	"pUsrdecFrame == NULL\000" )
	.space	3
.LC119:
	ASCII(.ascii	"VCTRL_PutUsrdecFrame: VidStd is %d\012\000" )
.LC120:
	ASCII(.ascii	"VCTRL_PutUsrdecFrame return err\012\000" )
	.space	3
.LC121:
	ASCII(.ascii	"L:%d g_pstRegCrg is NULL\012\000" )
	.space	2
.LC122:
	ASCII(.ascii	"L:%d ChanID out of range\012\000" )
	.space	2
.LC123:
	ASCII(.ascii	"L:%d This Chan has not been created!!!\012\000" )
.LC124:
	ASCII(.ascii	"L:%d WARNING: vidio std not setted!\012\000" )
	.space	3
.LC125:
	ASCII(.ascii	"WARNING: vidio std not setted!\000" )
	.space	1
.LC126:
	ASCII(.ascii	"This Chan has not been created or has been destroye" )
	ASCII(.ascii	"d !\000" )
	.space	1
.LC127:
	ASCII(.ascii	"VCTRL_StopChanWithCheck fail!\012\000" )
	.space	1
.LC128:
	ASCII(.ascii	"---------------------------------------------------" )
	ASCII(.ascii	"----------------------\012\000" )
	.space	1
.LC129:
	ASCII(.ascii	"pChanOption == null\000" )
.LC130:
	ASCII(.ascii	"VDEC_CID_CREATE_CHAN_WITH_OPTION is designed for CA" )
	ASCII(.ascii	"P_LEVEL_USER_DEFINE_WITH_OPTION, please change chan" )
	ASCII(.ascii	"nel's capability.\012\000" )
	.space	3
.LC131:
	ASCII(.ascii	"line %d VCTRL_GetChanMemSizeWithOption failed!\012\000" )
.LC132:
	ASCII(.ascii	"L: %d : part we can NOT alloc buffer for channel co" )
	ASCII(.ascii	"ntext\012\000" )
	.space	2
.LC133:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel context\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC134:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel vdh\012\000" )
	.space	2
.LC135:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel vdh, %#x <" )
	ASCII(.ascii	" %#x\012\000" )
	.space	3
.LC136:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for channel scd\012\000" )
	.space	2
.LC137:
	ASCII(.ascii	"L: %d : can NOT alloc buffer for SCD\012\000" )
	.space	2
.LC138:
	ASCII(.ascii	"can NOT enable FSP instance\012\000" )
	.space	3
.LC139:
	ASCII(.ascii	"vfmw have max(%d) channels opened, can NOT crerate " )
	ASCII(.ascii	"more channels\012\000" )
	.space	2
.LC140:
	ASCII(.ascii	"VCTRL_CreateChan eCapLevel = %d error! Try to use V" )
	ASCII(.ascii	"CTRL_CreateChanWithOption(CAP_LEVEL_USER_DEFINE_WIT" )
	ASCII(.ascii	"H_OPTION, ...)\012\000" )
	.space	2
.LC141:
	ASCII(.ascii	"VCTRL_GetChanMemSize ERROR\012\000" )
.LC142:
	ASCII(.ascii	"channel memory have been allocated outside, but the" )
	ASCII(.ascii	" mem-info is not correct!\012\000" )
	.space	2
.LC143:
	ASCII(.ascii	"mem-info(phy, vir, size) = (%#x, %p, %d)\012\000" )
	.space	2
.LC144:
	ASCII(.ascii	"this channel totally need %d bytes memory\012\000" )
	.space	1
.LC145:
	ASCII(.ascii	"pstCfg == NULL\000" )
	.space	1
.LC146:
	ASCII(.ascii	"VCTRL_CheckChanWH return err.\012\000" )
	.space	1
.LC147:
	ASCII(.ascii	"VFMW didn't support std %d.\012\000" )
	.space	3
.LC148:
	ASCII(.ascii	"VCTRL_ConfigChan with same config paramater.\012\000" )
	.space	2
.LC149:
	ASCII(.ascii	"can NOT VCTRL_PartitionMemForStdUser\012\000" )
	.space	2
.LC150:
	ASCII(.ascii	"chan %d: new ChanErrThr = %d\012\000" )
	.space	2
.LC151:
	ASCII(.ascii	"chan %d: new DecOrderOutput = %d\012\000" )
	.space	2
.LC152:
	ASCII(.ascii	"chan %d: new DecMode = %d\012\000" )
	.space	1
.LC153:
	ASCII(.ascii	"chan %d: GetChanCfg failed!\012\000" )
	.space	3
.LC154:
	ASCII(.ascii	"chan %d: new StrmOFThr = %d\012\000" )
	.space	3
.LC155:
	ASCII(.ascii	"USE_FF_APT_EN = %d\012\000" )
.LC156:
	ASCII(.ascii	"USE_FF_APT_EN can NOT be set to %d, must be 0 or 1\012" )
	ASCII(.ascii	"\000" )
.LC157:
	ASCII(.ascii	"ResetCreateNewSave = %d\012\000" )
	.space	3
.LC158:
	ASCII(.ascii	"ResetCreateNewSave can NOT be set to %d, must be 0 " )
	ASCII(.ascii	"or 1\012\000" )
	.space	3
.LC159:
	ASCII(.ascii	"NO SUCH CHANNEL : %d\012\000" )
	.space	2
.LC160:
	ASCII(.ascii	"Pay attention to  CHANNEL : %d\012\000" )
.LC161:
	ASCII(.ascii	"print memory tracer...\012\000" )
.LC162:
	ASCII(.ascii	"OK create file '%s' for channel %d raw stream save\012" )
	ASCII(.ascii	"\000" )
.LC163:
	ASCII(.ascii	"failed create file '%s' for raw stream save!\012\000" )
	.space	2
.LC164:
	ASCII(.ascii	">>>> close raw stream saving >>>>\012\000" )
	.space	1
.LC165:
	ASCII(.ascii	"OK create file '%s' for channel %d seg stream save\012" )
	ASCII(.ascii	"\000" )
.LC166:
	ASCII(.ascii	"failed create file '%s' for seg stream save!\012\000" )
	.space	2
.LC167:
	ASCII(.ascii	">>>> close seg stream saving >>>>\012\000" )
	.space	1
.LC168:
	ASCII(.ascii	"Failed Alloc VFMW_BigTile1d_YUV for yuv save!\012\000" )
	.space	1
.LC169:
	ASCII(.ascii	"OK create file '%s' for chan %d yuv save.(crop %d)\012" )
	ASCII(.ascii	"\000" )
.LC170:
	ASCII(.ascii	"failed create file '%s' for yuv save!\012\000" )
	.space	1
.LC171:
	ASCII(.ascii	"OK close yuv save.\012\000" )
.LC172:
	ASCII(.ascii	"address '0x%x' is not valid!\012\000" )
	.space	2
.LC173:
	ASCII(.ascii	"2d image has been saved to '%s'\012\000" )
	.space	3
.LC174:
	ASCII(.ascii	"open file '%s' fail!\012\000" )
	.space	2
.LC175:
	ASCII(.ascii	"1d image has been saved to '%s'\012\000" )
	.space	3
.LC176:
	ASCII(.ascii	"stop chan %d: VCTRL_StopChan return %d\012\000" )
.LC177:
	ASCII(.ascii	"reset chan %d: VCTRL_ResetChan return %d\012\000" )
	.space	2
.LC178:
	ASCII(.ascii	"start chan %d: VCTRL_StartChan return %d\012\000" )
	.space	2
.LC179:
	ASCII(.ascii	"------ dec task delay %d ms ------\012\000" )
.LC180:
	ASCII(.ascii	"------ dnr active per %d ms ------\012\000" )
.LC181:
	ASCII(.ascii	"------ dec stop = %d ------\012\000" )
	.space	3
.LC182:
	ASCII(.ascii	"------ g_TraceCtrl = %x ------\012\000" )
.LC183:
	ASCII(.ascii	"------ g_TraceBsPeriod = %x ------\012\000" )
.LC184:
	ASCII(.ascii	"------ g_TraceFramePeriod = %x ------\012\000" )
	.space	1
.LC185:
	ASCII(.ascii	"------ g_TraceImgPeriod = %x ------\012\000" )
	.space	3
.LC186:
	ASCII(.ascii	"The channel number is to Large.\012\000" )
	.space	3
.LC187:
	ASCII(.ascii	"------ s_pstVfmwChan[%d]->stSynExtraData.s32ModuleL" )
	ASCII(.ascii	"owlyEnable = 1 ------\012\000" )
	.space	2
.LC188:
	ASCII(.ascii	"------ Set SCD[%d] to work  ------\012\000" )
.LC189:
	ASCII(.ascii	"pOption is NULL\000" )
.LC190:
	ASCII(.ascii	"vdm_ctrl.c,L%d: pOption->s32KeepBS error\012\000" )
	.space	2
.LC191:
	ASCII(.ascii	"vdm_ctrl.c,L%d: %s\012\000" )
.LC192:
	ASCII(.ascii	"This Chan has not been created or has been destroye" )
	ASCII(.ascii	"d !!!\000" )
	.space	3
.LC193:
	ASCII(.ascii	"can NOT stop a not-opened Chan\000" )
	.space	1
.LC194:
	ASCII(.ascii	"WARNNING: ScdLowdlyEnable = %d, VidStd = %d, eDSPSt" )
	ASCII(.ascii	"ate = %d AVS(+) and LOWDLY  cannot supported in the" )
	ASCII(.ascii	" same time!!!\012\000" )
	.space	3
.LC195:
	ASCII(.ascii	"DFS, framsize wrong! framesize: 0x%x\012\000" )
	.space	2
.LC196:
	ASCII(.ascii	"%s, %d, AllocMemMMZ fail!\012\000" )
	.space	1
.LC197:
	ASCII(.ascii	"%s,can not use mmz. NeedMMZ: %d\012\000" )
	.space	3
.LC198:
	ASCII(.ascii	"%s, %d, AllocMemPre fail!\012\000" )
	.space	1
.LC199:
	ASCII(.ascii	"%s,can't use mmz. NeedMMZ: %d\012\000" )
	.space	1
.LC200:
	ASCII(.ascii	"VFMW: WriteBigTileYuv %dx%d...\012\000" )
.LC201:
	ASCII(.ascii	"call VCTRL_GetChanImage, ChanID = %d,\012\000" )
	.space	1
.LC202:
	ASCII(.ascii	"%s: view_0 id(%d) > view_1 id(%d), error!\012\000" )
	.space	1
.LC203:
	ASCII(.ascii	"%s: continuous view0 id(%d)!\012\000" )
	.space	2
.LC204:
	ASCII(.ascii	"%s: continuous view1 id(%d)!\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
.LANCHOR3 = . + 8184
	.type	s_pstVfmwChan, %object
	.size	s_pstVfmwChan, 64
s_pstVfmwChan:
	.space	64
	.type	s_VfmwCTrl, %object
	.size	s_VfmwCTrl, 176
s_VfmwCTrl:
	.space	176
	.type	s_StreamIntf, %object
	.size	s_StreamIntf, 192
s_StreamIntf:
	.space	192
	.type	FspInstInfo.25630, %object
	.size	FspInstInfo.25630, 2060
FspInstInfo.25630:
	.space	2060
	.type	g_VdmCharacter, %object
	.size	g_VdmCharacter, 4
g_VdmCharacter:
	.space	4
	.type	last_rec_pos_time.25859, %object
	.size	last_rec_pos_time.25859, 64
last_rec_pos_time.25859:
	.space	64
	.type	extra_ref, %object
	.size	extra_ref, 4
extra_ref:
	.space	4
	.type	extra_disp, %object
	.size	extra_disp, 4
extra_disp:
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
	.size	g_DSPState, 64
g_DSPState:
	.space	64
	.type	last_rec_pos_time.26178, %object
	.size	last_rec_pos_time.26178, 64
last_rec_pos_time.26178:
	.space	64
	.type	last_rec_pos_decparam_time.26179, %object
	.size	last_rec_pos_decparam_time.26179, 64
last_rec_pos_decparam_time.26179:
	.space	64
	.type	ChanPriTab.26139, %object
	.size	ChanPriTab.26139, 64
ChanPriTab.26139:
	.space	64
	.type	g_SleepTime, %object
	.size	g_SleepTime, 4
g_SleepTime:
	.space	4
	.type	g_StopDec, %object
	.size	g_StopDec, 4
g_StopDec:
	.space	4
	.type	g_VfmwChanStat, %object
	.size	g_VfmwChanStat, 4800
g_VfmwChanStat:
	.space	4800
	.type	PrioArray.25729, %object
	.size	PrioArray.25729, 64
PrioArray.25729:
	.space	64
	.type	g_ResetCreateNewSave, %object
	.size	g_ResetCreateNewSave, 4
g_ResetCreateNewSave:
	.space	4
	.type	vfmw_save_str_file, %object
	.size	vfmw_save_str_file, 128
vfmw_save_str_file:
	.space	128
	.type	pOption, %object
	.size	pOption, 4
pOption:
	.space	4
	.type	s_ChanControlState, %object
	.size	s_ChanControlState, 64
s_ChanControlState:
	.space	64
	.type	Capability.25776, %object
	.size	Capability.25776, 148
Capability.25776:
	.space	148
	.type	PrioArray.25775, %object
	.size	PrioArray.25775, 64
PrioArray.25775:
	.space	64
	.type	g_CurProcChan, %object
	.size	g_CurProcChan, 4
g_CurProcChan:
	.space	4
	.type	save_file_cnt.26303, %object
	.size	save_file_cnt.26303, 4
save_file_cnt.26303:
	.space	4
	.type	save_str_chan_num, %object
	.size	save_str_chan_num, 4
save_str_chan_num:
	.space	4
	.type	vfmw_save_seg_file, %object
	.size	vfmw_save_seg_file, 128
vfmw_save_seg_file:
	.space	128
	.type	save_file_cnt.26306, %object
	.size	save_file_cnt.26306, 4
save_file_cnt.26306:
	.space	4
	.type	save_seg_chan_num, %object
	.size	save_seg_chan_num, 4
save_seg_chan_num:
	.space	4
	.type	vfmw_save_yuv_file, %object
	.size	vfmw_save_yuv_file, 128
vfmw_save_yuv_file:
	.space	128
	.type	save_file_cnt.26311, %object
	.size	save_file_cnt.26311, 4
save_file_cnt.26311:
	.space	4
	.type	MemRecord_YUV, %object
	.size	MemRecord_YUV, 16
MemRecord_YUV:
	.space	16
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
	.type	save_yuv_with_crop, %object
	.size	save_yuv_with_crop, 4
save_yuv_with_crop:
	.space	4
	.type	g_DnrSleepTime, %object
	.size	g_DnrSleepTime, 4
g_DnrSleepTime:
	.space	4
	.type	last_rec_pos_time.25849, %object
	.size	last_rec_pos_time.25849, 64
last_rec_pos_time.25849:
	.space	64
	.type	g_DnrIrqHandle, %object
	.size	g_DnrIrqHandle, 4
g_DnrIrqHandle:
	.space	4
	.type	g_VdecIrqHandle, %object
	.size	g_VdecIrqHandle, 4
g_VdecIrqHandle:
	.space	4
	.type	g_u32DFSMaxAllocTime, %object
	.size	g_u32DFSMaxAllocTime, 4
g_u32DFSMaxAllocTime:
	.space	4
	.type	g_eVdmVersion, %object
	.size	g_eVdmVersion, 4
g_eVdmVersion:
	.space	4
	.type	g_VfmwGlobalStat, %object
	.size	g_VfmwGlobalStat, 84
g_VfmwGlobalStat:
	.space	84
	.type	AcceleratorCharacter, %object
	.size	AcceleratorCharacter, 4
AcceleratorCharacter:
	.space	4
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
