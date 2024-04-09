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
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC0
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	bfi	w0, w19, 12, 5
	and	w0, w0, -131073
	str	w0, [x1, 120]
	orr	w0, w0, 131072
	str	w0, [x1, 120]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDM_SetClockSkip, .-VDM_SetClockSkip
	.align	3
.LC0:
	.xword	g_pstRegCrg
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
	ldr	x0, .LC1
	ldr	x1, [x0]
	ldr	w0, [x1, 136]
	orr	w0, w0, 1
	and	w0, w0, -17
	str	w0, [x1, 136]
	ldp	x29, x30, [sp], 16
	ret
	.size	BPD_OpenHardware, .-BPD_OpenHardware
	.align	3
.LC1:
	.xword	g_pstRegCrg
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
	ldr	x0, .LC2
	ldr	x1, [x0]
	ldr	w0, [x1, 136]
	and	w0, w0, -2
	orr	w0, w0, 16
	str	w0, [x1, 136]
	ldp	x29, x30, [sp], 16
	ret
	.size	BPD_CloseHardware, .-BPD_CloseHardware
	.align	3
.LC2:
	.xword	g_pstRegCrg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MMU_OpenHardware
	.type	MMU_OpenHardware, %function
MMU_OpenHardware:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x0, x30
	bl	_mcount
	ldr	x21, .LC3
	ldr	x20, .LC4
	mov	x0, 30
	ldr	x1, [x21]
	ldr	x2, [x20, 232]
	ldr	w19, [x1, 828]
	orr	w19, w19, 1
	str	w19, [x1, 828]
	and	w19, w19, -17
	blr	x2
	ldr	x2, [x21]
	mov	x0, 30
	ldr	x1, [x20, 232]
	str	w19, [x2, 828]
	blr	x1
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	MMU_OpenHardware, .-MMU_OpenHardware
	.align	3
.LC3:
	.xword	g_pstRegCrg
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MMU_CloseHardware
	.type	MMU_CloseHardware, %function
MMU_CloseHardware:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	MMU_CloseHardware, .-MMU_CloseHardware
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDM_OpenHardware
	.type	VDM_OpenHardware, %function
VDM_OpenHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L7
	ldr	x1, .LC5
	mov	w2, 3247
	movk	w2, 0xfffc, lsl 16
	ldr	x4, .LC6
	mov	x0, 30
	ldr	x3, [x1]
	ldr	w1, [x3, 120]
	orr	w1, w1, 1
	and	w1, w1, w2
	str	w1, [x3, 120]
	ldr	x1, [x4, 232]
	blr	x1
.L8:
	ldr	x0, .LC7
	mov	w1, 41463
	movk	w1, 0x481, lsl 16
	ldr	w0, [x0]
	add	w0, w0, 4
	bl	MEM_WritePhyWord
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L7:
	ldr	x1, .LC9
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	b	.L8
	.size	VDM_OpenHardware, .-VDM_OpenHardware
	.align	3
.LC5:
	.xword	g_pstRegCrg
	.align	3
.LC6:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC7:
	.xword	s_ScdRegPhyBaseAddr
	.align	3
.LC9:
	.xword	.LC8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDM_CloseHardware
	.type	VDM_CloseHardware, %function
VDM_CloseHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L12
	ldr	x20, .LC10
	ldr	x1, .LC11
	ldr	x0, [x20]
	ldr	x1, [x1, 168]
	ldr	w19, [x0, 120]
	cbz	x1, .L13
	mov	w0, 0
	blr	x1
.L14:
	ldr	x2, [x20]
	and	w19, w19, -2
	ldr	x1, .LC14
	mov	x0, 30
	str	w19, [x2, 120]
	ldr	x1, [x1, 232]
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L12:
	ldr	x1, .LC16
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L13:
	ldr	x1, .LC13
	mov	w2, 138
	mov	w0, 0
	bl	dprint_vfmw
	b	.L14
	.size	VDM_CloseHardware, .-VDM_CloseHardware
	.align	3
.LC10:
	.xword	g_pstRegCrg
	.align	3
.LC11:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC13:
	.xword	.LC12
	.align	3
.LC14:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC16:
	.xword	.LC15
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DSP_OpenHardware
	.type	DSP_OpenHardware, %function
DSP_OpenHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbz	w19, .L19
	ldr	x1, .LC20
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L19:
	ldr	x1, .LC17
	mov	x0, 30
	ldr	x3, .LC18
	ldr	x2, [x1]
	ldr	w1, [x2, 120]
	orr	w1, w1, 2
	str	w1, [x2, 120]
	ldr	x1, [x3, 232]
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DSP_OpenHardware, .-DSP_OpenHardware
	.align	3
.LC17:
	.xword	g_pstRegCrg
	.align	3
.LC18:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC20:
	.xword	.LC19
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	DSP_CloseHardware
	.type	DSP_CloseHardware, %function
DSP_CloseHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbz	w19, .L23
	ldr	x1, .LC24
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L23:
	ldr	x1, .LC21
	mov	x0, 30
	ldr	x3, .LC22
	ldr	x2, [x1]
	ldr	w1, [x2, 120]
	and	w1, w1, -3
	str	w1, [x2, 120]
	ldr	x1, [x3, 232]
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	DSP_CloseHardware, .-DSP_CloseHardware
	.align	3
.LC21:
	.xword	g_pstRegCrg
	.align	3
.LC22:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC24:
	.xword	.LC23
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCD_OpenHardware
	.type	SCD_OpenHardware, %function
SCD_OpenHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L25
	ldr	x0, .LC25
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	and	w0, w0, -33
	str	w0, [x1, 120]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L25:
	ldr	x1, .LC27
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCD_OpenHardware, .-SCD_OpenHardware
	.align	3
.LC25:
	.xword	g_pstRegCrg
	.align	3
.LC27:
	.xword	.LC26
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	SCD_CloseHardware
	.type	SCD_CloseHardware, %function
SCD_CloseHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L28
	ldr	x0, .LC28
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	orr	w0, w0, 32
	str	w0, [x1, 120]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L28:
	ldr	x1, .LC30
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCD_CloseHardware, .-SCD_CloseHardware
	.align	3
.LC28:
	.xword	g_pstRegCrg
	.align	3
.LC30:
	.xword	.LC29
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
	ldr	x0, .LC31
	ldr	w3, [x29, 60]
	add	x1, x0, 128
	ldr	w0, [x0, w19, sxtw 2]
	stp	w21, w0, [x29, 64]
	ldrb	w0, [x1, w19, sxtw]
	stp	w20, w3, [x29, 72]
	cmp	w0, 1
	beq	.L32
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L32:
	add	x0, x29, 64
	bl	HI_DRV_LD_Notify_Event
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDEC_Lowdelay_Event_Time, .-VDEC_Lowdelay_Event_Time
	.align	3
.LC31:
	.xword	.LANCHOR0
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_GetOutputFormat
	.type	PDT_GetOutputFormat, %function
PDT_GetOutputFormat:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x19]
	cmp	w0, 17
	beq	.L34
	ldr	w0, [x19, 4]
	cmp	w0, 1920
	bhi	.L34
	ldr	w0, [x19, 8]
	cmp	w0, 1088
	bhi	.L34
	str	wzr, [x19, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L34:
	mov	w0, 1
	str	w0, [x19, 12]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_GetOutputFormat, .-PDT_GetOutputFormat
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
	ldr	x3, .LC33
	mov	x2, 336
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x6, .LC34
	ldr	x5, .LC35
	ldr	x4, .LC36
	ldr	x3, .LC37
	ldr	x2, .LC38
	ldr	x1, .LC39
	ldr	x8, .LC40
	ldr	x0, .LC41
	stp	x6, x5, [x19]
	stp	x4, x3, [x19, 16]
	stp	x2, x1, [x19, 32]
	stp	x8, x0, [x19, 48]
	ldr	x7, .LC42
	ldr	x5, .LC44
	ldr	x4, .LC45
	ldr	x3, .LC46
	ldr	x2, .LC47
	ldr	x1, .LC48
	ldr	x0, .LC49
	ldr	x6, .LC43
	stp	x4, x3, [x19, 96]
	stp	x2, x1, [x19, 112]
	str	x7, [x19, 64]
	stp	x6, x5, [x19, 72]
	str	x0, [x19, 128]
	ldr	x6, .LC50
	ldr	x5, .LC51
	ldr	x4, .LC52
	ldr	x3, .LC53
	ldr	x2, .LC54
	ldr	x1, .LC55
	ldr	x0, .LC57
	ldr	x7, .LC58
	ldr	x8, .LC56
	stp	x4, x3, [x19, 136]
	stp	x6, x2, [x19, 152]
	stp	x0, x7, [x19, 184]
	stp	x1, x8, [x19, 168]
	str	x5, [x19, 328]
	ldr	x6, .LC59
	ldr	x5, .LC60
	ldr	x4, .LC61
	ldr	x3, .LC62
	ldr	x2, .LC63
	ldr	x1, .LC64
	ldr	x0, .LC65
	stp	x6, x5, [x19, 200]
	stp	x4, x3, [x19, 216]
	stp	x2, x1, [x19, 232]
	str	x0, [x19, 248]
	ldr	x8, .LC66
	ldr	x7, .LC67
	ldr	x6, .LC68
	ldr	x5, .LC69
	ldr	x4, .LC70
	ldr	x3, .LC71
	ldr	x2, .LC72
	ldr	x1, .LC73
	ldr	x0, .LC74
	str	x3, [x19, 88]
	stp	x8, x7, [x19, 256]
	stp	x6, x5, [x19, 272]
	stp	x4, x2, [x19, 288]
	stp	x1, x0, [x19, 312]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_InitHalInterface, .-PDT_InitHalInterface
	.align	3
.LC33:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC34:
	.xword	VDM_SetClockSkip
	.align	3
.LC35:
	.xword	VDM_OpenHardware
	.align	3
.LC36:
	.xword	VDM_CloseHardware
	.align	3
.LC37:
	.xword	DSP_OpenHardware
	.align	3
.LC38:
	.xword	DSP_CloseHardware
	.align	3
.LC39:
	.xword	SCD_OpenHardware
	.align	3
.LC40:
	.xword	SCD_CloseHardware
	.align	3
.LC41:
	.xword	BPD_OpenHardware
	.align	3
.LC42:
	.xword	BPD_CloseHardware
	.align	3
.LC43:
	.xword	MMU_OpenHardware
	.align	3
.LC44:
	.xword	MMU_CloseHardware
	.align	3
.LC45:
	.xword	VDMHAL_V5R2C1_GetHalMemSize
	.align	3
.LC46:
	.xword	VDMHAL_V5R2C1_CalcFsSize
	.align	3
.LC47:
	.xword	VDMHAL_V5R2C1_OpenHAL
	.align	3
.LC48:
	.xword	VDMHAL_V5R2C1_CloseHAL
	.align	3
.LC49:
	.xword	VDMHAL_V5R2C1_ArrangeMem
	.align	3
.LC50:
	.xword	VDMHAL_V5R2C1_ResetVdm
	.align	3
.LC51:
	.xword	VDMHAL_V5R2C1_GetRpuSize
	.align	3
.LC52:
	.xword	VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.align	3
.LC53:
	.xword	VDMHAL_V5R2C1_EnableSmmu
	.align	3
.LC54:
	.xword	VDMHAL_V5R2C1_GlbReset
	.align	3
.LC55:
	.xword	VDMHAL_V5R2C1_GlbResetX
	.align	3
.LC56:
	.xword	VDMHAL_V5R2C1_ClearIntState
	.align	3
.LC57:
	.xword	VDMHAL_V5R2C1_ClearMMUIntState
	.align	3
.LC58:
	.xword	VDMHAL_V5R2C1_MaskInt
	.align	3
.LC59:
	.xword	VDMHAL_V5R2C1_EnableInt
	.align	3
.LC60:
	.xword	VDMHAL_V5R2C1_CheckReg
	.align	3
.LC61:
	.xword	VDMHAL_V5R2C1_ReadMMUMask
	.align	3
.LC62:
	.xword	VDMHAL_V5R2C1_WriteMMUMask
	.align	3
.LC63:
	.xword	VDMHAL_V5R2C1_StartHwRepair
	.align	3
.LC64:
	.xword	VDMHAL_V5R2C1_StartHwDecode
	.align	3
.LC65:
	.xword	VDMHAL_V5R2C1_PrepareDec
	.align	3
.LC66:
	.xword	VDMHAL_V5R2C1_IsVdmReady
	.align	3
.LC67:
	.xword	VDMHAL_V5R2C1_IsVdmRun
	.align	3
.LC68:
	.xword	VDMHAL_V5R2C1_PrepareRepair
	.align	3
.LC69:
	.xword	VDMHAL_V5R2C1_MakeDecReport
	.align	3
.LC70:
	.xword	VDMHAL_V5R2C1_UpdateHardwareInfo
	.align	3
.LC71:
	.xword	VDMHAL_V5R2C1_GetCharacter
	.align	3
.LC72:
	.xword	VDMHAL_V5R2C1_WriteBigTitle1DYuv
	.align	3
.LC73:
	.xword	VDMHAL_V5R2C1_IsVdhDecOver
	.align	3
.LC74:
	.xword	VDMHAL_V5R2C1_IsVdhPartDecOver
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_GetVdecCapability
	.type	PDT_GetVdecCapability, %function
PDT_GetVdecCapability:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	x3, .LC76
	mov	x2, 148
	ldr	x4, .LC75
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	ldr	w20, [x4, 160]
	blr	x3
	mov	w0, 528
	mov	w1, 50
	movk	w0, 0x3798, lsl 16
	mov	w7, 32
	mov	w6, 4096
	mov	w5, 2304
	mov	w4, 424673280
	mov	w3, 3
	mov	w2, 2
	cmp	w20, w0
	stp	w7, w1, [x19]
	stp	w6, w5, [x19, 8]
	mov	w1, 6
	str	w1, [x19, 32]
	stp	w4, wzr, [x19, 16]
	stp	w3, w2, [x19, 24]
	beq	.L42
	mov	w4, 8
	mov	w3, 9
	mov	w2, 15
	mov	w1, 16
	stp	w4, w3, [x19, 36]
	mov	w0, 17
	mov	w8, 1
	mov	w7, 5
	mov	w6, 10
	mov	w5, 11
	mov	w4, 12
	mov	w3, 13
	str	w0, [x19, 76]
	stp	w8, w7, [x19, 44]
	stp	w6, w5, [x19, 52]
	stp	w2, w1, [x19, 68]
	stp	w4, w3, [x19, 60]
.L43:
	add	x2, x19, x2, sxtw 2
	add	x1, x19, x1, sxtw 2
	add	x0, x19, x0, sxtw 2
	mov	w5, 19
	mov	w4, 20
	mov	w3, 22
	str	w5, [x2, 20]
	str	w4, [x1, 20]
	str	w3, [x0, 20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L42:
	mov	w2, 5
	mov	w1, 15
	mov	w0, 16
	mov	w3, 1
	stp	w1, w0, [x19, 44]
	stp	w3, w2, [x19, 36]
	mov	w0, 10
	mov	w1, 9
	mov	w2, 8
	b	.L43
	.size	PDT_GetVdecCapability, .-PDT_GetVdecCapability
	.align	3
.LC75:
	.xword	.LANCHOR0
	.align	3
.LC76:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_GetAttribute
	.type	PDT_GetAttribute, %function
PDT_GetAttribute:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	x20, x1
	bl	_mcount
	cbz	w19, .L46
	cmp	w19, 2
	bne	.L56
	ldr	w0, [x20]
	cmp	w0, 17
	beq	.L49
	ldr	w0, [x20, 4]
	cmp	w0, 1920
	bhi	.L49
	ldr	w0, [x20, 8]
	cmp	w0, 1088
	bhi	.L49
	mov	w0, 0
	str	wzr, [x20, 12]
	b	.L48
	.p2align 3
.L56:
	ldr	x2, .LC77
	mov	w3, w19
	ldr	x1, .LC79
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
.L48:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L49:
	mov	w1, 1
	str	w1, [x20, 12]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L46:
	mov	x0, x20
	bl	PDT_GetVdecCapability
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_GetAttribute, .-PDT_GetAttribute
	.align	3
.LC77:
	.xword	.LANCHOR1
	.align	3
.LC79:
	.xword	.LC78
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
	ldr	x20, .LC80
	ldr	x21, .LC81
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
	ldr	x0, .LC82
	ldr	x0, [x0, 88]
	cbz	x0, .L58
	blr	x0
.L58:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	PDT_Init, .-PDT_Init
	.align	3
.LC80:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC81:
	.xword	.LANCHOR0
	.align	3
.LC82:
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
	ldr	x19, .LC85
	ldr	x20, .LC84
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
.LC84:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC85:
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
	.type	__func__.50697, %object
	.size	__func__.50697, 17
__func__.50697:
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
.LC8:
	ASCII(.string	"VDM_OpenHardware failed, wrong VdhId %d\n" )
	.zero	7
.LC12:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC15:
	ASCII(.string	"VDM_CloseHardware failed, wrong VdhId %d\n" )
	.zero	6
.LC19:
	ASCII(.string	"DSP_OpenHardware failed, wrong VdhId %d\n" )
	.zero	7
.LC23:
	ASCII(.string	"DSP_CloseHardware failed, wrong VdhId %d\n" )
	.zero	6
.LC26:
	ASCII(.string	"SCD_OpenHardware Wrong ScdId %d\n" )
	.zero	7
.LC29:
	ASCII(.string	"SCD_CloseHardware Wrong ScdId %d\n" )
	.zero	6
.LC78:
	ASCII(.string	"%s unkown eAttrID %d\n" )
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
