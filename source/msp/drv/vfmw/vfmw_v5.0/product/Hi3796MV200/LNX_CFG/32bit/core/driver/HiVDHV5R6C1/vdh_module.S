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
	.file	"vdh_module.c"
	.text
	.align	2
	.global	VDH_Reset_Global
	.type	VDH_Reset_Global, %function
VDH_Reset_Global:
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
	ldr	r4, .L14
	ldr	r3, [r4, #4]
	cmp	r3, #0
	beq	.L2
	mov	r0, #0
	blx	r3
	ldr	r3, [r4, #84]
	cmp	r3, #0
	beq	.L4
.L12:
	mov	r0, #0
	blx	r3
	ldr	r3, [r4, #68]
	cmp	r3, #0
	beq	.L6
.L13:
	mov	r0, #0
	blx	r3
.L7:
	ldr	r0, [r4, #72]
	cmp	r0, #0
	beq	.L8
	blx	r0
.L9:
	ldr	r3, [r4, #8]
	cmp	r3, #0
	beq	.L10
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L10:
	mov	r0, r3
	mov	r2, #34
	ldr	r1, .L14+4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L8:
	mov	r2, #32
	ldr	r1, .L14+4
	bl	dprint_vfmw
	b	.L9
.L2:
	mov	r0, r3
	mov	r2, #28
	ldr	r1, .L14+4
	bl	dprint_vfmw
	ldr	r3, [r4, #84]
	cmp	r3, #0
	bne	.L12
.L4:
	mov	r0, r3
	mov	r2, #29
	ldr	r1, .L14+4
	bl	dprint_vfmw
	ldr	r3, [r4, #68]
	cmp	r3, #0
	bne	.L13
.L6:
	mov	r0, r3
	mov	r2, #31
	ldr	r1, .L14+4
	bl	dprint_vfmw
	b	.L7
.L15:
	.align	2
.L14:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Reset_Global, .-VDH_Reset_Global
	.align	2
	.global	VDH_Start_Mfde_Repair
	.type	VDH_Start_Mfde_Repair, %function
VDH_Start_Mfde_Repair:
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
	mov	r6, #0
	movt	r6, 63683
	ldrb	r4, [r0]	@ zero_extendqisi2
	mov	r5, r0
	mov	r0, r6
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L20
	cmp	r4, #0
	bne	.L19
	ldr	r6, .L21
	movw	r2, #3075
	ldr	r0, [r5, #108]
	movt	r2, 48
	ldr	r1, .L21+4
	ldr	r3, [r6]
	str	r0, [r3, #16]
	ldr	r0, [r5, #124]
	str	r0, [r3, #36]
	ldr	r0, [r5, #104]
	str	r0, [r3, #12]
	str	r2, [r3, #60]
	str	r2, [r3, #64]
	str	r2, [r3, #68]
	str	r2, [r3, #72]
	str	r2, [r3, #76]
	str	r2, [r3, #80]
	str	r2, [r3, #84]
	ldr	r2, [r5, #100]
	str	r2, [r3, #8]
	ldr	r3, [r1, #112]
	blx	r3
	ldr	r3, [r6]
	mov	r2, #1
	str	r4, [r3]
	ldr	r3, [r6]
	str	r2, [r3]
	ldr	r3, [r6]
	str	r4, [r3]
.L16:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L19:
	mov	r5, #1
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	ldr	r2, .L21+8
	mov	r0, #32
	ldr	r1, .L21+12
	str	r5, [sp]
	bl	dprint_vfmw
	ldr	r3, .L21+4
	ldr	r3, [r3, #112]
	blx	r3
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	mov	r3, r4
	str	r5, [sp]
	mov	r0, #32
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	bl	dprint_vfmw
	str	r5, [sp]
	mov	r3, r4
	ldr	r2, .L21+8
	ldr	r1, .L21+12
	mov	r0, #32
	bl	dprint_vfmw
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L20:
	str	r6, [sp]
	mov	r3, r4
	ldr	r2, .L21+8
	ldr	r1, .L21+16
	bl	dprint_vfmw
	b	.L16
.L22:
	.align	2
.L21:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	VDH_Start_Mfde_Repair, .-VDH_Start_Mfde_Repair
	.align	2
	.global	VDH_Start_Mfde_Decode
	.type	VDH_Start_Mfde_Decode, %function
VDH_Start_Mfde_Decode:
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
	mov	r6, #0
	movt	r6, 63683
	ldrb	r5, [r0]	@ zero_extendqisi2
	mov	r4, r0
	mov	r0, r6
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L42
	ldr	r6, .L46
	ldr	r1, [r4, #56]
	ldr	r0, [r6]
	bl	MEM_WritePhyWord
	ldr	r0, [r6]
	ldr	r1, [r4, #64]
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	cmp	r5, #0
	bne	.L26
	ldr	r3, .L46+4
	ldr	r2, [r4, #100]
	ldr	r3, [r3]
	str	r2, [r3, #8]
	ldr	r2, [r4, #104]
	str	r2, [r3, #12]
	ldr	r2, [r4, #108]
	str	r2, [r3, #16]
	ldr	r2, [r4, #112]
	str	r2, [r3, #20]
	ldr	r2, [r4, #116]
	str	r2, [r3, #24]
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L43
.L28:
	ldr	r3, [r4, #60]
	ldr	r0, [r6]
	cmp	r3, #0
	add	r0, r0, #4
	beq	.L44
	bl	MEM_ReadPhyWord
	orr	r1, r0, #65536
.L32:
	ldr	r0, [r6]
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	cmp	r5, #0
	bne	.L33
	ldr	r3, .L46+4
	movw	r2, #3075
	movt	r2, 48
	ldr	r3, [r3]
	str	r2, [r3, #60]
	str	r2, [r3, #64]
	str	r2, [r3, #68]
	str	r2, [r3, #72]
	str	r2, [r3, #76]
	str	r2, [r3, #80]
	str	r2, [r3, #84]
	ldr	r2, [r4, #132]
	str	r2, [r3, #96]
	ldr	r2, [r4, #136]
	str	r2, [r3, #100]
	ldr	r2, [r4, #140]
	str	r2, [r3, #104]
	ldr	r2, [r4, #144]
	str	r2, [r3, #108]
	ldr	r2, [r4, #152]
	str	r2, [r3, #116]
	ldr	r2, [r4, #156]
	str	r2, [r3, #120]
	ldr	r2, [r4, #160]
	str	r2, [r3, #124]
	ldr	r2, [r4, #164]
	str	r2, [r3, #128]
	ldr	r2, [r4, #168]
	str	r2, [r3, #132]
	ldr	r2, [r4, #172]
	str	r2, [r3, #148]
	ldr	r2, [r4, #176]
	str	r2, [r3, #152]
	ldr	r2, [r4, #180]
	str	r2, [r3, #156]
	ldr	r3, .L46+8
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L35
.L45:
	ldr	r0, [r4, #20]
	blx	r3
.L36:
	ldr	r3, .L46+12
	ldr	r1, [r4, #16]
	ldr	r0, [r6]
	ldr	r2, [r3]
	add	r0, r0, #12
	ldr	r3, [r2, #120]
	bfi	r3, r1, #8, #2
	str	r3, [r2, #120]
	ldr	r1, [r4, #68]
	bl	MEM_WritePhyWord
	cmp	r5, #0
	bne	.L37
	ldr	r6, .L46+4
	mov	r0, #30
	ldr	r1, [r4, #120]
	ldr	r7, .L46+16
	ldr	r3, [r6]
	add	r2, r3, #61440
	str	r1, [r3, #32]
	ldr	r1, [r4, #124]
	str	r1, [r3, #36]
	ldr	r1, [r4, #184]
	ldr	r3, [r7, #116]
	str	r1, [r2, #32]
	blx	r3
	ldr	r3, [r7, #112]
	blx	r3
	ldr	r3, [r6]
	mov	r2, #1
	str	r5, [r3]
	ldr	r3, [r6]
	str	r2, [r3]
	ldr	r3, [r6]
	str	r5, [r3]
.L38:
	ldr	r3, [r4, #8]
	mov	r1, #4
	ldr	r2, .L46+20
	mov	r0, r3
	ldr	r2, [r2, r3, asl #2]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VDEC_Lowdelay_Event_Time
.L44:
	bl	MEM_ReadPhyWord
	bic	r1, r0, #65536
	b	.L32
.L26:
	mov	r7, #1
	mov	r3, r5
	str	r7, [sp]
	mov	r0, #32
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	bl	dprint_vfmw
	str	r7, [sp]
	mov	r3, r5
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	mov	r0, #32
	bl	dprint_vfmw
	str	r7, [sp]
	mov	r3, r5
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	mov	r0, #32
	bl	dprint_vfmw
	str	r7, [sp]
	mov	r3, r5
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	mov	r0, #32
	bl	dprint_vfmw
	str	r7, [sp]
	mov	r3, r5
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r7, [r4, #1]	@ zero_extendqisi2
	cmp	r7, #1
	bne	.L28
	mov	r3, r5
	str	r7, [sp]
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	bl	dprint_vfmw
	str	r7, [sp]
	mov	r3, r5
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	mov	r0, #32
	bl	dprint_vfmw
	b	.L28
.L37:
	mov	r6, #1
	mov	r3, r5
	ldr	r7, .L46+16
	mov	r0, #32
	str	r6, [sp]
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	bl	dprint_vfmw
	mov	r3, r5
	str	r6, [sp]
	mov	r0, #32
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	bl	dprint_vfmw
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	mov	r3, r5
	str	r6, [sp]
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r3, [r7, #116]
	mov	r0, #30
	blx	r3
	ldr	r3, [r7, #112]
	blx	r3
	mov	r3, r5
	str	r6, [sp]
	mov	r0, #32
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	bl	dprint_vfmw
	mov	r3, r5
	str	r6, [sp]
	mov	r0, #32
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	bl	dprint_vfmw
	str	r6, [sp]
	mov	r3, r5
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	mov	r0, #32
	bl	dprint_vfmw
	b	.L38
.L33:
	mov	r7, #1
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	ldr	r2, .L46+24
	mov	r0, #32
	ldr	r1, .L46+28
	str	r7, [sp]
	bl	dprint_vfmw
	mov	r3, r5
	str	r7, [sp]
	mov	r0, #32
	ldr	r2, .L46+24
	ldr	r1, .L46+28
	bl	dprint_vfmw
	ldr	r3, .L46+8
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L45
.L35:
	mov	r0, r3
	mov	r2, #151
	ldr	r1, .L46+32
	bl	dprint_vfmw
	b	.L36
.L43:
	ldr	r2, [r4, #128]
	str	r2, [r3, #92]
	ldr	r2, [r4, #148]
	str	r2, [r3, #112]
	b	.L28
.L42:
	str	r6, [sp]
	mov	r3, r5
	ldr	r2, .L46+24
	ldr	r1, .L46+36
	bl	dprint_vfmw
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L47:
	.align	2
.L46:
	.word	s_ScdRegPhyBaseAddr
	.word	g_HwMem
	.word	g_vdm_hal_fun_ptr
	.word	g_pstRegCrg
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_LowDelaySeqIndex
	.word	.LANCHOR0+24
	.word	.LC2
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	VDH_Start_Mfde_Decode, .-VDH_Start_Mfde_Decode
	.align	2
	.global	VDH_Init_Module
	.type	VDH_Init_Module, %function
VDH_Init_Module:
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
	b	VDH_Reset_Global
	UNWIND(.fnend)
	.size	VDH_Init_Module, .-VDH_Init_Module
	.align	2
	.global	VDH_Start_Mfde_Module
	.type	VDH_Start_Mfde_Module, %function
VDH_Start_Mfde_Module:
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
	subs	r3, r0, #0
	beq	.L52
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L53
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Start_Mfde_Decode
.L53:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VDH_Start_Mfde_Repair
.L52:
	ldr	r3, .L54
	ldr	r2, .L54+4
	ldr	r1, .L54+8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L55:
	.align	2
.L54:
	.word	.LC3
	.word	.LANCHOR0+48
	.word	.LC4
	UNWIND(.fnend)
	.size	VDH_Start_Mfde_Module, .-VDH_Start_Mfde_Module
	.align	2
	.global	VDH_Start_Scd_Module
	.type	VDH_Start_Scd_Module, %function
VDH_Start_Scd_Module:
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
	subs	r5, r0, #0
	beq	.L63
	mov	r0, #49152
	ldrb	r4, [r5]	@ zero_extendqisi2
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	beq	.L64
	ldr	r6, .L66
	mov	r0, r4
	bl	ResetSCD
	ldr	r1, [r5, #24]
	ldr	r0, [r6, r4, asl #2]
	add	r0, r0, #2048
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #28]
	add	r0, r0, #2048
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #32]
	add	r0, r0, #2048
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #36]
	add	r0, r0, #2064
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #40]
	add	r0, r0, #2064
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #44]
	add	r0, r0, #2064
	add	r0, r0, #8
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #52]
	add	r0, r0, #2080
	bl	MEM_WritePhyWord
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L65
.L59:
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #92]
	add	r0, r0, #2096
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #96]
	add	r0, r0, #2112
	add	r0, r0, #4
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	ldr	r1, [r5, #48]
	add	r0, r0, #2064
	add	r0, r0, #12
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	mov	r1, #0
	add	r0, r0, #2048
	bl	MEM_WritePhyWord
	ldr	r0, [r6, r4, asl #2]
	mov	r1, #1
	add	r0, r0, #2048
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	MEM_WritePhyWord
.L65:
	ldr	r1, [r5, #56]
	ldr	r0, [r6, r4, asl #2]
	bl	MEM_WritePhyWord
	b	.L59
.L63:
	ldr	r3, .L66+4
	ldr	r2, .L66+8
	ldr	r1, .L66+12
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L64:
	mov	r3, #49152
	ldr	r2, .L66+8
	movt	r3, 63683
	ldr	r1, .L66+16
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L67:
	.align	2
.L66:
	.word	s_ScdRegPhyBaseAddr
	.word	.LC3
	.word	.LANCHOR0+72
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	VDH_Start_Scd_Module, .-VDH_Start_Scd_Module
	.align	2
	.global	VDH_Record_CrgRegData
	.type	VDH_Record_CrgRegData, %function
VDH_Record_CrgRegData:
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
	subs	r3, r0, #0
	beq	.L73
	cmp	r1, #0
	streq	r2, [r3]
	beq	.L68
	cmp	r1, #1
	streq	r2, [r3, #4]
	beq	.L68
	str	r2, [sp]
	mov	r3, r1
	ldr	r2, .L74
	mov	r0, #1
	ldr	r1, .L74+4
	bl	dprint_vfmw
.L68:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L73:
	ldr	r3, .L74+8
	ldr	r2, .L74
	ldr	r1, .L74+12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L75:
	.align	2
.L74:
	.word	.LANCHOR0+96
	.word	.LC7
	.word	.LC6
	.word	.LC4
	UNWIND(.fnend)
	.size	VDH_Record_CrgRegData, .-VDH_Record_CrgRegData
	.align	2
	.global	VDH_Record_ScdRegData
	.type	VDH_Record_ScdRegData, %function
VDH_Record_ScdRegData:
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
	subs	ip, r0, #0
	beq	.L106
	movw	r3, #2072
	cmp	r1, r3
	beq	.L79
	bls	.L107
	cmp	r1, #2096
	beq	.L93
	bhi	.L94
	cmp	r1, #2080
	streq	r2, [ip, #28]
	beq	.L76
	bls	.L108
	movw	r3, #2088
	cmp	r1, r3
	streq	r2, [ip, #48]
	beq	.L76
	movw	r3, #2092
	cmp	r1, r3
	streq	r2, [ip, #52]
	bne	.L78
.L76:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L107:
	movw	r3, #2052
	cmp	r1, r3
	beq	.L81
	bhi	.L82
	cmp	r1, #4
	streq	r2, [ip, #36]
	beq	.L76
	bls	.L109
	cmp	r1, #8
	streq	r2, [ip, #40]
	beq	.L76
	cmp	r1, #12
	streq	r2, [ip, #44]
	beq	.L76
.L78:
	str	r2, [sp]
	mov	r3, r1
	ldr	r2, .L112
	mov	r0, #1
	ldr	r1, .L112+4
	bl	dprint_vfmw
	b	.L76
.L82:
	movw	r3, #2060
	cmp	r1, r3
	streq	r2, [ip, #8]
	beq	.L76
	bls	.L110
	cmp	r1, #2064
	streq	r2, [ip, #12]
	beq	.L76
	movw	r3, #2068
	cmp	r1, r3
	streq	r2, [ip, #16]
	beq	.L76
	b	.L78
.L94:
	movw	r3, #2104
	cmp	r1, r3
	streq	r2, [ip, #64]
	beq	.L76
	bls	.L111
	movw	r3, #2108
	cmp	r1, r3
	streq	r2, [ip, #68]
	beq	.L76
	movw	r3, #2116
	cmp	r1, r3
	streq	r2, [ip, #72]
	beq	.L76
	b	.L78
.L111:
	movw	r3, #2100
	cmp	r1, r3
	streq	r2, [ip, #60]
	beq	.L76
	b	.L78
.L109:
	cmp	r1, #0
	streq	r2, [ip, #32]
	beq	.L76
	b	.L78
.L110:
	movw	r3, #2056
	cmp	r1, r3
	streq	r2, [ip, #4]
	beq	.L76
	b	.L78
.L108:
	movw	r3, #2076
	cmp	r1, r3
	streq	r2, [ip, #24]
	beq	.L76
	b	.L78
.L79:
	str	r2, [ip, #20]
	b	.L76
.L81:
	str	r2, [ip]
	b	.L76
.L93:
	str	r2, [ip, #56]
	b	.L76
.L106:
	ldr	r3, .L112+8
	ldr	r2, .L112
	ldr	r1, .L112+12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L113:
	.align	2
.L112:
	.word	.LANCHOR0+120
	.word	.LC7
	.word	.LC6
	.word	.LC4
	UNWIND(.fnend)
	.size	VDH_Record_ScdRegData, .-VDH_Record_ScdRegData
	.align	2
	.global	VDH_Record_MfdeRegData
	.type	VDH_Record_MfdeRegData, %function
VDH_Record_MfdeRegData:
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
	subs	r3, r0, #0
	beq	.L175
	cmp	r1, #92
	beq	.L117
	bls	.L176
	cmp	r1, #124
	beq	.L130
	bhi	.L131
	cmp	r1, #108
	streq	r2, [r3, #44]
	beq	.L114
	bls	.L177
	cmp	r1, #116
	streq	r2, [r3, #52]
	beq	.L114
	cmp	r1, #120
	streq	r2, [r3, #56]
	beq	.L114
	cmp	r1, #112
	bne	.L116
	str	r2, [r3, #48]
.L114:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L131:
	cmp	r1, #148
	streq	r2, [r3, #72]
	beq	.L114
	bls	.L178
	cmp	r1, #156
	streq	r2, [r3, #80]
	beq	.L114
	movw	r0, #61472
	cmp	r1, r0
	streq	r2, [r3, #84]
	beq	.L114
	cmp	r1, #152
	bne	.L116
	str	r2, [r3, #76]
	b	.L114
.L176:
	cmp	r1, #36
	beq	.L119
	bhi	.L120
	cmp	r1, #16
	streq	r2, [r3, #8]
	beq	.L114
	bls	.L179
	cmp	r1, #24
	streq	r2, [r3, #16]
	beq	.L114
	cmp	r1, #32
	streq	r2, [r3, #20]
	beq	.L114
	cmp	r1, #20
	bne	.L116
	str	r2, [r3, #12]
	b	.L114
.L177:
	cmp	r1, #100
	streq	r2, [r3, #36]
	beq	.L114
	cmp	r1, #104
	streq	r2, [r3, #40]
	beq	.L114
	cmp	r1, #96
	bne	.L116
	str	r2, [r3, #32]
	b	.L114
.L178:
	cmp	r1, #132
	streq	r2, [r3, #68]
	beq	.L114
	cmp	r1, #144
	beq	.L114
	cmp	r1, #128
	streq	r2, [r3, #64]
	beq	.L114
.L116:
	str	r2, [sp]
	mov	r3, r1
	ldr	r2, .L180
	mov	r0, #1
	ldr	r1, .L180+4
	bl	dprint_vfmw
	b	.L114
.L179:
	cmp	r1, #8
	streq	r2, [r3]
	beq	.L114
	cmp	r1, #12
	streq	r2, [r3, #4]
	beq	.L114
	b	.L116
.L120:
	cmp	r1, #72
	beq	.L114
	bhi	.L129
	cmp	r1, #64
	beq	.L114
	cmp	r1, #68
	beq	.L114
	cmp	r1, #60
	bne	.L116
	b	.L114
.L175:
	ldr	r3, .L180+8
	ldr	r2, .L180
	ldr	r1, .L180+12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L130:
	str	r2, [r3, #60]
	b	.L114
.L117:
	str	r2, [r3, #28]
	b	.L114
.L119:
	str	r2, [r3, #24]
	b	.L114
.L129:
	cmp	r1, #80
	beq	.L114
	cmp	r1, #84
	beq	.L114
	cmp	r1, #76
	bne	.L116
	b	.L114
.L181:
	.align	2
.L180:
	.word	.LANCHOR0+144
	.word	.LC7
	.word	.LC6
	.word	.LC4
	UNWIND(.fnend)
	.size	VDH_Record_MfdeRegData, .-VDH_Record_MfdeRegData
	.align	2
	.global	VDH_Init_Hardware
	.type	VDH_Init_Hardware, %function
VDH_Init_Hardware:
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
	ldr	r4, .L190
	ldr	r3, [r4, #36]
	cmp	r3, #0
	beq	.L183
	mov	r0, #0
	blx	r3
.L183:
	ldr	r3, [r4, #68]
	cmp	r3, #0
	beq	.L184
	mov	r0, #0
	blx	r3
.L185:
	ldr	r0, [r4, #72]
	cmp	r0, #0
	beq	.L186
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r0	@ indirect register sibling call
.L186:
	movw	r2, #481
	ldr	r1, .L190+4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L184:
	mov	r0, r3
	mov	r2, #480
	ldr	r1, .L190+4
	bl	dprint_vfmw
	b	.L185
.L191:
	.align	2
.L190:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Init_Hardware, .-VDH_Init_Hardware
	.align	2
	.global	VDH_Enable_Scd_Module
	.type	VDH_Enable_Scd_Module, %function
VDH_Enable_Scd_Module:
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
	ldr	r3, .L194
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L193
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L193:
	mov	r0, r3
	movw	r2, #493
	ldr	r1, .L194+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L195:
	.align	2
.L194:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Enable_Scd_Module, .-VDH_Enable_Scd_Module
	.align	2
	.global	VDH_Disable_Scd_Module
	.type	VDH_Disable_Scd_Module, %function
VDH_Disable_Scd_Module:
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
	ldr	r3, .L198
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L197
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L197:
	mov	r0, r3
	mov	r2, #504
	ldr	r1, .L198+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L199:
	.align	2
.L198:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Disable_Scd_Module, .-VDH_Disable_Scd_Module
	.align	2
	.global	VDH_Reset_Scd_Module
	.type	VDH_Reset_Scd_Module, %function
VDH_Reset_Scd_Module:
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
	b	ResetSCD
	UNWIND(.fnend)
	.size	VDH_Reset_Scd_Module, .-VDH_Reset_Scd_Module
	.align	2
	.global	VDH_Enable_Mfde_Module
	.type	VDH_Enable_Mfde_Module, %function
VDH_Enable_Mfde_Module:
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
	ldr	r3, .L203
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L202
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L202:
	mov	r0, r3
	movw	r2, #525
	ldr	r1, .L203+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L204:
	.align	2
.L203:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Enable_Mfde_Module, .-VDH_Enable_Mfde_Module
	.align	2
	.global	VDH_Disable_Mfde_Module
	.type	VDH_Disable_Mfde_Module, %function
VDH_Disable_Mfde_Module:
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
	ldr	r3, .L208
	mov	r4, r0
	ldr	r3, [r3, #8]
	cmp	r3, #0
	beq	.L206
	blx	r3
.L207:
	mov	r0, r4
	bl	SCDDRV_SetStateIdle
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VDMDRV_SetStateIdle
.L206:
	mov	r0, r3
	movw	r2, #535
	ldr	r1, .L208+4
	bl	dprint_vfmw
	b	.L207
.L209:
	.align	2
.L208:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Disable_Mfde_Module, .-VDH_Disable_Mfde_Module
	.align	2
	.global	VDH_Reset_Mfde_Module
	.type	VDH_Reset_Mfde_Module, %function
VDH_Reset_Mfde_Module:
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
	ldr	r3, .L212
	ldr	r3, [r3, #76]
	cmp	r3, #0
	beq	.L211
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L211:
	mov	r0, r3
	movw	r2, #547
	ldr	r1, .L212+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L213:
	.align	2
.L212:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Reset_Mfde_Module, .-VDH_Reset_Mfde_Module
	.align	2
	.global	VDH_Enable_Bpd_Module
	.type	VDH_Enable_Bpd_Module, %function
VDH_Enable_Bpd_Module:
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
	ldr	r4, .L218
	mov	r5, r0
	ldr	r3, [r4, #4]
	cmp	r3, #0
	beq	.L215
	blx	r3
.L216:
	ldr	r3, [r4, #28]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L215:
	mov	r0, r3
	movw	r2, #557
	ldr	r1, .L218+4
	bl	dprint_vfmw
	b	.L216
.L219:
	.align	2
.L218:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Enable_Bpd_Module, .-VDH_Enable_Bpd_Module
	.align	2
	.global	VDH_Disable_Bpd_Module
	.type	VDH_Disable_Bpd_Module, %function
VDH_Disable_Bpd_Module:
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
	ldr	r3, .L222
	ldr	r3, [r3, #32]
	cmp	r3, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L223:
	.align	2
.L222:
	.word	g_vdm_hal_fun_ptr
	UNWIND(.fnend)
	.size	VDH_Disable_Bpd_Module, .-VDH_Disable_Bpd_Module
	.align	2
	.global	VDH_Enable_Dsp_Module
	.type	VDH_Enable_Dsp_Module, %function
VDH_Enable_Dsp_Module:
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
	ldr	r3, .L226
	ldr	r3, [r3, #12]
	cmp	r3, #0
	beq	.L225
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L225:
	mov	r0, r3
	movw	r2, #578
	ldr	r1, .L226+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L227:
	.align	2
.L226:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Enable_Dsp_Module, .-VDH_Enable_Dsp_Module
	.align	2
	.global	VDH_Disable_Dsp_Module
	.type	VDH_Disable_Dsp_Module, %function
VDH_Disable_Dsp_Module:
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
	ldr	r3, .L230
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L229
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3	@ indirect register sibling call
.L229:
	mov	r0, r3
	mov	r2, #588
	ldr	r1, .L230+4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L231:
	.align	2
.L230:
	.word	g_vdm_hal_fun_ptr
	.word	.LC0
	UNWIND(.fnend)
	.size	VDH_Disable_Dsp_Module, .-VDH_Disable_Dsp_Module
	.align	2
	.global	VDH_Load_Dsp_Code
	.type	VDH_Load_Dsp_Code, %function
VDH_Load_Dsp_Code:
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
	b	SCDDRV_LoadDspCode
	UNWIND(.fnend)
	.size	VDH_Load_Dsp_Code, .-VDH_Load_Dsp_Code
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.49283, %object
	.size	__func__.49283, 22
__func__.49283:
	.ascii	"VDH_Start_Mfde_Repair\000"
	.space	2
	.type	__func__.49291, %object
	.size	__func__.49291, 22
__func__.49291:
	.ascii	"VDH_Start_Mfde_Decode\000"
	.space	2
	.type	__func__.49298, %object
	.size	__func__.49298, 22
__func__.49298:
	.ascii	"VDH_Start_Mfde_Module\000"
	.space	2
	.type	__func__.49304, %object
	.size	__func__.49304, 21
__func__.49304:
	.ascii	"VDH_Start_Scd_Module\000"
	.space	3
	.type	__func__.49310, %object
	.size	__func__.49310, 22
__func__.49310:
	.ascii	"VDH_Record_CrgRegData\000"
	.space	2
	.type	__func__.49316, %object
	.size	__func__.49316, 22
__func__.49316:
	.ascii	"VDH_Record_ScdRegData\000"
	.space	2
	.type	__func__.49343, %object
	.size	__func__.49343, 23
__func__.49343:
	.ascii	"VDH_Record_MfdeRegData\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"VDMHAL_NULL_FUN_PRINT,L%d\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"%s: map mfde %d register 0x%x failed!\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"pTask is null\000" )
	.space	2
.LC4:
	ASCII(.ascii	"%s: %s\012\000" )
.LC5:
	ASCII(.ascii	"%s: map scd register 0x%x failed!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"pRegMap is null\000" )
.LC7:
	ASCII(.ascii	"%s: unrecord reg 0x%x data %d!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
