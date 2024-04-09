#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"product.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VDM_SetClockSkip
	.type	VDM_SetClockSkip, %function
VDM_SetClockSkip:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDM_SetClockSkip, .-VDM_SetClockSkip
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	BPD_CloseHardware
	.type	BPD_CloseHardware, %function
BPD_CloseHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	BPD_CloseHardware, .-BPD_CloseHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	BPD_OpenHardware
	.type	BPD_OpenHardware, %function
BPD_OpenHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	BPD_OpenHardware, .-BPD_OpenHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDM_OpenHardware
	.type	VDM_OpenHardware, %function
VDM_OpenHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDM_OpenHardware, .-VDM_OpenHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDM_CloseHardware
	.type	VDM_CloseHardware, %function
VDM_CloseHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDM_CloseHardware, .-VDM_CloseHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DSP_OpenHardware
	.type	DSP_OpenHardware, %function
DSP_OpenHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	DSP_OpenHardware, .-DSP_OpenHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DSP_CloseHardware
	.type	DSP_CloseHardware, %function
DSP_CloseHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	DSP_CloseHardware, .-DSP_CloseHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCD_OpenHardware
	.type	SCD_OpenHardware, %function
SCD_OpenHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	SCD_OpenHardware, .-SCD_OpenHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCD_CloseHardware
	.type	SCD_CloseHardware, %function
SCD_CloseHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	SCD_CloseHardware, .-SCD_CloseHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDEC_Lowdelay_Event_Time
	.type	VDEC_Lowdelay_Event_Time, %function
VDEC_Lowdelay_Event_Time:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w21, w1
	mov	w20, w2
	bl	_mcount
	add	x0, x29, 80
	str	wzr, [x0, -20]!
	bl	HI_DRV_SYS_GetTimeStampMs
	ldr	x0, .LC0
	ldr	w3, [x29, 60]
	add	x1, x0, 128
	ldr	w0, [x0, w19, sxtw 2]
	stp	w21, w0, [x29, 64]
	ldrb	w0, [x1, w19, sxtw]
	stp	w20, w3, [x29, 72]
	cmp	w0, 1
	beq	.L13
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L13:
	add	x0, x29, 64
	bl	HI_DRV_LD_Notify_Event
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDEC_Lowdelay_Event_Time, .-VDEC_Lowdelay_Event_Time
	.align	3
.LC0:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_InitHalInterface
	.type	PDT_InitHalInterface, %function
PDT_InitHalInterface:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC2
	mov	x2, 336
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x6, .LC3
	ldr	x5, .LC4
	ldr	x4, .LC5
	ldr	x3, .LC6
	ldr	x2, .LC7
	ldr	x1, .LC8
	ldr	x8, .LC9
	ldr	x0, .LC10
	stp	x6, x5, [x19]
	stp	x4, x3, [x19, 16]
	stp	x2, x1, [x19, 32]
	stp	x8, x0, [x19, 48]
	ldr	x7, .LC11
	ldr	x5, .LC13
	ldr	x4, .LC14
	ldr	x3, .LC15
	ldr	x2, .LC16
	ldr	x1, .LC17
	ldr	x0, .LC18
	ldr	x6, .LC12
	stp	x4, x3, [x19, 112]
	str	x7, [x19, 64]
	stp	x6, x5, [x19, 96]
	str	x2, [x19, 128]
	str	x1, [x19, 152]
	str	x0, [x19, 328]
	ldr	x6, .LC19
	ldr	x5, .LC20
	ldr	x4, .LC21
	ldr	x3, .LC22
	ldr	x2, .LC23
	ldr	x1, .LC24
	ldr	x8, .LC25
	ldr	x0, .LC26
	stp	x6, x5, [x19, 136]
	stp	x4, x3, [x19, 160]
	stp	x2, x1, [x19, 176]
	stp	x8, x0, [x19, 192]
	ldr	x7, .LC27
	ldr	x5, .LC29
	ldr	x4, .LC30
	ldr	x3, .LC31
	ldr	x2, .LC32
	ldr	x1, .LC33
	ldr	x0, .LC34
	ldr	x6, .LC28
	stp	x4, x3, [x19, 232]
	stp	x2, x1, [x19, 248]
	str	x7, [x19, 208]
	stp	x6, x5, [x19, 216]
	str	x0, [x19, 264]
	ldr	x6, .LC35
	ldr	x5, .LC36
	ldr	x4, .LC37
	ldr	x3, .LC38
	ldr	x2, .LC39
	ldr	x1, .LC40
	ldr	x0, .LC41
	str	x3, [x19, 88]
	stp	x6, x5, [x19, 272]
	stp	x4, x2, [x19, 288]
	stp	x1, x0, [x19, 312]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_InitHalInterface, .-PDT_InitHalInterface
	.align	3
.LC2:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC3:
	.xword	VDM_SetClockSkip
	.align	3
.LC4:
	.xword	VDM_OpenHardware
	.align	3
.LC5:
	.xword	VDM_CloseHardware
	.align	3
.LC6:
	.xword	DSP_OpenHardware
	.align	3
.LC7:
	.xword	DSP_CloseHardware
	.align	3
.LC8:
	.xword	SCD_OpenHardware
	.align	3
.LC9:
	.xword	SCD_CloseHardware
	.align	3
.LC10:
	.xword	BPD_OpenHardware
	.align	3
.LC11:
	.xword	BPD_CloseHardware
	.align	3
.LC12:
	.xword	VDMHAL_V5R6C1_GetHalMemSize
	.align	3
.LC13:
	.xword	VDMHAL_V5R6C1_CalcFsSize
	.align	3
.LC14:
	.xword	VDMHAL_V5R6C1_OpenHAL
	.align	3
.LC15:
	.xword	VDMHAL_V5R6C1_CloseHAL
	.align	3
.LC16:
	.xword	VDMHAL_V5R6C1_ArrangeMem
	.align	3
.LC17:
	.xword	VDMHAL_V5R6C1_ResetVdm
	.align	3
.LC18:
	.xword	VDMHAL_V5R6C1_GetRpuSize
	.align	3
.LC19:
	.xword	VDMHAL_V5R6C1_SetSmmuPageTableAddr
	.align	3
.LC20:
	.xword	VDMHAL_V5R6C1_EnableSmmu
	.align	3
.LC21:
	.xword	VDMHAL_V5R6C1_GlbReset
	.align	3
.LC22:
	.xword	VDMHAL_V5R6C1_GlbResetX
	.align	3
.LC23:
	.xword	VDMHAL_V5R6C1_ClearIntState
	.align	3
.LC24:
	.xword	VDMHAL_V5R6C1_ClearMMUIntState
	.align	3
.LC25:
	.xword	VDMHAL_V5R6C1_MaskInt
	.align	3
.LC26:
	.xword	VDMHAL_V5R6C1_EnableInt
	.align	3
.LC27:
	.xword	VDMHAL_V5R6C1_CheckReg
	.align	3
.LC28:
	.xword	VDMHAL_V5R6C1_ReadMMUMask
	.align	3
.LC29:
	.xword	VDMHAL_V5R6C1_WriteMMUMask
	.align	3
.LC30:
	.xword	VDMHAL_V5R6C1_StartHwRepair
	.align	3
.LC31:
	.xword	VDMHAL_V5R6C1_StartHwDecode
	.align	3
.LC32:
	.xword	VDMHAL_V5R6C1_PrepareDec
	.align	3
.LC33:
	.xword	VDMHAL_V5R6C1_IsVdmReady
	.align	3
.LC34:
	.xword	VDMHAL_V5R6C1_IsVdmRun
	.align	3
.LC35:
	.xword	VDMHAL_V5R6C1_PrepareRepair
	.align	3
.LC36:
	.xword	VDMHAL_V5R6C1_MakeDecReport
	.align	3
.LC37:
	.xword	VDMHAL_V5R6C1_UpdateHardwareInfo
	.align	3
.LC38:
	.xword	VDMHAL_V5R6C1_GetCharacter
	.align	3
.LC39:
	.xword	VDMHAL_V5R6C1_WriteBigTitle1DYuv
	.align	3
.LC40:
	.xword	VDMHAL_V5R6C1_IsVdhDecOver
	.align	3
.LC41:
	.xword	VDMHAL_V5R6C1_IsVdhPartDecOver
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_Is3716MV450
	.type	PDT_Is3716MV450, %function
PDT_Is3716MV450:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC42
	mov	w2, 512
	movk	w2, 0x3796, lsl 16
	mov	w0, 0
	add	x3, x1, 160
	ldr	w1, [x1, 160]
	cmp	w1, w2
	bne	.L16
	ldrh	w0, [x3, 6]
	and	w0, w0, 31
	cmp	w0, 16
	cset	w0, eq
.L16:
	ldp	x29, x30, [sp], 16
	ret
	.size	PDT_Is3716MV450, .-PDT_Is3716MV450
	.align	3
.LC42:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_GetVdecCapability
	.type	PDT_GetVdecCapability, %function
PDT_GetVdecCapability:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC44
	mov	x2, 148
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	w4, 32
	mov	w3, 50
	mov	w2, 4096
	mov	w1, 2304
	mov	w0, 3
	mov	w8, 424673280
	stp	w4, w3, [x19]
	stp	w2, w1, [x19, 8]
	mov	w7, 2
	mov	w6, 6
	stp	w0, w7, [x19, 24]
	mov	w5, 8
	mov	w4, 9
	mov	w3, 1
	mov	w2, 5
	mov	w1, 10
	mov	w0, 11
	stp	w6, w5, [x19, 32]
	stp	w4, w3, [x19, 40]
	stp	w2, w1, [x19, 48]
	stp	w8, wzr, [x19, 16]
	mov	w7, 13
	mov	w8, 12
	mov	w6, 15
	mov	w5, 16
	stp	w0, w8, [x19, 56]
	stp	w7, w6, [x19, 64]
	str	w5, [x19, 72]
	mov	w4, 17
	mov	w3, 18
	mov	w2, 19
	stp	w4, w3, [x19, 76]
	mov	w1, 20
	mov	w0, 22
	stp	w2, w1, [x19, 84]
	str	w0, [x19, 92]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_GetVdecCapability, .-PDT_GetVdecCapability
	.align	3
.LC44:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_IsNVRChipType
	.type	PDT_IsNVRChipType, %function
PDT_IsNVRChipType:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	add	x0, x29, 44
	bl	HI_DRV_SYS_GetChipPackageType
	ldr	w0, [x29, 44]
	cbz	w0, .L22
	mov	w0, 1
	str	w0, [x19]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L22:
	str	wzr, [x19]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PDT_IsNVRChipType, .-PDT_IsNVRChipType
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_GetAttribute
	.type	PDT_GetAttribute, %function
PDT_GetAttribute:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	w19, .L25
	cmp	w19, 1
	beq	.L26
	ldr	x2, .LC45
	mov	w3, w19
	ldr	x1, .LC47
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L26:
	add	x0, x29, 44
	bl	HI_DRV_SYS_GetChipPackageType
	ldr	w1, [x29, 44]
	mov	w0, 0
	cmp	w1, wzr
	cset	w1, ne
	str	w1, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L25:
	mov	x0, x20
	bl	PDT_GetVdecCapability
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	PDT_GetAttribute, .-PDT_GetAttribute
	.align	3
.LC45:
	.xword	.LANCHOR1
	.align	3
.LC47:
	.xword	.LC46
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_Init
	.type	PDT_Init, %function
PDT_Init:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	x0, x30
	bl	_mcount
	ldr	x20, .LC48
	ldr	x21, .LC49
	mov	x2, 24
	mov	w1, 0
	ldr	x3, [x20, 96]
	add	x19, x21, 160
	mov	x0, x19
	blr	x3
	ldr	x2, [x20, 304]
	mov	w0, 3808
	mov	w1, 4096
	movk	w0, 0xf800, lsl 16
	blr	x2
	mov	x2, x0
	str	x2, [x21, 168]
	mov	w0, 2112
	ldr	x3, [x20, 304]
	mov	w1, 4096
	ldr	w2, [x2]
	movk	w0, 0xf8a2, lsl 16
	str	w2, [x21, 160]
	blr	x3
	mov	x1, x0
	str	x1, [x21, 176]
	mov	x0, x22
	ldr	w1, [x1]
	str	w1, [x21, 164]
	bl	PDT_InitHalInterface
	ldr	x0, .LC50
	ldr	x0, [x0, 88]
	cbz	x0, .L33
	blr	x0
.L33:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PDT_Init, .-PDT_Init
	.align	3
.LC48:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC49:
	.xword	.LANCHOR0
	.align	3
.LC50:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_Deinit
	.type	PDT_Deinit, %function
PDT_Deinit:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC53
	ldr	x20, .LC52
	ldr	x0, [x19, 168]
	ldr	x1, [x20, 312]
	blr	x1
	ldr	x0, [x19, 176]
	ldr	x1, [x20, 312]
	blr	x1
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_Deinit, .-PDT_Deinit
	.align	3
.LC52:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC53:
	.xword	.LANCHOR0
	.global	g_chipIdentity
	.global	g_LowDelaySeqIndex
	.global	g_LowDelayCalcHandle
	.global	g_LowDelayCalcStat
	.global	g_ChipMaxHeight
	.global	g_ChipMaxWidth
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.53372, %object
	.size	__func__.53372, 17
__func__.53372:
	.string	"PDT_GetAttribute"
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
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC46:
	ASCII(.string	"%s unknown eAttrID %d\n" )
	.bss
	.align	3
.LANCHOR0 = . + 0
	.type	g_LowDelayCalcHandle, %object
	.size	g_LowDelayCalcHandle, 128
g_LowDelayCalcHandle:
	.zero	128
	.type	g_LowDelayCalcStat, %object
	.size	g_LowDelayCalcStat, 32
g_LowDelayCalcStat:
	.zero	32
	.type	g_chipIdentity, %object
	.size	g_chipIdentity, 24
g_chipIdentity:
	.zero	24
	.type	g_LowDelaySeqIndex, %object
	.size	g_LowDelaySeqIndex, 128
g_LowDelaySeqIndex:
	.zero	128
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
