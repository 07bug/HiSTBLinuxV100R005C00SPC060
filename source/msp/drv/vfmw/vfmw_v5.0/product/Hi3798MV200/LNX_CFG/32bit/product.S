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
	.file	"product.c"
	.text
	.align	2
	.global	VDM_SetClockSkip
	.type	VDM_SetClockSkip, %function
VDM_SetClockSkip:
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
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	bfi	r3, r0, #12, #5
	bfc	r3, #17, #1
	str	r3, [r2, #120]
	orr	r3, r3, #131072
	str	r3, [r2, #120]
	ldmfd	sp, {fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	g_pstRegCrg
	UNWIND(.fnend)
	.size	VDM_SetClockSkip, .-VDM_SetClockSkip
	.align	2
	.global	BPD_OpenHardware
	.type	BPD_OpenHardware, %function
BPD_OpenHardware:
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
	ldr	r2, [r3]
	ldr	r3, [r2, #136]
	orr	r3, r3, #1
	bfc	r3, #4, #1
	str	r3, [r2, #136]
	ldmfd	sp, {fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	g_pstRegCrg
	UNWIND(.fnend)
	.size	BPD_OpenHardware, .-BPD_OpenHardware
	.align	2
	.global	BPD_CloseHardware
	.type	BPD_CloseHardware, %function
BPD_CloseHardware:
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
	ldr	r2, [r3]
	ldr	r3, [r2, #136]
	bic	r3, r3, #17
	orr	r3, r3, #16
	str	r3, [r2, #136]
	ldmfd	sp, {fp, sp, pc}
.L9:
	.align	2
.L8:
	.word	g_pstRegCrg
	UNWIND(.fnend)
	.size	BPD_CloseHardware, .-BPD_CloseHardware
	.align	2
	.global	MMU_OpenHardware
	.type	MMU_OpenHardware, %function
MMU_OpenHardware:
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
	ldr	r6, .L11
	mov	r0, #30
	ldr	r5, .L11+4
	ldr	r3, [r6]
	ldr	r2, [r5, #116]
	ldr	r4, [r3, #828]
	orr	r4, r4, #1
	str	r4, [r3, #828]
	blx	r2
	ldr	r2, [r6]
	bfc	r4, #4, #1
	ldr	r3, [r5, #116]
	mov	r0, #30
	str	r4, [r2, #828]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L12:
	.align	2
.L11:
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MMU_OpenHardware, .-MMU_OpenHardware
	.align	2
	.global	MMU_CloseHardware
	.type	MMU_CloseHardware, %function
MMU_CloseHardware:
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
	.size	MMU_CloseHardware, .-MMU_CloseHardware
	.align	2
	.global	VDM_OpenHardware
	.type	VDM_OpenHardware, %function
VDM_OpenHardware:
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
	subs	r2, r0, #0
	bne	.L15
	ldr	r1, .L18
	mov	r0, #30
	ldr	r3, .L18+4
	ldr	r1, [r1]
	ldr	r4, [r3, #116]
	ldr	r3, [r1, #120]
	orr	r3, r3, #1
	bfi	r3, r2, #4, #1
	bfi	r3, r2, #6, #1
	bfi	r3, r2, #8, #2
	bfi	r3, r2, #12, #5
	bfi	r3, r2, #17, #1
	str	r3, [r1, #120]
	blx	r4
.L16:
	ldr	r3, .L18+8
	movw	r1, #41463
	movt	r1, 1153
	ldr	r0, [r3]
	add	r0, r0, #4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MEM_WritePhyWord
.L15:
	ldr	r1, .L18+12
	mov	r0, #0
	bl	dprint_vfmw
	b	.L16
.L19:
	.align	2
.L18:
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_ScdRegPhyBaseAddr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDM_OpenHardware, .-VDM_OpenHardware
	.align	2
	.global	VDM_CloseHardware
	.type	VDM_CloseHardware, %function
VDM_CloseHardware:
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
	subs	r2, r0, #0
	bne	.L21
	ldr	r3, .L24
	ldr	r5, .L24+4
	ldr	r3, [r3, #84]
	ldr	r2, [r5]
	cmp	r3, #0
	ldr	r4, [r2, #120]
	beq	.L22
	blx	r3
.L23:
	ldr	r2, [r5]
	bfc	r4, #0, #1
	ldr	r3, .L24+8
	mov	r0, #30
	str	r4, [r2, #120]
	ldr	r3, [r3, #116]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L21:
	ldr	r1, .L24+12
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L22:
	mov	r2, #138
	ldr	r1, .L24+16
	bl	dprint_vfmw
	b	.L23
.L25:
	.align	2
.L24:
	.word	g_vdm_hal_fun_ptr
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VDM_CloseHardware, .-VDM_CloseHardware
	.align	2
	.global	DSP_OpenHardware
	.type	DSP_OpenHardware, %function
DSP_OpenHardware:
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
	subs	r2, r0, #0
	beq	.L28
	ldr	r1, .L29
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L28:
	ldr	r2, .L29+4
	mov	r0, #30
	ldr	r3, .L29+8
	ldr	r2, [r2]
	ldr	r1, [r3, #116]
	ldr	r3, [r2, #120]
	orr	r3, r3, #2
	str	r3, [r2, #120]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r1	@ indirect register sibling call
.L30:
	.align	2
.L29:
	.word	.LC3
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	DSP_OpenHardware, .-DSP_OpenHardware
	.align	2
	.global	DSP_CloseHardware
	.type	DSP_CloseHardware, %function
DSP_CloseHardware:
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
	subs	r2, r0, #0
	beq	.L33
	ldr	r1, .L34
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L33:
	ldr	r1, .L34+4
	mov	r0, #30
	ldr	r3, .L34+8
	ldr	r1, [r1]
	ldr	ip, [r3, #116]
	ldr	r3, [r1, #120]
	bfi	r3, r2, #1, #1
	str	r3, [r1, #120]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip	@ indirect register sibling call
.L35:
	.align	2
.L34:
	.word	.LC4
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	DSP_CloseHardware, .-DSP_CloseHardware
	.align	2
	.global	SCD_OpenHardware
	.type	SCD_OpenHardware, %function
SCD_OpenHardware:
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
	subs	r2, r0, #0
	bne	.L37
	ldr	r3, .L40
	ldr	r1, [r3]
	ldr	r3, [r1, #120]
	bfi	r3, r2, #5, #1
	str	r3, [r1, #120]
	ldmfd	sp, {fp, sp, pc}
.L37:
	ldr	r1, .L40+4
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L41:
	.align	2
.L40:
	.word	g_pstRegCrg
	.word	.LC5
	UNWIND(.fnend)
	.size	SCD_OpenHardware, .-SCD_OpenHardware
	.align	2
	.global	SCD_CloseHardware
	.type	SCD_CloseHardware, %function
SCD_CloseHardware:
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
	subs	r2, r0, #0
	bne	.L43
	ldr	r3, .L46
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	orr	r3, r3, #32
	str	r3, [r2, #120]
	ldmfd	sp, {fp, sp, pc}
.L43:
	ldr	r1, .L46+4
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L47:
	.align	2
.L46:
	.word	g_pstRegCrg
	.word	.LC6
	UNWIND(.fnend)
	.size	SCD_CloseHardware, .-SCD_CloseHardware
	.align	2
	.global	VDEC_Lowdelay_Event_Time
	.type	VDEC_Lowdelay_Event_Time, %function
VDEC_Lowdelay_Event_Time:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	sub	r3, fp, #28
	mov	r4, r0
	mov	r0, #0
	str	r0, [r3, #-20]!
	mov	r0, r3
	mov	r6, r1
	mov	r5, r2
	bl	HI_DRV_SYS_GetTimeStampMs
	ldr	r3, .L51
	ldr	r0, [fp, #-48]
	add	r2, r3, r4
	str	r6, [fp, #-44]
	ldr	r3, [r3, r4, asl #2]
	ldrb	r1, [r2, #128]	@ zero_extendqisi2
	str	r5, [fp, #-36]
	cmp	r1, #1
	str	r3, [fp, #-40]
	str	r0, [fp, #-32]
	beq	.L50
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L50:
	sub	r0, fp, #44
	bl	HI_DRV_LD_Notify_Event
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L52:
	.align	2
.L51:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDEC_Lowdelay_Event_Time, .-VDEC_Lowdelay_Event_Time
	.align	2
	.global	PDT_GetOutputFormat
	.type	PDT_GetOutputFormat, %function
PDT_GetOutputFormat:
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
	cmp	r3, #17
	beq	.L54
	ldr	r3, [r0, #4]
	cmp	r3, #1920
	bhi	.L54
	ldr	r3, [r0, #8]
	cmp	r3, #1088
	movls	r3, #0
	strls	r3, [r0, #12]
	ldmlsfd	sp, {fp, sp, pc}
.L54:
	mov	r3, #1
	str	r3, [r0, #12]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	PDT_GetOutputFormat, .-PDT_GetOutputFormat
	.align	2
	.global	PDT_InitHalInterface
	.type	PDT_InitHalInterface, %function
PDT_InitHalInterface:
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
	ldr	r3, .L61
	mov	r2, #168
	mov	r1, #0
	mov	r4, r0
	ldr	r6, .L61+4
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, .L61+8
	ldr	r5, .L61+12
	ldr	lr, .L61+16
	ldr	ip, .L61+20
	ldr	r0, .L61+24
	ldr	r1, .L61+28
	ldr	r2, .L61+32
	str	r3, [r4]
	ldr	r3, .L61+36
	str	r6, [r4, #4]
	str	r5, [r4, #8]
	ldr	r6, .L61+40
	ldr	r5, .L61+44
	str	lr, [r4, #12]
	str	ip, [r4, #16]
	ldr	lr, .L61+48
	ldr	ip, .L61+52
	str	r0, [r4, #20]
	str	r1, [r4, #24]
	ldr	r0, .L61+56
	ldr	r1, .L61+60
	str	r2, [r4, #28]
	str	r3, [r4, #32]
	ldr	r2, .L61+64
	ldr	r3, .L61+68
	str	r6, [r4, #36]
	str	r5, [r4, #40]
	ldr	r6, .L61+72
	ldr	r5, .L61+76
	str	lr, [r4, #48]
	str	ip, [r4, #52]
	ldr	lr, .L61+80
	ldr	ip, .L61+84
	str	r0, [r4, #56]
	str	r1, [r4, #60]
	ldr	r0, .L61+88
	ldr	r1, .L61+92
	str	r2, [r4, #64]
	str	r3, [r4, #76]
	ldr	r2, .L61+96
	ldr	r3, .L61+100
	str	r6, [r4, #164]
	str	r5, [r4, #68]
	ldr	r6, .L61+104
	ldr	r5, .L61+108
	str	lr, [r4, #72]
	str	ip, [r4, #80]
	ldr	lr, .L61+112
	ldr	ip, .L61+116
	str	r0, [r4, #84]
	str	r1, [r4, #88]
	ldr	r0, .L61+120
	ldr	r1, .L61+124
	str	r2, [r4, #92]
	str	r3, [r4, #96]
	ldr	r2, .L61+128
	ldr	r3, .L61+132
	str	r6, [r4, #100]
	str	r5, [r4, #104]
	str	lr, [r4, #108]
	str	ip, [r4, #112]
	str	r0, [r4, #116]
	str	r1, [r4, #120]
	str	r2, [r4, #124]
	ldr	r6, .L61+136
	str	r3, [r4, #128]
	ldr	r5, .L61+140
	ldr	lr, .L61+144
	ldr	ip, .L61+148
	ldr	r0, .L61+152
	ldr	r1, .L61+156
	ldr	r2, .L61+160
	ldr	r3, .L61+164
	str	r6, [r4, #132]
	str	r5, [r4, #136]
	str	lr, [r4, #140]
	str	ip, [r4, #144]
	str	r0, [r4, #44]
	str	r1, [r4, #148]
	str	r2, [r4, #156]
	str	r3, [r4, #160]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L62:
	.align	2
.L61:
	.word	vfmw_Osal_Func_Ptr_S
	.word	VDM_OpenHardware
	.word	VDM_SetClockSkip
	.word	VDM_CloseHardware
	.word	DSP_OpenHardware
	.word	DSP_CloseHardware
	.word	SCD_OpenHardware
	.word	SCD_CloseHardware
	.word	BPD_OpenHardware
	.word	BPD_CloseHardware
	.word	MMU_OpenHardware
	.word	MMU_CloseHardware
	.word	VDMHAL_V5R2C1_GetHalMemSize
	.word	VDMHAL_V5R2C1_CalcFsSize
	.word	VDMHAL_V5R2C1_OpenHAL
	.word	VDMHAL_V5R2C1_CloseHAL
	.word	VDMHAL_V5R2C1_ArrangeMem
	.word	VDMHAL_V5R2C1_ResetVdm
	.word	VDMHAL_V5R2C1_GetRpuSize
	.word	VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.word	VDMHAL_V5R2C1_EnableSmmu
	.word	VDMHAL_V5R2C1_GlbReset
	.word	VDMHAL_V5R2C1_GlbResetX
	.word	VDMHAL_V5R2C1_ClearIntState
	.word	VDMHAL_V5R2C1_ClearMMUIntState
	.word	VDMHAL_V5R2C1_MaskInt
	.word	VDMHAL_V5R2C1_EnableInt
	.word	VDMHAL_V5R2C1_CheckReg
	.word	VDMHAL_V5R2C1_ReadMMUMask
	.word	VDMHAL_V5R2C1_WriteMMUMask
	.word	VDMHAL_V5R2C1_StartHwRepair
	.word	VDMHAL_V5R2C1_StartHwDecode
	.word	VDMHAL_V5R2C1_PrepareDec
	.word	VDMHAL_V5R2C1_IsVdmReady
	.word	VDMHAL_V5R2C1_IsVdmRun
	.word	VDMHAL_V5R2C1_PrepareRepair
	.word	VDMHAL_V5R2C1_MakeDecReport
	.word	VDMHAL_V5R2C1_UpdateHardwareInfo
	.word	VDMHAL_V5R2C1_GetCharacter
	.word	VDMHAL_V5R2C1_WriteBigTitle1DYuv
	.word	VDMHAL_V5R2C1_IsVdhDecOver
	.word	VDMHAL_V5R2C1_IsVdhPartDecOver
	UNWIND(.fnend)
	.size	PDT_InitHalInterface, .-PDT_InitHalInterface
	.align	2
	.global	PDT_GetVdecCapability
	.type	PDT_GetVdecCapability, %function
PDT_GetVdecCapability:
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
	ldr	ip, .L66
	mov	r2, #148
	ldr	r3, .L66+4
	mov	r1, #0
	mov	r4, r0
	ldr	r5, [ip, #160]
	ldr	r3, [r3, #48]
	blx	r3
	mov	r3, #528
	movt	r3, 14232
	cmp	r5, r3
	mov	r3, #0
	mov	r1, #32
	mov	r2, #50
	movt	r3, 6480
	stmia	r4, {r1, r2}
	mov	r2, #2304
	mov	r1, #4096
	str	r2, [r4, #12]
	str	r3, [r4, #16]
	mov	r2, #0
	mov	r3, #2
	str	r2, [r4, #20]
	str	r3, [r4, #28]
	mov	r2, #3
	mov	r3, #6
	str	r1, [r4, #8]
	str	r2, [r4, #24]
	str	r3, [r4, #32]
	beq	.L64
	mov	ip, #8
	mov	r0, #9
	mov	r2, #15
	mov	r3, #16
	mov	r1, #17
	str	ip, [r4, #36]
	str	r0, [r4, #40]
	mov	ip, #1
	mov	r0, #5
	str	ip, [r4, #44]
	str	r0, [r4, #48]
	mov	ip, #10
	mov	r0, #11
	str	ip, [r4, #52]
	str	r0, [r4, #56]
	mov	ip, #12
	mov	r0, #13
	str	r2, [r4, #68]
	str	r3, [r4, #72]
	str	r1, [r4, #76]
	str	ip, [r4, #60]
	str	r0, [r4, #64]
.L65:
	add	r2, r4, r2, lsl #2
	add	r3, r4, r3, lsl #2
	add	r4, r4, r1, lsl #2
	mov	r0, #19
	mov	r1, #20
	str	r0, [r2, #20]
	mov	r2, #22
	str	r1, [r3, #20]
	str	r2, [r4, #20]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L64:
	mov	ip, #1
	mov	r0, #5
	str	ip, [r4, #36]
	mov	r1, #10
	str	r0, [r4, #40]
	mov	ip, #15
	mov	r0, #16
	mov	r3, #9
	mov	r2, #8
	str	ip, [r4, #44]
	str	r0, [r4, #48]
	b	.L65
.L67:
	.align	2
.L66:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	PDT_GetVdecCapability, .-PDT_GetVdecCapability
	.align	2
	.global	PDT_GetAttribute
	.type	PDT_GetAttribute, %function
PDT_GetAttribute:
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
	subs	r4, r0, #0
	beq	.L70
	cmp	r4, #2
	bne	.L80
	ldr	r3, [r1]
	cmp	r3, #17
	beq	.L73
	ldr	r3, [r1, #4]
	cmp	r3, #1920
	bhi	.L73
	ldr	r3, [r1, #8]
	cmp	r3, #1088
	bhi	.L73
	mov	r4, #0
	str	r4, [r1, #12]
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L80:
	mov	r3, r4
	ldr	r2, .L81
	ldr	r1, .L81+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L73:
	mov	r3, #1
	mov	r0, #0
	str	r3, [r1, #12]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L70:
	mov	r0, r1
	bl	PDT_GetVdecCapability
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L82:
	.align	2
.L81:
	.word	.LANCHOR1
	.word	.LC7
	UNWIND(.fnend)
	.size	PDT_GetAttribute, .-PDT_GetAttribute
	.align	2
	.global	PDT_Init
	.type	PDT_Init, %function
PDT_Init:
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
	ldr	r5, .L88
	mov	r2, #16
	ldr	r4, .L88+4
	mov	r6, r0
	mov	r1, #0
	ldr	r3, [r5, #48]
	add	r0, r4, #160
	blx	r3
	mov	r0, #3808
	ldr	r3, [r5, #152]
	mov	r1, #4096
	movt	r0, 63488
	blx	r3
	mov	r1, #4096
	mov	r3, r0
	str	r0, [r4, #168]
	ldr	r2, [r3]
	mov	r0, #2112
	ldr	r3, [r5, #152]
	movt	r0, 63650
	str	r2, [r4, #160]
	blx	r3
	mov	r3, r0
	str	r0, [r4, #172]
	ldr	r3, [r3]
	mov	r0, r6
	str	r3, [r4, #164]
	bl	PDT_InitHalInterface
	ldr	r3, .L88+8
	ldr	r3, [r3, #44]
	cmp	r3, #0
	beq	.L84
	blx	r3
.L84:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L89:
	.align	2
.L88:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	PDT_Init, .-PDT_Init
	.align	2
	.global	PDT_Deinit
	.type	PDT_Deinit, %function
PDT_Deinit:
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
	ldr	r4, .L91
	ldr	r5, .L91+4
	ldr	r0, [r4, #168]
	ldr	r3, [r5, #156]
	blx	r3
	ldr	r0, [r4, #172]
	ldr	r3, [r5, #156]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L92:
	.align	2
.L91:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	PDT_Deinit, .-PDT_Deinit
	.global	g_chipIdentity
	.global	g_LowDelaySeqIndex
	.global	g_LowDelayCalcHandle
	.global	g_LowDelayCalcStat
	.global	g_ChipMaxHeight
	.global	g_ChipMaxWidth
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.53366, %object
	.size	__func__.53366, 17
__func__.53366:
	.ascii	"PDT_GetAttribute\000"
	.data
	.align	2
	.type	g_ChipMaxHeight, %object
	.size	g_ChipMaxHeight, 4
g_ChipMaxHeight:
	.word	8192
	.type	g_ChipMaxWidth, %object
	.size	g_ChipMaxWidth, 4
g_ChipMaxWidth:
	.word	8192
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"VDM_OpenHardware failed, wrong VdhId %d\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"VDM_CloseHardware failed, wrong VdhId %d\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"DSP_OpenHardware failed, wrong VdhId %d\012\000" )
	.space	3
.LC4:
	ASCII(.ascii	"DSP_CloseHardware failed, wrong VdhId %d\012\000" )
	.space	2
.LC5:
	ASCII(.ascii	"SCD_OpenHardware Wrong ScdId %d\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"SCD_CloseHardware Wrong ScdId %d\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"%s unkown eAttrID %d\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	g_LowDelayCalcHandle, %object
	.size	g_LowDelayCalcHandle, 128
g_LowDelayCalcHandle:
	.space	128
	.type	g_LowDelayCalcStat, %object
	.size	g_LowDelayCalcStat, 32
g_LowDelayCalcStat:
	.space	32
	.type	g_chipIdentity, %object
	.size	g_chipIdentity, 16
g_chipIdentity:
	.space	16
	.type	g_LowDelaySeqIndex, %object
	.size	g_LowDelaySeqIndex, 128
g_LowDelaySeqIndex:
	.space	128
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
