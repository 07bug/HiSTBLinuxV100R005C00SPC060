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
	.file	"vdm_drv.c"
	.text
	.align	2
	.type	VDMDRV_IsMpeg4NvopCopy.part.3, %function
VDMDRV_IsMpeg4NvopCopy.part.3:
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
	mov	r0, #0
	ldr	r1, .L2+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	UNWIND(.fnend)
	.size	VDMDRV_IsMpeg4NvopCopy.part.3, .-VDMDRV_IsMpeg4NvopCopy.part.3
	.align	2
	.type	VDMDRV_IsVc1SkpicCopy.part.4, %function
VDMDRV_IsVc1SkpicCopy.part.4:
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
	mov	r0, #0
	ldr	r1, .L5+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC1
	UNWIND(.fnend)
	.size	VDMDRV_IsVc1SkpicCopy.part.4, .-VDMDRV_IsVc1SkpicCopy.part.4
	.align	2
	.global	VDMDRV_Init
	.type	VDMDRV_Init, %function
VDMDRV_Init:
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
	ldr	r3, .L8
	mov	r4, r0
	ldr	r5, .L8+4
	mov	r0, r0, asl #6
	sub	r0, r0, r4, asl #3
	mov	r2, #56
	add	r0, r5, r0
	ldr	r3, [r3, #48]
	mov	r1, #0
	add	r5, r5, r4, lsl #2
	blx	r3
	ldr	r2, .L8+8
	mov	r1, #84
	mov	r3, #0
	str	r3, [r5, #56]
	mla	r4, r1, r4, r2
	str	r3, [r5, #60]
	add	r4, r4, #8
	str	r3, [r4, #4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L9:
	.align	2
.L8:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	g_VfmwGlobalStat
	UNWIND(.fnend)
	.size	VDMDRV_Init, .-VDMDRV_Init
	.align	2
	.global	VDMDRV_Reset
	.type	VDMDRV_Reset, %function
VDMDRV_Reset:
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
	ldr	r1, .L11
	mov	r3, r0, asl #6
	ldr	ip, .L11+4
	sub	r0, r3, r0, asl #3
	mov	r2, #56
	ldr	r3, [r1, #48]
	add	r0, ip, r0
	mov	r1, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L12:
	.align	2
.L11:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_Reset, .-VDMDRV_Reset
	.align	2
	.global	VDMDRV_SetPriority
	.type	VDMDRV_SetPriority, %function
VDMDRV_SetPriority:
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
	ldr	r5, .L26
	mov	r4, #0
	sub	r7, r0, #4
	mov	lr, r4
	mov	r6, r4
.L20:
	mov	ip, #0
	mov	r1, r7
	mov	r3, ip
.L15:
	ldr	r2, [r1, #4]!
	cmp	r2, ip
	movgt	lr, r3
	add	r3, r3, #1
	movgt	ip, r2
	cmp	r3, #16
	bne	.L15
	cmp	ip, #0
	ble	.L25
	add	r4, r4, #1
	str	lr, [r5, #4]!
	cmp	r4, #16
	str	r6, [r0, lr, asl #2]
	bne	.L20
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L25:
	cmp	r4, #15
	ldmgtfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, .L26+4
	mov	r2, r4, asl #2
	mvn	r1, #0
.L18:
	add	r4, r4, #1
	add	r3, r0, r2
	cmp	r4, #16
	add	r2, r2, #4
	str	r1, [r3, #132]
	bne	.L18
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L27:
	.align	2
.L26:
	.word	.LANCHOR0+128
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_SetPriority, .-VDMDRV_SetPriority
	.align	2
	.global	VDMDRV_AdjustPriorityAfterDec
	.type	VDMDRV_AdjustPriorityAfterDec, %function
VDMDRV_AdjustPriorityAfterDec:
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
	ldr	r5, .L41
	add	ip, r5, #132
	ldr	r3, [r5, #132]
	cmp	r3, r0
	beq	.L37
	mov	r3, #1
	mov	r2, ip
.L33:
	ldr	r1, [r2, #4]!
	cmp	r1, r0
	beq	.L39
	add	r3, r3, #1
	cmp	r3, #16
	bne	.L33
	mov	r3, #0
	mov	r6, #4
	mov	lr, r3
.L34:
	ldr	r0, [ip, r6]
	add	r6, ip, r6
	cmp	r0, #0
	ldmltfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r2, r3, #2
	mov	r2, r2, asl #2
	b	.L32
.L36:
	ldr	r0, [ip, r2]
	add	r2, r2, #4
	cmp	r0, #0
	ldmltfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L32:
	ldr	r4, [ip, lr, asl #2]
	add	r1, r5, r0, lsl #2
	add	r3, r3, #1
	ldr	r7, [r1, #68]
	add	r1, r5, r4, lsl #2
	ldr	r1, [r1, #68]
	cmp	r7, r1
	strge	r0, [ip, lr, asl #2]
	strge	r4, [r6]
	cmp	r3, #14
	add	r6, ip, r2
	mov	lr, r3
	ble	.L36
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L39:
	cmp	r3, #14
	bgt	.L40
.L29:
	add	r6, r3, #1
	mov	lr, r3
	mov	r6, r6, asl #2
	b	.L34
.L37:
	mov	r3, #0
	b	.L29
.L40:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L42:
	.align	2
.L41:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_AdjustPriorityAfterDec, .-VDMDRV_AdjustPriorityAfterDec
	.align	2
	.global	VDMDRV_PrepareSleep
	.type	VDMDRV_PrepareSleep, %function
VDMDRV_PrepareSleep:
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
	ldr	r1, .L47
	add	ip, r1, r0, lsl #2
	ldr	r3, [ip, #56]
	cmp	r3, #0
	bne	.L46
	mov	r2, r0, asl #6
	sub	r0, r2, r0, asl #3
	ldr	r0, [r1, r0]
	cmp	r0, #0
	moveq	r3, #2
	movne	r0, r3
	movne	r3, #1
	str	r3, [ip, #56]
	ldmfd	sp, {fp, sp, pc}
.L46:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L48:
	.align	2
.L47:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_PrepareSleep, .-VDMDRV_PrepareSleep
	.align	2
	.global	VDMDRV_GetSleepStage
	.type	VDMDRV_GetSleepStage, %function
VDMDRV_GetSleepStage:
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
	ldr	r3, .L50
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #56]
	ldmfd	sp, {fp, sp, pc}
.L51:
	.align	2
.L50:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_GetSleepStage, .-VDMDRV_GetSleepStage
	.align	2
	.global	VDMDRV_ForceSleep
	.type	VDMDRV_ForceSleep, %function
VDMDRV_ForceSleep:
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
	ldr	r3, .L57
	ldr	r5, .L57+4
	add	r4, r3, r0, lsl #2
	ldr	r2, [r4, #56]
	cmp	r2, #2
	beq	.L53
	mov	r2, r0, asl #6
	mov	r1, #0
	sub	r0, r2, r0, asl #3
	mov	r2, #56
	add	r0, r3, r0
	ldr	r3, [r5, #48]
	blx	r3
	mov	r3, #2
	str	r3, [r4, #56]
.L53:
	ldr	r3, [r5, #68]
	mov	r0, #0
	ldr	r1, .L57+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L58:
	.align	2
.L57:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	UNWIND(.fnend)
	.size	VDMDRV_ForceSleep, .-VDMDRV_ForceSleep
	.align	2
	.global	VDMDRV_ExitSleep
	.type	VDMDRV_ExitSleep, %function
VDMDRV_ExitSleep:
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
	ldr	r3, .L62
	mov	r4, r0
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L60
	blx	r3
.L61:
	ldr	r0, .L62+4
	mov	r3, #0
	add	r0, r0, r4, lsl #2
	str	r3, [r0, #56]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L60:
	ldr	ip, .L62+8
	mov	r0, r3
	mov	r2, #252
	ldr	r1, .L62+12
	ldr	r3, [ip, #68]
	blx	r3
	b	.L61
.L63:
	.align	2
.L62:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_ExitSleep, .-VDMDRV_ExitSleep
	.align	2
	.global	VDMDRV_StartRepair
	.type	VDMDRV_StartRepair, %function
VDMDRV_StartRepair:
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
	ldr	r3, .L67
	mov	r5, r0
	mov	r4, r1
	ldr	r3, [r3, #84]
	cmp	r3, #0
	beq	.L65
	mov	r0, r1
	blx	r3
.L66:
	mov	r1, r4, asl #6
	ldr	r3, .L67+4
	sub	r1, r1, r4, asl #3
	str	r5, [r3, r1]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L65:
	ldr	ip, .L67+8
	mov	r0, r3
	mov	r2, #260
	ldr	r1, .L67+12
	ldr	r3, [ip, #68]
	blx	r3
	b	.L66
.L68:
	.align	2
.L67:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_StartRepair, .-VDMDRV_StartRepair
	.align	2
	.global	VDMDRV_StartDec
	.type	VDMDRV_StartDec, %function
VDMDRV_StartDec:
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
	ldr	r3, .L72
	mov	r4, r0
	ldr	r3, [r3, #88]
	cmp	r3, #0
	beq	.L70
	blx	r3
.L71:
	mov	r0, r4, asl #6
	ldr	r3, .L72+4
	sub	r0, r0, r4, asl #3
	mov	r2, #1
	str	r2, [r3, r0]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L70:
	ldr	ip, .L72+8
	mov	r0, r3
	mov	r2, #268
	ldr	r1, .L72+12
	ldr	r3, [ip, #68]
	blx	r3
	b	.L71
.L73:
	.align	2
.L72:
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_StartDec, .-VDMDRV_StartDec
	.align	2
	.global	VDMDRV_IsChanDec
	.type	VDMDRV_IsChanDec, %function
VDMDRV_IsChanDec:
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
	ldr	r3, .L75
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #196]
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L76:
	.align	2
.L75:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_IsChanDec, .-VDMDRV_IsChanDec
	.align	2
	.global	VDMDRV_SetChanIsDec
	.type	VDMDRV_SetChanIsDec, %function
VDMDRV_SetChanIsDec:
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
	ldmhifd	sp, {fp, sp, pc}
	ldr	r2, .L79
	add	r1, r1, #1
	add	r3, r2, r0, lsl #2
	str	r1, [r3, #196]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMDRV_AdjustPriorityAfterDec
.L80:
	.align	2
.L79:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_SetChanIsDec, .-VDMDRV_SetChanIsDec
	.align	2
	.global	VDMDRV_ClearChanIsDec
	.type	VDMDRV_ClearChanIsDec, %function
VDMDRV_ClearChanIsDec:
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
	addls	r0, r0, #32
	ldrls	r3, .L83
	movls	r2, #0
	addls	r0, r3, r0, lsl #2
	strls	r2, [r0, #68]
	ldmfd	sp, {fp, sp, pc}
.L84:
	.align	2
.L83:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_ClearChanIsDec, .-VDMDRV_ClearChanIsDec
	.align	2
	.global	VDMDRV_ParamInit
	.type	VDMDRV_ParamInit, %function
VDMDRV_ParamInit:
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
	ldr	r3, .L92
	mov	r0, #1
	add	r1, r3, #64
.L87:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	strne	r0, [r2, #20]
	cmp	r3, r1
	bne	.L87
	ldmfd	sp, {fp, sp, pc}
.L93:
	.align	2
.L92:
	.word	s_pstVfmwChan-4
	UNWIND(.fnend)
	.size	VDMDRV_ParamInit, .-VDMDRV_ParamInit
	.align	2
	.global	VDMDRV_AddMatchMode
	.type	VDMDRV_AddMatchMode, %function
VDMDRV_AddMatchMode:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMDRV_AddMatchMode, .-VDMDRV_AddMatchMode
	.align	2
	.global	VDMDRV_CheckAttachMode
	.type	VDMDRV_CheckAttachMode, %function
VDMDRV_CheckAttachMode:
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
	cmp	r0, #15
	mov	r4, r0
	bgt	.L95
	ldr	r7, .L121
	ldr	r2, [r7, r0, asl #2]
	cmp	r2, #0
	beq	.L95
	add	r3, r2, #204800
	ldr	r5, .L121+4
	mov	r8, r0, asl #2
	ldr	r6, [r3, #1536]
	ldr	r3, [r3, #1532]
	cmp	r6, #2160
	cmpcs	r3, #3840
	movcs	r6, #1
	movcc	r6, #0
	bcs	.L120
	add	r3, r5, r8
	ldr	r3, [r3, #324]
.L103:
	cmp	r3, #10
	beq	.L105
.L104:
	ldr	r3, [r2, #20]
	cmp	r3, #0
	beq	.L106
.L105:
	ldr	r3, [r2, #1464]
	cmp	r3, #35
	ble	.L107
	cmp	r6, #0
	beq	.L106
	ldr	ip, .L121+8
	mov	r1, #1
	movw	r3, #530
	str	r1, [r2, #1456]
	mov	r0, #0
	str	r1, [sp, #4]
	ldr	r2, .L121+12
	str	r4, [sp]
	ldr	r1, .L121+16
	ldr	r6, [ip, #68]
	blx	r6
	ldr	r2, [r7, r4, asl #2]
.L106:
	mov	r3, #0
	str	r3, [r2, #20]
	ldr	r3, [r7, r4, asl #2]
	add	r5, r5, r8
	ldr	r3, [r3, #1464]
	str	r3, [r5, #260]
.L95:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L120:
	add	r3, r5, r8
	ldr	r2, [r2, #1464]
	ldr	r9, .L121+8
	mov	r0, #22
	ldr	r1, [r3, #260]
	movw	r3, #502
	str	r2, [sp]
	cmp	r2, r1
	rsbhi	r10, r1, r2
	rsbls	r10, r2, r1
	str	r1, [sp, #4]
	ldr	r2, .L121+12
	ldr	r1, .L121+20
	ldr	ip, [r9, #68]
	blx	ip
	cmp	r10, #2
	bgt	.L100
	add	r2, r5, r8
	ldr	r3, [r2, #324]
	add	r3, r3, #1
	str	r3, [r2, #324]
.L101:
	cmn	r3, #1
	beq	.L102
	ldr	r2, [r7, r4, asl #2]
	b	.L103
.L107:
	mov	r3, #0
	str	r3, [r2, #1456]
	ldr	r2, [r7, r4, asl #2]
	b	.L106
.L100:
	add	lr, r5, r8
	ldr	r10, [r9, #68]
	movw	r3, #511
	ldr	r2, .L121+12
	mov	r9, lr
	ldr	r1, .L121+24
	mov	r0, #22
	mov	ip, #0
	str	ip, [lr, #324]
	blx	r10
	ldr	r3, [r9, #324]
	b	.L101
.L102:
	add	r3, r5, r8
	mov	r1, #11
	ldr	r2, [r7, r4, asl #2]
	str	r1, [r3, #324]
	b	.L104
.L122:
	.align	2
.L121:
	.word	s_pstVfmwChan
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC6
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	VDMDRV_CheckAttachMode, .-VDMDRV_CheckAttachMode
	.align	2
	.global	VDMDRV_ChnDecReady
	.type	VDMDRV_ChnDecReady, %function
VDMDRV_ChnDecReady:
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
	mov	r6, r1
	mov	r5, r0
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L127
	ldr	r3, .L130
	add	r3, r3, r5, lsl #2
	ldr	r4, [r3, #196]
	cmp	r4, #0
	bne	.L128
	str	r4, [r6]
	mov	r0, r5
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	str	r0, [r6]
	beq	.L129
.L125:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L127:
	ldr	ip, .L130+4
	mov	r3, r5
	ldr	r2, .L130+8
	mov	r4, #1
	ldr	r1, .L130+12
	mov	r0, #22
	ldr	r5, [ip, #68]
	blx	r5
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L128:
	ldr	r3, .L130+4
	mov	r2, r5
	ldr	r1, .L130+16
	mov	r4, #1
	mov	r0, #22
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L129:
	ldr	r3, .L130+4
	mov	r2, r5
	ldr	r1, .L130+20
	mov	r0, #22
	mov	r4, #1
	ldr	r3, [r3, #68]
	blx	r3
	b	.L125
.L131:
	.align	2
.L130:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+24
	.word	.LC7
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	VDMDRV_ChnDecReady, .-VDMDRV_ChnDecReady
	.align	2
	.global	VDMDRV_WaitVdmReadyIfNoIsr
	.type	VDMDRV_WaitVdmReadyIfNoIsr, %function
VDMDRV_WaitVdmReadyIfNoIsr:
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
	ldr	r6, .L141
	mov	r5, r0
	mov	r4, #0
	b	.L134
.L136:
	add	r4, r4, #1
	cmp	r4, #400
	beq	.L135
.L134:
	ldr	r3, [r6, #96]
	mov	r0, r5
	cmp	r3, #0
	beq	.L136
	blx	r3
	cmp	r0, #0
	beq	.L136
.L135:
	cmp	r4, #400
	movcc	r0, #0
	movcs	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L142:
	.align	2
.L141:
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	VDMDRV_WaitVdmReadyIfNoIsr, .-VDMDRV_WaitVdmReadyIfNoIsr
	.align	2
	.global	VDMDRV_H264NeedMoreStart
	.type	VDMDRV_H264NeedMoreStart, %function
VDMDRV_H264NeedMoreStart:
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
	bics	r3, r0, #16
	bne	.L145
	ldr	r0, [r1, #20]
	ldr	r3, [r1, #28]
	ldr	r2, [r1, #664]
	mul	r3, r3, r0
	cmp	r3, r2
	movle	r0, #0
	movgt	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L145:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMDRV_H264NeedMoreStart, .-VDMDRV_H264NeedMoreStart
	.align	2
	.global	VDMDRV_H264FinishedMultiStart
	.type	VDMDRV_H264FinishedMultiStart, %function
VDMDRV_H264FinishedMultiStart:
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
	bics	r0, r0, #16
	bne	.L148
	ldr	ip, [r1, #20]
	ldr	r3, [r1, #28]
	ldr	r2, [r1, #664]
	mul	r3, r3, ip
	cmp	r3, r2
	ldrlesb	r0, [r1, #2]
	clzle	r0, r0
	movle	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L148:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDMDRV_H264FinishedMultiStart, .-VDMDRV_H264FinishedMultiStart
	.align	2
	.global	VDMDRV_AvsFirstFldNeedRepair
	.type	VDMDRV_AvsFirstFldNeedRepair, %function
VDMDRV_AvsFirstFldNeedRepair:
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
	cmp	r0, #6
	beq	.L154
.L153:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L154:
	ldr	r3, [r1, #32]
	cmp	r3, #1
	bne	.L153
	ldr	r3, .L155
	mov	r1, #1744
	mla	r2, r1, r2, r3
	ldr	r3, [r2, #1228]
	cmp	r3, #0
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L156:
	.align	2
.L155:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_AvsFirstFldNeedRepair, .-VDMDRV_AvsFirstFldNeedRepair
	.align	2
	.global	VDMDRV_AvsSecondFldNeedRepair
	.type	VDMDRV_AvsSecondFldNeedRepair, %function
VDMDRV_AvsSecondFldNeedRepair:
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
	cmp	r0, #6
	beq	.L161
.L160:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L161:
	ldr	r3, [r1, #32]
	cmp	r3, #1
	bne	.L160
	ldr	r3, .L162
	mov	r1, #1744
	mla	r2, r1, r2, r3
	ldr	r3, [r2, #1712]
	cmp	r3, #0
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L163:
	.align	2
.L162:
	.word	.LANCHOR0+388
	UNWIND(.fnend)
	.size	VDMDRV_AvsSecondFldNeedRepair, .-VDMDRV_AvsSecondFldNeedRepair
	.align	2
	.global	VDMDRV_IsMpeg4NvopCopy
	.type	VDMDRV_IsMpeg4NvopCopy, %function
VDMDRV_IsMpeg4NvopCopy:
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
	cmp	r1, #0
	beq	.L168
	cmp	r0, #2
	ldreqb	r0, [r1, #158]	@ zero_extendqisi2
	subeq	r0, r0, #1
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L168:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMDRV_IsMpeg4NvopCopy.part.3
	UNWIND(.fnend)
	.size	VDMDRV_IsMpeg4NvopCopy, .-VDMDRV_IsMpeg4NvopCopy
	.align	2
	.global	VDMDRV_IsVc1SkpicCopy
	.type	VDMDRV_IsVc1SkpicCopy, %function
VDMDRV_IsVc1SkpicCopy:
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
	cmp	r1, #0
	beq	.L173
	cmp	r0, #1
	ldreqb	r0, [r1, #1]	@ zero_extendqisi2
	subeq	r0, r0, #1
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L173:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMDRV_IsVc1SkpicCopy.part.4
	UNWIND(.fnend)
	.size	VDMDRV_IsVc1SkpicCopy, .-VDMDRV_IsVc1SkpicCopy
	.align	2
	.global	VDMDRV_IsVp6NvopCopy
	.type	VDMDRV_IsVp6NvopCopy, %function
VDMDRV_IsVp6NvopCopy:
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
	beq	.L178
	sub	r0, r0, #10
	cmp	r0, #2
	ldrlsb	r0, [r4, #1]	@ zero_extendqisi2
	subls	r0, r0, #1
	clzls	r0, r0
	movls	r0, r0, lsr #5
	movhi	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L178:
	ldr	r3, .L179
	mov	r0, r4
	ldr	r1, .L179+4
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L180:
	.align	2
.L179:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	UNWIND(.fnend)
	.size	VDMDRV_IsVp6NvopCopy, .-VDMDRV_IsVp6NvopCopy
	.align	2
	.global	VDMDRV_DoBeforeDec
	.type	VDMDRV_DoBeforeDec, %function
VDMDRV_DoBeforeDec:
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
	ldr	r3, [r2]
	mov	r9, r2
	mov	r4, r0
	cmp	r3, #0
	mov	r5, r1
	beq	.L227
	mov	r0, r1
	mov	r6, r4, asl #3
	bl	VCTRL_GetVidStd
	ldr	r3, .L237
	mov	r8, r4, asl #6
	ldr	r7, .L237+4
	rsb	r10, r6, r8
	ldr	r3, [r3]
	add	r10, r7, r10
	add	r10, r10, #8
	cmp	r3, #0
	str	r0, [r10, #4]
	beq	.L184
	ldr	r2, [r9]
	str	r0, [fp, #-52]
	sub	r0, fp, #56
	str	r5, [fp, #-56]
	str	r2, [fp, #-48]
	blx	r3
	cmp	r0, #1
	mov	r3, r0
	beq	.L183
	ldr	r0, [r10, #4]
.L184:
	ldr	r1, [r9]
	cmp	r1, #0
	beq	.L228
	cmp	r0, #2
	beq	.L229
.L189:
	cmp	r0, #1
	beq	.L230
.L190:
	bl	VDMDRV_IsVp6NvopCopy
	cmp	r0, #1
	beq	.L231
	ldr	r3, .L237+8
	ldr	r3, [r3, #92]
	cmp	r3, #0
	beq	.L202
	rsb	r2, r6, r8
	ldr	r1, [r9]
	add	r9, r7, r2
	mov	r2, r4
	ldr	r0, [r9, #12]
	blx	r3
	subs	r3, r0, #0
	beq	.L232
.L202:
	ldr	r10, .L237+12
	rsb	r6, r6, r8
	mov	r0, #0
	ldr	r1, .L237+16
	add	r8, r7, r6
	mov	r9, r0
	ldr	r3, [r10, #68]
	blx	r3
	mov	ip, #100
	str	r4, [sp]
	mov	r1, ip
	mov	r3, r9
	mov	r2, #15
	mov	r0, r5
	str	ip, [r8, #4]
	str	r9, [r7, r6]
	bl	VCTRL_VdmPostProc
	mov	r2, #56
	mov	r0, r8
	ldr	r3, [r10, #48]
	mov	r1, r9
	blx	r3
	cmp	r5, #15
	ldr	r2, .L237+4
	bhi	.L193
	add	r5, r5, #32
	mov	r3, r9
	add	r2, r2, r5, lsl #2
	str	r9, [r2, #68]
.L183:
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L230:
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L190
.L196:
	ldr	r10, .L237+12
	mov	r0, #22
	ldr	r1, .L237+20
	ldr	r3, [r10, #68]
	blx	r3
	mov	r1, r4
	ldr	r0, [r9]
	bl	PostPro_CopyYuv_Vc1
	subs	r3, r0, #0
	bne	.L193
	rsb	r6, r6, r8
	mov	r1, r4
	add	r6, r7, r6
	mov	r0, #2
	str	r3, [fp, #-64]
	str	r3, [r6, #4]
	bl	VDMDRV_StartRepair
	cmp	r5, #15
	ldr	r2, .L237+4
	ldr	r3, [fp, #-64]
	bls	.L233
.L197:
	mov	r0, #7
	str	r3, [fp, #-64]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L193
	ldr	r2, [r10]
	add	r7, r7, r5, lsl #2
	blx	r2
	ldr	r1, .L237+24
	ldr	r2, [r7, #2132]
	ldr	r1, [r1]
	rsb	r2, r2, r0
	mov	ip, r0
	cmp	r2, r1
	addhi	r2, r4, r5, lsl #24
	movhi	r1, #656
	bhi	.L224
.L193:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L229:
	ldrb	r3, [r1, #158]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L190
.L188:
	mov	r0, r1
	mov	r1, r4
	bl	PostPro_CopyYuv
	subs	r3, r0, #0
	bne	.L193
	rsb	r6, r6, r8
	mov	r1, r4
	add	r6, r7, r6
	mov	r0, #2
	str	r3, [fp, #-64]
	str	r3, [r6, #4]
	bl	VDMDRV_StartRepair
	cmp	r5, #15
	ldr	r8, .L237+4
	ldr	r3, [fp, #-64]
	bls	.L234
.L192:
	mov	r0, #7
	str	r3, [fp, #-64]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L193
	ldr	r2, .L237+12
	add	r7, r7, r5, lsl #2
	ldr	r2, [r2]
	blx	r2
	ldr	r1, .L237+24
	ldr	r2, [r7, #2132]
	ldr	r1, [r1]
	rsb	r2, r2, r0
	mov	ip, r0
	cmp	r2, r1
	addhi	r2, r4, r5, lsl #24
	movwhi	r1, #629
	bls	.L193
.L224:
	add	r2, r2, #458752
	ldr	r0, .L237+28
	str	ip, [r7, #2132]
	bl	DBG_AddTrace
	ldr	r3, [fp, #-64]
	b	.L183
.L232:
	ldr	r10, .L237+12
	str	r3, [fp, #-64]
	ldr	r2, [r10]
	blx	r2
	ldr	ip, .L237+32
	mov	r2, #84
	mla	r2, r2, r4, ip
	mov	r1, r0
	str	r0, [r9, #20]
	str	r1, [r2, #4]
	mov	r0, r4
	bl	VDMDRV_StartDec
	cmp	r5, #15
	ldr	r3, [fp, #-64]
	bls	.L235
.L204:
	mov	r0, #5
	str	r3, [fp, #-64]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L193
	ldr	r2, [r10]
	add	r7, r7, r5, lsl #2
	blx	r2
	ldr	r1, .L237+24
	ldr	r2, [r7, #2132]
	ldr	r1, [r1]
	rsb	r2, r2, r0
	mov	ip, r0
	cmp	r2, r1
	bls	.L193
	add	r2, r4, r5, lsl #24
	movw	r1, #723
	add	r2, r2, #327680
	ldr	r0, .L237+28
	str	ip, [r7, #2132]
	bl	DBG_AddTrace
	ldr	r3, [fp, #-64]
	b	.L183
.L227:
	ldr	ip, .L237+12
	mov	r2, r1
	mov	r0, #22
	ldr	r1, .L237+36
	mov	r3, #1
	str	r3, [fp, #-64]
	ldr	r4, [ip, #68]
	blx	r4
	ldr	r3, [fp, #-64]
	mov	r0, r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L231:
	ldr	r10, .L237+12
	mov	r0, #22
	ldr	r1, .L237+20
	ldr	r3, [r10, #68]
	blx	r3
	mov	r1, r4
	ldr	r0, [r9]
	bl	PostPro_CopyYuv_Vp6
	subs	r3, r0, #0
	bne	.L193
	rsb	r6, r6, r8
	mov	r1, r4
	add	r6, r7, r6
	mov	r0, #2
	str	r3, [fp, #-64]
	str	r3, [r6, #4]
	bl	VDMDRV_StartRepair
	cmp	r5, #15
	ldr	r2, .L237+4
	ldr	r3, [fp, #-64]
	bls	.L236
.L199:
	mov	r0, #7
	str	r3, [fp, #-64]
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L193
	ldr	r2, [r10]
	add	r7, r7, r5, lsl #2
	blx	r2
	ldr	r1, .L237+24
	ldr	r2, [r7, #2132]
	ldr	r1, [r1]
	rsb	r2, r2, r0
	mov	ip, r0
	cmp	r2, r1
	bls	.L193
	add	r2, r4, r5, lsl #24
	movw	r1, #683
	b	.L224
.L228:
	bl	VDMDRV_IsMpeg4NvopCopy.part.3
	cmp	r0, #1
	ldreq	r1, [r9]
	beq	.L188
.L187:
	rsb	r10, r6, r8
	ldr	r1, [r9]
	add	r10, r7, r10
	add	r10, r10, #8
	cmp	r1, #0
	ldr	r0, [r10, #4]
	bne	.L189
	bl	VDMDRV_IsVc1SkpicCopy.part.4
	cmp	r0, #1
	beq	.L196
	ldr	r0, [r10, #4]
	ldr	r1, [r9]
	b	.L190
.L235:
	ldr	r3, .L237+4
	mov	r0, r5
	add	r1, r4, #1
	add	r2, r3, r5, lsl #2
	str	r1, [r2, #196]
	bl	VDMDRV_AdjustPriorityAfterDec
	ldr	r3, [fp, #-64]
	b	.L204
.L233:
	add	r2, r2, r5, lsl #2
	mov	r0, r5
	add	r1, r4, #1
	str	r1, [r2, #196]
	bl	VDMDRV_AdjustPriorityAfterDec
	ldr	r3, [fp, #-64]
	b	.L197
.L234:
	add	r8, r8, r5, lsl #2
	mov	r0, r5
	add	r2, r4, #1
	str	r2, [r8, #196]
	bl	VDMDRV_AdjustPriorityAfterDec
	ldr	r3, [fp, #-64]
	b	.L192
.L236:
	add	r2, r2, r5, lsl #2
	mov	r0, r5
	add	r1, r4, #1
	str	r1, [r2, #196]
	bl	VDMDRV_AdjustPriorityAfterDec
	ldr	r3, [fp, #-64]
	b	.L199
.L238:
	.align	2
.L237:
	.word	AcceleratorCharacter
	.word	.LANCHOR0
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LC12
	.word	g_TraceFramePeriod
	.word	.LANCHOR1+44
	.word	g_VfmwGlobalStat
	.word	.LC11
	UNWIND(.fnend)
	.size	VDMDRV_DoBeforeDec, .-VDMDRV_DoBeforeDec
	.align	2
	.global	VDMDRV_ActivateVDH
	.type	VDMDRV_ActivateVDH, %function
VDMDRV_ActivateVDH:
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
	ldr	r9, .L245
	mov	r5, r0, asl #6
	ldr	r6, .L245+4
	sub	r5, r5, r0, asl #3
	mov	r8, r0
	mov	r0, #5
	ldr	r3, [r9, #12]
	add	r7, r5, #16
	blx	r3
	ldr	r3, [r6, #132]
	add	r7, r6, r7
	cmp	r3, #0
	blt	.L240
	add	r5, r6, r5
	add	r4, r6, #132
	add	r6, r6, #192
	b	.L241
.L244:
	cmp	r4, r6
	beq	.L240
	ldr	r3, [r4, #4]!
	cmp	r3, #0
	blt	.L240
.L241:
	mov	r0, r3
	mov	r1, r7
	str	r3, [r5, #8]
	bl	VDMDRV_ChnDecReady
	cmp	r0, #0
	bne	.L244
	mov	r2, r7
	ldr	r1, [r5, #8]
	mov	r0, r8
	bl	VDMDRV_DoBeforeDec
	cmp	r0, #0
	bne	.L244
.L240:
	ldr	r3, [r9, #16]
	mov	r0, #5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L246:
	.align	2
.L245:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDMDRV_ActivateVDH, .-VDMDRV_ActivateVDH
	.align	2
	.global	VDMDRV_AfterDec
	.type	VDMDRV_AfterDec, %function
VDMDRV_AfterDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 176
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #188)
	sub	sp, sp, #188
	ldr	r4, .L377
	mov	r2, r0, asl #6
	mov	r3, r0, asl #3
	str	r3, [fp, #-200]
	rsb	r3, r3, r2
	add	r3, r4, r3
	str	r2, [fp, #-204]
	ldr	r2, .L377+4
	mov	r10, r0
	ldr	r3, [r3, #8]
	mov	r1, #0
	ldr	r7, .L377+8
	sub	r0, fp, #180
	ldr	r8, [r2, r3, asl #2]
	mov	r2, #136
	cmp	r8, #0
	streq	r8, [fp, #-212]
	ldrne	r3, [r8, #1232]
	strne	r3, [fp, #-212]
	ldr	r3, [r7, #48]
	blx	r3
	mov	r3, #180
	mla	r3, r3, r10, r4
	ldr	r1, .L377+12
	mov	r0, #2
	ldr	r2, [r3, #2196]
	and	r2, r2, #15
	cmp	r2, #5
	ldr	r2, [fp, #-200]
	ldreq	r3, [r3, #2208]
	ldrne	r3, [r3, #2204]
	andeq	r3, r3, #1
	andne	r3, r3, #31
	str	r3, [fp, #-208]
	ldr	r3, [fp, #-204]
	rsb	r6, r2, r3
	add	r5, r4, r6
	add	r9, r5, #32
	ldr	r2, [r4, r6]
	ldr	ip, [r5, #4]
	ldr	r3, [r9, #4]
	str	ip, [sp]
	ldr	ip, [r7, #68]
	blx	ip
	ldr	r6, [r4, r6]
	ldr	r3, .L377+8
	cmp	r6, #1
	beq	.L357
	cmp	r6, #2
	beq	.L358
	cmp	r6, #3
	beq	.L359
	ldr	r4, [r3, #68]
	mov	r2, r6
	ldr	r3, [r5, #8]
	mov	r0, #0
	ldr	r1, .L377+16
	blx	r4
	ldr	r3, [r5, #8]
	cmp	r3, #15
	bhi	.L247
	add	r3, r3, #32
	ldr	r1, .L377
	mov	r2, #0
	add	r10, r1, r3, lsl #2
	str	r2, [r10, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L359:
	ldr	r3, [r9, #4]
	ldr	r2, [fp, #-200]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [r9, #4]
	ldr	r3, [fp, #-204]
.L354:
	rsb	r0, r2, r3
	str	r10, [sp]
	add	r5, r4, r0
	sub	r3, fp, #180
	mov	r8, #0
	ldr	r2, [fp, #-208]
	ldr	r1, [r5, #4]
	str	r8, [r4, r0]
	cmp	r1, #100
	ldr	r0, [r5, #8]
	ldr	r6, .L377
	movge	r1, #100
	bic	r1, r1, r1, asr #31
	str	r1, [r5, #4]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r5, #8]
	cmp	r3, #15
	addls	r3, r3, #32
	addls	r3, r6, r3, lsl #2
	strls	r8, [r3, #68]
.L306:
	ldr	r3, [fp, #-204]
	mov	r1, #0
	ldr	r2, [fp, #-200]
	rsb	r0, r2, r3
	ldr	r3, [r7, #48]
	add	r0, r4, r0
	mov	r2, #56
	blx	r3
	mov	r0, r10
	bl	VDMDRV_ActivateVDH
.L247:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L357:
	ldr	r2, [r9, #4]
	cmp	r2, #1
	beq	.L360
	ldr	r9, [r3, #48]
	mov	r2, #12
	mov	r1, #0
	sub	r0, fp, #192
	str	r3, [fp, #-216]
	blx	r9
	ldr	r1, [r5, #12]
	sub	r0, fp, #192
	ldr	r2, [r5, #16]
	str	r10, [fp, #-184]
	str	r1, [fp, #-192]
	str	r2, [fp, #-188]
	bl	PostPro_GetErrRatio
	ldr	r3, [fp, #-216]
	cmp	r0, #0
	mov	ip, r0
	str	r0, [r5, #4]
	bne	.L361
.L254:
	ldr	r3, [fp, #-204]
	ldr	r2, [fp, #-200]
	rsb	r2, r2, r3
	ldr	r3, .L377+4
	add	r2, r4, r2
	ldr	r0, [r2, #8]
	ldr	r1, [r2, #12]
	ldr	r3, [r3, r0, asl #2]
	sub	ip, r1, #8
	cmp	r1, #5
	cmpne	ip, #1
	add	r3, r3, #229376
	ldr	r1, [r3, #768]
	add	r1, r1, #1
	str	r1, [r3, #768]
	movls	r3, #0
	strls	r3, [r2, #4]
	bls	.L253
	ldr	r1, [r2, #4]
	cmp	r1, #0
	beq	.L253
	ldr	r2, .L377+20
	ldr	r3, [r8, #1144]
	ldr	r5, [r2]
	add	r3, r3, #1
	str	r3, [r8, #1144]
	cmp	r5, #0
	beq	.L253
	sub	r2, fp, #44
	mov	r3, #4
	str	r1, [r2, #-152]!
	mov	r1, #114
	blx	r5
.L253:
	ldr	r3, [fp, #-212]
	cmp	r3, #1
	beq	.L362
.L258:
	ldr	r3, [fp, #-204]
	ldr	r2, [fp, #-200]
	rsb	r3, r2, r3
	add	r5, r4, r3
	ldr	r1, [r5, #16]
	ldr	r0, [r5, #12]
	bl	PostPro_GetRepairStratage
	ldr	r1, [r5, #12]
	ldr	r3, [r5, #16]
	bics	r1, r1, #16
	mov	r9, r0
	beq	.L363
	mov	r1, #0
	str	r1, [r5, #28]
	mov	r2, r1
.L260:
	ldr	r3, [fp, #-204]
	ldr	r0, [fp, #-200]
	ldr	r6, [r7, #68]
	rsb	r8, r0, r3
	mov	r3, r1
	add	r5, r4, r8
	mov	r0, #2
	str	r1, [r5, #32]
	ldr	r1, .L377+24
	blx	r6
	ldr	r3, [r5, #28]
	ldr	r6, .L377+8
	cmp	r3, #1
	beq	.L364
	ldr	r3, [r5, #32]
	cmp	r3, #1
	beq	.L365
	ldr	r1, [r5, #4]
	cmp	r1, #0
	cmpne	r9, #1
	moveq	r9, #1
	movne	r9, #0
	beq	.L366
	add	r3, r5, #8
	ldr	r2, [r3, #4]
	add	r8, r5, #16
	ldr	r1, [r5, #16]
	cmp	r2, #6
	beq	.L367
.L274:
	ldr	r3, [r7]
	blx	r3
	ldr	r3, .L377+28
	ldr	r2, [fp, #-204]
	ldr	r1, [fp, #-200]
	ldr	r6, [r3, #104]
	rsb	r5, r1, r2
	ldr	r8, .L377+8
	add	r5, r4, r5
	cmp	r6, #0
	add	r7, r5, #16
	ldr	r9, .L377
	str	r0, [r7, #4]
	beq	.L277
	mov	r3, r10
	mov	r2, #0
	ldr	r1, [r5, #16]
	ldr	r0, [r5, #12]
	blx	r6
	cmp	r0, #0
	beq	.L368
.L277:
	ldr	r3, [fp, #-204]
	mov	r1, #100
	ldr	r2, [fp, #-200]
	str	r10, [sp]
	rsb	r5, r2, r3
	ldr	r2, [fp, #-208]
	add	r5, r4, r5
	sub	r3, fp, #180
	ldr	r6, .L377
	ldr	r0, [r5, #8]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r5, #8]
	cmp	r3, #15
	addls	r3, r3, #32
	movls	r2, #0
	addls	r3, r6, r3, lsl #2
	strls	r2, [r3, #68]
	ldr	r3, [fp, #-204]
	ldr	r2, [fp, #-200]
	rsb	r0, r2, r3
	mov	r3, #0
	str	r3, [r4, r0]
	b	.L247
.L358:
	ldr	r3, [r9, #4]
	ldr	r2, [fp, #-200]
	cmp	r3, #1
	ldr	r6, .L377
	moveq	r3, #0
	streq	r3, [r9, #4]
	ldr	r3, [fp, #-204]
	rsb	r5, r2, r3
	add	r5, r4, r5
	add	r9, r5, #8
	add	r8, r5, #16
	ldr	r3, [r9, #4]
	ldr	r1, [r5, #16]
	cmp	r3, #6
	beq	.L369
.L286:
	cmp	r1, #0
	beq	.L370
	cmp	r3, #2
	beq	.L371
	ldr	r3, [fp, #-204]
	ldr	r2, [fp, #-200]
	rsb	r3, r2, r3
	add	r3, r4, r3
	ldr	r0, [r3, #12]
	ldr	r1, [r3, #16]
.L295:
	cmp	r0, #1
	beq	.L372
.L299:
	bl	VDMDRV_IsVp6NvopCopy
	ldr	r3, [fp, #-204]
	ldr	r2, [fp, #-200]
	cmp	r0, #1
	bne	.L354
.L352:
	rsb	ip, r2, r3
	mov	r5, #0
	add	r6, r4, ip
	str	r10, [sp]
	sub	r3, fp, #180
	ldr	r2, [fp, #-208]
	ldr	r0, [r6, #8]
	mov	r1, r5
	str	r5, [r4, ip]
	str	r5, [r6, #4]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r6, #8]
	ldr	r8, .L377
	cmp	r3, #15
	addls	r3, r3, #32
	addls	r3, r8, r3, lsl #2
	strls	r5, [r3, #68]
	b	.L306
.L363:
	ldr	r0, [r3, #20]
	ldr	r2, [r3, #28]
	ldr	ip, [r3, #664]
	mul	r2, r2, r0
	cmp	r2, ip
	movle	r2, #0
	movgt	r2, #1
	str	r2, [r5, #28]
	ldr	lr, [r3, #20]
	ldr	r0, [r3, #28]
	mul	r0, r0, lr
	cmp	ip, r0
	ldrgesb	r1, [r3, #2]
	clzge	r1, r1
	movge	r1, r1, lsr #5
	b	.L260
.L361:
	ldr	r2, [r5, #8]
	mov	r0, r6
	ldr	r5, [r3, #68]
	ldr	r3, .L377+4
	ldr	r1, .L377+32
	ldr	r3, [r3, r2, asl #2]
	add	r3, r3, #229376
	ldr	r3, [r3, #768]
	str	ip, [sp]
	blx	r5
	b	.L254
.L369:
	ldr	r2, [r1, #32]
	cmp	r2, #1
	bne	.L286
	mov	r0, #1744
	mla	r0, r0, r10, r6
	ldr	r0, [r0, #2100]
	cmp	r0, #0
	ble	.L286
	ldr	r3, [r7]
	str	r2, [fp, #-212]
	blx	r3
	ldr	r3, .L377+28
	ldr	r2, [fp, #-212]
	ldr	r7, [r3, #104]
	cmp	r7, #0
	str	r0, [r8, #4]
	beq	.L277
	ldr	r0, [r9, #4]
	mov	r3, r10
	ldr	r1, [r5, #16]
	blx	r7
	cmp	r0, #0
	bne	.L277
	ldr	r0, .L377+36
	mov	r3, #84
	ldr	r2, [r8, #4]
	mov	r1, r10
	mla	r3, r3, r10, r0
	mov	r0, #3
	str	r2, [r3, #4]
	bl	VDMDRV_StartRepair
	mov	r0, #7
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L247
	ldr	r3, .L377+8
	ldr	r3, [r3]
	blx	r3
	ldr	r2, [r5, #8]
	ldr	r3, .L377+40
	add	r6, r6, r2, lsl #2
	ldr	r1, [r3]
	ldr	r3, [r6, #2376]
	rsb	r3, r3, r0
	mov	ip, r0
	cmp	r3, r1
	bls	.L247
	add	r2, r10, r2, lsl #24
	movw	r1, #1333
	add	r2, r2, #458752
	ldr	r0, .L377+44
	str	ip, [r6, #2376]
	bl	DBG_AddTrace
	b	.L247
.L366:
	ldr	r3, [fp, #-212]
	cmp	r3, #1
	beq	.L373
	cmp	r1, #100
	ldr	ip, .L377
	ldr	r0, [r5, #8]
	sub	r3, fp, #180
	movge	r1, #100
	str	r10, [sp]
	bic	r1, r1, r1, asr #31
	ldr	r2, [fp, #-208]
	str	r1, [r5, #4]
	mov	r6, #0
	str	r6, [ip, r8]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r5, #8]
	cmp	r3, #15
	bhi	.L306
.L346:
	add	r3, r3, #32
	ldr	r2, .L377
	add	r3, r2, r3, lsl #2
	str	r6, [r3, #68]
	b	.L306
.L362:
	ldr	r2, [fp, #-200]
	ldr	r3, [fp, #-204]
	rsb	r3, r2, r3
	mov	r2, #0
	add	r3, r4, r3
	str	r2, [r3, #4]
	b	.L258
.L360:
	mov	r2, r10
	ldr	r1, [r5, #16]
	ldr	r0, [r5, #12]
	str	r3, [fp, #-216]
	bl	PostPro_SetFullRepair
	ldr	r3, [fp, #-216]
	mov	r2, #0
	mov	r0, r2
	str	r2, [r9, #4]
	ldr	r1, .L377+48
	mov	r2, #100
	ldr	r3, [r3, #68]
	str	r2, [r5, #4]
	blx	r3
	b	.L253
.L368:
	ldr	r0, .L377+36
	mov	r3, #84
	ldr	r2, [r7, #4]
	mov	r1, r10
	mla	r3, r3, r10, r0
	mov	r0, #2
	str	r2, [r3, #4]
	bl	VDMDRV_StartRepair
	mov	r0, #7
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L247
	ldr	r3, [r8]
	blx	r3
	ldr	r2, [r5, #8]
	ldr	r3, .L377+40
	add	r9, r9, r2, lsl #2
	ldr	r1, [r3]
	ldr	r3, [r9, #2376]
	rsb	r3, r3, r0
	mov	ip, r0
	cmp	r3, r1
	bls	.L247
	add	r2, r10, r2, lsl #24
	movw	r1, #1292
	add	r2, r2, #458752
	ldr	r0, .L377+44
	str	ip, [r9, #2376]
	bl	DBG_AddTrace
	b	.L247
.L371:
	ldrb	r3, [r1, #158]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L300
	ldr	r3, [fp, #-204]
	ldr	r2, [fp, #-200]
	rsb	r3, r2, r3
	add	r3, r4, r3
	ldr	r0, [r3, #12]
	ldr	r1, [r3, #16]
	b	.L299
.L372:
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L299
.L300:
	ldr	r3, [fp, #-204]
	ldr	r2, [fp, #-200]
	b	.L352
.L364:
	ldr	ip, .L377
	mov	r4, #0
	ldr	r0, [r5, #8]
	sub	r3, fp, #180
	str	r10, [sp]
	mov	r1, r4
	ldr	r2, [fp, #-208]
	str	r4, [ip, r8]
	str	r4, [r5, #4]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r5, #8]
	cmp	r3, #15
	addls	r3, r3, #32
	ldrls	r2, .L377
	addls	r10, r2, r3, lsl #2
	strls	r4, [r10, #68]
	b	.L247
.L373:
	cmp	r1, #100
	ldr	r3, [r5, #52]
	movge	r1, #100
	cmp	r3, #1
	bic	r1, r1, r1, asr #31
	str	r1, [r5, #4]
	beq	.L374
	cmp	r3, #2
	beq	.L375
	cmp	r3, #3
	bne	.L247
	ldr	r0, [r5, #8]
	sub	r3, fp, #180
	ldr	r2, [fp, #-208]
	str	r10, [sp]
	bl	VCTRL_VdmPostProc
	ldr	r2, .L377
	ldr	r3, [r5, #8]
	mov	r1, #0
	str	r1, [r2, r8]
.L351:
	ldr	r2, .L377+4
	cmp	r3, #15
	ldr	r2, [r2, r3, asl #2]
	add	r2, r2, #229376
	str	r1, [r2, #1160]
	str	r1, [r2, #3112]
	addls	r3, r3, #32
	ldrls	r2, .L377
	addls	r3, r2, r3, lsl #2
	strls	r1, [r3, #68]
	b	.L306
.L365:
	ldr	ip, .L377
	mov	r6, #0
	ldr	r0, [r5, #8]
	sub	r3, fp, #180
	str	r10, [sp]
	mov	r1, r6
	ldr	r2, [fp, #-208]
	str	r6, [ip, r8]
	str	r6, [r5, #4]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r5, #8]
	cmp	r3, #15
	bls	.L346
	b	.L306
.L367:
	ldr	r2, [r1, #32]
	cmp	r2, #1
	bne	.L274
	mov	r1, #1744
	ldr	r0, .L377
	mul	r1, r1, r10
	add	r0, r0, r1
	ldr	r0, [r0, #1228]
	cmp	r0, #0
	ble	.L376
	ldr	r2, [r6]
	str	r3, [fp, #-212]
	blx	r2
	ldr	r2, .L377+28
	ldr	r3, [fp, #-212]
	ldr	r7, [r2, #104]
	cmp	r7, #0
	str	r0, [r8, #4]
	beq	.L277
	ldr	r0, [r3, #4]
	mov	r2, r9
	mov	r3, r10
	ldr	r1, [r5, #16]
	blx	r7
	cmp	r0, #0
	bne	.L277
	ldr	r0, .L377+36
	mov	r3, #84
	ldr	r2, [r8, #4]
	mov	r1, r10
	mla	r3, r3, r10, r0
	mov	r0, #2
	str	r2, [r3, #4]
	bl	VDMDRV_StartRepair
	mov	r0, #7
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L247
	ldr	r3, [r6]
	blx	r3
	ldr	r2, [r5, #8]
	ldr	r1, .L377+40
	mov	r3, r2, asl #2
	mov	ip, r0
	ldr	r0, .L377
	add	lr, r0, r3
	ldr	r0, [r1]
	ldr	r1, [lr, #2376]
	rsb	r1, r1, ip
	cmp	r1, r0
	bls	.L247
	add	r3, r4, r3
	add	r2, r10, r2, lsl #24
	add	r2, r2, #458752
	movw	r1, #1225
	ldr	r0, .L377+44
	str	ip, [r3, #2376]
	bl	DBG_AddTrace
	b	.L247
.L370:
	bl	VDMDRV_IsMpeg4NvopCopy.part.3
	cmp	r0, #1
	beq	.L300
	ldr	r3, [fp, #-204]
	ldr	r2, [fp, #-200]
	rsb	r5, r2, r3
	add	r5, r4, r5
	add	r6, r5, #8
	ldr	r1, [r5, #16]
	ldr	r0, [r6, #4]
	cmp	r1, #0
	bne	.L295
	bl	VDMDRV_IsVc1SkpicCopy.part.4
	cmp	r0, #1
	beq	.L300
	ldr	r0, [r6, #4]
	ldr	r1, [r5, #16]
	b	.L299
.L376:
	ldr	r9, .L377
	add	r1, r9, r1
	ldr	r1, [r1, #2100]
	cmp	r1, #0
	ble	.L274
	ldr	r1, [r7]
	mov	r7, r6
	str	r2, [fp, #-216]
	str	r3, [fp, #-212]
	blx	r1
	ldr	r1, .L377+28
	ldr	r3, [fp, #-212]
	ldr	r2, [fp, #-216]
	ldr	r6, [r1, #104]
	cmp	r6, #0
	str	r0, [r8, #4]
	beq	.L277
	ldr	r0, [r3, #4]
	mov	r3, r10
	ldr	r1, [r5, #16]
	blx	r6
	cmp	r0, #0
	bne	.L277
	ldr	r0, .L377+36
	mov	r3, #84
	ldr	r2, [r8, #4]
	mov	r1, r10
	mla	r3, r3, r10, r0
	mov	r0, #3
	str	r2, [r3, #4]
	bl	VDMDRV_StartRepair
	mov	r0, #7
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	beq	.L247
	ldr	r3, [r7]
	blx	r3
	ldr	r3, [r5, #8]
	ldr	r2, .L377+40
	add	lr, r9, r3, lsl #2
	ldr	r1, [r2]
	ldr	r2, [lr, #2376]
	rsb	r2, r2, r0
	mov	ip, r0
	cmp	r2, r1
	bls	.L247
	add	r2, r10, r3, lsl #24
	movw	r1, #1259
	add	r2, r2, #458752
	ldr	r0, .L377+44
	str	ip, [lr, #2376]
	bl	DBG_AddTrace
	b	.L247
.L374:
	ldr	r0, [r5, #8]
	sub	r3, fp, #180
	str	r10, [sp]
	ldr	r2, [fp, #-208]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r5, #8]
	mov	r1, #0
	b	.L351
.L375:
	ldr	r0, [r5, #8]
	sub	r3, fp, #180
	str	r10, [sp]
	ldr	r2, [fp, #-208]
	bl	VCTRL_VdmPostProc
	b	.L247
.L378:
	.align	2
.L377:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	.LC18
	.word	g_event_report
	.word	.LC17
	.word	g_vdm_hal_fun_ptr
	.word	.LC16
	.word	g_VfmwGlobalStat
	.word	g_TraceFramePeriod
	.word	.LANCHOR1+64
	.word	.LC15
	UNWIND(.fnend)
	.size	VDMDRV_AfterDec, .-VDMDRV_AfterDec
	.align	2
	.global	VDMDRV_CheckDevice
	.type	VDMDRV_CheckDevice, %function
VDMDRV_CheckDevice:
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
	ldr	r4, .L433
	mov	r6, r0, asl #3
	mov	r7, r0, asl #6
	rsb	r5, r6, r7
	mov	r8, r0
	add	r9, r4, r5
	ldr	r0, [r9, #8]
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L427
.L381:
	rsb	r3, r6, r7
	add	r5, r4, r3
	ldr	r3, [r4, r3]
	cmp	r3, #0
	bne	.L428
.L382:
	rsb	r9, r6, r7
	ldr	r3, .L433
	add	r9, r4, r9
	ldr	r5, [r9, #28]
	cmp	r5, #1
	beq	.L429
	add	r8, r3, r8, lsl #2
	ldr	r5, [r8, #56]
	cmp	r5, #0
	beq	.L406
	cmp	r5, #1
	moveq	r3, #2
	streq	r3, [r8, #56]
	beq	.L423
.L388:
	mov	r5, #1
.L430:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L428:
	ldr	r10, .L433+4
	ldr	r3, [r10]
	blx	r3
	add	r1, r5, #16
	ldr	r2, [r1, #4]
	str	r0, [r5, #24]
	cmp	r0, r2
	bcc	.L386
	clz	r3, r2
	rsb	r2, r2, r0
	mov	r3, r3, lsr #5
	orrs	r3, r3, r2, lsr #31
	bne	.L386
	cmp	r2, #500
	bls	.L388
	ldr	r9, [r10, #68]
	mov	r0, #1
	ldr	r1, .L433+8
	str	r3, [fp, #-48]
	blx	r9
	ldr	r2, .L433+12
	ldr	r9, [r2]
	cmp	r9, #0
	beq	.L391
	ldr	r3, [fp, #-48]
	mov	r1, #101
	ldr	r0, [r5, #8]
	mov	r2, r3
	blx	r9
.L391:
	ldr	r3, .L433+16
	ldr	r3, [r3, #56]
	cmp	r3, #0
	beq	.L392
	mov	r0, r8
	blx	r3
.L393:
	rsb	r6, r6, r7
	mov	r5, #1
	add	r4, r4, r6
	ldr	r0, .L433
	ldr	r3, [r4, #44]
	str	r5, [r4, #36]
	cmp	r3, r5
	bne	.L394
	ldr	ip, [r4, #8]
	mov	r3, #0
	str	r3, [r4, #44]
	cmp	ip, #15
	str	r3, [r0, r6]
	str	r3, [r4, #36]
	bls	.L395
.L406:
	mov	r5, #0
.L423:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L386:
	str	r0, [r1, #4]
	mov	r5, #1
	b	.L430
.L429:
	ldr	r3, [r9, #40]
	ldr	r10, .L433+4
	cmp	r3, #0
	beq	.L431
.L397:
	rsb	r9, r6, r7
	mov	r2, #0
	add	r9, r4, r9
	str	r2, [fp, #-52]
	add	r3, r9, #16
	str	r3, [fp, #-56]
	ldr	r0, [r9, #8]
	add	r3, r9, #8
	str	r2, [r9, #16]
	str	r3, [fp, #-48]
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	str	r0, [r9, #16]
	beq	.L398
	ldr	r2, [fp, #-52]
	ldr	r0, [r9, #8]
	str	r2, [r9, #40]
	bl	VCTRL_GetVidStd
	ldr	r3, .L433+16
	ldr	r2, [fp, #-48]
	ldr	r3, [r3, #92]
	cmp	r3, #0
	str	r0, [r2, #4]
	beq	.L402
	mov	r2, r8
	ldr	r1, [r9, #16]
	blx	r3
	cmp	r0, #0
	beq	.L432
.L402:
	rsb	r6, r6, r7
	ldr	r3, [r10, #68]
	mov	r0, #0
	add	r10, r4, r6
	mov	r9, r0
	ldr	r1, .L433+20
	blx	r3
	str	r8, [sp]
	mov	r3, r9
	str	r9, [r4, r6]
	mov	r1, r9
	ldr	r0, [r10, #8]
	mov	r2, #15
	str	r9, [r10, #4]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r10, #8]
	ldr	r4, .L433
	cmp	r3, #15
	bhi	.L388
	add	r3, r3, #32
	add	r3, r4, r3, lsl #2
	str	r9, [r3, #68]
	b	.L423
.L427:
	ldr	r2, [r4, r5]
	cmp	r2, #0
	beq	.L382
	ldr	r3, .L433+16
	ldr	r3, [r3, #100]
	cmp	r3, #0
	beq	.L383
	mov	r0, r8
	blx	r3
	cmp	r0, #0
	movne	r3, #1
	ldreq	r2, [r4, r5]
	strne	r3, [r9, #44]
	bne	.L381
.L383:
	rsb	r5, r6, r7
	ldr	r10, .L433+4
	add	r5, r4, r5
	mov	r9, #0
	movw	r1, #1449
	ldr	r0, .L433+24
	str	r9, [r5, #44]
	bl	DBG_AddTrace
	ldr	r3, [r10, #48]
	mov	r2, #56
	mov	r0, r5
	mov	r1, r9
	blx	r3
	ldr	r3, [r5, #8]
	ldr	r2, .L433
	cmp	r3, #15
	addls	r3, r3, #32
	addls	r3, r2, r3, lsl #2
	strls	r9, [r3, #68]
	b	.L381
.L431:
	ldr	r3, [r10]
	blx	r3
	str	r0, [r9, #40]
	b	.L397
.L395:
	add	ip, ip, #32
	mov	r5, r3
	add	r0, r0, ip, lsl #2
	str	r3, [r0, #68]
	b	.L423
.L394:
	mov	r0, r8
	bl	VDMDRV_AfterDec
	b	.L423
.L432:
	ldr	r3, [r10]
	blx	r3
	ldr	r1, .L433+28
	mov	r3, #84
	mla	r3, r3, r8, r1
	mov	r2, r0
	ldr	r0, [fp, #-56]
	str	r2, [r3, #4]
	str	r2, [r0, #4]
	mov	r0, r8
	bl	VDMDRV_StartDec
	ldr	r0, [r9, #8]
	cmp	r0, #15
	bhi	.L388
	ldr	r3, .L433
	add	r8, r8, #1
	add	r3, r3, r0, lsl #2
	str	r8, [r3, #196]
	bl	VDMDRV_AdjustPriorityAfterDec
	b	.L423
.L398:
	ldr	r3, [r10, #68]
	ldr	r1, .L433+32
	blx	r3
	ldr	r3, [r10]
	blx	r3
	ldr	r3, [r9, #40]
	cmp	r0, r3
	rsbcc	r3, r0, r3
	rsbcs	r3, r3, r0
	mvncc	r3, r3
	cmp	r3, #200
	bls	.L388
	rsb	r6, r6, r7
	ldr	r3, [r10, #68]
	add	r7, r4, r6
	mov	r0, #0
	ldr	r1, .L433+36
	mov	r9, r0
	blx	r3
	mov	ip, #100
	str	r8, [sp]
	mov	r3, r9
	mov	r2, #15
	mov	r1, ip
	ldr	r0, [r7, #8]
	str	r9, [r4, r6]
	str	r9, [r7, #40]
	str	ip, [r7, #4]
	bl	VCTRL_VdmPostProc
	ldr	r3, [r7, #8]
	ldr	r2, .L433
	cmp	r3, #15
	bhi	.L388
	add	r3, r3, #32
	add	r3, r2, r3, lsl #2
	str	r9, [r3, #68]
	b	.L423
.L392:
	ldr	r5, [r10, #68]
	mov	r0, r3
	movw	r2, #1492
	ldr	r1, .L433+40
	blx	r5
	b	.L393
.L434:
	.align	2
.L433:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	.word	g_event_report
	.word	g_vdm_hal_fun_ptr
	.word	.LC20
	.word	.LANCHOR1+80
	.word	g_VfmwGlobalStat
	.word	.LC21
	.word	.LC22
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_CheckDevice, .-VDMDRV_CheckDevice
	.align	2
	.global	VDMDRV_WakeUpVdm
	.type	VDMDRV_WakeUpVdm, %function
VDMDRV_WakeUpVdm:
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
	bl	VDMDRV_CheckDevice
	cmp	r0, #0
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDMDRV_ActivateVDH
	UNWIND(.fnend)
	.size	VDMDRV_WakeUpVdm, .-VDMDRV_WakeUpVdm
	.global	__aeabi_uidiv
	.align	2
	.global	VDMDRV_VdmIntServProc
	.type	VDMDRV_VdmIntServProc, %function
VDMDRV_VdmIntServProc:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
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
	subs	r4, r0, #0
	mov	r3, #15
	str	r3, [fp, #-56]
	bgt	.L492
	mov	r10, r4, asl #3
	mov	r6, r4, asl #6
	ldr	r5, .L503
	rsb	r3, r10, r6
	ldr	r2, .L503+4
	mov	r0, #0
	add	r3, r5, r3
	ldr	r9, .L503+8
	ldr	r8, .L503+12
	ldr	r3, [r3, #8]
	ldr	r7, [r2, r3, asl #2]
	ldr	r3, [r9, #12]
	cmp	r7, #0
	ldrne	r7, [r7, #1232]
	blx	r3
	ldr	r3, [r8, #80]
	cmp	r3, #0
	beq	.L477
	mov	r1, r4
	mov	r0, #2
	blx	r3
	ldr	r3, [r8, #80]
	cmp	r3, #0
	str	r0, [fp, #-64]
	moveq	r0, r3
	beq	.L441
	mov	r1, r4
	mov	r0, #1
	blx	r3
	ldr	r2, [r8, #80]
	cmp	r2, #0
	mov	r3, r0
	moveq	r0, r2
	beq	.L441
	mov	r1, r4
	mov	r0, #3
	str	r3, [fp, #-68]
	blx	r2
	ldr	r3, [fp, #-68]
.L441:
	cmp	r7, #1
	beq	.L493
	ldr	r2, [fp, #-64]
	tst	r2, #1
	bne	.L445
	tst	r3, #131072
	beq	.L446
	tst	r0, #1
	bne	.L437
.L446:
	ldr	r3, [r9, #16]
	mov	r0, #0
	blx	r3
	rsb	r6, r10, r6
	mov	r3, #0
	str	r3, [r5, r6]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L492:
	ldr	r1, .L503+8
	mov	r0, #0
	mov	r3, r4
	str	r0, [sp]
	ldr	r2, .L503+16
	ldr	r4, [r1, #68]
	ldr	r1, .L503+20
	blx	r4
.L437:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L493:
	ldr	r3, [fp, #-64]
	ands	r2, r3, #5
	beq	.L494
	ldr	r3, [r8, #80]
	cmp	r3, #0
	beq	.L445
	mov	r0, r7
	mov	r1, r4
	blx	r3
	and	r0, r0, #655360
	cmp	r0, #655360
	beq	.L450
	cmp	r0, #524288
	beq	.L495
	cmp	r0, #131072
	bne	.L445
	rsb	r3, r10, r6
	add	r3, r5, r3
	add	r3, r3, #48
	ldr	r2, [r3, #4]
	cmp	r2, #2
	beq	.L496
.L450:
	rsb	r3, r10, r6
	mov	r2, #1
	add	r3, r5, r3
	str	r2, [r3, #52]
.L445:
	mov	r3, r4, asl #2
	mov	r1, #1
	add	r2, r5, r3
	str	r3, [fp, #-64]
	sub	r0, fp, #52
	ldr	r3, [r9, #48]
	str	r1, [r2, #2440]
	mov	r2, #8
	mov	r1, #0
	ldr	r7, .L503+8
	blx	r3
	ldr	r2, [r8, #112]
	sub	r3, fp, #56
	str	r4, [fp, #-48]
	cmp	r2, #0
	str	r3, [fp, #-52]
	beq	.L451
	sub	r0, fp, #52
	blx	r2
.L452:
	ldr	r3, [r8, #68]
	cmp	r3, #0
	beq	.L453
	mov	r0, r4
	blx	r3
.L454:
	mov	r0, #6
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L497
.L456:
	rsb	r2, r10, r6
	ldr	r3, .L503
	add	r2, r5, r2
	add	r1, r2, #40
	ldr	r0, [r2, #44]
	cmp	r0, #1
	beq	.L498
	mov	r8, #84
	mov	r1, #180
	mul	r2, r8, r4
	ldr	r7, .L503+24
	mla	r1, r1, r4, r3
	ldr	r0, [fp, #-64]
	add	r8, r7, r2
	add	r3, r3, r0
	ldr	r0, [r8, #4]
	str	r2, [fp, #-68]
	ldr	r1, [r1, #2220]
	cmp	r0, #0
	ldr	r2, [r3, #2508]
	add	r2, r2, r1
	str	r2, [r3, #2508]
	bne	.L499
.L463:
	rsb	r3, r10, r6
	add	r7, r5, r3
	ldr	r2, [r5, r3]
	cmp	r2, #0
	beq	.L467
	ldr	r8, [r7, #16]
	cmp	r8, #0
	beq	.L500
.L467:
	rsb	r7, r10, r6
	ldr	r8, .L503
	add	r7, r5, r7
	ldr	r0, [r7, #8]
	bl	VCTRL_IsChanActive
	cmp	r0, #0
	bne	.L501
	ldr	r0, [r7, #8]
	bl	VCTRL_GetDecParam
	subs	r3, r0, #0
	str	r3, [fp, #-68]
	beq	.L502
	mov	r0, r4
	bl	VDMDRV_AfterDec
.L473:
	ldr	r3, [fp, #-64]
	rsb	r6, r10, r6
	mov	r2, #0
	add	r3, r5, r3
	add	r5, r5, r6
	ldr	r0, [r5, #8]
	str	r2, [r3, #2440]
	bl	VCTRL_InformVdmFree
.L461:
	ldr	r3, [r9, #16]
	mov	r0, #0
	blx	r3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L477:
	str	r3, [fp, #-64]
	mov	r0, r3
	b	.L441
.L501:
	movw	r2, #1815
	ldr	r3, [r7, #8]
	ldr	r4, [r9, #68]
	mov	r0, #0
	ldr	r1, .L503+28
	blx	r4
	ldr	r3, [r7, #8]
	cmp	r3, #15
	addls	r3, r3, #32
	movls	r2, #0
	addls	r8, r8, r3, lsl #2
	strls	r2, [r8, #68]
.L472:
	rsb	r3, r10, r6
	mov	r2, #0
	str	r2, [r5, r3]
	b	.L473
.L499:
	ldr	r3, [r9]
	blx	r3
	ldr	r3, [fp, #-68]
	mov	lr, #84
	mul	lr, lr, r4
	ldr	ip, [r7, r3]
	ldr	r3, [r8, #4]
	add	r2, ip, #49920
	add	r2, r2, #80
	cmp	r2, r3
	str	lr, [fp, #-72]
	ldrcc	r1, [fp, #-68]
	movcc	ip, r3
	ldrcs	r2, [r8, #8]
	movcc	r2, #0
	strcc	r3, [r7, r1]
	mov	r1, #180
	mla	r1, r1, r4, r5
	add	r7, r7, lr
	rsb	ip, ip, r0
	str	ip, [fp, #-68]
	ldr	lr, [r7, #52]
	cmp	ip, #1000
	ldr	ip, [r7, #48]
	rsb	r0, r3, r0
	add	r0, r0, r2
	add	r3, r7, #48
	ldr	r8, [r1, #2220]
	add	r2, r7, #8
	add	ip, ip, #1
	str	r2, [fp, #-76]
	str	r0, [r7, #8]
	mov	r2, #0
	add	r8, lr, r8, lsr #10
	str	ip, [r7, #48]
	str	r2, [r7, #4]
	str	r8, [r7, #52]
	bcc	.L463
	mov	ip, #1000
	ldr	r1, [fp, #-68]
	mul	r0, ip, r0
	str	r3, [fp, #-84]
	str	r2, [fp, #-80]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-68]
	ldr	r2, [fp, #-80]
	ldr	r1, .L503+24
	str	r3, [r7, #60]
	ldr	r3, [fp, #-84]
	ldr	ip, [fp, #-72]
	str	r8, [r7, #56]
	str	r2, [r3, #4]
	ldr	r3, [fp, #-76]
	str	r2, [r1, ip]
	str	r2, [r7, #48]
	str	r0, [r3, #4]
	b	.L463
.L497:
	ldr	r3, [r9]
	blx	r3
	rsb	r3, r10, r6
	add	r3, r5, r3
	ldr	r1, .L503+32
	ldr	r2, [r3, #8]
	ldr	r1, [r1]
	add	ip, r5, r2, lsl #2
	ldr	r3, [ip, #2444]
	rsb	r3, r3, r0
	cmp	r3, r1
	bls	.L456
	add	r2, r4, r2, lsl #24
	str	r0, [ip, #2444]
	movw	r1, #1742
	add	r2, r2, #393216
	ldr	r0, .L503+36
	bl	DBG_AddTrace
	b	.L456
.L498:
	ldr	r2, [r2, #8]
	mov	r0, #0
	str	r0, [r1, #4]
	cmp	r2, #15
	addls	r2, r2, #32
	addls	r3, r3, r2, lsl #2
	strls	r0, [r3, #68]
.L460:
	rsb	r6, r10, r6
	mov	r3, #0
	str	r3, [r5, r6]
	b	.L461
.L453:
	mov	r0, r3
	mov	r2, #1728
	ldr	r3, [r9, #68]
	ldr	r1, .L503+40
	blx	r3
	b	.L454
.L451:
	ldr	r3, [r7, #68]
	mov	r0, r2
	ldr	r1, .L503+40
	movw	r2, #1726
	blx	r3
	b	.L452
.L495:
	rsb	r3, r10, r6
	mov	r2, #2
	add	r3, r5, r3
	str	r2, [r3, #52]
	b	.L445
.L500:
	ldr	r3, [r9, #68]
	mov	r0, r8
	ldr	r1, .L503+44
	blx	r3
	ldr	r0, [r7, #8]
	bl	VCTRL_GetDecParam
	cmp	r0, #0
	beq	.L468
	ldr	r0, [r7, #8]
	mov	r3, r8
	ldr	r2, [fp, #-56]
	mov	r1, #100
	str	r4, [sp]
	bl	VCTRL_VdmPostProc
.L468:
	rsb	r3, r10, r6
	ldr	r2, .L503
	add	r3, r5, r3
	ldr	r3, [r3, #8]
	cmp	r3, #15
	addls	r3, r3, #32
	movls	r1, #0
	addls	r3, r2, r3, lsl #2
	strls	r1, [r3, #68]
	b	.L460
.L494:
	mov	r0, r2
	ldr	r3, [r9, #16]
	str	r2, [fp, #-64]
	blx	r3
	ldr	r2, [fp, #-64]
	rsb	r6, r10, r6
	str	r2, [r5, r6]
	b	.L437
.L502:
	ldr	r3, [r7, #8]
	movw	r2, #1825
	ldr	r4, [r9, #68]
	ldr	r1, .L503+48
	blx	r4
	ldr	r3, [r7, #8]
	cmp	r3, #15
	addls	r8, r8, r3, lsl #2
	ldrls	r3, [fp, #-68]
	strls	r3, [r8, #196]
	b	.L472
.L496:
	mov	r2, #3
	str	r2, [r3, #4]
	b	.L445
.L504:
	.align	2
.L503:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_vdm_hal_fun_ptr
	.word	.LANCHOR1+100
	.word	.LC23
	.word	g_VfmwGlobalStat
	.word	.LC25
	.word	g_TraceFramePeriod
	.word	.LANCHOR1+124
	.word	.LC3
	.word	.LC24
	.word	.LC26
	UNWIND(.fnend)
	.size	VDMDRV_VdmIntServProc, .-VDMDRV_VdmIntServProc
	.align	2
	.global	VDMDRV_ResetVDH
	.type	VDMDRV_ResetVDH, %function
VDMDRV_ResetVDH:
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
	ldr	r4, .L509
	ldr	r3, [r4, #8]
	cmp	r3, r0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L509+4
	ldr	r3, [r3, #56]
	cmp	r3, #0
	beq	.L507
	mov	r0, #0
	blx	r3
.L508:
	mov	r3, #0
	str	r3, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L507:
	ldr	ip, .L509+8
	mov	r0, r3
	movw	r2, #2074
	ldr	r1, .L509+12
	ldr	r3, [ip, #68]
	blx	r3
	b	.L508
.L510:
	.align	2
.L509:
	.word	.LANCHOR0
	.word	g_vdm_hal_fun_ptr
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	UNWIND(.fnend)
	.size	VDMDRV_ResetVDH, .-VDMDRV_ResetVDH
	.align	2
	.global	VDMDRV_MarkReloadDsp
	.type	VDMDRV_MarkReloadDsp, %function
VDMDRV_MarkReloadDsp:
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
	subs	ip, r0, #0
	bne	.L511
	add	r3, r1, #1
	cmp	r3, #16
	bhi	.L511
	ldr	r3, .L518
	cmn	r1, #1
	mov	r2, #1
	str	r2, [r3, #48]
	beq	.L511
	ldr	lr, .L518+4
	mvn	r6, #0
	ldr	r4, .L518+8
	movw	r3, #2103
	ldr	r2, .L518+12
	mov	r0, #22
	ldr	r5, [lr, r1, asl #2]
	ldr	r1, .L518+16
	str	r6, [r5, #32]
	ldr	lr, [lr]
	ldr	r4, [r4, #68]
	ldr	lr, [lr, #32]
	stmia	sp, {ip, lr}
	blx	r4
.L511:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L519:
	.align	2
.L518:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+148
	.word	.LC27
	UNWIND(.fnend)
	.size	VDMDRV_MarkReloadDsp, .-VDMDRV_MarkReloadDsp
	.align	2
	.global	VDMDRV_UpdateMatchMode
	.type	VDMDRV_UpdateMatchMode, %function
VDMDRV_UpdateMatchMode:
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
	cmp	r0, #0
	mov	ip, r1
	bne	.L520
	cmp	r1, #15
	bls	.L522
.L520:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L522:
	ldr	lr, .L523
	mov	r6, #1
	ldr	r4, .L523+4
	movw	r3, #2116
	ldr	r2, .L523+8
	mov	r0, #22
	ldr	r5, [lr, r1, asl #2]
	ldr	r1, .L523+12
	str	r6, [r5, #32]
	ldr	lr, [lr, ip, asl #2]
	str	ip, [sp, #4]
	ldr	r4, [r4, #68]
	ldr	ip, [lr, #32]
	str	ip, [sp]
	blx	r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L524:
	.align	2
.L523:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1+172
	.word	.LC28
	UNWIND(.fnend)
	.size	VDMDRV_UpdateMatchMode, .-VDMDRV_UpdateMatchMode
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
	.global	CapItem
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.13285, %object
	.size	__func__.13285, 23
__func__.13285:
	.ascii	"VDMDRV_CheckAttachMode\000"
	.space	1
	.type	__func__.13290, %object
	.size	__func__.13290, 19
__func__.13290:
	.ascii	"VDMDRV_ChnDecReady\000"
	.space	1
	.type	__FUNCTION__.13306, %object
	.size	__FUNCTION__.13306, 19
__FUNCTION__.13306:
	.ascii	"VDMDRV_DoBeforeDec\000"
	.space	1
	.type	__FUNCTION__.13341, %object
	.size	__FUNCTION__.13341, 16
__FUNCTION__.13341:
	.ascii	"VDMDRV_AfterDec\000"
	.type	__FUNCTION__.13360, %object
	.size	__FUNCTION__.13360, 19
__FUNCTION__.13360:
	.ascii	"VDMDRV_CheckDevice\000"
	.space	1
	.type	__func__.13378, %object
	.size	__func__.13378, 22
__func__.13378:
	.ascii	"VDMDRV_VdmIntServProc\000"
	.space	2
	.type	__FUNCTION__.13379, %object
	.size	__FUNCTION__.13379, 22
__FUNCTION__.13379:
	.ascii	"VDMDRV_VdmIntServProc\000"
	.space	2
	.type	__func__.13453, %object
	.size	__func__.13453, 21
__func__.13453:
	.ascii	"VDMDRV_MarkReloadDsp\000"
	.space	3
	.type	__func__.13458, %object
	.size	__func__.13458, 23
__func__.13458:
	.ascii	"VDMDRV_UpdateMatchMode\000"
	.data
	.align	2
	.type	USE_FF_APT_EN, %object
	.size	USE_FF_APT_EN, 4
USE_FF_APT_EN:
	.word	1
	.type	CapItem, %object
	.size	CapItem, 924
CapItem:
	.word	176
	.word	144
	.word	4
	.word	10
	.word	11
	.word	12
	.word	524288
	.word	352
	.word	288
	.word	4
	.word	10
	.word	11
	.word	12
	.word	786432
	.word	720
	.word	576
	.word	4
	.word	10
	.word	11
	.word	12
	.word	1048576
	.word	1280
	.word	736
	.word	4
	.word	10
	.word	11
	.word	12
	.word	2097152
	.word	1920
	.word	1088
	.word	4
	.word	10
	.word	11
	.word	12
	.word	3145728
	.word	176
	.word	144
	.word	15
	.word	19
	.word	22
	.word	24
	.word	524288
	.word	352
	.word	288
	.word	15
	.word	19
	.word	22
	.word	24
	.word	786432
	.word	720
	.word	576
	.word	9
	.word	15
	.word	16
	.word	17
	.word	1048576
	.word	1280
	.word	736
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1920
	.word	1088
	.word	6
	.word	13
	.word	13
	.word	13
	.word	2097152
	.word	5632
	.word	4224
	.word	1
	.word	3
	.word	3
	.word	3
	.word	16777216
	.word	1280
	.word	800
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	800
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1488
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	14
	.word	3145728
	.word	1280
	.word	1488
	.word	6
	.word	13
	.word	13
	.word	14
	.word	3145728
	.word	2160
	.word	1280
	.word	6
	.word	13
	.word	13
	.word	13
	.word	3145728
	.word	1280
	.word	2176
	.word	6
	.word	13
	.word	13
	.word	13
	.word	3145728
	.word	2160
	.word	2176
	.word	4
	.word	11
	.word	11
	.word	11
	.word	4194304
	.word	4096
	.word	2304
	.word	2
	.word	9
	.word	9
	.word	9
	.word	5242880
	.word	2304
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	5242880
	.word	4096
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	8388608
	.word	8192
	.word	4096
	.word	2
	.word	9
	.word	9
	.word	9
	.word	10485760
	.word	4096
	.word	8192
	.word	2
	.word	9
	.word	9
	.word	9
	.word	10485760
	.word	8192
	.word	8192
	.word	1
	.word	3
	.word	3
	.word	3
	.word	20971520
	.word	1920
	.word	1088
	.word	1
	.word	3
	.word	3
	.word	3
	.word	2097152
	.word	1920
	.word	1088
	.word	1
	.word	3
	.word	3
	.word	3
	.word	2097152
	.word	1920
	.word	1088
	.word	17
	.word	26
	.word	26
	.word	26
	.word	2097152
	.word	192
	.word	192
	.word	15
	.word	19
	.word	22
	.word	24
	.word	524288
	.word	384
	.word	320
	.word	15
	.word	19
	.word	22
	.word	24
	.word	786432
	.word	768
	.word	576
	.word	9
	.word	15
	.word	16
	.word	17
	.word	1048576
	.word	1280
	.word	768
	.word	6
	.word	13
	.word	13
	.word	14
	.word	2097152
	.word	1920
	.word	1088
	.word	6
	.word	13
	.word	13
	.word	13
	.word	2097152
	.word	4096
	.word	2304
	.word	4
	.word	4
	.word	4
	.word	4
	.word	16777216
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"VDMHAL_V200_IsMpeg4NvopCopy point of picture para n" )
	ASCII(.ascii	"ull, wait forever!!!\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"VDMDRV_IsVc1SkpicCopy point of picture para null, w" )
	ASCII(.ascii	"ait forever!!!\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"====== forece VDM sleep! ======\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"%s,%d,  frameRate = %d,last = %d\012\000" )
	.space	2
.LC5:
	ASCII(.ascii	"%s,%d, the frameRate change!\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"%s,%d,chanid = %d,s32Is4k60fpsb = %d\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"%s The channel %d is not active\012\000" )
	.space	3
.LC8:
	ASCII(.ascii	"The channel %d is decoding\012\000" )
.LC9:
	ASCII(.ascii	"The channel %d DEC PARAM is not ready\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"VDMDRV_IsVp6NvopCopy point of picture para null, wa" )
	ASCII(.ascii	"it forever!!!\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"The channel %d DEC PARAM is not ready(pDecParam == " )
	ASCII(.ascii	"NULL)\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"---SKIP REPAIR!---\012\000" )
.LC13:
	ASCII(.ascii	"VDM Start Fail 2 !\012\000" )
.LC14:
	ASCII(.ascii	"isr begin: *pVdmStateMachine = %d, timeout = %d, Er" )
	ASCII(.ascii	"rRatio = %d\012\000" )
.LC15:
	ASCII(.ascii	"ISR process vdm timeout!\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"Chan %d: Current frame:%d  ErrRatio = %d\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"*pH264NeedMoreStart, *pH264FinishedMultiStart = %d," )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"*****VdmStateMachine=%d, *pChanId=%d Error!\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"VDM Time Out(%d ms), Reset VDM!\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"VDM Start Fail 1 !\012\000" )
.LC21:
	ASCII(.ascii	"h264 more start need parameter\012\000" )
.LC22:
	ASCII(.ascii	"wait more start time out!\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC24:
	ASCII(.ascii	"vdm state machine = %d, but DecParam is null!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"line :%d ISR called but chan %d is not active!\012\000" )
.LC26:
	ASCII(.ascii	"lline: %d ISR called but chan %d is not active!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC27:
	ASCII(.ascii	"%s,%d, i = %d, MatchVdhIdPlus1 = %d\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"%s,%d, MatchVdhIdPlus1 = %d,chanId = %d\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_VdmDrvParam, %object
	.size	g_VdmDrvParam, 56
g_VdmDrvParam:
	.space	56
	.type	s_eVdmDrvSleepState, %object
	.size	s_eVdmDrvSleepState, 4
s_eVdmDrvSleepState:
	.space	4
	.type	g_DspDrvState, %object
	.size	g_DspDrvState, 8
g_DspDrvState:
	.space	8
	.type	g_ChanCtx, %object
	.size	g_ChanCtx, 192
g_ChanCtx:
	.space	192
	.type	g_LastFPS.13282, %object
	.size	g_LastFPS.13282, 64
g_LastFPS.13282:
	.space	64
	.type	DiffFrameCnt.13281, %object
	.size	DiffFrameCnt.13281, 64
DiffFrameCnt.13281:
	.space	64
	.type	g_RepairParam, %object
	.size	g_RepairParam, 1744
g_RepairParam:
	.space	1744
	.type	last_rec_pos_time.13304, %object
	.size	last_rec_pos_time.13304, 64
last_rec_pos_time.13304:
	.space	64
	.type	g_BackUp, %object
	.size	g_BackUp, 180
g_BackUp:
	.space	180
	.type	last_rec_pos_time.13335, %object
	.size	last_rec_pos_time.13335, 64
last_rec_pos_time.13335:
	.space	64
	.type	s_VdmIsInISR, %object
	.size	s_VdmIsInISR, 4
s_VdmIsInISR:
	.space	4
	.type	last_rec_pos_time.13374, %object
	.size	last_rec_pos_time.13374, 64
last_rec_pos_time.13374:
	.space	64
	.type	cycle.13373, %object
	.size	cycle.13373, 4
cycle.13373:
	.space	4
	.type	g_VdmExtParam, %object
	.size	g_VdmExtParam, 140
g_VdmExtParam:
	.space	140
	.type	g_DecReport, %object
	.size	g_DecReport, 816
g_DecReport:
	.space	816
	.type	g_HwMem, %object
	.size	g_HwMem, 1208
g_HwMem:
	.space	1208
	.type	g_UpMsg, %object
	.size	g_UpMsg, 3200
g_UpMsg:
	.space	3200
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
