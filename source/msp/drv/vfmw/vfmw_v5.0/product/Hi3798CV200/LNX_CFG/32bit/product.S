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
	bne	.L11
	ldr	r1, .L14
	mov	r0, #30
	ldr	r3, .L14+4
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
.L12:
	ldr	r3, .L14+8
	movw	r1, #41463
	movt	r1, 1
	ldr	r0, [r3]
	add	r0, r0, #4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	MEM_WritePhyWord
.L11:
	ldr	r1, .L14+12
	mov	r0, #0
	bl	dprint_vfmw
	b	.L12
.L15:
	.align	2
.L14:
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
	bne	.L17
	ldr	r3, .L20
	ldr	r5, .L20+4
	ldr	r3, [r3, #84]
	ldr	r2, [r5]
	cmp	r3, #0
	ldr	r4, [r2, #120]
	beq	.L18
	blx	r3
.L19:
	ldr	r2, [r5]
	bfc	r4, #0, #1
	ldr	r3, .L20+8
	mov	r0, #30
	str	r4, [r2, #120]
	ldr	r3, [r3, #116]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L17:
	ldr	r1, .L20+12
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L18:
	mov	r2, #118
	ldr	r1, .L20+16
	bl	dprint_vfmw
	b	.L19
.L21:
	.align	2
.L20:
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
	beq	.L24
	ldr	r1, .L25
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L24:
	ldr	r2, .L25+4
	mov	r0, #30
	ldr	r3, .L25+8
	ldr	r2, [r2]
	ldr	r1, [r3, #116]
	ldr	r3, [r2, #120]
	orr	r3, r3, #2
	str	r3, [r2, #120]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r1	@ indirect register sibling call
.L26:
	.align	2
.L25:
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
	beq	.L29
	ldr	r1, .L30
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L29:
	ldr	r1, .L30+4
	mov	r0, #30
	ldr	r3, .L30+8
	ldr	r1, [r1]
	ldr	ip, [r3, #116]
	ldr	r3, [r1, #120]
	bfi	r3, r2, #1, #1
	str	r3, [r1, #120]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip	@ indirect register sibling call
.L31:
	.align	2
.L30:
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
	bne	.L33
	ldr	r3, .L36
	ldr	r1, [r3]
	ldr	r3, [r1, #120]
	bfi	r3, r2, #5, #1
	str	r3, [r1, #120]
	ldmfd	sp, {fp, sp, pc}
.L33:
	ldr	r1, .L36+4
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L37:
	.align	2
.L36:
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
	bne	.L39
	ldr	r3, .L42
	ldr	r2, [r3]
	ldr	r3, [r2, #120]
	orr	r3, r3, #32
	str	r3, [r2, #120]
	ldmfd	sp, {fp, sp, pc}
.L39:
	ldr	r1, .L42+4
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L43:
	.align	2
.L42:
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
	ldr	r3, .L47
	ldr	r0, [fp, #-48]
	add	r2, r3, r4
	str	r6, [fp, #-44]
	ldr	r3, [r3, r4, asl #2]
	ldrb	r1, [r2, #128]	@ zero_extendqisi2
	str	r5, [fp, #-36]
	cmp	r1, #1
	str	r3, [fp, #-40]
	str	r0, [fp, #-32]
	beq	.L46
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L46:
	sub	r0, fp, #44
	bl	HI_DRV_LD_Notify_Event
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L48:
	.align	2
.L47:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VDEC_Lowdelay_Event_Time, .-VDEC_Lowdelay_Event_Time
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
	ldr	r3, .L50
	mov	r2, #168
	mov	r1, #0
	mov	r4, r0
	ldr	r5, .L50+4
	ldr	r3, [r3, #48]
	blx	r3
	ldr	lr, .L50+8
	ldr	ip, .L50+12
	ldr	r0, .L50+16
	ldr	r1, .L50+20
	ldr	r2, .L50+24
	ldr	r3, .L50+28
	ldr	r6, .L50+32
	str	r5, [r4]
	str	lr, [r4, #4]
	ldr	r5, .L50+36
	ldr	lr, .L50+40
	str	ip, [r4, #8]
	str	r0, [r4, #12]
	ldr	ip, .L50+44
	ldr	r0, .L50+48
	str	r1, [r4, #16]
	str	r2, [r4, #20]
	ldr	r1, .L50+52
	ldr	r2, .L50+56
	str	r3, [r4, #24]
	ldr	r3, .L50+60
	str	r6, [r4, #28]
	str	r5, [r4, #32]
	ldr	r6, .L50+64
	ldr	r5, .L50+68
	str	lr, [r4, #48]
	str	ip, [r4, #52]
	ldr	lr, .L50+72
	ldr	ip, .L50+76
	str	r0, [r4, #56]
	str	r1, [r4, #60]
	ldr	r0, .L50+80
	ldr	r1, .L50+84
	str	r2, [r4, #64]
	str	r3, [r4, #76]
	ldr	r2, .L50+88
	ldr	r3, .L50+92
	str	r6, [r4, #164]
	str	r5, [r4, #68]
	ldr	r6, .L50+96
	ldr	r5, .L50+100
	str	lr, [r4, #72]
	str	ip, [r4, #80]
	ldr	lr, .L50+104
	ldr	ip, .L50+108
	str	r0, [r4, #84]
	str	r1, [r4, #88]
	ldr	r0, .L50+112
	ldr	r1, .L50+116
	str	r2, [r4, #92]
	str	r3, [r4, #96]
	ldr	r2, .L50+120
	ldr	r3, .L50+124
	str	r6, [r4, #100]
	str	r5, [r4, #104]
	str	lr, [r4, #108]
	str	ip, [r4, #112]
	str	r0, [r4, #116]
	str	r1, [r4, #120]
	str	r2, [r4, #124]
	str	r3, [r4, #128]
	ldr	r6, .L50+128
	ldr	r5, .L50+132
	ldr	lr, .L50+136
	ldr	ip, .L50+140
	ldr	r0, .L50+144
	ldr	r1, .L50+148
	ldr	r2, .L50+152
	ldr	r3, .L50+156
	str	r6, [r4, #132]
	str	r5, [r4, #136]
	str	lr, [r4, #140]
	str	ip, [r4, #144]
	str	r0, [r4, #44]
	str	r1, [r4, #148]
	str	r2, [r4, #156]
	str	r3, [r4, #160]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L51:
	.align	2
.L50:
	.word	vfmw_Osal_Func_Ptr_S
	.word	VDM_SetClockSkip
	.word	VDM_OpenHardware
	.word	VDM_CloseHardware
	.word	DSP_OpenHardware
	.word	DSP_CloseHardware
	.word	SCD_OpenHardware
	.word	SCD_CloseHardware
	.word	BPD_OpenHardware
	.word	BPD_CloseHardware
	.word	VDMHAL_V4R3C1_GetHalMemSize
	.word	VDMHAL_V4R3C1_CalcFsSize
	.word	VDMHAL_V4R3C1_OpenHAL
	.word	VDMHAL_V4R3C1_CloseHAL
	.word	VDMHAL_V4R3C1_ArrangeMem
	.word	VDMHAL_V4R3C1_ResetVdm
	.word	VDMHAL_V4R3C1_GetRpuSize
	.word	VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.word	VDMHAL_V4R3C1_EnableSmmu
	.word	VDMHAL_V4R3C1_GlbReset
	.word	VDMHAL_V4R3C1_GlbResetX
	.word	VDMHAL_V4R3C1_ClearIntState
	.word	VDMHAL_V4R3C1_ClearMMUIntState
	.word	VDMHAL_V4R3C1_MaskInt
	.word	VDMHAL_V4R3C1_EnableInt
	.word	VDMHAL_V4R3C1_CheckReg
	.word	VDMHAL_V4R3C1_ReadMMUMask
	.word	VDMHAL_V4R3C1_WriteMMUMask
	.word	VDMHAL_V4R3C1_StartHwRepair
	.word	VDMHAL_V4R3C1_StartHwDecode
	.word	VDMHAL_V4R3C1_PrepareDec
	.word	VDMHAL_V4R3C1_IsVdmReady
	.word	VDMHAL_V4R3C1_IsVdmRun
	.word	VDMHAL_V4R3C1_PrepareRepair
	.word	VDMHAL_V4R3C1_MakeDecReport
	.word	VDMHAL_V4R3C1_UpdateHardwareInfo
	.word	VDMHAL_V4R3C1_GetCharacter
	.word	VDMHAL_V4R3C1_WriteBigTitle1DYuv
	.word	VDMHAL_V4R3C1_IsVdhDecOver
	.word	VDMHAL_V4R3C1_IsVdhPartDecOver
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
	ldr	r3, .L53
	mov	r2, #148
	mov	r1, #0
	mov	r4, r0
	ldr	r3, [r3, #48]
	blx	r3
	mov	r3, #0
	mov	r1, #32
	mov	r2, #50
	movt	r3, 6480
	str	r1, [r4]
	str	r2, [r4, #4]
	mov	r1, #4096
	mov	r2, #2304
	str	r3, [r4, #16]
	str	r2, [r4, #12]
	mov	r3, #3
	mov	r2, #0
	str	r3, [r4, #24]
	str	r2, [r4, #20]
	mov	r3, #6
	mov	r2, #2
	str	r3, [r4, #32]
	str	r2, [r4, #28]
	mov	r3, #9
	mov	r2, #8
	str	r3, [r4, #40]
	str	r2, [r4, #36]
	mov	r3, #5
	mov	r2, #1
	str	r3, [r4, #48]
	str	r2, [r4, #44]
	mov	r3, #11
	mov	r2, #10
	str	r3, [r4, #56]
	str	r2, [r4, #52]
	mov	r3, #13
	mov	r2, #12
	str	r3, [r4, #64]
	str	r2, [r4, #60]
	mov	r3, #16
	mov	r2, #15
	str	r3, [r4, #72]
	str	r2, [r4, #68]
	mov	r3, #19
	mov	r2, #17
	str	r3, [r4, #80]
	str	r2, [r4, #76]
	mov	r3, #22
	mov	r2, #20
	str	r1, [r4, #8]
	str	r2, [r4, #84]
	str	r3, [r4, #88]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L54:
	.align	2
.L53:
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
	bne	.L59
	mov	r0, r1
	bl	PDT_GetVdecCapability
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L59:
	mov	r3, r4
	ldr	r2, .L60
	ldr	r1, .L60+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L61:
	.align	2
.L60:
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
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	bl	PDT_InitHalInterface
	ldr	r3, .L67
	ldr	r3, [r3, #44]
	cmp	r3, #0
	beq	.L63
	blx	r3
.L63:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L68:
	.align	2
.L67:
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
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	PDT_Deinit, .-PDT_Deinit
	.global	g_LowDelaySeqIndex
	.global	g_LowDelayCalcHandle
	.global	g_LowDelayCalcStat
	.global	g_ChipMaxHeight
	.global	g_ChipMaxWidth
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.54663, %object
	.size	__func__.54663, 17
__func__.54663:
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
	.type	g_LowDelaySeqIndex, %object
	.size	g_LowDelaySeqIndex, 128
g_LowDelaySeqIndex:
	.space	128
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
