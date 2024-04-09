#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdh_module.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.global	VDH_Reset_Global
	.type	VDH_Reset_Global, %function
VDH_Reset_Global:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC0
	ldr	x1, [x19, 8]
	cbz	x1, .L2
	mov	w0, 0
	blr	x1
	ldr	x1, [x19, 168]
	cbz	x1, .L4
.L13:
	mov	w0, 0
	blr	x1
	ldr	x1, [x19, 136]
	cbz	x1, .L6
.L14:
	mov	w0, 0
	blr	x1
.L7:
	ldr	x0, [x19, 144]
	cbz	x0, .L8
	blr	x0
.L9:
	ldr	x1, [x19, 16]
	cbz	x1, .L10
	mov	w0, 0
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L10:
	ldr	x1, .LC2
	mov	w2, 34
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L8:
	ldr	x1, .LC2
	mov	w2, 32
	mov	w0, 0
	bl	dprint_vfmw
	b	.L9
	.p2align 3
.L2:
	ldr	x1, .LC2
	mov	w2, 28
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x19, 168]
	cbnz	x1, .L13
	.p2align 2
.L4:
	ldr	x1, .LC2
	mov	w2, 29
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x1, [x19, 136]
	cbnz	x1, .L14
	.p2align 2
.L6:
	ldr	x1, .LC2
	mov	w2, 31
	mov	w0, 0
	bl	dprint_vfmw
	b	.L7
	.size	VDH_Reset_Global, .-VDH_Reset_Global
	.align	3
.LC0:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC2:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Start_Mfde_Repair
	.type	VDH_Start_Mfde_Repair, %function
VDH_Start_Mfde_Repair:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	ldrb	w19, [x20]
	bl	MEM_Phy2Vir
	cbz	x0, .L19
	cbnz	w19, .L18
	ldr	x19, .LC6
	mov	w1, 3075
	ldr	w3, [x20, 108]
	movk	w1, 0x30, lsl 16
	ldr	x2, .LC7
	ldr	x0, [x19]
	str	w3, [x0, 16]
	ldr	w3, [x20, 124]
	str	w3, [x0, 36]
	ldr	w3, [x20, 104]
	str	w3, [x0, 12]
	str	w1, [x0, 60]
	str	w1, [x0, 64]
	str	w1, [x0, 68]
	str	w1, [x0, 72]
	str	w1, [x0, 76]
	str	w1, [x0, 80]
	str	w1, [x0, 84]
	ldr	w1, [x20, 100]
	str	w1, [x0, 8]
	ldr	x0, [x2, 224]
	blr	x0
	ldr	x0, [x19]
	mov	w1, 1
	str	wzr, [x0]
	ldr	x0, [x19]
	str	w1, [x0]
	ldr	x0, [x19]
	str	wzr, [x0]
.L15:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L18:
	ldr	x21, .LC3
	mov	w3, w19
	ldr	x20, .LC9
	mov	w4, 1
	mov	x2, x21
	mov	w0, 32
	mov	x1, x20
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x0, .LC7
	ldr	x0, [x0, 224]
	blr	x0
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x21
	mov	x1, x20
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L19:
	ldr	x2, .LC3
	mov	w4, -121438208
	ldr	x1, .LC5
	mov	w3, w19
	bl	dprint_vfmw
	b	.L15
	.size	VDH_Start_Mfde_Repair, .-VDH_Start_Mfde_Repair
	.align	3
.LC3:
	.xword	.LANCHOR0
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC6:
	.xword	g_HwMem
	.align	3
.LC7:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC9:
	.xword	.LC8
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Start_Mfde_Decode
	.type	VDH_Start_Mfde_Decode, %function
VDH_Start_Mfde_Decode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	ldrb	w20, [x19]
	bl	MEM_Phy2Vir
	cbz	x0, .L38
	ldr	x22, .LC12
	ldr	w1, [x19, 56]
	ldr	w0, [x22]
	bl	MEM_WritePhyWord
	ldr	w0, [x22]
	ldr	w1, [x19, 64]
	add	w0, w0, 8
	bl	MEM_WritePhyWord
	cbnz	w20, .L23
	ldr	x0, .LC13
	ldr	w1, [x19, 100]
	ldr	x0, [x0]
	str	w1, [x0, 8]
	ldr	w1, [x19, 104]
	str	w1, [x0, 12]
	ldr	w1, [x19, 108]
	str	w1, [x0, 16]
	ldr	w1, [x19, 112]
	str	w1, [x0, 20]
	ldr	w1, [x19, 116]
	str	w1, [x0, 24]
	ldrb	w1, [x19, 1]
	cmp	w1, 1
	beq	.L39
.L25:
	ldr	w0, [x19, 60]
	cbz	w0, .L40
.L28:
	ldr	w0, [x22]
	add	w0, w0, 4
	bl	MEM_ReadPhyWord
	orr	w1, w0, 65536
	ldr	w0, [x22]
	add	w0, w0, 4
	bl	MEM_WritePhyWord
	cbnz	w20, .L30
.L41:
	ldr	x0, .LC13
	mov	w1, 3075
	movk	w1, 0x30, lsl 16
	ldr	x0, [x0]
	str	w1, [x0, 60]
	str	w1, [x0, 64]
	str	w1, [x0, 68]
	str	w1, [x0, 72]
	str	w1, [x0, 76]
	str	w1, [x0, 80]
	str	w1, [x0, 84]
	ldr	w1, [x19, 132]
	str	w1, [x0, 96]
	ldr	w1, [x19, 136]
	str	w1, [x0, 100]
	ldr	w1, [x19, 140]
	str	w1, [x0, 104]
	ldr	w1, [x19, 144]
	str	w1, [x0, 108]
	ldr	w1, [x19, 152]
	str	w1, [x0, 116]
	ldr	w1, [x19, 156]
	str	w1, [x0, 120]
	ldr	w1, [x19, 160]
	str	w1, [x0, 124]
	ldr	w1, [x19, 164]
	str	w1, [x0, 128]
	ldr	w1, [x19, 168]
	str	w1, [x0, 132]
	ldr	w1, [x19, 172]
	str	w1, [x0, 148]
	ldr	w1, [x19, 176]
	str	w1, [x0, 152]
	ldr	w1, [x19, 180]
	str	w1, [x0, 156]
	ldr	x0, .LC15
	ldr	x1, [x0]
	cbz	x1, .L32
.L42:
	ldr	w0, [x19, 20]
	blr	x1
.L33:
	ldr	x1, .LC17
	ldr	w3, [x19, 16]
	ldr	w0, [x22]
	ldr	x2, [x1]
	add	w0, w0, 12
	ldr	w1, [x2, 120]
	bfi	w1, w3, 8, 2
	str	w1, [x2, 120]
	ldr	w1, [x19, 68]
	bl	MEM_WritePhyWord
	cbnz	w20, .L34
	ldr	x20, .LC13
	mov	x0, 30
	ldr	w3, [x19, 120]
	ldr	x21, .LC18
	ldr	x1, [x20]
	add	x2, x1, 61440
	str	w3, [x1, 32]
	ldr	w3, [x19, 124]
	str	w3, [x1, 36]
	ldr	w3, [x19, 184]
	ldr	x1, [x21, 232]
	str	w3, [x2, 32]
	blr	x1
	ldr	x0, [x21, 224]
	blr	x0
	ldr	x0, [x20]
	mov	w1, 1
	str	wzr, [x0]
	ldr	x0, [x20]
	str	w1, [x0]
	ldr	x0, [x20]
	str	wzr, [x0]
.L35:
	ldr	w2, [x19, 8]
	mov	w1, 4
	ldr	x3, .LC19
	mov	w0, w2
	ldr	w2, [x3, w2, sxtw 2]
	bl	VDEC_Lowdelay_Event_Time
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L40:
	ldr	w0, [x22]
	add	w0, w0, 4
	bl	MEM_ReadPhyWord
	uxth	w1, w0
	ldr	w0, [x22]
	add	w0, w0, 4
	bl	MEM_WritePhyWord
	cbz	w20, .L41
.L30:
	ldr	x21, .LC10
	mov	w4, 1
	ldr	x23, .LC14
	mov	w3, w20
	add	x21, x21, 24
	mov	w0, 32
	mov	x1, x23
	mov	x2, x21
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	x1, x23
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x0, .LC15
	ldr	x1, [x0]
	cbnz	x1, .L42
.L32:
	ldr	x1, .LC16
	mov	w2, 151
	mov	w0, 0
	bl	dprint_vfmw
	b	.L33
	.p2align 3
.L23:
	ldr	x21, .LC10
	mov	w4, 1
	ldr	x23, .LC14
	mov	w3, w20
	add	x21, x21, 24
	mov	w0, 32
	mov	x1, x23
	mov	x2, x21
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w24, [x19, 1]
	cmp	w24, 1
	bne	.L25
	mov	w4, w24
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, w24
	mov	w3, w20
	mov	x2, x21
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	b	.L25
	.p2align 3
.L34:
	ldr	x21, .LC10
	mov	w3, w20
	ldr	x22, .LC14
	mov	w4, 1
	add	x21, x21, 24
	mov	w0, 32
	mov	x1, x22
	mov	x2, x21
	bl	dprint_vfmw
	mov	w3, w20
	mov	x2, x21
	mov	x1, x22
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w20
	mov	x2, x21
	mov	w4, 1
	mov	x1, x22
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x23, .LC18
	mov	x0, 30
	ldr	x1, [x23, 232]
	blr	x1
	ldr	x0, [x23, 224]
	blr	x0
	mov	w3, w20
	mov	x2, x21
	mov	x1, x22
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w20
	mov	x2, x21
	mov	x1, x22
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x21
	mov	x1, x22
	mov	w0, 32
	bl	dprint_vfmw
	b	.L35
	.p2align 3
.L39:
	ldr	w1, [x19, 128]
	str	w1, [x0, 92]
	ldr	w1, [x19, 148]
	str	w1, [x0, 112]
	ldr	w0, [x19, 60]
	cbnz	w0, .L28
	b	.L40
	.p2align 3
.L38:
	ldr	x2, .LC10
	mov	w3, w20
	ldr	x1, .LC11
	mov	w4, -121438208
	add	x2, x2, 24
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	VDH_Start_Mfde_Decode, .-VDH_Start_Mfde_Decode
	.align	3
.LC10:
	.xword	.LANCHOR0
	.align	3
.LC11:
	.xword	.LC4
	.align	3
.LC12:
	.xword	s_ScdRegPhyBaseAddr
	.align	3
.LC13:
	.xword	g_HwMem
	.align	3
.LC14:
	.xword	.LC8
	.align	3
.LC15:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC16:
	.xword	.LC1
	.align	3
.LC17:
	.xword	g_pstRegCrg
	.align	3
.LC18:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC19:
	.xword	g_LowDelaySeqIndex
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Init_Module
	.type	VDH_Init_Module, %function
VDH_Init_Module:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	bl	VDH_Reset_Global
	ldp	x29, x30, [sp], 16
	ret
	.size	VDH_Init_Module, .-VDH_Init_Module
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Start_Mfde_Module
	.type	VDH_Start_Mfde_Module, %function
VDH_Start_Mfde_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L48
	ldrb	w0, [x19, 2]
	cmp	w0, 1
	mov	x0, x19
	beq	.L49
	bl	VDH_Start_Mfde_Decode
.L44:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L49:
	bl	VDH_Start_Mfde_Repair
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L48:
	ldr	x2, .LC23
	mov	w0, 0
	ldr	x3, .LC22
	ldr	x1, .LC25
	add	x2, x2, 48
	bl	dprint_vfmw
	b	.L44
	.size	VDH_Start_Mfde_Module, .-VDH_Start_Mfde_Module
	.align	3
.LC22:
	.xword	.LC21
	.align	3
.LC23:
	.xword	.LANCHOR0
	.align	3
.LC25:
	.xword	.LC24
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Start_Scd_Module
	.type	VDH_Start_Scd_Module, %function
VDH_Start_Scd_Module:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L58
	mov	w0, 49152
	ldrb	w20, [x19]
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_Phy2Vir
	cbz	x0, .L59
	mov	w0, w20
	bl	ResetSCD
	ldr	x21, .LC31
	ldr	w1, [x19, 24]
	ldr	w0, [x21, w20, uxtw 2]
	add	w0, w0, 2052
	bl	MEM_WritePhyWord
	ldr	w0, [x21, w20, uxtw 2]
	ldr	w1, [x19, 28]
	add	w0, w0, 2056
	bl	MEM_WritePhyWord
	ldr	w0, [x21, w20, uxtw 2]
	ldr	w1, [x19, 32]
	add	w0, w0, 2060
	bl	MEM_WritePhyWord
	ldr	w0, [x21, w20, uxtw 2]
	ldr	w1, [x19, 36]
	add	w0, w0, 2064
	bl	MEM_WritePhyWord
	ldr	w0, [x21, w20, uxtw 2]
	ldr	w1, [x19, 40]
	add	w0, w0, 2068
	bl	MEM_WritePhyWord
	ldr	w0, [x21, w20, uxtw 2]
	ldr	w1, [x19, 44]
	add	w0, w0, 2072
	bl	MEM_WritePhyWord
	ldr	w0, [x21, w20, uxtw 2]
	ldr	w1, [x19, 52]
	add	w0, w0, 2080
	bl	MEM_WritePhyWord
	ldrb	w0, [x19, 1]
	cbnz	w0, .L60
.L54:
	ldr	w0, [x21, w20, uxtw 2]
	ldr	w1, [x19, 48]
	add	w0, w0, 2076
	bl	MEM_WritePhyWord
	ldr	w0, [x21, w20, uxtw 2]
	mov	w1, 0
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
	ldr	w0, [x21, w20, uxtw 2]
	mov	w1, 1
	add	w0, w0, 2048
	bl	MEM_WritePhyWord
.L50:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L60:
	ldr	w0, [x21, w20, uxtw 2]
	ldr	w1, [x19, 56]
	bl	MEM_WritePhyWord
	b	.L54
	.p2align 3
.L58:
	ldr	x2, .LC27
	mov	w0, 0
	ldr	x3, .LC26
	ldr	x1, .LC28
	add	x2, x2, 72
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L59:
	ldr	x2, .LC27
	mov	w3, 49152
	ldr	x1, .LC30
	movk	w3, 0xf8c3, lsl 16
	add	x2, x2, 72
	bl	dprint_vfmw
	b	.L50
	.size	VDH_Start_Scd_Module, .-VDH_Start_Scd_Module
	.align	3
.LC26:
	.xword	.LC21
	.align	3
.LC27:
	.xword	.LANCHOR0
	.align	3
.LC28:
	.xword	.LC24
	.align	3
.LC30:
	.xword	.LC29
	.align	3
.LC31:
	.xword	s_ScdRegPhyBaseAddr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Record_CrgRegData
	.type	VDH_Record_CrgRegData, %function
VDH_Record_CrgRegData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	cbz	x20, .L66
	cbz	w19, .L67
	cmp	w19, 1
	beq	.L68
	ldr	x2, .LC34
	mov	w4, w21
	ldr	x1, .LC37
	mov	w3, w19
	add	x2, x2, 96
	mov	w0, 1
	bl	dprint_vfmw
.L61:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L68:
	str	w21, [x20, 4]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L67:
	str	w21, [x20]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L66:
	ldr	x2, .LC34
	mov	w0, 0
	ldr	x3, .LC33
	ldr	x1, .LC35
	add	x2, x2, 96
	bl	dprint_vfmw
	b	.L61
	.size	VDH_Record_CrgRegData, .-VDH_Record_CrgRegData
	.align	3
.LC33:
	.xword	.LC32
	.align	3
.LC34:
	.xword	.LANCHOR0
	.align	3
.LC35:
	.xword	.LC24
	.align	3
.LC37:
	.xword	.LC36
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Record_ScdRegData
	.type	VDH_Record_ScdRegData, %function
VDH_Record_ScdRegData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	cbz	x20, .L97
	cmp	w19, 2068
	beq	.L73
	bls	.L98
	cmp	w19, 2088
	beq	.L85
	bls	.L99
	cmp	w19, 2096
	beq	.L90
	bls	.L100
	cmp	w19, 2100
	beq	.L93
	cmp	w19, 2104
	bne	.L72
	str	w21, [x20, 64]
.L69:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L98:
	cmp	w19, 12
	beq	.L75
	bls	.L101
	cmp	w19, 2056
	beq	.L80
	bls	.L102
	cmp	w19, 2060
	beq	.L83
	cmp	w19, 2064
	bne	.L72
	str	w21, [x20, 12]
	b	.L69
	.p2align 3
.L90:
	str	w21, [x20, 56]
	b	.L69
	.p2align 3
.L80:
	str	w21, [x20, 4]
	b	.L69
	.p2align 3
.L99:
	cmp	w19, 2076
	beq	.L87
	cmp	w19, 2080
	beq	.L88
	cmp	w19, 2072
	beq	.L103
.L72:
	ldr	x2, .LC39
	mov	w4, w21
	ldr	x1, .LC41
	mov	w3, w19
	add	x2, x2, 120
	mov	w0, 1
	bl	dprint_vfmw
	b	.L69
	.p2align 3
.L103:
	str	w21, [x20, 20]
	b	.L69
	.p2align 3
.L101:
	cmp	w19, 4
	beq	.L77
	cmp	w19, 8
	beq	.L78
	cbnz	w19, .L72
	str	w21, [x20, 32]
	b	.L69
	.p2align 3
.L100:
	cmp	w19, 2092
	bne	.L72
	str	w21, [x20, 52]
	b	.L69
	.p2align 3
.L102:
	cmp	w19, 2052
	bne	.L72
	str	w21, [x20]
	b	.L69
	.p2align 3
.L87:
	str	w21, [x20, 24]
	b	.L69
	.p2align 3
.L85:
	str	w21, [x20, 48]
	b	.L69
	.p2align 3
.L93:
	str	w21, [x20, 60]
	b	.L69
	.p2align 3
.L83:
	str	w21, [x20, 8]
	b	.L69
	.p2align 3
.L73:
	str	w21, [x20, 16]
	b	.L69
	.p2align 3
.L78:
	str	w21, [x20, 40]
	b	.L69
	.p2align 3
.L77:
	str	w21, [x20, 36]
	b	.L69
	.p2align 3
.L88:
	str	w21, [x20, 28]
	b	.L69
	.p2align 3
.L75:
	str	w21, [x20, 44]
	b	.L69
	.p2align 3
.L97:
	ldr	x2, .LC39
	mov	w0, 0
	ldr	x3, .LC38
	ldr	x1, .LC40
	add	x2, x2, 120
	bl	dprint_vfmw
	b	.L69
	.size	VDH_Record_ScdRegData, .-VDH_Record_ScdRegData
	.align	3
.LC38:
	.xword	.LC32
	.align	3
.LC39:
	.xword	.LANCHOR0
	.align	3
.LC40:
	.xword	.LC24
	.align	3
.LC41:
	.xword	.LC36
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Record_MfdeRegData
	.type	VDH_Record_MfdeRegData, %function
VDH_Record_MfdeRegData:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	w19, w1
	mov	w21, w2
	bl	_mcount
	cbz	x20, .L165
	cmp	w19, 92
	beq	.L108
	bls	.L166
	cmp	w19, 124
	beq	.L120
	bhi	.L121
	cmp	w19, 108
	beq	.L122
	bls	.L167
	cmp	w19, 116
	beq	.L127
	cmp	w19, 120
	beq	.L128
	cmp	w19, 112
	bne	.L107
	str	w21, [x20, 48]
	b	.L104
	.p2align 3
.L121:
	cmp	w19, 148
	beq	.L130
	bls	.L168
	cmp	w19, 156
	beq	.L134
	mov	w0, 61472
	cmp	w19, w0
	beq	.L135
	cmp	w19, 152
	bne	.L107
	str	w21, [x20, 76]
	b	.L104
	.p2align 3
.L166:
	cmp	w19, 36
	beq	.L110
	bhi	.L111
	cmp	w19, 16
	beq	.L112
	bls	.L169
	cmp	w19, 24
	beq	.L116
	cmp	w19, 32
	beq	.L117
	cmp	w19, 20
	bne	.L107
	str	w21, [x20, 12]
	b	.L104
	.p2align 3
.L167:
	cmp	w19, 100
	beq	.L124
	cmp	w19, 104
	beq	.L125
	cmp	w19, 96
	beq	.L170
	.p2align 2
.L107:
	ldr	x2, .LC43
	mov	w4, w21
	ldr	x1, .LC45
	mov	w3, w19
	add	x2, x2, 144
	mov	w0, 1
	bl	dprint_vfmw
	b	.L104
	.p2align 3
.L168:
	cmp	w19, 132
	beq	.L132
	cmp	w19, 144
	beq	.L104
	cmp	w19, 128
	bne	.L107
	str	w21, [x20, 64]
.L104:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L169:
	cmp	w19, 8
	beq	.L114
	cmp	w19, 12
	bne	.L107
	str	w21, [x20, 4]
	b	.L104
	.p2align 3
.L114:
	str	w21, [x20]
	b	.L104
	.p2align 3
.L125:
	str	w21, [x20, 40]
	b	.L104
	.p2align 3
.L135:
	str	w21, [x20, 84]
	b	.L104
	.p2align 3
.L132:
	str	w21, [x20, 68]
	b	.L104
	.p2align 3
.L128:
	str	w21, [x20, 56]
	b	.L104
	.p2align 3
.L117:
	str	w21, [x20, 20]
	b	.L104
	.p2align 3
.L111:
	cmp	w19, 72
	beq	.L104
	bhi	.L119
	cmp	w19, 64
	beq	.L104
	cmp	w19, 68
	beq	.L104
	cmp	w19, 60
	bne	.L107
	b	.L104
	.p2align 3
.L165:
	ldr	x2, .LC43
	mov	w0, 0
	ldr	x3, .LC42
	ldr	x1, .LC44
	add	x2, x2, 144
	bl	dprint_vfmw
	b	.L104
	.p2align 3
.L124:
	str	w21, [x20, 36]
	b	.L104
	.p2align 3
.L134:
	str	w21, [x20, 80]
	b	.L104
	.p2align 3
.L120:
	str	w21, [x20, 60]
	b	.L104
	.p2align 3
.L108:
	str	w21, [x20, 28]
	b	.L104
	.p2align 3
.L112:
	str	w21, [x20, 8]
	b	.L104
	.p2align 3
.L110:
	str	w21, [x20, 24]
	b	.L104
	.p2align 3
.L122:
	str	w21, [x20, 44]
	b	.L104
	.p2align 3
.L130:
	str	w21, [x20, 72]
	b	.L104
	.p2align 3
.L170:
	str	w21, [x20, 32]
	b	.L104
	.p2align 3
.L127:
	str	w21, [x20, 52]
	b	.L104
	.p2align 3
.L116:
	str	w21, [x20, 16]
	b	.L104
	.p2align 3
.L119:
	cmp	w19, 80
	beq	.L104
	cmp	w19, 84
	beq	.L104
	cmp	w19, 76
	bne	.L107
	b	.L104
	.size	VDH_Record_MfdeRegData, .-VDH_Record_MfdeRegData
	.align	3
.LC42:
	.xword	.LC32
	.align	3
.LC43:
	.xword	.LANCHOR0
	.align	3
.LC44:
	.xword	.LC24
	.align	3
.LC45:
	.xword	.LC36
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Init_Hardware
	.type	VDH_Init_Hardware, %function
VDH_Init_Hardware:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC46
	ldr	x1, [x19, 72]
	cbz	x1, .L172
	mov	w0, 0
	blr	x1
.L172:
	ldr	x1, [x19, 136]
	cbz	x1, .L173
	mov	w0, 0
	blr	x1
.L174:
	ldr	x0, [x19, 144]
	cbz	x0, .L175
	blr	x0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L175:
	ldr	x1, .LC47
	mov	w2, 455
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L173:
	ldr	x1, .LC47
	mov	w2, 454
	mov	w0, 0
	bl	dprint_vfmw
	b	.L174
	.size	VDH_Init_Hardware, .-VDH_Init_Hardware
	.align	3
.LC46:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC47:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Enable_Scd_Module
	.type	VDH_Enable_Scd_Module, %function
VDH_Enable_Scd_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC48
	ldr	x1, [x0, 40]
	cbz	x1, .L181
	mov	w0, w19
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L181:
	ldr	x1, .LC49
	mov	w2, 467
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Enable_Scd_Module, .-VDH_Enable_Scd_Module
	.align	3
.LC48:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC49:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Disable_Scd_Module
	.type	VDH_Disable_Scd_Module, %function
VDH_Disable_Scd_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC50
	ldr	x1, [x0, 48]
	cbz	x1, .L184
	mov	w0, w19
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L184:
	ldr	x1, .LC51
	mov	w2, 478
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Disable_Scd_Module, .-VDH_Disable_Scd_Module
	.align	3
.LC50:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC51:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Reset_Scd_Module
	.type	VDH_Reset_Scd_Module, %function
VDH_Reset_Scd_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, w19
	bl	ResetSCD
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Reset_Scd_Module, .-VDH_Reset_Scd_Module
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Enable_Mfde_Module
	.type	VDH_Enable_Mfde_Module, %function
VDH_Enable_Mfde_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC52
	ldr	x1, [x0, 8]
	cbz	x1, .L188
	mov	w0, w19
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L188:
	ldr	x1, .LC53
	mov	w2, 499
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Enable_Mfde_Module, .-VDH_Enable_Mfde_Module
	.align	3
.LC52:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC53:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Disable_Mfde_Module
	.type	VDH_Disable_Mfde_Module, %function
VDH_Disable_Mfde_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC54
	ldr	x1, [x0, 16]
	cbz	x1, .L191
	mov	w0, w19
	blr	x1
	mov	w0, w19
	bl	SCDDRV_SetStateIdle
	mov	w0, w19
	bl	VDMDRV_SetStateIdle
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L191:
	ldr	x1, .LC55
	mov	w2, 509
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, w19
	bl	SCDDRV_SetStateIdle
	mov	w0, w19
	bl	VDMDRV_SetStateIdle
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Disable_Mfde_Module, .-VDH_Disable_Mfde_Module
	.align	3
.LC54:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC55:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Reset_Mfde_Module
	.type	VDH_Reset_Mfde_Module, %function
VDH_Reset_Mfde_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC56
	ldr	x1, [x0, 152]
	cbz	x1, .L194
	mov	w0, w19
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L194:
	ldr	x1, .LC57
	mov	w2, 521
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Reset_Mfde_Module, .-VDH_Reset_Mfde_Module
	.align	3
.LC56:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC57:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Enable_Bpd_Module
	.type	VDH_Enable_Bpd_Module, %function
VDH_Enable_Bpd_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	bl	_mcount
	ldr	x19, .LC58
	ldr	x1, [x19, 8]
	cbz	x1, .L197
	mov	w0, w20
	blr	x1
.L198:
	ldr	x1, [x19, 56]
	cbz	x1, .L196
	mov	w0, w20
	blr	x1
.L196:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L197:
	ldr	x1, .LC59
	mov	w2, 531
	mov	w0, 0
	bl	dprint_vfmw
	b	.L198
	.size	VDH_Enable_Bpd_Module, .-VDH_Enable_Bpd_Module
	.align	3
.LC58:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC59:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Disable_Bpd_Module
	.type	VDH_Disable_Bpd_Module, %function
VDH_Disable_Bpd_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC60
	ldr	x1, [x0, 64]
	cbz	x1, .L203
	mov	w0, w19
	blr	x1
.L203:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Disable_Bpd_Module, .-VDH_Disable_Bpd_Module
	.align	3
.LC60:
	.xword	g_vdm_hal_fun_ptr
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Enable_Dsp_Module
	.type	VDH_Enable_Dsp_Module, %function
VDH_Enable_Dsp_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC61
	ldr	x1, [x0, 24]
	cbz	x1, .L209
	mov	w0, w19
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L209:
	ldr	x1, .LC62
	mov	w2, 552
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Enable_Dsp_Module, .-VDH_Enable_Dsp_Module
	.align	3
.LC61:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC62:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Disable_Dsp_Module
	.type	VDH_Disable_Dsp_Module, %function
VDH_Disable_Dsp_Module:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC63
	ldr	x1, [x0, 32]
	cbz	x1, .L212
	mov	w0, w19
	blr	x1
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L212:
	ldr	x1, .LC64
	mov	w2, 562
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Disable_Dsp_Module, .-VDH_Disable_Dsp_Module
	.align	3
.LC63:
	.xword	g_vdm_hal_fun_ptr
	.align	3
.LC64:
	.xword	.LC1
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDH_Load_Dsp_Code
	.type	VDH_Load_Dsp_Code, %function
VDH_Load_Dsp_Code:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	mov	w1, w20
	mov	w0, w19
	bl	SCDDRV_LoadDspCode
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDH_Load_Dsp_Code, .-VDH_Load_Dsp_Code
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.45625, %object
	.size	__func__.45625, 22
__func__.45625:
	.string	"VDH_Start_Mfde_Repair"
	.zero	2
	.type	__func__.45633, %object
	.size	__func__.45633, 22
__func__.45633:
	.string	"VDH_Start_Mfde_Decode"
	.zero	2
	.type	__func__.45640, %object
	.size	__func__.45640, 22
__func__.45640:
	.string	"VDH_Start_Mfde_Module"
	.zero	2
	.type	__func__.45646, %object
	.size	__func__.45646, 21
__func__.45646:
	.string	"VDH_Start_Scd_Module"
	.zero	3
	.type	__func__.45652, %object
	.size	__func__.45652, 22
__func__.45652:
	.string	"VDH_Record_CrgRegData"
	.zero	2
	.type	__func__.45658, %object
	.size	__func__.45658, 22
__func__.45658:
	.string	"VDH_Record_ScdRegData"
	.zero	2
	.type	__func__.45683, %object
	.size	__func__.45683, 23
__func__.45683:
	.string	"VDH_Record_MfdeRegData"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC1:
	ASCII(.string	"VDMHAL_NULL_FUN_PRINT,L%d\n" )
	.zero	5
.LC4:
	ASCII(.string	"%s: map mfde %d register 0x%x failed!\n" )
	.zero	1
.LC8:
	ASCII(.string	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC21:
	ASCII(.string	"pTask is null" )
	.zero	2
.LC24:
	ASCII(.string	"%s: %s\n" )
.LC29:
	ASCII(.string	"%s: map scd register 0x%x failed!\n" )
	.zero	5
.LC32:
	ASCII(.string	"pRegMap is null" )
.LC36:
	ASCII(.string	"%s: unrecord reg 0x%x data %d!\n" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
