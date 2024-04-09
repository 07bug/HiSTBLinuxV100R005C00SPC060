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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VDM_SetClockSkip, .-VDM_SetClockSkip
	.align	2
	.global	VDM_OpenHardware
	.type	VDM_OpenHardware, %function
VDM_OpenHardware:
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
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldmfd	sp, {fp, sp, pc}
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
	ldmfd	sp, {fp, sp, pc}
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
	ldmfd	sp, {fp, sp, pc}
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
	ldmfd	sp, {fp, sp, pc}
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SCD_CloseHardware, .-SCD_CloseHardware
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
	ldmfd	sp, {fp, sp, pc}
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	BPD_CloseHardware, .-BPD_CloseHardware
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
	ldr	r3, .L14
	ldr	r0, [fp, #-48]
	add	r2, r3, r4
	str	r6, [fp, #-44]
	ldr	r3, [r3, r4, asl #2]
	ldrb	r1, [r2, #128]	@ zero_extendqisi2
	str	r5, [fp, #-36]
	cmp	r1, #1
	str	r3, [fp, #-40]
	str	r0, [fp, #-32]
	beq	.L13
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L13:
	sub	r0, fp, #44
	bl	HI_DRV_LD_Notify_Event
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L15:
	.align	2
.L14:
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
	ldr	r3, .L17
	mov	r2, #168
	mov	r1, #0
	mov	r4, r0
	ldr	r5, .L17+4
	ldr	r3, [r3, #48]
	blx	r3
	ldr	lr, .L17+8
	ldr	ip, .L17+12
	ldr	r0, .L17+16
	ldr	r1, .L17+20
	ldr	r2, .L17+24
	ldr	r3, .L17+28
	ldr	r6, .L17+32
	str	r5, [r4]
	str	lr, [r4, #4]
	ldr	r5, .L17+36
	ldr	lr, .L17+40
	str	ip, [r4, #8]
	str	r0, [r4, #12]
	ldr	ip, .L17+44
	ldr	r0, .L17+48
	str	r1, [r4, #16]
	str	r2, [r4, #20]
	ldr	r1, .L17+52
	ldr	r2, .L17+56
	str	r3, [r4, #24]
	ldr	r3, .L17+60
	str	r6, [r4, #28]
	str	r5, [r4, #32]
	ldr	r6, .L17+64
	ldr	r5, .L17+68
	str	lr, [r4, #48]
	str	ip, [r4, #52]
	ldr	lr, .L17+72
	ldr	ip, .L17+76
	str	r0, [r4, #56]
	str	r1, [r4, #60]
	ldr	r0, .L17+80
	ldr	r1, .L17+84
	str	r2, [r4, #64]
	str	r3, [r4, #76]
	ldr	r2, .L17+88
	ldr	r3, .L17+92
	str	r6, [r4, #164]
	str	r5, [r4, #68]
	ldr	r6, .L17+96
	ldr	r5, .L17+100
	str	lr, [r4, #72]
	str	ip, [r4, #80]
	ldr	lr, .L17+104
	ldr	ip, .L17+108
	str	r0, [r4, #84]
	str	r1, [r4, #88]
	ldr	r0, .L17+112
	ldr	r1, .L17+116
	str	r2, [r4, #92]
	str	r3, [r4, #96]
	ldr	r2, .L17+120
	ldr	r3, .L17+124
	str	r6, [r4, #100]
	str	r5, [r4, #104]
	str	lr, [r4, #108]
	str	ip, [r4, #112]
	str	r0, [r4, #116]
	str	r1, [r4, #120]
	str	r2, [r4, #124]
	str	r3, [r4, #128]
	ldr	r6, .L17+128
	ldr	r5, .L17+132
	ldr	lr, .L17+136
	ldr	ip, .L17+140
	ldr	r0, .L17+144
	ldr	r1, .L17+148
	ldr	r2, .L17+152
	ldr	r3, .L17+156
	str	r6, [r4, #132]
	str	r5, [r4, #136]
	str	lr, [r4, #140]
	str	ip, [r4, #144]
	str	r0, [r4, #44]
	str	r1, [r4, #148]
	str	r2, [r4, #156]
	str	r3, [r4, #160]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L18:
	.align	2
.L17:
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
	.word	VDMHAL_V5R6C1_GetHalMemSize
	.word	VDMHAL_V5R6C1_CalcFsSize
	.word	VDMHAL_V5R6C1_OpenHAL
	.word	VDMHAL_V5R6C1_CloseHAL
	.word	VDMHAL_V5R6C1_ArrangeMem
	.word	VDMHAL_V5R6C1_ResetVdm
	.word	VDMHAL_V5R6C1_GetRpuSize
	.word	VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.word	VDMHAL_V5R6C1_EnableSmmu
	.word	VDMHAL_V5R6C1_GlbReset
	.word	VDMHAL_V5R6C1_GlbResetX
	.word	VDMHAL_V5R6C1_ClearIntState
	.word	VDMHAL_V5R6C1_ClearMMUIntState
	.word	VDMHAL_V5R6C1_MaskInt
	.word	VDMHAL_V5R6C1_EnableInt
	.word	VDMHAL_V5R6C1_CheckReg
	.word	VDMHAL_V5R6C1_ReadMMUMask
	.word	VDMHAL_V5R6C1_WriteMMUMask
	.word	VDMHAL_V5R6C1_StartHwRepair
	.word	VDMHAL_V5R6C1_StartHwDecode
	.word	VDMHAL_V5R6C1_PrepareDec
	.word	VDMHAL_V5R6C1_IsVdmReady
	.word	VDMHAL_V5R6C1_IsVdmRun
	.word	VDMHAL_V5R6C1_PrepareRepair
	.word	VDMHAL_V5R6C1_MakeDecReport
	.word	VDMHAL_V5R6C1_UpdateHardwareInfo
	.word	VDMHAL_V5R6C1_GetCharacter
	.word	VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.word	VDMHAL_V5R6C1_IsVdhDecOver
	.word	VDMHAL_V5R6C1_IsVdhPartDecOver
	UNWIND(.fnend)
	.size	PDT_InitHalInterface, .-PDT_InitHalInterface
	.align	2
	.global	PDT_Is3716MV450
	.type	PDT_Is3716MV450, %function
PDT_Is3716MV450:
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
	ldr	r2, .L22
	mov	r3, #512
	movt	r3, 14230
	ldr	r1, [r2, #160]
	cmp	r1, r3
	ldreqh	r0, [r2, #166]
	andeq	r0, r0, #31
	subeq	r0, r0, #16
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L23:
	.align	2
.L22:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	PDT_Is3716MV450, .-PDT_Is3716MV450
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
	ldr	r3, .L25
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
	str	r1, [r4, #8]
	str	r2, [r4, #12]
	mov	r1, #0
	mov	r2, #3
	str	r3, [r4, #16]
	str	r2, [r4, #24]
	mov	r3, #2
	mov	r2, #6
	str	r3, [r4, #28]
	str	r2, [r4, #32]
	mov	r3, #8
	mov	r2, #9
	str	r3, [r4, #36]
	str	r2, [r4, #40]
	mov	r3, #1
	mov	r2, #5
	str	r3, [r4, #44]
	str	r2, [r4, #48]
	mov	r3, #10
	mov	r2, #11
	str	r3, [r4, #52]
	str	r2, [r4, #56]
	mov	r3, #12
	mov	r2, #13
	str	r3, [r4, #60]
	str	r2, [r4, #64]
	mov	r3, #15
	mov	r2, #16
	str	r3, [r4, #68]
	str	r2, [r4, #72]
	mov	r3, #17
	mov	r2, #18
	str	r3, [r4, #76]
	str	r2, [r4, #80]
	mov	r3, #19
	mov	r2, #20
	str	r3, [r4, #84]
	str	r1, [r4, #20]
	mov	r3, #22
	str	r2, [r4, #88]
	str	r3, [r4, #92]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L26:
	.align	2
.L25:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	PDT_GetVdecCapability, .-PDT_GetVdecCapability
	.align	2
	.global	PDT_IsNVRChipType
	.type	PDT_IsNVRChipType, %function
PDT_IsNVRChipType:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r4, r0
	sub	r0, fp, #24
	bl	HI_DRV_SYS_GetChipPackageType
	ldr	r3, [fp, #-24]
	mov	r0, #0
	cmp	r3, #0
	movne	r3, #1
	str	r3, [r4]
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	PDT_IsNVRChipType, .-PDT_IsNVRChipType
	.align	2
	.global	PDT_GetAttribute
	.type	PDT_GetAttribute, %function
PDT_GetAttribute:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	subs	r4, r0, #0
	mov	r5, r1
	beq	.L33
	cmp	r4, #1
	beq	.L34
	mov	r3, r4
	ldr	r2, .L40
	ldr	r1, .L40+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L34:
	sub	r0, fp, #24
	bl	HI_DRV_SYS_GetChipPackageType
	ldr	r3, [fp, #-24]
	mov	r0, #0
	cmp	r3, r0
	movne	r3, #1
	str	r3, [r5]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L33:
	mov	r0, r1
	bl	PDT_GetVdecCapability
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L41:
	.align	2
.L40:
	.word	.LANCHOR1
	.word	.LC0
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
	ldr	r5, .L47
	mov	r2, #16
	ldr	r4, .L47+4
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
	ldr	r3, .L47+8
	ldr	r3, [r3, #44]
	cmp	r3, #0
	beq	.L43
	blx	r3
.L43:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L48:
	.align	2
.L47:
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
	ldr	r4, .L50
	ldr	r5, .L50+4
	ldr	r0, [r4, #168]
	ldr	r3, [r5, #156]
	blx	r3
	ldr	r0, [r4, #172]
	ldr	r3, [r5, #156]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L51:
	.align	2
.L50:
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
	.type	__func__.56041, %object
	.size	__func__.56041, 17
__func__.56041:
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
	ASCII(.ascii	"%s unknown eAttrID %d\012\000" )
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
