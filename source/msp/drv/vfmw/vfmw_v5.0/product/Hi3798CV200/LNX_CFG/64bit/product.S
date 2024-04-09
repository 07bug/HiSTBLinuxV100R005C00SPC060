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
	.global	VDM_OpenHardware
	.type	VDM_OpenHardware, %function
VDM_OpenHardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cbnz	w19, .L5
	ldr	x1, .LC3
	mov	w2, 3247
	movk	w2, 0xfffc, lsl 16
	ldr	x4, .LC4
	mov	x0, 30
	ldr	x3, [x1]
	ldr	w1, [x3, 120]
	orr	w1, w1, 1
	and	w1, w1, w2
	str	w1, [x3, 120]
	ldr	x1, [x4, 232]
	blr	x1
.L6:
	ldr	x0, .LC5
	mov	w1, 41463
	movk	w1, 0x1, lsl 16
	ldr	w0, [x0]
	add	w0, w0, 4
	bl	MEM_WritePhyWord
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L5:
	ldr	x1, .LC7
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	b	.L6
	.size	VDM_OpenHardware, .-VDM_OpenHardware
	.align	3
.LC3:
	.xword	g_pstRegCrg
	.align	3
.LC4:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC5:
	.xword	s_ScdRegPhyBaseAddr
	.align	3
.LC7:
	.xword	.LC6
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
	cbnz	w19, .L10
	ldr	x20, .LC8
	ldr	x1, .LC9
	ldr	x0, [x20]
	ldr	x1, [x1, 168]
	ldr	w19, [x0, 120]
	cbz	x1, .L11
	mov	w0, 0
	blr	x1
.L12:
	ldr	x2, [x20]
	and	w19, w19, -2
	ldr	x1, .LC12
	mov	x0, 30
	str	w19, [x2, 120]
	ldr	x1, [x1, 232]
	blr	x1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L10:
	ldr	x1, .LC14
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L11:
	ldr	x1, .LC11
	mov	w2, 118
	mov	w0, 0
	bl	dprint_vfmw
	b	.L12
	.size	VDM_CloseHardware, .-VDM_CloseHardware
	.align	3
.LC8:
	.xword	g_pstRegCrg
	.align	3
.LC9:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC11:
	.xword	.LC10
	.align	3
.LC12:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC14:
	.xword	.LC13
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
	cbz	w19, .L17
	ldr	x1, .LC18
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L17:
	ldr	x1, .LC15
	mov	x0, 30
	ldr	x3, .LC16
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
.LC15:
	.xword	g_pstRegCrg
	.align	3
.LC16:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC18:
	.xword	.LC17
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
	cbz	w19, .L21
	ldr	x1, .LC22
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L21:
	ldr	x1, .LC19
	mov	x0, 30
	ldr	x3, .LC20
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
.LC19:
	.xword	g_pstRegCrg
	.align	3
.LC20:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC22:
	.xword	.LC21
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
	cbnz	w19, .L23
	ldr	x0, .LC23
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	and	w0, w0, -33
	str	w0, [x1, 120]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L23:
	ldr	x1, .LC25
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCD_OpenHardware, .-SCD_OpenHardware
	.align	3
.LC23:
	.xword	g_pstRegCrg
	.align	3
.LC25:
	.xword	.LC24
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
	cbnz	w19, .L26
	ldr	x0, .LC26
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	orr	w0, w0, 32
	str	w0, [x1, 120]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L26:
	ldr	x1, .LC28
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	SCD_CloseHardware, .-SCD_CloseHardware
	.align	3
.LC26:
	.xword	g_pstRegCrg
	.align	3
.LC28:
	.xword	.LC27
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
	ldr	x0, .LC29
	ldr	w3, [x29, 60]
	add	x1, x0, 128
	ldr	w0, [x0, w19, sxtw 2]
	stp	w21, w0, [x29, 64]
	ldrb	w0, [x1, w19, sxtw]
	stp	w20, w3, [x29, 72]
	cmp	w0, 1
	beq	.L30
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L30:
	add	x0, x29, 64
	bl	HI_DRV_LD_Notify_Event
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDEC_Lowdelay_Event_Time, .-VDEC_Lowdelay_Event_Time
	.align	3
.LC29:
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
	ldr	x3, .LC31
	mov	x2, 336
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	ldr	x6, .LC32
	ldr	x5, .LC33
	ldr	x4, .LC34
	ldr	x3, .LC35
	ldr	x2, .LC36
	ldr	x1, .LC37
	ldr	x8, .LC38
	ldr	x0, .LC39
	stp	x6, x5, [x19]
	stp	x4, x3, [x19, 16]
	stp	x2, x1, [x19, 32]
	stp	x8, x0, [x19, 48]
	ldr	x7, .LC40
	ldr	x5, .LC42
	ldr	x4, .LC43
	ldr	x3, .LC44
	ldr	x2, .LC45
	ldr	x1, .LC46
	ldr	x0, .LC47
	ldr	x6, .LC41
	stp	x4, x3, [x19, 112]
	str	x7, [x19, 64]
	stp	x6, x5, [x19, 96]
	str	x2, [x19, 128]
	str	x1, [x19, 152]
	str	x0, [x19, 328]
	ldr	x6, .LC48
	ldr	x5, .LC49
	ldr	x4, .LC50
	ldr	x3, .LC51
	ldr	x2, .LC52
	ldr	x1, .LC53
	ldr	x8, .LC54
	ldr	x0, .LC55
	stp	x6, x5, [x19, 136]
	stp	x4, x3, [x19, 160]
	stp	x2, x1, [x19, 176]
	stp	x8, x0, [x19, 192]
	ldr	x7, .LC56
	ldr	x5, .LC58
	ldr	x4, .LC59
	ldr	x3, .LC60
	ldr	x2, .LC61
	ldr	x1, .LC62
	ldr	x0, .LC63
	ldr	x6, .LC57
	stp	x4, x3, [x19, 232]
	stp	x2, x1, [x19, 248]
	str	x7, [x19, 208]
	stp	x6, x5, [x19, 216]
	str	x0, [x19, 264]
	ldr	x6, .LC64
	ldr	x5, .LC65
	ldr	x4, .LC66
	ldr	x3, .LC67
	ldr	x2, .LC68
	ldr	x1, .LC69
	ldr	x0, .LC70
	str	x3, [x19, 88]
	stp	x6, x5, [x19, 272]
	stp	x4, x2, [x19, 288]
	stp	x1, x0, [x19, 312]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_InitHalInterface, .-PDT_InitHalInterface
	.align	3
.LC31:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC32:
	.xword	VDM_SetClockSkip
	.align	3
.LC33:
	.xword	VDM_OpenHardware
	.align	3
.LC34:
	.xword	VDM_CloseHardware
	.align	3
.LC35:
	.xword	DSP_OpenHardware
	.align	3
.LC36:
	.xword	DSP_CloseHardware
	.align	3
.LC37:
	.xword	SCD_OpenHardware
	.align	3
.LC38:
	.xword	SCD_CloseHardware
	.align	3
.LC39:
	.xword	BPD_OpenHardware
	.align	3
.LC40:
	.xword	BPD_CloseHardware
	.align	3
.LC41:
	.xword	VDMHAL_V4R3C1_GetHalMemSize
	.align	3
.LC42:
	.xword	VDMHAL_V4R3C1_CalcFsSize
	.align	3
.LC43:
	.xword	VDMHAL_V4R3C1_OpenHAL
	.align	3
.LC44:
	.xword	VDMHAL_V4R3C1_CloseHAL
	.align	3
.LC45:
	.xword	VDMHAL_V4R3C1_ArrangeMem
	.align	3
.LC46:
	.xword	VDMHAL_V4R3C1_ResetVdm
	.align	3
.LC47:
	.xword	VDMHAL_V4R3C1_GetRpuSize
	.align	3
.LC48:
	.xword	VDMHAL_V4R3C1_SetSmmuPageTableAddr
	.align	3
.LC49:
	.xword	VDMHAL_V4R3C1_EnableSmmu
	.align	3
.LC50:
	.xword	VDMHAL_V4R3C1_GlbReset
	.align	3
.LC51:
	.xword	VDMHAL_V4R3C1_GlbResetX
	.align	3
.LC52:
	.xword	VDMHAL_V4R3C1_ClearIntState
	.align	3
.LC53:
	.xword	VDMHAL_V4R3C1_ClearMMUIntState
	.align	3
.LC54:
	.xword	VDMHAL_V4R3C1_MaskInt
	.align	3
.LC55:
	.xword	VDMHAL_V4R3C1_EnableInt
	.align	3
.LC56:
	.xword	VDMHAL_V4R3C1_CheckReg
	.align	3
.LC57:
	.xword	VDMHAL_V4R3C1_ReadMMUMask
	.align	3
.LC58:
	.xword	VDMHAL_V4R3C1_WriteMMUMask
	.align	3
.LC59:
	.xword	VDMHAL_V4R3C1_StartHwRepair
	.align	3
.LC60:
	.xword	VDMHAL_V4R3C1_StartHwDecode
	.align	3
.LC61:
	.xword	VDMHAL_V4R3C1_PrepareDec
	.align	3
.LC62:
	.xword	VDMHAL_V4R3C1_IsVdmReady
	.align	3
.LC63:
	.xword	VDMHAL_V4R3C1_IsVdmRun
	.align	3
.LC64:
	.xword	VDMHAL_V4R3C1_PrepareRepair
	.align	3
.LC65:
	.xword	VDMHAL_V4R3C1_MakeDecReport
	.align	3
.LC66:
	.xword	VDMHAL_V4R3C1_UpdateHardwareInfo
	.align	3
.LC67:
	.xword	VDMHAL_V4R3C1_GetCharacter
	.align	3
.LC68:
	.xword	VDMHAL_V4R3C1_WriteBigTitle1DYuv
	.align	3
.LC69:
	.xword	VDMHAL_V4R3C1_IsVdhDecOver
	.align	3
.LC70:
	.xword	VDMHAL_V4R3C1_IsVdhPartDecOver
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
	ldr	x3, .LC71
	mov	x2, 148
	mov	w1, 0
	mov	x0, x19
	ldr	x3, [x3, 96]
	blr	x3
	mov	w3, 32
	mov	w2, 50
	mov	w1, 2304
	mov	w0, 3
	stp	w3, w2, [x19]
	mov	w8, 4096
	mov	w7, 424673280
	stp	w8, w1, [x19, 8]
	mov	w6, 2
	mov	w5, 6
	stp	w0, w6, [x19, 24]
	mov	w4, 8
	mov	w3, 9
	mov	w2, 1
	mov	w1, 5
	mov	w0, 11
	mov	w8, 10
	stp	w5, w4, [x19, 32]
	stp	w3, w2, [x19, 40]
	stp	w7, wzr, [x19, 16]
	stp	w1, w8, [x19, 48]
	mov	w7, 12
	mov	w6, 13
	stp	w0, w7, [x19, 56]
	mov	w5, 15
	mov	w4, 16
	stp	w6, w5, [x19, 64]
	str	w4, [x19, 72]
	mov	w3, 17
	mov	w2, 19
	mov	w1, 20
	stp	w3, w2, [x19, 76]
	mov	w0, 22
	stp	w1, w0, [x19, 84]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_GetVdecCapability, .-PDT_GetVdecCapability
	.align	3
.LC71:
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
	cbnz	w19, .L37
	mov	x0, x20
	bl	PDT_GetVdecCapability
	mov	w0, 0
.L36:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L37:
	ldr	x2, .LC72
	mov	w3, w19
	ldr	x1, .LC74
	mov	w0, 1
	bl	dprint_vfmw
	mov	w0, -1
	b	.L36
	.size	PDT_GetAttribute, .-PDT_GetAttribute
	.align	3
.LC72:
	.xword	.LANCHOR1
	.align	3
.LC74:
	.xword	.LC73
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_Init
	.type	PDT_Init, %function
PDT_Init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	x0, x19
	bl	PDT_InitHalInterface
	ldr	x0, .LC75
	ldr	x0, [x0, 88]
	cbz	x0, .L39
	blr	x0
.L39:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	PDT_Init, .-PDT_Init
	.align	3
.LC75:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	PDT_Deinit
	.type	PDT_Deinit, %function
PDT_Deinit:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	PDT_Deinit, .-PDT_Deinit
	.global	g_LowDelaySeqIndex
	.global	g_LowDelayCalcHandle
	.global	g_LowDelayCalcStat
	.global	g_ChipMaxHeight
	.global	g_ChipMaxWidth
	.section	.rodata
	.align	3
.LANCHOR1 = . + 0
	.type	__func__.51994, %object
	.size	__func__.51994, 17
__func__.51994:
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
.LC6:
	ASCII(.string	"VDM_OpenHardware failed, wrong VdhId %d\n" )
	.zero	7
.LC10:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC13:
	ASCII(.string	"VDM_CloseHardware failed, wrong VdhId %d\n" )
	.zero	6
.LC17:
	ASCII(.string	"DSP_OpenHardware failed, wrong VdhId %d\n" )
	.zero	7
.LC21:
	ASCII(.string	"DSP_CloseHardware failed, wrong VdhId %d\n" )
	.zero	6
.LC24:
	ASCII(.string	"SCD_OpenHardware Wrong ScdId %d\n" )
	.zero	7
.LC27:
	ASCII(.string	"SCD_CloseHardware Wrong ScdId %d\n" )
	.zero	6
.LC73:
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
	.type	g_LowDelaySeqIndex, %object
	.size	g_LowDelaySeqIndex, 128
g_LowDelaySeqIndex:
	.zero	128
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
